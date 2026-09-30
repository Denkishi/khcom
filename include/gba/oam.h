#ifndef GUARD_GBA_OAM_H
#define GUARD_GBA_OAM_H

#include "types.h"

#define OAM_SHAPE_SQUARE     0x0000
#define OAM_SHAPE_HORIZONTAL 0x4000
#define OAM_SHAPE_VERTICAL   0x8000
#define OAM_SHAPE_MASK       0xC000
#define OAM_SIZE(n)          ((n) << 14)

#define OAM_SHAPE_SIZE(shape, size) (((u32)OAM_SIZE(size) << 16) | (shape))

#endif
