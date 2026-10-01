#ifndef GUARD_MODE_VSBATTLE_H
#define GUARD_MODE_VSBATTLE_H

#include "hum_types.h"
#include "enemy_types.h"
#include "types.h"

typedef struct VsTaskArg {
    s32 side;
    u32 mainSide : 8;
} VsTaskArg;

extern u16 gVsBattleMinY;
extern u16 gVsBattleMaxY;
extern u16 gVsBattleHalfWidth;
extern u8 gUnk_02039B98;
extern u8 gUnk_08F69BC4[];

void VsBattleUpdate();
void VsBtlWorkInit();

void SetRikuReloadCharging();

void mode_vsbattle_0(u32 mode);
void mode_vsbattle_1();
void mode_vsbattle_2();
void func_0800C6B0();
void func_0800C6B4();
void PlayVsBattleBgm();
void EmyStartKnockback(EmyWork* work);
void HumSubReleaseGraphics(HumSub* sub);
void HumStartKnockback(HumWork* work);
void HumSubUpdateAnimation(HumSub* sub);

#endif
