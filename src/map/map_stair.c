#include "map_tasks.h"
#include "sprites_btl.h"
#include "sprite_palettes.h"
#include "engine_math.h"
#include "card_api.h"
#include "field_state.h"
#include "fld_types.h"
#include "game_state.h"
#include "map.h"
#include "map_api.h"
#include "map_types.h"
#include "obj.h"
#include "obj_api.h"
#include "player_progression_types.h"
#include "registration_data.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

s32 IsPlayerWithin(FldPos* p, s32 lim) {
    s32 dx;
    s32 dy;

    dx = p->x - gFieldState->actor.fieldPosition.x;

    if (dx < 0) {
        dx = gFieldState->actor.fieldPosition.x - p->x;
    }

    dy = p->y - gFieldState->actor.fieldPosition.y;

    if (dy < 0) {
        dy = gFieldState->actor.fieldPosition.y - p->y;
    }

    if (dx > 0x8000 || dy > 0x8000) {
        return 0;
    }

    return Sqrt8((dx * dx >> 8) + (dy * dy >> 8)) < lim ? 1 : 0;
}

void MapStairWaitStepOn(MapStairWork* w) {
    if ((u8)IsPlayerWithin(&w->obj.fieldPosition, 0x800) != 0) {
        if (gFieldState->actor.fieldPosition.z == gFieldState->actor.fieldPosition.ground) {
            if (gMapFloorState.room == MAP_ROOM_ENTRANCE_HALL) {
                gMapRoomState->flags |= ROOM_FLAG_WALK_OUT;
            } else {
                gMapRoomState->flags |= ROOM_FLAG_EXIT_NEXT_FLOOR;
            }
        }
    }
}

void MapStairWaitStepOn2(MapStairWork* w) {
    s32 k = 0x800;

    if ((u8)IsPlayerWithin(&w->obj.fieldPosition, k) != 0) {
        if (gFieldState->actor.fieldPosition.z == gFieldState->actor.fieldPosition.ground) {
            if (gMapFloorState.room == MAP_ROOM_ENTRANCE_HALL) {
                gMapRoomState->flags |= k;
            } else {
                gMapRoomState->flags |= ROOM_FLAG_ENTER_WORLD;
            }
        }
    }
}

void MapStairWaitApproach(MapStairWork* w) {
    if ((u8)IsPlayerWithin(&w->obj.fieldPosition, 0x3000) != 0) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        gMapRoomState->flags |= ROOM_FLAG_TUTORIAL_ACTIVE;
        CreateCardMessageTask(&w->tasks, 0, 0xA7);
        w->update = MapStairWaitMessage;
    }
}

void MapStairWaitMessage(MapStairWork* w) {
    if (IsMessageWindowOpen() == 0) {
        gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
        gMapRoomState->flags &= ~ROOM_FLAG_TUTORIAL_ACTIVE;
        gGameState.progression.tutorialFlags |= 0x400;
        w->update = MapStairWaitStepOn;
    }
}

void Task_MapStair_0(MapStairWork* w, FldObj* arg) {
    s32 y;

    w->obj.angle = arg->angle;
    w->obj.fieldPosition.x = arg->fieldPosition.x;
    y = arg->fieldPosition.y;
    w->obj.fieldPosition.ground = 0;
    w->obj.fieldPosition.z = 0;
    w->obj.fieldPosition.y = y;
    w->palette = LoadObjPalette(gUnk_08F69BE4, 0x20);
    w->tiles = LoadObjTiles(gUnk_08B1EA00, 0xE0);
    w->visible = 0;

    switch (w->obj.angle) {
    case 0x2D:
        if ((gGameState.progression.tutorialFlags & 0x400) == 0 && gMapFloorState.room == MAP_ROOM_EXIT_HALL) {
            w->update = MapStairWaitApproach;
        } else {
            w->update = MapStairWaitStepOn;
        }

        break;
    case 0xAD:
        w->update = MapStairWaitStepOn2;
        break;
    }

    TaskPoolInit(&w->tasks, 1);
}

s32 Task_MapStair_1(MapStairWork* w) {
    TaskPoolUpdate(&w->tasks);

    if (w->update != NULL) {
        w->update(w);
    }

    return 1;
}

void Task_MapStair_2(MapStairWork* w) {
    s32 x;
    s32 y;

    TaskPoolDraw(&w->tasks);

    if (w->visible == 1) {
        x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
        y = (w->obj.fieldPosition.y >> 8) + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
        DrawSprite(x, y, gUnk_08B1E9A6, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), 0x101);
    }
}

void Task_MapStair_3(MapStairWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    TaskPoolDestroy(&w->tasks);
}

TaskDesc gTaskDescMapStair = {
    "Task_MapStair",
    (TaskInitFunc)Task_MapStair_0,
    (TaskUpdateFunc)Task_MapStair_1,
    (TaskDrawFunc)Task_MapStair_2,
    (TaskDestroyFunc)Task_MapStair_3,
    sizeof(MapStairWork),
};
