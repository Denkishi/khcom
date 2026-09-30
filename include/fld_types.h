#ifndef GUARD_FLD_TYPES_H
#define GUARD_FLD_TYPES_H

#include "types.h"
#include "anim.h"
#include "listpool.h"
#include "taskpool.h"
#include "obj.h"
#include "battle_actor_types.h"

typedef struct FldPos {
    s32 x;
    s32 y;
    s32 z;
    s32 ground;
} FldPos;

typedef AnimDef FldAnimDef;

typedef ObjPalette FldRes;

typedef struct FldActor {
    FldPos fieldPosition;
    s32 speed;
    u8 angle;
    u8 unk_15[0x05];
    u16 height;
    ListNode node;
    u16 kind;
    u16 unk_32;
    u8 unk_34[0x06];
    u16 shadowPriority;
    s32 shadowZ;
    ListPool pool;
} FldActor;

typedef struct FldObj {
    FldPos fieldPosition;
    s32 speed;
    u8 angle;
    u8 unk_15[0x05];
    s16 height;
    ListNode node;
    u16 kind;
    u16 unk_32;
    u16 unk_34;
    u8 unk_36[0x04];
    u16 shadowPriority;
    s32 shadowZ;
} FldObj;

typedef char FldActor_size[(sizeof(FldActor) == 0x50) ? 1 : -1];
typedef char FldObj_size[(sizeof(FldObj) == 0x40) ? 1 : -1];

typedef struct FldWork {
    void* tiles;
    FldRes* palette;
    AnimState anim;
    void* gfx;
    TaskPool tasks;
    Collider collider;
    u32 state;
    s16 timer;
    s16 steps;
    u8 unk_9C;
    u8 unk_9D;
    u16 unk_9E;
    s32 vz;
    u16 flags;
    u8 unk_A6[0x02];
    s32 animAction;
    const u16* sounds;
    s32 targetX;
    s32 targetY;
    s32 targetZ;
    u8 onCollider;
    u8 unk_BD[0x03];
} FldWork;

typedef char FldWork_size[(sizeof(FldWork) == 0xC0) ? 1 : -1];

#endif
