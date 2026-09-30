#ifndef GUARD_BOSS_BOOGIE_H
#define GUARD_BOSS_BOOGIE_H

#include "anim.h"
#include "obj.h"
#include "taskpool.h"
#include "battle_actor.h"

typedef struct BoogieWork {
    s32 state;
    s16 timer;
    u16 unk_006;
    ObjTiles* tiles;
    ObjPalette* palette;
    ObjPalette* palette2;
    AnimState anim;
    TaskPool tasks;
    BtlObj actor;
    s32 vx;
    s32 vy;
    s32 vz;
    s32 animationIndex;
    Task* dice;
    Task* task;
    Task* dice2;
    Task* dice3;
    u32 defeatStep;
    u8 cardRequested;
    u8 diceFollower;
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
    s32 vz;
    s32 speed;
    u8 angle;
    u8 unk_159[0x3];
    s32 scaleX;
    s32 scaleY;
    s32 y;
    u8 counted;
    u8 unk_169[0x3];
    BoogieWork* parent;
    u8 follower;
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

void BosBoogieApplyDiceFace(BoogieWork* work);
void SetBoogieAnimation(BoogieWork* work, s32 a, u16 b);
u8 ClampBoogiePosition(s32* a, s32* b);
void task_bos_boogie_0(BoogieWork* work);
u8 task_bos_boogie_1(BoogieWork* work);
void task_bos_boogie_2(BoogieWork* work);
void task_bos_boogie_3(BoogieWork* work);
void BosBoogieRemoveOtherEnemies(void);
void BosBoogieApplyGimmick(void);
u32 GetBoogieDiceState(void);

#endif
