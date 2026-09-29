#include "event_index_data.h"
#include "card_localized_data.h"
#include "registration_data.h"
#ifndef GUARD_MODE_EVENTSELECT_H
#define GUARD_MODE_EVENTSELECT_H


#include "card_api.h"

#include "msg_api.h"
#include "mode_test_api.h"

#include "eventselect_api.h"

#include "text.h"
#include "fade.h"
#include "obj_api.h"
#include "display.h"
#include "types.h"
#include "engine_math.h"
#include "listpool.h"
#include "key.h"
#include "taskpool.h"
#include "gba/syscall.h"
#include "malloc.h"
#include "m4a.h"
#include "evt_types.h"
#include "event_chara_types.h"
#include "game.h"
#include "card.h"
#include "mode.h"
#include "anim.h"

typedef struct UnkStruct_02039DD0 {
    s16 pan;
    u16 volume;
} UnkStruct_02039DD0;

typedef struct DownWork {
    s32 unk_00[8];
    s32 unk_20[8];
    u8 unk_40[8];
    u16 angle[8];
} DownWork;

typedef struct EvSoundWork {
    const EvSoundCue* soundCues;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    s32 unk_08;
} EvSoundWork;

typedef struct EventDebugWork {
    void* tiles;
    void* palette;
    u16 digits[16];
    u8 digitCount;
} EventDebugWork;

typedef struct EffectWork {
    EventCharaWork* actor;
    void* tiles;
    void* palette;
    void* gfx;
    DownWork* down;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    s32 z2;
    s32 vx;
    s32 vz;
    u16 unk_44;
    u16 unk_46;
    u8 unk_48;
    u8 state;
    u8 unk_4A[0x02];
    TaskPool tasks;
} EffectWork;

extern EventState* gEventState;
extern u8 gMaruxhaBtEffPalette[];
extern u8 gMaruxhaBtEff2Tiles[];
extern const EventCharaParams gUnk_0903380C[];
extern const char gUnk_08F70990[];
#ifdef VERSION_EU
#endif

void mode_eventselect_0(void);
void mode_eventselect_1(void);
void mode_eventselect_2(void);
void Hanabira_0(EffectWork* w, EventCharaWork* chara);
s32 Hanabira_1(EffectWork* w);
void Hanabira_2(EffectWork* w);
void Hanabira_3(EffectWork* w);
void Hanabira_c_0(EffectWork* w, EventCharaWork* chara);
s32 Hanabira_c_1(EffectWork* w);
void Hanabira_c_2(EffectWork* w);
void Hanabira_c_3(EffectWork* w);
void smoke_0(EffectWork* w, EventCharaWork* chara);
void Exclamation_0(EffectWork* w, EventCharaWork* chara);
void balloon_0(EffectWork* w, EventCharaWork* chara);
s32 func_08075720(EffectWork* w);
s32 Exclamation_1(EffectWork* w);
void EffectDrawObj(EffectWork* w);
void EffectReleaseObj(EffectWork* w);
void Question_0(EffectWork* w, EventCharaWork* chara);
void func_080758D0(EffectWork* w, EventCharaWork* chara);
s32 Question_1(EffectWork* w);
s32 func_080759B0(EffectWork* w);
void func_080759E0(EffectWork* w);
void func_08075A54(EffectWork* w);
void GlowNose_0(EffectWork* w, EventCharaWork* chara);
s32 GlowNose_1(EffectWork* w);
void GlowNose2_0(EffectWork* w, EventCharaWork* chara);
s32 GlowNose2_1(EffectWork* w);
void down_0(EffectWork* w, EventCharaWork* chara);
s32 down_1(EffectWork* w);
s32 down_2(EffectWork* w);
void down_3(EffectWork* w);
void Tinkerbell_0(EffectWork* w, EventCharaWork* chara);
s32 Tinkerbell_1(EffectWork* w);
void Tinkerbell_2(EffectWork* w);
void Tinkerbell_3(EffectWork* w);
void CreateDownTask(EventCharaWork* p);
void CreateSmokeTask(EventCharaWork* p);
void CreateExclamationTask(EventCharaWork* p);
void CreateBalloonTask(EventCharaWork* p);
void CreateQuestionTask(EventCharaWork* p);
void CreateGlowNoseTask(EventCharaWork* p);
void CreateGlowNose2Task(EventCharaWork* p);
void CreateHanabiraTask(EventCharaWork* p);
void EV_SOUND_0(EvSoundWork* w, u8* arg);
s32 EV_SOUND_1(EvSoundWork* w);
void EV_SOUND_2(void);
void EV_SOUND_3(void);
void func_080760D8(EvSoundWork* w);
void Event_Debug_0(EventDebugWork* work);
s32 Event_Debug_1(EventDebugWork* work);
void Event_Debug_2(EventDebugWork* work);
void Event_Debug_3(EventDebugWork* work);

s16 GetEventListLength(u8 a);

#endif
