#ifndef GUARD_STAFF_ROLL_TYPES_H
#define GUARD_STAFF_ROLL_TYPES_H

#include "types.h"

typedef struct StaffRollScene {
    u8 color256;
    u8 fadeInBg;
    u8 fadeOutBg;
    u8 unk_03;
    s32 duration;
    s32 x;
    s32 y;
    void* tiles;
    u16 tilesSize;
    u16 unk_16;
    void* map;
    u16 mapSize;
    u16 unk_1E;
    void* palette;
    u16 paletteSize;
    u16 unk_26;
    s32 targetX;
    s32 targetY;
    u16 animId;
    u16 nameIndex;
} StaffRollScene;

#endif
