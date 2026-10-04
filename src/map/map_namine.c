#include "map_tasks.h"
#include "sprites_evt.h"
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

void MapNamineCheckTalk(MapNamineWork* w) {
    if (w->targeted && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;

        if (gMapFloorState.progress == 27) {
            CreateCardMessageTask(&w->tasks, 0, 0x33);
        } else {
            CreateCardMessageTask(&w->tasks, 0, 0x32);
        }

        w->update = MapNamineWaitMessage;
    }
}

void MapNamineWaitMessage(MapNamineWork* w) {
    if (!IsMessageWindowOpen()) {
        gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
        w->update = MapNamineCheckTalk;
    }
}

void Task_MapNamine_0(MapNamineWork* w) {
    FldObj* p = &w->obj;

    switch (gMapFloorState.progress) {
    case 27:
        w->obj.fieldPosition.x = 0x20D00;
        w->obj.fieldPosition.y = 0xD500;
        w->spriteFlags = SPRITE_PRIORITY(2);
        break;
    case 23:
        w->obj.fieldPosition.x = 0x27C00;
        w->obj.fieldPosition.y = 0xD400;
        w->spriteFlags = SPRITE_PRIORITY(2);
        break;
    case 24:
    case 25:
    case 26:
    default:
        p->fieldPosition.x = 0x15200;
        p->fieldPosition.y = 0xF800;
        w->spriteFlags = SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
        break;
    }

    p->fieldPosition.z = 0;
    p->fieldPosition.z = p->fieldPosition.ground = GetFldPosFloor(&p->fieldPosition);
    p->fieldPosition.y -= p->fieldPosition.ground;
    p->angle = 173;
    p->height = 48;
    p->kind = 2;
    w->registered = gMapFloorState.progress != 23;
    w->visible = 1;
    w->update = MapNamineCheckTalk;
    w->tiles = AllocObjTiles(0x300, gNamiF00Tiles);
    w->palette = LoadObjPalette(gNaminePalette, 32);
    AnimInit(&w->anim, gNamiF00Anims, gNamiF00Frames);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    ColliderInit(&w->collider, 4, 16, 48);
    ColliderSetPosition(&w->collider, p->fieldPosition.x, p->fieldPosition.y, p->fieldPosition.z);

    if (w->registered) {
        FldObjRegister(p);
    }

    TaskPoolInit(&w->tasks, 2);
    TaskCreate(&w->tasks, &gTaskDescFldShadow, &w->obj);
    w->targeted = 0;
    TaskPoolInit(&w->tasks2, 1);
    TaskCreate(&w->tasks2, &gTaskDescMapTalk, &w->obj);
}

s32 Task_MapNamine_1(MapNamineWork* w) {
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

void Task_MapNamine_2(MapNamineWork* w) {
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

void Task_MapNamine_3(MapNamineWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);

    if (w->registered) {
        FldObjUnregister(&w->obj);
    }

    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->tasks2);
}

TaskDesc gTaskDescMapNamine = {
    "Task_MapNamine",
    (TaskInitFunc)Task_MapNamine_0,
    (TaskUpdateFunc)Task_MapNamine_1,
    (TaskDrawFunc)Task_MapNamine_2,
    (TaskDestroyFunc)Task_MapNamine_3,
    sizeof(MapNamineWork),
};
