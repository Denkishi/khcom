#ifndef GUARD_CARD_LABEL_DATA_H
#define GUARD_CARD_LABEL_DATA_H

#include "card_ui_types.h"
#include "types.h"

typedef struct HcEffectDef {
#ifdef VERSION_EU
    void** tiles;
    void*** sprites;
#else
    void* tiles;
    u32 tilesSize;
    void** sprites;
#endif
    u16 spriteIndex;
    u16 count;
} HcEffectDef;

extern const HcEffectDef gHcEffectDefs[];
extern const SpriteFrameResourceDef gStockNameSprites[];

#endif
