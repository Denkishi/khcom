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
#include "mode_battle_data.h"
#include "obj_api.h"
#include "sprites_status.h"
#include "system_state.h"
#include "text.h"

// Room cards. A door opens with a room card: any card opens any door, and
// the room behind is the card's. Without one there is always the plain
// battle, which costs nothing. There is a card for each kind of room, one for each character
// met in an event room, who is then sure to be there, and one for each boss
// and miniboss, fought there and then for a boss's reward. Cards drop from
// battles, are sold at every door for the run's shards, and in the hub,
// before the run starts, for the shards kept between runs: those go into the
// run with Sora.

enum {
    CARD_KIND, // arg: the kind of room
    CARD_EVENT, // arg: who is there
    CARD_BOSS // arg: the battle; skin: who is drawn in it
};

typedef struct RogueMapCard {
    u8 type;
    u8 arg;
    u8 skin;
    const u8* name;
} RogueMapCard;

#define KIND(name, kind, text) static const u8 name[] = text;
#define COST_KIND 12
#define COST_EVENT 20
#define COST_BOSS 35

static const u8 sK0[] = "Battaglia";
static const u8 sK1[] = "Elite";
static const u8 sK2[] = "Tesoro";
static const u8 sK3[] = "Moguri";
static const u8 sK4[] = "Riposo";
static const u8 sK5[] = "Sfida";
static const u8 sE0[] = "Belle";
static const u8 sE1[] = "Leon";
static const u8 sE2[] = "Yuffie";
static const u8 sE3[] = "Moguri errante";
static const u8 sE4[] = "Jack";
static const u8 sE5[] = "Ercole";
static const u8 sE6[] = "Tigro";
static const u8 sE7[] = "Riku";
static const u8 sE8[] = "Lexaeus";
static const u8 sE9[] = "Replica";
static const u8 sE10[] = "Jafar";
static const u8 sE11[] = "Oogie";
static const u8 sE12[] = "Ansem";
static const u8 sE13[] = "Sally";
static const u8 sE14[] = "Grillo";
static const u8 sE15[] = "Wendy";
static const u8 sE16[] = "Bestia";
static const u8 sE17[] = "Tidus";
static const u8 sE18[] = "Selphie";
static const u8 sB0[] = "Guard Armor";
static const u8 sB1[] = "Jafar, boss";
static const u8 sB2[] = "Trickmaster";
static const u8 sB3[] = "Ade";
static const u8 sB4[] = "Parassita";
static const u8 sB5[] = "Oogie, boss";
static const u8 sB6[] = "Ursula";
static const u8 sB7[] = "Uncino";
static const u8 sB8[] = "Malefica";
static const u8 sB9[] = "Darkside";
static const u8 sB10[] = "Marluxia";
static const u8 sB11[] = "Leon, boss";
static const u8 sB12[] = "Riku, boss";
static const u8 sB13[] = "Larxene";
static const u8 sB14[] = "Cloud";
static const u8 sB15[] = "Vexen";
static const u8 sB16[] = "Lexaeus boss";
static const u8 sB17[] = "Axel";
static const u8 sB18[] = "Topolino";
static const u8 sB19[] = "Bestia, boss";
static const u8 sB20[] = "Jack, boss";
static const u8 sB21[] = "Peter Pan";
static const u8 sB22[] = "Pippo";
static const u8 sB23[] = "Paperino";
static const u8 sB24[] = "Aladdin";
static const u8 sB25[] = "Sephiroth";
static const u8 sB26[] = "Sora II";
static const u8 sB27[] = "Roxas";
static const u8 sB28[] = "Roxas II";
static const u8 sB29[] = "Roxas III";

static const RogueMapCard sCards[ROGUE_MAP_CARD_KINDS] = {
    { CARD_KIND, ROGUE_ROOM_BATTLE, 0, sK0 },
    { CARD_KIND, ROGUE_ROOM_ELITE, 0, sK1 },
    { CARD_KIND, ROGUE_ROOM_TREASURE, 0, sK2 },
    { CARD_KIND, ROGUE_ROOM_SHOP, 0, sK3 },
    { CARD_KIND, ROGUE_ROOM_REST, 0, sK4 },
    { CARD_KIND, ROGUE_ROOM_CHALLENGE, 0, sK5 },
    { CARD_EVENT, ROGUE_EVENT_BELLE, 0, sE0 },
    { CARD_EVENT, ROGUE_EVENT_LEON, 0, sE1 },
    { CARD_EVENT, ROGUE_EVENT_YUFFIE, 0, sE2 },
    { CARD_EVENT, ROGUE_EVENT_MOOGLE, 0, sE3 },
    { CARD_EVENT, ROGUE_EVENT_JACK, 0, sE4 },
    { CARD_EVENT, ROGUE_EVENT_HERCULES, 0, sE5 },
    { CARD_EVENT, ROGUE_EVENT_TIGGER, 0, sE6 },
    { CARD_EVENT, ROGUE_EVENT_RIKU, 0, sE7 },
    { CARD_EVENT, ROGUE_EVENT_LEXAEUS, 0, sE8 },
    { CARD_EVENT, ROGUE_EVENT_REPLICA, 0, sE9 },
    { CARD_EVENT, ROGUE_EVENT_JAFAR, 0, sE10 },
    { CARD_EVENT, ROGUE_EVENT_OOGIE, 0, sE11 },
    { CARD_EVENT, ROGUE_EVENT_ANSEM, 0, sE12 },
    { CARD_EVENT, ROGUE_EVENT_SALLY, 0, sE13 },
    { CARD_EVENT, ROGUE_EVENT_JIMINY, 0, sE14 },
    { CARD_EVENT, ROGUE_EVENT_WENDY, 0, sE15 },
    { CARD_EVENT, ROGUE_EVENT_BEAST, 0, sE16 },
    { CARD_EVENT, ROGUE_EVENT_TIDUS, 0, sE17 },
    { CARD_EVENT, ROGUE_EVENT_SELPHIE, 0, sE18 },
    // The game's own bosses and minibosses.
    { CARD_BOSS, 0x94, ROGUE_SKIN_NONE, sB0 },
    { CARD_BOSS, 0x95, ROGUE_SKIN_NONE, sB1 },
    { CARD_BOSS, 0x96, ROGUE_SKIN_NONE, sB2 },
    { CARD_BOSS, 0xA0, ROGUE_SKIN_NONE, sB3 },
    { CARD_BOSS, 0x98, ROGUE_SKIN_NONE, sB4 },
    { CARD_BOSS, 0x9B, ROGUE_SKIN_NONE, sB5 },
    { CARD_BOSS, 0x97, ROGUE_SKIN_NONE, sB6 },
    { CARD_BOSS, 0x9E, ROGUE_SKIN_NONE, sB7 },
    { CARD_BOSS, 0x99, ROGUE_SKIN_NONE, sB8 },
    { CARD_BOSS, 0x9A, ROGUE_SKIN_NONE, sB9 },
    { CARD_BOSS, 0xA5, ROGUE_SKIN_NONE, sB10 },
    { CARD_BOSS, 0x9D, ROGUE_SKIN_NONE, sB11 },
    { CARD_BOSS, 0xA1, ROGUE_SKIN_NONE, sB12 },
    { CARD_BOSS, 0xA3, ROGUE_SKIN_NONE, sB13 },
    { CARD_BOSS, 0x9F, ROGUE_SKIN_NONE, sB14 },
    { CARD_BOSS, 0xA4, ROGUE_SKIN_NONE, sB15 },
    { CARD_BOSS, 0xA7, ROGUE_SKIN_NONE, sB16 },
    { CARD_BOSS, 0xA2, ROGUE_SKIN_NONE, sB17 },
    // Those who fight in Leon's place, and those drawn from their own sheets.
    { CARD_BOSS, 0x9D, ROGUE_SKIN_MICKEY, sB18 },
    { CARD_BOSS, 0x9D, ROGUE_SKIN_BEAST, sB19 },
    { CARD_BOSS, 0x9D, ROGUE_SKIN_JACK, sB20 },
    { CARD_BOSS, 0x9D, ROGUE_SKIN_PETER_PAN, sB21 },
    { CARD_BOSS, 0x9D, ROGUE_SKIN_GOOFY, sB22 },
    { CARD_BOSS, 0x9D, ROGUE_SKIN_DONALD, sB23 },
    { CARD_BOSS, 0x9D, ROGUE_SKIN_ALADDIN, sB24 },
    { CARD_BOSS, 0x9D, ROGUE_SKIN_SEPHIROTH, sB25 },
    { CARD_BOSS, 0x9D, ROGUE_SKIN_SORA_KH2, sB26 },
    { CARD_BOSS, 0x9D, ROGUE_SKIN_ROXAS, sB27 },
    { CARD_BOSS, 0x9D, ROGUE_SKIN_ROXAS_COAT, sB28 },
    { CARD_BOSS, 0x9D, ROGUE_SKIN_ROXAS_HOOD, sB29 },
};

#define FIRST_EVENT_CARD 6
#define FIRST_BOSS_CARD 25

const u8* RogueMapCardName(u8 card) {
    return sCards[card].name;
}

u8 RogueMapCardCost(u8 card) {
    static const u8 costs[3] = { COST_KIND, COST_EVENT, COST_BOSS };

    return costs[sCards[card].type];
}

// The cards kept between runs live in the bytes the saved progress had to
// spare, so that an older save reads as having none.
static u8* RogueMapKept(u8 slot) {
    if (slot < 2) {
        return &gRogueMeta.unused2[slot];
    }

    if (slot < 4) {
        return &gRogueMeta.unused3[slot - 2];
    }

    return &gRogueMeta.unused4[slot - 4];
}

// A slot of the cards held: the run's, or in the hub those kept for the next run. Holds the card plus one, 0 when empty.
static u8* RogueMapSlot(u8 hub, u8 slot) {
    return hub ? RogueMapKept(slot) : &gRogue.mapCards[slot];
}

static u8 RogueMapGive(u8 hub, u8 card) {
    u8 slot;

    for (slot = 0; slot < ROGUE_MAP_CARDS; slot++) {
        if (*RogueMapSlot(hub, slot) == 0) {
            *RogueMapSlot(hub, slot) = card + 1;
            return 1;
        }
    }

    return 0;
}

u8 RogueMapCardCount(void) {
    u8 slot;
    u8 count = 0;

    for (slot = 0; slot < ROGUE_MAP_CARDS; slot++) {
        count += gRogue.mapCards[slot] != 0;
    }

    return count;
}

// Whether the menu has anything to offer: a card held, or shards enough for the cheapest.
u8 RogueMapMenuWanted(u8 hub) {
    u8 slot;

    for (slot = 0; slot < ROGUE_MAP_CARDS; slot++) {
        if (*RogueMapSlot(hub, slot) != 0) {
            return 1;
        }
    }

    // A door always asks which room; the hub only when there is something to buy or to see.
    return !hub || gRogueMeta.shards >= COST_KIND;
}

// One of the cards, by what it is: a kind of room half the time, a
// character a third, a boss the rest.
static u8 RogueMapRoll(u32 roll) {
    u32 pick = roll % 100;

    roll /= 100;

    if (pick < 50) {
        return roll % FIRST_EVENT_CARD;
    }

    if (pick < 84) {
        return FIRST_EVENT_CARD + roll % (FIRST_BOSS_CARD - FIRST_EVENT_CARD);
    }

    return FIRST_BOSS_CARD + roll % (ROGUE_MAP_CARD_KINDS - FIRST_BOSS_CARD);
}

// Called when a run starts: the cards bought in the hub go with Sora.
void RogueMapStartRun(void) {
    u8 slot;

    for (slot = 0; slot < ROGUE_MAP_CARDS; slot++) {
        gRogue.mapCards[slot] = *RogueMapKept(slot);
        *RogueMapKept(slot) = 0;
    }

    gRogue.cardEvent = 0;

    // And two to begin with, of the kinds of room.
    RogueMapGive(0, RogueRandBelow(FIRST_EVENT_CARD));
    RogueMapGive(0, RogueRandBelow(FIRST_EVENT_CARD));
}

// Called after a battle won: a card may drop, more often from the harder rooms.
void RogueMapDrop(void) {
    // One from every battle, and a second from the harder rooms.
    u32 count = gRogue.kind == ROGUE_ROOM_BATTLE ? 1 : 2;

    while (count-- != 0) {
        if (RogueMapGive(0, RogueMapRoll(RogueRand()))) {
            gRogueDebug.mapDrops++;
        }
    }
}

// Spends the card in a slot of the run's on the door: the room behind is the
// card's. Returns the battle to fight at once for a boss's card, 0 otherwise.
static u16 RogueMapUse(u8 slot, u8 door) {
    const RogueMapCard* card = &sCards[gRogue.mapCards[slot] - 1];

    gRogue.mapCards[slot] = 0;
    gRogueDebug.mapUsed++;

    switch (card->type) {
    case CARD_KIND:
        gRogue.doors[door] = card->arg;
        break;
    case CARD_EVENT:
        gRogue.doors[door] = ROGUE_ROOM_EVENT;
        gRogue.cardEvent = card->arg + 1;
        break;
    case CARD_BOSS:
        gRogue.duel = 1;
        gRogue.bossSkin = card->skin;
        return card->arg;
    }

    return 0;
}

// The door whose card has been chosen, plus one: back in the room it opens by itself.
static u8 sChosen;

u8 RogueDoorChosen(u8 door) {
    return sChosen == door + 1;
}

void RogueDoorClear(void) {
    sChosen = 0;
}

// Every door asks for a card but the one of the floor's boss.
u8 RogueDoorAsks(u8 door) {
    return gRogue.doors[door] != ROGUE_ROOM_BOSS;
}

// The menu: at a door, or in the hub before the run.

#define LINE_SLOTS 26
#define LINES 4 // shown at once, under the title
#define OFFERS 3
#define ROWS (1 + ROGUE_MAP_CARDS + OFFERS)

typedef struct RogueDoorWork {
    TextSlot title[LINE_SLOTS];
    TextSlot about[LINE_SLOTS + 8];
    u8 aboutCount;
    TextSlot lines[LINES][LINE_SLOTS];
    u8 titleCount;
    u8 counts[LINES];
    u8 text[48];
    void* palette;
    void* titlePalette;
    RogueUi ui;
    u16 map[0x500 / 2];
    u8 rows[ROWS]; // what each row is: 0 to go on, 1 + slot for a card held, 16 + offer for one on sale
    u8 rowCount;
    u8 offers[OFFERS]; // the cards on sale, plus one; 0 once bought
    u8 cursor;
    u8 top; // the first row shown
    u8 state;
    u8 hub;
    u8 door;
    u16 battle; // the boss to fight on leaving
} RogueDoorWork;

static RogueDoorWork* sWork;

static const u8 sTitleDoor[] = "Apri la porta con:";
static const u8 sTitleHub[] = "Carte per la run";
static const u8 sGo[] = "Battaglia";
static const u8 sGoHub[] = "Parti";
static const u8 sBuy[] = "Compra ";
// What the row under the glove means, on the line below the plates.
static const u8 sAboutGo[] = "Gratis: nemici normali";
static const u8 sAboutGoHub[] = "Comincia la run";
static const u8 sAboutCost[] = "Costa ";
static const u8 sAboutHave[] = " frammenti, ne hai ";
static const u8 sAboutKeep[] = "La porti nella run";
static const u8 sAbout0[] = "Nemici normali";
static const u8 sAbout1[] = "Nemici forti, pi\xF9 premi";
static const u8 sAbout2[] = "Battaglia e premio ricco";
static const u8 sAbout3[] = "Il negozio dei Moguri";
static const u8 sAbout4[] = "Recuperi PV";
static const u8 sAbout5[] = "Dura: premio da boss";
static const u8 sAboutEvent[] = "Lo incontri di sicuro";
static const u8 sAboutBoss[] = "Lo sfidi subito";
static const u8* const sAboutKinds[6] = { sAbout0, sAbout1, sAbout2, sAbout3, sAbout4, sAbout5 };

static u8* RogueDoorAppend(u8* out, const u8* text) {
    while (*text != 0) {
        *out++ = *text++;
    }

    *out = 0;
    return out;
}

static u8* RogueDoorNumber(u8* out, u16 value) {
    u8 digits[5];
    s32 count = 0;

    do {
        digits[count++] = '0' + value % 10;
        value /= 10;
    } while (value != 0);

    while (count > 0) {
        *out++ = digits[--count];
    }

    *out = 0;
    return out;
}

static u16 RogueDoorShards(void) {
    return sWork->hub ? gRogueMeta.shards : gRogue.shards;
}

static void RogueDoorRefresh(void) {
    u8* out;
    u8 slot;
    u8 i;

    // The rows: going on, the cards held, the cards on sale.
    sWork->rowCount = 0;
    sWork->rows[sWork->rowCount++] = 0;

    for (slot = 0; slot < ROGUE_MAP_CARDS; slot++) {
        if (*RogueMapSlot(sWork->hub, slot) != 0) {
            sWork->rows[sWork->rowCount++] = 1 + slot;
        }
    }

    for (i = 0; i < OFFERS; i++) {
        if (sWork->offers[i] != 0) {
            sWork->rows[sWork->rowCount++] = 16 + i;
        }
    }

    if (sWork->cursor >= sWork->rowCount) {
        sWork->cursor = sWork->rowCount - 1;
    }

    if (sWork->cursor < sWork->top) {
        sWork->top = sWork->cursor;
    } else if (sWork->cursor >= sWork->top + LINES) {
        sWork->top = sWork->cursor - LINES + 1;
    }

    FreeTextSlots(sWork->title, LINE_SLOTS);
    sWork->titleCount = LoadTextSlots((u16*)(sWork->hub ? sTitleHub : sTitleDoor), sWork->title);

    // What the row under the glove means.
    {
        u8 row = sWork->rows[sWork->cursor];
        const RogueMapCard* card = 0;

        FreeTextSlots(sWork->about, LINE_SLOTS + 8);

        if (row == 0) {
            RogueDoorAppend(sWork->text, sWork->hub ? sAboutGoHub : sAboutGo);
        } else if (row >= 16) {
            out = RogueDoorAppend(sWork->text, sAboutCost);
            out = RogueDoorNumber(out, RogueMapCardCost(sWork->offers[row - 16] - 1));
            out = RogueDoorAppend(out, sAboutHave);
            RogueDoorNumber(out, RogueDoorShards());
        } else if (sWork->hub) {
            RogueDoorAppend(sWork->text, sAboutKeep);
        } else {
            card = &sCards[*RogueMapSlot(0, row - 1) - 1];
            RogueDoorAppend(sWork->text, card->type == CARD_KIND ? sAboutKinds[card - sCards] : card->type == CARD_EVENT ? sAboutEvent : sAboutBoss);
        }

        sWork->aboutCount = LoadTextSlots((u16*)sWork->text, sWork->about);
    }

    for (i = 0; i < LINES; i++) {
        u8 row;

        FreeTextSlots(sWork->lines[i], LINE_SLOTS);
        sWork->counts[i] = 0;

        if (sWork->top + i >= sWork->rowCount) {
            continue;
        }

        row = sWork->rows[sWork->top + i];

        if (row == 0) {
            RogueDoorAppend(sWork->text, sWork->hub ? sGoHub : sGo);
        } else if (row < 16) {
            RogueDoorAppend(sWork->text, sCards[*RogueMapSlot(sWork->hub, row - 1) - 1].name);
        } else {
            out = RogueDoorAppend(sWork->text, sBuy);
            RogueDoorAppend(out, sCards[sWork->offers[row - 16] - 1].name);
        }

        sWork->counts[i] = LoadTextSlots((u16*)sWork->text, sWork->lines[i]);
    }
}

static void RogueDoor_Init(s32 arg) {
    s32 i;
    u32 roll;

    sWork = EwramAlloc(sizeof(RogueDoorWork));
    sWork->state = 0;
    sWork->hub = arg == ROGUE_DOOR_HUB;
    sWork->door = arg;
    sWork->cursor = 0;
    sWork->top = 0;
    sWork->battle = 0;
    SetBgMode0();
    SetupBg(3, 0, 0x1D, 0);
    SetBgPriority(3, 3);
    LoadBgTiles(3, gUnk_097FFB98, 0x2060);
    LoadBgPalette(3, gUnk_0984B118, 0xA0);
    LoadBgMap(3, gUnk_09848198, 0x500);
    SetupBg(2, 0, 0x1E, 0);
    SetBgPriority(2, 2);
    RogueUiFrameMap(sWork->map);
    LoadBgMap(2, sWork->map, 0x500);
    RogueUiInit(&sWork->ui);
    sWork->palette = _08066468(1);
    sWork->titlePalette = _08066468(0);
    InitTextSlots(sWork->title, LINE_SLOTS);
    InitTextSlots(sWork->about, LINE_SLOTS + 8);

    for (i = 0; i < LINES; i++) {
        InitTextSlots(sWork->lines[i], LINE_SLOTS);
    }

    // Three cards on sale, not two alike. In the hub they change with the moment.
    for (i = 0; i < OFFERS; i++) {
        u32 again = 0;

        do {
            roll = sWork->hub ? (gFrameCounter + i * 7919 + again++ * 104729) * 0x9E3779B1u >> 8 : RogueRand();
            sWork->offers[i] = RogueMapRoll(roll + i) + 1;
        } while ((i > 0 && sWork->offers[i] == sWork->offers[0]) || (i > 1 && sWork->offers[i] == sWork->offers[1]));
    }

    RogueDoorRefresh();
    FadeStartIn(0, 16);
}

// The row under the glove is taken: 1 when the menu is to close.
static u8 RogueDoorPick(void) {
    u8 row = sWork->rows[sWork->cursor];
    u8 card;

    if (row == 0) {
        // The plain battle, which needs no card.
        if (!sWork->hub) {
            gRogue.doors[sWork->door] = ROGUE_ROOM_BATTLE;
        }

        return 1;
    }

    if (row < 16) {
        // A card held: at a door it is spent on it. In the hub they wait for the run.
        if (sWork->hub) {
            return 0;
        }

        sWork->battle = RogueMapUse(row - 1, sWork->door);
        return 1;
    }

    card = sWork->offers[row - 16] - 1;

    if (RogueDoorShards() < RogueMapCardCost(card) || !RogueMapGive(sWork->hub, card)) {
        m4aSongNumStart(SONG_SYS_CANSEL);
        return 0;
    }

    if (sWork->hub) {
        gRogueMeta.shards -= RogueMapCardCost(card);
        RogueMetaSave();
    } else {
        gRogue.shards -= RogueMapCardCost(card);
    }

    sWork->offers[row - 16] = 0;
    gRogueDebug.mapBought++;
    m4aSongNumStart(SONG_SYS_KETTEI);
    RogueDoorRefresh();
    return 0;
}

static void RogueDoor_Update(void) {
    s32 i;

    switch (sWork->state) {
    case 0:
        if (!FadeIsActive()) {
            sWork->state = 1;
        }
        break;
    case 1:
        if (GetKeysPressed() & DPAD_DOWN) {
            sWork->cursor = (sWork->cursor + 1) % sWork->rowCount;
            m4aSongNumStart(SONG_SYS_CLICK);
            RogueDoorRefresh();
        } else if (GetKeysPressed() & DPAD_UP) {
            sWork->cursor = (sWork->cursor + sWork->rowCount - 1) % sWork->rowCount;
            m4aSongNumStart(SONG_SYS_CLICK);
            RogueDoorRefresh();
        } else if (GetKeysPressed() & (A_BUTTON | B_BUTTON | START_BUTTON)) {
            // B and Start go on without a card.
            if (!(GetKeysPressed() & A_BUTTON)) {
                sWork->cursor = 0;
            }

            if (RogueDoorPick()) {
                m4aSongNumStart(SONG_SYS_KETTEI);
                FadeStartOut(0, 16);
                sWork->state = 2;
            }
        }
        break;
    case 2:
        if (!FadeIsActive()) {
            if (sWork->hub) {
                RogueStartRun();
            } else if (sWork->battle != 0) {
                ModeRequest(&gModeBattle, sWork->battle);
            } else {
                // Back to the room, where the door now opens.
                sChosen = sWork->door + 1;
                func_080E04EC();
            }

            sWork->state = 3;
        }
        break;
    }

    DrawTextSlots(172 - GetTextSlotsWidth(sWork->title, sWork->titleCount) / 2, 34, sWork->title, sWork->titlePalette, 50, sWork->titleCount);
    DrawTextSlots(120 - GetTextSlotsWidth(sWork->about, sWork->aboutCount) / 2, 144, sWork->about, sWork->palette, 50, sWork->aboutCount);

    for (i = 0; i < LINES; i++) {
        if (sWork->counts[i] != 0) {
            s16 x = RogueUiPlate(&sWork->ui, 44, 62 + i * 20, sWork->top + i == sWork->cursor);

            DrawTextSlots(x, 64 + i * 20, sWork->lines[i], sWork->palette, 50, sWork->counts[i]);

            if (sWork->top + i == sWork->cursor) {
                RogueUiGlove(&sWork->ui, 48, 70 + i * 20);
            }
        }
    }
}

static void RogueDoor_Exit(void) {
    s32 i;

    FreeTextSlots(sWork->title, LINE_SLOTS);
    FreeTextSlots(sWork->about, LINE_SLOTS + 8);

    for (i = 0; i < LINES; i++) {
        FreeTextSlots(sWork->lines[i], LINE_SLOTS);
    }

    RogueUiExit(&sWork->ui);
    ReleaseObjPalette(sWork->palette);
    ReleaseObjPalette(sWork->titlePalette);
    EwramFree(sWork);
}

Mode gModeRogueDoor = {
    "mode_rogue_door",
    RogueDoor_Init,
    RogueDoor_Update,
    RogueDoor_Exit,
};
