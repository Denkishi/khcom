#include "rogue.h"
#include "registration_data.h"
#include "battle_actor.h"
#include "map.h"
#include "map_runtime.h"
#include "engine_math.h"
#include "system_state.h"
#include "task.h"
#include "world_types.h"

RogueRun gRogue;
Mode* gRogueLeaveMode;
s32 gRogueLeaveArg;
u8 gRogueLinks[4];

// Map room type of each room kind, a row of gUnk_0984D134.
static const u8 sRoomTypes[ROGUE_ROOM_KINDS] = {
    6, // start: Moment's Reprieve
    2, // battle: Tranquil Darkness
    1, // elite: Teeming Darkness
    3, // treasure: Guarded Trove
    11, // shop: Moogle Room
    6, // rest: Moment's Reprieve
    1, // boss
    6, // event: Moment's Reprieve
};

// Battles to win before the room's doors open, by room kind.
static const u8 sRoomBattles[ROGUE_ROOM_KINDS] = { 0, 1, 2, 1, 0, 0, 0, 0 };

// Map card whose art the room's door shows, by room kind.
static const u8 sRoomCards[ROGUE_ROOM_KINDS] = { 5, 1, 0, 2, 10, 5, 0, 14 };

// The floors of a run in order: each has a world and the battle that ends it.
// The last floor of a chapter is its boss, the others are minibosses. Once a
// floor's chapter has been completed, its second boss shows up half the time.
typedef struct RogueFloor {
    u8 world;
    u8 boss;
    u8 otherBoss;
} RogueFloor;

static const RogueFloor sFloors[ROGUE_FLOORS] = {
    { WORLD_TRAVERSE_TOWN, 0x94, 0x9D }, // Guard Armor, Leon
    { WORLD_AGRABAH, 0x95, 0xA1 }, // Jafar, Riku
    { WORLD_WONDERLAND, 0x96, 0xA3 }, // Trickmaster, Larxene
    { WORLD_OLYMPUS_COLISEUM, 0xA0, 0x9F }, // Hades, Cloud
    { WORLD_MONSTRO, 0x98, 0xA8 }, // Parasite Cage, Riku
    { WORLD_HALLOWEEN_TOWN, 0x9B, 0xA4 }, // Oogie Boogie, Vexen
    { WORLD_ATLANTICA, 0x97, 0xA9 }, // Ursula, Riku
    { WORLD_NEVER_LAND, 0x9E, 0xA7 }, // Hook, Lexaeus
    { WORLD_HOLLOW_BASTION, 0x99, 0xAA }, // Dragon Maleficent, Riku
    { WORLD_DESTINY_ISLANDS, 0x9A, 0xAF }, // Darkside, Vexen
    { WORLD_CASTLE_OBLIVION, 0xA5, 0xA2 }, // Marluxia, Axel
};

// Floors in a run of 1 to ROGUE_CHAPTERS chapters.
static const u8 sChapterFloors[ROGUE_CHAPTERS + 1] = { 0, 2, 5, 8, 11 };

u8 RogueFloorCount(void) {
    return sChapterFloors[gRogue.chapters];
}

static u8 RogueRollBoss(void) {
    const RogueFloor* floor = &sFloors[gRogue.floor];
    u8 chapter = 0;

    while (gRogue.floor >= sChapterFloors[chapter + 1]) {
        chapter++;
    }

    if ((gRogueMeta.chapters > chapter + 1 || (gRogueMeta.flags & ROGUE_META_ALL_CLEARED)) && RogueRandBelow(2) == 0) {
        return floor->otherBoss;
    }

    return floor->boss;
}

u8 RogueFloorIsChapterEnd(void) {
    u8 chapter;

    for (chapter = 1; chapter <= ROGUE_CHAPTERS; chapter++) {
        if (gRogue.floor + 1 == sChapterFloors[chapter]) {
            return 1;
        }
    }

    return 0;
}

// The run has its own generator so that battles, which reseed the game's, do
// not change what the run rolls next.
u32 RogueRand(void) {
    u32 x = gRogue.rng;

    if (x == 0) {
        x = 0x2545F491;
    }

    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    gRogue.rng = x;
    return x;
}

u32 RogueRandBelow(u32 n) {
    return (RogueRand() >> 8) % n;
}

u8* RogueRoomLinks(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (gRogue.doors[i] != ROGUE_NO_DOOR) {
            gRogueLinks[i] = ROGUE_ROOM_ID + 1 + i;
        } else {
            gRogueLinks[i] = 0xFF;
        }
    }

    return gRogueLinks;
}

u16 RogueDoorFlags(u8 door) {
    if (gRogue.doors[door] != ROGUE_NO_DOOR) {
        return 1;
    }

    return 0;
}

static u8 RogueRollKind(void) {
    u32 roll = RogueRandBelow(100);

    if (roll < 48) {
        return ROGUE_ROOM_BATTLE;
    }

    if (roll < 62) {
        return ROGUE_ROOM_ELITE;
    }

    if (roll < 72) {
        return ROGUE_ROOM_TREASURE;
    }

    if (roll < 80) {
        return ROGUE_ROOM_REST;
    }

    if (roll < 94) {
        return ROGUE_ROOM_EVENT;
    }

    return ROGUE_ROOM_SHOP;
}

// Rolls the doors out of the current room: the boss door alone at the end of
// the floor, otherwise two or three doors to different kinds of room.
static void RogueRollDoors(void) {
    s32 i;
    s32 count;
    s32 door;
    u8 kind;

    for (i = 0; i < 4; i++) {
        gRogue.doors[i] = ROGUE_NO_DOOR;
    }

    if (gRogue.kind == ROGUE_ROOM_START) {
        gRogue.doors[RogueRandBelow(4)] = ROGUE_ROOM_BATTLE;
        return;
    }

    if (gRogue.room == ROGUE_FLOOR_ROOMS - 1) {
        gRogue.doors[RogueRandBelow(4)] = ROGUE_ROOM_BOSS;
        return;
    }

    count = 2 + RogueRandBelow(2);

    while (count > 0) {
        door = RogueRandBelow(4);

        if (gRogue.doors[door] != ROGUE_NO_DOOR) {
            continue;
        }

        kind = RogueRollKind();

        for (i = 0; i < 4; i++) {
            if (gRogue.doors[i] == kind) {
                break;
            }
        }

        if (i == 4 || kind == ROGUE_ROOM_BATTLE) {
            gRogue.doors[door] = kind;
            count--;
        }
    }
}

static void RogueEnterRoom(u8 firstOfFloor) {
    UnkStruct_080DEE18* room;
    const u8* row;
    s32 i;

    gGameState.floor = 1;
    gGameState.floors[1].world = gRogue.world;
    gGameState.unk_00F = 0xFF;
    gUnk_0203C590.unk_02 = firstOfFloor ? 0x100 : 0x110;
    gUnk_0203C590.unk_04 = gRogue.world;
    gUnk_0203C590.unk_05 = 0;
    gUnk_0203C590.unk_06 = ROGUE_ROOM_ID;
    gUnk_0203C590.unk_07 = 5;

    for (i = 0; i < 32; i++) {
        room = func_080DEE18(i);
        room->unk_00 = 0;
        room->unk_04 = 0;
        room->unk_08 = 0;
        room->unk_09 = 0;
        room->unk_0A = 0;
    }

    if (gRogue.kind == ROGUE_ROOM_EVENT) {
        gRogue.event = RogueRandBelow(ROGUE_EVENTS);
        gRogue.eventDone = 0;

        if (gRogueDebug.event != 0) {
            gRogue.event = gRogueDebug.event - 1;
        }
    }

    if (gRogue.kind == ROGUE_ROOM_REST) {
        gGameState.hp += (gGameState.progression.maxHp * ROGUE_REST_HEAL) >> 8;

        if (gGameState.hp > gGameState.progression.maxHp) {
            gGameState.hp = gGameState.progression.maxHp;
        }
    }

    if (gRogue.kind == ROGUE_ROOM_BOSS) {
        func_080DEF20();
        func_0801CB00();
        ModeRequest(&gModeBattle, RogueRollBoss());
        return;
    }

    RogueRollDoors();
    room = func_080DEE18(ROGUE_ROOM_ID);
    row = gUnk_0984D134[sRoomTypes[gRogue.kind]];
    room->unk_00 = 1;
    room->unk_04 = RogueRand();
    room->unk_08 = sRoomCards[gRogue.kind];
    room->unk_09 = sRoomTypes[gRogue.kind];
    room->unk_0A = 1;
    room->unk_0B = sRoomBattles[gRogue.kind];
    room->unk_0C = row[6];
    func_0801CB00();
    ModeRequest(&gModeMapFld, 0);
}

void RogueStartRun(void) {
    s32 i;

    gRogue.seed = gFrameCounter * 0x9E3779B1 + GetRandom();
    gRogue.rng = gRogue.seed | 1;
    gRogue.depth = 0;
    gRogue.floor = 0;
    gRogue.room = 0;
    gRogue.kind = ROGUE_ROOM_START;
    gRogue.comboPlus = 0;
    gRogue.relics = 0;
    gRogue.airJumps = 0;
    gRogue.airJumpsUsed = 0;
    gRogue.world = sFloors[0].world;
    gRogue.rerolls = 0;
    gRogue.duel = 0;

    for (i = 0; i < ROGUE_ART_KINDS; i++) {
        gRogue.arts[i] = 0;
    }

    gRogue.shards = 0;
    gRogue.newChapter = 0;
    gRogue.chapters = gRogueMeta.chapters;
    gRogue.deckBias = 0;
    RogueApplyUpgrades();
    RogueApplyBoon();
    gRogue.deckWanted = 1;
    func_0801CD20();
    gGameState.progression.unk_82 = 0xFFFF;
    RogueEnterRoom(1);
}

void RogueLeaveRoom(u8 door) {
    gRogue.kind = gRogue.doors[door];
    gRogue.depth++;
    gRogue.room++;
    RogueEnterRoom(0);
}

// After a boss: the next floor, or the end of the run if that was the last.
void RogueNextFloor(void) {
    if (gRogue.floor + 1 >= RogueFloorCount()) {
        RogueMetaEndRun(1);
        ModeRequest(&gModeRogueOver, 1);
        return;
    }

    gRogue.floor++;
    gRogue.depth++;
    gRogue.room = 0;
    gRogue.kind = ROGUE_ROOM_BATTLE;
    gRogue.world = sFloors[gRogue.floor].world;
    RogueEnterRoom(1);
}

// A won battle leads to the reward screen, which then goes back to the room
// or, after a boss, on to the next floor. Returns 0 to go straight back to
// the room.
u8 RogueOnBattleEnd(u16 battle) {
    // Running away wins nothing: back to the room, which still has its battle.
    if (gGameState.flags & 0x40) {
        gRogue.duel = 0;
        return 0;
    }

    RogueGainCardXp();

    // Moogle points, to spend in the moogle rooms' shop.
    if (gGameState.progression.mooglePoints < 9999 - ROGUE_MOOGLE_POINTS) {
        gGameState.progression.mooglePoints += ROGUE_MOOGLE_POINTS;
    }

    // A duel picked in an event pays like a boss and leaves the room as it was.
    if (gRogue.duel) {
        gRogue.duel = 0;
        gRogue.shards += ROGUE_SHARDS_DUEL;
        RogueOnBossBeaten(battle);
        ModeRequest(&gModeRogueReward, ROGUE_REWARD_DUEL);
        return 1;
    }

    if (gRogue.kind != ROGUE_ROOM_BOSS) {
        gRogue.shards += ROGUE_SHARDS_ROOM;
    } else if (RogueFloorIsChapterEnd()) {
        RogueOnBossBeaten(battle);
        gRogue.shards += ROGUE_SHARDS_BOSS;
    } else {
        RogueOnBossBeaten(battle);
        gRogue.shards += ROGUE_SHARDS_MINIBOSS;
    }

    if (gRogue.kind == ROGUE_ROOM_BOSS) {
        ModeRequest(&gModeRogueReward, ROGUE_REWARD_BOSS);
    } else if (gRogue.kind == ROGUE_ROOM_TREASURE) {
        // A treasure room pays like a boss.
        ModeRequest(&gModeRogueReward, ROGUE_REWARD_DUEL);
    } else {
        ModeRequest(&gModeRogueReward, ROGUE_REWARD_BATTLE);
    }
    return 1;
}

// A lost battle ends the run.
void RogueOnDefeat(void) {
    RogueMetaEndRun(0);
    ModeRequest(&gModeRogueOver, 0);
}

// Doors stay shut until the room's battles are won.
u8 RogueDoorsOpen(void) {
    return func_080DEE18(ROGUE_ROOM_ID)->unk_0B == 0;
}

u8 RogueTryAirJump(void) {
    if (gRogue.airJumpsUsed >= gRogue.airJumps) {
        return 0;
    }

    gRogue.airJumpsUsed++;
    gRogue.jumpBuffer = 0;
    return 1;
}

void RogueResetAirJumps(void) {
    gRogue.airJumpsUsed = 0;
    gRogue.jumpBuffer = 0;
}

// Hits in the attack combo, the last of which is the finisher.
u8 RogueComboHits(void) {
    return ROGUE_COMBO_BASE + gRogue.comboPlus;
}

// Which of the three attacks of a chain a combo step uses: the two openers
// alternate and the last step is the finisher.
u8 RogueComboSlot(u8 step) {
    if (step >= RogueComboHits() - 1) {
        return 2;
    }

    return step & 1;
}
