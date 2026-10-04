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

void MapNiserikuCheckTalk(MapNiserikuWork* work) {
    if (work->targeted && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        CreateCardMessageTask(&work->tasks, 0, 0x34);
        work->update = MapNiserikuWaitMessage;
    }
}

void MapNiserikuWaitMessage(MapNiserikuWork* work) {
    if (!IsMessageWindowOpen()) {
        gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
        work->update = MapNiserikuCheckTalk;
    }
}

void MapNiserikuWaitApproach(MapNiserikuWork* work) {
    s32 dx;
    s32 dy;

    dx = work->obj.fieldPosition.x - gFieldState->actor.fieldPosition.x;

    if (dx < 0) {
        dx = gFieldState->actor.fieldPosition.x - work->obj.fieldPosition.x;
    }

    dy = work->obj.fieldPosition.y - gFieldState->actor.fieldPosition.y;

    if (dy < 0) {
        dy = gFieldState->actor.fieldPosition.y - work->obj.fieldPosition.y;
    }

    if (dx <= 0x8000 && dy <= 0x8000) {
        if (Sqrt8((dx * dx >> 8) + (dy * dy >> 8)) < 0x3000) {
            FadeStartOut(FADE_MODE_BLACK, 16);
            gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
            work->update = MapNiserikuStartEvent;
        }
    }
}

void MapNiserikuStartEvent(MapNiserikuWork* work) {
    if (!FadeIsActive()) {
        RequestEventMode(0x3B);
        work->update = NULL;
    }
}

void Task_MapNiseriku_0(MapNiserikuWork* work) {
    FldObj* e = &work->obj;
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

    work->registered = c;

    work->visible = 1;
    work->targeted = 0;
    TaskPoolInit(&work->tasks2, 1);
    TaskCreate(&work->tasks2, &gTaskDescMapTalk, &work->obj);
    TaskPoolInit(&work->tasks, 2);

    switch (gMapFloorState.progress) {
    case 27:
        work->update = MapNiserikuCheckTalk;
        work->tiles = AllocObjTiles(0x680, gNiseFl00Tiles);
        work->palette = LoadObjPalette(gNiserikuPalette, 32);
        AnimInit(&work->anim, gNiseFl00Anims, gNiseFl00Frames);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        ColliderInit(&work->collider, 4, 16, 48);
        ColliderSetPosition(&work->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
        TaskCreate(&work->tasks, &gTaskDescFldShadow, &work->obj);
        break;
    case 23:
        work->update = MapNiserikuWaitApproach;
        work->tiles = AllocObjTiles(0x320, gNiserikuHizaFTiles);
        work->palette = LoadObjPalette(gNiserikuPalette, 32);
        AnimInit(&work->anim, gNiserikuHizaFAnims, gNiserikuHizaFFrames);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        ColliderInit(&work->collider, 4, 16, 48);
        ColliderSetPosition(&work->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
        TaskCreate(&work->tasks, &gTaskDescFldShadow, &work->obj);
        break;
    case 24:
    case 25:
    case 26:
    default:
        work->update = NULL;
        work->tiles = AllocObjTiles(0x300, gNiserikuDownFTiles);
        work->palette = LoadObjPalette(gNiserikuPalette, 32);
        AnimInit(&work->anim, gNiserikuDownFAnims, gNiserikuDownFFrames);
        AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
        ColliderInit(&work->collider, 4, 36, 48);
        ColliderSetPosition(&work->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
        break;
    }

    if (work->registered) {
        FldObjRegister(e);
    }
}

s32 Task_MapNiseriku_1(MapNiserikuWork* work) {
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

void Task_MapNiseriku_2(MapNiserikuWork* work) {
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

void Task_MapNiseriku_3(MapNiserikuWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);

    if (work->registered) {
        FldObjUnregister(&work->obj);
    }

    TaskPoolDestroy(&work->tasks);
    TaskPoolDestroy(&work->tasks2);
}

TaskDesc gTaskDescMapNiseriku = {
    "Task_MapNiseriku",
    (TaskInitFunc)Task_MapNiseriku_0,
    (TaskUpdateFunc)Task_MapNiseriku_1,
    (TaskDrawFunc)Task_MapNiseriku_2,
    (TaskDestroyFunc)Task_MapNiseriku_3,
    sizeof(MapNiserikuWork),
};
