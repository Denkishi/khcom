#ifndef GUARD_BOS7_API_H
#define GUARD_BOS7_API_H

#include "types.h"

struct Task;

typedef struct LstBitArg {
    s32 kind;
    s32 index;
    s16* facing;
    u16* falCount;
    s16* unk_10;
    s32 x;
    s32 y;
    s32 z;
    s32 x2;
    s32 y2;
    s32 z2;
} LstBitArg;

typedef struct LstCtrArg {
    s16* unk_00;
    u16 count;
    u16 index;
    s32 delay;
    s32 x;
    s32 y;
    s32 z;
} LstCtrArg;

typedef struct LstFalArg {
    s32 kind;
    s32 x;
    s32 y;
    s32 z;
    u8 angle;
    u8 unk_11;
    s16 facing;
    u16* falCount;
} LstFalArg;

typedef struct LstSnpArg {
    s32 x;
    s32 y;
    s32 z;
    s16 facing;
} LstSnpArg;

void BosLstFldSetBgMode(struct Task* t, s32 a, s32 b);
void BosLstFldSetCameraMode(struct Task* t, s32 a);
void BosLstFldSetScrollSpeed(struct Task* t, s32 a);
u8 BosLstBitIsAlive(struct Task* task);
u8 BosLstBitHasShots(struct Task* task);
s16 BosLstBitMarkFirstAlive(struct Task* task, s16 a);
void BosLstBitStartHover(struct Task* task);
void BosLstBitStartFiring(struct Task* task, s16 a);
void BosLstBitStartReturn(struct Task* task);
u8 BosLstBitInterrupt(struct Task* task, u8 a);
u8 BosLstCtrIsActive(struct Task* task);

#endif
