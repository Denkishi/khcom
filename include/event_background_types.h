#ifndef GUARD_EVENT_BACKGROUND_TYPES_H
#define GUARD_EVENT_BACKGROUND_TYPES_H

#include "types.h"

struct EventMapObjectDef;

typedef struct EventBackgroundDef {
    void* tiles;
    void* tiles2;
    void* palette;
    const void** maps;
    const void** maps2;
    const void** maps3;
    u16 tilesSize;
    u16 tilesSize2;
    u16 paletteSize;
    u8 mapWidth;
    u8 mapHeight;
    s32 mapAnim;
    u8 isAffine;
    u8 unk_25[3];
    struct EventMapObjectDef* mapObjects;
    u8 groundType;
    u8 flags;
    u8 compression[2];
} EventBackgroundDef;

#endif
