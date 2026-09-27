#ifndef GUARD_EVENT_CHARA_TYPES_H
#define GUARD_EVENT_CHARA_TYPES_H

#include "types.h"
#include "taskpool.h"
#include "battle_actor_types.h"
#include "evt_object_types.h"
#include "msg_types.h"

typedef struct EventSeqArg {
    u32 unk_00 : 16;
    u32 unk_02 : 8;
    u32 unk_03 : 8;
} EventSeqArg;

typedef struct EventCharaParams {
    s16 spriteYOffset;
    s16 unk_02;
    s16 unk_04;
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
    s32 unk_17C;
    s32 unk_180;
    s32 unk_184;
    s32 unk_188;
    s32 unk_18C;
    s32 unk_190;
    s32 unk_194;
    s32 unk_198;
    s32 unk_19C;
    u32 unk_1A0;
    s32 unk_1A4;
    u8 unk_1A8;
    u8 unk_1A9;
    u8 unk_1AA;
    u8 unk_1AB;
    u8 unk_1AC;
    u8 unk_1AD;
    u8 unk_1AE;
    u8 unk_1AF;
    u8 unk_1B0;
    u8 unk_1B1;
    u8 unk_1B2;
    u8 unk_1B3;
    u8 unk_1B4;
    u8 unk_1B5;
    u8 unk_1B6;
    u8 unk_1B7;
    u16 unk_1B8;
    u8 unk_1BA[2];
} EventCharaWork;

#endif
