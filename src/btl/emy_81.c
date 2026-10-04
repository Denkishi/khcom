/**
 * emy_81.c
 * Tornado Step Enemy
 */

#include "task_descriptors.h"
#include "emy.h"
#include "sprites_emy.h"
#include "enemy_common.h"
#include "songs.h"
#include "emy_tasks.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "btl_collision.h"
#include "enemy_types.h"
#include "engine_math.h"
#include "m4a_song.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "sprite_palettes.h"

static const AnimDef sEmy81CommonAnimDefs[3] = {
    { gEmy8100Frames, gEmy8100Anims, gEmy8100Tiles, 0, { 0, 0, 0 } },
    { gEmy8102Frames, gEmy8102Anims, gEmy8102Tiles, 0, { 0, 0, 0 } },
    { gEmy8100Frames, gEmy8100Anims, gEmy8100Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy81AnimDefs[5] = {
    { gEmy8110Frames, gEmy8110Anims, gEmy8110Tiles, 0, { 0, 0, 0 } },
    { gEmy8111Frames, gEmy8111Anims, gEmy8111Tiles, 0, { 0, 0, 0 } },
    { gEmy8105Frames, gEmy8105Anims, gEmy8105Tiles, 0, { 0, 0, 0 } },
    { gEmy8105Frames, gEmy8105Anims, gEmy8105Tiles, 1, { 0, 0, 0 } },
    { gEmy8105Frames, gEmy8105Anims, gEmy8105Tiles, 2, { 0, 0, 0 } },
};

static const EmyDef sEmy81Def = { gEmy81Palette, sEmy81CommonAnimDefs, 128, 130, 20, 15, 64, 32, 32, 10, 0, { 29, 66, 27, 13, 16, 100, 0 } };

TaskDesc gTaskDescEmy81 = {
    "task_emy_81",
    (TaskInitFunc)task_emy_81_0,
    (TaskUpdateFunc)task_emy_81_1,
    (TaskDrawFunc)task_emy_81_2,
    (TaskDestroyFunc)task_emy_81_3,
    sizeof(Emy81Work),
};

void task_emy_81_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy81Def, obj);
}

static inline s32 EmyFacingX(BtlObj* actor, s32 offset) {
    return actor->flags & BTLOBJ_FLAG_FACING_LEFT ? actor->x - offset : actor->x + offset;
}

u8 task_emy_81_1(Emy81Work* work) {
    Emy81Work* w;
    BtlObj* act;
    u16 r;
    u16 frame;
    u16 idleFrame;
    s32 d;
    s32 hitX;
    s32 a;
    s32 z;
    s32 b;

    w = work;
    act = &work->base.actor;

    if (EmyUpdateReaction(&work->base)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->base.state = 18;
            break;
        case 1:
            work->base.state = 19;
            break;
        }
    }

    switch (work->base.state) {
    case 0:
    case 4:
        idleFrame = AnimGetGfxIndex(&work->base.anim);

        if ((idleFrame == 2 || idleFrame == 6) && work->base.anim.timer == 0) {
            work->base.vz = -0x133;
        }

        if (GetRandom() % 200 == 0) {
            work->base.state = 20;
            work->base.stateTimer = 0;
            w->speedX = 0;
        }

        break;
    case 20:
        AnimChangeWithDef(sEmy81AnimDefs, &w->base.anim, 2, 0, w->base.tiles);

        d = (-0x2800 - act->z) >> 4;

        if (d < -w->speedX) {
            w->speedX += 25;
        } else {
            w->speedX = -d;
        }

        work->base.vz = 0;

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 21;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 21:
        if (work->base.stateTimer == 0) {
            GetEnemyTargetPosition(act, &a, &b, NULL);
            AnimChangeWithDef(sEmy81AnimDefs, &w->base.anim, 3, ANIM_FLAG_LOOP, w->base.tiles);
            w->targetX = (a * 2) - act->x;
            w->targetY = (b * 2) - act->y;
            w->speedX = 0;
            w->speedY = 0;
        }

        work->base.vz = 0;

        {
            s32 sample = SIN((u16)work->base.stateTimer * 4) * 10;
            s32 current = act->z;

            z = current + 0x2800;
            act->z = current + ((sample - z) >> 3);
        }

        d = (w->targetX - act->x) >> 4;

        if (d > w->speedX) {
            d = w->speedX;
            w->speedX += 51;
        } else if (d < -w->speedX) {
            d = -w->speedX;
            w->speedX += 51;
        } else {
            w->speedX = d < 0 ? -d : d;
        }

        act->x += d;
        d = (w->targetY - act->y) >> 4;

        if (d > w->speedY) {
            d = w->speedY;
            w->speedY = d + 2;
        } else if (d < -w->speedY) {
            d = -w->speedY;
            w->speedY += 2;
        } else {
            w->speedY = d < 0 ? -d : d;
        }

        act->y += d;

        if ((work->base.flags & EMY_FLAG_AT_FIELD_EDGE)
                || ((w->targetX - act->x < 0
                        ? act->x - w->targetX
                        : w->targetX - act->x) <= 0x7FF
                    && (w->targetY - act->y < 0
                        ? act->y - w->targetY
                        : w->targetY - act->y) <= 0x7FF)) {
            work->base.state = 22;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 22:
        AnimChangeWithDef(sEmy81AnimDefs, &w->base.anim, 4, 0, w->base.tiles);
        work->base.vz -= 25;

        if (act->z >= act->groundZ) {
            work->base.state = work->base.idleState;
            work->base.stateTimer = 0;
        }

        break;
    case 18:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sEmy81AnimDefs, &w->base.anim, 0, 0, w->base.tiles);
        }

        {
            s32 currentX;
            s32 targetX;
            s32 adjustedX;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                targetX = 0x3000;
                currentX = act->x;
                adjustedX = currentX + targetX;
            } else {
                targetX = -0x3000;
                currentX = act->x;
                adjustedX = currentX + targetX;
            }

            targetX = act->originX;
            targetX -= adjustedX;
            targetX >>= 4;
            currentX += targetX;
            act->x = currentX;
        }

        frame = AnimGetFrame(&work->base.anim);

        if (frame >= 3 && frame <= 6) {
            work->base.vz = 0;
        }

        switch (frame) {
        case 1:
            if (work->base.anim.timer == 0) {
                work->base.vz = -0x400;
            }

            break;
        case 3:
            hitX = EmyFacingX(act, 0x1600);

            if (ApplyAttackBox(0xDC, hitX, act->y, act->z + 0x800, 10, 10, 10)) {
                m4aSongNumStart(SONG_BTL_MON_HIT04);
            }

            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }

        break;
    case 19:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sEmy81AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
        }

        {
            s32 currentX;
            s32 targetX;
            s32 adjustedX;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                targetX = 0x4600;
                currentX = act->x;
                adjustedX = currentX + targetX;
            } else {
                targetX = -0x4600;
                currentX = act->x;
                adjustedX = currentX + targetX;
            }

            targetX = act->originX;
            targetX -= adjustedX;
            targetX >>= 4;
            currentX += targetX;
            act->x = currentX;
        }

        frame = AnimGetFrame(&work->base.anim);

        if (frame == 4) {
            s32 centerX = EmyFacingX(act, 0);

            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(0xDD, centerX - 0x1800, act->y, act->z,
                        0x10, 0x10, 10)
                    : ApplyAttackBox(0xDD, centerX + 0x1800, act->y, act->z,
                        0x10, 0x10, 10)) {
                m4aSongNumStart(SONG_BTL_MON_HIT00);
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }

        break;
    }

    return EmyUpdateCommonStates(&work->base);
}

void task_emy_81_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_81_3(EmyWork* work) {
    EmyReleaseResources(work);
}
