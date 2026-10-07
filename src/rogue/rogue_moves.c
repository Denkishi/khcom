#include "rogue.h"
#include "anim.h"
#include "battle.h"
#include "battle_actor.h"
#include "btl.h"
#include "engine_math.h"
#include "gba/keys.h"
#include "listpool.h"
#include "btl_collision.h"
#include "fade.h"
#include "m4a_song.h"
#include "obj_api.h"
#include "sprite.h"
#include "sprite_palettes.h"
#include "sprites_hum.h"
#include "system_state.h"
#include "taskpool.h"
#include "rogue_actor_art.h"

// Moves built from the effect sprites of other characters. The effects are
// already in the game and only their owners use them; here each becomes
// something Sora does, with one of the existing attack definitions for its
// hit. A move goes off on a combo finisher if the run has its relic, or with
// a card whose kind it has been bound to.

enum {
    MOTION_THROWN, // flies ahead of Sora, hitting what it meets
    MOTION_AHEAD, // appears in front of Sora and hits around itself
    MOTION_AROUND, // appears on Sora and hits all around him
    MOTION_PULL // appears in front of Sora and draws the enemies to itself
};

typedef struct RogueMoveDef {
    void* tiles;
    u16 tilesSize; // of the whole sheet, loaded at once
    u16 block; // or, for a big sheet, the tile block its frames are loaded into one at a time
    void* palette;
    void* anims;
    void* frames;
    u8 anim;
    u8 motion;
    u8 count; // how many are thrown; for the others, how many times in a row it hits
    u8 frames_; // frames it lasts
    u8 hitFrame; // for the ones that do not fly: the frame the first hit lands on
    u8 launch; // its hits send enemies up, as a combo finisher does
    u16 attack; // attack definition of the hit
    u16 scale; // 8.8, of that attack's damage
    u8 width; // of the hit box, in pixels
    u8 depth;
    u8 height;
    u16 sound;
    u8 back; // a thrown one goes through what it hits and, at the end of its flight, comes back
} RogueMoveDef;

#define SHEET(name) name##Tiles, sizeof(name##Tiles), 0
#define BLOCK(name, size) name##Tiles, 0, size

// The attacks used: 14 is a keyblade finisher (256 a swing), 303 one of
// Axel's fire attacks (512), 313 one of Vexen's ice ones (256) and 0x133
// Larxene's thunder knife.
static const RogueMoveDef sMoves[ROGUE_MOVE_ALL] = {
    // Axel's chakram: thrown ahead, burning what it crosses.
    { SHEET(gAcceleBtWep), gAccelePalette, gAcceleBtWepAnims, gAcceleBtWepFrames, 0, MOTION_THROWN, 1, 40, 0, 0, 303, 128, 12, 12, 12,
      SONG_EF_RAC_3TR },
    // Vexen's needles: three thrown ahead.
    { SHEET(gVixenE1), gVixEPalette, gVixenE1Anims, gVixenE1Frames, 0, MOTION_THROWN, 3, 36, 0, 0, 313, 192, 6, 8, 6, SONG_EF_RAC_3TR },
    // Marluxia's petals: a burst around Sora.
    { SHEET(gMaruxhaBtEff1), gMaruxhaBtEffPalette, gMaruxhaBtEff1Anims, gMaruxhaBtEff1Frames, 0, MOTION_AROUND, 1, 36, 8, 0, 14, 384,
      56, 36, 56, SONG_EF_SUMMON_UP },
    // Vexen's ice shards: a blast in front of Sora.
    { SHEET(gVixenReitouHahen), gVixEPalette, gVixenReitouHahenAnims, gVixenReitouHahenFrames, 0, MOTION_AHEAD, 1, 30, 4, 0, 313, 320,
      36, 24, 44, SONG_EF_RAC_3TR },
    // Hades's fireball: thrown ahead, slow and heavy.
    { BLOCK(gHadesFigaballBall, 75 * 32), gBStatesPalette, gHadesFigaballBallAnims, gHadesFigaballBallFrames, 1, MOTION_THROWN, 1, 44,
      0, 0, 303, 224, 20, 16, 20, SONG_EF_RAC_3TR },
    // Hades's fire: a burst in front of Sora that hits twice.
    { BLOCK(gHadesFigaballBall, 75 * 32), gBStatesPalette, gHadesFigaballBallAnims, gHadesFigaballBallFrames, 0, MOTION_AHEAD, 2, 30,
      4, 0, 303, 160, 40, 24, 40, SONG_EF_RAC_3TR },
    // Lexaeus's rock: rises in front of Sora and sends what it hits flying.
    { BLOCK(gRexeusRock01, 0xDC0), gRexeusRock01Palette, gRexeusRock01Anims, gRexeusRock01Frames, 0, MOTION_AHEAD, 1, 34, 8, 1, 14, 448,
      44, 28, 56, SONG_EF_SUMMON_UP },
    // Hook's bomb: thrown ahead.
    { BLOCK(gPBakudan, 0x280), gPBakudanPalette, gPBakudanAnims, gPBakudanFrames, 0, MOTION_THROWN, 1, 36, 0, 0, 303, 192, 16, 14, 16,
      SONG_EF_RAC_3TR },
    // Water: a wave of ice-blue spray that hits three times as it stands.
    { SHEET(gVixenReitouHahen), gVixEPalette, gVixenReitouHahenAnims, gVixenReitouHahenFrames, 0, MOTION_AHEAD, 3, 36, 4, 0, 14, 200, 44,
      28, 44, SONG_EF_RAC_3TR },
    // Wind: a whirl around Sora that hits three times and lifts.
    { SHEET(gMaruxhaBtEff1), gMaruxhaBtEffPalette, gMaruxhaBtEff1Anims, gMaruxhaBtEff1Frames, 0, MOTION_AROUND, 3, 40, 6, 1, 14, 150, 60,
      40, 60, SONG_EF_SUMMON_UP },
    // Magnet: draws every enemy to a point in front of Sora, then hits there.
    { SHEET(gMaruxhaBtEff1), gMaruxhaBtEffPalette, gMaruxhaBtEff1Anims, gMaruxhaBtEff1Frames, 0, MOTION_PULL, 1, ROGUE_MAGNET_FRAMES + 12,
      ROGUE_MAGNET_FRAMES, 0, 14, 256, 48, 32, 48, SONG_EF_SUMMON_UP },
    // Axel's wall of fire: it stands in front of Sora and burns four times.
    // (His own wall is drawn on the background: Hades's flames stand in for it.)
    { BLOCK(gHadesFigaballBall, 75 * 32), gBStatesPalette, gHadesFigaballBallAnims, gHadesFigaballBallFrames, 0, MOTION_AHEAD, 4, 44, 4, 0, 303,
      110, 40, 28, 48, SONG_EF_RAC_3TR },
    // Marluxia's scythe of petals: two thrown ahead.
    { SHEET(gMaruxhaBtEff2), gMaruxhaBtEffPalette, gMaruxhaBtEff2Anims, gMaruxhaBtEff2Frames, 0, MOTION_THROWN, 2, 36, 0, 0, 14, 220,
      14, 12, 14, SONG_EF_RAC_3TR },
    // Sephiroth's cut that flies along the ground.
    { (void*)gRogueFxWaveTiles, sizeof(gRogueFxWaveTiles), 0, (void*)gRogueFxWavePalette, (void*)gRogueFxWaveAnims, (void*)gRogueFxWaveFrames, 0, MOTION_THROWN, 1, 50, 0, 0,
      14, 320, 10, 14, 28, SONG_EF_RAC_3TR },
    // The Keyblade thrown: it goes through what it meets and comes back.
    { (void*)gRogueFxRaidTiles, sizeof(gRogueFxRaidTiles), 0, (void*)gRogueFxRaidPalette, (void*)gRogueFxRaidAnims, (void*)gRogueFxRaidFrames,
      0, MOTION_THROWN, 1, 22, 0, 0, 14, 300, 14, 14, 16, SONG_EF_RAC_3TR, 1 },
    // A ball of light.
    { (void*)gRogueFxPearlTiles, sizeof(gRogueFxPearlTiles), 0, (void*)gRogueFxPearlPalette, (void*)gRogueFxPearlAnims,
      (void*)gRogueFxPearlFrames, 0, MOTION_THROWN, 1, 40, 0, 0, 14, 200, 10, 10, 12, SONG_EF_RAC_3TR },
    // Roxas's pillar of light: it rises under what is in front and sends it up.
    { (void*)gRogueFxPillarTiles, sizeof(gRogueFxPillarTiles), 0, (void*)gRogueFxPillarPalette, (void*)gRogueFxPillarAnims,
      (void*)gRogueFxPillarFrames, 0, MOTION_AHEAD, 1, 30, 4, 1, 14, 300, 18, 16, 60, SONG_EF_SUMMON_UP },
};

typedef struct RogueMoveArgs {
    const RogueMoveDef* def;
    s32 x;
    s32 y;
    s32 z;
    s32 vy; // sideways speed of a thrown one, for the fan
    u8 left;
    u8 delay; // frames before it appears
    u8 mode; // a RogueMoveMode
    u8 phase; // see RogueMoveMode
    u8 freeze; // its hits freeze
    BtlObj* foe; // the boss who made it, when it is one of theirs: then it is Sora it hits
} RogueMoveArgs;

typedef struct RogueMoveWork {
    RogueMoveArgs args;
    void* tiles;
    void* palette;
    AnimState anim;
    u8 timer;
    u8 hits; // made so far, for the ones that hit more than once
    u8 shown;
    u8 rest; // frames until an orbiting one can hit again
    u16 turn; // how far round Sora an orbiting one is, in 1/65536
} RogueMoveWork;

static void RogueMove_Init(RogueMoveWork* w, RogueMoveArgs* args) {
    w->args = *args;
    w->timer = 0;
    w->hits = 0;
    w->shown = 0;
    w->rest = 0;
    w->turn = args->phase << 8;
    w->tiles = 0;
    w->palette = 0;
}

// The sprite is loaded when the move appears: a delayed one holds no tiles
// while it waits.
static s32 RogueMoveShow(RogueMoveWork* w) {
    const RogueMoveDef* def = w->args.def;
    u16 tiles = (def->block != 0 ? def->block : def->tilesSize) / 32;

    if (!CanAllocObjTiles(tiles) || !CanAllocObjPalette(1)) {
        return 0;
    }

    w->palette = LoadObjPalette(def->palette, 0x20);
    w->tiles = def->block != 0 ? (void*)AllocObjTiles(def->block, def->tiles) : (void*)LoadObjTiles(def->tiles, def->tilesSize);
    AnimInit(&w->anim, def->anims, def->frames);
    AnimStart(&w->anim, def->anim, def->motion == MOTION_THROWN || w->args.mode != ROGUE_MOVE_PLAIN);
    w->shown = 1;
    return 1;
}

// The attack a move hits with: its own, or with the prism the one of the
// element the deck is built on.
static u16 RogueMoveAttack(const RogueMoveDef* def) {
    static const u16 elements[ROGUE_ELEMENTS] = { 303, 313, 0x133 };
    u8 element;

    if (RogueHasRelic(ROGUE_RELIC_MOD_PRISM)) {
        element = RogueBuildElement();

        if (element != ROGUE_ELEMENT_NONE) {
            return elements[element];
        }
    }

    return def->attack;
}

// Tests the move's hit box as a hit of Sora's. Whom a hitbox hurts follows
// whose card is in play, so the player's turn is claimed for the test.
static s32 RogueMoveHit(RogueMoveWork* w) {
    const RogueMoveDef* def = w->args.def;
    u64 flags = gBtlWork->flags;
    s32 scale = gBtlWork->unk_124;
    s32 damage = def->scale;
    s32 width = def->width;
    s32 depth = def->depth;
    s32 height = def->height;
    s32 hit;

    if (w->args.foe != 0) {
        return RogueFoeHit(w->args.foe, w->args.x, w->args.y, w->args.z, width, depth, height, 256);
    }

    damage += damage * RogueUpgradeLevel(ROGUE_UPGRADE_MOVES) * 15 / 100;
    damage = Rogue2dScale(damage);

    if (RogueHasRelic(ROGUE_RELIC_MOD_GIANT)) {
        damage += damage / 2;
        width += width / 2;
        depth += depth / 2;
        height += height / 2;
    }

    gBtlWork->flags |= 0x20000000;
    gBtlWork->unk_124 = damage;
    gRogue.projectile = 1;
    gRogue.echoing = 1;
    gRogue.finisher = def->launch;
    gRogue.freezing = w->args.freeze;
    hit = func_08011F78(RogueMoveAttack(def), w->args.x, w->args.y, w->args.z, width, depth, height);
    gRogue.freezing = 0;
    gRogue.finisher = 0;
    gRogue.echoing = 0;
    gRogue.projectile = 0;
    gBtlWork->unk_124 = scale;
    gBtlWork->flags = (gBtlWork->flags & ~0x20000000ULL) | (flags & 0x20000000);

    if (hit) {
        gRogueDebug.moveHits++;
    }

    return hit;
}

// Draws every enemy a step nearer to the move.
static void RogueMovePull(RogueMoveWork* w) {
    BtlObj* sora = gBtlWork->actor;
    BtlObj* actor;

    for (actor = (BtlObj*)ListPoolFirst(&gBtlWork->pool); actor != 0; actor = (BtlObj*)ListPoolNext(&actor->node)) {
        if (actor != sora) {
            actor->x += (w->args.x - actor->x) / 6;
            actor->y += (w->args.y - actor->y) / 6;
            gRogueDebug.pulled++;
        }
    }
}

static s32 RogueMove_Update(RogueMoveWork* w) {
    const RogueMoveDef* def = w->args.def;
    BtlObj* target;

    if (w->args.delay != 0) {
        w->args.delay--;
        return 1;
    }

    if (!w->shown && !RogueMoveShow(w)) {
        return 0;
    }

    if (w->args.mode == ROGUE_MOVE_CIRCLE && ++w->timer > 240) {
        return 0;
    }

    if (w->args.mode == ROGUE_MOVE_ORBIT || w->args.mode == ROGUE_MOVE_CIRCLE) {
        // Round Sora for as long as the battle lasts; what it touches is hit,
        // and then left alone for a moment.
        BtlObj* sora = gBtlWork->actor;

        w->turn += 0x380;
        w->args.x = sora->x + gSineTable[w->turn >> 8] * 0x28;
        w->args.y = sora->y - gSineTable[(w->turn >> 8) + 64] * 0x12;
        w->args.z = sora->z - 0x1000;
        w->args.left = (w->turn >> 8) >= 128;

        if (w->rest != 0) {
            w->rest--;
        } else if (RogueMoveHit(w)) {
            w->rest = 30;
        }

        AnimUpdate(&w->anim);
        return 1;
    }

    if (w->args.mode == ROGUE_MOVE_SHARD) {
        BtlObj* sora = gBtlWork->actor;

        AnimUpdate(&w->anim);

        if (w->timer < w->args.phase) {
            // It forms over Sora's head and waits there; a boss's waits where it was set.
            if (w->args.foe == 0) {
                w->args.x = sora->x;
                w->args.y = sora->y;
                w->args.z = sora->z - 0x3000;
            }

            w->timer++;
            return 1;
        }

        // Then it goes for the enemy locked on, or any; a boss's goes for Sora.
        if (w->args.foe != 0) {
            target = sora;
        } else {
            target = gBtlWork->actor2 != 0 ? gBtlWork->actor2 : RogueGaugeTarget();
        }

        if (target == 0 || ++w->timer > w->args.phase + 90) {
            return 0;
        }

        w->args.left = target->x < w->args.x;
        w->args.x += (target->x - w->args.x) / 6;
        w->args.y += (target->y - w->args.y) / 6;
        w->args.z += (target->z - 0x1000 - w->args.z) / 6;
        return !RogueMoveHit(w);
    }

    switch (def->motion) {
    case MOTION_THROWN:
        if (def->back) {
            // It goes through, hitting again only after a moment.
            if (w->rest != 0) {
                w->rest--;
            } else if (RogueMoveHit(w)) {
                w->rest = 14;
            }
        } else if (RogueMoveHit(w) && (w->args.foe != 0 || !RogueHasRelic(ROGUE_RELIC_PIERCE))) {
            // It stops at what it hits, or with the bounce turns back once.
            if (w->args.foe != 0 || !RogueHasRelic(ROGUE_RELIC_BOUNCE) || w->hits != 0) {
                return 0;
            }

            w->hits = 1;
            w->args.left ^= 1;
            w->timer = 0;
        }

        // At the end of its flight the bounce sends it back too.
        if (w->timer + 1 >= def->frames_ && w->hits == 0 && (def->back || (w->args.foe == 0 && RogueHasRelic(ROGUE_RELIC_BOUNCE)))) {
            w->hits = 1;
            w->args.left ^= 1;
            w->timer = 0;
        }

        w->args.x += w->args.left ? -ROGUE_MOVE_SPEED : ROGUE_MOVE_SPEED;
        w->args.y += w->args.vy;
        target = gBtlWork->actor2;

        // The hound: it drifts across to the enemy locked on.
        if (w->args.foe == 0 && RogueHasRelic(ROGUE_RELIC_MOD_HOMING) && target != 0) {
            if (target->y > w->args.y + 0x200) {
                w->args.y += 0x200;
            } else if (target->y < w->args.y - 0x200) {
                w->args.y -= 0x200;
            }
        }
        break;
    case MOTION_PULL:
        if (w->timer < def->hitFrame) {
            RogueMovePull(w);
        } else if (w->timer == def->hitFrame) {
            RogueMoveHit(w);
        }
        break;
    default:
        // One hit, or several eight frames apart.
        if (w->hits < def->count && w->timer == def->hitFrame + w->hits * 8) {
            RogueMoveHit(w);
            w->hits++;
        }
        break;
    }

    AnimUpdate(&w->anim);
    return ++w->timer < def->frames_;
}

static void RogueMove_Draw(RogueMoveWork* w) {
    u16 attr = GetBattleSpritePriorityFlags(w->args.y);
    s16 x;
    s16 y;

    if (!w->shown) {
        return;
    }

    if (!w->args.left) {
        attr |= 1;
    }

    WorldToScreen(&x, &y, w->args.x, w->args.y, w->args.z);
    DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, attr, -0x1004 - (w->args.y >> 8) * 4);
}

static void RogueMove_Destroy(RogueMoveWork* w) {
    if (w->shown) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
    }
}

static TaskDesc sTaskDescRogueMove = {
    "task_rogue_move",
    (TaskInitFunc)RogueMove_Init,
    (TaskUpdateFunc)RogueMove_Update,
    (TaskDrawFunc)RogueMove_Draw,
    (TaskDestroyFunc)RogueMove_Destroy,
    sizeof(RogueMoveWork),
};

static void RogueAfterTick(void);
static void RogueStyleTick(void);

// Sora's casting pose, for a move made while he is free: in the middle of a
// swing or a spell he is already moving. The states are standing, running and
// the parts of a jump, each with its twin for when cards are locked.
void RogueSoraPose(BtlObj* sora) {
    BtlSoraWork* work = (BtlSoraWork*)((u8*)sora - (u32) & ((BtlSoraWork*)0)->actor);
    u32 state = work->unk_038;

    if ((state >= 1 && state <= 4) || (state >= 18 && state <= 21)) {
        gRogue.pose = 0;
        SetBtlSoraAnimation(work, 42, 0);
        gRogue.pose = ROGUE_MOVE_POSE;
    }
}

static void RogueMoveCast(u8 move, BtlObj* sora, u8 again) {
    const RogueMoveDef* def = &sMoves[move];
    RogueMoveArgs args;
    s32 count = 1;
    s32 i;

    if (def->motion == MOTION_THROWN) {
        count = def->count;

        // A projectile build throws two more of whatever comes in numbers,
        // and the multiplier two more of anything.
        if (count > 1 && RogueBuildBonus(ROGUE_BUILD_PROJECTILE) != 0) {
            count += 2;
        }

        if (RogueHasRelic(ROGUE_RELIC_MOD_MULTI)) {
            count += 2;
        }
    } else if (def->motion != MOTION_PULL && RogueHasRelic(ROGUE_RELIC_MOD_MULTI)) {
        // Of the ones that stand, the multiplier sets three in a row.
        count = 3;
    }

    RogueSoraPose(sora);
    m4aSongNumStart(def->sound);
    args.def = def;
    args.left = (sora->flags & 4) != 0;
    args.foe = 0;

    for (i = 0; i < count; i++) {
        args.x = sora->x;
        args.y = sora->y;
        args.z = sora->z;
        args.vy = 0;
        args.delay = 0;
        args.mode = ROGUE_MOVE_PLAIN;
        args.phase = 0;
        args.freeze = 0;

        if (def->motion != MOTION_AROUND) {
            args.x += args.left ? -0x2000 : 0x2000;
        }

        if (def->motion == MOTION_THROWN) {
            args.y += (i - count / 2) * 0x0A00;
            args.z -= 0x1400;

            if (RogueHasRelic(ROGUE_RELIC_MOD_FAN)) {
                args.vy = (i - count / 2) * 0x180 + (count == 1 ? 0 : 0);
            }
        } else if (i != 0) {
            // The next of a row stands further on and comes a moment later.
            args.x += (args.left ? -0x2800 : 0x2800) * i;
            args.delay = i * 6;
        }

        TaskCreate(&gBtlWork->taskPools[0], &sTaskDescRogueMove, &args);
        gRogueDebug.moves++;
    }

    // The double throw: the same again in a moment, once.
    if (!again && RogueHasRelic(ROGUE_RELIC_MOD_ECHO)) {
        gRogue.moveEcho = move + 1;
        gRogue.moveEchoTimer = ROGUE_MOVE_ECHO_DELAY;
    }
}

// Sora does one of the moves.
void RogueDoMove(u8 move, BtlObj* sora) {
    RogueMoveCast(move, sora, 0);
}

// Called once a frame in battle: what the relics owe from earlier frames.
void RogueMovesTick(void) {
    RogueAfterTick();
    RogueStyleTick();
    RogueGadgetTick();
    RogueHeroTick();
    Rogue2dTick();

    if (gRogue.moveEchoTimer != 0 && --gRogue.moveEchoTimer == 0 && gRogue.moveEcho != 0) {
        RogueMoveCast(gRogue.moveEcho - 1, gBtlWork->actor, 1);
        gRogue.moveEcho = 0;
    }

    // The fast: whatever HP Sora gains in battle is taken back.
    if (RogueHasRelic(ROGUE_RELIC_NO_HEAL) && gBtlWork->actor != 0) {
        BtlObj* sora = gBtlWork->actor;

        if (gRogue.lastHp > 0 && sora->unk_02C > gRogue.lastHp) {
            sora->unk_02C = gRogue.lastHp;
        }

        gRogue.lastHp = sora->unk_02C;
    }

    if (gRogue.thorns) {
        gRogue.thorns = 0;
        RogueMoveCast(ROGUE_MOVE_PETALS, gBtlWork->actor, 1);
    }
}

// A blast all around Sora, with nothing drawn but a flash: what a creature
// too big to stand in for him does.
void RogueShockwave(BtlObj* sora, u8 element, u16 scale) {
    static const u16 attacks[4] = { 14, 303, 313, 0x133 };
    u64 flags = gBtlWork->flags;
    s32 old = gBtlWork->unk_124;

    RogueSoraPose(sora);
    m4aSongNumStart(SONG_EF_SUMMON_UP);
    FadeFromAmount(2, 12, 16);
    gBtlWork->flags |= 0x20000000;
    gBtlWork->unk_124 = scale;
    gRogue.projectile = 1;
    gRogue.echoing = 1;

    if (func_08011F78(attacks[element], sora->x, sora->y, sora->z, 120, 60, 80)) {
        gRogueDebug.moveHits++;
    }

    gRogue.echoing = 0;
    gRogue.projectile = 0;
    gBtlWork->unk_124 = old;
    gBtlWork->flags = (gBtlWork->flags & ~0x20000000ULL) | (flags & 0x20000000);
}

// A small blast around Sora, with nothing drawn: one hit of a move that hits all round him.
void RogueShockwaveSmall(BtlObj* sora, u16 scale) {
    u64 flags = gBtlWork->flags;
    s32 old = gBtlWork->unk_124;

    gBtlWork->flags |= 0x20000000;
    gBtlWork->unk_124 = scale;
    gRogue.projectile = 1;
    gRogue.echoing = 1;

    if (func_08011F78(14, sora->x, sora->y, sora->z - 0x1000, 34, 20, 36)) {
        gRogueDebug.moveHits++;
    }

    gRogue.echoing = 0;
    gRogue.projectile = 0;
    gBtlWork->unk_124 = old;
    gBtlWork->flags = (gBtlWork->flags & ~0x20000000ULL) | (flags & 0x20000000);
}

// The movement relics.

// Called every frame Sora is in the air.
void RogueAirControl(BtlSoraWork* work, u16 held, u16 pressed) {
    BtlObj* sora = &work->actor;

    // The glide: holding the jump button, he comes down slowly. Gravity is
    // added after this, so the speed is set short of it.
    if (RogueHasRelic(ROGUE_RELIC_GLIDE) && (held & B_BUTTON) && work->unk_150 > ROGUE_GLIDE_SPEED - gBtlWork->unk_12C) {
        work->unk_150 = ROGUE_GLIDE_SPEED - gBtlWork->unk_12C;
    }

    // The air dash: a second tap of left or right, as the dodge on the
    // ground, once until he lands. It goes through the knockback speed, which
    // nothing in the air overwrites.
    if (RogueHasRelic(ROGUE_RELIC_AIR_DASH) && !gRogue.airDashUsed) {
        if ((pressed & DPAD_LEFT) && work->unk_170[0] != 0) {
            sora->vx = -ROGUE_AIR_DASH_SPEED;
            sora->flags |= 4;
        } else if ((pressed & DPAD_RIGHT) && work->unk_170[1] != 0) {
            sora->vx = ROGUE_AIR_DASH_SPEED;
            sora->flags &= ~4;
        } else {
            return;
        }

        gRogue.airDashUsed = 1;
        work->unk_150 = -200;
        m4aSongNumStart(SONG_EF_RAC_3TR);
        gRogueDebug.airDashes++;
    }
}

// Called as a dodge takes off: with the shadow step and an enemy locked on,
// Sora comes out of it behind that enemy, facing it.
void RogueOnDodge(BtlObj* sora) {
    BtlObj* target = gBtlWork->actor2;

    RogueGadgetFire(GADGET_ON_DODGE, target);

    if (!RogueHasRelic(ROGUE_RELIC_TELEPORT) || target == 0) {
        return;
    }

    if (sora->x < target->x) {
        sora->x = target->x + 0x2400;
        sora->flags |= 4;
    } else {
        sora->x = target->x - 0x2400;
        sora->flags &= ~4;
    }

    sora->y = target->y;
    sora->unk_014 = sora->x;
    gRogueDebug.teleports++;
}

// Called every frame of a dodge's slide: with the trail it cuts what it
// passes through.
void RogueDodgeTrail(BtlObj* sora) {
    u64 flags;
    s32 scale;

    RogueGadgetFire(GADGET_ON_DODGE_STEP, 0);

    if (!RogueHasRelic(ROGUE_RELIC_TRAIL)) {
        return;
    }

    flags = gBtlWork->flags;
    scale = gBtlWork->unk_124;
    gBtlWork->flags |= 0x20000000;
    gBtlWork->unk_124 = 160;
    gRogue.echoing = 1;

    if (func_08011F78(14, sora->x, sora->y, sora->z, 20, 14, 32)) {
        gRogueDebug.moveHits++;
    }

    gRogue.echoing = 0;
    gBtlWork->unk_124 = scale;
    gBtlWork->flags = (gBtlWork->flags & ~0x20000000ULL) | (flags & 0x20000000);
}

// What the elements leave behind. A hit is still being worked out when its
// relic sees it, so the effect is noted and done on a later frame.
enum { AFTER_NONE, AFTER_BURN, AFTER_FREEZE, AFTER_SHOCK };

typedef struct RogueAfterEffect {
    BtlObj* target;
    s16 amount;
    u8 kind;
    u8 timer; // frames until it acts
    u8 ticks; // times it still acts
} RogueAfterEffect;

static RogueAfterEffect sAfter[ROGUE_AFTER_EFFECTS];

static void RogueAfterAdd(BtlObj* target, u8 kind, s16 amount, u8 timer, u8 ticks) {
    s32 i;

    for (i = 0; i < ROGUE_AFTER_EFFECTS; i++) {
        // One of a kind on an enemy: a new burn renews the old.
        if (sAfter[i].kind == kind && sAfter[i].target == target) {
            break;
        }
    }

    if (i == ROGUE_AFTER_EFFECTS) {
        for (i = 0; i < ROGUE_AFTER_EFFECTS && sAfter[i].kind != AFTER_NONE; i++) {
        }
    }

    if (i < ROGUE_AFTER_EFFECTS) {
        sAfter[i].target = target;
        sAfter[i].kind = kind;
        sAfter[i].amount = amount;
        sAfter[i].timer = timer;
        sAfter[i].ticks = ticks;
    }
}

// Called for each enemy one of Sora's hits has just been worked out on.
void RogueAfterHit(BtlObj* target) {
    u32 element = target->unk_024;
    s32 damage = target->unk_020;

    if (damage <= 0) {
        return;
    }

    if ((element & 0x10000000) && RogueHasRelic(ROGUE_RELIC_BURN)) {
        RogueAfterAdd(target, AFTER_BURN, damage / 4 + 1, 30, ROGUE_BURN_TICKS);
    }

    if (gRogue.freezing) {
        RogueApplyFreeze(target);
    } else if ((element & 0x20000000) && RogueHasRelic(ROGUE_RELIC_FREEZE) && !(target->flags & 0x80000000)) {
        RogueAfterAdd(target, AFTER_FREEZE, 0, 20, 1);
    }

    if ((element & 0x40000000) && RogueHasRelic(ROGUE_RELIC_SHOCK)) {
        RogueAfterAdd(target, AFTER_SHOCK, damage / 2 + 1, 4, 1);
    }
}

// Damage that comes from no hitbox: the enemy takes it when it next looks.
void RogueDirectDamage(BtlObj* target, s16 amount) {
    if (target->unk_0D8 != 0) {
        target = target->unk_0D8;
    }

    if (target->unk_02C <= 0 || (target->flags & 2)) {
        return;
    }

    target->unk_020 = amount;
    target->unk_024 = 0;
    target->unk_0A8 = 0;
    target->unk_0AC = 0;
    gBtlWork->unk_076 = 0;
    target->flags |= 2;
    gRogueDebug.afterHits++;
}

static void RogueAfterTick(void) {
    BtlObj* sora = gBtlWork->actor;
    BtlObj* actor;
    RogueAfterEffect* effect;
    s32 i;
    s32 alive;

    for (i = 0; i < ROGUE_AFTER_EFFECTS; i++) {
        effect = &sAfter[i];

        if (effect->kind == AFTER_NONE) {
            continue;
        }

        if (effect->timer != 0) {
            effect->timer--;
            continue;
        }

        // The enemy may be gone since: only one still in the battle is touched.
        alive = 0;

        for (actor = (BtlObj*)ListPoolFirst(&gBtlWork->pool); actor != 0; actor = (BtlObj*)ListPoolNext(&actor->node)) {
            if (actor == effect->target && actor != sora && actor->unk_02C > 0) {
                alive = 1;
            }
        }

        if (!alive && effect->kind != AFTER_SHOCK) {
            effect->kind = AFTER_NONE;
            continue;
        }

        switch (effect->kind) {
        case AFTER_BURN:
            RogueDirectDamage(effect->target, effect->amount);
            effect->timer = 30;
            break;
        case AFTER_FREEZE:
            // The game's own Stop, asked for as its spell asks.
            effect->target->unk_020 = ROGUE_FREEZE_FRAMES;
            effect->target->flags |= 0x800;
            gRogueDebug.afterHits++;
            break;
        case AFTER_SHOCK:
            for (actor = (BtlObj*)ListPoolFirst(&gBtlWork->pool); actor != 0; actor = (BtlObj*)ListPoolNext(&actor->node)) {
                if (actor != effect->target && actor != sora) {
                    RogueDirectDamage(actor, effect->amount);
                }
            }
            break;
        }

        if (--effect->ticks == 0) {
            effect->kind = AFTER_NONE;
        }
    }
}

// For what burns or freezes without a relic.
void RogueApplyBurn(BtlObj* target, s16 amount) {
    RogueAfterAdd(target, AFTER_BURN, amount, 30, ROGUE_BURN_TICKS);
}

void RogueApplyFreeze(BtlObj* target) {
    if (!(target->flags & 0x80000000)) {
        RogueAfterAdd(target, AFTER_FREEZE, 0, 20, 1);
    }
}

void RogueAfterReset(void) {
    s32 i;

    for (i = 0; i < ROGUE_AFTER_EFFECTS; i++) {
        sAfter[i].kind = AFTER_NONE;
    }
}

// Styles. A string of plain hits sets its element off on the enemy every few
// hits: a burst of flame that burns, ice that freezes, or the bolt of Sora's
// own Thunder. The burst is done on the frame after the hit that earned it.

void func_08015834(u16 a, s32 x, s32 y, s32 z, s32 p, s32 q, s32 r, s32 s);

static BtlObj* sStyleTarget;
static u8 sStyleDelay[ROGUE_ELEMENTS]; // frames until each element's burst, 0 when none is owed

// One of the moves somewhere of the caller's choosing, in one of the modes.
void RogueMoveSpawn(u8 move, s32 x, s32 y, s32 z, u8 mode, u8 phase, u8 delay, u8 freeze) {
    RogueMoveArgs args;

    args.def = &sMoves[move];
    args.left = (gBtlWork->actor->flags & 4) != 0;
    args.x = x;
    args.y = y;
    args.z = z;
    args.vy = 0;
    args.delay = delay;
    args.mode = mode;
    args.phase = phase;
    args.freeze = freeze;
    args.foe = 0;

    if (delay == 0 && mode == ROGUE_MOVE_PLAIN) {
        m4aSongNumStart(args.def->sound);
    }

    TaskCreate(&gBtlWork->taskPools[0], &sTaskDescRogueMove, &args);
    gRogueDebug.moves++;
}

// One of the moves made by a boss: it is Sora it hits. left: the way a thrown one flies.
void RogueFoeMove(BtlObj* foe, u8 move, s32 x, s32 y, s32 z, u8 mode, u8 phase, u8 delay, u8 left) {
    RogueMoveArgs args;

    args.def = &sMoves[move];
    args.left = left;
    args.x = x;
    args.y = y;
    args.z = z;
    args.vy = 0;
    args.delay = delay;
    args.mode = mode;
    args.phase = phase;
    args.freeze = 0;
    args.foe = foe;

    if (delay == 0) {
        m4aSongNumStart(args.def->sound);
    }

    TaskCreate(&gBtlWork->taskPools[0], &sTaskDescRogueMove, &args);
}

// The bolt of Sora's own Thunder, from above him onto an enemy. The game
// draws one at a time: a second asked for meanwhile does not come.
void RogueThunderBolt(BtlObj* target) {
    BtlObj* sora = gBtlWork->actor;

    func_08015834(0, sora->x, sora->y, sora->z - 16384, target->x, target->y, 0, 72);
}

// Called for each plain hit of Sora's, with the string's count already on it.
// Every style whose turn it is goes off, one after the other.
void RogueStyleOnHit(BtlObj* target) {
    static const u8 every[ROGUE_ELEMENTS] = { ROGUE_STYLE_FIRE_EVERY, ROGUE_STYLE_ICE_EVERY, ROGUE_STYLE_THUNDER_EVERY };
    u8 build = RogueBuildElement();
    u8 element;
    u8 delay = 1;

    if (gRogue.combo == 0) {
        return;
    }

    for (element = 0; element < ROGUE_ELEMENTS; element++) {
        if ((build == element || RogueHasRelic(ROGUE_RELIC_STYLE_FIRE + element)) && gRogue.combo % every[element] == 0 &&
            sStyleDelay[element] == 0) {
            sStyleDelay[element] = delay;
            sStyleTarget = target;
            delay += 14;
        }
    }
}

static void RogueStyleTick(void) {
    BtlObj* sora = gBtlWork->actor;
    BtlObj* actor;
    BtlObj* target = 0;
    u8 element;

    for (element = 0; element < ROGUE_ELEMENTS; element++) {
        if (sStyleDelay[element] == 0 || --sStyleDelay[element] != 0) {
            continue;
        }

        // The enemy may be gone since the hit.
        for (actor = (BtlObj*)ListPoolFirst(&gBtlWork->pool); actor != 0; actor = (BtlObj*)ListPoolNext(&actor->node)) {
            if (actor == sStyleTarget && actor != sora) {
                target = actor;
            }
        }

        if (target == 0) {
            continue;
        }

        switch (element) {
        case ROGUE_ELEMENT_FIRE:
            RogueMoveSpawn(ROGUE_MOVE_FIRE_BURST, target->x, target->y, target->z, ROGUE_MOVE_PLAIN, 0, 0, 0);
            RogueApplyBurn(target, 2 + gRogue.floor);
            break;
        case ROGUE_ELEMENT_ICE:
            RogueMoveSpawn(ROGUE_MOVE_SHARDS, target->x, target->y, target->z, ROGUE_MOVE_PLAIN, 0, 0, 1);
            break;
        case ROGUE_ELEMENT_THUNDER:
            RogueThunderBolt(target);
            break;
        }

        gRogueDebug.styleHits++;
    }
}

void RogueStyleReset(void) {
    u8 element;

    for (element = 0; element < ROGUE_ELEMENTS; element++) {
        sStyleDelay[element] = 0;
    }
}
