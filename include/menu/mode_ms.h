#ifndef GUARD_MODE_MS_H
#define GUARD_MODE_MS_H

#include "types.h"
#include "fld_types.h"
#include "anim.h"

typedef struct MooglePackCardDef {
    u16 cardId;
    u8 unk_02[0x2];
    s32 unlockFlag;
    u16 weights[4];
} MooglePackCardDef;

typedef struct MooglePackCardTable {
    const MooglePackCardDef* cards;
    s16 count;
    u8 unk_06[0x2];
} MooglePackCardTable;

typedef struct MooglePackSpriteDef {
    void* palette;
    u16 paletteSize;
    u8 unk_06[0x2];
    void* tiles;
    u16 tilesSize;
    u8 unk_0E[0x2];
    void* sprite;
    u16 xOffset;
    u16 yOffset;
} MooglePackSpriteDef;

typedef struct MooglePackTilemapDef {
#ifdef VERSION_EU
    u16** tilemap;
#else
    u16* tilemap;
#endif
    s16 srcX;
    s16 srcY;
} MooglePackTilemapDef;

typedef struct MooglePackMenuEntry {
    s16 upEntry;
    s16 downEntry;
    s16 leftEntry;
    s16 rightEntry;
    s16 cursorX;
    s16 cursorY;
    void* selectionTilemap;
    u16 selectionTilemapSize;
    s16 tilemapX;
    s16 tilemapY;
    u16 spriteX;
    u16 spriteY;
    u16 unk_1A;
    MooglePackTilemapDef packTilemaps[4];
} MooglePackMenuEntry;

typedef struct MooglePackCardWork {
    FldRes* palette;
    void* tiles;
    void* gfx;
    FldRes* palette2;
    void* tiles2;
    void* backSprite;
    AnimState anim;
    u16 flipAngle;
    u16 unk_32;
    s32 scale;
    u16 state;
    u16 unk_3A;
    s32 x;
    s32 y;
    u16 timer;
    u8 premium;
    u8 revealed;
} MooglePackCardWork;

void ClearMooglePackBought(u16 a, u16 b, u16 c);
u8 IsMooglePackBought(u16 a, u16 b, u16 c);
void SetMoogleFreePackFlag(u16 a);
void ClearMoogleFreePackFlag(u16 a);
u8 GetMoogleFreePackFlag(u16 a);
void ClearMoogleRoomFlags();
u8 BuildMooglePackList(s16 a);
s32 MoogleShopReadMenuKeys();
u16 RollMoogleCardValue();
void DrawMoogleShopPacks(s16 a);
void DrawMoogleShopCategoryLabels(s16 a);
void ReleaseMooglePackOpening();
void mode_ms_shop_1();
void MoogleShopDraw();
void mode_ms_shop_0();
void MoogleShopHandlePackInput();
void mode_ms_shop_2();
void LoadMooglePackSelectionTilemap(s16 a);
void MoogleShopHandleSoldOutInput();
void MoogleShopHandleRowInput();

void ShowPersistentCardMessage(void* pool, u32 a, u16 b);

void SetMooglePackBought(u16 a, u16 b, u16 c);
u8 UpdateMooglePackOpening(u16 a);
void InitMooglePackOpening(s16 x, s16 y);
void RollMooglePackCards(s16 a, s16 b);
void MoogleShopCopyTilemapRect(u16 w, s16 h, u16* src, s16 sx, s16 sy, u16* dst, s16 dx, s16 dy);

extern u16 gSoraPalette[];
extern u8 gSor1ll00Tiles[];
extern u16 gBStatesPalette[];
extern u16 gMoguPalette[];
extern u8 gMoguFl00Tiles[];
extern u16 gCard00Palette[];
#endif /* GUARD_MODE_MS_H */
