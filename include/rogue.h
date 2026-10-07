#ifndef GUARD_ROGUE_H
#define GUARD_ROGUE_H

#include "types.h"
#include "mode.h"

#define ROGUE_LANGUAGE 3 /* Italian */

#define ROGUE_ROOM_ID 0
#define ROGUE_NO_DOOR 0xFF
#define ROGUE_FLOOR_ROOMS 7

#define ROGUE_COMBO_BASE 3
#define ROGUE_COMBO_PLUS_MAX 4
#define ROGUE_AIR_JUMPS_MAX 2
// Frames after a finisher's hit frame until the next card can be played.
#define ROGUE_FINISHER_RECOVERY 8
// Frames after a hit frame until holding a direction walks out of the swing.
#define ROGUE_MOVE_CANCEL 10
// Vertical speed a mid-air hit gives Sora (negative is up).
#define ROGUE_AIR_HIT_LIFT -384
// Ground movement and dodge roll, vanilla 128 / 614 and 1664 / 32.
#define ROGUE_RUN_ACCEL 192
#define ROGUE_RUN_SPEED 768
#define ROGUE_DODGE_SPEED 2048
#define ROGUE_DODGE_FRAMES 24

enum RogueRoomKind {
    ROGUE_ROOM_START,
    ROGUE_ROOM_BATTLE,
    ROGUE_ROOM_ELITE,
    ROGUE_ROOM_TREASURE,
    ROGUE_ROOM_SHOP,
    ROGUE_ROOM_REST,
    ROGUE_ROOM_BOSS,
    ROGUE_ROOM_KINDS
};

// Card message ids from here up are the mod's, see RogueCardMessageDef.
#define ROGUE_MSG_BASE 0x400
#define ROGUE_MSG_AXEL_FIRST ROGUE_MSG_BASE
#define ROGUE_MSG_AXEL_LAST (ROGUE_MSG_BASE + 8)
#define ROGUE_MSG_COUNT 9

typedef struct RogueRun {
    u32 seed;
    u32 rng;
    u16 depth; // rooms entered this run, the start room is 0
    u8 floor; // floors cleared this run
    u8 room; // room index within the floor
    u8 world;
    u8 kind;
    u8 doors[4]; // room kind behind each door, ROGUE_NO_DOOR if none
    u8 comboPlus; // extra hits in the attack combo
    u8 airJumps; // jumps allowed in mid-air
    u8 airJumpsUsed;
} RogueRun;

extern RogueRun gRogue;
extern Mode gModeRogueBoot;
extern Mode gModeRogueReward;

u32 RogueRand(void);
u32 RogueRandBelow(u32 n);

void RogueStartRun(void);
void RogueLeaveRoom(u8 door);
u8 RogueOnBattleEnd(void);
void RogueOnDefeat(void);
void RogueNextFloor(void);
u8 RogueDoorsOpen(void);
u8 RogueEnemyLevel(void);
u16 RogueRollRewardCard(void);
u8 RogueTryAirJump(void);
void RogueResetAirJumps(void);
u8* RogueRoomLinks(void);
u16 RogueDoorFlags(u8 door);
void RogueSpawnRoomActors(void);
void RogueBuildStartDeck(void);
void RogueLearnSleights(void);
u8 RogueComboHits(void);
u8 RogueComboSlot(u8 step);
const struct CardMessageDef* RogueCardMessageDef(u16 id);

#endif
