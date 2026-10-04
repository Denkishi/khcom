#ifndef GUARD_BOS_URSULA_H
#define GUARD_BOS_URSULA_H

#include "battle_actor_types.h"
#include "battle_bg_types.h"
#include "types.h"
#include "anim.h"
#include "taskpool.h"
#include "bos4_api.h"
#include "obj.h"

typedef struct UrsulaWork {
    u32 state;
    s16 timer;
    u8 unk_006[0x2];
    TaskPool tasks;
    Task* tako;
    Task* tako2;
    BtlObj obj;
    const u16** mapBlocks;
    s32 bobZ;
    s32 bobTarget;
    u16 bobTimer;
    u16 gimmickTimer;
    u8 unk_144[0x4];
    u32 gimmickCameraX;
    u32 gimmickViewY;
    u32 sinkZ;
    u32 gimmickCameraY;
    u16 sinkSteps;
    u16 riseSteps;
    u16 unk_15C;
    u16 gimmickDelay;
    u8 takoRecoverPending;
    u8 unk_161[0x3];
} UrsulaWork;

void BosUrsulaStartAttack(s32 a);
u8 BosUrsulaIsAttacking();
u8 BosUrsulaIsCharging();
u16 BosUrsulaGetCardInterval();
void task_bos_ursula_3(UrsulaWork* work);

typedef struct UrsulaTakoWork {
    void* tiles;
    void* palette;
    void* palette2;
    AnimState anim;
    u16 animBase;
    u8 unk_026[0x2];
    BtlObj obj;
    u32 state;
    u16 timer;
    u8 isLeft;
    u8 unk_13F[0x1];
    Collider collider;
    Collider collider2;
    s32 collider2OffsetX;
    s32 offsetX;
    s32 offsetZ;
} UrsulaTakoWork;

extern u8 gUnk_0979D0B6[];
extern u16 gUnk_0984B0D8[];
void BosUrsulaUpdateMapBlocks(UrsulaWork* work);
void task_bos_ursula_2(UrsulaWork* work);
u8 BosUrsulaIsGuarded(UrsulaWork* work);
u8 BosUrsulaMoveForward(UrsulaWork* work);
void BosUrsulaUpdateBob(UrsulaWork* work);
s32 BosUrsulaChooseAttackPhase0(UrsulaWork* work);
s32 BosUrsulaChooseAttackPhase1(UrsulaWork* work);
s32 BosUrsulaChooseAttack(UrsulaWork* work);
void BosUrsulaRecoverPendingTakos(UrsulaWork* work);
void BosUrsulaUpdateTakoRecovery(UrsulaWork* work);
void task_bos_ursula_tako_3(UrsulaTakoWork* work);
u8 BosUrsulaTakoIsBusy(UrsulaTakoWork* work);
void BosUrsulaTakoEndDown(UrsulaTakoWork* work);
u8 BosUrsulaTakoIsStoodOn(UrsulaTakoWork* work);

typedef struct UrsulaMapanimeWork {
    BosMapanimeState anim;
    u32 attack;
    TaskPool tasks;
    Task* task;
    u8 attackSpawned;
    u8 unk_029[0x3];
} UrsulaMapanimeWork;

typedef struct UrsulaMapWork {
    s32 viewYMax;
    s32 viewYMaxTarget;
    u16 viewYMaxSteps;
    u8 unk_0A[0x2];
} UrsulaMapWork;

typedef struct UrsulaBorderWork {
    ObjTiles* tiles;
    ObjPalette* palette;
} UrsulaBorderWork;

void task_bos_ursula_map_0(UrsulaMapWork* work, BattleBackgroundDef* arg);
u8 task_bos_ursula_map_1(UrsulaMapWork* work);

typedef struct UrsulaBacktakoWork {
    ObjTiles* tiles;
    ObjPalette* palette;
    AnimState anim;
    u16 animBase;
    u8 isLeft;
    u8 unk_023[0x1];
    u32 offsetX;
    u32 offsetZ;
    u32 x;
    u32 y;
    u32 z;
    u32 x2;
    u32 y2;
    u32 z2;
} UrsulaBacktakoWork;

u8 BosUrsulaIsFacingLeft();
u8 BosUrsulaIsGimmickActive();
u8 BosUrsulaObjectsGone();
u8 BosUrsulaIsGimmickStarting();
u8 func_080DC5B0();
u32 BosUrsulaGetHpPhase();
u8 BosUrsulaIsDefeated();
s32 BosUrsulaGetTakoPlatformRadius(u8 a);
void task_bos_ursula_border_0(UrsulaBorderWork* work);
void task_bos_ursula_border_3(UrsulaBorderWork* work);
u8 task_bos_ursula_backtako_1(UrsulaBacktakoWork* work);
void task_bos_ursula_backtako_3(UrsulaBacktakoWork* work);
void task_bos_ursula_map_3();
s32 task_bos_ursula_border_1();
void task_bos_ursula_mapanime_0(UrsulaMapanimeWork* work);
u8 task_bos_ursula_mapanime_1(UrsulaMapanimeWork* work);
void task_bos_ursula_mapanime_2(UrsulaMapanimeWork* work);
void task_bos_ursula_mapanime_3(UrsulaMapanimeWork* work);
void task_bos_ursula_tako_2(UrsulaTakoWork* work);
void task_bos_ursula_tako_0(UrsulaTakoWork* work, u8* arg);
u8 task_bos_ursula_tako_1(UrsulaTakoWork* work);
void task_bos_ursula_0(UrsulaWork* work);
void task_bos_ursula_backtako_0(UrsulaBacktakoWork* work, u8* arg);
extern u8 gUnk_0979E344[];
void task_bos_ursula_border_2(UrsulaBorderWork* work);
extern u8 gUnk_0979D090[];
extern u8 gUnk_0979D8B8[];
extern u16 gUnk_0984AFF8[];
void task_bos_ursula_backtako_2(UrsulaBacktakoWork* work);
void BosUrsulaTakoGetPosition(s32* a, s32* b, s32* c, UrsulaTakoWork* work);
void BosUrsulaBacktakoGetPosition(s32* a, s32* b, s32* c, UrsulaBacktakoWork* work);
s32 BosUrsulaChooseAttackPhase2(UrsulaWork* work);
u8 task_bos_ursula_1(UrsulaWork* work);

#endif /* GUARD_BOS_URSULA_H */
