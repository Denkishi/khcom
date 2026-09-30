#ifndef GUARD_HUM_TYPES_H
#define GUARD_HUM_TYPES_H

#include "types.h"
#include "anim.h"
#include "taskpool.h"
#include "obj.h"
#include "battle_actor_types.h"

typedef struct HumSub {
    void* unk_00;
    void* tiles;
    void* palette;
    void* palette2;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    u16 flags;
    u16 unk_36;
    void* gfx;
} HumSub;

typedef struct HumDef {
    u16 tileCount;
    u16 unk_02;
    void* palette;
    u32 unk_08;
    EmyKind kind;
} HumDef;

typedef struct HumSubDef {
    void* palette;
    u16 tileCount;
    u16 unk_06;
} HumSubDef;

typedef struct HumWork {
    const void* def;
    ObjTiles* tiles;
    ObjPalette* palette;
    HumSub* sub;
    HumSub* sub2;
    AnimState anim;
    TaskPool tasks;
    BtlObj actor;
    s16 stateTimer;
    s16 steps;
    u32 flags;
    u32 vz;
    u32 targetX;
    u32 targetY;
    s32 targetZ;
    s32 scaleX;
    s32 scaleY;
    u32 state;
    s16 boundsMargin;
    u16 unk_176;
    void* paletteData;
    u16 unk_17C;
    u16 itemIndex;
    void* gfx;
    const u32* stockMoves;
} HumWork;

#endif
