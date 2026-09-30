#ifndef GUARD_POO_DATA_H
#define GUARD_POO_DATA_H

#include "types.h"
#include "anim.h"

typedef struct PooPoint {
    s32 x;
    s32 y;
} PooPoint;

typedef struct PooSpot {
    s32 x;
    s32 y;
    s32 z;
} PooSpot;

typedef struct PooMapBgDesc {
    void* tiles;
    u16 tilesSize;
    u16 unk_06;
    void* palette;
    u16 paletteSize;
    u16 unk_0E;
    void* tiles2;
    u16 tilesSize2;
    u8 mapWidth;
    u8 mapHeight;
} PooMapBgDesc;

extern const PooSpot gPooh04FrameOffsets[];
extern const PooSpot gPooh04aFrameOffsets[];
extern const PooPoint gPoohStumpCircle[];
extern const PooMapBgDesc gPooMapBgDesc;
extern const PooSpot gPooCabbageStackOffsets[];

#endif
