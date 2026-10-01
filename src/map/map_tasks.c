#include "monsgage.h"
#include "map_resource_assets.h"
#include "map_tasks.h"
#include "map_enemy_assets.h"
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
#include "mode_test_api.h"
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
#include "mode_chkobj_assets.h"
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

static const AnimDef sMapEnm00AnimDefs[10] = {
    { gEmy00L06Frames, gEmy00L06Anims, gEmy00L06Tiles, 0, { 0, 0, 0 } },
    { gEmy00L06Frames, gEmy00L06Anims, gEmy00L06Tiles, 0, { 0, 0, 0 } },
    { gUnk_09EDF860, gUnk_09EDF880, gUnk_08958AC8, 0, { 0, 0, 0 } },
    { gEmy00L00Frames, gEmy00L00Anims, gEmy00L00Tiles, 0, { 0, 0, 0 } },
    { gUnk_09EDF8A8, gUnk_09EDF8C8, gUnk_0895B2C0, 0, { 0, 0, 0 } },
    { gEmy00L02Frames, gEmy00L02Anims, gEmy00L02Tiles, 0, { 0, 0, 0 } },
    { gUnk_09EDF97C, gUnk_09EDF9A4, gUnk_0896213C, 0, { 0, 0, 0 } },
    { gEmy00L07Frames, gEmy00L07Anims, gEmy00L07Tiles, 0, { 0, 0, 0 } },
    { gEmy00L09Frames, gEmy00L09Anims, gEmy00L09Tiles, 0, { 0, 0, 0 } },
    { gEmy00L09Frames, gEmy00L09Anims, gEmy00L09Tiles, 0, { 0, 0, 0 } },
};

const AnimDef gUnk_0984BC3C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 1, { 0, 0, 0 },
};

const AnimDef gUnk_0984BC4C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 1, { 0, 0, 0 },
};

const AnimDef gUnk_0984BC5C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 0, { 0, 0, 0 },
};

const AnimDef gUnk_0984BC6C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 0, { 0, 0, 0 },
};

const AnimDef gUnk_0984BC7C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 2, { 0, 0, 0 },
};

const AnimDef gUnk_0984BC8C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 2, { 0, 0, 0 },
};

const MapEnmDef gMapEnm00Def = {
    sMapEnm00AnimDefs, gEmy00Palette,
    32, 8, 16, 0,
    &gTaskDescMapEnm00, MAP_ENM_DEF_FLAG_NO_SHADOW, 0,
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
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 0, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 0, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 2, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 2, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 3, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 3, { 0, 0, 0 } },
};

const MapEnmDef gMapEnm01Def = {
    sMapEnm01AnimDefs, gEmy01Palette,
    17, 16, 16, 0,
    &gTaskDescMapEnm01, MAP_ENM_DEF_FLAG_AIRBORNE, 0,
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
    { gEmy3800Frames, gEmy3800Anims, gEmy3800Tiles, 0, { 0, 0, 0 } },
    { gEmy3800Frames, gEmy3800Anims, gEmy3800Tiles, 0, { 0, 0, 0 } },
};

const AnimDef gUnk_0984BD6C = {
    gEmy3801Frames, gEmy3801Anims, gEmy3801Tiles, 0, { 0, 0, 0 },
};

const AnimDef gUnk_0984BD7C = {
    gEmy3801Frames, gEmy3801Anims, gEmy3801Tiles, 0, { 0, 0, 0 },
};

const MapEnmDef gMapEnm02Def = {
    sMapEnm02AnimDefs, gEmy38Palette,
    106, 48, 36, 0,
    &gTaskDescMapEnm02, MAP_ENM_DEF_FLAG_GUARD, 0,
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
    { gEmy2900Frames, gEmy2900Anims, gEmy2900Tiles, 0, { 0, 0, 0 } },
    { gEmy2900Frames, gEmy2900Anims, gEmy2900Tiles, 0, { 0, 0, 0 } },
    { gEmy2900Frames, gEmy2900Anims, gEmy2900Tiles, 0, { 0, 0, 0 } },
    { gEmy2900Frames, gEmy2900Anims, gEmy2900Tiles, 0, { 0, 0, 0 } },
};

const AnimDef gUnk_0984BDF4 = {
    gEmy2902Frames, gEmy2902Anims, gEmy2902Tiles, 0, { 0, 0, 0 },
};

const AnimDef gUnk_0984BE04 = {
    gEmy2902Frames, gEmy2902Anims, gEmy2902Tiles, 0, { 0, 0, 0 },
};

const MapEnmDef gMapEnm03Def = {
    sMapEnm03AnimDefs, gEmy29Palette,
    73, 56, 36, 0,
    &gTaskDescMapEnm03, MAP_ENM_DEF_FLAG_AIRBORNE | MAP_ENM_DEF_FLAG_GUARD, 0,
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
    { gUnk_09EF8D24, gUnk_09EF8D44, gUnk_098A659A, 0, { 0, 0, 0 } },
    { gEmy0600Frames, gEmy0600Anims, gEmy0600Tiles, 0, { 0, 0, 0 } },
    { gUnk_09EF8D24, gUnk_09EF8D44, gUnk_098A659A, 0, { 0, 0, 0 } },
    { gEmy0600Frames, gEmy0600Anims, gEmy0600Tiles, 0, { 0, 0, 0 } },
    { gEmy0603Frames, gEmy0603Anims, gEmy0603Tiles, 0, { 0, 0, 0 } },
    { gEmy0603Frames, gEmy0603Anims, gEmy0603Tiles, 0, { 0, 0, 0 } },
};

const MapEnmDef gMapEnm04Def = {
    sMapEnm04AnimDefs, gEmy06Palette,
    34, 16, 12, 0,
    &gTaskDescMapEnm04, MAP_ENM_DEF_FLAG_AIRBORNE, 0,
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
    { gEmy07Fl01Frames, gEmy07Fl01Anims, gEmy07Fl01Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl01Frames, gEmy07Fl01Anims, gEmy07Fl01Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl02Frames, gEmy07Fl02Anims, gEmy07Fl02Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl02Frames, gEmy07Fl02Anims, gEmy07Fl02Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl03Frames, gEmy07Fl03Anims, gEmy07Fl03Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl03Frames, gEmy07Fl03Anims, gEmy07Fl03Tiles, 0, { 0, 0, 0 } },
};

const MapEnmDef gMapEnm05Def = {
    sMapEnm05AnimDefs, gEmy07Palette,
    26, 16, 12, 0,
    &gTaskDescMapEnm05, MAP_ENM_DEF_FLAG_SPAWN_ANYWHERE, 0,
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
    { gEmy07Fl01Frames, gEmy07Fl01Anims, gEmy07Fl01Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl01Frames, gEmy07Fl01Anims, gEmy07Fl01Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl02Frames, gEmy07Fl02Anims, gEmy07Fl02Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl02Frames, gEmy07Fl02Anims, gEmy07Fl02Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl03Frames, gEmy07Fl03Anims, gEmy07Fl03Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl03Frames, gEmy07Fl03Anims, gEmy07Fl03Tiles, 0, { 0, 0, 0 } },
};

const MapEnmDef gMapEnm06Def = {
    sMapEnm06AnimDefs, gEmy07bPalette,
    26, 16, 12, 0,
    &gTaskDescMapEnm06, MAP_ENM_DEF_FLAG_SPAWN_ANYWHERE, 0,
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

s32 MapEnm00CheckOffscreen(MapEnmWork* p) {
    FldPos* q = &p->obj.fieldPosition;

    if (p->obj.fieldPosition.x < gFieldState->x - 0x1800 || p->obj.fieldPosition.x > gFieldState->x + 0x10800 ||
        q->y + q->z < gFieldState->y - 0x800 || q->y + q->z > gFieldState->y + 0xC000) {
        p->update = NULL;
        ColliderSetDisabled(&p->collider, 1);
        return 1;
    }

    return 0;
}

void MapEnm00Move(MapEnmWork* p, s32 b, s32 c) {
    FldObj* q = &p->obj;

    if (p->flags & MAP_ENM_FLAG_SLOW) {
        b /= 5;
        c /= 5;
    }

    p->obj.fieldPosition.x += gSineTable[q->angle] * q->speed >> 8;
    q->fieldPosition.y += -gSineTable[q->angle + 64] * q->speed >> 8;
    q->speed += b;

    if (q->speed > c) {
        q->speed = c;
    }
}

void MapEnm00CheckBlocked(MapEnmWork* p, s32 b, s32 c) {
    FldPos* q = &p->obj.fieldPosition;

    if (IsFldPosBlocked(q) != 0 || GetFldPosGround(q) != q->z) {
        p->obj.fieldPosition.x = b;
        q->y = c;
        p->update = MapEnm00Vanish;
        ColliderSetDisabled(&p->collider, 1);
    }
}

s32 MapEnm00SpotPlayer(MapEnmWork* p) {
    FldObj* q = &p->obj;
    u8 ang;

    if (gFieldState->actor.fieldPosition.ground != q->fieldPosition.ground) {
        return 0;
    }

    ang = GetAngle(p->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);

    if (abs(GetAngleDiff(ang, q->angle)) > 0x18) {
        return 0;
    }

    q->angle = ang;
    return 1;
}

void MapEnm00Appear(MapEnmWork* p) {
    MapEnmSetAnim(p, 0, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        if (p->flags & MAP_ENM_FLAG_AGGRESSIVE) {
            p->update = MapEnm00Pursue;
        } else {
            p->update = MapEnm00Idle;
        }

        p->timer = 0;
        ColliderSetDisabled(&p->collider, 0);
    } else {
        MapEnmUpdateAnim(p);

        if (p->colliderDelay > 0) {
            p->colliderDelay--;

            if (p->colliderDelay <= 0) {
                ColliderSetDisabled(&p->collider, 0);
            }
        }
    }
}

void MapEnm00Idle(MapEnmWork* p) {
    FldObj* q = &p->obj;
    s32 x;
    s32 y;

    MapEnmSetAnim(p, 1, 1);
    MapEnmUpdateAnim(p);
    TaskPoolUpdate(&p->tasks);
    x = p->obj.fieldPosition.x;
    y = q->fieldPosition.y;

    if ((u8)MapEnm00SpotPlayer(p) != 0) {
        p->timer = 0;
        p->update = MapEnm00Chase;
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

        p->timer = 0;
        p->update = MapEnm00Wander;
    }

    if ((u8)MapEnmCheckAttacked(p) != 0) {
        p->update = MapEnm00Hit;
    } else {
        MapEnmCheckContact(p);

        if ((u8)MapEnm00CheckOffscreen(p) == 0) {
            MapEnm00CheckBlocked(p, x, y);
        }
    }
}

void MapEnm00Wander(MapEnmWork* p) {
    FldObj* q = &p->obj;
    s32 x;
    s32 y;

    MapEnmSetAnim(p, 2, 1);
    MapEnmUpdateAnim(p);
    TaskPoolUpdate(&p->tasks);
    x = p->obj.fieldPosition.x;
    y = q->fieldPosition.y;

    if ((u8)MapEnm00SpotPlayer(p) != 0) {
        p->timer = 0;
        p->update = MapEnm00Chase;
    } else if (GetRandom() % 80 == 0) {
        q->speed = 0;
        p->update = MapEnm00Idle;
    } else {
        MapEnm00Move(p, 12, 0x80);
    }

    if ((u8)MapEnmCheckAttacked(p) != 0) {
        p->update = MapEnm00Hit;
    } else {
        MapEnmCheckContact(p);

        if ((u8)MapEnm00CheckOffscreen(p) == 0) {
            MapEnm00CheckBlocked(p, x, y);
        }
    }
}

void MapEnm00Chase(MapEnmWork* p) {
    FldObj* q = &p->obj;
    s32 x;
    s32 y;

    MapEnmSetAnim(p, 2, 1);
    MapEnmUpdateAnim(p);
    TaskPoolUpdate(&p->tasks);
    x = q->fieldPosition.x;
    y = q->fieldPosition.y;

    if (p->timer % 8 == 0) {
        if ((u8)MapEnm00SpotPlayer(p) == 0) {
            q->speed = 0;
            p->update = MapEnm00Idle;
        }
    }

    MapEnm00Move(p, 12, 0x180);
    p->timer++;

    if ((u8)MapEnmCheckAttacked(p) != 0) {
        p->update = MapEnm00Hit;
    } else {
        MapEnmCheckContact(p);

        if ((u8)MapEnm00CheckOffscreen(p) == 0) {
            MapEnm00CheckBlocked(p, x, y);
        }
    }
}

void MapEnm00Pursue(MapEnmWork* p) {
    FldObj* q = &p->obj;
    s32 x;
    s32 y;

    MapEnmSetAnim(p, 2, 1);
    MapEnmUpdateAnim(p);
    TaskPoolUpdate(&p->tasks);
    x = q->fieldPosition.x;
    y = q->fieldPosition.y;

    if (p->timer % 8 == 0) {
        q->angle = GetAngle(x, y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    MapEnm00Move(p, 25, 0x200);

    if ((u8)MapEnmCheckAttacked(p) != 0) {
        p->update = MapEnm00Hit;
    } else {
        MapEnmCheckContact(p);
        MapEnm00CheckBlocked(p, x, y);
        p->timer++;
    }
}

void MapEnm00Vanish(MapEnmWork* p) {
    p->flags |= MAP_ENM_FLAG_REMOVED;
    MapEnmSetAnim(p, 3, 0);
    MapEnmUpdateAnim(p);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->update = NULL;
    }
}

void MapEnm00Hit(MapEnmWork* p) {
    MapEnmSetAnim(p, 4, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->flags |= MAP_ENM_FLAG_FIRST_STRIKE;
        MapEnmStartBattle(p);
    } else {
        MapEnmUpdateAnim(p);
    }
}

void MapEnm00Stand(MapEnmWork* p) {
    MapEnmSetAnim(p, 1, 0);
    p->gfx = AnimGetGfx(&p->anim);
    TaskPoolUpdate(&p->tasks);

    if ((u8)MapEnmCheckAttacked(p) != 0) {
        p->update = MapEnm00Hit;
    } else {
        MapEnmCheckContact(p);
    }
}

void Task_MapEnm00_0(MapEnmWork* p, MapEnmArgs* q) {
    MapEnmInit(p, q);

    if (p->update == NULL) {
        if (p->flags & MAP_ENM_FLAG_ASLEEP) {
            p->update = MapEnm00Stand;
            MapEnmSetAnim(p, 1, 0);
            p->gfx = AnimGetGfx(&p->anim);
            ColliderSetDisabled(&p->collider, 0);
        } else {
            p->update = MapEnm00Appear;
            MapEnmSetAnim(p, 0, 0);
            p->gfx = AnimGetGfx(&p->anim);
            ColliderSetDisabled(&p->collider, 1);
        }
    } else {
        ColliderSetDisabled(&p->collider, 0);
    }

    p->timer = 0;
}

s32 Task_MapEnm00_1(MapEnmWork* p) {
    FldPos* q = &p->obj.fieldPosition;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapEnmSaveToCache(p);
        return 0;
    }

    if ((gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) && p->update != MapEnm00Hit) {
        return 1;
    }

    if (p->update != NULL) {
        p->update(p);

        if (p->update != NULL) {
            ColliderSetPosition(&p->collider, q->x, q->y, q->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm00_2(MapEnmWork* p) {
    MapEnmDraw(p);
}

void Task_MapEnm00_3(MapEnmWork* p) {
    MapEnmDestroy(p);
}

void MapEnm01CheckOffscreen(MapEnm01Work* p) {
    if (p->enm.obj.fieldPosition.x < gFieldState->x - 0x1800 || p->enm.obj.fieldPosition.x > gFieldState->x + 0x10800) {
        if (p->wasOnScreen != 0) {
            p->enm.update = NULL;
        }
    } else if (p->wasOnScreen == 0) {
        p->wasOnScreen = 1;
    }
}

void MapEnm01UpdateHover(MapEnmWork* p, u8 a) {
    s32* q = &p->obj.fieldPosition.x;
    s32 t = q[2];
    s32 v;

    switch (a) {
    case 1:
        v = p->targetZ + gSineTable[gFrameCounter & 0xFF] * 10;
        break;
    case 0:
    default:
        v = p->targetZ + gSineTable[gFrameCounter * 2 & 0xFF] * 12;
        break;
    }

    if (p->flags & MAP_ENM_FLAG_SLOW) {
        q[2] += (v - q[2]) / 80;
    } else {
        q[2] += (v - q[2]) >> 4;
    }

    if (q[3] < q[2]) {
        q[2] = t;
        p->targetZ = t - 0x1C00;
    }
}

void MapEnm01PickTarget(MapEnmWork* w, u8 a) {
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;

    if (a != 0) {
        w->targetX = gFieldState->actor.fieldPosition.x;
        w->targetY = gFieldState->actor.fieldPosition.y;
        w->targetZ = gFieldState->actor.fieldPosition.z - 0x1000;
    } else {
        w->targetX = gFieldState->actor.fieldPosition.x;
        w->targetY = gFieldState->actor.fieldPosition.y;
        w->targetZ = gFieldState->actor.fieldPosition.z;

        if (GetRandom() % 2) {
            t1 = GetRandom() % 65 * 256;
            t1 += 0x2000;
            w->targetX -= t1;
        } else {
            t2 = GetRandom() % 65 * 256;
            t2 += 0x2000;
            w->targetX += t2;
        }

        t3 = GetRandom() % 121 * 256;
        t3 -= 0x3C00;
        w->targetY += t3;
        t4 = GetRandom() % 49 * 256;
        t4 += 0x1000;
        w->targetZ -= t4;
    }
}

void MapEnm01Idle(MapEnmWork* p) {
    MapEnmWork* w = p;
    FldObj* q = &p->obj;

    MapEnmSetAnim(p, 0, 3);
    MapEnmUpdateAnim(p);
    TaskPoolUpdate(&p->tasks);
    MapEnm01UpdateHover(p, 0);

    if (GetRandom() % 20 == 0) {
        q->angle = GetAngle(p->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if (q->fieldPosition.z < gFieldState->actor.fieldPosition.z - 0x4000) {
        MapEnm01PickTarget(p, 0);
        p->timer = 0;
        q->speed = 0;
        p->update = MapEnm01Fly;
    } else if (GetRandom() % 130 == 0) {
        if (GetRandom() % 2 != 0) {
            MapEnm01PickTarget(p, 0);
        } else {
            MapEnm01PickTarget(p, 1);
        }

        w->timer = 0;
        q->speed = 0;
        w->update = MapEnm01Fly;
    }

    if ((u8)MapEnmCheckAttacked(w) != 0) {
        w->update = MapEnm01Hit;
    } else {
        MapEnmCheckContact(w);
        MapEnm01CheckOffscreen((MapEnm01Work*)p);
    }
}

void MapEnm01Fly(MapEnmWork* p) {
    FldObj* q = &p->obj;
    FldPos t;
    s32 dx;
    s32 dy;
    s32 v;
    s32 r;
    u32 lim;

    MapEnmSetAnim(p, 1, 3);
    MapEnmUpdateAnim(p);
    TaskPoolUpdate(&p->tasks);
    MapEnm01UpdateHover(p, 1);
    t = p->obj.fieldPosition;

    if (GetRandom() % 20 != 0) {
        q->angle = GetAngle(p->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    dx = p->targetX;
    dy = p->targetY;

    if (p->flags & MAP_ENM_FLAG_SLOW) {
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

    if (p->timer > lim) {
        p->update = MapEnm01Idle;
    } else {
        p->timer++;
    }

    r = GetFldPosGround(&q->fieldPosition);

    if (r < q->fieldPosition.z) {
        q->fieldPosition = t;
        p->targetY = q->fieldPosition.y + 0x1000;
    } else if (r == 0x100000) {
        q->fieldPosition = t;
        p->targetY = q->fieldPosition.y - 0x1000;
    } else {
        q->fieldPosition.ground = r;
    }

    if ((u8)MapEnmCheckAttacked(p) != 0) {
        p->update = MapEnm01Hit;
    } else {
        MapEnmCheckContact(p);
    }
}

void MapEnm01Hit(MapEnmWork* p) {
    MapEnmSetAnim(p, 2, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->flags |= MAP_ENM_FLAG_FIRST_STRIKE;
        MapEnmStartBattle(p);
    } else {
        MapEnmUpdateAnim(p);
    }
}

void MapEnm01Stand(MapEnmWork* p) {
    MapEnmSetAnim(p, 0, 0);
    p->gfx = AnimGetGfx(&p->anim);
    TaskPoolUpdate(&p->tasks);

    if ((u8)MapEnmCheckAttacked(p) != 0) {
        p->update = MapEnm01Hit;
    } else {
        MapEnmCheckContact(p);
    }
}

void Task_MapEnm01_0(MapEnmWork* p, MapEnmArgs* q) {
    MapEnm01Work* w = (MapEnm01Work*)p;

    MapEnmInit(p, q);

    if (p->flags & MAP_ENM_FLAG_ASLEEP) {
        p->update = MapEnm01Stand;
        MapEnmSetAnim(p, 0, 0);
        p->gfx = AnimGetGfx(&p->anim);
        ColliderSetDisabled(&p->collider, 0);
    } else {
        p->update = MapEnm01Idle;
        MapEnmSetAnim(p, 0, 1);
        p->gfx = AnimGetGfx(&p->anim);
        ColliderSetDisabled(&p->collider, 0);
    }

    w->enm.timer = 0;
    ((MapEnm01Work*)p)->wasOnScreen = 0;
}

s32 Task_MapEnm01_1(MapEnmWork* p) {
    MapEnmWork* q = p;
    FldPos* pos = &p->obj.fieldPosition;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapEnmSaveToCache(p);
        return 0;
    }

    if ((gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) && p->update != MapEnm01Hit) {
        return 1;
    }

    if (p->update != NULL) {
        (p->update)(q);

        if (p->update != NULL) {
            ColliderSetPosition(&p->collider, pos->x, pos->y, pos->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm01_2(MapEnmWork* p) {
    MapEnmDraw(p);
}

void Task_MapEnm01_3(MapEnmWork* p) {
    MapEnmDestroy(p);
}

void MapEnm02Idle(MapEnmWork* p) {
    MapEnmSetAnim(p, 0, 1);
    MapEnmUpdateAnim(p);
    TaskPoolUpdate(&p->tasks);

    if (IsHitByMapAttack(&p->obj.fieldPosition, p->radius, p->height)) {
        m4aSongNumStart(SONG_SYS_FIELD_ATT00);
        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        gMapRoomState->flags |= ROOM_FLAG_ENEMY_STRUCK;
        MapEnmStartBattle(p);
    }

    MapEnmCheckContact(p);
}

void Task_MapEnm02_0(MapEnmWork* p, MapEnmArgs* q) {
    MapEnmInit(p, q);
    p->update = MapEnm02Idle;
    MapEnmSetAnim(p, 0, 1);
    p->gfx = AnimGetGfx(&p->anim);
    ColliderSetDisabled(&p->collider, 0);
}

s32 Task_MapEnm02_1(MapEnmWork* p) {
    MapEnmWork* w = p;
    FldPos* q = &w->obj.fieldPosition;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapEnmSaveToCache(p);
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

void Task_MapEnm02_2(MapEnmWork* p) {
    MapEnmDraw(p);
}

void Task_MapEnm02_3(MapEnmWork* p) {
    MapEnmDestroy(p);
}

void MapEnm03UpdateHover(MapEnmWork* p, u8 a) {
    s32* q = &p->obj.fieldPosition.x;
    s32 t = q[2];
    s32 v;

    switch (a) {
    case 1:
        v = p->targetZ + gSineTable[gFrameCounter & 0xFF] * 10;
        break;
    case 0:
    default:
        v = p->targetZ + gSineTable[gFrameCounter * 2 & 0xFF] * 12;
        break;
    }

    if (p->flags & MAP_ENM_FLAG_SLOW) {
        q[2] += (v - q[2]) / 80;
    } else {
        q[2] += (v - q[2]) >> 4;
    }

    if (q[3] < q[2]) {
        q[2] = t;
        p->targetZ = t - 0x1C00;
    }
}

s32 MapEnm03MoveToTarget(MapEnmWork* p) {
    s32* q = &p->obj.fieldPosition.x;
    s32 dx;
    s32 dy;
    s32 lim;

    q[4] += 0x100;

    if (q[4] > 0x500) {
        q[4] = 0x500;
    }

    dx = (p->targetX - p->obj.fieldPosition.x) / 32;
    lim = q[4];

    if (dx > lim) {
        dx = lim;
    } else if (dx < -lim) {
        dx = -lim;
    }

    q[0] += dx;

    dy = (p->targetY - q[1]) / 32;

    if (dy > lim) {
        dy = lim;
    } else if (dy < -lim) {
        dy = -lim;
    }

    q[1] += dy;

    if (p->timer > 64) {
        return 1;
    }

    p->timer++;
    return 0;
}

s32 MapEnm03IsPlayerNearHome(MapEnm03Work* p, s32 lim) {
    s32 dx;
    s32 dy;

    dx = p->home.x - gFieldState->actor.fieldPosition.x;

    if (dx < 0) {
        dx = gFieldState->actor.fieldPosition.x - p->home.x;
    }

    dy = p->home.y - gFieldState->actor.fieldPosition.y;

    if (dy < 0) {
        dy = gFieldState->actor.fieldPosition.y - p->home.y;
    }

    if (dx > 0x8000 || dy > 0x8000) {
        return 0;
    }

    return Sqrt8((dx * dx >> 8) + (dy * dy >> 8)) < lim ? 1 : 0;
}

void MapEnm03Guard(MapEnmWork* w) {
    FldObj* q = &w->obj;

    MapEnmSetAnim(w, 0, 3);
    MapEnmUpdateAnim(w);
    TaskPoolUpdate(&w->tasks);
    MapEnm03UpdateHover(w, 0);

    if (GetRandom() % 20 == 0) {
        q->angle = GetAngle(w->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if ((u8)MapEnm03IsPlayerNearHome((MapEnm03Work*)w, 0x6000) != 0 && q->fieldPosition.ground == gFieldState->actor.fieldPosition.ground) {
        w->targetX = gFieldState->actor.fieldPosition.x;
        w->targetY = gFieldState->actor.fieldPosition.y;
        w->targetZ = gFieldState->actor.fieldPosition.ground - 0x1000;
        w->timer = 0;
        q->speed = 0;
        w->update = MapEnm03Charge;
    }

    MapEnmCheckContact(w);
}

void MapEnm03Charge(MapEnmWork* w) {
    MapEnm03Work* q = (MapEnm03Work*)w;
    FldObj* v = &w->obj;
    FldPos tmp;
    s32 n;

    MapEnmSetAnim(w, 1, 3);
    MapEnmUpdateAnim(w);
    TaskPoolUpdate(&w->tasks);
    MapEnm03UpdateHover(w, 1);
    tmp = v->fieldPosition;

    if (GetRandom() % 20 != 0) {
        v->angle = GetAngle(w->obj.fieldPosition.x, v->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if ((u8)MapEnm03IsPlayerNearHome((MapEnm03Work*)w, 0x6000) != 0 && v->fieldPosition.ground == gFieldState->actor.fieldPosition.ground) {
        w->targetX = gFieldState->actor.fieldPosition.x;
        w->targetY = gFieldState->actor.fieldPosition.y;
    }

    if ((u8)MapEnm03MoveToTarget(&q->enm) != 0) {
        w->targetX = q->home.x;
        w->targetY = q->home.y;
        w->targetZ = q->home.z;
        w->timer = 0;
        v->speed = 0;
        w->update = MapEnm03Return;
    }

    n = GetFldPosGround(&v->fieldPosition);

    if (n < v->fieldPosition.z) {
        v->fieldPosition = tmp;
        w->targetY = v->fieldPosition.y + 0x1000;
    } else if (n == 0x100000) {
        v->fieldPosition = tmp;
        w->targetY = v->fieldPosition.y - 0x1000;
    } else {
        v->fieldPosition.ground = n;
    }

    MapEnmCheckContact(w);
}

void MapEnm03Return(MapEnmWork* w) {
    FldObj* q = &w->obj;
    FldPos save;
    s32 r;

    MapEnmSetAnim(w, 1, 3);
    MapEnmUpdateAnim(w);
    TaskPoolUpdate(&w->tasks);
    MapEnm03UpdateHover(w, 1);
    save = q->fieldPosition;

    if (GetRandom() % 20 != 0) {
        q->angle = GetAngle(w->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if ((u8)MapEnm03MoveToTarget(w) != 0) {
        w->timer = 0;
        q->speed = 0;
        w->update = MapEnm03Guard;
    }

    r = GetFldPosGround(&q->fieldPosition);

    if (r < q->fieldPosition.z) {
        q->fieldPosition = save;
        w->targetY = q->fieldPosition.y + 0x1000;
    } else if (r == 0x100000) {
        q->fieldPosition = save;
        w->targetY = q->fieldPosition.y - 0x1000;
    } else {
        q->fieldPosition.ground = r;
    }

    MapEnmCheckContact(w);
}

void Task_MapEnm03_0(MapEnmWork* w, MapEnmArgs* arg) {
    MapEnmInit(w, arg);
    w->update = MapEnm03Guard;
    MapEnmSetAnim(w, 0, 1);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderSetDisabled(&w->collider, 0);
    w->timer = 0;
    ((MapEnm03Work*)w)->home = w->obj.fieldPosition;
}

s32 Task_MapEnm03_1(MapEnmWork* p) {
    MapEnmWork* w = p;
    FldPos* q = &w->obj.fieldPosition;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapEnmSaveToCache(p);
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

void Task_MapEnm03_2(MapEnmWork* p) {
    MapEnmDraw(p);
}

void Task_MapEnm03_3(MapEnmWork* p) {
    MapEnmDestroy(p);
}

void MapEnm04CheckOffscreen(MapEnm01Work* p) {
    if (p->enm.obj.fieldPosition.x < gFieldState->x - 0x1800 || p->enm.obj.fieldPosition.x > gFieldState->x + 0x10800) {
        if (p->wasOnScreen != 0) {
            p->enm.update = NULL;
        }
    } else if (p->wasOnScreen == 0) {
        p->wasOnScreen = 1;
    }
}

void MapEnm04UpdateHover(MapEnmWork* p, u8 a) {
    s32* q = &p->obj.fieldPosition.x;
    s32 t = q[2];
    s32 v;

    switch (a) {
    case 1:
        v = p->targetZ + gSineTable[gFrameCounter & 0xFF] * 10;
        break;
    case 0:
    default:
        v = p->targetZ + gSineTable[gFrameCounter * 2 & 0xFF] * 12;
        break;
    }

    if (p->flags & MAP_ENM_FLAG_SLOW) {
        q[2] += (v - q[2]) / 80;
    } else {
        q[2] += (v - q[2]) >> 4;
    }

    if (q[3] < q[2]) {
        q[2] = t;
        p->targetZ = t - 0x1C00;
    }
}

void MapEnm04PickTarget(MapEnmWork* p, u8 flag) {
    if (flag) {
        p->targetX = gFieldState->actor.fieldPosition.x;
        p->targetY = gFieldState->actor.fieldPosition.y;
        p->targetZ = gFieldState->actor.fieldPosition.z - 0x1000;
    } else {
        p->targetX = gFieldState->actor.fieldPosition.x;
        p->targetY = gFieldState->actor.fieldPosition.y;
        p->targetZ = gFieldState->actor.fieldPosition.z;

        if (GetRandom() % 2) {
            s32 t = GetRandom() % 65 * 256 + 0x2000;

            p->targetX -= t;
        } else {
            s32 t = GetRandom() % 65 * 256 + 0x2000;

            p->targetX += t;
        }

        {
            s32 t = GetRandom() % 121 * 256 - 0x3C00;

            p->targetY += t;
        }

        {
            s32 t = GetRandom() % 49 * 256 + 0x1000;

            p->targetZ -= t;
        }
    }
}

void MapEnm04Idle(MapEnmWork* p) {
    MapEnmWork* r = p;
    FldObj* q = &p->obj;
    FldPos tmp;

    MapEnmSetAnim(p, 0, 3);
    MapEnmUpdateAnim(p);
    TaskPoolUpdate(&p->tasks);
    tmp = p->obj.fieldPosition;
    MapEnm04UpdateHover(p, 0);

    if (GetRandom() % 20 == 0) {
        q->angle = GetAngle(p->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if (q->fieldPosition.z < gFieldState->actor.fieldPosition.z - 0x4000) {
        MapEnm04PickTarget(p, 0);
        p->timer = 0;
        q->speed = 0;
        p->update = MapEnm04Fly;
    } else if (GetRandom() % 130 == 0) {
        if (GetRandom() % 2) {
            MapEnm04PickTarget(p, 0);
        } else {
            MapEnm04PickTarget(p, 1);
        }

        r->timer = 0;
        q->speed = 0;
        r->update = MapEnm04Fly;
    }

    if ((u8)MapEnmCheckAttacked(r) != 0) {
        r->update = MapEnm04Hit;
    } else {
        MapEnmCheckContact(r);
        MapEnm04CheckOffscreen((MapEnm01Work*)p);
    }
}

void MapEnm04Fly(MapEnmWork* p) {
    FldObj* q = &p->obj;
    FldPos t;
    s32 dx;
    s32 dy;
    s32 v;
    s32 r;
    u32 lim;

    MapEnmSetAnim(p, 1, 3);
    MapEnmUpdateAnim(p);
    TaskPoolUpdate(&p->tasks);
    MapEnm04UpdateHover(p, 1);
    t = p->obj.fieldPosition;

    if (GetRandom() % 20 != 0) {
        q->angle = GetAngle(p->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    dx = p->targetX;
    dy = p->targetY;

    if (p->flags & MAP_ENM_FLAG_SLOW) {
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

    if (p->timer > lim) {
        p->update = MapEnm04Idle;
    } else {
        p->timer++;
    }

    r = GetFldPosGround(&q->fieldPosition);

    if (r < q->fieldPosition.z) {
        q->fieldPosition = t;
        p->targetY = q->fieldPosition.y + 0x1000;
    } else if (r == 0x100000) {
        q->fieldPosition = t;
        p->targetY = q->fieldPosition.y - 0x1000;
    } else {
        q->fieldPosition.ground = r;
    }

    if ((u8)MapEnmCheckAttacked(p) != 0) {
        p->update = MapEnm04Hit;
    } else {
        MapEnmCheckContact(p);
    }
}

void MapEnm04Hit(MapEnmWork* p) {
    MapEnmSetAnim(p, 2, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->flags |= MAP_ENM_FLAG_FIRST_STRIKE;
        MapEnmStartBattle(p);
    } else {
        MapEnmUpdateAnim(p);
    }
}

void MapEnm04Stand(MapEnmWork* p) {
    MapEnmSetAnim(p, 0, 0);
    p->gfx = AnimGetGfx(&p->anim);
    TaskPoolUpdate(&p->tasks);

    if ((u8)MapEnmCheckAttacked(p)) {
        p->update = MapEnm04Hit;
    } else {
        MapEnmCheckContact(p);
    }
}

void Task_MapEnm04_0(MapEnmWork* p, MapEnmArgs* q) {
    MapEnm01Work* w = (MapEnm01Work*)p;

    MapEnmInit(p, q);

    if (p->flags & MAP_ENM_FLAG_ASLEEP) {
        p->update = MapEnm04Stand;
        MapEnmSetAnim(p, 0, 0);
        p->gfx = AnimGetGfx(&p->anim);
        ColliderSetDisabled(&p->collider, 0);
    } else {
        p->update = MapEnm04Idle;
        MapEnmSetAnim(p, 0, 1);
        p->gfx = AnimGetGfx(&p->anim);
        ColliderSetDisabled(&p->collider, 0);
    }

    w->enm.timer = 0;
    ((MapEnm01Work*)p)->wasOnScreen = 0;
}

s32 Task_MapEnm04_1(MapEnmWork* p) {
    MapEnmWork* q = p;
    FldPos* pos = &p->obj.fieldPosition;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapEnmSaveToCache(p);
        return 0;
    }

    if ((gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) && p->update != MapEnm04Hit) {
        return 1;
    }

    if (p->update != NULL) {
        (p->update)(q);

        if (p->update != NULL) {
            ColliderSetPosition(&p->collider, pos->x, pos->y, pos->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm04_2(MapEnmWork* p) {
    MapEnmDraw(p);
}

void Task_MapEnm04_3(MapEnmWork* p) {
    MapEnmDestroy(p);
}

void MapEnm05Appear(MapEnmWork* p) {
    MapEnmWork* q = p;

    MapEnmSetAnim(p, 0, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        ColliderSetDisabled(&p->collider, 0);
        p->timer = GetRandom() % 121 + 60;
        p->update = MapEnm05Idle;
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

void MapEnm05Idle(MapEnmWork* p) {
    MapEnmWork* q = p;
    FldObj* r = &p->obj;

    MapEnmSetAnim(p, 1, 1);
    MapEnmUpdateAnim(p);
    TaskPoolUpdate(&p->tasks);

    if (GetRandom() % 20 == 0) {
        r->angle = GetAngle(p->obj.fieldPosition.x, r->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if ((u8)MapEnmCheckAttacked(p) != 0) {
        p->update = MapEnm05Hit;
    } else {
        MapEnmCheckContact(p);

        if (p->timer != 0) {
            p->timer--;
        } else {
            ColliderSetDisabled(&q->collider, 1);
            q->update = MapEnm05Vanish;
        }
    }
}

void MapEnm05Vanish(MapEnmWork* p) {
    p->flags |= MAP_ENM_FLAG_REMOVED;
    MapEnmSetAnim(p, 2, 0);
    MapEnmUpdateAnim(p);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->update = NULL;
    }
}

void MapEnm05Hit(MapEnmWork* p) {
    MapEnmSetAnim(p, 3, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->flags |= MAP_ENM_FLAG_FIRST_STRIKE;
        MapEnmStartBattle(p);
    } else {
        MapEnmUpdateAnim(p);
    }
}

void Task_MapEnm05_0(MapEnmWork* p, MapEnmArgs* q) {
    MapEnmInit(p, q);

    if (p->update == NULL) {
        p->update = MapEnm05Appear;
        MapEnmSetAnim(p, 0, 0);
        p->gfx = AnimGetGfx(&p->anim);
        ColliderSetDisabled(&p->collider, 1);
    } else {
        ColliderSetDisabled(&p->collider, 0);
    }

    p->timer = 0;
}

s32 Task_MapEnm05_1(MapEnmWork* p) {
    MapEnmWork* q = p;
    FldPos* pos = &p->obj.fieldPosition;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapEnmSaveToCache(p);
        return 0;
    }

    if ((gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) && p->update != MapEnm05Hit) {
        return 1;
    }

    if (p->update != NULL) {
        (p->update)(q);

        if (p->update != NULL) {
            ColliderSetPosition(&p->collider, pos->x, pos->y, pos->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm05_2(MapEnmWork* p) {
    MapEnmDraw(p);
}

void Task_MapEnm05_3(MapEnmWork* p) {
    MapEnmDestroy(p);
}

void MapEnm06Appear(MapEnmWork* p) {
    MapEnmWork* q = p;

    MapEnmSetAnim(p, 0, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        ColliderSetDisabled(&p->collider, 0);
        p->timer = GetRandom() % 121 + 60;
        p->update = MapEnm06Idle;
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

void MapEnm06Idle(MapEnmWork* p) {
    MapEnmWork* q = p;
    FldObj* r = &p->obj;

    MapEnmSetAnim(p, 1, 1);
    MapEnmUpdateAnim(p);
    TaskPoolUpdate(&p->tasks);

    if (GetRandom() % 20 == 0) {
        r->angle = GetAngle(p->obj.fieldPosition.x, r->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if ((u8)MapEnmCheckAttacked(p) != 0) {
        p->update = MapEnm06Hit;
    } else {
        MapEnmCheckContact(p);

        if (p->timer != 0) {
            p->timer--;
        } else {
            ColliderSetDisabled(&q->collider, 1);
            q->update = MapEnm06Vanish;
        }
    }
}

void MapEnm06Vanish(MapEnmWork* p) {
    p->flags |= MAP_ENM_FLAG_REMOVED;
    MapEnmSetAnim(p, 2, 0);
    MapEnmUpdateAnim(p);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->update = NULL;
    }
}

void MapEnm06Hit(MapEnmWork* p) {
    MapEnmSetAnim(p, 3, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->flags |= MAP_ENM_FLAG_FIRST_STRIKE;
        MapEnmStartBattle(p);
    } else {
        MapEnmUpdateAnim(p);
    }
}

void Task_MapEnm06_0(MapEnmWork* p, MapEnmArgs* q) {
    MapEnmInit(p, q);

    if (p->update == NULL) {
        p->update = MapEnm06Appear;
        MapEnmSetAnim(p, 0, 0);
        p->gfx = AnimGetGfx(&p->anim);
        ColliderSetDisabled(&p->collider, 1);
    } else {
        ColliderSetDisabled(&p->collider, 0);
    }

    p->timer = 0;
}

s32 Task_MapEnm06_1(MapEnmWork* p) {
    MapEnmWork* q = p;
    FldPos* pos = &p->obj.fieldPosition;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapEnmSaveToCache(p);
        return 0;
    }

    if ((gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) && p->update != MapEnm06Hit) {
        return 1;
    }

    if (p->update != NULL) {
        (p->update)(q);

        if (p->update != NULL) {
            ColliderSetPosition(&p->collider, pos->x, pos->y, pos->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm06_2(MapEnmWork* p) {
    MapEnmDraw(p);
}

void Task_MapEnm06_3(MapEnmWork* p) {
    MapEnmDestroy(p);
}

s32 GetMapRoomDebugCode(MapFloorRoom* p) {
    return (gGameState.floor << 28) + (p->roomType << 20) + (p->cardValue << 16) + (gMapFloorState.room << 8) + (gMapFloorState.eventStep << 4) + gMapFloorState.world;
}

void MapDbgWaitInput(MapDbgWork* w) {
    if ((GetKeysHeld() & (L_BUTTON | R_BUTTON)) == (L_BUTTON | R_BUTTON)) {
        if (GetKeysPressed() & SELECT_BUTTON) {
            *w->editing = 1;
            RequestFieldResume();
            ModeRequest(&gModeDebflag, 1);
        }

#ifndef VERSION_EU
        if (GetKeysPressed() & START_BUTTON) {
            w->visible = 1;
            *w->editing = 1;
            w->update = MapDbgEditSeed;
        }
#endif
    }
}

void MapDbgEditSeed(MapDbgWork* w) {
    MapFloorRoom* d;
    s32 step;
    s32 i;

    step = 1;

    for (i = w->seedCursor; i > 0; i--) {
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
        w->seedCursor = w->seedCursor == 7 ? 0 : w->seedCursor + 1;
    }

    if (GetKeysPressed() & DPAD_RIGHT) {
        w->seedCursor = w->seedCursor == 0 ? 7 : w->seedCursor - 1;
    }

    w->seedTextLength = FormatSmallFontHex(d->seed, w->seedText);

    if (GetKeysPressed() & SELECT_BUTTON) {
        if (++gMapFloorState.world > 12) {
            gMapFloorState.world = 0;
        }

        w->codeTextLength = FormatSmallFontHex(GetMapRoomDebugCode(d), w->codeText);
    }

    if (GetKeysPressed() & (L_BUTTON | R_BUTTON)) {
        w->update = MapDbgEditWorld;
    } else if (GetKeysPressed() & (A_BUTTON | B_BUTTON | START_BUTTON)) {
        *w->editing = 0;
        w->update = MapDbgWaitInput;
    }
}

void MapDbgEditWorld(MapDbgWork* w) {
    MapFloorRoom* d = GetMapFloorRoom(gMapFloorState.room);

    if ((GetKeysRepeat() & DPAD_UP) && w->codeCursor == 0) {
        gMapFloorState.world = gMapFloorState.world < WORLD_CASTLE_OBLIVION ? gMapFloorState.world + 1 : 0;
    }

    if ((GetKeysRepeat() & DPAD_DOWN) && w->codeCursor == 0) {
        gMapFloorState.world = gMapFloorState.world != 0 ? gMapFloorState.world - 1 : 12;
    }

    w->codeTextLength = FormatSmallFontHex(GetMapRoomDebugCode(d), w->codeText);

    if (GetKeysPressed() & (L_BUTTON | R_BUTTON)) {
        w->update = MapDbgEditSeed;
    }

    if (GetKeysPressed() & (A_BUTTON | B_BUTTON | START_BUTTON)) {
        *w->editing = 0;
        w->update = MapDbgWaitInput;
    }
}

void Task_MapDbg_0(MapDbgWork* w, u8* p) {
#ifndef VERSION_EU
    MapFloorRoom* d;
#endif
    w->visible = 0;
    w->editing = p;
    *p = 0;
    w->update = MapDbgWaitInput;
    w->seedCursor = 0;
    w->codeCursor = 0;
#ifdef VERSION_EU
    GetMapFloorRoom(gMapFloorState.room);
#else
    d = GetMapFloorRoom(gMapFloorState.room);
    w->tiles = LoadSmallFontTiles();
    w->palette = LoadSmallFontPalette();
    w->seedTextLength = FormatSmallFontHex(d->seed, w->seedText);
    w->codeTextLength = FormatSmallFontHex(GetMapRoomDebugCode(d), w->codeText);
    w->cursorTextLength = EncodeSmallFontString(sMapDbgCursorString, &w->cursorText);
#endif
}

s32 Task_MapDbg_1(MapDbgWork* w) {
    w->update(w);
    return 1;
}

void Task_MapDbg_2(MapDbgWork* w) {
#ifndef VERSION_EU
    if (w->visible != 0) {
        DrawSmallFontString(240 - w->seedTextLength * 8, 0x8E, w->seedText, w->tiles, w->palette, 0, w->seedTextLength);
        DrawSmallFontString(240 - w->codeTextLength * 8, 0x96, w->codeText, w->tiles, w->palette, 0, w->codeTextLength);

        if (*w->editing != 0) {
            if (w->update == MapDbgEditSeed) {
                DrawSmallFontString(240 - (w->seedCursor + 1) * 8, 0x90, &w->cursorText, w->tiles, w->palette, 0, w->cursorTextLength);
            } else {
                DrawSmallFontString(240 - (w->codeCursor + 1) * 8, 0x98, &w->cursorText, w->tiles, w->palette, 0, w->cursorTextLength);
            }
        }
    }
#endif
}

void Task_MapDbg_3(MapDbgWork* w) {
#ifndef VERSION_EU
    FreeSmallFontResources(w->tiles, w->palette);
#endif
}

void MapGmkJumpWaitStep(MapGmkJumpWork* w) {
    if (ColliderIsTouchingType(&w->collider, 1) && (w->collider.standFlags & COLLIDER_STAND_STOOD_ON)) {
        gMapRoomState->jumpGmkHeight = w->jumpHeight;
        gMapRoomState->jumpGmkAngle = w->obj.angle;
        w->update = MapGmkJumpWaitJump;
        w->state = 1;
        AnimStart(&w->anim, 1, ANIM_FLAG_LOOP);
    } else {
        AnimUpdate(&w->anim);
    }
}

void MapGmkJumpWaitJump(MapGmkJumpWork* w) {
    if (ColliderIsTouchingType(&w->collider, 1)) {
        gMapRoomState->jumpGmkHeight = w->jumpHeight;
        gMapRoomState->jumpGmkAngle = w->obj.angle;
    } else if (gFieldState->actor.fieldPosition.z != gFieldState->actor.fieldPosition.ground) {
        w->update = MapGmkJumpLaunch;
        w->state = 2;
        AnimStart(&w->anim, 2, ANIM_FLAG_LOOP);
    } else {
        w->update = MapGmkJumpWaitStep;
        w->state = 0;
        AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    }
}

void MapGmkJumpLaunch(MapGmkJumpWork* w) {
    if (AnimIsFinished(&w->anim)) {
        w->update = MapGmkJumpWaitStep;
        w->state = 0;
        AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    } else {
        AnimUpdate(&w->anim);
    }
}

void Task_MapGmk_Jump_0(MapGmkJumpWork* w, MapPlatform* arg) {
    FldObj* p = &w->obj;
    AnimState* a;

    p->fieldPosition.x = arg->x << 13;
    p->fieldPosition.y = arg->y << 12;
    p->fieldPosition.z = 0;
    p->fieldPosition.z = w->obj.fieldPosition.ground = GetFldPosFloor(&p->fieldPosition);
    p->fieldPosition.y -= w->obj.fieldPosition.ground;

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

    w->jumpHeight = arg->spotLowerZ - arg->spotUpperZ;
    w->palette = LoadObjPalette(&gUnk_099910C4[0x120], 32);
    w->tiles = LoadObjTiles(gUnk_0985A3EA, 0x980);
    a = &w->anim;
    AnimInit(a, gUnk_09EF8488, gUnk_09EF8468);
    w->state = 0;
    AnimStart(a, 0, ANIM_FLAG_LOOP);
    w->update = MapGmkJumpWaitStep;
    ColliderInit(&w->collider, 6, 16, 0);
    ColliderSetPosition(&w->collider, p->fieldPosition.x, p->fieldPosition.y, p->fieldPosition.z);
}

s32 Task_MapGmk_Jump_1(MapGmkJumpWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (FldObjIsOutOfView(&w->obj)) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != NULL) {
        w->update(w);
    }

    return 1;
}

void Task_MapGmk_Jump_2(MapGmkJumpWork* w) {
    u16 v;
    s32 k;
    s16 x;
    s16 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_Jump_3(MapGmkJumpWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 MapGmkEnmRise(MapGmkEnmWork* w) {
    if (w->timer != 0) {
        w->gfx = AnimUpdate(&w->anim);
        ApproachValue(&w->obj.fieldPosition.z, w->targetZ, w->timer);
        w->timer--;
    } else {
        gMapRoomState->flags |= ROOM_FLAG_START_BATTLE;
        gFieldState->flags |= FIELD_FLAG_FREEZE_ENEMIES;
        gMapRoomState->battleId = GetRandomBattleId();
        w->update = NULL;
    }

    return 1;
}

void Task_MapGmk_Enm_0(MapGmkEnmWork* w, FldPos* arg) {
    FldPos* e = &w->obj.fieldPosition;
    AnimState* an;
    void* anim;
    void* frames;
    u8 f;

    w->obj.fieldPosition = *arg;
    w->obj.fieldPosition.y += 0x800;
    w->obj.fieldPosition.z -= 0x1000;
    w->obj.height = 16;

    if (gMapFloorState.world != WORLD_ATLANTICA) {
        w->tiles = AllocObjTiles(0x220, gEmy01L00Tiles);
        w->palette = LoadObjPalette(gEmy01Palette, 32);
        an = &w->anim;
        anim = gEmy01L00Anims;
        frames = gEmy01L00Frames;
    } else {
        w->tiles = AllocObjTiles(0x440, gEmy0600Tiles);
        w->palette = LoadObjPalette(gEmy06Palette, 32);
        an = &w->anim;
        anim = gEmy0600Anims;
        frames = gEmy0600Frames;
    }

    do {
        AnimInit(an, anim, frames);
        AnimStart(an, 0, ANIM_FLAG_LOOP);
    } while (0);

    w->gfx = AnimGetGfx(an);
    w->update = MapGmkEnmRise;
    f = 0;

    if (gFieldState->actor.fieldPosition.x >= e->x) {
        f = 1;
    }

    w->flipX = f;
    w->timer = 8;
    w->targetZ = e->z - 0x1000;
}

u8 Task_MapGmk_Enm_1(MapGmkEnmWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (w->update != NULL) {
        return w->update(w);
    }

    return 1;
}

void Task_MapGmk_Enm_2(MapGmkEnmWork* w) {
    u16 flags;
    s32 k;
    s32 x;
    s32 y;
    s32 t;

    t = w->flipX;
    flags = SPRITE_PRIORITY(2);

    if (t) {
        flags = SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
    }

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, flags, -0x1004 - k * 4);
}

void Task_MapGmk_Enm_3(MapGmkEnmWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void Task_MapGmk_Dmy_0(MapGmkDmyWork* w) {
    w->tiles = AllocObjTiles(MapGmkGetFreeTiles() << 5, NULL);
}

s32 Task_MapGmk_Dmy_1() {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    return 1;
}

void Task_MapGmk_Dmy_2(MapGmkDmyWork* w) {
}

void Task_MapGmk_Dmy_3(MapGmkDmyWork* w) {
    if (w->tiles != NULL) {
        ReleaseObjTiles(w->tiles);
    }
}

u8 MapGmkTutorialWaitHit(MapGmkTutorialWork* w) {
    if (IsHitByMapAttack(&w->obj.fieldPosition, 0, 8) != 0) {
        if ((gFieldState->flags & FIELD_FLAG_PLAYER_JUMPING) == 0 && gFieldState->actor.fieldPosition.z == gFieldState->actor.fieldPosition.ground) {
            TaskPool* pool = &w->tasks;

            TaskCreate(pool, &gTaskDescMapSpark, &w->obj);
            m4aSongNumStart(SONG_SND_220);
            gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
            gFieldState->lockonTarget = &w->obj;
            gMapRoomState->door = &w->obj;
            w->update = MapGmkTutorialWaitCard;
            gMapRoomState->doorRoom = 0;
            gMapRoomState->doorSide = 0;
            FadeSetPaletteExcluded(w->palette->index + 16, 1);
            TaskCreate(pool, &gTaskDescRoomcreate, NULL);
        }
    }

    return 1;
}

u8 MapGmkTutorialWaitCard(MapGmkTutorialWork* w) {
    void* p = GetSelectedMapCard();

    if (p != NULL) {
        CreateMapRoom(gUnk_0984C868[0].entryRoom, p);
        w->update = MapGmkTutorialWaitOpen;
    }

    if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) == 0) {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        FadeSetPaletteExcluded(w->palette->index + 16, 0);
        w->update = MapGmkTutorialWaitHit;
    }

    return 1;
}

u8 MapGmkTutorialWaitOpen(MapGmkTutorialWork* w) {
    if (gFieldState->flags & FIELD_FLAG_DOOR_OPENED) {
        UpdateSpriteFrameTiles(w->tiles, gMapUiSpriteUs_098A94A0, gUnk_0994C364);
        w->opened = 1;
        w->update = MapGmkTutorialIdle;
    }

    return 1;
}

u8 MapGmkTutorialIdle(MapGmkTutorialWork* w) {
    return 1;
}

void Task_MapGmk_Tutorial_0(MapGmkTutorialWork* w) {
    w->obj.fieldPosition.x = 0x19000;
    w->obj.fieldPosition.y = 0xAA00;
    w->obj.fieldPosition.z = 0;
    w->obj.fieldPosition.ground = GetFldPosFloor(&w->obj.fieldPosition);
    w->obj.fieldPosition.z = w->obj.fieldPosition.ground;
    w->obj.fieldPosition.y -= w->obj.fieldPosition.ground;
    w->obj.angle = 0xAD;
    w->obj.height = 32;
    w->palette = LoadObjPalette(gUnk_09991204, 32);
    w->tiles = AllocSpriteFrameTiles(0x400);
    UpdateSpriteFrameTiles(w->tiles, gMapUiSpriteUs_098A94A0, gUnk_0994BF64);
    ColliderInit(&w->collider, 6, 16, 0);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, w->obj.fieldPosition.y, w->obj.fieldPosition.z);
    w->opened = 0;
    w->update = MapGmkTutorialWaitHit;
    TaskPoolInit(&w->tasks, 2);
}

s32 Task_MapGmk_Tutorial_1(MapGmkTutorialWork* w) {
    if (w->opened != 0 && (w->collider.standFlags & COLLIDER_STAND_STOOD_ON) && w->collider.otherType == 1) {
        gMapRoomState->flags |= ROOM_FLAG_ENTER_WORLD;
    }

    if (w->update != NULL) {
        if (w->update(w) == 0) {
            return 0;
        }
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

void Task_MapGmk_Tutorial_2(MapGmkTutorialWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0xFE4 - k * 4;
    DrawSprite(x, y, NULL, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
    TaskPoolDraw(&w->tasks);
}

void Task_MapGmk_Tutorial_3(MapGmkTutorialWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    TaskPoolDestroy(&w->tasks);
}

u8 MapGmkSpiderStartBattle(MapGmkSpiderWork* w) {
    AnimState* a = &w->anim;

    if (AnimIsFinished(a)) {
        gMapRoomState->flags |= ROOM_FLAG_START_BATTLE;
        gFieldState->flags |= FIELD_FLAG_FREEZE_ENEMIES;
        gMapRoomState->battleId = GetRandom() % 3 + 125;
        w->update = NULL;
    } else {
        w->gfx = AnimUpdate(a);
    }

    return 1;
}

void Task_MapGmk_Spider_0(MapGmkSpiderWork* w, MapGmkPlacement* arg) {
    u8 v;

    w->obj.fieldPosition = arg->pos;
    w->obj.height = 24;
    w->tiles = AllocObjTiles(0x720, gEmy2103Tiles);
    w->palette = LoadObjPalette(gEmy21Palette, 32);
    AnimInit(&w->anim, gEmy2103Anims, gEmy2103Frames);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    SetObjTileSource(w->tiles, gEmy2103Tiles);
    w->update = MapGmkSpiderStartBattle;
    v = 0;

    if (gFieldState->actor.fieldPosition.x >= w->obj.fieldPosition.x) {
        v = 1;
    }

    w->flipX = v;
}

u8 Task_MapGmk_Spider_1(MapGmkSpiderWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (w->update != NULL) {
        return w->update(w);
    }

    return 1;
}

void Task_MapGmk_Spider_2(MapGmkSpiderWork* w) {
    u16 flags;
    u16 v;
    s32 t;
    s32 k;
    s32 x;
    s32 y;

    t = w->flipX;
    flags = SPRITE_PRIORITY(2);

    if (t) {
        flags = SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
    }

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, flags, v);
}

void Task_MapGmk_Spider_3(MapGmkSpiderWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

u8 MapGmkGp00WaitHit(MapGmkGpWork* w) {
    FldPos* p = &w->obj.fieldPosition;

    if (IsHitByMapAttack(p, 8, 8)) {
        m4aSongNumStart(w->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, p);

        if (!(w->placement->flags & GMK_FLAG_USED)) {
            w->placement->flags |= GMK_FLAG_USED;
            DropMapGmkPrize(p);
        }

        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        w->timer = 20;
        w->update = MapGmkGp00HitDelay;
    }

    return 1;
}

u8 MapGmkGp00HitDelay(MapGmkGpWork* w) {
    if (w->timer != 0) {
        w->timer--;
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        w->update = MapGmkGp00WaitHit;
    }

    return 1;
}

void Task_MapGmk_GP00_0(MapGmkGpWork* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;

    w->placement = arg;
    e->fieldPosition = arg->pos;
    w->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    w->tiles = LoadObjTiles(d->tiles, d->tilesSize);
    w->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&w->anim, d->anims, d->gfxTable);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderInit(&w->collider, 6, d->radius, d->height);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->hitSong = d->hitSong;
    w->timer = 0;
    w->update = MapGmkGp00WaitHit;
}

u8 Task_MapGmk_GP00_1(MapGmkGpWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (FldObjIsOutOfView(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != NULL) {
        return w->update(w);
    }

    return 1;
}

void Task_MapGmk_GP00_2(MapGmkGpWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_GP00_3(MapGmkGpWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 MapGmkGp01WaitHit(MapGmkGp1Work* w) {
    FldPos* p = &w->obj.fieldPosition;

    if (FldObjIsOutOfView(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (!IsHitByMapAttack(p, 8, 8)) {
        w->gfx = AnimUpdate(&w->anim);
    } else {
        m4aSongNumStart(w->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, p);
        DropMapGmkPrize(&w->obj.fieldPosition);
        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        w->placement->flags |= GMK_FLAG_DESTROYED;
        ColliderSetDisabled(&w->collider, 1);
        AnimStart(&w->anim, 1, 0);
        w->update = MapGmkGp01Break;
    }

    return 1;
}

u8 MapGmkGp01Break(MapGmkGp1Work* w) {
    AnimState* a = &w->anim;

    if (!AnimIsFinished(a)) {
        w->gfx = AnimUpdate(a);
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        w->visible = 0;
        w->update = NULL;
    }

    return 1;
}

void Task_MapGmk_GP01_0(MapGmkGp1Work* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;
    AnimState* a;

    w->placement = arg;
    e->fieldPosition = arg->pos;
    w->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    a = &w->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(a);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->radius, d->height);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->hitSong = d->hitSong;
    w->visible = 1;
    w->update = MapGmkGp01WaitHit;
}

u8 Task_MapGmk_GP01_1(MapGmkGp1Work* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (w->update != NULL) {
        return w->update(w);
    }

    return 1;
}

void Task_MapGmk_GP01_2(MapGmkGp1Work* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    if (w->visible != 0) {
        x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
        k = w->obj.fieldPosition.y >> 8;
        y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
    }
}

void Task_MapGmk_GP01_3(MapGmkGp1Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 MapGmkGp02WaitHit(MapGmkGpWork* w) {
    FldPos* q = &w->obj.fieldPosition;

    if (IsHitByMapAttack(q, 8, 8)) {
        MapGmkPlacement* e;

        m4aSongNumStart(w->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);
        e = w->placement;

        if ((e->flags & GMK_FLAG_USED) == 0) {
            e->flags |= GMK_FLAG_USED;
            DropMapGmkPrize(q);
        }

        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        AnimStart(&w->anim, 1, 0);
        w->update = MapGmkGp02HitAnim;
    }

    return 1;
}

u8 MapGmkGp02HitAnim(MapGmkGpWork* w) {
    if (AnimIsFinished(&w->anim) == 0) {
        w->gfx = AnimUpdate(&w->anim);
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        AnimStart(&w->anim, 0, 0);
        w->gfx = AnimGetGfx(&w->anim);
        w->update = MapGmkGp02WaitHit;
    }

    return 1;
}

void Task_MapGmk_GP02_0(MapGmkGpWork* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;
    AnimState* a;

    w->placement = arg;
    e->fieldPosition = arg->pos;
    w->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    a = &w->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(a);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->radius, d->height);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->hitSong = d->hitSong;
    w->update = MapGmkGp02WaitHit;
}

u8 Task_MapGmk_GP02_1(MapGmkGpWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (FldObjIsOutOfView(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != NULL) {
        return w->update(w);
    }

    return 1;
}

void Task_MapGmk_GP02_2(MapGmkGpWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_GP02_3(MapGmkGpWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 MapGmkGp03WaitHit(MapGmkGpWork* w) {
    FldPos* q = &w->obj.fieldPosition;

    if (IsHitByMapAttack(q, 8, 8)) {
        m4aSongNumStart(w->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);
        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        AnimStart(&w->anim, 1, 0);
        w->update = MapGmkGp03HitAnim;
    }

    return 1;
}

u8 MapGmkGp03HitAnim(MapGmkGpWork* w) {
    AnimState* a = &w->anim;

    if (AnimIsFinished(a)) {
        MapGmkPlacement* e = w->placement;

        if ((e->flags & GMK_FLAG_USED) == 0) {
            e->flags |= GMK_FLAG_USED;
            DropMapGmkPrize(&w->obj.fieldPosition);
        }

        AnimStart(a, 2, 0);
        w->update = MapGmkGp03EndAnim;
    } else {
        w->gfx = AnimUpdate(a);
    }

    return 1;
}

u8 MapGmkGp03EndAnim(MapGmkGpWork* w) {
    if (AnimIsFinished(&w->anim) == 0) {
        w->gfx = AnimUpdate(&w->anim);
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        AnimStart(&w->anim, 0, 0);
        w->gfx = AnimGetGfx(&w->anim);
        w->update = MapGmkGp03WaitHit;
    }

    return 1;
}

void Task_MapGmk_GP03_0(MapGmkGpWork* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;
    AnimState* a;

    w->placement = arg;
    e->fieldPosition = arg->pos;
    w->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    a = &w->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(a);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->radius, d->height);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->hitSong = d->hitSong;
    w->update = MapGmkGp03WaitHit;
}

u8 Task_MapGmk_GP03_1(MapGmkGpWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (FldObjIsOutOfView(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != NULL) {
        return w->update(w);
    }

    return 1;
}

void Task_MapGmk_GP03_2(MapGmkGpWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_GP03_3(MapGmkGpWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 MapGmkGp04WaitHit(MapGmkGpWork* w) {
    FldPos* q = &w->obj.fieldPosition;
    AnimState* a = &w->anim;

    w->gfx = AnimUpdate(a);

    if ((w->placement->flags & GMK_FLAG_USED) == 0 && IsHitByMapAttack(q, 8, 8)) {
        m4aSongNumStart(w->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);
        DropMapGmkPrize(q);
        w->placement->flags |= GMK_FLAG_USED;
        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        AnimStart(a, 1, ANIM_FLAG_LOOP);
        w->timer = 20;
        w->update = MapGmkGp04HitDelay;
    }

    return 1;
}

u8 MapGmkGp04HitDelay(MapGmkGpWork* w) {
    w->gfx = AnimUpdate(&w->anim);

    if (w->timer != 0) {
        w->timer--;
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        w->update = NULL;
    }

    return 1;
}

void Task_MapGmk_GP04_0(MapGmkGpWork* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;

    w->placement = arg;
    e->fieldPosition = arg->pos;
    w->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&w->anim, d->anims, d->gfxTable);

    if (w->placement->flags & GMK_FLAG_USED) {
        AnimStart(&w->anim, 1, ANIM_FLAG_LOOP);
    } else {
        AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    }

    w->gfx = AnimGetGfx(&w->anim);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->radius, d->height);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->hitSong = d->hitSong;
    w->update = MapGmkGp04WaitHit;
}

u8 Task_MapGmk_GP04_1(MapGmkGpWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (FldObjIsOutOfView(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != NULL) {
        return w->update(w);
    }

    return 1;
}

void Task_MapGmk_GP04_2(MapGmkGpWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_GP04_3(MapGmkGpWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 MapGmkGp05WaitHit(MapGmkGpWork* w) {
    FldPos* q = &w->obj.fieldPosition;

    if (!(w->placement->flags & GMK_FLAG_USED) && IsHitByMapAttack(q, 8, 8)) {
        m4aSongNumStart(w->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);
        DropMapGmkPrize(q);
        w->placement->flags |= GMK_FLAG_USED;
        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        AnimStart(&w->anim, 1, 0);
        w->update = MapGmkGp05HitAnim;
    }

    return 1;
}

u8 MapGmkGp05HitAnim(MapGmkGpWork* w) {
    AnimState* a = &w->anim;

    if (!AnimIsFinished(a)) {
        w->gfx = AnimUpdate(a);
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        AnimStart(a, 2, 0);
        w->gfx = AnimGetGfx(a);
        w->update = NULL;
    }

    return 1;
}

void Task_MapGmk_GP05_0(MapGmkGpWork* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;

    w->placement = arg;
    e->fieldPosition = arg->pos;
    w->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&w->anim, d->anims, d->gfxTable);

    if (w->placement->flags & GMK_FLAG_USED) {
        AnimStart(&w->anim, 2, ANIM_FLAG_LOOP);
    } else {
        AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    }

    w->gfx = AnimGetGfx(&w->anim);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->radius, d->height);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->hitSong = d->hitSong;
    w->update = MapGmkGp05WaitHit;
}

u8 Task_MapGmk_GP05_1(MapGmkGpWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (FldObjIsOutOfView(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != NULL) {
        return w->update(w);
    }

    return 1;
}

void Task_MapGmk_GP05_2(MapGmkGpWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_GP05_3(MapGmkGpWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 MapGmkGp06WaitHit(MapGmkGpWork* w) {
    FldPos* q = &w->obj.fieldPosition;
    AnimState* a = &w->anim;

    w->gfx = AnimUpdate(a);

    if (IsHitByMapAttack(q, 8, 8)) {
        m4aSongNumStart(w->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);

        if ((w->placement->flags & GMK_FLAG_USED) == 0) {
            w->placement->flags |= GMK_FLAG_USED;
            DropMapGmkPrize(q);
        }

        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;

        if (w->placement->flags & GMK_FLAG_TOGGLED) {
            w->placement->flags &= ~GMK_FLAG_TOGGLED;
            AnimStart(a, 0, ANIM_FLAG_LOOP);
        } else {
            w->placement->flags |= GMK_FLAG_TOGGLED;
            AnimStart(a, 1, ANIM_FLAG_LOOP);
        }

        w->timer = 20;
        w->update = MapGmkGp06HitDelay;
    }

    return 1;
}

u8 MapGmkGp06HitDelay(MapGmkGpWork* w) {
    w->gfx = AnimUpdate(&w->anim);

    if (w->timer != 0) {
        w->timer--;
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        w->update = MapGmkGp06WaitHit;
    }

    return 1;
}

void Task_MapGmk_GP06_0(MapGmkGpWork* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;

    w->placement = arg;
    e->fieldPosition = arg->pos;
    w->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&w->anim, d->anims, d->gfxTable);

    if (w->placement->flags & GMK_FLAG_TOGGLED) {
        AnimStart(&w->anim, 1, ANIM_FLAG_LOOP);
    } else {
        AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    }

    w->gfx = AnimGetGfx(&w->anim);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->radius, d->height);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->hitSong = d->hitSong;
    w->update = MapGmkGp06WaitHit;
}

u8 Task_MapGmk_GP06_1(MapGmkGpWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (FldObjIsOutOfView(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != NULL) {
        return w->update(w);
    }

    return 1;
}

void Task_MapGmk_GP06_2(MapGmkGpWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_GP06_3(MapGmkGpWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

s32 MapGmkGp07WaitStep(MapGmkGp07Work* w) {
    AnimState* a = &w->anim;

    w->gfx = AnimUpdate(a);

    if (ColliderIsTouchingType(&w->collider, 1) != 0) {
        if (w->collider.standFlags & COLLIDER_STAND_STOOD_ON) {
            if (!(w->placement->flags & GMK_FLAG_USED)) {
                w->placement->flags |= GMK_FLAG_USED;
                DropMapGmkPrize(&w->obj.fieldPosition);
            }

            AnimStart(a, 1, 0);
            w->gfx = AnimGetGfx(a);
            w->update = MapGmkGp07WaitStepOff;
        }
    }

    return 1;
}

s32 MapGmkGp07WaitStepOff(MapGmkGp07Work* w) {
    w->gfx = AnimUpdate(&w->anim);

    if (ColliderIsTouchingType(&w->collider, 1) == 0) {
        AnimStart(&w->anim, 2, 0);
        w->update = MapGmkGp07EndAnim;
    }

    return 1;
}

s32 MapGmkGp07EndAnim(MapGmkGp07Work* w) {
    AnimState* a = &w->anim;

    if (AnimIsFinished(a)) {
        AnimStart(a, 0, ANIM_FLAG_LOOP);
        w->gfx = AnimGetGfx(a);
        w->update = MapGmkGp07WaitStep;
    } else {
        w->gfx = AnimUpdate(a);
    }

    return 1;
}

void Task_MapGmk_GP07_0(MapGmkGp07Work* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;

    w->placement = arg;
    e->fieldPosition = arg->pos;
    w->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&w->anim, d->anims, d->gfxTable);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->radius, d->height);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->update = MapGmkGp07WaitStep;
}

u8 Task_MapGmk_GP07_1(MapGmkGp07Work* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (FldObjIsOutOfView(&w->obj)) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != NULL) {
        return w->update(w);
    }

    return 1;
}

void Task_MapGmk_GP07_2(MapGmkGp07Work* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk_GP07_3(MapGmkGp07Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

s32 MapGmkGp08WaitHit(MapGmkGp08Work* w) {
    FldPos* q = &w->obj.fieldPosition;
    AnimState* a;

    if (IsHitByMapAttack(q, 8, 8)) {
        m4aSongNumStart(w->hitSong);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);

        if (!(w->placement->flags & GMK_FLAG_USED)) {
            w->placement->flags |= GMK_FLAG_USED;
            DropMapGmkPrize(q);
        }

        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        a = &w->anim;
        AnimStart(a, 1, 0);
        w->gfx2 = AnimGetGfx(a);
        w->overlayVisible = 1;
        w->update = MapGmkGp08HitAnim;
    }

    return 1;
}

s32 MapGmkGp08HitAnim(MapGmkGp08Work* w) {
    AnimState* a = &w->anim;

    if (!AnimIsFinished(a)) {
        w->gfx2 = AnimUpdate(a);
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        w->overlayVisible = 0;
        w->update = MapGmkGp08WaitHit;
    }

    return 1;
}

void Task_MapGmk_GP08_0(MapGmkGp08Work* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;

    w->placement = arg;
    e->fieldPosition = arg->pos;
    w->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    w->tiles = LoadObjTiles(d->tiles, d->tilesSize);
    w->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&w->anim, d->anims, d->gfxTable);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderInit(&w->collider, 6, d->radius, d->height);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->hitSong = d->hitSong;
    w->overlayVisible = 0;
    w->update = MapGmkGp08WaitHit;
}

u8 Task_MapGmk_GP08_1(MapGmkGp08Work* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (FldObjIsOutOfView(&w->obj)) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != NULL) {
        return w->update(w);
    }

    return 1;
}

void Task_MapGmk_GP08_2(MapGmkGp08Work* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);

    if (w->overlayVisible != 0) {
        DrawSprite(x, y, w->gfx2, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v - 1);
    }
}

void Task_MapGmk_GP08_3(MapGmkGp08Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

s32 MapGmkGp09WaitStep(MapGmkGp09Work* w) {
    AnimState* a = &w->anim;

    w->gfx2 = AnimUpdate(a);

    if (ColliderIsTouchingType(&w->collider, 1) != 0) {
        if (w->collider.standFlags & COLLIDER_STAND_STOOD_ON) {
            if (!(w->placement->flags & GMK_FLAG_USED)) {
                w->placement->flags |= GMK_FLAG_USED;
                DropMapGmkPrize(&w->obj.fieldPosition);
            }

            AnimStart(a, 1, 0);
            w->gfx2 = AnimGetGfx(a);
            w->overlayVisible = 1;
            w->update = MapGmkGp09StepAnim;
        }
    }

    return 1;
}

s32 MapGmkGp09StepAnim(MapGmkGp09Work* w) {
    if (AnimIsFinished(&w->anim)) {
        w->overlayVisible = 0;
        w->update = MapGmkGp09WaitStepOff;
    } else {
        w->gfx2 = AnimUpdate(&w->anim);
    }

    return 1;
}

s32 MapGmkGp09WaitStepOff(MapGmkGp09Work* w) {
    if (ColliderIsTouchingType(&w->collider, 1) == 0) {
        w->update = MapGmkGp09WaitStep;
    }

    return 1;
}

void Task_MapGmk_GP09_0(MapGmkGp09Work* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;

    w->placement = arg;
    e->fieldPosition = arg->pos;
    w->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    w->tiles = LoadObjTiles(d->tiles, d->tilesSize);
    w->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&w->anim, d->anims, d->gfxTable);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderInit(&w->collider, 6, d->radius, d->height);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->overlayVisible = 0;
    w->update = MapGmkGp09WaitStep;
}

u8 Task_MapGmk_GP09_1(MapGmkGp09Work* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (FldObjIsOutOfView(&w->obj)) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != NULL) {
        return w->update(w);
    }

    return 1;
}

void Task_MapGmk_GP09_2(MapGmkGp09Work* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);

    if (w->overlayVisible != 0) {
        DrawSprite(x, y, w->gfx2, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v - 1);
    }
}

void Task_MapGmk_GP09_3(MapGmkGp09Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

void Task_MapGmk00_0(MapGmk00Work* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;
    AnimState* a;

    w->placement = arg;
    e->fieldPosition = arg->pos;
    w->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    w->tiles = LoadObjTiles(d->tiles, d->tilesSize);
    w->palette = LoadObjPalette(d->palette, 32);
    a = &w->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(a);
    ColliderInit(&w->collider, 6, d->radius, d->height);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);

    if (FldObjIsOutOfView(e) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    }

    w->radius = d->radius;
    w->stoodOn = 0;
    w->visible = 1;
    w->unk_0C6 = 0;
}

u8 Task_MapGmk00_1(MapGmk00Work* w) {
    FldPos* q = &w->obj.fieldPosition;
    u16 t;

    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (FldObjIsOutOfView(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (!(w->placement->flags & GMK_FLAG_USED)) {
        t = w->collider.standFlags & COLLIDER_STAND_STOOD_ON;

        if (t != 0) {
            if (w->stoodOn != 1) {
                w->stoodOn = 1;
                w->placement->flags |= GMK_FLAG_USED;
                DropMapGmkPrize(q);
            }
        } else {
            w->stoodOn = 0;
        }
    }

    return 1;
}

void Task_MapGmk00_2(MapGmk00Work* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    if (w->visible != 0) {
        x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
        k = w->obj.fieldPosition.y >> 8;
        y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
    }
}

void Task_MapGmk00_3(MapGmk00Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 MapGmk01WaitHit(MapGmk01Work* w) {
    if (IsHitByMapAttack(&w->obj.fieldPosition, 8, 8)) {
        AnimState* a;

        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        m4aSongNumStart(SONG_SYS_TRESURE);
        a = &w->anim;
        AnimStart(a, 1, ANIM_FLAG_LOOP);
        w->gfx = AnimGetGfx(a);
        SetObjTileSource(w->tiles, gUnk_09858320);
        w->update = MapGmk01Open;
    }

    return 1;
}

u8 MapGmk01Open(MapGmk01Work* w) {
    FldPos* q = &w->obj.fieldPosition;

    if (w->placement->flags & GMK_FLAG_HAS_ENEMY) {
        gMapRoomState->flags |= ROOM_FLAG_ENEMY_STRUCK;
        w->placement->flags |= GMK_FLAG_USED;
        TaskCreate(&gFieldState->tasks, &sTaskDescMapGmkEnm, q);
        w->update = NULL;
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_NO_RANDOM_PRIZE;
        CreateWorldPrize(gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y, gFieldState->actor.fieldPosition.z);
        GetMapFloorRoom(gMapFloorState.room)->flags |= FLOOR_ROOM_FLAG_CHEST_OPENED;
        w->placement->flags |= GMK_FLAG_USED;
        w->timer = 20;
        w->update = MapGmk01WaitPrize;
    }

    return 1;
}

u8 MapGmk01WaitPrize(MapGmk01Work* w) {
    if (w->timer != 0) {
        if (IsMessageWindowOpen() == 0) {
            w->timer--;
        }
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        w->update = NULL;
    }

    return 1;
}

void Task_MapGmk01_0(MapGmk01Work* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;
    AnimState* a;

    w->placement = arg;
    e->fieldPosition = arg->pos;
    e->height = d->height;
    w->tiles = AllocObjTiles(0x320, gUnk_09858320);
    w->palette = LoadObjPalette(d->palette, 32);
    a = &w->anim;
    AnimInit(a, d->anims, d->gfxTable);

    if (w->placement->flags & GMK_FLAG_USED) {
        AnimStart(a, 1, ANIM_FLAG_LOOP);
        w->gfx = AnimGetGfx(a);
        w->update = NULL;
    } else {
        gMapRoomState->flags |= ROOM_FLAG_NO_RANDOM_PRIZE;
        AnimStart(a, 0, ANIM_FLAG_LOOP);
        w->gfx = AnimGetGfx(a);
        w->update = MapGmk01WaitHit;
    }

    SetObjTileSource(w->tiles, gUnk_09858320);
    ColliderInit(&w->collider, 6, d->radius, d->height);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
}

u8 Task_MapGmk01_1(MapGmk01Work* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (w->update != NULL) {
        return w->update(w);
    }

    return 1;
}

void Task_MapGmk01_2(MapGmk01Work* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk01_3(MapGmk01Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
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

u8 MapGmkBarrelWaitHit(MapGmkBarrelWork* w) {
    FldPos* p = &w->obj.fieldPosition;
    u16 r;

    if (IsHitByMapAttack(p, 8, 8) != 0) {
        r = GetRandom() % 10000;

        if (r <= 1499) {
            m4aSongNumStart(SONG_SYS_OBJ_BREAK);
            TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, p);
            gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
            gMapRoomState->flags |= ROOM_FLAG_ENEMY_STRUCK;
            w->placement->flags |= GMK_FLAG_DESTROYED;
            TaskCreate(&gFieldState->tasks, &sTaskDescMapGmkSpider, w->placement);
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
        w->placement->flags |= GMK_FLAG_DESTROYED;
        ColliderSetDisabled(&w->collider, 1);
        AnimStart(&w->anim, 1, 0);
        w->update = MapGmkBarrelBreak;
        return 1;
    }

    if (FldObjIsOutOfView(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    return 1;
}

u8 MapGmkBarrelBreak(MapGmkBarrelWork* w) {
    AnimState* a = &w->anim;

    if (!AnimIsFinished(a)) {
        w->gfx = AnimUpdate(a);
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        w->visible = 0;
        w->update = NULL;
    }

    return 1;
}

void Task_MapGmk_Barrel_0(MapGmkBarrelWork* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;
    AnimState* a;

    w->placement = arg;
    e->fieldPosition = arg->pos;
    w->obj.fieldPosition.x += d->offsetX << 8;
    e->fieldPosition.y += d->offsetY << 8;
    e->fieldPosition.z += d->offsetZ << 8;
    e->height = d->height;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    a = &w->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(a);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->radius, d->height);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->visible = 1;
    w->update = MapGmkBarrelWaitHit;
}

u8 Task_MapGmk_Barrel_1(MapGmkBarrelWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (w->update != NULL) {
        return w->update(w);
    }

    return 1;
}

void Task_MapGmk_Barrel_2(MapGmkBarrelWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    if (w->visible != 0) {
        x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
        k = w->obj.fieldPosition.y >> 8;
        y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
    }
}

void Task_MapGmk_Barrel_3(MapGmkBarrelWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

void MapGmk04CheckTalk(MapGmk04Work* w) {
    if ((gMapRoomState->flags & ROOM_FLAG_TUTORIAL_ACTIVE) == 0 && (u8)IsFldObjTalkTarget(&w->obj) != 0 && (GetKeysPressed() & A_BUTTON)) {
        m4aSongNumStart(SONG_SYS_KETTEI);
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSave, NULL);
        w->update = NULL;
    }
}

void MapGmk04CheckFirstTalk(MapGmk04Work* w) {
    u32 state = gMapRoomState->flags;

    if (state & ROOM_FLAG_TUTORIAL_ACTIVE) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        CreateCardMessageTask(&w->tasks, 0, 0x69);
        w->update = MapGmk04WaitFirstTalkEnd;
    } else if (gFieldState->lockonTarget == &w->obj) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        gMapRoomState->flags = state | 0x4000;
        CreateCardMessageTask(&w->tasks, 0, 0x67);
        w->update = MapGmk04WaitMessage;
    }
}

void MapGmk04WaitMessage(MapGmk04Work* w) {
    if (IsMessageWindowOpen() == 0) {
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSave, NULL);
        w->update = NULL;
    }
}

void MapGmk04WaitFirstTalkEnd(MapGmk04Work* w) {
    if (IsMessageWindowOpen() == 0) {
        gMapRoomState->flags &= ~ROOM_FLAG_TUTORIAL_ACTIVE;
        gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
        gGameState.progression.tutorialFlags |= 0x10;
        w->update = MapGmk04CheckTalk;
    }
}

void Task_MapGmk04_0(MapGmk04Work* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;

    w->placement = arg;
    e->fieldPosition = arg->pos;
    e->height = d->height;
    e->kind = 3;

    if (gGameState.progression.tutorialFlags & 0x10) {
        w->update = MapGmk04CheckTalk;
    } else {
        w->update = MapGmk04CheckFirstTalk;
    }

    w->palette = LoadObjPalette(d->palette, 32);
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    AnimInit(&w->anim, d->anims, d->gfxTable);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderInit(&w->collider, 4, 24, 24);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    TaskPoolInit(&w->tasks, 1);
    FldObjRegister(e);
}

s32 Task_MapGmk04_1(MapGmk04Work* w) {
    TaskPoolUpdate(&w->tasks);

    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    w->gfx = AnimUpdate(&w->anim);

    if (w->update != NULL) {
        w->update(w);

        if (w->update != NULL) {
            return 1;
        }
    }

    return 0;
}

void Task_MapGmk04_2(MapGmk04Work* w) {
    FldPos* p = &w->obj.fieldPosition;
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    TaskPoolDraw(&w->tasks);
    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = p->y >> 8;
    y = k + (p->z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk04_3(MapGmk04Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    TaskPoolDestroy(&w->tasks);
    FldObjUnregister(&w->obj);
}

void MapGmk05CheckTalk(MapGmk05Work* w) {
    if (w->targeted != 0 && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        RequestFieldResume();
        FadeStartOut(FADE_MODE_BLACK, 16);
        m4aSongNumStart(SONG_SYS_MOUGURI);
        w->update = MapGmk05EnterShop;
    }
}

void MapGmk05EnterShop(MapGmk05Work* w) {
    MapFloorRoom* e;

    if (FadeIsActive() != 0) {
        return;
    }

    e = GetMapFloorRoom(gMapFloorState.room);

    if (e->flags & FLOOR_ROOM_FLAG_SHOP_VISITED) {
        ModeRequest(&gModeMsTop, 0);
    } else {
        e->flags |= FLOOR_ROOM_FLAG_SHOP_VISITED;
        ModeRequest(&gModeMsTop, 1);
    }

    w->update = NULL;
}

void Task_MapGmk05_0(MapGmk05Work* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;
    AnimState* a;

    e->fieldPosition = arg->pos;
    e->height = d->height;
    e->kind = 2;
    w->update = MapGmk05CheckTalk;
    w->palette = LoadObjPalette(d->palette, 32);
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    a = &w->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(a);
    ColliderInit(&w->collider, 4, 16, 24);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    FldObjRegister(e);
    TaskPoolInit(&w->tasks, 1);
    TaskCreate(&w->tasks, &gTaskDescFldShadow, e);
    w->targeted = 0;
    TaskPoolInit(&w->tasks2, 1);
    TaskCreate(&w->tasks2, &gTaskDescMapTalk, e);
}

s32 Task_MapGmk05_1(MapGmk05Work* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    w->gfx = AnimUpdate(&w->anim);
    w->targeted = IsFldObjTalkTarget(&w->obj);

    if (w->update != NULL) {
        w->update(w);

        if (w->update != NULL) {
            return 1;
        }
    }

    return 0;
}

void Task_MapGmk05_2(MapGmk05Work* w) {
    FldObj* p = &w->obj;
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    k = p->fieldPosition.y >> 8;
    v = -0x1004 - k * 4;
    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    y = k + (p->fieldPosition.z >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
    p->shadowZ = p->fieldPosition.ground;
    p->shadowPriority = v + 1;
    TaskPoolDraw(&w->tasks);

    if (w->targeted != 0) {
        TaskPoolDraw(&w->tasks2);
    }
}

void Task_MapGmk05_3(MapGmk05Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    FldObjUnregister(&w->obj);
    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->tasks2);
}

void MapGmk06CheckTalk(MapGmk06Work* w) {
    if (gFieldState->lockonTarget == &w->obj && (gGameState.progression.tutorialFlags & 0x100) == 0) {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        gMapRoomState->flags |= ROOM_FLAG_TUTORIAL_ACTIVE;
        CreateCardMessageTask(&w->tasks, 0, 0x84);
        gFieldState->lockonDelay = 30;
        w->update = MapGmk06WaitMessage;
    } else if ((u8)IsFldObjTalkTarget(&w->obj) != 0 && (GetKeysPressed() & A_BUTTON)) {
        m4aSongNumStart(SONG_SYS_KETTEI);
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        RequestFieldResume();
        FadeStartOut(FADE_MODE_BLACK, 16);
        w->update = MapGmk06EnterWorldWarp;
    }
}

void MapGmk06EnterWorldWarp(MapGmk06Work* w) {
    if (FadeIsActive() == 0) {
        ModeRequest(&gModeWorldwarp, 0);
        w->update = NULL;
    }
}

void MapGmk06WaitMessage(MapGmk06Work* w) {
    if (IsMessageWindowOpen() == 0) {
        gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
        gMapRoomState->flags &= ~ROOM_FLAG_TUTORIAL_ACTIVE;
        gGameState.progression.tutorialFlags |= 0x100;
        w->update = MapGmk06CheckTalk;
    } else {
        gFieldState->lockonDelay = 30;
    }
}

void Task_MapGmk06_0(MapGmk06Work* w, MapGmkPlacement* arg) {
    FldObj* e = &w->obj;
    const MapGmkDef* d = arg->def;

    e->fieldPosition = arg->pos;
    e->height = d->height;
    e->kind = 3;
    w->update = MapGmk06CheckTalk;
    w->palette = LoadObjPalette(d->palette, 32);
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    AnimInit(&w->anim, d->anims, d->gfxTable);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderInit(&w->collider, 4, 24, 24);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    TaskPoolInit(&w->tasks, 1);
    FldObjRegister(e);
}

s32 Task_MapGmk06_1(MapGmk06Work* w) {
    TaskPoolUpdate(&w->tasks);

    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    w->gfx = AnimUpdate(&w->anim);

    if (w->update != NULL) {
        w->update(w);

        if (w->update != NULL) {
            return 1;
        }
    }

    return 0;
}

void Task_MapGmk06_2(MapGmk06Work* w) {
    FldPos* p = &w->obj.fieldPosition;
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    TaskPoolDraw(&w->tasks);
    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = p->y >> 8;
    y = k + (p->z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), v);
}

void Task_MapGmk06_3(MapGmk06Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    TaskPoolDestroy(&w->tasks);
    FldObjUnregister(&w->obj);
}

void MapPrizeBounce(MapPrizeWork* w) {
    w->vz += 0x38;
    w->z += w->vz;
    w->x += gSineTable[w->angle] * w->speed >> 8;
    w->y += -gSineTable[w->angle + 64] * w->speed >> 8;

    if (IsFldPosBlocked((FldPos*)w) != 0) {
        w->angle = w->angle + (100 + GetRandom() % 57);
    } else {
        w->ground = GetFldPosGround((FldPos*)w);
    }

    if (w->z > w->ground) {
        w->z = w->ground;
        w->vz = -(GetRandom() % 0x181 + 0x180);
    }

    if (w->collider.colliding != 0) {
        u16 t;

        switch (w->kind) {
        case 2:
        case 3:
            m4aSongNumStart(SONG_SYS_POWER_GET);
            gGameState.progression.mooglePoints += w->amount;

            if (gGameState.progression.mooglePoints > 99999) {
                gGameState.progression.mooglePoints = 99999;
            }

            break;
        case 0:
        case 1:
        default:
            m4aSongNumStart(SONG_SYS_POWER_GET);
            gGameState.hp += w->amount;
            t = gGameState.progression.maxHp;

            if (gGameState.hp > (s16)t) {
                gGameState.hp = t;
            }

            break;
        }

        w->update = MapPrizeCollect;
        w->timer = 0;
        w->angle = GetAngle(gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y, w->x, w->y);
        w->collected = 1;
        w->visible = 1;
        w->angleStep = GetRandom() % 6 + 5;
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetPosition(&w->collider, w->x, w->y, w->z);

        if (w->timer == 20) {
            ColliderSetDisabled(&w->collider, 0);
        }

        if (w->timer > 420) {
                w->visible = w->visible == 0 ? 1 : 0;
        }

        if (w->timer++ > 480) {
            w->update = NULL;
        }
    }
}

void MapPrizeCollect(MapPrizeWork* w) {
    s32 x;
    s32 y;
    s32 z;
    s32 s;
    FieldState* g = gFieldState;

    s = gSineTable[w->angle] * 32;
    x = g->actor.fieldPosition.x + (s * w->scale >> 8);
    s = -gSineTable[w->angle + 64] * 22;
    y = g->actor.fieldPosition.y + (s * w->scale >> 8);
    z = g->actor.fieldPosition.z - (w->timer / 2 << 8);
    w->angle += w->angleStep;
    w->x += (x - w->x) >> 2;
    w->y += (y - w->y) >> 2;
    w->z += (z - w->z) >> 2;
    w->ground = func_080DFE7C(w->x, w->y, w->z);
    w->scale -= 2;

    if (w->timer > 60) {
        w->update = NULL;
    } else {
        w->timer++;
    }
}

void Task_MapPrize_0(MapPrizeWork* w, MapPrizeArgs* arg) {
    w->x = arg->x;
    w->y = arg->y;
    w->z = arg->z;
    w->ground = 0;
    FldPosInitGround((FldPos*)w);
    w->vz = -(GetRandom() % 0x301 + 0x200);
    w->speed = GetRandom() % 155 + 153;
    w->angle = GetRandom();
    w->tiles = LoadObjTiles(gUnk_098A5CF4, 0x160);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    w->kind = arg->id;

    switch (w->kind) {
    case 3:
        w->gfx = gUnk_098A5CAE;
        w->amount = 10;
        break;
    case 2:
        w->gfx = gUnk_098A5CA4;
        w->amount = 4;
        break;
    case 1:
        w->gfx = gUnk_098A5C9A;
        w->amount = gGameState.progression.maxHp / 20;
        break;
    case 0:
    default:
        w->gfx = gUnk_098A5C90;
        w->amount = gGameState.progression.maxHp * 3 / 100;
        break;
    }

    w->gfx2 = gUnk_098A5CB8;
    w->collected = 0;
    w->visible = 1;
    w->timer = 0;
    w->update = MapPrizeBounce;
    w->scale = 0x100;
    ColliderInit(&w->collider, 5, 16, 50);
    ColliderSetPosition(&w->collider, w->x, w->y, w->z);
    ColliderSetDisabled(&w->collider, 1);
}

s32 Task_MapPrize_1(MapPrizeWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (w->update == NULL) {
        return 0;
    }

    w->update(w);

    if (w->update == NULL) {
        return 0;
    }

    return 1;
}

void Task_MapPrize_2(MapPrizeWork* w) {
    s16 x;
    s16 y;
    ObjAffine* aff;

    if (w->visible != 0) {
        x = (w->x >> 8) - (gFieldState->x >> 8);
        y = (w->y >> 8) + (w->z >> 8) - (gFieldState->y >> 8);

        if (w->scale != 0x100) {
            aff = AllocObjAffine(0, w->scale, w->scale, 0);
        } else {
            aff = NULL;
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, aff, SPRITE_PRIORITY(2), -0x1004 - (w->y >> 8) * 4);

        if (w->collected == 0) {
            DrawSprite(x, (w->y >> 8) + (w->ground >> 8) - (gFieldState->y >> 8), w->gfx2, w->tiles, w->palette, aff, SPRITE_PRIORITY(2), 0xFFFF);
        }
    }
}

void Task_MapPrize_3(MapPrizeWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

void MapPrzCardUpdateScale(MapPrzCardWork* work) {
    work->scaleX = -gSineTable[((work->phaseX + 0x80) & 0xFF) + 0x40] * work->scale >> 8;
    work->scaleY = -gSineTable[((work->phaseY + 0x80) & 0xFF) + 0x40] * work->scale >> 8;

    if ((u16)(work->scaleX + 2) <= 4) {
        work->scaleX = 2;
    }

    if ((u16)(work->scaleY + 2) <= 4) {
        work->scaleY = 2;
    }
}

void MapPrzCardAimAtCenter(MapPrzCardWork* w) {
    s32 dx;
    s32 dy;

    dx = 0x7800;
    dy = 0x5000;
    dx -= w->posX;
    dy -= w->posY;
    w->distance = NormalizeVector2D8(&dx, &dy);
    w->dirX = -dx;
    w->dirY = -dy;
    w->speed = 0x300;
    w->unk_0AC = 2;
}

void MapPrzCardBounce(MapPrzCardWork* w) {
    FldPos v = *(FldPos*)w;
    s32 nx;
    s32 ny;

    w->unk_0AC += 0x38;
    w->posZ += w->unk_0AC;
    w->posX += gSineTable[w->angle] * w->speed >> 8;
    w->posY += -gSineTable[w->angle + 64] * w->speed >> 8;

    if (IsFldPosBlocked((FldPos*)w) != 0) {
        w->angle = w->angle + (112 + GetRandom() % 33);
        w->posX = v.x;
        w->posY = v.y;
    } else {
        w->ground = GetFldPosGround((FldPos*)w);
    }

    if (w->posZ - 0x800 > w->ground) {
        w->posZ = w->ground - 0x800;
        w->unk_0AC = -(w->unk_0AC * 217 >> 8);

        if (w->unk_0AC > -0x200) {
            w->unk_0AC = -0x200;
        }
    }

    if (w->collider.colliding != 0) {
        w->collected = 1;
        m4aSongNumStart(SONG_SYS_ITEMGET);
        ObtainCard(w->cardId);

        if (w->worldPrize == 0) {
            MapFloorRoom* e = GetMapFloorRoom(gMapFloorState.room);

            if (e->przCardsLeft != 0) {
                e->przCardsLeft--;
            }
        }

        nx = (w->posX >> 8) - (gFieldState->x >> 8);
        ny = (w->posY >> 8) + (w->posZ >> 8) - (gFieldState->y >> 8);
        w->posX = (s16)nx << 8;
        w->posY = (s16)ny << 8;
        ColliderSetDisabled(&w->collider, 1);
        w->priority = 50;
        MapPrzCardAimAtCenter(w);
        w->spriteFlags = 0;
        w->update = MapPrzCardFlyToCenter;
    } else {
        w->x = (w->posX >> 8) - (gFieldState->x >> 8);
        w->y = (w->posY >> 8) + (w->posZ >> 8) - (gFieldState->y >> 8);
        w->priority = -0x1004 - (w->posY >> 8) * 4;
        MapPrzCardUpdateScale(w);
        w->phaseX += 2;
        ColliderSetPosition(&w->collider, w->posX, w->posY, w->posZ);

        if (w->timer == 20) {
            ColliderSetDisabled(&w->collider, 0);
        }

        if (w->timer <= 59) {
            w->timer++;
        }
    }
}

void MapPrzCardFlyToCenter(MapPrzCardWork* w) {
    s32 dx;
    s32 dy;
    s32 x;
    s32 y;

    if (w->speed < 0) {
        dx = 0x7800 - w->posX;
        dy = 0x5000 - w->posY;
        NormalizeVector2D8(&dx, &dy);
        w->dirX = -dx;
        w->dirY = -dy;

        if (w->distance <= 0x7FF) {
            w->rotation = 0;
            w->timer = 0;
            w->update = MapPrzCardShowName;
            TaskCreate(&w->tasks, &gTaskDescMapMsg, LANGSEL(gCardDefs[w->cardId].name));
        }
    }

    w->posX += w->dirX * w->speed >> 8;
    w->posY += w->dirY * w->speed >> 8;
    w->rotation += 32;
    w->phaseY += (64 - w->phaseY) >> 4;
    w->phaseX = 0;
    w->distance = VectorLength2D(0x7800 - w->posX, 0x5000 - w->posY);
    w->speed -= w->unk_0AC;
    w->unk_0AC += 2;
    w->scale += 3;

    if (w->scale > 0x100) {
        w->scale = 0x100;
    }

    x = w->posX >> 8;
    w->x = x;
    y = w->posY >> 8;
    w->y = y;
    MapPrzCardUpdateScale(w);
}

void MapPrzCardShowName(MapPrzCardWork* w) {
    s32 x;
    s32 y;

    w->posX = 0x7800;
    w->posY = 0x5800;
    w->rotation = 0;
    w->phaseY = 0;
    w->scale += 2;

    if (w->scale > 0x100) {
        w->scale = 0x100;
    }

    x = w->posX >> 8;
    w->x = x;
    y = w->posY >> 8;
    w->y = y;
    MapPrzCardUpdateScale(w);
    w->timer++;

    if (w->timer == 30) {
        w->timer = 0;
        w->update = MapPrzCardShrink;
    }

    TaskPoolUpdate(&w->tasks);
}

void MapPrzCardShrink(MapPrzCardWork* w) {
    s32 x;
    s32 y;

    w->rotation += 32;
    x = (gFieldState->actor.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    y = (gFieldState->actor.fieldPosition.y >> 8) + (gFieldState->actor.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    w->x += ((s16)x - w->x) >> 3;
    w->y += ((s16)y - w->y) >> 3;
    w->scaleX -= 10;
    w->scaleY -= 10;

    if (w->scaleX <= 10) {
        w->update = NULL;
    }
}

void Task_MapPrzCard_0(MapPrzCardWork* w, MapPrizeArgs* p) {
    const CardDef* d;
    const CardBack* q;

    gMapRoomState->flags |= ROOM_FLAG_PRIZE_CARD_ACTIVE;
    w->cardId = p->id;
    d = &gCardDefs[w->cardId];
    w->tiles = LoadObjTiles(d->tiles, 0x300);
    w->palette = LoadObjPalette(d->palette, 32);
    w->stat = *(UnkStruct_08F70ACC*)&d->kind;
    q = &gCardBacks[w->stat.category];
    w->palette2 = LoadObjPalette(gCard00Palette, 32);
    w->tiles2 = LoadObjTiles(q->tiles, 0x280);
    w->tiles3 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    w->palette3 = LoadObjPalette(gUnk_08F69BE4, 32);
    w->tiles4 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    w->posX = p->x;
    w->posY = p->y;
    w->posZ = p->z;
    w->ground = 0;
    FldPosInitGround((FldPos*)w);
    w->unk_0AC = -(GetRandom() % 129 + 0x300);
    w->speed = GetRandom() % 129 + 128;
    w->angle = GetRandom();
    w->scaleX = 128;
    w->scaleY = 128;
    w->scale = 128;
    w->rotation = 24;
    w->phaseY = 0;
    w->phaseX = 0;
    w->worldPrize = p->worldPrize;
    ColliderInit(&w->collider, 5, 30, 10);
    ColliderSetPosition(&w->collider, w->posX, w->posY, w->posZ);

    if (w->worldPrize != 0) {
        ColliderSetDisabled(&w->collider, 0);
    } else {
        ColliderSetDisabled(&w->collider, 1);
    }

    w->spriteFlags = SPRITE_PRIORITY(2);
    w->timer = 0;
    w->update = MapPrzCardBounce;
    w->collected = 0;
    TaskPoolInit(&w->tasks, 1);
}

s32 Task_MapPrzCard_1(MapPrzCardWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        return 0;
    }

    if (w->update == NULL) {
        return 0;
    }

    w->update(w);

    if (w->update == NULL) {
        return 0;
    }

    return 1;
}

void Task_MapPrzCard_2(MapPrzCardWork* w) {
    const CardDef* d;
    const CardBack* q;
    void* t;
    ObjAffine* affine;
    s16 x;
    s16 y;
    s16 s;

    if (w->scaleX == 0x100 && w->scaleY == 0x100 && w->rotation == 0) {
        affine = NULL;
    } else {
        affine = AllocObjAffine(w->rotation, w->scaleX, w->scaleY, 1);
    }

    d = &gCardDefs[w->cardId];
    DrawSprite(w->x, w->y - 8, d->gfx, w->tiles, w->palette,
        affine, w->spriteFlags, w->priority + 1);
    q = &gCardBacks[w->stat.category];
    DrawSprite(w->x, w->y - 8, q->gfx, w->tiles2,
        w->palette2, affine, w->spriteFlags, w->priority);

    if (w->stat.category != 3) {
        t = gUnk_09EE981C[w->stat.value];
        DrawSprite(w->x, w->y - 8, t, w->tiles3,
            w->palette2, affine, w->spriteFlags, w->priority - 1);
    }

    if (w->collected == 0) {
        x = (w->posX >> 8) - (gFieldState->x >> 8);
        y = (w->posY >> 8) + (w->ground >> 8) - (gFieldState->y >> 8);
        s = 204 - ((w->ground - w->posZ) >> 7);

        if (s <= 2) {
            s = 2;
        }

        DrawSprite(x, y, gUnk_09EE1380[0], w->tiles4, w->palette3,
            AllocObjAffine(0, s, s, 0), SPRITE_PRIORITY(2), w->priority + 2);
    }

    TaskPoolDraw(&w->tasks);
}

void Task_MapPrzCard_3(MapPrzCardWork* w) {
    FadeSetPaletteExcluded(w->palette2->index + 0x10, 0);
    FadeSetPaletteExcluded(w->palette->index + 0x10, 0);
    ColliderUnregister(&w->collider);
    ReleaseObjTiles(w->tiles);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjTiles(w->tiles3);
    ReleaseObjTiles(w->tiles4);
    ReleaseObjPalette(w->palette);
    ReleaseObjPalette(w->palette2);
    ReleaseObjPalette(w->palette3);
    TaskPoolDestroy(&w->tasks);
    gMapRoomState->flags &= ~ROOM_FLAG_PRIZE_CARD_ACTIVE;
}

void MapPrzStockShowMessage(MapPrzStockWork* w) {
    CreateCardMessageTask(&w->tasks, 0, w->stock[1]);
    w->update = MapPrzStockWaitMessage;
}

void MapPrzStockWaitMessage(MapPrzStockWork* w) {
    if (IsMessageWindowOpen() == 0) {
        w->update = NULL;
    }
}

void Task_MapPrzStock_0(MapPrzStockWork* w, u16* a) {
    w->stock = a;
    gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
    gFieldState->flags |= FIELD_FLAG_FREEZE_ENEMIES;
    w->update = MapPrzStockShowMessage;
    TaskPoolInit(&w->tasks, 1);
}

s32 Task_MapPrzStock_1(MapPrzStockWork* w) {
    TaskPoolUpdate(&w->tasks);

    if (w->update != NULL) {
        w->update(w);

        if (w->update != NULL) {
            return 1;
        }
    }

    return 0;
}

void Task_MapPrzStock_2(MapPrzStockWork* w) {
    TaskPoolDraw(&w->tasks);
}

void Task_MapPrzStock_3(MapPrzStockWork* w) {
    TaskPoolDestroy(&w->tasks);
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_ENEMIES;
}

void MapMsgInit(MapMsgWork* w, void* text) {
    LoadBgTiles(0, &gUnk_099597E4[0x140], 0x140);
    LoadBgMap(0, &gUnk_09985F44[0x400], 0x800);
    SetBgScroll(0, 0, (u16)-46);
    LoadPalette(gCard00Palette, &gUnk_050001C0[0x20], 32);
    InitTextSlots(w->textSlots, 48);
    w->textSlotCount = LoadTextSlots(text, w->textSlots);
    w->palette = LoadTextPalette(1);
    FadeSetPaletteExcluded(w->palette->index + 16, 1);
    w->textX = (240 - GetTextSlotsWidth(w->textSlots, w->textSlotCount)) / 2;
    w->timer = 0;
}

s32 Task_MapMsg_1(MapMsgWork* w) {
    return 1;
}

void MapMsgDraw(MapMsgWork* w) {
    DrawTextSlots(w->textX, 120, w->textSlots, w->palette, 50, w->textSlotCount);
}

void MapMsgDestroy(MapMsgWork* w) {
    if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) == 0) {
        DisableBg(0);
    }

    FadeSetPaletteExcluded(w->palette->index + 0x10, 0);
    ReleaseObjPalette(w->palette);
    FreeTextSlots(w->textSlots, 0x30);
}

s32 Task_MapMsg2_1(MapMsgWork* w) {
    w->timer++;

    if (w->timer == 120) {
        return 0;
    }

    return 1;
}

void Task_MapSpark_0(MapSparkWork* w, FldObj* obj) {
    AnimState* a;

    w->obj = obj;
    w->tiles = AllocObjTiles(0x200, gUnk_098A4B68);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    a = &w->anim;
    AnimInit(a, gUnk_09EF8CC0, gUnk_09EF8CA0);

    if (gGameState.flags & GAME_FLAG_RIKU) {
        AnimStart(a, 1, ANIM_FLAG_LOOP);
    } else {
        AnimStart(a, 0, ANIM_FLAG_LOOP);
    }
}

s32 Task_MapSpark_1(MapSparkWork* w) {
    AnimUpdate(&w->anim);

    if (AnimIsFinished(&w->anim) != 0) {
        return 0;
    }

    return 1;
}

void Task_MapSpark_2(MapSparkWork* w) {
    FldObj* p = w->obj;
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
    DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, NULL, SPRITE_PRIORITY(1), 0x50);
}

void Task_MapSpark_3(MapSparkWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void Task_MapTalk_0(MapTalkWork* w, FldObj* obj) {
    w->obj = obj;
    w->tiles = AllocObjTiles(0x200, &gUnk_098A4B68[0x1028]);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    AnimInit(&w->anim, gUnk_09EF8CD0, gUnk_09EF8CC8);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->playerOnRight = 0;
}

s32 Task_MapTalk_1(MapTalkWork* w) {
    FldObj* p = w->obj;
    AnimState* anim = &w->anim;

    AnimUpdate(anim);

    if (gFieldState->actor.fieldPosition.x < p->fieldPosition.x) {
        w->playerOnRight = 0;
        AnimStart(anim, 0, ANIM_FLAG_LOOP);
    } else {
        w->playerOnRight = 1;
        AnimStart(anim, 1, ANIM_FLAG_LOOP);
    }

    return 1;
}

void Task_MapTalk_2(MapTalkWork* w) {
    FldObj* p = w->obj;
    u16 x;
    u16 y;

    if (w->playerOnRight != 0) {
        x = (p->fieldPosition.x >> 8) - (gFieldState->x >> 8) - 16;
    } else {
        x = (p->fieldPosition.x >> 8) - (gFieldState->x >> 8) + 16;
    }

    y = (p->fieldPosition.y >> 8) + ((p->fieldPosition.z - (p->height << 8)) >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, NULL, SPRITE_PRIORITY(1), 0x50);
}

void Task_MapTalk_3(MapTalkWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

const MapGmkDef gMapGmk01Def = {
    gUnk_099912C4, gUnk_09858320, 0x200, 0, 0, gUnk_09EF8414, gUnk_09EF841C,
    1, 13, 0, 0, 0, 16, 16, SONG_SYS_TRESURE, 0, &gTaskDescMapGmk01,
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
    gUnk_099912E4, gUnk_09858B3C, 0x400, 0, 0, gUnk_09EF8424, gUnk_09EF8460,
    1, 0, 0, 0, 0, 12, 24, SONG_SYS_OBJ_BREAK, 0, &gTaskDescMapGmkBarrel,
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
    gUnk_09991324, gUnk_0985ADAA, 0x400, 0, 0, &gUnk_09EF8494, &gUnk_09EF84A4,
    1, 13, 0, 0, 0, 24, 62, SONG_SYS_KETTEI, 0, &gTaskDescMapGmk04,
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
    gMoguPalette, gMoguFl00Tiles, 0x100, 0, 0, gMoguFl00Frames, gMoguFl00Anims,
    1, 13, 0, 0, 0, 16, 24, SONG_SYS_MOUGURI, 0, &gTaskDescMapGmk05,
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
    gUnk_09991344, gUnk_0985BDEA, 0x400, 0, 0, &gUnk_09EF84A8, &gUnk_09EF84B8,
    1, 13, 0, 0, 0, 24, 54, SONG_SYS_KETTEI, 0, &gTaskDescMapGmk06,
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
