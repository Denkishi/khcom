/**
 * status.c
 * Status Screen Tasks
 */

#include "macros.h"
#include "registration_data.h"
#include "system_state.h"
#include "status_api.h"
#include "anim.h"
#include "status.h"
#include "gba/keys.h"
#include "sprites_fld.h"
#include "sprites_status.h"
#include "card_ids.h"
#include "player_progression.h"
#include "fade.h"
#include "songs.h"
#include "mode_status_api.h"
#include "card_api.h"
#include "card_def_data.h"
#include "card_label_data.h"
#include "card_types.h"
#include "card_ui_types.h"
#include "display.h"
#include "engine_math.h"
#include "game_state.h"
#include "key.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "player_progression_types.h"
#include "poo_api.h"
#include "taskpool.h"
#include "text.h"
#include "types.h"
#include <stddef.h>
#include "card_deckmenu2.h"
#include "card_stock_info.h"
#include "sprite_palettes.h"

TaskDesc gTaskDescStatus = {
    "task_status",
    (TaskInitFunc)task_status_0,
    (TaskUpdateFunc)task_status_1,
    (TaskDrawFunc)task_status_2,
    (TaskDestroyFunc)task_status_3,
    sizeof(StatusWork),
};

#ifdef VERSION_EU
static const u16 sStatusBarTileSizes[5] = {736, 608, 736, 640, 704};
#endif

#ifdef VERSION_EU
static void* sStatusBarTiles[5] = {
    gUnk_097A18EC,
    gUnkEu_0977DE68,
    gUnk_097A18EC,
    gUnkEu_0977E494,
    gUnkEu_0977E14A,
};

static void** sStatusBarSprites[5] = {
    gUnk_09EF68E0,
    gUnkEu_09F81ED8,
    gUnk_09EF68E0,
    gUnkEu_09F81EF8,
    gUnkEu_09F81EE8,
};
#endif

TaskDesc gTaskDescStatusBar = {
    "task_status_bar",
    (TaskInitFunc)task_status_bar_0,
    (TaskUpdateFunc)task_status_bar_1,
    (TaskDrawFunc)task_status_bar_2,
    (TaskDestroyFunc)task_status_bar_3,
    sizeof(StatusBarWork),
};

#ifdef VERSION_EU
static void* sStatusTabTiles[5] = {
    gUnk_097A24A6,
    gUnkEu_0977EFAE,
    gUnkEu_0977EB7A,
    gUnkEu_0977F3E2,
    gUnkEu_0977EB7A,
};

static void** sStatusTabSprites[5] = {
    gUnk_09EF6920,
    gUnkEu_09F81F30,
    gUnkEu_09F81F1C,
    gUnkEu_09F81F44,
    gUnkEu_09F81F1C,
};
#endif

static TaskDesc sTaskDescStatusTab = {
    "task_status_tab",
    (TaskInitFunc)task_status_tab_0,
    (TaskUpdateFunc)task_status_tab_1,
    (TaskDrawFunc)task_status_tab_2,
    (TaskDestroyFunc)task_status_tab_3,
    sizeof(StatusTabWork),
};

static TaskDesc sTaskDescStatusSora = {
    "task_status_sora",
    (TaskInitFunc)task_status_sora_0,
    (TaskUpdateFunc)task_status_sora_1,
    (TaskDrawFunc)task_status_sora_2,
    (TaskDestroyFunc)task_status_sora_3,
    sizeof(StatusSoraWork),
};

static TaskDesc sTaskDescStatusDeckname = {
    "task_status_deckname",
    (TaskInitFunc)task_status_deckname_0,
    (TaskUpdateFunc)task_status_deckname_1,
    (TaskDrawFunc)task_status_deckname_2,
    (TaskDestroyFunc)task_status_deckname_3,
    sizeof(StatusDecknameWork),
};

static const s32 sStatusTabCursorX[4] = {-1536, 2816, 6912, 10240};

static TaskDesc sTaskDescStatusCursor = {
    "task_status_cursor",
    (TaskInitFunc)task_status_cursor_0,
    (TaskUpdateFunc)task_status_cursor_1,
    (TaskDrawFunc)task_status_cursor_2,
    (TaskDestroyFunc)task_status_cursor_3,
    sizeof(StatusCursorWork),
};

#ifdef VERSION_EU
static const u16 sStatusNewMarkTileSizes[5] = {64, 128, 64, 128, 128};
#endif

#ifdef VERSION_EU
static void* sStatusNewMarkTiles[5] = {
    gUnkEu_0977F7F8,
    gUnkEu_0977F84C,
    gUnkEu_0977FA08,
    gUnkEu_0977F974,
    gUnkEu_0977F8E0,
};

static void* sStatusNewMarkSprites[5] = {
    gUnkEu_0977F7E4,
    gUnkEu_0977F838,
    gUnkEu_0977F9F4,
    gUnkEu_0977F960,
    gUnkEu_0977F8CC,
};
#endif

static TaskDesc sTaskDescStatusStocklist = {
    "task_status_stocklist",
    (TaskInitFunc)task_status_stocklist_0,
    (TaskUpdateFunc)task_status_stocklist_1,
    (TaskDrawFunc)task_status_stocklist_2,
    (TaskDestroyFunc)task_status_stocklist_3,
    sizeof(StatusStocklistWork),
};

static TaskDesc sTaskDescStatusScrollcursor = {
    "task_status_scrollcursor",
    (TaskInitFunc)task_status_scrollcursor_0,
    (TaskUpdateFunc)task_status_scrollcursor_1,
    (TaskDrawFunc)task_status_scrollcursor_2,
    (TaskDestroyFunc)task_status_scrollcursor_3,
    sizeof(StatusScrollcursorWork),
};

static TaskDesc sTaskDescStatusMeswindow = {
    "task_status_meswindow",
    (TaskInitFunc)task_status_meswindow_0,
    (TaskUpdateFunc)task_status_meswindow_1,
    (TaskDrawFunc)task_status_meswindow_2,
    (TaskDestroyFunc)task_status_meswindow_3,
    sizeof(StatusMeswindowWork),
};

static TaskDesc sTaskDescStatusMessage = {
    "task_status_message",
    (TaskInitFunc)task_status_message_0,
    (TaskUpdateFunc)task_status_message_1,
    (TaskDrawFunc)task_status_message_2,
    (TaskDestroyFunc)task_status_message_3,
    sizeof(StatusMessageWork),
};

static TaskDesc sTaskDescStatusFriend = {
    "task_status_friend",
    (TaskInitFunc)task_status_friend_0,
    (TaskUpdateFunc)task_status_friend_1,
    (TaskDrawFunc)task_status_friend_2,
    (TaskDestroyFunc)task_status_friend_3,
    sizeof(StatusFriendWork),
};

static const StatusFriendTable sStatusFriendTable = {{
    {2, CARD_ID(CARD_DONALD_DUCK, 0)},
    {1, CARD_ID(CARD_GOOFY, 0)},
    {4, CARD_ID(CARD_ALADDIN, 0)},
    {8, CARD_ID(CARD_ARIEL, 0)},
    {16, CARD_ID(CARD_JACK, 0)},
    {32, CARD_ID(CARD_PETER_PAN, 0)},
    {64, CARD_ID(CARD_THE_BEAST, 0)},
    {128, CARD_ID(CARD_THE_KING, 0)},
}};

static StatusWork* sStatusWork;
static u8 sStatusMesWindowOpen;
static s16 sStatusSelectedIndex;
static StatusStocklistWork* sStatusStocklistWork;

s32 gStatusBarState EWRAM_COMMON(4);

void task_status_0(StatusWork* work) {
    sStatusWork = work;
    work->tab = 0;
    sStatusMesWindowOpen = 0;
    work->cursor = 0;
    work->scroll = 0;
    TaskPoolInit(&work->pool, 9);
    TaskCreate(&work->pool, &sTaskDescStatusFriend, NULL);
    TaskCreate(&work->pool, &sTaskDescStatusSora, NULL);

    if (!(gGameState.flags & GAME_FLAG_RIKU)) {
        TaskCreate(&work->pool, &sTaskDescStatusTab, &work->tab);
        TaskCreate(&work->pool, &sTaskDescStatusDeckname, &sStatusMesWindowOpen);
    }

    TaskCreate(&work->pool, &sTaskDescStatusStocklist, &work->tab);
    TaskCreate(&work->pool, &sTaskDescStatusScrollcursor, &work->scroll);
    TaskCreate(&work->pool, &sTaskDescStatusMeswindow, &sStatusMesWindowOpen);

    if (GetStatusVisibleRowCount() == 0) {
        work->cursor = ~work->tab;
    } else {
        work->cursor = 0;
    }

    TaskCreate(&work->pool, &sTaskDescStatusCursor, &work->cursor);
    sStatusSelectedIndex = work->cursor + work->scroll;
}

void StatusHandleInput(StatusWork* work) {
    u16 keys;

    keys = GetKeysRepeat() & DPAD_UP;

    if (keys != 0) {
        if (work->cursor > 0) {
            work->cursor--;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        } else if (work->scroll > 0) {
            work->scroll--;
            StatusStocklistScrollUp();
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        } else if (work->cursor == 0) {
            if (!(gGameState.flags & GAME_FLAG_RIKU)) {
                work->cursor = ~work->tab;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
                sStatusMesWindowOpen = 0;
            }
        }
    } else if (GetKeysRepeat() & DPAD_DOWN) {
        if (work->cursor < GetStatusVisibleRowCount() - 1) {
            if (work->cursor >= 0) {
                work->cursor++;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            } else if (GetStatusVisibleRowCount() != 0) {
                work->cursor = 0;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        } else if (work->scroll < GetStatusMaxScroll()) {
            work->scroll++;
            StatusStocklistScrollDown();
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }
    } else if ((GetKeysRepeat() & DPAD_LEFT) && !(gGameState.flags & GAME_FLAG_RIKU)) {
        if (work->tab != 0) {
            work->tab--;

            if (work->cursor < 0 || GetStatusVisibleRowCount() == 0) {
                work->cursor = ~work->tab;
                sStatusMesWindowOpen = 0;
            } else {
                work->cursor = 0;
            }

            work->scroll = 0;
            StatusStocklistLoadRows(0);
            m4aSongNumStart(SONG_SYS_CLICK);
        }
    } else if ((GetKeysRepeat() & DPAD_RIGHT) && !(gGameState.flags & GAME_FLAG_RIKU)) {
        if (work->tab <= 2) {
            work->tab++;

            if (work->cursor < 0 || GetStatusVisibleRowCount() == 0) {
                work->cursor = ~work->tab;
                sStatusMesWindowOpen = 0;
            } else {
                work->cursor = 0;
            }

            work->scroll = 0;
            StatusStocklistLoadRows(0);
            m4aSongNumStart(SONG_SYS_CLICK);
        }
    } else if (GetKeysPressed() & SELECT_BUTTON) {
        if (work->cursor >= 0) {
            work->cursor = ~work->tab;
            work->scroll = 0;
            StatusStocklistLoadRows(0);
            m4aSongNumStart(SONG_SYS_CLICKI04B);
#ifdef VERSION_EU
            sStatusMesWindowOpen = 0;
#endif
        }
    } else if ((GetKeysPressed() & A_BUTTON) && StatusTabHasItems() && sStatusMesWindowOpen == 0 && work->cursor >= 0) {
        sStatusMesWindowOpen = 1;
        m4aSongNumStart(SONG_SYS_KETTEI);
    } else if (sStatusMesWindowOpen != 0) {
        if ((GetKeysPressed() & B_BUTTON) || !StatusTabHasItems()) {
            sStatusMesWindowOpen = 0;
            m4aSongNumStart(SONG_SYS_CLOSE);
        }
    }
}

u8 task_status_1(StatusWork* work) {
    if (IsStatusBarIdle()) {
        StatusHandleInput(work);
    }

    sStatusSelectedIndex = work->cursor + work->scroll;
    TaskPoolUpdate(&work->pool);
    return 1;
}

void task_status_2(StatusWork* work) {
    TaskPoolDraw(&work->pool);
}

void task_status_3(StatusWork* work) {
    TaskPoolDestroy(&work->pool);
}

u8 IsStatusMesWindowOpen() {
    return sStatusMesWindowOpen;
}

s16 GetStatusSelectedIndex() {
    return sStatusSelectedIndex;
}

s16 GetStatusScroll() {
    return sStatusWork->scroll;
}

void StatusBarStartClose(StatusBarWork* work) {
    work->closing = 1;

    if (gStatusBarState == 0) {
        gStatusBarState = 4;
    } else {
        gStatusBarState = 3;
    }

    if (work->steps == 0) {
        work->steps = 16;
    }

    LoadBgMap(3, gUnk_09848198, 0x500);
    work->targetY = -0x800;
    work->targetY2 = 0xA000;
    work->targetX = -0x8000;
}

void task_status_bar_0(StatusBarWork* work) {
#ifdef VERSION_EU
    work->tiles = LoadObjTiles(sStatusBarTiles[gLanguage], sStatusBarTileSizes[gLanguage]);
#else
    work->tiles = LoadObjTiles(gUnk_097A18EC, 0x2E0);
#endif
    work->palette = LoadObjPalette(gUnk_0984B1B8, 0x20);
    work->steps = 16;
    gStatusBarState = 0;
    work->y = -0x800;
    work->y2 = 0xA000;
    work->x = -0x8000;
    work->targetY = 0;
    work->targetY2 = 0x9800;
    work->targetX = 0;
    work->closing = 0;
    work->fadeStarted = 0;
}

u8 task_status_bar_1(StatusBarWork* work) {
    switch (gStatusBarState) {
    case 0:
        ApproachValue(&work->y, work->targetY, work->steps);
        ApproachValue(&work->y2, work->targetY2, work->steps);
        work->steps--;

        if (work->steps == 0) {
            work->steps = 16;
            gStatusBarState = 1;
        }

        break;
    case 1:
        ApproachValue(&work->x, work->targetX, work->steps);
        work->steps--;

        if (work->steps == 0) {
            LoadBgMap(3, gUnk_09848698, 0x500);
            gStatusBarState = 2;
        }

        break;
    case 3:
        ApproachValue(&work->x, work->targetX, work->steps);
        work->steps--;

        if (work->steps == 0) {
            work->steps = 16;
            gStatusBarState = 4;
        }

        break;
    case 4:
        if (!FadeIsActive() && !work->fadeStarted) {
            FadeStartOut(FADE_MODE_BLACK, 16);
            work->fadeStarted = 1;
        }

        ApproachValue(&work->y, work->targetY, work->steps);
        ApproachValue(&work->y2, work->targetY2, work->steps);
        work->steps--;

        if (work->steps == 0) {
            return 0;
        }

        break;
    case 2:
        if (!work->closing) {
            if (GetKeysPressed() & START_BUTTON) {
                m4aSongNumStart(SONG_SYS_CLOSE);
                FadeStartOut(FADE_MODE_BLACK, 16);
                SetStatusReturnToMenu(0);
                gStatusBarState = 5;
            } else if (GetKeysPressed() & B_BUTTON) {
                if (!IsStatusMesWindowOpen()) {
                    m4aSongNumStart(SONG_SYS_CLOSE);
                    StatusBarStartClose(work);
                    SetStatusReturnToMenu(1);
                }
            }
        }

        break;
    case 5:
        if (!FadeIsActive()) {
            return 0;
        }

        break;
    }

    return 1;
}

void task_status_bar_2(StatusBarWork* work) {
#ifdef VERSION_EU
    DrawSprite(work->x >> 8, 0, (sStatusBarSprites[gLanguage])[2], work->tiles,
        work->palette, NULL, SPRITE_PRIORITY(3), 29);
#else
    DrawSprite(work->x >> 8, 0, gUnk_097A18CC, work->tiles, work->palette, NULL, SPRITE_PRIORITY(3), 29);
#endif

    if (gStatusBarState != 2) {
#ifdef VERSION_EU
        DrawSprite(128, work->y >> 8, (sStatusBarSprites[gLanguage])[0], work->tiles,
            work->palette, NULL, SPRITE_PRIORITY(3), 30);
        DrawSprite(128, work->y2 >> 8, (sStatusBarSprites[gLanguage])[1], work->tiles,
            work->palette, NULL, SPRITE_PRIORITY(3), 31);
#else
        DrawSprite(128, work->y >> 8, gUnk_097A1864, work->tiles, work->palette, NULL, SPRITE_PRIORITY(3), 30);
        DrawSprite(128, work->y2 >> 8, gUnk_097A1898, work->tiles, work->palette, NULL, SPRITE_PRIORITY(3), 31);
#endif
    }
}

void task_status_bar_3(StatusBarWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

u8 IsStatusBarIdle() {
    if (gStatusBarState == 2) {
        return 1;
    }

    return 0;
}

void task_status_tab_0(StatusTabWork* work, s32* arg) {
    work->tab = arg;
#ifdef VERSION_EU
    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(sStatusTabSprites[gLanguage], 4),
        sStatusTabTiles[gLanguage]);
#else
    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF6920, 4), gUnk_097A24A6);
#endif
    work->palette = LoadObjPalette(gUnk_0984B218, 0x20);
#ifdef VERSION_EU
    work->gfx = (sStatusTabSprites[gLanguage])[*work->tab];
#else
    work->gfx = gUnk_09EF6920[*work->tab];
#endif
    work->tiles2 = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF6934, 4), gUnk_097A28DA);
    work->palette2 = LoadObjPalette(gUnk_0984B238, 0x20);
    work->gfx2 = gUnk_09EF6934[*work->tab];
}

u8 task_status_tab_1(StatusTabWork* work) {
#ifdef VERSION_EU
    work->gfx = (sStatusTabSprites[gLanguage])[*work->tab];
#else
    work->gfx = gUnk_09EF6920[*work->tab];
#endif
    work->gfx2 = gUnk_09EF6934[*work->tab];
    return 1;
}

void task_status_tab_2(StatusTabWork* work) {
    DrawSprite(0, 16, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), 10);
    DrawSprite(0, 16, work->gfx2, work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(2), 11);
}

void task_status_tab_3(StatusTabWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette2);
}

void task_status_sora_0(StatusSoraWork* work) {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        work->tiles = AllocObjTiles(0x800, NULL);
        work->palette = LoadObjPalette(gRikuPalette, 0x20);
        SetObjTileSource(work->tiles, gRikuBt00Tiles);
        AnimInit(&work->anim, gRikuBt00Anims, gRikuBt00Frames);
    } else {
        work->tiles = AllocObjTiles(0x500, NULL);
        work->palette = LoadObjPalette(gSoraPalette, 0x20);
        SetObjTileSource(work->tiles, gSor1ll51Tiles);
        AnimInit(&work->anim, gSor1ll51Anims, gSor1ll51Frames);
    }

    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
}

u8 task_status_sora_1(StatusSoraWork* work) {
    work->gfx = AnimUpdate(&work->anim);
    return 1;
}

void task_status_sora_2(StatusSoraWork* work) {
    s16 x;
    s16 y;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        x = 160;
        y = 65;
    } else {
        x = 140;
        y = 56;
    }

    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), 12);
}

void task_status_sora_3(StatusSoraWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_status_deckname_0(StatusDecknameWork* work, u8* arg) {
    InitTextSlots(work->textSlots, 10);
    work->mesWindowOpen = arg;
    work->textSlotCount = LoadTextSlots(GetDeckName(GetActiveDeckIndex()), work->textSlots);
    work->palette = LoadObjPalette(gUnk_0984B1D8, 0x20);
}

u8 task_status_deckname_1(StatusDecknameWork* work) {
    return 1;
}

void task_status_deckname_2(StatusDecknameWork* work) {
    if (*work->mesWindowOpen == 0) {
        DrawTextSlots(144, 142, work->textSlots, work->palette, 4, work->textSlotCount);
    }
}

void task_status_deckname_3(StatusDecknameWork* work) {
    FreeTextSlots(work->textSlots, 10);
    ReleaseObjPalette(work->palette);
}

void task_status_cursor_0(StatusCursorWork* work, s16* arg) {
    work->cursor = arg;
    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF68F0, 5), gUnk_097A1C54);
    work->palette = LoadObjPalette(gUnk_0984B1D8, 0x20);
    AnimInit(&work->anim[0], gUnk_09EF6904, gUnk_09EF68F0);
    AnimStart(&work->anim[0], 0, ANIM_FLAG_LOOP);
    work->gfx[0] = AnimGetGfx(&work->anim[0]);
    work->tiles2 = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF6908, 4), gUnk_097A2394);
    work->palette2 = LoadObjPalette(gUnk_0984B1F8, 0x20);
    AnimInit(&work->anim[1], gUnk_09EF691C, gUnk_09EF6908);
    AnimStart(&work->anim[1], 0, ANIM_FLAG_LOOP);
    work->gfx[1] = AnimGetGfx(&work->anim[1]);
    work->lastCursor = *work->cursor;

    if (work->lastCursor < 0) {
        work->x = sStatusTabCursorX[~work->lastCursor];
        work->targetX = work->x;
        work->y = 0x1000;
        work->targetY = 0x1000;
    } else {
        work->x = 0x1800;
        work->targetX = 0x1800;
        work->y = *work->cursor * 3072 + 0x2400;
        work->targetY = work->y;
    }

    work->unk_4E = 0;
}

u8 task_status_cursor_1(StatusCursorWork* work) {
    s32 i;

    if (work->lastCursor != *work->cursor) {
        work->lastCursor = *work->cursor;
        work->unk_4E = 4;

        if (work->lastCursor < 0) {
            work->targetX = sStatusTabCursorX[~work->lastCursor];
            work->targetY = 0x1000;
        } else {
            work->targetX = 0x1800;
            work->targetY = *work->cursor * 3072 + 0x2400;
        }
    }

    ApproachValueHalf(&work->y, work->targetY);
    ApproachValueHalf(&work->x, work->targetX);

    for (i = 0; i < 2; i++) {
        work->gfx[i] = AnimUpdate(&work->anim[i]);
    }

    return 1;
}

void task_status_cursor_2(StatusCursorWork* work) {
    if (!FadeIsActive()) {
        if (!(gGameState.flags & GAME_FLAG_RIKU) || StatusTabHasItems()) {
            DrawSprite(work->x >> 8, (work->y >> 8) - 16, work->gfx[1], work->tiles2, work->palette2, NULL, 0, 0);

            if (work->lastCursor >= 0) {
                DrawSprite(1, (work->y >> 8) + 3, work->gfx[0], work->tiles, work->palette, NULL, 0, 1);
            }
        }
    }
}

void task_status_cursor_3(StatusCursorWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette2);
}

void task_status_stocklist_0(StatusStocklistWork* work, s32* arg) {
    s32 i;
    StatusEntry* e;

    sStatusStocklistWork = work;
    work->tab = arg;
    e = work->entries;

    for (i = 0; i < 4; i++) {
        StatusEntryClear(e);
        e++;
    }

    if (gGameState.flags & GAME_FLAG_RIKU) {
        for (i = 66; i <= 69; i++) {
            if (IsStockLearned(i)) {
                StatusEntryAppend(work->entries, i);
            }
        }
    } else {
        for (i = 0; i <= 65; i++) {
            if (IsStockLearned(i)) {
                StatusEntryAppend(work->entries, i);
                StatusEntryAppend(&work->entries[GetStatusItemTab(i)], i);
            }
        }
    }

    for (i = 0; i < 8; i++) {
        work->tiles2[i] = NULL;
    }

    StatusStocklistLoadRows(0);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
#ifdef VERSION_EU
    work->tiles = LoadObjTiles(sStatusNewMarkTiles[gLanguage], sStatusNewMarkTileSizes[gLanguage]);
#else
    work->tiles = LoadObjTiles(gUnk_097A2E16, 0xC0);
#endif
    work->palette2 = LoadObjPalette(gUnk_0984B278, 0x20);
#ifdef VERSION_EU
    work->gfx = sStatusNewMarkSprites[gLanguage];
#else
    work->gfx = gUnk_097A2DF8;
#endif
    work->timer = 0;
    work->blink = 0;
}

u8 task_status_stocklist_1(StatusStocklistWork* work) {
    work->timer++;

    if (work->timer > 24) {
        work->blink = !work->blink ? 1 : 0;
        work->timer = 0;
    }

    return 1;
}

void task_status_stocklist_2(StatusStocklistWork* work) {
    s32 i;
    s16 y;

    y = 36;

    for (i = 0; i < 8; i++) {
        if (work->tiles2[i] != NULL) {
            if (work->blink) {
                if (IsStockNew(GetStatusListItem(GetStatusScroll() + i))) {
                    DrawSprite(0, y, work->gfx, work->tiles, work->palette2, NULL, SPRITE_PRIORITY(2), i + 13);
                }
            }

            DrawSprite(1, y, NULL, work->tiles2[i], work->palette, NULL, SPRITE_PRIORITY(2), i + 21);
        }

        y += 12;
    }
}

void task_status_stocklist_3(StatusStocklistWork* work) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (work->tiles2[i] != NULL) {
            ReleaseObjTiles(work->tiles2[i]);
        }
    }

    ReleaseObjPalette(work->palette);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette2);
}

u16 GetStatusVisibleRowCount() {
    if (sStatusStocklistWork->entries[*sStatusStocklistWork->tab].count <= 7) {
        return sStatusStocklistWork->entries[*sStatusStocklistWork->tab].count;
    }

    return 8;
}

u16 GetStatusMaxScroll() {
    s16 v = sStatusStocklistWork->entries[*sStatusStocklistWork->tab].count - 8;

    if (v <= 0) {
        return 0;
    }

    return v;
}

u8 StatusTabHasItems() {
    if (sStatusStocklistWork->entries[*sStatusStocklistWork->tab].count == 0) {
        return 0;
    }

    return 1;
}

void StatusStocklistScrollDown() {
    s32 i;

    ReleaseObjTiles(sStatusStocklistWork->tiles2[0]);

    for (i = 0; i < 7; i++) {
        sStatusStocklistWork->tiles2[i] = sStatusStocklistWork->tiles2[i + 1];
    }

    sStatusStocklistWork->scroll++;
    sStatusStocklistWork->tiles2[7] = LoadStockNameTiles(GetStatusItemStockIndex(sStatusStocklistWork->entries[*sStatusStocklistWork->tab].items[sStatusStocklistWork->scroll + 7]));
}

void StatusStocklistScrollUp() {
    s32 i;

    ReleaseObjTiles(sStatusStocklistWork->tiles2[7]);

    for (i = 7; i > 0; i--) {
        sStatusStocklistWork->tiles2[i] = sStatusStocklistWork->tiles2[i - 1];
    }

    sStatusStocklistWork->scroll--;
    sStatusStocklistWork->tiles2[0] = LoadStockNameTiles(GetStatusItemStockIndex(sStatusStocklistWork->entries[*sStatusStocklistWork->tab].items[sStatusStocklistWork->scroll]));
}

void StatusStocklistLoadRows(u16 a) {
    s32 i;

    for (i = 0; i <= 7; i++) {
        if (sStatusStocklistWork->tiles2[i] != NULL) {
            ReleaseObjTiles(sStatusStocklistWork->tiles2[i]);
            sStatusStocklistWork->tiles2[i] = NULL;
        }
    }

    sStatusStocklistWork->scroll = a;

    for (i = 0; i < sStatusStocklistWork->entries[*sStatusStocklistWork->tab].count - a && i <= 7; i++) {
        sStatusStocklistWork->tiles2[i] = LoadStockNameTiles(GetStatusItemStockIndex(sStatusStocklistWork->entries[*sStatusStocklistWork->tab].items[a + i]));
    }
}

s32 GetStatusListItem(s16 a) {
    return sStatusStocklistWork->entries[*sStatusStocklistWork->tab].items[a];
}

void StatusEntryClear(StatusEntry* e) {
    e->count = 0;
}

void StatusEntryAppend(StatusEntry* e, s32 v) {
    e->items[e->count] = v;
    e->count++;
}

s32 GetStatusItemTab(u32 a) {
    if (a <= 8) {
        return 1;
    }

    if (a >= 9 && a <= 46) {
        return 2;
    }

    return 3;
}

void* LoadStockNameTiles(u16 a) {
    const SpriteFrameResourceDef* d;
    void* t;

    d = &gStockNameSprites[a];
    t = AllocSpriteFrameTiles(d->tilesSize);
#ifdef VERSION_EU
    UpdateSpriteFrameTiles(t, d->sprites[gLanguage][d->spriteIndex],
        d->tiles[gLanguage]);
#else
    UpdateSpriteFrameTiles(t, d->sprites[d->spriteIndex], d->tiles);
#endif
    return t;
}

s32 GetStatusItemStockIndex(s32 a) {
    switch (a) {
    case 1:
        return 46;
    case 5:
        return 5;
    case 6:
        return 47;
    case 4:
        return 6;
    case 7:
        return 48;
    case 8:
        return 49;
    case 0:
        return 50;
    case 2:
        return 51;
    case 3:
        return 52;
    case 39:
        return 53;
    case 38:
        return 54;
    case 42:
        return 55;
    case 41:
        return 56;
    case 70:
        return 57;
    case 27:
        return 58;
    case 28:
        return 59;
    case 29:
        return 60;
    case 23:
        return 61;
    case 24:
        return 62;
    case 25:
        return 63;
    case 26:
        return 64;
    case 34:
        return 65;
    case 46:
        return 66;
    case 58:
        return 67;
    case 71:
        return 68;
    case 44:
        return 69;
    case 32:
        return 70;
    case 31:
        return 71;
    case 35:
        return 72;
    case 50:
        return 73;
    case 56:
        return 74;
    case 30:
        return 75;
    case 33:
        return 76;
    case 43:
        return 77;
    case 40:
        return 78;
    case 36:
        return 79;
    case 37:
        return 80;
    case 45:
        return 81;
    case 9:
        return 0;
    case 11:
        return 1;
    case 13:
        return 2;
    case 15:
        return 3;
    case 17:
        return 11;
    case 19:
        return 4;
    case 21:
        return 44;
    case 10:
        return 7;
    case 12:
        return 8;
    case 14:
        return 9;
    case 16:
        return 10;
    case 18:
        return 12;
    case 20:
        return 13;
    case 22:
        return 45;
    case 47:
        return 18;
    case 52:
        return 20;
    case 53:
        return 26;
    case 51:
        return 28;
    case 55:
        return 30;
    case 49:
        return 22;
    case 48:
        return 24;
    case 57:
        return 16;
    case 59:
        return 15;
    case 60:
        return 14;
    case 61:
        return 32;
    case 62:
        return 36;
    case 63:
        return 34;
    case 64:
        return 38;
    case 65:
        return 40;
    case 66:
        return 82;
    case 67:
        return 83;
    case 68:
        return 84;
    case 54:
        return 31;
    case 69:
        return 42;
    case 72:
        return 0xFFFF;
    }
}

s16 GetStatusScrollcursorY(StatusScrollcursorWork* work) {
    if (GetStatusMaxScroll() == 0) {
        return 40;
    }

    return *work->scroll * 84 / GetStatusMaxScroll() + 40;
}

void task_status_scrollcursor_0(StatusScrollcursorWork* work, u16* arg) {
    work->scroll = arg;
    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF6908, 4), gUnk_097A2394);
    work->palette = LoadObjPalette(gUnk_0984B1F8, 0x20);
    work->gfx = gUnk_09EF6908[4];
    work->y = GetStatusScrollcursorY(work);
}

u8 task_status_scrollcursor_1(StatusScrollcursorWork* work) {
    work->y = GetStatusScrollcursorY(work);
    return 1;
}

void task_status_scrollcursor_2(StatusScrollcursorWork* work) {
    if (StatusTabHasItems()) {
        DrawSprite(84, work->y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), 6);
    }
}

void task_status_scrollcursor_3(StatusScrollcursorWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_status_meswindow_0(StatusMeswindowWork* work, u8* arg) {
    work->open = arg;
    work->item = 72;
    TaskPoolInit(&work->pool, 2);
    work->task = NULL;
    work->textIndex = 0;
}

u8 task_status_meswindow_1(StatusMeswindowWork* work) {
    s32 v;
    s16 idx;

    if (*work->open != 0) {
        idx = GetStatusSelectedIndex();

        if (idx >= 0) {
            v = GetStatusListItem(GetStatusSelectedIndex());

            if (work->item != v) {
                work->item = v;

                if (work->task != NULL) {
                    work->textIndex = GetStockMesDispTextIndex(work->task);
                    TaskKill(&work->pool, work->task);
                }

                work->task = CreateStockMesDispTask(&work->pool, GetStatusItemStockIndex(work->item), work->textIndex, 88, 98);
                ClearStockNew(work->item);
            }

            TaskPoolUpdate(&work->pool);
        }
    }

    return 1;
}

void task_status_meswindow_2(StatusMeswindowWork* work) {
    if (*work->open == 0) {
        DisableBg(0);
    } else {
        EnableBg(0);
        TaskPoolDraw(&work->pool);
    }
}

void task_status_meswindow_3(StatusMeswindowWork* work) {
    TaskPoolDestroy(&work->pool);
}

void task_status_message_0(StatusMessageWork* work, StatusMessageParam* arg) {
    InitTextSlots(work->textSlots, 100);
    work->param = *arg;
    work->textSlotCount = LoadTextSlots(work->param.text, work->textSlots);
    work->palette = LoadObjPalette(gUnk_0984B1B8, 0x20);
}

u8 task_status_message_1(StatusMessageWork* work) {
    return 1;
}

void task_status_message_2(StatusMessageWork* work) {
    DrawTextSlots(work->param.x, work->param.y, work->textSlots, work->palette, 3, work->textSlotCount);
}

void task_status_message_3(StatusMessageWork* work) {
    FreeTextSlots(work->textSlots, 100);
    ReleaseObjPalette(work->palette);
}

Task* CreateStatusMessageTask(void* pool, s16 x, s16 y, void* p) {
    StatusMessageParam param;

    param.x = x;
    param.y = y;
    param.text = p;
    return TaskCreate(pool, &sTaskDescStatusMessage, &param);
}

void task_status_friend_0(StatusFriendWork* work) {
    work->count = LoadFriendCardSprites(work->tiles, work->palette, work->gfx);
}

u8 task_status_friend_1(StatusFriendWork* work) {
    return 1;
}

void task_status_friend_2(StatusFriendWork* work) {
    s32 i;
    s16 x;

    x = (gGameState.flags & GAME_FLAG_RIKU) ? 216 : 186;

    for (i = 0; i < work->count; i++) {
        DrawSprite(x, 45, work->gfx[i], work->tiles[i], work->palette[i], NULL, SPRITE_PRIORITY(2), i + 7);
        x += 20;
    }
}

void task_status_friend_3(StatusFriendWork* work) {
    s32 i;

    for (i = 0; i < work->count; i++) {
        ReleaseObjTiles(work->tiles[i]);
        ReleaseObjPalette(work->palette[i]);
    }
}

u16 LoadFriendCardSprites(void** a, void** b, void** c) {
    StatusFriendTable table;
    const CardDef* card;
    const void* data;
    u16 count;
    u16 index;
    u16 limit;
    const void* source;

    source = &sStatusFriendTable;
    table = *(const StatusFriendTable*)source;

    data = &gGameState;

    if (((const GameState*)data)->flags & GAME_FLAG_RIKU) {
        limit = 1;
    } else {
        limit = 3;
    }

    count = 0;

    for (index = 0; index <= 7; index++) {
        data = &table.entries[index];
        source = &gGameState.progression.friendFlags;

        if (*(const u16*)source & ((const StatusFriendEntry*)data)->flag) {
            card = &gCardDefs[((const StatusFriendEntry*)data)->cardId];
            a[count] = LoadObjTiles(card->tiles2, 0x100);
            b[count] = LoadObjPalette(card->palette2, 0x20);
            c[count] = card->gfx2;
            count++;

            if (count >= limit) {
                break;
            }
        }
    }

    return count;
}

void stock_mes_disp_0(StockMesDispWork* work, StatusMesParam* arg) {
    gStockMesDispWork = work;
    *(StatusMesParam*)&work->x = *arg;
    work->textCount = GetCardHelpTextCount(work->helpIndex);

    if (work->textIndex >= work->textCount - 1) {
        work->textIndex = work->textCount - 1;
    }

    work->tiles = LoadStockNameTiles(work->helpIndex);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    TaskPoolInit(&work->tasks, 1);
    work->task = CreateStatusMessageTask(&work->tasks, work->x + 6, work->y + 16,
                                        GetCardHelpText(work->helpIndex, work->textIndex));
    work->tiles2 = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF6948, 2), gUnk_097A2CF6);
    work->palette2 = LoadObjPalette(gUnk_0984B258, 0x20);
    work->gfx = gUnk_09EF6948[0];
    work->tiles3 = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF6948, 2), gUnk_097A2CF6);
    work->palette3 = LoadObjPalette(gUnk_0984B258, 0x20);
    work->gfx2 = gUnk_09EF6948[1];
    work->frame = 0;
}

u8 stock_mes_disp_1(StockMesDispWork* work) {
    u8 changed = 0;

    if (GetKeysPressed() & R_BUTTON) {
        if (work->textIndex < work->textCount - 1) {
            work->textIndex++;
            changed = 1;
        }
    } else if (GetKeysPressed() & L_BUTTON) {
        if (work->textIndex != 0) {
            work->textIndex--;
            changed = 1;
        }
    }

    if (changed) {
        m4aSongNumStart(SONG_SYS_CANSEL);
        TaskKill(&work->tasks, work->task);
        work->task = CreateStatusMessageTask(&work->tasks, work->x + 6, work->y + 16, GetCardHelpText(work->helpIndex, work->textIndex));
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void stock_mes_disp_2(StockMesDispWork* work) {
    DrawSprite(work->x + 14, work->y - 4, NULL, work->tiles, work->palette, NULL, 0, 5);

    if (work->textIndex != 0) {
        DrawSprite(work->x - (work->frame / 8) % 4, work->y, work->gfx, work->tiles2, work->palette2, NULL, 0, 2);
    }

    if (work->textIndex < work->textCount - 1) {
        DrawSprite(work->x + ((work->frame / 8) % 4 + 136), work->y, work->gfx2, work->tiles3, work->palette3, NULL, 0, 3);
    }

    TaskPoolDraw(&work->tasks);
    work->frame++;
}

void stock_mes_disp_3(StockMesDispWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette2);
    ReleaseObjTiles(work->tiles3);
    ReleaseObjPalette(work->palette3);
    TaskPoolDestroy(&work->tasks);
}

void* CreateStockMesDispTask(void* pool, u16 b, u8 c, u16 d, s32 e) {
    StatusMesParam p;

    p.helpIndex = b;
    p.textIndex = c;
    p.x = d;
    p.y = e;
    return TaskCreate(pool, &gTaskDescStockMesDisp, &p);
}

u8 GetStockMesDispTextIndex(void* a) {
    return ((StockMesDispWork*)gStockMesDispWork)->textIndex;
}

TaskDesc gTaskDescStockMesDisp = {
    "stock_mes_disp",
    (TaskInitFunc)stock_mes_disp_0,
    (TaskUpdateFunc)stock_mes_disp_1,
    (TaskDrawFunc)stock_mes_disp_2,
    (TaskDestroyFunc)stock_mes_disp_3,
    sizeof(StockMesDispWork),
};
