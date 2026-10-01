#include "macros.h"
#include "registration_data.h"
#include "title_api.h"
#include "map_api.h"
#include "task.h"
#include "system_state.h"
#include "sprites_title.h"
#include "game_state.h"
#include "gba/keys.h"
#include "gba/io_reg.h"
#include "mode_pooh_api.h"
#include "card_api.h"
#include "malloc.h"
#include "fade.h"
#include "songs.h"
#include "battle_actor.h"
#include "display.h"
#include "engine_math.h"
#include "gba/defines.h"
#include "intr.h"
#include "key.h"
#include "m4a.h"
#include "m4a_song.h"
#include "mode.h"
#include "mode_sio_api.h"
#include "save_api.h"
#include "save_types.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"

s32 gTitleBgScale EWRAM_COMMON(4);
s32 gTitleBgX EWRAM_COMMON(4);
s32 gTitleBgY EWRAM_COMMON(4);

static u32 sTitleState;
static TaskPool sTitleTaskPool;
static Task* sTitleMenuTask;
static Task* sTitleLogoTask;
static Task* sTitleObjTask;
static u16 sTitleTimer;
static s16 sTitleMenuChoice;
static u8* sTitlePaletteBuffer;
static u16 sTitleBlendStep;
static u8 sTitleCancelled;

void TitleCopyToPaletteBuffer(u16 a, void* b, u16 c) {
    RequestDma3Copy(b, sTitlePaletteBuffer + a * 32, c);
}

void TitleLoadPaletteBuffer() {
    LoadPalette(sTitlePaletteBuffer, (void*)PLTT, PLTT_SIZE);
}

void TitleExitToChoice() {
    if (sTitleCancelled != 0) {
        ModeRequest(&gModeTitle, 0);
        return;
    }

    switch (sTitleMenuChoice) {
    case 3:
        SaveLoadSystem();
        SaveClearSystem();
        RequestMapMode();
        return;
    case 1:
        ModeRequest(&gModeMenuLoad, 0);
        return;
    case 2:
        ClearSioBattleFileLoaded();
        ModeRequest(&gModeSioBattle, 0);
        return;
    case 4:
        SetupSoraNewGame();
        ModeRequest(&gModeMenuNew, 0);
        return;
    case 5:
        SetupRikuNewGame();
        ModeRequest(&gModeMenuNew, 0);
        return;
    case 0:
    default:
        ModeRequest(&gModeMenuNew, 0);
        return;
    }
}

void TitleShowLogo(u16 a) {
    if ((gGameState.flags & GAME_FLAG_RIKU_TITLE) != 0) {
        LoadBgPalette(1, gUnk_0984A818, 0x200);
        TitleCopyToPaletteBuffer(0, gUnk_0984A818, 0x200);
    } else {
        LoadBgPalette(1, gUnk_0984A418, 0x200);
        TitleCopyToPaletteBuffer(0, gUnk_0984A418, 0x200);
    }

    EnableBg(0);
    DisableBg(1);
    DisableBg(2);

    if (IsTaskActive(sTitleLogoTask) == 0) {
        sTitleLogoTask = TaskCreate(&sTitleTaskPool, &gTaskDescTitleLogo, NULL);
    }

    if (IsTaskActive(sTitleObjTask) == 0) {
        sTitleObjTask = TaskCreate(&sTitleTaskPool, &gTaskDescTitleObj, NULL);
    }

    FadeStartIn(FADE_MODE_ADD_WHITE, a);
}

void TitleFinishIntro() {
#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
    case LANGUAGE_FRENCH:
    case LANGUAGE_ITALIAN:
    case LANGUAGE_SPANISH:
    case 5:
    case 6:
#endif
        LoadBgMap(0, gUnk_0983F398, 0x800);
#ifdef VERSION_EU
        break;
    case LANGUAGE_GERMAN:
        LoadBgMap(0, gUnkEu_09814E40, 0x800);
        break;
    }
#endif

    SetBgBlend(0, 5, 16);
    EnableBg(1);
    m4aSongNumStart(SONG_BGM_TITLE);
}

void TitleFadeOut() {
    m4aMPlayFadeOut(gMPlayTable[gSongTable[6].ms].info, 5);
    FadeStartOut(FADE_MODE_BLACK, 90);
    BackdropFadeStartOut(0, 90);
    sTitleState = 9;
}

void mode_title_0() {
    sTitleCancelled = 0;
    ResetGameState();
    SaveLoadHeader();
    InitMapCardInventory();
    ResetSelectedMapCard();
    sTitleMenuChoice = 0;
    sTitlePaletteBuffer = EwramAlloc(0x400);
    SetBgMode1();
    SetupBg(0, 0, 0x1D, 0);
    SetBgPriority(0, 3);

    if (gGameState.flags & GAME_FLAG_RIKU_TITLE) {
#ifdef VERSION_EU
        LoadBgMapLz77(0, gUnk_09840798);
#else
        LoadBgMap(0, gUnk_09840798, 0x800);
#endif
    } else {
#ifdef VERSION_EU
        LoadBgMapLz77(0, gUnk_0983E398);
#else
        LoadBgMap(0, gUnk_0983E398, 0x800);
#endif
    }

    DisableBg(0);
    SetupBg(1, 0, 0x1E, 0);
    SetBgPriority(1, 3);

    if (gGameState.flags & GAME_FLAG_RIKU_TITLE) {
#ifdef VERSION_EU
        LoadBgTilesLz77(1, gUnk_097D3658);
        LoadBgMapLz77(1, gUnk_09840F98);
#else
        LoadBgTiles(1, gUnk_097D3658, 0x7FA0);
        LoadBgMap(1, gUnk_09840F98, 0x800);
#endif
    } else {
#ifdef VERSION_EU
        LoadBgTilesLz77(1, gUnk_097C77B8);
        LoadBgMapLz77(1, gUnk_0983EB98);
#else
        LoadBgTiles(1, gUnk_097C77B8, 0x7FA0);
        LoadBgMap(1, gUnk_0983EB98, 0x800);
#endif
    }

    DisableBg(1);
    BackdropFadeReset();
    BackdropFadeSetColor(0, 0, 0);
    SetupBg(2, 2, 0x1F, 0xB);
    SetBgSize(2, 0x4000);
    SetBgPriority(2, 2);
    LoadBgTiles(2, gUnk_097CF758, 0x3F00);
    LoadBgPalette(2, gUnk_0984A618, 0xA0);
    LoadBgMap(2, gUnk_0983FB98, 0x400);
    gTitleBgX = 0x7800;
    gTitleBgY = 0x5A00;
    gTitleBgScale = 0x1000;
    SetBgAffine(2, 0, gTitleBgScale >> 4, gTitleBgScale >> 4, gTitleBgX, gTitleBgY);
    TaskPoolInit(&sTitleTaskPool, 4);
    sTitleLogoTask = NULL;
    sTitleObjTask = NULL;
    FadeStartIn(FADE_MODE_BLACK, 0x4C);
    sTitleState = 0;
    m4aSongNumStart(SONG_SND_0);
    sTitleTimer = 0x1E;
}

void mode_title_1() {
    switch (sTitleState) {
    case 0:
        if (FadeIsActive()) {
            break;
        }

        if (sTitleTimer != 0) {
            sTitleTimer--;

            if (sTitleTimer != 0) {
                break;
            }
        }

        sTitleState = 1;
        sTitleTimer = 100;
        break;
    case 1:
        if (gGameState.flags & GAME_FLAG_RIKU_TITLE) {
            ApproachValue(&gTitleBgX, 0x3F3F, sTitleTimer);
        } else {
            ApproachValue(&gTitleBgX, 0xB0C1, sTitleTimer);
        }

        ApproachValue(&gTitleBgY, 0x6A37, sTitleTimer);
        ApproachValue(&gTitleBgScale, 0xBD0, sTitleTimer);
        SetBgAffine(2, 0, gTitleBgScale / 16, gTitleBgScale / 16, gTitleBgX, gTitleBgY);
        sTitleTimer--;

        if (sTitleTimer == 0x46) {
            BackdropFadeStartOut(1, 0x46);

            if (sTitleTimer == 0x46) {
                FadeStartOut(FADE_MODE_WHITE, 0x46);
            }
        }

        if (sTitleTimer == 0) {
            sTitleState = 2;
            sTitleTimer = 2;
        }

        break;
    case 2:
        if (FadeIsActive()) {
            break;
        }

        sTitleTimer--;

        if (sTitleTimer != 0) {
            break;
        }

        TitleShowLogo(15);
        sTitleState = 3;
        sTitleTimer = 0x28;
        break;
    case 3:
        if (FadeIsActive()) {
            break;
        }

        if (sTitleTimer != 0) {
            sTitleTimer--;
            break;
        }

        sTitleState = 4;
        sTitleBlendStep = 0;
        gBldCnt = (BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG1 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_OBJ);
        gBldAlpha = BLDALPHA_BLEND(16, 0);
        sTitleTimer = 4;
        EnableBg(1);
        break;
    case 4:
        if (sTitleTimer != 0) {
            sTitleTimer--;
            break;
        }

        sTitleTimer = 4;
        sTitleBlendStep++;
        gBldAlpha = (sTitleBlendStep << 8) | (16 - sTitleBlendStep);

        if (sTitleBlendStep > 15) {
            gBldCnt = 0;
            TitleFinishIntro();
            sTitleState = 5;
        }

        break;
    case 5:
        if (!IsTitleObjSlideDone()) {
            break;
        }

        if (!(GetKeysPressed() & START_BUTTON) && !(GetKeysPressed() & A_BUTTON)) {
            break;
        }

        m4aSongNumStart(SONG_SYS_KETTEI);

        if (SaveRepairSystem() == SAVE_OK) {
            sTitleMenuChoice = 3;
        } else if (SaveRepairFileLarge(0) == SAVE_OK || SaveRepairFileLarge(1) == SAVE_OK) {
            sTitleMenuChoice = 1;
        } else if ((gGameState.flags & GAME_FLAG_SORA_CLEAR) &&
                   (SaveRepairFileSmall(0) == SAVE_OK || SaveRepairFileSmall(1) == SAVE_OK)) {
            sTitleMenuChoice = 1;
        } else {
            sTitleMenuChoice = 0;
        }

        TaskKill(&sTitleTaskPool, sTitleLogoTask);
        TaskKill(&sTitleTaskPool, sTitleObjTask);
        sTitleMenuTask = TaskCreate(&sTitleTaskPool, &gTaskDescTitleMenu, &sTitleMenuChoice);
        DisableBg(0);
        sTitleState = 6;
        sTitleBlendStep = 0;
        gBldCnt = (BLDCNT_TGT1_OBJ | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG1);
        gBldAlpha = ((16 - sTitleBlendStep) << 8) | sTitleBlendStep;
        sTitleTimer = 4;
        break;
    case 6:
        if (sTitleTimer != 0) {
            sTitleTimer--;
            break;
        }

        sTitleTimer = 4;
        sTitleBlendStep++;
        gBldAlpha = ((16 - sTitleBlendStep) << 8) | sTitleBlendStep;

        if (sTitleBlendStep > 15) {
            gBldCnt = 0;
            sTitleState = 8;
        }

        break;
    case 7:
        if (sTitleTimer != 0) {
            sTitleTimer--;
            break;
        }

        sTitleTimer = 1;
        sTitleBlendStep--;
        gBldAlpha = ((16 - sTitleBlendStep) << 8) | sTitleBlendStep;

        if (sTitleBlendStep > 15) {
            gBldCnt = 0;
            TaskKill(&sTitleTaskPool, sTitleMenuTask);
            sTitleLogoTask = TaskCreate(&sTitleTaskPool, &gTaskDescTitleLogo, NULL);
            sTitleObjTask = TaskCreate(&sTitleTaskPool, &gTaskDescTitleObj, NULL);
            EnableBg(0);
            sTitleState = 5;
        }

        break;
    case 8:
        if ((GetKeysPressed() & START_BUTTON) || (GetKeysPressed() & A_BUTTON)) {
            switch (sTitleMenuChoice) {
            case 0:
            case 4:
            case 5:
                m4aSongNumStart(SONG_SYS_START);
                break;
            default:
                m4aSongNumStart(SONG_SYS_KETTEI);
                break;
            }

            TitleFadeOut();
        } else if (GetKeysPressed() & B_BUTTON) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            sTitleCancelled = 1;
            TitleFadeOut();
        }

        break;
    case 9:
        if (!FadeIsActive()) {
            TitleExitToChoice();
        }

        break;
    }

    if (!FadeIsActive() && sTitleState != 6) {
        TaskPoolUpdate(&sTitleTaskPool);
    }

    TaskPoolDraw(&sTitleTaskPool);
    BackdropFadeUpdate();

    if (sTitleState <= 4 && (GetKeysPressed() & (A_BUTTON | START_BUTTON))) {
        m4aSongNumStart(SONG_SYS_CLICK);

        if (sTitleState <= 3) {
            TitleShowLogo(2);
        }

        TitleFinishIntro();
        sTitleState = 5;
    }
}

void mode_title_2() {
    TaskPoolDestroy(&sTitleTaskPool);
    REG_IME = 0;
    REG_IE &= ~INTR_FLAG_VCOUNT;
    REG_DISPSTAT &= ~DISPSTAT_VCOUNT_INTR;
    REG_IME = 1;
    ResetVCountCallback();
    EwramFree(sTitlePaletteBuffer);
}

u8 IsTitleLogoShown() {
    if (sTitleState > 2) {
        return 1;
    }

    return 0;
}

u8 IsTitleIntroDone() {
    if (sTitleState > 4) {
        return 1;
    }

    return 0;
}

Mode gModeTitle = {
    "mode_title",
    (ModeInitFunc)mode_title_0,
    mode_title_1,
    mode_title_2,
};
