#ifndef GUARD_MODE_H
#define GUARD_MODE_H

#include "types.h"

enum ModeFlag {
    MODE_FLAG_BLANK_PENDING = 0x1,
    MODE_FLAG_DISPLAY_HELD = 0x2,
    MODE_FLAG_TRANSITION_ACTIVE = 0x4,
    MODE_FLAG_STARTED = 0x8,
    MODE_FLAG_HEAP_RESET = 0x10
};

typedef void (*ModeInitFunc)(s32 arg);
typedef void (*ModeFunc)(void);

typedef struct Mode {
    const char* name;
    ModeInitFunc init;
    ModeFunc update;
    ModeFunc exit;
} Mode;

void ModeRequest(Mode* mode, s32 arg);
void ModeUpdate(void);
void ModeRequestHeapReset(Mode* mode, s32 arg);
void DebugTextLoadPalette(s32 a, void* b, s32 c, u8 d);
void DebugTextClear(void);
void DebugTextDestroy(void);

extern Mode gModeDebug;
extern Mode gModeChkobj;
extern Mode gModeChkeff;
extern Mode gModeDummy;
extern Mode gModeDebflag;
extern Mode gModeVsbattle;

u8 IsModeStarted(void);
void ModeClearTransitionCallback(void);
void SetModeUpdate(void (*fn)(void));
#ifdef VERSION_EU
void eu_0800115C(void);
#endif
void ModeSetTransitionCallback(void (*a)(void), void (*b)(void));
void ModeFlushDisplay(void);
void ModeRunVBlankCallbacks(void);

#ifdef VERSION_EU
void ModeInit(u8 a);
#else
void ModeInit(void);
#endif

#endif
