/**
 * romcri.c
 * Room Creation Effects
 */

#include "pallet.h"
#include "romcri.h"
#include "romcri_backgrounds.h"
#include "display.h"
#include "game_state.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

void task_romcri_eff_0(RomcriEffWork* work, s32 arg) {
    SetupBg(1, 0, 23, 12);
    work->angle = arg;
    work->timer = 0;
    DisableBg(1);
    PushPaletteEffect(0);
    LoadBgPalette(1, gRomcriEffPalette, 0x20);
    PopPaletteEffect();
    SetBgPriority(1, 0);
    SetBgBlend(1, 16, 16);

    switch (work->angle) {
    case 0xAD:
        LoadBgTiles(1, gRomcriEffDownTiles, 0x4AC0);
        SetBgScroll(1, (u16)-35, (u16)-23);
        break;
    case 0x53:
        LoadBgTiles(1, gRomcriEffDownTiles, 0x4AC0);
        SetBgScroll(1, (u16)-77, (u16)-23);
        break;
    case 0xD3:
        LoadBgTiles(1, gRomcriEffUpTiles, 0x7520);
        SetBgScroll(1, (u16)-39, 2);
        break;
    case 0x2D:
        LoadBgTiles(1, gRomcriEffUpTiles, 0x7520);
#ifdef VERSION_EU
        SetBgScroll(1, (u16)-73, 5);
#else
        SetBgScroll(1, (u16)-71, 3);
#endif
        break;
    }
}

u8 task_romcri_eff_1(RomcriEffWork* work) {
    switch (work->angle) {
    case 0xAD:
        switch (work->timer) {
        case 0:
            LoadBgMap(1, gRomcriEffDownLeftMap0, 0x800);
            break;
        case 4:
            LoadBgMap(1, gRomcriEffDownLeftMap1, 0x800);
            break;
        case 8:
            LoadBgMap(1, gRomcriEffDownLeftMap2, 0x800);
            break;
        case 12:
            LoadBgMap(1, gRomcriEffDownLeftMap3, 0x800);
            break;
        case 16:
            LoadBgTiles(1, gRomcriEffDown2Tiles, 0x4EA0);
            LoadBgMap(1, gRomcriEffDownLeftMap4, 0x800);
            break;
        case 20:
            LoadBgMap(1, gRomcriEffDownLeftMap5, 0x800);
            break;
        case 24:
            LoadBgMap(1, gRomcriEffDownLeftMap6, 0x800);
            break;
        case 28:
            LoadBgMap(1, gRomcriEffDownLeftMap7, 0x800);
            break;
        case 32:
            return 0;
        }

        break;
    case 0x53:
        switch (work->timer) {
        case 0:
            LoadBgMap(1, gRomcriEffDownRightMap0, 0x800);
            break;
        case 4:
            LoadBgMap(1, gRomcriEffDownRightMap1, 0x800);
            break;
        case 8:
            LoadBgMap(1, gRomcriEffDownRightMap2, 0x800);
            break;
        case 12:
            LoadBgMap(1, gRomcriEffDownRightMap3, 0x800);
            break;
        case 16:
            LoadBgTiles(1, gRomcriEffDown2Tiles, 0x4EA0);
            LoadBgMap(1, gRomcriEffDownRightMap4, 0x800);
            break;
        case 20:
            LoadBgMap(1, gRomcriEffDownRightMap5, 0x800);
            break;
        case 24:
            LoadBgMap(1, gRomcriEffDownRightMap6, 0x800);
            break;
        case 28:
            LoadBgMap(1, gRomcriEffDownRightMap7, 0x800);
            break;
        case 32:
            return 0;
        }

        break;
    case 0x2D:
        switch (work->timer) {
        case 0:
            LoadBgMap(1, gRomcriEffUpRightMap0, 0x800);
            break;
        case 4:
            LoadBgMap(1, gRomcriEffUpRightMap1, 0x800);
            break;
        case 8:
            LoadBgMap(1, gRomcriEffUpRightMap2, 0x800);
            break;
        case 12:
            LoadBgMap(1, gRomcriEffUpRightMap3, 0x800);
            break;
        case 16:
            LoadBgMap(1, gRomcriEffUpRightMap4, 0x800);
            break;
        case 20:
            LoadBgMap(1, gRomcriEffUpRightMap5, 0x800);
            break;
        case 24:
            LoadBgMap(1, gRomcriEffUpRightMap6, 0x800);
            break;
        case 28:
            LoadBgMap(1, gRomcriEffUpRightMap7, 0x800);
            break;
        case 32:
            return 0;
        }

        break;
    case 0xD3:
        switch (work->timer) {
        case 0:
            LoadBgMap(1, gRomcriEffUpLeftMap0, 0x800);
            break;
        case 4:
            LoadBgMap(1, gRomcriEffUpLeftMap1, 0x800);
            break;
        case 8:
            LoadBgMap(1, gRomcriEffUpLeftMap2, 0x800);
            break;
        case 12:
            LoadBgMap(1, gRomcriEffUpLeftMap3, 0x800);
            break;
        case 16:
            LoadBgMap(1, gRomcriEffUpLeftMap4, 0x800);
            break;
        case 20:
            LoadBgMap(1, gRomcriEffUpLeftMap5, 0x800);
            break;
        case 24:
            LoadBgMap(1, gRomcriEffUpLeftMap6, 0x800);
            break;
        case 28:
            LoadBgMap(1, gRomcriEffUpLeftMap7, 0x800);
            break;
        case 32:
            return 0;
        }

        break;
    }

    work->timer++;
    return 1;
}

void task_romcri_eff_3() {
    DisableBg(1);
}

void task_romcri_eff2_0(RomcriEff2Work* work, s32 arg) {
    SetupBg(1, 0, 23, 12);
    work->timer = 0;
    work->frame = 0;
    work->angle = arg;
    DisableBg(1);
    PushPaletteEffect(0);
    LoadBgPalette(1, gRomcriEff2Palette, 0x20);
    PopPaletteEffect();
    SetBgPriority(1, 0);
    SetBgBlend(1, 16, 16);
    LoadBgTiles(1, gRomcriEff2Tiles, 0xA20);

    if (gGameState.flags & GAME_FLAG_RIKU) {
        switch (work->angle) {
        case 0x2D:
            SetBgScroll(1, (u16)-100, 4);
            break;
        case 0xD3:
            SetBgScroll(1, (u16)-73, 5);
            break;
        case 0x53:
            SetBgScroll(1, (u16)-101, (u16)-18);
            break;
        case 0xAD:
            SetBgScroll(1, (u16)-75, (u16)-19);
            break;
        }
    } else {
        switch (work->angle) {
        case 0x2D:
            SetBgScroll(1, (u16)-100, (u16)-6);
            break;
        case 0xD3:
            SetBgScroll(1, (u16)-73, (u16)-5);
            break;
        case 0x53:
            SetBgScroll(1, (u16)-101, (u16)-28);
            break;
        case 0xAD:
            SetBgScroll(1, (u16)-75, (u16)-29);
            break;
        }
    }
}

u8 task_romcri_eff2_1(RomcriEff2Work* work) {
    if (work->timer % 4 == 0) {
        switch (work->frame) {
        case 0:
            LoadBgMap(1, gRomcriEff2Map0, 0x800);
            break;
        case 1:
            EnableBg(1);
            LoadBgMap(1, gRomcriEff2Map1, 0x800);
            break;
        case 2:
            LoadBgMap(1, gRomcriEff2Map2, 0x800);
            break;
        case 3:
            LoadBgMap(1, gRomcriEff2Map3, 0x800);
            break;
        case 4:
            LoadBgMap(1, gRomcriEff2Map2, 0x800);
            break;
        case 5:
            LoadBgMap(1, gRomcriEff2Map1, 0x800);
            break;
        }

        work->frame++;

        if (work->frame > 5) {
            work->frame = 0;
        }
    }

    if (work->timer > 30 && work->frame == 0) {
        return 0;
    }

    work->timer++;
    return 1;
}

void task_romcri_eff2_3() {
    DisableBg(1);
}

TaskDesc gTaskDescRomcriEff = {
    "task_romcri_eff",
    (TaskInitFunc)task_romcri_eff_0,
    (TaskUpdateFunc)task_romcri_eff_1,
    NULL,
    (TaskDestroyFunc)task_romcri_eff_3,
    sizeof(RomcriEffWork),
};

TaskDesc gTaskDescRomcriEff2 = {
    "task_romcri_eff2",
    (TaskInitFunc)task_romcri_eff2_0,
    (TaskUpdateFunc)task_romcri_eff2_1,
    NULL,
    (TaskDestroyFunc)task_romcri_eff2_3,
    sizeof(RomcriEff2Work),
};
