#include "rogue.h"
#include "rogue_ui.h"
#include "registration_data.h"
#include "anim.h"
#include "battle_actor.h"
#include "card_api.h"
#include "card_message_data.h"
#include "display.h"
#include "fade.h"
#include "gba/io_reg.h"
#include "gba/keys.h"
#include "key.h"
#include "m4a_song.h"
#include "malloc.h"
#include "obj_api.h"
#include "sprite.h"
#include "sprite_palettes.h"
#include "sprites_evt.h"
#include "system_state.h"
#include "taskpool.h"
#include "text.h"

// The hub: the Station of Calling, where every run starts from. Sora walks
// on the stained glass, seen from above at its own size. Axel sells the permanent upgrades, and the others who
// stand there, more of them as the game is played, each offer a boon for the
// next run: talking to one picks theirs. Start begins the run.

extern const u8 gRogueStationTiles[];
extern const u16 gRogueStationMap[640];
extern const u16 gRogueStationPalette[256];
extern const u32 gRogueStationTilesSize;
// Sora's field sprites: [action][direction], directions back, front,
// front-left, left and back-left, mirrored for the right-hand ones.
extern const AnimDef gUnk_0813C89C[15][5];

enum {
    DIR_BACK,
    DIR_FRONT,
    DIR_FRONT_LEFT,
    DIR_LEFT,
    DIR_BACK_LEFT
};

#define ACTION_STAND 0
#define ACTION_WALK 1

// Where Sora can walk, in screen pixels: the picture above the text.
#define WALK_LEFT 12
#define WALK_RIGHT 228
#define WALK_TOP 42
#define WALK_BOTTOM 126
#define START_X 120
#define START_Y 84
#define TALK_RANGE 26
#define WALK_SPEED 0x180

typedef struct RogueHubNpc {
    void* tiles;
    u16 tilesSize;
    void* palette;
    void* anims;
    void* frames;
    s16 x;
    s16 y;
    u8 boon; // the boon they offer, ROGUE_BOON_NONE for Axel
} RogueHubNpc;

#define NPC(name, palette, x, y, boon) \
    { g##name##Fl00Tiles, sizeof(g##name##Fl00Tiles), palette, g##name##Fl00Anims, g##name##Fl00Frames, x, y, boon }

// They stand around the edge, leaving the middle to walk in.
static const RogueHubNpc sNpcs[] = {
    NPC(Accele, gAccelePalette, 120, 46, ROGUE_BOON_NONE),
    NPC(Bell, gBellPalette, 66, 50, ROGUE_BOON_BELLE),
    NPC(Mogu, gMoguPalette, 174, 50, ROGUE_BOON_MOOGLE),
    NPC(Reon, gReonPalette, 26, 84, ROGUE_BOON_LEON),
    NPC(Yuffie, gYuffiePalette, 214, 84, ROGUE_BOON_YUFFIE),
    NPC(Heracles, gHeraclesPalette, 62, 122, ROGUE_BOON_HERCULES),
    NPC(Tigger, gTiggerPalette, 178, 122, ROGUE_BOON_TIGGER),
    NPC(Jack, gJackPalette, 120, 124, ROGUE_BOON_JACK),
};

#define HUB_NPCS (sizeof(sNpcs) / sizeof(sNpcs[0]))
#define LINE_SLOTS 30

typedef struct RogueHubWork {
    TaskPool tasks;
    TextSlot line[LINE_SLOTS];
    TextSlot hint[LINE_SLOTS];
    TextSlot level[14]; // the oblivion level's plate
    TextSlot hero[26]; // the hero hint's plate
    u8 levelText[14];
    u8 lineCount;
    u8 hintCount;
    u8 levelCount;
    u8 heroCount;
    RogueUi ui;
    u8 text[72];
    void* textPalette;
    void* hintPalette;
    void* soraTiles;
    void* soraPalette;
    AnimState soraAnim;
    void* npcTiles[HUB_NPCS];
    void* npcPalettes[HUB_NPCS];
    AnimState npcAnims[HUB_NPCS];
    u8 present[HUB_NPCS];
    s32 x; // Sora's feet, 24.8
    s32 y;
    u8 direction;
    u8 mirrored;
    u8 walking;
    u8 state;
    u8 next; // what the hub leads to once it has faded out
    u8 talking;
} RogueHubWork;

enum {
    HUB_NEXT_RUN,
    HUB_NEXT_SHOP
};

static RogueHubWork* sWork;

static const u8 sHint[] = "START: parti";
static const u8 sBoon[] = "Dono: ";
static const u8 sBoonNone[] = "nessuno";
static const u8 sStrong[] = " +";
static const u8 sHero0[] = "SELECT: Sora";
static const u8 sHero1[] = "SELECT: Topolino";
static const u8 sHero2[] = "SELECT: Sora II";
static const u8 sHero3[] = "SELECT: Riku";
static const u8 sHero4[] = "SELECT: Roxas";
static const u8* const sHero[ROGUE_HEROES] = { sHero0, sHero1, sHero2, sHero3, sHero4 };
static const u8 sOblivion[] = "L/R: Oblio ";
static const u8 sBoonBelle[] = "PV +30";
static const u8 sBoonMoogle[] = "2 rilanci";
static const u8 sBoonLeon[] = "lame";
static const u8 sBoonYuffie[] = "magie";
static const u8 sBoonHercules[] = "Forza +2";
static const u8 sBoonTigger[] = "salto";
static const u8 sBoonJack[] = "reliquia";
static const u8* const sBoonNames[ROGUE_BOONS] = {
    sBoonNone, sBoonBelle, sBoonMoogle, sBoonLeon, sBoonYuffie, sBoonHercules, sBoonTigger, sBoonJack,
};

static void RogueHubShowBoon(void) {
    u8* out = sWork->text;
    const u8* text;

    for (text = sBoon; *text != 0; text++) {
        *out++ = *text;
    }

    for (text = sBoonNames[gRogueMeta.boon]; *text != 0; text++) {
        *out++ = *text;
    }

    if (gRogueMeta.boon != ROGUE_BOON_NONE && RogueBoonLevel(gRogueMeta.boon) == 2) {
        for (text = sStrong; *text != 0; text++) {
            *out++ = *text;
        }
    }

    *out = 0;
    FreeTextSlots(sWork->line, LINE_SLOTS);
    sWork->lineCount = LoadTextSlots((u16*)sWork->text, sWork->line);

    // The oblivion level, once there is one to pick with L and R, and the
    // hero, once there is another: a plate each.
    FreeTextSlots(sWork->level, 14);
    FreeTextSlots(sWork->hero, 14);
    sWork->levelCount = 0;
    sWork->heroCount = 0;

    if (gRogueMeta.oblivionMax != 0) {
        out = sWork->levelText;

        for (text = sOblivion; *text != 0; text++) {
            *out++ = *text;
        }

        *out++ = '0' + gRogueMeta.oblivion;
        *out = 0;
        sWork->levelCount = LoadTextSlots((u16*)sWork->levelText, sWork->level);
    }

    if (RogueNextHero() != gRogueMeta.hero) {
        sWork->heroCount = LoadTextSlots((u16*)sHero[gRogueMeta.hero], sWork->hero);
    }

}

static void RogueHubSoraAnim(u8 action, u8 direction) {
    if (RogueHeroHub(0) != 0) {
        // He has one way of standing and one of walking, turned as he goes.
        AnimChangeWithDef(RogueHeroHub(0), &sWork->soraAnim, action, 1, sWork->soraTiles);
    } else {
        AnimChangeWithDef(gUnk_0813C89C[action], &sWork->soraAnim, direction, 1, sWork->soraTiles);
    }

    sWork->walking = action;
    sWork->direction = direction;
}

static void RogueHub_Init(s32 arg) {
    u32 i;

    sWork = EwramAlloc(sizeof(RogueHubWork));
    sWork->state = 0;
    sWork->talking = 0;
    sWork->x = START_X << 8;
    sWork->y = START_Y << 8;
    sWork->mirrored = 0;
    SetBgMode0();
    SetupBg(3, 0, 0x1D, 0);
    SetBgPriority(3, 3);
    // The picture is the mod's only 256-colour background.
    gBg3Cnt |= BGCNT_256COLOR;
    LoadBgTiles(3, (void*)gRogueStationTiles, gRogueStationTilesSize);
    LoadBgPalette(3, (void*)gRogueStationPalette, 224 * 2);
    LoadBgMap(3, (void*)gRogueStationMap, sizeof(gRogueStationMap));
    // The dialogue window goes on the first background, set up as in a room.
    SetupBg(0, 3, 31, 14);
    SetBgPriority(0, 0);
    TaskPoolInit(&sWork->tasks, 2);
    sWork->textPalette = _08066468(1);
    sWork->hintPalette = _08066468(0);
    InitTextSlots(sWork->line, LINE_SLOTS);
    InitTextSlots(sWork->hint, LINE_SLOTS);
    InitTextSlots(sWork->level, 14);
    InitTextSlots(sWork->hero, 14);
    sWork->levelCount = 0;
    sWork->heroCount = 0;
    RogueUiInit(&sWork->ui);
    sWork->hintCount = LoadTextSlots((u16*)sHint, sWork->hint);
    RogueHubShowBoon();

    sWork->soraTiles = AllocObjTiles(0x500, 0);
    sWork->soraPalette = LoadObjPalette(RogueHeroPalette(gSoraPalette), 32);
    AnimInit(&sWork->soraAnim, 0, 0);
    RogueHubSoraAnim(ACTION_STAND, DIR_FRONT);

    for (i = 0; i < HUB_NPCS; i++) {
        sWork->present[i] = RogueBoonUnlocked(sNpcs[i].boon);

        if (sWork->present[i]) {
            sWork->npcTiles[i] = AllocObjTiles(sNpcs[i].tilesSize, sNpcs[i].tiles);
            sWork->npcPalettes[i] = LoadObjPalette(sNpcs[i].palette, 32);
            AnimInit(&sWork->npcAnims[i], sNpcs[i].anims, sNpcs[i].frames);
            AnimStart(&sWork->npcAnims[i], 0, 1);
        }
    }

    m4aSongNumStartOrContinue(SONG_BGM_TITLE);
    FadeStartIn(0, 16);
}

// The character Sora stands next to, HUB_NPCS if none.
static u32 RogueHubNearest(void) {
    s32 x = sWork->x >> 8;
    s32 y = sWork->y >> 8;
    s32 dx;
    s32 dy;
    u32 i;

    for (i = 0; i < HUB_NPCS; i++) {
        dx = x - sNpcs[i].x;
        dy = y - sNpcs[i].y;

        if (sWork->present[i] && dx * dx + dy * dy * 2 < TALK_RANGE * TALK_RANGE) {
            return i;
        }
    }

    return HUB_NPCS;
}

static void RogueHubWalk(void) {
    u16 held = GetKeysHeld();
    s32 dx = 0;
    s32 dy = 0;
    s32 x;
    s32 y;
    u8 direction = sWork->direction;
    u8 mirrored = sWork->mirrored;

    if (held & DPAD_LEFT) {
        dx = -WALK_SPEED;
    } else if (held & DPAD_RIGHT) {
        dx = WALK_SPEED;
    }

    if (held & DPAD_UP) {
        dy = -WALK_SPEED * 2 / 3;
    } else if (held & DPAD_DOWN) {
        dy = WALK_SPEED * 2 / 3;
    }

    if (dx == 0 && dy == 0) {
        if (sWork->walking != ACTION_STAND) {
            RogueHubSoraAnim(ACTION_STAND, sWork->direction);
        }

        return;
    }

    if (dx != 0) {
        mirrored = dx > 0;
        direction = dy < 0 ? DIR_BACK_LEFT : dy > 0 ? DIR_FRONT_LEFT : DIR_LEFT;
    } else {
        direction = dy < 0 ? DIR_BACK : DIR_FRONT;
    }

    if (sWork->walking != ACTION_WALK || direction != sWork->direction) {
        RogueHubSoraAnim(ACTION_WALK, direction);
    }

    sWork->mirrored = mirrored;

    x = (sWork->x + dx) >> 8;
    y = (sWork->y + dy) >> 8;

    if (x >= WALK_LEFT && x <= WALK_RIGHT) {
        sWork->x += dx;
    }

    if (y >= WALK_TOP && y <= WALK_BOTTOM) {
        sWork->y += dy;
    }
}

static void RogueHub_Update(void) {
    u32 near;
    u32 i;
    u16 attr;

    switch (sWork->state) {
    case 0:
        if (!FadeIsActive()) {
            sWork->state = 1;
        }
        break;
    case 1:
        if (sWork->talking) {
            // The boon is picked once the character has said what it is.
            if (func_080A42C8() == 0) {
                sWork->talking = 0;
                RogueHubShowBoon();
            }
            break;
        }

        RogueHubWalk();
        near = RogueHubNearest();

        if ((GetKeysPressed() & (L_BUTTON | R_BUTTON)) && gRogueMeta.oblivionMax != 0) {
            // L and R pick the oblivion level among the ones unlocked.
            if (GetKeysPressed() & R_BUTTON) {
                gRogueMeta.oblivion = gRogueMeta.oblivion < gRogueMeta.oblivionMax ? gRogueMeta.oblivion + 1 : 0;
            } else {
                gRogueMeta.oblivion = gRogueMeta.oblivion > 0 ? gRogueMeta.oblivion - 1 : gRogueMeta.oblivionMax;
            }

            m4aSongNumStart(SONG_SYS_CLICK);
            RogueMetaSave();
            RogueHubShowBoon();
        } else if ((GetKeysPressed() & SELECT_BUTTON) && RogueNextHero() != gRogueMeta.hero) {
            // SELECT changes who fights, among the heroes unlocked.
            gRogueMeta.hero = RogueNextHero();
            m4aSongNumStart(SONG_SYS_KETTEI);
            RogueMetaSave();
            LoadObjPaletteBank(((ObjPalette*)sWork->soraPalette)->index, RogueHeroPalette(gSoraPalette));
            RogueHubSoraAnim(ACTION_STAND, DIR_FRONT);
            RogueHubShowBoon();
        } else if (GetKeysPressed() & START_BUTTON) {
            m4aSongNumStart(SONG_SYS_START);
            sWork->next = HUB_NEXT_RUN;
            FadeStartOut(0, 16);
            sWork->state = 2;
        } else if ((GetKeysPressed() & A_BUTTON) && near != HUB_NPCS) {
            if (sNpcs[near].boon == ROGUE_BOON_NONE) {
                m4aSongNumStart(SONG_SYS_KETTEI);
                sWork->next = HUB_NEXT_SHOP;
                FadeStartOut(0, 16);
                sWork->state = 2;
            } else {
                gRogueMeta.boon = sNpcs[near].boon;
                RogueMetaSave();
                RogueHubSoraAnim(ACTION_STAND, sWork->direction);
                CreateCardMessageTask(&sWork->tasks, 0, ROGUE_MSG_BOON_FIRST + sNpcs[near].boon - 1);
                sWork->talking = 1;
            }
        }
        break;
    case 2:
        if (!FadeIsActive()) {
            if (sWork->next == HUB_NEXT_RUN) {
                RogueStartRun();
            } else {
                ModeRequest(&gModeRogueShop, ROGUE_SHOP_FROM_HUB);
            }

            sWork->state = 3;
        }
        break;
    }

    TaskPoolUpdate(&sWork->tasks);
    AnimUpdate(&sWork->soraAnim);

    // Lower on the screen is nearer: the priority follows the feet.
    for (i = 0; i < HUB_NPCS; i++) {
        if (sWork->present[i]) {
            AnimUpdate(&sWork->npcAnims[i]);
            DrawSprite(sNpcs[i].x, sNpcs[i].y, AnimGetGfx(&sWork->npcAnims[i]), sWork->npcTiles[i], sWork->npcPalettes[i], 0, 0x800,
                       -0x1000 - sNpcs[i].y * 4);
        }
    }

    attr = 0x800;

    if (sWork->mirrored) {
        attr |= 1;
    }

    DrawSprite(sWork->x >> 8, sWork->y >> 8, AnimGetGfx(&sWork->soraAnim), sWork->soraTiles, sWork->soraPalette, 0, attr,
               -0x1000 - (sWork->y >> 8) * 4);

    if (!sWork->talking) {
        // Four plates at the bottom: the boon and the oblivion level, and
        // under them how to start and how to change hero.
        DrawTextSlots(RogueUiPlate(&sWork->ui, 20, 124, 0), 126, sWork->line, sWork->textPalette, 50, sWork->lineCount);
        DrawTextSlots(RogueUiPlate(&sWork->ui, 12, 142, 1), 144, sWork->hint, sWork->textPalette, 50, sWork->hintCount);

        if (sWork->levelCount != 0) {
            DrawTextSlots(RogueUiPlate(&sWork->ui, 124, 124, 0), 126, sWork->level, sWork->textPalette, 50, sWork->levelCount);
        }

        if (sWork->heroCount != 0) {
            DrawTextSlots(RogueUiPlate(&sWork->ui, 124, 142, 0), 144, sWork->hero, sWork->textPalette, 50, sWork->heroCount);
        }
    }

    TaskPoolDraw(&sWork->tasks);
}

static void RogueHub_Exit(void) {
    u32 i;

    TaskPoolDestroy(&sWork->tasks);
    FreeTextSlots(sWork->line, LINE_SLOTS);
    FreeTextSlots(sWork->hint, LINE_SLOTS);
    FreeTextSlots(sWork->level, 14);
    FreeTextSlots(sWork->hero, 14);
    RogueUiExit(&sWork->ui);
    ReleaseObjPalette(sWork->textPalette);
    ReleaseObjPalette(sWork->hintPalette);
    ReleaseObjTiles(sWork->soraTiles);
    ReleaseObjPalette(sWork->soraPalette);

    for (i = 0; i < HUB_NPCS; i++) {
        if (sWork->present[i]) {
            ReleaseObjTiles(sWork->npcTiles[i]);
            ReleaseObjPalette(sWork->npcPalettes[i]);
        }
    }

    EwramFree(sWork);
}

Mode gModeRogueHub = {
    "mode_rogue_hub",
    RogueHub_Init,
    RogueHub_Update,
    RogueHub_Exit,
};
