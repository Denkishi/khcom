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

extern UnkStruct_0203C590 gUnk_0203C590;

const char gDebugMenuTextUs_0984B5F8[] = "\202s\202t\202s\202n\202q\202h\202`\202k";

const char gDebugMenuTextUs_0984B60C[] = "\202f\202n\202`\202k\201@\201@\201@\201@";

const char gDebugMenuTextUs_0984B620[] = "\202r\202s\202`\202q\202s\201@\201@\201@";

const char gDebugMenuTextUs_0984B634[] = "\202e\202h\202d\202k\202c\201@\201@\201@";

const char gDebugMenuTextUs_0984B648[] = "\202c\202d\202a\202t\202f\201@\201@\201@";

const char gDebugMenuTextUs_0984B65C[] = "\202e\202t\202m\202m\202d\202k\201@";

const char gDebugMenuTextUs_0984B66C[] = "\202r\202s\202`\202f\202d\201@\201@";

const char gDebugMenuTextUs_0984B67C[] = "\202g\202d\202w\202`\202f\202n\202m";

const char gDebugMenuTextUs_0984B68C[] = "\202b\202k\202h\202e\202e\201@\201@";

const char gDebugMenuTextUs_0984B69C[] = "\202o\202`\202r\202r\201@\201@\201@";

const char gDebugMenuTextUs_0984B6AC[] = "\202s\202n\202v\202d\202q\201@\201@";

const char gDebugMenuTextUs_0984B6BC[] = "\202r\202l\202`\202k\202k\201@\201@";

const char gDebugMenuTextUs_0984B6CC[] = "\202e\202k\202`\202s\201@\201@\201@";

const char gDebugMenuTextUs_0984B6DC[] = "\202v\202h\202c\202d\201@\201@\201@";

const char gDebugMenuTextUs_0984B6EC[] = "\202g\202h\202f\202g\201@\201@\201@";

const char gDebugMenuTextUs_0984B6FC[] = "\202k\202n\202v\201@\201@\201@\201@";

const char gDebugMenuTextUs_0984B70C[] = "\202q\202`\202m\202c\202n\202l\201@";

const char gDebugMenuTextUs_0984B71C[] = "\202c\202d\202e\202`\202t\202k\202s";

const char gUnk_0984B72C[32] = "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377";

const char gUnk_0984B74C[] = "\202n\202m\201@";

const char gUnk_0984B754[] = "\202n\202e\202e";

const char gUnk_0984B75C[] = "\201i\202a\201@\201@\201@\201j";

const char gUnk_0984B76C[] = "\201i\202a\201|\201|\201|\201j";

const char gUnk_0984B77C[] = "\202t\202c\201F\202r\202d\202k\202d\202b\202s\201@\202k\202q\201F\202r\202d\202s\201@\202`\201F\202r\202s\202`\202q\202s";

const char gUnk_0984B7B0[] = "\202l\202n\202c\202d\201@\201F";

const char gUnk_0984B7C0[] = "\202v\202n\202q\202k\202c\201F";

const char gUnk_0984B7D0[] = "\202e\202k\202n\202n\202q\201F";

const char gUnk_0984B7E0[] = "\202o\202`\202q\202`\202l\201F";

const char gUnk_0984B7F0[] = "\202e\202n\202q\202l\201@\201F";

const char gUnk_0984B800[] = "\202v\202h\202c\202d\201@\201F";

const char gUnk_0984B810[] = "\202g\202h\202f\202g\201@\201F";

const char gUnk_0984B820[] = "\202c\202d\202d\202o\201@\201F";

const char gUnk_0984B830[] = "\201@";

const char gUnk_0984B834[] = "\201\204";
extern const u8 gUnk_0984B458[][8];

static MapChkWork* gMapChkWork;
static UnkStruct_0203C7B0* gUnk_02034F18;

const char* gUnk_09EF6960[] = {
    gDebugMenuTextUs_0984B648,
    gDebugMenuTextUs_0984B634,
    gDebugMenuTextUs_0984B620,
    gDebugMenuTextUs_0984B60C,
    gDebugMenuTextUs_0984B5F8,
};

const char* gUnk_09EF6974[] = {
    gDebugMenuTextUs_0984B71C,
    gDebugMenuTextUs_0984B70C,
    gDebugMenuTextUs_0984B6FC,
    gDebugMenuTextUs_0984B6EC,
    gDebugMenuTextUs_0984B6DC,
    gDebugMenuTextUs_0984B6CC,
    gDebugMenuTextUs_0984B6BC,
    gDebugMenuTextUs_0984B6AC,
    gDebugMenuTextUs_0984B69C,
    gDebugMenuTextUs_0984B68C,
    gDebugMenuTextUs_0984B67C,
    gDebugMenuTextUs_0984B66C,
    gDebugMenuTextUs_0984B65C,
};

void (*gUnk_09EF69A8[10])(MapChkWork*) = {
    func_080DE2A4,
    func_080DE2FC,
    func_080DE35C,
    func_080DE50C,
    func_080DE3E8,
    func_080DE4A4,
    func_080DE534,
    func_080DE5B0,
    func_080DE62C,
    func_080DE6A8,
};

Mode gModeMapChk = {
    "Mode_MapChk",
    (ModeInitFunc)Mode_MapChk_0,
    Mode_MapChk_1,
    Mode_MapChk_2,
};

void func_080DDEC8(u8* p, u8 a) {
    if (p[5] != a) {
        p[5] = a;

        if (a != 0) {
            func_0805FCB0(80, 68, 2, gUnk_0984B74C);
        } else {
            func_0805FCB0(80, 68, 2, gUnk_0984B754);
        }
    }
}

void func_080DDF04(u8 a, u8 b) {
    if ((gGameState.flags & 8) != 0) {
        if (b != 0) {
            switch (a) {
            case 0:
                gUnk_0203C590.unk_00 = 1;
                break;
            case 1:
                gUnk_0203C590.unk_00 = 3;
                break;
            case 2:
                gUnk_0203C590.unk_00 = 5;
                break;
            case 3:
                gUnk_0203C590.unk_00 = 7;
                break;
            case 4:
                gUnk_0203C590.unk_00 = 9;
                break;
            case 5:
                gUnk_0203C590.unk_00 = 11;
                break;
            case 6:
                gUnk_0203C590.unk_00 = 13;
                break;
            case 7:
                gUnk_0203C590.unk_00 = 15;
                break;
            case 8:
                gUnk_0203C590.unk_00 = 17;
                break;
            case 9:
                gUnk_0203C590.unk_00 = 19;
                break;
            case 10:
                gUnk_0203C590.unk_00 = 22;
                break;
            case 11:
                gUnk_0203C590.unk_00 = 24;
                break;
            }
        } else {
            switch (a) {
            case 0:
                gUnk_0203C590.unk_00 = 0;
                break;
            case 1:
                gUnk_0203C590.unk_00 = 2;
                break;
            case 2:
                gUnk_0203C590.unk_00 = 4;
                break;
            case 3:
                gUnk_0203C590.unk_00 = 6;
                break;
            case 4:
                gUnk_0203C590.unk_00 = 8;
                break;
            case 5:
                gUnk_0203C590.unk_00 = 10;
                break;
            case 6:
                gUnk_0203C590.unk_00 = 12;
                break;
            case 7:
                gUnk_0203C590.unk_00 = 14;
                break;
            case 8:
                gUnk_0203C590.unk_00 = 16;
                break;
            case 9:
                gUnk_0203C590.unk_00 = 18;
                break;
            case 10:
                gUnk_0203C590.unk_00 = 20;
                break;
            case 11:
                gUnk_0203C590.unk_00 = 23;
                break;
            }
        }
    } else {
        if (b != 0) {
            switch (a) {
            case 0:
                gUnk_0203C590.unk_00 = 1;
                break;
            case 1:
                gUnk_0203C590.unk_00 = 3;
                break;
            case 2:
                gUnk_0203C590.unk_00 = 5;
                break;
            case 3:
                gUnk_0203C590.unk_00 = 7;
                break;
            case 4:
                gUnk_0203C590.unk_00 = 9;
                break;
            case 5:
                gUnk_0203C590.unk_00 = 11;
                break;
            case 6:
                gUnk_0203C590.unk_00 = 13;
                break;
            case 7:
                gUnk_0203C590.unk_00 = 15;
                break;
            case 8:
                gUnk_0203C590.unk_00 = 17;
                break;
            case 9:
                gUnk_0203C590.unk_00 = 19;
                break;
            case 10:
                gUnk_0203C590.unk_00 = 21;
                break;
            case 11:
                gUnk_0203C590.unk_00 = 23;
                break;
            case 12:
                gUnk_0203C590.unk_00 = 27;
                break;
            }
        } else {
            switch (a) {
            case 0:
                gUnk_0203C590.unk_00 = 0;
                break;
            case 1:
                gUnk_0203C590.unk_00 = 2;
                break;
            case 2:
                gUnk_0203C590.unk_00 = 4;
                break;
            case 3:
                gUnk_0203C590.unk_00 = 6;
                break;
            case 4:
                gUnk_0203C590.unk_00 = 8;
                break;
            case 5:
                gUnk_0203C590.unk_00 = 10;
                break;
            case 6:
                gUnk_0203C590.unk_00 = 12;
                break;
            case 7:
                gUnk_0203C590.unk_00 = 14;
                break;
            case 8:
                gUnk_0203C590.unk_00 = 16;
                break;
            case 9:
                gUnk_0203C590.unk_00 = 18;
                break;
            case 10:
                gUnk_0203C590.unk_00 = 20;
                break;
            case 11:
                gUnk_0203C590.unk_00 = 22;
                break;
            case 12:
                gUnk_0203C590.unk_00 = 25;
                break;
            }
        }
    }
}
void func_080DE2A4(MapChkWork* p) {
    if ((GetKeysRepeat() & DPAD_LEFT) != 0) {
        p->unk_01 = p->unk_01 == 0 ? 4 : p->unk_01 - 1;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0) {
        p->unk_01 = p->unk_01 > 3 ? 0 : p->unk_01 + 1;
    }

    func_0805FCB0(80, 32, 2, gUnk_09EF6960[p->unk_01]);
}
void func_080DE2FC(MapChkWork* p) {
    u8 v = p->unk_02;
    const u8* t;
    s32 n;

    if ((GetKeysRepeat() & DPAD_LEFT) != 0) {
        p->unk_02 = p->unk_02 == 0 ? 12 : p->unk_02 - 1;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0) {
        p->unk_02 = p->unk_02 > 11 ? 0 : p->unk_02 + 1;
    }

    if (v != p->unk_02) {
        t = gUnk_0984B458[0];
        n = p->unk_02 * 8;
        t += 4;
        func_0805FCB0(80, 44, 2, *(const char**)(t + n));
    }
}
void func_080DE35C(MapChkWork* p) {
    if ((GetKeysRepeat() & DPAD_LEFT) != 0) {
        p->unk_03 = p->unk_03 == 0 ? 13 : p->unk_03 - 1;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0) {
        p->unk_03 = p->unk_03 > 12 ? 0 : p->unk_03 + 1;
    }

    func_0805FC04(80, 56, 2, p->unk_03 + 1);
    func_0805FCB0(112, 56, 2, gUnk_0984B75C);

    if (12 - p->unk_03 > 0) {
        func_0805FC04(128, 56, 2, 12 - p->unk_03);
    } else {
        func_0805FCB0(112, 56, 2, gUnk_0984B76C);
    }
}
void func_080DE3E8(MapChkWork* p) {
    u8 v = p->unk_04;

    if ((GetKeysRepeat() & DPAD_LEFT) != 0) {
        p->unk_04 = p->unk_04 == 0 ? 12 : p->unk_04 - 1;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0) {
        p->unk_04 = p->unk_04 > 11 ? 0 : p->unk_04 + 1;
    }

    if (v != p->unk_04) {
        func_080E5510(p->unk_04 + 15);
        func_0805FCB0(80, 80, 2, gUnk_09EF6974[p->unk_04]);
        func_0805FC04(80, 92, 2, gUnk_02034F18->unk_02);
        func_0805FC04(80, 104, 2, gUnk_02034F18->unk_03);
        func_0805FC04(80, 116, 2, gUnk_02034F18->unk_04);
        func_0805FC04(80, 128, 2, gUnk_02034F18->unk_05);
        func_0805FC04(80, 140, 2, gUnk_02034F18->unk_06);
        func_080DDEC8((u8*)p, 1);
    }
}
void func_080DE4A4(MapChkWork* p) {
    u8 v = gUnk_02034F18->unk_02;

    if ((GetKeysRepeat() & DPAD_LEFT) != 0 && v > 8) {
        v--;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0 && v <= 47) {
        v++;
    }

    if (gUnk_02034F18->unk_02 != v) {
        gUnk_02034F18->unk_02 = v;
        gUnk_02034F18->unk_01 = v;
        func_0805FC04(80, 92, 2, gUnk_02034F18->unk_02);
        func_080DDEC8((u8*)p, 1);
    }
}
void func_080DE50C(MapChkWork* p) {
    if ((GetKeysRepeat() & (DPAD_RIGHT | DPAD_LEFT)) != 0) {
        func_080DDEC8((u8*)p, p->unk_05 == 0 ? 1 : 0);
    }
}
void func_080DE534(MapChkWork* p) {
    u8 v = gUnk_02034F18->unk_03;

    if ((GetKeysRepeat() & DPAD_LEFT) != 0 && v > 2) {
        v--;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0 && v <= 9) {
        v++;
    }

    if (gUnk_02034F18->unk_03 != v) {
        gUnk_02034F18->unk_03 = v;
        func_0805FC04(80, 104, 2, gUnk_02034F18->unk_03);

        if (gUnk_02034F18->unk_04 < v) {
            gUnk_02034F18->unk_04 = v;
            func_0805FC04(80, 116, 2, gUnk_02034F18->unk_04);
        }

        func_080DDEC8((u8*)p, 1);
    }
}
void func_080DE5B0(MapChkWork* p) {
    u8 v = gUnk_02034F18->unk_04;

    if ((GetKeysRepeat() & DPAD_LEFT) != 0 && v > 2) {
        v--;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0 && v <= 9) {
        v++;
    }

    if (gUnk_02034F18->unk_04 != v) {
        gUnk_02034F18->unk_04 = v;
        func_0805FC04(80, 116, 2, gUnk_02034F18->unk_04);

        if (gUnk_02034F18->unk_03 > v) {
            gUnk_02034F18->unk_03 = v;
            func_0805FC04(80, 104, 2, gUnk_02034F18->unk_03);
        }

        func_080DDEC8((u8*)p, 1);
    }
}
void func_080DE62C(MapChkWork* p) {
    u8 v = gUnk_02034F18->unk_05;

    if ((GetKeysRepeat() & DPAD_LEFT) != 0 && v > 3) {
        v--;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0 && v <= 47) {
        v++;
    }

    if (gUnk_02034F18->unk_05 != v) {
        gUnk_02034F18->unk_05 = v;
        func_0805FC04(80, 128, 2, gUnk_02034F18->unk_05);

        if (gUnk_02034F18->unk_06 < v) {
            gUnk_02034F18->unk_06 = v;
            func_0805FC04(80, 140, 2, gUnk_02034F18->unk_06);
        }

        func_080DDEC8((u8*)p, 1);
    }
}
void func_080DE6A8(MapChkWork* p) {
    u8 v = gUnk_02034F18->unk_06;

    if ((GetKeysRepeat() & DPAD_LEFT) != 0 && v > 3) {
        v--;
    }

    if ((GetKeysRepeat() & DPAD_RIGHT) != 0 && v <= 47) {
        v++;
    }

    if (gUnk_02034F18->unk_06 != v) {
        gUnk_02034F18->unk_06 = v;
        func_0805FC04(80, 140, 2, gUnk_02034F18->unk_06);

        if (gUnk_02034F18->unk_05 > v) {
            gUnk_02034F18->unk_05 = v;
            func_0805FC04(80, 128, 2, gUnk_02034F18->unk_05);
        }

        func_080DDEC8((u8*)p, 1);
    }
}
void Mode_MapChk_0(void) {
    const u8* t;
    s32 n;

    gMapChkWork = (MapChkWork*)EwramAlloc(8);
    SaveLoadHeader();
    gUnk_0203C584 = 0;
    gMapChkWork->unk_00 = 0;
    gMapChkWork->unk_01 = 0;
    gMapChkWork->unk_02 = 0;
    gMapChkWork->unk_03 = 1;
    gMapChkWork->unk_04 = 0;
    gMapChkWork->unk_05 = 0;
    gGameState.unk_1B8 = 0;
    func_080E5510(gMapChkWork->unk_04);
    gUnk_02034F18 = &gUnk_0203C7B0;
    SetBgMode0();
    SetupBg(0, 0, 15, 0);
    EnableBg(0);
    func_0805FA8C(0, 0x5400, 0x500);
    func_0805FA60(0, gUnk_0984B72C, 32, 15);
    func_0805FCB0(0, 0, 2, gUnk_0984B77C);
    func_0805FCB0(24, 32, 2, gUnk_0984B7B0);
    func_0805FCB0(24, 44, 2, gUnk_0984B7C0);
    func_0805FCB0(24, 56, 2, gUnk_0984B7D0);
    func_0805FCB0(24, 68, 2, gUnk_0984B7E0);
    func_0805FCB0(24, 80, 2, gUnk_0984B7F0);
    func_0805FCB0(24, 92, 2, gUnk_0984B800);
    func_0805FCB0(24, 104, 2, gUnk_0984B810);
    func_0805FCB0(24, 128, 2, gUnk_0984B820);
    func_0805FCB0(80, 68, 2, gUnk_0984B754);
    func_0805FCB0(80, 32, 2, gUnk_09EF6960[gMapChkWork->unk_01]);
    t = gUnk_0984B458[0];
    n = gMapChkWork->unk_02 * 8;
    t += 4;
    func_0805FCB0(80, 44, 2, *(const char**)(t + n));
    func_0805FC04(80, 56, 2, gMapChkWork->unk_03 + 1);
    func_0805FCB0(80, 80, 2, gUnk_09EF6974[gMapChkWork->unk_04]);
    func_0805FC04(80, 92, 2, gUnk_02034F18->unk_02);
    func_0805FC04(80, 104, 2, gUnk_02034F18->unk_03);
    func_0805FC04(80, 116, 2, gUnk_02034F18->unk_04);
    func_0805FC04(80, 128, 2, gUnk_02034F18->unk_05);
    func_0805FC04(80, 140, 2, gUnk_02034F18->unk_06);
    FadeStartIn(0, 8);
    m4aMPlayAllStop();
}
void Mode_MapChk_1(void) {
    MapChkWork* e;

    func_0805FCB0(12, gMapChkWork->unk_00 * 12 + 32, 2, gUnk_0984B830);

    if ((GetKeysRepeat() & DPAD_UP) != 0) {
        gMapChkWork->unk_00 = gMapChkWork->unk_00 == 0 ? 9 : gMapChkWork->unk_00 - 1;
    }

    if ((GetKeysRepeat() & DPAD_DOWN) != 0) {
        gMapChkWork->unk_00 = gMapChkWork->unk_00 > 8 ? 0 : gMapChkWork->unk_00 + 1;
    }

    func_0805FCB0(12, gMapChkWork->unk_00 * 12 + 32, 2, gUnk_0984B834);
    gUnk_09EF69A8[gMapChkWork->unk_00](gMapChkWork);

    if ((GetKeysPressed() & (A_BUTTON | START_BUTTON)) != 0) {
        func_08085FB0();

        if ((gGameState.flags & 8) == 0) {
            func_08085C3C();
        }

        InitMapCardInventory();
        gUnk_0203C584 = gMapChkWork->unk_05;
        gGameState.progression.unk_84 |= 2;
        gGameState.progression.unk_84 |= 1;
        gGameState.progression.unk_82 |= 0x778;
        e = gMapChkWork;

        switch (e->unk_01) {
        case 1:
            gGameState.floors[e->unk_03].world = gUnk_0984B458[e->unk_02][0];
            func_080DDF04(gMapChkWork->unk_03, 0);
            func_080DF990(gMapChkWork->unk_03);
            func_080DFA18(gUnk_0984B458[gMapChkWork->unk_02][0]);
            gUnk_0203C590.unk_02 |= 0x10;
            func_080DFA3C();
            func_080E04EC();
            break;
        case 2:
            gGameState.floors[e->unk_03].world = 0;
            func_080DDF04(gMapChkWork->unk_03, 0);
            func_080DF990(gMapChkWork->unk_03);
            gUnk_0203C590.unk_06 = 0xFE;
            gUnk_0203C590.unk_07 = 5;
            func_080E04EC();
            break;
        case 3:
            gGameState.floors[gMapChkWork->unk_03].world = gUnk_0984B458[gMapChkWork->unk_02][0];
            func_080DDF04(gMapChkWork->unk_03, 1);
            func_080DF990(gMapChkWork->unk_03);
            gUnk_0203C590.unk_06 = 0xFD;
            gUnk_0203C590.unk_07 = 5;
            func_080E04EC();
            break;
        case 4:
            gGameState.floors[0].world = WORLD_TRAVERSE_TOWN;
            func_080DF990(0);
            func_080DFA18(10);
            gUnk_0203C590.unk_06 = 0xFC;
            gUnk_0203C590.unk_07 = 5;
            func_080E04EC();
            break;
        default:
            gGameState.floors[gMapChkWork->unk_03].world =
                gUnk_0984B458[gMapChkWork->unk_02][0];
            func_080DDF04(gMapChkWork->unk_03, 0);
            func_080DF990(gMapChkWork->unk_03);
            func_080DFA18(gUnk_0984B458[gMapChkWork->unk_02][0]);
            func_080DFA3C();
            ModeRequest(&gModeMapDbg, 0);
            break;
        }
    } else if ((GetKeysPressed() & (B_BUTTON | SELECT_BUTTON)) != 0) {
        ModeRequest(&gModeDebug, 0);
    } else {
        func_080605A4(0);
        func_08060598();
    }
}

void Mode_MapChk_2(void) {
    func_080609A0();
    EwramFree(gMapChkWork);
}
