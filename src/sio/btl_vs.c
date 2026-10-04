/**
 * btl_vs.c
 * Link Battle Logic
 */

#include "display.h"
#include "m4a_song.h"
#include "battle.h"
#include "gba/keys.h"
#include "fade.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "card_api.h"
#include "card_battle.h"
#include "gba/macro.h"
#include "gba/syscall.h"
#include "mode.h"
#include "mode_vsbattle.h"
#include "registration_data.h"
#include <stddef.h>
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"
#include "key_state.h"

static u16 sVsKeyHoldL[2];
static u16 sVsKeyHoldR[2];
static u16 sVsKeyReleaseL[2];
static u16 sVsKeyReleaseR[2];
static u16 sVsKeyChordLatch[2];
static u16 sVsSoraReloadTimer;
static u16 sVsRikuReloadTimer;

void UpdateVsKeyHoldTimes(u16 keys, s32 i) {
    if (keys & L_BUTTON) {
        sVsKeyHoldL[i]++;
        sVsKeyReleaseL[i] = 0;

        if (sVsKeyHoldL[i] > 32) {
            sVsKeyHoldL[i] = 29;
        }
    } else {
        sVsKeyHoldL[i] = 0;

        if (sVsKeyReleaseL[i] < 255) {
            sVsKeyReleaseL[i]++;
        }
    }

    if (keys & R_BUTTON) {
        sVsKeyHoldR[i]++;
        sVsKeyReleaseR[i] = 0;

        if (sVsKeyHoldR[i] > 32) {
            sVsKeyHoldR[i] = 29;
        }
    } else {
        sVsKeyHoldR[i] = 0;

        if (sVsKeyReleaseR[i] < 255) {
            sVsKeyReleaseR[i]++;
        }
    }
}

s32 ReadVsKeyChord(u16 a, u16 b, s32 i) {
    s32 ret = 0;

    UpdateVsKeyHoldTimes(a, i);

    if (sVsKeyReleaseL[i] == 2) {
        sVsKeyChordLatch[i] &= ~L_BUTTON;
    }

    if (sVsKeyReleaseR[i] == 2) {
        sVsKeyChordLatch[i] &= ~R_BUTTON;
    }

    if (((b & L_BUTTON) && (a & R_BUTTON)) || ((b & R_BUTTON) && (a & L_BUTTON))) {
        sVsKeyChordLatch[i] |= (L_BUTTON | R_BUTTON);
        ret = L_BUTTON | R_BUTTON;
    }

    if (!(sVsKeyChordLatch[i] & L_BUTTON)) {
        if (sVsKeyHoldL[i] == 5 || sVsKeyReleaseL[i] == 1) {
            sVsKeyChordLatch[i] |= L_BUTTON;
            ret = L_BUTTON;
        }
    }

    if (!(sVsKeyChordLatch[i] & R_BUTTON)) {
        if (sVsKeyHoldR[i] == 5 || sVsKeyReleaseR[i] == 1) {
            sVsKeyChordLatch[i] |= R_BUTTON;
            ret = R_BUTTON;
        }
    }

    return ret;
}

void VsBtlWorkInit() {
    CpuFill32(0, gBtlWork, sizeof(BtlWork));
    CpuFill32(0, gRikuBtlWork, sizeof(BtlWork));
    gBtlWork->phase = 0;
    gBtlWork->fadeExcludedPalettes = -0x10000;
    gBtlWork->gravity = 66;
    gBtlWork->fadeAmount = 10;
    gBtlWork->flags |= BTL_FLAG_VS_BATTLE;
    sVsKeyHoldL[0] = 0;
    sVsKeyHoldR[0] = 0;
    sVsKeyReleaseL[0] = 0;
    sVsKeyReleaseR[0] = 0;
    sVsKeyHoldL[1] = 0;
    sVsKeyHoldR[1] = 0;
    sVsKeyReleaseL[1] = 0;
    sVsKeyReleaseR[1] = 0;
    sVsKeyChordLatch[0] = 0;
    sVsKeyChordLatch[1] = 0;
    sVsSoraReloadTimer = 0;
    sVsRikuReloadTimer = 0;
}

void HandleVsRikuCardInput() {
    BtlWork* w;
    BtlObj* o;
    u16 held;
    u16 pressed;
    s32 res;
    u8 f;

    w = gRikuBtlWork;

    if (gBtlWork->flags & BTL_FLAG_VS_LINK_PARENT) {
        held = SioKeyGetHeldB();
        pressed = SioKeyGetPressedB();
    } else {
        held = SioKeyGetHeldA();
        pressed = SioKeyGetPressedA();
    }

    if (gRikuBtlWork->flags & BTL_FLAG_CAN_CHARGE_RELOAD) {
        if (held & A_BUTTON) {
            if (!(held & (L_BUTTON | R_BUTTON))) {
                SetRikuReloadCharging();
            }
        }
    }

    if (gRikuBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
        sVsRikuReloadTimer = 5;
        return;
    }

    if ((s16)gRikuBtlWork->listSwitchTimer > 0) {
        if (--gRikuBtlWork->listSwitchTimer == 0) {
            RequestSwitchRikuCardList();
        }

        return;
    }

    if ((s16)sVsRikuReloadTimer > 0) {
        sVsRikuReloadTimer--;
    }

    res = (u16)ReadVsKeyChord(held, pressed, 1);

    switch (res) {
    case L_BUTTON:
        RequestRikuNextCard();
        break;
    case R_BUTTON:
        RequestRikuPrevCard();
        break;
    }

    if (pressed & SELECT_BUTTON) {
        RequestSwitchRikuCardList();
    }

    f = IsRikuReloadCardSelected();

    if (f) {
        w->lHeldFrames = 0;
        w->rHeldFrames = 0;
    } else {
        if ((held & L_BUTTON) && !(held & R_BUTTON)) {
            if (w->lHeldFrames <= 254) {
                w->lHeldFrames++;
            }
        } else {
            w->lHeldFrames = f;
        }

        if ((held & R_BUTTON) && !(held & L_BUTTON)) {
            if (w->rHeldFrames <= 254) {
                w->rHeldFrames++;
            }
        } else {
            w->rHeldFrames = 0;
        }
    }

    if (w->lHeldFrames > 32) {
        RequestRikuNextCard();
    }

    if (w->rHeldFrames > 32) {
        RequestRikuPrevCard();
    }

    o = w->actor;

    if (o->flags & BTLOBJ_FLAG_CARD_USE_BLOCKED) {
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

    if (o->flags & BTLOBJ_FLAG_DAMAGE_PENDING) {
        return;
    }

    if (res == 0x300) {
        if (GetRikuStockCount() > 2) {
            RequestRikuStockUse();
        } else {
            RequestRikuCardStock();
        }
    }

    if (pressed & A_BUTTON) {
        RequestRikuCardUse();

        if (GetRikuCardListIndex() == 3) {
            if (IsRikuSelectionEmpty() == 0) {
                gRikuBtlWork->listSwitchTimer = 15;
            }
        }
    }
}

void HandleVsSoraCardInput() {
    BtlWork* w;
    BtlObj* o;
    u16 held;
    u16 pressed;
    s32 res;
    u8 f;

    w = gBtlWork;

    if (w->flags & BTL_FLAG_VS_LINK_PARENT) {
        held = SioKeyGetHeldA();
        pressed = SioKeyGetPressedA();
    } else {
        held = SioKeyGetHeldB();
        pressed = SioKeyGetPressedB();
    }

    if (gBtlWork->flags & BTL_FLAG_CAN_CHARGE_RELOAD) {
        if (held & A_BUTTON) {
            if (!(held & (L_BUTTON | R_BUTTON))) {
                SetSoraReloadCharging();
            }
        }
    }

    if (gBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
        sVsSoraReloadTimer = 5;
        return;
    }

    if ((s16)gBtlWork->listSwitchTimer > 0) {
        if (--gBtlWork->listSwitchTimer == 0) {
            RequestSwitchSoraCardList();
        }

        return;
    }

    if ((s16)sVsSoraReloadTimer > 0) {
        sVsSoraReloadTimer--;
    }

    res = (u16)ReadVsKeyChord(held, pressed, 0);

    switch (res) {
    case L_BUTTON:
        RequestSoraNextCard();
        break;
    case R_BUTTON:
        RequestSoraPrevCard();
        break;
    }

    if (pressed & SELECT_BUTTON) {
        RequestSwitchSoraCardList();
    }

    f = IsSoraReloadCardSelected();

    if (f) {
        w->lHeldFrames = 0;
        w->rHeldFrames = 0;
    } else {
        if ((held & L_BUTTON) && !(held & R_BUTTON)) {
            if (w->lHeldFrames <= 254) {
                w->lHeldFrames++;
            }
        } else {
            w->lHeldFrames = f;
        }

        if ((held & R_BUTTON) && !(held & L_BUTTON)) {
            if (w->rHeldFrames <= 254) {
                w->rHeldFrames++;
            }
        } else {
            w->rHeldFrames = 0;
        }
    }

    if (w->lHeldFrames > 32) {
        RequestSoraNextCard();
    }

    if (w->rHeldFrames > 32) {
        RequestSoraPrevCard();
    }

    o = w->actor;

    if (o->flags & BTLOBJ_FLAG_CARD_USE_BLOCKED) {
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

    if (o->flags & BTLOBJ_FLAG_DAMAGE_PENDING) {
        return;
    }

    if (res == 0x300) {
        if (GetSoraStockCount() > 2) {
            RequestSoraStockUse();
        } else {
            RequestSoraCardStock();
        }
    }

    if (pressed & A_BUTTON) {
        RequestSoraCardUse();

        if (GetSoraCardListIndex() == 3) {
            if (IsSoraSelectionEmpty() == 0) {
                gBtlWork->listSwitchTimer = 15;
            }
        }
    }
}

void VsEndCardPlay() {
    gBtlWork->phase = 1;

    if (!(gBtlWork->flags & BTL_FLAG_CARD_BREAK)) {
        gBtlWork->flags |= BTL_FLAG_CARD_PLAY_ENDED;
    }

    gBtlWork->flags &= ~BTL_FLAG_OPPONENT_CARD_ACTION;
    gBtlWork->flags &= ~BTL_FLAG_PLAYER_CARD_ACTION;
}

void VsBattleUpdate() {
    BtlObj* player = gBtlWork->actor;
    BtlObj* other = gRikuBtlWork->actor;
    s32 entered;
    s32 i;
    s32 busy;
    s8 rank;

    if (gBtlWork->hcEffect == 53 || gRikuBtlWork->hcEffect == 53) {
        gBtlWork->gravity = 38;
    } else {
        gBtlWork->gravity = 66;
    }

    switch ((u32)gBtlWork->phase) {
    case 1:
    case 2:
        if (gBtlWork->flags & BTL_FLAG_VS_LINK_PARENT) {
            HandleVsSoraCardInput();
            HandleVsRikuCardInput();
        } else {
            HandleVsRikuCardInput();
            HandleVsSoraCardInput();
        }

        break;
    }

    TaskPoolUpdate(&gBtlWork->taskPools[1]);

    if (gBtlWork->flags & BTL_FLAG_CARD_BREAK) {
        gBtlWork->flags |= BTL_FLAG_STOP_BGFX;
        gBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;
        gRikuBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;
        gBtlWork->phase = 1;

        if (gBtlWork->soraOwnsPlay) {
            gBtlWork->flags &= ~BTL_FLAG_OPPONENT_CARD_ACTION;
            other->flags |= BTLOBJ_FLAG_CARD_BREAK_PENDING;
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
        entered = 1;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_START;

        if (gBtlWork->soraOwnsPlay) {
            gBtlWork->flags |= BTL_FLAG_PLAYER_CARD_ACTION;
            player->flags |= BTLOBJ_FLAG_CARD_ACTION_PENDING;
        } else {
            gBtlWork->flags |= BTL_FLAG_OPPONENT_CARD_ACTION;
            other->flags |= BTLOBJ_FLAG_CARD_ACTION_PENDING;
        }

        gBtlWork->phase = 2;
        gBtlWork->phaseStep = 0;
    } else {
        entered = 0;
    }

    if ((gBtlWork->flags & BTL_FLAG_PLAYER_DEFEATED) && gBtlWork->phase != 4) {
        gBtlWork->phase = 4;
        gBtlWork->phaseStep = 0;
    }

    switch ((u32)gBtlWork->phase) {
    case 1:
        break;
    case 0:
        if (gBtlWork->phaseStep == 0) {
            gBtlWork->task = NULL;
            gBtlWork->phaseStep = 1;
        }

        if (FadeIsActive()) return;

        if (gBtlWork->phaseStep == 1) {
            for (i = 0; i < 32; i++) {
                if (gBtlWork->fadeExcludedPalettes & (s32)(1U << i)) FadeSetPaletteExcluded(i, 1);
            }

            gBtlWork->phaseStep = 2;
        }

        if (IsTaskActive(gBtlWork->task)) return;

        if (gBtlWork->phaseStep == 2) {
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlVslockon, NULL);
            TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlHpply, NULL);
            TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlHpoth, NULL);

            if (gBtlWork->flags & BTL_FLAG_VS_LINK_PARENT) {
                TaskCreate(&gBtlWork->taskPools[1], &gTaskDescCardBattleSora, NULL);
                TaskCreate(&gBtlWork->taskPools[1], &gTaskDescCardBattleRiku, NULL);
            } else {
                TaskCreate(&gBtlWork->taskPools[1], &gTaskDescCardBattleRiku, NULL);
                TaskCreate(&gBtlWork->taskPools[1], &gTaskDescCardBattleSora, NULL);
            }

            RequestOpenCards();
            func_080838E8();
            gBtlWork->phaseStep = 3;
        } else if (gBtlWork->phaseStep == 3) {
            gBtlWork->phase = 1;
            gBtlWork->phaseStep = 0;
        }

        break;
    case 4:
        if (gBtlWork->phaseStep == 0) {
            RequestCloseCards();
            RequestBossCardClose();
            gBtlWork->flags |= BTL_FLAG_CARD_PLAY_ENDED;
            gRikuBtlWork->flags |= BTL_FLAG_DISMISS_SUMMONS;
            gBtlWork->flags |= BTL_FLAG_DISMISS_SUMMONS;
            SetBattleZoom(8, 256, gBtlWork->x2, gBtlWork->y2);
            gBtlWork->hcEffect = 0;
            gRikuBtlWork->hcEffect = 0;
        }

        if (gBtlWork->phaseStep == 140) {
            FadeStartOut(FADE_MODE_WHITE, 100);
            FadeLock();
            gBtlWork->flags |= BTL_FLAG_STOP_BGFX;
            gBtlWork->hitStop = 100;
        } else if (gBtlWork->phaseStep > 140 && !FadeIsActive()) {
            m4aMPlayAllStop();

            if (player->hp <= 0) ModeRequest(&gModeSioBtlCardget, 1);
            else ModeRequest(&gModeSioBtlCardget, 0);

            return;
        }

        gBtlWork->phaseStep++;
        break;
    case 2:
        if (entered) return;

        busy = 0;

        if (player->flags & BTLOBJ_FLAG_IN_CARD_ACTION) busy = 1;

        if (other->flags & BTLOBJ_FLAG_IN_CARD_ACTION) busy = 1;

        if (busy) return;

        rank = GetStockMoveCount();
        gBtlWork->phaseStep = 0;

        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            if (gBtlWork->stockMove >= rank) gBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;

            if (gBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE) player->flags |= BTLOBJ_FLAG_CARD_ACTION_PENDING;
            else VsEndCardPlay();
        } else {
            if (gRikuBtlWork->stockMove >= rank) gRikuBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;

            if (gRikuBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE) other->flags |= BTLOBJ_FLAG_CARD_ACTION_PENDING;
            else VsEndCardPlay();
        }

        break;
    }
}
