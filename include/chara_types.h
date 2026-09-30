#ifndef GUARD_CHARA_TYPES_H
#define GUARD_CHARA_TYPES_H

#include "types.h"

typedef struct CharaObjParam {
    u32 tilesAddr;
    u16 tileCount;
    u8 unk_06[0x02];
    u32 tilesAddr2;
    u16 tileCount2;
    u8 unk_0E[0x02];
    u32 tilesAddr3;
    u16 tileCount3;
    u8 unk_16[0x02];
    u32 paletteAddr;
    u16 paletteSize;
    u8 unk_1E[0x02];
    u32 tilesAddr4;
    u16 tileCount4;
    u8 unk_26[0x02];
    u32 paletteAddr2;
    u16 paletteSize2;
    u8 unk_2E[0x02];
    u32 x;
    u32 y;
    u32 z;
    void (*callback)(void);
    struct BtlObj* prizeObj;
    u16 flags;
} CharaObjParam;

typedef struct CharaObjParam2 {
    u32 tilesAddr;
    u16 tileCount;
    u8 unk_06[0x02];
    u32 paletteAddr;
    u16 paletteSize;
    u8 unk_0E[0x02];
    u32 x;
    u32 y;
    u32 z;
    void (*callback)(void);
    struct BtlObj* prizeObj;
} CharaObjParam2;

typedef struct CharaLinkData {
    u16 hp;
    u16 maxHp;
    u16 level;
    u16 winCount;
    u16 loseCount;
    u16 ap;
    u64 learnedStocks;
    u64 learnedStocks2;
    u16 worldFlags;
    u16 seed;
} CharaLinkData;

#endif
