#ifndef GUARD_CARD_TYPES_H
#define GUARD_CARD_TYPES_H

#include "types.h"

#define DECK_SIZE 99
#define CARD_ID_MASK 0xFFF

enum CardIdSentinel {
    CARD_ID_RELOAD = 0xFFFE,
    CARD_ID_NONE = 0xFFFF
};

typedef struct Deck {
    u16 cards[DECK_SIZE];
    u8 name[0x14];
    u16 cpCost;
    u16 cardCount;
    u16 unk_DE;
} Deck;

enum CardDefFlag {
    CARD_DEF_FLAG_ITEM = 0x2,
    CARD_DEF_FLAG_SUMMON = 0x4,
    CARD_DEF_FLAG_FRIEND = 0x8,
    CARD_DEF_FLAG_GIMMICK = 0x10
};

typedef struct CardDef {
    void* gfx;
    void* tiles;
    void* palette;
    void* name;
    void* gfx2;
    void* tiles2;
    void* palette2;
    u16 kind;
    u16 flags;
    u8 value;
    u8 unk_21[0x03];
    u32 move;
    u16 unk_28;
    u8 category;
    u8 unk_2B;
    u16 cpCost;
    u8 unk_2E[0x06];
} CardDef;

typedef struct CardBack {
    void* gfx;
    void* gfx2;
    void* unk_08;
    void* tiles;
    void* tiles2;
    void* tiles3;
} CardBack;

typedef struct CardStat {
    u16 unk_00;
    u16 unk_02;
    u8 value;
    u8 unk_05[0x03];
    u32 unk_08;
    u16 unk_0C;
    u8 category;
    u8 unk_0F;
    u16 cpCost;
    u8 unk_12[0x06];
} CardStat;

#endif
