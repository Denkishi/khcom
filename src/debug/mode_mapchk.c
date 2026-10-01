#include "mode_mapchk.h"
#include "registration_data.h"
#include "map_runtime.h"
#include "map_api.h"
#include "mode_test_api.h"
#include "card_api.h"
#include "save_api.h"
#include "bos4_api.h"
#include "game_state.h"
#include "m4a_song.h"
#include "display.h"
#include "fade.h"
#include "key.h"
#include "malloc.h"
#include "world_types.h"
#include "gba/keys.h"
#include "map_types.h"
#include "mode.h"
#include "player_progression_types.h"
#include "save_types.h"
#include "types.h"

static const char sDebugMenuTextUs_0984B5F8[] = "\202s\202t\202s\202n\202q\202h\202`\202k";

static const char sDebugMenuTextUs_0984B60C[] = "\202f\202n\202`\202k\201@\201@\201@\201@";

static const char sDebugMenuTextUs_0984B620[] = "\202r\202s\202`\202q\202s\201@\201@\201@";

static const char sDebugMenuTextUs_0984B634[] = "\202e\202h\202d\202k\202c\201@\201@\201@";

static const char sDebugMenuTextUs_0984B648[] = "\202c\202d\202a\202t\202f\201@\201@\201@";

static const char sDebugMenuTextUs_0984B65C[] = "\202e\202t\202m\202m\202d\202k\201@";

static const char sDebugMenuTextUs_0984B66C[] = "\202r\202s\202`\202f\202d\201@\201@";

static const char sDebugMenuTextUs_0984B67C[] = "\202g\202d\202w\202`\202f\202n\202m";

static const char sDebugMenuTextUs_0984B68C[] = "\202b\202k\202h\202e\202e\201@\201@";

static const char sDebugMenuTextUs_0984B69C[] = "\202o\202`\202r\202r\201@\201@\201@";

static const char sDebugMenuTextUs_0984B6AC[] = "\202s\202n\202v\202d\202q\201@\201@";

static const char sDebugMenuTextUs_0984B6BC[] = "\202r\202l\202`\202k\202k\201@\201@";

static const char sDebugMenuTextUs_0984B6CC[] = "\202e\202k\202`\202s\201@\201@\201@";

static const char sDebugMenuTextUs_0984B6DC[] = "\202v\202h\202c\202d\201@\201@\201@";

static const char sDebugMenuTextUs_0984B6EC[] = "\202g\202h\202f\202g\201@\201@\201@";

static const char sDebugMenuTextUs_0984B6FC[] = "\202k\202n\202v\201@\201@\201@\201@";

static const char sDebugMenuTextUs_0984B70C[] = "\202q\202`\202m\202c\202n\202l\201@";

static const char sDebugMenuTextUs_0984B71C[] = "\202c\202d\202e\202`\202t\202k\202s";

static const char sMapChkWhitePalette[32] = "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377";

static const char sMapChkOnText[] = "\202n\202m\201@";

static const char sMapChkOffText[] = "\202n\202e\202e";

static const char sMapChkBasementText[] = "\201i\202a\201@\201@\201@\201j";

static const char sMapChkBasementNoneText[] = "\201i\202a\201|\201|\201|\201j";

static const char sMapChkHelpText[] = "\202t\202c\201F\202r\202d\202k\202d\202b\202s\201@\202k\202q\201F\202r\202d\202s\201@\202`\201F\202r\202s\202`\202q\202s";

static const char sMapChkModeLabel[] = "\202l\202n\202c\202d\201@\201F";

static const char sMapChkWorldLabel[] = "\202v\202n\202q\202k\202c\201F";

static const char sMapChkFloorLabel[] = "\202e\202k\202n\202n\202q\201F";

static const char sMapChkParamLabel[] = "\202o\202`\202q\202`\202l\201F";

static const char sMapChkFormLabel[] = "\202e\202n\202q\202l\201@\201F";

static const char sMapChkWideLabel[] = "\202v\202h\202c\202d\201@\201F";

static const char sMapChkHighLabel[] = "\202g\202h\202f\202g\201@\201F";

static const char sMapChkDeepLabel[] = "\202c\202d\202d\202o\201@\201F";

static const char sMapChkCursorBlankText[] = "\201@";

static const char sMapChkCursorText[] = "\201\204";

static MapChkWork* gMapChkWork;
static MapFormDef* sMapChkForm;

static const char* sMapChkModeNames[] = {
    sDebugMenuTextUs_0984B648,
    sDebugMenuTextUs_0984B634,
    sDebugMenuTextUs_0984B620,
    sDebugMenuTextUs_0984B60C,
    sDebugMenuTextUs_0984B5F8,
};

static const char* sMapChkFormNames[] = {
    sDebugMenuTextUs_0984B71C,
    sDebugMenuTextUs_0984B70C,
    sDebugMenuTextUs_0984B6FC,
    sDebugMenuTextUs_0984B6EC,
    sDebugMenuTextUs_0984B6DC,
    sDebugMenuTextUs_0984B6CC,
    sDebugMenuTextUs_0984B6BC,
    sDebugMenuTextUs_0984B6AC,
    sDebugMenuTextUs_0984B69C,
    sDebugMenuTextUs_0984B68C,
    sDebugMenuTextUs_0984B67C,
    sDebugMenuTextUs_0984B66C,
    sDebugMenuTextUs_0984B65C,
};

static void (*sMapChkRowHandlers[10])(MapChkWork*) = {
    MapChkEditMode,
    MapChkEditWorld,
    MapChkEditFloor,
    MapChkFlipParamToggle,
    MapChkEditForm,
    MapChkEditWidth,
    MapChkEditMinHeight,
    MapChkEditMaxHeight,
    MapChkEditMinDepth,
    MapChkEditMaxDepth,
};

Mode gModeMapChk = {
    "Mode_MapChk",
    (ModeInitFunc)Mode_MapChk_0,
    Mode_MapChk_1,
    Mode_MapChk_2,
};

void MapChkSetParamToggle(u8* p, u8 a) {
    if (p[5] != a) {
        p[5] = a;

        if (a != 0) {
            DebugTextPrint(80, 68, 2, sMapChkOnText);
        } else {
            DebugTextPrint(80, 68, 2, sMapChkOffText);
        }
    }
}

void MapChkSetFloorProgress(u8 a, u8 b) {
    if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
        if (b != 0) {
            switch (a) {
            case 0:
                gMapFloorState.progress = 1;
                break;
            case 1:
                gMapFloorState.progress = 3;
                break;
            case 2:
                gMapFloorState.progress = 5;
                break;
            case 3:
                gMapFloorState.progress = 7;
                break;
            case 4:
                gMapFloorState.progress = 9;
                break;
            case 5:
                gMapFloorState.progress = 11;
                break;
            case 6:
                gMapFloorState.progress = 13;
                break;
            case 7:
                gMapFloorState.progress = 15;
                break;
            case 8:
                gMapFloorState.progress = 17;
                break;
            case 9:
                gMapFloorState.progress = 19;
                break;
            case 10:
                gMapFloorState.progress = 22;
                break;
            case 11:
                gMapFloorState.progress = 24;
                break;
            }
        } else {
            switch (a) {
            case 0:
                gMapFloorState.progress = 0;
                break;
            case 1:
                gMapFloorState.progress = 2;
                break;
            case 2:
                gMapFloorState.progress = 4;
                break;
            case 3:
                gMapFloorState.progress = 6;
                break;
            case 4:
                gMapFloorState.progress = 8;
                break;
            case 5:
                gMapFloorState.progress = 10;
                break;
            case 6:
                gMapFloorState.progress = 12;
                break;
            case 7:
                gMapFloorState.progress = 14;
                break;
            case 8:
                gMapFloorState.progress = 16;
                break;
            case 9:
                gMapFloorState.progress = 18;
                break;
            case 10:
                gMapFloorState.progress = 20;
                break;
            case 11:
                gMapFloorState.progress = 23;
                break;
            }
        }
    } else {
        if (b != 0) {
            switch (a) {
            case 0:
                gMapFloorState.progress = 1;
                break;
            case 1:
                gMapFloorState.progress = 3;
                break;
            case 2:
                gMapFloorState.progress = 5;
                break;
            case 3:
                gMapFloorState.progress = 7;
                break;
            case 4:
                gMapFloorState.progress = 9;
                break;
            case 5:
                gMapFloorState.progress = 11;
                break;
            case 6:
                gMapFloorState.progress = 13;
                break;
            case 7:
                gMapFloorState.progress = 15;
                break;
            case 8:
                gMapFloorState.progress = 17;
                break;
            case 9:
                gMapFloorState.progress = 19;
                break;
            case 10:
                gMapFloorState.progress = 21;
                break;
            case 11:
                gMapFloorState.progress = 23;
                break;
            case 12:
                gMapFloorState.progress = 27;
                break;
            }
        } else {
            switch (a) {
            case 0:
                gMapFloorState.progress = 0;
                break;
            case 1:
                gMapFloorState.progress = 2;
                break;
            case 2:
                gMapFloorState.progress = 4;
                break;
            case 3:
                gMapFloorState.progress = 6;
                break;
            case 4:
                gMapFloorState.progress = 8;
                break;
            case 5:
                gMapFloorState.progress = 10;
                break;
            case 6:
                gMapFloorState.progress = 12;
                break;
            case 7:
                gMapFloorState.progress = 14;
                break;
            case 8:
                gMapFloorState.progress = 16;
                break;
            case 9:
                gMapFloorState.progress = 18;
                break;
            case 10:
                gMapFloorState.progress = 20;
                break;
            case 11:
                gMapFloorState.progress = 22;
                break;
            case 12:
                gMapFloorState.progress = 25;
                break;
            }
        }
    }
}

void MapChkEditMode(MapChkWork* p) {
    if ((GetKeysRepeat() & DPAD_LEFT) != 0) {
        p->mode = p->mode == 0 ? 4 : p->mode - 1;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0) {
        p->mode = p->mode > 3 ? 0 : p->mode + 1;
    }

    DebugTextPrint(80, 32, 2, sMapChkModeNames[p->mode]);
}

void MapChkEditWorld(MapChkWork* p) {
    u8 v = p->world;
    const u8* t;
    s32 n;

    if ((GetKeysRepeat() & DPAD_LEFT) != 0) {
        p->world = p->world == 0 ? 12 : p->world - 1;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0) {
        p->world = p->world > 11 ? 0 : p->world + 1;
    }

    if (v != p->world) {
        t = gUnk_0984B458[0];
        n = p->world * 8;
        t += 4;
        DebugTextPrint(80, 44, 2, *(const char**)(t + n));
    }
}

void MapChkEditFloor(MapChkWork* p) {
    if ((GetKeysRepeat() & DPAD_LEFT) != 0) {
        p->floor = p->floor == 0 ? 13 : p->floor - 1;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0) {
        p->floor = p->floor > 12 ? 0 : p->floor + 1;
    }

    DebugTextPrintNumber(80, 56, 2, p->floor + 1);
    DebugTextPrint(112, 56, 2, sMapChkBasementText);

    if (12 - p->floor > 0) {
        DebugTextPrintNumber(128, 56, 2, 12 - p->floor);
    } else {
        DebugTextPrint(112, 56, 2, sMapChkBasementNoneText);
    }
}

void MapChkEditForm(MapChkWork* p) {
    u8 v = p->form;

    if ((GetKeysRepeat() & DPAD_LEFT) != 0) {
        p->form = p->form == 0 ? 12 : p->form - 1;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0) {
        p->form = p->form > 11 ? 0 : p->form + 1;
    }

    if (v != p->form) {
        LoadMapForm(p->form + 15);
        DebugTextPrint(80, 80, 2, sMapChkFormNames[p->form]);
        DebugTextPrintNumber(80, 92, 2, sMapChkForm->maxWidth);
        DebugTextPrintNumber(80, 104, 2, sMapChkForm->minHeight);
        DebugTextPrintNumber(80, 116, 2, sMapChkForm->maxHeight);
        DebugTextPrintNumber(80, 128, 2, sMapChkForm->minDepth);
        DebugTextPrintNumber(80, 140, 2, sMapChkForm->maxDepth);
        MapChkSetParamToggle((u8*)p, 1);
    }
}

void MapChkEditWidth(MapChkWork* p) {
    u8 v = sMapChkForm->maxWidth;

    if ((GetKeysRepeat() & DPAD_LEFT) != 0 && v > 8) {
        v--;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0 && v <= 47) {
        v++;
    }

    if (sMapChkForm->maxWidth != v) {
        sMapChkForm->maxWidth = v;
        sMapChkForm->minWidth = v;
        DebugTextPrintNumber(80, 92, 2, sMapChkForm->maxWidth);
        MapChkSetParamToggle((u8*)p, 1);
    }
}

void MapChkFlipParamToggle(MapChkWork* p) {
    if ((GetKeysRepeat() & (DPAD_RIGHT | DPAD_LEFT)) != 0) {
        MapChkSetParamToggle((u8*)p, p->useParams == 0 ? 1 : 0);
    }
}

void MapChkEditMinHeight(MapChkWork* p) {
    u8 v = sMapChkForm->minHeight;

    if ((GetKeysRepeat() & DPAD_LEFT) != 0 && v > 2) {
        v--;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0 && v <= 9) {
        v++;
    }

    if (sMapChkForm->minHeight != v) {
        sMapChkForm->minHeight = v;
        DebugTextPrintNumber(80, 104, 2, sMapChkForm->minHeight);

        if (sMapChkForm->maxHeight < v) {
            sMapChkForm->maxHeight = v;
            DebugTextPrintNumber(80, 116, 2, sMapChkForm->maxHeight);
        }

        MapChkSetParamToggle((u8*)p, 1);
    }
}

void MapChkEditMaxHeight(MapChkWork* p) {
    u8 v = sMapChkForm->maxHeight;

    if ((GetKeysRepeat() & DPAD_LEFT) != 0 && v > 2) {
        v--;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0 && v <= 9) {
        v++;
    }

    if (sMapChkForm->maxHeight != v) {
        sMapChkForm->maxHeight = v;
        DebugTextPrintNumber(80, 116, 2, sMapChkForm->maxHeight);

        if (sMapChkForm->minHeight > v) {
            sMapChkForm->minHeight = v;
            DebugTextPrintNumber(80, 104, 2, sMapChkForm->minHeight);
        }

        MapChkSetParamToggle((u8*)p, 1);
    }
}

void MapChkEditMinDepth(MapChkWork* p) {
    u8 v = sMapChkForm->minDepth;

    if ((GetKeysRepeat() & DPAD_LEFT) != 0 && v > 3) {
        v--;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0 && v <= 47) {
        v++;
    }

    if (sMapChkForm->minDepth != v) {
        sMapChkForm->minDepth = v;
        DebugTextPrintNumber(80, 128, 2, sMapChkForm->minDepth);

        if (sMapChkForm->maxDepth < v) {
            sMapChkForm->maxDepth = v;
            DebugTextPrintNumber(80, 140, 2, sMapChkForm->maxDepth);
        }

        MapChkSetParamToggle((u8*)p, 1);
    }
}

void MapChkEditMaxDepth(MapChkWork* p) {
    u8 v = sMapChkForm->maxDepth;

    if ((GetKeysRepeat() & DPAD_LEFT) != 0 && v > 3) {
        v--;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0 && v <= 47) {
        v++;
    }

    if (sMapChkForm->maxDepth != v) {
        sMapChkForm->maxDepth = v;
        DebugTextPrintNumber(80, 140, 2, sMapChkForm->maxDepth);

        if (sMapChkForm->minDepth > v) {
            sMapChkForm->minDepth = v;
            DebugTextPrintNumber(80, 128, 2, sMapChkForm->minDepth);
        }

        MapChkSetParamToggle((u8*)p, 1);
    }
}

void Mode_MapChk_0() {
    const u8* t;
    s32 n;

    gMapChkWork = EwramAlloc(8);
    SaveLoadHeader();
    gMapChkUseParams = 0;
    gMapChkWork->cursor = 0;
    gMapChkWork->mode = 0;
    gMapChkWork->world = 0;
    gMapChkWork->floor = 1;
    gMapChkWork->form = 0;
    gMapChkWork->useParams = 0;
    gGameState.roomEffect = 0;
    LoadMapForm(gMapChkWork->form);
    sMapChkForm = &gMapForm;
    SetBgMode0();
    SetupBg(0, 0, 15, 0);
    EnableBg(0);
    DebugTextInit(0, 0x5400, 0x500);
    DebugTextLoadPalette(0, sMapChkWhitePalette, 32, 15);
    DebugTextPrint(0, 0, 2, sMapChkHelpText);
    DebugTextPrint(24, 32, 2, sMapChkModeLabel);
    DebugTextPrint(24, 44, 2, sMapChkWorldLabel);
    DebugTextPrint(24, 56, 2, sMapChkFloorLabel);
    DebugTextPrint(24, 68, 2, sMapChkParamLabel);
    DebugTextPrint(24, 80, 2, sMapChkFormLabel);
    DebugTextPrint(24, 92, 2, sMapChkWideLabel);
    DebugTextPrint(24, 104, 2, sMapChkHighLabel);
    DebugTextPrint(24, 128, 2, sMapChkDeepLabel);
    DebugTextPrint(80, 68, 2, sMapChkOffText);
    DebugTextPrint(80, 32, 2, sMapChkModeNames[gMapChkWork->mode]);
    t = gUnk_0984B458[0];
    n = gMapChkWork->world * 8;
    t += 4;
    DebugTextPrint(80, 44, 2, *(const char**)(t + n));
    DebugTextPrintNumber(80, 56, 2, gMapChkWork->floor + 1);
    DebugTextPrint(80, 80, 2, sMapChkFormNames[gMapChkWork->form]);
    DebugTextPrintNumber(80, 92, 2, sMapChkForm->maxWidth);
    DebugTextPrintNumber(80, 104, 2, sMapChkForm->minHeight);
    DebugTextPrintNumber(80, 116, 2, sMapChkForm->maxHeight);
    DebugTextPrintNumber(80, 128, 2, sMapChkForm->minDepth);
    DebugTextPrintNumber(80, 140, 2, sMapChkForm->maxDepth);
    FadeStartIn(FADE_MODE_BLACK, 8);
    m4aMPlayAllStop();
}

void Mode_MapChk_1() {
    MapChkWork* e;

    DebugTextPrint(12, gMapChkWork->cursor * 12 + 32, 2, sMapChkCursorBlankText);

    if ((GetKeysRepeat() & DPAD_UP) != 0) {
        gMapChkWork->cursor = gMapChkWork->cursor == 0 ? 9 : gMapChkWork->cursor - 1;
    }

    if ((GetKeysRepeat() & DPAD_DOWN) != 0) {
        gMapChkWork->cursor = gMapChkWork->cursor > 8 ? 0 : gMapChkWork->cursor + 1;
    }

    DebugTextPrint(12, gMapChkWork->cursor * 12 + 32, 2, sMapChkCursorText);
    sMapChkRowHandlers[gMapChkWork->cursor](gMapChkWork);

    if ((GetKeysPressed() & (A_BUTTON | START_BUTTON)) != 0) {
        func_08085FB0();

        if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
            InitSoraDecks();
        }

        InitMapCardInventory();
        gMapChkUseParams = gMapChkWork->useParams;
        gGameState.progression.friendFlags |= FRIEND_FLAG_DONALD_DUCK;
        gGameState.progression.friendFlags |= FRIEND_FLAG_GOOFY;
        gGameState.progression.tutorialFlags |= 0x778;
        e = gMapChkWork;

        switch (e->mode) {
        case 1:
            gGameState.floors[e->floor].world = gUnk_0984B458[e->world][0];
            MapChkSetFloorProgress(gMapChkWork->floor, 0);
            GoToFloor(gMapChkWork->floor);
            SetFloorWorld(gUnk_0984B458[gMapChkWork->world][0]);
            gMapFloorState.flags |= FLOOR_FLAG_LOGO_SHOWN;
            EnterFloorWorld();
            RequestMapMode();
            break;
        case 2:
            gGameState.floors[e->floor].world = 0;
            MapChkSetFloorProgress(gMapChkWork->floor, 0);
            GoToFloor(gMapChkWork->floor);
            gMapFloorState.room = MAP_ROOM_ENTRANCE_HALL;
            gMapFloorState.entrySide = 5;
            RequestMapMode();
            break;
        case 3:
            gGameState.floors[gMapChkWork->floor].world = gUnk_0984B458[gMapChkWork->world][0];
            MapChkSetFloorProgress(gMapChkWork->floor, 1);
            GoToFloor(gMapChkWork->floor);
            gMapFloorState.room = MAP_ROOM_EXIT_HALL;
            gMapFloorState.entrySide = 5;
            RequestMapMode();
            break;
        case 4:
            gGameState.floors[0].world = WORLD_TRAVERSE_TOWN;
            GoToFloor(0);
            SetFloorWorld(WORLD_TRAVERSE_TOWN);
            gMapFloorState.room = MAP_ROOM_TUTORIAL;
            gMapFloorState.entrySide = 5;
            RequestMapMode();
            break;
        default:
            gGameState.floors[gMapChkWork->floor].world =
                gUnk_0984B458[gMapChkWork->world][0];
            MapChkSetFloorProgress(gMapChkWork->floor, 0);
            GoToFloor(gMapChkWork->floor);
            SetFloorWorld(gUnk_0984B458[gMapChkWork->world][0]);
            EnterFloorWorld();
            ModeRequest(&gModeMapDbg, 0);
            break;
        }
    } else if ((GetKeysPressed() & (B_BUTTON | SELECT_BUTTON)) != 0) {
        ModeRequest(&gModeDebug, 0);
    } else {
        DebugTextDraw(0);
        DebugTextClear();
    }
}

void Mode_MapChk_2() {
    DebugTextDestroy();
    EwramFree(gMapChkWork);
}
