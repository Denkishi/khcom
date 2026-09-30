#ifndef GUARD_BATTLE_WORK_H
#define GUARD_BATTLE_WORK_H

#include "types.h"
#include "taskpool.h"
#include "battle_bounds.h"

#include "battle_actor_types.h"

typedef struct BtlWork {
    s32 viewX;
    s32 viewY;
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;
    u8 rotation;
    u8 unk_019;
    s16 zoomSteps;
    s32 zoomX;
    s32 zoomY;
    s32 scale;
    s32 zoomScale;
    TaskPool taskPools[3];
    u64 flags;
    u8 paused;
    u8 unk_071;
    s16 hitStop;
    s16 freezeTimer;
    u16 pendingHitStop;
    BtlObj* actor2;
    BtlObj* actor;
    ListPool pool;
    ListPool pool2;
    s32 phase;
    u8 soraOwnsPlay;
    u8 unk_0A5[0x03];
    BtlObj* actor3;
    BtlObj* actor4;
    s16 prizeCount;
    s8 stockMove;
    u8 fadeAmount;
    u8 areaUpdated;
    u8 unk_0B5[0x03];
    s32 x3;
    s32 y3;
    s32 z3;
    s16 areaHalfX;
    s16 areaHalfY;
    s16 areaHalfZ;
    u8 unk_0CA[0x02];
    s32 bossX;
    s32 bossY;
    s32 bossZ;
    s16 bossPriorityOffset;
    s16 xMin;
    s16 xMax;
    s16 yMin;
    s16 yMax;
    u8 lHeldFrames;
    u8 rHeldFrames;
    s16 phaseStep;
    u8 unk_0E6[0x02];
    Task* task;
    s16 enemyTileCount;
    u8 enemyCount;
    u8 rikuKeys;
    Collider* platform;
    s32 hcEffect;
    u16 hcEffectCount;
    u8 pendingLevelUps;
    u8 gimmickFlags;
    s32 fadeExcludedPalettes;
    s32 gimmickX;
    s32 gimmickY;
    s32 gimmickZ;
    s32 battleId;
    void* tiles;
    void* tiles2;
    void* tiles3;
    u8 unk_11C[0x04];
    s16 pendingEnemies;
    u8 unk_122[0x02];
    s32 damageScale;
    BtlBoundsCallback boundsCallback;
    s32 gravity;
    s32 targetX;
    s32 targetY;
    s32 targetZ;
    u8 savedProgression[0x88];
    u16 bg;
    u16 mapBg;
    s16 darkPoints;
    s8 breakDifference;
    u8 unk_1CB;
    u16 listSwitchTimer;
    u8 unk_1CE[0x02];
} BtlWork;

typedef char BtlWork_size[(sizeof(BtlWork) == 0x1D0) ? 1 : -1];

extern BtlWork* gBtlWork;
extern BtlWork* gRikuBtlWork;

#endif
