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
#include "rogue_npc_art.h"
#include "msg_portrait_data.h"

// The hub: the Station of Calling, where every run starts from. Sora walks
// on the stained glass, seen from above at its own size. Axel sells the permanent upgrades, and the others who
// stand there, more of them as the game is played, each offer a boon for the
// next run: talking to one picks theirs. Start begins the run.

// The picture of the station's top, larger than the screen: WORLD_COLUMNS by
// WORLD_ROWS tiles stored as they lie, see tools/rogue_backgrounds.py.
extern const u8 gRogueStationWorld[];
extern const u16 gRogueStationPalette[256];
#define WORLD_COLUMNS 58
#define WORLD_ROWS 36
#define WORLD_WIDTH (WORLD_COLUMNS * 8)
#define WORLD_HEIGHT (WORLD_ROWS * 8)
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
// Where Sora can walk, in the picture's pixels: on the glass, an ellipse.
#define GLASS_X 232
#define GLASS_Y 142
#define GLASS_RX 206
#define GLASS_RY 112
#define START_X 232
#define START_Y 150
#define NPC_RADIUS 13 // how near a character Sora's feet can come
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

#define DRAWN(name, x, y, boon) \
    { (void*)gRogueNpc##name##Tiles, sizeof(gRogueNpc##name##Tiles), (void*)gRogueNpc##name##Palette, (void*)gRogueNpc##name##Anims, \
      (void*)gRogueNpc##name##Frames, x, y, boon }

// They stand round the rim of the glass, far enough apart that the screen
// never shows more of them than it has palettes for.
static const RogueHubNpc sNpcs[] = {
    NPC(Accele, gAccelePalette, 232, 62, ROGUE_BOON_NONE),
    NPC(Bell, gBellPalette, 156, 70, ROGUE_BOON_BELLE),
    NPC(Mogu, gMoguPalette, 308, 70, ROGUE_BOON_MOOGLE),
    NPC(Reon, gReonPalette, 60, 127, ROGUE_BOON_LEON),
    NPC(Yuffie, gYuffiePalette, 404, 127, ROGUE_BOON_YUFFIE),
    NPC(Heracles, gHeraclesPalette, 94, 198, ROGUE_BOON_HERCULES),
    NPC(Tigger, gTiggerPalette, 370, 198, ROGUE_BOON_TIGGER),
    NPC(Jack, gJackPalette, 232, 230, ROGUE_BOON_JACK),
    // Those drawn from sheets of standing sprites, see tools/rogue_npcs.py: they have the one pose.
    DRAWN(Kairi, 156, 222, ROGUE_BOON_KAIRI),
    DRAWN(Namine, 308, 222, ROGUE_BOON_NAMINE),
    DRAWN(Aqua, 60, 165, ROGUE_BOON_AQUA),
    DRAWN(Terra, 404, 165, ROGUE_BOON_TERRA),
    DRAWN(Ventus, 94, 94, ROGUE_BOON_VENTUS),
    DRAWN(Vanitas, 370, 94, ROGUE_BOON_VANITAS),
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
    s16 camX; // the corner of the picture the screen shows
    s16 camY;
    s16 tileX; // the tile at that corner when the picture was last loaded
    s16 tileY;
    u8 greeting; // the character Sora is being greeted by, whose boon follows
} RogueHubWork;

enum {
    HUB_NEXT_RUN,
    HUB_NEXT_SHOP
};

static RogueHubWork* sWork;

static void RogueHubCamera(void);
static void RogueHubLoadPicture(u8 all);
static void RogueHubShowNear(void);

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
static const u8 sBoonKairi[] = "PV e rilancio";
static const u8 sBoonNamine[] = "PC +30";
static const u8 sBoonAqua[] = "barriera";
static const u8 sBoonTerra[] = "critici";
static const u8 sBoonVentus[] = "aria";
static const u8 sBoonVanitas[] = "vetro";
static const u8* const sBoonNames[ROGUE_BOONS] = {
    sBoonNone, sBoonBelle, sBoonMoogle, sBoonLeon, sBoonYuffie, sBoonHercules, sBoonTigger, sBoonJack,
    sBoonKairi, sBoonNamine, sBoonAqua, sBoonTerra, sBoonVentus, sBoonVanitas,
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
    FreeTextSlots(sWork->hero, 26);
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
    LoadBgPalette(3, (void*)gRogueStationPalette, 224 * 2);
    // The dialogue window goes on the first background, set up as in a room.
    SetupBg(0, 3, 31, 14);
    SetBgPriority(0, 0);
    TaskPoolInit(&sWork->tasks, 2);
    sWork->textPalette = _08066468(1);
    sWork->hintPalette = _08066468(0);
    InitTextSlots(sWork->line, LINE_SLOTS);
    InitTextSlots(sWork->hint, LINE_SLOTS);
    InitTextSlots(sWork->level, 14);
    InitTextSlots(sWork->hero, 26);
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
        sWork->present[i] = 0;
    }

    sWork->greeting = HUB_NPCS;
    RogueHubCamera();
    RogueHubLoadPicture(1);
    RogueHubShowNear();

    m4aSongNumStartOrContinue(SONG_BGM_TITLE);
    FadeStartIn(0, 16);
}

// The screen's corner follows Sora, as far as the picture goes.
static void RogueHubCamera(void) {
    s32 x = (sWork->x >> 8) - 120;
    s32 y = (sWork->y >> 8) - 88;

    sWork->camX = x < 0 ? 0 : x > WORLD_WIDTH - 240 ? WORLD_WIDTH - 240 : x;
    sWork->camY = y < 0 ? 0 : y > WORLD_HEIGHT - 160 ? WORLD_HEIGHT - 160 : y;
}

// One tile of the picture into the video memory. There is room for 32 by 24
// tiles of it at a time, more than the screen shows, so a tile's place there
// is its column and row wrapped to that; the map, 32 by 32, is told where.
static void RogueHubLoadTile(s32 tx, s32 ty) {
    const u32* from = (const u32*)&gRogueStationWorld[(ty * WORLD_COLUMNS + tx) * 64];
    u16 slot = (ty % 24) * 32 + (tx & 31);
    u32* to = (u32*)(0x06000000 + slot * 64);
    s32 i;

    for (i = 0; i < 16; i++) {
        to[i] = from[i];
    }

    ((u16*)0x0600E800)[(ty & 31) * 32 + (tx & 31)] = slot;
}

// Loads what the screen has come to show: all of it, or the column and the
// row that have just come in at an edge.
static void RogueHubLoadPicture(u8 all) {
    s32 tileX = sWork->camX >> 3;
    s32 tileY = sWork->camY >> 3;
    s32 x;
    s32 y;

    for (y = tileY; y <= tileY + 20 && y < WORLD_ROWS; y++) {
        for (x = tileX; x <= tileX + 30 && x < WORLD_COLUMNS; x++) {
            if (all || x < sWork->tileX || x > sWork->tileX + 30 || y < sWork->tileY || y > sWork->tileY + 20) {
                RogueHubLoadTile(x, y);
            }
        }
    }

    sWork->tileX = tileX;
    sWork->tileY = tileY;
    SetBgScroll(3, sWork->camX, sWork->camY);
}

// Puts on the screen the characters near enough to be seen and takes off
// those left behind: there are not the palettes for all of them at once.
static void RogueHubShowNear(void) {
    u32 i;

    for (i = 0; i < HUB_NPCS; i++) {
        s32 dx = sNpcs[i].x - (sWork->camX + 120);
        s32 dy = sNpcs[i].y - (sWork->camY + 80);
        // On the screen, or about to be: they are drawn from the feet up, and are tall.
        u8 near = RogueBoonUnlocked(sNpcs[i].boon) && dx > -150 && dx < 150 && dy > -92 && dy < 164;

        if (near && !sWork->present[i] && CanAllocObjPalette(3)) {
            sWork->present[i] = 1;
            sWork->npcTiles[i] = AllocObjTiles(sNpcs[i].tilesSize, sNpcs[i].tiles);
            sWork->npcPalettes[i] = LoadObjPalette(sNpcs[i].palette, 32);
            AnimInit(&sWork->npcAnims[i], sNpcs[i].anims, sNpcs[i].frames);
            AnimStart(&sWork->npcAnims[i], 0, 1);
        } else if (!near && sWork->present[i]) {
            ReleaseObjTiles(sWork->npcTiles[i]);
            ReleaseObjPalette(sWork->npcPalettes[i]);
            sWork->present[i] = 0;
        }
    }
}

// Whether Sora's feet can be there: on the glass and not inside a character.
static u8 RogueHubFree(s32 x, s32 y) {
    s32 ex = (x - GLASS_X) * GLASS_RY;
    s32 ey = (y - GLASS_Y) * GLASS_RX;
    u32 i;

    if (ex * ex + ey * ey > GLASS_RX * GLASS_RX * GLASS_RY * GLASS_RY) {
        return 0;
    }

    for (i = 0; i < HUB_NPCS; i++) {
        s32 dx = x - sNpcs[i].x;
        s32 dy = (y - sNpcs[i].y) * 2;

        if (sWork->present[i] && dx * dx + dy * dy < NPC_RADIUS * NPC_RADIUS) {
            return 0;
        }
    }

    return 1;
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

    // Each way by itself, so that he slides along what stops him.
    if (RogueHubFree(x, sWork->y >> 8)) {
        sWork->x += dx;
    }

    if (RogueHubFree(sWork->x >> 8, y)) {
        sWork->y += dy;
    }

    RogueHubCamera();
    RogueHubLoadPicture(0);
    RogueHubShowNear();
}

// For the trailer (tools/trailer.py): its lines of text are written by the
// game, in its own letters on an empty screen, to be photographed.
static const u8 sCaption0[] = "\x1D" "KINGDOM HEARTS\x1E";
static const u8 sCaption1[] = "\x1D" "CHAIN OF MEMORIES\x1E";
static const u8 sCaption2[] = "\x1D" "ROGUELITE\x1E";
static const u8 sCaption3[] = "\x1D" "Ogni run \xE8 diversa\x1E";
static const u8 sCaption4[] = "\x1D" "Un hub da esplorare\x1E";
static const u8 sCaption5[] = "\x1D" "Ogni porta, una carta\x1E";
static const u8 sCaption6[] = "\x1D" "Tu scegli la stanza\x1E";
static const u8 sCaption7[] = "\x1D" "Battaglie in 2D\x1E";
static const u8 sCaption8[] = "\x1D" "Nuove mosse\x1E";
static const u8 sCaption9[] = "\x1D" "Salta. Taglia. Tuffati.\x1E";
static const u8 sCaption10[] = "\x1D" "Ogni mossa \xE8 una carta\x1E";
static const u8 sCaption11[] = "\x1D" "Le mosse dei boss sono tue\x1E";
static const u8 sCaption12[] = "\x1D" "Pi\xF9 di 180 reliquie\x1E";
static const u8 sCaption13[] = "\x1D" "Nuovi eroi\x1E";
static const u8 sCaption14[] = "\x1D" "Nuovi boss\x1E";
static const u8 sCaption15[] = "\x1D" "Riuscirai a batterli?\x1E";
static const u8 sCaption16[] = "\x1D" "CoM ROGUELITE\x1E";
static const u8 sCaption17[] = "\x1D" "github.com/Denkishi/khcom\x1E";
static const u8* const sCaptions[] = { sCaption0, sCaption1, sCaption2, sCaption3, sCaption4, sCaption5, sCaption6, sCaption7, sCaption8, sCaption9, sCaption10, sCaption11, sCaption12, sCaption13, sCaption14, sCaption15, sCaption16, sCaption17 };

static void RogueHubCaption(void) {
    static u8 shown;

    if (shown != gRogueDebug.caption) {
        shown = gRogueDebug.caption;
        DisableBg(3);
        FreeTextSlots(sWork->line, LINE_SLOTS);
        sWork->lineCount = shown == 255 ? 0 : LoadTextSlots((u16*)sCaptions[shown - 1], sWork->line);
    }

    // 255: the two plates of the menus, plain and chosen, with nothing written on them.
    if (shown == 255) {
        RogueUiPlate(&sWork->ui, 20, 40, 0);
        RogueUiPlate(&sWork->ui, 20, 80, 1);
        return;
    }

    DrawTextSlots(8, 72, sWork->line, sWork->textPalette, 50, sWork->lineCount);
}

static void RogueHub_Update(void) {
    u32 near;
    u32 i;
    u16 attr;

    if (gRogueDebug.caption != 0) {
        RogueHubCaption();
        return;
    }

    switch (sWork->state) {
    case 0:
        if (!FadeIsActive()) {
            sWork->state = 1;
        }
        break;
    case 1:
        if (sWork->talking) {
            if (func_080A42C8() != 0) {
                break;
            }

            // After the greeting, what the character offers; the boon is
            // picked once they have said what it is.
            if (sWork->greeting != HUB_NPCS) {
                u8 boon = sNpcs[sWork->greeting].boon;

                sWork->greeting = HUB_NPCS;
                gRogueMeta.boon = boon;
                RogueMetaSave();
                CreateCardMessageTask(&sWork->tasks, 0, ROGUE_MSG_BOON_FIRST + boon - 1);
                break;
            }

            sWork->talking = 0;
            RogueHubShowBoon();
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
                RogueHubSoraAnim(ACTION_STAND, sWork->direction);
                CreateCardMessageTask(&sWork->tasks, 0, ROGUE_MSG_GREET_FIRST + sNpcs[near].boon - 1);
                sWork->greeting = near;
                sWork->talking = 1;
            }
        }
        break;
    case 2:
        if (!FadeIsActive()) {
            if (sWork->next == HUB_NEXT_RUN) {
                // The room cards first: bought here, they go into the run.
                if (RogueMapMenuWanted(1)) {
                    ModeRequest(&gModeRogueDoor, ROGUE_DOOR_HUB);
                } else {
                    RogueStartRun();
                }
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
            DrawSprite(sNpcs[i].x - sWork->camX, sNpcs[i].y - sWork->camY, AnimGetGfx(&sWork->npcAnims[i]), sWork->npcTiles[i],
                       sWork->npcPalettes[i], 0, 0x800, -0x1000 - sNpcs[i].y * 4);
        }
    }

    attr = 0x800;

    if (sWork->mirrored) {
        attr |= 1;
    }

    DrawSprite((sWork->x >> 8) - sWork->camX, (sWork->y >> 8) - sWork->camY, AnimGetGfx(&sWork->soraAnim), sWork->soraTiles, sWork->soraPalette, 0, attr,
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
    FreeTextSlots(sWork->hero, 26);
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

// The faces shown in a message: the game's, or those of the characters the mod draws.
const MsgFaceAnim* RogueFaceAnims(s32 portrait) {
    if (portrait >= ROGUE_FACE_FIRST) {
        return &gRogueNpcFaces[portrait - ROGUE_FACE_FIRST];
    }

    return gMsgFaceAnims[portrait];
}
