/**
 * bos_lst_ctr.c
 * Marluxia Final Form Projectiles
 */

#include "bos7.h"
#include "sprites_bos7.h"
#include "sprites_bos6.h"
#include "songs.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "bos7_api.h"
#include "btl_collision.h"
#include "engine_math.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"

const EmyKind gBosLstCtrEmyKind = { 0, 1, 8, 8, 0, 128, 0 };

static const u32 sBosLstCtrAngles[6][5] = {
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 128, 0, 0, 0 },
    { 0, 86, 171, 0, 0 },
    { 0, 64, 128, 192, 0 },
    { 0, 51, 102, 153, 204 },
};

TaskDesc gTaskDescBosLstCtr = {
    "task_bos_lst_ctr",
    (TaskInitFunc)task_bos_lst_ctr_0,
    (TaskUpdateFunc)task_bos_lst_ctr_1,
    (TaskDrawFunc)task_bos_lst_ctr_2,
    (TaskDestroyFunc)task_bos_lst_ctr_3,
    sizeof(LstCtrWork),
};

s32 BosLstCtrSquare(s32 x) {
    return x * x;
}

s32 BosLstCtrSquare2(s32 x) {
    return x * x;
}

u8 BosLstCtrIsActive(Task* task) {
    LstCtrWork* s;

    s = task->work;
    return s->state != 4;
}

s32 BosLstCtrSqrt(s32 n) {
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

void task_bos_lst_ctr_0(LstCtrWork* work, LstCtrArg* arg) {
    work->unk_000 = arg->unk_00;
    work->count = arg->count;
    work->index = arg->index;
    work->state = 0;
    work->unk_00A = 0;
    work->timer = 0;
    work->delay = arg->delay;
    work->offsetX = 0;
    work->offsetY = 0;
    work->offsetZ = 0;
    work->curX = arg->x;
    work->curY = arg->y;
    work->curZ = arg->z;
    work->x = arg->x;
    work->y = arg->y;
    work->z = arg->z;
    work->tiles = LoadObjTiles(gUnk_09C5C704, 0x500);
    work->palette = LoadObjPalette(gUnk_09D69594, 0x60);
    AnimInit(&work->anim, gUnk_09EFAF50, gUnk_09EFAF24);
    AnimStart(&work->anim, 3, ANIM_FLAG_LOOP);
}

u8 task_bos_lst_ctr_1(LstCtrWork* work) {
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    BtlObj* p;
    s32 c;

    work->offsetX /= 2;
    work->offsetY /= 2;
    work->offsetZ /= 2;

    switch (work->state) {
    case 0:
        c = (u16)work->timer + 1;
        work->timer = c;
        work->delay--;

        if (work->delay <= 0) {
            p = gBtlWork->actor;
            work->x2 = work->curX - (work->curX - p->x) / 4;
            work->y2 = p->y;
            work->z2 = -0x1000;
            work->state = 1;
            work->unk_00A = 0;
            work->timer = 0;
            work->delay = 0;
            WorldToScreen(&x1, &y1, work->x, work->y, work->z);
            WorldToScreen(&x2, &y2, work->x2, work->y2, work->z2);
            work->unk_010 = 0;
            work->duration = (s16)BosLstCtrSqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) / 9;
        } else {
            work->offsetX =
                (-COS(sBosLstCtrAngles[work->count][work->index] + c) * 5 >> 6) << 8;
            work->offsetZ =
                ((SIN(sBosLstCtrAngles[work->count][work->index] + c) * 3 >> 5) - 4) << 8;
        }

        break;
    case 1:
        work->curX = work->x - (work->x - work->x2) * work->timer / work->duration;
        work->curY = work->y + (work->y2 - work->y) * work->timer / work->duration;
        work->curZ = work->z + (work->z2 - work->z) * work->timer / work->duration;
        work->timer++;

        if (work->timer >= work->duration) {
            work->state = 2;
            work->unk_00A = 0;
            work->timer = 0;
            work->delay = 0;
        }

        if (ApplyAttackBox(0x10F, work->curX, work->curY, work->curZ, 8, 1, 4) != 0) {
            m4aSongNumStart(SONG_EF_DS_ANKOKUPUNCH);
        }

        break;
    case 2:
        work->timer++;

        if (work->timer > 2) {
            work->state = 3;
            work->unk_00A = 0;
            work->timer = 0;
            work->delay = 0;
            work->curX = work->x2;
            work->curY = work->y2;
            work->curZ = work->z2;
            AnimStart(&work->anim, 1, 0);
            m4aSongNumStart(SONG_SND_710);
        }

        break;
    case 3:
        if (work->x > work->x2) {
            work->unk_010 = 0;
            work->curX = work->curX - 0x600;

            if (work->curX < 0x6000) {
                work->state = 4;
                work->unk_00A = 0;
                work->timer = 0;
                work->delay = 0;
            }
        } else {
            work->unk_010 = 0x80;
            work->curX = work->curX + 0x600;

            if (work->curX > 0x19000) {
                work->state = 4;
                work->unk_00A = 0;
                work->timer = 0;
                work->delay = 0;
            }
        }

        work->curZ = work->z2 - ((work->timer >> 2) << 8);

        if (ApplyAttackBox(0x10F, work->curX, work->curY, work->curZ, 8, 4, 4) != 0) {
            m4aSongNumStart(SONG_EF_DS_ANKOKUPUNCH);
        }

        work->timer++;
        break;
    case 4:
        AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);
        break;
    }

    AnimUpdate(&work->anim);

    return 1;
}

void task_bos_lst_ctr_2(LstCtrWork* work) {
    s16 x;
    s16 y;
    ObjAffine* affine;
    u16 prio;
    u16 z;
    void* gfx;
    s32 d;

    WorldToScreen(&x, &y, work->curX + work->offsetX, work->curY + work->offsetY,
                  work->curZ + work->offsetZ);
    affine = NULL;
    prio = GetBattleSpritePriorityFlags(work->curY + work->offsetY) | 4;
    z = -0x1004 - ((work->curY + work->offsetY) >> 8) * 4;

    switch (work->state) {
    case 0:
        d = work->timer - work->index * 8;

        if (d <= 0) {
            return;
        }

        if (d <= 15) {
            affine = AllocObjAffine(0, 0x100, d * 16, 0);
        }

        break;
    case 1:
        affine = AllocObjAffine(0, 0x100 - work->timer * 4, 0x100 - work->timer * 4, 1);
        break;
    case 2:
        affine = AllocObjAffine(0, 0x100 - (work->duration - work->timer) * 4,
                                0x100 - work->duration * 4, 1);
        break;
    default:
        if (work->curX + work->offsetX > work->x2) {
            prio |= 1;
        }

        break;
    }

    gfx = AnimGetGfx(&work->anim);
    DrawSprite(x, y, gfx, work->tiles, work->palette, affine, prio, z);
}

void task_bos_lst_ctr_3(LstCtrWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}
