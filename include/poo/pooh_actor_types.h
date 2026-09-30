#ifndef GUARD_POOH_ACTOR_TYPES_H
#define GUARD_POOH_ACTOR_TYPES_H

#include "types.h"
#include "anim.h"
#include "battle_actor_types.h"
#include "obj.h"
#include "taskpool.h"
#include "listpool.h"

struct PooNode;

typedef struct PooPos {
    s32 x;
    s32 y;
    s32 z;
    s32 ground;
} PooPos;

typedef struct PooActor {
    PooPos pos;
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
} PooActor;

typedef struct PooState {
    PooPos pos;
    PooPos pos2;
    s32 poohAction;
    u32 flags;
    u16 eventsDone;
    u16 unk_2A;
    u32 droppedPrizes[4];
    u16 gauge;
    u16 gaugeTimer;
    u16 wheelX;
    u16 wheelY;
} PooState;

typedef struct PooShadowInfo {
    u16 priority;
    u16 unk_02;
    s32 z;
} PooShadowInfo;

typedef struct PooHitBox {
    void* palette;
    u16 tileCount;
    s16 height;
    s16 radius;
    s16 unk_0A;
} PooHitBox;

typedef struct PoohWork {
    void* tiles;
    ObjPalette* palette;
    void* gfx;
    AnimState anim;
    u8 flipped;
    u8 unk_25;
    u16 animAction;
    PooPos pos;
    u8 angle;
    u8 lookTarget;
    u8 lookAngle;
    u8 lookColumn;
    s32 speed;
    s32 targetX;
    s32 targetY;
    s32 vz;
    Collider collider;
    s32 dirIndex;
    u16 balloonTimer;
    u8 unk_AE[0x02];
    TaskPool tasks;
    Task* task;
    Task* zzzTask;
    u8 unk_CC;
    u8 unk_CD[0x03];
    struct PooNode* targetNode;
    u16 lookTimer;
    u8 unk_D6;
    u8 unk_D7;
    u16 sleepTimer;
    s16 actionTimer;
    u16 callTimer;
    u8 unk_DE[0x02];
    PooShadowInfo shadowInfo;
    u8 onCollider;
    u8 unk_E9[0x03];
    s32 groundZ;
    s32 stumpIndex;
    u16 stumpCount;
    u8 leavingWagon;
    u8 unk_F7;
    u16 callCount;
    u8 hideShadow;
    u8 hopAngle;
} PoohWork;

#endif
