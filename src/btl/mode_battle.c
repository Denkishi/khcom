#include "mode_battle.h"
#include "sprites_language_select.h"
#include "malloc.h"
#include "fade.h"
#include "songs.h"
#include "gba/keys.h"
#include "battle_actor.h"
#include "battle_bounds.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "display.h"
#include "formation_data.h"
#include "game_state.h"
#include "gba/macro.h"
#include "gba/syscall.h"
#include "key.h"
#include "m4a_song.h"
#include "mode.h"
#include "mode_chkbtl_api.h"
#include "obj_api.h"
#include "registration_data.h"
#include "save_api.h"
#include <stddef.h>
#include "system_state.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"

#ifdef VERSION_EU
LangWork* gLangWork;

void eu_08009CD0(s32 arg) {
    gLangWork = EwramAlloc(sizeof(LangWork));
    SetBgMode0();
    SetupBg(0, 0, 29, 0);
    SetupBg(1, 0, 30, 0);
    SetBgPriority(0, 0);
    SetBgPriority(1, 1);
    LoadBgPalette(0, gUnkEu_08F6A6FC, 0x40);
    eu_080059D4(0, gUnkEu_08F77180);
    eu_080059F4(0, gUnkEu_08F7EFB0);
    eu_080059F4(1, gUnkEu_08F7EBF8);
    gLangWork->tiles = LoadObjTiles(gUnkEu_08C9CA58, 0x1A0);
    gLangWork->palette = LoadObjPalette(gUnkEu_08F6A6DC, 32);
    gLangWork->timer = 0;
    gLangWork->state = 0;
    gLangWork->flags = 0;
    SaveLoadHeader();

    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        gLangWork->cursor = 0;
        break;
    case LANGUAGE_ITALIAN:
        gLangWork->cursor = 1;
        break;
    case LANGUAGE_FRENCH:
        gLangWork->cursor = 2;
        break;
    case LANGUAGE_SPANISH:
        gLangWork->cursor = 3;
        break;
    case LANGUAGE_GERMAN:
        gLangWork->cursor = 4;
        break;
    default:
        gLanguage = LANGUAGE_ENGLISH;
        gLangWork->cursor = 0;
        break;
    }

    gLangWork->language = gLanguage;
    FadeStartIn(FADE_MODE_BLACK, 16);
}

void eu_08009E10() {
    switch (gLangWork->state) {
    case 0:
        if (!FadeIsActive()) {
            gLangWork->state = 1;
        }

        break;
    case 1:
        if (GetKeysRepeat() & DPAD_UP) {
            gLangWork->cursor--;

            if (gLangWork->cursor < 0) {
                gLangWork->cursor = 4;
            }

            m4aSongNumStart(SONG_SYS_CLICK);
        } else if (GetKeysRepeat() & DPAD_DOWN) {
            gLangWork->cursor++;

            if (gLangWork->cursor > 4) {
                gLangWork->cursor = 0;
            }

            m4aSongNumStart(SONG_SYS_CLICK);
        } else if (GetKeysPressed() & A_BUTTON) {
            gLangWork->timer = 0;
            gLangWork->state = 2;
            m4aSongNumStart(SONG_SYS_KETTEI);
        } else if (GetKeysPressed() & B_BUTTON) {
            gLangWork->state = 3;
            m4aSongNumStart(SONG_SYS_CANSEL);
        }

        break;
    case 2:
        if (gLangWork->timer == 0) {
            switch (gLangWork->cursor) {
            case 0:
                gLanguage = LANGUAGE_ENGLISH;
                break;
            case 1:
                gLanguage = LANGUAGE_ITALIAN;
                break;
            case 2:
                gLanguage = LANGUAGE_FRENCH;
                break;
            case 3:
                gLanguage = LANGUAGE_SPANISH;
                break;
            case 4:
                gLanguage = LANGUAGE_GERMAN;
                break;
            default:
                gLanguage = LANGUAGE_ENGLISH;
                break;
            }

            if (gLangWork->language != gLanguage) {
                SaveWriteHeader(-1);
            }
        }

        if (gLangWork->timer % 4 < 2) {
            gLangWork->flags &= ~LANG_FLAG_HIDE_CURSOR;
        } else {
            gLangWork->flags |= LANG_FLAG_HIDE_CURSOR;
        }

        if (gLangWork->timer > 29) {
            gLangWork->flags &= ~LANG_FLAG_HIDE_CURSOR;
            gLangWork->state = 3;
            gLangWork->timer = 0;
        } else {
            gLangWork->timer++;
        }

        break;
    case 3:
        if (gLangWork->timer == 0) {
            FadeStartOut(FADE_MODE_BLACK, 16);
        }

        if (!FadeIsActive()) {
            ModeRequest(&gModeCopyright1, 0);
        } else {
            gLangWork->timer++;
        }

        break;
    }

    if (!(gLangWork->flags & LANG_FLAG_HIDE_CURSOR)) {
        switch (gLangWork->cursor) {
        case 0:
            DrawSprite(0x60, 0x58, gUnkEu_08C9C97C, gLangWork->tiles, gLangWork->palette, NULL, 0, 0);
            break;
        case 1:
            DrawSprite(0x60, 0x68, gUnkEu_08C9C99E, gLangWork->tiles, gLangWork->palette, NULL, 0, 0);
            break;
        case 2:
            DrawSprite(0x60, 0x78, gUnkEu_08C9C9C0, gLangWork->tiles, gLangWork->palette, NULL, 0, 0);
            break;
        case 3:
            DrawSprite(0x60, 0x88, gUnkEu_08C9C9E2, gLangWork->tiles, gLangWork->palette, NULL, 0, 0);
            break;
        case 4:
            DrawSprite(0x60, 0x98, gUnkEu_08C9CA04, gLangWork->tiles, gLangWork->palette, NULL, 0, 0);
            break;
        }
    }
}

void eu_0800A0DC() {
    ReleaseObjTiles(gLangWork->tiles);
    ReleaseObjPalette(gLangWork->palette);
    EwramFree(gLangWork);
}
#endif

void mode_battle_0(u32 mode) {
    BtlWork** p;

    gBtlWork = EwramAlloc(sizeof(BtlWork));
    gRikuBtlWork = NULL;
    BtlWorkInit();
    AllocBattleTiles();
    gBtlWork->battleId = mode;
    gGameState.flags &= ~GAME_FLAG_BATTLE_NOT_WON;

    switch (mode) {
    case 0x94 ... 0x9C:
        gBtlWork->flags |= BTL_FLAG_BOSS_BATTLE;
        break;
    case 0xB2 ... 0xB8:
        gBtlWork->flags |= BTL_FLAG_TUTORIAL;
    case 0x9D ... 0xB1:
        gBtlWork->flags |= BTL_FLAG_HUM_BATTLE;
        p = &gRikuBtlWork;
        *p = EwramAlloc(sizeof(BtlWork));
        CpuFill32(0, gRikuBtlWork, sizeof(BtlWork));
        break;
    }

    if (gBtlWork->flags & BTL_FLAG_BOSS_BATTLE) {
        SetBgMode1();

        switch (mode) {
        case 0x9C:
            m4aSongNumStart(SONG_BGM_LASTBOSS2);
            break;
        case 0x95:
        case 0x97:
        case 0x99:
        case 0x9B:
            m4aSongNumStart(SONG_BGM_BOSSWORLD);
            break;
        case 0x94:
        case 0x96:
        case 0x98:
        case 0x9A:
        default:
            m4aSongNumStart(SONG_BGM_BOSS1_WORLD);
            break;
        }

        gBtlWork->bg = 2;

        switch (mode) {
        case 0x98:
        case 0x9C:
            SetupBg(0, 0, 22, 0);
            SetupBg(1, 0, 24, 0);
            SetupBg(2, 2, 28, 10);
            SetBgPriority(0, 2);
            SetBgPriority(2, 0);
            SetBgPriority(1, 1);
            SetBgOverflow(2, 0);
            SetBgSize(1, 0x4000);
            break;
        case 0x94:
        case 0x95:
        case 0x96:
        case 0x97:
        case 0x99:
        case 0x9A:
        case 0x9B:
        default:
            SetupBg(0, 0, 24, 0);
            SetupBg(1, 0, 26, 0);
            SetupBg(2, 2, 28, 10);
            SetBgPriority(0, 2);
            SetBgPriority(2, 0);
            SetBgPriority(1, 1);
            SetBgOverflow(2, 0);
            break;
        }
    } else if (gBtlWork->flags & BTL_FLAG_TUTORIAL) {
        m4aSongNumStart(SONG_BGM_EVENT2);
        gBtlWork->bg = 3;
        gBtlWork->mapBg = 2;
        SetBgMode2();
        SetupBg(gBtlWork->mapBg, 0, 12, 0);
        SetupBg(gBtlWork->bg, 2, 28, 10);
        SetBgPriority(gBtlWork->mapBg, 2);
        SetBgPriority(gBtlWork->bg, 0);
        SetBgOverflow(gBtlWork->mapBg, 1);
        SetBgOverflow(gBtlWork->bg, 0);
    } else if (gBtlWork->flags & BTL_FLAG_HUM_BATTLE) {
        gBtlWork->bg = 2;
        gBtlWork->mapBg = 3;

        switch (mode) {
        case 0xA1:
        case 0xA8 ... 0xAC:
            m4aSongNumStart(SONG_BGM_NISERIKU);
            break;
        case 0x9D:
        case 0x9F:
            m4aSongNumStart(SONG_BGM_EVENT2);
            break;
        case 0xA5:
            m4aSongNumStart(SONG_BGM_LASTBOSS1);
            break;
        case 0x9E:
        case 0xA0:
            m4aSongNumStart(SONG_BGM_BOSSWORLD);
            break;
        case 0xB1:
            m4aSongNumStart(SONG_BGM_RIKU_ANSEM);
            break;
        default:
            m4aSongNumStart(SONG_BGM_BOSS3_XIII);
            break;
        }

        SetBgMode2();
        SetupBg(3, 0, 12, 0);
        SetupBg(2, 2, 28, 10);
        SetBgPriority(3, 2);
        SetBgPriority(2, 0);
        SetBgOverflow(3, 1);
        SetBgOverflow(2, 0);
    } else {
        gBtlWork->bg = 2;
        gBtlWork->mapBg = 3;

        switch (gGameState.battleStage) {
        case BATTLE_STAGE_WONDERLAND:
        case 2:
            m4aSongNumStart(SONG_BGM_ALICE_BTL);
            break;
        case BATTLE_STAGE_AGRABAH:
            m4aSongNumStart(SONG_BGM_ALADDIN_BATTLE);
            break;
        case BATTLE_STAGE_ATLANTICA:
            m4aSongNumStart(SONG_BGM_MARMAID_BATTLE);
            break;
        case BATTLE_STAGE_MONSTRO:
            if (mode == 0x79) {
                m4aSongNumStart(SONG_BGM_EVENT2);
            } else {
                m4aSongNumStart(SONG_BGM_PINOCCHIO_BTL);
            }

            break;
        case BATTLE_STAGE_OLYMPUS_COLISEUM:
            m4aSongNumStart(SONG_BGM_HERCULES_BATTLE);
            break;
        case BATTLE_STAGE_HALLOWEEN_TOWN:
            m4aSongNumStart(SONG_BGM_HALLOWEEN_BTL);
            break;
        case BATTLE_STAGE_NEVER_LAND:
            m4aSongNumStart(SONG_BGM_PETERPAN_BTL);
            break;
        case BATTLE_STAGE_HOLLOW_BASTION:
            m4aSongNumStart(SONG_BGM_HOLLOW_BATTLE);
            break;
        case BATTLE_STAGE_TRAVERSE_TOWN:
            m4aSongNumStart(SONG_BGM_TOWN_BTL);
            break;
        case BATTLE_STAGE_DESTINY_ISLANDS:
            m4aSongNumStart(SONG_BGM_DESTINY_BATTLE);
            break;
        case BATTLE_STAGE_CASTLE_OBLIVION:
            m4aSongNumStart(SONG_BGM_F13F_FORGET_BATTLE);
            break;
        case BATTLE_STAGE_TWILIGHT_TOWN:
            m4aSongNumStart(SONG_BGM_TWILIGHT_BATTLE);
            break;
        }

        SetBgMode2();
        SetupBg(3, 0, 12, 0);
        SetupBg(2, 2, 28, 10);
        SetBgPriority(3, 2);
        SetBgPriority(2, 0);
        SetBgOverflow(3, 1);
        SetBgOverflow(2, 0);
    }

    TaskPoolInit(&gBtlWork->taskPools[0], 40);
    TaskPoolInit(&gBtlWork->taskPools[1], 32);
    TaskPoolInit(&gBtlWork->taskPools[2], 1);
    BgFxInit(0x80, gBtlWork->bg);
    ColliderPoolsInit();

    if (gGameState.flags & GAME_FLAG_RIKU) {
        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlRiku, NULL);
    } else {
        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlSora, NULL);
    }

    if (gBtlWork->flags & BTL_FLAG_BOSS_BATTLE) {
        gBtlWork->flags |= BTL_FLAG_NO_ENEMY_DROPS;

        switch (mode) {
        case 0x9A:
            SetBattleBounds(0, 0x100, 0x148, 0x1A8);
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBosDsd, NULL);
            gBtlWork->fadeAmount = 10;
            break;
        case 0x94:
            SetBattleBounds(-32, 0x120, 0x120, 0x180);
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBosGa, NULL);
            gBtlWork->fadeAmount = 5;
            break;
        case 0x99:
#ifdef VERSION_EU
            SetBattleBounds(0, 0xE0, 0x130, 0x180);
#else
            SetBattleBounds(0, 0xE0, 0x118, 0x180);
#endif
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBosMd, NULL);
            gBtlWork->fadeAmount = 5;
            break;
        case 0x96:
            SetBattleBounds(0x80, 0x180, 0x140, 0x180);
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBosTm, NULL);
            gBtlWork->fadeAmount = 12;
            break;
        case 0x97:
            SetBattleBounds(0, 0x200, 0, 0x200);
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBosUrsula, NULL);
            gBtlWork->fadeAmount = 5;
            break;
        case 0x98:
            SetBattleBounds(0x80, 0x1A8, 0x126, 0x180);
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBosPc, NULL);
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescPcAcddmg, gBtlWork->actor);
            gBtlWork->fadeAmount = 12;
            break;
        case 0x9C:
            SetBattleBounds(0x80, 0x170, 0x1E0, 0x200);
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBosLst, NULL);
            gBtlWork->fadeAmount = 10;
            break;
        case 0x9B:
            SetBattleBounds(0x80, 0x170, 0x228, 0x278);
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBosBoogie, NULL);
            gBtlWork->boundsCallback = &ClampBosBoogieBounds;
            gBtlWork->fadeAmount = 5;
            break;
        default:
            SetBattleBounds(0x1A4, 0x264, 0x148, 0x180);
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBosJf, NULL);
            gBtlWork->boundsCallback = &ClampBosJfBounds;
            gBtlWork->fadeAmount = 10;
            break;
        }
    } else if (gBtlWork->flags & BTL_FLAG_TUTORIAL) {
        SetBattleBounds(0x68, 0x198, 0x160, 0x1A2);

        if (mode == 0xB2) {
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumRobe, NULL);
            TaskCreate(&gBtlWork->taskPools[1], &gTaskDescTutorial, NULL);
        } else {
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumLeon, NULL);
            TaskCreate(&gBtlWork->taskPools[1], &gTaskDescTutorial, (void*)1);
        }

        gGameState.battleStage = BATTLE_STAGE_TRAVERSE_TOWN;
        TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlMap, NULL);
    } else if (gBtlWork->flags & BTL_FLAG_HUM_BATTLE) {
        gBtlWork->flags |= BTL_FLAG_NO_ENEMY_DROPS;

        switch (mode) {
        case 0x9E:
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumHook, NULL);
            SetBattleBounds(0x68, 0x198, 0x160, 0x1A2);
            break;
        case 0xA6:
        case 0xB1:
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumAnsem, NULL);
            SetBattleBounds(0x50, 0x1B0, 0x160, 0x1A2);
            break;
        case 0x9F:
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumCloud, NULL);
            SetBattleBounds(0x50, 0x1B0, 0x160, 0x1A2);
            break;
        case 0xA0:
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumHades, NULL);
            SetBattleBounds(0x50, 0x1B0, 0x160, 0x1A2);
            break;
        case 0xA5:
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumMahluxia, NULL);
            SetBattleBounds(0x50, 0x1B0, 0x160, 0x1A2);
            break;
        case 0xA3:
        case 0xAE:
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumLaxene, NULL);
            SetBattleBounds(0x50, 0x1B0, 0x160, 0x1A2);
            break;
        case 0xA2:
        case 0xAD:
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumAxcel, NULL);
            SetBattleBounds(0x50, 0x1B0, 0x160, 0x1A2);
            break;
        case 0xA4:
        case 0xAF:
        case 0xB0:
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumVixen, NULL);
            SetBattleBounds(0x50, 0x1B0, 0x160, 0x1A2);
            break;
        case 0xA7:
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumLexceus, NULL);
            SetBattleBounds(0x50, 0x1B0, 0x160, 0x1A2);
            break;
        case 0x9D:
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumLeon, NULL);
            SetBattleBounds(0x50, 0x1B0, 0x160, 0x1A2);
            break;
        default:
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumRiku, NULL);
            SetBattleBounds(0x50, 0x1B0, 0x160, 0x1A2);
            break;
        }

        TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlMap, NULL);
    } else {
        SetBattleBounds(0x68, 0x198, 0x160, 0x1A2);

        if (mode <= 0x92) {
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlForm, (void*)gBtlFormListByBattleId[mode]);
        } else if (gDebugFlags & DEBUG_FLAG_CHKBTL) {
            ChkBtlSpawnEnemy();
        }

        TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlMap, NULL);

        if (mode == 0x79) {
            gBtlWork->flags |= BTL_FLAG_NO_ENEMY_DROPS;
            gGameState.flags |= GAME_FLAG_MONSGAGE_BATTLE;
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescMonsgage, NULL);
        }
    }

    if (!(gBtlWork->flags & BTL_FLAG_TUTORIAL)) {
        TaskCreate(&gBtlWork->taskPools[2], &gTaskDescBtlPause, NULL);
    }

    FadeStartIn(FADE_MODE_BLACK, 60);
    gGameState.battleCount++;
}

void mode_battle_1() {
    TaskPoolUpdate(&gBtlWork->taskPools[2]);
    TaskPoolDraw(&gBtlWork->taskPools[2]);

    if (gBtlWork->freezeTimer > 0) {
        TaskPoolDraw(&gBtlWork->taskPools[1]);
        TaskPoolDraw(&gBtlWork->taskPools[0]);
        gBtlWork->freezeTimer--;
    } else {
        if (gBtlWork->paused == 0) {
            _08019CB4();

            if (gBtlWork->hitStop <= 0) {
                TaskPoolUpdate(&gBtlWork->taskPools[0]);
            } else {
                gBtlWork->hitStop--;
            }

            if (!(gBtlWork->flags & BTL_FLAG_BGFX_PAUSED)) {
                BgFxUpdate();
            }

            ColliderUpdateAll();
            TaskPoolDraw(&gBtlWork->taskPools[1]);

            if (gBtlWork->flags & BTL_FLAG_CARD_BREAK) {
                gBtlWork->flags &= ~BTL_FLAG_CARD_BREAK;
            }

            UpdatePlayTime();
        }

        if (!(gBtlWork->flags & BTL_FLAG_FIELD_HIDDEN)) {
            TaskPoolDraw(&gBtlWork->taskPools[0]);
        }
    }
}

void mode_battle_2() {
    gGameState.flags &= ~GAME_FLAG_FIRST_STRIKE;
    BgFxFree();
    TaskPoolDestroy(&gBtlWork->taskPools[2]);
    TaskPoolDestroy(&gBtlWork->taskPools[1]);
    TaskPoolDestroy(&gBtlWork->taskPools[0]);
    ReleaseBattleTiles();

    if (gBtlWork->flags & BTL_FLAG_HUM_BATTLE) {
        EwramFree(gRikuBtlWork);
    }

    EwramFree(gBtlWork);
}

#ifdef VERSION_EU
Mode gModeLang = { "mode_lang", eu_08009CD0, eu_08009E10, eu_0800A0DC };
#endif
Mode gModeBattle = { "mode_battle", (ModeInitFunc)mode_battle_0, mode_battle_1, mode_battle_2 };
