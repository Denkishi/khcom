/**
 * emy_19.c
 * Bandit Enemy
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
#include "m4a_song.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "sprite_palettes.h"

static const AnimDef sEmy19CommonAnimDefs[3] = {
    { gEmy1900Frames, gEmy1900Anims, gEmy1900Tiles, 0 },
    { gEmy1902Frames, gEmy1902Anims, gEmy1902Tiles, 0 },
    { gEmy1901Frames, gEmy1901Anims, gEmy1901Tiles, 0 },
};

static const AnimDef sEmy19AnimDefs[5] = {
    { gEmy1910Frames, gEmy1910Anims, gEmy1910Tiles, 0 },
    { gEmy1910Frames, gEmy1910Anims, gEmy1910Tiles, 1 },
    { gEmy1910Frames, gEmy1910Anims, gEmy1910Tiles, 2 },
    { gEmy1910Frames, gEmy1910Anims, gEmy1910Tiles, 3 },
    { gEmy1911Frames, gEmy1911Anims, gEmy1911Tiles, 0 },
};

static const EmyDef sEmy19Def = { gEmy19Palette, sEmy19CommonAnimDefs, 256, 130, 20, 20, 80, 80, 32, 10, 0, { 13, 53, 32, 13, 16, 100, 0 } };

TaskDesc gTaskDescEmy19 = {
    "task_emy_19",
    (TaskInitFunc)task_emy_19_0,
    (TaskUpdateFunc)task_emy_19_1,
    (TaskDrawFunc)task_emy_19_2,
    (TaskDestroyFunc)task_emy_19_3,
    sizeof(Emy19Work),
};

void task_emy_19_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy19Def, obj);
}

u8 task_emy_19_1(Emy19Work* work) {
    Emy19Work* w;
    BtlObj* act;
    s32 pos;
    s32 d;

    w = work;
    act = &work->base.actor;

    if (EmyUpdateReaction(&work->base)) {
        GetEnemyTargetPosition(act, &pos, NULL, NULL);
        d = act->x - pos;

        if (d >= 0 ? d <= 0x3BFF : pos - act->x <= 0x3BFF) {
            work->base.state = 0x17;
        } else {
            work->base.state = 0x12;
        }

        w->dashSpeed = 0;
    }

    switch (work->base.state) {
    case 0x12:
        AnimChangeWithDef(sEmy19AnimDefs, &w->base.anim, 0, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 0x13;
            work->base.stateTimer = 0;
        }

        break;
    case 0x13:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sEmy19AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
            work->base.vz = -0x500;
            w->dashSpeed = 0x500;
        }

        act->x = act->flags & BTLOBJ_FLAG_FACING_LEFT ? act->x - w->dashSpeed : act->x + w->dashSpeed;
        w->dashSpeed = w->dashSpeed * 248 >> 8;

        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 0x14;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 0x14:
        AnimChangeWithDef(sEmy19AnimDefs, &w->base.anim, 2, ANIM_FLAG_LOOP, w->base.tiles);
        act->x = act->flags & BTLOBJ_FLAG_FACING_LEFT ? act->x - w->dashSpeed : act->x + w->dashSpeed;
        w->dashSpeed = w->dashSpeed * 248 >> 8;

        if (act->z >= act->groundZ) {
            work->base.vz = -0x500;
        }

        if (ApplyAttackBox(0xBB, act->x, act->y, act->z, 10, 10, 10) != 0) {
            m4aSongNumStart(SONG_BTL_MON_SWORD03);
            w->dashSpeed = -w->dashSpeed;
            work->base.vz = -0x500;
        }

        if (work->base.stateTimer > 55) {
            work->base.state = 0x15;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 0x15:
        AnimChangeWithDef(sEmy19AnimDefs, &w->base.anim, 3, 0, w->base.tiles);
        act->x = act->flags & BTLOBJ_FLAG_FACING_LEFT ? act->x - w->dashSpeed : act->x + w->dashSpeed;
        w->dashSpeed = w->dashSpeed * 248 >> 8;

        if (act->z >= act->groundZ) {
            work->base.state = 0x16;
            work->base.stateTimer = 0;
        }

        break;
    case 0x16:
        AnimChangeWithDef(sEmy19AnimDefs, &w->base.anim, 0, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        }

        break;
    case 0x17:
        AnimChangeWithDef(sEmy19AnimDefs, &w->base.anim, 4, 0, w->base.tiles);

        switch (AnimGetFrame(&work->base.anim)) {
        case 3:
            if (work->base.anim.timer == 0) {
                w->dashSpeed = 0x400;
            }

            break;
        case 4:
            if (work->base.anim.timer == 0) {
                w->dashSpeed = 0;
            }

            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(0xBC, act->x - 0x1000, act->y, act->z, 16, 16, 32) != 0
                    : ApplyAttackBox(0xBC, act->x + 0x1000, act->y, act->z, 16, 16, 32) != 0) {
                m4aSongNumStart(SONG_BTL_MON_SWORD02);
            }

            break;
        }

        act->x = act->flags & BTLOBJ_FLAG_FACING_LEFT ? act->x - w->dashSpeed : act->x + w->dashSpeed;
        w->dashSpeed = w->dashSpeed * 240 >> 8;

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        }

        break;
    }

    return EmyUpdateCommonStates(&work->base);
}

void task_emy_19_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_19_3(EmyWork* work) {
    EmyReleaseResources(work);
}
