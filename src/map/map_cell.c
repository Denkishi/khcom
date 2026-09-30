#include "macros.h"
#include "map.h"
#include "malloc.h"
#include "map_runtime.h"
#include "engine_math.h"
#include <stdlib.h>
#include "map_fixed_data.h"
#include "world_types.h"
#include "card_api.h"
#include "display.h"
#include "field_state.h"
#include "fld_types.h"
#include "game_state.h"
#include "listpool.h"
#include "m4a_catalog_data.h"
#include "m4a_song.h"
#include "map_api.h"
#include "map_room_data.h"
#include "map_room_types.h"
#include "map_types.h"
#include "mode.h"
#include "registration_data.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

MapRoomState* gMapRoomState EWRAM_COMMON(4);
MapFormDef gMapForm EWRAM_COMMON(8);
struct MapGmkPlacement* gMapGmkPlacements EWRAM_COMMON(4);

MapCell* gMapCells;
MapPlatform* gMapPlatforms;
MapDoor* gMapDoors;
u16 gMapCols;
u16 gMapRows;
u16 gMapTopRow;
u16 gMapBottomRow;
void* gMapBgBuffer;
MapRoomDef* gMapRoomDef;
MapCell* gMapFixCells;

#ifndef VERSION_EU
u8 gUnk_02034F3C[4];
#endif

s32 FieldGroundAt(s32 x, s32 y, s32 z) {
    MapCell* p = FieldCellAt(x, y);
    s32 r;

    if (p == NULL) {
        return 0;
    }

    if (p->upperZ < z) {
        if (p->type == 4 || p->type == 6) {
            if (MapCellMaskBitAt(p, x, y)) {
                r = p->upperZ;
            } else {
                r = p->lowerZ;
            }
        } else {
            r = p->upperZ;
        }
    } else {
        if (p->type == 3 || p->type == 5) {
            if (MapCellMaskBitAt(p, x, y)) {
                r = p->lowerZ;
            } else {
                r = p->upperZ;
            }
        } else {
            r = p->lowerZ;
        }
    }

    return r;
}

s32 GetFldPosGround(FldPos* p) {
    return FieldGroundAt(p->x, p->y + p->ground, p->ground);
}

s32 GetFldPosFloor(FldPos* p) {
    return FieldGroundAt(p->x, p->y + p->z, -0x100000);
}

void FldPosInitGround(FldPos* p) {
    p->ground = GetFldPosFloor(p);
}

void FldPosPlaceAtCell(FldPos* p, s16 x, s16 y, u8 a, u8 b) {
    p->x = (x << 13) + (a << 12);
    p->y = (y << 12) + (b << 11);
    p->z = 0;
    p->z = p->ground = GetFldPosFloor(p);
    p->y -= p->ground;
}

s32 GetLedgeAngleAt(s32 x, s32 y, s32 z) {
    switch (FieldCellAt(x, y + z)->type) {
    case 1:
    case 2:
    case 7:
        return 0;
    case 3:
    case 4:
    case 8:
        return 0xD3;
    case 5:
    case 6:
    case 9:
        return 0x2D;
    }

    return 0x80;
}

void FldPosPlaceOnFreeFloor(FldPos* p) {
    MapPickFreeFloorPos(p, &p->y);
    p->z = 0;
    p->z = p->ground = GetFldPosFloor(p);
    p->y -= p->ground;
}

s32 MapClampCameraX(s32 x) {
    s32 lim;

    x -= 0x7800;
    lim = (gFieldState->tileCols << 11) - 0xF000;

    if (x < 0) {
        x = 0;
    } else if (x > lim) {
        x = lim;
    }

    return x;
}

s32 MapClampCameraY(s32 y) {
    s32 lim;

    y -= 0x6000;
    lim = (gFieldState->tileRows << 11) - 0xA000;

    if (y < 0) {
        y = 0;
    } else if (y > lim) {
        y = lim;
    }

    return y;
}

void MapSnapCamera(void) {
    s16 sx;
    s16 sy;

    gFieldState->x = MapClampCameraX(gFieldState->x2);
    gFieldState->y = MapClampCameraY(gFieldState->y2);
    sx = gFieldState->x >> 8;
    sy = gFieldState->y >> 8;
    MapDrawBgs(sx / 8, sy / 8);
    SetBgScroll(3, (u16)sx, (u16)sy);
    SetBgScroll(2, (u16)sx, (u16)sy);
    SetBgScroll(1, (u16)sx, (u16)sy);
}

void MapUpdateCamera(s32 a, s32 b) {
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s16 sx;
    s16 sy;
    u8* p;

    if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) == 0) {
        x = MapClampCameraX(a);
        y = MapClampCameraY(b);
    } else {
        x = a - 0x7800;
        y = b - 0x6000;
    }

    dx = (x - gFieldState->x) >> 3;

    if (dx > 0x800) {
        dx = 0x800;
    } else if (dx < -0x800) {
        dx = -0x800;
    }

    dy = (y - gFieldState->y) >> 3;

    if (dy > 0x800) {
        dy = 0x800;
    } else if (dy < -0x800) {
        dy = -0x800;
    }

    if (abs(dx) <= 50) {
        dx = 0;
    }

    if (abs(dy) <= 50) {
        dy = 0;
    }

    gFieldState->x += dx;
    gFieldState->y += dy;
    sx = gFieldState->x / 0x800;
    sy = gFieldState->y / 0x800;
    p = GetMapBgBuffer();

    if (dx > 0) {
        MapDrawBgColumn(p, sx + 30, sy - 1);
    } else if (dx < 0) {
        MapDrawBgColumn(p, sx - 1, sy - 1);
    }

    p += 0xC0;

    if (dy > 0) {
        MapDrawBgRow(p, sx - 1, sy + 20);
    } else if (dy < 0) {
        MapDrawBgRow(p, sx - 1, sy - 1);
    }

    SetBgScroll(3, (u16)(gFieldState->x >> 8), (u16)(gFieldState->y >> 8));
    SetBgScroll(2, (u16)(gFieldState->x >> 8), (u16)(gFieldState->y >> 8));

    if (!(gMapRoomState->flags & ROOM_FLAG_BG1_FROZEN)) {
        SetBgScroll(1, (u16)(gFieldState->x >> 8), (u16)(gFieldState->y >> 8));
    }
}

void MapSetCameraTarget(s32 x, s32 y) {
    gFieldState->x2 = x;
    gFieldState->y2 = y;
}

void MapMoveCameraTarget(s32 dx, s32 dy) {
    gFieldState->x2 += dx;
    gFieldState->y2 += dy;
}

void SetMapAttackBox(s32 x, s32 y, s32 z) {
    gMapRoomState->attackActive = 1;
    gMapRoomState->attackX = x;
    gMapRoomState->attackY = y;
    gMapRoomState->attackZ = z;
}

u8 IsHitByMapAttack(FldPos* p, s16 a, s16 b) {
    if (gMapRoomState->attackActive == 0) {
        return 0;
    }

    if (gMapRoomState->flags & ROOM_FLAG_ATTACK_HIT) {
        return 0;
    }

    if (gMapRoomState->attackX - 0x1400 > p->x + (a << 8)) {
        return 0;
    }

    if (gMapRoomState->attackX + 0x1400 < p->x - (a << 8)) {
        return 0;
    }

    if (gMapRoomState->attackY - 0x1400 > p->y + (a << 8)) {
        return 0;
    }

    if (gMapRoomState->attackY + 0x1400 < p->y - (a << 8)) {
        return 0;
    }

    if (gMapRoomState->attackZ - 0x2000 > p->z) {
        return 0;
    }

    if (gMapRoomState->attackZ + 0x800 < p->z - (b << 8)) {
        return 0;
    }

    if (gMapRoomState->attackZ <= p->ground) {
        return 1;
    }

    return 0;
}

u8 GetCurrentRoomCardValue(void) {
    return GetMapRoomCardValue(gMapFloorState.room);
}

s32 IsMapInterrupted(void) {
    if ((gFieldState->flags & (FIELD_FLAG_MENU_OPEN | FIELD_FLAG_ROOM_CREATE)) || (gMapRoomState->flags & ROOM_FLAG_SAVE_MENU_OPEN)) {
        return 1;
    }

    return 0;
}

s32 IsFldObjTalkTarget(FldObj* obj) {
    if (IsMessageWindowOpen()) {
        return 0;
    }

    if (gFieldState->flags & (FIELD_FLAG_FREEZE_PLAYER | FIELD_FLAG_ROOM_CREATE | FIELD_FLAG_PLAYER_JUMPING)) {
        return 0;
    }

    if (gMapRoomState->flags & (ROOM_FLAG_ENEMY_STRUCK | ROOM_FLAG_ATTACK_HIT)) {
        return 0;
    }

    if (gFieldState->actor.fieldPosition.z != gFieldState->actor.fieldPosition.ground) {
        return 0;
    }

    return gFieldState->lockonTarget == obj;
}

void MapFreezeBg1(void) {
    gMapRoomState->flags |= ROOM_FLAG_BG1_FROZEN;
}

void MapRestoreBg1(void) {
    MapFixedDef* p;
    MapRoomDef* q;
    s16 x;
    s16 y;

    if ((s32)gMapRoomState->flags < 0) {
        p = gMapFixedDefs[4];
        LoadBgTiles(1, p->tiles2, p->tilesSize2);
        LoadBgPalette(1, p->palette, p->paletteSize);
        SetBgMapBlocks(1, p->map, p->mapWidth, p->mapHeight);
        gMapRoomState->flags &= ~ROOM_FLAG_BG1_FROZEN;
    } else {
        q = gMapRoomDefs[gMapFloorState.world];
        LoadBgTiles(1, q->tiles2, q->tilesSize2);
        LoadBgPalette(1, q->palette, q->paletteSize);
        x = gFieldState->x >> 8;
        y = gFieldState->y >> 8;
        MapDrawBg1(x / 8, y / 8);
        SetBgScroll(1, (u16)x, (u16)y);
        gMapRoomState->flags &= ~ROOM_FLAG_BG1_FROZEN;
    }
}

FldObj* GetMapRoomDoor(void) {
    return gMapRoomState->door;
}

void RequestMapMode(void) {
    switch (gMapFloorState.room) {
    case MAP_ROOM_TUTORIAL:
    case MAP_ROOM_EXIT_HALL:
    case MAP_ROOM_ENTRANCE_HALL:
        ModeRequest(&gModeMapFix, 0);
        break;
    default:
        if (gMapFloorState.world != WORLD_100_ACRE_WOOD) {
            ModeRequest(&gModeMapFld, 0);
        } else {
            ModeRequest(&gModePooh, 1);
        }

        break;
    }
}

void ReturnToMap(u8 a) {
    if (a != 1) {
        gGameState.mapMenuCursor = 0xFF;
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, 0xFF, 0x100);
    }

    RequestMapMode();
}

void InitFieldState(void) {
    gFieldState->x = 0;
    gFieldState->y = 0;
    gFieldState->x2 = 0;
    gFieldState->y2 = 0;
    gFieldState->tileCols = 32;
    gFieldState->tileRows = 32;
    gFieldState->lockonTarget = 0;
    gFieldState->lockonDelay = 60;
    gFieldState->flags = 0;
    gFieldState->unk_74 = 0;
    TaskPoolInit(&gFieldState->tasks, 50);
    TaskPoolInit(&gFieldState->tasks2, 1);
    ListPoolInit(&gFieldState->actor.pool);
    TaskPoolInit(&gFieldState->tasks3, 25);
    TaskPoolInit(&gFieldState->tasks5, 1);
    TaskPoolInit(&gFieldState->tasks4, 8);
    gMapRoomState->flags = 0;
    gMapRoomState->jumpGmkAngle = 0;
    gMapRoomState->jumpGmkHeight = 0;
    gMapRoomState->attackActive = 0;
    TaskPoolInit(&gMapRoomState->tasks, 1);
}

void CreateMapRndTask(void) {
    LoadMapRoomState(gMapRoomState, gMapFloorState.room);

    if (gMapRoomState->roomType == 5) {
        gFieldState->flags |= FIELD_FLAG_NO_ENEMY_SPAWN;
    }

    TaskCreate(&gFieldState->tasks, &gTaskDescMapRnd, 0);
}

void SpawnMapPlayer(void) {
    MapDoor* e;
    s32 x;
    s32 y;

    if (gMapFloorState.entrySide <= 3) {
        e = GetMapDoor(gMapFloorState.entrySide);
        x = (e->cellX << 5) + 16;
        y = (e->cellY << 4) + 10;

        switch (gMapFloorState.entrySide) {
        case 0:
            gFieldState->spawnX = (x << 8) - 0xC00;
            gFieldState->spawnY = (y << 8) + 0x800;
            gFieldState->spawnAngle = 0xAD;
            break;
        case 1:
            gFieldState->spawnX = (x << 8) + 0xC00;
            gFieldState->spawnY = (y << 8) - 0x800;
            gFieldState->spawnAngle = 0x2D;
            break;
        case 2:
            gFieldState->spawnX = (x << 8) - 0xC00;
            gFieldState->spawnY = (y << 8) - 0x800;
            gFieldState->spawnAngle = 0xD3;
            break;
        case 3:
            gFieldState->spawnX = (x << 8) + 0xC00;
            gFieldState->spawnY = (y << 8) + 0x800;
            gFieldState->spawnAngle = 0x53;
            break;
        }
    } else {
        MapPickFreeFloorPos((FldPos*)&gFieldState->spawnX, &gFieldState->spawnY);
        gFieldState->spawnAngle = 0x80;
    }

    if (gGameState.flags & GAME_FLAG_RIKU) {
        TaskCreate(&gFieldState->tasks2, &gTaskDescFldRiku, 0);
    } else {
        TaskCreate(&gFieldState->tasks2, &gTaskDescFldSora, 0);
    }
}

void UpdateMapField(void) {
    if (gFieldState->lockonDelay > 0) {
        gFieldState->flags |= FIELD_FLAG_NO_LOCKON;
        gFieldState->lockonDelay--;
    } else {
        gFieldState->flags &= ~FIELD_FLAG_NO_LOCKON;
    }

    gMapRoomState->jumpGmkHeight = 0;
    TaskPoolUpdate(&gFieldState->tasks);
    gMapRoomState->attackActive = 0;

    if ((gFieldState->flags & FIELD_FLAG_FREEZE_PLAYER) == 0 && (gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) == 0) {
        TaskPoolUpdate(&gFieldState->tasks2);
    }

    if ((gFieldState->flags & FIELD_FLAG_FREEZE_ENEMIES) == 0) {
        TaskPoolUpdate(&gFieldState->tasks4);
    }

    TaskPoolUpdate(&gFieldState->tasks3);
    TaskPoolUpdate(&gFieldState->tasks5);
}

void DrawMapField(void) {
    TaskPoolDraw(&gFieldState->tasks);

    if ((gMapRoomState->flags & ROOM_FLAG_HIDE_PLAYER) == 0) {
        TaskPoolDraw(&gFieldState->tasks2);
    }

    if ((gFieldState->flags & FIELD_FLAG_HIDE_ENEMIES) == 0) {
        TaskPoolDraw(&gFieldState->tasks4);
    }

    TaskPoolDraw(&gFieldState->tasks3);
    TaskPoolDraw(&gFieldState->tasks5);
}

void DestroyMapField(void) {
    TaskPoolDestroy(&gFieldState->tasks);
    TaskPoolDestroy(&gFieldState->tasks2);
    TaskPoolDestroy(&gFieldState->tasks3);
    TaskPoolDestroy(&gFieldState->tasks5);
    TaskPoolDestroy(&gFieldState->tasks4);
    TaskPoolDestroy(&gMapRoomState->tasks);
}

MapCell* MapGetCell(s16 x, s16 y) {
    if (y < 0 || y >= gMapRows) {
        return 0;
    }

    if (x < 0 || x >= gMapCols) {
        return 0;
    }

    return &gMapCells[gMapCols * y + x];
}

void MapCellSetType(MapCell* p, s32 a, s32 b) {
    if (p != NULL) {
        p->type = a;
        p->maskTable = GetCellMaskTable(a);
        p->upperZ = b;
    }
}

u8 FldPosHeightExceeds(FldPos* p, u16 a) {
    u16 d = (p->ground - p->z) >> 8;

    return d > a * 16;
}

u8 GetRandomPieceVariant(u8 a) {
    const u8* p = gUnk_0984D32C[a];
    return GetRandom() % p[3];
}

void MapCellSetBg3Piece(MapCell* p, s32 n) {
    if (p != NULL) {
        u16* base = gMapRoomDef->map3;
        const u8* q = gUnk_0984D314[n];
        u8 m = GetRandom() % q[3];
        s32 u = ((m & 7) + q[1]) * 4;
        s32 v = (m >> 3) + q[2];
        p->bg3Piece = n;
        p->bg3Map = base + (v * 64 + u);
    }
}

void MapCellSetBg2Piece(MapCell* p, u8 n, u8 v) {
    if (p != NULL) {
        const u8* q = gUnk_0984D32C[n];
        u16* base;
        u16 t;

        switch (q[0]) {
        case 1:
            base = gMapRoomDef->map2;
            break;
        case 0:
        default:
            base = gMapRoomDef->map3;
            break;
        }

        t = ((v & 7) + q[1]) * 4 + ((v >> 3) + q[2]) * 64;

        if (p->flags & MAP_CELL_FLAG_EDGE_LEFT) {
            t = t + q[3] * 4;
        }

        if (p->flags & MAP_CELL_FLAG_EDGE_RIGHT) {
            t = t + q[3] * 8;
        }

        p->bg2Piece = n;
        p->bg2Map = base + t;
    }
}

void MapCellSetFloorBg3Piece(MapCell* p) {
    if (p->flags & 1) {
        MapCellSetBg3Piece(p, 1);
    } else if (p->flags & 2) {
        MapCellSetBg3Piece(p, 2);
    } else {
        MapCellSetBg3Piece(p, 0);
    }
}

void func_080E0A70(MapCell* p, s32 n) {
    u16* base;
    const u8* t;
    u8 r;
    u16 off;
    u16 step;

    if (p == NULL) {
        return;
    }

    if ((p->flags & (MAP_CELL_FLAG_EDGE_LEFT | MAP_CELL_FLAG_EDGE_RIGHT)) == 0) {
        p->bg2Piece = n;
        return;
    }

    base = gMapRoomDef->map3;
    t = gUnk_0984D32C[n];
    r = GetRandom() % t[3];
    off = (r % 8 + t[1]) * 4 + (r / 8 + t[2]) * 64;

    if (p->flags & MAP_CELL_FLAG_EDGE_RIGHT) {
        step = t[3] * 4;
        off += step;

        if (p->flags & MAP_CELL_FLAG_EDGE_LEFT) {
            off += step;
        }
    }

    p->bg2Piece = n;
    p->bg2Map = base + off;
}

void sub_080E0B00(MapCell* p, s32 n) {
    const u8* t;
    u16* base;
    u16 off;

    if (p == NULL) {
        return;
    }

    t = gUnk_0984D32C[n];
    off = t[1] * 4 + t[2] * 64;
    base = gMapRoomDef->map2;

    switch (n) {
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
        if (p->flags & MAP_CELL_FLAG_EDGE_RIGHT) {
            off += t[3] * 4;
        }

        break;
    case 23:
    case 24:
    case 25:
    case 32:
    case 33:
    case 34:
        if (p->flags & MAP_CELL_FLAG_EDGE_LEFT) {
            off += t[3] * 4;
        }

        break;
    }

    p->bg2Piece = n;
    p->bg2Map = base + off;
}

void MapCellSetBg2PieceVariant(MapCell* p, s32 n, u8 v) {
    if (p != NULL) {
        u16* base = gMapRoomDef->map2;
        const u8* q = gUnk_0984D32C[n];
        s32 t;

        if (v == 0xFF) {
            v = GetRandom() % q[3];
        }

        t = ((v & 7) + q[1]) * 4 + ((v >> 3) + q[2]) * 64;
        p->bg2Piece = n;
        p->bg2Map = base + t;
    }
}

void func_080E0BF4(s16 x, s16 y, s32 a, s32 b) {
    MapCell* p = MapGetCell(x, y);

    MapCellSetBg3Piece(p, a);
    sub_080E0B00(p, b);
}

void MapBuildStairs(u16 x, u16 y) {
    MapCell* e;
    u8 v;
    s32 go;

    go = 1;

    while (go) {
        e = MapGetCell((s16)x, (s16)y);

        switch (e->type) {
        case 3:
            MapGetCell((s16)x, (s16)(y - 1))->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell((s16)(x - 1), (s16)y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell((s16)(x - 1), (s16)(y - 1))->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            v = GetRandomPieceVariant(38);
            e->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(e, 38, v);
            y++;
            e = MapGetCell((s16)x, (s16)y);
            e->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(e, 39, v);
            break;
        case 5:
            MapGetCell((s16)x, (s16)(y - 1))->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell((s16)(x + 1), (s16)y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell((s16)(x + 1), (s16)(y - 1))->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            v = GetRandomPieceVariant(43);
            e->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(e, 43, v);
            y++;
            e = MapGetCell((s16)x, (s16)y);
            e->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(e, 44, v);
            break;
        case 8:
            e->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(e, 37, 0xFF);
            break;
        case 9:
            e->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(e, 42, 0xFF);
            break;
        case 4:
            MapGetCell((s16)x, (s16)(y + 1))->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell((s16)(x + 1), (s16)y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell((s16)(x + 1), (s16)(y + 1))->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            v = GetRandomPieceVariant(40);
            e->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(e, 40, v);
            e = MapGetCell((s16)x, (s16)(y - 1));
            e->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(e, 41, v);
            go = 0;
            break;
        case 6:
            MapGetCell((s16)x, (s16)(y + 1))->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell((s16)(x - 1), (s16)y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell((s16)(x - 1), (s16)(y + 1))->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            v = GetRandomPieceVariant(45);
            e->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(e, 45, v);
            e = MapGetCell((s16)x, (s16)(y - 1));
            e->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(e, 46, v);
            go = 0;
            break;
        }

        y++;
    }
}

void MapMarkJumpSpot(MapPlatform* p) {
    s32 go = 1;
    u16 x = p->x;
    u16 y = p->y;

    while (go) {
        s16 cy = (s16)y;
        MapCell* c = MapGetCell((s16)x, cy);

        switch (c->type) {
        case 4:
            MapGetCell((s16)x, (s16)(y + 1))->flags |= MAP_CELL_FLAG_JUMP_PAD;
            MapGetCell((s16)(x + 1), cy)->flags |= MAP_CELL_FLAG_JUMP_PAD;
            MapGetCell((s16)(x + 1), (s16)(y + 1))->flags |= MAP_CELL_FLAG_JUMP_PAD;
            c->flags |= MAP_CELL_FLAG_JUMP_PAD;
            p->x = x + 1;
            p->y = y + 1;
            go = 0;
            break;
        case 6:
            MapGetCell((s16)x, (s16)(y + 1))->flags |= MAP_CELL_FLAG_JUMP_PAD;
            MapGetCell((s16)(x - 1), cy)->flags |= MAP_CELL_FLAG_JUMP_PAD;
            MapGetCell((s16)(x - 1), (s16)(y + 1))->flags |= MAP_CELL_FLAG_JUMP_PAD;
            c->flags |= MAP_CELL_FLAG_JUMP_PAD;
            p->x = x;
            p->y = y + 1;
            go = 0;
            break;
        default:
            break;
        }

        y++;
    }
}

void MapFindPlatformStairs(MapPlatform* p) {
    u16 x;
    u16 y;
    u16 d;
    MapCell* e;
    MapCell* q;

    x = p->left;

    while (x < p->right) {
        y = gMapTopRow;

        while (y < gMapBottomRow) {
            e = MapGetCell((s16)x, (s16)y);

            if (e->type == 4 || e->type == 6) {
                if (e->upperZ != -0x100000 && p->z == e->lowerZ) {
                    d = ((p->z - e->upperZ) >> 8) / 16;

                    if (FldPosHeightExceeds((FldPos*)e, 3)) {
                        q = MapGetCell((s16)x, (s16)(y - d));

                        if ((e->flags & (MAP_CELL_FLAG_EDGE_LEFT | MAP_CELL_FLAG_EDGE_RIGHT | MAP_CELL_FLAG_CORNER)) == 0 && (q->flags & (MAP_CELL_FLAG_EDGE_LEFT | MAP_CELL_FLAG_EDGE_RIGHT | MAP_CELL_FLAG_CORNER)) == 0) {
                            if (p->hasStairs == 0 ||
                                (p->spotUpperZ <= q->upperZ &&
                                 (p->spotUpperZ < q->upperZ ||
                                  p->left + GetRandom() % (p->right - p->left + 1) > x))) {
                                p->hasStairs = 1;
                                p->x = x;
                                p->y = y - d;
                                p->spotType = q->type;
                                p->spotUpperZ = q->upperZ;
                                p->spotLowerZ = q->lowerZ;
                            }
                        } else if (p->hasStairs == 0 && p->spotUpperZ <= q->upperZ &&
                                   (p->spotUpperZ < q->upperZ ||
                                    p->left + GetRandom() % (p->right - p->left + 1) > x)) {
                            p->x = x;
                            p->y = y - d;
                            p->spotType = q->type;
                            p->spotUpperZ = q->upperZ;
                            p->spotLowerZ = q->lowerZ;
                        }
                    }
                }
            }

            y++;
        }

        x++;
    }
}

void MapPlacePlatformStairs(void) {
    s32 i;

    for (i = 11; i >= 0; i--) {
        MapPlatform* e = &gMapPlatforms[i];

        if (e->z != 0x100000) {
            MapFindPlatformStairs(e);
        }

        if (e->hasStairs != 0) {
            MapBuildStairs(e->x, e->y);
        } else if (e->spotLowerZ != 0x100000) {
            MapMarkJumpSpot(e);
        }
    }
}

s16 MapOutlineNextRowLeftToRight(u8 a, u8 b, s16 c) {
    switch (a) {
    case 2:
    case 6:
        if (b == 6) {
            c++;
        }

        break;
    case 4:
        if (b != 6) {
            c--;
        }

        break;
    case 1:
    case 3:
        if (b == 3) {
            c--;
        }

        break;
    case 5:
        if (b != 3) {
            c++;
        }

        break;
    }

    return c;
}

s16 MapOutlineNextRowRightToLeft(u8 a, u8 b, s16 c) {
    switch (a) {
    case 2:
    case 4:
        if (b == 4) {
            c += 1;
        }

        break;
    case 6:
        if (b != 4) {
            c -= 1;
        }

        break;
    case 1:
    case 5:
        if (b == 5) {
            c -= 1;
        }

        break;
    case 3:
        if (b != 5) {
            c += 1;
        }

        break;
    }

    return c;
}

void MapFillOutlineCells(void) {
    s32 i;
    s32 j;
    s32 dir;
    MapCell* p;

    for (i = 0; i < gMapCols; i++) {
        dir = 10;

        for (j = 0; j < gMapRows; j++) {
            p = MapGetCell(i, j);

            switch (p->type) {
            case 2:
            case 4:
            case 6:
                dir = 0;
                break;
            case 3:
                dir = 8;
                break;
            case 5:
                dir = 9;
                break;
            case 1:
                dir = 7;
                break;
            case 11:
                if (dir != 10) {
                    MapCellSetType(p, dir, 0);
                }

                break;
            }
        }

        if (dir == 11) {
            for (j = 0; j < gMapRows; j++) {
                MapCellSetType(MapGetCell(i, j), 7, 0);
            }
        }
    }

    for (i = 0; i < gMapCols; i++) {
        dir = 10;

        for (j = gMapRows - 1; j >= 0; j--) {
            p = MapGetCell(i, j);

            switch (p->type) {
            case 4:
                dir = 8;
                break;
            case 6:
                dir = 9;
                break;
            case 2:
                dir = 7;
                break;
            case 11:
                if (dir != 10) {
                    MapCellSetType(p, dir, 0);
                }

                break;
            }
        }
    }
}

void func_080E13B0(void) {
    u16 y = gMapBottomRow;
    u16 n = y - gMapTopRow + 1;
    s32 j;

    for (j = 0; j < n; j++) {
        u16 x;

        for (x = 0; x < gMapCols; x++) {
            MapCell* c = MapGetCell((s16)x, (s16)y);
            s32 v;
            s32 ok;
            s32 k;

            switch (c->type) {
            case 0:
            case 1:
            case 3:
            case 5:
                v = c->upperZ;
                break;
            case 2:
            case 4:
            case 6:
                v = c->lowerZ;
                break;
            default:
                v = 0x100000;
                break;
            }

            if (v == 0x100000) {
                continue;
            }

            ok = 1;

            for (k = 11; k >= 0; k--) {
                if (gMapPlatforms[k].z != v) {
                    if (gMapPlatforms[k].z != 0x100000) {
                        ok = 0;
                    }
                } else {
                    if (ok == 0) {
                        if (k % 2) {
                            c->flags |= 2;
                        } else {
                            c->flags |= 1;
                        }
                    }

                    break;
                }
            }
        }

        y--;
    }
}

void MapMarkCellEdges(void) {
    s32 x;
    s32 y;

    for (y = 0; y < gMapRows; y++) {
        for (x = 0; x < gMapCols - 1; x++) {
            MapCell* a = MapGetCell(x, y);
            MapCell* b = MapGetCell(x + 1, y);
            s32 flag = 0;

            switch (a->type) {
            case 0:
                if (b->type != 0 && b->type != 3 && b->type != 4 && b->type != 5 &&
                    b->type != 6) {
                    flag = 1;
                }

                break;
            case 6:
                if (b->type != 9) {
                    flag = 1;
                }

                break;
            case 3:
                if (b->type != 8) {
                    flag = 1;
                }

                break;
            case 4:
            case 5:
                if (b->type != 0) {
                    flag = 1;
                }

                break;
            case 8:
                if (b->type != 8 && b->type != 4) {
                    flag = 1;
                }

                break;
            case 9:
                if (b->type != 9 && b->type != 5) {
                    flag = 1;
                }

                break;
            case 1:
            case 2:
            case 7:
                if (a->type != b->type) {
                    flag = 1;
                }

                break;
            }

            if (flag != 0) {
                a->flags |= MAP_CELL_FLAG_EDGE_RIGHT;
                b->flags |= MAP_CELL_FLAG_EDGE_LEFT;
            }

            switch (a->type) {
            case 4:
                if (MapGetCell(x + 1, y - 1)->type == 2) {
                    a->flags |= MAP_CELL_FLAG_EDGE_RIGHT;
                }

                break;
            case 6:
                if (MapGetCell(x - 1, y - 1)->type == 2) {
                    a->flags |= MAP_CELL_FLAG_EDGE_LEFT;
                }

                break;
            case 3:
                if (MapGetCell(x - 1, y + 1)->type == 1) {
                    a->flags |= MAP_CELL_FLAG_EDGE_LEFT;
                }

                break;
            case 5:
                if (MapGetCell(x + 1, y + 1)->type == 1) {
                    a->flags |= MAP_CELL_FLAG_EDGE_RIGHT;
                }

                break;
            }
        }
    }
}

void MapAssignCellPieces(void) {
    s32 i;
    s32 j;
    MapCell* e;
    u8 v;

    for (i = 0; i < gMapCols; i++) {
        for (j = 0; j < gMapRows; j++) {
            e = MapGetCell(i, j);

            if (e->bg3Piece != 7) {
                continue;
            }

            switch (e->type) {
            case 0:
                MapCellSetFloorBg3Piece(e);
                break;
            case 7:
                MapCellSetBg3Piece(e, 3);
                func_080E0A70(e, 4);
                break;
            case 8:
                MapCellSetBg3Piece(e, 4);
                func_080E0A70(e, 5);
                break;
            case 9:
                MapCellSetBg3Piece(e, 5);
                func_080E0A70(e, 6);
                break;
            case 2:
                v = GetRandomPieceVariant(10);

                if (FldPosHeightExceeds((FldPos*)e, 3)) {
                    MapCellSetFloorBg3Piece(e);
                    MapCellSetBg2Piece(e, 10, v);
                    MapCellSetBg3Piece(MapGetCell(i, j - 1), 3);
                    MapCellSetBg2Piece(MapGetCell(i, j - 1), 11, v);
                } else {
                    MapCellSetFloorBg3Piece(e);
                    MapCellSetBg2Piece(e, 12, v);
                }

                break;
            case 1:
                v = GetRandomPieceVariant(7);
                MapCellSetBg2Piece(MapGetCell(i, j - 1), 48, v);
                MapCellSetFloorBg3Piece(e);

                if (FldPosHeightExceeds((FldPos*)e, 3)) {
                    MapCellSetBg2Piece(e, 7, v);
                    MapCellSetBg3Piece(MapGetCell(i, j + 1), 3);
                    MapCellSetBg2Piece(MapGetCell(i, j + 1), 8, v);
                } else {
                    MapCellSetBg2Piece(e, 9, v);
                }

                break;
            case 3:
                if (e->flags & MAP_CELL_FLAG_CORNER) {
                    MapCellSetFloorBg3Piece(e);
                    sub_080E0B00(e, 23);

                    if (FldPosHeightExceeds((FldPos*)e, 2)) {
                        func_080E0BF4(i, j + 1, 4, 24);
                    } else {
                        func_080E0BF4(i, j + 1, 4, 25);

                        if ((MapGetCell(i, j + 2)->flags & MAP_CELL_FLAG_CORNER) == 0) {
                            MapCellSetFloorBg3Piece(MapGetCell(i, j + 2));
                            MapCellSetBg2Piece(MapGetCell(i, j + 2), 15, 0);
                        }
                    }
                } else {
                    v = GetRandomPieceVariant(13);
                    MapCellSetFloorBg3Piece(e);
                    MapCellSetBg2Piece(e, 13, v);
                    MapCellSetBg2Piece(MapGetCell(i, j - 1), 47, v);

                    if (FldPosHeightExceeds((FldPos*)e, 2)) {
                        MapCellSetBg3Piece(MapGetCell(i, j + 1), 4);
                        MapCellSetBg2Piece(MapGetCell(i, j + 1), 14, v);
                    } else if ((MapGetCell(i, j + 2)->flags & MAP_CELL_FLAG_CORNER) == 0) {
                        MapCellSetBg3Piece(MapGetCell(i, j + 1), 4);
                        MapCellSetBg2Piece(MapGetCell(i, j + 1), 17, v);
                        MapCellSetFloorBg3Piece(MapGetCell(i, j + 2));
                        MapCellSetBg2Piece(MapGetCell(i, j + 2), 15, v);
                    }
                }

                break;
            case 5:
                if (e->flags & MAP_CELL_FLAG_CORNER) {
                    MapCellSetFloorBg3Piece(e);
                    sub_080E0B00(e, 29);

                    if (FldPosHeightExceeds((FldPos*)e, 2)) {
                        func_080E0BF4(i, j + 1, 5, 30);
                    } else {
                        func_080E0BF4(i, j + 1, 5, 31);

                        if ((MapGetCell(i, j + 2)->flags & MAP_CELL_FLAG_CORNER) == 0) {
                            MapCellSetFloorBg3Piece(MapGetCell(i, j + 2));
                            MapCellSetBg2Piece(MapGetCell(i, j + 2), 20, 0);
                        }
                    }
                } else {
                    v = GetRandomPieceVariant(18);
                    MapCellSetFloorBg3Piece(e);
                    MapCellSetBg2Piece(e, 18, v);
                    MapCellSetBg2Piece(MapGetCell(i, j - 1), 49, v);

                    if (FldPosHeightExceeds((FldPos*)e, 2)) {
                        MapCellSetBg3Piece(MapGetCell(i, j + 1), 5);
                        MapCellSetBg2Piece(MapGetCell(i, j + 1), 19, v);
                    } else if ((MapGetCell(i, j + 2)->flags & MAP_CELL_FLAG_CORNER) == 0) {
                        MapCellSetBg3Piece(MapGetCell(i, j + 1), 5);
                        MapCellSetBg2Piece(MapGetCell(i, j + 1), 22, v);
                        MapCellSetFloorBg3Piece(MapGetCell(i, j + 2));
                        MapCellSetBg2Piece(MapGetCell(i, j + 2), 20, v);
                    }
                }

                break;
            case 4:
                if (e->flags & MAP_CELL_FLAG_CORNER) {
                    MapCellSetFloorBg3Piece(e);
                    sub_080E0B00(e, 26);

                    if (FldPosHeightExceeds((FldPos*)e, 2)) {
                        func_080E0BF4(i, j - 1, 4, 27);
                    } else if ((MapGetCell(i, j - 2)->flags & MAP_CELL_FLAG_CORNER) == 0) {
                        func_080E0BF4(i, j - 1, 4, 28);
                    } else {
                        func_080E0BF4(i, j - 1, 4, 35);
                    }
                } else {
                    v = GetRandomPieceVariant(15);
                    MapCellSetFloorBg3Piece(e);
                    MapCellSetBg2Piece(e, 15, v);

                    if (FldPosHeightExceeds((FldPos*)e, 2)) {
                        MapCellSetBg3Piece(MapGetCell(i, j - 1), 4);
                        MapCellSetBg2Piece(MapGetCell(i, j - 1), 16, v);
                    }
                }

                break;
            case 6:
                if (e->flags & MAP_CELL_FLAG_CORNER) {
                    MapCellSetFloorBg3Piece(e);
                    sub_080E0B00(e, 32);

                    if (FldPosHeightExceeds((FldPos*)e, 2)) {
                        func_080E0BF4(i, j - 1, 5, 33);
                    } else if ((MapGetCell(i, j - 2)->flags & MAP_CELL_FLAG_CORNER) == 0) {
                        func_080E0BF4(i, j - 1, 5, 34);
                    } else {
                        func_080E0BF4(i, j - 1, 5, 36);
                    }
                } else {
                    v = GetRandomPieceVariant(20);
                    MapCellSetFloorBg3Piece(e);
                    MapCellSetBg2Piece(e, 20, v);

                    if (FldPosHeightExceeds((FldPos*)e, 2)) {
                        MapCellSetBg3Piece(MapGetCell(i, j - 1), 5);
                        MapCellSetBg2Piece(MapGetCell(i, j - 1), 21, v);
                    }
                }

                break;
            }
        }
    }
}

void MapCellSetBg1Piece(s16 x, s16 y, u8 n) {
    MapCell* p = MapGetCell(x, y);

    if (p != NULL) {
        u16* base = gMapRoomDef->map;
        const u8* q = gUnk_0984D3F8[n];
        s32 t = q[1] * 4 + q[2] * 64;
        p->bg1Piece = n;
        p->bg1Map = base + t;
    }
}

u8 MapCellIsUnbounded(s16 x, s16 y) {
    MapCell* p = MapGetCell(x, y);

    if (p == NULL || p->upperZ == -0x100000 || p->lowerZ == 0x100000) {
        return 1;
    }

    return 0;
}

u8 MapCellHasType(s16 x, s16 y, u8 n) {
    MapCell* p = MapGetCell(x, y);

    if (p != NULL && p->type == n) {
        return 1;
    }

    return 0;
}

void MapAssignWallTopPieces(s16 x, s16 y) {
    MapCell* p = MapGetCell(x, y + 7);

    if (p->upperZ == -0x100000) {
        switch (p->type) {
        case 4:
            if (!MapCellIsUnbounded(x + 1, y + 6)) {
                MapCellSetBg1Piece(x, y, 18);
                MapCellSetBg1Piece(x, y + 1, 19);
            } else if (!MapCellIsUnbounded(x - 1, y + 7)) {
                MapCellSetBg1Piece(x, y, 26);
                MapCellSetBg1Piece(x, y + 1, 27);
            } else {
                MapCellSetBg1Piece(x, y, 6);
                MapCellSetBg1Piece(x, y + 1, 7);
            }

            break;
        case 6:
            if (!MapCellIsUnbounded(x - 1, y + 6)) {
                MapCellSetBg1Piece(x, y, 20);
                MapCellSetBg1Piece(x, y + 1, 21);
            } else if (!MapCellIsUnbounded(x + 1, y + 7)) {
                MapCellSetBg1Piece(x, y, 28);
                MapCellSetBg1Piece(x, y + 1, 29);
            } else {
                MapCellSetBg1Piece(x, y, 8);
                MapCellSetBg1Piece(x, y + 1, 9);
            }

            break;
        case 2:
            if (!MapCellIsUnbounded(x + 1, y + 7)) {
                MapCellSetBg1Piece(x, y, 2);
                MapCellSetBg1Piece(x, y + 1, 34);
            } else if (!MapCellIsUnbounded(x - 1, y + 7)) {
                MapCellSetBg1Piece(x, y, 3);
                MapCellSetBg1Piece(x, y + 1, 35);
            } else {
                MapCellSetBg1Piece(x, y, 1);
                MapCellSetBg1Piece(x, y + 1, 4);
            }

            break;
        case 7:
        case 8:
        case 9:
            if (MapCellHasType(x - 1, y + 6, 6)) {
                MapCellSetBg1Piece(x, y, 15);
            } else if (MapCellHasType(x + 1, y + 6, 4)) {
                MapCellSetBg1Piece(x, y, 14);
            } else if (!MapCellIsUnbounded(x + 1, y + 7)) {
                MapCellSetBg1Piece(x, y, 2);
            } else if (!MapCellIsUnbounded(x - 1, y + 7)) {
                MapCellSetBg1Piece(x, y, 3);
            } else {
                MapCellSetBg1Piece(x, y, 1);
            }

            break;
        }
    }
}

void MapAssignLedgePieces(s16 x, s16 y) {
    MapCell* p = MapGetCell(x, y);

    if (p->lowerZ == 0x100000 && p->bg1Piece == 0) {
        switch (p->type) {
        case 3:
            MapCellSetBg1Piece(x, y, 12);
            MapCellSetBg1Piece(x, y - 1, 13);

            if (!MapCellIsUnbounded(x - 1, y + 1)) {
                MapCellSetBg1Piece(x, y + 1, 1);
                MapCellSetBg1Piece(x - 1, y + 1, 24);
                MapCellSetBg1Piece(x - 1, y, 25);
            }

            if (!MapCellIsUnbounded(x + 1, y)) {
                MapCellSetBg1Piece(x + 1, y - 1, 32);
                MapCellSetBg1Piece(x + 1, y - 2, 33);
                MapCellSetBg1Piece(x + 1, y, 2);

                if (MapCellIsUnbounded(x + 1, y + 1)) {
                    MapCellSetBg1Piece(x + 1, y + 1, 16);
                } else {
                    MapCellSetBg1Piece(x + 1, y + 1, 2);
                }
            }

            break;
        case 5:
            MapCellSetBg1Piece(x, y, 10);
            MapCellSetBg1Piece(x, y - 1, 11);

            if (!MapCellIsUnbounded(x + 1, y + 1)) {
                MapCellSetBg1Piece(x, y + 1, 1);
                MapCellSetBg1Piece(x + 1, y + 1, 22);
                MapCellSetBg1Piece(x + 1, y, 23);
            }

            if (!MapCellIsUnbounded(x - 1, y)) {
                MapCellSetBg1Piece(x - 1, y - 1, 30);
                MapCellSetBg1Piece(x - 1, y - 2, 31);
                MapCellSetBg1Piece(x - 1, y, 3);

                if (MapCellIsUnbounded(x - 1, y + 1)) {
                    MapCellSetBg1Piece(x - 1, y + 1, 17);
                } else {
                    MapCellSetBg1Piece(x - 1, y + 1, 3);
                }
            }

            break;
        case 1:
            MapCellSetBg1Piece(x, y, 1);
            MapCellSetBg1Piece(x, y - 1, 5);

            if (!MapCellIsUnbounded(x - 1, y)) {
                MapCellSetBg1Piece(x - 1, y, 3);
                MapCellSetBg1Piece(x - 1, y - 1, 37);
            }

            if (!MapCellIsUnbounded(x + 1, y)) {
                MapCellSetBg1Piece(x + 1, y, 2);
                MapCellSetBg1Piece(x + 1, y - 1, 36);
            }

            break;
        case 7:
        case 8:
        case 9:
            MapCellSetBg1Piece(x, y, 1);

            if (MapCellHasType(x - 1, y + 1, 3)) {
                MapCellSetBg1Piece(x - 1, y, 3);
                MapCellSetBg1Piece(x - 1, y + 1, 17);
            }

            if (MapCellHasType(x + 1, y + 1, 5)) {
                MapCellSetBg1Piece(x + 1, y, 2);
                MapCellSetBg1Piece(x + 1, y + 1, 16);
            }

            if (!MapCellIsUnbounded(x - 1, y)) {
                if (MapCellHasType(x, y - 1, 3)) {
                    MapCellSetBg1Piece(x - 1, y, 24);
                    MapCellSetBg1Piece(x - 1, y - 1, 25);
                } else {
                    MapCellSetBg1Piece(x - 1, y, 3);
                }
            }

            if (!MapCellIsUnbounded(x + 1, y)) {
                if (MapCellHasType(x, y - 1, 5)) {
                    MapCellSetBg1Piece(x + 1, y, 22);
                    MapCellSetBg1Piece(x + 1, y - 1, 23);
                } else {
                    MapCellSetBg1Piece(x + 1, y, 2);
                }
            }

            break;
        }
    }
}

void MapAssignLeftBorderPiece(s16 y) {
    switch (MapGetCell(0, y)->bg1Piece) {
    case 10:
        MapCellSetBg1Piece(0, y, 16);
        break;
    case 6:
        MapCellSetBg1Piece(0, y, 14);
        break;
    case 0:
    case 7:
    case 11:
    case 18:
    case 19:
    case 22:
    case 23:
        MapCellSetBg1Piece(0, y, 2);
        break;
    }
}

void MapAssignRightBorderPiece(s16 j) {
    s16 x = gMapCols - 1;
    MapCell* q = MapGetCell(x, j);

    switch (q->bg1Piece) {
    case 12:
        MapCellSetBg1Piece(x, j, 17);
        break;
    case 8:
        MapCellSetBg1Piece(x, j, 15);
        break;
    case 0:
    case 9:
    case 13:
    case 20:
    case 21:
    case 24:
    case 25:
        MapCellSetBg1Piece(x, j, 3);
        break;
    }
}

void MapAssignBg1Pieces(void) {
    s32 i;
    s32 j;

    for (i = 0; i < gMapCols; i++) {
        for (j = 0; j < gMapRows; j++) {
            MapAssignWallTopPieces(i, j);
            MapAssignLedgePieces(i, j);
        }
    }

    for (j = 0; j < gMapRows; j++) {
        MapAssignLeftBorderPiece(j);
        MapAssignRightBorderPiece(j);
    }
}

void MapComputeCellHeights(void) {
    s16 i;
    s16 j;
    s32 z;
    MapCell* p;

    for (i = 0; i < gMapCols; i++) {
        z = 0x100000;

        for (j = gMapRows - 1; j >= 0; j--) {
            p = MapGetCell(i, j);

            switch (p->type) {
            case 1:
            case 3:
            case 5:
                p->lowerZ = z;
                z = p->upperZ;
                break;
            case 0:
                p->upperZ = z;
                p->lowerZ = z;
                break;
            case 2:
            case 4:
            case 6:
                p->lowerZ = p->upperZ;
                break;
            case 7:
            case 8:
            case 9:
            default:
                p->lowerZ = z;
                break;
            }
        }
    }

    for (i = 0; i < gMapCols; i++) {
        z = -0x100000;

        for (j = 0; j < gMapRows; j++) {
            p = MapGetCell(i, j);

            switch (p->type) {
            case 1:
            case 3:
            case 5:
                z = p->upperZ;
                break;
            case 2:
            case 4:
            case 6:
            case 7:
            case 8:
            case 9:
                p->upperZ = z;
                break;
            }
        }
    }
}

void MapPlaceDoorOnPlatform(MapPlatform* p, s32 a) {
    u8 d;
    s32 i;
    u16 x;
    u16 y;
    u16 w;
    MapDoor* e;
    MapCell* q;

    d = a;
    e = GetMapDoor(d);

    if (!(e->flags & DOOR_FLAG_PRESENT)) {
        return;
    }

    w = p->right - p->left;

    if (d == 0) {
        x = p->left + w * 5 / 8 + GetRandom() % (w >> 2);

        for (i = 0; i < w; i++) {
            for (y = gMapTopRow; y <= gMapBottomRow; y++) {
                q = MapGetCell(x, y);

                if (q->type == 6 && q->lowerZ == p->z && q->upperZ == -0x100000 && (q->flags & MAP_CELL_FLAG_STAIRS) == 0) {
                    e->cellX = x;
                    e->cellY = y;
                    q->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    q->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    MapGetCell(x, y + 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x - 1, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x - 1, y + 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x, y - 1)->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    MapGetCell(x, y - 2)->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    MapGetCell(x, y - 3)->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    return;
                }
            }

            x = x < p->right - 1 ? x + 1 : p->left;
        }
    }

    if (d == 2) {
        x = p->left + w * 5 / 8 + GetRandom() % (w >> 2);

        for (i = 0; i < w; i++) {
            for (y = gMapTopRow; y <= gMapBottomRow; y++) {
                q = MapGetCell(x, y);

                if (q->type == 3 && q->upperZ == p->z && q->lowerZ == 0x100000 && (q->flags & MAP_CELL_FLAG_STAIRS) == 0) {
                    e->cellX = x;
                    e->cellY = y;
                    MapGetCell(x, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x, y - 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x - 1, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x - 1, y - 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    return;
                }
            }

            x = x < p->right - 1 ? x + 1 : p->left;
        }
    }

    if (d == 1) {
        x = p->left + w * 3 / 8 - GetRandom() % (w >> 2);

        for (i = 0; i < w; i++) {
            for (y = gMapTopRow; y <= gMapBottomRow; y++) {
                q = MapGetCell(x, y);

                if (q->type == 5 && q->upperZ == p->z && q->lowerZ == 0x100000 && (q->flags & MAP_CELL_FLAG_STAIRS) == 0) {
                    e->cellX = x;
                    e->cellY = y;
                    MapGetCell(x, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x, y - 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x + 1, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x + 1, y - 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    return;
                }
            }

            x = x > p->left ? x - 1 : p->right - 1;
        }
    }

    if (d == 3) {
        x = p->left + w * 3 / 8 - GetRandom() % (w >> 2);

        for (i = 0; i < w; i++) {
            for (y = gMapTopRow; y <= gMapBottomRow; y++) {
                q = MapGetCell(x, y);

                if (q->type == 4 && q->lowerZ == p->z && q->upperZ == -0x100000 && (q->flags & MAP_CELL_FLAG_STAIRS) == 0) {
                    e->cellX = x;
                    e->cellY = y;
                    q->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    q->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    MapGetCell(x, y + 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x + 1, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x + 1, y + 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x, y - 1)->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    MapGetCell(x, y - 2)->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    MapGetCell(x, y - 3)->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    return;
                }
            }

            x = x > p->left ? x - 1 : p->right - 1;
        }
    }
}

s32 MapPlaceLastPlatformDoor(void) {
    s32 r = 5;
    MapPlatform* p = &gMapPlatforms[11];

    while (p->z == 0x100000) {
        p--;
    }

    switch (gMapRoomState->flags & (ROOM_FLAG_DOOR(1) | ROOM_FLAG_DOOR(2))) {
    case 0x2000000:
        r = 1;
        break;
    case 0x4000000:
        r = 2;
        break;
    case 0x6000000:
        if (p->right == gMapCols) {
            r = 2;
        } else if (p->left == 0) {
            r = 1;
        } else {
            s32 v = GetRandom() % 2 ? 2 : 1;

            r = v;
        }

        break;
    }

    if (r != 5) {
        MapPlaceDoorOnPlatform(p, r);
    }

    return r;
}

u8 MapPlaceFirstPlatformDoor(u8 a) {
    MapPlatform* p = gMapPlatforms;

    switch (gMapRoomState->flags & (ROOM_FLAG_DOOR(0) | ROOM_FLAG_DOOR(3))) {
    case 0x1000000:
        a = 0;
        break;
    case 0x8000000:
        a = 3;
        break;
    case 0x9000000:
        break;
    default:
        a = 5;
        break;
    }

    if (a != 5) {
        MapPlaceDoorOnPlatform(p, a);
    }

    return a;
}

void MapPlaceRightPlatformDoor(u8 a) {
    MapPlatform* p = gMapPlatforms;

    while (p->right != gMapCols) {
        p++;
    }

    MapPlaceDoorOnPlatform(p, a);
}

void MapPlaceLeftPlatformDoor(u8 a) {
    MapPlatform* p = gMapPlatforms;

    while (p->left != 0) {
        p++;
    }

    MapPlaceDoorOnPlatform(p, a);
}

void MapPlaceDoorsOnLastPlatform(void) {
    MapPlatform* p = &gMapPlatforms[11];

    while (p->z == 0x100000) {
        p--;
    }

    MapPlaceDoorOnPlatform(p, 0);
    MapPlaceDoorOnPlatform(p, 1);
    MapPlaceDoorOnPlatform(p, 2);
    MapPlaceDoorOnPlatform(p, 3);
}

void MapPlaceDoors(void) {
    s32 i;
    MapDoor* e;

    for (i = 0; i < 4; i++) {
        e = GetMapDoor(i);
        e->room = GetMapRoomLink(gMapFloorState.room, i);
        e->side = i;
        e->flags = GetMapDoorFlags(gMapFloorState.room, i);

        if (e->room != MAP_ROOM_NONE) {
            switch (i) {
            case 0:
                gMapRoomState->flags |= ROOM_FLAG_DOOR(0);
                break;
            case 1:
                gMapRoomState->flags |= ROOM_FLAG_DOOR(1);
                break;
            case 2:
                gMapRoomState->flags |= ROOM_FLAG_DOOR(2);
                break;
            case 3:
                gMapRoomState->flags |= ROOM_FLAG_DOOR(3);
                break;
            }
        }
    }

    if (gMapRoomState->roomType != 3) {
        if ((u8)MapPlaceLastPlatformDoor() != 2) {
            MapPlaceRightPlatformDoor(2);

            if (MapPlaceFirstPlatformDoor(0) != 3) {
                MapPlaceLeftPlatformDoor(3);
            }
        } else {
            MapPlaceLeftPlatformDoor(1);

            if (MapPlaceFirstPlatformDoor(3) != 0) {
                MapPlaceRightPlatformDoor(0);
            }
        }
    } else {
        MapPlaceDoorsOnLastPlatform();
    }
}

void MapComputeRowBounds(void) {
    s32 i;
    s32 j;

    gMapTopRow = gMapRows;
    gMapBottomRow = 0;

    for (i = 0; i < gMapCols; i++) {
        for (j = 0; j < gMapRows; j++) {
            switch (MapGetCell(i, j)->type) {
            case 2:
            case 4:
            case 6:
                if (j < gMapTopRow) {
                    gMapTopRow = j;
                }

                break;
            case 1:
            case 3:
            case 5:
                if (j > gMapBottomRow) {
                    gMapBottomRow = j;
                }

                break;
            }
        }
    }
}

s32 PickRandomTopEdgeType(s16 a, s16 b, s16 c) {
    s32 ret;

    if (c - a < b - c) {
        if (GetRandom() % 3 != 0) {
            ret = 4;
        } else {
            ret = GetRandom() % 5 != 0 ? 2 : 6;
        }
    } else {
        if (GetRandom() % 3 != 0) {
            ret = 6;
        } else {
            ret = GetRandom() % 5 != 0 ? 2 : 4;
        }
    }

    return ret;
}

s32 PickRandomBottomEdgeType(s16 a, s16 b, s16 c) {
    s32 ret;

    if (c - a < b - c) {
        if (GetRandom() % 3 != 0) {
            ret = 5;
        } else {
            ret = GetRandom() % 5 != 0 ? 1 : 3;
        }
    } else {
        if (GetRandom() % 3 != 0) {
            ret = 3;
        } else {
            ret = GetRandom() % 5 != 0 ? 1 : 5;
        }
    }

    return ret;
}

s32 GetMatchingBottomEdgeType(s16 x, s16 y) {
    switch (MapGetCell(x, y)->type) {
    case 6:
        return 5;
    case 2:
        return 1;
    case 4:
        return 3;
    }

    return 0xB;
}

s32 PickEdgeTypeByHalf(s16 a, s16 b, s16 c, u8 d) {
    if (d != 0) {
        if (c - a < b - c) {
            return 4;
        }

        return 6;
    }

    if (c - a < b - c) {
        return 5;
    }

    return 3;
}

s32 PickEdgeTypeByThird(s16 a, s16 b, s16 c, u8 d) {
    if (d != 0) {
        if (c - a < (b - a) / 3) {
            return 4;
        }

        if (b - c > (b - a) / 3) {
            return 2;
        }

        return 6;
    }

    if (c - a < (b - a) / 3) {
        return 5;
    }

    if (b - c > (b - a) / 3) {
        return 1;
    }

    return 3;
}

s32 GetTopEdgeTypeBelowLedge(u8 d, s16 x, s16 y) {
    s32 i;

    if (d != 0) {
        for (i = y; i >= 0; i--) {
            switch (MapGetCell(x, i)->type) {
            case 3:
                return 4;
            case 5:
                return 6;
            case 1:
                return 2;
            }
        }
    }

    return 0xB;
}

void MapSetPlatform(u8 i, u16 a, u16 b, s16 c) {
    if (gMapPlatforms[i].z == 0x100000) {
        gMapPlatforms[i].left = a;
        gMapPlatforms[i].right = b;
        gMapPlatforms[i].z = c << 12;
    }
}

void MapTracePlatformLeftToRight(u8 i, s16 a, s16 b, s16 c, u8 e) {
    s16 x;
    s16 y;
    s16 yn;
    s16 n;
    u8 t;
    s32 k;
    s16 yb;
    u16* buf;
    u16* w;
    s32 v;
    MapCell* q;
    s32 m;

    v = gMapPlatforms[i].z;
    buf = EwramAlloc(96);
    y = c;
    k = 4;
    q = MapGetCell(a, y);
    MapCellSetType(q, 4, v);
    q->flags |= MAP_CELL_FLAG_CORNER;
    w = buf;
    *w++ = y;

    for (x = a + 1; x < b - 1; x++) {
        t = GetTopEdgeTypeBelowLedge(i, x, y);

        if (t == 11) {
            if (y <= 3) {
                t = 6;
            } else if (i == 0) {
                if (e == 2) {
                    t = PickEdgeTypeByHalf(a, b, x, 1);
                } else if (e == 3) {
                    t = PickEdgeTypeByThird(a, b, x, 1);
                } else {
                    t = PickRandomTopEdgeType(a, b, x);
                }
            } else {
                t = PickRandomTopEdgeType(a, b, x);
            }
        }

        y = MapOutlineNextRowLeftToRight(k, t, y);
        k = t;
        q = MapGetCell(x, y);
        MapCellSetType(q, t, v);
        *w++ = y;
    }

    n = MapOutlineNextRowLeftToRight(k, 6, y);
    q = MapGetCell(x, n);
    MapCellSetType(q, 6, v);
    q->flags |= MAP_CELL_FLAG_CORNER;
    yb = n + (b - a);
    y = c + 1;
    q = MapGetCell(a, y);
    k = 5;
    MapCellSetType(q, 5, v);
    q->flags |= MAP_CELL_FLAG_CORNER;
    w = buf + 1;

    for (x = a + 1; x < b - 1; x++) {
        yn = MapOutlineNextRowLeftToRight(k, 1, y);

        if (b - x == 2 && yb - yn == 2) {
            t = 5;
        } else if (yb - yn == 1) {
            t = 1;
        } else if (yn >= yb) {
            t = 3;
        } else if (yn - w[1] < gMapForm.minDepth) {
            t = 5;
        } else if (yn - w[1] > gMapForm.maxDepth) {
            t = 3;
        } else if (yn - w[1] == gMapForm.minDepth || yn - w[1] == gMapForm.maxDepth) {
            t = GetMatchingBottomEdgeType(x, w[0]);
        } else if (e == 2) {
            t = PickEdgeTypeByHalf(a, b, x, 0);
        } else if (e == 3) {
            t = PickEdgeTypeByThird(a, b, x, 0);
        } else {
            t = PickRandomBottomEdgeType(a, b, x);
        }

        if (yn >= gMapRows - 1 && t == 5) {
            t = 1;
        }

        y = MapOutlineNextRowLeftToRight(k, t, y);
        k = t;
        q = MapGetCell(x, y);
        MapCellSetType(q, t, v);
        w++;
        yb--;
    }

    m = MapOutlineNextRowLeftToRight(k, 3, y);
    q = MapGetCell(x, m);
    MapCellSetType(q, 3, v);
    q->flags |= MAP_CELL_FLAG_CORNER;
    EwramFree(buf);
}

void MapTracePlatformRightToLeft(u8 i, s16 a, s16 b, s16 c, u8 e) {
    s16 x;
    s16 yn;
    s16 n;
    u8 t;
    s32 k;
    s16 y;
    s16 yb;
    u16* buf;
    u16* w;
    s32 v;
    MapCell* q;
    s32 m;

    v = gMapPlatforms[i].z;
    buf = EwramAlloc(96);
    y = c;
    k = 6;
    q = MapGetCell(b - 1, y);
    MapCellSetType(q, 6, v);
    q->flags |= MAP_CELL_FLAG_CORNER;
    w = buf;
    *w++ = y;

    for (x = b - 2; x > a; x--) {
        t = GetTopEdgeTypeBelowLedge(i, x, y);

        if (t == 11) {
            if (y <= 3) {
                t = 4;
            } else if (i == 0) {
                if (e == 2) {
                    t = PickEdgeTypeByHalf(a, b, x, 1);
                } else if (e == 3) {
                    t = PickEdgeTypeByThird(a, b, x, 1);
                } else {
                    t = PickRandomTopEdgeType(a, b, x);
                }
            } else {
                t = PickRandomTopEdgeType(a, b, x);
            }
        }

        y = MapOutlineNextRowRightToLeft(k, t, y);
        k = t;
        q = MapGetCell(x, y);
        MapCellSetType(q, t, v);
        *w++ = y;
    }

    n = MapOutlineNextRowRightToLeft(k, 4, y);
    q = MapGetCell(x, n);
    MapCellSetType(q, 4, v);
    q->flags |= MAP_CELL_FLAG_CORNER;
    yb = n + (b - a);
    y = c + 1;
    q = MapGetCell(b - 1, y);
    k = 3;
    MapCellSetType(q, 3, v);
    q->flags |= MAP_CELL_FLAG_CORNER;
    w = buf + 1;

    for (x = b - 2; x > a; x--) {
        yn = MapOutlineNextRowRightToLeft(k, 1, y);

        if (x - a == 1 && yb - yn == 2) {
            t = 3;
        } else if (yb - yn == 1) {
            t = 1;
        } else if (yn >= yb) {
            t = 5;
        } else if (yn - w[1] < gMapForm.minDepth) {
            t = 3;
        } else if (yn - w[1] > gMapForm.maxDepth) {
            t = 5;
        } else if (yn - w[1] == gMapForm.minDepth || yn - w[1] == gMapForm.maxDepth) {
            t = GetMatchingBottomEdgeType(x, w[0]);
        } else if (e == 2) {
            t = PickEdgeTypeByHalf(a, b, x, 0);
        } else if (e == 3) {
            t = PickEdgeTypeByThird(a, b, x, 0);
        } else {
            t = PickRandomBottomEdgeType(a, b, x);
        }

        if (yn >= gMapRows - 1 && t == 3) {
            t = 1;
        }

        y = MapOutlineNextRowRightToLeft(k, t, y);
        k = t;
        q = MapGetCell(x, y);
        MapCellSetType(q, t, v);
        w++;
        yb--;
    }

    m = MapOutlineNextRowRightToLeft(k, 5, y);
    q = MapGetCell(x, m);
    MapCellSetType(q, 5, v);
    q->flags |= MAP_CELL_FLAG_CORNER;
    EwramFree(buf);
}

void MapTracePlatformOutward(u8 i, s16 a, s16 b, s16 c, s16 d, u8 e) {
    s16 x;
    s16 yn;
    s16 n;
    u8 t;
    s32 k;
    s16 y;
    s16 yb;
    u16* buf;
    u16* w;
    s32 v;
    MapCell* q;
    s32 m;

    v = gMapPlatforms[i].z;
    buf = EwramAlloc(96);
    w = buf + c;
    y = d;
    t = GetTopEdgeTypeBelowLedge(i, c, y);
    k = t;
    q = MapGetCell(c, y);
    MapCellSetType(q, t, v);
    *w++ = y;

    for (x = c + 1; x < b - 1; x++) {
        s32 t = (u8)GetTopEdgeTypeBelowLedge(i, x, y);

        if (t == 11) {
            if (y <= 3) {
                t = 6;
            } else if (i == 0) {
                if (e == 2) {
                    t = (u8)PickEdgeTypeByHalf(a, b, x, 1);
                } else if (e == 3) {
                    t = (u8)PickEdgeTypeByThird(a, b, x, 1);
                } else {
                    t = (u8)PickRandomTopEdgeType(a, b, x);
                }
            } else {
                t = (u8)PickRandomTopEdgeType(a, b, x);
            }
        }

        y = MapOutlineNextRowLeftToRight(k, t, y);
        k = t;
        q = MapGetCell(x, y);
        MapCellSetType(q, t, v);
        *w++ = y;
    }

    y = MapOutlineNextRowLeftToRight(k, 6, y);
    q = MapGetCell(x, y);
    MapCellSetType(q, 6, v);
    q->flags |= MAP_CELL_FLAG_CORNER;
    *w = y;
    w = buf + c;
    y = d;
    t = GetTopEdgeTypeBelowLedge(i, c, y);
    k = t;
    w--;

    for (x = c - 1; x > a; x--) {
        s32 t = (u8)GetTopEdgeTypeBelowLedge(i, x, y);

        if (t == 11) {
            if (y <= 3) {
                t = 4;
            } else if (i == 0) {
                if (e == 2) {
                    t = (u8)PickEdgeTypeByHalf(a, b, x, 1);
                } else if (e == 3) {
                    t = (u8)PickEdgeTypeByThird(a, b, x, 1);
                } else {
                    t = (u8)PickRandomTopEdgeType(a, b, x);
                }
            } else {
                t = (u8)PickRandomTopEdgeType(a, b, x);
            }
        }

        y = MapOutlineNextRowRightToLeft(k, t, y);
        k = t;
        q = MapGetCell(x, y);
        MapCellSetType(q, t, v);
        *w-- = y;
    }

    n = MapOutlineNextRowRightToLeft(k, 4, y);
    q = MapGetCell(x, n);
    MapCellSetType(q, 4, v);
    q->flags |= MAP_CELL_FLAG_CORNER;
    yb = *(buf + b - a - 1) + (b - a);
    y = n + 1;
    q = MapGetCell(a, y);
    k = 5;
    MapCellSetType(q, 5, v);
    q->flags |= MAP_CELL_FLAG_CORNER;
    w = buf + 1;

    for (x = a + 1; x < b - 1; x++) {
        yn = MapOutlineNextRowLeftToRight(k, 1, y);

        if (b - x == 2 && yb - yn == 2) {
            t = 5;
        } else if (yb - yn == 1) {
            t = 1;
        } else if (yn >= yb) {
            t = 3;
        } else if (yn - w[1] < gMapForm.minDepth) {
            t = 5;
        } else if (yn - w[1] > gMapForm.maxDepth) {
            t = 3;
        } else if (yn - w[1] == gMapForm.minDepth || yn - w[1] == gMapForm.maxDepth) {
            t = GetMatchingBottomEdgeType(x, w[0]);
        } else if (e == 2) {
            t = PickEdgeTypeByHalf(a, b, x, 0);
        } else if (e == 3) {
            t = PickEdgeTypeByThird(a, b, x, 0);
        } else {
            t = PickRandomBottomEdgeType(a, b, x);
        }

        if (yn >= gMapRows - 1 && t == 5) {
            t = 1;
        }

        y = MapOutlineNextRowLeftToRight(k, t, y);
        k = t;
        q = MapGetCell(x, y);
        MapCellSetType(q, t, v);
        w++;
        yb--;
    }

    m = MapOutlineNextRowLeftToRight(k, 3, y);
    q = MapGetCell(x, m);
    MapCellSetType(q, 3, v);
    q->flags |= MAP_CELL_FLAG_CORNER;
    EwramFree(buf);
}

void MapFindLowestEdgeRightward(s32 a, s16* px, s16* py, s16* pz, s16 lo, s16 hi) {
    s32 x = lo + GetRandom() % (hi - lo);
    s32 n;

    for (n = 0; n < -lo + hi; n++) {
        s32 j;

        for (j = gMapRows - 1; j >= 0; j--) {
            MapCell* p = MapGetCell(x, j);

            if (p->type == a) {
                *px = x;
                *py = j;
                *pz = (p->upperZ >> 11) / 2;
                return;
            }

            if (p->type != 11) {
                break;
            }
        }

        x++;

        if (x == hi) {
            x = lo;
        }
    }
}

void MapFindLowestEdgeLeftward(s32 a, s16* px, s16* py, s16* pz, s16 e, s16 f) {
    s32 i;
    s32 j;
    s32 x;
    u16 n;
    MapCell* q;

    n = f - e;
    x = e + GetRandom() % (-e + f);

    for (i = 0; i < n; i++) {
        for (j = gMapRows - 1; j >= 0; j--) {
            q = MapGetCell(x, j);

            if (q->type == a) {
                *px = x;
                *py = j;
                *pz = (q->upperZ >> 8) / 16;
                return;
            }

            if (q->type != 11) {
                break;
            }
        }

        x = x > e ? x - 1 : f - 1;
    }
}

u8 MapFindSpanBelowPlatforms(s16* a, s16* b, s16* c, s16* d) {
    u16 x1 = 0;
    u16 y1 = 0;
    u16 x2 = 0;
    u16 y2 = 0;
    s32 z1 = 0;
    s32 z2 = 0;
    s32 found = 0;
    s32 x;
    s32 y;
    MapCell* p;

    for (x = 0; x < gMapCols; x++) {
        for (y = gMapRows - 1; y >= 0; y--) {
            p = MapGetCell((s16)x, (s16)y);

            if (p->type == 3) {
                x1 = x;
                y1 = y;
                z1 = p->upperZ;
                found = 1;
                break;
            }

            if (p->type != 11) {
                break;
            }
        }

        if (found != 0) {
            break;
        }
    }

    found = 0;

    for (x = gMapCols - 1; x >= 0; x--) {
        for (y = gMapRows - 1; y >= 0; y--) {
            p = MapGetCell((s16)x, (s16)y);

            if (p->type == 5) {
                x2 = x + 1;
                y2 = y;
                z2 = p->upperZ;
                found = 1;
                break;
            }

            if (p->type != 11) {
                break;
            }
        }

        if (found != 0) {
            break;
        }
    }

    if ((s16)y1 <= gMapRows - gMapRows / 4 &&
        (s16)y2 <= gMapRows - gMapRows / 4 && (s16)x2 - (s16)x1 > 4) {
        *a = x1;
        *b = x2;

        if (z1 > z2) {
            *d = z1 / 16 >> 8;
            *c = y1;
            return 1;
        }

        *d = z2 / 16 >> 8;
        *c = y2;
        return 2;
    }

    return 0;
}

void func_080E3EFC(void) {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    s16 v;

    d = gMapCols / 2;
    b = gMapRows / 4;
    d = gMapCols - d;
    a = gMapCols;
    MapSetPlatform(0, d, a, 0);
    MapTracePlatformLeftToRight(0, d, a, b, 2);
    MapFindLowestEdgeLeftward(5, &a, &b, &c, 0, gMapCols);
    v = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
    MapSetPlatform(1, 0, a + 1, v + c);
    MapTracePlatformRightToLeft(1, 0, a + 1, v + b, 0);
}

void func_080E3FD4(void) {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    s16 t;
    s16 v;
    s32 k;

    t = GetRandom() % (gMapCols - 7) + 4;
    a = GetRandom() % (gMapCols - t - 3) + 2;
    d = a + t;
    b = gMapRows / 4;
    MapSetPlatform(0, a, d, 0);
    MapTracePlatformLeftToRight(0, a, d, b, k = 0);

    if (GetRandom() % 100 < 50) {
        MapFindLowestEdgeRightward(3, &a, &b, &c, k, gMapCols);
        v = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(1, a, gMapCols, v + c);
        MapTracePlatformLeftToRight(1, a, gMapCols, v + b, k);
        MapFindLowestEdgeLeftward(5, &d, &b, &c, k, gMapCols);
        v = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(2, 0, d + 1, v + c);
        MapTracePlatformRightToLeft(2, 0, d + 1, v + b, k);
    } else {
        MapFindLowestEdgeLeftward(5, &d, &b, &c, k, gMapCols);
        v = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(1, 0, d + 1, v + c);
        MapTracePlatformRightToLeft(1, 0, d + 1, v + b, k);
        MapFindLowestEdgeRightward(3, &a, &b, &c, k, gMapCols);
        v = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(2, a, gMapCols, v + c);
        MapTracePlatformLeftToRight(2, a, gMapCols, v + b, k);
    }
}

void func_080E4244(void) {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    s16 t;
    s16 v;

    t = GetRandom() % (gMapCols - 9) + 6;
    a = (gMapCols - t) / 2;
    d = a + t;
    b = gMapRows / 4;
    MapSetPlatform(0, a, d, 0);
    MapTracePlatformLeftToRight(0, a, d, b, 2);

    if (GetRandom() % 100 < 50) {
        MapFindLowestEdgeRightward(3, &a, &b, &c, 0, gMapCols);
        v = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1) + 10;
        MapSetPlatform(1, a, gMapCols, v + c);
        MapTracePlatformLeftToRight(1, a, gMapCols, v + b, 2);
        MapFindLowestEdgeLeftward(5, &d, &b, &c, 0, gMapCols);
        v = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(2, 0, d + 1, v + c);
        MapTracePlatformRightToLeft(2, 0, d + 1, v + b, 2);
    } else {
        MapFindLowestEdgeLeftward(5, &d, &b, &c, 0, gMapCols);
        v = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1) + 10;
        MapSetPlatform(1, 0, d + 1, v + c);
        MapTracePlatformRightToLeft(1, 0, d + 1, v + b, 2);
        MapFindLowestEdgeRightward(3, &a, &b, &c, 0, gMapCols);
        v = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(2, a, gMapCols, v + c);
        MapTracePlatformLeftToRight(2, a, gMapCols, v + b, 2);
    }
}

void func_080E44A8(void) {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    s16 t;
    s16 v;

    t = GetRandom() % (gMapCols - 9) + 6;
    a = (gMapCols - t) / 2;
    d = a + t;
    b = gMapRows / 4;
    MapSetPlatform(0, a, d, 0);
    MapTracePlatformLeftToRight(0, a, d, b, 3);

    if (GetRandom() % 100 < 50) {
        MapFindLowestEdgeRightward(3, &a, &b, &c, 0, gMapCols);
        v = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(1, a, gMapCols, v + c);
        MapTracePlatformLeftToRight(1, a, gMapCols, v + b, 3);
        MapFindLowestEdgeLeftward(5, &d, &b, &c, 0, gMapCols);
        v = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(2, 0, d + 1, v + c);
        MapTracePlatformRightToLeft(2, 0, d + 1, v + b, 3);
    } else {
        MapFindLowestEdgeLeftward(5, &d, &b, &c, 0, gMapCols);
        v = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(1, 0, d + 1, v + c);
        MapTracePlatformRightToLeft(1, 0, d + 1, v + b, 3);
        MapFindLowestEdgeRightward(3, &a, &b, &c, 0, gMapCols);
        v = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(2, a, gMapCols, v + c);
        MapTracePlatformLeftToRight(2, a, gMapCols, v + b, 3);
    }
}

void func_080E470C(void) {
    s16 a;
    s16 b;
    s16 c;
    s16 t;
    s16 d;
    s16 v;
    s32 k;

    t = (gMapCols * 5) / 8;
    a = (gMapCols - t) / 2;
    d = a + t;
    b = gMapRows / 4;
    MapSetPlatform(0, a, d, 0);
    MapTracePlatformLeftToRight(0, a, d, b, k = 3);
    MapFindLowestEdgeRightward(3, &a, &b, &c, 0, gMapCols);
    v = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
    MapSetPlatform(1, 0, gMapCols, v + c);
    MapTracePlatformOutward(1, 0, gMapCols, a, v + b, k);
}

void MapAddLowerPlatforms(u8 a, u8 b) {
    s32 i;

    for (i = a; i < b; i++) {
        s16 p;
        s16 q;
        s16 r;
        s16 s;
        s16 t;

        switch (MapFindSpanBelowPlatforms(&p, &q, &r, &s)) {
        case 1:
            t = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
            MapSetPlatform(i, p, q, t + s);
            MapTracePlatformLeftToRight(i, p, q, t + r, 0);
            break;
        case 2:
            t = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
            MapSetPlatform(i, p, q, t + s);
            MapTracePlatformRightToLeft(i, p, q, t + r, 0);
            break;
        default:
            return;
        }
    }
}

void MapGenerateLayout(void) {
    switch (gMapForm.layout) {
    case 0:
        MapSetPlatform(0, 0, gMapCols, 0);
        MapTracePlatformLeftToRight(0, 0, gMapCols, gMapRows / 4, 0);
        break;
    case 1:
        func_080E3EFC();
        break;
    case 2:
        func_080E3FD4();
        break;
    case 4:
        func_080E4244();
        MapAddLowerPlatforms(3, 4);
        break;
    case 5:
        func_080E44A8();
        MapAddLowerPlatforms(3, 4);
        break;
    case 6:
        func_080E470C();
        break;
    case 7:
        MapSetPlatform(0, 0, gMapCols, 0);
        MapTracePlatformLeftToRight(0, 0, gMapCols, gMapRows / 4, 3);
        MapAddLowerPlatforms(1, 12);
        break;
    case 3:
    default:
        func_080E3FD4();
        MapAddLowerPlatforms(3, 12);
        break;
    }
}

void MapGenerateRoom(u16 a, u16 b) {
    s32 i;
    s32 n;
    void** p;

    gMapRoomDef = gMapRoomDefs[gMapFloorState.world];
    gMapCols = a;
    gMapRows = b;
    p = &gMapBgBuffer;
    *p = EwramAlloc(0x1800);

    if (gGameState.fieldResume == 0) {
        gMapCells = EwramAlloc(sizeof(MapCell) * 0xC00);
        gMapPlatforms = EwramAlloc(0x120);
        gMapDoors = EwramAlloc(sizeof(MapDoor) * 4);
        n = gMapCols * gMapRows;

        for (i = 0; i < n; i++) {
            gMapCells[i].flags = 0;
            gMapCells[i].type = 11;
            gMapCells[i].bg3Piece = 7;
            gMapCells[i].bg2Piece = 0;
            gMapCells[i].bg1Piece = 0;
            gMapCells[i].bg3Map = 0;
            gMapCells[i].bg2Map = 0;
            gMapCells[i].bg1Map = 0;
        }

        for (i = 0; i < 12; i++) {
            gMapPlatforms[i].left = 0;
            gMapPlatforms[i].right = 0;
            gMapPlatforms[i].z = 0x100000;
            gMapPlatforms[i].hasStairs = 0;
            gMapPlatforms[i].x = 0;
            gMapPlatforms[i].y = 0;
            gMapPlatforms[i].spotType = 11;
            gMapPlatforms[i].spotUpperZ = -0x100000;
            gMapPlatforms[i].spotLowerZ = 0x100000;
        }

        MapGenerateLayout();
        MapFillOutlineCells();
        MapComputeCellHeights();
        MapComputeRowBounds();
        MapMarkCellEdges();
        func_080E13B0();
        MapAssignCellPieces();
        MapAssignBg1Pieces();
        MapPlacePlatformStairs();
        MapPlaceDoors();
    }

    gMapRoomState->topRow = gMapTopRow;
    gMapRoomState->bottomRow = gMapBottomRow;
}

void MapFreeRoom(void) {
    EwramFree(gMapBgBuffer);

    if (gGameState.fieldResume == 0) {
        EwramFree(gMapCells);
        EwramFree(gMapPlatforms);
        EwramFree(gMapDoors);
    }
}

void MapDrawBgs(s16 x, s16 y) {
    s16 x0;
    u16* p0;
    u16* p1;
    u16* p2;
    s16 yy;
    s32 i;

    p0 = gMapBgBuffer;
    p1 = (u16*)((u8*)gMapBgBuffer + 0x800);
    p2 = (u16*)((u8*)gMapBgBuffer + 0x1000);
    x0 = x - 1;
    yy = y - 1;

    for (i = 0; i < 32; i++) {
        s16 v;
        s16 m;
        s16 ya;
        s16 xx;
        s32 j;

        v = (yy < 0) ? (yy - 8) / 2 : yy / 2;

        m = yy % 2;
        ya = yy & 31;
        xx = x0;

        for (j = 0; j < 32; j++) {
            MapCell* e;
            s16 c;
            s16 n;
            s16 xa;

            if (xx < 0) {
                c = (xx - 8) / 4;
            } else {
                c = xx / 4;
            }

            n = xx % 4;
            xa = xx & 31;
            e = MapGetCell(c, v);

            if (e != NULL) {
                p0[ya * 32 + xa] = e->bg3Map[m * 32 + n];

                if (e->bg2Map != NULL) {
                    p1[ya * 32 + xa] = e->bg2Map[m * 32 + n];
                } else {
                    p1[ya * 32 + xa] = 0;
                }

                if (e->bg1Map != NULL) {
                    p2[ya * 32 + xa] = e->bg1Map[m * 32 + n];
                } else {
                    p2[ya * 32 + xa] = 0;
                }
            } else {
                p0[ya * 32 + xa] = 0;
                p1[ya * 32 + xa] = gMapRoomDef->map2[0x340];
                p2[ya * 32 + xa] = gMapRoomDef->map[0x110];
            }

            xx++;
        }

        yy++;
    }

    RequestDma3Copy(p0, GetBgScreenBase(3), 0x800);
    RequestDma3Copy(p1, GetBgScreenBase(2), 0x800);
    RequestDma3Copy(p2, GetBgScreenBase(1), 0x800);
}

void MapDrawBg1(s32 x, s32 y) {
    s16 x0;
    u16* dst;
    s16 yy;
    s32 i;

    dst = (u16*)((u8*)gMapBgBuffer + 0x1000);
    x0 = x;
    x0--;
    yy = y;
    yy--;

    for (i = 0; i < 32; i++) {
        s16 v;
        s16 m;
        s16 ya;
        s16 xx;
        s32 j;

        v = (yy < 0) ? (yy - 8) / 2 : yy / 2;

        m = yy % 2;
        ya = yy & 31;
        xx = x0;

        for (j = 0; j < 32; j++) {
            MapCell* e;
            s16 c;
            s16 n;
            s16 xa;

            if (xx < 0) {
                c = (xx - 8) / 4;
            } else {
                c = xx / 4;
            }

            n = xx % 4;
            xa = xx & 31;
            e = MapGetCell(c, v);

            if (e != NULL) {
                if (e->bg1Map != NULL) {
                    dst[ya * 32 + xa] = e->bg1Map[m * 32 + n];
                } else {
                    dst[ya * 32 + xa] = 0;
                }
            } else {
                dst[ya * 32 + xa] = gMapRoomDef->map[0x110];
            }

            xx++;
        }

        yy++;
    }

    RequestDma3Copy(dst, GetBgScreenBase(1), 0x800);
}

void MapBuildBgColumn(u16* a, u16* b, u16* c, s16 d, s16 e) {
    MapCell* cell;
    s16 hx;
    s16 mx;
    s16 hy;
    s16 my;
    s32 i;

    hx = (d < 0) ? (d - 8) / 4 : d / 4;
    mx = d % 4;

    for (i = 0; i < 32; i++) {
        hy = (e < 0) ? (e - 8) / 2 : e / 2;
        my = e % 2;
        cell = MapGetCell(hx, hy);

        if (cell != NULL) {
            a[i] = cell->bg3Map[my * 32 + mx];

            if (cell->bg2Map != NULL) {
                b[i] = cell->bg2Map[my * 32 + mx];
            } else {
                b[i] = 0;
            }

            if (cell->bg1Map != NULL) {
                c[i] = cell->bg1Map[my * 32 + mx];
            } else {
                c[i] = 0;
            }
        } else {
            a[i] = 0;
            b[i] = gMapRoomDef->map2[0x340];
            c[i] = gMapRoomDef->map[0x110];
        }

        e++;
    }
}

void MapDrawBgColumn(void* p, s16 a, s16 b) {
    void* q = (u8*)p + 0x40;
    void* r = (u8*)p + 0x80;

    MapBuildBgColumn(p, q, r, a, b);
    RequestTilemapStripCopy(p, GetBgScreenBase(3), a, b, 1);
    RequestTilemapStripCopy(q, GetBgScreenBase(2), a, b, 1);
    RequestTilemapStripCopy(r, GetBgScreenBase(1), a, b, 1);
}

void MapBuildBgRow(u16* a, u16* b, u16* c, s16 d, s16 e) {
    MapCell* cell;
    s16 hx;
    s16 mx;
    s16 hy;
    s16 my;
    s32 i;

    hy = (e < 0) ? (e - 8) / 2 : e / 2;
    my = e % 2;

    for (i = 0; i < 32; i++) {
        if (d < 0) {
            hx = (d - 8) / 4;
        } else {
            hx = d / 4;
        }

        mx = d % 4;
        cell = MapGetCell(hx, hy);

        if (cell != NULL) {
            a[i] = cell->bg3Map[my * 32 + mx];

            if (cell->bg2Map != NULL) {
                b[i] = cell->bg2Map[my * 32 + mx];
            } else {
                b[i] = 0;
            }

            if (cell->bg1Map != NULL) {
                c[i] = cell->bg1Map[my * 32 + mx];
            } else {
                c[i] = 0;
            }
        } else {
            a[i] = 0;
            b[i] = gMapRoomDef->map2[0x340];
            c[i] = gMapRoomDef->map[0x110];
        }

        d++;
    }
}

void MapDrawBgRow(void* p, s16 a, s16 b) {
    void* q = (u8*)p + 0x40;
    void* r = (u8*)p + 0x80;

    MapBuildBgRow(p, q, r, a, b);
    RequestTilemapStripCopy(p, GetBgScreenBase(3), a, b, 0);
    RequestTilemapStripCopy(q, GetBgScreenBase(2), a, b, 0);
    RequestTilemapStripCopy(r, GetBgScreenBase(1), a, b, 0);
}

u8 MapPickFreeFloorPos(FldPos* a, s32* b) {
    u16 h;
    u16 x;
    u16 y;
    s32 i;
    s32 j;

    h = gMapBottomRow - gMapTopRow;
    x = GetRandom() % gMapCols;
    y = GetRandom() % h;

    for (i = 0; i < h; i++) {
        for (j = 0; j < gMapCols; j++) {
            u16 yy = y + gMapTopRow;

            if ((*(u32*)MapGetCell(x, yy) & 0xFF0340) == 0) {
                a->x = (x << 13) + 0x1000;
                *b = (yy << 12) + 0x800;
                return 1;
            }

            x++;
            x %= gMapCols;
        }

        y++;
        y %= h;
    }

    a->x = gFieldState->actor.fieldPosition.x;
    *b = gFieldState->actor.fieldPosition.y + gFieldState->actor.fieldPosition.ground;
    return 0;
}

u8 MapPickFreeFloorPosInView(FldPos* a, s32* b) {
    u16 w = 6;
    u16 h = 8;
    u16 x;
    u16 y;
    s32 i;
    s32 k;

    x = GetRandom() % w;
    y = GetRandom() % h;

    for (k = 0; k < h; k++) {
        s32 ty = (gFieldState->y / 16 >> 8) + 2;
        u16 yy = y + ty;

        for (i = 0; i < w; i++) {
            s32 tx = (gFieldState->x / 32 >> 8) + 1;
            u16 xx = x + tx;
            s32* q = &gFieldState->actor.fieldPosition.x;
            MapCell* e;

            if (q[0] < (xx * 32 + 80) << 8 && q[0] > (xx * 32 - 48) << 8 &&
                q[1] < (yy * 16 + 40) << 8 && q[1] > (yy * 16 - 24) << 8) {
                continue;
            }

            e = MapGetCell(xx, yy);

            if (e != NULL && (*(u32*)e & 0xFF0340) == 0) {
                a->x = (xx << 13) + 0x1000;
                *b = (yy << 12) + 0x800;
                return 1;
            }

            x++;
            x %= w;
        }

        y++;
        y %= h;
    }

    MapPickFreeFloorPos(a, b);
    return 0;
}

MapCell* MapCellAt(s16 x, s16 y) {
    return MapGetCell(x, y);
}

MapPlatform* GetMapPlatform(u8 a) {
    return &gMapPlatforms[a];
}

u8* GetMapRoomEvent(u8 a) {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        return (u8*)(gMapRoomDefs[gMapFloorState.world]->rikuEvents + a);
    }

    return (u8*)(gMapRoomDefs[gMapFloorState.world]->soraEvents + a);
}

void* GetMapBgBuffer(void) {
    return gMapBgBuffer;
}

void LoadMapForm(u8 a) {
    if (a != 0x10) {
        gMapForm = gUnk_0984D1F4[a];
    } else {
        gMapForm = gUnk_0984D1F4[GetRandom() % 15];
    }
}

u16 GetRandomMapWidth(void) {
    return gMapForm.minWidth + GetRandom() % (gMapForm.maxWidth - gMapForm.minWidth + 1);
}

MapDoor* MapGetDoor(u8 a) {
    return &gMapDoors[a];
}

MapCell* MapFixGetCell(s16 x, s16 y) {
    if (y < 0 || y >= gMapRoomState->rows || x < 0 || x >= gMapRoomState->cols) {
        return 0;
    }

    return &gMapFixCells[gMapRoomState->cols * y + x];
}

void MapFixLoadCellTypes(const u8* src) {
    s32 x;
    s32 y;

    for (y = 0; y < gMapRoomState->rows; y++) {
        for (x = 0; x < gMapRoomState->cols; x++) {
            MapCell* e = MapFixGetCell(x, y);

            e->type = src[gMapRoomState->cols * y + x];
            e->maskTable = GetCellMaskTable(e->type);

            switch (e->type) {
            case 0:
                e->upperZ = 0;
                e->lowerZ = 0;
                break;
            case 1:
            case 3:
            case 5:
                e->upperZ = 0;
                e->lowerZ = 0x100000;
                break;
            case 2:
            case 4:
            case 6:
                e->upperZ = -0x100000;
                e->lowerZ = 0;
                break;
            default:
                e->upperZ = -0x100000;
                e->lowerZ = 0x100000;
                break;
            }
        }
    }
}

void MapFixCreateGimmicks(void* a) {
    MapFixedGmk* q = a;
    MapGmkPlacement* e;
    FldPos v;
    s32 x;
    s32 n;

    if (q == NULL) {
        return;
    }

    e = gMapGmkPlacements;

    while (q->defIndex != 0xFF) {
        v.x = q->x;
        x = q->y;
        v.y = v.z = v.ground = 0;
        v.y = x;
        e->flags = GMK_FLAG_USED;
        n = q->defIndex;
        e->def = &gMapGmkDefs[n];
        e->pos = v;
        TaskCreate(&gFieldState->tasks, &gTaskDescMapGmk00, e);
        q++;
        e++;
    }

    if (gMapFloorState.room != MAP_ROOM_ENTRANCE_HALL) {
        return;
    }

    if ((gGameState.flags & GAME_FLAG_RIKU) || gGameState.floor != 0) {
        v.x = 0x18000;
        x = 0x11000;
    } else {
        v.x = 0x26000;
        x = 0x12000;
    }

    v.y = x;
    n = 0;
    v.ground = n;
    v.z = n;
    e->flags = n;
    e->def = &gMapGmk04Def;
    e->pos = v;
    TaskCreate(&gFieldState->tasks, gMapGmk04Def.desc, e);
    e++;

    if (GetProgressFloor() != 0) {
        if ((gGameState.flags & GAME_FLAG_RIKU) || gGameState.floor != 0) {
            v.x = 0x1F000;
            x = 0x14000;
        } else {
            v.x = 0x2D000;
            x = 0x15000;
        }

        v.y = x;
        n = 0;
        v.ground = n;
        v.z = n;
        e->flags = n;
        e->def = &gMapGmk06Def;
        e->pos = v;
        TaskCreate(&gFieldState->tasks, gMapGmk06Def.desc, e);
    }
}

void MapFixSnapCamera(void) {
    u16 sx;
    u16 sy;

    gFieldState->x = gFieldState->x2 - 0x7800;
    gFieldState->y = gFieldState->y2 - 0x6000;
    sx = (gFieldState->x / 8) >> 8;
    sy = (gFieldState->y / 8) >> 8;
    RedrawBgMapAt(3, sx, sy);
    RedrawBgMapAt(2, sx, sy);
    RedrawBgMapAt(1, sx, sy);
}

void MapFixInitCells(MapFixedDef* p) {
    s32 i;
    s32 n;

    gMapFixCells = EwramAlloc(sizeof(MapCell) * 0xC00);
    n = gMapRoomState->cols * gMapRoomState->rows;

    for (i = 0; i < n; i++) {
        gMapFixCells[i].flags = 0;
        gMapFixCells[i].type = 11;
        gMapFixCells[i].bg3Piece = 7;
        gMapFixCells[i].bg2Piece = 0;
        gMapFixCells[i].bg1Piece = 0;
        gMapFixCells[i].bg3Map = 0;
        gMapFixCells[i].bg2Map = 0;
        gMapFixCells[i].bg1Map = 0;
    }

    MapFixLoadCellTypes(p->cellTypes);
}

void MapFixFreeCells(void) {
    EwramFree(gMapFixCells);
}

MapCell* MapFixCellAt(s16 a, s16 b) {
    return MapFixGetCell(a, b);
}
