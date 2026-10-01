#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "display.h"
#include "text.h"
#include "monsgage.h"
#include "mode_ms.h"
#include "gba/keys.h"
#include "moogle_assets.h"
#include "sprites_moogle_shop.h"
#include "sprites_card_pictures.h"
#include "card_ids.h"
#include "ms_types.h"
#include "gba/io_reg.h"
#include "mode_ms_top_api.h"
#include "malloc.h"
#include "fade.h"
#include "mode_test_api.h"
#include "player_progression.h"
#include "songs.h"
#include "anim.h"
#include "card.h"
#include "card_api.h"
#include "card_def_data.h"
#include "card_types.h"
#include "engine_math.h"
#include "game_state.h"
#include "gba/defines.h"
#include "gba/macro.h"
#include "key.h"
#include "m4a_song.h"
#include "map_types.h"
#include "mode.h"
#include "obj.h"
#include "obj_api.h"
#include <stddef.h>
#include "taskpool.h"
#include "text_types.h"
#include "types.h"

#ifdef VERSION_EU
static void* sUnkEu_09F84F5C[5] = {
    gUnkEu_09A8DAA0,
    gUnk_09A3B25C,
    gUnkEu_09A91920,
    gUnkEu_09A91420,
    gUnk_09A3B75C,
};

static u16* sUnkEu_09F84F70[5] = {
    gMoogleAssetEu_09A8F3A0,
    gMoogleAssetEu_09A8F3A0,
    gMoogleAssetEu_09A92E20,
    gMoogleAssetEu_09A92620,
    gMoogleAssetEu_09A91E20,
};

static u16* sUnkEu_09F84F84[5] = {
    gMoogleAssetEu_09A8FBA0,
    gMoogleAssetEu_09A8FBA0,
    gMoogleAssetEu_09A94620,
    gMoogleAssetEu_09A93E20,
    gMoogleAssetEu_09A93620,
};
#endif

static const MooglePackMenuEntry sMooglePackMenuEntries[4] = {
#if defined(VERSION_US)
    {-1, 2, 5, 1, 67, 16, gMoogleAssetUs_09A387DC, 1280, 5, 3, 40, 24, 0, {{gMoogleAssetUs_09A39BDC, 0, 0}, {gMoogleAssetUs_09A39BDC, 0, 16}, {gMoogleAssetUs_09A3A3DC, 0, 0}, {gMoogleAssetUs_09A3A3DC, 0, 16}}},
    {-1, 3, 0, -1, 163, 16, gMoogleAssetUs_09A38CDC, 1280, 17, 3, 136, 24, 0, {{gMoogleAssetUs_09A39BDC, 12, 0}, {gMoogleAssetUs_09A39BDC, 12, 16}, {gMoogleAssetUs_09A3A3DC, 12, 0}, {gMoogleAssetUs_09A3A3DC, 12, 16}}},
    {0, -1, 5, 3, 67, 80, gMoogleAssetUs_09A391DC, 1280, 5, 11, 40, 88, 0, {{gMoogleAssetUs_09A39BDC, 0, 8}, {gMoogleAssetUs_09A39BDC, 0, 24}, {gMoogleAssetUs_09A3A3DC, 0, 8}, {gMoogleAssetUs_09A3A3DC, 0, 24}}},
    {1, -1, 2, -1, 163, 80, gMoogleAssetUs_09A396DC, 1280, 17, 11, 136, 88, 0, {{gMoogleAssetUs_09A39BDC, 12, 8}, {gMoogleAssetUs_09A39BDC, 12, 24}, {gMoogleAssetUs_09A3A3DC, 12, 8}, {gMoogleAssetUs_09A3A3DC, 12, 24}}},
#elif defined(VERSION_JP)
    {-1, 2, 5, 1, 67, 16, gMoogleAssetJp_099ED264, 1280, 5, 3, 40, 24, 0, {{gMoogleAssetJp_099EE664, 0, 0}, {gMoogleAssetJp_099EE664, 0, 16}, {gMoogleAssetJp_099EEE64, 0, 0}, {gMoogleAssetJp_099EEE64, 0, 16}}},
    {-1, 3, 0, -1, 163, 16, gMoogleAssetJp_099ED764, 1280, 17, 3, 136, 24, 0, {{gMoogleAssetJp_099EE664, 12, 0}, {gMoogleAssetJp_099EE664, 12, 16}, {gMoogleAssetJp_099EEE64, 12, 0}, {gMoogleAssetJp_099EEE64, 12, 16}}},
    {0, -1, 5, 3, 67, 80, gMoogleAssetJp_099EDC64, 1280, 5, 11, 40, 88, 0, {{gMoogleAssetJp_099EE664, 0, 8}, {gMoogleAssetJp_099EE664, 0, 24}, {gMoogleAssetJp_099EEE64, 0, 8}, {gMoogleAssetJp_099EEE64, 0, 24}}},
    {1, -1, 2, -1, 163, 80, gMoogleAssetJp_099EE164, 1280, 17, 11, 136, 88, 0, {{gMoogleAssetJp_099EE664, 12, 8}, {gMoogleAssetJp_099EE664, 12, 24}, {gMoogleAssetJp_099EEE64, 12, 8}, {gMoogleAssetJp_099EEE64, 12, 24}}},
#elif defined(VERSION_EU)
    {-1, 2, 5, 1, 67, 16, gMoogleAssetEu_09A8DFA0, 1280, 5, 3, 40, 24, 0, {{sUnkEu_09F84F70, 0, 0}, {sUnkEu_09F84F70, 0, 16}, {sUnkEu_09F84F84, 0, 0}, {sUnkEu_09F84F84, 0, 16}}},
    {-1, 3, 0, -1, 163, 16, gMoogleAssetEu_09A8E4A0, 1280, 17, 3, 136, 24, 0, {{sUnkEu_09F84F70, 12, 0}, {sUnkEu_09F84F70, 12, 16}, {sUnkEu_09F84F84, 12, 0}, {sUnkEu_09F84F84, 12, 16}}},
    {0, -1, 5, 3, 67, 80, gMoogleAssetEu_09A8E9A0, 1280, 5, 11, 40, 88, 0, {{sUnkEu_09F84F70, 0, 8}, {sUnkEu_09F84F70, 0, 24}, {sUnkEu_09F84F84, 0, 8}, {sUnkEu_09F84F84, 0, 24}}},
    {1, -1, 2, -1, 163, 80, gMoogleAssetEu_09A8EEA0, 1280, 17, 11, 136, 88, 0, {{sUnkEu_09F84F70, 12, 8}, {sUnkEu_09F84F70, 12, 24}, {sUnkEu_09F84F84, 12, 8}, {sUnkEu_09F84F84, 12, 24}}},
#endif
};

static const MooglePackSpriteDef sMooglePackSpriteDefs[4] = {
#if defined(VERSION_US)
    {gMoogleAssetUs_09A3DA9C, 32, {0, 0}, gMoogleAssetUs_099A3EC4, 800, {0, 0}, gMoogleAssetUs_099A3EA4, 10, 12},
    {gMoogleAssetUs_09A3DABC, 32, {0, 0}, gMoogleAssetUs_099A4204, 608, {0, 0}, gMoogleAssetUs_099A41E4, 12, 13},
    {gMoogleAssetUs_09A3DADC, 32, {0, 0}, gMoogleAssetUs_099A4484, 608, {0, 0}, gMoogleAssetUs_099A4464, 12, 13},
    {gMoogleAssetUs_09A3DAFC, 32, {0, 0}, gMoogleAssetUs_099A4704, 896, {0, 0}, gMoogleAssetUs_099A46E4, 9, 7},
#elif defined(VERSION_JP)
    {gMoogleAssetJp_099F2524, 32, {0, 0}, gMoogleAssetJp_0995894C, 800, {0, 0}, gMoogleAssetJp_0995892C, 10, 12},
    {gMoogleAssetJp_099F2544, 32, {0, 0}, gMoogleAssetJp_09958C8C, 608, {0, 0}, gMoogleAssetJp_09958C6C, 12, 13},
    {gMoogleAssetJp_099F2564, 32, {0, 0}, gMoogleAssetJp_09958F0C, 608, {0, 0}, gMoogleAssetJp_09958EEC, 12, 13},
    {gMoogleAssetJp_099F2584, 32, {0, 0}, gMoogleAssetJp_0995918C, 896, {0, 0}, gMoogleAssetJp_0995916C, 9, 7},
#elif defined(VERSION_EU)
    {gMoogleAssetEu_09A9B560, 32, {0, 0}, gMoogleAssetEu_099B1E48, 800, {0, 0}, gMoogleAssetEu_099B1E28, 10, 12},
    {gMoogleAssetEu_09A9B580, 32, {0, 0}, gMoogleAssetEu_099B2188, 608, {0, 0}, gMoogleAssetEu_099B2168, 12, 13},
    {gMoogleAssetEu_09A9B5A0, 32, {0, 0}, gMoogleAssetEu_099B2408, 608, {0, 0}, gMoogleAssetEu_099B23E8, 12, 13},
    {gMoogleAssetEu_09A9B5C0, 32, {0, 0}, gMoogleAssetEu_099B2688, 896, {0, 0}, gMoogleAssetEu_099B2668, 9, 7},
#endif
};

static const u16 sMoogleCardValueWeights[10] = {
    5,
    15,
    15,
    16,
    14,
    10,
    10,
    6,
    5,
    4,
};

static const MooglePackCardDef sMoogleAttackPackCards[17] = {
    {0, {0, 0}, 0, {0, 0, 0, 0}},
    {CARD_ID(CARD_THREE_WISHES, 0), {0, 0}, 1, {20, 14, 4, 4}},
    {CARD_ID(CARD_PUMPKINHEAD, 0), {0, 0}, 3, {20, 14, 4, 4}},
    {CARD_ID(CARD_WISHING_STAR, 0), {0, 0}, 5, {20, 14, 4, 4}},
    {CARD_ID(CARD_LADY_LUCK, 0), {0, 0}, 10, {20, 14, 4, 4}},
    {CARD_ID(CARD_OLYMPIA, 0), {0, 0}, 8, {20, 14, 4, 4}},
    {CARD_ID(CARD_METAL_CHOCOBO, 0), {0, 0}, 7, {0, 5, 10, 6}},
    {CARD_ID(CARD_CRABCLAW, 0), {0, 0}, 2, {0, 5, 10, 6}},
    {CARD_ID(CARD_FAIRY_HARP, 0), {0, 0}, 4, {0, 5, 10, 6}},
    {CARD_ID(CARD_LIONHEART, 0), {0, 0}, 9, {0, 5, 10, 6}},
    {CARD_ID(CARD_SPELLBINDER, 0), {0, 0}, 6, {0, 5, 10, 6}},
    {CARD_ID(CARD_DIVINE_ROSE, 0), {0, 0}, 11, {0, 5, 10, 6}},
    {CARD_ID(CARD_OATHKEEPER, 0), {0, 0}, 12, {0, 0, 5, 10}},
    {CARD_ID(CARD_OBLIVION, 0), {0, 0}, 13, {0, 0, 5, 10}},
    {CARD_ID(CARD_DIAMOND_DUST, 0), {0, 0}, 15, {0, 0, 5, 10}},
    {CARD_ID(CARD_ONE_WINGED_ANGEL, 0), {0, 0}, 16, {0, 0, 5, 10}},
    {CARD_ID(CARD_ULTIMA_WEAPON, 0), {0, 0}, 14, {0, 0, 0, 4}},
};

static const MooglePackCardDef sMoogleMagicPackCards[14] = {
    {CARD_ID(CARD_FIRE, 0), {0, 0}, 17, {15, 10, 5, 5}},
    {CARD_ID(CARD_BLIZZARD, 0), {0, 0}, 18, {15, 10, 5, 5}},
    {CARD_ID(CARD_THUNDER, 0), {0, 0}, 19, {15, 10, 5, 5}},
    {CARD_ID(CARD_GRAVITY, 0), {0, 0}, 21, {0, 5, 10, 5}},
    {CARD_ID(CARD_STOP, 0), {0, 0}, 22, {0, 5, 10, 5}},
    {CARD_ID(CARD_AERO, 0), {0, 0}, 23, {0, 5, 10, 5}},
    {CARD_ID(CARD_CURE, 0), {0, 0}, 20, {10, 5, 0, 0}},
    {CARD_ID(CARD_SIMBA, 0), {0, 0}, 24, {20, 5, 5, 5}},
    {CARD_ID(CARD_GENIE, 0), {0, 0}, 25, {10, 20, 8, 10}},
    {CARD_ID(CARD_BAMBI, 0), {0, 0}, 26, {0, 0, 8, 10}},
    {CARD_ID(CARD_DUMBO, 0), {0, 0}, 27, {10, 20, 8, 10}},
    {CARD_ID(CARD_TINKER_BELL, 0), {0, 0}, 28, {0, 0, 8, 10}},
    {CARD_ID(CARD_MUSHU, 0), {0, 0}, 29, {0, 0, 8, 10}},
    {CARD_ID(CARD_CLOUD, 0), {0, 0}, 30, {5, 5, 10, 15}},
};

static const MooglePackCardDef sMoogleItemPackCards[7] = {
    {CARD_ID(CARD_POTION, 0), {0, 0}, 31, {50, 40, 0, 0}},
    {CARD_ID(CARD_ETHER, 0), {0, 0}, 34, {50, 40, 20, 15}},
    {CARD_ID(CARD_HI_POTION, 0), {0, 0}, 32, {0, 10, 25, 20}},
    {CARD_ID(CARD_MEGA_ETHER, 0), {0, 0}, 35, {0, 10, 25, 20}},
    {CARD_ID(CARD_MEGA_POTION, 0), {0, 0}, 33, {0, 0, 15, 20}},
    {CARD_ID(CARD_ELIXIR, 0), {0, 0}, 36, {0, 0, 15, 15}},
    {CARD_ID(CARD_MEGALIXIR, 0), {0, 0}, 37, {0, 0, 0, 10}},
};

static const MooglePackCardTable sMooglePackCardTables[3] = {
    {sMoogleAttackPackCards, 17, {0, 0}},
    {sMoogleMagicPackCards, 14, {0, 0}},
    {sMoogleItemPackCards, 7, {0, 0}},
};

static const s16 sMooglePackTiers[13][4][4] = {
    {{0, 0, -1, -1}, {0, 0, -1, -1}, {0, 0, -1, -1}, {0, 0, -1, -1}},
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 1, 1, 2}, {0, 1, 1, 2}, {0, 1, 1, 2}, {0, 1, 1, 2}},
    {{0, 1, 1, 2}, {0, 1, 1, 2}, {0, 1, 1, 2}, {0, 1, 1, 2}},
    {{0, 1, 1, 2}, {0, 1, 1, 2}, {0, 1, 1, 2}, {0, 1, 1, 2}},
    {{0, 1, 1, 2}, {0, 1, 1, 2}, {0, 1, 1, 2}, {0, 1, 1, 2}},
    {{0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3}},
    {{0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3}},
    {{0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3}},
};

static const s16 sMooglePackPrices[4][4] = {
    {100, 200, 300, 500},
    {200, 250, 270, 300},
    {150, 200, 300, 350},
    {150, 200, 300, 400},
};

static MooglePackCardWork sMooglePackCards[5];
static struct ObjPalette* sMooglePackCard00Palette;
static struct ObjTiles* sMooglePackValueTiles;
static struct ObjPalette* sMooglePackPremiumValuePalette;
static struct ObjTiles* sMooglePackPremiumValueTiles;
static struct ObjPalette* sMooglePackCategoryPalette;
static TextSlot* sMooglePackNameText;
static u8 sMooglePackNameTextCount;
static TextSlot* sMooglePackDescText;
static u8 sMooglePackDescTextCount;
static struct ObjTiles* sMooglePackPremiumTiles;
static AnimState sMooglePackPremiumAnim;
static TaskPool sMooglePackHosiTasks[5];
static s32 sMooglePackCursorX;
static s32 sMooglePackCursorY;
static struct ObjTiles* sMooglePackCursorTiles;
static struct ObjPalette* sMooglePackCursorPalette;
static AnimState sMooglePackCursorAnim;
static u8 sMoogleShopHasPacks;
static s16 sMoogleShopState;
static s16 sMoogleShopRowCursor;
static s16 sMoogleShopRowCategory[4];
static s16 sMoogleShopPackCursor;
static s16 sMoogleShopPacks[4][4][2];
static u16 sMooglePackCardIds[5];
static s16 sMooglePackCardCursor;
static u16 sMooglePackBoughtFlags[32];
static u16 sMoogleFreePackFlags[2];
static struct ObjTiles* sMoogleShopCursorTiles;
static struct ObjPalette* sMoogleShopCursorPalette;
static AnimState sMoogleShopCursorAnim;
static void* sMooglePackTiles[4];
static void* sMooglePackPalettes[4];
static void* sMooglePackSprites[4];
static u16* sMoogleShopTilemap;
static s32 sMoogleShopCursorX;
static s32 sMoogleShopCursorY;
static u8 sMoogleShopBackToTop;

void MoogleShopClearFlags() {
    s32 i;

    for (i = 0; i < 32; i++) {
        sMooglePackBoughtFlags[i] = 0;
    }

    for (i = 0; i < 2; i++) {
        sMoogleFreePackFlags[i] = 0;
    }
}

void MoogleShopSaveFlags(void* a) {
    u16* p = a;
    s32 i;

    for (i = 0; i < 32; i++) {
        p[i] = sMooglePackBoughtFlags[i];
    }

    for (i = 0; i < 2; i++) {
        p[i + 32] = sMoogleFreePackFlags[i];
    }
}

void MoogleShopLoadFlags(void* a) {
    u16* p = a;
    s32 i;

    for (i = 0; i < 32; i++) {
        sMooglePackBoughtFlags[i] = p[i];
    }

    for (i = 0; i < 2; i++) {
        sMoogleFreePackFlags[i] = p[i + 32];
    }
}

void SetMooglePackBought(u16 a, u16 b, u16 c) {
    u16 v;
    v = a * 16 + b * 4 + c;

    if (v <= 0x1FF) {
        sMooglePackBoughtFlags[v >> 4] |= 1 << (v & 15);
    }
}

void ClearMooglePackBought(u16 a, u16 b, u16 c) {
    u16 v;
    v = a * 16 + b * 4 + c;

    if (v <= 0x1FF) {
        sMooglePackBoughtFlags[v >> 4] &= ~(1 << (v & 15));
    }
}

u8 IsMooglePackBought(u16 a, u16 b, u16 c) {
    u16 v;
    v = a * 16 + b * 4 + c;

    if (v <= 0x1FF) {
        return sMooglePackBoughtFlags[v >> 4] >> (v & 15) & 1;
    }

    return 0;
}

void SetMoogleFreePackFlag(u16 a) {
    if (a <= 31) {
        sMoogleFreePackFlags[a >> 4] |= 1 << (a & 15);
    }
}

void ClearMoogleFreePackFlag(u16 a) {
    if (a <= 31) {
        sMoogleFreePackFlags[a >> 4] &= ~(1 << (a & 15));
    }
}

u8 GetMoogleFreePackFlag(u16 a) {
    if (a <= 31) {
        return sMoogleFreePackFlags[a >> 4] >> (a & 15) & 1;
    }

    return 0;
}

void ClearMoogleRoomFlags() {
    s16 i;
    s16 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            ClearMooglePackBought(gMapFloorState.room, i, j);
        }
    }

    ClearMoogleFreePackFlag(gMapFloorState.room);
}

u8 BuildMooglePackList(s16 a) {
    s16 i;
    s16 k;
    s16 m;
    s16 n;
    s16 v;
    s32 r;

    for (i = 0; i < 4; i++) {
        sMoogleShopRowCategory[i] = -1;

        for (k = 0; k < 4; k++) {
            sMoogleShopPacks[i][k][0] = -1;
        }
    }

    n = 0;

    for (i = 0; i < 4; i++) {
        m = 0;

        for (k = 0; k < 4; k++) {
            v = sMooglePackTiers[a][i][k];

            if (IsMooglePackBought(gMapFloorState.room, i, k) == 0) {
                if (v >= 0) {
                    sMoogleShopPacks[n][m][0] = k;
                    sMoogleShopPacks[n][m][1] = v;
                    m++;
                }
            }
        }

        if (m > 0) {
            sMoogleShopRowCategory[n] = i;
            n++;
        }
    }

    r = 0;

    if (n > 0) {
        r = 1;
    }

    return r;
}

void MoogleShopCopyTilemapRect(u16 w, s16 h, u16* src, s16 sx, s16 sy, u16* dst, s16 dx, s16 dy) {
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

void DrawMoogleShopPacks(s16 a) {
    s32 j;

    DmaFill16(3, 0, sMoogleShopTilemap, 0x500);

    for (j = 0; j < 4; j++) {
        if (sMoogleShopPacks[a][j][0] >= 0) {
            LoadDecimalDigitTiles(sMooglePackPrices[sMoogleShopRowCategory[a]][sMoogleShopPacks[a][j][1]], gUnk_09A18EBC,
                (u8*)GetBgCharBase(2) + (j * 0xC0 + 0xC0), 0x40, 3);
            MoogleShopCopyTilemapRect(12, 8, LANGSTR(sMooglePackMenuEntries[j].packTilemaps[sMoogleShopRowCategory[a]].tilemap),
                sMooglePackMenuEntries[j].packTilemaps[sMoogleShopRowCategory[a]].srcX,
                sMooglePackMenuEntries[j].packTilemaps[sMoogleShopRowCategory[a]].srcY, sMoogleShopTilemap,
                sMooglePackMenuEntries[j].tilemapX, sMooglePackMenuEntries[j].tilemapY);
        }
    }

    LoadBgMap(2, sMoogleShopTilemap, 0x500);
}

s32 MoogleShopReadMenuKeys() {
    s32 k;

    k = GetKeysPressed() & (A_BUTTON | B_BUTTON | SELECT_BUTTON | START_BUTTON);
    return k | (GetKeysRepeat() & (DPAD_ANY | R_BUTTON | L_BUTTON));
}

void InitMooglePackOpening(s16 x, s16 y) {
    s16 i;
    u16 id;
    TextSlot** p;

    for (i = 0; i < 5; i++) {
        id = sMooglePackCardIds[i];

        if (id & 0x8000) {
            sMooglePackCards[i].premium = 1;
        } else {
            sMooglePackCards[i].premium = 0;
        }

        sMooglePackCards[i].revealed = 0;
        id &= 0xFFF;
        sMooglePackCards[i].palette = LoadObjPalette(gCardDefs[id].palette, 0x20);
        FadeSetPaletteExcluded(sMooglePackCards[i].palette->index + 0x10, 1);
        sMooglePackCards[i].tiles = LoadObjTiles(gCardDefs[id].tiles, 0x200);
        sMooglePackCards[i].gfx = gCardDefs[id].gfx;
        sMooglePackCards[i].palette2 = LoadObjPalette(gUnk_09A3DB1C + gCardDefs[id].category * 16, 0x20);
        FadeSetPaletteExcluded(sMooglePackCards[i].palette2->index + 0x10, 1);
        sMooglePackCards[i].tiles2 = LoadObjTiles(gUnk_099A4B9A, 0x1D80);
        sMooglePackCards[i].backSprite = NULL;
        AnimInit(&sMooglePackCards[i].anim, gUnk_09EF9A48, gUnk_09EF9A20);
        AnimStart(&sMooglePackCards[i].anim, 0, ANIM_FLAG_LOOP);
        sMooglePackCards[i].x = x << 8;
        sMooglePackCards[i].y = y << 8;
        sMooglePackCards[i].scale = 2;
        sMooglePackCards[i].flipAngle = 0;
        sMooglePackCards[i].state = 0;
        sMooglePackCards[i].timer = 0;
    }

    sMooglePackCard00Palette = LoadObjPalette(gCard00Palette, 0x20);
    FadeSetPaletteExcluded(sMooglePackCard00Palette->index + 0x10, 1);
    sMooglePackValueTiles = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    sMooglePackPremiumValuePalette = LoadObjPalette(gBStatesPalette, 0x20);
    FadeSetPaletteExcluded(sMooglePackPremiumValuePalette->index + 0x10, 1);
    sMooglePackPremiumValueTiles = LoadObjTiles(gUnk_0905ED36, 0x140);
    sMooglePackCursorPalette = LoadObjPalette(gUnk_09A3DA7C, 0x20);
    sMooglePackCursorTiles = LoadObjTiles(gUnk_099A3CE4, 0x1C0);
    AnimInit(&sMooglePackCursorAnim, gUnk_09EF99F8, gUnk_09EF99D8);
    AnimStart(&sMooglePackCursorAnim, 0, ANIM_FLAG_LOOP);
    FadeSetPaletteExcluded(sMooglePackCursorPalette->index + 0x10, 1);
    sMooglePackCategoryPalette = LoadObjPalette(gUnk_09A3DB7C, 0x20);
    FadeSetPaletteExcluded(sMooglePackCategoryPalette->index + 0x10, 1);
    p = &sMooglePackNameText;
    *p = EwramAlloc(0x24 * sizeof(TextSlot));
    InitTextSlots(sMooglePackNameText, 0x24);
    p = &sMooglePackDescText;
    *p = EwramAlloc(0x5A * sizeof(TextSlot));
    InitTextSlots(sMooglePackDescText, 0x5A);
    sMooglePackPremiumTiles = LoadObjTiles(gUnk_0908B1B4, 0x9A0);
    AnimInit(&sMooglePackPremiumAnim, gUnk_09EEA164, gUnk_09EEA148);
    AnimStart(&sMooglePackPremiumAnim, 0, ANIM_FLAG_LOOP);

    for (i = 0; i < 5; i++) {
        TaskPoolInit(&sMooglePackHosiTasks[i], 8);
    }

    sMooglePackCards[0].timer = 15;
}

void ReleaseMooglePackOpening() {
    s16 i;

    for (i = 0; i < 5; i++) {
        FadeSetPaletteExcluded(sMooglePackCards[i].palette->index + 0x10, 0);
        ReleaseObjPalette(sMooglePackCards[i].palette);
        ReleaseObjTiles(sMooglePackCards[i].tiles);
        FadeSetPaletteExcluded(sMooglePackCards[i].palette2->index + 0x10, 0);
        ReleaseObjPalette(sMooglePackCards[i].palette2);
        ReleaseObjTiles(sMooglePackCards[i].tiles2);
    }

    FadeSetPaletteExcluded(sMooglePackCursorPalette->index + 0x10, 0);
    ReleaseObjPalette(sMooglePackCursorPalette);
    ReleaseObjTiles(sMooglePackCursorTiles);
    FadeSetPaletteExcluded(sMooglePackCategoryPalette->index + 0x10, 0);
    ReleaseObjPalette(sMooglePackCategoryPalette);
    FreeTextSlots(sMooglePackNameText, 0x24);
    EwramFree(sMooglePackNameText);
    FreeTextSlots(sMooglePackDescText, 0x5A);
    EwramFree(sMooglePackDescText);
    FadeSetPaletteExcluded(sMooglePackCard00Palette->index + 0x10, 0);
    ReleaseObjPalette(sMooglePackCard00Palette);
    ReleaseObjTiles(sMooglePackValueTiles);
    FadeSetPaletteExcluded(sMooglePackPremiumValuePalette->index + 0x10, 0);
    ReleaseObjPalette(sMooglePackPremiumValuePalette);
    ReleaseObjTiles(sMooglePackPremiumValueTiles);
    ReleaseObjTiles(sMooglePackPremiumTiles);

    for (i = 0; i < 5; i++) {
        TaskPoolDestroy(&sMooglePackHosiTasks[i]);
    }
}

void DrawMooglePackOpening() {
    s16 i;
    ObjAffine* affine;
    void* obj;
    s32 v;
    void* anim;

    anim = AnimUpdate(&sMooglePackPremiumAnim);

    for (i = 0; i < 5; i++) {
        if (sMooglePackCards[i].revealed == 0) {
            v = sMooglePackCards[i].scale;
            affine = AllocObjAffine(0, v, v, 0);
            obj = AnimUpdate(&sMooglePackCards[i].anim);
        } else {
            v = sMooglePackCards[i].scale * -gSineTable[(sMooglePackCards[i].flipAngle & 0xFF) + 0x40] >> 8;
            affine = AllocObjAffine(0, v, sMooglePackCards[i].scale, 0);
            obj = sMooglePackCards[i].backSprite;
        }

        if (v != 0) {
            DrawSprite(sMooglePackCards[i].x >> 8, sMooglePackCards[i].y >> 8, obj, sMooglePackCards[i].tiles2, sMooglePackCards[i].palette2, affine, 0, 0x50);

            if (sMooglePackCards[i].revealed != 0) {
                DrawSprite(sMooglePackCards[i].x >> 8, sMooglePackCards[i].y >> 8, sMooglePackCards[i].gfx, sMooglePackCards[i].tiles, sMooglePackCards[i].palette, affine, 0, 0x58);

                if (sMooglePackCards[i].premium != 0) {
                    DrawSprite(sMooglePackCards[i].x >> 8, sMooglePackCards[i].y >> 8, gUnk_09EE9894[gCardDefs[sMooglePackCardIds[i] & 0xFFF].value], sMooglePackPremiumValueTiles, sMooglePackPremiumValuePalette, affine, 0, 0x48);
                    DrawSprite(sMooglePackCards[i].x >> 8, sMooglePackCards[i].y >> 8, anim, sMooglePackPremiumTiles, sMooglePackCard00Palette, affine, 0, 0x40);
                } else {
                    DrawSprite(sMooglePackCards[i].x >> 8, sMooglePackCards[i].y >> 8, gUnk_09EE981C[gCardDefs[sMooglePackCardIds[i] & 0xFFF].value], sMooglePackValueTiles, sMooglePackCard00Palette, affine, 0, 0x48);
                }
            }
        }

        if (sMooglePackCards[i].state == 9) {
            DrawTextSlots(0x30, 0x63, sMooglePackNameText, sMooglePackCategoryPalette, 0, sMooglePackNameTextCount);
            DrawTextSlots(0x31, 0x72, sMooglePackDescText, sMooglePackCursorPalette, 0, sMooglePackDescTextCount);
            ApproachValueHalf(&sMooglePackCursorX, sMooglePackCards[sMooglePackCardCursor].x - 0x1000);
            ApproachValueHalf(&sMooglePackCursorY, sMooglePackCards[sMooglePackCardCursor].y - 0x2000);
            DrawSprite(sMooglePackCursorX >> 8, sMooglePackCursorY >> 8, AnimUpdate(&sMooglePackCursorAnim), sMooglePackCursorTiles, sMooglePackCursorPalette, NULL, 0, 0);
        }
    }

    for (i = 0; i < 5; i++) {
        TaskPoolDraw(&sMooglePackHosiTasks[i]);
    }
}

u8 UpdateMooglePackOpening(u16 a) {
    MsShopHosiArg arg0;
    MsShopHosiArg arg1;
    MsShopHosiArg arg2;
    u8 result;
    s16 i;
    s16 j;
    s16 k;
    s16 old;
    u16 keys;
    u16 d;
    s32 f;
    s32 g;
    s32 h;

    result = 1;

    for (i = 0; i < 5; i++) {
        switch (sMooglePackCards[i].state) {
        case 0:
            if (FadeIsActive() == 0) {
                if (sMooglePackCards[i].timer != 0) {
                    sMooglePackCards[i].state = 1;
                }
            }

            break;
        case 1:
            ApproachValue(&sMooglePackCards[i].x, i * 10240 + 0x2800, sMooglePackCards[i].timer);
            ApproachValue(&sMooglePackCards[i].y, 0x6400, sMooglePackCards[i].timer);
            ApproachValue(&sMooglePackCards[i].scale, 0x100, sMooglePackCards[i].timer);

            if (--sMooglePackCards[i].timer == 0) {
                if (sMooglePackCards[i].premium != 0) {
                    sMooglePackCards[i].state = 5;
                } else {
                    sMooglePackCards[i].state = 2;
                }

                if (i <= 3) {
                    sMooglePackCards[i + 1].timer = 15;
                } else {
                    for (j = 0; j < 5; j++) {
                        if (sMooglePackCards[j].state == 2) {
                            sMooglePackCards[j].timer = 8;
                            break;
                        }
                    }

                    if (j == 5) {
                        sMooglePackCards[0].timer = 8;
                    }
                }
            }

            break;
        case 2:
            if (sMooglePackCards[i].timer != 0) {
                if (AnimGetFrame(&sMooglePackCards[i].anim) == 3 || AnimGetFrame(&sMooglePackCards[i].anim) == 8) {
                    ReleaseObjPalette(sMooglePackCards[i].palette2);
                    ReleaseObjTiles(sMooglePackCards[i].tiles2);
                    sMooglePackCards[i].palette2 = LoadObjPalette(gCard00Palette, 0x20);
                    FadeSetPaletteExcluded(sMooglePackCards[i].palette2->index + 0x10, 1);
                    sMooglePackCards[i].tiles2 = LoadObjTiles(gCardBacks[gCardDefs[sMooglePackCardIds[i] & 0xFFF].category].tiles, 0x300);
                    sMooglePackCards[i].backSprite = gCardBacks[gCardDefs[sMooglePackCardIds[i] & 0xFFF].category].gfx;
                    sMooglePackCards[i].flipAngle = 0x40;
                    sMooglePackCards[i].state = 3;
                    sMooglePackCards[i].revealed = 1;
                }
            }

            break;
        case 3:
            d = 0x80 - sMooglePackCards[i].flipAngle;
            sMooglePackCards[i].flipAngle += d / sMooglePackCards[i].timer;

            if (--sMooglePackCards[i].timer == 0) {
                sMooglePackCards[i].timer = 5;
                sMooglePackCards[i].state = 4;
            }

            break;
        case 4:
            ApproachValue(&sMooglePackCards[i].y, 0x4600, sMooglePackCards[i].timer);

            if (--sMooglePackCards[i].timer == 0) {
                m4aSongNumStart(SONG_SYS_KAIHUKU);
                sMooglePackCards[i].state = 8;

                for (j = 0; j < 5; j++) {
                    if (sMooglePackCards[j].state == 2) {
                        sMooglePackCards[j].timer = 8;
                        break;
                    }
                }

                if (j == 5) {
                    for (j = 0; j < 5; j++) {
                        if (sMooglePackCards[j].state == 5) {
                            sMooglePackCards[j].timer = 8;
                            break;
                        }
                    }

                    if (j == 5) {
                        sMooglePackCards[0].timer = 60;
                    }
                }
            }

            break;
        case 5:
            if (sMooglePackCards[i].timer != 0) {
                if (AnimGetFrame(&sMooglePackCards[i].anim) == 3 || AnimGetFrame(&sMooglePackCards[i].anim) == 8) {
                    ReleaseObjPalette(sMooglePackCards[i].palette2);
                    ReleaseObjTiles(sMooglePackCards[i].tiles2);
                    sMooglePackCards[i].palette2 = LoadObjPalette(gCard00Palette, 0x20);
                    FadeSetPaletteExcluded(sMooglePackCards[i].palette2->index + 0x10, 1);
                    sMooglePackCards[i].tiles2 = LoadObjTiles(gCardBacks[gCardDefs[sMooglePackCardIds[i] & 0xFFF].category].tiles, 0x300);
                    sMooglePackCards[i].backSprite = gCardBacks[gCardDefs[sMooglePackCardIds[i] & 0xFFF].category].gfx;
                    sMooglePackCards[i].flipAngle = 0x40;
                    sMooglePackCards[i].state = 6;
                    sMooglePackCards[i].revealed = 1;
                }
            }

            break;
        case 6:
            d = 0x80 - sMooglePackCards[i].flipAngle;
            sMooglePackCards[i].flipAngle += d / sMooglePackCards[i].timer;

            if (--sMooglePackCards[i].timer == 0) {
                sMooglePackCards[i].timer = 5;
                sMooglePackCards[i].state = 7;

                for (k = 0; k < 8; k++) {
                    arg0.x = sMooglePackCards[i].x >> 8;
                    arg0.y = sMooglePackCards[i].y >> 8;
                    arg0.palette = sMooglePackCategoryPalette;
                    arg0.angle = GetRandom() % 96 - 48;
                    arg0.speed = GetRandom() % 256 + 0x1C0;
                    TaskCreate(&sMooglePackHosiTasks[i], &gTaskDescMsShopHosi, &arg0);
                }
            }

            break;
        case 7:
            ApproachValue(&sMooglePackCards[i].y, 0x4600, sMooglePackCards[i].timer);
            f = gFrameCounter & 0x1F;

            if (f == 0) {
                arg0.x = (sMooglePackCards[i].x >> 8) + GetRandom() % 32 - 16;
                arg0.y = (sMooglePackCards[i].y >> 8) + GetRandom() % 32 - 16;
                arg0.palette = sMooglePackCategoryPalette;
                arg0.angle = 0x80;
                arg0.speed = f;
                TaskCreate(&sMooglePackHosiTasks[i], &gTaskDescMsShopHosi, &arg0);
            }

            if (--sMooglePackCards[i].timer == 0) {
                m4aSongNumStart(SONG_SYS_KAIHUKU);
                sMooglePackCards[i].state = 8;

                for (j = 0; j < 5; j++) {
                    if (sMooglePackCards[j].state == 5) {
                        sMooglePackCards[j].timer = 8;
                        break;
                    }
                }

                if (j == 5) {
                    sMooglePackCards[0].timer = 60;
                }
            }

            break;
        case 8:
            if (sMooglePackCards[i].premium != 0) {
                g = gFrameCounter & 0x1F;

                if (g == 0) {
                    arg1.x = (sMooglePackCards[i].x >> 8) + GetRandom() % 32 - 16;
                    arg1.y = (sMooglePackCards[i].y >> 8) + GetRandom() % 32 - 16;
                    arg1.palette = sMooglePackCategoryPalette;
                    arg1.angle = 0x80;
                    arg1.speed = g;
                    TaskCreate(&sMooglePackHosiTasks[i], &gTaskDescMsShopHosi, &arg1);
                }
            }

            if (sMooglePackCards[i].timer != 0) {
                if (--sMooglePackCards[i].timer == 0) {
                    if (a & 1) {
                        SetupBg(3, 0, 31, 0);
                        SetBgScroll(3, 0, 0);
                        RequestDma3Copy(gUnk_09A17D1C, (u8*)GetBgCharBase(3) + 0x5800, 0x1400);
                        LoadBgMap(3, gUnk_09A3AD5C, 0x500);
                    }

                    sMooglePackCardCursor = 0;
                    sMooglePackCursorX = sMooglePackCards[0].x - 0x1000;
                    sMooglePackCursorY = sMooglePackCards[0].y - 0x2000;
                    LoadPalette(gUnk_09A3DA1C + gCardDefs[sMooglePackCardIds[sMooglePackCardCursor] & 0xFFF].category * 16, (void*)(BG_PLTT + 13 * PLTT_SIZE_4BPP), 0x20);
                    sMooglePackNameTextCount = LoadTextSlots(LANGSEL(gCardDefs[sMooglePackCardIds[sMooglePackCardCursor] & 0xFFF].name), sMooglePackNameText);
                    sMooglePackDescTextCount = LoadTextSlots((void*)LANGSTR(gCardKindDescriptions[gCardDefs[sMooglePackCardIds[sMooglePackCardCursor] & 0xFFF].kind]), sMooglePackDescText);
                    LoadObjPaletteBank(sMooglePackCategoryPalette->index, gUnk_09A3DB7C + gCardDefs[sMooglePackCardIds[sMooglePackCardCursor] & 0xFFF].category * 16);
                    EnableBg(3);
                    sMooglePackCards[i].state = 9;
                }
            }

            break;
        case 9:
            if (sMooglePackCards[i].premium != 0) {
                h = gFrameCounter & 0x1F;

                if (h == 0) {
                    arg2.x = (sMooglePackCards[i].x >> 8) + GetRandom() % 32 - 16;
                    arg2.y = (sMooglePackCards[i].y >> 8) + GetRandom() % 32 - 16;
                    arg2.palette = sMooglePackCategoryPalette;
                    arg2.angle = 0x80;
                    arg2.speed = h;
                    TaskCreate(&sMooglePackHosiTasks[i], &gTaskDescMsShopHosi, &arg2);
                }
            }

            keys = MoogleShopReadMenuKeys();
            old = sMooglePackCardCursor;

            if (keys & (A_BUTTON | B_BUTTON)) {
                m4aSongNumStart(SONG_SYS_CLOSE);
                result = 0;
            } else if (keys & DPAD_LEFT) {
                sMooglePackCardCursor--;

                if (sMooglePackCardCursor < 0) {
                    sMooglePackCardCursor = 4;
                }
            } else if (keys & DPAD_RIGHT) {
                sMooglePackCardCursor++;

                if (sMooglePackCardCursor > 4) {
                    sMooglePackCardCursor = 0;
                }
            }

            if (sMooglePackCardCursor != old) {
                LoadPalette(gUnk_09A3DA1C + gCardDefs[sMooglePackCardIds[sMooglePackCardCursor] & 0xFFF].category * 16, (void*)(BG_PLTT + 13 * PLTT_SIZE_4BPP), 0x20);
                sMooglePackNameTextCount = LoadTextSlots(LANGSEL(gCardDefs[sMooglePackCardIds[sMooglePackCardCursor] & 0xFFF].name), sMooglePackNameText);
                sMooglePackDescTextCount = LoadTextSlots((void*)LANGSTR(gCardKindDescriptions[gCardDefs[sMooglePackCardIds[sMooglePackCardCursor] & 0xFFF].kind]), sMooglePackDescText);
                LoadObjPaletteBank(sMooglePackCategoryPalette->index, gUnk_09A3DB7C + gCardDefs[sMooglePackCardIds[sMooglePackCardCursor] & 0xFFF].category * 16);
                m4aSongNumStart(SONG_SYS_CLICK);
            }

            break;
        }
    }

    for (i = 0; i < 5; i++) {
        TaskPoolUpdate(&sMooglePackHosiTasks[i]);
    }

    return result;
}

void DrawMoogleShopCategoryLabels(s16 a) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (sMoogleShopRowCategory[i] >= 0) {
            RequestTilemapRectCopy(gUnk_09A3ABDC, GetBgScreenBase(0), sMoogleShopRowCategory[i] * 6, i == a ? 0 : 3, 0, i * 3 + 3, 6, 3);
        }
    }
}

void LoadMooglePackSelectionTilemap(s16 a) {
    LoadBgMap(1, sMooglePackMenuEntries[a].selectionTilemap, sMooglePackMenuEntries[a].selectionTilemapSize);
}

void MoogleShopHandleSoldOutInput() {
    u16 keys;
    keys = MoogleShopReadMenuKeys();

    if ((keys & A_BUTTON) == 0) {
        if (keys & B_BUTTON) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            FadeStartOut(FADE_MODE_BLACK, 16);
            sMoogleShopBackToTop = 1;
            sMoogleShopState = 5;
        } else if (keys & START_BUTTON) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            FadeStartOut(FADE_MODE_BLACK, 16);
            sMoogleShopBackToTop = 0;
            sMoogleShopState = 5;
        }
    }
}

void MoogleShopHandleRowInput() {
    u16 keys;
    s16 old;
    s16 i;

    old = sMoogleShopRowCursor;
    keys = MoogleShopReadMenuKeys();

    if ((keys & A_BUTTON) == 0) {
        if (keys & B_BUTTON) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            FadeStartOut(FADE_MODE_BLACK, 16);
            sMoogleShopBackToTop = 1;
            sMoogleShopState = 5;
        } else if (keys & START_BUTTON) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            FadeStartOut(FADE_MODE_BLACK, 16);
            sMoogleShopBackToTop = 0;
            sMoogleShopState = 5;
        } else if (keys & DPAD_UP) {
            sMoogleShopRowCursor--;

            if (sMoogleShopRowCursor < 0) {
                i = 3;

                if (sMoogleShopRowCategory[i] < 0) {
                    do {
                        i--;

                        if (i <= 0) {
                            break;
                        }
                    } while (sMoogleShopRowCategory[i] < 0);
                }

                sMoogleShopRowCursor = i;
            }
        } else if (keys & DPAD_DOWN) {
            sMoogleShopRowCursor++;

            if (sMoogleShopRowCursor > 3) {
                sMoogleShopRowCursor = 0;
            } else if (sMoogleShopRowCategory[sMoogleShopRowCursor] < 0) {
                sMoogleShopRowCursor = 0;
            }
        } else if (keys & DPAD_RIGHT) {
            sMoogleShopState = 3;
            sMoogleShopPackCursor = 0;
            LoadMooglePackSelectionTilemap(0);
            m4aSongNumStart(SONG_SYS_CLICK);
        }
    }

    if (sMoogleShopRowCursor == -1) {
        sMoogleShopRowCursor = old;
    }

    if (sMoogleShopRowCursor != old) {
        DrawMoogleShopCategoryLabels(sMoogleShopRowCursor);
        DrawMoogleShopPacks(sMoogleShopRowCursor);
        m4aSongNumStart(SONG_SYS_CLICK);
    }
}

u16 RollMoogleCardValue() {
    s16 i;
    u16 r;
    u16 acc;

    r = GetRandom() % 100;
    i = 0;
    acc = sMoogleCardValueWeights[0];

    if (r >= acc) {
        do {
            i++;

            if (i > 9) {
                break;
            }

            acc += sMoogleCardValueWeights[i];
        } while (r >= acc);
    }

    return i % 10;
}

void RollMooglePackCards(s16 a, s16 b) {
    s16 lo;
    s16 hi;
    s16 j;
    s16 m;
    s16 k;
    s16 cnt;
    u16 total;
    u16 rnd;
    u16 acc;
    u16 id;
    const MooglePackCardDef** list;
    const MooglePackCardDef* e;
    s16 n;

    id = 0;

    if (a <= 2) {
        lo = a;
        hi = a + 1;
    } else {
        lo = 0;
        hi = 3;
    }

    total = 0;
    cnt = 0;

    for (j = lo; j < hi; j++) {
        cnt += sMooglePackCardTables[j].count;
    }

    list = EwramAlloc(cnt * sizeof(*list));
    k = 0;

    for (j = lo; j < hi; j++) {
        e = sMooglePackCardTables[j].cards;
        n = sMooglePackCardTables[j].count;

        for (m = 0; m < n; m++) {
            if (e[m].weights[b] != 0) {
                total += e[m].weights[b];
                list[k] = &e[m];
                k++;
            }
        }
    }

    for (j = 0; j < 5; j++) {
        rnd = GetRandom() % total;
        acc = 0;

        for (m = 0; m < k; m++) {
            acc += list[m]->weights[b];

            if (rnd < acc) {
                if (IsCardKindObtained(list[m]->unlockFlag) != 0) {
                    id = list[m]->cardId;
                } else {
                    switch (gCardDefs[list[m]->cardId].category) {
                    case 0:
                        id = CARD_ID(CARD_KINGDOM_KEY, 0);
                        break;
                    case 1:
                        id = CARD_ID(CARD_CURE, 0);
                        break;
                    case 2:
                        id = CARD_ID(CARD_POTION, 0);
                        break;
                    }
                }

                id += RollMoogleCardValue();

                if (gCardDefs[id].category <= 1) {
                    if (GetRandom() % 100 <= 9) {
                        id |= 0x8000;
                    }
                }

                sMooglePackCardIds[j] = id;

                if (ObtainCard(id) < 0) {
                    AddMooglePoints(GetCardMooglePointValue(id));
                }

                break;
            }
        }
    }

    EwramFree(list);
}

void MoogleShopHandlePackInput() {
    u16 keys;
    s16 old;

    old = sMoogleShopPackCursor;
    keys = MoogleShopReadMenuKeys();

    if (keys & A_BUTTON) {
        if (sMoogleShopPacks[sMoogleShopRowCursor][sMoogleShopPackCursor][0] >= 0 &&
            SpendMooglePoints(sMooglePackPrices[sMoogleShopRowCategory[sMoogleShopRowCursor]][sMoogleShopPacks[sMoogleShopRowCursor][sMoogleShopPackCursor][1]]) != 0) {
            RollMooglePackCards(sMoogleShopRowCategory[sMoogleShopRowCursor], sMoogleShopPacks[sMoogleShopRowCursor][sMoogleShopPackCursor][1]);
            InitMooglePackOpening(sMoogleShopPackCursor % 2 * 96 + 72, sMoogleShopPackCursor / 2 * 64 + 48);
            FadeSetPaletteExcluded(13, 1);
            FadeToAmount(FADE_MODE_BLACK, 16, 8);
            m4aSongNumStart(SONG_SYS_KETTEI);
            sMoogleShopState = 4;
        } else {
            m4aSongNumStart(SONG_SYS_BEEP);
        }
    } else if (keys & B_BUTTON) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        FadeStartOut(FADE_MODE_BLACK, 16);
        sMoogleShopBackToTop = 1;
        sMoogleShopState = 5;
    } else if (keys & START_BUTTON) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        FadeStartOut(FADE_MODE_BLACK, 16);
        sMoogleShopBackToTop = 0;
        sMoogleShopState = 5;
    } else if (keys & DPAD_UP) {
        sMoogleShopPackCursor = sMooglePackMenuEntries[sMoogleShopPackCursor].upEntry;
    } else if (keys & DPAD_DOWN) {
        sMoogleShopPackCursor = sMooglePackMenuEntries[sMoogleShopPackCursor].downEntry;
    } else if (keys & DPAD_LEFT) {
        sMoogleShopPackCursor = sMooglePackMenuEntries[sMoogleShopPackCursor].leftEntry;
    } else if (keys & DPAD_RIGHT) {
        sMoogleShopPackCursor = sMooglePackMenuEntries[sMoogleShopPackCursor].rightEntry;
    }

    if (sMoogleShopPackCursor == -1) {
        sMoogleShopPackCursor = old;
    } else if (sMoogleShopPackCursor == 5) {
        sMoogleShopPackCursor = old;
        sMoogleShopState = 2;
        DisableBg(1);
        m4aSongNumStart(SONG_SYS_CLICK);
    } else if (sMoogleShopPacks[sMoogleShopRowCursor][sMoogleShopPackCursor][0] < 0) {
        sMoogleShopPackCursor = old;
    }

    if (sMoogleShopPackCursor != old) {
        LoadMooglePackSelectionTilemap(sMoogleShopPackCursor);
        m4aSongNumStart(SONG_SYS_CLICK);
    }
}

void MoogleShopDraw() {
    s32 i;
    s16 v;

    switch (sMoogleShopState) {
    case 2:
        if (sMoogleShopHasPacks != 0) {
            ApproachValueHalf(&sMoogleShopCursorX, 0x400);
            ApproachValueHalf(&sMoogleShopCursorY, sMoogleShopRowCursor * 6144 + 0x800);
            DrawSprite(sMoogleShopCursorX >> 8, sMoogleShopCursorY >> 8, AnimUpdate(&sMoogleShopCursorAnim), sMoogleShopCursorTiles, sMoogleShopCursorPalette, NULL, SPRITE_PRIORITY(1), 0x3E8);
        }

        break;
    case 3:
        ApproachValueHalf(&sMoogleShopCursorX, sMooglePackMenuEntries[sMoogleShopPackCursor].cursorX << 8);
        ApproachValueHalf(&sMoogleShopCursorY, sMooglePackMenuEntries[sMoogleShopPackCursor].cursorY << 8);
        DrawSprite(sMoogleShopCursorX >> 8, sMoogleShopCursorY >> 8, AnimUpdate(&sMoogleShopCursorAnim), sMoogleShopCursorTiles, sMoogleShopCursorPalette, NULL, SPRITE_PRIORITY(1), 0x3E8);
        break;
    case 4:
        DrawMooglePackOpening();
        break;
    }

    for (i = 0; i < 4; i++) {
        if (sMoogleShopPacks[sMoogleShopRowCursor][i][0] >= 0) {
            v = sMoogleShopPacks[sMoogleShopRowCursor][i][1];
            DrawSprite(sMooglePackMenuEntries[i].spriteX + sMooglePackSpriteDefs[v].xOffset, sMooglePackMenuEntries[i].spriteY + sMooglePackSpriteDefs[v].yOffset, sMooglePackSprites[v], sMooglePackTiles[v], sMooglePackPalettes[v], NULL, SPRITE_PRIORITY(1), 0x3F2);
        }
    }
}

void mode_ms_shop_0() {
    s16 i;
    s32 size;
    u16** p;

    p = &sMoogleShopTilemap;
    size = 0x500;
    *p = EwramAlloc(size);
    SpriteReset();
    FadeStartIn(FADE_MODE_BLACK, 16);
    SetBgMode0();
    SetupBg(0, 0, 28, 0);
    SetupBg(1, 0, 29, 0);
    SetupBg(2, 0, 30, 0);
    SetupBg(3, 0, 31, 0);
    SetBgPriority(0, 3);
    SetBgPriority(1, 2);
    SetBgPriority(2, 1);
    SetBgPriority(3, 0);
    sMoogleShopState = 0;
    sMoogleShopRowCursor = 0;
    sMoogleShopPackCursor = 0;
    sMoogleShopHasPacks = BuildMooglePackList(gGameState.floor);
    LoadBgPalette(0, gUnk_09A3D87C, 0x1A0);
    LoadBgTiles(0, gUnk_09A1251C, 0x6860);
    LoadDecimalDigitTiles(GetMooglePoints(), gUnk_09A18D7C, (u8*)GetBgCharBase(0) + 0x20, 0x20, 5);
#ifdef VERSION_EU
    LoadBgMap(0, sUnkEu_09F84F5C[gLanguage], size);
#else
    LoadBgMap(0, gUnk_09A382DC, size);
#endif
    DrawMoogleShopCategoryLabels(sMoogleShopRowCursor);

    if (sMoogleShopHasPacks != 0) {
        LoadMooglePackSelectionTilemap(sMoogleShopPackCursor);
    }

    DrawMoogleShopPacks(sMoogleShopRowCursor);
    LoadBgMap(3, gUnk_09A3AD5C, size);
    sMoogleShopCursorPalette = LoadObjPalette(gUnk_09A3DA7C, 0x20);
    sMoogleShopCursorTiles = LoadObjTiles(gUnk_099A3CE4, 0x1C0);
    AnimInit(&sMoogleShopCursorAnim, gUnk_09EF99F8, gUnk_09EF99D8);
    AnimStart(&sMoogleShopCursorAnim, 0, ANIM_FLAG_LOOP);

    for (i = 0; i < 4; i++) {
        sMooglePackPalettes[i] = LoadObjPalette(sMooglePackSpriteDefs[i].palette, sMooglePackSpriteDefs[i].paletteSize);
        sMooglePackTiles[i] = LoadObjTiles(sMooglePackSpriteDefs[i].tiles, sMooglePackSpriteDefs[i].tilesSize);
        sMooglePackSprites[i] = sMooglePackSpriteDefs[i].sprite;
    }

    EnableBg(0);
    DisableBg(1);
    EnableBg(2);
    DisableBg(3);
}

void mode_ms_shop_1() {
    UpdatePlayTime();

    switch (sMoogleShopState) {
    case 0:
        if (FadeIsActive() == 0) {
            if (sMoogleShopHasPacks != 0) {
                sMoogleShopCursorX = 0x400;
                sMoogleShopCursorY = sMoogleShopRowCursor * 6144 + 0x800;
                sMoogleShopState = 2;
            } else {
                sMoogleShopState = 1;
            }
        }

        break;
    case 1:
        MoogleShopHandleSoldOutInput();
        break;
    case 2:
        MoogleShopHandleRowInput();
        break;
    case 3:
        MoogleShopHandlePackInput();
        break;
    case 4:
        if (UpdateMooglePackOpening(0) == 0) {
            ReleaseMooglePackOpening();
            SetMooglePackBought(gMapFloorState.room, sMoogleShopRowCategory[sMoogleShopRowCursor], sMoogleShopPacks[sMoogleShopRowCursor][sMoogleShopPackCursor][0]);
            sMoogleShopHasPacks = BuildMooglePackList(gGameState.floor);
#ifdef VERSION_EU
            LoadBgMap(0, sUnkEu_09F84F5C[gLanguage], 0x500);
#else
            LoadBgMap(0, gUnk_09A382DC, 0x500);
#endif

            if (sMoogleShopRowCursor > 0) {
                if (sMoogleShopRowCategory[sMoogleShopRowCursor] < 0) {
                    do {
                        sMoogleShopRowCursor--;

                        if (sMoogleShopRowCursor <= 0) {
                            break;
                        }
                    } while (sMoogleShopRowCategory[sMoogleShopRowCursor] < 0);
                }
            }

            DrawMoogleShopCategoryLabels(sMoogleShopRowCursor);
            DrawMoogleShopPacks(sMoogleShopRowCursor);

            if (sMoogleShopHasPacks != 0) {
                for (; sMoogleShopPackCursor > 0 && sMoogleShopPacks[sMoogleShopRowCursor][sMoogleShopPackCursor][0] < 0; sMoogleShopPackCursor--) {
                }

                LoadMooglePackSelectionTilemap(sMoogleShopPackCursor);
            } else {
                DisableBg(1);
            }

            LoadDecimalDigitTiles(GetMooglePoints(), gUnk_09A18D7C, (u8*)GetBgCharBase(0) + 0x20, 0x20, 5);
            DisableBg(3);
            FadeToOriginal(FADE_MODE_BLACK, 8);
            sMoogleShopState = sMoogleShopHasPacks != 0 ? 3 : 1;
        }

        break;
    case 5:
        if (FadeIsActive() == 0) {
            if (sMoogleShopBackToTop != 0) {
                ModeRequest(&gModeMsTop, 2);
            } else {
                RequestMapMode();
            }
        }

        break;
    }

    MoogleShopDraw();
}

void mode_ms_shop_2() {
    s32 i;

    ReleaseObjPalette(sMoogleShopCursorPalette);
    ReleaseObjTiles(sMoogleShopCursorTiles);

    for (i = 0; i < 4; i++) {
        ReleaseObjPalette(sMooglePackPalettes[i]);
        ReleaseObjTiles(sMooglePackTiles[i]);
    }

    EwramFree(sMoogleShopTilemap);
}

Mode gModeMsShop = {
    "mode_ms_shop",
    (ModeInitFunc)mode_ms_shop_0,
    mode_ms_shop_1,
    mode_ms_shop_2,
};
