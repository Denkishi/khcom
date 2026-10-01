#include "map_tasks.h"
#include "sprites_btl.h"
#include "sprite_palettes.h"
#include "field_state.h"
#include "map.h"
#include "map_api.h"
#include "map_types.h"
#include "obj.h"
#include "obj_api.h"
#include "registration_data.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

void Task_MapDmg_0(MapDmgWork* w) {
    s32 z = 0;

    w->visible = z;
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    w->tiles = LoadObjTiles(gUnk_08B1EA00, 224);
    w->timer = z;
    w->enabled = 1;
}

s32 Task_MapDmg_1(MapDmgWork* w) {
    if (w->enabled == 0) {
        w->visible = 0;
    } else {
        if (gMapRoomState->attackActive != 0 || (gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK)) {
            w->timer = 20;
        }

        w->visible = w->timer != 0;

        if (w->timer != 0) {
            w->timer -= 1;
        }
    }

    return 1;
}

void Task_MapDmg_2(MapDmgWork* w) {
    s16 x;
    s16 y;

    if (w->visible == 0) {
        return;
    }

    x = ((gMapRoomState->attackX - 0x1400) >> 8) - (gFieldState->x >> 8);
    y = ((gMapRoomState->attackY - 0x1400) >> 8) + (gMapRoomState->attackZ >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, gUnk_08B1E974, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), 0x101);

    x = ((gMapRoomState->attackX + 0x1400) >> 8) - (gFieldState->x >> 8);
    y = ((gMapRoomState->attackY - 0x1400) >> 8) + (gMapRoomState->attackZ >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, gUnk_08B1E97E, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), 0x101);

    x = ((gMapRoomState->attackX - 0x1400) >> 8) - (gFieldState->x >> 8);
    y = ((gMapRoomState->attackY + 0x1400) >> 8) + (gMapRoomState->attackZ >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, gUnk_08B1E992, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), 0x101);

    x = ((gMapRoomState->attackX + 0x1400) >> 8) - (gFieldState->x >> 8);
    y = ((gMapRoomState->attackY + 0x1400) >> 8) + (gMapRoomState->attackZ >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, gUnk_08B1E988, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), 0x101);

    x = ((gMapRoomState->attackX) >> 8) - (gFieldState->x >> 8);
    y = ((gMapRoomState->attackY) >> 8) + (gMapRoomState->attackZ >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, gUnk_08B1E9A6, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), 0x101);
}

void Task_MapDmg_3(MapDmgWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

TaskDesc gTaskDescMapDmg = {
    "Task_MapDmg",
    (TaskInitFunc)Task_MapDmg_0,
    (TaskUpdateFunc)Task_MapDmg_1,
    (TaskDrawFunc)Task_MapDmg_2,
    (TaskDestroyFunc)Task_MapDmg_3,
    sizeof(MapDmgWork),
};
