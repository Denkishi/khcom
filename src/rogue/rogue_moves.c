#include "rogue.h"
#include "anim.h"
#include "battle.h"
#include "battle_actor.h"
#include "btl.h"
#include "btl_collision.h"
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
    MOTION_AROUND // appears on Sora and hits all around him
};

typedef struct RogueMoveDef {
    void* tiles;
    u16 tilesSize;
    void* palette;
    void* anims;
    void* frames;
    u8 anim;
    u8 motion;
    u8 count; // how many are thrown
    u8 frames_; // frames it lasts
    u8 hitFrame; // for the ones that do not fly: the frame the hit lands on
    u16 attack; // attack definition of the hit
    u16 scale; // 8.8, of that attack's damage
    u8 width; // of the hit box, in pixels
    u8 depth;
    u8 height;
    u16 sound;
} RogueMoveDef;

// The attacks used: 14 is a keyblade finisher (256 a swing), 303 one of
// Axel's fire attacks (512) and 313 one of Vexen's ice ones (256).
static const RogueMoveDef sMoves[ROGUE_MOVES] = {
    // Axel's chakram: thrown ahead, burning what it crosses.
    { gAcceleBtWepTiles, sizeof(gAcceleBtWepTiles), gAccelePalette, gAcceleBtWepAnims, gAcceleBtWepFrames, 0, MOTION_THROWN, 1, 40,
      0, 303, 128, 12, 12, 12, SONG_EF_RAC_3TR },
    // Vexen's needles: three thrown ahead.
    { gVixenE1Tiles, sizeof(gVixenE1Tiles), gVixEPalette, gVixenE1Anims, gVixenE1Frames, 0, MOTION_THROWN, 3, 36, 0, 313, 192, 6,
      8, 6, SONG_EF_RAC_3TR },
    // Marluxia's petals: a burst around Sora.
    { gMaruxhaBtEff1Tiles, sizeof(gMaruxhaBtEff1Tiles), gMaruxhaBtEffPalette, gMaruxhaBtEff1Anims, gMaruxhaBtEff1Frames, 0,
      MOTION_AROUND, 1, 36, 8, 14, 384, 56, 36, 56, SONG_EF_SUMMON_UP },
    // Vexen's ice shards: a blast in front of Sora.
    { gVixenReitouHahenTiles, sizeof(gVixenReitouHahenTiles), gVixEPalette, gVixenReitouHahenAnims, gVixenReitouHahenFrames, 0,
      MOTION_AHEAD, 1, 30, 4, 313, 320, 36, 24, 44, SONG_EF_RAC_3TR },
};

typedef struct RogueMoveArgs {
    const RogueMoveDef* def;
    s32 x;
    s32 y;
    s32 z;
    u8 left;
} RogueMoveArgs;

typedef struct RogueMoveWork {
    RogueMoveArgs args;
    void* tiles;
    void* palette;
    AnimState anim;
    u8 timer;
} RogueMoveWork;

static void RogueMove_Init(RogueMoveWork* w, RogueMoveArgs* args) {
    w->args = *args;
    w->timer = 0;
    w->palette = LoadObjPalette(args->def->palette, 0x20);
    w->tiles = LoadObjTiles(args->def->tiles, args->def->tilesSize);
    AnimInit(&w->anim, args->def->anims, args->def->frames);
    AnimStart(&w->anim, args->def->anim, args->def->motion == MOTION_THROWN);
}

// Tests the move's hit box as a hit of Sora's. Whom a hitbox hurts follows
// whose card is in play, so the player's turn is claimed for the test.
static s32 RogueMoveHit(RogueMoveWork* w) {
    const RogueMoveDef* def = w->args.def;
    u64 flags = gBtlWork->flags;
    s32 scale = gBtlWork->unk_124;
    s32 hit;

    gBtlWork->flags |= 0x20000000;
    gBtlWork->unk_124 = def->scale;
    gRogue.projectile = 1;
    gRogue.echoing = 1;
    hit = func_08011F78(def->attack, w->args.x, w->args.y, w->args.z, def->width, def->depth, def->height);
    gRogue.echoing = 0;
    gRogue.projectile = 0;
    gBtlWork->unk_124 = scale;
    gBtlWork->flags = (gBtlWork->flags & ~0x20000000ULL) | (flags & 0x20000000);

    if (hit) {
        gRogueDebug.moveHits++;
    }

    return hit;
}

static s32 RogueMove_Update(RogueMoveWork* w) {
    const RogueMoveDef* def = w->args.def;

    if (def->motion == MOTION_THROWN) {
        RogueMoveHit(w);
        w->args.x += w->args.left ? -ROGUE_MOVE_SPEED : ROGUE_MOVE_SPEED;
    } else if (w->timer == def->hitFrame) {
        RogueMoveHit(w);
    }

    AnimUpdate(&w->anim);
    return ++w->timer < def->frames_;
}

static void RogueMove_Draw(RogueMoveWork* w) {
    u16 attr = GetBattleSpritePriorityFlags(w->args.y);
    s16 x;
    s16 y;

    if (!w->args.left) {
        attr |= 1;
    }

    WorldToScreen(&x, &y, w->args.x, w->args.y, w->args.z);
    DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, attr, -0x1004 - (w->args.y >> 8) * 4);
}

static void RogueMove_Destroy(RogueMoveWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
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
static void RogueMovePose(BtlObj* sora) {
    BtlSoraWork* work = (BtlSoraWork*)((u8*)sora - (u32) & ((BtlSoraWork*)0)->actor);
    u32 state = work->unk_038;

    if ((state >= 1 && state <= 4) || (state >= 18 && state <= 21)) {
        gRogue.pose = 0;
        SetBtlSoraAnimation(work, 42, 0);
        gRogue.pose = ROGUE_MOVE_POSE;
    }
}

// Sora does one of the moves.
void RogueDoMove(u8 move, BtlObj* sora) {
    const RogueMoveDef* def = &sMoves[move];
    RogueMoveArgs args;
    s32 count = def->count;
    s32 i;

    // A projectile build throws two more of whatever comes in numbers.
    if (def->motion == MOTION_THROWN && count > 1 && RogueBuildBonus(ROGUE_BUILD_PROJECTILE) != 0) {
        count += 2;
    }

    RogueMovePose(sora);
    m4aSongNumStart(def->sound);
    args.def = def;
    args.left = (sora->flags & 4) != 0;

    for (i = 0; i < count; i++) {
        // The check counts 8x8 tiles, the size is in bytes.
        if (!CanAllocObjTiles(def->tilesSize / 32)) {
            return;
        }

        args.x = sora->x;
        args.y = sora->y + (i - count / 2) * 0x0A00;
        args.z = sora->z;

        if (def->motion != MOTION_AROUND) {
            args.x += args.left ? -0x2000 : 0x2000;
        }

        if (def->motion == MOTION_THROWN) {
            args.z -= 0x1400;
        }

        TaskCreate(&gBtlWork->taskPools[0], &sTaskDescRogueMove, &args);
        gRogueDebug.moves++;
    }
}
