#include "rogue.h"
#include "anim.h"
#include "battle.h"
#include "battle_actor.h"
#include "btl.h"
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
} RogueMoveDef;

#define SHEET(name) name##Tiles, sizeof(name##Tiles), 0
#define BLOCK(name, size) name##Tiles, 0, size

// The attacks used: 14 is a keyblade finisher (256 a swing), 303 one of
// Axel's fire attacks (512), 313 one of Vexen's ice ones (256) and 0x133
// Larxene's thunder knife.
static const RogueMoveDef sMoves[ROGUE_MOVE_DEFS] = {
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
};

typedef struct RogueMoveArgs {
    const RogueMoveDef* def;
    s32 x;
    s32 y;
    s32 z;
    s32 vy; // sideways speed of a thrown one, for the fan
    u8 left;
    u8 delay; // frames before it appears
} RogueMoveArgs;

typedef struct RogueMoveWork {
    RogueMoveArgs args;
    void* tiles;
    void* palette;
    AnimState anim;
    u8 timer;
    u8 hits; // made so far, for the ones that hit more than once
    u8 shown;
} RogueMoveWork;

static void RogueMove_Init(RogueMoveWork* w, RogueMoveArgs* args) {
    w->args = *args;
    w->timer = 0;
    w->hits = 0;
    w->shown = 0;
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
    AnimStart(&w->anim, def->anim, def->motion == MOTION_THROWN);
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

    damage += damage * RogueUpgradeLevel(ROGUE_UPGRADE_MOVES) * 15 / 100;

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
    hit = func_08011F78(RogueMoveAttack(def), w->args.x, w->args.y, w->args.z, width, depth, height);
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

    switch (def->motion) {
    case MOTION_THROWN:
        RogueMoveHit(w);
        w->args.x += w->args.left ? -ROGUE_MOVE_SPEED : ROGUE_MOVE_SPEED;
        w->args.y += w->args.vy;
        target = gBtlWork->actor2;

        // The hound: it drifts across to the enemy locked on.
        if (RogueHasRelic(ROGUE_RELIC_MOD_HOMING) && target != 0) {
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

    for (i = 0; i < count; i++) {
        args.x = sora->x;
        args.y = sora->y;
        args.z = sora->z;
        args.vy = 0;
        args.delay = 0;

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
    if (gRogue.moveEchoTimer != 0 && --gRogue.moveEchoTimer == 0 && gRogue.moveEcho != 0) {
        RogueMoveCast(gRogue.moveEcho - 1, gBtlWork->actor, 1);
        gRogue.moveEcho = 0;
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
