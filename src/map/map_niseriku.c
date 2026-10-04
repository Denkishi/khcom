#include "map_tasks.h"
#include "sprites_evt.h"
#include "sprites_map_tasks.h"
#include "sprite_palettes.h"
#include "gba/keys.h"
#include "fade.h"
#include "engine_math.h"
#include "anim.h"
#include "btl_collision.h"
#include "card_api.h"
#include "field_state.h"
#include "fld_types.h"
#include "key.h"
#include "map.h"
#include "map_api.h"
#include "map_types.h"
#include "msg_api.h"
#include "obj.h"
#include "obj_api.h"
#include "registration_data.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

void MapNiserikuCheckTalk(MapNiserikuWork* w) {
    if (w->targeted && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        CreateCardMessageTask(&w->tasks, 0, 0x34);
        w->update = MapNiserikuWaitMessage;
    }
}

void MapNiserikuWaitMessage(MapNiserikuWork* w) {
    if (!IsMessageWindowOpen()) {
        gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
        w->update = MapNiserikuCheckTalk;
    }
}

void MapNiserikuWaitApproach(MapNiserikuWork* w) {
    s32 dx;
    s32 dy;

    dx = w->obj.fieldPosition.x - gFieldState->actor.fieldPosition.x;

    if (dx < 0) {
        dx = gFieldState->actor.fieldPosition.x - w->obj.fieldPosition.x;
    }

    dy = w->obj.fieldPosition.y - gFieldState->actor.fieldPosition.y;

    if (dy < 0) {
        dy = gFieldState->actor.fieldPosition.y - w->obj.fieldPosition.y;
    }

    if (dx <= 0x8000 && dy <= 0x8000) {
        if (Sqrt8((dx * dx >> 8) + (dy * dy >> 8)) < 0x3000) {
            FadeStartOut(FADE_MODE_BLACK, 16);
            gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
            w->update = MapNiserikuStartEvent;
        }
    }
}

void MapNiserikuStartEvent(MapNiserikuWork* w) {
    if (!FadeIsActive()) {
        RequestEventMode(0x3B);
        w->update = NULL;
    }
}

void Task_MapNiseriku_0(MapNiserikuWork* w) {
    FldObj* e = &w->obj;
    s32 c;

    switch (gMapFloorState.progress) {
    case 27:
        e->fieldPosition.x = 0x27C00;
        e->fieldPosition.y = 0x10700;
        break;
    case 23:
        e->fieldPosition.x = 0x24900;
        e->fieldPosition.y = 0xD500;
        break;
    case 24:
    case 25:
    case 26:
    default:
        e->fieldPosition.x = 0x17A00;
        e->fieldPosition.y = 0x11000;
        break;
    }

    e->fieldPosition.z = 0;
    e->fieldPosition.z = e->fieldPosition.ground = GetFldPosFloor(&e->fieldPosition);
    e->fieldPosition.y -= e->fieldPosition.z;
    e->angle = 173;
    e->height = 48;
    e->kind = 2;

    c = 0;

    if (gMapFloorState.progress == 27) {
        c = 1;
    }

    w->registered = c;

    w->visible = 1;
    w->targeted = 0;
    TaskPoolInit(&w->tasks2, 1);
    TaskCreate(&w->tasks2, &gTaskDescMapTalk, &w->obj);
    TaskPoolInit(&w->tasks, 2);

    switch (gMapFloorState.progress) {
    case 27:
        w->update = MapNiserikuCheckTalk;
        w->tiles = AllocObjTiles(0x680, gNiseFl00Tiles);
        w->palette = LoadObjPalette(gNiserikuPalette, 32);
        AnimInit(&w->anim, gNiseFl00Anims, gNiseFl00Frames);
        AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
        ColliderInit(&w->collider, 4, 16, 48);
        ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
        TaskCreate(&w->tasks, &gTaskDescFldShadow, &w->obj);
        break;
    case 23:
        w->update = MapNiserikuWaitApproach;
        w->tiles = AllocObjTiles(0x320, gNiserikuHizaFTiles);
        w->palette = LoadObjPalette(gNiserikuPalette, 32);
        AnimInit(&w->anim, gNiserikuHizaFAnims, gNiserikuHizaFFrames);
        AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
        ColliderInit(&w->collider, 4, 16, 48);
        ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
        TaskCreate(&w->tasks, &gTaskDescFldShadow, &w->obj);
        break;
    case 24:
    case 25:
    case 26:
    default:
        w->update = NULL;
        w->tiles = AllocObjTiles(0x300, gNiserikuDownFTiles);
        w->palette = LoadObjPalette(gNiserikuPalette, 32);
        AnimInit(&w->anim, gNiserikuDownFAnims, gNiserikuDownFFrames);
        AnimStart(&w->anim, 1, ANIM_FLAG_LOOP);
        ColliderInit(&w->collider, 4, 36, 48);
        ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
        break;
    }

    if (w->registered) {
        FldObjRegister(e);
    }
}

s32 Task_MapNiseriku_1(MapNiserikuWork* w) {
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

void Task_MapNiseriku_2(MapNiserikuWork* w) {
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

void Task_MapNiseriku_3(MapNiserikuWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);

    if (w->registered) {
        FldObjUnregister(&w->obj);
    }

    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->tasks2);
}

TaskDesc gTaskDescMapNiseriku = {
    "Task_MapNiseriku",
    (TaskInitFunc)Task_MapNiseriku_0,
    (TaskUpdateFunc)Task_MapNiseriku_1,
    (TaskDrawFunc)Task_MapNiseriku_2,
    (TaskDestroyFunc)Task_MapNiseriku_3,
    sizeof(MapNiserikuWork),
};
