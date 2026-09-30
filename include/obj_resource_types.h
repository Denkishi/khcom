#ifndef GUARD_OBJ_RESOURCE_TYPES_H
#define GUARD_OBJ_RESOURCE_TYPES_H

#include "types.h"

typedef struct ObjPaletteHeader {
    u8* src;
    u8 unk_04[0x02];
    u16 index;
    u16 count;
} ObjPaletteHeader;

#endif
