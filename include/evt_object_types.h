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
    s32 unk_10;
    u16 flags;
    u16 unk_16;
    struct AnimState* anim;
    u16 unk_1C;
    u8 unk_1E[0x02];
    s32 scaleX;
    s32 scaleY;
    u8 angle;
} EvtObj;

#endif
