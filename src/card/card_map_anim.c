/**
 * card_map_anim.c
 * Card Collection and Map Tile Animation
 */

#include "macros.h"
#include "player_progression.h"
#include "game_state.h"
#include "display.h"
#include "taskpool.h"
#include "malloc.h"
#include "card.h"
#include "map_tile_animations.h"
#include "evt_obj.h"
#include "card_api.h"
#include "card_def_data.h"
#include "card_types.h"
#include "evt_types.h"
#include "map_animation_types.h"
#include "player_progression_types.h"
#include "types.h"
#include "gba/macro.h"
#include <stddef.h>
#include "card_deckmenu2.h"
#include "card_ids.h"

Deck gDecks[3] EWRAM_COMMON(16);

u16 gCardCollection[999] EWRAM_COMMON(16);

Deck* gLinkPartnerDeck EWRAM_COMMON(4);

Deck* gLinkSendDeck EWRAM_COMMON(4);

u16 gCardCount EWRAM_COMMON(4);

void map_anim_0(MapTileAnimationWork* work) {
    u8 i;

    work->definition = gMapTileAnimationDefs[gEventState->mapAnim];

    if (work->definition != NULL) {
        for (i = 0; i < work->definition->trackCount; i++) {
            work->frameTimers[i] = 0;
            work->frameIndices[i] = 0;
        }
    }

    work->firstTrack = 0;
}

u8 map_anim_1(MapTileAnimationWork* work) {
    const MapTileAnimationDef* def;
    const MapTileAnimationTrack* track;
    const MapTileAnimationFrame* frame;
    const MapTileAnimationFrame* nextFrame;
    u8 i;
    u8* dst;

    def = work->definition;

    if (def == NULL) {
        return 1;
    }

    for (i = work->firstTrack; i < (def = work->definition)->trackCount; i++) {
        track = &def->tracks[i];
        frame = &track->frames[work->frameIndices[i]];
        work->frameTimers[i]++;

        if (work->frameTimers[i] == frame->duration) {
            work->frameIndices[i]++;

            if (work->frameIndices[i] == track->frameCount) {
                work->frameIndices[i] = 0;
            }

            nextFrame = &track->frames[work->frameIndices[i]];
            dst = (u8*)GetBgCharBase(3) + 0x7000;
            RequestDma3Copy(track->tiles + nextFrame->tileOffset, dst + track->destOffset, track->copySize);
            work->frameTimers[i] = 0;
        }
    }

    return 1;
}

void map_anim_2() {
}

void map_anim_3() {
}

Deck* CreateLinkSendDeck() {
    Deck* active;
    s32 i;

    active = GetActiveDeck();
    gLinkSendDeck = EwramAlloc(sizeof(Deck));

    for (i = 0; i < 99; i++) {
        gLinkSendDeck->cards[i] |= 0xFFFF;
    }

    for (i = 0; i < 99; i++) {
        if (active->cards[i] != 0xFFFF) {
            gLinkSendDeck->cards[i] = gCardCollection[active->cards[i]];
        } else {
            gLinkSendDeck->cards[i] |= 0xFFFF;
        }
    }

    for (i = 0; i < 20; i++) {
        gLinkSendDeck->name[i] = gDecks[GetActiveDeckIndex()].name[i];
    }

    gLinkSendDeck->cpCost = GetDeckCpCost(GetActiveDeckIndex());
    gLinkSendDeck->cardCount = GetDeckCardCount(GetActiveDeckIndex());
    return gLinkSendDeck;
}

void FreeLinkSendDeck() {
    EwramFree(gLinkSendDeck);
}

Deck* CreateLinkPartnerDeck() {
    s32 i;

    gLinkPartnerDeck = EwramAlloc(sizeof(Deck));

    for (i = 0; i < 99; i++) {
        gLinkPartnerDeck->cards[i] |= 0xFFFF;
    }

    for (i = 0; i < 20; i++) {
        gLinkPartnerDeck->name[i] = 0;
    }

    gLinkPartnerDeck->cpCost = 0;
    gLinkPartnerDeck->cardCount = 0;
    return gLinkPartnerDeck;
}

void FreeLinkPartnerDeck() {
    EwramFree(gLinkPartnerDeck);
}

u16 GetLinkPartnerDeckCardCount() {
    return gLinkPartnerDeck->cardCount;
}

u16 CountLinkPartnerDeckCardsOfCategory(u8 slot) {
    u16* cards;
    u16 count;
    u16 i;

    count = 0;
    cards = gLinkPartnerDeck->cards;

    for (i = 0; i < DECK_SIZE; i++) {
        if (cards[i] != 0xFFFF) {
            if (gCardDefs[cards[i] & CARD_ID_MASK].category == slot) {
                count++;
            }
        }
    }

    return count;
}

u16 CountLinkPartnerDeckCards(u8 mode) {
    u8 slot;
    u16* cards;
    u16 count;
    u16 i;

    count = 0;
    cards = gLinkPartnerDeck->cards;

    switch (mode) {
    case 0:
        for (i = 0; i < DECK_SIZE; i++) {
            if (cards[i] != 0xFFFF) {
                slot = gCardDefs[cards[i] & CARD_ID_MASK].category;

                if (slot <= 2) {
                    count++;
                }
            }
        }

        break;
    case 3:
        for (i = 0; i < DECK_SIZE; i++) {
            if (cards[i] != 0xFFFF) {
                if (gCardDefs[cards[i] & CARD_ID_MASK].category == 3) {
                    count++;
                }
            }
        }

        break;
    }

    return count;
}

Deck* GetLinkPartnerDeck() {
    return gLinkPartnerDeck;
}

void CopyLinkPartnerDeckCards(u8 kind, u16* out) {
    Deck* deck;
    u16 i;

    deck = GetLinkPartnerDeck();

    for (i = 0; i < 99; i++) {
        if (deck->cards[i] != 0xFFFF) {
            switch (kind) {
            case 0:
                if (gCardDefs[deck->cards[i] & CARD_ID_MASK].category <= 2) {
                    *out++ = deck->cards[i];
                }

                break;
            case 3:
                if (gCardDefs[deck->cards[i] & CARD_ID_MASK].category == 3) {
                    *out++ = deck->cards[i];
                }

                break;
            }
        }
    }
}

void ObtainCardIntoActiveDeck(u16 cardId) {
    s16 card;

    card = ObtainCard(cardId);

    if (gCardDefs[cardId].value + GetDeckCpCost(GetActiveDeckIndex()) <=
            gGameState.progression.cp &&
        card != -1) {
        AddCardToActiveDeck(card);
    }
}

void InitCardCollection() {
    u16 i;

    for (i = 0; i < 999; i++) {
        gCardCollection[i] = CARD_ID_MASK;
    }

    gCardCount = 911;
}

u16 CountCardsById(u16 cardId) {
    u16 i;
    u16 count;

    i = 0;
    count = 0;

    for (; i < gCardCount; i++) {
        if ((gCardCollection[i] & CARD_ID_MASK) == cardId) {
            count++;
        }
    }

    return count;
}

s16 AddCardToCollection(u16 cardId) {
    u16 i;

    i = 0;

    if (CountCardsById(cardId) > 98) {
        return -1;
    }

    while (gCardCollection[i] != CARD_ID_MASK) {
        i++;

        if (i == gCardCount) {
            return -1;
        }
    }

    if (gCardDefs[cardId & CARD_ID_MASK].flags & CARD_DEF_FLAG_FRIEND) {
        return -1;
    }

    gCardCollection[i] = cardId;

    return i;
}

u8 IsCardCollectionFull() {
    s32 count;
    s32 i;

    count = 0;

    for (i = 0; i < gCardCount; i++) {
        if (gCardCollection[i] == CARD_ID_MASK) {
            count++;
        }
    }

    if (count > 0) {
        return 0;
    }

    return 1;
}

void ExpandCardCollectionForNewCard(u16 cardId) {
    u16 kind;
    u8 jiminyFlag;

    kind = gCardDefs[cardId & CARD_ID_MASK].kind;

    if (kind > 0x61) {
        if (gCardCount > 999) {
            gCardCount = 999;
        }

        return;
    }

    switch (kind) {
    case 0:
        jiminyFlag = 119;
        break;
    case 8:
        jiminyFlag = 127;
        break;
    case 1:
        jiminyFlag = 120;
        break;
    case 2:
        jiminyFlag = 121;
        break;
    case 3:
        jiminyFlag = 122;
        break;
    case 4:
        jiminyFlag = 123;
        break;
    case 5:
        jiminyFlag = 124;
        break;
    case 6:
        jiminyFlag = 125;
        break;
    case 7:
        jiminyFlag = 126;
        break;
    case 9:
        jiminyFlag = 128;
        break;
    case 10:
        jiminyFlag = 129;
        break;
    case 11:
        jiminyFlag = 130;
        break;
    case 12:
        jiminyFlag = 131;
        break;
    case 13:
        jiminyFlag = 132;
        break;
    case 16:
        jiminyFlag = 133;
        break;
    case 14:
        jiminyFlag = 134;
        break;
    case 15:
        jiminyFlag = 135;
        break;
    case 18:
        jiminyFlag = 136;
        break;
    case 19:
        jiminyFlag = 137;
        break;
    case 20:
        jiminyFlag = 138;
        break;
    case 21:
        jiminyFlag = 139;
        break;
    case 22:
        jiminyFlag = 140;
        break;
    case 23:
        jiminyFlag = 141;
        break;
    case 24:
        jiminyFlag = 142;
        break;
    case 25:
        jiminyFlag = 143;
        break;
    case 26:
        jiminyFlag = 144;
        break;
    case 27:
        jiminyFlag = 145;
        break;
    case 28:
        jiminyFlag = 146;
        break;
    case 29:
        jiminyFlag = 147;
        break;
    case 30:
        jiminyFlag = 148;
        break;
    case 31:
        jiminyFlag = 149;
        break;
    case 32:
        jiminyFlag = 150;
        break;
    case 33:
        jiminyFlag = 151;
        break;
    case 34:
        jiminyFlag = 152;
        break;
    case 35:
        jiminyFlag = 153;
        break;
    case 36:
        jiminyFlag = 154;
        break;
    case 37:
        jiminyFlag = 155;
        break;
    case 38:
        jiminyFlag = 156;
        break;
    case 47:
        jiminyFlag = 164;
        break;
    case 50:
        jiminyFlag = 165;
        break;
    case 51:
        jiminyFlag = 166;
        break;
    case 52:
        jiminyFlag = 167;
        break;
    case 53:
        jiminyFlag = 168;
        break;
    case 61:
        jiminyFlag = 169;
        break;
    case 73:
        jiminyFlag = 170;
        break;
    case 74:
        jiminyFlag = 171;
        break;
    case 48:
        jiminyFlag = 172;
        break;
    case 54:
        jiminyFlag = 173;
        break;
    case 55:
        jiminyFlag = 174;
        break;
    case 56:
        jiminyFlag = 175;
        break;
    case 57:
        jiminyFlag = 176;
        break;
    case 59:
        jiminyFlag = 177;
        break;
    case 60:
        jiminyFlag = 178;
        break;
    case 62:
        jiminyFlag = 179;
        break;
    case 64:
        jiminyFlag = 180;
        break;
    case 65:
        jiminyFlag = 181;
        break;
    case 66:
        jiminyFlag = 182;
        break;
    case 67:
        jiminyFlag = 183;
        break;
    case 68:
        jiminyFlag = 184;
        break;
    case 70:
        jiminyFlag = 185;
        break;
    case 71:
        jiminyFlag = 186;
        break;
    case 72:
        jiminyFlag = 187;
        break;
    case 49:
        jiminyFlag = 188;
        break;
    case 58:
        jiminyFlag = 189;
        break;
    case 63:
        jiminyFlag = 190;
        break;
    case 69:
        jiminyFlag = 191;
        break;
    case 76:
        jiminyFlag = 192;
        break;
    case 77:
        jiminyFlag = 193;
        break;
    case 75:
        jiminyFlag = 194;
        break;
    case 81:
        jiminyFlag = 204;
        break;
    case 78:
        jiminyFlag = 195;
        break;
    case 86:
        jiminyFlag = 200;
        break;
    case 80:
        jiminyFlag = 197;
        break;
    case 79:
        jiminyFlag = 201;
        break;
    case 85:
        jiminyFlag = 198;
        break;
    case 87:
        jiminyFlag = 199;
        break;
    case 89:
        jiminyFlag = 203;
        break;
    case 88:
        jiminyFlag = 202;
        break;
    case 84:
        jiminyFlag = 196;
        break;
    case 90:
        jiminyFlag = 247;
        break;
    case 91:
        jiminyFlag = 206;
        break;
    case 92:
        jiminyFlag = 205;
        break;
    case 93:
        jiminyFlag = 207;
        break;
    case 94:
        jiminyFlag = 208;
        break;
    case 82:
    case 83:
        jiminyFlag = 246;
        break;
    case 96:
        jiminyFlag = 248;
        break;
    case 97:
        jiminyFlag = 249;
        break;
    default:
        if (gCardCount > 999) {
            gCardCount = 999;
        }

        return;
    }

    if (!IsJiminyFlagSet(jiminyFlag)) {
        gCardCount++;
    }

    if (gCardCount > 999) {
        gCardCount = 999;
    }
}

s16 ObtainCard(u16 cardId) {
    u16 i = 0;

    if (CountCardsById(cardId) > 98) {
        return -1;
    }

    ExpandCardCollectionForNewCard(cardId);

    while (gCardCollection[i] != CARD_ID_MASK) {
        i++;

        if (i == gCardCount) {
            return -1;
        }
    }

    if (gCardDefs[cardId & CARD_ID_MASK].flags & CARD_DEF_FLAG_FRIEND) {
        return -1;
    }

    gCardCollection[i] = cardId;

    switch (gCardDefs[cardId & CARD_ID_MASK].kind) {
    case CARD_KIND_KINGDOM_KEY:
        SetCardKindObtained(0);
        SetJiminyFlag(119);
        break;
    case CARD_KIND_OLYMPIA:
        SetCardKindObtained(8);
        SetJiminyFlag(127);
        break;
    case CARD_KIND_THREE_WISHES:
        SetCardKindObtained(1);
        SetJiminyFlag(120);
        break;
    case CARD_KIND_CRABCLAW:
        SetCardKindObtained(2);
        SetJiminyFlag(121);
        break;
    case CARD_KIND_PUMPKINHEAD:
        SetCardKindObtained(3);
        SetJiminyFlag(122);
        break;
    case CARD_KIND_FAIRY_HARP:
        SetCardKindObtained(4);
        SetJiminyFlag(123);
        break;
    case CARD_KIND_WISHING_STAR:
        SetCardKindObtained(5);
        SetJiminyFlag(124);
        break;
    case CARD_KIND_SPELLBINDER:
        SetCardKindObtained(6);
        SetJiminyFlag(125);
        break;
    case CARD_KIND_METAL_CHOCOBO:
        SetCardKindObtained(7);
        SetJiminyFlag(126);
        break;
    case CARD_KIND_LIONHEART:
        SetCardKindObtained(9);
        SetJiminyFlag(128);
        break;
    case CARD_KIND_LADY_LUCK:
        SetCardKindObtained(10);
        SetJiminyFlag(129);
        break;
    case CARD_KIND_DIVINE_ROSE:
        SetCardKindObtained(11);
        SetJiminyFlag(130);
        break;
    case CARD_KIND_OATHKEEPER:
        SetCardKindObtained(12);
        SetJiminyFlag(131);
        break;
    case CARD_KIND_OBLIVION:
        SetCardKindObtained(13);
        SetJiminyFlag(132);
        break;
    case CARD_KIND_ULTIMA_WEAPON:
        SetCardKindObtained(14);
        SetJiminyFlag(133);
        break;
    case CARD_KIND_DIAMOND_DUST:
        SetCardKindObtained(15);
        SetJiminyFlag(134);
        break;
    case CARD_KIND_ONE_WINGED_ANGEL:
        SetCardKindObtained(16);
        SetJiminyFlag(135);
        break;
    case CARD_KIND_FIRE:
        SetCardKindObtained(17);
        LearnStock(9);
        LearnStock(10);
        SetJiminyFlag(136);
        break;
    case CARD_KIND_BLIZZARD:
        SetCardKindObtained(18);
        LearnStock(11);
        LearnStock(12);
        SetJiminyFlag(137);
        break;
    case CARD_KIND_THUNDER:
        SetCardKindObtained(19);
        LearnStock(13);
        LearnStock(14);
        SetJiminyFlag(138);
        break;
    case CARD_KIND_CURE:
        SetCardKindObtained(20);
        LearnStock(15);
        LearnStock(16);
        SetJiminyFlag(139);
        break;
    case CARD_KIND_GRAVITY:
        SetCardKindObtained(21);
        LearnStock(17);
        LearnStock(18);
        SetJiminyFlag(140);
        break;
    case CARD_KIND_STOP:
        SetCardKindObtained(22);
        LearnStock(19);
        LearnStock(20);
        SetJiminyFlag(141);
        break;
    case CARD_KIND_AERO:
        SetCardKindObtained(23);
        LearnStock(21);
        LearnStock(22);
        SetJiminyFlag(142);
        break;
    case CARD_KIND_SIMBA:
        SetCardKindObtained(24);
        LearnStock(47);
        SetJiminyFlag(143);
        SetJiminyFlag(23);
        break;
    case CARD_KIND_GENIE:
        SetCardKindObtained(25);
        LearnStock(52);
        SetJiminyFlag(144);
        break;
    case CARD_KIND_BAMBI:
        SetCardKindObtained(26);
        LearnStock(49);
        LearnStock(50);
        SetJiminyFlag(145);
        SetJiminyFlag(25);
        break;
    case CARD_KIND_DUMBO:
        SetCardKindObtained(27);
        LearnStock(48);
        SetJiminyFlag(146);
        SetJiminyFlag(24);
        break;
    case CARD_KIND_TINKER_BELL:
        SetCardKindObtained(28);
        LearnStock(53);
        SetJiminyFlag(147);
        break;
    case CARD_KIND_MUSHU:
        SetCardKindObtained(29);
        LearnStock(51);
        SetJiminyFlag(148);
        SetJiminyFlag(26);
        break;
    case CARD_KIND_CLOUD:
        SetCardKindObtained(30);
        LearnStock(54);
        LearnStock(55);
        SetJiminyFlag(149);
        break;
    case CARD_KIND_POTION:
        SetCardKindObtained(31);
        SetJiminyFlag(150);
        break;
    case CARD_KIND_HI_POTION:
        SetCardKindObtained(32);
        SetJiminyFlag(151);
        break;
    case CARD_KIND_MEGA_POTION:
        SetCardKindObtained(33);
        SetJiminyFlag(152);
        break;
    case CARD_KIND_ETHER:
        SetCardKindObtained(34);
        SetJiminyFlag(153);
        break;
    case CARD_KIND_MEGA_ETHER:
        SetCardKindObtained(35);
        SetJiminyFlag(154);
        break;
    case CARD_KIND_ELIXIR:
        SetCardKindObtained(36);
        SetJiminyFlag(155);
        break;
    case CARD_KIND_MEGALIXIR:
        SetCardKindObtained(37);
        SetJiminyFlag(156);
        break;
    case CARD_KIND_SHADOW:
        SetJiminyFlag(164);
        break;
    case CARD_KIND_RED_NOCTURNE:
        SetJiminyFlag(165);
        break;
    case CARD_KIND_BLUE_RHAPSODY:
        SetJiminyFlag(166);
        break;
    case CARD_KIND_YELLOW_OPERA:
        SetJiminyFlag(167);
        break;
    case CARD_KIND_GREEN_REQUIEM:
        SetJiminyFlag(168);
        break;
    case CARD_KIND_SEA_NEON:
        SetJiminyFlag(169);
        break;
    case CARD_KIND_WHITE_MUSHROOM:
        SetJiminyFlag(170);
        break;
    case CARD_KIND_BLACK_FUNGUS:
        SetJiminyFlag(171);
        break;
    case CARD_KIND_SOLDIER:
        SetJiminyFlag(172);
        break;
    case CARD_KIND_POWERWILD:
        SetJiminyFlag(173);
        break;
    case CARD_KIND_BOUNCYWILD:
        SetJiminyFlag(174);
        break;
    case CARD_KIND_AIR_SOLDIER:
        SetJiminyFlag(175);
        break;
    case CARD_KIND_BANDIT:
        SetJiminyFlag(176);
        break;
    case CARD_KIND_BARREL_SPIDER:
        SetJiminyFlag(177);
        break;
    case CARD_KIND_SEARCH_GHOST:
        SetJiminyFlag(178);
        break;
    case CARD_KIND_SCREWDIVER:
        SetJiminyFlag(179);
        break;
    case CARD_KIND_WIGHT_KNIGHT:
        SetJiminyFlag(180);
        break;
    case CARD_KIND_GARGOYLE:
        SetJiminyFlag(181);
        break;
    case CARD_KIND_PIRATE:
        SetJiminyFlag(182);
        break;
    case CARD_KIND_AIR_PIRATE:
        SetJiminyFlag(183);
        break;
    case CARD_KIND_DARKBALL:
        SetJiminyFlag(184);
        break;
    case CARD_KIND_WYVERN:
        SetJiminyFlag(185);
        break;
    case CARD_KIND_WIZARD:
        SetJiminyFlag(186);
        break;
    case CARD_KIND_NEOSHADOW:
        SetJiminyFlag(187);
        break;
    case CARD_KIND_LARGE_BODY:
        SetJiminyFlag(188);
        break;
    case CARD_KIND_FAT_BANDIT:
        SetJiminyFlag(189);
        break;
    case CARD_KIND_AQUATANK:
        SetJiminyFlag(190);
        break;
    case CARD_KIND_DEFENDER:
        SetJiminyFlag(191);
        break;
    case CARD_KIND_TORNADO_STEP:
        SetJiminyFlag(192);
        break;
    case CARD_KIND_CRESCENDO:
        SetJiminyFlag(193);
        break;
    case CARD_KIND_CREEPER_PLANT:
        SetJiminyFlag(194);
        break;
    case CARD_KIND_DARKSIDE:
        SetJiminyFlag(204);
        break;
    case CARD_KIND_GUARD_ARMOR:
        SetJiminyFlag(195);
        break;
    case CARD_KIND_OOGIE_BOOGIE:
        SetJiminyFlag(200);
        break;
    case CARD_KIND_TRICKMASTER:
        SetJiminyFlag(197);
        break;
    case CARD_KIND_PARASITE_CAGE:
        SetJiminyFlag(201);
        break;
    case CARD_KIND_JAFAR:
        SetJiminyFlag(198);
        break;
    case CARD_KIND_URSULA:
        SetJiminyFlag(199);
        break;
    case CARD_KIND_DRAGON_MALEFICENT:
        SetJiminyFlag(203);
        break;
    case CARD_KIND_HOOK:
        SetJiminyFlag(202);
        break;
    case CARD_KIND_HADES:
        SetJiminyFlag(196);
        break;
    case CARD_KIND_RIKU:
        SetJiminyFlag(247);
        break;
    case CARD_KIND_AXEL:
        SetJiminyFlag(206);
        break;
    case CARD_KIND_LARXENE:
        SetJiminyFlag(205);
        break;
    case CARD_KIND_VEXEN:
        SetJiminyFlag(207);
        break;
    case CARD_KIND_MARLUXIA:
        SetJiminyFlag(208);
        break;
    case CARD_KIND_CARD_SOLDIER_HEART:
    case CARD_KIND_CARD_SOLDIER_SPADE:
        SetJiminyFlag(246);
        break;
    case CARD_KIND_LEXAEUS:
        SetJiminyFlag(248);
        break;
    case CARD_KIND_ANSEM:
        SetJiminyFlag(249);
        break;
    }

    SetRikuCardKindObtained(gCardDefs[cardId].kind);
    return i;
}

void SetRikuCardKindObtained(u16 kind) {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        switch (kind) {
        case CARD_KIND_DARKSIDE:
            SetCardKindObtained(44);
            break;
        case CARD_KIND_GUARD_ARMOR:
            SetCardKindObtained(38);
            break;
        case CARD_KIND_OOGIE_BOOGIE:
            SetCardKindObtained(45);
            break;
        case CARD_KIND_TRICKMASTER:
            SetCardKindObtained(40);
            break;
        case CARD_KIND_PARASITE_CAGE:
            SetCardKindObtained(42);
            break;
        case CARD_KIND_JAFAR:
            SetCardKindObtained(39);
            break;
        case CARD_KIND_URSULA:
            SetCardKindObtained(41);
            break;
        case CARD_KIND_DRAGON_MALEFICENT:
            SetCardKindObtained(43);
            break;
        case CARD_KIND_HOOK:
            SetCardKindObtained(48);
            break;
        case CARD_KIND_HADES:
            SetCardKindObtained(50);
            break;
        case CARD_KIND_RIKU:
            SetCardKindObtained(51);
            break;
        case CARD_KIND_VEXEN:
            SetCardKindObtained(54);
            break;
        case CARD_KIND_LEXAEUS:
            SetCardKindObtained(57);
            break;
        }
    }
}

u16 CountCollectionCards() {
    u16 count;
    u16 i;

    count = i = 0;

    for (i = 0; i < gCardCount; i++) {
        if (gCardCollection[i] != CARD_ID_MASK) {
            count++;
        }
    }

    return count;
}

u16 CountCardsInDecks() {
    u16 count;
    u16 i;

    count = i = 0;

    for (i = 0; i < gCardCount; i++) {
        if (gCardCollection[i] != CARD_ID_MASK && (gCardCollection[i] & 0x7000)) {
            count++;
        }
    }

    return count;
}

u16 ListCardKindsNotInDeck(u8 deck, u8 mode, u16* out) {
    u16 count;
    u16 total;
    u16 mask;
    u16* present;
    u16 i;

    mask = total = count = 0;
    present = EwramAlloc(0x23C);
    CpuFill32(0, present, 0x23C);

    if (mode == 1) {
        switch (deck) {
        case 0:
            mask = 0x1000;
            break;
        case 1:
            mask = 0x2000;
            break;
        case 2:
            mask = 0x4000;
            break;
        }
    } else {
        mask = 0x7000;
    }

    for (i = 0; i < gCardCount; i++) {
        if (gCardCollection[i] == CARD_ID_MASK) {
            continue;
        }

        if (gCardCollection[i] & mask) {
            continue;
        }

        if (!(gCardCollection[i] & 0x8000)) {
            present[gCardDefs[gCardCollection[i] & CARD_ID_MASK].kind] = 1;
        } else {
            present[gCardDefs[gCardCollection[i] & CARD_ID_MASK].kind + 0x8F] = 1;
        }
    }

    for (i = 0; i < 0x11E; i++) {
        if (present[i] != 0) {
            total += present[i];
            out[count++] = i;
        }
    }

    EwramFree(present);
    return total;
}

static const MapTileAnimationFrame sMapTileAnim0Frames0[4] = {
    {0, 18},
    {1024, 12},
    {2048, 12},
    {1024, 12},
};

static const MapTileAnimationFrame sMapTileAnim0Frames1[4] = {
    {0, 15},
    {3232, 15},
    {6464, 15},
    {9696, 15},
};

static const MapTileAnimationTrack sMapTileAnim0Tracks[2] = {
    {sMapTileAnim0Frames0, gMapTileAnim0Track0Tiles, 4, 3232, 864},
    {sMapTileAnim0Frames1, gMapTileAnim0Track1Tiles, 4, 0, 3232},
};

static const MapTileAnimationDef sMapTileAnim0Def = {
    sMapTileAnim0Tracks, 2, 1,
};

static const MapTileAnimationFrame sMapTileAnim1Frames0[4] = {
    {0, 70},
    {192, 7},
    {384, 15},
    {192, 7},
};

static const MapTileAnimationFrame sMapTileAnim1Frames1[4] = {
    {0, 25},
    {192, 7},
    {384, 15},
    {192, 7},
};

static const MapTileAnimationFrame sMapTileAnim1Frames2[4] = {
    {0, 10},
    {96, 10},
    {192, 10},
    {96, 10},
};

static const MapTileAnimationFrame sMapTileAnim1Frames3[4] = {
    {0, 50},
    {128, 7},
    {256, 10},
    {128, 10},
};

static const MapTileAnimationFrame sMapTileAnim1Frames4[4] = {
    {0, 10},
    {352, 20},
    {0, 7},
    {352, 150},
};

static const MapTileAnimationFrame sMapTileAnim1Frames5[4] = {
    {0, 50},
    {128, 5},
    {0, 7},
    {128, 5},
};

static const MapTileAnimationTrack sMapTileAnim1Tracks[6] = {
    {sMapTileAnim1Frames0, gMapTileAnim1Track0Tiles, 4, 2048, 192},
    {sMapTileAnim1Frames1, gMapTileAnim1Track1Tiles, 4, 2240, 192},
    {sMapTileAnim1Frames2, gMapTileAnim1Track2Tiles, 4, 2432, 96},
    {sMapTileAnim1Frames3, gMapTileAnim1Track3Tiles, 4, 2528, 128},
    {sMapTileAnim1Frames4, gMapTileAnim1Track4Tiles, 4, 3072, 352},
    {sMapTileAnim1Frames5, gMapTileAnim1Track5Tiles, 4, 3424, 128},
};

static const MapTileAnimationDef sMapTileAnim1Def = {
    sMapTileAnim1Tracks, 6, 0,
};

static const MapTileAnimationFrame sMapTileAnim2Frames[5] = {
    {0, 6},
    {1024, 6},
    {2048, 6},
    {3072, 6},
    {4096, 6},
};

static const MapTileAnimationTrack sMapTileAnim2Track = {
    sMapTileAnim2Frames, gMapTileAnim2Tiles, 5, 3072, 896,
};

static const MapTileAnimationDef sMapTileAnim2Def = {
    &sMapTileAnim2Track, 1, 1,
};

static const MapTileAnimationFrame sMapTileAnim3Frames[4] = {
    {0, 30},
    {3072, 30},
    {6144, 30},
    {9216, 30},
};

static const MapTileAnimationTrack sMapTileAnim3Track = {
    sMapTileAnim3Frames, gMapTileAnim3Tiles, 4, -15360, 3072,
};

static const MapTileAnimationDef sMapTileAnim3Def = {
    &sMapTileAnim3Track, 1, 1,
};

static const MapTileAnimationFrame sMapTileAnim4Frames[6] = {
    {0, 20},
    {1024, 20},
    {2048, 20},
    {3072, 20},
    {4096, 20},
    {5120, 20},
};

static const MapTileAnimationTrack sMapTileAnim4Track = {
    sMapTileAnim4Frames, gMapTileAnim4Tiles, 6, -5120, 1024,
};

static const MapTileAnimationDef sMapTileAnim4Def = {
    &sMapTileAnim4Track, 1, 1,
};

const MapTileAnimationDef* gMapTileAnimationDefs[6] = {
    &sMapTileAnim0Def,
    &sMapTileAnim1Def,
    &sMapTileAnim2Def,
    &sMapTileAnim3Def,
    &sMapTileAnim4Def,
    NULL,
};

const MapTileAnimationDef* gUnk_09EE4A44 = {
    NULL,
};

const MapTileAnimationDef* gUnk_09EE4A48 = {
    NULL,
};

const MapTileAnimationDef* gUnk_09EE4A4C = {
    NULL,
};

TaskDesc gTaskDescMapAnim = {
    "map_anim",
    (TaskInitFunc)map_anim_0,
    (TaskUpdateFunc)map_anim_1,
    (TaskDrawFunc)map_anim_2,
    (TaskDestroyFunc)map_anim_3,
    sizeof(MapTileAnimationWork),
};
