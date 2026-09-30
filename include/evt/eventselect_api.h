#ifndef GUARD_EVENTSELECT_API_H
#define GUARD_EVENTSELECT_API_H

#include "types.h"

struct EventCharaWork;
struct EventSoundMix;

extern struct EventSoundMix* gEventSoundMix;

void SetEventSoundPosition(u16 song, s16 x, s16 y);
void CreateTinkerbellTask(struct EventCharaWork* p);
void CreateDownTask(struct EventCharaWork* p);
void CreateSmokeTask(struct EventCharaWork* p);
void CreateExclamationTask(struct EventCharaWork* p);
void CreateBalloonTask(struct EventCharaWork* p);
void CreateQuestionTask(struct EventCharaWork* p);
void CreateGlowNoseTask(struct EventCharaWork* p);
void CreateHanabiraTask(struct EventCharaWork* p);

#endif
