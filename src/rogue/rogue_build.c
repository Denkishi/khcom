#include "rogue.h"
#include "battle.h"
#include "battle_actor.h"
#include "btl_collision.h"
#include "card.h"
#include "card_def_data.h"
#include "card_ids.h"
#include "card_types.h"
#include "system_state.h"
#include "taskpool.h"

extern const BattleAttackDef gBattleAttackDefs[];

// Builds: the deck's cards of one element make that element stronger and
// come up more often, and an infused blade adds the element to keyblade hits.

// The element bit of a BattleAttackDef's flags, by RogueElement.
static const u32 sElementFlags[ROGUE_ELEMENTS] = { 0x10000000, 0x20000000, 0x40000000 };

// Sora's own spells, used for the hit an infused blade adds.
static const u16 sElementAttacks[ROGUE_ELEMENTS] = { 66, 69, 72 };

// 8.8 damage scale that brings each of those to 192, against a swing's 256.
static const u16 sElementScales[ROGUE_ELEMENTS] = { 38, 48, 64 };

static const u8 sElementSpells[ROGUE_ELEMENTS] = { CARD_FIRE, CARD_BLIZZARD, CARD_THUNDER };

static u8 RogueFlagsElement(u32 flags) {
    u8 element;

    for (element = 0; element < ROGUE_ELEMENTS; element++) {
        if (flags & sElementFlags[element]) {
            return element;
        }
    }

    return ROGUE_ELEMENT_NONE;
}

// The element of a card: the three spells, Mushu, and the keyblades whose
// swings carry one.
u8 RogueCardElement(u16 id) {
    u16 kind = id / 10;
    u8 element;

    for (element = 0; element < ROGUE_ELEMENTS; element++) {
        if (kind == sElementSpells[element]) {
            return element;
        }
    }

    if (kind == CARD_MUSHU) {
        return ROGUE_ELEMENT_FIRE;
    }

    if (kind <= CARD_ULTIMA_WEAPON) {
        return RogueFlagsElement(gBattleAttackDefs[12 + kind * 3].flags);
    }

    return ROGUE_ELEMENT_NONE;
}

// Counts the deck's cards of each element; called when a battle starts and
// when the run page opens.
void RogueCountBuild(void) {
    Deck* deck = GetActiveDeck();
    u8 element;
    s32 i;

    for (element = 0; element < ROGUE_ELEMENTS; element++) {
        gRogue.build[element] = 0;
    }

    for (i = 0; i < DECK_SIZE; i++) {
        if (deck->cards[i] == 0xFFFF) {
            continue;
        }

        element = RogueCardElement(gCardCollection[deck->cards[i]] & CARD_ID_MASK);

        if (element != ROGUE_ELEMENT_NONE && gRogue.build[element] < 99) {
            gRogue.build[element]++;
        }
    }
}

// The element the deck is built around: the one with the most cards, from
// three up. ROGUE_ELEMENT_NONE if there is none.
u8 RogueBuildElement(void) {
    u8 best = ROGUE_ELEMENT_NONE;
    u8 count = ROGUE_BUILD_MIN - 1;
    u8 element;

    for (element = 0; element < ROGUE_ELEMENTS; element++) {
        if (gRogue.build[element] > count) {
            count = gRogue.build[element];
            best = element;
        }
    }

    return best;
}

// Damage bonus of the build in percent: 4 for each card of its element, up
// to 40.
u8 RogueBuildBonus(void) {
    u8 element = RogueBuildElement();
    u8 count;

    if (element == ROGUE_ELEMENT_NONE) {
        return 0;
    }

    count = gRogue.build[element];

    if (count > ROGUE_BUILD_MAX) {
        count = ROGUE_BUILD_MAX;
    }

    return count * 4;
}

// Called for the damage of every attack Sora lands.
s32 RogueElementDamage(s32 damage, u32 attackFlags) {
    u8 element = RogueBuildElement();

    if (element != ROGUE_ELEMENT_NONE && (attackFlags & sElementFlags[element])) {
        damage += damage * RogueBuildBonus() / 100;
    }

    return damage;
}

// A card kind to offer instead of a random one, so that a build keeps finding
// its element: its spell, about half the time. 0xFFFF for no preference.
u16 RogueBuildSpell(void) {
    u8 element;

    RogueCountBuild();
    element = RogueBuildElement();

    if (element == ROGUE_ELEMENT_NONE || RogueRandBelow(2) == 0) {
        return 0xFFFF;
    }

    return sElementSpells[element];
}

// The magic hit an infused blade adds to a keyblade hit: one of Sora's own
// spells landing on the same spot a few frames later.

typedef struct RogueEchoArgs {
    s32 x;
    s32 y;
    s32 z;
    u8 element;
} RogueEchoArgs;

typedef struct RogueEchoWork {
    RogueEchoArgs args;
    u8 timer;
    u8 wait;
} RogueEchoWork;

static void RogueEcho_Init(RogueEchoWork* w, RogueEchoArgs* args) {
    w->args = *args;
    w->timer = ROGUE_INFUSION_DELAY;
    w->wait = 0;
}

static s32 RogueEcho_Update(RogueEchoWork* w) {
    BtlObj* target = gBtlWork->actor2;
    u64 flags;
    s32 scale;

    if (w->timer != 0) {
        w->timer--;
        return 1;
    }

    // An enemy cannot be hit again while it reels from the keyblade, and by
    // then it has been knocked away: wait for the locked-on target to
    // recover, for a while, and strike it where it is.
    if (target != 0) {
        if ((target->flags & 0x180) && w->wait < ROGUE_INFUSION_WAIT) {
            w->wait++;
            return 1;
        }

        w->args.x = target->x;
        w->args.y = target->y;
        w->args.z = target->z;
    }

    // Whom a hitbox hurts follows whose card is in play: claim the player's
    // turn for this one test, as the thrown knives do.
    // The spells hit three to five times as hard as a swing; scaled down
    // here the added hit is worth about three quarters of one.
    flags = gBtlWork->flags;
    scale = gBtlWork->unk_124;
    gBtlWork->flags |= 0x20000000;
    gBtlWork->unk_124 = sElementScales[w->args.element];
    func_08011F78(sElementAttacks[w->args.element], w->args.x, w->args.y, w->args.z, 24, 16, 32);
    gBtlWork->unk_124 = scale;
    gBtlWork->flags = (gBtlWork->flags & ~0x20000000ULL) | (flags & 0x20000000);
    return 0;
}

static void RogueEcho_Draw(RogueEchoWork* w) {
}

static TaskDesc sTaskDescRogueEcho = {
    "task_rogue_echo",
    (TaskInitFunc)RogueEcho_Init,
    (TaskUpdateFunc)RogueEcho_Update,
    (TaskDrawFunc)RogueEcho_Draw,
    (TaskDestroyFunc)RogueEcho_Draw,
    sizeof(RogueEchoWork),
};

// Called when a keyblade swing connects, with the centre of its hitbox.
void RogueOnKeybladeHit(s32 x, s32 y, s32 z) {
    RogueEchoArgs args;
    u8 element;

    for (element = 0; element < ROGUE_ELEMENTS; element++) {
        if (RogueHasRelic(ROGUE_RELIC_FIRE_BLADE + element)) {
            args.x = x;
            args.y = y;
            args.z = z;
            args.element = element;
            TaskCreate(&gBtlWork->taskPools[0], &sTaskDescRogueEcho, &args);
        }
    }
}
