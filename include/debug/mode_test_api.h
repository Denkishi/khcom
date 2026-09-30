#ifndef GUARD_MODE_TEST_API_H
#define GUARD_MODE_TEST_API_H

#include "types.h"

void DebugTextPrint(u8 x, u8 y, u32 c, const char* s);
void DebugTextDraw(u8 bg);
void DebugTextInit(u8 bg, u16 b, u16 c);
void DebugTextPrintNumber(u8 x, u8 y, u32 c, u16 v);
s32 VectorLength2D(s32 a, s32 b);
s32 NormalizeVector2D8(s32* x, s32* y);
u16 GetCardMooglePointValue(u16 a);
u16 GetCardCpCost(u16 a);

#endif
