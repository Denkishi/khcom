#include "mode_pooh.h"
#include "sprites_pooh.h"
#include "world_types.h"

Mode gModePooh = {
    "mode_pooh",
    mode_pooh_0,
    mode_pooh_1,
    mode_pooh_2,
};

const PooHitBox gPoohHitBox = { gPoohPalette, 36, 16, 6, 0 };

const s8 gPoohLookOffsets[8][8] = {
    { 0, 1, 2, 2, 3, -2, -2, -1 },
    { -1, 0, 1, 2, 2, 3, -2, -2 },
    { -2, -1, 0, 1, 2, 2, 3, -2 },
    { -2, -2, -1, 0, 1, 2, 2, 3 },
    { 3, -2, -2, -1, 0, 1, 2, 2 },
    { -2, 3, 2, 2, 1, 0, -1, -2 },
    { -2, -2, 3, 2, 2, 1, 0, -1 },
    { -1, -2, -2, 3, 2, 2, 1, 0 },
};

AnimDef gPooh00AnimDefs[5] = {
    { gPoohBb00Frames, gPoohBb00Anims, gPoohBb00Tiles, 0, { 0, 0, 0 } },
    { gPoohFf00Frames, gPoohFf00Anims, gPoohFf00Tiles, 0, { 0, 0, 0 } },
    { gPoohFr00Frames, gPoohFr00Anims, gPoohFr00Tiles, 0, { 0, 0, 0 } },
    { gPoohRr00Frames, gPoohRr00Anims, gPoohRr00Tiles, 0, { 0, 0, 0 } },
    { gPoohBr00Frames, gPoohBr00Anims, gPoohBr00Tiles, 0, { 0, 0, 0 } },
};

AnimDef gPooh04AnimDefs[5] = {
    { gPoohBb04Frames, gPoohBb04Anims, gPoohBb04Tiles, 0, { 0, 0, 0 } },
    { gPoohFf04Frames, gPoohFf04Anims, gPoohFf04Tiles, 0, { 0, 0, 0 } },
    { gPoohFl04Frames, gPoohFl04Anims, gPoohFl04Tiles, 0, { 0, 0, 0 } },
    { gPoohLl04Frames, gPoohLl04Anims, gPoohLl04Tiles, 0, { 0, 0, 0 } },
    { gPoohBl04Frames, gPoohBl04Anims, gPoohBl04Tiles, 0, { 0, 0, 0 } },
};

AnimDef gPooh04aAnimDefs[5] = {
    { gPoohBb04aFrames, gPoohBb04aAnims, gPoohBb04aTiles, 0, { 0, 0, 0 } },
    { gPoohFf04aFrames, gPoohFf04aAnims, gPoohFf04aTiles, 0, { 0, 0, 0 } },
    { gPoohFl04aFrames, gPoohFl04aAnims, gPoohFl04aTiles, 0, { 0, 0, 0 } },
    { gPoohLl04aFrames, gPoohLl04aAnims, gPoohLl04aTiles, 0, { 0, 0, 0 } },
    { gPoohBl04aFrames, gPoohBl04aAnims, gPoohBl04aTiles, 0, { 0, 0, 0 } },
};

AnimDef gPooh01AnimDefs[8] = {
    { gPoohBb01Frames, gPoohBb01Anims, gPoohBb01Tiles, 0, { 0, 0, 0 } },
    { gPoohFf01Frames, gPoohFf01Anims, gPoohFf01Tiles, 0, { 0, 0, 0 } },
    { gPoohFr01Frames, gPoohFr01Anims, gPoohFr01Tiles, 0, { 0, 0, 0 } },
    { gPoohRr01Frames, gPoohRr01Anims, gPoohRr01Tiles, 0, { 0, 0, 0 } },
    { gPoohBr01Frames, gPoohBr01Anims, gPoohBr01Tiles, 0, { 0, 0, 0 } },
    { gPoohFl01Frames, gPoohFl01Anims, gPoohFl01Tiles, 0, { 0, 0, 0 } },
    { gPoohLl01Frames, gPoohLl01Anims, gPoohLl01Tiles, 0, { 0, 0, 0 } },
    { gPoohBl01Frames, gPoohBl01Anims, gPoohBl01Tiles, 0, { 0, 0, 0 } },
};

AnimDef gTrap0001AnimDefs[8] = {
    { gTrap0001bbFrames, gTrap0001bbAnims, gTrap0001bbTiles, 0, { 0, 0, 0 } },
    { gTrap0001ffFrames, gTrap0001ffAnims, gTrap0001ffTiles, 0, { 0, 0, 0 } },
    { gTrap0001frFrames, gTrap0001frAnims, gTrap0001frTiles, 0, { 0, 0, 0 } },
    { gTrap0001rrFrames, gTrap0001rrAnims, gTrap0001rrTiles, 0, { 0, 0, 0 } },
    { gTrap0001brFrames, gTrap0001brAnims, gTrap0001brTiles, 0, { 0, 0, 0 } },
    { gTrap0001flFrames, gTrap0001flAnims, gTrap0001flTiles, 0, { 0, 0, 0 } },
    { gTrap0001llFrames, gTrap0001llAnims, gTrap0001llTiles, 0, { 0, 0, 0 } },
    { gTrap0001blFrames, gTrap0001blAnims, gTrap0001blTiles, 0, { 0, 0, 0 } },
};

AnimDef gTrap0002Anim0Def = { gTrap0002Frames, gTrap0002Anims, gTrap0002Tiles, 0, { 0, 0, 0 } };

AnimDef gTrap0002Anim1Def = { gTrap0002Frames, gTrap0002Anims, gTrap0002Tiles, 1, { 0, 0, 0 } };

AnimDef gTrap0003Anim0Def = { gTrap0003Frames, gTrap0003Anims, gTrap0003Tiles, 0, { 0, 0, 0 } };

AnimDef gPoohOwlDescentAnimDef = { gUnk_09EF5824, gUnk_09EF583C, gUnk_09724C1C, 1, { 0, 0, 0 } };

AnimDef gPooh03AnimDefs[2] = {
    { gPoohBl03Frames, gPoohBl03Anims, gPoohBl03Tiles, 0, { 0, 0, 0 } },
    { gPoohFl03Frames, gPoohFl03Anims, gPoohFl03Tiles, 0, { 0, 0, 0 } },
};

AnimDef gPooh07Anim0Defs[2] = {
    { gPoohBl07Frames, gPoohBl07Anims, gPoohBl07Tiles, 0, { 0, 0, 0 } },
    { gPoohFl07Frames, gPoohFl07Anims, gPoohFl07Tiles, 0, { 0, 0, 0 } },
};

AnimDef gPooh07Anim1Defs[2] = {
    { gPoohBl07Frames, gPoohBl07Anims, gPoohBl07Tiles, 1, { 0, 0, 0 } },
    { gPoohFl07Frames, gPoohFl07Anims, gPoohFl07Tiles, 1, { 0, 0, 0 } },
};

AnimDef gPoohFl05Anim0Def = { gPoohFl05Frames, gPoohFl05Anims, gPoohFl05Tiles, 0, { 0, 0, 0 } };

AnimDef gPoohFl05Anim1Def = { gPoohFl05Frames, gPoohFl05Anims, gPoohFl05Tiles, 1, { 0, 0, 0 } };

AnimDef gPoohFl05Anim2Def = { gPoohFl05Frames, gPoohFl05Anims, gPoohFl05Tiles, 2, { 0, 0, 0 } };

AnimDef gPoohFl05Anim3Def = { gPoohFl05Frames, gPoohFl05Anims, gPoohFl05Tiles, 3, { 0, 0, 0 } };

AnimDef gPoohFl05Anim4Def = { gPoohFl05Frames, gPoohFl05Anims, gPoohFl05Tiles, 4, { 0, 0, 0 } };

AnimDef gPoohFl05Anim5Def = { gPoohFl05Frames, gPoohFl05Anims, gPoohFl05Tiles, 5, { 0, 0, 0 } };

AnimDef gPoohFl05Anim9Def = { gPoohFl05Frames, gPoohFl05Anims, gPoohFl05Tiles, 9, { 0, 0, 0 } };

AnimDef gPoohFl06Anim1Def = { gPoohFl06Frames, gPoohFl06Anims, gPoohFl06Tiles, 1, { 0, 0, 0 } };

AnimDef gPoohFl06Anim2Def = { gPoohFl06Frames, gPoohFl06Anims, gPoohFl06Tiles, 2, { 0, 0, 0 } };

AnimDef gPoohFl06Anim3Def = { gPoohFl06Frames, gPoohFl06Anims, gPoohFl06Tiles, 3, { 0, 0, 0 } };

AnimDef gPoohFl09Anim0Def = { gPoohFl09Frames, gPoohFl09Anims, gPoohFl09Tiles, 0, { 0, 0, 0 } };

AnimDef gPoohFl09Anim1Def = { gPoohFl09Frames, gPoohFl09Anims, gPoohFl09Tiles, 1, { 0, 0, 0 } };

AnimDef gPoohFl09Anim2Def = { gPoohFl09Frames, gPoohFl09Anims, gPoohFl09Tiles, 2, { 0, 0, 0 } };

AnimDef gPooh10AnimDefs[4] = {
    { gPoohLl10Frames, gPoohLl10Anims, gPoohLl10Tiles, 0, { 0, 0, 0 } },
    { gPoohFf10Frames, gPoohFf10Anims, gPoohFf10Tiles, 0, { 0, 0, 0 } },
    { gPoohLl10Frames, gPoohLl10Anims, gPoohLl10Tiles, 0, { 0, 0, 0 } },
    { gPoohLl10Frames, gPoohLl10Anims, gPoohLl10Tiles, 0, { 0, 0, 0 } },
};

AnimDef gPoohLl10Anim0Def = { gPoohLl10Frames, gPoohLl10Anims, gPoohLl10Tiles, 0, { 0, 0, 0 } };

AnimDef gPooh00LookAnimDefs[5][5] = {
    {
        { gPoohBb00LlFrames, gPoohBb00LlAnims, gPoohBb00LlTiles, 0, { 0, 0, 0 } },
        { gPoohBb00BlFrames, gPoohBb00BlAnims, gPoohBb00BlTiles, 0, { 0, 0, 0 } },
        { gPoohBb00Frames, gPoohBb00Anims, gPoohBb00Tiles, 0, { 0, 0, 0 } },
        { gPoohBb00BrFrames, gPoohBb00BrAnims, gPoohBb00BrTiles, 0, { 0, 0, 0 } },
        { gPoohBb00RrFrames, gPoohBb00RrAnims, gPoohBb00RrTiles, 0, { 0, 0, 0 } },
    },
    {
        { gPoohFf00RrFrames, gPoohFf00RrAnims, gPoohFf00RrTiles, 0, { 0, 0, 0 } },
        { gPoohFf00FrFrames, gPoohFf00FrAnims, gPoohFf00FrTiles, 0, { 0, 0, 0 } },
        { gPoohFf00Frames, gPoohFf00Anims, gPoohFf00Tiles, 0, { 0, 0, 0 } },
        { gPoohFf00FlFrames, gPoohFf00FlAnims, gPoohFf00FlTiles, 0, { 0, 0, 0 } },
        { gPoohFf00LlFrames, gPoohFf00LlAnims, gPoohFf00LlTiles, 0, { 0, 0, 0 } },
    },
    {
        { gPoohFr00BrFrames, gPoohFr00BrAnims, gPoohFr00BrTiles, 0, { 0, 0, 0 } },
        { gPoohFr00RrFrames, gPoohFr00RrAnims, gPoohFr00RrTiles, 0, { 0, 0, 0 } },
        { gPoohFr00Frames, gPoohFr00Anims, gPoohFr00Tiles, 0, { 0, 0, 0 } },
        { gPoohFr00FfFrames, gPoohFr00FfAnims, gPoohFr00FfTiles, 0, { 0, 0, 0 } },
        { gPoohFr00FlFrames, gPoohFr00FlAnims, gPoohFr00FlTiles, 0, { 0, 0, 0 } },
    },
    {
        { gPoohRr00BbFrames, gPoohRr00BbAnims, gPoohRr00BbTiles, 0, { 0, 0, 0 } },
        { gPoohRr00BrFrames, gPoohRr00BrAnims, gPoohRr00BrTiles, 0, { 0, 0, 0 } },
        { gPoohRr00Frames, gPoohRr00Anims, gPoohRr00Tiles, 0, { 0, 0, 0 } },
        { gPoohRr00FrFrames, gPoohRr00FrAnims, gPoohRr00FrTiles, 0, { 0, 0, 0 } },
        { gPoohRr00FfFrames, gPoohRr00FfAnims, gPoohRr00FfTiles, 0, { 0, 0, 0 } },
    },
    {
        { gPoohBr00BlFrames, gPoohBr00BlAnims, gPoohBr00BlTiles, 0, { 0, 0, 0 } },
        { gPoohBr00BbFrames, gPoohBr00BbAnims, gPoohBr00BbTiles, 0, { 0, 0, 0 } },
        { gPoohBr00Frames, gPoohBr00Anims, gPoohBr00Tiles, 0, { 0, 0, 0 } },
        { gPoohBr00RrFrames, gPoohBr00RrAnims, gPoohBr00RrTiles, 0, { 0, 0, 0 } },
        { gPoohBr00FrFrames, gPoohBr00FrAnims, gPoohBr00FrTiles, 0, { 0, 0, 0 } },
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
static Task* gWLogoTask;
static u8 sPooMapBeeVisible;
static s32 sPooAttackX;
static s32 sPooAttackY;
static s32 sPooAttackZ;

void BackdropFadeReset(void) {
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

void BackdropFadeUpdate(void) {
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

void BackdropFadeStartIn(u32 a, u16 b) {
    sBackdropFadeActive = 1;
    sBackdropFadeTimer = b;
    sBackdropFadeAmount = 0x1F00;
    sBackdropFadeTarget = 0;
    sBackdropFadeLastAmount = 0;
    sBackdropFadeMode = a;
}

void BackdropFadeStartOut(u32 a, u16 b) {
    sBackdropFadeActive = 1;
    sBackdropFadeTimer = b;
    sBackdropFadeAmount = 0;
    sBackdropFadeTarget = 0x1F00;
    sBackdropFadeLastAmount = 0;
    sBackdropFadeMode = a;
}

void BackdropFadeToOriginal(u32 a, u16 b) {
    sBackdropFadeActive = 1;
    sBackdropFadeTimer = b;
    sBackdropFadeTarget = 0;
    sBackdropFadeMode = a;
}

void BackdropFadeToAmount(u32 a, u16 b, u16 c) {
    sBackdropFadeActive = 1;
    sBackdropFadeTimer = c;
    sBackdropFadeTarget = b << 8;
    sBackdropFadeMode = a;
}

u8 BackdropFadeIsActive(void) {
    return sBackdropFadeActive;
}

void BackdropFadeFromAmount(u32 a, u16 b, u16 c) {
    sBackdropFadeActive = 1;
    sBackdropFadeTimer = c;
    sBackdropFadeAmount = b << 8;
    sBackdropFadeLastAmount = 0;
    sBackdropFadeTarget = 0;
    sBackdropFadeMode = a;
}

void SetPooAttackPoint(s32 a, s32 b, s32 c) {
    gPooAttackActive = 1;
    sPooAttackX = a;
    sPooAttackY = b * 2;
    sPooAttackZ = c;
}

u8 PooAttackHitsCollider(Collider* p) {
    s32 lim;
    s32 dx;
    s32 dy;
    s32 dz;

    lim = p->radius + 0x1400;
    dx = sPooAttackX - p->x;
    if (dx < 0) {
        dx = p->x - sPooAttackX;
    }
    dy = sPooAttackY - p->y;
    if (dy < 0) {
        dy = p->y - sPooAttackY;
    }
    dz = sPooAttackZ - p->z;
    if (dx < lim && dy < lim && dz <= 0x1FFF && -dz < p->height) {
        return 1;
    }
    return 0;
}

void SetPooStartPositions(void) {
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

void SetPooReentryPositions(void) {
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
        sPooPrizeTasks[i] = 0;
    }

    TaskCreate(&sModePoohTasks, &gTaskDescPooSora, 0);
    TaskCreate(&sModePoohTasks, &gTaskDescPooPiglet, 0);

    if (!IsPooEventDone(2)) {
        TaskCreate(&sModePoohTasks, &gTaskDescPooEeyoretail, 0);
        TaskCreate(&sModePoohTasks, &gTaskDescPooBee, 0);
    } else {
        TaskCreate(&sModePoohTasks, &gTaskDescPooBeeAfterEvent, 0);
    }

    TaskCreate(&sModePoohTasks, &gTaskDescPooEeyore, 0);
    TaskCreate(&sModePoohTasks, &gTaskDescPooHoneycomb, 0);
    TaskCreate(&sModePoohTasks, &gTaskDescPooOwl, 0);
    TaskCreate(&sModePoohTasks, &gTaskDescPooWagon, 0);
    TaskCreate(&sModePoohTasks, &gTaskDescPooWagonwheel, 0);

    if (!IsPooEventDone(4)) {
        TaskCreate(&sModePoohTasks, &gTaskDescPooRabbit, 0);
        TaskCreate(&sModePoohTasks, &gTaskDescPooCabbageborn, 0);
    } else {
        TaskCreate(&sModePoohTasks, &gTaskDescPooRabbitAfterEvent, 0);
        TaskCreate(&sModePoohTasks, &gTaskDescPooCabbageAfterEvent, 0);
    }

    TaskCreate(&sModePoohTasks, &gTaskDescPooVegetable, 0);
    TaskCreate(&sModePoohTasks, &gTaskDescPooTigger, 0);
    TaskCreate(&sModePoohTasks, &gTaskDescPooRooFootmark, 0);

    if (IsPooEventDone(5)) {
        if (!IsPooEventDone(1)) {
            TaskCreate(&sModePoohTasks, &gTaskDescPooRoo, 0);
        } else {
            TaskCreate(&sModePoohTasks, &gTaskDescPooTiggerroo, 0);
        }
    }

    TaskCreate(&sModePoohTasks, &gTaskDescPooMap, 0);
    TaskCreate(&sModePoohTasks, &gTaskDescPooPooh, 0);
    TaskCreate(&sModePoohTasks, &gTaskDescPooGauge, 0);

    TaskPoolInit(&sModePoohWLogoTasks, 1);

    if (IsPooFlagSet(2)) {
        gWLogoTask = 0;
    } else {
        gWLogoTask = TaskCreate(&sModePoohWLogoTasks, &gTaskDescWLogo, 0);
        SetPooFlag(2);
    }

    TaskPoolInit(&sModePoohMessageTasks, 1);
    BackdropFadeReset();
    BackdropFadeSetColor(6, 31, 31);
    FadeStartIn(0, 16);
    BackdropFadeStartIn(0, 16);
    sModePoohExiting = 0;
#ifdef VERSION_EU
    sModePoohMessage = 179;
#else
    sModePoohMessage = 180;
#endif
}

void mode_pooh_1(void) {
    UpdatePlayTime();
    SetPooMapBeeVisible(0);

    if (sModePoohExiting != 0 && !FadeIsActive()) {
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

    if (FadeIsActive() == 0) {
        gPooAttackActive = 0;

        if (IsTaskActive(gWLogoTask)) {
            TaskPoolUpdate(&sModePoohWLogoTasks);
        } else if (IsMessageWindowOpen() == 0) {
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

void mode_pooh_2(void) {
    TaskPoolDestroy(&sModePoohTasks);
    TaskPoolDestroy(&sModePoohMessageTasks);
    TaskPoolDestroy(&sModePoohWLogoTasks);
    FreePoohInteractions();
    m4aSongNumStop(SONG_BG_POO);
}

void ExitPoohMode(u32 a) {
    s32 i;

    if (sModePoohExiting == 0) {
        sModePoohExitEvent = a;

        for (i = 0; i <= 31; i++) {
            FadeSetPaletteExcluded(i, 0);
        }
        FadeStartOut(0, 16);
        BackdropFadeStartOut(0, 16);
        sModePoohExiting = 1;
    }
}

void OpenPoohModeMessage(u16 a) {
    sModePoohMessage = a;

    if (a == 0xFFFD || a == 0xFFFE) {
        a = 0x45;
    }
    CreateCardMessageTask(&sModePoohMessageTasks, 0, a);
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

u16 CountPooPrizes(void) {
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

void SetPooMapBeeVisible(u8 a) {
    sPooMapBeeVisible = a;
}

u8 IsPooMapBeeVisible(void) {
    return sPooMapBeeVisible;
}

void SetPoohDir5Right(PoohWork* w) {
    switch (((w->angle + 16) & 0xFF) >> 5) {
    case 1:
        w->dirIndex = 4;
        w->flipped = 0;
        break;
    case 2:
        w->dirIndex = 3;
        w->flipped = 0;
        break;
    case 3:
        w->dirIndex = 2;
        w->flipped = 0;
        break;
    case 4:
        w->dirIndex = 1;
        w->flipped = 0;
        break;
    case 5:
        w->dirIndex = 2;
        w->flipped = 1;
        break;
    case 6:
        w->dirIndex = 3;
        w->flipped = 1;
        break;
    case 7:
        w->dirIndex = 4;
        w->flipped = 1;
        break;
    case 0:
    default:
        w->dirIndex = 0;
        w->flipped = 0;
        break;
    }
}

void SetPoohDir5Left(PoohWork* w) {
    switch (((w->angle + 16) & 0xFF) >> 5) {
    case 1:
        w->dirIndex = 4;
        w->flipped = 1;
        break;
    case 2:
        w->dirIndex = 3;
        w->flipped = 1;
        break;
    case 3:
        w->dirIndex = 2;
        w->flipped = 1;
        break;
    case 4:
        w->dirIndex = 1;
        w->flipped = 0;
        break;
    case 5:
        w->dirIndex = 2;
        w->flipped = 0;
        break;
    case 6:
        w->dirIndex = 3;
        w->flipped = 0;
        break;
    case 7:
        w->dirIndex = 4;
        w->flipped = 0;
        break;
    case 0:
    default:
        w->dirIndex = 0;
        w->flipped = 0;
        break;
    }
}

void SetPoohDir8(PoohWork* w) {
    w->flipped = 0;

    switch (((w->angle + 16) & 0xFF) >> 5) {
    case 0:
        w->dirIndex = 0;
        break;
    case 1:
        w->dirIndex = 4;
        break;
    case 2:
        w->dirIndex = 3;
        break;
    case 3:
        w->dirIndex = 2;
        break;
    case 4:
        w->dirIndex = 1;
        break;
    case 5:
        w->dirIndex = 5;
        break;
    case 6:
        w->dirIndex = 6;
        break;
    case 7:
        w->dirIndex = 7;
        break;
    default:
        w->dirIndex = 0;
        break;
    }
}

void SetPoohDir2(PoohWork* w) {
    switch (((w->angle + 16) & 0xFF) >> 5) {
    case 0:
    case 1:
        w->dirIndex = 0;
        w->flipped = 1;
        break;
    case 2:
        w->dirIndex = 1;
        w->flipped = 1;
        break;
    case 3:
        w->dirIndex = 1;
        w->flipped = 1;
        break;
    case 4:
    case 5:
    case 6:
        w->dirIndex = 1;
        w->flipped = 0;
        break;
    case 7:
    default:
        w->dirIndex = 0;
        w->flipped = 0;
        break;
    }
}

void SetPoohDir3(PoohWork* w) {
    if (w->angle <= 99) {
        w->dirIndex = 3;
        w->flipped = 1;
    } else if (w->angle <= 156) {
        w->dirIndex = 1;
        w->flipped = 0;
    } else {
        w->dirIndex = 3;
        w->flipped = 0;
    }
}

u8 IsAngleFacingRight(u8 a) {
    switch (((a + 16) & 0xFF) >> 5) {
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

u8 GetPoohLookColumn(PoohWork* w) {
    u8 tbl[8][8];
    u32 row;
    u32 col;

    memcpy(tbl, gPoohLookOffsets, sizeof(tbl));
    row = (u32)((w->angle + 16) & 0xFF) >> 5;
    col = (u32)((w->lookAngle + 16) & 0xFF) >> 5;
    if ((s8)tbl[row][col] == 3) {
        return w->lookColumn;
    }
    return tbl[row][col] + 2;
}

void SetPoohAnimation(PoohWork* w, u32 anim) {
    AnimDef* e;
    u16 flags;

    flags = 0;
    ColliderSetRadius(&w->collider, gPoohHitBox.radius);

    if (w->animAction == anim) {
        flags = 4;
    }
    w->animAction = anim;

    switch (anim) {
    case 3:
    case 4:
    case 7:
        flags |= 1;
        SetPoohDir8(w);
        e = &gPooh01AnimDefs[w->dirIndex];
        break;
    case 5:
    case 6:
        flags |= 1;
        SetPoohDir3(w);
        e = &gPooh10AnimDefs[w->dirIndex];
        break;
    case 16:
        SetPoohDir8(w);
        e = &gTrap0001AnimDefs[w->dirIndex];
        break;
    case 17:
        SetPoohDir5Left(w);
        e = &gPooh04AnimDefs[w->dirIndex];
        break;
    case 18:
        SetPoohDir5Left(w);
        e = &gPooh04aAnimDefs[w->dirIndex];
        break;
    case 19:
        SetPoohDir2(w);
        e = &gPooh03AnimDefs[w->dirIndex];
        break;
    case 20:
        w->hideShadow = 1;
        SetPoohDir2(w);
        e = &gPooh07Anim0Defs[w->dirIndex];
        break;
    case 21:
        w->hideShadow = 1;
        SetPoohDir2(w);

        if (IsPooEventDone(6) != 0 || w->leavingWagon != 0 || (w->dirIndex == 5 && w->flipped == 0)) {
            e = &gPooh07Anim0Defs[w->dirIndex];
        } else {
            e = &gPooh07Anim1Defs[w->dirIndex];
        }
        break;
    case 36:
        w->flipped = 0;
        e = &gTrap0002Anim0Def;
        break;
    case 37:
        w->flipped = 0;
        e = &gTrap0002Anim1Def;
        break;
    case 23:
        w->flipped = IsAngleFacingRight(w->angle);
        e = &gPoohFl05Anim0Def;
        w->hideShadow = 1;
        break;
    case 32:
        w->flipped = 0;
        e = &gPoohFl05Anim9Def;
        w->hideShadow = 1;
        break;
    case 33:
        w->flipped = 0;
        e = &gPoohFl09Anim0Def;
        break;
    case 34:
        w->flipped = 0;
        e = &gPoohFl09Anim1Def;
        break;
    case 35:
        w->flipped = 0;
        e = &gPoohFl09Anim2Def;
        break;
    case 24:
        w->flipped = IsAngleFacingRight(w->angle);
        e = &gPoohFl05Anim1Def;
        w->hideShadow = 1;
        break;
    case 25:
        w->flipped = IsAngleFacingRight(w->angle);
        e = &gPoohFl05Anim2Def;
        w->hideShadow = 1;
        break;
    case 26:
        ColliderSetRadius(&w->collider, 14);
        flags |= 1;
        w->flipped = IsAngleFacingRight(w->angle);
        e = &gPoohFl05Anim3Def;
        w->hideShadow = 1;
        break;
    case 27:
        w->flipped = IsAngleFacingRight(w->angle);
        e = &gPoohFl05Anim4Def;
        w->hideShadow = 1;
        break;
    case 28:
        w->flipped = IsAngleFacingRight(w->angle);
        e = &gPoohFl05Anim5Def;
        w->hideShadow = 1;
        break;
    case 29:
        w->flipped = IsAngleFacingRight(w->angle);
        e = &gPoohFl06Anim1Def;
        break;
    case 30:
        flags |= 1;
        w->flipped = IsAngleFacingRight(w->angle);
        e = &gPoohFl06Anim2Def;
        break;
    case 31:
        w->flipped = IsAngleFacingRight(w->angle);
        e = &gPoohFl06Anim3Def;
        break;
    case 38:
    case 39:
        flags |= 1;
        w->flipped = 0;
        e = &gTrap0003Anim0Def;
        break;
    case 22:
        flags |= 1;
        w->flipped = 0;
        e = &gPoohOwlDescentAnimDef;
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
        flags |= 1;
        SetPoohDir5Right(w);
        w->lookColumn = GetPoohLookColumn(w);
        e = &gPooh00LookAnimDefs[w->dirIndex][GetPoohLookColumn(w)];
        break;
    default:
        flags |= 1;
        SetPoohDir5Right(w);
        e = &gPooh00AnimDefs[w->dirIndex];
        break;
    }

    AnimChangeWithTables(&w->anim, e->animId, flags, e->anims, e->gfxTable);
    SetObjTileSource(w->tiles, e->tiles);
}

u8 IsWithinPoohRadius(u16 x, u16 y, u16 px, u16 py) {
    if (x - gPoohHitBox.radius < px && px < x + gPoohHitBox.radius &&
        y - gPoohHitBox.radius < py && py < y + gPoohHitBox.radius) {
        return 1;
    }
    return 0;
}

s32 GetPooManhattanDistance(PooPos* a, PooPos* b) {
    s32 dx;
    s32 dy;

    dx = a->x - b->x;
    if (dx < 0) {
        dx = b->x - a->x;
    }
    dy = a->y - b->y;
    if (dy < 0) {
        dy = b->y - a->y;
    }
    return dx + dy;
}

void SetPoohPalette(PoohWork* w, u32 b) {
    u8* pal;

    switch (b) {
    case 16:
        pal = gTrap0001Palette;
        break;
    case 36:
    case 37:
        pal = gTrap0002Palette;
        break;
    case 38:
    case 39:
        pal = gTrap0003Palette;
        break;
    default:
        pal = gPoohPalette;
        break;
    }

    if (w->palette->src != pal) {
        ReleaseObjPalette(w->palette);
        w->palette = LoadObjPalette(pal, 32);
    }
}
