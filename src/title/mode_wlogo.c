#include "mode_wlogo.h"
#include "registration_data.h"
#include "mode_sio.h"
#include "monsgage.h"
#include "jiminy_data.h"
#include "gba/keys.h"
#include "battle_backgrounds.h"
#include "link_menus.h"
#include "fade.h"
#include "common_text.h"
#include "display.h"
#include "jiminy_inline_text_data.h"
#include "key.h"
#include "map_api.h"
#include "mode.h"
#include "obj_api.h"
#include "poo_api.h"
#include "taskpool.h"
#include "text.h"
#include "text_types.h"
#include "types.h"

void WLogoInitWorldSelect();
void WLogoStartLogo(u8 a);

static u8* sWorldNames[13] = {
#if defined(VERSION_US)
    (u8*)gUnk_0815A534,
    (u8*)gUnk_0815A59A,
    (u8*)gUnk_0815A57C,
    (u8*)gUnk_0815A5AA,
    (u8*)gUnk_0815A5BE,
    (u8*)gUnk_0815A54A,
    (u8*)gUnk_0815A5D4,
    (u8*)gUnk_0815A62A,
    (u8*)gUnk_0815A56C,
    (u8*)gUnk_0815A518,
    (u8*)gUnk_0815A5F2,
    (u8*)gUnk_0815A60E,
    (u8*)gUnk_0815A64A,
#elif defined(VERSION_JP)
    gUnkJp_0814E59C,
    gUnkJp_0814E5AC,
    gUnkJp_0814E5B8,
    gUnkJp_0814E5E4,
    gUnkJp_0814E5F4,
    gUnkJp_0814E5CC,
    gUnkJp_0814E618,
    gUnkJp_0814E62C,
    gUnkJp_0814E590,
    gUnkJp_0814E57C,
    gUnkJp_0814E604,
    gUnkJp_0814E644,
    gUnkJp_0814E658,
#elif defined(VERSION_EU)
    (u8*)&gUnkEu_0888E410,
    (u8*)&gUnkEu_0888E450,
    (u8*)&gUnkEu_0888E4C0,
    (u8*)&gUnkEu_0888E578,
    (u8*)&gUnkEu_0888E5DC,
    (u8*)&gUnkEu_0888E530,
    (u8*)&gUnkEu_0888E6BC,
    (u8*)&gUnkEu_0888E72C,
    (u8*)&gUnkEu_0888E3A0,
    (u8*)&gUnkEu_0888E364,
    (u8*)&gUnkEu_0888E654,
    (u8*)&gUnkEu_0888E78C,
    (u8*)&gUnkEu_0888E804,
#endif
};

static u8 sWLogoWorldIds[13] = {
    4,
    5,
    6,
    2,
    7,
    3,
    8,
    9,
    1,
    10,
    0,
    11,
    12,
};

static u8 sWLogoState;
static s8 sWLogoWorld;
static u8 sWLogoTimer;
static u8 sWLogoNameLength;
#ifdef VERSION_EU
static TextSlot sWLogoNameSlots[80];
#else
static TextSlot sWLogoNameSlots[20];
#endif
static struct ObjPalette* sWLogoNamePalette;
static TaskPool sModeWLogoTasks;
static Task* sModeWLogoTask;
static TaskPool sTaskWLogoTasks;
static Task* sTaskWLogoTask;

void mode_wLogo_0(s32 arg) {
    sWLogoWorld = arg;
    WLogoInitWorldSelect();
}

void mode_wLogo_1() {
    u8* p;

    switch (sWLogoState) {
    case 0:
        DrawTextSlots(35, 75, sWLogoNameSlots, sWLogoNamePalette, 20, sWLogoNameLength);

        if (GetKeysPressed() & DPAD_LEFT) {
            sWLogoWorld--;

            if (sWLogoWorld < 0) {
                sWLogoWorld = 12;
            }

#ifdef VERSION_EU
            sWLogoNameLength = LoadTextSlots(eu_0805E924(sWorldNames[sWLogoWorld]), sWLogoNameSlots);
#else
            sWLogoNameLength = LoadTextSlots(sWorldNames[sWLogoWorld], sWLogoNameSlots);
#endif
        }

        if (GetKeysPressed() & DPAD_RIGHT) {
            sWLogoWorld++;

            if (sWLogoWorld > 12) {
                sWLogoWorld = 0;
            }

            p = &sWLogoNameLength;
#ifdef VERSION_EU
            *p = LoadTextSlots(eu_0805E924(sWorldNames[sWLogoWorld]), sWLogoNameSlots);
#else
            *p = LoadTextSlots(sWorldNames[sWLogoWorld], sWLogoNameSlots);
#endif
        }

        if (GetKeysPressed() & A_BUTTON) {
            FadeStartOut(FADE_MODE_BLACK, 16);
            DisableBg(0);
            DisableBg(1);
            sWLogoState++;
        }

        if (GetKeysPressed() & B_BUTTON) {
            ModeRequest(&gModeDebug, 0);
        }

        break;
    case 1:
        WLogoStartLogo(sWLogoWorldIds[sWLogoWorld]);
        sWLogoState++;
        break;
    case 2:
        if (IsTaskActive(sModeWLogoTask)) {
            TaskPoolUpdate(&sModeWLogoTasks);
            TaskPoolDraw(&sModeWLogoTasks);
        } else {
            sWLogoState++;
        }

        break;
    case 3:
        sWLogoTimer++;

        if (sWLogoTimer > 10) {
            ModeRequest(&gModeWLogo, sWLogoWorld);
        }

        break;
    }
}

void mode_wLogo_2() {
    FreeTextSlots(sWLogoNameSlots, 20);
    ReleaseObjPalette(sWLogoNamePalette);

    if (sWLogoState != 0) {
        if (sWLogoState == 3) {
            TaskPoolDestroy(&sModeWLogoTasks);
        }
    }
}

void WLogoInitWorldSelect() {
    u8* p;
    FadeStartIn(FADE_MODE_BLACK, 16);
    SetBgMode0();
    SetupBg(1, 2, 31, 0);
    SetBgSize(1, 0);
    LoadBgTiles(1, gUnk_096ACA44, 0xBC0);
    LoadBgPalette(1, gUnk_096FBA04, 0x40);
    LoadBgMap(1, gUnk_096F5464, 0x800);
    DisableBg(0);
    EnableBg(1);
    sWLogoState = 0;
    sWLogoTimer = 0;
    InitTextSlots(sWLogoNameSlots, 20);
    p = &sWLogoNameLength;
#ifdef VERSION_EU
    *p = LoadTextSlots(eu_0805E924(sWorldNames[sWLogoWorld]), sWLogoNameSlots);
#else
    *p = LoadTextSlots(sWorldNames[sWLogoWorld], sWLogoNameSlots);
#endif
    sWLogoNamePalette = LoadObjPalette(gUnk_096FBCC4, 32);
}

void WLogoStartLogo(u8 a) {
    FadeStartIn(FADE_MODE_BLACK, 16);
    SetBgMode1();
    SetupBg(0, 0, 7, 14);
    SetBgPriority(0, 0);
    SetBgOverflow(0, 1);
    SetBgSize(0, 0);
    SetupBg(2, 2, 24, 0);
    SetBgPriority(2, 2);
    SetBgOverflow(2, 1);
    SetBgSize(2, 0x8000);
    TaskPoolInit(&sModeWLogoTasks, 2);

    switch (a) {
    case 4:
        LoadBgTiles(2, gUnk_08C84824, 0x4000);
        LoadBgPalette(2, gUnk_08F68904, 0xC0);
#ifdef VERSION_EU
        eu_080059F4(2, gUnk_08EF2384);
#else
        LoadBgMap(2, gUnk_08EF2384, 0x1000);
#endif
        sModeWLogoTask = TaskCreate(&sModeWLogoTasks, &gTaskDescWlogoWon, 0);
        break;
    case 5:
        LoadBgTiles(2, gUnk_08C8C824, 0x4000);
        LoadBgPalette(2, gUnk_08F68A84, 0x100);
#ifdef VERSION_EU
        eu_080059F4(2, gUnk_08EF4384);
#else
        LoadBgMap(2, gUnk_08EF4384, 0x1000);
#endif
        sModeWLogoTask = TaskCreate(&sModeWLogoTasks, &gTaskDescWlogoMons, 0);
        break;
    case 6:
        LoadBgTiles(2, gUnk_08C94824, 0x4000);
        LoadBgPalette(2, gUnk_08F68C84, 0xE0);
#ifdef VERSION_EU
        eu_080059F4(2, gUnk_08EF6384);
#else
        LoadBgMap(2, gUnk_08EF6384, 0x1000);
#endif
        sModeWLogoTask = TaskCreate(&sModeWLogoTasks, &gTaskDescWlogoHwt, 0);
        break;
    case 2:
        LoadBgTiles(2, gUnk_08C88824, 0x4000);
        LoadBgPalette(2, gUnk_08F689C4, 0xC0);
#ifdef VERSION_EU
        eu_080059F4(2, gUnk_08EF3384);
#else
        LoadBgMap(2, gUnk_08EF3384, 0x1000);
#endif
        sModeWLogoTask = TaskCreate(&sModeWLogoTasks, &gTaskDescWlogoAtl, 0);
        break;
    case 7:
        LoadBgTiles(2, gUnk_08C98824, 0x3EC0);
        LoadBgPalette(2, gUnk_08F68D64, 0x140);
#ifdef VERSION_EU
        eu_080059F4(2, gUnk_08EF7384);
#else
        LoadBgMap(2, gUnk_08EF7384, 0x1000);
#endif
        sModeWLogoTask = TaskCreate(&sModeWLogoTasks, &gTaskDescWlogoNvl, 0);
        break;
    case 3:
        LoadBgTiles(2, gUnk_08C7C824, 0x4000);
        LoadBgPalette(2, gUnk_08F686E4, 0xE0);
#ifdef VERSION_EU
        eu_080059F4(2, gUnk_08EF0384);
#else
        LoadBgMap(2, gUnk_08EF0384, 0x1000);
#endif
        sModeWLogoTask = TaskCreate(&sModeWLogoTasks, &gTaskDescWlogoCol, 0);
        break;
    case 8:
        LoadBgTiles(2, gUnk_08CA06E4, 0x4000);
        LoadBgPalette(2, gUnk_08F68FC4, 0xE0);
#ifdef VERSION_EU
        eu_080059F4(2, gUnk_08EF9384);
#else
        LoadBgMap(2, gUnk_08EF9384, 0x1000);
#endif
        sModeWLogoTask = TaskCreate(&sModeWLogoTasks, &gTaskDescWlogoHlw, 0);
        break;
    case 9:
        LoadBgTiles(2, gUnk_08C9C6E4, 0x4000);
        LoadBgPalette(2, gUnk_08F68EA4, 0x120);
#ifdef VERSION_EU
        eu_080059F4(2, gUnk_08EF8384);
#else
        LoadBgMap(2, gUnk_08EF8384, 0x1000);
#endif
        sModeWLogoTask = TaskCreate(&sModeWLogoTasks, &gTaskDescWlogoDil, 0);
        break;
    case 1:
        LoadBgTiles(2, gUnk_08C90824, 0x4000);
        LoadBgPalette(2, gUnk_08F68B84, 0x100);
#ifdef VERSION_EU
        eu_080059F4(2, gUnk_08EF5384);
#else
        LoadBgMap(2, gUnk_08EF5384, 0x1000);
#endif
        sModeWLogoTask = TaskCreate(&sModeWLogoTasks, &gTaskDescWlogoAgr, 0);
        break;
    case 10:
        LoadBgTiles(2, gUnk_08C78824, 0x4000);
        LoadBgPalette(2, gUnk_08F68624, 0xC0);
#ifdef VERSION_EU
        eu_080059F4(2, gUnk_08EEF384);
#else
        LoadBgMap(2, gUnk_08EEF384, 0x1000);
#endif
        sModeWLogoTask = TaskCreate(&sModeWLogoTasks, &gTaskDescWlogoTvt, 0);
        break;
    case 0:
        LoadBgTiles(2, gUnk_08C84824, 0x4000);
        LoadBgPalette(2, gUnk_08F68904, 0xC0);
#ifdef VERSION_EU
        eu_080059F4(2, gUnk_08EF2384);
#else
        LoadBgMap(2, gUnk_08EF2384, 0x1000);
#endif
        sModeWLogoTask = TaskCreate(&sModeWLogoTasks, &gTaskDescWlogoPoo, 0);
        break;
    case 11:
        LoadBgTiles(2, gUnk_08CA46E4, 0x4000);
        LoadBgPalette(2, gUnk_08F690A4, 0x140);
#ifdef VERSION_EU
        eu_080059F4(2, gUnk_08EFA384);
#else
        LoadBgMap(2, gUnk_08EFA384, 0x1000);
#endif
        sModeWLogoTask = TaskCreate(&sModeWLogoTasks, &gTaskDescWlogoTt, 0);
        break;
    case 12:
        LoadBgTiles(2, gUnk_08CA86E4, 0x4000);
        LoadBgPalette(2, gUnk_08F691E4, 0xE0);
#ifdef VERSION_EU
        eu_080059F4(2, gUnk_08EFB384);
#else
        LoadBgMap(2, gUnk_08EFB384, 0x1000);
#endif
        sModeWLogoTask = TaskCreate(&sModeWLogoTasks, &gTaskDescWlogoBks, 0);
        break;
    }

    SetBgAffine(2, 0, 256, 256, 0x10000, 0x16800);
}

void task_wLogo_0(WLogoTaskWork* work, u8 arg) {
    work->worldId = arg;
    work->cameraOffsetY = -0x5A00;
    work->timer = 0;
    TaskPoolInit(&sTaskWLogoTasks, 2);

    switch (work->worldId) {
    case 4:
        sTaskWLogoTask = TaskCreate(&sTaskWLogoTasks, &gTaskDescWlogoWon, 0);
        break;
    case 5:
        sTaskWLogoTask = TaskCreate(&sTaskWLogoTasks, &gTaskDescWlogoMons, 0);
        break;
    case 6:
        sTaskWLogoTask = TaskCreate(&sTaskWLogoTasks, &gTaskDescWlogoHwt, 0);
        break;
    case 2:
        sTaskWLogoTask = TaskCreate(&sTaskWLogoTasks, &gTaskDescWlogoAtl, 0);
        break;
    case 7:
        sTaskWLogoTask = TaskCreate(&sTaskWLogoTasks, &gTaskDescWlogoNvl, 0);
        break;
    case 3:
        sTaskWLogoTask = TaskCreate(&sTaskWLogoTasks, &gTaskDescWlogoCol, 0);
        break;
    case 8:
        sTaskWLogoTask = TaskCreate(&sTaskWLogoTasks, &gTaskDescWlogoHlw, 0);
        break;
    case 1:
        sTaskWLogoTask = TaskCreate(&sTaskWLogoTasks, &gTaskDescWlogoAgr, 0);
        break;
    case 9:
        sTaskWLogoTask = TaskCreate(&sTaskWLogoTasks, &gTaskDescWlogoDil, 0);
        break;
    case 10:
        sTaskWLogoTask = TaskCreate(&sTaskWLogoTasks, &gTaskDescWlogoTvt, 0);
        break;
    case 0:
        sTaskWLogoTask = TaskCreate(&sTaskWLogoTasks, &gTaskDescWlogoPoo, 0);
        break;
    case 11:
        sTaskWLogoTask = TaskCreate(&sTaskWLogoTasks, &gTaskDescWlogoTt, 0);
        break;
    case 12:
        sTaskWLogoTask = TaskCreate(&sTaskWLogoTasks, &gTaskDescWlogoBks, 0);
        break;
    default:
        sTaskWLogoTask = TaskCreate(&sTaskWLogoTasks, &gTaskDescWlogoWon, 0);
        break;
    }

    if (work->worldId == 0) {
        MovePooCamera(0, work->cameraOffsetY);
    } else {
        MapMoveCameraTarget(0, work->cameraOffsetY);
    }
}

u8 task_wLogo_1(WLogoTaskWork* work) {
    if (work->worldId == 0) {
        work->timer++;

        if (work->timer <= 314) {
            MovePooCamera(0, 76);
        }
    } else {
        work->timer++;

        if (work->timer <= 314) {
            MapMoveCameraTarget(0, 76);
        }
    }

    if (IsTaskActive(sTaskWLogoTask) != 0) {
        TaskPoolUpdate(&sTaskWLogoTasks);
        TaskPoolDraw(&sTaskWLogoTasks);
        return 1;
    }

    return 0;
}

void task_wLogo_2(WLogoTaskWork* work) {
}

void task_wLogo_3(WLogoTaskWork* work) {
    TaskPoolDestroy(&sTaskWLogoTasks);
    SetBgBlend(0, 0, 16);
}

Mode gModeWLogo = {
    "mode_wLogo",
    mode_wLogo_0,
    mode_wLogo_1,
    mode_wLogo_2,
};

TaskDesc gTaskDescWLogo = {
    "task_wLogo",
    (TaskInitFunc)task_wLogo_0,
    (TaskUpdateFunc)task_wLogo_1,
    (TaskDrawFunc)task_wLogo_2,
    (TaskDestroyFunc)task_wLogo_3,
    sizeof(WLogoTaskWork),
};
