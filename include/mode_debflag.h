#ifndef GUARD_MODE_DEBFLAG_H
#define GUARD_MODE_DEBFLAG_H

#include "system_state.h"

#include "map_api.h"
#include "mode_test_api.h"

#include "types.h"
#include "key.h"
#include "mode.h"
#include "engine.h"
typedef struct DebugFlag {
    const char* name;
    u32 mask;
} DebugFlag;
extern u8 gDebflagReturnToMap;
extern const DebugFlag gDebugFlagList[];
extern const DebugFlag gDebugFlagListMap[];

void mode_debflag_0(s32 arg);
void mode_debflag_1(void);
void mode_debflag_2(void);

#endif /* GUARD_MODE_DEBFLAG_H */
