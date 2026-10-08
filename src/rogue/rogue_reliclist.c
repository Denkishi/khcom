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

// The relics the run has, one by one: four names at a time, the one under
// the glove on a plate, and under them what it does. Up and down go through
// the list, B leaves. Reached from the relics page of Memoria.

#define NAMES 4 // shown at once
#define NAME_SLOTS 24
#define TEXT_SLOTS 30

typedef struct RogueRelicListWork {
    TextSlot title[NAME_SLOTS];
    TextSlot names[NAMES][NAME_SLOTS];
    TextSlot text[2][TEXT_SLOTS];
    u8 titleCount;
    u8 nameCounts[NAMES];
    u8 textCounts[2];
    u8 buffer[64];
    void* palette;
    void* titlePalette;
    RogueUi ui;
    u8 owned[ROGUE_RELICS]; // the relics the run has, in their order
    u8 count;
    u8 cursor;
    u8 top;
    u8 state;
} RogueRelicListWork;

static RogueRelicListWork* sWork;

static const u8 sTitle[] = "Reliquie ";
static const u8 sNone[] = "Nessuna reliquia";

static u8* RogueRelicListNumber(u8* out, u8 value) {
    if (value >= 100) {
        *out++ = '0' + value / 100;
    }

    if (value >= 10) {
        *out++ = '0' + value / 10 % 10;
    }

    *out++ = '0' + value % 10;
    *out = 0;
    return out;
}

static void RogueRelicListRefresh(void) {
    const u8* from;
    u8* out;
    u8 i;
    u8 line;

    if (sWork->cursor < sWork->top) {
        sWork->top = sWork->cursor;
    } else if (sWork->cursor >= sWork->top + NAMES) {
        sWork->top = sWork->cursor - NAMES + 1;
    }

    // The title counts: which one of how many.
    FreeTextSlots(sWork->title, NAME_SLOTS);
    out = sWork->buffer;

    for (from = sTitle; *from != 0; from++) {
        *out++ = *from;
    }

    if (sWork->count != 0) {
        out = RogueRelicListNumber(out, sWork->cursor + 1);
        *out++ = '/';
        out = RogueRelicListNumber(out, sWork->count);
    }

    *out = 0;
    sWork->titleCount = LoadTextSlots((u16*)sWork->buffer, sWork->title);

    for (i = 0; i < NAMES; i++) {
        FreeTextSlots(sWork->names[i], NAME_SLOTS);
        sWork->nameCounts[i] = 0;

        if (sWork->top + i < sWork->count) {
            sWork->nameCounts[i] = LoadTextSlots((u16*)RogueRelicName(sWork->owned[sWork->top + i]), sWork->names[i]);
        } else if (i == 0) {
            sWork->nameCounts[i] = LoadTextSlots((u16*)sNone, sWork->names[i]);
        }
    }

    // What the one under the glove does: its text, a line break in it making the second line.
    FreeTextSlots(sWork->text[0], TEXT_SLOTS);
    FreeTextSlots(sWork->text[1], TEXT_SLOTS);
    sWork->textCounts[0] = 0;
    sWork->textCounts[1] = 0;

    if (sWork->count == 0) {
        return;
    }

    from = RogueRelicText(sWork->owned[sWork->cursor]);

    for (line = 0; line < 2 && from != 0 && *from != 0; line++) {
        out = sWork->buffer;

        while (*from != 0 && *from != 0x1F && out < sWork->buffer + sizeof(sWork->buffer) - 1) {
            *out++ = *from++;
        }

        if (*from == 0x1F) {
            from++;
        }

        *out = 0;
        sWork->textCounts[line] = LoadTextSlots((u16*)sWork->buffer, sWork->text[line]);
    }
}

static void RogueRelicList_Init(s32 arg) {
    s32 i;

    sWork = EwramAlloc(sizeof(RogueRelicListWork));
    sWork->state = 0;
    sWork->cursor = 0;
    sWork->top = 0;
    sWork->count = 0;

    for (i = 0; i < ROGUE_RELICS; i++) {
        if (RogueHasRelic(i)) {
            sWork->owned[sWork->count++] = i;
        }
    }

    SetBgMode0();
    SetupBg(3, 0, 0x1D, 0);
    SetBgPriority(3, 3);
    LoadBgTiles(3, gUnk_097FFB98, 0x2060);
    LoadBgPalette(3, gUnk_0984B118, 0xA0);
    LoadBgMap(3, gUnk_09848198, 0x500);
    RogueUiInit(&sWork->ui);
    sWork->palette = _08066468(1);
    sWork->titlePalette = _08066468(0);
    InitTextSlots(sWork->title, NAME_SLOTS);
    InitTextSlots(sWork->text[0], TEXT_SLOTS);
    InitTextSlots(sWork->text[1], TEXT_SLOTS);

    for (i = 0; i < NAMES; i++) {
        InitTextSlots(sWork->names[i], NAME_SLOTS);
    }

    RogueRelicListRefresh();
    FadeStartIn(0, 16);
}

static void RogueRelicList_Update(void) {
    u16 pressed = GetKeysPressed();
    s32 i;

    switch (sWork->state) {
    case 0:
        if (!FadeIsActive()) {
            sWork->state = 1;
        }
        break;
    case 1:
        if ((pressed & (DPAD_UP | DPAD_DOWN)) && sWork->count != 0) {
            sWork->cursor = (sWork->cursor + ((pressed & DPAD_DOWN) ? 1 : sWork->count - 1)) % sWork->count;
            m4aSongNumStart(SONG_SYS_CLICK);
            RogueRelicListRefresh();
        } else if (pressed & (B_BUTTON | START_BUTTON | A_BUTTON)) {
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

    DrawTextSlots(120 - GetTextSlotsWidth(sWork->title, sWork->titleCount) / 2, 12, sWork->title, sWork->titlePalette, 50, sWork->titleCount);

    for (i = 0; i < NAMES; i++) {
        s16 y = 34 + i * 20;

        if (sWork->nameCounts[i] == 0) {
            continue;
        }

        if (sWork->top + i == sWork->cursor && sWork->count != 0) {
            // The one under the glove on a plate, the others plain.
            RogueUiPlate(&sWork->ui, 28, y, 1);
            RogueUiGlove(&sWork->ui, 22, y + 8);
        }

        DrawTextSlots(48, y + 2, sWork->names[i], sWork->palette, 50, sWork->nameCounts[i]);
    }

    DrawTextSlots(120 - GetTextSlotsWidth(sWork->text[0], sWork->textCounts[0]) / 2, 122, sWork->text[0], sWork->palette, 50, sWork->textCounts[0]);
    DrawTextSlots(120 - GetTextSlotsWidth(sWork->text[1], sWork->textCounts[1]) / 2, 138, sWork->text[1], sWork->palette, 50, sWork->textCounts[1]);
}

static void RogueRelicList_Exit(void) {
    s32 i;

    FreeTextSlots(sWork->title, NAME_SLOTS);
    FreeTextSlots(sWork->text[0], TEXT_SLOTS);
    FreeTextSlots(sWork->text[1], TEXT_SLOTS);

    for (i = 0; i < NAMES; i++) {
        FreeTextSlots(sWork->names[i], NAME_SLOTS);
    }

    RogueUiExit(&sWork->ui);
    ReleaseObjPalette(sWork->palette);
    ReleaseObjPalette(sWork->titlePalette);
    EwramFree(sWork);
}

Mode gModeRogueRelicList = {
    "mode_rogue_relic_list",
    RogueRelicList_Init,
    RogueRelicList_Update,
    RogueRelicList_Exit,
};
