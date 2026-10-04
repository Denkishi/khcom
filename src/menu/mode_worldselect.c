/**
 * mode_worldselect.c
 * World Select Screen
 */

#include "system_state.h"
#include "map_api.h"
#include "msg_api.h"
#include "display.h"
#include "fade.h"
#include "mode_worldselect.h"
#include "worldinspect_assets.h"
#include "sprites_bos5.h"
#include "sprites_worldinspect.h"
#include "gba/keys.h"
#include "gba/io_reg.h"
#include "malloc.h"
#include "songs.h"
#include "worldselect_assets.h"
#include "jiminy_records_assets.h"
#include "world_types.h"
#include "bg_animation_data.h"
#include "card_api.h"
#include "engine_math.h"
#include "game_state.h"
#include "gba/defines.h"
#include "key.h"
#include "m4a_song.h"
#include "map_runtime.h"
#include "mode.h"
#include "obj.h"
#include "obj_api.h"
#include "poo_api.h"
#include "taskpool.h"
#include "types.h"
#include "gba/macro.h"
#include <stddef.h>

#ifdef VERSION_EU
static void* sWorldselectBg1Maps[5] = {
    gUnk_09A31FDC,
    gUnkEu_09A840A0,
    gUnkEu_09A84FA0,
    gUnkEu_09A84AA0,
    gUnkEu_09A845A0,
};

static void* sWorldselectNameTileData[5] = {
    gUnk_099F4D3C,
    gUnkEu_09A0A480,
    gUnkEu_09A1DC80,
    gUnkEu_09A17480,
    gUnkEu_09A10C80,
};

static void* sWorldselectTitleGfx[5] = {
    gUnk_0999CB90,
    gUnkEu_099A31F4,
    gUnkEu_099A3DF4,
    gUnkEu_099A39CC,
    gUnkEu_099A35E0,
};

static void* sWorldselectTitleTileData[5] = {
    gUnk_0999CBB6,
    gUnkEu_099A3220,
    gUnkEu_099A3E1A,
    gUnkEu_099A39F2,
    gUnkEu_099A360C,
};
#endif

static void* sWorldselectPaletteCycle[30] = {
    gUnk_09A3CA3C,
    gUnk_09A3CA5C,
    gUnk_09A3CA7C,
    gUnk_09A3CA9C,
    gUnk_09A3CABC,
    gUnk_09A3CADC,
    gUnk_09A3CAFC,
    gUnk_09A3CB1C,
    gUnk_09A3CB3C,
    gUnk_09A3CB5C,
    gUnk_09A3CB7C,
    gUnk_09A3CB9C,
    gUnk_09A3CBBC,
    gUnk_09A3CBDC,
    gUnk_09A3CBFC,
    gUnk_09A3CC1C,
    gUnk_09A3CBFC,
    gUnk_09A3CBDC,
    gUnk_09A3CBBC,
    gUnk_09A3CB9C,
    gUnk_09A3CB7C,
    gUnk_09A3CB5C,
    gUnk_09A3CB3C,
    gUnk_09A3CB1C,
    gUnk_09A3CAFC,
    gUnk_09A3CADC,
    gUnk_09A3CABC,
    gUnk_09A3CA9C,
    gUnk_09A3CA7C,
    gUnk_09A3CA5C,
};

#ifdef VERSION_EU
static const WorldselectTileSizes sWorldselectTitleTileSizes = { { 896, 960, 1024, 1024, 960 } };
#endif

static const WorldselectWorldDef sWorldselectWorldDefs[13] = {
#ifdef VERSION_EU
    { 1, WORLD_AGRABAH, 107, -1, gUnk_09A3CD1C, gUnk_099E7E7C, gUnk_099A8824, sWorldselectNameTileData, 8192, 0 },
#else
    { 1, WORLD_AGRABAH, 107, -1, gUnk_09A3CD1C, gUnk_099E7E7C, gUnk_099A8824, gUnk_099F6D3C },
#endif
#ifdef VERSION_EU
    { 2, WORLD_ATLANTICA, 101, -1, gUnk_09A3CD5C, gUnk_099E9E7C, gUnk_099A8880, sWorldselectNameTileData, 12288, 0 },
#else
    { 2, WORLD_ATLANTICA, 101, -1, gUnk_09A3CD5C, gUnk_099E9E7C, gUnk_099A8880, gUnk_099F7D3C },
#endif
#ifdef VERSION_EU
    { 4, WORLD_OLYMPUS_COLISEUM, 120, -1, gUnk_09A3CCFC, gUnk_099E6E7C, gUnk_099A87F8, sWorldselectNameTileData, 6144, 0 },
#else
    { 4, WORLD_OLYMPUS_COLISEUM, 120, -1, gUnk_09A3CCFC, gUnk_099E6E7C, gUnk_099A87F8, gUnk_099F653C },
#endif
#ifdef VERSION_EU
    { 8, WORLD_WONDERLAND, 94, -1, gUnk_09A3CC9C, gUnk_099E3E7C, gUnk_099A8758, sWorldselectNameTileData, 0, 0 },
#else
    { 8, WORLD_WONDERLAND, 94, -1, gUnk_09A3CC9C, gUnk_099E3E7C, gUnk_099A8758, gUnk_099F4D3C },
#endif
#ifdef VERSION_EU
    { 16, WORLD_MONSTRO, 74, -1, gUnk_09A3CD3C, gUnk_099E8E7C, gUnk_099A884C, sWorldselectNameTileData, 10240, 0 },
#else
    { 16, WORLD_MONSTRO, 74, -1, gUnk_09A3CD3C, gUnk_099E8E7C, gUnk_099A884C, gUnk_099F753C },
#endif
#ifdef VERSION_EU
    { 32, WORLD_HALLOWEEN_TOWN, 87, -1, gUnk_09A3CD7C, gUnk_099EAE7C, gUnk_099A88A0, sWorldselectNameTileData, 14336, 0 },
#else
    { 32, WORLD_HALLOWEEN_TOWN, 87, -1, gUnk_09A3CD7C, gUnk_099EAE7C, gUnk_099A88A0, gUnk_099F853C },
#endif
#ifdef VERSION_EU
    { 64, WORLD_NEVER_LAND, 115, -1, gUnk_09A3CD9C, gUnk_099EBE7C, gUnk_099A88D4, sWorldselectNameTileData, 16384, 0 },
#else
    { 64, WORLD_NEVER_LAND, 115, -1, gUnk_09A3CD9C, gUnk_099EBE7C, gUnk_099A88D4, gUnk_099F8D3C },
#endif
#ifdef VERSION_EU
    { 128, WORLD_HOLLOW_BASTION, 127, 149, gUnk_09A3CE1C, gUnk_099EEE7C, gUnk_099A8930, sWorldselectNameTileData, 20480, 0 },
#else
    { 128, WORLD_HOLLOW_BASTION, 129, 151, gUnk_09A3CE1C, gUnk_099EEE7C, gUnk_099A8930, gUnk_099F9D3C },
#endif
#ifdef VERSION_EU
    { 256, WORLD_DESTINY_ISLANDS, 53, 175, gUnk_09A3CCBC, gUnk_099E4E7C, gUnk_099A8780, sWorldselectNameTileData, 2048, 0 },
#else
    { 256, WORLD_DESTINY_ISLANDS, 53, 177, gUnk_09A3CCBC, gUnk_099E4E7C, gUnk_099A8780, gUnk_099F553C },
#endif
#ifdef VERSION_EU
    { 512, WORLD_TRAVERSE_TOWN, 1, -1, gUnk_09A3CCDC, gUnk_099E5E7C, gUnk_099A87C0, sWorldselectNameTileData, 4096, 0 },
#else
    { 512, WORLD_TRAVERSE_TOWN, 1, -1, gUnk_09A3CCDC, gUnk_099E5E7C, gUnk_099A87C0, gUnk_099F5D3C },
#endif
#ifdef VERSION_EU
    { 2048, WORLD_TWILIGHT_TOWN, 44, 184, gUnk_09A3CE3C, gUnk_099EFE7C, gUnk_099A895C, sWorldselectNameTileData, 22528, 0 },
#else
    { 2048, WORLD_TWILIGHT_TOWN, 44, 186, gUnk_09A3CE3C, gUnk_099EFE7C, gUnk_099A895C, gUnk_099FA53C },
#endif
#ifdef VERSION_EU
    { 4096, WORLD_CASTLE_OBLIVION, 61, 190, gUnk_09A3CE5C, gUnk_099F0E7C, gUnk_099A897C, sWorldselectNameTileData, 24576, 0 },
#else
    { 4096, WORLD_CASTLE_OBLIVION, 61, 192, gUnk_09A3CE5C, gUnk_099F0E7C, gUnk_099A897C, gUnk_099FAD3C },
#endif
#ifdef VERSION_EU
    { 1024, WORLD_100_ACRE_WOOD, 132, -1, gUnk_09A3CDBC, gUnk_099ECE7C, gUnk_099A8900, sWorldselectNameTileData, 18432, 0 },
#else
    { 1024, WORLD_100_ACRE_WOOD, 134, -1, gUnk_09A3CDBC, gUnk_099ECE7C, gUnk_099A8900, gUnk_099F953C },
#endif
};

Mode gModeWorldselect = {
    "mode_worldselect",
    (ModeInitFunc)mode_worldselect_0,
    mode_worldselect_1,
    mode_worldselect_2,
};

static s16 sWorldselectCursor;
static WorldselectSlot sWorldselectSlots[5];
static s16 sWorldselectWorlds[14];
static u32 sWorldselectRotation;
static s16 sWorldselectSlotCount;
static s16 sWorldselectWorldCount;
static void* sWorldselectCardTiles[2];
static void* sWorldselectCardPalettes[2];
static struct ObjTiles* sWorldselectTitleTiles;
static struct ObjPalette* sWorldselectOverlayPalette;
static struct ObjTiles* sWorldselectFrameTiles;
static u8 sWorldselectBobPhase;
static s16 sWorldselectNameMode;
static s16 sWorldselectNameWidth;
static s16 sWorldselectNameWorld;
static void* sWorldselectNameBuffer;
static s16 sWorldselectStep;
static s16 sWorldselectTimer;
static s32 sWorldselectFrameY[2];
static s32 sWorldselectTitleX;
static TaskPool sWorldselectTaskPool;
static s16 sWorldselectTutorialStep;
static u8 sWorldselectFirstVisit;
static u8 sWorldselectBgAnimActive;
static u8 sWorldselectCancelled;
static s16 sWorldselectPaletteTimer;
static u16 sWorldselectPaletteFrame;

void WorldselectLoadSlotPalette(s16 model, s16 slot) {
    void* src;
    s32 size;

    if (sWorldselectWorldDefs[model].world == WORLD_100_ACRE_WOOD && IsPooAltImageActive()) {
        src = gUnk_09A3CDDC;
        size = 0x40;
    } else {
        src = sWorldselectWorldDefs[model].palette;
        size = 0x20;
    }

    sWorldselectSlots[slot].palette = LoadObjPalette(src, size);
}

void WorldselectLoadSlotTiles(s16 model, s16 slot) {
    void* src;

    if (sWorldselectWorldDefs[model].world == WORLD_100_ACRE_WOOD && IsPooAltImageActive()) {
        src = gUnk_099EDE7C;
    } else {
        src = sWorldselectWorldDefs[model].tiles;
    }

    sWorldselectSlots[slot].tiles = LoadObjTiles(src, 0x1000);
}

s16 WorldselectSetSlotGfx(s16 model, s16 slot) {
    if (sWorldselectWorldDefs[model].world == WORLD_100_ACRE_WOOD && IsPooAltImageActive()) {
        sWorldselectSlots[slot].gfx = gUnk_099A8914;
    } else {
        sWorldselectSlots[slot].gfx = sWorldselectWorldDefs[model].gfx;
    }
}

void WorldselectDrawName(s16 model, s16 n) {
    u8* src;
    u8* src2;

    DmaFill16(3, 0, sWorldselectNameBuffer, 0x6C0);

    if (n > 0) {
#ifdef VERSION_EU
        src = ((u8**)sWorldselectWorldDefs[model].nameTiles)[gLanguage];
        src += sWorldselectWorldDefs[model].nameTilesOffset;
#else
        src = sWorldselectWorldDefs[model].nameTiles;
#endif
        DmaCopy16(3, src, (u8*)sWorldselectNameBuffer + (9 - n) * 32, n * 32);
        src2 = src + (18 - n) * 32;
        DmaCopy16(3, src2, (u8*)sWorldselectNameBuffer + 288, n * 32);
        DmaCopy16(3, src + 576, (u8*)sWorldselectNameBuffer + (9 - n) * 32 + 576, n * 32);
        DmaCopy16(3, src2 + 576, (u8*)sWorldselectNameBuffer + 864, n * 32);
        DmaCopy16(3, src + 1152, (u8*)sWorldselectNameBuffer + (9 - n) * 32 + 1152, n * 32);
        DmaCopy16(3, src2 + 1152, (u8*)sWorldselectNameBuffer + 1440, n * 32);
    }

    RequestDma3Copy(sWorldselectNameBuffer, (u8*)GetBgCharBase(0) + 1024, 0x6C0);
}

void WorldselectHandleInput() {
    s16 i;
    s16 j;
    s16 k;
    u8 step;

    switch (sWorldselectRotation) {
    case 0:
        if (GetKeysPressed() & A_BUTTON) {
            BgAnimInit(2, 0x8000, 128);
            BgAnimStart(&gBgAnimDefWorldStart, 112, 126);
            SetBgPriority(2, 1);
            gBldCnt |= BLDCNT_TGT2_OBJ;
            sWorldselectBgAnimActive = 1;
            m4aSongNumStart(SONG_SYS_WORLDSTART);
            sWorldselectCancelled = 0;
            sWorldselectStep = 4;
        } else if ((GetKeysPressed() & B_BUTTON) && sWorldselectFirstVisit == 0) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            LoadBgMap(0, gUnk_09A310DC, 0x500);
            LoadBgMap(1, gUnk_09A31ADC, 0x500);
            sWorldselectCancelled = 1;
            sWorldselectTimer = 16;
            sWorldselectStep = 5;
        } else if (sWorldselectSlotCount > 1) {
            if (GetKeysHeld() & DPAD_LEFT) {
                j = sWorldselectCursor - sWorldselectSlotCount / 2;

                while (j < 0) {
                    j += sWorldselectSlotCount;
                }

                ReleaseObjPalette(sWorldselectSlots[j].palette);
                ReleaseObjTiles(sWorldselectSlots[j].tiles);
                k = sWorldselectSlots[sWorldselectCursor].listIndex - sWorldselectSlotCount / 2;

                while (k < 0) {
                    k += sWorldselectWorldCount;
                }

                sWorldselectSlots[j].listIndex = k;
                WorldselectLoadSlotPalette(sWorldselectWorlds[k], j);
                WorldselectLoadSlotTiles(sWorldselectWorlds[k], j);
                WorldselectSetSlotGfx(sWorldselectWorlds[k], j);
                sWorldselectCursor--;

                if (sWorldselectCursor < 0) {
                    sWorldselectCursor = sWorldselectSlotCount - 1;
                }

                m4aSongNumStart(SONG_SYS_WORLDSELECT);
                sWorldselectNameMode = 2;
                sWorldselectRotation = 2;
            } else if (GetKeysHeld() & DPAD_RIGHT) {
                j = sWorldselectCursor + sWorldselectSlotCount / 2;

                while (j >= sWorldselectSlotCount) {
                    j -= sWorldselectSlotCount;
                }

                ReleaseObjPalette(sWorldselectSlots[j].palette);
                ReleaseObjTiles(sWorldselectSlots[j].tiles);
                k = sWorldselectSlots[sWorldselectCursor].listIndex + sWorldselectSlotCount / 2;

                while (k >= sWorldselectWorldCount) {
                    k -= sWorldselectWorldCount;
                }

                sWorldselectSlots[j].listIndex = k;
                WorldselectLoadSlotPalette(sWorldselectWorlds[k], j);
                WorldselectLoadSlotTiles(sWorldselectWorlds[k], j);
                WorldselectSetSlotGfx(sWorldselectWorlds[k], j);
                sWorldselectCursor++;

                if (sWorldselectCursor >= sWorldselectSlotCount) {
                    sWorldselectCursor = 0;
                }

                m4aSongNumStart(SONG_SYS_WORLDSELECT);
                sWorldselectNameMode = 2;
                sWorldselectRotation = 1;
            }
        }

        break;
    case 1:
        if (GetKeysHeld() & DPAD_LEFT) {
            j = sWorldselectCursor - sWorldselectSlotCount / 2;

            while (j < 0) {
                j += sWorldselectSlotCount;
            }

            ReleaseObjPalette(sWorldselectSlots[j].palette);
            ReleaseObjTiles(sWorldselectSlots[j].tiles);
            k = sWorldselectSlots[sWorldselectCursor].listIndex - sWorldselectSlotCount / 2;

            while (k < 0) {
                k += sWorldselectWorldCount;
            }

            sWorldselectSlots[j].listIndex = k;
            WorldselectLoadSlotPalette(sWorldselectWorlds[k], j);
            WorldselectLoadSlotTiles(sWorldselectWorlds[k], j);
            WorldselectSetSlotGfx(sWorldselectWorlds[k], j);
            sWorldselectCursor--;

            if (sWorldselectCursor < 0) {
                sWorldselectCursor = sWorldselectSlotCount - 1;
            }

            m4aSongNumStart(SONG_SYS_WORLDSELECT);
            sWorldselectRotation = 2;
        } else {
            for (i = 0; i < sWorldselectSlotCount; i++) {
                sWorldselectSlots[i].angle -= 2;
            }

            if (sWorldselectSlots[sWorldselectCursor].angle <= 128) {
                if (GetKeysHeld() & DPAD_RIGHT) {
                    j = sWorldselectCursor + sWorldselectSlotCount / 2;

                    while (j >= sWorldselectSlotCount) {
                        j -= sWorldselectSlotCount;
                    }

                    ReleaseObjPalette(sWorldselectSlots[j].palette);
                    ReleaseObjTiles(sWorldselectSlots[j].tiles);
                    k = sWorldselectSlots[sWorldselectCursor].listIndex + sWorldselectSlotCount / 2;

                    while (k >= sWorldselectWorldCount) {
                        k -= sWorldselectWorldCount;
                    }

                    sWorldselectSlots[j].listIndex = k;
                    WorldselectLoadSlotPalette(sWorldselectWorlds[k], j);
                    WorldselectLoadSlotTiles(sWorldselectWorlds[k], j);
                    WorldselectSetSlotGfx(sWorldselectWorlds[k], j);
                    sWorldselectCursor++;

                    if (sWorldselectCursor >= sWorldselectSlotCount) {
                        sWorldselectCursor = 0;
                    }

                    m4aSongNumStart(SONG_SYS_WORLDSELECT);
                    sWorldselectRotation = 1;
                } else {
                    step = 128 - sWorldselectSlots[sWorldselectCursor].angle;

                    for (i = 0; i < sWorldselectSlotCount; i++) {
                        sWorldselectSlots[i].angle += step;
                    }

                    sWorldselectNameMode = 1;
                    sWorldselectNameWorld = sWorldselectWorlds[sWorldselectSlots[sWorldselectCursor].listIndex];
                    sWorldselectRotation = 0;
                }
            }
        }

        break;
    case 2:
        if (GetKeysHeld() & DPAD_RIGHT) {
            j = sWorldselectCursor + sWorldselectSlotCount / 2;

            while (j >= sWorldselectSlotCount) {
                j -= sWorldselectSlotCount;
            }

            ReleaseObjPalette(sWorldselectSlots[j].palette);
            ReleaseObjTiles(sWorldselectSlots[j].tiles);
            k = sWorldselectSlots[sWorldselectCursor].listIndex + sWorldselectSlotCount / 2;

            while (k >= sWorldselectWorldCount) {
                k -= sWorldselectWorldCount;
            }

            sWorldselectSlots[j].listIndex = k;
            WorldselectLoadSlotPalette(sWorldselectWorlds[k], j);
            WorldselectLoadSlotTiles(sWorldselectWorlds[k], j);
            WorldselectSetSlotGfx(sWorldselectWorlds[k], j);
            sWorldselectCursor++;

            if (sWorldselectCursor >= sWorldselectSlotCount) {
                sWorldselectCursor = 0;
            }

            m4aSongNumStart(SONG_SYS_WORLDSELECT);
            sWorldselectRotation = 1;
        } else {
            for (i = 0; i < sWorldselectSlotCount; i++) {
                sWorldselectSlots[i].angle += 2;
            }

            if ((s8)sWorldselectSlots[sWorldselectCursor].angle < 0) {
                if (GetKeysHeld() & DPAD_LEFT) {
                    j = sWorldselectCursor - sWorldselectSlotCount / 2;

                    while (j < 0) {
                        j += sWorldselectSlotCount;
                    }

                    ReleaseObjPalette(sWorldselectSlots[j].palette);
                    ReleaseObjTiles(sWorldselectSlots[j].tiles);
                    k = sWorldselectSlots[sWorldselectCursor].listIndex - sWorldselectSlotCount / 2;

                    while (k < 0) {
                        k += sWorldselectWorldCount;
                    }

                    sWorldselectSlots[j].listIndex = k;
                    WorldselectLoadSlotPalette(sWorldselectWorlds[k], j);
                    WorldselectLoadSlotTiles(sWorldselectWorlds[k], j);
                    WorldselectSetSlotGfx(sWorldselectWorlds[k], j);
                    sWorldselectCursor--;

                    if (sWorldselectCursor < 0) {
                        sWorldselectCursor = sWorldselectSlotCount - 1;
                    }

                    m4aSongNumStart(SONG_SYS_WORLDSELECT);
                    sWorldselectRotation = 2;
                } else {
                    step = sWorldselectSlots[sWorldselectCursor].angle + 128;

                    for (i = 0; i < sWorldselectSlotCount; i++) {
                        sWorldselectSlots[i].angle -= step;
                    }

                    sWorldselectNameMode = 1;
                    sWorldselectNameWorld = sWorldselectWorlds[sWorldselectSlots[sWorldselectCursor].listIndex];
                    sWorldselectRotation = 0;
                }
            }
        }

        break;
    }
}

void WorldselectDraw() {
    s16 i;
    ObjAffine* sprite;
    s16 x;
    s16 y;
    u8 ang;
    u8 t;
    s32 s;
    s32 h;
    s32 d;
    s32 w;
    s32 v;
    s16 angle;
    void* anim;
    void* tiles;
    void* pal;

    if (sWorldselectStep < 2 || sWorldselectStep > 4) {
        DrawSprite(sWorldselectTitleX >> 8, 0,
#ifdef VERSION_EU
                      sWorldselectTitleGfx[gLanguage],
#else
                      gUnk_0999CB90,
#endif
                      sWorldselectTitleTiles, sWorldselectOverlayPalette, NULL, SPRITE_PRIORITY(1),
                      0x3E8);
        DrawSprite(120, sWorldselectFrameY[0] >> 8, gUnk_0999C394, sWorldselectFrameTiles, sWorldselectOverlayPalette, NULL,
                      SPRITE_PRIORITY(1), 0x3E9);
        DrawSprite(120, sWorldselectFrameY[1] >> 8, gUnk_0999C3C8, sWorldselectFrameTiles, sWorldselectOverlayPalette, NULL,
                      SPRITE_PRIORITY(3), 0xBBA);
    }

    for (i = 0; i < sWorldselectSlotCount; i++) {
        ang = sWorldselectSlots[i].angle;
        s = -gSineTable[((256 / sWorldselectSlotCount * i + sWorldselectBobPhase) & 0xFF) + 64];
        t = (s * 3 >> 7) + ang;

        if ((u8)(t - 62) > 2 && (u8)(t + 64) > 2) {
            h = -gSineTable[ang + 64] * 5 >> 5;
            d = -25600 / (h - 140);
            w = -gSineTable[t + 64] * d >> 8;
            angle = ang;
            x = (gSineTable[angle] * 5 >> 4) + 120;
            v = ((d << 3) * s >> 16) + 64;
            y = h + v;

            if ((u8)(t - 121) <= 14) {
                sprite = NULL;
                tiles = sWorldselectCardTiles[0];
                pal = sWorldselectCardPalettes[0];
                anim = gUnk_0999A350;

                if (sWorldselectStep > 3 && !sWorldselectCancelled) {
                    BgAnimSetPosition(x - 1, y - 5);
                }
            } else if (t <= 61) {
                sprite = NULL;
                tiles = sWorldselectCardTiles[1];
                pal = sWorldselectCardPalettes[1];
                anim = gUnk_09EF9770[(62 - t) / 13];
            } else if (t > 194) {
                sprite = NULL;
                tiles = sWorldselectCardTiles[1];
                pal = sWorldselectCardPalettes[1];
                anim = gUnk_09EF9770[(t - 194) / 13];
            } else {
                sprite = AllocObjAffine(0, w, d, 0);
                tiles = sWorldselectCardTiles[0];
                pal = sWorldselectCardPalettes[0];
                anim = gUnk_0999A350;
            }

            DrawSprite(x, y, anim, tiles, pal, sprite, SPRITE_PRIORITY(2),
                          ang > 128 ? (u16)(ang * 2 + 0x6D1) : (u16)((128 - ang) * 2 + 0x7D1));

            if ((u8)(t - 65) <= 126) {
                DrawSprite(x, y, sWorldselectSlots[i].gfx, sWorldselectSlots[i].tiles,
                              sWorldselectSlots[i].palette, sprite, SPRITE_PRIORITY(2),
                              ang > 128 ? (u16)(ang * 2 + 0x6D0)
                                        : (u16)((128 - ang) * 2 + 0x7D0));
            }
        }
    }

    switch (sWorldselectNameMode) {
    case 1:
        WorldselectDrawName(sWorldselectNameWorld, sWorldselectNameWidth);

        if (sWorldselectNameWidth <= 8) {
            sWorldselectNameWidth++;
        } else {
            sWorldselectNameMode = 0;
        }

        break;
    case 2:
        WorldselectDrawName(sWorldselectNameWorld, sWorldselectNameWidth);

        if (sWorldselectNameWidth > 0) {
            sWorldselectNameWidth--;
        } else {
            sWorldselectNameMode = 0;
        }

        break;
    }

    if (sWorldselectBgAnimActive) {
        BgAnimUpdate();
    }

    TaskPoolDraw(&sWorldselectTaskPool);
}

void WorldselectSetBgMode0() {
    SetBgMode0();
    SetupBg(0, 0, 28, 0);
    SetupBg(1, 0, 29, 0);
    SetupBg(2, 1, 30, 14);
    SetBgPriority(0, 3);
    SetBgPriority(1, 1);
    SetBgPriority(2, 0);
}

void WorldselectSetBgMode1() {
    SetBgMode1();
    SetupBg(0, 0, 28, 0);
    SetupBg(1, 0, 29, 0);
    SetupBg(2, 1, 30, 10);
    SetBgPriority(0, 3);
    SetBgPriority(1, 0);
    SetBgPriority(2, 2);
    gBldCnt = (BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1);
    gBldAlpha = BLDALPHA_BLEND(16, 16);
}

void WorldselectCyclePalette() {
    sWorldselectPaletteTimer++;

    if (sWorldselectPaletteTimer > 6) {
        sWorldselectPaletteTimer = 0;
        sWorldselectPaletteFrame++;

        if (sWorldselectPaletteFrame > 29) {
            sWorldselectPaletteFrame = 0;
        }

        LoadPalette(sWorldselectPaletteCycle[(s16)sWorldselectPaletteFrame], (void*)(BG_PLTT + 2 * PLTT_SIZE_4BPP), 32);
    }
}

void mode_worldselect_0() {
    s16 i;
    s16 j;
    void** p;

    SpriteReset();
    sWorldselectFirstVisit = (gGameState.progression.tutorialFlags ^ 1) & 1;
    sWorldselectBgAnimActive = 0;
    sWorldselectCancelled = 0;
    FadeStartIn(FADE_MODE_ADD_WHITE, 16);

    if (sWorldselectFirstVisit != 0) {
        WorldselectSetBgMode0();
    } else {
        WorldselectSetBgMode1();
    }

    sWorldselectCursor = 0;
    sWorldselectRotation = 0;
    j = 0;

    for (i = 0; i <= 12; i++) {
        if (gGameState.availableWorlds & sWorldselectWorldDefs[i].worldBit) {
            sWorldselectWorlds[j] = i;
            j++;
        }
    }

    sWorldselectWorldCount = j;
    sWorldselectSlotCount = j > 5 ? 5 : j;
    j = 0;

    for (i = 0; i < sWorldselectSlotCount; i++, j++) {
        if (j >= sWorldselectWorldCount) {
            j = 0;
        }

        if (i == sWorldselectSlotCount - 1 && sWorldselectSlotCount > 2) {
            j = sWorldselectWorldCount - 1;
        }

        sWorldselectSlots[i].listIndex = j;
        sWorldselectSlots[i].angle = 256 / sWorldselectSlotCount * i - 128;
        WorldselectLoadSlotPalette(sWorldselectWorlds[j], i);
        WorldselectLoadSlotTiles(sWorldselectWorlds[j], i);
        WorldselectSetSlotGfx(sWorldselectWorlds[j], i);
    }

    sWorldselectBobPhase = 0;
    sWorldselectNameMode = 1;
    sWorldselectNameWidth = 0;
    sWorldselectNameWorld = sWorldselectWorlds[sWorldselectSlots[sWorldselectCursor].listIndex];
    p = &sWorldselectNameBuffer;
    *p = EwramAlloc(0x6C0);
    sWorldselectPaletteTimer = 0;
    sWorldselectPaletteFrame = 0;
    sWorldselectStep = 0;
    sWorldselectTimer = 16;
    sWorldselectFrameY[0] = -2048;
    sWorldselectFrameY[1] = 0xA800;
    sWorldselectTitleX = -32768;
    LoadBgPalette(0, gUnk_09A3C9DC, 96);
#ifdef VERSION_EU
    LoadBgTiles(0, gUnk_099F1E7C, 16000);
#else
    LoadBgTiles(0, gUnk_099F1E7C, 11968);
#endif
    WorldselectDrawName(sWorldselectNameWorld, sWorldselectNameWidth);
    LoadBgMap(0, gUnk_09A310DC, 0x500);
    LoadBgMap(1, gUnk_09A31ADC, 0x500);

    if (sWorldselectFirstVisit == 0) {
        BgAnimInit(2, 0x8000, 128);
        BgAnimStart(&gBgAnimDefWorldSelect, 120, 110);
        BgAnimSetLoopStartFrame(0);
        sWorldselectBgAnimActive = 1;
    }

    sWorldselectCardPalettes[0] = LoadObjPalette(gUnk_09A3CC3C, 32);
    sWorldselectCardTiles[0] = LoadObjTiles(gUnk_0999A394, 0xC40);
    sWorldselectCardPalettes[1] = LoadObjPalette(gUnk_09A3CC5C, 32);
    sWorldselectCardTiles[1] = LoadObjTiles(gUnk_0999B052, 0x1340);
    sWorldselectOverlayPalette = LoadObjPalette(gUnk_09A3CC7C, 32);
#ifdef VERSION_EU
    sWorldselectTitleTiles = LoadObjTiles(sWorldselectTitleTileData[gLanguage], sWorldselectTitleTileSizes.sizes[gLanguage]);
#else
    sWorldselectTitleTiles = LoadObjTiles(gUnk_0999CBB6, 0x380);
#endif
    sWorldselectFrameTiles = LoadObjTiles(gUnk_0999C410, 0x780);
    TaskPoolInit(&sWorldselectTaskPool, 1);
    EnableBg(0);
    EnableBg(1);

    if (sWorldselectFirstVisit != 0) {
        DisableBg(2);
    } else {
        EnableBg(2);
    }
}

void mode_worldselect_1() {
    s16 a;
    s16 b;

    UpdatePlayTime();
    sWorldselectBobPhase += 2;

    switch (sWorldselectStep) {
    case 0:
        ApproachValue(&sWorldselectFrameY[0], 0, sWorldselectTimer);
        ApproachValue(&sWorldselectFrameY[1], 0x9800, sWorldselectTimer);
        sWorldselectTimer--;

        if (sWorldselectTimer <= 0) {
            sWorldselectTimer = 16;
            sWorldselectStep = 1;
        }

        break;
    case 1:
        ApproachValue(&sWorldselectTitleX, 0, sWorldselectTimer);
        sWorldselectTimer--;

        if (sWorldselectTimer <= 0) {
            if (sWorldselectFirstVisit != 0) {
                sWorldselectTutorialStep = 0;
                CreateCardMessageTask(&sWorldselectTaskPool, 2, 70);
                sWorldselectStep = 2;
            } else {
                sWorldselectStep = 3;
            }

            LoadBgMap(0, gUnk_09A315DC, 0x500);
#ifdef VERSION_EU
            LoadBgMap(1, sWorldselectBg1Maps[gLanguage], 0x500);
#else
            LoadBgMap(1, gUnk_09A31FDC, 0x500);
#endif
        }

        break;
    case 2:
        if (!IsMessageWindowOpen()) {
            if (sWorldselectTutorialStep == 0) {
                CreateCardMessageTask(&sWorldselectTaskPool, 2, 71);
                sWorldselectTutorialStep++;
            } else {
                gGameState.progression.tutorialFlags |= 1;
                WorldselectSetBgMode1();
                BgAnimInit(2, 0x8000, 128);
                BgAnimStart(&gBgAnimDefWorldSelect, 120, 110);
                BgAnimSetLoopStartFrame(0);
                sWorldselectBgAnimActive = 1;
                sWorldselectStep = 3;
            }
        }

        break;
    case 3:
        WorldselectHandleInput();
        break;
    case 4:
        if (BgAnimIsStopped()) {
            LoadBgMap(0, gUnk_09A310DC, 0x500);
            LoadBgMap(1, gUnk_09A31ADC, 0x500);
            sWorldselectTimer = 16;
            sWorldselectStep = 5;
        }

        break;
    case 5:
        ApproachValue(&sWorldselectTitleX, -32768, sWorldselectTimer);
        sWorldselectTimer--;

        if (sWorldselectTimer <= 0) {
            sWorldselectTimer = 16;
            sWorldselectStep = 6;
        }

        break;
    case 6:
        ApproachValue(&sWorldselectFrameY[0], -2048, sWorldselectTimer);
        ApproachValue(&sWorldselectFrameY[1], 0xA800, sWorldselectTimer);
        sWorldselectTimer--;

        if (sWorldselectTimer <= 0) {
            sWorldselectStep = 7;
        }

        break;
    case 7:
        FadeLock();

        if (sWorldselectCancelled) {
            FadeStartOut(FADE_MODE_BLACK, 16);
        } else {
            FadeStartOut(FADE_MODE_ADD_WHITE, 16);
        }

        sWorldselectStep = 8;
        break;
    case 8:
        if (!FadeIsActive()) {
            if (sWorldselectCancelled) {
                RequestMapMode();
            } else {
                sWorldselectTimer = 60;
                sWorldselectStep = 9;
            }
        }

        break;
    case 9:
        sWorldselectTimer--;

        if (sWorldselectTimer <= 0) {
            a = sWorldselectWorldDefs[sWorldselectWorlds[sWorldselectSlots[sWorldselectCursor].listIndex]].world;

            if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
                b = sWorldselectWorldDefs[sWorldselectWorlds[sWorldselectSlots[sWorldselectCursor].listIndex]].eventId;
            } else {
                b = sWorldselectWorldDefs[sWorldselectWorlds[sWorldselectSlots[sWorldselectCursor].listIndex]].rikuEventId;
            }

            gGameState.availableWorlds &=
                ~sWorldselectWorldDefs[sWorldselectWorlds[sWorldselectSlots[sWorldselectCursor].listIndex]].worldBit;
            SetFloorWorld(a);

            if (b >= 0) {
                RequestEventMode(b);
            } else {
                if (gGameState.flags & GAME_FLAG_RIKU) {
                    AddMapCard(221);
                }

                EnterFloorWorld();
                RequestMapMode();
            }
        }

        break;
    }

    WorldselectCyclePalette();

    if (FadeIsActive()) {
        FadeGetAmount();
    }

    TaskPoolUpdate(&sWorldselectTaskPool);
    WorldselectDraw();
}

void mode_worldselect_2() {
    s16 i;

    EwramFree(sWorldselectNameBuffer);

    for (i = 0; i < sWorldselectSlotCount; i++) {
        ReleaseObjPalette(sWorldselectSlots[i].palette);
        ReleaseObjTiles(sWorldselectSlots[i].tiles);
    }

    for (i = 0; i < 2; i++) {
        ReleaseObjPalette(sWorldselectCardPalettes[i]);
        ReleaseObjTiles(sWorldselectCardTiles[i]);
    }

    ReleaseObjPalette(sWorldselectOverlayPalette);
    ReleaseObjTiles(sWorldselectTitleTiles);
    ReleaseObjTiles(sWorldselectFrameTiles);
    TaskPoolDestroy(&sWorldselectTaskPool);
}
