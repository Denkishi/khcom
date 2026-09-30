#ifndef GUARD_PC_SPRITE_TYPES_H
#define GUARD_PC_SPRITE_TYPES_H

#include "types.h"

typedef struct PcSpriteDef {
    u16 unk_00;
    u16 attr0;
    u16 attr1;
    u16 attr2;
} PcSpriteDef;

typedef char PcSpriteDef_size[(sizeof(PcSpriteDef) == 8) ? 1 : -1];

#endif
