/**
 * mode_debug.c
 * Debug Menu
 */

#include "mode_continue.h"
#include "mode_chkmov.h"
#include "system_state.h"
#include "mode_debug.h"
#include "game_state.h"
#include "sprites_mode_debug.h"
#include "gba/keys.h"
#include "malloc.h"
#include "fade.h"
#include "songs.h"
#include "player_progression.h"
#include "gba/io_reg.h"
#include "anim.h"
#include "card_api.h"
#include "display.h"
#include "key.h"
#include "m4a_song.h"
#include "mode.h"
#include "obj_api.h"
#include "pallet.h"
#include "player_progression_types.h"
#include "registration_data.h"
#include "save_api.h"
#include <stddef.h>
#include "types.h"
#include "debug_text.h"

static DebugWork* sDebugWork;

#ifdef VERSION_US
const char gVersionString[12] = "N041001a";
#elif defined(VERSION_JP)
const char gVersionString[12] = "J041001a";
#else
const char gVersionString[12] = "E041220b";
#endif

void mode_debug_0() {
    m4aMPlayAllStop();
#ifdef VERSION_EU
    SaveLoadHeader();
#endif
    sDebugWork = EwramAlloc(sizeof(DebugWork));
    FadeStartIn(FADE_MODE_WHITE, 16);
    ResetGameState();
#ifdef VERSION_EU
    gDebugFlags |= DEBUG_FLAG_DEBUG_MENU;
#endif
    SetBgMode0();
    SetupBg(0, 0, 15, 0);
    SetupBg(1, 2, 31, 0);
    SetBgColorMode(1, BGCNT_256COLOR);
    SetBgSize(1, 0);
#ifdef VERSION_EU
    LoadBgPalette(1, gDebugMenuBgPalette, 0x200);
    LoadBgTilesLz77(1, gDebugMenuBgTiles);
    LoadBgMapLz77(1, gDebugMenuBgMap);
#else
    LoadBgTiles(1, gDebugMenuBgTiles, 0x5B40);
    LoadBgPalette(1, gDebugMenuBgPalette, 0x200);
    LoadBgMap(1, gDebugMenuBgMap, 0x800);
#endif
    EnableBg(1);
    SetBackdropColor(31, 31, 31);
    EnableBg(0);
    DebugTextInit(0, 0x5400, 0x500);
    DebugTextLoadPalette(0, gDebugMenuTextPalette, 0x20, 0x0F);
    sDebugWork->tiles = LoadObjTiles(gDebugMenuCursorTiles, 0x2E0);
    sDebugWork->palette = LoadObjPalette(gDebugMenuCursorPalette, 0x20);
    AnimInit(&sDebugWork->anim, gDebugMenuCursorAnims, gDebugMenuCursorFrames);
    AnimStart(&sDebugWork->anim, 0, ANIM_FLAG_LOOP);
#ifdef VERSION_JP
    DebugTextPrint(0, 0, 2, "\x82\x69\x82\x4f\x82\x53\x82\x50\x82\x4f\x82\x4f\x82\x50\x82\x81");
#elif defined(VERSION_EU)
    DebugTextPrint(0, 0, 2, "\x82\x64\x82\x4f\x82\x53\x82\x50\x82\x51\x82\x51\x82\x4f\x82\x82");
#else
    DebugTextPrint(0, 0, 2, "\x82\x6d\x82\x4f\x82\x53\x82\x50\x82\x4f\x82\x4f\x82\x50\x82\x81");
#endif

    if (GetPaletteEffect() < 0) {
        DebugTextPrint(168, 150, 2, "\x82\x63\x82\x60\x82\x71\x82\x6a\x82\x64\x82\x71");
    } else if (GetPaletteEffect() > 0) {
        DebugTextPrint(168, 150, 2, "\x82\x6b\x82\x68\x82\x66\x82\x67\x82\x73\x82\x64\x82\x71");
    } else {
        DebugTextPrint(144, 150, 2, "\x82\x61\x82\x71\x82\x68\x82\x66\x82\x67\x82\x73\x82\x6d\x82\x64\x82\x72\x82\x72");
    }

    sDebugWork->cursor = 0;
    sDebugWork->page = -1;
}

void mode_debug_1() {
    s16 v;
    s8 old;
    void* gfx;

    v = GetPaletteEffect();

    switch (GetKeysPressed() & (L_BUTTON | R_BUTTON)) {
    case R_BUTTON:
        if (v <= 23) {
            SetPaletteEffect(v + 1);
            ModeRequest(&gModeDebug, 0);
            return;
        }

        break;
    case L_BUTTON:
        if (v > -24) {
            SetPaletteEffect(v - 1);
            ModeRequest(&gModeDebug, 0);
            return;
        }

        break;
    }

    if (GetKeysRepeat() & DPAD_UP) {
        sDebugWork->cursor--;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    if (GetKeysRepeat() & DPAD_DOWN) {
        sDebugWork->cursor++;
        m4aSongNumStart(SONG_SYS_CLICK);
    }

    switch (sDebugWork->cursor) {
    case 0:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
#ifdef VERSION_EU
            gDebugFlags &= ~DEBUG_FLAG_DEBUG_MENU;
#endif
            ModeRequest(&gModeCopyright1, 0);
            return;
        }

        break;
    case 1:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequest(&gModeChkobj, 0);
            return;
        }

        break;
    case 2:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
#ifdef VERSION_EU
            gDebugFlags &= ~DEBUG_FLAG_DEBUG_MENU;
#endif
            ModeRequest(&gModeMapChk, 0);
            return;
        }

        break;
    case 3:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequest(&gModeChkeff, 0);
            return;
        }

        break;
    case 4:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequest(&gModeChksnd, 0);
            return;
        }

        break;
    case 5:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequest(&gModeEventselect, 0);
            return;
        }

        break;
    case 6:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
#ifndef VERSION_EU
            SaveLoadHeader();
#endif
            func_08085FB0();
            InitSoraDecks();
            ModeRequest(&gModeSioBattle, 0);
            return;
        }

        break;
    case 7:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequest(&gModeChkbtl, 0);
        }

        break;
    case 8:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequest(&gModePooh, 0);
        }

        break;
    case 9:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequest(&gModeDebflag, 0);
        }

        break;
    case 10:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequest(&gModeWLogo, 0);
        }

        break;
    case 11:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            SaveClearHeader();
            SaveClearFileLarge(0);
            SaveClearFileLarge(1);
            SaveClearFileSmall(0);
            SaveClearFileSmall(1);
            SaveClearSystem();
            ModeRequest(&gModeDebug, 0);
        }

        break;
    case 12:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            SetJiminyFlag(0);
            SetJiminyFlag(17);
            SetJiminyFlag(18);
            SetJiminyFlag(19);
            SetJiminyFlag(20);
            SetJiminyFlag(21);
            SetJiminyFlag(22);
            ModeRequest(&gModeBackupstat, 0);
        }

        break;
#ifdef VERSION_EU
    case 13:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequest(&gModeMovieDebugEu, 0);
        }

        break;
    case 14:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequest(&gModeStaffRoll, 0);
        }

        break;
    case 15:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequest(&gModeLang, 0);
        }

        break;
    case 16:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            SetJiminyFlag(250);
            ModeRequest(&gModeJiminy, 0);
        }

        break;
    case 17:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            gGameState.availableWorlds = 0xFFFF;
            gGameState.progression.tutorialFlags = -1;
            ModeRequest(&gModeWorldselect, 0);
        }

        break;
    case 18:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequest(&gModeContinue, 0);
        }

        break;
    case 19:
        sDebugWork->cursor = 0;
        break;
    case -1:
        sDebugWork->cursor = 18;
        break;
#else
    case 13:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequestHeapReset(&gModeMovie, 1);
        }

        break;
    case 14:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequestHeapReset(&gModeMovie, 2);
        }

        break;
    case 15:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequestHeapReset(&gModeMovie, 3);
        }

        break;
    case 16:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequestHeapReset(&gModeMovie, 4);
        }

        break;
    case 17:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            ModeRequestHeapReset(&gModeMovie, 5);
        }

        break;
    case 18:
        sDebugWork->cursor = 0;
        break;
    case -1:
        sDebugWork->cursor = 17;
        break;
#endif
    }

    old = sDebugWork->page;
    sDebugWork->page = sDebugWork->cursor / 9;

    if (GetKeysRepeat() & DPAD_LEFT) {
        sDebugWork->page--;

        if (sDebugWork->page < 0) {
            sDebugWork->page = 2;
        }

        sDebugWork->cursor = sDebugWork->page * 9;
    } else if (GetKeysRepeat() & DPAD_RIGHT) {
        sDebugWork->page++;

        if (sDebugWork->page > 2) {
            sDebugWork->page = 0;
        }

        sDebugWork->cursor = sDebugWork->page * 9;
    }

    if (old != sDebugWork->page) {
        switch (sDebugWork->page) {
        case 0:
            DebugTextPrint(24, 12, 2, "\x82\x6c\x82\x60\x82\x68\x82\x6d\x81\x40\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 28, 2, "\x82\x6e\x82\x61\x82\x69\x82\x64\x82\x62\x82\x73\x81\x40\x81\x40");
            DebugTextPrint(24, 44, 2, "\x82\x6c\x82\x60\x82\x6f\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 60, 2, "\x82\x64\x82\x65\x82\x65\x82\x64\x82\x62\x82\x73\x81\x40\x81\x40");
            DebugTextPrint(24, 76, 2, "\x82\x72\x82\x6e\x82\x74\x82\x6d\x82\x63\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 92, 2, "\x82\x64\x82\x75\x82\x64\x82\x6d\x82\x73\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 108, 2, "\x82\x6b\x82\x68\x82\x6d\x82\x6a\x81\x40\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 124, 2, "\x82\x61\x82\x60\x82\x73\x82\x73\x82\x6b\x82\x64\x81\x40\x81\x40");
            DebugTextPrint(24, 140, 2, "\x82\x6f\x82\x6e\x82\x6e\x82\x67\x81\x40\x81\x40\x81\x40\x81\x40");
            break;
#ifdef VERSION_EU
        case 1:
            DebugTextPrint(24, 12, 2, "\x82\x65\x82\x6b\x82\x60\x82\x66\x81\x40\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 28, 2, "\x82\x6b\x82\x6e\x82\x66\x82\x6e\x81\x40\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 44, 2, "\x82\x63\x82\x64\x82\x6b\x81\x40\x82\x72\x82\x60\x82\x75\x82\x64");
            DebugTextPrint(24, 60, 2, "\x82\x6e\x82\x6f\x82\x64\x81\x40\x82\x72\x82\x60\x82\x75\x82\x64");
            DebugTextPrint(24, 76, 2, "\x82\x6c\x82\x6e\x82\x75\x82\x68\x82\x64\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 92, 2, "\x82\x64\x82\x6d\x82\x63\x82\x71\x82\x6e\x82\x6b\x82\x6b\x81\x40");
            DebugTextPrint(24, 108, 2, "\x82\x6b\x82\x60\x82\x6d\x82\x66\x82\x74\x82\x60\x82\x66\x82\x64");
            DebugTextPrint(24, 124, 2, "\x82\x69\x82\x6e\x82\x74\x82\x71\x82\x6d\x82\x60\x82\x6b\x81\x40");
            DebugTextPrint(24, 140, 2, "\x82\x76\x82\x6e\x82\x71\x82\x6b\x82\x63\x82\x72\x82\x64\x82\x6b");
            break;
        case 2:
        default:
            DebugTextPrint(24, 12, 2, "\x82\x62\x82\x6e\x82\x6d\x82\x73\x82\x68\x82\x6d\x82\x74\x82\x64");
            DebugTextPrint(24, 28, 2, "\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 44, 2, "\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 60, 2, "\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 76, 2, "\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 92, 2, "\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 108, 2, "\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 124, 2, "\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 140, 2, "\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40");
            break;
#else
        default:
            DebugTextPrint(24, 12, 2, "\x82\x65\x82\x6b\x82\x60\x82\x66\x81\x40\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 28, 2, "\x82\x6b\x82\x6e\x82\x66\x82\x6e\x81\x40\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(24, 44, 2, "\x82\x63\x82\x64\x82\x6b\x81\x40\x82\x72\x82\x60\x82\x75\x82\x64");
            DebugTextPrint(24, 60, 2, "\x82\x6e\x82\x6f\x82\x64\x81\x40\x82\x72\x82\x60\x82\x75\x82\x64");
            DebugTextPrint(24, 76, 2, "\x82\x6c\x82\x6e\x82\x75\x82\x68\x82\x64\x82\x50\x81\x40\x81\x40");
            DebugTextPrint(24, 92, 2, "\x82\x6c\x82\x6e\x82\x75\x82\x68\x82\x64\x82\x51\x81\x40\x81\x40");
            DebugTextPrint(24, 108, 2, "\x82\x6c\x82\x6e\x82\x75\x82\x68\x82\x64\x82\x52\x81\x40\x81\x40");
            DebugTextPrint(24, 124, 2, "\x82\x6c\x82\x6e\x82\x75\x82\x68\x82\x64\x82\x53\x81\x40\x81\x40");
            DebugTextPrint(24, 140, 2, "\x82\x6c\x82\x6e\x82\x75\x82\x68\x82\x64\x82\x54\x81\x40\x81\x40");
            break;
#endif
        }
    }

    if (GetKeysPressed() & SELECT_BUTTON) {
        ModeRequest(&gModeDebflag, 0);
    }

    DebugTextDraw(0);
    DebugTextClear();
    gfx = AnimUpdate(&sDebugWork->anim);
    DrawSprite(9, sDebugWork->cursor % 9 * 16 + 13, gfx, sDebugWork->tiles,
               sDebugWork->palette, NULL, 0, 0);
}

void mode_debug_2() {
    DebugTextDestroy();
    ReleaseObjTiles(sDebugWork->tiles);
    ReleaseObjPalette(sDebugWork->palette);
    EwramFree(sDebugWork);
}

Mode gModeDebug = { "mode_debug", mode_debug_0, mode_debug_1, mode_debug_2 };
