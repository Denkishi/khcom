#ifndef GUARD_MODE_TEST_H
#define GUARD_MODE_TEST_H

#include "mode.h"
#include "evt_types.h"
#include "types.h"

#ifndef VERSION_EU
extern Mode gModeTest;
#endif
void mode_test_0();
void mode_test_1();
void mode_test_2();

extern EventState* gEventState;

extern Mode gModeChkbtl;
extern u8 gBHpgagETiles[];
extern u16 gUnk_096148B8[];
extern u16 gBStatesPalette[];
extern u16 gUnk_08F69BE4[];

#endif /* GUARD_MODE_TEST_H */
