/**
 * emy_15.c
 * Powerwild Enemy
 */

#include "task_descriptors.h"
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
#include "sprite_palettes.h"

static const AnimDef sEmy15CommonAnimDefs[3] = {
    { gEmy1500Frames, gEmy1500Anims, gEmy1500Tiles, 0, { 0, 0, 0 } },
    { gEmy1502Frames, gEmy1502Anims, gEmy1502Tiles, 0, { 0, 0, 0 } },
    { gEmy1501Frames, gEmy1501Anims, gEmy1501Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy15AnimDefs[5] = {
    { gEmy1510Frames, gEmy1510Anims, gEmy1510Tiles, 0, { 0, 0, 0 } },
    { gEmy1510Frames, gEmy1510Anims, gEmy1510Tiles, 1, { 0, 0, 0 } },
    { gEmy1510Frames, gEmy1510Anims, gEmy1510Tiles, 2, { 0, 0, 0 } },
    { gEmy1511Frames, gEmy1511Anims, gEmy1511Tiles, 0, { 0, 0, 0 } },
    { gEmy1511Frames, gEmy1511Anims, gEmy1511Tiles, 1, { 0, 0, 0 } },
};

static const EmyDef sEmy15Def = { gEmy15Palette, sEmy15CommonAnimDefs, 192, 200, 2, 20, 64, 32, 32, 10, 0, { 10, 41, 35, 12, 16, 100, 0 } };

TaskDesc gTaskDescEmy15 = {
    "task_emy_15",
    (TaskInitFunc)task_emy_15_0,
    (TaskUpdateFunc)task_emy_15_1,
    (TaskDrawFunc)task_emy_15_2,
    (TaskDestroyFunc)task_emy_15_3,
    sizeof(EmyWork),
};

void task_emy_15_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy15Def, obj);
}

u8 task_emy_15_1(EmyWork* work) {
    EmyWork* w;
    BtlObj* act;
    u16 r;

    w = work;
    act = &work->actor;

    if (EmyUpdateReaction(work)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->state = 0x12;
            break;
        case 1:
            work->state = 0x15;
            break;
        }
    }

    switch (work->state) {
    case 0x12:
        AnimChangeWithDef(sEmy15AnimDefs, &w->anim, 0, 0, w->tiles);

        if (AnimIsFinished(&work->anim)) {
            work->state = 0x13;
            work->stateTimer = 0x1E;
        }

        break;
    case 0x13:
        AnimChangeWithDef(sEmy15AnimDefs, &w->anim, 1, 0, w->tiles);

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            ApproachValueHalfSteps(&act->x, act->originX - 0x5000, work->stateTimer);
        } else {
            ApproachValueHalfSteps(&act->x, act->originX + 0x5000, work->stateTimer);
        }

        work->stateTimer--;

        if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                ? ApplyAttackBox(0xB5, act->x - 0x1400, act->y, act->z, 5, 5, 4)
                : ApplyAttackBox(0xB5, act->x + 0x1400, act->y, act->z, 5, 5, 4)) {
            m4aSongNumStart(SONG_BTL_HANE_HIT);
        }

        if (work->stateTimer <= 0) {
            work->state = 0x14;
            work->stateTimer = 0;
        }

        break;
    case 0x14:
        AnimChangeWithDef(sEmy15AnimDefs, &w->anim, 2, 0, w->tiles);

        if (AnimIsFinished(&work->anim)) {
            EmyReturnToIdle(work);
        }

        break;
    case 0x15:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sEmy15AnimDefs, &w->anim, 3, 0, w->tiles);
            work->vz = -0x533;
        }

        if (work->stateTimer > 5) {
            work->state = 0x16;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    case 0x16:
        AnimChangeWithDef(sEmy15AnimDefs, &w->anim, 4, 0, w->tiles);
        EmyLungeAttack(work, 0x16, 0x16, 0x3C, 0xB6, 0x40, SONG_BTL_MON_HIT02, 0x10, -0x0C, 0x0C);
        break;
    }

    return EmyUpdateCommonStates(work);
}

void task_emy_15_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_15_3(EmyWork* work) {
    EmyReleaseResources(work);
}
