#include "rogue.h"
#include "card_ids.h"
#include "agb_sram.h"
#include "battle.h"
#include "map_api.h"
#include "save.h"
#include "system_state.h"

// What survives between runs: memory shards, the chapters unlocked and the
// upgrades bought from Axel. It has a block of its own in the SRAM the
// original game leaves unused.

#define META_SRAM ((u8*)0x0E007000)
#define META_MAGIC 0x314D4752 /* "RGM1" */
#define SUSPEND_SRAM (META_SRAM + 0x80)
#define SUSPEND_MAGIC 0x31534752 /* "RGS1" */

// The run in progress, written by the pause menu's quick save next to the
// game's own suspend save and consumed when the run is resumed.
typedef struct RogueSuspend {
    u32 magic;
    u16 checksum;
    u16 unused;
    RogueRun run;
} RogueSuspend;

static RogueSuspend sSuspend;

RogueMeta gRogueMeta;

// The tree: three branches, each upgrade open once the one before it on its
// branch has a level (two, after the first of a branch).
static const RogueUpgradeDef sUpgrades[ROGUE_UPGRADES] = {
    { 5, 8, ROGUE_UPGRADES, 0 }, // max HP
    { 5, 8, ROGUE_UPGRADE_HP, 2 }, // CP
    { 3, 15, ROGUE_UPGRADES, 0 }, // strength
    { 1, 40, ROGUE_UPGRADE_ATTACK, 2 }, // combo plus
    { 1, 30, ROGUE_UPGRADE_COMBO, 1 }, // air jump
    { 3, 12, ROGUE_UPGRADE_HEAL, 1 }, // rerolls
    { 1, 60, ROGUE_UPGRADE_REROLL, 1 }, // a relic to start with
    { 3, 20, ROGUE_UPGRADES, 0 }, // more shards kept
    { 1, 35, ROGUE_UPGRADE_GREED, 1 }, // cards learn faster
    { 3, 15, ROGUE_UPGRADE_AIR_JUMP, 1 }, // faster reload
    { 3, 20, ROGUE_UPGRADE_XP, 1 }, // stronger moves
    { 3, 15, ROGUE_UPGRADE_CP, 1 }, // healing after battles
    { 1, 80, ROGUE_UPGRADE_RELIC, 1 }, // the second wind relic to start with
    { 3, 25, ROGUE_UPGRADE_RELOAD, 1 }, // critical hits
    { 3, 25, ROGUE_UPGRADE_CRIT, 1 }, // stronger finishers
    { 3, 20, ROGUE_UPGRADE_MOVES, 1 }, // stronger spells
    { 3, 20, ROGUE_UPGRADE_MAGIC, 1 }, // stronger summons and called enemies
    { 1, 50, ROGUE_UPGRADE_SUMMON, 1 }, // a seal more from each boss
    // The second page: plain numbers. Its first and second branches grow out
    // of the first page's HP and strength at their last level.
    { 5, 12, ROGUE_UPGRADE_HP, 5 }, // +10 max HP
    { 5, 18, ROGUE_UPGRADE_HP2, 5 }, // +15 max HP
    { 3, 30, ROGUE_UPGRADE_HP3, 1 }, // 4% less damage taken
    { 2, 30, ROGUE_UPGRADE_TOUGH, 1 }, // 15% of max HP back at each new floor
    { 5, 12, ROGUE_UPGRADE_FLOOR_HEAL, 1 }, // +15 CP
    { 5, 18, ROGUE_UPGRADE_CP2, 5 }, // +20 CP
    { 3, 25, ROGUE_UPGRADE_ATTACK, 3 }, // strength +1
    { 3, 40, ROGUE_UPGRADE_ATTACK2, 3 }, // strength +1
    { 1, 60, ROGUE_UPGRADE_ATTACK3, 1 }, // a combo hit more
    { 1, 90, ROGUE_UPGRADE_COMBO2, 1 }, // and another
    { 1, 60, ROGUE_UPGRADE_COMBO3, 1 }, // the second air jump
    { 1, 70, ROGUE_UPGRADE_AIR_JUMP2, 1 }, // the momentum relic to start with
    { 3, 10, ROGUE_UPGRADES, 0 }, // 10 shards to start with
    { 2, 25, ROGUE_UPGRADE_SHARDS, 1 }, // a reroll more
    { 1, 60, ROGUE_UPGRADE_REROLL2, 1 }, // a seal more from each boss
    { 1, 90, ROGUE_UPGRADE_SEAL2, 1 }, // another relic to start with
    { 2, 40, ROGUE_UPGRADE_RELIC2, 1 }, // cards of the starting deck worth one more at most
    { 3, 30, ROGUE_UPGRADE_VALUE, 1 }, // 4% more critical hits
};

// The upgrade at each place of the tree, a branch a row.
static const u8 sTree[ROGUE_TREE_PAGES * ROGUE_TREE_BRANCHES][ROGUE_TREE_DEPTH] = {
    { ROGUE_UPGRADE_HP, ROGUE_UPGRADE_CP, ROGUE_UPGRADE_HEAL, ROGUE_UPGRADE_REROLL, ROGUE_UPGRADE_RELIC, ROGUE_UPGRADE_SECOND_LIFE },
    { ROGUE_UPGRADE_ATTACK, ROGUE_UPGRADE_COMBO, ROGUE_UPGRADE_AIR_JUMP, ROGUE_UPGRADE_RELOAD, ROGUE_UPGRADE_CRIT, ROGUE_UPGRADE_FINISHER },
    { ROGUE_UPGRADE_GREED, ROGUE_UPGRADE_XP, ROGUE_UPGRADE_MOVES, ROGUE_UPGRADE_MAGIC, ROGUE_UPGRADE_SUMMON, ROGUE_UPGRADE_SEAL },
    { ROGUE_UPGRADE_HP2, ROGUE_UPGRADE_HP3, ROGUE_UPGRADE_TOUGH, ROGUE_UPGRADE_FLOOR_HEAL, ROGUE_UPGRADE_CP2, ROGUE_UPGRADE_CP3 },
    { ROGUE_UPGRADE_ATTACK2, ROGUE_UPGRADE_ATTACK3, ROGUE_UPGRADE_COMBO2, ROGUE_UPGRADE_COMBO3, ROGUE_UPGRADE_AIR_JUMP2,
      ROGUE_UPGRADE_MOMENTUM },
    { ROGUE_UPGRADE_SHARDS, ROGUE_UPGRADE_REROLL2, ROGUE_UPGRADE_SEAL2, ROGUE_UPGRADE_RELIC2, ROGUE_UPGRADE_VALUE, ROGUE_UPGRADE_CRIT2 },
};

u8 RogueTreeNode(u8 branch, u8 depth) {
    return sTree[branch][depth];
}

static u8* RogueUpgradeSlot(u8 upgrade) {
    if (upgrade < ROGUE_UPGRADE_PAGE) {
        return &gRogueMeta.upgrades[upgrade];
    }

    if (upgrade < ROGUE_UPGRADE_PAGE * 2) {
        return &gRogueMeta.upgrades2[upgrade - ROGUE_UPGRADE_PAGE];
    }

    if (upgrade < ROGUE_FIRST_PLAIN_UPGRADE) {
        return &gRogueMeta.upgrades3[upgrade - ROGUE_UPGRADE_PAGE * 2];
    }

    return &gRogueMeta.upgrades4[upgrade - ROGUE_FIRST_PLAIN_UPGRADE];
}

u8 RogueUpgradeLevel(u8 upgrade) {
    return *RogueUpgradeSlot(upgrade);
}

// The cards that can be unlocked to start every run with, and their cost in
// seals.
static const u8 sStarters[ROGUE_STARTERS][2] = {
    { CARD_FIRE, 2 }, { CARD_BLIZZARD, 2 }, { CARD_THUNDER, 2 }, { CARD_SIMBA, 3 }, { CARD_CLOUD, 4 }, { CARD_LIONHEART, 4 },
};

u8 RogueStarterKind(u8 starter) {
    return sStarters[starter][0];
}

u8 RogueStarterCost(u8 starter) {
    return sStarters[starter][1];
}

u8 RogueBuyStarter(u8 starter) {
    if ((gRogueMeta.starters & (1 << starter)) || gRogueMeta.seals < sStarters[starter][1]) {
        return 0;
    }

    gRogueMeta.seals -= sStarters[starter][1];
    gRogueMeta.starters |= 1 << starter;
    RogueMetaSave();
    return 1;
}

u8 RogueUpgradeNeeds(u8 upgrade) {
    return sUpgrades[upgrade].needs;
}

u8 RogueUpgradeNeedsLevel(u8 upgrade) {
    return sUpgrades[upgrade].needsLevel;
}

// Whether the upgrade's place in the tree has been reached.
u8 RogueUpgradeOpen(u8 upgrade) {
    u8 needs = sUpgrades[upgrade].needs;

    return needs == ROGUE_UPGRADES || RogueUpgradeLevel(needs) >= sUpgrades[upgrade].needsLevel;
}

static void RogueMetaReset(void) {
    u8* p = (u8*)&gRogueMeta;
    u32 i;

    for (i = 0; i < sizeof(gRogueMeta); i++) {
        p[i] = 0;
    }

    gRogueMeta.magic = META_MAGIC;
    gRogueMeta.chapters = 1;
}

void RogueMetaLoad(void) {
    // The save has grown a few times: one of an earlier size is read as it was,
    // with nothing in what was added since.
    static const u8 sizes[] = { sizeof(RogueMeta), offsetof(RogueMeta, upgrades4), offsetof(RogueMeta, upgrades3),
                                offsetof(RogueMeta, upgrades2) };
    u8* bytes = (u8*)&gRogueMeta;
    u32 i;
    u32 j;

    ReadSramFast(META_SRAM, bytes, sizeof(gRogueMeta));

    if (gRogueMeta.magic == META_MAGIC) {
        for (i = 0; i < sizeof(sizes); i++) {
            if (gRogueMeta.checksum == SaveChecksum((u16*)&gRogueMeta.shards, sizes[i] - offsetof(RogueMeta, shards))) {
                for (j = sizes[i]; j < sizeof(gRogueMeta); j++) {
                    bytes[j] = 0;
                }

                return;
            }
        }
    }

    RogueMetaReset();
}

void RogueMetaSave(void) {
    gRogueMeta.checksum = SaveChecksum((u16*)&gRogueMeta.shards, sizeof(gRogueMeta) - offsetof(RogueMeta, shards));
    WriteSramFast((u8*)&gRogueMeta, META_SRAM, sizeof(gRogueMeta));
}

u8 RogueUpgradeMax(u8 upgrade) {
    return sUpgrades[upgrade].levels;
}

// Each level costs as much again as the first.
u16 RogueUpgradeCost(u8 upgrade) {
    return sUpgrades[upgrade].cost * (RogueUpgradeLevel(upgrade) + 1);
}

// Gives one level of an upgrade to the run in progress.
static void RogueApplyUpgrade(u8 upgrade) {
    switch (upgrade) {
    case ROGUE_UPGRADE_HP:
        gGameState.progression.maxHp += 10;
        gGameState.hp += 10;
        break;
    case ROGUE_UPGRADE_CP:
        gGameState.progression.cp += 15;
        break;
    case ROGUE_UPGRADE_ATTACK:
        gGameState.progression.ap++;
        break;
    case ROGUE_UPGRADE_COMBO:
        gRogue.comboPlus++;
        break;
    case ROGUE_UPGRADE_AIR_JUMP:
        gRogue.airJumps++;
        break;
    case ROGUE_UPGRADE_REROLL:
        gRogue.rerolls++;
        break;
    case ROGUE_UPGRADE_SECOND_LIFE:
        RogueGiveRelic(ROGUE_RELIC_SECOND_WIND);
        break;
    case ROGUE_UPGRADE_HP2:
        gGameState.progression.maxHp += 10;
        gGameState.hp += 10;
        break;
    case ROGUE_UPGRADE_HP3:
        gGameState.progression.maxHp += 15;
        gGameState.hp += 15;
        break;
    case ROGUE_UPGRADE_CP2:
        gGameState.progression.cp += 15;
        break;
    case ROGUE_UPGRADE_CP3:
        gGameState.progression.cp += 20;
        break;
    case ROGUE_UPGRADE_ATTACK2:
    case ROGUE_UPGRADE_ATTACK3:
        gGameState.progression.ap++;
        break;
    case ROGUE_UPGRADE_COMBO2:
    case ROGUE_UPGRADE_COMBO3:
        if (gRogue.comboPlus < ROGUE_COMBO_PLUS_MAX) {
            gRogue.comboPlus++;
        }
        break;
    case ROGUE_UPGRADE_AIR_JUMP2:
        if (gRogue.airJumps < ROGUE_AIR_JUMPS_MAX) {
            gRogue.airJumps++;
        }
        break;
    case ROGUE_UPGRADE_MOMENTUM:
        RogueGiveRelic(ROGUE_RELIC_MOMENTUM);
        break;
    case ROGUE_UPGRADE_SHARDS:
        gRogue.shards += 10;
        break;
    case ROGUE_UPGRADE_REROLL2:
        gRogue.rerolls++;
        break;
    case ROGUE_UPGRADE_RELIC2: {
        u8 relic = RogueRollRelic();

        if (relic != ROGUE_RELICS) {
            RogueGiveRelic(relic);
        }
        break;
    }
    case ROGUE_UPGRADE_RELIC: {
        u8 relic = RogueRollRelic();

        if (relic != ROGUE_RELICS) {
            RogueGiveRelic(relic);
        }
        break;
    }
    }
}

// Called when a run starts, before its deck is built.
void RogueApplyUpgrades(void) {
    u8 upgrade;
    u8 level;

    for (upgrade = 0; upgrade < ROGUE_UPGRADES; upgrade++) {
        for (level = 0; level < RogueUpgradeLevel(upgrade); level++) {
            RogueApplyUpgrade(upgrade);
        }
    }
}

// The characters of the hub. Axel is always there. Each of the others comes
// to stay once Sora has met them in an event room of a run, and from then on
// offers a boon for the next run. Completing a run with a boon makes it
// stronger for good.

// The event each boon's character is met in, by boon.
static const u8 sBoonEvents[ROGUE_BOONS] = {
    0xFF, ROGUE_EVENT_BELLE, ROGUE_EVENT_MOOGLE, ROGUE_EVENT_LEON, ROGUE_EVENT_YUFFIE, ROGUE_EVENT_HERCULES,
    ROGUE_EVENT_TIGGER, ROGUE_EVENT_JACK, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

u8 RogueBoonUnlocked(u8 boon) {
    if (boon == ROGUE_BOON_NONE) {
        return 1;
    }

    // Those met in no run come as the game is played.
    switch (boon) {
    case ROGUE_BOON_KAIRI:
        return gRogueMeta.wins >= 1;
    case ROGUE_BOON_NAMINE:
    case ROGUE_BOON_VENTUS:
        return gRogueMeta.chapters >= 2;
    case ROGUE_BOON_AQUA:
        return gRogueMeta.wins >= 2;
    case ROGUE_BOON_TERRA:
        return gRogueMeta.chapters >= 3;
    case ROGUE_BOON_VANITAS:
        return gRogueMeta.wins >= 3;
    }

    return (gRogueMeta.boonsMet >> boon) & 1;
}

// 2 once a run has been completed with the boon, 1 before.
u8 RogueBoonLevel(u8 boon) {
    // The later ones have one level only.
    if (boon >= ROGUE_BOON_KAIRI) {
        return 1;
    }

    return ((gRogueMeta.boonsWon >> boon) & 1) + 1;
}

// Called when Sora talks to the character of an event room.
void RogueMeetBoon(u8 event) {
    u8 boon;

    for (boon = 1; boon < ROGUE_BOONS; boon++) {
        if (sBoonEvents[boon] == event && !RogueBoonUnlocked(boon)) {
            gRogueMeta.boonsMet |= 1 << boon;
            RogueMetaSave();
        }
    }
}

// Gives the run the boon picked in the hub. Called when a run starts, before
// its deck is built. The second figure is the boon at level 2.
void RogueApplyBoon(void) {
    u8 strong = RogueBoonLevel(gRogueMeta.boon) == 2;
    u8 relic;
    u8 i;

    // Pity: some more HP after each run lost in a row.
    gGameState.progression.maxHp += ROGUE_PITY_HP * gRogueMeta.losses;
    gGameState.hp += ROGUE_PITY_HP * gRogueMeta.losses;

    gRogue.boon = gRogueMeta.boon;

    switch (gRogueMeta.boon) {
    case ROGUE_BOON_BELLE:
        // 30 or 50 more max HP.
        gGameState.progression.maxHp += strong ? 50 : 30;
        gGameState.hp += strong ? 50 : 30;
        break;
    case ROGUE_BOON_MOOGLE:
        // Two or three rerolls.
        gRogue.rerolls += strong ? 3 : 2;
        break;
    case ROGUE_BOON_LEON:
        // A deck of keyblades, and strength +1.
        gRogue.deckBias = 1;

        if (strong) {
            gGameState.progression.ap++;
        }
        break;
    case ROGUE_BOON_YUFFIE:
        // A deck of spells, and 20 more CP for it.
        gRogue.deckBias = 2;

        if (strong) {
            gGameState.progression.cp += 20;
        }
        break;
    case ROGUE_BOON_HERCULES:
        // Strength +2 or +3.
        gGameState.progression.ap += strong ? 3 : 2;
        break;
    case ROGUE_BOON_TIGGER:
        // One air jump, or both.
        gRogue.airJumps = strong ? ROGUE_AIR_JUMPS_MAX : 1;
        break;
    case ROGUE_BOON_KAIRI:
        gGameState.progression.maxHp += 20;
        gGameState.hp += 20;
        gRogue.rerolls++;
        break;
    case ROGUE_BOON_NAMINE:
        gGameState.progression.cp += 30;
        break;
    case ROGUE_BOON_AQUA:
        RogueGiveRelic(ROGUE_RELIC_SECOND_WIND);
        break;
    case ROGUE_BOON_TERRA:
        gGameState.progression.ap++;
        RogueGiveRelic(ROGUE_RELIC_CRITICAL);
        break;
    case ROGUE_BOON_VENTUS:
        if (gRogue.airJumps < 1) {
            gRogue.airJumps = 1;
        }

        RogueGiveRelic(ROGUE_RELIC_AIR_MASTER);
        break;
    case ROGUE_BOON_VANITAS:
        gGameState.progression.ap += 3;
        RogueGiveRelic(ROGUE_RELIC_GLASS_CANNON);
        break;
    case ROGUE_BOON_JACK:
        // One random relic, or two.
        for (i = 0; i < (strong ? 2 : 1); i++) {
            relic = RogueRollRelic();

            if (relic != ROGUE_RELICS) {
                RogueGiveRelic(relic);
            }
        }
        break;
    }
}

// Buys the next level. Bought during a run it counts for that run too; bought
// in the hub it is applied with the others when the run starts.
u8 RogueBuyUpgrade(u8 upgrade, u8 inRun) {
    u16 cost = RogueUpgradeCost(upgrade);

    if (RogueUpgradeLevel(upgrade) >= sUpgrades[upgrade].levels || gRogueMeta.shards < cost || !RogueUpgradeOpen(upgrade)) {
        return 0;
    }

    gRogueMeta.shards -= cost;
    (*RogueUpgradeSlot(upgrade))++;

    if (inRun) {
        RogueApplyUpgrade(upgrade);
    }

    RogueMetaSave();
    return 1;
}

// Banks what the run earned. A completed run unlocks the next chapter, with a
// bonus the first time.
void RogueMetaEndRun(u8 completed) {
    gRogueMeta.runs++;

    if (gRogue.depth > gRogueMeta.bestDepth) {
        gRogueMeta.bestDepth = gRogue.depth;
    }

    // Losses in a row are counted, to go easier on the next run.
    if (!completed && gRogueMeta.losses < ROGUE_PITY_MAX) {
        gRogueMeta.losses++;
    }

    if (completed) {
        gRogueMeta.losses = 0;
        gRogueMeta.wins++;
        gRogueMeta.boonsWon |= 1 << gRogue.boon;

        // Completing every chapter at the highest oblivion level opens the next.
        if (gRogue.chapters == ROGUE_CHAPTERS && gRogue.oblivion == gRogueMeta.oblivionMax &&
            gRogueMeta.oblivionMax < ROGUE_OBLIVION_MAX && (gRogueMeta.flags & ROGUE_META_ALL_CLEARED)) {
            gRogueMeta.oblivionMax++;
        }

        if (gRogue.chapters == ROGUE_CHAPTERS) {
            gRogueMeta.flags |= ROGUE_META_ALL_CLEARED;
        }

        if (gRogueMeta.chapters < ROGUE_CHAPTERS && gRogue.chapters == gRogueMeta.chapters) {
            gRogueMeta.chapters++;
            gRogue.shards += ROGUE_SHARDS_NEW_CHAPTER;
            gRogue.newChapter = 1;
        }
    }

    // Each oblivion level is worth a quarter more shards.
    gRogue.shards += gRogue.shards * gRogue.oblivion / 4;

    // Greed: a fifth more of the run's shards are kept for each level.
    gRogue.shards += gRogue.shards * RogueUpgradeLevel(ROGUE_UPGRADE_GREED) / 5;

    if (gRogueMeta.shards + gRogue.shards > 9999) {
        gRogueMeta.shards = 9999;
    } else {
        gRogueMeta.shards += gRogue.shards;
    }

    RogueMetaSave();
}

void RogueSuspendSave(void) {
    sSuspend.magic = SUSPEND_MAGIC;
    sSuspend.unused = 0;
    sSuspend.run = gRogue;
    sSuspend.checksum = SaveChecksum((u16*)&sSuspend.run, sizeof(sSuspend.run));
    WriteSramFast((u8*)&sSuspend, SUSPEND_SRAM, sizeof(sSuspend));
}

// Takes the saved run back, if there is one. It can be resumed only once.
u8 RogueSuspendLoad(void) {
    ReadSramFast(SUSPEND_SRAM, (u8*)&sSuspend, sizeof(sSuspend));

    if (sSuspend.magic != SUSPEND_MAGIC ||
        sSuspend.checksum != SaveChecksum((u16*)&sSuspend.run, sizeof(sSuspend.run))) {
        return 0;
    }

    gRogue = sSuspend.run;
    sSuspend.magic = 0;
    WriteSramFast((u8*)&sSuspend, SUSPEND_SRAM, 8);
    return 1;
}

// Picks up a run left with the pause menu's quick save. Returns 0 if there
// is none.
u8 RogueResumeRun(void) {
    if (SaveRepairSystem() != 2 || !RogueSuspendLoad()) {
        return 0;
    }

    SaveLoadSystem();
    SaveClearSystem();
    func_080E04EC();
    return 1;
}


// Gives the run up from the pause menu: it ends as a lost one, shards kept.
void RogueAbandonRun(void) {
    RogueMetaEndRun(0);
    ModeRequest(&gModeRogueOver, 0);
}
