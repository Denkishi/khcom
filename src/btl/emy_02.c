#include "task_descriptors.h"
#include "sprites_emy.h"
#include "enemy_common.h"
#include "emy_tasks.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "btl_effect.h"
#include "enemy_types.h"
#include "engine_math.h"
#include "mode_chkobj_assets.h"
#include "taskpool.h"
#include "types.h"

static const AnimDef sEmy02CommonAnimDefs[3] = {
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 0, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 3, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 2, { 0, 0, 0 } },
};

static const AnimDef sEmy02AnimDefs[2] = {
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 6, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 8, { 0, 0, 0 } },
};

static const EmyDef sEmy02Def = { gEmy02Palette, sEmy02CommonAnimDefs, 460, 130, 20, 20, 64, 32, 32, 10, 0, { 2, 34, 24, 12, 4, 100, EMY_KIND_FLAG_NO_ENEMY_COLLISION } };

TaskDesc gTaskDescEmy02 = {
    "task_emy_02",
    (TaskInitFunc)task_emy_02_0,
    (TaskUpdateFunc)task_emy_02_1,
    (TaskDrawFunc)task_emy_02_2,
    (TaskDestroyFunc)task_emy_02_3,
    sizeof(EmyWork),
};

void task_emy_02_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy02Def, obj);
    work->idleState = 7;
}

u8 task_emy_02_1(EmyWork* work) {
    EmyWork* w;
    BtlObj* act;
    u16 r;
    s32 p;

    w = work;
    act = &work->actor;

    if (EmyUpdateReaction(work)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->state = 0x12;
            break;
        case 1:
            work->state = 0x13;
            break;
        }
    }

    switch (work->state) {
    case 0x12: {
        s32 y;

        AnimChangeWithDef(sEmy02AnimDefs, &w->anim, 0, 0, w->tiles);
        work->vz = 0;

        if (work->stateTimer == 0) {
        } else if (work->stateTimer == 22) {
            y = act->y;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                p = act->x - 0x3C00;
                BgFxStartBlizzard(0, act->x - 0x2800, y, act->z - 0x800, p, y, 0, 1,
                    0xA9);
            } else {
                p = act->x + 0x3C00;
                BgFxStartBlizzard(0, act->x + 0x2800, y, act->z - 0x800, p, y, 0, 0,
                    0xA9);
            }
        }

        if (work->stateTimer > 21 && !BgFxIsActive()) {
            EmyReturnToIdle(work);
        } else {
            work->stateTimer++;
        }

        break;
    }
    case 0x13: {
        s32 y;

        AnimChangeWithDef(sEmy02AnimDefs, &w->anim, 1, 0, w->tiles);
        work->vz = 0;

        if (work->stateTimer == 0) {
        } else if (work->stateTimer == 3) {
            y = act->y;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                p = act->x - 0x3C00;
                BgFxStartBlizzard(1, act->x - 0x2800, y, act->z - 0x800, p, y, 0, 1,
                    0xAA);
            } else {
                p = act->x + 0x3C00;
                BgFxStartBlizzard(1, act->x + 0x2800, y, act->z - 0x800, p, y, 0, 0,
                    0xAA);
            }
        }

        if (work->stateTimer > 2 && !BgFxIsActive()) {
            EmyReturnToIdle(work);
        } else {
            work->stateTimer++;
        }

        break;
    }
    }

    return EmyUpdateCommonStates(work);
}

void task_emy_02_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_02_3(EmyWork* work) {
    EmyReleaseResources(work);
}
