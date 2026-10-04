/**
 * map_tasks.c
 * Field Enemies and Gimmicks
 */

#include "monsgage.h"
#include "map_resource_assets.h"
#include "map_tasks.h"
#include "sprites_btl.h"
#include "sprites_emy.h"
#include "sprites_evt.h"
#include "sprites_map.h"
#include "sprites_map_tasks.h"
#include "sprites_card_pictures.h"
#include "system_state.h"
#include "gba/keys.h"
#include "engine_math.h"
#include "map_runtime.h"
#include "fade.h"
#include "songs.h"
#include <stdlib.h>
#include "world_types.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "btl_collision.h"
#include "card.h"
#include "card_api.h"
#include "card_def_data.h"
#include "card_types.h"
#include "display.h"
#include "field_state.h"
#include "fld_types.h"
#include "game_state.h"
#include "key.h"
#include "m4a_song.h"
#include "map.h"
#include "map_api.h"
#include "map_types.h"
#include "mode.h"
#include "msg_api.h"
#include "obj.h"
#include "obj_api.h"
#include "player_progression_types.h"
#include "registration_data.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "text.h"
#include "types.h"
#include <stddef.h>
#include "lockon.h"
#include "map_room_tables.h"
#include "sprite_palettes.h"

static const AnimDef sMapEnm00AnimDefs[10] = {
    { gEmy00L06Frames, gEmy00L06Anims, gEmy00L06Tiles, 0 },
    { gEmy00L06Frames, gEmy00L06Anims, gEmy00L06Tiles, 0 },
    { gUnk_09EDF860, gUnk_09EDF880, gUnk_08958AC8, 0 },
    { gEmy00L00Frames, gEmy00L00Anims, gEmy00L00Tiles, 0 },
    { gUnk_09EDF8A8, gUnk_09EDF8C8, gUnk_0895B2C0, 0 },
    { gEmy00L02Frames, gEmy00L02Anims, gEmy00L02Tiles, 0 },
    { gUnk_09EDF97C, gUnk_09EDF9A4, gUnk_0896213C, 0 },
    { gEmy00L07Frames, gEmy00L07Anims, gEmy00L07Tiles, 0 },
    { gEmy00L09Frames, gEmy00L09Anims, gEmy00L09Tiles, 0 },
    { gEmy00L09Frames, gEmy00L09Anims, gEmy00L09Tiles, 0 },
};

const AnimDef gUnk_0984BC3C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 1,
};

const AnimDef gUnk_0984BC4C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 1,
};

const AnimDef gUnk_0984BC5C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 0,
};

const AnimDef gUnk_0984BC6C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 0,
};

const AnimDef gUnk_0984BC7C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 2,
};

const AnimDef gUnk_0984BC8C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 2,
};

const MapEnmDef gMapEnm00Def = {
    sMapEnm00AnimDefs, gEmy00Palette,
    32, 8, 16,
    &gTaskDescMapEnm00, MAP_ENM_DEF_FLAG_NO_SHADOW,
};

TaskDesc gTaskDescMapEnm00 = {
    "Task_MapEnm00",
    (TaskInitFunc)Task_MapEnm00_0,
    (TaskUpdateFunc)Task_MapEnm00_1,
    (TaskDrawFunc)Task_MapEnm00_2,
    (TaskDestroyFunc)Task_MapEnm00_3,
    sizeof(MapEnmWork),
};

static const AnimDef sMapEnm01AnimDefs[6] = {
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 0 },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 0 },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 2 },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 2 },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 3 },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 3 },
};

const MapEnmDef gMapEnm01Def = {
    sMapEnm01AnimDefs, gEmy01Palette,
    17, 16, 16,
    &gTaskDescMapEnm01, MAP_ENM_DEF_FLAG_AIRBORNE,
};

TaskDesc gTaskDescMapEnm01 = {
    "Task_MapEnm01",
    (TaskInitFunc)Task_MapEnm01_0,
    (TaskUpdateFunc)Task_MapEnm01_1,
    (TaskDrawFunc)Task_MapEnm01_2,
    (TaskDestroyFunc)Task_MapEnm01_3,
    sizeof(MapEnm01Work),
};

static const AnimDef sMapEnm02AnimDefs[2] = {
    { gEmy3800Frames, gEmy3800Anims, gEmy3800Tiles, 0 },
    { gEmy3800Frames, gEmy3800Anims, gEmy3800Tiles, 0 },
};

const AnimDef gUnk_0984BD6C = {
    gEmy3801Frames, gEmy3801Anims, gEmy3801Tiles, 0,
};

const AnimDef gUnk_0984BD7C = {
    gEmy3801Frames, gEmy3801Anims, gEmy3801Tiles, 0,
};

const MapEnmDef gMapEnm02Def = {
    sMapEnm02AnimDefs, gEmy38Palette,
    106, 48, 36,
    &gTaskDescMapEnm02, MAP_ENM_DEF_FLAG_GUARD,
};

TaskDesc gTaskDescMapEnm02 = {
    "Task_MapEnm02",
    (TaskInitFunc)Task_MapEnm02_0,
    (TaskUpdateFunc)Task_MapEnm02_1,
    (TaskDrawFunc)Task_MapEnm02_2,
    (TaskDestroyFunc)Task_MapEnm02_3,
    sizeof(MapEnmWork),
};

static const AnimDef sMapEnm03AnimDefs[4] = {
    { gEmy2900Frames, gEmy2900Anims, gEmy2900Tiles, 0 },
    { gEmy2900Frames, gEmy2900Anims, gEmy2900Tiles, 0 },
    { gEmy2900Frames, gEmy2900Anims, gEmy2900Tiles, 0 },
    { gEmy2900Frames, gEmy2900Anims, gEmy2900Tiles, 0 },
};

const AnimDef gUnk_0984BDF4 = {
    gEmy2902Frames, gEmy2902Anims, gEmy2902Tiles, 0,
};

const AnimDef gUnk_0984BE04 = {
    gEmy2902Frames, gEmy2902Anims, gEmy2902Tiles, 0,
};

const MapEnmDef gMapEnm03Def = {
    sMapEnm03AnimDefs, gEmy29Palette,
    73, 56, 36,
    &gTaskDescMapEnm03, MAP_ENM_DEF_FLAG_AIRBORNE | MAP_ENM_DEF_FLAG_GUARD,
};

TaskDesc gTaskDescMapEnm03 = {
    "Task_MapEnm03",
    (TaskInitFunc)Task_MapEnm03_0,
    (TaskUpdateFunc)Task_MapEnm03_1,
    (TaskDrawFunc)Task_MapEnm03_2,
    (TaskDestroyFunc)Task_MapEnm03_3,
    sizeof(MapEnm03Work),
};

static const AnimDef sMapEnm04AnimDefs[6] = {
    { gUnk_09EF8D24, gUnk_09EF8D44, gUnk_098A659A, 0 },
    { gEmy0600Frames, gEmy0600Anims, gEmy0600Tiles, 0 },
    { gUnk_09EF8D24, gUnk_09EF8D44, gUnk_098A659A, 0 },
    { gEmy0600Frames, gEmy0600Anims, gEmy0600Tiles, 0 },
    { gEmy0603Frames, gEmy0603Anims, gEmy0603Tiles, 0 },
    { gEmy0603Frames, gEmy0603Anims, gEmy0603Tiles, 0 },
};

const MapEnmDef gMapEnm04Def = {
    sMapEnm04AnimDefs, gEmy06Palette,
    34, 16, 12,
    &gTaskDescMapEnm04, MAP_ENM_DEF_FLAG_AIRBORNE,
};

TaskDesc gTaskDescMapEnm04 = {
    "Task_MapEnm04",
    (TaskInitFunc)Task_MapEnm04_0,
    (TaskUpdateFunc)Task_MapEnm04_1,
    (TaskDrawFunc)Task_MapEnm04_2,
    (TaskDestroyFunc)Task_MapEnm04_3,
    sizeof(MapEnm01Work),
};

static const AnimDef sMapEnm05AnimDefs[8] = {
    { gEmy07Fl01Frames, gEmy07Fl01Anims, gEmy07Fl01Tiles, 0 },
    { gEmy07Fl01Frames, gEmy07Fl01Anims, gEmy07Fl01Tiles, 0 },
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0 },
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0 },
    { gEmy07Fl02Frames, gEmy07Fl02Anims, gEmy07Fl02Tiles, 0 },
    { gEmy07Fl02Frames, gEmy07Fl02Anims, gEmy07Fl02Tiles, 0 },
    { gEmy07Fl03Frames, gEmy07Fl03Anims, gEmy07Fl03Tiles, 0 },
    { gEmy07Fl03Frames, gEmy07Fl03Anims, gEmy07Fl03Tiles, 0 },
};

const MapEnmDef gMapEnm05Def = {
    sMapEnm05AnimDefs, gEmy07Palette,
    26, 16, 12,
    &gTaskDescMapEnm05, MAP_ENM_DEF_FLAG_SPAWN_ANYWHERE,
};

TaskDesc gTaskDescMapEnm05 = {
    "Task_MapEnm05",
    (TaskInitFunc)Task_MapEnm05_0,
    (TaskUpdateFunc)Task_MapEnm05_1,
    (TaskDrawFunc)Task_MapEnm05_2,
    (TaskDestroyFunc)Task_MapEnm05_3,
    sizeof(MapEnmWork),
};

static const AnimDef sMapEnm06AnimDefs[8] = {
    { gEmy07Fl01Frames, gEmy07Fl01Anims, gEmy07Fl01Tiles, 0 },
    { gEmy07Fl01Frames, gEmy07Fl01Anims, gEmy07Fl01Tiles, 0 },
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0 },
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0 },
    { gEmy07Fl02Frames, gEmy07Fl02Anims, gEmy07Fl02Tiles, 0 },
    { gEmy07Fl02Frames, gEmy07Fl02Anims, gEmy07Fl02Tiles, 0 },
    { gEmy07Fl03Frames, gEmy07Fl03Anims, gEmy07Fl03Tiles, 0 },
    { gEmy07Fl03Frames, gEmy07Fl03Anims, gEmy07Fl03Tiles, 0 },
};

const MapEnmDef gMapEnm06Def = {
    sMapEnm06AnimDefs, gEmy07bPalette,
    26, 16, 12,
    &gTaskDescMapEnm06, MAP_ENM_DEF_FLAG_SPAWN_ANYWHERE,
};

TaskDesc gTaskDescMapEnm06 = {
    "Task_MapEnm06",
    (TaskInitFunc)Task_MapEnm06_0,
    (TaskUpdateFunc)Task_MapEnm06_1,
    (TaskDrawFunc)Task_MapEnm06_2,
    (TaskDestroyFunc)Task_MapEnm06_3,
    sizeof(MapEnmWork),
};

static u8 sMapDbgCursorString[] = "_";

TaskDesc gTaskDescMapDbg = {
    "Task_MapDbg",
    (TaskInitFunc)Task_MapDbg_0,
    (TaskUpdateFunc)Task_MapDbg_1,
    (TaskDrawFunc)Task_MapDbg_2,
    (TaskDestroyFunc)Task_MapDbg_3,
    sizeof(MapDbgWork),
};

TaskDesc gTaskDescMapGmkJump = {
    "Task_MapGmk_Jump",
    (TaskInitFunc)Task_MapGmk_Jump_0,
    (TaskUpdateFunc)Task_MapGmk_Jump_1,
    (TaskDrawFunc)Task_MapGmk_Jump_2,
    (TaskDestroyFunc)Task_MapGmk_Jump_3,
    sizeof(MapGmkJumpWork),
};

static TaskDesc sTaskDescMapGmkEnm = {
    "Task_MapGmk_Enm",
    (TaskInitFunc)Task_MapGmk_Enm_0,
    (TaskUpdateFunc)Task_MapGmk_Enm_1,
    (TaskDrawFunc)Task_MapGmk_Enm_2,
    (TaskDestroyFunc)Task_MapGmk_Enm_3,
    sizeof(MapGmkEnmWork),
};

TaskDesc gTaskDescMapGmkDmy = {
    "Task_MapGmk_Dmy",
    (TaskInitFunc)Task_MapGmk_Dmy_0,
    (TaskUpdateFunc)Task_MapGmk_Dmy_1,
    (TaskDrawFunc)Task_MapGmk_Dmy_2,
    (TaskDestroyFunc)Task_MapGmk_Dmy_3,
    sizeof(MapGmkDmyWork),
};

TaskDesc gTaskDescMapGmkTutorial = {
    "Task_MapGmk_Tutorial",
    (TaskInitFunc)Task_MapGmk_Tutorial_0,
    (TaskUpdateFunc)Task_MapGmk_Tutorial_1,
    (TaskDrawFunc)Task_MapGmk_Tutorial_2,
    (TaskDestroyFunc)Task_MapGmk_Tutorial_3,
    sizeof(MapGmkTutorialWork),
};

static TaskDesc sTaskDescMapGmkSpider = {
    "Task_MapGmk_Spider",
    (TaskInitFunc)Task_MapGmk_Spider_0,
    (TaskUpdateFunc)Task_MapGmk_Spider_1,
    (TaskDrawFunc)Task_MapGmk_Spider_2,
    (TaskDestroyFunc)Task_MapGmk_Spider_3,
    sizeof(MapGmkSpiderWork),
};

TaskDesc gTaskDescMapGmkGP00 = {
    "Task_MapGmk_GP00",
    (TaskInitFunc)Task_MapGmk_GP00_0,
    (TaskUpdateFunc)Task_MapGmk_GP00_1,
    (TaskDrawFunc)Task_MapGmk_GP00_2,
    (TaskDestroyFunc)Task_MapGmk_GP00_3,
    sizeof(MapGmkGpWork),
};

TaskDesc gTaskDescMapGmkGP01 = {
    "Task_MapGmk_GP01",
    (TaskInitFunc)Task_MapGmk_GP01_0,
    (TaskUpdateFunc)Task_MapGmk_GP01_1,
    (TaskDrawFunc)Task_MapGmk_GP01_2,
    (TaskDestroyFunc)Task_MapGmk_GP01_3,
    sizeof(MapGmkGp1Work),
};

TaskDesc gTaskDescMapGmkGP02 = {
    "Task_MapGmk_GP02",
    (TaskInitFunc)Task_MapGmk_GP02_0,
    (TaskUpdateFunc)Task_MapGmk_GP02_1,
    (TaskDrawFunc)Task_MapGmk_GP02_2,
    (TaskDestroyFunc)Task_MapGmk_GP02_3,
    sizeof(MapGmkGpWork),
};

TaskDesc gTaskDescMapGmkGP03 = {
    "Task_MapGmk_GP03",
    (TaskInitFunc)Task_MapGmk_GP03_0,
    (TaskUpdateFunc)Task_MapGmk_GP03_1,
    (TaskDrawFunc)Task_MapGmk_GP03_2,
    (TaskDestroyFunc)Task_MapGmk_GP03_3,
    sizeof(MapGmkGpWork),
};

TaskDesc gTaskDescMapGmkGP04 = {
    "Task_MapGmk_GP04",
    (TaskInitFunc)Task_MapGmk_GP04_0,
    (TaskUpdateFunc)Task_MapGmk_GP04_1,
    (TaskDrawFunc)Task_MapGmk_GP04_2,
    (TaskDestroyFunc)Task_MapGmk_GP04_3,
    sizeof(MapGmkGpWork),
};

TaskDesc gTaskDescMapGmkGP05 = {
    "Task_MapGmk_GP05",
    (TaskInitFunc)Task_MapGmk_GP05_0,
    (TaskUpdateFunc)Task_MapGmk_GP05_1,
    (TaskDrawFunc)Task_MapGmk_GP05_2,
    (TaskDestroyFunc)Task_MapGmk_GP05_3,
    sizeof(MapGmkGpWork),
};

TaskDesc gTaskDescMapGmkGP06 = {
    "Task_MapGmk_GP06",
    (TaskInitFunc)Task_MapGmk_GP06_0,
    (TaskUpdateFunc)Task_MapGmk_GP06_1,
    (TaskDrawFunc)Task_MapGmk_GP06_2,
    (TaskDestroyFunc)Task_MapGmk_GP06_3,
    sizeof(MapGmkGpWork),
};

TaskDesc gTaskDescMapGmkGP07 = {
    "Task_MapGmk_GP07",
    (TaskInitFunc)Task_MapGmk_GP07_0,
    (TaskUpdateFunc)Task_MapGmk_GP07_1,
    (TaskDrawFunc)Task_MapGmk_GP07_2,
    (TaskDestroyFunc)Task_MapGmk_GP07_3,
    sizeof(MapGmkGp07Work),
};

TaskDesc gTaskDescMapGmkGP08 = {
    "Task_MapGmk_GP08",
    (TaskInitFunc)Task_MapGmk_GP08_0,
    (TaskUpdateFunc)Task_MapGmk_GP08_1,
    (TaskDrawFunc)Task_MapGmk_GP08_2,
    (TaskDestroyFunc)Task_MapGmk_GP08_3,
    sizeof(MapGmkGp08Work),
};

TaskDesc gTaskDescMapGmkGP09 = {
    "Task_MapGmk_GP09",
    (TaskInitFunc)Task_MapGmk_GP09_0,
    (TaskUpdateFunc)Task_MapGmk_GP09_1,
    (TaskDrawFunc)Task_MapGmk_GP09_2,
    (TaskDestroyFunc)Task_MapGmk_GP09_3,
    sizeof(MapGmkGp09Work),
};

TaskDesc gTaskDescMapGmk00 = {
    "Task_MapGmk00",
    (TaskInitFunc)Task_MapGmk00_0,
    (TaskUpdateFunc)Task_MapGmk00_1,
    (TaskDrawFunc)Task_MapGmk00_2,
    (TaskDestroyFunc)Task_MapGmk00_3,
    sizeof(MapGmk00Work),
};

s32 MapEnm00CheckOffscreen(MapEnmWork* work) {
    FldPos* q = &work->obj.fieldPosition;

    if (work->obj.fieldPosition.x < gFieldState->x - 0x1800 || work->obj.fieldPosition.x > gFieldState->x + 0x10800 ||
        q->y + q->z < gFieldState->y - 0x800 || q->y + q->z > gFieldState->y + 0xC000) {
        work->update = NULL;
        ColliderSetDisabled(&work->collider, 1);
        return 1;
    }

    return 0;
}

void MapEnm00Move(MapEnmWork* work, s32 b, s32 c) {
    FldObj* q = &work->obj;

    if (work->flags & MAP_ENM_FLAG_SLOW) {
        b /= 5;
        c /= 5;
    }

    work->obj.fieldPosition.x += gSineTable[q->angle] * q->speed >> 8;
    q->fieldPosition.y += -gSineTable[q->angle + 64] * q->speed >> 8;
    q->speed += b;

    if (q->speed > c) {
        q->speed = c;
    }
}

void MapEnm00CheckBlocked(MapEnmWork* work, s32 b, s32 c) {
    FldPos* q = &work->obj.fieldPosition;

    if (IsFldPosBlocked(q) != 0 || GetFldPosGround(q) != q->z) {
        work->obj.fieldPosition.x = b;
        q->y = c;
        work->update = MapEnm00Vanish;
        ColliderSetDisabled(&work->collider, 1);
    }
}

s32 MapEnm00SpotPlayer(MapEnmWork* work) {
    FldObj* q = &work->obj;
    u8 ang;

    if (gFieldState->actor.fieldPosition.ground != q->fieldPosition.ground) {
        return 0;
    }

    ang = GetAngle(work->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);

    if (abs(GetAngleDiff(ang, q->angle)) > 0x18) {
        return 0;
    }

    q->angle = ang;
    return 1;
}

void MapEnm00Appear(MapEnmWork* work) {
    MapEnmSetAnim(work, 0, 0);
    TaskPoolUpdate(&work->tasks);

    if (AnimIsFinished(&work->anim)) {
        if (work->flags & MAP_ENM_FLAG_AGGRESSIVE) {
            work->update = MapEnm00Pursue;
        } else {
            work->update = MapEnm00Idle;
        }

        work->timer = 0;
        ColliderSetDisabled(&work->collider, 0);
    } else {
        MapEnmUpdateAnim(work);

        if (work->colliderDelay > 0) {
            work->colliderDelay--;

            if (work->colliderDelay <= 0) {
                ColliderSetDisabled(&work->collider, 0);
            }
        }
    }
}

void MapEnm00Idle(MapEnmWork* work) {
    FldObj* q = &work->obj;
    s32 x;
    s32 y;

    MapEnmSetAnim(work, 1, 1);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);
    x = work->obj.fieldPosition.x;
    y = q->fieldPosition.y;

    if ((u8)MapEnm00SpotPlayer(work)) {
        work->timer = 0;
        work->update = MapEnm00Chase;
    } else if (GetRandom() % 80 == 0) {
        switch (GetRandom() % 4) {
        case 0:
            q->angle = 173;
            break;
        case 1:
            q->angle = 83;
            break;
        case 2:
            q->angle = 211;
            break;
        default:
            q->angle = 45;
            break;
        }

        work->timer = 0;
        work->update = MapEnm00Wander;
    }

    if ((u8)MapEnmCheckAttacked(work)) {
        work->update = MapEnm00Hit;
    } else {
        MapEnmCheckContact(work);

        if (!(u8)MapEnm00CheckOffscreen(work)) {
            MapEnm00CheckBlocked(work, x, y);
        }
    }
}

void MapEnm00Wander(MapEnmWork* work) {
    FldObj* q = &work->obj;
    s32 x;
    s32 y;

    MapEnmSetAnim(work, 2, 1);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);
    x = work->obj.fieldPosition.x;
    y = q->fieldPosition.y;

    if ((u8)MapEnm00SpotPlayer(work)) {
        work->timer = 0;
        work->update = MapEnm00Chase;
    } else if (GetRandom() % 80 == 0) {
        q->speed = 0;
        work->update = MapEnm00Idle;
    } else {
        MapEnm00Move(work, 12, 0x80);
    }

    if ((u8)MapEnmCheckAttacked(work)) {
        work->update = MapEnm00Hit;
    } else {
        MapEnmCheckContact(work);

        if (!(u8)MapEnm00CheckOffscreen(work)) {
            MapEnm00CheckBlocked(work, x, y);
        }
    }
}

void MapEnm00Chase(MapEnmWork* work) {
    FldObj* q = &work->obj;
    s32 x;
    s32 y;

    MapEnmSetAnim(work, 2, 1);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);
    x = q->fieldPosition.x;
    y = q->fieldPosition.y;

    if (work->timer % 8 == 0) {
        if (!(u8)MapEnm00SpotPlayer(work)) {
            q->speed = 0;
            work->update = MapEnm00Idle;
        }
    }

    MapEnm00Move(work, 12, 0x180);
    work->timer++;

    if ((u8)MapEnmCheckAttacked(work)) {
        work->update = MapEnm00Hit;
    } else {
        MapEnmCheckContact(work);

        if (!(u8)MapEnm00CheckOffscreen(work)) {
            MapEnm00CheckBlocked(work, x, y);
        }
    }
}

void MapEnm00Pursue(MapEnmWork* work) {
    FldObj* q = &work->obj;
    s32 x;
    s32 y;

    MapEnmSetAnim(work, 2, 1);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);
    x = q->fieldPosition.x;
    y = q->fieldPosition.y;

    if (work->timer % 8 == 0) {
        q->angle = GetAngle(x, y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    MapEnm00Move(work, 25, 0x200);

    if ((u8)MapEnmCheckAttacked(work)) {
        work->update = MapEnm00Hit;
    } else {
        MapEnmCheckContact(work);
        MapEnm00CheckBlocked(work, x, y);
        work->timer++;
    }
}

void MapEnm00Vanish(MapEnmWork* work) {
    work->flags |= MAP_ENM_FLAG_REMOVED;
    MapEnmSetAnim(work, 3, 0);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);

    if (AnimIsFinished(&work->anim)) {
        work->update = NULL;
    }
}

void MapEnm00Hit(MapEnmWork* work) {
    MapEnmSetAnim(work, 4, 0);
    TaskPoolUpdate(&work->tasks);

    if (AnimIsFinished(&work->anim)) {
        work->flags |= MAP_ENM_FLAG_FIRST_STRIKE;
        MapEnmStartBattle(work);
    } else {
        MapEnmUpdateAnim(work);
    }
}

void MapEnm00Stand(MapEnmWork* work) {
    MapEnmSetAnim(work, 1, 0);
    work->gfx = AnimGetGfx(&work->anim);
    TaskPoolUpdate(&work->tasks);

    if ((u8)MapEnmCheckAttacked(work)) {
        work->update = MapEnm00Hit;
    } else {
        MapEnmCheckContact(work);
    }
}

void Task_MapEnm00_0(MapEnmWork* work, MapEnmArgs* q) {
    MapEnmInit(work, q);

    if (work->update == NULL) {
        if (work->flags & MAP_ENM_FLAG_ASLEEP) {
            work->update = MapEnm00Stand;
            MapEnmSetAnim(work, 1, 0);
            work->gfx = AnimGetGfx(&work->anim);
            ColliderSetDisabled(&work->collider, 0);
        } else {
            work->update = MapEnm00Appear;
            MapEnmSetAnim(work, 0, 0);
            work->gfx = AnimGetGfx(&work->anim);
            ColliderSetDisabled(&work->collider, 1);
        }
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    work->timer = 0;
}

s32 Task_MapEnm00_1(MapEnmWork* work) {
    FldPos* q = &work->obj.fieldPosition;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapEnmSaveToCache(work);
        return 0;
    }

    if ((gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) && work->update != MapEnm00Hit) {
        return 1;
    }

    if (work->update != NULL) {
        work->update(work);

        if (work->update != NULL) {
            ColliderSetPosition(&work->collider, q->x, q->y, q->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm00_2(MapEnmWork* work) {
    MapEnmDraw(work);
}

void Task_MapEnm00_3(MapEnmWork* work) {
    MapEnmDestroy(work);
}

void MapEnm01CheckOffscreen(MapEnm01Work* work) {
    if (work->enm.obj.fieldPosition.x < gFieldState->x - 0x1800 || work->enm.obj.fieldPosition.x > gFieldState->x + 0x10800) {
        if (work->wasOnScreen) {
            work->enm.update = NULL;
        }
    } else if (!work->wasOnScreen) {
        work->wasOnScreen = 1;
    }
}

void MapEnm01UpdateHover(MapEnmWork* work, u8 a) {
    s32* q = &work->obj.fieldPosition.x;
    s32 t = q[2];
    s32 v;

    switch (a) {
    case 1:
        v = work->targetZ + SIN(gFrameCounter) * 10;
        break;
    case 0:
    default:
        v = work->targetZ + SIN(gFrameCounter * 2) * 12;
        break;
    }

    if (work->flags & MAP_ENM_FLAG_SLOW) {
        q[2] += (v - q[2]) / 80;
    } else {
        q[2] += (v - q[2]) >> 4;
    }

    if (q[3] < q[2]) {
        q[2] = t;
        work->targetZ = t - 0x1C00;
    }
}

void MapEnm01PickTarget(MapEnmWork* work, u8 a) {
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;

    if (a) {
        work->targetX = gFieldState->actor.fieldPosition.x;
        work->targetY = gFieldState->actor.fieldPosition.y;
        work->targetZ = gFieldState->actor.fieldPosition.z - 0x1000;
    } else {
        work->targetX = gFieldState->actor.fieldPosition.x;
        work->targetY = gFieldState->actor.fieldPosition.y;
        work->targetZ = gFieldState->actor.fieldPosition.z;

        if (GetRandom() % 2) {
            t1 = GetRandom() % 65 * 256;
            t1 += 0x2000;
            work->targetX -= t1;
        } else {
            t2 = GetRandom() % 65 * 256;
            t2 += 0x2000;
            work->targetX += t2;
        }

        t3 = GetRandom() % 121 * 256;
        t3 -= 0x3C00;
        work->targetY += t3;
        t4 = GetRandom() % 49 * 256;
        t4 += 0x1000;
        work->targetZ -= t4;
    }
}

void MapEnm01Idle(MapEnmWork* work) {
    MapEnmWork* w = work;
    FldObj* q = &work->obj;

    MapEnmSetAnim(work, 0, 3);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);
    MapEnm01UpdateHover(work, 0);

    if (GetRandom() % 20 == 0) {
        q->angle = GetAngle(work->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if (q->fieldPosition.z < gFieldState->actor.fieldPosition.z - 0x4000) {
        MapEnm01PickTarget(work, 0);
        work->timer = 0;
        q->speed = 0;
        work->update = MapEnm01Fly;
    } else if (GetRandom() % 130 == 0) {
        if (GetRandom() % 2 != 0) {
            MapEnm01PickTarget(work, 0);
        } else {
            MapEnm01PickTarget(work, 1);
        }

        w->timer = 0;
        q->speed = 0;
        w->update = MapEnm01Fly;
    }

    if ((u8)MapEnmCheckAttacked(w)) {
        w->update = MapEnm01Hit;
    } else {
        MapEnmCheckContact(w);
        MapEnm01CheckOffscreen((MapEnm01Work*)work);
    }
}

void MapEnm01Fly(MapEnmWork* work) {
    FldObj* q = &work->obj;
    FldPos t;
    s32 dx;
    s32 dy;
    s32 v;
    s32 r;
    u32 lim;

    MapEnmSetAnim(work, 1, 3);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);
    MapEnm01UpdateHover(work, 1);
    t = work->obj.fieldPosition;

    if (GetRandom() % 20 != 0) {
        q->angle = GetAngle(work->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    dx = work->targetX;
    dy = work->targetY;

    if (work->flags & MAP_ENM_FLAG_SLOW) {
        lim = 0x140;
        q->speed += 10;

        if (q->speed > 76) {
            q->speed = 76;
        }
    } else {
        lim = 64;
        q->speed += 51;

        if (q->speed > 0x180) {
            q->speed = 0x180;
        }
    }

    v = (dx - q->fieldPosition.x) >> 5;

    if (v > q->speed) {
        v = q->speed;
    } else if (v < -q->speed) {
        v = -q->speed;
    }

    q->fieldPosition.x += v;
    v = (dy - q->fieldPosition.y) >> 5;

    if (v > q->speed) {
        v = q->speed;
    } else if (v < -q->speed) {
        v = -q->speed;
    }

    q->fieldPosition.y += v;

    if (work->timer > lim) {
        work->update = MapEnm01Idle;
    } else {
        work->timer++;
    }

    r = GetFldPosGround(&q->fieldPosition);

    if (r < q->fieldPosition.z) {
        q->fieldPosition = t;
        work->targetY = q->fieldPosition.y + 0x1000;
    } else if (r == 0x100000) {
        q->fieldPosition = t;
        work->targetY = q->fieldPosition.y - 0x1000;
    } else {
        q->fieldPosition.ground = r;
    }

    if ((u8)MapEnmCheckAttacked(work)) {
        work->update = MapEnm01Hit;
    } else {
        MapEnmCheckContact(work);
    }
}

void MapEnm01Hit(MapEnmWork* work) {
    MapEnmSetAnim(work, 2, 0);
    TaskPoolUpdate(&work->tasks);

    if (AnimIsFinished(&work->anim)) {
        work->flags |= MAP_ENM_FLAG_FIRST_STRIKE;
        MapEnmStartBattle(work);
    } else {
        MapEnmUpdateAnim(work);
    }
}

void MapEnm01Stand(MapEnmWork* work) {
    MapEnmSetAnim(work, 0, 0);
    work->gfx = AnimGetGfx(&work->anim);
    TaskPoolUpdate(&work->tasks);

    if ((u8)MapEnmCheckAttacked(work)) {
        work->update = MapEnm01Hit;
    } else {
        MapEnmCheckContact(work);
    }
}

void Task_MapEnm01_0(MapEnmWork* work, MapEnmArgs* q) {
    MapEnm01Work* w = (MapEnm01Work*)work;

    MapEnmInit(work, q);

    if (work->flags & MAP_ENM_FLAG_ASLEEP) {
        work->update = MapEnm01Stand;
        MapEnmSetAnim(work, 0, 0);
        work->gfx = AnimGetGfx(&work->anim);
        ColliderSetDisabled(&work->collider, 0);
    } else {
        work->update = MapEnm01Idle;
        MapEnmSetAnim(work, 0, 1);
        work->gfx = AnimGetGfx(&work->anim);
        ColliderSetDisabled(&work->collider, 0);
    }

    w->enm.timer = 0;
    ((MapEnm01Work*)work)->wasOnScreen = 0;
}

s32 Task_MapEnm01_1(MapEnmWork* work) {
    MapEnmWork* q = work;
    FldPos* pos = &work->obj.fieldPosition;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapEnmSaveToCache(work);
        return 0;
    }

    if ((gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) && work->update != MapEnm01Hit) {
        return 1;
    }

    if (work->update != NULL) {
        (work->update)(q);

        if (work->update != NULL) {
            ColliderSetPosition(&work->collider, pos->x, pos->y, pos->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm01_2(MapEnmWork* work) {
    MapEnmDraw(work);
}

void Task_MapEnm01_3(MapEnmWork* work) {
    MapEnmDestroy(work);
}

void MapEnm02Idle(MapEnmWork* work) {
    MapEnmSetAnim(work, 0, 1);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);

    if (IsHitByMapAttack(&work->obj.fieldPosition, work->radius, work->height)) {
        m4aSongNumStart(SONG_SYS_FIELD_ATT00);
        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        gMapRoomState->flags |= ROOM_FLAG_ENEMY_STRUCK;
        MapEnmStartBattle(work);
    }

    MapEnmCheckContact(work);
}

void Task_MapEnm02_0(MapEnmWork* work, MapEnmArgs* q) {
    MapEnmInit(work, q);
    work->update = MapEnm02Idle;
    MapEnmSetAnim(work, 0, 1);
    work->gfx = AnimGetGfx(&work->anim);
    ColliderSetDisabled(&work->collider, 0);
}

s32 Task_MapEnm02_1(MapEnmWork* work) {
    MapEnmWork* w = work;
    FldPos* q = &w->obj.fieldPosition;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapEnmSaveToCache(work);
        return 0;
    }

    if (w->update != NULL) {
        (w->update)(w);

        if (w->update != NULL) {
            ColliderSetPosition(&w->collider, q->x, q->y, q->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm02_2(MapEnmWork* work) {
    MapEnmDraw(work);
}

void Task_MapEnm02_3(MapEnmWork* work) {
    MapEnmDestroy(work);
}

void MapEnm03UpdateHover(MapEnmWork* work, u8 a) {
    s32* q = &work->obj.fieldPosition.x;
    s32 t = q[2];
    s32 v;

    switch (a) {
    case 1:
        v = work->targetZ + SIN(gFrameCounter) * 10;
        break;
    case 0:
    default:
        v = work->targetZ + SIN(gFrameCounter * 2) * 12;
        break;
    }

    if (work->flags & MAP_ENM_FLAG_SLOW) {
        q[2] += (v - q[2]) / 80;
    } else {
        q[2] += (v - q[2]) >> 4;
    }

    if (q[3] < q[2]) {
        q[2] = t;
        work->targetZ = t - 0x1C00;
    }
}

s32 MapEnm03MoveToTarget(MapEnmWork* work) {
    s32* q = &work->obj.fieldPosition.x;
    s32 dx;
    s32 dy;
    s32 lim;

    q[4] += 0x100;

    if (q[4] > 0x500) {
        q[4] = 0x500;
    }

    dx = (work->targetX - work->obj.fieldPosition.x) / 32;
    lim = q[4];

    if (dx > lim) {
        dx = lim;
    } else if (dx < -lim) {
        dx = -lim;
    }

    q[0] += dx;

    dy = (work->targetY - q[1]) / 32;

    if (dy > lim) {
        dy = lim;
    } else if (dy < -lim) {
        dy = -lim;
    }

    q[1] += dy;

    if (work->timer > 64) {
        return 1;
    }

    work->timer++;
    return 0;
}

s32 MapEnm03IsPlayerNearHome(MapEnm03Work* work, s32 lim) {
    s32 dx;
    s32 dy;

    dx = work->home.x - gFieldState->actor.fieldPosition.x;

    if (dx < 0) {
        dx = gFieldState->actor.fieldPosition.x - work->home.x;
    }

    dy = work->home.y - gFieldState->actor.fieldPosition.y;

    if (dy < 0) {
        dy = gFieldState->actor.fieldPosition.y - work->home.y;
    }

    if (dx > 0x8000 || dy > 0x8000) {
        return 0;
    }

    return Sqrt8((dx * dx >> 8) + (dy * dy >> 8)) < lim ? 1 : 0;
}

void MapEnm03Guard(MapEnmWork* work) {
    FldObj* q = &work->obj;

    MapEnmSetAnim(work, 0, 3);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);
    MapEnm03UpdateHover(work, 0);

    if (GetRandom() % 20 == 0) {
        q->angle = GetAngle(work->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if ((u8)MapEnm03IsPlayerNearHome((MapEnm03Work*)work, 0x6000) && q->fieldPosition.ground == gFieldState->actor.fieldPosition.ground) {
        work->targetX = gFieldState->actor.fieldPosition.x;
        work->targetY = gFieldState->actor.fieldPosition.y;
        work->targetZ = gFieldState->actor.fieldPosition.ground - 0x1000;
        work->timer = 0;
        q->speed = 0;
        work->update = MapEnm03Charge;
    }

    MapEnmCheckContact(work);
}

void MapEnm03Charge(MapEnmWork* work) {
    MapEnm03Work* q = (MapEnm03Work*)work;
    FldObj* v = &work->obj;
    FldPos tmp;
    s32 n;

    MapEnmSetAnim(work, 1, 3);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);
    MapEnm03UpdateHover(work, 1);
    tmp = v->fieldPosition;

    if (GetRandom() % 20 != 0) {
        v->angle = GetAngle(work->obj.fieldPosition.x, v->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if ((u8)MapEnm03IsPlayerNearHome((MapEnm03Work*)work, 0x6000) && v->fieldPosition.ground == gFieldState->actor.fieldPosition.ground) {
        work->targetX = gFieldState->actor.fieldPosition.x;
        work->targetY = gFieldState->actor.fieldPosition.y;
    }

    if ((u8)MapEnm03MoveToTarget(&q->enm)) {
        work->targetX = q->home.x;
        work->targetY = q->home.y;
        work->targetZ = q->home.z;
        work->timer = 0;
        v->speed = 0;
        work->update = MapEnm03Return;
    }

    n = GetFldPosGround(&v->fieldPosition);

    if (n < v->fieldPosition.z) {
        v->fieldPosition = tmp;
        work->targetY = v->fieldPosition.y + 0x1000;
    } else if (n == 0x100000) {
        v->fieldPosition = tmp;
        work->targetY = v->fieldPosition.y - 0x1000;
    } else {
        v->fieldPosition.ground = n;
    }

    MapEnmCheckContact(work);
}

void MapEnm03Return(MapEnmWork* work) {
    FldObj* q = &work->obj;
    FldPos save;
    s32 r;

    MapEnmSetAnim(work, 1, 3);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);
    MapEnm03UpdateHover(work, 1);
    save = q->fieldPosition;

    if (GetRandom() % 20 != 0) {
        q->angle = GetAngle(work->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if ((u8)MapEnm03MoveToTarget(work)) {
        work->timer = 0;
        q->speed = 0;
        work->update = MapEnm03Guard;
    }

    r = GetFldPosGround(&q->fieldPosition);

    if (r < q->fieldPosition.z) {
        q->fieldPosition = save;
        work->targetY = q->fieldPosition.y + 0x1000;
    } else if (r == 0x100000) {
        q->fieldPosition = save;
        work->targetY = q->fieldPosition.y - 0x1000;
    } else {
        q->fieldPosition.ground = r;
    }

    MapEnmCheckContact(work);
}

void Task_MapEnm03_0(MapEnmWork* work, MapEnmArgs* arg) {
    MapEnmInit(work, arg);
    work->update = MapEnm03Guard;
    MapEnmSetAnim(work, 0, 1);
    work->gfx = AnimGetGfx(&work->anim);
    ColliderSetDisabled(&work->collider, 0);
    work->timer = 0;
    ((MapEnm03Work*)work)->home = work->obj.fieldPosition;
}

s32 Task_MapEnm03_1(MapEnmWork* work) {
    MapEnmWork* w = work;
    FldPos* q = &w->obj.fieldPosition;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapEnmSaveToCache(work);
        return 0;
    }

    if (w->update != NULL) {
        (w->update)(w);

        if (w->update != NULL) {
            ColliderSetPosition(&w->collider, q->x, q->y, q->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm03_2(MapEnmWork* work) {
    MapEnmDraw(work);
}

void Task_MapEnm03_3(MapEnmWork* work) {
    MapEnmDestroy(work);
}

void MapEnm04CheckOffscreen(MapEnm01Work* work) {
    if (work->enm.obj.fieldPosition.x < gFieldState->x - 0x1800 || work->enm.obj.fieldPosition.x > gFieldState->x + 0x10800) {
        if (work->wasOnScreen) {
            work->enm.update = NULL;
        }
    } else if (!work->wasOnScreen) {
        work->wasOnScreen = 1;
    }
}

void MapEnm04UpdateHover(MapEnmWork* work, u8 a) {
    s32* q = &work->obj.fieldPosition.x;
    s32 t = q[2];
    s32 v;

    switch (a) {
    case 1:
        v = work->targetZ + SIN(gFrameCounter) * 10;
        break;
    case 0:
    default:
        v = work->targetZ + SIN(gFrameCounter * 2) * 12;
        break;
    }

    if (work->flags & MAP_ENM_FLAG_SLOW) {
        q[2] += (v - q[2]) / 80;
    } else {
        q[2] += (v - q[2]) >> 4;
    }

    if (q[3] < q[2]) {
        q[2] = t;
        work->targetZ = t - 0x1C00;
    }
}

void MapEnm04PickTarget(MapEnmWork* work, u8 flag) {
    if (flag) {
        work->targetX = gFieldState->actor.fieldPosition.x;
        work->targetY = gFieldState->actor.fieldPosition.y;
        work->targetZ = gFieldState->actor.fieldPosition.z - 0x1000;
    } else {
        work->targetX = gFieldState->actor.fieldPosition.x;
        work->targetY = gFieldState->actor.fieldPosition.y;
        work->targetZ = gFieldState->actor.fieldPosition.z;

        if (GetRandom() % 2) {
            s32 t = GetRandom() % 65 * 256 + 0x2000;

            work->targetX -= t;
        } else {
            s32 t = GetRandom() % 65 * 256 + 0x2000;

            work->targetX += t;
        }

        {
            s32 t = GetRandom() % 121 * 256 - 0x3C00;

            work->targetY += t;
        }

        {
            s32 t = GetRandom() % 49 * 256 + 0x1000;

            work->targetZ -= t;
        }
    }
}

void MapEnm04Idle(MapEnmWork* work) {
    MapEnmWork* r = work;
    FldObj* q = &work->obj;
    FldPos tmp;

    MapEnmSetAnim(work, 0, 3);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);
    tmp = work->obj.fieldPosition;
    MapEnm04UpdateHover(work, 0);

    if (GetRandom() % 20 == 0) {
        q->angle = GetAngle(work->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if (q->fieldPosition.z < gFieldState->actor.fieldPosition.z - 0x4000) {
        MapEnm04PickTarget(work, 0);
        work->timer = 0;
        q->speed = 0;
        work->update = MapEnm04Fly;
    } else if (GetRandom() % 130 == 0) {
        if (GetRandom() % 2) {
            MapEnm04PickTarget(work, 0);
        } else {
            MapEnm04PickTarget(work, 1);
        }

        r->timer = 0;
        q->speed = 0;
        r->update = MapEnm04Fly;
    }

    if ((u8)MapEnmCheckAttacked(r)) {
        r->update = MapEnm04Hit;
    } else {
        MapEnmCheckContact(r);
        MapEnm04CheckOffscreen((MapEnm01Work*)work);
    }
}

void MapEnm04Fly(MapEnmWork* work) {
    FldObj* q = &work->obj;
    FldPos t;
    s32 dx;
    s32 dy;
    s32 v;
    s32 r;
    u32 lim;

    MapEnmSetAnim(work, 1, 3);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);
    MapEnm04UpdateHover(work, 1);
    t = work->obj.fieldPosition;

    if (GetRandom() % 20 != 0) {
        q->angle = GetAngle(work->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    dx = work->targetX;
    dy = work->targetY;

    if (work->flags & MAP_ENM_FLAG_SLOW) {
        lim = 0x140;
        q->speed += 10;

        if (q->speed > 76) {
            q->speed = 76;
        }
    } else {
        lim = 64;
        q->speed += 51;

        if (q->speed > 0x180) {
            q->speed = 0x180;
        }
    }

    v = (dx - q->fieldPosition.x) >> 5;

    if (v > q->speed) {
        v = q->speed;
    } else if (v < -q->speed) {
        v = -q->speed;
    }

    q->fieldPosition.x += v;
    v = (dy - q->fieldPosition.y) >> 5;

    if (v > q->speed) {
        v = q->speed;
    } else if (v < -q->speed) {
        v = -q->speed;
    }

    q->fieldPosition.y += v;

    if (work->timer > lim) {
        work->update = MapEnm04Idle;
    } else {
        work->timer++;
    }

    r = GetFldPosGround(&q->fieldPosition);

    if (r < q->fieldPosition.z) {
        q->fieldPosition = t;
        work->targetY = q->fieldPosition.y + 0x1000;
    } else if (r == 0x100000) {
        q->fieldPosition = t;
        work->targetY = q->fieldPosition.y - 0x1000;
    } else {
        q->fieldPosition.ground = r;
    }

    if ((u8)MapEnmCheckAttacked(work)) {
        work->update = MapEnm04Hit;
    } else {
        MapEnmCheckContact(work);
    }
}

void MapEnm04Hit(MapEnmWork* work) {
    MapEnmSetAnim(work, 2, 0);
    TaskPoolUpdate(&work->tasks);

    if (AnimIsFinished(&work->anim)) {
        work->flags |= MAP_ENM_FLAG_FIRST_STRIKE;
        MapEnmStartBattle(work);
    } else {
        MapEnmUpdateAnim(work);
    }
}

void MapEnm04Stand(MapEnmWork* work) {
    MapEnmSetAnim(work, 0, 0);
    work->gfx = AnimGetGfx(&work->anim);
    TaskPoolUpdate(&work->tasks);

    if ((u8)MapEnmCheckAttacked(work)) {
        work->update = MapEnm04Hit;
    } else {
        MapEnmCheckContact(work);
    }
}

void Task_MapEnm04_0(MapEnmWork* work, MapEnmArgs* q) {
    MapEnm01Work* w = (MapEnm01Work*)work;

    MapEnmInit(work, q);

    if (work->flags & MAP_ENM_FLAG_ASLEEP) {
        work->update = MapEnm04Stand;
        MapEnmSetAnim(work, 0, 0);
        work->gfx = AnimGetGfx(&work->anim);
        ColliderSetDisabled(&work->collider, 0);
    } else {
        work->update = MapEnm04Idle;
        MapEnmSetAnim(work, 0, 1);
        work->gfx = AnimGetGfx(&work->anim);
        ColliderSetDisabled(&work->collider, 0);
    }

    w->enm.timer = 0;
    ((MapEnm01Work*)work)->wasOnScreen = 0;
}

s32 Task_MapEnm04_1(MapEnmWork* work) {
    MapEnmWork* q = work;
    FldPos* pos = &work->obj.fieldPosition;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapEnmSaveToCache(work);
        return 0;
    }

    if ((gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) && work->update != MapEnm04Hit) {
        return 1;
    }

    if (work->update != NULL) {
        (work->update)(q);

        if (work->update != NULL) {
            ColliderSetPosition(&work->collider, pos->x, pos->y, pos->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm04_2(MapEnmWork* work) {
    MapEnmDraw(work);
}

void Task_MapEnm04_3(MapEnmWork* work) {
    MapEnmDestroy(work);
}

void MapEnm05Appear(MapEnmWork* work) {
    MapEnmWork* q = work;

    MapEnmSetAnim(work, 0, 0);
    TaskPoolUpdate(&work->tasks);

    if (AnimIsFinished(&work->anim)) {
        ColliderSetDisabled(&work->collider, 0);
        work->timer = GetRandom() % 121 + 60;
        work->update = MapEnm05Idle;
    } else {
        MapEnmUpdateAnim(q);

        if (q->colliderDelay > 0) {
            q->colliderDelay--;

            if (q->colliderDelay <= 0) {
                ColliderSetDisabled(&q->collider, 0);
            }
        }
    }
}

void MapEnm05Idle(MapEnmWork* work) {
    MapEnmWork* q = work;
    FldObj* r = &work->obj;

    MapEnmSetAnim(work, 1, 1);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);

    if (GetRandom() % 20 == 0) {
        r->angle = GetAngle(work->obj.fieldPosition.x, r->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if ((u8)MapEnmCheckAttacked(work)) {
        work->update = MapEnm05Hit;
    } else {
        MapEnmCheckContact(work);

        if (work->timer != 0) {
            work->timer--;
        } else {
            ColliderSetDisabled(&q->collider, 1);
            q->update = MapEnm05Vanish;
        }
    }
}

void MapEnm05Vanish(MapEnmWork* work) {
    work->flags |= MAP_ENM_FLAG_REMOVED;
    MapEnmSetAnim(work, 2, 0);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);

    if (AnimIsFinished(&work->anim)) {
        work->update = NULL;
    }
}

void MapEnm05Hit(MapEnmWork* work) {
    MapEnmSetAnim(work, 3, 0);
    TaskPoolUpdate(&work->tasks);

    if (AnimIsFinished(&work->anim)) {
        work->flags |= MAP_ENM_FLAG_FIRST_STRIKE;
        MapEnmStartBattle(work);
    } else {
        MapEnmUpdateAnim(work);
    }
}

void Task_MapEnm05_0(MapEnmWork* work, MapEnmArgs* q) {
    MapEnmInit(work, q);

    if (work->update == NULL) {
        work->update = MapEnm05Appear;
        MapEnmSetAnim(work, 0, 0);
        work->gfx = AnimGetGfx(&work->anim);
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    work->timer = 0;
}

s32 Task_MapEnm05_1(MapEnmWork* work) {
    MapEnmWork* q = work;
    FldPos* pos = &work->obj.fieldPosition;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapEnmSaveToCache(work);
        return 0;
    }

    if ((gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) && work->update != MapEnm05Hit) {
        return 1;
    }

    if (work->update != NULL) {
        (work->update)(q);

        if (work->update != NULL) {
            ColliderSetPosition(&work->collider, pos->x, pos->y, pos->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm05_2(MapEnmWork* work) {
    MapEnmDraw(work);
}

void Task_MapEnm05_3(MapEnmWork* work) {
    MapEnmDestroy(work);
}

void MapEnm06Appear(MapEnmWork* work) {
    MapEnmWork* q = work;

    MapEnmSetAnim(work, 0, 0);
    TaskPoolUpdate(&work->tasks);

    if (AnimIsFinished(&work->anim)) {
        ColliderSetDisabled(&work->collider, 0);
        work->timer = GetRandom() % 121 + 60;
        work->update = MapEnm06Idle;
    } else {
        MapEnmUpdateAnim(q);

        if (q->colliderDelay > 0) {
            q->colliderDelay--;

            if (q->colliderDelay <= 0) {
                ColliderSetDisabled(&q->collider, 0);
            }
        }
    }
}

void MapEnm06Idle(MapEnmWork* work) {
    MapEnmWork* q = work;
    FldObj* r = &work->obj;

    MapEnmSetAnim(work, 1, 1);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);

    if (GetRandom() % 20 == 0) {
        r->angle = GetAngle(work->obj.fieldPosition.x, r->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if ((u8)MapEnmCheckAttacked(work)) {
        work->update = MapEnm06Hit;
    } else {
        MapEnmCheckContact(work);

        if (work->timer != 0) {
            work->timer--;
        } else {
            ColliderSetDisabled(&q->collider, 1);
            q->update = MapEnm06Vanish;
        }
    }
}

void MapEnm06Vanish(MapEnmWork* work) {
    work->flags |= MAP_ENM_FLAG_REMOVED;
    MapEnmSetAnim(work, 2, 0);
    MapEnmUpdateAnim(work);
    TaskPoolUpdate(&work->tasks);

    if (AnimIsFinished(&work->anim)) {
        work->update = NULL;
    }
}

void MapEnm06Hit(MapEnmWork* work) {
    MapEnmSetAnim(work, 3, 0);
    TaskPoolUpdate(&work->tasks);

    if (AnimIsFinished(&work->anim)) {
        work->flags |= MAP_ENM_FLAG_FIRST_STRIKE;
        MapEnmStartBattle(work);
    } else {
        MapEnmUpdateAnim(work);
    }
}

void Task_MapEnm06_0(MapEnmWork* work, MapEnmArgs* q) {
    MapEnmInit(work, q);

    if (work->update == NULL) {
        work->update = MapEnm06Appear;
        MapEnmSetAnim(work, 0, 0);
        work->gfx = AnimGetGfx(&work->anim);
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    work->timer = 0;
}

s32 Task_MapEnm06_1(MapEnmWork* work) {
    MapEnmWork* q = work;
    FldPos* pos = &work->obj.fieldPosition;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapEnmSaveToCache(work);
        return 0;
    }

    if ((gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) && work->update != MapEnm06Hit) {
        return 1;
    }

    if (work->update != NULL) {
        (work->update)(q);

        if (work->update != NULL) {
            ColliderSetPosition(&work->collider, pos->x, pos->y, pos->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm06_2(MapEnmWork* work) {
    MapEnmDraw(work);
}

void Task_MapEnm06_3(MapEnmWork* work) {
    MapEnmDestroy(work);
}

s32 GetMapRoomDebugCode(MapFloorRoom* p) {
    return (gGameState.floor << 28) + (p->roomType << 20) + (p->cardValue << 16) + (gMapFloorState.room << 8) + (gMapFloorState.eventStep << 4) + gMapFloorState.world;
}

void MapDbgWaitInput(MapDbgWork* work) {
    if ((GetKeysHeld() & (L_BUTTON | R_BUTTON)) == (L_BUTTON | R_BUTTON)) {
        if (GetKeysPressed() & SELECT_BUTTON) {
            *work->editing = 1;
            RequestFieldResume();
            ModeRequest(&gModeDebflag, 1);
        }

#ifndef VERSION_EU
        if (GetKeysPressed() & START_BUTTON) {
            work->visible = 1;
            *work->editing = 1;
            work->update = MapDbgEditSeed;
        }
#endif
    }
}

void MapDbgEditSeed(MapDbgWork* work) {
    MapFloorRoom* d;
    s32 step;
    s32 i;

    step = 1;

    for (i = work->seedCursor; i > 0; i--) {
        step <<= 4;
    }

    d = GetMapFloorRoom(gMapFloorState.room);

    if (GetKeysRepeat() & DPAD_UP) {
        d->seed += step;
    }

    if (GetKeysRepeat() & DPAD_DOWN) {
        d->seed -= step;
    }

    if (GetKeysPressed() & DPAD_LEFT) {
        work->seedCursor = work->seedCursor == 7 ? 0 : work->seedCursor + 1;
    }

    if (GetKeysPressed() & DPAD_RIGHT) {
        work->seedCursor = work->seedCursor == 0 ? 7 : work->seedCursor - 1;
    }

    work->seedTextLength = FormatSmallFontHex(d->seed, work->seedText);

    if (GetKeysPressed() & SELECT_BUTTON) {
        if (++gMapFloorState.world > 12) {
            gMapFloorState.world = 0;
        }

        work->codeTextLength = FormatSmallFontHex(GetMapRoomDebugCode(d), work->codeText);
    }

    if (GetKeysPressed() & (L_BUTTON | R_BUTTON)) {
        work->update = MapDbgEditWorld;
    } else if (GetKeysPressed() & (A_BUTTON | B_BUTTON | START_BUTTON)) {
        *work->editing = 0;
        work->update = MapDbgWaitInput;
    }
}

void MapDbgEditWorld(MapDbgWork* work) {
    MapFloorRoom* d = GetMapFloorRoom(gMapFloorState.room);

    if ((GetKeysRepeat() & DPAD_UP) && work->codeCursor == 0) {
        gMapFloorState.world = gMapFloorState.world < WORLD_CASTLE_OBLIVION ? gMapFloorState.world + 1 : 0;
    }

    if ((GetKeysRepeat() & DPAD_DOWN) && work->codeCursor == 0) {
        gMapFloorState.world = gMapFloorState.world != 0 ? gMapFloorState.world - 1 : 12;
    }

    work->codeTextLength = FormatSmallFontHex(GetMapRoomDebugCode(d), work->codeText);

    if (GetKeysPressed() & (L_BUTTON | R_BUTTON)) {
        work->update = MapDbgEditSeed;
    }

    if (GetKeysPressed() & (A_BUTTON | B_BUTTON | START_BUTTON)) {
        *work->editing = 0;
        work->update = MapDbgWaitInput;
    }
}

void Task_MapDbg_0(MapDbgWork* work, u8* p) {
#ifndef VERSION_EU
    MapFloorRoom* d;
#endif
    work->visible = 0;
    work->editing = p;
    *p = 0;
    work->update = MapDbgWaitInput;
    work->seedCursor = 0;
    work->codeCursor = 0;
#ifdef VERSION_EU
    GetMapFloorRoom(gMapFloorState.room);
#else
    d = GetMapFloorRoom(gMapFloorState.room);
    work->tiles = LoadSmallFontTiles();
    work->palette = LoadSmallFontPalette();
    work->seedTextLength = FormatSmallFontHex(d->seed, work->seedText);
    work->codeTextLength = FormatSmallFontHex(GetMapRoomDebugCode(d), work->codeText);
    work->cursorTextLength = EncodeSmallFontString(sMapDbgCursorString, &work->cursorText);
#endif
}

s32 Task_MapDbg_1(MapDbgWork* work) {
    work->update(work);
    return 1;
}

void Task_MapDbg_2(MapDbgWork* work) {
#ifndef VERSION_EU
    if (work->visible) {
        DrawSmallFontString(240 - work->seedTextLength * 8, 0x8E, work->seedText, work->tiles, work->palette, 0, work->seedTextLength);
        DrawSmallFontString(240 - work->codeTextLength * 8, 0x96, work->codeText, work->tiles, work->palette, 0, work->codeTextLength);

        if (*work->editing != 0) {
            if (work->update == MapDbgEditSeed) {
                DrawSmallFontString(240 - (work->seedCursor + 1) * 8, 0x90, &work->cursorText, work->tiles, work->palette, 0, work->cursorTextLength);
            } else {
                DrawSmallFontString(240 - (work->codeCursor + 1) * 8, 0x98, &work->cursorText, work->tiles, work->palette, 0, work->cursorTextLength);
            }
        }
    }
#endif
}

void Task_MapDbg_3(MapDbgWork* work) {
#ifndef VERSION_EU
    FreeSmallFontResources(work->tiles, work->palette);
#endif
}

void MapGmkJumpWaitStep(MapGmkJumpWork* work) {
    if (ColliderIsTouchingType(&work->collider, 1) && (work->collider.standFlags & COLLIDER_STAND_STOOD_ON)) {
        gMapRoomState->jumpGmkHeight = work->jumpHeight;
        gMapRoomState->jumpGmkAngle = work->obj.angle;
        work->update = MapGmkJumpWaitJump;
        work->state = 1;
        AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
    } else {
        AnimUpdate(&work->anim);
    }
}

void MapGmkJumpWaitJump(MapGmkJumpWork* work) {
    if (ColliderIsTouchingType(&work->collider, 1)) {
        gMapRoomState->jumpGmkHeight = work->jumpHeight;
        gMapRoomState->jumpGmkAngle = work->obj.angle;
    } else if (gFieldState->actor.fieldPosition.z != gFieldState->actor.fieldPosition.ground) {
        work->update = MapGmkJumpLaunch;
        work->state = 2;
        AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);
    } else {
        work->update = MapGmkJumpWaitStep;
        work->state = 0;
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    }
}

void MapGmkJumpLaunch(MapGmkJumpWork* work) {
    if (AnimIsFinished(&work->anim)) {
        work->update = MapGmkJumpWaitStep;
        work->state = 0;
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    } else {
        AnimUpdate(&work->anim);
    }
}

void Task_MapGmk_Jump_0(MapGmkJumpWork* work, MapPlatform* arg) {
    FldObj* p = &work->obj;
    AnimState* a;

    p->fieldPosition.x = arg->x << 13;
    p->fieldPosition.y = arg->y << 12;
    p->fieldPosition.z = 0;
    p->fieldPosition.z = work->obj.fieldPosition.ground = GetFldPosFloor(&p->fieldPosition);
    p->fieldPosition.y -= work->obj.fieldPosition.ground;

    switch (arg->spotType) {
    case 3:
        p->angle = 211;
        break;
    case 5:
        p->angle = 45;
        break;
    case 0:
    default:
        p->angle = 0;
        break;
    }

    work->jumpHeight = arg->spotLowerZ - arg->spotUpperZ;
    work->palette = LoadObjPalette(&gUnk_099912E4[0x10], 32);
    work->tiles = LoadObjTiles(gUnk_0985A3EA, 0x980);
    a = &work->anim;
    AnimInit(a, gUnk_09EF8488, gUnk_09EF8468);
    work->state = 0;
    AnimStart(a, 0, ANIM_FLAG_LOOP);
    work->update = MapGmkJumpWaitStep;
    ColliderInit(&work->collider, 6, 16, 0);
    ColliderSetPosition(&work->collider, p->fieldPosition.x, p->fieldPosition.y, p->fieldPosition.z);
}

s32 Task_MapGmk_Jump_1(MapGmkJumpWork* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (FldObjIsOutOfView(&work->obj)) {
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    if (work->update != NULL) {
        work->update(work);
    }

    return 1;
}

void Task_MapGmk_Jump_2(MapGmkJumpWork* work) {
    u16 v;
    s32 k;
    s16 x;
    s16 y;

    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = work->obj.fieldPosition.y >> 8;
    y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_Jump_3(MapGmkJumpWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

u8 MapGmkEnmRise(MapGmkEnmWork* work) {
    if (work->timer != 0) {
        work->gfx = AnimUpdate(&work->anim);
        ApproachValue(&work->obj.fieldPosition.z, work->targetZ, work->timer);
        work->timer--;
    } else {
        gMapRoomState->flags |= ROOM_FLAG_START_BATTLE;
        gFieldState->flags |= FIELD_FLAG_FREEZE_ENEMIES;
        gMapRoomState->battleId = GetRandomBattleId();
        work->update = NULL;
    }

    return 1;
}

void Task_MapGmk_Enm_0(MapGmkEnmWork* work, FldPos* arg) {
    FldPos* e = &work->obj.fieldPosition;
    AnimState* an;
    void* anim;
    void* frames;
    u8 f;

    work->obj.fieldPosition = *arg;
    work->obj.fieldPosition.y += 0x800;
    work->obj.fieldPosition.z -= 0x1000;
    work->obj.height = 16;

    if (gMapFloorState.world != WORLD_ATLANTICA) {
        work->tiles = AllocObjTiles(0x220, gEmy01L00Tiles);
        work->palette = LoadObjPalette(gEmy01Palette, 32);
        an = &work->anim;
        anim = gEmy01L00Anims;
        frames = gEmy01L00Frames;
    } else {
        work->tiles = AllocObjTiles(0x440, gEmy0600Tiles);
        work->palette = LoadObjPalette(gEmy06Palette, 32);
        an = &work->anim;
        anim = gEmy0600Anims;
        frames = gEmy0600Frames;
    }

    // fakematch
    do {
        AnimInit(an, anim, frames);
        AnimStart(an, 0, ANIM_FLAG_LOOP);
    } while (0);

    work->gfx = AnimGetGfx(an);
    work->update = MapGmkEnmRise;
    f = 0;

    if (gFieldState->actor.fieldPosition.x >= e->x) {
        f = 1;
    }

    work->flipX = f;
    work->timer = 8;
    work->targetZ = e->z - 0x1000;
}

u8 Task_MapGmk_Enm_1(MapGmkEnmWork* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (work->update != NULL) {
        return work->update(work);
    }

    return 1;
}

void Task_MapGmk_Enm_2(MapGmkEnmWork* work) {
    u16 flags;
    s32 k;
    s32 x;
    s32 y;
    s32 t;

    t = work->flipX;
    flags = SPRITE_PRIORITY(2);

    if (t) {
        flags = SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
    }

    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = work->obj.fieldPosition.y >> 8;
    y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, flags, -0x1004 - k * 4);
}

void Task_MapGmk_Enm_3(MapGmkEnmWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void Task_MapGmk_Dmy_0(MapGmkDmyWork* work) {
    work->tiles = AllocObjTiles(MapGmkGetFreeTiles() << 5, NULL);
}

s32 Task_MapGmk_Dmy_1() {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    return 1;
}

void Task_MapGmk_Dmy_2(MapGmkDmyWork* work) {
}

void Task_MapGmk_Dmy_3(MapGmkDmyWork* work) {
    if (work->tiles != NULL) {
        ReleaseObjTiles(work->tiles);
    }
}

u8 MapGmkTutorialWaitHit(MapGmkTutorialWork* work) {
    if (IsHitByMapAttack(&work->obj.fieldPosition, 0, 8)) {
        if ((gFieldState->flags & FIELD_FLAG_PLAYER_JUMPING) == 0 && gFieldState->actor.fieldPosition.z == gFieldState->actor.fieldPosition.ground) {
            TaskPool* pool = &work->tasks;

            TaskCreate(pool, &gTaskDescMapSpark, &work->obj);
            m4aSongNumStart(SONG_SND_220);
            gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
            gFieldState->lockonTarget = &work->obj;
            gMapRoomState->door = &work->obj;
            work->update = MapGmkTutorialWaitCard;
            gMapRoomState->doorRoom = 0;
            gMapRoomState->doorSide = 0;
            FadeSetPaletteExcluded(work->palette->index + 16, 1);
            TaskCreate(pool, &gTaskDescRoomcreate, NULL);
        }
    }

    return 1;
}

u8 MapGmkTutorialWaitCard(MapGmkTutorialWork* work) {
    void* p = GetSelectedMapCard();

    if (p != NULL) {
        CreateMapRoom(gUnk_0984C868[0].entryRoom, p);
        work->update = MapGmkTutorialWaitOpen;
    }

    if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) == 0) {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        FadeSetPaletteExcluded(work->palette->index + 16, 0);
        work->update = MapGmkTutorialWaitHit;
    }

    return 1;
}

u8 MapGmkTutorialWaitOpen(MapGmkTutorialWork* work) {
    if (gFieldState->flags & FIELD_FLAG_DOOR_OPENED) {
        UpdateSpriteFrameTiles(work->tiles, gMapUiSpriteUs_098A94A0, gUnk_0994C364);
        work->opened = 1;
        work->update = MapGmkTutorialIdle;
    }

    return 1;
}

u8 MapGmkTutorialIdle(MapGmkTutorialWork* work) {
    return 1;
}

void Task_MapGmk_Tutorial_0(MapGmkTutorialWork* work) {
    work->obj.fieldPosition.x = 0x19000;
    work->obj.fieldPosition.y = 0xAA00;
    work->obj.fieldPosition.z = 0;
    work->obj.fieldPosition.ground = GetFldPosFloor(&work->obj.fieldPosition);
    work->obj.fieldPosition.z = work->obj.fieldPosition.ground;
    work->obj.fieldPosition.y -= work->obj.fieldPosition.ground;
    work->obj.angle = 0xAD;
    work->obj.height = 32;
    work->palette = LoadObjPalette(gUnk_09991204, 32);
    work->tiles = AllocSpriteFrameTiles(0x400);
    UpdateSpriteFrameTiles(work->tiles, gMapUiSpriteUs_098A94A0, gUnk_0994BF64);
    ColliderInit(&work->collider, 6, 16, 0);
    ColliderSetPosition(&work->collider, work->obj.fieldPosition.x, work->obj.fieldPosition.y, work->obj.fieldPosition.z);
    work->opened = 0;
    work->update = MapGmkTutorialWaitHit;
    TaskPoolInit(&work->tasks, 2);
}

s32 Task_MapGmk_Tutorial_1(MapGmkTutorialWork* work) {
    if (work->opened && (work->collider.standFlags & COLLIDER_STAND_STOOD_ON) && work->collider.otherType == 1) {
        gMapRoomState->flags |= ROOM_FLAG_ENTER_WORLD;
    }

    if (work->update != NULL) {
        if (work->update(work) == 0) {
            return 0;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void Task_MapGmk_Tutorial_2(MapGmkTutorialWork* work) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = work->obj.fieldPosition.y >> 8;
    y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0xFE4 - k * 4;
    DrawSprite(x, y, NULL, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
    TaskPoolDraw(&work->tasks);
}

void Task_MapGmk_Tutorial_3(MapGmkTutorialWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
    TaskPoolDestroy(&work->tasks);
}

u8 MapGmkSpiderStartBattle(MapGmkSpiderWork* work) {
    AnimState* a = &work->anim;

    if (AnimIsFinished(a)) {
        gMapRoomState->flags |= ROOM_FLAG_START_BATTLE;
        gFieldState->flags |= FIELD_FLAG_FREEZE_ENEMIES;
        gMapRoomState->battleId = GetRandom() % 3 + 125;
        work->update = NULL;
    } else {
        work->gfx = AnimUpdate(a);
    }

    return 1;
}

void Task_MapGmk_Spider_0(MapGmkSpiderWork* work, MapGmkPlacement* arg) {
    u8 v;

    work->obj.fieldPosition = arg->pos;
    work->obj.height = 24;
    work->tiles = AllocObjTiles(0x720, gEmy2103Tiles);
    work->palette = LoadObjPalette(gEmy21Palette, 32);
    AnimInit(&work->anim, gEmy2103Anims, gEmy2103Frames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    SetObjTileSource(work->tiles, gEmy2103Tiles);
    work->update = MapGmkSpiderStartBattle;
    v = 0;

    if (gFieldState->actor.fieldPosition.x >= work->obj.fieldPosition.x) {
        v = 1;
    }

    work->flipX = v;
}

u8 Task_MapGmk_Spider_1(MapGmkSpiderWork* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (work->update != NULL) {
        return work->update(work);
    }

    return 1;
}

void Task_MapGmk_Spider_2(MapGmkSpiderWork* work) {
    u16 flags;
    u16 v;
    s32 t;
    s32 k;
    s32 x;
    s32 y;

    t = work->flipX;
    flags = SPRITE_PRIORITY(2);

    if (t) {
        flags = SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
    }

    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = work->obj.fieldPosition.y >> 8;
    y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, flags, v);
}

void Task_MapGmk_Spider_3(MapGmkSpiderWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

u8 MapGmkGp00WaitHit(MapGmkGpWork* work) {
    FldPos* p = &work->obj.fieldPosition;

    if (IsHitByMapAttack(p, 8, 8)) {
        m4aSongNumStart(work->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, p);

        if (!(work->placement->flags & GMK_FLAG_USED)) {
            work->placement->flags |= GMK_FLAG_USED;
            DropMapGmkPrize(p);
        }

        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        work->timer = 20;
        work->update = MapGmkGp00HitDelay;
    }

    return 1;
}

u8 MapGmkGp00HitDelay(MapGmkGpWork* work) {
    if (work->timer != 0) {
        work->timer--;
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        work->update = MapGmkGp00WaitHit;
    }

    return 1;
}

void Task_MapGmk_GP00_0(MapGmkGpWork* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;

    work->placement = arg;
    e->fieldPosition = arg->pos;
    work->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    work->tiles = LoadObjTiles(d->tiles, d->tilesSize);
    work->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&work->anim, d->anims, d->gfxTable);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    ColliderInit(&work->collider, 6, d->radius, d->height);
    ColliderSetPosition(&work->collider, work->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    work->hitSong = d->hitSong;
    work->timer = 0;
    work->update = MapGmkGp00WaitHit;
}

u8 Task_MapGmk_GP00_1(MapGmkGpWork* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (FldObjIsOutOfView(&work->obj)) {
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    if (work->update != NULL) {
        return work->update(work);
    }

    return 1;
}

void Task_MapGmk_GP00_2(MapGmkGpWork* work) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = work->obj.fieldPosition.y >> 8;
    y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_GP00_3(MapGmkGpWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

u8 MapGmkGp01WaitHit(MapGmkGp1Work* work) {
    FldPos* p = &work->obj.fieldPosition;

    if (FldObjIsOutOfView(&work->obj)) {
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    if (!IsHitByMapAttack(p, 8, 8)) {
        work->gfx = AnimUpdate(&work->anim);
    } else {
        m4aSongNumStart(work->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, p);
        DropMapGmkPrize(&work->obj.fieldPosition);
        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        work->placement->flags |= GMK_FLAG_DESTROYED;
        ColliderSetDisabled(&work->collider, 1);
        AnimStart(&work->anim, 1, 0);
        work->update = MapGmkGp01Break;
    }

    return 1;
}

u8 MapGmkGp01Break(MapGmkGp1Work* work) {
    AnimState* a = &work->anim;

    if (!AnimIsFinished(a)) {
        work->gfx = AnimUpdate(a);
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        work->visible = 0;
        work->update = NULL;
    }

    return 1;
}

void Task_MapGmk_GP01_0(MapGmkGp1Work* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;
    AnimState* a;

    work->placement = arg;
    e->fieldPosition = arg->pos;
    work->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    work->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    work->palette = LoadObjPalette(d->palette, 32);
    a = &work->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(a);
    SetObjTileSource(work->tiles, d->tiles);
    ColliderInit(&work->collider, 6, d->radius, d->height);
    ColliderSetPosition(&work->collider, work->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    work->hitSong = d->hitSong;
    work->visible = 1;
    work->update = MapGmkGp01WaitHit;
}

u8 Task_MapGmk_GP01_1(MapGmkGp1Work* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (work->update != NULL) {
        return work->update(work);
    }

    return 1;
}

void Task_MapGmk_GP01_2(MapGmkGp1Work* work) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    if (work->visible) {
        x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
        k = work->obj.fieldPosition.y >> 8;
        y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
    }
}

void Task_MapGmk_GP01_3(MapGmkGp1Work* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

u8 MapGmkGp02WaitHit(MapGmkGpWork* work) {
    FldPos* q = &work->obj.fieldPosition;

    if (IsHitByMapAttack(q, 8, 8)) {
        MapGmkPlacement* e;

        m4aSongNumStart(work->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);
        e = work->placement;

        if ((e->flags & GMK_FLAG_USED) == 0) {
            e->flags |= GMK_FLAG_USED;
            DropMapGmkPrize(q);
        }

        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        AnimStart(&work->anim, 1, 0);
        work->update = MapGmkGp02HitAnim;
    }

    return 1;
}

u8 MapGmkGp02HitAnim(MapGmkGpWork* work) {
    if (!AnimIsFinished(&work->anim)) {
        work->gfx = AnimUpdate(&work->anim);
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        AnimStart(&work->anim, 0, 0);
        work->gfx = AnimGetGfx(&work->anim);
        work->update = MapGmkGp02WaitHit;
    }

    return 1;
}

void Task_MapGmk_GP02_0(MapGmkGpWork* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;
    AnimState* a;

    work->placement = arg;
    e->fieldPosition = arg->pos;
    work->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    work->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    work->palette = LoadObjPalette(d->palette, 32);
    a = &work->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(a);
    SetObjTileSource(work->tiles, d->tiles);
    ColliderInit(&work->collider, 6, d->radius, d->height);
    ColliderSetPosition(&work->collider, work->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    work->hitSong = d->hitSong;
    work->update = MapGmkGp02WaitHit;
}

u8 Task_MapGmk_GP02_1(MapGmkGpWork* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (FldObjIsOutOfView(&work->obj)) {
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    if (work->update != NULL) {
        return work->update(work);
    }

    return 1;
}

void Task_MapGmk_GP02_2(MapGmkGpWork* work) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = work->obj.fieldPosition.y >> 8;
    y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_GP02_3(MapGmkGpWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

u8 MapGmkGp03WaitHit(MapGmkGpWork* work) {
    FldPos* q = &work->obj.fieldPosition;

    if (IsHitByMapAttack(q, 8, 8)) {
        m4aSongNumStart(work->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);
        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        AnimStart(&work->anim, 1, 0);
        work->update = MapGmkGp03HitAnim;
    }

    return 1;
}

u8 MapGmkGp03HitAnim(MapGmkGpWork* work) {
    AnimState* a = &work->anim;

    if (AnimIsFinished(a)) {
        MapGmkPlacement* e = work->placement;

        if ((e->flags & GMK_FLAG_USED) == 0) {
            e->flags |= GMK_FLAG_USED;
            DropMapGmkPrize(&work->obj.fieldPosition);
        }

        AnimStart(a, 2, 0);
        work->update = MapGmkGp03EndAnim;
    } else {
        work->gfx = AnimUpdate(a);
    }

    return 1;
}

u8 MapGmkGp03EndAnim(MapGmkGpWork* work) {
    if (!AnimIsFinished(&work->anim)) {
        work->gfx = AnimUpdate(&work->anim);
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        AnimStart(&work->anim, 0, 0);
        work->gfx = AnimGetGfx(&work->anim);
        work->update = MapGmkGp03WaitHit;
    }

    return 1;
}

void Task_MapGmk_GP03_0(MapGmkGpWork* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;
    AnimState* a;

    work->placement = arg;
    e->fieldPosition = arg->pos;
    work->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    work->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    work->palette = LoadObjPalette(d->palette, 32);
    a = &work->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(a);
    SetObjTileSource(work->tiles, d->tiles);
    ColliderInit(&work->collider, 6, d->radius, d->height);
    ColliderSetPosition(&work->collider, work->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    work->hitSong = d->hitSong;
    work->update = MapGmkGp03WaitHit;
}

u8 Task_MapGmk_GP03_1(MapGmkGpWork* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (FldObjIsOutOfView(&work->obj)) {
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    if (work->update != NULL) {
        return work->update(work);
    }

    return 1;
}

void Task_MapGmk_GP03_2(MapGmkGpWork* work) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = work->obj.fieldPosition.y >> 8;
    y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_GP03_3(MapGmkGpWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

u8 MapGmkGp04WaitHit(MapGmkGpWork* work) {
    FldPos* q = &work->obj.fieldPosition;
    AnimState* a = &work->anim;

    work->gfx = AnimUpdate(a);

    if ((work->placement->flags & GMK_FLAG_USED) == 0 && IsHitByMapAttack(q, 8, 8)) {
        m4aSongNumStart(work->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);
        DropMapGmkPrize(q);
        work->placement->flags |= GMK_FLAG_USED;
        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        AnimStart(a, 1, ANIM_FLAG_LOOP);
        work->timer = 20;
        work->update = MapGmkGp04HitDelay;
    }

    return 1;
}

u8 MapGmkGp04HitDelay(MapGmkGpWork* work) {
    work->gfx = AnimUpdate(&work->anim);

    if (work->timer != 0) {
        work->timer--;
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        work->update = NULL;
    }

    return 1;
}

void Task_MapGmk_GP04_0(MapGmkGpWork* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;

    work->placement = arg;
    e->fieldPosition = arg->pos;
    work->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    work->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    work->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&work->anim, d->anims, d->gfxTable);

    if (work->placement->flags & GMK_FLAG_USED) {
        AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
    } else {
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    }

    work->gfx = AnimGetGfx(&work->anim);
    SetObjTileSource(work->tiles, d->tiles);
    ColliderInit(&work->collider, 6, d->radius, d->height);
    ColliderSetPosition(&work->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    work->hitSong = d->hitSong;
    work->update = MapGmkGp04WaitHit;
}

u8 Task_MapGmk_GP04_1(MapGmkGpWork* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (FldObjIsOutOfView(&work->obj)) {
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    if (work->update != NULL) {
        return work->update(work);
    }

    return 1;
}

void Task_MapGmk_GP04_2(MapGmkGpWork* work) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = work->obj.fieldPosition.y >> 8;
    y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_GP04_3(MapGmkGpWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

u8 MapGmkGp05WaitHit(MapGmkGpWork* work) {
    FldPos* q = &work->obj.fieldPosition;

    if (!(work->placement->flags & GMK_FLAG_USED) && IsHitByMapAttack(q, 8, 8)) {
        m4aSongNumStart(work->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);
        DropMapGmkPrize(q);
        work->placement->flags |= GMK_FLAG_USED;
        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        AnimStart(&work->anim, 1, 0);
        work->update = MapGmkGp05HitAnim;
    }

    return 1;
}

u8 MapGmkGp05HitAnim(MapGmkGpWork* work) {
    AnimState* a = &work->anim;

    if (!AnimIsFinished(a)) {
        work->gfx = AnimUpdate(a);
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        AnimStart(a, 2, 0);
        work->gfx = AnimGetGfx(a);
        work->update = NULL;
    }

    return 1;
}

void Task_MapGmk_GP05_0(MapGmkGpWork* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;

    work->placement = arg;
    e->fieldPosition = arg->pos;
    work->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    work->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    work->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&work->anim, d->anims, d->gfxTable);

    if (work->placement->flags & GMK_FLAG_USED) {
        AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);
    } else {
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    }

    work->gfx = AnimGetGfx(&work->anim);
    SetObjTileSource(work->tiles, d->tiles);
    ColliderInit(&work->collider, 6, d->radius, d->height);
    ColliderSetPosition(&work->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    work->hitSong = d->hitSong;
    work->update = MapGmkGp05WaitHit;
}

u8 Task_MapGmk_GP05_1(MapGmkGpWork* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (FldObjIsOutOfView(&work->obj)) {
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    if (work->update != NULL) {
        return work->update(work);
    }

    return 1;
}

void Task_MapGmk_GP05_2(MapGmkGpWork* work) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = work->obj.fieldPosition.y >> 8;
    y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_GP05_3(MapGmkGpWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

u8 MapGmkGp06WaitHit(MapGmkGpWork* work) {
    FldPos* q = &work->obj.fieldPosition;
    AnimState* a = &work->anim;

    work->gfx = AnimUpdate(a);

    if (IsHitByMapAttack(q, 8, 8)) {
        m4aSongNumStart(work->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);

        if ((work->placement->flags & GMK_FLAG_USED) == 0) {
            work->placement->flags |= GMK_FLAG_USED;
            DropMapGmkPrize(q);
        }

        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;

        if (work->placement->flags & GMK_FLAG_TOGGLED) {
            work->placement->flags &= ~GMK_FLAG_TOGGLED;
            AnimStart(a, 0, ANIM_FLAG_LOOP);
        } else {
            work->placement->flags |= GMK_FLAG_TOGGLED;
            AnimStart(a, 1, ANIM_FLAG_LOOP);
        }

        work->timer = 20;
        work->update = MapGmkGp06HitDelay;
    }

    return 1;
}

u8 MapGmkGp06HitDelay(MapGmkGpWork* work) {
    work->gfx = AnimUpdate(&work->anim);

    if (work->timer != 0) {
        work->timer--;
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        work->update = MapGmkGp06WaitHit;
    }

    return 1;
}

void Task_MapGmk_GP06_0(MapGmkGpWork* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;

    work->placement = arg;
    e->fieldPosition = arg->pos;
    work->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    work->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    work->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&work->anim, d->anims, d->gfxTable);

    if (work->placement->flags & GMK_FLAG_TOGGLED) {
        AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
    } else {
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    }

    work->gfx = AnimGetGfx(&work->anim);
    SetObjTileSource(work->tiles, d->tiles);
    ColliderInit(&work->collider, 6, d->radius, d->height);
    ColliderSetPosition(&work->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    work->hitSong = d->hitSong;
    work->update = MapGmkGp06WaitHit;
}

u8 Task_MapGmk_GP06_1(MapGmkGpWork* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (FldObjIsOutOfView(&work->obj)) {
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    if (work->update != NULL) {
        return work->update(work);
    }

    return 1;
}

void Task_MapGmk_GP06_2(MapGmkGpWork* work) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = work->obj.fieldPosition.y >> 8;
    y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_GP06_3(MapGmkGpWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

s32 MapGmkGp07WaitStep(MapGmkGp07Work* work) {
    AnimState* a = &work->anim;

    work->gfx = AnimUpdate(a);

    if (ColliderIsTouchingType(&work->collider, 1)) {
        if (work->collider.standFlags & COLLIDER_STAND_STOOD_ON) {
            if (!(work->placement->flags & GMK_FLAG_USED)) {
                work->placement->flags |= GMK_FLAG_USED;
                DropMapGmkPrize(&work->obj.fieldPosition);
            }

            AnimStart(a, 1, 0);
            work->gfx = AnimGetGfx(a);
            work->update = MapGmkGp07WaitStepOff;
        }
    }

    return 1;
}

s32 MapGmkGp07WaitStepOff(MapGmkGp07Work* work) {
    work->gfx = AnimUpdate(&work->anim);

    if (!ColliderIsTouchingType(&work->collider, 1)) {
        AnimStart(&work->anim, 2, 0);
        work->update = MapGmkGp07EndAnim;
    }

    return 1;
}

s32 MapGmkGp07EndAnim(MapGmkGp07Work* work) {
    AnimState* a = &work->anim;

    if (AnimIsFinished(a)) {
        AnimStart(a, 0, ANIM_FLAG_LOOP);
        work->gfx = AnimGetGfx(a);
        work->update = MapGmkGp07WaitStep;
    } else {
        work->gfx = AnimUpdate(a);
    }

    return 1;
}

void Task_MapGmk_GP07_0(MapGmkGp07Work* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;

    work->placement = arg;
    e->fieldPosition = arg->pos;
    work->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    work->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    work->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&work->anim, d->anims, d->gfxTable);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    SetObjTileSource(work->tiles, d->tiles);
    ColliderInit(&work->collider, 6, d->radius, d->height);
    ColliderSetPosition(&work->collider, work->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    work->update = MapGmkGp07WaitStep;
}

u8 Task_MapGmk_GP07_1(MapGmkGp07Work* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (FldObjIsOutOfView(&work->obj)) {
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    if (work->update != NULL) {
        return work->update(work);
    }

    return 1;
}

void Task_MapGmk_GP07_2(MapGmkGp07Work* work) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = work->obj.fieldPosition.y >> 8;
    y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_GP07_3(MapGmkGp07Work* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

s32 MapGmkGp08WaitHit(MapGmkGp08Work* work) {
    FldPos* q = &work->obj.fieldPosition;
    AnimState* a;

    if (IsHitByMapAttack(q, 8, 8)) {
        m4aSongNumStart(work->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);

        if (!(work->placement->flags & GMK_FLAG_USED)) {
            work->placement->flags |= GMK_FLAG_USED;
            DropMapGmkPrize(q);
        }

        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        a = &work->anim;
        AnimStart(a, 1, 0);
        work->gfx2 = AnimGetGfx(a);
        work->overlayVisible = 1;
        work->update = MapGmkGp08HitAnim;
    }

    return 1;
}

s32 MapGmkGp08HitAnim(MapGmkGp08Work* work) {
    AnimState* a = &work->anim;

    if (!AnimIsFinished(a)) {
        work->gfx2 = AnimUpdate(a);
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        work->overlayVisible = 0;
        work->update = MapGmkGp08WaitHit;
    }

    return 1;
}

void Task_MapGmk_GP08_0(MapGmkGp08Work* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;

    work->placement = arg;
    e->fieldPosition = arg->pos;
    work->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    work->tiles = LoadObjTiles(d->tiles, d->tilesSize);
    work->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&work->anim, d->anims, d->gfxTable);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    ColliderInit(&work->collider, 6, d->radius, d->height);
    ColliderSetPosition(&work->collider, work->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    work->hitSong = d->hitSong;
    work->overlayVisible = 0;
    work->update = MapGmkGp08WaitHit;
}

u8 Task_MapGmk_GP08_1(MapGmkGp08Work* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (FldObjIsOutOfView(&work->obj)) {
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    if (work->update != NULL) {
        return work->update(work);
    }

    return 1;
}

void Task_MapGmk_GP08_2(MapGmkGp08Work* work) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = work->obj.fieldPosition.y >> 8;
    y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);

    if (work->overlayVisible) {
        DrawSprite(x, y, work->gfx2, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v - 1);
    }
}

void Task_MapGmk_GP08_3(MapGmkGp08Work* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

s32 MapGmkGp09WaitStep(MapGmkGp09Work* work) {
    AnimState* a = &work->anim;

    work->gfx2 = AnimUpdate(a);

    if (ColliderIsTouchingType(&work->collider, 1)) {
        if (work->collider.standFlags & COLLIDER_STAND_STOOD_ON) {
            if (!(work->placement->flags & GMK_FLAG_USED)) {
                work->placement->flags |= GMK_FLAG_USED;
                DropMapGmkPrize(&work->obj.fieldPosition);
            }

            AnimStart(a, 1, 0);
            work->gfx2 = AnimGetGfx(a);
            work->overlayVisible = 1;
            work->update = MapGmkGp09StepAnim;
        }
    }

    return 1;
}

s32 MapGmkGp09StepAnim(MapGmkGp09Work* work) {
    if (AnimIsFinished(&work->anim)) {
        work->overlayVisible = 0;
        work->update = MapGmkGp09WaitStepOff;
    } else {
        work->gfx2 = AnimUpdate(&work->anim);
    }

    return 1;
}

s32 MapGmkGp09WaitStepOff(MapGmkGp09Work* work) {
    if (!ColliderIsTouchingType(&work->collider, 1)) {
        work->update = MapGmkGp09WaitStep;
    }

    return 1;
}

void Task_MapGmk_GP09_0(MapGmkGp09Work* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;

    work->placement = arg;
    e->fieldPosition = arg->pos;
    work->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    work->tiles = LoadObjTiles(d->tiles, d->tilesSize);
    work->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&work->anim, d->anims, d->gfxTable);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    ColliderInit(&work->collider, 6, d->radius, d->height);
    ColliderSetPosition(&work->collider, work->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    work->overlayVisible = 0;
    work->update = MapGmkGp09WaitStep;
}

u8 Task_MapGmk_GP09_1(MapGmkGp09Work* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (FldObjIsOutOfView(&work->obj)) {
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    if (work->update != NULL) {
        return work->update(work);
    }

    return 1;
}

void Task_MapGmk_GP09_2(MapGmkGp09Work* work) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = work->obj.fieldPosition.y >> 8;
    y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);

    if (work->overlayVisible) {
        DrawSprite(x, y, work->gfx2, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v - 1);
    }
}

void Task_MapGmk_GP09_3(MapGmkGp09Work* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

void Task_MapGmk00_0(MapGmk00Work* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;
    AnimState* a;

    work->placement = arg;
    e->fieldPosition = arg->pos;
    work->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    work->tiles = LoadObjTiles(d->tiles, d->tilesSize);
    work->palette = LoadObjPalette(d->palette, 32);
    a = &work->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(a);
    ColliderInit(&work->collider, 6, d->radius, d->height);
    ColliderSetPosition(&work->collider, work->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);

    if (FldObjIsOutOfView(e)) {
        ColliderSetDisabled(&work->collider, 1);
    }

    work->radius = d->radius;
    work->stoodOn = 0;
    work->visible = 1;
    work->unk_0C6 = 0;
}

u8 Task_MapGmk00_1(MapGmk00Work* work) {
    FldPos* q = &work->obj.fieldPosition;
    u16 t;

    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (FldObjIsOutOfView(&work->obj)) {
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    if (!(work->placement->flags & GMK_FLAG_USED)) {
        t = work->collider.standFlags & COLLIDER_STAND_STOOD_ON;

        if (t != 0) {
            if (work->stoodOn != 1) {
                work->stoodOn = 1;
                work->placement->flags |= GMK_FLAG_USED;
                DropMapGmkPrize(q);
            }
        } else {
            work->stoodOn = 0;
        }
    }

    return 1;
}

void Task_MapGmk00_2(MapGmk00Work* work) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    if (work->visible) {
        x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
        k = work->obj.fieldPosition.y >> 8;
        y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
    }
}

void Task_MapGmk00_3(MapGmk00Work* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

u8 MapGmk01WaitHit(MapGmk01Work* work) {
    if (IsHitByMapAttack(&work->obj.fieldPosition, 8, 8)) {
        AnimState* a;

        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        m4aSongNumStart(SONG_SYS_TRESURE);
        a = &work->anim;
        AnimStart(a, 1, ANIM_FLAG_LOOP);
        work->gfx = AnimGetGfx(a);
        SetObjTileSource(work->tiles, gUnk_09858320);
        work->update = MapGmk01Open;
    }

    return 1;
}

u8 MapGmk01Open(MapGmk01Work* work) {
    FldPos* q = &work->obj.fieldPosition;

    if (work->placement->flags & GMK_FLAG_HAS_ENEMY) {
        gMapRoomState->flags |= ROOM_FLAG_ENEMY_STRUCK;
        work->placement->flags |= GMK_FLAG_USED;
        TaskCreate(&gFieldState->tasks, &sTaskDescMapGmkEnm, q);
        work->update = NULL;
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_NO_RANDOM_PRIZE;
        CreateWorldPrize(gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y, gFieldState->actor.fieldPosition.z);
        GetMapFloorRoom(gMapFloorState.room)->flags |= FLOOR_ROOM_FLAG_CHEST_OPENED;
        work->placement->flags |= GMK_FLAG_USED;
        work->timer = 20;
        work->update = MapGmk01WaitPrize;
    }

    return 1;
}

u8 MapGmk01WaitPrize(MapGmk01Work* work) {
    if (work->timer != 0) {
        if (!IsMessageWindowOpen()) {
            work->timer--;
        }
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        work->update = NULL;
    }

    return 1;
}

void Task_MapGmk01_0(MapGmk01Work* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;
    AnimState* a;

    work->placement = arg;
    e->fieldPosition = arg->pos;
    e->height = d->height;
    work->tiles = AllocObjTiles(0x320, gUnk_09858320);
    work->palette = LoadObjPalette(d->palette, 32);
    a = &work->anim;
    AnimInit(a, d->anims, d->gfxTable);

    if (work->placement->flags & GMK_FLAG_USED) {
        AnimStart(a, 1, ANIM_FLAG_LOOP);
        work->gfx = AnimGetGfx(a);
        work->update = NULL;
    } else {
        gMapRoomState->flags |= ROOM_FLAG_NO_RANDOM_PRIZE;
        AnimStart(a, 0, ANIM_FLAG_LOOP);
        work->gfx = AnimGetGfx(a);
        work->update = MapGmk01WaitHit;
    }

    SetObjTileSource(work->tiles, gUnk_09858320);
    ColliderInit(&work->collider, 6, d->radius, d->height);
    ColliderSetPosition(&work->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
}

u8 Task_MapGmk01_1(MapGmk01Work* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (work->update != NULL) {
        return work->update(work);
    }

    return 1;
}

void Task_MapGmk01_2(MapGmk01Work* work) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = work->obj.fieldPosition.y >> 8;
    y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk01_3(MapGmk01Work* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

void MapGmkBarrelDropPrizes(FldPos* p) {
    u16 r;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        r = GetRandom() % 10000;

        if (r < 6000) {
            CreateMapPrizeTasks(0, 5, p->x, p->y, p->z);
        } else if (r < 10000) {
            CreateMapPrizeTasks(1, 3, p->x, p->y, p->z);
        }
    } else {
        r = GetRandom() % 10000;

        if (r < 3000) {
            CreateMapPrizeTasks(0, 5, p->x, p->y, p->z);
        } else if (r < 5000) {
            CreateMapPrizeTasks(1, 3, p->x, p->y, p->z);
        } else if (r < 8000) {
            CreateMapPrizeTasks(2, 5, p->x, p->y, p->z);
        } else {
            CreateMapPrizeTasks(3, 5, p->x, p->y, p->z);
        }
    }
}

u8 MapGmkBarrelWaitHit(MapGmkBarrelWork* work) {
    FldPos* p = &work->obj.fieldPosition;
    u16 r;

    if (IsHitByMapAttack(p, 8, 8)) {
        r = GetRandom() % 10000;

        if (r <= 1499) {
            m4aSongNumStart(SONG_SYS_OBJ_BREAK);
            TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, p);
            gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
            gMapRoomState->flags |= ROOM_FLAG_ENEMY_STRUCK;
            work->placement->flags |= GMK_FLAG_DESTROYED;
            TaskCreate(&gFieldState->tasks, &sTaskDescMapGmkSpider, work->placement);
            return 0;
        }

        m4aSongNumStart(SONG_SYS_OBJ_BREAK);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, p);

        if (r <= 5999) {
            if (TryCreateRandomPrzCard(0, p->x, p->y, p->z) != 1) {
                MapGmkBarrelDropPrizes(p);
            }
        } else if (r <= 9999) {
            MapGmkBarrelDropPrizes(p);
        }

        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        work->placement->flags |= GMK_FLAG_DESTROYED;
        ColliderSetDisabled(&work->collider, 1);
        AnimStart(&work->anim, 1, 0);
        work->update = MapGmkBarrelBreak;
        return 1;
    }

    if (FldObjIsOutOfView(&work->obj)) {
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetDisabled(&work->collider, 0);
    }

    return 1;
}

u8 MapGmkBarrelBreak(MapGmkBarrelWork* work) {
    AnimState* a = &work->anim;

    if (!AnimIsFinished(a)) {
        work->gfx = AnimUpdate(a);
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        work->visible = 0;
        work->update = NULL;
    }

    return 1;
}

void Task_MapGmk_Barrel_0(MapGmkBarrelWork* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;
    AnimState* a;

    work->placement = arg;
    e->fieldPosition = arg->pos;
    work->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    work->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    work->palette = LoadObjPalette(d->palette, 32);
    a = &work->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(a);
    SetObjTileSource(work->tiles, d->tiles);
    ColliderInit(&work->collider, 6, d->radius, d->height);
    ColliderSetPosition(&work->collider, work->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    work->visible = 1;
    work->update = MapGmkBarrelWaitHit;
}

u8 Task_MapGmk_Barrel_1(MapGmkBarrelWork* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (work->update != NULL) {
        return work->update(work);
    }

    return 1;
}

void Task_MapGmk_Barrel_2(MapGmkBarrelWork* work) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    if (work->visible) {
        x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
        k = work->obj.fieldPosition.y >> 8;
        y = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
    }
}

void Task_MapGmk_Barrel_3(MapGmkBarrelWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

void MapGmk04CheckTalk(MapGmk04Work* work) {
    if ((gMapRoomState->flags & ROOM_FLAG_TUTORIAL_ACTIVE) == 0 && (u8)IsFldObjTalkTarget(&work->obj) && (GetKeysPressed() & A_BUTTON)) {
        m4aSongNumStart(SONG_SYS_KETTEI);
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSave, NULL);
        work->update = NULL;
    }
}

void MapGmk04CheckFirstTalk(MapGmk04Work* work) {
    u32 state = gMapRoomState->flags;

    if (state & ROOM_FLAG_TUTORIAL_ACTIVE) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        CreateCardMessageTask(&work->tasks, 0, 0x69);
        work->update = MapGmk04WaitFirstTalkEnd;
    } else if (gFieldState->lockonTarget == &work->obj) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        gMapRoomState->flags = state | 0x4000;
        CreateCardMessageTask(&work->tasks, 0, 0x67);
        work->update = MapGmk04WaitMessage;
    }
}

void MapGmk04WaitMessage(MapGmk04Work* work) {
    if (!IsMessageWindowOpen()) {
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSave, NULL);
        work->update = NULL;
    }
}

void MapGmk04WaitFirstTalkEnd(MapGmk04Work* work) {
    if (!IsMessageWindowOpen()) {
        gMapRoomState->flags &= ~ROOM_FLAG_TUTORIAL_ACTIVE;
        gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
        gGameState.progression.tutorialFlags |= 0x10;
        work->update = MapGmk04CheckTalk;
    }
}

void Task_MapGmk04_0(MapGmk04Work* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;

    work->placement = arg;
    e->fieldPosition = arg->pos;
    e->height = d->height;
    e->kind = 3;

    if (gGameState.progression.tutorialFlags & 0x10) {
        work->update = MapGmk04CheckTalk;
    } else {
        work->update = MapGmk04CheckFirstTalk;
    }

    work->palette = LoadObjPalette(d->palette, 32);
    work->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    AnimInit(&work->anim, d->anims, d->gfxTable);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    ColliderInit(&work->collider, 4, 24, 24);
    ColliderSetPosition(&work->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    TaskPoolInit(&work->tasks, 1);
    FldObjRegister(e);
}

s32 Task_MapGmk04_1(MapGmk04Work* work) {
    TaskPoolUpdate(&work->tasks);

    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    work->gfx = AnimUpdate(&work->anim);

    if (work->update != NULL) {
        work->update(work);

        if (work->update != NULL) {
            return 1;
        }
    }

    return 0;
}

void Task_MapGmk04_2(MapGmk04Work* work) {
    FldPos* p = &work->obj.fieldPosition;
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    TaskPoolDraw(&work->tasks);
    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = p->y >> 8;
    y = k + (p->z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk04_3(MapGmk04Work* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
    TaskPoolDestroy(&work->tasks);
    FldObjUnregister(&work->obj);
}

void MapGmk05CheckTalk(MapGmk05Work* work) {
    if (work->targeted && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        RequestFieldResume();
        FadeStartOut(FADE_MODE_BLACK, 16);
        m4aSongNumStart(SONG_SYS_MOUGURI);
        work->update = MapGmk05EnterShop;
    }
}

void MapGmk05EnterShop(MapGmk05Work* work) {
    MapFloorRoom* e;

    if (FadeIsActive()) {
        return;
    }

    e = GetMapFloorRoom(gMapFloorState.room);

    if (e->flags & FLOOR_ROOM_FLAG_SHOP_VISITED) {
        ModeRequest(&gModeMsTop, 0);
    } else {
        e->flags |= FLOOR_ROOM_FLAG_SHOP_VISITED;
        ModeRequest(&gModeMsTop, 1);
    }

    work->update = NULL;
}

void Task_MapGmk05_0(MapGmk05Work* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;
    AnimState* a;

    e->fieldPosition = arg->pos;
    e->height = d->height;
    e->kind = 2;
    work->update = MapGmk05CheckTalk;
    work->palette = LoadObjPalette(d->palette, 32);
    work->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    a = &work->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(a);
    ColliderInit(&work->collider, 4, 16, 24);
    ColliderSetPosition(&work->collider, work->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    FldObjRegister(e);
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescFldShadow, e);
    work->targeted = 0;
    TaskPoolInit(&work->tasks2, 1);
    TaskCreate(&work->tasks2, &gTaskDescMapTalk, e);
}

s32 Task_MapGmk05_1(MapGmk05Work* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&work->tasks2);
    work->gfx = AnimUpdate(&work->anim);
    work->targeted = IsFldObjTalkTarget(&work->obj);

    if (work->update != NULL) {
        work->update(work);

        if (work->update != NULL) {
            return 1;
        }
    }

    return 0;
}

void Task_MapGmk05_2(MapGmk05Work* work) {
    FldObj* p = &work->obj;
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    k = p->fieldPosition.y >> 8;
    v = -0x1004 - k * 4;
    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    y = k + (p->fieldPosition.z >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
    p->shadowZ = p->fieldPosition.ground;
    p->shadowPriority = v + 1;
    TaskPoolDraw(&work->tasks);

    if (work->targeted) {
        TaskPoolDraw(&work->tasks2);
    }
}

void Task_MapGmk05_3(MapGmk05Work* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
    FldObjUnregister(&work->obj);
    TaskPoolDestroy(&work->tasks);
    TaskPoolDestroy(&work->tasks2);
}

void MapGmk06CheckTalk(MapGmk06Work* work) {
    if (gFieldState->lockonTarget == &work->obj && (gGameState.progression.tutorialFlags & 0x100) == 0) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        gMapRoomState->flags |= ROOM_FLAG_TUTORIAL_ACTIVE;
        CreateCardMessageTask(&work->tasks, 0, 0x84);
        gFieldState->lockonDelay = 30;
        work->update = MapGmk06WaitMessage;
    } else if ((u8)IsFldObjTalkTarget(&work->obj) && (GetKeysPressed() & A_BUTTON)) {
        m4aSongNumStart(SONG_SYS_KETTEI);
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        RequestFieldResume();
        FadeStartOut(FADE_MODE_BLACK, 16);
        work->update = MapGmk06EnterWorldWarp;
    }
}

void MapGmk06EnterWorldWarp(MapGmk06Work* work) {
    if (!FadeIsActive()) {
        ModeRequest(&gModeWorldwarp, 0);
        work->update = NULL;
    }
}

void MapGmk06WaitMessage(MapGmk06Work* work) {
    if (!IsMessageWindowOpen()) {
        gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
        gMapRoomState->flags &= ~ROOM_FLAG_TUTORIAL_ACTIVE;
        gGameState.progression.tutorialFlags |= 0x100;
        work->update = MapGmk06CheckTalk;
    } else {
        gFieldState->lockonDelay = 30;
    }
}

void Task_MapGmk06_0(MapGmk06Work* work, MapGmkPlacement* arg) {
    FldObj* e = &work->obj;
    const MapGmkDef* d = arg->def;

    e->fieldPosition = arg->pos;
    e->height = d->height;
    e->kind = 3;
    work->update = MapGmk06CheckTalk;
    work->palette = LoadObjPalette(d->palette, 32);
    work->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    AnimInit(&work->anim, d->anims, d->gfxTable);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    ColliderInit(&work->collider, 4, 24, 24);
    ColliderSetPosition(&work->collider, work->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    TaskPoolInit(&work->tasks, 1);
    FldObjRegister(e);
}

s32 Task_MapGmk06_1(MapGmk06Work* work) {
    TaskPoolUpdate(&work->tasks);

    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    work->gfx = AnimUpdate(&work->anim);

    if (work->update != NULL) {
        work->update(work);

        if (work->update != NULL) {
            return 1;
        }
    }

    return 0;
}

void Task_MapGmk06_2(MapGmk06Work* work) {
    FldPos* p = &work->obj.fieldPosition;
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    TaskPoolDraw(&work->tasks);
    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = p->y >> 8;
    y = k + (p->z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk06_3(MapGmk06Work* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
    TaskPoolDestroy(&work->tasks);
    FldObjUnregister(&work->obj);
}

void MapPrizeBounce(MapPrizeWork* work) {
    work->vz += 0x38;
    work->z += work->vz;
    work->x += gSineTable[work->angle] * work->speed >> 8;
    work->y += -gSineTable[work->angle + 64] * work->speed >> 8;

    if (IsFldPosBlocked((FldPos*)work) != 0) {
        work->angle = work->angle + (100 + GetRandom() % 57);
    } else {
        work->ground = GetFldPosGround((FldPos*)work);
    }

    if (work->z > work->ground) {
        work->z = work->ground;
        work->vz = -(GetRandom() % 0x181 + 0x180);
    }

    if (work->collider.colliding) {
        u16 t;

        switch (work->kind) {
        case 2:
        case 3:
            m4aSongNumStart(SONG_SYS_POWER_GET);
            gGameState.progression.mooglePoints += work->amount;

            if (gGameState.progression.mooglePoints > 99999) {
                gGameState.progression.mooglePoints = 99999;
            }

            break;
        case 0:
        case 1:
        default:
            m4aSongNumStart(SONG_SYS_POWER_GET);
            gGameState.hp += work->amount;
            t = gGameState.progression.maxHp;

            if (gGameState.hp > (s16)t) {
                gGameState.hp = t;
            }

            break;
        }

        work->update = MapPrizeCollect;
        work->timer = 0;
        work->angle = GetAngle(gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y, work->x, work->y);
        work->collected = 1;
        work->visible = 1;
        work->angleStep = GetRandom() % 6 + 5;
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetPosition(&work->collider, work->x, work->y, work->z);

        if (work->timer == 20) {
            ColliderSetDisabled(&work->collider, 0);
        }

        if (work->timer > 420) {
                work->visible = !work->visible ? 1 : 0;
        }

        if (work->timer++ > 480) {
            work->update = NULL;
        }
    }
}

void MapPrizeCollect(MapPrizeWork* work) {
    s32 x;
    s32 y;
    s32 z;
    s32 s;
    FieldState* g = gFieldState;

    s = gSineTable[work->angle] * 32;
    x = g->actor.fieldPosition.x + (s * work->scale >> 8);
    s = -gSineTable[work->angle + 64] * 22;
    y = g->actor.fieldPosition.y + (s * work->scale >> 8);
    z = g->actor.fieldPosition.z - (work->timer / 2 << 8);
    work->angle += work->angleStep;
    work->x += (x - work->x) >> 2;
    work->y += (y - work->y) >> 2;
    work->z += (z - work->z) >> 2;
    work->ground = FieldFloorAt(work->x, work->y, work->z);
    work->scale -= 2;

    if (work->timer > 60) {
        work->update = NULL;
    } else {
        work->timer++;
    }
}

void Task_MapPrize_0(MapPrizeWork* work, MapPrizeArgs* arg) {
    work->x = arg->x;
    work->y = arg->y;
    work->z = arg->z;
    work->ground = 0;
    FldPosInitGround((FldPos*)work);
    work->vz = -(GetRandom() % 0x301 + 0x200);
    work->speed = GetRandom() % 155 + 153;
    work->angle = GetRandom();
    work->tiles = LoadObjTiles(gUnk_098A5CF4, 0x160);
    work->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    work->kind = arg->id;

    switch (work->kind) {
    case 3:
        work->gfx = gUnk_098A5CAE;
        work->amount = 10;
        break;
    case 2:
        work->gfx = gUnk_098A5CA4;
        work->amount = 4;
        break;
    case 1:
        work->gfx = gUnk_098A5C9A;
        work->amount = gGameState.progression.maxHp / 20;
        break;
    case 0:
    default:
        work->gfx = gUnk_098A5C90;
        work->amount = gGameState.progression.maxHp * 3 / 100;
        break;
    }

    work->gfx2 = gUnk_098A5CB8;
    work->collected = 0;
    work->visible = 1;
    work->timer = 0;
    work->update = MapPrizeBounce;
    work->scale = 0x100;
    ColliderInit(&work->collider, 5, 16, 50);
    ColliderSetPosition(&work->collider, work->x, work->y, work->z);
    ColliderSetDisabled(&work->collider, 1);
}

s32 Task_MapPrize_1(MapPrizeWork* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (work->update == NULL) {
        return 0;
    }

    work->update(work);

    if (work->update == NULL) {
        return 0;
    }

    return 1;
}

void Task_MapPrize_2(MapPrizeWork* work) {
    s16 x;
    s16 y;
    ObjAffine* aff;

    if (work->visible) {
        x = (work->x >> 8) - (gFieldState->x >> 8);
        y = (work->y >> 8) + (work->z >> 8) - (gFieldState->y >> 8);

        if (work->scale != 0x100) {
            aff = AllocObjAffine(0, work->scale, work->scale, 0);
        } else {
            aff = NULL;
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, aff, SPRITE_PRIORITY(2), -0x1004 - (work->y >> 8) * 4);

        if (!work->collected) {
            DrawSprite(x, (work->y >> 8) + (work->ground >> 8) - (gFieldState->y >> 8), work->gfx2, work->tiles, work->palette, aff, SPRITE_PRIORITY(2), 0xFFFF);
        }
    }
}

void Task_MapPrize_3(MapPrizeWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

void MapPrzCardUpdateScale(MapPrzCardWork* work) {
    work->scaleX = -COS(work->phaseX + 0x80) * work->scale >> 8;
    work->scaleY = -COS(work->phaseY + 0x80) * work->scale >> 8;

    if ((u16)(work->scaleX + 2) <= 4) {
        work->scaleX = 2;
    }

    if ((u16)(work->scaleY + 2) <= 4) {
        work->scaleY = 2;
    }
}

void MapPrzCardAimAtCenter(MapPrzCardWork* work) {
    s32 dx;
    s32 dy;

    dx = 0x7800;
    dy = 0x5000;
    dx -= work->posX;
    dy -= work->posY;
    work->distance = NormalizeVector2D8(&dx, &dy);
    work->dirX = -dx;
    work->dirY = -dy;
    work->speed = 0x300;
    work->vz = 2;
}

void MapPrzCardBounce(MapPrzCardWork* work) {
    FldPos v = *(FldPos*)work;
    s32 nx;
    s32 ny;

    work->vz += 0x38;
    work->posZ += work->vz;
    work->posX += gSineTable[work->angle] * work->speed >> 8;
    work->posY += -gSineTable[work->angle + 64] * work->speed >> 8;

    if (IsFldPosBlocked((FldPos*)work) != 0) {
        work->angle = work->angle + (112 + GetRandom() % 33);
        work->posX = v.x;
        work->posY = v.y;
    } else {
        work->ground = GetFldPosGround((FldPos*)work);
    }

    if (work->posZ - 0x800 > work->ground) {
        work->posZ = work->ground - 0x800;
        work->vz = -(work->vz * 217 >> 8);

        if (work->vz > -0x200) {
            work->vz = -0x200;
        }
    }

    if (work->collider.colliding) {
        work->collected = 1;
        m4aSongNumStart(SONG_SYS_ITEMGET);
        ObtainCard(work->cardId);

        if (!work->worldPrize) {
            MapFloorRoom* e = GetMapFloorRoom(gMapFloorState.room);

            if (e->przCardsLeft != 0) {
                e->przCardsLeft--;
            }
        }

        nx = (work->posX >> 8) - (gFieldState->x >> 8);
        ny = (work->posY >> 8) + (work->posZ >> 8) - (gFieldState->y >> 8);
        work->posX = (s16)nx << 8;
        work->posY = (s16)ny << 8;
        ColliderSetDisabled(&work->collider, 1);
        work->priority = 50;
        MapPrzCardAimAtCenter(work);
        work->spriteFlags = 0;
        work->update = MapPrzCardFlyToCenter;
    } else {
        work->x = (work->posX >> 8) - (gFieldState->x >> 8);
        work->y = (work->posY >> 8) + (work->posZ >> 8) - (gFieldState->y >> 8);
        work->priority = -0x1004 - (work->posY >> 8) * 4;
        MapPrzCardUpdateScale(work);
        work->phaseX += 2;
        ColliderSetPosition(&work->collider, work->posX, work->posY, work->posZ);

        if (work->timer == 20) {
            ColliderSetDisabled(&work->collider, 0);
        }

        if (work->timer <= 59) {
            work->timer++;
        }
    }
}

void MapPrzCardFlyToCenter(MapPrzCardWork* work) {
    s32 dx;
    s32 dy;
    s32 x;
    s32 y;

    if (work->speed < 0) {
        dx = 0x7800 - work->posX;
        dy = 0x5000 - work->posY;
        NormalizeVector2D8(&dx, &dy);
        work->dirX = -dx;
        work->dirY = -dy;

        if (work->distance <= 0x7FF) {
            work->rotation = 0;
            work->timer = 0;
            work->update = MapPrzCardShowName;
            TaskCreate(&work->tasks, &gTaskDescMapMsg, LANGSEL(gCardDefs[work->cardId].name));
        }
    }

    work->posX += work->dirX * work->speed >> 8;
    work->posY += work->dirY * work->speed >> 8;
    work->rotation += 32;
    work->phaseY += (64 - work->phaseY) >> 4;
    work->phaseX = 0;
    work->distance = VectorLength2D(0x7800 - work->posX, 0x5000 - work->posY);
    work->speed -= work->vz;
    work->vz += 2;
    work->scale += 3;

    if (work->scale > 0x100) {
        work->scale = 0x100;
    }

    x = work->posX >> 8;
    work->x = x;
    y = work->posY >> 8;
    work->y = y;
    MapPrzCardUpdateScale(work);
}

void MapPrzCardShowName(MapPrzCardWork* work) {
    s32 x;
    s32 y;

    work->posX = 0x7800;
    work->posY = 0x5800;
    work->rotation = 0;
    work->phaseY = 0;
    work->scale += 2;

    if (work->scale > 0x100) {
        work->scale = 0x100;
    }

    x = work->posX >> 8;
    work->x = x;
    y = work->posY >> 8;
    work->y = y;
    MapPrzCardUpdateScale(work);
    work->timer++;

    if (work->timer == 30) {
        work->timer = 0;
        work->update = MapPrzCardShrink;
    }

    TaskPoolUpdate(&work->tasks);
}

void MapPrzCardShrink(MapPrzCardWork* work) {
    s32 x;
    s32 y;

    work->rotation += 32;
    x = (gFieldState->actor.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    y = (gFieldState->actor.fieldPosition.y >> 8) + (gFieldState->actor.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    work->x += ((s16)x - work->x) >> 3;
    work->y += ((s16)y - work->y) >> 3;
    work->scaleX -= 10;
    work->scaleY -= 10;

    if (work->scaleX <= 10) {
        work->update = NULL;
    }
}

void Task_MapPrzCard_0(MapPrzCardWork* work, MapPrizeArgs* p) {
    const CardDef* d;
    const CardBack* q;

    gMapRoomState->flags |= ROOM_FLAG_PRIZE_CARD_ACTIVE;
    work->cardId = p->id;
    d = &gCardDefs[work->cardId];
    work->tiles = LoadObjTiles(d->tiles, 0x300);
    work->palette = LoadObjPalette(d->palette, 32);
    work->stat = *(CardStat*)&d->kind;
    q = &gCardBacks[work->stat.category];
    work->palette2 = LoadObjPalette(gCard00Palette, 32);
    work->tiles2 = LoadObjTiles(q->tiles, 0x280);
    work->tiles3 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    work->palette3 = LoadObjPalette(gUnk_08F69BE4, 32);
    work->tiles4 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    work->posX = p->x;
    work->posY = p->y;
    work->posZ = p->z;
    work->ground = 0;
    FldPosInitGround((FldPos*)work);
    work->vz = -(GetRandom() % 129 + 0x300);
    work->speed = GetRandom() % 129 + 128;
    work->angle = GetRandom();
    work->scaleX = 128;
    work->scaleY = 128;
    work->scale = 128;
    work->rotation = 24;
    work->phaseY = 0;
    work->phaseX = 0;
    work->worldPrize = p->worldPrize;
    ColliderInit(&work->collider, 5, 30, 10);
    ColliderSetPosition(&work->collider, work->posX, work->posY, work->posZ);

    if (work->worldPrize) {
        ColliderSetDisabled(&work->collider, 0);
    } else {
        ColliderSetDisabled(&work->collider, 1);
    }

    work->spriteFlags = SPRITE_PRIORITY(2);
    work->timer = 0;
    work->update = MapPrzCardBounce;
    work->collected = 0;
    TaskPoolInit(&work->tasks, 1);
}

s32 Task_MapPrzCard_1(MapPrzCardWork* work) {
    if ((u8)IsMapInterrupted()) {
        return 0;
    }

    if (work->update == NULL) {
        return 0;
    }

    work->update(work);

    if (work->update == NULL) {
        return 0;
    }

    return 1;
}

void Task_MapPrzCard_2(MapPrzCardWork* work) {
    const CardDef* d;
    const CardBack* q;
    void* t;
    ObjAffine* affine;
    s16 x;
    s16 y;
    s16 s;

    if (work->scaleX == 0x100 && work->scaleY == 0x100 && work->rotation == 0) {
        affine = NULL;
    } else {
        affine = AllocObjAffine(work->rotation, work->scaleX, work->scaleY, 1);
    }

    d = &gCardDefs[work->cardId];
    DrawSprite(work->x, work->y - 8, d->gfx, work->tiles, work->palette,
        affine, work->spriteFlags, work->priority + 1);
    q = &gCardBacks[work->stat.category];
    DrawSprite(work->x, work->y - 8, q->gfx, work->tiles2,
        work->palette2, affine, work->spriteFlags, work->priority);

    if (work->stat.category != 3) {
        t = gUnk_09EE981C[work->stat.value];
        DrawSprite(work->x, work->y - 8, t, work->tiles3,
            work->palette2, affine, work->spriteFlags, work->priority - 1);
    }

    if (!work->collected) {
        x = (work->posX >> 8) - (gFieldState->x >> 8);
        y = (work->posY >> 8) + (work->ground >> 8) - (gFieldState->y >> 8);
        s = 204 - ((work->ground - work->posZ) >> 7);

        if (s <= 2) {
            s = 2;
        }

        DrawSprite(x, y, gUnk_09EE1380[0], work->tiles4, work->palette3,
            AllocObjAffine(0, s, s, 0), SPRITE_PRIORITY(2), work->priority + 2);
    }

    TaskPoolDraw(&work->tasks);
}

void Task_MapPrzCard_3(MapPrzCardWork* work) {
    FadeSetPaletteExcluded(work->palette2->index + 0x10, 0);
    FadeSetPaletteExcluded(work->palette->index + 0x10, 0);
    ColliderUnregister(&work->collider);
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles3);
    ReleaseObjTiles(work->tiles4);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
    ReleaseObjPalette(work->palette3);
    TaskPoolDestroy(&work->tasks);
    gMapRoomState->flags &= ~ROOM_FLAG_PRIZE_CARD_ACTIVE;
}

void MapPrzStockShowMessage(MapPrzStockWork* work) {
    CreateCardMessageTask(&work->tasks, 0, work->stock[1]);
    work->update = MapPrzStockWaitMessage;
}

void MapPrzStockWaitMessage(MapPrzStockWork* work) {
    if (!IsMessageWindowOpen()) {
        work->update = NULL;
    }
}

void Task_MapPrzStock_0(MapPrzStockWork* work, u16* a) {
    work->stock = a;
    gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
    gFieldState->flags |= FIELD_FLAG_FREEZE_ENEMIES;
    work->update = MapPrzStockShowMessage;
    TaskPoolInit(&work->tasks, 1);
}

s32 Task_MapPrzStock_1(MapPrzStockWork* work) {
    TaskPoolUpdate(&work->tasks);

    if (work->update != NULL) {
        work->update(work);

        if (work->update != NULL) {
            return 1;
        }
    }

    return 0;
}

void Task_MapPrzStock_2(MapPrzStockWork* work) {
    TaskPoolDraw(&work->tasks);
}

void Task_MapPrzStock_3(MapPrzStockWork* work) {
    TaskPoolDestroy(&work->tasks);
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_ENEMIES;
}

void MapMsgInit(MapMsgWork* work, void* text) {
    LoadBgTiles(0, &gUnk_099597E4[0x140], 0x140);
    LoadBgMap(0, &gUnk_09985F44[0x400], 0x800);
    SetBgScroll(0, 0, (u16)-46);
    LoadPalette(gCard00Palette, &gUnk_050001C0[0x20], 32);
    InitTextSlots(work->textSlots, 48);
    work->textSlotCount = LoadTextSlots(text, work->textSlots);
    work->palette = LoadTextPalette(1);
    FadeSetPaletteExcluded(work->palette->index + 16, 1);
    work->textX = (240 - GetTextSlotsWidth(work->textSlots, work->textSlotCount)) / 2;
    work->timer = 0;
}

s32 Task_MapMsg_1(MapMsgWork* work) {
    return 1;
}

void MapMsgDraw(MapMsgWork* work) {
    DrawTextSlots(work->textX, 120, work->textSlots, work->palette, 50, work->textSlotCount);
}

void MapMsgDestroy(MapMsgWork* work) {
    if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) == 0) {
        DisableBg(0);
    }

    FadeSetPaletteExcluded(work->palette->index + 0x10, 0);
    ReleaseObjPalette(work->palette);
    FreeTextSlots(work->textSlots, 0x30);
}

s32 Task_MapMsg2_1(MapMsgWork* work) {
    work->timer++;

    if (work->timer == 120) {
        return 0;
    }

    return 1;
}

void Task_MapSpark_0(MapSparkWork* work, FldObj* obj) {
    AnimState* a;

    work->obj = obj;
    work->tiles = AllocObjTiles(0x200, gUnk_098A4B68);
    work->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    a = &work->anim;
    AnimInit(a, gUnk_09EF8CC0, gUnk_09EF8CA0);

    if (gGameState.flags & GAME_FLAG_RIKU) {
        AnimStart(a, 1, ANIM_FLAG_LOOP);
    } else {
        AnimStart(a, 0, ANIM_FLAG_LOOP);
    }
}

s32 Task_MapSpark_1(MapSparkWork* work) {
    AnimUpdate(&work->anim);

    if (AnimIsFinished(&work->anim)) {
        return 0;
    }

    return 1;
}

void Task_MapSpark_2(MapSparkWork* work) {
    FldObj* p = work->obj;
    s32 h;
    u16 x;
    u16 y;

    if (p->height <= 32) {
        h = p->height << 8;
    } else {
        h = 0x2000;
    }

    x = (p->fieldPosition.x >> 8) - (gFieldState->x >> 8);
    y = (p->fieldPosition.y >> 8) + ((p->fieldPosition.z - h) >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL, SPRITE_PRIORITY(1), 0x50);
}

void Task_MapSpark_3(MapSparkWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void Task_MapTalk_0(MapTalkWork* work, FldObj* obj) {
    work->obj = obj;
    work->tiles = AllocObjTiles(0x200, &gUnk_098A4B68[0x1028]);
    work->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    AnimInit(&work->anim, gUnk_09EF8CD0, gUnk_09EF8CC8);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->playerOnRight = 0;
}

s32 Task_MapTalk_1(MapTalkWork* work) {
    FldObj* p = work->obj;
    AnimState* anim = &work->anim;

    AnimUpdate(anim);

    if (gFieldState->actor.fieldPosition.x < p->fieldPosition.x) {
        work->playerOnRight = 0;
        AnimStart(anim, 0, ANIM_FLAG_LOOP);
    } else {
        work->playerOnRight = 1;
        AnimStart(anim, 1, ANIM_FLAG_LOOP);
    }

    return 1;
}

void Task_MapTalk_2(MapTalkWork* work) {
    FldObj* p = work->obj;
    u16 x;
    u16 y;

    if (work->playerOnRight) {
        x = (p->fieldPosition.x >> 8) - (gFieldState->x >> 8) - 16;
    } else {
        x = (p->fieldPosition.x >> 8) - (gFieldState->x >> 8) + 16;
    }

    y = (p->fieldPosition.y >> 8) + ((p->fieldPosition.z - (p->height << 8)) >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL, SPRITE_PRIORITY(1), 0x50);
}

void Task_MapTalk_3(MapTalkWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

const MapGmkDef gMapGmk01Def = {
    gUnk_099912C4, gUnk_09858320, 0x200, gUnk_09EF8414, gUnk_09EF841C,
    1, 13, 0, 0, 0, 16, 16, SONG_SYS_TRESURE, &gTaskDescMapGmk01,
};

TaskDesc gTaskDescMapGmk01 = {
    "Task_MapGmk01",
    (TaskInitFunc)Task_MapGmk01_0,
    (TaskUpdateFunc)Task_MapGmk01_1,
    (TaskDrawFunc)Task_MapGmk01_2,
    (TaskDestroyFunc)Task_MapGmk01_3,
    sizeof(MapGmk01Work),
};

const MapGmkDef gMapGmkBarrelDef = {
    gUnk_099912E4, gUnk_09858B3C, 0x400, gUnk_09EF8424, gUnk_09EF8460,
    1, 0, 0, 0, 0, 12, 24, SONG_SYS_OBJ_BREAK, &gTaskDescMapGmkBarrel,
};

TaskDesc gTaskDescMapGmkBarrel = {
    "Task_MapGmk_Barrel",
    (TaskInitFunc)Task_MapGmk_Barrel_0,
    (TaskUpdateFunc)Task_MapGmk_Barrel_1,
    (TaskDrawFunc)Task_MapGmk_Barrel_2,
    (TaskDestroyFunc)Task_MapGmk_Barrel_3,
    sizeof(MapGmkBarrelWork),
};

const MapGmkDef gMapGmk04Def = {
    gUnk_09991324, gUnk_0985ADAA, 0x400, gUnk_09EF8494, gUnk_09EF84A4,
    1, 13, 0, 0, 0, 24, 62, SONG_SYS_KETTEI, &gTaskDescMapGmk04,
};

TaskDesc gTaskDescMapGmk04 = {
    "Task_MapGmk04",
    (TaskInitFunc)Task_MapGmk04_0,
    (TaskUpdateFunc)Task_MapGmk04_1,
    (TaskDrawFunc)Task_MapGmk04_2,
    (TaskDestroyFunc)Task_MapGmk04_3,
    sizeof(MapGmk04Work),
};

const MapGmkDef gMapGmk05Def = {
    gMoguPalette, gMoguFl00Tiles, 0x100, gMoguFl00Frames, gMoguFl00Anims,
    1, 13, 0, 0, 0, 16, 24, SONG_SYS_MOUGURI, &gTaskDescMapGmk05,
};

TaskDesc gTaskDescMapGmk05 = {
    "Task_MapGmk05",
    (TaskInitFunc)Task_MapGmk05_0,
    (TaskUpdateFunc)Task_MapGmk05_1,
    (TaskDrawFunc)Task_MapGmk05_2,
    (TaskDestroyFunc)Task_MapGmk05_3,
    sizeof(MapGmk05Work),
};

const MapGmkDef gMapGmk06Def = {
    gMapGmk06Palette, gUnk_0985BDEA, 0x400, gUnk_09EF84A8, gUnk_09EF84B8,
    1, 13, 0, 0, 0, 24, 54, SONG_SYS_KETTEI, &gTaskDescMapGmk06,
};

TaskDesc gTaskDescMapGmk06 = {
    "Task_MapGmk06",
    (TaskInitFunc)Task_MapGmk06_0,
    (TaskUpdateFunc)Task_MapGmk06_1,
    (TaskDrawFunc)Task_MapGmk06_2,
    (TaskDestroyFunc)Task_MapGmk06_3,
    sizeof(MapGmk06Work),
};

TaskDesc gTaskDescMapPrize = {
    "Task_MapPrize",
    (TaskInitFunc)Task_MapPrize_0,
    (TaskUpdateFunc)Task_MapPrize_1,
    (TaskDrawFunc)Task_MapPrize_2,
    (TaskDestroyFunc)Task_MapPrize_3,
    sizeof(MapPrizeWork),
};

TaskDesc gTaskDescMapPrzCard = {
    "Task_MapPrzCard",
    (TaskInitFunc)Task_MapPrzCard_0,
    (TaskUpdateFunc)Task_MapPrzCard_1,
    (TaskDrawFunc)Task_MapPrzCard_2,
    (TaskDestroyFunc)Task_MapPrzCard_3,
    sizeof(MapPrzCardWork),
};

TaskDesc gTaskDescMapPrzStock = {
    "Task_MapPrzStock",
    (TaskInitFunc)Task_MapPrzStock_0,
    (TaskUpdateFunc)Task_MapPrzStock_1,
    (TaskDrawFunc)Task_MapPrzStock_2,
    (TaskDestroyFunc)Task_MapPrzStock_3,
    sizeof(MapPrzStockWork),
};

TaskDesc gTaskDescMapMsg = {
    "Task_MapMsg",
    (TaskInitFunc)MapMsgInit,
    (TaskUpdateFunc)Task_MapMsg_1,
    (TaskDrawFunc)MapMsgDraw,
    (TaskDestroyFunc)MapMsgDestroy,
    sizeof(MapMsgWork),
};

TaskDesc gTaskDescMapMsg2 = {
    "Task_MapMsg2",
    (TaskInitFunc)MapMsgInit,
    (TaskUpdateFunc)Task_MapMsg2_1,
    (TaskDrawFunc)MapMsgDraw,
    (TaskDestroyFunc)MapMsgDestroy,
    sizeof(MapMsgWork),
};

TaskDesc gTaskDescMapSpark = {
    "Task_MapSpark",
    (TaskInitFunc)Task_MapSpark_0,
    (TaskUpdateFunc)Task_MapSpark_1,
    (TaskDrawFunc)Task_MapSpark_2,
    (TaskDestroyFunc)Task_MapSpark_3,
    sizeof(MapSparkWork),
};

TaskDesc gTaskDescMapTalk = {
    "Task_MapTalk",
    (TaskInitFunc)Task_MapTalk_0,
    (TaskUpdateFunc)Task_MapTalk_1,
    (TaskDrawFunc)Task_MapTalk_2,
    (TaskDestroyFunc)Task_MapTalk_3,
    sizeof(MapTalkWork),
};
