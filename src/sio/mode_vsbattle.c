#include "macros.h"
#include "mode_vsbattle.h"
#include "chara_types.h"
#include "malloc.h"
#include "fade.h"
#include "songs.h"
#include "mode_sio_api.h"
#include "sio_api.h"

u8 gUnk_02039B98 EWRAM_COMMON(4);

void mode_vsbattle_0(u32 mode) {
    VsTaskArg arg;
    VsTaskArg arg2;
    BtlWork** p;

    gBtlWork = EwramAlloc(sizeof(BtlWork));
    p = &gRikuBtlWork;
    *p = EwramAlloc(sizeof(BtlWork));

    if (gSioPlayerId == 0) {
        SeedRandom(gCharaLinkSend.seed);
    } else {
        SeedRandom(gCharaLinkRecv.seed);
    }

    VsBtlWorkInit();
    AllocBattleTiles();
    PlayVsBattleBgm();
    SetBgMode2();
    gBtlWork->bg = 2;
    gBtlWork->mapBg = 3;
    SetupBg(3, 0, 12, 0);
    SetupBg(2, 2, 28, 10);
    SetBgPriority(3, 2);
    SetBgPriority(2, 0);
    SetBgOverflow(3, 1);
    SetBgOverflow(2, 0);
    TaskPoolInit(&gBtlWork->taskPools[0], 32);
    TaskPoolInit(&gBtlWork->taskPools[1], 32);
    BgFxInit(0x80, gBtlWork->bg);
    ColliderPoolsInit();

    if (mode == 0) {
        arg.mainSide = 1;
        arg.side = 0;
        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlSora, &arg);
        arg.mainSide = 0;
        arg.side = 1;
        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlSora, &arg);
        gBtlWork->flags |= BTL_FLAG_VS_LINK_PARENT;
    } else {
        arg2.mainSide = 0;
        arg2.side = 0;
        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlSora, &arg2);
        arg2.mainSide = 1;
        arg2.side = 1;
        TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlSora, &arg2);
    }

    SetBattleBounds((s16)(0x100 - gVsBattleHalfWidth), (s16)(gVsBattleHalfWidth + 0x100),
                  (s16)gVsBattleMinY, (s16)gVsBattleMaxY);
    TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlMap, 0);
    gUnk_02039B98 = 0;
    FadeStartIn(FADE_MODE_BLACK, 60);
}

void mode_vsbattle_1(void) {
    if (gBtlWork->paused == 0) {
        VsBattleUpdate();

        if (gBtlWork->hitStop <= 0) {
            TaskPoolUpdate(&gBtlWork->taskPools[0]);
        } else {
            gBtlWork->hitStop--;
        }

        BgFxUpdate();
        ColliderUpdateAll();
        TaskPoolDraw(&gBtlWork->taskPools[1]);

        if (gBtlWork->flags & BTL_FLAG_CARD_BREAK) {
            gBtlWork->flags &= ~BTL_FLAG_CARD_BREAK;
        }
    }

    TaskPoolDraw(&gBtlWork->taskPools[0]);
}

void mode_vsbattle_2(void) {
    BgFxFree();
    TaskPoolDestroy(&gBtlWork->taskPools[1]);
    TaskPoolDestroy(&gBtlWork->taskPools[0]);
    ReleaseBattleTiles();
    EwramFree(gRikuBtlWork);
    EwramFree(gBtlWork);
}

void func_0800C6B0(void) {
}

void func_0800C6B4(void) {
}

void PlayVsBattleBgm(void) {
    switch (gGameState.battleStage) {
    case BATTLE_STAGE_WONDERLAND:
        m4aSongNumStart(SONG_BGM_ALICE_BTL);
        break;
    case BATTLE_STAGE_AGRABAH:
        m4aSongNumStart(SONG_BGM_ALADDIN_BATTLE);
        break;
    case BATTLE_STAGE_ATLANTICA:
        m4aSongNumStart(SONG_BGM_MARMAID_BATTLE);
        break;
    case BATTLE_STAGE_MONSTRO:
        m4aSongNumStart(SONG_BGM_PINOCCHIO_BTL);
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
    default:
        m4aSongNumStart(SONG_BGM_BOSS1_WORLD);
        break;
    }
}

Mode gModeVsbattle = { "mode_vsbattle", (ModeInitFunc)mode_vsbattle_0, mode_vsbattle_1, mode_vsbattle_2 };
