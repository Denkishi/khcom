#include "map_tasks.h"
#include "sprites_evt.h"
#include "gba/keys.h"
#include "anim.h"
#include "btl_collision.h"
#include "card_api.h"
#include "field_state.h"
#include "fld_types.h"
#include "game_state.h"
#include "key.h"
#include "map.h"
#include "map_api.h"
#include "map_types.h"
#include "obj.h"
#include "obj_api.h"
#include "registration_data.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

void MapDonaldCheckTalk(MapDonaldWork* work) {
    if (work->targeted && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;

        if (gGameState.floor == 12 && gMapFloorState.room == MAP_ROOM_EXIT_HALL) {
            CreateCardMessageTask(&work->tasks, 0, 24);
        } else {
            CreateCardMessageTask(&work->tasks, 0, gDonaldTalkMessages[gMapFloorState.progress]);
        }

        work->update = MapDonaldWaitMessage;
    }
}

void MapDonaldWaitMessage(MapDonaldWork* work) {
    if (!IsMessageWindowOpen()) {
        gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
        work->update = MapDonaldCheckTalk;
    }
}

void Task_MapDonald_0(MapDonaldWork* work) {
    FldObj* e = &work->obj;

    if (gMapFloorState.room != MAP_ROOM_ENTRANCE_HALL) {
        if (gGameState.floor == 12) {
            work->obj.fieldPosition.x = 0x22300;
            work->obj.fieldPosition.y = 0xE600;
        } else {
            work->obj.fieldPosition.x = 0x28800;
            work->obj.fieldPosition.y = 0x10000;
        }
    } else {
        if (gGameState.floor != 0) {
            work->obj.fieldPosition.x = 0x25000;
            work->obj.fieldPosition.y = 0x11000;
        } else {
            work->obj.fieldPosition.x = 0x35000;
            work->obj.fieldPosition.y = 0x12000;
        }
    }

    e->fieldPosition.z = 0;
    e->fieldPosition.ground = GetFldPosFloor(&e->fieldPosition);
    e->fieldPosition.z = e->fieldPosition.ground;
    e->fieldPosition.y -= e->fieldPosition.ground;
    e->angle = 0x80;
    e->height = 0x20;
    e->kind = 2;
    work->visible = 1;
    work->update = MapDonaldCheckTalk;
    work->tiles = AllocObjTiles(0x400, gDonaFl00Tiles);
    work->palette = LoadObjPalette(gDonaldPalette, 32);
    AnimInit(&work->anim, gDonaFl00Anims, gDonaFl00Frames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    ColliderInit(&work->collider, 4, 16, 48);
    ColliderSetPosition(&work->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    FldObjRegister(e);
    TaskPoolInit(&work->tasks, 2);
    TaskCreate(&work->tasks, &gTaskDescFldShadow, &work->obj);
    work->targeted = 0;
    TaskPoolInit(&work->tasks2, 1);
    TaskCreate(&work->tasks2, &gTaskDescMapTalk, &work->obj);
}

s32 Task_MapDonald_1(MapDonaldWork* work) {
    if ((u8)IsMapInterrupted()) {
        work->visible = 0;
    } else {
        work->visible = 1;
        work->targeted = IsFldObjTalkTarget(&work->obj);
        TaskPoolUpdate(&work->tasks);
        TaskPoolUpdate(&work->tasks2);
        AnimUpdate(&work->anim);

        if (work->update != NULL) {
            work->update(work);
        }
    }

    return 1;
}

void Task_MapDonald_2(MapDonaldWork* work) {
    FldPos* p = &work->obj.fieldPosition;
    u16 v;
    s32 k;
    s16 x;
    s16 y;

    if (work->visible) {
        x = (p->x >> 8) - (gFieldState->x >> 8);
        k = p->y >> 8;
        y = k + (p->z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
        work->obj.shadowZ = p->ground;
        work->obj.shadowPriority = v + 1;
        TaskPoolDraw(&work->tasks);

        if (work->targeted) {
            TaskPoolDraw(&work->tasks2);
        }
    }
}

void Task_MapDonald_3(MapDonaldWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
    FldObjUnregister(&work->obj);
    TaskPoolDestroy(&work->tasks);
    TaskPoolDestroy(&work->tasks2);
}

const u8 gDonaldTalkMessages[28] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
    14, 15, 16, 17, 18, 19, 20, 21, 21, 21, 22, 22, 23, 23,
};

TaskDesc gTaskDescMapDonald = {
    "Task_MapDonald",
    (TaskInitFunc)Task_MapDonald_0,
    (TaskUpdateFunc)Task_MapDonald_1,
    (TaskDrawFunc)Task_MapDonald_2,
    (TaskDestroyFunc)Task_MapDonald_3,
    sizeof(MapDonaldWork),
};
