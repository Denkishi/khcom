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
#include "card_deck.h"
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
#include "task.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "text.h"
#include "text_types.h"
#include "types.h"
#include <stddef.h>

extern u8 gSoraWorldBattleBase[];
extern u8 gRikuWorldBattleBase[];
extern u8 (*gMapGmkSpotFuncs[])(FldPos*);
extern u8 (*gMapAnmCmds[])(MapAnmSlot*);
extern u8 gWorldEntryEvents[];

u8 gMapEnmCount;
u8 gMapEnmTileCount;
u8 gMapEnmSpawnTimer;
u32 gUnk_02034F44;
FldPos gMapEnmSpawnPositions[3];
u8 gMapGmkCount;
u8 gMapGmkPaletteCount;
u16 gMapGmkTileCount;
EventKeyList* gEventKeyList;
EventKey gEventKey;
EventKeyProgress* gEventKeyProgress;
ModeFunc gMapDbgUpdate;
u32 gUnk_02034F8C;
TaskPool gMapDbgTasks;
u8 gMapDbgEditing;
void* gMapDbgAllmapRoomTask;
u32 gUnk_02034FAC;
ModeFunc gMapFldUpdate;
Task* gMapFldWorldLogoTask;
void* gMapFldAllmapRoomTask;
u8 gUnk_02034FBC;
u8 gUnk_02034FBD[0x17];
ModeFunc gMapFixUpdate;
u8 gMapFixEventDelay;
NewGameSlotMenuWork* gNewGameSlotMenuWork;
LoadGameMenuWork* gLoadGameMenuWork;
MenuMsgWork* gMenuMsgWork;

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

    if (MapPickFreeFloorPos(q, &q->y) != 0) {
        q->z = 0;
        t = GetFldPosFloor(q);
        q->ground = t;
        q->z = t;
        q->y -= t;

        for (i = 0; i < gMapEnmCount; i++) {
            if (gMapEnmSpawnPositions[i].x >> 8 == q->x >> 8 && gMapEnmSpawnPositions[i].y >> 8 == q->y >> 8) {
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

    t = gUnk_0984D134[gMapRoomState->roomType];
    e = GetMapFloorRoom(gMapFloorState.room);

    if (gMapEnmCount >= t[1]) {
        return;
    }

    if (e->enemiesLeft - gMapEnmCount <= 0) {
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
        gMapEnmSpawnPositions[gMapEnmCount] = w->pos;
        w->speed = 0;
        w->def = d;
        w->update = NULL;
        TaskCreate(&gFieldState->tasks4, d->desc, w);
    }
}

void MapEnmApplyRoomFlags(MapEnmWork* p) {
    switch (gMapRoomState->roomType) {
    case 4:
        p->flags |= MAP_ENM_FLAG_AGGRESSIVE;
        break;
    case 5:
        p->flags |= MAP_ENM_FLAG_ASLEEP;
        p->flags |= MAP_ENM_FLAG_PERSISTENT;
        break;
    case 18:
        p->flags |= MAP_ENM_FLAG_SLOW;
        break;
    case 20:
        p->flags |= MAP_ENM_FLAG_WHITE_MUSHROOM;
        break;
    case 21:
        p->flags |= MAP_ENM_FLAG_BLACK_FUNGUS;
        break;
    }
}

void MapEnmSetAnim(MapEnmWork* p, u8 n, u16 a) {
    const AnimDef* q = p->def->animDef;

    switch (p->obj.angle >> 6) {
    case 0:
        q += n * 2;
        p->flags |= MAP_ENM_FLAG_HFLIP;
        break;
    case 1:
        q += n * 2 + 1;
        p->flags |= MAP_ENM_FLAG_HFLIP;
        break;
    case 2:
        q += n * 2 + 1;
        p->flags &= ~MAP_ENM_FLAG_HFLIP;
        break;
    default:
        q += n * 2;
        p->flags &= ~MAP_ENM_FLAG_HFLIP;
        break;
    }

    AnimChangeWithTables(&p->anim, q->animId, a, q->anims, q->gfxTable);
    SetObjTileSource(p->tiles, q->tiles);
}

void MapEnmUpdateAnim(MapEnmWork* p) {
    if (gFieldState->flags & FIELD_FLAG_ENEMY_FRAME_CHANGED) {
        if (AnimIsFrameEnding(&p->anim)) {
            return;
        }
    } else {
        if (AnimIsFrameEnding(&p->anim)) {
            gFieldState->flags |= FIELD_FLAG_ENEMY_FRAME_CHANGED;
        }
    }

    p->gfx = AnimUpdate(&p->anim);
}

u8 GetRandomBattleId() {
    const u8* q = gUnk_0984D134[gMapRoomState->roomType];
    u8 v = q[3] + GetRandom() % (q[4] - q[3] + 1);

    if (gGameState.flags & GAME_FLAG_RIKU) {
        return v + gRikuWorldBattleBase[gMapFloorState.world];
    }

    return v + gSoraWorldBattleBase[gMapFloorState.world];
}

void MapEnmStartBattle(MapEnmWork* p) {
    gGameState.flags |= GAME_FLAG_MAP_ENEMY_BATTLE;
    ColliderSetDisabled(&p->collider, 1);
    gMapRoomState->flags |= ROOM_FLAG_START_BATTLE;
    gFieldState->flags |= FIELD_FLAG_FREEZE_ENEMIES;
    p->flags |= MAP_ENM_FLAG_REMOVED;

    if (p->flags & MAP_ENM_FLAG_FIRST_STRIKE) {
        gGameState.flags |= GAME_FLAG_FIRST_STRIKE;
    }

    if (p->flags & MAP_ENM_FLAG_WHITE_MUSHROOM) {
        gMapRoomState->battleId = GetRandom() % 3 + 128;
    } else if (p->flags & MAP_ENM_FLAG_BLACK_FUNGUS) {
        gMapRoomState->battleId = GetRandom() % 3 + 131;
    } else {
        gMapRoomState->battleId = GetRandomBattleId();
    }
}

void MapEnmCheckContact(MapEnmWork* p) {
    if (p->collider.colliding != 0) {
        if ((gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) == 0 && ColliderIsTouchingType(&p->collider, 1)) {
            MapEnmStartBattle(p);
            return;
        }

        if (ColliderIsTouchingType(&p->collider, 6)) {
            p->obj.fieldPosition.x += p->collider.pushX;
            p->obj.fieldPosition.y += p->collider.pushY;
        }
    }
}

s32 MapEnmCheckAttacked(MapEnmWork* p) {
    if (IsHitByMapAttack(&p->obj.fieldPosition, p->radius / 2, p->height / 2)) {
        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        gMapRoomState->flags |= ROOM_FLAG_ENEMY_STRUCK;
        TaskCreate(&p->tasks, &gTaskDescMapSpark, &p->obj);

        if (gGameState.flags & GAME_FLAG_RIKU) {
            m4aSongNumStart(SONG_SND_228);
        } else {
            m4aSongNumStart(SONG_SYS_FIELD_ATT00);
        }

        return 1;
    }

    return 0;
}

void MapEnmSaveToCache(MapEnmWork* p) {
    MapEnmCache* q = ListPoolFirstFree(&gGameState.enemyCachePool);

    if (q != NULL) {
        q->def = p->def;
        q->update = p->update;
        q->pos = p->obj.fieldPosition;
        q->angle = p->obj.angle;
        q->speed = p->obj.speed;
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

    gMapEnmCount = 0;
    gMapEnmTileCount = 0;
    gMapEnmSpawnTimer = 46;

    if (gGameState.fieldResume != 0) {
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

    t = gUnk_0984D134[gMapRoomState->roomType];
    gFieldState->flags &= ~FIELD_FLAG_ENEMY_FRAME_CHANGED;

    if (gMapEnmSpawnTimer != 0) {
        gMapEnmSpawnTimer--;
        return;
    }

    e = GetMapFloorRoom(gMapFloorState.room);

    if (gMapEnmCount >= t[1]) {
        return;
    }

    if (e->enemiesLeft - gMapEnmCount <= 0) {
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

    if (gMapEnmTileCount + d->tileCount > 256) {
        return;
    }

    gMapEnmSpawnTimer = 30;
    MapEnmSetupArgs(&w, d);
    TaskCreate(&gFieldState->tasks4, d->desc, &w);
}

void MapEnmInit(MapEnmWork* p, MapEnmArgs* q) {
    FldObj* e = &p->obj;
    const MapEnmDef* d = q->def;

    p->def = d;
    p->update = q->update;
    p->flags = 0;
    p->colliderDelay = 30;
    e->fieldPosition = q->pos;
    e->angle = q->angle;
    e->speed = q->speed;
    e->height = d->height;
    e->unk_34 = 0;
    e->kind = 1;
    p->radius = d->radius;
    p->height = d->height;
    p->timer = 0;
    p->unk_D2 = 0;
    p->targetX = e->fieldPosition.x;
    p->targetY = e->fieldPosition.y;
    p->targetZ = e->fieldPosition.z;
    gMapEnmCount++;
    gMapEnmTileCount += d->tileCount;
    p->tiles = AllocObjTiles(d->tileCount * 32, NULL);
    p->palette = LoadObjPalette(d->palette, 32);
    p->gfx = NULL;
    AnimInit(&p->anim, NULL, NULL);
    TaskPoolInit(&p->tasks, 2);

    if ((d->flags & MAP_ENM_DEF_FLAG_NO_SHADOW) == 0) {
        TaskCreate(&p->tasks, &gTaskDescFldShadow, e);
    }

    if (d->flags & MAP_ENM_DEF_FLAG_GUARD) {
        p->flags |= MAP_ENM_FLAG_PERSISTENT;
        ColliderInit(&p->collider, 11, d->radius, d->height);
    } else {
        ColliderInit(&p->collider, 3, d->radius, d->height);
    }

    ColliderSetPosition(&p->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    ColliderSetDisabled(&p->collider, 1);
    MapEnmApplyRoomFlags(p);
}

void MapEnmDraw(MapEnmWork* p) {
    FldObj* q = &p->obj;
    u16 flags;
    u16 v;
    s32 k;
    s32 x;
    s32 y;
    s32 z;
    s32 t;

    if (p->gfx == NULL) {
        return;
    }

    t = p->flags & MAP_ENM_FLAG_HFLIP;
    flags = SPRITE_PRIORITY(2);

    if (t) {
        flags = SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
    }

    k = q->fieldPosition.y >> 8;
    v = -0x1004 - k * 4;
    q->shadowZ = q->fieldPosition.ground;
    q->shadowPriority = v + 1;
    z = 0;
    x = (p->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    t = flags;
    y = k + (q->fieldPosition.z >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, p->gfx, p->tiles, p->palette, NULL, t, v);
    TaskPoolDraw(&p->tasks);
}

void MapEnmDestroy(MapEnmWork* p) {
    MapEnmCache* q;

    if (gGameState.fieldResume != 0 && (p->flags & MAP_ENM_FLAG_REMOVED) == 0 &&
        ((gMapRoomState->flags & ROOM_FLAG_START_BATTLE) == 0 || (p->flags & MAP_ENM_FLAG_PERSISTENT))) {
        q = ListPoolFirstFree(&gGameState.enemyCachePool);

        if (q != NULL) {
            q->def = p->def;
            q->update = p->update;
            q->pos = p->obj.fieldPosition;
            q->angle = p->obj.angle;
            q->speed = p->obj.speed;
            ListPoolActivate(&q->node, &gGameState.enemyCachePool);
        }
    }

    gMapEnmCount--;
    gMapEnmTileCount -= p->def->tileCount;
    ColliderUnregister(&p->collider);
    ReleaseObjTiles(p->tiles);
    ReleaseObjPalette(p->palette);
    TaskPoolDestroy(&p->tasks);
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

    for (i = 0; i < gMapGmkCount; i++) {
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
            if (MapCellIsFreeOfType(x + i, y + j, n) == 0) {
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
            if ((u8)MapGmkIsAreaSparse(rx, sy) != 0 && (u8)MapAreaIsFreeOfType(rx, sy, 2, 2, 0) != 0) {
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
            if ((u8)MapGmkIsAreaSparse(rx, sy) != 0 && MapCellIsFreeOfType(rx, sy, 8) != 0) {
                s32 y1 = (s16)(sy + 1);

                if (MapCellIsFreeOfType(rx, y1, 4) != 0) {
                    s32 y2 = (s16)(sy + 2);

                    if (MapCellIsFreeOfType(rx, y2, 0) != 0) {
                        s32 x1 = (s16)(rx + 1);

                        if (MapCellIsFreeOfType(x1, sy, 4) != 0 && MapCellIsFreeOfType(x1, y1, 0) != 0 &&
                            MapCellIsFreeOfType(x1, y2, 0) != 0 && (u8)MapCellHeightExceeds(rx, sy, 3) != 0) {
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
            if ((u8)MapGmkIsAreaSparse(x, cy) != 0) {
                if (MapCellIsFreeOfType(x, cy, 4) != 0) {
                    if (MapCellIsFreeOfType(x, cy + 1, 0) != 0) {
                        if (MapCellIsFreeOfType(x, cy + 2, 0) != 0) {
                            if (MapCellIsFreeOfType(x, cy + 3, 0) != 0) {
                                if ((u8)MapCellHeightExceeds(x, cy, 3) != 0) {
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
            if ((u8)MapGmkIsAreaSparse(rx, sy) != 0 && MapCellIsFreeOfType(rx, sy, 6) != 0) {
                s32 y1 = (s16)(sy + 1);

                if (MapCellIsFreeOfType(rx, y1, 0) != 0) {
                    s32 y2 = (s16)(sy + 2);

                    if (MapCellIsFreeOfType(rx, y2, 0) != 0) {
                        s32 x1 = (s16)(rx + 1);

                        if (MapCellIsFreeOfType(x1, sy, 9) != 0 && MapCellIsFreeOfType(x1, y1, 6) != 0 &&
                            MapCellIsFreeOfType(x1, y2, 0) != 0 && (u8)MapCellHeightExceeds(rx, sy, 3) != 0) {
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
            if ((u8)MapGmkIsAreaSparse(rx, sy) != 0 && (u8)MapAreaIsFreeOfType(rx, sy, 3, 3, 8) != 0) {
                u16 a;
                u16 b;

                if ((u8)MapWallFaceIsUnreserved(rx, sy, 3) == 0) {
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
            if ((u8)MapGmkIsAreaSparse(rx, sy) != 0 && (u8)MapAreaIsFreeOfType(rx, sy, 3, 3, 9) != 0) {
                u16 a;
                u16 b;

                if ((u8)MapWallFaceIsUnreserved(rx, sy, 3) == 0) {
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
            if ((u8)MapGmkIsAreaSparse(rx, sy) != 0 && MapCellIsFreeOfType(rx, sy, 0) != 0) {
                if (MapCellIsFreeOfType(rx, sy + 1, 3) != 0) {
                    if (MapCellIsFreeOfType(rx + 1, sy, 3) != 0 &&
                        MapCellIsFreeOfType(rx + 1, sy + 1, 8) != 0) {
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
            if ((u8)MapGmkIsAreaSparse(x, cy) != 0) {
                if (MapCellIsFreeOfType(x, cy, 1) != 0) {
                    if (MapCellIsFreeOfType(x, cy + 1, 7) != 0) {
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
            if ((u8)MapGmkIsAreaSparse(rx, sy) != 0 && MapCellIsFreeOfType(rx, sy, 5) != 0) {
                s32 y1 = (s16)(sy + 1);

                if (MapCellIsFreeOfType(rx, y1, 9) != 0) {
                    if (MapCellIsFreeOfType(rx + 1, sy, 0) != 0 &&
                        MapCellIsFreeOfType(rx + 1, y1, 5) != 0) {
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
            if ((u8)MapGmkIsAreaSparse(rx, sy) != 0 && MapCellIsFreeOfType(rx, sy, 2) != 0) {
                s32 y1 = (s16)(sy + 1);

                if (MapCellIsFreeOfType(rx, y1, 0) != 0) {
                    s32 y2 = (s16)(sy + 2);

                    if (MapCellIsFreeOfType(rx, y2, 0) != 0) {
                        s32 x1 = (s16)(rx + 1);

                        if (MapCellIsFreeOfType(x1, sy, 2) != 0 && MapCellIsFreeOfType(x1, y1, 0) != 0 &&
                            MapCellIsFreeOfType(x1, y2, 0) != 0 && (u8)MapCellHeightExceeds(rx, sy, 3) != 0) {
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
            if ((u8)MapGmkIsAreaSparse(rx, sy) != 0 && (u8)MapAreaIsFreeOfType(rx, sy, 3, 3, 0) != 0) {
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
            if ((u8)MapGmkIsAreaSparse(rx, sy) != 0 && (u8)MapAreaIsFreeOfType(rx, sy, 4, 4, 0) != 0) {
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
            if ((u8)MapGmkIsAreaSparse(rx, sy) != 0 && (u8)MapAreaIsFreeOfType(rx, sy, 5, 5, 0) != 0) {
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

            if ((u8)MapAreaIsFreeOfType(sx, sy, 2, 2, 0) != 0 && e->z == MapCellAt(sx, sy)->lowerZ) {
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

    for (i = 0; i < gMapGmkCount; i++) {
        if (gMapGmkPlacements[i].def->palette == a) {
            return 0;
        }
    }

    return 1;
}

s32 MapGmkNeedsTiles(u8 flag, const void* a) {
    s32 i;

    if (flag != 0) {
        return 1;
    }

    for (i = 0; i < gMapGmkCount; i++) {
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

        if (p->hasStairs == 0 && p->spotLowerZ != 0x100000) {
            gMapGmkTileCount += 0x4C;
            gMapGmkPaletteCount++;
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
        n = &gMapGmkCount;

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
            gMapGmkTileCount += (size = q->tilesSize) / 32;
            gMapGmkPaletteCount++;
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
            gMapGmkPlacements[gMapGmkCount].flags = GMK_FLAG_USED;
        } else {
            gMapGmkPlacements[gMapGmkCount].flags = 0;
        }

        gMapGmkPlacements[gMapGmkCount].def = q;
        gMapGmkPlacements[gMapGmkCount].pos = w;
        gMapGmkTileCount += q->tilesSize >> 5;
        gMapGmkPaletteCount++;
        gMapGmkCount++;
        p = MapCellAtPos(w.x, w.y + w.z);
        p->flags |= MAP_CELL_FLAG_CHEST;
    }
}

void MapGmkPlaceGmk04() {
    FldPos w;

    if (gMapRoomState->roomType == 6 || gMapRoomState->roomType == 0x17) {
        MapGmkFindSpot(&w, gMapGmk04Def.spotFinder);
        gMapGmkPlacements[gMapGmkCount].flags = 0;
        gMapGmkPlacements[gMapGmkCount].def = &gMapGmk04Def;
        gMapGmkPlacements[gMapGmkCount].pos = w;
        gMapGmkTileCount += gMapGmk04Def.tilesSize >> 5;
        gMapGmkPaletteCount++;
        gMapGmkCount++;
    }
}

void MapGmkPlaceMoogle() {
    FldPos w;

    if (gMapRoomState->roomType == 11) {
        MapGmkFindSpot(&w, gMapGmk05Def.spotFinder);
        gMapGmkPlacements[gMapGmkCount].flags = 0;
        gMapGmkPlacements[gMapGmkCount].def = &gMapGmk05Def;
        gMapGmkPlacements[gMapGmkCount].pos = w;
        gMapGmkTileCount += gMapGmk05Def.tilesSize >> 5;
        gMapGmkPaletteCount++;
        gMapGmkCount++;
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

    for (i = gMapGmkCount; i <= 15; i++) {
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

        if (gMapGmkTileCount + t->tilesSize / 32 > 0x200) {
            return;
        }

        f = (u8)MapGmkIsPaletteUnused(t->palette);

        if (f != 0 && gMapGmkPaletteCount > 5) {
            return;
        }

        if (MapGmkFindSpot(&w, t->spotFinder) == 0) {
            return;
        }

        gMapGmkPlacements[gMapGmkCount].flags = 0;
        gMapGmkPlacements[gMapGmkCount].def = t;
        gMapGmkPlacements[gMapGmkCount].pos = w;
        gMapGmkTileCount += t->tilesSize >> 5;
        gMapGmkCount++;

        if (f != 0) {
            gMapGmkPaletteCount++;
        }
    }
}

void MapGmkPlaceRandomGimmicks() {
    s32 i;

    for (i = gMapGmkCount; i < 16; i++) {
        FldPos w;
        const MapGmkDef* e = &gMapGmkDefs[GetRandomMapGmkIndex(i)];
        u8 f = MapGmkNeedsTiles(e->ownTiles, e->tiles);
        u8 g;

        if (f != 0) {
            if ((e->tilesSize >> 5) + gMapGmkTileCount > 512) {
                continue;
            }
        }

        g = MapGmkIsPaletteUnused(e->palette);

        if (g != 0) {
            if (gMapGmkPaletteCount > 5) {
                continue;
            }
        }

        if (MapGmkFindSpot(&w, e->spotFinder) == 0) {
            continue;
        }

        gMapGmkPlacements[gMapGmkCount].flags = 0;
        gMapGmkPlacements[gMapGmkCount].def = e;
        gMapGmkPlacements[gMapGmkCount].pos = w;
        gMapGmkCount++;

        if (f != 0) {
            gMapGmkTileCount += e->tilesSize >> 5;
        }

        if (g != 0) {
            gMapGmkPaletteCount++;
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
    return 512 - gMapGmkTileCount;
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
    if (gGameState.fieldResume == 0) {
        gMapGmkPlacements = EwramAlloc(sizeof(MapGmkPlacement) * 16);
        gMapGmkCount = 0;
        gMapGmkPaletteCount = 0;
        gMapGmkTileCount = 0;
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

        if (p->hasStairs == 0 && p->spotLowerZ != 0x100000) {
            TaskCreate(&gFieldState->tasks, &gTaskDescMapGmkJump, p);
        }
    }

    for (i = 0; i < gMapGmkCount; i++) {
        d = gMapGmkPlacements[i].def;

        if ((gMapGmkPlacements[i].flags & GMK_FLAG_DESTROYED) == 0) {
            TaskCreate(&gFieldState->tasks, d->desc, &gMapGmkPlacements[i]);
        }
    }

    TaskCreate(&gFieldState->tasks, &gTaskDescMapGmkDmy, NULL);
}

void MapGmkFree() {
    if (gGameState.fieldResume == 0) {
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
    if (gGameState.fieldResume == 0) {
        MapRoomDef* p = gMapRoomDefs[gMapFloorState.world];

        MapApplyLayer1DecorRules(p->layer1DecorRules);
        MapApplyLayer2DecorRules(p->layer2DecorRules);
    }
}

void MapAnmSetupSlot(MapAnmSlot* p, const MapGmkDef* q) {
    p->tiles = q->tiles;
    p->frameSize = q->tilesSize;
    p->dest += q->unk_0A << 5;
    p->timer = 0;
    p->script = q->palette;
    p->scriptPos = q->palette;
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
            gEventKeyList = &gEventKeyLists[p->keyList];
            gEventKeyProgress = &gMapFloorState.eventKeyProgress[i];
            return 1;
        }

        i++;
        p++;
    }

    return 0;
}

u8 CountRemainingEventKeys() {
    return gEventKeyList->count - gEventKeyProgress->paid;
}

EventKey* GetEventKey(u8 a) {
    EventKey* p = &gEventKeyList->keys[gEventKeyProgress->paid];
    EventKey* q = &p[a];

    gEventKey = *q;

    if (a == 0 && q->rule == 4 && gEventKeyProgress->remaining != 0) {
        gEventKey.value = gEventKeyProgress->remaining;
    }

    return &gEventKey;
}

u8 DoorAcceptsMapCard(MapCardAttributes* p) {
    EventKey* q;
    u8 n;

    if (IsEventDoor(gMapRoomState->doorRoom, gMapRoomState->doorSide) == 0) {
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

s32 PayEventKey(UnkStruct_080E8E24* p) {
    if (GetEventKey(0)->rule == 4) {
        if (gEventKey.value > p->unk_02) {
            gEventKey.value -= p->unk_02;
            gEventKeyProgress->remaining = gEventKey.value;
            return 0;
        }

        gEventKeyProgress->remaining = 0;
    }

    gEventKeyProgress->paid++;
    return 1;
}

const UnkStruct_080E8E24* PickRandomPrzCard(u8 a) {
    u16 v = GetRandom() % 10000;
    PrzCardChance** t = gWorldPrzCardChances;
    PrzCardChance* p = t[gGameState.world];

    while (p->cardIndex != 41) {
        const UnkStruct_080E8E24* q = &gPrzCardKinds[p->cardIndex];
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

s32 CreateMapPrzCardTask(const UnkStruct_080E8E24* a, u8 b, s32 c, s32 d, s32 e) {
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
    const UnkStruct_080E8E24* q;

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
    UnkStruct_080E8E24* p = gWorldPrizeLists[gGameState.world];
    const UnkStruct_080E8E24* e;

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

    if ((gGameState.flags & GAME_FLAG_RIKU_CLEAR) && gGameState.world == WORLD_CASTLE_OBLIVION && IsCardKindObtained(16) != 0) {
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
        UnkStruct_080E8E24** t = gWorldPrizeLists;

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
    gMapDbgUpdate = a;
}

void MapDbgSetUpdateAndRun(ModeFunc a) {
    MapDbgSetUpdate(a);
    gMapDbgUpdate();
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
        TaskKill(&gFieldState->tasks, gMapDbgAllmapRoomTask);
        gMapDbgAllmapRoomTask = NULL;
        MapDbgSetUpdateAndRun(MapDbgWaitMenu);
        return;
    }

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        TaskKill(&gFieldState->tasks, gMapDbgAllmapRoomTask);
        gMapDbgAllmapRoomTask = NULL;
        MapDbgSetUpdateAndRun(MapDbgWaitRoomCreate);
        return;
    }

    if (gMapDbgEditing != 0) {
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

    if (FadeIsActive() == 0) {
        SetCurrentMapRoom(gMapRoomState->doorRoom, gMapRoomState->doorSide);

        if (gMapRoomState->doorRoom != MAP_ROOM_EXIT_HALL && gMapRoomState->doorRoom != MAP_ROOM_ENTRANCE_HALL) {
            ModeRequest(&gModeMapDbg, 0);
        } else {
            RequestMapMode();
        }
    }
}

void MapDbgFreeCameraMode() {
    if (gMapDbgEditing != 0) {
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

    if (gMapDbgEditing == 0) {
        ModeRequest(&gModeMapDbg, 0);
    }
}

void MapDbgWaitMenu() {
    if ((gFieldState->flags & FIELD_FLAG_MENU_OPEN) == 0 && (gMapRoomState->flags & ROOM_FLAG_SAVE_MENU_OPEN) == 0) {
        gMapDbgAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
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
        gMapDbgAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
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
    gMapDbgAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
    MapDbgSetUpdate(MapDbgMain);

    if (gGameState.fieldResume != 0) {
        MapSetCameraTarget(gGameState.fieldPosition.x, gGameState.fieldPosition.y + gGameState.fieldPosition.z);
    } else {
        MapSetCameraTarget(gFieldState->spawnX, gFieldState->spawnY);
    }

    MapSnapCamera();
    ClearFieldResume();
    SeedRandom(gFrameCounter);
    m4aSongNumStartOrContinue(p->song);
    TaskPoolInit(&gMapDbgTasks, 1);
    TaskCreate(&gMapDbgTasks, &gTaskDescMapDbg, &gMapDbgEditing);
    TaskCreate(&gFieldState->tasks, &gTaskDescMapDmg, NULL);
    FadeStartIn(FADE_MODE_BLACK, 16);
}

void Mode_MapDbg_1() {
    TaskPoolUpdate(&gMapDbgTasks);
    TaskPoolDraw(&gMapDbgTasks);
    gMapDbgUpdate();
    UpdatePlayTime();
}

void Mode_MapDbg_2() {
    DestroyMapField();
    MapGmkFree();
    EwramFree(gFieldState);
    EwramFree(gMapRoomState);
    TaskPoolDestroy(&gMapDbgTasks);
}

void MapFldSetUpdate(ModeFunc a) {
    gMapFldUpdate = a;
}

void MapFldSetUpdateAndRun(ModeFunc a) {
    MapFldSetUpdate(a);
    gMapFldUpdate();
}

void MapFldCreateWorldLogo() {
    switch (gMapFloorState.world) {
    case WORLD_ATLANTICA:
        gMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)2);
        break;
    case WORLD_HALLOWEEN_TOWN:
        gMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)6);
        break;
    case WORLD_MONSTRO:
        gMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)5);
        break;
    case WORLD_NEVER_LAND:
        gMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)7);
        break;
    case WORLD_OLYMPUS_COLISEUM:
        gMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)3);
        break;
    case WORLD_HOLLOW_BASTION:
        gMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)8);
        break;
    case WORLD_DESTINY_ISLANDS:
        gMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)9);
        break;
    case WORLD_AGRABAH:
        gMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)1);
        break;
    case WORLD_TRAVERSE_TOWN:
        gMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)10);
        break;
    case WORLD_TWILIGHT_TOWN:
        gMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)11);
        break;
    case WORLD_CASTLE_OBLIVION:
        gMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)12);
        break;
    default:
        gMapFldWorldLogoTask = TaskCreate(&gMapRoomState->tasks, &gTaskDescWLogo, (void*)4);
        break;
    }
}

void MapFldDestroyAllmapRoom() {
    if (gMapFldAllmapRoomTask != NULL) {
        TaskKill(&gFieldState->tasks, gMapFldAllmapRoomTask);
        gMapFldAllmapRoomTask = NULL;
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
    u8 r = IsTaskActive(gMapFldWorldLogoTask);

    if (r != 0) {
        TaskPoolUpdate(&gMapRoomState->tasks);
        TaskPoolDraw(&gMapRoomState->tasks);
        TaskPoolUpdate(&gFieldState->tasks);
        DrawMapField();
    } else {
        u16 t = gMapFloorState.flags | FLOOR_FLAG_LOGO_SHOWN;
        gMapFloorState.flags = t;
        gMapFldWorldLogoTask = NULL;
        gMapFldAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
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

    if (FadeIsActive() == 0 && (gGameState.progression.tutorialFlags & 0x200) != 0 &&
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

    if (r != 0) {
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

    if (FadeIsActive() == 0) {
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

    if (FadeIsActive() == 0) {
        RequestFieldResume();
        ModeRequest(&gModeAllmap, 1);
    }
}

void MapFldWaitMenu() {
    if ((gFieldState->flags & FIELD_FLAG_MENU_OPEN) == 0 && (gMapRoomState->flags & ROOM_FLAG_SAVE_MENU_OPEN) == 0) {
        SetupBg(0, 3, 31, 14);
        SetBgPriority(0, 0);
        MapGmkCreateTasks();
        gMapFldAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
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
        gMapFldAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
        MapFldSetUpdateAndRun(MapFldMain);
    } else {
        UpdateMapField();
        DrawMapField();
    }
}

void func_080E9F30() {
    DrawMapField();

    if (gUnk_02034FBC == 0) {
        ModeRequest(&gModeMapFld, 0);
    }
}

void Mode_MapFld_0() {
    MapRoomDef* p;

    if ((gMapFloorState.flags & FLOOR_FLAG_LOGO_SHOWN) && gGameState.fieldResume == 0) {
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
    gMapFldWorldLogoTask = NULL;
    gMapFldAllmapRoomTask = NULL;
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
    } else if (gGameState.fieldResume != 0) {
        MapSetCameraTarget(gGameState.fieldPosition.x, gGameState.fieldPosition.y + gGameState.fieldPosition.z);

        if ((s8)gGameState.mapMenuCursor != -1) {
            gDispCnt &= ~DISPCNT_OBJ_ON;
            TaskCreate(&gFieldState->tasks, &gTaskDescMapMenu, NULL);
            MapFldSetUpdate(MapFldWaitMenu);
        } else {
            gMapFldAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
            MapFldSetUpdate(MapFldMain);
        }
    } else {
        gMapFldAllmapRoomTask = CreateAllmapRoomTask(&gFieldState->tasks);
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
    gMapFldUpdate();
    UpdatePlayTime();
}

void Mode_MapFld_2() {
    DestroyMapField();
    MapGmkFree();
    EwramFree(gFieldState);
    EwramFree(gMapRoomState);
}

void MapFixSetUpdate(ModeFunc a) {
    gMapFixUpdate = a;
}

void MapFixSetUpdateAndRun(ModeFunc a) {
    MapFixSetUpdate(a);
    gMapFixUpdate();
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
    } else if (FadeIsActive() == 0 && (gGameState.progression.tutorialFlags & 0x200) != 0 &&
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

    if (FadeIsActive() == 0) {
        EnterFloorWorld();
        ModeRequest(&gModeMapFld, 0);
    }
}

void MapFixLeaveEntranceHall() {
    DrawMapField();

    if (FadeIsActive() != 0) {
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
            gMapFixEventDelay = 60;
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

    if (FadeIsActive() != 0) {
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
    if (gMapFixEventDelay != 0) {
        gMapFixEventDelay--;
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

    if (gGameState.fieldResume != 0) {
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
    gMapFixUpdate();
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
        if (b != 0) {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gUnk_09963D64[c];
            } else {
                src = gUnkEu_09955250[c];
            }
        } else {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gUnk_09964EE4[c];
            } else {
                src = gUnk_09962BE4[c];
            }
        }

        break;
    case LANGUAGE_FRENCH:
        if (b != 0) {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gUnkEu_0995BB50[c];
            } else {
                src = gUnkEu_09959850[c];
            }
        } else {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gUnkEu_0995CCD0[c];
            } else {
                src = gUnkEu_0995A9D0[c];
            }
        }

        break;
    case LANGUAGE_SPANISH:
        if (b != 0) {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gUnkEu_09960150[c];
            } else {
                src = gUnkEu_0995DE50[c];
            }
        } else {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gUnkEu_099612D0[c];
            } else {
                src = gUnkEu_0995EFD0[c];
            }
        }

        break;
    case LANGUAGE_ITALIAN:
        if (b != 0) {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gUnkEu_09964750[c];
            } else {
                src = gUnkEu_09962450[c];
            }
        } else {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gUnkEu_099658D0[c];
            } else {
                src = gUnkEu_099635D0[c];
            }
        }

        break;
    case LANGUAGE_GERMAN:
    default:
        if (b != 0) {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gUnkEu_09968D50[c];
            } else {
                src = gUnkEu_09966A50[c];
            }
        } else {
            if (gGameState.flags & GAME_FLAG_RIKU) {
                src = gUnkEu_09969ED0[c];
            } else {
                src = gUnkEu_09967BD0[c];
            }
        }

        break;
    }
#else
    if (b != 0) {
        if (gGameState.flags & GAME_FLAG_RIKU) {
            src = gUnk_09963D64[c];
        } else {
            src = gUnk_09961A64[c];
        }
    } else {
        if (gGameState.flags & GAME_FLAG_RIKU) {
            src = gUnk_09964EE4[c];
        } else {
            src = gUnk_09962BE4[c];
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
        RequestDma3Copy((void*)&gUnk_09966064[*q * 32], (u8*)GetBgCharBase(1) + off + i * 32, 0x20);
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
        RequestDma3Copy((void*)&gUnk_09966064[*q * 32], (u8*)GetBgCharBase(1) + off + i * 32, 0x20);
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
    u8 i = gNewGameSlotMenuWork->isRiku != 0 ? a + 2 : a;
    e = &gGameState.fileSummaries[i];

    if (e->level != 0) {
        NewGameSlotMenuLoadFloorTiles(i, 1, e->floor);
        gNewGameSlotMenuWork->textSlotCount = LoadTextSlots(GetMapWorldName(e->world), gNewGameSlotMenuWork->textSlots);

        if (gNewGameSlotMenuWork->isRiku == 0) {
            LoadObjPaletteBank(gNewGameSlotMenuWork->palette8->index, gUnk_09991C04);
        } else {
            LoadObjPaletteBank(gNewGameSlotMenuWork->palette8->index, gUnk_09991C44);
        }
    } else {
        NewGameSlotMenuLoadFloorTiles(i, 1, 13);
        gNewGameSlotMenuWork->textSlotCount = 0;
    }

    if (gNewGameSlotMenuWork->selectedSlot == 0) {
        if (gNewGameSlotMenuWork->isRiku != 0) {
            LoadBgMap(1, &gUnk_09985F44[0x8800], 0x800);
        } else {
            LoadBgMap(1, &gUnk_09985F44[0x7800], 0x800);
        }

        SetBgScroll(1, 0, (u16)-9);
    } else {
        if (gNewGameSlotMenuWork->isRiku != 0) {
            LoadBgMap(1, &gUnk_09985F44[0x9000], 0x800);
        } else {
            LoadBgMap(1, &gUnk_09985F44[0x8000], 0x800);
        }

        SetBgScroll(1, 0, (u16)-6);
    }
}

void NewGameSlotMenuDeselectSlot(u8 a) {
    u8 idx = gNewGameSlotMenuWork->isRiku != 0 ? a + 2 : a;
    SaveFileSummary* e = &gGameState.fileSummaries[idx];

    if (e->level != 0) {
        NewGameSlotMenuLoadFloorTiles(idx, 0, e->floor);
    } else {
        NewGameSlotMenuLoadFloorTiles(idx, 0, 13);
    }

    gNewGameSlotMenuWork->textSlotCount = 0;
}

void NewGameSlotMenuDraw() {
    s32 t;
    s32 u;

    DrawSprite(128, gNewGameSlotMenuWork->y >> 8, gUnk_09EF8D68[1], gNewGameSlotMenuWork->tiles2,
        gNewGameSlotMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
    DrawSprite(128, gNewGameSlotMenuWork->y2 >> 8, gUnk_09EF8D68[2], gNewGameSlotMenuWork->tiles2,
        gNewGameSlotMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);

    if (gNewGameSlotMenuWork->isRiku == 0) {
        DrawSprite(56, 112, gSor1ff00Frames[0], gNewGameSlotMenuWork->tiles4,
            gNewGameSlotMenuWork->palette4, NULL, SPRITE_PRIORITY(1), 80);
        DrawSprite(72, 96, gDona2Fl00Frames[0], gNewGameSlotMenuWork->tiles5, gNewGameSlotMenuWork->palette5, NULL,
            SPRITE_PRIORITY(1) | SPRITE_FLAG_HFLIP, 81);
        DrawSprite(40, 96, gGoofy2Fl00Frames[0], gNewGameSlotMenuWork->tiles6, gNewGameSlotMenuWork->palette6, NULL,
            SPRITE_PRIORITY(1), 81);
    } else {
        DrawSprite(56, 112, gRikuFf00Frames[0], gNewGameSlotMenuWork->tiles7, gNewGameSlotMenuWork->palette7, NULL,
            SPRITE_PRIORITY(1), 81);
    }

    DrawSprite(0, 16, gMapUiSpriteUs_098A8F28, gNewGameSlotMenuWork->tiles3, gNewGameSlotMenuWork->palette3, NULL, SPRITE_PRIORITY(1), 90);
    t = 45;
    u = gNewGameSlotMenuWork->selectedSlot * t;
    ApproachValueHalf(&gNewGameSlotMenuWork->y3, (gNewGameSlotMenuWork->slotBaseY + u) << 8);
    DrawSprite(76, gNewGameSlotMenuWork->y3 >> 8, AnimGetGfx(&gNewGameSlotMenuWork->anim),
        gNewGameSlotMenuWork->tiles, gNewGameSlotMenuWork->palette, NULL, 0, 70);
    DrawTextSlots(100, u + (gNewGameSlotMenuWork->slotBaseY + 22), gNewGameSlotMenuWork->textSlots,
        gNewGameSlotMenuWork->palette8, 50, gNewGameSlotMenuWork->textSlotCount);
    DrawTextSlots(
        (240 - GetTextSlotsWidth(gNewGameSlotMenuWork->textSlots2, gNewGameSlotMenuWork->textSlotCount2)) / 2, 134,
        gNewGameSlotMenuWork->textSlots2, gNewGameSlotMenuWork->palette9, 50, gNewGameSlotMenuWork->textSlotCount2);
}

void NewGameSlotMenuMoveCursor(NewGameSlotMenuWork* w) {
    u8 prev = w->selectedSlot;

    if (GetKeysRepeat() & DPAD_UP) {
        w->selectedSlot = w->selectedSlot != 0 ? w->selectedSlot - 1 : 1;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysRepeat() & DPAD_DOWN) {
        w->selectedSlot = w->selectedSlot == 0 ? w->selectedSlot + 1 : 0;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (prev != w->selectedSlot) {
        NewGameSlotMenuDeselectSlot(prev);
        NewGameSlotMenuSelectSlot(w->selectedSlot);
    }
}

void NewGameSlotMenuSlideIn(NewGameSlotMenuWork* w) {
    if (w->timer != 0) {
        ApproachValue(&w->y, 0, w->timer);
        ApproachValue(&w->y2, 0x9800, w->timer);
        w->timer--;
    } else {
        w->update = NewGameSlotMenuInput;
    }
}

void NewGameSlotMenuInput(NewGameSlotMenuWork* w) {
    NewGameSlotMenuMoveCursor(w);

    if (GetKeysPressed() & B_BUTTON) {
        m4aSongNumStart(SONG_SYS_CLOSE);
    } else {
        if (!(GetKeysPressed() & (A_BUTTON | START_BUTTON))) {
            return;
        }

        switch (w->selectedSlot) {
        case 0:
            gGameState.flags &= ~GAME_FLAG_SECOND_FILE;
            break;
        case 1:
            gGameState.flags |= GAME_FLAG_SECOND_FILE;
            break;
        }

        m4aSongNumStart(SONG_SYS_SAVELOAD);
        w->confirmed = 1;
    }

    w->timer = 16;
    w->update = NewGameSlotMenuSlideOut;
}

void NewGameSlotMenuSlideOut(NewGameSlotMenuWork* w) {
    if (w->timer != 0) {
        ApproachValue(&w->y, -0x800, w->timer);
        ApproachValue(&w->y2, 0xA000, w->timer);
        w->timer--;
    } else {
        FadeStartOut(FADE_MODE_BLACK, 90);
        w->update = NewGameSlotMenuExit;
    }
}

void NewGameSlotMenuExit(NewGameSlotMenuWork* w) {
    if (FadeIsActive() != 0) {
        return;
    }

    if (w->confirmed != 0) {
        if (w->isRiku != 0) {
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

    gNewGameSlotMenuWork = EwramAlloc(sizeof(NewGameSlotMenuWork));
    gNewGameSlotMenuWork->confirmed = 0;
    gNewGameSlotMenuWork->isRiku = (gGameState.flags >> 3) & 1;
    gNewGameSlotMenuWork->slotBaseY = 33;
    gNewGameSlotMenuWork->timer = 16;
    gNewGameSlotMenuWork->update = NewGameSlotMenuSlideIn;
    SetBgMode0();
    SetupBg(3, 0, 28, 0);
    SetupBg(1, 0, 29, 0);
    SetupBg(0, 0, 30, 0);
    SetBgPriority(3, 3);
    SetBgPriority(1, 0);
    SetBgPriority(0, 0);
#ifdef VERSION_EU
    LoadBgTiles(0, gUnk_099661A4, 0x1FA0);

    switch (gLanguage) {
    case LANGUAGE_FRENCH:
        RequestDma3Copy((void*)gUnkEu_0996D130, (u8*)GetBgCharBase(0) + 0x800, 0x800);
        break;
    case LANGUAGE_SPANISH:
        RequestDma3Copy((void*)gUnkEu_0996D930, (u8*)GetBgCharBase(0) + 0x800, 0x800);
        break;
    case LANGUAGE_ITALIAN:
        RequestDma3Copy((void*)gUnkEu_0996E130, (u8*)GetBgCharBase(0) + 0x800, 0x800);
        break;
    case LANGUAGE_GERMAN:
        RequestDma3Copy((void*)gUnkEu_0996E930, (u8*)GetBgCharBase(0) + 0x800, 0x800);
        break;
    }

    LoadBgPalette(3, gUnk_09991D44, 0x200);
    LoadBgMap(3, gUnk_0998CF44, 0x800);
    LoadBgPalette(1, gUnk_09991D44, 0x200);
    LoadBgPalette(0, gUnk_09991D44, 0x200);
    LoadBgMap(0, gUnk_0998F744, 0x800);
#else
    LoadBgTiles(3, gUnk_099661A4, 0x1FA0);
    LoadBgPalette(3, gUnk_09991D44, 0x200);
    LoadBgMap(3, gUnk_0998CF44, 0x800);
    LoadBgTiles(1, gUnk_099661A4, 0x1FA0);
    LoadBgPalette(1, gUnk_09991D44, 0x200);
    LoadBgTiles(0, gUnk_099661A4, 0x1FA0);
    LoadBgPalette(0, gUnk_09991D44, 0x200);
    LoadBgMap(0, gUnk_0998F744, 0x800);
#endif
    SetBgScroll(0, 0, 0xFFFC);
    gNewGameSlotMenuWork->palette2 = LoadObjPalette(gUnk_09991D04, 32);
    gNewGameSlotMenuWork->tiles2 = LoadObjTiles(gUnk_098A8C66, 0x2C0);
    gNewGameSlotMenuWork->y = -0x800;
    gNewGameSlotMenuWork->y2 = 0xA000;
    gNewGameSlotMenuWork->tiles4 = AllocObjTiles(0x340, gSor1ff00Tiles);
    gNewGameSlotMenuWork->palette4 = LoadObjPalette(gSoraPalette, 32);
    gNewGameSlotMenuWork->tiles5 = AllocObjTiles(0x280, gDona2Fl00Tiles);
    gNewGameSlotMenuWork->palette5 = LoadObjPalette(gDonald2Palette, 32);
    gNewGameSlotMenuWork->tiles6 = AllocObjTiles(0x400, gGoofy2Fl00Tiles);
    gNewGameSlotMenuWork->palette6 = LoadObjPalette(gGoofy2Palette, 32);
    gNewGameSlotMenuWork->tiles7 = AllocObjTiles(0x400, gRikuFf00Tiles);
    gNewGameSlotMenuWork->palette7 = LoadObjPalette(gRikuPalette, 32);
    gNewGameSlotMenuWork->palette3 = LoadObjPalette(gUnk_09991D24, 32);
    gNewGameSlotMenuWork->tiles3 = LoadObjTiles(gUnk_098A8F8A, 0x4C0);
    gNewGameSlotMenuWork->palette = LoadObjPalette(gUnk_09991BE4, 32);
    gNewGameSlotMenuWork->tiles = AllocObjTiles(0x120, gUnk_098A8AE2);
    AnimInit(&gNewGameSlotMenuWork->anim, gUnk_09EF8D88, gUnk_09EF8D78);
    AnimStart(&gNewGameSlotMenuWork->anim, 0, ANIM_FLAG_LOOP);
    gNewGameSlotMenuWork->palette8 = LoadObjPalette(gUnk_09991C04, 32);
    gNewGameSlotMenuWork->textSlotCount = 0;
    InitTextSlots(gNewGameSlotMenuWork->textSlots, 36);
    InitTextSlots(gNewGameSlotMenuWork->textSlots2, 54);
    gNewGameSlotMenuWork->palette9 = LoadObjPalette(gUnk_09991BE4, 32);
#ifdef VERSION_EU
    gNewGameSlotMenuWork->textSlotCount2 = LoadTextSlots(eu_0805E924(&gUnkEu_08892780), gNewGameSlotMenuWork->textSlots2);
#else
    gNewGameSlotMenuWork->textSlotCount2 = LoadTextSlots(gUnk_08159E1E, gNewGameSlotMenuWork->textSlots2);
#endif

    if (gNewGameSlotMenuWork->isRiku != 0) {
        v = NewGameSlotMenuShowSummary(2);
        u = NewGameSlotMenuShowSummary(3);
    } else {
        v = NewGameSlotMenuShowSummary(0);
        u = NewGameSlotMenuShowSummary(1);
    }

    if (v != 0) {
        gNewGameSlotMenuWork->selectedSlot = u == 0 ? 1 : 0;
    } else {
        gNewGameSlotMenuWork->selectedSlot = 0;
    }

    NewGameSlotMenuSelectSlot(gNewGameSlotMenuWork->selectedSlot);
    gNewGameSlotMenuWork->y3 = (gNewGameSlotMenuWork->slotBaseY + gNewGameSlotMenuWork->selectedSlot * 45) << 8;
    FadeStartIn(FADE_MODE_BLACK, 8);
}

void Mode_MenuNew_1() {
    if (gNewGameSlotMenuWork->update != NULL) {
        gNewGameSlotMenuWork->update(gNewGameSlotMenuWork);
    }

    NewGameSlotMenuDraw();
}

void Mode_MenuNew_2() {
    ReleaseObjPalette(gNewGameSlotMenuWork->palette2);
    ReleaseObjTiles(gNewGameSlotMenuWork->tiles2);
    ReleaseObjPalette(gNewGameSlotMenuWork->palette3);
    ReleaseObjTiles(gNewGameSlotMenuWork->tiles3);
    ReleaseObjPalette(gNewGameSlotMenuWork->palette);
    ReleaseObjTiles(gNewGameSlotMenuWork->tiles);
    ReleaseObjPalette(gNewGameSlotMenuWork->palette4);
    ReleaseObjTiles(gNewGameSlotMenuWork->tiles4);
    ReleaseObjPalette(gNewGameSlotMenuWork->palette5);
    ReleaseObjTiles(gNewGameSlotMenuWork->tiles5);
    ReleaseObjPalette(gNewGameSlotMenuWork->palette6);
    ReleaseObjTiles(gNewGameSlotMenuWork->tiles6);
    ReleaseObjPalette(gNewGameSlotMenuWork->palette7);
    ReleaseObjTiles(gNewGameSlotMenuWork->tiles7);
    ReleaseObjPalette(gNewGameSlotMenuWork->palette8);
    FreeTextSlots(gNewGameSlotMenuWork->textSlots, 36);
    ReleaseObjPalette(gNewGameSlotMenuWork->palette9);
    FreeTextSlots(gNewGameSlotMenuWork->textSlots2, 54);
    EwramFree(gNewGameSlotMenuWork);
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
            if (b != 0) {
                src = gUnkEu_09955250[c];
            } else {
                src = gUnk_09962BE4[c];
            }
        } else {
            if (b != 0) {
                src = gUnk_09963D64[c];
            } else {
                src = gUnk_09964EE4[c];
            }
        }

        break;
    case LANGUAGE_FRENCH:
        if (a <= 1) {
            if (b != 0) {
                src = gUnkEu_09959850[c];
            } else {
                src = gUnkEu_0995A9D0[c];
            }
        } else {
            if (b != 0) {
                src = gUnkEu_0995BB50[c];
            } else {
                src = gUnkEu_0995CCD0[c];
            }
        }

        break;
    case LANGUAGE_SPANISH:
        if (a <= 1) {
            if (b != 0) {
                src = gUnkEu_0995DE50[c];
            } else {
                src = gUnkEu_0995EFD0[c];
            }
        } else {
            if (b != 0) {
                src = gUnkEu_09960150[c];
            } else {
                src = gUnkEu_099612D0[c];
            }
        }

        break;
    case LANGUAGE_ITALIAN:
        if (a <= 1) {
            if (b != 0) {
                src = gUnkEu_09962450[c];
            } else {
                src = gUnkEu_099635D0[c];
            }
        } else {
            if (b != 0) {
                src = gUnkEu_09964750[c];
            } else {
                src = gUnkEu_099658D0[c];
            }
        }

        break;
    case LANGUAGE_GERMAN:
    default:
        if (a <= 1) {
            if (b != 0) {
                src = gUnkEu_09966A50[c];
            } else {
                src = gUnkEu_09967BD0[c];
            }
        } else {
            if (b != 0) {
                src = gUnkEu_09968D50[c];
            } else {
                src = gUnkEu_09969ED0[c];
            }
        }

        break;
    }
#else
    if (a <= 1) {
        if (b != 0) {
            src = gUnk_09961A64[c];
        } else {
            src = gUnk_09962BE4[c];
        }
    } else {
        if (b != 0) {
            src = gUnk_09963D64[c];
        } else {
            src = gUnk_09964EE4[c];
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
        RequestDma3Copy((void*)&gUnk_09966064[*q * 32], (u8*)GetBgCharBase(1) + off + i * 32, 0x20);
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
        RequestDma3Copy((void*)&gUnk_09966064[*q * 32], (u8*)GetBgCharBase(1) + off + i * 32, 0x20);
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
        gLoadGameMenuWork->textSlotCount = LoadTextSlots(GetMapWorldName(e->world), gLoadGameMenuWork->textSlots);

        if (a <= 1) {
            LoadObjPaletteBank(gLoadGameMenuWork->palette7->index, gUnk_09991C04);
        } else {
            LoadObjPaletteBank(gLoadGameMenuWork->palette7->index, gUnk_09991C44);
        }
    } else {
        LoadGameMenuLoadFloorTiles(a, 1, 13);
        gLoadGameMenuWork->textSlotCount = 0;
    }
}

void LoadGameMenuDeselectSlot(u8 a) {
    SaveFileSummary* e = &gGameState.fileSummaries[a];

    if (e->level != 0) {
        LoadGameMenuLoadFloorTiles(a, 0, e->floor);
    } else {
        LoadGameMenuLoadFloorTiles(a, 0, 13);
    }

    gLoadGameMenuWork->textSlotCount = 0;
}

void LoadGameMenuDraw() {
    s32 t;
    s32 u;

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        DrawSprite(128, gLoadGameMenuWork->y >> 8, gUnk_09EF8D68[1], gLoadGameMenuWork->tiles2,
            gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(128, gLoadGameMenuWork->y2 >> 8, gUnk_09EF8D68[2], gLoadGameMenuWork->tiles2,
            gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(gLoadGameMenuWork->x >> 8, 0, gUnk_09EF8D68[0], gLoadGameMenuWork->tiles2,
            gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 80);
        break;
    case LANGUAGE_FRENCH:
        DrawSprite(128, gLoadGameMenuWork->y >> 8, gUnkEu_09F843D8[1], gLoadGameMenuWork->tiles2,
            gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(128, gLoadGameMenuWork->y2 >> 8, gUnkEu_09F843D8[2], gLoadGameMenuWork->tiles2,
            gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(gLoadGameMenuWork->x >> 8, 0, gUnkEu_09F843D8[0], gLoadGameMenuWork->tiles2,
            gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 80);
        break;
    case LANGUAGE_SPANISH:
        DrawSprite(128, gLoadGameMenuWork->y >> 8, gUnkEu_09F843E8[1], gLoadGameMenuWork->tiles2,
            gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(128, gLoadGameMenuWork->y2 >> 8, gUnkEu_09F843E8[2], gLoadGameMenuWork->tiles2,
            gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(gLoadGameMenuWork->x >> 8, 0, gUnkEu_09F843E8[0], gLoadGameMenuWork->tiles2,
            gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 80);
        break;
    case LANGUAGE_ITALIAN:
        DrawSprite(128, gLoadGameMenuWork->y >> 8, gUnkEu_09F843F8[1], gLoadGameMenuWork->tiles2,
            gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(128, gLoadGameMenuWork->y2 >> 8, gUnkEu_09F843F8[2], gLoadGameMenuWork->tiles2,
            gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(gLoadGameMenuWork->x >> 8, 0, gUnkEu_09F843F8[0], gLoadGameMenuWork->tiles2,
            gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 80);
        break;
    case LANGUAGE_GERMAN:
    default:
        DrawSprite(128, gLoadGameMenuWork->y >> 8, gUnkEu_09F84408[1], gLoadGameMenuWork->tiles2,
            gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(128, gLoadGameMenuWork->y2 >> 8, gUnkEu_09F84408[2], gLoadGameMenuWork->tiles2,
            gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
        DrawSprite(gLoadGameMenuWork->x >> 8, 0, gUnkEu_09F84408[0], gLoadGameMenuWork->tiles2,
            gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 80);
        break;
    }
#else
    DrawSprite(128, gLoadGameMenuWork->y >> 8, gUnk_09EF8D68[1], gLoadGameMenuWork->tiles2,
        gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
    DrawSprite(128, gLoadGameMenuWork->y2 >> 8, gUnk_09EF8D68[2], gLoadGameMenuWork->tiles2,
        gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 90);
    DrawSprite(gLoadGameMenuWork->x >> 8, 0, gUnk_09EF8D68[0], gLoadGameMenuWork->tiles2,
        gLoadGameMenuWork->palette2, NULL, SPRITE_PRIORITY(3), 80);
#endif

    if (gLoadGameMenuWork->selectedSlot <= 1) {
        DrawSprite(56, 112, gSor1ff00Frames[0], gLoadGameMenuWork->tiles3,
            gLoadGameMenuWork->palette3, NULL, SPRITE_PRIORITY(1), 80);
        DrawSprite(72, 96, gDonaFl00Frames[0], gLoadGameMenuWork->tiles4,
            gLoadGameMenuWork->palette4, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_HFLIP, 81);
        DrawSprite(40, 96, gGoofyFl00Frames[0], gLoadGameMenuWork->tiles5,
            gLoadGameMenuWork->palette5, NULL, SPRITE_PRIORITY(1), 81);
    } else {
        DrawSprite(56, 112, gRikuFf00Frames[0], gLoadGameMenuWork->tiles6, gLoadGameMenuWork->palette6, NULL,
            SPRITE_PRIORITY(1), 81);
    }

    if (gLoadGameMenuWork->showRikuSlots != 0) {
        t = 32;
    } else {
        t = 45;
    }

    u = t * gLoadGameMenuWork->selectedSlot;
    ApproachValueHalf(&gLoadGameMenuWork->y3, (gLoadGameMenuWork->slotBaseY + u) << 8);
    DrawSprite(76, gLoadGameMenuWork->y3 >> 8, AnimGetGfx(&gLoadGameMenuWork->anim),
        gLoadGameMenuWork->tiles, gLoadGameMenuWork->palette, NULL, SPRITE_PRIORITY(1), 70);
    DrawTextSlots(100, u + (gLoadGameMenuWork->slotBaseY + 22), gLoadGameMenuWork->textSlots,
        gLoadGameMenuWork->palette7, 50, gLoadGameMenuWork->textSlotCount);
}

void LoadGameMenuMoveCursor(LoadGameMenuWork* w) {
    u8 old = w->selectedSlot;

    if (GetKeysRepeat() & DPAD_UP) {
        w->selectedSlot = w->selectedSlot != 0 ? w->selectedSlot - 1 : w->lastSlot;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysRepeat() & DPAD_DOWN) {
        w->selectedSlot = w->selectedSlot < w->lastSlot ? w->selectedSlot + 1 : 0;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (old != w->selectedSlot) {
        LoadGameMenuDeselectSlot(old);
        LoadGameMenuSelectSlot(w->selectedSlot);

        switch (w->selectedSlot) {
        case 0:
            if (w->showRikuSlots != 0) {
                LoadBgMap(1, gUnk_09988F44, 0x800);
                SetBgScroll(1, 0, (u16)-1);
            } else {
                LoadBgMap(1, gUnk_09987F44, 0x800);
                SetBgScroll(1, 0, (u16)-3);
            }

            break;
        case 1:
            if (w->showRikuSlots != 0) {
                LoadBgMap(1, &gUnk_09985F44[0x3800], 0x800);
                SetBgScroll(1, 0, (u16)-1);
            } else {
                LoadBgMap(1, &gUnk_09985F44[0x2800], 0x800);
                SetBgScroll(1, 0, 0);
            }

            break;
        case 2:
            LoadBgMap(1, &gUnk_09985F44[0x4000], 0x800);
            SetBgScroll(1, 0, (u16)-1);
            break;
        case 3:
            LoadBgMap(1, &gUnk_09985F44[0x4800], 0x800);
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
        if ((u8)LoadGameMenuLoadFile(work->selectedSlot) != 0) {
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

    if (FadeIsActive() != 0) {
        return;
    }

    if (work->forSioBattle != 0) {
        if (work->loaded != 0) {
            ModeRequest(&gModeSioBattle, 1);
        } else {
            ModeRequest(&gModeSioBattle, 0);
        }
    } else if (work->loaded != 0) {
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

    gLoadGameMenuWork = EwramAlloc(sizeof(LoadGameMenuWork));
    gLoadGameMenuWork->forSioBattle = arg != 0;

    if (gLoadGameMenuWork->forSioBattle != 0) {
        gLoadGameMenuWork->showRikuSlots = 0;
    } else {
        gLoadGameMenuWork->showRikuSlots = (gGameState.flags >> 5) & 1;
    }

    gLoadGameMenuWork->loaded = 0;
    gLoadGameMenuWork->selectedSlot = 0;

    if (gLoadGameMenuWork->showRikuSlots != 0) {
        gLoadGameMenuWork->lastSlot = 3;
        gLoadGameMenuWork->slotBaseY = 17;
        gLoadGameMenuWork->y3 = gLoadGameMenuWork->slotBaseY << 8;
    } else {
        gLoadGameMenuWork->lastSlot = 1;
        gLoadGameMenuWork->slotBaseY = 43;
        gLoadGameMenuWork->y3 = gLoadGameMenuWork->slotBaseY << 8;
    }

    gLoadGameMenuWork->timer = 16;
    gLoadGameMenuWork->update = LoadGameMenuSlideInY;
    SetBgMode0();
    SetupBg(3, 0, 28, 0);
    SetupBg(2, 0, 29, 0);
    SetupBg(1, 0, 30, 0);
    SetupBg(0, 3, 31, 0);
#ifdef VERSION_EU
    LoadBgTiles(1, gUnk_09959A64, 0x8000);

    switch (gLanguage) {
    case LANGUAGE_FRENCH:
        RequestDma3Copy(gUnk_09961A64, (u8*)GetBgCharBase(1) + 0xC00, 0x800);
        break;
    case LANGUAGE_SPANISH:
        RequestDma3Copy((void*)gUnkEu_09953BF0, (u8*)GetBgCharBase(1) + 0xC00, 0x800);
        break;
    case LANGUAGE_ITALIAN:
        RequestDma3Copy((void*)gUnkEu_099543F0, (u8*)GetBgCharBase(1) + 0xC00, 0x800);
        break;
    case LANGUAGE_GERMAN:
        RequestDma3Copy((void*)gUnkEu_09954BF0, (u8*)GetBgCharBase(1) + 0xC00, 0x800);
        break;
    }

    LoadBgPalette(3, gUnk_099919C4, 0x200);
    LoadBgMap(3, gUnk_09986F44, 0x800);
    LoadBgPalette(2, gUnk_099919C4, 0x200);
    LoadBgMap(2, gUnk_09987744, 0x800);
    LoadBgPalette(1, gUnk_099919C4, 0x200);
#else
    LoadBgTiles(3, gUnk_09959A64, 0x8000);
    LoadBgPalette(3, gUnk_099919C4, 0x200);
    LoadBgMap(3, gUnk_09986F44, 0x800);
    LoadBgTiles(2, gUnk_09959A64, 0x8000);
    LoadBgPalette(2, gUnk_099919C4, 0x200);
    LoadBgMap(2, gUnk_09987744, 0x800);
    LoadBgTiles(1, gUnk_09959A64, 0x8000);
    LoadBgPalette(1, gUnk_099919C4, 0x200);
#endif

    if (gLoadGameMenuWork->showRikuSlots != 0) {
        LoadBgMap(1, gUnk_09988F44, 0x800);
        SetBgScroll(1, 0, 0xFFFF);
    } else {
        LoadBgMap(1, gUnk_09987F44, 0x800);
        SetBgScroll(1, 0, 0xFFFD);
    }

    gLoadGameMenuWork->palette2 = LoadObjPalette(gUnk_09991BC4, 32);

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        gLoadGameMenuWork->tiles2 = LoadObjTiles(gUnk_098A87AA, 0x2C0);
        break;
    case LANGUAGE_FRENCH:
        gLoadGameMenuWork->tiles2 = LoadObjTiles(gUnkEu_0988519C, 0x300);
        break;
    case LANGUAGE_SPANISH:
        gLoadGameMenuWork->tiles2 = LoadObjTiles(gUnkEu_0988551E, 0x2C0);
        break;
    case LANGUAGE_ITALIAN:
        gLoadGameMenuWork->tiles2 = LoadObjTiles(gUnkEu_09885862, 0x2C0);
        break;
    case LANGUAGE_GERMAN:
    default:
        gLoadGameMenuWork->tiles2 = LoadObjTiles(gUnkEu_09885BA6, 0x2C0);
        break;
    }
#else
    gLoadGameMenuWork->tiles2 = LoadObjTiles(gUnk_098A87AA, 0x2C0);
#endif
    gLoadGameMenuWork->y = -0x800;
    gLoadGameMenuWork->y2 = 0xA000;
    gLoadGameMenuWork->x = -0x8000;
    gLoadGameMenuWork->tiles3 = AllocObjTiles(0x340, gSor1ff00Tiles);
    gLoadGameMenuWork->palette3 = LoadObjPalette(gSoraPalette, 32);
    gLoadGameMenuWork->tiles4 = AllocObjTiles(0x280, gDonaFl00Tiles);
    gLoadGameMenuWork->palette4 = LoadObjPalette(gDonaldPalette, 32);
    gLoadGameMenuWork->tiles5 = AllocObjTiles(0x400, gGoofyFl00Tiles);
    gLoadGameMenuWork->palette5 = LoadObjPalette(gGoofyPalette, 32);
    gLoadGameMenuWork->tiles6 = AllocObjTiles(0x400, gRikuFf00Tiles);
    gLoadGameMenuWork->palette6 = LoadObjPalette(gRikuPalette, 32);
    gLoadGameMenuWork->palette = LoadObjPalette(gUnk_09991BE4, 32);
    gLoadGameMenuWork->tiles = AllocObjTiles(0x120, gUnk_098A8AE2);
    AnimInit(&gLoadGameMenuWork->anim, gUnk_09EF8D88, gUnk_09EF8D78);
    AnimStart(&gLoadGameMenuWork->anim, 0, ANIM_FLAG_LOOP);
    gLoadGameMenuWork->palette7 = LoadObjPalette(gUnk_09991C04, 32);
    gLoadGameMenuWork->textSlotCount = 0;
    InitTextSlots(gLoadGameMenuWork->textSlots, 36);

    for (i = 0; i < 4; i++) {
        LoadGameMenuShowSummary(i);
    }

    LoadGameMenuSelectSlot(gLoadGameMenuWork->selectedSlot);
    FadeStartIn(FADE_MODE_BLACK, 16);
}

void Mode_MenuLoad_1() {
    if (gLoadGameMenuWork->update != NULL) {
        gLoadGameMenuWork->update(gLoadGameMenuWork);
    }

    LoadGameMenuDraw();
}

void Mode_MenuLoad_2() {
    ReleaseObjPalette(gLoadGameMenuWork->palette2);
    ReleaseObjTiles(gLoadGameMenuWork->tiles2);
    ReleaseObjPalette(gLoadGameMenuWork->palette);
    ReleaseObjTiles(gLoadGameMenuWork->tiles);
    ReleaseObjPalette(gLoadGameMenuWork->palette3);
    ReleaseObjTiles(gLoadGameMenuWork->tiles3);
    ReleaseObjPalette(gLoadGameMenuWork->palette4);
    ReleaseObjTiles(gLoadGameMenuWork->tiles4);
    ReleaseObjPalette(gLoadGameMenuWork->palette5);
    ReleaseObjTiles(gLoadGameMenuWork->tiles5);
    ReleaseObjPalette(gLoadGameMenuWork->palette6);
    ReleaseObjTiles(gLoadGameMenuWork->tiles6);
    ReleaseObjPalette(gLoadGameMenuWork->palette7);
    FreeTextSlots(gLoadGameMenuWork->textSlots, 36);
    EwramFree(gLoadGameMenuWork);
}

void MenuMsgWaitMessage(MenuMsgWork* w) {
    if (IsMessageWindowOpen() == 0) {
        if (w->toTitle == 0) {
            BackdropFadeStartOut(1, 16);
            FadeStartOut(FADE_MODE_WHITE, 16);
        } else {
            BackdropFadeStartOut(0, 16);
            FadeStartOut(FADE_MODE_BLACK, 16);
        }

        w->update = MenuMsgWaitFade;
    }
}

void MenuMsgWaitFade(MenuMsgWork* w) {
    if (FadeIsActive() == 0) {
        if (w->toTitle == 0) {
            ModeRequest(&gModeCopyright1, 0);
        } else {
            ModeRequest(&gModeTitle, 0);
        }
    }
}

void Mode_MenuMsg_0(s32 arg) {
    gMenuMsgWork = EwramAlloc(sizeof(MenuMsgWork));
    gMenuMsgWork->toTitle = arg;
    SetBgMode0();
    TaskPoolInit(&gMenuMsgWork->tasks, 1);

    if (gMenuMsgWork->toTitle == 0) {
        CreateSysmsgwinTask(&gMenuMsgWork->tasks, 0xB0);
        BackdropFadeReset();
        BackdropFadeSetColor(0, 0, 0);
        BackdropFadeStartIn(1, 16);
        FadeStartIn(FADE_MODE_WHITE, 16);
        FadeLock();
    } else {
#ifdef VERSION_EU
        CreateSysmsgwinTask(&gMenuMsgWork->tasks, 0xB2);
#else
        CreateSysmsgwinTask(&gMenuMsgWork->tasks, 0xB3);
#endif
        BackdropFadeReset();
        BackdropFadeSetColor(0, 0, 0);
        BackdropFadeStartIn(0, 1);
        FadeStartIn(FADE_MODE_BLACK, 1);
        FadeLock();
    }

    gMenuMsgWork->update = MenuMsgWaitMessage;
}

void Mode_MenuMsg_1() {
    gMenuMsgWork->update(gMenuMsgWork);
    TaskPoolUpdate(&gMenuMsgWork->tasks);
    TaskPoolDraw(&gMenuMsgWork->tasks);
    BackdropFadeUpdate();
}

void Mode_MenuMsg_2() {
    TaskPoolDestroy(&gMenuMsgWork->tasks);
    EwramFree(gMenuMsgWork);
}

void Task_MapRnd_0(MapRndWork* w) {
    MapRoomDef* r = gMapRoomDefs[gMapFloorState.world];
    s32 i;

    TaskPoolInit(&w->tasks, 4);
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
                TaskCreate(&w->tasks, &gTaskDescMapDoor, e);
            }
        }
    }
}

s32 Task_MapRnd_1(MapRndWork* w) {
    MapUpdateCamera(gFieldState->x2, gFieldState->y2);
    TaskPoolUpdate(&w->tasks);
    return 1;
}

void Task_MapRnd_2(MapRndWork* w) {
    TaskPoolDraw(&w->tasks);
}

void Task_MapRnd_3(MapRndWork* w) {
    TaskPoolDestroy(&w->tasks);
    MapFreeRoom();
}

void MapFixInitColliders(MapFixWork* p, MapFixedCollider* q) {
    s32 i;

    p->colliderCount = 0;

    if (q != NULL) {
        i = 0;

        do {
            if (q->radius != 0) {
                ColliderInit(&p->colliders[i], 6, q->radius, 0xA0);
                ColliderSetPosition(&p->colliders[i], q->x, q->y, 0);
                p->colliderCount++;
            } else {
                break;
            }

            q++;
            i++;
        } while (i < 5);
    }
}

void Task_MapFix_0(MapFixWork* w, MapFixedDef* p) {
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
    w->bg1MapLoaded = 0;
    w->bg2MapLoaded = 0;
    w->bg3MapLoaded = 0;

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
    w->bg3MapLoaded = 1;
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
        w->bg2MapLoaded = 1;
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
        w->bg1MapLoaded = 1;
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
    TaskPoolInit(&w->tasks, 2);
    v.fieldPosition.x = p->stairX;
    v.fieldPosition.y = p->stairY;
    v.angle = 45;
    TaskCreate(&w->tasks, &gTaskDescMapStair, &v);

    if (p->stair2X != 0 || p->stair2Y != 0) {
        v.fieldPosition.x = p->stair2X;
        v.fieldPosition.y = p->stair2Y;
        v.angle = 173;
        TaskCreate(&w->tasks, &gTaskDescMapStair, &v);
    }

    MapFixInitColliders(w, p->colliders);
}

s32 Task_MapFix_1(MapFixWork* w) {
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

    TaskPoolUpdate(&w->tasks);
    return 1;
}

void Task_MapFix_2(MapFixWork* w) {
    ScrollBgMapTo(3, gFieldState->x >> 8, gFieldState->y >> 8);
    ScrollBgMapTo(2, gFieldState->x >> 8, gFieldState->y >> 8);

    if ((gMapRoomState->flags & ROOM_FLAG_BG1_FROZEN) == 0) {
        ScrollBgMapTo(1, gFieldState->x >> 8, gFieldState->y >> 8);
    }

    TaskPoolDraw(&w->tasks);
}

void Task_MapFix_3(MapFixWork* w) {
    s32 i;

    for (i = 0; i < w->colliderCount; i++) {
        ColliderUnregister(&w->colliders[i]);
    }

#ifdef VERSION_EU
    if (w->bg3MapLoaded != 0) {
        FreeBgDecompressedMap(3);
    }

    if (w->bg2MapLoaded != 0) {
        FreeBgDecompressedMap(2);
    }

    if (w->bg1MapLoaded != 0) {
        FreeBgDecompressedMap(1);
    }
#endif

    TaskPoolDestroy(&w->tasks);
    MapFixFreeCells();
}

void MapDoorShowOpen(MapDoorWork* p) {
    UpdateSpriteFrameTiles(p->tiles, p->sprite, p->openSrc);
    UpdateSpriteFrameTiles(p->tiles2, p->sprite2, p->openSrc2);
}

void MapDoorShowClosed(MapDoorWork* p) {
    UpdateSpriteFrameTiles(p->tiles, p->sprite, p->closedSrc);
    UpdateSpriteFrameTiles(p->tiles2, p->sprite2, p->closedSrc2);
}

u8 MapDoorWaitHit(MapDoorWork* p) {
    MapDoor* flags = p->door;
    FldObj* e = &p->obj;

    if (!(gFieldState->flags & FIELD_FLAG_MENU_OPEN) && !(gMapRoomState->flags & (ROOM_FLAG_ENEMY_STRUCK | ROOM_FLAG_TUTORIAL_ACTIVE)) &&
        (u8)(flags->room + 3) > 1 && (flags->flags & (DOOR_FLAG_OPEN | DOOR_FLAG_EVENT)) != (DOOR_FLAG_OPEN | DOOR_FLAG_EVENT) &&
        IsHitByMapAttack(&e->fieldPosition, 0, 8) != 0 && !(gFieldState->flags & FIELD_FLAG_PLAYER_JUMPING) &&
        gFieldState->actor.fieldPosition.z == gFieldState->actor.fieldPosition.ground) {
        TaskPool* pool;

        m4aSongNumStart(SONG_SND_220);
        pool = &p->tasks;
        TaskCreate(pool, &gTaskDescMapSpark, e);
        gMapRoomState->flags |= ROOM_FLAG_ATTACK_HIT;
        gFieldState->lockonTarget = e;
        gMapRoomState->door = e;
        p->triggered = 1;
        p->update = MapDoorWaitCard;
        gMapRoomState->doorRoom = flags->room;
        gMapRoomState->doorSide = flags->side;
        FadeSetPaletteExcluded(p->palette->index + 16, 1);
        FadeSetPaletteExcluded(p->palette2->index + 16, 1);
        TaskCreate(pool, &gTaskDescRoomcreate, NULL);
    }

    return 1;
}

u8 MapDoorWaitCard(MapDoorWork* p) {
    MapDoor* flags = p->door;
    void* t = GetSelectedMapCard();

    if (t != NULL) {
        if (flags->flags & DOOR_FLAG_EVENT) {
            CreateMapRoom(flags->room, NULL);
        } else {
            CreateMapRoom(flags->room, t);
        }

        p->update = MapDoorWaitOpen;
    }

    if (!(gFieldState->flags & FIELD_FLAG_ROOM_CREATE)) {
        gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
        FadeSetPaletteExcluded(p->palette->index + 16, 0);
        FadeSetPaletteExcluded(p->palette2->index + 16, 0);
        p->update = MapDoorWaitHit;
    }

    return 1;
}

u8 MapDoorWaitOpen(MapDoorWork* p) {
    MapDoor* flags = p->door;
    u16 v;

    if (gFieldState->flags & FIELD_FLAG_DOOR_OPENED) {
        MapDoorShowOpen(p);
        v = flags->flags | DOOR_FLAG_OPEN;
        flags->flags = v;
        p->update = MapDoorIdle;
    }

    return 1;
}

u8 MapDoorIdle(MapDoorWork* p) {
    return 1;
}

void Task_MapDoor_0(MapDoorWork* w, MapDoor* p) {
    FldObj* e = &w->obj;
    FldPos* v = &e->fieldPosition;
    const MapDoorGfx* q = &gWorldMapDoorGfx[gMapFloorState.world];

    w->door = p;
    w->triggered = 0;
    w->visible = 1;

    switch (p->side) {
    case 0:
        w->sprite = gMapUiSpriteUs_098A94A0;
        w->openSrc = q->side0Open;
        w->closedSrc = q->side0Closed;
        e->angle = 173;
        w->obj.fieldPosition.x = (p->cellX << 5) + 16;
        e->fieldPosition.y = (p->cellY << 4) + 10;
        break;
    case 1:
        w->sprite = gMapUiSpriteUs_098A94B4;
        w->openSrc = q->side1Open;
        w->closedSrc = q->side1Closed;
        e->angle = 45;
        w->obj.fieldPosition.x = (p->cellX << 5) + 16;
        e->fieldPosition.y = (p->cellY << 4) + 6;
        break;
    case 2:
        w->sprite = gMapUiSpriteUs_098A94C8;
        w->openSrc = q->side2Open;
        w->closedSrc = q->side2Closed;
        e->angle = 211;
        w->obj.fieldPosition.x = (p->cellX << 5) + 16;
        e->fieldPosition.y = (p->cellY << 4) + 6;
        break;
    case 3:
        w->sprite = gMapUiSpriteUs_098A948C;
        w->openSrc = q->side3Open;
        w->closedSrc = q->side3Closed;
        e->angle = 83;
        w->obj.fieldPosition.x = (p->cellX << 5) + 16;
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
    w->tiles = AllocSpriteFrameTiles(0x400);
    w->palette = LoadObjPalette(q->palette, 32);
    w->palette2 = LoadObjPalette(gUnk_09991284, 32);
    w->tiles2 = AllocSpriteFrameTiles(0x100);

    switch (p->side) {
    case 0:
    case 1:
        w->sprite2 = gMapUiSpriteUs_098A94DC;
        w->openSrc2 = gUnk_09953864;
        w->closedSrc2 = gUnk_09953864 + 0x200;
        break;
    case 2:
    case 3:
        w->sprite2 = gMapUiSpriteUs_098A94FC;
        w->openSrc2 = gUnk_09953764;
        w->closedSrc2 = gUnk_09953764 + 0x200;
        break;
    }

    if (p->flags & DOOR_FLAG_OPEN) {
        w->update = MapDoorWaitHit;
        MapDoorShowOpen(w);
    } else {
        w->update = MapDoorWaitHit;
        MapDoorShowClosed(w);
    }

    TaskPoolInit(&w->tasks, 2);
}

s32 Task_MapDoor_1(MapDoorWork* w) {
    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        if (w->triggered == 0) {
            w->visible = 0;
        }
    } else {
        w->triggered = 0;
        w->visible = 1;
    }

    if (w->update != NULL) {
        if (w->update(w) == 0) {
            return 0;
        }
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

void Task_MapDoor_2(MapDoorWork* p) {
    MapDoor* f = p->door;
    u16 sx;
    u16 sy;
    u16 v;
    u16 t;
    s32 k;

    if (p->visible == 1) {
        sx = (p->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
        k = p->obj.fieldPosition.y >> 8;
        sy = k + (p->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);

        switch (f->side) {
        case 0:
        case 3:
            v = -0xFE4 - (p->obj.fieldPosition.y >> 8) * 4;
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
        DrawSprite(sx, sy, NULL, p->tiles, p->palette, NULL, t, v);

        if (f->flags & DOOR_FLAG_EVENT) {
            switch (f->side) {
            case 0:
            case 2:
                DrawSprite(sx, sy, NULL, p->tiles2, p->palette2, NULL, t, v - 1);
                break;
            case 1:
            case 3:
                DrawSprite(sx, sy, NULL, p->tiles2, p->palette2, NULL, t, v - 1);
                break;
            }
        }

        TaskPoolDraw(&p->tasks);
    }
}

void Task_MapDoor_3(MapDoorWork* p) {
    ReleaseObjTiles(p->tiles);
    ReleaseObjPalette(p->palette);
    ReleaseObjTiles(p->tiles2);
    ReleaseObjPalette(p->palette2);
    TaskPoolDestroy(&p->tasks);
}

void MapMenuSetPanelPalettesExcluded(MapMenuWork* p, u8 a) {
    s32 i;

    FadeSetPaletteExcluded(p->palette3->index + 0x10, a);
    FadeSetPaletteExcluded(p->palette8->index + 0x10, a);
    FadeSetPaletteExcluded(p->palette4->index + 0x10, a);
    FadeSetPaletteExcluded(p->palette5->index + 0x10, a);
    FadeSetPaletteExcluded(p->palette->index + 0x10, a);

    for (i = 0; i < 3; i++) {
        if (p->palette9[i] != NULL) {
            FadeSetPaletteExcluded(p->palette9[i]->index + 0x10, a);
        }
    }
}

void MapMenuSetCharaPalettesExcluded(MapMenuWork* p, u8 a) {
    FadeSetPaletteExcluded(p->palette2->index + 0x10, a);
    FadeSetPaletteExcluded(p->palette6->index + 0x10, a);
    FadeSetPaletteExcluded(p->palette7->index + 0x10, a);
}

void MapMenuWriteDigits3(ObjTiles* p, u8 a, u16 v) {
    u16 d[3];
    u16* q;
    s32 i;

    d[0] = v / 100;
    d[1] = v / 10 - d[0] * 10;
    d[2] = v - d[0] * 100 - d[1] * 10;

    for (i = 0, q = d; i < 3; i++) {
        RequestDma3Copy((void*)&gUnk_099581A4[*q * 32], (void*)(OBJ_VRAM0 + (p->index + a + i) * 32), 0x20);
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
        RequestDma3Copy((void*)&gUnk_099581A4[*q * 32], (void*)(OBJ_VRAM0 + (p->index + a + i) * 32), 0x20);
        q++;
    }
}

void MapMenuInitConfirm(MapMenuWork* w) {
    TextSlot* p1;
    TextSlot* p2;
    TextSlot* p3;

    LoadBgTiles(0, gUnk_099597E4, 0x140);
    LoadBgMap(0, gUnk_09985F44, 0x800);
    LoadPalette(gCard00Palette, &gUnk_050001C0[0x20], 0x20);
    FadeSetPaletteExcluded(15, 1);
    SetBgScroll(0, 0, 0);
    w->confirmPalette = LoadTextPalette(1);
#ifdef VERSION_EU
    p1 = w->textSlots2;
    InitTextSlots(p1, 66);
    p2 = w->textSlots3;
    InitTextSlots(p2, 6);
    p3 = w->textSlots4;
    InitTextSlots(p3, 9);
    w->textSlotCount2 = LoadTextSlots(eu_0805E924(&gUnkEu_088927F4), p1);
    w->textSlotCount3 = LoadTextSlots(eu_0805E924(&gUnkEu_08890E1C), p2);
    w->textSlotCount4 = LoadTextSlots(eu_0805E924(&gUnkEu_08890E44), p3);
#else
    p1 = w->textSlots2;
    InitTextSlots(p1, 33);
    p2 = w->textSlots3;
    InitTextSlots(p2, 6);
    p3 = w->textSlots4;
    InitTextSlots(p3, 9);
    w->textSlotCount2 = LoadTextSlots(gUnk_0815A03A, p1);
    w->textSlotCount3 = LoadTextSlots(gUnk_08159E10, p2);
    w->textSlotCount4 = LoadTextSlots(gUnk_08159E18, p3);
#endif
}

void MapMenuFreeConfirm(MapMenuWork* w) {
    FadeSetPaletteExcluded(15, 0);
    DisableBg(0);
    ReleaseObjPalette(w->confirmPalette);
#ifdef VERSION_EU
    FreeTextSlots(w->textSlots2, 0x42);
    FreeTextSlots(w->textSlots3, 6);
    FreeTextSlots(w->textSlots4, 9);
#else
    FreeTextSlots(w->textSlots2, 0x21);
    FreeTextSlots(w->textSlots3, 6);
    FreeTextSlots(w->textSlots4, 9);
#endif
}

s32 MapMenuOpen(MapMenuWork* w) {
    w->palette2 = LoadObjPalette(gUnk_09991984, 32);
    w->tiles2 = LoadObjTiles(gUnk_09958124, 0x80);
    w->y = -0x800;
    w->y2 = 0xA000;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        w->tiles8 = AllocObjTiles(0x400, gRikuFf00Tiles);
    } else {
        w->tiles8 = AllocObjTiles(0x340, gSor1ff00Tiles);
    }

    w->tiles7 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    w->palette7 = LoadObjPalette(gUnk_08F69BE4, 32);
    w->playerStartX = gFieldState->actor.fieldPosition.x - gFieldState->x;
    w->playerStartY = gFieldState->actor.fieldPosition.y + gFieldState->actor.fieldPosition.z - gFieldState->y;
    w->x8 = w->playerStartX;
    w->y4 = w->playerStartY;
    w->cursor = gGameState.mapMenuCursor;
    w->confirmCursor = 0;
    w->cursorVisible = 0;
    w->panelsVisible = 0;
    w->steps = w->reopened != 0 ? 1 : 16;
    w->update = MapMenuSlideInY;
    MapMenuSetCharaPalettesExcluded(w, 1);

    if (w->reopened == 0) {
        FadeToAmount(FADE_MODE_BLACK, 16, 16);
    }

    return 1;
}

s32 MapMenuSlideInY(MapMenuWork* w) {
    if (w->steps != 0) {
        ApproachValue(&w->y, 0, w->steps);
        ApproachValue(&w->y2, 0x9800, w->steps);
        w->steps--;
    } else {
        s32 i;

        gMapRoomState->flags |= ROOM_FLAG_HIDE_PLAYER;
        gFieldState->flags |= FIELD_FLAG_HIDE_ENEMIES;

#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            w->tiles5 = LoadObjTiles(gUnk_09954B64, 0x1BC0);
            break;
        case LANGUAGE_FRENCH:
            w->tiles5 = LoadObjTiles(gUnk_09956724, 0x1BC0);
            break;
        case LANGUAGE_SPANISH:
            w->tiles5 = LoadObjTiles(gUnkEu_09938170, 0x1BC0);
            break;
        case LANGUAGE_ITALIAN:
            w->tiles5 = LoadObjTiles(gUnkEu_09939D30, 0x1BC0);
            break;
        case LANGUAGE_GERMAN:
        default:
            w->tiles5 = LoadObjTiles(gUnkEu_0993B8F0, 0x1BC0);
            break;
        }
#else
        w->tiles5 = LoadObjTiles(gUnk_09954B64, 0x1BC0);
#endif
        w->palette3 = LoadObjPalette(gUnk_09991924, 32);
        w->x3 = 0x11800;
        w->x4 = 0xF000;
        w->x5 = 0x10000;
        MapMenuWriteDigits3(w->tiles5, 0, gGameState.progression.level);
        MapMenuWriteDigits3(w->tiles5, 6, gGameState.progression.maxHp);
        MapMenuWriteDigits3(w->tiles5, 3, gGameState.hp);

        if (gGameState.flags & GAME_FLAG_RIKU) {
            MapMenuWriteDigits3(w->tiles5, 9, gGameState.progression.dp);
        } else {
            MapMenuWriteDigits5(w->tiles5, 9, gGameState.progression.mooglePoints);
        }

        w->palette4 = LoadObjPalette(gUnk_09991964, 32);
        w->palette5 = LoadObjPalette(gUnk_09991944, 32);

#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            if (gGameState.flags & GAME_FLAG_RIKU) {
                w->tiles6 = LoadObjTiles(gUnk_099582E4, 0x1500);
            } else {
                w->tiles6 = LoadObjTiles(gUnkEu_0993D4B0, 0x1500);
            }

            break;
        case LANGUAGE_FRENCH:
            if (gGameState.flags & GAME_FLAG_RIKU) {
                w->tiles6 = LoadObjTiles(gUnkEu_099452B0, 0x1500);
            } else {
                w->tiles6 = LoadObjTiles(gUnkEu_0993E9B0, 0x1500);
            }

            break;
        case LANGUAGE_SPANISH:
            if (gGameState.flags & GAME_FLAG_RIKU) {
                w->tiles6 = LoadObjTiles(gUnkEu_099467B0, 0x1500);
            } else {
                w->tiles6 = LoadObjTiles(gUnkEu_0993FEB0, 0x1500);
            }

            break;
        case LANGUAGE_ITALIAN:
            if (gGameState.flags & GAME_FLAG_RIKU) {
                w->tiles6 = LoadObjTiles(gUnkEu_09947CB0, 0x1500);
            } else {
                w->tiles6 = LoadObjTiles(gUnkEu_099413B0, 0x1500);
            }

            break;
        case LANGUAGE_GERMAN:
        default:
            if (gGameState.flags & GAME_FLAG_RIKU) {
                w->tiles6 = LoadObjTiles(gUnkEu_099491B0, 0x1500);
            } else {
                w->tiles6 = LoadObjTiles(gUnkEu_099428B0, 0x1500);
            }

            break;
        }
#else
        if (gGameState.flags & GAME_FLAG_RIKU) {
            w->tiles6 = LoadObjTiles(gUnk_099582E4, 0x1500);
        } else {
            w->tiles6 = LoadObjTiles(gUnk_09956724, 0x1500);
        }
#endif

        w->x6 = -0x7800;
        w->palette = LoadObjPalette(gUnk_099919A4, 32);
        w->tiles = AllocObjTiles(0x120, gUnk_098A8628);
        AnimInit(&w->anim, gUnk_09EF8D58, gUnk_09EF8D48);
        AnimStart(&w->anim, 2, ANIM_FLAG_LOOP);

        for (i = 0; i < 3; i++) {
            w->tiles9[i] = NULL;
            w->palette9[i] = NULL;
            w->gfx[i] = NULL;
        }

        LoadFriendCardSprites(w->tiles9, (void**)w->palette9, w->gfx);
        InitTextSlots(w->textSlots, 24);
        w->palette8 = LoadTextPalette(1);
        w->textSlotCount = LoadTextSlots(GetDeckName(GetActiveDeckIndex()), w->textSlots);

#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            w->tiles3 = LoadObjTiles(gUnk_09957F24, 0x200);
            break;
        case LANGUAGE_FRENCH:
            w->tiles3 = LoadObjTiles(gUnk_09957F24, 0x200);
            break;
        case LANGUAGE_SPANISH:
            w->tiles3 = LoadObjTiles(gUnkEu_0994A8B0, 0x200);
            break;
        case LANGUAGE_ITALIAN:
            w->tiles3 = LoadObjTiles(gUnk_09957F24, 0x200);
            break;
        case LANGUAGE_GERMAN:
        default:
            w->tiles3 = LoadObjTiles(gUnkEu_0994AAB0, 0x200);
            break;
        }

        w->x = -0x8000;
        w->tiles4 = LoadObjTiles(gUnk_09957C24, 0x300);
#else
        w->tiles3 = LoadObjTiles(gUnk_09957F24, 0x200);
        w->x = -0x8000;
        w->tiles4 = LoadObjTiles(gUnk_09957C24, 0x300);
#endif
        w->x2 = 0xF800;
        MapMenuSetPanelPalettesExcluded(w, 1);
        w->panelsVisible = 1;
        w->steps = w->reopened != 0 ? 1 : 16;
        w->update = MapMenuSlideInX;
    }

    return 1;
}

s32 MapMenuSlideInX(MapMenuWork* w) {
    if (w->steps != 0) {
        ApproachValue(&w->x, 0, w->steps);
        ApproachValue(&w->x6, 0x800, w->steps);
        ApproachValue(&w->x2, 0x7800, w->steps);
        ApproachValue(&w->x3, 0x9800, w->steps);
        ApproachValue(&w->x4, 0x7000, w->steps);
        ApproachValue(&w->x5, 0x8000, w->steps);
        ApproachValue(&w->x8, 0xAC00, w->steps);
        ApproachValue(&w->y4, 0x6000, w->steps);
        w->steps--;
    } else {
        w->cursorVisible = 1;
        w->y3 = (w->cursor * 19 + 16) << 8;

        if (w->reopened != 0) {
            w->reopened = 0;
            FadeToAmount(FADE_MODE_BLACK, 16, 1);
            w->update = MapMenuResume;
        } else {
            w->update = (gGameState.flags & GAME_FLAG_RIKU) ? MapMenuRikuInput : MapMenuSoraInput;
        }
    }

    return 1;
}

s32 MapMenuSoraInput(MapMenuWork* w) {
    if (GetKeysRepeat() & DPAD_UP) {
        w->cursor = w->cursor != 0 ? w->cursor - 1 : 6;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysRepeat() & DPAD_DOWN) {
        w->cursor = w->cursor <= 5 ? w->cursor + 1 : 0;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysPressed() & (B_BUTTON | START_BUTTON)) {
        w->cursorVisible = 0;
        w->steps = 16;
        w->update = MapMenuSlideOutX;
        m4aSongNumStart(SONG_SYS_CLOSE);
    } else if (GetKeysPressed() & A_BUTTON) {
        switch (w->cursor) {
        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
            RequestFieldResume();
            w->update = MapMenuOpenSubMode;
            m4aSongNumStart(SONG_SYS_KETTEI);
            break;
        case 1:
            if ((u8)(gMapFloorState.room + 4) > 2) {
                RequestFieldResume();
                w->update = MapMenuOpenSubMode;
                m4aSongNumStart(SONG_SYS_KETTEI);
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }

            break;
        case 6:
            m4aSongNumStart(SONG_SYS_KETTEI);
            MapMenuInitConfirm(w);
            w->confirmCursor = 2;
            w->x7 = 0x8800;
            w->update = MapMenuConfirmInput;
            break;
        }
    }

    return 1;
}

s32 MapMenuRikuInput(MapMenuWork* w) {
    if (GetKeysRepeat() & DPAD_UP) {
        w->cursor = w->cursor != 0 ? w->cursor - 1 : 6;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysRepeat() & DPAD_DOWN) {
        w->cursor = w->cursor <= 5 ? w->cursor + 1 : 0;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysPressed() & (B_BUTTON | START_BUTTON)) {
        w->cursorVisible = 0;
        w->steps = 16;
        w->update = MapMenuSlideOutX;
        m4aSongNumStart(SONG_SYS_CLOSE);
    } else if (GetKeysPressed() & A_BUTTON) {
        switch (w->cursor) {
        case 0:
        case 2:
        case 3:
        case 4:
            m4aSongNumStart(SONG_SYS_KETTEI);
            RequestFieldResume();
            w->update = MapMenuOpenSubMode;
            break;
        case 5:
            m4aSongNumStart(SONG_SYS_KETTEI);
            RequestFieldResume();
            w->update = MapMenuOpenSubMode;
            break;
        case 1:
            if ((u8)(gMapFloorState.room + 4) > 2) {
                m4aSongNumStart(SONG_SYS_KETTEI);
                RequestFieldResume();
                w->update = MapMenuOpenSubMode;
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }

            break;
        case 6:
            m4aSongNumStart(SONG_SYS_KETTEI);
            MapMenuInitConfirm(w);
            w->confirmCursor = 2;
            w->x7 = 0x8800;
            w->update = MapMenuConfirmInput;
            break;
        }
    }

    return 1;
}

s32 MapMenuOpenSubMode(MapMenuWork* w) {
    gGameState.mapMenuCursor = w->cursor;

    switch (w->cursor) {
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

s32 MapMenuSlideOutX(MapMenuWork* w) {
    if (w->steps != 0) {
        ApproachValue(&w->x, -0x8000, w->steps);
        ApproachValue(&w->x6, -0x7800, w->steps);
        ApproachValue(&w->x2, 0xF800, w->steps);
        ApproachValue(&w->x3, 0x11800, w->steps);
        ApproachValue(&w->x4, 0xF000, w->steps);
        ApproachValue(&w->x5, 0x10000, w->steps);
        ApproachValue(&w->x8, w->playerStartX, w->steps);
        ApproachValue(&w->y4, w->playerStartY, w->steps);
        w->steps--;
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_HIDE_PLAYER;
        gFieldState->flags &= ~FIELD_FLAG_HIDE_ENEMIES;
        MapMenuSetPanelPalettesExcluded(w, 0);
        FadeToOriginal(FADE_MODE_BLACK, 16);
        w->steps = 16;
        w->update = MapMenuSlideOutY;
    }

    return 1;
}

s32 MapMenuSlideOutY(MapMenuWork* w) {
    if (w->steps != 0) {
        ApproachValue(&w->y, -0x800, w->steps);
        ApproachValue(&w->y2, 0xA000, w->steps);
        w->steps--;
        return 1;
    }

    gGameState.mapMenuCursor = 0xFF;
    m4aMPlayVolumeControl(&gMPlayInfo_BGM, 0xFF, 0x100);
    return 0;
}

s32 MapMenuConfirmInput(MapMenuWork* w) {
    if (GetKeysPressed() & DPAD_LEFT) {
        if (w->confirmCursor != 1) {
            w->confirmCursor = 1;
            m4aSongNumStart(SONG_SYS_CLICK);
        }
    }

    if (GetKeysPressed() & DPAD_RIGHT) {
        if (w->confirmCursor != 2) {
            w->confirmCursor = 2;
            m4aSongNumStart(SONG_SYS_CLICK);
        }
    }

    if ((GetKeysPressed() & B_BUTTON) || ((GetKeysPressed() & A_BUTTON) && w->confirmCursor == 2)) {
        w->confirmCursor = 0;
        MapMenuFreeConfirm(w);
        w->y3 = (w->cursor * 19 + 16) << 8;
        w->update = (gGameState.flags & GAME_FLAG_RIKU) ? MapMenuRikuInput : MapMenuSoraInput;
        m4aSongNumStart(SONG_SYS_CLOSE);
    } else if (GetKeysPressed() & A_BUTTON) {
        SaveWriteSystem();
        w->update = MapMenuOpenSubMode;
        m4aSongNumStart(SONG_SYS_KETTEI);
    }

    return 1;
}

s32 MapMenuResume(MapMenuWork* w) {
    gDispCnt |= DISPCNT_OBJ_ON;
    w->update = (gGameState.flags & GAME_FLAG_RIKU) ? MapMenuRikuInput : MapMenuSoraInput;
    return 1;
}

void Task_MapMenu_0(MapMenuWork* w) {
    s8 v;

    gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
    gFieldState->flags |= FIELD_FLAG_FREEZE_ENEMIES;
    gFieldState->flags |= FIELD_FLAG_MENU_OPEN;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        w->palette6 = LoadObjPalette(gRikuPalette, 32);
    } else {
        w->palette6 = LoadObjPalette(gSoraPalette, 32);
    }

    FadeSetPaletteExcluded(w->palette6->index + 0x10, 1);
    v = gGameState.mapMenuCursor;

    if (v != -1) {
        w->reopened = 1;
    } else {
        gGameState.mapMenuCursor = 0;
        w->reopened = 0;
        m4aSongNumStart(SONG_SYS_CANSEL);
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, 0xFF, 0x80);
    }

    w->update = MapMenuOpen;
}

s32 Task_MapMenu_1(MapMenuWork* w) {
    if (w->reopened != 0) {
        FadeStartIn(FADE_MODE_BLACK, 16);
    }

    if (w->panelsVisible != 0) {
        AnimUpdate(&w->anim);
    }

    if (w->update != NULL && (u8)w->update(w) == 0) {
        return 0;
    }

    return 1;
}

void Task_MapMenu_2(MapMenuWork* w) {
    s32 i;
    s32 k;

#ifdef VERSION_EU
    DrawSprite(128, w->y >> 8, gUnkEu_09F84738[0], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
    DrawSprite(128, w->y2 >> 8, gUnkEu_09F84738[1], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
#else
    DrawSprite(128, w->y >> 8, gUnk_09EF8E74[0], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
    DrawSprite(128, w->y2 >> 8, gUnk_09EF8E74[1], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
#endif

    if (
#ifdef VERSION_EU
        w->confirmCursor == 0 &&
#endif
        (gMapRoomState->flags & ROOM_FLAG_HIDE_PLAYER)) {
        if (gGameState.flags & GAME_FLAG_RIKU) {
            DrawSprite(w->x8 >> 8, w->y4 >> 8, gRikuFf00Frames[0], w->tiles8, w->palette6,
                NULL, SPRITE_PRIORITY(1), 80);
        } else {
            DrawSprite(w->x8 >> 8, w->y4 >> 8, gSor1ff00Frames[0], w->tiles8,
                w->palette6, NULL, SPRITE_PRIORITY(1), 80);
        }

        DrawSprite(w->x8 >> 8, w->y4 >> 8, gUnk_09EE1380[0], w->tiles7, w->palette7, NULL,
            SPRITE_PRIORITY(1), 81);
    }

    if (w->panelsVisible != 0) {
#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_SPANISH:
            DrawSprite(w->x >> 8, 0, gUnkEu_09F84720[0], w->tiles3, w->palette2, NULL, SPRITE_PRIORITY(1), 80);
            break;
        case LANGUAGE_ENGLISH:
        case LANGUAGE_FRENCH:
        case LANGUAGE_ITALIAN:
            DrawSprite(w->x >> 8, 0, gUnkEu_09F84718[0], w->tiles3, w->palette2, NULL, SPRITE_PRIORITY(1), 80);
            break;
        case LANGUAGE_GERMAN:
        default:
            DrawSprite(w->x >> 8, 0, gUnkEu_09F84728[0], w->tiles3, w->palette2, NULL, SPRITE_PRIORITY(1), 80);
            break;
        }
#else
        DrawSprite(w->x >> 8, 0, gUnk_09EF8E6C[0], w->tiles3, w->palette2, NULL, SPRITE_PRIORITY(1), 80);
#endif
#ifdef VERSION_EU
        DrawSprite(w->x2 >> 8, 14, gUnkEu_09F84730[0], w->tiles4, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
#else
        DrawSprite(w->x2 >> 8, 14, gUnk_09EF8E64[0], w->tiles4, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
#endif

        if (gGameState.flags & GAME_FLAG_RIKU) {
#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F84560[0], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F84560[1], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(w->x4 >> 8, 103, gUnkEu_09F84560[2], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_FRENCH:
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F84574[0], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F84574[1], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(w->x4 >> 8, 103, gUnkEu_09F84574[2], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_SPANISH:
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F84588[0], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F84588[1], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(w->x4 >> 8, 103, gUnkEu_09F84588[2], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_ITALIAN:
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F8459C[0], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F8459C[1], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(w->x4 >> 8, 103, gUnkEu_09F8459C[2], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_GERMAN:
            default:
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F845B0[0], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F845B0[1], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(w->x4 >> 8, 103, gUnkEu_09F845B0[2], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            }
#else
            DrawSprite(w->x3 >> 8, 0, gUnk_09EF8E80[0], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 80);
            DrawSprite(w->x3 >> 8, 0, gUnk_09EF8E80[1], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 81);
            DrawSprite(w->x4 >> 8, 103, gUnk_09EF8E80[2], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                81);
#endif

            if (w->tiles9[0] != NULL) {
                DrawSprite((w->x4 >> 8) + 18, 124, w->gfx[0], w->tiles9[0],
                    w->palette9[0], NULL, SPRITE_PRIORITY(1), 80);
            }
        } else {
#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F844FC[0], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F844FC[1], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(w->x4 >> 8, 103, gUnkEu_09F844FC[2], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_FRENCH:
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F84510[0], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F84510[1], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(w->x4 >> 8, 103, gUnkEu_09F84510[2], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_SPANISH:
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F84524[0], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F84524[1], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(w->x4 >> 8, 103, gUnkEu_09F84524[2], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_ITALIAN:
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F84538[0], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F84538[1], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(w->x4 >> 8, 103, gUnkEu_09F84538[2], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_GERMAN:
            default:
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F8454C[0], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 80);
                DrawSprite(w->x3 >> 8, 0, gUnkEu_09F8454C[1], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 81);
                DrawSprite(w->x4 >> 8, 103, gUnkEu_09F8454C[2], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            }
#else
            DrawSprite(w->x3 >> 8, 0, gUnk_09EF8E0C[0], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 80);
            DrawSprite(w->x3 >> 8, 0, gUnk_09EF8E0C[1], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1), 81);
            DrawSprite(w->x4 >> 8, 103, gUnk_09EF8E0C[2], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                81);
#endif

            for (i = 0; i < 3; i++) {
                k = i * 20 + 14;

                if (w->tiles9[i] != NULL) {
                    DrawSprite((w->x4 >> 8) + k, 124, w->gfx[i], w->tiles9[i],
                        w->palette9[i], NULL, SPRITE_PRIORITY(1), 80);
                }
            }
        }

        if (!(gGameState.flags & GAME_FLAG_RIKU)) {
#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                DrawSprite(w->x5 >> 8, 144, gUnkEu_09F844FC[3], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_FRENCH:
                DrawSprite(w->x5 >> 8, 144, gUnkEu_09F84510[3], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_SPANISH:
                DrawSprite(w->x5 >> 8, 144, gUnkEu_09F84524[3], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_ITALIAN:
                DrawSprite(w->x5 >> 8, 144, gUnkEu_09F84538[3], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            case LANGUAGE_GERMAN:
            default:
                DrawSprite(w->x5 >> 8, 144, gUnkEu_09F8454C[3], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                    81);
                break;
            }
#else
            DrawSprite(w->x5 >> 8, 144, gUnk_09EF8E0C[3], w->tiles5, w->palette3, NULL, SPRITE_PRIORITY(1),
                81);
#endif
            DrawTextSlots((w->x5 >> 8) + 16, 145, w->textSlots, w->palette8, 50,
                w->textSlotCount);
        }

#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            if (w->cursorVisible != 0) {
                DrawSprite(w->x6 >> 8, 26, gUnkEu_09F845C4[w->cursor], w->tiles6, w->palette5, NULL,
                    SPRITE_PRIORITY(1), 81);
                DrawSprite(w->x6 >> 8, 26, gUnkEu_09F84678[w->cursor], w->tiles6, w->palette4, NULL,
                    SPRITE_PRIORITY(1), 81);
            } else {
                DrawSprite(w->x6 >> 8, 26, gUnkEu_09F845C4[7], w->tiles6, w->palette5, NULL, SPRITE_PRIORITY(1),
                    80);
            }

            break;
        case LANGUAGE_FRENCH:
            if (w->cursorVisible != 0) {
                DrawSprite(w->x6 >> 8, 26, gUnkEu_09F845E8[w->cursor], w->tiles6, w->palette5, NULL,
                    SPRITE_PRIORITY(1), 81);
                DrawSprite(w->x6 >> 8, 26, gUnkEu_09F84698[w->cursor], w->tiles6, w->palette4, NULL,
                    SPRITE_PRIORITY(1), 81);
            } else {
                DrawSprite(w->x6 >> 8, 26, gUnkEu_09F845E8[7], w->tiles6, w->palette5, NULL, SPRITE_PRIORITY(1),
                    80);
            }

            break;
        case LANGUAGE_SPANISH:
            if (w->cursorVisible != 0) {
                DrawSprite(w->x6 >> 8, 26, gUnkEu_09F8460C[w->cursor], w->tiles6, w->palette5, NULL,
                    SPRITE_PRIORITY(1), 81);
                DrawSprite(w->x6 >> 8, 26, gUnkEu_09F846B8[w->cursor], w->tiles6, w->palette4, NULL,
                    SPRITE_PRIORITY(1), 81);
            } else {
                DrawSprite(w->x6 >> 8, 26, gUnkEu_09F8460C[7], w->tiles6, w->palette5, NULL, SPRITE_PRIORITY(1),
                    80);
            }

            break;
        case LANGUAGE_ITALIAN:
            if (w->cursorVisible != 0) {
                DrawSprite(w->x6 >> 8, 26, gUnkEu_09F84630[w->cursor], w->tiles6, w->palette5, NULL,
                    SPRITE_PRIORITY(1), 81);
                DrawSprite(w->x6 >> 8, 26, gUnkEu_09F846D8[w->cursor], w->tiles6, w->palette4, NULL,
                    SPRITE_PRIORITY(1), 81);
            } else {
                DrawSprite(w->x6 >> 8, 26, gUnkEu_09F84630[7], w->tiles6, w->palette5, NULL, SPRITE_PRIORITY(1),
                    80);
            }

            break;
        case LANGUAGE_GERMAN:
        default:
            if (w->cursorVisible != 0) {
                DrawSprite(w->x6 >> 8, 26, gUnkEu_09F84654[w->cursor], w->tiles6, w->palette5, NULL,
                    SPRITE_PRIORITY(1), 81);
                DrawSprite(w->x6 >> 8, 26, gUnkEu_09F846F8[w->cursor], w->tiles6, w->palette4, NULL,
                    SPRITE_PRIORITY(1), 81);
            } else {
                DrawSprite(w->x6 >> 8, 26, gUnkEu_09F84654[7], w->tiles6, w->palette5, NULL, SPRITE_PRIORITY(1),
                    80);
            }

            break;
        }
#else
        if (w->cursorVisible != 0) {
            DrawSprite(w->x6 >> 8, 26, gUnk_09EF8E20[w->cursor], w->tiles6, w->palette5, NULL,
                SPRITE_PRIORITY(1), 81);
            DrawSprite(w->x6 >> 8, 26, gUnk_09EF8E44[w->cursor], w->tiles6, w->palette4, NULL,
                SPRITE_PRIORITY(1), 81);
        } else {
            DrawSprite(w->x6 >> 8, 26, gUnk_09EF8E20[7], w->tiles6, w->palette5, NULL, SPRITE_PRIORITY(1),
                80);
        }
#endif

        if (w->cursorVisible != 0) {
            switch (w->confirmCursor) {
            case 1:
                ApproachValueHalf(&w->x7, 0x4800);
                DrawSprite(w->x7 >> 8, 80, AnimGetGfx(&w->anim), w->tiles, w->palette, NULL,
                    SPRITE_FLAG_HFLIP, 60);
                break;
            case 2:
                ApproachValueHalf(&w->x7, 0x8800);
                DrawSprite(w->x7 >> 8, 80, AnimGetGfx(&w->anim), w->tiles, w->palette, NULL,
                    SPRITE_FLAG_HFLIP, 60);
                break;
            case 0:
            default:
                ApproachValueHalf(&w->y3, (w->cursor * 19 + 16) << 8);
                DrawSprite(24, w->y3 >> 8, AnimGetGfx(&w->anim), w->tiles, w->palette, NULL,
                    SPRITE_PRIORITY(1) | SPRITE_FLAG_HFLIP, 60);
                break;
            }
        }

        if (w->confirmCursor != 0) {
            DrawTextSlots(
#ifdef VERSION_EU
                120 - (GetTextSlotsWidth(w->textSlots2, w->textSlotCount2) >> 1),
#else
                (240 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2,
#endif
                64, w->textSlots2,
                w->confirmPalette, 70, w->textSlotCount2);
            DrawTextSlots(80, 84, w->textSlots3, w->confirmPalette, 70, w->textSlotCount3);
            DrawTextSlots(144, 84, w->textSlots4, w->confirmPalette, 70, w->textSlotCount4);
        }
    }
}

void Task_MapMenu_3(MapMenuWork* w) {
    s32 i;

    MapMenuSetCharaPalettesExcluded(w, 0);
    MapMenuSetPanelPalettesExcluded(w, 0);
    ReleaseObjPalette(w->palette2);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjTiles(w->tiles3);
    ReleaseObjTiles(w->tiles4);
    ReleaseObjPalette(w->palette3);
    ReleaseObjTiles(w->tiles5);
    ReleaseObjPalette(w->palette4);
    ReleaseObjPalette(w->palette5);
    ReleaseObjTiles(w->tiles6);
    ReleaseObjPalette(w->palette);
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette6);
    ReleaseObjTiles(w->tiles8);
    ReleaseObjPalette(w->palette7);
    ReleaseObjTiles(w->tiles7);

    for (i = 0; i < 3; i++) {
        if (w->tiles9[i] != NULL) {
            ReleaseObjTiles(w->tiles9[i]);
            ReleaseObjPalette(w->palette9[i]);
        }
    }

    FreeTextSlots(w->textSlots, 24);
    ReleaseObjPalette(w->palette8);
    gMapRoomState->flags &= ~ROOM_FLAG_ATTACK_HIT;
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_ENEMIES;
    gFieldState->flags &= ~FIELD_FLAG_MENU_OPEN;
}

void MapSaveSetPanelPalettesExcluded(MapSaveWork* p, u8 a) {
    FadeSetPaletteExcluded(0x0B, a);
    FadeSetPaletteExcluded(0x0C, a);
    FadeSetPaletteExcluded(0x0D, a);
    FadeSetPaletteExcluded(0x0E, a);
    FadeSetPaletteExcluded(p->palette3->index + 0x10, a);
    FadeSetPaletteExcluded(p->palette->index + 0x10, a);
    FadeSetPaletteExcluded(p->palette4->index + 0x10, a);
    FadeSetPaletteExcluded(p->palette8->index + 0x10, a);
}

void MapSaveSetCharaPalettesExcluded(MapSaveWork* p, u8 a) {
    FadeSetPaletteExcluded(p->palette2->index + 0x10, a);
    FadeSetPaletteExcluded(p->palette5->index + 0x10, a);
    FadeSetPaletteExcluded(p->palette6->index + 0x10, a);
    FadeSetPaletteExcluded(p->palette7->index + 0x10, a);
}

void MapSaveLoadFloorTiles(u8 a) {
    const u8* src;

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        if (gGameState.flags & GAME_FLAG_RIKU) {
            src = gUnk_09963D64[a];
        } else {
            src = gUnkEu_09955250[a];
        }

        break;
    case LANGUAGE_FRENCH:
        if (gGameState.flags & GAME_FLAG_RIKU) {
            src = gUnkEu_0995BB50[a];
        } else {
            src = gUnkEu_09959850[a];
        }

        break;
    case LANGUAGE_SPANISH:
        if (gGameState.flags & GAME_FLAG_RIKU) {
            src = gUnkEu_09960150[a];
        } else {
            src = gUnkEu_0995DE50[a];
        }

        break;
    case LANGUAGE_ITALIAN:
        if (gGameState.flags & GAME_FLAG_RIKU) {
            src = gUnkEu_09964750[a];
        } else {
            src = gUnkEu_09962450[a];
        }

        break;
    case LANGUAGE_GERMAN:
    default:
        if (gGameState.flags & GAME_FLAG_RIKU) {
            src = gUnkEu_09968D50[a];
        } else {
            src = gUnkEu_09966A50[a];
        }

        break;
    }
#else
    if (gGameState.flags & GAME_FLAG_RIKU) {
        src = gUnk_09963D64[a];
    } else {
        src = gUnk_09961A64[a];
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
        RequestDma3Copy((void*)&gUnk_09966064[*q * 32], (u8*)GetBgCharBase(0) + off, 0x20);

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
        RequestDma3Copy((void*)&gUnk_09966064[*q * 32], (u8*)GetBgCharBase(0) + off, 0x20);
        off += 0x20;
        q++;
    }
}

void MapSaveShowSummary(MapSaveWork* w, u8 i) {
    SaveFileSummary* e = &gGameState.fileSummaries[i];

    if (e->level == 0) {
        w->textSlotCount = 0;
    } else {
        MapSaveLoadFloorTiles(e->floor);
        MapSaveLoadLevelTiles(e->level);
        MapSaveLoadTimeTiles(e->playTime);
        w->textSlotCount = LoadTextSlots(GetMapWorldName(e->world), w->textSlots);
    }
}

s32 MapSaveSlideInY(MapSaveWork* w) {
    if (w->steps != 0) {
        ApproachValue(&w->y, 0, w->steps);
        ApproachValue(&w->y2, 0x9800, w->steps);
        w->steps -= 1;
    } else {
        gMapRoomState->flags |= ROOM_FLAG_HIDE_PLAYER;
        gFieldState->flags |= FIELD_FLAG_HIDE_ENEMIES;
        w->steps = 16;
        w->update = MapSaveSlideInX;
    }

    return 1;
}

s32 MapSaveSlideInX(MapSaveWork* w) {
    TextSlot* p1;
    TextSlot* p2;
    TextSlot* p3;

    if (w->steps != 0) {
        ApproachValue(&w->x, 0, w->steps);

        if (gGameState.flags & GAME_FLAG_RIKU) {
            ApproachValue(&w->x3, 0x3800, w->steps);
            ApproachValue(&w->y3, 0x7000, w->steps);
        } else {
            ApproachValue(&w->x3, 0x3800, w->steps);
            ApproachValue(&w->y3, 0x7000, w->steps);
        }

        w->steps -= 1;
    } else {
        if (!(gGameState.flags & GAME_FLAG_RIKU)) {
            w->palette4 = LoadObjPalette(gUnk_09991C04, 32);
        } else {
            w->palette4 = LoadObjPalette(gUnk_09991C44, 32);
        }

        w->textSlotCount = 0;
        InitTextSlots(w->textSlots, 36);
        SetupBg(0, 3, 31, 11);
        SetBgPriority(0, 0);
        LoadBgPalette(0, gUnk_09991C84, 128);
        LoadBgTiles(0, gUnk_099661A4, 0x1FA0);

#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_FRENCH:
            RequestDma3Copy((void*)gUnkEu_0996D130, (u8*)GetBgCharBase(0) + 0x800, 0x800);
            break;
        case LANGUAGE_SPANISH:
            RequestDma3Copy((void*)gUnkEu_0996D930, (u8*)GetBgCharBase(0) + 0x800, 0x800);
            break;
        case LANGUAGE_ITALIAN:
            RequestDma3Copy((void*)gUnkEu_0996E130, (u8*)GetBgCharBase(0) + 0x800, 0x800);
            break;
        case LANGUAGE_GERMAN:
            RequestDma3Copy((void*)gUnkEu_0996E930, (u8*)GetBgCharBase(0) + 0x800, 0x800);
            break;
        }
#endif

        if (gGameState.flags & GAME_FLAG_RIKU) {
            if (gGameState.flags & GAME_FLAG_SECOND_FILE) {
                LoadBgMap(0, gUnk_0998C744, 0x800);

                if (SaveRepairFileSmall(1) == SAVE_OK) {
                    MapSaveShowSummary(w, 3);
                }
            } else {
                LoadBgMap(0, gUnk_0998BF44, 0x800);

                if (SaveRepairFileSmall(0) == SAVE_OK) {
                    MapSaveShowSummary(w, 2);
                }
            }
        } else {
            if (gGameState.flags & GAME_FLAG_SECOND_FILE) {
                LoadBgMap(0, gUnk_0998B744, 0x800);

                if (SaveRepairFileLarge(1) == SAVE_OK) {
                    MapSaveShowSummary(w, 1);
                }
            } else {
                LoadBgMap(0, gUnk_0998AF44, 0x800);

                if (SaveRepairFileLarge(0) == SAVE_OK) {
                    MapSaveShowSummary(w, 0);
                }
            }
        }

        SetBgScroll(0, 0, 0xFFFB);
        w->tiles5 = AllocObjTiles(0x280, gDonaFl00Tiles);
        w->tiles6 = AllocObjTiles(0x400, gGoofyFl00Tiles);
        w->palette3 = LoadObjPalette(gUnk_09991D24, 32);
        w->tiles3 = LoadObjTiles(gUnk_098A8F8A, 0x4C0);
        w->palette = LoadObjPalette(gUnk_099919A4, 32);
        w->tiles = AllocObjTiles(0x120, gUnk_098A8628);
        AnimInit(&w->anim, gUnk_09EF8D58, gUnk_09EF8D48);
        AnimStart(&w->anim, 2, ANIM_FLAG_LOOP);
        w->palette8 = LoadTextPalette(1);
        p1 = w->textSlots2;
#ifdef VERSION_EU
        InitTextSlots(p1, 54);
#else
        InitTextSlots(p1, 27);
#endif
        p2 = w->textSlots3;
        InitTextSlots(p2, 6);
        p3 = w->textSlots4;
        InitTextSlots(p3, 9);
#ifdef VERSION_EU
        w->textSlotCount2 = LoadTextSlots(eu_0805E924(&gUnkEu_08892864), p1);
        w->textSlotCount3 = LoadTextSlots(eu_0805E924(&gUnkEu_08890E1C), p2);
        w->textSlotCount4 = LoadTextSlots(eu_0805E924(&gUnkEu_08890E44), p3);
#else
        w->textSlotCount2 = LoadTextSlots(gUnk_08159DF0, p1);
        w->textSlotCount3 = LoadTextSlots(gUnk_08159E10, p2);
        w->textSlotCount4 = LoadTextSlots(gUnk_08159E18, p3);
#endif
        MapSaveSetPanelPalettesExcluded(w, 1);
        w->dialogVisible = 1;
        w->confirmCursor = 2;
        w->x2 = 0xB000;
        w->update = MapSaveInput;
    }

    return 1;
}

s32 MapSaveInput(MapSaveWork* w) {
    if (GetKeysRepeat() & DPAD_LEFT) {
        if (w->confirmCursor != 1) {
            w->confirmCursor = 1;
            m4aSongNumStart(SONG_SYS_CLICK);
        }
    }

    if (GetKeysRepeat() & DPAD_RIGHT) {
        if (w->confirmCursor != 2) {
            w->confirmCursor = 2;
            m4aSongNumStart(SONG_SYS_CLICK);
        }
    }

    if ((GetKeysPressed() & B_BUTTON) || ((GetKeysPressed() & A_BUTTON) && w->confirmCursor != 1)) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        w->confirmCursor = 0;
        w->dialogVisible = 0;
        w->steps = 16;
        w->update = MapSaveSlideOutX;
        DisableBg(0);
    } else if (GetKeysPressed() & A_BUTTON) {
        m4aSongNumStart(SONG_SYS_SAVELOAD);

        if (gGameState.flags & GAME_FLAG_RIKU) {
            if (gGameState.flags & GAME_FLAG_SECOND_FILE) {
                SaveWriteFileSmall(1);
                MapSaveShowSummary(w, 3);
            } else {
                SaveWriteFileSmall(0);
                MapSaveShowSummary(w, 2);
            }
        } else {
            if (gGameState.flags & GAME_FLAG_SECOND_FILE) {
                SaveWriteFileLarge(1);
                MapSaveShowSummary(w, 1);
            } else {
                SaveWriteFileLarge(0);
                MapSaveShowSummary(w, 0);
            }
        }

#ifdef VERSION_EU
        w->textSlotCount2 = LoadTextSlots(eu_0805E924(&gUnkEu_088928E4), w->textSlots2);
#else
        w->textSlotCount2 = LoadTextSlots(gUnk_0815B5A6, w->textSlots2);
#endif
        w->textSlotCount3 = 0;
        w->textSlotCount4 = 0;
        w->confirmCursor = 0;
        w->update = MapSaveWaitClose;
    }

    return 1;
}

s32 MapSaveWaitClose(MapSaveWork* w) {
    if (GetKeysPressed() & (A_BUTTON | B_BUTTON)) {
        w->dialogVisible = 0;
        DisableBg(0);
        w->steps = 16;
        w->update = MapSaveSlideOutX;
    }

    return 1;
}

s32 MapSaveSlideOutX(MapSaveWork* w) {
    if (w->steps != 0) {
        ApproachValue(&w->x, -0x8000, w->steps);
        ApproachValue(&w->x3, w->playerStartX, w->steps);
        ApproachValue(&w->y3, w->playerStartY, w->steps);
        w->steps--;
    } else {
        gMapRoomState->flags &= ~ROOM_FLAG_HIDE_PLAYER;
        gFieldState->flags &= ~FIELD_FLAG_HIDE_ENEMIES;
        MapSaveSetPanelPalettesExcluded(w, 0);
        FadeToOriginal(FADE_MODE_BLACK, 16);
        w->steps = 16;
        w->update = MapSaveSlideOutY;
    }

    return 1;
}

s32 MapSaveSlideOutY(MapSaveWork* w) {
    if (w->steps != 0) {
        ApproachValue(&w->y, -0x800, w->steps);
        ApproachValue(&w->y2, 0xA000, w->steps);
        w->steps--;
        return 1;
    }

    return 0;
}

void Task_MapSave_0(MapSaveWork* w) {
    gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
    gFieldState->flags |= FIELD_FLAG_FREEZE_ENEMIES;
    gMapRoomState->flags |= ROOM_FLAG_SAVE_MENU_OPEN;
    gGameState.hp = gGameState.progression.maxHp;

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        w->tiles2 = LoadObjTiles(gUnk_098A8C66, 0x2C0);
        break;
    case LANGUAGE_FRENCH:
        w->tiles2 = LoadObjTiles(gUnkEu_098863B2, 0x400);
        break;
    case LANGUAGE_SPANISH:
        w->tiles2 = LoadObjTiles(gUnkEu_0988683C, 0x3C0);
        break;
    case LANGUAGE_ITALIAN:
        w->tiles2 = LoadObjTiles(gUnkEu_09886C7E, 0x2C0);
        break;
    case LANGUAGE_GERMAN:
    default:
        w->tiles2 = LoadObjTiles(gUnkEu_09886FC8, 0x3C0);
        break;
    }

    w->palette2 = LoadObjPalette(gUnk_09991D04, 32);
#else
    w->palette2 = LoadObjPalette(gUnk_09991D04, 32);
    w->tiles2 = LoadObjTiles(gUnk_098A8C66, 0x2C0);
#endif
    w->y = -0x800;
    w->y2 = 0xA000;
    w->x = -0x8000;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        w->tiles4 = AllocObjTiles(0x400, gRikuFf00Tiles);
        w->palette5 = LoadObjPalette(gRikuPalette, 32);
    } else {
        w->tiles4 = AllocObjTiles(0x340, gSor1ff00Tiles);
        w->palette5 = LoadObjPalette(gSoraPalette, 32);
    }

    w->palette6 = LoadObjPalette(gDonaldPalette, 32);
    w->palette7 = LoadObjPalette(gGoofyPalette, 32);
    w->playerStartX = gFieldState->actor.fieldPosition.x - gFieldState->x;
    w->playerStartY = gFieldState->actor.fieldPosition.y + gFieldState->actor.fieldPosition.z - gFieldState->y;
    w->x3 = w->playerStartX;
    w->y3 = w->playerStartY;
    w->confirmCursor = 0;
    w->dialogVisible = 0;
    w->steps = 16;
    w->update = MapSaveSlideInY;
    TaskPoolInit(&w->tasks, 1);
    MapSaveSetCharaPalettesExcluded(w, 1);
    FadeToAmount(FADE_MODE_BLACK, 16, 16);
    m4aSongNumStart(SONG_SYS_CANSEL);
}

s32 Task_MapSave_1(MapSaveWork* w) {
    TaskPoolUpdate(&w->tasks);

    if (w->confirmCursor != 0) {
        AnimUpdate(&w->anim);
    }

    if (w->update != NULL) {
        if ((u8)w->update(w) == 0) {
            return 0;
        }
    }

    return 1;
}

void Task_MapSave_2(MapSaveWork* w) {
    TaskPoolDraw(&w->tasks);

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        DrawSprite(128, w->y >> 8, gUnkEu_09F8447C[1], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(128, w->y2 >> 8, gUnkEu_09F8447C[2], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(w->x >> 8, 0, gUnkEu_09F8447C[0], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 80);
        break;
    case LANGUAGE_FRENCH:
        DrawSprite(128, w->y >> 8, gUnk_09EF8D8C[1], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(128, w->y2 >> 8, gUnk_09EF8D8C[2], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(w->x >> 8, 0, gUnk_09EF8D8C[0], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 80);
        break;
    case LANGUAGE_SPANISH:
        DrawSprite(128, w->y >> 8, gUnkEu_09F8444C[1], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(128, w->y2 >> 8, gUnkEu_09F8444C[2], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(w->x >> 8, 0, gUnkEu_09F8444C[0], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 80);
        break;
    case LANGUAGE_ITALIAN:
        DrawSprite(128, w->y >> 8, gUnkEu_09F8445C[1], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(128, w->y2 >> 8, gUnkEu_09F8445C[2], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(w->x >> 8, 0, gUnkEu_09F8445C[0], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 80);
        break;
    case LANGUAGE_GERMAN:
    default:
        DrawSprite(128, w->y >> 8, gUnkEu_09F8446C[1], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(128, w->y2 >> 8, gUnkEu_09F8446C[2], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
        DrawSprite(w->x >> 8, 0, gUnkEu_09F8446C[0], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 80);
        break;
    }
#else
    DrawSprite(128, w->y >> 8, gUnk_09EF8D8C[1], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
    DrawSprite(128, w->y2 >> 8, gUnk_09EF8D8C[2], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 90);
    DrawSprite(w->x >> 8, 0, gUnk_09EF8D8C[0], w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(1), 80);
#endif

    if (gMapRoomState->flags & ROOM_FLAG_HIDE_PLAYER) {
        if (gGameState.flags & GAME_FLAG_RIKU) {
            DrawSprite(w->x3 >> 8, w->y3 >> 8, gRikuFf00Frames[0], w->tiles4, w->palette5,
                NULL, SPRITE_PRIORITY(1), 80);
        } else {
            DrawSprite(w->x3 >> 8, w->y3 >> 8, gSor1ff00Frames[0], w->tiles4,
                w->palette5, NULL, SPRITE_PRIORITY(1), 80);
        }
    }

    if (w->dialogVisible != 0) {
        if (!(gGameState.flags & GAME_FLAG_RIKU)) {
            DrawSprite(72, 96, gDonaFl00Frames[0], w->tiles5, w->palette6, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_HFLIP, 81);
            DrawSprite(40, 96, gGoofyFl00Frames[0], w->tiles6, w->palette7, NULL, SPRITE_PRIORITY(1), 81);
        }

        DrawSprite(0, 16, gMapUiSpriteUs_098A8F28, w->tiles3, w->palette3, NULL, SPRITE_PRIORITY(1), 90);
        DrawTextSlots(100, 59, w->textSlots, w->palette4, 50, w->textSlotCount);

        if (w->confirmCursor != 0) {
#ifdef VERSION_EU
            DrawTextSlots(166 - (GetTextSlotsWidth(w->textSlots2, w->textSlotCount2) >> 1), 92, w->textSlots2, w->palette8, 50, w->textSlotCount2);
#elif defined(VERSION_JP)
            DrawTextSlots(129, 92, w->textSlots2, w->palette8, 50, w->textSlotCount2);
#else
            DrawTextSlots(124, 92, w->textSlots2, w->palette8, 50, w->textSlotCount2);
#endif
            DrawTextSlots(128, 114, w->textSlots3, w->palette8, 50, w->textSlotCount3);
            DrawTextSlots(184, 114, w->textSlots4, w->palette8, 50, w->textSlotCount4);
        } else {
#ifdef VERSION_EU
            DrawTextSlots(166 - (GetTextSlotsWidth(w->textSlots2, w->textSlotCount2) >> 1), 102, w->textSlots2, w->palette8, 50, w->textSlotCount2);
#elif defined(VERSION_JP)
            DrawTextSlots(129, 103, w->textSlots2, w->palette8, 50, w->textSlotCount2);
#else
            DrawTextSlots(130, 102, w->textSlots2, w->palette8, 50, w->textSlotCount2);
#endif
        }

        switch (w->confirmCursor) {
        case 1:
            ApproachValueHalf(&w->x2, 0x7800);
            DrawSprite(w->x2 >> 8, 110, AnimGetGfx(&w->anim), w->tiles, w->palette, NULL, SPRITE_FLAG_HFLIP,
                40);
            break;
        case 2:
            ApproachValueHalf(&w->x2, 0xB000);
            DrawSprite(w->x2 >> 8, 110, AnimGetGfx(&w->anim), w->tiles, w->palette, NULL, SPRITE_FLAG_HFLIP,
                40);
            break;
        }
    }
}

void Task_MapSave_3(MapSaveWork* w) {
    u32 f;

    MapSaveSetCharaPalettesExcluded(w, 0);
    ReleaseObjPalette(w->palette2);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjPalette(w->palette3);
    ReleaseObjTiles(w->tiles3);
    ReleaseObjPalette(w->palette);
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette5);
    ReleaseObjTiles(w->tiles4);
    ReleaseObjPalette(w->palette6);
    ReleaseObjTiles(w->tiles5);
    ReleaseObjPalette(w->palette7);
    ReleaseObjTiles(w->tiles6);
    ReleaseObjPalette(w->palette4);
    FreeTextSlots(w->textSlots, 36);
    ReleaseObjPalette(w->palette8);
#ifdef VERSION_EU
    FreeTextSlots(w->textSlots2, 54);
#else
    FreeTextSlots(w->textSlots2, 27);
#endif
    FreeTextSlots(w->textSlots3, 6);
    FreeTextSlots(w->textSlots4, 9);
    f = gMapRoomState->flags & ~ROOM_FLAG_ATTACK_HIT;
    gMapRoomState->flags = f;
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_ENEMIES;
    gMapRoomState->flags = f & ~ROOM_FLAG_SAVE_MENU_OPEN;
    TaskPoolDestroy(&w->tasks);
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
                MapAnmSetupSlot(e, (const MapGmkDef*)list);
                e++;
                list++;
            } while (list->script != NULL);
        }
    }
}

s32 Task_MapAnm_1(MapAnmWork* w) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (w->slots[i].script != NULL) {
            MapAnmUpdateSlot(&w->slots[i]);
        }
    }

    return 1;
}

void Task_MapAnm_2(MapAnmWork* w) {
}

void Task_MapAnm_3(MapAnmWork* w) {
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
    { gUnk_09991224, gUnk_0994DF64, gUnk_0994E364, gUnk_0994D764, gUnk_0994DB64, gUnk_0994EF64, gUnk_0994F364, gUnk_0994E764, gUnk_0994EB64 },
    { gUnk_09991104, gUnk_0993BF64, gUnk_0993C364, gUnk_0993B764, gUnk_0993BB64, gUnk_0993CF64, gUnk_0993D364, gUnk_0993C764, gUnk_0993CB64 },
    { gUnk_09991124, gUnk_0993DF64, gUnk_0993E364, gUnk_0993D764, gUnk_0993DB64, gUnk_0993EF64, gUnk_0993F364, gUnk_0993E764, gUnk_0993EB64 },
    { gUnk_09991144, gUnk_0993FF64, gUnk_09940364, gUnk_0993F764, gUnk_0993FB64, gUnk_09940F64, gUnk_09941364, gUnk_09940764, gUnk_09940B64 },
    { gUnk_09991224, gUnk_0994DF64, gUnk_0994E364, gUnk_0994D764, gUnk_0994DB64, gUnk_0994EF64, gUnk_0994F364, gUnk_0994E764, gUnk_0994EB64 },
    { gUnk_099911C4, gUnk_09947F64, gUnk_09948364, gUnk_09947764, gUnk_09947B64, gUnk_09948F64, gUnk_09949364, gUnk_09948764, gUnk_09948B64 },
    { gUnk_09991184, gUnk_09943F64, gUnk_09944364, gUnk_09943764, gUnk_09943B64, gUnk_09944F64, gUnk_09945364, gUnk_09944764, gUnk_09944B64 },
    { gUnk_099911E4, gUnk_09949F64, gUnk_0994A364, gUnk_09949764, gUnk_09949B64, gUnk_0994AF64, gUnk_0994B364, gUnk_0994A764, gUnk_0994AB64 },
    { gUnk_099911A4, gUnk_09945F64, gUnk_09946364, gUnk_09945764, gUnk_09945B64, gUnk_09946F64, gUnk_09947364, gUnk_09946764, gUnk_09946B64 },
    { gUnk_09991164, gUnk_09941F64, gUnk_09942364, gUnk_09941764, gUnk_09941B64, gUnk_09942F64, gUnk_09943364, gUnk_09942764, gUnk_09942B64 },
    { gUnk_09991204, gUnk_0994BF64, gUnk_0994C364, gUnk_0994B764, gUnk_0994BB64, gUnk_0994CF64, gUnk_0994D364, gUnk_0994C764, gUnk_0994CB64 },
    { gUnk_09991264, gUnk_09951F64, gUnk_09952364, gUnk_09951764, gUnk_09951B64, gUnk_09952F64, gUnk_09953364, gUnk_09952764, gUnk_09952B64 },
    { gUnk_09991244, gUnk_0994FF64, gUnk_09950364, gUnk_0994F764, gUnk_0994FB64, gUnk_09950F64, gUnk_09951364, gUnk_09950764, gUnk_09950B64 },
    { gUnk_09991224, gUnk_0994DF64, gUnk_0994E364, gUnk_0994D764, gUnk_0994DB64, gUnk_0994EF64, gUnk_0994F364, gUnk_0994E764, gUnk_0994EB64 },
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
