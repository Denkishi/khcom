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
static const u8 sNameKnives[] = "Lame di Larxene";
static const u8 sNameFire[] = "Lama ardente";
static const u8 sNameIce[] = "Lama gelida";
static const u8 sNameThunder[] = "Lama tonante";
static const u8 sNameEcho[] = "Eco arcano";
static const u8 sNamePillar[] = "Gelo di Vexen";
static const u8 sNameChakram[] = "Chakram di Axel";
static const u8 sNameNeedles[] = "Aghi di Vexen";
static const u8 sNamePetals[] = "Petali di Marluxia";
static const u8 sNameShards[] = "Schegge di Vexen";
static const u8 sNameFireball[] = "Globo di Ade";
static const u8 sNameFireBurst[] = "Vampa di Ade";
static const u8 sNameRock[] = "Roccia di Lexaeus";
static const u8 sNameBomb[] = "Bomba di Uncino";
static const u8 sNameMulti[] = "Moltiplicatore";
static const u8 sNameFan[] = "Ventaglio";
static const u8 sNameHoming[] = "Segugio";
static const u8 sNameMoveEcho[] = "Doppio lancio";
static const u8 sNameGiant[] = "Gigante";
static const u8 sNamePrism[] = "Prisma";
static const u8 sNameBerserk[] = "Furia";
static const u8 sNameThorns[] = "Spine";
static const u8 sNameComboHeal[] = "Ritmo vitale";
static const u8 sNameAirMaster[] = "Asso dei cieli";
static const u8 sNameTagTeam[] = "Gioco di squadra";
static const u8 sNameTreasurer[] = "Tesoriere";

static const u8 sTextVampire[] = "Ogni colpo a segno\x1Fti cura di 1 PV";
static const u8 sTextCritical[] = "Un colpo su sette\x1F" "fa danno doppio";
static const u8 sTextSecondWind[] = "Una volta a battaglia\x1Fresti a 1 PV";
static const u8 sTextGlass[] = "Dai e subisci il\x1F" "50% di danno in pi\xF9";
static const u8 sTextMomentum[] = "Il bonus combo\x1F" "arriva al 60%";
static const u8 sTextReload[] = "Il mazzo si ricarica\x1Fmolto pi\xF9 in fretta";
static const u8 sTextKnives[] = "Il finisher lancia\x1Ftre coltelli";
static const u8 sTextFire[] = "Ogni colpo di Keyblade\x1F\xE8 seguito da un Fuoco";
static const u8 sTextIce[] = "Ogni colpo di Keyblade\x1F\xE8 seguito da un Gelo";
static const u8 sTextThunder[] = "Ogni colpo di Keyblade\x1F\xE8 seguito da un Tuono";
static const u8 sTextEcho[] = "Ogni magia a segno\x1Fcolpisce due volte";
static const u8 sTextPillar[] = "Il finisher alza un\x1F" "blocco di ghiaccio";
static const u8 sTextChakram[] = "Il finisher lancia\x1Fun chakram di fuoco";
static const u8 sTextNeedles[] = "Il finisher lancia\x1Ftre aghi di ghiaccio";
static const u8 sTextPetals[] = "Il finisher scatena\x1Fpetali tutt'intorno";
static const u8 sTextShards[] = "Il finisher fa\x1F" "esplodere ghiaccio";
static const u8 sTextFireball[] = "Il finisher lancia\x1Fun globo di fuoco";
static const u8 sTextFireBurst[] = "Il finisher scatena\x1Funa vampa davanti";
static const u8 sTextRock[] = "Il finisher alza\x1Funa roccia davanti";
static const u8 sTextBomb[] = "Il finisher lancia\x1Funa bomba";
static const u8 sTextMulti[] = "Ogni mossa lanciata\x1F" "ha due colpi in pi\xF9";
static const u8 sTextFan[] = "I colpi lanciati\x1Fsi aprono a ventaglio";
static const u8 sTextHoming[] = "I colpi lanciati\x1Finseguono il bersaglio";
static const u8 sTextMoveEcho[] = "Ogni mossa si ripete\x1F" "dopo un istante";
static const u8 sTextGiant[] = "Le mosse colpiscono\x1Fpi\xF9 largo e pi\xF9 forte";
static const u8 sTextPrism[] = "Le mosse prendono\x1Fl'elemento del mazzo";
static const u8 sTextBerserk[] = "Sotto un quarto dei PV\x1F" "fai il 50% in pi\xF9";
static const u8 sTextThorns[] = "Quando vieni colpito\x1Fpetali tutt'intorno";
static const u8 sTextComboHeal[] = "Ogni 10 colpi di fila\x1Fti curi di 3 PV";
static const u8 sTextAirMaster[] = "In aria fai il\x1F" "30% di danno in pi\xF9";
static const u8 sTextTagTeam[] = "Evocazioni e nemici\x1F" "chiamati: 50% in pi\xF9";
static const u8 sTextTreasurer[] = "Ogni stanza d\xE0 il\x1F" "50% di frammenti in pi\xF9";

static const u8* const sNames[ROGUE_RELICS] = {
    sNameVampire, sNameCritical, sNameSecondWind, sNameGlass, sNameMomentum, sNameReload, sNameKnives, sNameFire, sNameIce, sNameThunder, sNameEcho, sNamePillar, sNameChakram, sNameNeedles, sNamePetals, sNameShards,
    sNameFireball, sNameFireBurst, sNameRock, sNameBomb, sNameMulti, sNameFan, sNameHoming, sNameMoveEcho, sNameGiant, sNamePrism,
    sNameBerserk, sNameThorns, sNameComboHeal, sNameAirMaster, sNameTagTeam, sNameTreasurer,
};

static const u8* const sTexts[ROGUE_RELICS] = {
    sTextVampire, sTextCritical, sTextSecondWind, sTextGlass, sTextMomentum, sTextReload, sTextKnives, sTextFire, sTextIce, sTextThunder, sTextEcho, sTextPillar, sTextChakram, sTextNeedles, sTextPetals, sTextShards,
    sTextFireball, sTextFireBurst, sTextRock, sTextBomb, sTextMulti, sTextFan, sTextHoming, sTextMoveEcho, sTextGiant, sTextPrism,
    sTextBerserk, sTextThorns, sTextComboHeal, sTextAirMaster, sTextTagTeam, sTextTreasurer,
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

static u8 RogueRelicUnlocked(u8 relic) {
    u8 pool;

    if (relic == ROGUE_RELIC_KNIVES) {
        return gRogueMeta.bossMoves & ROGUE_BOSS_MOVE_LARXENE;
    }

    if (relic == ROGUE_RELIC_ICE_PILLAR) {
        return gRogueMeta.bossMoves & ROGUE_BOSS_MOVE_VEXEN;
    }

    // The synergy relics come two for each chapter unlocked.
    if (relic >= ROGUE_FIRST_SYNERGY) {
        return relic - ROGUE_FIRST_SYNERGY < gRogueMeta.chapters * 2;
    }

    // A modifier is of use to a run that has a move, a blade or the echo.
    if (relic >= ROGUE_FIRST_MOD) {
        return gRogueMeta.bossMoves != 0 && (gRogue.relics >> ROGUE_RELIC_KNIVES) != 0;
    }

    if (relic >= ROGUE_RELIC_CHAKRAM) {
        return RogueMoveUnlocked(relic - ROGUE_RELIC_CHAKRAM);
    }

    if (relic == ROGUE_RELIC_ARCANE_ECHO) {
        return gRogueMeta.chapters >= 2;
    }

    // The infused blades come with the second chapter, and only one of them
    // to a run.
    if (relic >= ROGUE_RELIC_FIRE_BLADE) {
        return gRogueMeta.chapters >= 2 && !RogueHasRelic(ROGUE_RELIC_FIRE_BLADE) &&
               !RogueHasRelic(ROGUE_RELIC_ICE_BLADE) && !RogueHasRelic(ROGUE_RELIC_THUNDER_BLADE);
    }

    // Two relics are in the pool from the start and each chapter adds two.
    pool = gRogueMeta.chapters * 2;
    return relic < pool;
}

// Returns a relic that is unlocked and that the run does not have yet, or
// ROGUE_RELICS.
u8 RogueRollRelic(void) {
    u8 relic;
    s32 tries;

    for (tries = 0; tries < 64; tries++) {
        relic = RogueRandBelow(ROGUE_RELICS);

        if (RogueRelicUnlocked(relic) && !RogueHasRelic(relic)) {
            return relic;
        }
    }

    return ROGUE_RELICS;
}

// A move is unlocked by beating the character it comes from.
u8 RogueMoveUnlocked(u8 move) {
    static const u8 bosses[ROGUE_MOVES] = {
        ROGUE_BOSS_MOVE_AXEL, ROGUE_BOSS_MOVE_VEXEN, ROGUE_BOSS_MOVE_MARLUXIA, ROGUE_BOSS_MOVE_VEXEN,
        ROGUE_BOSS_MOVE_HADES, ROGUE_BOSS_MOVE_HADES, ROGUE_BOSS_MOVE_LEXAEUS, ROGUE_BOSS_MOVE_HOOK,
    };

    return (gRogueMeta.bossMoves & bosses[move]) != 0;
}

// Beating a boss can unlock its move for later runs.
void RogueOnBossBeaten(u16 battle) {
    // Every boss and miniboss leaves a seal, for the starting cards.
    if (gRogueMeta.seals < ROGUE_SEALS_MAX) {
        gRogueMeta.seals++;
    }

    // Mickey, beaten, can be played: picked in the hub.
    if (battle == 0x9D && gRogue.bossSkin == ROGUE_SKIN_MICKEY) {
        gRogueMeta.flags |= ROGUE_META_MICKEY;
    }

    if (battle == 0xA3 || battle == 0xAE) {
        gRogueMeta.bossMoves |= ROGUE_BOSS_MOVE_LARXENE;
    }

    if (battle == 0xA4 || battle == 0xAF || battle == 0xB0) {
        gRogueMeta.bossMoves |= ROGUE_BOSS_MOVE_VEXEN;
    }

    if (battle == 0xA0) {
        gRogueMeta.bossMoves |= ROGUE_BOSS_MOVE_HADES;
    }

    if (battle == 0xA7) {
        gRogueMeta.bossMoves |= ROGUE_BOSS_MOVE_LEXAEUS;
    }

    if (battle == 0x9E) {
        gRogueMeta.bossMoves |= ROGUE_BOSS_MOVE_HOOK;
    }

    if (battle == 0xA2 || battle == 0xAD) {
        gRogueMeta.bossMoves |= ROGUE_BOSS_MOVE_AXEL;
    }

    if (battle == 0xA5) {
        gRogueMeta.bossMoves |= ROGUE_BOSS_MOVE_MARLUXIA;
    }
}

// The run's pages in the pause menu: where the run is and its builds, its
// relics, and the records with the way to give the run up. A turns the page,
// B closes.

#define LINE_SLOTS 26
#define PAGE_LINES 9

typedef struct RogueRelicsWork {
    TextSlot lines[PAGE_LINES][LINE_SLOTS];
    u8 counts[PAGE_LINES];
    u8 text[40];
    void* palette;
    void* titlePalette;
    u8 lineCount;
    u8 page;
    u8 state;
    u8 abandon; // set by a first press of select on the records page
    u8 leave; // the run was given up
} RogueRelicsWork;

static RogueRelicsWork* sWork;

static const u8 sTitle[] = "La tua run";
static const u8 sTitleRelics[] = "Reliquie";
static const u8 sTitleRecords[] = "Record";
static const u8 sRuns[] = "Run giocate: ";
static const u8 sWins[] = "Run completate: ";
static const u8 sBest[] = "Stanze in una run: ";
static const u8 sChaptersLine[] = "Capitoli: ";
static const u8 sAbandon[] = "SELECT: abbandona";
static const u8 sAbandonSure[] = "SELECT ancora: conferma";
static const u8 sFloor[] = "Piano ";
static const u8 sCombo[] = "  Combo+";
static const u8 sJumps[] = "  Salti ";
static const u8 sNone[] = "Nessuna";
static const u8 sNoBuild[] = "Nessuna build attiva";
static const u8 sCards[] = "Carte Lv2: ";
static const u8 sCards3[] = "  Lv3: ";
static const u8 sBuildFire[] = "Build Fuoco";
static const u8 sBuildIce[] = "Build Gelo";
static const u8 sBuildThunder[] = "Build Tuono";
static const u8 sBuildBlade[] = "Build Lame";
static const u8 sBuildSpell[] = "Build Magie";
static const u8 sBuildSummon[] = "Build Evocazioni";
static const u8 sBuildProjectile[] = "Build Proiettili";
static const u8* const sBuildNames[ROGUE_BUILDS] = {
    sBuildFire, sBuildIce, sBuildThunder, sBuildBlade, sBuildSpell, sBuildSummon, sBuildProjectile,
};

static u8* RogueRelicsAppend(u8* out, const u8* text) {
    while (*text != 0) {
        *out++ = *text++;
    }

    *out = 0;
    return out;
}

static u8* RogueRelicsNumber(u8* out, u8 value) {
    *out++ = '0' + value / 10;
    *out++ = '0' + value % 10;
    *out = 0;
    return out;
}

static void RogueRelicsLine(const u8* text) {
    if (sWork->lineCount < PAGE_LINES) {
        sWork->counts[sWork->lineCount] = LoadTextSlots((u16*)text, sWork->lines[sWork->lineCount]);
        sWork->lineCount++;
    }
}

static void RogueRelicsRecord(const u8* label, u16 value) {
    u8* out = RogueRelicsAppend(sWork->text, label);

    if (value >= 100) {
        *out++ = '0' + value / 100 % 10;
    }

    RogueRelicsNumber(out, value % 100);
    RogueRelicsLine(sWork->text);
}

static void RogueRelicsShowPage(void) {
    u8* out;
    u8 first;
    u8 i;

    for (i = 0; i < PAGE_LINES; i++) {
        FreeTextSlots(sWork->lines[i], LINE_SLOTS);
    }

    sWork->lineCount = 0;

    if (sWork->page == 0) {
        RogueRelicsLine(sTitle);
        out = RogueRelicsAppend(sWork->text, sFloor);
        out = RogueRelicsNumber(out, gRogue.floor + 1);
        out = RogueRelicsAppend(out, sCombo);
        *out++ = '0' + gRogue.comboPlus;
        out = RogueRelicsAppend(out, sJumps);
        *out++ = '0' + gRogue.airJumps;
        *out = 0;
        RogueRelicsLine(sWork->text);
        out = RogueRelicsAppend(sWork->text, sCards);
        out = RogueRelicsNumber(out, RogueCountCards(2));
        out = RogueRelicsAppend(out, sCards3);
        RogueRelicsNumber(out, RogueCountCards(3));
        RogueRelicsLine(sWork->text);
        first = sWork->lineCount;

        for (i = 0; i < ROGUE_BUILDS; i++) {
            if (RogueBuildBonus(i) != 0) {
                out = RogueRelicsAppend(sWork->text, sBuildNames[i]);
                *out++ = ' ';
                *out++ = '+';
                out = RogueRelicsNumber(out, RogueBuildBonus(i));
                *out++ = '%';
                *out = 0;
                RogueRelicsLine(sWork->text);
            }
        }

        if (sWork->lineCount == first) {
            RogueRelicsLine(sNoBuild);
        }
    } else if (sWork->page == 2) {
        RogueRelicsLine(sTitleRecords);
        RogueRelicsRecord(sRuns, gRogueMeta.runs);
        RogueRelicsRecord(sWins, gRogueMeta.wins);
        RogueRelicsRecord(sBest, gRogueMeta.bestDepth);
        RogueRelicsRecord(sChaptersLine, gRogueMeta.chapters);
        RogueRelicsLine(sWork->abandon ? sAbandonSure : sAbandon);
    } else {
        RogueRelicsLine(sTitleRelics);
        first = sWork->lineCount;

        for (i = 0; i < ROGUE_RELICS; i++) {
            if (RogueHasRelic(i)) {
                RogueRelicsLine(sNames[i]);
            }
        }

        if (sWork->lineCount == first) {
            RogueRelicsLine(sNone);
        }
    }
}

static void RogueRelics_Init(s32 arg) {
    s32 i;

    sWork = EwramAlloc(sizeof(RogueRelicsWork));
    sWork->state = 0;
    sWork->page = 0;
    sWork->abandon = 0;
    sWork->leave = 0;
    SetBgMode0();
    SetupBg(3, 0, 0x1D, 0);
    SetBgPriority(3, 3);
    LoadBgTiles(3, gUnk_097FFB98, 0x2060);
    LoadBgPalette(3, gUnk_0984B118, 0xA0);
    LoadBgMap(3, gUnk_09848198, 0x500);
    sWork->palette = _08066468(1);
    sWork->titlePalette = _08066468(0);

    for (i = 0; i < PAGE_LINES; i++) {
        InitTextSlots(sWork->lines[i], LINE_SLOTS);
    }

    RogueCountBuild();
    RogueRelicsShowPage();
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
        if (GetKeysPressed() & A_BUTTON) {
            m4aSongNumStart(SONG_SYS_CLICK);
            sWork->page = (sWork->page + 1) % 3;
            sWork->abandon = 0;
            RogueRelicsShowPage();
        } else if ((GetKeysPressed() & SELECT_BUTTON) && sWork->page == 2) {
            // Giving the run up takes two presses on the records page.
            if (sWork->abandon) {
                sWork->leave = 1;
                FadeStartOut(0, 16);
                sWork->state = 2;
            } else {
                sWork->abandon = 1;
                RogueRelicsShowPage();
            }

            m4aSongNumStart(SONG_SYS_KETTEI);
        } else if (GetKeysPressed() & B_BUTTON) {
            m4aSongNumStart(SONG_SYS_CANSEL);
            FadeStartOut(0, 16);
            sWork->state = 2;
        }
        break;
    case 2:
        if (!FadeIsActive()) {
            if (sWork->leave) {
                RogueAbandonRun();
            } else {
                func_080E04EC();
            }

            sWork->state = 3;
        }
        break;
    }

    for (i = 0; i < sWork->lineCount; i++) {
        DrawTextSlots((240 - GetTextSlotsWidth(sWork->lines[i], sWork->counts[i])) / 2, i == 0 ? 8 : 14 + i * 15,
                      sWork->lines[i], i == 0 ? sWork->titlePalette : sWork->palette, 50, sWork->counts[i]);
    }
}

static void RogueRelics_Exit(void) {
    s32 i;

    for (i = 0; i < PAGE_LINES; i++) {
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
