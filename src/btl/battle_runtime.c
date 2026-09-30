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
#include "card_deck.h"
#include "player_progression.h"
#include <stdlib.h>
#include "enemy_tile_counts.h"
#include <string.h>

s32 gUnk_02039DC0 EWRAM_COMMON(4);
s32* gLockonDoorPosition EWRAM_COMMON(4);

void SetBattleZoom(u16 a, s32 b, s32 c, s32 d) {
    gBtlWork->zoomScale = b;
    gBtlWork->zoomSteps = a;
    gBtlWork->zoomX = c;
    gBtlWork->zoomY = d;
}

void AnimChangeWithDef(const AnimDef* tbl, void* a, u16 i, u16 j, void* obj) {
    const AnimDef* e = &tbl[i];
    AnimChangeWithTables(a, e->animId, j, e->anims, e->gfxTable);
    SetObjTileSource(obj, e->tiles);
}

void WorldToScreen(s16* a, s16* b, s32 px, s32 py, s32 pz) {
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
        *a = x + 120;
        *b = y + 80;
    } else {
        ang = -gBtlWork->rotation;
        sine = gSineTable;
        c = ang + 64;
        idx = c & 255;
        u = sine[idx] * x;
        v = sine[idx += 64] * x;
        u += sine[ang] * y;
        v += sine[c] * y;
        *a = (u >> 8) + 120;
        *b = (v >> 8) + 80;
    }
}
void CreateBtlPopTask(BtlObj* p, s16 b) {
    BtlPrizeSrc a;
    s16* t;

    if (b != 9) {
        if (p->parent != NULL) {
            t = &p->parent->popCooldown;
        } else {
            t = &p->popCooldown;
        }

        if (*t > 0) {
            return;
        }
        *t = 50;
    }
    a.x = p->x;
    a.y = p->y;
    a.z = p->z - ((p->height / 2) << 8);
    if (gGameState.flags & GAME_FLAG_RIKU) {
        if (b == 9) {
            a.kind = abs(gBtlWork->breakDifference);
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPopCb, &a);
            return;
        }
        a.kind = b;
        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPop, &a);
        return;
    }
    a.kind = b;

    if (b == 9) {
        if (p->flags & 0x200000000000) {
            return;
        }
        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPop, &a);
        return;
    }
    TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPop, &a);
}

void BtlWorkInit(void) {
    s32 zero = 0;
    u8* d;
    u8* p;
    CpuSet(&zero, gBtlWork, 0x05000074);
    gBtlWork->phase = 0;
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

void UpdateEnemyCardUse(void) {
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
    if (p->flags & 0x7202) {
        return;
    }
    gBtlWork->actor3 = p;
    UseEnemyCard(p->kind);
}

void HandleSoraCardInput(void) {
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

    if (IsSoraReloadCardSelected() != 0) {
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

    if (p->flags & 0x200) {
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
    if (p->flags & 2) {
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

void HandleRikuCardInput(void) {
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

    if (IsRikuReloadCardSelected() != 0) {
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

    if (p->flags & 0x200) {
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
    if (p->flags & 2) {
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

void HandleTutorialCardInput(void) {
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
        if (IsSoraReloadCardSelected() != 0) {
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

    if (p->flags & 0x200) {
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
    if (p->flags & 2) {
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
void MakeOpponentsHittable(void) {
    BtlWork* w = gBtlWork;
    BtlObj* p;

    if (w->flags & BTL_FLAG_VS_BATTLE) {
        if (w->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            p = gRikuBtlWork->actor;
            p->flags &= ~0x80;
            return;
        }
    } else if (w->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
        p = ListPoolFirst(&w->pool);

        while (p != NULL) {
            p->flags &= ~0x80;
            p->invincibleTimer = 0;
            p = ListPoolNext(&p->node);
        }
        return;
    }
    p = w->actor;
    p->flags &= ~0x80;
}

void DropFriendCard(s32 a, s32 b, s32 c) {
    u16 flags;
    s16 v;

    flags = gGameState.progression.friendFlags;

    if (gBtlWork->flags & BTL_FLAG_TUTORIAL) {
        return;
    }

    if (gGameState.flags & GAME_FLAG_RIKU) {
        if (flags & 0x80) {
            SetJiminyFlag(244);
            CreateFriendCardTask(gBtlWork->taskPools, a >> 8, b >> 8, c >> 8, 7);
        }
        return;
    }

    v = -1;

    if (GetRandom() % 4 != 0) {
        switch (gGameState.world) {
        case WORLD_AGRABAH:
            if (flags & 4) {
                v = 2;
                SetJiminyFlag(159);
            }
            break;
        case WORLD_ATLANTICA:
            if (flags & 8) {
                v = 3;
                SetJiminyFlag(160);
            }
            break;
        case WORLD_HALLOWEEN_TOWN:
            if (flags & 0x10) {
                v = 4;
                SetJiminyFlag(161);
            }
            break;
        case WORLD_NEVER_LAND:
            if (flags & 0x20) {
                v = 5;
                SetJiminyFlag(162);
            }
            break;
        case WORLD_HOLLOW_BASTION:
            if (flags & 0x40) {
                v = 6;
                SetJiminyFlag(163);
            }
            break;
        }
    }

    if (v == -1) {
        if (GetRandom() % 2 != 0) {
            if (flags & 1) {
                v = 0;
                SetJiminyFlag(158);
            }
        } else {
            if (flags & 2) {
                v = 1;
                SetJiminyFlag(157);
            }
        }
    }

    if (v != -1) {
        CreateFriendCardTask(gBtlWork->taskPools, a >> 8, b >> 8, c >> 8, v);
    }
}

void EndCardPlay(void) {
    gBtlWork->phase = 1;

    if (!(gBtlWork->flags & BTL_FLAG_CARD_BREAK)) {
        gBtlWork->flags |= BTL_FLAG_CARD_PLAY_ENDED;
    }
    gBtlWork->flags &= ~BTL_FLAG_OPPONENT_CARD_ACTION;
    gBtlWork->flags &= ~BTL_FLAG_PLAYER_CARD_ACTION;
}

void _08019CB4(void) {
    BtlObj* player;
    s32 i;
    s32 changed;
    s32 busy;
    u8 count;
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
    case 1:
    case 2:
        if (gBtlWork->flags & BTL_FLAG_TUTORIAL) {
            HandleTutorialCardInput();
#ifdef VERSION_EU
            eu_08013190();
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
    gBtlWork->actor4 = 0;
    TaskPoolUpdate(&gBtlWork->taskPools[1]);
    if (gBtlWork->flags & BTL_FLAG_CARD_BREAK) {
        gBtlWork->flags |= BTL_FLAG_STOP_BGFX;
        gBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;
        if (gBtlWork->flags & BTL_FLAG_HUM_BATTLE) {
            gRikuBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;
        }
        gBtlWork->phase = 1;
        if (gBtlWork->soraOwnsPlay) {
            BtlObj* obj;
            gBtlWork->flags &= ~BTL_FLAG_OPPONENT_CARD_ACTION;
            obj = gBtlWork->actor3;
            if (obj != NULL) {
                obj->flags |= 0x10000ULL;
            }
            FadeFromAmount(2, 10, 4);
        } else {
            gBtlWork->flags &= ~BTL_FLAG_PLAYER_CARD_ACTION;
            player->flags |= 0x10000ULL;
            FadeFromAmount(3, 10, 4);
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
            player->flags |= 1;
        } else {
            BtlObj* obj;
            gBtlWork->flags |= BTL_FLAG_OPPONENT_CARD_ACTION;
            obj = gBtlWork->actor3;
            if (obj != NULL) {
                obj->flags |= 1;
            }
        }
        gBtlWork->phase = 2;
        gBtlWork->phaseStep = 0;
    } else {
        changed = 0;
    }
    if (gBtlWork->flags & BTL_FLAG_PLAYER_DEFEATED) {
        if (gBtlWork->phase != 3) {
            gBtlWork->phase = 3;
            gBtlWork->phaseStep = 0;
        }
    } else if (gBtlWork->flags & BTL_FLAG_BATTLE_OVER) {
        if (gBtlWork->phase != 4) {
            gBtlWork->phase = 4;
            gBtlWork->phaseStep = 0;
            switch ((u32)gBtlWork->battleId) {
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
    case 0:
        if (gBtlWork->phaseStep == 0) {
            if (!(gBtlWork->flags & BTL_FLAG_TUTORIAL)) {
                gBtlWork->task = TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlStart, 0);
            }
            gBtlWork->phaseStep = 1;
        }
        if (FadeIsActive()) {
            break;
        }
        if (gBtlWork->phaseStep == 1) {
            for (i = 0; i < 32; i++) {
                if (gBtlWork->fadeExcludedPalettes & (s32)(1U << i)) {
                    FadeSetPaletteExcluded(i, 1);
                }
            }
            gBtlWork->phaseStep = 2;
        }
        if (IsTaskActiveNamed(gBtlWork->task, gTaskDescBtlStart.name)) {
            break;
        }
        if (gBtlWork->phaseStep == 2) {
            gBtlWork->flags |= BTL_FLAG_ENEMY_MOVE_ENABLED;
            gBtlWork->flags &= ~BTL_FLAG_PAUSE_DISABLED;
            TaskCreate(gBtlWork->taskPools, &gTaskDescBtlLockon, 0);
            TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlHpply, 0);
            if (!(gBtlWork->flags & BTL_FLAG_TUTORIAL)) {
                TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlHpenm, 0);
            }
            TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlExp, 0);
            if (!(gBtlWork->flags & BTL_FLAG_BOSS_BATTLE) && !(gBtlWork->flags & BTL_FLAG_HUM_BATTLE)) {
                switch ((u32)gBtlWork->battleId) {
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
                        TaskCreate(gBtlWork->taskPools, &gTaskDescBtlEscape, 0);
                    } else if (gGameState.progression.unk_82 & 0x20) {
                        TaskCreate(gBtlWork->taskPools, &gTaskDescBtlEscape, 0);
                    }
                    break;
                }
            }
            TaskCreate(&gBtlWork->taskPools[1], &gTaskDescCardBattleSora, 0);
            if (gBtlWork->flags & BTL_FLAG_TUTORIAL) {
                if (gBtlWork->battleId == 179) {
                    TaskCreate(&gBtlWork->taskPools[1], &gTaskDescCardBattleRiku, 0);
                }
            } else if (gBtlWork->flags & BTL_FLAG_HUM_BATTLE) {
                TaskCreate(&gBtlWork->taskPools[1], &gTaskDescCardBattleRiku, 0);
            }
            RequestOpenCards();
            func_080838E8();
            gBtlWork->phaseStep = 3;
        } else if (gBtlWork->phaseStep == 3) {
            gBtlWork->phase = 1;
            gBtlWork->phaseStep = 0;
            if (gGameState.roomEffect == 5) {
                DropFriendCard(0x10000, gBtlWork->actor->y, gBtlWork->actor->z - 0x7800);
            }
        }
        break;
    case 1:
        break;
    case 4:
        if (gBtlWork->phaseStep == 0) {
            RequestCloseCards();
            RequestBossCardClose();
            gBtlWork->flags &= ~BTL_FLAG_ENEMY_MOVE_ENABLED;
            if (gBtlWork->flags & BTL_FLAG_SUMMON_ACTIVE) {
                gBtlWork->flags |= BTL_FLAG_DISMISS_SUMMONS;
                FadeToOriginal(0, 8);
            }
            SetBattleZoom(8, 256, gBtlWork->x2, gBtlWork->y2);
            gBtlWork->flags |= BTL_FLAG_CARD_PLAY_ENDED;
            gBtlWork->actor2 = 0;
            gBtlWork->phaseStep = 1;
            gBtlWork->hcEffect = 0;
            gBtlWork->flags |= BTL_FLAG_STOP_SPAWNING;
        } else if (gBtlWork->phaseStep == 1) {
            gBtlWork->phaseStep = 2;
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
                if (gBtlWork->phaseStep == 2) {
                    ReleaseBattleTiles();
                    gBtlWork->task = TaskCreate(&gBtlWork->taskPools[1], &gTaskDescPremireChance, 0);
                    gBtlWork->flags |= BTL_FLAG_PAUSE_DISABLED;
                    gBtlWork->flags |= BTL_FLAG_FIELD_HIDDEN;
                    gBtlWork->phaseStep = -1;
                } else {
                    if (IsTaskActiveNamed(gBtlWork->task, gTaskDescPremireChance.name)) {
                        break;
                    }
                    gBtlWork->flags &= ~BTL_FLAG_PREMIRE_COLLECTED;
                    gBtlWork->phaseStep = 2;
                }
                break;
            }
            if (gBtlWork->pendingLevelUps != 0) {
                if (gBtlWork->phaseStep == 2) {
                    ReleaseBattleTiles();
                    gBtlWork->task = TaskCreate(&gBtlWork->taskPools[1], &gTaskDescLevelUp, 0);
                    gBtlWork->flags |= BTL_FLAG_PAUSE_DISABLED;
                    gBtlWork->flags |= BTL_FLAG_FIELD_HIDDEN;
                    gBtlWork->phaseStep = -1;
                }
                break;
            }
            if (gBtlWork->phaseStep == -1) {
                if (!IsTaskActive(gBtlWork->task)) {
                    BtlObj* healed;
                    gBtlWork->phaseStep = 2;
                    healed = gBtlWork->actor;
                    healed->hp = gGameState.progression.maxHp;
                    healed->maxHp = gGameState.progression.maxHp;
                }
                break;
            }
            if (gBtlWork->phaseStep == 2 && !FadeIsActive()) {
                gBtlWork->flags |= BTL_FLAG_PAUSE_DISABLED;
                gBtlWork->hitStop = 99;
                gBtlWork->phaseStep = 3;
            } else if (gBtlWork->phaseStep == 3) {
                SetBackdropColor(0, 0, 0);
                FadeStartOut(0, 15);
                FadeLock();
                gBtlWork->phaseStep = 4;
            } else if (!FadeIsActive()) {
                ExitBattle();
            }
        }
        break;
    case 3:
        if (gBtlWork->phaseStep == 0) {
            RequestCloseCards();
            RequestBossCardClose();
            gBtlWork->flags &= ~BTL_FLAG_ENEMY_MOVE_ENABLED;
            gBtlWork->flags |= BTL_FLAG_CARD_PLAY_ENDED;
            gBtlWork->actor2 = 0;
            gBtlWork->pendingEnemies = 0;
        }
        if (gBtlWork->phaseStep == 140) {
            FadeStartOut(1, 100);
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
                switch ((u32)gBtlWork->battleId) {
                case 166:
                    state->progression.friendFlags = 0;
                    break;
                case 174:
                    state->progression.friendFlags &= ~3;
                    break;
#ifdef VERSION_EU
                case 158:
                    state->progression.friendFlags &= ~0x20;
                    break;
#endif
                }
                ModeRequest(&gModeContinue, 0);
            }
            break;
        }
        gBtlWork->phaseStep++;
        break;
    case 2: {
        BtlObj* obj;
        if (changed) {
            break;
        }
        busy = 0;
        if (player->flags & 0x10) {
            busy = 1;
        }
        if (busy) {
            break;
        }
        obj = ListPoolFirst(&gBtlWork->pool);
        while (obj != NULL) {
            if (obj->flags & 0x10) {
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
                if (gBtlWork->stockMove >= (s8)count) {
                    gBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;
                }
                if (gBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE) {
                    player->flags |= 1;
                } else {
                    EndCardPlay();
                }
            } else {
                if (gRikuBtlWork->stockMove >= (s8)count) {
                    gRikuBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;
                }
                if (gRikuBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE) {
                    gRikuBtlWork->actor->flags |= 1;
                } else {
                    EndCardPlay();
                }
            }
        } else {
            if (gBtlWork->stockMove >= (s8)count) {
                gBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;
            }
            if (gBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE) {
                player->flags |= 1;
            } else {
                EndCardPlay();
            }
        }
        break;
    }
    }
}

u32 ClampBattlePosition(s32* px, s32* py, s32 radiusX, s32 radiusY) {
    u16 rx = radiusX;
    u16 ry = radiusY;
    u8 r = 0;

    if (*py < (gBtlWork->yMin - (s16)ry) << 8) {
        *py = (gBtlWork->yMin - (s16)ry) << 8;
        r = 3;
    }

    if (*py > (gBtlWork->yMax + (s16)ry) << 8) {
        *py = (gBtlWork->yMax + (s16)ry) << 8;
        r = 4;
    }

    if (*px < (gBtlWork->xMin - (s16)rx) << 8) {
        *px = (gBtlWork->xMin - (s16)rx) << 8;
        r = 1;
    }

    if (*px > (gBtlWork->xMax + (s16)rx) << 8) {
        *px = (gBtlWork->xMax + (s16)rx) << 8;
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

s32 ApplyBtlObjHit(BtlObj* p) {
    if (p->flags & 0x40) {
        p->flags &= ~0x40;

        if (p->hitFlags & 0x20000) {
            p->flags |= 0x800000000;
        }
        return 11;
    }

    if (p->flags & 2) {
        p->flags &= ~3;
        p->hp -= p->damage;

        if (p->hp < 0) {
            p->hp = 0;
        }
        p->flags &= ~1;
        gBtlWork->hitStop = gBtlWork->pendingHitStop;
        p->flags |= 0x2280;
        p->hitFlashFrames = 0;

        if (p->hp <= 0) {
            p->flags |= 0x100;
            p->flags &= ~0x4020;
            p->flags |= 0x1000000000;
            p->badStatus = 0;
            p->badStatusTimer = 0;

            if (p->hitFlags & 0x20000) {
                p->flags |= 0x800000000;
            }

            if (p->flags & 0x40000) {
                p->flags &= ~0x40000;
                return 8;
            }
            return 3;
        }

        if (p->kind != 55 && GetRandom() % 8 == 0) {
            DropFriendCard(p->x, p->y, p->z - 0x7800);
        }

        if (p->flags & 0x40000) {
            p->flags &= ~0x40000;
            p->flags &= ~0x52000004800;
            p->badStatus = 0;
            p->badStatusTimer = 0;
            return 7;
        }

        if (p->flags & 0x4000) {
            p->flags &= ~0x52000004800;

            if (p->badStatus != 1) {
                p->badStatus = 1;
                p->badStatusTimer = 240;
            }
            return 6;
        }

        if (p->flags & 0x2000000000) {
            p->flags &= ~0x52000004800;
            p->badStatus = 4;
            p->badStatusTimer = 300;
            return 12;
        }

        if (p->flags & 0x10000000000) {
            p->flags &= ~0x52000004800;
            p->badStatus = 3;
            p->badStatusTimer = 300;
            return 1;
        }

        if (p->flags & 0x40000000000) {
            p->flags &= ~0x52000004800;

            if (p->badStatus != 5) {
                p->badStatus = 5;
                p->badStatusTimer = 600;
            }
            return 1;
        }
        p->badStatus = 0;
        p->badStatusTimer = 0;
        return 1;
    }

    if (p->flags & 0x20) {
        p->flags &= ~0x21;
        p->flags |= 0x280;
        return 2;
    }

    if (p->flags & 0x20000000) {
        p->flags &= ~0x20000000;

        if (p->hp > 0) {
            ClearBtlObjActionFlags(p);
            return 9;
        }
        return 0;
    }

    if (p->flags & 0x800) {
        p->flags &= ~0x52000004800;
        gBtlWork->hitStop = gBtlWork->pendingHitStop;
        ClearBtlObjActionFlags(p);
        p->flags |= 0x200;

        if (p->badStatus != 2) {
            p->badStatus = 2;
            p->badStatusTimer = p->damage;
        }
        return 10;
    }
    return 0;
}

u8 TryStartCardAction(BtlObj* p) {
    u64 f = p->flags;

    if (f & 1) {
        p->flags &= ~0x46023;
        p->flags |= 0x90;
        p->originX = p->x;
        p->originY = p->y;
        p->originZ = p->z;
        return 1;
    }
    return 0;
}

s32 UpdateBtlObjReaction(BtlObj* p) {
    u16 t;
    u16 u;
    u16 v;

    if (p->badStatus == 2) {
        if (p->flags & 2) {
            p->flags &= ~0x40002;
            p->flags &= ~0x52000004800;
            gBtlWork->hitStop = gBtlWork->pendingHitStop;
            p->invincibleTimer = 30;
            p->delayedDamage += p->damage;
        }
    } else {
        t = p->delayedDamage;

        if ((s16)p->delayedDamage > 0) {
            p->damage = t;
            p->delayedDamage = 0;
            gBtlWork->pendingHitStop = 0;
            p->flags &= ~0x52000004800;
            p->flags |= 2;
            p->hitFlags = 0;
            p->knockbackSpeed = 0;
            p->knockbackLift = 0;
        }
    }
    u = p->invincibleTimer;

    if (p->invincibleTimer > 0) {
        p->invincibleTimer = u - 1;
    }
    v = p->popCooldown;

    if (p->popCooldown > 0) {
        p->popCooldown = v - 1;
    }

    if (p->flags & 0x10000) {
        p->flags &= ~0x10003;
        ClearBtlObjActionFlags(p);
        p->flags |= 0x200;
        CreateBtlPopTask(p, 9);
        gBtlWork->hitStop = 12;
        return 4;
    }
    if (TryStartCardAction(p)) {
        return 5;
    }
    return ApplyBtlObjHit(p);
}

void ClearBtlObjActionFlags(BtlObj* p) {
    p->flags &= ~0x2290;
}

u16 GetBattleSpritePriorityFlags(s32 a) {
    if (a < gBtlWork->bossY + (gBtlWork->bossPriorityOffset << 8)) {
        return 0x800;
    }
    return 0x400;
}

void BeginBossDefeat(BtlObj* actor) {
    BtlObj* p;

    gBtlWork->flags |= BTL_FLAG_BOSS_DEFEATING;
    gBtlWork->flags |= BTL_FLAG_DISMISS_SUMMONS;
    gBtlWork->flags |= BTL_FLAG_BATTLE_OVER;
    SetEnemyJiminyFlag(actor);
    m4aMPlayFadeOut(gMPlayTable[gSongTable[3].ms].info, 12);
    FadeStartIn(2, 20);
    FadeLock();
    p = ListPoolFirst(&gBtlWork->pool);

    while (p != NULL) {
        p->node.flags |= LIST_NODE_FLAG_SKIP;
        p = ListPoolNext(&p->node);
    }
    gBtlWork->enemyCount = 0;
}

void EndBossDefeat(void) {
    gBtlWork->flags &= ~BTL_FLAG_BOSS_DEFEATING;
}

void SetEnemyKindFlags(BtlObj* p) {
    switch (p->kind) {
    case 1:
        p->flags |= 0x10800000100000;
        break;
    case 2:
        p->flags |= 0x10400000200000;
        break;
    case 3:
        p->flags |= 0x400000;
        break;
    case 4:
        p->flags |= 0x700000;
        break;
    case 5:
        p->flags |= 0x1000000000000;
        break;
    case 7:
        p->flags |= 0x3C02C000000000;
        break;
    case 16:
        p->flags |= 0x400000;
        break;
    case 23:
        p->flags |= 0x280700000;
        break;
    case 27:
        p->flags |= 0x400000;
        break;
    case 32:
        p->flags |= 0x11C000000000000;
        break;
    case 33:
        p->flags |= 0x11C000000000000;
        break;
    case 34:
        p->flags |= 0x11C000000000000;
        break;
    case 35:
        p->flags |= 0x11C000000000000;
        break;
    case 36:
        p->flags |= 0x11C000000000000;
        break;
    case 37:
        p->flags |= 0x11C000000000000;
        break;
    case 38:
        p->flags |= 0x11C000000000000;
        break;
    case 39:
        p->flags |= 0x11E000000000000;
        break;
    case 40:
        p->flags |= 0x11E000000000000;
        break;
    case 42:
        p->flags |= 0x108000290000000;
        break;
    case 43:
        p->flags |= 0x11C000280000000;
        break;
    case 44:
        p->flags |= 0x100000290100000;
        break;
    case 45:
        p->flags |= 0x1C000280000000;
        break;
    case 46:
        p->flags |= 0x400000000000;
        break;
    case 47:
        p->flags |= 0x400000000000;
        break;
    case 48:
        p->flags |= 0x110000280100000;
        break;
    case 49:
        p->flags |= 0xC000280400000;
        break;
    case 50:
        p->flags |= 0x110000280200000;
        break;
    case 51:
        p->flags |= 0x11E000280000000;
        break;
    case 52:
        p->flags |= 0x11C000280000000;
        break;
    case 53:
        p->flags |= 0x34000288000000;
        break;
    case 0:
    default:
        break;
    }
}

void InitEnemyBtlObj(BtlObj* p, const EmyKind* d, s32 x, s32 y, s32 z) {
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

    e = GetEnemyBaseStats(d->id);

    if (e != NULL) {
        v = d->id;

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
                p->maxHp = 1120;
                p->attack = 5;
                p->exp = 2775;
                break;
            case 168:
                p->maxHp = 1120;
                p->attack = 5;
                p->exp = 3225;
                break;
            case 169:
                p->maxHp = 1120;
                p->attack = 8;
                p->exp = 5700;
                break;
            case 170:
                p->maxHp = 1680;
                p->attack = 10;
                p->exp = 6825;
                break;
            case 171:
                p->maxHp = 1120;
                p->attack = 5;
                p->exp = 1875;
                break;
            case 172:
                p->maxHp = 1680;
                p->attack = 10;
                p->exp = 5700;
                break;
            case 162:
                p->maxHp = 320;
                p->attack = 2;
                p->exp = 75;
                break;
            case 173:
                p->maxHp = 1680;
                p->attack = 15;
                p->exp = 6825;
                break;
            case 163:
                p->maxHp = 1120;
                p->attack = 5;
                p->exp = 2325;
                break;
            case 174:
                p->maxHp = 1680;
                p->attack = 15;
                p->exp = 6263;
                break;
            case 164:
                p->maxHp = 1120;
                p->attack = 15;
                p->exp = 4125;
                break;
            case 175:
                p->maxHp = 1120;
                p->attack = 20;
                p->exp = 5700;
                break;
            case 176:
                p->maxHp = 1120;
                p->attack = 3;
                p->exp = 975;
                break;
            case 166:
                p->maxHp = 400;
                p->attack = 3;
                p->exp = 133;
                break;
            case 177:
                p->maxHp = 2240;
                p->attack = 25;
                p->exp = 0;
                break;
            case 167:
                p->maxHp = 1680;
                p->attack = 15;
                p->exp = 6517;
                break;
            default:
                p->maxHp = 2240;
                p->attack = 27;
                p->exp = 13131;
                break;
            }
            break;
        case EMY_ID_37:
            if (gGameState.flags & GAME_FLAG_RIKU) {
                p->maxHp = 300;
                p->attack = 4;
                p->exp = 150;
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
            p->maxHp = ((gGameState.floor * a + 256) * e->hp) >> 8;
            p->attack = ((gGameState.floor * b + 256) * e->attack) >> 8;
            p->exp = ((c * gGameState.floor + 256) * (u16)e->exp) >> 8;
            break;
        }
    } else {
        p->maxHp = d->maxHp;
        p->attack = 0;
        p->exp = 1;
        v = d->id;
    }
    p->attackOffset = 80;
    p->attackRangeX = 32;
    p->attackRangeY = 32;
    p->cardInterval = 100;
    p->hp = p->maxHp;
    p->self = p;
    p->x = x;
    p->y = y;
    p->z = z;
    p->groundZ = 0;
    p->flags = 0;
    p->kindFlags = d->flags;
    p->height = d->height;
    p->centerHeight = d->centerHeight;
    p->centerOffsetX = 0;
    p->radiusX = d->radius;
    p->radiusY = d->radius >> 1;
    p->kind = v;
    p->damage = 0;
    p->floorZ = 0;
    p->parent = 0;
    p->invincibleTimer = 0;
    p->delayedDamage = 0;
    p->shadowPriority = 0xFFF1;
    p->btl = 0;
    p->badStatus = 0;
    p->badStatusTimer = 0;
    p->unk_0F0 = gBtlWork->actor->x;
    p->unk_0F4 = gBtlWork->actor->y;
    p->unk_0F8 = gBtlWork->actor->z;
    p->vx = 0;
    p->vy = 0;
    p->popCooldown = 0;

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
        if (!(d->flags & 1)) {
            ColliderInit(&p->collider, 8, d->radius, d->height);
        }
        p->flags |= 0xAC280000000;
        p->flags |= 0x40000000;
        break;
    default:
        if (!(d->flags & 1)) {
            if (d->flags & 8) {
                ColliderInit(&p->collider, 11, d->radius, d->height);
            } else {
                ColliderInit(&p->collider, 3, d->radius, d->height);
            }
        }
    }
    SetEnemyKindFlags(p);

    if (d->flags & 4) {
        p->flags |= 0x20000;
    }
    ListNodeInit(&p->node, &gBtlWork->pool, p);
    ListPoolAppend(&p->node, &gBtlWork->pool);
    gBtlWork->enemyCount++;
}

void ReleaseEnemyBtlObj(BtlObj* obj) {
    BtlObj* p = obj->self;
    if (p == obj) {
        ListPoolRemove(&p->node, &gBtlWork->pool);

        if (!(p->kindFlags & 1)) {
            ColliderUnregister(&p->collider);
        }
        gBtlWork->enemyCount--;
    }
}

u8 CreateBtlPrizeTasksCapped(BtlPrizeSrc* p, u16 b, s16 c, s16* n, s16* cnt) {
    s16 i;
    s16 lim;

    lim = *n / c;
    p->kind = b;

    for (i = 0; i < lim; i++) {
        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPrize, p);

        if (++(*cnt) > 2) {
            return 1;
        }
    }
    *n = *n % c;
    return 0;
}

void CreateBtlPrizeTasks(BtlPrizeSrc* p, u16 b, s16 c, s16* n) {
    s16 i;
    s16 lim;
    lim = *n / c;
    p->kind = b;

    for (i = 0; i < lim; i++) {
        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPrize, p);
    }
    *n = *n % c;
}
void DropBossPrizes(BtlObj* p) {
    BtlPrizeSrc a;
    s16 n;
    a.x = p->x;
    a.y = p->y;
    a.z = p->z;
    a.noTimeout = 1;
    n = p->exp;
    CreateBtlPrizeTasks(&a, 0, 0x578, &n);
    CreateBtlPrizeTasks(&a, 8, 199, &n);
    CreateBtlPrizeTasks(&a, 5, 60, &n);
    CreateBtlPrizeTasks(&a, 7, 30, &n);
    CreateBtlPrizeTasks(&a, 4, 10, &n);
    CreateBtlPrizeTasks(&a, 6, 5, &n);
    CreateBtlPrizeTasks(&a, 3, 1, &n);
}

void DropEnemyPrizes(BtlObj* p) {
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
    a.x = p->x;
    a.y = p->y;
    a.z = p->z;
    a.noTimeout = 0;
    n = p->exp;
    cnt = 0;

    if (gBtlWork->enemyCount == 1 && gBtlWork->pendingEnemies <= 0) {
        if (CountRegularMapCards() <= 4) {
            flag = 0;
        } else {
            switch (p->kind) {
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
            if (flag != 0) {
                CreateHeartlessCardTask(&gBtlWork->taskPools[0], p->x >> 8, p->y >> 8, p->z >> 8, p->kind);
            } else {
                b.x = p->x;
                b.y = p->y;
                b.z = p->z;
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

void TryDropPremireCard(BtlObj* p) {
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
    a.x = p->x;
    a.y = p->y;
    a.z = p->z;
    a.noTimeout = 0;
    TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPremire, &a);
}

u8 IsPlayerOnPlatform(Collider* a) {
    if (a == gBtlWork->platform) {
        return 1;
    } else {
        return 0;
    }
}

void SetBattleActorPosition(s32 a, s32 b, s32 c) {
    gBtlWork->actor->x = a;
    gBtlWork->actor->y = b;
    gBtlWork->actor->z = c;
}

void RequestEnemyCardUse(BtlObj* p) {
    if (!(p->flags & 0x7202)) {
        gBtlWork->actor4 = p;
    }
}

void TryEnemyCardUse(BtlObj* p) {
    s32 x;
    s32 y;
    s32 cx;
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;

    if (p->flags & 0x7202) {
        return;
    }
    if (GetRandom() % (p->cardInterval * gBtlWork->enemyCount) != 0) {
        return;
    }
    GetEnemyTargetPosition(p, &x, &y, 0);

    if (p->attackRangeX == 0) {
        gBtlWork->actor4 = p;
        return;
    }

    if (p->flags & 4) {
        cx = p->x - ((s16)(x1 = p->attackOffset) * 256);
        x1 = p->attackRangeX;
    } else {
        x1 = p->attackOffset;
        cx = p->x + (s16)x1 * 256;
        x1 = p->attackRangeX;
    }

    x1 -= 4;
    x0 = cx - (x1 *= 256);
    y0 = p->y - (p->attackRangeY * 256);
    x1 = x0 + ((p->attackRangeX + 4) * 512);
    y1 = y0 + ((p->attackRangeY + 4) * 512);

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
    gBtlWork->actor4 = p;
}

void SetBtlObjParent(BtlObj* p, BtlObj* v) {
    p->parent = v;
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
        s.flags |= 1;
        break;
    case 19:
        s.desc = &gTaskDescEmy27;
        break;
    case 20:
        s.desc = &gTaskDescEmy28;
        s.flags |= 1;
        break;
    case 21:
        s.desc = &gTaskDescEmy29;
        s.flags |= 1;
        break;
    case 22:
        s.desc = &gTaskDescEmy30;
        s.flags |= 1;
        break;
    case 23:
        s.desc = &gTaskDescEmy31;
        s.flags |= 1;
        break;
    case 24:
        s.desc = &gTaskDescEmy37;
        born = 0;
        break;
    case 25:
        s.desc = &gTaskDescEmy38;
        s.flags |= 1;
        break;
    case 26:
        s.desc = &gTaskDescEmy39;
        s.flags |= 1;
        break;
    case 27:
        s.desc = &gTaskDescEmy41;
        s.flags |= 1;
        break;
    case 28:
        s.desc = &gTaskDescEmy44;
        s.flags |= 1;
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

    if (born != 0) {
        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlBorn, &s);
    } else {
        if (CanAllocObjTiles(s.tileCount) == 0 || CanAllocObjPalette(1) == 0) {
            gBtlWork->pendingEnemies--;
            return 0;
        }
        TaskCreate(&gBtlWork->taskPools[0], s.desc, &s.x);
    }
    return 1;
}

void AllocBattleTiles(void) {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        gBtlWork->tiles = AllocObjTiles(0x840, 0);
    } else {
        gBtlWork->tiles = AllocObjTiles(0xC80, 0);
        gBtlWork->tiles2 = AllocObjTiles(0xA00, 0);

        if (gBtlWork->flags & BTL_FLAG_VS_BATTLE) {
            gRikuBtlWork->tiles = AllocObjTiles(0xC80, 0);
        }
    }
    gBtlWork->flags |= BTL_FLAG_TILES_ALLOCATED;
}

void ReleaseBattleTiles(void) {
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

void SetGimmickFlag(u8 a) {
    if (a <= 4) {
        gBtlWork->gimmickFlags |= 1 << a;
    }
}

u8 ConsumeGimmickFlag(u8 a) {
    u8 m;

    if (a > 4) {
        return 0;
    }
    m = 1 << a;
    if (gBtlWork->gimmickFlags & m) {
        gBtlWork->gimmickFlags &= ~m;
        return 1;
    }
    return 0;
}

void _0801C1F8(u8 a, s32 x, s32 y, s32 z) {
    u16 id;

    switch (a) {
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

void SetGimmickTarget(s32 a, s32 b, s32 c) {
    gBtlWork->gimmickX = a;
    gBtlWork->gimmickY = b;
    gBtlWork->gimmickZ = c;
}

void SetBtlPaletteFadeExcluded(u8 a, u8 b) {
    if (a <= 0x1F) {
        if (b != 0) {
            gBtlWork->fadeExcludedPalettes |= 1 << a;
        } else {
            gBtlWork->fadeExcludedPalettes &= ~(1 << a);
        }
    }
}

void SetBtlObjUnhittable(BtlObj* p, u8 f) {
    if (f) {
        p->flags |= 0x1000000;
    } else {
        p->flags &= ~0x1000000;
    }
}

void ExitBattle(void) {
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


u8 ApplyBattleBounds(s32* a, s32* b, s32* c, s32* d) {
    if (gBtlWork->boundsCallback != NULL) {
        return gBtlWork->boundsCallback(a, b, c, d);
    }
    return 0;
}

void GetEnemyTargetPosition(BtlObj* a, s32* b, s32* c, s32* d) {
    u16 n;

    if (a->badStatus == 3) {
        if (b != NULL) {
            *b = a->unk_0F0;
        }
        if (c != NULL) {
            *c = a->unk_0F4;
        }
        if (d != NULL) {
            *d = a->unk_0F8;
        }
        n = GetRandom() % 6;

        if (n == 0) {
            if (b != NULL) {
                *b = (gBtlWork->xMin + GetRandom() % (gBtlWork->xMax - gBtlWork->xMin + 1)) << 8;
            }
            if (c != NULL) {
                *c = (gBtlWork->yMin + GetRandom() % (gBtlWork->yMax - gBtlWork->yMin + 1)) << 8;
            }
            if (d != NULL) {
                *d = n;
            }
        }
    } else {
        if (b != NULL) {
            *b = gBtlWork->targetX;
        }
        if (c != NULL) {
            *c = gBtlWork->targetY;
        }
        if (d != NULL) {
            *d = gBtlWork->targetZ;
        }
    }
}

void SetEnemyHpFromStats(BtlObj* a, s32 id, s32 c) {
    u16 b = id;
    const EnemyBaseStats* e = GetEnemyBaseStats(b);
    if (e != NULL) {
        a->maxHp = (e->hp * c) >> 8;
        if (a->maxHp <= 0) {
            a->maxHp = 1;
        }
        a->hp = a->maxHp;
    }
}

void SetEnemyJiminyFlag(BtlObj* p) {
    switch (p->kind) {
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

u8 StepHitFlash(BtlObj* p) {
    if (gBtlWork->paused == 1) {
        return 0;
    }

    if (!(p->flags & 0x2000)) {
        return 0;
    }

    if (p->hitFlashFrames > 0x17) {
        return 0;
    }
    p->hitFlashFrames++;
    if (p->hitFlashFrames & 1) {
        return 1;
    }
    return 0;
}

u8 StepHitFlashSolid(BtlObj* p) {
    if (gBtlWork->paused == 1) {
        return 0;
    }

    if (!(p->flags & 0x2000)) {
        return 0;
    }

    if (p->hitFlashFrames > 0x17) {
        return 0;
    }
    p->hitFlashFrames++;
    return 1;
}

void InitGameState(void) {
    s32 zero = 0;
    CpuSet(&zero, &gGameState, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(GameState) / 4);

    if (gDebugFlags & DEBUG_FLAG_RIKU) {
        gGameState.flags |= GAME_FLAG_RIKU;
        gGameState.flags |= GAME_FLAG_SORA_CLEAR;
    }
    gGameState.world = WORLD_WONDERLAND;
    gGameState.battleStage = BATTLE_STAGE_WONDERLAND;
    InitPlayerProgression();
    gGameState.availableWorlds = 0xFFFF;
    ResetMapFloors();
    gGameState.hp = gGameState.progression.maxHp;
    gGameState.fieldAngle = 0x2D;
    gGameState.roomEffect = 0;
}

void ClearFieldResume(void) {
    gGameState.fieldResume = 0;
}

void RequestFieldResume(void) {
    gGameState.fieldResume = 1;
}

void SeedGameRandom(void) {
    if (gGameState.fieldResume != 0) {
        SeedRandom(gGameState.randomSeed);
    } else {
        gGameState.randomSeed = GetRandom();
        SeedRandom(gGameState.randomSeed);
    }
}

void ResetGameState(void) {
    SeedRandom(gFrameCounter);
    InitGameState();
    ClearFieldResume();
    ChkBtlReset();
    gUnk_02039DC0 = 0;
#ifdef VERSION_EU
    gDebugFlags &= ~DEBUG_FLAG_DEBUG_MENU;
#endif
}
