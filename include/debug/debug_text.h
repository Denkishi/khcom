#ifndef GUARD_DEBUG_TEXT_H
#define GUARD_DEBUG_TEXT_H

#include "types.h"

typedef struct DebugTextLine {
    u16 glyphs[61];
    u8 x;
    u8 y;
    u8 unk_7C;
    u8 length;
    u32 font;
} DebugTextLine;

typedef struct CharTile {
    u32 rows[8];
} CharTile;

extern u8* gDebugFont2Banks[2];

void DebugTextClearBg();
void func_0805F7B0(s32 a);
void DebugTextClearScreen();
void func_0805F7C8(u8 a);
void DebugTextPrintFont2(u8 x, u8 y, u16* s);
u8 DebugTextGetPixelShift(u8 a);
void DebugTextClearLines();
s32 DebugTextScrollUp(u8 bg, u8 b, u8 c, u8 d, u8 e);
void DebugTextLoadPalette(s32 a, const void* b, s32 c, u8 d);
void DebugTextInit(u8 bg, u16 b, u16 c);
void DebugTextSetMergeFirstGlyph(s32 a);
void DebugTextPrintXNumber(u8 x, u8 y, u32 c, u8 v);
void DebugTextPrintNumber(u8 x, u8 y, u32 c, u16 v);
void DebugTextPrint(u8 x, u8 y, u32 c, const char* s);
void DebugTextDrawAligned(u8 bg);
void DebugTextClear();
void DebugTextDraw(u8 bg);
void DebugTextFree();
void DebugTextDestroy();

#endif
