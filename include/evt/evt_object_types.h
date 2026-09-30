#ifndef GUARD_EVT_OBJECT_TYPES_H
#define GUARD_EVT_OBJECT_TYPES_H

#include "types.h"

struct AnimState;
struct EvtObjAnim;

typedef struct EvtObj {
    const struct EvtObjAnim* animEntry;
    s32 x;
    s32 y;
    s32 z;
    s32 groundZ;
    u16 flags;
    u16 drawFlags;
    struct AnimState* anim;
    u16 paletteIndex;
    u8 unk_1E[0x02];
    s32 scaleX;
    s32 scaleY;
    u8 angle;
} EvtObj;

#endif
