/**
 * mode_status.c
 * Status Screen
 */

#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "display.h"
#include "sprites_status.h"
#include "game_state.h"
#include "fade.h"
#include "mode.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"
#include "copyright_screens.h"
#include "player_progression_types.h"

static TaskPool sStatusTaskPool;
static Task* sStatusBarTask;
static u8 sStatusReturnToMenu;

u8* CopyNumberTiles(u8* dst, s32 value, u16 digits) {
    u16 buf[6];
    s32 scale;
    s32 i;

    if (digits > 6) {
        digits = 6;
    }

    scale = 1;

    for (i = 0; i < digits; i++) {
        scale *= 10;
    }

    if (value > scale - 1) {
        value = scale - 1;
    } else if (value < 0) {
        value = 0;
    }

    for (i = 0; i < digits; i++) {
        buf[i] = (value % scale) / (scale / 10);
        scale /= 10;
    }

    for (i = 0; i < digits; i++) {
        RequestDma3Copy(&gStatusDigitTiles[buf[i] * 32], dst, 32);
        dst += 32;
    }

    return dst;
}

void LoadStatusNumberTiles() {
    u8* p;

    p = GetBgCharBase(2) + 0x40;
    p = CopyNumberTiles(p, gGameState.progression.level, 2);
    p = CopyNumberTiles(p, gGameState.hp, 3);
    p = CopyNumberTiles(p, gGameState.progression.maxHp, 3);

    if (gGameState.flags & GAME_FLAG_RIKU) {
        p += 0x80;
    } else {
        p = CopyNumberTiles(p, gGameState.progression.cp, 4);
    }

    p = CopyNumberTiles(p, gGameState.progression.exp, 6);
    p = CopyNumberTiles(p, gGameState.progression.nextExp, 6);

    if (gGameState.flags & GAME_FLAG_RIKU) {
        p += 0xC0;
        p = CopyNumberTiles(p, gGameState.progression.ap, 2);
        CopyNumberTiles(p, gGameState.progression.dp, 3);
    } else {
        p += 0x20;
        CopyNumberTiles(p, gGameState.progression.mooglePoints, 5);
    }
}

void mode_status_0() {
    BgReset();
    SetBgMode0();
    SetupBg(0, 0, 0x1F, 0);
    SetupBg(2, 0, 0x1E, 0);
    SetupBg(3, 0, 0x1D, 0);
    SetBgPriority(0, 1);
    SetBgPriority(2, 2);
    SetBgPriority(3, 3);
#ifdef VERSION_EU
    LoadBgTiles(3, gStatusBgTiles, 0x2060);

    switch (gLanguage) {
    case LANGUAGE_FRENCH:
        RequestDma3Copy(gStatusBgFrenchTiles, (u8*)GetBgCharBase(3) + 0x1800, 0xC00);
        break;
    case LANGUAGE_GERMAN:
        RequestDma3Copy(gStatusBgGermanTiles, (u8*)GetBgCharBase(3) + 0x1800, 0xC00);
        break;
    case LANGUAGE_ITALIAN:
        RequestDma3Copy(gStatusBgItalianTiles, (u8*)GetBgCharBase(3) + 0x1800, 0xC00);
        break;
    case LANGUAGE_SPANISH:
        RequestDma3Copy(gStatusBgSpanishTiles, (u8*)GetBgCharBase(3) + 0x1800, 0xC00);
        break;
    case LANGUAGE_ENGLISH:
    default:
        break;
    }
#else
    LoadBgTiles(3, gStatusBgTiles, 0x2100);
#endif
    LoadBgPalette(3, gStatusBgPalette, 0xA0);
    LoadBgMap(3, gStatusBgMap, 0x500);

    if (gGameState.flags & GAME_FLAG_RIKU) {
        LoadBgMap(2, gStatusRikuBgMap, 0x500);
    } else {
        LoadBgMap(2, gStatusSoraBgMap, 0x500);
    }

    LoadBgMap(0, gStatusMesWindowMap, 0x500);
    DisableBg(0);
    LoadStatusNumberTiles();
    TaskPoolInit(&sStatusTaskPool, 4);
    sStatusBarTask = TaskCreate(&sStatusTaskPool, &gTaskDescStatusBar, NULL);
    TaskCreate(&sStatusTaskPool, &gTaskDescStatus, NULL);
    FadeStartIn(FADE_MODE_BLACK, 0x10);
}

void mode_status_1() {
    UpdatePlayTime();
    TaskPoolUpdate(&sStatusTaskPool);
    TaskPoolDraw(&sStatusTaskPool);

    if (!IsTaskActive(sStatusBarTask) && !FadeIsActive()) {
        ReturnToMap(sStatusReturnToMenu);
    }
}

void mode_status_2() {
    TaskPoolDestroy(&sStatusTaskPool);
}

void SetStatusReturnToMenu(u8 returnToMenu) {
    sStatusReturnToMenu = returnToMenu;
}

Mode gModeStatus = {
    "mode_status",
    (ModeInitFunc)mode_status_0,
    mode_status_1,
    mode_status_2,
};
