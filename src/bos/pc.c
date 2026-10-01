#include "pc.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "engine_math.h"
#include "hum.h"
#include "hum_types.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

void task_pc_acddmg_0(PcAcdDmgWork* work, BtlObj* obj) {
    work->actor = obj;
    work->groundFrames = 0;
    work->timer = 0x28;
    work->grounded = 0;
}

s32 task_pc_acddmg_1(PcAcdDmgWork* work) {
    BtlObj* obj;

    if (!(gBtlWork->flags & 0x100000)) {
        obj = work->actor;

        if (obj->z >= 0) {
            work->grounded = 1;

            if (work->timer <= 0) {
                if (work->groundFrames % 60 == 0) {
                    obj->flags |= BTLOBJ_FLAG_HAZARD_PENDING;
                }

                work->groundFrames++;
            } else {
                work->timer--;
            }
        } else {
            if (work->grounded != 0) {
                work->grounded = 0;
                work->groundFrames = 0;
                work->timer = 0;
            }

            if (!(gBtlWork->flags & BTL_FLAG_PLAYER_AIRBORNE)) {
                work->timer = 0x28;
            }
        }
    }

    return 1;
}

void CloudJumpOffset(CloudWork* work, s16 a, s32 b) {
    CloudWork* w = work;
    BtlObj* obj = &work->base.actor;

    if (obj->flags & BTLOBJ_FLAG_FACING_LEFT) {
        work->base.targetX = obj->x - (a << 8);
    } else {
        work->base.targetX = obj->x + (a << 8);
    }

    w->base.targetY = obj->y;
    w->base.state = 0x19;
    w->base.stateTimer = 0;
    work->unk_188 = -b;
    work->state = 0;
}

void CloudJumpTo(CloudWork* work, s32 a, s32 b) {
    work->base.targetX = a;
    work->base.targetY = b;
    work->base.state = 0x19;
    work->base.stateTimer = 0;
    work->unk_188 = -0x500;
    work->nextState = 0;
}

void CloudLeapTo(CloudWork* work, s32 a, s32 b) {
    work->base.targetX = a;
    work->base.targetY = b;
    work->base.state = 0x21;
    work->base.stateTimer = 0;
}

s32 CloudTryJumpAway(CloudWork* work) {
    s32 x;
    s32 y;
    BtlObj* obj;

    obj = gBtlWork->actor;

    if (GetRandom() % 60 == 0) {
        GetEnemyTargetPosition(&work->base.actor, &x, &y, NULL);
        HumFaceTarget(&work->base, 1);

        if (HumIsInPlayerReach(&work->base, 0x100, 0x100, 0x100)) {
            if (gBtlWork->flags & BTL_FLAG_PLAYER_AIRBORNE) {
                CloudJumpOffset(work, -0x63, 0x280);
            } else if (GetRandom() & 1) {
                if (obj->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    CloudJumpTo(work, x + 0x2800, y);
                } else {
                    CloudJumpTo(work, x - 0x2800, y);
                }
            } else {
                CloudJumpOffset(work, -0x50, 0x500);
            }

            return 1;
        }
    }

    return 0;
}

TaskDesc gTaskDescPcAcddmg = {
    "task_pc_acddmg",
    (TaskInitFunc)task_pc_acddmg_0,
    (TaskUpdateFunc)task_pc_acddmg_1,
    NULL,
    NULL,
    sizeof(PcAcdDmgWork),
};
