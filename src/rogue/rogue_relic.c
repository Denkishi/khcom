#include "rogue.h"
#include "registration_data.h"
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

// Relics: passive effects that last the run. The battle code asks RogueHasRelic.

static const u8 sNameVampire[] = "Zanna vampira";
static const u8 sNameCritical[] = "Occhio critico";
static const u8 sNameSecondWind[] = "Ultimo respiro";
static const u8 sNameGlass[] = "Cannone vetro";
static const u8 sNameMomentum[] = "Slancio";
static const u8 sNameReload[] = "Mano lesta";

static const u8 sTextVampire[] = "Ogni colpo a segno\x1Fti cura di 1 PV";
static const u8 sTextCritical[] = "Un colpo su sette\x1F" "fa danno doppio";
static const u8 sTextSecondWind[] = "Una volta a battaglia\x1Fresti a 1 PV";
static const u8 sTextGlass[] = "Dai e subisci il\x1F" "50% di danno in pi\xF9";
static const u8 sTextMomentum[] = "Il bonus combo\x1F" "arriva al 60%";
static const u8 sTextReload[] = "Il mazzo si ricarica\x1Fmolto pi\xF9 in fretta";

static const u8* const sNames[ROGUE_RELICS] = {
    sNameVampire, sNameCritical, sNameSecondWind, sNameGlass, sNameMomentum, sNameReload,
};

static const u8* const sTexts[ROGUE_RELICS] = {
    sTextVampire, sTextCritical, sTextSecondWind, sTextGlass, sTextMomentum, sTextReload,
};

const u8* RogueRelicName(u8 relic) {
    return sNames[relic];
}

const u8* RogueRelicText(u8 relic) {
    return sTexts[relic];
}

u8 RogueHasRelic(u8 relic) {
    return (gRogue.relics >> relic) & 1;
}

// Two relics are in the pool from the start and each chapter unlocked adds
// two more. Returns one the run does not have yet, or ROGUE_RELICS.
u8 RogueRollRelic(void) {
    u8 pool = gRogueMeta.chapters * 2;
    u8 relic;
    s32 tries;

    if (pool > ROGUE_RELICS) {
        pool = ROGUE_RELICS;
    }

    for (tries = 0; tries < 12; tries++) {
        relic = RogueRandBelow(pool);

        if (!RogueHasRelic(relic)) {
            return relic;
        }
    }

    return ROGUE_RELICS;
}

// The run's page in the pause menu: where the run is and the relics it has.

#define LINE_SLOTS 26
#define RELIC_LINES (2 + ROGUE_RELICS)

typedef struct RogueRelicsWork {
    TextSlot lines[RELIC_LINES][LINE_SLOTS];
    u8 counts[RELIC_LINES];
    u8 text[40];
    void* palette;
    void* titlePalette;
    u8 lineCount;
    u8 state;
} RogueRelicsWork;

static RogueRelicsWork* sWork;

static const u8 sTitle[] = "La tua run";
static const u8 sFloor[] = "Piano ";
static const u8 sCombo[] = "  Combo+";
static const u8 sJumps[] = "  Salti ";
static const u8 sNone[] = "Nessuna reliquia";

static u8* RogueRelicsAppend(u8* out, const u8* text) {
    while (*text != 0) {
        *out++ = *text++;
    }

    *out = 0;
    return out;
}

static void RogueRelicsLine(const u8* text) {
    InitTextSlots(sWork->lines[sWork->lineCount], LINE_SLOTS);
    sWork->counts[sWork->lineCount] = LoadTextSlots((u16*)text, sWork->lines[sWork->lineCount]);
    sWork->lineCount++;
}

static void RogueRelics_Init(s32 arg) {
    u8* out;
    u8 relic;

    sWork = EwramAlloc(sizeof(RogueRelicsWork));
    sWork->state = 0;
    sWork->lineCount = 0;
    SetBgMode0();
    SetupBg(3, 0, 0x1D, 0);
    SetBgPriority(3, 3);
    LoadBgTiles(3, gUnk_097FFB98, 0x2060);
    LoadBgPalette(3, gUnk_0984B118, 0xA0);
    LoadBgMap(3, gUnk_09848198, 0x500);
    sWork->palette = _08066468(1);
    sWork->titlePalette = _08066468(0);
    RogueRelicsLine(sTitle);
    out = RogueRelicsAppend(sWork->text, sFloor);
    *out++ = '0' + (gRogue.floor + 1) / 10;
    *out++ = '0' + (gRogue.floor + 1) % 10;
    out = RogueRelicsAppend(out, sCombo);
    *out++ = '0' + gRogue.comboPlus;
    out = RogueRelicsAppend(out, sJumps);
    *out++ = '0' + gRogue.airJumps;
    *out = 0;
    RogueRelicsLine(sWork->text);

    for (relic = 0; relic < ROGUE_RELICS; relic++) {
        if (RogueHasRelic(relic)) {
            RogueRelicsLine(sNames[relic]);
        }
    }

    if (sWork->lineCount == 2) {
        RogueRelicsLine(sNone);
    }

    FadeStartIn(0, 16);
}

static void RogueRelics_Update(void) {
    s32 i;

    switch (sWork->state) {
    case 0:
        if (!FadeIsActive()) {
            sWork->state = 1;
        }
        break;
    case 1:
        if (GetKeysPressed() & (A_BUTTON | B_BUTTON)) {
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

    for (i = 0; i < sWork->lineCount; i++) {
        DrawTextSlots((240 - GetTextSlotsWidth(sWork->lines[i], sWork->counts[i])) / 2, i == 0 ? 12 : 20 + i * 16,
                      sWork->lines[i], i == 0 ? sWork->titlePalette : sWork->palette, 50, sWork->counts[i]);
    }
}

static void RogueRelics_Exit(void) {
    s32 i;

    for (i = 0; i < sWork->lineCount; i++) {
        FreeTextSlots(sWork->lines[i], LINE_SLOTS);
    }

    ReleaseObjPalette(sWork->palette);
    ReleaseObjPalette(sWork->titlePalette);
    EwramFree(sWork);
}

Mode gModeRogueRelics = {
    "mode_rogue_relics",
    RogueRelics_Init,
    RogueRelics_Update,
    RogueRelics_Exit,
};
