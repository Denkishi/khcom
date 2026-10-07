#include "rogue.h"
#include "registration_data.h"
#include "battle_actor.h"
#include "map.h"
#include "mode_battle_data.h"
#include "system_state.h"
#include "world_types.h"

// Test hooks. Nothing in the game sets gRogueDebug: the emulator test scripts
// poke a command into it, so that a test can jump straight to what it checks.
RogueDebug gRogueDebug;

// Runs a pending command while Sora walks around a room.
void RogueDebugField(void) {
    u8 command = gRogueDebug.command;
    u8 arg = gRogueDebug.arg;

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
    case ROGUE_DEBUG_RELIC:
        gRogue.relics |= 1 << arg;
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
