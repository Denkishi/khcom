#ifndef GUARD_POOH_ACTOR_TYPES_H
#define GUARD_POOH_ACTOR_TYPES_H

#include "types.h"
#include "anim.h"
#include "battle_actor_types.h"
#include "obj.h"
#include "taskpool.h"

typedef struct PooPos {
    s32 x;
    s32 y;
    s32 z;
    s32 unk_0C;
} PooPos;

typedef struct PooActor {
    PooPos pos;
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
} PooActor;

typedef struct PooState {
    PooPos pos;
    PooPos pos2;
    s32 unk_20;
    u32 unk_24;
    u16 unk_28;
    u16 unk_2A;
    u32 unk_2C[4];
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
    u16 unk_42;
} PooState;

typedef struct PooShadowInfo {
    u16 unk_00;
    u16 unk_02;
    s32 unk_04;
} PooShadowInfo;

typedef struct PooHitBox {
    void* unk_00;
    u16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
} PooHitBox;

typedef struct PoohWork {
    void* tiles;
    ObjPalette* palette;
    void* gfx;
    AnimState anim;
    u8 unk_24;
    u8 unk_25;
    u16 unk_26;
    PooPos pos;
    u8 angle;
    u8 unk_39;
    u8 unk_3A;
    u8 unk_3B;
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    Collider collider;
    s32 unk_A8;
    u16 unk_AC;
    u8 unk_AE[0x02];
    TaskPool tasks;
    Task* task;
    Task* unk_C8;
    u8 unk_CC;
    u8 unk_CD[0x03];
    struct PooNode* unk_D0;
    u16 unk_D4;
    u8 unk_D6;
    u8 unk_D7;
    u16 unk_D8;
    s16 unk_DA;
    u16 unk_DC;
    u8 unk_DE[0x02];
    PooShadowInfo shadowInfo;
    u8 unk_E8;
    u8 unk_E9[0x03];
    s32 unk_EC;
    s32 unk_F0;
    u16 unk_F4;
    u8 unk_F6;
    u8 unk_F7;
    u16 unk_F8;
    u8 unk_FA;
    u8 unk_FB;
} PoohWork;

#endif
