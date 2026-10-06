/**
 * mode_pooh.c
 * 100 Acre Wood Mode
 */

#include "mode_pooh.h"
#include "sprites_pooh.h"
#include "world_types.h"
#include "prize_types.h"
#include "mode_pooh_api.h"
#include "fade.h"
#include "songs.h"
#include <string.h>
#include "anim.h"
#include "battle_actor_types.h"
#include "btl_collision.h"
#include "card_api.h"
#include "display.h"
#include "engine_math.h"
#include "game_state.h"
#include "m4a_song.h"
#include "map_runtime.h"
#include "mode.h"
#include "msg_api.h"
#include "obj_api.h"
#include "poo_api.h"
#include "pooh_actor_types.h"
#include "registration_data.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"
#include "sprite_palettes.h"

Mode gModePooh = {
    "mode_pooh",
    mode_pooh_0,
    mode_pooh_1,
    mode_pooh_2,
};

const PooHitBox gPoohHitBox = { gPoohPalette, 36, 16, 6 };

static const s8 sPoohLookOffsets[8][8] = {
    { 0, 1, 2, 2, 3, -2, -2, -1 },
    { -1, 0, 1, 2, 2, 3, -2, -2 },
    { -2, -1, 0, 1, 2, 2, 3, -2 },
    { -2, -2, -1, 0, 1, 2, 2, 3 },
    { 3, -2, -2, -1, 0, 1, 2, 2 },
    { -2, 3, 2, 2, 1, 0, -1, -2 },
    { -2, -2, 3, 2, 2, 1, 0, -1 },
    { -1, -2, -2, 3, 2, 2, 1, 0 },
};

static AnimDef sPooh00AnimDefs[5] = {
    { gPoohBb00Frames, gPoohBb00Anims, gPoohBb00Tiles, 0 },
    { gPoohFf00Frames, gPoohFf00Anims, gPoohFf00Tiles, 0 },
    { gPoohFr00Frames, gPoohFr00Anims, gPoohFr00Tiles, 0 },
    { gPoohRr00Frames, gPoohRr00Anims, gPoohRr00Tiles, 0 },
    { gPoohBr00Frames, gPoohBr00Anims, gPoohBr00Tiles, 0 },
};

static AnimDef sPooh04AnimDefs[5] = {
    { gPoohBb04Frames, gPoohBb04Anims, gPoohBb04Tiles, 0 },
    { gPoohFf04Frames, gPoohFf04Anims, gPoohFf04Tiles, 0 },
    { gPoohFl04Frames, gPoohFl04Anims, gPoohFl04Tiles, 0 },
    { gPoohLl04Frames, gPoohLl04Anims, gPoohLl04Tiles, 0 },
    { gPoohBl04Frames, gPoohBl04Anims, gPoohBl04Tiles, 0 },
};

static AnimDef sPooh04aAnimDefs[5] = {
    { gPoohBb04aFrames, gPoohBb04aAnims, gPoohBb04aTiles, 0 },
    { gPoohFf04aFrames, gPoohFf04aAnims, gPoohFf04aTiles, 0 },
    { gPoohFl04aFrames, gPoohFl04aAnims, gPoohFl04aTiles, 0 },
    { gPoohLl04aFrames, gPoohLl04aAnims, gPoohLl04aTiles, 0 },
    { gPoohBl04aFrames, gPoohBl04aAnims, gPoohBl04aTiles, 0 },
};

static AnimDef sPooh01AnimDefs[8] = {
    { gPoohBb01Frames, gPoohBb01Anims, gPoohBb01Tiles, 0 },
    { gPoohFf01Frames, gPoohFf01Anims, gPoohFf01Tiles, 0 },
    { gPoohFr01Frames, gPoohFr01Anims, gPoohFr01Tiles, 0 },
    { gPoohRr01Frames, gPoohRr01Anims, gPoohRr01Tiles, 0 },
    { gPoohBr01Frames, gPoohBr01Anims, gPoohBr01Tiles, 0 },
    { gPoohFl01Frames, gPoohFl01Anims, gPoohFl01Tiles, 0 },
    { gPoohLl01Frames, gPoohLl01Anims, gPoohLl01Tiles, 0 },
    { gPoohBl01Frames, gPoohBl01Anims, gPoohBl01Tiles, 0 },
};

static AnimDef sTrap0001AnimDefs[8] = {
    { gTrap0001bbFrames, gTrap0001bbAnims, gTrap0001bbTiles, 0 },
    { gTrap0001ffFrames, gTrap0001ffAnims, gTrap0001ffTiles, 0 },
    { gTrap0001frFrames, gTrap0001frAnims, gTrap0001frTiles, 0 },
    { gTrap0001rrFrames, gTrap0001rrAnims, gTrap0001rrTiles, 0 },
    { gTrap0001brFrames, gTrap0001brAnims, gTrap0001brTiles, 0 },
    { gTrap0001flFrames, gTrap0001flAnims, gTrap0001flTiles, 0 },
    { gTrap0001llFrames, gTrap0001llAnims, gTrap0001llTiles, 0 },
    { gTrap0001blFrames, gTrap0001blAnims, gTrap0001blTiles, 0 },
};

static AnimDef sTrap0002Anim0Def = { gTrap0002Frames, gTrap0002Anims, gTrap0002Tiles, 0 };

static AnimDef sTrap0002Anim1Def = { gTrap0002Frames, gTrap0002Anims, gTrap0002Tiles, 1 };

static AnimDef sTrap0003Anim0Def = { gTrap0003Frames, gTrap0003Anims, gTrap0003Tiles, 0 };

static AnimDef sPoohOwlDescentAnimDef = { gPoohOwlDescentFrames, gPoohOwlDescentAnims, gPoohOwlDescentTiles, 1 };

static AnimDef sPooh03AnimDefs[2] = {
    { gPoohBl03Frames, gPoohBl03Anims, gPoohBl03Tiles, 0 },
    { gPoohFl03Frames, gPoohFl03Anims, gPoohFl03Tiles, 0 },
};

static AnimDef sPooh07Anim0Defs[2] = {
    { gPoohBl07Frames, gPoohBl07Anims, gPoohBl07Tiles, 0 },
    { gPoohFl07Frames, gPoohFl07Anims, gPoohFl07Tiles, 0 },
};

static AnimDef sPooh07Anim1Defs[2] = {
    { gPoohBl07Frames, gPoohBl07Anims, gPoohBl07Tiles, 1 },
    { gPoohFl07Frames, gPoohFl07Anims, gPoohFl07Tiles, 1 },
};

static AnimDef sPoohFl05Anim0Def = { gPoohFl05Frames, gPoohFl05Anims, gPoohFl05Tiles, 0 };

static AnimDef sPoohFl05Anim1Def = { gPoohFl05Frames, gPoohFl05Anims, gPoohFl05Tiles, 1 };

static AnimDef sPoohFl05Anim2Def = { gPoohFl05Frames, gPoohFl05Anims, gPoohFl05Tiles, 2 };

static AnimDef sPoohFl05Anim3Def = { gPoohFl05Frames, gPoohFl05Anims, gPoohFl05Tiles, 3 };

static AnimDef sPoohFl05Anim4Def = { gPoohFl05Frames, gPoohFl05Anims, gPoohFl05Tiles, 4 };

static AnimDef sPoohFl05Anim5Def = { gPoohFl05Frames, gPoohFl05Anims, gPoohFl05Tiles, 5 };

static AnimDef sPoohFl05Anim9Def = { gPoohFl05Frames, gPoohFl05Anims, gPoohFl05Tiles, 9 };

static AnimDef sPoohFl06Anim1Def = { gPoohFl06Frames, gPoohFl06Anims, gPoohFl06Tiles, 1 };

static AnimDef sPoohFl06Anim2Def = { gPoohFl06Frames, gPoohFl06Anims, gPoohFl06Tiles, 2 };

static AnimDef sPoohFl06Anim3Def = { gPoohFl06Frames, gPoohFl06Anims, gPoohFl06Tiles, 3 };

static AnimDef sPoohFl09Anim0Def = { gPoohFl09Frames, gPoohFl09Anims, gPoohFl09Tiles, 0 };

static AnimDef sPoohFl09Anim1Def = { gPoohFl09Frames, gPoohFl09Anims, gPoohFl09Tiles, 1 };

static AnimDef sPoohFl09Anim2Def = { gPoohFl09Frames, gPoohFl09Anims, gPoohFl09Tiles, 2 };

static AnimDef sPooh10AnimDefs[4] = {
    { gPoohLl10Frames, gPoohLl10Anims, gPoohLl10Tiles, 0 },
    { gPoohFf10Frames, gPoohFf10Anims, gPoohFf10Tiles, 0 },
    { gPoohLl10Frames, gPoohLl10Anims, gPoohLl10Tiles, 0 },
    { gPoohLl10Frames, gPoohLl10Anims, gPoohLl10Tiles, 0 },
};

AnimDef gPoohLl10Anim0Def = { gPoohLl10Frames, gPoohLl10Anims, gPoohLl10Tiles, 0 };

static AnimDef sPooh00LookAnimDefs[5][5] = {
    {
        { gPoohBb00LlFrames, gPoohBb00LlAnims, gPoohBb00LlTiles, 0 },
        { gPoohBb00BlFrames, gPoohBb00BlAnims, gPoohBb00BlTiles, 0 },
        { gPoohBb00Frames, gPoohBb00Anims, gPoohBb00Tiles, 0 },
        { gPoohBb00BrFrames, gPoohBb00BrAnims, gPoohBb00BrTiles, 0 },
        { gPoohBb00RrFrames, gPoohBb00RrAnims, gPoohBb00RrTiles, 0 },
    },
    {
        { gPoohFf00RrFrames, gPoohFf00RrAnims, gPoohFf00RrTiles, 0 },
        { gPoohFf00FrFrames, gPoohFf00FrAnims, gPoohFf00FrTiles, 0 },
        { gPoohFf00Frames, gPoohFf00Anims, gPoohFf00Tiles, 0 },
        { gPoohFf00FlFrames, gPoohFf00FlAnims, gPoohFf00FlTiles, 0 },
        { gPoohFf00LlFrames, gPoohFf00LlAnims, gPoohFf00LlTiles, 0 },
    },
    {
        { gPoohFr00BrFrames, gPoohFr00BrAnims, gPoohFr00BrTiles, 0 },
        { gPoohFr00RrFrames, gPoohFr00RrAnims, gPoohFr00RrTiles, 0 },
        { gPoohFr00Frames, gPoohFr00Anims, gPoohFr00Tiles, 0 },
        { gPoohFr00FfFrames, gPoohFr00FfAnims, gPoohFr00FfTiles, 0 },
        { gPoohFr00FlFrames, gPoohFr00FlAnims, gPoohFr00FlTiles, 0 },
    },
    {
        { gPoohRr00BbFrames, gPoohRr00BbAnims, gPoohRr00BbTiles, 0 },
        { gPoohRr00BrFrames, gPoohRr00BrAnims, gPoohRr00BrTiles, 0 },
        { gPoohRr00Frames, gPoohRr00Anims, gPoohRr00Tiles, 0 },
        { gPoohRr00FrFrames, gPoohRr00FrAnims, gPoohRr00FrTiles, 0 },
        { gPoohRr00FfFrames, gPoohRr00FfAnims, gPoohRr00FfTiles, 0 },
    },
    {
        { gPoohBr00BlFrames, gPoohBr00BlAnims, gPoohBr00BlTiles, 0 },
        { gPoohBr00BbFrames, gPoohBr00BbAnims, gPoohBr00BbTiles, 0 },
        { gPoohBr00Frames, gPoohBr00Anims, gPoohBr00Tiles, 0 },
        { gPoohBr00RrFrames, gPoohBr00RrAnims, gPoohBr00RrTiles, 0 },
        { gPoohBr00FrFrames, gPoohBr00FrAnims, gPoohBr00FrTiles, 0 },
    },
};

static u16 sBackdropFadeColor;
static u32 sBackdropFadeAmount;
static u32 sBackdropFadeTarget;
static u32 sBackdropFadeLastAmount;
static u16 sBackdropFadeTimer;
static u32 sBackdropFadeMode;
static u8 sBackdropFadeActive;
static TaskPool sModePoohTasks;
static TaskPool sModePoohMessageTasks;
static u8 sModePoohExiting;
static u32 sModePoohExitEvent;
static u16 sModePoohMessage;
static Task* sPooPrizeTasks[12];
static TaskPool sModePoohWLogoTasks;
static Task* sWLogoTask;
static u8 sPooMapBeeVisible;
static s32 sPooAttackX;
static s32 sPooAttackY;
static s32 sPooAttackZ;

void BackdropFadeReset() {
    sBackdropFadeAmount = 0;
    sBackdropFadeTarget = 0;
    sBackdropFadeLastAmount = 0;
    sBackdropFadeTimer = 0;
    sBackdropFadeMode = 0;
    sBackdropFadeActive = 0;
}

void BackdropFadeSetColor(u16 r, u16 g, u16 b) {
    SetBackdropColor(r, g, b);
    sBackdropFadeColor = (b << 10) | (g << 5) | r;
}

void BackdropFadeUpdate() {
    u16 amt;
    u16 r;
    u16 g;
    u16 b;

    if (sBackdropFadeAmount != sBackdropFadeLastAmount) {
        amt = sBackdropFadeAmount >> 8;
        r = sBackdropFadeColor & 31;
        g = (sBackdropFadeColor >> 5) & 31;
        b = (sBackdropFadeColor >> 10) & 31;

        switch (sBackdropFadeMode) {
        case 0:
            r -= amt;
            g -= amt;
            b -= amt;

            if ((s16)r < 0) {
                r = 0;
            }

            if ((s16)g < 0) {
                g = 0;
            }

            if ((s16)b < 0) {
                b = 0;
            }

            break;
        case 1:
            if ((s16)r < amt) {
                r = amt;
            }

            if ((s16)g < amt) {
                g = amt;
            }

            if ((s16)b < amt) {
                b = amt;
            }

            break;
        case 3:
            r = amt + r;
            g -= amt;
            b -= amt;

            if ((s16)r > 31) {
                r = 31;
            }

            if ((s16)g < 0) {
                g = 0;
            }

            if ((s16)b < 0) {
                b = 0;
            }

            break;
        case 5:
            r -= amt;
            g = amt + g;
            b -= amt;

            if ((s16)r < 0) {
                r = 0;
            }

            if ((s16)g > 31) {
                g = 31;
            }

            if ((s16)b < 0) {
                b = 0;
            }

            break;
        case 4:
            r -= amt;
            g -= amt;
            b = amt + b;

            if ((s16)r < 0) {
                r = 0;
            }

            if ((s16)g < 0) {
                g = 0;
            }

            if ((s16)b > 31) {
                b = 31;
            }

            break;
        default:
            r = amt + r;
            g = amt + g;
            b = amt + b;

            if ((s16)r > 31) {
                r = 31;
            }

            if ((s16)g > 31) {
                g = 31;
            }

            if ((s16)b > 31) {
                b = 31;
            }

            break;
        }

        SetBackdropColor(r, g, b);
    }

    if (sBackdropFadeTimer != 0) {
        sBackdropFadeLastAmount = sBackdropFadeAmount;
        ApproachValue(&sBackdropFadeAmount, sBackdropFadeTarget, sBackdropFadeTimer);
        sBackdropFadeTimer--;
    } else {
        sBackdropFadeActive = 0;
    }
}

void BackdropFadeStartIn(u32 mode, u16 frames) {
    sBackdropFadeActive = 1;
    sBackdropFadeTimer = frames;
    sBackdropFadeAmount = 0x1F00;
    sBackdropFadeTarget = 0;
    sBackdropFadeLastAmount = 0;
    sBackdropFadeMode = mode;
}

void BackdropFadeStartOut(u32 mode, u16 frames) {
    sBackdropFadeActive = 1;
    sBackdropFadeTimer = frames;
    sBackdropFadeAmount = 0;
    sBackdropFadeTarget = 0x1F00;
    sBackdropFadeLastAmount = 0;
    sBackdropFadeMode = mode;
}

void BackdropFadeToOriginal(u32 mode, u16 frames) {
    sBackdropFadeActive = 1;
    sBackdropFadeTimer = frames;
    sBackdropFadeTarget = 0;
    sBackdropFadeMode = mode;
}

void BackdropFadeToAmount(u32 mode, u16 amount, u16 frames) {
    sBackdropFadeActive = 1;
    sBackdropFadeTimer = frames;
    sBackdropFadeTarget = amount << 8;
    sBackdropFadeMode = mode;
}

u8 BackdropFadeIsActive() {
    return sBackdropFadeActive;
}

void BackdropFadeFromAmount(u32 mode, u16 amount, u16 frames) {
    sBackdropFadeActive = 1;
    sBackdropFadeTimer = frames;
    sBackdropFadeAmount = amount << 8;
    sBackdropFadeLastAmount = 0;
    sBackdropFadeTarget = 0;
    sBackdropFadeMode = mode;
}

void SetPooAttackPoint(s32 x, s32 y, s32 z) {
    gPooAttackActive = 1;
    sPooAttackX = x;
    sPooAttackY = y * 2;
    sPooAttackZ = z;
}

u8 PooAttackHitsCollider(Collider* collider) {
    s32 lim;
    s32 dx;
    s32 dy;
    s32 dz;

    lim = collider->radius + 0x1400;
    dx = sPooAttackX - collider->x;

    if (dx < 0) {
        dx = collider->x - sPooAttackX;
    }

    dy = sPooAttackY - collider->y;

    if (dy < 0) {
        dy = collider->y - sPooAttackY;
    }

    dz = sPooAttackZ - collider->z;

    if (dx < lim && dy < lim && dz <= 0x1FFF && -dz < collider->height) {
        return 1;
    }

    return 0;
}

void SetPooStartPositions() {
    PooPos p;

    p.x = 0x13000;
    p.y = 0xE800;
    p.z = 0;
    SetPooStatePos2(&p);
    p.x = 0x11000;
    p.y = 0xF800;
    p.z = 0;
    SetPooStatePooh(&p, 0);
}

void SetPooReentryPositions() {
    PooPos p;

    p.x = 0xB5400;
    p.y = 0x5DE00;
    p.z = 0;
    SetPooStatePos2(&p);

    if (IsPooFlagSet(3)) {
        p.x = 0xB3400;
        p.y = 0x5EE00;
        p.z = 0;
        SetPooStatePooh(&p, 0);
    }
}

void mode_pooh_0(s32 arg) {
    s32 i;

    gGameState.world = WORLD_100_ACRE_WOOD;

    if (arg == 0) {
        ClearPooPrizesDropped();
        SetPooStartPositions();
    } else if (arg == 2) {
        ClearPooPrizesDropped();
        SetPooReentryPositions();
    }

    m4aSongNumStart(SONG_BGM_POOHGAME);
    m4aSongNumStart(SONG_BG_POO);
    SetBgMode0();
    SetupBg(3, 0, 28, 0);
    SetupBg(1, 0, 29, 0);
    SetupBg(2, 2, 30, 0);
    SetupBg(0, 3, 31, 14);
    SetBgPriority(0, 0);
    SetBgPriority(1, 1);
    SetBgPriority(2, 2);
    SetBgPriority(3, 3);
    ColliderPoolsInit();
    InitPooNodes();
    InitPoohInteractions();

    TaskPoolInit(&sModePoohTasks, 32);

    for (i = 0; i < 12; i++) {
        sPooPrizeTasks[i] = NULL;
    }

    TaskCreate(&sModePoohTasks, &gTaskDescPooSora, NULL);
    TaskCreate(&sModePoohTasks, &gTaskDescPooPiglet, NULL);

    if (!IsPooEventDone(2)) {
        TaskCreate(&sModePoohTasks, &gTaskDescPooEeyoretail, NULL);
        TaskCreate(&sModePoohTasks, &gTaskDescPooBee, NULL);
    } else {
        TaskCreate(&sModePoohTasks, &gTaskDescPooBeeAfterEvent, NULL);
    }

    TaskCreate(&sModePoohTasks, &gTaskDescPooEeyore, NULL);
    TaskCreate(&sModePoohTasks, &gTaskDescPooHoneycomb, NULL);
    TaskCreate(&sModePoohTasks, &gTaskDescPooOwl, NULL);
    TaskCreate(&sModePoohTasks, &gTaskDescPooWagon, NULL);
    TaskCreate(&sModePoohTasks, &gTaskDescPooWagonwheel, NULL);

    if (!IsPooEventDone(4)) {
        TaskCreate(&sModePoohTasks, &gTaskDescPooRabbit, NULL);
        TaskCreate(&sModePoohTasks, &gTaskDescPooCabbageborn, NULL);
    } else {
        TaskCreate(&sModePoohTasks, &gTaskDescPooRabbitAfterEvent, NULL);
        TaskCreate(&sModePoohTasks, &gTaskDescPooCabbageAfterEvent, NULL);
    }

    TaskCreate(&sModePoohTasks, &gTaskDescPooVegetable, NULL);
    TaskCreate(&sModePoohTasks, &gTaskDescPooTigger, NULL);
    TaskCreate(&sModePoohTasks, &gTaskDescPooRooFootmark, NULL);

    if (IsPooEventDone(5)) {
        if (!IsPooEventDone(1)) {
            TaskCreate(&sModePoohTasks, &gTaskDescPooRoo, NULL);
        } else {
            TaskCreate(&sModePoohTasks, &gTaskDescPooTiggerroo, NULL);
        }
    }

    TaskCreate(&sModePoohTasks, &gTaskDescPooMap, NULL);
    TaskCreate(&sModePoohTasks, &gTaskDescPooPooh, NULL);
    TaskCreate(&sModePoohTasks, &gTaskDescPooGauge, NULL);

    TaskPoolInit(&sModePoohWLogoTasks, 1);

    if (IsPooFlagSet(2)) {
        sWLogoTask = NULL;
    } else {
        sWLogoTask = TaskCreate(&sModePoohWLogoTasks, &gTaskDescWLogo, NULL);
        SetPooFlag(2);
    }

    TaskPoolInit(&sModePoohMessageTasks, 1);
    BackdropFadeReset();
    BackdropFadeSetColor(6, 31, 31);
    FadeStartIn(FADE_MODE_BLACK, 16);
    BackdropFadeStartIn(0, 16);
    sModePoohExiting = 0;
#ifdef VERSION_EU
    sModePoohMessage = 179;
#else
    sModePoohMessage = 180;
#endif
}

void mode_pooh_1() {
    UpdatePlayTime();
    SetPooMapBeeVisible(0);

    if (sModePoohExiting && !FadeIsActive()) {
#ifdef VERSION_EU
        if (sModePoohExitEvent == 195) {
#else
        if (sModePoohExitEvent == 197) {
#endif
            EnterEntranceHall();
        } else {
            RequestEventMode(sModePoohExitEvent);
        }

        return;
    }

    if (!FadeIsActive()) {
        gPooAttackActive = 0;

        if (IsTaskActive(sWLogoTask)) {
            TaskPoolUpdate(&sModePoohWLogoTasks);
        } else if (!IsMessageWindowOpen()) {
            if (sModePoohMessage == 0xFFFE) {
                if (IsMessageWindowAnswerYes()) {
#ifdef VERSION_EU
                    ExitPoohMode(195);
#else
                    ExitPoohMode(197);
#endif
                } else {
#ifdef VERSION_EU
                    sModePoohMessage = 179;
#else
                    sModePoohMessage = 180;
#endif
                }
            } else if (sModePoohMessage == 0xFFFD) {
                if (IsMessageWindowAnswerYes()) {
#ifdef VERSION_EU
                    ExitPoohMode(146);
#else
                    ExitPoohMode(148);
#endif
                } else {
#ifdef VERSION_EU
                    sModePoohMessage = 179;
#else
                    sModePoohMessage = 180;
#endif
                }
            } else {
                TaskPoolUpdate(&sModePoohTasks);
            }
        } else {
            TaskPoolUpdate(&sModePoohMessageTasks);
        }
    }

    TaskPoolDraw(&sModePoohWLogoTasks);
    TaskPoolDraw(&sModePoohMessageTasks);
    TaskPoolDraw(&sModePoohTasks);
    ColliderUpdateAll();
    BackdropFadeUpdate();
}

void mode_pooh_2() {
    TaskPoolDestroy(&sModePoohTasks);
    TaskPoolDestroy(&sModePoohMessageTasks);
    TaskPoolDestroy(&sModePoohWLogoTasks);
    FreePoohInteractions();
    m4aSongNumStop(SONG_BG_POO);
}

void ExitPoohMode(u32 event) {
    s32 i;

    if (!sModePoohExiting) {
        sModePoohExitEvent = event;

        for (i = 0; i <= 31; i++) {
            FadeSetPaletteExcluded(i, 0);
        }

        FadeStartOut(FADE_MODE_BLACK, 16);
        BackdropFadeStartOut(0, 16);
        sModePoohExiting = 1;
    }
}

void OpenPoohModeMessage(u16 message) {
    sModePoohMessage = message;

    if (message == 0xFFFD || message == 0xFFFE) {
        message = 0x45;
    }

    CreateCardMessageTask(&sModePoohMessageTasks, 0, message);
}

u16 SpawnPooPrizes(u8 kind, u8 count, s32 x, s32 y, s32 z) {
    PoohPrizeArgs args;
    u16 made;
    s32 i;
    s32 j;

    args.x = x;
    args.y = y;
    args.z = z;
    args.kind = kind;
    made = 0;
    j = 0;

    for (i = 0; i < count; i++) {
        for (; j < 12; j++) {
            if (!IsTaskActive(sPooPrizeTasks[j])) {
                sPooPrizeTasks[j] = TaskCreate(&sModePoohTasks, &gTaskDescPooPrize, &args);
                made++;
                break;
            }
        }
    }

    return made;
}

u16 CountPooPrizes() {
    u16 n;
    s32 i;

    n = 0;

    for (i = 0; i < 12; i++) {
        if (IsTaskActive(sPooPrizeTasks[i])) {
            n++;
        }
    }

    return n;
}

void SetPooMapBeeVisible(u8 visible) {
    sPooMapBeeVisible = visible;
}

u8 IsPooMapBeeVisible() {
    return sPooMapBeeVisible;
}

void SetPoohDir5Right(PoohWork* work) {
    switch (((work->angle + 16) & 0xFF) >> 5) {
    case 1:
        work->dirIndex = 4;
        work->flipped = 0;
        break;
    case 2:
        work->dirIndex = 3;
        work->flipped = 0;
        break;
    case 3:
        work->dirIndex = 2;
        work->flipped = 0;
        break;
    case 4:
        work->dirIndex = 1;
        work->flipped = 0;
        break;
    case 5:
        work->dirIndex = 2;
        work->flipped = 1;
        break;
    case 6:
        work->dirIndex = 3;
        work->flipped = 1;
        break;
    case 7:
        work->dirIndex = 4;
        work->flipped = 1;
        break;
    case 0:
    default:
        work->dirIndex = 0;
        work->flipped = 0;
        break;
    }
}

void SetPoohDir5Left(PoohWork* work) {
    switch (((work->angle + 16) & 0xFF) >> 5) {
    case 1:
        work->dirIndex = 4;
        work->flipped = 1;
        break;
    case 2:
        work->dirIndex = 3;
        work->flipped = 1;
        break;
    case 3:
        work->dirIndex = 2;
        work->flipped = 1;
        break;
    case 4:
        work->dirIndex = 1;
        work->flipped = 0;
        break;
    case 5:
        work->dirIndex = 2;
        work->flipped = 0;
        break;
    case 6:
        work->dirIndex = 3;
        work->flipped = 0;
        break;
    case 7:
        work->dirIndex = 4;
        work->flipped = 0;
        break;
    case 0:
    default:
        work->dirIndex = 0;
        work->flipped = 0;
        break;
    }
}

void SetPoohDir8(PoohWork* work) {
    work->flipped = 0;

    switch (((work->angle + 16) & 0xFF) >> 5) {
    case 0:
        work->dirIndex = 0;
        break;
    case 1:
        work->dirIndex = 4;
        break;
    case 2:
        work->dirIndex = 3;
        break;
    case 3:
        work->dirIndex = 2;
        break;
    case 4:
        work->dirIndex = 1;
        break;
    case 5:
        work->dirIndex = 5;
        break;
    case 6:
        work->dirIndex = 6;
        break;
    case 7:
        work->dirIndex = 7;
        break;
    default:
        work->dirIndex = 0;
        break;
    }
}

void SetPoohDir2(PoohWork* work) {
    switch (((work->angle + 16) & 0xFF) >> 5) {
    case 0:
    case 1:
        work->dirIndex = 0;
        work->flipped = 1;
        break;
    case 2:
        work->dirIndex = 1;
        work->flipped = 1;
        break;
    case 3:
        work->dirIndex = 1;
        work->flipped = 1;
        break;
    case 4:
    case 5:
    case 6:
        work->dirIndex = 1;
        work->flipped = 0;
        break;
    case 7:
    default:
        work->dirIndex = 0;
        work->flipped = 0;
        break;
    }
}

void SetPoohDir3(PoohWork* work) {
    if (work->angle <= 99) {
        work->dirIndex = 3;
        work->flipped = 1;
    } else if (work->angle <= 156) {
        work->dirIndex = 1;
        work->flipped = 0;
    } else {
        work->dirIndex = 3;
        work->flipped = 0;
    }
}

u8 IsAngleFacingRight(u8 angle) {
    switch (((angle + 16) & 0xFF) >> 5) {
    case 1:
    case 2:
    case 3:
        return 1;
    case 0:
    case 4:
    case 5:
    case 6:
    case 7:
        return 0;
    }

    return 0;
}

u8 GetPoohLookColumn(PoohWork* work) {
    u8 tbl[8][8];
    u32 row;
    u32 col;

    memcpy(tbl, sPoohLookOffsets, sizeof(tbl));
    row = (u32)((work->angle + 16) & 0xFF) >> 5;
    col = (u32)((work->lookAngle + 16) & 0xFF) >> 5;

    if ((s8)tbl[row][col] == 3) {
        return work->lookColumn;
    }

    return tbl[row][col] + 2;
}

void SetPoohAnimation(PoohWork* work, u32 anim) {
    AnimDef* e;
    u16 flags;

    flags = 0;
    ColliderSetRadius(&work->collider, gPoohHitBox.radius);

    if (work->animAction == anim) {
        flags = ANIM_FLAG_KEEP_FRAME;
    }

    work->animAction = anim;

    switch (anim) {
    case 3:
    case 4:
    case 7:
        flags |= ANIM_FLAG_LOOP;
        SetPoohDir8(work);
        e = &sPooh01AnimDefs[work->dirIndex];
        break;
    case 5:
    case 6:
        flags |= ANIM_FLAG_LOOP;
        SetPoohDir3(work);
        e = &sPooh10AnimDefs[work->dirIndex];
        break;
    case 16:
        SetPoohDir8(work);
        e = &sTrap0001AnimDefs[work->dirIndex];
        break;
    case 17:
        SetPoohDir5Left(work);
        e = &sPooh04AnimDefs[work->dirIndex];
        break;
    case 18:
        SetPoohDir5Left(work);
        e = &sPooh04aAnimDefs[work->dirIndex];
        break;
    case 19:
        SetPoohDir2(work);
        e = &sPooh03AnimDefs[work->dirIndex];
        break;
    case 20:
        work->hideShadow = 1;
        SetPoohDir2(work);
        e = &sPooh07Anim0Defs[work->dirIndex];
        break;
    case 21:
        work->hideShadow = 1;
        SetPoohDir2(work);

        if (IsPooEventDone(6) || work->leavingWagon || (work->dirIndex == 5 && work->flipped == 0)) {
            e = &sPooh07Anim0Defs[work->dirIndex];
        } else {
            e = &sPooh07Anim1Defs[work->dirIndex];
        }

        break;
    case 36:
        work->flipped = 0;
        e = &sTrap0002Anim0Def;
        break;
    case 37:
        work->flipped = 0;
        e = &sTrap0002Anim1Def;
        break;
    case 23:
        work->flipped = IsAngleFacingRight(work->angle);
        e = &sPoohFl05Anim0Def;
        work->hideShadow = 1;
        break;
    case 32:
        work->flipped = 0;
        e = &sPoohFl05Anim9Def;
        work->hideShadow = 1;
        break;
    case 33:
        work->flipped = 0;
        e = &sPoohFl09Anim0Def;
        break;
    case 34:
        work->flipped = 0;
        e = &sPoohFl09Anim1Def;
        break;
    case 35:
        work->flipped = 0;
        e = &sPoohFl09Anim2Def;
        break;
    case 24:
        work->flipped = IsAngleFacingRight(work->angle);
        e = &sPoohFl05Anim1Def;
        work->hideShadow = 1;
        break;
    case 25:
        work->flipped = IsAngleFacingRight(work->angle);
        e = &sPoohFl05Anim2Def;
        work->hideShadow = 1;
        break;
    case 26:
        ColliderSetRadius(&work->collider, 14);
        flags |= ANIM_FLAG_LOOP;
        work->flipped = IsAngleFacingRight(work->angle);
        e = &sPoohFl05Anim3Def;
        work->hideShadow = 1;
        break;
    case 27:
        work->flipped = IsAngleFacingRight(work->angle);
        e = &sPoohFl05Anim4Def;
        work->hideShadow = 1;
        break;
    case 28:
        work->flipped = IsAngleFacingRight(work->angle);
        e = &sPoohFl05Anim5Def;
        work->hideShadow = 1;
        break;
    case 29:
        work->flipped = IsAngleFacingRight(work->angle);
        e = &sPoohFl06Anim1Def;
        break;
    case 30:
        flags |= ANIM_FLAG_LOOP;
        work->flipped = IsAngleFacingRight(work->angle);
        e = &sPoohFl06Anim2Def;
        break;
    case 31:
        work->flipped = IsAngleFacingRight(work->angle);
        e = &sPoohFl06Anim3Def;
        break;
    case 38:
    case 39:
        flags |= ANIM_FLAG_LOOP;
        work->flipped = 0;
        e = &sTrap0003Anim0Def;
        break;
    case 22:
        flags |= ANIM_FLAG_LOOP;
        work->flipped = 0;
        e = &sPoohOwlDescentAnimDef;
        break;
    case 0:
    case 1:
    case 2:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        flags |= ANIM_FLAG_LOOP;
        SetPoohDir5Right(work);
        work->lookColumn = GetPoohLookColumn(work);
        e = &sPooh00LookAnimDefs[work->dirIndex][GetPoohLookColumn(work)];
        break;
    default:
        flags |= ANIM_FLAG_LOOP;
        SetPoohDir5Right(work);
        e = &sPooh00AnimDefs[work->dirIndex];
        break;
    }

    AnimChangeWithTables(&work->anim, e->animId, flags, e->anims, e->gfxTable);
    SetObjTileSource(work->tiles, e->tiles);
}

u8 IsWithinPoohRadius(u16 x, u16 y, u16 px, u16 py) {
    if (x - gPoohHitBox.radius < px && px < x + gPoohHitBox.radius &&
        y - gPoohHitBox.radius < py && py < y + gPoohHitBox.radius) {
        return 1;
    }

    return 0;
}
