#include "rogue.h"
#include "rogue_ui.h"
#include "battle.h"
#include "display.h"
#include "fade.h"
#include "gba/keys.h"
#include "key.h"
#include "m4a_song.h"
#include "malloc.h"
#include "map_api.h"
#include "obj_api.h"
#include "sprites_status.h"
#include "system_state.h"
#include "text.h"

// The techniques of the flat battle, all on one screen: eight plates, the
// four places on the ground on the left and the four in the air on the
// right, each with its keys and the technique set on it. The pad moves
// between them, A sets the next technique the run has and L the one before,
// B leaves. Reached from the options page of Memoria.

#define PLATE_SLOTS 16

typedef struct RogueTechsWork {
    TextSlot title[PLATE_SLOTS];
    TextSlot lines[ROGUE_2D_SLOTS][PLATE_SLOTS];
    u8 titleCount;
    u8 counts[ROGUE_2D_SLOTS];
    u8 text[24];
    void* palette;
    void* titlePalette;
    RogueUi ui;
    u16 map[0x500 / 2];
    u8 cursor;
    u8 state;
} RogueTechsWork;

static RogueTechsWork* sWork;

static const u8 sTitle[] = "Terra                 Aria";
// The keys of each place, as short as they can be told apart: the screen has
// room for few letters.
static const u8 sKey0[] = "B ";
static const u8 sKey1[] = "B> ";
static const u8 sKey2[] = "Bsu ";
static const u8 sKey3[] = "Bgiu ";
static const u8* const sKeys[4] = { sKey0, sKey1, sKey2, sKey3 };

static void RogueTechsLine(u8 slot) {
    u8* out = sWork->text;
    const u8* text;

    FreeTextSlots(sWork->lines[slot], PLATE_SLOTS);

    for (text = sKeys[slot % 4]; *text != 0; text++) {
        *out++ = *text;
    }

    for (text = Rogue2dTechShort(Rogue2dTechAt(slot)); *text != 0; text++) {
        *out++ = *text;
    }

    *out = 0;
    sWork->counts[slot] = LoadTextSlots((u16*)sWork->text, sWork->lines[slot]);
}

static void RogueTechs_Init(s32 arg) {
    s32 i;

    sWork = EwramAlloc(sizeof(RogueTechsWork));
    sWork->state = 0;
    sWork->cursor = 0;
    SetBgMode0();
    SetupBg(3, 0, 0x1D, 0);
    SetBgPriority(3, 3);
    LoadBgTiles(3, gUnk_097FFB98, 0x2060);
    LoadBgPalette(3, gUnk_0984B118, 0xA0);
    LoadBgMap(3, gUnk_09848198, 0x500);
    RogueUiInit(&sWork->ui);
    sWork->palette = _08066468(1);
    sWork->titlePalette = _08066468(0);
    InitTextSlots(sWork->title, PLATE_SLOTS);
    sWork->titleCount = LoadTextSlots((u16*)sTitle, sWork->title);

    for (i = 0; i < ROGUE_2D_SLOTS; i++) {
        InitTextSlots(sWork->lines[i], PLATE_SLOTS);
        RogueTechsLine(i);
    }

    FadeStartIn(0, 16);
}

static void RogueTechs_Update(void) {
    u16 pressed = GetKeysPressed();
    s32 i;
    u8 tech;

    switch (sWork->state) {
    case 0:
        if (!FadeIsActive()) {
            sWork->state = 1;
        }
        break;
    case 1:
        if (pressed & (DPAD_UP | DPAD_DOWN)) {
            // Up and down within a column, left and right between the two.
            sWork->cursor = (sWork->cursor & 4) | ((sWork->cursor + ((pressed & DPAD_DOWN) ? 1 : 3)) & 3);
            m4aSongNumStart(SONG_SYS_CLICK);
        } else if (pressed & (DPAD_LEFT | DPAD_RIGHT)) {
            sWork->cursor ^= 4;
            m4aSongNumStart(SONG_SYS_CLICK);
        } else if (pressed & (A_BUTTON | L_BUTTON | R_BUTTON)) {
            // The next technique the run has, or with L the one before:
            // those of relics only with the relic.
            tech = Rogue2dTechAt(sWork->cursor);

            do {
                tech = (tech + ((pressed & L_BUTTON) ? ROGUE_2D_TECHS - 1 : 1)) % ROGUE_2D_TECHS;
            } while (!Rogue2dTechOwned(tech));

            Rogue2dSetTech(sWork->cursor, tech);
            RogueTechsLine(sWork->cursor);
            m4aSongNumStart(SONG_SYS_KETTEI);
        } else if (pressed & (B_BUTTON | START_BUTTON)) {
            m4aSongNumStart(SONG_SYS_CANSEL);
            FadeStartOut(0, 16);
            sWork->state = 2;
        }
        break;
    case 2:
        if (!FadeIsActive()) {
            func_080E04EC();
            sWork->state = 3;
        }
        break;
    }

    DrawTextSlots(36, 18, sWork->title, sWork->titlePalette, 50, sWork->titleCount);

    for (i = 0; i < ROGUE_2D_SLOTS; i++) {
        s16 px = (i & 4) ? 132 : 20;
        s16 py = 44 + (i & 3) * 26;
        s16 x = RogueUiPlate(&sWork->ui, px, py, i == sWork->cursor);

        DrawTextSlots(x, py + 2, sWork->lines[i], sWork->palette, 50, sWork->counts[i]);

        if (i == sWork->cursor) {
            RogueUiGlove(&sWork->ui, px - 14, py + 8);
        }
    }
}

static void RogueTechs_Exit(void) {
    s32 i;

    FreeTextSlots(sWork->title, PLATE_SLOTS);

    for (i = 0; i < ROGUE_2D_SLOTS; i++) {
        FreeTextSlots(sWork->lines[i], PLATE_SLOTS);
    }

    RogueUiExit(&sWork->ui);
    ReleaseObjPalette(sWork->palette);
    ReleaseObjPalette(sWork->titlePalette);
    EwramFree(sWork);
}

Mode gModeRogueTechs = {
    "mode_rogue_techs",
    RogueTechs_Init,
    RogueTechs_Update,
    RogueTechs_Exit,
};
