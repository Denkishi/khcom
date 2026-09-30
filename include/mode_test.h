#include "event_index_data.h"
#include "mode.h"
#include "taskpool.h"
#include "card_def_data.h"
#include "registration_data.h"
#include "system_state.h"
#ifndef GUARD_MODE_TEST_H
#define GUARD_MODE_TEST_H

#include "msg_types.h"

#include "field_state.h"

#include "continue_types.h"

#include "fld_types.h"

#include "evt_types.h"

#include "card_types.h"

#include "card_api.h"

#include "map_api.h"
#include "mode_test_api.h"

#include "fade.h"
#include "btl_effect.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "display.h"
#include "types.h"
#include "malloc.h"
#include "engine_math.h"
#include "listpool.h"
#include "battle_work.h"
#include "game_state.h"
#include "key.h"
#include "anim.h"
#include "mode.h"
#include "mode_battle_data.h"
#include "taskpool.h"
#include "gba/syscall.h"
#include "m4a.h"
#include "bos4_api.h"
#include "btl_api.h"

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

#ifdef VERSION_EU
typedef struct FrdPoohBody {
    s32 unk_00;
    s32 x;
    s32 y;
    s32 z;
    s32 ground;
    u8 unk_14[0x20];
    u64 flags;
    u8 unk_3C[4];
    u8 particles[0x8C];
    u16 depth;
    u8 unk_CE[0x42];
} FrdPoohBody;

typedef struct FrdPoohWork {
    TaskPool tasks;
    BtlObj* actor;
    void* tiles;
    void* palette;
    FrdPoohBody body;
    AnimState anim;
    s32 state;
    u8 side;
    u8 card;
    s16 counter;
    s32 targetX;
    s32 targetY;
    s32 velocity;
    s32 speed;
    u8 bounce;
    u8 unk_161[3];
    s32 bob;
    s32 animcounter;
    s32 scale;
} FrdPoohWork;

typedef struct FrdPoohArgs {
    u16 card;
    u8 side;
    u8 unk_03;
} FrdPoohArgs;

extern u8 gPoohPalette[];
extern const AnimDef gFrdPoohAnimDefsEu[];

#endif

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
void SioBtlOptionRecvSettings(void);

#ifndef VERSION_EU
extern Mode gModeTest;
#endif
void mode_test_0(void);
void mode_test_1(void);
void mode_test_2(void);
void LockonClearTargets(LockonWork* w);
void func_0805F728(s32* x, s32* y);
void DebugTextClearBg(void);
void func_0805F7B0(s32 a);
void func_0805F7BC(void);
void func_0805F7C8(u8 a);
u8 func_0805F8F0(u8 a);
void DebugTextClearLines(void);
void func_0805FB78(s32 a);
void func_0805FB84(u8 x, u8 y, u32 c, u8 v);
void task_lockon_0(LockonWork* w);
s8 LockonPickNearest(s32 a, s32 b, LockonWork* w, s8 n, s8* list);
u8 LockonIsInFront(u16 a, s32 b, s32 c, FldObj* d);
u8 task_lockon_1(LockonWork* w);
void task_lockon_2(LockonWork* w);
void task_lockon_3(LockonWork* w);
void DebugTextPrintFont2(u8 x, u8 y, u16* s);
void func_08060470(u8 bg);
void DebugTextFree(void);

extern u8* gDebugFont2Banks[2];
extern u8* gUnk_09EE26F4;
extern u8* gUnk_09EE26F8;
extern u8* gUnk_09EE26FC;
extern u8* gUnk_09EE2700;

extern s32* gLockonDoorPosition;
extern EventState* gEventState;

extern Mode gModeChkbtl;
extern u8 gBHpgagETiles[];
extern u8 gUnk_096148B8[];
extern u8 gBStatesPalette[];
extern u8 gUnk_08F69BE4[];

#endif /* GUARD_MODE_TEST_H */
