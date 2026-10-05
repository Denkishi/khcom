/**
 * bos_lst_fal.c
 * Marluxia Final Form Falling Particles
 */

#include "bos7.h"
#include "sprites_bos7.h"
#include "sprites_bos6.h"
#include "anim.h"
#include "battle_actor.h"
#include "bos7_api.h"
#include "engine_math.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

static const LstFalAnim sBosLstFalAnims[8] = { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }, { 5, 0 } };

TaskDesc gTaskDescBosLstFal = {
    "task_bos_lst_fal",
    (TaskInitFunc)task_bos_lst_fal_0,
    (TaskUpdateFunc)task_bos_lst_fal_1,
    (TaskDrawFunc)task_bos_lst_fal_2,
    (TaskDestroyFunc)task_bos_lst_fal_3,
    sizeof(LstFalWork),
};

s32 BosLstFalSquare(s32 x) {
    return x * x;
}

s32 BosLstFalSquare2(s32 x) {
    return x * x;
}

void task_bos_lst_fal_0(LstFalWork* work, LstFalArg* arg) {
    u16 anim;

    anim = sBosLstFalAnims[GetRandom() & 7].anim;
    work->kind = arg->kind;
    work->x = arg->x;
    work->y = arg->y;
    work->z = arg->z;
    work->vx = (GetRandom() % 0x181 + 0x80) * arg->facing;
    work->vz = GetRandom() % 0xC1 + 0x40;
    work->lift = GetRandom() % 0x81 + 0x80;

    switch (arg->kind) {
    case 1:
        if ((GetRandom() & 1) != 0) {
            work->vx = work->vx * 512 >> 8;
            work->vz = work->vz * 384 >> 8;
            work->lift = GetRandom() % 0x81 + 0x380;
        }

        break;
    case 2:
        work->vz = GetRandom() % 0x81 + 0x180;
        break;
    case 3:
        work->vx = work->vx * 640 >> 8;
        break;
    case 4:
        work->vx = (-gSineTable[arg->angle + 0x40] << 8) / 256;
        work->vz = (gSineTable[arg->angle] << 8) / 256;
        break;
    case 5:
        work->vx = GetRandom() % 0x201 - 0x100;
        work->vz = GetRandom() % 0xC1 + 0xC0;
        work->lift = GetRandom() % 0x381 + 0x80;
        break;
    }

    switch (anim) {
    case 4:
    case 5:
        work->vx = work->vx * 320 >> 8;
        work->vz = work->vz * 320 >> 8;
        break;
    }

    work->falCount = arg->falCount;
    (*work->falCount)++;
    work->tiles = LoadObjTiles(gBosLstFalTiles, 0x700);
    work->palette = LoadObjPalette(gBosLstObjPalette, 0x60);
    AnimInit(&work->anim, gBosLstFalAnims, gBosLstFalFrames);
    AnimStart(&work->anim, anim, ANIM_FLAG_LOOP);
}

u8 task_bos_lst_fal_1(LstFalWork* work) {
    u16 x;
    s16 y;
    u8 result;
    s32 d;

    result = 1;
    work->x += work->vx;
    work->z += work->vz;

    if (work->kind != 4) {
        if (work->lift > 0) {
            d = 512;

            if (work->lift <= 512) {
                d = work->lift;
            }

            work->z -= d;
            work->lift = work->lift - 25;
        } else {
            work->lift = GetRandom() % 0x41 + 0x40;
        }
    }

    WorldToScreen((s16*)&x, &y, work->x, work->y, work->z);

    if ((u16)(x + 16) > 272 || y < -64 || y > 224) {
        result = 0;
    }

    AnimUpdate(&work->anim);

    return result;
}

void task_bos_lst_fal_2(LstFalWork* work) {
    s16 x;
    s16 y;
    void* gfx;
    u16 prio;

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    gfx = AnimGetGfx(&work->anim);
    prio = GetBattleSpritePriorityFlags(work->y) | 4;
    DrawSprite(x, y, gfx, work->tiles, work->palette, NULL, prio,
               -0x1004 - (work->y >> 8) * 4);
}

void task_bos_lst_fal_3(LstFalWork* work) {
    if (work->tiles != NULL) {
        ReleaseObjTiles(work->tiles);
    }

    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
    }

    (*work->falCount)--;
}
