#include "card_localized_data.h"
#include "msg_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "msg_api.h"
#include "mode_sio_api.h"
#include "card_battle.h"
#include "m4a_song.h"
#include "game_state.h"
#include "text.h"
#include "monsgage.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "display.h"
#include "engine_math.h"
#include "listpool.h"
#include "anim.h"
#include "obj.h"
#include "text_types.h"
#include "taskpool.h"
#include "key.h"
#include "gba/syscall.h"
#include "card.h"
#include "card_message_assets.h"
#include "card_description_assets.h"
#include "game.h"
#include "bos4_api.h"
#include "sprites_card.h"
#include "card_ids.h"
#include "card_description_text.h"
#include "card_deck.h"

#ifndef VERSION_EU
TaskPool gModeDeckExchangeTasks;

u8 gModeDeckExchangeResult;

u8 gUnk_02034B1D[3];
#endif

#ifndef VERSION_EU
void Mode_DeckExchange_0(void) {
    gModeDeckExchangeResult = 0;
    gSioTradeCardId = 2048;
    TaskPoolInit(&gModeDeckExchangeTasks, 1);
    TaskCreate(&gModeDeckExchangeTasks, &gTaskDescDeckexchange, &gModeDeckExchangeResult);
}

void Mode_DeckExchange_1(void) {
    if (gSystemFlags & SYSTEM_FLAG_LINK_ACTIVE) {
        SioChgCardRecvSlotIds();
    } else {
        UpdatePlayTime();
    }

    TaskPoolUpdate(&gModeDeckExchangeTasks);
    TaskPoolDraw(&gModeDeckExchangeTasks);

    if (gModeDeckExchangeResult == 6) {
        ModeRequest(&gModeSioChgCard, gSioTradeCardId);
    }
}

void Mode_DeckExchange_2(void) {
    TaskPoolDestroy(&gModeDeckExchangeTasks);
}
#endif

void DarkPoint_0(DarkPointWork* w) {
    w->tiles = LoadObjTiles(gUnk_093FB6C4, 576);
    w->slideTimer = 8;
    w->x = -0x2000;
    SplitFourDigits(gBtlWork->darkPoints, &w->thousands);
}

s32 DarkPoint_1(DarkPointWork* w) {
    SplitFourDigits(gBtlWork->darkPoints, &w->thousands);

    if (w->slideTimer > 0) {
        ApproachValue(&w->x, 0, (u16)w->slideTimer);
        w->slideTimer--;
    }

    return 1;
}

void DarkPoint_2(DarkPointWork* w) {
    DrawSprite(w->x >> 8, 27, gUnk_09EF1298[0], w->tiles, gCardBattleState->palette, 0, 0, 30);

    if (w->hundreds != 0) {
        DrawSprite((w->x >> 8) + 11, 30, gUnk_09EF1298[w->hundreds + 1], w->tiles, gCardBattleState->palette, 0, 0, 29);
        DrawSprite((w->x >> 8) + 17, 30, gUnk_09EF1298[w->tens + 1], w->tiles, gCardBattleState->palette, 0, 0, 29);
        DrawSprite((w->x >> 8) + 23, 30, gUnk_09EF1298[w->ones + 1], w->tiles, gCardBattleState->palette, 0, 0, 29);
    } else if (w->tens != 0) {
        DrawSprite((w->x >> 8) + 15, 30, gUnk_09EF1298[w->tens + 1], w->tiles, gCardBattleState->palette, 0, 0, 29);
        DrawSprite((w->x >> 8) + 21, 30, gUnk_09EF1298[w->ones + 1], w->tiles, gCardBattleState->palette, 0, 0, 29);
    } else {
        DrawSprite((w->x >> 8) + 17, 30, gUnk_09EF1298[w->ones + 1], w->tiles, gCardBattleState->palette, 0, 0, 29);
    }
}

void DarkPoint_3(DarkPointWork* w) {
    ReleaseObjTiles(w->tiles);
}

void AddCardToDeckViaActive(u8 a, u16 b) {
    u8 saved;

    saved = GetActiveDeckIndex();
    SetActiveDeckIndex(a);
    AddCardToActiveDeck(b);
    SetActiveDeckIndex(saved);
}

void FillDebugCardCollection(void) {
#ifdef VERSION_EU
    u16 i;
    u16 n;

    n = 0;
    gCardCount = 999;

    for (i = 0; i < 170; i++) {
        gCardCollection[n++] = i;
    }

    for (i = 170; i < 380; i++) {
        gCardCollection[n++] = i;
    }

    for (i = 380; i < 450; i++) {
        gCardCollection[n++] = i;
    }

    for (i = 380; i < 450; i++) {
        gCardCollection[n++] = i;
    }

    for (i = 450; i < 526; i += 3) {
        gCardCollection[n++] = i;
    }

    gCardCollection[n++] = CARD_WHITE_MUSHROOM_2;
    gCardCollection[n++] = 529;
    gCardCollection[n++] = CARD_CREEPER_PLANT_2;
    gCardCollection[n++] = CARD_TORNADO_STEP_2;
    gCardCollection[n++] = CARD_CRESCENDO_2;
    gCardCollection[n++] = CARD_GUARD_ARMOR_1;
    gCardCollection[n++] = CARD_TRICKMASTER_1;
    gCardCollection[n++] = CARD_PARASITE_CAGE_1;
    gCardCollection[n++] = CARD_DARKSIDE_1;
    gCardCollection[n++] = CARD_CARD_SOLDIER_2;
    gCardCollection[n++] = CARD_HADES_9;
    gCardCollection[n++] = CARD_JAFAR_1;
    gCardCollection[n++] = CARD_OOGIE_BOOGIE_1;
    gCardCollection[n++] = CARD_URSULA_1;
    gCardCollection[n++] = CARD_HOOK_9;
    gCardCollection[n++] = CARD_DRAGON_MALEFICENT_1;
    gCardCollection[n++] = CARD_RIKU_9;
    gCardCollection[n++] = CARD_AXEL_9;
    gCardCollection[n++] = CARD_LARXENE_9;
    gCardCollection[n++] = CARD_VEXEN_9;
    gCardCollection[n++] = CARD_MARLUXIA_9;
    gCardCollection[n++] = CARD_LEXAEUS_9;
    gCardCollection[n++] = CARD_ANSEM_9;

    for (i = 0; i < 170; i++) {
        if (n < 999) {
            gCardCollection[n++] = i | 0x8000;
        }
    }

    for (i = 170; i < 240; i++) {
        if (n < 999) {
            gCardCollection[n++] = i | 0x8000;
        }
    }

    for (i = 0; i < 95; i++) {
        gCardCollection[n++] = CARD_ID(CARD_KINGDOM_KEY, 6);
    }
#endif
}

void func_080AB22C(u8 a) {
    AddCardToDeckViaActive(a, 0);
    AddCardToDeckViaActive(a, 1);
    AddCardToDeckViaActive(a, 2);
    AddCardToDeckViaActive(a, 3);
    AddCardToDeckViaActive(a, 4);
    AddCardToDeckViaActive(a, 5);
    AddCardToDeckViaActive(a, 6);
    AddCardToDeckViaActive(a, 7);
    AddCardToDeckViaActive(a, 8);
    AddCardToDeckViaActive(a, 9);
    AddCardToDeckViaActive(a, 73);
    AddCardToDeckViaActive(a, 74);
    AddCardToDeckViaActive(a, 75);
    AddCardToDeckViaActive(a, 76);
    AddCardToDeckViaActive(a, 77);
    AddCardToDeckViaActive(a, 78);
    AddCardToDeckViaActive(a, 79);
    AddCardToDeckViaActive(a, 80);
    AddCardToDeckViaActive(a, 81);
    AddCardToDeckViaActive(a, 82);
    AddCardToDeckViaActive(a, 83);
    AddCardToDeckViaActive(a, 84);
    AddCardToDeckViaActive(a, 85);
    AddCardToDeckViaActive(a, 86);
    AddCardToDeckViaActive(a, 87);
    AddCardToDeckViaActive(a, 88);
    AddCardToDeckViaActive(a, 89);
    AddCardToDeckViaActive(a, 90);
    AddCardToDeckViaActive(a, 91);
    AddCardToDeckViaActive(a, 92);
    AddCardToDeckViaActive(a, 93);
}

void BuildDebugKingdomKeyDeck(u8 a) {
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 5)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 7)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 4)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 5)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 4)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 3)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 4)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 5)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 6)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 7)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 6)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 5)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 4)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 3)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 4)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 5)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_BLIZZARD, 6)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_BLIZZARD, 5)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_CURE, 7)));
    AddCardToDeckViaActive(a, ObtainCard(CARD_ID(CARD_CURE, 5)));
}

void func_080AB4AC(u8 a) {
    AddCardToDeckViaActive(a, 0);
    AddCardToDeckViaActive(a, 1);
    AddCardToDeckViaActive(a, 2);
    AddCardToDeckViaActive(a, 3);
    AddCardToDeckViaActive(a, 4);
    AddCardToDeckViaActive(a, 5);
    AddCardToDeckViaActive(a, 6);
    AddCardToDeckViaActive(a, 7);
    AddCardToDeckViaActive(a, 8);
    AddCardToDeckViaActive(a, 9);
    AddCardToDeckViaActive(a, 173);
    AddCardToDeckViaActive(a, 176);
    AddCardToDeckViaActive(a, 178);
    AddCardToDeckViaActive(a, 181);
    AddCardToDeckViaActive(a, 184);
    AddCardToDeckViaActive(a, 189);
    AddCardToDeckViaActive(a, 192);
    AddCardToDeckViaActive(a, 195);
    AddCardToDeckViaActive(a, 197);
    AddCardToDeckViaActive(a, 202);
    AddCardToDeckViaActive(a, 204);
    AddCardToDeckViaActive(a, 207);
    AddCardToDeckViaActive(a, 213);
    AddCardToDeckViaActive(a, 216);
    AddCardToDeckViaActive(a, 219);
    AddCardToDeckViaActive(a, 224);
    AddCardToDeckViaActive(a, 225);
    AddCardToDeckViaActive(a, 228);
    AddCardToDeckViaActive(a, 234);
    AddCardToDeckViaActive(a, 235);
    AddCardToDeckViaActive(a, 238);
    AddCardToDeckViaActive(a, 255);
    AddCardToDeckViaActive(a, 257);
    AddCardToDeckViaActive(a, 258);
    AddCardToDeckViaActive(a, 245);
    AddCardToDeckViaActive(a, 247);
    AddCardToDeckViaActive(a, 248);
    AddCardToDeckViaActive(a, 265);
    AddCardToDeckViaActive(a, 267);
    AddCardToDeckViaActive(a, 268);
    AddCardToDeckViaActive(a, 275);
    AddCardToDeckViaActive(a, 277);
    AddCardToDeckViaActive(a, 278);
    AddCardToDeckViaActive(a, 285);
    AddCardToDeckViaActive(a, 287);
    AddCardToDeckViaActive(a, 288);
    AddCardToDeckViaActive(a, 295);
    AddCardToDeckViaActive(a, 297);
    AddCardToDeckViaActive(a, 298);
    AddCardToDeckViaActive(a, 305);
    AddCardToDeckViaActive(a, 307);
    AddCardToDeckViaActive(a, 308);
    AddCardToDeckViaActive(a, 315);
    AddCardToDeckViaActive(a, 317);
    AddCardToDeckViaActive(a, 318);
    AddCardToDeckViaActive(a, 325);
    AddCardToDeckViaActive(a, 327);
    AddCardToDeckViaActive(a, 328);
    AddCardToDeckViaActive(a, 335);
    AddCardToDeckViaActive(a, 337);
    AddCardToDeckViaActive(a, 338);
    AddCardToDeckViaActive(a, 345);
    AddCardToDeckViaActive(a, 347);
    AddCardToDeckViaActive(a, 348);
    AddCardToDeckViaActive(a, 355);
    AddCardToDeckViaActive(a, 357);
    AddCardToDeckViaActive(a, 358);
    AddCardToDeckViaActive(a, 365);
    AddCardToDeckViaActive(a, 367);
    AddCardToDeckViaActive(a, 368);
    AddCardToDeckViaActive(a, 375);
    AddCardToDeckViaActive(a, 377);
    AddCardToDeckViaActive(a, 378);
    AddCardToDeckViaActive(a, 450);
    AddCardToDeckViaActive(a, 459);
    AddCardToDeckViaActive(a, 462);
    AddCardToDeckViaActive(a, 465);
    AddCardToDeckViaActive(a, 468);
    AddCardToDeckViaActive(a, 492);
    AddCardToDeckViaActive(a, 528);
    AddCardToDeckViaActive(a, 529);
    AddCardToDeckViaActive(a, 453);
    AddCardToDeckViaActive(a, 471);
    AddCardToDeckViaActive(a, 474);
    AddCardToDeckViaActive(a, 477);
    AddCardToDeckViaActive(a, 480);
    AddCardToDeckViaActive(a, 486);
    AddCardToDeckViaActive(a, 489);
    AddCardToDeckViaActive(a, 495);
    AddCardToDeckViaActive(a, 501);
    AddCardToDeckViaActive(a, 504);
    AddCardToDeckViaActive(a, 507);
    AddCardToDeckViaActive(a, 510);
    AddCardToDeckViaActive(a, 513);
    AddCardToDeckViaActive(a, 519);
    AddCardToDeckViaActive(a, 522);
}

void ObtainStarterCards(void) {
    ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 7));
    ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 6));
    ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 5));
    ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 5));
    ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 4));
    ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 3));
    ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 4));
    ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 3));
    ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 2));
    ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 2));
    ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 1));
    ObtainCard(CARD_ID(CARD_KINGDOM_KEY, 0));
    ObtainCard(CARD_ID(CARD_BLIZZARD, 5));
    ObtainCard(CARD_ID(CARD_POTION, 6));
    ObtainCard(CARD_ID(CARD_CURE, 7));
}

void FillStarterDeck(void) {
    AddCardToDeckViaActive(0, 0);
    AddCardToDeckViaActive(0, 1);
    AddCardToDeckViaActive(0, 2);
    AddCardToDeckViaActive(0, 3);
    AddCardToDeckViaActive(0, 4);
    AddCardToDeckViaActive(0, 5);
    AddCardToDeckViaActive(0, 6);
    AddCardToDeckViaActive(0, 7);
    AddCardToDeckViaActive(0, 8);
    AddCardToDeckViaActive(0, 9);
    AddCardToDeckViaActive(0, 10);
    AddCardToDeckViaActive(0, 11);
    AddCardToDeckViaActive(0, 12);
    AddCardToDeckViaActive(0, 13);
    AddCardToDeckViaActive(0, 14);
}

void func_080AB964(void) {
}

void func_080AB968(void) {
}

#ifndef VERSION_EU
Mode gModeDeckExchange = {
    "Mode_Deck",
    (ModeInitFunc)Mode_DeckExchange_0,
    Mode_DeckExchange_1,
    Mode_DeckExchange_2,
};
#endif

TaskDesc gTaskDescDarkPoint = {
    "DarkPoint",
    (TaskInitFunc)DarkPoint_0,
    (TaskUpdateFunc)DarkPoint_1,
    (TaskDrawFunc)DarkPoint_2,
    (TaskDestroyFunc)DarkPoint_3,
    sizeof(DarkPointWork),
};

CardDescriptionText* gCardKindDescriptions[98] = {
#if defined(VERSION_EU)
    &gUnkEu_09F5EA0C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090106C0,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042080,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EA20,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090106F4,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090420FC,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EA34,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010728,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042176,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EA48,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010760,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090421EE,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EA5C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010794,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904226A,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EA70,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090107CC,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090422E4,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EA84,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010800,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904235E,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EA98,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010834,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090423D6,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EAAC,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010868,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042452,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EAC0,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_0901089C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090424CC,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EAD4,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090108D0,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904254E,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EAE8,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010904,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090425CA,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EAFC,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010938,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042646,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EB10,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_0901096C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090426C0,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EB24,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090109A0,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904273C,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EB38,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090109D8,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090427BC,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EB4C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010A0C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042840,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EB60,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010A40,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904434A,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EB74,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010A6C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042F40,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EB88,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010A8C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042F6A,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EB9C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010AAC,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042F92,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EBB0,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010ACC,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042FC6,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EBC4,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010AE0,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042FDE,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EBD8,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010B10,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090428BC,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EBEC,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010B2C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043042,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EC00,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010B60,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042912,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EC14,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010B84,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904309C,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EC28,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010BB4,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042984,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EC3C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010BE4,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090429E6,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EC50,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010C0C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042A40,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EC64,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010C38,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090430F0,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EC78,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010C58,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042AA0,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EC8C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010C6C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904315A,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5ECA0,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010CA8,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042AFC,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5ECB4,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010CE4,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090431C6,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5ECC8,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010D20,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043230,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5ECDC,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010D5C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904329A,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5ECF0,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010D98,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042B5C,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5ED04,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010DD4,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043302,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5ED18,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010E10,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904336A,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5ED2C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010E4C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090433DA,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5ED40,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010E6C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043426,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5ED54,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010E88,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043474,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5ED68,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010EBC,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090434E0,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5ED7C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010EF4,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043540,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5ED90,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010F08,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043586,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EDA4,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010F30,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09045146,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EDB8,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010F68,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090435E4,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EDCC,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010F94,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043632,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EDE0,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011018,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043746,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EDF4,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_0901111C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090438CA,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EE08,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011144,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904391C,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EE1C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_0901116C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043976,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EE30,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011194,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090439CE,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EE44,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010FB4,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043678,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EE58,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09010FE4,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090436E0,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EE6C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090111F8,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043A80,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EE80,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090110BC,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043814,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EE94,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011050,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090437B0,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EEA8,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011224,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042C02,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EEBC,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090112D8,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043B7C,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EED0,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_0901108C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042BB4,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EEE4,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011344,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043BDE,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EEF8,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011314,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042C88,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EF0C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011248,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042C32,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EF20,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090112B0,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043B0E,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EF34,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090110F0,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043880,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EF48,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011278,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043AB0,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EF5C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011370,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043C2C,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EF70,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090113D0,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043CE2,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EF84,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_0901139C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043C82,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EF98,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090111BC,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043A1E,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EFAC,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011500,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043F00,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EFC0,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090113F8,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043D42,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EFD4,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011428,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043DA6,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EFE8,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011460,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043DF0,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5EFFC,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011488,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043E56,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F010,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090114C4,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043E9E,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F024,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_0901152C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043F4A,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F038,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011654,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904408C,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F04C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_0901159C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090442E0,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F060,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090116F8,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042D38,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F074,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011810,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042CE4,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F074,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011810,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042CE4,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F088,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011564,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09043FA0,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F09C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090115D8,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042D90,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F0B0,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011638,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044060,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F0C4,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_0901160C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044000,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F0D8,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011684,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090440E6,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F0EC,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090116BC,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044160,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F100,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011770,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090441C2,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F114,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011724,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042DF2,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F128,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011754,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042E4C,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F13C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090117AC,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904422C,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F150,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090117D4,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044282,
#endif
#if defined(VERSION_EU)
    0,
#elif defined(VERSION_JP)
    0,
#elif defined(VERSION_US)
    0,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F164,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011844,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042E7C,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F178,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011870,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09042EEA,
#endif
};

CardDescriptionText* gMapCardDescriptions[26] = {
#if defined(VERSION_EU)
    &gUnkEu_09F5F18C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011B30,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044886,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F1A0,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011B5C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090448CE,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F1B4,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011B84,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044922,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F1C8,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011BB0,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044980,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F1DC,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011BE0,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090449D8,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F1F0,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011C18,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044A44,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F204,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011C44,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044A96,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F218,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011C74,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044AF4,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F22C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011CA4,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044B56,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F240,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011CB8,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044B8E,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F254,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011CE0,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044BEA,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F268,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011D08,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044C48,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F27C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011D3C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044CA2,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F290,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011D70,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044CFE,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F2A4,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011DA4,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044D56,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F2B8,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011DE0,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044DBE,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F2CC,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011E04,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044E06,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F2E0,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011E40,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044E6E,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F2F4,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011E78,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044EC6,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F308,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011EB4,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044F16,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F31C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011EEC,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044F80,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F330,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011F1C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044FD4,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F344,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011F48,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09045026,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F358,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011F78,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904506E,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F36C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011FA8,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090450B6,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F380,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011FD8,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090450FE,
#endif
};

CardDescriptionText* gWorldDescriptions[14] = {
#if defined(VERSION_EU)
    &gUnkEu_09F5F394,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_0901192C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904446C,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F3A8,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090119EC,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090445B4,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F3BC,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090119B4,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904455E,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F3D0,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011984,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044514,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F3E4,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090118D0,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090443B2,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F3F8,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011960,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090444C4,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F40C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090118FC,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_0904440A,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F420,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011A04,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090445FA,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F434,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011AA0,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090446FC,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F448,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_090118A0,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090447B6,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F45C,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011A74,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_090446A8,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F470,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011AD4,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044758,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F484,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011A3C,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044654,
#endif
#if defined(VERSION_EU)
    &gUnkEu_09F5F498,
#elif defined(VERSION_JP)
    gCardDescriptionTextJp_09011B04,
#elif defined(VERSION_US)
    gCardDescriptionTextUs_09044816,
#endif
};
