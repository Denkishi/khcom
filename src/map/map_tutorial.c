#include "map_resource_assets.h"
#include "map_tasks.h"
#include "sprites_emy.h"
#include "sprites_map.h"
#include "sprites_map_tasks.h"
#include "sprite_palettes.h"
#include "songs.h"
#include "anim.h"
#include "battle_actor_types.h"
#include "btl_collision.h"
#include "card_api.h"
#include "field_state.h"
#include "fld_types.h"
#include "game_state.h"
#include "m4a_song.h"
#include "map.h"
#include "map_api.h"
#include "map_types.h"
#include "obj.h"
#include "obj_api.h"
#include "player_progression_types.h"
#include "registration_data.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

void MapTutorialStartBattle() {
    gFieldState->flags |= FIELD_FLAG_FREEZE_ENEMIES;
    gMapRoomState->battleId = 10;
    gMapRoomState->flags &= ~ROOM_FLAG_TUTORIAL_ACTIVE;
    gMapRoomState->flags |= ROOM_FLAG_START_BATTLE;
}

void MapTutorialWaitStart(MapTutorialWork* w) {
    u32 flags;

    if (gFieldState->lockonTarget == NULL) {
        flags = gFieldState->flags;

        if (!(flags & FIELD_FLAG_MENU_OPEN) && !(gMapRoomState->flags & ROOM_FLAG_SAVE_MENU_OPEN) && (gGameState.progression.tutorialFlags & 0x10)) {
            gMapRoomState->flags |= ROOM_FLAG_TUTORIAL_ACTIVE;
            gFieldState->flags = flags | FIELD_FLAG_FREEZE_PLAYER;
            CreateCardMessageTask(&w->tasks, 0, 0x6A);
            w->update = MapTutorialDropBarrel;
        }
    }
}

void MapTutorialDropBarrel(MapTutorialWork* w) {
    if (!IsMessageWindowOpen()) {
        AnimState* a;

        MapPickFreeFloorPosInView(&w->obj.fieldPosition, &w->obj.fieldPosition.y);
        w->obj.fieldPosition.z = 0;
        w->obj.fieldPosition.ground = GetFldPosFloor(&w->obj.fieldPosition);
        w->obj.fieldPosition.y -= w->obj.fieldPosition.ground;
        w->obj.fieldPosition.z = w->obj.fieldPosition.ground - 0xA000;
        w->obj.height = 24;
        w->obj.speed = 2;
        w->tiles = AllocObjTiles(0x400, gUnk_09858B3C);
        w->palette = LoadObjPalette(gUnk_099912E4, 32);
        a = &w->anim;
        AnimInit(a, gUnk_09EF8460, gUnk_09EF8424);
        AnimStart(a, 0, ANIM_FLAG_LOOP);
        w->gfx = AnimGetGfx(a);
        ColliderInit(&w->collider, 6, 12, 24);
        ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, w->obj.fieldPosition.y, w->obj.fieldPosition.z);
        w->shadowVisible = 1;
        TaskCreate(&w->tasks2, &gTaskDescFldShadow, &w->obj);
        w->visible = 1;
        w->update = MapTutorialBarrelFall;
    }
}

void MapTutorialBarrelFall(MapTutorialWork* w) {
    MapTutorialWork* p = w;

    w->obj.speed += 0x38;
    w->obj.fieldPosition.z += w->obj.speed;

    if (w->obj.fieldPosition.z > w->obj.fieldPosition.ground) {
        gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
        m4aSongNumStart(SONG_SND_215);
        w->obj.fieldPosition.z = w->obj.fieldPosition.ground;
        w->obj.speed = 0;
        w->shadowVisible = 0;
        w->update = MapTutorialWaitBarrelHit;
    }

    ColliderSetPosition(&p->collider, p->obj.fieldPosition.x, p->obj.fieldPosition.y, p->obj.fieldPosition.z);
}

void MapTutorialWaitBarrelHit(MapTutorialWork* w) {
    if (IsHitByMapAttack(&w->obj.fieldPosition, 8, 8)) {
        m4aSongNumStart(SONG_SYS_OBJ_BREAK);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, &w->obj);
        gMapRoomState->flags &= ~ROOM_FLAG_NO_RANDOM_PRIZE;
        TryCreateRandomPrzCard(0, w->obj.fieldPosition.x, w->obj.fieldPosition.y, w->obj.fieldPosition.z);
        AnimStart(&w->anim, 1, 0);
        w->update = MapTutorialBarrelBreak;
        ColliderUnregister(&w->collider);
    }
}

void MapTutorialBarrelBreak(MapTutorialWork* w) {
    if (AnimIsFinished(&w->anim)) {
        w->update = MapTutorialWaitPrizeCard;
    } else {
        w->gfx = AnimUpdate(&w->anim);
    }
}

void MapTutorialWaitPrizeCard(MapTutorialWork* w) {
    if ((gMapRoomState->flags & ROOM_FLAG_PRIZE_CARD_ACTIVE) == 0) {
        gGameState.progression.tutorialFlags |= 0x2000;
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        CreateCardMessageTask(&w->tasks, 0, 0x6B);
        w->update = MapTutorialSpawnEnemy;
    }
}

void MapTutorialSpawnEnemy(MapTutorialWork* w) {
    if (!IsMessageWindowOpen()) {
        AnimState* a;
        u8 v;

        MapPickFreeFloorPosInView(&w->obj.fieldPosition, &w->obj.fieldPosition.y);
        w->obj.fieldPosition.z = 0;
        w->obj.fieldPosition.ground = GetFldPosFloor(&w->obj.fieldPosition);
        w->obj.fieldPosition.y -= w->obj.fieldPosition.ground;
        w->obj.fieldPosition.z = w->obj.fieldPosition.ground;
        w->obj.height = 16;
        v = 0;

        if (gFieldState->actor.fieldPosition.x > w->obj.fieldPosition.x) {
            v = 1;
        }

        w->flip = v;
        w->tiles = AllocObjTiles(0x400, gEmy00L06Tiles);
        w->palette = LoadObjPalette(gEmy00Palette, 32);
        a = &w->anim;
        AnimInit(a, gEmy00L06Anims, gEmy00L06Frames);
        AnimStart(a, 0, ANIM_FLAG_LOOP);
        w->gfx = AnimGetGfx(a);
        ColliderInit(&w->collider, 3, 8, 16);
        ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, w->obj.fieldPosition.y, w->obj.fieldPosition.z);
        ColliderSetDisabled(&w->collider, 1);
        w->update = MapTutorialEnemyAppear;
    }
}

void MapTutorialEnemyAppear(MapTutorialWork* w) {
    AnimState* a = &w->anim;

    if (AnimIsFinished(a)) {
        AnimChangeWithTables(a, 0, ANIM_FLAG_LOOP, gEmy00L00Anims, gEmy00L00Frames);
        SetObjTileSource(w->tiles, gEmy00L00Tiles);
        CreateCardMessageTask(&w->tasks, 0, 0x6C);
        w->update = MapTutorialWaitEnemyMessage;
    } else {
        w->gfx = AnimUpdate(a);
    }
}

void MapTutorialWaitEnemyMessage(MapTutorialWork* w) {
    w->gfx = AnimUpdate(&w->anim);

    if (!IsMessageWindowOpen()) {
        gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
        ColliderSetDisabled(&w->collider, 0);
        w->update = MapTutorialEnemyUpdate;
    }
}

void MapTutorialEnemyUpdate(MapTutorialWork* w) {
    AnimState* a = &w->anim;

    w->gfx = AnimUpdate(a);

    if (IsHitByMapAttack(&w->obj.fieldPosition, 8, 16)) {
        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        gMapRoomState->flags |= ROOM_FLAG_ENEMY_STRUCK;
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, &w->obj);
        m4aSongNumStart(SONG_SYS_FIELD_ATT00);
        AnimChangeWithTables(a, 0, ANIM_FLAG_LOOP, gEmy00L09Anims, gEmy00L09Frames);
        SetObjTileSource(w->tiles, gEmy00L09Tiles);
        w->update = MapTutorialEnemyHit;
    } else if (w->collider.colliding) {
        if (!(gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) && w->collider.otherType == 1) {
            ColliderSetDisabled(&w->collider, 1);
            MapTutorialStartBattle();
        } else {
            w->obj.fieldPosition.x += w->collider.pushX;
            w->obj.fieldPosition.y += w->collider.pushY;
        }
    }
}

void MapTutorialEnemyHit(MapTutorialWork* w) {
    AnimState* a = &w->anim;

    if (AnimIsFinished(a)) {
        ColliderSetDisabled(&w->collider, 1);
        gGameState.flags |= GAME_FLAG_FIRST_STRIKE;
        MapTutorialStartBattle();
    } else {
        w->gfx = AnimUpdate(a);
    }
}

void Task_MapTutorial_0(MapTutorialWork* w) {
    u16 t;

    TaskPoolInit(&w->tasks, 1);
    TaskPoolInit(&w->tasks2, 1);
    gMapRoomState->flags |= ROOM_FLAG_NO_RANDOM_PRIZE;
    w->tiles = NULL;
    w->palette = NULL;
    w->flip = 0;
    t = gGameState.progression.tutorialFlags & 0x2000;

    if (t == 0) {
        w->shadowVisible = 0;
        w->visible = 0;
        w->update = MapTutorialWaitStart;
    } else {
        gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
        TaskCreate(&w->tasks2, &gTaskDescFldShadow, &w->obj);
        w->visible = 1;
        w->shadowVisible = 1;
        w->update = MapTutorialSpawnEnemy;
    }
}

s32 Task_MapTutorial_1(MapTutorialWork* w) {
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);

    if (w->update != NULL) {
        w->update(w);

        if (w->update != NULL) {
            return 1;
        }
    }

    return 0;
}

void Task_MapTutorial_2(MapTutorialWork* w) {
    u16 flags;
    u16 v;
    s32 k;
    s32 t;
    s16 x;
    s16 y;

    TaskPoolDraw(&w->tasks);

    if (w->visible) {
        x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
        k = w->obj.fieldPosition.y >> 8;
        y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        t = w->flip;
        flags = SPRITE_PRIORITY(2);

        if (t) {
            flags = SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, flags, v);

        if (w->shadowVisible) {
            w->obj.shadowZ = w->obj.fieldPosition.ground;
            w->obj.shadowPriority = v + 1;
            TaskPoolDraw(&w->tasks2);
        }
    }
}

void Task_MapTutorial_3(MapTutorialWork* w) {
    if (w->tiles != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
    }

    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->tasks2);
}

TaskDesc gTaskDescMapTutorial = {
    "Task_MapTutorial",
    (TaskInitFunc)Task_MapTutorial_0,
    (TaskUpdateFunc)Task_MapTutorial_1,
    (TaskDrawFunc)Task_MapTutorial_2,
    (TaskDestroyFunc)Task_MapTutorial_3,
    sizeof(MapTutorialWork),
};
