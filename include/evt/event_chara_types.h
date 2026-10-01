#ifndef GUARD_EVENT_CHARA_TYPES_H
#define GUARD_EVENT_CHARA_TYPES_H

#include "types.h"
#include "taskpool.h"
#include "battle_actor_types.h"
#include "evt_object_types.h"
#include "msg_types.h"

typedef struct EventSeqArg {
    u32 eventId : 16;
    u32 chara : 8;
    u32 track : 8;
} EventSeqArg;

typedef struct EventCharaParams {
    s16 spriteYOffset;
    s16 slowSpeed;
    s16 fastSpeed;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
} EventCharaParams;

typedef struct EventCharaWork {
    const EventCharaKeyframe* keyframes;
    void* tiles;
    void* palette;
    void* gfx;
    TaskPool tasks;
    EventSeqArg arg;
    EvtObj obj;
    BtlObj actor;
    u8 unk_164[0x18];
    s32 animId;
    s32 spriteX;
    s32 spriteY;
    s32 hopVelocity;
    s32 unk_18C;
    s32 startX;
    s32 startZ;
    s32 unk_198;
    s32 speed;
    u32 keyframe;
    s32 steps;
    u8 waitTimer;
    u8 effectLevel;
    u8 effectTimer;
    u8 angle;
    u8 lastAngle;
    u8 moveMode;
    u8 lastMoveMode;
    u8 jumpPhase;
    u8 bobPhase;
    u8 spriteFlipX;
    u8 callbackActive;
    u8 usesBtlWork;
    u8 hasObj;
    u8 finished;
    u8 visible;
    u8 unk_1B7;
    u16 unk_1B8;
    u8 unk_1BA[2];
} EventCharaWork;

#endif
