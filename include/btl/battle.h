#ifndef GUARD_BATTLE_H
#define GUARD_BATTLE_H

#include "anim.h"
#include "battle_actor.h"
#include "types.h"
#include "listpool.h"
#include "taskpool.h"
#include "mode.h"
#include "battle_actor_types.h"
struct BtlObj;

enum BgFxFlag {
    BGFX_FLAG_FLIP_X = 0x1,
    BGFX_FLAG_ACTIVE = 0x2,
    BGFX_FLAG_IGNORE_ZOOM = 0x4,
    BGFX_FLAG_SCREEN_DIMMED = 0x8,
    BGFX_FLAG_ABOVE_SPRITES = 0x10,
    BGFX_FLAG_BELOW_SPRITES = 0x20
};

typedef struct BgFx {
    s32 bg;
    void (*update)();
    s16 timer;
    s16 steps;
    s16 unk_0C;
    s16 scaleYSteps;
    s32 x;
    s32 y;
    s32 z;
    s32 scaleX;
    s32 scaleY;
    u8 angle;
    u8 unk_25;
    u16 state;
    s32 targetX;
    s32 targetY;
    s32 targetZ;
    u16 flags;
    u16 endSignals;
    u8 priority;
    u8 unk_39[0x03];
    s32 unk_3C;
    s32 angleFixed;
    struct BtlObj* actor;
    s32 attack;
    s16 releaseFrames;
    u16 unk_4E;
} BgFx;

typedef struct EnemySpawnRequest {
    TaskDesc* desc;
    s32 x;
    s32 y;
    s32 z;
    u16 flags;
    u16 tileCount;
} EnemySpawnRequest;

typedef struct BtlPrizeSrc {
    s32 x;
    s32 y;
    s32 z;
    u8 unk_0C[0x06];
    u16 kind;
    u16 noTimeout;
    u8 unk_16[0x0A];
} BtlPrizeSrc;

typedef struct FieldTransitionWork {
    void* tiles;
    void* palette;
    AnimState anim;
    u16 initialized;
    u8 flipped;
    u8 unk_23;
} FieldTransitionWork;

typedef struct EnemyBaseStats {
    s16 hp;
    s16 attack;
    s16 exp;
    s16 unk_06;
} EnemyBaseStats;

typedef struct BattleAttackDef {
    s32 power;
    s32 knockbackSpeed;
    s32 knockbackLift;
    s32 hitStop;
    void (*hitEffect)(s32, s32, s32);
    u32 flags;
} BattleAttackDef;

extern s32 gUnk_02039DC0;
extern u16 gUnk_08F69BC4[];


void* ColliderGetPool(u32 type);
void HandleSoraCardInput();
void HandleTutorialCardInput();
void SetEnemyKindFlags(BtlObj* p);
void CreateHeartlessCardTask(void* p, s16 x, s16 y, s16 z, u16 n);
void BgFxReset();
void BgFxUpdateBase();
void FieldTransitionInit();
s32 ApplyAttackAt(s32 a, s32 b, s32 c, s32 d);
void BgFxUpdateFlash();
void BgFxUpdateStop();
void BgFxUpdateAnsemWave();
void BgFxUpdateGravityStrike();
void BgFxUpdateShockwave();
void BgFxUpdateGround();
BtlObj* BgFxGetSyncTarget();
void UpdateEnemyCardUse();
void BgFxUpdateEnemyDeath();
void BgFxUpdateZantetsuken();
void BgFxUpdateFadeOut();
void BgFxUpdateExplosion();
void BgFxUpdateGravity();
void BgFxUpdateFadeInOut();
void BgFxUpdateRagnarokCharge();
void BgFxUpdateBossDeathFlash();
void UseEnemyCard(u16 a);
void BgFxUpdateGas();
void BgFxUpdateRikuLimit();
void BgFxUpdateLaxeneBeam();
void BgFxUpdateAero();
void ColliderCheckPoolPairs(ListPool* a, ListPool* b);
s64 __ashldi3(s64 v, s32 n);
u8 GetStockMoveCount();

const EnemyBaseStats* GetEnemyBaseStats(u16 i);
s32 ResolveAttackHit(BtlObj* a, s32 b);

u8 GetRikuSelectedCardValue();
s32 GetRikuSelectedMove();
u8 GetRikuCardsLeft();
u8 GetActiveCardValue();
void RequestBossCardOpen();
void RequestBossCardClose();
extern Mode gModeChkbtl;

extern u8 gUnk_08935BC2[];
extern u8 gRik1bl01Tiles[];
extern u8 gRik1ll01Tiles[];
extern u8 gRik1fl01Tiles[];
extern u8 gUnk_0893416A[];
extern u8 gSor1bb01Tiles[];
extern u8 gSor1bl01Tiles[];
extern u8 gSor1ll01Tiles[];
extern u8 gSor1fl01Tiles[];
extern u8 gSor1ff01Tiles[];
extern u16 gRikuPalette[];
extern u16 gSoraPalette[];

u8 TryStartCardAction(BtlObj* p);
void VsBtlWorkInit();
void VsEndCardPlay();
void VsBattleUpdate();
void AbsorbAttack(BtlObj* a, BtlObj* b, const BattleAttackDef* c);

void func_080135EC(s32 x, s32 y, s32 z);
void BgFxStartFlashHit(s32 x, s32 y, s32 z);
void BgFxUpdateFlashHit();
void BgFxUpdateBlizzard();
void func_080146A8(s32 x, s32 y, s32 z);
void func_08014654();
void BgFxUpdateUrsulaBeam();
void BgFxUpdateFire();
void BgFxStartAxcelFireWall(s32 x, u8 f, s32 w);
void BgFxUpdateBind();
void BgFxUpdateAxcelFireWall();
void BgFxUpdateFireBurst();
void BgFxUpdateDsdEnergy();
void BgFxTornadoLiftBtlObj(BtlObj* p, BtlObj* o, u8 a, u8 b);
void BgFxUpdateTornado();
void BgFxUpdatePcShot();
void BgFxUpdateRikuLimitFinish();
void BgFxUpdateHanabira();
void BgFxUpdateKama();
void BgFxUpdateTrinityLimitBlast();
void BgFxUpdateRagnarokShot();
void BgFxUpdateThunder();
void BgFxUpdateDumboSplash();
void BgFxUpdateWideThunder();
void BgFxUpdateHoly();
void BgFxUpdateSync();
void BgFxUpdateRikuDarkMode();
void BgFxStartFireHit(s32 x, s32 y, s32 z);
void BgFxStartBlizzardHit(s32 x, s32 y, s32 z);
void BgFxStartEnemyHit(s32 x, s32 y, s32 z);
void BgFxStartRikuHit(s32 x, s32 y, s32 z);
void BgFxStartSoraHit(s32 x, s32 y, s32 z);
void BgFxUpdateFullscreen();
void BgFxUpdateVixenIceFall();
u8 CreateBtlPrizeTasksCapped(BtlPrizeSrc* p, u16 b, s16 c, s16* n, s16* cnt);
void CreateBtlPrizeTasks(BtlPrizeSrc* p, u16 b, s16 c, s16* n);

s32 LevelUpMaxHp();
s32 LevelUpCp();
s32 LevelUpDp();
s32 LevelUpAp();
void AddExp(u16 a);
void BgFxUpdateTrinityLimit();
s32 ApplyAttackInFront(BtlObj* p, s16 h, s32 c);
void RequestSwitchRikuCardList();
u8 GetRikuStockCount();
u8 IsRikuSelectionEmpty();
u8 GetRikuCardListIndex();
u8 StepHitFlashSolid(BtlObj* p);

void BgFxReleaseEarly(s16 a);
void BgFxStartGuard(s32 x, s32 y, s32 z);
void BgFxStartLimit(s32 x, s32 y, s32 z, u8 f);
void BgFxUpdateFollowActor();
void EndCardPlay();

void func_08012214();
void ColliderClearPoolContacts(ListPool* pool);
u8 BgFxIsBlocked(u8 a);

u8 ColliderIsColliding(Collider* p);
s32 ApplyBtlObjHit(BtlObj* p);
void CreateGimmickCardTask(void* pool, s16 a, s16 b, s16 c, u16 d);

typedef struct BtlPrizeArgs {
    s32 x;
    s32 y;
    s32 z;
    u8 unk_0C[0x14];
} BtlPrizeArgs;

#endif /* GUARD_BATTLE_H */
