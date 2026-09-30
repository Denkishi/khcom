#ifndef GUARD_MODE_WLOGO_H
#define GUARD_MODE_WLOGO_H

#include "types.h"

typedef struct WLogoTaskWork {
    u8 worldId;
    u8 unk_01[3];
    s32 cameraOffsetY;
    s16 timer;
    u8 unk_0A[2];
} WLogoTaskWork;

#endif
