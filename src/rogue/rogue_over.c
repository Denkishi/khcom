#include "rogue.h"
#include "registration_data.h"
#include "battle.h"
#include "display.h"
#include "fade.h"
#include "gba/keys.h"
#include "key.h"
#include "m4a_song.h"
#include "malloc.h"
#include "obj_api.h"
#include "sprites_status.h"
#include "system_state.h"
#include "text.h"

// The summary shown when a run ends, before going back to the title.

#define OVER_LINES 6
#define OVER_SLOTS 28

typedef struct RogueOverWork {
    TextSlot lines[OVER_LINES][OVER_SLOTS];
    u8 counts[OVER_LINES];
    u8 text[32];
    void* palette;
    void* titlePalette;
    u8 state;
} RogueOverWork;

static RogueOverWork* sWork;

static const u8 sTitle[] = "Run finita";
static const u8 sTitleWon[] = "Run completata!";
static const u8 sShards[] = "Frammenti: +";
static const u8 sNewChapter[] = "Nuovo capitolo sbloccato";
static const u8 sNothing[] = "";
static const u8 sFloor[] = "Piano raggiunto: ";
static const u8 sRooms[] = "Stanze superate: ";
static const u8 sLevel[] = "Livello di Sora: ";

static void RogueOverLine(u8 line, const u8* label, s32 value) {
    u8* out = sWork->text;

    while (*label != 0) {
        *out++ = *label++;
    }

    if (value >= 0) {
        if (value >= 100) {
            *out++ = '0' + value / 100;
        }

        if (value >= 10) {
            *out++ = '0' + value / 10 % 10;
        }

        *out++ = '0' + value % 10;
    }

    *out = 0;
    InitTextSlots(sWork->lines[line], OVER_SLOTS);
    sWork->counts[line] = LoadTextSlots((u16*)sWork->text, sWork->lines[line]);
}

static void RogueOver_Init(s32 completed) {
    sWork = EwramAlloc(sizeof(RogueOverWork));
    sWork->state = 0;
    SetBgMode0();
    SetupBg(3, 0, 0x1D, 0);
    SetBgPriority(3, 3);
    LoadBgTiles(3, gUnk_097FFB98, 0x2060);
    LoadBgPalette(3, gUnk_0984B118, 0xA0);
    LoadBgMap(3, gUnk_09848198, 0x500);
    sWork->palette = _08066468(1);
    sWork->titlePalette = _08066468(0);
    RogueOverLine(0, completed ? sTitleWon : sTitle, -1);
    RogueOverLine(1, sFloor, gRogue.floor + 1);
    RogueOverLine(2, sRooms, gRogue.depth);
    RogueOverLine(3, sLevel, gGameState.progression.level);
    RogueOverLine(4, sShards, gRogue.shards);
    RogueOverLine(5, gRogue.newChapter ? sNewChapter : sNothing, -1);
    m4aSongNumStart(0);
    FadeStartIn(0, 30);
}

static void RogueOver_Update(void) {
    s32 i;

    switch (sWork->state) {
    case 0:
        if (!FadeIsActive()) {
            sWork->state = 1;
        }
        break;
    case 1:
        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            FadeStartOut(0, 30);
            sWork->state = 2;
        }
        break;
    case 2:
        if (!FadeIsActive()) {
            ModeRequest(&gModeTitle, 0);
            sWork->state = 3;
        }
        break;
    }

    for (i = 0; i < OVER_LINES; i++) {
        DrawTextSlots((240 - GetTextSlotsWidth(sWork->lines[i], sWork->counts[i])) / 2, i == 0 ? 24 : 36 + i * 16,
                      sWork->lines[i], i == 0 ? sWork->titlePalette : sWork->palette, 50, sWork->counts[i]);
    }
}

static void RogueOver_Exit(void) {
    s32 i;

    for (i = 0; i < OVER_LINES; i++) {
        FreeTextSlots(sWork->lines[i], OVER_SLOTS);
    }

    ReleaseObjPalette(sWork->palette);
    ReleaseObjPalette(sWork->titlePalette);
    EwramFree(sWork);
}

Mode gModeRogueOver = {
    "mode_rogue_over",
    RogueOver_Init,
    RogueOver_Update,
    RogueOver_Exit,
};
