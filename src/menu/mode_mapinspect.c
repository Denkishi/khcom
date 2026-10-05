/**
 * mode_mapinspect.c
 * Map Card List Screen
 */

#include "system_state.h"
#include "map_api.h"
#include "text.h"
#include "monsgage.h"
#include "mode_mapinspect.h"
#include "gba/keys.h"
#include "sprites_card.h"
#include "sprites_worldinspect.h"
#include "sprites_map.h"
#include "sprites_card_pictures.h"
#include "malloc.h"
#include "fade.h"
#include "mode_ms_top_api.h"
#include "songs.h"
#include "ms_types.h"
#include "jiminy_data.h"
#include "common_text.h"
#include "anim.h"
#include "card.h"
#include "card_api.h"
#include "card_description_data.h"
#include "card_ui_types.h"
#include "display.h"
#include "engine_math.h"
#include "game_state.h"
#include "gba/defines.h"
#include "key.h"
#include "m4a_song.h"
#include "mode.h"
#include "obj.h"
#include "obj_api.h"
#include "text_types.h"
#include "types.h"
#include "gba/macro.h"
#include <stddef.h>
#include "card_worldselect.h"
#include "registration_data.h"
#include "sprite_palettes.h"

#ifdef VERSION_EU
static void* sMapInspectScrollMarkerSpritesByLanguage[5] = {
    gMapInspectBarFrame4,
    gMapInspectBarFrFrame4,
    gMapInspectBarDeFrame4,
    gMapInspectBarItFrame4,
    gMapInspectBarEsFrame4,
};

static void* sMapInspectTitleSpritesByLanguage[5] = {
    gMapInspectBarFrame5,
    gMapInspectBarFrFrame5,
    gMapInspectBarDeFrame5,
    gMapInspectBarItFrame5,
    gMapInspectBarEsFrame5,
};

static void* sMapInspectTopBarSpritesByLanguage[5] = {
    gMapInspectBarFrame6,
    gMapInspectBarFrFrame6,
    gMapInspectBarDeFrame6,
    gMapInspectBarItFrame6,
    gMapInspectBarEsFrame6,
};

static void* sMapInspectBottomBarSpritesByLanguage[5] = {
    gMapInspectBarFrame7,
    gMapInspectBarFrFrame7,
    gMapInspectBarDeFrame7,
    gMapInspectBarItFrame7,
    gMapInspectBarEsFrame7,
};

static void* sMapInspectBarTilesByLanguage[5] = {
    gMapInspectBarTiles,
    gMapInspectBarFrTiles,
    gMapInspectBarDeTiles,
    gMapInspectBarItTiles,
    gMapInspectBarEsTiles,
};

static AnimHeader** sMapInspectCursorAnimsByLanguage[5] = {
    gMapInspectBarAnims,
    gMapInspectBarFrAnims,
    gMapInspectBarDeAnims,
    gMapInspectBarItAnims,
    gMapInspectBarEsAnims,
};

static void** sMapInspectCursorFramesByLanguage[5] = {
    gMapInspectBarFrames,
    gMapInspectBarFrFrames,
    gMapInspectBarDeFrames,
    gMapInspectBarItFrames,
    gMapInspectBarEsFrames,
};
#endif

static MapCardCategoryDef sMapCardCategoryDefs[5] = {
    {4, 1, 1, 0},
    {0, 2, 2, 0},
    {1, 3, 3, 0},
    {2, 65535, 4, 0},
    {65535, 0, 0, 0},
};

#ifdef VERSION_EU
static const u16 sMapInspectBarTileSizesByLanguage[5] = {2752, 2816, 2816, 2816, 2816};
#endif
static const u16 sMapCardCategoryTypes[4] = {2, 1, 3, 4};

static MapCardInventoryEntry* sMapCardInventoryEntries;
static s16 sMapInspectMenuState;
static s16 sMapInspectTab;
static u16 sMapInspectCategoryStart[4];
static u16 sMapInspectCategoryEntryCount[4];
static s16 sMapInspectCategoryCardCount[4];
static s16 sMapInspectCardTotal;
static struct ObjPalette* sMapInspectBarPalette;
static struct ObjTiles* sMapInspectBarTiles;
static AnimState sMapInspectCursorAnim;
static struct ObjPalette* sMapInspectBarPalette2;
static struct ObjPalette* sMapInspectCategoryPalette;
static struct ObjTiles* sMapInspectHighlightTiles;
static AnimState sMapInspectHighlightAnim;
static s16 sMapInspectGridCol;
static s16 sMapInspectGridRow;
static s16 sMapInspectGridScroll;
static void* sMapInspectGridPalettes[4][3];
static void* sMapInspectGridTiles[4][3];
static void* sMapInspectGridSprites[4][3];
static u8 sMapInspectGridPremium[4][3];
static struct ObjPalette* sMapInspectCardPalette;
static struct ObjTiles* sMapInspectCardTiles;
static void* sMapInspectCardSprite;
static struct ObjPalette* sMapInspectCardBackPalette;
static struct ObjTiles* sMapInspectCardBackTiles;
static void* sMapInspectCardBackSprite;
static struct ObjTiles* sMapInspectPremiumTiles;
static AnimState sMapInspectPremiumAnim;
static struct ObjTiles* sMapInspectGridPremiumTiles;
static AnimState sMapInspectGridPremiumAnim;
static u8 sMapInspectCardPremium;
static TextSlot* sMapInspectNameText;
static u8 sMapInspectNameTextCount;
static TextSlot* sMapInspectDescText;
static u8 sMapInspectDescTextCount;
static TextSlot* sMapInspectConfirmText;
static u8 sMapInspectConfirmTextCount;
static u16 sMapInspectConfirmTextLength;
static TextSlot* sMapInspectYesText;
static u8 sMapInspectYesTextCount;
static u16 sMapInspectYesTextLength;
static TextSlot* sMapInspectNoText;
static u8 sMapInspectNoTextCount;
static u16 sMapInspectNoTextLength;
#ifdef VERSION_JP
static TextSlot* sMapInspectNoticeText[2];
static u8 sMapInspectNoticeTextCount[2];
static u16 sMapInspectNoticeTextLength[2];
#else
static TextSlot* sMapInspectNoticeText[1];
static u8 sMapInspectNoticeTextCount[1];
static u16 sMapInspectNoticeTextLength[1];
#endif

static s16 sMapInspectValueCol;
static s16 sMapInspectValueRow;
static s16 sMapInspectConfirmCursor;
static s16 sMapInspectState;
static s16 sMapInspectSteps;
static s32 sMapInspectBarY[2];
static s32 sMapInspectBarX;
static s32 sMapInspectCursorX;
static s32 sMapInspectCursorY;
static u8 sMapInspectReturnToMenu;

s16 GetMapInspectTabStart(s16 a) {
    s16 r;

    if (a <= 3) {
        r = sMapInspectCategoryStart[a];
    } else {
        r = 0;
    }

    return r;
}

s16 GetMapInspectSelectedIndex() {
    return GetMapInspectTabStart(sMapInspectTab) + (sMapInspectGridScroll + sMapInspectGridRow) * 3 + sMapInspectGridCol;
}

MapCardInventoryEntry* GetMapInspectSelectedEntry() {
    return &sMapCardInventoryEntries[GetMapInspectSelectedIndex()];
}

void MapInspectSelectFirstValue() {
    MapCardInventoryEntry* p;
    s16 i;

    p = GetMapInspectSelectedEntry();

    if (p->cardType <= 26) {
        for (i = 0; i < 10; i++) {
            if (p->countsByValue[i] > 0) {
                break;
            }
        }

        sMapInspectValueCol = i / 5;
        sMapInspectValueRow = i % 5;
    } else {
        sMapInspectValueCol = 0;
        sMapInspectValueRow = 0;
    }
}

s16 GetMapInspectTabCount(s16 a) {
    s16 r;
    s16 i;
    s32 t;

    if (a <= 3) {
        r = sMapInspectCategoryEntryCount[a];
    } else {
        r = 0;

        for (i = 0; i <= 3; i++) {
            t = sMapInspectCategoryEntryCount[i];
            r += t;
        }
    }

    return r;
}

u8 MapInspectCanDelete() {
    if (sMapInspectCardTotal > 20) {
        return 1;
    }

    return 0;
}

void MapInspectLoadGrid() {
    s16 a;
    s16 k;
    s16 i;
    s16 j;
    s16 b;
    u16 idx;

    a = GetMapInspectTabStart(sMapInspectTab);
    b = GetMapInspectTabCount(sMapInspectTab);
    k = sMapInspectGridScroll * 3;

    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 2; j++) {
            if (sMapInspectGridPalettes[i][j] != NULL) {
                ReleaseObjPalette(sMapInspectGridPalettes[i][j]);
            }

            if (sMapInspectGridTiles[i][j] != NULL) {
                ReleaseObjTiles(sMapInspectGridTiles[i][j]);
            }

            if (k < b) {
                idx = sMapCardInventoryEntries[a + k].cardIndex;
                sMapInspectGridPalettes[i][j] = LoadObjPalette(gMapCardDefs[idx].palette2, 32);
                sMapInspectGridTiles[i][j] = LoadObjTiles(gMapCardDefs[idx].tiles2, gMapCardDefs[idx].tilesSize2);
                sMapInspectGridSprites[i][j] = *gMapCardDefs[idx].sprites2;
                sMapInspectGridPremium[i][j] = sMapCardInventoryEntries[a + k].category == 3;
            } else {
                sMapInspectGridPalettes[i][j] = NULL;
                sMapInspectGridTiles[i][j] = NULL;
                sMapInspectGridSprites[i][j] = NULL;
                sMapInspectGridPremium[i][j] = 0;
            }

            k++;
        }
    }
}

void MapInspectLoadSelectedCard() {
    MapCardInventoryEntry* p;
    u16 idx;
    u16 k;
    u8* q;

    p = GetMapInspectSelectedEntry();

    if (sMapInspectCardPalette != NULL) {
        ReleaseObjPalette(sMapInspectCardPalette);
    }

    if (sMapInspectCardTiles != NULL) {
        ReleaseObjTiles(sMapInspectCardTiles);
    }

    if (sMapInspectCardBackPalette != NULL) {
        ReleaseObjPalette(sMapInspectCardBackPalette);
    }

    if (sMapInspectCardBackTiles != NULL) {
        ReleaseObjTiles(sMapInspectCardBackTiles);
    }

    if (sMapInspectCategoryPalette != NULL) {
        ReleaseObjPalette(sMapInspectCategoryPalette);
    }

    if (p->cardType <= 26 && GetMapInspectTabCount(sMapInspectTab) > 0) {
        idx = p->cardIndex;
        k = sMapCardCategoryTypes[p->category];
        sMapInspectCardPalette = LoadObjPalette(gMapCardDefs[idx].palette, gMapCardDefs[idx].paletteSize);
        sMapInspectCardTiles = LoadObjTiles(gMapCardDefs[idx].tiles, gMapCardDefs[idx].tilesSize);
        sMapInspectCardSprite = *gMapCardDefs[idx].sprites;
        sMapInspectCardBackPalette = LoadObjPalette(gMapCardBackDefs[k].palette, gMapCardBackDefs[k].paletteSize);
        sMapInspectCardBackTiles = LoadObjTiles(gMapCardBackDefs[k].tiles, gMapCardBackDefs[k].tilesSize);
        sMapInspectCardBackSprite = *gMapCardBackDefs[k].sprites;
        sMapInspectCardPremium = p->category == 3;
        sMapInspectCategoryPalette = LoadObjPalette(gMapInspectCategoryPalettes + p->category * 16, 32);
        q = &sMapInspectNameTextCount;
        *q = LoadTextSlots(GetRoomName(p->cardType), sMapInspectNameText);

#ifdef VERSION_EU
        {
            const u8** strings = gMapCardDescriptions[p->cardType]->strings;
            q = &sMapInspectDescTextCount;
            *q = LoadTextSlots((void*)strings[gLanguage], sMapInspectDescText);
        }
#else
        q = &sMapInspectDescTextCount;
        *q = LoadTextSlots((void*)gMapCardDescriptions[p->cardType], sMapInspectDescText);
#endif
    } else {
        sMapInspectCardPalette = NULL;
        sMapInspectCardTiles = NULL;
        sMapInspectCardSprite = NULL;
        sMapInspectCardBackPalette = NULL;
        sMapInspectCardBackTiles = NULL;
        sMapInspectCardBackSprite = NULL;
        sMapInspectCardPremium = 0;
        sMapInspectCategoryPalette = NULL;
        sMapInspectNameTextCount = 0;
        sMapInspectDescTextCount = 0;
    }
}

s16 GetMapInspectValueIndex(s16 a, s16 b) {
    return b + a * 5;
}

s16 GetMapInspectSelectedValue() {
    return GetMapInspectValueIndex(sMapInspectValueCol, sMapInspectValueRow);
}

void MapInspectDrawCardTotal() {
    LoadDecimalDigitTiles(sMapInspectCardTotal, gMapInspectTotalDigitTiles, (u8*)GetBgCharBase(0) + 0x3A0, 32, 2);
    LoadDecimalDigitTiles(99, gMapInspectTotalDigitTiles, (u8*)GetBgCharBase(0) + 0x3E0, 32, 2);
}

void MapInspectDrawCategoryCounts() {
    s16 i;
    s16 v;

    for (i = 0; i <= 3; i++) {
        v = sMapInspectCategoryCardCount[i];

        if (v != 0) {
            LoadDecimalDigitTiles(v, gMapInspectCategoryDigitTiles, (u8*)GetBgCharBase(0) + (i * 64 + 0x2A0), 32, 2);
        } else {
            LoadDecimalDigitTiles(0, gMapInspectCategoryZeroTiles, (u8*)GetBgCharBase(0) + (i * 64 + 0x2A0), 32, 2);
        }
    }
}

void MapInspectDrawValueCounts() {
    MapCardInventoryEntry* p;
    s16 i;
    s32 v;

    p = GetMapInspectSelectedEntry();

    if (GetMapInspectTabCount(sMapInspectTab) > 0) {
        LoadPalette(gMapInspectCategoryBgPalettes + p->category * 16, (void*)PLTT, 12);
    }

    if (sMapInspectMenuState == 1) {
        for (i = 0; i <= 9; i++) {
            LoadDecimalDigitTiles(0, gMapInspectValueZeroTiles, (u8*)GetBgCharBase(0) + (i * 64 + 0x40), 32, 1);
            LoadPalette(gMapInspectValueZeroPalette, (void*)(PLTT + (i + 6) * 2), 2);
        }
    } else if (p->category == 3) {
        if (GetMapInspectTabCount(sMapInspectTab) > 0) {
            LoadBgMap(1, gMapInspectPremiumValuesMap, 0x500);
        }

        for (i = 0; i <= 9; i++) {
            v = p->countsByValue[i];

            if (v != 0 && GetMapInspectTabCount(sMapInspectTab) > 0) {
                LoadDecimalDigitTiles(v, gMapInspectValueDigitTiles, (u8*)GetBgCharBase(0) + 0x40, 32, 1);
                LoadPalette(gMapInspectValueDigitPalette, (void*)(BG_PLTT + 0xC), 2);
                break;
            }
        }

        if (i > 9) {
            LoadDecimalDigitTiles(0, gMapInspectValueZeroTiles, (u8*)GetBgCharBase(0) + 0x40, 32, 1);
            LoadPalette(gMapInspectValueZeroPalette, (void*)(BG_PLTT + 0xC), 2);
        }
    } else {
        if (GetMapInspectTabCount(sMapInspectTab) > 0) {
            LoadBgMap(1, gMapInspectValuesMap, 0x500);
        }

        for (i = 0; i <= 9; i++) {
            v = p->countsByValue[i];

            if (v != 0 && GetMapInspectTabCount(sMapInspectTab) > 0) {
                LoadDecimalDigitTiles(v, gMapInspectValueDigitTiles, (u8*)GetBgCharBase(0) + (i * 64 + 0x40), 32, 1);
                LoadPalette(gMapInspectValueDigitPalette, (void*)(PLTT + (i + 6) * 2), 2);
            } else {
                LoadDecimalDigitTiles(0, gMapInspectValueZeroTiles, (u8*)GetBgCharBase(0) + (i * 64 + 0x40), 32, 1);
                LoadPalette(gMapInspectValueZeroPalette, (void*)(PLTT + (i + 6) * 2), 2);
            }
        }
    }
}

void MapInspectDrawTab(s16 a) {
    RequestTilemapRectCopy(gMapInspectTabsMap, GetBgScreenBase(0), 0, sMapCardCategoryDefs[a].displayIndex * 2, 0, 2, 11, 2);
}

void MapInspectDeleteCard() {
    MapCardInventoryEntry* p;
    u16 card;

    p = GetMapInspectSelectedEntry();

    if (p->countsByValue[GetMapInspectSelectedValue()] > 0) {
        card = GetMapInspectSelectedValue() + p->cardIndex;
        sMapInspectCategoryCardCount[p->category]--;
        sMapInspectCardTotal--;
        p->countsByValue[GetMapInspectSelectedValue()]--;
        RemoveMapCard(card);
        MapInspectDrawCardTotal();
        MapInspectDrawValueCounts();
        MapInspectDrawCategoryCounts();
    }
}

u8 MapCardEntryIsEmpty(MapCardInventoryEntry* p) {
    s16 i;

    for (i = 0; i < 10; i++) {
        if (p->countsByValue[i] > 0) {
            break;
        }
    }

    if (i > 9) {
        return 1;
    }

    return 0;
}

u8 MapCardEntrySelectedValueIsEmpty(MapCardInventoryEntry* p) {
    if (p->countsByValue[GetMapInspectSelectedValue()] == 0) {
        return 1;
    }

    return 0;
}

void MapInspectSelectNextValue(MapCardInventoryEntry* p) {
    s16 k;
    s16 i;

    k = GetMapInspectSelectedValue();

    for (i = 0; i <= 9; i++) {
        if (p->countsByValue[k] > 0) {
            break;
        }

        k++;

        if (k > 9) {
            k = 0;
        }
    }

    sMapInspectValueCol = k / 5;
    sMapInspectValueRow = k % 5;
}

void MapInspectRemoveEntry(MapCardInventoryEntry* p) {
    u16 row;
    s16 j;

    row = p->category;
    DmaCopy16(3, p + 1, p, (26 - GetMapInspectSelectedIndex()) * 28);
    DmaFill16(3, 0, &sMapCardInventoryEntries[26], 0x1C);
    sMapCardInventoryEntries[26].cardType = 27;

    for (j = row + 1; j <= 3; j++) {
        sMapInspectCategoryStart[j]--;
    }

    sMapInspectCategoryEntryCount[row]--;

    if (GetMapInspectSelectedIndex() >= GetMapInspectTabCount(sMapInspectTab)) {
        if (--sMapInspectGridCol < 0) {
            sMapInspectGridCol = 2;

            if (--sMapInspectGridRow < 0) {
                sMapInspectGridRow = 0;

                if (--sMapInspectGridScroll < 0) {
                    sMapInspectGridCol = 0;
                    sMapInspectGridScroll = 0;
                }
            }
        }
    }

    sMapInspectValueCol = 0;
    sMapInspectValueRow = 0;
    MapInspectLoadGrid();
    MapInspectLoadSelectedCard();
    MapInspectDrawValueCounts();
}

void MapInspectBuildInventory() {
    s16* pd;
    s32 w;
    s16 k;
    s16 j;
    s16 i;
    s16 a;
    u16 u;
    u16 n;
    u16 t;

    DmaFill16(3, 0, sMapCardInventoryEntries, 0x2F4);

    for (i = 0; i <= 26; i++) {
        sMapCardInventoryEntries[i].cardType = 27;
    }

    a = 0;
    sMapInspectCardTotal = 0;

    for (j = 0; j <= 3; j++) {
        sMapInspectCategoryStart[j] = a;
        sMapInspectCategoryCardCount[j] = 0;

        for (k = 0; k <= 26; k++) {
            t = gMapCardDefs[k * 10].color;

            if (t == sMapCardCategoryTypes[j]) {
                u = gMapCardDefs[k * 10].kind;

                for (i = 0; i <= 9; i++) {
                    n = gMapCardCounts[(u16)(k * 10 + i)];

                    if (n != 0) {
                        if (t != 4) {
                            sMapInspectCardTotal += n;
                        }

                        {
                            s16* counts = sMapInspectCategoryCardCount;
                            s32 index = a;

                            counts[j] += n;
                            sMapCardInventoryEntries[index].cardType = u;
                            sMapCardInventoryEntries[index].cardIndex = k * 10;
                            sMapCardInventoryEntries[index].category = j;
                            sMapCardInventoryEntries[index].countsByValue[i] = n;
                        }
                    }
                }
            }

            if (sMapCardInventoryEntries[a].cardType <= 26) {
                a++;
            }
        }

        pd = &sMapInspectCategoryEntryCount[j];
        w = sMapInspectCategoryStart[j];
        *pd = a - w;
    }
}

u16 MapInspectReadMenuKeys() {
    u16 keys;

    keys = GetKeysPressed() & (A_BUTTON | B_BUTTON | SELECT_BUTTON | START_BUTTON);
    keys |= GetKeysRepeat() & (DPAD_ANY | L_BUTTON | R_BUTTON);
    return keys;
}

void MapInspectHandleGridInput() {
    s16 a;
    s16 b;
    s16 c;
    u16 keys;

    a = sMapInspectGridCol;
    b = sMapInspectGridRow;
    c = sMapInspectGridScroll;
    keys = MapInspectReadMenuKeys();

    if (keys & A_BUTTON) {
        if (GetMapInspectSelectedEntry()->category != 3) {
            MapInspectSelectFirstValue();
            m4aSongNumStart(SONG_SYS_KETTEI);
            AnimStart(&sMapInspectHighlightAnim, 1, ANIM_FLAG_LOOP);
            sMapInspectMenuState = 2;
        } else {
            m4aSongNumStart(SONG_SYS_BEEP);
        }
    } else if (keys & B_BUTTON) {
        LoadBgMap(0, gMapInspectBgMap, 0x500);
        m4aSongNumStart(SONG_SYS_CLOSE);
        sMapInspectReturnToMenu = 1;
        sMapInspectSteps = 16;
        sMapInspectState = 3;
    } else if (keys & START_BUTTON) {
        LoadBgMap(0, gMapInspectBgMap, 0x500);
        m4aSongNumStart(SONG_SYS_CLOSE);
        sMapInspectReturnToMenu = 0;
        FadeStartOut(FADE_MODE_BLACK, 16);
        sMapInspectState = 5;
    } else if (keys & SELECT_BUTTON) {
        sMapInspectGridCol = 0;
        sMapInspectGridRow = 0;
        sMapInspectGridScroll = 0;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
        sMapInspectMenuState = 1;
        MapInspectDrawValueCounts();
    } else if (keys & DPAD_UP) {
        if (sMapInspectGridRow > 0) {
            sMapInspectGridRow--;
        } else if (sMapInspectGridScroll > 0) {
            sMapInspectGridScroll--;
        } else {
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            sMapInspectMenuState = 1;
            MapInspectDrawValueCounts();
        }
    } else if (keys & DPAD_DOWN) {
        if ((sMapInspectGridScroll + sMapInspectGridRow + 1) * 3 + sMapInspectGridCol < GetMapInspectTabCount(sMapInspectTab)) {
            if (sMapInspectGridRow > 2) {
                sMapInspectGridScroll++;
            } else {
                sMapInspectGridRow++;
            }
        } else if (sMapInspectGridRow == 3) {
            if ((sMapInspectGridScroll + sMapInspectGridRow + 1) * 3 < GetMapInspectTabCount(sMapInspectTab)) {
                sMapInspectGridCol = (GetMapInspectTabCount(sMapInspectTab) - 1) % 3;
                sMapInspectGridScroll++;
            }
        }
    } else if (keys & DPAD_LEFT) {
        if (sMapInspectGridCol > 0) {
            sMapInspectGridCol--;
        }
    } else if (keys & DPAD_RIGHT) {
        if ((sMapInspectGridScroll + sMapInspectGridRow) * 3 + sMapInspectGridCol + 1 < GetMapInspectTabCount(sMapInspectTab)) {
            if (sMapInspectGridCol <= 1) {
                sMapInspectGridCol++;
            }
        }
    }

    if (sMapInspectGridCol != a || sMapInspectGridRow != b || sMapInspectGridScroll != c) {
        MapInspectSelectFirstValue();
        MapInspectDrawValueCounts();
        MapInspectLoadSelectedCard();
        m4aSongNumStart(SONG_SYS_CLICKI04B);

        if (sMapInspectGridScroll != c) {
            MapInspectLoadGrid();
        }
    }
}

void MapInspectHandleTabInput() {
    s16 old;
    u16 keys;

    old = sMapInspectTab;
    keys = MapInspectReadMenuKeys();

    if ((keys & A_BUTTON) == 0) {
        if (keys & START_BUTTON) {
            LoadBgMap(0, gMapInspectBgMap, 0x500);
            m4aSongNumStart(SONG_SYS_CLOSE);
            sMapInspectReturnToMenu = 0;
            FadeStartOut(FADE_MODE_BLACK, 16);
            sMapInspectState = 5;
        } else if (keys & (B_BUTTON | DPAD_DOWN)) {
            if (GetMapInspectTabCount(sMapInspectTab) > 0) {
                sMapInspectGridCol = 0;
                sMapInspectGridRow = 0;
                sMapInspectGridScroll = 0;
                MapInspectSelectFirstValue();
                MapInspectDrawValueCounts();
                MapInspectLoadSelectedCard();
                AnimStart(&sMapInspectHighlightAnim, 0, ANIM_FLAG_LOOP);
                m4aSongNumStart(SONG_SYS_CLICKI04B);
                sMapInspectMenuState = 0;
                MapInspectDrawValueCounts();
            } else if (keys & B_BUTTON) {
                LoadBgMap(0, gMapInspectBgMap, 0x500);
                m4aSongNumStart(SONG_SYS_CLOSE);
                sMapInspectReturnToMenu = 1;
                sMapInspectSteps = 16;
                sMapInspectState = 3;
            } else if (keys & DPAD_DOWN) {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        } else if (keys & DPAD_LEFT) {
            sMapInspectTab = sMapCardCategoryDefs[sMapInspectTab].leftCategory;
        } else if (keys & DPAD_RIGHT) {
            sMapInspectTab = sMapCardCategoryDefs[sMapInspectTab].rightCategory;
        }
    }

    if (sMapInspectTab < 0) {
        sMapInspectTab = old;
    }

    if (sMapInspectTab != old) {
        MapInspectDrawTab(sMapInspectTab);
        MapInspectLoadGrid();
        m4aSongNumStart(SONG_SYS_CLICK);
    }
}

void MapInspectSelectValueInColumn(MapCardInventoryEntry* p, u16 row) {
    s16 c;
    s16 i;
    s32 k;

    c = sMapInspectValueRow;

    for (i = 0; i <= 4; i++) {
        k = c - i;

        if (k >= 0 && p->countsByValue[GetMapInspectValueIndex(row, k)] > 0) {
            sMapInspectValueCol = row;
            sMapInspectValueRow = k;
            return;
        }

        k = c + i;

        if (k <= 4 && p->countsByValue[GetMapInspectValueIndex(row, k)] > 0) {
            sMapInspectValueCol = row;
            sMapInspectValueRow = k;
            return;
        }
    }
}

void MapInspectHandleValueInput() {
    MapCardInventoryEntry* p;
    s16 a;
    s16 b;
    s16 i;
    u16 keys;
    u16 trg;

    p = GetMapInspectSelectedEntry();
    a = sMapInspectValueCol;
    b = sMapInspectValueRow;
    trg = MapInspectReadMenuKeys();
    keys = trg;

    if (keys & A_BUTTON) {
        if (MapInspectCanDelete()) {
            sMapInspectConfirmCursor = 1;
            sMapInspectCursorX = 0x7400;
            sMapInspectCursorY = 0x5000;
            AnimStart(&sMapInspectCursorAnim, 4, ANIM_FLAG_LOOP);
            EnableBg(2);
            m4aSongNumStart(SONG_SYS_CANSEL);
            sMapInspectMenuState = 3;
        } else {
            EnableBg(2);
            m4aSongNumStart(SONG_SYS_BEEP);
            sMapInspectMenuState = 4;
        }
    } else {
        if (keys & B_BUTTON) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            AnimStart(&sMapInspectHighlightAnim, 0, ANIM_FLAG_LOOP);
            sMapInspectMenuState = 0;
        } else if (keys & START_BUTTON) {
            LoadBgMap(0, gMapInspectBgMap, 0x500);
            m4aSongNumStart(SONG_SYS_CLOSE);
            sMapInspectReturnToMenu = 0;
            FadeStartOut(FADE_MODE_BLACK, 16);
            sMapInspectState = 5;
        } else if (keys & DPAD_LEFT) {
            MapInspectSelectValueInColumn(p, 0);
        } else if (keys & DPAD_RIGHT) {
            MapInspectSelectValueInColumn(p, 1);
        } else if (keys & DPAD_UP) {
            for (i = 0; i <= 4; i++) {
                if (--sMapInspectValueRow < 0) {
                    sMapInspectValueRow = 4;
                }

                if (p->countsByValue[GetMapInspectSelectedValue()] > 0) {
                    break;
                }
            }
        } else if (keys & DPAD_DOWN) {
            for (i = 0; i <= 4; i++) {
                if (++sMapInspectValueRow > 4) {
                    sMapInspectValueRow = 0;
                }

                if (p->countsByValue[GetMapInspectSelectedValue()] > 0) {
                    break;
                }
            }
        }
    }

    if (sMapInspectValueCol != a || sMapInspectValueRow != b) {
        m4aSongNumStart(SONG_SYS_CLICK);
    }
}

void MapInspectHandleConfirmInput() {
    MapCardInventoryEntry* p;
    s16 old;
    u16 keys;

    p = GetMapInspectSelectedEntry();
    old = sMapInspectConfirmCursor;
    keys = MapInspectReadMenuKeys();

    if (keys & A_BUTTON) {
        sMapInspectCursorX = sMapInspectValueCol * 12288 + 0x9200;
        sMapInspectCursorY = sMapInspectValueRow * 2048 + 0x1000;
        AnimStart(&sMapInspectCursorAnim, 0, ANIM_FLAG_LOOP);
        DisableBg(2);

        if (sMapInspectConfirmCursor == 0) {
            MapInspectDeleteCard();
            m4aSongNumStart(SONG_SYS_CARD_DELETE);

            if (MapCardEntryIsEmpty(p)) {
                MapInspectRemoveEntry(p);

                if (GetMapInspectTabCount(sMapInspectTab) > 0) {
                    AnimStart(&sMapInspectHighlightAnim, 0, ANIM_FLAG_LOOP);
                    sMapInspectMenuState = 0;
                } else {
                    sMapInspectMenuState = 1;
                }
            } else {
                if (MapCardEntrySelectedValueIsEmpty(p)) {
                    MapInspectSelectNextValue(p);
                }

                AnimStart(&sMapInspectHighlightAnim, 1, ANIM_FLAG_LOOP);
                sMapInspectMenuState = 2;
            }
        } else {
            m4aSongNumStart(SONG_SYS_CLOSE);
            AnimStart(&sMapInspectHighlightAnim, 1, ANIM_FLAG_LOOP);
            sMapInspectMenuState = 2;
        }
    } else if (keys & B_BUTTON) {
        sMapInspectCursorX = sMapInspectValueCol * 12288 + 0x9200;
        sMapInspectCursorY = sMapInspectValueRow * 2048 + 0x1000;
        AnimStart(&sMapInspectCursorAnim, 0, ANIM_FLAG_LOOP);
        DisableBg(2);
        m4aSongNumStart(SONG_SYS_CLOSE);
        AnimStart(&sMapInspectHighlightAnim, 1, ANIM_FLAG_LOOP);
        sMapInspectMenuState = 2;
    } else if (keys & START_BUTTON) {
        LoadBgMap(0, gMapInspectBgMap, 0x500);
        m4aSongNumStart(SONG_SYS_CLOSE);
        sMapInspectReturnToMenu = 0;
        FadeStartOut(FADE_MODE_BLACK, 16);
        sMapInspectState = 5;
    } else if (keys & DPAD_LEFT) {
        sMapInspectConfirmCursor = 0;
    } else if (keys & DPAD_RIGHT) {
        sMapInspectConfirmCursor = 1;
    }

    if (sMapInspectConfirmCursor != old) {
        m4aSongNumStart(SONG_SYS_CLICK);
    }
}

void MapInspectHandleNoticeInput() {
    u16 keys;

    keys = MapInspectReadMenuKeys();

    if (keys & (A_BUTTON | B_BUTTON)) {
        DisableBg(2);
        m4aSongNumStart(SONG_SYS_CLOSE);
        sMapInspectMenuState = 2;
    } else if (keys & START_BUTTON) {
        LoadBgMap(0, gMapInspectBgMap, 0x500);
        m4aSongNumStart(SONG_SYS_CLOSE);
        sMapInspectReturnToMenu = 0;
        FadeStartOut(FADE_MODE_BLACK, 16);
        sMapInspectState = 5;
    }
}

void MapInspectDraw() {
    s32 i;
    s32 j;
    s16 n;
    s16 t;
    void* anim;

    if (sMapInspectState != 2) {
        DrawSprite(sMapInspectBarX >> 8, 0,
#ifdef VERSION_EU
            sMapInspectTitleSpritesByLanguage[gLanguage],
#else
            gMapInspectBarFrame5,
#endif
            sMapInspectBarTiles, sMapInspectBarPalette, NULL, SPRITE_PRIORITY(3), 0xBB8);
        DrawSprite(128, sMapInspectBarY[0] >> 8,
#ifdef VERSION_EU
            sMapInspectTopBarSpritesByLanguage[gLanguage],
#else
            gMapInspectBarFrame6,
#endif
            sMapInspectBarTiles, sMapInspectBarPalette, NULL, SPRITE_PRIORITY(3), 0xBB9);
        DrawSprite(128, sMapInspectBarY[1] >> 8,
#ifdef VERSION_EU
            sMapInspectBottomBarSpritesByLanguage[gLanguage],
#else
            gMapInspectBarFrame7,
#endif
            sMapInspectBarTiles, sMapInspectBarPalette, NULL, SPRITE_PRIORITY(3), 0xBB9);
    }

    n = (GetMapInspectTabCount(sMapInspectTab) + 2) / 3 - 4;

    if (sMapInspectGridScroll <= n) {
        t = 84 * sMapInspectGridScroll / n;
    } else {
        t = 0;
    }

    DrawSprite(72, t + 40,
#ifdef VERSION_EU
            sMapInspectScrollMarkerSpritesByLanguage[gLanguage],
#else
            gMapInspectBarFrame4,
#endif
            sMapInspectBarTiles, sMapInspectBarPalette, NULL, SPRITE_PRIORITY(2), 0x898);

    if (sMapInspectState == 2) {
        switch (sMapInspectMenuState) {
        case 1:
            ApproachValueHalf(&sMapInspectCursorX, sMapCardCategoryDefs[sMapInspectTab].displayIndex * 3584 - 256);
            ApproachValueHalf(&sMapInspectCursorY, 0);
            DrawSprite(sMapInspectCursorX >> 8, sMapInspectCursorY >> 8, AnimUpdate(&sMapInspectCursorAnim), sMapInspectBarTiles, sMapInspectBarPalette, NULL, SPRITE_PRIORITY(2), 0x7D0);
            break;
        case 0:
            ApproachValueHalf(&sMapInspectCursorX, (sMapInspectGridCol * 23 - 2) * 256);
            ApproachValueHalf(&sMapInspectCursorY, (sMapInspectGridRow * 26 + 16) * 256);
            DrawSprite(sMapInspectCursorX >> 8, sMapInspectCursorY >> 8, AnimUpdate(&sMapInspectCursorAnim), sMapInspectBarTiles, sMapInspectBarPalette, NULL, SPRITE_PRIORITY(2), 0x7D0);
            DrawSprite(sMapInspectGridCol * 23 - 3, sMapInspectGridRow * 26 + 28, AnimUpdate(&sMapInspectHighlightAnim), sMapInspectHighlightTiles, sMapInspectCategoryPalette, NULL, SPRITE_PRIORITY(2), 0x7DA);
            break;
        case 2:
            GetMapInspectSelectedEntry();
            ApproachValueHalf(&sMapInspectCursorX, sMapInspectValueCol * 12288 + 0x9200);
            ApproachValueHalf(&sMapInspectCursorY, sMapInspectValueRow * 2048 + 0x1000);
            DrawSprite(sMapInspectCursorX >> 8, sMapInspectCursorY >> 8, AnimUpdate(&sMapInspectCursorAnim), sMapInspectBarTiles, sMapInspectBarPalette, NULL, SPRITE_PRIORITY(2), 0x7D0);
            DrawSprite(sMapInspectValueCol * 48 + 133, sMapInspectValueRow * 8 + 35, AnimUpdate(&sMapInspectHighlightAnim), sMapInspectHighlightTiles, sMapInspectCategoryPalette, NULL, SPRITE_PRIORITY(2), 0x7DA);
            break;
        case 3:
            ApproachValueHalf(&sMapInspectCursorX, sMapInspectConfirmCursor == 0 ? 0x3400 : 0x7400);
            ApproachValueHalf(&sMapInspectCursorY, 0x5000);
            DrawSprite(sMapInspectCursorX >> 8, sMapInspectCursorY >> 8, AnimUpdate(&sMapInspectCursorAnim), sMapInspectBarTiles, sMapInspectBarPalette, NULL, 0, 0);

            if (sMapInspectConfirmTextCount != 0) {
                DrawTextSlots(120 - GetTextSlotsWidth(sMapInspectConfirmText, sMapInspectConfirmTextCount) / 2, 64, sMapInspectConfirmText, sMapInspectBarPalette, 1, sMapInspectConfirmTextCount);
            }

            if (sMapInspectYesTextCount != 0) {
                DrawTextSlots(80, 84, sMapInspectYesText, sMapInspectBarPalette, 1, sMapInspectYesTextCount);
            }

            if (sMapInspectNoTextCount != 0) {
                DrawTextSlots(144, 84, sMapInspectNoText, sMapInspectBarPalette, 1, sMapInspectNoTextCount);
            }

            break;
        case 4:
            if (sMapInspectNoticeTextCount[0] != 0) {
                DrawTextSlots(120 - GetTextSlotsWidth(sMapInspectNoticeText[0], sMapInspectNoticeTextCount[0]) / 2, 68, sMapInspectNoticeText[0], sMapInspectBarPalette, 1, sMapInspectNoticeTextCount[0]);
#ifdef VERSION_JP
                DrawTextSlots(120 - GetTextSlotsWidth(sMapInspectNoticeText[1], sMapInspectNoticeTextCount[1]) / 2, 80, sMapInspectNoticeText[1], sMapInspectBarPalette, 1, sMapInspectNoticeTextCount[1]);
#endif
            }

            break;
        }
    }

    anim = AnimUpdate(&sMapInspectGridPremiumAnim);

    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 2; j++) {
            if (sMapInspectGridSprites[i][j] != NULL) {
                DrawSprite(j * 23 + 13, i * 26 + 47, sMapInspectGridSprites[i][j], sMapInspectGridTiles[i][j], sMapInspectGridPalettes[i][j], NULL, SPRITE_PRIORITY(2), 0x83E);

                if (sMapInspectGridPremium[i][j] != 0) {
                    DrawSprite(j * 23 + 13, i * 26 + 47, anim, sMapInspectGridPremiumTiles, sMapInspectCardBackPalette, NULL, SPRITE_PRIORITY(2), 0x834);
                }
            }
        }
    }

    if (sMapInspectMenuState != 1) {
        if (sMapInspectCardSprite != NULL) {
            DrawSprite(112, 56, sMapInspectCardSprite, sMapInspectCardTiles, sMapInspectCardPalette, NULL, SPRITE_PRIORITY(2), 0x848);
        }

        if (sMapInspectCardBackSprite != NULL) {
            DrawSprite(112, 56, sMapInspectCardBackSprite, sMapInspectCardBackTiles, sMapInspectCardBackPalette, NULL, SPRITE_PRIORITY(2), 0x83E);

            if (sMapInspectCardPremium) {
                DrawSprite(112, 56, AnimUpdate(&sMapInspectPremiumAnim), sMapInspectPremiumTiles, sMapInspectCardBackPalette, NULL, SPRITE_PRIORITY(2), 0x834);
            }
        }

        if (sMapInspectNameTextCount != 0) {
            if (sMapInspectMenuState != 3) {
                if (sMapInspectMenuState != 4) {
                    DrawTextSlots(96, 92, sMapInspectNameText, sMapInspectCategoryPalette, 1, sMapInspectNameTextCount);
                }
            }
        }

        if (sMapInspectDescTextCount != 0) {
            DrawTextSlots(95, 107, sMapInspectDescText, sMapInspectBarPalette, 1, sMapInspectDescTextCount);
        }
    }
}

void mode_mapinspect_0() {
    s16 i;
    s16 j;
    s16 v;
    u16 length;

    sMapCardInventoryEntries = EwramAlloc(27 * sizeof(MapCardInventoryEntry));
    SpriteReset();
    FadeStartIn(FADE_MODE_BLACK, 16);
    SetBgMode0();
    SetupBg(0, 0, 28, 0);
    SetupBg(1, 0, 29, 0);
    SetupBg(2, 2, 30, 15);
    SetupBg(3, 0, 31, 0);
    SetBgPriority(0, 3);
    SetBgPriority(1, 2);
    SetBgPriority(2, 1);
    SetBgPriority(3, 0);
    MapInspectBuildInventory();
    sMapInspectState = 0;
    sMapInspectSteps = 16;
    sMapInspectBarY[0] = -0x800;
    sMapInspectBarY[1] = 0xA800;
    sMapInspectBarX = -0x8000;
    sMapInspectTab = 4;
    sMapInspectGridCol = 0;
    sMapInspectGridRow = 0;
    sMapInspectGridScroll = 0;

    if (sMapInspectCardTotal > 0) {
        sMapInspectCursorX = (v = 0, -0x200);
        sMapInspectCursorY = 0x1000;
        sMapInspectMenuState = v;
    } else {
        sMapInspectCursorX = sMapCardCategoryDefs[4].displayIndex * 7 * 512 - 0x100;
        sMapInspectCursorY = 0;
        sMapInspectMenuState = 1;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            sMapInspectGridPalettes[i][j] = NULL;
            sMapInspectGridTiles[i][j] = NULL;
            sMapInspectGridSprites[i][j] = NULL;
            sMapInspectGridPremium[i][j] = 0;
        }
    }

    sMapInspectCardPalette = NULL;
    sMapInspectCardTiles = NULL;
    sMapInspectCardSprite = NULL;
    sMapInspectCardBackPalette = NULL;
    sMapInspectCardBackTiles = NULL;
    sMapInspectCardBackSprite = NULL;
    sMapInspectCardPremium = 0;
    sMapInspectCategoryPalette = NULL;
    sMapInspectValueCol = 0;
    sMapInspectValueRow = 0;
    LoadBgPalette(0, gMapInspectPalettes, 0x160);
#ifdef VERSION_EU
    LoadBgTiles(0, gMapInspectTiles, 0x2C00);

    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        break;
    case LANGUAGE_FRENCH:
        RequestDma3Copy(gMapInspectFrTiles, (u8*)GetBgCharBase(0) + 0x800, 0xC00);
        RequestDma3Copy(gMapInspectFrTiles + 0xC00, (u8*)GetBgCharBase(0) + 0x2400, 0x800);
        break;
    case LANGUAGE_GERMAN:
        RequestDma3Copy(gMapInspectDeTiles, (u8*)GetBgCharBase(0) + 0x800, 0xC00);
        RequestDma3Copy(gMapInspectDeTiles + 0xC00, (u8*)GetBgCharBase(0) + 0x2400, 0x800);
        break;
    case LANGUAGE_ITALIAN:
        RequestDma3Copy(gMapInspectItTiles, (u8*)GetBgCharBase(0) + 0x800, 0xC00);
        RequestDma3Copy(gMapInspectItTiles + 0xC00, (u8*)GetBgCharBase(0) + 0x2400, 0x800);
        break;
    case LANGUAGE_SPANISH:
        RequestDma3Copy(gMapInspectEsTiles, (u8*)GetBgCharBase(0) + 0x800, 0xC00);
        RequestDma3Copy(gMapInspectEsTiles + 0xC00, (u8*)GetBgCharBase(0) + 0x2400, 0x800);
        break;
    }
#else
    LoadBgTiles(0, gMapInspectTiles, 0x2980);
#endif
    LoadBgPalette(2, gCard00Palette, 0x20);
    LoadBgTiles(2, gConfirmWinTiles, 0x140);
    LoadBgMap(2, gConfirmWinMap, 0x800);
    LoadBgMap(0, gMapInspectBgMap, 0x500);

    if (GetMapInspectSelectedEntry()->category == 3) {
        LoadBgMap(1, gMapInspectPremiumValuesMap, 0x500);
    } else {
        LoadBgMap(1, gMapInspectValuesMap, 0x500);
    }

    MapInspectDrawTab(sMapInspectTab);
    MapInspectDrawCardTotal();
    MapInspectDrawCategoryCounts();
    MapInspectDrawValueCounts();
    sMapInspectBarPalette = LoadObjPalette(gMapInspectBarPalette, 0x20);
#ifdef VERSION_EU
    sMapInspectBarTiles = LoadObjTiles(sMapInspectBarTilesByLanguage[gLanguage], sMapInspectBarTileSizesByLanguage[gLanguage]);
    AnimInit(&sMapInspectCursorAnim, sMapInspectCursorAnimsByLanguage[gLanguage], sMapInspectCursorFramesByLanguage[gLanguage]);
#else
#ifdef VERSION_JP
    sMapInspectBarTiles = LoadObjTiles(gMapInspectBarTiles, 0xA80);
#else
    sMapInspectBarTiles = LoadObjTiles(gMapInspectBarTiles, 0xAC0);
#endif
    AnimInit(&sMapInspectCursorAnim, gMapInspectBarAnims, gMapInspectBarFrames);
#endif
    AnimStart(&sMapInspectCursorAnim, 0, ANIM_FLAG_LOOP);
    sMapInspectHighlightTiles = LoadObjTiles(gMapInspectHighlightTiles, 0xD60);
    AnimInit(&sMapInspectHighlightAnim, gMapInspectHighlightAnims, gMapInspectHighlightFrames);
    AnimStart(&sMapInspectHighlightAnim, 0, ANIM_FLAG_LOOP);
    sMapInspectBarPalette2 = LoadObjPalette(gMapInspectBarPalette, 0x20);
    sMapInspectPremiumTiles = LoadObjTiles(gCardPremiumTiles, 0x9A0);
    AnimInit(&sMapInspectPremiumAnim, gCardPremiumAnims, gCardPremiumFrames);
    AnimStart(&sMapInspectPremiumAnim, 0, ANIM_FLAG_LOOP);
    sMapInspectGridPremiumTiles = LoadObjTiles(gCardPremiumSmallTiles, 0x260);
    AnimInit(&sMapInspectGridPremiumAnim, gCardPremiumSmallAnims, gCardPremiumSmallFrames);
    AnimStart(&sMapInspectGridPremiumAnim, 0, ANIM_FLAG_LOOP);

    sMapInspectNameText = EwramAlloc(0x24 * sizeof(TextSlot));
    InitTextSlots(sMapInspectNameText, 0x24);
    sMapInspectDescText = EwramAlloc(0x5A * sizeof(TextSlot));
    InitTextSlots(sMapInspectDescText, 0x5A);

#ifdef VERSION_EU
    length = GetTextLength(GetLocalizedString(&gDeleteCardConfirmTextByLanguage));
#else
    length = GetTextLength(gDeleteCardConfirmText);
#endif
    sMapInspectConfirmTextLength = length;
    sMapInspectConfirmText = EwramAlloc(sMapInspectConfirmTextLength * sizeof(TextSlot));
    InitTextSlots(sMapInspectConfirmText, sMapInspectConfirmTextLength);
#ifdef VERSION_EU
    sMapInspectConfirmTextCount = LoadTextSlots(GetLocalizedString(&gDeleteCardConfirmTextByLanguage), sMapInspectConfirmText);
#else
    sMapInspectConfirmTextCount = LoadTextSlots(gDeleteCardConfirmText, sMapInspectConfirmText);
#endif

#ifdef VERSION_EU
    length = GetTextLength(GetLocalizedString(&gYesChoiceTextByLanguage));
#else
    length = GetTextLength(gYesChoiceText);
#endif
    sMapInspectYesTextLength = length;
    sMapInspectYesText = EwramAlloc(sMapInspectYesTextLength * sizeof(TextSlot));
    InitTextSlots(sMapInspectYesText, sMapInspectYesTextLength);
#ifdef VERSION_EU
    sMapInspectYesTextCount = LoadTextSlots(GetLocalizedString(&gYesChoiceTextByLanguage), sMapInspectYesText);
#else
    sMapInspectYesTextCount = LoadTextSlots(gYesChoiceText, sMapInspectYesText);
#endif

#ifdef VERSION_EU
    length = GetTextLength(GetLocalizedString(&gNoChoiceTextByLanguage));
#else
    length = GetTextLength(gNoChoiceText);
#endif
    sMapInspectNoTextLength = length;
    sMapInspectNoText = EwramAlloc(sMapInspectNoTextLength * sizeof(TextSlot));
    InitTextSlots(sMapInspectNoText, sMapInspectNoTextLength);
#ifdef VERSION_EU
    sMapInspectNoTextCount = LoadTextSlots(GetLocalizedString(&gNoChoiceTextByLanguage), sMapInspectNoText);
#else
    sMapInspectNoTextCount = LoadTextSlots(gNoChoiceText, sMapInspectNoText);
#endif

#ifdef VERSION_JP
    sMapInspectNoticeTextLength[0] = GetTextLength(gDeckErrorAnyMoreText);
    sMapInspectNoticeText[0] = EwramAlloc(sMapInspectNoticeTextLength[0] * sizeof(TextSlot));
    InitTextSlots(sMapInspectNoticeText[0], sMapInspectNoticeTextLength[0]);
    sMapInspectNoticeTextCount[0] = LoadTextSlots(gDeckErrorAnyMoreText, sMapInspectNoticeText[0]);

    sMapInspectNoticeTextLength[1] = GetTextLength(gDeckErrorLastAttackCardText);
    sMapInspectNoticeText[1] = EwramAlloc(sMapInspectNoticeTextLength[1] * sizeof(TextSlot));
    InitTextSlots(sMapInspectNoticeText[1], sMapInspectNoticeTextLength[1]);
    sMapInspectNoticeTextCount[1] = LoadTextSlots(gDeckErrorLastAttackCardText, sMapInspectNoticeText[1]);
#else
#ifdef VERSION_EU
    sMapInspectNoticeTextLength[0] = GetTextLength(GetLocalizedString(&gDeckErrorLastAttackCardTextByLanguage));
#else
    sMapInspectNoticeTextLength[0] = GetTextLength(gMapInspectNoticeText);
#endif
    sMapInspectNoticeText[0] = EwramAlloc(sMapInspectNoticeTextLength[0] * sizeof(TextSlot));
    InitTextSlots(sMapInspectNoticeText[0], sMapInspectNoticeTextLength[0]);
#ifdef VERSION_EU
    sMapInspectNoticeTextCount[0] = LoadTextSlots(GetLocalizedString(&gDeckErrorLastAttackCardTextByLanguage), sMapInspectNoticeText[0]);
#else
    sMapInspectNoticeTextCount[0] = LoadTextSlots(gMapInspectNoticeText, sMapInspectNoticeText[0]);
#endif
#endif

    MapInspectLoadGrid();
    MapInspectLoadSelectedCard();
    EnableBg(0);
    EnableBg(1);
    DisableBg(2);
    DisableBg(3);
}

void mode_mapinspect_1() {
    UpdatePlayTime();

    switch (sMapInspectState) {
    case 0:
        ApproachValue(&sMapInspectBarY[0], 0, sMapInspectSteps);
        ApproachValue(&sMapInspectBarY[1], 0x9800, sMapInspectSteps);
        sMapInspectSteps--;

        if (sMapInspectSteps <= 0) {
            sMapInspectSteps = 16;
            sMapInspectState = 1;
        }

        break;
    case 1:
        ApproachValue(&sMapInspectBarX, 0, sMapInspectSteps);
        sMapInspectSteps--;

        if (sMapInspectSteps <= 0) {
            LoadBgMap(0, gMapInspectBgHeaderMap, 0x500);
            sMapInspectState = 2;
        }

        break;
    case 2:
        switch (sMapInspectMenuState) {
        case 0:
            MapInspectHandleGridInput();
            break;
        case 1:
            MapInspectHandleTabInput();
            break;
        case 2:
            MapInspectHandleValueInput();
            break;
        case 3:
            MapInspectHandleConfirmInput();
            break;
        case 4:
            MapInspectHandleNoticeInput();
            break;
        }

        break;
    case 3:
        ApproachValue(&sMapInspectBarX, -0x8000, sMapInspectSteps);
        sMapInspectSteps--;

        if (sMapInspectSteps <= 0) {
            sMapInspectSteps = 16;
            sMapInspectState = 4;
        }

        break;
    case 4:
        ApproachValue(&sMapInspectBarY[0], -0x800, sMapInspectSteps);
        ApproachValue(&sMapInspectBarY[1], 0xA800, sMapInspectSteps);
        sMapInspectSteps--;

        if (sMapInspectSteps <= 0) {
            FadeStartOut(FADE_MODE_BLACK, 16);
            sMapInspectState = 5;
        }

        break;
    case 5:
        if (!FadeIsActive()) {
            ReturnToMap(sMapInspectReturnToMenu);
        }

        break;
    }

    MapInspectDraw();
}

void mode_mapinspect_2() {
    s32 i;
    s32 j;

    ReleaseObjPalette(sMapInspectBarPalette);
    ReleaseObjTiles(sMapInspectBarTiles);
    ReleaseObjTiles(sMapInspectHighlightTiles);
    ReleaseObjPalette(sMapInspectBarPalette2);
    ReleaseObjTiles(sMapInspectPremiumTiles);
    ReleaseObjTiles(sMapInspectGridPremiumTiles);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            if (sMapInspectGridPalettes[i][j] != NULL) {
                ReleaseObjPalette(sMapInspectGridPalettes[i][j]);
            }

            if (sMapInspectGridTiles[i][j] != NULL) {
                ReleaseObjTiles(sMapInspectGridTiles[i][j]);
            }
        }
    }

    if (sMapInspectCardPalette != NULL) {
        ReleaseObjPalette(sMapInspectCardPalette);
    }

    if (sMapInspectCardTiles != NULL) {
        ReleaseObjTiles(sMapInspectCardTiles);
    }

    if (sMapInspectCardBackPalette != NULL) {
        ReleaseObjPalette(sMapInspectCardBackPalette);
    }

    if (sMapInspectCardBackTiles != NULL) {
        ReleaseObjTiles(sMapInspectCardBackTiles);
    }

    if (sMapInspectCategoryPalette != NULL) {
        ReleaseObjPalette(sMapInspectCategoryPalette);
    }

    FreeTextSlots(sMapInspectNameText, 0x24);
    EwramFree(sMapInspectNameText);
    FreeTextSlots(sMapInspectDescText, 0x5A);
    EwramFree(sMapInspectDescText);
    FreeTextSlots(sMapInspectConfirmText, sMapInspectConfirmTextLength);
    EwramFree(sMapInspectConfirmText);
    FreeTextSlots(sMapInspectYesText, sMapInspectYesTextLength);
    EwramFree(sMapInspectYesText);
    FreeTextSlots(sMapInspectNoText, sMapInspectNoTextLength);
    EwramFree(sMapInspectNoText);

#ifdef VERSION_JP
    for (i = 0; i < 2; i++) {
#else
    for (i = 0; i < 1; i++) {
#endif
        FreeTextSlots(sMapInspectNoticeText[i], sMapInspectNoticeTextLength[i]);
        EwramFree(sMapInspectNoticeText[i]);
    }

    EwramFree(sMapCardInventoryEntries);
}

Mode gModeMapinspect = {
    "mode_mapinspect",
    (ModeInitFunc)mode_mapinspect_0,
    mode_mapinspect_1,
    mode_mapinspect_2,
};
