#ifndef GUARD_MODE_EVENT_H
#define GUARD_MODE_EVENT_H

#include "mode.h"
#include "taskpool.h"
#include "types.h"

typedef struct EvtArg {
    u32 eventId : 8;
    u32 unk_08 : 8;
    u32 unk_10 : 16;
} EvtArg;

extern Mode gModeEventDebug;
extern Mode gModeEvent;
extern TaskPool gEventTaskPool;
extern u8 gEventPaused;
extern u32 gEventId;
extern u8 gEventEndStep;

void ShowEventEndMessage();
void func_08061FC8();
void func_0806250C();
void func_0806297C();
u8 func_080629CC();
void func_080629F8();
void SaveAfterEvent();
void func_08062D20();
void func_08062D3C();

#endif
