#include "map_tasks.h"
#include "sprites_btl.h"
#include "sprite_palettes.h"
#include "anim.h"
#include "field_state.h"
#include "fld_types.h"
#include "map.h"
#include "obj.h"
#include "obj_api.h"
#include "registration_data.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

void Task_MapFaint_0(MapFaintWork* w, FldObj* obj) {
    w->obj = obj;
    w->tiles = AllocObjTiles(0x80, gUnk_08B21ACE);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    AnimInit(&w->anim, gUnk_09EE12E4, gUnk_09EE12D4);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
}

s32 Task_MapFaint_1(MapFaintWork* w) {
    AnimUpdate(&w->anim);
    return 1;
}

void Task_MapFaint_2(MapFaintWork* w) {
    FldObj* e = w->obj;
    u16 x;
    u16 y;

    x = (e->fieldPosition.x >> 8) - (gFieldState->x >> 8);
    y = (e->fieldPosition.y >> 8) + ((e->fieldPosition.z - (e->height + 8) * 0x100) >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1005 - (e->fieldPosition.y >> 8) * 4);
}

void Task_MapFaint_3(MapFaintWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

TaskDesc gTaskDescMapFaint = {
    "Task_MapFaint",
    (TaskInitFunc)Task_MapFaint_0,
    (TaskUpdateFunc)Task_MapFaint_1,
    (TaskDrawFunc)Task_MapFaint_2,
    (TaskDestroyFunc)Task_MapFaint_3,
    sizeof(MapFaintWork),
};
