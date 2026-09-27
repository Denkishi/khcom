#include "map_tasks.h"
#include "sprites_evt.h"

void func_080F5C60(MapDonaldWork* w) {
    if (w->unk_0C0 != 0 && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= 0x1000;

        if ((s8)gGameState.floor == 12 && gUnk_0203C590.unk_06 == 0xFD) {
            CreateCardMessageTask(&w->tasks, 0, 24);
        } else {
            CreateCardMessageTask(&w->tasks, 0, gUnk_0984C2E4[gUnk_0203C590.unk_00]);
        }

        w->update = func_080F5CDC;
    }
}

void func_080F5CDC(MapDonaldWork* w) {
    if (func_080A42C8() == 0) {
        gFieldState->flags &= ~0x1000;
        w->update = func_080F5C60;
    }
}

void Task_MapDonald_0(MapDonaldWork* w) {
    FldObj* e = &w->obj;

    if (gUnk_0203C590.unk_06 != 0xFE) {
        if ((s8)gGameState.floor == 12) {
            w->obj.fieldPosition.x = 0x22300;
            w->obj.fieldPosition.y = 0xE600;
        } else {
            w->obj.fieldPosition.x = 0x28800;
            w->obj.fieldPosition.y = 0x10000;
        }
    } else {
        if ((s8)gGameState.floor != 0) {
            w->obj.fieldPosition.x = 0x25000;
            w->obj.fieldPosition.y = 0x11000;
        } else {
            w->obj.fieldPosition.x = 0x35000;
            w->obj.fieldPosition.y = 0x12000;
        }
    }

    e->fieldPosition.z = 0;
    e->fieldPosition.unk_0C = func_080DFF30(&e->fieldPosition);
    e->fieldPosition.z = e->fieldPosition.unk_0C;
    e->fieldPosition.y -= e->fieldPosition.unk_0C;
    e->angle = 0x80;
    e->unk_1A = 0x20;
    e->unk_30 = 2;
    w->unk_0C1 = 1;
    w->update = func_080F5C60;
    w->tiles = AllocObjTiles(0x400, gDonaFl00Tiles);
    w->palette = LoadObjPalette(gDonaldPalette, 32);
    AnimInit(&w->anim, gDonaFl00Anims, gDonaFl00Frames);
    AnimStart(&w->anim, 0, 1);
    ColliderInit(&w->collider, 4, 16, 48);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    FldObjRegister(e);
    TaskPoolInit(&w->tasks, 2);
    TaskCreate(&w->tasks, &gTaskDescFldShadow, &w->obj);
    w->unk_0C0 = 0;
    TaskPoolInit(&w->tasks2, 1);
    TaskCreate(&w->tasks2, &gTaskDescMapTalk, &w->obj);
}

s32 Task_MapDonald_1(MapDonaldWork* w) {
    if ((u8)func_080E0390() != 0) {
        w->unk_0C1 = 0;
    } else {
        w->unk_0C1 = 1;
        w->unk_0C0 = func_080E03C0(&w->obj);
        TaskPoolUpdate(&w->tasks);
        TaskPoolUpdate(&w->tasks2);
        AnimUpdate(&w->anim);

        if (w->update != 0) {
            w->update(w);
        }
    }

    return 1;
}

void Task_MapDonald_2(MapDonaldWork* w) {
    FldPos* p = &w->obj.fieldPosition;
    u16 v;
    s32 k;
    s16 x;
    s16 y;

    if (w->unk_0C1 != 0) {
        x = (p->x >> 8) - (gFieldState->x >> 8);
        k = p->y >> 8;
        y = k + (p->z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, 0x800, v);
        w->obj.unk_3C = p->unk_0C;
        w->obj.unk_3A = v + 1;
        TaskPoolDraw(&w->tasks);

        if (w->unk_0C0 != 0) {
            TaskPoolDraw(&w->tasks2);
        }
    }
}

void Task_MapDonald_3(MapDonaldWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    FldObjUnregister(&w->obj);
    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->tasks2);
}

const u8 gUnk_0984C2E4[28] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
    14, 15, 16, 17, 18, 19, 20, 21, 21, 21, 22, 22, 23, 23,
};

const char gTaskNameMapDonald[] = "Task_MapDonald";

TaskDesc gTaskDescMapDonald = {
    gTaskNameMapDonald,
    (TaskInitFunc)Task_MapDonald_0,
    (TaskUpdateFunc)Task_MapDonald_1,
    (TaskFunc)Task_MapDonald_2,
    (TaskFunc)Task_MapDonald_3,
    sizeof(MapDonaldWork),
};
