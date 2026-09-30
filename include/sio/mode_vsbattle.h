#ifndef GUARD_MODE_VSBATTLE_H
#define GUARD_MODE_VSBATTLE_H

#include "task_descriptors.h"
#include "registration_data.h"

#include "hum_types.h"

#include "enemy_types.h"

#include "chara_types.h"

#include "card_api.h"

#include "btl_effect.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "display.h"
#include "types.h"
#include "engine_math.h"
#include "battle_work.h"
#include "game_state.h"
#include "anim.h"
#include "taskpool.h"
#include "m4a.h"

typedef struct VsTaskArg {
    s32 side;
    u32 mainSide : 8;
} VsTaskArg;

extern u16 gVsBattleMinY;
extern u16 gVsBattleMaxY;
extern u16 gVsBattleHalfWidth;
extern u8 gUnk_02039B98;
extern u8 gUnk_08F69BC4[];

void VsBattleUpdate(void);
void VsBtlWorkInit(void);

void SetRikuReloadCharging(void);

void mode_vsbattle_0(u32 mode);
void mode_vsbattle_1(void);
void mode_vsbattle_2(void);
void func_0800C6B0(void);
void func_0800C6B4(void);
void PlayVsBattleBgm(void);
void EmyStartKnockback(EmyWork* work);
void HumSubReleaseGraphics(HumSub* sub);
void HumStartKnockback(HumWork* work);
void HumSubUpdateAnimation(HumSub* sub);

#endif
