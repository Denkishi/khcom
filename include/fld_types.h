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
    s32 unk_0C;
} FldPos;

typedef AnimDef FldAnimDef;

typedef ObjPalette FldRes;

typedef struct FldActor {
    FldPos fieldPosition;
    s32 unk_10;
    u8 angle;
    u8 unk_15[0x05];
    u16 unk_1A;
    ListNode node;
    u16 unk_30;
    u16 unk_32;
    u8 unk_34[0x06];
    u16 unk_3A;
    s32 unk_3C;
    ListPool pool;
} FldActor;

typedef struct FldObj {
    FldPos fieldPosition;
    s32 unk_10;
    u8 angle;
    u8 unk_15[0x05];
    s16 unk_1A;
    ListNode node;
    u16 unk_30;
    u16 unk_32;
    u16 unk_34;
    u8 unk_36[0x04];
    u16 unk_3A;
    s32 unk_3C;
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
    u32 unk_94;
    s16 unk_98;
    s16 unk_9A;
    u8 unk_9C;
    u8 unk_9D;
    u16 unk_9E;
    s32 unk_A0;
    u16 unk_A4;
    u8 unk_A6[0x02];
    s32 unk_A8;
    const u16* unk_AC;
    s32 unk_B0;
    s32 unk_B4;
    s32 unk_B8;
    u8 unk_BC;
    u8 unk_BD[0x03];
} FldWork;

typedef char FldWork_size[(sizeof(FldWork) == 0xC0) ? 1 : -1];

#endif
