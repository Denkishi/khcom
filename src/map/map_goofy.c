#include "map_tasks.h"
#include "sprites_evt.h"
#include "sprite_palettes.h"
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

void MapGoofyCheckTalk(MapGoofyWork* w) {
    if (w->targeted && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;

        if (gGameState.floor == 12 && gMapFloorState.room == MAP_ROOM_EXIT_HALL) {
            CreateCardMessageTask(&w->tasks, 0, 49);
        } else {
            CreateCardMessageTask(&w->tasks, 0, gGoofyTalkMessages[gMapFloorState.progress]);
        }

        w->update = MapGoofyWaitMessage;
    }
}

void MapGoofyWaitMessage(MapGoofyWork* w) {
    if (!IsMessageWindowOpen()) {
        gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
        w->update = MapGoofyCheckTalk;
    }
}

void Task_MapGoofy_0(MapGoofyWork* w) {
    FldObj* e = &w->obj;

    if (gMapFloorState.room != MAP_ROOM_ENTRANCE_HALL) {
        if (gGameState.floor == 12) {
            w->obj.fieldPosition.x = 0x25000;
            w->obj.fieldPosition.y = 0x10A00;
        } else {
            w->obj.fieldPosition.x = 0x20000;
            w->obj.fieldPosition.y = 0xB000;
        }
    } else {
        if (gGameState.floor != 0) {
            w->obj.fieldPosition.x = 0x1E800;
            w->obj.fieldPosition.y = 0xD000;
        } else {
            w->obj.fieldPosition.x = 0x2C000;
            w->obj.fieldPosition.y = 0xE000;
        }
    }

    e->fieldPosition.z = 0;
    e->fieldPosition.ground = GetFldPosFloor(&e->fieldPosition);
    e->fieldPosition.z = e->fieldPosition.ground;
    e->fieldPosition.y -= e->fieldPosition.ground;
    e->angle = 0x80;
    e->height = 0x30;
    e->kind = 2;
    w->visible = 1;
    w->update = MapGoofyCheckTalk;
    w->tiles = AllocObjTiles(0x400, gGoofyFl00Tiles);
    w->palette = LoadObjPalette(gGoofyPalette, 32);
    AnimInit(&w->anim, gGoofyFl00Anims, gGoofyFl00Frames);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    ColliderInit(&w->collider, 4, 16, 48);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    FldObjRegister(e);
    TaskPoolInit(&w->tasks, 2);
    TaskCreate(&w->tasks, &gTaskDescFldShadow, &w->obj);
    w->targeted = 0;
    TaskPoolInit(&w->tasks2, 1);
    TaskCreate(&w->tasks2, &gTaskDescMapTalk, &w->obj);
}

s32 Task_MapGoofy_1(MapGoofyWork* w) {
    if ((u8)IsMapInterrupted()) {
        w->visible = 0;
    } else {
        w->visible = 1;
        w->targeted = IsFldObjTalkTarget(&w->obj);
        TaskPoolUpdate(&w->tasks);
        TaskPoolUpdate(&w->tasks2);
        AnimUpdate(&w->anim);

        if (w->update != NULL) {
            w->update(w);
        }
    }

    return 1;
}

void Task_MapGoofy_2(MapGoofyWork* w) {
    FldPos* p = &w->obj.fieldPosition;
    u16 v;
    s32 k;
    s16 x;
    s16 y;

    if (w->visible) {
        x = (p->x >> 8) - (gFieldState->x >> 8);
        k = p->y >> 8;
        y = k + (p->z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
        w->obj.shadowZ = p->ground;
        w->obj.shadowPriority = v + 1;
        TaskPoolDraw(&w->tasks);

        if (w->targeted) {
            TaskPoolDraw(&w->tasks2);
        }
    }
}

void Task_MapGoofy_3(MapGoofyWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    FldObjUnregister(&w->obj);
    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->tasks2);
}

const u8 gGoofyTalkMessages[28] = {
    25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
    39, 40, 41, 42, 43, 44, 45, 46, 46, 46, 47, 47, 48, 48,
};

TaskDesc gTaskDescMapGoofy = {
    "Task_MapGoofy",
    (TaskInitFunc)Task_MapGoofy_0,
    (TaskUpdateFunc)Task_MapGoofy_1,
    (TaskDrawFunc)Task_MapGoofy_2,
    (TaskDestroyFunc)Task_MapGoofy_3,
    sizeof(MapGoofyWork),
};
