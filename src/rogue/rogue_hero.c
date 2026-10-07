#include "rogue.h"
#include "battle.h"
#include "battle_actor.h"
#include "btl.h"

// What each hero does that Sora does not. The heroes drawn from a sheet
// share his animations and his cards, so the difference is made here: how
// fast they are, how hard they hit, and what their swings set off.
//
//   Mickey     small and quick: he runs a quarter faster, has one more jump
//              in the air and hits a little softer; his finisher lets three
//              pearls of light go, each after an enemy.
//   Sora II    throws the Keyblade: a swing at an enemy out of reach becomes
//              a throw, and the finisher is a Strike Raid, which goes through
//              what it meets and comes back.
//   Roxas      two Keyblades: every hit lands a second time a moment later,
//              and the finisher raises pillars of light; he is hurt a little
//              more than Sora is.
//   Riku       has the game's own way of fighting, see RogueApplyHero.

#define ROXAS_ECHO_DELAY 7 // frames between a hit of Roxas's and its second
#define ROXAS_ECHOES 4 // waiting at once
#define RAID_REACH 0x3400 // further than this, Sora II throws instead of swinging at the air

typedef struct RogueEcho {
    BtlObj* target;
    s16 amount;
    u8 timer;
} RogueEcho;

static RogueEcho sEchoes[ROXAS_ECHOES];

void RogueHeroReset(void) {
    s32 i;

    for (i = 0; i < ROXAS_ECHOES; i++) {
        sEchoes[i].timer = 0;
    }
}

s32 RogueHeroRunSpeed(s32 speed) {
    return gRogueMeta.hero == ROGUE_HERO_MICKEY ? speed + speed / 4 : speed;
}

u8 RogueHeroAirJumps(void) {
    return gRogueMeta.hero == ROGUE_HERO_MICKEY;
}

// The damage of one of the hero's hits.
s16 RogueHeroDamage(s16 amount) {
    if (gRogueMeta.hero == ROGUE_HERO_MICKEY && amount > 1) {
        amount -= amount * 15 / 100;
    }

    return amount;
}

// The damage the hero takes.
s16 RogueHeroHurt(s16 amount) {
    if (gRogueMeta.hero == ROGUE_HERO_ROXAS && amount > 0) {
        amount += (amount + 9) / 10;
    }

    return amount;
}

// Called for each plain hit of the hero's, with its damage settled.
void RogueHeroOnHit(BtlObj* target) {
    s32 i;

    if (gRogueMeta.hero != ROGUE_HERO_ROXAS || target->unk_020 <= 1) {
        return;
    }

    for (i = 0; i < ROXAS_ECHOES; i++) {
        if (sEchoes[i].timer == 0) {
            sEchoes[i].target = target;
            sEchoes[i].amount = target->unk_020 * 2 / 5;
            sEchoes[i].timer = ROXAS_ECHO_DELAY;
            return;
        }
    }
}

// Called on the hit frame of each swing of a combo.
void RogueHeroOnSwing(BtlObj* sora, u8 finisher) {
    BtlObj* target = gBtlWork->actor2 != 0 ? gBtlWork->actor2 : RogueGaugeTarget();
    s32 left = (sora->flags & 4) != 0;
    s32 i;
    s32 dx;

    switch (gRogueMeta.hero) {
    case ROGUE_HERO_MICKEY:
        if (finisher) {
            for (i = 0; i < 3; i++) {
                RogueMoveSpawn(ROGUE_MOVE_PEARL, sora->x, sora->y, sora->z - 0x2000, ROGUE_MOVE_SHARD, 6 + i * 6, i * 3, 0);
            }

            gRogueDebug.heroMoves++;
        }
        break;
    case ROGUE_HERO_SORA_KH2:
        if (finisher) {
            RogueDoMove(ROGUE_MOVE_RAID, sora);
            gRogueDebug.heroMoves++;
        } else if (target != 0) {
            dx = target->x - sora->x;

            if (dx > RAID_REACH || dx < -RAID_REACH) {
                RogueMoveSpawn(ROGUE_MOVE_RAID, sora->x + (left ? -0x1800 : 0x1800), sora->y, sora->z - 0x1400, ROGUE_MOVE_PLAIN, 0, 0, 0);
                gRogueDebug.heroMoves++;
            }
        }
        break;
    case ROGUE_HERO_ROXAS:
        if (finisher) {
            // One where the enemy stands, or in front of him, and one further on.
            s32 x = target != 0 ? target->x : sora->x + (left ? -0x2800 : 0x2800);
            s32 y = target != 0 ? target->y : sora->y;

            RogueMoveSpawn(ROGUE_MOVE_PILLAR, x, y, sora->unk_010, ROGUE_MOVE_PLAIN, 0, 0, 0);
            RogueMoveSpawn(ROGUE_MOVE_PILLAR, x + (left ? -0x2400 : 0x2400), y, sora->unk_010, ROGUE_MOVE_PLAIN, 0, 8, 0);
            gRogueDebug.heroMoves++;
        }
        break;
    }
}

// Called once a frame in battle.
void RogueHeroTick(void) {
    s32 i;

    for (i = 0; i < ROXAS_ECHOES; i++) {
        if (sEchoes[i].timer != 0 && --sEchoes[i].timer == 0) {
            RogueDirectDamage(sEchoes[i].target, sEchoes[i].amount);
            gRogueDebug.heroMoves++;
        }
    }
}
