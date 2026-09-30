#include "macros.h"
#include "registration_data.h"
#include "title_api.h"
#include "map_api.h"
#include "task.h"
#include "system_state.h"
#include "mode_title.h"
#include "sprites_title.h"
#include "game_state.h"
#include "title_types.h"
#include "gba/keys.h"
#include "gba/io_reg.h"
#include "mode_pooh_api.h"
#include "card_api.h"
#include "malloc.h"
#include "fade.h"
#include "songs.h"

s32 gTitleBgScale EWRAM_COMMON(4);
s32 gTitleBgX EWRAM_COMMON(4);
s32 gTitleBgY EWRAM_COMMON(4);

u32 gTitleState;
u32 gUnk_02034E9C;
TaskPool gTitleTaskPool __attribute__((aligned(8)));
Task* gTitleMenuTask;
Task* gTitleLogoTask;
Task* gTitleObjTask;
u16 gTitleTimer;
s16 gTitleMenuChoice;
u8* gTitlePaletteBuffer;
u16 gTitleBlendStep;
u8 gTitleCancelled;
u8 gUnk_02034ECB;
u8 gTitleLogoScaleDone;

void TitleCopyToPaletteBuffer(u16 a, void* b, u16 c) {
    RequestDma3Copy(b, gTitlePaletteBuffer + a * 32, c);
}

void TitleLoadPaletteBuffer(void) {
    LoadPalette(gTitlePaletteBuffer, (void*)0x05000000, 0x400);
}

void TitleExitToChoice(void) {
    if (gTitleCancelled != 0) {
        ModeRequest(&gModeTitle, 0);
        return;
    }

    switch (gTitleMenuChoice) {
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

    if (IsTaskActive(gTitleLogoTask) == 0) {
        gTitleLogoTask = TaskCreate(&gTitleTaskPool, &gTaskDescTitleLogo, 0);
    }

    if (IsTaskActive(gTitleObjTask) == 0) {
        gTitleObjTask = TaskCreate(&gTitleTaskPool, &gTaskDescTitleObj, 0);
    }
    FadeStartIn(2, a);
}

void TitleFinishIntro(void) {
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

void TitleFadeOut(void) {
    m4aMPlayFadeOut(gMPlayTable[gSongTable[6].ms].info, 5);
    FadeStartOut(0, 90);
    BackdropFadeStartOut(0, 90);
    gTitleState = 9;
}

void mode_title_0(void) {
    gTitleCancelled = 0;
    ResetGameState();
    SaveLoadHeader();
    InitMapCardInventory();
    ResetSelectedMapCard();
    gTitleMenuChoice = 0;
    gTitlePaletteBuffer = EwramAlloc(0x400);
    SetBgMode1();
    SetupBg(0, 0, 0x1D, 0);
    SetBgPriority(0, 3);

    if (gGameState.flags & GAME_FLAG_RIKU_TITLE) {
#ifdef VERSION_EU
        eu_080059F4(0, gUnk_09840798);
#else
        LoadBgMap(0, gUnk_09840798, 0x800);
#endif
    } else {
#ifdef VERSION_EU
        eu_080059F4(0, gUnk_0983E398);
#else
        LoadBgMap(0, gUnk_0983E398, 0x800);
#endif
    }
    DisableBg(0);
    SetupBg(1, 0, 0x1E, 0);
    SetBgPriority(1, 3);

    if (gGameState.flags & GAME_FLAG_RIKU_TITLE) {
#ifdef VERSION_EU
        eu_080059D4(1, gUnk_097D3658);
        eu_080059F4(1, gUnk_09840F98);
#else
        LoadBgTiles(1, gUnk_097D3658, 0x7FA0);
        LoadBgMap(1, gUnk_09840F98, 0x800);
#endif
    } else {
#ifdef VERSION_EU
        eu_080059D4(1, gUnk_097C77B8);
        eu_080059F4(1, gUnk_0983EB98);
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
    TaskPoolInit(&gTitleTaskPool, 4);
    gTitleLogoTask = 0;
    gTitleObjTask = 0;
    FadeStartIn(0, 0x4C);
    gTitleState = 0;
    m4aSongNumStart(SONG_SND_0);
    gTitleTimer = 0x1E;
}

void mode_title_1(void) {
    switch (gTitleState) {
    case 0:
        if (FadeIsActive()) {
            break;
        }

        if (gTitleTimer != 0) {
            gTitleTimer--;
            if (gTitleTimer != 0) {
                break;
            }
        }
        gTitleState = 1;
        gTitleTimer = 100;
        break;
    case 1:
        if (gGameState.flags & GAME_FLAG_RIKU_TITLE) {
            ApproachValue(&gTitleBgX, 0x3F3F, gTitleTimer);
        } else {
            ApproachValue(&gTitleBgX, 0xB0C1, gTitleTimer);
        }
        ApproachValue(&gTitleBgY, 0x6A37, gTitleTimer);
        ApproachValue(&gTitleBgScale, 0xBD0, gTitleTimer);
        SetBgAffine(2, 0, gTitleBgScale / 16, gTitleBgScale / 16, gTitleBgX, gTitleBgY);
        gTitleTimer--;
        if (gTitleTimer == 0x46) {
            BackdropFadeStartOut(1, 0x46);

            if (gTitleTimer == 0x46) {
                FadeStartOut(1, 0x46);
            }
        }

        if (gTitleTimer == 0) {
            gTitleState = 2;
            gTitleTimer = 2;
        }
        break;
    case 2:
        if (FadeIsActive()) {
            break;
        }
        gTitleTimer--;
        if (gTitleTimer != 0) {
            break;
        }
        TitleShowLogo(15);
        gTitleState = 3;
        gTitleTimer = 0x28;
        break;
    case 3:
        if (FadeIsActive()) {
            break;
        }

        if (gTitleTimer != 0) {
            gTitleTimer--;
            break;
        }
        gTitleState = 4;
        gTitleBlendStep = 0;
        gBldCnt = (BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG1 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_OBJ);
        gBldAlpha = BLDALPHA_BLEND(16, 0);
        gTitleTimer = 4;
        EnableBg(1);
        break;
    case 4:
        if (gTitleTimer != 0) {
            gTitleTimer--;
            break;
        }
        gTitleTimer = 4;
        gTitleBlendStep++;
        gBldAlpha = (gTitleBlendStep << 8) | (16 - gTitleBlendStep);

        if (gTitleBlendStep > 15) {
            gBldCnt = 0;
            TitleFinishIntro();
            gTitleState = 5;
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
            gTitleMenuChoice = 3;
        } else if (SaveRepairFileLarge(0) == SAVE_OK || SaveRepairFileLarge(1) == SAVE_OK) {
            gTitleMenuChoice = 1;
        } else if ((gGameState.flags & GAME_FLAG_SORA_CLEAR) &&
                   (SaveRepairFileSmall(0) == SAVE_OK || SaveRepairFileSmall(1) == SAVE_OK)) {
            gTitleMenuChoice = 1;
        } else {
            gTitleMenuChoice = 0;
        }
        TaskKill(&gTitleTaskPool, gTitleLogoTask);
        TaskKill(&gTitleTaskPool, gTitleObjTask);
        gTitleMenuTask = TaskCreate(&gTitleTaskPool, &gTaskDescTitleMenu, &gTitleMenuChoice);
        DisableBg(0);
        gTitleState = 6;
        gTitleBlendStep = 0;
        gBldCnt = (BLDCNT_TGT1_OBJ | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG1);
        gBldAlpha = ((16 - gTitleBlendStep) << 8) | gTitleBlendStep;
        gTitleTimer = 4;
        break;
    case 6:
        if (gTitleTimer != 0) {
            gTitleTimer--;
            break;
        }
        gTitleTimer = 4;
        gTitleBlendStep++;
        gBldAlpha = ((16 - gTitleBlendStep) << 8) | gTitleBlendStep;

        if (gTitleBlendStep > 15) {
            gBldCnt = 0;
            gTitleState = 8;
        }
        break;
    case 7:
        if (gTitleTimer != 0) {
            gTitleTimer--;
            break;
        }
        gTitleTimer = 1;
        gTitleBlendStep--;
        gBldAlpha = ((16 - gTitleBlendStep) << 8) | gTitleBlendStep;

        if (gTitleBlendStep > 15) {
            gBldCnt = 0;
            TaskKill(&gTitleTaskPool, gTitleMenuTask);
            gTitleLogoTask = TaskCreate(&gTitleTaskPool, &gTaskDescTitleLogo, 0);
            gTitleObjTask = TaskCreate(&gTitleTaskPool, &gTaskDescTitleObj, 0);
            EnableBg(0);
            gTitleState = 5;
        }
        break;
    case 8:
        if ((GetKeysPressed() & START_BUTTON) || (GetKeysPressed() & A_BUTTON)) {
            switch (gTitleMenuChoice) {
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
            gTitleCancelled = 1;
            TitleFadeOut();
        }
        break;
    case 9:
        if (!FadeIsActive()) {
            TitleExitToChoice();
        }
        break;
    }

    if (!FadeIsActive() && gTitleState != 6) {
        TaskPoolUpdate(&gTitleTaskPool);
    }
    TaskPoolDraw(&gTitleTaskPool);
    BackdropFadeUpdate();

    if (gTitleState <= 4 && (GetKeysPressed() & (A_BUTTON | START_BUTTON))) {
        m4aSongNumStart(SONG_SYS_CLICK);

        if (gTitleState <= 3) {
            TitleShowLogo(2);
        }
        TitleFinishIntro();
        gTitleState = 5;
    }
}

void mode_title_2(void) {
    TaskPoolDestroy(&gTitleTaskPool);
    REG_IME = 0;
    REG_IE &= ~INTR_FLAG_VCOUNT;
    REG_DISPSTAT &= ~DISPSTAT_VCOUNT_INTR;
    REG_IME = 1;
    ResetVCountCallback();
    EwramFree(gTitlePaletteBuffer);
}

u8 IsTitleLogoShown(void) {
    if (gTitleState > 2) {
        return 1;
    }
    return 0;
}

u8 IsTitleIntroDone(void) {
    if (gTitleState > 4) {
        return 1;
    }
    return 0;
}

void TitleLogoLoadSprites(TitleLogoWork* work) {
    work->sprites[0].tiles = LoadObjTiles(gUnk_0976E9F4, 0x240);
    work->sprites[0].gfx = gUnk_09EF659C;

    if (gGameState.flags & GAME_FLAG_RIKU_TITLE) {
        work->sprites[1].tiles = LoadObjTiles(gUnk_09776076, 0x43C0);
        work->sprites[1].gfx = gUnk_09EF669C;
        work->sprites[1].palette = LoadObjPalette(gUnk_0984AA18, 0x20);
    } else {
        work->sprites[1].tiles = LoadObjTiles(gUnk_0976EC54, 0xE0);
        work->sprites[1].gfx = gUnk_09EF65A4;
        work->sprites[1].palette = LoadObjPalette(gUnk_0984A6D8, 0x20);
    }
    work->sprites[2].tiles = LoadObjTiles(gUnk_0976ED5A, 0x380);
    work->sprites[2].gfx = gUnk_09EF65AC;
    work->sprites[3].tiles = LoadObjTiles(gUnk_0976F0F6, 0xC0);
    work->sprites[3].gfx = gUnk_09EF65B4;
    work->sprites[4].tiles = LoadObjTiles(gUnk_0976F1F0, 0xAC0);
    work->sprites[4].gfx = gUnk_09EF65BC;
    work->sprites[5].tiles = LoadObjTiles(gUnk_0976FD96, 0x1140);
    work->sprites[5].gfx = gUnk_09EF65C4;
    work->sprites[0].palette = LoadObjPalette(gUnk_0984A6B8, 0x20);
    work->sprites[2].palette = LoadObjPalette(gUnk_0984A6F8, 0x20);
    work->sprites[3].palette = LoadObjPalette(gUnk_0984A6F8, 0x20);
    work->sprites[4].palette = LoadObjPalette(gUnk_0984A718, 0x20);
    work->sprites[5].palette = LoadObjPalette(gUnk_0984A738, 0x20);
    work->scale = 0;
    work->unk_48 = 0xC00;
    work->unk_50 = 0;
    gTitleLogoScaleDone = 0;
}

Mode gModeTitle = {
    "mode_title",
    (ModeInitFunc)mode_title_0,
    mode_title_1,
    mode_title_2,
};
