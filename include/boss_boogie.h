#ifndef GUARD_BOSS_BOOGIE_H
#define GUARD_BOSS_BOOGIE_H

#include "anim.h"
#include "obj.h"
#include "taskpool.h"
#include "battle_actor.h"

typedef struct BoogieWork {
    s32 unk_000;
    s16 timer;
    u16 unk_006;
    ObjTiles* tiles;
    ObjPalette* palette;
    ObjPalette* palette2;
    AnimState anim;
    TaskPool tasks;
    BtlObj actor;
    s32 unk_150;
    s32 unk_154;
    s32 unk_158;
    s32 animationIndex;
    Task* dice;
    Task* task;
    Task* dice2;
    Task* dice3;
    u32 unk_170;
    u8 unk_174;
    u8 unk_175;
    u8 unk_176[2];
} BoogieWork;

typedef struct BoogieDiceWork {
    u32 state;
    u16 timer;
    u8 unk_006[0x2];
    ObjTiles* tiles;
    ObjPalette* palette;
    ObjPalette* palette2;
    AnimState anim;
    TaskPool tasks;
    BtlObj obj;
    s32 unk_150;
    s32 unk_154;
    u8 angle;
    u8 unk_159[0x3];
    s32 unk_15C;
    s32 unk_160;
    s32 y;
    u8 unk_168;
    u8 unk_169[0x3];
    BoogieWork* parent;
    u8 unk_170;
    u8 unk_171[0x3];
} BoogieDiceWork;

typedef struct StatusObjDef {
    void* sprites;
    u16 spriteCount;
    u16 unk_06;
} StatusObjDef;

typedef struct StatusAnimDef {
    AnimHeader** anims;
    void** gfxTable;
    void* tiles;
    u16 animId;
    u16 unk_0E;
} StatusAnimDef;

void func_080D8F14(BoogieWork* work);
void SetBoogieAnimation(BoogieWork* work, s32 a, u16 b);
u8 ClampBoogiePosition(s32* a, s32* b);
void task_bos_boogie_0(BoogieWork* work);
u8 task_bos_boogie_1(BoogieWork* work);
void task_bos_boogie_2(BoogieWork* work);
void task_bos_boogie_3(BoogieWork* work);
void func_080D9A14(void);
void func_080D9A58(void);
u32 GetBoogieDiceState(void);

#endif
