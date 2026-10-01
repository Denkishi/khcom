#include "system_state.h"
#include "game_state.h"
#include "card_api.h"
#include "map_runtime.h"
#include "player_progression.h"
#include "player_progression_types.h"
#include "types.h"

u8 GetAngle(s32 x0, s32 y0, s32 x1, s32 y1) {
    s32 dx;
    s32 dy;
    u8 angle;

    dx = x1 - x0;
    dy = y1 - y0;
    angle = 0;

    if (dx == 0 && dy == 0) {
        angle = 0;
    } else if (dx > 0 && dy < 0) {
        dy = -dy;

        if (dx <= dy) {
            angle = ((0x200000 / dy) * dx) >> 16;
        } else {
            angle = 0x40 - (((0x200000 / dx) * dy) >> 16);
        }
    } else if (dx > 0 && dy > 0) {
        if (dx <= dy) {
            angle = 0x7F - (((0x200000 / dy) * dx) >> 16);
        } else {
            angle = (((0x200000 / dx) * dy) >> 16) + 0x3F;
        }
    } else if (dx < 0 && dy > 0) {
        dx = -dx;

        if (dx <= dy) {
            angle = (((0x200000 / dy) * dx) >> 16) - 0x80;
        } else {
            angle = -0x40 - (((0x200000 / dx) * dy) >> 16);
        }
    } else if (dx < 0 && dy < 0) {
        dx = -dx;
        dy = -dy;

        if (dx <= dy) {
            angle = -1 - (((0x200000 / dy) * dx) >> 16);
        } else {
            angle = (((0x200000 / dx) * dy) >> 16) - 0x41;
        }
    } else if (dx == 0 && dy < 0) {
        angle = 0;
    } else if (dx == 0 && dy > 0) {
        angle = 0x80;
    } else if (dx < 0 && dy == 0) {
        angle = 0xC0;
    } else if (dx > 0 && dy == 0) {
        angle = 0x40;
    }

    return angle;
}

void UpdatePlayTime() {
    if (gFrameCounter % 60 == 0) {
        if (gGameState.playTime <= 0x57E3E) {
            gGameState.playTime++;
        }
    }
}

void SetupRikuNewGame() {
    InitStartFloor(0, 0);
    gGameState.progression.unk_82 = 0xE7FF;
    gGameState.progression.friendFlags = FRIEND_FLAG_THE_KING;
    InitRikuDeckForWorld(0);
    gGameState.flags |= GAME_FLAG_RIKU;
    gGameState.flags |= GAME_FLAG_DARK_POINTS_LOCKED;
    SetJiminyFlag(0);
    SetJiminyFlag(0x15);
    SetJiminyFlag(0xED);
    SetJiminyFlag(0x11);
    SetJiminyFlag(0x16);
    SetJiminyFlag(0xEF);
    SetJiminyFlag(0xF3);
}

void SetupSoraNewGame() {
    gGameState.progression.friendFlags = (FRIEND_FLAG_GOOFY | FRIEND_FLAG_DONALD_DUCK);
    InitSoraDecks();
    gGameState.flags &= ~GAME_FLAG_RIKU;
    SetJiminyFlag(0x11);
    SetJiminyFlag(0x12);
    SetJiminyFlag(0x13);
    SetJiminyFlag(0x14);
    SetJiminyFlag(0x15);
    SetJiminyFlag(0x16);
    InitStartFloor(0, 10);
}
