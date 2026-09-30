#ifndef GUARD_GAME_STATE_H
#define GUARD_GAME_STATE_H

#include <stddef.h>
#include "types.h"
#include "save_types.h"
#include "fld_types.h"
#include "player_progression_types.h"

typedef struct GameFloor {
    u16 flags;
    u8 world;
    u8 eventStep;
} GameFloor;

struct MapEnmDef;
struct MapEnmWork;

typedef struct MapEnmCache {
    FldPos pos;
    u8 angle;
    u8 unk_11[0x03];
    s32 speed;
    u8 unk_18[0x04];
    ListNode node;
    const struct MapEnmDef* def;
    void (*update)(struct MapEnmWork*);
} MapEnmCache;

typedef struct GameState {
    u8 fieldResume;
    u8 unk_001[0x03];
    u32 randomSeed;
    u32 flags;
    u8 world;
    u8 battleStage;
    s8 floor;
    u8 mapMenuCursor;
    u16 battleCount;
    u8 unk_012[0x02];
    FldPos fieldPosition;
    u8 fieldAngle;
    u8 unk_025[0x03];
    s32 fieldSpeed;
    s32 fieldVz;
    u16 fieldState;
    s16 hp;
    s32 fieldTargetX;
    s32 fieldTargetY;
    s32 fieldTargetZ;
    MapEnmCache enemyCache[3];
    ListPool enemyCachePool;
    PlayerProgression progression;
    u16 availableWorlds;
    u8 unk_182[0x02];
    GameFloor floors[13];
    u32 roomEffect;
    SaveFileSummary fileSummaries[4];
    u32 playTime;
    u16 linkMaxHp;
    u16 linkAp;
    u8 linkLevel;
    u8 unk_1E5[0x03];
    u64 linkLearnedStocks;
    u64 linkLearnedStocks2;
    u16 linkPartnerMaxHp;
    u16 linkPartnerAp;
    u8 linkPartnerLevel;
    u8 unk_1FD[0x03];
    u64 linkPartnerLearnedStocks;
    u64 linkPartnerLearnedStocks2;
} GameState;

typedef char GameState_size[(sizeof(GameState) == 0x210) ? 1 : -1];
typedef char GameState_progression_offset[(offsetof(GameState, progression) == 0xF8) ? 1 : -1];
typedef char GameFloor_size[(sizeof(GameFloor) == 4) ? 1 : -1];
typedef char MapEnmCache_size[(sizeof(MapEnmCache) == 0x38) ? 1 : -1];

extern GameState gGameState;

void UpdatePlayTime(void);

#endif
