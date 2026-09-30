#ifndef GUARD_BATTLE_ACTOR_TYPES_H
#define GUARD_BATTLE_ACTOR_TYPES_H

#include "types.h"
#include "taskpool.h"

typedef struct EmyKind {
    u32 id;
    u16 maxHp;
    s16 height;
    s16 radius;
    u16 centerHeight;
    u16 unk_0C;
    u16 flags;
} EmyKind;

typedef struct Collider {
    s32 type;
    s32 x;
    s32 y;
    s32 z;
    s32 radius;
    s32 height;
    ListNode node;
    u8 colliding;
    u8 unk_2D;
    u16 standFlags;
    u16 flags;
    u8 unk_32[0x02];
    s32 otherType;
    s32 pushX;
    s32 pushY;
    s32 platformZ;
    s32 platformX;
    s32 platformY;
    s32 penetration;
    struct Collider* other;
    struct Collider* self;
    u32 touchedTypes;
} Collider;

typedef struct BtlObjPos {
    s32 unk_00;
    s32 x;
    s32 y;
    s32 z;
} BtlObjPos;

typedef struct BtlObj {
    s32 kind;
    s32 x;
    s32 y;
    s32 z;
    s32 groundZ;
    s32 originX;
    s32 originY;
    s32 originZ;
    s16 damage;
    u8 unk_022[0x02];
    s32 hitFlags;
    s32 hitAttack;
    s16 hp;
    s16 maxHp;
    s16 attack;
    u8 unk_032[0x02];
    u64 flags;
    u16 kindFlags;
    u8 unk_03E[0x02];
    Collider collider;
    u16 height;
    u16 radiusX;
    u16 radiusY;
    s16 centerHeight;
    s16 centerOffsetX;
    u8 unk_0A6[0x02];
    s32 knockbackSpeed;
    s32 knockbackLift;
    u8 angle;
    u8 unk_0B1;
    u16 cardInterval;
    u16 exp;
    u8 unk_0B6[0x02];
    ListNode node;
    u16 shadowPriority;
    s16 attackOffset;
    s16 attackRangeX;
    s16 attackRangeY;
    s32 floorZ;
    struct BtlObj* parent;
    struct BtlObj* self;
    u16 delayedDamage;
    s16 invincibleTimer;
    struct BtlWork* btl;
    s32 badStatus;
    s16 badStatusTimer;
    u8 unk_0EE[0x02];
    s32 unk_0F0;
    s32 unk_0F4;
    s32 unk_0F8;
    s32 prevX;
    s32 prevY;
    s16 popCooldown;
    s16 hitFlashFrames;
    s32 vx;
    s32 vy;
} BtlObj;

typedef char Collider_size[(sizeof(Collider) == 0x5C) ? 1 : -1];
typedef char BtlObj_size[(sizeof(BtlObj) == 0x110) ? 1 : -1];

#endif
