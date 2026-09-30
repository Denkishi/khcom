#include "task_descriptors.h"
#include "btl.h"
#include "battle_backgrounds.h"
#include "btl_api.h"

u8 gBtlMapShakeActive;
u16 gBtlMapShakeStep;
s32 gBtlMapShakeOffset;

static const s8 sBtlMapShakePattern[32] = {
    4, 4, 4, 4, -4, -4, -4, -4, 3, 3, 3, 3, -3, -3, -3, -3, 2, 2, 2, 2, -2, -2, -2, -2, 1, 1, 1, 1, -1, -1, -1, -1,
};

#ifdef VERSION_EU
extern u8 gUnkEu_08F7042C[];
extern u8 gUnkEu_08F7D724[];
#endif

void task_btl_map_0(BtlMapWork* work) {
    SetBgSize(gBtlWork->mapBg, 0x8000);

    if (gBtlWork->flags & BTL_FLAG_HUM_BATTLE) {
        switch (gBtlWork->battleId) {
        case 0xB2:
        case 0xB3:
            LoadBgTiles(gBtlWork->mapBg, gUnk_08C78824, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F68624, 0xC0);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EEF384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EEF384, 0x1000);
#endif
            gBtlWork->fadeAmount = 5;
            break;
        case 0xB1:
#ifdef VERSION_EU
            eu_080059D4(gBtlWork->mapBg, gUnk_08CBC6E4);
#else
            LoadBgTiles(gBtlWork->mapBg, gUnk_08CBC6E4, 0x4000);
#endif
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F69604, 0x120);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08F00384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08F00384, 0x1000);
#endif
            gBtlWork->fadeAmount = 5;
            break;
        case 0xA0:
#ifdef VERSION_EU
            eu_080059D4(gBtlWork->mapBg, gUnkEu_08F7042C);
#else
            LoadBgTiles(gBtlWork->mapBg, gUnk_08CB06E4, 0x4000);
#endif
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F69404, 0xC0);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnkEu_08F7D724);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EFD384, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case 0x9E:
#ifdef VERSION_EU
            eu_080059D4(gBtlWork->mapBg, gUnk_08CAC6E4);
#else
            LoadBgTiles(gBtlWork->mapBg, gUnk_08CAC6E4, 0x4000);
#endif
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F692C4, 0x140);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EFC384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EFC384, 0x1000);
#endif
            gBtlWork->fadeAmount = 9;
            break;
        case 0x9F:
            LoadBgTiles(gBtlWork->mapBg, gUnk_08C7C824, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F686E4, 0xE0);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EF0384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EF0384, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case 0xAC:
        case 0xAF:
#ifdef VERSION_EU
            eu_080059D4(gBtlWork->mapBg, gUnk_08CB86E4);
#else
            LoadBgTiles(gBtlWork->mapBg, gUnk_08CB86E4, 0x4000);
#endif
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F69544, 0xC0);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EFF384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EFF384, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case 0xA5:
#ifdef VERSION_EU
            eu_080059D4(gBtlWork->mapBg, gUnk_08CC06E4);
#else
            LoadBgTiles(gBtlWork->mapBg, gUnk_08CC06E4, 0x4000);
#endif
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F69724, 0x80);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08F01384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08F01384, 0x1000);
#endif
            gBtlWork->fadeAmount = 20;
            break;
        default:
#ifdef VERSION_EU
            eu_080059D4(gBtlWork->mapBg, gUnk_08CB46E4);
#else
            LoadBgTiles(gBtlWork->mapBg, gUnk_08CB46E4, 0x4000);
#endif
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F694C4, 0x80);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EFE384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EFE384, 0x1000);
#endif
            gBtlWork->fadeAmount = 20;
            break;
        }
    } else if (gBtlWork->battleId == 0x78) {
        LoadBgTiles(gBtlWork->mapBg, gUnk_08C80824, 0x4000);
        LoadBgPalette(gBtlWork->mapBg, gUnk_08F687C4, 0x140);
#ifdef VERSION_EU
        eu_080059F4(gBtlWork->mapBg, gUnk_08EF1384);
#else
        LoadBgMap(gBtlWork->mapBg, gUnk_08EF1384, 0x1000);
#endif
        gBtlWork->fadeAmount = 10;
    } else {
        switch (gGameState.battleStage) {
        case BATTLE_STAGE_WONDERLAND:
            LoadBgTiles(gBtlWork->mapBg, gUnk_08C84824, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F68904, 0xC0);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EF2384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EF2384, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case 2:
            LoadBgTiles(gBtlWork->mapBg, gUnk_08C80824, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F687C4, 0x140);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EF1384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EF1384, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_STAGE_AGRABAH:
            LoadBgTiles(gBtlWork->mapBg, gUnk_08C90824, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F68B84, 0x100);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EF5384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EF5384, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_STAGE_ATLANTICA:
            LoadBgTiles(gBtlWork->mapBg, gUnk_08C88824, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F689C4, 0xC0);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EF3384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EF3384, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_STAGE_MONSTRO:
            LoadBgTiles(gBtlWork->mapBg, gUnk_08C8C824, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F68A84, 0x100);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EF4384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EF4384, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_STAGE_HALLOWEEN_TOWN:
            LoadBgTiles(gBtlWork->mapBg, gUnk_08C94824, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F68C84, 0xE0);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EF6384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EF6384, 0x1000);
#endif
            gBtlWork->fadeAmount = 5;
            break;
        case BATTLE_STAGE_NEVER_LAND:
            LoadBgTiles(gBtlWork->mapBg, gUnk_08C98824, 0x3EC0);
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F68D64, 0x140);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EF7384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EF7384, 0x1000);
#endif
            gBtlWork->fadeAmount = 5;
            break;
        case BATTLE_STAGE_DESTINY_ISLANDS:
            LoadBgTiles(gBtlWork->mapBg, gUnk_08C9C6E4, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F68EA4, 0x120);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EF8384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EF8384, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_STAGE_HOLLOW_BASTION:
            LoadBgTiles(gBtlWork->mapBg, gUnk_08CA06E4, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F68FC4, 0xE0);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EF9384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EF9384, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_STAGE_TRAVERSE_TOWN:
            LoadBgTiles(gBtlWork->mapBg, gUnk_08C78824, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F68624, 0xC0);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EEF384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EEF384, 0x1000);
#endif
            gBtlWork->fadeAmount = 5;
            break;
        case BATTLE_STAGE_CASTLE_OBLIVION:
            LoadBgTiles(gBtlWork->mapBg, gUnk_08CA86E4, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F691E4, 0xE0);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EFB384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EFB384, 0x1000);
#endif
            gBtlWork->fadeAmount = 20;
            break;
        case BATTLE_STAGE_TWILIGHT_TOWN:
            LoadBgTiles(gBtlWork->mapBg, gUnk_08CA46E4, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F690A4, 0x140);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EFA384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EFA384, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        default:
            LoadBgTiles(gBtlWork->mapBg, gUnk_08C7C824, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gUnk_08F686E4, 0xE0);
#ifdef VERSION_EU
            eu_080059F4(gBtlWork->mapBg, gUnk_08EF0384);
#else
            LoadBgMap(gBtlWork->mapBg, gUnk_08EF0384, 0x1000);
#endif
            gBtlWork->fadeAmount = 11;
            break;
        }
    }
    gBtlWork->scale = 0x100;
    gBtlWork->zoomScale = 0x100;
    gBtlWork->x = 0x10000;
    gBtlWork->y = 0x16000;
    gBtlWork->viewX = 0x10000;
    gBtlWork->viewY = 0x16000;
    gBtlWork->x2 = 0x10000;
    gBtlWork->y2 = 0x16000;
    gBtlWork->zoomX = 0x10000;
    gBtlWork->zoomY = 0x16000;
    gBtlWork->zoomSteps = 0;
    gBtlWork->rotation = 0;
    work->xMin = gBtlWork->xMin << 8;
    work->xMax = gBtlWork->xMax << 8;
    work->yMin = gBtlWork->yMin << 8;
    work->yMax = (gBtlWork->yMax + 0x20) << 8;
    BtlMapResetShake();
    SetBgAffine(gBtlWork->mapBg, gBtlWork->rotation, gBtlWork->scale,
                gBtlWork->scale, gBtlWork->viewX,
                gBtlWork->viewY + 0x2800);
}

void BtlMapResetShake(void) {
    gBtlMapShakeActive = 0;
    gBtlMapShakeStep = 0;
    gBtlMapShakeOffset = 0;
}

void BtlMapStartShake(void) {
    gBtlMapShakeActive = 1;
    gBtlMapShakeStep = 0;
    gBtlMapShakeOffset = 0;
}

void BtlMapUpdateShake(void) {
    if (gBtlMapShakeActive != 0) {
        gBtlMapShakeOffset += ((sBtlMapShakePattern[(s16)gBtlMapShakeStep] << 12) - gBtlMapShakeOffset) >> 3;
        gBtlMapShakeStep++;
        if (gBtlMapShakeStep > 0x1F) {
            gBtlMapShakeActive = 0;
            gBtlMapShakeOffset = 0;
            gBtlWork->rotation = 0;
        }
    }
}

s32 BtlMapGetShake(void) {
    return gBtlMapShakeOffset;
}

void BtlMapSetCameraTarget(s32 a, s32 b) {
    gBtlWork->x2 = a;
    gBtlWork->y2 = b;
}

void BtlMapFollowPosition(s32 a, s32 b, s32 c) {
    s32 x = (a + 0x10000) >> 1;
    s32 y = (b + 0x14400) >> 1;

    if (a - x > 0x3000) {
        x = a - 0x3000;
    } else if (x - a > 0x3000) {
        x = a + 0x3000;
    }

    if (b - y > 0x3000) {
        y = b - 0x3000;
    } else if (y - b > 0x3000) {
        y = b + 0x3000;
    }
    gBtlWork->x2 = x;
    gBtlWork->y2 = y + c;
}

s32 task_btl_map_1(BtlMapWork* work) {
    s32 dx;
    s32 dy;

    BtlMapUpdateShake();

    if (gBtlWork->zoomSteps > 0) {
        ApproachValueHalfSteps(&gBtlWork->scale, gBtlWork->zoomScale, gBtlWork->zoomSteps);
        ApproachValueHalfSteps(&gBtlWork->x, gBtlWork->zoomX, gBtlWork->zoomSteps);
        ApproachValueHalfSteps(&gBtlWork->y, gBtlWork->zoomY, gBtlWork->zoomSteps);

        if (gBtlWork->zoomScale == 0x100) {
            ApproachValueHalfSteps(&work->xMin, gBtlWork->xMin << 8, gBtlWork->zoomSteps);
            ApproachValueHalfSteps(&work->xMax, gBtlWork->xMax << 8, gBtlWork->zoomSteps);
            ApproachValueHalfSteps(&work->yMin, gBtlWork->yMin << 8, gBtlWork->zoomSteps);
            ApproachValueHalfSteps(&work->yMax, (gBtlWork->yMax + 0x20) << 8, gBtlWork->zoomSteps);
        } else if (gBtlWork->zoomScale > 0x100) {
            ApproachValueHalfSteps(&work->xMin, 0x3000, gBtlWork->zoomSteps);
            ApproachValueHalfSteps(&work->xMax, 0x1D000, gBtlWork->zoomSteps);
            ApproachValueHalfSteps(&work->yMin, 0x9000, gBtlWork->zoomSteps);
            ApproachValueHalfSteps(&work->yMax, 0x1E800, gBtlWork->zoomSteps);
        }
        gBtlWork->zoomSteps--;
    } else if (gBtlWork->scale == 0x100) {
        dx = (gBtlWork->x2 - gBtlWork->x) >> 3;
        dy = (gBtlWork->y2 - gBtlWork->y) >> 3;

        if (dx > 0x400) {
            dx = 0x400;
        } else if (dx < -0x400) {
            dx = -0x400;
        }

        if (dy > 0x400) {
            dy = 0x400;
        } else if (dy < -0x400) {
            dy = -0x400;
        }
        gBtlWork->x += dx;
        gBtlWork->y += dy;
    }
    gBtlWork->viewX = gBtlWork->x;
    gBtlWork->viewY = gBtlWork->y;

    if (gBtlMapShakeActive != 0) {
        gBtlWork->rotation = (gBtlMapShakeOffset >> 8) / 3;
    }

    if (gBtlWork->viewX - 0x7800 < work->xMin) {
        gBtlWork->viewX = work->xMin + 0x7800;
    } else if (gBtlWork->viewX + 0x7800 > work->xMax) {
        gBtlWork->viewX = work->xMax - 0x7800;
    }

    if (gBtlWork->viewY - 0x5000 < 0x9000) {
        gBtlWork->viewY = 0xE000;
    } else if (gBtlWork->viewY + 0x5000 > work->yMax) {
        gBtlWork->viewY = work->yMax - 0x5000;
    }
    SetBgAffine(gBtlWork->mapBg, gBtlWork->rotation, gBtlWork->scale,
                  gBtlWork->scale, gBtlWork->viewX,
                  gBtlWork->viewY + 0x2800);
    return 1;
}

TaskDesc gTaskDescBtlMap = {
    "task_btl_map",
    (TaskInitFunc)task_btl_map_0,
    (TaskUpdateFunc)task_btl_map_1,
    NULL,
    NULL,
    sizeof(BtlMapWork),
};
