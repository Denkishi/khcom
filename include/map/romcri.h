#ifndef GUARD_ROMCRI_H
#define GUARD_ROMCRI_H

#include "types.h"
#include "formation_types.h"

typedef struct RomcriEffWork {
    s16 timer;
    u8 angle;
    u8 unk_03;
} RomcriEffWork;

typedef struct RomcriEff2Work {
    s16 timer;
    u8 angle;
    u8 frame;
} RomcriEff2Work;

u16 GetBtlFormEntryTileCount(const BtlFormEntry* list);

#endif /* GUARD_ROMCRI_H */
