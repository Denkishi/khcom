#ifndef GUARD_MAP_TYPES_H
#define GUARD_MAP_TYPES_H

#include "types.h"
#include "fld_types.h"

typedef struct EventKey {
    u8 kind;
    u8 color;
    u8 rule;
    u8 value;
} EventKey;

typedef struct EventKeyList {
    u8 count;
    u8 unk_01[0x03];
    EventKey* keys;
} EventKeyList;

typedef struct MapDoor {
    u16 flags;
    u16 cellX;
    u16 cellY;
    u8 side;
    u8 room;
} MapDoor;

typedef struct MapRoomState {
    u32 flags;
    u16 cols;
    u16 rows;
    u16 topRow;
    u16 bottomRow;
    u8 nameId;
    u8 roomType;
    u8 battleId;
    u8 doorRoom;
    u8 doorSide;
    u8 unk_11[0x03];
    FldObj* door;
    u8 jumpGmkAngle;
    u8 unk_19[0x03];
    s32 jumpGmkHeight;
    u8 attackActive;
    u8 unk_21[0x03];
    s32 attackX;
    s32 attackY;
    s32 attackZ;
    TaskPool tasks;
} MapRoomState;

typedef struct MapCell {
    u16 flags;
    u8 type;
    u8 bg3Piece;
    u8 bg2Piece;
    u8 bg1Piece;
    u8 unk_06[0x02];
    s32 upperZ;
    s32 lowerZ;
    void* maskTable;
    u16* bg3Map;
    u16* bg2Map;
    u16* bg1Map;
} MapCell;

typedef struct MapEventDoor {
    u8 kind;
    u8 keyList;
    u8 room;
    u8 side;
    u8 returnRoom;
    u8 returnSide;
    u8 unk_06[0x02];
} MapEventDoor;

typedef struct MapFloorRoom {
    u16 flags;
    u8 unk_02;
    u8 unk_03;
    u32 seed;
    u8 nameId;
    u8 roomType;
    u8 cardValue;
    u8 enemiesLeft;
    u8 przCardsLeft;
    u8 unk_0D[0x03];
} MapFloorRoom;

typedef struct EventKeyProgress {
    u8 paid;
    u8 remaining;
    u8 unk_02[0x02];
} EventKeyProgress;

typedef struct MapFloorState {
    u8 progress;
    u8 unk_01;
    u16 flags;
    u8 world;
    u8 eventStep;
    u8 room;
    u8 entrySide;
    EventKeyProgress eventKeyProgress[4];
    u8 unk_18[0x04];
    MapFloorRoom rooms[32];
} MapFloorState;

typedef struct MapFormDef {
    u8 layout;
    u8 minWidth;
    u8 maxWidth;
    u8 minHeight;
    u8 maxHeight;
    u8 minDepth;
    u8 maxDepth;
    u8 unk_07;
} MapFormDef;

#endif
