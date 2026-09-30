#ifndef GUARD_FIELD_STATE_H
#define GUARD_FIELD_STATE_H

#include "types.h"
#include "fld_types.h"
#include "taskpool.h"

typedef struct FieldState {
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;
    u16 tileCols;
    u16 tileRows;
    u8 unk_14[0x04];
    FldActor actor;
    void* lockonTarget;
    s16 lockonDelay;
    u16 unk_6E;
    u32 flags;
    u16 unk_74;
    u16 unk_76;
    TaskPool tasks;
    TaskPool tasks2;
    TaskPool tasks3;
    TaskPool tasks4;
    TaskPool tasks5;
    s32 spawnX;
    s32 spawnY;
    u8 spawnAngle;
    u8 unk_E5[0x03];
} FieldState;

typedef char FieldState_size[(sizeof(FieldState) == 0xE8) ? 1 : -1];

extern FieldState* gFieldState;

#endif
