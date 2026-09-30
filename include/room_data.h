#ifndef GUARD_ROOM_DATA_H
#define GUARD_ROOM_DATA_H

#include "types.h"
#include "anim.h"
#include "battle_actor_types.h"
#include "boss_background_types.h"

typedef struct GaEntryDef {
    s32 hpScale;
    s32 offsetX;
    s32 offsetY;
    s32 offsetZ;
    u16 x2;
    u16 y2;
    void* owner;
    AnimHeader** anims;
    void** gfxTable;
    u16 spriteCount;
    u16 unk_22;
} GaEntryDef;

extern const EmyKind gBosGaEmyKind;
extern const GaEntryDef gGaEntryDefs[];
extern const BosMapConfig gBosMapConfig;
extern const s32 gBos5TanTable[];

#endif
