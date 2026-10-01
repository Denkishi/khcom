#include "types.h"
#include "worldinspect_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "engine_math.h"
#include "m4a_song.h"
#include "text.h"
#include "monsgage.h"
#include "fade.h"
#include "obj_api.h"
#include "display.h"
#include "malloc.h"
#include "mode_worldinspect.h"
#include "game_state.h"
#include "gba/keys.h"
#include "anim.h"
#include "card_description_data.h"
#include "worldselect_assets.h"
#include "worldinspect_assets.h"
#include "sprites_bos5.h"
#include "sprites_worldinspect.h"
#include "gba/io_reg.h"
#include "songs.h"
#include "common_text.h"
#include "jiminy_records_assets.h"
#include "world_types.h"
#include "jiminy_data.h"
#include "jiminy_inline_text_data.h"
#include "key.h"
#include "mode.h"
#include "obj.h"
#include "poo_api.h"
#include "text_types.h"
#include "gba/macro.h"
#include <stddef.h>

static s16 sWorldInspectCursor;
static s16 sWorldInspectFloorCount;
static s16 sWorldInspectWorlds[12];

extern u8 gUnk_09A3CE7C[];
extern u8 gUnk_09A3D07C[];

static const WorldinspectConn sWorldinspectConns[3] = {
    { 2, 1, 20, 2 },
    { 2, 5, 0, 13 },
    { 2, 5, 3, 13 },
};

static s16 sWorldInspectDetailOpen;
static u8 sWorldInspectBobPhase;
static struct ObjPalette* sWorldInspectBarPalette;
static struct ObjTiles* sWorldInspectBarTiles;
static struct ObjPalette* sWorldInspectHighlightPalette;
static struct ObjTiles* sWorldInspectHighlightTiles;
static AnimState sWorldInspectHighlightAnim;
static struct ObjPalette* sWorldInspectCursorPalette;
static struct ObjTiles* sWorldInspectCursorTiles;
static AnimState sWorldInspectCursorAnim;
static void* sWorldInspectIconPalettes[12];
static void* sWorldInspectIconTiles[12];
static void* sWorldInspectIconSprites[12];
#ifdef VERSION_EU
static TextSlot sWorldInspectNameText[48];
#else
static TextSlot sWorldInspectNameText[24];
#endif
static u8 sWorldInspectNameTextCount;
#ifdef VERSION_EU
static TextSlot sWorldInspectDescText[120];
#else
static TextSlot sWorldInspectDescText[60];
#endif
static u8 sWorldInspectDescTextCount;
static void* sWorldInspectDetailPalettes[2];
static void* sWorldInspectDetailTiles[2];
static void* sWorldInspectDetailSprites[2];
static s16 sWorldInspectState;
static s16 sWorldInspectSteps;
static s32 sWorldInspectBarY[2];
static s32 sWorldInspectBarX;
static void* sWorldInspectTilemap;
static s32 sWorldInspectCursorX;
static s32 sWorldInspectCursorY;
static u8 sWorldInspectReturnToMenu;

static WorldinspectNav sWorldinspectNavs[12] = {
    { 7, 8, 1, 3, 22, 14, 0, 21, 16, { 0, 0 } },
    { 6, 9, 2, 0, 15, 14, 0, 14, 16, { 0, 0 } },
    { 5, 10, 3, 1, 8, 14, 0, 7, 16, { 0, 0 } },
    { 4, 11, 0, 2, 1, 14, 1, 0, 12, { 0, 0 } },
    { 11, 3, 7, 5, 1, 10, 0, 7, 12, { 0, 0 } },
    { 10, 2, 4, 6, 8, 10, 0, 14, 12, { 0, 0 } },
    { 9, 1, 5, 7, 15, 10, 0, 21, 12, { 0, 0 } },
    { 8, 0, 6, 4, 22, 10, 2, 28, 8, { 0, 0 } },
    { 0, 7, 9, 11, 22, 6, 0, 21, 8, { 0, 0 } },
    { 1, 6, 10, 8, 15, 6, 0, 14, 8, { 0, 0 } },
    { 2, 5, 11, 9, 8, 6, 0, 7, 8, { 0, 0 } },
    { 3, 4, 8, 10, 1, 6, 0, 0, 8, { 0, 0 } },
};

static WorldinspectMsg sWorldinspectMsgs[14] = {
    {
        0, 0, 0, 0, { 0, 0 }, 0, 0, { 0, 0 }, 0, 0, 0, { 0, 0 }, 0, 0, { 0, 0 }, 0,
        0,
        0, 0,
    },
    {
        1, WORLD_AGRABAH, gUnk_09A3D65C, 32, { 0, 0 }, gUnk_099A0B5C, 576, { 0, 0 }, gUnk_099A0B3C, gUnk_09A3CD1C, 32, { 0, 0 }, gUnk_099E7E7C, 4096, { 0, 0 }, gUnk_099A8824,
#if defined(VERSION_EU)
        &gUnkEu_0888E3A0,
#elif defined(VERSION_JP)
        gUnkJp_0814E590,
#elif defined(VERSION_US)
        gUnk_0815A56C,
#endif
        0, 0,
    },
    {
        2, WORLD_ATLANTICA, gUnk_09A3D69C, 32, { 0, 0 }, gUnk_099A0F70, 512, { 0, 0 }, gUnk_099A0F5C, gUnk_09A3CD5C, 32, { 0, 0 }, gUnk_099E9E7C, 4096, { 0, 0 }, gUnk_099A8880,
#if defined(VERSION_EU)
        &gUnkEu_0888E578,
#elif defined(VERSION_JP)
        gUnkJp_0814E5E4,
#elif defined(VERSION_US)
        gUnk_0815A5AA,
#endif
        2, 2,
    },
    {
        4, WORLD_OLYMPUS_COLISEUM, gUnk_09A3D63C, 32, { 0, 0 }, gUnk_099A08BA, 640, { 0, 0 }, gUnk_099A08A0, gUnk_09A3CCFC, 32, { 0, 0 }, gUnk_099E6E7C, 4096, { 0, 0 }, gUnk_099A87F8,
#if defined(VERSION_EU)
        &gUnkEu_0888E530,
#elif defined(VERSION_JP)
        gUnkJp_0814E5CC,
#elif defined(VERSION_US)
        gUnk_0815A54A,
#endif
        6, 6,
    },
    {
        8, WORLD_WONDERLAND, gUnk_09A3D5DC, 32, { 0, 0 }, gUnk_099A0206, 544, { 0, 0 }, gUnk_099A01EC, gUnk_09A3CC9C, 32, { 0, 0 }, gUnk_099E3E7C, 4096, { 0, 0 }, gUnk_099A8758,
#if defined(VERSION_EU)
        &gUnkEu_0888E410,
#elif defined(VERSION_JP)
        gUnkJp_0814E59C,
#elif defined(VERSION_US)
        gUnk_0815A534,
#endif
        4, 4,
    },
    {
        16, WORLD_MONSTRO, gUnk_09A3D67C, 32, { 0, 0 }, gUnk_099A0DBC, 416, { 0, 0 }, gUnk_099A0D9C, gUnk_09A3CD3C, 32, { 0, 0 }, gUnk_099E8E7C, 4096, { 0, 0 }, gUnk_099A884C,
#if defined(VERSION_EU)
        &gUnkEu_0888E450,
#elif defined(VERSION_JP)
        gUnkJp_0814E5AC,
#elif defined(VERSION_US)
        gUnk_0815A59A,
#endif
        3, 3,
    },
    {
        32, WORLD_HALLOWEEN_TOWN, gUnk_09A3D6BC, 32, { 0, 0 }, gUnk_099A118A, 544, { 0, 0 }, gUnk_099A1170, gUnk_09A3CD7C, 32, { 0, 0 }, gUnk_099EAE7C, 4096, { 0, 0 }, gUnk_099A88A0,
#if defined(VERSION_EU)
        &gUnkEu_0888E4C0,
#elif defined(VERSION_JP)
        gUnkJp_0814E5B8,
#elif defined(VERSION_US)
        gUnk_0815A57C,
#endif
        5, 5,
    },
    {
        64, WORLD_NEVER_LAND, gUnk_09A3D6DC, 32, { 0, 0 }, gUnk_099A13CC, 544, { 0, 0 }, gUnk_099A13AC, gUnk_09A3CD9C, 32, { 0, 0 }, gUnk_099EBE7C, 4096, { 0, 0 }, gUnk_099A88D4,
#if defined(VERSION_EU)
        &gUnkEu_0888E5DC,
#elif defined(VERSION_JP)
        gUnkJp_0814E5F4,
#elif defined(VERSION_US)
        gUnk_0815A5BE,
#endif
        1, 1,
    },
    {
        128, WORLD_HOLLOW_BASTION, gUnk_09A3D71C, 32, { 0, 0 }, gUnk_099A181A, 768, { 0, 0 }, gUnk_099A1800, gUnk_09A3CE1C, 32, { 0, 0 }, gUnk_099EEE7C, 4096, { 0, 0 }, gUnk_099A8930,
#if defined(VERSION_EU)
        &gUnkEu_0888E6BC,
#elif defined(VERSION_JP)
        gUnkJp_0814E618,
#elif defined(VERSION_US)
        gUnk_0815A5D4,
#endif
        7, 7,
    },
    {
        256, WORLD_DESTINY_ISLANDS, gUnk_09A3D5FC, 32, { 0, 0 }, gUnk_099A0442, 544, { 0, 0 }, gUnk_099A0428, gUnk_09A3CCBC, 32, { 0, 0 }, gUnk_099E4E7C, 4096, { 0, 0 }, gUnk_099A8780,
#if defined(VERSION_EU)
        &gUnkEu_0888E72C,
#elif defined(VERSION_JP)
        gUnkJp_0814E62C,
#elif defined(VERSION_US)
        gUnk_0815A62A,
#endif
        8, 8,
    },
    {
        512, WORLD_TRAVERSE_TOWN, gUnk_09A3D61C, 32, { 0, 0 }, gUnk_099A067E, 544, { 0, 0 }, gUnk_099A0664, gUnk_09A3CCDC, 32, { 0, 0 }, gUnk_099E5E7C, 4096, { 0, 0 }, gUnk_099A87C0,
#if defined(VERSION_EU)
        &gUnkEu_0888E364,
#elif defined(VERSION_JP)
        gUnkJp_0814E57C,
#elif defined(VERSION_US)
        gUnk_0815A518,
#endif
        9, 9,
    },
    {
        2048, WORLD_TWILIGHT_TOWN, gUnk_09A3D73C, 32, { 0, 0 }, gUnk_099A1B30, 512, { 0, 0 }, gUnk_099A1B1C, gUnk_09A3CE3C, 32, { 0, 0 }, gUnk_099EFE7C, 4096, { 0, 0 }, gUnk_099A895C,
#if defined(VERSION_EU)
        &gUnkEu_0888E78C,
#elif defined(VERSION_JP)
        gUnkJp_0814E644,
#elif defined(VERSION_US)
        gUnk_0815A60E,
#endif
        10, 10,
    },
    {
        4096, WORLD_CASTLE_OBLIVION, gUnk_09A3D75C, 32, { 0, 0 }, gUnk_099A1D44, 512, { 0, 0 }, gUnk_099A1D30, gUnk_09A3CE5C, 32, { 0, 0 }, gUnk_099F0E7C, 4096, { 0, 0 }, gUnk_099A897C,
#if defined(VERSION_EU)
        &gUnkEu_0888E804,
#elif defined(VERSION_JP)
        gUnkJp_0814E658,
#elif defined(VERSION_US)
        gUnk_0815A64A,
#endif
        11, 13,
    },
    {
        1024, WORLD_100_ACRE_WOOD, gUnk_09A3D6FC, 32, { 0, 0 }, gUnk_099A1600, 512, { 0, 0 }, gUnk_099A15EC, gUnk_09A3CDBC, 32, { 0, 0 }, gUnk_099ECE7C, 4096, { 0, 0 }, gUnk_099A8900,
#if defined(VERSION_EU)
        &gUnkEu_0888E654,
#elif defined(VERSION_JP)
        gUnkJp_0814E604,
#elif defined(VERSION_US)
        gUnk_0815A5F2,
#endif
        12, 12,
    },
};

void WorldInspectSetTilemapRectPalette(u8 pal, u16 w, s16 h, u16* map, s16 x, s16 y) {
    s16 i;
    s16 j;
    s16 n;
    u16 v;

    n = w;
    v = pal << 12;
    map += x + y * 32;

    for (j = 0; j < h; j++) {
        for (i = 0; i < n; i++) {
            *map = (*map & 0xFFF) | v;
            map++;
        }

        map += 32 - n;
    }
}

void WorldInspectCopyTilemapRect(s16 w, s16 h, u16* src, s16 sx, s16 sy, u16* dst, s16 dx, s16 dy) {
    s16 i;
    s16 j;
    s16 n;

    n = w;
    src += sx + sy * 32;
    dst += dx + dy * 32;

    for (j = 0; j < h; j++) {
        for (i = 0; i < n; i++) {
            *dst++ = *src++;
        }

        src += 32 - n;
        dst += 32 - n;
    }
}

u8 WorldInspectLoadName(s16 id) {
#ifdef VERSION_EU
    u8 ret = 0;

    if (id != 0) {
        ret = LoadTextSlots(eu_0805E924(sWorldinspectMsgs[id].text), sWorldInspectNameText);
    }

    return ret;
#else
    if (id == 0) {
        return 0;
    }

    return LoadTextSlots(sWorldinspectMsgs[id].text, sWorldInspectNameText);
#endif
}

u8 WorldInspectLoadDesc(s16 id) {
    CardDescriptionText** tbl;
    CardDescriptionText** p;
    u16 i;

    if (id != 0) {
        tbl = gWorldDescriptions;

        if (gGameState.flags & GAME_FLAG_RIKU) {
            i = sWorldinspectMsgs[id].descId2;
        } else {
            i = sWorldinspectMsgs[id].descId;
        }

        p = &tbl[i];

#ifdef VERSION_EU
        {
            const u8** langs = (*p)->strings;

            return LoadTextSlots((void*)langs[gLanguage], sWorldInspectDescText);
        }
#else
        return LoadTextSlots((void*)*p, sWorldInspectDescText);
#endif
    }

    return 0;
}

void WorldInspectLoadFloorTiles(s16 index) {
    u8* src;

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
#endif
        if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
            src = gUnk_09A020FC;
        } else {
            src = gUnk_09A02EFC;
        }

#ifdef VERSION_EU
        break;
    case LANGUAGE_FRENCH:
        if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
            src = gUnkEu_09A30C00;
        } else {
            src = gUnkEu_09A34400;
        }

        break;
    case LANGUAGE_SPANISH:
        if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
            src = gUnkEu_09A31A00;
        } else {
            src = gUnkEu_09A35200;
        }

        break;
    case LANGUAGE_ITALIAN:
        if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
            src = gUnkEu_09A32800;
        } else {
            src = gUnkEu_09A38C00;
        }

        break;
    case LANGUAGE_GERMAN:
    default:
        if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
            src = gUnkEu_09A33600;
        } else {
            src = gUnkEu_09A39A00;
        }

        break;
    }
#endif

    if (index < sWorldInspectFloorCount) {
        src += index * 256;
    } else {
        src += 0xD00;
    }

    RequestDma3Copy(src, (u8*)GetBgCharBase(0) + 32, 0x100);
}

s32 WorldInspectReadMenuKeys() {
    s32 keys;

    keys = GetKeysPressed() & (A_BUTTON | B_BUTTON | SELECT_BUTTON | START_BUTTON);
    keys |= GetKeysRepeat() & (DPAD_ANY | L_BUTTON | R_BUTTON);
    return keys;
}

void WorldInspectHandleInput() {
    u16 keys;
    s16 old;
    s16 i;

    old = sWorldInspectCursor;
    keys = WorldInspectReadMenuKeys();

    if (keys & A_BUTTON) {
        if (sWorldInspectWorlds[sWorldInspectCursor] != 0) {
#ifdef VERSION_EU
            ReleaseObjPalette(sWorldInspectBarPalette);
            sWorldInspectBarPalette = NULL;
#endif
            sWorldInspectDetailPalettes[0] = LoadObjPalette(gUnk_09A3CC3C, 32);
            sWorldInspectDetailTiles[0] = LoadObjTiles(gUnk_0999A394, 0xC40);
            sWorldInspectDetailSprites[0] = gUnk_0999A350;

            if (sWorldInspectCursor <= 9) {
                for (i = 10; i < 12; i++) {
                    if (sWorldInspectIconPalettes[i] != NULL) {
                        ReleaseObjPalette(sWorldInspectIconPalettes[i]);
                        sWorldInspectIconPalettes[i] = NULL;
                    }
                }
            } else {
                for (i = 4; i < 6; i++) {
                    if (sWorldInspectIconPalettes[i] != NULL) {
                        ReleaseObjPalette(sWorldInspectIconPalettes[i]);
                        sWorldInspectIconPalettes[i] = NULL;
                    }
                }
            }

            if (sWorldInspectWorlds[sWorldInspectCursor] == WORLD_100_ACRE_WOOD && IsPooAltImageActive()) {
                sWorldInspectDetailPalettes[1] = LoadObjPalette(gUnk_09A3CDDC, 64);
                sWorldInspectDetailTiles[1] = LoadObjTiles(gUnk_099EDE7C, 0x1000);
                sWorldInspectDetailSprites[1] = gUnk_099A8914;
            } else {
                sWorldInspectDetailPalettes[1] =
                    LoadObjPalette(sWorldinspectMsgs[sWorldInspectWorlds[sWorldInspectCursor]].palette2,
                                   sWorldinspectMsgs[sWorldInspectWorlds[sWorldInspectCursor]].paletteSize2);
                sWorldInspectDetailTiles[1] =
                    LoadObjTiles(sWorldinspectMsgs[sWorldInspectWorlds[sWorldInspectCursor]].tiles2,
                                 sWorldinspectMsgs[sWorldInspectWorlds[sWorldInspectCursor]].tilesSize2);
                sWorldInspectDetailSprites[1] = sWorldinspectMsgs[sWorldInspectWorlds[sWorldInspectCursor]].sprite2;
            }

            sWorldInspectDescTextCount = WorldInspectLoadDesc(sWorldInspectWorlds[sWorldInspectCursor]);
            gBldCnt = (BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2);
            gBldAlpha = BLDALPHA_BLEND(8, 8);
            EnableBg(2);
            EnableBg(3);
            m4aSongNumStart(SONG_SYS_KETTEI);
            sWorldInspectDetailOpen = 1;
        }
    } else if (keys & B_BUTTON) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        LoadBgMap(0, gUnk_09A324DC, 0x500);
#ifndef VERSION_EU
        sWorldInspectBarPalette = LoadObjPalette(gUnk_09A3D07C, 32);
#endif
        sWorldInspectReturnToMenu = 1;
        sWorldInspectSteps = 16;
        sWorldInspectState = 3;
    } else if (keys & START_BUTTON) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        LoadBgMap(0, gUnk_09A324DC, 0x500);
#ifndef VERSION_EU
        sWorldInspectBarPalette = LoadObjPalette(gUnk_09A3D07C, 32);
#endif
        sWorldInspectReturnToMenu = 0;
        FadeStartOut(FADE_MODE_BLACK, 16);
        sWorldInspectState = 5;
    } else if (keys & DPAD_UP) {
        while (1) {
            sWorldInspectCursor = sWorldinspectNavs[sWorldInspectCursor].up;

            if (sWorldInspectCursor == old) {
                break;
            }

            if (sWorldInspectWorlds[sWorldInspectCursor] != 0) {
                break;
            }
        }
    } else if (keys & DPAD_DOWN) {
        while (1) {
            sWorldInspectCursor = sWorldinspectNavs[sWorldInspectCursor].down;

            if (sWorldInspectCursor == old) {
                break;
            }

            if (sWorldInspectWorlds[sWorldInspectCursor] != 0) {
                break;
            }
        }
    } else if (keys & DPAD_LEFT) {
        while (1) {
            sWorldInspectCursor = sWorldinspectNavs[sWorldInspectCursor].left;

            if (sWorldInspectCursor == old) {
                break;
            }

            if (sWorldInspectWorlds[sWorldInspectCursor] != 0) {
                break;
            }
        }
    } else if (keys & DPAD_RIGHT) {
        while (1) {
            sWorldInspectCursor = sWorldinspectNavs[sWorldInspectCursor].right;

            if (sWorldInspectCursor == old) {
                break;
            }

            if (sWorldInspectWorlds[sWorldInspectCursor] != 0) {
                break;
            }
        }
    }

    if (sWorldInspectCursor != old) {
        WorldInspectLoadFloorTiles(sWorldInspectCursor);
        sWorldInspectNameTextCount = WorldInspectLoadName(sWorldInspectWorlds[sWorldInspectCursor]);
        m4aSongNumStart(SONG_SYS_CLICK);
    }
}

void WorldInspectHandleDetailInput() {
    u16 keys;
    s32 i;

    keys = WorldInspectReadMenuKeys();

    if (keys & (B_BUTTON | START_BUTTON)) {
        m4aSongNumStart(SONG_SYS_CLOSE);

        for (i = 0; i < 2; i++) {
            ReleaseObjPalette(sWorldInspectDetailPalettes[i]);
            ReleaseObjTiles(sWorldInspectDetailTiles[i]);
        }

        if (sWorldInspectCursor <= 9) {
            for (i = 10; i < 12; i++) {
                if (sWorldInspectWorlds[i] != 0) {
                    sWorldInspectIconPalettes[i] = LoadObjPalette(sWorldinspectMsgs[sWorldInspectWorlds[i]].palette,
                                                      sWorldinspectMsgs[sWorldInspectWorlds[i]].paletteSize);
                }
            }
        } else {
            for (i = 4; i < 6; i++) {
                if (sWorldInspectWorlds[i] != 0) {
                    sWorldInspectIconPalettes[i] = LoadObjPalette(sWorldinspectMsgs[sWorldInspectWorlds[i]].palette,
                                                      sWorldinspectMsgs[sWorldInspectWorlds[i]].paletteSize);
                }
            }
        }

        gBldCnt = 0;
        DisableBg(2);
        DisableBg(3);
        sWorldInspectReturnToMenu = 1;
        sWorldInspectDetailOpen = 0;

#ifdef VERSION_EU
        sWorldInspectBarPalette = LoadObjPalette(gUnk_09A3D07C, 32);
#endif

        if (keys & START_BUTTON) {
            LoadBgMap(0, gUnk_09A324DC, 0x500);
#ifndef VERSION_EU
            sWorldInspectBarPalette = LoadObjPalette(gUnk_09A3D07C, 32);
#endif
            sWorldInspectReturnToMenu = 0;
            FadeStartOut(FADE_MODE_BLACK, 16);
            sWorldInspectState = 5;
        }
    }
}

void WorldInspectDraw() {
    s32 i;
    u16 prio;
#ifdef VERSION_EU
    void* first;
    void* second;
    void* third;

    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        first = gUnkEu_099A421C;
        second = gUnkEu_099A4238;
        third = gUnkEu_099A426C;
        break;
    case LANGUAGE_FRENCH:
        first = gUnkEu_099A4C4C;
        second = gUnkEu_099A4C68;
        third = gUnkEu_099A4C9C;
        break;
    case LANGUAGE_SPANISH:
        first = gUnkEu_099A511C;
        second = gUnkEu_099A5138;
        third = gUnkEu_099A516C;
        break;
    case LANGUAGE_ITALIAN:
        first = gUnkEu_099A55AC;
        second = gUnkEu_099A55C8;
        third = gUnkEu_099A55FC;
        break;
    case LANGUAGE_GERMAN:
    default:
        first = gUnkEu_099A5A3C;
        second = gUnkEu_099A5A58;
        third = gUnkEu_099A5A8C;
        break;
    }
#endif

#ifdef VERSION_EU
    if (sWorldInspectBarPalette != NULL) {
#else
    if (sWorldInspectState != 2) {
#endif
        DrawSprite(sWorldInspectBarX >> 8, 0,
#ifdef VERSION_EU
                      first,
#else
                      gUnk_0999CF38,
#endif
                      sWorldInspectBarTiles, sWorldInspectBarPalette, NULL,
                      SPRITE_PRIORITY(3), 3000);
#ifdef VERSION_EU
    }

    if (sWorldInspectState != 2) {
#endif
        DrawSprite(112, sWorldInspectBarY[0] >> 8,
#ifdef VERSION_EU
                      second,
#else
                      gUnk_0999CF54,
#endif
                      sWorldInspectBarTiles, sWorldInspectBarPalette, NULL,
                      SPRITE_PRIORITY(3), 3001);
        DrawSprite(112, sWorldInspectBarY[1] >> 8,
#ifdef VERSION_EU
                      third,
#else
                      gUnk_0999CF88,
#endif
                      sWorldInspectBarTiles, sWorldInspectBarPalette, NULL,
                      SPRITE_PRIORITY(3), 3001);
    }

    prio = 0x400;

    if (sWorldInspectDetailOpen == 1) {
        prio |= 4;
    }

    if (sWorldInspectState == 2) {
        DrawSprite(sWorldinspectNavs[sWorldInspectCursor].x * 8 + 22,
                      sWorldinspectNavs[sWorldInspectCursor].y * 8 + 12,
                      AnimUpdate(&sWorldInspectHighlightAnim), sWorldInspectHighlightTiles, sWorldInspectHighlightPalette, NULL, prio, 2013);
        ApproachValueHalf(&sWorldInspectCursorX,
                      (sWorldinspectNavs[sWorldInspectCursor].x << 11) + 0x2000);
        ApproachValueHalf(&sWorldInspectCursorY,
                      (sWorldinspectNavs[sWorldInspectCursor].y << 11) + 0xFFFFFA00);
        DrawSprite(sWorldInspectCursorX >> 8, sWorldInspectCursorY >> 8, AnimUpdate(&sWorldInspectCursorAnim),
                      sWorldInspectCursorTiles, sWorldInspectCursorPalette, NULL, prio, 2000);
    }

    for (i = 0; i < 12; i++) {
        if (sWorldInspectIconSprites[i] != NULL && sWorldInspectIconPalettes[i] != NULL) {
            DrawSprite(sWorldinspectNavs[i].x * 8 + 16, sWorldinspectNavs[i].y * 8 + 16,
                          sWorldInspectIconSprites[i], sWorldInspectIconTiles[i], sWorldInspectIconPalettes[i], NULL, prio,
                          i + 2001);
        }
    }

    if (sWorldInspectIconSprites[sWorldInspectCursor] != NULL) {
        DrawSprite(
#ifdef VERSION_EU
                      102,
#else
                      112,
#endif
                      32, sWorldInspectIconSprites[sWorldInspectCursor], sWorldInspectIconTiles[sWorldInspectCursor],
                      sWorldInspectIconPalettes[sWorldInspectCursor], NULL, 0, 0);
    }

    if (sWorldInspectNameTextCount != 0) {
        DrawTextSlots(
#ifdef VERSION_EU
                      120,
#else
                      128,
#endif
                      28, sWorldInspectNameText, sWorldInspectCursorPalette, 1, sWorldInspectNameTextCount);
    }

    if (sWorldInspectDetailOpen == 1) {
        if (sWorldInspectDescTextCount != 0) {
            DrawTextSlots(97, 56, sWorldInspectDescText, sWorldInspectHighlightPalette, 0, sWorldInspectDescTextCount);
        }

        DrawSprite(47, (-gSineTable[sWorldInspectBobPhase + 0x40] >> 5) + 84, sWorldInspectDetailSprites[0],
                      sWorldInspectDetailTiles[0], sWorldInspectDetailPalettes[0], NULL, 0, 1);
        DrawSprite(47, (-gSineTable[sWorldInspectBobPhase + 0x40] >> 5) + 84, sWorldInspectDetailSprites[1],
                      sWorldInspectDetailTiles[1], sWorldInspectDetailPalettes[1], NULL, 0, 0);
    }
}

void mode_worldinspect_0() {
    s16 i;
    s32 floor;
    s16 id;
    void** p;
    u32 floorKeep;
    s16 fa;

    p = &sWorldInspectTilemap;
    *p = EwramAlloc(0x500);
    SpriteReset();
    FadeStartIn(FADE_MODE_BLACK, 16);
    SetBgMode0();
    SetupBg(0, 0, 0x1C, 0);
    SetupBg(1, 0, 0x1D, 0);
    SetupBg(2, 0, 0x1E, 0);
    SetupBg(3, 0, 0x1F, 0);
    SetBgPriority(0, 3);
    SetBgPriority(1, 2);
    SetBgPriority(2, 1);
    SetBgPriority(3, 0);
    floor = gGameState.floor;
    floorKeep = (u16)floor;
    sWorldInspectCursor = gGameState.floor > 11 ? 11 : floor;

    sWorldInspectFloorCount = 0;

    for (i = 0; i <= 11; i++) {
        sWorldInspectWorlds[i] = gGameState.floors[i].world;

        if (sWorldInspectWorlds[i] != 0) {
            sWorldInspectFloorCount = i + 1;
        }
    }

    for (i = 0, fa = sWorldInspectFloorCount; i <= 13; i++) {
        if ((gGameState.availableWorlds & sWorldinspectMsgs[i].flags) != 0) {
            sWorldInspectWorlds[fa++] = sWorldinspectMsgs[i].world;

            if (fa > 11) {
                break;
            }
        }
    }

    sWorldInspectDetailOpen = 0;
    sWorldInspectBobPhase = 0;
    sWorldInspectCursorX = (sWorldinspectNavs[sWorldInspectCursor].x << 11) + 0x2000;
    sWorldInspectCursorY = (sWorldinspectNavs[sWorldInspectCursor].y << 11) - 0x600;
    sWorldInspectState = 0;
    sWorldInspectSteps = 16;
    sWorldInspectBarY[0] = -0x800;
    sWorldInspectBarY[1] = 0xA800;
    sWorldInspectBarX = -0x8000;
    LoadBgPalette(0, gUnk_09A3CE7C, 0x200);

    for (i = 0; i <= 11; i++) {
        if (sWorldInspectWorlds[i] != 0) {
            id = sWorldInspectWorlds[i];
            sWorldInspectIconPalettes[i] = LoadObjPalette(sWorldinspectMsgs[id].palette, sWorldinspectMsgs[id].paletteSize);
            id = sWorldInspectWorlds[i];
            sWorldInspectIconTiles[i] = LoadObjTiles(sWorldinspectMsgs[id].tiles, sWorldinspectMsgs[id].tilesSize);
            id = sWorldInspectWorlds[i];
            sWorldInspectIconSprites[i] = sWorldinspectMsgs[id].sprite;
        } else {
            sWorldInspectIconPalettes[i] = NULL;
            sWorldInspectIconTiles[i] = NULL;
            sWorldInspectIconSprites[i] = NULL;
        }
    }

    LoadBgTiles(0, gUnk_099FB53C, 0x6BC0);

#ifdef VERSION_EU
    if (gGameState.flags & GAME_FLAG_RIKU) {
        switch (gLanguage) {
        case LANGUAGE_FRENCH:
            RequestDma3Copy(gUnkEu_09A2D440, (u8*)GetBgCharBase(0) + 0x6400, 0x800);
            break;
        case LANGUAGE_SPANISH:
            RequestDma3Copy(gUnkEu_09A2E440, (u8*)GetBgCharBase(0) + 0x6400, 0x800);
            break;
        case LANGUAGE_ITALIAN:
            RequestDma3Copy(gUnkEu_09A2F440, (u8*)GetBgCharBase(0) + 0x6400, 0x800);
            break;
        case LANGUAGE_GERMAN:
            RequestDma3Copy(gUnkEu_09A30440, (u8*)GetBgCharBase(0) + 0x6400, 0x800);
            break;
        }
    } else {
        switch (gLanguage) {
        case LANGUAGE_FRENCH:
            RequestDma3Copy(gUnkEu_09A2CC40, (u8*)GetBgCharBase(0) + 0x800, 0x800);
            break;
        case LANGUAGE_SPANISH:
            RequestDma3Copy(gUnkEu_09A2DC40, (u8*)GetBgCharBase(0) + 0x800, 0x800);
            break;
        case LANGUAGE_ITALIAN:
            RequestDma3Copy(gUnkEu_09A2EC40, (u8*)GetBgCharBase(0) + 0x800, 0x800);
            break;
        case LANGUAGE_GERMAN:
            RequestDma3Copy(gUnkEu_09A2FC40, (u8*)GetBgCharBase(0) + 0x800, 0x800);
            break;
        }
    }
#endif

    LoadBgMap(0, gUnk_09A324DC, 0x500);
    DmaCopy16(3, gUnk_09A32EDC, sWorldInspectTilemap, 0x500);

    for (i = 0; i <= 11; i++) {
        if (sWorldInspectWorlds[i] != 0) {
            WorldInspectCopyTilemapRect(7, 4, gUnk_09A333DC, 0, 0, sWorldInspectTilemap, sWorldinspectNavs[i].x, sWorldinspectNavs[i].y);
        }
    }

    for (i = 0; i < sWorldInspectFloorCount - 1; i++) {
        if (sWorldInspectWorlds[i] != 0 && sWorldInspectWorlds[i + 1] != 0) {
            const WorldinspectConn* conn = sWorldinspectConns;
            id = sWorldinspectNavs[i].rect;
            WorldInspectCopyTilemapRect(conn[id].width, conn[id].height, gUnk_09A333DC, conn[id].x, conn[id].y, sWorldInspectTilemap, sWorldinspectNavs[i].x2, sWorldinspectNavs[i].y2);
        }
    }

    for (i = 0; i < sWorldInspectFloorCount; i++) {
        if (sWorldInspectWorlds[i] != 0) {
            if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
                if (i <= 8) {
                    WorldInspectCopyTilemapRect(3, 1, gUnk_09A333DC, i * 3, 9, sWorldInspectTilemap, sWorldinspectNavs[i].x + 3, sWorldinspectNavs[i].y + 2);
                } else {
                    WorldInspectCopyTilemapRect(4, 1, gUnk_09A333DC, (i - 9) * 4, 10, sWorldInspectTilemap, sWorldinspectNavs[i].x + 3, sWorldinspectNavs[i].y + 2);
                }
            } else {
                if (i <= 2) {
                    WorldInspectCopyTilemapRect(4, 1, gUnk_09A333DC, i * 4, 0x15, sWorldInspectTilemap, sWorldinspectNavs[i].x + 3, sWorldinspectNavs[i].y + 2);
                } else {
                    WorldInspectCopyTilemapRect(3, 1, gUnk_09A333DC, (i - 3) * 3, 0x16, sWorldInspectTilemap, sWorldinspectNavs[i].x + 3, sWorldinspectNavs[i].y + 2);
                }
            }
        }
    }

    for (i = 0; i < sWorldInspectFloorCount; i++) {
        if ((s16)floorKeep == i) {
            WorldInspectSetTilemapRectPalette(3, 7, 4, sWorldInspectTilemap, sWorldinspectNavs[i].x, sWorldinspectNavs[i].y);
        } else {
            WorldInspectSetTilemapRectPalette(2, 7, 4, sWorldInspectTilemap, sWorldinspectNavs[i].x, sWorldinspectNavs[i].y);
        }
    }

    LoadBgMap(1, sWorldInspectTilemap, 0x500);
    LoadBgMap(2, gUnk_09A33E9C, 0x500);
    LoadBgMap(3, gUnk_09A3399C, 0x500);
    WorldInspectLoadFloorTiles(sWorldInspectCursor);
    sWorldInspectHighlightPalette = LoadObjPalette(gUnk_09A3D09C, 0x20);
    sWorldInspectHighlightTiles = LoadObjTiles(gUnk_0999D41A, 0x400);
    AnimInit(&sWorldInspectHighlightAnim, gUnk_09EF97C4, gUnk_09EF97B0);
    AnimStart(&sWorldInspectHighlightAnim, 0, ANIM_FLAG_LOOP);
    sWorldInspectCursorPalette = LoadObjPalette(gUnk_09A3D0BC, 0x20);
    sWorldInspectCursorTiles = LoadObjTiles(gUnk_0999D8A8, 0xC0);
    AnimInit(&sWorldInspectCursorAnim, gUnk_09EF97DC, gUnk_09EF97CC);
    AnimStart(&sWorldInspectCursorAnim, 0, ANIM_FLAG_LOOP);
#ifdef VERSION_EU
    InitTextSlots(sWorldInspectNameText, 0x30);
#else
    InitTextSlots(sWorldInspectNameText, 0x18);
#endif
    sWorldInspectNameTextCount = WorldInspectLoadName(sWorldInspectWorlds[sWorldInspectCursor]);
#ifdef VERSION_EU
    InitTextSlots(sWorldInspectDescText, 0x78);
#else
    InitTextSlots(sWorldInspectDescText, 0x3C);
#endif
    sWorldInspectBarPalette = LoadObjPalette(gUnk_09A3D07C, 0x20);

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        sWorldInspectBarTiles = LoadObjTiles(gUnk_0999CFC6, 0x400);
        break;
    case LANGUAGE_FRENCH:
        sWorldInspectBarTiles = LoadObjTiles(gUnkEu_099A4CDA, 0x440);
        break;
    case LANGUAGE_SPANISH:
        sWorldInspectBarTiles = LoadObjTiles(gUnkEu_099A51AA, 0x400);
        break;
    case LANGUAGE_ITALIAN:
        sWorldInspectBarTiles = LoadObjTiles(gUnkEu_099A563A, 0x400);
        break;
    case LANGUAGE_GERMAN:
    default:
        sWorldInspectBarTiles = LoadObjTiles(gUnkEu_099A5ACA, 0x440);
        break;
    }
#elif defined(VERSION_JP)
    sWorldInspectBarTiles = LoadObjTiles(gUnk_0999CFC6, 0x3C0);
#else
    sWorldInspectBarTiles = LoadObjTiles(gUnk_0999CFC6, 0x400);
#endif
    EnableBg(0);
    EnableBg(1);
    DisableBg(2);
    DisableBg(3);
}

void mode_worldinspect_1() {
    UpdatePlayTime();
    sWorldInspectBobPhase += 2;

    switch (sWorldInspectState) {
    case 0:
        ApproachValue(&sWorldInspectBarY[0], 0, sWorldInspectSteps);
        ApproachValue(&sWorldInspectBarY[1], 0x9800, sWorldInspectSteps);
        sWorldInspectSteps--;

        if (sWorldInspectSteps <= 0) {
            sWorldInspectSteps = 16;
            sWorldInspectState = 1;
        }

        break;
    case 1:
        ApproachValue(&sWorldInspectBarX, 0, sWorldInspectSteps);
        sWorldInspectSteps--;

        if (sWorldInspectSteps <= 0) {
#ifdef VERSION_EU
            LoadBgMap(0, gUnk_09A329DC, 0x500);
#else
            LoadBgMap(0, gUnk_09A329DC, 0x500);
            ReleaseObjPalette(sWorldInspectBarPalette);
#endif
            sWorldInspectState = 2;
        }

        break;
    case 2:
        switch (sWorldInspectDetailOpen) {
        case 0:
            WorldInspectHandleInput();
            break;
        case 1:
            WorldInspectHandleDetailInput();
            break;
        }

        break;
    case 3:
        ApproachValue(&sWorldInspectBarX, -0x8000, sWorldInspectSteps);
        sWorldInspectSteps--;

        if (sWorldInspectSteps <= 0) {
            sWorldInspectSteps = 16;
            sWorldInspectState = 4;
        }

        break;
    case 4:
        ApproachValue(&sWorldInspectBarY[0], -0x800, sWorldInspectSteps);
        ApproachValue(&sWorldInspectBarY[1], 0xA800, sWorldInspectSteps);
        sWorldInspectSteps--;

        if (sWorldInspectSteps <= 0) {
            FadeStartOut(FADE_MODE_BLACK, 16);
            sWorldInspectState = 5;
        }

        break;
    case 5:
        if (!FadeIsActive()) {
            ReturnToMap(sWorldInspectReturnToMenu);
        }

        break;
    }

    WorldInspectDraw();
}

void mode_worldinspect_2() {
    s32 i;

    ReleaseObjPalette(sWorldInspectBarPalette);
    ReleaseObjTiles(sWorldInspectBarTiles);
    ReleaseObjPalette(sWorldInspectHighlightPalette);
    ReleaseObjTiles(sWorldInspectHighlightTiles);
    ReleaseObjPalette(sWorldInspectCursorPalette);
    ReleaseObjTiles(sWorldInspectCursorTiles);

    for (i = 0; i < 12; i++) {
        if (sWorldInspectIconPalettes[i]) {
            ReleaseObjPalette(sWorldInspectIconPalettes[i]);
        }

        if (sWorldInspectIconTiles[i]) {
            ReleaseObjTiles(sWorldInspectIconTiles[i]);
        }
    }

#ifdef VERSION_EU
    FreeTextSlots(sWorldInspectNameText, 0x30);
#else
    FreeTextSlots(sWorldInspectNameText, 0x18);
#endif
#ifdef VERSION_EU
    FreeTextSlots(sWorldInspectDescText, 0x78);
#else
    FreeTextSlots(sWorldInspectDescText, 0x3C);
#endif
    EwramFree(sWorldInspectTilemap);
}

Mode gModeWorldinspect = {
    "mode_worldinspect",
    (ModeInitFunc)mode_worldinspect_0,
    mode_worldinspect_1,
    mode_worldinspect_2,
};
