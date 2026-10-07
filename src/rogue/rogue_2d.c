#include "rogue.h"
#include "battle.h"
#include "battle_actor.h"
#include "btl.h"
#include "card.h"
#include "card_def_data.h"
#include "card_ids.h"
#include "card_types.h"
#include "fade.h"
#include "gba/keys.h"
#include "listpool.h"
#include "m4a_song.h"
#include "system_state.h"

// The flat battle, an option. Battles lose their depth: everyone stands on
// one line, and what is left is how far and how high. Up jumps, which frees
// B and Down, and the direction held as a card is played picks what the card
// does. A still swings; with Down on the ground it is the slide, with Up as a
// jump starts a turning hop, in the air with Up a cut that carries Sora and
// the enemy higher, with Down a dive. B plays the card too, as a technique:
// there are eight places for one, on the ground and in the air, each with no
// direction, forward, Up and Down, and the player sets which technique goes
// where. The relics that are moves can be put there as well. Every one of
// them spends the card in hand, the counter too.

#define JUMP_WINDOW 9 // frames after a jump starts in which Up still counts as "as the jump starts"
#define PENDING_TIME 60 // frames the direction held at a press is remembered for the card it plays
#define GUARD_ANIM 50 // the animation of Sora's a counter holds: he stands with the Keyblade raised in front of him
#define COUNTER_TIME 20 // frames a counter turns a hit away for
#define LAUNCH_TIME 24 // frames an uppercut's hits send the enemy up for
#define DIVE_SPEED 1700
#define RISE_SPEED -1500

enum {
    DIR_NONE,
    DIR_FORWARD,
    DIR_UP,
    DIR_DOWN
};

typedef struct RogueTech {
    u8 kind;
    u8 arg;
    u8 relic; // the relic it comes with, ROGUE_RELICS for one that is always there
} RogueTech;

enum {
    KIND_SWING, // nothing but the swing
    KIND_MOVE, // one of the moves of rogue_moves.c; arg: which
    KIND_SLEIGHT, // one of the game's own; arg: its action
    KIND_COUNTER,
    KIND_CIRCLE, // fire turning round Sora for a while
    KIND_PEARLS, // lights that go after the enemies
    KIND_QUAKE, // down at once, and the ground bursts where he lands
    KIND_DASH, // forward through the air, cutting
    KIND_KNIVES,
    KIND_PILLAR
};

// In the order of Rogue2dTech.
static const RogueTech sTechs[ROGUE_2D_TECHS] = {
    { KIND_SWING, 0, ROGUE_RELICS },
    { KIND_MOVE, ROGUE_MOVE_RAID, ROGUE_RELICS },
    { KIND_MOVE, ROGUE_MOVE_WAVE, ROGUE_RELICS },
    { KIND_MOVE, ROGUE_MOVE_PILLAR, ROGUE_RELICS },
    { KIND_COUNTER, 0, ROGUE_RELICS },
    { KIND_CIRCLE, 0, ROGUE_RELICS },
    { KIND_PEARLS, 0, ROGUE_RELICS },
    { KIND_QUAKE, 0, ROGUE_RELICS },
    { KIND_DASH, 0, ROGUE_RELICS },
    { KIND_SLEIGHT, 100, ROGUE_RELICS },
    // The relics that are moves.
    { KIND_MOVE, ROGUE_MOVE_CHAKRAM, ROGUE_RELIC_CHAKRAM + ROGUE_MOVE_CHAKRAM },
    { KIND_MOVE, ROGUE_MOVE_NEEDLES, ROGUE_RELIC_CHAKRAM + ROGUE_MOVE_NEEDLES },
    { KIND_MOVE, ROGUE_MOVE_PETALS, ROGUE_RELIC_CHAKRAM + ROGUE_MOVE_PETALS },
    { KIND_MOVE, ROGUE_MOVE_SHARDS, ROGUE_RELIC_CHAKRAM + ROGUE_MOVE_SHARDS },
    { KIND_MOVE, ROGUE_MOVE_FIREBALL, ROGUE_RELIC_CHAKRAM + ROGUE_MOVE_FIREBALL },
    { KIND_MOVE, ROGUE_MOVE_FIRE_BURST, ROGUE_RELIC_CHAKRAM + ROGUE_MOVE_FIRE_BURST },
    { KIND_MOVE, ROGUE_MOVE_ROCK, ROGUE_RELIC_CHAKRAM + ROGUE_MOVE_ROCK },
    { KIND_MOVE, ROGUE_MOVE_BOMB, ROGUE_RELIC_CHAKRAM + ROGUE_MOVE_BOMB },
    { KIND_KNIVES, 0, ROGUE_RELIC_KNIVES },
    { KIND_PILLAR, 0, ROGUE_RELIC_ICE_PILLAR },
};

// What each place holds until the player sets something else: on the ground
// with no direction, forward, Up and Down, then the same in the air.
static const u8 sDefaults[ROGUE_2D_SLOTS] = {
    ROGUE_TECH_RAID, ROGUE_TECH_WAVE, ROGUE_TECH_PILLAR, ROGUE_TECH_COUNTER,
    ROGUE_TECH_PEARLS, ROGUE_TECH_DASH, ROGUE_TECH_CIRCLE, ROGUE_TECH_QUAKE,
};

u8 gRogueWide;

static s32 sLane; // the line everyone stands on
static u8 sLaneSet;
static u8 sJumpAge; // frames since the last jump started, 0xFF when long ago
static u8 sPendingButton; // 1 for A, 2 for B, 0 when nothing is remembered
static u8 sPendingDir;
static u8 sPendingAir;
static u8 sPendingTime;
static u8 sCounter; // frames left of a counter
static u8 sLaunch; // frames left in which Sora's hits send the enemy up
static u8 sSpin; // hits a turning hop still owes
static u8 sSpinWait;
static u8 sDive; // 1: falling to hit, 2: falling to make the ground burst
static u8 sDash; // frames left of the dash through the air
static u8 sPower; // the value of the card a technique was made with, plus one; 0 when none is going
static u8 sPowerTime;
static u8 sPressed;
static u32 sPressFrame;

u8 Rogue2d(void) {
    return (gRogueMeta.flags & ROGUE_META_2D) != 0 && gRogueMeta.hero != ROGUE_HERO_RIKU;
}

void Rogue2dReset(void) {
    sLaneSet = 0;
    sJumpAge = 0xFF;
    sPendingButton = 0;
    sCounter = 0;
    sLaunch = 0;
    sSpin = 0;
    sDive = 0;
    sDash = 0;
    sPower = 0;
    sPressed = 0;
}

static BtlSoraWork* Rogue2dWork(BtlObj* sora) {
    return (BtlSoraWork*)((u8*)sora - (u32) & ((BtlSoraWork*)0)->actor);
}

static u8 Rogue2dAirborne(BtlObj* sora) {
    return sora->z < sora->unk_010;
}

// The technique a place holds.
u8 Rogue2dTechAt(u8 slot) {
    u8 tech = gRogue.techs[slot];

    // Nothing set, or a relic's that the run no longer has.
    if (tech == 0 || !Rogue2dTechOwned(tech - 1)) {
        return sDefaults[slot];
    }

    return tech - 1;
}

u8 Rogue2dTechOwned(u8 tech) {
    return sTechs[tech].relic == ROGUE_RELICS || RogueHasRelic(sTechs[tech].relic);
}

// A relic set on a button no longer goes off by itself on a finisher.
u8 Rogue2dRelicBound(u8 relic) {
    u8 slot;

    if (!Rogue2d()) {
        return 0;
    }

    for (slot = 0; slot < ROGUE_2D_SLOTS; slot++) {
        if (sTechs[Rogue2dTechAt(slot)].relic == relic) {
            return 1;
        }
    }

    return 0;
}

void Rogue2dSetTech(u8 slot, u8 tech) {
    gRogue.techs[slot] = tech + 1;
}

// Sora's keys, as his battle task reads them: Up is the jump, B and the two
// directions that went into the depth are no longer his to move with.
u16 Rogue2dMoveKeys(u16* held, u16 pressed) {
    u16 had = *held;

    if (!Rogue2d()) {
        return pressed;
    }

    *held &= ~(DPAD_UP | DPAD_DOWN | B_BUTTON);

    if (had & DPAD_UP) {
        *held |= B_BUTTON;
    }

    if (pressed & DPAD_UP) {
        sJumpAge = 0;
        pressed = (pressed & ~(DPAD_UP | DPAD_DOWN)) | B_BUTTON;
    } else {
        pressed &= ~(DPAD_UP | DPAD_DOWN | B_BUTTON);
    }

    return pressed;
}

// The keys as the hand of cards reads them: B plays the card as A does. What
// was held is remembered for the card it plays, which may come a moment later.
u16 Rogue2dCardKeys(u16 pressed) {
    BtlObj* sora = gBtlWork->actor;
    u16 held;

    if (!Rogue2d() || sora == 0 || !(pressed & (A_BUTTON | B_BUTTON))) {
        return pressed;
    }

    held = GetKeysHeld();
    sPendingButton = (pressed & A_BUTTON) ? 1 : 2;
    sPendingAir = Rogue2dAirborne(sora) && sJumpAge > JUMP_WINDOW;
    sPendingTime = PENDING_TIME;

    if (held & DPAD_DOWN) {
        sPendingDir = DIR_DOWN;
    } else if ((held & DPAD_UP) || (sJumpAge <= JUMP_WINDOW && sPendingButton == 1)) {
        sPendingDir = DIR_UP;
    } else if (held & (DPAD_LEFT | DPAD_RIGHT)) {
        sPendingDir = DIR_FORWARD;
    } else {
        sPendingDir = DIR_NONE;
    }

    return pressed | A_BUTTON;
}

static void Rogue2dPower(const CardDef* def) {
    sPower = def->unk_20 + 1;
    sPowerTime = 90;
}

// The damage of a move made as a technique: from 70% with a 0 to 160% with a 9.
s32 Rogue2dScale(s32 damage) {
    if (sPower == 0) {
        return damage;
    }

    return damage * (60 + sPower * 10) / 100;
}

// What the card played does, given what was held: an action of Sora's battle
// task, or -1 for what the card would do anyway.
s32 Rogue2dAction(const CardDef* def) {
    BtlObj* sora = gBtlWork->actor;
    BtlSoraWork* work;
    const RogueTech* tech;
    u8 button = sPendingButton;
    s32 left;
    s32 i;

    if (gRogueDebug.techForce != 0) {
        return gRogueDebug.techForce;
    }

    sPendingButton = 0;

    if (!Rogue2d() || button == 0 || sora == 0) {
        return -1;
    }

    work = Rogue2dWork(sora);
    left = (sora->flags & 4) != 0;

    if (button == 1) {
        // A with a direction. Only a Keyblade does these: a spell is still cast.
        if (!ROGUE_IS_KEYBLADE((def - gCardDefs) / 10)) {
            return -1;
        }

        if (!sPendingAir) {
            if (sPendingDir == DIR_DOWN) {
                gRogueDebug.techs++;
                return 100;
            }

            if (sPendingDir == DIR_UP) {
                // The hop that turns: it hits four times around him.
                sSpin = 4;
                sSpinWait = 3;
                work->unk_150 = -700;
                Rogue2dPower(def);
                gRogueDebug.techs++;
            }

            return -1;
        }

        if (sPendingDir == DIR_UP) {
            // The cut that rises: he goes up, and so does what it hits.
            work->unk_150 = RISE_SPEED;
            sLaunch = LAUNCH_TIME;
            gRogueDebug.techs++;
        } else if (sPendingDir == DIR_DOWN) {
            work->unk_150 = DIVE_SPEED;
            sDive = 1;
            gRogueDebug.techs++;
        }

        return -1;
    }

    // B: the technique of the place.
    tech = &sTechs[Rogue2dTechAt((sPendingAir ? 4 : 0) + sPendingDir)];
    Rogue2dPower(def);
    gRogueDebug.techs++;
    gRogueDebug.tech = tech - sTechs;

    switch (tech->kind) {
    case KIND_MOVE:
        RogueDoMove(tech->arg, sora);
        break;
    case KIND_SLEIGHT:
        return tech->arg;
    case KIND_COUNTER:
        // He does not swing: he stands with the Keyblade up, a shell of light
        // round him, for as long as the counter lasts.
        sCounter = COUNTER_TIME;
        gRogue.pose = 0;
        SetBtlSoraAnimation(work, gRogueDebug.guardAnim != 0 ? gRogueDebug.guardAnim : GUARD_ANIM, 0);
        gRogue.pose = COUNTER_TIME;
        m4aSongNumStart(SONG_EF_RAC_3TR);

        RogueMoveSpawn(ROGUE_MOVE_WAVE, sora->x, sora->y, sora->z, ROGUE_MOVE_GUARD, 0, 0, 0);
        RogueMoveSpawn(ROGUE_MOVE_WAVE, sora->x, sora->y, sora->z, ROGUE_MOVE_GUARD, 1, 0, 0);

        return ROGUE_ACTION_NONE;
    case KIND_CIRCLE:
        for (i = 0; i < 3; i++) {
            RogueMoveSpawn(ROGUE_MOVE_FIREBALL, sora->x, sora->y, sora->z, ROGUE_MOVE_CIRCLE, i * 85, 0, 0);
        }
        break;
    case KIND_PEARLS:
        for (i = 0; i < 3; i++) {
            RogueMoveSpawn(ROGUE_MOVE_PEARL, sora->x, sora->y, sora->z - 0x2000, ROGUE_MOVE_SHARD, 6 + i * 6, i * 3, 0);
        }
        break;
    case KIND_QUAKE:
        if (Rogue2dAirborne(sora)) {
            work->unk_150 = DIVE_SPEED;
            sDive = 2;
        } else {
            RogueShockwave(sora, 0, Rogue2dScale(300));
        }
        break;
    case KIND_DASH:
        sDash = 10;
        break;
    case KIND_KNIVES:
        RogueThrowKnives(sora);
        break;
    case KIND_PILLAR:
        RogueRaisePillar(sora);
        break;
    }

    return ROGUE_ACTION_SWING;
}

// For the tests: one of the moves, as if a Keyblade of value 5 were played with those keys.
void Rogue2dDebug(u8 arg) {
    sPendingButton = (arg & 128) ? 2 : 1;
    sPendingAir = (arg & 64) != 0;
    sPendingDir = arg & 3;
    sPendingTime = PENDING_TIME;
    gRogueDebug.techAction = Rogue2dAction(&gCardDefs[CARD_ID(CARD_KINGDOM_KEY, 5)]);
}

// A hit on Sora while he counters: it is turned away, and whoever made it
// takes one back and is held where it stands. Returns 1 if it was.
u8 Rogue2dCounterHit(BtlObj* sora) {
    BtlObj* foe = gBtlWork->actor3;

    if (sCounter == 0) {
        return 0;
    }

    sCounter = 0;
    FadeFromAmount(2, 10, 16);
    m4aSongNumStart(SONG_EF_SUMMON_UP);
    gRogueDebug.counters++;

    if (foe != 0 && foe != sora) {
        RogueDirectDamage(foe, Rogue2dScale(sora->unk_030 * 3));
        RogueApplyFreeze(foe);
    }

    return 1;
}

// 1 while an uppercut's hits send the enemy up with Sora.
u8 Rogue2dLaunching(void) {
    return sLaunch != 0;
}

// Called once a frame in battle.
void Rogue2dTick(void) {
    BtlObj* sora = gBtlWork->actor;
    BtlObj* actor;

    if (!Rogue2d() || sora == 0) {
        return;
    }

    // Everyone on the one line, which is where Sora stood as the battle began.
    if (!sLaneSet) {
        sLane = sora->y;
        sLaneSet = 1;
    }

    for (actor = (BtlObj*)ListPoolFirst(&gBtlWork->pool); actor != 0; actor = (BtlObj*)ListPoolNext(&actor->node)) {
        actor->y = sLane;
        actor->vy = 0;
    }

    sora->y = sLane;

    if (sJumpAge != 0xFF) {
        sJumpAge++;
    }

    if (sPendingTime != 0 && --sPendingTime == 0) {
        sPendingButton = 0;
    }

    if (sCounter != 0) {
        sCounter--;
    }

    if (sLaunch != 0) {
        sLaunch--;
    }

    if (sPowerTime != 0 && --sPowerTime == 0) {
        sPower = 0;
    }

    if (sSpin != 0 && --sSpinWait == 0) {
        sSpin--;
        sSpinWait = 5;
        RogueShockwaveSmall(sora, Rogue2dScale(110));
    }

    if (sDash != 0) {
        sDash--;
        sora->x += (sora->flags & 4) ? -0x600 : 0x600;
    }

    // The dive ends on the ground.
    if (sDive != 0 && !Rogue2dAirborne(sora)) {
        if (sDive == 2) {
            RogueShockwave(sora, 0, Rogue2dScale(300));
        } else {
            RogueShockwaveSmall(sora, Rogue2dScale(160));
        }

        sDive = 0;
    }
}

// The names, for the options page.

static const u8 sTech0[] = "Colpo semplice";
static const u8 sTech1[] = "Lancio del Keyblade";
static const u8 sTech2[] = "Onda di lama";
static const u8 sTech3[] = "Pilastro di luce";
static const u8 sTech4[] = "Contrattacco";
static const u8 sTech5[] = "Cerchio di fuoco";
static const u8 sTech6[] = "Perle di luce";
static const u8 sTech7[] = "Terremoto";
static const u8 sTech8[] = "Scatto tagliente";
static const u8 sTech9[] = "Scivolata";
static const u8 sTech10[] = "Chakram";
static const u8 sTech11[] = "Aghi di ghiaccio";
static const u8 sTech12[] = "Petali";
static const u8 sTech13[] = "Schegge di gelo";
static const u8 sTech14[] = "Globo di fuoco";
static const u8 sTech15[] = "Vampa";
static const u8 sTech16[] = "Roccia";
static const u8 sTech17[] = "Bomba";
static const u8 sTech18[] = "Coltelli di tuono";
static const u8 sTech19[] = "Blocco di ghiaccio";
static const u8* const sTechNames[ROGUE_2D_TECHS] = {
    sTech0, sTech1, sTech2, sTech3, sTech4, sTech5, sTech6, sTech7, sTech8, sTech9,
    sTech10, sTech11, sTech12, sTech13, sTech14, sTech15, sTech16, sTech17, sTech18, sTech19,
};

static const u8 sSlot0[] = "B a terra";
static const u8 sSlot1[] = "B + avanti";
static const u8 sSlot2[] = "B dopo SU";
static const u8 sSlot3[] = "B + GI\xD9";
static const u8 sSlot4[] = "B in aria";
static const u8 sSlot5[] = "B + avanti, aria";
static const u8 sSlot6[] = "B + SU in aria";
static const u8 sSlot7[] = "B + GI\xD9 in aria";
static const u8* const sSlotNames[ROGUE_2D_SLOTS] = { sSlot0, sSlot1, sSlot2, sSlot3, sSlot4, sSlot5, sSlot6, sSlot7 };

const u8* Rogue2dTechName(u8 tech) {
    return sTechNames[tech];
}

const u8* Rogue2dSlotName(u8 slot) {
    return sSlotNames[slot];
}

// The card button, kept. The hand of cards reads it only while Sora can play
// one; a press made a moment too soon is remembered and played as soon as he
// can. In the flat battle B counts as well, with what was held.

void RogueNoteCardPress(void) {
    if (Rogue2dCardKeys(GetKeysPressed()) & A_BUTTON) {
        sPressed = 1;
        sPressFrame = gFrameCounter;
    }
}

u8 RogueTakeCardPress(void) {
    if (!sPressed) {
        return 0;
    }

    sPressed = 0;

    if (gFrameCounter - sPressFrame > ROGUE_PRESS_BUFFER) {
        return 0;
    }

    if (gFrameCounter != sPressFrame) {
        gRogueDebug.presses++;
    }

    return 1;
}
