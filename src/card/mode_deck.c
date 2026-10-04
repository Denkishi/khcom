/**
 * mode_deck.c
 * Deck Menu Screen
 */

#include "mode_deck.h"
#include "registration_data.h"
#include "map_api.h"
#include "mode.h"
#include "m4a_song.h"
#include "mode_test.h"
#include "gba/keys.h"
#include "sprites_msg.h"
#include "fade.h"
#include "songs.h"
#include "field_state.h"
#include "game_state.h"
#include "key.h"
#include "obj_api.h"
#include <stddef.h>
#include "system_state.h"
#include "taskpool.h"
#include "types.h"
#include "mode_sio.h"

static TaskPool sModeDeckTasks;
static u8 sModeDeckResult;

void Mode_Deck_0() {
    sModeDeckResult = 0;
    TaskPoolInit(&sModeDeckTasks, 1);

    if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
        TaskCreate(&sModeDeckTasks, &gTaskDescDeckmenu2, &sModeDeckResult);
    } else {
        TaskCreate(&sModeDeckTasks, &gTaskDescDeckmenu2Riku, &sModeDeckResult);
    }

    if (gSystemFlags & SYSTEM_FLAG_LINK_ACTIVE) {
        m4aMPlayAllStop();
    }
}

void Mode_Deck_1() {
    if (gSystemFlags & SYSTEM_FLAG_LINK_ACTIVE) {
        SioBtlOptionRecvSettings();
    } else {
        UpdatePlayTime();
    }

    TaskPoolUpdate(&sModeDeckTasks);
    TaskPoolDraw(&sModeDeckTasks);

    if (sModeDeckResult == 7) {
        if (gDebugFlags & DEBUG_FLAG_CHKBTL) {
            ModeRequest(&gModeChkbtl, 0);
        } else if (gSystemFlags & SYSTEM_FLAG_LINK_ACTIVE) {
            ModeRequest(&gModeSioBtlOption, 1);
        } else {
            ReturnToMap(0);
        }
    }

    if (sModeDeckResult == 8) {
        if (gDebugFlags & DEBUG_FLAG_CHKBTL) {
            ModeRequest(&gModeChkbtl, 0);
        } else if (gSystemFlags & SYSTEM_FLAG_LINK_ACTIVE) {
            ModeRequest(&gModeSioBtlOption, 1);
        } else {
            ReturnToMap(1);
        }
    }
}

void Mode_Deck_2() {
    TaskPoolDestroy(&sModeDeckTasks);
}

void menu_0(MenuWork* work) {
    gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
    gFieldState->flags |= FIELD_FLAG_FREEZE_ENEMIES;
    gFieldState->flags |= FIELD_FLAG_MENU_OPEN;
    work->x = 0xF000;
    work->y = 0x4800;
    work->cursor = 0;
    work->state = 0;
    work->tiles = LoadObjTiles(gUnk_090D4DD0, 0x2E80);
    work->palette = LoadObjPalette(gUnk_096148B8, 0x20);
    m4aSongNumStart(SONG_SYS_CANSEL);
}

u8 menu_1(MenuWork* work) {
    switch (work->state) {
    case 0:
        work->x += (0xBC00 - work->x) >> 1;

        if ((work->x >> 8) == 0xBC) {
            work->state = 1;
        }

        if (GetKeysPressed() & B_BUTTON) {
            work->state = 4;
        }

        break;
    case 1:
        if (GetKeysRepeat() & DPAD_UP) {
            if (work->cursor != 0) {
                work->cursor--;
            } else {
                work->cursor = 5;
            }

            m4aSongNumStart(SONG_SYS_CLICK);
        }

        if (GetKeysRepeat() & DPAD_DOWN) {
            if (work->cursor <= 4) {
                work->cursor++;
            } else {
                work->cursor = 0;
            }

            m4aSongNumStart(SONG_SYS_CLICK);
        }

        if (GetKeysPressed() & A_BUTTON) {
            switch (work->cursor) {
            case 0:
                work->state = 2;
                work->cursor = 6;
                m4aSongNumStart(SONG_SYS_CANSEL);
                break;
            case 2:
                RequestFieldResume();
                FadeStartOut(FADE_MODE_BLACK, 32);
                work->state = 4;
                m4aSongNumStart(SONG_SYS_KETTEI);
                break;
            case 1:
            case 3:
            case 4:
                m4aSongNumStart(SONG_SYS_BEEP);
                break;
            case 5:
                m4aSongNumStart(SONG_SYS_BEEP);
                break;
            }
        }

        if (GetKeysPressed() & B_BUTTON) {
            work->state = 5;
            m4aSongNumStart(SONG_SYS_CLOSE);
        }

        break;
    case 2:
        if (GetKeysRepeat() & DPAD_UP) {
            if (work->cursor > 6) {
                work->cursor--;
            } else {
                work->cursor = 9;
            }

            m4aSongNumStart(SONG_SYS_CLICK);
        }

        if (GetKeysRepeat() & DPAD_DOWN) {
            if (work->cursor <= 8) {
                work->cursor++;
            } else {
                work->cursor = 6;
            }

            m4aSongNumStart(SONG_SYS_CLICK);
        }

        if (GetKeysPressed() & B_BUTTON) {
            work->state = 1;
            work->cursor = 0;
            m4aSongNumStart(SONG_SYS_CLOSE);
        }

        if (GetKeysPressed() & A_BUTTON) {
            switch (work->cursor) {
            case 6:
                work->cursor = 0;
                work->state = 1;
                m4aSongNumStart(SONG_SYS_KETTEI);
                break;
            case 7:
                work->cursor = 0;
                work->state = 1;
                m4aSongNumStart(SONG_SYS_KETTEI);
                break;
            case 8:
                work->cursor = 0;
                work->state = 1;
                m4aSongNumStart(SONG_SYS_KETTEI);
                break;
            case 9:
                RequestFieldResume();
                FadeStartOut(FADE_MODE_BLACK, 32);
                work->state = 4;
                m4aSongNumStart(SONG_SYS_KETTEI);
                break;
            }
        }

        break;
    case 4:
        work->x += (0x11800 - work->x) >> 1;

        if ((work->x >> 8) > 274) {
            if (!FadeIsActive()) {
                if (work->cursor != 2) {
                    if (work->cursor == 9) {
                        ModeRequest(&gModeDeck, 0);
                    }
                } else {
                    ModeRequest(&gModeAllmap, 0);
                }

                work->state = 5;
            }
        }

        break;
    case 5:
        work->x += (0x11800 - work->x) >> 1;

        if ((work->x >> 8) > 274) {
            return 0;
        }

        break;
    case 3:
    default:
        break;
    }

    return 1;
}

void menu_2(MenuWork* work) {
    DrawSprite(work->x >> 8, work->y >> 8, gUnk_09EEC600[work->cursor], work->tiles, work->palette, NULL, 0, 80);
}

void menu_3(MenuWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_ENEMIES;
    gFieldState->flags &= ~FIELD_FLAG_MENU_OPEN;
}

Mode gModeDeck = { "Mode_Deck", (ModeInitFunc)Mode_Deck_0, Mode_Deck_1, Mode_Deck_2 };

TaskDesc gTaskDescMenu = {
    "menu",
    (TaskInitFunc)menu_0,
    (TaskUpdateFunc)menu_1,
    (TaskDrawFunc)menu_2,
    (TaskDestroyFunc)menu_3,
    sizeof(MenuWork),
};
