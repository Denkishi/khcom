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
#include "jiminy_records_index_data.h"

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
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_KINGDOM_KEY;
        break;
    case 8:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_OLYMPIA;
        break;
    case 1:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_THREE_WISHES;
        break;
    case 2:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_CRABCLAW;
        break;
    case 3:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_PUMPKINHEAD;
        break;
    case 4:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_FAIRY_HARP;
        break;
    case 5:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_WISHING_STAR;
        break;
    case 6:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_SPELLBINDER;
        break;
    case 7:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_METAL_CHOCOBO;
        break;
    case 9:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_LIONHEART;
        break;
    case 10:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_LADY_LUCK;
        break;
    case 11:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_DIVINE_ROSE;
        break;
    case 12:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_OATHKEEPER;
        break;
    case 13:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_OBLIVION;
        break;
    case 16:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_ULTIMA_WEAPON;
        break;
    case 14:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_DIAMOND_DUST;
        break;
    case 15:
        jiminyFlag = JIMINY_RECORD_ATTACK_CARD_ONE_WINGED_ANGEL;
        break;
    case 18:
        jiminyFlag = JIMINY_RECORD_MAGIC_CARD_FIRE;
        break;
    case 19:
        jiminyFlag = JIMINY_RECORD_MAGIC_CARD_BLIZZARD;
        break;
    case 20:
        jiminyFlag = JIMINY_RECORD_MAGIC_CARD_THUNDER;
        break;
    case 21:
        jiminyFlag = JIMINY_RECORD_MAGIC_CARD_CURE;
        break;
    case 22:
        jiminyFlag = JIMINY_RECORD_MAGIC_CARD_GRAVITY;
        break;
    case 23:
        jiminyFlag = JIMINY_RECORD_MAGIC_CARD_STOP;
        break;
    case 24:
        jiminyFlag = JIMINY_RECORD_MAGIC_CARD_AERO;
        break;
    case 25:
        jiminyFlag = JIMINY_RECORD_MAGIC_CARD_SIMBA;
        break;
    case 26:
        jiminyFlag = JIMINY_RECORD_MAGIC_CARD_GENIE;
        break;
    case 27:
        jiminyFlag = JIMINY_RECORD_MAGIC_CARD_BAMBI;
        break;
    case 28:
        jiminyFlag = JIMINY_RECORD_MAGIC_CARD_DUMBO;
        break;
    case 29:
        jiminyFlag = JIMINY_RECORD_MAGIC_CARD_TINKER_BELL;
        break;
    case 30:
        jiminyFlag = JIMINY_RECORD_MAGIC_CARD_MUSHU;
        break;
    case 31:
        jiminyFlag = JIMINY_RECORD_MAGIC_CARD_CLOUD;
        break;
    case 32:
        jiminyFlag = JIMINY_RECORD_ITEM_CARD_POTION;
        break;
    case 33:
        jiminyFlag = JIMINY_RECORD_ITEM_CARD_HI_POTION;
        break;
    case 34:
        jiminyFlag = JIMINY_RECORD_ITEM_CARD_MEGA_POTION;
        break;
    case 35:
        jiminyFlag = JIMINY_RECORD_ITEM_CARD_ETHER;
        break;
    case 36:
        jiminyFlag = JIMINY_RECORD_ITEM_CARD_MEGA_ETHER;
        break;
    case 37:
        jiminyFlag = JIMINY_RECORD_ITEM_CARD_ELIXIR;
        break;
    case 38:
        jiminyFlag = JIMINY_RECORD_ITEM_CARD_MEGALIXIR;
        break;
    case 47:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_SHADOW;
        break;
    case 50:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_RED_NOCTURNE;
        break;
    case 51:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_BLUE_RHAPSODY;
        break;
    case 52:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_YELLOW_OPERA;
        break;
    case 53:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_GREEN_REQUIEM;
        break;
    case 61:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_SEA_NEON;
        break;
    case 73:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_WHITE_MUSHROOM;
        break;
    case 74:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_BLACK_FUNGUS;
        break;
    case 48:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_SOLDIER;
        break;
    case 54:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_POWERWILD;
        break;
    case 55:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_BOUNCYWILD;
        break;
    case 56:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_AIR_SOLDIER;
        break;
    case 57:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_BANDIT;
        break;
    case 59:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_BARREL_SPIDER;
        break;
    case 60:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_SEARCH_GHOST;
        break;
    case 62:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_SCREWDIVER;
        break;
    case 64:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_WIGHT_KNIGHT;
        break;
    case 65:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_GARGOYLE;
        break;
    case 66:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_PIRATE;
        break;
    case 67:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_AIR_PIRATE;
        break;
    case 68:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_DARKBALL;
        break;
    case 70:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_WYVERN;
        break;
    case 71:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_WIZARD;
        break;
    case 72:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_NEOSHADOW;
        break;
    case 49:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_LARGE_BODY;
        break;
    case 58:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_FAT_BANDIT;
        break;
    case 63:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_AQUATANK;
        break;
    case 69:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_DEFENDER;
        break;
    case 76:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_TORNADO_STEP;
        break;
    case 77:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_CRESCENDO;
        break;
    case 75:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_CREEPER_PLANT;
        break;
    case 81:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_DARKSIDE;
        break;
    case 78:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_GUARD_ARMOR;
        break;
    case 86:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_OOGIE_BOOGIE;
        break;
    case 80:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_TRICKMASTER;
        break;
    case 79:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_PARASITE_CAGE;
        break;
    case 85:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_JAFAR;
        break;
    case 87:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_URSULA;
        break;
    case 89:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_DRAGON_MALEFICENT;
        break;
    case 88:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_HOOK;
        break;
    case 84:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_HADES;
        break;
    case 90:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_RIKU;
        break;
    case 91:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_AXEL;
        break;
    case 92:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_LARXENE;
        break;
    case 93:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_VEXEN;
        break;
    case 94:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_MARLUXIA;
        break;
    case 82:
    case 83:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_CARD_SOLDIER;
        break;
    case 96:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_LEXAEUS;
        break;
    case 97:
        jiminyFlag = JIMINY_RECORD_ENEMY_CARD_ANSEM;
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
        SetCardKindObtained(OBTAINED_CARD_KINGDOM_KEY);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_KINGDOM_KEY);
        break;
    case CARD_KIND_OLYMPIA:
        SetCardKindObtained(OBTAINED_CARD_OLYMPIA);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_OLYMPIA);
        break;
    case CARD_KIND_THREE_WISHES:
        SetCardKindObtained(OBTAINED_CARD_THREE_WISHES);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_THREE_WISHES);
        break;
    case CARD_KIND_CRABCLAW:
        SetCardKindObtained(OBTAINED_CARD_CRABCLAW);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_CRABCLAW);
        break;
    case CARD_KIND_PUMPKINHEAD:
        SetCardKindObtained(OBTAINED_CARD_PUMPKINHEAD);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_PUMPKINHEAD);
        break;
    case CARD_KIND_FAIRY_HARP:
        SetCardKindObtained(OBTAINED_CARD_FAIRY_HARP);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_FAIRY_HARP);
        break;
    case CARD_KIND_WISHING_STAR:
        SetCardKindObtained(OBTAINED_CARD_WISHING_STAR);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_WISHING_STAR);
        break;
    case CARD_KIND_SPELLBINDER:
        SetCardKindObtained(OBTAINED_CARD_SPELLBINDER);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_SPELLBINDER);
        break;
    case CARD_KIND_METAL_CHOCOBO:
        SetCardKindObtained(OBTAINED_CARD_METAL_CHOCOBO);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_METAL_CHOCOBO);
        break;
    case CARD_KIND_LIONHEART:
        SetCardKindObtained(OBTAINED_CARD_LIONHEART);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_LIONHEART);
        break;
    case CARD_KIND_LADY_LUCK:
        SetCardKindObtained(OBTAINED_CARD_LADY_LUCK);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_LADY_LUCK);
        break;
    case CARD_KIND_DIVINE_ROSE:
        SetCardKindObtained(OBTAINED_CARD_DIVINE_ROSE);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_DIVINE_ROSE);
        break;
    case CARD_KIND_OATHKEEPER:
        SetCardKindObtained(OBTAINED_CARD_OATHKEEPER);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_OATHKEEPER);
        break;
    case CARD_KIND_OBLIVION:
        SetCardKindObtained(OBTAINED_CARD_OBLIVION);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_OBLIVION);
        break;
    case CARD_KIND_ULTIMA_WEAPON:
        SetCardKindObtained(OBTAINED_CARD_ULTIMA_WEAPON);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_ULTIMA_WEAPON);
        break;
    case CARD_KIND_DIAMOND_DUST:
        SetCardKindObtained(OBTAINED_CARD_DIAMOND_DUST);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_DIAMOND_DUST);
        break;
    case CARD_KIND_ONE_WINGED_ANGEL:
        SetCardKindObtained(OBTAINED_CARD_ONE_WINGED_ANGEL);
        SetJiminyFlag(JIMINY_RECORD_ATTACK_CARD_ONE_WINGED_ANGEL);
        break;
    case CARD_KIND_FIRE:
        SetCardKindObtained(OBTAINED_CARD_FIRE);
        LearnStock(LEARNED_STOCK_FIRA);
        LearnStock(LEARNED_STOCK_FIRAGA);
        SetJiminyFlag(JIMINY_RECORD_MAGIC_CARD_FIRE);
        break;
    case CARD_KIND_BLIZZARD:
        SetCardKindObtained(OBTAINED_CARD_BLIZZARD);
        LearnStock(LEARNED_STOCK_BLIZZARA);
        LearnStock(LEARNED_STOCK_BLIZZAGA);
        SetJiminyFlag(JIMINY_RECORD_MAGIC_CARD_BLIZZARD);
        break;
    case CARD_KIND_THUNDER:
        SetCardKindObtained(OBTAINED_CARD_THUNDER);
        LearnStock(LEARNED_STOCK_THUNDARA);
        LearnStock(LEARNED_STOCK_THUNDAGA);
        SetJiminyFlag(JIMINY_RECORD_MAGIC_CARD_THUNDER);
        break;
    case CARD_KIND_CURE:
        SetCardKindObtained(OBTAINED_CARD_CURE);
        LearnStock(LEARNED_STOCK_CURA);
        LearnStock(LEARNED_STOCK_CURAGA);
        SetJiminyFlag(JIMINY_RECORD_MAGIC_CARD_CURE);
        break;
    case CARD_KIND_GRAVITY:
        SetCardKindObtained(OBTAINED_CARD_GRAVITY);
        LearnStock(LEARNED_STOCK_GRAVIRA);
        LearnStock(LEARNED_STOCK_GRAVIGA);
        SetJiminyFlag(JIMINY_RECORD_MAGIC_CARD_GRAVITY);
        break;
    case CARD_KIND_STOP:
        SetCardKindObtained(OBTAINED_CARD_STOP);
        LearnStock(LEARNED_STOCK_STOPRA);
        LearnStock(LEARNED_STOCK_STOPGA);
        SetJiminyFlag(JIMINY_RECORD_MAGIC_CARD_STOP);
        break;
    case CARD_KIND_AERO:
        SetCardKindObtained(OBTAINED_CARD_AERO);
        LearnStock(LEARNED_STOCK_AERORA);
        LearnStock(LEARNED_STOCK_AEROGA);
        SetJiminyFlag(JIMINY_RECORD_MAGIC_CARD_AERO);
        break;
    case CARD_KIND_SIMBA:
        SetCardKindObtained(OBTAINED_CARD_SIMBA);
        LearnStock(LEARNED_STOCK_PROUD_ROAR);
        SetJiminyFlag(JIMINY_RECORD_MAGIC_CARD_SIMBA);
        SetJiminyFlag(JIMINY_RECORD_CHARACTER_SIMBA);
        break;
    case CARD_KIND_GENIE:
        SetCardKindObtained(OBTAINED_CARD_GENIE);
        LearnStock(LEARNED_STOCK_SHOWTIME);
        SetJiminyFlag(JIMINY_RECORD_MAGIC_CARD_GENIE);
        break;
    case CARD_KIND_BAMBI:
        SetCardKindObtained(OBTAINED_CARD_BAMBI);
        LearnStock(LEARNED_STOCK_PARADISE);
        LearnStock(LEARNED_STOCK_IDYLL_ROMP);
        SetJiminyFlag(JIMINY_RECORD_MAGIC_CARD_BAMBI);
        SetJiminyFlag(JIMINY_RECORD_CHARACTER_BAMBI);
        break;
    case CARD_KIND_DUMBO:
        SetCardKindObtained(OBTAINED_CARD_DUMBO);
        LearnStock(LEARNED_STOCK_SPLASH);
        SetJiminyFlag(JIMINY_RECORD_MAGIC_CARD_DUMBO);
        SetJiminyFlag(JIMINY_RECORD_CHARACTER_DUMBO);
        break;
    case CARD_KIND_TINKER_BELL:
        SetCardKindObtained(OBTAINED_CARD_TINKER_BELL);
        LearnStock(LEARNED_STOCK_TWINKLE);
        SetJiminyFlag(JIMINY_RECORD_MAGIC_CARD_TINKER_BELL);
        break;
    case CARD_KIND_MUSHU:
        SetCardKindObtained(OBTAINED_CARD_MUSHU);
        LearnStock(LEARNED_STOCK_FLARE_BREATH);
        SetJiminyFlag(JIMINY_RECORD_MAGIC_CARD_MUSHU);
        SetJiminyFlag(JIMINY_RECORD_CHARACTER_MUSHU);
        break;
    case CARD_KIND_CLOUD:
        SetCardKindObtained(OBTAINED_CARD_CLOUD);
        LearnStock(LEARNED_STOCK_CROSS_SLASH);
        LearnStock(LEARNED_STOCK_OMNISLASH);
        SetJiminyFlag(JIMINY_RECORD_MAGIC_CARD_CLOUD);
        break;
    case CARD_KIND_POTION:
        SetCardKindObtained(OBTAINED_CARD_POTION);
        SetJiminyFlag(JIMINY_RECORD_ITEM_CARD_POTION);
        break;
    case CARD_KIND_HI_POTION:
        SetCardKindObtained(OBTAINED_CARD_HI_POTION);
        SetJiminyFlag(JIMINY_RECORD_ITEM_CARD_HI_POTION);
        break;
    case CARD_KIND_MEGA_POTION:
        SetCardKindObtained(OBTAINED_CARD_MEGA_POTION);
        SetJiminyFlag(JIMINY_RECORD_ITEM_CARD_MEGA_POTION);
        break;
    case CARD_KIND_ETHER:
        SetCardKindObtained(OBTAINED_CARD_ETHER);
        SetJiminyFlag(JIMINY_RECORD_ITEM_CARD_ETHER);
        break;
    case CARD_KIND_MEGA_ETHER:
        SetCardKindObtained(OBTAINED_CARD_MEGA_ETHER);
        SetJiminyFlag(JIMINY_RECORD_ITEM_CARD_MEGA_ETHER);
        break;
    case CARD_KIND_ELIXIR:
        SetCardKindObtained(OBTAINED_CARD_ELIXIR);
        SetJiminyFlag(JIMINY_RECORD_ITEM_CARD_ELIXIR);
        break;
    case CARD_KIND_MEGALIXIR:
        SetCardKindObtained(OBTAINED_CARD_MEGALIXIR);
        SetJiminyFlag(JIMINY_RECORD_ITEM_CARD_MEGALIXIR);
        break;
    case CARD_KIND_SHADOW:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_SHADOW);
        break;
    case CARD_KIND_RED_NOCTURNE:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_RED_NOCTURNE);
        break;
    case CARD_KIND_BLUE_RHAPSODY:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_BLUE_RHAPSODY);
        break;
    case CARD_KIND_YELLOW_OPERA:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_YELLOW_OPERA);
        break;
    case CARD_KIND_GREEN_REQUIEM:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_GREEN_REQUIEM);
        break;
    case CARD_KIND_SEA_NEON:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_SEA_NEON);
        break;
    case CARD_KIND_WHITE_MUSHROOM:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_WHITE_MUSHROOM);
        break;
    case CARD_KIND_BLACK_FUNGUS:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_BLACK_FUNGUS);
        break;
    case CARD_KIND_SOLDIER:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_SOLDIER);
        break;
    case CARD_KIND_POWERWILD:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_POWERWILD);
        break;
    case CARD_KIND_BOUNCYWILD:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_BOUNCYWILD);
        break;
    case CARD_KIND_AIR_SOLDIER:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_AIR_SOLDIER);
        break;
    case CARD_KIND_BANDIT:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_BANDIT);
        break;
    case CARD_KIND_BARREL_SPIDER:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_BARREL_SPIDER);
        break;
    case CARD_KIND_SEARCH_GHOST:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_SEARCH_GHOST);
        break;
    case CARD_KIND_SCREWDIVER:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_SCREWDIVER);
        break;
    case CARD_KIND_WIGHT_KNIGHT:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_WIGHT_KNIGHT);
        break;
    case CARD_KIND_GARGOYLE:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_GARGOYLE);
        break;
    case CARD_KIND_PIRATE:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_PIRATE);
        break;
    case CARD_KIND_AIR_PIRATE:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_AIR_PIRATE);
        break;
    case CARD_KIND_DARKBALL:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_DARKBALL);
        break;
    case CARD_KIND_WYVERN:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_WYVERN);
        break;
    case CARD_KIND_WIZARD:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_WIZARD);
        break;
    case CARD_KIND_NEOSHADOW:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_NEOSHADOW);
        break;
    case CARD_KIND_LARGE_BODY:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_LARGE_BODY);
        break;
    case CARD_KIND_FAT_BANDIT:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_FAT_BANDIT);
        break;
    case CARD_KIND_AQUATANK:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_AQUATANK);
        break;
    case CARD_KIND_DEFENDER:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_DEFENDER);
        break;
    case CARD_KIND_TORNADO_STEP:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_TORNADO_STEP);
        break;
    case CARD_KIND_CRESCENDO:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_CRESCENDO);
        break;
    case CARD_KIND_CREEPER_PLANT:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_CREEPER_PLANT);
        break;
    case CARD_KIND_DARKSIDE:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_DARKSIDE);
        break;
    case CARD_KIND_GUARD_ARMOR:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_GUARD_ARMOR);
        break;
    case CARD_KIND_OOGIE_BOOGIE:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_OOGIE_BOOGIE);
        break;
    case CARD_KIND_TRICKMASTER:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_TRICKMASTER);
        break;
    case CARD_KIND_PARASITE_CAGE:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_PARASITE_CAGE);
        break;
    case CARD_KIND_JAFAR:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_JAFAR);
        break;
    case CARD_KIND_URSULA:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_URSULA);
        break;
    case CARD_KIND_DRAGON_MALEFICENT:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_DRAGON_MALEFICENT);
        break;
    case CARD_KIND_HOOK:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_HOOK);
        break;
    case CARD_KIND_HADES:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_HADES);
        break;
    case CARD_KIND_RIKU:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_RIKU);
        break;
    case CARD_KIND_AXEL:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_AXEL);
        break;
    case CARD_KIND_LARXENE:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_LARXENE);
        break;
    case CARD_KIND_VEXEN:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_VEXEN);
        break;
    case CARD_KIND_MARLUXIA:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_MARLUXIA);
        break;
    case CARD_KIND_CARD_SOLDIER_HEART:
    case CARD_KIND_CARD_SOLDIER_SPADE:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_CARD_SOLDIER);
        break;
    case CARD_KIND_LEXAEUS:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_LEXAEUS);
        break;
    case CARD_KIND_ANSEM:
        SetJiminyFlag(JIMINY_RECORD_ENEMY_CARD_ANSEM);
        break;
    }

    SetRikuCardKindObtained(gCardDefs[cardId].kind);
    return i;
}

void SetRikuCardKindObtained(u16 kind) {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        switch (kind) {
        case CARD_KIND_DARKSIDE:
            SetCardKindObtained(OBTAINED_CARD_DARKSIDE);
            break;
        case CARD_KIND_GUARD_ARMOR:
            SetCardKindObtained(OBTAINED_CARD_GUARD_ARMOR);
            break;
        case CARD_KIND_OOGIE_BOOGIE:
            SetCardKindObtained(OBTAINED_CARD_OOGIE_BOOGIE);
            break;
        case CARD_KIND_TRICKMASTER:
            SetCardKindObtained(OBTAINED_CARD_TRICKMASTER);
            break;
        case CARD_KIND_PARASITE_CAGE:
            SetCardKindObtained(OBTAINED_CARD_PARASITE_CAGE);
            break;
        case CARD_KIND_JAFAR:
            SetCardKindObtained(OBTAINED_CARD_JAFAR);
            break;
        case CARD_KIND_URSULA:
            SetCardKindObtained(OBTAINED_CARD_URSULA);
            break;
        case CARD_KIND_DRAGON_MALEFICENT:
            SetCardKindObtained(OBTAINED_CARD_DRAGON_MALEFICENT);
            break;
        case CARD_KIND_HOOK:
            SetCardKindObtained(OBTAINED_CARD_HOOK);
            break;
        case CARD_KIND_HADES:
            SetCardKindObtained(OBTAINED_CARD_HADES);
            break;
        case CARD_KIND_RIKU:
            SetCardKindObtained(OBTAINED_CARD_RIKU);
            break;
        case CARD_KIND_VEXEN:
            SetCardKindObtained(OBTAINED_CARD_VEXEN);
            break;
        case CARD_KIND_LEXAEUS:
            SetCardKindObtained(OBTAINED_CARD_LEXAEUS);
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
