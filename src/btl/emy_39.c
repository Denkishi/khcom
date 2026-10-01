#include "task_descriptors.h"
#include "display.h"
#include "emy.h"
#include "sprites_emy.h"
#include "enemy_common.h"
#include "songs.h"
#include "emy_tasks.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "enemy_types.h"
#include "engine_math.h"
#include "m4a_song.h"
#include "mode_chkobj_assets.h"
#include "taskpool.h"
#include "types.h"

static const AnimDef sEmy39CommonAnimDefs[3] = {
    { gEmy3900Frames, gEmy3900Anims, gEmy3900Tiles, 0, { 0, 0, 0 } },
    { gEmy3902Frames, gEmy3902Anims, gEmy3902Tiles, 0, { 0, 0, 0 } },
    { gEmy3901Frames, gEmy3901Anims, gEmy3901Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy39AnimDefs[2] = {
    { gEmy3910Frames, gEmy3910Anims, gEmy3910Tiles, 0, { 0, 0, 0 } },
    { gEmy3911Frames, gEmy3911Anims, gEmy3911Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy39Def = { gEmy39Palette, sEmy39CommonAnimDefs, 102, 130, 100, 22, 64, 32, 32, 10, 0, { 26, 134, 56, 25, 32, 100, EMY_KIND_FLAG_LARGE_BODY } };

TaskDesc gTaskDescEmy39 = {
    "task_emy_39",
    (TaskInitFunc)task_emy_39_0,
    (TaskUpdateFunc)task_emy_39_1,
    (TaskDrawFunc)task_emy_39_2,
    (TaskDestroyFunc)task_emy_39_3,
    sizeof(Emy39Work),
};

void task_emy_39_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy39Def, obj);
}

u8 task_emy_39_1(Emy39Work* work) {
    Emy39Work* w;
    BtlObj* act;
    u16 r;
    s16 c;
    s32 z;
    s32 x;
    s32 p;
    s32 q;
    u8 ret;

    w = work;
    act = &work->base.actor;

    if (EmyUpdateReaction(&work->base)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->base.state = 0x12;
            break;
        case 1:
            work->base.state = 0x13;
            break;
        }
    }

    switch (work->base.state) {
    case 0x12:
        AnimChangeWithDef(sEmy39AnimDefs, &w->base.anim, 0, 0, w->base.tiles);

        if (work->base.stateTimer == 0x30) {
            z = act->y;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                x = act->x - 0x6400;
                BgFxStartFire(0, act->x - 0x4000, z, act->z - 0x2000, x, z, 0, 1,
                    0xD6);
            } else {
                x = act->x + 0x6400;
                BgFxStartFire(0, act->x + 0x4000, z, act->z - 0x2000, x, z, 0, 0,
                    0xD6);
            }
        }

        if (work->base.stateTimer > 0x30 && BgAnimIsStopped()) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }

        break;
    case 0x13:
        c = work->base.stateTimer;

        if (c == 0) {
            AnimChangeWithDef(sEmy39AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
            w->dashSpeed = 0;
        }

        switch (AnimGetFrame(&work->base.anim)) {
        case 0:
            p = 24;
            q = 20;
            break;
        case 1:
            p = 30;
            q = 16;
            break;
        case 2:
            p = 24;
            q = 20;

            if (work->base.anim.timer == 0) {
                w->dashSpeed = 0x200;
            }

            break;
        case 3:
            p = 24;
            q = 16;
            break;
        case 4:
            p = 48;
            q = 20;
            break;
        case 5:
            p = 30;
            q = 16;

            if (work->base.anim.timer == 0) {
                w->dashSpeed = 0x200;
            }

            break;
        case 6:
            p = 48;
            q = 20;
            break;
        case 7:
        default:
            p = 24;
            q = 20;
            break;
        }

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            act->x -= w->dashSpeed;
        } else {
            act->x += w->dashSpeed;
        }

        w->dashSpeed -= 0x19;

        if (w->dashSpeed < 0) {
            w->dashSpeed = 0;
        }

        if (ApplyAttackBox(0xD7, act->x, act->y, act->z, p, q, 0x28)) {
            m4aSongNumStart(SONG_BTL_MON_HIT02);
        }

        if (AnimIsFinished(&work->base.anim)) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }

        break;
    }

    ret = EmyUpdateCommonStates(&work->base);

    if ((gBtlWork->actor->x < work->base.actor.x
                && (work->base.actor.flags & BTLOBJ_FLAG_FACING_LEFT))
            || (gBtlWork->actor->x > work->base.actor.x
                && !(work->base.actor.flags & BTLOBJ_FLAG_FACING_LEFT))) {
        work->base.actor.flags |= BTLOBJ_FLAG_GUARD_PHYSICAL;
    } else {
        work->base.actor.flags &= ~BTLOBJ_FLAG_GUARD_PHYSICAL;
    }

    return ret;
}

void task_emy_39_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_39_3(EmyWork* work) {
    EmyReleaseResources(work);
}
