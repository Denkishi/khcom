#include "system_state.h"
#include "map_api.h"
#include "msg_api.h"
#include "display.h"
#include "fade.h"
#include "bos5.h"
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

u32 gUnk_02034FEC;
s16 gWorldselectCursor;
u32 gUnk_02034FF4;
WorldselectSlot gWorldselectSlots[5];
s16 gWorldselectWorlds[14];
u32 gWorldselectRotation;
s16 gWorldselectSlotCount;
s16 gWorldselectWorldCount;
u32 gUnk_02035094;
void* gWorldselectCardTiles[2];
void* gWorldselectCardPalettes[2];
struct ObjTiles* gWorldselectTitleTiles;
struct ObjPalette* gWorldselectOverlayPalette;
struct ObjTiles* gWorldselectFrameTiles;
u8 gWorldselectBobPhase;
s16 gWorldselectNameMode;
s16 gWorldselectNameWidth;
s16 gWorldselectNameWorld;
void* gWorldselectNameBuffer;
s16 gWorldselectStep;
s16 gWorldselectTimer;
u32 gUnk_020350C4;
s32 gWorldselectFrameY[2];
s32 gWorldselectTitleX;
u32 gUnk_020350D4;
TaskPool gWorldselectTaskPool;
s16 gWorldselectTutorialStep;
u8 gWorldselectFirstVisit;
u8 gWorldselectBgAnimActive;
u8 gWorldselectCancelled;
s16 gWorldselectPaletteTimer;
u16 gWorldselectPaletteFrame;

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

    gWorldselectSlots[slot].palette = LoadObjPalette(src, size);
}

void WorldselectLoadSlotTiles(s16 model, s16 slot) {
    void* src;

    if (sWorldselectWorldDefs[model].world == WORLD_100_ACRE_WOOD && IsPooAltImageActive()) {
        src = gUnk_099EDE7C;
    } else {
        src = sWorldselectWorldDefs[model].tiles;
    }

    gWorldselectSlots[slot].tiles = LoadObjTiles(src, 0x1000);
}

s16 WorldselectSetSlotGfx(s16 model, s16 slot) {
    if (sWorldselectWorldDefs[model].world == WORLD_100_ACRE_WOOD && IsPooAltImageActive()) {
        gWorldselectSlots[slot].gfx = gUnk_099A8914;
    } else {
        gWorldselectSlots[slot].gfx = sWorldselectWorldDefs[model].gfx;
    }
}

void WorldselectDrawName(s16 model, s16 n) {
    u8* src;
    u8* src2;

    DmaFill16(3, 0, gWorldselectNameBuffer, 0x6C0);

    if (n > 0) {
#ifdef VERSION_EU
        src = ((u8**)sWorldselectWorldDefs[model].nameTiles)[gLanguage];
        src += sWorldselectWorldDefs[model].nameTilesOffset;
#else
        src = sWorldselectWorldDefs[model].nameTiles;
#endif
        DmaCopy16(3, src, (u8*)gWorldselectNameBuffer + (9 - n) * 32, n * 32);
        src2 = src + (18 - n) * 32;
        DmaCopy16(3, src2, (u8*)gWorldselectNameBuffer + 288, n * 32);
        DmaCopy16(3, src + 576, (u8*)gWorldselectNameBuffer + (9 - n) * 32 + 576, n * 32);
        DmaCopy16(3, src2 + 576, (u8*)gWorldselectNameBuffer + 864, n * 32);
        DmaCopy16(3, src + 1152, (u8*)gWorldselectNameBuffer + (9 - n) * 32 + 1152, n * 32);
        DmaCopy16(3, src2 + 1152, (u8*)gWorldselectNameBuffer + 1440, n * 32);
    }

    RequestDma3Copy(gWorldselectNameBuffer, (u8*)GetBgCharBase(0) + 1024, 0x6C0);
}

void WorldselectHandleInput() {
    s16 i;
    s16 j;
    s16 k;
    u8 step;

    switch (gWorldselectRotation) {
    case 0:
        if (GetKeysPressed() & A_BUTTON) {
            BgAnimInit(2, 0x8000, 128);
            BgAnimStart(&gBgAnimDefWorldStart, 112, 126);
            SetBgPriority(2, 1);
            gBldCnt |= BLDCNT_TGT2_OBJ;
            gWorldselectBgAnimActive = 1;
            m4aSongNumStart(SONG_SYS_WORLDSTART);
            gWorldselectCancelled = 0;
            gWorldselectStep = 4;
        } else if ((GetKeysPressed() & B_BUTTON) && gWorldselectFirstVisit == 0) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            LoadBgMap(0, gUnk_09A310DC, 0x500);
            LoadBgMap(1, gUnk_09A31ADC, 0x500);
            gWorldselectCancelled = 1;
            gWorldselectTimer = 16;
            gWorldselectStep = 5;
        } else if (gWorldselectSlotCount > 1) {
            if (GetKeysHeld() & DPAD_LEFT) {
                j = gWorldselectCursor - gWorldselectSlotCount / 2;

                while (j < 0) {
                    j += gWorldselectSlotCount;
                }

                ReleaseObjPalette(gWorldselectSlots[j].palette);
                ReleaseObjTiles(gWorldselectSlots[j].tiles);
                k = gWorldselectSlots[gWorldselectCursor].listIndex - gWorldselectSlotCount / 2;

                while (k < 0) {
                    k += gWorldselectWorldCount;
                }

                gWorldselectSlots[j].listIndex = k;
                WorldselectLoadSlotPalette(gWorldselectWorlds[k], j);
                WorldselectLoadSlotTiles(gWorldselectWorlds[k], j);
                WorldselectSetSlotGfx(gWorldselectWorlds[k], j);
                gWorldselectCursor--;

                if (gWorldselectCursor < 0) {
                    gWorldselectCursor = gWorldselectSlotCount - 1;
                }

                m4aSongNumStart(SONG_SYS_WORLDSELECT);
                gWorldselectNameMode = 2;
                gWorldselectRotation = 2;
            } else if (GetKeysHeld() & DPAD_RIGHT) {
                j = gWorldselectCursor + gWorldselectSlotCount / 2;

                while (j >= gWorldselectSlotCount) {
                    j -= gWorldselectSlotCount;
                }

                ReleaseObjPalette(gWorldselectSlots[j].palette);
                ReleaseObjTiles(gWorldselectSlots[j].tiles);
                k = gWorldselectSlots[gWorldselectCursor].listIndex + gWorldselectSlotCount / 2;

                while (k >= gWorldselectWorldCount) {
                    k -= gWorldselectWorldCount;
                }

                gWorldselectSlots[j].listIndex = k;
                WorldselectLoadSlotPalette(gWorldselectWorlds[k], j);
                WorldselectLoadSlotTiles(gWorldselectWorlds[k], j);
                WorldselectSetSlotGfx(gWorldselectWorlds[k], j);
                gWorldselectCursor++;

                if (gWorldselectCursor >= gWorldselectSlotCount) {
                    gWorldselectCursor = 0;
                }

                m4aSongNumStart(SONG_SYS_WORLDSELECT);
                gWorldselectNameMode = 2;
                gWorldselectRotation = 1;
            }
        }

        break;
    case 1:
        if (GetKeysHeld() & DPAD_LEFT) {
            j = gWorldselectCursor - gWorldselectSlotCount / 2;

            while (j < 0) {
                j += gWorldselectSlotCount;
            }

            ReleaseObjPalette(gWorldselectSlots[j].palette);
            ReleaseObjTiles(gWorldselectSlots[j].tiles);
            k = gWorldselectSlots[gWorldselectCursor].listIndex - gWorldselectSlotCount / 2;

            while (k < 0) {
                k += gWorldselectWorldCount;
            }

            gWorldselectSlots[j].listIndex = k;
            WorldselectLoadSlotPalette(gWorldselectWorlds[k], j);
            WorldselectLoadSlotTiles(gWorldselectWorlds[k], j);
            WorldselectSetSlotGfx(gWorldselectWorlds[k], j);
            gWorldselectCursor--;

            if (gWorldselectCursor < 0) {
                gWorldselectCursor = gWorldselectSlotCount - 1;
            }

            m4aSongNumStart(SONG_SYS_WORLDSELECT);
            gWorldselectRotation = 2;
        } else {
            for (i = 0; i < gWorldselectSlotCount; i++) {
                gWorldselectSlots[i].angle -= 2;
            }

            if (gWorldselectSlots[gWorldselectCursor].angle <= 128) {
                if (GetKeysHeld() & DPAD_RIGHT) {
                    j = gWorldselectCursor + gWorldselectSlotCount / 2;

                    while (j >= gWorldselectSlotCount) {
                        j -= gWorldselectSlotCount;
                    }

                    ReleaseObjPalette(gWorldselectSlots[j].palette);
                    ReleaseObjTiles(gWorldselectSlots[j].tiles);
                    k = gWorldselectSlots[gWorldselectCursor].listIndex + gWorldselectSlotCount / 2;

                    while (k >= gWorldselectWorldCount) {
                        k -= gWorldselectWorldCount;
                    }

                    gWorldselectSlots[j].listIndex = k;
                    WorldselectLoadSlotPalette(gWorldselectWorlds[k], j);
                    WorldselectLoadSlotTiles(gWorldselectWorlds[k], j);
                    WorldselectSetSlotGfx(gWorldselectWorlds[k], j);
                    gWorldselectCursor++;

                    if (gWorldselectCursor >= gWorldselectSlotCount) {
                        gWorldselectCursor = 0;
                    }

                    m4aSongNumStart(SONG_SYS_WORLDSELECT);
                    gWorldselectRotation = 1;
                } else {
                    step = 128 - gWorldselectSlots[gWorldselectCursor].angle;

                    for (i = 0; i < gWorldselectSlotCount; i++) {
                        gWorldselectSlots[i].angle += step;
                    }

                    gWorldselectNameMode = 1;
                    gWorldselectNameWorld = gWorldselectWorlds[gWorldselectSlots[gWorldselectCursor].listIndex];
                    gWorldselectRotation = 0;
                }
            }
        }

        break;
    case 2:
        if (GetKeysHeld() & DPAD_RIGHT) {
            j = gWorldselectCursor + gWorldselectSlotCount / 2;

            while (j >= gWorldselectSlotCount) {
                j -= gWorldselectSlotCount;
            }

            ReleaseObjPalette(gWorldselectSlots[j].palette);
            ReleaseObjTiles(gWorldselectSlots[j].tiles);
            k = gWorldselectSlots[gWorldselectCursor].listIndex + gWorldselectSlotCount / 2;

            while (k >= gWorldselectWorldCount) {
                k -= gWorldselectWorldCount;
            }

            gWorldselectSlots[j].listIndex = k;
            WorldselectLoadSlotPalette(gWorldselectWorlds[k], j);
            WorldselectLoadSlotTiles(gWorldselectWorlds[k], j);
            WorldselectSetSlotGfx(gWorldselectWorlds[k], j);
            gWorldselectCursor++;

            if (gWorldselectCursor >= gWorldselectSlotCount) {
                gWorldselectCursor = 0;
            }

            m4aSongNumStart(SONG_SYS_WORLDSELECT);
            gWorldselectRotation = 1;
        } else {
            for (i = 0; i < gWorldselectSlotCount; i++) {
                gWorldselectSlots[i].angle += 2;
            }

            if ((s8)gWorldselectSlots[gWorldselectCursor].angle < 0) {
                if (GetKeysHeld() & DPAD_LEFT) {
                    j = gWorldselectCursor - gWorldselectSlotCount / 2;

                    while (j < 0) {
                        j += gWorldselectSlotCount;
                    }

                    ReleaseObjPalette(gWorldselectSlots[j].palette);
                    ReleaseObjTiles(gWorldselectSlots[j].tiles);
                    k = gWorldselectSlots[gWorldselectCursor].listIndex - gWorldselectSlotCount / 2;

                    while (k < 0) {
                        k += gWorldselectWorldCount;
                    }

                    gWorldselectSlots[j].listIndex = k;
                    WorldselectLoadSlotPalette(gWorldselectWorlds[k], j);
                    WorldselectLoadSlotTiles(gWorldselectWorlds[k], j);
                    WorldselectSetSlotGfx(gWorldselectWorlds[k], j);
                    gWorldselectCursor--;

                    if (gWorldselectCursor < 0) {
                        gWorldselectCursor = gWorldselectSlotCount - 1;
                    }

                    m4aSongNumStart(SONG_SYS_WORLDSELECT);
                    gWorldselectRotation = 2;
                } else {
                    step = gWorldselectSlots[gWorldselectCursor].angle + 128;

                    for (i = 0; i < gWorldselectSlotCount; i++) {
                        gWorldselectSlots[i].angle -= step;
                    }

                    gWorldselectNameMode = 1;
                    gWorldselectNameWorld = gWorldselectWorlds[gWorldselectSlots[gWorldselectCursor].listIndex];
                    gWorldselectRotation = 0;
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

    if (gWorldselectStep < 2 || gWorldselectStep > 4) {
        DrawSprite(gWorldselectTitleX >> 8, 0,
#ifdef VERSION_EU
                      sWorldselectTitleGfx[gLanguage],
#else
                      gUnk_0999CB90,
#endif
                      gWorldselectTitleTiles, gWorldselectOverlayPalette, NULL, SPRITE_PRIORITY(1),
                      0x3E8);
        DrawSprite(120, gWorldselectFrameY[0] >> 8, gUnk_0999C394, gWorldselectFrameTiles, gWorldselectOverlayPalette, NULL,
                      SPRITE_PRIORITY(1), 0x3E9);
        DrawSprite(120, gWorldselectFrameY[1] >> 8, gUnk_0999C3C8, gWorldselectFrameTiles, gWorldselectOverlayPalette, NULL,
                      SPRITE_PRIORITY(3), 0xBBA);
    }

    for (i = 0; i < gWorldselectSlotCount; i++) {
        ang = gWorldselectSlots[i].angle;
        s = -gSineTable[((256 / gWorldselectSlotCount * i + gWorldselectBobPhase) & 0xFF) + 64];
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
                tiles = gWorldselectCardTiles[0];
                pal = gWorldselectCardPalettes[0];
                anim = gUnk_0999A350;

                if (gWorldselectStep > 3 && gWorldselectCancelled == 0) {
                    BgAnimSetPosition(x - 1, y - 5);
                }
            } else if (t <= 61) {
                sprite = NULL;
                tiles = gWorldselectCardTiles[1];
                pal = gWorldselectCardPalettes[1];
                anim = gUnk_09EF9770[(62 - t) / 13];
            } else if (t > 194) {
                sprite = NULL;
                tiles = gWorldselectCardTiles[1];
                pal = gWorldselectCardPalettes[1];
                anim = gUnk_09EF9770[(t - 194) / 13];
            } else {
                sprite = AllocObjAffine(0, w, d, 0);
                tiles = gWorldselectCardTiles[0];
                pal = gWorldselectCardPalettes[0];
                anim = gUnk_0999A350;
            }

            DrawSprite(x, y, anim, tiles, pal, sprite, SPRITE_PRIORITY(2),
                          ang > 128 ? (u16)(ang * 2 + 0x6D1) : (u16)((128 - ang) * 2 + 0x7D1));

            if ((u8)(t - 65) <= 126) {
                DrawSprite(x, y, gWorldselectSlots[i].gfx, gWorldselectSlots[i].tiles,
                              gWorldselectSlots[i].palette, sprite, SPRITE_PRIORITY(2),
                              ang > 128 ? (u16)(ang * 2 + 0x6D0)
                                        : (u16)((128 - ang) * 2 + 0x7D0));
            }
        }
    }

    switch (gWorldselectNameMode) {
    case 1:
        WorldselectDrawName(gWorldselectNameWorld, gWorldselectNameWidth);

        if (gWorldselectNameWidth <= 8) {
            gWorldselectNameWidth++;
        } else {
            gWorldselectNameMode = 0;
        }

        break;
    case 2:
        WorldselectDrawName(gWorldselectNameWorld, gWorldselectNameWidth);

        if (gWorldselectNameWidth > 0) {
            gWorldselectNameWidth--;
        } else {
            gWorldselectNameMode = 0;
        }

        break;
    }

    if (gWorldselectBgAnimActive != 0) {
        BgAnimUpdate();
    }

    TaskPoolDraw(&gWorldselectTaskPool);
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
    gWorldselectPaletteTimer++;

    if (gWorldselectPaletteTimer > 6) {
        gWorldselectPaletteTimer = 0;
        gWorldselectPaletteFrame++;

        if (gWorldselectPaletteFrame > 29) {
            gWorldselectPaletteFrame = 0;
        }

        LoadPalette(sWorldselectPaletteCycle[(s16)gWorldselectPaletteFrame], (void*)(BG_PLTT + 2 * PLTT_SIZE_4BPP), 32);
    }
}

void mode_worldselect_0() {
    s16 i;
    s16 j;
    void** p;

    SpriteReset();
    gWorldselectFirstVisit = (gGameState.progression.tutorialFlags ^ 1) & 1;
    gWorldselectBgAnimActive = 0;
    gWorldselectCancelled = 0;
    FadeStartIn(FADE_MODE_ADD_WHITE, 16);

    if (gWorldselectFirstVisit != 0) {
        WorldselectSetBgMode0();
    } else {
        WorldselectSetBgMode1();
    }

    gWorldselectCursor = 0;
    gWorldselectRotation = 0;
    j = 0;

    for (i = 0; i <= 12; i++) {
        if (gGameState.availableWorlds & sWorldselectWorldDefs[i].worldBit) {
            gWorldselectWorlds[j] = i;
            j++;
        }
    }

    gWorldselectWorldCount = j;
    gWorldselectSlotCount = j > 5 ? 5 : j;
    j = 0;

    for (i = 0; i < gWorldselectSlotCount; i++, j++) {
        if (j >= gWorldselectWorldCount) {
            j = 0;
        }

        if (i == gWorldselectSlotCount - 1 && gWorldselectSlotCount > 2) {
            j = gWorldselectWorldCount - 1;
        }

        gWorldselectSlots[i].listIndex = j;
        gWorldselectSlots[i].angle = 256 / gWorldselectSlotCount * i - 128;
        WorldselectLoadSlotPalette(gWorldselectWorlds[j], i);
        WorldselectLoadSlotTiles(gWorldselectWorlds[j], i);
        WorldselectSetSlotGfx(gWorldselectWorlds[j], i);
    }

    gWorldselectBobPhase = 0;
    gWorldselectNameMode = 1;
    gWorldselectNameWidth = 0;
    gWorldselectNameWorld = gWorldselectWorlds[gWorldselectSlots[gWorldselectCursor].listIndex];
    p = &gWorldselectNameBuffer;
    *p = EwramAlloc(0x6C0);
    gWorldselectPaletteTimer = 0;
    gWorldselectPaletteFrame = 0;
    gWorldselectStep = 0;
    gWorldselectTimer = 16;
    gWorldselectFrameY[0] = -2048;
    gWorldselectFrameY[1] = 0xA800;
    gWorldselectTitleX = -32768;
    LoadBgPalette(0, gUnk_09A3C9DC, 96);
#ifdef VERSION_EU
    LoadBgTiles(0, gUnk_099F1E7C, 16000);
#else
    LoadBgTiles(0, gUnk_099F1E7C, 11968);
#endif
    WorldselectDrawName(gWorldselectNameWorld, gWorldselectNameWidth);
    LoadBgMap(0, gUnk_09A310DC, 0x500);
    LoadBgMap(1, gUnk_09A31ADC, 0x500);

    if (gWorldselectFirstVisit == 0) {
        BgAnimInit(2, 0x8000, 128);
        BgAnimStart(&gBgAnimDefWorldSelect, 120, 110);
        BgAnimSetLoopStartFrame(0);
        gWorldselectBgAnimActive = 1;
    }

    gWorldselectCardPalettes[0] = LoadObjPalette(gUnk_09A3CC3C, 32);
    gWorldselectCardTiles[0] = LoadObjTiles(gUnk_0999A394, 0xC40);
    gWorldselectCardPalettes[1] = LoadObjPalette(gUnk_09A3CC5C, 32);
    gWorldselectCardTiles[1] = LoadObjTiles(gUnk_0999B052, 0x1340);
    gWorldselectOverlayPalette = LoadObjPalette(gUnk_09A3CC7C, 32);
#ifdef VERSION_EU
    gWorldselectTitleTiles = LoadObjTiles(sWorldselectTitleTileData[gLanguage], sWorldselectTitleTileSizes.sizes[gLanguage]);
#else
    gWorldselectTitleTiles = LoadObjTiles(gUnk_0999CBB6, 0x380);
#endif
    gWorldselectFrameTiles = LoadObjTiles(gUnk_0999C410, 0x780);
    TaskPoolInit(&gWorldselectTaskPool, 1);
    EnableBg(0);
    EnableBg(1);

    if (gWorldselectFirstVisit != 0) {
        DisableBg(2);
    } else {
        EnableBg(2);
    }
}

void mode_worldselect_1() {
    s16 a;
    s16 b;

    UpdatePlayTime();
    gWorldselectBobPhase += 2;

    switch (gWorldselectStep) {
    case 0:
        ApproachValue(&gWorldselectFrameY[0], 0, gWorldselectTimer);
        ApproachValue(&gWorldselectFrameY[1], 0x9800, gWorldselectTimer);
        gWorldselectTimer--;

        if (gWorldselectTimer <= 0) {
            gWorldselectTimer = 16;
            gWorldselectStep = 1;
        }

        break;
    case 1:
        ApproachValue(&gWorldselectTitleX, 0, gWorldselectTimer);
        gWorldselectTimer--;

        if (gWorldselectTimer <= 0) {
            if (gWorldselectFirstVisit != 0) {
                gWorldselectTutorialStep = 0;
                CreateCardMessageTask(&gWorldselectTaskPool, 2, 70);
                gWorldselectStep = 2;
            } else {
                gWorldselectStep = 3;
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
        if (IsMessageWindowOpen() == 0) {
            if (gWorldselectTutorialStep == 0) {
                CreateCardMessageTask(&gWorldselectTaskPool, 2, 71);
                gWorldselectTutorialStep++;
            } else {
                gGameState.progression.tutorialFlags |= 1;
                WorldselectSetBgMode1();
                BgAnimInit(2, 0x8000, 128);
                BgAnimStart(&gBgAnimDefWorldSelect, 120, 110);
                BgAnimSetLoopStartFrame(0);
                gWorldselectBgAnimActive = 1;
                gWorldselectStep = 3;
            }
        }

        break;
    case 3:
        WorldselectHandleInput();
        break;
    case 4:
        if (BgAnimIsStopped() != 0) {
            LoadBgMap(0, gUnk_09A310DC, 0x500);
            LoadBgMap(1, gUnk_09A31ADC, 0x500);
            gWorldselectTimer = 16;
            gWorldselectStep = 5;
        }

        break;
    case 5:
        ApproachValue(&gWorldselectTitleX, -32768, gWorldselectTimer);
        gWorldselectTimer--;

        if (gWorldselectTimer <= 0) {
            gWorldselectTimer = 16;
            gWorldselectStep = 6;
        }

        break;
    case 6:
        ApproachValue(&gWorldselectFrameY[0], -2048, gWorldselectTimer);
        ApproachValue(&gWorldselectFrameY[1], 0xA800, gWorldselectTimer);
        gWorldselectTimer--;

        if (gWorldselectTimer <= 0) {
            gWorldselectStep = 7;
        }

        break;
    case 7:
        FadeLock();

        if (gWorldselectCancelled != 0) {
            FadeStartOut(FADE_MODE_BLACK, 16);
        } else {
            FadeStartOut(FADE_MODE_ADD_WHITE, 16);
        }

        gWorldselectStep = 8;
        break;
    case 8:
        if (FadeIsActive() == 0) {
            if (gWorldselectCancelled != 0) {
                RequestMapMode();
            } else {
                gWorldselectTimer = 60;
                gWorldselectStep = 9;
            }
        }

        break;
    case 9:
        gWorldselectTimer--;

        if (gWorldselectTimer <= 0) {
            a = sWorldselectWorldDefs[gWorldselectWorlds[gWorldselectSlots[gWorldselectCursor].listIndex]].world;

            if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
                b = sWorldselectWorldDefs[gWorldselectWorlds[gWorldselectSlots[gWorldselectCursor].listIndex]].eventId;
            } else {
                b = sWorldselectWorldDefs[gWorldselectWorlds[gWorldselectSlots[gWorldselectCursor].listIndex]].rikuEventId;
            }

            gGameState.availableWorlds &=
                ~sWorldselectWorldDefs[gWorldselectWorlds[gWorldselectSlots[gWorldselectCursor].listIndex]].worldBit;
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

    if (FadeIsActive() != 0) {
        FadeGetAmount();
    }

    TaskPoolUpdate(&gWorldselectTaskPool);
    WorldselectDraw();
}

void mode_worldselect_2() {
    s16 i;

    EwramFree(gWorldselectNameBuffer);

    for (i = 0; i < gWorldselectSlotCount; i++) {
        ReleaseObjPalette(gWorldselectSlots[i].palette);
        ReleaseObjTiles(gWorldselectSlots[i].tiles);
    }

    for (i = 0; i < 2; i++) {
        ReleaseObjPalette(gWorldselectCardPalettes[i]);
        ReleaseObjTiles(gWorldselectCardTiles[i]);
    }

    ReleaseObjPalette(gWorldselectOverlayPalette);
    ReleaseObjTiles(gWorldselectTitleTiles);
    ReleaseObjTiles(gWorldselectFrameTiles);
    TaskPoolDestroy(&gWorldselectTaskPool);
}
