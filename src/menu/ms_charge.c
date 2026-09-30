#include "localized_resource_assets.h"
#include "system_state.h"
#include "ms_charge_api.h"
#include "display.h"
#include "text.h"
#include "monsgage.h"
#include "ms_charge.h"
#include "gba/keys.h"
#include "sprites_card.h"
#include "sprites_evt.h"
#include "sprites_moogle_shop.h"
#include "sprites_card_pictures.h"
#include "gba/io_reg.h"
#include "mode_ms_top_api.h"
#include "malloc.h"
#include "fade.h"
#include "mode_test_api.h"
#include "songs.h"
#include "jiminy_data.h"
#include "common_text.h"

#ifdef VERSION_EU
#define LANGSTR(x) (((void**)(x))[gLanguage])
#else
#define LANGSTR(x) (x)
#endif

#ifdef VERSION_EU
static void* sUnkEu_09F84FA8[5] = {
    gUnkEu_09A94E20,
    gUnkEu_09A95320,
    gUnkEu_09A96220,
    gUnkEu_09A95D20,
    gUnkEu_09A95820,
};

static void* sUnkEu_09F84FBC[5] = {
    gUnkEu_09A96720,
    gUnkEu_09A96820,
    gUnkEu_09A96920,
    gUnkEu_09A96A20,
    gUnkEu_09A96920,
};

static void* sUnkEu_09F84FD0[5] = {
    gUnk_09A3B85C,
    gUnkEu_09A97A20,
    gUnkEu_09A98920,
    gUnkEu_09A98420,
    gUnkEu_09A97F20,
};

static void* sUnkEu_09F84FE4[5] = {
    gUnk_09A3BD5C,
    gUnkEu_09A98E20,
    gUnkEu_09A99D20,
    gUnkEu_09A99820,
    gUnkEu_09A99320,
};
#endif

static MsCard* gMsCards;
static s16 sMsChargeState;
static s16 sMsChargeMenuState;
static s16 sMsChargeTab;
static s16 sMsChargeCategoryStart[4];
static s16 sMsChargeCategoryEntryCount[4];
static s16 sMsChargeCategoryCardCount[4];
static s16 sMsChargeDeckCardCount;
static s16 sMsChargeCardTotal;
static u16 sMsChargeCollectionCount;
static struct ObjTiles* sMsChargeScrollbarTiles;
static struct ObjPalette* gUnk_02035C44;
static struct ObjTiles* gUnk_02035C48;
static AnimState gUnk_02035C50;
static AnimState sMsChargeHighlightAnim;
static struct ObjPalette* sMsChargeMooglePalette;
static struct ObjTiles* sMsChargeMoogleTiles;
static AnimState sMsChargeCursorAnim;
static AnimState sMsChargeMoogleAnim;
static u8 sMsChargeBobPhase;
static s16 sMsChargeMoogleAnimId;
static s16 sMsChargeMoogleAnimTimer;
static struct ObjPalette* sMsChargeConfirmCursorPalette;
static struct ObjTiles* sMsChargeConfirmCursorTiles;
static AnimState sMsChargeConfirmCursorAnim;
static s16 sMsChargeGridCol;
static s16 sMsChargeGridRow;
static s16 sMsChargeGridScroll;
static void* sMsChargeGridPalettes[4][3];
static void* sMsChargeGridTiles[4][3];
static void* sMsChargeGridSprites[4][3];
static u8 sMsChargeGridPremium[4][3];
static struct ObjPalette* sMsChargeCardPalette;
static struct ObjTiles* sMsChargeCardTiles;
static void* sMsChargeCardSprite;
static struct ObjPalette* gUnk_02035D90;
static struct ObjTiles* gUnk_02035D94;
static void* gUnk_02035D98;
static struct ObjTiles* sMsChargePremiumTiles;
static AnimState sMsChargePremiumAnim;
static struct ObjTiles* sMsChargeGridPremiumTiles;
static u32 gUnk_02035DBC;
static AnimState sMsChargeGridPremiumAnim;
static u8 sMsChargeCardPremium;
static TextSlot* sMsChargeNameText;
static u8 sMsChargeNameTextCount;
static TextSlot* sMsChargeDescText;
static u8 sMsChargeDescTextCount;
static TextSlot* sMsChargeConfirmText;
static u8 sMsChargeConfirmTextCount;
static u16 sMsChargeConfirmTextLength;
static TextSlot* sMsChargeNoticeText;
static u8 sMsChargeNoticeTextCount;
static u16 sMsChargeNoticeTextLength;
static TextSlot* sMsChargeYesText;
static u8 sMsChargeYesTextCount;
static u16 sMsChargeYesTextLength;
static TextSlot* sMsChargeNoText;
static u8 sMsChargeNoTextCount;
static u16 sMsChargeNoTextLength;
static s16 sMsChargeValueCol;
static s16 sMsChargeValueRow;
static s16 sMsChargeConfirmCursor;
static u32 sMsChargeConfirmCursorX;
static s32 sMsChargeCursorX;
static s32 sMsChargeCursorY;
static u8 sMsChargeBackToTop;

s16 GetMsChargeTabStart(s16 a) {
    s16 v;

    if (a <= 3) {
        v = sMsChargeCategoryStart[a];
    } else {
        v = 0;
    }
    return v;
}

s16 GetMsChargeTabCount(s16 a) {
    s16 v;
    s16 i;

    if (a <= 3) {
        v = sMsChargeCategoryEntryCount[a];
    } else {
        v = 0;

        for (i = 0; i < 4; i++) {
            v += sMsChargeCategoryEntryCount[i];
        }
    }
    return v;
}

s16 GetMsChargeSelectedIndex(void) {
    return GetMsChargeTabStart(sMsChargeTab) + (sMsChargeGridScroll + sMsChargeGridRow) * 3 + sMsChargeGridCol;
}

MsCard* GetMsChargeSelectedCard(void) {
    return gMsCards + GetMsChargeSelectedIndex();
}

void MsChargeSelectFirstValue(void) {
    MsCard* card;
    s16 i;

    card = GetMsChargeSelectedCard();
    if (card->kind != 0x8F) {
        for (i = 0; i < 10; i++) {
            if (card->values[i][0] > 0) {
                break;
            }
        }
        sMsChargeValueCol = i / 5;
        sMsChargeValueRow = i % 5;
    } else {
        sMsChargeValueCol = 0;
        sMsChargeValueRow = 0;
    }
}

void MsChargeLoadGrid(void) {
    s16 i;
    s16 k;
    s16 idx;
    s16 a;
    s16 limit;
    s32 defIdx;

    a = GetMsChargeTabStart(sMsChargeTab);
    limit = GetMsChargeTabCount(sMsChargeTab);
    idx = sMsChargeGridScroll * 3;

    for (i = 0; i < 4; i++) {
        for (k = 0; k < 3; k++) {
            if (sMsChargeGridPalettes[i][k] != NULL) {
                ReleaseObjPalette(sMsChargeGridPalettes[i][k]);
            }

            if (sMsChargeGridTiles[i][k] != NULL) {
                ReleaseObjTiles(sMsChargeGridTiles[i][k]);
            }

            if (idx < limit) {
                defIdx = gMsCards[a + idx].cardId;
                sMsChargeGridPalettes[i][k] = LoadObjPalette(gCardDefs[defIdx].palette2, 0x20);
                sMsChargeGridTiles[i][k] = LoadObjTiles(gCardDefs[defIdx].tiles2, 0x100);
                sMsChargeGridSprites[i][k] = gCardDefs[defIdx].gfx2;
                sMsChargeGridPremium[i][k] = gMsCards[a + idx].premium;
            } else {
                sMsChargeGridPalettes[i][k] = 0;
                sMsChargeGridTiles[i][k] = 0;
                sMsChargeGridSprites[i][k] = 0;
                sMsChargeGridPremium[i][k] = 0;
            }
            idx++;
        }
    }
}

void MsChargeLoadSelectedCard(void) {
    MsCard* card;
    u8* p;
    u8* q;
    s32 defIdx;

    card = GetMsChargeSelectedCard();

    if (sMsChargeCardPalette != NULL) {
        ReleaseObjPalette(sMsChargeCardPalette);
    }

    if (sMsChargeCardTiles != NULL) {
        ReleaseObjTiles(sMsChargeCardTiles);
    }

    if (gUnk_02035D94 != NULL) {
        ReleaseObjTiles(gUnk_02035D94);
    }

    if (card->kind != 0x8F && GetMsChargeTabCount(sMsChargeTab) > 0) {
        defIdx = card->cardId;
        sMsChargeCardPalette = LoadObjPalette(gCardDefs[defIdx].palette, 0x20);
        sMsChargeCardTiles = LoadObjTiles(gCardDefs[defIdx].tiles, 0x200);
        sMsChargeCardSprite = gCardDefs[defIdx].gfx;
        gUnk_02035D94 = LoadObjTiles(gCardBacks[card->category].tiles, 0x300);
        gUnk_02035D98 = gCardBacks[card->category].gfx;
        sMsChargeCardPremium = card->premium;
        p = &sMsChargeNameTextCount;
#ifdef VERSION_EU
        *p = LoadTextSlots(eu_0805E924(gCardDefs[defIdx].name), sMsChargeNameText);
#else
        *p = LoadTextSlots(gCardDefs[defIdx].name, sMsChargeNameText);
#endif
        q = &sMsChargeDescTextCount;
        *q = LoadTextSlots((void*)LANGSTR(gCardKindDescriptions[card->kind]), sMsChargeDescText);
        LoadObjPaletteBank(gUnk_02035C44->index, gUnk_09A3DE7C + card->category * 0x20);
    } else {
        sMsChargeCardPalette = 0;
        sMsChargeCardTiles = 0;
        sMsChargeCardSprite = 0;
        gUnk_02035D94 = 0;
        gUnk_02035D98 = 0;
        sMsChargeCardPremium = 0;
        sMsChargeNameTextCount = 0;
        sMsChargeDescTextCount = 0;
    }
}

s16 GetMsChargeValueIndex(s16 a, s16 b) {
    return b + a * 5;
}

s16 GetMsChargeSelectedValue(void) {
    return GetMsChargeValueIndex(sMsChargeValueCol, sMsChargeValueRow);
}

u16 GetMsChargeCardPoints(u16 index) {
    MsCard* card;
    u16 id;

    card = &gMsCards[index];
    if (card->kind != 0x8F) {
        id = card->values[GetMsChargeSelectedValue()][1];
        return GetCardMooglePointValue(card->premium != 0 ? id | 0x8000 : id);
    }
    return 0;
}

void MsChargeDrawPoints(void) {
    u32 v;

    v = GetMooglePoints();
    LoadDecimalDigitTiles(v, gUnk_09A1DB9C, (u8*)GetBgCharBase(0) + 0x20, 0x20, 5);

    if (sMsChargeMenuState >= 2 && sMsChargeMenuState <= 3) {
        v = GetMsChargeCardPoints(GetMsChargeSelectedIndex());
    } else {
        v = 0;
    }
    LoadDecimalDigitTiles(v, gUnk_09A1DCDC, (u8*)GetBgCharBase(0) + 0x180, 0x20, 2);
}

void MsChargeDrawCardCounts(void) {
    LoadDecimalDigitTiles(sMsChargeDeckCardCount, gUnk_09A1DB9C, (u8*)GetBgCharBase(0) + 0xC0, 0x20, 3);
    LoadDecimalDigitTiles(sMsChargeCollectionCount, gUnk_09A1DB9C, (u8*)GetBgCharBase(0) + 0x120, 0x20, 3);
}

void MsChargeDrawCategoryCounts(void) {
    s16 i;
    s32 v;

    for (i = 0; i < 4; i++) {
        v = sMsChargeCategoryCardCount[i];
        if (v != 0) {
            LoadDecimalDigitTiles(v, gUnk_09A1DE3C, (u8*)GetBgCharBase(0) + (i * 3 * 0x20 + 0x1C0), 0x20, 3);
        } else {
            LoadDecimalDigitTiles(0, gUnk_09A1DE1C, (u8*)GetBgCharBase(0) + (i * 3 * 0x20 + 0x1C0), 0x20, 3);
        }
    }
}

void MsChargeDrawValueCounts(void) {
    MsCard* card;
    s16 i;
    s32 v;

    card = GetMsChargeSelectedCard();

    if (GetMsChargeTabCount(sMsChargeTab) > 0) {
        LoadPalette(gUnk_09A3DD7C + card->category * 0x20, (void*)0x050000E0, 0x0C);
    }

    if ((s16)sMsChargeMenuState == 1) {
        for (i = 0; i < 10; i++) {
            LoadDecimalDigitTiles(0, gUnk_09A1DF7C, (u8*)GetBgCharBase(0) + (i * 0x40 + 0x340), 0x20, 2);
            LoadPalette(gUnk_09A3DE08, (void*)(0x050000EC + i * 2), 2);
        }
    } else if (card->category == 3) {
        if (GetMsChargeTabCount(sMsChargeTab) > 0) {
#ifdef VERSION_EU
            LoadBgMap(1, sUnkEu_09F84FE4[gLanguage], 0x500);
#else
            LoadBgMap(1, gUnk_09A3BD5C, 0x500);
#endif
        }

        for (i = 0; i < 10; i++) {
            v = card->values[i][0];
            if (v != 0 && GetMsChargeTabCount(sMsChargeTab) > 0) {
                LoadDecimalDigitTiles(v, gUnk_09A1DF9C, (u8*)GetBgCharBase(0) + 0x340, 0x20, 2);
                LoadPalette(gUnk_09A3DD88, (void*)0x050000EC, 2);
                break;
            }
        }

        if (i > 9) {
            LoadDecimalDigitTiles(0, gUnk_09A1DF7C, (u8*)GetBgCharBase(0) + 0x340, 0x20, 2);
            LoadPalette(gUnk_09A3DE08, (void*)0x050000EC, 2);
        }
    } else {
        if (GetMsChargeTabCount(sMsChargeTab) > 0) {
#ifdef VERSION_EU
            LoadBgMap(1, sUnkEu_09F84FD0[gLanguage], 0x500);
#else
            LoadBgMap(1, gUnk_09A3B85C, 0x500);
#endif
        }

        for (i = 0; i < 10; i++) {
            v = card->values[i][0];
            if (v != 0 && GetMsChargeTabCount(sMsChargeTab) > 0) {
                LoadDecimalDigitTiles(v, gUnk_09A1DF9C, (u8*)GetBgCharBase(0) + (i * 0x40 + 0x340), 0x20, 2);
                LoadPalette(gUnk_09A3DD88, (void*)(0x050000EC + i * 2), 2);
            } else {
                LoadDecimalDigitTiles(0, gUnk_09A1DF7C, (u8*)GetBgCharBase(0) + (i * 0x40 + 0x340), 0x20, 2);
                LoadPalette(gUnk_09A3DE08, (void*)(0x050000EC + i * 2), 2);
            }
        }
    }
}

void MsChargeDrawTab(s16 a) {
    s16 t;
    void* base;

    t = 4 - a;
    base = GetBgScreenBase(0);
#ifdef VERSION_EU
    RequestTilemapRectCopy(sUnkEu_09F84FBC[gLanguage], base, t % 3 * 10, t / 3 * 2, 20, 2, 10, 2);
#else
    RequestTilemapRectCopy(gUnk_09A3B75C, base, t % 3 * 10, t / 3 * 2, 20, 2, 10, 2);
#endif
}

void MsChargeSellCard(void) {
    MsCard* card;
    u16 id;
    s16 i;

    card = GetMsChargeSelectedCard();

    if (card->values[GetMsChargeSelectedValue()][0] > 0) {
        id = card->values[GetMsChargeSelectedValue()][1];

        if (card->premium != 0) {
            id |= 0x8000;
        }

        for (i = 0; i < gCardCount; i++) {
            if (gCardCollection[i] == id) {
                AddMooglePoints(GetMsChargeCardPoints(GetMsChargeSelectedIndex()));
                sMsChargeCategoryCardCount[card->category]--;
                sMsChargeCardTotal--;
                sMsChargeCollectionCount--;
                card->values[GetMsChargeSelectedValue()][0]--;
                ClearCardCollectionSlot(&gCardCollection[i]);
                break;
            }
        }
    }
}

u8 MsCardIsEmpty(MsCard* card) {
    s16 i;

    for (i = 0; i < 10; i++) {
        if (card->values[i][0] > 0) {
            break;
        }
    }

    if (i > 9) {
        return 1;
    }
    return 0;
}

u8 MsCardSelectedValueIsEmpty(MsCard* card) {
    if (card->values[GetMsChargeSelectedValue()][0] == 0) {
        return 1;
    }
    return 0;
}

void MsChargeSelectNextValue(MsCard* card) {
    s16 k;
    s16 n;

    k = GetMsChargeSelectedValue();

    for (n = 0; n < 10; n++) {
        if (card->values[k][0] > 0) {
            break;
        }
        k++;
        if (k > 9) {
            k = 0;
        }
    }
    sMsChargeValueCol = k / 5;
    sMsChargeValueRow = k % 5;
}

void MsChargeRemoveCard(MsCard* card) {
    vu32* dma;
    MsCard* last;
    u16* p;
    u16 zero;
    u8 slot;
    s16 j;

    slot = gCardDefs[card->cardId].category;
    dma = (vu32*)REG_ADDR_DMA3;
    dma[0] = (u32)(card + 1);
    dma[1] = (u32)card;
    dma[2] = ((285 - GetMsChargeSelectedIndex()) * 26) | (DMA_ENABLE << 16);
    dma[2];
    p = &zero;
    *p = 0;
    dma[0] = (u32)p;
    last = &gMsCards[285];
    dma[1] = (u32)last;
    dma[2] = ((DMA_ENABLE | DMA_SRC_FIXED) << 16) | 0x1A;
    dma[2];
    last->kind = 0x8F;

    for (j = slot + 1; j <= 3; j++) {
        sMsChargeCategoryStart[j]--;
    }
    sMsChargeCategoryEntryCount[slot]--;

    if (GetMsChargeSelectedIndex() >= GetMsChargeTabCount(sMsChargeTab)) {
        sMsChargeGridCol--;
        if (sMsChargeGridCol < 0) {
            sMsChargeGridCol = 2;
            sMsChargeGridRow--;
            if (sMsChargeGridRow < 0) {
                sMsChargeGridRow = 0;
                sMsChargeGridScroll--;
                if (sMsChargeGridScroll < 0) {
                    sMsChargeGridCol = 0;
                    sMsChargeGridScroll = 0;
                }
            }
        }
    }
    sMsChargeValueCol = 0;
    sMsChargeValueRow = 0;
}

s32 FindMsCard(u16 id, u8 flag, s16 count) {
    s16 i;

    for (i = 0; i < count; i++) {
        if (gMsCards[i].kind == id && gMsCards[i].premium == flag) {
            return i;
        }
    }
    return -1;
}

void MsChargeBuildCardList(void) {
    MsCard tmp;
    vu32* dma;
    u16* p;
    s16* q;
    s16 a;
    u16 zero;
    s16 n;
    u16 id;
    s16 i;
    u16 raw;
    u16 kind;
    u16 flags;
    u32 sortKey;
    u8 prem;
    s16 j;
    s16 idx;

    p = &zero;
    *p = 0;
    dma = (vu32*)REG_ADDR_DMA3;
    dma[0] = (u32)p;
    dma[1] = (u32)gMsCards;
    dma[2] = ((DMA_ENABLE | DMA_SRC_FIXED) << 16) | 0x1D0C;
    dma[2];

    for (n = 0; n <= 285; n++) {
        gMsCards[n].kind = 0x8F;
        gMsCards[n].cardId = 0x3B6;
        gMsCards[n].premium = 0;
    }
    a = CountCollectionCards();
    sMsChargeCollectionCount = a;
    q = &sMsChargeDeckCardCount;
    *q = CountCardsInDecks();

    for (j = 0; j < 4; j++) {
        sMsChargeCategoryStart[j] = 0;
        sMsChargeCategoryCardCount[j] = 0;
        sMsChargeCategoryEntryCount[j] = 0;
    }
    sMsChargeCardTotal = 0;
    n = 0;

    for (i = 0; i < gCardCount; i++) {
        raw = gCardCollection[i];
        id = raw & CARD_ID_MASK;
        if (raw != CARD_ID_MASK && (raw & 0x7000) == 0 && id <= 0x21C) {
            j = gCardDefs[id].category;
            kind = gCardDefs[id].kind;
            flags = raw & 0x8000;
            prem = flags != 0;
            sMsChargeCategoryCardCount[j]++;
            sMsChargeCardTotal++;
            if ((idx = FindMsCard(kind, prem, n)) >= 0) {
                gMsCards[idx].values[raw = gCardDefs[id].value][0]++;
                gMsCards[idx].values[raw][1] = id;
            } else {
                gMsCards[n].kind = kind;
                gMsCards[n].cardId = gCardDefs[id].unk_28;
                gMsCards[n].category = j;
                raw = gCardDefs[id].value;
                gMsCards[n].values[raw][0]++;
                gMsCards[n].values[raw][1] = id;
                gMsCards[n].premium = prem;
                sortKey = 0x01000000;

                if (prem != 0) {
                    sortKey = 0x03000000;
                }
                gMsCards[n].sortKey = (sortKey << (gMsCards[n].category * 2)) | gMsCards[n].cardId;
                sMsChargeCategoryEntryCount[j]++;
                n++;
            }
        }
    }

    for (j = 1; j < 4; j++) {
        sMsChargeCategoryStart[j] = sMsChargeCategoryStart[j - 1] + sMsChargeCategoryEntryCount[j - 1];
    }

    for (i = 1; i < n; i++) {
        tmp = gMsCards[i];

        for (j = i - 1; j >= 0; j--) {
            if (gMsCards[j].sortKey > tmp.sortKey) {
                gMsCards[j + 1] = gMsCards[j];
            } else {
                break;
            }
        }
        gMsCards[j + 1] = tmp;
    }
}

s32 MsChargeReadMenuKeys(void) {
    s32 keys;

    keys = GetKeysPressed() & (A_BUTTON | B_BUTTON | SELECT_BUTTON | START_BUTTON);
    return keys | (GetKeysRepeat() & (DPAD_ANY | L_BUTTON | R_BUTTON));
}

void MsChargeHandleGridInput(void) {
    s16 oldCE0;
    s16 oldCE2;
    s16 oldCE4;
    u16 keys;

    oldCE0 = sMsChargeGridCol;
    oldCE2 = sMsChargeGridRow;
    oldCE4 = sMsChargeGridScroll;
    keys = MsChargeReadMenuKeys();
    if (keys & 1) {
        MsChargeSelectFirstValue();
        m4aSongNumStart(SONG_SYS_KETTEI);
        AnimStart(&sMsChargeHighlightAnim, 0, 1);
        sMsChargeMoogleAnimId = 1;
        sMsChargeMenuState = 2;
        MsChargeDrawPoints();
    } else if (keys & 2) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        sMsChargeBackToTop = 1;
        FadeStartOut(0, 0x10);
        sMsChargeState = 2;
    } else if (keys & 8) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        sMsChargeBackToTop = 0;
        FadeStartOut(0, 0x10);
        sMsChargeState = 2;
    } else if (keys & 4) {
        sMsChargeGridCol = 0;
        sMsChargeGridRow = 0;
        sMsChargeGridScroll = 0;
        sMsChargeMoogleAnimId = 0;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
        sMsChargeMenuState = 1;
        MsChargeDrawValueCounts();
    } else if (keys & 0x40) {
        if (sMsChargeGridRow > 0) {
            sMsChargeGridRow--;
        } else if (sMsChargeGridScroll > 0) {
            sMsChargeGridScroll--;
        } else {
            sMsChargeMoogleAnimId = 0;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            sMsChargeMenuState = 1;
            MsChargeDrawValueCounts();
        }
    } else if (keys & 0x80) {
        if ((sMsChargeGridScroll + sMsChargeGridRow + 1) * 3 + sMsChargeGridCol < GetMsChargeTabCount(sMsChargeTab)) {
            if (sMsChargeGridRow <= 2) {
                sMsChargeGridRow++;
            } else {
                sMsChargeGridScroll++;
            }
        } else if (sMsChargeGridRow == 3) {
            if ((sMsChargeGridScroll + sMsChargeGridRow + 1) * 3 < GetMsChargeTabCount(sMsChargeTab)) {
                sMsChargeGridCol = (GetMsChargeTabCount(sMsChargeTab) - 1) % 3;
                sMsChargeGridScroll++;
            }
        }
    } else if (keys & 0x20) {
        if (sMsChargeGridCol > 0) {
            sMsChargeGridCol--;
        }
    } else if (keys & 0x10) {
        if ((sMsChargeGridScroll + sMsChargeGridRow) * 3 + sMsChargeGridCol + 1 < GetMsChargeTabCount(sMsChargeTab)) {
            if (sMsChargeGridCol <= 1) {
                sMsChargeGridCol++;
            }
        }
    }

    if (sMsChargeGridCol != oldCE0 || sMsChargeGridRow != oldCE2 || sMsChargeGridScroll != oldCE4) {
        MsChargeSelectFirstValue();
        MsChargeDrawValueCounts();
        MsChargeDrawPoints();
        MsChargeLoadSelectedCard();
        m4aSongNumStart(SONG_SYS_CLICKI04B);

        if (sMsChargeGridScroll != oldCE4) {
            MsChargeLoadGrid();
        }
    }
}

void MsChargeHandleTabInput(void) {
    s16 old;
    u16 keys;

    old = sMsChargeTab;
    keys = MsChargeReadMenuKeys();
    if ((keys & 1) == 0) {
        if (keys & 8) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            sMsChargeBackToTop = 0;
            FadeStartOut(0, 0x10);
            sMsChargeState = 2;
        } else if (keys & 0x82) {
            if (GetMsChargeTabCount(sMsChargeTab) > 0) {
                sMsChargeGridCol = 0;
                sMsChargeGridRow = 0;
                sMsChargeGridScroll = 0;
                AnimStart(&sMsChargeHighlightAnim, 2, 1);
                sMsChargeMoogleAnimId = 0;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
                sMsChargeMenuState = 0;
                MsChargeSelectFirstValue();
                MsChargeDrawValueCounts();
                MsChargeLoadSelectedCard();
            } else if (keys & 2) {
                m4aSongNumStart(SONG_SYS_CLOSE);
                sMsChargeBackToTop = 1;
                FadeStartOut(0, 0x10);
                sMsChargeState = 2;
            } else if (keys & 0x80) {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        } else if (keys & 0x20) {
            if (sMsChargeTab > 0) {
                sMsChargeTab--;
            }
        } else if (keys & 0x10) {
            if (sMsChargeTab <= 3) {
                sMsChargeTab++;
            }
        }
    }

    if (sMsChargeTab != old) {
        MsChargeDrawTab(sMsChargeTab);
        MsChargeLoadGrid();
        m4aSongNumStart(SONG_SYS_CLICK);
    }
}

s32 MsChargeSelectValueInColumn(MsCard* card, u16 col) {
    s16 base;
    s16 i;
    s32 r;
    s32 found;

    found = 0;
    base = sMsChargeValueRow;

    for (i = 0; i <= 4; i++) {
        r = base - i;
        if (r >= 0 && card->values[GetMsChargeValueIndex(col, r)][0] > 0) {
            sMsChargeValueCol = col;
            sMsChargeValueRow = r;
            found = 1;
            break;
        }
        r = base + i;
        if (r <= 4 && card->values[GetMsChargeValueIndex(col, r)][0] > 0) {
            sMsChargeValueCol = col;
            sMsChargeValueRow = r;
            found = 1;
            break;
        }
    }
    return found;
}

void MsChargeHandleValueInput(void) {
    MsCard* card;
    s16 oldCol;
    s16 oldRow;
    u16 keys;
    s16 i;

    card = GetMsChargeSelectedCard();
    oldCol = sMsChargeValueCol;
    oldRow = sMsChargeValueRow;
    keys = MsChargeReadMenuKeys();
    if (keys & 1) {
        if (GetMooglePoints() + GetMsChargeCardPoints(GetMsChargeSelectedIndex()) > 99999) {
            m4aSongNumStart(SONG_SYS_BEEP);
        } else if (sMsChargeCollectionCount <= 1) {
            EnableBg(2);
            m4aSongNumStart(SONG_SYS_CANSEL);
            sMsChargeMenuState = 4;
        } else {
            sMsChargeConfirmCursor = 0;
            sMsChargeConfirmCursorX = 0x4800;
            AnimStart(&sMsChargeConfirmCursorAnim, 0, 1);
            EnableBg(2);
            m4aSongNumStart(SONG_SYS_CANSEL);
            sMsChargeMenuState = 3;
        }
    } else if (keys & 2) {
        AnimStart(&sMsChargeHighlightAnim, 2, 1);
        sMsChargeMoogleAnimId = 0;
        m4aSongNumStart(SONG_SYS_CLOSE);
        sMsChargeMenuState = 0;
        MsChargeDrawPoints();
    } else if (keys & 8) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        sMsChargeBackToTop = 0;
        FadeStartOut(0, 0x10);
        sMsChargeState = 2;
    } else if (keys & 0x20) {
        MsChargeSelectValueInColumn(card, 0);
    } else if (keys & 0x10) {
        MsChargeSelectValueInColumn(card, 1);
    } else if (keys & 0x40) {
        for (i = 0; i <= 4; i++) {
            sMsChargeValueRow--;
            if (sMsChargeValueRow < 0) {
                sMsChargeValueRow = 4;
            }

            if (card->values[GetMsChargeSelectedValue()][0] > 0) {
                break;
            }
        }
    } else if (keys & 0x80) {
        for (i = 0; i <= 4; i++) {
            sMsChargeValueRow++;
            if (sMsChargeValueRow > 4) {
                sMsChargeValueRow = 0;
            }

            if (card->values[GetMsChargeSelectedValue()][0] > 0) {
                break;
            }
        }
    }

    if (card->category == 3) {
        sMsChargeValueCol = oldCol;
        sMsChargeValueRow = oldRow;
    }

    if (sMsChargeValueCol != oldCol || sMsChargeValueRow != oldRow) {
        MsChargeDrawPoints();
        m4aSongNumStart(SONG_SYS_CLICK);
    }
}

void MsChargeHandleConfirmInput(void) {
    MsCard* card;
    s16 old;
    u16 keys;

    card = GetMsChargeSelectedCard();
    old = sMsChargeConfirmCursor;
    keys = MsChargeReadMenuKeys();
    if (keys & 1) {
        DisableBg(2);

        if (sMsChargeConfirmCursor == 0) {
            sMsChargeMoogleAnimTimer = 180;
            MsChargeSellCard();
            m4aSongNumStart(SONG_SYS_KAIHUKU);

            if (MsCardIsEmpty(card)) {
                MsChargeRemoveCard(card);
                MsChargeLoadGrid();
                MsChargeLoadSelectedCard();

                if (GetMsChargeTabCount(sMsChargeTab) > 0) {
                    AnimStart(&sMsChargeHighlightAnim, 2, 1);
                    sMsChargeMoogleAnimId = 0;
                    sMsChargeMenuState = 0;
                } else {
                    sMsChargeMoogleAnimId = 0;
                    sMsChargeMenuState = 1;
                }
            } else {
                if (MsCardSelectedValueIsEmpty(card)) {
                    MsChargeSelectNextValue(card);
                }
                AnimStart(&sMsChargeHighlightAnim, 0, 1);
                sMsChargeMoogleAnimId = 1;
                sMsChargeMenuState = 2;
            }
            MsChargeDrawPoints();
            MsChargeDrawValueCounts();
            MsChargeDrawCardCounts();
            MsChargeDrawCategoryCounts();
        } else {
            m4aSongNumStart(SONG_SYS_CLOSE);
            AnimStart(&sMsChargeHighlightAnim, 0, 1);
            sMsChargeMoogleAnimId = 1;
            sMsChargeMenuState = 2;
        }
    } else if (keys & 2) {
        DisableBg(2);
        m4aSongNumStart(SONG_SYS_CLOSE);
        AnimStart(&sMsChargeHighlightAnim, 0, 1);
        sMsChargeMoogleAnimId = 1;
        sMsChargeMenuState = 2;
    } else if (keys & 8) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        sMsChargeBackToTop = 0;
        FadeStartOut(0, 0x10);
        sMsChargeState = 2;
    } else if (keys & 0x20) {
        sMsChargeConfirmCursor = 0;
    } else if (keys & 0x10) {
        sMsChargeConfirmCursor = 1;
    }

    if (sMsChargeConfirmCursor != old) {
        m4aSongNumStart(SONG_SYS_CLICK);
    }
}

void MsChargeHandleNoticeInput(void) {
    u16 keys;

    keys = MsChargeReadMenuKeys();
    if (keys & 3) {
        DisableBg(2);
        m4aSongNumStart(SONG_SYS_CLOSE);
        sMsChargeMenuState = 2;
    } else if (keys & 8) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        sMsChargeBackToTop = 0;
        FadeStartOut(0, 0x10);
        sMsChargeState = 2;
    }
}

void MsChargeDraw(void) {
    MsCard* card;
    void* anim;
    s32 sine;
    s16 t;
    s16 v;
    s16 col;
    s16 row;
    s32 i;
    s32 j;

    if ((s16)sMsChargeMenuState != 1) {
        DrawSprite(16, 60, AnimUpdate(&gUnk_02035C50), gUnk_02035C48, gUnk_02035C44, 0, 0x800, 0x7D0);
    }
    t = (GetMsChargeTabCount(sMsChargeTab) + 2) / 3 - 4;
    if (sMsChargeGridScroll <= t) {
        v = 84 * sMsChargeGridScroll / t;
    } else {
        v = 0;
    }
    DrawSprite(160, v + 40, gUnk_099A7C64, sMsChargeScrollbarTiles, gUnk_02035D90, 0, 0x800, 0x898);
    DrawSprite(24, 58, AnimUpdate(&sMsChargeMoogleAnim), sMsChargeMoogleTiles, sMsChargeMooglePalette, 0, 0x801, 0x834);

    if (sMsChargeState == 1) {
        switch ((s16)sMsChargeMenuState) {
        case 1:
            sMsChargeCursorX = sMsChargeTab * 3584 + 0xAC00;
            sMsChargeCursorY = 0x1000;
            DrawSprite(sMsChargeCursorX >> 8, (sMsChargeCursorY >> 8) + ((sine = gSineTable[sMsChargeBobPhase]) >> 6), AnimUpdate(&sMsChargeCursorAnim), sMsChargeMoogleTiles, sMsChargeMooglePalette, 0, 0x801, 0x7D0);
            break;
        case 0:
            ApproachValueHalf(&sMsChargeCursorX, (sMsChargeGridCol * 23 + 181) << 8);
            ApproachValueHalf(&sMsChargeCursorY, (sMsChargeGridRow * 26 + 40) << 8);
            DrawSprite(sMsChargeCursorX >> 8, (sMsChargeCursorY >> 8) + ((sine = gSineTable[sMsChargeBobPhase]) >> 6), AnimUpdate(&sMsChargeCursorAnim), sMsChargeMoogleTiles, sMsChargeMooglePalette, 0, 0x801, 0x7D0);
            DrawSprite(sMsChargeGridCol * 23 + 165, sMsChargeGridRow * 26 + 27, AnimUpdate(&sMsChargeHighlightAnim), gUnk_02035C48, gUnk_02035C44, 0, 0x800, 0x7DA);
            break;
        case 2:
            card = GetMsChargeSelectedCard();
            if (card->category == 3) {
                col = 0;
                row = 0;
            } else {
                col = sMsChargeValueCol;
                row = sMsChargeValueRow;
            }
            ApproachValueHalf(&sMsChargeCursorX, (col * 48 + 64) << 8);
            ApproachValueHalf(&sMsChargeCursorY, (row * 8 + 64) << 8);
            DrawSprite(sMsChargeCursorX >> 8, (sMsChargeCursorY >> 8) + ((sine = gSineTable[sMsChargeBobPhase]) >> 6), AnimUpdate(&sMsChargeCursorAnim), sMsChargeMoogleTiles, sMsChargeMooglePalette, 0, 0x801, 0x7D0);
            DrawSprite(col * 48 + 53, row * 8 + 67, AnimUpdate(&sMsChargeHighlightAnim), gUnk_02035C48, gUnk_02035C44, 0, 0x800, 0x7DA);
            break;
        case 3:
            ApproachValueHalf(&sMsChargeConfirmCursorX, sMsChargeConfirmCursor == 0 ? 0x4800 : 0x8800);
            DrawSprite(sMsChargeConfirmCursorX >> 8, 98, AnimUpdate(&sMsChargeConfirmCursorAnim), sMsChargeConfirmCursorTiles, sMsChargeConfirmCursorPalette, 0, 1, 0);

            if (sMsChargeConfirmTextCount != 0) {
                DrawTextSlots(120 - GetTextSlotsWidth(sMsChargeConfirmText, sMsChargeConfirmTextCount) / 2, 60, sMsChargeConfirmText, sMsChargeMooglePalette, 1, sMsChargeConfirmTextCount);
            }

            if (sMsChargeYesTextCount != 0) {
                DrawTextSlots(80, 88, sMsChargeYesText, sMsChargeMooglePalette, 1, sMsChargeYesTextCount);
            }

            if (sMsChargeNoTextCount != 0) {
                DrawTextSlots(144, 88, sMsChargeNoText, sMsChargeMooglePalette, 1, sMsChargeNoTextCount);
            }
            break;
        case 4:
            if (sMsChargeNoticeTextCount != 0) {
                DrawTextSlots(120 - GetTextSlotsWidth(sMsChargeNoticeText, sMsChargeNoticeTextCount) / 2, 74, sMsChargeNoticeText, sMsChargeMooglePalette, 1, sMsChargeNoticeTextCount);
            }
            break;
        }
    }
    anim = AnimUpdate(&sMsChargeGridPremiumAnim);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            if (sMsChargeGridSprites[i][j] != NULL) {
                DrawSprite(j * 23 + 181, i * 26 + 47, sMsChargeGridSprites[i][j], sMsChargeGridTiles[i][j], sMsChargeGridPalettes[i][j], 0, 0x800, 0x83E);

                if (sMsChargeGridPremium[i][j] != 0) {
                    DrawSprite(j * 23 + 181, i * 26 + 47, anim, sMsChargeGridPremiumTiles, gUnk_02035D90, 0, 0x800, 0x834);
                }
            }
        }
    }

    if ((s16)sMsChargeMenuState != 1) {
        if (sMsChargeCardSprite != NULL) {
            DrawSprite(24, 92, sMsChargeCardSprite, sMsChargeCardTiles, sMsChargeCardPalette, 0, 0x800, 0x848);
        }

        if (gUnk_02035D98 != NULL) {
            DrawSprite(24, 92, gUnk_02035D98, gUnk_02035D94, gUnk_02035D90, 0, 0x800, 0x83E);

            if (sMsChargeCardPremium != 0) {
                DrawSprite(24, 92, AnimUpdate(&sMsChargePremiumAnim), sMsChargePremiumTiles, gUnk_02035D90, 0, 0x800, 0x834);
            }
        }

        if (sMsChargeNameTextCount != 0) {
            DrawTextSlots(12, 115, sMsChargeNameText, gUnk_02035C44, 1, sMsChargeNameTextCount);
        }

        if (sMsChargeDescTextCount != 0) {
            DrawTextSlots(6, 131, sMsChargeDescText, sMsChargeMooglePalette, 1, sMsChargeDescTextCount);
        }
    }
}
void mode_ms_charge_0(void) {
    s16 i;
    s16 j;
    u8* pb;
    u16 length;

    {
        MsCard** dst = &gMsCards;
        *dst = EwramAlloc(286 * sizeof(MsCard));
    }
    SpriteReset();
    FadeStartIn(0, 16);
    SetBgMode0();
    SetupBg(0, 0, 28, 0);
    SetupBg(1, 0, 29, 0);
    SetupBg(2, 0, 30, 0);
    SetupBg(3, 0, 31, 0);
    SetBgPriority(0, 3);
    SetBgPriority(1, 2);
    SetBgPriority(2, 1);
    SetBgPriority(3, 0);
    sMsChargeState = 0;
    sMsChargeTab = 4;
    MsChargeBuildCardList();
    sMsChargeGridCol = 0;
    sMsChargeGridRow = 0;
    sMsChargeGridScroll = 0;

    if (sMsChargeCardTotal > 0) {
        s32* position = &sMsChargeCursorX;
        s16 state = 0;
        *position = 0xB500;
        sMsChargeCursorY = 0x2800;
        sMsChargeMenuState = state;
    } else {
        sMsChargeCursorX = sMsChargeTab * 3584 + 0xAC00;
        sMsChargeCursorY = 0x1000;
        sMsChargeMenuState = 1;
    }

    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 2; j++) {
            sMsChargeGridPalettes[i][j] = 0;
            sMsChargeGridTiles[i][j] = 0;
            sMsChargeGridSprites[i][j] = 0;
            sMsChargeGridPremium[i][j] = 0;
        }
    }
    sMsChargeCardPalette = 0;
    sMsChargeCardTiles = 0;
    sMsChargeCardSprite = 0;
    gUnk_02035D94 = 0;
    gUnk_02035D98 = 0;
    sMsChargeCardPremium = 0;
    sMsChargeValueCol = 0;
    sMsChargeValueRow = 0;
    sMsChargeBobPhase = 0;
    sMsChargeMoogleAnimId = -1;
    sMsChargeMoogleAnimTimer = 0;
    LoadBgPalette(0, gUnk_09A3DBDC, 0x1A0);
    LoadBgTiles(0, gUnk_09A1913C,
#ifdef VERSION_EU
        0x61C0
#else
        0x4A60
#endif
    );
    LoadBgMap(0,
#ifdef VERSION_EU
        sUnkEu_09F84FA8[gLanguage]
#else
        gUnk_09A3B25C
#endif
    , 0x500);

    if (GetMsChargeSelectedCard()->category == 3) {
        LoadBgMap(1,
#ifdef VERSION_EU
        sUnkEu_09F84FE4[gLanguage]
#else
        gUnk_09A3BD5C
#endif
    , 0x500);
    } else {
        LoadBgMap(1,
#ifdef VERSION_EU
        sUnkEu_09F84FD0[gLanguage]
#else
        gUnk_09A3B85C
#endif
    , 0x500);
    }
    MsChargeDrawTab(sMsChargeTab);
    LoadBgMap(2,
        gUnk_09A3C25C
    , 0x500);
    MsChargeDrawPoints();
    MsChargeDrawCardCounts();
    MsChargeDrawCategoryCounts();
    MsChargeDrawValueCounts();
    gUnk_02035D90 = LoadObjPalette(gCard00Palette, 32);
    sMsChargePremiumTiles = LoadObjTiles(gUnk_0908B1B4, 0x9A0);
    AnimInit(&sMsChargePremiumAnim, gUnk_09EEA164, gUnk_09EEA148);
    AnimStart(&sMsChargePremiumAnim, 0, 1);
    sMsChargeGridPremiumTiles = LoadObjTiles(gUnk_0908C3CE, 0x260);
    AnimInit(&sMsChargeGridPremiumAnim, gUnk_09EEA198, gUnk_09EEA180);
    AnimStart(&sMsChargeGridPremiumAnim, 0, 1);
    sMsChargeScrollbarTiles = LoadObjTiles(gUnk_099A7C78, 32);
    gUnk_02035C44 = LoadObjPalette(gUnk_09A3DE7C, 32);
    gUnk_02035C48 = LoadObjTiles(gUnk_099A6C82, 0xFE0);
    AnimInit(&gUnk_02035C50, gUnk_09EF9AA4, gUnk_09EF9A68);
    AnimStart(&gUnk_02035C50, 1, 1);
    AnimInit(&sMsChargeHighlightAnim, gUnk_09EF9AA4, gUnk_09EF9A68);
    AnimStart(&sMsChargeHighlightAnim, 2, 1);
    sMsChargeMooglePalette = LoadObjPalette(gMoguPalette, 32);
    sMsChargeMoogleTiles = LoadObjTiles(
#ifdef VERSION_EU
        gUnkEu_099AEE98
#else
        gUnk_099A2194
#endif
    , 0x940);
    AnimInit(&sMsChargeCursorAnim,
        gUnk_09EF9978
    ,
        gUnk_09EF9928
    );
    AnimStart(&sMsChargeCursorAnim, 3, 1);
    AnimInit(&sMsChargeMoogleAnim,
        gUnk_09EF9978
    ,
        gUnk_09EF9928
    );
    AnimStart(&sMsChargeMoogleAnim, 0, 1);
    sMsChargeConfirmCursorPalette = LoadObjPalette(gMoguPalette, 32);
    sMsChargeConfirmCursorTiles = LoadObjTiles(
#ifdef VERSION_EU
        gUnkEu_092D1F74
#else
        gMoguFl00Tiles
#endif
    , 0xC00);
    AnimInit(&sMsChargeConfirmCursorAnim, gMoguFl00Anims, gMoguFl00Frames);
    {
        TextSlot** dst = &sMsChargeNameText;
        *dst = EwramAlloc(36 * sizeof(TextSlot));
    }
    InitTextSlots(sMsChargeNameText, 36);
    {
        TextSlot** dst = &sMsChargeDescText;
        *dst = EwramAlloc(90 * sizeof(TextSlot));
    }
    InitTextSlots(sMsChargeDescText, 90);
    length = GetTextLength(
#ifdef VERSION_EU
        eu_0805E924(&gUnkEu_08890F40)
#else
        gUnk_08159F38
#endif
    );
    sMsChargeConfirmTextLength = length;
    {
        TextSlot** dst = &sMsChargeConfirmText;
        *dst = EwramAlloc(sMsChargeConfirmTextLength * sizeof(TextSlot));
    }
    InitTextSlots(sMsChargeConfirmText, sMsChargeConfirmTextLength);
    pb = &sMsChargeConfirmTextCount;
    *pb = LoadTextSlots(
#ifdef VERSION_EU
        eu_0805E924(&gUnkEu_08890F40)
#else
        gUnk_08159F38
#endif
    , sMsChargeConfirmText);
    length = GetTextLength(
#ifdef VERSION_EU
        eu_0805E924(&gUnkEu_08895960)
#else
        gUnk_0815C204
#endif
    );
    sMsChargeNoticeTextLength = length;
    {
        TextSlot** dst = &sMsChargeNoticeText;
        *dst = EwramAlloc(sMsChargeNoticeTextLength * sizeof(TextSlot));
    }
    InitTextSlots(sMsChargeNoticeText, sMsChargeNoticeTextLength);
    pb = &sMsChargeNoticeTextCount;
    *pb = LoadTextSlots(
#ifdef VERSION_EU
        eu_0805E924(&gUnkEu_08895960)
#else
        gUnk_0815C204
#endif
    , sMsChargeNoticeText);
    length = GetTextLength(
#ifdef VERSION_EU
        eu_0805E924(&gUnkEu_08890E1C)
#else
        gUnk_08159E10
#endif
    );
    sMsChargeYesTextLength = length;
    {
        TextSlot** dst = &sMsChargeYesText;
        *dst = EwramAlloc(sMsChargeYesTextLength * sizeof(TextSlot));
    }
    InitTextSlots(sMsChargeYesText, sMsChargeYesTextLength);
    pb = &sMsChargeYesTextCount;
    *pb = LoadTextSlots(
#ifdef VERSION_EU
        eu_0805E924(&gUnkEu_08890E1C)
#else
        gUnk_08159E10
#endif
    , sMsChargeYesText);
    length = GetTextLength(
#ifdef VERSION_EU
        eu_0805E924(&gUnkEu_08890E44)
#else
        gUnk_08159E18
#endif
    );
    sMsChargeNoTextLength = length;
    {
        TextSlot** dst = &sMsChargeNoText;
        *dst = EwramAlloc(sMsChargeNoTextLength * sizeof(TextSlot));
    }
    InitTextSlots(sMsChargeNoText, sMsChargeNoTextLength);
    pb = &sMsChargeNoTextCount;
    *pb = LoadTextSlots(
#ifdef VERSION_EU
        eu_0805E924(&gUnkEu_08890E44)
#else
        gUnk_08159E18
#endif
    , sMsChargeNoText);
    MsChargeLoadGrid();
    MsChargeLoadSelectedCard();
    EnableBg(0);
    EnableBg(1);
    DisableBg(2);
    DisableBg(3);
}

void mode_ms_charge_1(void) {
    UpdatePlayTime();
    sMsChargeBobPhase += 2;

    switch (sMsChargeState) {
    case 0:
        if (!FadeIsActive()) {
            sMsChargeState = 1;
        }
        break;
    case 1:
        switch (sMsChargeMenuState) {
        case 0:
            MsChargeHandleGridInput();
            break;
        case 1:
            MsChargeHandleTabInput();
            break;
        case 2:
            MsChargeHandleValueInput();
            break;
        case 3:
            MsChargeHandleConfirmInput();
            break;
        case 4:
            MsChargeHandleNoticeInput();
            break;
        }
        break;
    case 2:
        if (!FadeIsActive()) {
            if (sMsChargeBackToTop != 0) {
                ModeRequest(&gModeMsTop, 2);
            } else {
                RequestMapMode();
            }
        }
        break;
    }

    if (sMsChargeMoogleAnimTimer > 0) {
        if (AnimGetId(&sMsChargeMoogleAnim) != 2) {
            if (sMsChargeMoogleAnimId < 0) {
                sMsChargeMoogleAnimId = AnimGetId(&sMsChargeMoogleAnim);
            }
            AnimStart(&sMsChargeMoogleAnim, 2, 1);
        }

        if (--sMsChargeMoogleAnimTimer <= 0) {
            if (AnimGetId(&sMsChargeMoogleAnim) != sMsChargeMoogleAnimId) {
                AnimStart(&sMsChargeMoogleAnim, sMsChargeMoogleAnimId, 1);
            }
            sMsChargeMoogleAnimId = -1;
        }
    } else if (sMsChargeMoogleAnimId >= 0) {
        if (AnimGetId(&sMsChargeMoogleAnim) != sMsChargeMoogleAnimId) {
            AnimStart(&sMsChargeMoogleAnim, sMsChargeMoogleAnimId, 1);
        }
        sMsChargeMoogleAnimId = -1;
    }
    MsChargeDraw();
}

void mode_ms_charge_2(void) {
    s32 i;
    s32 j;

    ReleaseObjPalette(gUnk_02035D90);
    ReleaseObjTiles(sMsChargePremiumTiles);
    ReleaseObjTiles(sMsChargeGridPremiumTiles);
    ReleaseObjTiles(sMsChargeScrollbarTiles);
    ReleaseObjPalette(gUnk_02035C44);
    ReleaseObjTiles(gUnk_02035C48);
    ReleaseObjPalette(sMsChargeMooglePalette);
    ReleaseObjTiles(sMsChargeMoogleTiles);
    ReleaseObjPalette(sMsChargeConfirmCursorPalette);
    ReleaseObjTiles(sMsChargeConfirmCursorTiles);

    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 2; j++) {
            if (sMsChargeGridPalettes[i][j] != NULL) {
                ReleaseObjPalette(sMsChargeGridPalettes[i][j]);
            }

            if (sMsChargeGridTiles[i][j] != NULL) {
                ReleaseObjTiles(sMsChargeGridTiles[i][j]);
            }
        }
    }

    if (sMsChargeCardPalette != NULL) {
        ReleaseObjPalette(sMsChargeCardPalette);
    }

    if (sMsChargeCardTiles != NULL) {
        ReleaseObjTiles(sMsChargeCardTiles);
    }

    if (gUnk_02035D94 != NULL) {
        ReleaseObjTiles(gUnk_02035D94);
    }
    FreeTextSlots(sMsChargeNameText, 36);
    EwramFree(sMsChargeNameText);
    FreeTextSlots(sMsChargeDescText, 90);
    EwramFree(sMsChargeDescText);
    FreeTextSlots(sMsChargeConfirmText, sMsChargeConfirmTextLength);
    EwramFree(sMsChargeConfirmText);
    FreeTextSlots(sMsChargeNoticeText, sMsChargeNoticeTextLength);
    EwramFree(sMsChargeNoticeText);
    FreeTextSlots(sMsChargeYesText, sMsChargeYesTextLength);
    EwramFree(sMsChargeYesText);
    FreeTextSlots(sMsChargeNoText, sMsChargeNoTextLength);
    EwramFree(sMsChargeNoText);
    EwramFree(gMsCards);
}

Mode gModeMsCharge = {
    "mode_ms_charge",
    (ModeInitFunc)mode_ms_charge_0,
    mode_ms_charge_1,
    mode_ms_charge_2,
};
