#ifndef GUARD_BATTLE_ACTOR_H
#define GUARD_BATTLE_ACTOR_H

#include "battle_actor_types.h"
#include "types.h"

struct EmyKind;
struct AnimDef;

void SetBattleZoom(u16 a, s32 b, s32 c, s32 d);
void AnimChangeWithDef(const struct AnimDef* tbl, void* a, u16 i, u16 j, void* obj);
void WorldToScreen(s16* x, s16* y, s32 px, s32 py, s32 pz);
void CreateBtlPopTask(BtlObj* p, s16 b);
void MakeOpponentsHittable();
u32 ClampBattlePosition(s32* px, s32* py, s32 rx, s32 ry);
void SetBattleBounds(s32 xMin, s32 xMax, s32 yMin, s32 yMax);
s32 UpdateBtlObjReaction(BtlObj* p);
void ClearBtlObjActionFlags(BtlObj* p);
u16 GetBattleSpritePriorityFlags(s32 y);
void BeginBossDefeat(BtlObj* actor);
void EndBossDefeat();
void InitEnemyBtlObj(BtlObj* p, const struct EmyKind* d, s32 x, s32 y, s32 z);
void ReleaseEnemyBtlObj(BtlObj* obj);
void DropBossPrizes(BtlObj* p);
void DropEnemyPrizes(BtlObj* p);
void TryDropPremireCard(BtlObj* p);
void RequestEnemyCardUse(BtlObj* p);
void TryEnemyCardUse(BtlObj* p);
void SetBtlObjParent(BtlObj* p, BtlObj* v);
u8 ConsumeGimmickFlag(u8 a);
void SetBtlPaletteFadeExcluded(u8 a, u8 b);
void SetBtlObjUnhittable(BtlObj* p, u8 f);
void ExitBattle();
u8 ApplyBattleBounds(s32* a, s32* b, s32* c, s32* d);
void GetEnemyTargetPosition(BtlObj* a, s32* b, s32* c, s32* d);
u8 StepHitFlash(BtlObj* p);

struct HumWork;
struct HumSub;

void BtlWorkInit();
u8 IsPlayerOnPlatform(Collider* a);
void SetBattleActorPosition(s32 a, s32 b, s32 c);
u8 SpawnEnemy(s32 id, s32 x, s32 y, s32 z);
void AllocBattleTiles();
void ReleaseBattleTiles();
void SetGimmickFlag(u8 a);
void DropGimmickCard(u8 a, s32 x, s32 y, s32 z);
void SetGimmickTarget(s32 a, s32 b, s32 c);
void SetEnemyHpFromStats(BtlObj* a, s32 b, s32 c);
void SetEnemyJiminyFlag(BtlObj* p);
void HumDraw(struct HumWork* work);
void HumFaceTarget(struct HumWork* p, u16 n);
u8 HumMoveToward(struct HumWork* p, s32 x, s32 y, s32 spd);
u8 HumIsNearAreaEdge(struct HumWork* p, u16 b);
u8 HumIsInPlayerReach(struct HumWork* p, s16 a, u16 b, u16 r);
u8 HumChooseCardAction(struct HumWork* work, u16 interval, u16 offset, u16 width, u16 depth);
s32 HumResolveCardMove(struct HumWork* work);

#endif
