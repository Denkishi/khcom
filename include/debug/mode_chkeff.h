#ifndef GUARD_MODE_CHKEFF_H
#define GUARD_MODE_CHKEFF_H

#include "types.h"
#include "taskpool.h"

typedef struct ChkEffWork {
    TaskPool pool;
    s16 effectIndex;
    u8 paused;
    u8 unk_17;
    u16 scrollX;
    u16 scrollY;
    u8 rotation;
    u8 unk_1D[0x03];
    s32 scale;
    u16 alphaA;
    u16 alphaB;
} ChkEffWork;

void mode_chkeff_0();
void mode_chkeff_1();
void mode_chkeff_2();

#endif /* GUARD_MODE_CHKEFF_H */
