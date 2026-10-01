#ifndef GUARD_PC_H
#define GUARD_PC_H

#include "types.h"
#include "battle_actor_types.h"

typedef struct PcAcdDmgWork {
    s16 timer;
    s16 groundFrames;
    BtlObj* actor;
    u8 grounded;
    u8 unk_09[0x3];
} PcAcdDmgWork;

#endif /* GUARD_PC_H */
