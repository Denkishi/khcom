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
};

// Battles to win before the room's doors open, by room kind.
static const u8 sRoomBattles[ROGUE_ROOM_KINDS] = { 0, 1, 2, 1, 0, 0, 0 };

// Map card whose art the room's door shows, by room kind.
static const u8 sRoomCards[ROGUE_ROOM_KINDS] = { 5, 1, 0, 2, 10, 5, 0 };

static const u8 sWorlds[] = {
    WORLD_TRAVERSE_TOWN,
    WORLD_AGRABAH,
    WORLD_OLYMPUS_COLISEUM,
    WORLD_WONDERLAND,
    WORLD_MONSTRO,
    WORLD_HALLOWEEN_TOWN,
    WORLD_ATLANTICA,
    WORLD_NEVER_LAND,
    WORLD_HOLLOW_BASTION,
    WORLD_TWILIGHT_TOWN,
    WORLD_DESTINY_ISLANDS,
    WORLD_CASTLE_OBLIVION,
};

// Boss battle of each world, indexed by WorldId. Worlds without a giant boss
// of their own get an Organization member.
static const u8 sWorldBosses[] = {
    0x94, // unused
    0x95, // Agrabah
    0x97, // Atlantica
    0xA0, // Olympus Coliseum
    0x96, // Wonderland
    0x98, // Monstro
    0x9B, // Halloween Town
    0x9E, // Never Land
    0xA2, // Hollow Bastion
    0xA2, // Destiny Islands
    0x94, // Traverse Town
    0xA2, // Twilight Town
    0xA2, // Castle Oblivion
};

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

    if (roll < 55) {
        return ROGUE_ROOM_BATTLE;
    }

    if (roll < 70) {
        return ROGUE_ROOM_ELITE;
    }

    if (roll < 82) {
        return ROGUE_ROOM_TREASURE;
    }

    if (roll < 91) {
        return ROGUE_ROOM_REST;
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

    if (gRogue.kind == ROGUE_ROOM_BOSS) {
        func_080DEF20();
        func_0801CB00();
        ModeRequest(&gModeBattle, sWorldBosses[gRogue.world]);
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
    gRogue.seed = gFrameCounter * 0x9E3779B1 + GetRandom();
    gRogue.rng = gRogue.seed | 1;
    gRogue.depth = 0;
    gRogue.floor = 0;
    gRogue.room = 0;
    gRogue.kind = ROGUE_ROOM_START;
    gRogue.comboPlus = 0;
    gRogue.airJumps = 0;
    gRogue.airJumpsUsed = 0;
    gRogue.world = RogueRollWorld();
    func_0801CD20();
    gGameState.progression.unk_82 = 0xFFFF;
    RogueLearnSleights();
    RogueEnterRoom(1);
}

void RogueLeaveRoom(u8 door) {
    gRogue.kind = gRogue.doors[door];
    gRogue.depth++;
    gRogue.room++;
    RogueEnterRoom(0);
}

// Rolls the next floor's world: later floors reach later worlds.
static u8 RogueRollWorld(void) {
    u32 index = gRogue.floor + RogueRandBelow(3);

    if (index >= sizeof(sWorlds) / sizeof(sWorlds[0])) {
        index = sizeof(sWorlds) / sizeof(sWorlds[0]) - 1 - RogueRandBelow(4);
    }

    return sWorlds[index];
}

void RogueNextFloor(void) {
    gRogue.floor++;
    gRogue.depth++;
    gRogue.room = 0;
    gRogue.kind = ROGUE_ROOM_BATTLE;
    gRogue.world = RogueRollWorld();
    RogueEnterRoom(1);
}

// A won battle leads to the reward screen, which then goes back to the room
// or, after a boss, on to the next floor.
u8 RogueOnBattleEnd(void) {
    RogueGainCardXp();
    ModeRequest(&gModeRogueReward, gRogue.kind == ROGUE_ROOM_BOSS);
    return 1;
}

// A lost battle ends the run.
void RogueOnDefeat(void) {
    ModeRequest(&gModeTitle, 0);
}

// Doors stay shut until the room's battles are won.
u8 RogueDoorsOpen(void) {
    return func_080DEE18(ROGUE_ROOM_ID)->unk_0B == 0;
}

// How far the run has gone, for enemy stats: three levels a floor plus up to
// three more across its rooms.
u8 RogueEnemyLevel(void) {
    return gRogue.floor * 3 + gRogue.room / 2;
}

u8 RogueTryAirJump(void) {
    if (gRogue.airJumpsUsed >= gRogue.airJumps) {
        return 0;
    }

    gRogue.airJumpsUsed++;
    return 1;
}

void RogueResetAirJumps(void) {
    gRogue.airJumpsUsed = 0;
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
