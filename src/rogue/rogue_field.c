#include "rogue.h"
#include "anim.h"
#include "engine_math.h"
#include "map.h"
#include "obj_api.h"
#include "sprite.h"
#include "sprite_palettes.h"
#include "taskpool.h"

// Sora and the enemies of a room, before the battle. The nearest enemy
// within sight is marked with the ring the battle marks its target with,
// and a swing made near enough turns Sora to face it: he swings in one of
// eight directions, and an enemy between two of them was missed. The swing
// also reaches a little wider, see ROGUE_FIELD_REACH in map_cell.c.

#define SIGHT (96 << 8) // how far the ring looks for an enemy
#define AIM (64 << 8) // how near the enemy must be for the swing to turn to it

// The ring of the battle's lock-on.
extern u8 gUnk_08B1D8BC[];
extern u8 gUnk_09EE10F8[];
extern u8 gUnk_09EE10EC[];

typedef struct RogueRingWork {
    void* tiles;
    void* palette;
    AnimState anim;
} RogueRingWork;

// The nearest enemy seen so far this frame, and the one of the frame before:
// the enemies report themselves one by one as they are updated.
static FldPos sSeen;
static s32 sSeenFar;
static u8 sSeenAny;
static FldPos sTarget;
static s32 sTargetFar;
static u8 sTargetAny;

static s32 RogueFieldFar(const FldPos* p) {
    s32 dx = p->x - gFieldState->actor.fieldPosition.x;
    s32 dy = p->y - gFieldState->actor.fieldPosition.y;

    return (dx < 0 ? -dx : dx) + (dy < 0 ? -dy : dy);
}

// Called by each enemy of the room, every frame.
void RogueFieldSeeEnemy(FldPos* p) {
    s32 far = RogueFieldFar(p);

    if (!sSeenAny || far < sSeenFar) {
        sSeen = *p;
        sSeenFar = far;
        sSeenAny = 1;
    }
}

// The direction for a swing, given the one Sora faces: towards the marked
// enemy if it is near, as the nearest of the eight he can swing in.
u8 RogueFieldAim(u8 angle) {
    static const u8 angles[8] = { 0, 45, 64, 83, 128, 173, 192, 211 };
    s32 dx;
    s32 dy;
    s32 best = 0;
    s32 dot;
    s32 i;

    if (!sTargetAny || sTargetFar > AIM) {
        return angle;
    }

    dx = (sTarget.x - gFieldState->actor.fieldPosition.x) >> 8;
    dy = (sTarget.y - gFieldState->actor.fieldPosition.y) >> 8;

    // Sora steps along (sine, -cosine) of his angle: the one that points most the enemy's way.
    for (i = 0; i < 8; i++) {
        dot = gSineTable[angles[i]] * dx - gSineTable[angles[i] + 64] * dy;

        if (i == 0 || dot > best) {
            best = dot;
            angle = angles[i];
        }
    }

    gRogueDebug.fieldAims++;
    return angle;
}

static void RogueRing_Init(RogueRingWork* w) {
    // Only if the room leaves room for it: a room full of characters has no
    // palette to spare, and the game does not check before it uses one.
    w->tiles = 0;

    if (CanAllocObjTiles(12) && CanAllocObjPalette(3)) {
        w->tiles = LoadObjTiles(gUnk_08B1D8BC, 0x180);
        w->palette = LoadObjPalette(gBStatesPalette, 0x20);
        AnimInit(&w->anim, gUnk_09EE10F8, gUnk_09EE10EC);
        AnimStart(&w->anim, 0, 1);
    }

    sSeenAny = 0;
    sTargetAny = 0;
}

static s32 RogueRing_Update(RogueRingWork* w) {
    sTargetAny = sSeenAny && sSeenFar < SIGHT;
    sTarget = sSeen;
    sTargetFar = sSeenFar;
    sSeenAny = 0;

    if (w->tiles != 0) {
        AnimUpdate(&w->anim);
    }

    return 1;
}

static void RogueRing_Draw(RogueRingWork* w) {
    s16 x;
    s16 y;

    if (!sTargetAny || w->tiles == 0) {
        return;
    }

    x = (sTarget.x >> 8) - (gFieldState->x >> 8);
    y = (sTarget.y >> 8) + (sTarget.z >> 8) - (gFieldState->y >> 8) - 16;
    DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, 0x800, -0x3000);
    gRogueDebug.fieldRing = 1;
}

static void RogueRing_Destroy(RogueRingWork* w) {
    if (w->tiles != 0) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
    }
}

TaskDesc gTaskDescRogueRing = {
    "task_rogue_ring",
    (TaskInitFunc)RogueRing_Init,
    (TaskUpdateFunc)RogueRing_Update,
    (TaskDrawFunc)RogueRing_Draw,
    (TaskDestroyFunc)RogueRing_Destroy,
    sizeof(RogueRingWork),
};
