/**
 * btl_map.c
 * Battle Background Map
 */

#include "btl.h"
#include "battle_backgrounds.h"
#include "btl_api.h"
#include "battle_work.h"
#include "display.h"
#include "engine_math.h"
#include "game_state.h"
#include "taskpool.h"
#include "types.h"
#include "event_backgrounds.h"
#include <stddef.h>
#include "battle_ids.h"

static u8 sBtlMapShakeActive;
static u16 sBtlMapShakeStep;
static s32 sBtlMapShakeOffset;

static const s8 sBtlMapShakePattern[32] = {
    4, 4, 4, 4, -4, -4, -4, -4, 3, 3, 3, 3, -3, -3, -3, -3, 2, 2, 2, 2, -2, -2, -2, -2, 1, 1, 1, 1, -1, -1, -1, -1,
};

void task_btl_map_0(BtlMapWork* work) {
    SetBgSize(gBtlWork->mapBg, 0x8000);

    if (gBtlWork->flags & BTL_FLAG_HUM_BATTLE) {
        switch (gBtlWork->battleId) {
        case BATTLE_TUTORIAL_0:
        case BATTLE_TUTORIAL_1:
            LoadBgTiles(gBtlWork->mapBg, gBtlBgTraverseTownTiles, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gBtlBgTraverseTownPalette, 0xC0);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgTraverseTownMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgTraverseTownMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 5;
            break;
        case BATTLE_ANSEM_2:
#ifdef VERSION_EU
            LoadBgTilesLz77(gBtlWork->mapBg, gBtlBgAnsem2Tiles);
#else
            LoadBgTiles(gBtlWork->mapBg, gBtlBgAnsem2Tiles, 0x4000);
#endif
            LoadBgPalette(gBtlWork->mapBg, gBtlBgAnsem2Palette, 0x120);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgAnsem2Map);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgAnsem2Map, 0x1000);
#endif
            gBtlWork->fadeAmount = 5;
            break;
        case BATTLE_HADES:
#ifdef VERSION_EU
            LoadBgTilesLz77(gBtlWork->mapBg, gBtlBgHadesTiles);
#else
            LoadBgTiles(gBtlWork->mapBg, gBtlBgHadesTiles, 0x4000);
#endif
            LoadBgPalette(gBtlWork->mapBg, gBtlBgHadesPalette, 0xC0);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgHadesMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgHadesMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_HOOK:
#ifdef VERSION_EU
            LoadBgTilesLz77(gBtlWork->mapBg, gBtlBgHookTiles);
#else
            LoadBgTiles(gBtlWork->mapBg, gBtlBgHookTiles, 0x4000);
#endif
            LoadBgPalette(gBtlWork->mapBg, gBtlBgHookPalette, 0x140);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgHookMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgHookMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 9;
            break;
        case BATTLE_CLOUD:
            LoadBgTiles(gBtlWork->mapBg, gBtlBgOlympusColiseumTiles, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gBtlBgOlympusColiseumPalette, 0xE0);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgOlympusColiseumMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgOlympusColiseumMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_RIKU_6:
        case BATTLE_VEXEN_2:
#ifdef VERSION_EU
            LoadBgTilesLz77(gBtlWork->mapBg, gBtlBgMansionTiles);
#else
            LoadBgTiles(gBtlWork->mapBg, gBtlBgMansionTiles, 0x4000);
#endif
            LoadBgPalette(gBtlWork->mapBg, gBtlBgMansionPalette, 0xC0);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgMansionMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgMansionMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_MARLUXIA:
#ifdef VERSION_EU
            LoadBgTilesLz77(gBtlWork->mapBg, gBtlBgMarluxiaTiles);
#else
            LoadBgTiles(gBtlWork->mapBg, gBtlBgMarluxiaTiles, 0x4000);
#endif
            LoadBgPalette(gBtlWork->mapBg, gBtlBgMarluxiaPalette, 0x80);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgMarluxiaMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgMarluxiaMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 20;
            break;
        default:
#ifdef VERSION_EU
            LoadBgTilesLz77(gBtlWork->mapBg, gBtlBgHumTiles);
#else
            LoadBgTiles(gBtlWork->mapBg, gBtlBgHumTiles, 0x4000);
#endif
            LoadBgPalette(gBtlWork->mapBg, gBtlBgHumPalette, 0x80);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgHumMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgHumMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 20;
            break;
        }
    } else if (gBtlWork->battleId == BATTLE_CARD_SOLDIERS) {
        LoadBgTiles(gBtlWork->mapBg, gBtlBgGardenTiles, 0x4000);
        LoadBgPalette(gBtlWork->mapBg, gBtlBgGardenPalette, 0x140);
#ifdef VERSION_EU
        LoadBgMapLz77(gBtlWork->mapBg, gBtlBgGardenMap);
#else
        LoadBgMap(gBtlWork->mapBg, gBtlBgGardenMap, 0x1000);
#endif
        gBtlWork->fadeAmount = 10;
    } else {
        switch (gGameState.battleStage) {
        case BATTLE_STAGE_WONDERLAND:
            LoadBgTiles(gBtlWork->mapBg, gBtlBgWonderlandTiles, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gBtlBgWonderlandPalette, 0xC0);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgWonderlandMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgWonderlandMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_STAGE_GARDEN:
            LoadBgTiles(gBtlWork->mapBg, gBtlBgGardenTiles, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gBtlBgGardenPalette, 0x140);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgGardenMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgGardenMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_STAGE_AGRABAH:
            LoadBgTiles(gBtlWork->mapBg, gBtlBgAgrabahTiles, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gBtlBgAgrabahPalette, 0x100);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgAgrabahMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgAgrabahMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_STAGE_ATLANTICA:
            LoadBgTiles(gBtlWork->mapBg, gBtlBgAtlanticaTiles, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gBtlBgAtlanticaPalette, 0xC0);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgAtlanticaMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgAtlanticaMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_STAGE_MONSTRO:
            LoadBgTiles(gBtlWork->mapBg, gBtlBgMonstroTiles, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gBtlBgMonstroPalette, 0x100);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgMonstroMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgMonstroMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_STAGE_HALLOWEEN_TOWN:
            LoadBgTiles(gBtlWork->mapBg, gBtlBgHalloweenTownTiles, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gBtlBgHalloweenTownPalette, 0xE0);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgHalloweenTownMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgHalloweenTownMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 5;
            break;
        case BATTLE_STAGE_NEVER_LAND:
            LoadBgTiles(gBtlWork->mapBg, gBtlBgNeverLandTiles, 0x3EC0);
            LoadBgPalette(gBtlWork->mapBg, gBtlBgNeverLandPalette, 0x140);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgNeverLandMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgNeverLandMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 5;
            break;
        case BATTLE_STAGE_DESTINY_ISLANDS:
            LoadBgTiles(gBtlWork->mapBg, gBtlBgDestinyIslandsTiles, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gBtlBgDestinyIslandsPalette, 0x120);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgDestinyIslandsMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgDestinyIslandsMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_STAGE_HOLLOW_BASTION:
            LoadBgTiles(gBtlWork->mapBg, gBtlBgHollowBastionTiles, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gBtlBgHollowBastionPalette, 0xE0);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgHollowBastionMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgHollowBastionMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        case BATTLE_STAGE_TRAVERSE_TOWN:
            LoadBgTiles(gBtlWork->mapBg, gBtlBgTraverseTownTiles, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gBtlBgTraverseTownPalette, 0xC0);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgTraverseTownMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgTraverseTownMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 5;
            break;
        case BATTLE_STAGE_CASTLE_OBLIVION:
            LoadBgTiles(gBtlWork->mapBg, gBtlBgCastleOblivionTiles, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gBtlBgCastleOblivionPalette, 0xE0);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgCastleOblivionMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgCastleOblivionMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 20;
            break;
        case BATTLE_STAGE_TWILIGHT_TOWN:
            LoadBgTiles(gBtlWork->mapBg, gBtlBgTwilightTownTiles, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gBtlBgTwilightTownPalette, 0x140);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgTwilightTownMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgTwilightTownMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 10;
            break;
        default:
            LoadBgTiles(gBtlWork->mapBg, gBtlBgOlympusColiseumTiles, 0x4000);
            LoadBgPalette(gBtlWork->mapBg, gBtlBgOlympusColiseumPalette, 0xE0);
#ifdef VERSION_EU
            LoadBgMapLz77(gBtlWork->mapBg, gBtlBgOlympusColiseumMap);
#else
            LoadBgMap(gBtlWork->mapBg, gBtlBgOlympusColiseumMap, 0x1000);
#endif
            gBtlWork->fadeAmount = 11;
            break;
        }
    }

    gBtlWork->scale = Q_8_8(1);
    gBtlWork->zoomScale = Q_8_8(1);
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

void BtlMapResetShake() {
    sBtlMapShakeActive = 0;
    sBtlMapShakeStep = 0;
    sBtlMapShakeOffset = 0;
}

void BtlMapStartShake() {
    sBtlMapShakeActive = 1;
    sBtlMapShakeStep = 0;
    sBtlMapShakeOffset = 0;
}

void BtlMapUpdateShake() {
    if (sBtlMapShakeActive) {
        sBtlMapShakeOffset += ((sBtlMapShakePattern[(s16)sBtlMapShakeStep] << 12) - sBtlMapShakeOffset) >> 3;
        sBtlMapShakeStep++;

        if (sBtlMapShakeStep > 0x1F) {
            sBtlMapShakeActive = 0;
            sBtlMapShakeOffset = 0;
            gBtlWork->rotation = 0;
        }
    }
}

s32 BtlMapGetShake() {
    return sBtlMapShakeOffset;
}

void BtlMapSetCameraTarget(s32 x, s32 y) {
    gBtlWork->x2 = x;
    gBtlWork->y2 = y;
}

void BtlMapFollowPosition(s32 px, s32 py, s32 pz) {
    s32 x = (px + 0x10000) >> 1;
    s32 y = (py + 0x14400) >> 1;

    if (px - x > 0x3000) {
        x = px - 0x3000;
    } else if (x - px > 0x3000) {
        x = px + 0x3000;
    }

    if (py - y > 0x3000) {
        y = py - 0x3000;
    } else if (y - py > 0x3000) {
        y = py + 0x3000;
    }

    gBtlWork->x2 = x;
    gBtlWork->y2 = y + pz;
}

s32 task_btl_map_1(BtlMapWork* work) {
    s32 dx;
    s32 dy;

    BtlMapUpdateShake();

    if (gBtlWork->zoomSteps > 0) {
        ApproachValueHalfSteps(&gBtlWork->scale, gBtlWork->zoomScale, gBtlWork->zoomSteps);
        ApproachValueHalfSteps(&gBtlWork->x, gBtlWork->zoomX, gBtlWork->zoomSteps);
        ApproachValueHalfSteps(&gBtlWork->y, gBtlWork->zoomY, gBtlWork->zoomSteps);

        if (gBtlWork->zoomScale == Q_8_8(1)) {
            ApproachValueHalfSteps(&work->xMin, gBtlWork->xMin << 8, gBtlWork->zoomSteps);
            ApproachValueHalfSteps(&work->xMax, gBtlWork->xMax << 8, gBtlWork->zoomSteps);
            ApproachValueHalfSteps(&work->yMin, gBtlWork->yMin << 8, gBtlWork->zoomSteps);
            ApproachValueHalfSteps(&work->yMax, (gBtlWork->yMax + 0x20) << 8, gBtlWork->zoomSteps);
        } else if (gBtlWork->zoomScale > Q_8_8(1)) {
            ApproachValueHalfSteps(&work->xMin, 0x3000, gBtlWork->zoomSteps);
            ApproachValueHalfSteps(&work->xMax, 0x1D000, gBtlWork->zoomSteps);
            ApproachValueHalfSteps(&work->yMin, 0x9000, gBtlWork->zoomSteps);
            ApproachValueHalfSteps(&work->yMax, 0x1E800, gBtlWork->zoomSteps);
        }

        gBtlWork->zoomSteps--;
    } else if (gBtlWork->scale == Q_8_8(1)) {
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

    if (sBtlMapShakeActive) {
        gBtlWork->rotation = (sBtlMapShakeOffset >> 8) / 3;
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
