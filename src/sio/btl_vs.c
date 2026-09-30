#include "display.h"
#include "m4a_song.h"
#include "battle.h"

u16 gVsKeyHoldL[2];
u16 gVsKeyHoldR[2];
u16 gVsKeyReleaseL[2];
u16 gVsKeyReleaseR[2];
u16 gVsKeyChordLatch[2];
u16 gUnk_020348E0;
u16 gUnk_020348E2;

void UpdateVsKeyHoldTimes(u16 keys, s32 i) {
    if (keys & L_BUTTON) {
        gVsKeyHoldL[i]++;
        gVsKeyReleaseL[i] = 0;

        if (gVsKeyHoldL[i] > 32) {
            gVsKeyHoldL[i] = 29;
        }
    } else {
        gVsKeyHoldL[i] = 0;

        if (gVsKeyReleaseL[i] < 255) {
            gVsKeyReleaseL[i]++;
        }
    }

    if (keys & R_BUTTON) {
        gVsKeyHoldR[i]++;
        gVsKeyReleaseR[i] = 0;

        if (gVsKeyHoldR[i] > 32) {
            gVsKeyHoldR[i] = 29;
        }
    } else {
        gVsKeyHoldR[i] = 0;

        if (gVsKeyReleaseR[i] < 255) {
            gVsKeyReleaseR[i]++;
        }
    }
}
s32 ReadVsKeyChord(u16 a, u16 b, s32 i) {
    s32 ret = 0;

    UpdateVsKeyHoldTimes(a, i);

    if (gVsKeyReleaseL[i] == 2) {
        gVsKeyChordLatch[i] &= ~L_BUTTON;
    }
    if (gVsKeyReleaseR[i] == 2) {
        gVsKeyChordLatch[i] &= ~R_BUTTON;
    }

    if (((b & L_BUTTON) && (a & R_BUTTON)) || ((b & R_BUTTON) && (a & L_BUTTON))) {
        gVsKeyChordLatch[i] |= (L_BUTTON | R_BUTTON);
        ret = L_BUTTON | R_BUTTON;
    }

    if (!(gVsKeyChordLatch[i] & L_BUTTON)) {
        if (gVsKeyHoldL[i] == 5 || gVsKeyReleaseL[i] == 1) {
            gVsKeyChordLatch[i] |= L_BUTTON;
            ret = L_BUTTON;
        }
    }

    if (!(gVsKeyChordLatch[i] & R_BUTTON)) {
        if (gVsKeyHoldR[i] == 5 || gVsKeyReleaseR[i] == 1) {
            gVsKeyChordLatch[i] |= R_BUTTON;
            ret = R_BUTTON;
        }
    }
    return ret;
}
void VsBtlWorkInit(void) {
    s32 a;
    s32 b;

    a = 0;
    CpuSet(&a, gBtlWork, 0x05000074);
    b = 0;
    CpuSet(&b, gRikuBtlWork, 0x05000074);
    gBtlWork->phase = 0;
    gBtlWork->fadeExcludedPalettes = -0x10000;
    gBtlWork->gravity = 66;
    gBtlWork->fadeAmount = 10;
    gBtlWork->flags |= 0x4000;
    gVsKeyHoldL[0] = 0;
    gVsKeyHoldR[0] = 0;
    gVsKeyReleaseL[0] = 0;
    gVsKeyReleaseR[0] = 0;
    gVsKeyHoldL[1] = 0;
    gVsKeyHoldR[1] = 0;
    gVsKeyReleaseL[1] = 0;
    gVsKeyReleaseR[1] = 0;
    gVsKeyChordLatch[0] = 0;
    gVsKeyChordLatch[1] = 0;
    gUnk_020348E0 = 0;
    gUnk_020348E2 = 0;
}
void HandleVsRikuCardInput(void) {
    BtlWork* w;
    BtlObj* o;
    u16 held;
    u16 pressed;
    s32 res;
    u8 f;

    w = gRikuBtlWork;

    if (gBtlWork->flags & 0x1000) {
        held = SioKeyGetHeldB();
        pressed = SioKeyGetPressedB();
    } else {
        held = SioKeyGetHeldA();
        pressed = SioKeyGetPressedA();
    }

    if (gRikuBtlWork->flags & 0x10000000000000) {
        if (held & A_BUTTON) {
            if (!(held & (L_BUTTON | R_BUTTON))) {
                SetRikuReloadCharging();
            }
        }
    }

    if (gRikuBtlWork->flags & 0x1000000) {
        gUnk_020348E2 = 5;
        return;
    }

    if ((s16)gRikuBtlWork->listSwitchTimer > 0) {
        if (--gRikuBtlWork->listSwitchTimer == 0) {
            RequestSwitchRikuCardList();
        }
        return;
    }

    if ((s16)gUnk_020348E2 > 0) {
        gUnk_020348E2--;
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

    if (f != 0) {
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

    if (o->flags & 0x200) {
        return;
    }

    if (gBtlWork->flags & 0x40) {
        return;
    }

    if (gBtlWork->flags & 0x10000000) {
        return;
    }

    if (gBtlWork->flags & 0x800000) {
        return;
    }

    if (o->flags & 2) {
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

void HandleVsSoraCardInput(void) {
    BtlWork* w;
    BtlObj* o;
    u16 held;
    u16 pressed;
    s32 res;
    u8 f;

    w = gBtlWork;

    if (w->flags & 0x1000) {
        held = SioKeyGetHeldA();
        pressed = SioKeyGetPressedA();
    } else {
        held = SioKeyGetHeldB();
        pressed = SioKeyGetPressedB();
    }

    if (gBtlWork->flags & 0x10000000000000) {
        if (held & A_BUTTON) {
            if (!(held & (L_BUTTON | R_BUTTON))) {
                SetSoraReloadCharging();
            }
        }
    }

    if (gBtlWork->flags & 0x1000000) {
        gUnk_020348E0 = 5;
        return;
    }

    if ((s16)gBtlWork->listSwitchTimer > 0) {
        if (--gBtlWork->listSwitchTimer == 0) {
            RequestSwitchSoraCardList();
        }
        return;
    }

    if ((s16)gUnk_020348E0 > 0) {
        gUnk_020348E0--;
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

    if (f != 0) {
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

    if (o->flags & 0x200) {
        return;
    }

    if (gBtlWork->flags & 0x20000000) {
        return;
    }

    if (gBtlWork->flags & 0x8000000) {
        return;
    }

    if (gBtlWork->flags & 0x800000) {
        return;
    }

    if (o->flags & 2) {
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

void VsEndCardPlay(void) {
    gBtlWork->phase = 1;

    if (!(gBtlWork->flags & 0x800000)) {
        gBtlWork->flags |= 0x20;
    }
    gBtlWork->flags &= ~0x40;
    gBtlWork->flags &= ~0x20000000;
}

void VsBattleUpdate(void) {
    BtlObj* player = gBtlWork->actor;
    BtlObj* other = gRikuBtlWork->actor;
    s32 entered;
    s32 i;
    s32 busy;
    u8 rank;
    if (gBtlWork->hcEffect == 53 || gRikuBtlWork->hcEffect == 53) {
        gBtlWork->gravity = 38;
    } else {
        gBtlWork->gravity = 66;
    }
    switch ((u32)gBtlWork->phase) {
    case 1:
    case 2:
        if (gBtlWork->flags & 0x1000) {
            HandleVsSoraCardInput();
            HandleVsRikuCardInput();
        } else {
            HandleVsRikuCardInput();
            HandleVsSoraCardInput();
        }
        break;
    }
    TaskPoolUpdate(&gBtlWork->taskPools[1]);
    if (gBtlWork->flags & 0x800000) {
        gBtlWork->flags |= 0x400000;
        gBtlWork->flags &= ~2ULL;
        gRikuBtlWork->flags &= ~2ULL;
        gBtlWork->phase = 1;
        if (gBtlWork->soraOwnsPlay != 0) {
            gBtlWork->flags &= ~0x40ULL;
            other->flags |= 0x10000;
            FadeFromAmount(2, 10, 4);
        } else {
            gBtlWork->flags &= ~0x20000000ULL;
            player->flags |= 0x10000;
            FadeFromAmount(3, 10, 4);
        }
        MosaicStartIn(16, 15);
        SetBattleZoom(1, 256, gBtlWork->x2, gBtlWork->y2);
        gBtlWork->phaseStep = 0;
    }
    if (gBtlWork->flags & 0x400) {
        entered = 1;
        gBtlWork->flags &= ~0x400ULL;
        if (gBtlWork->soraOwnsPlay != 0) {
            gBtlWork->flags |= 0x20000000;
            player->flags |= 1;
        } else {
            gBtlWork->flags |= 0x40;
            other->flags |= 1;
        }
        gBtlWork->phase = 2;
        gBtlWork->phaseStep = 0;
    } else {
        entered = 0;
    }
    if ((gBtlWork->flags & 0x400000000000ULL) && gBtlWork->phase != 4) {
        gBtlWork->phase = 4;
        gBtlWork->phaseStep = 0;
    }
    switch ((u32)gBtlWork->phase) {
    case 1:
        break;
    case 0:
        if (gBtlWork->phaseStep == 0) {
            gBtlWork->task = 0;
            gBtlWork->phaseStep = 1;
        }
        if (FadeIsActive()) return;
        if (gBtlWork->phaseStep == 1) {
            for (i = 0; i < 32; i++) {
                if (gBtlWork->fadeExcludedPalettes & (s32)(1U << i)) FadeSetPaletteExcluded(i, 1);
            }
            gBtlWork->phaseStep = 2;
        }
        if (IsTaskActive((Task*)gBtlWork->task)) return;
        if (gBtlWork->phaseStep == 2) {
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlVslockon, 0);
            TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlHpply, 0);
            TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlHpoth, 0);
            if (gBtlWork->flags & 0x1000) {
                TaskCreate(&gBtlWork->taskPools[1], &gTaskDescCardBattleSora, 0);
                TaskCreate(&gBtlWork->taskPools[1], &gTaskDescCardBattleRiku, 0);
            } else {
                TaskCreate(&gBtlWork->taskPools[1], &gTaskDescCardBattleRiku, 0);
                TaskCreate(&gBtlWork->taskPools[1], &gTaskDescCardBattleSora, 0);
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
            gBtlWork->flags |= 0x20;
            gRikuBtlWork->flags |= 0x40000000;
            gBtlWork->flags |= 0x40000000;
            SetBattleZoom(8, 256, gBtlWork->x2, gBtlWork->y2);
            gBtlWork->hcEffect = 0;
            gRikuBtlWork->hcEffect = 0;
        }
        if (gBtlWork->phaseStep == 140) {
            FadeStartOut(1, 100);
            FadeLock();
            gBtlWork->flags |= 0x400000;
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
        if (player->flags & 0x10) busy = 1;
        if (other->flags & 0x10) busy = 1;
        if (busy) return;
        rank = GetStockMoveCount();
        gBtlWork->phaseStep = 0;
        if (gBtlWork->flags & 0x20000000) {
            if (gBtlWork->stockMove >= (s8)rank) gBtlWork->flags &= ~2ULL;
            if (gBtlWork->flags & 2) player->flags |= 1;
            else VsEndCardPlay();
        } else {
            if (gRikuBtlWork->stockMove >= (s8)rank) gRikuBtlWork->flags &= ~2ULL;
            if (gRikuBtlWork->flags & 2) other->flags |= 1;
            else VsEndCardPlay();
        }
        break;
    }
}
