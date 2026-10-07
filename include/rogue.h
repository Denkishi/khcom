#ifndef GUARD_ROGUE_H
#define GUARD_ROGUE_H

#include "types.h"
#include "mode.h"

#define ROGUE_LANGUAGE 3 /* Italian */

#define ROGUE_ROOM_ID 0
#define ROGUE_NO_DOOR 0xFF
#define ROGUE_FLOOR_ROOMS 5

// A run goes through the chapters unlocked so far; beating the last boss of
// the deepest one completes it and unlocks the next.
#define ROGUE_CHAPTERS 4
#define ROGUE_FLOORS 11

// Memory shards, the currency kept between runs.
#define ROGUE_SHARDS_ROOM 2
#define ROGUE_SHARDS_MINIBOSS 10
#define ROGUE_SHARDS_BOSS 25
#define ROGUE_SHARDS_NEW_CHAPTER 50

enum RogueUpgrade {
    ROGUE_UPGRADE_HP,
    ROGUE_UPGRADE_CP,
    ROGUE_UPGRADE_ATTACK,
    ROGUE_UPGRADE_COMBO,
    ROGUE_UPGRADE_AIR_JUMP,
    ROGUE_UPGRADE_REROLL,
    ROGUE_UPGRADES
};

typedef struct RogueUpgradeDef {
    u8 levels;
    u8 cost; // of the first level
} RogueUpgradeDef;

typedef struct RogueMeta {
    u32 magic;
    u16 checksum; // of everything from shards on
    u16 shards;
    u16 runs;
    u16 wins;
    u16 bestDepth;
    u8 chapters; // chapters unlocked, at least 1
    u8 flags;
    u8 upgrades[ROGUE_UPGRADES];
    u8 unused[10];
} RogueMeta;

#define ROGUE_META_TUTORIAL_SEEN 1

#define ROGUE_COMBO_BASE 3
#define ROGUE_COMBO_PLUS_MAX 4
#define ROGUE_AIR_JUMPS_MAX 2
#define ROGUE_AP_MAX 20

// Cards level up by winning battles in the deck; two level 3 cards can fuse.
#define ROGUE_CARD_SLOTS 160
#define ROGUE_CARD_XP_LEVEL_2 2
#define ROGUE_CARD_XP_LEVEL_3 4
#define ROGUE_CARD_LEVEL_MAX 3
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
// Deck reload: charge per tick, vanilla 25, or 12 under the enemy card that
// slows it, and how many extra charges a reload can come to cost, vanilla 2.
#define ROGUE_RELOAD_RATE 40
#define ROGUE_RELOAD_RATE_SLOWED 20
#define ROGUE_RELOAD_STEPS_MAX 1
// Share of max HP a rest room gives back, in 1/256.
#define ROGUE_REST_HEAL 90

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
#define ROGUE_MSG_AXEL_LAST (ROGUE_MSG_BASE + 12)
#define ROGUE_MSG_COUNT 13

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
    u8 deckWanted; // set while a run is starting, see RogueBuildStartDeck
    u8 rerolls; // reward rerolls left this run
    u8 chapters; // chapters this run goes through
    u8 newChapter; // set by RogueMetaEndRun when the run unlocked one
    u16 shards; // earned this run, banked when it ends
    u8 cardXp[ROGUE_CARD_SLOTS]; // battles won with each collection slot in the deck
} RogueRun;

extern RogueRun gRogue;
extern RogueMeta gRogueMeta;
extern Mode gModeRogueShop;
extern Mode gModeRogueBoot;
extern Mode gModeRogueReward;
extern Mode gModeRogueOver;

u32 RogueRand(void);
u32 RogueRandBelow(u32 n);

void RogueStartRun(void);
void RogueLeaveRoom(u8 door);
u8 RogueOnBattleEnd(void);
void RogueOnDefeat(void);
void RogueNextFloor(void);
u8 RogueFloorCount(void);
void RogueMetaLoad(void);
void RogueMetaSave(void);
void RogueMetaEndRun(u8 completed);
void RogueApplyUpgrades(void);
u8 RogueBuyUpgrade(u8 upgrade);
u8 RogueUpgradeMax(u8 upgrade);
u16 RogueUpgradeCost(u8 upgrade);
void RogueOpenShop(void);
u8 RogueDoorsOpen(void);
u8 RogueEnemyLevel(void);
u16 RogueEnemyHp(u16 base);
u16 RogueEnemyAttack(u16 base);
u16 RogueEnemyExp(u16 base);
u16 RogueBossStat(u16 base);
u8 RogueCardTier(u16 id);
u8 RogueMaxCardTier(void);
u8 RogueMaxCardValue(void);
u8 RogueCardUnlocked(u16 id);
u16 RogueRollRewardCard(void);
void RogueGiveCard(u16 id);
u8 RogueCardLevel(u16 slot);
void RogueGainCardXp(void);
u8 RogueRollFusion(u8* posA, u8* posB, u16* result);
void RogueFuse(u8 posA, u8 posB, u16 result);
u8 RogueTryAirJump(void);
void RogueResetAirJumps(void);
u8* RogueRoomLinks(void);
u16 RogueDoorFlags(u8 door);
void RogueSpawnRoomActors(void);
void RogueBuildStartDeck(void);
u8 RogueComboHits(void);
u8 RogueComboSlot(u8 step);
const struct CardMessageDef* RogueCardMessageDef(u16 id);

#endif
