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

// Builds: what the deck and the relics have a lot of gets stronger and comes
// up more often. Several builds can be active at once and their bonuses add
// up on an attack that belongs to more than one, which is how a run breaks
// the game: a deck of Fire spells with the knives is a fire, spell and
// projectile build all together.

typedef struct RogueBuildDef {
    u8 min; // points needed for the build to count
    u8 max; // points past which it stops growing
    u8 bonus; // percent of damage for each point
} RogueBuildDef;

static const RogueBuildDef sBuilds[ROGUE_BUILDS] = {
    { 3, 10, 4 }, // fire
    { 3, 10, 4 }, // ice
    { 3, 10, 4 }, // thunder
    { 10, 16, 2 }, // blade: keyblade cards
    { 5, 10, 4 }, // spell: magic cards
    { 2, 5, 8 }, // summon
    { 3, 8, 6 }, // projectile: thrown things, see RogueCountBuild
};

// The element bit of a BattleAttackDef's flags, by element build.
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

    // Water is Blizzard underneath.
    if (kind == ROGUE_CARD_WATER) {
        return ROGUE_ELEMENT_ICE;
    }

    // A keyblade's swings are the three attacks from 12 + 3 * its action id.
    if (ROGUE_IS_KEYBLADE(kind)) {
        return RogueFlagsElement(gBattleAttackDefs[12 + gCardDefs[id].unk_24 * 3].flags);
    }

    return ROGUE_ELEMENT_NONE;
}

// The class build a kind of card belongs to, ROGUE_BUILDS for none.
static u8 RogueKindBuild(u16 kind) {
    if (ROGUE_IS_KEYBLADE(kind)) {
        return ROGUE_BUILD_BLADE;
    }

    if ((kind >= CARD_FIRE && kind <= CARD_AERO) || ROGUE_IS_NEW_SPELL(kind)) {
        return ROGUE_BUILD_SPELL;
    }

    if (kind >= CARD_SIMBA && kind <= CARD_CLOUD) {
        return ROGUE_BUILD_SUMMON;
    }

    return ROGUE_BUILDS;
}

static void RogueBuildAdd(u8 build, u8 points) {
    if (build < ROGUE_BUILDS && gRogue.build[build] < 99) {
        gRogue.build[build] += points;
    }
}

// Counts the points of every build; called when a battle starts, when the
// run page opens and before a reward is rolled. A card gives a point to its
// element and one to its class; Fire and Blizzard, which are thrown, give one
// to projectiles too. The knives are worth three projectile points and an
// infused blade two of its element.
void RogueCountBuild(void) {
    Deck* deck = GetActiveDeck();
    u16 id;
    u8 build;
    u8 moves;
    s32 i;

    for (build = 0; build < ROGUE_BUILDS; build++) {
        gRogue.build[build] = 0;
    }

    for (i = 0; i < DECK_SIZE; i++) {
        if (deck->cards[i] == 0xFFFF) {
            continue;
        }

        id = gCardCollection[deck->cards[i]] & CARD_ID_MASK;

        if (gCardDefs[id].unk_2A == 3) {
            continue;
        }

        RogueBuildAdd(RogueCardElement(id), 1);
        RogueBuildAdd(RogueKindBuild(id / 10), 1);

        if (id / 10 == CARD_FIRE || id / 10 == CARD_BLIZZARD || id / 10 == ROGUE_CARD_WATER) {
            RogueBuildAdd(ROGUE_BUILD_PROJECTILE, 1);
        }
    }

    if (RogueHasRelic(ROGUE_RELIC_KNIVES)) {
        RogueBuildAdd(ROGUE_BUILD_PROJECTILE, 3);
    }

    if (RogueHasRelic(ROGUE_RELIC_ICE_PILLAR)) {
        RogueBuildAdd(ROGUE_ELEMENT_ICE, 2);
    }

    for (build = 0; build < ROGUE_ELEMENTS; build++) {
        if (RogueHasRelic(ROGUE_RELIC_FIRE_BLADE + build)) {
            RogueBuildAdd(build, 2);
        }
    }

    // Relic sets. Vexen's three, the ice block, the needles and the shards,
    // are worth four ice points together; any three boss moves, three
    // projectile points.
    if (RogueHasRelic(ROGUE_RELIC_ICE_PILLAR) && RogueHasRelic(ROGUE_RELIC_NEEDLES) && RogueHasRelic(ROGUE_RELIC_SHARDS)) {
        RogueBuildAdd(ROGUE_ELEMENT_ICE, 4);
    }

    moves = RogueHasRelic(ROGUE_RELIC_KNIVES) + RogueHasRelic(ROGUE_RELIC_ICE_PILLAR);

    for (build = 0; build < ROGUE_MOVES; build++) {
        moves += RogueHasRelic(ROGUE_RELIC_CHAKRAM + build);
    }

    if (moves >= 3) {
        RogueBuildAdd(ROGUE_BUILD_PROJECTILE, 3);
    }
}

// Damage bonus of a build in percent, 0 while it has too few points.
u8 RogueBuildBonus(u8 build) {
    u8 points = gRogue.build[build];

    if (points < sBuilds[build].min) {
        return 0;
    }

    if (points > sBuilds[build].max) {
        points = sBuilds[build].max;
    }

    return points * sBuilds[build].bonus;
}

// The element with the most points among the active element builds, or
// ROGUE_ELEMENT_NONE.
u8 RogueBuildElement(void) {
    u8 best = ROGUE_ELEMENT_NONE;
    u8 points = 0;
    u8 element;

    for (element = 0; element < ROGUE_ELEMENTS; element++) {
        if (RogueBuildBonus(element) != 0 && gRogue.build[element] > points) {
            points = gRogue.build[element];
            best = element;
        }
    }

    return best;
}

static void RogueEcho(s32 x, s32 y, s32 z, u16 attack, u16 scale);

// Called for the damage of every attack Sora lands, with the attack's
// definition index and flags. Adds up the bonuses of every build the attack
// belongs to, up to double damage.
s32 RogueBuildDamage(s32 damage, u16 attack, u32 attackFlags) {
    s32 bonus = 0;
    u8 element = RogueFlagsElement(attackFlags);
    BtlObj* target;

    if (element != ROGUE_ELEMENT_NONE) {
        bonus += RogueBuildBonus(element);
    }

    if (gRogue.projectile) {
        bonus += RogueBuildBonus(ROGUE_BUILD_PROJECTILE);
    } else if (gRogue.playedKind != ROGUE_NO_KIND) {
        if (RogueKindBuild(gRogue.playedKind) != ROGUE_BUILDS) {
            bonus += RogueBuildBonus(RogueKindBuild(gRogue.playedKind));
        }

        if (gRogue.playedKind == CARD_FIRE || gRogue.playedKind == CARD_BLIZZARD) {
            bonus += RogueBuildBonus(ROGUE_BUILD_PROJECTILE);
        }

        // Arcane echo: a spell that lands is cast again at half strength.
        if (RogueHasRelic(ROGUE_RELIC_ARCANE_ECHO) && RogueKindBuild(gRogue.playedKind) == ROGUE_BUILD_SPELL &&
            !gRogue.echoing) {
            target = gBtlWork->actor2;

            if (target != 0) {
                RogueEcho(target->x, target->y, target->z, attack, 128);
            }
        }
    }

    if (!gRogue.projectile && gRogue.playedKind != ROGUE_NO_KIND && RogueKindBuild(gRogue.playedKind) == ROGUE_BUILD_SPELL) {
        bonus += 10 * RogueUpgradeLevel(ROGUE_UPGRADE_MAGIC);
    }

    if (gRogue.playedMod == ROGUE_MOD_HEAVY && !gRogue.projectile && !gRogue.echoing) {
        bonus += 25;
    }

    if (bonus > 100) {
        bonus = 100;
    }

    return damage + damage * bonus / 100;
}

// Reward rolls lean towards what the deck is built on. Returns how much of
// 100 goes to a card pool on top of its share: 0 to 2 for keyblades, spells
// and summons.
u8 RogueBuildPoolBias(u8 pool) {
    static const u8 builds[] = { ROGUE_BUILD_BLADE, ROGUE_BUILD_SPELL, ROGUE_BUILD_SUMMON };

    if (pool < 3 && RogueBuildBonus(builds[pool]) != 0) {
        return 15;
    }

    return 0;
}

// A card kind to offer instead of a random spell, so that an element build
// keeps finding its spell: about half the time. 0xFFFF for no preference.
u16 RogueBuildSpell(void) {
    u8 element = RogueBuildElement();

    if (element == ROGUE_ELEMENT_NONE || RogueRandBelow(2) == 0) {
        return 0xFFFF;
    }

    return sElementSpells[element];
}

// An added hit: an attack landing on the locked-on enemy a little after the
// one that caused it. Infused blades, the arcane echo and build finishers all
// use it.

typedef struct RogueEchoArgs {
    s32 x;
    s32 y;
    s32 z;
    u16 attack;
    u16 scale; // 8.8, of the attack's own damage
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

    // An enemy cannot be hit again while it reels from the first hit, and by
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
    flags = gBtlWork->flags;
    scale = gBtlWork->unk_124;
    gBtlWork->flags |= 0x20000000;
    gBtlWork->unk_124 = w->args.scale;
    gRogue.echoing = 1;
    gRogue.projectile = 1;

    if (func_08011F78(w->args.attack, w->args.x, w->args.y, w->args.z, 24, 16, 32)) {
        gRogueDebug.echoes++;
    }

    gRogue.projectile = 0;
    gRogue.echoing = 0;
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

static void RogueEcho(s32 x, s32 y, s32 z, u16 attack, u16 scale) {
    RogueEchoArgs args;

    args.x = x;
    args.y = y;
    args.z = z;
    args.attack = attack;
    args.scale = scale;
    TaskCreate(&gBtlWork->taskPools[0], &sTaskDescRogueEcho, &args);
}

// Called when a keyblade swing connects, with the centre of its hitbox and
// whether it is the combo's finisher. An infused blade follows every swing
// with its element; an element build follows the finisher with a stronger
// one of its own.
static void RogueKeybladeEffect(s32 x, s32 y, s32 z, u8 finisher);

void RogueOnKeybladeHit(s32 x, s32 y, s32 z, u8 finisher) {
    u8 element;

    for (element = 0; element < ROGUE_ELEMENTS; element++) {
        if (RogueHasRelic(ROGUE_RELIC_FIRE_BLADE + element)) {
            RogueEcho(x, y, z, sElementAttacks[element], sElementScales[element]);
        }
    }

    element = RogueBuildElement();

    if (finisher && element != ROGUE_ELEMENT_NONE) {
        RogueEcho(x, y, z, sElementAttacks[element], sElementScales[element] * 2);
    }

    RogueKeybladeEffect(x, y, z, finisher);

    // What the card played is enchanted with.
    switch (gRogue.playedMod) {
    case ROGUE_MOD_FIRE:
    case ROGUE_MOD_ICE:
    case ROGUE_MOD_THUNDER:
        RogueEcho(x, y, z, sElementAttacks[gRogue.playedMod - ROGUE_MOD_FIRE], 96);
        break;
    case ROGUE_MOD_DOUBLE:
        RogueEcho(x, y, z, 14, 128);
        break;
    case ROGUE_MOD_LIFESTEAL:
        if (gBtlWork->actor->unk_02C > 0 && gBtlWork->actor->unk_02C < gBtlWork->actor->unk_02E) {
            gBtlWork->actor->unk_02C++;
        }
        break;
    }
}

// What each of the mod's keyblades does of its own when a swing of it lands,
// on every hit or on the finisher.
static void RogueKeybladeEffect(s32 x, s32 y, s32 z, u8 finisher) {
    BtlObj* sora = gBtlWork->actor;
    BtlObj* target = gBtlWork->actor2;

    if (gRogue.playedKind < ROGUE_FIRST_CARD_KIND || gRogue.echoing) {
        return;
    }

    gRogueDebug.keybladeEffects++;

    switch (gRogue.playedKind - ROGUE_FIRST_CARD_KIND) {
    case 0: // Bond of Flame: fire follows every hit
        RogueEcho(x, y, z, sElementAttacks[ROGUE_ELEMENT_FIRE], 96);
        break;
    case 1: // Two Become One: every hit lands twice
        RogueEcho(x, y, z, 14, 128);
        break;
    case 2: // Hidden Dragon: the finisher throws a fireball
        if (finisher) {
            RogueDoMove(ROGUE_MOVE_FIREBALL, sora);
        }
        break;
    case 3: // Follow the Wind: the finisher raises a whirl
        if (finisher) {
            RogueDoMove(ROGUE_MOVE_WIND, sora);
        }
        break;
    case 4: // Monochrome: every hit heals a little
        if (sora->unk_02C > 0 && sora->unk_02C < sora->unk_02E) {
            sora->unk_02C++;
        }
        break;
    case 5: // Midnight Roar: the finisher shakes everything around
        if (finisher) {
            RogueShockwave(sora, 0, 120);
        }
        break;
    case 6: // Total Eclipse: thunder follows every hit
        RogueEcho(x, y, z, sElementAttacks[ROGUE_ELEMENT_THUNDER], 96);
        break;
    case 7: // Glimpse of Darkness: a second, heavier hit paid in HP
        RogueEcho(x, y, z, 14, 224);

        if (sora->unk_02C > 1) {
            sora->unk_02C--;
        }
        break;
    case 8: // Maverick Flare: the finisher bursts into flame
        if (finisher) {
            RogueDoMove(ROGUE_MOVE_FIRE_BURST, sora);
        }
        break;
    case 9: // Ominous Blight: every hit leaves a burn
        if (target != 0) {
            RogueApplyBurn(target, 2 + gRogue.floor);
        }
        break;
    case 10: // Lunar Eclipse: ice follows every hit
        RogueEcho(x, y, z, sElementAttacks[ROGUE_ELEMENT_ICE], 96);
        break;
    case 11: // Silent Dirge: the finisher freezes its target
        if (finisher && target != 0) {
            RogueApplyFreeze(target);
        }
        break;
    case 12: // Dream Sword: the first hit of a string lands twice as hard
        if (gRogue.combo <= 1) {
            RogueEcho(x, y, z, 14, 256);
        }
        break;
    case 16: // Hero's Key: the finisher heals
        if (finisher) {
            sora->unk_02C += 3;

            if (sora->unk_02C > sora->unk_02E) {
                sora->unk_02C = sora->unk_02E;
            }
        }
        break;
    }
}

// Arts: a sleight bound to a kind of card, so that one high card of that kind
// performs it alone. The numbers are the action ids Sora's battle task gives
// the sleights; these were picked by trying each from a single card.
static const u8 sAttackArts[] = { 107, 111, 127, 129 };
static const u8 sFireArts[] = { 114, 126 };

// An art that suits a kind of card, 0 if the kind takes none.
u8 RogueRollArt(u16 kind) {
    u8 move;

    // One of the moves made from other characters' effects, if any is unlocked,
    // one time in four.
    if (RogueRandBelow(4) == 0) {
        move = RogueRandBelow(ROGUE_MOVES);

        if (RogueMoveUnlocked(move)) {
            return ROGUE_ART_MOVES + move;
        }
    }

    // A boss move, once its boss has been beaten, about one time in three.
    if ((gRogueMeta.bossMoves & (ROGUE_BOSS_MOVE_LARXENE | ROGUE_BOSS_MOVE_VEXEN)) != 0 && RogueRandBelow(3) == 0) {
        if ((gRogueMeta.bossMoves & ROGUE_BOSS_MOVE_VEXEN) &&
            (!(gRogueMeta.bossMoves & ROGUE_BOSS_MOVE_LARXENE) || RogueRandBelow(2) == 0)) {
            return ROGUE_ART_PILLAR;
        }

        return ROGUE_ART_KNIVES;
    }

    if (kind <= CARD_ULTIMA_WEAPON) {
        return sAttackArts[RogueRandBelow(sizeof(sAttackArts))];
    }

    switch (kind) {
    case CARD_FIRE:
        return sFireArts[RogueRandBelow(sizeof(sFireArts))];
    case CARD_BLIZZARD:
        return 124;
    case CARD_THUNDER:
        return 118;
    }

    return 0;
}

// What a card played alone does: its own action, or its kind's art if the
// card is high enough. Also notes the kind played, for the builds.
s32 RogueCardAction(const CardDef* def) {
    u16 id = def - gCardDefs;
    u16 kind = id / 10;

    gRogue.playedKind = def->unk_2A != 3 ? kind : ROGUE_NO_KIND;

    // The new spells: each is a move of its own, cast with a swing.
    if (ROGUE_IS_NEW_SPELL(kind)) {
        RogueDoMove(ROGUE_MOVE_WATER + kind - ROGUE_CARD_WATER, gBtlWork->actor);
        return ROGUE_ACTION_SWING;
    }

    // The whim: after each reload the first attack or spell played alone
    // does a sleight picked at random.
    if (RogueHasRelic(ROGUE_RELIC_RANDOM_SLEIGHT) && gRogue.sleightReady && def->unk_2A != 3 && kind <= CARD_AERO) {
        u8 art = RogueRollArt(kind);

        gRogue.sleightReady = 0;

        if (art >= ROGUE_ART_MOVES) {
            RogueDoMove(art - ROGUE_ART_MOVES, gBtlWork->actor);
            return def->unk_24;
        }

        if (art == ROGUE_ART_KNIVES) {
            RogueThrowKnives(gBtlWork->actor);
            return def->unk_24;
        }

        if (art == ROGUE_ART_PILLAR) {
            RogueRaisePillar(gBtlWork->actor);
            return def->unk_24;
        }

        return art;
    }

    // The cards with an effect of their own, cast with a swing.
    if (kind >= ROGUE_FIRST_EFFECT_KIND && kind < ROGUE_FIRST_CARD_KIND + ROGUE_CARD_KINDS) {
        const RogueCardEffect* effect = &gRogueCardEffects[kind - ROGUE_FIRST_CARD_KIND];
        BtlObj* sora = gBtlWork->actor;

        switch (effect->effect) {
        case ROGUE_EFFECT_MOVE:
            RogueDoMove(effect->a, sora);
            return ROGUE_ACTION_SWING;
        case ROGUE_EFFECT_SHOCK:
            RogueShockwave(sora, effect->a, effect->b * 4);
            return ROGUE_ACTION_SWING;
        case ROGUE_EFFECT_PLUTO:
            if (gRogue.shards < 9999 - ROGUE_PLUTO_SHARDS) {
                gRogue.shards += ROGUE_PLUTO_SHARDS;
            }
            // And heals.
        case ROGUE_EFFECT_HEAL:
            sora->unk_02C += (sora->unk_02E * effect->a) >> 8;

            if (sora->unk_02C > sora->unk_02E) {
                sora->unk_02C = sora->unk_02E;
            }

            RogueSoraPose(sora);
            m4aSongNumStart(SONG_EF_SUMMON_UP);
            return ROGUE_ACTION_SWING;
        case ROGUE_EFFECT_KNIVES:
            RogueThrowKnives(sora);
            return ROGUE_ACTION_SWING;
        case ROGUE_EFFECT_PILLAR:
            RogueRaisePillar(sora);
            return ROGUE_ACTION_SWING;
        case ROGUE_EFFECT_SLEIGHT:
            return effect->a;
        }
    }

    // A tag card: the character does the move and the card counts as a swing,
    // so that it chains with the cards around it.
    if (def->unk_2A != 3 && RogueTagIn(kind)) {
        gRogue.playedKind = CARD_KINGDOM_KEY;
        return ROGUE_ACTION_SWING;
    }

    // An art works once for each reload of the deck.
    if (kind < ROGUE_ART_KINDS && gRogue.arts[kind] != 0 && def->unk_2A != 3 && def->unk_20 >= ROGUE_ART_MIN_VALUE &&
        !(gRogue.artsUsed & (1 << kind))) {
        gRogue.artsUsed |= 1 << kind;

        switch (gRogue.arts[kind]) {
        case ROGUE_ART_KNIVES:
            RogueThrowKnives(gBtlWork->actor);
            return def->unk_24;
        case ROGUE_ART_PILLAR:
            RogueRaisePillar(gBtlWork->actor);
            return def->unk_24;
        }

        if (gRogue.arts[kind] >= ROGUE_ART_MOVES) {
            RogueDoMove(gRogue.arts[kind] - ROGUE_ART_MOVES, gBtlWork->actor);
            return def->unk_24;
        }

        return gRogue.arts[kind];
    }

    return def->unk_24;
}

// Called when cards are played together, as a sleight or a stock: the hits
// that follow belong to no single kind.
void RogueOnStockPlayed(void) {
    gRogue.playedKind = ROGUE_NO_KIND;
    gRogue.playedMod = ROGUE_MOD_NONE;
    gRogue.cardBuffer = 0;
}

void RogueOnReload(void) {
    gRogue.artsUsed = 0;
    gRogue.freeCard = 1;
    gRogue.sleightReady = 1;
}

// The relics of the card game.

// Whether an enemy card of this value fails to break the player's card on
// the table: a zero that cannot be broken, or a tie the player wins.
u8 RogueBlocksBreak(s32 value) {
    s32 mine = (s16)gCardBattleState->unk_0C2;

    if (gBtlWork->unk_0A4 != 1) {
        return 0;
    }

    if (RogueHasRelic(ROGUE_RELIC_ZERO_SHIELD) && mine == 0) {
        return 1;
    }

    return RogueHasRelic(ROGUE_RELIC_TIE_WIN) && mine == value && value != 0;
}

u8 RogueTieWins(void) {
    return RogueHasRelic(ROGUE_RELIC_TIE_WIN);
}

// The value one of the player's cards plays at. A zero stays a zero: it is
// worth more as one.
u8 RoguePlayerCardValue(u8 value) {
    if (RogueHasRelic(ROGUE_RELIC_PLUS_ONE) && value != 0 && value < 9) {
        value++;
    }

    return value;
}

u8 RogueKeepCard(void) {
    if (RogueHasRelic(ROGUE_RELIC_FREE_FIRST) && gRogue.freeCard) {
        gRogue.freeCard = 0;
        return 1;
    }

    return 0;
}

// Called with the place in the deck of a card played alone, before its
// action is asked for: what that card is enchanted with counts for its hits.
void RogueOnCardSlot(u16 deckIndex) {
    u16 slot = deckIndex < DECK_SIZE ? GetActiveDeck()->cards[deckIndex] : 0xFFFF;

    gRogue.playedMod = slot < ROGUE_CARD_SLOTS ? gRogue.cardMod[slot] : ROGUE_MOD_NONE;
    gRogueDebug.lastMod = gRogue.playedMod;
}

static const u8 sModFire[] = "Fuoco a ogni colpo";
static const u8 sModIce[] = "Gelo a ogni colpo";
static const u8 sModThunder[] = "Tuono a ogni colpo";
static const u8 sModDouble[] = "Ogni colpo vale doppio";
static const u8 sModLifesteal[] = "Ogni colpo cura 1 PV";
static const u8 sModHeavy[] = "Un quarto di danno in pi\xF9";

const u8* RogueCardModName(u8 mod) {
    static const u8* const names[ROGUE_CARD_MODS] = { sModFire, sModFire, sModIce, sModThunder, sModDouble, sModLifesteal, sModHeavy };

    return names[mod];
}
