#include "mode_test.h"
#include "msg.h"
#include "card_ids.h"


TaskPool gEventTaskPool;
u8 gEventPaused;
u32 gEventId;
u8 gEventEndStep;

void Event_0(s32 arg) {
    EvtArg cfg;
    EventBackgroundDef* e;

    gEventState = EwramAlloc(sizeof(EventState));
    e = gEventBackgroundDefs[arg & 0x7FFF];
    gBldCnt = 0;
    gBldAlpha = 0;
    gEventId = arg;
    gEventPaused = 0;

    if (e != 0) {
        if (e->isAffine != 0) {
            SetBgMode1();
            SetupBg(0, 3, 31, 14);
            SetupBg(1, 0, 16, 0);
            SetupBg(2, 0, 17, 0);
            SetupBg(3, 0, 18, 0);
            SetBgPriority(0, 0);
            SetBgPriority(1, 1);
            SetBgPriority(2, 2);
            SetBgPriority(3, 3);
        } else {
            SetBgMode0();
            SetupBg(0, 3, 31, 14);
            SetupBg(1, 0, 21, 0);
            SetupBg(2, 0, 22, 0);
            SetupBg(3, 0, 23, 0);
            SetBgPriority(0, 0);
            SetBgPriority(1, 1);
            SetBgPriority(2, 2);
            SetBgPriority(3, 3);
            DisableBg(0);
            DisableBg(1);
            DisableBg(2);
            DisableBg(3);
        }
    } else {
        SetBgMode0();
        SetBgMode0();
        SetupBg(0, 0, 22, 0);
        SetupBg(1, 0, 24, 0);
        SetupBg(2, 2, 28, 14);
        SetBgPriority(0, 3);
        SetBgPriority(1, 2);
        SetBgPriority(2, 1);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
    }

    cfg.eventId = arg;
    gEventState->eventId = arg & 0x7FFF;

    if (arg & 0x8000) {
        cfg.unk_08 = 0;
    } else {
        cfg.unk_08 = 1;
    }

    // @bug? Should mask with 0x7FFF.
    if (gEventSequenceDefs[gEventId & 0x8000]->keyframes->flags & 0x80) {
        FadeStartIn(1, 999);
    }

    TaskPoolInit(&gEventTaskPool, 2);
    TaskCreate(&gEventTaskPool, &gTaskDescEventSeq, &cfg);
    ResetMessageWindowFlags();
    gEventEndStep = 0;
}
void EventDebugUpdate(void) {
    if (gEventState == 0) {
        ModeRequest(&gModeEventselect, 0);
    }

    if (gEventPaused == 0) {
        TaskPoolUpdate(&gEventTaskPool);
    } else if (GetKeysRepeat() & SELECT_BUTTON) {
        TaskPoolUpdate(&gEventTaskPool);
    }

    TaskPoolDraw(&gEventTaskPool);

    if (gEventState->running == 0) {
        if (gEventEndStep == 0) {
            ShowEventEndMessage();
            gEventEndStep = 1;
        }

        if (gEventEndStep == 1) {
            if (IsMessageWindowOpen() == 0) {
                ModeRequest(&gModeEventselect, 0);
            }
        }
    }

    if (GetKeysPressed() & START_BUTTON) {
        gEventPaused = 0;
    }
}

void EventUpdate(void) {
    EventSequenceDef* p = gEventSequenceDefs[gEventId];
    UpdatePlayTime();
    TaskPoolUpdate(&gEventTaskPool);
    TaskPoolDraw(&gEventTaskPool);
    if (gEventState->running != 0) {
        return;
    }
    if (gEventEndStep == 0) {
        ShowEventEndMessage();
        gEventEndStep = 1;
    }
    if (gEventEndStep != 1) {
        return;
    }
    if (IsMessageWindowOpen() != 0) {
        return;
    }
    func_08062D3C();
    if (IsMessageWindowAnswerYes() == 1) {
        func_0806250C();
        SaveAfterEvent();
        return;
    }
    func_08061FC8();
    func_0806250C();
    func_080629F8();
    func_08062D20();
    if (gEventState->askedYesNo != 0) {
        if (gEventState->answerYes == 0) {
            if (func_080629CC() == 0) {
                AdvanceFloorStory();
                RequestMapMode();
            }
        } else {
            func_0806297C();
        }
        return;
    }
    if (p->unk_1A != 0) {
#ifdef VERSION_EU
        if (gEventId == 148) {
#else
        if (gEventId == 150) {
#endif
            ModeRequest(&gModeWorldselect, 0);
        } else {
            AdvanceFloorStory();
            RequestMapMode();
        }
        return;
    }
    if (p->nextEvent != 0xFFFF) {
        switch (p->nextEvent) {
        case 12:
        case 14:
        case 17:
        case 20:
        case 23:
        case 28:
        case 32:
        case 35:
        case 38:
        case 42:
        case 47:
        case 50:
        case 53:
        case 58:
        case 68:
#ifdef VERSION_EU
        case 155:
        case 163:
        case 166:
        case 167:
        case 173:
        case 182:
        case 189:
#else
        case 157:
        case 165:
        case 168:
        case 169:
        case 175:
        case 184:
        case 191:
#endif
            AdvanceFloorStory();
            RequestMapMode();
            break;
        case 61:
            AdvanceToExitHall();
            RequestMapMode();
            break;
        default:
            ModeRequest(&gModeEvent, p->nextEvent);
            break;
        }
        return;
    }
    if (p->startsBattle != 0) {
        if (p->battleId == 122) {
            gGameState.battleStage = 7;
        } else if (p->battleId == 120) {
            gGameState.battleStage = 1;
        } else if (p->battleId == 121) {
            gGameState.battleStage = 5;
        } else if (p->battleId == 123) {
            gGameState.battleStage = 3;
        } else if (p->battleId == 124) {
            gGameState.battleStage = 3;
        }
        ModeRequest(&gModeBattle, p->battleId);
        return;
    }
    if (p->toTitle != 0) {
        FadeStartOut(0, 16);
        ModeRequest(&gModeTitle, 0);
        return;
    }
    if (p->toCopyright != 0) {
        ModeRequest(&gModeCopyright1, 0);
        return;
    }
    if (p->unk_1E != 0) {
        AdvanceFloorStory();
        ModeRequest(&gModeMapFld, 0);
        return;
    }
    if (p->unk_28 != 0xFFFF) {
        switch (p->unk_28) {
        case 2:
            ModeRequest(&gModeBattle, 178);
            break;
        case 4:
            ModeRequest(&gModeBattle, 179);
            break;
        case 12:
            ModeRequestHeapReset(&gModeMovie, 4);
            break;
        case 1:
            gGameState.availableWorlds = 512;
            ModeRequest(&gModeWorldselect, 0);
            break;
        case 10:
            ModeRequestHeapReset(&gModeMovie, 2);
            break;
        case 11:
            ModeRequestHeapReset(&gModeMovie, 3);
            break;
        case 13:
            ModeRequestHeapReset(&gModeMovie, 5);
            break;
        case 3:
        case 5:
        case 6:
            AdvanceFloorStory();
            RequestMapMode();
            break;
        default:
            ModeRequest(&gModeDummy, p->unk_28);
            break;
        }
        return;
    }
    if (p->unk_2A != 0) {
        AdvanceFloorStory();
        RequestMapMode();
    } else if (p->unk_2B != 255) {
        AdvanceFloorStory();
        RequestMapMode();
    } else if (p->unk_2C != 255) {
        if (p->unk_2C == 0) {
            AdvanceFloorStory();
            ModeRequest(&gModePooh, 0);
        } else if (p->unk_2C <= 6) {
            ModeRequest(&gModePooh, 1);
        }
    }
}

void Event_2(void) {
    TaskPoolDestroy(&gEventTaskPool);
    EwramFree(gEventState);
    gEventState = 0;
}

void RequestEventMode(u16 a) {
    ModeRequest(&gModeEvent, a);
}
#ifdef VERSION_EU
#define MSG_CODE(n) ((n) - 2)
#else
#define MSG_CODE(n) (n)
#endif

void ShowEventEndMessage(void) {
    SetBackdropColor(0, 0, 0);

    switch (gEventId & 0x7FFF) {
    case 41:
    case 49:
    case MSG_CODE(176):
    case MSG_CODE(185):
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        m4aSongNumStart(SONG_SYS_ITEMGET);
        CreateSysmsgwinTask(&gEventTaskPool, 173);
        break;
    case 34:
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        m4aSongNumStart(SONG_SYS_ITEMGET);
        CreateSysmsgwinTask(&gEventTaskPool, 133);
        break;
    case 88:
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        m4aSongNumStart(SONG_SYS_ITEMGET);
        CreateSysmsgwinTask(&gEventTaskPool, 134);
        break;
    case MSG_CODE(136):
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        m4aSongNumStart(SONG_SYS_ITEMGET);
        CreateSysmsgwinTask(&gEventTaskPool, 139);
        break;
    case MSG_CODE(137):
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        m4aSongNumStart(SONG_SYS_ITEMGET);
        CreateSysmsgwinTask(&gEventTaskPool, 160);
        break;
    case MSG_CODE(139):
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        m4aSongNumStart(SONG_SYS_ITEMGET);
        CreateSysmsgwinTask(&gEventTaskPool, 159);
        break;
    case MSG_CODE(140):
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        m4aSongNumStart(SONG_SYS_ITEMGET);
        CreateSysmsgwinTask(&gEventTaskPool, 136);
        break;
    case MSG_CODE(141):
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        m4aSongNumStart(SONG_SYS_ITEMGET);
        CreateSysmsgwinTask(&gEventTaskPool, 137);
        break;
    case MSG_CODE(142):
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        m4aSongNumStart(SONG_SYS_ITEMGET);
        CreateSysmsgwinTask(&gEventTaskPool, 135);
        break;
    case 61:
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        m4aSongNumStart(SONG_SYS_ITEMGET);
        CreateSysmsgwinTask(&gEventTaskPool, 138);
        break;
    case 126:
        m4aSongNumStart(SONG_SYS_ITEMGET);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        CreateSysmsgwinTask(&gEventTaskPool, 162);
        break;
    case 114:
        m4aSongNumStart(SONG_SYS_ITEMGET);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        CreateSysmsgwinTask(&gEventTaskPool, 161);
        break;
    case 57:
        m4aSongNumStart(SONG_SYS_ITEMGET);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        CreateSysmsgwinTask(&gEventTaskPool, 163);
        break;
    case MSG_CODE(143):
    case MSG_CODE(144):
        m4aSongNumStart(SONG_SYS_ITEMGET);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        CreateSysmsgwinTask(&gEventTaskPool, 165);
        break;
    case MSG_CODE(145):
    case MSG_CODE(146):
    case MSG_CODE(147):
    case MSG_CODE(148):
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        CreateSysmsgwinTask(&gEventTaskPool, 166);
        break;
    case 3:
    case 44:
    case 53:
    case 74:
    case 94:
    case 101:
    case 108:
    case 115:
    case 120:
    case MSG_CODE(129):
    case MSG_CODE(151):
    case MSG_CODE(177):
    case MSG_CODE(186):
    case MSG_CODE(192):
        m4aSongNumStart(SONG_SYS_ITEMGET);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        CreateSysmsgwinTask(&gEventTaskPool, 168);
        break;
    case 54:
    case 75:
    case 89:
    case 96:
    case 102:
    case 109:
    case 116:
    case 121:
    case MSG_CODE(130):
    case MSG_CODE(152):
    case MSG_CODE(188):
        m4aSongNumStart(SONG_SYS_ITEMGET);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        CreateSysmsgwinTask(&gEventTaskPool, 169);
        break;
    case 5:
        m4aSongNumStart(SONG_SYS_ITEMGET);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        CreateSysmsgwinTask(&gEventTaskPool, 175);
        break;
    case 6:
    case 80:
    case 90:
    case 97:
    case 103:
    case 111:
    case 117:
    case 123:
    case MSG_CODE(131):
    case MSG_CODE(153):
        m4aSongNumStart(SONG_SYS_ITEMGET);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        CreateSysmsgwinTask(&gEventTaskPool, 170);
        break;
    case 119:
        m4aSongNumStart(SONG_SYS_ITEMGET);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        CreateSysmsgwinTask(&gEventTaskPool, 172);
        break;
    case 60:
        m4aSongNumStart(SONG_SYS_ITEMGET);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        CreateSysmsgwinTask(&gEventTaskPool, 164);
        break;
    case 27:
    case MSG_CODE(156):
    case MSG_CODE(166):
        m4aSongNumStart(SONG_SYS_ITEMGET);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        FadeStartIn(0, 1);
        CreateSysmsgwinTask(&gEventTaskPool, 174);
        break;
    }
}
void func_08061FC8(void) {
    switch (gEventId) {
    case 0:
        gGameState.progression.friendFlags = 3;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        break;
    case 94:
        gGameState.progression.friendFlags = 3;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        break;
    case 74:
        gGameState.progression.friendFlags = 3;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        break;
    case 88:
        gGameState.progression.friendFlags = 19;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        LearnStock(62);
        break;
    case 93:
        gGameState.progression.friendFlags = 3;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        break;
    case 107:
        gGameState.progression.friendFlags = 7;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        LearnStock(61);
        break;
    case 114:
        gGameState.progression.friendFlags = 3;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        break;
    case 103:
        gGameState.progression.friendFlags = 11;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        LearnStock(63);
        break;
    case 106:
        gGameState.progression.friendFlags = 3;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        break;
    case MSG_CODE(131):
        gGameState.progression.friendFlags = 67;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        LearnStock(65);
        break;
    case MSG_CODE(133):
        gGameState.progression.friendFlags = 3;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        break;
    case 117:
        gGameState.progression.friendFlags = 3;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        break;
    case 116:
    case 118:
        gGameState.progression.friendFlags = 35;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        LearnStock(64);
        break;
    case 119:
        gGameState.progression.friendFlags = 3;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        break;
    case 120:
        gGameState.progression.friendFlags = 3;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        break;
    case 44:
        gGameState.progression.friendFlags = 3;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        break;
    case 59:
        gGameState.progression.friendFlags = 3;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        break;
    case 52:
    case MSG_CODE(149):
        gGameState.progression.friendFlags = 0;
        LearnStock(57);
        LearnStock(59);
        LearnStock(60);
        break;
    case MSG_CODE(155):
        gGameState.progression.friendFlags = 128;
        LearnStock(69);
        break;
    case MSG_CODE(174):
    case MSG_CODE(186):
        gGameState.progression.friendFlags = 0;
        break;
    case MSG_CODE(185):
    case MSG_CODE(190):
        gGameState.progression.friendFlags = 128;
        break;
    case MSG_CODE(156):
        gGameState.flags &= ~0x100;
        LearnStock(66);
        LearnStock(67);
        LearnStock(68);
        break;
    }
}
void func_0806250C(void) {
    switch (gEventId) {
    case 0:
        gGameState.availableWorlds = 0x200;
        break;
    case 5:
        ObtainCard(CARD_ID(CARD_SIMBA, 6));
        break;
    case 11:
        gGameState.availableWorlds = 61;
        break;
    case 27:
        gGameState.availableWorlds = 0x4C2;
        break;
    case 41:
        gGameState.availableWorlds = 0x800;
        break;
    case 49:
        gGameState.availableWorlds = 256;
        break;
    case 60:
        gGameState.availableWorlds = 0x1000;
        ObtainCard(CARD_ID(CARD_OBLIVION, 6));
        break;
    case 57:
        ObtainCard(CARD_ID(CARD_OATHKEEPER, 4));
        break;
    case 3:
    case 44:
    case 53:
    case 61:
    case 74:
    case 88:
    case 94:
    case 101:
    case 108:
    case 115:
    case 120:
    case MSG_CODE(129):
    case MSG_CODE(151):
    case MSG_CODE(177):
    case MSG_CODE(186):
    case MSG_CODE(192):
        AddMapCard(221);
        break;
    case 4:
    case 54:
    case 75:
    case 89:
    case 96:
    case 102:
    case 109:
    case 116:
    case 121:
    case MSG_CODE(130):
    case MSG_CODE(152):
    case MSG_CODE(188):
        AddMapCard(231);
        break;
    case 6:
    case 80:
    case 90:
    case 97:
    case 103:
    case 111:
    case 117:
    case 123:
    case MSG_CODE(131):
    case MSG_CODE(153):
        AddMapCard(241);
        break;
    case 114:
        ObtainCard(CARD_ID(CARD_GENIE, 6));
        break;
    case 119:
        ObtainCard(CARD_ID(CARD_TINKER_BELL, 4));
        break;
    case 126:
        ObtainCard(CARD_ID(CARD_CLOUD, 4));
        break;
    case MSG_CODE(137):
        ObtainCard(CARD_ID(CARD_SPELLBINDER, 4));
        break;
    case MSG_CODE(139):
        ObtainCard(CARD_ID(CARD_ELIXIR, 1));
        break;
    case MSG_CODE(143):
    case MSG_CODE(144):
        ObtainCard(CARD_ID(CARD_BAMBI, 5));
        break;
    case MSG_CODE(149):
        gGameState.availableWorlds = 128;
        break;
    case MSG_CODE(156):
        gGameState.availableWorlds = 593;
        break;
    case MSG_CODE(166):
        gGameState.availableWorlds = 46;
        break;
    case MSG_CODE(176):
        gGameState.availableWorlds = 256;
        break;
    case MSG_CODE(185):
        gGameState.availableWorlds = 0x800;
        break;
    case MSG_CODE(191):
        gGameState.availableWorlds = 0x1000;
        break;
    }
}
void func_0806297C(void) {
    EventSequenceDef* m = gEventSequenceDefs[gEventId];

    switch (gEventId) {
    case 68:
        ModeRequest(&gModeEvent, 69);
        break;
    case 83:
    case 84:
        gGameState.battleStage = 5;
        ModeRequest(&gModeBattle, m->battleId);
        break;
    }
}
u8 func_080629CC(void) {
    switch (gEventId) {
    case 0x44:
    case 0x53:
    case 0x54:
        RequestMapMode();
        return 1;
    }
    return 0;
}
void func_080629F8(void) {
    switch (gEventId) {
    case 2:
        SetCardKindObtained(0);
        break;
    case MSG_CODE(136):
        LearnStock(41);
        break;
    case MSG_CODE(140):
        LearnStock(40);
        break;
    case MSG_CODE(141):
        LearnStock(50);
        break;
    case MSG_CODE(142):
        LearnStock(43);
        break;
    case 34:
        LearnStock(38);
        break;
    case 88:
        LearnStock(42);
        break;
    case 108:
        SetCardKindObtained(1);
        break;
    case 74:
        SetCardKindObtained(5);
        break;
    case 120:
        SetCardKindObtained(8);
        break;
    case 94:
        SetCardKindObtained(10);
        break;
    case 101:
        SetCardKindObtained(2);
        break;
    case 115:
        SetCardKindObtained(4);
        break;
    case MSG_CODE(129):
        SetCardKindObtained(11);
        break;
    case 87:
        SetCardKindObtained(3);
        break;
    case 59:
        SetCardKindObtained(13);
        break;
    case 61:
        LearnStock(8);
        break;
    case 67:
        SetCardKindObtained(15);
        SetCardKindObtained(16);
        break;
    }
}
#ifdef VERSION_EU
#define MSG_SAVE_ID_LO 0x8D
#else
#define MSG_SAVE_ID_LO 0x8F
#endif

void SaveAfterEvent(void) {
    switch (gEventId) {
    case MSG_SAVE_ID_LO + 0:
    case MSG_SAVE_ID_LO + 1:
    case MSG_SAVE_ID_LO + 2:
    case MSG_SAVE_ID_LO + 3:
    case MSG_SAVE_ID_LO + 4:
    case MSG_SAVE_ID_LO + 5:
        if (gGameState.flags & 0x10) {
            SaveWriteFileLarge(1);
        } else {
            SaveWriteFileLarge(0);
        }
        EnterExitHall();
        break;
    }
}
void func_08062D20(void) {
    switch (gEventId) {
    case MSG_SAVE_ID_LO + 0:
    case MSG_SAVE_ID_LO + 1:
    case MSG_SAVE_ID_LO + 2:
    case MSG_SAVE_ID_LO + 3:
    case MSG_SAVE_ID_LO + 4:
    case MSG_SAVE_ID_LO + 5:
        EnterExitHall();
        break;
    }
}
void func_08062D3C(void) {
    switch (gEventId) {
    case 0x43:
        SetJiminyFlag(16);
        break;
    case 0x3F:
        SetJiminyFlag(41);
        break;
    }
}

Mode gModeEventDebug = {
    "Event",
    Event_0,
    EventDebugUpdate,
    Event_2,
};

Mode gModeEvent = {
    "Event",
    Event_0,
    EventUpdate,
    Event_2,
};
