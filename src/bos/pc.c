#include "task_descriptors.h"
#include "pc.h"
#include "pc_api.h"

void task_pc_acddmg_0(PcAcdDmgWork* work, BtlObj* obj) {
    work->actor = obj;
    work->unk_02 = 0;
    work->timer = 0x28;
    work->unk_08 = 0;
}

s32 task_pc_acddmg_1(PcAcdDmgWork* work) {
    BtlObj* obj;

    if (!(gBtlWork->flags & 0x100000)) {
        obj = work->actor;
        if (obj->z >= 0) {
            work->unk_08 = 1;

            if (work->timer <= 0) {
                if (work->unk_02 % 60 == 0) {
                    obj->flags |= 0x20000000;
                }
                work->unk_02++;
            } else {
                work->timer--;
            }
        } else {
            if (work->unk_08 != 0) {
                work->unk_08 = 0;
                work->unk_02 = 0;
                work->timer = 0;
            }

            if (!(gBtlWork->flags & 0x8000)) {
                work->timer = 0x28;
            }
        }
    }
    return 1;
}

void func_08049E70(CloudWork* work, s16 a, s32 b) {
    CloudWork* w = work;
    BtlObj* obj = &work->base.actor;

    if (obj->flags & 4) {
        work->base.targetX = obj->x - (a << 8);
    } else {
        work->base.targetX = obj->x + (a << 8);
    }
    w->base.targetY = obj->y;
    w->base.unk_170 = 0x19;
    w->base.unk_150 = 0;
    work->unk_188 = -b;
    work->state = 0;
}

void func_08049EE4(CloudWork* work, s32 a, s32 b) {
    work->base.targetX = a;
    work->base.targetY = b;
    work->base.unk_170 = 0x19;
    work->base.unk_150 = 0;
    work->unk_188 = -0x500;
    work->unk_190 = 0;
}

void func_08049F24(CloudWork* work, s32 a, s32 b) {
    work->base.targetX = a;
    work->base.targetY = b;
    work->base.unk_170 = 0x21;
    work->base.unk_150 = 0;
}

s32 func_08049F50(CloudWork* work) {
    s32 x;
    s32 y;
    BtlObj* obj;

    obj = gBtlWork->actor;

    if ((u16)GetRandom() % 60 == 0) {
        func_0801C700(&work->base.actor, &x, &y, 0);
        func_0800F368(&work->base, 1);

        if (func_0800F504(&work->base, 0x100, 0x100, 0x100)) {
            if (gBtlWork->flags & 0x8000) {
                func_08049E70(work, -0x63, 0x280);
            } else if (GetRandom() & 1) {
                if (obj->flags & 4) {
                    func_08049EE4(work, x + 0x2800, y);
                } else {
                    func_08049EE4(work, x - 0x2800, y);
                }
            } else {
                func_08049E70(work, -0x50, 0x500);
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
