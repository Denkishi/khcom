#include "macros.h"
#include "card_localized_data.h"
#include "msg_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
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
#include "card_deckmenu2.h"
#include "ms_charge.h"

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

static void Deckmenu2_0(DeckMenuWork* work, void* a) {
    work->resultOut = a;
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
    ListPoolInit(&work->pool);
    TaskPoolInit(&work->taskpool, 286);
    TaskPoolInit(&work->cardpool, 1);
    work->deckIndex = GetActiveDeckIndex();
    CreateDeckGridCards(work, 0);
    work->tiles = AllocObjTiles(0x120, NULL);
    SetObjTileSource(work->tiles, gUnk_090A4664);
    AnimInit(&work->anim2, gUnk_09EEB03C, gUnk_09EEB008);
    AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim2);
    work->x = sDeckTabPointerX[0] << 8;
    work->y = sDeckTabPointerY[0] << 8;
    work->handFlags = 0;
#ifdef VERSION_EU
    work->tiles4 = LoadObjTiles(gUnk_090A44C4, 32);
#else
    work->tiles4 = LoadObjTiles(gUnk_090A44C4, 32);
#endif
    work->palette = LoadObjPalette(gUnk_09614418, 32);
#ifdef VERSION_EU
    work->tiles5 = LoadObjTiles(gDeckButtonLabelTiles[gLanguage], sDeckButtonLabelTileSizes[gLanguage]);
#else
    work->tiles5 = LoadObjTiles(gUnk_090A1FB2, 0x280);
#endif
#ifdef VERSION_EU
    work->gfx7 = gDeckButtonLabelSprites[gLanguage][0];
    work->gfx8 = gDeckButtonLabelSprites[gLanguage][1];
#else
    work->gfx7 = gUnk_09EEAFD4[0];
    work->gfx8 = gUnk_09EEAFD4[1];
#endif
    work->tiles2 = AllocObjTiles(0x280, NULL);
    SetDeckMenuFrameCursor(work, 0);
    work->palette4 = LoadObjPalette(gUnk_09614438, 32);
    gCardUiSpriteState.tiles = AllocObjTiles(0x100, NULL);
    gCardUiSpriteState.palette = LoadObjPalette(gCard00Palette, 32);
    SetObjTileSource(gCardUiSpriteState.tiles, gUnk_0908C3CE);
    AnimInit(&gCardUiSpriteState.anim, gUnk_09EEA198, gUnk_09EEA180);
    AnimStart(&gCardUiSpriteState.anim, 0, ANIM_FLAG_LOOP);
    gCardUiSpriteState.gfx = AnimUpdate(&gCardUiSpriteState.anim);
    work->tiles10 = NULL;
    work->tiles7 = NULL;
    work->tiles8 = NULL;
    work->tiles9 = NULL;
    work->palette5 = NULL;
    work->palette6 = NULL;
    work->tiles3 = NULL;
    work->palette2 = NULL;
    work->tiles12 = NULL;
    work->tiles6 = NULL;
    work->palette3 = NULL;
    work->cursorCol = 0;
    work->cursorRow = 0;
    work->prevCursor[0] = 0;
    work->prevCursor[1] = 0;
    work->timer = 16;
    work->commandCursor = 0;
    work->cursorCard = NULL;
    work->prevCursorCard = NULL;
    work->mode = 0;
    work->view = 0;
    work->deckAttackCount = CountActiveDeckCardsOfCategory(0);
    work->deckMagicCount = CountActiveDeckCardsOfCategory(1);
    work->deckItemCount = CountActiveDeckCardsOfCategory(2);
    work->deckEnemyCount = CountActiveDeckCardsOfCategory(3);
    work->categoryFilter = 0;
    work->entryCount = 0;
    work->entries = NULL;
    work->popupActive = 0;
    work->exitRequested = 0;
    work->barSlideTimer = 16;
    work->bannerSlideTimer = 16;
    work->x5 = 0x7800;
    work->y5 = -0x800;
    work->x6 = 0xA400;
    work->y6 = 0xA000;
    work->x7 = -0x8000;
    work->holding = 0;
    work->handVisible = 0;
    work->removeLabelX = 95;
    work->removeLabelY = -2;
    work->addLabelX = 135;
    work->addLabelY = -2;
    work->inputDelay = 0;
    work->textSlotCount = 0;
    work->textSlotCount2 = 0;
    work->textSlotCount3 = 0;
    work->textSlotCount4 = 0;
    InitTextSlots(work->textSlots, 8);
    InitTextSlots(work->textSlots2, 8);
    InitTextSlots(work->textSlots3, 8);
    InitTextSlots(work->textSlots4, 30);
    InitTextSlots(work->textSlots5, 90);
    work->step = 0;
    work->result = 0;
}

static u8 Deckmenu2_1(DeckMenuWork* work, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 16);

    if (work->step == 0) {
        RequestDma3Clear(GetBgCharBase(0), 0x2000);
    }

    if (work->step == 1) {
        RequestDma3Clear(GetBgCharBase(0) + 0x2000, 0x2000);
    }

    if (work->step == 2) {
        RequestDma3Clear(GetBgCharBase(1), 0x2000);
    }

    if (work->step == 3) {
        RequestDma3Clear(GetBgCharBase(1) + 0x2000, 0x2000);
    }

    if (work->step == 4) {
        RequestDma3Clear(GetBgCharBase(2), 0x2000);
    }

    if (work->step == 5) {
        RequestDma3Clear(GetBgCharBase(2) + 0x2000, 0x2000);
    }

    if (work->step == 6) {
        RequestDma3Clear(GetBgCharBase(3), 0x2000);
    }

    if (work->step == 7) {
        RequestDma3Clear(GetBgCharBase(3) + 0x2000, 0x2000);
    }

    work->step++;

    if (work->step == 8) {
        work->step = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuLoadBgs);
    }

    return 1;
}

u8 UpdateDeckMenuLoadBgs(DeckMenuWork* work, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 16);

    switch (work->step) {
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
        work->step = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuLoadDeckInfo);
        return 1;
    }

    work->step++;
    return 1;
}

u8 UpdateDeckMenuLoadDeckInfo(DeckMenuWork* work, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 16);

    switch (work->step) {
    case 0:
        LoadBgMap(0, gUnk_09519AB8, 0x180);
        LoadBgMap(1, gUnk_0951A2B8, 0x180);
        LoadBgMap(2, gUnk_0951AAB8, 0x180);
        work->step++;
        break;
    case 1:
        DrawDeckCategoryCount(work->deckAttackCount, 0);
        DrawDeckCategoryCount(work->deckMagicCount, 1);
        DrawDeckCategoryCount(work->deckItemCount, 2);
        DrawDeckCategoryCount(work->deckEnemyCount, 3);
        HighlightDeckTab(work, work->deckIndex);
        work->step++;
        break;
    case 2:
        DrawDeckCardCount(0);
        DrawDeckCardCount(1);
        DrawDeckCardCount(2);
        work->step++;
        break;
    case 3:
        DrawDeckCpCost(0);
        DrawDeckCpCost(1);
        DrawDeckCpCost(2);
        work->step++;
        break;
    case 4:
        DrawDeckEquipMarker(GetActiveDeckIndex());
        DrawCardTotals();
        work->x2 = 0x4800;
        work->y2 = 0x2800;
        work->cursorRow = work->deckIndex;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuSlideIn);
        work->view = 1;
        SetDeckMenuHandAnim(work);
        LoadDeckNameTexts(work);
        work->x = sDeckTabPointerX[work->cursorCol] << 8;
        work->y = sDeckTabPointerY[work->cursorRow] << 8;
        work->tiles6 = LoadObjTiles(gUnk_090A583E, 0x620);
#ifdef VERSION_EU
        work->tiles12 = LoadObjTiles(gDeckTitleBannerTiles[gLanguage], sDeckTitleBannerTileSizes[gLanguage]);
#elif defined(VERSION_US)
        if (gGameState.flags & GAME_FLAG_RIKU) {
            work->tiles12 = LoadObjTiles(gUnk_090A418E, 0x320);
        } else {
            work->tiles12 = LoadObjTiles(gUnk_090A3E46, 0x320);
        }
#else
        work->tiles12 = LoadObjTiles(gUnk_090A418E, 0x320);
#endif
        work->palette3 = LoadObjPalette(gUnk_096144F8, 32);
        work->step = 0;
        work->timer = 16;
        return 1;
    }

    return 1;
}

u8 UpdateDeckMenuSlideIn(DeckMenuWork* work, void* a) {
    work->gfx = AnimUpdate(&work->anim2);
    work->gfx2 = AnimUpdate(&work->anim3);

    if (!FadeIsActive()) {
        switch (work->step) {
        case 0:
            ApproachValue(&work->y5, 0, work->timer);
            ApproachValue(&work->y6, 0x9800, work->timer);
            work->timer--;

            if (work->timer == 0) {
                work->timer = 16;
                work->step++;
            }

            break;
        case 1:
            ApproachValue(&work->x7, 0, work->timer);
            work->timer--;

            if (work->timer == 0) {
                ReleaseObjTiles(work->tiles6);
                ReleaseObjTiles(work->tiles12);
                ReleaseObjPalette(work->palette3);
                work->tiles6 = NULL;
                work->tiles12 = NULL;
                work->palette3 = NULL;
                work->handVisible = 1;
                LoadBgMap(3, gUnk_09512AB8, 0x800);
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckSelect);
            }

            break;
        }
    }

    return 1;
}

u8 UpdateDeckMenuEnterDeckGrid(DeckMenuWork* work, void* a) {
    LoadDeckNameTexts(work);
    ApproachValueHalf(&work->x, gDeckGridColumnX[work->cursorCol] << 8);
    ApproachValueHalf(&work->y, gDeckGridRowY[work->cursorRow] << 8);
    work->timer--;

    if (work->timer == 0) {
        work->view = 0;
        SetDeckMenuHandAnim(work);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckGrid);
    }

    return 1;
}

u8 UpdateDeckMenuDeckGrid(DeckMenuWork* work, void* a) {
    work->gfx = AnimUpdate(&work->anim2);
    work->gfx2 = AnimUpdate(&work->anim3);

    if (FadeIsActive()) {
        TaskPoolUpdate(&work->taskpool);
        return 1;
    }

    if (work->popupActive != 0) {
        ApproachValueHalf(&work->x, gDeckGridColumnX[work->cursorCol] << 8);
        ApproachValueHalf(&work->y, gDeckGridRowY[work->cursorRow] << 8);

        if (work->timer != 0) {
            work->timer--;
        }

        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            work->exitRequested = 1;
            work->result = 7;
        }

        work->inputDelay = 4;
        return 1;
    }

    if (work->inputDelay > 0) {
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);
        work->inputDelay--;
        return 1;
    }

    if (work->exitRequested) {
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        } else {
            work->exitRequested = 0;
        }
    }

    switch (GetKeysRepeat()) {
    case DPAD_UP:
        if (work->cursorRow > 0) {
            work->cursorRow--;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        } else {
            if (!ScrollGridUp(work, 1)) {
                if (!work->holding) {
                    work->cursorCol = work->categoryFilter;
                    work->timer = 1;
                    m4aSongNumStart(SONG_SYS_CLICKI04B);
                    work->prevView = work->view;
                    work->view = 2;
                    AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
                    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckFilter);
                    DrawCpCost(0);
                    return 1;
                }
            } else {
                if (work->holding) {
                    work->heldRow++;

                    if ((u16)work->heldRow <= 3) {
                        work->y3 = gDeckGridRowY[work->heldRow] << 8;
                    } else {
                        work->y3 = -0x10000;
                    }
                }
            }
        }

        break;
    case DPAD_DOWN:
        if (work->cursorRow <= 2) {
            work->cursorRow++;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        } else {
            ScrollGridDown(work);

            if (work->holding) {
                if ((u16)work->heldRow <= 3) {
                    work->y3 = gDeckGridRowY[work->heldRow] << 8;
                } else {
                    work->y3 = -0x10000;
                }
            }
        }

        break;
    case DPAD_LEFT:
        if (work->cursorCol > 0) {
            work->cursorCol--;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        break;
    case DPAD_RIGHT:
        if (work->cursorCol > 1) {
            if (!work->holding) {
                work->cursorCol = 0;
                work->cursorRow = work->deckIndex;
                work->timer = 1;
                work->prevView = work->view;
                work->view = 1;
                SetDeckMenuHandAnim(work);
                m4aSongNumStart(SONG_SYS_CLICK);
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckSelect);
                return 1;
            }
        } else {
            work->cursorCol++;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        break;
    }

    switch (GetKeysPressed()) {
    case B_BUTTON:
        if (!work->holding) {
            work->cursorCol = 0;
            work->cursorRow = work->deckIndex;
            work->timer = 1;
            work->prevView = work->view;
            work->view = 1;
            SetDeckMenuHandAnim(work);
            m4aSongNumStart(SONG_SYS_CLICK);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckSelect);
            return 1;
        } else {
            m4aSongNumStart(SONG_SYS_CLOSE);
            work->holding = 0;
            AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
            return 1;
        }
    case A_BUTTON:
        if (work->categoryFilter != 0) {
            return 1;
        }

        if (!work->holding) {
            m4aSongNumStart(SONG_SYS_KETEI2);
            work->holding = 1;
            work->heldCol = work->cursorCol;
            work->heldRow = work->cursorRow;
            work->x3 = gDeckGridColumnX[work->heldCol] << 8;
            work->y3 = gDeckGridRowY[work->heldRow] << 8;
            AnimStart(&work->anim2, 4, ANIM_FLAG_LOOP);
        } else {
            if (SwapHeldDeckCard(work)) {
                m4aSongNumStart(SONG_SYS_KETEI2);
                work->holding = 0;
                AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        }

        return 1;
    case START_BUTTON:
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CLOSE);
            work->result = 7;
        }

        return 1;
    case L_BUTTON:
        m4aSongNumStart(SONG_SYS_CANSEL);
        work->holding = 0;
        AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenRemoveMode);
        return 1;
    case R_BUTTON:
        FreeCollectionEntries(work);
        m4aSongNumStart(SONG_SYS_CANSEL);
        work->holding = 0;
        AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenAddMode);
        return 1;
    }

    if (GetKeysPressed() & SELECT_BUTTON) {
        work->holding = 0;
        work->cursorRow = 0;
        work->scrollRowEnd = 4;
        ResetGridScroll(work);
        work->x2 = 0x4800;
        work->y2 = 0x2800;
        work->cursorCol = work->categoryFilter;
        work->timer = 1;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
        work->view = 2;
        AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckFilter);
        DrawCpCost(0);
        return 1;
    }

    work->cursorCard = GetCardAtCursor(work);
    ApproachValueHalf(&work->x, gDeckGridColumnX[work->cursorCol] << 8);
    ApproachValueHalf(&work->y, gDeckGridRowY[work->cursorRow] << 8);

    if (work->timer != 0) {
        work->timer--;
    }

    work->prevCursorCard = work->cursorCard;
    work->prevCursor[0] = work->cursorCol;
    work->prevCursor[1] = work->cursorRow;
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuDeckFilter(DeckMenuWork* work, void* a) {
    work->gfx = AnimUpdate(&work->anim2);

    if (work->popupActive != 0) {
        ApproachValueHalf(&work->x, sDeckFilterTabX[work->cursorCol] << 8);
        ApproachValueHalf(&work->y, 0x1E00);
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            work->result = 7;
            work->exitRequested = 1;
        }

        work->inputDelay = 4;
        return 1;
    }

    if (work->exitRequested) {
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        work->exitRequested = 0;
    }

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
        if (work->cursorCol > 0) {
            work->cursorCol--;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICK);
            work->categoryFilter = work->cursorCol;
            DrawDeckFilterTab(work->categoryFilter, work->mode);
            ClearCardGrid(work);
            CreateDeckGridCards(work, work->categoryFilter);
        }

        break;
    case DPAD_RIGHT:
        if (work->cursorCol < 4) {
            work->cursorCol++;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICK);
            work->categoryFilter = work->cursorCol;
            DrawDeckFilterTab(work->categoryFilter, work->mode);
            ClearCardGrid(work);
            CreateDeckGridCards(work, work->categoryFilter);
        }

        break;
    }

    switch (GetKeysPressed()) {
    case B_BUTTON:
    case DPAD_DOWN:
        work->cursorCol = 0;
        work->cursorRow = 0;
        work->timer = 1;
        m4aSongNumStart(SONG_SYS_CLICKI04B);

        if (work->view == 2) {
            work->view = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuEnterDeckGrid);
        }

        if (work->view == 8) {
            work->view = 7;
            ShowDeckCardPreview(work);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuRemoveGrid);
        }

        work->x2 = 0x4800;
        work->y2 = 0x2800;
        work->scrollRowEnd = 4;
        return 1;
    case R_BUTTON:
        FreeCollectionEntries(work);
        work->unk_8CA = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenAddMode);
        m4aSongNumStart(SONG_SYS_CANSEL);
        return 1;
    case L_BUTTON:
        if (work->view == 2) {
            m4aSongNumStart(SONG_SYS_CANSEL);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenRemoveMode);
        }

        return 1;
    case START_BUTTON:
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 16);
            work->result = 7;
        }

        return 1;
    }

    ApproachValueHalf(&work->x, sDeckFilterTabX[work->cursorCol] << 8);
    ApproachValueHalf(&work->y, 0x1E00);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuDeletePrompt(DeckMenuWork* work, void* a) {
    PromptChoiceLayout table = sDeckPromptChoiceLayout;

    work->gfx = AnimUpdate(&work->anim2);
    work->gfx2 = AnimUpdate(&work->anim3);

    if (GetKeysPressed() & DPAD_LEFT) {
        if (work->promptChoice != 0) {
            work->promptChoice--;
        }

        work->timer = 1;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysPressed() & DPAD_RIGHT) {
        if (work->promptChoice == 0) {
            work->promptChoice++;
        }

        work->timer = 1;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysPressed() & A_BUTTON) {
        if (work->promptChoice == 1) {
            work->timer = 1;
            work->view = 11;
            SetDeckMenuHandAnim(work);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteValueSelect);
            TaskPoolUpdate(&work->taskpool);
            TaskPoolUpdate(&work->cardpool);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        work->timer = 1;
        DeleteSelectedValueCard(work);
        DrawCardTotals();
        CountCardsNotInDeckByCategory(3, work->collectionCategoryCounts);
        DrawCollectionCategoryCount(work->collectionCategoryCounts[0], 0);
        DrawCollectionCategoryCount(work->collectionCategoryCounts[1], 1);
        DrawCollectionCategoryCount(work->collectionCategoryCounts[2], 2);
        DrawCollectionCategoryCount(work->collectionCategoryCounts[3], 3);

        if (!(u8)MoveValueCursor(work, 0)) {
            RemoveEmptyCollectionEntry(work, 1);

            if (work->gridEntryCount != 0) {
                SetDeckMenuFrameCursor(work, 0);
                work->cursorCol = work->savedCol;
                work->cursorRow = work->savedRow;

                while (!(u8)IsCardAtCursor(work)) {
                    work->cursorCol--;

                    if (work->cursorCol < 0) {
                        work->cursorRow--;

                        if (work->cursorRow < 0) {
                            ScrollGridUp(work, 0);
                            work->cursorRow = 0;
                        }

                        work->cursorCol = 2;
                    }
                }

                work->x = gCollectionGridColumnX[work->cursorCol] << 8;
                work->y = gCollectionGridRowY[work->cursorRow] << 8;
                ShowCollectionCardPreview(work);
                work->view = 9;
                SetDeckMenuHandAnim(work);
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteGrid);
                TaskPoolUpdate(&work->taskpool);
                TaskPoolUpdate(&work->cardpool);
                return 1;
            } else {
                SetDeckMenuFrameCursor(work, 0);
                work->cursorCol = work->categoryFilter;
                work->timer = 1;
                work->view = 10;
                SetDeckMenuHandAnim(work);
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
                work->gridEntryCount = 0;
                TaskPoolUpdate(&work->taskpool);
                TaskPoolUpdate(&work->cardpool);
                return 1;
            }
        } else {
            DrawSelectedValueCpCost(work);
            work->view = 11;
            SetDeckMenuHandAnim(work);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteValueSelect);
            TaskPoolUpdate(&work->taskpool);
            TaskPoolUpdate(&work->cardpool);
            return 1;
        }
    } else if (GetKeysPressed() & B_BUTTON) {
        work->timer = 1;
        work->view = 11;
        SetDeckMenuHandAnim(work);
        m4aSongNumStart(SONG_SYS_CANSEL);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteValueSelect);
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);
        return 1;
    } else {
        ApproachValueHalf(&work->x, table.x[work->promptChoice] << 8);
        ApproachValueHalf(&work->y, 0x7200);
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);
        return 1;
    }
}

u8 UpdateDeckMenuDeleteValueSelect(DeckMenuWork* work, void* a) {
    s8 n;
    s16 v;

    if (work->popupActive != 0) {
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            work->result = 7;
            work->exitRequested = 1;
        }

        work->inputDelay = 8;
        return 1;
    }

    if (work->exitRequested) {
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        work->exitRequested = 0;
    }

    work->gfx = AnimUpdate(&work->anim2);
    work->gfx2 = AnimUpdate(&work->anim3);

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
    case (DPAD_LEFT | DPAD_UP):
    case (DPAD_LEFT | DPAD_DOWN):
        if (work->cursorCol > 0) {
            work->cursorCol--;
            work->timer = 1;

            if ((u8)MoveValueCursor(work, 32)) {
                m4aSongNumStart(SONG_SYS_CLICK);
            }
        }

        DrawSelectedValueCpCost(work);
        break;
    case DPAD_RIGHT:
    case (DPAD_RIGHT | DPAD_UP):
    case (DPAD_RIGHT | DPAD_DOWN):
        if (work->cursorCol <= 0) {
            work->cursorCol++;
            work->timer = 1;

            if ((u8)MoveValueCursor(work, 16)) {
                m4aSongNumStart(SONG_SYS_CLICK);
            }
        }

        DrawSelectedValueCpCost(work);
        break;
    case DPAD_UP:
        n = work->cursorRow;

        if (work->cursorRow > 0) {
            work->cursorRow = work->cursorRow - 1;
        } else {
            work->cursorRow = 4;
        }

        work->timer = 1;
        MoveValueCursor(work, 64);

        if (n != work->cursorRow) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        DrawSelectedValueCpCost(work);
        break;
    case DPAD_DOWN:
        n = work->cursorRow;

        if (work->cursorRow <= 3) {
            work->cursorRow = work->cursorRow + 1;
        } else {
            work->cursorRow = 0;
        }

        work->timer = 1;
        MoveValueCursor(work, 128);

        if (n != work->cursorRow) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        DrawSelectedValueCpCost(work);
        break;
    }

    switch (GetKeysPressed()) {
    case B_BUTTON:
        SetDeckMenuFrameCursor(work, 0);
        v = work->savedCol;
        work->cursorCol = v;
        v = work->savedRow;
        work->cursorRow = v;
        work->x = gCollectionGridColumnX[work->cursorCol] << 8;
        work->y = gCollectionGridRowY[work->cursorRow] << 8;
        ShowCollectionCardPreview(work);
        work->view = 9;
        m4aSongNumStart(SONG_SYS_CLOSE);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteGrid);
        return 1;
    case A_BUTTON:
        if (work->inputDelay > 0) {
            return 1;
        }

        if (!CheckCardDeletable(work)) {
            return 1;
        }

        TaskCreate(&work->cardpool, &gTaskDescDeckYesNo, &work->popupActive);
        work->promptChoice = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeletePrompt);
        work->timer = 1;
        work->view = 12;
        m4aSongNumStart(SONG_SYS_CLOSE);
        SetDeckMenuHandAnim(work);
        return 1;
    case START_BUTTON:
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CLOSE);
            work->result = 7;
        }

        return 1;
    }

    ApproachValueHalf(&work->x, sValueGridX[work->cursorCol] << 8);
    ApproachValueHalf(&work->y, (sValueGridY[work->cursorRow] - 16) << 8);

    if (work->inputDelay > 0) {
        work->inputDelay--;
    }

    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

void RemoveEmptyCollectionEntry(DeckMenuWork* work, u8 mode) {
    DeckCard2Work* node;
    DeckCard2Work* p;
    CardKindEntry* e;
    s32 i;

    node = ListPoolFirst(&work->pool);
    i = 0;
    e = &work->entries[work->entryIndex];
    EwramFree(work->entries[work->entryIndex].indices);
    work->entries[work->entryIndex].indices = NULL;

    for (i = work->entryIndex; i < work->entryCount - 1; i++) {
        work->entries[i] = work->entries[i + 1];
    }

    work->entryCount -= 1;
    work->gridEntryCount -= 1;

    while (node != NULL) {
        if (node->args.col == work->savedCol && node->args.row == work->savedRow) {
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
    TaskPoolUpdate(&work->taskpool);
    ShowCollectionCardPreview(work);
#ifdef VERSION_EU
    SetGridRowCount(work, work->gridEntryCount);
#else
    SetGridRowCount(work, work->entryCount);
#endif
    UpdateGridScrollBar(work);
}

u8 UpdateDeckMenuAddValueSelect(DeckMenuWork* work, void* a) {
    s8 n;

    if (work->popupActive != 0) {
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            work->result = 7;
            work->exitRequested = 1;
        }

        return 1;
    }

    if (work->exitRequested) {
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        work->exitRequested = 0;
    }

    work->gfx = AnimUpdate(&work->anim2);
    work->gfx2 = AnimUpdate(&work->anim3);

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
    case (DPAD_LEFT | DPAD_UP):
    case (DPAD_LEFT | DPAD_DOWN):
        if (work->cursorCol > 0) {
            work->cursorCol--;
            work->timer = 1;

            if ((u8)MoveValueCursor(work, 32)) {
                m4aSongNumStart(SONG_SYS_CLICK);
            }
        }

        DrawSelectedValueCpCost(work);
        break;
    case DPAD_RIGHT:
    case (DPAD_RIGHT | DPAD_UP):
    case (DPAD_RIGHT | DPAD_DOWN):
        if (work->cursorCol <= 0) {
            work->cursorCol++;
            work->timer = 1;

            if ((u8)MoveValueCursor(work, 16)) {
                m4aSongNumStart(SONG_SYS_CLICK);
            }
        }

        DrawSelectedValueCpCost(work);
        break;
    case DPAD_UP:
        n = work->cursorRow;

        if (work->cursorRow > 0) {
            work->cursorRow = work->cursorRow - 1;
        } else {
            work->cursorRow = 4;
        }

        work->timer = 1;
        MoveValueCursor(work, 64);

        if (n != work->cursorRow) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        DrawSelectedValueCpCost(work);
        break;
    case DPAD_DOWN:
        n = work->cursorRow;

        if (work->cursorRow <= 3) {
            work->cursorRow = work->cursorRow + 1;
        } else {
            work->cursorRow = 0;
        }

        work->timer = 1;
        MoveValueCursor(work, 128);

        if (n != work->cursorRow) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        DrawSelectedValueCpCost(work);
        break;
    }

    switch (GetKeysPressed()) {
    case B_BUTTON:
        SetDeckMenuFrameCursor(work, 0);
        n = work->savedCol;
        work->cursorCol = n;
        n = work->savedRow;
        work->cursorRow = n;
        work->x = gCollectionGridColumnX[work->cursorCol] << 8;
        work->y = gCollectionGridRowY[work->cursorRow] << 8;
        ShowCollectionCardPreview(work);
        DrawCpCost(0);
        work->view = 4;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuAddGrid);
        m4aSongNumStart(SONG_SYS_CLOSE);
        return 1;
    case A_BUTTON:
        if (GetDeckCardCount(work->deckIndex) <= 98) {
            AddSelectedValueCardToDeck(work);
            DrawDeckCardCount(work->deckIndex);
            DrawDeckCpCost(work->deckIndex);
            work->deckAttackCount = CountDeckCardsOfCategory(0, work->deckIndex);
            work->deckMagicCount = CountDeckCardsOfCategory(1, work->deckIndex);
            work->deckItemCount = CountDeckCardsOfCategory(2, work->deckIndex);
            work->deckEnemyCount = CountDeckCardsOfCategory(3, work->deckIndex);
            DrawDeckCategoryCount(work->deckAttackCount, 0);
            DrawDeckCategoryCount(work->deckMagicCount, 1);
            DrawDeckCategoryCount(work->deckItemCount, 2);
            DrawDeckCategoryCount(work->deckEnemyCount, 3);
            DrawCardTotals();
            CountCardsNotInDeckByCategory(work->deckIndex, work->collectionCategoryCounts);
            DrawCollectionCategoryCount(work->collectionCategoryCounts[0], 0);
            DrawCollectionCategoryCount(work->collectionCategoryCounts[1], 1);
            DrawCollectionCategoryCount(work->collectionCategoryCounts[2], 2);
            DrawCollectionCategoryCount(work->collectionCategoryCounts[3], 3);
            work->timer = 1;

            if (!(u8)MoveValueCursor(work, 0)) {
                RemoveEmptyCollectionEntry(work, 0);

                if (work->gridEntryCount != 0) {
                    u8 ready;
                    SetDeckMenuFrameCursor(work, 0);
                    work->cursorCol = work->savedCol;
                    work->cursorRow = work->savedRow;

                    while ((ready = IsCardAtCursor(work)) == 0) {
                        if (--work->cursorCol < 0) {
                            if (--work->cursorRow < 0) {
                                ScrollGridUp(work, 0);
                                work->cursorRow = ready;
                            }

                            work->cursorCol = 2;
                        }
                    }

                    work->x = gCollectionGridColumnX[work->cursorCol] << 8;
                    work->y = gCollectionGridRowY[work->cursorRow] << 8;
                    ShowCollectionCardPreview(work);
                    work->view = 4;
                    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuAddGrid);
                    return 1;
                } else {
                    SetDeckMenuFrameCursor(work, 0);
                    work->cursorCol = work->categoryFilter;
                    work->timer = 1;
                    work->view = 6;
                    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
                    work->gridEntryCount = 0;
                    return 1;
                }
            } else {
                DrawSelectedValueCpCost(work);
            }
        } else {
            m4aSongNumStart(SONG_SYS_BEEP);
            TaskCreate(&work->cardpool, &gTaskDescDeckErrorDeckFull, &work->popupActive);
            return 1;
        }

        break;
    case L_BUTTON:
        FreeCollectionEntries(work);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenRemoveMode);
        m4aSongNumStart(SONG_SYS_CANSEL);
        return 1;
    case START_BUTTON:
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CLOSE);
            work->result = 7;
        }

        return 1;
    }

    ApproachValueHalf(&work->x, sValueGridX[work->cursorCol] << 8);
    ApproachValueHalf(&work->y, sValueGridY[work->cursorRow] << 8);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuCollectionFilter(DeckMenuWork* work, void* a) {
    u16 i;
    u16 n;

    work->gfx = AnimUpdate(&work->anim2);

    if (work->popupActive != 0) {
        ApproachValueHalf(&work->x, sCollectionFilterTabX[work->cursorCol] << 8);
        ApproachValueHalf(&work->y, 0x1E00);
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            work->result = 7;
            work->exitRequested = 1;
        }

        return 1;
    }

    if (work->exitRequested) {
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        work->exitRequested = 0;
    }

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
        if (work->cursorCol > 1) {
            work->cursorCol--;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICK);
            n = work->cursorCol;
            work->categoryFilter = n;
            DrawCollectionFilterTab(work->categoryFilter, work->mode);
            ClearCardGrid(work);

            if (work->view == 6) {
                work->gridEntryCount = CreateCollectionGridCards(work, work->categoryFilter, 0);
            } else {
                work->gridEntryCount = CreateCollectionGridCards(work, work->categoryFilter, 1);
            }
        }

        for (i = 0; i <= 9; i++) {
            DrawValueCount(0, i);
        }

        break;
    case DPAD_RIGHT:
        if (work->cursorCol <= 4) {
            work->cursorCol++;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICK);
            n = work->cursorCol;
            work->categoryFilter = n;
            DrawCollectionFilterTab(work->categoryFilter, work->mode);
            ClearCardGrid(work);

            if (work->view == 6) {
                work->gridEntryCount = CreateCollectionGridCards(work, work->categoryFilter, 0);
            } else {
                work->gridEntryCount = CreateCollectionGridCards(work, work->categoryFilter, 1);
            }
        }

        for (i = 0; i <= 9; i++) {
            DrawValueCount(0, i);
        }

        break;
    case DPAD_DOWN:
        if (work->gridEntryCount != 0) {
            work->cursorCol = 0;
            work->cursorRow = 0;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            ShowCollectionCardPreview(work);

            if (work->view == 6) {
                work->view = 4;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuAddGrid);
            }

            if (work->view == 10) {
                work->view = 9;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteGrid);
            }
        } else {
            m4aSongNumStart(SONG_SYS_BEEP);
        }

        work->x2 = 0xA000;
        work->y2 = 0x2800;
        work->scrollRowEnd = 4;
        return 1;
    case B_BUTTON:
        if (work->gridEntryCount != 0) {
            work->cursorCol = 0;
            work->cursorRow = 0;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            ShowCollectionCardPreview(work);

            if (work->view == 6) {
                work->view = 4;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuAddGrid);
            }

            if (work->view == 10) {
                work->view = 9;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteGrid);
            }
        } else {
            m4aSongNumStart(SONG_SYS_CANSEL);

            if (work->view == 6) {
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseAddMode);
            }

            if (work->view == 10) {
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseDeleteMode);
            }
        }

        work->x2 = 0xA000;
        work->y2 = 0x2800;
        work->scrollRowEnd = 4;
        return 1;
    case L_BUTTON:
        if (work->view == 6) {
            FadeStartIn(FADE_MODE_BLACK, 1);
            FreeCollectionEntries(work);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenRemoveMode);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        break;
    case START_BUTTON:
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CLOSE);
            work->result = 7;
        }

        return 1;
    }

    ApproachValueHalf(&work->x, sCollectionFilterTabX[work->cursorCol] << 8);
    ApproachValueHalf(&work->y, 0x1E00);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuClearPrompt(DeckMenuWork* work, void* a) {
    PromptChoiceLayout tbl;

    tbl = sDeckPromptChoiceLayout;
    work->gfx = AnimUpdate(&work->anim2);
    work->gfx2 = AnimUpdate(&work->anim3);

    if (GetKeysPressed() & DPAD_LEFT) {
        if (work->promptChoice != 0) {
            work->promptChoice--;
        }

        work->timer = 1;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysPressed() & DPAD_RIGHT) {
        if (work->promptChoice == 0) {
            work->promptChoice++;
        }

        work->timer = 1;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysPressed() & A_BUTTON) {
        if (work->promptChoice == 1) {
            work->timer = 1;
            work->view = 3;
            SetDeckMenuHandAnim(work);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCommands);
            TaskPoolUpdate(&work->taskpool);
            TaskPoolUpdate(&work->cardpool);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        m4aSongNumStart(SONG_SYS_KETTEI);
        ClearDeck(work->deckIndex);
        DrawDeckCardCount(work->deckIndex);
        DrawDeckCpCost(work->deckIndex);
        DrawCardTotals();
        work->deckAttackCount = CountDeckCardsOfCategory(0, work->deckIndex);
        work->deckMagicCount = CountDeckCardsOfCategory(1, work->deckIndex);
        work->deckItemCount = CountDeckCardsOfCategory(2, work->deckIndex);
        work->deckEnemyCount = CountDeckCardsOfCategory(3, work->deckIndex);
        DrawDeckCategoryCount(work->deckAttackCount, 0);
        DrawDeckCategoryCount(work->deckMagicCount, 1);
        DrawDeckCategoryCount(work->deckItemCount, 2);
        DrawDeckCategoryCount(work->deckEnemyCount, 3);
        ClearCardGrid(work);
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);
        work->timer = 1;
        work->view = 3;
        SetDeckMenuHandAnim(work);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCommands);
    }

    if (GetKeysPressed() & B_BUTTON) {
        work->timer = 1;
        work->view = 3;
        SetDeckMenuHandAnim(work);
        m4aSongNumStart(SONG_SYS_CANSEL);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCommands);
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);
        return 1;
    }

    ApproachValueHalf(&work->x, tbl.x[work->promptChoice] << 8);
    ApproachValueHalf(&work->y, 0x7200);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuDeckSelect(DeckMenuWork* work, void* a) {
    work->gfx = AnimUpdate(&work->anim2);
    work->gfx2 = AnimUpdate(&work->anim3);

#ifdef VERSION_EU
    if (FadeIsActive()) {
        return 1;
    }
#endif

    if (work->popupActive != 0) {
        ApproachValueHalf(&work->x, sDeckTabPointerX[work->cursorCol] << 8);
        ApproachValueHalf(&work->y, sDeckTabPointerY[work->cursorRow] << 8);
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            work->result = 7;
            work->exitRequested = 1;
        }

        work->inputDelay = 4;
        return 1;
    }

    if (work->inputDelay > 0) {
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);
        work->inputDelay--;
        return 1;
    }

    if (work->exitRequested) {
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        } else {
            work->exitRequested = 0;
        }
    }

    switch (GetKeysRepeat()) {
    case DPAD_UP:
        if (work->cursorRow > 0) {
            work->cursorRow--;
            work->timer = 1;
            work->deckIndex = work->cursorRow;
            ClearCardGrid(work);
            CreateDeckGridCards(work, work->categoryFilter);
            work->deckAttackCount = CountDeckCardsOfCategory(0, work->deckIndex);
            work->deckMagicCount = CountDeckCardsOfCategory(1, work->deckIndex);
            work->deckItemCount = CountDeckCardsOfCategory(2, work->deckIndex);
            work->deckEnemyCount = CountDeckCardsOfCategory(3, work->deckIndex);
            DrawDeckCategoryCount(work->deckAttackCount, 0);
            DrawDeckCategoryCount(work->deckMagicCount, 1);
            DrawDeckCategoryCount(work->deckItemCount, 2);
            DrawDeckCategoryCount(work->deckEnemyCount, 3);
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        break;
    case DPAD_DOWN:
        if (work->cursorRow < 2) {
            work->cursorRow++;
            work->deckIndex = work->cursorRow;
            work->timer = 1;
            ClearCardGrid(work);
            CreateDeckGridCards(work, work->categoryFilter);
            work->deckAttackCount = CountDeckCardsOfCategory(0, work->deckIndex);
            work->deckMagicCount = CountDeckCardsOfCategory(1, work->deckIndex);
            work->deckItemCount = CountDeckCardsOfCategory(2, work->deckIndex);
            work->deckEnemyCount = CountDeckCardsOfCategory(3, work->deckIndex);
            DrawDeckCategoryCount(work->deckAttackCount, 0);
            DrawDeckCategoryCount(work->deckMagicCount, 1);
            DrawDeckCategoryCount(work->deckItemCount, 2);
            DrawDeckCategoryCount(work->deckEnemyCount, 3);
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        break;

    case DPAD_LEFT:
        if (work->cursorRow == 2) {
            work->cursorRow = 3;
        }

        work->cursorCol = 2;
        work->timer = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuEnterDeckGrid);
        m4aSongNumStart(SONG_SYS_CANSEL);
        return 1;
    }

    switch (GetKeysPressed()) {
    case A_BUTTON:
        work->timer = 1;
        work->prevView = work->view;
        m4aSongNumStart(SONG_SYS_CANSEL);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenCommands);
        return 1;
    case SELECT_BUTTON:
#ifndef VERSION_EU
        work->scrollRowEnd = 4;
#endif
        SetActiveDeckIndex(work->deckIndex);
        DrawDeckEquipMarker(work->deckIndex);
        TaskCreate(&work->cardpool, &gTaskDescDeckEquip, &work->popupActive);
        m4aSongNumStart(SONG_SYS_DECKSET);
        break;
    case B_BUTTON:
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuStartSlideOut);
            work->result = 8;
            m4aSongNumStart(SONG_SYS_CLOSE);
        }

        return 1;
    case START_BUTTON:
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CLOSE);
            work->result = 7;
        }

        return 1;
    case L_BUTTON:
        FreeCollectionEntries(work);
        m4aSongNumStart(SONG_SYS_CANSEL);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenRemoveMode);
        return 1;
    case R_BUTTON:
        FreeCollectionEntries(work);
        m4aSongNumStart(SONG_SYS_CANSEL);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenAddMode);
        return 1;
    }

    HighlightDeckTab(work, work->deckIndex);
    ApproachValueHalf(&work->x, sDeckTabPointerX[work->cursorCol] << 8);
    ApproachValueHalf(&work->y, sDeckTabPointerY[work->cursorRow] << 8);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuOpenCommands(DeckMenuWork* work, void* a) {
    u8* p;
    u8 z;

#ifdef VERSION_EU
    work->tiles3 = LoadObjTiles(gDeckCommandMenuTiles[gLanguage], sDeckCommandMenuTileSizes[gLanguage]);
#else
    work->tiles3 = LoadObjTiles(gUnk_090A261E, 0x1800);
#endif
    work->palette2 = LoadObjPalette(gUnk_096144D8, 32);
    SetDeckMenuFrameCursor(work, 1);
    p = &work->view;
    z = 0;
    *p = 3;
    work->commandCursor = z;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCommands);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuCommands(DeckMenuWork* work, void* a) {
    work->gfx = AnimUpdate(&work->anim2);
    work->gfx2 = AnimUpdate(&work->anim3);

    if (work->popupActive != 0) {
        work->view = 1;
        SetDeckMenuHandAnim(work);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseCommands);
    }

    switch (GetKeysRepeat()) {
    case DPAD_UP:
        if (work->commandCursor != 0) {
            work->commandCursor--;
        } else {
            work->commandCursor = 5;
        }

        m4aSongNumStart(SONG_SYS_CLICK);
        work->timer = 1;
        break;
    case DPAD_DOWN:
        if (work->commandCursor < 5) {
            work->commandCursor++;
        } else {
            work->commandCursor = 0;
        }

        work->timer = 1;
        m4aSongNumStart(SONG_SYS_CLICK);
        break;
    }

    switch (GetKeysPressed()) {
    case B_BUTTON:
        work->timer = 1;

        if (work->prevView == 0) {
            work->view = 0;
            SetDeckMenuHandAnim(work);
            SetDeckMenuFrameCursor(work, 0);
            m4aSongNumStart(SONG_SYS_CLOSE);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckGrid);
            ReleaseCommandMenuGfx(work);
        } else {
            work->view = 1;
            SetDeckMenuHandAnim(work);
            m4aSongNumStart(SONG_SYS_CLOSE);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseCommands);
        }

        break;
    case START_BUTTON:
        work->exitRequested = 1;
        work->timer = 1;

        if (work->prevView == 0) {
            work->view = 0;
            SetDeckMenuHandAnim(work);
            SetDeckMenuFrameCursor(work, 0);
            m4aSongNumStart(SONG_SYS_CLOSE);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckGrid);
            ReleaseCommandMenuGfx(work);
        } else {
            m4aSongNumStart(SONG_SYS_CLOSE);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseCommands);
            work->result = 7;
        }

        break;
    case A_BUTTON:
        switch (work->commandCursor) {
        case 0:
            SetActiveDeckIndex(work->deckIndex);
            DrawDeckEquipMarker(work->deckIndex);
            TaskCreate(&work->cardpool, &gTaskDescDeckEquip, &work->popupActive);
            m4aSongNumStart(SONG_SYS_DECKSET);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseCommands);
            return 1;
        case 1:
            m4aSongNumStart(SONG_SYS_KETTEI);
            ClearCardGrid(work);
            work->step = 0;
            ReleaseCommandMenuGfx(work);
#ifdef VERSION_EU
            FadeStartIn(FADE_MODE_BLACK, 16);
#endif
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenKeyboard);
            break;
        case 2:
            m4aSongNumStart(SONG_SYS_KETTEI);
            work->view = 15;
            TaskCreate(&work->cardpool, &gTaskDescDeckClear, &work->popupActive);
            work->promptChoice = 1;
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
        ApproachValueHalf(&work->x, 0x6600);
        break;
    case LANGUAGE_FRENCH:
        ApproachValueHalf(&work->x, 0x6200);
        break;
    case LANGUAGE_GERMAN:
        ApproachValueHalf(&work->x, 0x5E00);
        break;
    case LANGUAGE_ITALIAN:
        ApproachValueHalf(&work->x, 0x6200);
        break;
    case LANGUAGE_SPANISH:
        ApproachValueHalf(&work->x, 0x5E00);
        break;
    default:
        ApproachValueHalf(&work->x, 0x6600);
        break;
    }
#else
    ApproachValueHalf(&work->x, 0x6600);
#endif
    ApproachValueHalf(&work->y, sDeckCommandY[work->commandCursor] << 8);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuCloseCommands(DeckMenuWork* work, void* a) {
    work->gfx = AnimUpdate(&work->anim2);
    work->gfx2 = AnimUpdate(&work->anim3);
    ReleaseCommandMenuGfx(work);
    SetDeckMenuFrameCursor(work, 0);

    switch (work->commandCursor) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        if (work->prevView == 0) {
            work->view = 0;
            SetDeckMenuHandAnim(work);
            work->timer = 4;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckGrid);
        } else {
            work->view = 1;
            work->timer = 4;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckSelect);
        }

        break;
    }

    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuOpenAddMode(DeckMenuWork* work, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 4);

    switch (work->deckIndex) {
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
        work->deckNameX = 16;
        work->deckNameY = 28;
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
        work->deckName2X = 16;
        work->deckName2Y = 28;
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
        work->deckName3X = 16;
        work->deckName3Y = 28;
        break;
    }

    CountCardsNotInDeckByCategory(work->deckIndex, work->collectionCategoryCounts);
    DrawCollectionCategoryCount(work->collectionCategoryCounts[0], 0);
    DrawCollectionCategoryCount(work->collectionCategoryCounts[1], 1);
    DrawCollectionCategoryCount(work->collectionCategoryCounts[2], 2);
    DrawCollectionCategoryCount(work->collectionCategoryCounts[3], 3);
    work->step = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuBuildAddList);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuBuildAddList(DeckMenuWork* work, void* a) {
    u16 i;
    u16 n;
    u16 m;
    CardKindEntry* k;
    u16* count;
    u8* p;
    u8* q;

    FadeStartIn(FADE_MODE_BLACK, 4);

    switch (work->step) {
    case 0:
        q = &work->view;
        k = NULL;
        *q = 4;
        work->descriptionX = 7;
        work->descriptionY = 130;
        ReleaseCommandMenuGfx(work);
        SetDeckMenuFrameCursor(work, 0);
        ClearCardGrid(work);
        LoadBgMap(3, gUnk_095142B8, 0x800);
        count = &work->entryCount;
        *count = n = 0x11E;
        work->kindEntries = EwramAlloc(n * sizeof(CardKindEntry));
        CpuFill32(0, work->kindEntries, *count * sizeof(CardKindEntry));
        work->entries = k;
        break;
    case 1:
        CountCardsNotInDeckByKind(work->kindEntries, work->deckIndex, 1, work->entryCount, work->unk_4FC);
        break;
    case 2:
        work->entryCount = ListCardsNotInDeckByKind(work->kindEntries, work->deckIndex, 1, work->entryCount, work->unk_4FC);
        break;
    case 3:
        if (work->entryCount != 0) {
            BuildCollectionEntries(work);
        }

        break;
    case 4:
        for (i = 0; i < 0x11E; i++) {
            if (work->kindEntries[i].count != 0) {
                EwramFree(work->kindEntries[i].indices);
            }
        }

        EwramFree(work->kindEntries);
        break;
    case 5:
        p = &work->categoryFilter;
        m = 0;
        *p = 5;
        work->gridEntryCount = CreateCollectionGridCards(work, 5, 0);
        SetDeckMenuHandAnim(work);
        work->x = gCollectionGridColumnX[0] << 8;
        work->y = gCollectionGridRowY[0] << 8;
        work->mode = 2;
        work->cursorCol = m;
        work->cursorRow = m;
        ShowCollectionCardPreview(work);
        DrawCpCost(0);

        if (work->gridEntryCount != 0) {
            work->step = 4;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuAddGrid);
        } else {
            work->cursorCol = *p;
            work->timer = 1;
            work->view = 6;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
        }

        break;
    }

    work->step++;
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuAddGrid(DeckMenuWork* work, void* a) {
    u16 i;

#ifdef VERSION_EU
    if (FadeIsActive()) {
        return 1;
    }
#endif

    work->gfx = AnimUpdate(&work->anim2);
    work->gfx2 = AnimUpdate(&work->anim3);

    if (work->popupActive != 0) {
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            work->result = 7;
            work->exitRequested = 1;
        }

        return 1;
    }

    if (work->exitRequested) {
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        } else {
            work->exitRequested = 0;
        }
    }

    if (work->step == 0) {
        switch (GetKeysRepeat()) {
        case DPAD_UP:
            if (work->cursorRow > 0) {
                if (IsCardAt(work, work->cursorCol, work->cursorRow - 1)) {
                    work->cursorRow--;
                    work->timer = 1;
                    m4aSongNumStart(SONG_SYS_CLICKI04B);
                }
            } else {
                if (!ScrollGridUp(work, 1)) {
                    work->cursorCol = work->categoryFilter;
                    work->timer = 1;
                    m4aSongNumStart(SONG_SYS_CLICKI04B);
                    work->view = 6;

                    for (i = 0; i < 10; i++) {
                        DrawValueCount(0, i);
                    }

                    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
                    return 1;
                }
            }

            ShowCollectionCardPreview(work);
            break;
        case DPAD_DOWN:
            if (work->cursorRow <= 2) {
                if (IsCardAt(work, work->cursorCol, work->cursorRow + 1)) {
                    work->cursorRow++;
                    work->timer = 1;
                    m4aSongNumStart(SONG_SYS_CLICKI04B);
                }
            } else {
                if (IsCardAt(work, work->cursorCol, work->cursorRow + 1)) {
                    ScrollGridDown(work);
                }
            }

            ShowCollectionCardPreview(work);
            break;
        case DPAD_LEFT:
            if (work->cursorCol > 0) {
                if (IsCardAt(work, work->cursorCol - 1, work->cursorRow)) {
                    work->cursorCol--;
                    work->timer = 1;
                    m4aSongNumStart(SONG_SYS_CLICKI04B);
                }
            }

            ShowCollectionCardPreview(work);
            break;
        case DPAD_RIGHT:
            if (work->cursorCol > 1) {
                work->timer = 1;
                return 1;
            }

            if (IsCardAt(work, work->cursorCol + 1, work->cursorRow)) {
                work->cursorCol++;
                work->timer = 1;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            }

            ShowCollectionCardPreview(work);
            break;
        }

        switch (GetKeysPressed()) {
        case A_BUTTON:
            if ((u8)IsCardAtCursor(work)) {
                work->savedCol = work->cursorCol;
                work->savedRow = work->cursorRow;
                work->cursorCol = 0;
                work->cursorRow = 0;

                if ((u8)MoveValueCursor(work, 0)) {
                    m4aSongNumStart(SONG_SYS_KETTEI);
                    DrawSelectedValueCpCost(work);
                    SetDeckMenuFrameCursor(work, 1);
                    work->view = 5;
                    work->x = sValueGridX[work->cursorCol] << 8;
                    work->y = sValueGridY[work->cursorRow] << 8;
                    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuAddValueSelect);
                    return 1;
                } else {
                    work->cursorCol = work->savedCol;
                    work->cursorRow = work->savedRow;
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
            FreeCollectionEntries(work);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenRemoveMode);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        case START_BUTTON:
            if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
                FadeStartOut(FADE_MODE_BLACK, 4);
                m4aSongNumStart(SONG_SYS_CLOSE);
                work->result = 7;
            }

            return 1;
        }

        if (GetKeysPressed() & SELECT_BUTTON) {
            work->cursorRow = 0;
            ResetGridScroll(work);
            work->cursorCol = work->categoryFilter;
            work->timer = 1;
            work->x2 = 0xA000;
            work->y2 = 0x2800;
            work->scrollRowEnd = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            work->view = 6;

            for (i = 0; i < 10; i++) {
                DrawValueCount(0, i);
            }

            TaskPoolUpdate(&work->taskpool);
            TaskPoolUpdate(&work->cardpool);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
            return 1;
        }
    } else {
        work->step--;
    }

    ApproachValueHalf(&work->x, gCollectionGridColumnX[work->cursorCol] << 8);
    ApproachValueHalf(&work->y, gCollectionGridRowY[work->cursorRow] << 8);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuCloseAddMode(DeckMenuWork* work, void* a) {
    u8* q;

    FadeStartIn(FADE_MODE_BLACK, 4);
    q = &work->view;
    *q = 4;
    work->removeLabelX = 95;
    ReleaseCardPreview(work);
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
    HighlightDeckTab(work, work->deckIndex);
    LoadBgMap(3, gUnk_09512AB8, 0x800);
    FreeCollectionEntries(work);
    ClearCardGrid(work);
    work->categoryFilter = 0;
    work->cursorCol = 0;
    work->cursorRow = work->deckIndex;
    CreateDeckGridCards(work, work->categoryFilter);
    work->mode = 0;
    *q = 1;
    SetDeckMenuHandAnim(work);
    ApproachValueHalf(&work->x, sDeckTabPointerX[work->cursorCol] << 8);
    ApproachValueHalf(&work->y, sDeckTabPointerY[work->cursorRow] << 8);
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckSelect);
    LoadPalette(gUnk_09614438,
                (void*)(work->palette4->index * 32 +
                        OBJ_PLTT),
                work->palette4->count << 5);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuOpenRemoveMode(DeckMenuWork* work, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 4);

    switch (work->deckIndex) {
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
        work->deckNameX = 102;
        work->deckNameY = 28;
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
        work->deckName2X = 102;
        work->deckName2Y = 28;
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
        work->deckName3X = 102;
        work->deckName3Y = 28;
        break;
    }

    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuBuildRemoveGrid);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuBuildRemoveGrid(DeckMenuWork* work, void* a) {
    work->descriptionX = 94;
    work->descriptionY = 130;
    work->view = 7;
    ReleaseCommandMenuGfx(work);
    SetDeckMenuFrameCursor(work, 0);
    SetDeckMenuHandAnim(work);
#ifdef VERSION_EU
    LoadBgMap(3, &gUnk_095132B8[0x400], 0x800);
#else
    LoadBgMap(3, gUnk_095132B8, 0x800);
#endif
    ClearCardGrid(work);
    work->categoryFilter = 0;
    work->cursorCol = 0;
    work->cursorRow = 0;
    CreateDeckGridCards(work, work->categoryFilter);
    work->x = gDeckGridColumnX[work->cursorCol] << 8;
    work->y = gDeckGridRowY[work->cursorRow] << 8;
    ShowDeckCardPreview(work);
    work->mode = 1;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuRemoveGrid);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuRemoveGrid(DeckMenuWork* work, void* a) {
    u8 v;

    work->gfx = AnimUpdate(&work->anim2);
    work->gfx2 = AnimUpdate(&work->anim3);

#ifdef VERSION_EU
    if (FadeIsActive()) {
        return 1;
    }
#endif

    if (work->popupActive != 0) {
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            work->result = 7;
            work->exitRequested = 1;
        }

        return 1;
    }

    if (work->exitRequested) {
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        work->exitRequested = 0;
    }

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
        if (work->cursorCol > 0) {
            work->cursorCol--;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        ShowDeckCardPreview(work);
        break;
    case DPAD_RIGHT:
        if (work->cursorCol <= 1) {
            work->cursorCol++;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        ShowDeckCardPreview(work);
        break;
    case DPAD_UP:
        if (work->cursorRow > 0) {
            work->cursorRow--;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        } else if (!ScrollGridUp(work, 1)) {
            v = work->categoryFilter;
            work->cursorCol = v;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            work->view = 8;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckFilter);
            DrawCpCost(0);
            return 1;
        }

        ShowDeckCardPreview(work);
        break;
    case DPAD_DOWN:
        if (work->cursorRow <= 2) {
            work->cursorRow++;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        } else {
            ScrollGridDown(work);
        }

        ShowDeckCardPreview(work);
        break;
    }

    switch (GetKeysPressed()) {
    case A_BUTTON:
        RemoveCursorCardFromDeck(work);
        ShowDeckCardPreview(work);
        DrawDeckCardCount(work->deckIndex);
        DrawDeckCpCost(work->deckIndex);
        work->deckAttackCount = CountDeckCardsOfCategory(0, work->deckIndex);
        work->deckMagicCount = CountDeckCardsOfCategory(1, work->deckIndex);
        work->deckItemCount = CountDeckCardsOfCategory(2, work->deckIndex);
        work->deckEnemyCount = CountDeckCardsOfCategory(3, work->deckIndex);
        DrawDeckCategoryCount(work->deckAttackCount, 0);
        DrawDeckCategoryCount(work->deckMagicCount, 1);
        DrawDeckCategoryCount(work->deckItemCount, 2);
        DrawDeckCategoryCount(work->deckEnemyCount, 3);
        DrawCardTotals();
        break;
    case B_BUTTON:
        work->unk_8CA = 0;
        FadeStartIn(FADE_MODE_BLACK, 1);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseRemoveMode);
        m4aSongNumStart(SONG_SYS_CANSEL);
        return 1;
    case R_BUTTON:
        work->unk_8CA = 1;
        FreeCollectionEntries(work);
        FadeStartIn(FADE_MODE_BLACK, 1);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuOpenAddMode);
        m4aSongNumStart(SONG_SYS_CANSEL);
        return 1;
    case START_BUTTON:
        if (!(u8)CheckDeckCpCost(work)) {
            return 1;
        }

        if (!(u8)CheckDeckHasAttackCard(work)) {
            return 1;
        }

        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
        FadeStartOut(FADE_MODE_BLACK, 4);
        m4aSongNumStart(SONG_SYS_CLOSE);
        work->result = 7;
        return 1;
    }

    if (GetKeysPressed() & SELECT_BUTTON) {
        work->cursorRow = 0;
        ResetGridScroll(work);
        v = work->categoryFilter;
        work->cursorCol = v;
        work->timer = 1;
        work->x2 = 0x4800;
        work->y2 = 0x2800;
        work->scrollRowEnd = 4;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
        work->view = 8;
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckFilter);
        DrawCpCost(0);
        return 1;
    }

    ApproachValueHalf(&work->x, gDeckGridColumnX[work->cursorCol] << 8);
    ApproachValueHalf(&work->y, gDeckGridRowY[work->cursorRow] << 8);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuCloseRemoveMode(DeckMenuWork* work, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 4);
    work->removeLabelX = 95;
    ReleaseCardPreview(work);
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
    HighlightDeckTab(work, work->deckIndex);
    LoadBgMap(3, gUnk_09512AB8, 0x800);
    FreeCollectionEntries(work);
    ClearCardGrid(work);
    work->categoryFilter = 0;
    work->cursorCol = 0;
    work->cursorRow = work->deckIndex;
    CreateDeckGridCards(work, work->categoryFilter);
    work->mode = 0;
    work->view = 1;
    SetDeckMenuHandAnim(work);
    ApproachValueHalf(&work->x, sDeckTabPointerX[work->cursorCol] << 8);
    ApproachValueHalf(&work->y, sDeckTabPointerY[work->cursorRow] << 8);
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckSelect);
    LoadPalette(gUnk_09614438,
                (void*)(work->palette4->index * 32 +
                        OBJ_PLTT),
                work->palette4->count << 5);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuOpenDeleteMode(DeckMenuWork* work, void* a) {
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
    CountCardsNotInDeckByCategory(3, work->collectionCategoryCounts);
    DrawCollectionCategoryCount(work->collectionCategoryCounts[0], 0);
    DrawCollectionCategoryCount(work->collectionCategoryCounts[1], 1);
    DrawCollectionCategoryCount(work->collectionCategoryCounts[2], 2);
    DrawCollectionCategoryCount(work->collectionCategoryCounts[3], 3);
    q = &work->view;
    z = 0;
    *q = 9;
    ReleaseCommandMenuGfx(work);
    SetDeckMenuFrameCursor(work, 0);
    ClearCardGrid(work);
    work->step = z;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuBuildDeleteList);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuBuildDeleteList(DeckMenuWork* work, void* a) {
    u16 i;

    FadeStartIn(FADE_MODE_BLACK, 4);

    switch (work->step) {
    case 0:
        work->entryCount = 286;
        work->kindEntries = EwramAlloc(work->entryCount * sizeof(CardKindEntry));
        CpuFill32(0, work->kindEntries, work->entryCount * sizeof(CardKindEntry));
        work->entries = NULL;
        work->descriptionX = 7;
        work->descriptionY = 113;
        break;
    case 1:
        CountCardsNotInDeckByKind(work->kindEntries, work->deckIndex, 0, work->entryCount, work->unk_4FC);
        break;
    case 2:
        work->entryCount = ListCardsNotInDeckByKind(work->kindEntries, work->deckIndex, 0, work->entryCount, work->unk_4FC);
        break;
    case 3:
        if (work->entryCount != 0) {
            BuildCollectionEntries(work);
        }

        break;
    case 4:
        for (i = 0; i < 286; i++) {
            if (work->kindEntries[i].count != 0) {
                EwramFree(work->kindEntries[i].indices);
            }
        }

        EwramFree(work->kindEntries);
        break;
    case 5:
        work->categoryFilter = 5;
        work->gridEntryCount = CreateCollectionGridCards(work, 5, 1);
        SetDeckMenuHandAnim(work);
        work->x = gCollectionGridColumnX[0] << 8;
        work->y = gCollectionGridRowY[0] << 8;
        work->mode = 3;
        work->cursorCol = 0;
        work->cursorRow = 0;
        ShowCollectionCardPreview(work);

        if (work->gridEntryCount != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteGrid);
        } else {
            work->view = 10;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
            work->cursorCol = work->categoryFilter;
            work->timer = 1;
        }

        break;
    }

    work->step++;
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuDeleteGrid(DeckMenuWork* work, void* a) {
    u16 i;

    work->gfx = AnimUpdate(&work->anim2);
    work->gfx2 = AnimUpdate(&work->anim3);

    if (work->popupActive != 0) {
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            work->result = 7;
            work->exitRequested = 1;
        }

        return 1;
    }

    if (work->exitRequested) {
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        } else {
            work->exitRequested = 0;
        }
    }

    switch (GetKeysRepeat()) {
    case DPAD_UP:
        if (work->cursorRow > 0) {
            if (IsCardAt(work, work->cursorCol, work->cursorRow - 1)) {
                work->cursorRow--;
                work->timer = 1;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            }
        } else {
            if (!ScrollGridUp(work, 1)) {
                work->cursorCol = work->categoryFilter;
                work->timer = 1;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
                work->view = 10;

                for (i = 0; i < 10; i++) {
                    DrawValueCount(0, i);
                }

                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
                return 1;
            }
        }

        ShowCollectionCardPreview(work);
        break;
    case DPAD_DOWN:
        if (work->cursorRow <= 2) {
            if (IsCardAt(work, work->cursorCol, work->cursorRow + 1)) {
                work->cursorRow++;
                work->timer = 1;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            }
        } else {
            if (IsCardAt(work, work->cursorCol, work->cursorRow + 1)) {
                ScrollGridDown(work);
            }
        }

        ShowCollectionCardPreview(work);
        break;
    case DPAD_LEFT:
        if (work->cursorCol > 0) {
            if (IsCardAt(work, work->cursorCol - 1, work->cursorRow)) {
                work->cursorCol--;
                work->timer = 1;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            }
        }

        ShowCollectionCardPreview(work);
        break;
    case DPAD_RIGHT:
        if (work->cursorCol > 1) {
            work->timer = 1;
            return 1;
        }

        if (IsCardAt(work, work->cursorCol + 1, work->cursorRow)) {
            work->cursorCol++;
            work->timer = 1;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        ShowCollectionCardPreview(work);
        break;
    }

    switch (GetKeysPressed()) {
    case A_BUTTON:
        if ((u8)IsCardAtCursor(work)) {
            work->savedCol = work->cursorCol;
            work->savedRow = work->cursorRow;
            work->cursorCol = 0;
            work->cursorRow = 0;
            SetDeckMenuFrameCursor(work, 1);

            if ((u8)MoveValueCursor(work, 0)) {
                m4aSongNumStart(SONG_SYS_KETTEI);
                DrawSelectedValueCpCost(work);
                work->view = 11;
                work->x = sValueGridX[work->cursorCol] << 8;
                work->y = (sValueGridY[work->cursorRow] - 16) << 8;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeleteValueSelect);
                return 1;
            } else {
                work->cursorCol = work->savedCol;
                work->cursorRow = work->savedRow;
                SetDeckMenuFrameCursor(work, 0);
                work->view = 9;
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
        if ((u8)CheckDeckCpCost(work) && (u8)CheckDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CLOSE);
            work->result = 7;
        }

        return 1;
    }

    if (GetKeysPressed() & SELECT_BUTTON) {
        ResetGridScroll(work);
        work->cursorCol = work->categoryFilter;
        work->timer = 1;
        work->x2 = 0xA000;
        work->y2 = 0x2800;
        work->scrollRowEnd = 4;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
        work->view = 10;

        for (i = 0; i < 10; i++) {
            DrawValueCount(0, i);
        }

        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCollectionFilter);
        return 1;
    }

    ApproachValueHalf(&work->x, gCollectionGridColumnX[work->cursorCol] << 8);
    ApproachValueHalf(&work->y, gCollectionGridRowY[work->cursorRow] << 8);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuCloseDeleteMode(DeckMenuWork* work, void* a) {
    u8* q;

    FadeStartIn(FADE_MODE_BLACK, 4);
    q = &work->view;
    *q = 9;
    work->removeLabelX = 95;
    ReleaseCardPreview(work);
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
    HighlightDeckTab(work, work->deckIndex);
    LoadBgMap(3, gUnk_09512AB8, 0x800);
    FreeCollectionEntries(work);
    ClearCardGrid(work);
    work->categoryFilter = 0;
    work->cursorCol = 0;
    work->cursorRow = work->deckIndex;
    CreateDeckGridCards(work, work->categoryFilter);
    work->mode = 0;
    *q = 1;
    SetDeckMenuHandAnim(work);
    ApproachValueHalf(&work->x, sDeckTabPointerX[work->cursorCol] << 8);
    ApproachValueHalf(&work->y, sDeckTabPointerY[work->cursorRow] << 8);
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuDeckSelect);
    LoadPalette(gUnk_09614438,
                (void*)(work->palette4->index * 32 +
                        OBJ_PLTT),
                work->palette4->count << 5);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuFadeOut(DeckMenuWork* work) {
    if (!FadeIsActive()) {
        return 0;
    }

    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuStartSlideOut(DeckMenuWork* work, void* a) {
    work->tiles6 = LoadObjTiles(gUnk_090A583E, 0x620);

#ifdef VERSION_EU
    work->tiles12 = LoadObjTiles(gDeckTitleBannerTiles[gLanguage], sDeckTitleBannerTileSizes[gLanguage]);
#elif defined(VERSION_US)
    if (gGameState.flags & GAME_FLAG_RIKU) {
        work->tiles12 = LoadObjTiles(gUnk_090A418E, 0x320);
    } else {
        work->tiles12 = LoadObjTiles(gUnk_090A3E46, 0x320);
    }
#else
    work->tiles12 = LoadObjTiles(gUnk_090A418E, 0x320);
#endif

    work->palette3 = LoadObjPalette(gUnk_096144F8, 32);
#ifdef VERSION_EU
    LoadBgMap(3, gUnk_095132B8, 0x800);
#else
    LoadBgMap(3, gUnk_09516AB8, 0x800);
#endif
    work->x5 = 0x7800;
    work->y5 = 0;
    work->x6 = 0xA400;
    work->y6 = 0x9800;
    work->x7 = 0;
    work->barSlideTimer = 16;
    work->bannerSlideTimer = 16;
    work->handVisible = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuSlideOut);
    return 1;
}

u8 UpdateDeckMenuSlideOut(DeckMenuWork* work, void* a) {
    if ((s8)work->bannerSlideTimer > 0) {
        ApproachValue(&work->x7, -0x8000, (s8)work->bannerSlideTimer);
        work->bannerSlideTimer--;
    } else if ((s8)work->barSlideTimer > 0) {
        ApproachValue(&work->y5, -0x800, (s8)work->barSlideTimer);
        ApproachValue(&work->y6, 0xA000, (s8)work->barSlideTimer);
        work->barSlideTimer--;
    } else {
        FadeStartOut(FADE_MODE_BLACK, 4);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuFadeOut);
    }

    return 1;
}

void DrawCardDescription(DeckMenuWork* work) {
    DrawTextSlotsUnsorted(work->descriptionX, work->descriptionY, work->textSlots5,
                  work->palette, 20, work->textSlotCount5);
}

void DrawDeckNames(DeckMenuWork* work, u8 flag) {
    if (!flag) {
        switch (work->deckIndex) {
        case 0:
            DrawTextSlots(work->deckNameX, work->deckNameY, work->textSlots, work->palette, 20, work->textSlotCount);
            DrawTextSlots(work->deckName2X, work->deckName2Y, work->textSlots2, work->palette4, 20, work->textSlotCount2);
            DrawTextSlots(work->deckName3X, work->deckName3Y, work->textSlots3, work->palette4, 20, work->textSlotCount3);
            break;
        case 1:
            DrawTextSlots(work->deckNameX, work->deckNameY, work->textSlots, work->palette4, 20, work->textSlotCount);
            DrawTextSlots(work->deckName2X, work->deckName2Y, work->textSlots2, work->palette, 20, work->textSlotCount2);
            DrawTextSlots(work->deckName3X, work->deckName3Y, work->textSlots3, work->palette4, 20, work->textSlotCount3);
            break;
        case 2:
            DrawTextSlots(work->deckNameX, work->deckNameY, work->textSlots, work->palette4, 20, work->textSlotCount);
            DrawTextSlots(work->deckName2X, work->deckName2Y, work->textSlots2, work->palette4, 20, work->textSlotCount2);
            DrawTextSlots(work->deckName3X, work->deckName3Y, work->textSlots3, work->palette, 20, work->textSlotCount3);
            break;
        }
    } else {
        switch (work->deckIndex) {
        case 0:
            DrawTextSlots(work->deckNameX, work->deckNameY, work->textSlots, work->palette, 20, work->textSlotCount);
            break;
        case 1:
            DrawTextSlots(work->deckName2X, work->deckName2Y, work->textSlots2, work->palette, 20, work->textSlotCount2);
            break;
        case 2:
            DrawTextSlots(work->deckName3X, work->deckName3Y, work->textSlots3, work->palette, 20, work->textSlotCount3);
            break;
        }
    }
}

static void Deckmenu2_2(DeckMenuWork* work) {
    gCardUiSpriteState.gfx = AnimUpdate(&gCardUiSpriteState.anim);

    if (work->popupActive == 0) {
        if (work->handVisible != 0) {
            DrawSprite((work->x >> 8) - 16, (work->y >> 8) - 30, work->gfx, work->tiles, work->palette, NULL, work->handFlags, 3);
        }
    }

    if (work->view != 13) {
        DrawSprite(work->x2 >> 8, work->y2 >> 8, gUnk_09EEB000, work->tiles4, work->palette, NULL, SPRITE_PRIORITY(2), 10);
    }

    if (work->tiles6 != NULL) {
        DrawSprite(work->x5 >> 8, work->y5 >> 8, gUnk_09EEB080[0], work->tiles6, work->palette3, NULL, SPRITE_PRIORITY(3), 10000);
        DrawSprite(work->x6 >> 8, work->y6 >> 8, gUnk_09EEB080[1], work->tiles6, work->palette3, NULL, SPRITE_PRIORITY(3), 10000);
    }

    if (work->tiles12 != NULL) {
        DrawSprite(work->x7 >> 8, 0,
#ifdef VERSION_EU
                   gDeckTitleBannerSprites[gLanguage][0],
#else
                   gUnk_09EEAFF0,
#endif
                   work->tiles12, work->palette3, NULL, 0, 10);
    }

    switch (work->view) {
    case 0:
        if (work->holding) {
            DrawSprite((work->x3 >> 8) - 16, (work->y3 >> 8) - 20, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);
        }

        DrawSprite((work->x >> 8) - 16, (work->y >> 8) - 20, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);
        DrawDeckNames(work, 0);
        DrawSprite(work->removeLabelX, work->removeLabelY, work->gfx7, work->tiles5, work->palette, NULL, 0, 10);
        DrawSprite(work->addLabelX, work->addLabelY, work->gfx8, work->tiles5, work->palette, NULL, 0, 10);
        break;
    case 3:
#ifdef VERSION_EU
        if (work->tiles3 != NULL) {
            DrawSprite(120, 80, gDeckCommandMenuSprites[gLanguage][0], work->tiles3, work->palette2, NULL, 0, 8);
        }
#else
        DrawSprite(120, 80, gUnk_09EEAFE8, work->tiles3, work->palette2, NULL, 0, 8);
#endif
        DrawDeckNames(work, 0);
        DrawSprite(work->removeLabelX, work->removeLabelY, work->gfx7, work->tiles5, work->palette, NULL, 0, 10);
        DrawSprite(work->addLabelX, work->addLabelY, work->gfx8, work->tiles5, work->palette, NULL, 0, 10);
        break;
    case 2:
        DrawDeckNames(work, 0);
        DrawSprite(work->removeLabelX, work->removeLabelY, work->gfx7, work->tiles5, work->palette, NULL, 0, 10);
        DrawSprite(work->addLabelX, work->addLabelY, work->gfx8, work->tiles5, work->palette, NULL, 0, 10);
        break;
    case 1:
        DrawSprite(work->removeLabelX, work->removeLabelY, work->gfx7, work->tiles5, work->palette, NULL, 0, 10);
        DrawSprite(work->addLabelX, work->addLabelY, work->gfx8, work->tiles5, work->palette, NULL, 0, 10);
        DrawDeckNames(work, 0);
        break;
    case 4:
        DrawDeckNames(work, 1);
        DrawSprite(work->removeLabelX, work->removeLabelY, work->gfx7, work->tiles5, work->palette, NULL, 0, 10);
        DrawSprite((work->x >> 8) - 16, (work->y >> 8) - 20, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);

        if (work->tiles7 != NULL) {
            if (work->popupActive == 0) {
                DrawSprite((work->x >> 8) - 16, (work->y >> 8) - 20, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);
            }

            DrawSprite(24, 82, work->gfx4, work->tiles7, work->palette5, NULL, SPRITE_PRIORITY(1), 100);
            DrawSprite(24, 82, work->gfx5, work->tiles8, work->palette6, NULL, SPRITE_PRIORITY(1), 101);
            DrawTextSlots(10, 116, work->textSlots4, work->palette4, 20, work->textSlotCount4);

            if (work->tiles10 != NULL) {
                work->gfx3 = AnimUpdate(&work->anim);
                DrawSprite(24, 82, work->gfx3, work->tiles10, work->palette5, NULL, 0, 1);
            }
        }

        if (work->popupActive == 0) {
            DrawCardDescription(work);
        }

        break;
    case 7:
        DrawDeckNames(work, 1);
        DrawSprite(work->addLabelX, work->addLabelY, work->gfx8, work->tiles5, work->palette, NULL, 0, 10);
        DrawSprite((work->x >> 8) - 16, (work->y >> 8) - 20, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);

        if (work->tiles7 != NULL) {
            DrawSprite(164, 82, work->gfx4, work->tiles7, work->palette5, NULL, SPRITE_PRIORITY(1), 100);
            DrawSprite(164, 82, work->gfx5, work->tiles8, work->palette6, NULL, SPRITE_PRIORITY(1), 101);

            if (work->tiles10 != NULL) {
                work->gfx3 = AnimUpdate(&work->anim);
                DrawSprite(164, 82, work->gfx3, work->tiles10, work->palette5, NULL, 0, 1);
            }

            if (work->tiles9 != NULL) {
                DrawSprite(164, 82, work->gfx6, work->tiles9, work->palette5, NULL, 0, 19);
            }

            DrawTextSlots(100, 116, work->textSlots4, work->palette4, 20, work->textSlotCount4);

            if (work->popupActive == 0) {
                DrawCardDescription(work);
            }
        }

        break;
    case 5:
        DrawSprite(work->removeLabelX, work->removeLabelY, work->gfx7, work->tiles5, work->palette, NULL, 0, 10);
        DrawSprite((work->x >> 8) - 26, (work->y >> 8) - 13, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);
        DrawDeckNames(work, 1);

        if (work->tiles7 != NULL) {
            DrawSprite(24, 82, work->gfx4, work->tiles7, work->palette5, NULL, SPRITE_PRIORITY(1), 100);
            DrawSprite(24, 82, work->gfx5, work->tiles8, work->palette6, NULL, SPRITE_PRIORITY(1), 101);

            if (work->tiles10 != NULL) {
                work->gfx3 = AnimUpdate(&work->anim);
                DrawSprite(24, 82, work->gfx3, work->tiles10, work->palette5, NULL, 0, 1);
            }

            DrawTextSlots(10, 116, work->textSlots4, work->palette4, 20, work->textSlotCount4);
        }

        if (work->popupActive == 0) {
            DrawCardDescription(work);
        }

        break;
    case 6:
        DrawSprite(work->removeLabelX, work->removeLabelY, work->gfx7, work->tiles5, work->palette, NULL, 0, 10);
        DrawDeckNames(work, 1);
        break;
    case 8:
        DrawSprite(work->addLabelX, work->addLabelY, work->gfx8, work->tiles5, work->palette, NULL, 0, 10);
        DrawDeckNames(work, 1);
        break;
    case 9:
        DrawSprite((work->x >> 8) - 16, (work->y >> 8) - 20, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);

        if (work->tiles7 != NULL) {
            DrawSprite(24, 66, work->gfx4, work->tiles7, work->palette5, NULL, SPRITE_PRIORITY(1), 100);
            DrawSprite(24, 66, work->gfx5, work->tiles8, work->palette6, NULL, SPRITE_PRIORITY(1), 101);

            if (work->tiles10 != NULL) {
                work->gfx3 = AnimUpdate(&work->anim);
                DrawSprite(24, 66, work->gfx3, work->tiles10, work->palette5, NULL, 0, 1);
            }

            DrawTextSlots(10, 100, work->textSlots4, work->palette4, 20, work->textSlotCount4);
        }

        if (work->popupActive == 0) {
            DrawCardDescription(work);
        }

        break;
    case 11:
        DrawSprite((work->x >> 8) - 26, (work->y >> 8) - 13, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);

        if (work->tiles7 != NULL) {
            DrawSprite(24, 66, work->gfx4, work->tiles7, work->palette5, NULL, SPRITE_PRIORITY(1), 100);
            DrawSprite(24, 66, work->gfx5, work->tiles8, work->palette6, NULL, SPRITE_PRIORITY(1), 101);

            if (work->tiles10 != NULL) {
                work->gfx3 = AnimUpdate(&work->anim);
                DrawSprite(24, 66, work->gfx3, work->tiles10, work->palette5, NULL, 0, 1);
            }

            DrawTextSlots(10, 100, work->textSlots4, work->palette4, 20, work->textSlotCount4);
        }

        if (work->popupActive == 0) {
            DrawCardDescription(work);
        }

        break;
    case 13:
        DrawSprite(work->x9 >> 8, work->y8 >> 8, work->gfx9, work->tiles11, work->palette7, NULL, 0, 20);
        DrawSprite(work->x10 >> 8, 18, NULL, work->tiles13, work->palette7, NULL, 0, 21);
        DrawTextSlots(138, 16, work->textSlots6, work->palette, 20, work->textSlotCount6);
        break;
    case 12:
        DrawSprite((work->x >> 8) - 16, (work->y >> 8) - 30, work->gfx, work->tiles, work->palette, NULL, work->handFlags, 0);

        if (work->tiles7 != NULL) {
            DrawSprite(24, 66, work->gfx4, work->tiles7, work->palette5, NULL, SPRITE_PRIORITY(1), 100);
            DrawSprite(24, 66, work->gfx5, work->tiles8, work->palette6, NULL, SPRITE_PRIORITY(1), 101);

            if (work->tiles10 != NULL) {
                work->gfx3 = AnimUpdate(&work->anim);
                DrawSprite(24, 66, work->gfx3, work->tiles10, work->palette5, NULL, 0, 1);
            }

            DrawTextSlots(10, 100, work->textSlots4, work->palette4, 20, work->textSlotCount4);
        }

        if (work->popupActive == 0) {
            DrawCardDescription(work);
        }

        break;
    case 15:
        DrawSprite((work->x >> 8) - 16, (work->y >> 8) - 30, work->gfx, work->tiles, work->palette, NULL, work->handFlags, 0);

        if (work->tiles7 != NULL) {
            DrawSprite(24, 66, work->gfx4, work->tiles7, work->palette5, NULL, SPRITE_PRIORITY(1), 100);
            DrawSprite(24, 66, work->gfx5, work->tiles8, work->palette6, NULL, SPRITE_PRIORITY(1), 101);

            if (work->tiles10 != NULL) {
                work->gfx3 = AnimUpdate(&work->anim);
                DrawSprite(24, 66, work->gfx3, work->tiles10, work->palette5, NULL, 0, 1);
            }
        }

        break;
    }

    TaskPoolDraw(&work->taskpool);
    TaskPoolDraw(&work->cardpool);
}

void DeckMenuDestroy(DeckMenuWork* work) {
    ClearCardGrid(work);
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles4);
    ReleaseObjPalette(work->palette);

    if (work->tiles12 != NULL) {
        ReleaseObjTiles(work->tiles12);
    }

    if (work->tiles6 != NULL) {
        ReleaseObjTiles(work->tiles6);
    }

    if (work->palette3 != NULL) {
        ReleaseObjPalette(work->palette3);
    }

    ReleaseCommandMenuGfx(work);
    FreeTextSlots(work->textSlots, 8);
    FreeTextSlots(work->textSlots2, 8);
    FreeTextSlots(work->textSlots3, 8);
    FreeTextSlots(work->textSlots4, 30);
    FreeTextSlots(work->textSlots5, 90);
    ReleaseObjPalette(work->palette4);
    TaskPoolDestroy(&work->taskpool);
    TaskPoolDestroy(&work->cardpool);
    FreeCollectionEntries(work);
    *work->resultOut = work->result;
    ReleaseObjTiles(work->tiles5);
    ReleaseObjTiles(gCardUiSpriteState.tiles);
    ReleaseObjPalette(gCardUiSpriteState.palette);
}

void CreateDeckGridCards(DeckMenuWork* work, u8 kind) {
    DeckCard2Args args;
    u16* deck;
    u8 i;
    s8 x;
    s8 y;

    deck = (u16*)GetDeck(work->deckIndex);
    x = 0;
    y = 0;

    if (kind == 0) {
        for (i = 0; i < 99; i++) {
            if (deck[i] != 0xFFFF) {
                if (kind == 0) {
                    args.pool = &work->pool;
                    args.cardId = gCardCollection[deck[i]] & 0x8FFF;
                    args.col = x;
                    args.row = y;
                    args.panel = 0;
                    args.slot = &deck[i];
                    TaskCreate(&work->taskpool, &gTaskDescDeckCard2, &args);
                } else if (gCardDefs[gCardCollection[deck[i]] & 0xFFF].category == kind - 1) {
                    args.pool = &work->pool;
                    args.cardId = gCardCollection[deck[i]] & 0x8FFF;
                    args.col = x;
                    args.row = y;
                    args.panel = 0;
                    args.slot = &deck[i];
                    TaskCreate(&work->taskpool, &gTaskDescDeckCard2, &args);
                }
            } else {
                args.pool = &work->pool;
                args.cardId = 0xFFFF;
                args.col = x;
                args.row = y;
                args.panel = 0;
                args.slot = &deck[i];
                TaskCreate(&work->taskpool, &gTaskDescDeckCard2, &args);
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
                args.pool = &work->pool;
                args.cardId = gCardCollection[deck[i]] & 0x8FFF;
                args.col = x;
                args.row = y;
                args.panel = 0;
                args.slot = &deck[i];
                TaskCreate(&work->taskpool, &gTaskDescDeckCard2, &args);
                x++;
            }

            if (x > 2) {
                x = 0;
                y++;
            }
        }
    }

    work->x2 = 0x4800;
    work->y2 = 0x2800;
    work->scrollRowEnd = 4;
    SetGridRowCount(work, 99);
}

s32 CreateCollectionGridCards(DeckMenuWork* work, u8 kind, u8 c) {
    DeckCard2Args args;
    u16 i;
    u16 count;
    s8 x;
    s8 y;

    x = 0;
    y = 0;
    count = 0;

    if (!c) {
        for (i = 0; i < work->entryCount; i++) {
            if (kind == 5) {
                if (work->entries[i].count != 0) {
                    args.pool = &work->pool;
                    args.cardId = GetCardIdForKindEntry(
                        work->entries[i].kind);
                    args.col = x;
                    args.row = y;
                    args.panel = 1;
                    args.slot = NULL;
                    TaskCreate(&work->taskpool, &gTaskDescDeckCard2, &args);
                    x++;
                    count++;
                }
            } else if (work->entries[i].count != 0) {
                args.pool = &work->pool;
                args.cardId = GetCardIdForKindEntry(
                    work->entries[i].kind);

                if (gCardDefs[args.cardId & 0xFFF].category == kind - 1) {
                    args.col = x;
                    args.row = y;
                    args.panel = 1;
                    args.slot = NULL;
                    TaskCreate(&work->taskpool, &gTaskDescDeckCard2, &args);
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
        for (i = 0; i < work->entryCount; i++) {
            if (kind == 5) {
                if (work->entries[i].count != 0) {
                    if ((u16)(work->entries[i].kind - 78) >
                        64) {
                        args.pool = &work->pool;
                        args.cardId = GetCardIdForKindEntry(
                            work->entries[i].kind);
                        args.col = x;
                        args.row = y;
                        args.panel = 1;
                        args.slot = NULL;
                        TaskCreate(&work->taskpool, &gTaskDescDeckCard2, &args);
                        x++;
                        count++;
                    }
                }
            } else if (work->entries[i].count != 0) {
                args.pool = &work->pool;
                args.cardId = GetCardIdForKindEntry(
                    work->entries[i].kind);

                if (gCardDefs[args.cardId & 0xFFF].category == kind - 1) {
                    if ((u16)(work->entries[i].kind - 78) >
                        64) {
                        args.col = x;
                        args.row = y;
                        args.panel = 1;
                        args.slot = NULL;
                        TaskCreate(&work->taskpool, &gTaskDescDeckCard2, &args);
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

    work->x2 = 0xA000;
    work->y2 = 0x2800;
    work->scrollRowEnd = 4;
    SetGridRowCount(work, y * 3 + x);

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

void ClearCardGrid(DeckMenuWork* work) {
    DeckCard2Work* t;

    t = ListPoolFirst(&work->pool);

    while (t != NULL) {
        t->done = 1;
        t = ListPoolNext(&t->node);
    }

    TaskPoolUpdate(&work->taskpool);
}

void SetGridRowCount(DeckMenuWork* work, s16 n) {
    work->rowCount = n / 3;

    if (n % 3 != 0) {
        work->rowCount = n / 3 + 1;
    }
}

void UpdateGridScrollBar(DeckMenuWork* work) {
    s32 v;

    v = 0x5400 / (work->rowCount - 4);
    work->y2 = v * (work->scrollRowEnd - 4) + 0x2800;

    if (work->y2 > 0x7C00) {
        work->y2 = 0x7C00;
    }

    if (work->y2 <= 0x27FF) {
        work->y2 = 0x2800;
    }
}

void ScrollGridDown(DeckMenuWork* work) {
    DeckCard2Work* node;

    node = ListPoolFirst(&work->pool);

    if (work->scrollRowEnd != work->rowCount) {
        while (node != NULL) {
            node->args.row--;

            if (node->args.row < 0) {
                node->y = 0x20000;
                DeckCard2ReleaseGfx(node);
            }

            node = ListPoolNext(&node->node);
        }

        m4aSongNumStart(SONG_SYS_CLICKI04B);
        work->scrollRowEnd++;
        work->y2 += 0x300;

        if (work->y2 > 0x7C00) {
            work->y2 = 0x7C00;
        }

        if (work->holding) {
            work->heldRow--;
        }

        UpdateGridScrollBar(work);
    }
}

u8 ScrollGridUp(DeckMenuWork* work, u8 a) {
    DeckCard2Work* n;
    u8 b;
    u16 t;

    b = a;
    n = ListPoolFirst(&work->pool);

    if (work->scrollRowEnd <= 4) {
        return 0;
    }

    if (n == NULL) {
        work->y2 -= 0x300;

        t = work->scrollRowEnd;

        if ((s16)t > 4) {
            work->scrollRowEnd = t - 1;
        }

        if (work->y2 < 0x2800) {
            work->y2 = 0x2800;
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

        work->scrollRowEnd--;
        work->y2 -= 0x300;

        if (work->y2 < 0x2800) {
            work->y2 = 0x2800;
        }
    }

    UpdateGridScrollBar(work);
    return 1;
}

DeckCard2Work* GetCardAtCursor(DeckMenuWork* work) {
    DeckCard2Work* node;

    node = ListPoolFirst(&work->pool);

    while (node != NULL) {
        if (work->cursorCol == node->args.col &&
            work->cursorRow == node->args.row) {
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

void SetDeckMenuHandAnim(DeckMenuWork* work) {
    u16 t;

    switch (work->view) {
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
        AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
        work->handFlags &= ~SPRITE_FLAG_HFLIP;
        break;
    case 1:
    case 3:
    case 12:
        AnimStart(&work->anim2, 2, ANIM_FLAG_LOOP);
        t = work->handFlags | SPRITE_FLAG_HFLIP;
        work->handFlags = t;
        break;
    }
}

void HighlightDeckTab(DeckMenuWork* work, u8 b) {
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
        work->deckNameX = 100;
        work->deckNameY = 25;
        work->deckName2X = 102;
        work->deckName2Y = 75;
        work->deckName3X = 102;
        work->deckName3Y = 122;
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
        work->deckNameX = 102;
        work->deckNameY = 27;
        work->deckName2X = 100;
        work->deckName2Y = 73;
        work->deckName3X = 102;
        work->deckName3Y = 122;
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
        work->deckNameX = 102;
        work->deckNameY = 27;
        work->deckName2X = 102;
        work->deckName2Y = 75;
        work->deckName3X = 100;
        work->deckName3Y = 121;
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

void LoadDeckNameTexts(DeckMenuWork* work) {
    InitTextSlots(work->textSlots, 8);
    InitTextSlots(work->textSlots2, 8);
    InitTextSlots(work->textSlots3, 8);
    work->textSlotCount = LoadTextSlots(GetDeckName(0), work->textSlots);
    work->textSlotCount2 = LoadTextSlots(GetDeckName(1), work->textSlots2);
    work->textSlotCount3 = LoadTextSlots(GetDeckName(2), work->textSlots3);
}

void LoadCardNameText(DeckMenuWork* work, s32 id) {
    const CardDef* def;

    def = &gCardDefs[id];
#ifdef VERSION_EU
    work->textSlotCount4 = LoadTextSlots(eu_0805E924(def->name), work->textSlots4);
#else
    work->textSlotCount4 = LoadTextSlots(def->name, work->textSlots4);
#endif

    switch (def->category) {
    case 0:
        LoadPalette(gUnk_09614458,
                    (void*)(work->palette4->index * 32 +
                            OBJ_PLTT),
                    work->palette4->count << 5);
        break;
    case 1:
        LoadPalette(gUnk_09614478,
                    (void*)(work->palette4->index * 32 +
                            OBJ_PLTT),
                    work->palette4->count << 5);
        break;
    case 2:
        LoadPalette(gUnk_09614498,
                    (void*)(work->palette4->index * 32 +
                            OBJ_PLTT),
                    work->palette4->count << 5);
        break;
    case 3:
        LoadPalette(gUnk_096144B8,
                    (void*)(work->palette4->index * 32 +
                            OBJ_PLTT),
                    work->palette4->count << 5);
        break;
    }
}

void LoadCardDescriptionText(DeckMenuWork* work, u16 index) {
    const CardDef* d;
    void* s;

    d = &gCardDefs[index];
    s = gCardKindDescriptions[d->kind];
    work->textSlotCount5 = LoadTextSlots(LANGSTR(s), work->textSlots5);
}

s32 ShowCollectionCardPreview(DeckMenuWork* work) {
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
    t = ListPoolFirst(&work->pool);

    while (t != NULL) {
        if (t->args.row == work->cursorRow &&
            t->args.col == work->cursorCol) {
            id = t->args.cardId;
            break;
        }

        t = ListPoolNext(&t->node);
    }

    ReleaseCardPreview(work);

    if (id != 0xFFFF) {
        flag = id & 0x8000;

        if (flag != 0) {
            work->tiles10 = AllocObjTiles(0x280, NULL);
            SetObjTileSource(work->tiles10, gUnk_0908B1B4);
            AnimInit(&work->anim, gUnk_09EEA164, gUnk_09EEA148);
            AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
            work->gfx3 = AnimGetGfx(&work->anim);
        }

        def = &gCardDefs[id & 0xFFF];
        work->tiles7 = LoadObjTiles(gCardBacks[def->category].tiles, 0x300);
        work->tiles8 = LoadObjTiles(def->tiles, 0x200);
        work->palette6 = LoadObjPalette(def->palette, 32);
        work->palette5 = LoadObjPalette(gCard00Palette, 32);
        work->gfx4 = gCardBacks[def->category].gfx;
        work->gfx5 = def->gfx;

        for (i = 0; i < work->entryCount; i++) {
            if ((u16)(id & 0x8000) != 0) {
                if (work->entries[i].kind ==
                    def->kind + 143) {
                    break;
                }
            } else {
                if (work->entries[i].kind ==
                    def->kind) {
                    break;
                }
            }
        }

        work->entryIndex = i;
        dst = gUnk_05000160;
        LoadPalette(&gUnk_09614318[def->category * 16], dst, 32);

        for (j = 0; j <= 9; j++) {
            DrawValueCount(work->entries[i].valueCounts[j], j);
        }

        v = id & 0xFFF;
        LoadCardNameText(work, v);
        LoadCardDescriptionText(work, v);

        if (work->view >= 9 &&work->view <= 12) {
            if (def->kind > 46) {
                LoadBgMap(2, gUnk_09518AB8, 0x800);
                DrawCpCost(GetCardCpCost(id));
                return id;
            }

            LoadBgMap(2, gUnk_095182B8, 0x800);
            DrawCpCost(0);
        } else if (def->kind > 46) {
            switch (work->deckIndex) {
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
            switch (work->deckIndex) {
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

void ReleaseCardPreview(DeckMenuWork* work) {
    if (work->tiles10 != NULL) {
        ReleaseObjTiles(work->tiles10);
        work->tiles10 = NULL;
    }

    if (work->tiles7 != NULL) {
        ReleaseObjTiles(work->tiles7);
        ReleaseObjPalette(work->palette5);
        ReleaseObjTiles(work->tiles8);
        ReleaseObjPalette(work->palette6);

        if (work->tiles9 != NULL) {
            ReleaseObjTiles(work->tiles9);
            work->tiles9 = NULL;
        }

        work->tiles7 = NULL;
        work->palette5 = NULL;
        work->tiles8 = NULL;
        work->palette6 = NULL;
    }
}

void ShowDeckCardPreview(DeckMenuWork* work) {
    DeckCard2Work* node;
    const CardDef* def;
    void* dst;
    u16 id;

    id = 0xFFFF;
    node = ListPoolFirst(&work->pool);

    while (node != NULL) {
        if (node->args.row == work->cursorRow && node->args.col == work->cursorCol) {
            id = node->args.cardId;
            break;
        }

        node = ListPoolNext(&node->node);
    }

    ReleaseCardPreview(work);

    if (id != 0xFFFF) {
        if (id & 0x8000) {
            work->tiles10 = AllocObjTiles(0x280, NULL);
            SetObjTileSource(work->tiles10, gUnk_0908B1B4);
            AnimInit(&work->anim, gUnk_09EEA164, gUnk_09EEA148);
            AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
            work->gfx3 = AnimGetGfx(&work->anim);
        }

        def = &gCardDefs[id & CARD_ID_MASK];
        work->tiles7 = LoadObjTiles(gCardBacks[def->category].tiles, 768);
        work->tiles8 = LoadObjTiles(def->tiles, 512);
        work->palette6 = LoadObjPalette(def->palette, 32);
        work->palette5 = LoadObjPalette(gCard00Palette, 32);
        work->gfx4 = gCardBacks[def->category].gfx;
        work->gfx5 = def->gfx;

        if ((id & CARD_ID_MASK) <= 0x1C1) {
            work->tiles9 = LoadObjTiles(gUnk_0905EAE8, 480);
            work->gfx6 = gUnk_09EE981C[def->value];
        }

        DrawCpCost(GetCardCpCost(id));
        dst = gUnk_05000160;
        LoadPalette(&gUnk_09614118[def->category * 16 + 0x100], dst, 32);
        LoadCardNameText(work, id & CARD_ID_MASK);
        LoadCardDescriptionText(work, id & CARD_ID_MASK);
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

void DrawSelectedValueCpCost(DeckMenuWork* work) {
    u16 t;

    t = GetCardIdForKindEntry(work->entries[work->entryIndex].kind);
    DrawCpCost(GetCardCpCost(t + work->cursorCol * 5 + (u16)work->cursorRow));
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

s32 MoveValueCursor(DeckMenuWork* work, u16 keys) {
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

    k = work->cursorCol * 5 + *(u8*)&work->cursorRow;
    idx = k;
    p = &work->entries[work->entryIndex];
    t884 = *(u16*)&work->cursorCol;
    y0 = work->cursorCol;
    x0 = *(u8*)&work->cursorRow;

    if (p->valueCounts[idx] != 0) {
        return 1;
    }

    switch (keys) {
    case 64:
        do {
            t = *(u16*)&work->cursorRow;
            *(u16*)&work->cursorRow = (s16)t > 0 ? t - 1 : 4;
            idx = work->cursorCol * 5 + *(u8*)&work->cursorRow;

            if (work->cursorCol == y0 && work->cursorRow == x0) {
                return 0;
            }
        } while (p->valueCounts[idx] == 0);

        break;
    case 128:
        do {
            t = *(u16*)&work->cursorRow;
            *(u16*)&work->cursorRow = (s16)t <= 3 ? t + 1 : 0;
            idx = work->cursorCol * 5 + *(u8*)&work->cursorRow;

            if (work->cursorCol == y0 && work->cursorRow == x0) {
                return 0;
            }
        } while (p->valueCounts[idx] == 0);

        break;
    case 32:
        if (p->valueCounts[work->cursorRow] != 0) {
            if ((s16)t884 > 0) {
                *(u16*)&work->cursorCol = t884 - 1;
            }

            break;
        }

        sum = 0;

        for (i = 0; i < 5; i++) {
            sum += p->valueCounts[i];
        }

        if (sum == 0) {
            *(u16*)&work->cursorCol = 1;
            return 0;
        }

        x = (u8*)&work->cursorRow;
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
        if (p->valueCounts[work->cursorRow + 5] != 0) {
            if ((s16)t884 <= 0) {
                *(u16*)&work->cursorCol = t884 + 1;
            }

            break;
        }

        sum = 0;

        for (i = 0; i < 5; i++) {
            sum += p->valueCounts[i + 5];
        }

        if (sum == 0) {
            *(u16*)&work->cursorCol = 0;
            return 0;
        }

        x = (u8*)&work->cursorRow;
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
        *(u16*)&work->cursorRow = k;
        break;
    case 0:
        do {
            t = *(u16*)&work->cursorRow;

            if ((s16)t <= 3) {
                *(u16*)&work->cursorRow = t + 1;
            } else {
                *(u16*)&work->cursorRow = 0;
            }

            if (work->cursorCol == y0 && work->cursorRow == x0) {
                t884 = *(u16*)&work->cursorCol;

                if ((s16)t884 <= 0) {
                    *(u16*)&work->cursorCol = t884 + 1;
                } else {
                    *(u16*)&work->cursorCol = 0;
                }

                *(u16*)&work->cursorRow = 0;

                if (SumValueCounts(p->valueCounts) == 0) {
                    return 0;
                }
            }

            idx = work->cursorCol * 5 + *(u8*)&work->cursorRow;
        } while (p->valueCounts[idx] == 0);

        break;
    }

    return 1;
}

s32 AddSelectedValueCardToDeck(DeckMenuWork* work) {
    u16 mask;
    u16 idx;
    CardKindEntry* e;
    u16 i;
    u16 card;
    u16 v;
    u32 id;
    const CardDef* def;

    mask = 0;
    idx = work->cursorCol * 5 + work->cursorRow;

    switch (work->deckIndex) {
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

    e = &work->entries[work->entryIndex];

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
                    AddCardToDeck(card, work->deckIndex);
                    e->valueCounts[idx]--;
                    DrawValueCount(e->valueCounts[idx], idx);
                    m4aSongNumStart(SONG_SYS_KETTEI);
                    return e->valueCounts[idx];
                }
            } else if (def->value == idx) {
                AddCardToDeck(card, work->deckIndex);
                e->valueCounts[idx]--;
                DrawValueCount(e->valueCounts[idx], idx);
                m4aSongNumStart(SONG_SYS_KETTEI);
                return e->valueCounts[idx];
            }
        }
    }

    m4aSongNumStart(SONG_SYS_BEEP);
}

void FreeCollectionEntries(DeckMenuWork* work) {
    u16 i;

    if (work->entries != NULL) {
        for (i = 0; i < work->entryCount; i++) {
            EwramFree(work->entries[i].indices);
        }

        EwramFree(work->entries);
        work->entries = NULL;
    }
}

void ReleaseCommandMenuGfx(DeckMenuWork* work) {
    if (work->tiles3 != NULL) {
        ReleaseObjTiles(work->tiles3);
        ReleaseObjPalette(work->palette2);
        work->tiles3 = NULL;
        work->palette2 = NULL;
    }
}

void SetDeckMenuFrameCursor(DeckMenuWork* work, u8 kind) {
    switch (kind) {
    case 0:
        SetObjTileSource(work->tiles2, gUnk_090A4A0C);
        AnimInit(&work->anim3, gUnk_09EEB064, gUnk_09EEB050);
        AnimStart(&work->anim3, 0, ANIM_FLAG_LOOP);
        work->gfx2 = AnimGetGfx(&work->anim3);
        break;
    case 1:
        SetObjTileSource(work->tiles2, gUnk_090A51F6);
        AnimInit(&work->anim3, gUnk_09EEB07C, gUnk_09EEB068);
        AnimStart(&work->anim3, 0, ANIM_FLAG_LOOP);
        work->gfx2 = AnimGetGfx(&work->anim3);
        break;
    }
}

void RemoveCursorCardFromDeck(DeckMenuWork* work) {
    DeckCard2Work* n;

    n = ListPoolFirst(&work->pool);

    while (n != NULL) {
        if (n->args.row == work->cursorRow && n->args.col == work->cursorCol) {
            if (n->args.cardId != 0xFFFF) {
                RemoveCardFromDeck(n->args.slot, work->deckIndex);
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

u8 CheckCardDeletable(DeckMenuWork* work) {
    u16 idx;
    CardKindEntry* e;
    u16 i;
    u16 id;
    u16 c;
    const CardDef* def;

    idx = work->cursorCol * 5 + work->cursorRow;
    e = &work->entries[work->entryIndex];

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

            TaskCreate(&work->cardpool, &gTaskDescDeckErrorLastAttackCard, &work->popupActive);
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

            TaskCreate(&work->cardpool, &gTaskDescDeckErrorLastAttackCard, &work->popupActive);
            m4aSongNumStart(SONG_SYS_BEEP);
            return 0;
        }
    }

    return 1;
}

u8 DeleteSelectedValueCard(DeckMenuWork* work) {
    u16 idx;
    CardKindEntry* e;
    u16 i;
    u16 card;
    u16 id;
    const CardDef* def;

    idx = work->cursorCol * 5 + work->cursorRow;
    e = &work->entries[work->entryIndex];

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
                            TaskCreate(&work->cardpool, &gTaskDescDeckErrorLastAttackCard, &work->popupActive);
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
                        TaskCreate(&work->cardpool, &gTaskDescDeckErrorLastAttackCard, &work->popupActive);
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

s32 CheckDeckCpCost(DeckMenuWork* work) {
    if (GetDeckCpCost(GetActiveDeckIndex()) > gGameState.progression.cp) {
        TaskCreate(&work->cardpool, &gTaskDescDeckErrorCp, &work->popupActive);
        m4aSongNumStart(SONG_SYS_BEEP);

        return 0;
    }

    return 1;
}

s32 CheckDeckHasAttackCard(DeckMenuWork* work) {
    if (CountActiveDeckCardsOfCategory(0) == 0) {
        m4aSongNumStart(SONG_SYS_BEEP);
        TaskCreate(&work->cardpool, &gTaskDescDeckErrorNoAttackCard, &work->popupActive);

        return 0;
    }

    return 1;
}

void ResetGridScroll(DeckMenuWork* work) {
    DeckCard2Work* node;
    s16 x;
    s16 y;

    node = ListPoolFirst(&work->pool);
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

    work->y2 = 0x2800;
    work->scrollRowEnd = 4;
}

s32 IsCardAtCursor(DeckMenuWork* work) {
    DeckCard2Work* t;

    t = ListPoolFirst(&work->pool);

    while (t != NULL) {
        if (t->args.col == work->cursorCol) {
            if (t->args.row == work->cursorRow) {
                return 1;
            }
        }

        t = ListPoolNext(&t->node);
    }

    return 0;
}

u8 IsCardAt(DeckMenuWork* work, s16 a, s16 b) {
    DeckCard2Work* node;

    node = ListPoolFirst(&work->pool);

    while (node != NULL) {
        if (node->args.col == a && node->args.row == b) {
            return 1;
        }

        node = ListPoolNext(&node->node);
    }

    return 0;
}

u8 FindCardInDirection(DeckMenuWork* work, s16 x, s16 y, u16 dir) {
    DeckCard2Work* node;

    node = ListPoolFirst(&work->pool);

    while (node != NULL) {
        if (node->args.col == x && node->args.row == y) {
            return 1;
        }

        node = ListPoolNext(&node->node);
    }

    switch (dir) {
    case 0x40:
        return FindCardInDirection(work, x, y - 1, 0x40);
    case 0x80:
        return FindCardInDirection(work, x, y + 1, 0x80);
    case 0x20:
        return FindCardInDirection(work, x - 1, y, 0x20);
    case 0x10:
        return FindCardInDirection(work, x + 1, y, 0x10);
    }

    return 0;
}

void RecreateDeckGridCards(DeckMenuWork* work, u8 kind) {
    DeckCard2Args args;
    u16* deck;
    u8 i;
    s8 x;
    s8 y;

    deck = (u16*)GetDeck(work->deckIndex);
    x = 0;
    y = 4 - work->scrollRowEnd;

    if (kind == 0) {
        for (i = 0; i < 99; i++) {
            if (deck[i] != 0xFFFF) {
                if (kind == 0) {
                    args.pool = &work->pool;
                    args.cardId = gCardCollection[deck[i]] & 0x8FFF;
                    args.col = x;
                    args.row = y;
                    args.panel = 0;
                    args.slot = &deck[i];
                    TaskCreate(&work->taskpool, &gTaskDescDeckCard2, &args);
                } else if (gCardDefs[gCardCollection[deck[i]] & 0xFFF].category == kind - 1) {
                    args.pool = &work->pool;
                    args.cardId = gCardCollection[deck[i]] & 0x8FFF;
                    args.col = x;
                    args.row = y;
                    args.panel = 0;
                    args.slot = &deck[i];
                    TaskCreate(&work->taskpool, &gTaskDescDeckCard2, &args);
                }
            } else {
                args.pool = &work->pool;
                args.cardId = 0xFFFF;
                args.col = x;
                args.row = y;
                args.panel = 0;
                args.slot = &deck[i];
                TaskCreate(&work->taskpool, &gTaskDescDeckCard2, &args);
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
                args.pool = &work->pool;
                args.cardId = gCardCollection[deck[i]] & 0x8FFF;
                args.col = x;
                args.row = y;
                args.panel = 0;
                args.slot = &deck[i];
                TaskCreate(&work->taskpool, &gTaskDescDeckCard2, &args);
                x++;
            }

            if (x > 2) {
                x = 0;
                y++;
            }
        }
    }
}

u8 ToggleDeckSlotGap(DeckMenuWork* work) {
    DeckCard2Work* p;
    DeckCard2Work* q;
    DeckCard2Work* last;
    DeckCard2Work* n;

    p = ListPoolFirst(&work->pool);
    last = ListPoolLast(&work->pool);
    q = NULL;

    while (p != NULL) {
        if (work->cursorCol == p->args.col && work->cursorRow == p->args.row) {
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
            ClearCardGrid(work);
            TaskPoolUpdate(&work->taskpool);
            RecreateDeckGridCards(work, work->categoryFilter);
            work->cursorCol++;

            if (work->cursorCol > 2) {
                work->cursorCol = 0;

                if (work->cursorRow <= 2) {
                    work->cursorRow++;
                } else {
                    ScrollGridDown(work);
                }
            }

            work->timer = 1;
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
        ClearCardGrid(work);
        TaskPoolUpdate(&work->taskpool);
        RecreateDeckGridCards(work, work->categoryFilter);
        return 1;
    }

    return 0;
}

u8 SwapHeldDeckCard(DeckMenuWork* work) {
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

    p = ListPoolFirst(&work->pool);
    q = ListPoolFirst(&work->pool);

    if (work->cursorCol == work->heldCol && work->cursorRow == work->heldRow) {
        return ToggleDeckSlotGap(work);
    }

    while (p != NULL) {
        if (work->cursorCol == p->args.col && work->cursorRow == p->args.row) {
            break;
        }

        p = ListPoolNext(&p->node);
    }

    if (p == NULL) {
        return 0;
    }

    while (q != NULL) {
        if (work->heldCol == q->args.col &&work->heldRow == q->args.row) {
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
        ListPoolRemove(&p->node, &work->pool);
        ListPoolInsertBefore(&p->node, &work->pool, &q->node);

        for (n = ListPoolFirst(&work->pool); n != NULL; n = ListPoolNext(&n->node)) {
            if (n == ListPoolNext(&n->node)) {
                break;
            }
        }
    } else if (ListPoolNext(&p->node) == q) {
        ListPoolRemove(&p->node, &work->pool);
        ListPoolInsertAfter(&p->node, &work->pool, &q->node);

        for (n = ListPoolFirst(&work->pool); n != NULL; n = ListPoolNext(&n->node)) {
            if (n == ListPoolNext(&n->node)) {
                break;
            }
        }
    } else {
        prev = ListPoolRemove(&p->node, &work->pool);
        ListPoolInsertBefore(&p->node, &work->pool, &q->node);
        ListPoolRemove(&q->node, &work->pool);

        if (prev == NULL) {
            ListPoolAppend(&q->node, &work->pool);
        } else {
            ListPoolInsertBefore(&q->node, &work->pool, &prev->node);
        }
    }

    return 1;
}

u8 WrapKanaKeyboardCursor(DeckMenuWork* work, u16 dir) {
    u16 row;
    u16 row2;

    row = work->cursor.parts.y;

    if ((s16)row == 3 && (u16)work->cursor.parts.x > 9) {
        switch (dir) {
        case 0x40:
            work->cursor.parts.y = row - 1;
            break;
        case 0x80:
            work->cursor.parts.y = row + 1;
            break;
        case 0x20:
            work->cursor.parts.x = 9;
            break;
        case 0x10:
            work->cursor.parts.x = 0;
            break;
        }
    }

    if (work->keyboardPage == 0) {
        row2 = work->cursor.parts.y;

        if ((s16)row2 == 5 && (u16)(work->cursor.parts.x - 5) <= 4) {
            switch (dir) {
            case 0x40:
                work->cursor.parts.y = row2 - 1;
                break;
            case 0x80:
                work->cursor.parts.y = row2 + 1;
                break;
            case 0x20:
                work->cursor.parts.x = 4;
                break;
            case 0x10:
                work->cursor.parts.x = 10;
                break;
            }
        }
    }

    if (work->cursor.parts.y > 6) {
        work->cursor.parts.y = 0;
    }

    if (work->cursor.parts.y < 0) {
        work->cursor.parts.y = 6;
    }

    if (work->cursor.parts.x > 14) {
        work->cursor.parts.x = 0;
    }

    if (work->cursor.parts.x < 0) {
        work->cursor.parts.x = 14;
    }

    if (work->cursor.parts.y == 6 && work->cursor.parts.x > 11) {
        if (work->cursor.parts.x == 13 && dir == 0x20) {
            work->cursor.parts.x = 11;
            AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
        } else {
            work->cursor.parts.x = 14;
            AnimStart(&work->anim4, 1, ANIM_FLAG_LOOP);
        }

        return 0;
    }

    return 1;
}

u8 WrapKeyboardCursor(DeckMenuWork* work, u16 keys) {
    if (work->cursor.parts.y == 1 && (u16)work->cursor.parts.x > 10) {
        switch (keys) {
        case 64:
            work->cursor.parts.y--;
            break;
        case 128:
            work->cursor.parts.y++;
            break;
        case 32:
            work->cursor.parts.x = 10;
            break;
        case 16:
            work->cursor.parts.x = 0;
            break;
        }
    }

    if (work->cursor.parts.y == 3 && (u16)work->cursor.parts.x > 10) {
        switch (keys) {
        case 64:
            work->cursor.parts.y--;
            break;
        case 128:
            work->cursor.parts.y++;
            break;
        case 32:
            work->cursor.parts.x = 10;
            break;
        case 16:
            work->cursor.parts.x = 0;
            break;
        }
    }

#if defined(VERSION_JP) || defined(VERSION_EU)
#ifdef VERSION_JP
    if (work->cursor.parts.y == 4 && (u16)work->cursor.parts.x > 9) {
#else
    if (work->cursor.parts.y == 5 && (u16)work->cursor.parts.x > 9) {
#endif
        switch (keys) {
        case 64:
#ifdef VERSION_JP
            work->cursor.parts.y -= 2;
#else
            work->cursor.parts.y--;
#endif
            break;
        case 128:
            work->cursor.parts.y++;
            break;
        case 32:
            work->cursor.parts.x = 9;
            break;
        case 16:
            work->cursor.parts.x = 0;
            break;
        }
    }
#endif

    if (work->cursor.parts.x > 14) {
        work->cursor.parts.x = 0;
    }

    if (work->cursor.parts.x < 0) {
        work->cursor.parts.x = 14;
    }

#ifdef VERSION_EU
    if (work->cursor.parts.y > 7) {
#else
    if (work->cursor.parts.y > 6) {
#endif
        work->cursor.parts.y = 0;
    }

    if (work->cursor.parts.y < 0) {
#ifdef VERSION_EU
        work->cursor.parts.y = 7;
#else
        work->cursor.parts.y = 6;
#endif
    }

#ifndef VERSION_JP
    if (work->cursor.parts.x > gKeyboardRowLayouts[work->cursor.parts.y].count - 1) {
        work->cursor.parts.x = 0;
    }

    if (work->cursor.parts.x < 0) {
        work->cursor.parts.x = gKeyboardRowLayouts[work->cursor.parts.y].count - 1;
    }

    if (work->cursor.parts.y > gKeyboardColumnLayouts[work->cursor.parts.x].count - 1) {
        work->cursor.parts.y = 0;
    }

    if (work->cursor.parts.y < 0) {
        work->cursor.parts.y = gKeyboardColumnLayouts[work->cursor.parts.x].count - 1;
    }
#endif

#ifdef VERSION_EU
    if (work->cursor.parts.y == 7 &&work->cursor.parts.x > 9) {
#else
    if (work->cursor.parts.y == 6 &&work->cursor.parts.x > 9) {
#endif
        if (work->cursor.parts.x == 13 && keys == 32) {
            work->cursor.parts.x = 9;
            AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
#ifdef VERSION_EU
            work->onEndKey = 0;
#endif
        } else {
            work->cursor.parts.x = 14;
            AnimStart(&work->anim4, 1, ANIM_FLAG_LOOP);
#ifdef VERSION_EU
            work->onEndKey = 1;
#endif
        }

        return 0;
    }

    return 1;
}

#ifdef VERSION_EU
u8 func_eu_0808E94C(DeckMenuWork* work, u16 keys) {
    if (work->cursor.parts.y == 1 && (u16)work->cursor.parts.x > 5) {
        switch (keys) {
        case 64:
            work->cursor.parts.y--;
            break;
        case 128:
            work->cursor.parts.y++;
            break;
        case 32:
            work->cursor.parts.x = 5;
            break;
        case 16:
            work->cursor.parts.x = 0;
            break;
        }
    }

    if (work->cursor.parts.y == 4 && (u16)work->cursor.parts.x > 2) {
        switch (keys) {
        case 64:
            work->cursor.parts.y--;
            break;
        case 128:
            work->cursor.parts.y++;
            break;
        case 32:
            work->cursor.parts.x = 2;
            break;
        case 16:
            work->cursor.parts.x = 0;
            break;
        }
    }

    if (work->cursor.parts.x > 14) {
        work->cursor.parts.x = 0;
    }

    if (work->cursor.parts.x < 0) {
        work->cursor.parts.x = 14;
    }

    if (work->cursor.parts.y > 6) {
        work->cursor.parts.y = 0;
    }

    if (work->cursor.parts.y < 0) {
        work->cursor.parts.y = 6;
    }

    if (work->cursor.parts.x > gKeyboardSymbolRowLayouts[work->cursor.parts.y].count - 1) {
        work->cursor.parts.x = 0;
    }

    if (work->cursor.parts.x < 0) {
        work->cursor.parts.x = gKeyboardSymbolRowLayouts[work->cursor.parts.y].count - 1;
    }

    if (work->cursor.parts.y > gKeyboardSymbolColumnLayouts[work->cursor.parts.x].count - 1) {
        work->cursor.parts.y = 0;
    }

    if (work->cursor.parts.y < 0) {
        work->cursor.parts.y = gKeyboardSymbolColumnLayouts[work->cursor.parts.x].count - 1;
    }

    if (work->cursor.parts.y == 6 &&work->cursor.parts.x > 1) {
        if (work->cursor.parts.x == 13 && keys == 32) {
            work->cursor.parts.x = 1;
            AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
            work->onEndKey = 0;
        } else {
            work->cursor.parts.x = 14;
            AnimStart(&work->anim4, 1, ANIM_FLAG_LOOP);
            work->onEndKey = 1;
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

void CopyDeckNameToBuffer(DeckMenuWork* work) {
    u8* s;
    u8* d;
    s32 i;

    s = GetDeckName(work->deckIndex);

    for (i = 0; i <= 19; i++) {
        d = work->nameBuffer;
        d[i] = s[i];
    }

    work->nameBuffer[18] = 0;
    work->nameBuffer[19] = 0;
}

void SaveDeckNameFromBuffer(DeckMenuWork* work) {
    u8* d;
    u8* s;
    s32 i;

    d = GetDeckName(work->deckIndex);

    for (i = 0; i <= 19; i++) {
        s = work->nameBuffer;
        d[i] = s[i];
    }

    d[18] = 0;
    d[19] = 0;
}

void DeleteLastNameChar(DeckMenuWork* work) {
    u8* p;
    s32 t;
    u8 i;

    if (work->textSlotCount6 == 0) {
        m4aSongNumStart(SONG_SYS_BEEP);
        return;
    }

#ifdef VERSION_EU
    for (i = work->textSlotCount6 - 1; i <= 19; i++) {
        p = work->nameBuffer;
        p[i] = 0;
    }
#else
    for (i = work->textSlotCount6 - 1; i <= 8; i++) {
        p = work->nameBuffer;
        t = i * 2;
        p[t] = 0;
        t++;
        p[t] = 0;
    }
#endif

    m4aSongNumStart(SONG_SYS_CLOSE);
}

s32 AppendKeyboardChar(DeckMenuWork* work) {
    const u8* src = NULL;
    u8* dst;
    s32 offset;
    s32 zero;
    s32 offset2;
    u8 value;
    u8* out;

    if (work->textSlotCount6 <= 7) {
        m4aSongNumStart(SONG_SYS_KETTEI);

#ifdef VERSION_EU
        if (work->keyboardPage == 2) {
            src = gDeckKeyboardLetterRows[work->cursor.parts.y];
        } else {
            src = gDeckKeyboardSymbolRows[work->cursor.parts.y];
        }
#else
#ifdef VERSION_JP
        switch (work->keyboardPage) {
        case 0:
            src = gDeckKeyboardRows[work->cursor.parts.y];
            break;
        case 1:
            src = gDeckKeyboardKatakanaRows[work->cursor.parts.y];
            break;
        case 2:
            src = gDeckKeyboardAlphanumericRows[work->cursor.parts.y];
            break;
        }
#else
        src = gDeckKeyboardRows[work->cursor.parts.y];
#endif
#endif
#ifdef VERSION_EU
        offset = work->textSlotCount6;
        dst = work->nameBuffer;
        out = &dst[offset];
        value = src[work->cursor.parts.x];
        zero = 0;
        *out = value;
        offset2 = work->textSlotCount6 + 1;
        dst[offset2] = zero;
#else
        offset = work->textSlotCount6 * 2;
        dst = work->nameBuffer;
        out = &dst[offset];
        value = src[work->cursor.parts.x * 2];
        zero = 0;
        *out = value;
        offset2 = work->textSlotCount6 * 2;
        offset2++;
        dst[offset2] = src[work->cursor.parts.x * 2 + 1];
        offset = (work->textSlotCount6 + 1) * 2;
        dst[offset] = zero;
        offset = (work->textSlotCount6 + 1) * 2;
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
void func_jp_0808F240(DeckMenuWork* work) {
    switch (work->keyboardPage) {
#ifdef VERSION_JP
    case 0:
        if (work->cursor.parts.y == 5 && (u16)(work->cursor.parts.x - 5) <= 4) {
            work->cursor.parts.x = 4;
        }

        break;
    case 1:
        switch (work->cursor.parts.y) {
        case 0:
        case 1:
        case 2:
            break;
        case 3:
            if (work->cursor.parts.x > 9) {
                work->cursor.parts.x = 9;
            }

            break;
        case 4:
        case 5:
        case 6:
            break;
        }

        break;
    case 2:
        switch (work->cursor.parts.y) {
        case 0:
            break;
        case 1:
            if (work->cursor.parts.x > 10) {
                work->cursor.parts.x = 10;
            }

            break;
        case 2:
        case 3:
            break;
        case 4:
            if (work->cursor.parts.x > 9) {
                work->cursor.parts.x = 9;
            }

            break;
        case 5:
            break;
        case 6:
            if (work->cursor.parts.x >= 10 &&work->cursor.parts.x <= 13) {
                work->cursor.parts.x = 9;
            }

            break;
        }

        break;
#else
    case 2:
        switch (work->cursor.parts.y) {
        case 0:
            break;
        case 1:
        case 3:
            if (work->cursor.parts.x > 10) {
                work->cursor.parts.x = 10;
            }

            break;
        case 2:
        case 4:
            break;
        case 5:
            if (work->cursor.parts.x > 9) {
                work->cursor.parts.x = 9;
            }

            break;
        case 6:
            if (work->onEndKey == 1) {
                work->cursor.parts.x = 14;
                work->cursor.parts.y = 7;
            }

            break;
        case 7:
            if (work->cursor.parts.x >= 10 &&work->cursor.parts.x <= 13) {
                work->cursor.parts.x = 9;
            }

            break;
        }

        break;
    case 3:
        switch (work->cursor.parts.y) {
        case 0:
            break;
        case 1:
            if (work->cursor.parts.x > 5) {
                work->cursor.parts.x = 5;
            }

            break;
        case 2:
        case 3:
            break;
        case 4:
            if (work->cursor.parts.x > 2) {
                work->cursor.parts.x = 2;
            }

            break;
        case 5:
            break;
        case 6:
            if (work->onEndKey == 1) {
                work->cursor.parts.y = 6;
                work->cursor.parts.x = 14;
            } else if (work->cursor.parts.x > 1) {
                work->cursor.parts.x = 1;
            }

            break;
        case 7:
            if (work->cursor.parts.x == 14) {
                work->cursor.parts.y = 6;
            } else {
                work->cursor.parts.y = 6;
                work->cursor.parts.x = 0;
            }

            break;
        }

        break;
#endif
    }
}

void func_jp_0808F34C(DeckMenuWork* work) {
    switch (work->keyboardPage) {
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

    func_jp_0808F240(work);
}
#endif

u8 UpdateDeckMenuOpenKeyboard(DeckMenuWork* work, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 16);

#ifdef VERSION_EU
    work->handVisible = 0;
    work->onEndKey = 0;
#endif

    switch (work->step) {
    case 0:
        work->view = 13;
        SetDeckMenuHandAnim(work);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
#ifdef VERSION_EU
        work->tiles11 = AllocObjTiles(0x400, NULL);
#else
        work->tiles11 = AllocObjTiles(0x200, NULL);
#endif
        work->palette7 = LoadObjPalette(gUnk_096145B8, 32);
        work->tiles13 = AllocSpriteFrameTiles(0x80);
#ifdef VERSION_EU
        SetObjTileSource(work->tiles11, gDeckKeyboardCursorTiles[gLanguage]);
        AnimInit(&work->anim4, gDeckKeyboardCursorAnims[gLanguage], gDeckKeyboardCursorSprites[gLanguage]);
#else
        SetObjTileSource(work->tiles11, gUnk_090A5F1E);
        AnimInit(&work->anim4, gUnk_09EEB0B8, gUnk_09EEB08C);
#endif
        AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
        work->gfx9 = AnimGetGfx(&work->anim4);
#ifdef VERSION_EU
        UpdateSpriteFrameTiles(work->tiles13, gDeckKeyboardCursorSprites[gLanguage][10], gDeckKeyboardCursorTiles[gLanguage]);
#else
        UpdateSpriteFrameTiles(work->tiles13, gUnk_09EEB08C[10], gUnk_090A5F1E);
#endif
        FreeTextSlots(work->textSlots, 8);
        FreeTextSlots(work->textSlots2, 8);
        FreeTextSlots(work->textSlots3, 8);
        FreeTextSlots(work->textSlots4, 30);
        FreeTextSlots(work->textSlots5, 90);
        InitTextSlots(work->textSlots6, 8);
        CopyDeckNameToBuffer(work);
        work->textSlotCount6 = LoadTextSlots(work->nameBuffer, work->textSlots6);
        work->x10 = (GetTextSlotsWidth(work->textSlots6, work->textSlotCount6) << 8) + 0x8300;
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
        work->x9 = gKeyboardKeyX[0] << 8;
        work->y8 = gKeyboardKeyY[0] << 8;
        work->keyCursorSteps = 4;
        work->cursor.parts.x = 0;
        work->cursor.parts.y = 0;
#ifdef VERSION_JP
        work->keyboardPage = 0;
#else
        work->keyboardPage = 2;
#endif
        DrawKeyboardDeckNumber(work->deckIndex);
        break;
    }

    work->step++;
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

#if defined(VERSION_JP) || defined(VERSION_EU)
u8 func_jp_0808F638(DeckMenuWork* work, void* a) {
#ifdef VERSION_EU
    u8* mode = &work->keyboardPage;
    work->handVisible = 1;
#endif

    switch (GetKeysRepeat()) {
    case DPAD_RIGHT:
#ifdef VERSION_EU
        work->keyCursorSteps = 1;

        if (*mode <= 2) {
            (*mode)++;
#else
        if (work->keyboardPage <= 1) {
            work->keyboardPage++;
#endif
            func_jp_0808F34C(work);
            m4aSongNumStart(SONG_SYS_CANSEL);
            work->keyCursorSteps = 1;
        }

        break;
    case DPAD_LEFT:
#ifdef VERSION_EU
        work->keyCursorSteps = 1;

        if (*mode > 2) {
            (*mode)--;
#else
        if (work->keyboardPage != 0) {
            work->keyboardPage--;
#endif
            func_jp_0808F34C(work);
            m4aSongNumStart(SONG_SYS_CANSEL);
            work->keyCursorSteps = 1;
        }

        break;
    case SELECT_BUTTON:
    case DPAD_DOWN:
        work->keyCursorSteps = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuKeyboard);
        work->view = 13;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
#ifdef VERSION_EU
        work->handVisible = 0;
#endif
        return 1;
    }

#ifdef VERSION_EU
    if (work->keyCursorSteps != 0) {
        if (work->onEndKey == 1) {
            if (gLanguage == LANGUAGE_GERMAN) {
                work->x9 = 0xC800;
            } else if (gLanguage == LANGUAGE_ITALIAN) {
                work->x9 = 0xD100;
            } else {
                work->x9 = 0xD300;
            }

            work->y8 = 0x8C00;
        } else if (work->keyboardPage == 2) {
            ApproachValue(&work->x9, gKeyboardRowLayouts[work->cursor.parts.y].positions[work->cursor.parts.x] << 8, work->keyCursorSteps);
            ApproachValue(&work->y8, gKeyboardColumnLayouts[work->cursor.parts.x].positions[work->cursor.parts.y] << 8, work->keyCursorSteps);
        } else {
            ApproachValue(&work->x9, gKeyboardSymbolRowLayouts[work->cursor.parts.y].positions[work->cursor.parts.x] << 8, work->keyCursorSteps);
            ApproachValue(&work->y8, gKeyboardSymbolColumnLayouts[work->cursor.parts.x].positions[work->cursor.parts.y] << 8, work->keyCursorSteps);
        }

        work->keyCursorSteps--;
    }

    ApproachValueHalf(&work->x, (gKeyboardPageTabXEu[work->keyboardPage - 2] + 8) << 8);
#else
    ApproachValueHalf(&work->x, (gKeyboardPageTabXJp[work->keyboardPage] + 8) << 8);
#endif
    ApproachValueHalf(&work->y, 0x1A00);
    work->gfx9 = AnimUpdate(&work->anim4);
    work->gfx = AnimUpdate(&work->anim2);
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}
#endif

u8 UpdateDeckMenuKeyboard(DeckMenuWork* work, void* a) {
#ifdef VERSION_EU
    u8 mode = work->keyboardPage;
    s32 bottom = 6;

    if (mode == 2) {
        bottom = 7;
    }
#endif

    work->gfx9 = AnimUpdate(&work->anim4);
    work->gfx = AnimUpdate(&work->anim2);

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
        work->keyCursorSteps = 1;
        work->cursor.parts.x--;

        switch (work->keyboardPage) {
        case 0:
        case 1:
            if (WrapKanaKeyboardCursor(work, 32)) {
                AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
            }

            break;
        case 2:
            if (WrapKeyboardCursor(work, 32)) {
                AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
#ifdef VERSION_EU
                work->onEndKey = 0;
#endif
            }

            break;
#ifdef VERSION_EU
        case 3:
            if (func_eu_0808E94C(work, 32)) {
                AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
                work->onEndKey = 0;
            }

            break;
#endif
        }

        m4aSongNumStart(SONG_SYS_CLICKI04B);
        break;
    case DPAD_RIGHT:
        work->keyCursorSteps = 1;
        work->cursor.parts.x++;

        switch (work->keyboardPage) {
        case 0:
        case 1:
            if (WrapKanaKeyboardCursor(work, 16)) {
                AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
            }

            break;
        case 2:
            if (WrapKeyboardCursor(work, 16)) {
                AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
#ifdef VERSION_EU
                work->onEndKey = 0;
#endif
            }

            break;
#ifdef VERSION_EU
        case 3:
            if (func_eu_0808E94C(work, 16)) {
                AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
                work->onEndKey = 0;
            }

            break;
#endif
        }

        m4aSongNumStart(SONG_SYS_CLICKI04B);
        break;
    case DPAD_UP:
        work->keyCursorSteps = 1;
        work->cursor.parts.y--;

#if defined(VERSION_JP) || defined(VERSION_EU)
        if (work->cursor.parts.y < 0) {
            work->keyCursorSteps = 1;
            work->cursor.parts.y = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)func_jp_0808F638);
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            return 1;
        }
#endif

        switch (work->keyboardPage) {
        case 0:
        case 1:
            if (WrapKanaKeyboardCursor(work, 64)) {
                AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
            }

            break;
        case 2:
            if (WrapKeyboardCursor(work, 64)) {
                AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
#ifdef VERSION_EU
                work->onEndKey = 0;
#endif
            }

            break;
#ifdef VERSION_EU
        case 3:
            if (func_eu_0808E94C(work, 64)) {
                AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
                work->onEndKey = 0;
            }

            break;
#endif
        }

        m4aSongNumStart(SONG_SYS_CLICKI04B);
        break;
    case DPAD_DOWN:
        work->keyCursorSteps = 1;
        work->cursor.parts.y++;

        switch (work->keyboardPage) {
        case 0:
        case 1:
            if (WrapKanaKeyboardCursor(work, 128)) {
                AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
            }

            break;
        case 2:
            if (WrapKeyboardCursor(work, 128)) {
                AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
#ifdef VERSION_EU
                work->onEndKey = 0;
#endif
            }

            break;
#ifdef VERSION_EU
        case 3:
            if (func_eu_0808E94C(work, 128)) {
                AnimStart(&work->anim4, 0, ANIM_FLAG_LOOP);
                work->onEndKey = 0;
            }

            break;
#endif
        }

        m4aSongNumStart(SONG_SYS_CLICKI04B);
        break;
    }

    switch (GetKeysPressed()) {
    case B_BUTTON:
        DeleteLastNameChar(work);
        work->textSlotCount6 = LoadTextSlots(work->nameBuffer, work->textSlots6);
        work->x10 = (GetTextSlotsWidth(work->textSlots6, work->textSlotCount6) << 8) + 0x8300;
        break;
    case A_BUTTON:
#ifdef VERSION_EU
        if (work->cursor.parts.x == 14 &&work->cursor.parts.y == bottom) {
#else
        if (work->cursor.packed == 0x6000E) {
#endif
            SaveDeckNameFromBuffer(work);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuCloseKeyboard);
            m4aSongNumStart(SONG_SYS_KETTEI);
            FadeStartIn(FADE_MODE_BLACK, 16);
        } else {
            if ((u8)AppendKeyboardChar(work)) {
                work->textSlotCount6 = LoadTextSlots(work->nameBuffer, work->textSlots6);
                work->x10 = (GetTextSlotsWidth(work->textSlots6, work->textSlotCount6) << 8) + 0x8300;
            } else {
                work->cursor.parts.x = 14;
#ifdef VERSION_EU
                work->cursor.parts.y = bottom;
#else
                work->cursor.parts.y = 6;
#endif
                AnimStart(&work->anim4, 1, ANIM_FLAG_LOOP);
#ifdef VERSION_EU
                work->onEndKey = 1;
#endif
            }
        }

        break;
    case START_BUTTON:
        work->cursor.parts.x = 14;
#ifdef VERSION_EU
        work->cursor.parts.y = bottom;

        if (gLanguage == LANGUAGE_GERMAN) {
            work->x9 = 0xC800;
        } else if (gLanguage == LANGUAGE_ITALIAN) {
            work->x9 = 0xD100;
        } else {
            work->x9 = 0xD300;
        }

        work->y8 = 0x8C00;
#else
        work->cursor.parts.y = 6;
#endif
        AnimStart(&work->anim4, 1, ANIM_FLAG_LOOP);
        m4aSongNumStart(SONG_SYS_CLICKI04B);
#ifdef VERSION_EU
        work->onEndKey = 1;
#endif
        break;
#if defined(VERSION_JP) || defined(VERSION_EU)
    case R_BUTTON:
#ifdef VERSION_JP
        if (work->keyboardPage <= 1) {
#else
        if (work->keyboardPage <= 2) {
#endif
            work->keyboardPage++;
            func_jp_0808F34C(work);
            m4aSongNumStart(SONG_SYS_CANSEL);
        }

        break;
    case L_BUTTON:
#ifdef VERSION_JP
        if (work->keyboardPage != 0) {
#else
        if (work->keyboardPage > 2) {
#endif
            work->keyboardPage--;
            func_jp_0808F34C(work);
            m4aSongNumStart(SONG_SYS_CANSEL);
        }

        break;
    case SELECT_BUTTON:
        work->keyCursorSteps = 1;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
#ifdef VERSION_EU
        work->x = (gKeyboardPageTabXEu[work->keyboardPage] + 8) << 8;
        work->y = 0x1A00;
#endif
        SetTaskUpdate(a, (TaskUpdateFunc)func_jp_0808F638);
#ifdef VERSION_JP
        return 1;
#else
        break;
#endif
#endif
    }

    if (work->keyCursorSteps != 0) {
#ifdef VERSION_EU
        if (work->cursor.parts.x == 14 &&work->cursor.parts.y == bottom) {
            if (gLanguage == LANGUAGE_GERMAN) {
                ApproachValue(&work->x9, 0xC800, work->keyCursorSteps);
            } else if (gLanguage == LANGUAGE_ITALIAN) {
                ApproachValue(&work->x9, 0xD100, work->keyCursorSteps);
            } else {
                ApproachValue(&work->x9, 0xD300, work->keyCursorSteps);
            }
#else
        if (work->cursor.packed == 0x6000E) {
            ApproachValue(&work->x9, 0xD300, work->keyCursorSteps);
#endif
            ApproachValue(&work->y8, 0x8C00, work->keyCursorSteps);
#ifdef VERSION_EU
        } else if (work->keyboardPage == 2) {
#else
        } else {
#endif
            ApproachValue(&work->x9, gKeyboardRowLayouts[work->cursor.parts.y].positions[work->cursor.parts.x] << 8, work->keyCursorSteps);
            ApproachValue(&work->y8, gKeyboardColumnLayouts[work->cursor.parts.x].positions[work->cursor.parts.y] << 8, work->keyCursorSteps);
#ifdef VERSION_EU
        } else {
            ApproachValue(&work->x9, gKeyboardSymbolRowLayouts[work->cursor.parts.y].positions[work->cursor.parts.x] << 8, work->keyCursorSteps);
            ApproachValue(&work->y8, gKeyboardSymbolColumnLayouts[work->cursor.parts.x].positions[work->cursor.parts.y] << 8, work->keyCursorSteps);
#endif
        }
    }

    work->x = work->x9 + 0x800;
    work->y = work->y8 + 0x800;
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateDeckMenuCloseKeyboard(DeckMenuWork* work, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 16);
    work->view = 0;
    SetDeckMenuFrameCursor(work, 0);
    SetDeckMenuHandAnim(work);
    FreeTextSlots(work->textSlots6, 8);
    ReleaseObjTiles(work->tiles11);
    ReleaseObjTiles(work->tiles13);
    ReleaseObjPalette(work->palette7);
    work->step = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckMenuLoadBgs);
    CreateDeckGridCards(work, 0);

#ifdef VERSION_EU
    {
        u8* p;
        u8 n;

        p = &work->handVisible;
        n = 1;
        *p = n;
        return n;
    }
#else
    return 1;
#endif
}

void BuildCollectionEntries(DeckMenuWork* work) {
    u16 i;
    u16 j;
    u16 n;

    work->entries = EwramAlloc(work->entryCount * sizeof(CardKindEntry));

    for (i = 0, n = 0; i <= 16; i++) {
        if (work->kindEntries[i].count != 0) {
            work->entries[n] = work->kindEntries[i];
            work->entries[n].indices = EwramAlloc(work->kindEntries[i].indexCount * 2);

            for (j = 0; j < work->kindEntries[i].indexCount; j++) {
                work->entries[n].indices[j] = work->kindEntries[i].indices[j];
            }

            n++;
        }
    }

    for (i = 143; i <= 159; i++) {
        if (work->kindEntries[i].count != 0) {
            work->entries[n] = work->kindEntries[i];
            work->entries[n].indices = EwramAlloc(work->kindEntries[i].indexCount * 2);

            for (j = 0; j < work->kindEntries[i].indexCount; j++) {
                work->entries[n].indices[j] = work->kindEntries[i].indices[j];
            }

            n++;
        }
    }

    for (i = 18; i <= 31; i++) {
        if (work->kindEntries[i].count != 0) {
            work->entries[n] = work->kindEntries[i];
            work->entries[n].indices = EwramAlloc(work->kindEntries[i].indexCount * 2);

            for (j = 0; j < work->kindEntries[i].indexCount; j++) {
                work->entries[n].indices[j] = work->kindEntries[i].indices[j];
            }

            n++;
        }
    }

    for (i = 161; i <= 174; i++) {
        if (work->kindEntries[i].count != 0) {
            work->entries[n] = work->kindEntries[i];
            work->entries[n].indices = EwramAlloc(work->kindEntries[i].indexCount * 2);

            for (j = 0; j < work->kindEntries[i].indexCount; j++) {
                work->entries[n].indices[j] = work->kindEntries[i].indices[j];
            }

            n++;
        }
    }

    for (i = 32; i <= 142; i++) {
        if (work->kindEntries[i].count != 0) {
            work->entries[n] = work->kindEntries[i];
            work->entries[n].indices = EwramAlloc(work->kindEntries[i].indexCount * 2);

            for (j = 0; j < work->kindEntries[i].indexCount; j++) {
                work->entries[n].indices[j] = work->kindEntries[i].indices[j];
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
