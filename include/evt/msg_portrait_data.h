#ifndef GUARD_MSG_PORTRAIT_DATA_H
#define GUARD_MSG_PORTRAIT_DATA_H

#include "anim.h"
#include "types.h"

typedef struct MsgFaceAnim {
    void* tiles;
    void* palette;
    void** gfxTable;
    AnimHeader** anims;
    u8 animCount;
    u8 animFlags;
    u8 unk_12[2];
} MsgFaceAnim;

extern const MsgFaceAnim* gMsgFaceAnims[62];

#endif
