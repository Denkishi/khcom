#include "rogue.h"
#include "card_types.h"
#include "registration_data.h"
#include "battle_actor.h"
#include "map.h"
#include "mode_battle_data.h"
#include "system_state.h"
#include "world_types.h"
#include "gba/io_reg.h"

extern vu32 gVBlankCounter;

// Test hooks. Nothing in the game sets gRogueDebug: the emulator test scripts
// poke a command into it, so that a test can jump straight to what it checks.
RogueDebug gRogueDebug;

Deck* GetActiveDeck(void);
u16 CountCardsById(u16 cardId);

// Runs a pending command while Sora walks around a room.
void RogueDebugField(void) {
    u8 command = gRogueDebug.command;
    u8 arg = gRogueDebug.arg;

    gRogueDebug.seenMaxHp = gGameState.progression.maxHp;
    gRogueDebug.seenAp = gGameState.progression.ap;
    gRogueDebug.seenCp = gGameState.progression.cp;
    gRogueDebug.seenDeckCards = GetActiveDeck()->unk_DC;
    gRogueDebug.seenCount = CountCardsById(gRogueDebug.countCard);

    if (command == ROGUE_DEBUG_NONE) {
        return;
    }

    switch (command) {
    case ROGUE_DEBUG_ROOM:
        // Leaves through door 0 into a room of the kind in arg.
        gRogue.doors[0] = arg;
        gUnk_0203C7AC->unk_10 = 0;
        gFieldState->flags |= 0x10;
        break;
    case ROGUE_DEBUG_BATTLE:
        func_0801CB0C();
        ModeRequest(&gModeBattle, arg);
        break;
    case ROGUE_DEBUG_REWARD:
        RogueLeaveRoomFor(&gModeRogueReward, arg);
        break;
    case ROGUE_DEBUG_DOOR: {
        u8 door;

        for (door = 0; door < 3 && gRogue.doors[door] == ROGUE_NO_DOOR; door++) {
        }

        gRogue.mapCards[0] = arg + 1;
        RogueLeaveRoomFor(&gModeRogueDoor, door);
        break;
    }
    case ROGUE_DEBUG_RELIC:
        RogueGiveRelic(arg);
        break;
    case ROGUE_DEBUG_FLOOR:
        gRogue.floor = arg;
        break;
    default:
        // A battle command: leave it for RogueDebugBattle.
        return;
    }

    gRogueDebug.command = ROGUE_DEBUG_NONE;
}

// Called at the end of each frame's work, before the wait for the vertical
// blank: how far down the screen the frame got, and whether it ran over. The
// work starts at line 160, where the blank begins.
void RogueProfileFrame(void) {
    u16 lines = (REG_VCOUNT + 228 - 160) % 228;
    u32 blanks = gVBlankCounter;

    if (gRogueDebug.lastVBlank != 0 && blanks - gRogueDebug.lastVBlank > 1) {
        gRogueDebug.dropped += blanks - gRogueDebug.lastVBlank - 1;
        lines += 228;
    }

    gRogueDebug.lastVBlank = blanks;
    gRogueDebug.loadLast = lines;
    gRogueDebug.loadSum += lines;
    gRogueDebug.loadFrames++;

    if (lines > gRogueDebug.loadMax) {
        gRogueDebug.loadMax = lines;
    }
}
