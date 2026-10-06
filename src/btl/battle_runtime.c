/**
 * battle_runtime.c
 * Battle Core Logic
 */

#include "macros.h"
#include "mode_continue.h"
#include "registration_data.h"
#include "map_api.h"
#include "msg_api.h"
#include "display.h"
#include "key.h"
#include "m4a_song.h"
#include "obj_api.h"
#include "battle.h"
#include "battle_actor.h"
#include "world_types.h"
#include "gba/keys.h"
#include "fade.h"
#include "player_progression.h"
#include <stdlib.h>
#include "enemy_tile_counts.h"
#include <string.h>
#include "anim.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "card_api.h"
#include "card_battle.h"
#include "engine_math.h"
#include "game_state.h"
#include "listpool.h"
#include "m4a.h"
#include "map_runtime.h"
#include "mode.h"
#include "obj.h"
#include "player_progression_types.h"
#include "save_api.h"
#include "system_state.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"
#include "gba/macro.h"
#include <stddef.h>
#include "hum_common.h"
#include "card_deckmenu2.h"

s32 gUnk_02039DC0 EWRAM_COMMON(4);
s32* gLockonDoorPosition EWRAM_COMMON(4);

void SetBattleZoom(u16 steps, s32 scale, s32 x, s32 y) {
    gBtlWork->zoomScale = scale;
    gBtlWork->zoomSteps = steps;
    gBtlWork->zoomX = x;
    gBtlWork->zoomY = y;
}

void AnimChangeWithDef(const AnimDef* defs, void* anim, u16 index, u16 flags, void* tiles) {
    const AnimDef* e = &defs[index];
    AnimChangeWithTables(anim, e->animId, flags, e->anims, e->gfxTable);
    SetObjTileSource(tiles, e->tiles);
}

void WorldToScreen(s16* outX, s16* outY, s32 px, s32 py, s32 pz) {
    s16 x;
    s16 y;
    u8 ang;
    s32 c;
    s16 idx;
    const s16* sine;
    s32 u;
    s32 v;

    if (gBtlWork->scale == 0x100) {
        x = (px >> 8) - (gBtlWork->viewX >> 8);
        y = ((py >> 8) + (pz >> 8)) - (gBtlWork->viewY >> 8);
    } else {
        x = (((px >> 8) - (gBtlWork->viewX >> 8)) * gBtlWork->scale) >> 8;
        y = ((((py >> 8) + (pz >> 8)) - (gBtlWork->viewY >> 8)) * gBtlWork->scale) >> 8;
    }

    if (gBtlWork->rotation == 0) {
        *outX = x + 120;
        *outY = y + 80;
    } else {
        ang = -gBtlWork->rotation;
        sine = gSineTable;
        c = ang + 64;
        idx = c & 255;
        u = sine[idx] * x;
        v = sine[idx += 64] * x;
        u += sine[ang] * y;
        v += sine[c] * y;
        *outX = (u >> 8) + 120;
        *outY = (v >> 8) + 80;
    }
}

void CreateBtlPopTask(BtlObj* obj, s16 kind) {
    BtlPrizeSrc a;
    s16* t;

    if (kind != 9) {
        if (obj->parent != NULL) {
            t = &obj->parent->popCooldown;
        } else {
            t = &obj->popCooldown;
        }

        if (*t > 0) {
            return;
        }

        *t = 50;
    }

    a.x = obj->x;
    a.y = obj->y;
    a.z = obj->z - ((obj->height / 2) << 8);

    if (gGameState.flags & GAME_FLAG_RIKU) {
        if (kind == 9) {
            a.kind = abs(gBtlWork->breakDifference);
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPopCb, &a);
            return;
        }

        a.kind = kind;
        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPop, &a);
        return;
    }

    a.kind = kind;

    if (kind == 9) {
        if (obj->flags & BTLOBJ_FLAG_NO_BREAK_POP) {
            return;
        }

        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPop, &a);
        return;
    }

    TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPop, &a);
}

void BtlWorkInit() {
    u8* d;
    u8* p;
    CpuFill32(0, gBtlWork, sizeof(BtlWork));
    gBtlWork->phase = BTL_PHASE_START;
    gBtlWork->fadeExcludedPalettes = 0xFFFF0000;
    gBtlWork->gravity = 0x42;
    gBtlWork->fadeAmount = 10;
    d = gBtlWork->savedProgression;
    p = (u8*)&gGameState;
    p += offsetof(GameState, progression);
    memcpy(d, p, 0x88);
    ListPoolInit(&gBtlWork->pool);
    ListPoolInit(&gBtlWork->pool2);
}

void UpdateEnemyCardUse() {
    BtlObj* p;

    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_BUSY) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_CARD_BREAK) {
        return;
    }

    p = gBtlWork->actor4;

    if (p == NULL) {
        return;
    }

    if (p->flags & BTLOBJ_FLAGS_NO_CARD_USE) {
        return;
    }

    gBtlWork->actor3 = p;
    UseEnemyCard(p->kind);
}

void HandleSoraCardInput() {
    BtlObj* p;
    u16 t;
    u16 a;

    if (gBtlWork->flags & BTL_FLAG_GIMMICK_CARD_ACTIVE) {
        return;
    }

    t = gBtlWork->listSwitchTimer;

    if ((s16)t > 0) {
        gBtlWork->listSwitchTimer = t - 1;

        if (gBtlWork->listSwitchTimer == 0) {
            RequestSwitchSoraCardList();
        }

        return;
    }

    if (gBtlWork->flags & BTL_FLAG_CAN_CHARGE_RELOAD) {
        if (!(gGameState.flags & GAME_FLAG_RIKU)) {
            if (GetKeysHeld() & A_BUTTON) {
                if (!(GetKeysHeld() & (L_BUTTON | R_BUTTON))) {
                    SetSoraReloadCharging();
                }
            }
        }
    }

    if (gBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
        return;
    }

    a = ReadKeyChord(L_BUTTON, R_BUTTON);

    switch (a) {
    case L_BUTTON:
        RequestSoraNextCard();
        break;
    case R_BUTTON:
        RequestSoraPrevCard();
        break;
    }

    if (GetKeysPressed() & SELECT_BUTTON) {
        RequestSwitchSoraCardList();
    }

    if (IsSoraReloadCardSelected()) {
        gBtlWork->lHeldFrames = 0;
        gBtlWork->rHeldFrames = 0;
    } else {
        if ((GetKeysHeld() & L_BUTTON) && !(GetKeysHeld() & R_BUTTON)) {
            if (gBtlWork->lHeldFrames < 255) {
                gBtlWork->lHeldFrames++;
            }
        } else {
            gBtlWork->lHeldFrames = 0;
        }

        if ((GetKeysHeld() & R_BUTTON) && !(GetKeysHeld() & L_BUTTON)) {
            if (gBtlWork->rHeldFrames < 255) {
                gBtlWork->rHeldFrames++;
            }
        } else {
            gBtlWork->rHeldFrames = 0;
        }
    }

    if (gBtlWork->lHeldFrames > 32) {
        RequestSoraNextCard();
    }

    if (gBtlWork->rHeldFrames > 32) {
        RequestSoraPrevCard();
    }

    p = gBtlWork->actor;

    if (p->flags & BTLOBJ_FLAG_CARD_USE_BLOCKED) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_BUSY) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_CARD_BREAK) {
        return;
    }

    if (p->flags & BTLOBJ_FLAG_DAMAGE_PENDING) {
        return;
    }

    if (a == (L_BUTTON | R_BUTTON)) {
        if (GetSoraStockCount() > 2) {
            RequestSoraStockUse();
        } else {
            RequestSoraCardStock();
        }
    }

    if (GetKeysPressed() & A_BUTTON) {
        RequestSoraCardUse();

        if (GetSoraCardListIndex() == 3) {
            if (IsSoraSelectionEmpty() == 0) {
                gBtlWork->listSwitchTimer = 15;
            }
        }
    }
}

void HandleRikuCardInput() {
    BtlObj* p;
    u16 t;
    u16 a;

    if (gRikuBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
        return;
    }

    t = gRikuBtlWork->listSwitchTimer;

    if ((s16)t > 0) {
        gRikuBtlWork->listSwitchTimer = t - 1;

        if (gRikuBtlWork->listSwitchTimer == 0) {
            RequestSwitchRikuCardList();
        }

        return;
    }

    a = ReadKeyChord(L_BUTTON, R_BUTTON);

    switch (a) {
    case L_BUTTON:
        RequestRikuNextCard();
        break;
    case R_BUTTON:
        RequestRikuPrevCard();
        break;
    }

    if (GetKeysPressed() & SELECT_BUTTON) {
        RequestSwitchRikuCardList();
    }

    if (IsRikuReloadCardSelected()) {
        gBtlWork->lHeldFrames = 0;
        gBtlWork->rHeldFrames = 0;
    } else {
        if ((GetKeysHeld() & L_BUTTON) && !(GetKeysHeld() & R_BUTTON)) {
            if (gBtlWork->lHeldFrames < 255) {
                gBtlWork->lHeldFrames++;
            }
        } else {
            gBtlWork->lHeldFrames = 0;
        }

        if ((GetKeysHeld() & R_BUTTON) && !(GetKeysHeld() & L_BUTTON)) {
            if (gBtlWork->rHeldFrames < 255) {
                gBtlWork->rHeldFrames++;
            }
        } else {
            gBtlWork->rHeldFrames = 0;
        }
    }

    if (gBtlWork->lHeldFrames > 32) {
        RequestRikuNextCard();
    }

    if (gBtlWork->rHeldFrames > 32) {
        RequestRikuPrevCard();
    }

    p = gRikuBtlWork->actor;

    if (p->flags & BTLOBJ_FLAG_CARD_USE_BLOCKED) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_BUSY) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_CARD_BREAK) {
        return;
    }

    if (p->flags & BTLOBJ_FLAG_DAMAGE_PENDING) {
        return;
    }

    if (a == (L_BUTTON | R_BUTTON)) {
        if (GetRikuStockCount() > 2) {
            RequestRikuStockUse();
        } else {
            RequestRikuCardStock();
        }
    }

    if (GetKeysPressed() & A_BUTTON) {
        RequestRikuCardUse();

        if (GetRikuCardListIndex() == 3) {
            if (IsRikuSelectionEmpty() == 0) {
                gRikuBtlWork->listSwitchTimer = 15;
            }
        }
    }
}

void HandleTutorialCardInput() {
    BtlObj* p;
    u16 a;
    u16 pressed;
    u16 held;

    if (!(gBtlWork->flags & BTL_FLAG_TUTORIAL_NO_CARD_USE)) {
        if (gBtlWork->flags & BTL_FLAG_CAN_CHARGE_RELOAD) {
            if (!(gGameState.flags & GAME_FLAG_RIKU)) {
                if (GetKeysHeld() & A_BUTTON) {
                    if (!(GetKeysHeld() & (L_BUTTON | R_BUTTON))) {
                        SetSoraReloadCharging();
                    }
                }
            }
        }
    }

    if (gBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
        return;
    }

    a = ReadKeyChord(L_BUTTON, R_BUTTON);
    pressed = GetKeysPressed();
    held = GetKeysHeld();

    if (!(gBtlWork->flags & BTL_FLAG_TUTORIAL_NO_CARD_SELECT)) {
        switch (a) {
        case L_BUTTON:
            RequestSoraNextCard();
            break;
        case R_BUTTON:
            RequestSoraPrevCard();
            break;
        }
    }

    if (!(gBtlWork->flags & BTL_FLAG_TUTORIAL_NO_LIST_SWITCH)) {
        if (pressed & SELECT_BUTTON) {
            RequestSwitchSoraCardList();
        }
    }

    if (!(gBtlWork->flags & BTL_FLAG_TUTORIAL_NO_CARD_SELECT)) {
        if (IsSoraReloadCardSelected()) {
            gBtlWork->lHeldFrames = 0;
            gBtlWork->rHeldFrames = 0;
        } else {
            if ((held & L_BUTTON) && !(held & R_BUTTON)) {
                if (gBtlWork->lHeldFrames < 255) {
                    gBtlWork->lHeldFrames++;
                }
            } else {
                gBtlWork->lHeldFrames = 0;
            }

            if ((held & R_BUTTON) && !(held & L_BUTTON)) {
                if (gBtlWork->rHeldFrames < 255) {
                    gBtlWork->rHeldFrames++;
                }
            } else {
                gBtlWork->rHeldFrames = 0;
            }
        }
    }

    if (gBtlWork->lHeldFrames > 32) {
        RequestSoraNextCard();
    }

    if (gBtlWork->rHeldFrames > 32) {
        RequestSoraPrevCard();
    }

    p = gBtlWork->actor;

    if (p->flags & BTLOBJ_FLAG_CARD_USE_BLOCKED) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_BUSY) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_CARD_BREAK) {
        return;
    }

    if (p->flags & BTLOBJ_FLAG_DAMAGE_PENDING) {
        return;
    }

    if (a == (L_BUTTON | R_BUTTON)) {
        if (GetSoraStockCount() > 2) {
            if (!(gBtlWork->flags & BTL_FLAG_TUTORIAL_NO_STOCK_USE)) {
                RequestSoraStockUse();
            }
        } else {
            if (!(gBtlWork->flags & BTL_FLAG_TUTORIAL_NO_STOCK)) {
                RequestSoraCardStock();
            }
        }
    }

    if (!(gBtlWork->flags & BTL_FLAG_TUTORIAL_NO_CARD_USE)) {
        if (pressed & A_BUTTON) {
            RequestSoraCardUse();
        }
    }
}

void MakeOpponentsHittable() {
    BtlWork* w = gBtlWork;
    BtlObj* p;

    if (w->flags & BTL_FLAG_VS_BATTLE) {
        if (w->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            p = gRikuBtlWork->actor;
            p->flags &= ~BTLOBJ_FLAG_HIT_LOCKED;
            return;
        }
    } else if (w->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
        p = ListPoolFirst(&w->pool);

        while (p != NULL) {
            p->flags &= ~BTLOBJ_FLAG_HIT_LOCKED;
            p->invincibleTimer = 0;
            p = ListPoolNext(&p->node);
        }

        return;
    }

    p = w->actor;
    p->flags &= ~BTLOBJ_FLAG_HIT_LOCKED;
}

void DropFriendCard(s32 x, s32 y, s32 z) {
    u16 flags;
    s16 v;

    flags = gGameState.progression.friendFlags;

    if (gBtlWork->flags & BTL_FLAG_TUTORIAL) {
        return;
    }

    if (gGameState.flags & GAME_FLAG_RIKU) {
        if (flags & FRIEND_FLAG_THE_KING) {
            SetJiminyFlag(244);
            CreateFriendCardTask(gBtlWork->taskPools, x >> 8, y >> 8, z >> 8, 7);
        }

        return;
    }

    v = -1;

    if (GetRandom() % 4 != 0) {
        switch (gGameState.world) {
        case WORLD_AGRABAH:
            if (flags & FRIEND_FLAG_ALADDIN) {
                v = 2;
                SetJiminyFlag(159);
            }

            break;
        case WORLD_ATLANTICA:
            if (flags & FRIEND_FLAG_ARIEL) {
                v = 3;
                SetJiminyFlag(160);
            }

            break;
        case WORLD_HALLOWEEN_TOWN:
            if (flags & FRIEND_FLAG_JACK) {
                v = 4;
                SetJiminyFlag(161);
            }

            break;
        case WORLD_NEVER_LAND:
            if (flags & FRIEND_FLAG_PETER_PAN) {
                v = 5;
                SetJiminyFlag(162);
            }

            break;
        case WORLD_HOLLOW_BASTION:
            if (flags & FRIEND_FLAG_THE_BEAST) {
                v = 6;
                SetJiminyFlag(163);
            }

            break;
        }
    }

    if (v == -1) {
        if (GetRandom() % 2 != 0) {
            if (flags & FRIEND_FLAG_GOOFY) {
                v = 0;
                SetJiminyFlag(158);
            }
        } else {
            if (flags & FRIEND_FLAG_DONALD_DUCK) {
                v = 1;
                SetJiminyFlag(157);
            }
        }
    }

    if (v != -1) {
        CreateFriendCardTask(gBtlWork->taskPools, x >> 8, y >> 8, z >> 8, v);
    }
}

void EndCardPlay() {
    gBtlWork->phase = BTL_PHASE_IDLE;

    if (!(gBtlWork->flags & BTL_FLAG_CARD_BREAK)) {
        gBtlWork->flags |= BTL_FLAG_CARD_PLAY_ENDED;
    }

    gBtlWork->flags &= ~BTL_FLAG_OPPONENT_CARD_ACTION;
    gBtlWork->flags &= ~BTL_FLAG_PLAYER_CARD_ACTION;
}

enum BtlEndStep {
    BTL_END_STEP_REWARD_SCREEN = -1,
    BTL_END_STEP_CLOSE_CARDS,
    BTL_END_STEP_WAIT_FRAME,
    BTL_END_STEP_REWARDS,
    BTL_END_STEP_FADE_OUT,
    BTL_END_STEP_EXIT
};

void UpdateBattleState() {
    BtlObj* player;
    s32 i;
    s32 changed;
    s32 busy;
    s8 count;
    BtlPrizeArgs pos;

    player = gBtlWork->actor;

    if (gBtlWork->hcEffect == 53) {
        gBtlWork->gravity = 38;
    } else {
        gBtlWork->gravity = 66;
    }

    if (gBtlWork->hcEffect == 19) {
        if (!(gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) && gFrameCounter % 30 == 0) {
            gBtlWork->targetX = (gBtlWork->xMin + GetRandom() % (gBtlWork->xMax - gBtlWork->xMin + 1)) * 256;
            gBtlWork->targetY = (gBtlWork->yMin + GetRandom() % (gBtlWork->yMax - gBtlWork->yMin + 1)) * 256;
            gBtlWork->targetZ = 0;
        }
    } else {
        gBtlWork->targetX = gBtlWork->actor->x;
        gBtlWork->targetY = gBtlWork->actor->y;
        gBtlWork->targetZ = gBtlWork->actor->z;
    }

    gBtlWork->flags &= ~BTL_FLAG_ENEMY_FRAME_CHANGED;

    switch ((u32)gBtlWork->phase) {
    case BTL_PHASE_IDLE:
    case BTL_PHASE_CARD_PLAY:
        if (gBtlWork->flags & BTL_FLAG_TUTORIAL) {
            HandleTutorialCardInput();
#ifdef VERSION_EU
            HandleRikuTutorialCardInput();
#else
            HandleRikuAiCardInput();
#endif
        } else if (gBtlWork->flags & BTL_FLAG_HUM_BATTLE) {
            HandleSoraCardInput();
            HandleRikuAiCardInput();
        } else {
            UpdateEnemyCardUse();
            HandleSoraCardInput();
        }

        break;
    }

    gBtlWork->actor4 = NULL;
    TaskPoolUpdate(&gBtlWork->taskPools[1]);

    if (gBtlWork->flags & BTL_FLAG_CARD_BREAK) {
        gBtlWork->flags |= BTL_FLAG_STOP_BGFX;
        gBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;

        if (gBtlWork->flags & BTL_FLAG_HUM_BATTLE) {
            gRikuBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;
        }

        gBtlWork->phase = BTL_PHASE_IDLE;

        if (gBtlWork->soraOwnsPlay) {
            BtlObj* obj;
            gBtlWork->flags &= ~BTL_FLAG_OPPONENT_CARD_ACTION;
            obj = gBtlWork->actor3;

            if (obj != NULL) {
                obj->flags |= BTLOBJ_FLAG_CARD_BREAK_PENDING;
            }

            FadeFromAmount(FADE_MODE_ADD_WHITE, 10, 4);
        } else {
            gBtlWork->flags &= ~BTL_FLAG_PLAYER_CARD_ACTION;
            player->flags |= BTLOBJ_FLAG_CARD_BREAK_PENDING;
            FadeFromAmount(FADE_MODE_RED, 10, 4);
        }

        MosaicStartIn(16, 15);
        SetBattleZoom(1, 256, gBtlWork->x2, gBtlWork->y2);
        gBtlWork->phaseStep = 0;
    }

    if (gBtlWork->flags & BTL_FLAG_CARD_PLAY_START) {
        changed = 1;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_START;

        if (gBtlWork->soraOwnsPlay) {
            gBtlWork->flags |= BTL_FLAG_PLAYER_CARD_ACTION;
            player->flags |= BTLOBJ_FLAG_CARD_ACTION_PENDING;
        } else {
            BtlObj* obj;
            gBtlWork->flags |= BTL_FLAG_OPPONENT_CARD_ACTION;
            obj = gBtlWork->actor3;

            if (obj != NULL) {
                obj->flags |= BTLOBJ_FLAG_CARD_ACTION_PENDING;
            }
        }

        gBtlWork->phase = BTL_PHASE_CARD_PLAY;
        gBtlWork->phaseStep = 0;
    } else {
        changed = 0;
    }

    if (gBtlWork->flags & BTL_FLAG_PLAYER_DEFEATED) {
        if (gBtlWork->phase != BTL_PHASE_GAME_OVER) {
            gBtlWork->phase = BTL_PHASE_GAME_OVER;
            gBtlWork->phaseStep = 0;
        }
    } else if (gBtlWork->flags & BTL_FLAG_BATTLE_OVER) {
        if (gBtlWork->phase != BTL_PHASE_END) {
            gBtlWork->phase = BTL_PHASE_END;
            gBtlWork->phaseStep = BTL_END_STEP_CLOSE_CARDS;

            switch (gBtlWork->battleId) {
            case 120:
            case 124:
                pos.x = 0x10000;
                pos.y = (gBtlWork->yMin + gBtlWork->yMax) * 128;
                pos.z = -0x4600;
                CreateBossPrizeCardTask(gBtlWork->taskPools, &pos);
                break;
            case 121:
                if (gBtlWork->flags & 0x100000) {
                    pos.x = 0x10000;
                    pos.y = (gBtlWork->yMin + gBtlWork->yMax) * 128;
                    pos.z = -0x4600;
                    CreateBossPrizeCardTask(gBtlWork->taskPools, &pos);
                }

                break;
            }
        }
    }

    switch ((u32)gBtlWork->phase) {
    case BTL_PHASE_START:
        if (gBtlWork->phaseStep == BTL_START_STEP_INTRO) {
            if (!(gBtlWork->flags & BTL_FLAG_TUTORIAL)) {
                gBtlWork->task = TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlStart, NULL);
            }

            gBtlWork->phaseStep = BTL_START_STEP_EXCLUDE_PALETTES;
        }

        if (FadeIsActive()) {
            break;
        }

        if (gBtlWork->phaseStep == BTL_START_STEP_EXCLUDE_PALETTES) {
            for (i = 0; i < 32; i++) {
                if (gBtlWork->fadeExcludedPalettes & (s32)(1U << i)) {
                    FadeSetPaletteExcluded(i, 1);
                }
            }

            gBtlWork->phaseStep = BTL_START_STEP_CREATE_TASKS;
        }

        if (IsTaskActiveNamed(gBtlWork->task, gTaskDescBtlStart.name)) {
            break;
        }

        if (gBtlWork->phaseStep == BTL_START_STEP_CREATE_TASKS) {
            gBtlWork->flags |= BTL_FLAG_ENEMY_MOVE_ENABLED;
            gBtlWork->flags &= ~BTL_FLAG_PAUSE_DISABLED;
            TaskCreate(gBtlWork->taskPools, &gTaskDescBtlLockon, NULL);
            TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlHpply, NULL);

            if (!(gBtlWork->flags & BTL_FLAG_TUTORIAL)) {
                TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlHpenm, NULL);
            }

            TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlExp, NULL);

            if (!(gBtlWork->flags & BTL_FLAG_BOSS_BATTLE) && !(gBtlWork->flags & BTL_FLAG_HUM_BATTLE)) {
                switch (gBtlWork->battleId) {
                case 120:
                case 122:
                case 123:
                case 124:
                case 178:
                case 179:
                case 180:
                case 181:
                case 182:
                case 183:
                case 184:
                    break;
                default:
                    if (gDebugFlags & DEBUG_FLAG_CHKBTL) {
                        TaskCreate(gBtlWork->taskPools, &gTaskDescBtlEscape, NULL);
                    } else if (gGameState.progression.tutorialFlags & 0x20) {
                        TaskCreate(gBtlWork->taskPools, &gTaskDescBtlEscape, NULL);
                    }

                    break;
                }
            }

            TaskCreate(&gBtlWork->taskPools[1], &gTaskDescCardBattleSora, NULL);

            if (gBtlWork->flags & BTL_FLAG_TUTORIAL) {
                if (gBtlWork->battleId == 179) {
                    TaskCreate(&gBtlWork->taskPools[1], &gTaskDescCardBattleRiku, NULL);
                }
            } else if (gBtlWork->flags & BTL_FLAG_HUM_BATTLE) {
                TaskCreate(&gBtlWork->taskPools[1], &gTaskDescCardBattleRiku, NULL);
            }

            RequestOpenCards();
            RequestBossCardOpen();
            gBtlWork->phaseStep = BTL_START_STEP_FINISH;
        } else if (gBtlWork->phaseStep == BTL_START_STEP_FINISH) {
            gBtlWork->phase = BTL_PHASE_IDLE;
            gBtlWork->phaseStep = 0;

            if (gGameState.roomEffect == 5) {
                DropFriendCard(0x10000, gBtlWork->actor->y, gBtlWork->actor->z - 0x7800);
            }
        }

        break;
    case BTL_PHASE_IDLE:
        break;
    case BTL_PHASE_END:
        if (gBtlWork->phaseStep == BTL_END_STEP_CLOSE_CARDS) {
            RequestCloseCards();
            RequestBossCardClose();
            gBtlWork->flags &= ~BTL_FLAG_ENEMY_MOVE_ENABLED;

            if (gBtlWork->flags & BTL_FLAG_SUMMON_ACTIVE) {
                gBtlWork->flags |= BTL_FLAG_DISMISS_SUMMONS;
                FadeToOriginal(FADE_MODE_BLACK, 8);
            }

            SetBattleZoom(8, 256, gBtlWork->x2, gBtlWork->y2);
            gBtlWork->flags |= BTL_FLAG_CARD_PLAY_ENDED;
            gBtlWork->actor2 = NULL;
            gBtlWork->phaseStep = BTL_END_STEP_WAIT_FRAME;
            gBtlWork->hcEffect = 0;
            gBtlWork->flags |= BTL_FLAG_STOP_SPAWNING;
        } else if (gBtlWork->phaseStep == BTL_END_STEP_WAIT_FRAME) {
            gBtlWork->phaseStep = BTL_END_STEP_REWARDS;
        } else {
            if (BgFxIsActive()) {
                break;
            }

            if (gBtlWork->flags & BTL_FLAG_BOSS_DEFEATING) {
                break;
            }

            if (gBtlWork->prizeCount != 0 && !(gBtlWork->flags & BTL_FLAG_ESCAPED)) {
                break;
            }

            if (gBtlWork->flags & BTL_FLAG_PREMIRE_COLLECTED) {
                if (gBtlWork->phaseStep == BTL_END_STEP_REWARDS) {
                    ReleaseBattleTiles();
                    gBtlWork->task = TaskCreate(&gBtlWork->taskPools[1], &gTaskDescPremireChance, NULL);
                    gBtlWork->flags |= BTL_FLAG_PAUSE_DISABLED;
                    gBtlWork->flags |= BTL_FLAG_FIELD_HIDDEN;
                    gBtlWork->phaseStep = BTL_END_STEP_REWARD_SCREEN;
                } else {
                    if (IsTaskActiveNamed(gBtlWork->task, gTaskDescPremireChance.name)) {
                        break;
                    }

                    gBtlWork->flags &= ~BTL_FLAG_PREMIRE_COLLECTED;
                    gBtlWork->phaseStep = BTL_END_STEP_REWARDS;
                }

                break;
            }

            if (gBtlWork->pendingLevelUps != 0) {
                if (gBtlWork->phaseStep == BTL_END_STEP_REWARDS) {
                    ReleaseBattleTiles();
                    gBtlWork->task = TaskCreate(&gBtlWork->taskPools[1], &gTaskDescLevelUp, NULL);
                    gBtlWork->flags |= BTL_FLAG_PAUSE_DISABLED;
                    gBtlWork->flags |= BTL_FLAG_FIELD_HIDDEN;
                    gBtlWork->phaseStep = BTL_END_STEP_REWARD_SCREEN;
                }

                break;
            }

            if (gBtlWork->phaseStep == BTL_END_STEP_REWARD_SCREEN) {
                if (!IsTaskActive(gBtlWork->task)) {
                    BtlObj* healed;
                    gBtlWork->phaseStep = BTL_END_STEP_REWARDS;
                    healed = gBtlWork->actor;
                    healed->hp = gGameState.progression.maxHp;
                    healed->maxHp = gGameState.progression.maxHp;
                }

                break;
            }

            if (gBtlWork->phaseStep == BTL_END_STEP_REWARDS && !FadeIsActive()) {
                gBtlWork->flags |= BTL_FLAG_PAUSE_DISABLED;
                gBtlWork->hitStop = 99;
                gBtlWork->phaseStep = BTL_END_STEP_FADE_OUT;
            } else if (gBtlWork->phaseStep == BTL_END_STEP_FADE_OUT) {
                SetBackdropColor(0, 0, 0);
                FadeStartOut(FADE_MODE_BLACK, 15);
                FadeLock();
                gBtlWork->phaseStep = BTL_END_STEP_EXIT;
            } else if (!FadeIsActive()) {
                ExitBattle();
            }
        }

        break;
    case BTL_PHASE_GAME_OVER:
        if (gBtlWork->phaseStep == 0) {
            RequestCloseCards();
            RequestBossCardClose();
            gBtlWork->flags &= ~BTL_FLAG_ENEMY_MOVE_ENABLED;
            gBtlWork->flags |= BTL_FLAG_CARD_PLAY_ENDED;
            gBtlWork->actor2 = NULL;
            gBtlWork->pendingEnemies = 0;
        }

        if (gBtlWork->phaseStep == 140) {
            FadeStartOut(FADE_MODE_WHITE, 100);
            FadeLock();
            gBtlWork->flags |= BTL_FLAG_PAUSE_DISABLED;
            gBtlWork->flags |= BTL_FLAG_STOP_BGFX;
            gBtlWork->hitStop = 100;
        } else if (gBtlWork->phaseStep > 140 && !FadeIsActive()) {
            m4aMPlayAllStop();

            if (gDebugFlags & DEBUG_FLAG_CHKBTL) {
                ModeRequest(&gModeChkbtl, 0);
            } else {
                GameState* state = &gGameState;
                memcpy(&state->progression.maxHp, gBtlWork->savedProgression, 0x88);
                state->flags |= GAME_FLAG_BATTLE_NOT_WON;

                switch (gBtlWork->battleId) {
                case 166:
                    state->progression.friendFlags = 0;
                    break;
                case 174:
                    state->progression.friendFlags &= ~(FRIEND_FLAG_GOOFY | FRIEND_FLAG_DONALD_DUCK);
                    break;
#ifdef VERSION_EU
                case 158:
                    state->progression.friendFlags &= ~FRIEND_FLAG_PETER_PAN;
                    break;
#endif
                }

                ModeRequest(&gModeContinue, 0);
            }

            break;
        }

        gBtlWork->phaseStep++;
        break;
    case BTL_PHASE_CARD_PLAY: {
        BtlObj* obj;

        if (changed) {
            break;
        }

        busy = 0;

        if (player->flags & BTLOBJ_FLAG_IN_CARD_ACTION) {
            busy = 1;
        }

        if (busy) {
            break;
        }

        obj = ListPoolFirst(&gBtlWork->pool);

        while (obj != NULL) {
            if (obj->flags & BTLOBJ_FLAG_IN_CARD_ACTION) {
                busy = 1;
                break;
            }

            obj = ListPoolNext(&obj->node);
        }

        if (busy) {
            break;
        }

        count = GetStockMoveCount();
        gBtlWork->phaseStep = 0;

        if (gBtlWork->flags & BTL_FLAG_HUM_BATTLE) {
            if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
                if (gBtlWork->stockMove >= count) {
                    gBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;
                }

                if (gBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE) {
                    player->flags |= BTLOBJ_FLAG_CARD_ACTION_PENDING;
                } else {
                    EndCardPlay();
                }
            } else {
                if (gRikuBtlWork->stockMove >= count) {
                    gRikuBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;
                }

                if (gRikuBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE) {
                    gRikuBtlWork->actor->flags |= BTLOBJ_FLAG_CARD_ACTION_PENDING;
                } else {
                    EndCardPlay();
                }
            }
        } else {
            if (gBtlWork->stockMove >= count) {
                gBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;
            }

            if (gBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE) {
                player->flags |= BTLOBJ_FLAG_CARD_ACTION_PENDING;
            } else {
                EndCardPlay();
            }
        }

        break;
    }
    }
}

u32 ClampBattlePosition(s32* px, s32* py, s32 radiusX, s32 radiusY) {
    s16 rx = radiusX;
    s16 ry = radiusY;
    u8 r = 0;

    if (*py < (gBtlWork->yMin - ry) << 8) {
        *py = (gBtlWork->yMin - ry) << 8;
        r = 3;
    }

    if (*py > (gBtlWork->yMax + ry) << 8) {
        *py = (gBtlWork->yMax + ry) << 8;
        r = 4;
    }

    if (*px < (gBtlWork->xMin - rx) << 8) {
        *px = (gBtlWork->xMin - rx) << 8;
        r = 1;
    }

    if (*px > (gBtlWork->xMax + rx) << 8) {
        *px = (gBtlWork->xMax + rx) << 8;
        r = 2;
    }

    return r;
}

void SetBattleBounds(s32 xMin, s32 xMax, s32 yMin, s32 yMax) {
    u16 a = xMin;
    u16 b = xMax;
    u16 c = yMin;
    u16 d = yMax;

    gBtlWork->xMin = a;
    gBtlWork->xMax = b;
    gBtlWork->yMin = c;
    gBtlWork->yMax = d;
    SetGimmickTarget(((s16)a + (s16)b) << 7, ((s16)c + (s16)d) << 7, -0x2000);
}

s32 ApplyBtlObjHit(BtlObj* obj) {
    if (obj->flags & BTLOBJ_FLAG_WARP_PENDING) {
        obj->flags &= ~BTLOBJ_FLAG_WARP_PENDING;

        if (obj->hitFlags & ATTACK_FLAG_NO_DEATH_EFFECT) {
            obj->flags |= BTLOBJ_FLAG_NO_DEATH_FX;
        }

        return BTL_REACTION_WARPED;
    }

    if (obj->flags & BTLOBJ_FLAG_DAMAGE_PENDING) {
        obj->flags &= ~(BTLOBJ_FLAG_CARD_ACTION_PENDING | BTLOBJ_FLAG_DAMAGE_PENDING);
        obj->hp -= obj->damage;

        if (obj->hp < 0) {
            obj->hp = 0;
        }

        obj->flags &= ~BTLOBJ_FLAG_CARD_ACTION_PENDING;
        gBtlWork->hitStop = gBtlWork->pendingHitStop;
        obj->flags |= (BTLOBJ_FLAG_HIT_LOCKED | BTLOBJ_FLAG_CARD_USE_BLOCKED | BTLOBJ_FLAG_HURT);
        obj->hitFlashFrames = 0;

        if (obj->hp <= 0) {
            obj->flags |= BTLOBJ_FLAG_INTANGIBLE;
            obj->flags &= ~(BTLOBJ_FLAG_HEAL_PENDING | BTLOBJ_FLAG_STUN_PENDING);
            obj->flags |= BTLOBJ_FLAG_DEFEATED;
            obj->badStatus = BAD_STATUS_NONE;
            obj->badStatusTimer = 0;

            if (obj->hitFlags & ATTACK_FLAG_NO_DEATH_EFFECT) {
                obj->flags |= BTLOBJ_FLAG_NO_DEATH_FX;
            }

            if (obj->flags & BTLOBJ_FLAG_GRAVITY_PENDING) {
                obj->flags &= ~BTLOBJ_FLAG_GRAVITY_PENDING;
                return BTL_REACTION_GRAVITY_DEFEATED;
            }

            return BTL_REACTION_DEFEATED;
        }

        if (obj->kind != 55 && GetRandom() % 8 == 0) {
            DropFriendCard(obj->x, obj->y, obj->z - 0x7800);
        }

        if (obj->flags & BTLOBJ_FLAG_GRAVITY_PENDING) {
            obj->flags &= ~BTLOBJ_FLAG_GRAVITY_PENDING;
            obj->flags &= ~BTLOBJ_FLAGS_STATUS_PENDING;
            obj->badStatus = BAD_STATUS_NONE;
            obj->badStatusTimer = 0;
            return BTL_REACTION_GRAVITY;
        }

        if (obj->flags & BTLOBJ_FLAG_STUN_PENDING) {
            obj->flags &= ~BTLOBJ_FLAGS_STATUS_PENDING;

            if (obj->badStatus != BAD_STATUS_STUN) {
                obj->badStatus = BAD_STATUS_STUN;
                obj->badStatusTimer = 240;
            }

            return BTL_REACTION_STUNNED;
        }

        if (obj->flags & BTLOBJ_FLAG_TERROR_PENDING) {
            obj->flags &= ~BTLOBJ_FLAGS_STATUS_PENDING;
            obj->badStatus = BAD_STATUS_TERROR;
            obj->badStatusTimer = 300;
            return BTL_REACTION_TERRIFIED;
        }

        if (obj->flags & BTLOBJ_FLAG_CONFUSE_PENDING) {
            obj->flags &= ~BTLOBJ_FLAGS_STATUS_PENDING;
            obj->badStatus = BAD_STATUS_CONFUSE;
            obj->badStatusTimer = 300;
            return BTL_REACTION_HURT;
        }

        if (obj->flags & BTLOBJ_FLAG_BIND_PENDING) {
            obj->flags &= ~BTLOBJ_FLAGS_STATUS_PENDING;

            if (obj->badStatus != BAD_STATUS_BIND) {
                obj->badStatus = BAD_STATUS_BIND;
                obj->badStatusTimer = 600;
            }

            return BTL_REACTION_HURT;
        }

        obj->badStatus = BAD_STATUS_NONE;
        obj->badStatusTimer = 0;
        return BTL_REACTION_HURT;
    }

    if (obj->flags & BTLOBJ_FLAG_HEAL_PENDING) {
        obj->flags &= ~(BTLOBJ_FLAG_CARD_ACTION_PENDING | BTLOBJ_FLAG_HEAL_PENDING);
        obj->flags |= (BTLOBJ_FLAG_HIT_LOCKED | BTLOBJ_FLAG_CARD_USE_BLOCKED);
        return BTL_REACTION_HEALED;
    }

    if (obj->flags & BTLOBJ_FLAG_HAZARD_PENDING) {
        obj->flags &= ~BTLOBJ_FLAG_HAZARD_PENDING;

        if (obj->hp > 0) {
            ClearBtlObjActionFlags(obj);
            return BTL_REACTION_HAZARD;
        }

        return BTL_REACTION_NONE;
    }

    if (obj->flags & BTLOBJ_FLAG_STOP_PENDING) {
        obj->flags &= ~BTLOBJ_FLAGS_STATUS_PENDING;
        gBtlWork->hitStop = gBtlWork->pendingHitStop;
        ClearBtlObjActionFlags(obj);
        obj->flags |= BTLOBJ_FLAG_CARD_USE_BLOCKED;

        if (obj->badStatus != BAD_STATUS_STOP) {
            obj->badStatus = BAD_STATUS_STOP;
            obj->badStatusTimer = obj->damage;
        }

        return BTL_REACTION_STOPPED;
    }

    return BTL_REACTION_NONE;
}

u8 TryStartCardAction(BtlObj* obj) {
    u64 f = obj->flags;

    if (f & BTLOBJ_FLAG_CARD_ACTION_PENDING) {
        obj->flags &= ~(BTLOBJ_FLAG_CARD_ACTION_PENDING | BTLOBJ_FLAG_DAMAGE_PENDING | BTLOBJ_FLAG_HEAL_PENDING | BTLOBJ_FLAG_HURT | BTLOBJ_FLAG_STUN_PENDING | BTLOBJ_FLAG_GRAVITY_PENDING);
        obj->flags |= (BTLOBJ_FLAG_IN_CARD_ACTION | BTLOBJ_FLAG_HIT_LOCKED);
        obj->originX = obj->x;
        obj->originY = obj->y;
        obj->originZ = obj->z;
        return 1;
    }

    return 0;
}

s32 UpdateBtlObjReaction(BtlObj* obj) {
    u16 t;
    u16 u;
    u16 v;

    if (obj->badStatus == BAD_STATUS_STOP) {
        if (obj->flags & BTLOBJ_FLAG_DAMAGE_PENDING) {
            obj->flags &= ~(BTLOBJ_FLAG_DAMAGE_PENDING | BTLOBJ_FLAG_GRAVITY_PENDING);
            obj->flags &= ~BTLOBJ_FLAGS_STATUS_PENDING;
            gBtlWork->hitStop = gBtlWork->pendingHitStop;
            obj->invincibleTimer = 30;
            obj->delayedDamage += obj->damage;
        }
    } else {
        t = obj->delayedDamage;

        if ((s16)obj->delayedDamage > 0) {
            obj->damage = t;
            obj->delayedDamage = 0;
            gBtlWork->pendingHitStop = 0;
            obj->flags &= ~BTLOBJ_FLAGS_STATUS_PENDING;
            obj->flags |= BTLOBJ_FLAG_DAMAGE_PENDING;
            obj->hitFlags = 0;
            obj->knockbackSpeed = 0;
            obj->knockbackLift = 0;
        }
    }

    u = obj->invincibleTimer;

    if (obj->invincibleTimer > 0) {
        obj->invincibleTimer = u - 1;
    }

    v = obj->popCooldown;

    if (obj->popCooldown > 0) {
        obj->popCooldown = v - 1;
    }

    if (obj->flags & BTLOBJ_FLAG_CARD_BREAK_PENDING) {
        obj->flags &= ~(BTLOBJ_FLAG_CARD_ACTION_PENDING | BTLOBJ_FLAG_DAMAGE_PENDING | BTLOBJ_FLAG_CARD_BREAK_PENDING);
        ClearBtlObjActionFlags(obj);
        obj->flags |= BTLOBJ_FLAG_CARD_USE_BLOCKED;
        CreateBtlPopTask(obj, 9);
        gBtlWork->hitStop = 12;
        return BTL_REACTION_CARD_BROKEN;
    }

    if (TryStartCardAction(obj)) {
        return BTL_REACTION_CARD_ACTION;
    }

    return ApplyBtlObjHit(obj);
}

void ClearBtlObjActionFlags(BtlObj* obj) {
    obj->flags &= ~(BTLOBJ_FLAG_IN_CARD_ACTION | BTLOBJ_FLAG_HIT_LOCKED | BTLOBJ_FLAG_CARD_USE_BLOCKED | BTLOBJ_FLAG_HURT);
}

u16 GetBattleSpritePriorityFlags(s32 y) {
    if (y < gBtlWork->bossY + (gBtlWork->bossPriorityOffset << 8)) {
        return SPRITE_PRIORITY(2);
    }

    return SPRITE_PRIORITY(1);
}

void BeginBossDefeat(BtlObj* actor) {
    BtlObj* p;

    gBtlWork->flags |= BTL_FLAG_BOSS_DEFEATING;
    gBtlWork->flags |= BTL_FLAG_DISMISS_SUMMONS;
    gBtlWork->flags |= BTL_FLAG_BATTLE_OVER;
    SetEnemyJiminyFlag(actor);
    m4aMPlayFadeOut(gMPlayTable[gSongTable[3].ms].info, 12);
    FadeStartIn(FADE_MODE_ADD_WHITE, 20);
    FadeLock();
    p = ListPoolFirst(&gBtlWork->pool);

    while (p != NULL) {
        p->node.flags |= LIST_NODE_FLAG_SKIP;
        p = ListPoolNext(&p->node);
    }

    gBtlWork->enemyCount = 0;
}

void EndBossDefeat() {
    gBtlWork->flags &= ~BTL_FLAG_BOSS_DEFEATING;
}

void SetEnemyKindFlags(BtlObj* obj) {
    switch (obj->kind) {
    case 1:
        obj->flags |= (BTLOBJ_FLAG_ABSORB_FIRE | BTLOBJ_FLAG_WEAK_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER);
        break;
    case 2:
        obj->flags |= (BTLOBJ_FLAG_ABSORB_BLIZZARD | BTLOBJ_FLAG_WEAK_FIRE | BTLOBJ_FLAG_RESIST_THUNDER);
        break;
    case 3:
        obj->flags |= BTLOBJ_FLAG_ABSORB_THUNDER;
        break;
    case 4:
        obj->flags |= (BTLOBJ_FLAG_ABSORB_FIRE | BTLOBJ_FLAG_ABSORB_BLIZZARD | BTLOBJ_FLAG_ABSORB_THUNDER);
        break;
    case 5:
        obj->flags |= BTLOBJ_FLAG_WEAK_THUNDER;
        break;
    case 7:
        obj->flags |= (BTLOBJ_FLAG_IMMUNE_TERROR | BTLOBJ_FLAG_IMMUNE_WARP | BTLOBJ_FLAG_IMMUNE_CONFUSE | BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_PHYSICAL);
        break;
    case 16:
        obj->flags |= BTLOBJ_FLAG_ABSORB_THUNDER;
        break;
    case 23:
        obj->flags |= (BTLOBJ_FLAG_ABSORB_FIRE | BTLOBJ_FLAG_ABSORB_BLIZZARD | BTLOBJ_FLAG_ABSORB_THUNDER | BTLOBJ_FLAG_IMMUNE_STOP | BTLOBJ_FLAG_IMMUNE_GRAVITY);
        break;
    case 27:
        obj->flags |= BTLOBJ_FLAG_ABSORB_THUNDER;
        break;
    case 32:
        obj->flags |= (BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 33:
        obj->flags |= (BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 34:
        obj->flags |= (BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 35:
        obj->flags |= (BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 36:
        obj->flags |= (BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 37:
        obj->flags |= (BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 38:
        obj->flags |= (BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 39:
        obj->flags |= (BTLOBJ_FLAG_WEAK_PHYSICAL | BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 40:
        obj->flags |= (BTLOBJ_FLAG_WEAK_PHYSICAL | BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 42:
        obj->flags |= (BTLOBJ_FLAG_IMMUNE_THUNDER | BTLOBJ_FLAG_IMMUNE_STOP | BTLOBJ_FLAG_IMMUNE_GRAVITY | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 43:
        obj->flags |= (BTLOBJ_FLAG_IMMUNE_STOP | BTLOBJ_FLAG_IMMUNE_GRAVITY | BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 44:
        obj->flags |= (BTLOBJ_FLAG_ABSORB_FIRE | BTLOBJ_FLAG_IMMUNE_THUNDER | BTLOBJ_FLAG_IMMUNE_STOP | BTLOBJ_FLAG_IMMUNE_GRAVITY | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 45:
        obj->flags |= (BTLOBJ_FLAG_IMMUNE_STOP | BTLOBJ_FLAG_IMMUNE_GRAVITY | BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER);
        break;
    case 46:
        obj->flags |= BTLOBJ_FLAG_WEAK_FIRE;
        break;
    case 47:
        obj->flags |= BTLOBJ_FLAG_WEAK_FIRE;
        break;
    case 48:
        obj->flags |= (BTLOBJ_FLAG_ABSORB_FIRE | BTLOBJ_FLAG_IMMUNE_STOP | BTLOBJ_FLAG_IMMUNE_GRAVITY | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 49:
        obj->flags |= (BTLOBJ_FLAG_ABSORB_THUNDER | BTLOBJ_FLAG_IMMUNE_STOP | BTLOBJ_FLAG_IMMUNE_GRAVITY | BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD);
        break;
    case 50:
        obj->flags |= (BTLOBJ_FLAG_ABSORB_BLIZZARD | BTLOBJ_FLAG_IMMUNE_STOP | BTLOBJ_FLAG_IMMUNE_GRAVITY | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 51:
        obj->flags |= (BTLOBJ_FLAG_IMMUNE_STOP | BTLOBJ_FLAG_IMMUNE_GRAVITY | BTLOBJ_FLAG_WEAK_PHYSICAL | BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 52:
        obj->flags |= (BTLOBJ_FLAG_IMMUNE_STOP | BTLOBJ_FLAG_IMMUNE_GRAVITY | BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_NEUTRAL);
        break;
    case 53:
        obj->flags |= (BTLOBJ_FLAG_IMMUNE_BLIZZARD | BTLOBJ_FLAG_IMMUNE_STOP | BTLOBJ_FLAG_IMMUNE_GRAVITY | BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_PHYSICAL);
        break;
    case 0:
    default:
        break;
    }
}

void InitEnemyBtlObj(BtlObj* obj, const EmyKind* kind, s32 x, s32 y, s32 z) {
    const EnemyBaseStats* e;
    enum EmyId {
        EMY_ID_32 = 32,
        EMY_ID_33 = 33,
        EMY_ID_34 = 34,
        EMY_ID_35 = 35,
        EMY_ID_36 = 36,
        EMY_ID_37 = 37,
        EMY_ID_38 = 38,
        EMY_ID_39 = 39,
        EMY_ID_40 = 40,
        EMY_ID_45 = 45,
        EMY_ID_48 = 48,
        EMY_ID_49 = 49,
        EMY_ID_50 = 50,
        EMY_ID_51 = 51,
        EMY_ID_52 = 52,
        EMY_ID_53 = 53
    } v;
    s32 a;
    s32 b;
    s32 c;

    e = GetEnemyBaseStats(kind->id);

    if (e != NULL) {
        v = kind->id;

        switch (v) {
        case EMY_ID_45:
        case EMY_ID_48:
        case EMY_ID_49:
        case EMY_ID_50:
        case EMY_ID_51:
        case EMY_ID_52:
        case EMY_ID_53:
            switch (gBtlWork->battleId) {
            case 161:
                obj->maxHp = 1120;
                obj->attack = 5;
                obj->exp = 2775;
                break;
            case 168:
                obj->maxHp = 1120;
                obj->attack = 5;
                obj->exp = 3225;
                break;
            case 169:
                obj->maxHp = 1120;
                obj->attack = 8;
                obj->exp = 5700;
                break;
            case 170:
                obj->maxHp = 1680;
                obj->attack = 10;
                obj->exp = 6825;
                break;
            case 171:
                obj->maxHp = 1120;
                obj->attack = 5;
                obj->exp = 1875;
                break;
            case 172:
                obj->maxHp = 1680;
                obj->attack = 10;
                obj->exp = 5700;
                break;
            case 162:
                obj->maxHp = 320;
                obj->attack = 2;
                obj->exp = 75;
                break;
            case 173:
                obj->maxHp = 1680;
                obj->attack = 15;
                obj->exp = 6825;
                break;
            case 163:
                obj->maxHp = 1120;
                obj->attack = 5;
                obj->exp = 2325;
                break;
            case 174:
                obj->maxHp = 1680;
                obj->attack = 15;
                obj->exp = 6263;
                break;
            case 164:
                obj->maxHp = 1120;
                obj->attack = 15;
                obj->exp = 4125;
                break;
            case 175:
                obj->maxHp = 1120;
                obj->attack = 20;
                obj->exp = 5700;
                break;
            case 176:
                obj->maxHp = 1120;
                obj->attack = 3;
                obj->exp = 975;
                break;
            case 166:
                obj->maxHp = 400;
                obj->attack = 3;
                obj->exp = 133;
                break;
            case 177:
                obj->maxHp = 2240;
                obj->attack = 25;
                obj->exp = 0;
                break;
            case 167:
                obj->maxHp = 1680;
                obj->attack = 15;
                obj->exp = 6517;
                break;
            default:
                obj->maxHp = 2240;
                obj->attack = 27;
                obj->exp = 13131;
                break;
            }

            break;
        case EMY_ID_37:
            if (gGameState.flags & GAME_FLAG_RIKU) {
                obj->maxHp = 300;
                obj->attack = 4;
                obj->exp = 150;
                break;
            }
        default:
            if (gGameState.floor <= 9) {
                a = 25;
                b = 102;
                c = 384;
            } else {
                a = 51;
                b = 76;
                c = 640;
            }

            obj->maxHp = ((gGameState.floor * a + 256) * e->hp) >> 8;
            obj->attack = ((gGameState.floor * b + 256) * e->attack) >> 8;
            obj->exp = ((c * gGameState.floor + 256) * (u16)e->exp) >> 8;
            break;
        }
    } else {
        obj->maxHp = kind->maxHp;
        obj->attack = 0;
        obj->exp = 1;
        v = kind->id;
    }

    obj->attackOffset = 80;
    obj->attackRangeX = 32;
    obj->attackRangeY = 32;
    obj->cardInterval = 100;
    obj->hp = obj->maxHp;
    obj->self = obj;
    obj->x = x;
    obj->y = y;
    obj->z = z;
    obj->groundZ = 0;
    obj->flags = 0;
    obj->kindFlags = kind->flags;
    obj->height = kind->height;
    obj->centerHeight = kind->centerHeight;
    obj->centerOffsetX = 0;
    obj->radiusX = kind->radius;
    obj->radiusY = kind->radius >> 1;
    obj->kind = v;
    obj->damage = 0;
    obj->floorZ = 0;
    obj->parent = NULL;
    obj->invincibleTimer = 0;
    obj->delayedDamage = 0;
    obj->shadowPriority = 0xFFF1;
    obj->btl = NULL;
    obj->badStatus = BAD_STATUS_NONE;
    obj->badStatusTimer = 0;
    obj->confuseTargetX = gBtlWork->actor->x;
    obj->confuseTargetY = gBtlWork->actor->y;
    obj->confuseTargetZ = gBtlWork->actor->z;
    obj->vx = 0;
    obj->vy = 0;
    obj->popCooldown = 0;

    switch (v) {
    case EMY_ID_32:
    case EMY_ID_33:
    case EMY_ID_34:
    case EMY_ID_35:
    case EMY_ID_36:
    case EMY_ID_37:
    case EMY_ID_38:
    case EMY_ID_39:
    case EMY_ID_40:
        if (!(kind->flags & EMY_KIND_FLAG_NO_COLLIDER)) {
            ColliderInit(&obj->collider, 8, kind->radius, kind->height);
        }

        obj->flags |= (BTLOBJ_FLAG_IMMUNE_STOP | BTLOBJ_FLAG_IMMUNE_GRAVITY | BTLOBJ_FLAG_IMMUNE_TERROR | BTLOBJ_FLAG_IMMUNE_WARP | BTLOBJ_FLAG_IMMUNE_CONFUSE | BTLOBJ_FLAG_IMMUNE_BIND);
        obj->flags |= BTLOBJ_FLAG_BOSS;
        break;
    default:
        if (!(kind->flags & EMY_KIND_FLAG_NO_COLLIDER)) {
            if (kind->flags & EMY_KIND_FLAG_NO_ENEMY_COLLISION) {
                ColliderInit(&obj->collider, 11, kind->radius, kind->height);
            } else {
                ColliderInit(&obj->collider, 3, kind->radius, kind->height);
            }
        }
    }

    SetEnemyKindFlags(obj);

    if (kind->flags & EMY_KIND_FLAG_LARGE_BODY) {
        obj->flags |= BTLOBJ_FLAG_LARGE_SHADOW;
    }

    ListNodeInit(&obj->node, &gBtlWork->pool, obj);
    ListPoolAppend(&obj->node, &gBtlWork->pool);
    gBtlWork->enemyCount++;
}

void ReleaseEnemyBtlObj(BtlObj* obj) {
    BtlObj* p = obj->self;

    if (p == obj) {
        ListPoolRemove(&p->node, &gBtlWork->pool);

        if (!(p->kindFlags & EMY_KIND_FLAG_NO_COLLIDER)) {
            ColliderUnregister(&p->collider);
        }

        gBtlWork->enemyCount--;
    }
}

u8 CreateBtlPrizeTasksCapped(BtlPrizeSrc* src, u16 kind, s16 value, s16* remaining, s16* cnt) {
    s16 i;
    s16 lim;

    lim = *remaining / value;
    src->kind = kind;

    for (i = 0; i < lim; i++) {
        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPrize, src);

        if (++(*cnt) > 2) {
            return 1;
        }
    }

    *remaining = *remaining % value;
    return 0;
}

void CreateBtlPrizeTasks(BtlPrizeSrc* src, u16 kind, s16 value, s16* remaining) {
    s16 i;
    s16 lim;
    lim = *remaining / value;
    src->kind = kind;

    for (i = 0; i < lim; i++) {
        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPrize, src);
    }

    *remaining = *remaining % value;
}

void DropBossPrizes(BtlObj* obj) {
    BtlPrizeSrc a;
    s16 n;
    a.x = obj->x;
    a.y = obj->y;
    a.z = obj->z;
    a.noTimeout = 1;
    n = obj->exp;
    CreateBtlPrizeTasks(&a, 0, 0x578, &n);
    CreateBtlPrizeTasks(&a, 8, 199, &n);
    CreateBtlPrizeTasks(&a, 5, 60, &n);
    CreateBtlPrizeTasks(&a, 7, 30, &n);
    CreateBtlPrizeTasks(&a, 4, 10, &n);
    CreateBtlPrizeTasks(&a, 6, 5, &n);
    CreateBtlPrizeTasks(&a, 3, 1, &n);
}

void DropEnemyPrizes(BtlObj* obj) {
    BtlPrizeSrc a;
    BtlPrizeSrc b;
    s16 n;
    s16 cnt;
    s32 flag;
    s32 hit;
    s32 v;
    s32 r;

    if (gBtlWork->flags & BTL_FLAG_NO_ENEMY_DROPS) {
        return;
    }

    a.x = obj->x;
    a.y = obj->y;
    a.z = obj->z;
    a.noTimeout = 0;
    n = obj->exp;
    cnt = 0;

    if (gBtlWork->enemyCount == 1 && gBtlWork->pendingEnemies <= 0) {
        if (CountRegularMapCards() <= 4) {
            flag = 0;
        } else {
            switch (obj->kind) {
            case 10:
            case 15:
            case 25:
            case 26:
            case 27:
            case 31:
                v = 2;
                break;
            case 0:
            case 5:
            case 6:
            case 9:
            case 11:
            case 14:
            case 16:
            case 18:
            case 20:
            case 21:
            case 22:
            case 28:
            case 29:
                v = 4;
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            case 7:
            case 12:
            case 13:
            case 17:
            case 19:
            case 23:
            case 24:
            case 30:
                v = 3;
                break;
            default:
                v = 0;
                break;
            }

            if (v > 99) {
                flag = 1;
            } else if (v == 0) {
                flag = 0;
            } else {
                if (gGameState.roomEffect == 1 || gGameState.roomEffect == 10) {
                    v = (v * 5 * 128) >> 8;
                }

                v = 100 / v;
                r = GetRandom();
                hit = 0;

                if ((u16)r % v == 0) {
                    hit = 1;
                }

                flag = hit;
            }
        }

        if (gGameState.flags & GAME_FLAG_RIKU) {
            flag = 0;
        }

        if (gBtlWork->battleId != 120 && gBtlWork->battleId != 124) {
            if (flag) {
                CreateHeartlessCardTask(&gBtlWork->taskPools[0], obj->x >> 8, obj->y >> 8, obj->z >> 8, obj->kind);
            } else {
                b.x = obj->x;
                b.y = obj->y;
                b.z = obj->z;
                CreatePrizeCardTask(&gBtlWork->taskPools[0], &b);
            }
        }
    }

    if (CreateBtlPrizeTasksCapped(&a, 0, 0x578, &n, &cnt)) {
        return;
    }

    if (CreateBtlPrizeTasksCapped(&a, 8, 199, &n, &cnt)) {
        return;
    }

    if (CreateBtlPrizeTasksCapped(&a, 5, 60, &n, &cnt)) {
        return;
    }

    if (CreateBtlPrizeTasksCapped(&a, 7, 30, &n, &cnt)) {
        return;
    }

    if (CreateBtlPrizeTasksCapped(&a, 4, 10, &n, &cnt)) {
        return;
    }

    if (CreateBtlPrizeTasksCapped(&a, 6, 5, &n, &cnt)) {
        return;
    }

    CreateBtlPrizeTasksCapped(&a, 3, 1, &n, &cnt);
}

void TryDropPremireCard(BtlObj* obj) {
    BtlPrizeSrc a;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        return;
    }

    if (IsActiveDeckAllPremium()) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_NO_ENEMY_DROPS) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_PREMIRE_DROPPED) {
        return;
    }

    if (!HasNonPremiumCardsInActiveDeck()) {
        return;
    }

    if (GetDeckCardCount(GetActiveDeckIndex()) <= 9) {
        return;
    }

    gBtlWork->flags |= BTL_FLAG_PREMIRE_DROPPED;
    a.x = obj->x;
    a.y = obj->y;
    a.z = obj->z;
    a.noTimeout = 0;
    TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPremire, &a);
}

u8 IsPlayerOnPlatform(Collider* platform) {
    if (platform == gBtlWork->platform) {
        return 1;
    } else {
        return 0;
    }
}

void SetBattleActorPosition(s32 x, s32 y, s32 z) {
    gBtlWork->actor->x = x;
    gBtlWork->actor->y = y;
    gBtlWork->actor->z = z;
}

void RequestEnemyCardUse(BtlObj* obj) {
    if (!(obj->flags & BTLOBJ_FLAGS_NO_CARD_USE)) {
        gBtlWork->actor4 = obj;
    }
}

void TryEnemyCardUse(BtlObj* obj) {
    s32 x;
    s32 y;
    s32 cx;
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;

    if (obj->flags & BTLOBJ_FLAGS_NO_CARD_USE) {
        return;
    }

    if (GetRandom() % (obj->cardInterval * gBtlWork->enemyCount) != 0) {
        return;
    }

    GetEnemyTargetPosition(obj, &x, &y, NULL);

    if (obj->attackRangeX == 0) {
        gBtlWork->actor4 = obj;
        return;
    }

    if (obj->flags & BTLOBJ_FLAG_FACING_LEFT) {
        cx = obj->x - ((s16)(x1 = obj->attackOffset) * 256);
        x1 = obj->attackRangeX;
    } else {
        x1 = obj->attackOffset;
        cx = obj->x + (s16)x1 * 256;
        x1 = obj->attackRangeX;
    }

    x1 -= 4;
    x0 = cx - (x1 *= 256);
    y0 = obj->y - (obj->attackRangeY * 256);
    x1 = x0 + ((obj->attackRangeX + 4) * 512);
    y1 = y0 + ((obj->attackRangeY + 4) * 512);

    if (x0 > x) {
        return;
    }

    if (x1 < x) {
        return;
    }

    if (y0 > y) {
        return;
    }

    if (y1 < y) {
        return;
    }

    gBtlWork->actor4 = obj;
}

void SetBtlObjParent(BtlObj* obj, BtlObj* parent) {
    obj->parent = parent;
}

u8 SpawnEnemy(s32 id, s32 x, s32 y, s32 z) {
    EnemySpawnRequest s;
    s32 born;

    born = 1;
    s.flags = 0;

    switch (id) {
    case 0:
        s.desc = &gTaskDescEmy00;
        born = 0;
        break;
    case 1:
        s.desc = &gTaskDescEmy01;
        break;
    case 2:
        s.desc = &gTaskDescEmy02;
        break;
    case 3:
        s.desc = &gTaskDescEmy03;
        break;
    case 4:
        s.desc = &gTaskDescEmy04;
        break;
    case 5:
        s.desc = &gTaskDescEmy06;
        break;
    case 6:
        s.desc = &gTaskDescEmy07;
        break;
    case 7:
        s.desc = &gTaskDescEmy08;
        break;
    case 9:
        s.desc = &gTaskDescEmy14;
        break;
    case 10:
        s.desc = &gTaskDescEmy15;
        break;
    case 11:
        s.desc = &gTaskDescEmy16;
        break;
    case 12:
        s.desc = &gTaskDescEmy18;
        break;
    case 13:
        s.desc = &gTaskDescEmy19;
        break;
    case 14:
        s.desc = &gTaskDescEmy21;
        break;
    case 15:
        s.desc = &gTaskDescEmy22;
        break;
    case 16:
        s.desc = &gTaskDescEmy23;
        break;
    case 17:
        s.desc = &gTaskDescEmy25;
        break;
    case 18:
        s.desc = &gTaskDescEmy26;
        s.flags |= SPAWN_FLAG_LARGE_EFFECT;
        break;
    case 19:
        s.desc = &gTaskDescEmy27;
        break;
    case 20:
        s.desc = &gTaskDescEmy28;
        s.flags |= SPAWN_FLAG_LARGE_EFFECT;
        break;
    case 21:
        s.desc = &gTaskDescEmy29;
        s.flags |= SPAWN_FLAG_LARGE_EFFECT;
        break;
    case 22:
        s.desc = &gTaskDescEmy30;
        s.flags |= SPAWN_FLAG_LARGE_EFFECT;
        break;
    case 23:
        s.desc = &gTaskDescEmy31;
        s.flags |= SPAWN_FLAG_LARGE_EFFECT;
        break;
    case 24:
        s.desc = &gTaskDescEmy37;
        born = 0;
        break;
    case 25:
        s.desc = &gTaskDescEmy38;
        s.flags |= SPAWN_FLAG_LARGE_EFFECT;
        break;
    case 26:
        s.desc = &gTaskDescEmy39;
        s.flags |= SPAWN_FLAG_LARGE_EFFECT;
        break;
    case 27:
        s.desc = &gTaskDescEmy41;
        s.flags |= SPAWN_FLAG_LARGE_EFFECT;
        break;
    case 28:
        s.desc = &gTaskDescEmy44;
        s.flags |= SPAWN_FLAG_LARGE_EFFECT;
        break;
    case 29:
        s.desc = &gTaskDescEmy81;
        break;
    case 30:
        s.desc = &gTaskDescEmy82;
        break;
    case 31:
        s.desc = &gTaskDescEmy83;
        break;
    case 47:
        s.desc = &gTaskDescEmyTrumpH;
        born = 0;
        break;
    case 46:
        s.desc = &gTaskDescEmyTrumpS;
        born = 0;
        break;
    default:
        s.desc = &gTaskDescEmy00;
        break;
    }

    s.x = x;
    s.y = y;
    s.z = z;
    s.tileCount = gEnemyTileCounts[id];

    if (born) {
        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlBorn, &s);
    } else {
        if (!CanAllocObjTiles(s.tileCount) || !CanAllocObjPalette(1)) {
            gBtlWork->pendingEnemies--;
            return 0;
        }

        TaskCreate(&gBtlWork->taskPools[0], s.desc, &s.x);
    }

    return 1;
}

void AllocBattleTiles() {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        gBtlWork->tiles = AllocObjTiles(0x840, NULL);
    } else {
        gBtlWork->tiles = AllocObjTiles(0xC80, NULL);
        gBtlWork->tiles2 = AllocObjTiles(0xA00, NULL);

        if (gBtlWork->flags & BTL_FLAG_VS_BATTLE) {
            gRikuBtlWork->tiles = AllocObjTiles(0xC80, NULL);
        }
    }

    gBtlWork->flags |= BTL_FLAG_TILES_ALLOCATED;
}

void ReleaseBattleTiles() {
    if (gBtlWork->flags & BTL_FLAG_TILES_ALLOCATED) {
        if (gGameState.flags & GAME_FLAG_RIKU) {
            ReleaseObjTiles(gBtlWork->tiles);
        } else {
            ReleaseObjTiles(gBtlWork->tiles);
            ReleaseObjTiles(gBtlWork->tiles2);

            if (gBtlWork->flags & BTL_FLAG_VS_BATTLE) {
                ReleaseObjTiles(gRikuBtlWork->tiles);
            }
        }

        gBtlWork->flags &= ~BTL_FLAG_TILES_ALLOCATED;
    }
}

void SetGimmickFlag(u8 index) {
    if (index <= 4) {
        gBtlWork->gimmickFlags |= 1 << index;
    }
}

u8 ConsumeGimmickFlag(u8 index) {
    u8 m;

    if (index > 4) {
        return 0;
    }

    m = 1 << index;

    if (gBtlWork->gimmickFlags & m) {
        gBtlWork->gimmickFlags &= ~m;
        return 1;
    }

    return 0;
}

void DropGimmickCard(u8 index, s32 x, s32 y, s32 z) {
    u16 id;

    switch (index) {
    case 0:
        id = 0x28F;
        break;
    case 1:
        id = 0x290;
        break;
    case 2:
        id = 0x291;
        break;
    case 3:
        id = 0x292;
        break;
    case 4:
        id = 0x293;
        break;
    default:
        return;
    }

    CreateGimmickCardTask(&gBtlWork->taskPools[0], x >> 8, y >> 8, z >> 8, id);
}

void SetGimmickTarget(s32 x, s32 y, s32 z) {
    gBtlWork->gimmickX = x;
    gBtlWork->gimmickY = y;
    gBtlWork->gimmickZ = z;
}

void SetBtlPaletteFadeExcluded(u8 index, u8 on) {
    if (index <= 0x1F) {
        if (on) {
            gBtlWork->fadeExcludedPalettes |= 1 << index;
        } else {
            gBtlWork->fadeExcludedPalettes &= ~(1 << index);
        }
    }
}

void SetBtlObjUnhittable(BtlObj* obj, u8 on) {
    if (on) {
        obj->flags |= BTLOBJ_FLAG_UNHITTABLE;
    } else {
        obj->flags &= ~BTLOBJ_FLAG_UNHITTABLE;
    }
}

void ExitBattle() {
    m4aMPlayAllStop();

    if (gDebugFlags & DEBUG_FLAG_CHKBTL) {
        ModeRequest(&gModeChkbtl, 0);
        return;
    }

    if (gGameState.flags & GAME_FLAG_RIKU) {
        switch (gBtlWork->battleId) {
        case 166:
#ifdef VERSION_EU
            RequestEventMode(154);
#else
            RequestEventMode(156);
#endif
            return;
        case 176:
#ifdef VERSION_EU
            RequestEventMode(159);
#else
            RequestEventMode(161);
#endif
            return;
        case 171:
#ifdef VERSION_EU
            RequestEventMode(162);
#else
            RequestEventMode(164);
#endif
            return;
        case 167:
#ifdef VERSION_EU
            RequestEventMode(170);
#else
            RequestEventMode(172);
#endif
            return;
        case 154:
#ifdef VERSION_EU
            RequestEventMode(179);
#else
            RequestEventMode(181);
#endif
            return;
        case 172:
#ifdef VERSION_EU
            RequestEventMode(186);
#else
            RequestEventMode(188);
#endif
            return;
        case 177:
            gGameState.flags |= GAME_FLAG_RIKU_CLEAR;
            SaveWriteHeader(-1);
#ifdef VERSION_EU
            RequestEventMode(192);
#else
            RequestEventMode(194);
#endif
            return;
        default:
            if (gBtlWork->flags & BTL_FLAG_BOSS_BATTLE) {
                AdvanceFloorStory();
                RequestMapMode();
            } else if (gBtlWork->flags & BTL_FLAG_HUM_BATTLE) {
                AdvanceFloorStory();
                RequestMapMode();
            } else {
                RequestMapMode();
            }

            return;
        }
    } else {
        switch (gBtlWork->battleId) {
        case 120:
            RequestEventMode(96);
            return;
        case 121:
            if (gBtlWork->flags & BTL_FLAG_ESCAPED) {
                RequestEventMode(84);
            } else if (gBtlWork->flags & 0x100000) {
                RequestEventMode(82);
            } else {
                RequestEventMode(83);
            }

            return;
        case 122:
            RequestEventMode(88);
            return;
        case 123:
            RequestEventMode(108);
            return;
        case 124:
            RequestEventMode(111);
            return;
        case 148:
            RequestEventMode(9);
            return;
        case 149:
            RequestEventMode(114);
            return;
        case 150:
            RequestEventMode(100);
            return;
        case 151:
            RequestEventMode(106);
            return;
        case 152:
            RequestEventMode(78);
            return;
        case 153:
#ifdef VERSION_EU
            RequestEventMode(131);
#else
            RequestEventMode(133);
#endif
            return;
        case 154:
            RequestEventMode(56);
            return;
        case 155:
            RequestEventMode(93);
            return;
        case 156:
            gGameState.flags |= GAME_FLAG_SORA_CLEAR;
            SaveWriteHeader(-1);
            RequestEventMode(71);
            return;
        case 157:
            RequestEventMode(6);
            return;
        case 158:
            RequestEventMode(119);
            return;
        case 159:
            RequestEventMode(123);
            return;
        case 160:
            RequestEventMode(126);
            return;
        case 161:
            RequestEventMode(31);
            return;
        case 162:
            RequestEventMode(11);
            return;
        case 163:
            RequestEventMode(27);
            return;
        case 164:
            RequestEventMode(41);
            return;
        case 165:
            RequestEventMode(67);
            return;
        case 168:
            RequestEventMode(34);
            return;
        case 169:
            RequestEventMode(49);
            return;
        case 173:
            RequestEventMode(65);
            return;
        case 174:
            RequestEventMode(60);
            return;
        case 175:
            RequestEventMode(46);
            return;
        case 178:
            RequestEventMode(3);
            return;
        case 179:
            RequestEventMode(5);
            return;
        case 170:
            AdvanceFloorStory();
            RequestMapMode();
            return;
        default:
            if (gBtlWork->flags & BTL_FLAG_BOSS_BATTLE) {
                AdvanceFloorStory();
                RequestMapMode();
            } else if (gBtlWork->flags & BTL_FLAG_HUM_BATTLE) {
                AdvanceFloorStory();
                RequestMapMode();
            } else {
                RequestMapMode();
            }

            return;
        }
    }
}

u8 ApplyBattleBounds(s32* x, s32* y, s32* z, s32* floor) {
    if (gBtlWork->boundsCallback != NULL) {
        return gBtlWork->boundsCallback(x, y, z, floor);
    }

    return 0;
}

void GetEnemyTargetPosition(BtlObj* obj, s32* x, s32* y, s32* z) {
    u16 n;

    if (obj->badStatus == BAD_STATUS_CONFUSE) {
        if (x != NULL) {
            *x = obj->confuseTargetX;
        }

        if (y != NULL) {
            *y = obj->confuseTargetY;
        }

        if (z != NULL) {
            *z = obj->confuseTargetZ;
        }

        n = GetRandom() % 6;

        if (n == 0) {
            if (x != NULL) {
                *x = (gBtlWork->xMin + GetRandom() % (gBtlWork->xMax - gBtlWork->xMin + 1)) << 8;
            }

            if (y != NULL) {
                *y = (gBtlWork->yMin + GetRandom() % (gBtlWork->yMax - gBtlWork->yMin + 1)) << 8;
            }

            if (z != NULL) {
                *z = n;
            }
        }
    } else {
        if (x != NULL) {
            *x = gBtlWork->targetX;
        }

        if (y != NULL) {
            *y = gBtlWork->targetY;
        }

        if (z != NULL) {
            *z = gBtlWork->targetZ;
        }
    }
}

void SetEnemyHpFromStats(BtlObj* obj, s32 id, s32 hpScale) {
    u16 b = id;
    const EnemyBaseStats* e = GetEnemyBaseStats(b);

    if (e != NULL) {
        obj->maxHp = (e->hp * hpScale) >> 8;

        if (obj->maxHp <= 0) {
            obj->maxHp = 1;
        }

        obj->hp = obj->maxHp;
    }
}

void SetEnemyJiminyFlag(BtlObj* obj) {
    switch (obj->kind) {
    case 0:
        SetJiminyFlag(84);
        break;
    case 1:
        SetJiminyFlag(87);
        break;
    case 2:
        SetJiminyFlag(88);
        break;
    case 3:
        SetJiminyFlag(89);
        break;
    case 4:
        SetJiminyFlag(90);
        break;
    case 5:
        SetJiminyFlag(98);
        break;
    case 6:
        SetJiminyFlag(110);
        break;
    case 7:
        SetJiminyFlag(111);
        break;
    case 9:
        SetJiminyFlag(85);
        break;
    case 10:
        SetJiminyFlag(91);
        break;
    case 11:
        SetJiminyFlag(92);
        break;
    case 12:
        SetJiminyFlag(93);
        break;
    case 13:
        SetJiminyFlag(94);
        break;
    case 14:
        SetJiminyFlag(96);
        break;
    case 15:
        SetJiminyFlag(97);
        break;
    case 16:
        SetJiminyFlag(99);
        break;
    case 17:
        SetJiminyFlag(101);
        break;
    case 18:
        SetJiminyFlag(102);
        break;
    case 19:
        SetJiminyFlag(103);
        break;
    case 20:
        SetJiminyFlag(104);
        break;
    case 21:
        SetJiminyFlag(105);
        break;
    case 22:
        SetJiminyFlag(107);
        break;
    case 23:
        SetJiminyFlag(108);
        break;
    case 24:
        SetJiminyFlag(109);
        break;
    case 25:
        SetJiminyFlag(86);
        break;
    case 26:
        SetJiminyFlag(95);
        break;
    case 27:
        SetJiminyFlag(100);
        break;
    case 28:
        SetJiminyFlag(106);
        break;
    case 29:
        SetJiminyFlag(113);
        break;
    case 30:
        SetJiminyFlag(114);
        break;
    case 31:
        SetJiminyFlag(112);
        break;
    case 32:
        SetJiminyFlag(115);
        break;
    case 34:
        SetJiminyFlag(117);
        break;
    case 36:
        SetJiminyFlag(116);
        break;
    case 38:
        SetJiminyFlag(118);
        break;
    }
}

u8 StepHitFlash(BtlObj* obj) {
    if (gBtlWork->paused == 1) {
        return 0;
    }

    if (!(obj->flags & BTLOBJ_FLAG_HURT)) {
        return 0;
    }

    if (obj->hitFlashFrames > 0x17) {
        return 0;
    }

    obj->hitFlashFrames++;

    if (obj->hitFlashFrames & 1) {
        return 1;
    }

    return 0;
}

u8 StepHitFlashSolid(BtlObj* obj) {
    if (gBtlWork->paused == 1) {
        return 0;
    }

    if (!(obj->flags & BTLOBJ_FLAG_HURT)) {
        return 0;
    }

    if (obj->hitFlashFrames > 0x17) {
        return 0;
    }

    obj->hitFlashFrames++;
    return 1;
}
