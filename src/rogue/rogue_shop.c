#include "rogue.h"
#include "monsgage.h"
#include "card_types.h"
#include "card_ids.h"
#include "card_def_data.h"
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

// Axel's shop: permanent upgrades bought with memory shards. It shares the
// reward screen's look.

#define SHOP_TEXT_MAX 110
#define TITLE_SLOTS 36
#define LABEL_SLOTS 14
#define DETAIL_SLOTS 96
#define CARD_PAGE 2
// The upgrade a line of the two ability pages stands for.
#define UPGRADE(line) (sWork->page * ROGUE_UPGRADE_PAGE + (line))
#define PANEL_COLUMNS 13

typedef struct RogueShopWork {
    TextSlot title[TITLE_SLOTS];
    TextSlot labels[ROGUE_UPGRADE_PAGE][LABEL_SLOTS];
    TextSlot detail[DETAIL_SLOTS];
    u16 map[0x500 / 2];
    u8 text[SHOP_TEXT_MAX + 8];
    // The text slots keep reading their string: each has a buffer of its own.
    u8 titleText[40];
    u8 labelText[ROGUE_UPGRADE_PAGE][LABEL_SLOTS + 2];
    void* palette;
    void* cursorPalette;
    u8 titleCount;
    u8 labelCounts[ROGUE_UPGRADE_PAGE];
    u8 detailCount;
    u8 cursor;
    u8 state;
    u8 fromHub;
    u8 page; // the two pages of abilities, then the starting cards
} RogueShopWork;

static RogueShopWork* sWork;

static const u8 sShards[] = "Abilit\xE0  Frammenti: ";
static const u8 sSeals[] = "Carte iniziali   Sigilli: ";
static const u8 sNeeds[] = "\x1F" "Richiede ";
static const u8 sNeedsLevel[] = " liv. ";
static const u8 sStarterDetail[] = "Ogni run parte con\x1Fquesta carta nel mazzo";
static const u8 sOwned[] = "\x1F" "Sbloccata";
static const u8 sPages[] = "\x1FL/R: cambia pagina";
static const u8 sLevel[] = "\x1FLivello ";
static const u8 sCost[] = "\x1F" "Costo: ";
static const u8 sMaxed[] = "\x1F" "Al massimo";

static const u8 sLabelHp[] = "PV";
static const u8 sLabelCp[] = "PC";
static const u8 sLabelAttack[] = "Forza";
static const u8 sLabelCombo[] = "Combo+";
static const u8 sLabelAirJump[] = "Salto";
static const u8 sLabelReroll[] = "Rilanci";
static const u8 sLabelRelic[] = "Reliquia";
static const u8 sLabelGreed[] = "Avidit\xE0";
static const u8 sLabelXp[] = "Maestria";
static const u8 sLabelReload[] = "Ricarica";
static const u8 sLabelMoves[] = "Mosse";
static const u8 sLabelHeal[] = "Ristoro";
static const u8* const sLabels[ROGUE_UPGRADES] = {
    sLabelHp, sLabelCp, sLabelAttack, sLabelCombo, sLabelAirJump, sLabelReroll,
    sLabelRelic, sLabelGreed, sLabelXp, sLabelReload, sLabelMoves, sLabelHeal,
};

static const u8 sDetailHp[] = "Parti con +10 PV";
static const u8 sDetailCp[] = "Parti con +15 PC";
static const u8 sDetailAttack[] = "Parti con Forza +1";
static const u8 sDetailCombo[] = "Parti con Combo+";
static const u8 sDetailAirJump[] = "Parti col salto in aria";
static const u8 sDetailReroll[] = "Un rilancio a run";
static const u8 sDetailRelic[] = "Parti con una reliquia";
static const u8 sDetailGreed[] = "Tieni il 20% in pi\xF9\x1F" "dei frammenti";
static const u8 sDetailXp[] = "Le carte salgono\x1F" "di livello pi\xF9 in fretta";
static const u8 sDetailReload[] = "Ricarica pi\xF9 rapida\x1F" "del 10%";
static const u8 sDetailMoves[] = "Le mosse fanno il\x1F" "15% di danno in pi\xF9";
static const u8 sDetailHeal[] = "+2 PV dopo ogni\x1F" "battaglia vinta";
static const u8* const sDetails[ROGUE_UPGRADES] = {
    sDetailHp, sDetailCp, sDetailAttack, sDetailCombo, sDetailAirJump, sDetailReroll,
    sDetailRelic, sDetailGreed, sDetailXp, sDetailReload, sDetailMoves, sDetailHeal,
};

static u8* RogueShopAppend(u8* out, const u8* text) {
    while (*text != 0) {
        *out++ = *text++;
    }

    *out = 0;
    return out;
}

static u8* RogueShopNumber(u8* out, u16 value) {
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

// Reloads the shard count and the description of the line under the cursor.
static void RogueShopRefresh(void) {
    u8* out;

    s32 i;

    FreeTextSlots(sWork->title, TITLE_SLOTS);
    out = RogueShopAppend(sWork->titleText, sWork->page != CARD_PAGE ? sShards : sSeals);
    RogueShopNumber(out, sWork->page != CARD_PAGE ? gRogueMeta.shards : gRogueMeta.seals);
    sWork->titleCount = LoadTextSlots((u16*)sWork->titleText, sWork->title);

    for (i = 0; i < ROGUE_UPGRADE_PAGE; i++) {
        FreeTextSlots(sWork->labels[i], LABEL_SLOTS);

        if (sWork->page != CARD_PAGE) {
            sWork->labelCounts[i] = LoadTextSlots((u16*)sLabels[UPGRADE(i)], sWork->labels[i]);
        } else {
            // The card's name, cut to what a label holds.
            const u8* name = eu_0805E924(gCardDefs[CARD_ID(RogueStarterKind(i), ROGUE_STARTER_VALUE)].name);
            s32 n;

            for (n = 0; n < LABEL_SLOTS - 1 && name[n] != 0; n++) {
                sWork->labelText[i][n] = name[n];
            }

            sWork->labelText[i][n] = 0;
            sWork->labelCounts[i] = LoadTextSlots((u16*)sWork->labelText[i], sWork->labels[i]);
        }
    }

    FreeTextSlots(sWork->detail, DETAIL_SLOTS);

    if (sWork->page == CARD_PAGE) {
        out = RogueShopAppend(sWork->text, sStarterDetail);

        if (gRogueMeta.starters & (1 << sWork->cursor)) {
            out = RogueShopAppend(out, sOwned);
        } else {
            out = RogueShopAppend(out, sCost);
            out = RogueShopNumber(out, RogueStarterCost(sWork->cursor));
        }

        RogueShopAppend(out, sPages);
        sWork->detailCount = LoadTextSlots((u16*)sWork->text, sWork->detail);
        return;
    }

    out = RogueShopAppend(sWork->text, sDetails[UPGRADE(sWork->cursor)]);
    out = RogueShopAppend(out, sLevel);
    out = RogueShopNumber(out, RogueUpgradeLevel(UPGRADE(sWork->cursor)));
    *out++ = '/';
    out = RogueShopNumber(out, RogueUpgradeMax(UPGRADE(sWork->cursor)));

    if (!RogueUpgradeOpen(UPGRADE(sWork->cursor))) {
        // A branch not reached yet: what it grows from.
        out = RogueShopAppend(out, sNeeds);
        out = RogueShopAppend(out, sLabels[RogueUpgradeNeeds(UPGRADE(sWork->cursor))]);
        out = RogueShopAppend(out, sNeedsLevel);
        out = RogueShopNumber(out, RogueUpgradeNeedsLevel(UPGRADE(sWork->cursor)));
    } else if (RogueUpgradeLevel(UPGRADE(sWork->cursor)) < RogueUpgradeMax(UPGRADE(sWork->cursor))) {
        out = RogueShopAppend(out, sCost);
        out = RogueShopNumber(out, RogueUpgradeCost(UPGRADE(sWork->cursor)));
    } else {
        out = RogueShopAppend(out, sMaxed);
    }

    RogueShopAppend(out, sPages);

    sWork->detailCount = LoadTextSlots((u16*)sWork->text, sWork->detail);
}

static void RogueShop_Init(s32 from) {
    const u16* map = (const u16*)gUnk_09847798;
    s32 i;

    sWork = EwramAlloc(sizeof(RogueShopWork));
    sWork->cursor = 0;
    sWork->page = 0;
    sWork->state = 0;
    sWork->fromHub = from == ROGUE_SHOP_FROM_HUB;
    SetBgMode0();
    SetupBg(3, 0, 0x1D, 0);
    SetupBg(2, 0, 0x1E, 0);
    SetBgPriority(3, 3);
    SetBgPriority(2, 2);
    LoadBgTiles(3, gUnk_097FFB98, 0x2060);
    LoadBgPalette(3, gUnk_0984B118, 0xA0);
    LoadBgMap(3, gUnk_09848198, 0x500);

    for (i = 0; i < 0x500 / 2; i++) {
        sWork->map[i] = (i & 31) < PANEL_COLUMNS ? map[i] : map[0];
    }

    LoadBgMap(2, sWork->map, 0x500);
    sWork->palette = _08066468(1);
    sWork->cursorPalette = _08066468(0);
    InitTextSlots(sWork->title, TITLE_SLOTS);
    InitTextSlots(sWork->detail, DETAIL_SLOTS);

    for (i = 0; i < ROGUE_UPGRADE_PAGE; i++) {
        InitTextSlots(sWork->labels[i], LABEL_SLOTS);
    }

    RogueShopRefresh();
    FadeStartIn(0, 16);
}

static void RogueShop_Update(void) {
    s32 i;

    switch (sWork->state) {
    case 0:
        if (!FadeIsActive()) {
            sWork->state = 1;
        }
        break;
    case 1:
        if (GetKeysRepeat() & DPAD_UP) {
            sWork->cursor = (sWork->cursor + ROGUE_UPGRADE_PAGE - 1) % ROGUE_UPGRADE_PAGE;
            m4aSongNumStart(SONG_SYS_CLICK);
            RogueShopRefresh();
        } else if (GetKeysRepeat() & DPAD_DOWN) {
            sWork->cursor = (sWork->cursor + 1) % ROGUE_UPGRADE_PAGE;
            m4aSongNumStart(SONG_SYS_CLICK);
            RogueShopRefresh();
        } else if (GetKeysPressed() & (L_BUTTON | R_BUTTON)) {
            if (GetKeysPressed() & R_BUTTON) {
                sWork->page = (sWork->page + 1) % (CARD_PAGE + 1);
            } else {
                sWork->page = (sWork->page + CARD_PAGE) % (CARD_PAGE + 1);
            }

            m4aSongNumStart(SONG_SYS_CLICK);
            RogueShopRefresh();
        } else if (GetKeysPressed() & A_BUTTON) {
            if (sWork->page == CARD_PAGE ? RogueBuyStarter(sWork->cursor) : RogueBuyUpgrade(UPGRADE(sWork->cursor), !sWork->fromHub)) {
                m4aSongNumStart(SONG_SYS_KETTEI);
                RogueShopRefresh();
            } else {
                m4aSongNumStart(SONG_SYS_CANSEL);
            }
        } else if (GetKeysPressed() & B_BUTTON) {
            m4aSongNumStart(SONG_SYS_CANSEL);
            FadeStartOut(0, 16);
            sWork->state = 2;
        }
        break;
    case 2:
        if (!FadeIsActive()) {
            if (sWork->fromHub) {
                ModeRequest(&gModeRogueHub, 1);
            } else {
                func_080E04EC();
            }

            sWork->state = 3;
        }
        break;
    }

    DrawTextSlots((240 - GetTextSlotsWidth(sWork->title, sWork->titleCount)) / 2, 8, sWork->title, sWork->palette, 50,
                  sWork->titleCount);

    for (i = 0; i < ROGUE_UPGRADE_PAGE; i++) {
        DrawTextSlots(14, 40 + i * 16, sWork->labels[i], i == sWork->cursor ? sWork->cursorPalette : sWork->palette, 50,
                      sWork->labelCounts[i]);
    }

    DrawTextSlots(112, 60, sWork->detail, sWork->palette, 50, sWork->detailCount);
}

static void RogueShop_Exit(void) {
    s32 i;

    FreeTextSlots(sWork->title, TITLE_SLOTS);
    FreeTextSlots(sWork->detail, DETAIL_SLOTS);

    for (i = 0; i < ROGUE_UPGRADE_PAGE; i++) {
        FreeTextSlots(sWork->labels[i], LABEL_SLOTS);
    }

    ReleaseObjPalette(sWork->palette);
    ReleaseObjPalette(sWork->cursorPalette);
    EwramFree(sWork);
}

Mode gModeRogueShop = {
    "mode_rogue_shop",
    RogueShop_Init,
    RogueShop_Update,
    RogueShop_Exit,
};
