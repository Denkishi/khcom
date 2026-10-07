#include "rogue.h"
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
#define SUSPEND_SRAM (META_SRAM + 0x40)
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

static const RogueUpgradeDef sUpgrades[ROGUE_UPGRADES] = {
    { 5, 8 }, // max HP
    { 5, 8 }, // CP
    { 3, 15 }, // strength
    { 1, 40 }, // combo plus
    { 1, 30 }, // air jump
    { 3, 12 }, // rerolls
};

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
    ReadSramFast(META_SRAM, (u8*)&gRogueMeta, sizeof(gRogueMeta));

    if (gRogueMeta.magic != META_MAGIC ||
        gRogueMeta.checksum != SaveChecksum((u16*)&gRogueMeta.shards, sizeof(gRogueMeta) - offsetof(RogueMeta, shards))) {
        RogueMetaReset();
    }
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
    return sUpgrades[upgrade].cost * (gRogueMeta.upgrades[upgrade] + 1);
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
    }
}

// Called when a run starts, before its deck is built.
void RogueApplyUpgrades(void) {
    u8 upgrade;
    u8 level;

    for (upgrade = 0; upgrade < ROGUE_UPGRADES; upgrade++) {
        for (level = 0; level < gRogueMeta.upgrades[upgrade]; level++) {
            RogueApplyUpgrade(upgrade);
        }
    }
}

// Buys the next level; it counts for the run in progress too.
u8 RogueBuyUpgrade(u8 upgrade) {
    u16 cost = RogueUpgradeCost(upgrade);

    if (gRogueMeta.upgrades[upgrade] >= sUpgrades[upgrade].levels || gRogueMeta.shards < cost) {
        return 0;
    }

    gRogueMeta.shards -= cost;
    gRogueMeta.upgrades[upgrade]++;
    RogueApplyUpgrade(upgrade);
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

    if (completed) {
        gRogueMeta.wins++;

        if (gRogue.chapters == ROGUE_CHAPTERS) {
            gRogueMeta.flags |= ROGUE_META_ALL_CLEARED;
        }

        if (gRogueMeta.chapters < ROGUE_CHAPTERS && gRogue.chapters == gRogueMeta.chapters) {
            gRogueMeta.chapters++;
            gRogue.shards += ROGUE_SHARDS_NEW_CHAPTER;
            gRogue.newChapter = 1;
        }
    }

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

