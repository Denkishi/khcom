/**
 * mode_copyright1.c
 * Copyright Screen and Save Data Check
 */

#include "registration_data.h"
#include "copyright_screens.h"
#include "fade.h"
#include "songs.h"
#include "display.h"
#include "m4a_song.h"
#include "mode.h"
#include "save_api.h"
#include "save_types.h"
#include "types.h"

#ifndef VERSION_JP
static u8 sCopyrightExtraScreen;
#endif
static u16 sCopyright1Timer;
static u8 sCopyrightSaveCorrupted;
#ifndef VERSION_JP
static u16 sUnk_02034EDA;
#endif

void mode_copyright1_0(s32 arg) {
#ifndef VERSION_JP
    if (arg == 0) {
        sCopyrightExtraScreen = TRUE;
    } else {
        sCopyrightExtraScreen = FALSE;
    }
#endif

    sCopyrightSaveCorrupted = FALSE;

    if (SaveRepairHeader() == SAVE_BAD_CHECKSUM) {
        sCopyrightSaveCorrupted = TRUE;
        SaveClearHeader();
        SaveClearSystem();
        SaveClearFileLarge(0);
        SaveClearFileLarge(1);
        SaveClearFileSmall(0);
        SaveClearFileSmall(1);
    }

    if (SaveRepairFileLarge(0) == SAVE_BAD_CHECKSUM) {
        sCopyrightSaveCorrupted = TRUE;
        SaveClearFileLarge(0);
    }

    if (SaveRepairFileLarge(1) == SAVE_BAD_CHECKSUM) {
        sCopyrightSaveCorrupted = TRUE;
        SaveClearFileLarge(1);
    }

    if (SaveRepairFileSmall(0) == SAVE_BAD_CHECKSUM) {
        sCopyrightSaveCorrupted = TRUE;
        SaveClearFileSmall(0);
    }

    if (SaveRepairFileSmall(1) == SAVE_BAD_CHECKSUM) {
        sCopyrightSaveCorrupted = TRUE;
        SaveClearFileSmall(1);
    }

    if (SaveRepairSystem() == SAVE_BAD_CHECKSUM) {
        sCopyrightSaveCorrupted = TRUE;
        SaveClearSystem();
    }

    m4aSongNumStart(SONG_SND_0);
    SetBgMode0();
    SetupBg(0, 0, 0x1F, 0);
    SetBgPriority(0, 3);

#ifndef VERSION_JP
    if (sCopyrightExtraScreen) {
#ifdef VERSION_EU
        LoadBgTiles(0, gCopyrightNintendoTiles, 0x7A0);
        LoadBgPalette(0, gCopyrightNintendoPalette, 0x20);
#else
        LoadBgTiles(0, gCopyrightNintendoTiles, 0x4FC0);
        LoadBgPalette(0, gCopyrightNintendoPalette, 0x1C0);
#endif
        LoadBgMap(0, gCopyrightNintendoMap, 0x800);
    } else
#endif
    {
        LoadBgTiles(0, gCopyright1Tiles, 0x4FC0);
        LoadBgPalette(0, gCopyright1Palette, 0x200);
        LoadBgMap(0, gCopyright1Map, 0x800);
    }

    FadeStartIn(FADE_MODE_WHITE, 0x43);
    sCopyright1Timer = 60;
}

void mode_copyright1_1() {
    if (sCopyrightSaveCorrupted) {
        ModeRequest(&gModeMenuMsg, 0);
    } else if (!FadeIsActive()) {
        if (sCopyright1Timer != 0) {
            if (--sCopyright1Timer == 0) {
                FadeStartOut(FADE_MODE_WHITE, 0x43);
            }
        } else
#ifndef VERSION_JP
        if (sCopyrightExtraScreen) {
            ModeRequest(&gModeCopyright1, 1);
        } else
#endif
        {
            ModeRequest(&gModeCopyright2, 1);
        }
    }
}

void mode_copyright1_2() {
}

Mode gModeCopyright1 = {
    "mode_copyright1",
    mode_copyright1_0,
    mode_copyright1_1,
    mode_copyright1_2,
};
