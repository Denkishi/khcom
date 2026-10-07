#include "rogue.h"
#include "registration_data.h"
#include "display.h"
#include "fade.h"
#include "gba/io_reg.h"
#include "gba/keys.h"
#include "key.h"
#include "m4a_song.h"
#include "malloc.h"
#include "obj_api.h"
#include "system_state.h"
#include "text.h"

// The hub: the Station of Calling, where every run starts from. It shows what
// has been unlocked and leads to a new run or to the permanent upgrades.

extern const u8 gRogueStationTiles[31424];
extern const u16 gRogueStationMap[640];
extern const u16 gRogueStationPalette[256];

#define HUB_OPTIONS 2
#define HUB_LINES (2 + HUB_OPTIONS)
#define LINE_SLOTS 28

typedef struct RogueHubWork {
    TextSlot lines[HUB_LINES][LINE_SLOTS];
    u8 counts[HUB_LINES];
    u8 text[40];
    void* palette;
    void* cursorPalette;
    u8 cursor;
    u8 state;
} RogueHubWork;

static RogueHubWork* sWork;

static const u8 sTitle[] = "Stazione del Risveglio";
static const u8 sShards[] = "Frammenti ";
static const u8 sChapters[] = "   Capitoli ";
static const u8 sStart[] = "Inizia una run";
static const u8 sUpgrades[] = "Potenziamenti";

static u8* RogueHubAppend(u8* out, const u8* text) {
    while (*text != 0) {
        *out++ = *text++;
    }

    *out = 0;
    return out;
}

static u8* RogueHubNumber(u8* out, u16 value) {
    if (value >= 1000) {
        *out++ = '0' + value / 1000;
    }

    if (value >= 100) {
        *out++ = '0' + value / 100 % 10;
    }

    if (value >= 10) {
        *out++ = '0' + value / 10 % 10;
    }

    *out++ = '0' + value % 10;
    *out = 0;
    return out;
}

static void RogueHubLine(u8 line, const u8* text) {
    InitTextSlots(sWork->lines[line], LINE_SLOTS);
    sWork->counts[line] = LoadTextSlots((u16*)text, sWork->lines[line]);
}

static void RogueHub_Init(s32 arg) {
    u8* out;

    sWork = EwramAlloc(sizeof(RogueHubWork));
    sWork->cursor = arg;
    sWork->state = 0;
    SetBgMode0();
    SetupBg(3, 0, 0x1D, 0);
    SetBgPriority(3, 3);
    // The picture is the mod's only 256-colour background.
    gBg3Cnt |= BGCNT_256COLOR;
    LoadBgTiles(3, (void*)gRogueStationTiles, sizeof(gRogueStationTiles));
    LoadBgPalette(3, (void*)gRogueStationPalette, sizeof(gRogueStationPalette));
    LoadBgMap(3, (void*)gRogueStationMap, sizeof(gRogueStationMap));
    sWork->palette = _08066468(1);
    sWork->cursorPalette = _08066468(0);
    RogueHubLine(0, sTitle);
    out = RogueHubAppend(sWork->text, sShards);
    out = RogueHubNumber(out, gRogueMeta.shards);
    out = RogueHubAppend(out, sChapters);
    *out++ = '0' + gRogueMeta.chapters;
    *out++ = '/';
    *out++ = '0' + ROGUE_CHAPTERS;
    *out = 0;
    RogueHubLine(1, sWork->text);
    RogueHubLine(2, sStart);
    RogueHubLine(3, sUpgrades);
    m4aSongNumStartOrContinue(SONG_BGM_TITLE);
    FadeStartIn(0, 16);
}

static void RogueHub_Update(void) {
    s32 i;

    switch (sWork->state) {
    case 0:
        if (!FadeIsActive()) {
            sWork->state = 1;
        }
        break;
    case 1:
        if (GetKeysRepeat() & (DPAD_UP | DPAD_DOWN)) {
            sWork->cursor ^= 1;
            m4aSongNumStart(SONG_SYS_CLICK);
        } else if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            m4aSongNumStart(sWork->cursor == 0 ? SONG_SYS_START : SONG_SYS_KETTEI);
            FadeStartOut(0, 16);
            sWork->state = 2;
        }
        break;
    case 2:
        if (!FadeIsActive()) {
            if (sWork->cursor == 0) {
                RogueStartRun();
            } else {
                ModeRequest(&gModeRogueShop, ROGUE_SHOP_FROM_HUB);
            }

            sWork->state = 3;
        }
        break;
    }

    DrawTextSlots((240 - GetTextSlotsWidth(sWork->lines[0], sWork->counts[0])) / 2, 4, sWork->lines[0], sWork->cursorPalette, 50,
                  sWork->counts[0]);
    DrawTextSlots((240 - GetTextSlotsWidth(sWork->lines[1], sWork->counts[1])) / 2, 110, sWork->lines[1], sWork->palette, 50,
                  sWork->counts[1]);

    for (i = 0; i < HUB_OPTIONS; i++) {
        DrawTextSlots((240 - GetTextSlotsWidth(sWork->lines[2 + i], sWork->counts[2 + i])) / 2, 126 + i * 15, sWork->lines[2 + i],
                      i == sWork->cursor ? sWork->cursorPalette : sWork->palette, 50, sWork->counts[2 + i]);
    }
}

static void RogueHub_Exit(void) {
    s32 i;

    for (i = 0; i < HUB_LINES; i++) {
        FreeTextSlots(sWork->lines[i], LINE_SLOTS);
    }

    ReleaseObjPalette(sWork->palette);
    ReleaseObjPalette(sWork->cursorPalette);
    EwramFree(sWork);
}

Mode gModeRogueHub = {
    "mode_rogue_hub",
    RogueHub_Init,
    RogueHub_Update,
    RogueHub_Exit,
};
