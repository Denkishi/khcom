#ifndef GUARD_BOS_GA_H
#define GUARD_BOS_GA_H

#include "ga_types.h"
#include "types.h"

void task_bos_ga_2(GaWork* work);
void task_bos_ga_3(GaWork* work);
void task_bos_ga_0(GaWork* work, s32 arg);
u8 task_bos_ga_1(GaWork* work);
u16 BosGaAtan(s32 a);
s32 BosGaGetAngle(s32 x0, s32 y0, s32 x1, s32 y1);
void BosGaEntryUpdateFall(GaEntryWork* e);
void BosGaRequestState(GaWork* work, s32 state);
s32 BosGaEntryOffsetX(GaWork* work, s16 i);
s32 BosGaEntryOffsetY(GaWork* work, s16 i);
s32 BosGaEntryHomeX(GaWork* work, s16 i);
s32 BosGaEntryHomeY(GaWork* work, s16 i);
s32 BosGaEntryHomeZ(GaWork* work, s16 i);
void BosGaEntryResetHome(GaWork* work, s32 i);
void BosGaUpdateFacing(GaWork* work);
void BosGaEntryInit(GaWork* work, u32 i, s32 c);
void BosGaEntryRelease(GaEntryWork* e);
void BosGaReleaseBody();
void BosGaEntryDraw(GaWork* work, GaEntryWork* e);
u8 BosGaUpdateAssemble(GaWork* work);
u8 BosGaUpdateIdle(GaWork* work);
u8 BosGaUpdateWalk(GaWork* work);
u8 BosGaUpdateStomp(GaWork* work);
u8 BosGaUpdateThrust(GaWork* work);
u8 BosGaUpdateOrbit(GaWork* work);
u8 BosGaUpdateJump(GaWork* work);
u8 BosGaUpdateBodyChase(GaWork* work);
u8 BosGaUpdateBodyDash(GaWork* work);
u8 BosGaUpdateBodyJump(GaWork* work);
u8 BosGaUpdateGimmick(GaWork* work);
u8 BosGaUpdateDefeat(GaWork* work);
void BosGaEntryUpdate(GaWork* work, GaEntryWork* p);
extern u16 gBoss01objPalette[];
extern u16 gUnk_08F69BC4[];

#endif /* GUARD_BOS_GA_H */
