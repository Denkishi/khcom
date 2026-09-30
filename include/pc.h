#ifndef GUARD_PC_H
#define GUARD_PC_H

#include "types.h"
#include "battle_actor.h"
#include "engine_math.h"
#include "game.h"
#include "hum.h"
#include "pc_api.h"

typedef struct PcAcdDmgWork {
    s16 timer;
    s16 groundFrames;
    BtlObj* actor;
    u8 grounded;
    u8 unk_09[0x3];
} PcAcdDmgWork;

void CloudJumpOffset(CloudWork* work, s16 a, s32 b);

#endif /* GUARD_PC_H */
