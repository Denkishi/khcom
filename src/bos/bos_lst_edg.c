/**
 * bos_lst_edg.c
 * Marluxia Final Form Boomerang Attack
 */

#include "bos7.h"
#include "sprites_bos7.h"
#include "sprites_bos6.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "engine_math.h"
#include "obj_api.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"

TaskDesc gTaskDescBosLstEdg = {
    "task_bos_lst_edg",
    (TaskInitFunc)task_bos_lst_edg_0,
    (TaskUpdateFunc)task_bos_lst_edg_1,
    (TaskDrawFunc)task_bos_lst_edg_2,
    (TaskDestroyFunc)task_bos_lst_edg_3,
    sizeof(LstEdgWork),
};

s32 BosLstEdgSquare(s32 x) {
    return x * x;
}

s32 BosLstEdgSquare2(s32 x) {
    return x * x;
}

u8 BosLstEdgIsActive(Task* task) {
    LstEdgWork* s;

    s = task->work;
    return s->state != 4;
}

void task_bos_lst_edg_0(LstEdgWork* work, LstEdgArg* arg) {
    work->state = 0;
    work->unk_002 = 0;
    work->timer = 0;
    work->delay = arg->delay;
    work->x = arg->x;
    work->y = arg->y;
    work->z = arg->z;
    work->homeX = arg->x;
    work->homeY = arg->y;
    work->homeZ = arg->z;
    work->tiles = AllocObjTiles(0x80, gUnk_09C5C4E2);
    work->palette = LoadObjPalette(gUnk_09D69594, 0x60);
    AnimInit(&work->anim, gUnk_09EFAF1C, gUnk_09EFAEF8);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
}

u8 task_bos_lst_edg_1(LstEdgWork* work) {
    BtlObj* p;

    switch (work->state) {
    case 0:
        work->delay--;

        if (work->delay <= 0) {
            work->state = 1;
            work->unk_002 = 0;
            work->timer = 0;
            work->delay = 0;
            p = gBtlWork->actor;
            work->targetX = p->x;
            work->targetY = p->y;
            work->targetZ = -0x1000;
        }

        break;
    case 1:
        work->targetX = gBtlWork->actor->x;
        ApproachValueHalfSteps(&work->x, work->targetX, 30);
        ApproachValueHalfSteps(&work->y, work->targetY, 30);
        ApproachValueHalfSteps(&work->z, work->targetZ, 30);
        work->timer++;

        if (work->timer > 49) {
            work->state = 2;
            work->unk_002 = 0;
            work->timer = 0;
            work->delay = 0;
        }

        ApplyAttackBox(0x10C, work->x, work->y, work->z, 8, 8, 1);
        break;
    case 2:
        ApproachValueHalfSteps(&work->x, work->homeX, 30);
        ApproachValueHalfSteps(&work->y, work->homeY, 30);
        ApproachValueHalfSteps(&work->z, work->homeZ, 30);
        work->timer++;

        if (work->timer > 49) {
            work->state = 3;
            work->unk_002 = 0;
            work->timer = 0;
            work->delay = 0;
        }

        ApplyAttackBox(0x10C, work->x, work->y, work->z, 8, 8, 1);
        break;
    case 3:
        work->state = 4;
        work->unk_002 = 0;
        work->timer = 0;
        work->delay = 0;
        break;
    case 4:
        AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
        break;
    }

    AnimUpdate(&work->anim);

    return 1;
}

void task_bos_lst_edg_2(LstEdgWork* work) {
    s16 x;
    s16 y;
    u16 prio;
    u16 z;
    void* gfx;

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    prio = GetBattleSpritePriorityFlags(work->y);
    z = -0x1004 - (work->y >> 8) * 4;
    gfx = AnimGetGfx(&work->anim);
    DrawSprite(x, y, gfx, work->tiles, work->palette, NULL, prio, z);
}

void task_bos_lst_edg_3(LstEdgWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}
