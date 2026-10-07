#include "rogue.h"
#include "battle.h"
#include "battle_actor.h"
#include "listpool.h"
#include "system_state.h"

// Gadgets: relics that add something to how a battle plays. Each is a line
// of a table: when it goes off, what it does, and after how long. The list,
// with the names and the texts, is in tools/rogue_gadgets.py.

enum {
    GADGET_DO_ORBIT, // a: move, b: how many circle Sora
    GADGET_DO_SHARD, // a: move, b: frames it hangs over Sora before it flies
    GADGET_DO_BOLT, // a: 0 on the enemy that set it off or is locked on, 1 on another
    GADGET_DO_AT_TARGET, // a: move, where the enemy stands; b: 1 if it freezes
    GADGET_DO_AT_SORA, // a: move, where Sora stands; b: 1 if it freezes
    GADGET_DO_AT_SPOT, // a: move, where what set it off happened
    GADGET_DO_CAST, // a: move, done by Sora as any other, modifiers and all
    GADGET_DO_RAIN, // a: move, b: how many come down around the enemy
    GADGET_DO_SHOCK, // a: element (0 plain), b: damage in 1/64 of a swing
    GADGET_DO_HEAL, // a: HP
    GADGET_DO_VOLLEY, // a: move, b: how many form over Sora and fly one after the other
    GADGET_DO_BUFF, // a: percent more damage, b: for how many tenths of a second
    GADGET_DO_PACT, // the same, at the cost of 1 HP
    GADGET_DO_WEIGHT, // the same, and slower on his feet meanwhile
    GADGET_DO_HASTE, // a: percent faster on his feet, b: for how many tenths of a second
    GADGET_DO_RELOAD, // a: percent faster reload, b: for how many tenths of a second
    GADGET_DO_VALUE, // a: what the next card played is worth more
    GADGET_DO_HURT, // a: HP Sora loses, never the last
    GADGET_DO_SHARDS, // a: shards
    GADGET_DO_STOP_ALL, // every enemy is frozen for a moment
    GADGET_DO_SHIELD // a: tenths of a second no hit hurts
};

typedef struct RogueGadgetDef {
    const u8* name;
    const u8* text;
    u8 trigger;
    u8 number;
    u8 effect;
    u8 a;
    u8 b;
    u8 delay; // frames from the trigger to the effect
} RogueGadgetDef;

// A pair of gadgets that, owned together, do one thing between them in place
// of what each does.
typedef struct RogueFusionDef {
    u8 first;
    u8 second;
    RogueGadgetDef def;
} RogueFusionDef;

#include "rogue_gadget_table.inc"

const u8* RogueGadgetName(u8 gadget) {
    return sGadgets[gadget].name;
}

const u8* RogueGadgetText(u8 gadget) {
    return sGadgets[gadget].text;
}

// What is owed: a trigger is often met in the middle of a hit being worked
// out, so the effect is noted and done on a later frame. That also lets
// several gadgets set off together go one after the other.
#define GADGET_QUEUE 16

typedef struct RogueGadgetOwed {
    BtlObj* target;
    s32 x;
    s32 y;
    s32 z;
    u8 gadget; // plus one, 0 for a free place
    u8 delay;
} RogueGadgetOwed;

static RogueGadgetOwed sOwed[GADGET_QUEUE];
static u16 sTimers[ROGUE_GADGETS + ROGUE_FUSIONS];
static u16 sCounts[GADGET_TRIGGERS]; // times each trigger was met this battle
static u8 sStarted;
static u8 sWasAirborne;
static u8 sFirstHit;
static u8 sOrbiters; // things circling Sora
static BtlObj* sLocked;
static s32 sLastX;
static s32 sLastY;
// What is on for a while, each with the frames it still lasts.
static u16 sBuffTime;
static u8 sBuff; // percent more damage
static u16 sHasteTime;
static s8 sHaste; // percent faster, or slower
static u16 sReloadTime;
static u8 sReload; // percent faster reload
static u16 sShieldTime;
static u8 sValue; // what the next card is worth more
static u16 sHurtSeen; // hits taken as of last frame

#define GADGET_ORBITERS_MAX 6

void RogueGadgetReset(void) {
    s32 i;

    for (i = 0; i < GADGET_QUEUE; i++) {
        sOwed[i].gadget = 0;
    }

    for (i = 0; i < ROGUE_GADGETS + ROGUE_FUSIONS; i++) {
        sTimers[i] = 0;
    }

    for (i = 0; i < GADGET_TRIGGERS; i++) {
        sCounts[i] = 0;
    }

    sStarted = 0;
    sWasAirborne = 0;
    sFirstHit = 0;
    sOrbiters = 0;
    sLocked = 0;
    sBuffTime = 0;
    sHasteTime = 0;
    sReloadTime = 0;
    sShieldTime = 0;
    sValue = 0;
    sHurtSeen = 0;
    sLastX = 0;
    sLastY = 0;
}

// The table entry of a gadget or, past the gadgets, of a fusion.
static const RogueGadgetDef* RogueGadgetEntry(u8 index) {
    if (index >= ROGUE_GADGETS) {
        return &sFusions[index - ROGUE_GADGETS].def;
    }

    return &sGadgets[index];
}

// Whether an entry is at work: a fusion when the run has both its relics, a
// gadget when the run has its relic and no fusion has taken it.
static u8 RogueGadgetOwned(u8 index) {
    const RogueFusionDef* fusion;
    u8 i;

    if (index >= ROGUE_GADGETS) {
        fusion = &sFusions[index - ROGUE_GADGETS];
        return RogueHasRelic(ROGUE_RELIC_FIRST_GADGET + fusion->first) && RogueHasRelic(ROGUE_RELIC_FIRST_GADGET + fusion->second);
    }

    if (!RogueHasRelic(ROGUE_RELIC_FIRST_GADGET + index)) {
        return 0;
    }

    for (i = 0; i < ROGUE_FUSIONS; i++) {
        if ((sFusions[i].first == index || sFusions[i].second == index) && RogueGadgetOwned(ROGUE_GADGETS + i)) {
            return 0;
        }
    }

    return 1;
}

// An enemy still in the battle: the one asked for if it is, or the one locked
// on, or any. `other` asks for one that is not the one given.
static BtlObj* RogueGadgetEnemy(BtlObj* wanted, u8 other) {
    BtlObj* sora = gBtlWork->actor;
    BtlObj* actor;
    BtlObj* any = 0;

    for (actor = (BtlObj*)ListPoolFirst(&gBtlWork->pool); actor != 0; actor = (BtlObj*)ListPoolNext(&actor->node)) {
        if (actor == sora || actor->unk_02C <= 0) {
            continue;
        }

        if (actor == wanted && !other) {
            return actor;
        }

        if (actor != wanted && (any == 0 || actor == gBtlWork->actor2)) {
            any = actor;
        }
    }

    return any;
}

static void RogueGadgetDo(const RogueGadgetDef* def, RogueGadgetOwed* owed) {
    BtlObj* sora = gBtlWork->actor;
    BtlObj* enemy;
    s32 i;

    switch (def->effect) {
    case GADGET_DO_ORBIT:
        // b: how many, with the top bit for ones that freeze. However many
        // relics ask for them, only so many things circle Sora at once.
        for (i = 0; i < (def->b & 0x7F) && sOrbiters < GADGET_ORBITERS_MAX; i++) {
            RogueMoveSpawn(def->a, sora->x, sora->y, sora->z, ROGUE_MOVE_ORBIT, i * 256 / (def->b & 0x7F) + sOrbiters * 20, 0, def->b >> 7);
            sOrbiters++;
        }
        break;
    case GADGET_DO_SHARD:
        RogueMoveSpawn(def->a, sora->x, sora->y, sora->z - 0x3000, ROGUE_MOVE_SHARD, def->b, 0, 1);
        break;
    case GADGET_DO_VOLLEY:
        for (i = 0; i < def->b; i++) {
            RogueMoveSpawn(def->a, sora->x, sora->y, sora->z - 0x3000, ROGUE_MOVE_SHARD, 40 + i * 12, 0, 1);
        }
        break;
    case GADGET_DO_PACT:
        if (sora->unk_02C > 1) {
            sora->unk_02C--;
        }
        // And the buff.
    case GADGET_DO_WEIGHT:
        if (def->effect == GADGET_DO_WEIGHT) {
            sHaste = -20;
            sHasteTime = def->b * 6;
        }
        // And the buff.
    case GADGET_DO_BUFF:
        // The stronger of what is on and what comes stays, for the longer time.
        if (sBuffTime == 0 || def->a >= sBuff) {
            sBuff = def->a;
        }

        if (sBuffTime < def->b * 6) {
            sBuffTime = def->b * 6;
        }
        break;
    case GADGET_DO_HASTE:
        sHaste = def->a;
        sHasteTime = def->b * 6;
        break;
    case GADGET_DO_RELOAD:
        sReload = def->a;
        sReloadTime = def->b * 6;
        break;
    case GADGET_DO_VALUE:
        if (sValue < def->a) {
            sValue = def->a;
        }
        break;
    case GADGET_DO_HURT:
        if (sora->unk_02C > def->a) {
            sora->unk_02C -= def->a;
        }
        break;
    case GADGET_DO_SHARDS:
        if (gRogue.shards < 9999 - def->a) {
            gRogue.shards += def->a;
        }
        break;
    case GADGET_DO_STOP_ALL:
        for (enemy = (BtlObj*)ListPoolFirst(&gBtlWork->pool); enemy != 0; enemy = (BtlObj*)ListPoolNext(&enemy->node)) {
            if (enemy != sora && enemy->unk_02C > 0) {
                RogueApplyFreeze(enemy);
            }
        }
        break;
    case GADGET_DO_SHIELD:
        sShieldTime = def->a * 6;
        break;
    case GADGET_DO_BOLT:
        enemy = RogueGadgetEnemy(owed->target, def->a);

        if (enemy != 0) {
            RogueThunderBolt(enemy);
        }
        break;
    case GADGET_DO_AT_TARGET:
        enemy = RogueGadgetEnemy(owed->target, 0);

        if (enemy != 0) {
            RogueMoveSpawn(def->a, enemy->x, enemy->y, enemy->z, ROGUE_MOVE_PLAIN, 0, 0, def->b);
        }
        break;
    case GADGET_DO_AT_SORA:
        RogueMoveSpawn(def->a, sora->x, sora->y, sora->z, ROGUE_MOVE_PLAIN, 0, 0, def->b);
        break;
    case GADGET_DO_AT_SPOT:
        RogueMoveSpawn(def->a, owed->x, owed->y, owed->z, ROGUE_MOVE_PLAIN, 0, 0, def->b);
        break;
    case GADGET_DO_CAST:
        RogueDoMove(def->a, sora);
        break;
    case GADGET_DO_RAIN:
        enemy = RogueGadgetEnemy(owed->target, 0);

        if (enemy != 0) {
            for (i = 0; i < def->b; i++) {
                RogueMoveSpawn(def->a, enemy->x + (i - def->b / 2) * 0x1800, enemy->y, enemy->z, ROGUE_MOVE_PLAIN, 0, i * 10, 0);
            }
        }
        break;
    case GADGET_DO_SHOCK:
        RogueShockwave(sora, def->a, def->b * 4);
        break;
    case GADGET_DO_HEAL:
        if (sora->unk_02C > 0) {
            sora->unk_02C += def->a;

            if (sora->unk_02C > sora->unk_02E) {
                sora->unk_02C = sora->unk_02E;
            }
        }
        break;
    }

    gRogueDebug.gadgets++;
}

// Notes one gadget's effect as owed. Those already owed push it back, so
// that what goes off together comes one after the other.
static void RogueGadgetOwe(u8 gadget, BtlObj* target) {
    BtlObj* sora = gBtlWork->actor;
    s32 i;
    s32 free = -1;
    u8 delay = RogueGadgetEntry(gadget)->delay + 1;

    for (i = 0; i < GADGET_QUEUE; i++) {
        if (sOwed[i].gadget == 0) {
            if (free < 0) {
                free = i;
            }
        } else {
            if (sOwed[i].gadget == gadget + 1) {
                return; // once at a time
            }

            delay += 6;
        }
    }

    if (free < 0) {
        return;
    }

    gRogueDebug.gadgetOwed++;
    sOwed[free].gadget = gadget + 1;
    sOwed[free].delay = delay;
    sOwed[free].target = target;
    sOwed[free].x = target != 0 ? target->x : sora->x;
    sOwed[free].y = target != 0 ? target->y : sora->y;
    sOwed[free].z = target != 0 ? target->z : sora->z;
}

// Something happened: every gadget of the run that waits for it goes off.
// `target` is the enemy it happened to, if any.
void RogueGadgetFire(u8 trigger, BtlObj* target) {
    u8 gadget;

    if (gBtlWork == 0 || gBtlWork->actor == 0 || trigger >= GADGET_TRIGGERS) {
        return;
    }

    if (trigger == GADGET_ON_DODGE) {
        sCounts[GADGET_ON_DODGE_STEP] = 0;
    }

    sCounts[trigger]++;
    gRogueDebug.gadgetTriggers[trigger] = sCounts[trigger];

    for (gadget = 0; gadget < ROGUE_GADGETS + ROGUE_FUSIONS; gadget++) {
        const RogueGadgetDef* def = RogueGadgetEntry(gadget);

        if (def->trigger != trigger || !RogueGadgetOwned(gadget)) {
            continue;
        }

        switch (trigger) {
        case GADGET_ON_HIT_N:
            if (gRogue.combo == 0 || gRogue.combo % def->number != 0) {
                continue;
            }
            break;
        case GADGET_ON_CARD_N:
        case GADGET_ON_DODGE_STEP:
        case GADGET_ON_ROTATE:
        case GADGET_ON_LOCK:
        case GADGET_ON_AIR_HIT:
        case GADGET_ON_ENEMY_CARD:
        case GADGET_ON_SPELL:
        case GADGET_ON_ATTACK_CARD:
        case GADGET_ON_PRIZE:
            // Every so many times.
            if (def->number > 1 && sCounts[trigger] % def->number != 0) {
                continue;
            }
            break;
        }

        RogueGadgetOwe(gadget, target);
    }
}

// A string of hits ran out.
void RogueGadgetComboEnd(u16 hits) {
    u8 gadget;

    for (gadget = 0; gadget < ROGUE_GADGETS + ROGUE_FUSIONS; gadget++) {
        const RogueGadgetDef* def = RogueGadgetEntry(gadget);

        if (def->trigger == GADGET_ON_COMBO_END && hits >= def->number && RogueGadgetOwned(gadget)) {
            RogueGadgetOwe(gadget, 0);
        }
    }
}

// What is on for a while, asked by the battle code.
s32 RogueGadgetDamage(s32 damage) {
    if (sBuffTime != 0) {
        damage += damage * sBuff / 100;
    }

    return damage;
}

s32 RogueGadgetRunSpeed(s32 speed) {
    speed = RogueHeroRunSpeed(speed);

    if (sHasteTime != 0) {
        speed += speed * sHaste / 100;
    }

    return speed;
}

u8 RogueGadgetReloadRate(u8 rate) {
    s32 faster = rate;

    if (sReloadTime != 0) {
        faster += faster * sReload / 100;
    }

    return faster > 255 ? 255 : faster;
}

// Called as a card is played: the worth lent to it is spent.
void RogueGadgetCardPlayed(void) {
    sValue = 0;
}

// The next card played is worth more, once.
u8 RogueGadgetCardValue(u8 value) {
    if (sValue != 0 && value != 0) {
        value += sValue;

        if (value > 9) {
            value = 9;
        }
    }

    return value;
}

u8 RogueGadgetShielded(void) {
    return sShieldTime != 0;
}

// Called once a frame in battle.
void RogueGadgetTick(void) {
    BtlObj* sora = gBtlWork->actor;
    u8 gadget;
    u8 airborne;
    u8 moving;
    s32 i;

    if (sora == 0) {
        return;
    }

    if (!sStarted) {
        sStarted = 1;
        RogueGadgetFire(GADGET_ON_START, 0);
    }

    if (sBuffTime != 0) {
        sBuffTime--;
    }

    if (sHasteTime != 0) {
        sHasteTime--;
    }

    if (sReloadTime != 0) {
        sReloadTime--;
    }

    if (sShieldTime != 0) {
        sShieldTime--;
    }

    airborne = sora->z < sora->unk_010;
    // On the move: more than a nudge since the last frame.
    moving = sora->x - sLastX > 0x60 || sLastX - sora->x > 0x60 || sora->y - sLastY > 0x60 || sLastY - sora->y > 0x60;
    sLastX = sora->x;
    sLastY = sora->y;

    if (airborne) {
        gRogueDebug.airFrames++;
    } else if (!moving) {
        gRogueDebug.stillFrames++;
    }

    // A new enemy locked on.
    if (gBtlWork->actor2 != 0 && gBtlWork->actor2 != sLocked) {
        RogueGadgetFire(GADGET_ON_LOCK, gBtlWork->actor2);
    }

    sLocked = gBtlWork->actor2;

    // The ones on a clock: each runs while its condition holds and starts
    // over when it does not.
    for (gadget = 0; gadget < ROGUE_GADGETS + ROGUE_FUSIONS; gadget++) {
        const RogueGadgetDef* def = RogueGadgetEntry(gadget);
        u8 holds;

        switch (def->trigger) {
        case GADGET_ON_TIMER:
            holds = 1;
            break;
        case GADGET_ON_LOW_HP:
            holds = sora->unk_02C * 4 <= sora->unk_02E;
            break;
        case GADGET_ON_IDLE:
            holds = !moving && !airborne;
            break;
        case GADGET_ON_RUN:
            holds = moving && !airborne;
            break;
        case GADGET_ON_AIRTIME:
            holds = airborne;
            break;
        case GADGET_ON_UNHURT:
            holds = 1; // started over by a hit, see RogueGadgetFire's callers
            break;
        case GADGET_ON_FULL_HP:
            holds = sora->unk_02C >= sora->unk_02E;
            break;
        default:
            continue;
        }

        if (!RogueGadgetOwned(gadget)) {
            continue;
        }

        if (!holds || (def->trigger == GADGET_ON_UNHURT && sCounts[GADGET_ON_HURT] != sHurtSeen)) {
            sTimers[gadget] = 0;
            continue;
        }

        if (++sTimers[gadget] >= def->number * 6) {
            sTimers[gadget] = 0;

            // Nothing is thrown at an empty room.
            if (RogueGadgetEnemy(0, 0) != 0 || def->effect >= GADGET_DO_HEAL) {
                RogueGadgetOwe(gadget, 0);
            }
        }
    }

    sHurtSeen = sCounts[GADGET_ON_HURT];

    // Landing: he was in the air and now stands.

    if (sWasAirborne && !airborne) {
        RogueGadgetFire(GADGET_ON_LAND, 0);
    }

    sWasAirborne = airborne;

    for (i = 0; i < GADGET_QUEUE; i++) {
        if (sOwed[i].gadget != 0 && --sOwed[i].delay == 0) {
            RogueGadgetDo(RogueGadgetEntry(sOwed[i].gadget - 1), &sOwed[i]);
            sOwed[i].gadget = 0;
        }
    }
}
