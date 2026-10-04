#include "map_tasks.h"
#include "sprites_map_tasks.h"
#include "sprite_palettes.h"
#include "gba/keys.h"
#include "anim.h"
#include "btl_collision.h"
#include "card_api.h"
#include "field_state.h"
#include "fld_types.h"
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

void MapMickeyCheckTalk(MapMickeyWork* w) {
    if (w->targeted && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;

        switch (gMapFloorState.progress) {
        case 20:
            CreateCardMessageTask(&w->tasks, 0, 0x3F);
            break;
        case 22:
            CreateCardMessageTask(&w->tasks, 0, 0x3D);
            break;
        case 23:
        default:
            CreateCardMessageTask(&w->tasks, 0, 0x3E);
            break;
        }

        w->update = MapMickeyWaitMessage;
    }
}

void MapMickeyWaitMessage(MapMickeyWork* w) {
    if (!IsMessageWindowOpen()) {
        gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
        w->update = MapMickeyCheckTalk;
    }
}

void Task_MapMickey_0(MapMickeyWork* w) {
    FldObj* e = &w->obj;

    e->fieldPosition.x = 0x1C800;
    e->fieldPosition.y = 0xE000;
    w->spriteFlags = SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
    e->fieldPosition.z = 0;
    e->fieldPosition.ground = GetFldPosFloor(&e->fieldPosition);
    e->fieldPosition.z = e->fieldPosition.ground;
    e->fieldPosition.y -= e->fieldPosition.ground;
    e->angle = 0xAD;
    e->height = 0x30;
    e->kind = 2;
    w->visible = 1;
    w->update = MapMickeyCheckTalk;
    w->tiles = AllocObjTiles(0x300, gMickeyFl00Tiles);
    w->palette = LoadObjPalette(gMickeyPalette, 32);
    AnimInit(&w->anim, gMickeyFl00Anims, gMickeyFl00Frames);
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

s32 Task_MapMickey_1(MapMickeyWork* w) {
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

void Task_MapMickey_2(MapMickeyWork* w) {
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
        DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, NULL, w->spriteFlags, v);
        w->obj.shadowZ = p->ground;
        w->obj.shadowPriority = v + 1;
        TaskPoolDraw(&w->tasks);

        if (w->targeted) {
            TaskPoolDraw(&w->tasks2);
        }
    }
}

void Task_MapMickey_3(MapMickeyWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    FldObjUnregister(&w->obj);
    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->tasks2);
}

TaskDesc gTaskDescMapMickey = {
    "Task_MapMickey",
    (TaskInitFunc)Task_MapMickey_0,
    (TaskUpdateFunc)Task_MapMickey_1,
    (TaskDrawFunc)Task_MapMickey_2,
    (TaskDestroyFunc)Task_MapMickey_3,
    sizeof(MapMickeyWork),
};
