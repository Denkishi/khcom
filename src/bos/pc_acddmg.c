#include "pc_acddmg.h"
#include "battle_actor_types.h"
#include "battle_work.h"
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

TaskDesc gTaskDescPcAcddmg = {
    "task_pc_acddmg",
    (TaskInitFunc)task_pc_acddmg_0,
    (TaskUpdateFunc)task_pc_acddmg_1,
    NULL,
    NULL,
    sizeof(PcAcdDmgWork),
};
