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
// Argument of gModeRogueShop: where it was opened from and goes back to.
#define ROGUE_SHOP_FROM_ROOM 0
#define ROGUE_SHOP_FROM_HUB 1

#define ROGUE_SHARDS_ROOM 2
#define ROGUE_SHARDS_MINIBOSS 10
#define ROGUE_SHARDS_BOSS 25
#define ROGUE_SHARDS_NEW_CHAPTER 50
#define ROGUE_SHARDS_DUEL 15
// Oblivion levels, the difficulty past the last chapter: each adds this many
// enemy levels and a quarter more shards.
#define ROGUE_OBLIVION_MAX 5
#define ROGUE_OBLIVION_LEVELS 3
// Enemy levels a challenge room adds.
#define ROGUE_CHALLENGE_LEVELS 4
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

#define ROGUE_STARTERS 6 // cards that can be unlocked to start every run with
#define ROGUE_STARTER_VALUE 6
#define ROGUE_SEALS_MAX 99

typedef struct RogueUpgradeDef {
    u8 levels;
    u8 cost; // of the first level
    u8 needs; // the upgrade it branches from, ROGUE_UPGRADES for a root
    u8 needsLevel; // the level that one must have
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
    u8 boon; // the RogueBoon picked in the hub for the next run
    u8 boonsMet; // one bit for each boon whose character was met in a run
    u8 boonsWon; // one bit for each boon a run was completed with: it is stronger
    u8 oblivion; // difficulty level picked in the hub
    u8 oblivionMax; // highest level unlocked
    u8 hero; // the RogueHero picked in the hub
    u8 seals; // won from bosses, spent on starting cards
    u8 starters; // one bit for each starting card unlocked, see ROGUE_STARTERS
    u8 unused[1];
} RogueMeta;

#define ROGUE_META_TUTORIAL_SEEN 1
#define ROGUE_META_MICKEY 4 // Mickey was beaten as a boss: he can be played

// Who the player fights as. All of them play as Sora does, drawn as themselves.
enum RogueHero { ROGUE_HERO_SORA, ROGUE_HERO_MICKEY, ROGUE_HERO_SORA_KH2, ROGUE_HEROES };

// What the characters in the hub offer for the next run; one at a time.
enum RogueBoon {
    ROGUE_BOON_NONE,
    ROGUE_BOON_BELLE, // 30 more max HP
    ROGUE_BOON_MOOGLE, // two reward rerolls
    ROGUE_BOON_LEON, // a starting deck of keyblades
    ROGUE_BOON_YUFFIE, // a starting deck of spells
    ROGUE_BOON_HERCULES, // strength +2
    ROGUE_BOON_TIGGER, // an air jump
    ROGUE_BOON_JACK, // a random relic
    ROGUE_BOONS
};
#define ROGUE_BOSS_MOVE_LARXENE 1
#define ROGUE_BOSS_MOVE_VEXEN 2
#define ROGUE_BOSS_MOVE_AXEL 4
#define ROGUE_BOSS_MOVE_MARLUXIA 8
#define ROGUE_BOSS_MOVE_HADES 16
#define ROGUE_BOSS_MOVE_LEXAEUS 32
#define ROGUE_BOSS_MOVE_HOOK 64
#define ROGUE_BASE_RELICS ROGUE_RELIC_KNIVES
#define ROGUE_META_ALL_CLEARED 2 // a run through every chapter was completed

#define ROGUE_COMBO_BASE 3
#define ROGUE_COMBO_PLUS_MAX 4
#define ROGUE_AIR_JUMPS_MAX 2
#define ROGUE_AP_MAX 20
// Frames the battle freezes on a hit, and a jump press stays valid.
#define ROGUE_HITSTOP 2
#define ROGUE_JUMP_BUFFER 6
// Frames a press of the card button stays valid while Sora is busy.
#define ROGUE_CARD_BUFFER 6
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
    ROGUE_ROOM_CHALLENGE, // tougher enemies, a boss's reward
    ROGUE_ROOM_KINDS
};

// Card message ids from here up are the mod's, see RogueCardMessageDef.
#define ROGUE_MSG_BASE 0x400
#define ROGUE_MSG_AXEL_FIRST ROGUE_MSG_BASE
#define ROGUE_MSG_AXEL_LAST (ROGUE_MSG_BASE + 15)
#define ROGUE_MSG_EVENT_FIRST (ROGUE_MSG_BASE + 16)
#define ROGUE_MSG_BOON_FIRST (ROGUE_MSG_EVENT_FIRST + ROGUE_EVENTS * ROGUE_EVENT_PAGES)
#define ROGUE_MSG_COUNT (16 + ROGUE_EVENTS * ROGUE_EVENT_PAGES + ROGUE_BOONS - 1)

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
    // The moves of rogue_moves.c, in the order of RogueMove.
    ROGUE_RELIC_CHAKRAM,
    ROGUE_RELIC_NEEDLES,
    ROGUE_RELIC_PETALS,
    ROGUE_RELIC_SHARDS,
    ROGUE_RELIC_FIREBALL,
    ROGUE_RELIC_FIRE_BURST,
    ROGUE_RELIC_ROCK,
    ROGUE_RELIC_BOMB,
    // Modifiers: each changes every move the run has, and they add up.
    ROGUE_RELIC_MOD_MULTI,
    ROGUE_RELIC_MOD_FAN,
    ROGUE_RELIC_MOD_HOMING,
    ROGUE_RELIC_MOD_ECHO,
    ROGUE_RELIC_MOD_GIANT,
    ROGUE_RELIC_MOD_PRISM,
    ROGUE_RELIC_BERSERK,
    ROGUE_RELIC_THORNS,
    ROGUE_RELIC_COMBO_HEAL,
    ROGUE_RELIC_AIR_MASTER,
    ROGUE_RELIC_TAG_TEAM,
    ROGUE_RELIC_TREASURER,
    ROGUE_RELICS
};
#define ROGUE_FIRST_MOD ROGUE_RELIC_MOD_MULTI
#define ROGUE_FIRST_SYNERGY ROGUE_RELIC_BERSERK

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
// The mod's cards come after the original 950; ten ids are skipped, see
// rogue_cards.c. Each new keyblade kind has ten ids, one for each value.
#define ROGUE_FIRST_CARD_KIND 96
#define ROGUE_CARD_KINDS 16
// The first of them are keyblades, then come the spells Water, Wind and Magnet.
#define ROGUE_NEW_KEYBLADES 13
#define ROGUE_CARD_WATER (ROGUE_FIRST_CARD_KIND + 13)
#define ROGUE_CARD_WIND (ROGUE_FIRST_CARD_KIND + 14)
#define ROGUE_CARD_MAGNET (ROGUE_FIRST_CARD_KIND + 15)
#define ROGUE_CARD_DEFS ((ROGUE_FIRST_CARD_KIND + ROGUE_CARD_KINDS) * 10)
// Whether a card kind is a keyblade, original or new. Needs card_ids.h.
#define ROGUE_IS_KEYBLADE(kind) \
    ((kind) <= CARD_ULTIMA_WEAPON || ((kind) >= ROGUE_FIRST_CARD_KIND && (kind) < ROGUE_FIRST_CARD_KIND + ROGUE_NEW_KEYBLADES))
#define ROGUE_IS_NEW_SPELL(kind) ((kind) >= ROGUE_CARD_WATER && (kind) <= ROGUE_CARD_MAGNET)
// Tier of the new keyblades, see RogueCardTier: they come from fusions.
#define ROGUE_NEW_CARD_TIER 5
// The action id of a Kingdom Key swing, which a tag card is played as.
#define ROGUE_ACTION_SWING 0
// Upward speed a combo finisher gives the enemy it hits; a keyblade's own is 384.
#define ROGUE_LAUNCH 560
// 8.8 damage scale of the ice block of the Vexen relic: a swing and a half.
#define ROGUE_PILLAR_SCALE 384

// Arts: card kinds that can have a sleight bound, and the value a card needs
// to perform it alone.
#define ROGUE_ART_KINDS 24
// Arts from this number up are boss moves: the card keeps its own action and
// the move goes off with it.
#define ROGUE_ART_KNIVES 200
#define ROGUE_ART_PILLAR 201
// The moves of rogue_moves.c follow, in the order of RogueMove.
#define ROGUE_ART_MOVES 202
#define ROGUE_ART_MIN_VALUE 5

// Frames between a keyblade hit and the magic hit of an infused blade.
#define ROGUE_INFUSION_DELAY 7
// Frames it then waits for the enemy to be hittable again.
#define ROGUE_INFUSION_WAIT 50

// Moves made from other characters' effects, see rogue_moves.c.
enum RogueMove {
    ROGUE_MOVE_CHAKRAM, // Axel
    ROGUE_MOVE_NEEDLES, // Vexen
    ROGUE_MOVE_PETALS, // Marluxia
    ROGUE_MOVE_SHARDS, // Vexen
    ROGUE_MOVE_FIREBALL, // Hades
    ROGUE_MOVE_FIRE_BURST, // Hades
    ROGUE_MOVE_ROCK, // Lexaeus
    ROGUE_MOVE_BOMB, // Hook
    ROGUE_MOVES,
    // The new spells, which are moves no relic gives.
    ROGUE_MOVE_WATER = ROGUE_MOVES,
    ROGUE_MOVE_WIND,
    ROGUE_MOVE_MAGNET,
    ROGUE_MOVE_DEFS
};

// How far a thrown move flies each frame.
#define ROGUE_DAMAGE_NUMBERS 6 // shown at once
#define ROGUE_DAMAGE_NUMBER_TIME 36 // frames each stays
#define ROGUE_MOVE_SPEED 0xA00
#define ROGUE_MOVE_ECHO_DELAY 18 // frames before a move is done again
#define ROGUE_MAGNET_FRAMES 24 // frames enemies are pulled for
#define ROGUE_MOVE_POSE 22 // frames Sora holds his casting pose for a move

// A character drawn in place of a boss whose fight they borrow.
enum RogueBossSkin {
    ROGUE_SKIN_NONE,
    ROGUE_SKIN_MICKEY // in place of Leon
};

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
    u8 deckBias; // the starting deck leans to keyblades (1) or spells (2)
    u8 rerolls; // reward rerolls left this run
    u8 chapters; // chapters this run goes through
    u8 newChapter; // set by RogueMetaEndRun when the run unlocked one
    u16 shards; // earned this run, banked when it ends
    u32 relics; // one bit for each RogueRelic the run has
    u8 secondWindUsed; // this battle
    u16 combo; // hits landed without being hit
    u8 comboTimer; // frames until the hit count lapses
    u8 jumpBuffer;
    u8 cardBuffer;
    u8 event; // who is in this event room
    u8 eventDone; // set once they have made their offer
    u8 duel; // set while the battle is a duel picked in an event
    u8 boon; // the boon the run started with
    u8 bossSkin; // who stands in for the boss of the battle, see RogueBossSkin
    u8 oblivion; // the oblivion level the run is played at
    u8 build[ROGUE_BUILDS]; // points of each build, see RogueCountBuild
    u8 playedKind; // kind of the card played alone, ROGUE_NO_KIND otherwise
    u8 projectile; // set while a thrown thing or an added hit tests its hitbox
    u8 echoing; // set while an added hit lands, so that it adds none itself
    u8 finisher; // set while a combo finisher tests its hitbox
    u32 artsUsed; // one bit for each card kind whose art was used this reload
    u8 moveEcho; // the move to do again, plus one, when moveEchoTimer runs out
    u8 moveEchoTimer;
    u8 thorns; // Sora was hurt: the thorns relic answers on the next frame
    u8 pose; // frames Sora still holds the pose of a move
    u8 tagTimer; // frames a tag character still stands in for Sora
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
    ROGUE_DEBUG_FINISHER, // what a combo finisher sets off, without the swing
    ROGUE_DEBUG_TAG, // arg: card kind whose tag character comes in
    ROGUE_DEBUG_ENEMY_TAG, // arg: enemy card id, counted from the first, whose enemy comes in
    ROGUE_DEBUG_MOVE // arg: effect move Sora does
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
    u16 tagHits; // tag attacks that connected this battle
    u16 pulled; // enemy steps towards a magnet
    u16 enemyTags; // enemies and bosses called in by their cards
    u8 slow; // the original routines run in place of the mod's faster ones, to compare
    u16 loadMax; // the longest frame since it was cleared, in scanlines of the 228 there are
    u16 loadLast;
    u32 loadSum; // of every frame since it was cleared
    u16 loadFrames;
    u16 dropped; // video frames missed since it was cleared
    u32 lastVBlank;
    u16 moves; // effect moves started this battle
    u16 moveHits; // hit tests of theirs that connected
    u8 tagAnim; // animation a tag attack plays instead of its own, plus one
} RogueDebug;

extern RogueDebug gRogueDebug;
void RogueDebugField(void);
void RogueDebugBattle(void);

extern RogueRun gRogue;
extern RogueMeta gRogueMeta;
extern Mode gModeRogueShop;
extern Mode gModeRogueHub;
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
u8 RogueBoonUnlocked(u8 boon);
u8 RogueBoonLevel(u8 boon);
void RogueMeetBoon(u8 event);
void RogueAbandonRun(void);
void RogueApplyBoon(void);
u8 RogueBuyUpgrade(u8 upgrade, u8 inRun);
u8 RogueUpgradeMax(u8 upgrade);
u8 RogueUpgradeNeeds(u8 upgrade);
u8 RogueUpgradeNeedsLevel(u8 upgrade);
u8 RogueUpgradeOpen(u8 upgrade);
u8 RogueStarterKind(u8 starter);
u8 RogueStarterCost(u8 starter);
u8 RogueBuyStarter(u8 starter);
u16 RogueUpgradeCost(u8 upgrade);
void RogueLeaveRoomFor(Mode* mode, s32 arg);
struct AnimDef;
struct HumDef;
const struct AnimDef* RogueLeonAnim(u16 slot);
const struct HumDef* RogueLeonDef(void);
const struct AnimDef* RogueHeroAnim(u16 anim);
const struct AnimDef* RogueHeroDirection(u16 action, u16 direction);
void* RogueHeroPalette(void* sora);
u8 RogueHeroUnlocked(u8 hero);
u8 RogueNextHero(void);
void RogueProfileFrame(void);
void RogueMovesTick(void);
void RogueBuildOam(void);
s32 RogueSqrt8(s32 a);
extern const u16 gRogueMickeyPalette[16];
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
u8 RogueTagIn(u16 kind);
struct CardDef;
void RogueOnEnemyCard(const struct CardDef* def);
struct BtlObj;
void RogueSoraPose(struct BtlObj* sora);
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
u16 RogueBufferCard(u16 pressed);
void RogueOnFinisher(struct BtlObj* sora);
void RogueThrowKnives(struct BtlObj* sora);
void RogueRaisePillar(struct BtlObj* sora);
void RogueDoMove(u8 move, struct BtlObj* sora);
u8 RogueMoveUnlocked(u8 move);
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
