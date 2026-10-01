#ifndef GUARD_MONSGAGE_H
#define GUARD_MONSGAGE_H

#include "types.h"

typedef struct MonsgageWork {
    void* tiles;
    void* tiles2;
    void* palette;
    s32 value;
    s32 shownValue;
    void* gfx;
    void* gfx2;
    s16 timer;
    u8 unk_1E[0x2];
    u32 state;
    u8 visible;
    u8 unk_25[0x3];
} MonsgageWork;

void task_monsgage_0(MonsgageWork* work);
s32 task_monsgage_1(MonsgageWork* work);
void task_monsgage_2(MonsgageWork* work);
void task_monsgage_3(MonsgageWork* work);

#ifdef VERSION_EU
void* eu_0805E924(const void* strings);
void* eu_0805E968(void* text);
s32 eu_0805E9AC(void* text);

#define LANGSEL(x) eu_0805E924(x)
#else
#define LANGSEL(x) (x)
#endif

#endif /* GUARD_MONSGAGE_H */
