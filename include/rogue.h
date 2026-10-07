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
#define ROGUE_SHARDS_DUEL 15
// Moogle points a won battle gives.
#define ROGUE_MOOGLE_POINTS 30

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
    u8 bossMoves; // one bit for each boss move unlocked, see ROGUE_BOSS_MOVE_
    u8 unused[9];
} RogueMeta;

#define ROGUE_META_TUTORIAL_SEEN 1
#define ROGUE_BOSS_MOVE_LARXENE 1
#define ROGUE_BOSS_MOVE_VEXEN 2
#define ROGUE_BASE_RELICS ROGUE_RELIC_KNIVES
#define ROGUE_META_ALL_CLEARED 2 // a run through every chapter was completed

#define ROGUE_COMBO_BASE 3
#define ROGUE_COMBO_PLUS_MAX 4
#define ROGUE_AIR_JUMPS_MAX 2
#define ROGUE_AP_MAX 20
// Frames the battle freezes on a hit, and a jump press stays valid.
#define ROGUE_HITSTOP 2
#define ROGUE_JUMP_BUFFER 6
// The hit counter: frames it lasts without a new hit, and hits that count
// towards its damage bonus of 2% each.
#define ROGUE_COMBO_TIME 150
#define ROGUE_COMBO_BONUS_HITS 15

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
    ROGUE_ROOM_EVENT,
    ROGUE_ROOM_KINDS
};

// Card message ids from here up are the mod's, see RogueCardMessageDef.
#define ROGUE_MSG_BASE 0x400
#define ROGUE_MSG_AXEL_FIRST ROGUE_MSG_BASE
#define ROGUE_MSG_AXEL_LAST (ROGUE_MSG_BASE + 15)
#define ROGUE_MSG_EVENT_FIRST (ROGUE_MSG_BASE + 16)
#define ROGUE_MSG_COUNT (16 + ROGUE_EVENTS * ROGUE_EVENT_PAGES)

enum RogueRelic {
    ROGUE_RELIC_VAMPIRE,
    ROGUE_RELIC_CRITICAL,
    ROGUE_RELIC_SECOND_WIND,
    ROGUE_RELIC_GLASS_CANNON,
    ROGUE_RELIC_MOMENTUM,
    ROGUE_RELIC_RELOAD,
    // Boss moves: each enters the pool once its boss has been beaten.
    ROGUE_RELIC_KNIVES,
    // Infused blades, in the order of RogueElement.
    ROGUE_RELIC_FIRE_BLADE,
    ROGUE_RELIC_ICE_BLADE,
    ROGUE_RELIC_THUNDER_BLADE,
    ROGUE_RELIC_ARCANE_ECHO,
    ROGUE_RELIC_ICE_PILLAR, // Vexen's move
    ROGUE_RELICS
};

// Builds, see rogue_build.c. The first three are the elements.
enum RogueBuild {
    ROGUE_ELEMENT_FIRE,
    ROGUE_ELEMENT_ICE,
    ROGUE_ELEMENT_THUNDER,
    ROGUE_ELEMENTS,
    ROGUE_ELEMENT_NONE = ROGUE_ELEMENTS,
    ROGUE_BUILD_BLADE = ROGUE_ELEMENTS,
    ROGUE_BUILD_SPELL,
    ROGUE_BUILD_SUMMON,
    ROGUE_BUILD_PROJECTILE,
    ROGUE_BUILDS
};

#define ROGUE_NO_KIND 0xFF
// Upward speed a combo finisher gives the enemy it hits; a keyblade's own is 384.
#define ROGUE_LAUNCH 560
// 8.8 damage scale of the ice block of the Vexen relic: a swing and a half.
#define ROGUE_PILLAR_SCALE 384

// Arts: card kinds that can have a sleight bound, and the value a card needs
// to perform it alone.
#define ROGUE_ART_KINDS 24
#define ROGUE_ART_MIN_VALUE 5

// Frames between a keyblade hit and the magic hit of an infused blade.
#define ROGUE_INFUSION_DELAY 7
// Frames it then waits for the enemy to be hittable again.
#define ROGUE_INFUSION_WAIT 50

// Event rooms.
enum RogueEvent {
    ROGUE_EVENT_BELLE,
    ROGUE_EVENT_LEON,
    ROGUE_EVENT_YUFFIE,
    ROGUE_EVENT_MOOGLE,
    ROGUE_EVENT_JACK,
    ROGUE_EVENT_HERCULES,
    ROGUE_EVENT_TIGGER,
    ROGUE_EVENT_RIKU,
    ROGUE_EVENT_LEXAEUS,
    ROGUE_EVENT_REPLICA,
    ROGUE_EVENT_JAFAR,
    ROGUE_EVENT_OOGIE,
    ROGUE_EVENT_ANSEM,
    ROGUE_EVENT_SALLY,
    ROGUE_EVENT_JIMINY,
    ROGUE_EVENT_WENDY,
    ROGUE_EVENT_BEAST,
    ROGUE_EVENT_TIDUS,
    ROGUE_EVENT_SELPHIE,
    ROGUE_EVENTS
};

#define ROGUE_EVENT_PAGES 2
#define ROGUE_EVENT_OFFERS 3

// What an event can offer; the reward screen turns each into a reward.
enum RogueOffer {
    ROGUE_OFFER_HEAL,
    ROGUE_OFFER_MAX_HP,
    ROGUE_OFFER_CP,
    ROGUE_OFFER_COMBO,
    ROGUE_OFFER_AIR_JUMP,
    ROGUE_OFFER_UPGRADE,
    ROGUE_OFFER_RANDOM_CARD,
    ROGUE_OFFER_CARD, // param: card id
    ROGUE_OFFER_SHARDS, // param: how many
    ROGUE_OFFER_REROLL,
    ROGUE_OFFER_ATTACK_FOR_HP,
    ROGUE_OFFER_GAMBLE,
    ROGUE_OFFER_DUEL, // param: battle id
    ROGUE_OFFER_LEAVE,
    ROGUE_OFFER_ATTACK2_FOR_HP,
    ROGUE_OFFER_SHARDS_FOR_CARD,
    ROGUE_OFFER_BIG_GAMBLE,
    ROGUE_OFFER_DUPLICATE,
    ROGUE_OFFER_TRANSFORM,
    ROGUE_OFFER_PAY_HP,
    ROGUE_OFFER_RELIC_FOR_HP
};

typedef struct RogueEventOffer {
    u8 offer;
    u16 param;
} RogueEventOffer;

// Argument of gModeRogueReward.
enum {
    ROGUE_REWARD_BATTLE,
    ROGUE_REWARD_BOSS,
    ROGUE_REWARD_EVENT,
    ROGUE_REWARD_DUEL // a won duel or a treasure room: a boss's rewards, then back to the room
};

struct FldObj;
struct BtlObj;
struct CardDef;

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
    u16 relics; // one bit for each RogueRelic the run has
    u8 secondWindUsed; // this battle
    u16 combo; // hits landed without being hit
    u8 comboTimer; // frames until the hit count lapses
    u8 jumpBuffer;
    u8 event; // who is in this event room
    u8 eventDone; // set once they have made their offer
    u8 duel; // set while the battle is a duel picked in an event
    u8 build[ROGUE_BUILDS]; // points of each build, see RogueCountBuild
    u8 playedKind; // kind of the card played alone, ROGUE_NO_KIND otherwise
    u8 projectile; // set while a thrown thing or an added hit tests its hitbox
    u8 echoing; // set while an added hit lands, so that it adds none itself
    u8 finisher; // set while a combo finisher tests its hitbox
    u32 artsUsed; // one bit for each card kind whose art was used this reload
    u8 arts[ROGUE_ART_KINDS]; // sleight bound to each card kind, 0 for none
    u8 cardXp[ROGUE_CARD_SLOTS]; // battles won with each collection slot in the deck
} RogueRun;

// Test hooks, see rogue_debug.c.
enum RogueDebugCommand {
    ROGUE_DEBUG_NONE,
    ROGUE_DEBUG_ROOM, // arg: room kind to walk into
    ROGUE_DEBUG_BATTLE, // arg: battle id to start
    ROGUE_DEBUG_REWARD, // arg: reward screen source
    ROGUE_DEBUG_RELIC, // arg: relic to give
    ROGUE_DEBUG_FLOOR, // arg: floor the run is on
    ROGUE_DEBUG_WIN, // win the battle
    ROGUE_DEBUG_HURT, // arg: damage Sora takes
    ROGUE_DEBUG_HIT, // arg: damage the locked-on enemy takes
    ROGUE_DEBUG_ATTACK, // arg: attack definition Sora lands on the locked-on enemy
    ROGUE_DEBUG_FINISHER // what a combo finisher sets off, without the swing
};

typedef struct RogueDebug {
    u8 command;
    u8 arg;
    u8 god; // Sora takes no damage
    u8 event; // event the next event room holds, plus one
    // Read back by the tests, refreshed every battle frame.
    s16 soraHp;
    s16 targetHp;
    s32 soraZ;
    s32 targetZ; // height of the enemy Sora hit last
    u16 lastDamage; // the last damage an enemy took
    u16 hits; // times an enemy took damage this battle
    u16 knives; // projectiles the knife relic threw this battle
    u16 echoes; // added magic hits that connected this battle
    u16 pillars; // ice blocks the Vexen relic raised this battle
} RogueDebug;

extern RogueDebug gRogueDebug;
void RogueDebugField(void);
void RogueDebugBattle(void);

extern RogueRun gRogue;
extern RogueMeta gRogueMeta;
extern Mode gModeRogueShop;
extern Mode gModeRogueRelics;
extern Mode* gRogueLeaveMode;
extern s32 gRogueLeaveArg;
extern struct TaskDesc gTaskDescRogueEvent;
extern Mode gModeRogueBoot;
extern Mode gModeRogueReward;
extern Mode gModeRogueOver;

u32 RogueRand(void);
u32 RogueRandBelow(u32 n);

void RogueStartRun(void);
void RogueLeaveRoom(u8 door);
u8 RogueOnBattleEnd(u16 battle);
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
void RogueLeaveRoomFor(Mode* mode, s32 arg);
u8 RogueHasRelic(u8 relic);
u8 RogueCardElement(u16 id);
void RogueCountBuild(void);
u8 RogueBuildElement(void);
u8 RogueBuildBonus(u8 build);
s32 RogueBuildDamage(s32 damage, u16 attack, u32 attackFlags);
u8 RogueBuildPoolBias(u8 pool);
u16 RogueBuildSpell(void);
void RogueOnKeybladeHit(s32 x, s32 y, s32 z, u8 finisher);
void RogueOnStockPlayed(void);
void RogueOnReload(void);
void RogueOnKnockback(struct BtlObj* target);
u8 RogueRollArt(u16 kind);
struct CardDef;
s32 RogueCardAction(const struct CardDef* def);
u8 RogueRollRelic(void);
const u8* RogueRelicName(u8 relic);
const u8* RogueRelicText(u8 relic);
u8 RogueReloadRate(u8 slowed);
void RogueSuspendSave(void);
u8 RogueSuspendLoad(void);
u8 RogueResumeRun(void);
const RogueEventOffer* RogueEventOffers(void);
u8 RogueDoorsOpen(void);
u8 RogueEnemyLevel(void);
u16 RogueEnemyHp(u16 base);
u16 RogueEnemyAttack(u16 base);
u16 RogueEnemyExp(u16 base);
u16 RogueBossHp(void);
u16 RogueBossAttack(void);
u8 RogueFloorIsChapterEnd(void);
void RoguePlaceNpc(struct FldObj* obj);
u8 RogueCardTier(u16 id);
u8 RogueMaxCardTier(void);
u8 RogueMaxCardValue(void);
u8 RogueCardUnlocked(u16 id);
u16 RogueRollRewardCard(void);
void RogueGiveCard(u16 id);
u8 RogueCardLevel(u16 slot);
void RogueGainCardXp(void);
u8 RogueCountCards(u8 level);
u8 RogueRollFusion(u8* posA, u8* posB, u16* result);
void RogueFuse(u8 posA, u8 posB, u16 result);
void RogueRemoveDeckCard(u8 pos);
u8 RogueRollDeckCard(void);
u16 RogueRollTransform(u16 id);
u8 RogueTryAirJump(void);
void RogueResetAirJumps(void);
struct BtlObj;
void RogueOnDamage(struct BtlObj* p);
u16 RogueBufferJump(u16 pressed);
void RogueOnFinisher(struct BtlObj* sora);
void RogueOnBossBeaten(u16 battle);
extern struct TaskDesc gTaskDescRogueHud;
u8* RogueRoomLinks(void);
u16 RogueDoorFlags(u8 door);
void RogueSpawnRoomActors(void);
void RogueBuildStartDeck(void);
u8 RogueComboHits(void);
u8 RogueComboSlot(u8 step);
const struct CardMessageDef* RogueCardMessageDef(u16 id);

#endif
