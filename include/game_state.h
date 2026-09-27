#ifndef GUARD_GAME_STATE_H
#define GUARD_GAME_STATE_H

#include "types.h"
#include "save_types.h"
#include "fld_types.h"
#include "player_progression_types.h"

typedef struct GameFloor {
    u16 unk_00;
    u8 world;
    u8 unk_03;
} GameFloor;

struct UnkStruct_0984BC9C;
struct MapEnmWork;

typedef struct MapEnmCache {
    FldPos unk_00;
    u8 unk_10;
    u8 unk_11[0x03];
    s32 unk_14;
    u8 unk_18[0x04];
    ListNode node;
    const struct UnkStruct_0984BC9C* unk_30;
    void (*unk_34)(struct MapEnmWork*);
} MapEnmCache;

typedef struct GameState {
    u8 unk_000;
    u8 unk_001[0x03];
    u32 randomSeed;
    u32 flags;
    u8 world;
    u8 unk_00D;
    s8 floor;
    u8 unk_00F;
    u16 unk_010;
    u8 unk_012[0x02];
    FldPos fieldPosition;
    u8 unk_024;
    u8 unk_025[0x03];
    s32 unk_028;
    s32 unk_02C;
    u16 unk_030;
    s16 hp;
    s32 unk_034;
    s32 unk_038;
    s32 unk_03C;
    MapEnmCache enemyCache[3];
    ListPool enemyCachePool;
    PlayerProgression progression;
    u16 unk_180;
    u8 unk_182[0x02];
    GameFloor floors[13];
    u32 unk_1B8;
    SaveFileSummary fileSummaries[4];
    u32 playTime;
    u16 unk_1E0;
    u16 unk_1E2;
    u8 unk_1E4;
    u8 unk_1E5[0x03];
    u64 unk_1E8;
    u64 unk_1F0;
    u16 unk_1F8;
    u16 unk_1FA;
    u8 unk_1FC;
    u8 unk_1FD[0x03];
    u64 unk_200;
    u64 unk_208;
} GameState;

typedef char GameState_size[(sizeof(GameState) == 0x210) ? 1 : -1];
typedef char GameState_progression_offset[((u32)&((GameState*)0)->progression == 0xF8) ? 1 : -1];
typedef char GameFloor_size[(sizeof(GameFloor) == 4) ? 1 : -1];
typedef char MapEnmCache_size[(sizeof(MapEnmCache) == 0x38) ? 1 : -1];

extern GameState gGameState;

void UpdatePlayTime(void);

#endif
