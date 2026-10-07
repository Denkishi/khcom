#include "rogue.h"
#include "card_def_data.h"
#include "card_ids.h"
#include "card_types.h"
#include "battle.h"
#include "system_state.h"
#include "world_types.h"

// Everything that sets how strong the two sides are, in one place.

// Enemy level: three levels a floor plus up to three across its rooms, pulled
// up to two levels towards the player's own level so that a strong player
// meets tougher enemies and a struggling one gets some room.
u8 RogueEnemyLevel(void) {
    s32 level = gRogue.floor * 3 + gRogue.room / 2;
    s32 lead = (gGameState.progression.level - 1 - level) / 2;

    if (lead > 2) {
        lead = 2;
    }

    if (lead < -2) {
        lead = -2;
    }

    level += lead;

    if (level < 0) {
        level = 0;
    }

    if (level > 60) {
        level = 60;
    }

    return level;
}

// 8.8 multiplier that grows by `early` per level up to level 15 and by `late`
// after it. The player's damage grows fast while keyblades are still being
// unlocked and slowly afterwards, and enemies follow the same shape.
static s32 RogueCurve(s32 early, s32 late) {
    s32 level = RogueEnemyLevel();

    if (level <= 15) {
        return 256 + level * early;
    }

    return 256 + 15 * early + (level - 15) * late;
}

// About 6% more HP a level, then 3%.
u16 RogueEnemyHp(u16 base) {
    return (RogueCurve(15, 8) * base) >> 8;
}

// About 5% more attack a level, then 3%.
u16 RogueEnemyAttack(u16 base) {
    return (RogueCurve(13, 8) * base) >> 8;
}

// EXP keeps pace with the level thresholds: 40% more a level, then 20%.
u16 RogueEnemyExp(u16 base) {
    return (RogueCurve(102, 51) * base) >> 8;
}

// The bosses fought as characters (Leon, Riku, the Organization...) have flat
// stats in the original game, set for wherever the story put them. Here any
// of them can end any floor, so their HP and attack come from the floor:
// 300 HP and 2 attack on the first, 180 HP and 2 attack more on each one
// after, and a quarter more HP for the boss that ends a chapter.
u16 RogueBossHp(void) {
    s32 hp = 300 + gRogue.floor * 180;

    if (RogueFloorIsChapterEnd()) {
        hp += hp / 4;
    }

    return hp;
}

u16 RogueBossAttack(void) {
    s32 attack = 2 + gRogue.floor * 2;

    if (attack > 25) {
        attack = 25;
    }

    return attack;
}

// Card kinds unlock by tier as the run goes down: floor 0 offers tiers 0 and
// 1, and each floor adds one.
static const u8 sKindTiers[] = {
    0, // Kingdom Key
    1, // Three Wishes
    1, // Crabclaw
    2, // Pumpkinhead
    2, // Fairy Harp
    2, // Wishing Star
    3, // Spellbinder
    3, // Metal Chocobo
    3, // Olympia
    4, // Lionheart
    4, // Lady Luck
    4, // Divine Rose
    5, // Oathkeeper
    5, // Oblivion
    6, // Diamond Dust
    6, // One-Winged Angel
    7, // Ultima Weapon
    0, // Fire
    0, // Blizzard
    0, // Thunder
    0, // Cure
    2, // Gravity
    2, // Stop
    3, // Aero
    0, // Donald Duck
    0, // Goofy
    2, // Simba
    3, // Genie
    2, // Bambi
    2, // Dumbo
    3, // Tinker Bell
    3, // Mushu
    4, // Cloud
    0, // Aladdin
    0, // Ariel
    0, // Jack
    0, // Peter Pan
    0, // The Beast
    0, // Potion
    1, // Hi-Potion
    3, // Mega-Potion
    1, // Ether
    3, // Mega-Ether
    4, // Elixir
    6, // Megalixir
};

#define ENEMY_CARD_TIER 1
#define BOSS_CARD_TIER 4

u8 RogueCardTier(u16 id) {
    if (id >= CARD_GUARD_ARMOR_1) {
        return BOSS_CARD_TIER;
    }

    if (id >= CARD_SOLDIER_1) {
        return ENEMY_CARD_TIER;
    }

    if (id / 10 < sizeof(sKindTiers)) {
        return sKindTiers[id / 10];
    }

    return 0xFF;
}

u8 RogueMaxCardTier(void) {
    return gRogue.floor + 1;
}

// Highest card value on offer: 5 on the first floor, one more each floor.
u8 RogueMaxCardValue(void) {
    if (gRogue.floor >= 4) {
        return 9;
    }

    return 5 + gRogue.floor;
}

// Whether a card may be offered at this point of the run.
u8 RogueCardUnlocked(u16 id) {
    if (RogueCardTier(id) > RogueMaxCardTier()) {
        return 0;
    }

    if (gCardDefs[id].unk_2A != 3 && gCardDefs[id].unk_20 > RogueMaxCardValue()) {
        return 0;
    }

    return 1;
}
