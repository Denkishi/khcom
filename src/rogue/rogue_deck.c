#include "rogue.h"
#include "card.h"
#include "card_deck.h"
#include "card_def_data.h"
#include "card_ids.h"
#include "card_types.h"
#include "mode_sio.h"
#include "mode_test_api.h"
#include "player_progression.h"
#include "system_state.h"

#define DECK_TARGET 16
#define DECK_MAX 22
#define DECK_ENEMY_CARDS_MAX 2
#define FIRST_SLEIGHT 0
#define SLEIGHT_COUNT 106

enum {
    POOL_ATTACK,
    POOL_MAGIC,
    POOL_SUMMON,
    POOL_ITEM,
    POOL_ENEMY,
};

static u16 sDeckCp;
static u8 sDeckCards;
static u8 sDeckEnemyCards;

static u8 RogueAddCard(u16 id, u16 costLimit) {
    u16 cost = GetCardCpCost(id);
    s16 slot;

    if (cost == 0 || cost > costLimit || sDeckCp + cost > gGameState.progression.cp) {
        return 0;
    }

    if (gCardDefs[id].flags & 8) {
        return 0;
    }

    slot = AddCardToCollection(id);

    if (slot == -1) {
        return 0;
    }

    AddCardToActiveDeck(slot);
    sDeckCp += cost;
    sDeckCards++;
    return 1;
}

static u8 RogueRollPool(void) {
    u32 roll = RogueRandBelow(100);

    if (roll < 62) {
        return POOL_ATTACK;
    }

    if (roll < 80) {
        return POOL_MAGIC;
    }

    if (roll < 87) {
        return POOL_SUMMON;
    }

    if (roll < 95) {
        return POOL_ITEM;
    }

    return POOL_ENEMY;
}

// Rolls a card of the pool: any keyblade, spell, summon or item at any value,
// or any enemy card.
static u16 RogueRollCard(u8 pool) {
    u16 id;

    switch (pool) {
    case POOL_ATTACK:
        return CARD_ID(CARD_KINGDOM_KEY + RogueRandBelow(CARD_ULTIMA_WEAPON + 1), RogueRandBelow(RogueMaxCardValue() + 1));
    case POOL_MAGIC:
        return CARD_ID(CARD_FIRE + RogueRandBelow(CARD_AERO - CARD_FIRE + 1), RogueRandBelow(RogueMaxCardValue() + 1));
    case POOL_SUMMON:
        return CARD_ID(CARD_SIMBA + RogueRandBelow(CARD_THE_BEAST - CARD_SIMBA + 1), RogueRandBelow(RogueMaxCardValue() + 1));
    case POOL_ITEM:
        return CARD_ID(CARD_POTION + RogueRandBelow(CARD_MEGALIXIR - CARD_POTION + 1), RogueRandBelow(RogueMaxCardValue() + 1));
    default:
        id = CARD_SOLDIER_1 + RogueRandBelow(CARD_ANSEM_9 + 1 - CARD_SOLDIER_1);

        if (gCardDefs[id].unk_2A != 3 || gCardDefs[id].gfx == 0) {
            return 0;
        }

        return id;
    }
}

// Rolls cards of the pool until one is unlocked at this point of the run, so
// that the pools keep their share whatever is locked. Returns 0 if none came up.
static u16 RogueRollUnlockedCard(u8 pool) {
    u16 id;
    s32 tries;

    for (tries = 0; tries < 24; tries++) {
        id = RogueRollCard(pool);

        if (id != 0 && GetCardCpCost(id) != 0 && !(gCardDefs[id].flags & 8) && RogueCardUnlocked(id)) {
            return id;
        }
    }

    return 0;
}

// A random card to offer as a reward, 0 if the roll found none.
u16 RogueRollRewardCard(void) {
    return RogueRollUnlockedCard(RogueRollPool());
}

// Builds the run's first deck: random cards from the whole game within the CP
// limit, with the pieces every deck needs to be playable.
void RogueBuildStartDeck(void) {
    u16 budget = gGameState.progression.cp;
    u16 id;
    u8 pool;
    s32 tries;

    // The game also resets the deck when the title loads; only a run's start
    // needs one built.
    if (!gRogue.deckWanted) {
        return;
    }

    gRogue.deckWanted = 0;
    sDeckCp = 0;
    sDeckCards = 0;
    sDeckEnemyCards = 0;

    for (tries = 0; tries < ROGUE_CARD_SLOTS; tries++) {
        gRogue.cardXp[tries] = 0;
    }

    // A cure and a zero come first, so the budget cannot run out before them.
    RogueAddCard(CARD_ID(CARD_CURE, 3 + RogueRandBelow(3)), budget);
    RogueAddCard(CARD_ID(CARD_KINGDOM_KEY + RogueRandBelow(3), 0), budget);

    // No card costs less than 10 CP, so stop once that little is left.
    for (tries = 0; tries < 400 && sDeckCards < DECK_MAX && budget - sDeckCp >= 10; tries++) {
        pool = RogueRollPool();

        if (pool == POOL_ENEMY && sDeckEnemyCards >= DECK_ENEMY_CARDS_MAX) {
            continue;
        }

        id = RogueRollUnlockedCard(pool);

        if (id == 0) {
            continue;
        }

        // Until the deck has enough cards no one card may take a big share
        // of the budget.
        if (RogueAddCard(id, sDeckCards < DECK_TARGET ? budget / 10 : budget) && pool == POOL_ENEMY) {
            sDeckEnemyCards++;
        }
    }
}


// Adds a card won during the run. It joins the deck if it fits the CP limit,
// otherwise it waits in the collection.
void RogueGiveCard(u16 id) {
    s16 slot = AddCardToCollection(id);

    if (slot == -1) {
        return;
    }

    if (slot < ROGUE_CARD_SLOTS) {
        gRogue.cardXp[slot] = 0;
    }

    if (GetDeckCpCost(GetActiveDeckIndex()) + GetCardCpCost(id) <= gGameState.progression.cp) {
        AddCardToActiveDeck(slot);
    }
}

u8 RogueCardLevel(u16 slot) {
    if (slot >= ROGUE_CARD_SLOTS || gRogue.cardXp[slot] < ROGUE_CARD_XP_LEVEL_2) {
        return 1;
    }

    if (gRogue.cardXp[slot] < ROGUE_CARD_XP_LEVEL_3) {
        return 2;
    }

    return ROGUE_CARD_LEVEL_MAX;
}

// How many cards of the deck are at a level.
u8 RogueCountCards(u8 level) {
    Deck* deck = GetActiveDeck();
    u8 count = 0;
    s32 i;

    for (i = 0; i < DECK_SIZE; i++) {
        if (deck->cards[i] != 0xFFFF && RogueCardLevel(deck->cards[i]) == level) {
            count++;
        }
    }

    return count;
}

// Every card in the deck gains experience from a won battle.
void RogueGainCardXp(void) {
    Deck* deck = GetActiveDeck();
    u16 slot;
    s32 i;

    for (i = 0; i < DECK_SIZE; i++) {
        slot = deck->cards[i];

        if (slot < ROGUE_CARD_SLOTS && gRogue.cardXp[slot] < ROGUE_CARD_XP_LEVEL_3) {
            gRogue.cardXp[slot]++;
        }
    }
}

enum {
    FUSE_ATTACK,
    FUSE_MAGIC,
    FUSE_ITEM,
};

static u8 RogueFuseClass(u16 id) {
    u16 kind = id / 10;

    if (kind <= CARD_ULTIMA_WEAPON) {
        return FUSE_ATTACK;
    }

    if (kind >= CARD_POTION) {
        return FUSE_ITEM;
    }

    return FUSE_MAGIC;
}

// What two cards fuse into: always a stronger kind, one value above the
// better of the two. Two keyblades make a later keyblade, two spells a
// summon, an item with anything a better item, and a keyblade with a spell
// one of the last five keyblades.
static u16 RogueFusionResult(u16 a, u16 b) {
    u8 classA = RogueFuseClass(a);
    u8 classB = RogueFuseClass(b);
    u16 kindA = a / 10;
    u16 kindB = b / 10;
    u16 kind;
    u16 value = a % 10 > b % 10 ? a % 10 : b % 10;

    if (value < 9) {
        value++;
    }

    if (classA == FUSE_ITEM || classB == FUSE_ITEM) {
        kind = CARD_POTION + 2;

        if (classA == FUSE_ITEM && kindA + 2 > kind) {
            kind = kindA + 2;
        }

        if (classB == FUSE_ITEM && kindB + 2 > kind) {
            kind = kindB + 2;
        }

        if (kind > CARD_MEGALIXIR) {
            kind = CARD_MEGALIXIR;
        }
    } else if (classA == FUSE_ATTACK && classB == FUSE_ATTACK) {
        kind = (kindA > kindB ? kindA : kindB) + 1 + RogueRandBelow(3);

        if (kind > CARD_ULTIMA_WEAPON) {
            kind = CARD_ULTIMA_WEAPON;
        }

        // A fusion may reach two tiers past what the floor offers, no further.
        while (kind > kindA && kind > kindB && RogueCardTier(CARD_ID(kind, 0)) > RogueMaxCardTier() + 2) {
            kind--;
        }
    } else if (classA == FUSE_MAGIC && classB == FUSE_MAGIC) {
        kind = CARD_SIMBA + RogueRandBelow(CARD_THE_BEAST - CARD_SIMBA + 1);
    } else {
        kind = CARD_OATHKEEPER + RogueRandBelow(CARD_ULTIMA_WEAPON - CARD_OATHKEEPER + 1);

        while (kind > CARD_SPELLBINDER && RogueCardTier(CARD_ID(kind, 0)) > RogueMaxCardTier() + 2) {
            kind--;
        }
    }

    return CARD_ID(kind, value);
}

// Fusions unlock with the chapters: keyblades with keyblades and anything
// with an item from the start, spells into summons from the second chapter,
// a keyblade with a spell from the third.
static u8 RogueFusionUnlocked(u16 a, u16 b) {
    u8 classA = RogueFuseClass(a);
    u8 classB = RogueFuseClass(b);

    if (classA == FUSE_ITEM || classB == FUSE_ITEM) {
        return 1;
    }

    if (classA == FUSE_ATTACK && classB == FUSE_ATTACK) {
        return 1;
    }

    if (classA == FUSE_MAGIC && classB == FUSE_MAGIC) {
        return gRogueMeta.chapters >= 2;
    }

    return gRogueMeta.chapters >= 3;
}

// Looks for two level 3 cards in the deck to fuse. Fills in their deck
// positions and the card they make.
u8 RogueRollFusion(u8* posA, u8* posB, u16* result) {
    Deck* deck = GetActiveDeck();
    u8 ready[DECK_SIZE];
    u16 slot;
    u16 id;
    s32 count = 0;
    s32 i;
    s32 a;
    s32 b;

    for (i = 0; i < DECK_SIZE; i++) {
        slot = deck->cards[i];

        if (slot == 0xFFFF || RogueCardLevel(slot) < ROGUE_CARD_LEVEL_MAX) {
            continue;
        }

        id = gCardCollection[slot] & CARD_ID_MASK;

        if (gCardDefs[id].unk_2A != 3 && id < CARD_ID(CARD_MEGALIXIR + 1, 0)) {
            ready[count++] = i;
        }
    }

    if (count < 2) {
        return 0;
    }

    // Pairs whose kind of fusion is still locked are passed over.
    for (i = 0; i < 12; i++) {
        a = RogueRandBelow(count);
        b = RogueRandBelow(count - 1);

        if (b >= a) {
            b++;
        }

        if (RogueFusionUnlocked(gCardCollection[deck->cards[ready[a]]] & CARD_ID_MASK,
                                gCardCollection[deck->cards[ready[b]]] & CARD_ID_MASK)) {
            break;
        }
    }

    if (i == 12) {
        return 0;
    }

    *posA = ready[a];
    *posB = ready[b];
    *result = RogueFusionResult(gCardCollection[deck->cards[ready[a]]] & CARD_ID_MASK,
                                gCardCollection[deck->cards[ready[b]]] & CARD_ID_MASK);
    return 1;
}

// Takes a card out of the deck and of the collection. The deck is read up to
// its first empty position, so the gap is closed.
void RogueRemoveDeckCard(u8 pos) {
    Deck* deck = GetActiveDeck();
    u16 slot = deck->cards[pos];
    s32 count;
    s32 i;

    RemoveCardFromActiveDeck(pos);
    gCardCollection[slot] = CARD_ID_MASK;

    for (i = 0, count = 0; i < DECK_SIZE; i++) {
        if (deck->cards[i] != 0xFFFF) {
            deck->cards[count++] = deck->cards[i];
        }
    }

    while (count < DECK_SIZE) {
        deck->cards[count++] = 0xFFFF;
    }
}

// A random position of the deck that holds a keyblade, spell, summon or item
// card, or 0xFF if it has none.
u8 RogueRollDeckCard(void) {
    Deck* deck = GetActiveDeck();
    u16 id;
    u8 pos;
    s32 tries;

    for (tries = 0; tries < 40; tries++) {
        pos = RogueRandBelow(DECK_SIZE);

        if (deck->cards[pos] == 0xFFFF) {
            continue;
        }

        id = gCardCollection[deck->cards[pos]] & CARD_ID_MASK;

        if (gCardDefs[id].unk_2A != 3) {
            return pos;
        }
    }

    return 0xFF;
}

// Another card of the same kind of pool to turn a card into, 0 if none came up.
u16 RogueRollTransform(u16 id) {
    u8 pool = POOL_ATTACK;
    u16 result;

    if (RogueFuseClass(id) == FUSE_MAGIC) {
        pool = id / 10 >= CARD_SIMBA ? POOL_SUMMON : POOL_MAGIC;
    } else if (RogueFuseClass(id) == FUSE_ITEM) {
        pool = POOL_ITEM;
    }

    result = RogueRollUnlockedCard(pool);
    return result != id ? result : 0;
}

// Consumes the two cards and adds what they make. The CP limit grows if the
// new card costs more than the two did, so the fusion always fits.
void RogueFuse(u8 posA, u8 posB, u16 result) {
    Deck* deck = GetActiveDeck();
    u16 slotA = deck->cards[posA];
    u16 slotB = deck->cards[posB];
    u16 freed = GetCardCpCost(gCardCollection[slotA]) + GetCardCpCost(gCardCollection[slotB]);
    u16 cost = GetCardCpCost(result);

    // The higher position goes first, so the lower one is still where it was.
    RogueRemoveDeckCard(posA > posB ? posA : posB);
    RogueRemoveDeckCard(posA > posB ? posB : posA);

    if (cost > freed) {
        gGameState.progression.cp += cost - freed;
    }

    RogueGiveCard(result);
}
