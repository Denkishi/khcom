#include "bos7.h"
#include "sprites_bos7.h"
#include "sprites_bos6.h"

TaskDesc gTaskDescBosLstPtl = {
    "task_bos_lst_ptl",
    (TaskInitFunc)task_bos_lst_ptl_0,
    (TaskUpdateFunc)task_bos_lst_ptl_1,
    (TaskFunc)task_bos_lst_ptl_2,
    (TaskFunc)task_bos_lst_ptl_3,
    sizeof(LstPtlWork),
};

s32 func_081119F8(s32 x) {
    return x * x;
}

s32 func_08111A00(s32 x) {
    return x * x;
}

u8 func_08111A08(Task* task) {
    LstPtlWork* s;

    s = task->work;
    return s->state != 2;
}

void task_bos_lst_ptl_0(LstPtlWork* work, LstPtlArg* arg) {
    work->state = 0;
    work->unk_002 = 0;
    work->unk_004 = 0;
    work->unk_006 = arg->unk_00;
    work->unk_008 = arg->unk_04;
    work->unk_00C = arg->unk_08;
    work->unk_010 = 0;
    work->unk_014 = 0;
    work->tiles = LoadObjTiles(gUnk_09CD0C34, 0x200);
    work->palette = LoadObjPalette(gUnk_09D69594, 0x60);
    AnimInit(&work->anim, gUnk_09EFBF54, gUnk_09EFBF40);
    AnimStart(&work->anim, 0, 1);
}

u8 task_bos_lst_ptl_1(LstPtlWork* work) {
    u8 result;

    result = 1;

    switch (work->state) {
    case 0:
        work->unk_006--;
        if (work->unk_006 <= 0) {
            work->state = 1;
            work->unk_002 = 0;
            work->unk_004 = 0;
            work->unk_006 = 0;
            AnimReset(&work->anim);
            AnimChange(&work->anim, 1, 1);
        }
        break;
    case 1:
        work->unk_008 -= 0x80;
        work->unk_00C += 0x100;
        work->unk_010 = -gSineTable[((work->unk_004 * 8) & 0xFF) + 0x40];
        work->unk_014 = gSineTable[(work->unk_004 * 2) & 0xFF];
        work->unk_004++;
        if ((work->unk_00C >> 8) > 0xA8) {
            work->state = 2;
            work->unk_002 = 0;
            work->unk_004 = 0;
            work->unk_006 = 0;
        }
        break;
    case 2:
        AnimReset(&work->anim);
        AnimChange(&work->anim, 0, 1);
        break;
    }

    AnimUpdate(&work->anim);

    return result;
}

void task_bos_lst_ptl_2(LstPtlWork* work) {
    u16 x;
    u16 y;
    u16 prio;
    void* gfx;
    u16 z;

    x = (work->unk_008 >> 8) + (work->unk_010 * 12 >> 8);
    y = (work->unk_00C >> 8) + (work->unk_014 * 6 >> 8);
    prio = GetBattleSpritePriorityFlags(0x20100);
    z = 0xE7F8;
    gfx = AnimGetGfx(&work->anim);
    DrawSprite(x, y, gfx, work->tiles, work->palette, 0, prio, z);
}

void task_bos_lst_ptl_3(LstPtlWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}
