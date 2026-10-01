#include "macros.h"
#include "mode_allmap.h"
#include "sprites_allmap.h"
#include "poo.h"
#include "sprites_pooh.h"
#include "system_state.h"
#include "gba/io_reg.h"
#include "allmap_api.h"
#include "malloc.h"
#include "fade.h"
#include <string.h>
#include "allmap_types.h"
#include "anim.h"
#include "display.h"
#include "game_state.h"
#include "gba/syscall.h"
#include "intr.h"
#include "m4a_catalog_data.h"
#include "m4a_song.h"
#include "map_api.h"
#include "map_runtime.h"
#include "map_types.h"
#include "mode.h"
#include "mode_battle_data.h"
#include "obj_api.h"
#include "poo_api.h"
#include "registration_data.h"
#include "taskpool.h"
#include "types.h"

#if defined(VERSION_US)
static const PooBgSet sAllmapWorldBgs[15] = {
    { gUnk_0983BC18 + 0x80, gUnk_097B8258 + 0x1040, gUnk_0984A218 + 0x60 },
    { gUnk_0983BC18 + 0xC80, gUnk_097B8258 + 0x54C0, gUnk_0984A218 + 0xE0 },
    { gUnk_0983BC18 + 0x1280, gUnk_097B8258 + 0x72C0, gUnk_0984A218 + 0x120 },
    { gUnk_0983BC18 + 0x980, gUnk_097B8258 + 0x4B80, gUnk_0984A218 + 0xC0 },
    { gUnk_0983BC18 + 0x80, gUnk_097B8258 + 0x1040, gUnk_0984A218 + 0x60 },
    { gUnk_0983BC18 + 0xF80, gUnk_097B8258 + 0x6580, gUnk_0984A218 + 0x100 },
    { gUnk_0983BC18 + 0x1580, gUnk_097B8258 + 0x7FE0, gUnk_0984A218 + 0x140 },
    { gUnk_0983BC18 + 0x1880, gUnk_097B8258 + 0x98E0, gUnk_0984A218 + 0x160 },
    { gUnk_0983BC18 + 0x1E80, gUnk_097B8258 + 0xBEA0, gUnk_0984A218 + 0x1A0 },
    { gUnk_0983BC18 + 0x380, gUnk_097B8258 + 0x2580, gUnk_0984A218 + 0x80 },
    { gUnk_0983BC18 + 0x680, gUnk_097B8258 + 0x3680, gUnk_0984A218 + 0xA0 },
    { gUnk_0983BC18 + 0x2180, gUnk_097B8258 + 0xCFA0, gUnk_0984A218 + 0x1C0 },
    { gUnk_0983BC18 + 0x2480, gUnk_097B8258 + 0xE0A0, gUnk_0984A218 + 0x1E0 },
    { gUnk_0983BC18 + 0x1B80, gUnk_097B8258 + 0xA9C0, gUnk_0984A218 + 0x180 },
    { gUnk_0983BC18 + 0x80, gUnk_097B8258 + 0x1040, gUnk_0984A218 + 0x60 },
};
#elif defined(VERSION_JP)
static const PooBgSet sAllmapWorldBgs[15] = {
    { gUnk_0983BC18 + 0x80, gUnk_097B8258 + 0x1040, gUnkJp_097FEEEC + 0x60 },
    { gUnk_0983BC18 + 0xC80, gUnk_097B8258 + 0x54C0, gUnkJp_097FEEEC + 0xE0 },
    { gUnk_0983BC18 + 0x1280, gUnk_097B8258 + 0x72C0, gUnkJp_097FEEEC + 0x120 },
    { gUnk_0983BC18 + 0x980, gUnk_097B8258 + 0x4B80, gUnkJp_097FEEEC + 0xC0 },
    { gUnk_0983BC18 + 0x80, gUnk_097B8258 + 0x1040, gUnkJp_097FEEEC + 0x60 },
    { gUnk_0983BC18 + 0xF80, gUnk_097B8258 + 0x6580, gUnkJp_097FEEEC + 0x100 },
    { gUnk_0983BC18 + 0x1580, gUnk_097B8258 + 0x7FE0, gUnkJp_097FEEEC + 0x140 },
    { gUnk_0983BC18 + 0x1880, gUnk_097B8258 + 0x98E0, gUnkJp_097FEEEC + 0x160 },
    { gUnk_0983BC18 + 0x1E80, gUnk_097B8258 + 0xBEA0, gUnkJp_097FEEEC + 0x1A0 },
    { gUnk_0983BC18 + 0x380, gUnk_097B8258 + 0x2580, gUnkJp_097FEEEC + 0x80 },
    { gUnk_0983BC18 + 0x680, gUnk_097B8258 + 0x3680, gUnkJp_097FEEEC + 0xA0 },
    { gUnk_0983BC18 + 0x2180, gUnk_097B8258 + 0xCFA0, gUnkJp_097FEEEC + 0x1C0 },
    { gUnk_0983BC18 + 0x2480, gUnk_097B8258 + 0xE0A0, gUnkJp_097FEEEC + 0x1E0 },
    { gUnk_0983BC18 + 0x1B80, gUnk_097B8258 + 0xA9C0, gUnkJp_097FEEEC + 0x180 },
    { gUnk_0983BC18 + 0x80, gUnk_097B8258 + 0x1040, gUnkJp_097FEEEC + 0x60 },
};
#elif defined(VERSION_EU)
static const PooBgSet sAllmapWorldBgs[15] = {
    { gUnk_0983BC18 + 0x80, gUnkEu_0979E8A0 + 0x1040, gUnkEu_0981E8C0 + 0x60 },
    { gUnk_0983BC18 + 0xC80, gUnkEu_0979E8A0 + 0x54C0, gUnkEu_0981E8C0 + 0xE0 },
    { gUnk_0983BC18 + 0x1280, gUnkEu_0979E8A0 + 0x72C0, gUnkEu_0981E8C0 + 0x120 },
    { gUnk_0983BC18 + 0x980, gUnkEu_0979E8A0 + 0x4B80, gUnkEu_0981E8C0 + 0xC0 },
    { gUnk_0983BC18 + 0x80, gUnkEu_0979E8A0 + 0x1040, gUnkEu_0981E8C0 + 0x60 },
    { gUnk_0983BC18 + 0xF80, gUnkEu_0979E8A0 + 0x6580, gUnkEu_0981E8C0 + 0x100 },
    { gUnk_0983BC18 + 0x1580, gUnkEu_0979E8A0 + 0x7FE0, gUnkEu_0981E8C0 + 0x140 },
    { gUnk_0983BC18 + 0x1880, gUnkEu_0979E8A0 + 0x98E0, gUnkEu_0981E8C0 + 0x160 },
    { gUnk_0983BC18 + 0x1E80, gUnkEu_0979E8A0 + 0xBEA0, gUnkEu_0981E8C0 + 0x1A0 },
    { gUnk_0983BC18 + 0x380, gUnkEu_0979E8A0 + 0x2580, gUnkEu_0981E8C0 + 0x80 },
    { gUnk_0983BC18 + 0x680, gUnkEu_0979E8A0 + 0x3680, gUnkEu_0981E8C0 + 0xA0 },
    { gUnk_0983BC18 + 0x2180, gUnkEu_0979E8A0 + 0xCFA0, gUnkEu_0981E8C0 + 0x1C0 },
    { gUnk_0983BC18 + 0x2480, gUnkEu_0979E8A0 + 0xE0A0, gUnkEu_0981E8C0 + 0x1E0 },
    { gUnk_0983BC18 + 0x1B80, gUnkEu_0979E8A0 + 0xA9C0, gUnkEu_0981E8C0 + 0x180 },
    { gUnk_0983BC18 + 0x80, gUnkEu_0979E8A0 + 0x1040, gUnkEu_0981E8C0 + 0x60 },
};
#endif

static const PooPalStep sAllmapPalSteps[9] = {
    { 0, 40 },
    { 1, 8 },
    { 2, 8 },
    { 3, 8 },
    { 4, 15 },
    { 3, 8 },
    { 2, 8 },
    { 1, 8 },
    { 255, 255 },
};

Mode gModeAllmap = {
    "mode_allmap",
    mode_allmap_0,
    mode_allmap_1,
    mode_allmap_2,
};

static const AllmapRoomOrder sAllmapRoomOrder = {{
    0, 4, 2, 5, 3, 10, 9, 13, 1, 7, 8, 11, 6, 14, 12, 15,
}};

static const AllmapRoomDirs sAllmapRoomDirs = {{1, 2, 3, 0}};

u16* gAllmapBg0MapBlocks[8] EWRAM_COMMON(16);
u32 gAllmapModeState EWRAM_COMMON(4);
TaskPool gAllmapTaskPool EWRAM_COMMON(16);
u16* gAllmapBg1Map EWRAM_COMMON(4);
u16 gAllmapCursorDropTimer EWRAM_COMMON(4);
u16* gAllmapBg1MapBlocks[8] EWRAM_COMMON(16);
u16* gAllmapBg0Map EWRAM_COMMON(4);
u16 gAllmapScrollInTimer EWRAM_COMMON(4);

static u16 sAllmapPalTimer;
static u16 sAllmapPalStep;
static s16 sAllmapBlendTimer;
static u8 sUnk_02034E40[0x40];
static u8 sAllmapReturnToMenu;
static u8 sAllmapLowerBgm;

void AllmapCyclePalette(void) {
    PooPalStep t[9];

    memcpy(t, sAllmapPalSteps, sizeof(t));
    sAllmapPalTimer++;

    if (sAllmapPalTimer < t[sAllmapPalStep].duration) {
        return;
    }

    sAllmapPalTimer = 0;
    sAllmapPalStep++;

    if (t[sAllmapPalStep].palette == 0xFF) {
        sAllmapPalStep = 0;
    }

    LoadPalette(&gUnk_0984A138[t[sAllmapPalStep].palette * 0x20], (void*)0x05000040, 0x20);
}

void AllmapLoadWorldBg(void) {
    RequestDma3Copy(sAllmapWorldBgs[gGameState.world].map, (u8*)GetBgScreenBase(2) + 0x200, 0x300);
    RequestDma3Copy(sAllmapWorldBgs[gGameState.world].tiles, (u8*)GetBgCharBase(2) + 0x2000, 0x2000);
    LoadPalette(sAllmapWorldBgs[gGameState.world].palette, (void*)0x05000140, 0x20);
}

void AllmapLoadFloorTiles(void) {
    u8* src;
    void* dst;

    dst = (u8*)GetBgCharBase(2) + 0x20;

    if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
#ifdef VERSION_EU
        src = gAllmapRikuFloorTilesByLanguage[gLanguage] + gGameState.floor * 0x140;
#else
        src = &gUnk_097B8258[gGameState.floor * 0x140];
#endif
    } else {
#ifdef VERSION_EU
        src = gAllmapFloorTilesByLanguage[gLanguage] + gGameState.floor * 0x140;
#else
        src = &gUnk_097B7218[gGameState.floor * 0x140];
#endif
    }

    RequestDma3Copy(src, dst, 0x140);
    dst = (u8*)GetBgScreenBase(2) + 0x480;
    src = gUnk_0983BC18;
    RequestDma3Copy(src, dst, 10);
    dst = (u8*)GetBgScreenBase(2) + 0x4C0;
    src += 0x40;
    RequestDma3Copy(src, dst, 10);
}

void mode_allmap_0(s32 a) {
    sAllmapLowerBgm = 0;

    if (a == 1) {
        sAllmapLowerBgm = a;
    }

    SetObjPaletteRange(0, 14);
    ClearStockMesDispWork();
    SetBgMode0();
    SetupBg(3, 1, 28, 8);
    SetBgPriority(3, 3);
#ifdef VERSION_EU
    LoadBgTiles(3, gUnk_097B62B8, 0x1A40);
#else
    LoadBgTiles(3, gUnk_097B62B8, 0xF60);
#endif
    LoadBgPalette(3, gUnk_09849F78, 0x100);
    LoadBgMap(3, gUnk_0983AD98, 0x500);
    SetupBg(2, 1, 29, 8);
    SetBgPriority(2, 0);
    LoadBgMap(2, gUnk_08125E24, 0x200);
    AllmapLoadWorldBg();
    AllmapLoadFloorTiles();
    SetupBg(0, 0, 26, 0);
    SetBgPriority(0, 2);
    LoadBgTiles(0, gUnk_0976B340, 0x2400);
    LoadBgPalette(0, gUnk_0984A0F8, 0xE0);
    AllmapAllocBgMaps();
    SetBgMapBlocks(0, gAllmapBg0MapBlocks, 2, 4);
    SetupBg(1, 0, 27, 0);
    SetBgPriority(1, 2);
    SetBgMapBlocks(1, gAllmapBg1MapBlocks, 2, 4);
    TaskPoolInit(&gAllmapTaskPool, 1);
    TaskCreate(&gAllmapTaskPool, &gTaskDescAllmapBar, 0);
    gAllmapModeState = 0;
    InitAllmap();
    REG_IME = 0;
    REG_IE |= INTR_FLAG_VCOUNT;
    REG_DISPSTAT &= 0xFF;
    REG_DISPSTAT |= DISPSTAT_VCOUNT_SETTING(80) | DISPSTAT_VCOUNT_INTR;
    SetVCountCallback(AllmapVCountCallback);
    REG_IME = 1;
    FadeStartIn(FADE_MODE_BLACK, 16);

    if (sAllmapLowerBgm != 0) {
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, 0xFF, 0x80);
    }

    gAllmapScrollInTimer = 30;
    gAllmapCursorDropTimer = 30;
    sAllmapPalTimer = 0;
    sAllmapPalStep = 0;
}

void func_080D3370(void) {
    FadeSetPaletteExcluded(10, 1);
    CpuSet(gUnk_05000140, sUnk_02034E40, 16);
    LoadPalette(sUnk_02034E40, gUnk_05000140, 32);
}

void mode_allmap_1(void) {
    UpdatePlayTime();
    TaskPoolUpdate(&gAllmapTaskPool);
    TaskPoolDraw(&gAllmapTaskPool);

    if (gAllmapModeState == 0 && !FadeIsActive()) {
        if (gAllmapScrollInTimer != 0 && gAllmapCursorDropTimer != 0) {
            gAllmapModeState = 1;
            sAllmapBlendTimer = 16;
        } else {
            ReturnToMap(sAllmapReturnToMenu);
        }
    }

    if (gAllmapModeState == 2) {
        if (gAllmapScrollInTimer != 0) {
            gAllmapScrollInTimer--;
        }

        if (gAllmapCursorDropTimer != 0) {
            gAllmapCursorDropTimer--;
        }

        if (sAllmapBlendTimer > 0) {
            if (sAllmapBlendTimer == 16) {
                AllmapDimPalette10();
            }

            sAllmapBlendTimer--;
            AllmapSetBlend(sAllmapBlendTimer);

            if (sAllmapBlendTimer == 0) {
                func_080D3370();
            }
        }

        if (gAllmapScrollInTimer == 0 && gAllmapCursorDropTimer == 0) {
            gAllmapModeState = 3;
        }
    }

    AllmapCyclePalette();

    if (gAllmapModeState == 2 || gAllmapModeState == 3) {
        EnableBg(0);
        EnableBg(1);
        UpdateAllmap();
    } else {
        DisableBg(0);
        DisableBg(1);
    }
}

void mode_allmap_2(void) {
    DestroyAllmap();
    TaskPoolDestroy(&gAllmapTaskPool);
    REG_IME = 0;
    REG_IE &= ~INTR_FLAG_VCOUNT;
    REG_DISPSTAT &= ~DISPSTAT_VCOUNT_INTR;
    REG_IME = 1;
    ResetVCountCallback();

    if (sAllmapLowerBgm != 0) {
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, 0xFF, 0x100);
    }

    EwramFree(gAllmapBg0Map);
    EwramFree(gAllmapBg1Map);
}

void SetAllmapReturnToMenu(u8 a) {
    sAllmapReturnToMenu = a;
}

u8 func_080D3538(u8 a, u8 b) {
    u8* p = GetMapRoomLinks(a);

    if ((u8)(p[b] + 3) <= 1) {
        return 1;
    }

    return 0;
}

u8 func_080D3564(u8 a, u8 b) {
    u16 v = GetMapDoorFlags(a, b);

    if (v == 0 || (v & 8) != 0) {
        return 0;
    }

    return 1;
}

u8 func_080D358C(u8 a, u8 b) {
    u16 v = GetMapDoorFlags(a, b);

    if ((v & 2) != 0) {
        return 1;
    }

    return 0;
}

s32 SetupAllmapRoomDoors(AllmapRoomWork* work) {
    AllmapRoomOrder order = sAllmapRoomOrder;
    AllmapRoomDirs dirs = sAllmapRoomDirs;
    u32 mask;
    u8 i;

    for (i = 0; i < 4; i++) {
        work->gfx[i] = 0;
        work->tiles2[i] = 0;
    }

    if (GetEventRoomKind(work->room) == 1 || GetEventRoomKind(work->room) == 4) {
        if (TestAllmapRoomFlag(work->room, FLOOR_ROOM_FLAG_EVENT_DONE) != 0) {
            return 17;
        }

        if (TestAllmapRoomFlag(work->room, FLOOR_ROOM_FLAG_VISITED) == 0) {
            return 1;
        }
    } else if (TestAllmapRoomFlag(work->room, FLOOR_ROOM_FLAG_VISITED) == 0) {
        return 0;
    }

    mask = 0;

    for (i = 0; i < 4; i++) {
        if (func_080D3564(work->room, i) == 0) {
            continue;
        }

        mask += 1 << i;

        if (func_080D3538(work->room, i) != 0) {
            AnimInit(&work->anim[i], gUnk_09EF653C, gUnk_09EF64FC);
            AnimStart(&work->anim[i], dirs.animIds[i], ANIM_FLAG_LOOP);
            work->gfx[i] = AnimGetGfx(&work->anim[i]);

            if (work->asSprite == 0) {
                work->tiles2[i] = LoadObjTiles(gUnk_0976DEDC, 0x500);
            } else {
                work->tiles2[i] = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF64FC, 16), gUnk_0976DEDC);
            }
        } else if (func_080D358C(work->room, i) == 0) {
            AnimInit(&work->anim[i], gUnk_09EF658C, gUnk_09EF654C);
            AnimStart(&work->anim[i], dirs.animIds[i], ANIM_FLAG_LOOP);
            work->gfx[i] = AnimGetGfx(&work->anim[i]);

            if (work->asSprite == 0) {
                work->tiles2[i] = LoadObjTiles(gUnk_0976E4D4, 0x500);
            } else {
                work->tiles2[i] = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF654C, 16), gUnk_0976E4D4);
            }
        }
    }

    return order.shapes[mask] + 1;
}

s32 GetAllmapRoomPaletteOffset(u8 a) {
    u8 r = 0;

    if (GetEventRoomKind(a) == 1 || GetEventRoomKind(a) == 4) {
        r = 1;
    }

    return r << 5;
}
