#ifndef GUARD_CARD_UI_TYPES_H
#define GUARD_CARD_UI_TYPES_H

#include "types.h"
#include "anim.h"

struct ObjTiles;
struct ObjPalette;

typedef struct CardUiSpriteState {
    struct ObjTiles* tiles;
    struct ObjPalette* palette;
    AnimState anim;
    void* gfx;
} CardUiSpriteState;

typedef struct MapCardUiResources {
    struct ObjTiles* tiles;
    struct ObjTiles* extraTiles;
    u8 unk_08[4];
    struct ObjPalette* palette;
    void* gfx;
    void** sprites;
    AnimState anim;
} MapCardUiResources;

typedef char CardUiSpriteState_size[(sizeof(CardUiSpriteState) == 0x24) ? 1 : -1];
typedef char MapCardUiResources_size[(sizeof(MapCardUiResources) == 0x30) ? 1 : -1];

typedef struct LayeredCardSprite {
    struct ObjTiles* tiles;
    struct ObjTiles* tiles2;
    struct ObjTiles* tiles3;
    struct ObjPalette* palette;
    struct ObjPalette* palette2;
    struct ObjPalette* palette3;
    void* gfx;
    void* gfx2;
    void* gfx3;
    s32 x;
    s32 y;
} LayeredCardSprite;

typedef struct EventKeyCard {
    LayeredCardSprite sprite;
    u16 unk_2C;
    u16 total;
    u16 drawnTotal;
    u8 color;
    u8 unk_33;
} EventKeyCard;

typedef char EventKeyCard_size[(sizeof(EventKeyCard) == 0x34) ? 1 : -1];

typedef struct SpriteFrameResourceDef {
#ifdef VERSION_EU
    void** tiles;
    void*** sprites;
#else
    void* tiles;
    void** sprites;
#endif
    u16 tilesSize;
    u16 spriteIndex;
} SpriteFrameResourceDef;

typedef struct MapCardDef {
    void* tiles;
    void* palette;
    void** sprites;
    void* tiles2;
    void* palette2;
    void** sprites2;
    u16 tilesSize;
    u16 paletteSize;
    u16 tilesSize2;
    u8 backIndex;
    u8 unk_1F;
    u16 kind;
    u16 value;
    u16 color;
    u16 unk_26;
} MapCardDef;

typedef struct MapCardBackDef {
    void* tiles;
    void* palette;
    void** sprites;
    void* tiles2;
    void** sprites2;
    u16 tilesSize;
    u16 paletteSize;
    u16 tilesSize2;
    u8 unk_1A[0x2];
} MapCardBackDef;

#endif
