#include "rogue.h"
#include "card.h"
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
        return CARD_ID(CARD_KINGDOM_KEY + RogueRandBelow(CARD_ULTIMA_WEAPON + 1), RogueRandBelow(10));
    case POOL_MAGIC:
        return CARD_ID(CARD_FIRE + RogueRandBelow(CARD_AERO - CARD_FIRE + 1), RogueRandBelow(10));
    case POOL_SUMMON:
        return CARD_ID(CARD_SIMBA + RogueRandBelow(CARD_THE_BEAST - CARD_SIMBA + 1), RogueRandBelow(10));
    case POOL_ITEM:
        return CARD_ID(CARD_POTION + RogueRandBelow(CARD_MEGALIXIR - CARD_POTION + 1), RogueRandBelow(10));
    default:
        id = CARD_SOLDIER_1 + RogueRandBelow(CARD_ANSEM_9 + 1 - CARD_SOLDIER_1);

        if (gCardDefs[id].unk_2A != 3 || gCardDefs[id].gfx == 0) {
            return 0;
        }

        return id;
    }
}

// Builds the run's first deck: random cards from the whole game within the CP
// limit, with the pieces every deck needs to be playable.
void RogueBuildStartDeck(void) {
    u16 budget = gGameState.progression.cp;
    u16 id;
    u8 pool;
    s32 tries;

    sDeckCp = 0;
    sDeckCards = 0;
    sDeckEnemyCards = 0;

    // A cure and a zero come first, so the budget cannot run out before them.
    RogueAddCard(CARD_ID(CARD_CURE, 3 + RogueRandBelow(6)), budget);
    RogueAddCard(CARD_ID(CARD_KINGDOM_KEY + RogueRandBelow(4), 0), budget);

    for (tries = 0; tries < 400 && sDeckCards < DECK_MAX; tries++) {
        pool = RogueRollPool();

        if (pool == POOL_ENEMY && sDeckEnemyCards >= DECK_ENEMY_CARDS_MAX) {
            continue;
        }

        id = RogueRollCard(pool);

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

// Every sleight is known from the start: a random deck decides which are usable.
void RogueLearnSleights(void) {
    u32 i;

    for (i = FIRST_SLEIGHT; i < SLEIGHT_COUNT; i++) {
        func_0800FB2C(i);
    }
}
