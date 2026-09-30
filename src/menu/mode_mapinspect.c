#include "localized_resource_assets.h"
#include "registration_data.h"
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
#include "gba/io_reg.h"
#include "malloc.h"
#include "fade.h"
#include "mode_ms_top_api.h"
#include "songs.h"
#include "ms_types.h"
#include "jiminy_data.h"

#ifdef VERSION_JP
extern u16 gUnk_0814FBB0[];
extern u16 gUnk_0814FBBC[];
#endif

#ifdef VERSION_EU
static void* sUnkEu_09F85008[5] = {
    gUnk_0999D9C0,
    gUnkEu_099A6BA8,
    gUnkEu_099A9128,
    gUnkEu_099A84A8,
    gUnkEu_099A7828,
};

static void* sUnkEu_09F8501C[5] = {
    gUnk_0999D9CA,
    gUnkEu_099A6BB2,
    gUnkEu_099A9132,
    gUnkEu_099A84B2,
    gUnkEu_099A7832,
};

static void* sUnkEu_09F85030[5] = {
    gUnk_0999D9E6,
    gUnkEu_099A6BC8,
    gUnkEu_099A9148,
    gUnkEu_099A84C8,
    gUnkEu_099A7848,
};

static void* sUnkEu_09F85044[5] = {
    gUnk_0999DA1A,
    gUnkEu_099A6BFC,
    gUnkEu_099A917C,
    gUnkEu_099A84FC,
    gUnkEu_099A787C,
};

static void* sUnkEu_09F85058[5] = {
    gUnkEu_099A6090,
    gUnkEu_099A6CCE,
    gUnkEu_099A924E,
    gUnkEu_099A85CE,
    gUnkEu_099A794E,
};

static AnimHeader** sUnkEu_09F8506C[5] = {
    gUnk_09EF981C,
    gUnkEu_09F8533C,
    gUnkEu_09F85408,
    gUnkEu_09F853C4,
    gUnkEu_09F85380,
};

static void** sUnkEu_09F85080[5] = {
    gUnk_09EF97EC,
    gUnkEu_09F8530C,
    gUnkEu_09F853D8,
    gUnkEu_09F85394,
    gUnkEu_09F85350,
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
static const u16 sUnkEu_09999A50[5] = {2752, 2816, 2816, 2816, 2816};
#endif

static const u16 sMapCardCategoryTypes[4] = {2, 1, 3, 4};

MapCardInventoryEntry* gMapCardInventoryEntries;
s16 gMapInspectMenuState;
s16 gMapInspectTab;
u16 gMapInspectCategoryStart[4] __attribute__((aligned(8)));
u16 gMapInspectCategoryEntryCount[4];
s16 gMapInspectCategoryCardCount[4];
s16 gMapInspectCardTotal;
struct ObjPalette* gUnk_02035E4C;
struct ObjTiles* gUnk_02035E50;
u32 gUnk_02035E54;
AnimState gMapInspectCursorAnim;
struct ObjPalette* gUnk_02035E70;
struct ObjPalette* gMapInspectCategoryPalette;
struct ObjTiles* gMapInspectHighlightTiles;
u32 gUnk_02035E7C;
AnimState gMapInspectHighlightAnim;
s16 gMapInspectGridCol;
s16 gMapInspectGridRow;
s16 gMapInspectGridScroll;
void* gMapInspectGridPalettes[4][3];
void* gMapInspectGridTiles[4][3];
void* gMapInspectGridSprites[4][3];
u8 gUnk_02035F30[4][3];
struct ObjPalette* gMapInspectCardPalette;
struct ObjTiles* gMapInspectCardTiles;
void* gMapInspectCardSprite;
struct ObjPalette* gUnk_02035F48;
struct ObjTiles* gUnk_02035F4C;
void* gUnk_02035F50;
struct ObjTiles* gUnk_02035F54;
AnimState gUnk_02035F58;
struct ObjTiles* gUnk_02035F70;
u32 gUnk_02035F74;
AnimState gUnk_02035F78;
u8 gUnk_02035F90;
TextSlot* gMapInspectNameText;
u8 gMapInspectNameTextCount;
TextSlot* gMapInspectDescText;
u8 gMapInspectDescTextCount;
TextSlot* gMapInspectConfirmText;
u8 gMapInspectConfirmTextCount;
u16 gMapInspectConfirmTextLength;
TextSlot* gMapInspectYesText;
u8 gMapInspectYesTextCount;
u16 gMapInspectYesTextLength;
TextSlot* gMapInspectNoText;
u8 gMapInspectNoTextCount;
u16 gMapInspectNoTextLength;
#ifdef VERSION_JP
u32 gUnkJp_02035F1C;
#endif
#ifdef VERSION_JP
TextSlot* gMapInspectNoticeText[2];
u8 gMapInspectNoticeTextCount[2];
u16 gUnkJp_02035F2A;
u16 gMapInspectNoticeTextLength[2];
#else
TextSlot* gMapInspectNoticeText[1];
u8 gMapInspectNoticeTextCount[1];
u16 gMapInspectNoticeTextLength[1];
#endif

s16 gMapInspectValueCol;
s16 gMapInspectValueRow;
s16 gMapInspectConfirmCursor;
s16 gMapInspectState;
s16 gMapInspectSteps;
#ifdef VERSION_JP
u32 gUnkJp_02035F3C;
#endif
s32 gMapInspectBarY[2];
s32 gMapInspectBarX;
s32 gMapInspectCursorX;
s32 gMapInspectCursorY;
u8 gMapInspectReturnToMenu;

s16 GetMapInspectTabStart(s16 a) {
    s16 r;

    if (a <= 3) {
        r = gMapInspectCategoryStart[a];
    } else {
        r = 0;
    }
    return r;
}

s16 GetMapInspectSelectedIndex(void) {
    return GetMapInspectTabStart(gMapInspectTab) + (gMapInspectGridScroll + gMapInspectGridRow) * 3 + gMapInspectGridCol;
}

MapCardInventoryEntry* GetMapInspectSelectedEntry(void) {
    return &gMapCardInventoryEntries[GetMapInspectSelectedIndex()];
}

void MapInspectSelectFirstValue(void) {
    MapCardInventoryEntry* p;
    s16 i;

    p = GetMapInspectSelectedEntry();
    if (p->cardType <= 26) {
        for (i = 0; i < 10; i++) {
            if (p->countsByValue[i] > 0) {
                break;
            }
        }
        gMapInspectValueCol = i / 5;
        gMapInspectValueRow = i % 5;
    } else {
        gMapInspectValueCol = 0;
        gMapInspectValueRow = 0;
    }
}

s16 GetMapInspectTabCount(s16 a) {
    s16 r;
    s16 i;
    s32 t;

    if (a <= 3) {
        r = gMapInspectCategoryEntryCount[a];
    } else {
        r = 0;

        for (i = 0; i <= 3; i++) {
            t = gMapInspectCategoryEntryCount[i];
            r += t;
        }
    }
    return r;
}

u8 MapInspectCanDelete(void) {
    if (gMapInspectCardTotal > 20) {
        return 1;
    }
    return 0;
}

void MapInspectLoadGrid(void) {
    s16 a;
    s16 k;
    s16 i;
    s16 j;
    s16 b;
    u16 idx;

    a = GetMapInspectTabStart(gMapInspectTab);
    b = GetMapInspectTabCount(gMapInspectTab);
    k = gMapInspectGridScroll * 3;

    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 2; j++) {
            if (gMapInspectGridPalettes[i][j] != NULL) {
                ReleaseObjPalette(gMapInspectGridPalettes[i][j]);
            }

            if (gMapInspectGridTiles[i][j] != NULL) {
                ReleaseObjTiles(gMapInspectGridTiles[i][j]);
            }

            if (k < b) {
                idx = gMapCardInventoryEntries[a + k].cardIndex;
                gMapInspectGridPalettes[i][j] = LoadObjPalette(gMapCardDefs[idx].palette2, 32);
                gMapInspectGridTiles[i][j] = LoadObjTiles(gMapCardDefs[idx].tiles2, gMapCardDefs[idx].tilesSize2);
                gMapInspectGridSprites[i][j] = *gMapCardDefs[idx].sprites2;
                gUnk_02035F30[i][j] = gMapCardInventoryEntries[a + k].category == 3;
            } else {
                gMapInspectGridPalettes[i][j] = 0;
                gMapInspectGridTiles[i][j] = 0;
                gMapInspectGridSprites[i][j] = 0;
                gUnk_02035F30[i][j] = 0;
            }
            k++;
        }
    }
}

void MapInspectLoadSelectedCard(void) {
    MapCardInventoryEntry* p;
    u16 idx;
    u16 k;
    u8* q;

    p = GetMapInspectSelectedEntry();

    if (gMapInspectCardPalette != NULL) {
        ReleaseObjPalette(gMapInspectCardPalette);
    }

    if (gMapInspectCardTiles != NULL) {
        ReleaseObjTiles(gMapInspectCardTiles);
    }

    if (gUnk_02035F48 != NULL) {
        ReleaseObjPalette(gUnk_02035F48);
    }

    if (gUnk_02035F4C != NULL) {
        ReleaseObjTiles(gUnk_02035F4C);
    }

    if (gMapInspectCategoryPalette != NULL) {
        ReleaseObjPalette(gMapInspectCategoryPalette);
    }

    if (p->cardType <= 26 && GetMapInspectTabCount(gMapInspectTab) > 0) {
        idx = p->cardIndex;
        k = sMapCardCategoryTypes[p->category];
        gMapInspectCardPalette = LoadObjPalette(gMapCardDefs[idx].palette, gMapCardDefs[idx].paletteSize);
        gMapInspectCardTiles = LoadObjTiles(gMapCardDefs[idx].tiles, gMapCardDefs[idx].tilesSize);
        gMapInspectCardSprite = *gMapCardDefs[idx].sprites;
        gUnk_02035F48 = LoadObjPalette(gMapCardBackDefs[k].palette, gMapCardBackDefs[k].paletteSize);
        gUnk_02035F4C = LoadObjTiles(gMapCardBackDefs[k].tiles, gMapCardBackDefs[k].tilesSize);
        gUnk_02035F50 = *gMapCardBackDefs[k].sprites;
        gUnk_02035F90 = p->category == 3;
        gMapInspectCategoryPalette = LoadObjPalette(gUnk_09A3D2FC + p->category * 32, 32);
        q = &gMapInspectNameTextCount;
        *q = LoadTextSlots(GetRoomName(p->cardType), gMapInspectNameText);
#ifdef VERSION_EU
        {
            u8** strings = gMapCardDescriptions[p->cardType]->strings;
            q = &gMapInspectDescTextCount;
            *q = LoadTextSlots((void*)strings[gLanguage], gMapInspectDescText);
        }
#else
        q = &gMapInspectDescTextCount;
        *q = LoadTextSlots((void*)gMapCardDescriptions[p->cardType], gMapInspectDescText);
#endif
    } else {
        gMapInspectCardPalette = 0;
        gMapInspectCardTiles = 0;
        gMapInspectCardSprite = 0;
        gUnk_02035F48 = 0;
        gUnk_02035F4C = 0;
        gUnk_02035F50 = 0;
        gUnk_02035F90 = 0;
        gMapInspectCategoryPalette = 0;
        gMapInspectNameTextCount = 0;
        gMapInspectDescTextCount = 0;
    }
}

s16 GetMapInspectValueIndex(s16 a, s16 b) {
    return b + a * 5;
}

s16 GetMapInspectSelectedValue(void) {
    return GetMapInspectValueIndex(gMapInspectValueCol, gMapInspectValueRow);
}

void MapInspectDrawCardTotal(void) {
    LoadDecimalDigitTiles(gMapInspectCardTotal, gUnk_09A0693C, (u8*)GetBgCharBase(0) + 0x3A0, 32, 2);
    LoadDecimalDigitTiles(99, gUnk_09A0693C, (u8*)GetBgCharBase(0) + 0x3E0, 32, 2);
}

void MapInspectDrawCategoryCounts(void) {
    s16 i;
    s16 v;

    for (i = 0; i <= 3; i++) {
        v = gMapInspectCategoryCardCount[i];
        if (v != 0) {
            LoadDecimalDigitTiles(v, gUnk_09A0669C, (u8*)GetBgCharBase(0) + (i * 64 + 0x2A0), 32, 2);
        } else {
            LoadDecimalDigitTiles(0, gUnk_09A0667C, (u8*)GetBgCharBase(0) + (i * 64 + 0x2A0), 32, 2);
        }
    }
}

void MapInspectDrawValueCounts(void) {
    MapCardInventoryEntry* p;
    s16 i;
    s32 v;

    p = GetMapInspectSelectedEntry();

    if (GetMapInspectTabCount(gMapInspectTab) > 0) {
        LoadPalette(gUnk_09A3D23C + p->category * 32, (void*)0x05000000, 12);
    }

    if (gMapInspectMenuState == 1) {
        for (i = 0; i <= 9; i++) {
            LoadDecimalDigitTiles(0, gUnk_09A067DC, (u8*)GetBgCharBase(0) + (i * 64 + 0x40), 32, 1);
            LoadPalette(gUnk_09A3D2C8, (void*)(0x05000000 + (i + 6) * 2), 2);
        }
    } else if (p->category == 3) {
        if (GetMapInspectTabCount(gMapInspectTab) > 0) {
            LoadBgMap(1, gUnk_09A3551C, 0x500);
        }

        for (i = 0; i <= 9; i++) {
            v = p->countsByValue[i];
            if (v != 0 && GetMapInspectTabCount(gMapInspectTab) > 0) {
                LoadDecimalDigitTiles(v, gUnk_09A067FC, (u8*)GetBgCharBase(0) + 0x40, 32, 1);
                LoadPalette(gUnk_09A3D248, (void*)0x0500000C, 2);
                break;
            }
        }

        if (i > 9) {
            LoadDecimalDigitTiles(0, gUnk_09A067DC, (u8*)GetBgCharBase(0) + 0x40, 32, 1);
            LoadPalette(gUnk_09A3D2C8, (void*)0x0500000C, 2);
        }
    } else {
        if (GetMapInspectTabCount(gMapInspectTab) > 0) {
            LoadBgMap(1, gUnk_09A3501C, 0x500);
        }

        for (i = 0; i <= 9; i++) {
            v = p->countsByValue[i];
            if (v != 0 && GetMapInspectTabCount(gMapInspectTab) > 0) {
                LoadDecimalDigitTiles(v, gUnk_09A067FC, (u8*)GetBgCharBase(0) + (i * 64 + 0x40), 32, 1);
                LoadPalette(gUnk_09A3D248, (void*)(0x05000000 + (i + 6) * 2), 2);
            } else {
                LoadDecimalDigitTiles(0, gUnk_09A067DC, (u8*)GetBgCharBase(0) + (i * 64 + 0x40), 32, 1);
                LoadPalette(gUnk_09A3D2C8, (void*)(0x05000000 + (i + 6) * 2), 2);
            }
        }
    }
}

void MapInspectDrawTab(s16 a) {
    RequestTilemapRectCopy(gUnk_09A34D9C, GetBgScreenBase(0), 0, sMapCardCategoryDefs[a].displayIndex * 2, 0, 2, 11, 2);
}

void MapInspectDeleteCard(void) {
    MapCardInventoryEntry* p;
    u16 card;

    p = GetMapInspectSelectedEntry();
    if (p->countsByValue[GetMapInspectSelectedValue()] > 0) {
        card = GetMapInspectSelectedValue() + p->cardIndex;
        gMapInspectCategoryCardCount[p->category]--;
        gMapInspectCardTotal--;
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
    gMapInspectValueCol = k / 5;
    gMapInspectValueRow = k % 5;
}

void MapInspectRemoveEntry(MapCardInventoryEntry* p) {
    vu32* dma;
    vu16 zero;
    MapCardInventoryEntry* q;
    u16 row;
    s16 j;

    row = p->category;
    dma = (vu32*)REG_ADDR_DMA3;
    dma[0] = (u32)(p + 1);
    dma[1] = (u32)p;
    dma[2] = ((26 - GetMapInspectSelectedIndex()) * 14) | (DMA_ENABLE << 16);
    dma[2];
    zero = 0;
    dma[0] = (u32)&zero;
    q = &gMapCardInventoryEntries[26];
    dma[1] = (u32)q;
    dma[2] = ((DMA_ENABLE | DMA_SRC_FIXED) << 16) | 0xE;
    dma[2];
    q->cardType = 27;

    for (j = row + 1; j <= 3; j++) {
        gMapInspectCategoryStart[j]--;
    }
    gMapInspectCategoryEntryCount[row]--;

    if (GetMapInspectSelectedIndex() >= GetMapInspectTabCount(gMapInspectTab)) {
        if (--gMapInspectGridCol < 0) {
            gMapInspectGridCol = 2;

            if (--gMapInspectGridRow < 0) {
                gMapInspectGridRow = 0;

                if (--gMapInspectGridScroll < 0) {
                    gMapInspectGridCol = 0;
                    gMapInspectGridScroll = 0;
                }
            }
        }
    }
    gMapInspectValueCol = 0;
    gMapInspectValueRow = 0;
    MapInspectLoadGrid();
    MapInspectLoadSelectedCard();
    MapInspectDrawValueCounts();
}

void MapInspectBuildInventory(void) {
    s16* pd;
    vu32* dma;
    vu16 zero;
    s32 w;
    s16 k;
    s16 j;
    s16 i;
    s16 a;
    u16 u;
    u16 n;
    u16 t;

    zero = 0;
    dma = (vu32*)REG_ADDR_DMA3;
    dma[0] = (u32)&zero;
    dma[1] = (u32)gMapCardInventoryEntries;
    dma[2] = ((DMA_ENABLE | DMA_SRC_FIXED) << 16) | 0x17A;
    dma[2];

    for (i = 0; i <= 26; i++) {
        gMapCardInventoryEntries[i].cardType = 27;
    }
    a = 0;
    gMapInspectCardTotal = 0;

    for (j = 0; j <= 3; j++) {
        gMapInspectCategoryStart[j] = a;
        gMapInspectCategoryCardCount[j] = 0;

        for (k = 0; k <= 26; k++) {
            t = gMapCardDefs[k * 10].color;
            if (t == sMapCardCategoryTypes[j]) {
                u = gMapCardDefs[k * 10].kind;

                for (i = 0; i <= 9; i++) {
                    n = gMapCardCounts[(u16)(k * 10 + i)];
                    if (n != 0) {
                        if (t != 4) {
                            gMapInspectCardTotal += n;
                        }
                        {
                            s16* counts = gMapInspectCategoryCardCount;
                            s32 index = a;

                            counts[j] += n;
                            gMapCardInventoryEntries[index].cardType = u;
                            gMapCardInventoryEntries[index].cardIndex = k * 10;
                            gMapCardInventoryEntries[index].category = j;
                            gMapCardInventoryEntries[index].countsByValue[i] = n;
                        }
                    }
                }
            }

            if (gMapCardInventoryEntries[a].cardType <= 26) {
                a++;
            }
        }
        pd = &gMapInspectCategoryEntryCount[j];
        w = gMapInspectCategoryStart[j];
        *pd = a - w;
    }
}

u16 MapInspectReadMenuKeys(void) {
    u16 keys;

    keys = GetKeysPressed() & (A_BUTTON | B_BUTTON | SELECT_BUTTON | START_BUTTON);
    keys |= GetKeysRepeat() & (DPAD_ANY | L_BUTTON | R_BUTTON);
    return keys;
}

void MapInspectHandleGridInput(void) {
    s16 a;
    s16 b;
    s16 c;
    u16 keys;

    a = gMapInspectGridCol;
    b = gMapInspectGridRow;
    c = gMapInspectGridScroll;
    keys = MapInspectReadMenuKeys();
    if (keys & 1) {
        if (GetMapInspectSelectedEntry()->category != 3) {
            MapInspectSelectFirstValue();
            m4aSongNumStart(SONG_SYS_KETTEI);
            AnimStart(&gMapInspectHighlightAnim, 1, 1);
            gMapInspectMenuState = 2;
        } else {
            m4aSongNumStart(SONG_SYS_BEEP);
        }
    } else if (keys & 2) {
        LoadBgMap(0, gUnk_09A3439C, 0x500);
        m4aSongNumStart(SONG_SYS_CLOSE);
        gMapInspectReturnToMenu = 1;
        gMapInspectSteps = 16;
        gMapInspectState = 3;
    } else if (keys & 8) {
        LoadBgMap(0, gUnk_09A3439C, 0x500);
        m4aSongNumStart(SONG_SYS_CLOSE);
        gMapInspectReturnToMenu = 0;
        FadeStartOut(0, 16);
        gMapInspectState = 5;
    } else if (keys & 4) {
        gMapInspectGridCol = 0;
        gMapInspectGridRow = 0;
        gMapInspectGridScroll = 0;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
        gMapInspectMenuState = 1;
        MapInspectDrawValueCounts();
    } else if (keys & 0x40) {
        if (gMapInspectGridRow > 0) {
            gMapInspectGridRow--;
        } else if (gMapInspectGridScroll > 0) {
            gMapInspectGridScroll--;
        } else {
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            gMapInspectMenuState = 1;
            MapInspectDrawValueCounts();
        }
    } else if (keys & 0x80) {
        if ((gMapInspectGridScroll + gMapInspectGridRow + 1) * 3 + gMapInspectGridCol < GetMapInspectTabCount(gMapInspectTab)) {
            if (gMapInspectGridRow > 2) {
                gMapInspectGridScroll++;
            } else {
                gMapInspectGridRow++;
            }
        } else if (gMapInspectGridRow == 3) {
            if ((gMapInspectGridScroll + gMapInspectGridRow + 1) * 3 < GetMapInspectTabCount(gMapInspectTab)) {
                gMapInspectGridCol = (GetMapInspectTabCount(gMapInspectTab) - 1) % 3;
                gMapInspectGridScroll++;
            }
        }
    } else if (keys & 0x20) {
        if (gMapInspectGridCol > 0) {
            gMapInspectGridCol--;
        }
    } else if (keys & 0x10) {
        if ((gMapInspectGridScroll + gMapInspectGridRow) * 3 + gMapInspectGridCol + 1 < GetMapInspectTabCount(gMapInspectTab)) {
            if (gMapInspectGridCol <= 1) {
                gMapInspectGridCol++;
            }
        }
    }

    if (gMapInspectGridCol != a || gMapInspectGridRow != b || gMapInspectGridScroll != c) {
        MapInspectSelectFirstValue();
        MapInspectDrawValueCounts();
        MapInspectLoadSelectedCard();
        m4aSongNumStart(SONG_SYS_CLICKI04B);

        if (gMapInspectGridScroll != c) {
            MapInspectLoadGrid();
        }
    }
}

void MapInspectHandleTabInput(void) {
    s16 old;
    u16 keys;

    old = gMapInspectTab;
    keys = MapInspectReadMenuKeys();
    if ((keys & 1) == 0) {
        if (keys & 8) {
            LoadBgMap(0, gUnk_09A3439C, 0x500);
            m4aSongNumStart(SONG_SYS_CLOSE);
            gMapInspectReturnToMenu = 0;
            FadeStartOut(0, 16);
            gMapInspectState = 5;
        } else if (keys & 0x82) {
            if (GetMapInspectTabCount(gMapInspectTab) > 0) {
                gMapInspectGridCol = 0;
                gMapInspectGridRow = 0;
                gMapInspectGridScroll = 0;
                MapInspectSelectFirstValue();
                MapInspectDrawValueCounts();
                MapInspectLoadSelectedCard();
                AnimStart(&gMapInspectHighlightAnim, 0, 1);
                m4aSongNumStart(SONG_SYS_CLICKI04B);
                gMapInspectMenuState = 0;
                MapInspectDrawValueCounts();
            } else if (keys & 2) {
                LoadBgMap(0, gUnk_09A3439C, 0x500);
                m4aSongNumStart(SONG_SYS_CLOSE);
                gMapInspectReturnToMenu = 1;
                gMapInspectSteps = 16;
                gMapInspectState = 3;
            } else if (keys & 0x80) {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        } else if (keys & 0x20) {
            gMapInspectTab = sMapCardCategoryDefs[gMapInspectTab].leftCategory;
        } else if (keys & 0x10) {
            gMapInspectTab = sMapCardCategoryDefs[gMapInspectTab].rightCategory;
        }
    }

    if (gMapInspectTab < 0) {
        gMapInspectTab = old;
    }

    if (gMapInspectTab != old) {
        MapInspectDrawTab(gMapInspectTab);
        MapInspectLoadGrid();
        m4aSongNumStart(SONG_SYS_CLICK);
    }
}

void MapInspectSelectValueInColumn(MapCardInventoryEntry* p, u16 row) {
    s16 c;
    s16 i;
    s32 k;

    c = gMapInspectValueRow;

    for (i = 0; i <= 4; i++) {
        k = c - i;
        if (k >= 0 && p->countsByValue[GetMapInspectValueIndex(row, k)] > 0) {
            gMapInspectValueCol = row;
            gMapInspectValueRow = k;
            return;
        }
        k = c + i;
        if (k <= 4 && p->countsByValue[GetMapInspectValueIndex(row, k)] > 0) {
            gMapInspectValueCol = row;
            gMapInspectValueRow = k;
            return;
        }
    }
}

void MapInspectHandleValueInput(void) {
    MapCardInventoryEntry* p;
    s16 a;
    s16 b;
    s16 i;
    u16 keys;
    u16 trg;

    p = GetMapInspectSelectedEntry();
    a = gMapInspectValueCol;
    b = gMapInspectValueRow;
    trg = MapInspectReadMenuKeys();
    keys = trg;

    if (keys & 1) {
        if (MapInspectCanDelete()) {
            gMapInspectConfirmCursor = 1;
            gMapInspectCursorX = 0x7400;
            gMapInspectCursorY = 0x5000;
            AnimStart(&gMapInspectCursorAnim, 4, 1);
            EnableBg(2);
            m4aSongNumStart(SONG_SYS_CANSEL);
            gMapInspectMenuState = 3;
        } else {
            EnableBg(2);
            m4aSongNumStart(SONG_SYS_BEEP);
            gMapInspectMenuState = 4;
        }
    } else {
        if (keys & 2) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            AnimStart(&gMapInspectHighlightAnim, 0, 1);
            gMapInspectMenuState = 0;
        } else if (keys & 8) {
            LoadBgMap(0, gUnk_09A3439C, 0x500);
            m4aSongNumStart(SONG_SYS_CLOSE);
            gMapInspectReturnToMenu = 0;
            FadeStartOut(0, 16);
            gMapInspectState = 5;
        } else if (keys & 0x20) {
            MapInspectSelectValueInColumn(p, 0);
        } else if (keys & 0x10) {
            MapInspectSelectValueInColumn(p, 1);
        } else if (keys & 0x40) {
            for (i = 0; i <= 4; i++) {
                if (--gMapInspectValueRow < 0) {
                    gMapInspectValueRow = 4;
                }

                if (p->countsByValue[GetMapInspectSelectedValue()] > 0) {
                    break;
                }
            }
        } else if (keys & 0x80) {
            for (i = 0; i <= 4; i++) {
                if (++gMapInspectValueRow > 4) {
                    gMapInspectValueRow = 0;
                }

                if (p->countsByValue[GetMapInspectSelectedValue()] > 0) {
                    break;
                }
            }
        }
    }

    if (gMapInspectValueCol != a || gMapInspectValueRow != b) {
        m4aSongNumStart(SONG_SYS_CLICK);
    }
}

void MapInspectHandleConfirmInput(void) {
    MapCardInventoryEntry* p;
    s16 old;
    u16 keys;

    p = GetMapInspectSelectedEntry();
    old = gMapInspectConfirmCursor;
    keys = MapInspectReadMenuKeys();
    if (keys & 1) {
        gMapInspectCursorX = gMapInspectValueCol * 12288 + 0x9200;
        gMapInspectCursorY = gMapInspectValueRow * 2048 + 0x1000;
        AnimStart(&gMapInspectCursorAnim, 0, 1);
        DisableBg(2);

        if (gMapInspectConfirmCursor == 0) {
            MapInspectDeleteCard();
            m4aSongNumStart(SONG_SYS_CARD_DELETE);

            if (MapCardEntryIsEmpty(p)) {
                MapInspectRemoveEntry(p);

                if (GetMapInspectTabCount(gMapInspectTab) > 0) {
                    AnimStart(&gMapInspectHighlightAnim, 0, 1);
                    gMapInspectMenuState = 0;
                } else {
                    gMapInspectMenuState = 1;
                }
            } else {
                if (MapCardEntrySelectedValueIsEmpty(p)) {
                    MapInspectSelectNextValue(p);
                }
                AnimStart(&gMapInspectHighlightAnim, 1, 1);
                gMapInspectMenuState = 2;
            }
        } else {
            m4aSongNumStart(SONG_SYS_CLOSE);
            AnimStart(&gMapInspectHighlightAnim, 1, 1);
            gMapInspectMenuState = 2;
        }
    } else if (keys & 2) {
        gMapInspectCursorX = gMapInspectValueCol * 12288 + 0x9200;
        gMapInspectCursorY = gMapInspectValueRow * 2048 + 0x1000;
        AnimStart(&gMapInspectCursorAnim, 0, 1);
        DisableBg(2);
        m4aSongNumStart(SONG_SYS_CLOSE);
        AnimStart(&gMapInspectHighlightAnim, 1, 1);
        gMapInspectMenuState = 2;
    } else if (keys & 8) {
        LoadBgMap(0, gUnk_09A3439C, 0x500);
        m4aSongNumStart(SONG_SYS_CLOSE);
        gMapInspectReturnToMenu = 0;
        FadeStartOut(0, 16);
        gMapInspectState = 5;
    } else if (keys & 0x20) {
        gMapInspectConfirmCursor = 0;
    } else if (keys & 0x10) {
        gMapInspectConfirmCursor = 1;
    }

    if (gMapInspectConfirmCursor != old) {
        m4aSongNumStart(SONG_SYS_CLICK);
    }
}

void MapInspectHandleNoticeInput(void) {
    u16 keys;

    keys = MapInspectReadMenuKeys();
    if (keys & 3) {
        DisableBg(2);
        m4aSongNumStart(SONG_SYS_CLOSE);
        gMapInspectMenuState = 2;
    } else if (keys & 8) {
        LoadBgMap(0, gUnk_09A3439C, 0x500);
        m4aSongNumStart(SONG_SYS_CLOSE);
        gMapInspectReturnToMenu = 0;
        FadeStartOut(0, 16);
        gMapInspectState = 5;
    }
}

void MapInspectDraw(void) {
    s32 i;
    s32 j;
    s16 n;
    s16 t;
    void* anim;

    if (gMapInspectState != 2) {
        DrawSprite(gMapInspectBarX >> 8, 0,
#ifdef VERSION_EU
            sUnkEu_09F8501C[gLanguage],
#else
            gUnk_0999D9CA,
#endif
            gUnk_02035E50, gUnk_02035E4C, 0, 0xC00, 0xBB8);
        DrawSprite(128, gMapInspectBarY[0] >> 8,
#ifdef VERSION_EU
            sUnkEu_09F85030[gLanguage],
#else
            gUnk_0999D9E6,
#endif
            gUnk_02035E50, gUnk_02035E4C, 0, 0xC00, 0xBB9);
        DrawSprite(128, gMapInspectBarY[1] >> 8,
#ifdef VERSION_EU
            sUnkEu_09F85044[gLanguage],
#else
            gUnk_0999DA1A,
#endif
            gUnk_02035E50, gUnk_02035E4C, 0, 0xC00, 0xBB9);
    }
    n = (GetMapInspectTabCount(gMapInspectTab) + 2) / 3 - 4;
    if (gMapInspectGridScroll <= n) {
        t = 84 * gMapInspectGridScroll / n;
    } else {
        t = 0;
    }
    DrawSprite(72, t + 40,
#ifdef VERSION_EU
            sUnkEu_09F85008[gLanguage],
#else
            gUnk_0999D9C0,
#endif
            gUnk_02035E50, gUnk_02035E4C, 0, 0x800, 0x898);

    if (gMapInspectState == 2) {
        switch (gMapInspectMenuState) {
        case 1:
            ApproachValueHalf(&gMapInspectCursorX, sMapCardCategoryDefs[gMapInspectTab].displayIndex * 3584 - 256);
            ApproachValueHalf(&gMapInspectCursorY, 0);
            DrawSprite(gMapInspectCursorX >> 8, gMapInspectCursorY >> 8, AnimUpdate(&gMapInspectCursorAnim), gUnk_02035E50, gUnk_02035E4C, 0, 0x800, 0x7D0);
            break;
        case 0:
            ApproachValueHalf(&gMapInspectCursorX, (gMapInspectGridCol * 23 - 2) * 256);
            ApproachValueHalf(&gMapInspectCursorY, (gMapInspectGridRow * 26 + 16) * 256);
            DrawSprite(gMapInspectCursorX >> 8, gMapInspectCursorY >> 8, AnimUpdate(&gMapInspectCursorAnim), gUnk_02035E50, gUnk_02035E4C, 0, 0x800, 0x7D0);
            DrawSprite(gMapInspectGridCol * 23 - 3, gMapInspectGridRow * 26 + 28, AnimUpdate(&gMapInspectHighlightAnim), gMapInspectHighlightTiles, gMapInspectCategoryPalette, 0, 0x800, 0x7DA);
            break;
        case 2:
            GetMapInspectSelectedEntry();
            ApproachValueHalf(&gMapInspectCursorX, gMapInspectValueCol * 12288 + 0x9200);
            ApproachValueHalf(&gMapInspectCursorY, gMapInspectValueRow * 2048 + 0x1000);
            DrawSprite(gMapInspectCursorX >> 8, gMapInspectCursorY >> 8, AnimUpdate(&gMapInspectCursorAnim), gUnk_02035E50, gUnk_02035E4C, 0, 0x800, 0x7D0);
            DrawSprite(gMapInspectValueCol * 48 + 133, gMapInspectValueRow * 8 + 35, AnimUpdate(&gMapInspectHighlightAnim), gMapInspectHighlightTiles, gMapInspectCategoryPalette, 0, 0x800, 0x7DA);
            break;
        case 3:
            ApproachValueHalf(&gMapInspectCursorX, gMapInspectConfirmCursor == 0 ? 0x3400 : 0x7400);
            ApproachValueHalf(&gMapInspectCursorY, 0x5000);
            DrawSprite(gMapInspectCursorX >> 8, gMapInspectCursorY >> 8, AnimUpdate(&gMapInspectCursorAnim), gUnk_02035E50, gUnk_02035E4C, 0, 0, 0);

            if (gMapInspectConfirmTextCount != 0) {
                DrawTextSlots(120 - GetTextSlotsWidth(gMapInspectConfirmText, gMapInspectConfirmTextCount) / 2, 64, gMapInspectConfirmText, gUnk_02035E4C, 1, gMapInspectConfirmTextCount);
            }

            if (gMapInspectYesTextCount != 0) {
                DrawTextSlots(80, 84, gMapInspectYesText, gUnk_02035E4C, 1, gMapInspectYesTextCount);
            }

            if (gMapInspectNoTextCount != 0) {
                DrawTextSlots(144, 84, gMapInspectNoText, gUnk_02035E4C, 1, gMapInspectNoTextCount);
            }
            break;
        case 4:
            if (gMapInspectNoticeTextCount[0] != 0) {
                DrawTextSlots(120 - GetTextSlotsWidth(gMapInspectNoticeText[0], gMapInspectNoticeTextCount[0]) / 2, 68, gMapInspectNoticeText[0], gUnk_02035E4C, 1, gMapInspectNoticeTextCount[0]);
#ifdef VERSION_JP
                DrawTextSlots(120 - GetTextSlotsWidth(gMapInspectNoticeText[1], gMapInspectNoticeTextCount[1]) / 2, 80, gMapInspectNoticeText[1], gUnk_02035E4C, 1, gMapInspectNoticeTextCount[1]);
#endif
            }
            break;
        }
    }
    anim = AnimUpdate(&gUnk_02035F78);

    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 2; j++) {
            if (gMapInspectGridSprites[i][j] != NULL) {
                DrawSprite(j * 23 + 13, i * 26 + 47, gMapInspectGridSprites[i][j], gMapInspectGridTiles[i][j], gMapInspectGridPalettes[i][j], 0, 0x800, 0x83E);

                if (gUnk_02035F30[i][j] != 0) {
                    DrawSprite(j * 23 + 13, i * 26 + 47, anim, gUnk_02035F70, gUnk_02035F48, 0, 0x800, 0x834);
                }
            }
        }
    }

    if (gMapInspectMenuState != 1) {
        if (gMapInspectCardSprite != NULL) {
            DrawSprite(112, 56, gMapInspectCardSprite, gMapInspectCardTiles, gMapInspectCardPalette, 0, 0x800, 0x848);
        }

        if (gUnk_02035F50 != NULL) {
            DrawSprite(112, 56, gUnk_02035F50, gUnk_02035F4C, gUnk_02035F48, 0, 0x800, 0x83E);

            if (gUnk_02035F90 != 0) {
                DrawSprite(112, 56, AnimUpdate(&gUnk_02035F58), gUnk_02035F54, gUnk_02035F48, 0, 0x800, 0x834);
            }
        }

        if (gMapInspectNameTextCount != 0) {
            if (gMapInspectMenuState != 3) {
                if (gMapInspectMenuState != 4) {
                    DrawTextSlots(96, 92, gMapInspectNameText, gMapInspectCategoryPalette, 1, gMapInspectNameTextCount);
                }
            }
        }

        if (gMapInspectDescTextCount != 0) {
            DrawTextSlots(95, 107, gMapInspectDescText, gUnk_02035E4C, 1, gMapInspectDescTextCount);
        }
    }
}

void mode_mapinspect_0(void) {
    s16 i;
    s16 j;
    s16 v;
    u16 length;

    gMapCardInventoryEntries = EwramAlloc(27 * sizeof(MapCardInventoryEntry));
    SpriteReset();
    FadeStartIn(0, 16);
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
    gMapInspectState = 0;
    gMapInspectSteps = 16;
    gMapInspectBarY[0] = -0x800;
    gMapInspectBarY[1] = 0xA800;
    gMapInspectBarX = -0x8000;
    gMapInspectTab = 4;
    gMapInspectGridCol = 0;
    gMapInspectGridRow = 0;
    gMapInspectGridScroll = 0;

    if (gMapInspectCardTotal > 0) {
        gMapInspectCursorX = (v = 0, -0x200);
        gMapInspectCursorY = 0x1000;
        gMapInspectMenuState = v;
    } else {
        gMapInspectCursorX = sMapCardCategoryDefs[4].displayIndex * 7 * 512 - 0x100;
        gMapInspectCursorY = 0;
        gMapInspectMenuState = 1;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            gMapInspectGridPalettes[i][j] = 0;
            gMapInspectGridTiles[i][j] = 0;
            gMapInspectGridSprites[i][j] = 0;
            gUnk_02035F30[i][j] = 0;
        }
    }

    gMapInspectCardPalette = 0;
    gMapInspectCardTiles = 0;
    gMapInspectCardSprite = 0;
    gUnk_02035F48 = 0;
    gUnk_02035F4C = 0;
    gUnk_02035F50 = 0;
    gUnk_02035F90 = 0;
    gMapInspectCategoryPalette = 0;
    gMapInspectValueCol = 0;
    gMapInspectValueRow = 0;
    LoadBgPalette(0, gUnk_09A3D0DC, 0x160);
#ifdef VERSION_EU
    LoadBgTiles(0, gUnk_09A03CFC, 0x2C00);

    switch (gLanguage) {
    case 0:
        break;
    case 1:
        RequestDma3Copy(gUnkEu_09A3D400, (u8*)GetBgCharBase(0) + 0x800, 0xC00);
        RequestDma3Copy(gUnkEu_09A3D400 + 0xC00, (u8*)GetBgCharBase(0) + 0x2400, 0x800);
        break;
    case 2:
        RequestDma3Copy(gUnkEu_09A41000, (u8*)GetBgCharBase(0) + 0x800, 0xC00);
        RequestDma3Copy(gUnkEu_09A41000 + 0xC00, (u8*)GetBgCharBase(0) + 0x2400, 0x800);
        break;
    case 3:
        RequestDma3Copy(gUnkEu_09A3FC00, (u8*)GetBgCharBase(0) + 0x800, 0xC00);
        RequestDma3Copy(gUnkEu_09A3FC00 + 0xC00, (u8*)GetBgCharBase(0) + 0x2400, 0x800);
        break;
    case 4:
        RequestDma3Copy(gUnkEu_09A3E800, (u8*)GetBgCharBase(0) + 0x800, 0xC00);
        RequestDma3Copy(gUnkEu_09A3E800 + 0xC00, (u8*)GetBgCharBase(0) + 0x2400, 0x800);
        break;
    }
#else
    LoadBgTiles(0, gUnk_09A03CFC, 0x2980);
#endif
    LoadBgPalette(2, gCard00Palette, 0x20);
    LoadBgTiles(2, gUnk_099597E4, 0x140);
    LoadBgMap(2, gUnk_09985F44, 0x800);
    LoadBgMap(0, gUnk_09A3439C, 0x500);

    if (GetMapInspectSelectedEntry()->category == 3) {
        LoadBgMap(1, gUnk_09A3551C, 0x500);
    } else {
        LoadBgMap(1, gUnk_09A3501C, 0x500);
    }

    MapInspectDrawTab(gMapInspectTab);
    MapInspectDrawCardTotal();
    MapInspectDrawCategoryCounts();
    MapInspectDrawValueCounts();
    gUnk_02035E4C = LoadObjPalette(gUnk_09A3D2DC, 0x20);
#ifdef VERSION_EU
    gUnk_02035E50 = LoadObjTiles(sUnkEu_09F85058[gLanguage], sUnkEu_09999A50[gLanguage]);
    AnimInit(&gMapInspectCursorAnim, sUnkEu_09F8506C[gLanguage], sUnkEu_09F85080[gLanguage]);
#else
#ifdef VERSION_JP
    gUnk_02035E50 = LoadObjTiles(gUnk_0999DAEC, 0xA80);
#else
    gUnk_02035E50 = LoadObjTiles(gUnk_0999DAEC, 0xAC0);
#endif
    AnimInit(&gMapInspectCursorAnim, gUnk_09EF981C, gUnk_09EF97EC);
#endif
    AnimStart(&gMapInspectCursorAnim, 0, 1);
    gMapInspectHighlightTiles = LoadObjTiles(gUnk_0999E69E, 0xD60);
    AnimInit(&gMapInspectHighlightAnim, gUnk_09EF9858, gUnk_09EF9830);
    AnimStart(&gMapInspectHighlightAnim, 0, 1);
    gUnk_02035E70 = LoadObjPalette(gUnk_09A3D2DC, 0x20);
    gUnk_02035F54 = LoadObjTiles(gUnk_0908B1B4, 0x9A0);
    AnimInit(&gUnk_02035F58, gUnk_09EEA164, gUnk_09EEA148);
    AnimStart(&gUnk_02035F58, 0, 1);
    gUnk_02035F70 = LoadObjTiles(gUnk_0908C3CE, 0x260);
    AnimInit(&gUnk_02035F78, gUnk_09EEA198, gUnk_09EEA180);
    AnimStart(&gUnk_02035F78, 0, 1);

    gMapInspectNameText = EwramAlloc(0x24 * sizeof(TextSlot));
    InitTextSlots(gMapInspectNameText, 0x24);
    gMapInspectDescText = EwramAlloc(0x5A * sizeof(TextSlot));
    InitTextSlots(gMapInspectDescText, 0x5A);

#ifdef VERSION_EU
    length = GetTextLength(eu_0805E924(&gUnkEu_08890EC0));
#else
    length = GetTextLength(gUnk_08159FBC);
#endif
    gMapInspectConfirmTextLength = length;
    gMapInspectConfirmText = EwramAlloc(gMapInspectConfirmTextLength * sizeof(TextSlot));
    InitTextSlots(gMapInspectConfirmText, gMapInspectConfirmTextLength);
#ifdef VERSION_EU
    gMapInspectConfirmTextCount = LoadTextSlots(eu_0805E924(&gUnkEu_08890EC0), gMapInspectConfirmText);
#else
    gMapInspectConfirmTextCount = LoadTextSlots(gUnk_08159FBC, gMapInspectConfirmText);
#endif

#ifdef VERSION_EU
    length = GetTextLength(eu_0805E924(&gUnkEu_08890E1C));
#else
    length = GetTextLength(gUnk_08159E10);
#endif
    gMapInspectYesTextLength = length;
    gMapInspectYesText = EwramAlloc(gMapInspectYesTextLength * sizeof(TextSlot));
    InitTextSlots(gMapInspectYesText, gMapInspectYesTextLength);
#ifdef VERSION_EU
    gMapInspectYesTextCount = LoadTextSlots(eu_0805E924(&gUnkEu_08890E1C), gMapInspectYesText);
#else
    gMapInspectYesTextCount = LoadTextSlots(gUnk_08159E10, gMapInspectYesText);
#endif

#ifdef VERSION_EU
    length = GetTextLength(eu_0805E924(&gUnkEu_08890E44));
#else
    length = GetTextLength(gUnk_08159E18);
#endif
    gMapInspectNoTextLength = length;
    gMapInspectNoText = EwramAlloc(gMapInspectNoTextLength * sizeof(TextSlot));
    InitTextSlots(gMapInspectNoText, gMapInspectNoTextLength);
#ifdef VERSION_EU
    gMapInspectNoTextCount = LoadTextSlots(eu_0805E924(&gUnkEu_08890E44), gMapInspectNoText);
#else
    gMapInspectNoTextCount = LoadTextSlots(gUnk_08159E18, gMapInspectNoText);
#endif

#ifdef VERSION_JP
    gMapInspectNoticeTextLength[0] = GetTextLength(gUnk_0814FBB0);
    gMapInspectNoticeText[0] = EwramAlloc(gMapInspectNoticeTextLength[0] * sizeof(TextSlot));
    InitTextSlots(gMapInspectNoticeText[0], gMapInspectNoticeTextLength[0]);
    gMapInspectNoticeTextCount[0] = LoadTextSlots(gUnk_0814FBB0, gMapInspectNoticeText[0]);

    gMapInspectNoticeTextLength[1] = GetTextLength(gUnk_0814FBBC);
    gMapInspectNoticeText[1] = EwramAlloc(gMapInspectNoticeTextLength[1] * sizeof(TextSlot));
    InitTextSlots(gMapInspectNoticeText[1], gMapInspectNoticeTextLength[1]);
    gMapInspectNoticeTextCount[1] = LoadTextSlots(gUnk_0814FBBC, gMapInspectNoticeText[1]);
#else
#ifdef VERSION_EU
    gMapInspectNoticeTextLength[0] = GetTextLength(eu_0805E924(&gUnkEu_08895CF8));
#else
    gMapInspectNoticeTextLength[0] = GetTextLength(gUnk_0815C136);
#endif
    gMapInspectNoticeText[0] = EwramAlloc(gMapInspectNoticeTextLength[0] * sizeof(TextSlot));
    InitTextSlots(gMapInspectNoticeText[0], gMapInspectNoticeTextLength[0]);
#ifdef VERSION_EU
    gMapInspectNoticeTextCount[0] = LoadTextSlots(eu_0805E924(&gUnkEu_08895CF8), gMapInspectNoticeText[0]);
#else
    gMapInspectNoticeTextCount[0] = LoadTextSlots(gUnk_0815C136, gMapInspectNoticeText[0]);
#endif
#endif

    MapInspectLoadGrid();
    MapInspectLoadSelectedCard();
    EnableBg(0);
    EnableBg(1);
    DisableBg(2);
    DisableBg(3);
}

void mode_mapinspect_1(void) {
    UpdatePlayTime();

    switch (gMapInspectState) {
    case 0:
        ApproachValue(&gMapInspectBarY[0], 0, gMapInspectSteps);
        ApproachValue(&gMapInspectBarY[1], 0x9800, gMapInspectSteps);
        gMapInspectSteps--;
        if (gMapInspectSteps <= 0) {
            gMapInspectSteps = 16;
            gMapInspectState = 1;
        }
        break;
    case 1:
        ApproachValue(&gMapInspectBarX, 0, gMapInspectSteps);
        gMapInspectSteps--;
        if (gMapInspectSteps <= 0) {
            LoadBgMap(0, gUnk_09A3489C, 0x500);
            gMapInspectState = 2;
        }
        break;
    case 2:
        switch (gMapInspectMenuState) {
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
        ApproachValue(&gMapInspectBarX, -0x8000, gMapInspectSteps);
        gMapInspectSteps--;
        if (gMapInspectSteps <= 0) {
            gMapInspectSteps = 16;
            gMapInspectState = 4;
        }
        break;
    case 4:
        ApproachValue(&gMapInspectBarY[0], -0x800, gMapInspectSteps);
        ApproachValue(&gMapInspectBarY[1], 0xA800, gMapInspectSteps);
        gMapInspectSteps--;
        if (gMapInspectSteps <= 0) {
            FadeStartOut(0, 16);
            gMapInspectState = 5;
        }
        break;
    case 5:
        if (!FadeIsActive()) {
            ReturnToMap(gMapInspectReturnToMenu);
        }
        break;
    }

    MapInspectDraw();
}

void mode_mapinspect_2(void) {
    s32 i;
    s32 j;

    ReleaseObjPalette(gUnk_02035E4C);
    ReleaseObjTiles(gUnk_02035E50);
    ReleaseObjTiles(gMapInspectHighlightTiles);
    ReleaseObjPalette(gUnk_02035E70);
    ReleaseObjTiles(gUnk_02035F54);
    ReleaseObjTiles(gUnk_02035F70);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            if (gMapInspectGridPalettes[i][j] != NULL) {
                ReleaseObjPalette(gMapInspectGridPalettes[i][j]);
            }

            if (gMapInspectGridTiles[i][j] != NULL) {
                ReleaseObjTiles(gMapInspectGridTiles[i][j]);
            }
        }
    }

    if (gMapInspectCardPalette != NULL) {
        ReleaseObjPalette(gMapInspectCardPalette);
    }

    if (gMapInspectCardTiles != NULL) {
        ReleaseObjTiles(gMapInspectCardTiles);
    }

    if (gUnk_02035F48 != NULL) {
        ReleaseObjPalette(gUnk_02035F48);
    }

    if (gUnk_02035F4C != NULL) {
        ReleaseObjTiles(gUnk_02035F4C);
    }

    if (gMapInspectCategoryPalette != NULL) {
        ReleaseObjPalette(gMapInspectCategoryPalette);
    }

    FreeTextSlots(gMapInspectNameText, 0x24);
    EwramFree(gMapInspectNameText);
    FreeTextSlots(gMapInspectDescText, 0x5A);
    EwramFree(gMapInspectDescText);
    FreeTextSlots(gMapInspectConfirmText, gMapInspectConfirmTextLength);
    EwramFree(gMapInspectConfirmText);
    FreeTextSlots(gMapInspectYesText, gMapInspectYesTextLength);
    EwramFree(gMapInspectYesText);
    FreeTextSlots(gMapInspectNoText, gMapInspectNoTextLength);
    EwramFree(gMapInspectNoText);

#ifdef VERSION_JP
    for (i = 0; i < 2; i++) {
#else
    for (i = 0; i < 1; i++) {
#endif
        FreeTextSlots(gMapInspectNoticeText[i], gMapInspectNoticeTextLength[i]);
        EwramFree(gMapInspectNoticeText[i]);
    }

    EwramFree(gMapCardInventoryEntries);
}

Mode gModeMapinspect = {
    "mode_mapinspect",
    (ModeInitFunc)mode_mapinspect_0,
    mode_mapinspect_1,
    mode_mapinspect_2,
};
