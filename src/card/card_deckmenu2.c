#include "macros.h"
#include "card_localized_data.h"
#include "msg_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "mode_test_api.h"
#include "player_progression.h"
#include "m4a_song.h"
#include "game_state.h"
#include "text.h"
#include "monsgage.h"
#include "fade.h"
#include "obj_api.h"
#include "display.h"
#include "engine_math.h"
#include "listpool.h"
#include "anim.h"
#include "obj.h"
#include "text_types.h"
#include "taskpool.h"
#include "key.h"
#include "gba/syscall.h"
#include "malloc.h"
#include "card.h"
#include "sprites_card.h"
#include "sprites_deck_menu.h"
#include "sprites_card_pictures.h"
#include "card_ids.h"
#include "gba/keys.h"
#include "songs.h"
#include "card_deck_data.h"
#include "card_api.h"
#include "card_def_data.h"
#include "card_types.h"
#include "card_ui_types.h"
#include "gba/defines.h"
#include "mode_battle_data.h"
#include "player_progression_types.h"
#include "types.h"
#include "gba/macro.h"
#include "sprite_palettes.h"
#include <stddef.h>

const u16 gRikuDeckCards0[21] = {
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_HI_POTION, 7),
};

const u16 gRikuDeckCards1[20] = {
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 2),
    CARD_ID(CARD_SOUL_EATER, 2),
    CARD_ID(CARD_SOUL_EATER, 2),
    CARD_ID(CARD_SOUL_EATER, 2),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 1),
};

const u16 gRikuDeckCards2[21] = {
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 2),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 8),
    CARD_ID(CARD_SOUL_EATER, 9),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 0),
    CARD_ID(CARD_SOUL_EATER, 0),
    CARD_ID(CARD_SOUL_EATER, 0),
};

const u16 gRikuDeckCards3[12] = {
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 5),
};

const u16 gRikuDeckCards4[20] = {
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 1),
};

const u16 gRikuDeckCards5[18] = {
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 4),
};

const u16 gRikuDeckCards6[17] = {
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 2),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 0),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 2),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 8),
    CARD_ID(CARD_SOUL_EATER, 9),
};

const u16 gRikuDeckCards7[16] = {
    CARD_ID(CARD_SOUL_EATER, 9),
    CARD_ID(CARD_SOUL_EATER, 8),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 8),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_POTION, 9),
};

const u16 gRikuDeckCards8[19] = {
    CARD_ID(CARD_SOUL_EATER, 0),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 0),
    CARD_ID(CARD_SOUL_EATER, 2),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 8),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 2),
    CARD_ID(CARD_SOUL_EATER, 0),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 2),
    CARD_ID(CARD_SOUL_EATER, 0),
};

const u16 gRikuDeckCards9[5] = {
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 8),
};

const u16 gRikuDeckCards10[25] = {
    CARD_ID(CARD_SOUL_EATER, 9),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 8),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 2),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 0),
    CARD_ID(CARD_SOUL_EATER, 9),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 5),
    CARD_ID(CARD_SOUL_EATER, 3),
    CARD_ID(CARD_SOUL_EATER, 1),
    CARD_ID(CARD_SOUL_EATER, 0),
    CARD_ID(CARD_SOUL_EATER, 2),
    CARD_ID(CARD_SOUL_EATER, 4),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 8),
    CARD_ID(CARD_SOUL_EATER, 0),
    CARD_ID(CARD_SOUL_EATER, 2),
    CARD_ID(CARD_SOUL_EATER, 9),
};

const u16 gRikuDeckCards11[30] = {
    CARD_ID(CARD_SOUL_EATER, 8),
    CARD_ID(CARD_SOUL_EATER, 8),
    CARD_ID(CARD_SOUL_EATER, 8),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 9),
    CARD_ID(CARD_SOUL_EATER, 9),
    CARD_ID(CARD_SOUL_EATER, 9),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 8),
    CARD_ID(CARD_SOUL_EATER, 9),
    CARD_ID(CARD_SOUL_EATER, 8),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 9),
    CARD_ID(CARD_SOUL_EATER, 9),
    CARD_ID(CARD_SOUL_EATER, 6),
    CARD_ID(CARD_SOUL_EATER, 7),
    CARD_ID(CARD_SOUL_EATER, 8),
    CARD_ID(CARD_HI_POTION, 9),
    CARD_ID(CARD_HI_POTION, 0),
    CARD_ID(CARD_SOUL_EATER, 0),
    CARD_ID(CARD_SOUL_EATER, 0),
    CARD_ID(CARD_SOUL_EATER, 0),
    CARD_ID(CARD_SOUL_EATER, 0),
};

const u16 gRikuDeckEnemyCard0 = CARD_FAT_BANDIT_3;

const u16 gRikuDeckEnemyCard1 = 492;

const u16 gRikuDeckEnemyCard2 = 471;

const u16 gRikuDeckEnemyCard3 = CARD_LARGE_BODY_1;

const u16 gRikuDeckEnemyCard4 = CARD_SEARCH_GHOST_1;

const u16 gRikuDeckEnemyCard5 = CARD_WIGHT_KNIGHT_2;

const u16 gRikuDeckEnemyCard6 = CARD_PIRATE_1;

const u16 gRikuDeckEnemyCard7 = CARD_DEFENDER_5;

const u16 gRikuDeckEnemyCard9 = 450;

const u16 gRikuDeckCardCounts[12] = {
    21,
    20,
    21,
    12,
    20,
    18,
    17,
    16,
    19,
    5,
    25,
    30,
};

const u16 gRikuDeckEnemyCardCounts[12] = {
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    0,
    1,
    0,
    0,
};

const u16 gUnk_090356EA = 0;

static u8 sActiveDeck;
static u16 sUnk_02034AB2;

CardUiSpriteState gCardUiSpriteState EWRAM_COMMON(16);

u8 UpdateDeckMenuOpenAddMode(DeckMenuWork* w, void* a);
void ReleaseCardPreview(DeckMenuWork* w);
void HighlightDeckTab(DeckMenuWork* w, u8 b);
void DrawCpCost(u8 a);
s32 GetCardIdForKindEntry(s32 a);
u8 UpdateDeckMenuBuildAddList(DeckMenuWork* w, void* a);
u8 UpdateDeckMenuCommands(DeckMenuWork* w, void* a);
u8 UpdateDeckMenuCloseCommands(DeckMenuWork* w, void* a);
u8 UpdateDeckMenuOpenKeyboard(DeckMenuWork* w, void* a);
u8 UpdateDeckMenuKeyboard(DeckMenuWork* w, void* a);
void LoadDeckNameTexts(DeckMenuWork* w);
u8 UpdateDeckMenuDeckGrid(DeckMenuWork* w, void* a);
void ReleaseCommandMenuGfx(DeckMenuWork* w);
u8 UpdateDeckMenuDeckSelect(DeckMenuWork* w, void* a);
u8 UpdateDeckMenuStartSlideOut(DeckMenuWork* w, void* a);
u8 UpdateDeckMenuAddGrid(DeckMenuWork* w, void* a);
void BuildRikuDeck(u8 a);
u8 UpdateDeckMenuCollectionFilter(DeckMenuWork* w, void* a);
u8 UpdateDeckMenuSlideOut(DeckMenuWork* w, void* a);
void ClearCardGrid(DeckMenuWork* w);
void CreateDeckGridCards(DeckMenuWork* w, u8 b);
void ShowDeckCardPreview(DeckMenuWork* w);
u8 UpdateDeckMenuRemoveGrid(DeckMenuWork* w, void* a);
u8 UpdateDeckMenuCloseRemoveMode(DeckMenuWork* w, void* a);
u8 UpdateDeckMenuCloseAddMode(DeckMenuWork* w, void* a);
u8 UpdateDeckMenuCloseDeleteMode(DeckMenuWork* w, void* a);
u8 UpdateDeckMenuOpenRemoveMode(DeckMenuWork* w, void* a);
u8 UpdateDeckMenuDeckFilter(DeckMenuWork* w, void* a);
s32 ShowCollectionCardPreview(DeckMenuWork* w);
void SetGridRowCount(DeckMenuWork* w, s16 n);
void UpdateGridScrollBar(DeckMenuWork* w);
u8 UpdateDeckMenuLoadBgs(DeckMenuWork* w, void* a);
void DrawCollectionCategoryCount(u16 a, u8 b);
u8 UpdateDeckMenuBuildRemoveGrid(DeckMenuWork* w, void* a);
u8 UpdateDeckMenuFadeOut(DeckMenuWork* w);
u8 UpdateDeckMenuDeleteGrid(DeckMenuWork* w, void* a);
u8 UpdateDeckMenuDeleteValueSelect(DeckMenuWork* w, void* a);
u8 UpdateDeckMenuBuildDeleteList(DeckMenuWork* w, void* a);
void FreeCollectionEntries(DeckMenuWork* w);
void DrawValueCount(u8 a, u16 b);
void DrawDeckCategoryCount(u8 a, u8 b);
u16 CountCollectionCards();
u16 CountCardsInDecks();
void RemoveEmptyCollectionEntry(DeckMenuWork* w, u8 mode);
s32 CreateCollectionGridCards(DeckMenuWork* w, u8 kind, u8 c);
void ScrollGridDown(DeckMenuWork* w);
DeckCard2Work* GetCardAtCursor(DeckMenuWork* w);
void DrawDeckEquipMarker(u8 mode);
void DrawDeckCpCost(u8 mode);
void DrawCardTotals();
void DrawSelectedValueCpCost(DeckMenuWork* w);
s32 MoveValueCursor(DeckMenuWork* w, u16 keys);
s32 AddSelectedValueCardToDeck(DeckMenuWork* w);
u8 DeleteSelectedValueCard(DeckMenuWork* w);
s32 CheckDeckCpCost(DeckMenuWork* w);
s32 CheckDeckHasAttackCard(DeckMenuWork* w);
s32 IsCardAtCursor(DeckMenuWork* w);
u8 IsCardAt(DeckMenuWork* w, s16 a, s16 b);
u8 SwapHeldDeckCard(DeckMenuWork* w);
void BuildCollectionEntries(DeckMenuWork* w);

void CountCardsNotInDeckByKind(CardKindEntry* out, u8 deck, u8 mode, u16 n, void* p) {
    u16 mask;
    u16 i;
    s32 x;

    mask = 0;

    if (mode == 1) {
        switch (deck) {
        case 0:
            mask = 0x1000;
            break;
        case 1:
            mask = 0x2000;
            break;
        case 2:
            mask = 0x4000;
            break;
        }
    } else {
        mask = 0x7000;
    }

    for (i = 0; i < gCardCount; i++) {
        if (gCardCollection[i] == CARD_ID_MASK) {
            continue;
        }

        if (gCardCollection[i] & mask) {
            continue;
        }

        if (!(gCardCollection[i] & 0x8000)) {
            x = gCardDefs[gCardCollection[i] & CARD_ID_MASK].kind;
            out[x].kind = x;
            out[x].count++;
        } else {
            x = gCardDefs[gCardCollection[i] & CARD_ID_MASK].kind;
            out[x + 0x8F].kind = x + 0x8F;
            out[x + 0x8F].count++;
        }
    }
}

u16 ListCardsNotInDeckByKind(CardKindEntry* out, u8 deck, u8 mode, u16 n, void* p) {
    u16 mask;
    u16 i;
    u16 count;
    u32 id;
    u16 x;

    mask = 0;

    if (mode == 1) {
        switch (deck) {
        case 0:
            mask = 0x1000;
            break;
        case 1:
            mask = 0x2000;
            break;
        case 2:
            mask = 0x4000;
            break;
        }
    } else {
        mask = 0x7000;
    }

    for (i = 0, count = 0; i < n; i++) {
        if (out[i].count != 0) {
            out[i].indices = EwramAlloc(out[i].count * 2);
            count++;
        } else {
            out[i].indices = NULL;
        }

        out[i].indexCount = 0;
    }

    for (i = 0; i < gCardCount; i++) {
        if (gCardCollection[i] == CARD_ID_MASK) {
            continue;
        }

        if (gCardCollection[i] & mask) {
            continue;
        }

        if (!(gCardCollection[i] & 0x8000)) {
            id = gCardCollection[i] & CARD_ID_MASK;
            x = gCardDefs[id].kind;

            if (id > 0x1C1) {
                out[x].valueCounts[0]++;
            } else {
                out[x].valueCounts[gCardDefs[id].value]++;
            }

            out[x].indices[out[x].indexCount++] = i;
        } else {
            id = gCardCollection[i] & CARD_ID_MASK;
            x = gCardDefs[id].kind + 0x8F;

            if (id > 0x1C1) {
                out[x].valueCounts[0]++;
            } else {
                out[x].valueCounts[gCardDefs[id].value]++;
            }

            out[x].indices[out[x].indexCount++] = i;
        }
    }

    return count;
}

void func_08084FA8() {
}

u16 CountCollectionCardsOfCategory(u8 slot) {
    u16 count;
    u16 i;

    count = 0;

    for (i = 0; i < gCardCount; i++) {
        if (gCardCollection[i] != CARD_ID_MASK) {
            if (gCardDefs[gCardCollection[i] & CARD_ID_MASK].category == slot) {
                count++;
            }
        }
    }

    return count;
}

void CountCardsNotInDeckByCategory(u8 mode, u16* out) {
    u16 mask;
    u16 i;

    mask = 0;
    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;

    switch (mode) {
    case 0:
        mask = 0x1000;
        break;
    case 1:
        mask = 0x2000;
        break;
    case 2:
        mask = 0x4000;
        break;
    case 3:
        mask = 0x7000;
        break;
    }

    for (i = 0; i < gCardCount; i++) {
        if (gCardCollection[i] != CARD_ID_MASK) {
            if (!(gCardCollection[i] & mask)) {
                out[gCardDefs[gCardCollection[i] & CARD_ID_MASK].category]++;
            }
        }
    }
}

void ClearCardCollectionSlot(u16* p) {
    *p = CARD_ID_MASK;
}

void RemoveUnequippedCardById(u16 id) {
    s32 i;

    for (i = 0; i < gCardCount; i++) {
        if (gCardCollection[i] != CARD_ID_MASK &&
            (gCardCollection[i] & 0x7000) == 0 &&
            (gCardCollection[i] & CARD_ID_MASK) == id) {
            gCardCollection[i] = CARD_ID_MASK;
            return;
        }
    }
}

u8 CollectionHasCard(u16 id) {
    s32 i;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        return 0;
    }

    for (i = 0; i < gCardCount; i++) {
        if ((gCardCollection[i] & CARD_ID_MASK) == id) {
            return 1;
        }
    }

    return 0;
}

void InitDecks() {
    u16 i;
    u16 j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 99; j++) {
            gDecks[i].cards[j] |= 0xFFFF;
        }

        for (j = 0; j < 20; j++) {
            gDecks[i].name[j] = 0;
        }

        gDecks[i].cpCost = 0;
        gDecks[i].cardCount = 0;
    }
}

void ClearDeck(u8 deck) {
    u16 mask;
    u16 i;

    mask = 0;

    switch (deck) {
    case 0:
        mask = 0x1000;
        break;
    case 1:
        mask = 0x2000;
        break;
    case 2:
        mask = 0x4000;
        break;
    }

    for (i = 0; i < 99; i++) {
        if (gDecks[deck].cards[i] != 0xFFFF) {
            gCardCollection[gDecks[deck].cards[i]] &= ~mask;
            gDecks[deck].cards[i] |= 0xFFFF;
        }
    }

    gDecks[deck].cpCost = 0;
    gDecks[deck].cardCount = 0;
}

u8 AddCardToActiveDeck(u16 card) {
    u16* cards;
    u16 i;
    u16 v;

    i = 0;
    cards = GetActiveDeck()->cards;

    while (cards[i] != 0xFFFF) {
        i++;

        if (i == 99) {
            return 0;
        }
    }

    cards[i] = card;

    switch (sActiveDeck) {
    case 0:
        gCardCollection[card] |= 0x1000;
        break;
    case 1:
        gCardCollection[card] |= 0x2000;
        break;
    case 2:
        gCardCollection[card] |= 0x4000;
        break;
    }

    v = GetCardCpCost(gCardCollection[card]);
    gDecks[sActiveDeck].cpCost += v;
    gDecks[sActiveDeck].cardCount++;
    return 1;
}

u8 AddCardToDeck(u16 card, u8 deck) {
    u16* cards;
    u16 i;
    u16 v;

    cards = GetDeck(deck)->cards;

    for (i = 0; i < 99 && cards[i] != 0xFFFF; i++) {
    }

    if (i == 99) {
        return 0;
    }

    cards[i] = card;

    switch (deck) {
    case 0:
        gCardCollection[card] |= 0x1000;
        break;
    case 1:
        gCardCollection[card] |= 0x2000;
        break;
    case 2:
        gCardCollection[card] |= 0x4000;
        break;
    }

    v = GetCardCpCost(gCardCollection[card]);
    gDecks[deck].cpCost += v;
    gDecks[deck].cardCount++;
    return 1;
}

void RemoveCardFromActiveDeck(u16 slot) {
    u16* cards;
    u16 v;

    cards = GetActiveDeck()->cards;

    if (cards[slot] != 0) {
        switch (sActiveDeck) {
        case 0:
            gCardCollection[cards[slot]] &= ~0x1000;
            break;
        case 1:
            gCardCollection[cards[slot]] &= ~0x2000;
            break;
        case 2:
            gCardCollection[cards[slot]] &= ~0x4000;
            break;
        }
    }

    v = GetCardCpCost(gCardCollection[cards[slot]]);
    gDecks[sActiveDeck].cpCost -= v;
    gDecks[sActiveDeck].cardCount--;
    cards[slot] = 0xFFFF;
}

void RemoveCardFromDeck(u16* p, u8 deck) {
    u16 v;

    switch (deck) {
    case 0:
        gCardCollection[*p] &= ~0x1000;
        break;
    case 1:
        gCardCollection[*p] &= ~0x2000;
        break;
    case 2:
        gCardCollection[*p] &= ~0x4000;
        break;
    }

    v = GetCardCpCost(gCardCollection[*p]);
    gDecks[deck].cpCost -= v;
    gDecks[deck].cardCount--;
    *p = 0xFFFF;
}

void RecalculateInactiveDeckCpCosts() {
    u8 i;
    u16 total;
    s32 j;
    Deck* deck;

    for (i = 0; i < 3; i++) {
        if (i == sActiveDeck) {
            continue;
        }

        total = 0;
        deck = GetDeck(i);

        for (j = 0; j < 99; j++) {
            if (deck->cards[j] != 0xFFFF) {
                total += GetCardCpCost(gCardCollection[deck->cards[j]]);
            }
        }

        gDecks[i].cpCost = total;
    }
}

void ConvertActiveDeckCardToPremium(u16 index) {
    u16* cards;
    u16 v;

    cards = GetActiveDeck()->cards;
    gDecks[sActiveDeck].cpCost -= GetCardCpCost(gCardCollection[cards[index]]);
    gCardCollection[cards[index]] |= 0x8000;
    v = GetCardCpCost(gCardCollection[cards[index]]) + gDecks[sActiveDeck].cpCost;
    gDecks[sActiveDeck].cpCost = v;
    RecalculateInactiveDeckCpCosts();
}

u8 HasNonPremiumCardsInActiveDeck() {
    Deck* deck;
    s32 count;
    s32 i;

    count = 0;
    deck = GetActiveDeck();

    for (i = 0; i < DECK_SIZE; i++) {
        if (deck->cards[i] != 0xFFFF) {
            if (gCardCollection[deck->cards[i]] & 0x8000) {
                count++;
            }
        }
    }

    if (gDecks[sActiveDeck].cardCount == count) {
        return 0;
    }

    return 1;
}

Deck* GetActiveDeck() {
    return &gDecks[sActiveDeck];
}

Deck* GetDeck(u8 index) {
    return &gDecks[index];
}

u16 GetDeckCpCost(u8 index) {
    return gDecks[index].cpCost;
}

void SetDeckName(u8 index, const void* src) {
    u8* deck;
    u32 offset;
    u8* d;
    const u8* s;

#ifdef VERSION_US
    if (*(const u16*)src == 0) {
#else
    if (*(const u8*)src == 0) {
#endif
        return;
    }

    deck = (u8*)&gDecks;
    offset = index * (sizeof(Deck) / sizeof(u16));
    s = src;
    offset *= sizeof(u16);
    d = deck + offsetof(Deck, name);
    d += offset;

#ifdef VERSION_US
    do {
        d[0] = s[0];
        d[1] = s[1];
        d += 2;
        s += 2;
    } while (*(const u16*)s != 0);
#else
    do {
        *d = *s;
#ifdef VERSION_EU
        d++;
        s++;
#else
        s++;
        d++;
#endif
    } while (*s != 0);
#endif
}

u8* GetDeckName(u8 index) {
    return gDecks[index].name;
}

u16 CountActiveDeckCardsOfCategory(u8 slot) {
    u16* cards;
    u16 count;
    u16 i;

    count = 0;
    cards = GetActiveDeck()->cards;

    for (i = 0; i < DECK_SIZE; i++) {
        if (cards[i] != 0xFFFF) {
            if (gCardDefs[gCardCollection[cards[i]] & CARD_ID_MASK].category == slot) {
                count++;
            }
        }
    }

    return count;
}

u16 CountDeckCardsOfCategory(u8 slot, u8 deckIndex) {
    u16* cards;
    u16 count;
    u16 i;

    count = 0;
    cards = GetDeck(deckIndex)->cards;

    for (i = 0; i < DECK_SIZE; i++) {
        if (cards[i] != 0xFFFF) {
            if (gCardDefs[gCardCollection[cards[i]] & CARD_ID_MASK].category == slot) {
                count++;
            }
        }
    }

    return count;
}

s16 CountActiveDeckCards(s32 index) {
    u16 count;
    s16 i;
    u16* cards;

    count = 0;
    cards = GetActiveDeck()->cards;

    switch (index) {
    case 0:
        for (i = 0; i <= 98; i++) {
            if (cards[i] != 0xFFFF) {
                if (gCardDefs[gCardCollection[cards[i]] & CARD_ID_MASK].category <= 2) {
                    count = ((count << 16) + 0x10000) >> 16;
                }
            }
        }

        break;
    case 1:
        for (i = 0; i <= 98; i++) {
            if (cards[i] != 0xFFFF) {
                if (gCardDefs[gCardCollection[cards[i]] & CARD_ID_MASK].category == 3) {
                    count = ((count << 16) + 0x10000) >> 16;
                }
            }
        }

        break;
    }

    return count;
}

s16 CountDeckCards(s32 mode, const Deck* d) {
    s16 count;
    s16 i;

    count = 0;

    switch (mode) {
    case 0:
        for (i = 0; i < d->cardCount; i++) {
            if (gCardDefs[d->cards[i] & CARD_ID_MASK].category <= 2) {
                count++;
            }
        }

        break;
    case 1:
        for (i = 0; i < d->cardCount; i++) {
            if (gCardDefs[d->cards[i] & CARD_ID_MASK].category == 3) {
                count++;
            }
        }

        break;
    }

    return count;
}

void CopyActiveDeckCards(s32 a, u16* out) {
    u16* cards;
    u16 i;

    cards = GetActiveDeck()->cards;

    switch (a) {
    case 0:
        for (i = 0; i < 99; i++) {
            if (cards[i] != 0xFFFF) {
                if (gCardDefs[gCardCollection[cards[i]] & 0xFFF].category <= 2) {
                    *out++ = gCardCollection[cards[i]] & 0x8FFF;
                }
            }
        }

        break;
    case 1:
        for (i = 0; i < 99; i++) {
            if (cards[i] != 0xFFFF) {
                if (gCardDefs[gCardCollection[cards[i]] & 0xFFF].category == 3) {
                    *out++ = gCardCollection[cards[i]] & 0x8FFF;
                }
            }
        }

        break;
    }
}

u16 GetDeckCardCount(u8 index) {
    return gDecks[index].cardCount;
}

void SetActiveDeckIndex(u8 index) {
    sActiveDeck = index;
}

u16 GetCollectionCardKind(u16 index) {
    return gCardDefs[gCardCollection[index] & CARD_ID_MASK].kind;
}

u8 GetCollectionCardCategory(u16 index) {
    return gCardDefs[gCardCollection[index] & CARD_ID_MASK].category;
}

u8 IsActiveDeckAllPremium() {
    Deck* deck;
    s32 a;
    s32 b;
    s32 i;

    a = 0;
    b = 0;
    deck = GetActiveDeck();

    for (i = 0; i < DECK_SIZE; i++) {
        if (deck->cards[i] != 0xFFFF) {
            if (GetCollectionCardCategory(deck->cards[i]) != 2) {
                if (GetCollectionCardCategory(deck->cards[i]) != 3) {
                    a++;
                }
            }
        }
    }

    for (i = 0; i < DECK_SIZE; i++) {
        if (deck->cards[i] != 0xFFFF) {
            if (gCardCollection[deck->cards[i]] & 0x8000) {
                b++;
            }
        }
    }

    if (b == a) {
        return 1;
    }

    return 0;
}

#ifdef VERSION_JP
#include "deck_names_shift_jis.inc"
#endif
void InitSoraDecks() {
    sActiveDeck = 0;
    InitCardCollection();
    InitDecks();

    if (gDebugFlags & DEBUG_FLAG_ALL_BTL_CARD) {
        FillDebugCardCollection();
        func_080AB22C(2);
        BuildDebugKingdomKeyDeck(1);
        func_080AB4AC(0);
    } else {
        ObtainStarterCards();
        FillStarterDeck();
        func_080AB964();
        func_080AB968();
    }

#ifdef VERSION_EU
    SetDeckName(0, gDefaultDeckName0.strings[gLanguage]);
    SetDeckName(1, gDefaultDeckName1.strings[gLanguage]);
    SetDeckName(2, gDefaultDeckName2.strings[gLanguage]);
#elif defined(VERSION_JP)
    SetDeckName(0, gUnkJp_090089B0);
    SetDeckName(1, gUnkJp_090089BC);
    SetDeckName(2, gUnkJp_090089C8);
#else
    SetDeckName(0, gUnk_09EE4AC8);
    SetDeckName(1, gUnk_09EE4AD6);
    SetDeckName(2, gUnk_09EE4AE4);
#endif
}

void InitDebugDecks() {
    sActiveDeck = 0;
    InitCardCollection();
    InitDecks();
    FillDebugCardCollection();
    BuildDebugKingdomKeyDeck(0);
    func_080AB22C(1);
    func_080AB4AC(2);
#ifdef VERSION_EU
    SetDeckName(0, gDefaultDeckName0.strings[gLanguage]);
    SetDeckName(1, gDefaultDeckName1.strings[gLanguage]);
    SetDeckName(2, gDefaultDeckName2.strings[gLanguage]);
#elif defined(VERSION_JP)
    SetDeckName(0, gUnkJp_090089B0);
    SetDeckName(1, gUnkJp_090089BC);
    SetDeckName(2, gUnkJp_090089C8);
#else
    SetDeckName(0, gUnk_09EE4AC8);
    SetDeckName(1, gUnk_09EE4AD6);
    SetDeckName(2, gUnk_09EE4AE4);
#endif
}

void InitRikuDeckForWorld(u8 a) {
    u8 n = 0;

    InitCardCollection();
    InitDecks();
    SetActiveDeckIndex(0);

    switch (a) {
    case 2:
        n = 1;
        break;
    case 3:
        n = 2;
        break;
    case 4:
        n = 3;
        break;
    case 5:
        n = 4;
        break;
    case 6:
        n = 5;
        break;
    case 7:
        n = 6;
        break;
    case 8:
        n = 7;
        break;
    case 9:
        n = 8;
        break;
    case 10:
        n = 9;
        break;
    case 11:
        n = 10;
        break;
    case 0:
    case 12:
        n = 11;
        break;
    case 1:
    case 13:
        n = 0;
        break;
    }

    BuildRikuDeck(n);
}

void BuildRikuDeck(u8 a) {
    s32 i;
    s32 j;

    for (i = 0, j = 0; i < gRikuDeckCardCounts[a]; i++, j++) {
        ObtainCard(gRikuDeckCards[a][i]);
        AddCardToActiveDeck(i);
    }

    for (i = 0; i < gRikuDeckEnemyCardCounts[a]; j++, i++) {
        ObtainCard(gRikuDeckEnemyCards[a][i]);
        AddCardToActiveDeck(j);
    }

    gCardCollection[200] = CARD_GUARD_ARMOR_1;
    gCardCollection[201] = CARD_PARASITE_CAGE_1;
    gCardCollection[202] = CARD_TRICKMASTER_1;
    gCardCollection[203] = CARD_DARKSIDE_1;
    gCardCollection[204] = CARD_HADES_9;
    gCardCollection[205] = CARD_JAFAR_1;
    gCardCollection[206] = CARD_OOGIE_BOOGIE_1;
    gCardCollection[207] = CARD_URSULA_1;
    gCardCollection[208] = CARD_HOOK_9;
    gCardCollection[209] = CARD_DRAGON_MALEFICENT_1;
    gCardCollection[210] = CARD_RIKU_9;
    gCardCollection[211] = CARD_VEXEN_9;
    gCardCollection[212] = CARD_LEXAEUS_9;
    gCardCollection[213] = CARD_ANSEM_9;

    if (IsCardKindObtained(38)) {
        AddCardToActiveDeck(200);
    }

    if (IsCardKindObtained(42)) {
        AddCardToActiveDeck(201);
    }

    if (IsCardKindObtained(40)) {
        AddCardToActiveDeck(202);
    }

    if (IsCardKindObtained(44)) {
        AddCardToActiveDeck(203);
    }

    if (IsCardKindObtained(50)) {
        AddCardToActiveDeck(204);
    }

    if (IsCardKindObtained(39)) {
        AddCardToActiveDeck(205);
    }

    if (IsCardKindObtained(45)) {
        AddCardToActiveDeck(206);
    }

    if (IsCardKindObtained(41)) {
        AddCardToActiveDeck(207);
    }

    if (IsCardKindObtained(48)) {
        AddCardToActiveDeck(208);
    }

    if (IsCardKindObtained(43)) {
        AddCardToActiveDeck(209);
    }

    if (IsCardKindObtained(51)) {
        AddCardToActiveDeck(210);
    }

    if (IsCardKindObtained(54)) {
        AddCardToActiveDeck(211);
    }

    if (IsCardKindObtained(57)) {
        AddCardToActiveDeck(212);
    }

    if (IsCardKindObtained(56)) {
        AddCardToActiveDeck(213);
    }
}

u8 GetActiveDeckIndex() {
    return sActiveDeck;
}

void func_08085FB0() {
}

#ifdef VERSION_EU
static const u16 sDeckButtonLabelTileSizes[5] = { 0x280, 0x280, 0x280, 0x280, 0x280 };
static const u16 sDeckCommandMenuTileSizes[5] = { 0x1800, 0x1800, 0x1800, 0x1800, 0x1800 };
static const u16 sDeckTitleBannerTileSizes[5] = { 0x320, 0x320, 0x320, 0x320, 0x320 };
#endif
static const s16 sDeckTabPointerX[3] = { 116, 116, 116 };

#ifdef VERSION_EU
static const s16 sDeckTabPointerY[3] = { 51, 99, 148 };
#else
static const s16 sDeckTabPointerY[3] = { 56, 104, 148 };
#endif

static const s16 sDeckFilterTabX[5] = { 12, 28, 42, 56, 70 };

static const s16 sCollectionFilterTabX[6] = { 172, 172, 188, 202, 216, 230 };

static const s16 sDeckCommandY[6] = { 50, 67, 85, 108, 126, 149 };

static const s16 sValueGridX[2] = { 80, 128 };

static const s16 sValueGridY[9] = { 80, 88, 96, 104, 112, 45, 93, 141, 30 };

#ifdef VERSION_JP
static const PromptChoiceLayout sDeckPromptChoiceLayout = { { 94, 151 } };
#else
static const PromptChoiceLayout sDeckPromptChoiceLayout = { { 102, 148 } };
#endif

static void Deckmenu2_0(DeckMenuWork* w, void* a) {
    w->resultOut = a;
    SetBgMode0();
    SetBackdropColor(0, 0, 0);
#ifdef VERSION_EU
    SetupBg(0, 0, 31, 0);
    SetupBg(1, 0, 29, 0);
    SetupBg(2, 0, 28, 0);
    SetupBg(3, 0, 30, 0);
#else
    SetupBg(0, 3, 31, 0);
    SetupBg(1, 2, 23, 0);
    SetupBg(2, 1, 15, 0);
    SetupBg(3, 0, 30, 0);
#endif
    SetBgPriority(0, 0);
    SetBgPriority(1, 1);
    SetBgPriority(2, 2);
    SetBgPriority(3, 3);
    FadeStartIn(FADE_MODE_BLACK, 16);
    ListPoolInit(&w->pool);
    TaskPoolInit(&w->taskpool, 286);
    TaskPoolInit(&w->cardpool, 1);
    w->deckIndex = GetActiveDeckIndex();
    CreateDeckGridCards(w, 0);
    w->tiles = AllocObjTiles(0x120, NULL);
    SetObjTileSource(w->tiles, gUnk_090A4664);
    AnimInit(&w->anim2, gUnk_09EEB03C, gUnk_09EEB008);
    AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim2);
    w->x = sDeckTabPointerX[0] << 8;
    w->y = sDeckTabPointerY[0] << 8;
    w->handFlags = 0;
#ifdef VERSION_EU
    w->tiles4 = LoadObjTiles(gUnk_090A44C4, 32);
#else
    w->tiles4 = LoadObjTiles(gUnk_090A44C4, 32);
#endif
    w->palette = LoadObjPalette(gUnk_09614418, 32);
#ifdef VERSION_EU
    w->tiles5 = LoadObjTiles(gDeckButtonLabelTiles[gLanguage], sDeckButtonLabelTileSizes[gLanguage]);
#else
    w->tiles5 = LoadObjTiles(gUnk_090A1FB2, 0x280);
#endif
#ifdef VERSION_EU
    w->gfx7 = gDeckButtonLabelSprites[gLanguage][0];
    w->gfx8 = gDeckButtonLabelSprites[gLanguage][1];
#else
    w->gfx7 = gUnk_09EEAFD4[0];
    w->gfx8 = gUnk_09EEAFD4[1];
#endif
    w->tiles2 = AllocObjTiles(0x280, NULL);
    SetDeckMenuFrameCursor(w, 0);
    w->palette4 = LoadObjPalette(gUnk_09614438, 32);
    gCardUiSpriteState.tiles = AllocObjTiles(0x100, NULL);
    gCardUiSpriteState.palette = LoadObjPalette(gCard00Palette, 32);
    SetObjTileSource(gCardUiSpriteState.tiles, gUnk_0908C3CE);
    AnimInit(&gCardUiSpriteState.anim, gUnk_09EEA198, gUnk_09EEA180);
    AnimStart(&gCardUiSpriteState.anim, 0, ANIM_FLAG_LOOP);
    gCardUiSpriteState.gfx = AnimUpdate(&gCardUiSpriteState.anim);
    w->tiles10 = NULL;
    w->tiles7 = NULL;
    w->tiles8 = NULL;
    w->tiles9 = NULL;
    w->palette5 = NULL;
    w->palette6 = NULL;
    w->tiles3 = NULL;
    w->palette2 = NULL;
    w->tiles12 = NULL;
    w->tiles6 = NULL;
    w->palette3 = NULL;
    w->cursorCol = 0;
    w->cursorRow = 0;
    w->prevCursor[0] = 0;
    w->prevCursor[1] = 0;
    w->timer = 16;
    w->commandCursor = 0;
    w->cursorCard = NULL;
    w->prevCursorCard = NULL;
    w->mode = 0;
    w->view = 0;
    w->deckAttackCount = CountActiveDeckCardsOfCategory(0);
    w->deckMagicCount = CountActiveDeckCardsOfCategory(1);
    w->deckItemCount = CountActiveDeckCardsOfCategory(2);
    w->deckEnemyCount = CountActiveDeckCardsOfCategory(3);
    w->categoryFilter = 0;
    w->entryCount = 0;
    w->entries = NULL;
    w->popupActive = 0;
    w->exitRequested = 0;
    w->barSlideTimer = 16;
    w->bannerSlideTimer = 16;
    w->x5 = 0x7800;
    w->y5 = -0x800;
    w->x6 = 0xA400;
    w->y6 = 0xA000;
    w->x7 = -0x8000;
    w->holding = 0;
    w->handVisible = 0;
    w->removeLabelX = 95;
    w->removeLabelY = -2;
    w->addLabelX = 135;
    w->addLabelY = -2;
    w->inputDelay = 0;
    w->textSlotCount = 0;
    w->textSlotCount2 = 0;
    w->textSlotCount3 = 0;
    w->textSlotCount4 = 0;
    InitTextSlots(w->textSlots, 8);
    InitTextSlots(w->textSlots2, 8);
    InitTextSlots(w->textSlots3, 8);
    InitTextSlots(w->textSlots4, 30);
    InitTextSlots(w->textSlots5, 90);
    w->step = 0;
    w->result = 0;
}

static u8 Deckmenu2_1(DeckMenuWork* w, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 16);

    if (w->step == 0) {
        RequestDma3Clear(GetBgCharBase(0), 0x2000);
    }

    if (w->step == 1) {
        RequestDma3Clear(GetBgCharBase(0) + 0x2000, 0x2000);
    }

    if (w->step == 2) {
        RequestDma3Clear(GetBgCharBase(1), 0x2000);
    }

    if (w->step == 3) {
        RequestDma3Clear(GetBgCharBase(1) + 0x2000, 0x2000);
    }

    if (w->step == 4) {
        RequestDma3Clear(GetBgCharBase(2), 0x2000);
    }

    if (w->step == 5) {
        RequestDma3Clear(GetBgCharBase(2) + 0x2000, 0x2000);
    }

    if (w->step == 6) {
        RequestDma3Clear(GetBgCharBase(3), 0x2000);
    }

    if (w->step == 7) {
        RequestDma3Clear(GetBgCharBase(3) + 0x2000, 0x2000);
    }

    w->step++;

    if (w->step == 8) {
        w->step = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuLoadBgs);
    }

    return 1;
}

u8 UpdateDeckMenuLoadDeckInfo(DeckMenuWork* w, void* a);

u8 UpdateDeckMenuLoadBgs(DeckMenuWork* w, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 16);

    switch (w->step) {
    case 0:
        LoadBgTiles(3, gUnk_09402F78, 0x2000);
        LoadBgPalette(3, gUnk_09614118, 0x1E0);
        break;
    case 1:
#ifdef VERSION_EU
        RequestDma3Copy(&gUnk_09402F78[0x2000],
                        (u8*)GetBgCharBase(3) + 0x2000, 0x1800);
#else
        RequestDma3Copy(&gUnk_09402F78[0x2000],
                        (u8*)GetBgCharBase(3) + 0x2000, 0x2000);
#endif
        break;
    case 2:
#ifdef VERSION_EU
        LoadBgMap(3, gUnk_095132B8, 0x800);
#else
        LoadBgMap(3, gUnk_09516AB8, 0x800);
#endif
        break;
    case 3:
#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            RequestDma3Copy(gUnkEu_094E04E4, (u8*)GetBgCharBase(3) + 0x3800, 0x1C00);
            break;
        case LANGUAGE_FRENCH:
            RequestDma3Copy(gUnkEu_094E20E4, (u8*)GetBgCharBase(3) + 0x3800, 0x1C00);
            break;
        case LANGUAGE_GERMAN:
            RequestDma3Copy(gUnkEu_094E74E4, (u8*)GetBgCharBase(3) + 0x3800, 0x1C00);
            break;
        case LANGUAGE_ITALIAN:
            RequestDma3Copy(gUnkEu_094E58E4, (u8*)GetBgCharBase(3) + 0x3800, 0x1C00);
            break;
        case LANGUAGE_SPANISH:
            RequestDma3Copy(gUnkEu_094E3CE4, (u8*)GetBgCharBase(3) + 0x3800, 0x1C00);
            break;
        }
#else
        LoadBgTiles(0, gUnk_09406F78, 0xC00);
#endif
        break;
    case 4:
        LoadBgMap(0, gUnk_08125E24, 0x800);
        break;
#ifndef VERSION_EU
    case 5:
        LoadBgTiles(1, &gUnk_09406F78[0xC00], 0x2000);
        break;
    case 6:
        RequestDma3Copy(&gUnk_09406F78[0x2C00],
                        (u8*)GetBgCharBase(1) + 0x2000, 0x1E20);
        break;
#endif
    case 7:
        LoadBgMap(1, gUnk_08125E24, 0x800);
        break;
#ifndef VERSION_EU
    case 8:
        LoadBgTiles(2, &gUnk_09406F78[0x4A20], 0x2000);
        break;
    case 9:
        RequestDma3Copy(&gUnk_09406F78[0x6A20],
                        (u8*)GetBgCharBase(2) + 0x2000, 0x1E20);
        break;
#endif
    case 10:
        LoadBgMap(2, gUnk_08125E24, 0x800);
        break;
    case 11:
        SetBgScroll(0, (u16)-88, (u16)-16);
        SetBgScroll(1, (u16)-88, (u16)-64);
        SetBgScroll(2, (u16)-88, (u16)-112);
        w->step = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuLoadDeckInfo);
        return 1;
    }

    w->step++;
    return 1;
}

u8 UpdateDeckMenuLoadDeckInfo(DeckMenuWork* w, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 16);

    switch (w->step) {
    case 0:
        LoadBgMap(0, gUnk_09519AB8, 0x180);
        LoadBgMap(1, gUnk_0951A2B8, 0x180);
        LoadBgMap(2, gUnk_0951AAB8, 0x180);
        w->step++;
        break;
    case 1:
        DrawDeckCategoryCount(w->deckAttackCount, 0);
        DrawDeckCategoryCount(w->deckMagicCount, 1);
        DrawDeckCategoryCount(w->deckItemCount, 2);
        DrawDeckCategoryCount(w->deckEnemyCount, 3);
        HighlightDeckTab(w, w->deckIndex);
        w->step++;
        break;
    case 2:
        DrawDeckCardCount(0);
        DrawDeckCardCount(1);
        DrawDeckCardCount(2);
        w->step++;
        break;
    case 3:
        DrawDeckCpCost(0);
        DrawDeckCpCost(1);
        DrawDeckCpCost(2);
        w->step++;
        break;
    case 4:
        DrawDeckEquipMarker(GetActiveDeckIndex());
        DrawCardTotals();
        w->x2 = 0x4800;
        w->y2 = 0x2800;
        w->cursorRow = w->deckIndex;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuSlideIn);
        w->view = 1;
        SetDeckMenuHandAnim(w);
        LoadDeckNameTexts(w);
        w->x = sDeckTabPointerX[w->cursorCol] << 8;
        w->y = sDeckTabPointerY[w->cursorRow] << 8;
        w->tiles6 = LoadObjTiles(gUnk_090A583E, 0x620);
#ifdef VERSION_EU
        w->tiles12 = LoadObjTiles(gDeckTitleBannerTiles[gLanguage], sDeckTitleBannerTileSizes[gLanguage]);
#elif defined(VERSION_US)
        if (gGameState.flags & GAME_FLAG_RIKU) {
            w->tiles12 = LoadObjTiles(gUnk_090A418E, 0x320);
        } else {
            w->tiles12 = LoadObjTiles(gUnk_090A3E46, 0x320);
        }
#else
        w->tiles12 = LoadObjTiles(gUnk_090A418E, 0x320);
#endif
        w->palette3 = LoadObjPalette(gUnk_096144F8, 32);
        w->step = 0;
        w->timer = 16;
        return 1;
    }

    return 1;
}

u8 UpdateDeckMenuSlideIn(DeckMenuWork* w, void* a) {
    w->gfx = AnimUpdate(&w->anim2);
    w->gfx2 = AnimUpdate(&w->anim3);

    if (!FadeIsActive()) {
        switch (w->step) {
        case 0:
            ApproachValue(&w->y5, 0, w->timer);
            ApproachValue(&w->y6, 0x9800, w->timer);
            w->timer--;

            if (w->timer == 0) {
                w->timer = 16;
                w->step++;
            }

            break;
        case 1:
            ApproachValue(&w->x7, 0, w->timer);
            w->timer--;

            if (w->timer == 0) {
                ReleaseObjTiles(w->tiles6);
                ReleaseObjTiles(w->tiles12);
                ReleaseObjPalette(w->palette3);
                w->tiles6 = NULL;
                w->tiles12 = NULL;
                w->palette3 = NULL;
                w->handVisible = 1;
                LoadBgMap(3, gUnk_09512AB8, 0x800);
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckSelect);
            }

            break;
        }
    }

    return 1;
}

u8 UpdateDeckMenuEnterDeckGrid(DeckMenuWork* w, void* a) {
    LoadDeckNameTexts(w);
    ApproachValueHalf(&w->x, gDeckGridColumnX[w->cursorCol] << 8);
    ApproachValueHalf(&w->y, gDeckGridRowY[w->cursorRow] << 8);
    w->timer--;

    if (w->timer == 0) {
        w->view = 0;
        SetDeckMenuHandAnim(w);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckGrid);
    }

    return 1;
}

u8 UpdateDeckMenuDeckGrid(DeckMenuWork* w, void* a) {
    w->gfx = AnimUpdate(&w->anim2);
    w->gfx2 = AnimUpdate(&w->anim3);

    if (FadeIsActive()) {
        TaskPoolUpdate(&w->taskpool);
        return 1;
    }

    if (w->popupActive != 0) {
        ApproachValueHalf(&w->x, gDeckGridColumnX[w->cursorCol] << 8);
        ApproachValueHalf(&w->y, gDeckGridRowY[w->cursorRow] << 8);

        if (w->timer != 0) {
            w->timer--;
        }

        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            w->exitRequested = 1;
            w->result = 7;
        }

        w->inputDelay = 4;
        return 1;
    }

    if (w->inputDelay > 0) {
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);
        w->inputDelay--;
        return 1;
    }

    if (w->exitRequested) {
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        } else {
            w->exitRequested = 0;
        }
    }

    switch (GetKeysRepeat()) {
    case DPAD_UP:
        if (w->cursorRow > 0) {
            w->cursorRow--;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        } else {
            if (!ScrollGridUp(w, 1)) {
                if (!w->holding) {
                    w->cursorCol = w->categoryFilter;
                    w->timer = 1;
                    m4aSongNumStart(SONG_SYS_CLICKI04B);
                    w->prevView = w->view;
                    w->view = 2;
                    AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
                    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckFilter);
                    DrawCpCost(0);
                    return 1;
                }
            } else {
                if (w->holding) {
                    w->heldRow++;

                    if ((u16)w->heldRow <= 3) {
                        w->y3 = gDeckGridRowY[w->heldRow] << 8;
                    } else {
                        w->y3 = -0x10000;
                    }
                }
            }
        }

        break;
    case DPAD_DOWN:
        if (w->cursorRow <= 2) {
            w->cursorRow++;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        } else {
            ScrollGridDown(w);

            if (w->holding) {
                if ((u16)w->heldRow <= 3) {
                    w->y3 = gDeckGridRowY[w->heldRow] << 8;
                } else {
                    w->y3 = -0x10000;
                }
            }
        }

        break;
    case DPAD_LEFT:
        if (w->cursorCol > 0) {
            w->cursorCol--;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        break;
    case DPAD_RIGHT:
        if (w->cursorCol > 1) {
            if (!w->holding) {
                w->cursorCol = 0;
                w->cursorRow = w->deckIndex;
                w->timer = 1;
                w->prevView = w->view;
                w->view = 1;
                SetDeckMenuHandAnim(w);
                m4aSongNumStart(SONG_SYS_CLICK);
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckSelect);
                return 1;
            }
        } else {
            w->cursorCol++;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        break;
    }

    switch (GetKeysPressed()) {
    case B_BUTTON:
        if (!w->holding) {
            w->cursorCol = 0;
            w->cursorRow = w->deckIndex;
            w->timer = 1;
            w->prevView = w->view;
            w->view = 1;
            SetDeckMenuHandAnim(w);
            m4aSongNumStart(SONG_SYS_CLICK);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckSelect);
            return 1;
        } else {
            m4aSongNumStart(SONG_SYS_CLOSE);
            w->holding = 0;
            AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
            return 1;
        }
    case A_BUTTON:
        if (w->categoryFilter != 0) {
            return 1;
        }

        if (!w->holding) {
            m4aSongNumStart(SONG_SYS_KETEI2);
            w->holding = 1;
            w->heldCol = w->cursorCol;
            w->heldRow = w->cursorRow;
            w->x3 = gDeckGridColumnX[w->heldCol] << 8;
            w->y3 = gDeckGridRowY[w->heldRow] << 8;
            AnimStart(&w->anim2, 4, ANIM_FLAG_LOOP);
        } else {
            if (SwapHeldDeckCard(w)) {
                m4aSongNumStart(SONG_SYS_KETEI2);
                w->holding = 0;
                AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        }

        return 1;
    case START_BUTTON:
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CLOSE);
            w->result = 7;
        }

        return 1;
    case L_BUTTON:
        m4aSongNumStart(SONG_SYS_CANSEL);
        w->holding = 0;
        AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenRemoveMode);
        return 1;
    case R_BUTTON:
        FreeCollectionEntries(w);
        m4aSongNumStart(SONG_SYS_CANSEL);
        w->holding = 0;
        AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenAddMode);
        return 1;
    }

    if (GetKeysPressed() & SELECT_BUTTON) {
        w->holding = 0;
        w->cursorRow = 0;
        w->scrollRowEnd = 4;
        ResetGridScroll(w);
        w->x2 = 0x4800;
        w->y2 = 0x2800;
        w->cursorCol = w->categoryFilter;
        w->timer = 1;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
        w->view = 2;
        AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckFilter);
        DrawCpCost(0);
        return 1;
    }

    w->cursorCard = GetCardAtCursor(w);
    ApproachValueHalf(&w->x, gDeckGridColumnX[w->cursorCol] << 8);
    ApproachValueHalf(&w->y, gDeckGridRowY[w->cursorRow] << 8);

    if (w->timer != 0) {
        w->timer--;
    }

    w->prevCursorCard = w->cursorCard;
    w->prevCursor[0] = w->cursorCol;
    w->prevCursor[1] = w->cursorRow;
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuDeckFilter(DeckMenuWork* w, void* a) {
    w->gfx = AnimUpdate(&w->anim2);

    if (w->popupActive != 0) {
        ApproachValueHalf(&w->x, sDeckFilterTabX[w->cursorCol] << 8);
        ApproachValueHalf(&w->y, 0x1E00);
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            w->result = 7;
            w->exitRequested = 1;
        }

        w->inputDelay = 4;
        return 1;
    }

    if (w->exitRequested) {
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        w->exitRequested = 0;
    }

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
        if (w->cursorCol > 0) {
            w->cursorCol--;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICK);
            w->categoryFilter = w->cursorCol;
            DrawDeckFilterTab(w->categoryFilter, w->mode);
            ClearCardGrid(w);
            CreateDeckGridCards(w, w->categoryFilter);
        }

        break;
    case DPAD_RIGHT:
        if (w->cursorCol < 4) {
            w->cursorCol++;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICK);
            w->categoryFilter = w->cursorCol;
            DrawDeckFilterTab(w->categoryFilter, w->mode);
            ClearCardGrid(w);
            CreateDeckGridCards(w, w->categoryFilter);
        }

        break;
    }

    switch (GetKeysPressed()) {
    case B_BUTTON:
    case DPAD_DOWN:
        w->cursorCol = 0;
        w->cursorRow = 0;
        w->timer = 1;
        m4aSongNumStart(SONG_SYS_CLICKI04B);

        if (w->view == 2) {
            w->view = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuEnterDeckGrid);
        }

        if (w->view == 8) {
            w->view = 7;
            ShowDeckCardPreview(w);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuRemoveGrid);
        }

        w->x2 = 0x4800;
        w->y2 = 0x2800;
        w->scrollRowEnd = 4;
        return 1;
    case R_BUTTON:
        FreeCollectionEntries(w);
        w->unk_8CA = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenAddMode);
        m4aSongNumStart(SONG_SYS_CANSEL);
        return 1;
    case L_BUTTON:
        if (w->view == 2) {
            m4aSongNumStart(SONG_SYS_CANSEL);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenRemoveMode);
        }

        return 1;
    case START_BUTTON:
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 16);
            w->result = 7;
        }

        return 1;
    }

    ApproachValueHalf(&w->x, sDeckFilterTabX[w->cursorCol] << 8);
    ApproachValueHalf(&w->y, 0x1E00);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuDeletePrompt(DeckMenuWork* w, void* a) {
    PromptChoiceLayout table = sDeckPromptChoiceLayout;

    w->gfx = AnimUpdate(&w->anim2);
    w->gfx2 = AnimUpdate(&w->anim3);

    if (GetKeysPressed() & DPAD_LEFT) {
        if (w->promptChoice != 0) {
            w->promptChoice--;
        }

        w->timer = 1;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysPressed() & DPAD_RIGHT) {
        if (w->promptChoice == 0) {
            w->promptChoice++;
        }

        w->timer = 1;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysPressed() & A_BUTTON) {
        if (w->promptChoice == 1) {
            w->timer = 1;
            w->view = 11;
            SetDeckMenuHandAnim(w);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteValueSelect);
            TaskPoolUpdate(&w->taskpool);
            TaskPoolUpdate(&w->cardpool);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        w->timer = 1;
        DeleteSelectedValueCard(w);
        DrawCardTotals();
        CountCardsNotInDeckByCategory(3, w->collectionCategoryCounts);
        DrawCollectionCategoryCount(w->collectionCategoryCounts[0], 0);
        DrawCollectionCategoryCount(w->collectionCategoryCounts[1], 1);
        DrawCollectionCategoryCount(w->collectionCategoryCounts[2], 2);
        DrawCollectionCategoryCount(w->collectionCategoryCounts[3], 3);

        if (!(u8)MoveValueCursor(w, 0)) {
            RemoveEmptyCollectionEntry(w, 1);

            if (w->gridEntryCount != 0) {
                SetDeckMenuFrameCursor(w, 0);
                w->cursorCol = w->savedCol;
                w->cursorRow = w->savedRow;

                while (!(u8)IsCardAtCursor(w)) {
                    w->cursorCol--;

                    if (w->cursorCol < 0) {
                        w->cursorRow--;

                        if (w->cursorRow < 0) {
                            ScrollGridUp(w, 0);
                            w->cursorRow = 0;
                        }

                        w->cursorCol = 2;
                    }
                }

                w->x = gCollectionGridColumnX[w->cursorCol] << 8;
                w->y = gCollectionGridRowY[w->cursorRow] << 8;
                ShowCollectionCardPreview(w);
                w->view = 9;
                SetDeckMenuHandAnim(w);
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteGrid);
                TaskPoolUpdate(&w->taskpool);
                TaskPoolUpdate(&w->cardpool);
                return 1;
            } else {
                SetDeckMenuFrameCursor(w, 0);
                w->cursorCol = w->categoryFilter;
                w->timer = 1;
                w->view = 10;
                SetDeckMenuHandAnim(w);
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
                w->gridEntryCount = 0;
                TaskPoolUpdate(&w->taskpool);
                TaskPoolUpdate(&w->cardpool);
                return 1;
            }
        } else {
            DrawSelectedValueCpCost(w);
            w->view = 11;
            SetDeckMenuHandAnim(w);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteValueSelect);
            TaskPoolUpdate(&w->taskpool);
            TaskPoolUpdate(&w->cardpool);
            return 1;
        }
    } else if (GetKeysPressed() & B_BUTTON) {
        w->timer = 1;
        w->view = 11;
        SetDeckMenuHandAnim(w);
        m4aSongNumStart(SONG_SYS_CANSEL);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteValueSelect);
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);
        return 1;
    } else {
        ApproachValueHalf(&w->x, table.x[w->promptChoice] << 8);
        ApproachValueHalf(&w->y, 0x7200);
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);
        return 1;
    }
}

u8 UpdateDeckMenuDeleteValueSelect(DeckMenuWork* w, void* a) {
    s8 n;
    s16 v;

    if (w->popupActive != 0) {
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            w->result = 7;
            w->exitRequested = 1;
        }

        w->inputDelay = 8;
        return 1;
    }

    if (w->exitRequested) {
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        w->exitRequested = 0;
    }

    w->gfx = AnimUpdate(&w->anim2);
    w->gfx2 = AnimUpdate(&w->anim3);

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
    case (DPAD_LEFT | DPAD_UP):
    case (DPAD_LEFT | DPAD_DOWN):
        if (w->cursorCol > 0) {
            w->cursorCol--;
            w->timer = 1;

            if ((u8)MoveValueCursor(w, 32)) {
                m4aSongNumStart(SONG_SYS_CLICK);
            }
        }

        DrawSelectedValueCpCost(w);
        break;
    case DPAD_RIGHT:
    case (DPAD_RIGHT | DPAD_UP):
    case (DPAD_RIGHT | DPAD_DOWN):
        if (w->cursorCol <= 0) {
            w->cursorCol++;
            w->timer = 1;

            if ((u8)MoveValueCursor(w, 16)) {
                m4aSongNumStart(SONG_SYS_CLICK);
            }
        }

        DrawSelectedValueCpCost(w);
        break;
    case DPAD_UP:
        n = w->cursorRow;

        if (w->cursorRow > 0) {
            w->cursorRow = w->cursorRow - 1;
        } else {
            w->cursorRow = 4;
        }

        w->timer = 1;
        MoveValueCursor(w, 64);

        if (n != w->cursorRow) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        DrawSelectedValueCpCost(w);
        break;
    case DPAD_DOWN:
        n = w->cursorRow;

        if (w->cursorRow <= 3) {
            w->cursorRow = w->cursorRow + 1;
        } else {
            w->cursorRow = 0;
        }

        w->timer = 1;
        MoveValueCursor(w, 128);

        if (n != w->cursorRow) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        DrawSelectedValueCpCost(w);
        break;
    }

    switch (GetKeysPressed()) {
    case B_BUTTON:
        SetDeckMenuFrameCursor(w, 0);
        v = w->savedCol;
        w->cursorCol = v;
        v = w->savedRow;
        w->cursorRow = v;
        w->x = gCollectionGridColumnX[w->cursorCol] << 8;
        w->y = gCollectionGridRowY[w->cursorRow] << 8;
        ShowCollectionCardPreview(w);
        w->view = 9;
        m4aSongNumStart(SONG_SYS_CLOSE);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteGrid);
        return 1;
    case A_BUTTON:
        if (w->inputDelay > 0) {
            return 1;
        }

        if (!CheckCardDeletable(w)) {
            return 1;
        }

        TaskCreate(&w->cardpool, &gTaskDescDeckYesNo, &w->popupActive);
        w->promptChoice = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeletePrompt);
        w->timer = 1;
        w->view = 12;
        m4aSongNumStart(SONG_SYS_CLOSE);
        SetDeckMenuHandAnim(w);
        return 1;
    case START_BUTTON:
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CLOSE);
            w->result = 7;
        }

        return 1;
    }

    ApproachValueHalf(&w->x, sValueGridX[w->cursorCol] << 8);
    ApproachValueHalf(&w->y, (sValueGridY[w->cursorRow] - 16) << 8);

    if (w->inputDelay > 0) {
        w->inputDelay--;
    }

    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

void RemoveEmptyCollectionEntry(DeckMenuWork* w, u8 mode) {
    DeckCard2Work* node;
    DeckCard2Work* p;
    CardKindEntry* e;
    s32 i;

    node = ListPoolFirst(&w->pool);
    i = 0;
    e = &w->entries[w->entryIndex];
    EwramFree(w->entries[w->entryIndex].indices);
    w->entries[w->entryIndex].indices = NULL;

    for (i = w->entryIndex; i < w->entryCount - 1; i++) {
        w->entries[i] = w->entries[i + 1];
    }

    w->entryCount -= 1;
    w->gridEntryCount -= 1;

    while (node != NULL) {
        if (node->args.col == w->savedCol && node->args.row == w->savedRow) {
            break;
        }

        node = ListPoolNext(&node->node);
    }

    p = ListPoolNext(&node->node);

    while (p != NULL) {
        p->args.col--;

        if (p->args.col < 0) {
            p->args.col = 2;
            p->args.row--;
        }

        p = ListPoolNext(&p->node);
    }

    node->done = 1;
    TaskPoolUpdate(&w->taskpool);
    ShowCollectionCardPreview(w);
#ifdef VERSION_EU
    SetGridRowCount(w, w->gridEntryCount);
#else
    SetGridRowCount(w, w->entryCount);
#endif
    UpdateGridScrollBar(w);
}

u8 UpdateDeckMenuAddValueSelect(DeckMenuWork* w, void* a) {
    s8 n;

    if (w->popupActive != 0) {
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            w->result = 7;
            w->exitRequested = 1;
        }

        return 1;
    }

    if (w->exitRequested) {
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        w->exitRequested = 0;
    }

    w->gfx = AnimUpdate(&w->anim2);
    w->gfx2 = AnimUpdate(&w->anim3);

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
    case (DPAD_LEFT | DPAD_UP):
    case (DPAD_LEFT | DPAD_DOWN):
        if (w->cursorCol > 0) {
            w->cursorCol--;
            w->timer = 1;

            if ((u8)MoveValueCursor(w, 32)) {
                m4aSongNumStart(SONG_SYS_CLICK);
            }
        }

        DrawSelectedValueCpCost(w);
        break;
    case DPAD_RIGHT:
    case (DPAD_RIGHT | DPAD_UP):
    case (DPAD_RIGHT | DPAD_DOWN):
        if (w->cursorCol <= 0) {
            w->cursorCol++;
            w->timer = 1;

            if ((u8)MoveValueCursor(w, 16)) {
                m4aSongNumStart(SONG_SYS_CLICK);
            }
        }

        DrawSelectedValueCpCost(w);
        break;
    case DPAD_UP:
        n = w->cursorRow;

        if (w->cursorRow > 0) {
            w->cursorRow = w->cursorRow - 1;
        } else {
            w->cursorRow = 4;
        }

        w->timer = 1;
        MoveValueCursor(w, 64);

        if (n != w->cursorRow) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        DrawSelectedValueCpCost(w);
        break;
    case DPAD_DOWN:
        n = w->cursorRow;

        if (w->cursorRow <= 3) {
            w->cursorRow = w->cursorRow + 1;
        } else {
            w->cursorRow = 0;
        }

        w->timer = 1;
        MoveValueCursor(w, 128);

        if (n != w->cursorRow) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        DrawSelectedValueCpCost(w);
        break;
    }

    switch (GetKeysPressed()) {
    case B_BUTTON:
        SetDeckMenuFrameCursor(w, 0);
        n = w->savedCol;
        w->cursorCol = n;
        n = w->savedRow;
        w->cursorRow = n;
        w->x = gCollectionGridColumnX[w->cursorCol] << 8;
        w->y = gCollectionGridRowY[w->cursorRow] << 8;
        ShowCollectionCardPreview(w);
        DrawCpCost(0);
        w->view = 4;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuAddGrid);
        m4aSongNumStart(SONG_SYS_CLOSE);
        return 1;
    case A_BUTTON:
        if (GetDeckCardCount(w->deckIndex) <= 98) {
            AddSelectedValueCardToDeck(w);
            DrawDeckCardCount(w->deckIndex);
            DrawDeckCpCost(w->deckIndex);
            w->deckAttackCount = CountDeckCardsOfCategory(0, w->deckIndex);
            w->deckMagicCount = CountDeckCardsOfCategory(1, w->deckIndex);
            w->deckItemCount = CountDeckCardsOfCategory(2, w->deckIndex);
            w->deckEnemyCount = CountDeckCardsOfCategory(3, w->deckIndex);
            DrawDeckCategoryCount(w->deckAttackCount, 0);
            DrawDeckCategoryCount(w->deckMagicCount, 1);
            DrawDeckCategoryCount(w->deckItemCount, 2);
            DrawDeckCategoryCount(w->deckEnemyCount, 3);
            DrawCardTotals();
            CountCardsNotInDeckByCategory(w->deckIndex, w->collectionCategoryCounts);
            DrawCollectionCategoryCount(w->collectionCategoryCounts[0], 0);
            DrawCollectionCategoryCount(w->collectionCategoryCounts[1], 1);
            DrawCollectionCategoryCount(w->collectionCategoryCounts[2], 2);
            DrawCollectionCategoryCount(w->collectionCategoryCounts[3], 3);
            w->timer = 1;

            if (!(u8)MoveValueCursor(w, 0)) {
                RemoveEmptyCollectionEntry(w, 0);

                if (w->gridEntryCount != 0) {
                    u8 ready;
                    SetDeckMenuFrameCursor(w, 0);
                    w->cursorCol = w->savedCol;
                    w->cursorRow = w->savedRow;

                    while ((ready = IsCardAtCursor(w)) == 0) {
                        if (--w->cursorCol < 0) {
                            if (--w->cursorRow < 0) {
                                ScrollGridUp(w, 0);
                                w->cursorRow = ready;
                            }

                            w->cursorCol = 2;
                        }
                    }

                    w->x = gCollectionGridColumnX[w->cursorCol] << 8;
                    w->y = gCollectionGridRowY[w->cursorRow] << 8;
                    ShowCollectionCardPreview(w);
                    w->view = 4;
                    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuAddGrid);
                    return 1;
                } else {
                    SetDeckMenuFrameCursor(w, 0);
                    w->cursorCol = w->categoryFilter;
                    w->timer = 1;
                    w->view = 6;
                    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
                    w->gridEntryCount = 0;
                    return 1;
                }
            } else {
                DrawSelectedValueCpCost(w);
            }
        } else {
            m4aSongNumStart(SONG_SYS_BEEP);
            TaskCreate(&w->cardpool, &gTaskDescDeckErrorDeckFull, &w->popupActive);
            return 1;
        }

        break;
    case L_BUTTON:
        FreeCollectionEntries(w);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenRemoveMode);
        m4aSongNumStart(SONG_SYS_CANSEL);
        return 1;
    case START_BUTTON:
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CLOSE);
            w->result = 7;
        }

        return 1;
    }

    ApproachValueHalf(&w->x, sValueGridX[w->cursorCol] << 8);
    ApproachValueHalf(&w->y, sValueGridY[w->cursorRow] << 8);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuCollectionFilter(DeckMenuWork* w, void* a) {
    u16 i;
    u16 n;

    w->gfx = AnimUpdate(&w->anim2);

    if (w->popupActive != 0) {
        ApproachValueHalf(&w->x, sCollectionFilterTabX[w->cursorCol] << 8);
        ApproachValueHalf(&w->y, 0x1E00);
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            w->result = 7;
            w->exitRequested = 1;
        }

        return 1;
    }

    if (w->exitRequested) {
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        w->exitRequested = 0;
    }

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
        if (w->cursorCol > 1) {
            w->cursorCol--;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICK);
            n = w->cursorCol;
            w->categoryFilter = n;
            DrawCollectionFilterTab(w->categoryFilter, w->mode);
            ClearCardGrid(w);

            if (w->view == 6) {
                w->gridEntryCount = CreateCollectionGridCards(w, w->categoryFilter, 0);
            } else {
                w->gridEntryCount = CreateCollectionGridCards(w, w->categoryFilter, 1);
            }
        }

        for (i = 0; i <= 9; i++) {
            DrawValueCount(0, i);
        }

        break;
    case DPAD_RIGHT:
        if (w->cursorCol <= 4) {
            w->cursorCol++;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICK);
            n = w->cursorCol;
            w->categoryFilter = n;
            DrawCollectionFilterTab(w->categoryFilter, w->mode);
            ClearCardGrid(w);

            if (w->view == 6) {
                w->gridEntryCount = CreateCollectionGridCards(w, w->categoryFilter, 0);
            } else {
                w->gridEntryCount = CreateCollectionGridCards(w, w->categoryFilter, 1);
            }
        }

        for (i = 0; i <= 9; i++) {
            DrawValueCount(0, i);
        }

        break;
    case DPAD_DOWN:
        if (w->gridEntryCount != 0) {
            w->cursorCol = 0;
            w->cursorRow = 0;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            ShowCollectionCardPreview(w);

            if (w->view == 6) {
                w->view = 4;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuAddGrid);
            }

            if (w->view == 10) {
                w->view = 9;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteGrid);
            }
        } else {
            m4aSongNumStart(SONG_SYS_BEEP);
        }

        w->x2 = 0xA000;
        w->y2 = 0x2800;
        w->scrollRowEnd = 4;
        return 1;
    case B_BUTTON:
        if (w->gridEntryCount != 0) {
            w->cursorCol = 0;
            w->cursorRow = 0;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            ShowCollectionCardPreview(w);

            if (w->view == 6) {
                w->view = 4;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuAddGrid);
            }

            if (w->view == 10) {
                w->view = 9;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteGrid);
            }
        } else {
            m4aSongNumStart(SONG_SYS_CANSEL);

            if (w->view == 6) {
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseAddMode);
            }

            if (w->view == 10) {
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseDeleteMode);
            }
        }

        w->x2 = 0xA000;
        w->y2 = 0x2800;
        w->scrollRowEnd = 4;
        return 1;
    case L_BUTTON:
        if (w->view == 6) {
            FadeStartIn(FADE_MODE_BLACK, 1);
            FreeCollectionEntries(w);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenRemoveMode);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        break;
    case START_BUTTON:
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CLOSE);
            w->result = 7;
        }

        return 1;
    }

    ApproachValueHalf(&w->x, sCollectionFilterTabX[w->cursorCol] << 8);
    ApproachValueHalf(&w->y, 0x1E00);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuClearPrompt(DeckMenuWork* w, void* a) {
    PromptChoiceLayout tbl;

    tbl = sDeckPromptChoiceLayout;
    w->gfx = AnimUpdate(&w->anim2);
    w->gfx2 = AnimUpdate(&w->anim3);

    if (GetKeysPressed() & DPAD_LEFT) {
        if (w->promptChoice != 0) {
            w->promptChoice--;
        }

        w->timer = 1;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysPressed() & DPAD_RIGHT) {
        if (w->promptChoice == 0) {
            w->promptChoice++;
        }

        w->timer = 1;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysPressed() & A_BUTTON) {
        if (w->promptChoice == 1) {
            w->timer = 1;
            w->view = 3;
            SetDeckMenuHandAnim(w);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCommands);
            TaskPoolUpdate(&w->taskpool);
            TaskPoolUpdate(&w->cardpool);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        m4aSongNumStart(SONG_SYS_KETTEI);
        ClearDeck(w->deckIndex);
        DrawDeckCardCount(w->deckIndex);
        DrawDeckCpCost(w->deckIndex);
        DrawCardTotals();
        w->deckAttackCount = CountDeckCardsOfCategory(0, w->deckIndex);
        w->deckMagicCount = CountDeckCardsOfCategory(1, w->deckIndex);
        w->deckItemCount = CountDeckCardsOfCategory(2, w->deckIndex);
        w->deckEnemyCount = CountDeckCardsOfCategory(3, w->deckIndex);
        DrawDeckCategoryCount(w->deckAttackCount, 0);
        DrawDeckCategoryCount(w->deckMagicCount, 1);
        DrawDeckCategoryCount(w->deckItemCount, 2);
        DrawDeckCategoryCount(w->deckEnemyCount, 3);
        ClearCardGrid(w);
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);
        w->timer = 1;
        w->view = 3;
        SetDeckMenuHandAnim(w);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCommands);
    }

    if (GetKeysPressed() & B_BUTTON) {
        w->timer = 1;
        w->view = 3;
        SetDeckMenuHandAnim(w);
        m4aSongNumStart(SONG_SYS_CANSEL);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCommands);
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);
        return 1;
    }

    ApproachValueHalf(&w->x, tbl.x[w->promptChoice] << 8);
    ApproachValueHalf(&w->y, 0x7200);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuDeckSelect(DeckMenuWork* w, void* a) {
    w->gfx = AnimUpdate(&w->anim2);
    w->gfx2 = AnimUpdate(&w->anim3);

#ifdef VERSION_EU
    if (FadeIsActive()) {
        return 1;
    }
#endif

    if (w->popupActive != 0) {
        ApproachValueHalf(&w->x, sDeckTabPointerX[w->cursorCol] << 8);
        ApproachValueHalf(&w->y, sDeckTabPointerY[w->cursorRow] << 8);
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            w->result = 7;
            w->exitRequested = 1;
        }

        w->inputDelay = 4;
        return 1;
    }

    if (w->inputDelay > 0) {
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);
        w->inputDelay--;
        return 1;
    }

    if (w->exitRequested) {
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        } else {
            w->exitRequested = 0;
        }
    }

    switch (GetKeysRepeat()) {
    case DPAD_UP:
        if (w->cursorRow > 0) {
            w->cursorRow--;
            w->timer = 1;
            w->deckIndex = w->cursorRow;
            ClearCardGrid(w);
            CreateDeckGridCards(w, w->categoryFilter);
            w->deckAttackCount = CountDeckCardsOfCategory(0, w->deckIndex);
            w->deckMagicCount = CountDeckCardsOfCategory(1, w->deckIndex);
            w->deckItemCount = CountDeckCardsOfCategory(2, w->deckIndex);
            w->deckEnemyCount = CountDeckCardsOfCategory(3, w->deckIndex);
            DrawDeckCategoryCount(w->deckAttackCount, 0);
            DrawDeckCategoryCount(w->deckMagicCount, 1);
            DrawDeckCategoryCount(w->deckItemCount, 2);
            DrawDeckCategoryCount(w->deckEnemyCount, 3);
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        break;
    case DPAD_DOWN:
        if (w->cursorRow < 2) {
            w->cursorRow++;
            w->deckIndex = w->cursorRow;
            w->timer = 1;
            ClearCardGrid(w);
            CreateDeckGridCards(w, w->categoryFilter);
            w->deckAttackCount = CountDeckCardsOfCategory(0, w->deckIndex);
            w->deckMagicCount = CountDeckCardsOfCategory(1, w->deckIndex);
            w->deckItemCount = CountDeckCardsOfCategory(2, w->deckIndex);
            w->deckEnemyCount = CountDeckCardsOfCategory(3, w->deckIndex);
            DrawDeckCategoryCount(w->deckAttackCount, 0);
            DrawDeckCategoryCount(w->deckMagicCount, 1);
            DrawDeckCategoryCount(w->deckItemCount, 2);
            DrawDeckCategoryCount(w->deckEnemyCount, 3);
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        break;

    case DPAD_LEFT:
        if (w->cursorRow == 2) {
            w->cursorRow = 3;
        }

        w->cursorCol = 2;
        w->timer = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuEnterDeckGrid);
        m4aSongNumStart(SONG_SYS_CANSEL);
        return 1;
    }

    switch (GetKeysPressed()) {
    case A_BUTTON:
        w->timer = 1;
        w->prevView = w->view;
        m4aSongNumStart(SONG_SYS_CANSEL);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenCommands);
        return 1;
    case SELECT_BUTTON:
#ifndef VERSION_EU
        w->scrollRowEnd = 4;
#endif
        SetActiveDeckIndex(w->deckIndex);
        DrawDeckEquipMarker(w->deckIndex);
        TaskCreate(&w->cardpool, &gTaskDescDeckEquip, &w->popupActive);
        m4aSongNumStart(SONG_SYS_DECKSET);
        break;
    case B_BUTTON:
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuStartSlideOut);
            w->result = 8;
            m4aSongNumStart(SONG_SYS_CLOSE);
        }

        return 1;
    case START_BUTTON:
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CLOSE);
            w->result = 7;
        }

        return 1;
    case L_BUTTON:
        FreeCollectionEntries(w);
        m4aSongNumStart(SONG_SYS_CANSEL);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenRemoveMode);
        return 1;
    case R_BUTTON:
        FreeCollectionEntries(w);
        m4aSongNumStart(SONG_SYS_CANSEL);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenAddMode);
        return 1;
    }

    HighlightDeckTab(w, w->deckIndex);
    ApproachValueHalf(&w->x, sDeckTabPointerX[w->cursorCol] << 8);
    ApproachValueHalf(&w->y, sDeckTabPointerY[w->cursorRow] << 8);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuOpenCommands(DeckMenuWork* w, void* a) {
    u8* p;
    u8 z;

#ifdef VERSION_EU
    w->tiles3 = LoadObjTiles(gDeckCommandMenuTiles[gLanguage], sDeckCommandMenuTileSizes[gLanguage]);
#else
    w->tiles3 = LoadObjTiles(gUnk_090A261E, 0x1800);
#endif
    w->palette2 = LoadObjPalette(gUnk_096144D8, 32);
    SetDeckMenuFrameCursor(w, 1);
    p = &w->view;
    z = 0;
    *p = 3;
    w->commandCursor = z;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCommands);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuCommands(DeckMenuWork* w, void* a) {
    w->gfx = AnimUpdate(&w->anim2);
    w->gfx2 = AnimUpdate(&w->anim3);

    if (w->popupActive != 0) {
        w->view = 1;
        SetDeckMenuHandAnim(w);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseCommands);
    }

    switch (GetKeysRepeat()) {
    case DPAD_UP:
        if (w->commandCursor != 0) {
            w->commandCursor--;
        } else {
            w->commandCursor = 5;
        }

        m4aSongNumStart(SONG_SYS_CLICK);
        w->timer = 1;
        break;
    case DPAD_DOWN:
        if (w->commandCursor < 5) {
            w->commandCursor++;
        } else {
            w->commandCursor = 0;
        }

        w->timer = 1;
        m4aSongNumStart(SONG_SYS_CLICK);
        break;
    }

    switch (GetKeysPressed()) {
    case B_BUTTON:
        w->timer = 1;

        if (w->prevView == 0) {
            w->view = 0;
            SetDeckMenuHandAnim(w);
            SetDeckMenuFrameCursor(w, 0);
            m4aSongNumStart(SONG_SYS_CLOSE);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckGrid);
            ReleaseCommandMenuGfx(w);
        } else {
            w->view = 1;
            SetDeckMenuHandAnim(w);
            m4aSongNumStart(SONG_SYS_CLOSE);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseCommands);
        }

        break;
    case START_BUTTON:
        w->exitRequested = 1;
        w->timer = 1;

        if (w->prevView == 0) {
            w->view = 0;
            SetDeckMenuHandAnim(w);
            SetDeckMenuFrameCursor(w, 0);
            m4aSongNumStart(SONG_SYS_CLOSE);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckGrid);
            ReleaseCommandMenuGfx(w);
        } else {
            m4aSongNumStart(SONG_SYS_CLOSE);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseCommands);
            w->result = 7;
        }

        break;
    case A_BUTTON:
        switch (w->commandCursor) {
        case 0:
            SetActiveDeckIndex(w->deckIndex);
            DrawDeckEquipMarker(w->deckIndex);
            TaskCreate(&w->cardpool, &gTaskDescDeckEquip, &w->popupActive);
            m4aSongNumStart(SONG_SYS_DECKSET);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseCommands);
            return 1;
        case 1:
            m4aSongNumStart(SONG_SYS_KETTEI);
            ClearCardGrid(w);
            w->step = 0;
            ReleaseCommandMenuGfx(w);
#ifdef VERSION_EU
            FadeStartIn(FADE_MODE_BLACK, 16);
#endif
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenKeyboard);
            break;
        case 2:
            m4aSongNumStart(SONG_SYS_KETTEI);
            w->view = 15;
            TaskCreate(&w->cardpool, &gTaskDescDeckClear, &w->popupActive);
            w->promptChoice = 1;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuClearPrompt);
            return 1;
        case 3:
            m4aSongNumStart(SONG_SYS_KETTEI);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenAddMode);
            break;
        case 4:
            m4aSongNumStart(SONG_SYS_KETTEI);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenRemoveMode);
            break;
        case 5:
            m4aSongNumStart(SONG_SYS_KETTEI);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenDeleteMode);
            break;
        }

        break;
    }

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        ApproachValueHalf(&w->x, 0x6600);
        break;
    case LANGUAGE_FRENCH:
        ApproachValueHalf(&w->x, 0x6200);
        break;
    case LANGUAGE_GERMAN:
        ApproachValueHalf(&w->x, 0x5E00);
        break;
    case LANGUAGE_ITALIAN:
        ApproachValueHalf(&w->x, 0x6200);
        break;
    case LANGUAGE_SPANISH:
        ApproachValueHalf(&w->x, 0x5E00);
        break;
    default:
        ApproachValueHalf(&w->x, 0x6600);
        break;
    }
#else
    ApproachValueHalf(&w->x, 0x6600);
#endif
    ApproachValueHalf(&w->y, sDeckCommandY[w->commandCursor] << 8);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuCloseCommands(DeckMenuWork* w, void* a) {
    w->gfx = AnimUpdate(&w->anim2);
    w->gfx2 = AnimUpdate(&w->anim3);
    ReleaseCommandMenuGfx(w);
    SetDeckMenuFrameCursor(w, 0);

    switch (w->commandCursor) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        if (w->prevView == 0) {
            w->view = 0;
            SetDeckMenuHandAnim(w);
            w->timer = 4;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckGrid);
        } else {
            w->view = 1;
            w->timer = 4;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckSelect);
        }

        break;
    }

    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuOpenAddMode(DeckMenuWork* w, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 4);

    switch (w->deckIndex) {
    case 0:
#ifdef VERSION_EU
        SetupBg(0, 0, 31, 0);
#else
        SetupBg(0, 3, 31, 0);
#endif
#ifdef VERSION_EU
        SetupBg(1, 0, 28, 0);
#else
        SetupBg(1, 0, 23, 0);
#endif
#ifdef VERSION_EU
        SetupBg(2, 0, 29, 0);
#else
        SetupBg(2, 0, 15, 0);
#endif
        SetupBg(3, 0, 30, 0);
        LoadBgMap(0, gUnk_09519AB8, 0x180);
        LoadBgMap(1, gUnk_095182B8, 0x800);
        LoadBgMap(2, gUnk_09514AB8, 0x800);
        SetBgScroll(0, 0, 0xFFF0);
        SetBgScroll(1, 0, 0);
        SetBgScroll(2, 0, 0);
        w->deckNameX = 16;
        w->deckNameY = 28;
        break;
    case 1:
        SetupBg(0, 0, 31, 0);
#ifdef VERSION_EU
        SetupBg(1, 0, 28, 0);
#else
        SetupBg(1, 2, 23, 0);
#endif
#ifdef VERSION_EU
        SetupBg(2, 0, 29, 0);
#else
        SetupBg(2, 0, 15, 0);
#endif
        SetupBg(3, 0, 30, 0);
        LoadBgMap(0, gUnk_095182B8, 0x800);
        LoadBgMap(1, gUnk_0951A2B8, 0x180);
        LoadBgMap(2, gUnk_09514AB8, 0x800);
        SetBgScroll(0, 0, 0);
        SetBgScroll(1, 0, 0xFFF0);
        SetBgScroll(2, 0, 0);
        w->deckName2X = 16;
        w->deckName2Y = 28;
        break;
    case 2:
        SetupBg(0, 0, 31, 0);
#ifdef VERSION_EU
        SetupBg(1, 0, 28, 0);
#else
        SetupBg(1, 0, 23, 0);
#endif
#ifdef VERSION_EU
        SetupBg(2, 0, 29, 0);
#else
        SetupBg(2, 1, 15, 0);
#endif
        SetupBg(3, 0, 30, 0);
        LoadBgMap(0, gUnk_095182B8, 0x800);
        LoadBgMap(1, gUnk_09514AB8, 0x800);
        LoadBgMap(2, gUnk_0951AAB8, 0x180);
        SetBgScroll(0, 0, 0);
        SetBgScroll(1, 0, 0);
        SetBgScroll(2, 0, 0xFFF0);
        w->deckName3X = 16;
        w->deckName3Y = 28;
        break;
    }

    CountCardsNotInDeckByCategory(w->deckIndex, w->collectionCategoryCounts);
    DrawCollectionCategoryCount(w->collectionCategoryCounts[0], 0);
    DrawCollectionCategoryCount(w->collectionCategoryCounts[1], 1);
    DrawCollectionCategoryCount(w->collectionCategoryCounts[2], 2);
    DrawCollectionCategoryCount(w->collectionCategoryCounts[3], 3);
    w->step = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuBuildAddList);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuBuildAddList(DeckMenuWork* w, void* a) {
    u16 i;
    u16 n;
    u16 m;
    CardKindEntry* k;
    u16* count;
    u8* p;
    u8* q;

    FadeStartIn(FADE_MODE_BLACK, 4);

    switch (w->step) {
    case 0:
        q = &w->view;
        k = NULL;
        *q = 4;
        w->descriptionX = 7;
        w->descriptionY = 130;
        ReleaseCommandMenuGfx(w);
        SetDeckMenuFrameCursor(w, 0);
        ClearCardGrid(w);
        LoadBgMap(3, gUnk_095142B8, 0x800);
        count = &w->entryCount;
        *count = n = 0x11E;
        w->kindEntries = EwramAlloc(n * sizeof(CardKindEntry));
        CpuFill32(0, w->kindEntries, *count * sizeof(CardKindEntry));
        w->entries = k;
        break;
    case 1:
        CountCardsNotInDeckByKind(w->kindEntries, w->deckIndex, 1, w->entryCount, w->unk_4FC);
        break;
    case 2:
        w->entryCount = ListCardsNotInDeckByKind(w->kindEntries, w->deckIndex, 1, w->entryCount, w->unk_4FC);
        break;
    case 3:
        if (w->entryCount != 0) {
            BuildCollectionEntries(w);
        }

        break;
    case 4:
        for (i = 0; i < 0x11E; i++) {
            if (w->kindEntries[i].count != 0) {
                EwramFree(w->kindEntries[i].indices);
            }
        }

        EwramFree(w->kindEntries);
        break;
    case 5:
        p = &w->categoryFilter;
        m = 0;
        *p = 5;
        w->gridEntryCount = CreateCollectionGridCards(w, 5, 0);
        SetDeckMenuHandAnim(w);
        w->x = gCollectionGridColumnX[0] << 8;
        w->y = gCollectionGridRowY[0] << 8;
        w->mode = 2;
        w->cursorCol = m;
        w->cursorRow = m;
        ShowCollectionCardPreview(w);
        DrawCpCost(0);

        if (w->gridEntryCount != 0) {
            w->step = 4;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuAddGrid);
        } else {
            w->cursorCol = *p;
            w->timer = 1;
            w->view = 6;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
        }

        break;
    }

    w->step++;
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuAddGrid(DeckMenuWork* w, void* a) {
    u16 i;

#ifdef VERSION_EU
    if (FadeIsActive()) {
        return 1;
    }
#endif

    w->gfx = AnimUpdate(&w->anim2);
    w->gfx2 = AnimUpdate(&w->anim3);

    if (w->popupActive != 0) {
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            w->result = 7;
            w->exitRequested = 1;
        }

        return 1;
    }

    if (w->exitRequested) {
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        } else {
            w->exitRequested = 0;
        }
    }

    if (w->step == 0) {
        switch (GetKeysRepeat()) {
        case DPAD_UP:
            if (w->cursorRow > 0) {
                if (IsCardAt(w, w->cursorCol, w->cursorRow - 1)) {
                    w->cursorRow--;
                    w->timer = 1;
                    m4aSongNumStart(SONG_SYS_CLICKI04B);
                }
            } else {
                if (!ScrollGridUp(w, 1)) {
                    w->cursorCol = w->categoryFilter;
                    w->timer = 1;
                    m4aSongNumStart(SONG_SYS_CLICKI04B);
                    w->view = 6;

                    for (i = 0; i < 10; i++) {
                        DrawValueCount(0, i);
                    }

                    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
                    return 1;
                }
            }

            ShowCollectionCardPreview(w);
            break;
        case DPAD_DOWN:
            if (w->cursorRow <= 2) {
                if (IsCardAt(w, w->cursorCol, w->cursorRow + 1)) {
                    w->cursorRow++;
                    w->timer = 1;
                    m4aSongNumStart(SONG_SYS_CLICKI04B);
                }
            } else {
                if (IsCardAt(w, w->cursorCol, w->cursorRow + 1)) {
                    ScrollGridDown(w);
                }
            }

            ShowCollectionCardPreview(w);
            break;
        case DPAD_LEFT:
            if (w->cursorCol > 0) {
                if (IsCardAt(w, w->cursorCol - 1, w->cursorRow)) {
                    w->cursorCol--;
                    w->timer = 1;
                    m4aSongNumStart(SONG_SYS_CLICKI04B);
                }
            }

            ShowCollectionCardPreview(w);
            break;
        case DPAD_RIGHT:
            if (w->cursorCol > 1) {
                w->timer = 1;
                return 1;
            }

            if (IsCardAt(w, w->cursorCol + 1, w->cursorRow)) {
                w->cursorCol++;
                w->timer = 1;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            }

            ShowCollectionCardPreview(w);
            break;
        }

        switch (GetKeysPressed()) {
        case A_BUTTON:
            if ((u8)IsCardAtCursor(w)) {
                w->savedCol = w->cursorCol;
                w->savedRow = w->cursorRow;
                w->cursorCol = 0;
                w->cursorRow = 0;

                if ((u8)MoveValueCursor(w, 0)) {
                    m4aSongNumStart(SONG_SYS_KETTEI);
                    DrawSelectedValueCpCost(w);
                    SetDeckMenuFrameCursor(w, 1);
                    w->view = 5;
                    w->x = sValueGridX[w->cursorCol] << 8;
                    w->y = sValueGridY[w->cursorRow] << 8;
                    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuAddValueSelect);
                    return 1;
                } else {
                    w->cursorCol = w->savedCol;
                    w->cursorRow = w->savedRow;
                    m4aSongNumStart(SONG_SYS_BEEP);
                    return 1;
                }
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
                return 1;
            }
        case B_BUTTON:
            FadeStartIn(FADE_MODE_BLACK, 1);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseAddMode);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        case L_BUTTON:
            FadeStartIn(FADE_MODE_BLACK, 1);
            FreeCollectionEntries(w);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenRemoveMode);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        case START_BUTTON:
            if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
                FadeStartOut(FADE_MODE_BLACK, 4);
                m4aSongNumStart(SONG_SYS_CLOSE);
                w->result = 7;
            }

            return 1;
        }

        if (GetKeysPressed() & SELECT_BUTTON) {
            w->cursorRow = 0;
            ResetGridScroll(w);
            w->cursorCol = w->categoryFilter;
            w->timer = 1;
            w->x2 = 0xA000;
            w->y2 = 0x2800;
            w->scrollRowEnd = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            w->view = 6;

            for (i = 0; i < 10; i++) {
                DrawValueCount(0, i);
            }

            TaskPoolUpdate(&w->taskpool);
            TaskPoolUpdate(&w->cardpool);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
            return 1;
        }
    } else {
        w->step--;
    }

    ApproachValueHalf(&w->x, gCollectionGridColumnX[w->cursorCol] << 8);
    ApproachValueHalf(&w->y, gCollectionGridRowY[w->cursorRow] << 8);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuCloseAddMode(DeckMenuWork* w, void* a) {
    u8* q;

    FadeStartIn(FADE_MODE_BLACK, 4);
    q = &w->view;
    *q = 4;
    w->removeLabelX = 95;
    ReleaseCardPreview(w);
    SetupBg(3, 0, 30, 0);
#ifdef VERSION_EU
    SetupBg(2, 0, 28, 0);
    SetupBg(1, 0, 29, 0);
    SetupBg(0, 0, 31, 0);
#else
    SetupBg(2, 1, 15, 0);
    SetupBg(1, 2, 23, 0);
    SetupBg(0, 3, 31, 0);
#endif
    LoadBgMap(0, gUnk_08125E24, 0x800);
    LoadBgMap(1, gUnk_08125E24, 0x800);
    LoadBgMap(2, gUnk_08125E24, 0x800);
    HighlightDeckTab(w, w->deckIndex);
    LoadBgMap(3, gUnk_09512AB8, 0x800);
    FreeCollectionEntries(w);
    ClearCardGrid(w);
    w->categoryFilter = 0;
    w->cursorCol = 0;
    w->cursorRow = w->deckIndex;
    CreateDeckGridCards(w, w->categoryFilter);
    w->mode = 0;
    *q = 1;
    SetDeckMenuHandAnim(w);
    ApproachValueHalf(&w->x, sDeckTabPointerX[w->cursorCol] << 8);
    ApproachValueHalf(&w->y, sDeckTabPointerY[w->cursorRow] << 8);
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckSelect);
    LoadPalette(gUnk_09614438,
                (void*)(w->palette4->index * 32 +
                        OBJ_PLTT),
                w->palette4->count << 5);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuOpenRemoveMode(DeckMenuWork* w, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 4);

    switch (w->deckIndex) {
    case 0:
#ifdef VERSION_EU
        SetupBg(0, 0, 31, 0);
#else
        SetupBg(0, 3, 31, 0);
#endif
#ifdef VERSION_EU
        SetupBg(1, 0, 28, 0);
#else
        SetupBg(1, 0, 23, 0);
#endif
#ifdef VERSION_EU
        SetupBg(2, 0, 29, 0);
#else
        SetupBg(2, 0, 15, 0);
#endif
        SetupBg(3, 0, 30, 0);
        LoadBgMap(0, gUnk_09519AB8, 0x180);
        LoadBgMap(1, gUnk_095172B8, 0x800);
        LoadBgMap(2, gUnk_09517AB8, 0x800);
        SetBgScroll(0, (u16)-88, (u16)-16);
        SetBgScroll(1, (u16)-88, (u16)-112);
        SetBgScroll(2, (u16)-140, (u16)-96);
        w->deckNameX = 102;
        w->deckNameY = 28;
        break;
    case 1:
        SetupBg(0, 0, 31, 0);
#ifdef VERSION_EU
        SetupBg(1, 0, 28, 0);
#else
        SetupBg(1, 2, 23, 0);
#endif
#ifdef VERSION_EU
        SetupBg(2, 0, 29, 0);
#else
        SetupBg(2, 0, 15, 0);
#endif
        SetupBg(3, 0, 30, 0);
        LoadBgMap(0, gUnk_095172B8, 0x800);
        LoadBgMap(1, gUnk_0951A2B8, 0x180);
        LoadBgMap(2, gUnk_09517AB8, 0x800);
        SetBgScroll(0, (u16)-88, (u16)-112);
        SetBgScroll(1, (u16)-88, (u16)-16);
        SetBgScroll(2, (u16)-140, (u16)-96);
        w->deckName2X = 102;
        w->deckName2Y = 28;
        break;
    case 2:
        SetupBg(0, 0, 31, 0);
#ifdef VERSION_EU
        SetupBg(1, 0, 28, 0);
#else
        SetupBg(1, 0, 23, 0);
#endif
#ifdef VERSION_EU
        SetupBg(2, 0, 29, 0);
#else
        SetupBg(2, 1, 15, 0);
#endif
        SetupBg(3, 0, 30, 0);
        LoadBgMap(0, gUnk_095172B8, 0x800);
        LoadBgMap(1, gUnk_09517AB8, 0x800);
        LoadBgMap(2, gUnk_0951AAB8, 0x180);
        SetBgScroll(0, (u16)-88, (u16)-112);
        SetBgScroll(1, (u16)-140, (u16)-96);
        SetBgScroll(2, (u16)-88, (u16)-16);
        w->deckName3X = 102;
        w->deckName3Y = 28;
        break;
    }

    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuBuildRemoveGrid);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuBuildRemoveGrid(DeckMenuWork* w, void* a) {
    w->descriptionX = 94;
    w->descriptionY = 130;
    w->view = 7;
    ReleaseCommandMenuGfx(w);
    SetDeckMenuFrameCursor(w, 0);
    SetDeckMenuHandAnim(w);
#ifdef VERSION_EU
    LoadBgMap(3, &gUnk_095132B8[0x400], 0x800);
#else
    LoadBgMap(3, gUnk_095132B8, 0x800);
#endif
    ClearCardGrid(w);
    w->categoryFilter = 0;
    w->cursorCol = 0;
    w->cursorRow = 0;
    CreateDeckGridCards(w, w->categoryFilter);
    w->x = gDeckGridColumnX[w->cursorCol] << 8;
    w->y = gDeckGridRowY[w->cursorRow] << 8;
    ShowDeckCardPreview(w);
    w->mode = 1;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuRemoveGrid);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuRemoveGrid(DeckMenuWork* w, void* a) {
    u8 v;

    w->gfx = AnimUpdate(&w->anim2);
    w->gfx2 = AnimUpdate(&w->anim3);

#ifdef VERSION_EU
    if (FadeIsActive()) {
        return 1;
    }
#endif

    if (w->popupActive != 0) {
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            w->result = 7;
            w->exitRequested = 1;
        }

        return 1;
    }

    if (w->exitRequested) {
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        w->exitRequested = 0;
    }

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
        if (w->cursorCol > 0) {
            w->cursorCol--;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        ShowDeckCardPreview(w);
        break;
    case DPAD_RIGHT:
        if (w->cursorCol <= 1) {
            w->cursorCol++;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        ShowDeckCardPreview(w);
        break;
    case DPAD_UP:
        if (w->cursorRow > 0) {
            w->cursorRow--;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        } else if (!ScrollGridUp(w, 1)) {
            v = w->categoryFilter;
            w->cursorCol = v;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            w->view = 8;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckFilter);
            DrawCpCost(0);
            return 1;
        }

        ShowDeckCardPreview(w);
        break;
    case DPAD_DOWN:
        if (w->cursorRow <= 2) {
            w->cursorRow++;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        } else {
            ScrollGridDown(w);
        }

        ShowDeckCardPreview(w);
        break;
    }

    switch (GetKeysPressed()) {
    case A_BUTTON:
        RemoveCursorCardFromDeck(w);
        ShowDeckCardPreview(w);
        DrawDeckCardCount(w->deckIndex);
        DrawDeckCpCost(w->deckIndex);
        w->deckAttackCount = CountDeckCardsOfCategory(0, w->deckIndex);
        w->deckMagicCount = CountDeckCardsOfCategory(1, w->deckIndex);
        w->deckItemCount = CountDeckCardsOfCategory(2, w->deckIndex);
        w->deckEnemyCount = CountDeckCardsOfCategory(3, w->deckIndex);
        DrawDeckCategoryCount(w->deckAttackCount, 0);
        DrawDeckCategoryCount(w->deckMagicCount, 1);
        DrawDeckCategoryCount(w->deckItemCount, 2);
        DrawDeckCategoryCount(w->deckEnemyCount, 3);
        DrawCardTotals();
        break;
    case B_BUTTON:
        w->unk_8CA = 0;
        FadeStartIn(FADE_MODE_BLACK, 1);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseRemoveMode);
        m4aSongNumStart(SONG_SYS_CANSEL);
        return 1;
    case R_BUTTON:
        w->unk_8CA = 1;
        FreeCollectionEntries(w);
        FadeStartIn(FADE_MODE_BLACK, 1);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenAddMode);
        m4aSongNumStart(SONG_SYS_CANSEL);
        return 1;
    case START_BUTTON:
        if (!(u8)CheckDeckCpCost(w)) {
            return 1;
        }

        if (!(u8)CheckDeckHasAttackCard(w)) {
            return 1;
        }

        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
        FadeStartOut(FADE_MODE_BLACK, 4);
        m4aSongNumStart(SONG_SYS_CLOSE);
        w->result = 7;
        return 1;
    }

    if (GetKeysPressed() & SELECT_BUTTON) {
        w->cursorRow = 0;
        ResetGridScroll(w);
        v = w->categoryFilter;
        w->cursorCol = v;
        w->timer = 1;
        w->x2 = 0x4800;
        w->y2 = 0x2800;
        w->scrollRowEnd = 4;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
        w->view = 8;
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckFilter);
        DrawCpCost(0);
        return 1;
    }

    ApproachValueHalf(&w->x, gDeckGridColumnX[w->cursorCol] << 8);
    ApproachValueHalf(&w->y, gDeckGridRowY[w->cursorRow] << 8);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuCloseRemoveMode(DeckMenuWork* w, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 4);
    w->removeLabelX = 95;
    ReleaseCardPreview(w);
    SetupBg(3, 0, 30, 0);
#ifdef VERSION_EU
    SetupBg(2, 0, 28, 0);
    SetupBg(1, 0, 29, 0);
    SetupBg(0, 0, 31, 0);
#else
    SetupBg(2, 1, 15, 0);
    SetupBg(1, 2, 23, 0);
    SetupBg(0, 3, 31, 0);
#endif
    LoadBgMap(0, gUnk_08125E24, 0x800);
    LoadBgMap(1, gUnk_08125E24, 0x800);
    LoadBgMap(2, gUnk_08125E24, 0x800);
    HighlightDeckTab(w, w->deckIndex);
    LoadBgMap(3, gUnk_09512AB8, 0x800);
    FreeCollectionEntries(w);
    ClearCardGrid(w);
    w->categoryFilter = 0;
    w->cursorCol = 0;
    w->cursorRow = w->deckIndex;
    CreateDeckGridCards(w, w->categoryFilter);
    w->mode = 0;
    w->view = 1;
    SetDeckMenuHandAnim(w);
    ApproachValueHalf(&w->x, sDeckTabPointerX[w->cursorCol] << 8);
    ApproachValueHalf(&w->y, sDeckTabPointerY[w->cursorRow] << 8);
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckSelect);
    LoadPalette(gUnk_09614438,
                (void*)(w->palette4->index * 32 +
                        OBJ_PLTT),
                w->palette4->count << 5);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuOpenDeleteMode(DeckMenuWork* w, void* a) {
    u8 z;
    u8* q;

    FadeStartIn(FADE_MODE_BLACK, 4);
    SetupBg(3, 0, 30, 0);
    SetupBg(2, 0, 15, 0);
    SetupBg(1, 0, 23, 0);
    SetupBg(0, 0, 31, 0);
    SetBgScroll(0, 0, 0);
    SetBgScroll(1, 0, 0);
    SetBgScroll(2, 0, 16);
    LoadBgMap(3, gUnk_095192B8, 0x800);
    LoadBgMap(2, gUnk_095182B8, 0x800);
    LoadBgMap(1, gUnk_09514AB8, 0x800);
    DisableBg(0);
    CountCardsNotInDeckByCategory(3, w->collectionCategoryCounts);
    DrawCollectionCategoryCount(w->collectionCategoryCounts[0], 0);
    DrawCollectionCategoryCount(w->collectionCategoryCounts[1], 1);
    DrawCollectionCategoryCount(w->collectionCategoryCounts[2], 2);
    DrawCollectionCategoryCount(w->collectionCategoryCounts[3], 3);
    q = &w->view;
    z = 0;
    *q = 9;
    ReleaseCommandMenuGfx(w);
    SetDeckMenuFrameCursor(w, 0);
    ClearCardGrid(w);
    w->step = z;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuBuildDeleteList);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuBuildDeleteList(DeckMenuWork* w, void* a) {
    u16 i;

    FadeStartIn(FADE_MODE_BLACK, 4);

    switch (w->step) {
    case 0:
        w->entryCount = 286;
        w->kindEntries = EwramAlloc(w->entryCount * sizeof(CardKindEntry));
        CpuFill32(0, w->kindEntries, w->entryCount * sizeof(CardKindEntry));
        w->entries = NULL;
        w->descriptionX = 7;
        w->descriptionY = 113;
        break;
    case 1:
        CountCardsNotInDeckByKind(w->kindEntries, w->deckIndex, 0, w->entryCount, w->unk_4FC);
        break;
    case 2:
        w->entryCount = ListCardsNotInDeckByKind(w->kindEntries, w->deckIndex, 0, w->entryCount, w->unk_4FC);
        break;
    case 3:
        if (w->entryCount != 0) {
            BuildCollectionEntries(w);
        }

        break;
    case 4:
        for (i = 0; i < 286; i++) {
            if (w->kindEntries[i].count != 0) {
                EwramFree(w->kindEntries[i].indices);
            }
        }

        EwramFree(w->kindEntries);
        break;
    case 5:
        w->categoryFilter = 5;
        w->gridEntryCount = CreateCollectionGridCards(w, 5, 1);
        SetDeckMenuHandAnim(w);
        w->x = gCollectionGridColumnX[0] << 8;
        w->y = gCollectionGridRowY[0] << 8;
        w->mode = 3;
        w->cursorCol = 0;
        w->cursorRow = 0;
        ShowCollectionCardPreview(w);

        if (w->gridEntryCount != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteGrid);
        } else {
            w->view = 10;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
            w->cursorCol = w->categoryFilter;
            w->timer = 1;
        }

        break;
    }

    w->step++;
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuDeleteGrid(DeckMenuWork* w, void* a) {
    u16 i;

    w->gfx = AnimUpdate(&w->anim2);
    w->gfx2 = AnimUpdate(&w->anim3);

    if (w->popupActive != 0) {
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            w->result = 7;
            w->exitRequested = 1;
        }

        return 1;
    }

    if (w->exitRequested) {
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        } else {
            w->exitRequested = 0;
        }
    }

    switch (GetKeysRepeat()) {
    case DPAD_UP:
        if (w->cursorRow > 0) {
            if (IsCardAt(w, w->cursorCol, w->cursorRow - 1)) {
                w->cursorRow--;
                w->timer = 1;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            }
        } else {
            if (!ScrollGridUp(w, 1)) {
                w->cursorCol = w->categoryFilter;
                w->timer = 1;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
                w->view = 10;

                for (i = 0; i < 10; i++) {
                    DrawValueCount(0, i);
                }

                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
                return 1;
            }
        }

        ShowCollectionCardPreview(w);
        break;
    case DPAD_DOWN:
        if (w->cursorRow <= 2) {
            if (IsCardAt(w, w->cursorCol, w->cursorRow + 1)) {
                w->cursorRow++;
                w->timer = 1;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            }
        } else {
            if (IsCardAt(w, w->cursorCol, w->cursorRow + 1)) {
                ScrollGridDown(w);
            }
        }

        ShowCollectionCardPreview(w);
        break;
    case DPAD_LEFT:
        if (w->cursorCol > 0) {
            if (IsCardAt(w, w->cursorCol - 1, w->cursorRow)) {
                w->cursorCol--;
                w->timer = 1;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            }
        }

        ShowCollectionCardPreview(w);
        break;
    case DPAD_RIGHT:
        if (w->cursorCol > 1) {
            w->timer = 1;
            return 1;
        }

        if (IsCardAt(w, w->cursorCol + 1, w->cursorRow)) {
            w->cursorCol++;
            w->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        ShowCollectionCardPreview(w);
        break;
    }

    switch (GetKeysPressed()) {
    case A_BUTTON:
        if ((u8)IsCardAtCursor(w)) {
            w->savedCol = w->cursorCol;
            w->savedRow = w->cursorRow;
            w->cursorCol = 0;
            w->cursorRow = 0;
            SetDeckMenuFrameCursor(w, 1);

            if ((u8)MoveValueCursor(w, 0)) {
                m4aSongNumStart(SONG_SYS_KETTEI);
                DrawSelectedValueCpCost(w);
                w->view = 11;
                w->x = sValueGridX[w->cursorCol] << 8;
                w->y = (sValueGridY[w->cursorRow] - 16) << 8;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteValueSelect);
                return 1;
            } else {
                w->cursorCol = w->savedCol;
                w->cursorRow = w->savedRow;
                SetDeckMenuFrameCursor(w, 0);
                w->view = 9;
                m4aSongNumStart(SONG_SYS_BEEP);
                return 1;
            }
        } else {
            m4aSongNumStart(SONG_SYS_BEEP);
            return 1;
        }
    case B_BUTTON:
        FadeStartIn(FADE_MODE_BLACK, 1);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseDeleteMode);
        m4aSongNumStart(SONG_SYS_CANSEL);
        return 1;
    case START_BUTTON:
        if ((u8)CheckDeckCpCost(w) && (u8)CheckDeckHasAttackCard(w)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CLOSE);
            w->result = 7;
        }

        return 1;
    }

    if (GetKeysPressed() & SELECT_BUTTON) {
        ResetGridScroll(w);
        w->cursorCol = w->categoryFilter;
        w->timer = 1;
        w->x2 = 0xA000;
        w->y2 = 0x2800;
        w->scrollRowEnd = 4;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
        w->view = 10;

        for (i = 0; i < 10; i++) {
            DrawValueCount(0, i);
        }

        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
        return 1;
    }

    ApproachValueHalf(&w->x, gCollectionGridColumnX[w->cursorCol] << 8);
    ApproachValueHalf(&w->y, gCollectionGridRowY[w->cursorRow] << 8);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuCloseDeleteMode(DeckMenuWork* w, void* a) {
    u8* q;

    FadeStartIn(FADE_MODE_BLACK, 4);
    q = &w->view;
    *q = 9;
    w->removeLabelX = 95;
    ReleaseCardPreview(w);
    SetupBg(3, 0, 30, 0);
#ifdef VERSION_EU
    SetupBg(2, 0, 28, 0);
    SetupBg(1, 0, 29, 0);
    SetupBg(0, 0, 31, 0);
#else
    SetupBg(2, 1, 15, 0);
    SetupBg(1, 2, 23, 0);
    SetupBg(0, 3, 31, 0);
#endif
    LoadBgMap(0, gUnk_08125E24, 0x800);
    LoadBgMap(1, gUnk_08125E24, 0x800);
    LoadBgMap(2, gUnk_08125E24, 0x800);
    HighlightDeckTab(w, w->deckIndex);
    LoadBgMap(3, gUnk_09512AB8, 0x800);
    FreeCollectionEntries(w);
    ClearCardGrid(w);
    w->categoryFilter = 0;
    w->cursorCol = 0;
    w->cursorRow = w->deckIndex;
    CreateDeckGridCards(w, w->categoryFilter);
    w->mode = 0;
    *q = 1;
    SetDeckMenuHandAnim(w);
    ApproachValueHalf(&w->x, sDeckTabPointerX[w->cursorCol] << 8);
    ApproachValueHalf(&w->y, sDeckTabPointerY[w->cursorRow] << 8);
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckSelect);
    LoadPalette(gUnk_09614438,
                (void*)(w->palette4->index * 32 +
                        OBJ_PLTT),
                w->palette4->count << 5);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuFadeOut(DeckMenuWork* w) {
    if (!FadeIsActive()) {
        return 0;
    }

    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuStartSlideOut(DeckMenuWork* w, void* a) {
    w->tiles6 = LoadObjTiles(gUnk_090A583E, 0x620);

#ifdef VERSION_EU
    w->tiles12 = LoadObjTiles(gDeckTitleBannerTiles[gLanguage], sDeckTitleBannerTileSizes[gLanguage]);
#elif defined(VERSION_US)
    if (gGameState.flags & GAME_FLAG_RIKU) {
        w->tiles12 = LoadObjTiles(gUnk_090A418E, 0x320);
    } else {
        w->tiles12 = LoadObjTiles(gUnk_090A3E46, 0x320);
    }
#else
    w->tiles12 = LoadObjTiles(gUnk_090A418E, 0x320);
#endif

    w->palette3 = LoadObjPalette(gUnk_096144F8, 32);
#ifdef VERSION_EU
    LoadBgMap(3, gUnk_095132B8, 0x800);
#else
    LoadBgMap(3, gUnk_09516AB8, 0x800);
#endif
    w->x5 = 0x7800;
    w->y5 = 0;
    w->x6 = 0xA400;
    w->y6 = 0x9800;
    w->x7 = 0;
    w->barSlideTimer = 16;
    w->bannerSlideTimer = 16;
    w->handVisible = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuSlideOut);
    return 1;
}

u8 UpdateDeckMenuSlideOut(DeckMenuWork* w, void* a) {
    if ((s8)w->bannerSlideTimer > 0) {
        ApproachValue(&w->x7, -0x8000, (s8)w->bannerSlideTimer);
        w->bannerSlideTimer--;
    } else if ((s8)w->barSlideTimer > 0) {
        ApproachValue(&w->y5, -0x800, (s8)w->barSlideTimer);
        ApproachValue(&w->y6, 0xA000, (s8)w->barSlideTimer);
        w->barSlideTimer--;
    } else {
        FadeStartOut(FADE_MODE_BLACK, 4);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
    }

    return 1;
}

void DrawCardDescription(DeckMenuWork* w) {
    DrawTextSlotsUnsorted(w->descriptionX, w->descriptionY, w->textSlots5,
                  w->palette, 20, w->textSlotCount5);
}

void DrawDeckNames(DeckMenuWork* w, u8 flag) {
    if (!flag) {
        switch (w->deckIndex) {
        case 0:
            DrawTextSlots(w->deckNameX, w->deckNameY, w->textSlots, w->palette, 20, w->textSlotCount);
            DrawTextSlots(w->deckName2X, w->deckName2Y, w->textSlots2, w->palette4, 20, w->textSlotCount2);
            DrawTextSlots(w->deckName3X, w->deckName3Y, w->textSlots3, w->palette4, 20, w->textSlotCount3);
            break;
        case 1:
            DrawTextSlots(w->deckNameX, w->deckNameY, w->textSlots, w->palette4, 20, w->textSlotCount);
            DrawTextSlots(w->deckName2X, w->deckName2Y, w->textSlots2, w->palette, 20, w->textSlotCount2);
            DrawTextSlots(w->deckName3X, w->deckName3Y, w->textSlots3, w->palette4, 20, w->textSlotCount3);
            break;
        case 2:
            DrawTextSlots(w->deckNameX, w->deckNameY, w->textSlots, w->palette4, 20, w->textSlotCount);
            DrawTextSlots(w->deckName2X, w->deckName2Y, w->textSlots2, w->palette4, 20, w->textSlotCount2);
            DrawTextSlots(w->deckName3X, w->deckName3Y, w->textSlots3, w->palette, 20, w->textSlotCount3);
            break;
        }
    } else {
        switch (w->deckIndex) {
        case 0:
            DrawTextSlots(w->deckNameX, w->deckNameY, w->textSlots, w->palette, 20, w->textSlotCount);
            break;
        case 1:
            DrawTextSlots(w->deckName2X, w->deckName2Y, w->textSlots2, w->palette, 20, w->textSlotCount2);
            break;
        case 2:
            DrawTextSlots(w->deckName3X, w->deckName3Y, w->textSlots3, w->palette, 20, w->textSlotCount3);
            break;
        }
    }
}

static void Deckmenu2_2(DeckMenuWork* w) {
    gCardUiSpriteState.gfx = AnimUpdate(&gCardUiSpriteState.anim);

    if (w->popupActive == 0) {
        if (w->handVisible != 0) {
            DrawSprite((w->x >> 8) - 16, (w->y >> 8) - 30, w->gfx, w->tiles, w->palette, NULL, w->handFlags, 3);
        }
    }

    if (w->view != 13) {
        DrawSprite(w->x2 >> 8, w->y2 >> 8, gUnk_09EEB000, w->tiles4, w->palette, NULL, SPRITE_PRIORITY(2), 10);
    }

    if (w->tiles6 != NULL) {
        DrawSprite(w->x5 >> 8, w->y5 >> 8, gUnk_09EEB080[0], w->tiles6, w->palette3, NULL, SPRITE_PRIORITY(3), 10000);
        DrawSprite(w->x6 >> 8, w->y6 >> 8, gUnk_09EEB080[1], w->tiles6, w->palette3, NULL, SPRITE_PRIORITY(3), 10000);
    }

    if (w->tiles12 != NULL) {
        DrawSprite(w->x7 >> 8, 0,
#ifdef VERSION_EU
                   gDeckTitleBannerSprites[gLanguage][0],
#else
                   gUnk_09EEAFF0,
#endif
                   w->tiles12, w->palette3, NULL, 0, 10);
    }

    switch (w->view) {
    case 0:
        if (w->holding) {
            DrawSprite((w->x3 >> 8) - 16, (w->y3 >> 8) - 20, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);
        }

        DrawSprite((w->x >> 8) - 16, (w->y >> 8) - 20, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);
        DrawDeckNames(w, 0);
        DrawSprite(w->removeLabelX, w->removeLabelY, w->gfx7, w->tiles5, w->palette, NULL, 0, 10);
        DrawSprite(w->addLabelX, w->addLabelY, w->gfx8, w->tiles5, w->palette, NULL, 0, 10);
        break;
    case 3:
#ifdef VERSION_EU
        if (w->tiles3 != NULL) {
            DrawSprite(120, 80, gDeckCommandMenuSprites[gLanguage][0], w->tiles3, w->palette2, NULL, 0, 8);
        }
#else
        DrawSprite(120, 80, gUnk_09EEAFE8, w->tiles3, w->palette2, NULL, 0, 8);
#endif
        DrawDeckNames(w, 0);
        DrawSprite(w->removeLabelX, w->removeLabelY, w->gfx7, w->tiles5, w->palette, NULL, 0, 10);
        DrawSprite(w->addLabelX, w->addLabelY, w->gfx8, w->tiles5, w->palette, NULL, 0, 10);
        break;
    case 2:
        DrawDeckNames(w, 0);
        DrawSprite(w->removeLabelX, w->removeLabelY, w->gfx7, w->tiles5, w->palette, NULL, 0, 10);
        DrawSprite(w->addLabelX, w->addLabelY, w->gfx8, w->tiles5, w->palette, NULL, 0, 10);
        break;
    case 1:
        DrawSprite(w->removeLabelX, w->removeLabelY, w->gfx7, w->tiles5, w->palette, NULL, 0, 10);
        DrawSprite(w->addLabelX, w->addLabelY, w->gfx8, w->tiles5, w->palette, NULL, 0, 10);
        DrawDeckNames(w, 0);
        break;
    case 4:
        DrawDeckNames(w, 1);
        DrawSprite(w->removeLabelX, w->removeLabelY, w->gfx7, w->tiles5, w->palette, NULL, 0, 10);
        DrawSprite((w->x >> 8) - 16, (w->y >> 8) - 20, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);

        if (w->tiles7 != NULL) {
            if (w->popupActive == 0) {
                DrawSprite((w->x >> 8) - 16, (w->y >> 8) - 20, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);
            }

            DrawSprite(24, 82, w->gfx4, w->tiles7, w->palette5, NULL, SPRITE_PRIORITY(1), 100);
            DrawSprite(24, 82, w->gfx5, w->tiles8, w->palette6, NULL, SPRITE_PRIORITY(1), 101);
            DrawTextSlots(10, 116, w->textSlots4, w->palette4, 20, w->textSlotCount4);

            if (w->tiles10 != NULL) {
                w->gfx3 = AnimUpdate(&w->anim);
                DrawSprite(24, 82, w->gfx3, w->tiles10, w->palette5, NULL, 0, 1);
            }
        }

        if (w->popupActive == 0) {
            DrawCardDescription(w);
        }

        break;
    case 7:
        DrawDeckNames(w, 1);
        DrawSprite(w->addLabelX, w->addLabelY, w->gfx8, w->tiles5, w->palette, NULL, 0, 10);
        DrawSprite((w->x >> 8) - 16, (w->y >> 8) - 20, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);

        if (w->tiles7 != NULL) {
            DrawSprite(164, 82, w->gfx4, w->tiles7, w->palette5, NULL, SPRITE_PRIORITY(1), 100);
            DrawSprite(164, 82, w->gfx5, w->tiles8, w->palette6, NULL, SPRITE_PRIORITY(1), 101);

            if (w->tiles10 != NULL) {
                w->gfx3 = AnimUpdate(&w->anim);
                DrawSprite(164, 82, w->gfx3, w->tiles10, w->palette5, NULL, 0, 1);
            }

            if (w->tiles9 != NULL) {
                DrawSprite(164, 82, w->gfx6, w->tiles9, w->palette5, NULL, 0, 19);
            }

            DrawTextSlots(100, 116, w->textSlots4, w->palette4, 20, w->textSlotCount4);

            if (w->popupActive == 0) {
                DrawCardDescription(w);
            }
        }

        break;
    case 5:
        DrawSprite(w->removeLabelX, w->removeLabelY, w->gfx7, w->tiles5, w->palette, NULL, 0, 10);
        DrawSprite((w->x >> 8) - 26, (w->y >> 8) - 13, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);
        DrawDeckNames(w, 1);

        if (w->tiles7 != NULL) {
            DrawSprite(24, 82, w->gfx4, w->tiles7, w->palette5, NULL, SPRITE_PRIORITY(1), 100);
            DrawSprite(24, 82, w->gfx5, w->tiles8, w->palette6, NULL, SPRITE_PRIORITY(1), 101);

            if (w->tiles10 != NULL) {
                w->gfx3 = AnimUpdate(&w->anim);
                DrawSprite(24, 82, w->gfx3, w->tiles10, w->palette5, NULL, 0, 1);
            }

            DrawTextSlots(10, 116, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }

        if (w->popupActive == 0) {
            DrawCardDescription(w);
        }

        break;
    case 6:
        DrawSprite(w->removeLabelX, w->removeLabelY, w->gfx7, w->tiles5, w->palette, NULL, 0, 10);
        DrawDeckNames(w, 1);
        break;
    case 8:
        DrawSprite(w->addLabelX, w->addLabelY, w->gfx8, w->tiles5, w->palette, NULL, 0, 10);
        DrawDeckNames(w, 1);
        break;
    case 9:
        DrawSprite((w->x >> 8) - 16, (w->y >> 8) - 20, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);

        if (w->tiles7 != NULL) {
            DrawSprite(24, 66, w->gfx4, w->tiles7, w->palette5, NULL, SPRITE_PRIORITY(1), 100);
            DrawSprite(24, 66, w->gfx5, w->tiles8, w->palette6, NULL, SPRITE_PRIORITY(1), 101);

            if (w->tiles10 != NULL) {
                w->gfx3 = AnimUpdate(&w->anim);
                DrawSprite(24, 66, w->gfx3, w->tiles10, w->palette5, NULL, 0, 1);
            }

            DrawTextSlots(10, 100, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }

        if (w->popupActive == 0) {
            DrawCardDescription(w);
        }

        break;
    case 11:
        DrawSprite((w->x >> 8) - 26, (w->y >> 8) - 13, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);

        if (w->tiles7 != NULL) {
            DrawSprite(24, 66, w->gfx4, w->tiles7, w->palette5, NULL, SPRITE_PRIORITY(1), 100);
            DrawSprite(24, 66, w->gfx5, w->tiles8, w->palette6, NULL, SPRITE_PRIORITY(1), 101);

            if (w->tiles10 != NULL) {
                w->gfx3 = AnimUpdate(&w->anim);
                DrawSprite(24, 66, w->gfx3, w->tiles10, w->palette5, NULL, 0, 1);
            }

            DrawTextSlots(10, 100, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }

        if (w->popupActive == 0) {
            DrawCardDescription(w);
        }

        break;
    case 13:
        DrawSprite(w->x9 >> 8, w->y8 >> 8, w->gfx9, w->tiles11, w->palette7, NULL, 0, 20);
        DrawSprite(w->x10 >> 8, 18, NULL, w->tiles13, w->palette7, NULL, 0, 21);
        DrawTextSlots(138, 16, w->textSlots6, w->palette, 20, w->textSlotCount6);
        break;
    case 12:
        DrawSprite((w->x >> 8) - 16, (w->y >> 8) - 30, w->gfx, w->tiles, w->palette, NULL, w->handFlags, 0);

        if (w->tiles7 != NULL) {
            DrawSprite(24, 66, w->gfx4, w->tiles7, w->palette5, NULL, SPRITE_PRIORITY(1), 100);
            DrawSprite(24, 66, w->gfx5, w->tiles8, w->palette6, NULL, SPRITE_PRIORITY(1), 101);

            if (w->tiles10 != NULL) {
                w->gfx3 = AnimUpdate(&w->anim);
                DrawSprite(24, 66, w->gfx3, w->tiles10, w->palette5, NULL, 0, 1);
            }

            DrawTextSlots(10, 100, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }

        if (w->popupActive == 0) {
            DrawCardDescription(w);
        }

        break;
    case 15:
        DrawSprite((w->x >> 8) - 16, (w->y >> 8) - 30, w->gfx, w->tiles, w->palette, NULL, w->handFlags, 0);

        if (w->tiles7 != NULL) {
            DrawSprite(24, 66, w->gfx4, w->tiles7, w->palette5, NULL, SPRITE_PRIORITY(1), 100);
            DrawSprite(24, 66, w->gfx5, w->tiles8, w->palette6, NULL, SPRITE_PRIORITY(1), 101);

            if (w->tiles10 != NULL) {
                w->gfx3 = AnimUpdate(&w->anim);
                DrawSprite(24, 66, w->gfx3, w->tiles10, w->palette5, NULL, 0, 1);
            }
        }

        break;
    }

    TaskPoolDraw(&w->taskpool);
    TaskPoolDraw(&w->cardpool);
}

void DeckMenuDestroy(DeckMenuWork* w) {
    ClearCardGrid(w);
    ReleaseObjTiles(w->tiles);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjTiles(w->tiles4);
    ReleaseObjPalette(w->palette);

    if (w->tiles12 != NULL) {
        ReleaseObjTiles(w->tiles12);
    }

    if (w->tiles6 != NULL) {
        ReleaseObjTiles(w->tiles6);
    }

    if (w->palette3 != NULL) {
        ReleaseObjPalette(w->palette3);
    }

    ReleaseCommandMenuGfx(w);
    FreeTextSlots(w->textSlots, 8);
    FreeTextSlots(w->textSlots2, 8);
    FreeTextSlots(w->textSlots3, 8);
    FreeTextSlots(w->textSlots4, 30);
    FreeTextSlots(w->textSlots5, 90);
    ReleaseObjPalette(w->palette4);
    TaskPoolDestroy(&w->taskpool);
    TaskPoolDestroy(&w->cardpool);
    FreeCollectionEntries(w);
    *w->resultOut = w->result;
    ReleaseObjTiles(w->tiles5);
    ReleaseObjTiles(gCardUiSpriteState.tiles);
    ReleaseObjPalette(gCardUiSpriteState.palette);
}

void CreateDeckGridCards(DeckMenuWork* w, u8 kind) {
    DeckCard2Args args;
    u16* deck;
    u8 i;
    s8 x;
    s8 y;

    deck = (u16*)GetDeck(w->deckIndex);
    x = 0;
    y = 0;

    if (kind == 0) {
        for (i = 0; i < 99; i++) {
            if (deck[i] != 0xFFFF) {
                if (kind == 0) {
                    args.pool = &w->pool;
                    args.cardId = gCardCollection[deck[i]] & 0x8FFF;
                    args.col = x;
                    args.row = y;
                    args.panel = 0;
                    args.slot = &deck[i];
                    TaskCreate(&w->taskpool, &gTaskDescDeckCard2, &args);
                } else if (gCardDefs[gCardCollection[deck[i]] & 0xFFF].category == kind - 1) {
                    args.pool = &w->pool;
                    args.cardId = gCardCollection[deck[i]] & 0x8FFF;
                    args.col = x;
                    args.row = y;
                    args.panel = 0;
                    args.slot = &deck[i];
                    TaskCreate(&w->taskpool, &gTaskDescDeckCard2, &args);
                }
            } else {
                args.pool = &w->pool;
                args.cardId = 0xFFFF;
                args.col = x;
                args.row = y;
                args.panel = 0;
                args.slot = &deck[i];
                TaskCreate(&w->taskpool, &gTaskDescDeckCard2, &args);
            }

            x++;

            if (x > 2) {
                x = 0;
                y++;
            }
        }
    } else {
        for (i = 0; i < 99; i++) {
            if (deck[i] != 0xFFFF && gCardDefs[gCardCollection[deck[i]] & 0xFFF].category == kind - 1) {
                args.pool = &w->pool;
                args.cardId = gCardCollection[deck[i]] & 0x8FFF;
                args.col = x;
                args.row = y;
                args.panel = 0;
                args.slot = &deck[i];
                TaskCreate(&w->taskpool, &gTaskDescDeckCard2, &args);
                x++;
            }

            if (x > 2) {
                x = 0;
                y++;
            }
        }
    }

    w->x2 = 0x4800;
    w->y2 = 0x2800;
    w->scrollRowEnd = 4;
    SetGridRowCount(w, 99);
}

s32 CreateCollectionGridCards(DeckMenuWork* w, u8 kind, u8 c) {
    DeckCard2Args args;
    u16 i;
    u16 count;
    s8 x;
    s8 y;

    x = 0;
    y = 0;
    count = 0;

    if (!c) {
        for (i = 0; i < w->entryCount; i++) {
            if (kind == 5) {
                if (w->entries[i].count != 0) {
                    args.pool = &w->pool;
                    args.cardId = GetCardIdForKindEntry(
                        w->entries[i].kind);
                    args.col = x;
                    args.row = y;
                    args.panel = 1;
                    args.slot = NULL;
                    TaskCreate(&w->taskpool, &gTaskDescDeckCard2, &args);
                    x++;
                    count++;
                }
            } else if (w->entries[i].count != 0) {
                args.pool = &w->pool;
                args.cardId = GetCardIdForKindEntry(
                    w->entries[i].kind);

                if (gCardDefs[args.cardId & 0xFFF].category == kind - 1) {
                    args.col = x;
                    args.row = y;
                    args.panel = 1;
                    args.slot = NULL;
                    TaskCreate(&w->taskpool, &gTaskDescDeckCard2, &args);
                    x++;
                    count++;
                }
            }

            if (x > 2) {
                x = 0;
                y++;
            }
        }
    } else {
        for (i = 0; i < w->entryCount; i++) {
            if (kind == 5) {
                if (w->entries[i].count != 0) {
                    if ((u16)(w->entries[i].kind - 78) >
                        64) {
                        args.pool = &w->pool;
                        args.cardId = GetCardIdForKindEntry(
                            w->entries[i].kind);
                        args.col = x;
                        args.row = y;
                        args.panel = 1;
                        args.slot = NULL;
                        TaskCreate(&w->taskpool, &gTaskDescDeckCard2, &args);
                        x++;
                        count++;
                    }
                }
            } else if (w->entries[i].count != 0) {
                args.pool = &w->pool;
                args.cardId = GetCardIdForKindEntry(
                    w->entries[i].kind);

                if (gCardDefs[args.cardId & 0xFFF].category == kind - 1) {
                    if ((u16)(w->entries[i].kind - 78) >
                        64) {
                        args.col = x;
                        args.row = y;
                        args.panel = 1;
                        args.slot = NULL;
                        TaskCreate(&w->taskpool, &gTaskDescDeckCard2, &args);
                        x++;
                        count++;
                    }
                }
            }

            if (x > 2) {
                x = 0;
                y++;
            }
        }
    }

    w->x2 = 0xA000;
    w->y2 = 0x2800;
    w->scrollRowEnd = 4;
    SetGridRowCount(w, y * 3 + x);

    return count;
}

s32 GetCardIdForKindEntry(s32 a) {
    u32 i;

    for (i = 0; i < 950; i++) {
        if (gCardDefs[i].kind == a) {
            return i;
        }

        if (gCardDefs[i].kind + 143 == a) {
            return i | 0x8000;
        }
    }
}

void ClearCardGrid(DeckMenuWork* w) {
    DeckCard2Work* t;

    t = ListPoolFirst(&w->pool);

    while (t != NULL) {
        t->done = 1;
        t = ListPoolNext(&t->node);
    }

    TaskPoolUpdate(&w->taskpool);
}

void SetGridRowCount(DeckMenuWork* w, s16 n) {
    w->rowCount = n / 3;

    if (n % 3 != 0) {
        w->rowCount = n / 3 + 1;
    }
}

void UpdateGridScrollBar(DeckMenuWork* w) {
    s32 v;

    v = 0x5400 / (w->rowCount - 4);
    w->y2 = v * (w->scrollRowEnd - 4) + 0x2800;

    if (w->y2 > 0x7C00) {
        w->y2 = 0x7C00;
    }

    if (w->y2 <= 0x27FF) {
        w->y2 = 0x2800;
    }
}

void ScrollGridDown(DeckMenuWork* w) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    if (w->scrollRowEnd != w->rowCount) {
        while (node != NULL) {
            node->args.row--;

            if (node->args.row < 0) {
                node->y = 0x20000;
                DeckCard2ReleaseGfx(node);
            }

            node = ListPoolNext(&node->node);
        }

        m4aSongNumStart(SONG_SYS_CLICKI04B);
        w->scrollRowEnd++;
        w->y2 += 0x300;

        if (w->y2 > 0x7C00) {
            w->y2 = 0x7C00;
        }

        if (w->holding) {
            w->heldRow--;
        }

        UpdateGridScrollBar(w);
    }
}

u8 ScrollGridUp(DeckMenuWork* w, u8 a) {
    DeckCard2Work* n;
    u8 b;
    u16 t;

    b = a;
    n = ListPoolFirst(&w->pool);

    if (w->scrollRowEnd <= 4) {
        return 0;
    }

    if (n == NULL) {
        w->y2 -= 0x300;

        t = w->scrollRowEnd;

        if ((s16)t > 4) {
            w->scrollRowEnd = t - 1;
        }

        if (w->y2 < 0x2800) {
            w->y2 = 0x2800;
            return 0;
        }

        if (a) {
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }
    } else {
        if (b) {
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        do {
            n->args.row++;

            if (n->args.row > 3) {
                n->y = 0x20000;
                DeckCard2ReleaseGfx(n);
            }

            n = ListPoolNext(&n->node);
        } while (n != NULL);

        w->scrollRowEnd--;
        w->y2 -= 0x300;

        if (w->y2 < 0x2800) {
            w->y2 = 0x2800;
        }
    }

    UpdateGridScrollBar(w);
    return 1;
}

DeckCard2Work* GetCardAtCursor(DeckMenuWork* w) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    while (node != NULL) {
        if (w->cursorCol == node->args.col &&
            w->cursorRow == node->args.row) {
            return node;
        }

        node = ListPoolNext(&node->node);
    }

    return NULL;
}

void DrawDeckCategoryCount(u8 a, u8 b) {
    u8 d[2];
    u8* base;

    if (a == 0) {
        base = GetBgCharBase(3);
        RequestDma3Copy(gUnk_0940F918, base + (b * 64 + 0x360), 32);
        RequestDma3Copy(gUnk_0940F918, base + (b * 64 + 0x360) + 32, 32);
    } else {
        d[0] = a / 10;
        d[1] = a - (u8)(a / 10) * 10;
        base = GetBgCharBase(3);
        RequestDma3Copy(&gUnk_0940F7B8[(d[0] + 1) * 32], base + (b * 64 + 0x360), 32);
        RequestDma3Copy(&gUnk_0940F7B8[(d[1] + 1) * 32], base + (b * 64 + 0x360) + 32, 32);
    }
}

void DrawCollectionCategoryCount(u16 a, u8 b) {
    u8 d[3];
    u8* base;

    if (a == 0) {
        base = GetBgCharBase(3);
        RequestDma3Copy(gUnk_0940F918, base + (b * 96 + 0x120), 32);
        RequestDma3Copy(gUnk_0940F918, base + (b * 96 + 0x120) + 32, 32);
        RequestDma3Copy(gUnk_0940F918, base + (b * 96 + 0x120) + 64, 32);
    } else {
        d[0] = a / 100;
        d[1] = a / 10 - d[0] * 10;
        d[2] = a - d[0] * 100 - d[1] * 10;
        base = GetBgCharBase(3);
        RequestDma3Copy(&gUnk_0940F7B8[(d[0] + 1) * 32], base + (b * 96 + 0x120), 32);
        RequestDma3Copy(&gUnk_0940F7B8[(d[1] + 1) * 32], base + (b * 96 + 0x120) + 32, 32);
        RequestDma3Copy(&gUnk_0940F7B8[(d[2] + 1) * 32], base + (b * 96 + 0x120) + 64, 32);
    }
}

void SetDeckMenuHandAnim(DeckMenuWork* w) {
    u16 t;

    switch (w->view) {
    case 0:
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 13:
        AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
        w->handFlags &= ~SPRITE_FLAG_HFLIP;
        break;
    case 1:
    case 3:
    case 12:
        AnimStart(&w->anim2, 2, ANIM_FLAG_LOOP);
        t = w->handFlags | SPRITE_FLAG_HFLIP;
        w->handFlags = t;
        break;
    }
}

void HighlightDeckTab(DeckMenuWork* w, u8 b) {
    void* dst;

    switch (b) {
    case 0:
        dst = (void*)(BG_PLTT + 8 * PLTT_SIZE_4BPP);
        LoadPalette(gUnk_096142F8, dst, 32);
        dst = (void*)(BG_PLTT + 9 * PLTT_SIZE_4BPP);
        LoadPalette(&gUnk_09614118[0x90], dst, 32);
        dst = (void*)(BG_PLTT + 10 * PLTT_SIZE_4BPP);
        LoadPalette(&gUnk_09614118[0xA0], dst, 32);
        LoadBgMap(0, &gUnk_09519AB8[0xC0], 0x180);
        LoadBgMap(1, gUnk_0951A2B8, 0x180);
        LoadBgMap(2, gUnk_0951AAB8, 0x180);
        SetBgScroll(0, 0xFFB4, 0xFFF2);
        SetBgScroll(1, 0xFFA8, 0xFFC0);
        SetBgScroll(2, 0xFFA8, 0xFF90);
        w->deckNameX = 100;
        w->deckNameY = 25;
        w->deckName2X = 102;
        w->deckName2Y = 75;
        w->deckName3X = 102;
        w->deckName3Y = 122;
        break;
    case 1:
        dst = (void*)(BG_PLTT + 9 * PLTT_SIZE_4BPP);
        LoadPalette(gUnk_096142F8, dst, 32);
        dst = (void*)(BG_PLTT + 8 * PLTT_SIZE_4BPP);
        LoadPalette(&gUnk_09614118[0x80], dst, 32);
        dst = (void*)(BG_PLTT + 10 * PLTT_SIZE_4BPP);
        LoadPalette(&gUnk_09614118[0xA0], dst, 32);
        LoadBgMap(0, gUnk_09519AB8, 0x180);
        LoadBgMap(1, &gUnk_0951A2B8[0xC0], 0x180);
        LoadBgMap(2, gUnk_0951AAB8, 0x180);
        SetBgScroll(0, 0xFFA8, 0xFFF0);
        SetBgScroll(1, 0xFFB4, 0xFFC2);
        SetBgScroll(2, 0xFFA8, 0xFF90);
        w->deckNameX = 102;
        w->deckNameY = 27;
        w->deckName2X = 100;
        w->deckName2Y = 73;
        w->deckName3X = 102;
        w->deckName3Y = 122;
        break;
    case 2:
        dst = (void*)(BG_PLTT + 10 * PLTT_SIZE_4BPP);
        LoadPalette(gUnk_096142F8, dst, 32);
        dst = (void*)(BG_PLTT + 8 * PLTT_SIZE_4BPP);
        LoadPalette(&gUnk_09614118[0x80], dst, 32);
        dst = (void*)(BG_PLTT + 9 * PLTT_SIZE_4BPP);
        LoadPalette(&gUnk_09614118[0x90], dst, 32);
        LoadBgMap(0, gUnk_09519AB8, 0x180);
        LoadBgMap(1, gUnk_0951A2B8, 0x180);
        LoadBgMap(2, &gUnk_0951AAB8[0xC0], 0x180);
        SetBgScroll(0, 0xFFA8, 0xFFF0);
        SetBgScroll(1, 0xFFA8, 0xFFC0);
        SetBgScroll(2, 0xFFB4, 0xFF92);
        w->deckNameX = 102;
        w->deckNameY = 27;
        w->deckName2X = 102;
        w->deckName2Y = 75;
        w->deckName3X = 100;
        w->deckName3Y = 121;
        break;
    }
}

void DrawDeckCardCount(u8 deck) {
    u8 d[2];
    u8 e[2];
    u8* base;
    u16 n;

    base = NULL;
    n = GetDeckCardCount(deck);
    d[0] = n / 10;
    d[1] = n - (u16)(n / 10) * 10;
    e[0] = 9;
    e[1] = 9;

    switch (deck) {
    case 0:
#ifdef VERSION_EU
        base = (u8*)GetBgCharBase(0) + 0x2BE0;
#else
        base = GetBgCharBase(0);
#endif
        break;
    case 1:
#ifdef VERSION_EU
        base = (u8*)GetBgCharBase(1) + 0x2F40;
#else
        base = GetBgCharBase(1);
#endif
        break;
    case 2:
#ifdef VERSION_EU
        base = (u8*)GetBgCharBase(2) + 0x32A0;
#else
        base = GetBgCharBase(2);
#endif
        break;
    }

    RequestDma3Copy(&gUnk_0940F938[(d[0] + 1) * 32], base + 0x20, 32);
    RequestDma3Copy(&gUnk_0940F938[(d[1] + 1) * 32], base + 0x40, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[0] + 1) * 32], base + 0x60, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[1] + 1) * 32], base + 0x80, 32);
}

void DrawDeckEquipMarker(u8 mode) {
#ifdef VERSION_EU
    u8* bg0;
    u8* bg1;
    u8* bg2;
    u8* src;

    bg0 = (u8*)GetBgCharBase(0) + 0x2D80;
    bg1 = (u8*)GetBgCharBase(1) + 0x30E0;
    bg2 = (u8*)GetBgCharBase(2) + 0x3440;
    src = gDeckEquipMarkerTiles[gLanguage];

    switch (mode) {
    case 0:
        RequestDma3Copy(src + 0x20, bg0, 0x1E0);
        RequestDma3Copy(src + 0x420, bg1, 0x1E0);
        RequestDma3Copy(src + 0x420, bg2, 0x1E0);
        break;
    case 1:
        RequestDma3Copy(src + 0x420, bg0, 0x1E0);
        RequestDma3Copy(src + 0x20, bg1, 0x1E0);
        RequestDma3Copy(src + 0x420, bg2, 0x1E0);
        break;
    case 2:
        RequestDma3Copy(src + 0x420, bg0, 0x1E0);
        RequestDma3Copy(src + 0x420, bg1, 0x1E0);
        RequestDma3Copy(src + 0x20, bg2, 0x1E0);
        break;
    }
#else
    u8* bg0;
    u8* bg1;
    u8* bg2;

    bg0 = GetBgCharBase(0);
    bg1 = GetBgCharBase(1);
    bg2 = GetBgCharBase(2);

    switch (mode) {
    case 0:
        RequestDma3Copy(gUnk_0940FC58, bg0 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_0940FC58 + 0x400, bg1 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_0940FC58 + 0x400, bg2 + 0x1A0, 0x1E0);
        break;
    case 1:
        RequestDma3Copy(gUnk_09410058, bg0 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_09410058 - 0x400, bg1 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_09410058, bg2 + 0x1A0, 0x1E0);
        break;
    case 2:
        RequestDma3Copy(gUnk_09410058, bg0 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_09410058, bg1 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_09410058 - 0x400, bg2 + 0x1A0, 0x1E0);
        break;
    }
#endif
}

void DrawDeckCpCost(u8 mode) {
    u8 d1[4];
    u8 d2[4];
    u16 v;

    u8* base;

    base = NULL;
    v = GetDeckCpCost(mode);

    d1[0] = v / 1000;
    d1[1] = v / 100 - d1[0] * 10;
    d1[2] = v / 10 - d1[0] * 100 - d1[1] * 10;
    d1[3] = v - d1[0] * 1000 - d1[1] * 100 - d1[2] * 10;
    d2[0] = gGameState.progression.cp / 1000;
    d2[1] = gGameState.progression.cp / 100 - d2[0] * 10;
    d2[2] = gGameState.progression.cp / 10 - d2[0] * 100 - d2[1] * 10;
    d2[3] = gGameState.progression.cp - d2[0] * 1000 - d2[1] * 100 - d2[2] * 10;

    switch (mode) {
    case 0:
#ifdef VERSION_EU
        base = (u8*)GetBgCharBase(0) + 0x2BE0;
#else
        base = GetBgCharBase(0);
#endif
        break;
    case 1:
#ifdef VERSION_EU
        base = (u8*)GetBgCharBase(1) + 0x2F40;
#else
        base = GetBgCharBase(1);
#endif
        break;
    case 2:
#ifdef VERSION_EU
        base = (u8*)GetBgCharBase(2) + 0x32A0;
#else
        base = GetBgCharBase(2);
#endif
        break;
    }

    RequestDma3Copy(&gUnk_0940F938[(d1[0] + 1) * 32], base + 0xA0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d1[1] + 1) * 32], base + 0xC0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d1[2] + 1) * 32], base + 0xE0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d1[3] + 1) * 32], base + 0x100, 32);
    RequestDma3Copy(&gUnk_0940F938[(d2[0] + 1) * 32], base + 0x120, 32);
    RequestDma3Copy(&gUnk_0940F938[(d2[1] + 1) * 32], base + 0x140, 32);
    RequestDma3Copy(&gUnk_0940F938[(d2[2] + 1) * 32], base + 0x160, 32);
    RequestDma3Copy(&gUnk_0940F938[(d2[3] + 1) * 32], base + 0x180, 32);
}
#ifdef VERSION_EU
#define CARD_SLOT_OFFSET(slot, fixed) ((fixed) * 128)
#else
#define CARD_SLOT_OFFSET(slot, fixed) ((slot) * 128)
#endif
void DrawDeckFilterTab(u8 kind, u8 slot) {
    u8* dst;

    dst = (u8*)GetBgScreenBase(3) + 0x80;

    switch (kind) {
    case 0:
        RequestDma3Copy(gUnk_095152B8 + CARD_SLOT_OFFSET(slot, 0), dst, 20);
        RequestDma3Copy(gUnk_095152B8 + 0x20 + CARD_SLOT_OFFSET(slot, 0), dst + 0x40, 20);
        break;
    case 1:
        RequestDma3Copy(gUnk_095152CC + CARD_SLOT_OFFSET(slot, 0), dst, 20);
        RequestDma3Copy(gUnk_095152CC + 0x20 + CARD_SLOT_OFFSET(slot, 0), dst + 0x40, 20);
        break;
    case 2:
        RequestDma3Copy(gUnk_095152E0 + CARD_SLOT_OFFSET(slot, 0), dst, 20);
        RequestDma3Copy(gUnk_095152E0 + 0x20 + CARD_SLOT_OFFSET(slot, 0), dst + 0x40, 20);
        break;
    case 3:
        RequestDma3Copy(gUnk_09515338 + CARD_SLOT_OFFSET(slot, 0), dst, 20);
        RequestDma3Copy(gUnk_09515338 + 0x20 + CARD_SLOT_OFFSET(slot, 0), dst + 0x40, 20);
        break;
    case 4:
        RequestDma3Copy(gUnk_0951534C + CARD_SLOT_OFFSET(slot, 0), dst, 20);
        RequestDma3Copy(gUnk_0951534C + 0x20 + CARD_SLOT_OFFSET(slot, 0), dst + 0x40, 20);
        break;
    }
}

void DrawCollectionFilterTab(u8 kind, u8 slot) {
    u8* dst;

    dst = (u8*)GetBgScreenBase(3) + 0xA8;

    switch (kind) {
    case 5:
        RequestDma3Copy(gUnk_095152B8 + CARD_SLOT_OFFSET(slot, 1), dst, 20);
        RequestDma3Copy(gUnk_095152B8 + 0x20 + CARD_SLOT_OFFSET(slot, 1), dst + 0x40, 20);
        break;
    case 4:
        RequestDma3Copy(gUnk_095152CC + CARD_SLOT_OFFSET(slot, 1), dst, 20);
        RequestDma3Copy(gUnk_095152CC + 0x20 + CARD_SLOT_OFFSET(slot, 1), dst + 0x40, 20);
        break;
    case 3:
        RequestDma3Copy(gUnk_095152E0 + CARD_SLOT_OFFSET(slot, 1), dst, 20);
        RequestDma3Copy(gUnk_095152E0 + 0x20 + CARD_SLOT_OFFSET(slot, 1), dst + 0x40, 20);
        break;
    case 2:
        RequestDma3Copy(gUnk_09515338 + CARD_SLOT_OFFSET(slot, 1), dst, 20);
        RequestDma3Copy(gUnk_09515338 + 0x20 + CARD_SLOT_OFFSET(slot, 1), dst + 0x40, 20);
        break;
    case 1:
        RequestDma3Copy(gUnk_0951534C + CARD_SLOT_OFFSET(slot, 1), dst, 20);
        RequestDma3Copy(gUnk_0951534C + 0x20 + CARD_SLOT_OFFSET(slot, 1), dst + 0x40, 20);
        break;
    }
}

void DrawCardTotals() {
    u8 d1[3];
    u8 d2[3];
    u16 a;
    u16 b;

    u8* base;

    a = CountCardsInDecks();
    b = CountCollectionCards();

    d1[0] = a / 100;
    d1[1] = a / 10 - d1[0] * 10;
    d1[2] = a - d1[0] * 100 - d1[1] * 10;
    d2[0] = b / 100;
    d2[1] = b / 10 - d2[0] * 10;
    d2[2] = b - d2[0] * 100 - d2[1] * 10;
    base = GetBgCharBase(3);
    RequestDma3Copy(&gUnk_0940F938[(d1[0] + 1) * 32], base + 0x2A0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d1[1] + 1) * 32], base + 0x2C0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d1[2] + 1) * 32], base + 0x2E0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d2[0] + 1) * 32], base + 0x300, 32);
    RequestDma3Copy(&gUnk_0940F938[(d2[1] + 1) * 32], base + 0x320, 32);
    RequestDma3Copy(&gUnk_0940F938[(d2[2] + 1) * 32], base + 0x340, 32);
}

void LoadDeckNameTexts(DeckMenuWork* w) {
    InitTextSlots(w->textSlots, 8);
    InitTextSlots(w->textSlots2, 8);
    InitTextSlots(w->textSlots3, 8);
    w->textSlotCount = LoadTextSlots(GetDeckName(0), w->textSlots);
    w->textSlotCount2 = LoadTextSlots(GetDeckName(1), w->textSlots2);
    w->textSlotCount3 = LoadTextSlots(GetDeckName(2), w->textSlots3);
}

void LoadCardNameText(DeckMenuWork* w, s32 id) {
    const CardDef* def;

    def = &gCardDefs[id];
#ifdef VERSION_EU
    w->textSlotCount4 = LoadTextSlots(eu_0805E924(def->name), w->textSlots4);
#else
    w->textSlotCount4 = LoadTextSlots(def->name, w->textSlots4);
#endif

    switch (def->category) {
    case 0:
        LoadPalette(gUnk_09614458,
                    (void*)(w->palette4->index * 32 +
                            OBJ_PLTT),
                    w->palette4->count << 5);
        break;
    case 1:
        LoadPalette(gUnk_09614478,
                    (void*)(w->palette4->index * 32 +
                            OBJ_PLTT),
                    w->palette4->count << 5);
        break;
    case 2:
        LoadPalette(gUnk_09614498,
                    (void*)(w->palette4->index * 32 +
                            OBJ_PLTT),
                    w->palette4->count << 5);
        break;
    case 3:
        LoadPalette(gUnk_096144B8,
                    (void*)(w->palette4->index * 32 +
                            OBJ_PLTT),
                    w->palette4->count << 5);
        break;
    }
}

void LoadCardDescriptionText(DeckMenuWork* w, u16 index) {
    const CardDef* d;
    void* s;

    d = &gCardDefs[index];
    s = gCardKindDescriptions[d->kind];
    w->textSlotCount5 = LoadTextSlots(LANGSTR(s), w->textSlots5);
}

s32 ShowCollectionCardPreview(DeckMenuWork* w) {
    DeckCard2Work* t;
    const CardDef* def;
    void* dst;
    u16 id;
    u16 flag;
    u16 v;
    u8 i;
    u8 j;
    u16 k;

    id = 0xFFFF;
    t = ListPoolFirst(&w->pool);

    while (t != NULL) {
        if (t->args.row == w->cursorRow &&
            t->args.col == w->cursorCol) {
            id = t->args.cardId;
            break;
        }

        t = ListPoolNext(&t->node);
    }

    ReleaseCardPreview(w);

    if (id != 0xFFFF) {
        flag = id & 0x8000;

        if (flag != 0) {
            w->tiles10 = AllocObjTiles(0x280, NULL);
            SetObjTileSource(w->tiles10, gUnk_0908B1B4);
            AnimInit(&w->anim, gUnk_09EEA164, gUnk_09EEA148);
            AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
            w->gfx3 = AnimGetGfx(&w->anim);
        }

        def = &gCardDefs[id & 0xFFF];
        w->tiles7 = LoadObjTiles(gCardBacks[def->category].tiles, 0x300);
        w->tiles8 = LoadObjTiles(def->tiles, 0x200);
        w->palette6 = LoadObjPalette(def->palette, 32);
        w->palette5 = LoadObjPalette(gCard00Palette, 32);
        w->gfx4 = gCardBacks[def->category].gfx;
        w->gfx5 = def->gfx;

        for (i = 0; i < w->entryCount; i++) {
            if ((u16)(id & 0x8000) != 0) {
                if (w->entries[i].kind ==
                    def->kind + 143) {
                    break;
                }
            } else {
                if (w->entries[i].kind ==
                    def->kind) {
                    break;
                }
            }
        }

        w->entryIndex = i;
        dst = gUnk_05000160;
        LoadPalette(&gUnk_09614318[def->category * 16], dst, 32);

        for (j = 0; j <= 9; j++) {
            DrawValueCount(w->entries[i].valueCounts[j], j);
        }

        v = id & 0xFFF;
        LoadCardNameText(w, v);
        LoadCardDescriptionText(w, v);

        if (w->view >= 9 &&w->view <= 12) {
            if (def->kind > 46) {
                LoadBgMap(2, gUnk_09518AB8, 0x800);
                DrawCpCost(GetCardCpCost(id));
                return id;
            }

            LoadBgMap(2, gUnk_095182B8, 0x800);
            DrawCpCost(0);
        } else if (def->kind > 46) {
            switch (w->deckIndex) {
            case 0:
                LoadBgMap(1, gUnk_09518AB8, 0x800);
                break;
            case 1:
            case 2:
                LoadBgMap(0, gUnk_09518AB8, 0x800);
                break;
            }

            DrawCpCost(0);
        } else {
            switch (w->deckIndex) {
            case 0:
                LoadBgMap(1, gUnk_095182B8, 0x800);
                break;
            case 1:
            case 2:
                LoadBgMap(0, gUnk_095182B8, 0x800);
                break;
            }

            DrawCpCost(0);
        }
    } else {
        for (k = 0; k <= 9; k++) {
            DrawValueCount(0, k);
        }

        DrawCpCost(0);
    }

    return id;
}

void ReleaseCardPreview(DeckMenuWork* w) {
    if (w->tiles10 != NULL) {
        ReleaseObjTiles(w->tiles10);
        w->tiles10 = NULL;
    }

    if (w->tiles7 != NULL) {
        ReleaseObjTiles(w->tiles7);
        ReleaseObjPalette(w->palette5);
        ReleaseObjTiles(w->tiles8);
        ReleaseObjPalette(w->palette6);

        if (w->tiles9 != NULL) {
            ReleaseObjTiles(w->tiles9);
            w->tiles9 = NULL;
        }

        w->tiles7 = NULL;
        w->palette5 = NULL;
        w->tiles8 = NULL;
        w->palette6 = NULL;
    }
}

void ShowDeckCardPreview(DeckMenuWork* w) {
    DeckCard2Work* node;
    const CardDef* def;
    void* dst;
    u16 id;

    id = 0xFFFF;
    node = ListPoolFirst(&w->pool);

    while (node != NULL) {
        if (node->args.row == w->cursorRow && node->args.col == w->cursorCol) {
            id = node->args.cardId;
            break;
        }

        node = ListPoolNext(&node->node);
    }

    ReleaseCardPreview(w);

    if (id != 0xFFFF) {
        if (id & 0x8000) {
            w->tiles10 = AllocObjTiles(0x280, NULL);
            SetObjTileSource(w->tiles10, gUnk_0908B1B4);
            AnimInit(&w->anim, gUnk_09EEA164, gUnk_09EEA148);
            AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
            w->gfx3 = AnimGetGfx(&w->anim);
        }

        def = &gCardDefs[id & CARD_ID_MASK];
        w->tiles7 = LoadObjTiles(gCardBacks[def->category].tiles, 768);
        w->tiles8 = LoadObjTiles(def->tiles, 512);
        w->palette6 = LoadObjPalette(def->palette, 32);
        w->palette5 = LoadObjPalette(gCard00Palette, 32);
        w->gfx4 = gCardBacks[def->category].gfx;
        w->gfx5 = def->gfx;

        if ((id & CARD_ID_MASK) <= 0x1C1) {
            w->tiles9 = LoadObjTiles(gUnk_0905EAE8, 480);
            w->gfx6 = gUnk_09EE981C[def->value];
        }

        DrawCpCost(GetCardCpCost(id));
        dst = gUnk_05000160;
        LoadPalette(&gUnk_09614118[def->category * 16 + 0x100], dst, 32);
        LoadCardNameText(w, id & CARD_ID_MASK);
        LoadCardDescriptionText(w, id & CARD_ID_MASK);
    } else {
        DrawCpCost(0);
    }
}

void DrawValueCount(u8 a, u16 b) {
    u8 v[2];
    u8* base;

    base = GetBgCharBase(3);

    if (a != 0) {
        u8* dst;

        v[0] = a / 10;
        v[1] = a - v[0] * 10;
        RequestDma3Copy(&gUnk_0940FA98[(v[0] + 3) * 32], dst = base + (b * 64 + 0xD20), 32);
        RequestDma3Copy(&gUnk_0940FA98[(v[1] + 3) * 32], dst += 32, 32);
    } else {
        u8* dst;

        RequestDma3Copy(gUnk_0940FAD8, dst = base + (b * 64 + 0xD20), 32);
        RequestDma3Copy(gUnk_0940FAD8, dst += 32, 32);
        LoadPalette(gUnk_09614406, (void*)(b * 2 + BG_PLTT + 11 * PLTT_SIZE_4BPP + 0xC), 2);
    }
}

void DrawSelectedValueCpCost(DeckMenuWork* w) {
    u16 t;

    t = GetCardIdForKindEntry(w->entries[w->entryIndex].kind);
    DrawCpCost(GetCardCpCost(t + w->cursorCol * 5 + (u16)w->cursorRow));
}

void DrawCpCost(u8 a) {
    u8 d[2];
    u8* base;

    base = GetBgCharBase(3);

    if (a != 0) {
        d[0] = a / 10;
        d[1] = a - d[0] * 10;
        RequestDma3Copy(&gUnk_0940FA98[(d[0] + 3) * 32], base + 0xCE0, 32);
        RequestDma3Copy(&gUnk_0940FA98[(d[1] + 3) * 32], base + 0xD00, 32);
    } else {
        RequestDma3Copy(gUnk_0940FAD8, base + 0xCE0, 32);
        RequestDma3Copy(gUnk_0940FAD8, base + 0xD00, 32);
    }
}

u32 SumValueCounts(u16* data) {
    u32 sum;
    u16* p;
    s32 i;

    sum = 0;
    p = data;
    i = 9;

    do {
        sum += *p++;
    } while (--i >= 0);

    return sum;
}

s32 MoveValueCursor(DeckMenuWork* w, u16 keys) {
    CardKindEntry* p;
    u8 y0;
    u8 x0;
    u8 idx;
    s8 v;
    s8 d;
    s32 i;
    s32 sum;
    s32 n;
    u16 t;
    u16 t884;
    s16 k;
    u8* x;

    k = w->cursorCol * 5 + *(u8*)&w->cursorRow;
    idx = k;
    p = &w->entries[w->entryIndex];
    t884 = *(u16*)&w->cursorCol;
    y0 = w->cursorCol;
    x0 = *(u8*)&w->cursorRow;

    if (p->valueCounts[idx] != 0) {
        return 1;
    }

    switch (keys) {
    case 64:
        do {
            t = *(u16*)&w->cursorRow;
            *(u16*)&w->cursorRow = (s16)t > 0 ? t - 1 : 4;
            idx = w->cursorCol * 5 + *(u8*)&w->cursorRow;

            if (w->cursorCol == y0 && w->cursorRow == x0) {
                return 0;
            }
        } while (p->valueCounts[idx] == 0);

        break;
    case 128:
        do {
            t = *(u16*)&w->cursorRow;
            *(u16*)&w->cursorRow = (s16)t <= 3 ? t + 1 : 0;
            idx = w->cursorCol * 5 + *(u8*)&w->cursorRow;

            if (w->cursorCol == y0 && w->cursorRow == x0) {
                return 0;
            }
        } while (p->valueCounts[idx] == 0);

        break;
    case 32:
        if (p->valueCounts[w->cursorRow] != 0) {
            if ((s16)t884 > 0) {
                *(u16*)&w->cursorCol = t884 - 1;
            }

            break;
        }

        sum = 0;

        for (i = 0; i < 5; i++) {
            sum += p->valueCounts[i];
        }

        if (sum == 0) {
            *(u16*)&w->cursorCol = 1;
            return 0;
        }

        x = (u8*)&w->cursorRow;
        d = -1;
        n = *x + d;

        while (1) {
            v = n;

            if (v < 0) {
                v = 0;
            }

            if (v > 4) {
                v = 4;
            }

            if (p->valueCounts[v] != 0) {
                break;
            }

            if (d < 0) {
                d = -d;
            } else {
                d = d + 1;
                d = -d;
            }

            n = d + *x;
        }

        goto store;
    case 16:
        if (p->valueCounts[w->cursorRow + 5] != 0) {
            if ((s16)t884 <= 0) {
                *(u16*)&w->cursorCol = t884 + 1;
            }

            break;
        }

        sum = 0;

        for (i = 0; i < 5; i++) {
            sum += p->valueCounts[i + 5];
        }

        if (sum == 0) {
            *(u16*)&w->cursorCol = 0;
            return 0;
        }

        x = (u8*)&w->cursorRow;
        d = -1;
        n = *x + d;

        for (;;) {
            v = n;

            if (v < 0) {
                v = 0;
            }

            if (v > 4) {
                v = 4;
            }

            if (p->valueCounts[v + 5] != 0) {
                break;
            }

            if (d < 0) {
                d = -d;
            } else {
                d = d + 1;
                d = -d;
            }

            n = d + *x;
        }

store:
        k = v;
        *(u16*)&w->cursorRow = k;
        break;
    case 0:
        do {
            t = *(u16*)&w->cursorRow;

            if ((s16)t <= 3) {
                *(u16*)&w->cursorRow = t + 1;
            } else {
                *(u16*)&w->cursorRow = 0;
            }

            if (w->cursorCol == y0 && w->cursorRow == x0) {
                t884 = *(u16*)&w->cursorCol;

                if ((s16)t884 <= 0) {
                    *(u16*)&w->cursorCol = t884 + 1;
                } else {
                    *(u16*)&w->cursorCol = 0;
                }

                *(u16*)&w->cursorRow = 0;

                if (SumValueCounts(p->valueCounts) == 0) {
                    return 0;
                }
            }

            idx = w->cursorCol * 5 + *(u8*)&w->cursorRow;
        } while (p->valueCounts[idx] == 0);

        break;
    }

    return 1;
}

s32 AddSelectedValueCardToDeck(DeckMenuWork* w) {
    u16 mask;
    u16 idx;
    CardKindEntry* e;
    u16 i;
    u16 card;
    u16 v;
    u32 id;
    const CardDef* def;

    mask = 0;
    idx = w->cursorCol * 5 + w->cursorRow;

    switch (w->deckIndex) {
    case 0:
        mask = 0x1000;
        break;
    case 1:
        mask = 0x2000;
        break;
    case 2:
        mask = 0x4000;
        break;
    }

    e = &w->entries[w->entryIndex];

    if (e->valueCounts[idx] == 0) {
        m4aSongNumStart(SONG_SYS_BEEP);
        return 0;
    }

    for (i = 0; i < e->count; i++) {
        card = e->indices[i];
        v = gCardCollection[card];

        if (!(mask & v)) {
            id = v & 0xFFF;
            def = &gCardDefs[id];

            if (id > 0x1C1) {
                if (idx == 0) {
                    AddCardToDeck(card, w->deckIndex);
                    e->valueCounts[idx]--;
                    DrawValueCount(e->valueCounts[idx], idx);
                    m4aSongNumStart(SONG_SYS_KETTEI);
                    return e->valueCounts[idx];
                }
            } else if (def->value == idx) {
                AddCardToDeck(card, w->deckIndex);
                e->valueCounts[idx]--;
                DrawValueCount(e->valueCounts[idx], idx);
                m4aSongNumStart(SONG_SYS_KETTEI);
                return e->valueCounts[idx];
            }
        }
    }

    m4aSongNumStart(SONG_SYS_BEEP);
}

void FreeCollectionEntries(DeckMenuWork* w) {
    u16 i;

    if (w->entries != NULL) {
        for (i = 0; i < w->entryCount; i++) {
            EwramFree(w->entries[i].indices);
        }

        EwramFree(w->entries);
        w->entries = NULL;
    }
}

void ReleaseCommandMenuGfx(DeckMenuWork* w) {
    if (w->tiles3 != NULL) {
        ReleaseObjTiles(w->tiles3);
        ReleaseObjPalette(w->palette2);
        w->tiles3 = NULL;
        w->palette2 = NULL;
    }
}

void SetDeckMenuFrameCursor(DeckMenuWork* w, u8 kind) {
    switch (kind) {
    case 0:
        SetObjTileSource(w->tiles2, gUnk_090A4A0C);
        AnimInit(&w->anim3, gUnk_09EEB064, gUnk_09EEB050);
        AnimStart(&w->anim3, 0, ANIM_FLAG_LOOP);
        w->gfx2 = AnimGetGfx(&w->anim3);
        break;
    case 1:
        SetObjTileSource(w->tiles2, gUnk_090A51F6);
        AnimInit(&w->anim3, gUnk_09EEB07C, gUnk_09EEB068);
        AnimStart(&w->anim3, 0, ANIM_FLAG_LOOP);
        w->gfx2 = AnimGetGfx(&w->anim3);
        break;
    }
}

void RemoveCursorCardFromDeck(DeckMenuWork* w) {
    DeckCard2Work* n;

    n = ListPoolFirst(&w->pool);

    while (n != NULL) {
        if (n->args.row == w->cursorRow && n->args.col == w->cursorCol) {
            if (n->args.cardId != 0xFFFF) {
                RemoveCardFromDeck(n->args.slot, w->deckIndex);
                n->done = 1;
                n->args.row = (u16)n->args.row | 0xFFFF;
                m4aSongNumStart(SONG_SYS_KETTEI);
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }

            return;
        }

        n = ListPoolNext(&n->node);
    }

    m4aSongNumStart(SONG_SYS_BEEP);
}

u8 CheckCardDeletable(DeckMenuWork* w) {
    u16 idx;
    CardKindEntry* e;
    u16 i;
    u16 id;
    u16 c;
    const CardDef* def;

    idx = w->cursorCol * 5 + w->cursorRow;
    e = &w->entries[w->entryIndex];

    if (e->valueCounts[idx] == 0) {
        m4aSongNumStart(SONG_SYS_BEEP);
        return 1;
    }

    for (i = 0; i < e->count; i++) {
        id = e->indices[i];

        if (id == 0xFFFF) {
            continue;
        }

        c = gCardCollection[id] & CARD_ID_MASK;
        def = &gCardDefs[c];

        if (c > 0x1C2) {
            if (idx != 0) {
                continue;
            }

            if (def->category != 0) {
                return 1;
            }

            if (CountCollectionCardsOfCategory(def->category) > 1) {
                return 1;
            }

            TaskCreate(&w->cardpool, &gTaskDescDeckErrorLastAttackCard, &w->popupActive);
            m4aSongNumStart(SONG_SYS_BEEP);
            return 0;
        } else {
            if (def->value != idx) {
                continue;
            }

            if (def->category != 0) {
                return 1;
            }

            if (CountCollectionCardsOfCategory(def->category) > 1) {
                return 1;
            }

            TaskCreate(&w->cardpool, &gTaskDescDeckErrorLastAttackCard, &w->popupActive);
            m4aSongNumStart(SONG_SYS_BEEP);
            return 0;
        }
    }

    return 1;
}

u8 DeleteSelectedValueCard(DeckMenuWork* w) {
    u16 idx;
    CardKindEntry* e;
    u16 i;
    u16 card;
    u16 id;
    const CardDef* def;

    idx = w->cursorCol * 5 + w->cursorRow;
    e = &w->entries[w->entryIndex];

    if (e->valueCounts[idx] == 0) {
        m4aSongNumStart(SONG_SYS_BEEP);
        return 1;
    }

    for (i = 0; i < e->count; i++) {
        card = e->indices[i];

        if (card != 0xFFFF) {
            id = gCardCollection[card] & CARD_ID_MASK;
            def = &gCardDefs[id];

            if (id >= 0x1C2) {
                if (idx == 0) {
                    if (def->category == 0) {
                        if (CountCollectionCardsOfCategory(def->category) > 1) {
                            ClearCardCollectionSlot(&gCardCollection[card]);
                            e->indices[i] = 0xFFFF;
                            e->valueCounts[idx]--;
                            DrawValueCount(e->valueCounts[idx], idx);
                            m4aSongNumStart(SONG_SYS_CARD_DELETE);
                            return 1;
                        } else {
                            TaskCreate(&w->cardpool, &gTaskDescDeckErrorLastAttackCard, &w->popupActive);
                            m4aSongNumStart(SONG_SYS_BEEP);
                            return 0;
                        }
                    } else {
                        ClearCardCollectionSlot(&gCardCollection[card]);
                        e->indices[i] = 0xFFFF;
                        e->valueCounts[idx]--;
                        DrawValueCount(e->valueCounts[idx], idx);
                        m4aSongNumStart(SONG_SYS_CARD_DELETE);
                        return 1;
                    }
                }
            } else if (def->value == idx) {
                if (def->category == 0) {
                    if (CountCollectionCardsOfCategory(def->category) > 1) {
                        ClearCardCollectionSlot(&gCardCollection[card]);
                        e->indices[i] = 0xFFFF;
                        e->valueCounts[idx]--;
                        DrawValueCount(e->valueCounts[idx], idx);
                        m4aSongNumStart(SONG_SYS_CARD_DELETE);
                        return 1;
                    } else {
                        TaskCreate(&w->cardpool, &gTaskDescDeckErrorLastAttackCard, &w->popupActive);
                        m4aSongNumStart(SONG_SYS_BEEP);
                        return 0;
                    }
                } else {
                    ClearCardCollectionSlot(&gCardCollection[card]);
                    e->indices[i] = 0xFFFF;
                    e->valueCounts[idx]--;
                    DrawValueCount(e->valueCounts[idx], idx);
                    m4aSongNumStart(SONG_SYS_CARD_DELETE);
                    return 1;
                }
            }
        }
    }

    m4aSongNumStart(SONG_SYS_BEEP);
    return 1;
}

s32 CheckDeckCpCost(DeckMenuWork* w) {
    if (GetDeckCpCost(GetActiveDeckIndex()) > gGameState.progression.cp) {
        TaskCreate(&w->cardpool, &gTaskDescDeckErrorCp, &w->popupActive);
        m4aSongNumStart(SONG_SYS_BEEP);

        return 0;
    }

    return 1;
}

s32 CheckDeckHasAttackCard(DeckMenuWork* w) {
    if (CountActiveDeckCardsOfCategory(0) == 0) {
        m4aSongNumStart(SONG_SYS_BEEP);
        TaskCreate(&w->cardpool, &gTaskDescDeckErrorNoAttackCard, &w->popupActive);

        return 0;
    }

    return 1;
}

void ResetGridScroll(DeckMenuWork* w) {
    DeckCard2Work* node;
    s16 x;
    s16 y;

    node = ListPoolFirst(&w->pool);
    x = 0;
    y = 0;

    while (node != NULL) {
        node->args.col = x;
        node->args.row = y;
        x++;

        if (node->flags & DECK_CARD2_FLAG_GFX_LOADED) {
            ReleaseObjPalette(node->palette2);
            ReleaseObjTiles(node->tiles);
            ReleaseObjPalette(node->palette);
            ReleaseObjTiles(node->tiles2);
            node->flags &= ~DECK_CARD2_FLAG_GFX_LOADED;
            node->tiles = NULL;
            node->palette = NULL;
            node->tiles2 = NULL;
            node->palette2 = NULL;
        }

        if (x > 2) {
            x = 0;
            y++;
        }

        node = ListPoolNext(&node->node);
    }

    w->y2 = 0x2800;
    w->scrollRowEnd = 4;
}

s32 IsCardAtCursor(DeckMenuWork* w) {
    DeckCard2Work* t;

    t = ListPoolFirst(&w->pool);

    while (t != NULL) {
        if (t->args.col == w->cursorCol) {
            if (t->args.row == w->cursorRow) {
                return 1;
            }
        }

        t = ListPoolNext(&t->node);
    }

    return 0;
}

u8 IsCardAt(DeckMenuWork* w, s16 a, s16 b) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    while (node != NULL) {
        if (node->args.col == a && node->args.row == b) {
            return 1;
        }

        node = ListPoolNext(&node->node);
    }

    return 0;
}

u8 FindCardInDirection(DeckMenuWork* w, s16 x, s16 y, u16 dir) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    while (node != NULL) {
        if (node->args.col == x && node->args.row == y) {
            return 1;
        }

        node = ListPoolNext(&node->node);
    }

    switch (dir) {
    case 0x40:
        return FindCardInDirection(w, x, y - 1, 0x40);
    case 0x80:
        return FindCardInDirection(w, x, y + 1, 0x80);
    case 0x20:
        return FindCardInDirection(w, x - 1, y, 0x20);
    case 0x10:
        return FindCardInDirection(w, x + 1, y, 0x10);
    }

    return 0;
}

void RecreateDeckGridCards(DeckMenuWork* w, u8 kind) {
    DeckCard2Args args;
    u16* deck;
    u8 i;
    s8 x;
    s8 y;

    deck = (u16*)GetDeck(w->deckIndex);
    x = 0;
    y = 4 - w->scrollRowEnd;

    if (kind == 0) {
        for (i = 0; i < 99; i++) {
            if (deck[i] != 0xFFFF) {
                if (kind == 0) {
                    args.pool = &w->pool;
                    args.cardId = gCardCollection[deck[i]] & 0x8FFF;
                    args.col = x;
                    args.row = y;
                    args.panel = 0;
                    args.slot = &deck[i];
                    TaskCreate(&w->taskpool, &gTaskDescDeckCard2, &args);
                } else if (gCardDefs[gCardCollection[deck[i]] & 0xFFF].category == kind - 1) {
                    args.pool = &w->pool;
                    args.cardId = gCardCollection[deck[i]] & 0x8FFF;
                    args.col = x;
                    args.row = y;
                    args.panel = 0;
                    args.slot = &deck[i];
                    TaskCreate(&w->taskpool, &gTaskDescDeckCard2, &args);
                }
            } else {
                args.pool = &w->pool;
                args.cardId = 0xFFFF;
                args.col = x;
                args.row = y;
                args.panel = 0;
                args.slot = &deck[i];
                TaskCreate(&w->taskpool, &gTaskDescDeckCard2, &args);
            }

            x++;

            if (x > 2) {
                x = 0;
                y++;
            }
        }
    } else {
        for (i = 0; i < 99; i++) {
            if (deck[i] != 0xFFFF && gCardDefs[gCardCollection[deck[i]] & 0xFFF].category == kind - 1) {
                args.pool = &w->pool;
                args.cardId = gCardCollection[deck[i]] & 0x8FFF;
                args.col = x;
                args.row = y;
                args.panel = 0;
                args.slot = &deck[i];
                TaskCreate(&w->taskpool, &gTaskDescDeckCard2, &args);
                x++;
            }

            if (x > 2) {
                x = 0;
                y++;
            }
        }
    }
}

u8 ToggleDeckSlotGap(DeckMenuWork* w) {
    DeckCard2Work* p;
    DeckCard2Work* q;
    DeckCard2Work* last;
    DeckCard2Work* n;

    p = ListPoolFirst(&w->pool);
    last = ListPoolLast(&w->pool);
    q = NULL;

    while (p != NULL) {
        if (w->cursorCol == p->args.col && w->cursorRow == p->args.row) {
            q = p;
            break;
        }

        p = ListPoolNext(&p->node);
    }

    if (p->args.cardId != 0xFFFF) {
        while (q != NULL) {
            if (q->args.cardId == 0xFFFF) {
                break;
            }

            q = ListPoolNext(&q->node);
        }

        if (q != NULL) {
            while (p != q) {
                n = ListPoolPrev(&q->node);

                if (n != NULL) {
                    *q->args.slot = *n->args.slot;
                }

                q = ListPoolPrev(&q->node);
            }

            *p->args.slot = 0xFFFF;
            ClearCardGrid(w);
            TaskPoolUpdate(&w->taskpool);
            RecreateDeckGridCards(w, w->categoryFilter);
            w->cursorCol++;

            if (w->cursorCol > 2) {
                w->cursorCol = 0;

                if (w->cursorRow <= 2) {
                    w->cursorRow++;
                } else {
                    ScrollGridDown(w);
                }
            }

            w->timer = 1;
            return 1;
        }
    } else {
        while (p != NULL) {
            n = ListPoolNext(&p->node);

            if (n != NULL) {
                *p->args.slot = *n->args.slot;
            }

            p = ListPoolNext(&p->node);
        }

        *last->args.slot = 0xFFFF;
        ClearCardGrid(w);
        TaskPoolUpdate(&w->taskpool);
        RecreateDeckGridCards(w, w->categoryFilter);
        return 1;
    }

    return 0;
}

u8 SwapHeldDeckCard(DeckMenuWork* w) {
    DeckCard2Work* p;
    DeckCard2Work* q;
    DeckCard2Work* n;
    DeckCard2Work* prev;
    u16* a;
    u16* b;
    s16 x;
    s16 y;
    u16 u;
    u16 v;

    p = ListPoolFirst(&w->pool);
    q = ListPoolFirst(&w->pool);

    if (w->cursorCol == w->heldCol && w->cursorRow == w->heldRow) {
        return ToggleDeckSlotGap(w);
    }

    while (p != NULL) {
        if (w->cursorCol == p->args.col && w->cursorRow == p->args.row) {
            break;
        }

        p = ListPoolNext(&p->node);
    }

    if (p == NULL) {
        return 0;
    }

    while (q != NULL) {
        if (w->heldCol == q->args.col &&w->heldRow == q->args.row) {
            break;
        }

        q = ListPoolNext(&q->node);
    }

    x = p->args.col;
    y = p->args.row;
    p->args.col = q->args.col;
    p->args.row = q->args.row;
    q->args.col = x;
    q->args.row = y;
    a = p->args.slot;
    u = *a;
    b = q->args.slot;
    v = *b;
    *a = v;
    *b = u;
    p->args.slot = b;
    q->args.slot = a;

    if (ListPoolPrev(&p->node) == (MapcardWork*)q) {
        ListPoolRemove(&p->node, &w->pool);
        ListPoolInsertBefore(&p->node, &w->pool, &q->node);

        for (n = ListPoolFirst(&w->pool); n != NULL; n = ListPoolNext(&n->node)) {
            if (n == ListPoolNext(&n->node)) {
                break;
            }
        }
    } else if (ListPoolNext(&p->node) == q) {
        ListPoolRemove(&p->node, &w->pool);
        ListPoolInsertAfter(&p->node, &w->pool, &q->node);

        for (n = ListPoolFirst(&w->pool); n != NULL; n = ListPoolNext(&n->node)) {
            if (n == ListPoolNext(&n->node)) {
                break;
            }
        }
    } else {
        prev = ListPoolRemove(&p->node, &w->pool);
        ListPoolInsertBefore(&p->node, &w->pool, &q->node);
        ListPoolRemove(&q->node, &w->pool);

        if (prev == NULL) {
            ListPoolAppend(&q->node, &w->pool);
        } else {
            ListPoolInsertBefore(&q->node, &w->pool, &prev->node);
        }
    }

    return 1;
}

u8 WrapKanaKeyboardCursor(DeckMenuWork* w, u16 dir) {
    u16 row;
    u16 row2;

    row = w->cursor.parts.y;

    if ((s16)row == 3 && (u16)w->cursor.parts.x > 9) {
        switch (dir) {
        case 0x40:
            w->cursor.parts.y = row - 1;
            break;
        case 0x80:
            w->cursor.parts.y = row + 1;
            break;
        case 0x20:
            w->cursor.parts.x = 9;
            break;
        case 0x10:
            w->cursor.parts.x = 0;
            break;
        }
    }

    if (w->keyboardPage == 0) {
        row2 = w->cursor.parts.y;

        if ((s16)row2 == 5 && (u16)(w->cursor.parts.x - 5) <= 4) {
            switch (dir) {
            case 0x40:
                w->cursor.parts.y = row2 - 1;
                break;
            case 0x80:
                w->cursor.parts.y = row2 + 1;
                break;
            case 0x20:
                w->cursor.parts.x = 4;
                break;
            case 0x10:
                w->cursor.parts.x = 10;
                break;
            }
        }
    }

    if (w->cursor.parts.y > 6) {
        w->cursor.parts.y = 0;
    }

    if (w->cursor.parts.y < 0) {
        w->cursor.parts.y = 6;
    }

    if (w->cursor.parts.x > 14) {
        w->cursor.parts.x = 0;
    }

    if (w->cursor.parts.x < 0) {
        w->cursor.parts.x = 14;
    }

    if (w->cursor.parts.y == 6 && w->cursor.parts.x > 11) {
        if (w->cursor.parts.x == 13 && dir == 0x20) {
            w->cursor.parts.x = 11;
            AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
        } else {
            w->cursor.parts.x = 14;
            AnimStart(&w->anim4, 1, ANIM_FLAG_LOOP);
        }

        return 0;
    }

    return 1;
}

u8 WrapKeyboardCursor(DeckMenuWork* w, u16 keys) {
    if (w->cursor.parts.y == 1 && (u16)w->cursor.parts.x > 10) {
        switch (keys) {
        case 64:
            w->cursor.parts.y--;
            break;
        case 128:
            w->cursor.parts.y++;
            break;
        case 32:
            w->cursor.parts.x = 10;
            break;
        case 16:
            w->cursor.parts.x = 0;
            break;
        }
    }

    if (w->cursor.parts.y == 3 && (u16)w->cursor.parts.x > 10) {
        switch (keys) {
        case 64:
            w->cursor.parts.y--;
            break;
        case 128:
            w->cursor.parts.y++;
            break;
        case 32:
            w->cursor.parts.x = 10;
            break;
        case 16:
            w->cursor.parts.x = 0;
            break;
        }
    }

#if defined(VERSION_JP) || defined(VERSION_EU)
#ifdef VERSION_JP
    if (w->cursor.parts.y == 4 && (u16)w->cursor.parts.x > 9) {
#else
    if (w->cursor.parts.y == 5 && (u16)w->cursor.parts.x > 9) {
#endif
        switch (keys) {
        case 64:
#ifdef VERSION_JP
            w->cursor.parts.y -= 2;
#else
            w->cursor.parts.y--;
#endif
            break;
        case 128:
            w->cursor.parts.y++;
            break;
        case 32:
            w->cursor.parts.x = 9;
            break;
        case 16:
            w->cursor.parts.x = 0;
            break;
        }
    }
#endif

    if (w->cursor.parts.x > 14) {
        w->cursor.parts.x = 0;
    }

    if (w->cursor.parts.x < 0) {
        w->cursor.parts.x = 14;
    }

#ifdef VERSION_EU
    if (w->cursor.parts.y > 7) {
#else
    if (w->cursor.parts.y > 6) {
#endif
        w->cursor.parts.y = 0;
    }

    if (w->cursor.parts.y < 0) {
#ifdef VERSION_EU
        w->cursor.parts.y = 7;
#else
        w->cursor.parts.y = 6;
#endif
    }

#ifndef VERSION_JP
    if (w->cursor.parts.x > gKeyboardRowLayouts[w->cursor.parts.y].count - 1) {
        w->cursor.parts.x = 0;
    }

    if (w->cursor.parts.x < 0) {
        w->cursor.parts.x = gKeyboardRowLayouts[w->cursor.parts.y].count - 1;
    }

    if (w->cursor.parts.y > gKeyboardColumnLayouts[w->cursor.parts.x].count - 1) {
        w->cursor.parts.y = 0;
    }

    if (w->cursor.parts.y < 0) {
        w->cursor.parts.y = gKeyboardColumnLayouts[w->cursor.parts.x].count - 1;
    }
#endif

#ifdef VERSION_EU
    if (w->cursor.parts.y == 7 &&w->cursor.parts.x > 9) {
#else
    if (w->cursor.parts.y == 6 &&w->cursor.parts.x > 9) {
#endif
        if (w->cursor.parts.x == 13 && keys == 32) {
            w->cursor.parts.x = 9;
            AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
#ifdef VERSION_EU
            w->onEndKey = 0;
#endif
        } else {
            w->cursor.parts.x = 14;
            AnimStart(&w->anim4, 1, ANIM_FLAG_LOOP);
#ifdef VERSION_EU
            w->onEndKey = 1;
#endif
        }

        return 0;
    }

    return 1;
}

#ifdef VERSION_EU
u8 func_eu_0808E94C(DeckMenuWork* w, u16 keys) {
    if (w->cursor.parts.y == 1 && (u16)w->cursor.parts.x > 5) {
        switch (keys) {
        case 64:
            w->cursor.parts.y--;
            break;
        case 128:
            w->cursor.parts.y++;
            break;
        case 32:
            w->cursor.parts.x = 5;
            break;
        case 16:
            w->cursor.parts.x = 0;
            break;
        }
    }

    if (w->cursor.parts.y == 4 && (u16)w->cursor.parts.x > 2) {
        switch (keys) {
        case 64:
            w->cursor.parts.y--;
            break;
        case 128:
            w->cursor.parts.y++;
            break;
        case 32:
            w->cursor.parts.x = 2;
            break;
        case 16:
            w->cursor.parts.x = 0;
            break;
        }
    }

    if (w->cursor.parts.x > 14) {
        w->cursor.parts.x = 0;
    }

    if (w->cursor.parts.x < 0) {
        w->cursor.parts.x = 14;
    }

    if (w->cursor.parts.y > 6) {
        w->cursor.parts.y = 0;
    }

    if (w->cursor.parts.y < 0) {
        w->cursor.parts.y = 6;
    }

    if (w->cursor.parts.x > gKeyboardSymbolRowLayouts[w->cursor.parts.y].count - 1) {
        w->cursor.parts.x = 0;
    }

    if (w->cursor.parts.x < 0) {
        w->cursor.parts.x = gKeyboardSymbolRowLayouts[w->cursor.parts.y].count - 1;
    }

    if (w->cursor.parts.y > gKeyboardSymbolColumnLayouts[w->cursor.parts.x].count - 1) {
        w->cursor.parts.y = 0;
    }

    if (w->cursor.parts.y < 0) {
        w->cursor.parts.y = gKeyboardSymbolColumnLayouts[w->cursor.parts.x].count - 1;
    }

    if (w->cursor.parts.y == 6 &&w->cursor.parts.x > 1) {
        if (w->cursor.parts.x == 13 && keys == 32) {
            w->cursor.parts.x = 1;
            AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
            w->onEndKey = 0;
        } else {
            w->cursor.parts.x = 14;
            AnimStart(&w->anim4, 1, ANIM_FLAG_LOOP);
            w->onEndKey = 1;
        }

        return 0;
    }

    return 1;
}
#endif

void DrawKeyboardDeckNumber(u8 a) {
    u8* base;

    base = GetBgCharBase(3);
    RequestDma3Copy(&gUnk_09417378[a * 64], base + 32, 64);
}

void CopyDeckNameToBuffer(DeckMenuWork* w) {
    u8* s;
    u8* d;
    s32 i;

    s = GetDeckName(w->deckIndex);

    for (i = 0; i <= 19; i++) {
        d = w->nameBuffer;
        d[i] = s[i];
    }

    w->nameBuffer[18] = 0;
    w->nameBuffer[19] = 0;
}

void SaveDeckNameFromBuffer(DeckMenuWork* w) {
    u8* d;
    u8* s;
    s32 i;

    d = GetDeckName(w->deckIndex);

    for (i = 0; i <= 19; i++) {
        s = w->nameBuffer;
        d[i] = s[i];
    }

    d[18] = 0;
    d[19] = 0;
}

void DeleteLastNameChar(DeckMenuWork* w) {
    u8* p;
    s32 t;
    u8 i;

    if (w->textSlotCount6 == 0) {
        m4aSongNumStart(SONG_SYS_BEEP);
        return;
    }

#ifdef VERSION_EU
    for (i = w->textSlotCount6 - 1; i <= 19; i++) {
        p = w->nameBuffer;
        p[i] = 0;
    }
#else
    for (i = w->textSlotCount6 - 1; i <= 8; i++) {
        p = w->nameBuffer;
        t = i * 2;
        p[t] = 0;
        t++;
        p[t] = 0;
    }
#endif

    m4aSongNumStart(SONG_SYS_CLOSE);
}

s32 AppendKeyboardChar(DeckMenuWork* w) {
    const u8* src = NULL;
    u8* dst;
    s32 offset;
    s32 zero;
    s32 offset2;
    u8 value;
    u8* out;

    if (w->textSlotCount6 <= 7) {
        m4aSongNumStart(SONG_SYS_KETTEI);

#ifdef VERSION_EU
        if (w->keyboardPage == 2) {
            src = gDeckKeyboardLetterRows[w->cursor.parts.y];
        } else {
            src = gDeckKeyboardSymbolRows[w->cursor.parts.y];
        }
#else
#ifdef VERSION_JP
        switch (w->keyboardPage) {
        case 0:
            src = gDeckKeyboardRows[w->cursor.parts.y];
            break;
        case 1:
            src = gDeckKeyboardKatakanaRows[w->cursor.parts.y];
            break;
        case 2:
            src = gDeckKeyboardAlphanumericRows[w->cursor.parts.y];
            break;
        }
#else
        src = gDeckKeyboardRows[w->cursor.parts.y];
#endif
#endif
#ifdef VERSION_EU
        offset = w->textSlotCount6;
        dst = w->nameBuffer;
        out = &dst[offset];
        value = src[w->cursor.parts.x];
        zero = 0;
        *out = value;
        offset2 = w->textSlotCount6 + 1;
        dst[offset2] = zero;
#else
        offset = w->textSlotCount6 * 2;
        dst = w->nameBuffer;
        out = &dst[offset];
        value = src[w->cursor.parts.x * 2];
        zero = 0;
        *out = value;
        offset2 = w->textSlotCount6 * 2;
        offset2++;
        dst[offset2] = src[w->cursor.parts.x * 2 + 1];
        offset = (w->textSlotCount6 + 1) * 2;
        dst[offset] = zero;
        offset = (w->textSlotCount6 + 1) * 2;
        offset++;
        dst[offset] = zero;
#endif
        return 1;
    } else {
        m4aSongNumStart(SONG_SYS_BEEP);
        return 0;
    }
}

#if defined(VERSION_JP) || defined(VERSION_EU)
void func_jp_0808F240(DeckMenuWork* w) {
    switch (w->keyboardPage) {
#ifdef VERSION_JP
    case 0:
        if (w->cursor.parts.y == 5 && (u16)(w->cursor.parts.x - 5) <= 4) {
            w->cursor.parts.x = 4;
        }

        break;
    case 1:
        switch (w->cursor.parts.y) {
        case 0:
        case 1:
        case 2:
            break;
        case 3:
            if (w->cursor.parts.x > 9) {
                w->cursor.parts.x = 9;
            }

            break;
        case 4:
        case 5:
        case 6:
            break;
        }

        break;
    case 2:
        switch (w->cursor.parts.y) {
        case 0:
            break;
        case 1:
            if (w->cursor.parts.x > 10) {
                w->cursor.parts.x = 10;
            }

            break;
        case 2:
        case 3:
            break;
        case 4:
            if (w->cursor.parts.x > 9) {
                w->cursor.parts.x = 9;
            }

            break;
        case 5:
            break;
        case 6:
            if (w->cursor.parts.x >= 10 &&w->cursor.parts.x <= 13) {
                w->cursor.parts.x = 9;
            }

            break;
        }

        break;
#else
    case 2:
        switch (w->cursor.parts.y) {
        case 0:
            break;
        case 1:
        case 3:
            if (w->cursor.parts.x > 10) {
                w->cursor.parts.x = 10;
            }

            break;
        case 2:
        case 4:
            break;
        case 5:
            if (w->cursor.parts.x > 9) {
                w->cursor.parts.x = 9;
            }

            break;
        case 6:
            if (w->onEndKey == 1) {
                w->cursor.parts.x = 14;
                w->cursor.parts.y = 7;
            }

            break;
        case 7:
            if (w->cursor.parts.x >= 10 &&w->cursor.parts.x <= 13) {
                w->cursor.parts.x = 9;
            }

            break;
        }

        break;
    case 3:
        switch (w->cursor.parts.y) {
        case 0:
            break;
        case 1:
            if (w->cursor.parts.x > 5) {
                w->cursor.parts.x = 5;
            }

            break;
        case 2:
        case 3:
            break;
        case 4:
            if (w->cursor.parts.x > 2) {
                w->cursor.parts.x = 2;
            }

            break;
        case 5:
            break;
        case 6:
            if (w->onEndKey == 1) {
                w->cursor.parts.y = 6;
                w->cursor.parts.x = 14;
            } else if (w->cursor.parts.x > 1) {
                w->cursor.parts.x = 1;
            }

            break;
        case 7:
            if (w->cursor.parts.x == 14) {
                w->cursor.parts.y = 6;
            } else {
                w->cursor.parts.y = 6;
                w->cursor.parts.x = 0;
            }

            break;
        }

        break;
#endif
    }
}

void func_jp_0808F34C(DeckMenuWork* w) {
    switch (w->keyboardPage) {
#ifdef VERSION_JP
    case 0:
        LoadBgMap(3, gUnk_0951C2B8, 0x800);
        break;
    case 1:
        LoadBgMap(3, gUnkJp_094D4594, 0x800);
        break;
    case 2:
        LoadBgMap(3, gUnkJp_094D4D94, 0x800);
        break;
#else
    case 2:
        LoadBgMap(3, gUnk_0951C2B8, 0x800);
        break;
    case 3:
        LoadBgMap(3, gUnkEu_0953C324, 0x800);
        break;
#endif
    }

    func_jp_0808F240(w);
}
#endif

u8 UpdateDeckMenuOpenKeyboard(DeckMenuWork* w, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 16);

#ifdef VERSION_EU
    w->handVisible = 0;
    w->onEndKey = 0;
#endif

    switch (w->step) {
    case 0:
        w->view = 13;
        SetDeckMenuHandAnim(w);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
#ifdef VERSION_EU
        w->tiles11 = AllocObjTiles(0x400, NULL);
#else
        w->tiles11 = AllocObjTiles(0x200, NULL);
#endif
        w->palette7 = LoadObjPalette(gUnk_096145B8, 32);
        w->tiles13 = AllocSpriteFrameTiles(0x80);
#ifdef VERSION_EU
        SetObjTileSource(w->tiles11, gDeckKeyboardCursorTiles[gLanguage]);
        AnimInit(&w->anim4, gDeckKeyboardCursorAnims[gLanguage], gDeckKeyboardCursorSprites[gLanguage]);
#else
        SetObjTileSource(w->tiles11, gUnk_090A5F1E);
        AnimInit(&w->anim4, gUnk_09EEB0B8, gUnk_09EEB08C);
#endif
        AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
        w->gfx9 = AnimGetGfx(&w->anim4);
#ifdef VERSION_EU
        UpdateSpriteFrameTiles(w->tiles13, gDeckKeyboardCursorSprites[gLanguage][10], gDeckKeyboardCursorTiles[gLanguage]);
#else
        UpdateSpriteFrameTiles(w->tiles13, gUnk_09EEB08C[10], gUnk_090A5F1E);
#endif
        FreeTextSlots(w->textSlots, 8);
        FreeTextSlots(w->textSlots2, 8);
        FreeTextSlots(w->textSlots3, 8);
        FreeTextSlots(w->textSlots4, 30);
        FreeTextSlots(w->textSlots5, 90);
        InitTextSlots(w->textSlots6, 8);
        CopyDeckNameToBuffer(w);
        w->textSlotCount6 = LoadTextSlots(w->nameBuffer, w->textSlots6);
        w->x10 = (GetTextSlotsWidth(w->textSlots6, w->textSlotCount6) << 8) + 0x8300;
        break;
    case 1:
#ifdef VERSION_JP
        LoadBgTiles(3, gUnk_09417438, 0x2000);
#else
        LoadBgTiles(3, gUnk_09417438, 0x1000);
#endif
        break;
    case 2:
#ifdef VERSION_JP
        RequestDma3Copy(gUnk_09418438, (u8*)GetBgCharBase(3) + 0x2000, 0x2000);
#else
        RequestDma3Copy(gUnk_09418438, (u8*)GetBgCharBase(3) + 0x1000, 0x1000);
#endif
        break;
    case 3:
#ifdef VERSION_JP
        RequestDma3Copy(gUnk_09419438, (u8*)GetBgCharBase(3) + 0x4000, 0x2000);
#elif defined(VERSION_EU)
        RequestDma3Copy(gUnk_09419438, (u8*)GetBgCharBase(3) + 0x2000, 0x2E40);
#else
        RequestDma3Copy(gUnk_09419438, (u8*)GetBgCharBase(3) + 0x2000, 0xFE0);
#endif
        break;
    case 4:
#ifdef VERSION_JP
        RequestDma3Copy(gUnkJp_093D1694, (u8*)GetBgCharBase(3) + 0x6000, 0x1000);
#elif defined(VERSION_EU)
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            break;
        case LANGUAGE_FRENCH:
            RequestDma3Copy(gUnkEu_094F03A4, (u8*)GetBgCharBase(3) + 0x4800, 0x800);
            break;
        case LANGUAGE_GERMAN:
            RequestDma3Copy(gUnkEu_094F1BA4, (u8*)GetBgCharBase(3) + 0x4800, 0x800);
            break;
        case LANGUAGE_ITALIAN:
            RequestDma3Copy(gUnkEu_094F13A4, (u8*)GetBgCharBase(3) + 0x4800, 0x800);
            break;
        case LANGUAGE_SPANISH:
            RequestDma3Copy(gUnkEu_094F0BA4, (u8*)GetBgCharBase(3) + 0x4800, 0x800);
            break;
        }
#endif

        break;
    case 5:
        LoadBgMap(3, gUnk_0951C2B8, 0x800);
        LoadBgPalette(3, gUnk_09614518, 0xA0);
        break;
    case 6:
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuKeyboard);
        w->x9 = gKeyboardKeyX[0] << 8;
        w->y8 = gKeyboardKeyY[0] << 8;
        w->keyCursorSteps = 4;
        w->cursor.parts.x = 0;
        w->cursor.parts.y = 0;
#ifdef VERSION_JP
        w->keyboardPage = 0;
#else
        w->keyboardPage = 2;
#endif
        DrawKeyboardDeckNumber(w->deckIndex);
        break;
    }

    w->step++;
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

#if defined(VERSION_JP) || defined(VERSION_EU)
u8 func_jp_0808F638(DeckMenuWork* w, void* a) {
#ifdef VERSION_EU
    u8* mode = &w->keyboardPage;
    w->handVisible = 1;
#endif

    switch (GetKeysRepeat()) {
    case DPAD_RIGHT:
#ifdef VERSION_EU
        w->keyCursorSteps = 1;

        if (*mode <= 2) {
            (*mode)++;
#else
        if (w->keyboardPage <= 1) {
            w->keyboardPage++;
#endif
            func_jp_0808F34C(w);
            m4aSongNumStart(SONG_SYS_CANSEL);
            w->keyCursorSteps = 1;
        }

        break;
    case DPAD_LEFT:
#ifdef VERSION_EU
        w->keyCursorSteps = 1;

        if (*mode > 2) {
            (*mode)--;
#else
        if (w->keyboardPage != 0) {
            w->keyboardPage--;
#endif
            func_jp_0808F34C(w);
            m4aSongNumStart(SONG_SYS_CANSEL);
            w->keyCursorSteps = 1;
        }

        break;
    case SELECT_BUTTON:
    case DPAD_DOWN:
        w->keyCursorSteps = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuKeyboard);
        w->view = 13;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
#ifdef VERSION_EU
        w->handVisible = 0;
#endif
        return 1;
    }

#ifdef VERSION_EU
    if (w->keyCursorSteps != 0) {
        if (w->onEndKey == 1) {
            if (gLanguage == LANGUAGE_GERMAN) {
                w->x9 = 0xC800;
            } else if (gLanguage == LANGUAGE_ITALIAN) {
                w->x9 = 0xD100;
            } else {
                w->x9 = 0xD300;
            }

            w->y8 = 0x8C00;
        } else if (w->keyboardPage == 2) {
            ApproachValue(&w->x9, gKeyboardRowLayouts[w->cursor.parts.y].positions[w->cursor.parts.x] << 8, w->keyCursorSteps);
            ApproachValue(&w->y8, gKeyboardColumnLayouts[w->cursor.parts.x].positions[w->cursor.parts.y] << 8, w->keyCursorSteps);
        } else {
            ApproachValue(&w->x9, gKeyboardSymbolRowLayouts[w->cursor.parts.y].positions[w->cursor.parts.x] << 8, w->keyCursorSteps);
            ApproachValue(&w->y8, gKeyboardSymbolColumnLayouts[w->cursor.parts.x].positions[w->cursor.parts.y] << 8, w->keyCursorSteps);
        }

        w->keyCursorSteps--;
    }

    ApproachValueHalf(&w->x, (gKeyboardPageTabXEu[w->keyboardPage - 2] + 8) << 8);
#else
    ApproachValueHalf(&w->x, (gKeyboardPageTabXJp[w->keyboardPage] + 8) << 8);
#endif
    ApproachValueHalf(&w->y, 0x1A00);
    w->gfx9 = AnimUpdate(&w->anim4);
    w->gfx = AnimUpdate(&w->anim2);
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}
#endif

u8 UpdateDeckMenuKeyboard(DeckMenuWork* w, void* a) {
#ifdef VERSION_EU
    u8 mode = w->keyboardPage;
    s32 bottom = 6;

    if (mode == 2) {
        bottom = 7;
    }
#endif

    w->gfx9 = AnimUpdate(&w->anim4);
    w->gfx = AnimUpdate(&w->anim2);

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
        w->keyCursorSteps = 1;
        w->cursor.parts.x--;

        switch (w->keyboardPage) {
        case 0:
        case 1:
            if (WrapKanaKeyboardCursor(w, 32)) {
                AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
            }

            break;
        case 2:
            if (WrapKeyboardCursor(w, 32)) {
                AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
#ifdef VERSION_EU
                w->onEndKey = 0;
#endif
            }

            break;
#ifdef VERSION_EU
        case 3:
            if (func_eu_0808E94C(w, 32)) {
                AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
                w->onEndKey = 0;
            }

            break;
#endif
        }

        m4aSongNumStart(SONG_SYS_CLICKI04B);
        break;
    case DPAD_RIGHT:
        w->keyCursorSteps = 1;
        w->cursor.parts.x++;

        switch (w->keyboardPage) {
        case 0:
        case 1:
            if (WrapKanaKeyboardCursor(w, 16)) {
                AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
            }

            break;
        case 2:
            if (WrapKeyboardCursor(w, 16)) {
                AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
#ifdef VERSION_EU
                w->onEndKey = 0;
#endif
            }

            break;
#ifdef VERSION_EU
        case 3:
            if (func_eu_0808E94C(w, 16)) {
                AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
                w->onEndKey = 0;
            }

            break;
#endif
        }

        m4aSongNumStart(SONG_SYS_CLICKI04B);
        break;
    case DPAD_UP:
        w->keyCursorSteps = 1;
        w->cursor.parts.y--;

#if defined(VERSION_JP) || defined(VERSION_EU)
        if (w->cursor.parts.y < 0) {
            w->keyCursorSteps = 1;
            w->cursor.parts.y = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)func_jp_0808F638);
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            return 1;
        }
#endif

        switch (w->keyboardPage) {
        case 0:
        case 1:
            if (WrapKanaKeyboardCursor(w, 64)) {
                AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
            }

            break;
        case 2:
            if (WrapKeyboardCursor(w, 64)) {
                AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
#ifdef VERSION_EU
                w->onEndKey = 0;
#endif
            }

            break;
#ifdef VERSION_EU
        case 3:
            if (func_eu_0808E94C(w, 64)) {
                AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
                w->onEndKey = 0;
            }

            break;
#endif
        }

        m4aSongNumStart(SONG_SYS_CLICKI04B);
        break;
    case DPAD_DOWN:
        w->keyCursorSteps = 1;
        w->cursor.parts.y++;

        switch (w->keyboardPage) {
        case 0:
        case 1:
            if (WrapKanaKeyboardCursor(w, 128)) {
                AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
            }

            break;
        case 2:
            if (WrapKeyboardCursor(w, 128)) {
                AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
#ifdef VERSION_EU
                w->onEndKey = 0;
#endif
            }

            break;
#ifdef VERSION_EU
        case 3:
            if (func_eu_0808E94C(w, 128)) {
                AnimStart(&w->anim4, 0, ANIM_FLAG_LOOP);
                w->onEndKey = 0;
            }

            break;
#endif
        }

        m4aSongNumStart(SONG_SYS_CLICKI04B);
        break;
    }

    switch (GetKeysPressed()) {
    case B_BUTTON:
        DeleteLastNameChar(w);
        w->textSlotCount6 = LoadTextSlots(w->nameBuffer, w->textSlots6);
        w->x10 = (GetTextSlotsWidth(w->textSlots6, w->textSlotCount6) << 8) + 0x8300;
        break;
    case A_BUTTON:
#ifdef VERSION_EU
        if (w->cursor.parts.x == 14 &&w->cursor.parts.y == bottom) {
#else
        if (w->cursor.packed == 0x6000E) {
#endif
            SaveDeckNameFromBuffer(w);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseKeyboard);
            m4aSongNumStart(SONG_SYS_KETTEI);
            FadeStartIn(FADE_MODE_BLACK, 16);
        } else {
            if ((u8)AppendKeyboardChar(w)) {
                w->textSlotCount6 = LoadTextSlots(w->nameBuffer, w->textSlots6);
                w->x10 = (GetTextSlotsWidth(w->textSlots6, w->textSlotCount6) << 8) + 0x8300;
            } else {
                w->cursor.parts.x = 14;
#ifdef VERSION_EU
                w->cursor.parts.y = bottom;
#else
                w->cursor.parts.y = 6;
#endif
                AnimStart(&w->anim4, 1, ANIM_FLAG_LOOP);
#ifdef VERSION_EU
                w->onEndKey = 1;
#endif
            }
        }

        break;
    case START_BUTTON:
        w->cursor.parts.x = 14;
#ifdef VERSION_EU
        w->cursor.parts.y = bottom;

        if (gLanguage == LANGUAGE_GERMAN) {
            w->x9 = 0xC800;
        } else if (gLanguage == LANGUAGE_ITALIAN) {
            w->x9 = 0xD100;
        } else {
            w->x9 = 0xD300;
        }

        w->y8 = 0x8C00;
#else
        w->cursor.parts.y = 6;
#endif
        AnimStart(&w->anim4, 1, ANIM_FLAG_LOOP);
        m4aSongNumStart(SONG_SYS_CLICKI04B);
#ifdef VERSION_EU
        w->onEndKey = 1;
#endif
        break;
#if defined(VERSION_JP) || defined(VERSION_EU)
    case R_BUTTON:
#ifdef VERSION_JP
        if (w->keyboardPage <= 1) {
#else
        if (w->keyboardPage <= 2) {
#endif
            w->keyboardPage++;
            func_jp_0808F34C(w);
            m4aSongNumStart(SONG_SYS_CANSEL);
        }

        break;
    case L_BUTTON:
#ifdef VERSION_JP
        if (w->keyboardPage != 0) {
#else
        if (w->keyboardPage > 2) {
#endif
            w->keyboardPage--;
            func_jp_0808F34C(w);
            m4aSongNumStart(SONG_SYS_CANSEL);
        }

        break;
    case SELECT_BUTTON:
        w->keyCursorSteps = 1;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
#ifdef VERSION_EU
        w->x = (gKeyboardPageTabXEu[w->keyboardPage] + 8) << 8;
        w->y = 0x1A00;
#endif
        SetTaskUpdate(a, (TaskUpdateFunc)func_jp_0808F638);
#ifdef VERSION_JP
        return 1;
#else
        break;
#endif
#endif
    }

    if (w->keyCursorSteps != 0) {
#ifdef VERSION_EU
        if (w->cursor.parts.x == 14 &&w->cursor.parts.y == bottom) {
            if (gLanguage == LANGUAGE_GERMAN) {
                ApproachValue(&w->x9, 0xC800, w->keyCursorSteps);
            } else if (gLanguage == LANGUAGE_ITALIAN) {
                ApproachValue(&w->x9, 0xD100, w->keyCursorSteps);
            } else {
                ApproachValue(&w->x9, 0xD300, w->keyCursorSteps);
            }
#else
        if (w->cursor.packed == 0x6000E) {
            ApproachValue(&w->x9, 0xD300, w->keyCursorSteps);
#endif
            ApproachValue(&w->y8, 0x8C00, w->keyCursorSteps);
#ifdef VERSION_EU
        } else if (w->keyboardPage == 2) {
#else
        } else {
#endif
            ApproachValue(&w->x9, gKeyboardRowLayouts[w->cursor.parts.y].positions[w->cursor.parts.x] << 8, w->keyCursorSteps);
            ApproachValue(&w->y8, gKeyboardColumnLayouts[w->cursor.parts.x].positions[w->cursor.parts.y] << 8, w->keyCursorSteps);
#ifdef VERSION_EU
        } else {
            ApproachValue(&w->x9, gKeyboardSymbolRowLayouts[w->cursor.parts.y].positions[w->cursor.parts.x] << 8, w->keyCursorSteps);
            ApproachValue(&w->y8, gKeyboardSymbolColumnLayouts[w->cursor.parts.x].positions[w->cursor.parts.y] << 8, w->keyCursorSteps);
#endif
        }
    }

    w->x = w->x9 + 0x800;
    w->y = w->y8 + 0x800;
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateDeckMenuCloseKeyboard(DeckMenuWork* w, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 16);
    w->view = 0;
    SetDeckMenuFrameCursor(w, 0);
    SetDeckMenuHandAnim(w);
    FreeTextSlots(w->textSlots6, 8);
    ReleaseObjTiles(w->tiles11);
    ReleaseObjTiles(w->tiles13);
    ReleaseObjPalette(w->palette7);
    w->step = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuLoadBgs);
    CreateDeckGridCards(w, 0);

#ifdef VERSION_EU
    {
        u8* p;
        u8 n;

        p = &w->handVisible;
        n = 1;
        *p = n;
        return n;
    }
#else
    return 1;
#endif
}

void BuildCollectionEntries(DeckMenuWork* w) {
    u16 i;
    u16 j;
    u16 n;

    w->entries = EwramAlloc(w->entryCount * sizeof(CardKindEntry));

    for (i = 0, n = 0; i <= 16; i++) {
        if (w->kindEntries[i].count != 0) {
            w->entries[n] = w->kindEntries[i];
            w->entries[n].indices = EwramAlloc(w->kindEntries[i].indexCount * 2);

            for (j = 0; j < w->kindEntries[i].indexCount; j++) {
                w->entries[n].indices[j] = w->kindEntries[i].indices[j];
            }

            n++;
        }
    }

    for (i = 143; i <= 159; i++) {
        if (w->kindEntries[i].count != 0) {
            w->entries[n] = w->kindEntries[i];
            w->entries[n].indices = EwramAlloc(w->kindEntries[i].indexCount * 2);

            for (j = 0; j < w->kindEntries[i].indexCount; j++) {
                w->entries[n].indices[j] = w->kindEntries[i].indices[j];
            }

            n++;
        }
    }

    for (i = 18; i <= 31; i++) {
        if (w->kindEntries[i].count != 0) {
            w->entries[n] = w->kindEntries[i];
            w->entries[n].indices = EwramAlloc(w->kindEntries[i].indexCount * 2);

            for (j = 0; j < w->kindEntries[i].indexCount; j++) {
                w->entries[n].indices[j] = w->kindEntries[i].indices[j];
            }

            n++;
        }
    }

    for (i = 161; i <= 174; i++) {
        if (w->kindEntries[i].count != 0) {
            w->entries[n] = w->kindEntries[i];
            w->entries[n].indices = EwramAlloc(w->kindEntries[i].indexCount * 2);

            for (j = 0; j < w->kindEntries[i].indexCount; j++) {
                w->entries[n].indices[j] = w->kindEntries[i].indices[j];
            }

            n++;
        }
    }

    for (i = 32; i <= 142; i++) {
        if (w->kindEntries[i].count != 0) {
            w->entries[n] = w->kindEntries[i];
            w->entries[n].indices = EwramAlloc(w->kindEntries[i].indexCount * 2);

            for (j = 0; j < w->kindEntries[i].indexCount; j++) {
                w->entries[n].indices[j] = w->kindEntries[i].indices[j];
            }

            n++;
        }
    }
}

const u16* gRikuDeckCards[12] = {
    gRikuDeckCards0,
    gRikuDeckCards1,
    gRikuDeckCards2,
    gRikuDeckCards3,
    gRikuDeckCards4,
    gRikuDeckCards5,
    gRikuDeckCards6,
    gRikuDeckCards7,
    gRikuDeckCards8,
    gRikuDeckCards9,
    gRikuDeckCards10,
    gRikuDeckCards11,
};

const u16* gRikuDeckEnemyCards[12] = {
    &gRikuDeckEnemyCard0,
    &gRikuDeckEnemyCard1,
    &gRikuDeckEnemyCard2,
    &gRikuDeckEnemyCard3,
    &gRikuDeckEnemyCard4,
    &gRikuDeckEnemyCard5,
    &gRikuDeckEnemyCard6,
    &gRikuDeckEnemyCard7,
    &gRikuDeckEnemyCard9,
    &gRikuDeckEnemyCard9,
    gRikuDeckCardCounts,
    gRikuDeckCardCounts,
};

#include "deck_names.inc"
#ifdef VERSION_EU
void* gDeckButtonLabelTiles[5] = { gUnk_090A1FB2, gUnkEu_09189F36, gUnkEu_0918A73A, gUnkEu_0918A48E, gUnkEu_0918A1E2 };
void** gDeckButtonLabelSprites[5] = { gUnk_09EEAFD4, gUnkEu_09F77070, gUnkEu_09F77094, gUnkEu_09F77088, gUnkEu_09F7707C };
void* gDeckCommandMenuTiles[5] = { gUnk_090A261E, gUnkEu_0918B8F2, gUnkEu_0919016A, gUnkEu_0918E942, gUnkEu_0918D11A };

void** gDeckCommandMenuSprites[5] = {
    &gUnk_09EEAFE8,
    &gUnkEu_09F770C0,
    &gUnkEu_09F770D8,
    &gUnkEu_09F770D0,
    &gUnkEu_09F770C8,
};

void* gDeckTitleBannerTiles[5] = { gUnk_090A3E46, gUnkEu_09191992, gUnkEu_0919236A, gUnkEu_09192022, gUnkEu_09191CDA };

void** gDeckTitleBannerSprites[5] = {
    &gUnk_09EEAFF0,
    &gUnkEu_09F770E0,
    &gUnkEu_09F770F8,
    &gUnkEu_09F770F0,
    &gUnkEu_09F770E8,
};

u8* gDeckEquipMarkerTiles[5] = { gUnkEu_094EAD64, gUnkEu_094E90E4, gUnkEu_094EA2E4, gUnkEu_094E9CE4, gUnkEu_094E96E4 };
#endif

TaskDesc gTaskDescDeckmenu2 = {
    "Deckmenu2",
    (TaskInitFunc)Deckmenu2_0,
    (TaskUpdateFunc)Deckmenu2_1,
    (TaskDrawFunc)Deckmenu2_2,
    (TaskDestroyFunc)DeckMenuDestroy,
    sizeof(DeckMenuWork),
};

#ifdef VERSION_EU
void* gDeckKeyboardCursorTiles[5] = { gUnk_090A5F1E, gUnk_090A5F1E, gUnkEu_091965CA, gUnkEu_091959DA, gUnk_090A5F1E };
void** gDeckKeyboardCursorSprites[5] = { gUnk_09EEB08C, gUnk_09EEB08C, gUnkEu_09F7721C, gUnkEu_09F771E4, gUnk_09EEB08C };
void* gDeckKeyboardCursorAnims[5] = { gUnk_09EEB0B8, gUnk_09EEB0B8, gUnkEu_09F77248, gUnkEu_09F77210, gUnk_09EEB0B8 };
#endif

#ifdef VERSION_US
#include "deck_keyboard.inc"
const u8* gDeckKeyboardRows[7] = {
    (const u8*)gKeyboardTextUs_09035742,
    (const u8*)gKeyboardTextUs_09035762,
    (const u8*)gKeyboardTextUs_0903577A,
    (const u8*)gKeyboardTextUs_0903579A,
    (const u8*)gKeyboardTextUs_090357B2,
    (const u8*)gKeyboardTextUs_090357D2,
    (const u8*)gKeyboardTextUs_090357F2,
};
#endif
#ifdef VERSION_JP
#include "deck_keyboard.inc"
const u8* gDeckKeyboardRows[7] = {
    gDeckKeyboardHiraganaRow0,
    gDeckKeyboardHiraganaRow1,
    gDeckKeyboardHiraganaRow2,
    gDeckKeyboardHiraganaRow3,
    gDeckKeyboardHiraganaRow4,
    gDeckKeyboardHiraganaRow5,
    gDeckKeyboardHiraganaRow6,
};

const u8* gDeckKeyboardKatakanaRows[7] = {
    gDeckKeyboardKatakanaRow0,
    gDeckKeyboardKatakanaRow1,
    gDeckKeyboardKatakanaRow2,
    gDeckKeyboardKatakanaRow3,
    gDeckKeyboardKatakanaRow4,
    gDeckKeyboardKatakanaRow5,
    gDeckKeyboardKatakanaRow6,
};

const u8* gDeckKeyboardAlphanumericRows[7] = {
    gDeckKeyboardAlphanumericRow0,
    gDeckKeyboardAlphanumericRow1,
    gDeckKeyboardAlphanumericRow2,
    gDeckKeyboardAlphanumericRow3,
    gDeckKeyboardAlphanumericRow4,
    gDeckKeyboardAlphanumericRow5,
    gDeckKeyboardAlphanumericRow6,
};
#endif
#ifdef VERSION_EU
#include "deck_keyboard.inc"
const u8* gDeckKeyboardLetterRows[8] = {
    gKeyboardTextEu_090CEA56,
    gKeyboardTextEu_090CEA66,
    gKeyboardTextEu_090CEA72,
    gKeyboardTextEu_090CEA82,
    gKeyboardTextEu_090CEA8E,
    gKeyboardTextEu_090CEA9E,
    gKeyboardTextEu_090CEAA9,
    gKeyboardTextEu_090CEAB9,
};

const u8* gDeckKeyboardSymbolRows[7] = {
    gKeyboardTextEu_090CEAC4,
    gKeyboardTextEu_090CEAD4,
    gKeyboardTextEu_090CEADF,
    gKeyboardTextEu_090CEAEF,
    gKeyboardTextEu_090CEAFF,
    gKeyboardTextEu_090CEB05,
    gKeyboardTextEu_090CEB15,
};
#endif

#ifdef VERSION_EU
const s16 gKeyboardKeyX[15] = {
    5, 19, 33, 47, 60, 83, 97, 111, 126, 140, 163, 177, 191, 205, 219,
};

const s16 gKeyboardKeyY[8] = {
    33, 47, 61, 76, 92, 110, 128, 143,
};

static const s16 sKeyboardSymbolKeyX[15] = {
    4, 18, 32, 46, 60, 83, 97, 109, 123, 137, 164, 177, 191, 205, 219,
};

static const s16 sKeyboardSymbolKeyY[7] = {
    40, 56, 70, 86, 102, 118, 134,
};

const KeyboardLineLayout gKeyboardRowLayouts[8] = {
    { gKeyboardKeyX, 15 },
    { gKeyboardKeyX, 15 },
    { gKeyboardKeyX, 15 },
    { gKeyboardKeyX, 15 },
    { gKeyboardKeyX, 15 },
    { gKeyboardKeyX, 15 },
    { gKeyboardKeyX, 15 },
    { gKeyboardKeyX, 15 },
};

const KeyboardLineLayout gKeyboardColumnLayouts[15] = {
    { gKeyboardKeyY, 8 },
    { gKeyboardKeyY, 8 },
    { gKeyboardKeyY, 8 },
    { gKeyboardKeyY, 8 },
    { gKeyboardKeyY, 8 },
    { gKeyboardKeyY, 8 },
    { gKeyboardKeyY, 8 },
    { gKeyboardKeyY, 8 },
    { gKeyboardKeyY, 8 },
    { gKeyboardKeyY, 8 },
    { gKeyboardKeyY, 8 },
    { gKeyboardKeyY, 8 },
    { gKeyboardKeyY, 8 },
    { gKeyboardKeyY, 8 },
    { gKeyboardKeyY, 8 },
};

const KeyboardLineLayout gKeyboardSymbolRowLayouts[8] = {
    { sKeyboardSymbolKeyX, 15 },
    { sKeyboardSymbolKeyX, 15 },
    { sKeyboardSymbolKeyX, 15 },
    { sKeyboardSymbolKeyX, 15 },
    { sKeyboardSymbolKeyX, 15 },
    { sKeyboardSymbolKeyX, 15 },
    { sKeyboardSymbolKeyX, 15 },
    { sKeyboardSymbolKeyX, 15 },
};

const KeyboardLineLayout gKeyboardSymbolColumnLayouts[15] = {
    { sKeyboardSymbolKeyY, 7 },
    { sKeyboardSymbolKeyY, 7 },
    { sKeyboardSymbolKeyY, 7 },
    { sKeyboardSymbolKeyY, 7 },
    { sKeyboardSymbolKeyY, 7 },
    { sKeyboardSymbolKeyY, 7 },
    { sKeyboardSymbolKeyY, 7 },
    { sKeyboardSymbolKeyY, 7 },
    { sKeyboardSymbolKeyY, 7 },
    { sKeyboardSymbolKeyY, 7 },
    { sKeyboardSymbolKeyY, 7 },
    { sKeyboardSymbolKeyY, 7 },
    { sKeyboardSymbolKeyY, 7 },
    { sKeyboardSymbolKeyY, 7 },
    { sKeyboardSymbolKeyY, 7 },
};

const s16 gKeyboardPageTabXEu[2] = { 1, 15 };
#else
const s16 gKeyboardKeyX[54] = {
    3, 16, 30, 45, 58, 83, 97, 110, 124, 138, 162, 177, 190, 205, 219,
    3, 16, 30, 45, 58, 83, 97, 124, 162, 177, 190, 205, 219, 3, 16,
    30, 45, 58, 3, 16, 30, 45, 58, 162, 177, 190, 205, 219, 3, 16,
    30, 45, 58, 83, 97, 110, 124, 138, 208,
};

const s16 gKeyboardKeyY[18] = {
    39, 55, 71, 87, 103, 119, 136, 39, 55, 71, 103, 136, 39, 55, 71,
    87, 103, 119,
};

const KeyboardLineLayout gKeyboardRowLayouts[7] = {
    { gKeyboardKeyX, 15 },
    { gKeyboardKeyX, 15 },
    { gKeyboardKeyX, 15 },
    { gKeyboardKeyX, 15 },
    { gKeyboardKeyX, 15 },
    { gKeyboardKeyX, 15 },
    { gKeyboardKeyX, 15 },
};

const KeyboardLineLayout gKeyboardColumnLayouts[16] = {
    { gKeyboardKeyY, 7 },
    { gKeyboardKeyY, 7 },
    { gKeyboardKeyY, 7 },
    { gKeyboardKeyY, 7 },
    { gKeyboardKeyY, 7 },
    { gKeyboardKeyY, 7 },
    { gKeyboardKeyY, 7 },
    { gKeyboardKeyY, 7 },
    { gKeyboardKeyY, 7 },
    { gKeyboardKeyY, 7 },
    { gKeyboardKeyY, 7 },
    { gKeyboardKeyY, 7 },
    { gKeyboardKeyY, 7 },
    { gKeyboardKeyY, 7 },
    { gKeyboardKeyY, 7 },
    { gKeyboardKeyY, 7 },
};
#endif

#ifdef VERSION_JP
const s16 gKeyboardPageTabXJp[3] = { 1, 15, 29 };
#endif
