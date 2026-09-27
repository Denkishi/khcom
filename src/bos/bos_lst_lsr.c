#include "bos7.h"
#include "sprites_bos7.h"
#include "sprites_bos6.h"

TaskDesc gTaskDescBosLstLsr = {
    "task_bos_lst_lsr",
    (TaskInitFunc)task_bos_lst_lsr_0,
    (TaskUpdateFunc)task_bos_lst_lsr_1,
    (TaskFunc)task_bos_lst_lsr_2,
    (TaskFunc)task_bos_lst_lsr_3,
    sizeof(LstLsrWork),
};

s32 func_0811156C(s32 x) {
    return x * x;
}

s32 func_08111574(s32 x) {
    return x * x;
}

s32 func_0811157C(s32 n) {
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

u8 func_081115B4(Task* task) {
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

void func_081115CC(Task* task, Vec3* a, Vec3* b, s32 c, u16 d) {
    LstLsrWork* s;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;

    s = task->work;
    s->state = 1;
    s->angle = c;
    s->unk_012 = d;
    s->pos = *a;
    s->pos2 = *b;
    WorldToScreen(&x1, &y1, s->pos.x, s->pos.y, s->pos.z);
    WorldToScreen(&x2, &y2, s->pos2.x, s->pos2.y, s->pos2.z);
    s->unk_014 = (s16)func_0811157C((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) / 16;

    if (s->unk_014 <= 1) {
        s->unk_014 = 2;
    }

    s->unk_010 = 0;
}

void func_08111660(Task* task) {
    LstLsrWork* w;

    w = task->work;
    w->state = 0;
    w->unk_010 = 0;
    AnimStart(&w->anim, 4, 0);
}

u8 func_08111678(LstLsrWork* work) {
    LstFalArg arg;
    u8 result;

    result = 0;

    if (work->unk_004 != 0) {
        return 0;
    }

    if ((s16)*work->unk_00C <= 31) {
        arg.unk_00 = 0;
        arg.x = work->pos2.x;
        arg.y = work->pos2.y;
        arg.z = work->pos2.z;
        arg.unk_12 = *work->unk_008;
        arg.unk_14 = work->unk_00C;
        TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosLstFal, &arg);
        result = 1;
    }

    return result;
}

void task_bos_lst_lsr_0(LstLsrWork* work, LstLsrArg* arg) {
    work->unk_004 = arg->unk_00;
    work->unk_008 = arg->unk_04;
    work->unk_00C = arg->unk_08;
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
        work->unk_012--;
        if (work->unk_012 > 0) {
            break;
        }
        work->state = 2;
        work->unk_012 = 0;
    case 2:
        work->unk_010++;
        if (work->unk_010 >= work->unk_014) {
            work->state = 3;
            work->unk_010 = 0;
            AnimReset(&work->anim);
            AnimChange(&work->anim, 6, 1);
        }
        break;
    case 3:
        if (work->unk_010 > 15) {
            work->state = 0;
            work->unk_010 = 0;
            AnimChange(&work->anim, 4, 0);
        } else {
            func_08011F78(0x10D, work->pos2.x, work->pos2.y, work->pos2.z, 8, 8, 8);
            if ((work->unk_010 & 3) == 0) {
                func_08111678(work);
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
            work->unk_010++;
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
    s32 oam;

    switch (work->state) {
    case 2:
        WorldToScreen(&x1, &y1, work->pos2.x, work->pos2.y, work->pos2.z);
        prio = GetBattleSpritePriorityFlags(work->pos2.y);
        z = -0x1004 - (work->pos2.y >> 8) * 4;
        WorldToScreen(&x2, &y2, work->pos.x, work->pos.y, work->pos.z);
        oam = AllocObjAffineAngle(work->angle, 1);
        x = x2 + (x1 - x2) * work->unk_010 / work->unk_014;
        y = y2 + (y1 - y2) * work->unk_010 / work->unk_014;
        DrawSprite(x, y, gUnk_09EFBEC4[13], work->tiles, work->palette,
                   oam, prio, z);
        break;
    case 3:
        WorldToScreen(&x1, &y1, work->pos2.x, work->pos2.y, work->pos2.z);
        prio = GetBattleSpritePriorityFlags(work->pos2.y);
        z = -0x1004 - (work->pos2.y >> 8) * 4;
        oam = AllocObjAffine(0, 0x100 - work->unk_010 * 8, work->unk_010 * 16 + 0x100, 1);
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
