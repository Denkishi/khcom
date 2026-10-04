/**
 * bos_lst_lsr.c
 * Marluxia Final Form Lasers
 */

#include "bos7.h"
#include "sprites_bos7.h"
#include "sprites_bos6.h"
#include <stdlib.h>
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "bos7_api.h"
#include "btl_collision.h"
#include "obj.h"
#include "obj_api.h"
#include "registration_data.h"
#include "taskpool.h"
#include "types.h"

TaskDesc gTaskDescBosLstLsr = {
    "task_bos_lst_lsr",
    (TaskInitFunc)task_bos_lst_lsr_0,
    (TaskUpdateFunc)task_bos_lst_lsr_1,
    (TaskDrawFunc)task_bos_lst_lsr_2,
    (TaskDestroyFunc)task_bos_lst_lsr_3,
    sizeof(LstLsrWork),
};

s32 BosLstLsrSquare(s32 x) {
    return x * x;
}

s32 BosLstLsrSquare2(s32 x) {
    return x * x;
}

s32 BosLstLsrSqrt(s32 n) {
    s32 x;
    s32 g;

    if (n <= 0) {
        return 0;
    }

    x = 1;
    g = n;

    while (x < g) {
        x <<= 1;
        g >>= 1;
    }

    do {
        g = x;
        x = (n / g + g) >> 1;
    } while (x < g);

    return g;
}

u8 BosLstLsrIsFiring(Task* task) {
    LstLsrWork* s;
    u8 result;

    s = task->work;
    result = 0;

    switch (s->state) {
    case 2:
    case 3:
        result = 1;
        break;
    }

    return result;
}

void BosLstLsrFire(Task* task, Vec3* a, Vec3* b, s32 c, u16 d) {
    LstLsrWork* s;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;

    s = task->work;
    s->state = 1;
    s->angle = c;
    s->delay = d;
    s->pos = *a;
    s->pos2 = *b;
    WorldToScreen(&x1, &y1, s->pos.x, s->pos.y, s->pos.z);
    WorldToScreen(&x2, &y2, s->pos2.x, s->pos2.y, s->pos2.z);
    s->duration = (s16)BosLstLsrSqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) / 16;

    if (s->duration <= 1) {
        s->duration = 2;
    }

    s->timer = 0;
}

void BosLstLsrStop(Task* task) {
    LstLsrWork* w;

    w = task->work;
    w->state = 0;
    w->timer = 0;
    AnimStart(&w->anim, 4, 0);
}

u8 BosLstLsrSpawnFal(LstLsrWork* work) {
    LstFalArg arg;
    u8 result;

    result = 0;

    if (work->kind != 0) {
        return 0;
    }

    if ((s16)*work->falCount <= 31) {
        arg.kind = 0;
        arg.x = work->pos2.x;
        arg.y = work->pos2.y;
        arg.z = work->pos2.z;
        arg.facing = *work->facing;
        arg.falCount = work->falCount;
        TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosLstFal, &arg);
        result = 1;
    }

    return result;
}

void task_bos_lst_lsr_0(LstLsrWork* work, LstLsrArg* arg) {
    work->kind = arg->kind;
    work->facing = arg->facing;
    work->falCount = arg->falCount;
    work->state = 0;
    work->tiles = LoadObjTiles(gUnk_09CD0334, 0x900);
    work->palette = LoadObjPalette(gUnk_09D69594, 0x60);
    AnimInit(&work->anim, gUnk_09EFBF18, gUnk_09EFBEC4);
    AnimStart(&work->anim, 4, 0);
}

u8 task_bos_lst_lsr_1(LstLsrWork* work) {
    switch (work->state) {
    case 0:
        break;
    case 1:
        work->delay--;

        if (work->delay > 0) {
            break;
        }

        work->state = 2;
        work->delay = 0;
    case 2:
        work->timer++;

        if (work->timer >= work->duration) {
            work->state = 3;
            work->timer = 0;
            AnimReset(&work->anim);
            AnimChange(&work->anim, 6, ANIM_FLAG_LOOP);
        }

        break;
    case 3:
        if (work->timer > 15) {
            work->state = 0;
            work->timer = 0;
            AnimChange(&work->anim, 4, 0);
        } else {
            ApplyAttackBox(0x10D, work->pos2.x, work->pos2.y, work->pos2.z, 8, 8, 8);

            if ((work->timer & 3) == 0) {
                BosLstLsrSpawnFal(work);
            }

            if (abs(work->pos2.x - gBtlWork->actor->x) < 384) {
                work->pos2.x = gBtlWork->actor->x;
            } else if (work->pos2.x > gBtlWork->actor->x) {
                work->pos2.x = work->pos2.x - 384;
            } else if (work->pos2.x < gBtlWork->actor->x) {
                work->pos2.x = work->pos2.x + 384;
            }

            if (abs(work->pos2.y - gBtlWork->actor->y) < 384) {
                work->pos2.y = gBtlWork->actor->y;
            } else if (work->pos2.y > gBtlWork->actor->y) {
                work->pos2.y = work->pos2.y - 384;
            } else if (work->pos2.y < gBtlWork->actor->y) {
                work->pos2.y = work->pos2.y + 384;
            }

            work->timer++;
        }

        break;
    }

    AnimUpdate(&work->anim);

    return 1;
}

void task_bos_lst_lsr_2(LstLsrWork* work) {
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    u16 z;
    u16 x;
    u16 y;
    u16 prio;
    void* gfx;
    ObjAffine* oam;

    switch (work->state) {
    case 2:
        WorldToScreen(&x1, &y1, work->pos2.x, work->pos2.y, work->pos2.z);
        prio = GetBattleSpritePriorityFlags(work->pos2.y);
        z = -0x1004 - (work->pos2.y >> 8) * 4;
        WorldToScreen(&x2, &y2, work->pos.x, work->pos.y, work->pos.z);
        oam = AllocObjAffineAngle(work->angle, 1);
        x = x2 + (x1 - x2) * work->timer / work->duration;
        y = y2 + (y1 - y2) * work->timer / work->duration;
        DrawSprite(x, y, gUnk_09EFBEC4[13], work->tiles, work->palette,
                   oam, prio, z);
        break;
    case 3:
        WorldToScreen(&x1, &y1, work->pos2.x, work->pos2.y, work->pos2.z);
        prio = GetBattleSpritePriorityFlags(work->pos2.y);
        z = -0x1004 - (work->pos2.y >> 8) * 4;
        oam = AllocObjAffine(0, 0x100 - work->timer * 8, work->timer * 16 + 0x100, 1);
        gfx = AnimGetGfx(&work->anim);
        DrawSprite(x1, y1, gfx, work->tiles, work->palette,
                   oam, prio | 4, z);
        break;
    }
}

void task_bos_lst_lsr_3(LstLsrWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}
