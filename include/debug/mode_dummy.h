#ifndef GUARD_MODE_DUMMY_H
#define GUARD_MODE_DUMMY_H

#include "types.h"
typedef struct DummyEntry {
    const char* name;
    const char* desc;
    u16 action;
} DummyEntry;

void mode_dummy_0(u32 arg);
void DummyUpdateExit(void);
void mode_dummy_1(void);
void mode_dummy_2(void);

#endif /* GUARD_MODE_DUMMY_H */
