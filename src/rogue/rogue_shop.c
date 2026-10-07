#include "rogue.h"
#include "rogue_ui.h"
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
#include "sprite.h"
#include "sprites_status.h"
#include "system_state.h"
#include "text.h"

// Axel's shop: the ability tree, bought with memory shards, and the cards
// every run starts with, bought with the seals bosses leave. L and R change
// page.

#define TITLE_SLOTS 36
#define LABEL_SLOTS 14
#define DETAIL_SLOTS 96
#define PANEL_COLUMNS 13
#define SHOP_TEXT_MAX 110
#define TREE_NODES (ROGUE_TREE_BRANCHES * ROGUE_TREE_DEPTH)
#define TREE_X 30 // of the first column's icons
#define TREE_Y 30
#define TREE_STEP_X 36
#define TREE_STEP_Y 24

enum { PAGE_TREE, PAGE_TREE2, PAGE_CARDS, PAGES };

extern const u8 gRogueTreeIconTiles[], gRogueTreePalette[], gRogueTreeLockedPalette[], gRogueTreeFullPalette[];
extern const u8 gRogueTreeIcon2Tiles[], gRogueTree2Palette[], gRogueTree2LockedPalette[], gRogueTree2FullPalette[];

typedef struct RogueShopWork {
    TextSlot title[TITLE_SLOTS];
    TextSlot labels[ROGUE_STARTERS][LABEL_SLOTS];
    TextSlot detail[DETAIL_SLOTS];
    u16 map[0x500 / 2];
    u8 text[SHOP_TEXT_MAX + 8];
    // The text slots keep reading their string: each has a buffer of its own.
    u8 titleText[40];
    u8 labelText[ROGUE_STARTERS][LABEL_SLOTS + 2];
    void* palette;
    void* cursorPalette;
    void* iconTiles[TREE_NODES];
    void* iconPalette; // a node that can be bought
    void* lockedPalette; // one whose branch has not reached it
    void* fullPalette; // one with every level
    RogueUi ui;
    void* cardTiles; // the picture of the starting card under the cursor, 0 on the tree
    void* cardPalette;
    void* cardGfx;
    u8 titleCount;
    u8 labelCounts[ROGUE_STARTERS];
    u8 detailCount;
    u8 cursor; // on the tree: branch * ROGUE_TREE_DEPTH + depth
    u8 state;
    u8 fromHub;
    u8 page;
    u8 frame;
} RogueShopWork;

static RogueShopWork* sWork;

static const u8 sShards[] = "Abilit\xE0   Frammenti: ";
static const u8 sSeals[] = "Carte   Sigilli: ";
static const u8 sLevel[] = "  Liv. ";
static const u8 sCost[] = "\x1F" "Costo: ";
static const u8 sMaxed[] = "\x1F" "Al massimo";
static const u8 sNeeds[] = "\x1F" "Richiede ";
static const u8 sNeedsLevel[] = " liv. ";
static const u8 sStarterDetail[] = "Parti sempre con\x1Fquesta carta";
static const u8 sOwned[] = "\x1F" "Sbloccata";
static const u8 sPages[] = "\x1FL/R: cambia pagina";

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
static const u8 sLabelSecondLife[] = "Seconda vita";
static const u8 sLabelCrit[] = "Critico";
static const u8 sLabelFinisher[] = "Colpo finale";
static const u8 sLabelMagic[] = "Magia";
static const u8 sLabelSummon[] = "Alleati";
static const u8 sLabelSeal[] = "Sigillo";
static const u8 sLabelHp2[] = "PV II";
static const u8 sLabelHp3[] = "PV III";
static const u8 sLabelTough[] = "Tempra";
static const u8 sLabelFloorHeal[] = "Sosta";
static const u8 sLabelCp2[] = "PC II";
static const u8 sLabelCp3[] = "PC III";
static const u8 sLabelAttack2[] = "Forza II";
static const u8 sLabelAttack3[] = "Forza III";
static const u8 sLabelCombo2[] = "Combo+ II";
static const u8 sLabelCombo3[] = "Combo+ III";
static const u8 sLabelAirJump2[] = "Salto II";
static const u8 sLabelMomentum[] = "Slancio";
static const u8 sLabelShards[] = "Gruzzolo";
static const u8 sLabelReroll2[] = "Rilanci II";
static const u8 sLabelSeal2[] = "Sigillo II";
static const u8 sLabelRelic2[] = "Reliquia II";
static const u8 sLabelValue[] = "Pregio";
static const u8 sLabelCrit2[] = "Critico II";
static const u8* const sLabels[ROGUE_UPGRADES] = {
    sLabelHp, sLabelCp, sLabelAttack, sLabelCombo, sLabelAirJump, sLabelReroll, sLabelRelic, sLabelGreed, sLabelXp, sLabelReload, sLabelMoves, sLabelHeal, sLabelSecondLife, sLabelCrit, sLabelFinisher, sLabelMagic, sLabelSummon, sLabelSeal, sLabelHp2, sLabelHp3, sLabelTough, sLabelFloorHeal, sLabelCp2, sLabelCp3, sLabelAttack2, sLabelAttack3, sLabelCombo2, sLabelCombo3, sLabelAirJump2, sLabelMomentum, sLabelShards, sLabelReroll2, sLabelSeal2, sLabelRelic2, sLabelValue, sLabelCrit2,
};

static const u8 sDetailHp[] = "Parti con +10 PV";
static const u8 sDetailCp[] = "Parti con +15 PC";
static const u8 sDetailAttack[] = "Parti con Forza +1";
static const u8 sDetailCombo[] = "Un colpo in pi\xF9\x1Fnella combo";
static const u8 sDetailAirJump[] = "Parti col salto in aria";
static const u8 sDetailReroll[] = "Un rilancio a run";
static const u8 sDetailRelic[] = "Parti con una reliquia";
static const u8 sDetailGreed[] = "Tieni il 20% in pi\xF9\x1F" "dei frammenti";
static const u8 sDetailXp[] = "Le carte salgono\x1Fprima di livello";
static const u8 sDetailReload[] = "Ricarica pi\xF9 rapida\x1F" "del 10%";
static const u8 sDetailMoves[] = "Mosse: danno +15%";
static const u8 sDetailHeal[] = "+2 PV dopo ogni\x1F" "battaglia";
static const u8 sDetailSecondLife[] = "Parti con\x1FUltimo respiro";
static const u8 sDetailCrit[] = "Critici +4%";
static const u8 sDetailFinisher[] = "Colpo finale: +15%";
static const u8 sDetailMagic[] = "Magie: danno +10%";
static const u8 sDetailSummon[] = "Alleati: danno +15%";
static const u8 sDetailSeal[] = "Un sigillo in pi\xF9\x1F" "da ogni boss";
static const u8 sDetailHp2[] = "Parti con +10 PV";
static const u8 sDetailHp3[] = "Parti con +15 PV";
static const u8 sDetailTough[] = "Subisci il 4% in meno";
static const u8 sDetailFloorHeal[] = "A ogni piano recuperi\x1Fil 15% dei PV";
static const u8 sDetailCp2[] = "Parti con +15 PC";
static const u8 sDetailCp3[] = "Parti con +20 PC";
static const u8 sDetailAttack2[] = "Parti con Forza +1";
static const u8 sDetailAttack3[] = "Parti con Forza +1";
static const u8 sDetailCombo2[] = "Un altro colpo\x1Fnella combo";
static const u8 sDetailCombo3[] = "Un altro colpo\x1Fnella combo";
static const u8 sDetailAirJump2[] = "Parti con due\x1Fsalti in aria";
static const u8 sDetailMomentum[] = "Parti con Slancio";
static const u8 sDetailShards[] = "Parti con 10\x1F" "frammenti";
static const u8 sDetailReroll2[] = "Un rilancio in pi\xF9";
static const u8 sDetailSeal2[] = "Un altro sigillo\x1F" "da ogni boss";
static const u8 sDetailRelic2[] = "Parti con un'altra\x1Freliquia";
static const u8 sDetailValue[] = "Carte iniziali di\x1Fvalore pi\xF9 alto";
static const u8 sDetailCrit2[] = "Critici +4%";
static const u8* const sDetails[ROGUE_UPGRADES] = {
    sDetailHp, sDetailCp, sDetailAttack, sDetailCombo, sDetailAirJump, sDetailReroll, sDetailRelic, sDetailGreed, sDetailXp, sDetailReload, sDetailMoves, sDetailHeal, sDetailSecondLife, sDetailCrit, sDetailFinisher, sDetailMagic, sDetailSummon, sDetailSeal, sDetailHp2, sDetailHp3, sDetailTough, sDetailFloorHeal, sDetailCp2, sDetailCp3, sDetailAttack2, sDetailAttack3, sDetailCombo2, sDetailCombo3, sDetailAirJump2, sDetailMomentum, sDetailShards, sDetailReroll2, sDetailSeal2, sDetailRelic2, sDetailValue, sDetailCrit2,
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

// The upgrade the cursor is on, on the tree.
static u8 RogueShopUpgrade(void) {
    return RogueTreeNode(sWork->page * ROGUE_TREE_BRANCHES + sWork->cursor / ROGUE_TREE_DEPTH, sWork->cursor % ROGUE_TREE_DEPTH);
}

// Reloads the title and the description of what is under the cursor.
static void RogueShopRefresh(void) {
    u8* out;
    u8 upgrade;
    s32 i;

    FreeTextSlots(sWork->title, TITLE_SLOTS);
    out = RogueShopAppend(sWork->titleText, sWork->page != PAGE_CARDS ? sShards : sSeals);
    RogueShopNumber(out, sWork->page != PAGE_CARDS ? gRogueMeta.shards : gRogueMeta.seals);
    sWork->titleCount = LoadTextSlots((u16*)sWork->titleText, sWork->title);
    FreeTextSlots(sWork->detail, DETAIL_SLOTS);

    for (i = 0; i < ROGUE_STARTERS; i++) {
        FreeTextSlots(sWork->labels[i], LABEL_SLOTS);
        sWork->labelCounts[i] = 0;
    }

    if (sWork->cardTiles != 0) {
        ReleaseObjTiles(sWork->cardTiles);
        ReleaseObjPalette(sWork->cardPalette);
        sWork->cardTiles = 0;
    }

    if (sWork->page == PAGE_CARDS) {
        const CardDef* card = &gCardDefs[CARD_ID(RogueStarterKind(sWork->cursor), ROGUE_STARTER_VALUE)];

        sWork->cardTiles = LoadObjTiles(card->tiles, 0x200);
        sWork->cardPalette = LoadObjPalette(card->palette, 32);
        sWork->cardGfx = card->gfx;
    }

    if (sWork->page == PAGE_CARDS) {
        for (i = 0; i < ROGUE_STARTERS; i++) {
            // The card's name, cut to what a label holds.
            const u8* name = eu_0805E924(gCardDefs[CARD_ID(RogueStarterKind(i), ROGUE_STARTER_VALUE)].name);
            s32 n;

            for (n = 0; n < LABEL_SLOTS - 1 && name[n] != 0; n++) {
                sWork->labelText[i][n] = name[n];
            }

            sWork->labelText[i][n] = 0;
            sWork->labelCounts[i] = LoadTextSlots((u16*)sWork->labelText[i], sWork->labels[i]);
        }

        out = RogueShopAppend(sWork->text, sStarterDetail);

        if (gRogueMeta.starters & (1 << sWork->cursor)) {
            out = RogueShopAppend(out, sOwned);
        } else {
            out = RogueShopAppend(out, sCost);
            out = RogueShopNumber(out, RogueStarterCost(sWork->cursor));
        }

        sWork->detailCount = LoadTextSlots((u16*)sWork->text, sWork->detail);
        return;
    }

    // The tree: the node's name and level, what it does, and what it costs
    // or what its branch still needs.
    upgrade = RogueShopUpgrade();
    out = RogueShopAppend(sWork->text, sLabels[upgrade]);
    out = RogueShopAppend(out, sLevel);
    out = RogueShopNumber(out, RogueUpgradeLevel(upgrade));
    *out++ = '/';
    out = RogueShopNumber(out, RogueUpgradeMax(upgrade));
    *out++ = 0x1F;
    out = RogueShopAppend(out, sDetails[upgrade]);

    if (!RogueUpgradeOpen(upgrade)) {
        out = RogueShopAppend(out, sNeeds);
        out = RogueShopAppend(out, sLabels[RogueUpgradeNeeds(upgrade)]);
        out = RogueShopAppend(out, sNeedsLevel);
        RogueShopNumber(out, RogueUpgradeNeedsLevel(upgrade));
    } else if (RogueUpgradeLevel(upgrade) < RogueUpgradeMax(upgrade)) {
        out = RogueShopAppend(out, sCost);
        RogueShopNumber(out, RogueUpgradeCost(upgrade));
    } else {
        RogueShopAppend(out, sMaxed);
    }

    sWork->detailCount = LoadTextSlots((u16*)sWork->text, sWork->detail);
}

// Loads the icons and the palettes of the page of the tree shown, none for
// the cards.
static void RogueShopIcons(void) {
    const u8* tiles = sWork->page == PAGE_TREE2 ? gRogueTreeIcon2Tiles : gRogueTreeIconTiles;
    s32 i;

    if (sWork->iconPalette != 0) {
        for (i = 0; i < TREE_NODES; i++) {
            ReleaseObjTiles(sWork->iconTiles[i]);
        }

        ReleaseObjPalette(sWork->iconPalette);
        ReleaseObjPalette(sWork->lockedPalette);
        ReleaseObjPalette(sWork->fullPalette);
        sWork->iconPalette = 0;
    }

    if (sWork->page == PAGE_CARDS) {
        return;
    }

    sWork->iconPalette = LoadObjPalette((void*)(sWork->page == PAGE_TREE2 ? gRogueTree2Palette : gRogueTreePalette), 32);
    sWork->lockedPalette = LoadObjPalette((void*)(sWork->page == PAGE_TREE2 ? gRogueTree2LockedPalette : gRogueTreeLockedPalette), 32);
    sWork->fullPalette = LoadObjPalette((void*)(sWork->page == PAGE_TREE2 ? gRogueTree2FullPalette : gRogueTreeFullPalette), 32);

    for (i = 0; i < TREE_NODES; i++) {
        sWork->iconTiles[i] = LoadObjTiles((void*)(tiles + i * 0x200), 0x200);
    }
}

// The panel on the left holds the list of cards; the tree has the whole
// screen.
static void RogueShopPanel(void) {
    if (sWork->page == PAGE_CARDS) {
        // The cards: the list, the window and the panel, as the rewards.
        RogueUiFrameMap(sWork->map);
        SetBgScroll(2, 0, 0);
    } else {
        // The tree fills the screen: only the panel, low and centred.
        RogueUiPanelMap(sWork->map);
        SetBgScroll(2, ROGUE_UI_PANEL_SCROLL_X, ROGUE_UI_PANEL_SCROLL_Y);
    }

    RogueShopIcons();

    LoadBgMap(2, sWork->map, 0x500);
}

static void RogueShop_Init(s32 from) {
    s32 i;

    sWork = EwramAlloc(sizeof(RogueShopWork));
    sWork->cursor = 0;
    sWork->page = PAGE_TREE;
    sWork->state = 0;
    sWork->frame = 0;
    sWork->cardTiles = 0;
    sWork->fromHub = from == ROGUE_SHOP_FROM_HUB;
    SetBgMode0();
    SetupBg(3, 0, 0x1D, 0);
    SetupBg(2, 0, 0x1E, 0);
    SetBgPriority(3, 3);
    SetBgPriority(2, 2);
    LoadBgTiles(3, gUnk_097FFB98, 0x2060);
    LoadBgPalette(3, gUnk_0984B118, 0xA0);
    LoadBgMap(3, gUnk_09848198, 0x500);
    sWork->iconPalette = 0;
    RogueShopPanel();
    RogueUiInit(&sWork->ui);
    sWork->palette = _08066468(1);
    sWork->cursorPalette = _08066468(0);

    InitTextSlots(sWork->title, TITLE_SLOTS);
    InitTextSlots(sWork->detail, DETAIL_SLOTS);

    for (i = 0; i < ROGUE_STARTERS; i++) {
        InitTextSlots(sWork->labels[i], LABEL_SLOTS);
    }

    RogueShopRefresh();
    FadeStartIn(0, 16);
}

static void RogueShopMove(s32 dx, s32 dy) {
    s32 branch = sWork->cursor / ROGUE_TREE_DEPTH;
    s32 depth = sWork->cursor % ROGUE_TREE_DEPTH;

    if (sWork->page == PAGE_CARDS) {
        sWork->cursor = (sWork->cursor + ROGUE_STARTERS + dy) % ROGUE_STARTERS;
    } else {
        branch = (branch + ROGUE_TREE_BRANCHES + dy) % ROGUE_TREE_BRANCHES;
        depth = (depth + ROGUE_TREE_DEPTH + dx) % ROGUE_TREE_DEPTH;
        sWork->cursor = branch * ROGUE_TREE_DEPTH + depth;
    }

    m4aSongNumStart(SONG_SYS_CLICK);
    RogueShopRefresh();
}

static void RogueShop_Update(void) {
    u16 repeat = GetKeysRepeat();
    s32 i;

    sWork->frame++;

    switch (sWork->state) {
    case 0:
        if (!FadeIsActive()) {
            sWork->state = 1;
        }
        break;
    case 1:
        if (repeat & DPAD_UP) {
            RogueShopMove(0, -1);
        } else if (repeat & DPAD_DOWN) {
            RogueShopMove(0, 1);
        } else if ((repeat & DPAD_LEFT) && sWork->page != PAGE_CARDS) {
            RogueShopMove(-1, 0);
        } else if ((repeat & DPAD_RIGHT) && sWork->page != PAGE_CARDS) {
            RogueShopMove(1, 0);
        } else if (GetKeysPressed() & (L_BUTTON | R_BUTTON)) {
            sWork->page = (GetKeysPressed() & R_BUTTON) ? (sWork->page + 1) % PAGES : (sWork->page + PAGES - 1) % PAGES;
            sWork->cursor = 0;
            m4aSongNumStart(SONG_SYS_CLICK);
            RogueShopPanel();
            RogueShopRefresh();
        } else if (GetKeysPressed() & A_BUTTON) {
            if (sWork->page == PAGE_CARDS ? RogueBuyStarter(sWork->cursor) : RogueBuyUpgrade(RogueShopUpgrade(), !sWork->fromHub)) {
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

    DrawTextSlots(236 - GetTextSlotsWidth(sWork->title, sWork->titleCount), 1, sWork->title, sWork->palette, 50, sWork->titleCount);

    if (sWork->page == PAGE_CARDS) {
        for (i = 0; i < ROGUE_STARTERS; i++) {
            s16 x = RogueUiPlate(&sWork->ui, 12, 34 + i * 18, i == (s32)sWork->cursor);

            DrawTextSlots(x, 34 + i * 18 + 2, sWork->labels[i], sWork->palette, 50, sWork->labelCounts[i]);
        }

        RogueUiGlove(&sWork->ui, 16, 34 + sWork->cursor * 18 + 8);

        if (sWork->cardTiles != 0) {
            DrawSprite(172, 42, sWork->cardGfx, sWork->cardTiles, sWork->cardPalette, 0, 0, 50);
        }

        DrawTextSlots(110, 74, sWork->detail, sWork->palette, 50, sWork->detailCount);
        return;
    }

    // The tree: a branch a row. The node under the cursor bobs.
    for (i = 0; i < TREE_NODES; i++) {
        u8 upgrade = RogueTreeNode(sWork->page * ROGUE_TREE_BRANCHES + i / ROGUE_TREE_DEPTH, i % ROGUE_TREE_DEPTH);
        void* palette = sWork->iconPalette;
        s32 y = TREE_Y + (i / ROGUE_TREE_DEPTH) * TREE_STEP_Y;

        if (!RogueUpgradeOpen(upgrade)) {
            palette = sWork->lockedPalette;
        } else if (RogueUpgradeLevel(upgrade) >= RogueUpgradeMax(upgrade)) {
            palette = sWork->fullPalette;
        }

        if (i == (s32)sWork->cursor && (sWork->frame & 16)) {
            y -= 3;
        }

        DrawSprite(TREE_X + (i % ROGUE_TREE_DEPTH) * TREE_STEP_X, y, gCardDefs[0].gfx, sWork->iconTiles[i], palette, 0, 0, 50);
    }

    DrawTextSlots(58, 102, sWork->detail, sWork->palette, 50, sWork->detailCount);
}

static void RogueShop_Exit(void) {
    s32 i;

    FreeTextSlots(sWork->title, TITLE_SLOTS);
    FreeTextSlots(sWork->detail, DETAIL_SLOTS);

    for (i = 0; i < ROGUE_STARTERS; i++) {
        FreeTextSlots(sWork->labels[i], LABEL_SLOTS);
    }

    sWork->page = PAGE_CARDS;
    RogueShopIcons();

    if (sWork->cardTiles != 0) {
        ReleaseObjTiles(sWork->cardTiles);
        ReleaseObjPalette(sWork->cardPalette);
    }

    RogueUiExit(&sWork->ui);
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
