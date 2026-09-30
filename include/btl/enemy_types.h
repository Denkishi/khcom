#ifndef GUARD_ENEMY_TYPES_H
#define GUARD_ENEMY_TYPES_H

#include "types.h"
#include "anim.h"
#include "taskpool.h"
#include "battle_actor.h"

enum EmyDefFlag {
    EMY_DEF_FLAG_NO_SHADOW = 0x1,
    EMY_DEF_FLAG_NO_SCALE_IN = 0x2
};

enum EmyFlag {
    EMY_FLAG_DARK_DEATH = 0x1,
    EMY_FLAG_AT_FIELD_EDGE = 0x2,
    EMY_FLAG_LUNGE_HIT = 0x4
};

typedef struct EmyDef {
    void* palette;
    const AnimDef* animDef;
    s32 speed;
    u16 moveInterval;
    u16 turnInterval;
    u16 hitStunFrames;
    u16 attackOffset;
    u16 attackRangeX;
    u16 attackRangeY;
    u16 cardInterval;
    u16 flags;
    EmyKind kind;
} EmyDef;

typedef struct EmyWork {
    void* tiles;
    void* palette;
    void* palette2;
    void* gfx;
    AnimState anim;
    TaskPool tasks;
    BtlObj actor;
    u32 state;
    u32 idleState;
    s16 stateTimer;
    s16 steps;
    u16 flags;
    u8 visible;
    u8 unk_15B;
    const EmyDef* def;
    u8 angle;
    u8 unk_161;
    u16 spriteFlags;
    s32 speed;
    s32 vz;
    u32 fxScale;
    s32 x;
    s32 y;
    s32 hoverZ;
    s32 scaleX;
    s32 scaleY;
} EmyWork;

typedef struct EmyObj {
    s32 x;
    s32 y;
    s32 z;
} EmyObj;

#endif
