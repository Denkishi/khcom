#ifndef GUARD_MAP_ROOM_TYPES_H
#define GUARD_MAP_ROOM_TYPES_H

#include "types.h"

typedef struct MapFixedGmk {
    u8 defIndex;
    u8 unk_01[0x03];
    s32 x;
    s32 y;
} MapFixedGmk;

typedef struct MapFixedCollider {
    u16 radius;
    u8 unk_02[0x02];
    s32 x;
    s32 y;
} MapFixedCollider;

typedef struct MapDecorRule {
    const u8* pattern;
    u8 width;
    u8 height;
    u8 chance;
    u8 unk_07;
    const u8* pieces;
    u16* tilemap;
} MapDecorRule;

typedef struct MapRoomDef {
    void* palette;
    u16 paletteSize;
    u8 unk_06[0x02];
    void* tiles;
    u16 tilesSize;
    u8 unk_0E[0x02];
    void* tiles2;
    u16 tilesSize2;
    u8 unk_16[0x02];
    u16* map3;
    u16* map2;
    u16* map;
    MapDecorRule* layer1DecorRules;
    MapDecorRule* layer2DecorRules;
    void* tileAnims;
    s32* soraEvents;
    s32* rikuEvents;
    u16 song;
} MapRoomDef;

typedef struct MapFixedDef {
    void* palette;
    u16 paletteSize;
    u8 unk_06[0x02];
    void* tiles;
    u16 tilesSize;
    u8 unk_0E[0x02];
    void* tiles2;
    u16 tilesSize2;
    u8 unk_16[0x02];
    void* map3;
    void* map2;
    void* map;
    u8 mapWidth;
    u8 mapHeight;
    u8 unk_26[0x02];
    const u8* cellTypes;
    struct MapFixedGmk* gimmicks;
    struct MapFixedCollider* colliders;
    u16 song;
    u8 unk_36[0x02];
    s32 stairX;
    s32 stairY;
    s32 stair2X;
    s32 stair2Y;
    s32 spawnX;
    s32 spawnY;
#ifdef VERSION_EU
    u8 unk_50;
#endif
} MapFixedDef;

#endif
