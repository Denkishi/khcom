#ifndef GUARD_MODE_TEST_H
#define GUARD_MODE_TEST_H

#include "mode.h"
#include "fld_types.h"
#include "evt_types.h"
#include "types.h"
#include "anim.h"

typedef struct DebugTextLine {
    u16 glyphs[61];
    u8 x;
    u8 y;
    u8 unk_7C;
    u8 length;
    u8 unk_7E[2];
    u32 font;
} DebugTextLine;

typedef struct CharTile {
    u32 rows[8];
} CharTile;

typedef struct LockonWork {
    void* tiles;
    void* palette;
    void* gfx;
    FldObj* targets[8];
    u8 targetCount;
    s8 selected;
    s8 prevSelected;
    u8 timer;
    u8 unk_30;
    u8 unk_31[3];
    AnimState anim;
    u8 unk_4C;
    u8 unk_4D[3];
} LockonWork;

s32 func_0805F93C(u8 bg, u8 b, u8 c, u8 d, u8 e);
void SioBtlOptionRecvSettings();

#ifndef VERSION_EU
extern Mode gModeTest;
#endif
void mode_test_0();
void mode_test_1();
void mode_test_2();
void LockonClearTargets(LockonWork* work);
void LockonGetDoorScreenPos(s32* x, s32* y);
void DebugTextClearBg();
void func_0805F7B0(s32 a);
void func_0805F7BC();
void func_0805F7C8(u8 a);
u8 DebugTextGetPixelShift(u8 a);
void DebugTextClearLines();
void DebugTextSetMergeFirstGlyph(s32 a);
void DebugTextPrintXNumber(u8 x, u8 y, u32 c, u8 v);
void task_lockon_0(LockonWork* work);
s8 LockonPickNearest(s32 a, s32 b, LockonWork* work, s8 n, s8* list);
u8 LockonIsInFront(u16 a, s32 b, s32 c, FldObj* d);
u8 task_lockon_1(LockonWork* work);
void task_lockon_2(LockonWork* work);
void task_lockon_3(LockonWork* work);
void DebugTextPrintFont2(u8 x, u8 y, u16* s);
void DebugTextDrawAligned(u8 bg);
void DebugTextFree();

extern u8* gDebugFont2Banks[2];
extern const u8* gUnk_09EE26F4;
extern const u8* gUnk_09EE26F8;
extern const u8* gUnk_09EE26FC;
extern const u8* gUnk_09EE2700;

extern s32* gLockonDoorPosition;
extern EventState* gEventState;

extern Mode gModeChkbtl;
extern u8 gBHpgagETiles[];
extern u16 gUnk_096148B8[];
extern u16 gBStatesPalette[];
extern u16 gUnk_08F69BE4[];

#endif /* GUARD_MODE_TEST_H */
