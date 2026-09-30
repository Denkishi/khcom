#include "mode_deck.h"
#include "registration_data.h"
#include "map_api.h"
#include "mode.h"
#include "m4a_song.h"
#include "mode_test.h"
#include "gba/keys.h"
#include "mode_test_api.h"
#include "sprites_msg.h"
#include "fade.h"
#include "songs.h"

static TaskPool sModeDeckTasks;
static u8 sModeDeckResult;

void Mode_Deck_0(void) {
    sModeDeckResult = 0;
    TaskPoolInit(&sModeDeckTasks, 1);

    if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
        TaskCreate(&sModeDeckTasks, &gTaskDescDeckmenu2, &sModeDeckResult);
    } else {
        TaskCreate(&sModeDeckTasks, &gTaskDescDeckmenu2Riku, &sModeDeckResult);
    }

    if (gSystemFlags & 1) {
        m4aMPlayAllStop();
    }
}

void Mode_Deck_1(void) {
    if (gSystemFlags & 1) {
        SioBtlOptionRecvSettings();
    } else {
        UpdatePlayTime();
    }

    TaskPoolUpdate(&sModeDeckTasks);
    TaskPoolDraw(&sModeDeckTasks);

    if (sModeDeckResult == 7) {
        if (gDebugFlags & 1) {
            ModeRequest(&gModeChkbtl, 0);
        } else if (gSystemFlags & 1) {
            ModeRequest(&gModeSioBtlOption, 1);
        } else {
            ReturnToMap(0);
        }
    }

    if (sModeDeckResult == 8) {
        if (gDebugFlags & 1) {
            ModeRequest(&gModeChkbtl, 0);
        } else if (gSystemFlags & 1) {
            ModeRequest(&gModeSioBtlOption, 1);
        } else {
            ReturnToMap(1);
        }
    }
}

void Mode_Deck_2(void) {
    TaskPoolDestroy(&sModeDeckTasks);
}
void menu_0(MenuWork* w) {
    gFieldState->flags |= 0x1000;
    gFieldState->flags |= 0x80;
    gFieldState->flags |= 0x2000;
    w->x = 0xF000;
    w->y = 0x4800;
    w->cursor = 0;
    w->state = 0;
    w->tiles = LoadObjTiles(gUnk_090D4DD0, 0x2E80);
    w->palette = LoadObjPalette(gUnk_096148B8, 0x20);
    m4aSongNumStart(SONG_SYS_CANSEL);
}

u8 menu_1(MenuWork* w) {
    switch (w->state) {
    case 0:
        w->x += (0xBC00 - w->x) >> 1;

        if ((w->x >> 8) == 0xBC) {
            w->state = 1;
        }

        if (GetKeysPressed() & B_BUTTON) {
            w->state = 4;
        }

        break;
    case 1:
        if (GetKeysRepeat() & DPAD_UP) {
            if (w->cursor != 0) {
                w->cursor--;
            } else {
                w->cursor = 5;
            }

            m4aSongNumStart(SONG_SYS_CLICK);
        }

        if (GetKeysRepeat() & DPAD_DOWN) {
            if (w->cursor <= 4) {
                w->cursor++;
            } else {
                w->cursor = 0;
            }

            m4aSongNumStart(SONG_SYS_CLICK);
        }

        if (GetKeysPressed() & A_BUTTON) {
            switch (w->cursor) {
            case 0:
                w->state = 2;
                w->cursor = 6;
                m4aSongNumStart(SONG_SYS_CANSEL);
                break;
            case 2:
                RequestFieldResume();
                FadeStartOut(0, 32);
                w->state = 4;
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
            w->state = 5;
            m4aSongNumStart(SONG_SYS_CLOSE);
        }

        break;
    case 2:
        if (GetKeysRepeat() & DPAD_UP) {
            if (w->cursor > 6) {
                w->cursor--;
            } else {
                w->cursor = 9;
            }

            m4aSongNumStart(SONG_SYS_CLICK);
        }

        if (GetKeysRepeat() & DPAD_DOWN) {
            if (w->cursor <= 8) {
                w->cursor++;
            } else {
                w->cursor = 6;
            }

            m4aSongNumStart(SONG_SYS_CLICK);
        }

        if (GetKeysPressed() & B_BUTTON) {
            w->state = 1;
            w->cursor = 0;
            m4aSongNumStart(SONG_SYS_CLOSE);
        }

        if (GetKeysPressed() & A_BUTTON) {
            switch (w->cursor) {
            case 6:
                w->cursor = 0;
                w->state = 1;
                m4aSongNumStart(SONG_SYS_KETTEI);
                break;
            case 7:
                w->cursor = 0;
                w->state = 1;
                m4aSongNumStart(SONG_SYS_KETTEI);
                break;
            case 8:
                w->cursor = 0;
                w->state = 1;
                m4aSongNumStart(SONG_SYS_KETTEI);
                break;
            case 9:
                RequestFieldResume();
                FadeStartOut(0, 32);
                w->state = 4;
                m4aSongNumStart(SONG_SYS_KETTEI);
                break;
            }
        }

        break;
    case 4:
        w->x += (0x11800 - w->x) >> 1;

        if ((w->x >> 8) > 274) {
            if (FadeIsActive() == 0) {
                if (w->cursor != 2) {
                    if (w->cursor == 9) {
                        ModeRequest(&gModeDeck, 0);
                    }
                } else {
                    ModeRequest(&gModeAllmap, 0);
                }

                w->state = 5;
            }
        }

        break;
    case 5:
        w->x += (0x11800 - w->x) >> 1;

        if ((w->x >> 8) > 274) {
            return 0;
        }

        break;
    case 3:
    default:
        break;
    }

    return 1;
}

void menu_2(MenuWork* w) {
    DrawSprite(w->x >> 8, w->y >> 8, gUnk_09EEC600[w->cursor], w->tiles, w->palette, 0, 0, 80);
}

void menu_3(MenuWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    gFieldState->flags &= ~0x1000;
    gFieldState->flags &= ~0x80;
    gFieldState->flags &= ~0x2000;
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
