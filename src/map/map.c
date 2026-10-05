/**
 * map.c
 * Field Map Modes and Menus
 */

#include "system_state.h"
#include "monsgage.h"
#include "map.h"
#include "map_spawn_data.h"
#include "sprites_btl.h"
#include "sprites_evt.h"
#include "sprites_map.h"
#include "sprites_sora.h"
#include "world_types.h"
#include "gba/keys.h"
#include "gba/io_reg.h"
#include "engine_math.h"
#include "mode_pooh_api.h"
#include "map_runtime.h"
#include "malloc.h"
#include "fade.h"
#include "player_progression.h"
#include "status_api.h"
#include "allmap_api.h"
#include "songs.h"
#include "map_fixed_data.h"
#include "jiminy_data.h"
#include "common_text.h"
#include <string.h>
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "btl_collision.h"
#include "card_api.h"
#include "display.h"
#include "field_state.h"
#include "fld_types.h"
#include "game_state.h"
#include "gba/defines.h"
#include "key.h"
#include "listpool.h"
#include "m4a_catalog_data.h"
#include "m4a_song.h"
#include "map_api.h"
#include "map_enemy_data.h"
#include "map_room_data.h"
#include "map_room_types.h"
#include "map_types.h"
#include "mode.h"
#include "mode_battle_data.h"
#include "msg_api.h"
#include "obj.h"
#include "obj_api.h"
#include "player_progression_types.h"
#include "registration_data.h"
#include "save.h"
#include "save_api.h"
#include "save_types.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "text.h"
#include "text_types.h"
#include "types.h"
#include <stddef.h>
#include "card_map_anim.h"
#include "card_deckmenu2.h"
#include "map_room_tables.h"
#include "sprite_palettes.h"

extern u8 gSoraWorldBattleBase[];
extern u8 gRikuWorldBattleBase[];
extern u8 (*gMapGmkSpotFuncs[])(FldPos*);
extern u8 (*gMapAnmCmds[])(MapAnmSlot*);
extern u8 gWorldEntryEvents[];

static u8 sMapEnmCount;
static u8 sMapEnmTileCount;
static u8 sMapEnmSpawnTimer;
static FldPos sMapEnmSpawnPositions[3];
static u8 sMapGmkCount;
static u8 sMapGmkPaletteCount;
static u16 sMapGmkTileCount;
static const EventKeyList* sEventKeyList;
static EventKey sEventKey;
static EventKeyProgress* sEventKeyProgress;
static ModeFunc sMapDbgUpdate;
static TaskPool sMapDbgTasks;
static u8 sMapDbgEditing;
static void* sMapDbgAllmapRoomTask;
static u32 sUnk_02034FAC;
static ModeFunc sMapFldUpdate;
static Task* sMapFldWorldLogoTask;
static void* sMapFldAllmapRoomTask;
static u8 sUnk_02034FBC;
static u8 sUnk_02034FC0[0x14];
static ModeFunc sMapFixUpdate;
static u8 sMapFixEventDelay;
static NewGameSlotMenuWork* sNewGameSlotMenuWork;
static LoadGameMenuWork* sLoadGameMenuWork;
static MenuMsgWork* sMenuMsgWork;

void MapEnmPlaceInView(MapEnmArgs* p) {
    FldPos* q = &p->pos;
    s32 t;

    MapPickFreeFloorPosInView(q, &q->y);
    q->z = 0;
    t = GetFldPosFloor(q);
    q->ground = t;
    q->y -= t;
    q->z = t;
}

void MapEnmPlaceInViewAbove(MapEnmArgs* p) {
    FldPos* q = &p->pos;
    s32 t;

    MapPickFreeFloorPosInView(q, &q->y);
    q->z = 0;
    t = GetFldPosFloor(q);
    q->ground = t;
    q->y -= t;
    q->z = -0xA000;
}

s32 MapEnmPlaceInRoom(MapEnmArgs* p) {
    FldPos* q = &p->pos;
    s32 t;
    s32 i;

    if (MapPickFreeFloorPos(q, &q->y)) {
        q->z = 0;
        t = GetFldPosFloor(q);
        q->ground = t;
        q->z = t;
        q->y -= t;

        for (i = 0; i < sMapEnmCount; i++) {
            if (sMapEnmSpawnPositions[i].x >> 8 == q->x >> 8 && sMapEnmSpawnPositions[i].y >> 8 == q->y >> 8) {
                return 0;
            }
        }

        return 1;
    }

    return 0;
}

u8 MapEnmPlaceAtStairs(MapEnmArgs* w) {
    FldPos* d = &w->pos;
    MapPlatform* q = GetMapPlatform(1);
    u16 wd = q->right - q->left - 2;
    u16 ht = gMapRoomState->bottomRow - gMapRoomState->topRow - 2;
    s32 i;

    for (i = 0; i < ht; i++) {
        s16 y = gMapRoomState->topRow + i;
        s32 j;

        for (j = 0; j < wd; j++) {
            s32 x = (s16)(q->left + j);
            MapCell* e = MapCellAt(x, y);

            if (e->lowerZ == q->z && (e->flags & MAP_CELL_FLAG_STAIRS)) {
                s32 t;
                s32 v;

                if (e->type == 4) {
                    w->angle = 0x53;
                    v = (x << 13) + 0x1800;
                } else if (e->type == 6) {
                    w->angle = 0xAD;
                    v = (x << 13) + 0x800;
                } else {
                    continue;
                }

                d->x = v;
                v = y << 12;
                d->y = v + 0x1800;
                d->z = 0;
                t = GetFldPosFloor(d);
                d->ground = t;
                d->z = t;
                d->y -= t;
                return 1;
            }
        }
    }

    return 0;
}

u8 MapEnmPlaceAboveGmk01(MapEnmArgs* w) {
    FldPos* d = &w->pos;
    MapPlatform* q = GetMapPlatform(0);
    u16 wd = q->right - q->left - 2;
    u16 ht = gMapRoomState->bottomRow - gMapRoomState->topRow - 2;
    s32 i;

    for (i = 0; i < ht; i++) {
        s16 y = gMapRoomState->topRow + i;
        s32 j;

        for (j = 0; j < wd; j++) {
            s32 x = (s16)(q->left + j);

            if (MapCellAt(x, y)->flags & MAP_CELL_FLAG_CHEST) {
                s32 t;

                d->x = x << 13;
                d->y = y << 12;
                d->z = 0;
                t = GetFldPosFloor(d);
                d->ground = t;
                d->y -= t;
                d->z = t - 0x2000;
                return 1;
            }
        }
    }

    return 0;
}

void MapEnmSetupArgs(MapEnmArgs* p, const MapEnmDef* q) {
    if (q->flags & MAP_ENM_DEF_FLAG_SPAWN_ANYWHERE) {
        MapEnmPlaceInRoom(p);
    } else if (q->flags & MAP_ENM_DEF_FLAG_AIRBORNE) {
        MapEnmPlaceInViewAbove(p);
    } else {
        MapEnmPlaceInView(p);
    }

    switch (GetRandom() % 4) {
    case 0:
        p->angle = 0xAD;
        break;
    case 1:
        p->angle = 0x53;
        break;
    case 2:
        p->angle = 0xD3;
        break;
    default:
        p->angle = 0x2D;
        break;
    }

    p->speed = 0;
    p->def = q;
    p->update = NULL;
}

void MapEnmSpawnFixed(MapEnmArgs* w, u8 a, u8 b) {
    const u8* t;
    MapFloorRoom* e;
    const MapEnmDef* d;
    u8 ok;

    t = gMapRoomShapes[gMapRoomState->roomType];
    e = GetMapFloorRoom(gMapFloorState.room);

    if (sMapEnmCount >= t[1]) {
        return;
    }

    if (e->enemiesLeft - sMapEnmCount <= 0) {
        return;
    }

    d = gMapEnmDefs[a];

    switch (b) {
    case 2:
        ok = MapEnmPlaceAtStairs(w);
        break;
    case 3:
        ok = MapEnmPlaceAboveGmk01(w);
        break;
    case 0:
    default:
        ok = MapEnmPlaceInRoom(w);
        w->angle = GetAngle(w->pos.x, w->pos.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
        break;
    }

    if (ok) {
        sMapEnmSpawnPositions[sMapEnmCount] = w->pos;
        w->speed = 0;
        w->def = d;
        w->update = NULL;
        TaskCreate(&gFieldState->tasks4, d->desc, w);
    }
}

void MapEnmApplyRoomFlags(MapEnmWork* work) {
    switch (gMapRoomState->roomType) {
    case 4:
        work->flags |= MAP_ENM_FLAG_AGGRESSIVE;
        break;
    case 5:
        work->flags |= MAP_ENM_FLAG_ASLEEP;
        work->flags |= MAP_ENM_FLAG_PERSISTENT;
        break;
    case 18:
        work->flags |= MAP_ENM_FLAG_SLOW;
        break;
    case 20:
        work->flags |= MAP_ENM_FLAG_WHITE_MUSHROOM;
        break;
    case 21:
        work->flags |= MAP_ENM_FLAG_BLACK_FUNGUS;
        break;
    }
}

void MapEnmSetAnim(MapEnmWork* work, u8 n, u16 a) {
    const AnimDef* q = work->def->animDef;

    switch (work->obj.angle >> 6) {
    case 0:
        q += n * 2;
        work->flags |= MAP_ENM_FLAG_HFLIP;
        break;
    case 1:
        q += n * 2 + 1;
        work->flags |= MAP_ENM_FLAG_HFLIP;
        break;
    case 2:
        q += n * 2 + 1;
        work->flags &= ~MAP_ENM_FLAG_HFLIP;
        break;
    default:
        q += n * 2;
        work->flags &= ~MAP_ENM_FLAG_HFLIP;
        break;
    }

    AnimChangeWithTables(&work->anim, q->animId, a, q->anims, q->gfxTable);
    SetObjTileSource(work->tiles, q->tiles);
}

void MapEnmUpdateAnim(MapEnmWork* work) {
    if (gFieldState->flags & FIELD_FLAG_ENEMY_FRAME_CHANGED) {
        if (AnimIsFrameEnding(&work->anim)) {
            return;
        }
    } else {
        if (AnimIsFrameEnding(&work->anim)) {
            gFieldState->flags |= FIELD_FLAG_ENEMY_FRAME_CHANGED;
        }
    }

    work->gfx = AnimUpdate(&work->anim);
}

u8 GetRandomBattleId() {
    const u8* q = gMapRoomShapes[gMapRoomState->roomType];
    u8 v = q[3] + GetRandom() % (q[4] - q[3] + 1);

    if (gGameState.flags & GAME_FLAG_RIKU) {
        return v + gRikuWorldBattleBase[gMapFloorState.world];
    }

    return v + gSoraWorldBattleBase[gMapFloorState.world];
}

void MapEnmStartBattle(MapEnmWork* work) {
    gGameState.flags |= GAME_FLAG_MAP_ENEMY_BATTLE;
    ColliderSetDisabled(&work->collider, 1);
    gMapRoomState->flags |= ROOM_FLAG_START_BATTLE;
    gFieldState->flags |= FIELD_FLAG_FREEZE_ENEMIES;
    work->flags |= MAP_ENM_FLAG_REMOVED;

    if (work->flags & MAP_ENM_FLAG_FIRST_STRIKE) {
        gGameState.flags |= GAME_FLAG_FIRST_STRIKE;
    }

    if (work->flags & MAP_ENM_FLAG_WHITE_MUSHROOM) {
        gMapRoomState->battleId = GetRandom() % 3 + 128;
    } else if (work->flags & MAP_ENM_FLAG_BLACK_FUNGUS) {
        gMapRoomState->battleId = GetRandom() % 3 + 131;
    } else {
        gMapRoomState->battleId = GetRandomBattleId();
    }
}

void MapEnmCheckContact(MapEnmWork* work) {
    if (work->collider.colliding) {
        if ((gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) == 0 && ColliderIsTouchingType(&work->collider, 1)) {
            MapEnmStartBattle(work);
            return;
        }

        if (ColliderIsTouchingType(&work->collider, 6)) {
            work->obj.fieldPosition.x += work->collider.pushX;
            work->obj.fieldPosition.y += work->collider.pushY;
        }
    }
}

s32 MapEnmCheckAttacked(MapEnmWork* work) {
    if (IsHitByMapAttack(&work->obj.fieldPosition, work->radius / 2, work->height / 2)) {
        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        gMapRoomState->flags |= ROOM_FLAG_ENEMY_STRUCK;
        TaskCreate(&work->tasks, &gTaskDescMapSpark, &work->obj);

        if (gGameState.flags & GAME_FLAG_RIKU) {
            m4aSongNumStart(SONG_SND_228);
        } else {
            m4aSongNumStart(SONG_SYS_FIELD_ATT00);
        }

        return 1;
    }

    return 0;
}

void MapEnmSaveToCache(MapEnmWork* work) {
    MapEnmCache* q = ListPoolFirstFree(&gGameState.enemyCachePool);

    if (q != NULL) {
        q->def = work->def;
        q->update = work->update;
        q->pos = work->obj.fieldPosition;
        q->angle = work->obj.angle;
        q->speed = work->obj.speed;
        ListPoolActivate(&q->node, &gGameState.enemyCachePool);
    }
}

void MapEnmRestoreFromCache() {
    MapEnmCache* q;
    MapEnmArgs w;
    const MapEnmDef* d;
    s32 i;

    q = ListPoolFirst(&gGameState.enemyCachePool);

    while (q != NULL) {
        d = q->def;
        w.def = d;
        w.update = q->update;
        w.pos = q->pos;
        w.angle = q->angle;
        w.speed = q->speed;
        TaskCreate(&gFieldState->tasks4, d->desc, &w);
        q = ListPoolNext(&q->node);
    }

    ListPoolInit(&gGameState.enemyCachePool);

    for (i = 0; i < 3; i++) {
        ListPoolAddFree(&gGameState.enemyCache[i].node, &gGameState.enemyCachePool, &gGameState.enemyCache[i]);
    }
}

void MapEnmSpawnRoomSet() {
    MapEnmArgs w;
    s32 i;

    switch (gMapRoomState->roomType) {
    case 3:
        MapEnmSpawnFixed(&w, 3, 3);
        MapEnmSpawnFixed(&w, 2, 2);
        break;
    case 5:
        for (i = 0; i < 3; i++) {
            if (gMapFloorState.world == WORLD_ATLANTICA) {
                MapEnmSpawnFixed(&w, 4, 0);
            } else if (GetRandom() % 2) {
                MapEnmSpawnFixed(&w, 0, 0);
            } else {
                MapEnmSpawnFixed(&w, 1, 0);
            }
        }

        break;
    }
}

void MapEnmInitRoom() {
    MapEnmCache* q;
    MapEnmArgs w;
    const MapEnmDef* d;
    MapFloorRoom* e;
    s32 i;

    sMapEnmCount = 0;
    sMapEnmTileCount = 0;
    sMapEnmSpawnTimer = 46;

    if (gGameState.fieldResume) {
        q = ListPoolFirst(&gGameState.enemyCachePool);

        while (q != NULL) {
            d = q->def;
            w.def = d;
            w.update = q->update;
            w.pos = q->pos;
            w.angle = q->angle;
            w.speed = q->speed;
            TaskCreate(&gFieldState->tasks4, d->desc, &w);
            q = ListPoolNext(&q->node);
        }

        if (gGameState.flags & GAME_FLAG_MAP_ENEMY_BATTLE) {
            gGameState.flags &= ~GAME_FLAG_MAP_ENEMY_BATTLE;

            if ((gGameState.flags & GAME_FLAG_BATTLE_NOT_WON) == 0) {
                e = GetMapFloorRoom(gMapFloorState.room);

                if (e->enemiesLeft != 0) {
                    e->enemiesLeft--;
                }
            }
        }
    } else {
        MapEnmSpawnRoomSet();
    }

    ListPoolInit(&gGameState.enemyCachePool);

    for (i = 0; i < 3; i++) {
        ListPoolAddFree(&gGameState.enemyCache[i].node, &gGameState.enemyCachePool, &gGameState.enemyCache[i]);
    }
}

void MapEnmUpdateSpawner() {
    const u8* t;
    MapFloorRoom* e;
    const MapEnmDef* d;
    MapEnmArgs w;

    t = gMapRoomShapes[gMapRoomState->roomType];
    gFieldState->flags &= ~FIELD_FLAG_ENEMY_FRAME_CHANGED;

    if (sMapEnmSpawnTimer != 0) {
        sMapEnmSpawnTimer--;
        return;
    }

    e = GetMapFloorRoom(gMapFloorState.room);

    if (sMapEnmCount >= t[1]) {
        return;
    }

    if (e->enemiesLeft - sMapEnmCount <= 0) {
        return;
    }

    if (gFieldState->flags & (FIELD_FLAG_FREEZE_ENEMIES | FIELD_FLAG_NO_ENEMY_SPAWN | FIELD_FLAG_ROOM_CREATE)) {
        return;
    }

    if (GetRandom() % 10000 <= 7999) {
        return;
    }

    switch (gMapRoomState->roomType) {
    case 20:
        d = gMapEnmDefs[5];
        break;
    case 21:
        d = gMapEnmDefs[6];
        break;
    default:
        if (gMapFloorState.world == WORLD_ATLANTICA) {
            d = gMapEnmDefs[4];
        } else if (GetRandom() % 3) {
            d = gMapEnmDefs[0];
        } else {
            d = gMapEnmDefs[1];
        }

        break;
    }

    if (sMapEnmTileCount + d->tileCount > 256) {
        return;
    }

    sMapEnmSpawnTimer = 30;
    MapEnmSetupArgs(&w, d);
    TaskCreate(&gFieldState->tasks4, d->desc, &w);
}

void MapEnmInit(MapEnmWork* work, MapEnmArgs* q) {
    FldObj* e = &work->obj;
    const MapEnmDef* d = q->def;

    work->def = d;
    work->update = q->update;
    work->flags = 0;
    work->colliderDelay = 30;
    e->fieldPosition = q->pos;
    e->angle = q->angle;
    e->speed = q->speed;
    e->height = d->height;
    e->unk_34 = 0;
    e->kind = 1;
    work->radius = d->radius;
    work->height = d->height;
    work->timer = 0;
    work->unk_D2 = 0;
    work->targetX = e->fieldPosition.x;
    work->targetY = e->fieldPosition.y;
    work->targetZ = e->fieldPosition.z;
    sMapEnmCount++;
    sMapEnmTileCount += d->tileCount;
    work->tiles = AllocObjTiles(d->tileCount * 32, NULL);
    work->palette = LoadObjPalette(d->palette, 32);
    work->gfx = NULL;
    AnimInit(&work->anim, NULL, NULL);
    TaskPoolInit(&work->tasks, 2);

    if ((d->flags & MAP_ENM_DEF_FLAG_NO_SHADOW) == 0) {
        TaskCreate(&work->tasks, &gTaskDescFldShadow, e);
    }

    if (d->flags & MAP_ENM_DEF_FLAG_GUARD) {
        work->flags |= MAP_ENM_FLAG_PERSISTENT;
        ColliderInit(&work->collider, 11, d->radius, d->height);
    } else {
        ColliderInit(&work->collider, 3, d->radius, d->height);
    }

    ColliderSetPosition(&work->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    ColliderSetDisabled(&work->collider, 1);
    MapEnmApplyRoomFlags(work);
}

void MapEnmDraw(MapEnmWork* work) {
    FldObj* q = &work->obj;
    u16 flags;
    u16 v;
    s32 k;
    s32 x;
    s32 y;
    s32 z;
    s32 t;

    if (work->gfx == NULL) {
        return;
    }

    t = work->flags & MAP_ENM_FLAG_HFLIP;
    flags = SPRITE_PRIORITY(2);

    if (t) {
        flags = SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
    }

    k = q->fieldPosition.y >> 8;
    v = -0x1004 - k * 4;
    q->shadowZ = q->fieldPosition.ground;
    q->shadowPriority = v + 1;
    z = 0;
    x = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    t = flags;
    y = k + (q->fieldPosition.z >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, t, v);
    TaskPoolDraw(&work->tasks);
}

void MapEnmDestroy(MapEnmWork* work) {
    MapEnmCache* q;

    if (gGameState.fieldResume && (work->flags & MAP_ENM_FLAG_REMOVED) == 0 &&
        ((gMapRoomState->flags & ROOM_FLAG_START_BATTLE) == 0 || (work->flags & MAP_ENM_FLAG_PERSISTENT))) {
        q = ListPoolFirstFree(&gGameState.enemyCachePool);

        if (q != NULL) {
            q->def = work->def;
            q->update = work->update;
            q->pos = work->obj.fieldPosition;
            q->angle = work->obj.angle;
            q->speed = work->obj.speed;
            ListPoolActivate(&q->node, &gGameState.enemyCachePool);
        }
    }

    sMapEnmCount--;
    sMapEnmTileCount -= work->def->tileCount;
    ColliderUnregister(&work->collider);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

u8 GetRandomMapGmkIndex(u8 a) {
    u8 r;

    switch (gMapFloorState.world) {
    case WORLD_AGRABAH:
        r = GetRandom() % 12 + 2;
        break;
    case WORLD_ATLANTICA:
        r = GetRandom() % 2;
        break;
    case WORLD_WONDERLAND:
        r = GetRandom() % 3 + 14;
        break;
    case WORLD_MONSTRO:
        r = GetRandom() % 5 + 17;
        break;
    case WORLD_OLYMPUS_COLISEUM:
        r = GetRandom() % 5 + 35;
        break;
    case WORLD_HOLLOW_BASTION:
        r = GetRandom() % 5 + 40;
        break;
    case WORLD_NEVER_LAND:
        r = GetRandom() % 7 + 45;
        break;
    case WORLD_DESTINY_ISLANDS:
        r = GetRandom() % 5 + 52;
        break;
    case WORLD_TRAVERSE_TOWN:
        r = GetRandom() % 2 + 57;
        break;
    case WORLD_CASTLE_OBLIVION:
        r = GetRandom() % 2 + 63;
        break;
    case WORLD_HALLOWEEN_TOWN:
        if (a <= 7) {
            switch (GetRandom() % 5) {
            case 2:
            case 3:
                r = GetRandom() % 3 != 0 ? 31 : 34;
                break;
            case 0:
            case 1:
                r = GetRandom() % 3 != 0 ? 30 : 33;
                break;
            default:
                r = GetRandom() % 3 != 0 ? 29 : 32;
                break;
            }
        } else {
            r = GetRandom() % 7 + 22;
        }

        break;
    default:
        r = GetRandom() % 3 + 59;
        break;
    }

    return r;
}

MapCell* MapCellAtPos(s32 x, s32 y) {
    u16 a = x / 0x2000;
    u16 b = y / 0x1000;
    return MapCellAt(a, b);
}

s32 MapGmkIsAreaSparse(s16 x, s16 y) {
    s32 i;
    u8 n;
    s16 cx;
    s16 cy;

    n = 0;

    for (i = 0; i < sMapGmkCount; i++) {
        cx = (gMapGmkPlacements[i].pos.x >> 8) / 32;
        cy = ((gMapGmkPlacements[i].pos.y + gMapGmkPlacements[i].pos.z) >> 8) / 16;

        if (cx > x - 9 && cx < x + 9 && cy > y - 11 && cy < y + 11) {
            n++;

            if (n > 2) {
                return 0;
            }
        }
    }

    return 1;
}

u8 MapCellIsFreeOfType(s16 x, s16 y, u8 n) {
    MapCell* p = MapCellAt(x, y);

    if (p != NULL && p->lowerZ != 0x100000 && p->type == n && (p->flags & (MAP_CELL_FLAG_STAIRS | MAP_CELL_FLAG_JUMP_PAD | MAP_CELL_FLAG_GMK_RESERVED | MAP_CELL_FLAG_KEEP_CLEAR)) == 0) {
        return 1;
    }

    return 0;
}

s32 MapAreaIsFreeOfType(s16 x, s16 y, u8 w, u8 h, u8 n) {
    s32 i;
    s32 j;

    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            if (!MapCellIsFreeOfType(x + i, y + j, n)) {
                return 0;
            }
        }
    }

    return 1;
}

s32 MapCellHeightExceeds(s16 a, s16 b, u8 c) {
    u16 d;
    MapCell* p = MapCellAt(a, b);
    d = (p->lowerZ - p->upperZ) >> 8;
    return d > (c << 4);
}

void MapReserveArea(s16 x, s16 y, u8 w, u8 h) {
    s32 i;
    s32 j;

    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            MapCellAt(x + i, y + j)->flags |= MAP_CELL_FLAG_GMK_RESERVED;
        }
    }
}

s16 MapRowsToWallBase(s16 x, s16 y) {
    u16 n = gMapRoomState->rows - y;
    s32 i;

    for (i = 0; i < n; i++) {
        MapCell* p = MapCellAt(x, y + i);

        if (p->flags & MAP_CELL_FLAG_GMK_RESERVED) {
            return 0;
        }

        if (p->type == 0 || p->type == 4 || p->type == 2 || p->type == 6) {
            return i;
        }
    }

    return 0;
}

s32 MapWallFaceIsUnreserved(s16 x, s16 y, u16 n) {
    s32 i;
    u16 h;
    s32 j;
    MapCell* q;
    s32 mask;

    h = gMapRoomState->rows - y;

    for (j = 0; j < n; j++) {
        for (i = 0; i < h; i++) {
            q = MapCellAt(x + j, y - i);

            if (q->flags & MAP_CELL_FLAG_GMK_RESERVED) {
                return 0;
            }

            if (q->type < 7 || q->type > 9) {
                break;
            }
        }
    }

    return 1;
}

u8 MapGmkFindFloor2x2(FldPos* p) {
    u16 w = gMapRoomState->cols - 2;
    u16 h = gMapRoomState->bottomRow - gMapRoomState->topRow - 2;
    s16 rx = GetRandom() % w;
    s16 ry = GetRandom() % h;
    s32 i;
    s32 j;

    for (j = 0; j < h; j++) {
        s16 sy = gMapRoomState->topRow + ry;

        for (i = 0; i < w; i++) {
            if ((u8)MapGmkIsAreaSparse(rx, sy) && (u8)MapAreaIsFreeOfType(rx, sy, 2, 2, 0)) {
                MapReserveArea(rx, sy, 2, 2);
                FldPosPlaceAtCell(p, rx, sy, 2, 2);
                return 1;
            }

            rx = (s16)(rx + 1) % w;
        }

        ry = (ry != 0 ? ry : h) - 1;
    }

    return 0;
}

u8 MapGmkFindLeftWallBase2x3(FldPos* p) {
    s16 ry;
    s16 rx;
    s16 sy;
    u16 h;
    u16 w;
    s32 i;
    s32 j;

    w = gMapRoomState->cols - 2;
    h = gMapRoomState->bottomRow - gMapRoomState->topRow - 3;
    rx = GetRandom() % w;
    ry = GetRandom() % h;

    for (j = 0; j < h; j++) {
        sy = gMapRoomState->topRow + ry;

        for (i = 0; i < w; i++) {
            if ((u8)MapGmkIsAreaSparse(rx, sy) && MapCellIsFreeOfType(rx, sy, 8)) {
                s32 y1 = (s16)(sy + 1);

                if (MapCellIsFreeOfType(rx, y1, 4)) {
                    s32 y2 = (s16)(sy + 2);

                    if (MapCellIsFreeOfType(rx, y2, 0)) {
                        s32 x1 = (s16)(rx + 1);

                        if (MapCellIsFreeOfType(x1, sy, 4) && MapCellIsFreeOfType(x1, y1, 0) &&
                            MapCellIsFreeOfType(x1, y2, 0) && (u8)MapCellHeightExceeds(rx, sy, 3)) {
                            MapReserveArea(rx, sy, 2, 3);
                            FldPosPlaceAtCell(p, rx, sy, 2, 3);
                            return 1;
                        }
                    }
                }
            }

            rx = (s16)(rx + 1) % w;
        }

        ry = (ry != 0 ? ry : h) - 1;
    }

    return 0;
}

u8 MapGmkFindLeftWallBase1x4(FldPos* p) {
    s16 x;
    s16 y;
    s16 cy;
    u16 n;
    u16 m;
    s32 i;
    s32 j;

    n = gMapRoomState->cols - 1;
    m = gMapRoomState->bottomRow - gMapRoomState->topRow - 4;
    x = GetRandom() % n;
    y = GetRandom() % m;

    for (i = 0; i < m; i++) {
        cy = gMapRoomState->topRow + y;

        for (j = 0; j < n; j++) {
            if ((u8)MapGmkIsAreaSparse(x, cy)) {
                if (MapCellIsFreeOfType(x, cy, 4)) {
                    if (MapCellIsFreeOfType(x, cy + 1, 0)) {
                        if (MapCellIsFreeOfType(x, cy + 2, 0)) {
                            if (MapCellIsFreeOfType(x, cy + 3, 0)) {
                                if ((u8)MapCellHeightExceeds(x, cy, 3)) {
                                    MapReserveArea(x, cy, 1, 4);
                                    FldPosPlaceAtCell(p, x, cy, 1, 4);
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }

            x++;
            x %= n;
        }

        y = (y != 0 ? y : m) - 1;
    }

    return 0;
}

u8 MapGmkFindRightWallBase2x3(FldPos* p) {
    s16 ry;
    s16 rx;
    s16 sy;
    u16 h;
    u16 w;
    s32 i;
    s32 j;

    w = gMapRoomState->cols - 2;
    h = gMapRoomState->bottomRow - gMapRoomState->topRow - 3;
    rx = GetRandom() % w;
    ry = GetRandom() % h;

    for (j = 0; j < h; j++) {
        sy = gMapRoomState->topRow + ry;

        for (i = 0; i < w; i++) {
            if ((u8)MapGmkIsAreaSparse(rx, sy) && MapCellIsFreeOfType(rx, sy, 6)) {
                s32 y1 = (s16)(sy + 1);

                if (MapCellIsFreeOfType(rx, y1, 0)) {
                    s32 y2 = (s16)(sy + 2);

                    if (MapCellIsFreeOfType(rx, y2, 0)) {
                        s32 x1 = (s16)(rx + 1);

                        if (MapCellIsFreeOfType(x1, sy, 9) && MapCellIsFreeOfType(x1, y1, 6) &&
                            MapCellIsFreeOfType(x1, y2, 0) && (u8)MapCellHeightExceeds(rx, sy, 3)) {
                            MapReserveArea(rx, sy, 2, 3);
                            FldPosPlaceAtCell(p, rx, sy, 2, 3);
                            return 1;
                        }
                    }
                }
            }

            rx = (s16)(rx + 1) % w;
        }

        ry = (ry != 0 ? ry : h) - 1;
    }

    return 0;
}

u8 MapGmkFindLeftWallFace3x3(FldPos* p) {
    s16 ry;
    s16 rx;
    s16 sy;
    u16 h;
    u16 w;
    s32 i;
    s32 j;

    w = gMapRoomState->cols - 3;
    h = gMapRoomState->bottomRow - gMapRoomState->topRow - 3;
    rx = GetRandom() % w;
    ry = GetRandom() % h;

    for (j = 0; j < h; j++) {
        sy = gMapRoomState->topRow + ry;

        for (i = 0; i < w; i++) {
            if ((u8)MapGmkIsAreaSparse(rx, sy) && (u8)MapAreaIsFreeOfType(rx, sy, 3, 3, 8)) {
                u16 a;
                u16 b;

                if (!(u8)MapWallFaceIsUnreserved(rx, sy, 3)) {
                    continue;
                }

                a = MapRowsToWallBase(rx, sy + 2);
                b = MapRowsToWallBase(rx + 2, sy);

                if (a == b && a > 8) {
                    MapReserveArea(rx, sy, 3, 3);
                    FldPosPlaceAtCell(p, rx, a + sy, 3, 3);
                    p->z -= a << 12;
                    return 1;
                }
            }

            rx = (s16)(rx + 1) % w;
        }

        ry = (ry != 0 ? ry : h) - 1;
    }

    return 0;
}

u8 MapGmkFindRightWallFace3x3(FldPos* p) {
    s16 ry;
    s16 rx;
    s16 sy;
    u16 h;
    u16 w;
    s32 i;
    s32 j;

    w = gMapRoomState->cols - 3;
    h = gMapRoomState->bottomRow - gMapRoomState->topRow - 3;
    rx = GetRandom() % w;
    ry = GetRandom() % h;

    for (j = 0; j < h; j++) {
        sy = gMapRoomState->topRow + ry;

        for (i = 0; i < w; i++) {
            if ((u8)MapGmkIsAreaSparse(rx, sy) && (u8)MapAreaIsFreeOfType(rx, sy, 3, 3, 9)) {
                u16 a;
                u16 b;

                if (!(u8)MapWallFaceIsUnreserved(rx, sy, 3)) {
                    continue;
                }

                a = MapRowsToWallBase(rx, sy);
                b = MapRowsToWallBase(rx + 2, sy + 2);

                if (a == b && a > 8) {
                    MapReserveArea(rx, sy, 3, 3);
                    FldPosPlaceAtCell(p, rx, a + sy, 3, 3);
                    p->z -= a << 12;
                    return 1;
                }
            }

            rx = (s16)(rx + 1) % w;
        }

        ry = (ry != 0 ? ry : h) - 1;
    }

    return 0;
}

u8 MapGmkFindLeftWallTop2x2(FldPos* p) {
    s16 ry;
    s16 rx;
    s16 sy;
    u16 h;
    u16 w;
    s32 i;
    s32 j;

    w = gMapRoomState->cols - 2;
    h = gMapRoomState->bottomRow - gMapRoomState->topRow - 2;
    rx = GetRandom() % w;
    ry = GetRandom() % h;

    for (j = 0; j < h; j++) {
        sy = gMapRoomState->topRow + ry;

        for (i = 0; i < w; i++) {
            if ((u8)MapGmkIsAreaSparse(rx, sy) && MapCellIsFreeOfType(rx, sy, 0)) {
                if (MapCellIsFreeOfType(rx, sy + 1, 3)) {
                    if (MapCellIsFreeOfType(rx + 1, sy, 3) &&
                        MapCellIsFreeOfType(rx + 1, sy + 1, 8)) {
                        u16 a = MapRowsToWallBase(rx, sy + 1);
                        u16 b = MapRowsToWallBase(rx + 1, sy);

                        if (a == b && a > 8) {
                            MapReserveArea(rx, sy, 2, 2);
                            FldPosPlaceAtCell(p, rx, a + sy, 2, 2);
                            p->z -= a << 12;
                            return 1;
                        }
                    }
                }
            }

            rx = (s16)(rx + 1) % w;
        }

        ry = (ry != 0 ? ry : h) - 1;
    }

    return 0;
}

u8 MapGmkFindBackWallTop1x2(FldPos* p) {
    s16 x;
    s16 y;
    s16 cy;
    u16 n;
    u16 m;
    u16 h;
    s32 i;
    s32 j;

    n = gMapRoomState->cols - 1;
    m = gMapRoomState->bottomRow - gMapRoomState->topRow - 2;
    x = GetRandom() % n;
    y = GetRandom() % m;

    for (i = 0; i < m; i++) {
        cy = gMapRoomState->topRow + y;

        for (j = 0; j < n; j++) {
            if ((u8)MapGmkIsAreaSparse(x, cy)) {
                if (MapCellIsFreeOfType(x, cy, 1)) {
                    if (MapCellIsFreeOfType(x, cy + 1, 7)) {
                        h = MapRowsToWallBase(x, cy);

                        if (h > 8) {
                            MapReserveArea(x, cy, 1, 2);
                            FldPosPlaceAtCell(p, x, h + cy, 1, 2);
                            p->z -= h << 12;
                            return 1;
                        }
                    }
                }
            }

            x++;
            x %= n;
        }

        y = (y != 0 ? y : m) - 1;
    }

    return 0;
}

u8 MapGmkFindRightWallTop2x2(FldPos* p) {
    s16 ry;
    s16 rx;
    s16 sy;
    u16 h;
    u16 w;
    s32 i;
    s32 j;

    w = gMapRoomState->cols - 2;
    h = gMapRoomState->bottomRow - gMapRoomState->topRow - 2;
    rx = GetRandom() % w;
    ry = GetRandom() % h;

    for (j = 0; j < h; j++) {
        sy = gMapRoomState->topRow + ry;

        for (i = 0; i < w; i++) {
            if ((u8)MapGmkIsAreaSparse(rx, sy) && MapCellIsFreeOfType(rx, sy, 5)) {
                s32 y1 = (s16)(sy + 1);

                if (MapCellIsFreeOfType(rx, y1, 9)) {
                    if (MapCellIsFreeOfType(rx + 1, sy, 0) &&
                        MapCellIsFreeOfType(rx + 1, y1, 5)) {
                        u16 a = MapRowsToWallBase(rx, sy);
                        u16 b = MapRowsToWallBase(rx + 1, y1);

                        if (a == b && a > 8) {
                            MapReserveArea(rx, sy, 2, 2);
                            FldPosPlaceAtCell(p, rx, a + sy, 2, 2);
                            p->z -= a << 12;
                            return 1;
                        }
                    }
                }
            }

            rx = (s16)(rx + 1) % w;
        }

        ry = (ry != 0 ? ry : h) - 1;
    }

    return 0;
}

u8 MapGmkFindBackWallBase2x3(FldPos* p) {
    s16 ry;
    s16 rx;
    s16 sy;
    u16 h;
    u16 w;
    s32 i;
    s32 j;

    w = gMapRoomState->cols - 2;
    h = gMapRoomState->bottomRow - gMapRoomState->topRow - 3;
    rx = GetRandom() % w;
    ry = GetRandom() % h;

    for (j = 0; j < h; j++) {
        sy = gMapRoomState->topRow + ry;

        for (i = 0; i < w; i++) {
            if ((u8)MapGmkIsAreaSparse(rx, sy) && MapCellIsFreeOfType(rx, sy, 2)) {
                s32 y1 = (s16)(sy + 1);

                if (MapCellIsFreeOfType(rx, y1, 0)) {
                    s32 y2 = (s16)(sy + 2);

                    if (MapCellIsFreeOfType(rx, y2, 0)) {
                        s32 x1 = (s16)(rx + 1);

                        if (MapCellIsFreeOfType(x1, sy, 2) && MapCellIsFreeOfType(x1, y1, 0) &&
                            MapCellIsFreeOfType(x1, y2, 0) && (u8)MapCellHeightExceeds(rx, sy, 3)) {
                            MapReserveArea(rx, sy, 2, 3);
                            FldPosPlaceAtCell(p, rx, sy, 2, 3);
                            return 1;
                        }
                    }
                }
            }

            rx = (s16)(rx + 1) % w;
        }

        ry = (ry != 0 ? ry : h) - 1;
    }

    return 0;
}

u8 MapGmkFindFloor3x3(FldPos* p) {
    u16 w = gMapRoomState->cols - 3;
    u16 h = gMapRoomState->bottomRow - gMapRoomState->topRow - 3;
    s16 rx = GetRandom() % w;
    s16 ry = GetRandom() % h;
    s32 i;
    s32 j;

    for (j = 0; j < h; j++) {
        s16 sy = gMapRoomState->topRow + ry;

        for (i = 0; i < w; i++) {
            if ((u8)MapGmkIsAreaSparse(rx, sy) && (u8)MapAreaIsFreeOfType(rx, sy, 3, 3, 0)) {
                MapReserveArea(rx, sy, 3, 3);
                FldPosPlaceAtCell(p, rx, sy, 3, 3);
                return 1;
            }

            rx = (s16)(rx + 1) % w;
        }

        ry = (ry != 0 ? ry : h) - 1;
    }

    return 0;
}

u8 MapGmkFindFloor4x4(FldPos* p) {
    u16 w = gMapRoomState->cols - 4;
    u16 h = gMapRoomState->bottomRow - gMapRoomState->topRow - 4;
    s16 rx = GetRandom() % w;
    s16 ry = GetRandom() % h;
    s32 i;
    s32 j;

    for (j = 0; j < h; j++) {
        s16 sy = gMapRoomState->topRow + ry;

        for (i = 0; i < w; i++) {
            if ((u8)MapGmkIsAreaSparse(rx, sy) && (u8)MapAreaIsFreeOfType(rx, sy, 4, 4, 0)) {
                MapReserveArea(rx, sy, 4, 4);
                FldPosPlaceAtCell(p, rx, sy, 4, 4);
                return 1;
            }

            rx = (s16)(rx + 1) % w;
        }

        ry = (ry != 0 ? ry : h) - 1;
    }

    return 0;
}

u8 MapGmkFindFloor5x5(FldPos* p) {
    u16 w = gMapRoomState->cols - 5;
    u16 h = gMapRoomState->bottomRow - gMapRoomState->topRow - 5;
    s16 rx = GetRandom() % w;
    s16 ry = GetRandom() % h;
    s32 i;
    s32 j;

    for (j = 0; j < h; j++) {
        s16 sy = gMapRoomState->topRow + ry;

        for (i = 0; i < w; i++) {
            if ((u8)MapGmkIsAreaSparse(rx, sy) && (u8)MapAreaIsFreeOfType(rx, sy, 5, 5, 0)) {
                MapReserveArea(rx, sy, 5, 5);
                FldPosPlaceAtCell(p, rx, sy, 5, 5);
                return 1;
            }

            rx = (s16)(rx + 1) % w;
        }

        ry = (ry != 0 ? ry : h) - 1;
    }

    return 0;
}

u8 MapGmkFindBaseFloor2x2(FldPos* p) {
    MapPlatform* e = GetMapPlatform(0);
    u16 w = e->right - e->left - 2;
    u16 h = gMapRoomState->bottomRow - gMapRoomState->topRow - 2;
    s16 rx = GetRandom() % w;
    s16 ry = GetRandom() % h;
    s32 i;
    s32 j;

    for (j = 0; j < h; j++) {
        s16 sy = gMapRoomState->topRow + ry;

        for (i = 0; i < w; i++) {
            s32 sx = (s16)(e->left + rx);

            if ((u8)MapAreaIsFreeOfType(sx, sy, 2, 2, 0) && e->z == MapCellAt(sx, sy)->lowerZ) {
                MapReserveArea(sx, sy, 2, 2);
                FldPosPlaceAtCell(p, sx, sy, 2, 2);
                return 1;
            }

            rx = (s16)(rx + 1) % w;
        }

        ry = (s16)(ry + 1) % h;
    }

    return 0;
}

u8 MapGmkFindSpot(FldPos* a, u8 b) {
    return gMapGmkSpotFuncs[b](a);
}

s32 MapGmkIsPaletteUnused(void* a) {
    s32 i;

    for (i = 0; i < sMapGmkCount; i++) {
        if (gMapGmkPlacements[i].def->palette == a) {
            return 0;
        }
    }

    return 1;
}

s32 MapGmkNeedsTiles(u8 flag, const void* a) {
    s32 i;

    if (flag) {
        return 1;
    }

    for (i = 0; i < sMapGmkCount; i++) {
        if (gMapGmkPlacements[i].def->tiles == a) {
            return 0;
        }
    }

    return 1;
}

void MapGmkReserveJump() {
    s32 i;

    for (i = 0; i < 12; i++) {
        MapPlatform* p = GetMapPlatform(i);

        if (!p->hasStairs && p->spotLowerZ != 0x100000) {
            sMapGmkTileCount += 0x4C;
            sMapGmkPaletteCount++;
            break;
        }
    }
}

void MapGmkPlaceGmk01() {
    FldPos w;
    MapFloorRoom* e;
    const MapGmkDef* q;
    s32 i;

    e = GetMapFloorRoom(gMapFloorState.room);

    if (gMapRoomState->roomType == 10) {
        u8* n;

        q = &gMapGmk01Def;
        n = &sMapGmkCount;

        for (i = 1; i >= 0; i--) {
            s32 size;

            MapGmkFindSpot(&w, q->spotFinder);

            if (e->flags & FLOOR_ROOM_FLAG_CHEST_OPENED) {
                gMapGmkPlacements[*n].flags = (GMK_FLAG_USED | GMK_FLAG_HAS_ENEMY);
            } else {
                gMapGmkPlacements[*n].flags = GMK_FLAG_HAS_ENEMY;
            }

            gMapGmkPlacements[*n].def = q;
            gMapGmkPlacements[*n].pos = w;
            sMapGmkTileCount += (size = q->tilesSize) / 32;
            sMapGmkPaletteCount++;
            (*n)++;
        }
    }

    if (gMapRoomState->roomType == 3 || gMapRoomState->roomType == 9 || gMapRoomState->roomType == 10 ||
        gMapRoomState->roomType == 22) {
        MapCell* p;
        u16 v;

        q = &gMapGmk01Def;
        MapGmkFindSpot(&w, q->spotFinder);
        v = e->flags & FLOOR_ROOM_FLAG_CHEST_OPENED;

        if (v != 0) {
            gMapGmkPlacements[sMapGmkCount].flags = GMK_FLAG_USED;
        } else {
            gMapGmkPlacements[sMapGmkCount].flags = 0;
        }

        gMapGmkPlacements[sMapGmkCount].def = q;
        gMapGmkPlacements[sMapGmkCount].pos = w;
        sMapGmkTileCount += q->tilesSize >> 5;
        sMapGmkPaletteCount++;
        sMapGmkCount++;
        p = MapCellAtPos(w.x, w.y + w.z);
        p->flags |= MAP_CELL_FLAG_CHEST;
    }
}

void MapGmkPlaceGmk04() {
    FldPos w;

    if (gMapRoomState->roomType == 6 || gMapRoomState->roomType == 0x17) {
        MapGmkFindSpot(&w, gMapGmk04Def.spotFinder);
        gMapGmkPlacements[sMapGmkCount].flags = 0;
        gMapGmkPlacements[sMapGmkCount].def = &gMapGmk04Def;
        gMapGmkPlacements[sMapGmkCount].pos = w;
        sMapGmkTileCount += gMapGmk04Def.tilesSize >> 5;
        sMapGmkPaletteCount++;
        sMapGmkCount++;
    }
}

void MapGmkPlaceMoogle() {
    FldPos w;

    if (gMapRoomState->roomType == 11) {
        MapGmkFindSpot(&w, gMapGmk05Def.spotFinder);
        gMapGmkPlacements[sMapGmkCount].flags = 0;
        gMapGmkPlacements[sMapGmkCount].def = &gMapGmk05Def;
        gMapGmkPlacements[sMapGmkCount].pos = w;
        sMapGmkTileCount += gMapGmk05Def.tilesSize >> 5;
        sMapGmkPaletteCount++;
        sMapGmkCount++;
    }
}

void MapGmkPlaceWorldGimmicks() {
    FldPos w;
    const MapGmkDef* t;
    s32 i;
    s32 f;

    if (gMapRoomState->roomType == 6 || gMapRoomState->roomType == 9 || gMapRoomState->roomType == 11 ||
        gMapRoomState->roomType == 22 || gMapRoomState->roomType == 23) {
        return;
    }

    for (i = sMapGmkCount; i <= 15; i++) {
        switch (gMapFloorState.world) {
        case WORLD_TRAVERSE_TOWN:
            t = &gWorldMapGmkDefs[0];
            break;
        case WORLD_WONDERLAND:
            t = &gWorldMapGmkDefs[1];
            break;
        case WORLD_ATLANTICA:
            t = &gWorldMapGmkDefs[2];
            break;
        case WORLD_HALLOWEEN_TOWN:
            t = &gWorldMapGmkDefs[3];
            break;
        case WORLD_HOLLOW_BASTION:
            t = GetRandom() % 2 ? &gWorldMapGmkDefs[4] : &gWorldMapGmkDefs[5];
            break;
        case WORLD_CASTLE_OBLIVION:
            t = &gWorldMapGmkDefs[6];
            break;
        default:
            t = &gMapGmkBarrelDef;
            break;
        }

        if (sMapGmkTileCount + t->tilesSize / 32 > 0x200) {
            return;
        }

        f = (u8)MapGmkIsPaletteUnused(t->palette);

        if (f && sMapGmkPaletteCount > 5) {
            return;
        }

        if (MapGmkFindSpot(&w, t->spotFinder) == 0) {
            return;
        }

        gMapGmkPlacements[sMapGmkCount].flags = 0;
        gMapGmkPlacements[sMapGmkCount].def = t;
        gMapGmkPlacements[sMapGmkCount].pos = w;
        sMapGmkTileCount += t->tilesSize >> 5;
        sMapGmkCount++;

        if (f) {
            sMapGmkPaletteCount++;
        }
    }
}

void MapGmkPlaceRandomGimmicks() {
    s32 i;

    for (i = sMapGmkCount; i < 16; i++) {
        FldPos w;
        const MapGmkDef* e = &gMapGmkDefs[GetRandomMapGmkIndex(i)];
        u8 f = MapGmkNeedsTiles(e->ownTiles, e->tiles);
        u8 g;

        if (f) {
            if ((e->tilesSize >> 5) + sMapGmkTileCount > 512) {
                continue;
            }
        }

        g = MapGmkIsPaletteUnused(e->palette);

        if (g) {
            if (sMapGmkPaletteCount > 5) {
                continue;
            }
        }

        if (MapGmkFindSpot(&w, e->spotFinder) == 0) {
            continue;
        }

        gMapGmkPlacements[sMapGmkCount].flags = 0;
        gMapGmkPlacements[sMapGmkCount].def = e;
        gMapGmkPlacements[sMapGmkCount].pos = w;
        sMapGmkCount++;

        if (f) {
            sMapGmkTileCount += e->tilesSize >> 5;
        }

        if (g) {
            sMapGmkPaletteCount++;
        }
    }
}

u8 FldObjIsOutOfView(FldObj* p) {
    s32 lim = gFieldState->actor.fieldPosition.y + gFieldState->actor.fieldPosition.z + 0x4000 + (p->height << 8);

    if (p->fieldPosition.x < gFieldState->x || p->fieldPosition.x > gFieldState->x + 0xF000 ||
        p->fieldPosition.y + p->fieldPosition.z < gFieldState->y || p->fieldPosition.y + p->fieldPosition.z > lim) {
        return 1;
    }

    return 0;
}

u16 MapGmkGetFreeTiles() {
    return 512 - sMapGmkTileCount;
}

void CreateRandomMapPrizes(s32 a, s32 b, s32 c) {
    u16 r;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        r = GetRandom() % 10000;

        if (r < 2500) {
            CreateMapPrizeTasks(0, 2, a, b, c);
        } else if (r < 6500) {
            CreateMapPrizeTasks(0, 5, a, b, c);
        } else if (r < 9000) {
            CreateMapPrizeTasks(1, 3, a, b, c);
        } else {
            CreateMapPrizeTasks(1, 5, a, b, c);
        }
    } else {
        r = GetRandom() % 10000;

        if (r < 2000) {
            CreateMapPrizeTasks(0, 2, a, b, c);
        } else if (r < 4000) {
            CreateMapPrizeTasks(0, 5, a, b, c);
        } else if (r < 6000) {
            CreateMapPrizeTasks(1, 3, a, b, c);
        } else if (r < 6500) {
            CreateMapPrizeTasks(1, 5, a, b, c);
        } else if (r < 8000) {
            CreateMapPrizeTasks(2, 5, a, b, c);
        } else {
            CreateMapPrizeTasks(3, 5, a, b, c);
        }
    }
}

void DropMapGmkPrize(FldPos* p) {
    u16 r = GetRandom() % 10000;

    if (r <= 0x5DB) {
        if (TryCreateRandomPrzCard(0, p->x, p->y, p->z) != 1) {
            CreateRandomMapPrizes(p->x, p->y, p->z);
        }
    } else if (r <= 0x1D4B) {
        CreateRandomMapPrizes(p->x, p->y, p->z);
    }
}

void MapGmkInitRoom() {
    if (!gGameState.fieldResume) {
        gMapGmkPlacements = EwramAlloc(sizeof(MapGmkPlacement) * 16);
        sMapGmkCount = 0;
        sMapGmkPaletteCount = 0;
        sMapGmkTileCount = 0;
        MapGmkReserveJump();
        MapGmkPlaceGmk01();
        MapGmkPlaceGmk04();
        MapGmkPlaceMoogle();
        MapGmkPlaceRandomGimmicks();
        MapGmkPlaceWorldGimmicks();
    }

    MapGmkCreateTasks();
}

void MapGmkCreateTasks() {
    s32 i;
    MapPlatform* p;
    const MapGmkDef* d;

    for (i = 0; i < 12; i++) {
        p = GetMapPlatform(i);

        if (!p->hasStairs && p->spotLowerZ != 0x100000) {
            TaskCreate(&gFieldState->tasks, &gTaskDescMapGmkJump, p);
        }
    }

    for (i = 0; i < sMapGmkCount; i++) {
        d = gMapGmkPlacements[i].def;

        if ((gMapGmkPlacements[i].flags & GMK_FLAG_DESTROYED) == 0) {
            TaskCreate(&gFieldState->tasks, d->desc, &gMapGmkPlacements[i]);
        }
    }

    TaskCreate(&gFieldState->tasks, &gTaskDescMapGmkDmy, NULL);
}

void MapGmkFree() {
    if (!gGameState.fieldResume) {
        EwramFree(gMapGmkPlacements);
    }
}

const u8* GetCellMaskBlock(void* a, u16 b, u16 c) {
    u8* p = a;

    return gCellMasks[p[(u8)(b >> 3) + (u8)(c >> 3) * 4]];
}

void* GetCellMaskTable(u8 a) {
    s32 i;

    switch (a) {
    case 1:
    case 2:
    case 7:
    case 8:
    case 9:
        i = 1;
        break;
    case 3:
        i = 2;
        break;
    case 5:
        i = 3;
        break;
    case 4:
        i = 4;
        break;
    case 6:
        i = 5;
        break;
    default:
        i = 0;
        break;
    }

    return &gCellMasks[i + 10];
}

u8 MapCellMaskBitAt(MapCell* p, s32 x, s32 y) {
    u16 cx;
    u16 cy;
    u8 bx;
    u8 by;
    const u8* t;

    if (p == NULL) {
        return 1;
    }

    cx = (x >> 8) % 32;
    cy = (y >> 8) % 16;
    t = GetCellMaskBlock(p->maskTable, cx, cy);
    bx = cx & 7;
    by = cy & 7;
    return (t[by] >> (7 - bx)) & 1;
}

void MapPlaceLayer1DecorPiece(s16 x, s16 y, const u8* p, u16* base) {
    s32 i;
    s32 j;
    s32 off;
    u8 v;
    MapCell* q;

    v = GetRandom() % 100;

    while (v >= p[0]) {
        p += 8;
    }

    for (j = 0; j < p[3]; j++) {
        for (i = 0; i < p[4]; i++) {
            switch (p[5]) {
            case 1:
                q = MapCellAt(x + j, y + i + (p[3] - 1 - j));
                break;
            case 2:
                q = MapCellAt(x + j, y + i + j);
                break;
            case 0:
            default:
                q = MapCellAt(x + j, y + i);
                break;
            }

            off = (p[2] + i) * 64 + (p[1] + j) * 4;
            // @bug q is NULL where the pattern reaches past the room edge (NULL write).
            q->bg2Piece = 50;
            q->bg2Map = base + off;
        }
    }
}

u8 MapPatternFits(s16 x, s16 y, const MapCellPattern* p) {
    MapCell* q;
    s32 v;

    while (p->bg3Piece != 0xFF) {
        // @bug MapCellAt returns NULL past the room edge (NULL read).
        q = MapCellAt(x + p->dx, y + p->dy);

        if (q->lowerZ == 0x100000) {
            return 0;
        }

        if (p->bg3Piece != 7 && q->bg3Piece != p->bg3Piece) {
            return 0;
        }

        if (q->bg2Piece != p->bg2Piece) {
            return 0;
        }

        v = 0x520;

        if ((q->flags & v) != 0) {
            return 0;
        }

        v = q->flags & (MAP_CELL_FLAG_EDGE_LEFT | MAP_CELL_FLAG_EDGE_RIGHT);
        v = v & ~p->edgeIgnoreMask;

        if (v != p->edgeFlags) {
            return 0;
        }

        p++;
    }

    return 1;
}

void MapApplyLayer1DecorRule(MapDecorRule* p) {
    u16 w = gMapRoomState->cols - p->width + 1;
    u16 h = gMapRoomState->bottomRow - gMapRoomState->topRow + 7;
    s16 y0 = gMapRoomState->topRow - 7;
    s32 i;

    for (i = 0; i < h; i++) {
        s16 y = y0 + i;
        s16 j;

        for (j = 0; j < w; j++) {
            if (MapPatternFits(j, y, (const MapCellPattern*)p->pattern)) {
                if (GetRandom() % 100 < p->chance) {
                    MapPlaceLayer1DecorPiece(j, y, p->pieces, p->tilemap);
                }
            }
        }
    }
}

void MapApplyLayer1DecorRules(MapDecorRule* p) {
    if (p != NULL) {
        while (p->pattern != NULL) {
            MapApplyLayer1DecorRule(p);
            p++;
        }
    }
}

void MapPlaceLayer2DecorPiece(s16 x, s16 y, const u8* p, u16* base) {
    s32 i;
    s32 j;
    s32 off;
    u8 v;
    MapCell* q;

    v = GetRandom() % 100;

    while (v >= p[0]) {
        p += 8;
    }

    for (j = 0; j < p[3]; j++) {
        for (i = 0; i < p[4]; i++) {
            q = MapCellAt(x + j, y + i);
            off = (p[2] + i) * 64 + (p[1] + j) * 4;
            // @bug q is NULL where the pattern reaches past the room edge (NULL write).
            q->bg1Piece = 38;
            q->bg1Map = base + off;
        }
    }
}

u8 MapDecorCheckFits(s16 x, s16 y, const u8* p) {
    while (p[0] != 0xFF) {
        if (MapCellAt(p[0] + x, p[1] + y)->bg1Piece != p[2]) {
            return 0;
        }

        p += 4;
    }

    return 1;
}

void MapApplyLayer2DecorRule(MapDecorRule* p) {
    s16 i;
    s16 j;
    u16 w;
    u16 h;

    w = gMapRoomState->cols - p->width + 1;
    h = gMapRoomState->rows - p->height + 1;

    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            if (MapDecorCheckFits(i, j, p->pattern)) {
                if (GetRandom() % 100 < p->chance) {
                    MapPlaceLayer2DecorPiece(i, j, p->pieces, p->tilemap);
                }
            }
        }
    }
}

void MapApplyLayer2DecorRules(MapDecorRule* p) {
    if (p != NULL) {
        while (p->pattern != NULL) {
            MapApplyLayer2DecorRule(p);
            p++;
        }
    }
}

void MapApplyRoomDecor() {
    if (!gGameState.fieldResume) {
        MapRoomDef* p = gMapRoomDefs[gMapFloorState.world];

        MapApplyLayer1DecorRules(p->layer1DecorRules);
        MapApplyLayer2DecorRules(p->layer2DecorRules);
    }
}

void MapAnmSetupSlot(MapAnmSlot* p, const MapAnmEntry* q) {
    p->tiles = q->tiles;
    p->frameSize = q->frameSize;
    p->dest += q->tileOffset << 5;
    p->timer = 0;
    p->script = q->script;
    p->scriptPos = q->script;
}

void MapAnmStepScript(MapAnmSlot* p) {
    s16* q;
    u8 (*f)(MapAnmSlot*);

    if (p->script == NULL) {
        return;
    }

    do {
        q = p->scriptPos;

        if (*q & 0x8000) {
            f = gMapAnmCmds[*(u8*)q];
        } else {
            f = MapAnmCmdFrame;
        }
    } while (f(p));
}

void MapAnmFlushSlot(MapAnmSlot* p) {
    if (p->pending != NULL) {
        RequestDma3Copy(p->pending, p->dest, p->frameSize);
        p->pending = NULL;
    }
}

void MapAnmUpdateSlot(MapAnmSlot* p) {
    MapAnmStepScript(p);
    MapAnmFlushSlot(p);
}

void MapAnmResetSlot(MapAnmSlot* p) {
    p->tiles = NULL;
    p->dest = (u8*)GetBgCharBase(2) + 0x7800;
    p->pending = NULL;
    p->timer = 0;
    p->script = NULL;
    p->scriptPos = NULL;
}

u8 MapAnmCmdEnd(MapAnmSlot* p) {
    p->script = NULL;
    p->scriptPos = NULL;
    return 0;
}

u8 MapAnmCmdFrame(MapAnmSlot* p) {
    MapAnmSlot* w = p;
    s16* q;
    s16 n;

    if (p->timer == 0) {
        p->pending = (u8*)p->tiles + p->frameSize * p->scriptPos[1];
    }

    q = w->scriptPos;
    n = *(u16*)q & 0x7FFF;

    if (n != 0) {
        w->timer++;

        if (w->timer >= n) {
            w->timer = 0;
            w->scriptPos = q + 2;
        }
    }

    return 0;
}

u8 MapAnmCmdLoop(MapAnmSlot* p) {
    p->scriptPos = p->script;
    return 1;
}

u8 IsEventDoor(u8 a, u8 b) {
    MapEventDoor* p;

    if ((s32)gMapRoomState->flags < 0) {
        return 0;
    }

    p = GetMapEventDoor(0);

    while (p->kind != 5) {
        if (p->keyList != 0xFF && p->room == a && p->side == b) {
            return 1;
        }

        p++;
    }

    return 0;
}

u8 SelectEventDoor(u8 a, u8 b) {
    MapEventDoor* p;
    u8 i;

    if ((s32)gMapRoomState->flags < 0) {
        return 0;
    }

    i = 0;
    p = GetMapEventDoor(0);

    while (p->kind != 5) {
        if (p->keyList != 0xFF && p->room == a && p->side == b) {
            sEventKeyList = &gEventKeyLists[p->keyList];
            sEventKeyProgress = &gMapFloorState.eventKeyProgress[i];
            return 1;
        }

        i++;
        p++;
    }

    return 0;
}

u8 CountRemainingEventKeys() {
    return sEventKeyList->count - sEventKeyProgress->paid;
}

EventKey* GetEventKey(u8 a) {
    EventKey* p = &sEventKeyList->keys[sEventKeyProgress->paid];
    EventKey* q = &p[a];

    sEventKey = *q;

    if (a == 0 && q->rule == 4 && sEventKeyProgress->remaining != 0) {
        sEventKey.value = sEventKeyProgress->remaining;
    }

    return &sEventKey;
}

u8 DoorAcceptsMapCard(MapCardAttributes* p) {
    EventKey* q;
    u8 n;

    if (!IsEventDoor(gMapRoomState->doorRoom, gMapRoomState->doorSide)) {
        if (p->kind > 21) {
            return 0;
        }

        n = GetMapRoomCardValue(gMapFloorState.room);

        if (p->value == 0) {
            return 1;
        }

        return p->value > n;
    }

    q = GetEventKey(0);

    if (q->kind != 0xFF) {
        if (q->kind != p->kind) {
            return 0;
        }
    } else if (p->kind > 21) {
        return 0;
    }

    if (q->color != 0 && q->color != p->color) {
        return 0;
    }

    switch (q->rule) {
    case 1:
        return p->value >= q->value;
    case 2:
        return p->value <= q->value;
    case 3:
        return p->value == q->value;
    case 4:
        return p->value != 0;
    }

    return 1;
}

s32 PayEventKey(MapCardAttributes* p) {
    if (GetEventKey(0)->rule == 4) {
        if (sEventKey.value > p->value) {
            sEventKey.value -= p->value;
            sEventKeyProgress->remaining = sEventKey.value;
            return 0;
        }

        sEventKeyProgress->remaining = 0;
    }

    sEventKeyProgress->paid++;
    return 1;
}

const PrizeEntry* PickRandomPrzCard(u8 a) {
    u16 v = GetRandom() % 10000;
    PrzCardChance** t = gWorldPrzCardChances;
    PrzCardChance* p = t[gGameState.world];

    while (p->cardIndex != 41) {
        const PrizeEntry* q = &gPrzCardKinds[p->cardIndex];
        u16 n = a != 0 ? p->weight2 : p->weight;

        if (v < n) {
            if (IsCardKindObtained(q->unk_00[0])) {
                return q;
            }

            if (p->cardIndex <= 16) {
                return &gPrzCardKinds[0];
            }

            if (p->cardIndex <= 30) {
                return &gPrzCardKinds[20];
            }

            return &gPrzCardKinds[31];
        }

        v -= n;
        p++;
    }

    return NULL;
}

u8 RollCardValue() {
    u16 acc = 0;
    u16 r = GetRandom() % 10000;
    s32 i;
    const u16* p = gCardValueWeights;

    for (i = 0; i < 10; i++) {
        acc += p[i];

        if (r < acc) {
            return i;
        }
    }

    return 0;
}

s32 CreateMapPrzCardTask(const PrizeEntry* a, u8 b, s32 c, s32 d, s32 e) {
    MapPrizeArgs w;

    w.worldPrize = b;
    w.x = c;
    w.y = d;
    w.z = e;
    w.id = a->unk_02;

    if (w.id <= 0x1B8) {
        w.id += RollCardValue();
    }

    if (CountCardsById(w.id) <= 0x62) {
        TaskCreate(&gFieldState->tasks5, &gTaskDescMapPrzCard, &w);
        return 1;
    }

    return 0;
}

u8 TryCreateRandomPrzCard(u8 a, s32 b, s32 c, s32 d) {
    const PrizeEntry* q;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        return 0;
    }

    if (IsCardCollectionFull()) {
        return 0;
    }

    if (gMapRoomState->flags & ROOM_FLAG_NO_RANDOM_PRIZE) {
        return 0;
    }

    if (gMapRoomState->flags & ROOM_FLAG_PRIZE_CARD_ACTIVE) {
        return 0;
    }

    if (GetMapFloorRoom(gMapFloorState.room)->przCardsLeft == 0) {
        return 0;
    }

    q = PickRandomPrzCard(a);

    if (q == NULL) {
        return 0;
    }

    return CreateMapPrzCardTask(q, 0, b, c, d);
}

void CreateMapPrizeTasks(u8 a, u8 b, s32 c, s32 d, s32 e) {
    MapPrizeArgs w;
    s32 i;

    w.x = c;
    w.y = d;
    w.z = e;
    w.id = a;

    for (i = 0; i < b; i++) {
        TaskCreate(&gFieldState->tasks3, &gTaskDescMapPrize, &w);
    }
}

void CreateWorldPrize(s32 x, s32 y, s32 z) {
    PrizeEntry* p = gWorldPrizeLists[gGameState.world];
    const PrizeEntry* e;

    for (; p->unk_00[0] != 4; p++) {
        switch (p->unk_00[0]) {
        case 0:
            if (gMapRoomState->roomType == 22) {
                break;
            }

            e = &gPrzCardKinds[p->unk_00[1]];

            if (IsCardKindObtained(e->unk_00[0]) == 1) {
                break;
            }

            SetCardKindObtained(e->unk_00[0]);
            CreateMapPrzCardTask(e, 1, x, y, z);
            return;
        case 1:
            if (gMapRoomState->roomType == 22) {
                break;
            }

            e = &gPrzStocks[p->unk_00[1]];

            if (IsStockLearned(e->unk_00[0]) == 1) {
                break;
            }

            LearnStock(e->unk_00[0]);
            TaskCreate(&gFieldState->tasks5, &gTaskDescMapPrzStock, e);
            return;
        case 2:
            if (gMapRoomState->roomType != 22) {
                break;
            }

            e = &gPrzCardKinds[p->unk_00[1]];

            if (IsCardKindObtained(e->unk_00[0]) == 1) {
                break;
            }

            SetCardKindObtained(e->unk_00[0]);
            CreateMapPrzCardTask(e, 1, x, y, z);
            gMapFloorState.flags |= FLOOR_FLAG_CHAMBER_PRIZE_TAKEN;
            return;
        case 3:
            if (gMapRoomState->roomType != 22) {
                break;
            }

            e = &gPrzStocks[p->unk_00[1]];

            if (IsStockLearned(e->unk_00[0]) != 1) {
                LearnStock(e->unk_00[0]);
                TaskCreate(&gFieldState->tasks5, &gTaskDescMapPrzStock, e);
                gMapFloorState.flags |= FLOOR_FLAG_CHAMBER_PRIZE_TAKEN;
                return;
            }

            break;
        }
    }

    if ((gGameState.flags & GAME_FLAG_RIKU_CLEAR) && gGameState.world == WORLD_CASTLE_OBLIVION && IsCardKindObtained(16)) {
        e = &gPrzCardKinds[14];

        if (IsCardKindObtained(e->unk_00[0]) != 1) {
            SetCardKindObtained(e->unk_00[0]);
            CreateMapPrzCardTask(e, 1, x, y, z);
            return;
        }

        e += 24;

        if (IsCardKindObtained(e->unk_00[0]) != 1) {
            SetCardKindObtained(e->unk_00[0]);
            CreateMapPrzCardTask(e, 1, x, y, z);
            return;
        }

        e++;

        if (IsCardKindObtained(e->unk_00[0]) != 1) {
            SetCardKindObtained(e->unk_00[0]);
            CreateMapPrzCardTask(e, 1, x, y, z);
            return;
        }
    }

    e = PickRandomPrzCard(1);

    if (e != NULL) {
        CreateMapPrzCardTask(e, 1, x, y, z);
    }
}

u8 AreWorldPrizesCollected() {
    s32 i;
    u8* p;

    for (i = 1; i <= 11; i++) {
        PrizeEntry** t = gWorldPrizeLists;

        p = (u8*)t[i];

        while (p[0] != 4) {
            switch (p[0]) {
            case 2:
                if (IsCardKindObtained((gPrzCardKinds + p[1])->unk_00[0]) != 1) {
                    return 0;
                }

                break;
            case 3:
                if (IsStockLearned((gPrzStocks + p[1])->unk_00[0]) != 1) {
                    return 0;
                }

                break;
            }

            p += 4;
        }
    }

    return 1;
}

void CopyMapProgress(MapProgress* p) {
    s32 i;
    u32* src;
    u32* dst;

    p->world = gGameState.world;
    p->floor = gGameState.floor;
    memcpy(p->floorState, &gMapFloorState, 0x21C);
    src = (u32*)gGameState.floors;
    dst = (u32*)p->floors;

    for (i = 12; i >= 0; i--) {
        *dst++ = *src++;
    }
}

void RestoreMapProgress(MapProgress* p) {
    s32 i;
    u32* src;
    u32* dst;

    gGameState.world = p->world;
    gGameState.floor = p->floor;
    memcpy(&gMapFloorState, p->floorState, 0x21C);
    src = (u32*)p->floors;
    dst = (u32*)gGameState.floors;

    for (i = 12; i >= 0; i--) {
        *dst++ = *src++;
    }
}

void MapDbgSetUpdate(ModeFunc a) {
    sMapDbgUpdate = a;
}

void MapDbgSetUpdateAndRun(ModeFunc a) {
    MapDbgSetUpdate(a);
    sMapDbgUpdate();
}

void MapDbgFreeCameraInput() {
    s32 y = 0;
    s32 x = 0;
    u16 m1 = DISPCNT_BG1_ON;
    u16 m2 = DISPCNT_OBJ_ON;

    if (GetKeysHeld() & DPAD_LEFT) {
        x = -1024;
    }

    if (GetKeysHeld() & DPAD_RIGHT) {
        x = 1024;
    }

    if (GetKeysHeld() & DPAD_UP) {
        y = -1024;
    }

    if (GetKeysHeld() & DPAD_DOWN) {
        y = 1024;
    }

    MapMoveCameraTarget(x, y);

    if (GetKeysPressed() & A_BUTTON) {
        gDispCnt = (gDispCnt & ~DISPCNT_BG1_ON) | (m1 & ~gDispCnt);
    }

    if (GetKeysPressed() & B_BUTTON) {
        gDispCnt = (gDispCnt & ~DISPCNT_OBJ_ON) | (m2 & ~gDispCnt);
    }
}

void MapDbgMain() {
    if (gMapRoomState->flags & ROOM_FLAG_START_BATTLE) {
        gMapRoomState->flags &= ~ROOM_FLAG_START_BATTLE;
        gMapRoomState->flags &= ~ROOM_FLAG_ENEMY_STRUCK;
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
    }

    if (gFieldState->flags & FIELD_FLAG_EXIT_ROOM) {
        FadeStartOut(FADE_MODE_BLACK, 16);
        MapDbgSetUpdateAndRun(MapDbgExitRoom);
        return;
    }

    if (gMapRoomState->flags & ROOM_FLAG_SAVE_MENU_OPEN) {
        TaskKill(&gFieldState->tasks, sMapDbgAllmapRoomTask);
        sMapDbgAllmapRoomTask = NULL;
        MapDbgSetUpdateAndRun(MapDbgWaitMenu);
        return;
    }

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        TaskKill(&gFieldState->tasks, sMapDbgAllmapRoomTask);
        sMapDbgAllmapRoomTask = NULL;
        MapDbgSetUpdateAndRun(MapDbgWaitRoomCreate);
        return;
    }

    if (sMapDbgEditing != 0) {
        MapDbgSetUpdateAndRun(MapDbgWaitEdit);
        return;
    }

    UpdateMapField();
    DrawMapField();
    ColliderUpdateAll();
    MapEnmUpdateSpawner();

    if ((GetKeysHeld() & (L_BUTTON | R_BUTTON)) == (L_BUTTON | R_BUTTON)) {
        return;
    }

    if (GetKeysPressed() & START_BUTTON) {
        MapDbgSetUpdate(MapDbgFreeCameraMode);
    }

    if (GetKeysPressed() & SELECT_BUTTON) {
        ModeRequest(&gModeMapChk, 0);
    }
}

void MapDbgExitRoom() {
    DrawMapField();

    if (!FadeIsActive()) {
        SetCurrentMapRoom(gMapRoomState->doorRoom, gMapRoomState->doorSide);

        if (gMapRoomState->doorRoom != MAP_ROOM_EXIT_HALL && gMapRoomState->doorRoom != MAP_ROOM_ENTRANCE_HALL) {
            ModeRequest(&gModeMapDbg, 0);
        } else {
            RequestMapMode();
        }
    }
}

void MapDbgFreeCameraMode() {
    if (sMapDbgEditing != 0) {
        MapDbgSetUpdateAndRun(MapDbgWaitEdit);
        return;
    }

    MapDbgFreeCameraInput();
    TaskPoolUpdate(&gFieldState->tasks);
    DrawMapField();

    if ((GetKeysHeld() & (L_BUTTON | R_BUTTON)) == (L_BUTTON | R_BUTTON)) {
        return;
    }

    if (GetKeysPressed() & START_BUTTON) {
        MapDbgSetUpdate(MapDbgMain);
    }

    if (GetKeysPressed() & SELECT_BUTTON) {
        ModeRequest(&gModeMapChk, 0);
    }
}

void MapDbgWaitEdit() {
    DrawMapField();

    if (sMapDbgEditing == 0) {
        ModeRequest(&gModeMapDbg, 0);
    }
}

void MapDbgWaitMenu() {
    if ((gFieldState->flags & FIELD_FLAG_MENU_OPEN) == 0 && (gMapRoomState->flags & ROOM_FLAG_SAVE_MENU_OPEN) == 0) {
        sMapDbgAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
        MapGmkCreateTasks();
        MapDbgSetUpdateAndRun(MapDbgMain);
    } else {
        UpdateMapField();
        DrawMapField();
    }
}

void MapDbgWaitRoomCreate() {
    if (gFieldState->flags & FIELD_FLAG_EXIT_ROOM) {
        FadeStartOut(FADE_MODE_BLACK, 16);
        MapDbgSetUpdateAndRun(MapDbgExitRoom);
    } else if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) == 0) {
        gBldCnt = 0;
        SetBgPriority(0, 0);
        sMapDbgAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
        MapGmkCreateTasks();
        MapEnmRestoreFromCache();
        MapDbgSetUpdateAndRun(MapDbgMain);
    } else {
        UpdateMapField();
        DrawMapField();
    }
}

void Mode_MapDbg_0() {
    MapRoomDef* p;

    gFieldState = EwramAlloc(sizeof(FieldState));
    gMapRoomState = EwramAlloc(sizeof(MapRoomState));
    UpdateGameWorld();
    SetBgMode0();
    SetupBg(3, 0, 28, 0);
    SetupBg(2, 0, 29, 0);
    SetupBg(1, 2, 30, 0);
    SetupBg(0, 3, 31, 14);
    SetBgPriority(3, 3);
    SetBgPriority(2, 3);
    SetBgPriority(1, 1);
    SetBgPriority(0, 0);
    SetBackdropColor(6, 31, 31);
    SetBlendAlpha(6, 10);
    InitFieldState();
    ColliderPoolsInit();
    CreateMapRndTask();
    MapGmkInitRoom();
    MapEnmInitRoom();
    MapApplyRoomDecor();
    SpawnMapPlayer();

    p = gMapRoomDefs[gMapFloorState.world];
    TaskCreate(&gFieldState->tasks, &gTaskDescLockon, NULL);
    TaskCreate(&gFieldState->tasks, &gTaskDescMapAnm, p->tileAnims);
    sMapDbgAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
    MapDbgSetUpdate(MapDbgMain);

    if (gGameState.fieldResume) {
        MapSetCameraTarget(gGameState.fieldPosition.x, gGameState.fieldPosition.y + gGameState.fieldPosition.z);
    } else {
        MapSetCameraTarget(gFieldState->spawnX, gFieldState->spawnY);
    }

    MapSnapCamera();
    ClearFieldResume();
    SeedRandom(gFrameCounter);
    m4aSongNumStartOrContinue(p->song);
    TaskPoolInit(&sMapDbgTasks, 1);
    TaskCreate(&sMapDbgTasks, &gTaskDescMapDbg, &sMapDbgEditing);
    TaskCreate(&gFieldState->tasks, &gTaskDescMapDmg, NULL);
    FadeStartIn(FADE_MODE_BLACK, 16);
}

void Mode_MapDbg_1() {
    TaskPoolUpdate(&sMapDbgTasks);
    TaskPoolDraw(&sMapDbgTasks);
    sMapDbgUpdate();
    UpdatePlayTime();
}

void Mode_MapDbg_2() {
    DestroyMapField();
    MapGmkFree();
    EwramFree(gFieldState);
    EwramFree(gMapRoomState);
    TaskPoolDestroy(&sMapDbgTasks);
}

void MapFldSetUpdate(ModeFunc a) {
    sMapFldUpdate = a;
}

void MapFldSetUpdateAndRun(ModeFunc a) {
    MapFldSetUpdate(a);
    sMapFldUpdate();
}

void MapFldCreateWorldLogo() {
    switch (gMapFloorState.world) {
    case WORLD_ATLANTICA:
        sMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)2);
        break;
    case WORLD_HALLOWEEN_TOWN:
        sMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)6);
        break;
    case WORLD_MONSTRO:
        sMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)5);
        break;
    case WORLD_NEVER_LAND:
        sMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)7);
        break;
    case WORLD_OLYMPUS_COLISEUM:
        sMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)3);
        break;
    case WORLD_HOLLOW_BASTION:
        sMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)8);
        break;
    case WORLD_DESTINY_ISLANDS:
        sMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)9);
        break;
    case WORLD_AGRABAH:
        sMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)1);
        break;
    case WORLD_TRAVERSE_TOWN:
        sMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)10);
        break;
    case WORLD_TWILIGHT_TOWN:
        sMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)11);
        break;
    case WORLD_CASTLE_OBLIVION:
        sMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)12);
        break;
    default:
        sMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)4);
        break;
    }
}

void MapFldDestroyAllmapRoom() {
    if (sMapFldAllmapRoomTask != NULL) {
        TaskKill(&gFieldState->tasks, sMapFldAllmapRoomTask);
        sMapFldAllmapRoomTask = NULL;
    }
}

void StartWorldBossBattle() {
    switch (gGameState.world) {
    case WORLD_TRAVERSE_TOWN:
        ModeRequest(&gModeBattle, 0x94);
        break;
    case WORLD_AGRABAH:
        ModeRequest(&gModeBattle, 0x95);
        break;
    case WORLD_MONSTRO:
        ModeRequest(&gModeBattle, 0x98);
        break;
    case WORLD_NEVER_LAND:
        ModeRequest(&gModeBattle, 0x9E);
        break;
    case WORLD_HALLOWEEN_TOWN:
        ModeRequest(&gModeBattle, 0x9B);
        break;
    case WORLD_ATLANTICA:
        ModeRequest(&gModeBattle, 0x97);
        break;
    case WORLD_WONDERLAND:
        ModeRequest(&gModeBattle, 0x96);
        break;
    case WORLD_OLYMPUS_COLISEUM:
        ModeRequest(&gModeBattle, 0xA0);
        break;
    }
}

void MapFldShowWorldLogo() {
    u8 r = IsTaskActive(sMapFldWorldLogoTask);

    if (r) {
        TaskPoolUpdate(&gMapRoomState->tasks);
        TaskPoolDraw(&gMapRoomState->tasks);
        TaskPoolUpdate(&gFieldState->tasks);
        DrawMapField();
    } else {
        u16 t = gMapFloorState.flags | FLOOR_FLAG_LOGO_SHOWN;
        gMapFloorState.flags = t;
        sMapFldWorldLogoTask = NULL;
        sMapFldAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
        gFieldState->flags &= ~FIELD_FLAG_NO_ENEMY_SPAWN;
        gFieldState->flags &= ~FIELD_FLAG_NO_LOCKON;
        MapFldSetUpdateAndRun(MapFldMain);
    }
}

void MapFldMain() {
    if (gMapRoomState->flags & ROOM_FLAG_START_BATTLE) {
        FadeStartOut(FADE_MODE_BLACK, 16);
        FadeLock();
        MapFldSetUpdateAndRun(MapFldStartBattle);
        return;
    }

    if (gFieldState->flags & FIELD_FLAG_EXIT_ROOM) {
        FadeStartOut(FADE_MODE_BLACK, 16);
        FadeLock();
        MapFldSetUpdateAndRun(MapFldExitRoom);
        return;
    }

    if (!FadeIsActive() && (gGameState.progression.tutorialFlags & 0x200) != 0 &&
        (gFieldState->flags & (FIELD_FLAG_FREEZE_PLAYER | FIELD_FLAG_ROOM_CREATE)) == 0 && (gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) == 0) {
        if (GetKeysPressed() & SELECT_BUTTON) {
            m4aSongNumStart(SONG_SYS_CANSEL);
            FadeStartOut(FADE_MODE_BLACK, 16);
            FadeLock();
            MapFldSetUpdateAndRun(MapFldOpenAllmap);
            return;
        }

        if (GetKeysPressed() & START_BUTTON) {
            MapFldDestroyAllmapRoom();
            TaskCreate(&gFieldState->tasks, &gTaskDescMapMenu, NULL);
            MapFldSetUpdateAndRun(MapFldWaitMenu);
            return;
        }
    }

    if (gMapRoomState->flags & ROOM_FLAG_SAVE_MENU_OPEN) {
        MapFldDestroyAllmapRoom();
        MapFldSetUpdateAndRun(MapFldWaitMenu);
        return;
    }

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapFldDestroyAllmapRoom();
        MapFldSetUpdateAndRun(MapFldWaitRoomCreate);
        return;
    }

    UpdateMapField();
    DrawMapField();
    ColliderUpdateAll();
    MapEnmUpdateSpawner();
}

void MapFldExitRoom() {
    u8 r;
    u8* e;
    MapEventDoor* d;

    DrawMapField();
    r = FadeIsActive();

    if (r) {
        return;
    }

    if (gMapRoomState->doorRoom == MAP_ROOM_ENTRANCE_HALL) {
        EnterEntranceHall();
        return;
    }

    if (gMapRoomState->doorRoom == MAP_ROOM_EXIT_HALL) {
        EnterExitHall();
        return;
    }

    e = GetMapRoomEvent(gMapFloorState.eventStep);

    if (e[0] == 0xFF) {
        SetCurrentMapRoom(gMapRoomState->doorRoom, gMapRoomState->doorSide);
        ModeRequest(&gModeMapFld, 0);
        return;
    }

    d = GetMapEventDoor(e[0]);

    if (d->room != gMapRoomState->doorRoom || d->side != gMapRoomState->doorSide) {
        SetCurrentMapRoom(gMapRoomState->doorRoom, gMapRoomState->doorSide);
        ModeRequest(&gModeMapFld, 0);
        return;
    }

    gGameState.roomEffect = r;

    switch (d->kind) {
    case 1:
    case 3:
        if (e[1] == 0x51 && (gGameState.flags & GAME_FLAG_MONSGAGE_BATTLE)) {
            RequestEventMode(0x55);
        } else {
            RequestEventMode(e[1]);
        }

        break;
    case 2:
        SetCurrentMapRoom(gMapRoomState->doorRoom, gMapRoomState->doorSide);
        ModeRequest(&gModeMapFld, 0);
        break;
    case 4:
        StartWorldBossBattle();
        break;
    }
}

void MapFldStartBattle() {
    DrawMapField();

    if (!FadeIsActive()) {
        RequestFieldResume();

        if (gGameState.flags & GAME_FLAG_RIKU) {
            if (gGameState.progression.tutorialFlags & 0x1000) {
                ModeRequest(&gModeBattle, gMapRoomState->battleId);
            } else {
                ModeRequest(&gModeRikuBtlTutorial, gMapRoomState->battleId);
            }
        } else {
            ModeRequest(&gModeBattle, gMapRoomState->battleId);
        }
    }
}

void MapFldOpenAllmap() {
    DrawMapField();

    if (!FadeIsActive()) {
        RequestFieldResume();
        ModeRequest(&gModeAllmap, 1);
    }
}

void MapFldWaitMenu() {
    if ((gFieldState->flags & FIELD_FLAG_MENU_OPEN) == 0 && (gMapRoomState->flags & ROOM_FLAG_SAVE_MENU_OPEN) == 0) {
        SetupBg(0, 3, 31, 14);
        SetBgPriority(0, 0);
        MapGmkCreateTasks();
        sMapFldAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
        MapFldSetUpdateAndRun(MapFldMain);
    } else {
        UpdateMapField();
        DrawMapField();
    }
}

void MapFldWaitRoomCreate() {
    u16 t;

    if (gFieldState->flags & FIELD_FLAG_EXIT_ROOM) {
        FadeStartOut(FADE_MODE_BLACK, 16);
        FadeLock();
        MapFldSetUpdateAndRun(MapFldExitRoom);

        if ((gGameState.progression.tutorialFlags & 0x200) == 0) {
            t = gGameState.progression.tutorialFlags | 0x200;
            gGameState.progression.tutorialFlags = t;
        }
    } else if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) == 0) {
        gBldCnt = 0;
        SetBgPriority(0, 0);
        MapGmkCreateTasks();
        MapEnmRestoreFromCache();
        sMapFldAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
        MapFldSetUpdateAndRun(MapFldMain);
    } else {
        UpdateMapField();
        DrawMapField();
    }
}

void MapFldRestart() {
    DrawMapField();

    if (sUnk_02034FBC == 0) {
        ModeRequest(&gModeMapFld, 0);
    }
}

void Mode_MapFld_0() {
    MapRoomDef* p;

    if ((gMapFloorState.flags & FLOOR_FLAG_LOGO_SHOWN) && !gGameState.fieldResume) {
        switch (gMapFloorState.entrySide) {
        case 0:
            gGameState.fieldAngle = 0xAD;
            break;
        case 1:
            gGameState.fieldAngle = 0x2D;
            break;
        case 2:
            gGameState.fieldAngle = 0xD3;
            break;
        case 3:
            gGameState.fieldAngle = 0x53;
            break;
        }

        StartFieldTransition();
    }

    gFieldState = EwramAlloc(sizeof(FieldState));
    gMapRoomState = EwramAlloc(sizeof(MapRoomState));
    sMapFldWorldLogoTask = NULL;
    sMapFldAllmapRoomTask = NULL;
    UpdateGameWorld();
    SetBgMode0();
    SetupBg(3, 0, 28, 0);
    SetupBg(2, 0, 29, 0);
    SetupBg(1, 2, 30, 0);
    SetupBg(0, 3, 31, 14);
    SetBgPriority(3, 3);
    SetBgPriority(2, 3);
    SetBgPriority(1, 1);
    SetBgPriority(0, 0);
    SetBackdropColor(6, 31, 31);
    InitFieldState();
    ColliderPoolsInit();
    CreateMapRndTask();
    MapGmkInitRoom();
    MapEnmInitRoom();
    MapApplyRoomDecor();
    SpawnMapPlayer();

    p = gMapRoomDefs[gMapFloorState.world];
    TaskCreate(&gFieldState->tasks, &gTaskDescLockon, NULL);
    TaskCreate(&gFieldState->tasks, &gTaskDescMapAnm, p->tileAnims);

    if ((gGameState.progression.tutorialFlags & 0x20) == 0) {
        TaskCreate(&gFieldState->tasks, &gTaskDescMapTutorial, NULL);
    }

    if ((gMapFloorState.flags & FLOOR_FLAG_LOGO_SHOWN) == 0) {
        MapFldSetUpdate(MapFldShowWorldLogo);
        gFieldState->flags |= FIELD_FLAG_NO_ENEMY_SPAWN;
        gFieldState->flags |= FIELD_FLAG_NO_LOCKON;
        MapSetCameraTarget(gFieldState->spawnX, gFieldState->spawnY);
        MapFldCreateWorldLogo();
    } else if (gGameState.fieldResume) {
        MapSetCameraTarget(gGameState.fieldPosition.x, gGameState.fieldPosition.y + gGameState.fieldPosition.z);

        if ((s8)gGameState.mapMenuCursor != -1) {
            gDispCnt &= ~DISPCNT_OBJ_ON;
            TaskCreate(&gFieldState->tasks, &gTaskDescMapMenu, NULL);
            MapFldSetUpdate(MapFldWaitMenu);
        } else {
            sMapFldAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
            MapFldSetUpdate(MapFldMain);
        }
    } else {
        sMapFldAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
        MapSetCameraTarget(gFieldState->spawnX, gFieldState->spawnY);
        MapFldSetUpdate(MapFldMain);
    }

    MapSnapCamera();
    ClearFieldResume();
    SeedRandom(gFrameCounter);
    m4aSongNumStartOrContinue(p->song);
    FadeStartIn(FADE_MODE_BLACK, 16);
}

void Mode_MapFld_1() {
    sMapFldUpdate();
    UpdatePlayTime();
}

void Mode_MapFld_2() {
    DestroyMapField();
    MapGmkFree();
    EwramFree(gFieldState);
    EwramFree(gMapRoomState);
}

void MapFixSetUpdate(ModeFunc a) {
    sMapFixUpdate = a;
}

void MapFixSetUpdateAndRun(ModeFunc a) {
    MapFixSetUpdate(a);
    sMapFixUpdate();
}

MapFixedDef* GetMapFixedDef() {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        if (gMapFloorState.room == MAP_ROOM_EXIT_HALL) {
            return gMapFixedDefs[2];
        }

        if (gMapFloorState.room == MAP_ROOM_ENTRANCE_HALL) {
            if (gGameState.floor != 0) {
                return gMapFixedDefs[1];
            }

            return gMapFixedDefs[5];
        }
    }

    if (gMapFloorState.room == MAP_ROOM_EXIT_HALL) {
        if (gGameState.floor != 12) {
            return gMapFixedDefs[2];
        }

        return gMapFixedDefs[3];
    }

    if (gMapFloorState.room == MAP_ROOM_ENTRANCE_HALL) {
        if (gGameState.floor != 0) {
            return gMapFixedDefs[1];
        }

        return gMapFixedDefs[0];
    }

    return gMapFixedDefs[4];
}

void MapFixCreateCharaTasks() {
    if (gMapFloorState.room == MAP_ROOM_TUTORIAL) {
        return;
    }

    if (gGameState.flags & GAME_FLAG_RIKU) {
        switch (gMapFloorState.progress) {
        case 20:
        case 22:
        case 23:
        case 24:
            TaskCreate(&gFieldState->tasks, &gTaskDescMapMickey, NULL);
            break;
        }

        return;
    }

    if (gGameState.progression.friendFlags & FRIEND_FLAG_DONALD_DUCK) {
        TaskCreate(&gFieldState->tasks, &gTaskDescMapDonald, NULL);
    }

    if (gGameState.progression.friendFlags & FRIEND_FLAG_GOOFY) {
        TaskCreate(&gFieldState->tasks, &gTaskDescMapGoofy, NULL);
    }

    if (gMapFloorState.room != MAP_ROOM_EXIT_HALL) {
        return;
    }

    switch (gMapFloorState.progress) {
    case 23:
    case 24:
        if (gGameState.floor == 11) {
            TaskCreate(&gFieldState->tasks, &gTaskDescMapNamine, NULL);
            TaskCreate(&gFieldState->tasks, &gTaskDescMapNiseriku, NULL);
        }

        break;
    case 25:
    case 26:
        if (gGameState.floor == 11 && gGameState.floors[12].eventStep == 0) {
            TaskCreate(&gFieldState->tasks, &gTaskDescMapNamine, NULL);
            TaskCreate(&gFieldState->tasks, &gTaskDescMapNiseriku, NULL);
        }

        break;
    case 27:
        if (gGameState.floor == 12) {
            TaskCreate(&gFieldState->tasks, &gTaskDescMapNamine, NULL);
            TaskCreate(&gFieldState->tasks, &gTaskDescMapNiseriku, NULL);
        }

        break;
    }
}

u8 GetWorldEntryEventId() {
    if (gMapFloorState.flags & FLOOR_FLAG_ENTRY_EVENT_DONE) {
        return 0xFF;
    }

    if (gGameState.flags & GAME_FLAG_RIKU) {
        switch (gMapFloorState.world) {
        case WORLD_HOLLOW_BASTION:
#ifdef VERSION_EU
            return 0x95;
#else
            return 0x97;
#endif
        case WORLD_DESTINY_ISLANDS:
#ifdef VERSION_EU
            return 0xAF;
#else
            return 0xB1;
#endif
        case WORLD_TWILIGHT_TOWN:
#ifdef VERSION_EU
            return 0xB8;
#else
            return 0xBA;
#endif
        case WORLD_CASTLE_OBLIVION:
#ifdef VERSION_EU
            return 0xBE;
#else
            return 0xC0;
#endif
        }

        return 0xFF;
    }

    return gWorldEntryEvents[gMapFloorState.world];
}

u8 GetFloorEventId() {
    if (gMapFloorState.flags & FLOOR_FLAG_CLEARED) {
        return 0xFF;
    }

    if (gGameState.flags & GAME_FLAG_RIKU) {
        return gRikuFloorEvents[gGameState.floor];
    }

    return gSoraFloorEvents[gGameState.floor];
}

void MapFixMain() {
    if (gMapRoomState->flags & ROOM_FLAG_WALK_OUT) {
        MapFixSetUpdateAndRun(MapFixWaitWalkOut);
        return;
    }

    if (gMapRoomState->flags & (ROOM_FLAG_ENTER_WORLD | ROOM_FLAG_EXIT_NEXT_FLOOR | ROOM_FLAG_EXIT_PREV_FLOOR)) {
        FadeStartOut(FADE_MODE_BLACK, 16);

        if (gMapFloorState.room == MAP_ROOM_ENTRANCE_HALL) {
            MapFixSetUpdateAndRun(MapFixLeaveEntranceHall);
            return;
        }

        if (gMapFloorState.room == MAP_ROOM_EXIT_HALL) {
            MapFixSetUpdateAndRun(MapFixLeaveExitHall);
            return;
        }

        MapFixSetUpdateAndRun(MapFixEnterMapFld);
        return;
    }

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        MapFixSetUpdateAndRun(MapFixWaitRoomCreate);
        return;
    }

    if (gMapRoomState->flags & ROOM_FLAG_SAVE_MENU_OPEN) {
        MapFixSetUpdateAndRun(MapFixWaitMenu);
    } else if (!FadeIsActive() && (gGameState.progression.tutorialFlags & 0x200) != 0 &&
               (gFieldState->flags & (FIELD_FLAG_FREEZE_PLAYER | FIELD_FLAG_ROOM_CREATE)) == 0 && (gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) == 0 &&
               (GetKeysPressed() & START_BUTTON) != 0) {
        TaskCreate(&gFieldState->tasks, &gTaskDescMapMenu, NULL);
        MapFixSetUpdateAndRun(MapFixWaitMenu);
    } else {
        UpdateMapField();
        DrawMapField();
        ColliderUpdateAll();
    }
}

void MapFixEnterMapFld() {
    DrawMapField();

    if (!FadeIsActive()) {
        EnterFloorWorld();
        ModeRequest(&gModeMapFld, 0);
    }
}

void MapFixLeaveEntranceHall() {
    DrawMapField();

    if (FadeIsActive()) {
        return;
    }

    if (gMapRoomState->flags & ROOM_FLAG_ENTER_WORLD) {
        if (gGameState.floor == GetProgressFloor()) {
            gGameState.flags &= ~GAME_FLAG_FRIENDS_SAVED;
            gGameState.progression.friendFlags = (gGameState.progression.friendFlags & ~FRIEND_FLAGS_WORLD) | gGameState.progression.savedFriendFlags;
        }

        if (gMapFloorState.world == 0) {
            gMapFloorState.entrySide = 0;
            ModeRequest(&gModeWorldselect, 0);
        } else if (gMapFloorState.world == WORLD_100_ACRE_WOOD) {
#ifdef VERSION_EU
            RequestEventMode(0x85);
#else
            RequestEventMode(0x87);
#endif
        } else if (GetWorldEntryEventId() != 0xFF) {
            sMapFixEventDelay = 60;
            MapFixSetUpdateAndRun(MapFixWaitWorldEvent);
        } else {
            EnterFloorWorld();
            RequestMapMode();
        }
    } else {
        StoreMapFloorState();
        GoToPreviousFloor();
        RequestMapMode();
    }
}

void MapFixLeaveExitHall() {
    u8 v;
    u16 t;

    DrawMapField();

    if (FadeIsActive()) {
        return;
    }

    if (gMapRoomState->flags & ROOM_FLAG_ENTER_WORLD) {
        if (gMapFloorState.world != WORLD_100_ACRE_WOOD) {
            EnterFloorWorld();
            ModeRequest(&gModeMapFld, 0);
        } else {
            gMapFloorState.entrySide = 1;
            ModeRequest(&gModePooh, 2);
        }

        return;
    }

    v = GetFloorEventId();

    if (v != 0xFF) {
        RequestEventMode(v);
        return;
    }

    if ((gMapFloorState.flags & FLOOR_FLAG_CLEARED) == 0) {
        t = gMapFloorState.flags | FLOOR_FLAG_CLEARED;
        gMapFloorState.flags = t;
        SetFloorJiminyFlags();
        gMapFloorState.progress++;
    }

    StoreMapFloorState();
    GoToNextFloor();
    RequestMapMode();
}

void MapFixWaitMenu() {
    if ((gFieldState->flags & FIELD_FLAG_MENU_OPEN) == 0 && (gMapRoomState->flags & ROOM_FLAG_SAVE_MENU_OPEN) == 0) {
        SetupBg(0, 3, 31, 14);
        SetBgPriority(0, 0);
        MapFixCreateGimmicks(GetMapFixedDef()->gimmicks);
        MapFixSetUpdateAndRun(MapFixMain);
    } else {
        UpdateMapField();
        DrawMapField();
    }
}

void MapFixWaitWalkOut() {
    if ((gMapRoomState->flags & ROOM_FLAG_WALK_OUT) == 0) {
        FadeStartOut(FADE_MODE_ADD_WHITE, 60);
        FadeLock();
        gMapRoomState->flags |= ROOM_FLAG_ENTER_WORLD;
        MapFixSetUpdateAndRun(MapFixLeaveEntranceHall);
    } else {
        UpdateMapField();
        DrawMapField();
    }
}

void MapFixWaitWorldEvent() {
    if (sMapFixEventDelay != 0) {
        sMapFixEventDelay--;
    } else {
        RequestEventMode(GetWorldEntryEventId());
    }
}

void MapFixWaitRoomCreate() {
    if (gFieldState->flags & FIELD_FLAG_EXIT_ROOM) {
        FadeStartOut(FADE_MODE_BLACK, 16);
        MapFixSetUpdateAndRun(MapFixEnterMapFld);
    } else if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) == 0) {
        gBldCnt = 0;
        SetBgPriority(0, 0);
        MapFixCreateGimmicks(GetMapFixedDef()->gimmicks);
        MapFixSetUpdateAndRun(MapFixMain);
    } else {
        UpdateMapField();
        DrawMapField();
        ColliderUpdateAll();
    }
}

void Mode_MapFix_0() {
    MapFixedDef* p;
    u16 t;

    gFieldState = EwramAlloc(sizeof(FieldState));
    gMapRoomState = EwramAlloc(sizeof(MapRoomState));
    gMapGmkPlacements = EwramAlloc(sizeof(MapGmkPlacement) * 16);
    UpdateGameWorld();
    SetBgMode0();

    if (gMapFloorState.room == MAP_ROOM_ENTRANCE_HALL) {
        SetupBg(3, 0, 28, 0);
        SetupBg(2, 0, 29, 0);
        SetupBg(1, 0, 30, 0);
        SetupBg(0, 3, 31, 14);
    } else {
        SetupBg(3, 0, 28, 0);
        SetupBg(2, 0, 29, 0);
        SetupBg(1, 2, 30, 0);
        SetupBg(0, 3, 31, 14);
    }

    SetBgPriority(3, 3);
    SetBgPriority(2, 3);
    SetBgPriority(1, 1);
    SetBgPriority(0, 0);
    SetBackdropColor(0, 0, 0);
    InitFieldState();
    ColliderPoolsInit();
    gMapRoomState->flags |= ROOM_FLAG_FIXED_ROOM;
    gMapRoomState->nameId = 26;
    gMapRoomState->roomType = 0;

    p = GetMapFixedDef();
    TaskCreate(&gFieldState->tasks, &gTaskDescMapFix, p);
    MapFixCreateGimmicks(p->gimmicks);

    if (gGameState.flags & GAME_FLAG_RIKU) {
        TaskCreate(&gFieldState->tasks2, &gTaskDescFldRiku, NULL);
    } else {
        TaskCreate(&gFieldState->tasks2, &gTaskDescFldSora, NULL);
    }

    TaskCreate(&gFieldState->tasks, &gTaskDescLockon, NULL);

    if (gMapFloorState.flags & FLOOR_FLAG_SHOW_FLOOR_NAME) {
        t = gMapFloorState.flags & ~FLOOR_FLAG_SHOW_FLOOR_NAME;
        gMapFloorState.flags = t;
        TaskCreate(&gFieldState->tasks, &gTaskDescMapFloor, NULL);
    }

    if (gMapFloorState.room == MAP_ROOM_TUTORIAL) {
        TaskCreate(&gFieldState->tasks, &gTaskDescMapGmkTutorial, NULL);
    }

    MapFixCreateCharaTasks();

    if (gGameState.fieldResume) {
        MapSetCameraTarget(gGameState.fieldPosition.x, gGameState.fieldPosition.y + gGameState.fieldPosition.z);

        if ((s8)gGameState.mapMenuCursor != -1) {
            gDispCnt &= ~DISPCNT_OBJ_ON;
            TaskCreate(&gFieldState->tasks, &gTaskDescMapMenu, NULL);
            MapFixSetUpdate(MapFixWaitMenu);
        } else {
            MapFixSetUpdate(MapFixMain);
        }
    } else {
        MapSetCameraTarget(gFieldState->spawnX, gFieldState->spawnY);
        MapFixSetUpdate(MapFixMain);
    }

    MapFixSnapCamera();
    ClearFieldResume();
    SeedRandom(gFrameCounter);
    m4aSongNumStartOrContinue(p->song);

    if (gMapFloorState.flags & FLOOR_FLAG_WARP_IN) {
        t = gMapFloorState.flags & ~FLOOR_FLAG_WARP_IN;
        gMapFloorState.flags = t;
        MosaicStartIn(16, 15);
        FadeStartIn(FADE_MODE_BLACK, 16);
    } else {
        FadeStartIn(FADE_MODE_BLACK, 16);
    }
}

void Mode_MapFix_1() {
    sMapFixUpdate();
    UpdatePlayTime();
}

void Mode_MapFix_2() {
    DestroyMapField();
    EwramFree(gFieldState);
    EwramFree(gMapRoomState);
    EwramFree(gMapGmkPlacements);
}

void NewGameSlotMenuLoadFloorTiles(u8 a, u8 b, u8 c) {
    const u8* src;

    a &= 1;

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        if (b) {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gSaveSlotRikuFloorSelectedTiles[c];
            } else {
                src = gSaveSlotSoraFloorSelectedTiles[c];
            }
        } else {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gSaveSlotRikuFloorTiles[c];
            } else {
                src = gSaveSlotSoraFloorTiles[c];
            }
        }

        break;
    case LANGUAGE_FRENCH:
        if (b) {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gSaveSlotRikuFloorSelectedFrenchTiles[c];
            } else {
                src = gSaveSlotSoraFloorSelectedFrenchTiles[c];
            }
        } else {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gSaveSlotRikuFloorFrenchTiles[c];
            } else {
                src = gSaveSlotSoraFloorFrenchTiles[c];
            }
        }

        break;
    case LANGUAGE_SPANISH:
        if (b) {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gSaveSlotRikuFloorSelectedSpanishTiles[c];
            } else {
                src = gSaveSlotSoraFloorSelectedSpanishTiles[c];
            }
        } else {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gSaveSlotRikuFloorSpanishTiles[c];
            } else {
                src = gSaveSlotSoraFloorSpanishTiles[c];
            }
        }

        break;
    case LANGUAGE_ITALIAN:
        if (b) {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gSaveSlotRikuFloorSelectedItalianTiles[c];
            } else {
                src = gSaveSlotSoraFloorSelectedItalianTiles[c];
            }
        } else {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gSaveSlotRikuFloorItalianTiles[c];
            } else {
                src = gSaveSlotSoraFloorItalianTiles[c];
            }
        }

        break;
    case LANGUAGE_GERMAN:
    default:
        if (b) {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gSaveSlotRikuFloorSelectedGermanTiles[c];
            } else {
                src = gSaveSlotSoraFloorSelectedGermanTiles[c];
            }
        } else {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gSaveSlotRikuFloorGermanTiles[c];
            } else {
                src = gSaveSlotSoraFloorGermanTiles[c];
            }
        }

        break;
    }
#else
    if (b) {
        if (gGameState.flags & GAME_FLAG_RIKU) {
            src = gSaveSlotRikuFloorSelectedTiles[c];
        } else {
            src = gSaveSlotSoraFloorSelectedTiles[c];
        }
    } else {
        if (gGameState.flags & GAME_FLAG_RIKU) {
            src = gSaveSlotRikuFloorTiles[c];
        } else {
            src = gSaveSlotSoraFloorTiles[c];
        }
    }
#endif

    RequestDma3Copy((void*)src, (u8*)GetBgCharBase(1) + (a * 608 + 320), 320);
}

void NewGameSlotMenuLoadLevelTiles(u8 a, u16 v) {
    u16 d[4];
    s32 off;
    u16* q;
    s32 i;

    a &= 1;
    d[0] = v / 100;
    d[1] = v / 10 - d[0] * 10;
    d[2] = v - d[0] * 100 - d[1] * 10;
    i = 1;
    off = a * 608 + 32;
    q = &d[1];

    while (i <= 2) {
        RequestDma3Copy((void*)&gSaveSlotDigitTiles[*q * 32], (u8*)GetBgCharBase(1) + off + i * 32, 0x20);
        q++;
        i++;
    }
}

void NewGameSlotMenuLoadTimeTiles(u8 a, u32 b) {
    u16 d[6];
    s32 off;
    u16* q;
    s32 i;
    u32 t;

    a &= 1;
    t = b / 3600;
    d[0] = t / 10;
    d[1] = t - d[0] * 10;
    b -= t * 3600;
    t = b / 60;
    d[2] = t / 10;
    d[3] = t - d[2] * 10;
    b -= t * 60;
    d[4] = b / 10;
    d[5] = b - d[4] * 10;
    i = 0;
    off = a * 608 + 128;
    q = &d[0];

    while (i <= 5) {
        RequestDma3Copy((void*)&gSaveSlotDigitTiles[*q * 32], (u8*)GetBgCharBase(1) + off + i * 32, 0x20);
        q++;
        i++;
    }
}

s32 NewGameSlotMenuShowSummary(u8 i) {
    SaveFileSummary* p = &gGameState.fileSummaries[i];

    if (p->level != 0) {
        NewGameSlotMenuLoadLevelTiles(i, p->level);
        NewGameSlotMenuLoadTimeTiles(i, p->playTime);
        NewGameSlotMenuLoadFloorTiles(i, 0, p->floor);
        return 1;
    }

    NewGameSlotMenuLoadFloorTiles(i, 0, 13);
    return 0;
}

void NewGameSlotMenuSelectSlot(u8 a) {
    SaveFileSummary* e;
    u8 i = sNewGameSlotMenuWork->isRiku != 0 ? a + 2 : a;
    e = &gGameState.fileSummaries[i];

    if (e->level != 0) {
        NewGameSlotMenuLoadFloorTiles(i, 1, e->floor);
        sNewGameSlotMenuWork->textSlotCount = LoadTextSlots(GetMapWorldName(e->world), sNewGameSlotMenuWork->textSlots);

        if (sNewGameSlotMenuWork->isRiku == 0) {
            LoadObjPaletteBank(sNewGameSlotMenuWork->palette8->index, gSaveFloorSoraPalette);
        } else {
            LoadObjPaletteBank(sNewGameSlotMenuWork->palette8->index, gSaveFloorRikuPalette);
        }
    } else {
        NewGameSlotMenuLoadFloorTiles(i, 1, 13);
        sNewGameSlotMenuWork->textSlotCount = 0;
    }

    if (sNewGameSlotMenuWork->selectedSlot == 0) {
        if (sNewGameSlotMenuWork->isRiku != 0) {
            LoadBgMap(1, &gMenuNewMaps[0xC00], 0x800);
        } else {
            LoadBgMap(1, &gMenuNewMaps[0x400], 0x800);
        }

        SetBgScroll(1, 0, (u16)-9);
    } else {
        if (sNewGameSlotMenuWork->isRiku != 0) {
            LoadBgMap(1, &gMenuNewMaps[0x1000], 0x800);
        } else {
            LoadBgMap(1, &gMenuNewMaps[0x800], 0x800);
        }

        SetBgScroll(1, 0, (u16)-6);
    }
}

void NewGameSlotMenuDeselectSlot(u8 a) {
    u8 idx = sNewGameSlotMenuWork->isRiku != 0 ? a + 2 : a;
    SaveFileSummary* e = &gGameState.fileSummaries[idx];

    if (e->level != 0) {
        NewGameSlotMenuLoadFloorTiles(idx, 0, e->floor);
    } else {
        NewGameSlotMenuLoadFloorTiles(idx, 0, 13);
    }

    sNewGameSlotMenuWork->textSlotCount = 0;
}

void NewGameSlotMenuDraw() {
    s32 t;
    s32 u;

    DrawSprite(128, sNewGameSlotMenuWork->y >> 8, gMenuLoadTitleFrames[1], sNewGameSlotMenuWork->tiles2,
        sNewGameSlotMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
    DrawSprite(128, sNewGameSlotMenuWork->y2 >> 8, gMenuLoadTitleFrames[2], sNewGameSlotMenuWork->tiles2,
        sNewGameSlotMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);

    if (sNewGameSlotMenuWork->isRiku == 0) {
        DrawSprite(56, 112, gSor1ff00Frames[0], sNewGameSlotMenuWork->tiles4,
            sNewGameSlotMenuWork->palette4, NULL, SPRITE_PRIORITY(1), 80);
        DrawSprite(72, 96, gDona2Fl00Frames[0], sNewGameSlotMenuWork->tiles5, sNewGameSlotMenuWork->palette5, NULL,
            SPRITE_PRIORITY(1) | SPRITE_FLAG_HFLIP, 81);
        DrawSprite(40, 96, gGoofy2Fl00Frames[0], sNewGameSlotMenuWork->tiles6, sNewGameSlotMenuWork->palette6, NULL,
            SPRITE_PRIORITY(1), 81);
    } else {
        DrawSprite(56, 112, gRikuFf00Frames[0], sNewGameSlotMenuWork->tiles7, sNewGameSlotMenuWork->palette7, NULL,
            SPRITE_PRIORITY(1), 81);
    }

    DrawSprite(0, 16, gSaveSlotCharaWinFrame0, sNewGameSlotMenuWork->tiles3, sNewGameSlotMenuWork->palette3, NULL, SPRITE_PRIORITY(1), 90);
    t = 45;
    u = sNewGameSlotMenuWork->selectedSlot * t;
    ApproachValueHalf(&sNewGameSlotMenuWork->y3, (sNewGameSlotMenuWork->slotBaseY + u) << 8);
    DrawSprite(76, sNewGameSlotMenuWork->y3 >> 8, AnimGetGfx(&sNewGameSlotMenuWork->anim),
        sNewGameSlotMenuWork->tiles, sNewGameSlotMenuWork->palette, NULL, 0, 70);
    DrawTextSlots(100, u + (sNewGameSlotMenuWork->slotBaseY + 22), sNewGameSlotMenuWork->textSlots,
        sNewGameSlotMenuWork->palette8, 50, sNewGameSlotMenuWork->textSlotCount);
    DrawTextSlots(
        (240 - GetTextSlotsWidth(sNewGameSlotMenuWork->textSlots2, sNewGameSlotMenuWork->textSlotCount2)) / 2, 134,
        sNewGameSlotMenuWork->textSlots2, sNewGameSlotMenuWork->palette9, 50, sNewGameSlotMenuWork->textSlotCount2);
}

void NewGameSlotMenuMoveCursor(NewGameSlotMenuWork* work) {
    u8 prev = work->selectedSlot;

    if (GetKeysRepeat() & DPAD_UP) {
        work->selectedSlot = work->selectedSlot != 0 ? work->selectedSlot - 1 : 1;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysRepeat() & DPAD_DOWN) {
        work->selectedSlot = work->selectedSlot == 0 ? work->selectedSlot + 1 : 0;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (prev != work->selectedSlot) {
        NewGameSlotMenuDeselectSlot(prev);
        NewGameSlotMenuSelectSlot(work->selectedSlot);
    }
}

void NewGameSlotMenuSlideIn(NewGameSlotMenuWork* work) {
    if (work->timer != 0) {
        ApproachValue(&work->y, 0, work->timer);
        ApproachValue(&work->y2, 0x9800, work->timer);
        work->timer--;
    } else {
        work->update = NewGameSlotMenuInput;
    }
}

void NewGameSlotMenuInput(NewGameSlotMenuWork* work) {
    NewGameSlotMenuMoveCursor(work);

    if (GetKeysPressed() & B_BUTTON) {
        m4aSongNumStart(SONG_SYS_CLOSE);
    } else {
        if (!(GetKeysPressed() & (A_BUTTON | START_BUTTON))) {
            return;
        }

        switch (work->selectedSlot) {
        case 0:
            gGameState.flags &= ~GAME_FLAG_SECOND_FILE;
            break;
        case 1:
            gGameState.flags |= GAME_FLAG_SECOND_FILE;
            break;
        }

        m4aSongNumStart(SONG_SYS_SAVELOAD);
        work->confirmed = 1;
    }

    work->timer = 16;
    work->update = NewGameSlotMenuSlideOut;
}

void NewGameSlotMenuSlideOut(NewGameSlotMenuWork* work) {
    if (work->timer != 0) {
        ApproachValue(&work->y, -0x800, work->timer);
        ApproachValue(&work->y2, 0xA000, work->timer);
        work->timer--;
    } else {
        FadeStartOut(FADE_MODE_BLACK, 90);
        work->update = NewGameSlotMenuExit;
    }
}

void NewGameSlotMenuExit(NewGameSlotMenuWork* work) {
    if (FadeIsActive()) {
        return;
    }

    if (work->confirmed) {
        if (work->isRiku != 0) {
            SetupRikuNewGame();
#ifdef VERSION_EU
            RequestEventMode(0x93);
#else
            RequestEventMode(0x95);
#endif
        } else {
            SetupSoraNewGame();
            ModeRequestHeapReset(&gModeMovie, 1);
        }
    } else {
        ModeRequest(&gModeTitle, 0);
    }
}

void Mode_MenuNew_0() {
    u8 v;
    u8 u;

    sNewGameSlotMenuWork = EwramAlloc(sizeof(NewGameSlotMenuWork));
    sNewGameSlotMenuWork->confirmed = 0;
    sNewGameSlotMenuWork->isRiku = (gGameState.flags >> 3) & 1;
    sNewGameSlotMenuWork->slotBaseY = 33;
    sNewGameSlotMenuWork->timer = 16;
    sNewGameSlotMenuWork->update = NewGameSlotMenuSlideIn;
    SetBgMode0();
    SetupBg(3, 0, 28, 0);
    SetupBg(1, 0, 29, 0);
    SetupBg(0, 0, 30, 0);
    SetBgPriority(3, 3);
    SetBgPriority(1, 0);
    SetBgPriority(0, 0);
#ifdef VERSION_EU
    LoadBgTiles(0, gSaveSlotBgTiles, 0x1FA0);

    switch (gLanguage) {
    case LANGUAGE_FRENCH:
        RequestDma3Copy((void*)gSaveSlotLabelsFrenchTiles, (u8*)GetBgCharBase(0) + 0x800, 0x800);
        break;
    case LANGUAGE_SPANISH:
        RequestDma3Copy((void*)gSaveSlotLabelsSpanishTiles, (u8*)GetBgCharBase(0) + 0x800, 0x800);
        break;
    case LANGUAGE_ITALIAN:
        RequestDma3Copy((void*)gSaveSlotLabelsItalianTiles, (u8*)GetBgCharBase(0) + 0x800, 0x800);
        break;
    case LANGUAGE_GERMAN:
        RequestDma3Copy((void*)gSaveSlotLabelsGermanTiles, (u8*)GetBgCharBase(0) + 0x800, 0x800);
        break;
    }

    LoadBgPalette(3, gMenuNewBgPalette, 0x200);
    LoadBgMap(3, gMenuNewMaps, 0x800);
    LoadBgPalette(1, gMenuNewBgPalette, 0x200);
#else
    LoadBgTiles(3, gSaveSlotBgTiles, 0x1FA0);
    LoadBgPalette(3, gMenuNewBgPalette, 0x200);
    LoadBgMap(3, gMenuNewMaps, 0x800);
    LoadBgTiles(1, gSaveSlotBgTiles, 0x1FA0);
    LoadBgPalette(1, gMenuNewBgPalette, 0x200);
    LoadBgTiles(0, gSaveSlotBgTiles, 0x1FA0);
#endif
    LoadBgPalette(0, gMenuNewBgPalette, 0x200);
    LoadBgMap(0, gMenuNewMsgWinMap, 0x800);
    SetBgScroll(0, 0, 0xFFFC);
    sNewGameSlotMenuWork->palette2 = LoadObjPalette(gSaveMenuTitlePalette, 32);
    sNewGameSlotMenuWork->tiles2 = LoadObjTiles(gMapSaveTitleTiles, 0x2C0);
    sNewGameSlotMenuWork->y = -0x800;
    sNewGameSlotMenuWork->y2 = 0xA000;
    sNewGameSlotMenuWork->tiles4 = AllocObjTiles(0x340, gSor1ff00Tiles);
    sNewGameSlotMenuWork->palette4 = LoadObjPalette(gSoraPalette, 32);
    sNewGameSlotMenuWork->tiles5 = AllocObjTiles(0x280, gDona2Fl00Tiles);
    sNewGameSlotMenuWork->palette5 = LoadObjPalette(gDonald2Palette, 32);
    sNewGameSlotMenuWork->tiles6 = AllocObjTiles(0x400, gGoofy2Fl00Tiles);
    sNewGameSlotMenuWork->palette6 = LoadObjPalette(gGoofy2Palette, 32);
    sNewGameSlotMenuWork->tiles7 = AllocObjTiles(0x400, gRikuFf00Tiles);
    sNewGameSlotMenuWork->palette7 = LoadObjPalette(gRikuPalette, 32);
    sNewGameSlotMenuWork->palette3 = LoadObjPalette(gFileMenuWindowPalette, 32);
    sNewGameSlotMenuWork->tiles3 = LoadObjTiles(gSaveSlotCharaWinTiles, 0x4C0);
    sNewGameSlotMenuWork->palette = LoadObjPalette(gFileMenuCursorPalette, 32);
    sNewGameSlotMenuWork->tiles = AllocObjTiles(0x120, gSaveSlotCursorTiles);
    AnimInit(&sNewGameSlotMenuWork->anim, gSaveSlotCursorAnims, gSaveSlotCursorFrames);
    AnimStart(&sNewGameSlotMenuWork->anim, 0, ANIM_FLAG_LOOP);
    sNewGameSlotMenuWork->palette8 = LoadObjPalette(gSaveFloorSoraPalette, 32);
    sNewGameSlotMenuWork->textSlotCount = 0;
    InitTextSlots(sNewGameSlotMenuWork->textSlots, 36);
    InitTextSlots(sNewGameSlotMenuWork->textSlots2, 54);
    sNewGameSlotMenuWork->palette9 = LoadObjPalette(gFileMenuCursorPalette, 32);
#ifdef VERSION_EU
    sNewGameSlotMenuWork->textSlotCount2 = LoadTextSlots(GetLocalizedString(&gNewGameSlotMenuTextByLanguage), sNewGameSlotMenuWork->textSlots2);
#else
    sNewGameSlotMenuWork->textSlotCount2 = LoadTextSlots(gNewGameSlotMenuText, sNewGameSlotMenuWork->textSlots2);
#endif

    if (sNewGameSlotMenuWork->isRiku != 0) {
        v = NewGameSlotMenuShowSummary(2);
        u = NewGameSlotMenuShowSummary(3);
    } else {
        v = NewGameSlotMenuShowSummary(0);
        u = NewGameSlotMenuShowSummary(1);
    }

    if (v) {
        sNewGameSlotMenuWork->selectedSlot = !u ? 1 : 0;
    } else {
        sNewGameSlotMenuWork->selectedSlot = 0;
    }

    NewGameSlotMenuSelectSlot(sNewGameSlotMenuWork->selectedSlot);
    sNewGameSlotMenuWork->y3 = (sNewGameSlotMenuWork->slotBaseY + sNewGameSlotMenuWork->selectedSlot * 45) << 8;
    FadeStartIn(FADE_MODE_BLACK, 8);
}

void Mode_MenuNew_1() {
    if (sNewGameSlotMenuWork->update != NULL) {
        sNewGameSlotMenuWork->update(sNewGameSlotMenuWork);
    }

    NewGameSlotMenuDraw();
}

void Mode_MenuNew_2() {
    ReleaseObjPalette(sNewGameSlotMenuWork->palette2);
    ReleaseObjTiles(sNewGameSlotMenuWork->tiles2);
    ReleaseObjPalette(sNewGameSlotMenuWork->palette3);
    ReleaseObjTiles(sNewGameSlotMenuWork->tiles3);
    ReleaseObjPalette(sNewGameSlotMenuWork->palette);
    ReleaseObjTiles(sNewGameSlotMenuWork->tiles);
    ReleaseObjPalette(sNewGameSlotMenuWork->palette4);
    ReleaseObjTiles(sNewGameSlotMenuWork->tiles4);
    ReleaseObjPalette(sNewGameSlotMenuWork->palette5);
    ReleaseObjTiles(sNewGameSlotMenuWork->tiles5);
    ReleaseObjPalette(sNewGameSlotMenuWork->palette6);
    ReleaseObjTiles(sNewGameSlotMenuWork->tiles6);
    ReleaseObjPalette(sNewGameSlotMenuWork->palette7);
    ReleaseObjTiles(sNewGameSlotMenuWork->tiles7);
    ReleaseObjPalette(sNewGameSlotMenuWork->palette8);
    FreeTextSlots(sNewGameSlotMenuWork->textSlots, 36);
    ReleaseObjPalette(sNewGameSlotMenuWork->palette9);
    FreeTextSlots(sNewGameSlotMenuWork->textSlots2, 54);
    EwramFree(sNewGameSlotMenuWork);
}

s32 LoadGameMenuLoadFile(u8 a) {
    switch (a) {
    case 0:
        if (SaveRepairFileLarge(0) == SAVE_OK) {
            SaveLoadFileLarge(0);
            return 1;
        }

        break;
    case 1:
        if (SaveRepairFileLarge(1) == SAVE_OK) {
            SaveLoadFileLarge(1);
            return 1;
        }

        break;
    case 2:
        if (SaveRepairFileSmall(0) == SAVE_OK) {
            SaveLoadFileSmall(0);
            InitRikuDeckForWorld(gGameState.world);
            return 1;
        }

        break;
    case 3:
        if (SaveRepairFileSmall(1) == SAVE_OK) {
            SaveLoadFileSmall(1);
            InitRikuDeckForWorld(gGameState.world);
            return 1;
        }

        break;
    }

    return 0;
}

void LoadGameMenuLoadFloorTiles(u8 a, u8 b, u8 c) {
    const u8* src;

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        if (a <= 1) {
            if (b) {
                src = gSaveSlotSoraFloorSelectedTiles[c];
            } else {
                src = gSaveSlotSoraFloorTiles[c];
            }
        } else {
            if (b) {
                src = gSaveSlotRikuFloorSelectedTiles[c];
            } else {
                src = gSaveSlotRikuFloorTiles[c];
            }
        }

        break;
    case LANGUAGE_FRENCH:
        if (a <= 1) {
            if (b) {
                src = gSaveSlotSoraFloorSelectedFrenchTiles[c];
            } else {
                src = gSaveSlotSoraFloorFrenchTiles[c];
            }
        } else {
            if (b) {
                src = gSaveSlotRikuFloorSelectedFrenchTiles[c];
            } else {
                src = gSaveSlotRikuFloorFrenchTiles[c];
            }
        }

        break;
    case LANGUAGE_SPANISH:
        if (a <= 1) {
            if (b) {
                src = gSaveSlotSoraFloorSelectedSpanishTiles[c];
            } else {
                src = gSaveSlotSoraFloorSpanishTiles[c];
            }
        } else {
            if (b) {
                src = gSaveSlotRikuFloorSelectedSpanishTiles[c];
            } else {
                src = gSaveSlotRikuFloorSpanishTiles[c];
            }
        }

        break;
    case LANGUAGE_ITALIAN:
        if (a <= 1) {
            if (b) {
                src = gSaveSlotSoraFloorSelectedItalianTiles[c];
            } else {
                src = gSaveSlotSoraFloorItalianTiles[c];
            }
        } else {
            if (b) {
                src = gSaveSlotRikuFloorSelectedItalianTiles[c];
            } else {
                src = gSaveSlotRikuFloorItalianTiles[c];
            }
        }

        break;
    case LANGUAGE_GERMAN:
    default:
        if (a <= 1) {
            if (b) {
                src = gSaveSlotSoraFloorSelectedGermanTiles[c];
            } else {
                src = gSaveSlotSoraFloorGermanTiles[c];
            }
        } else {
            if (b) {
                src = gSaveSlotRikuFloorSelectedGermanTiles[c];
            } else {
                src = gSaveSlotRikuFloorGermanTiles[c];
            }
        }

        break;
    }
#else
    if (a <= 1) {
        if (b) {
            src = gSaveSlotSoraFloorSelectedTiles[c];
        } else {
            src = gSaveSlotSoraFloorTiles[c];
        }
    } else {
        if (b) {
            src = gSaveSlotRikuFloorSelectedTiles[c];
        } else {
            src = gSaveSlotRikuFloorTiles[c];
        }
    }
#endif

    RequestDma3Copy((void*)src, (u8*)GetBgCharBase(1) + (a * 608 + 320), 320);
}

void LoadGameMenuLoadLevelTiles(u8 a, u16 v) {
    u16 d[4];
    s32 off;
    u16* q;
    s32 i;

    d[0] = v / 100;
    d[1] = v / 10 - d[0] * 10;
    d[2] = v - d[0] * 100 - d[1] * 10;
    i = 1;
    off = a * 608 + 32;
    q = &d[1];

    while (i <= 2) {
        RequestDma3Copy((void*)&gSaveSlotDigitTiles[*q * 32], (u8*)GetBgCharBase(1) + off + i * 32, 0x20);
        q++;
        i++;
    }
}

void LoadGameMenuLoadTimeTiles(u8 a, u32 v) {
    u16 d[6];
    s32 off;
    u16* q;
    s32 i;
    u32 t;

    t = v / 3600;
    d[0] = t / 10;
    d[1] = t - d[0] * 10;
    v -= t * 3600;
    t = v / 60;
    d[2] = t / 10;
    d[3] = t - d[2] * 10;
    v -= t * 60;
    d[4] = v / 10;
    d[5] = v - d[4] * 10;
    i = 0;
    off = a * 608 + 128;
    q = d;

    while (i <= 5) {
        RequestDma3Copy((void*)&gSaveSlotDigitTiles[*q * 32], (u8*)GetBgCharBase(1) + off + i * 32, 0x20);
        q++;
        i++;
    }
}

void LoadGameMenuShowSummary(u8 a) {
    SaveFileSummary* e = &gGameState.fileSummaries[a];

    if (e->level != 0) {
        LoadGameMenuLoadLevelTiles(a, e->level);
        LoadGameMenuLoadTimeTiles(a, e->playTime);
        LoadGameMenuLoadFloorTiles(a, 0, e->floor);
    } else {
        LoadGameMenuLoadFloorTiles(a, 0, 13);
    }
}

void LoadGameMenuSelectSlot(u8 a) {
    SaveFileSummary* e = &gGameState.fileSummaries[a];

    if (e->level != 0) {
        LoadGameMenuLoadFloorTiles(a, 1, e->floor);
        sLoadGameMenuWork->textSlotCount = LoadTextSlots(GetMapWorldName(e->world), sLoadGameMenuWork->textSlots);

        if (a <= 1) {
            LoadObjPaletteBank(sLoadGameMenuWork->palette7->index, gSaveFloorSoraPalette);
        } else {
            LoadObjPaletteBank(sLoadGameMenuWork->palette7->index, gSaveFloorRikuPalette);
        }
    } else {
        LoadGameMenuLoadFloorTiles(a, 1, 13);
        sLoadGameMenuWork->textSlotCount = 0;
    }
}

void LoadGameMenuDeselectSlot(u8 a) {
    SaveFileSummary* e = &gGameState.fileSummaries[a];

    if (e->level != 0) {
        LoadGameMenuLoadFloorTiles(a, 0, e->floor);
    } else {
        LoadGameMenuLoadFloorTiles(a, 0, 13);
    }

    sLoadGameMenuWork->textSlotCount = 0;
}

void LoadGameMenuDraw() {
    s32 t;
    s32 u;

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        DrawSprite(128, sLoadGameMenuWork->y >> 8, gMenuLoadTitleFrames[1], sLoadGameMenuWork->tiles2,
            sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(128, sLoadGameMenuWork->y2 >> 8, gMenuLoadTitleFrames[2], sLoadGameMenuWork->tiles2,
            sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(sLoadGameMenuWork->x >> 8, 0, gMenuLoadTitleFrames[0], sLoadGameMenuWork->tiles2,
            sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 80);
        break;
    case LANGUAGE_FRENCH:
        DrawSprite(128, sLoadGameMenuWork->y >> 8, gMenuLoadTitleFrenchFrames[1], sLoadGameMenuWork->tiles2,
            sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(128, sLoadGameMenuWork->y2 >> 8, gMenuLoadTitleFrenchFrames[2], sLoadGameMenuWork->tiles2,
            sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(sLoadGameMenuWork->x >> 8, 0, gMenuLoadTitleFrenchFrames[0], sLoadGameMenuWork->tiles2,
            sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 80);
        break;
    case LANGUAGE_SPANISH:
        DrawSprite(128, sLoadGameMenuWork->y >> 8, gMenuLoadTitleSpanishFrames[1], sLoadGameMenuWork->tiles2,
            sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(128, sLoadGameMenuWork->y2 >> 8, gMenuLoadTitleSpanishFrames[2], sLoadGameMenuWork->tiles2,
            sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(sLoadGameMenuWork->x >> 8, 0, gMenuLoadTitleSpanishFrames[0], sLoadGameMenuWork->tiles2,
            sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 80);
        break;
    case LANGUAGE_ITALIAN:
        DrawSprite(128, sLoadGameMenuWork->y >> 8, gMenuLoadTitleItalianFrames[1], sLoadGameMenuWork->tiles2,
            sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(128, sLoadGameMenuWork->y2 >> 8, gMenuLoadTitleItalianFrames[2], sLoadGameMenuWork->tiles2,
            sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(sLoadGameMenuWork->x >> 8, 0, gMenuLoadTitleItalianFrames[0], sLoadGameMenuWork->tiles2,
            sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 80);
        break;
    case LANGUAGE_GERMAN:
    default:
        DrawSprite(128, sLoadGameMenuWork->y >> 8, gMenuLoadTitleGermanFrames[1], sLoadGameMenuWork->tiles2,
            sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(128, sLoadGameMenuWork->y2 >> 8, gMenuLoadTitleGermanFrames[2], sLoadGameMenuWork->tiles2,
            sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(sLoadGameMenuWork->x >> 8, 0, gMenuLoadTitleGermanFrames[0], sLoadGameMenuWork->tiles2,
            sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 80);
        break;
    }
#else
    DrawSprite(128, sLoadGameMenuWork->y >> 8, gMenuLoadTitleFrames[1], sLoadGameMenuWork->tiles2,
        sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
    DrawSprite(128, sLoadGameMenuWork->y2 >> 8, gMenuLoadTitleFrames[2], sLoadGameMenuWork->tiles2,
        sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
    DrawSprite(sLoadGameMenuWork->x >> 8, 0, gMenuLoadTitleFrames[0], sLoadGameMenuWork->tiles2,
        sLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 80);
#endif

    if (sLoadGameMenuWork->selectedSlot <= 1) {
        DrawSprite(56, 112, gSor1ff00Frames[0], sLoadGameMenuWork->tiles3,
            sLoadGameMenuWork->palette3, NULL, SPRITE_PRIORITY(1), 80);
        DrawSprite(72, 96, gDonaFl00Frames[0], sLoadGameMenuWork->tiles4,
            sLoadGameMenuWork->palette4, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_HFLIP, 81);
        DrawSprite(40, 96, gGoofyFl00Frames[0], sLoadGameMenuWork->tiles5,
            sLoadGameMenuWork->palette5, NULL, SPRITE_PRIORITY(1), 81);
    } else {
        DrawSprite(56, 112, gRikuFf00Frames[0], sLoadGameMenuWork->tiles6, sLoadGameMenuWork->palette6, NULL,
            SPRITE_PRIORITY(1), 81);
    }

    if (sLoadGameMenuWork->showRikuSlots != 0) {
        t = 32;
    } else {
        t = 45;
    }

    u = t * sLoadGameMenuWork->selectedSlot;
    ApproachValueHalf(&sLoadGameMenuWork->y3, (sLoadGameMenuWork->slotBaseY + u) << 8);
    DrawSprite(76, sLoadGameMenuWork->y3 >> 8, AnimGetGfx(&sLoadGameMenuWork->anim),
        sLoadGameMenuWork->tiles, sLoadGameMenuWork->palette, NULL, SPRITE_PRIORITY(1), 70);
    DrawTextSlots(100, u + (sLoadGameMenuWork->slotBaseY + 22), sLoadGameMenuWork->textSlots,
        sLoadGameMenuWork->palette7, 50, sLoadGameMenuWork->textSlotCount);
}

void LoadGameMenuMoveCursor(LoadGameMenuWork* work) {
    u8 old = work->selectedSlot;

    if (GetKeysRepeat() & DPAD_UP) {
        work->selectedSlot = work->selectedSlot != 0 ? work->selectedSlot - 1 : work->lastSlot;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysRepeat() & DPAD_DOWN) {
        work->selectedSlot = work->selectedSlot < work->lastSlot ? work->selectedSlot + 1 : 0;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (old != work->selectedSlot) {
        LoadGameMenuDeselectSlot(old);
        LoadGameMenuSelectSlot(work->selectedSlot);

        switch (work->selectedSlot) {
        case 0:
            if (work->showRikuSlots != 0) {
                LoadBgMap(1, gMenuLoadFourSlotMaps, 0x800);
                SetBgScroll(1, 0, (u16)-1);
            } else {
                LoadBgMap(1, gMenuLoadTwoSlotMaps, 0x800);
                SetBgScroll(1, 0, (u16)-3);
            }

            break;
        case 1:
            if (work->showRikuSlots != 0) {
                LoadBgMap(1, &gMenuLoadFourSlotMaps[0x400], 0x800);
                SetBgScroll(1, 0, (u16)-1);
            } else {
                LoadBgMap(1, &gMenuLoadTwoSlotMaps[0x400], 0x800);
                SetBgScroll(1, 0, 0);
            }

            break;
        case 2:
            LoadBgMap(1, &gMenuLoadFourSlotMaps[0x800], 0x800);
            SetBgScroll(1, 0, (u16)-1);
            break;
        case 3:
            LoadBgMap(1, &gMenuLoadFourSlotMaps[0xC00], 0x800);
            SetBgScroll(1, 0, (u16)-1);
            break;
        }
    }
}

void LoadGameMenuSlideInY(LoadGameMenuWork* work) {
    if (work->timer != 0) {
        ApproachValue(&work->y, 0, work->timer);
        ApproachValue(&work->y2, 0x9800, work->timer);
        work->timer--;
    } else {
        work->timer = 16;
        work->update = LoadGameMenuSlideInX;
    }
}

void LoadGameMenuSlideInX(LoadGameMenuWork* work) {
    if (work->timer != 0) {
        ApproachValue(&work->x, 0, work->timer);
        work->timer--;
    } else {
        work->update = LoadGameMenuInput;
    }
}

void LoadGameMenuInput(LoadGameMenuWork* work) {
    LoadGameMenuMoveCursor(work);

    if (GetKeysPressed() & B_BUTTON) {
        work->timer = 16;
        work->update = LoadGameMenuSlideOutX;
        m4aSongNumStart(SONG_SYS_CLOSE);
    } else if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
        if ((u8)LoadGameMenuLoadFile(work->selectedSlot)) {
            switch (work->selectedSlot) {
            case 0:
                gGameState.flags &= ~GAME_FLAG_RIKU;
                gGameState.flags &= ~GAME_FLAG_SECOND_FILE;
                break;
            case 1:
                gGameState.flags &= ~GAME_FLAG_RIKU;
                gGameState.flags |= GAME_FLAG_SECOND_FILE;
                break;
            case 2:
                gGameState.flags |= GAME_FLAG_RIKU;
                gGameState.flags &= ~GAME_FLAG_SECOND_FILE;
                break;
            case 3:
                gGameState.flags |= GAME_FLAG_RIKU;
                gGameState.flags |= GAME_FLAG_SECOND_FILE;
                break;
            }

            m4aSongNumStart(SONG_SYS_SAVELOAD);
            work->loaded = 1;
            work->timer = 16;
            work->update = LoadGameMenuSlideOutX;
        } else {
            m4aSongNumStart(SONG_SYS_BEEP);
        }
    }
}

void LoadGameMenuSlideOutX(LoadGameMenuWork* work) {
    if (work->timer != 0) {
        ApproachValue(&work->x, -0x8000, work->timer);
        work->timer--;
    } else {
        work->timer = 16;
        work->update = LoadGameMenuSlideOutY;
    }
}

void LoadGameMenuSlideOutY(LoadGameMenuWork* work) {
    if (work->timer != 0) {
        ApproachValue(&work->y, -0x800, work->timer);
        ApproachValue(&work->y2, 0xA000, work->timer);
        work->timer--;
    } else {
        FadeStartOut(FADE_MODE_BLACK, 16);
        work->update = LoadGameMenuExit;
    }
}

void LoadGameMenuExit(LoadGameMenuWork* work) {
#ifdef VERSION_EU
    SaveFileSummary* e = &gGameState.fileSummaries[work->selectedSlot];
#endif

    if (FadeIsActive()) {
        return;
    }

    if (work->forSioBattle) {
        if (work->loaded) {
            ModeRequest(&gModeSioBattle, 1);
        } else {
            ModeRequest(&gModeSioBattle, 0);
        }
    } else if (work->loaded) {
#ifdef VERSION_EU
        if (e->world != WORLD_100_ACRE_WOOD) {
#else
        if (gMapFloorState.world != WORLD_100_ACRE_WOOD) {
#endif
            RequestMapMode();
        } else {
            ModeRequest(&gModePooh, 2);
        }
    } else {
        ModeRequest(&gModeTitle, 0);
    }
}

void Mode_MenuLoad_0(s32 arg) {
    s32 i;

    sLoadGameMenuWork = EwramAlloc(sizeof(LoadGameMenuWork));
    sLoadGameMenuWork->forSioBattle = arg != 0;

    if (sLoadGameMenuWork->forSioBattle) {
        sLoadGameMenuWork->showRikuSlots = 0;
    } else {
        sLoadGameMenuWork->showRikuSlots = (gGameState.flags >> 5) & 1;
    }

    sLoadGameMenuWork->loaded = 0;
    sLoadGameMenuWork->selectedSlot = 0;

    if (sLoadGameMenuWork->showRikuSlots != 0) {
        sLoadGameMenuWork->lastSlot = 3;
        sLoadGameMenuWork->slotBaseY = 17;
        sLoadGameMenuWork->y3 = sLoadGameMenuWork->slotBaseY << 8;
    } else {
        sLoadGameMenuWork->lastSlot = 1;
        sLoadGameMenuWork->slotBaseY = 43;
        sLoadGameMenuWork->y3 = sLoadGameMenuWork->slotBaseY << 8;
    }

    sLoadGameMenuWork->timer = 16;
    sLoadGameMenuWork->update = LoadGameMenuSlideInY;
    SetBgMode0();
    SetupBg(3, 0, 28, 0);
    SetupBg(2, 0, 29, 0);
    SetupBg(1, 0, 30, 0);
    SetupBg(0, 3, 31, 0);
#ifdef VERSION_EU
    LoadBgTiles(1, gMenuLoadBgTiles, 0x8000);

    switch (gLanguage) {
    case LANGUAGE_FRENCH:
        RequestDma3Copy(gMenuLoadLabelsFrenchTiles, (u8*)GetBgCharBase(1) + 0xC00, 0x800);
        break;
    case LANGUAGE_SPANISH:
        RequestDma3Copy((void*)gMenuLoadLabelsSpanishTiles, (u8*)GetBgCharBase(1) + 0xC00, 0x800);
        break;
    case LANGUAGE_ITALIAN:
        RequestDma3Copy((void*)gMenuLoadLabelsItalianTiles, (u8*)GetBgCharBase(1) + 0xC00, 0x800);
        break;
    case LANGUAGE_GERMAN:
        RequestDma3Copy((void*)gMenuLoadLabelsGermanTiles, (u8*)GetBgCharBase(1) + 0xC00, 0x800);
        break;
    }

    LoadBgPalette(3, gLoadMenuBgPalettes, 0x200);
    LoadBgMap(3, gMenuLoadBackdropMap, 0x800);
    LoadBgPalette(2, gLoadMenuBgPalettes, 0x200);
    LoadBgMap(2, gMenuLoadCharaWinMap, 0x800);
#else
    LoadBgTiles(3, gMenuLoadBgTiles, 0x8000);
    LoadBgPalette(3, gLoadMenuBgPalettes, 0x200);
    LoadBgMap(3, gMenuLoadBackdropMap, 0x800);
    LoadBgTiles(2, gMenuLoadBgTiles, 0x8000);
    LoadBgPalette(2, gLoadMenuBgPalettes, 0x200);
    LoadBgMap(2, gMenuLoadCharaWinMap, 0x800);
    LoadBgTiles(1, gMenuLoadBgTiles, 0x8000);
#endif
    LoadBgPalette(1, gLoadMenuBgPalettes, 0x200);

    if (sLoadGameMenuWork->showRikuSlots != 0) {
        LoadBgMap(1, gMenuLoadFourSlotMaps, 0x800);
        SetBgScroll(1, 0, 0xFFFF);
    } else {
        LoadBgMap(1, gMenuLoadTwoSlotMaps, 0x800);
        SetBgScroll(1, 0, 0xFFFD);
    }

    sLoadGameMenuWork->palette2 = LoadObjPalette(gLoadMenuTitlePalette, 32);

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        sLoadGameMenuWork->tiles2 = LoadObjTiles(gMenuLoadTitleTiles, 0x2C0);
        break;
    case LANGUAGE_FRENCH:
        sLoadGameMenuWork->tiles2 = LoadObjTiles(gMenuLoadTitleFrenchTiles, 0x300);
        break;
    case LANGUAGE_SPANISH:
        sLoadGameMenuWork->tiles2 = LoadObjTiles(gMenuLoadTitleSpanishTiles, 0x2C0);
        break;
    case LANGUAGE_ITALIAN:
        sLoadGameMenuWork->tiles2 = LoadObjTiles(gMenuLoadTitleItalianTiles, 0x2C0);
        break;
    case LANGUAGE_GERMAN:
    default:
        sLoadGameMenuWork->tiles2 = LoadObjTiles(gMenuLoadTitleGermanTiles, 0x2C0);
        break;
    }
#else
    sLoadGameMenuWork->tiles2 = LoadObjTiles(gMenuLoadTitleTiles, 0x2C0);
#endif
    sLoadGameMenuWork->y = -0x800;
    sLoadGameMenuWork->y2 = 0xA000;
    sLoadGameMenuWork->x = -0x8000;
    sLoadGameMenuWork->tiles3 = AllocObjTiles(0x340, gSor1ff00Tiles);
    sLoadGameMenuWork->palette3 = LoadObjPalette(gSoraPalette, 32);
    sLoadGameMenuWork->tiles4 = AllocObjTiles(0x280, gDonaFl00Tiles);
    sLoadGameMenuWork->palette4 = LoadObjPalette(gDonaldPalette, 32);
    sLoadGameMenuWork->tiles5 = AllocObjTiles(0x400, gGoofyFl00Tiles);
    sLoadGameMenuWork->palette5 = LoadObjPalette(gGoofyPalette, 32);
    sLoadGameMenuWork->tiles6 = AllocObjTiles(0x400, gRikuFf00Tiles);
    sLoadGameMenuWork->palette6 = LoadObjPalette(gRikuPalette, 32);
    sLoadGameMenuWork->palette = LoadObjPalette(gFileMenuCursorPalette, 32);
    sLoadGameMenuWork->tiles = AllocObjTiles(0x120, gSaveSlotCursorTiles);
    AnimInit(&sLoadGameMenuWork->anim, gSaveSlotCursorAnims, gSaveSlotCursorFrames);
    AnimStart(&sLoadGameMenuWork->anim, 0, ANIM_FLAG_LOOP);
    sLoadGameMenuWork->palette7 = LoadObjPalette(gSaveFloorSoraPalette, 32);
    sLoadGameMenuWork->textSlotCount = 0;
    InitTextSlots(sLoadGameMenuWork->textSlots, 36);

    for (i = 0; i < 4; i++) {
        LoadGameMenuShowSummary(i);
    }

    LoadGameMenuSelectSlot(sLoadGameMenuWork->selectedSlot);
    FadeStartIn(FADE_MODE_BLACK, 16);
}

void Mode_MenuLoad_1() {
    if (sLoadGameMenuWork->update != NULL) {
        sLoadGameMenuWork->update(sLoadGameMenuWork);
    }

    LoadGameMenuDraw();
}

void Mode_MenuLoad_2() {
    ReleaseObjPalette(sLoadGameMenuWork->palette2);
    ReleaseObjTiles(sLoadGameMenuWork->tiles2);
    ReleaseObjPalette(sLoadGameMenuWork->palette);
    ReleaseObjTiles(sLoadGameMenuWork->tiles);
    ReleaseObjPalette(sLoadGameMenuWork->palette3);
    ReleaseObjTiles(sLoadGameMenuWork->tiles3);
    ReleaseObjPalette(sLoadGameMenuWork->palette4);
    ReleaseObjTiles(sLoadGameMenuWork->tiles4);
    ReleaseObjPalette(sLoadGameMenuWork->palette5);
    ReleaseObjTiles(sLoadGameMenuWork->tiles5);
    ReleaseObjPalette(sLoadGameMenuWork->palette6);
    ReleaseObjTiles(sLoadGameMenuWork->tiles6);
    ReleaseObjPalette(sLoadGameMenuWork->palette7);
    FreeTextSlots(sLoadGameMenuWork->textSlots, 36);
    EwramFree(sLoadGameMenuWork);
}

void MenuMsgWaitMessage(MenuMsgWork* work) {
    if (!IsMessageWindowOpen()) {
        if (work->toTitle == 0) {
            BackdropFadeStartOut(1, 16);
            FadeStartOut(FADE_MODE_WHITE, 16);
        } else {
            BackdropFadeStartOut(0, 16);
            FadeStartOut(FADE_MODE_BLACK, 16);
        }

        work->update = MenuMsgWaitFade;
    }
}

void MenuMsgWaitFade(MenuMsgWork* work) {
    if (!FadeIsActive()) {
        if (work->toTitle == 0) {
            ModeRequest(&gModeCopyright1, 0);
        } else {
            ModeRequest(&gModeTitle, 0);
        }
    }
}

void Mode_MenuMsg_0(s32 arg) {
    sMenuMsgWork = EwramAlloc(sizeof(MenuMsgWork));
    sMenuMsgWork->toTitle = arg;
    SetBgMode0();
    TaskPoolInit(&sMenuMsgWork->tasks, 1);

    if (sMenuMsgWork->toTitle == 0) {
        CreateSysmsgwinTask(&sMenuMsgWork->tasks, 0xB0);
        BackdropFadeReset();
        BackdropFadeSetColor(0, 0, 0);
        BackdropFadeStartIn(1, 16);
        FadeStartIn(FADE_MODE_WHITE, 16);
        FadeLock();
    } else {
#ifdef VERSION_EU
        CreateSysmsgwinTask(&sMenuMsgWork->tasks, 0xB2);
#else
        CreateSysmsgwinTask(&sMenuMsgWork->tasks, 0xB3);
#endif
        BackdropFadeReset();
        BackdropFadeSetColor(0, 0, 0);
        BackdropFadeStartIn(0, 1);
        FadeStartIn(FADE_MODE_BLACK, 1);
        FadeLock();
    }

    sMenuMsgWork->update = MenuMsgWaitMessage;
}

void Mode_MenuMsg_1() {
    sMenuMsgWork->update(sMenuMsgWork);
    TaskPoolUpdate(&sMenuMsgWork->tasks);
    TaskPoolDraw(&sMenuMsgWork->tasks);
    BackdropFadeUpdate();
}

void Mode_MenuMsg_2() {
    TaskPoolDestroy(&sMenuMsgWork->tasks);
    EwramFree(sMenuMsgWork);
}

void Task_MapRnd_0(MapRndWork* work) {
    MapRoomDef* r = gMapRoomDefs[gMapFloorState.world];
    s32 i;

    TaskPoolInit(&work->tasks, 4);
    LoadBgTiles(3, r->tiles, r->tilesSize);
    LoadBgTiles(2, r->tiles, r->tilesSize);
    LoadBgTiles(1, r->tiles2, r->tilesSize2);
    LoadBgPalette(3, r->palette, r->paletteSize);
    LoadBgPalette(2, r->palette, r->paletteSize);
    LoadBgPalette(1, r->palette, r->paletteSize);
    gMapRoomState->cols = GetRandomMapWidth();
    gMapRoomState->rows = 64;
    gFieldState->tileCols = gMapRoomState->cols * 4;
    gFieldState->tileRows = gMapRoomState->rows * 2;
    MapGenerateRoom(gMapRoomState->cols, gMapRoomState->rows);

    for (i = 0; i < 4; i++) {
        MapDoor* e = GetMapDoor(i);

        if (e->flags & DOOR_FLAG_PRESENT) {
            if ((e->flags & DOOR_FLAG_SEALED) == 0) {
                TaskCreate(&work->tasks, &gTaskDescMapDoor, e);
            }
        }
    }
}

s32 Task_MapRnd_1(MapRndWork* work) {
    MapUpdateCamera(gFieldState->x2, gFieldState->y2);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void Task_MapRnd_2(MapRndWork* work) {
    TaskPoolDraw(&work->tasks);
}

void Task_MapRnd_3(MapRndWork* work) {
    TaskPoolDestroy(&work->tasks);
    MapFreeRoom();
}

void MapFixInitColliders(MapFixWork* work, MapFixedCollider* q) {
    s32 i;

    work->colliderCount = 0;

    if (q != NULL) {
        i = 0;

        do {
            if (q->radius != 0) {
                ColliderInit(&work->colliders[i], 6, q->radius, 0xA0);
                ColliderSetPosition(&work->colliders[i], q->x, q->y, 0);
                work->colliderCount++;
            } else {
                break;
            }

            q++;
            i++;
        } while (i < 5);
    }
}

void Task_MapFix_0(MapFixWork* work, MapFixedDef* p) {
    FldObj v;

    switch (gMapFloorState.entrySide) {
    case 0:
        gFieldState->spawnAngle = 173;
        gFieldState->spawnX = p->stairX - 0xC00;
        gFieldState->spawnY = p->stairY + 0x800;
        break;
    case 1:
        gFieldState->spawnAngle = 45;
        gFieldState->spawnX = p->stair2X + 0xC00;
        gFieldState->spawnY = p->stair2Y - 0x800;
        break;
    default:
        gFieldState->spawnAngle = 45;
        gFieldState->spawnX = p->spawnX;
        gFieldState->spawnY = p->spawnY;
        break;
    }

#ifdef VERSION_EU
    work->bg1MapLoaded = 0;
    work->bg2MapLoaded = 0;
    work->bg3MapLoaded = 0;

    if (p->rawTiles == 0) {
        LoadBgTilesLz77(3, p->tiles);
    } else {
        LoadBgTiles(3, p->tiles, p->tilesSize);
    }
#else
    LoadBgTiles(3, p->tiles, p->tilesSize);
#endif
    LoadBgPalette(3, p->palette, p->paletteSize);
#ifdef VERSION_EU
    SetBgMapBlocksLz77(3, p->map3, p->mapWidth, p->mapHeight);
    work->bg3MapLoaded = 1;
#else
    SetBgMapBlocks(3, p->map3, p->mapWidth, p->mapHeight);
#endif

    if (p->map2 != NULL) {
#ifdef VERSION_EU
        if (p->rawTiles == 0) {
            LoadBgTilesLz77(2, p->tiles);
        } else {
            LoadBgTiles(2, p->tiles, p->tilesSize);
        }
#else
        LoadBgTiles(2, p->tiles, p->tilesSize);
#endif
        LoadBgPalette(2, p->palette, p->paletteSize);
#ifdef VERSION_EU
        SetBgMapBlocksLz77(2, p->map2, p->mapWidth, p->mapHeight);
        work->bg2MapLoaded = 1;
#else
        SetBgMapBlocks(2, p->map2, p->mapWidth, p->mapHeight);
#endif
    } else {
        DisableBg(2);
    }

    if (p->map != NULL) {
#ifdef VERSION_EU
        if (p->rawTiles == 0) {
            LoadBgTilesLz77(1, p->tiles2);
        } else {
            LoadBgTiles(1, p->tiles2, p->tilesSize2);
        }
#else
        LoadBgTiles(1, p->tiles2, p->tilesSize2);
#endif
        LoadBgPalette(1, p->palette, p->paletteSize);
#ifdef VERSION_EU
        SetBgMapBlocksLz77(1, p->map, p->mapWidth, p->mapHeight);
        work->bg1MapLoaded = 1;
#else
        SetBgMapBlocks(1, p->map, p->mapWidth, p->mapHeight);
#endif
    } else {
        DisableBg(1);
    }

    gFieldState->tileCols = p->mapWidth * 32;
    gFieldState->tileRows = p->mapHeight * 32;
    gMapRoomState->cols = gFieldState->tileCols / 4;
    gMapRoomState->rows = gFieldState->tileRows / 2;
    MapFixInitCells(p);
    TaskPoolInit(&work->tasks, 2);
    v.fieldPosition.x = p->stairX;
    v.fieldPosition.y = p->stairY;
    v.angle = 45;
    TaskCreate(&work->tasks, &gTaskDescMapStair, &v);

    if (p->stair2X != 0 || p->stair2Y != 0) {
        v.fieldPosition.x = p->stair2X;
        v.fieldPosition.y = p->stair2Y;
        v.angle = 173;
        TaskCreate(&work->tasks, &gTaskDescMapStair, &v);
    }

    MapFixInitColliders(work, p->colliders);
}

s32 Task_MapFix_1(MapFixWork* work) {
    s32 tx = gFieldState->x2 - 0x7800;
    s32 ty = gFieldState->y2 - 0x6000;

    gFieldState->x += (tx - gFieldState->x) / 8;
    gFieldState->y += (ty - gFieldState->y) / 8;

    if (gFieldState->x < 0) {
        gFieldState->x = 0;
    }

    if (gFieldState->y < 0) {
        gFieldState->y = 0;
    }

    if (gFieldState->x + 0xF000 > gFieldState->tileCols << 11) {
        gFieldState->x = (gFieldState->tileCols << 11) - 0xF000;
    }

    if (gFieldState->y + 0xA000 > gFieldState->tileRows << 11) {
        gFieldState->y = (gFieldState->tileRows << 11) - 0xA000;
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void Task_MapFix_2(MapFixWork* work) {
    ScrollBgMapTo(3, gFieldState->x >> 8, gFieldState->y >> 8);
    ScrollBgMapTo(2, gFieldState->x >> 8, gFieldState->y >> 8);

    if ((gMapRoomState->flags & ROOM_FLAG_BG1_FROZEN) == 0) {
        ScrollBgMapTo(1, gFieldState->x >> 8, gFieldState->y >> 8);
    }

    TaskPoolDraw(&work->tasks);
}

void Task_MapFix_3(MapFixWork* work) {
    s32 i;

    for (i = 0; i < work->colliderCount; i++) {
        ColliderUnregister(&work->colliders[i]);
    }

#ifdef VERSION_EU
    if (work->bg3MapLoaded) {
        FreeBgDecompressedMap(3);
    }

    if (work->bg2MapLoaded) {
        FreeBgDecompressedMap(2);
    }

    if (work->bg1MapLoaded) {
        FreeBgDecompressedMap(1);
    }
#endif

    TaskPoolDestroy(&work->tasks);
    MapFixFreeCells();
}

void MapDoorShowOpen(MapDoorWork* work) {
    UpdateSpriteFrameTiles(work->tiles, work->sprite, work->openSrc);
    UpdateSpriteFrameTiles(work->tiles2, work->sprite2, work->openSrc2);
}

void MapDoorShowClosed(MapDoorWork* work) {
    UpdateSpriteFrameTiles(work->tiles, work->sprite, work->closedSrc);
    UpdateSpriteFrameTiles(work->tiles2, work->sprite2, work->closedSrc2);
}

u8 MapDoorWaitHit(MapDoorWork* work) {
    MapDoor* flags = work->door;
    FldObj* e = &work->obj;

    if (!(gFieldState->flags & FIELD_FLAG_MENU_OPEN) && !(gMapRoomState->flags & (ROOM_FLAG_ENEMY_STRUCK | ROOM_FLAG_TUTORIAL_ACTIVE)) &&
        (u8)(flags->room + 3) > 1 && (flags->flags & (DOOR_FLAG_OPEN | DOOR_FLAG_EVENT)) != (DOOR_FLAG_OPEN | DOOR_FLAG_EVENT) &&
        IsHitByMapAttack(&e->fieldPosition, 0, 8) && !(gFieldState->flags & FIELD_FLAG_PLAYER_JUMPING) &&
        gFieldState->actor.fieldPosition.z == gFieldState->actor.fieldPosition.ground) {
        TaskPool* pool;

        m4aSongNumStart(SONG_SND_220);
        pool = &work->tasks;
        TaskCreate(pool, &gTaskDescMapSpark, e);
        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        gFieldState->lockonTarget = e;
        gMapRoomState->door = e;
        work->triggered = 1;
        work->update = MapDoorWaitCard;
        gMapRoomState->doorRoom = flags->room;
        gMapRoomState->doorSide = flags->side;
        FadeSetPaletteExcluded(work->palette->index + 16, 1);
        FadeSetPaletteExcluded(work->palette2->index + 16, 1);
        TaskCreate(pool, &gTaskDescRoomcreate, NULL);
    }

    return 1;
}

u8 MapDoorWaitCard(MapDoorWork* work) {
    MapDoor* flags = work->door;
    void* t = GetSelectedMapCard();

    if (t != NULL) {
        if (flags->flags & DOOR_FLAG_EVENT) {
            CreateMapRoom(flags->room, NULL);
        } else {
            CreateMapRoom(flags->room, t);
        }

        work->update = MapDoorWaitOpen;
    }

    if (!(gFieldState->flags & FIELD_FLAG_ROOM_CREATE)) {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        FadeSetPaletteExcluded(work->palette->index + 16, 0);
        FadeSetPaletteExcluded(work->palette2->index + 16, 0);
        work->update = MapDoorWaitHit;
    }

    return 1;
}

u8 MapDoorWaitOpen(MapDoorWork* work) {
    MapDoor* flags = work->door;
    u16 v;

    if (gFieldState->flags & FIELD_FLAG_DOOR_OPENED) {
        MapDoorShowOpen(work);
        v = flags->flags | DOOR_FLAG_OPEN;
        flags->flags = v;
        work->update = MapDoorIdle;
    }

    return 1;
}

u8 MapDoorIdle(MapDoorWork* work) {
    return 1;
}

void Task_MapDoor_0(MapDoorWork* work, MapDoor* p) {
    FldObj* e = &work->obj;
    FldPos* v = &e->fieldPosition;
    const MapDoorGfx* q = &gWorldMapDoorGfx[gMapFloorState.world];

    work->door = p;
    work->triggered = 0;
    work->visible = 1;

    switch (p->side) {
    case 0:
        work->sprite = gMapDoorSide0Frame0;
        work->openSrc = q->side0Open;
        work->closedSrc = q->side0Closed;
        e->angle = 173;
        work->obj.fieldPosition.x = (p->cellX << 5) + 16;
        e->fieldPosition.y = (p->cellY << 4) + 10;
        break;
    case 1:
        work->sprite = gMapDoorSide1Frame0;
        work->openSrc = q->side1Open;
        work->closedSrc = q->side1Closed;
        e->angle = 45;
        work->obj.fieldPosition.x = (p->cellX << 5) + 16;
        e->fieldPosition.y = (p->cellY << 4) + 6;
        break;
    case 2:
        work->sprite = gMapDoorSide2Frame0;
        work->openSrc = q->side2Open;
        work->closedSrc = q->side2Closed;
        e->angle = 211;
        work->obj.fieldPosition.x = (p->cellX << 5) + 16;
        e->fieldPosition.y = (p->cellY << 4) + 6;
        break;
    case 3:
        work->sprite = gMapDoorSide3Frame0;
        work->openSrc = q->side3Open;
        work->closedSrc = q->side3Closed;
        e->angle = 83;
        work->obj.fieldPosition.x = (p->cellX << 5) + 16;
        e->fieldPosition.y = (p->cellY << 4) + 10;
        break;
    }

    v->x <<= 8;
    v->y <<= 8;
    v->z = 0;
    v->z = v->ground = GetFldPosFloor(v);
    v->y -= v->z;
    e->height = 32;
    e->kind = 3;
    work->tiles = AllocSpriteFrameTiles(0x400);
    work->palette = LoadObjPalette(q->palette, 32);
    work->palette2 = LoadObjPalette(gMapDoorEmblemPalette, 32);
    work->tiles2 = AllocSpriteFrameTiles(0x100);

    switch (p->side) {
    case 0:
    case 1:
        work->sprite2 = gMapDoorEmblemSide01Frame0;
        work->openSrc2 = gMapDoorEmblemTiles[0][1];
        work->closedSrc2 = gMapDoorEmblemTiles[1][1];
        break;
    case 2:
    case 3:
        work->sprite2 = gMapDoorEmblemSide23Frame0;
        work->openSrc2 = gMapDoorEmblemTiles[0][0];
        work->closedSrc2 = gMapDoorEmblemTiles[1][0];
        break;
    }

    if (p->flags & DOOR_FLAG_OPEN) {
        work->update = MapDoorWaitHit;
        MapDoorShowOpen(work);
    } else {
        work->update = MapDoorWaitHit;
        MapDoorShowClosed(work);
    }

    TaskPoolInit(&work->tasks, 2);
}

s32 Task_MapDoor_1(MapDoorWork* work) {
    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        if (!work->triggered) {
            work->visible = 0;
        }
    } else {
        work->triggered = 0;
        work->visible = 1;
    }

    if (work->update != NULL) {
        if (work->update(work) == 0) {
            return 0;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void Task_MapDoor_2(MapDoorWork* work) {
    MapDoor* f = work->door;
    u16 sx;
    u16 sy;
    u16 v;
    u16 t;
    s32 k;

    if (work->visible == 1) {
        sx = (work->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
        k = work->obj.fieldPosition.y >> 8;
        sy = k + (work->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);

        switch (f->side) {
        case 0:
        case 3:
            v = -0xFE4 - (work->obj.fieldPosition.y >> 8) * 4;
            break;
        case 1:
        case 2:
            v = -0x1024 - k * 4;
            break;
        default:
            v = 0;
            break;
        }

        t = 0x800;
        DrawSprite(sx, sy, NULL, work->tiles, work->palette, NULL, t, v);

        if (f->flags & DOOR_FLAG_EVENT) {
            switch (f->side) {
            case 0:
            case 2:
                DrawSprite(sx, sy, NULL, work->tiles2, work->palette2, NULL, t, v - 1);
                break;
            case 1:
            case 3:
                DrawSprite(sx, sy, NULL, work->tiles2, work->palette2, NULL, t, v - 1);
                break;
            }
        }

        TaskPoolDraw(&work->tasks);
    }
}

void Task_MapDoor_3(MapDoorWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette2);
    TaskPoolDestroy(&work->tasks);
}

void MapMenuSetPanelPalettesExcluded(MapMenuWork* work, u8 a) {
    s32 i;

    FadeSetPaletteExcluded(work->palette3->index + 0x10, a);
    FadeSetPaletteExcluded(work->palette8->index + 0x10, a);
    FadeSetPaletteExcluded(work->palette4->index + 0x10, a);
    FadeSetPaletteExcluded(work->palette5->index + 0x10, a);
    FadeSetPaletteExcluded(work->palette->index + 0x10, a);

    for (i = 0; i < 3; i++) {
        if (work->palette9[i] != NULL) {
            FadeSetPaletteExcluded(work->palette9[i]->index + 0x10, a);
        }
    }
}

void MapMenuSetCharaPalettesExcluded(MapMenuWork* work, u8 a) {
    FadeSetPaletteExcluded(work->palette2->index + 0x10, a);
    FadeSetPaletteExcluded(work->palette6->index + 0x10, a);
    FadeSetPaletteExcluded(work->palette7->index + 0x10, a);
}

void MapMenuWriteDigits3(ObjTiles* p, u8 a, u16 v) {
    u16 d[3];
    u16* q;
    s32 i;

    d[0] = v / 100;
    d[1] = v / 10 - d[0] * 10;
    d[2] = v - d[0] * 100 - d[1] * 10;

    for (i = 0, q = d; i < 3; i++) {
        RequestDma3Copy((void*)&gMapMenuDigitTiles[*q * 32], (void*)(OBJ_VRAM0 + (p->index + a + i) * 32), 0x20);
        q++;
    }
}

void MapMenuWriteDigits5(ObjTiles* p, u8 a, u32 v) {
    u16 d[5];
    u16* q;
    s32 i;

    d[0] = v / 10000;
    d[1] = v / 1000 - d[0] * 10;
    d[2] = v / 100 - d[0] * 100 - d[1] * 10;
    d[3] = v / 10 - d[0] * 1000 - d[1] * 100 - d[2] * 10;
    d[4] = v - d[0] * 10000 - d[1] * 1000 - d[2] * 100 - d[3] * 10;

    for (i = 0, q = d; i < 5; i++) {
        RequestDma3Copy((void*)&gMapMenuDigitTiles[*q * 32], (void*)(OBJ_VRAM0 + (p->index + a + i) * 32), 0x20);
        q++;
    }
}

void MapMenuInitConfirm(MapMenuWork* work) {
    TextSlot* p1;
    TextSlot* p2;
    TextSlot* p3;

    LoadBgTiles(0, gConfirmWinTiles, 0x140);
    LoadBgMap(0, gConfirmWinMap, 0x800);
    LoadPalette(gCard00Palette, &gUnk_050001C0[0x20], 0x20);
    FadeSetPaletteExcluded(15, 1);
    SetBgScroll(0, 0, 0);
    work->confirmPalette = LoadTextPalette(1);
    p1 = work->textSlots2;
#ifdef VERSION_EU
    InitTextSlots(p1, 66);
    p2 = work->textSlots3;
    InitTextSlots(p2, 6);
    p3 = work->textSlots4;
    InitTextSlots(p3, 9);
    work->textSlotCount2 = LoadTextSlots(GetLocalizedString(&gMapQuickSaveConfirmTextByLanguage), p1);
    work->textSlotCount3 = LoadTextSlots(GetLocalizedString(&gYesChoiceTextByLanguage), p2);
    work->textSlotCount4 = LoadTextSlots(GetLocalizedString(&gNoChoiceTextByLanguage), p3);
#else
    InitTextSlots(p1, 33);
    p2 = work->textSlots3;
    InitTextSlots(p2, 6);
    p3 = work->textSlots4;
    InitTextSlots(p3, 9);
    work->textSlotCount2 = LoadTextSlots(gMapQuickSaveConfirmText, p1);
    work->textSlotCount3 = LoadTextSlots(gYesChoiceText, p2);
    work->textSlotCount4 = LoadTextSlots(gNoChoiceText, p3);
#endif
}

void MapMenuFreeConfirm(MapMenuWork* work) {
    FadeSetPaletteExcluded(15, 0);
    DisableBg(0);
    ReleaseObjPalette(work->confirmPalette);
#ifdef VERSION_EU
    FreeTextSlots(work->textSlots2, 0x42);
#else
    FreeTextSlots(work->textSlots2, 0x21);
#endif
    FreeTextSlots(work->textSlots3, 6);
    FreeTextSlots(work->textSlots4, 9);
}

s32 MapMenuOpen(MapMenuWork* work) {
    work->palette2 = LoadObjPalette(gMapMenuBarPalette, 32);
    work->tiles2 = LoadObjTiles(gMapMenuBarsTiles, 0x80);
    work->y = -0x800;
    work->y2 = 0xA000;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        work->tiles8 = AllocObjTiles(0x400, gRikuFf00Tiles);
    } else {
        work->tiles8 = AllocObjTiles(0x340, gSor1ff00Tiles);
    }

    work->tiles7 = LoadObjTiles(gBtlShadowTiles, 0x100);
    work->palette7 = LoadObjPalette(gCommonObjPalette, 32);
    work->playerStartX = gFieldState->actor.fieldPosition.x - gFieldState->x;
    work->playerStartY = gFieldState->actor.fieldPosition.y + gFieldState->actor.fieldPosition.z - gFieldState->y;
    work->x8 = work->playerStartX;
    work->y4 = work->playerStartY;
    work->cursor = gGameState.mapMenuCursor;
    work->confirmCursor = 0;
    work->cursorVisible = 0;
    work->panelsVisible = 0;
    work->steps = work->reopened ? 1 : 16;
    work->update = MapMenuSlideInY;
    MapMenuSetCharaPalettesExcluded(work, 1);

    if (!work->reopened) {
        FadeToAmount(FADE_MODE_BLACK, 16, 16);
    }

    return 1;
}

s32 MapMenuSlideInY(MapMenuWork* work) {
    if (work->steps != 0) {
        ApproachValue(&work->y, 0, work->steps);
        ApproachValue(&work->y2, 0x9800, work->steps);
        work->steps--;
    } else {
        s32 i;

        gMapRoomState->flags |= ROOM_FLAG_HIDE_PLAYER;
        gFieldState->flags |= FIELD_FLAG_HIDE_ENEMIES;

#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            work->tiles5 = LoadObjTiles(gMapMenuStatusTiles, 0x1BC0);
            break;
        case LANGUAGE_FRENCH:
            work->tiles5 = LoadObjTiles(gMapMenuStatusFrenchTiles, 0x1BC0);
            break;
        case LANGUAGE_SPANISH:
            work->tiles5 = LoadObjTiles(gMapMenuStatusSpanishTiles, 0x1BC0);
            break;
        case LANGUAGE_ITALIAN:
            work->tiles5 = LoadObjTiles(gMapMenuStatusItalianTiles, 0x1BC0);
            break;
        case LANGUAGE_GERMAN:
        default:
            work->tiles5 = LoadObjTiles(gMapMenuStatusGermanTiles, 0x1BC0);
            break;
        }
#else
        work->tiles5 = LoadObjTiles(gMapMenuStatusTiles, 0x1BC0);
#endif
        work->palette3 = LoadObjPalette(gMapMenuStatusPalette, 32);
        work->x3 = 0x11800;
        work->x4 = 0xF000;
        work->x5 = 0x10000;
        MapMenuWriteDigits3(work->tiles5, 0, gGameState.progression.level);
        MapMenuWriteDigits3(work->tiles5, 6, gGameState.progression.maxHp);
        MapMenuWriteDigits3(work->tiles5, 3, gGameState.hp);

        if (gGameState.flags & GAME_FLAG_RIKU) {
            MapMenuWriteDigits3(work->tiles5, 9, gGameState.progression.dp);
        } else {
            MapMenuWriteDigits5(work->tiles5, 9, gGameState.progression.mooglePoints);
        }

        work->palette4 = LoadObjPalette(gMapMenuHighlightPalette, 32);
        work->palette5 = LoadObjPalette(gMapMenuPanelPalette, 32);

#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            if (gGameState.flags & GAME_FLAG_RIKU) {
                work->tiles6 = LoadObjTiles(gMapMenuRikuCommandsTiles, 0x1500);
            } else {
                work->tiles6 = LoadObjTiles(gMapMenuSoraCommandsTiles, 0x1500);
            }

            break;
        case LANGUAGE_FRENCH:
            if (gGameState.flags & GAME_FLAG_RIKU) {
                work->tiles6 = LoadObjTiles(gMapMenuRikuCommandsFrenchTiles, 0x1500);
            } else {
                work->tiles6 = LoadObjTiles(gMapMenuSoraCommandsFrenchTiles, 0x1500);
            }

            break;
        case LANGUAGE_SPANISH:
            if (gGameState.flags & GAME_FLAG_RIKU) {
                work->tiles6 = LoadObjTiles(gMapMenuRikuCommandsSpanishTiles, 0x1500);
            } else {
                work->tiles6 = LoadObjTiles(gMapMenuSoraCommandsSpanishTiles, 0x1500);
            }

            break;
        case LANGUAGE_ITALIAN:
            if (gGameState.flags & GAME_FLAG_RIKU) {
                work->tiles6 = LoadObjTiles(gMapMenuRikuCommandsItalianTiles, 0x1500);
            } else {
                work->tiles6 = LoadObjTiles(gMapMenuSoraCommandsItalianTiles, 0x1500);
            }

            break;
        case LANGUAGE_GERMAN:
        default:
            if (gGameState.flags & GAME_FLAG_RIKU) {
                work->tiles6 = LoadObjTiles(gMapMenuRikuCommandsGermanTiles, 0x1500);
            } else {
                work->tiles6 = LoadObjTiles(gMapMenuSoraCommandsGermanTiles, 0x1500);
            }

            break;
        }
#else
        if (gGameState.flags & GAME_FLAG_RIKU) {
            work->tiles6 = LoadObjTiles(gMapMenuRikuCommandsTiles, 0x1500);
        } else {
            work->tiles6 = LoadObjTiles(gMapMenuSoraCommandsTiles, 0x1500);
        }
#endif

        work->x6 = -0x7800;
        work->palette = LoadObjPalette(gMapMenuCursorPalette, 32);
        work->tiles = AllocObjTiles(0x120, gMapMenuCursorTiles);
        AnimInit(&work->anim, gMapMenuCursorAnims, gMapMenuCursorFrames);
        AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);

        for (i = 0; i < 3; i++) {
            work->tiles9[i] = NULL;
            work->palette9[i] = NULL;
            work->gfx[i] = NULL;
        }

        LoadFriendCardSprites(work->tiles9, (void**)work->palette9, work->gfx);
        InitTextSlots(work->textSlots, 24);
        work->palette8 = LoadTextPalette(1);
        work->textSlotCount = LoadTextSlots(GetDeckName(GetActiveDeckIndex()), work->textSlots);

#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            work->tiles3 = LoadObjTiles(gMapMenuTitleTiles, 0x200);
            break;
        case LANGUAGE_FRENCH:
            work->tiles3 = LoadObjTiles(gMapMenuTitleTiles, 0x200);
            break;
        case LANGUAGE_SPANISH:
            work->tiles3 = LoadObjTiles(gMapMenuTitleSpanishTiles, 0x200);
            break;
        case LANGUAGE_ITALIAN:
            work->tiles3 = LoadObjTiles(gMapMenuTitleTiles, 0x200);
            break;
        case LANGUAGE_GERMAN:
        default:
            work->tiles3 = LoadObjTiles(gMapMenuTitleGermanTiles, 0x200);
            break;
        }
#else
        work->tiles3 = LoadObjTiles(gMapMenuTitleTiles, 0x200);
#endif
        work->x = -0x8000;
        work->tiles4 = LoadObjTiles(gMapMenuCharaWinTiles, 0x300);
        work->x2 = 0xF800;
        MapMenuSetPanelPalettesExcluded(work, 1);
        work->panelsVisible = 1;
        work->steps = work->reopened ? 1 : 16;
        work->update = MapMenuSlideInX;
    }

    return 1;
}

s32 MapMenuSlideInX(MapMenuWork* work) {
    if (work->steps != 0) {
        ApproachValue(&work->x, 0, work->steps);
        ApproachValue(&work->x6, 0x800, work->steps);
        ApproachValue(&work->x2, 0x7800, work->steps);
        ApproachValue(&work->x3, 0x9800, work->steps);
        ApproachValue(&work->x4, 0x7000, work->steps);
        ApproachValue(&work->x5, 0x8000, work->steps);
        ApproachValue(&work->x8, 0xAC00, work->steps);
        ApproachValue(&work->y4, 0x6000, work->steps);
        work->steps--;
    } else {
        work->cursorVisible = 1;
        work->y3 = (work->cursor * 19 + 16) << 8;

        if (work->reopened) {
            work->reopened = 0;
            FadeToAmount(FADE_MODE_BLACK, 16, 1);
            work->update = MapMenuResume;
        } else {
            work->update = (gGameState.flags & GAME_FLAG_RIKU) ? MapMenuRikuInput : MapMenuSoraInput;
        }
    }

    return 1;
}

s32 MapMenuSoraInput(MapMenuWork* work) {
    if (GetKeysRepeat() & DPAD_UP) {
        work->cursor = work->cursor != 0 ? work->cursor - 1 : 6;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysRepeat() & DPAD_DOWN) {
        work->cursor = work->cursor <= 5 ? work->cursor + 1 : 0;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysPressed() & (B_BUTTON | START_BUTTON)) {
        work->cursorVisible = 0;
        work->steps = 16;
        work->update = MapMenuSlideOutX;
        m4aSongNumStart(SONG_SYS_CLOSE);
    } else if (GetKeysPressed() & A_BUTTON) {
        switch (work->cursor) {
        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
            RequestFieldResume();
            work->update = MapMenuOpenSubMode;
            m4aSongNumStart(SONG_SYS_KETTEI);
            break;
        case 1:
            if ((u8)(gMapFloorState.room + 4) > 2) {
                RequestFieldResume();
                work->update = MapMenuOpenSubMode;
                m4aSongNumStart(SONG_SYS_KETTEI);
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }

            break;
        case 6:
            m4aSongNumStart(SONG_SYS_KETTEI);
            MapMenuInitConfirm(work);
            work->confirmCursor = 2;
            work->x7 = 0x8800;
            work->update = MapMenuConfirmInput;
            break;
        }
    }

    return 1;
}

s32 MapMenuRikuInput(MapMenuWork* work) {
    if (GetKeysRepeat() & DPAD_UP) {
        work->cursor = work->cursor != 0 ? work->cursor - 1 : 6;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysRepeat() & DPAD_DOWN) {
        work->cursor = work->cursor <= 5 ? work->cursor + 1 : 0;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysPressed() & (B_BUTTON | START_BUTTON)) {
        work->cursorVisible = 0;
        work->steps = 16;
        work->update = MapMenuSlideOutX;
        m4aSongNumStart(SONG_SYS_CLOSE);
    } else if (GetKeysPressed() & A_BUTTON) {
        switch (work->cursor) {
        case 0:
        case 2:
        case 3:
        case 4:
            m4aSongNumStart(SONG_SYS_KETTEI);
            RequestFieldResume();
            work->update = MapMenuOpenSubMode;
            break;
        case 5:
            m4aSongNumStart(SONG_SYS_KETTEI);
            RequestFieldResume();
            work->update = MapMenuOpenSubMode;
            break;
        case 1:
            if ((u8)(gMapFloorState.room + 4) > 2) {
                m4aSongNumStart(SONG_SYS_KETTEI);
                RequestFieldResume();
                work->update = MapMenuOpenSubMode;
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }

            break;
        case 6:
            m4aSongNumStart(SONG_SYS_KETTEI);
            MapMenuInitConfirm(work);
            work->confirmCursor = 2;
            work->x7 = 0x8800;
            work->update = MapMenuConfirmInput;
            break;
        }
    }

    return 1;
}

s32 MapMenuOpenSubMode(MapMenuWork* work) {
    gGameState.mapMenuCursor = work->cursor;

    switch (work->cursor) {
    case 0:
        if (gGameState.flags & GAME_FLAG_RIKU) {
            if (gGameState.progression.tutorialFlags & 0x800) {
                ModeRequest(&gModeDeck, 0);
            } else {
                ModeRequest(&gModeRikuDeckTutorial, 0);
            }
        } else {
            ModeRequest(&gModeDeck, 0);
        }

        break;
    case 1:
        ModeRequest(&gModeAllmap, 0);
        break;
    case 4:
        ModeRequest(&gModeStatus, 0);
        break;
    case 2:
        ModeRequest(&gModeMapinspect, 0);
        break;
    case 3:
        ModeRequest(&gModeWorldinspect, 0);
        break;
    case 5:
        ModeRequest(&gModeJiminy, 0);
        break;
    case 6:
        ModeRequest(&gModeMenuMsg, 1);
        break;
    }

    return 1;
}

s32 MapMenuSlideOutX(MapMenuWork* work) {
    if (work->steps != 0) {
        ApproachValue(&work->x, -0x8000, work->steps);
        ApproachValue(&work->x6, -0x7800, work->steps);
        ApproachValue(&work->x2, 0xF800, work->steps);
        ApproachValue(&work->x3, 0x11800, work->steps);
        ApproachValue(&work->x4, 0xF000, work->steps);
        ApproachValue(&work->x5, 0x10000, work->steps);
        ApproachValue(&work->x8, work->playerStartX, work->steps);
        ApproachValue(&work->y4, work->playerStartY, work->steps);
        work->steps--;
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_HIDE_PLAYER;
        gFieldState->flags &= ~FIELD_FLAG_HIDE_ENEMIES;
        MapMenuSetPanelPalettesExcluded(work, 0);
        FadeToOriginal(FADE_MODE_BLACK, 16);
        work->steps = 16;
        work->update = MapMenuSlideOutY;
    }

    return 1;
}

s32 MapMenuSlideOutY(MapMenuWork* work) {
    if (work->steps != 0) {
        ApproachValue(&work->y, -0x800, work->steps);
        ApproachValue(&work->y2, 0xA000, work->steps);
        work->steps--;
        return 1;
    }

    gGameState.mapMenuCursor = 0xFF;
    m4aMPlayVolumeControl(&gMPlayInfo_BGM, 0xFF, 0x100);
    return 0;
}

s32 MapMenuConfirmInput(MapMenuWork* work) {
    if (GetKeysPressed() & DPAD_LEFT) {
        if (work->confirmCursor != 1) {
            work->confirmCursor = 1;
            m4aSongNumStart(SONG_SYS_CLICK);
        }
    }

    if (GetKeysPressed() & DPAD_RIGHT) {
        if (work->confirmCursor != 2) {
            work->confirmCursor = 2;
            m4aSongNumStart(SONG_SYS_CLICK);
        }
    }

    if ((GetKeysPressed() & B_BUTTON) || ((GetKeysPressed() & A_BUTTON) && work->confirmCursor == 2)) {
        work->confirmCursor = 0;
        MapMenuFreeConfirm(work);
        work->y3 = (work->cursor * 19 + 16) << 8;
        work->update = (gGameState.flags & GAME_FLAG_RIKU) ? MapMenuRikuInput : MapMenuSoraInput;
        m4aSongNumStart(SONG_SYS_CLOSE);
    } else if (GetKeysPressed() & A_BUTTON) {
        SaveWriteSystem();
        work->update = MapMenuOpenSubMode;
        m4aSongNumStart(SONG_SYS_KETTEI);
    }

    return 1;
}

s32 MapMenuResume(MapMenuWork* work) {
    gDispCnt |= DISPCNT_OBJ_ON;
    work->update = (gGameState.flags & GAME_FLAG_RIKU) ? MapMenuRikuInput : MapMenuSoraInput;
    return 1;
}

void Task_MapMenu_0(MapMenuWork* work) {
    s8 v;

    gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
    gFieldState->flags |= FIELD_FLAG_FREEZE_ENEMIES;
    gFieldState->flags |= FIELD_FLAG_MENU_OPEN;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        work->palette6 = LoadObjPalette(gRikuPalette, 32);
    } else {
        work->palette6 = LoadObjPalette(gSoraPalette, 32);
    }

    FadeSetPaletteExcluded(work->palette6->index + 0x10, 1);
    v = gGameState.mapMenuCursor;

    if (v != -1) {
        work->reopened = 1;
    } else {
        gGameState.mapMenuCursor = 0;
        work->reopened = 0;
        m4aSongNumStart(SONG_SYS_CANSEL);
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, 0xFF, 0x80);
    }

    work->update = MapMenuOpen;
}

s32 Task_MapMenu_1(MapMenuWork* work) {
    if (work->reopened) {
        FadeStartIn(FADE_MODE_BLACK, 16);
    }

    if (work->panelsVisible) {
        AnimUpdate(&work->anim);
    }

    if (work->update != NULL && (u8)work->update(work) == 0) {
        return 0;
    }

    return 1;
}

void Task_MapMenu_2(MapMenuWork* work) {
    s32 i;
    s32 k;

    DrawSprite(128, work->y >> 8, gMapMenuBarsFrames[0], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 90);
    DrawSprite(128, work->y2 >> 8, gMapMenuBarsFrames[1], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 90);

    if (
#ifdef VERSION_EU
        work->confirmCursor == 0 &&
#endif
        (gMapRoomState->flags & ROOM_FLAG_HIDE_PLAYER)) {
        if (gGameState.flags & GAME_FLAG_RIKU) {
            DrawSprite(work->x8 >> 8, work->y4 >> 8, gRikuFf00Frames[0], work->tiles8, work->palette6,
                NULL, SPRITE_PRIORITY(1), 80);
        } else {
            DrawSprite(work->x8 >> 8, work->y4 >> 8, gSor1ff00Frames[0], work->tiles8,
                work->palette6, NULL, SPRITE_PRIORITY(1), 80);
        }

        DrawSprite(work->x8 >> 8, work->y4 >> 8, gBtlShadowFrames[0], work->tiles7, work->palette7, NULL,
            SPRITE_PRIORITY(1), 81);
    }

    if (work->panelsVisible) {
#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_SPANISH:
            DrawSprite(work->x >> 8, 0, gMapMenuTitleSpanishFrames[0], work->tiles3, work->palette2, NULL, SPRITE_PRIORITY(1), 80);
            break;
        case LANGUAGE_ENGLISH:
        case LANGUAGE_FRENCH:
        case LANGUAGE_ITALIAN:
            DrawSprite(work->x >> 8, 0, gMapMenuTitleFrames[0], work->tiles3, work->palette2, NULL, SPRITE_PRIORITY(1), 80);
            break;
        case LANGUAGE_GERMAN:
        default:
            DrawSprite(work->x >> 8, 0, gMapMenuTitleGermanFrames[0], work->tiles3, work->palette2, NULL, SPRITE_PRIORITY(1), 80);
            break;
        }
#else
        DrawSprite(work->x >> 8, 0, gMapMenuTitleFrames[0], work->tiles3, work->palette2, NULL, SPRITE_PRIORITY(1), 80);
#endif
        DrawSprite(work->x2 >> 8, 14, gMapMenuCharaWinFrames[0], work->tiles4, work->palette2, NULL, SPRITE_PRIORITY(1), 90);

        if (gGameState.flags & GAME_FLAG_RIKU) {
#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                DrawSprite(work->x3 >> 8, 0, gMapMenuRikuStatusFrames[0], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(work->x3 >> 8, 0, gMapMenuRikuStatusFrames[1], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(work->x4 >> 8, 103, gMapMenuRikuStatusFrames[2], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_FRENCH:
                DrawSprite(work->x3 >> 8, 0, gMapMenuRikuStatusFrenchFrames[0], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(work->x3 >> 8, 0, gMapMenuRikuStatusFrenchFrames[1], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(work->x4 >> 8, 103, gMapMenuRikuStatusFrenchFrames[2], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_SPANISH:
                DrawSprite(work->x3 >> 8, 0, gMapMenuRikuStatusSpanishFrames[0], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(work->x3 >> 8, 0, gMapMenuRikuStatusSpanishFrames[1], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(work->x4 >> 8, 103, gMapMenuRikuStatusSpanishFrames[2], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_ITALIAN:
                DrawSprite(work->x3 >> 8, 0, gMapMenuRikuStatusItalianFrames[0], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(work->x3 >> 8, 0, gMapMenuRikuStatusItalianFrames[1], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(work->x4 >> 8, 103, gMapMenuRikuStatusItalianFrames[2], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_GERMAN:
            default:
                DrawSprite(work->x3 >> 8, 0, gMapMenuRikuStatusGermanFrames[0], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(work->x3 >> 8, 0, gMapMenuRikuStatusGermanFrames[1], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(work->x4 >> 8, 103, gMapMenuRikuStatusGermanFrames[2], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            }
#else
            DrawSprite(work->x3 >> 8, 0, gMapMenuRikuStatusFrames[0], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 80);
            DrawSprite(work->x3 >> 8, 0, gMapMenuRikuStatusFrames[1], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 81);
            DrawSprite(work->x4 >> 8, 103, gMapMenuRikuStatusFrames[2], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                81);
#endif

            if (work->tiles9[0] != NULL) {
                DrawSprite((work->x4 >> 8) + 18, 124, work->gfx[0], work->tiles9[0],
                    work->palette9[0], NULL, SPRITE_PRIORITY(1), 80);
            }
        } else {
#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                DrawSprite(work->x3 >> 8, 0, gMapMenuSoraStatusFrames[0], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(work->x3 >> 8, 0, gMapMenuSoraStatusFrames[1], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(work->x4 >> 8, 103, gMapMenuSoraStatusFrames[2], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_FRENCH:
                DrawSprite(work->x3 >> 8, 0, gMapMenuSoraStatusFrenchFrames[0], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(work->x3 >> 8, 0, gMapMenuSoraStatusFrenchFrames[1], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(work->x4 >> 8, 103, gMapMenuSoraStatusFrenchFrames[2], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_SPANISH:
                DrawSprite(work->x3 >> 8, 0, gMapMenuSoraStatusSpanishFrames[0], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(work->x3 >> 8, 0, gMapMenuSoraStatusSpanishFrames[1], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(work->x4 >> 8, 103, gMapMenuSoraStatusSpanishFrames[2], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_ITALIAN:
                DrawSprite(work->x3 >> 8, 0, gMapMenuSoraStatusItalianFrames[0], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(work->x3 >> 8, 0, gMapMenuSoraStatusItalianFrames[1], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(work->x4 >> 8, 103, gMapMenuSoraStatusItalianFrames[2], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_GERMAN:
            default:
                DrawSprite(work->x3 >> 8, 0, gMapMenuSoraStatusGermanFrames[0], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(work->x3 >> 8, 0, gMapMenuSoraStatusGermanFrames[1], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(work->x4 >> 8, 103, gMapMenuSoraStatusGermanFrames[2], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            }
#else
            DrawSprite(work->x3 >> 8, 0, gMapMenuSoraStatusFrames[0], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 80);
            DrawSprite(work->x3 >> 8, 0, gMapMenuSoraStatusFrames[1], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1), 81);
            DrawSprite(work->x4 >> 8, 103, gMapMenuSoraStatusFrames[2], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                81);
#endif

            for (i = 0; i < 3; i++) {
                k = i * 20 + 14;

                if (work->tiles9[i] != NULL) {
                    DrawSprite((work->x4 >> 8) + k, 124, work->gfx[i], work->tiles9[i],
                        work->palette9[i], NULL, SPRITE_PRIORITY(1), 80);
                }
            }
        }

        if (!(gGameState.flags & GAME_FLAG_RIKU)) {
#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                DrawSprite(work->x5 >> 8, 144, gMapMenuSoraStatusFrames[3], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_FRENCH:
                DrawSprite(work->x5 >> 8, 144, gMapMenuSoraStatusFrenchFrames[3], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_SPANISH:
                DrawSprite(work->x5 >> 8, 144, gMapMenuSoraStatusSpanishFrames[3], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_ITALIAN:
                DrawSprite(work->x5 >> 8, 144, gMapMenuSoraStatusItalianFrames[3], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_GERMAN:
            default:
                DrawSprite(work->x5 >> 8, 144, gMapMenuSoraStatusGermanFrames[3], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            }
#else
            DrawSprite(work->x5 >> 8, 144, gMapMenuSoraStatusFrames[3], work->tiles5, work->palette3, NULL, SPRITE_PRIORITY(1),
                81);
#endif
            DrawTextSlots((work->x5 >> 8) + 16, 145, work->textSlots, work->palette8, 50,
                work->textSlotCount);
        }

#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            if (work->cursorVisible) {
                DrawSprite(work->x6 >> 8, 26, gMapMenuCommandsFrames[work->cursor], work->tiles6, work->palette5, NULL,
                    SPRITE_PRIORITY(1), 81);
                DrawSprite(work->x6 >> 8, 26, gMapMenuCommandHighlightFrames[work->cursor], work->tiles6, work->palette4, NULL,
                    SPRITE_PRIORITY(1), 81);
            } else {
                DrawSprite(work->x6 >> 8, 26, gMapMenuCommandsFrames[7], work->tiles6, work->palette5, NULL, SPRITE_PRIORITY(1),
                    80);
            }

            break;
        case LANGUAGE_FRENCH:
            if (work->cursorVisible) {
                DrawSprite(work->x6 >> 8, 26, gMapMenuCommandsFrenchFrames[work->cursor], work->tiles6, work->palette5, NULL,
                    SPRITE_PRIORITY(1), 81);
                DrawSprite(work->x6 >> 8, 26, gMapMenuCommandHighlightFrenchFrames[work->cursor], work->tiles6, work->palette4, NULL,
                    SPRITE_PRIORITY(1), 81);
            } else {
                DrawSprite(work->x6 >> 8, 26, gMapMenuCommandsFrenchFrames[7], work->tiles6, work->palette5, NULL, SPRITE_PRIORITY(1),
                    80);
            }

            break;
        case LANGUAGE_SPANISH:
            if (work->cursorVisible) {
                DrawSprite(work->x6 >> 8, 26, gMapMenuCommandsSpanishFrames[work->cursor], work->tiles6, work->palette5, NULL,
                    SPRITE_PRIORITY(1), 81);
                DrawSprite(work->x6 >> 8, 26, gMapMenuCommandHighlightSpanishFrames[work->cursor], work->tiles6, work->palette4, NULL,
                    SPRITE_PRIORITY(1), 81);
            } else {
                DrawSprite(work->x6 >> 8, 26, gMapMenuCommandsSpanishFrames[7], work->tiles6, work->palette5, NULL, SPRITE_PRIORITY(1),
                    80);
            }

            break;
        case LANGUAGE_ITALIAN:
            if (work->cursorVisible) {
                DrawSprite(work->x6 >> 8, 26, gMapMenuCommandsItalianFrames[work->cursor], work->tiles6, work->palette5, NULL,
                    SPRITE_PRIORITY(1), 81);
                DrawSprite(work->x6 >> 8, 26, gMapMenuCommandHighlightItalianFrames[work->cursor], work->tiles6, work->palette4, NULL,
                    SPRITE_PRIORITY(1), 81);
            } else {
                DrawSprite(work->x6 >> 8, 26, gMapMenuCommandsItalianFrames[7], work->tiles6, work->palette5, NULL, SPRITE_PRIORITY(1),
                    80);
            }

            break;
        case LANGUAGE_GERMAN:
        default:
            if (work->cursorVisible) {
                DrawSprite(work->x6 >> 8, 26, gMapMenuCommandsGermanFrames[work->cursor], work->tiles6, work->palette5, NULL,
                    SPRITE_PRIORITY(1), 81);
                DrawSprite(work->x6 >> 8, 26, gMapMenuCommandHighlightGermanFrames[work->cursor], work->tiles6, work->palette4, NULL,
                    SPRITE_PRIORITY(1), 81);
            } else {
                DrawSprite(work->x6 >> 8, 26, gMapMenuCommandsGermanFrames[7], work->tiles6, work->palette5, NULL, SPRITE_PRIORITY(1),
                    80);
            }

            break;
        }
#else
        if (work->cursorVisible) {
            DrawSprite(work->x6 >> 8, 26, gMapMenuCommandsFrames[work->cursor], work->tiles6, work->palette5, NULL,
                SPRITE_PRIORITY(1), 81);
            DrawSprite(work->x6 >> 8, 26, gMapMenuCommandHighlightFrames[work->cursor], work->tiles6, work->palette4, NULL,
                SPRITE_PRIORITY(1), 81);
        } else {
            DrawSprite(work->x6 >> 8, 26, gMapMenuCommandsFrames[7], work->tiles6, work->palette5, NULL, SPRITE_PRIORITY(1),
                80);
        }
#endif

        if (work->cursorVisible) {
            switch (work->confirmCursor) {
            case 1:
                ApproachValueHalf(&work->x7, 0x4800);
                DrawSprite(work->x7 >> 8, 80, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL,
                    SPRITE_FLAG_HFLIP, 60);
                break;
            case 2:
                ApproachValueHalf(&work->x7, 0x8800);
                DrawSprite(work->x7 >> 8, 80, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL,
                    SPRITE_FLAG_HFLIP, 60);
                break;
            case 0:
            default:
                ApproachValueHalf(&work->y3, (work->cursor * 19 + 16) << 8);
                DrawSprite(24, work->y3 >> 8, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL,
                    SPRITE_PRIORITY(1) | SPRITE_FLAG_HFLIP, 60);
                break;
            }
        }

        if (work->confirmCursor != 0) {
            DrawTextSlots(
#ifdef VERSION_EU
                120 - (GetTextSlotsWidth(work->textSlots2, work->textSlotCount2) >> 1),
#else
                (240 - GetTextSlotsWidth(work->textSlots2, work->textSlotCount2)) / 2,
#endif
                64, work->textSlots2,
                work->confirmPalette, 70, work->textSlotCount2);
            DrawTextSlots(80, 84, work->textSlots3, work->confirmPalette, 70, work->textSlotCount3);
            DrawTextSlots(144, 84, work->textSlots4, work->confirmPalette, 70, work->textSlotCount4);
        }
    }
}

void Task_MapMenu_3(MapMenuWork* work) {
    s32 i;

    MapMenuSetCharaPalettesExcluded(work, 0);
    MapMenuSetPanelPalettesExcluded(work, 0);
    ReleaseObjPalette(work->palette2);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles3);
    ReleaseObjTiles(work->tiles4);
    ReleaseObjPalette(work->palette3);
    ReleaseObjTiles(work->tiles5);
    ReleaseObjPalette(work->palette4);
    ReleaseObjPalette(work->palette5);
    ReleaseObjTiles(work->tiles6);
    ReleaseObjPalette(work->palette);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette6);
    ReleaseObjTiles(work->tiles8);
    ReleaseObjPalette(work->palette7);
    ReleaseObjTiles(work->tiles7);

    for (i = 0; i < 3; i++) {
        if (work->tiles9[i] != NULL) {
            ReleaseObjTiles(work->tiles9[i]);
            ReleaseObjPalette(work->palette9[i]);
        }
    }

    FreeTextSlots(work->textSlots, 24);
    ReleaseObjPalette(work->palette8);
    gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_ENEMIES;
    gFieldState->flags &= ~FIELD_FLAG_MENU_OPEN;
}

void MapSaveSetPanelPalettesExcluded(MapSaveWork* work, u8 a) {
    FadeSetPaletteExcluded(0x0B, a);
    FadeSetPaletteExcluded(0x0C, a);
    FadeSetPaletteExcluded(0x0D, a);
    FadeSetPaletteExcluded(0x0E, a);
    FadeSetPaletteExcluded(work->palette3->index + 0x10, a);
    FadeSetPaletteExcluded(work->palette->index + 0x10, a);
    FadeSetPaletteExcluded(work->palette4->index + 0x10, a);
    FadeSetPaletteExcluded(work->palette8->index + 0x10, a);
}

void MapSaveSetCharaPalettesExcluded(MapSaveWork* work, u8 a) {
    FadeSetPaletteExcluded(work->palette2->index + 0x10, a);
    FadeSetPaletteExcluded(work->palette5->index + 0x10, a);
    FadeSetPaletteExcluded(work->palette6->index + 0x10, a);
    FadeSetPaletteExcluded(work->palette7->index + 0x10, a);
}

void MapSaveLoadFloorTiles(u8 a) {
    const u8* src;

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        if (gGameState.flags & GAME_FLAG_RIKU) {
            src = gSaveSlotRikuFloorSelectedTiles[a];
        } else {
            src = gSaveSlotSoraFloorSelectedTiles[a];
        }

        break;
    case LANGUAGE_FRENCH:
        if (gGameState.flags & GAME_FLAG_RIKU) {
            src = gSaveSlotRikuFloorSelectedFrenchTiles[a];
        } else {
            src = gSaveSlotSoraFloorSelectedFrenchTiles[a];
        }

        break;
    case LANGUAGE_SPANISH:
        if (gGameState.flags & GAME_FLAG_RIKU) {
            src = gSaveSlotRikuFloorSelectedSpanishTiles[a];
        } else {
            src = gSaveSlotSoraFloorSelectedSpanishTiles[a];
        }

        break;
    case LANGUAGE_ITALIAN:
        if (gGameState.flags & GAME_FLAG_RIKU) {
            src = gSaveSlotRikuFloorSelectedItalianTiles[a];
        } else {
            src = gSaveSlotSoraFloorSelectedItalianTiles[a];
        }

        break;
    case LANGUAGE_GERMAN:
    default:
        if (gGameState.flags & GAME_FLAG_RIKU) {
            src = gSaveSlotRikuFloorSelectedGermanTiles[a];
        } else {
            src = gSaveSlotSoraFloorSelectedGermanTiles[a];
        }

        break;
    }
#else
    if (gGameState.flags & GAME_FLAG_RIKU) {
        src = gSaveSlotRikuFloorSelectedTiles[a];
    } else {
        src = gSaveSlotSoraFloorSelectedTiles[a];
    }
#endif

    RequestDma3Copy((void*)src, (u8*)GetBgCharBase(0) + 320, 320);
}

void MapSaveLoadLevelTiles(u16 v) {
    u16 d[4];
    s32 off;
    u16* q;
    s32 i;

    d[0] = v / 100;
    d[1] = v / 10 - d[0] * 10;
    d[2] = v - d[0] * 100 - d[1] * 10;
    off = 0x40;
    q = &d[1];

    for (i = 0; i < 2; i++) {
        RequestDma3Copy((void*)&gSaveSlotDigitTiles[*q * 32], (u8*)GetBgCharBase(0) + off, 0x20);

        // fakematch
        do {
            off += 0x20;
        } while (0);

        q++;
    }
}

void MapSaveLoadTimeTiles(u32 t) {
    u16 d[6];
    s32 off;
    u16* q;
    s32 i;
    u32 v;

    v = t / 3600;
    d[0] = v / 10;
    d[1] = v - d[0] * 10;
    t -= v * 3600;
    v = t / 60;
    d[2] = v / 10;
    d[3] = v - d[2] * 10;
    t -= v * 60;
    d[4] = t / 10;
    d[5] = t - d[4] * 10;
    off = 128;
    q = d;

    for (i = 0; i < 6; i++) {
        RequestDma3Copy((void*)&gSaveSlotDigitTiles[*q * 32], (u8*)GetBgCharBase(0) + off, 0x20);
        off += 0x20;
        q++;
    }
}

void MapSaveShowSummary(MapSaveWork* work, u8 i) {
    SaveFileSummary* e = &gGameState.fileSummaries[i];

    if (e->level == 0) {
        work->textSlotCount = 0;
    } else {
        MapSaveLoadFloorTiles(e->floor);
        MapSaveLoadLevelTiles(e->level);
        MapSaveLoadTimeTiles(e->playTime);
        work->textSlotCount = LoadTextSlots(GetMapWorldName(e->world), work->textSlots);
    }
}

s32 MapSaveSlideInY(MapSaveWork* work) {
    if (work->steps != 0) {
        ApproachValue(&work->y, 0, work->steps);
        ApproachValue(&work->y2, 0x9800, work->steps);
        work->steps -= 1;
    } else {
        gMapRoomState->flags |= ROOM_FLAG_HIDE_PLAYER;
        gFieldState->flags |= FIELD_FLAG_HIDE_ENEMIES;
        work->steps = 16;
        work->update = MapSaveSlideInX;
    }

    return 1;
}

s32 MapSaveSlideInX(MapSaveWork* work) {
    TextSlot* p1;
    TextSlot* p2;
    TextSlot* p3;

    if (work->steps != 0) {
        ApproachValue(&work->x, 0, work->steps);

        if (gGameState.flags & GAME_FLAG_RIKU) {
            ApproachValue(&work->x3, 0x3800, work->steps);
            ApproachValue(&work->y3, 0x7000, work->steps);
        } else {
            ApproachValue(&work->x3, 0x3800, work->steps);
            ApproachValue(&work->y3, 0x7000, work->steps);
        }

        work->steps -= 1;
    } else {
        if (!(gGameState.flags & GAME_FLAG_RIKU)) {
            work->palette4 = LoadObjPalette(gSaveFloorSoraPalette, 32);
        } else {
            work->palette4 = LoadObjPalette(gSaveFloorRikuPalette, 32);
        }

        work->textSlotCount = 0;
        InitTextSlots(work->textSlots, 36);
        SetupBg(0, 3, 31, 11);
        SetBgPriority(0, 0);
        LoadBgPalette(0, gMapSaveBgPalettes, 128);
        LoadBgTiles(0, gSaveSlotBgTiles, 0x1FA0);

#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_FRENCH:
            RequestDma3Copy((void*)gSaveSlotLabelsFrenchTiles, (u8*)GetBgCharBase(0) + 0x800, 0x800);
            break;
        case LANGUAGE_SPANISH:
            RequestDma3Copy((void*)gSaveSlotLabelsSpanishTiles, (u8*)GetBgCharBase(0) + 0x800, 0x800);
            break;
        case LANGUAGE_ITALIAN:
            RequestDma3Copy((void*)gSaveSlotLabelsItalianTiles, (u8*)GetBgCharBase(0) + 0x800, 0x800);
            break;
        case LANGUAGE_GERMAN:
            RequestDma3Copy((void*)gSaveSlotLabelsGermanTiles, (u8*)GetBgCharBase(0) + 0x800, 0x800);
            break;
        }
#endif

        if (gGameState.flags & GAME_FLAG_RIKU) {
            if (gGameState.flags & GAME_FLAG_SECOND_FILE) {
                LoadBgMap(0, gMapSaveRikuFile2Map, 0x800);

                if (SaveRepairFileSmall(1) == SAVE_OK) {
                    MapSaveShowSummary(work, 3);
                }
            } else {
                LoadBgMap(0, gMapSaveRikuFile1Map, 0x800);

                if (SaveRepairFileSmall(0) == SAVE_OK) {
                    MapSaveShowSummary(work, 2);
                }
            }
        } else {
            if (gGameState.flags & GAME_FLAG_SECOND_FILE) {
                LoadBgMap(0, gMapSaveSoraFile2Map, 0x800);

                if (SaveRepairFileLarge(1) == SAVE_OK) {
                    MapSaveShowSummary(work, 1);
                }
            } else {
                LoadBgMap(0, gMapSaveSoraFile1Map, 0x800);

                if (SaveRepairFileLarge(0) == SAVE_OK) {
                    MapSaveShowSummary(work, 0);
                }
            }
        }

        SetBgScroll(0, 0, 0xFFFB);
        work->tiles5 = AllocObjTiles(0x280, gDonaFl00Tiles);
        work->tiles6 = AllocObjTiles(0x400, gGoofyFl00Tiles);
        work->palette3 = LoadObjPalette(gFileMenuWindowPalette, 32);
        work->tiles3 = LoadObjTiles(gSaveSlotCharaWinTiles, 0x4C0);
        work->palette = LoadObjPalette(gMapMenuCursorPalette, 32);
        work->tiles = AllocObjTiles(0x120, gMapMenuCursorTiles);
        AnimInit(&work->anim, gMapMenuCursorAnims, gMapMenuCursorFrames);
        AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);
        work->palette8 = LoadTextPalette(1);
        p1 = work->textSlots2;
#ifdef VERSION_EU
        InitTextSlots(p1, 54);
#else
        InitTextSlots(p1, 27);
#endif
        p2 = work->textSlots3;
        InitTextSlots(p2, 6);
        p3 = work->textSlots4;
        InitTextSlots(p3, 9);
#ifdef VERSION_EU
        work->textSlotCount2 = LoadTextSlots(GetLocalizedString(&gMapSaveConfirmTextByLanguage), p1);
        work->textSlotCount3 = LoadTextSlots(GetLocalizedString(&gYesChoiceTextByLanguage), p2);
        work->textSlotCount4 = LoadTextSlots(GetLocalizedString(&gNoChoiceTextByLanguage), p3);
#else
        work->textSlotCount2 = LoadTextSlots(gMapSaveConfirmText, p1);
        work->textSlotCount3 = LoadTextSlots(gYesChoiceText, p2);
        work->textSlotCount4 = LoadTextSlots(gNoChoiceText, p3);
#endif
        MapSaveSetPanelPalettesExcluded(work, 1);
        work->dialogVisible = 1;
        work->confirmCursor = 2;
        work->x2 = 0xB000;
        work->update = MapSaveInput;
    }

    return 1;
}

s32 MapSaveInput(MapSaveWork* work) {
    if (GetKeysRepeat() & DPAD_LEFT) {
        if (work->confirmCursor != 1) {
            work->confirmCursor = 1;
            m4aSongNumStart(SONG_SYS_CLICK);
        }
    }

    if (GetKeysRepeat() & DPAD_RIGHT) {
        if (work->confirmCursor != 2) {
            work->confirmCursor = 2;
            m4aSongNumStart(SONG_SYS_CLICK);
        }
    }

    if ((GetKeysPressed() & B_BUTTON) || ((GetKeysPressed() & A_BUTTON) && work->confirmCursor != 1)) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        work->confirmCursor = 0;
        work->dialogVisible = 0;
        work->steps = 16;
        work->update = MapSaveSlideOutX;
        DisableBg(0);
    } else if (GetKeysPressed() & A_BUTTON) {
        m4aSongNumStart(SONG_SYS_SAVELOAD);

        if (gGameState.flags & GAME_FLAG_RIKU) {
            if (gGameState.flags & GAME_FLAG_SECOND_FILE) {
                SaveWriteFileSmall(1);
                MapSaveShowSummary(work, 3);
            } else {
                SaveWriteFileSmall(0);
                MapSaveShowSummary(work, 2);
            }
        } else {
            if (gGameState.flags & GAME_FLAG_SECOND_FILE) {
                SaveWriteFileLarge(1);
                MapSaveShowSummary(work, 1);
            } else {
                SaveWriteFileLarge(0);
                MapSaveShowSummary(work, 0);
            }
        }

#ifdef VERSION_EU
        work->textSlotCount2 = LoadTextSlots(GetLocalizedString(&gMapSaveCompleteTextByLanguage), work->textSlots2);
#else
        work->textSlotCount2 = LoadTextSlots(gMapSaveCompleteText, work->textSlots2);
#endif
        work->textSlotCount3 = 0;
        work->textSlotCount4 = 0;
        work->confirmCursor = 0;
        work->update = MapSaveWaitClose;
    }

    return 1;
}

s32 MapSaveWaitClose(MapSaveWork* work) {
    if (GetKeysPressed() & (A_BUTTON | B_BUTTON)) {
        work->dialogVisible = 0;
        DisableBg(0);
        work->steps = 16;
        work->update = MapSaveSlideOutX;
    }

    return 1;
}

s32 MapSaveSlideOutX(MapSaveWork* work) {
    if (work->steps != 0) {
        ApproachValue(&work->x, -0x8000, work->steps);
        ApproachValue(&work->x3, work->playerStartX, work->steps);
        ApproachValue(&work->y3, work->playerStartY, work->steps);
        work->steps--;
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_HIDE_PLAYER;
        gFieldState->flags &= ~FIELD_FLAG_HIDE_ENEMIES;
        MapSaveSetPanelPalettesExcluded(work, 0);
        FadeToOriginal(FADE_MODE_BLACK, 16);
        work->steps = 16;
        work->update = MapSaveSlideOutY;
    }

    return 1;
}

s32 MapSaveSlideOutY(MapSaveWork* work) {
    if (work->steps != 0) {
        ApproachValue(&work->y, -0x800, work->steps);
        ApproachValue(&work->y2, 0xA000, work->steps);
        work->steps--;
        return 1;
    }

    return 0;
}

void Task_MapSave_0(MapSaveWork* work) {
    gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
    gFieldState->flags |= FIELD_FLAG_FREEZE_ENEMIES;
    gMapRoomState->flags |= ROOM_FLAG_SAVE_MENU_OPEN;
    gGameState.hp = gGameState.progression.maxHp;

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        work->tiles2 = LoadObjTiles(gMapSaveTitleTiles, 0x2C0);
        break;
    case LANGUAGE_FRENCH:
        work->tiles2 = LoadObjTiles(gMapSaveTitleFrenchTiles, 0x400);
        break;
    case LANGUAGE_SPANISH:
        work->tiles2 = LoadObjTiles(gMapSaveTitleSpanishTiles, 0x3C0);
        break;
    case LANGUAGE_ITALIAN:
        work->tiles2 = LoadObjTiles(gMapSaveTitleItalianTiles, 0x2C0);
        break;
    case LANGUAGE_GERMAN:
    default:
        work->tiles2 = LoadObjTiles(gMapSaveTitleGermanTiles, 0x3C0);
        break;
    }

    work->palette2 = LoadObjPalette(gSaveMenuTitlePalette, 32);
#else
    work->palette2 = LoadObjPalette(gSaveMenuTitlePalette, 32);
    work->tiles2 = LoadObjTiles(gMapSaveTitleTiles, 0x2C0);
#endif
    work->y = -0x800;
    work->y2 = 0xA000;
    work->x = -0x8000;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        work->tiles4 = AllocObjTiles(0x400, gRikuFf00Tiles);
        work->palette5 = LoadObjPalette(gRikuPalette, 32);
    } else {
        work->tiles4 = AllocObjTiles(0x340, gSor1ff00Tiles);
        work->palette5 = LoadObjPalette(gSoraPalette, 32);
    }

    work->palette6 = LoadObjPalette(gDonaldPalette, 32);
    work->palette7 = LoadObjPalette(gGoofyPalette, 32);
    work->playerStartX = gFieldState->actor.fieldPosition.x - gFieldState->x;
    work->playerStartY = gFieldState->actor.fieldPosition.y + gFieldState->actor.fieldPosition.z - gFieldState->y;
    work->x3 = work->playerStartX;
    work->y3 = work->playerStartY;
    work->confirmCursor = 0;
    work->dialogVisible = 0;
    work->steps = 16;
    work->update = MapSaveSlideInY;
    TaskPoolInit(&work->tasks, 1);
    MapSaveSetCharaPalettesExcluded(work, 1);
    FadeToAmount(FADE_MODE_BLACK, 16, 16);
    m4aSongNumStart(SONG_SYS_CANSEL);
}

s32 Task_MapSave_1(MapSaveWork* work) {
    TaskPoolUpdate(&work->tasks);

    if (work->confirmCursor != 0) {
        AnimUpdate(&work->anim);
    }

    if (work->update != NULL) {
        if ((u8)work->update(work) == 0) {
            return 0;
        }
    }

    return 1;
}

void Task_MapSave_2(MapSaveWork* work) {
    TaskPoolDraw(&work->tasks);

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        DrawSprite(128, work->y >> 8, gMapSaveTitleFrames[1], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(128, work->y2 >> 8, gMapSaveTitleFrames[2], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(work->x >> 8, 0, gMapSaveTitleFrames[0], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 80);
        break;
    case LANGUAGE_FRENCH:
        DrawSprite(128, work->y >> 8, gMapSaveTitleFrenchFrames[1], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(128, work->y2 >> 8, gMapSaveTitleFrenchFrames[2], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(work->x >> 8, 0, gMapSaveTitleFrenchFrames[0], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 80);
        break;
    case LANGUAGE_SPANISH:
        DrawSprite(128, work->y >> 8, gMapSaveTitleSpanishFrames[1], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(128, work->y2 >> 8, gMapSaveTitleSpanishFrames[2], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(work->x >> 8, 0, gMapSaveTitleSpanishFrames[0], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 80);
        break;
    case LANGUAGE_ITALIAN:
        DrawSprite(128, work->y >> 8, gMapSaveTitleItalianFrames[1], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(128, work->y2 >> 8, gMapSaveTitleItalianFrames[2], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(work->x >> 8, 0, gMapSaveTitleItalianFrames[0], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 80);
        break;
    case LANGUAGE_GERMAN:
    default:
        DrawSprite(128, work->y >> 8, gMapSaveTitleGermanFrames[1], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(128, work->y2 >> 8, gMapSaveTitleGermanFrames[2], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(work->x >> 8, 0, gMapSaveTitleGermanFrames[0], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 80);
        break;
    }
#else
    DrawSprite(128, work->y >> 8, gMapSaveTitleFrames[1], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 90);
    DrawSprite(128, work->y2 >> 8, gMapSaveTitleFrames[2], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 90);
    DrawSprite(work->x >> 8, 0, gMapSaveTitleFrames[0], work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1), 80);
#endif

    if (gMapRoomState->flags & ROOM_FLAG_HIDE_PLAYER) {
        if (gGameState.flags & GAME_FLAG_RIKU) {
            DrawSprite(work->x3 >> 8, work->y3 >> 8, gRikuFf00Frames[0], work->tiles4, work->palette5,
                NULL, SPRITE_PRIORITY(1), 80);
        } else {
            DrawSprite(work->x3 >> 8, work->y3 >> 8, gSor1ff00Frames[0], work->tiles4,
                work->palette5, NULL, SPRITE_PRIORITY(1), 80);
        }
    }

    if (work->dialogVisible) {
        if (!(gGameState.flags & GAME_FLAG_RIKU)) {
            DrawSprite(72, 96, gDonaFl00Frames[0], work->tiles5, work->palette6, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_HFLIP, 81);
            DrawSprite(40, 96, gGoofyFl00Frames[0], work->tiles6, work->palette7, NULL, SPRITE_PRIORITY(1), 81);
        }

        DrawSprite(0, 16, gSaveSlotCharaWinFrame0, work->tiles3, work->palette3, NULL, SPRITE_PRIORITY(1), 90);
        DrawTextSlots(100, 59, work->textSlots, work->palette4, 50, work->textSlotCount);

        if (work->confirmCursor != 0) {
#ifdef VERSION_EU
            DrawTextSlots(166 - (GetTextSlotsWidth(work->textSlots2, work->textSlotCount2) >> 1), 92, work->textSlots2, work->palette8, 50, work->textSlotCount2);
#elif defined(VERSION_JP)
            DrawTextSlots(129, 92, work->textSlots2, work->palette8, 50, work->textSlotCount2);
#else
            DrawTextSlots(124, 92, work->textSlots2, work->palette8, 50, work->textSlotCount2);
#endif
            DrawTextSlots(128, 114, work->textSlots3, work->palette8, 50, work->textSlotCount3);
            DrawTextSlots(184, 114, work->textSlots4, work->palette8, 50, work->textSlotCount4);
        } else {
#ifdef VERSION_EU
            DrawTextSlots(166 - (GetTextSlotsWidth(work->textSlots2, work->textSlotCount2) >> 1), 102, work->textSlots2, work->palette8, 50, work->textSlotCount2);
#elif defined(VERSION_JP)
            DrawTextSlots(129, 103, work->textSlots2, work->palette8, 50, work->textSlotCount2);
#else
            DrawTextSlots(130, 102, work->textSlots2, work->palette8, 50, work->textSlotCount2);
#endif
        }

        switch (work->confirmCursor) {
        case 1:
            ApproachValueHalf(&work->x2, 0x7800);
            DrawSprite(work->x2 >> 8, 110, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL, SPRITE_FLAG_HFLIP,
                40);
            break;
        case 2:
            ApproachValueHalf(&work->x2, 0xB000);
            DrawSprite(work->x2 >> 8, 110, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL, SPRITE_FLAG_HFLIP,
                40);
            break;
        }
    }
}

void Task_MapSave_3(MapSaveWork* work) {
    u32 f;

    MapSaveSetCharaPalettesExcluded(work, 0);
    ReleaseObjPalette(work->palette2);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette3);
    ReleaseObjTiles(work->tiles3);
    ReleaseObjPalette(work->palette);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette5);
    ReleaseObjTiles(work->tiles4);
    ReleaseObjPalette(work->palette6);
    ReleaseObjTiles(work->tiles5);
    ReleaseObjPalette(work->palette7);
    ReleaseObjTiles(work->tiles6);
    ReleaseObjPalette(work->palette4);
    FreeTextSlots(work->textSlots, 36);
    ReleaseObjPalette(work->palette8);
#ifdef VERSION_EU
    FreeTextSlots(work->textSlots2, 54);
#else
    FreeTextSlots(work->textSlots2, 27);
#endif
    FreeTextSlots(work->textSlots3, 6);
    FreeTextSlots(work->textSlots4, 9);
    f = gMapRoomState->flags & ~ROOM_FLAG_ATTACK_HIT;
    gMapRoomState->flags = f;
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_ENEMIES;
    gMapRoomState->flags = f & ~ROOM_FLAG_SAVE_MENU_OPEN;
    TaskPoolDestroy(&work->tasks);
}

void Task_MapAnm_0(MapAnmWork* work, MapAnmEntry* list) {
    MapAnmSlot* e;
    s32 i;

    e = work->slots;

    for (i = 0; i < 8; i++) {
        MapAnmResetSlot(e);
        e++;
    }

    if (list != NULL) {
        if (list->script != NULL) {
            e = work->slots;

            do {
                MapAnmSetupSlot(e, list);
                e++;
                list++;
            } while (list->script != NULL);
        }
    }
}

s32 Task_MapAnm_1(MapAnmWork* work) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (work->slots[i].script != NULL) {
            MapAnmUpdateSlot(&work->slots[i]);
        }
    }

    return 1;
}

void Task_MapAnm_2(MapAnmWork* work) {
}

void Task_MapAnm_3(MapAnmWork* work) {
}

const u8 gCellMasks[16][8] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
    { 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1F, 0x7F },
    { 0x01, 0x07, 0x1F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF },
    { 0x80, 0xE0, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF },
    { 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF8, 0xFE },
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF8, 0xE0, 0x80 },
    { 0xFE, 0xF8, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00 },
    { 0x7F, 0x1F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00 },
    { 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x07, 0x01 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0x00, 0x00, 0x02, 0x03, 0x02, 0x03, 0x01, 0x01 },
    { 0x04, 0x05, 0x00, 0x00, 0x01, 0x01, 0x04, 0x05 },
    { 0x01, 0x01, 0x06, 0x07, 0x06, 0x07, 0x00, 0x00 },
    { 0x08, 0x09, 0x01, 0x01, 0x00, 0x00, 0x08, 0x09 },
};

static const char sModeNameMapDbg[] = "Mode_MapDbg";

static const char sModeNameMapFld[] = "Mode_MapFld";

const u8 gSoraFloorEvents[13] = { 12, 14, 17, 20, 23, 28, 32, 35, 38, 42, 50, 255, 68 };

#ifdef VERSION_EU
const u8 gRikuFloorEvents[13] = { 155, 157, 255, 160, 163, 165, 166, 167, 173, 182, 189, 255, 0 };
#else
const u8 gRikuFloorEvents[13] = { 157, 159, 255, 162, 165, 167, 168, 169, 175, 184, 191, 255, 0 };
#endif

static const char sModeNameMapFix[] = "Mode_MapFix";

static const char sModeNameMenuNew[] = "Mode_MenuNew";

static const char sModeNameMenuLoad[] = "Mode_MenuLoad";

static const char sModeNameMenuMsg[] = "Mode_MenuMsg";

u8 gSoraWorldBattleBase[14] = {
    40,
    40,
    50,
    30,
    20,
    80,
    60,
    70,
    100,
    0,
    10,
    90,
    110,
    40,
};

u8 gRikuWorldBattleBase[14] = {
    40,
    40,
    50,
    30,
    20,
    80,
    60,
    70,
    134,
    0,
    10,
    90,
    110,
    40,
};

u8 (*gMapGmkSpotFuncs[14])(FldPos*) = {
    MapGmkFindFloor2x2,
    MapGmkFindLeftWallBase2x3,
    MapGmkFindRightWallBase2x3,
    MapGmkFindBackWallBase2x3,
    MapGmkFindLeftWallFace3x3,
    MapGmkFindRightWallFace3x3,
    MapGmkFindLeftWallTop2x2,
    MapGmkFindBackWallTop1x2,
    MapGmkFindRightWallTop2x2,
    MapGmkFindFloor3x3,
    MapGmkFindLeftWallBase1x4,
    MapGmkFindFloor4x4,
    MapGmkFindFloor5x5,
    MapGmkFindBaseFloor2x2,
};

u8 (*gMapAnmCmds[2])(MapAnmSlot*) = {
    MapAnmCmdEnd,
    MapAnmCmdLoop,
};

Mode gModeMapDbg = {
    sModeNameMapDbg,
    (ModeInitFunc)Mode_MapDbg_0,
    Mode_MapDbg_1,
    Mode_MapDbg_2,
};

Mode gModeMapFld = {
    sModeNameMapFld,
    (ModeInitFunc)Mode_MapFld_0,
    Mode_MapFld_1,
    Mode_MapFld_2,
};

u8 gWorldEntryEvents[14] = {
#if defined(VERSION_US)
    255,
    107,
    101,
    120,
    94,
    74,
    87,
    115,
    129,
    53,
    2,
    44,
    61,
    135,
#elif defined(VERSION_JP)
    255,
    107,
    101,
    120,
    94,
    74,
    87,
    115,
    129,
    53,
    2,
    44,
    61,
    135,
#elif defined(VERSION_EU)
    255,
    107,
    101,
    120,
    94,
    74,
    87,
    115,
    127,
    53,
    2,
    44,
    61,
    133,
#endif
};

Mode gModeMapFix = {
    sModeNameMapFix,
    (ModeInitFunc)Mode_MapFix_0,
    Mode_MapFix_1,
    Mode_MapFix_2,
};

Mode gModeMenuNew = {
    sModeNameMenuNew,
    (ModeInitFunc)Mode_MenuNew_0,
    Mode_MenuNew_1,
    Mode_MenuNew_2,
};

Mode gModeMenuLoad = {
    sModeNameMenuLoad,
    Mode_MenuLoad_0,
    Mode_MenuLoad_1,
    Mode_MenuLoad_2,
};

Mode gModeMenuMsg = {
    sModeNameMenuMsg,
    Mode_MenuMsg_0,
    Mode_MenuMsg_1,
    Mode_MenuMsg_2,
};

TaskDesc gTaskDescMapRnd = {
    "Task_MapRnd",
    (TaskInitFunc)Task_MapRnd_0,
    (TaskUpdateFunc)Task_MapRnd_1,
    (TaskDrawFunc)Task_MapRnd_2,
    (TaskDestroyFunc)Task_MapRnd_3,
    sizeof(MapRndWork),
};

TaskDesc gTaskDescMapFix = {
    "Task_MapFix",
    (TaskInitFunc)Task_MapFix_0,
    (TaskUpdateFunc)Task_MapFix_1,
    (TaskDrawFunc)Task_MapFix_2,
    (TaskDestroyFunc)Task_MapFix_3,
    sizeof(MapFixWork),
};

const MapDoorGfx gWorldMapDoorGfx[14] = {
    { gMapDoorWonderlandPalette, gMapDoorWonderlandSide0ClosedTiles, gMapDoorWonderlandSide0OpenTiles, gMapDoorWonderlandSide3ClosedTiles, gMapDoorWonderlandSide3OpenTiles, gMapDoorWonderlandSide2ClosedTiles, gMapDoorWonderlandSide2OpenTiles, gMapDoorWonderlandSide1ClosedTiles, gMapDoorWonderlandSide1OpenTiles },
    { gMapDoorAgrabahPalette, gMapDoorAgrabahSide0ClosedTiles, gMapDoorAgrabahSide0OpenTiles, gMapDoorAgrabahSide3ClosedTiles, gMapDoorAgrabahSide3OpenTiles, gMapDoorAgrabahSide2ClosedTiles, gMapDoorAgrabahSide2OpenTiles, gMapDoorAgrabahSide1ClosedTiles, gMapDoorAgrabahSide1OpenTiles },
    { gMapDoorAtlanticaPalette, gMapDoorAtlanticaSide0ClosedTiles, gMapDoorAtlanticaSide0OpenTiles, gMapDoorAtlanticaSide3ClosedTiles, gMapDoorAtlanticaSide3OpenTiles, gMapDoorAtlanticaSide2ClosedTiles, gMapDoorAtlanticaSide2OpenTiles, gMapDoorAtlanticaSide1ClosedTiles, gMapDoorAtlanticaSide1OpenTiles },
    { gMapDoorOlympusColiseumPalette, gMapDoorOlympusColiseumSide0ClosedTiles, gMapDoorOlympusColiseumSide0OpenTiles, gMapDoorOlympusColiseumSide3ClosedTiles, gMapDoorOlympusColiseumSide3OpenTiles, gMapDoorOlympusColiseumSide2ClosedTiles, gMapDoorOlympusColiseumSide2OpenTiles, gMapDoorOlympusColiseumSide1ClosedTiles, gMapDoorOlympusColiseumSide1OpenTiles },
    { gMapDoorWonderlandPalette, gMapDoorWonderlandSide0ClosedTiles, gMapDoorWonderlandSide0OpenTiles, gMapDoorWonderlandSide3ClosedTiles, gMapDoorWonderlandSide3OpenTiles, gMapDoorWonderlandSide2ClosedTiles, gMapDoorWonderlandSide2OpenTiles, gMapDoorWonderlandSide1ClosedTiles, gMapDoorWonderlandSide1OpenTiles },
    { gMapDoorMonstroPalette, gMapDoorMonstroSide0ClosedTiles, gMapDoorMonstroSide0OpenTiles, gMapDoorMonstroSide3ClosedTiles, gMapDoorMonstroSide3OpenTiles, gMapDoorMonstroSide2ClosedTiles, gMapDoorMonstroSide2OpenTiles, gMapDoorMonstroSide1ClosedTiles, gMapDoorMonstroSide1OpenTiles },
    { gMapDoorHalloweenTownPalette, gMapDoorHalloweenTownSide0ClosedTiles, gMapDoorHalloweenTownSide0OpenTiles, gMapDoorHalloweenTownSide3ClosedTiles, gMapDoorHalloweenTownSide3OpenTiles, gMapDoorHalloweenTownSide2ClosedTiles, gMapDoorHalloweenTownSide2OpenTiles, gMapDoorHalloweenTownSide1ClosedTiles, gMapDoorHalloweenTownSide1OpenTiles },
    { gMapDoorNeverLandPalette, gMapDoorNeverLandSide0ClosedTiles, gMapDoorNeverLandSide0OpenTiles, gMapDoorNeverLandSide3ClosedTiles, gMapDoorNeverLandSide3OpenTiles, gMapDoorNeverLandSide2ClosedTiles, gMapDoorNeverLandSide2OpenTiles, gMapDoorNeverLandSide1ClosedTiles, gMapDoorNeverLandSide1OpenTiles },
    { gMapDoorHollowBastionPalette, gMapDoorHollowBastionSide0ClosedTiles, gMapDoorHollowBastionSide0OpenTiles, gMapDoorHollowBastionSide3ClosedTiles, gMapDoorHollowBastionSide3OpenTiles, gMapDoorHollowBastionSide2ClosedTiles, gMapDoorHollowBastionSide2OpenTiles, gMapDoorHollowBastionSide1ClosedTiles, gMapDoorHollowBastionSide1OpenTiles },
    { gMapDoorDestinyIslandsPalette, gMapDoorDestinyIslandsSide0ClosedTiles, gMapDoorDestinyIslandsSide0OpenTiles, gMapDoorDestinyIslandsSide3ClosedTiles, gMapDoorDestinyIslandsSide3OpenTiles, gMapDoorDestinyIslandsSide2ClosedTiles, gMapDoorDestinyIslandsSide2OpenTiles, gMapDoorDestinyIslandsSide1ClosedTiles, gMapDoorDestinyIslandsSide1OpenTiles },
    { gMapDoorTraverseTownPalette, gMapDoorTraverseTownSide0ClosedTiles, gMapDoorTraverseTownSide0OpenTiles, gMapDoorTraverseTownSide3ClosedTiles, gMapDoorTraverseTownSide3OpenTiles, gMapDoorTraverseTownSide2ClosedTiles, gMapDoorTraverseTownSide2OpenTiles, gMapDoorTraverseTownSide1ClosedTiles, gMapDoorTraverseTownSide1OpenTiles },
    { gMapDoorTwilightTownPalette, gMapDoorTwilightTownSide0ClosedTiles, gMapDoorTwilightTownSide0OpenTiles, gMapDoorTwilightTownSide3ClosedTiles, gMapDoorTwilightTownSide3OpenTiles, gMapDoorTwilightTownSide2ClosedTiles, gMapDoorTwilightTownSide2OpenTiles, gMapDoorTwilightTownSide1ClosedTiles, gMapDoorTwilightTownSide1OpenTiles },
    { gMapDoorCastleOblivionPalette, gMapDoorCastleOblivionSide0ClosedTiles, gMapDoorCastleOblivionSide0OpenTiles, gMapDoorCastleOblivionSide3ClosedTiles, gMapDoorCastleOblivionSide3OpenTiles, gMapDoorCastleOblivionSide2ClosedTiles, gMapDoorCastleOblivionSide2OpenTiles, gMapDoorCastleOblivionSide1ClosedTiles, gMapDoorCastleOblivionSide1OpenTiles },
    { gMapDoorWonderlandPalette, gMapDoorWonderlandSide0ClosedTiles, gMapDoorWonderlandSide0OpenTiles, gMapDoorWonderlandSide3ClosedTiles, gMapDoorWonderlandSide3OpenTiles, gMapDoorWonderlandSide2ClosedTiles, gMapDoorWonderlandSide2OpenTiles, gMapDoorWonderlandSide1ClosedTiles, gMapDoorWonderlandSide1OpenTiles },
};

TaskDesc gTaskDescMapDoor = {
    "Task_MapDoor",
    (TaskInitFunc)Task_MapDoor_0,
    (TaskUpdateFunc)Task_MapDoor_1,
    (TaskDrawFunc)Task_MapDoor_2,
    (TaskDestroyFunc)Task_MapDoor_3,
    sizeof(MapDoorWork),
};

TaskDesc gTaskDescMapMenu = {
    "Task_MapMenu",
    (TaskInitFunc)Task_MapMenu_0,
    (TaskUpdateFunc)Task_MapMenu_1,
    (TaskDrawFunc)Task_MapMenu_2,
    (TaskDestroyFunc)Task_MapMenu_3,
    sizeof(MapMenuWork),
};

TaskDesc gTaskDescMapSave = {
    "Task_MapSave",
    (TaskInitFunc)Task_MapSave_0,
    (TaskUpdateFunc)Task_MapSave_1,
    (TaskDrawFunc)Task_MapSave_2,
    (TaskDestroyFunc)Task_MapSave_3,
    sizeof(MapSaveWork),
};

TaskDesc gTaskDescMapAnm = {
    "Task_MapAnm",
    (TaskInitFunc)Task_MapAnm_0,
    (TaskUpdateFunc)Task_MapAnm_1,
    (TaskDrawFunc)Task_MapAnm_2,
    (TaskDestroyFunc)Task_MapAnm_3,
    sizeof(MapAnmWork),
};
