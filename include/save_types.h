#ifndef GUARD_SAVE_TYPES_H
#define GUARD_SAVE_TYPES_H

#include "types.h"
#include "card_types.h"

#define SAVE_FILES 4
#define SAVE_CARDS 999
#define SAVE_DECKS 3

#define SAVE_BAD_SIGNATURE 0
#define SAVE_BAD_CHECKSUM 1
#define SAVE_OK 2

enum SaveHeaderFlag {
    SAVE_HEADER_SORA_CLEAR = 0x1,
    SAVE_HEADER_RIKU_TITLE = 0x2,
    SAVE_HEADER_RIKU_CLEAR = 0x4
};

typedef struct SaveCommon {
    u32 flags;
    u8 progression[0x88];
    u16 availableWorlds;
    u16 hp;
    u8 floor;
    u8 world;
    u8 unk_92[0x02];
    u32 playTime;
} SaveCommon;

typedef struct SaveFileSummary {
    u8 floor;
    u8 world;
    u8 level;
    u8 unk_03;
    u32 playTime;
} SaveFileSummary;

typedef struct SaveHeaderData {
    u16 flags;
    u16 language;
    SaveFileSummary files[SAVE_FILES];
} SaveHeaderData;

typedef struct SaveSharedSlice {
    u8 unk_000;
    u8 unk_001;
    u8 unk_002[2];
    u8 unk_004[0x21C];
    u32 unk_220[13];
} SaveSharedSlice;

typedef struct SaveLargeSlice {
    u8 activeDeck;
    u8 mapCardCounts[0x10E];
    u8 unk_10F;
    u16 cards[SAVE_CARDS];
    u16 cardCount;
    Deck decks[SAVE_DECKS];
} SaveLargeSlice;

typedef struct SaveSmallSlice {
    u8 mapCardCounts[0x10E];
    u8 unk_10E[2];
} SaveSmallSlice;

typedef struct SaveSliceE6C {
    u16 unk_00;
    u16 unk_02;
} SaveSliceE6C;

typedef struct SaveSliceEB4 {
    u16 unk_00[32];
    u16 unk_40[2];
} SaveSliceEB4;

typedef struct SaveFileLarge {
    SaveCommon common;
    SaveSharedSlice shared;
    SaveLargeSlice large;
    SaveSliceE6C unk_E6C;
    u8 pooState[0x044];
    SaveSliceEB4 moogleShop;
} SaveFileLarge;

typedef struct SaveFileSmall {
    SaveCommon common;
    SaveSharedSlice shared;
    SaveSmallSlice small;
} SaveFileSmall;

#endif
