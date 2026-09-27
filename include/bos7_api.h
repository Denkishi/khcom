#ifndef GUARD_BOS7_API_H
#define GUARD_BOS7_API_H

#include "types.h"

struct Task;

typedef struct LstBitArg {
    s32 unk_00;
    s32 unk_04;
    s16* unk_08;
    u16* unk_0C;
    s16* unk_10;
    s32 x;
    s32 y;
    s32 z;
    s32 unk_20;
    s32 y2;
    s32 unk_28;
} LstBitArg;

typedef struct LstCtrArg {
    s16* unk_00;
    u16 unk_04;
    u16 unk_06;
    s32 unk_08;
    s32 x;
    s32 y;
    s32 z;
} LstCtrArg;

typedef struct LstFalArg {
    s32 unk_00;
    s32 x;
    s32 y;
    s32 z;
    u8 angle;
    u8 unk_11;
    s16 unk_12;
    u16* unk_14;
} LstFalArg;

typedef struct LstSnpArg {
    s32 x;
    s32 y;
    s32 z;
    s16 unk_0C;
} LstSnpArg;

void func_0810FF50(struct Task* t, s32 a, s32 b);
void func_0810FF64(struct Task* t, s32 a);
void func_0810FF6C(struct Task* t, s32 a);
u8 func_08110918(struct Task* task);
u8 func_08110938(struct Task* task);
s16 func_0811095C(struct Task* task, s16 a);
void func_08110984(struct Task* task);
void func_08110994(struct Task* task, s16 a);
void func_081109A8(struct Task* task);
u8 func_081109B8(struct Task* task, u8 a);
u8 func_08111F4C(struct Task* task);

#endif
