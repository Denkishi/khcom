#include "rogue.h"
#include "registration_data.h"
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
#include "system_state.h"
#include "text.h"

// The "pick one of three" screen shown after a won battle.

#define REWARD_CHOICES 3
#define REWARD_TEXT_MAX 28
#define TITLE_SLOTS 32
#define CHOICE_SLOTS 32

enum {
    REWARD_CARD,
    REWARD_UPGRADE,
    REWARD_HEAL,
    REWARD_MAX_HP,
    REWARD_CP,
    REWARD_COMBO,
    REWARD_AIR_JUMP,
    REWARD_KINDS
};

typedef struct RogueReward {
    u8 kind;
    u16 card; // card id, or the collection slot to upgrade
} RogueReward;

typedef struct RogueRewardWork {
    RogueReward rewards[REWARD_CHOICES];
    TextSlot title[TITLE_SLOTS];
    TextSlot choices[REWARD_CHOICES][CHOICE_SLOTS];
    u8 text[REWARD_TEXT_MAX + 4];
    void* palette;
    void* cursorPalette;
    u8 titleCount;
    u8 choiceCounts[REWARD_CHOICES];
    u8 cursor;
    u8 state;
    u8 afterBoss;
} RogueRewardWork;

static RogueRewardWork* sWork;

static const u8 sTitle[] = "Scegli una ricompensa";
static const u8 sCard[] = "Carta: ";
static const u8 sUpgrade[] = "Potenzia: ";
static const u8 sHeal[] = "Cura completa";
static const u8 sMaxHp[] = "PV massimi +20";
static const u8 sCp[] = "PC +30";
static const u8 sCombo[] = "Combo+: un colpo in pi\xF9";
static const u8 sAirJump[] = "Reliquia: salto in aria";

static u8* RogueAppend(u8* out, const u8* text) {
    u8* end = sWork->text + REWARD_TEXT_MAX;

    while (*text != 0 && out < end) {
        *out++ = *text++;
    }

    *out = 0;
    return out;
}

static u8* RogueAppendCard(u8* out, u16 id) {
    out = RogueAppend(out, eu_0805E924(gCardDefs[id].name));

    if (gCardDefs[id].unk_2A != 3) {
        *out++ = ' ';
        *out++ = '0' + gCardDefs[id].unk_20;
        *out = 0;
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

    if (deck->unk_DC == 0) {
        return 0xFFFF;
    }

    for (tries = 0; tries < 30; tries++) {
        slot = deck->cards[RogueRandBelow(deck->unk_DC)];

        if (slot == 0xFFFF) {
            continue;
        }

        id = gCardCollection[slot] & 0x0FFF;

        if (gCardDefs[id].unk_2A != 3 && gCardDefs[id].unk_20 >= 1 && gCardDefs[id].unk_20 <= 8) {
            return slot;
        }
    }

    return 0xFFFF;
}

static u8 RogueRewardAvailable(RogueReward* reward) {
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
        return gRogue.airJumps < ROGUE_AIR_JUMPS_MAX;
    }

    return 1;
}

static void RogueRollRewards(void) {
    static const u8 weights[REWARD_KINDS] = { 30, 20, 14, 12, 12, 7, 5 };
    RogueReward* reward;
    u32 roll;
    s32 count = 0;
    s32 i;
    u8 kind;

    while (count < REWARD_CHOICES) {
        roll = RogueRandBelow(100);

        for (kind = 0; kind < REWARD_KINDS - 1; kind++) {
            if (roll < weights[kind]) {
                break;
            }

            roll -= weights[kind];
        }

        // Relics and combo hits are rarer in ordinary rooms than after a boss.
        if (!sWork->afterBoss && kind >= REWARD_COMBO && RogueRandBelow(2) == 0) {
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

static void RogueRewardText(RogueReward* reward) {
    u8* out = sWork->text;
    u16 id;

    switch (reward->kind) {
    case REWARD_CARD:
        out = RogueAppend(out, sCard);
        RogueAppendCard(out, reward->card);
        break;
    case REWARD_UPGRADE:
        id = gCardCollection[reward->card] & 0x0FFF;
        out = RogueAppend(out, sUpgrade);
        out = RogueAppendCard(out, id);
        *out++ = '>';
        *out++ = '0' + gCardDefs[id].unk_20 + 1;
        *out = 0;
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
    }
}

static void RogueGiveReward(RogueReward* reward) {
    Deck* deck;
    u16 before;
    u16 after;
    s16 slot;

    switch (reward->kind) {
    case REWARD_CARD:
        slot = AddCardToCollection(reward->card);

        // The card joins the deck if it fits, otherwise it waits in the collection.
        if (slot != -1 && GetDeckCpCost(GetActiveDeckIndex()) + GetCardCpCost(reward->card) <= gGameState.progression.cp) {
            AddCardToActiveDeck(slot);
        }
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
    }
}

static void RogueReward_Init(s32 afterBoss) {
    s32 i;

    sWork = EwramAlloc(sizeof(RogueRewardWork));
    sWork->afterBoss = afterBoss;
    sWork->cursor = 0;
    sWork->state = 0;
    SetBgMode0();
    SetBackdropColor(2, 3, 9);
    sWork->palette = _08066468(1);
    sWork->cursorPalette = _08066468(0);
    InitTextSlots(sWork->title, TITLE_SLOTS);
    sWork->titleCount = LoadTextSlots((u16*)sTitle, sWork->title);
    RogueRollRewards();

    for (i = 0; i < REWARD_CHOICES; i++) {
        RogueRewardText(&sWork->rewards[i]);
        InitTextSlots(sWork->choices[i], CHOICE_SLOTS);
        sWork->choiceCounts[i] = LoadTextSlots((u16*)sWork->text, sWork->choices[i]);
    }

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
        } else if (GetKeysRepeat() & DPAD_DOWN) {
            sWork->cursor = (sWork->cursor + 1) % REWARD_CHOICES;
            m4aSongNumStart(SONG_SYS_CLICK);
        } else if (GetKeysPressed() & A_BUTTON) {
            m4aSongNumStart(SONG_SYS_KETTEI);
            RogueGiveReward(&sWork->rewards[sWork->cursor]);
            FadeStartOut(0, 16);
            sWork->state = 2;
        }
        break;
    case 2:
        if (!FadeIsActive()) {
            if (sWork->afterBoss) {
                RogueNextFloor();
            } else {
                func_080E04EC();
            }

            sWork->state = 3;
        }
        break;
    }

    DrawTextSlots((240 - GetTextSlotsWidth(sWork->title, sWork->titleCount)) / 2, 24, sWork->title, sWork->palette, 50,
                  sWork->titleCount);

    for (i = 0; i < REWARD_CHOICES; i++) {
        DrawTextSlots(i == sWork->cursor ? 36 : 28, 60 + i * 24, sWork->choices[i],
                      i == sWork->cursor ? sWork->cursorPalette : sWork->palette, 50, sWork->choiceCounts[i]);
    }
}

static void RogueReward_Exit(void) {
    s32 i;

    FreeTextSlots(sWork->title, TITLE_SLOTS);

    for (i = 0; i < REWARD_CHOICES; i++) {
        FreeTextSlots(sWork->choices[i], CHOICE_SLOTS);
    }

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
