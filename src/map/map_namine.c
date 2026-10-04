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

void MapNamineCheckTalk(MapNamineWork* work) {
    if (work->targeted && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;

        if (gMapFloorState.progress == 27) {
            CreateCardMessageTask(&work->tasks, 0, 0x33);
        } else {
            CreateCardMessageTask(&work->tasks, 0, 0x32);
        }

        work->update = MapNamineWaitMessage;
    }
}

void MapNamineWaitMessage(MapNamineWork* work) {
    if (!IsMessageWindowOpen()) {
        gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
        work->update = MapNamineCheckTalk;
    }
}

void Task_MapNamine_0(MapNamineWork* work) {
    FldObj* p = &work->obj;

    switch (gMapFloorState.progress) {
    case 27:
        work->obj.fieldPosition.x = 0x20D00;
        work->obj.fieldPosition.y = 0xD500;
        work->spriteFlags = SPRITE_PRIORITY(2);
        break;
    case 23:
        work->obj.fieldPosition.x = 0x27C00;
        work->obj.fieldPosition.y = 0xD400;
        work->spriteFlags = SPRITE_PRIORITY(2);
        break;
    case 24:
    case 25:
    case 26:
    default:
        p->fieldPosition.x = 0x15200;
        p->fieldPosition.y = 0xF800;
        work->spriteFlags = SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
        break;
    }

    p->fieldPosition.z = 0;
    p->fieldPosition.z = p->fieldPosition.ground = GetFldPosFloor(&p->fieldPosition);
    p->fieldPosition.y -= p->fieldPosition.ground;
    p->angle = 173;
    p->height = 48;
    p->kind = 2;
    work->registered = gMapFloorState.progress != 23;
    work->visible = 1;
    work->update = MapNamineCheckTalk;
    work->tiles = AllocObjTiles(0x300, gNamiF00Tiles);
    work->palette = LoadObjPalette(gNaminePalette, 32);
    AnimInit(&work->anim, gNamiF00Anims, gNamiF00Frames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    ColliderInit(&work->collider, 4, 16, 48);
    ColliderSetPosition(&work->collider, p->fieldPosition.x, p->fieldPosition.y, p->fieldPosition.z);

    if (work->registered) {
        FldObjRegister(p);
    }

    TaskPoolInit(&work->tasks, 2);
    TaskCreate(&work->tasks, &gTaskDescFldShadow, &work->obj);
    work->targeted = 0;
    TaskPoolInit(&work->tasks2, 1);
    TaskCreate(&work->tasks2, &gTaskDescMapTalk, &work->obj);
}

s32 Task_MapNamine_1(MapNamineWork* work) {
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

void Task_MapNamine_2(MapNamineWork* work) {
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
        DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL, work->spriteFlags, v);
        work->obj.shadowZ = p->ground;
        work->obj.shadowPriority = v + 1;
        TaskPoolDraw(&work->tasks);

        if (work->targeted) {
            TaskPoolDraw(&work->tasks2);
        }
    }
}

void Task_MapNamine_3(MapNamineWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);

    if (work->registered) {
        FldObjUnregister(&work->obj);
    }

    TaskPoolDestroy(&work->tasks);
    TaskPoolDestroy(&work->tasks2);
}

TaskDesc gTaskDescMapNamine = {
    "Task_MapNamine",
    (TaskInitFunc)Task_MapNamine_0,
    (TaskUpdateFunc)Task_MapNamine_1,
    (TaskDrawFunc)Task_MapNamine_2,
    (TaskDestroyFunc)Task_MapNamine_3,
    sizeof(MapNamineWork),
};
