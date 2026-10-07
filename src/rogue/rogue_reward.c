#include "rogue.h"
#include "registration_data.h"
#include "mode_battle_data.h"
#include "card.h"
#include "card_deck.h"
#include "card_def_data.h"
#include "card_ids.h"
#include "card_types.h"
#include "display.h"
#include "fade.h"
#include "gba/keys.h"
#include "key.h"
#include "m4a_song.h"
#include "malloc.h"
#include "map_api.h"
#include "mode_sio.h"
#include "mode_test_api.h"
#include "monsgage.h"
#include "obj_api.h"
#include "sprites_status.h"
#include "system_state.h"
#include "text.h"

// The "pick one of three" screen shown after a won battle. It borrows the
// status screen's backdrop and list panel; the picked line's card and a short
// description show on the right.

#define REWARD_CHOICES 3
#define REWARD_TEXT_MAX 72
#define TITLE_SLOTS 32
#define LABEL_SLOTS 12
#define DETAIL_SLOTS 80
#define PANEL_COLUMNS 13

enum {
    REWARD_CARD,
    REWARD_UPGRADE,
    REWARD_HEAL,
    REWARD_MAX_HP,
    REWARD_CP,
    REWARD_COMBO,
    REWARD_AIR_JUMP,
    REWARD_ATTACK,
    REWARD_RELIC,
    REWARD_ART,
    REWARD_FUSION,
    // Offered by events only.
    REWARD_SHARDS,
    REWARD_REROLL,
    REWARD_ATTACK_FOR_HP,
    REWARD_GAMBLE,
    REWARD_DUEL,
    REWARD_LEAVE,
    REWARD_ATTACK2_FOR_HP,
    REWARD_SHARDS_FOR_CARD,
    REWARD_BIG_GAMBLE,
    REWARD_DUPLICATE,
    REWARD_TRANSFORM,
    REWARD_PAY_HP,
    REWARD_RELIC_FOR_HP,
    REWARD_KINDS
};

typedef struct RogueReward {
    u8 kind;
    u8 fuseA; // deck positions of the two cards a fusion consumes
    u8 fuseB;
    u16 card; // card id, collection slot, deck position, shards or battle id, by kind
    u16 result; // what a transformed card becomes
} RogueReward;

typedef struct RogueRewardWork {
    RogueReward rewards[REWARD_CHOICES];
    TextSlot title[TITLE_SLOTS];
    TextSlot labels[REWARD_CHOICES][LABEL_SLOTS];
    TextSlot detail[DETAIL_SLOTS];
    u16 map[0x500 / 2];
    u8 text[REWARD_TEXT_MAX + 8];
    void* palette;
    void* cursorPalette;
    void* cardTiles;
    void* cardPalette;
    void* cardGfx;
    u8 titleCount;
    u8 labelCounts[REWARD_CHOICES];
    u8 detailCount;
    u8 cursor;
    u8 state;
    u8 source; // ROGUE_REWARD_BATTLE, _BOSS, _EVENT or _DUEL
    u8 afterBoss;
    u8 rich; // boss and duel rewards: relics and combo hits come up more
    u8 duel; // battle to start when the screen closes, 0 for none
} RogueRewardWork;

static RogueRewardWork* sWork;

static const u8 sTitle[] = "Scegli una ricompensa";
static const u8 sTitleReroll[] = "Scegli (B: rilancia)";
static const u8 sLabelCard[] = "Carta";
static const u8 sLabelUpgrade[] = "Potenzia";
static const u8 sLabelHeal[] = "Cura";
static const u8 sLabelMaxHp[] = "PV max";
static const u8 sLabelCp[] = "PC";
static const u8 sLabelCombo[] = "Combo+";
static const u8 sLabelAirJump[] = "Reliquia";
static const u8 sLabelAttack[] = "Forza";
static const u8 sLabelRelic[] = "Reliquia";
static const u8 sLabelArt[] = "Tecnica";
static const u8 sLabelFusion[] = "Fusione";
static const u8 sLabelShards[] = "Frammenti";
static const u8 sLabelReroll[] = "Rilancio";
static const u8 sLabelPact[] = "Patto";
static const u8 sLabelGamble[] = "Azzardo";
static const u8 sLabelDuel[] = "Duello";
static const u8 sLabelLeave[] = "Rifiuta";
static const u8 sLabelDarkPact[] = "Patto nero";
static const u8 sLabelBarter[] = "Baratto";
static const u8 sLabelDice[] = "Dadi";
static const u8 sLabelCopy[] = "Copia";
static const u8 sLabelMutate[] = "Muta";
static const u8 sLabelFlee[] = "Fuggi";
static const u8 sLabelDarkness[] = "Oscurit\xE0";
static const u8* const sLabels[REWARD_KINDS] = {
    sLabelCard, sLabelUpgrade, sLabelHeal, sLabelMaxHp, sLabelCp, sLabelCombo, sLabelAirJump, sLabelAttack, sLabelRelic, sLabelArt, sLabelFusion, sLabelShards, sLabelReroll, sLabelPact, sLabelGamble,
    sLabelDuel, sLabelLeave, sLabelDarkPact, sLabelBarter, sLabelDice, sLabelCopy, sLabelMutate, sLabelFlee, sLabelDarkness,
};

static const u8 sCost[] = "\x1FPC ";
static const u8 sOtherPair[] = "\x1F< > altra coppia";
static const u8 sLevel[] = "\x1FLivello ";
static const u8 sHeal[] = "Recuperi tutti\x1Fi PV";
static const u8 sMaxHp[] = "PV massimi +20";
static const u8 sCp[] = "PC del mazzo +30";
static const u8 sAttack[] = "Forza +1: tutti i\x1F" "colpi fanno pi\xF9\x1F" "danno";
static const u8 sShards[] = " Frammenti";
static const u8 sReroll[] = "Un rilancio delle\x1Fricompense";
static const u8 sPact[] = "Forza +1, ma\x1FPV massimi -15";
static const u8 sGamble[] = "Una volta su due\x1F" "Forza +1, altrimenti\x1Fperdi 20 PV";
static const u8 sDuel[] = "Combatti. Se vinci:\x1Fricompensa da boss\x1F" "e 15 Frammenti";
static const u8 sLeave[] = "Te ne vai senza\x1Fprendere nulla";
static const u8 sDarkPact[] = "Forza +2, ma\x1FPV massimi -30";
static const u8 sBarter[] = "+30 Frammenti, ma\x1Fperdi una carta\x1F" "a caso";
static const u8 sDice[] = "Una volta su due una\x1Freliquia, altrimenti\x1Fperdi met\xE0 dei PV";
static const u8 sCopy[] = "Una copia di:\x1F";
static const u8 sMutate[] = "\x1F" "diventa\x1F";
static const u8 sFlee[] = "Scappi, ma perdi\x1F" "20 PV";
static const u8 sDarkness[] = "Una reliquia, ma\x1FPV massimi -25";
static const u8 sArt[] = " dal 5 in su\x1Flancia una tecnica\x1F" "da sola";
static const u8 sCombo[] = "Un colpo in pi\xF9\x1Fnella combo";
static const u8 sAirJump[] = "Salto in aria:\x1Fun salto in pi\xF9\x1F" "a mezz'aria";

static u8* RogueAppend(u8* out, const u8* text) {
    u8* end = sWork->text + REWARD_TEXT_MAX;

    while (*text != 0 && out < end) {
        *out++ = *text++;
    }

    *out = 0;
    return out;
}

static u8* RogueAppendNumber(u8* out, u16 value) {
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

static u8* RogueAppendCard(u8* out, u16 id) {
    out = RogueAppend(out, eu_0805E924(gCardDefs[id].name));

    if (gCardDefs[id].unk_2A != 3) {
        *out++ = ' ';
        out = RogueAppendNumber(out, gCardDefs[id].unk_20);
    }

    return out;
}

// Picks a card of the active deck that can still go up in value. Returns its
// collection slot, or 0xFFFF if the deck has none.
static u16 RogueRollUpgrade(void) {
    Deck* deck = GetActiveDeck();
    u16 slot;
    u16 id;
    s32 tries;

    for (tries = 0; tries < 40; tries++) {
        slot = deck->cards[RogueRandBelow(DECK_SIZE)];

        if (slot == 0xFFFF) {
            continue;
        }

        id = gCardCollection[slot] & CARD_ID_MASK;

        if (gCardDefs[id].unk_2A != 3 && gCardDefs[id].unk_20 >= 1 && gCardDefs[id].unk_20 < RogueMaxCardValue() + 1 &&
            gCardDefs[id].unk_20 <= 8) {
            return slot;
        }
    }

    return 0xFFFF;
}

static u8 RogueRewardAvailable(RogueReward* reward) {
    u8 pos;

    switch (reward->kind) {
    case REWARD_CARD:
        reward->card = RogueRollRewardCard();
        return reward->card != 0;
    case REWARD_UPGRADE:
        reward->card = RogueRollUpgrade();
        return reward->card != 0xFFFF;
    case REWARD_HEAL:
        return gGameState.hp < gGameState.progression.maxHp;
    case REWARD_COMBO:
        return gRogue.comboPlus < ROGUE_COMBO_PLUS_MAX;
    case REWARD_AIR_JUMP:
        // The relic enters the rewards with the second chapter.
        return gRogueMeta.chapters >= 2 && gRogue.airJumps < ROGUE_AIR_JUMPS_MAX;
    case REWARD_ATTACK:
        return gGameState.progression.ap < ROGUE_AP_MAX;
    case REWARD_RELIC:
        reward->card = RogueRollRelic();
        return reward->card != ROGUE_RELICS;
    case REWARD_ART:
        // A kind of card in the deck that has no art yet gets one.
        pos = RogueRollDeckCard();

        if (pos == 0xFF) {
            return 0;
        }

        reward->card = (gCardCollection[GetActiveDeck()->cards[pos]] & CARD_ID_MASK) / 10;

        if (reward->card >= ROGUE_ART_KINDS || gRogue.arts[reward->card] != 0) {
            return 0;
        }

        reward->result = RogueRollArt(reward->card);
        return reward->result != 0;
    }

    return 1;
}

// Turns what the room's event offers into the three rewards. An offer that
// cannot be given right now becomes a few shards.
static void RogueEventRewards(void) {
    static const u8 kinds[] = {
        REWARD_HEAL, REWARD_MAX_HP, REWARD_CP, REWARD_COMBO, REWARD_AIR_JUMP, REWARD_UPGRADE,
        REWARD_CARD, REWARD_CARD, REWARD_SHARDS, REWARD_REROLL, REWARD_ATTACK_FOR_HP, REWARD_GAMBLE,
        REWARD_DUEL, REWARD_LEAVE, REWARD_ATTACK2_FOR_HP, REWARD_SHARDS_FOR_CARD, REWARD_BIG_GAMBLE,
        REWARD_DUPLICATE, REWARD_TRANSFORM, REWARD_PAY_HP, REWARD_RELIC_FOR_HP,
    };
    Deck* deck = GetActiveDeck();
    u8 pos;
    const RogueEventOffer* offers = RogueEventOffers();
    RogueReward* reward;
    u8 available;
    s32 i;

    for (i = 0; i < REWARD_CHOICES; i++) {
        reward = &sWork->rewards[i];
        reward->kind = kinds[offers[i].offer];
        reward->card = offers[i].param;

        switch (offers[i].offer) {
        case ROGUE_OFFER_CARD:
        case ROGUE_OFFER_SHARDS:
        case ROGUE_OFFER_REROLL:
        case ROGUE_OFFER_GAMBLE:
        case ROGUE_OFFER_DUEL:
        case ROGUE_OFFER_LEAVE:
        case ROGUE_OFFER_BIG_GAMBLE:
        case ROGUE_OFFER_PAY_HP:
            available = 1;
            break;
        case ROGUE_OFFER_ATTACK2_FOR_HP:
            available = gGameState.progression.ap + 1 < ROGUE_AP_MAX && gGameState.progression.maxHp > 60;
            break;
        case ROGUE_OFFER_RELIC_FOR_HP:
            reward->card = RogueRollRelic();
            available = reward->card != ROGUE_RELICS && gGameState.progression.maxHp > 50;
            break;
        case ROGUE_OFFER_SHARDS_FOR_CARD:
            available = deck->unk_DC > 6 && RogueRollDeckCard() != 0xFF;
            break;
        case ROGUE_OFFER_DUPLICATE:
        case ROGUE_OFFER_TRANSFORM:
            pos = RogueRollDeckCard();
            available = pos != 0xFF;

            if (available) {
                reward->card = deck->cards[pos];
                reward->result = RogueRollTransform(gCardCollection[reward->card] & CARD_ID_MASK);
                available = offers[i].offer == ROGUE_OFFER_DUPLICATE || reward->result != 0;
            }
            break;
        case ROGUE_OFFER_AIR_JUMP:
            available = gRogue.airJumps < ROGUE_AIR_JUMPS_MAX;
            break;
        case ROGUE_OFFER_ATTACK_FOR_HP:
            available = gGameState.progression.ap < ROGUE_AP_MAX && gGameState.progression.maxHp > 40;
            break;
        default:
            available = RogueRewardAvailable(reward);
            break;
        }

        if (!available) {
            reward->kind = REWARD_SHARDS;
            reward->card = 10;
        }
    }
}

static void RogueRollRewards(void) {
    static const u8 weights[REWARD_FUSION] = { 25, 16, 11, 10, 9, 6, 4, 8, 6, 5 };
    RogueReward* reward;
    u32 roll;
    s32 count = 0;
    s32 i;
    u8 kind;

    if (sWork->source == ROGUE_REWARD_EVENT) {
        RogueEventRewards();
        return;
    }

    // A fusion is always on offer when two cards are ready for one.
    reward = &sWork->rewards[0];

    if (RogueRollFusion(&reward->fuseA, &reward->fuseB, &reward->card)) {
        reward->kind = REWARD_FUSION;
        count = 1;
    }

    while (count < REWARD_CHOICES) {
        roll = RogueRandBelow(100);

        for (kind = 0; kind < REWARD_FUSION - 1; kind++) {
            if (roll < weights[kind]) {
                break;
            }

            roll -= weights[kind];
        }

        // Relics and combo hits are rarer in ordinary rooms than after a boss.
        if (!sWork->rich && (kind == REWARD_COMBO || kind == REWARD_AIR_JUMP || kind == REWARD_RELIC || kind == REWARD_ART) &&
            RogueRandBelow(2) == 0) {
            continue;
        }

        for (i = 0; i < count; i++) {
            if (sWork->rewards[i].kind == kind) {
                break;
            }
        }

        if (i != count) {
            continue;
        }

        reward = &sWork->rewards[count];
        reward->kind = kind;

        if (RogueRewardAvailable(reward)) {
            count++;
        }
    }
}

// The card a reward shows on the right, 0 for none.
static u16 RogueRewardCard(RogueReward* reward) {
    switch (reward->kind) {
    case REWARD_CARD:
    case REWARD_FUSION:
        return reward->card;
    case REWARD_UPGRADE:
    case REWARD_DUPLICATE:
        return gCardCollection[reward->card] & CARD_ID_MASK;
    case REWARD_ART:
        return CARD_ID(reward->card, ROGUE_ART_MIN_VALUE);
    case REWARD_TRANSFORM:
        return reward->result;
    }

    return 0;
}

static void RogueRewardDetail(RogueReward* reward) {
    Deck* deck = GetActiveDeck();
    u8* out = sWork->text;
    u16 id;

    switch (reward->kind) {
    case REWARD_CARD:
        out = RogueAppendCard(out, reward->card);
        out = RogueAppend(out, sCost);
        RogueAppendNumber(out, GetCardCpCost(reward->card));
        break;
    case REWARD_UPGRADE:
        id = gCardCollection[reward->card] & CARD_ID_MASK;
        out = RogueAppendCard(out, id);
        *out++ = ' ';
        *out++ = '>';
        *out++ = ' ';
        out = RogueAppendNumber(out, gCardDefs[id].unk_20 + 1);
        out = RogueAppend(out, sLevel);
        RogueAppendNumber(out, RogueCardLevel(reward->card));
        break;
    case REWARD_FUSION:
        out = RogueAppendCard(out, gCardCollection[deck->cards[reward->fuseA]] & CARD_ID_MASK);
        *out++ = ' ';
        *out++ = '+';
        *out++ = 0x1F;
        out = RogueAppendCard(out, gCardCollection[deck->cards[reward->fuseB]] & CARD_ID_MASK);
        *out++ = 0x1F;
        *out++ = '>';
        *out++ = ' ';
        out = RogueAppendCard(out, reward->card);
        RogueAppend(out, sOtherPair);
        break;
    case REWARD_HEAL:
        RogueAppend(out, sHeal);
        break;
    case REWARD_MAX_HP:
        RogueAppend(out, sMaxHp);
        break;
    case REWARD_CP:
        RogueAppend(out, sCp);
        break;
    case REWARD_COMBO:
        RogueAppend(out, sCombo);
        break;
    case REWARD_AIR_JUMP:
        RogueAppend(out, sAirJump);
        break;
    case REWARD_ATTACK:
        RogueAppend(out, sAttack);
        break;
    case REWARD_RELIC:
        out = RogueAppend(out, RogueRelicName(reward->card));
        *out++ = 0x1F;
        RogueAppend(out, RogueRelicText(reward->card));
        break;
    case REWARD_ART:
        out = RogueAppend(out, eu_0805E924(gCardDefs[CARD_ID(reward->card, 1)].name));
        RogueAppend(out, sArt);
        break;
    case REWARD_SHARDS:
        *out++ = '+';
        out = RogueAppendNumber(out, reward->card);
        RogueAppend(out, sShards);
        break;
    case REWARD_REROLL:
        RogueAppend(out, sReroll);
        break;
    case REWARD_ATTACK_FOR_HP:
        RogueAppend(out, sPact);
        break;
    case REWARD_GAMBLE:
        RogueAppend(out, sGamble);
        break;
    case REWARD_DUEL:
        RogueAppend(out, sDuel);
        break;
    case REWARD_LEAVE:
        RogueAppend(out, sLeave);
        break;
    case REWARD_ATTACK2_FOR_HP:
        RogueAppend(out, sDarkPact);
        break;
    case REWARD_SHARDS_FOR_CARD:
        RogueAppend(out, sBarter);
        break;
    case REWARD_BIG_GAMBLE:
        RogueAppend(out, sDice);
        break;
    case REWARD_DUPLICATE:
        out = RogueAppend(out, sCopy);
        RogueAppendCard(out, gCardCollection[reward->card] & CARD_ID_MASK);
        break;
    case REWARD_TRANSFORM:
        out = RogueAppendCard(out, gCardCollection[reward->card] & CARD_ID_MASK);
        out = RogueAppend(out, sMutate);
        RogueAppendCard(out, reward->result);
        break;
    case REWARD_PAY_HP:
        RogueAppend(out, sFlee);
        break;
    case REWARD_RELIC_FOR_HP:
        out = RogueAppend(out, RogueRelicName(reward->card));
        *out++ = 0x1F;
        RogueAppend(out, sDarkness);
        break;
    }
}

// Costs never kill: they leave at least 1 HP.
static void RogueLoseHp(s32 amount) {
    if (gGameState.hp > amount) {
        gGameState.hp -= amount;
    } else {
        gGameState.hp = 1;
    }
}

static void RogueLoseMaxHp(s32 amount) {
    gGameState.progression.maxHp -= amount;

    if (gGameState.hp > gGameState.progression.maxHp) {
        gGameState.hp = gGameState.progression.maxHp;
    }
}

static void RogueGiveReward(RogueReward* reward) {
    Deck* deck;
    u16 before;
    u16 after;
    u8 slot;

    switch (reward->kind) {
    case REWARD_CARD:
        RogueGiveCard(reward->card);
        break;
    case REWARD_UPGRADE:
        // An upgrade brings the CP it costs with it, so the deck stays legal.
        deck = GetActiveDeck();
        before = GetCardCpCost(gCardCollection[reward->card]);
        gCardCollection[reward->card]++;
        after = GetCardCpCost(gCardCollection[reward->card]);
        deck->unk_DA += after - before;
        gGameState.progression.cp += after - before;
        break;
    case REWARD_FUSION:
        RogueFuse(reward->fuseA, reward->fuseB, reward->card);
        break;
    case REWARD_HEAL:
        gGameState.hp = gGameState.progression.maxHp;
        break;
    case REWARD_MAX_HP:
        gGameState.progression.maxHp += 20;
        gGameState.hp += 20;
        break;
    case REWARD_CP:
        gGameState.progression.cp += 30;
        break;
    case REWARD_COMBO:
        gRogue.comboPlus++;
        break;
    case REWARD_AIR_JUMP:
        gRogue.airJumps++;
        break;
    case REWARD_ATTACK:
        gGameState.progression.ap++;
        break;
    case REWARD_RELIC:
        gRogue.relics |= 1 << reward->card;
        break;
    case REWARD_ART:
        gRogue.arts[reward->card] = reward->result;
        break;
    case REWARD_SHARDS:
        gRogue.shards += reward->card;
        break;
    case REWARD_REROLL:
        gRogue.rerolls++;
        break;
    case REWARD_ATTACK_FOR_HP:
        gGameState.progression.ap++;
        RogueLoseMaxHp(15);
        break;
    case REWARD_GAMBLE:
        if (RogueRandBelow(2) == 0 && gGameState.progression.ap < ROGUE_AP_MAX) {
            gGameState.progression.ap++;
        } else {
            RogueLoseHp(20);
        }
        break;
    case REWARD_DUEL:
        gRogue.duel = 1;
        sWork->duel = reward->card;
        break;
    case REWARD_LEAVE:
        break;
    case REWARD_ATTACK2_FOR_HP:
        gGameState.progression.ap += 2;
        RogueLoseMaxHp(30);
        break;
    case REWARD_SHARDS_FOR_CARD:
        slot = RogueRollDeckCard();

        if (slot != 0xFF) {
            RogueRemoveDeckCard(slot);
        }

        gRogue.shards += 30;
        break;
    case REWARD_BIG_GAMBLE:
        if (RogueRandBelow(2) == 0) {
            slot = RogueRollRelic();

            if (slot != ROGUE_RELICS) {
                gRogue.relics |= 1 << slot;
            } else if (gGameState.progression.ap < ROGUE_AP_MAX) {
                gGameState.progression.ap++;
            }
        } else {
            RogueLoseHp(gGameState.hp / 2);
        }
        break;
    case REWARD_DUPLICATE:
        // The copy brings its CP with it, so it always fits the deck.
        gGameState.progression.cp += GetCardCpCost(gCardCollection[reward->card]);
        RogueGiveCard(gCardCollection[reward->card] & CARD_ID_MASK);
        break;
    case REWARD_TRANSFORM:
        deck = GetActiveDeck();
        before = GetCardCpCost(gCardCollection[reward->card]);
        gCardCollection[reward->card] = (gCardCollection[reward->card] & ~CARD_ID_MASK) | reward->result;
        after = GetCardCpCost(gCardCollection[reward->card]);
        deck->unk_DA += after - before;

        if (after > before) {
            gGameState.progression.cp += after - before;
        }
        break;
    case REWARD_PAY_HP:
        RogueLoseHp(20);
        break;
    case REWARD_RELIC_FOR_HP:
        gRogue.relics |= 1 << reward->card;
        RogueLoseMaxHp(25);
        break;
    }
}

static void RogueFreeCard(void) {
    if (sWork->cardTiles != 0) {
        ReleaseObjTiles(sWork->cardTiles);
        ReleaseObjPalette(sWork->cardPalette);
        sWork->cardTiles = 0;
    }
}

// Loads the description and the card picture of the line under the cursor.
static void RogueShowChoice(void) {
    RogueReward* reward = &sWork->rewards[sWork->cursor];
    u16 id = RogueRewardCard(reward);

    FreeTextSlots(sWork->detail, DETAIL_SLOTS);
    RogueRewardDetail(reward);
    sWork->detailCount = LoadTextSlots((u16*)sWork->text, sWork->detail);
    RogueFreeCard();

    if (id != 0) {
        sWork->cardTiles = LoadObjTiles(gCardDefs[id].tiles, 0x300);
        sWork->cardPalette = LoadObjPalette(gCardDefs[id].palette, 32);
        sWork->cardGfx = gCardDefs[id].gfx;
    }
}

// Rolls three rewards and loads their lines.
static void RogueOfferRewards(void) {
    s32 i;

    RogueCountBuild();
    RogueRollRewards();

    for (i = 0; i < REWARD_CHOICES; i++) {
        FreeTextSlots(sWork->labels[i], LABEL_SLOTS);
        sWork->labelCounts[i] = LoadTextSlots((u16*)sLabels[sWork->rewards[i].kind], sWork->labels[i]);
    }

    FreeTextSlots(sWork->title, TITLE_SLOTS);
    sWork->titleCount =
        LoadTextSlots((u16*)(gRogue.rerolls != 0 && sWork->source != ROGUE_REWARD_EVENT ? sTitleReroll : sTitle), sWork->title);
    RogueShowChoice();
}

static void RogueReward_Init(s32 source) {
    const u16* map = (const u16*)gUnk_09847798;
    s32 i;

    sWork = EwramAlloc(sizeof(RogueRewardWork));
    sWork->source = source;
    sWork->afterBoss = source == ROGUE_REWARD_BOSS;
    sWork->rich = source == ROGUE_REWARD_BOSS || source == ROGUE_REWARD_DUEL;
    sWork->duel = 0;
    sWork->cursor = 0;
    sWork->state = 0;
    sWork->cardTiles = 0;
    SetBgMode0();
    SetupBg(3, 0, 0x1D, 0);
    SetupBg(2, 0, 0x1E, 0);
    SetBgPriority(3, 3);
    SetBgPriority(2, 2);
    LoadBgTiles(3, gUnk_097FFB98, 0x2060);
    LoadBgPalette(3, gUnk_0984B118, 0xA0);
    LoadBgMap(3, gUnk_09848198, 0x500);

    // Only the list panel on the left of the status screen's frame layer is kept.
    for (i = 0; i < 0x500 / 2; i++) {
        sWork->map[i] = (i & 31) < PANEL_COLUMNS ? map[i] : map[0];
    }

    LoadBgMap(2, sWork->map, 0x500);
    sWork->palette = _08066468(1);
    sWork->cursorPalette = _08066468(0);
    InitTextSlots(sWork->title, TITLE_SLOTS);
    InitTextSlots(sWork->detail, DETAIL_SLOTS);

    for (i = 0; i < REWARD_CHOICES; i++) {
        InitTextSlots(sWork->labels[i], LABEL_SLOTS);
    }

    RogueOfferRewards();
    FadeStartIn(0, 16);
}

static void RogueReward_Update(void) {
    s32 i;

    switch (sWork->state) {
    case 0:
        if (!FadeIsActive()) {
            sWork->state = 1;
        }
        break;
    case 1:
        if (GetKeysRepeat() & DPAD_UP) {
            sWork->cursor = (sWork->cursor + REWARD_CHOICES - 1) % REWARD_CHOICES;
            m4aSongNumStart(SONG_SYS_CLICK);
            RogueShowChoice();
        } else if (GetKeysRepeat() & DPAD_DOWN) {
            sWork->cursor = (sWork->cursor + 1) % REWARD_CHOICES;
            m4aSongNumStart(SONG_SYS_CLICK);
            RogueShowChoice();
        } else if ((GetKeysRepeat() & (DPAD_LEFT | DPAD_RIGHT)) && sWork->rewards[sWork->cursor].kind == REWARD_FUSION) {
            // Left and right look for another pair of cards to fuse.
            RogueReward* fusion = &sWork->rewards[sWork->cursor];

            if (RogueRollFusion(&fusion->fuseA, &fusion->fuseB, &fusion->card)) {
                m4aSongNumStart(SONG_SYS_CLICK);
                RogueShowChoice();
            }
        } else if ((GetKeysPressed() & B_BUTTON) && gRogue.rerolls != 0 && sWork->source != ROGUE_REWARD_EVENT) {
            gRogue.rerolls--;
            m4aSongNumStart(SONG_SYS_CLICK);
            RogueOfferRewards();
        } else if (GetKeysPressed() & A_BUTTON) {
            m4aSongNumStart(SONG_SYS_KETTEI);
            RogueGiveReward(&sWork->rewards[sWork->cursor]);
            FadeStartOut(0, 16);
            sWork->state = 2;
        }
        break;
    case 2:
        if (!FadeIsActive()) {
            if (sWork->duel != 0) {
                ModeRequest(&gModeBattle, sWork->duel);
            } else if (sWork->afterBoss) {
                RogueNextFloor();
            } else {
                func_080E04EC();
            }

            sWork->state = 3;
        }
        break;
    }

    DrawTextSlots((240 - GetTextSlotsWidth(sWork->title, sWork->titleCount)) / 2, 8, sWork->title, sWork->palette, 50,
                  sWork->titleCount);

    for (i = 0; i < REWARD_CHOICES; i++) {
        DrawTextSlots(14, 46 + i * 26, sWork->labels[i], i == sWork->cursor ? sWork->cursorPalette : sWork->palette, 50,
                      sWork->labelCounts[i]);
    }

    if (sWork->cardTiles != 0) {
        DrawSprite(172, 70, sWork->cardGfx, sWork->cardTiles, sWork->cardPalette, 0, 0, 50);
    }

    DrawTextSlots(112, 106, sWork->detail, sWork->palette, 50, sWork->detailCount);
}

static void RogueReward_Exit(void) {
    s32 i;

    FreeTextSlots(sWork->title, TITLE_SLOTS);
    FreeTextSlots(sWork->detail, DETAIL_SLOTS);

    for (i = 0; i < REWARD_CHOICES; i++) {
        FreeTextSlots(sWork->labels[i], LABEL_SLOTS);
    }

    RogueFreeCard();
    ReleaseObjPalette(sWork->palette);
    ReleaseObjPalette(sWork->cursorPalette);
    EwramFree(sWork);
}

Mode gModeRogueReward = {
    "mode_rogue_reward",
    RogueReward_Init,
    RogueReward_Update,
    RogueReward_Exit,
};
