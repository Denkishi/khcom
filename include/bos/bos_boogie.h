#ifndef GUARD_BOS_BOOGIE_H
#define GUARD_BOS_BOOGIE_H

#include "anim.h"
#include "obj.h"
#include "taskpool.h"
#include "battle_actor_types.h"
#include "types.h"

typedef struct BoogieWork {
    s32 state;
    s16 timer;
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
} BoogieWork;

typedef struct BoogieDiceWork {
    u32 state;
    s16 timer;
    ObjTiles* tiles;
    ObjPalette* palette;
    ObjPalette* palette2;
    AnimState anim;
    TaskPool tasks;
    BtlObj obj;
    s32 vz;
    s32 speed;
    u8 angle;
    s32 scaleX;
    s32 scaleY;
    s32 y;
    u8 counted;
    BoogieWork* parent;
    u8 follower;
} BoogieDiceWork;

typedef struct StatusObjDef {
    void* sprites;
    u16 spriteCount;
} StatusObjDef;

typedef struct StatusAnimDef {
    AnimHeader** anims;
    void** gfxTable;
    void* tiles;
    u16 animId;
} StatusAnimDef;

void BosBoogieApplyDiceFace(BoogieWork* work);
void SetBoogieAnimation(BoogieWork* work, s32 index, u16 flags);
u8 ClampBoogiePosition(s32* x, s32* y);
void task_bos_boogie_0(BoogieWork* work);
u8 task_bos_boogie_1(BoogieWork* work);
void task_bos_boogie_2(BoogieWork* work);
void task_bos_boogie_3(BoogieWork* work);
void BosBoogieRemoveOtherEnemies();
void BosBoogieApplyGimmick();
u32 GetBoogieDiceState();

#endif
