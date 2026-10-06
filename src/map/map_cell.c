/**
 * map_cell.c
 * Field Cells and Room Generation
 */

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
#include "map_room_tables.h"
#include "map_rooms.h"

#define MAP_PIECE_VARIANT_RANDOM 0xFF

MapRoomState* gMapRoomState EWRAM_COMMON(4);
MapFormDef gMapForm EWRAM_COMMON(8);
struct MapGmkPlacement* gMapGmkPlacements EWRAM_COMMON(4);

static MapCell* sMapCells;
static MapPlatform* sMapPlatforms;
static MapDoor* sMapDoors;
static u16 sMapCols;
static u16 sMapRows;
static u16 sMapTopRow;
static u16 sMapBottomRow;
static void* sMapBgBuffer;
static MapRoomDef* sMapRoomDef;
static MapCell* sMapFixCells;

s32 FieldGroundAt(s32 x, s32 y, s32 z) {
    MapCell* cell = FieldCellAt(x, y);
    s32 ground;

    if (cell == NULL) {
        return 0;
    }

    if (cell->upperZ < z) {
        if (cell->type == 4 || cell->type == 6) {
            if (MapCellMaskBitAt(cell, x, y)) {
                ground = cell->upperZ;
            } else {
                ground = cell->lowerZ;
            }
        } else {
            ground = cell->upperZ;
        }
    } else {
        if (cell->type == 3 || cell->type == 5) {
            if (MapCellMaskBitAt(cell, x, y)) {
                ground = cell->lowerZ;
            } else {
                ground = cell->upperZ;
            }
        } else {
            ground = cell->lowerZ;
        }
    }

    return ground;
}

s32 GetFldPosGround(FldPos* pos) {
    return FieldGroundAt(pos->x, pos->y + pos->ground, pos->ground);
}

s32 GetFldPosFloor(FldPos* pos) {
    return FieldGroundAt(pos->x, pos->y + pos->z, -0x100000);
}

void FldPosInitGround(FldPos* pos) {
    pos->ground = GetFldPosFloor(pos);
}

void FldPosPlaceAtCell(FldPos* pos, s16 x, s16 y, u8 w, u8 h) {
    pos->x = (x << 13) + (w << 12);
    pos->y = (y << 12) + (h << 11);
    pos->z = 0;
    pos->z = pos->ground = GetFldPosFloor(pos);
    pos->y -= pos->ground;
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

void FldPosPlaceOnFreeFloor(FldPos* pos) {
    MapPickFreeFloorPos(pos, &pos->y);
    pos->z = 0;
    pos->z = pos->ground = GetFldPosFloor(pos);
    pos->y -= pos->ground;
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

void MapSnapCamera() {
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

void MapUpdateCamera(s32 targetX, s32 targetY) {
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s16 sx;
    s16 sy;
    u8* buf;

    if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) == 0) {
        x = MapClampCameraX(targetX);
        y = MapClampCameraY(targetY);
    } else {
        x = targetX - 0x7800;
        y = targetY - 0x6000;
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
    buf = GetMapBgBuffer();

    if (dx > 0) {
        MapDrawBgColumn(buf, sx + 30, sy - 1);
    } else if (dx < 0) {
        MapDrawBgColumn(buf, sx - 1, sy - 1);
    }

    buf += 0xC0;

    if (dy > 0) {
        MapDrawBgRow(buf, sx - 1, sy + 20);
    } else if (dy < 0) {
        MapDrawBgRow(buf, sx - 1, sy - 1);
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
    gMapRoomState->attackActive = TRUE;
    gMapRoomState->attackX = x;
    gMapRoomState->attackY = y;
    gMapRoomState->attackZ = z;
}

u8 IsHitByMapAttack(FldPos* pos, s16 radius, s16 height) {
    if (!gMapRoomState->attackActive) {
        return FALSE;
    }

    if (gMapRoomState->flags & ROOM_FLAG_ATTACK_HIT) {
        return FALSE;
    }

    if (gMapRoomState->attackX - 0x1400 > pos->x + (radius << 8)) {
        return FALSE;
    }

    if (gMapRoomState->attackX + 0x1400 < pos->x - (radius << 8)) {
        return FALSE;
    }

    if (gMapRoomState->attackY - 0x1400 > pos->y + (radius << 8)) {
        return FALSE;
    }

    if (gMapRoomState->attackY + 0x1400 < pos->y - (radius << 8)) {
        return FALSE;
    }

    if (gMapRoomState->attackZ - 0x2000 > pos->z) {
        return FALSE;
    }

    if (gMapRoomState->attackZ + 0x800 < pos->z - (height << 8)) {
        return FALSE;
    }

    if (gMapRoomState->attackZ <= pos->ground) {
        return TRUE;
    }

    return FALSE;
}

u8 GetCurrentRoomCardValue() {
    return GetMapRoomCardValue(gMapFloorState.room);
}

s32 IsMapInterrupted() {
    if ((gFieldState->flags & (FIELD_FLAG_MENU_OPEN | FIELD_FLAG_ROOM_CREATE)) || (gMapRoomState->flags & ROOM_FLAG_SAVE_MENU_OPEN)) {
        return TRUE;
    }

    return FALSE;
}

s32 IsFldObjTalkTarget(FldObj* obj) {
    if (IsMessageWindowOpen()) {
        return FALSE;
    }

    if (gFieldState->flags & (FIELD_FLAG_FREEZE_PLAYER | FIELD_FLAG_ROOM_CREATE | FIELD_FLAG_PLAYER_JUMPING)) {
        return FALSE;
    }

    if (gMapRoomState->flags & (ROOM_FLAG_ENEMY_STRUCK | ROOM_FLAG_ATTACK_HIT)) {
        return FALSE;
    }

    if (gFieldState->actor.fieldPosition.z != gFieldState->actor.fieldPosition.ground) {
        return FALSE;
    }

    return gFieldState->lockonTarget == obj;
}

void MapFreezeBg1() {
    gMapRoomState->flags |= ROOM_FLAG_BG1_FROZEN;
}

void MapRestoreBg1() {
    MapFixedDef* fixedDef;
    MapRoomDef* roomDef;
    s16 x;
    s16 y;

    if ((s32)gMapRoomState->flags < 0) {
        fixedDef = gMapFixedDefs[4];
        LoadBgTiles(1, fixedDef->tiles2, fixedDef->tilesSize2);
        LoadBgPalette(1, fixedDef->palette, fixedDef->paletteSize);
        SetBgMapBlocks(1, fixedDef->map, fixedDef->mapWidth, fixedDef->mapHeight);
        gMapRoomState->flags &= ~ROOM_FLAG_BG1_FROZEN;
    } else {
        roomDef = gMapRoomDefs[gMapFloorState.world];
        LoadBgTiles(1, roomDef->tiles2, roomDef->tilesSize2);
        LoadBgPalette(1, roomDef->palette, roomDef->paletteSize);
        x = gFieldState->x >> 8;
        y = gFieldState->y >> 8;
        MapDrawBg1(x / 8, y / 8);
        SetBgScroll(1, (u16)x, (u16)y);
        gMapRoomState->flags &= ~ROOM_FLAG_BG1_FROZEN;
    }
}

FldObj* GetMapRoomDoor() {
    return gMapRoomState->door;
}

void RequestMapMode() {
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

void ReturnToMap(u8 returnToMenu) {
    if (returnToMenu != TRUE) {
        gGameState.mapMenuCursor = 0xFF;
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, 0xFF, 0x100);
    }

    RequestMapMode();
}

void InitFieldState() {
    gFieldState->x = 0;
    gFieldState->y = 0;
    gFieldState->x2 = 0;
    gFieldState->y2 = 0;
    gFieldState->tileCols = 32;
    gFieldState->tileRows = 32;
    gFieldState->lockonTarget = NULL;
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
    gMapRoomState->attackActive = FALSE;
    TaskPoolInit(&gMapRoomState->tasks, 1);
}

void CreateMapRndTask() {
    LoadMapRoomState(gMapRoomState, gMapFloorState.room);

    if (gMapRoomState->roomType == ROOM_TYPE_SLEEPING_DARKNESS) {
        gFieldState->flags |= FIELD_FLAG_NO_ENEMY_SPAWN;
    }

    TaskCreate(&gFieldState->tasks, &gTaskDescMapRnd, NULL);
}

void SpawnMapPlayer() {
    MapDoor* door;
    s32 x;
    s32 y;

    if (gMapFloorState.entrySide <= 3) {
        door = GetMapDoor(gMapFloorState.entrySide);
        x = (door->cellX << 5) + 16;
        y = (door->cellY << 4) + 10;

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
        TaskCreate(&gFieldState->tasks2, &gTaskDescFldRiku, NULL);
    } else {
        TaskCreate(&gFieldState->tasks2, &gTaskDescFldSora, NULL);
    }
}

void UpdateMapField() {
    if (gFieldState->lockonDelay > 0) {
        gFieldState->flags |= FIELD_FLAG_NO_LOCKON;
        gFieldState->lockonDelay--;
    } else {
        gFieldState->flags &= ~FIELD_FLAG_NO_LOCKON;
    }

    gMapRoomState->jumpGmkHeight = 0;
    TaskPoolUpdate(&gFieldState->tasks);
    gMapRoomState->attackActive = FALSE;

    if ((gFieldState->flags & FIELD_FLAG_FREEZE_PLAYER) == 0 && (gMapRoomState->flags & ROOM_FLAG_ENEMY_STRUCK) == 0) {
        TaskPoolUpdate(&gFieldState->tasks2);
    }

    if ((gFieldState->flags & FIELD_FLAG_FREEZE_ENEMIES) == 0) {
        TaskPoolUpdate(&gFieldState->tasks4);
    }

    TaskPoolUpdate(&gFieldState->tasks3);
    TaskPoolUpdate(&gFieldState->tasks5);
}

void DrawMapField() {
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

void DestroyMapField() {
    TaskPoolDestroy(&gFieldState->tasks);
    TaskPoolDestroy(&gFieldState->tasks2);
    TaskPoolDestroy(&gFieldState->tasks3);
    TaskPoolDestroy(&gFieldState->tasks5);
    TaskPoolDestroy(&gFieldState->tasks4);
    TaskPoolDestroy(&gMapRoomState->tasks);
}

MapCell* MapGetCell(s16 x, s16 y) {
    if (y < 0 || y >= sMapRows) {
        return NULL;
    }

    if (x < 0 || x >= sMapCols) {
        return NULL;
    }

    return &sMapCells[sMapCols * y + x];
}

void MapCellSetType(MapCell* cell, s32 type, s32 upperZ) {
    if (cell != NULL) {
        cell->type = type;
        cell->maskTable = GetCellMaskTable(type);
        cell->upperZ = upperZ;
    }
}

u8 FldPosHeightExceeds(FldPos* pos, u16 limit) {
    u16 height = (pos->ground - pos->z) >> 8;

    return height > limit * 16;
}

u8 GetRandomPieceVariant(u8 piece) {
    const u8* def = gMapCellBg2Pieces[piece];
    return GetRandom() % def[3];
}

void MapCellSetBg3Piece(MapCell* cell, s32 piece) {
    if (cell != NULL) {
        u16* base = sMapRoomDef->map3;
        const u8* def = gMapCellBg3Pieces[piece];
        u8 variant = GetRandom() % def[3];
        s32 col = ((variant & 7) + def[1]) * 4;
        s32 row = (variant >> 3) + def[2];
        cell->bg3Piece = piece;
        cell->bg3Map = base + (row * 64 + col);
    }
}

void MapCellSetBg2Piece(MapCell* cell, u8 piece, u8 variant) {
    if (cell != NULL) {
        const u8* def = gMapCellBg2Pieces[piece];
        u16* base;
        u16 offset;

        switch (def[0]) {
        case 1:
            base = sMapRoomDef->map2;
            break;
        case 0:
        default:
            base = sMapRoomDef->map3;
            break;
        }

        offset = ((variant & 7) + def[1]) * 4 + ((variant >> 3) + def[2]) * 64;

        if (cell->flags & MAP_CELL_FLAG_EDGE_LEFT) {
            offset = offset + def[3] * 4;
        }

        if (cell->flags & MAP_CELL_FLAG_EDGE_RIGHT) {
            offset = offset + def[3] * 8;
        }

        cell->bg2Piece = piece;
        cell->bg2Map = base + offset;
    }
}

void MapCellSetFloorBg3Piece(MapCell* cell) {
    if (cell->flags & 1) {
        MapCellSetBg3Piece(cell, 1);
    } else if (cell->flags & 2) {
        MapCellSetBg3Piece(cell, 2);
    } else {
        MapCellSetBg3Piece(cell, 0);
    }
}

void MapCellSetBg2EdgePiece(MapCell* cell, s32 piece) {
    u16* base;
    const u8* def;
    u8 variant;
    u16 off;
    u16 step;

    if (cell == NULL) {
        return;
    }

    if ((cell->flags & (MAP_CELL_FLAG_EDGE_LEFT | MAP_CELL_FLAG_EDGE_RIGHT)) == 0) {
        cell->bg2Piece = piece;
        return;
    }

    base = sMapRoomDef->map3;
    def = gMapCellBg2Pieces[piece];
    variant = GetRandom() % def[3];
    off = (variant % 8 + def[1]) * 4 + (variant / 8 + def[2]) * 64;

    if (cell->flags & MAP_CELL_FLAG_EDGE_RIGHT) {
        step = def[3] * 4;
        off += step;

        if (cell->flags & MAP_CELL_FLAG_EDGE_LEFT) {
            off += step;
        }
    }

    cell->bg2Piece = piece;
    cell->bg2Map = base + off;
}

void MapCellSetBg2CornerPiece(MapCell* cell, s32 piece) {
    const u8* def;
    u16* base;
    u16 off;

    if (cell == NULL) {
        return;
    }

    def = gMapCellBg2Pieces[piece];
    off = def[1] * 4 + def[2] * 64;
    base = sMapRoomDef->map2;

    switch (piece) {
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
        if (cell->flags & MAP_CELL_FLAG_EDGE_RIGHT) {
            off += def[3] * 4;
        }

        break;
    case 23:
    case 24:
    case 25:
    case 32:
    case 33:
    case 34:
        if (cell->flags & MAP_CELL_FLAG_EDGE_LEFT) {
            off += def[3] * 4;
        }

        break;
    }

    cell->bg2Piece = piece;
    cell->bg2Map = base + off;
}

void MapCellSetBg2PieceVariant(MapCell* cell, s32 piece, u8 variant) {
    if (cell != NULL) {
        u16* base = sMapRoomDef->map2;
        const u8* def = gMapCellBg2Pieces[piece];
        s32 offset;

        if (variant == MAP_PIECE_VARIANT_RANDOM) {
            variant = GetRandom() % def[3];
        }

        offset = ((variant & 7) + def[1]) * 4 + ((variant >> 3) + def[2]) * 64;
        cell->bg2Piece = piece;
        cell->bg2Map = base + offset;
    }
}

void MapSetCornerCellPieces(s16 x, s16 y, s32 bg3Piece, s32 bg2Piece) {
    MapCell* cell = MapGetCell(x, y);

    MapCellSetBg3Piece(cell, bg3Piece);
    MapCellSetBg2CornerPiece(cell, bg2Piece);
}

void MapBuildStairs(u16 x, u16 y) {
    MapCell* cell;
    u8 variant;
    s32 go;

    go = TRUE;

    while (go) {
        cell = MapGetCell(x, y);

        switch (cell->type) {
        case 3:
            MapGetCell(x, y - 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell(x - 1, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell(x - 1, y - 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            variant = GetRandomPieceVariant(38);
            cell->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(cell, 38, variant);
            y++;
            cell = MapGetCell(x, y);
            cell->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(cell, 39, variant);
            break;
        case 5:
            MapGetCell(x, y - 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell(x + 1, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell(x + 1, y - 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            variant = GetRandomPieceVariant(43);
            cell->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(cell, 43, variant);
            y++;
            cell = MapGetCell(x, y);
            cell->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(cell, 44, variant);
            break;
        case 8:
            cell->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(cell, 37, MAP_PIECE_VARIANT_RANDOM);
            break;
        case 9:
            cell->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(cell, 42, MAP_PIECE_VARIANT_RANDOM);
            break;
        case 4:
            MapGetCell(x, y + 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell(x + 1, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell(x + 1, y + 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            variant = GetRandomPieceVariant(40);
            cell->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(cell, 40, variant);
            cell = MapGetCell(x, y - 1);
            cell->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(cell, 41, variant);
            go = FALSE;
            break;
        case 6:
            MapGetCell(x, y + 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell(x - 1, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            MapGetCell(x - 1, y + 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
            variant = GetRandomPieceVariant(45);
            cell->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(cell, 45, variant);
            cell = MapGetCell(x, y - 1);
            cell->flags |= MAP_CELL_FLAG_STAIRS;
            MapCellSetBg2PieceVariant(cell, 46, variant);
            go = FALSE;
            break;
        }

        y++;
    }
}

void MapMarkJumpSpot(MapPlatform* platform) {
    s32 go = TRUE;
    u16 x = platform->x;
    u16 y = platform->y;

    while (go) {
        s16 cy = y;
        MapCell* cell = MapGetCell(x, cy);

        switch (cell->type) {
        case 4:
            MapGetCell(x, y + 1)->flags |= MAP_CELL_FLAG_JUMP_PAD;
            MapGetCell(x + 1, cy)->flags |= MAP_CELL_FLAG_JUMP_PAD;
            MapGetCell(x + 1, y + 1)->flags |= MAP_CELL_FLAG_JUMP_PAD;
            cell->flags |= MAP_CELL_FLAG_JUMP_PAD;
            platform->x = x + 1;
            platform->y = y + 1;
            go = FALSE;
            break;
        case 6:
            MapGetCell(x, y + 1)->flags |= MAP_CELL_FLAG_JUMP_PAD;
            MapGetCell(x - 1, cy)->flags |= MAP_CELL_FLAG_JUMP_PAD;
            MapGetCell(x - 1, y + 1)->flags |= MAP_CELL_FLAG_JUMP_PAD;
            cell->flags |= MAP_CELL_FLAG_JUMP_PAD;
            platform->x = x;
            platform->y = y + 1;
            go = FALSE;
            break;
        default:
            break;
        }

        y++;
    }
}

void MapFindPlatformStairs(MapPlatform* platform) {
    u16 x;
    u16 y;
    u16 rise;
    MapCell* cell;
    MapCell* top;

    x = platform->left;

    while (x < platform->right) {
        y = sMapTopRow;

        while (y < sMapBottomRow) {
            cell = MapGetCell(x, y);

            if (cell->type == 4 || cell->type == 6) {
                if (cell->upperZ != -0x100000 && platform->z == cell->lowerZ) {
                    rise = ((platform->z - cell->upperZ) >> 8) / 16;

                    if (FldPosHeightExceeds((FldPos*)cell, 3)) {
                        top = MapGetCell(x, y - rise);

                        if ((cell->flags & (MAP_CELL_FLAG_EDGE_LEFT | MAP_CELL_FLAG_EDGE_RIGHT | MAP_CELL_FLAG_CORNER)) == 0 && (top->flags & (MAP_CELL_FLAG_EDGE_LEFT | MAP_CELL_FLAG_EDGE_RIGHT | MAP_CELL_FLAG_CORNER)) == 0) {
                            if (!platform->hasStairs ||
                                (platform->spotUpperZ <= top->upperZ &&
                                 (platform->spotUpperZ < top->upperZ ||
                                  platform->left + GetRandom() % (platform->right - platform->left + 1) > x))) {
                                platform->hasStairs = TRUE;
                                platform->x = x;
                                platform->y = y - rise;
                                platform->spotType = top->type;
                                platform->spotUpperZ = top->upperZ;
                                platform->spotLowerZ = top->lowerZ;
                            }
                        } else if (!platform->hasStairs && platform->spotUpperZ <= top->upperZ &&
                                   (platform->spotUpperZ < top->upperZ ||
                                    platform->left + GetRandom() % (platform->right - platform->left + 1) > x)) {
                            platform->x = x;
                            platform->y = y - rise;
                            platform->spotType = top->type;
                            platform->spotUpperZ = top->upperZ;
                            platform->spotLowerZ = top->lowerZ;
                        }
                    }
                }
            }

            y++;
        }

        x++;
    }
}

void MapPlacePlatformStairs() {
    s32 i;

    for (i = 11; i >= 0; i--) {
        MapPlatform* platform = &sMapPlatforms[i];

        if (platform->z != 0x100000) {
            MapFindPlatformStairs(platform);
        }

        if (platform->hasStairs) {
            MapBuildStairs(platform->x, platform->y);
        } else if (platform->spotLowerZ != 0x100000) {
            MapMarkJumpSpot(platform);
        }
    }
}

s16 MapOutlineNextRowLeftToRight(u8 prevType, u8 type, s16 y) {
    switch (prevType) {
    case 2:
    case 6:
        if (type == 6) {
            y++;
        }

        break;
    case 4:
        if (type != 6) {
            y--;
        }

        break;
    case 1:
    case 3:
        if (type == 3) {
            y--;
        }

        break;
    case 5:
        if (type != 3) {
            y++;
        }

        break;
    }

    return y;
}

s16 MapOutlineNextRowRightToLeft(u8 prevType, u8 type, s16 y) {
    switch (prevType) {
    case 2:
    case 4:
        if (type == 4) {
            y += 1;
        }

        break;
    case 6:
        if (type != 4) {
            y -= 1;
        }

        break;
    case 1:
    case 5:
        if (type == 5) {
            y -= 1;
        }

        break;
    case 3:
        if (type != 5) {
            y += 1;
        }

        break;
    }

    return y;
}

void MapFillOutlineCells() {
    s32 i;
    s32 j;
    s32 dir;
    MapCell* cell;

    for (i = 0; i < sMapCols; i++) {
        dir = 10;

        for (j = 0; j < sMapRows; j++) {
            cell = MapGetCell(i, j);

            switch (cell->type) {
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
                    MapCellSetType(cell, dir, 0);
                }

                break;
            }
        }

        if (dir == 11) {
            for (j = 0; j < sMapRows; j++) {
                MapCellSetType(MapGetCell(i, j), 7, 0);
            }
        }
    }

    for (i = 0; i < sMapCols; i++) {
        dir = 10;

        for (j = sMapRows - 1; j >= 0; j--) {
            cell = MapGetCell(i, j);

            switch (cell->type) {
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
                    MapCellSetType(cell, dir, 0);
                }

                break;
            }
        }
    }
}

void MapMarkFloorVariants() {
    u16 y = sMapBottomRow;
    u16 n = y - sMapTopRow + 1;
    s32 j;

    for (j = 0; j < n; j++) {
        u16 x;

        for (x = 0; x < sMapCols; x++) {
            MapCell* cell = MapGetCell(x, y);
            s32 floorZ;
            s32 ok;
            s32 k;

            switch (cell->type) {
            case 0:
            case 1:
            case 3:
            case 5:
                floorZ = cell->upperZ;
                break;
            case 2:
            case 4:
            case 6:
                floorZ = cell->lowerZ;
                break;
            default:
                floorZ = 0x100000;
                break;
            }

            if (floorZ == 0x100000) {
                continue;
            }

            ok = TRUE;

            for (k = 11; k >= 0; k--) {
                if (sMapPlatforms[k].z != floorZ) {
                    if (sMapPlatforms[k].z != 0x100000) {
                        ok = FALSE;
                    }
                } else {
                    if (!ok) {
                        if (k % 2) {
                            cell->flags |= 2;
                        } else {
                            cell->flags |= 1;
                        }
                    }

                    break;
                }
            }
        }

        y--;
    }
}

void MapMarkCellEdges() {
    s32 x;
    s32 y;

    for (y = 0; y < sMapRows; y++) {
        for (x = 0; x < sMapCols - 1; x++) {
            MapCell* left = MapGetCell(x, y);
            MapCell* right = MapGetCell(x + 1, y);
            s32 flag = FALSE;

            switch (left->type) {
            case 0:
                if (right->type != 0 && right->type != 3 && right->type != 4 && right->type != 5 &&
                    right->type != 6) {
                    flag = TRUE;
                }

                break;
            case 6:
                if (right->type != 9) {
                    flag = TRUE;
                }

                break;
            case 3:
                if (right->type != 8) {
                    flag = TRUE;
                }

                break;
            case 4:
            case 5:
                if (right->type != 0) {
                    flag = TRUE;
                }

                break;
            case 8:
                if (right->type != 8 && right->type != 4) {
                    flag = TRUE;
                }

                break;
            case 9:
                if (right->type != 9 && right->type != 5) {
                    flag = TRUE;
                }

                break;
            case 1:
            case 2:
            case 7:
                if (left->type != right->type) {
                    flag = TRUE;
                }

                break;
            }

            if (flag) {
                left->flags |= MAP_CELL_FLAG_EDGE_RIGHT;
                right->flags |= MAP_CELL_FLAG_EDGE_LEFT;
            }

            switch (left->type) {
            case 4:
                if (MapGetCell(x + 1, y - 1)->type == 2) {
                    left->flags |= MAP_CELL_FLAG_EDGE_RIGHT;
                }

                break;
            case 6:
                if (MapGetCell(x - 1, y - 1)->type == 2) {
                    left->flags |= MAP_CELL_FLAG_EDGE_LEFT;
                }

                break;
            case 3:
                if (MapGetCell(x - 1, y + 1)->type == 1) {
                    left->flags |= MAP_CELL_FLAG_EDGE_LEFT;
                }

                break;
            case 5:
                if (MapGetCell(x + 1, y + 1)->type == 1) {
                    left->flags |= MAP_CELL_FLAG_EDGE_RIGHT;
                }

                break;
            }
        }
    }
}

void MapAssignCellPieces() {
    s32 i;
    s32 j;
    MapCell* cell;
    u8 variant;

    for (i = 0; i < sMapCols; i++) {
        for (j = 0; j < sMapRows; j++) {
            cell = MapGetCell(i, j);

            if (cell->bg3Piece != 7) {
                continue;
            }

            switch (cell->type) {
            case 0:
                MapCellSetFloorBg3Piece(cell);
                break;
            case 7:
                MapCellSetBg3Piece(cell, 3);
                MapCellSetBg2EdgePiece(cell, 4);
                break;
            case 8:
                MapCellSetBg3Piece(cell, 4);
                MapCellSetBg2EdgePiece(cell, 5);
                break;
            case 9:
                MapCellSetBg3Piece(cell, 5);
                MapCellSetBg2EdgePiece(cell, 6);
                break;
            case 2:
                variant = GetRandomPieceVariant(10);

                if (FldPosHeightExceeds((FldPos*)cell, 3)) {
                    MapCellSetFloorBg3Piece(cell);
                    MapCellSetBg2Piece(cell, 10, variant);
                    MapCellSetBg3Piece(MapGetCell(i, j - 1), 3);
                    MapCellSetBg2Piece(MapGetCell(i, j - 1), 11, variant);
                } else {
                    MapCellSetFloorBg3Piece(cell);
                    MapCellSetBg2Piece(cell, 12, variant);
                }

                break;
            case 1:
                variant = GetRandomPieceVariant(7);
                MapCellSetBg2Piece(MapGetCell(i, j - 1), 48, variant);
                MapCellSetFloorBg3Piece(cell);

                if (FldPosHeightExceeds((FldPos*)cell, 3)) {
                    MapCellSetBg2Piece(cell, 7, variant);
                    MapCellSetBg3Piece(MapGetCell(i, j + 1), 3);
                    MapCellSetBg2Piece(MapGetCell(i, j + 1), 8, variant);
                } else {
                    MapCellSetBg2Piece(cell, 9, variant);
                }

                break;
            case 3:
                if (cell->flags & MAP_CELL_FLAG_CORNER) {
                    MapCellSetFloorBg3Piece(cell);
                    MapCellSetBg2CornerPiece(cell, 23);

                    if (FldPosHeightExceeds((FldPos*)cell, 2)) {
                        MapSetCornerCellPieces(i, j + 1, 4, 24);
                    } else {
                        MapSetCornerCellPieces(i, j + 1, 4, 25);

                        if ((MapGetCell(i, j + 2)->flags & MAP_CELL_FLAG_CORNER) == 0) {
                            MapCellSetFloorBg3Piece(MapGetCell(i, j + 2));
                            MapCellSetBg2Piece(MapGetCell(i, j + 2), 15, 0);
                        }
                    }
                } else {
                    variant = GetRandomPieceVariant(13);
                    MapCellSetFloorBg3Piece(cell);
                    MapCellSetBg2Piece(cell, 13, variant);
                    MapCellSetBg2Piece(MapGetCell(i, j - 1), 47, variant);

                    if (FldPosHeightExceeds((FldPos*)cell, 2)) {
                        MapCellSetBg3Piece(MapGetCell(i, j + 1), 4);
                        MapCellSetBg2Piece(MapGetCell(i, j + 1), 14, variant);
                    } else if ((MapGetCell(i, j + 2)->flags & MAP_CELL_FLAG_CORNER) == 0) {
                        MapCellSetBg3Piece(MapGetCell(i, j + 1), 4);
                        MapCellSetBg2Piece(MapGetCell(i, j + 1), 17, variant);
                        MapCellSetFloorBg3Piece(MapGetCell(i, j + 2));
                        MapCellSetBg2Piece(MapGetCell(i, j + 2), 15, variant);
                    }
                }

                break;
            case 5:
                if (cell->flags & MAP_CELL_FLAG_CORNER) {
                    MapCellSetFloorBg3Piece(cell);
                    MapCellSetBg2CornerPiece(cell, 29);

                    if (FldPosHeightExceeds((FldPos*)cell, 2)) {
                        MapSetCornerCellPieces(i, j + 1, 5, 30);
                    } else {
                        MapSetCornerCellPieces(i, j + 1, 5, 31);

                        if ((MapGetCell(i, j + 2)->flags & MAP_CELL_FLAG_CORNER) == 0) {
                            MapCellSetFloorBg3Piece(MapGetCell(i, j + 2));
                            MapCellSetBg2Piece(MapGetCell(i, j + 2), 20, 0);
                        }
                    }
                } else {
                    variant = GetRandomPieceVariant(18);
                    MapCellSetFloorBg3Piece(cell);
                    MapCellSetBg2Piece(cell, 18, variant);
                    MapCellSetBg2Piece(MapGetCell(i, j - 1), 49, variant);

                    if (FldPosHeightExceeds((FldPos*)cell, 2)) {
                        MapCellSetBg3Piece(MapGetCell(i, j + 1), 5);
                        MapCellSetBg2Piece(MapGetCell(i, j + 1), 19, variant);
                    } else if ((MapGetCell(i, j + 2)->flags & MAP_CELL_FLAG_CORNER) == 0) {
                        MapCellSetBg3Piece(MapGetCell(i, j + 1), 5);
                        MapCellSetBg2Piece(MapGetCell(i, j + 1), 22, variant);
                        MapCellSetFloorBg3Piece(MapGetCell(i, j + 2));
                        MapCellSetBg2Piece(MapGetCell(i, j + 2), 20, variant);
                    }
                }

                break;
            case 4:
                if (cell->flags & MAP_CELL_FLAG_CORNER) {
                    MapCellSetFloorBg3Piece(cell);
                    MapCellSetBg2CornerPiece(cell, 26);

                    if (FldPosHeightExceeds((FldPos*)cell, 2)) {
                        MapSetCornerCellPieces(i, j - 1, 4, 27);
                    } else if ((MapGetCell(i, j - 2)->flags & MAP_CELL_FLAG_CORNER) == 0) {
                        MapSetCornerCellPieces(i, j - 1, 4, 28);
                    } else {
                        MapSetCornerCellPieces(i, j - 1, 4, 35);
                    }
                } else {
                    variant = GetRandomPieceVariant(15);
                    MapCellSetFloorBg3Piece(cell);
                    MapCellSetBg2Piece(cell, 15, variant);

                    if (FldPosHeightExceeds((FldPos*)cell, 2)) {
                        MapCellSetBg3Piece(MapGetCell(i, j - 1), 4);
                        MapCellSetBg2Piece(MapGetCell(i, j - 1), 16, variant);
                    }
                }

                break;
            case 6:
                if (cell->flags & MAP_CELL_FLAG_CORNER) {
                    MapCellSetFloorBg3Piece(cell);
                    MapCellSetBg2CornerPiece(cell, 32);

                    if (FldPosHeightExceeds((FldPos*)cell, 2)) {
                        MapSetCornerCellPieces(i, j - 1, 5, 33);
                    } else if ((MapGetCell(i, j - 2)->flags & MAP_CELL_FLAG_CORNER) == 0) {
                        MapSetCornerCellPieces(i, j - 1, 5, 34);
                    } else {
                        MapSetCornerCellPieces(i, j - 1, 5, 36);
                    }
                } else {
                    variant = GetRandomPieceVariant(20);
                    MapCellSetFloorBg3Piece(cell);
                    MapCellSetBg2Piece(cell, 20, variant);

                    if (FldPosHeightExceeds((FldPos*)cell, 2)) {
                        MapCellSetBg3Piece(MapGetCell(i, j - 1), 5);
                        MapCellSetBg2Piece(MapGetCell(i, j - 1), 21, variant);
                    }
                }

                break;
            }
        }
    }
}

void MapCellSetBg1Piece(s16 x, s16 y, u8 piece) {
    MapCell* cell = MapGetCell(x, y);

    if (cell != NULL) {
        u16* base = sMapRoomDef->map;
        const u8* def = gMapCellBg1Pieces[piece];
        s32 offset = def[1] * 4 + def[2] * 64;
        cell->bg1Piece = piece;
        cell->bg1Map = base + offset;
    }
}

u8 MapCellIsUnbounded(s16 x, s16 y) {
    MapCell* cell = MapGetCell(x, y);

    if (cell == NULL || cell->upperZ == -0x100000 || cell->lowerZ == 0x100000) {
        return TRUE;
    }

    return FALSE;
}

u8 MapCellHasType(s16 x, s16 y, u8 type) {
    MapCell* cell = MapGetCell(x, y);

    if (cell != NULL && cell->type == type) {
        return TRUE;
    }

    return FALSE;
}

void MapAssignWallTopPieces(s16 x, s16 y) {
    MapCell* cell = MapGetCell(x, y + 7);

    if (cell->upperZ == -0x100000) {
        switch (cell->type) {
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
    MapCell* cell = MapGetCell(x, y);

    if (cell->lowerZ == 0x100000 && cell->bg1Piece == 0) {
        switch (cell->type) {
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

void MapAssignRightBorderPiece(s16 y) {
    s16 x = sMapCols - 1;
    MapCell* cell = MapGetCell(x, y);

    switch (cell->bg1Piece) {
    case 12:
        MapCellSetBg1Piece(x, y, 17);
        break;
    case 8:
        MapCellSetBg1Piece(x, y, 15);
        break;
    case 0:
    case 9:
    case 13:
    case 20:
    case 21:
    case 24:
    case 25:
        MapCellSetBg1Piece(x, y, 3);
        break;
    }
}

void MapAssignBg1Pieces() {
    s32 i;
    s32 j;

    for (i = 0; i < sMapCols; i++) {
        for (j = 0; j < sMapRows; j++) {
            MapAssignWallTopPieces(i, j);
            MapAssignLedgePieces(i, j);
        }
    }

    for (j = 0; j < sMapRows; j++) {
        MapAssignLeftBorderPiece(j);
        MapAssignRightBorderPiece(j);
    }
}

void MapComputeCellHeights() {
    s16 i;
    s16 j;
    s32 z;
    MapCell* cell;

    for (i = 0; i < sMapCols; i++) {
        z = 0x100000;

        for (j = sMapRows - 1; j >= 0; j--) {
            cell = MapGetCell(i, j);

            switch (cell->type) {
            case 1:
            case 3:
            case 5:
                cell->lowerZ = z;
                z = cell->upperZ;
                break;
            case 0:
                cell->upperZ = z;
                cell->lowerZ = z;
                break;
            case 2:
            case 4:
            case 6:
                cell->lowerZ = cell->upperZ;
                break;
            case 7:
            case 8:
            case 9:
            default:
                cell->lowerZ = z;
                break;
            }
        }
    }

    for (i = 0; i < sMapCols; i++) {
        z = -0x100000;

        for (j = 0; j < sMapRows; j++) {
            cell = MapGetCell(i, j);

            switch (cell->type) {
            case 1:
            case 3:
            case 5:
                z = cell->upperZ;
                break;
            case 2:
            case 4:
            case 6:
            case 7:
            case 8:
            case 9:
                cell->upperZ = z;
                break;
            }
        }
    }
}

void MapPlaceDoorOnPlatform(MapPlatform* platform, s32 side) {
    u8 doorSide;
    s32 i;
    u16 x;
    u16 y;
    u16 width;
    MapDoor* door;
    MapCell* cell;

    doorSide = side;
    door = GetMapDoor(doorSide);

    if (!(door->flags & DOOR_FLAG_PRESENT)) {
        return;
    }

    width = platform->right - platform->left;

    if (doorSide == 0) {
        x = platform->left + width * 5 / 8 + GetRandom() % (width >> 2);

        for (i = 0; i < width; i++) {
            for (y = sMapTopRow; y <= sMapBottomRow; y++) {
                cell = MapGetCell(x, y);

                if (cell->type == 6 && cell->lowerZ == platform->z && cell->upperZ == -0x100000 && (cell->flags & MAP_CELL_FLAG_STAIRS) == 0) {
                    door->cellX = x;
                    door->cellY = y;
                    cell->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    cell->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    MapGetCell(x, y + 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x - 1, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x - 1, y + 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x, y - 1)->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    MapGetCell(x, y - 2)->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    MapGetCell(x, y - 3)->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    return;
                }
            }

            x = x < platform->right - 1 ? x + 1 : platform->left;
        }
    }

    if (doorSide == 2) {
        x = platform->left + width * 5 / 8 + GetRandom() % (width >> 2);

        for (i = 0; i < width; i++) {
            for (y = sMapTopRow; y <= sMapBottomRow; y++) {
                cell = MapGetCell(x, y);

                if (cell->type == 3 && cell->upperZ == platform->z && cell->lowerZ == 0x100000 && (cell->flags & MAP_CELL_FLAG_STAIRS) == 0) {
                    door->cellX = x;
                    door->cellY = y;
                    MapGetCell(x, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x, y - 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x - 1, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x - 1, y - 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    return;
                }
            }

            x = x < platform->right - 1 ? x + 1 : platform->left;
        }
    }

    if (doorSide == 1) {
        x = platform->left + width * 3 / 8 - GetRandom() % (width >> 2);

        for (i = 0; i < width; i++) {
            for (y = sMapTopRow; y <= sMapBottomRow; y++) {
                cell = MapGetCell(x, y);

                if (cell->type == 5 && cell->upperZ == platform->z && cell->lowerZ == 0x100000 && (cell->flags & MAP_CELL_FLAG_STAIRS) == 0) {
                    door->cellX = x;
                    door->cellY = y;
                    MapGetCell(x, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x, y - 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x + 1, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x + 1, y - 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    return;
                }
            }

            x = x > platform->left ? x - 1 : platform->right - 1;
        }
    }

    if (doorSide == 3) {
        x = platform->left + width * 3 / 8 - GetRandom() % (width >> 2);

        for (i = 0; i < width; i++) {
            for (y = sMapTopRow; y <= sMapBottomRow; y++) {
                cell = MapGetCell(x, y);

                if (cell->type == 4 && cell->lowerZ == platform->z && cell->upperZ == -0x100000 && (cell->flags & MAP_CELL_FLAG_STAIRS) == 0) {
                    door->cellX = x;
                    door->cellY = y;
                    cell->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    cell->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    MapGetCell(x, y + 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x + 1, y)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x + 1, y + 1)->flags |= MAP_CELL_FLAG_KEEP_CLEAR;
                    MapGetCell(x, y - 1)->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    MapGetCell(x, y - 2)->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    MapGetCell(x, y - 3)->flags |= MAP_CELL_FLAG_DOOR_WALL;
                    return;
                }
            }

            x = x > platform->left ? x - 1 : platform->right - 1;
        }
    }
}

s32 MapPlaceLastPlatformDoor() {
    s32 side = 5;
    MapPlatform* platform = &sMapPlatforms[11];

    while (platform->z == 0x100000) {
        platform--;
    }

    switch (gMapRoomState->flags & (ROOM_FLAG_DOOR(1) | ROOM_FLAG_DOOR(2))) {
    case 0x2000000:
        side = 1;
        break;
    case 0x4000000:
        side = 2;
        break;
    case 0x6000000:
        if (platform->right == sMapCols) {
            side = 2;
        } else if (platform->left == 0) {
            side = 1;
        } else {
            s32 randomSide = GetRandom() % 2 ? 2 : 1;

            side = randomSide;
        }

        break;
    }

    if (side != 5) {
        MapPlaceDoorOnPlatform(platform, side);
    }

    return side;
}

u8 MapPlaceFirstPlatformDoor(u8 side) {
    MapPlatform* platform = sMapPlatforms;

    switch (gMapRoomState->flags & (ROOM_FLAG_DOOR(0) | ROOM_FLAG_DOOR(3))) {
    case 0x1000000:
        side = 0;
        break;
    case 0x8000000:
        side = 3;
        break;
    case 0x9000000:
        break;
    default:
        side = 5;
        break;
    }

    if (side != 5) {
        MapPlaceDoorOnPlatform(platform, side);
    }

    return side;
}

void MapPlaceRightPlatformDoor(u8 side) {
    MapPlatform* platform = sMapPlatforms;

    while (platform->right != sMapCols) {
        platform++;
    }

    MapPlaceDoorOnPlatform(platform, side);
}

void MapPlaceLeftPlatformDoor(u8 side) {
    MapPlatform* platform = sMapPlatforms;

    while (platform->left != 0) {
        platform++;
    }

    MapPlaceDoorOnPlatform(platform, side);
}

void MapPlaceDoorsOnLastPlatform() {
    MapPlatform* platform = &sMapPlatforms[11];

    while (platform->z == 0x100000) {
        platform--;
    }

    MapPlaceDoorOnPlatform(platform, 0);
    MapPlaceDoorOnPlatform(platform, 1);
    MapPlaceDoorOnPlatform(platform, 2);
    MapPlaceDoorOnPlatform(platform, 3);
}

void MapPlaceDoors() {
    s32 i;
    MapDoor* door;

    for (i = 0; i < 4; i++) {
        door = GetMapDoor(i);
        door->room = GetMapRoomLink(gMapFloorState.room, i);
        door->side = i;
        door->flags = GetMapDoorFlags(gMapFloorState.room, i);

        if (door->room != MAP_ROOM_NONE) {
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

    if (gMapRoomState->roomType != ROOM_TYPE_GUARDED_TROVE) {
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

void MapComputeRowBounds() {
    s32 i;
    s32 j;

    sMapTopRow = sMapRows;
    sMapBottomRow = 0;

    for (i = 0; i < sMapCols; i++) {
        for (j = 0; j < sMapRows; j++) {
            switch (MapGetCell(i, j)->type) {
            case 2:
            case 4:
            case 6:
                if (j < sMapTopRow) {
                    sMapTopRow = j;
                }

                break;
            case 1:
            case 3:
            case 5:
                if (j > sMapBottomRow) {
                    sMapBottomRow = j;
                }

                break;
            }
        }
    }
}

s32 PickRandomTopEdgeType(s16 left, s16 right, s16 x) {
    s32 type;

    if (x - left < right - x) {
        if (GetRandom() % 3 != 0) {
            type = 4;
        } else {
            type = GetRandom() % 5 != 0 ? 2 : 6;
        }
    } else {
        if (GetRandom() % 3 != 0) {
            type = 6;
        } else {
            type = GetRandom() % 5 != 0 ? 2 : 4;
        }
    }

    return type;
}

s32 PickRandomBottomEdgeType(s16 left, s16 right, s16 x) {
    s32 type;

    if (x - left < right - x) {
        if (GetRandom() % 3 != 0) {
            type = 5;
        } else {
            type = GetRandom() % 5 != 0 ? 1 : 3;
        }
    } else {
        if (GetRandom() % 3 != 0) {
            type = 3;
        } else {
            type = GetRandom() % 5 != 0 ? 1 : 5;
        }
    }

    return type;
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

s32 PickEdgeTypeByHalf(s16 left, s16 right, s16 x, u8 top) {
    if (top) {
        if (x - left < right - x) {
            return 4;
        }

        return 6;
    }

    if (x - left < right - x) {
        return 5;
    }

    return 3;
}

s32 PickEdgeTypeByThird(s16 left, s16 right, s16 x, u8 top) {
    if (top) {
        if (x - left < (right - left) / 3) {
            return 4;
        }

        if (right - x > (right - left) / 3) {
            return 2;
        }

        return 6;
    }

    if (x - left < (right - left) / 3) {
        return 5;
    }

    if (right - x > (right - left) / 3) {
        return 1;
    }

    return 3;
}

s32 GetTopEdgeTypeBelowLedge(u8 index, s16 x, s16 y) {
    s32 i;

    if (index != 0) {
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

void MapSetPlatform(u8 index, u16 left, u16 right, s16 z) {
    if (sMapPlatforms[index].z == 0x100000) {
        sMapPlatforms[index].left = left;
        sMapPlatforms[index].right = right;
        sMapPlatforms[index].z = z << 12;
    }
}

void MapTracePlatformLeftToRight(u8 index, s16 left, s16 right, s16 startY, u8 edgeMode) {
    s16 x;
    s16 y;
    s16 nextY;
    s16 cornerY;
    u8 type;
    s32 prevType;
    s16 bottomY;
    u16* buf;
    u16* topRows;
    s32 z;
    MapCell* cell;
    s32 endY;

    z = sMapPlatforms[index].z;
    buf = EwramAlloc(96);
    y = startY;
    prevType = 4;
    cell = MapGetCell(left, y);
    MapCellSetType(cell, 4, z);
    cell->flags |= MAP_CELL_FLAG_CORNER;
    topRows = buf;
    *topRows++ = y;

    for (x = left + 1; x < right - 1; x++) {
        type = GetTopEdgeTypeBelowLedge(index, x, y);

        if (type == 11) {
            if (y <= 3) {
                type = 6;
            } else if (index == 0) {
                if (edgeMode == 2) {
                    type = PickEdgeTypeByHalf(left, right, x, TRUE);
                } else if (edgeMode == 3) {
                    type = PickEdgeTypeByThird(left, right, x, TRUE);
                } else {
                    type = PickRandomTopEdgeType(left, right, x);
                }
            } else {
                type = PickRandomTopEdgeType(left, right, x);
            }
        }

        y = MapOutlineNextRowLeftToRight(prevType, type, y);
        prevType = type;
        cell = MapGetCell(x, y);
        MapCellSetType(cell, type, z);
        *topRows++ = y;
    }

    cornerY = MapOutlineNextRowLeftToRight(prevType, 6, y);
    cell = MapGetCell(x, cornerY);
    MapCellSetType(cell, 6, z);
    cell->flags |= MAP_CELL_FLAG_CORNER;
    bottomY = cornerY + (right - left);
    y = startY + 1;
    cell = MapGetCell(left, y);
    prevType = 5;
    MapCellSetType(cell, 5, z);
    cell->flags |= MAP_CELL_FLAG_CORNER;
    topRows = buf + 1;

    for (x = left + 1; x < right - 1; x++) {
        nextY = MapOutlineNextRowLeftToRight(prevType, 1, y);

        if (right - x == 2 && bottomY - nextY == 2) {
            type = 5;
        } else if (bottomY - nextY == 1) {
            type = 1;
        } else if (nextY >= bottomY) {
            type = 3;
        } else if (nextY - topRows[1] < gMapForm.minDepth) {
            type = 5;
        } else if (nextY - topRows[1] > gMapForm.maxDepth) {
            type = 3;
        } else if (nextY - topRows[1] == gMapForm.minDepth || nextY - topRows[1] == gMapForm.maxDepth) {
            type = GetMatchingBottomEdgeType(x, topRows[0]);
        } else if (edgeMode == 2) {
            type = PickEdgeTypeByHalf(left, right, x, FALSE);
        } else if (edgeMode == 3) {
            type = PickEdgeTypeByThird(left, right, x, FALSE);
        } else {
            type = PickRandomBottomEdgeType(left, right, x);
        }

        if (nextY >= sMapRows - 1 && type == 5) {
            type = 1;
        }

        y = MapOutlineNextRowLeftToRight(prevType, type, y);
        prevType = type;
        cell = MapGetCell(x, y);
        MapCellSetType(cell, type, z);
        topRows++;
        bottomY--;
    }

    endY = MapOutlineNextRowLeftToRight(prevType, 3, y);
    cell = MapGetCell(x, endY);
    MapCellSetType(cell, 3, z);
    cell->flags |= MAP_CELL_FLAG_CORNER;
    EwramFree(buf);
}

void MapTracePlatformRightToLeft(u8 index, s16 left, s16 right, s16 startY, u8 edgeMode) {
    s16 x;
    s16 nextY;
    s16 cornerY;
    u8 type;
    s32 prevType;
    s16 y;
    s16 bottomY;
    u16* buf;
    u16* topRows;
    s32 z;
    MapCell* cell;
    s32 endY;

    z = sMapPlatforms[index].z;
    buf = EwramAlloc(96);
    y = startY;
    prevType = 6;
    cell = MapGetCell(right - 1, y);
    MapCellSetType(cell, 6, z);
    cell->flags |= MAP_CELL_FLAG_CORNER;
    topRows = buf;
    *topRows++ = y;

    for (x = right - 2; x > left; x--) {
        type = GetTopEdgeTypeBelowLedge(index, x, y);

        if (type == 11) {
            if (y <= 3) {
                type = 4;
            } else if (index == 0) {
                if (edgeMode == 2) {
                    type = PickEdgeTypeByHalf(left, right, x, TRUE);
                } else if (edgeMode == 3) {
                    type = PickEdgeTypeByThird(left, right, x, TRUE);
                } else {
                    type = PickRandomTopEdgeType(left, right, x);
                }
            } else {
                type = PickRandomTopEdgeType(left, right, x);
            }
        }

        y = MapOutlineNextRowRightToLeft(prevType, type, y);
        prevType = type;
        cell = MapGetCell(x, y);
        MapCellSetType(cell, type, z);
        *topRows++ = y;
    }

    cornerY = MapOutlineNextRowRightToLeft(prevType, 4, y);
    cell = MapGetCell(x, cornerY);
    MapCellSetType(cell, 4, z);
    cell->flags |= MAP_CELL_FLAG_CORNER;
    bottomY = cornerY + (right - left);
    y = startY + 1;
    cell = MapGetCell(right - 1, y);
    prevType = 3;
    MapCellSetType(cell, 3, z);
    cell->flags |= MAP_CELL_FLAG_CORNER;
    topRows = buf + 1;

    for (x = right - 2; x > left; x--) {
        nextY = MapOutlineNextRowRightToLeft(prevType, 1, y);

        if (x - left == 1 && bottomY - nextY == 2) {
            type = 3;
        } else if (bottomY - nextY == 1) {
            type = 1;
        } else if (nextY >= bottomY) {
            type = 5;
        } else if (nextY - topRows[1] < gMapForm.minDepth) {
            type = 3;
        } else if (nextY - topRows[1] > gMapForm.maxDepth) {
            type = 5;
        } else if (nextY - topRows[1] == gMapForm.minDepth || nextY - topRows[1] == gMapForm.maxDepth) {
            type = GetMatchingBottomEdgeType(x, topRows[0]);
        } else if (edgeMode == 2) {
            type = PickEdgeTypeByHalf(left, right, x, FALSE);
        } else if (edgeMode == 3) {
            type = PickEdgeTypeByThird(left, right, x, FALSE);
        } else {
            type = PickRandomBottomEdgeType(left, right, x);
        }

        if (nextY >= sMapRows - 1 && type == 3) {
            type = 1;
        }

        y = MapOutlineNextRowRightToLeft(prevType, type, y);
        prevType = type;
        cell = MapGetCell(x, y);
        MapCellSetType(cell, type, z);
        topRows++;
        bottomY--;
    }

    endY = MapOutlineNextRowRightToLeft(prevType, 5, y);
    cell = MapGetCell(x, endY);
    MapCellSetType(cell, 5, z);
    cell->flags |= MAP_CELL_FLAG_CORNER;
    EwramFree(buf);
}

void MapTracePlatformOutward(u8 index, s16 left, s16 right, s16 startX, s16 startY, u8 edgeMode) {
    s16 x;
    s16 nextY;
    s16 cornerY;
    u8 type;
    s32 prevType;
    s16 y;
    s16 bottomY;
    u16* buf;
    u16* topRows;
    s32 z;
    MapCell* cell;
    s32 endY;

    z = sMapPlatforms[index].z;
    buf = EwramAlloc(96);
    topRows = buf + startX;
    y = startY;
    type = GetTopEdgeTypeBelowLedge(index, startX, y);
    prevType = type;
    cell = MapGetCell(startX, y);
    MapCellSetType(cell, type, z);
    *topRows++ = y;

    for (x = startX + 1; x < right - 1; x++) {
        s32 type = (u8)GetTopEdgeTypeBelowLedge(index, x, y);

        if (type == 11) {
            if (y <= 3) {
                type = 6;
            } else if (index == 0) {
                if (edgeMode == 2) {
                    type = (u8)PickEdgeTypeByHalf(left, right, x, TRUE);
                } else if (edgeMode == 3) {
                    type = (u8)PickEdgeTypeByThird(left, right, x, TRUE);
                } else {
                    type = (u8)PickRandomTopEdgeType(left, right, x);
                }
            } else {
                type = (u8)PickRandomTopEdgeType(left, right, x);
            }
        }

        y = MapOutlineNextRowLeftToRight(prevType, type, y);
        prevType = type;
        cell = MapGetCell(x, y);
        MapCellSetType(cell, type, z);
        *topRows++ = y;
    }

    y = MapOutlineNextRowLeftToRight(prevType, 6, y);
    cell = MapGetCell(x, y);
    MapCellSetType(cell, 6, z);
    cell->flags |= MAP_CELL_FLAG_CORNER;
    *topRows = y;
    topRows = buf + startX;
    y = startY;
    type = GetTopEdgeTypeBelowLedge(index, startX, y);
    prevType = type;
    topRows--;

    for (x = startX - 1; x > left; x--) {
        s32 type = (u8)GetTopEdgeTypeBelowLedge(index, x, y);

        if (type == 11) {
            if (y <= 3) {
                type = 4;
            } else if (index == 0) {
                if (edgeMode == 2) {
                    type = (u8)PickEdgeTypeByHalf(left, right, x, TRUE);
                } else if (edgeMode == 3) {
                    type = (u8)PickEdgeTypeByThird(left, right, x, TRUE);
                } else {
                    type = (u8)PickRandomTopEdgeType(left, right, x);
                }
            } else {
                type = (u8)PickRandomTopEdgeType(left, right, x);
            }
        }

        y = MapOutlineNextRowRightToLeft(prevType, type, y);
        prevType = type;
        cell = MapGetCell(x, y);
        MapCellSetType(cell, type, z);
        *topRows-- = y;
    }

    cornerY = MapOutlineNextRowRightToLeft(prevType, 4, y);
    cell = MapGetCell(x, cornerY);
    MapCellSetType(cell, 4, z);
    cell->flags |= MAP_CELL_FLAG_CORNER;
    bottomY = *(buf + right - left - 1) + (right - left);
    y = cornerY + 1;
    cell = MapGetCell(left, y);
    prevType = 5;
    MapCellSetType(cell, 5, z);
    cell->flags |= MAP_CELL_FLAG_CORNER;
    topRows = buf + 1;

    for (x = left + 1; x < right - 1; x++) {
        nextY = MapOutlineNextRowLeftToRight(prevType, 1, y);

        if (right - x == 2 && bottomY - nextY == 2) {
            type = 5;
        } else if (bottomY - nextY == 1) {
            type = 1;
        } else if (nextY >= bottomY) {
            type = 3;
        } else if (nextY - topRows[1] < gMapForm.minDepth) {
            type = 5;
        } else if (nextY - topRows[1] > gMapForm.maxDepth) {
            type = 3;
        } else if (nextY - topRows[1] == gMapForm.minDepth || nextY - topRows[1] == gMapForm.maxDepth) {
            type = GetMatchingBottomEdgeType(x, topRows[0]);
        } else if (edgeMode == 2) {
            type = PickEdgeTypeByHalf(left, right, x, FALSE);
        } else if (edgeMode == 3) {
            type = PickEdgeTypeByThird(left, right, x, FALSE);
        } else {
            type = PickRandomBottomEdgeType(left, right, x);
        }

        if (nextY >= sMapRows - 1 && type == 5) {
            type = 1;
        }

        y = MapOutlineNextRowLeftToRight(prevType, type, y);
        prevType = type;
        cell = MapGetCell(x, y);
        MapCellSetType(cell, type, z);
        topRows++;
        bottomY--;
    }

    endY = MapOutlineNextRowLeftToRight(prevType, 3, y);
    cell = MapGetCell(x, endY);
    MapCellSetType(cell, 3, z);
    cell->flags |= MAP_CELL_FLAG_CORNER;
    EwramFree(buf);
}

void MapFindLowestEdgeRightward(s32 type, s16* px, s16* py, s16* pz, s16 lo, s16 hi) {
    s32 x = lo + GetRandom() % (hi - lo);
    s32 n;

    for (n = 0; n < -lo + hi; n++) {
        s32 j;

        for (j = sMapRows - 1; j >= 0; j--) {
            MapCell* cell = MapGetCell(x, j);

            if (cell->type == type) {
                *px = x;
                *py = j;
                *pz = (cell->upperZ >> 11) / 2;
                return;
            }

            if (cell->type != 11) {
                break;
            }
        }

        x++;

        if (x == hi) {
            x = lo;
        }
    }
}

void MapFindLowestEdgeLeftward(s32 type, s16* px, s16* py, s16* pz, s16 lo, s16 hi) {
    s32 i;
    s32 j;
    s32 x;
    u16 n;
    MapCell* cell;

    n = hi - lo;
    x = lo + GetRandom() % (-lo + hi);

    for (i = 0; i < n; i++) {
        for (j = sMapRows - 1; j >= 0; j--) {
            cell = MapGetCell(x, j);

            if (cell->type == type) {
                *px = x;
                *py = j;
                *pz = (cell->upperZ >> 8) / 16;
                return;
            }

            if (cell->type != 11) {
                break;
            }
        }

        x = x > lo ? x - 1 : hi - 1;
    }
}

u8 MapFindSpanBelowPlatforms(s16* left, s16* right, s16* row, s16* z) {
    u16 x1 = 0;
    u16 y1 = 0;
    u16 x2 = 0;
    u16 y2 = 0;
    s32 z1 = 0;
    s32 z2 = 0;
    s32 found = FALSE;
    s32 x;
    s32 y;
    MapCell* cell;

    for (x = 0; x < sMapCols; x++) {
        for (y = sMapRows - 1; y >= 0; y--) {
            cell = MapGetCell(x, y);

            if (cell->type == 3) {
                x1 = x;
                y1 = y;
                z1 = cell->upperZ;
                found = TRUE;
                break;
            }

            if (cell->type != 11) {
                break;
            }
        }

        if (found) {
            break;
        }
    }

    found = FALSE;

    for (x = sMapCols - 1; x >= 0; x--) {
        for (y = sMapRows - 1; y >= 0; y--) {
            cell = MapGetCell(x, y);

            if (cell->type == 5) {
                x2 = x + 1;
                y2 = y;
                z2 = cell->upperZ;
                found = TRUE;
                break;
            }

            if (cell->type != 11) {
                break;
            }
        }

        if (found) {
            break;
        }
    }

    if ((s16)y1 <= sMapRows - sMapRows / 4 &&
        (s16)y2 <= sMapRows - sMapRows / 4 && (s16)x2 - (s16)x1 > 4) {
        *left = x1;
        *right = x2;

        if (z1 > z2) {
            *z = z1 / 16 >> 8;
            *row = y1;
            return 1;
        }

        *z = z2 / 16 >> 8;
        *row = y2;
        return 2;
    }

    return 0;
}

void MapGenerateLayout1() {
    s16 right;
    s16 y;
    s16 z;
    s16 left;
    s16 height;

    left = sMapCols / 2;
    y = sMapRows / 4;
    left = sMapCols - left;
    right = sMapCols;
    MapSetPlatform(0, left, right, 0);
    MapTracePlatformLeftToRight(0, left, right, y, 2);
    MapFindLowestEdgeLeftward(5, &right, &y, &z, 0, sMapCols);
    height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
    MapSetPlatform(1, 0, right + 1, height + z);
    MapTracePlatformRightToLeft(1, 0, right + 1, height + y, 0);
}

void MapGenerateLayout2() {
    s16 left;
    s16 y;
    s16 z;
    s16 right;
    s16 width;
    s16 height;
    s32 zero;

    width = GetRandom() % (sMapCols - 7) + 4;
    left = GetRandom() % (sMapCols - width - 3) + 2;
    right = left + width;
    y = sMapRows / 4;
    MapSetPlatform(0, left, right, 0);
    MapTracePlatformLeftToRight(0, left, right, y, zero = 0);

    if (GetRandom() % 100 < 50) {
        MapFindLowestEdgeRightward(3, &left, &y, &z, zero, sMapCols);
        height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(1, left, sMapCols, height + z);
        MapTracePlatformLeftToRight(1, left, sMapCols, height + y, zero);
        MapFindLowestEdgeLeftward(5, &right, &y, &z, zero, sMapCols);
        height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(2, 0, right + 1, height + z);
        MapTracePlatformRightToLeft(2, 0, right + 1, height + y, zero);
    } else {
        MapFindLowestEdgeLeftward(5, &right, &y, &z, zero, sMapCols);
        height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(1, 0, right + 1, height + z);
        MapTracePlatformRightToLeft(1, 0, right + 1, height + y, zero);
        MapFindLowestEdgeRightward(3, &left, &y, &z, zero, sMapCols);
        height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(2, left, sMapCols, height + z);
        MapTracePlatformLeftToRight(2, left, sMapCols, height + y, zero);
    }
}

void MapGenerateLayout4() {
    s16 left;
    s16 y;
    s16 z;
    s16 right;
    s16 width;
    s16 height;

    width = GetRandom() % (sMapCols - 9) + 6;
    left = (sMapCols - width) / 2;
    right = left + width;
    y = sMapRows / 4;
    MapSetPlatform(0, left, right, 0);
    MapTracePlatformLeftToRight(0, left, right, y, 2);

    if (GetRandom() % 100 < 50) {
        MapFindLowestEdgeRightward(3, &left, &y, &z, 0, sMapCols);
        height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1) + 10;
        MapSetPlatform(1, left, sMapCols, height + z);
        MapTracePlatformLeftToRight(1, left, sMapCols, height + y, 2);
        MapFindLowestEdgeLeftward(5, &right, &y, &z, 0, sMapCols);
        height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(2, 0, right + 1, height + z);
        MapTracePlatformRightToLeft(2, 0, right + 1, height + y, 2);
    } else {
        MapFindLowestEdgeLeftward(5, &right, &y, &z, 0, sMapCols);
        height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1) + 10;
        MapSetPlatform(1, 0, right + 1, height + z);
        MapTracePlatformRightToLeft(1, 0, right + 1, height + y, 2);
        MapFindLowestEdgeRightward(3, &left, &y, &z, 0, sMapCols);
        height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(2, left, sMapCols, height + z);
        MapTracePlatformLeftToRight(2, left, sMapCols, height + y, 2);
    }
}

void MapGenerateLayout5() {
    s16 left;
    s16 y;
    s16 z;
    s16 right;
    s16 width;
    s16 height;

    width = GetRandom() % (sMapCols - 9) + 6;
    left = (sMapCols - width) / 2;
    right = left + width;
    y = sMapRows / 4;
    MapSetPlatform(0, left, right, 0);
    MapTracePlatformLeftToRight(0, left, right, y, 3);

    if (GetRandom() % 100 < 50) {
        MapFindLowestEdgeRightward(3, &left, &y, &z, 0, sMapCols);
        height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(1, left, sMapCols, height + z);
        MapTracePlatformLeftToRight(1, left, sMapCols, height + y, 3);
        MapFindLowestEdgeLeftward(5, &right, &y, &z, 0, sMapCols);
        height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(2, 0, right + 1, height + z);
        MapTracePlatformRightToLeft(2, 0, right + 1, height + y, 3);
    } else {
        MapFindLowestEdgeLeftward(5, &right, &y, &z, 0, sMapCols);
        height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(1, 0, right + 1, height + z);
        MapTracePlatformRightToLeft(1, 0, right + 1, height + y, 3);
        MapFindLowestEdgeRightward(3, &left, &y, &z, 0, sMapCols);
        height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
        MapSetPlatform(2, left, sMapCols, height + z);
        MapTracePlatformLeftToRight(2, left, sMapCols, height + y, 3);
    }
}

void MapGenerateLayout6() {
    s16 left;
    s16 y;
    s16 z;
    s16 width;
    s16 right;
    s16 height;
    s32 edgeMode;

    width = (sMapCols * 5) / 8;
    left = (sMapCols - width) / 2;
    right = left + width;
    y = sMapRows / 4;
    MapSetPlatform(0, left, right, 0);
    MapTracePlatformLeftToRight(0, left, right, y, edgeMode = 3);
    MapFindLowestEdgeRightward(3, &left, &y, &z, 0, sMapCols);
    height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
    MapSetPlatform(1, 0, sMapCols, height + z);
    MapTracePlatformOutward(1, 0, sMapCols, left, height + y, edgeMode);
}

void MapAddLowerPlatforms(u8 start, u8 end) {
    s32 i;

    for (i = start; i < end; i++) {
        s16 left;
        s16 right;
        s16 row;
        s16 z;
        s16 height;

        switch (MapFindSpanBelowPlatforms(&left, &right, &row, &z)) {
        case 1:
            height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
            MapSetPlatform(i, left, right, height + z);
            MapTracePlatformLeftToRight(i, left, right, height + row, 0);
            break;
        case 2:
            height = gMapForm.minHeight + GetRandom() % (gMapForm.maxHeight - gMapForm.minHeight + 1);
            MapSetPlatform(i, left, right, height + z);
            MapTracePlatformRightToLeft(i, left, right, height + row, 0);
            break;
        default:
            return;
        }
    }
}

void MapGenerateLayout() {
    switch (gMapForm.layout) {
    case 0:
        MapSetPlatform(0, 0, sMapCols, 0);
        MapTracePlatformLeftToRight(0, 0, sMapCols, sMapRows / 4, 0);
        break;
    case 1:
        MapGenerateLayout1();
        break;
    case 2:
        MapGenerateLayout2();
        break;
    case 4:
        MapGenerateLayout4();
        MapAddLowerPlatforms(3, 4);
        break;
    case 5:
        MapGenerateLayout5();
        MapAddLowerPlatforms(3, 4);
        break;
    case 6:
        MapGenerateLayout6();
        break;
    case 7:
        MapSetPlatform(0, 0, sMapCols, 0);
        MapTracePlatformLeftToRight(0, 0, sMapCols, sMapRows / 4, 3);
        MapAddLowerPlatforms(1, 12);
        break;
    case 3:
    default:
        MapGenerateLayout2();
        MapAddLowerPlatforms(3, 12);
        break;
    }
}

void MapGenerateRoom(u16 cols, u16 rows) {
    s32 i;
    s32 n;
    void** bufferPtr;

    sMapRoomDef = gMapRoomDefs[gMapFloorState.world];
    sMapCols = cols;
    sMapRows = rows;
    bufferPtr = &sMapBgBuffer;
    *bufferPtr = EwramAlloc(0x1800);

    if (!gGameState.fieldResume) {
        sMapCells = EwramAlloc(sizeof(MapCell) * 0xC00);
        sMapPlatforms = EwramAlloc(sizeof(MapPlatform) * 12);
        sMapDoors = EwramAlloc(sizeof(MapDoor) * 4);
        n = sMapCols * sMapRows;

        for (i = 0; i < n; i++) {
            sMapCells[i].flags = 0;
            sMapCells[i].type = 11;
            sMapCells[i].bg3Piece = 7;
            sMapCells[i].bg2Piece = 0;
            sMapCells[i].bg1Piece = 0;
            sMapCells[i].bg3Map = NULL;
            sMapCells[i].bg2Map = NULL;
            sMapCells[i].bg1Map = NULL;
        }

        for (i = 0; i < 12; i++) {
            sMapPlatforms[i].left = 0;
            sMapPlatforms[i].right = 0;
            sMapPlatforms[i].z = 0x100000;
            sMapPlatforms[i].hasStairs = FALSE;
            sMapPlatforms[i].x = 0;
            sMapPlatforms[i].y = 0;
            sMapPlatforms[i].spotType = 11;
            sMapPlatforms[i].spotUpperZ = -0x100000;
            sMapPlatforms[i].spotLowerZ = 0x100000;
        }

        MapGenerateLayout();
        MapFillOutlineCells();
        MapComputeCellHeights();
        MapComputeRowBounds();
        MapMarkCellEdges();
        MapMarkFloorVariants();
        MapAssignCellPieces();
        MapAssignBg1Pieces();
        MapPlacePlatformStairs();
        MapPlaceDoors();
    }

    gMapRoomState->topRow = sMapTopRow;
    gMapRoomState->bottomRow = sMapBottomRow;
}

void MapFreeRoom() {
    EwramFree(sMapBgBuffer);

    if (!gGameState.fieldResume) {
        EwramFree(sMapCells);
        EwramFree(sMapPlatforms);
        EwramFree(sMapDoors);
    }
}

void MapDrawBgs(s16 x, s16 y) {
    s16 x0;
    u16* bg3Buf;
    u16* bg2Buf;
    u16* bg1Buf;
    s16 yy;
    s32 i;

    bg3Buf = sMapBgBuffer;
    bg2Buf = (u16*)((u8*)sMapBgBuffer + 0x800);
    bg1Buf = (u16*)((u8*)sMapBgBuffer + 0x1000);
    x0 = x - 1;
    yy = y - 1;

    for (i = 0; i < 32; i++) {
        s16 cellY;
        s16 subY;
        s16 ya;
        s16 xx;
        s32 j;

        cellY = (yy < 0) ? (yy - 8) / 2 : yy / 2;

        subY = yy % 2;
        ya = yy & 31;
        xx = x0;

        for (j = 0; j < 32; j++) {
            MapCell* cell;
            s16 cellX;
            s16 subX;
            s16 xa;

            if (xx < 0) {
                cellX = (xx - 8) / 4;
            } else {
                cellX = xx / 4;
            }

            subX = xx % 4;
            xa = xx & 31;
            cell = MapGetCell(cellX, cellY);

            if (cell != NULL) {
                bg3Buf[ya * 32 + xa] = cell->bg3Map[subY * 32 + subX];

                if (cell->bg2Map != NULL) {
                    bg2Buf[ya * 32 + xa] = cell->bg2Map[subY * 32 + subX];
                } else {
                    bg2Buf[ya * 32 + xa] = 0;
                }

                if (cell->bg1Map != NULL) {
                    bg1Buf[ya * 32 + xa] = cell->bg1Map[subY * 32 + subX];
                } else {
                    bg1Buf[ya * 32 + xa] = 0;
                }
            } else {
                bg3Buf[ya * 32 + xa] = 0;
                bg2Buf[ya * 32 + xa] = sMapRoomDef->map2[0x340];
                bg1Buf[ya * 32 + xa] = sMapRoomDef->map[0x110];
            }

            xx++;
        }

        yy++;
    }

    RequestDma3Copy(bg3Buf, GetBgScreenBase(3), 0x800);
    RequestDma3Copy(bg2Buf, GetBgScreenBase(2), 0x800);
    RequestDma3Copy(bg1Buf, GetBgScreenBase(1), 0x800);
}

void MapDrawBg1(s32 x, s32 y) {
    s16 x0;
    u16* dst;
    s16 yy;
    s32 i;

    dst = (u16*)((u8*)sMapBgBuffer + 0x1000);
    x0 = x;
    x0--;
    yy = y;
    yy--;

    for (i = 0; i < 32; i++) {
        s16 cellY;
        s16 subY;
        s16 ya;
        s16 xx;
        s32 j;

        cellY = (yy < 0) ? (yy - 8) / 2 : yy / 2;

        subY = yy % 2;
        ya = yy & 31;
        xx = x0;

        for (j = 0; j < 32; j++) {
            MapCell* cell;
            s16 cellX;
            s16 subX;
            s16 xa;

            if (xx < 0) {
                cellX = (xx - 8) / 4;
            } else {
                cellX = xx / 4;
            }

            subX = xx % 4;
            xa = xx & 31;
            cell = MapGetCell(cellX, cellY);

            if (cell != NULL) {
                if (cell->bg1Map != NULL) {
                    dst[ya * 32 + xa] = cell->bg1Map[subY * 32 + subX];
                } else {
                    dst[ya * 32 + xa] = 0;
                }
            } else {
                dst[ya * 32 + xa] = sMapRoomDef->map[0x110];
            }

            xx++;
        }

        yy++;
    }

    RequestDma3Copy(dst, GetBgScreenBase(1), 0x800);
}

void MapBuildBgColumn(u16* bg3Map, u16* bg2Map, u16* bg1Map, s16 x, s16 y) {
    MapCell* cell;
    s16 hx;
    s16 mx;
    s16 hy;
    s16 my;
    s32 i;

    hx = (x < 0) ? (x - 8) / 4 : x / 4;
    mx = x % 4;

    for (i = 0; i < 32; i++) {
        hy = (y < 0) ? (y - 8) / 2 : y / 2;
        my = y % 2;
        cell = MapGetCell(hx, hy);

        if (cell != NULL) {
            bg3Map[i] = cell->bg3Map[my * 32 + mx];

            if (cell->bg2Map != NULL) {
                bg2Map[i] = cell->bg2Map[my * 32 + mx];
            } else {
                bg2Map[i] = 0;
            }

            if (cell->bg1Map != NULL) {
                bg1Map[i] = cell->bg1Map[my * 32 + mx];
            } else {
                bg1Map[i] = 0;
            }
        } else {
            bg3Map[i] = 0;
            bg2Map[i] = sMapRoomDef->map2[0x340];
            bg1Map[i] = sMapRoomDef->map[0x110];
        }

        y++;
    }
}

void MapDrawBgColumn(void* buf, s16 x, s16 y) {
    void* bg2Buf = (u8*)buf + 0x40;
    void* bg1Buf = (u8*)buf + 0x80;

    MapBuildBgColumn(buf, bg2Buf, bg1Buf, x, y);
    RequestTilemapStripCopy(buf, GetBgScreenBase(3), x, y, TRUE);
    RequestTilemapStripCopy(bg2Buf, GetBgScreenBase(2), x, y, TRUE);
    RequestTilemapStripCopy(bg1Buf, GetBgScreenBase(1), x, y, TRUE);
}

void MapBuildBgRow(u16* bg3Map, u16* bg2Map, u16* bg1Map, s16 x, s16 y) {
    MapCell* cell;
    s16 hx;
    s16 mx;
    s16 hy;
    s16 my;
    s32 i;

    hy = (y < 0) ? (y - 8) / 2 : y / 2;
    my = y % 2;

    for (i = 0; i < 32; i++) {
        if (x < 0) {
            hx = (x - 8) / 4;
        } else {
            hx = x / 4;
        }

        mx = x % 4;
        cell = MapGetCell(hx, hy);

        if (cell != NULL) {
            bg3Map[i] = cell->bg3Map[my * 32 + mx];

            if (cell->bg2Map != NULL) {
                bg2Map[i] = cell->bg2Map[my * 32 + mx];
            } else {
                bg2Map[i] = 0;
            }

            if (cell->bg1Map != NULL) {
                bg1Map[i] = cell->bg1Map[my * 32 + mx];
            } else {
                bg1Map[i] = 0;
            }
        } else {
            bg3Map[i] = 0;
            bg2Map[i] = sMapRoomDef->map2[0x340];
            bg1Map[i] = sMapRoomDef->map[0x110];
        }

        x++;
    }
}

void MapDrawBgRow(void* buf, s16 x, s16 y) {
    void* bg2Buf = (u8*)buf + 0x40;
    void* bg1Buf = (u8*)buf + 0x80;

    MapBuildBgRow(buf, bg2Buf, bg1Buf, x, y);
    RequestTilemapStripCopy(buf, GetBgScreenBase(3), x, y, FALSE);
    RequestTilemapStripCopy(bg2Buf, GetBgScreenBase(2), x, y, FALSE);
    RequestTilemapStripCopy(bg1Buf, GetBgScreenBase(1), x, y, FALSE);
}

u8 MapPickFreeFloorPos(FldPos* pos, s32* py) {
    u16 rows;
    u16 x;
    u16 y;
    s32 i;
    s32 j;

    rows = sMapBottomRow - sMapTopRow;
    x = GetRandom() % sMapCols;
    y = GetRandom() % rows;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < sMapCols; j++) {
            u16 yy = y + sMapTopRow;

            if ((*(u32*)MapGetCell(x, yy) & 0xFF0340) == 0) {
                pos->x = (x << 13) + 0x1000;
                *py = (yy << 12) + 0x800;
                return TRUE;
            }

            x++;
            x %= sMapCols;
        }

        y++;
        y %= rows;
    }

    pos->x = gFieldState->actor.fieldPosition.x;
    *py = gFieldState->actor.fieldPosition.y + gFieldState->actor.fieldPosition.ground;
    return FALSE;
}

u8 MapPickFreeFloorPosInView(FldPos* pos, s32* py) {
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
            s32* playerPos = &gFieldState->actor.fieldPosition.x;
            MapCell* cell;

            if (playerPos[0] < (xx * 32 + 80) << 8 && playerPos[0] > (xx * 32 - 48) << 8 &&
                playerPos[1] < (yy * 16 + 40) << 8 && playerPos[1] > (yy * 16 - 24) << 8) {
                continue;
            }

            cell = MapGetCell(xx, yy);

            if (cell != NULL && (*(u32*)cell & 0xFF0340) == 0) {
                pos->x = (xx << 13) + 0x1000;
                *py = (yy << 12) + 0x800;
                return TRUE;
            }

            x++;
            x %= w;
        }

        y++;
        y %= h;
    }

    MapPickFreeFloorPos(pos, py);
    return FALSE;
}

MapCell* MapCellAt(s16 x, s16 y) {
    return MapGetCell(x, y);
}

MapPlatform* GetMapPlatform(u8 index) {
    return &sMapPlatforms[index];
}

u8* GetMapRoomEvent(u8 step) {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        return (u8*)(gMapRoomDefs[gMapFloorState.world]->rikuEvents + step);
    }

    return (u8*)(gMapRoomDefs[gMapFloorState.world]->soraEvents + step);
}

void* GetMapBgBuffer() {
    return sMapBgBuffer;
}

void LoadMapForm(u8 form) {
    if (form != 0x10) {
        gMapForm = gMapFormDefs[form];
    } else {
        gMapForm = gMapFormDefs[GetRandom() % 15];
    }
}

u16 GetRandomMapWidth() {
    return gMapForm.minWidth + GetRandom() % (gMapForm.maxWidth - gMapForm.minWidth + 1);
}

MapDoor* MapGetDoor(u8 side) {
    return &sMapDoors[side];
}

MapCell* MapFixGetCell(s16 x, s16 y) {
    if (y < 0 || y >= gMapRoomState->rows || x < 0 || x >= gMapRoomState->cols) {
        return NULL;
    }

    return &sMapFixCells[gMapRoomState->cols * y + x];
}

void MapFixLoadCellTypes(const u8* src) {
    s32 x;
    s32 y;

    for (y = 0; y < gMapRoomState->rows; y++) {
        for (x = 0; x < gMapRoomState->cols; x++) {
            MapCell* cell = MapFixGetCell(x, y);

            cell->type = src[gMapRoomState->cols * y + x];
            cell->maskTable = GetCellMaskTable(cell->type);

            switch (cell->type) {
            case 0:
                cell->upperZ = 0;
                cell->lowerZ = 0;
                break;
            case 1:
            case 3:
            case 5:
                cell->upperZ = 0;
                cell->lowerZ = 0x100000;
                break;
            case 2:
            case 4:
            case 6:
                cell->upperZ = -0x100000;
                cell->lowerZ = 0;
                break;
            default:
                cell->upperZ = -0x100000;
                cell->lowerZ = 0x100000;
                break;
            }
        }
    }
}

void MapFixCreateGimmicks(void* gimmicks) {
    MapFixedGmk* fixedGmk = gimmicks;
    MapGmkPlacement* placement;
    FldPos pos;
    s32 y;
    s32 n;

    if (fixedGmk == NULL) {
        return;
    }

    placement = gMapGmkPlacements;

    while (fixedGmk->defIndex != MAP_FIXED_GMK_END) {
        pos.x = fixedGmk->x;
        y = fixedGmk->y;
        pos.y = pos.z = pos.ground = 0;
        pos.y = y;
        placement->flags = GMK_FLAG_USED;
        n = fixedGmk->defIndex;
        placement->def = &gMapGmkDefs[n];
        placement->pos = pos;
        TaskCreate(&gFieldState->tasks, &gTaskDescMapGmk00, placement);
        fixedGmk++;
        placement++;
    }

    if (gMapFloorState.room != MAP_ROOM_ENTRANCE_HALL) {
        return;
    }

    if ((gGameState.flags & GAME_FLAG_RIKU) || gGameState.floor != 0) {
        pos.x = 0x18000;
        y = 0x11000;
    } else {
        pos.x = 0x26000;
        y = 0x12000;
    }

    pos.y = y;
    n = 0;
    pos.ground = n;
    pos.z = n;
    placement->flags = n;
    placement->def = &gMapGmk04Def;
    placement->pos = pos;
    TaskCreate(&gFieldState->tasks, gMapGmk04Def.desc, placement);
    placement++;

    if (GetProgressFloor() != 0) {
        if ((gGameState.flags & GAME_FLAG_RIKU) || gGameState.floor != 0) {
            pos.x = 0x1F000;
            y = 0x14000;
        } else {
            pos.x = 0x2D000;
            y = 0x15000;
        }

        pos.y = y;
        n = 0;
        pos.ground = n;
        pos.z = n;
        placement->flags = n;
        placement->def = &gMapGmk06Def;
        placement->pos = pos;
        TaskCreate(&gFieldState->tasks, gMapGmk06Def.desc, placement);
    }
}

void MapFixSnapCamera() {
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

void MapFixInitCells(MapFixedDef* def) {
    s32 i;
    s32 n;

    sMapFixCells = EwramAlloc(sizeof(MapCell) * 0xC00);
    n = gMapRoomState->cols * gMapRoomState->rows;

    for (i = 0; i < n; i++) {
        sMapFixCells[i].flags = 0;
        sMapFixCells[i].type = 11;
        sMapFixCells[i].bg3Piece = 7;
        sMapFixCells[i].bg2Piece = 0;
        sMapFixCells[i].bg1Piece = 0;
        sMapFixCells[i].bg3Map = NULL;
        sMapFixCells[i].bg2Map = NULL;
        sMapFixCells[i].bg1Map = NULL;
    }

    MapFixLoadCellTypes(def->cellTypes);
}

void MapFixFreeCells() {
    EwramFree(sMapFixCells);
}

MapCell* MapFixCellAt(s16 x, s16 y) {
    return MapFixGetCell(x, y);
}
