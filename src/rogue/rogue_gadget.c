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
    GADGET_DO_HEAL // a: HP
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
static u16 sTimers[ROGUE_GADGETS];
static u16 sCards; // cards played this battle
static u16 sDodgeSteps;
static u8 sStarted;
static u8 sWasAirborne;

void RogueGadgetReset(void) {
    s32 i;

    for (i = 0; i < GADGET_QUEUE; i++) {
        sOwed[i].gadget = 0;
    }

    for (i = 0; i < ROGUE_GADGETS; i++) {
        sTimers[i] = 0;
    }

    sCards = 0;
    sDodgeSteps = 0;
    sStarted = 0;
    sWasAirborne = 0;
}

static u8 RogueGadgetOwned(u8 gadget) {
    return RogueHasRelic(ROGUE_RELIC_FIRST_GADGET + gadget);
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
        for (i = 0; i < def->b; i++) {
            RogueMoveSpawn(def->a, sora->x, sora->y, sora->z, ROGUE_MOVE_ORBIT, i * 256 / def->b, 0, 0);
        }
        break;
    case GADGET_DO_SHARD:
        RogueMoveSpawn(def->a, sora->x, sora->y, sora->z - 0x3000, ROGUE_MOVE_SHARD, def->b, 0, 1);
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
    u8 delay = sGadgets[gadget].delay + 1;

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

    if (gBtlWork == 0 || gBtlWork->actor == 0) {
        return;
    }

    if (trigger == GADGET_ON_ZERO || trigger == GADGET_ON_CARD_N) {
        if (trigger == GADGET_ON_CARD_N) {
            sCards++;
        }
    }

    if (trigger == GADGET_ON_DODGE) {
        sDodgeSteps = 0;
    }

    if (trigger == GADGET_ON_DODGE_STEP) {
        sDodgeSteps++;
    }

    for (gadget = 0; gadget < ROGUE_GADGETS; gadget++) {
        const RogueGadgetDef* def = &sGadgets[gadget];

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
            if (sCards % def->number != 0) {
                continue;
            }
            break;
        case GADGET_ON_DODGE_STEP:
            if (sDodgeSteps % def->number != 0) {
                continue;
            }
            break;
        }

        RogueGadgetOwe(gadget, target);
    }
}

// Called once a frame in battle.
void RogueGadgetTick(void) {
    BtlObj* sora = gBtlWork->actor;
    u8 gadget;
    u8 airborne;
    s32 i;

    if (sora == 0) {
        return;
    }

    if (!sStarted) {
        sStarted = 1;
        RogueGadgetFire(GADGET_ON_START, 0);
    }

    // The ones on a clock, and the ones that run while Sora is nearly out.
    for (gadget = 0; gadget < ROGUE_GADGETS; gadget++) {
        const RogueGadgetDef* def = &sGadgets[gadget];

        if ((def->trigger != GADGET_ON_TIMER && def->trigger != GADGET_ON_LOW_HP) || !RogueGadgetOwned(gadget)) {
            continue;
        }

        if (def->trigger == GADGET_ON_LOW_HP && sora->unk_02C * 4 > sora->unk_02E) {
            sTimers[gadget] = 0;
            continue;
        }

        if (++sTimers[gadget] >= def->number * 6) {
            sTimers[gadget] = 0;

            // Nothing is thrown at an empty room.
            if (RogueGadgetEnemy(0, 0) != 0 || def->effect == GADGET_DO_HEAL) {
                RogueGadgetOwe(gadget, 0);
            }
        }
    }

    // Landing: he was in the air and now stands.
    airborne = sora->z < sora->unk_010;

    if (sWasAirborne && !airborne) {
        RogueGadgetFire(GADGET_ON_LAND, 0);
    }

    sWasAirborne = airborne;

    for (i = 0; i < GADGET_QUEUE; i++) {
        if (sOwed[i].gadget != 0 && --sOwed[i].delay == 0) {
            RogueGadgetDo(&sGadgets[sOwed[i].gadget - 1], &sOwed[i]);
            sOwed[i].gadget = 0;
        }
    }
}
