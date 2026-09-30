#ifndef GUARD_MODE_EVENT_H
#define GUARD_MODE_EVENT_H

#include "mode.h"
#include "taskpool.h"

typedef struct EvtArg {
    u32 eventId : 8;
    u32 unk_08 : 8;
    u32 unk_10 : 16;
} EvtArg;

extern Mode gModeEventDebug;
extern Mode gModeEvent;
extern TaskPool gEventTaskPool;
extern u32 gEventId;

void ShowEventEndMessage(void);
void func_08061FC8(void);
void func_0806250C(void);
void func_0806297C(void);
u8 func_080629CC(void);
void func_080629F8(void);
void SaveAfterEvent(void);
void func_08062D20(void);
void func_08062D3C(void);

#endif
