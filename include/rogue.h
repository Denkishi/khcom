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
    // The second page.
    ROGUE_UPGRADE_RELIC,
    ROGUE_UPGRADE_GREED,
    ROGUE_UPGRADE_XP,
    ROGUE_UPGRADE_RELOAD,
    ROGUE_UPGRADE_MOVES,
    ROGUE_UPGRADE_HEAL,
    // The third.
    ROGUE_UPGRADE_SECOND_LIFE,
    ROGUE_UPGRADE_CRIT,
    ROGUE_UPGRADE_FINISHER,
    ROGUE_UPGRADE_MAGIC,
    ROGUE_UPGRADE_SUMMON,
    ROGUE_UPGRADE_SEAL,
    // The second page of the tree: plain numbers, in the order of its grid.
    ROGUE_UPGRADE_HP2,
    ROGUE_UPGRADE_HP3,
    ROGUE_UPGRADE_TOUGH,
    ROGUE_UPGRADE_FLOOR_HEAL,
    ROGUE_UPGRADE_CP2,
    ROGUE_UPGRADE_CP3,
    ROGUE_UPGRADE_ATTACK2,
    ROGUE_UPGRADE_ATTACK3,
    ROGUE_UPGRADE_COMBO2,
    ROGUE_UPGRADE_COMBO3,
    ROGUE_UPGRADE_AIR_JUMP2,
    ROGUE_UPGRADE_MOMENTUM,
    ROGUE_UPGRADE_SHARDS,
    ROGUE_UPGRADE_REROLL2,
    ROGUE_UPGRADE_SEAL2,
    ROGUE_UPGRADE_RELIC2,
    ROGUE_UPGRADE_VALUE,
    ROGUE_UPGRADE_CRIT2,
    ROGUE_UPGRADES
};
#define ROGUE_FIRST_PLAIN_UPGRADE ROGUE_UPGRADE_HP2
#define ROGUE_TREE_BRANCHES 3 // to a page
#define ROGUE_TREE_PAGES 2
#define ROGUE_TREE_DEPTH 6
#define ROGUE_UPGRADE_PAGE 6 // upgrades to a page of the tree, and levels kept in each of the save's two arrays

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
    u8 upgrades[ROGUE_UPGRADE_PAGE]; // levels of the first page's upgrades; read them with RogueUpgradeLevel
    u8 bossMoves; // one bit for each boss move unlocked, see ROGUE_BOSS_MOVE_
    u8 boon; // the RogueBoon picked in the hub for the next run
    u8 boonsMet; // one bit for each boon whose character was met in a run
    u8 boonsWon; // one bit for each boon a run was completed with: it is stronger
    u8 oblivion; // difficulty level picked in the hub
    u8 oblivionMax; // highest level unlocked
    u8 hero; // the RogueHero picked in the hub
    u8 seals; // won from bosses, spent on starting cards
    u8 starters; // one bit for each starting card unlocked, see ROGUE_STARTERS
    u8 losses; // runs lost in a row: each softens the next one, see ROGUE_PITY_
    // Added after the first saves: a save without them is read as having none.
    u8 upgrades2[ROGUE_UPGRADE_PAGE]; // levels of the second page's
    u8 unused2[2];
    // Added later still.
    u8 upgrades3[ROGUE_UPGRADE_PAGE];
    u8 unused3[2];
    // And the second page of the tree.
    u8 upgrades4[18];
    u8 unused4[2];
} RogueMeta;

#define ROGUE_META_TUTORIAL_SEEN 1
#define ROGUE_META_2D 16 // an option: battles without depth, see rogue_2d.c
#define ROGUE_META_SWAP_LR 8 // an option: L and R turn the hand of cards the other way
#define ROGUE_META_MICKEY 4 // Mickey was beaten as a boss: he can be played

// Who the player fights as. All of them play as Sora does, drawn as themselves.
enum RogueHero { ROGUE_HERO_SORA, ROGUE_HERO_MICKEY, ROGUE_HERO_SORA_KH2, ROGUE_HERO_RIKU, ROGUE_HERO_ROXAS, ROGUE_HEROES };
const struct AnimDef* RogueHeroHub(u8 action);
void RogueApplyHero(void);

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
    // Those who come to the hub as the game is played, not met in a run.
    ROGUE_BOON_KAIRI, // 20 more max HP and a reward reroll
    ROGUE_BOON_NAMINE, // 30 more CP: a bigger deck
    ROGUE_BOON_AQUA, // the relic that lets Sora survive a blow once
    ROGUE_BOON_TERRA, // strength +1 and the relic of critical hits
    ROGUE_BOON_VENTUS, // an air jump and the relic of hits in the air
    ROGUE_BOON_VANITAS, // strength +3 and the cursed glass cannon
    ROGUE_BOONS
};
#define ROGUE_BOSS_MOVE_LARXENE 1
#define ROGUE_BOSS_MOVE_VEXEN 2
#define ROGUE_BOSS_MOVE_AXEL 4
#define ROGUE_BOSS_MOVE_MARLUXIA 8
#define ROGUE_BOSS_MOVE_HADES 16
#define ROGUE_BOSS_MOVE_LEXAEUS 32
#define ROGUE_BOSS_MOVE_HOOK 64
#define ROGUE_BOSS_MOVE_RIKU 128
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
#define ROGUE_AXEL_PAGES 23
#define ROGUE_MSG_AXEL_LAST (ROGUE_MSG_BASE + ROGUE_AXEL_PAGES - 1)
#define ROGUE_MSG_EVENT_FIRST (ROGUE_MSG_BASE + ROGUE_AXEL_PAGES)
#define ROGUE_MSG_BOON_FIRST (ROGUE_MSG_EVENT_FIRST + ROGUE_EVENTS * ROGUE_EVENT_PAGES)
#define ROGUE_MSG_COUNT (ROGUE_AXEL_PAGES + ROGUE_EVENTS * ROGUE_EVENT_PAGES + ROGUE_BOONS - 1)

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
    // The card game.
    ROGUE_RELIC_ZERO_SHIELD,
    ROGUE_RELIC_TIE_WIN,
    ROGUE_RELIC_PLUS_ONE,
    ROGUE_RELIC_INSTANT_RELOAD,
    ROGUE_RELIC_FREE_FIRST,
    ROGUE_RELIC_RANDOM_SLEIGHT,
    ROGUE_RELIC_FORESIGHT,
    // Cursed: strong, at a price.
    ROGUE_RELIC_HALF_DECK,
    ROGUE_RELIC_NO_HEAL,
    // Movement.
    ROGUE_RELIC_TRIPLE_JUMP,
    ROGUE_RELIC_AIR_DASH,
    ROGUE_RELIC_GLIDE,
    ROGUE_RELIC_TRAIL,
    ROGUE_RELIC_TELEPORT,
    // Thrown moves.
    ROGUE_RELIC_BOUNCE,
    ROGUE_RELIC_PIERCE,
    // What the elements leave on an enemy.
    ROGUE_RELIC_BURN,
    ROGUE_RELIC_FREEZE,
    ROGUE_RELIC_SHOCK,
    // Styles: a combo of plain hits sets off its element every few of them,
    // on the enemy hit. In the order of RogueElement. A deck built on an
    // element fights in its style without the relic.
    ROGUE_RELIC_STYLE_FIRE,
    ROGUE_RELIC_STYLE_ICE,
    ROGUE_RELIC_STYLE_THUNDER,
    // The gadgets of rogue_gadget.c, a hundred and thirty of them, in the order of its table.
    ROGUE_RELIC_FIRST_GADGET,
    ROGUE_RELICS = ROGUE_RELIC_FIRST_GADGET + 130
};
#define ROGUE_GADGETS (ROGUE_RELICS - ROGUE_RELIC_FIRST_GADGET)

// How one of the moves of rogue_moves.c is set going by RogueMoveSpawn.
enum RogueMoveMode {
    ROGUE_MOVE_PLAIN, // as the move is made
    ROGUE_MOVE_ORBIT, // it circles Sora for the whole battle, hitting what it touches. phase: where on the circle, in 1/256
    ROGUE_MOVE_SHARD, // it hangs over Sora for `phase` frames, then flies at an enemy
    ROGUE_MOVE_CIRCLE // as ROGUE_MOVE_ORBIT, for a few seconds
};

// One step of a clip, the way the bosses drawn from a sheet are animated: a
// pose, the frames it stays, how far the boss goes forward and up in each of
// them (in pixels), and what happens as it starts.
typedef struct RogueClipStep {
    u8 pose;
    u8 frames; // 0 ends the clip
    s8 move;
    s8 lift;
    u8 event; // a RogueClipEvent
    u8 arg;
} RogueClipStep;

enum RogueClipEvent {
    ROGUE_CLIP_NOTHING,
    ROGUE_CLIP_HIT, // a hit in front of the boss; arg: how far it reaches, in pixels
    ROGUE_CLIP_SPECIAL, // arg: which of the boss's own
    ROGUE_CLIP_HEAVY, // as a hit, half as strong again
    ROGUE_CLIP_BLINK, // as a hit, made from beside Sora: the boss is there at once, on one side and then the other
    ROGUE_CLIP_THROW, // one of the moves of rogue_moves.c, thrown ahead; arg: the move
    ROGUE_CLIP_SEEK, // the same set round Sora, closing on him one after the other
    ROGUE_CLIP_CAST, // the same made in front of the boss
    ROGUE_CLIP_BEHIND, // the boss is on the far side of Sora, looking back
    ROGUE_CLIP_OVER, // for the next frames the boss is carried over where Sora stands
    ROGUE_CLIP_LAND, // the boss is on the ground again and hits all around; arg: how far
    ROGUE_CLIP_FLASH, // the screen flashes
    ROGUE_CLIP_HEAL // the boss gets a sixth of its HP back
};

struct BtlObj;
void RogueMoveSpawn(u8 move, s32 x, s32 y, s32 z, u8 mode, u8 phase, u8 delay, u8 freeze);
void RogueThunderBolt(struct BtlObj* target);
void RogueGadgetFire(u8 trigger, struct BtlObj* target);
void RogueGadgetTick(void);
void RogueGadgetReset(void);
const u8* RogueGadgetName(u8 gadget);
const u8* RogueGadgetText(u8 gadget);

// When a gadget goes off.
enum RogueGadgetTrigger {
    GADGET_ON_START, // as the battle starts
    GADGET_ON_TIMER, // every `number` tenths of a second
    GADGET_ON_DODGE, // as a dodge takes off
    GADGET_ON_DODGE_STEP, // every `number` frames of a dodge's slide
    GADGET_ON_JUMP,
    GADGET_ON_AIR_JUMP,
    GADGET_ON_LAND,
    GADGET_ON_HIT_N, // on every `number`th hit of a string
    GADGET_ON_FINISHER,
    GADGET_ON_HURT,
    GADGET_ON_KILL,
    GADGET_ON_RELOAD,
    GADGET_ON_ZERO, // a card worth 0 is played
    GADGET_ON_CARD_N, // on every `number`th card played
    GADGET_ON_BREAK, // Sora breaks an enemy's card
    GADGET_ON_LOW_HP, // every `number` tenths of a second under a quarter of the HP
    GADGET_ON_ROTATE, // on every `number`th turn of the hand with L or R
    GADGET_ON_STOCK, // L and R together: a card goes to the stock
    GADGET_ON_SELECT,
    GADGET_ON_LOCK, // on every `number`th enemy newly locked on
    GADGET_ON_IDLE, // every `number` tenths of a second standing still
    GADGET_ON_RUN, // every `number` tenths of a second on the move
    GADGET_ON_AIRTIME, // every `number` tenths of a second in the air
    GADGET_ON_COMBO_END, // a string of `number` hits or more runs out
    GADGET_ON_AIR_HIT, // on every `number`th hit on an enemy in the air
    GADGET_ON_FIRST_HIT, // the first hit of the battle
    GADGET_ON_ENEMY_CARD, // on every `number`th card an enemy plays
    GADGET_ON_BROKEN, // an enemy breaks Sora's card
    GADGET_ON_NINE, // a card worth 9 is played
    GADGET_ON_SPELL, // on every `number`th spell played
    GADGET_ON_ATTACK_CARD, // on every `number`th keyblade card played
    GADGET_ON_SUMMON, // a friend, a summon or an enemy is called in
    GADGET_ON_PRIZE, // on every `number`th prize picked up
    GADGET_ON_UNHURT, // every `number` tenths of a second without being hit
    GADGET_ON_FULL_HP, // every `number` tenths of a second at full HP
    GADGET_TRIGGERS
};

s32 RogueGadgetDamage(s32 damage);
s32 RogueGadgetRunSpeed(s32 speed);
u8 RogueGadgetReloadRate(u8 rate);
u8 RogueGadgetCardValue(u8 value);
u8 RogueGadgetShielded(void);
void RogueGadgetComboEnd(u16 hits);
void RogueGadgetCardPlayed(void);
#define ROGUE_FIRST_CARD_RELIC ROGUE_RELIC_ZERO_SHIELD
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
#define ROGUE_CARD_KINDS 62
#define ROGUE_FIRST_EFFECT_KIND (ROGUE_FIRST_CARD_KIND + 16) // the first card with an effect of its own

// What a card can be enchanted with: it stays on that one card for the run.
enum RogueCardMod {
    ROGUE_MOD_NONE,
    ROGUE_MOD_FIRE, // a hit of the element follows each of its hits; in the order of RogueElement
    ROGUE_MOD_ICE,
    ROGUE_MOD_THUNDER,
    ROGUE_MOD_DOUBLE, // each hit lands twice
    ROGUE_MOD_LIFESTEAL, // each hit heals 1 HP
    ROGUE_MOD_HEAVY, // a quarter more damage
    ROGUE_MOD_PIERCE, // an enemy card must beat it by two to break it
    ROGUE_MOD_LIGHT, // it frees a third of its CP cost
    ROGUE_CARD_MODS
};

void RogueOnCardSlot(u16 deckIndex);
const u8* RogueCardModName(u8 mod);
const u8* RogueCardEffectText(u16 kind);

// What a card of the mod does beyond its base card.
enum RogueCardEffectKind {
    ROGUE_EFFECT_NONE,
    ROGUE_EFFECT_MOVE, // a: the RogueMove Sora does
    ROGUE_EFFECT_SHOCK, // a blast all around Sora. a: 0 plain, 1 fire, 2 ice, 3 thunder; b: its damage, in 1/64 of a swing
    ROGUE_EFFECT_HEAL, // a: the share of max HP healed, in 1/256
    ROGUE_EFFECT_PLUTO, // heals as above and digs up shards
    ROGUE_EFFECT_KNIVES,
    ROGUE_EFFECT_PILLAR,
    ROGUE_EFFECT_SLEIGHT // a: the action of the sleight the card does alone
};

typedef struct RogueCardEffect {
    u8 effect;
    u8 a;
    u8 b;
    u8 unlock; // bit of gRogueMeta.bossMoves that puts the card in the pools, 0 if it is there from the start
} RogueCardEffect;

extern const RogueCardEffect gRogueCardEffects[ROGUE_CARD_KINDS];
#define ROGUE_PLUTO_SHARDS 4
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
    // Boss moves that come as cards only.
    ROGUE_MOVE_FIREWALL, // Axel
    ROGUE_MOVE_SCYTHE, // Marluxia
    ROGUE_MOVE_DEFS,
    // Effects drawn from the sheets of the new characters, see tools/rogue_actors.py.
    ROGUE_MOVE_WAVE = ROGUE_MOVE_DEFS, // Sephiroth's cut that flies
    ROGUE_MOVE_RAID, // the Keyblade thrown, which comes back
    ROGUE_MOVE_PEARL, // a ball of light
    ROGUE_MOVE_PILLAR, // Roxas's pillar of light
    ROGUE_MOVE_ALL
};

// How far a thrown move flies each frame.
#define ROGUE_DAMAGE_NUMBERS 6 // shown at once
#define ROGUE_DAMAGE_NUMBER_TIME 36 // frames each stays
#define ROGUE_MOVE_SPEED 0xA00
// Hits of a combo between one burst of a style and the next: fire, ice, thunder.
#define ROGUE_STYLE_FIRE_EVERY 3
#define ROGUE_STYLE_ICE_EVERY 5
#define ROGUE_STYLE_THUNDER_EVERY 4
// The fight of the bosses that had none of their own: Leon and whoever
// stands in for him.
#define ROGUE_BOSS_AI_SPEED 0x180 // a frame, towards Sora
#define ROGUE_BOSS_AI_REACH 0x2600 // how near he comes before he strikes
#define ROGUE_BOSS_AI_WINDUP 18 // frames from the start of the swing to the hit
#define ROGUE_BOSS_AI_SWING 44 // frames the swing lasts
#define ROGUE_BOSS_AI_REST 80 // frames between swings on the first floor
#define ROGUE_BOSS_AI_REST_MIN 28
#define ROGUE_BOSS_AI_ATTACK 165 // the attack definition of his hit: the Shadow's claw
#define ROGUE_PITY_MAX 3 // losses in a row that count
#define ROGUE_PITY_HP 12 // max HP a run starts with for each
#define ROGUE_GLIDE_SPEED 96 // fall speed while gliding
#define ROGUE_AIR_DASH_SPEED 0x700
#define ROGUE_BURN_TICKS 4 // times a burn hurts, half a second apart
#define ROGUE_FREEZE_FRAMES 90
#define ROGUE_AFTER_EFFECTS 8 // burns, freezes and shocks waiting at once
#define ROGUE_MOVE_ECHO_DELAY 18 // frames before a move is done again
#define ROGUE_MAGNET_FRAMES 24 // frames enemies are pulled for
#define ROGUE_MOVE_POSE 22 // frames Sora holds his casting pose for a move

// A character drawn in place of a boss whose fight they borrow.
enum RogueBossSkin {
    ROGUE_SKIN_NONE,
    ROGUE_SKIN_MICKEY, // in place of Leon
    // The friends, as minibosses of any floor.
    ROGUE_SKIN_BEAST,
    ROGUE_SKIN_JACK,
    ROGUE_SKIN_PETER_PAN,
    ROGUE_SKIN_GOOFY,
    ROGUE_SKIN_DONALD,
    ROGUE_SKIN_ALADDIN,
    ROGUE_SKINS,
    // Those with a fight of their own, drawn from their own sheets: see rogue_actor.c.
    ROGUE_SKIN_SEPHIROTH = ROGUE_SKINS,
    ROGUE_SKIN_SORA_KH2,
    ROGUE_SKIN_ROXAS, // as in Twilight Town
    ROGUE_SKIN_ROXAS_COAT, // in the coat of the Organization
    ROGUE_SKIN_ROXAS_HOOD, // with the hood up
    ROGUE_SKIN_ACTORS_END
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

// The flat battle: the places a technique can be set on, and the techniques.
#define ROGUE_2D_SLOTS 8
enum Rogue2dTech {
    ROGUE_TECH_SWING,
    ROGUE_TECH_RAID,
    ROGUE_TECH_WAVE,
    ROGUE_TECH_PILLAR,
    ROGUE_TECH_COUNTER,
    ROGUE_TECH_CIRCLE,
    ROGUE_TECH_PEARLS,
    ROGUE_TECH_QUAKE,
    ROGUE_TECH_DASH,
    ROGUE_TECH_SLIDE,
    ROGUE_TECH_FIRST_RELIC, // from here on they come with a relic
    ROGUE_2D_TECHS = ROGUE_TECH_FIRST_RELIC + 10
};

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
    u32 relicBits[8]; // one bit for each RogueRelic the run has; ask RogueHasRelic
    u8 airDashUsed; // the air dash was done since Sora last left the ground
    u8 loops; // times the run went past its last floor and on, each an oblivion level higher
    u8 freezing; // set while a hit that freezes whatever it lands on is tested
    u8 freeCard; // the first card played since the reload is not used up
    u8 sleightReady; // the next card played alone does a random sleight
    s16 lastHp; // Sora's HP on the last frame, for the relic that forbids healing
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
    u8 techs[ROGUE_2D_SLOTS]; // the technique set on each place of the flat battle, plus one; 0 for the place's own
    u8 tagTimer; // frames a tag character still stands in for Sora
    u8 arts[ROGUE_ART_KINDS]; // sleight bound to each card kind, 0 for none
    u8 cardMod[ROGUE_CARD_SLOTS]; // the RogueCardMod each collection slot's card is enchanted with
    u8 playedMod; // the one on the card played last
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
    ROGUE_DEBUG_MOVE, // arg: effect move Sora does
    ROGUE_DEBUG_CARD, // arg: one of the mod's card kinds, counted from the first, played alone
    ROGUE_DEBUG_TECH // arg: a move of the flat battle, as if a Keyblade 5 were played: 128 for B, 64 in the air, and the direction (0 none, 1 forward, 2 Up, 3 Down)
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
    u16 airDashes;
    u16 teleports;
    u16 seenMaxHp; // the game's own numbers, copied here each frame in a room for the tests to read
    u16 seenAp;
    u16 seenCp;
    u16 seenDeckCards;
    u8 lastMod; // what the last card played alone was enchanted with
    u16 countCard; // a card id the tests poke...
    u16 seenCount; // ...and how many of it Sora has
    u16 gadgets; // times a gadget relic went off
    u16 gadgetTriggers[GADGET_TRIGGERS]; // times each trigger was met this battle
    u16 gadgetOwed; // effects noted as owed
    u16 stillFrames; // frames this battle Sora stood still on the ground
    u16 airFrames; // and in the air
    u16 styleHits; // times a style set its element off
    u16 bossSwings; // swings of the bosses that fight with the mod's AI
    u16 bossHits; // of those, the ones that landed
    u16 bossClips; // moves the bosses drawn from a sheet have started
    u8 bossClip; // the last of them
    u8 bossForce; // set from outside: the move such a boss makes next, plus one
    u16 heroMoves; // things a hero other than Sora has done that Sora does not
    u16 techs; // moves of the flat battle made
    u16 counters; // hits its counter has turned away
    u8 tech; // the last technique made with B
    u8 techForce; // set from outside: the action every card played does
    s16 techAction; // what the last move asked for by a test came to
    u16 keybladeEffects; // swings of the mod's keyblades that landed
    u16 afterHits; // burns, freezes and shocks dealt
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
u8 RogueUpgradeLevel(u8 upgrade);
u8 RogueTreeNode(u8 branch, u8 depth);
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
struct AnimState;
u8 RogueBossAi(struct BtlObj* boss, struct AnimState* anim, void* tiles);
u8 RogueBossAiMoves(void);
s32 RogueHeroRunSpeed(s32 speed);
u8 RogueHeroAirJumps(void);
s16 RogueHeroDamage(s16 amount);
s16 RogueHeroHurt(s16 amount);
void RogueHeroOnHit(struct BtlObj* target);
void RogueHeroOnSwing(struct BtlObj* sora, u8 finisher);
void RogueHeroTick(void);
void RogueHeroReset(void);
void RogueDirectDamage(struct BtlObj* target, s16 amount);
struct MsgFaceAnim;
#define ROGUE_FACE_FIRST 64 // the portraits of the characters drawn from sheets, after the game's 62
const struct MsgFaceAnim* RogueFaceAnims(s32 portrait);
u8 Rogue2d(void);
void Rogue2dReset(void);
void Rogue2dDebug(u8 arg);
u8 Rogue2dTechAt(u8 slot);
u8 Rogue2dTechOwned(u8 tech);
u8 Rogue2dRelicBound(u8 relic);
void Rogue2dSetTech(u8 slot, u8 tech);
u16 Rogue2dMoveKeys(u16* held, u16 pressed);
u16 Rogue2dCardKeys(u16 pressed);
s32 Rogue2dScale(s32 damage);
struct CardDef;
s32 Rogue2dAction(const struct CardDef* def);
u8 Rogue2dCounterHit(struct BtlObj* sora);
u8 Rogue2dLaunching(void);
void Rogue2dTick(void);
const u8* Rogue2dTechName(u8 tech);
const u8* Rogue2dSlotName(u8 slot);
void RogueShockwaveSmall(struct BtlObj* sora, u16 scale);
u8 RogueActorIs(void);
const struct AnimDef* RogueActorAnim(u16 slot);
const struct HumDef* RogueActorDef(void);
void RogueActorReset(void);
u8 RogueActorTick(struct BtlObj* boss, struct AnimState* anim, void* tiles);
void RogueFoeMove(struct BtlObj* foe, u8 move, s32 x, s32 y, s32 z, u8 mode, u8 phase, u8 delay, u8 left);
s32 RogueFoeHit(struct BtlObj* foe, s32 x, s32 y, s32 z, s16 width, s16 depth, s16 height, u16 scale);
void RogueBossAiReset(void);
const struct AnimDef* RogueHeroAnim(u16 anim);
const struct AnimDef* RogueHeroDirection(u16 action, u16 direction);
const struct AnimDef* RogueHeroField(u16 action, u16 direction);
void* RogueHeroPalette(void* sora);
void* RogueHeroFace(void* sora);
void* RogueHeroFacePalette(void* sora);
u8 RogueHeroUnlocked(u8 hero);
u8 RogueNextHero(void);
void RogueProfileFrame(void);
u8 RogueSwapLR(void);

void RogueMovesTick(void);
struct BtlSoraWork;
void RogueAirControl(struct BtlSoraWork* work, u16 held, u16 pressed);
void RogueOnDodge(struct BtlObj* sora);
void RogueDodgeTrail(struct BtlObj* sora);
void RogueAfterHit(struct BtlObj* target);
void RogueStyleOnHit(struct BtlObj* target);
void RogueStyleReset(void);
void RogueAfterReset(void);
void RogueApplyBurn(struct BtlObj* target, s16 amount);
void RogueApplyFreeze(struct BtlObj* target);
void RogueShockwave(struct BtlObj* sora, u8 element, u16 scale);
void RogueBuildOam(void);
s32 RogueSqrt8(s32 a);
extern const u8 gRogueMenuLabelTiles[], gRogueMenuLabelRikuTiles[];
u8 RogueHasRelic(u8 relic);
void RogueGiveRelic(u8 relic);
u8 RogueBlocksBreak(s32 value);
u8 RogueTieWins(void);
void RogueOnCardBreak(void);
u8 RoguePlayerCardValue(u8 value);
u8 RogueKeepCard(void);
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
struct BtlObj* RogueGaugeTarget(void);
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
