#include "system_state.h"
#include "msg_api.h"
#include <string.h>
#include "text.h"
#include "monsgage.h"
#include "obj_api.h"
#include "taskpool.h"
#include "key.h"
#include "card.h"
#include "sprites_card.h"
#include "gba/keys.h"
#include "card_deck.h"
#include "jiminy_data.h"
#include "common_text.h"
#include "card_api.h"
#include "card_types.h"
#include "save_types.h"
#include "types.h"
#include "deck_equip_suffix.inc"

void Deck_Equip_0(DeckConfirmWork* w, u8* a) {
    w->textSlotCount = 0;
    w->textSlotCount2 = 0;
    w->textSlotCount3 = 0;
    InitTextSlots(w->textSlots, 80);
    InitTextSlots(w->textSlots2, 80);
    InitTextSlots(w->textSlots3, 80);
    w->textSlotCount = LoadTextSlots(GetDeckName(GetActiveDeckIndex()), w->textSlots);
#ifdef VERSION_JP
    w->textSlotCount2 = LoadTextSlots(common_text_326, w->textSlots2);
#elif defined(VERSION_EU)
    w->textSlotCount2 = LoadTextSlots(eu_0805E924(&gUnkEu_08895A00), w->textSlots2);
#else
    w->textSlotCount2 = LoadTextSlots(common_text_331, w->textSlots2);
#endif
    w->palette = LoadObjPalette(gUnk_09614418, 32);
    w->tiles = LoadObjTiles(gUnk_093F8C8E, 0xC00);
    w->palette2 = LoadObjPalette(gCard00Palette, 32);
#ifdef VERSION_JP
    w->textSlotCount3 = LoadTextSlots((u16*)gUnk_0903C008, w->textSlots3);
    w->x = (233 - GetTextSlotsWidth(w->textSlots, w->textSlotCount) - GetTextSlotsWidth(w->textSlots3, w->textSlotCount3)) / 2;
    w->x3 = w->x + GetTextSlotsWidth(w->textSlots, w->textSlotCount);
    w->y3 = 66;
    w->y = 66;
    w->x2 = (243 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2;
    w->y2 = 82;
#else
    w->x = (240 - GetTextSlotsWidth(w->textSlots, w->textSlotCount)) / 2;
#ifdef VERSION_EU
    w->x2 = (240 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2;

    if (gLanguage - 1 <= 1) {
        w->y = 66;
        w->y2 = 82;
    } else {
        w->y = 82;
        w->y2 = 66;
    }
#else
    w->y = 82;
    w->x2 = (240 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2;
    w->y2 = 66;
#endif
#endif
    w->unk_790 = 0;
    w->unk_7A4 = 0;
    w->active = a;
    *a = 1;
}

void DeckErrorCpInit(DeckConfirmWork* w, u8* a) {
    w->textSlotCount = 0;
    w->textSlotCount2 = 0;
    w->textSlotCount3 = 0;
    InitTextSlots(w->textSlots, 0x50);
    InitTextSlots(w->textSlots2, 0x50);
    InitTextSlots(w->textSlots3, 0x50);
#ifdef VERSION_JP
    w->textSlotCount = 0;
    w->textSlotCount2 = LoadTextSlots(common_text_328, w->textSlots2);
#elif defined(VERSION_EU)
    w->textSlotCount2 = LoadTextSlots(eu_0805E924(&gUnkEu_08895AF4), w->textSlots2);
#else
    w->textSlotCount2 = LoadTextSlots(common_text_009, w->textSlots2);
#endif
    w->palette = LoadObjPalette(gUnk_09614418, 32);
    w->tiles = LoadObjTiles(gUnk_093F8C8E, 0xC00);
    w->palette2 = LoadObjPalette(gCard00Palette, 32);
#ifdef VERSION_JP
    w->x2 = (207 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2;
    w->y2 = 62;
#elif defined(VERSION_EU)
    w->x2 = (240 - eu_0806629C(w->textSlots2, w->textSlotCount2)) / 2;
    w->y2 = 68;
#else
    w->x2 = (240 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2;
    w->y2 = 68;
#endif
    w->unk_790 = 0;
    w->unk_7A4 = 0;
    w->active = a;
    a[0] = 1;
}

void DeckErrorNoAttackCardInit(DeckConfirmWork* w, u8* a) {
    w->textSlotCount = 0;
    w->textSlotCount2 = 0;
    InitTextSlots(w->textSlots, 0x50);
    InitTextSlots(w->textSlots2, 0x50);
    InitTextSlots(w->textSlots3, 0x50);
#ifdef VERSION_JP
    w->textSlotCount = 0;
    w->textSlotCount2 = LoadTextSlots(common_text_329, w->textSlots2);
#elif defined(VERSION_EU)
    w->textSlotCount2 = LoadTextSlots(eu_0805E924(&gUnkEu_08895C30), w->textSlots2);
#else
    w->textSlotCount2 = LoadTextSlots(common_text_334, w->textSlots2);
#endif
    w->palette = LoadObjPalette(gUnk_09614418, 32);
    w->tiles = LoadObjTiles(gUnk_093F8C8E, 0xC00);
    w->palette2 = LoadObjPalette(gCard00Palette, 32);
    w->x = (250 - GetTextSlotsWidth(w->textSlots, w->textSlotCount)) / 2;
    w->y = 64;
#ifdef VERSION_JP
    w->x2 = (219 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2;
#elif defined(VERSION_EU)
    w->x2 = (240 - eu_0806629C(w->textSlots2, w->textSlotCount2)) / 2;
#else
    w->x2 = (240 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2;
#endif
    w->y2 = 62;
    w->unk_790 = 0;
    w->unk_7A4 = 0;
    w->active = a;
    a[0] = 1;
}

void DeckErrorLastAttackCardInit(DeckConfirmWork* w, u8* a) {
    w->textSlotCount = 0;
    w->textSlotCount2 = 0;
    InitTextSlots(w->textSlots, 0x50);
    InitTextSlots(w->textSlots2, 0x50);
    InitTextSlots(w->textSlots3, 0x50);
#ifdef VERSION_JP
    w->textSlotCount = LoadTextSlots(gUnk_0814FBB0, w->textSlots);
    w->textSlotCount2 = LoadTextSlots(gUnk_0814FBBC, w->textSlots2);
#elif defined(VERSION_EU)
    w->textSlotCount2 = LoadTextSlots(eu_0805E924(&gUnkEu_08895CF8), w->textSlots2);
#else
    w->textSlotCount2 = LoadTextSlots(common_text_333, w->textSlots2);
#endif
    w->palette = LoadObjPalette(gUnk_09614418, 32);
    w->tiles = LoadObjTiles(gUnk_093F8C8E, 0xC00);
    w->palette2 = LoadObjPalette(gCard00Palette, 32);
    w->x = (242 - GetTextSlotsWidth(w->textSlots, w->textSlotCount)) / 2;
    w->y = 66;
    w->x2 = (242 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2;
#ifdef VERSION_JP
    w->y2 = 82;
#else
    w->y2 = 68;
#endif
    w->unk_790 = 0;
    w->unk_7A4 = 0;
    w->active = a;
    a[0] = 1;
}

void DeckErrorDeckFullInit(DeckConfirmWork* w, u8* a) {
    w->textSlotCount = 0;
    w->textSlotCount2 = 0;
    InitTextSlots(w->textSlots, 0x50);
    InitTextSlots(w->textSlots2, 0x50);
    InitTextSlots(w->textSlots3, 0x50);
#ifdef VERSION_JP
    w->textSlotCount = LoadTextSlots(gUnk_0814FBB0, w->textSlots);
    w->textSlotCount2 = LoadTextSlots(gUnk_0814FBD4, w->textSlots2);
#elif defined(VERSION_EU)
    w->textSlotCount2 = LoadTextSlots(eu_0805E924(&gUnkEu_08895DBC), w->textSlots2);
#else
    w->textSlotCount2 = LoadTextSlots(common_text_332, w->textSlots2);
#endif
    w->palette = LoadObjPalette(gUnk_09614418, 32);
    w->tiles = LoadObjTiles(gUnk_093F8C8E, 0xC00);
    w->palette2 = LoadObjPalette(gCard00Palette, 32);
    w->x = (243 - GetTextSlotsWidth(w->textSlots, w->textSlotCount)) / 2;
    w->y = 66;
    w->x2 = (243 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2;
#ifdef VERSION_JP
    w->y2 = 82;
#else
    w->y2 = 68;
#endif
    w->unk_7A4 = 0;
    w->unk_790 = 0;
    w->active = a;
    a[0] = 1;
}

s32 DeckConfirmUpdate() {
    if ((GetKeysPressed() & A_BUTTON) || (GetKeysPressed() & START_BUTTON) ||
        (GetKeysPressed() & B_BUTTON)) {
        return 0;
    }

    return 1;
}

void DeckConfirmDraw(DeckConfirmWork* w) {
    DrawTextSlots(w->x, w->y, w->textSlots, w->palette, 1, w->textSlotCount);
    DrawTextSlots(w->x2, w->y2, w->textSlots2, w->palette, 1, w->textSlotCount2);
    DrawTextSlots(w->x3, w->y3, w->textSlots3, w->palette, 1, w->textSlotCount3);
    DrawSprite(120, 80, gUnk_09EF1278[0], w->tiles, w->palette2, 0, 0, 2);
}

void DeckConfirmDestroy(DeckConfirmWork* w) {
    FreeTextSlots(w->textSlots, 80);
    FreeTextSlots(w->textSlots2, 80);
    FreeTextSlots(w->textSlots3, 80);
    ReleaseObjPalette(w->palette);
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette2);
    w->active[0] = 0;
}
#ifdef VERSION_JP
#define DECK_PROMPT_LEFT_DX 30
#define DECK_PROMPT_RIGHT_DX 35
#define DECK_CLEAR_TEXT_Y 66
#else
#define DECK_PROMPT_LEFT_DX 20
#define DECK_PROMPT_RIGHT_DX 20
#define DECK_CLEAR_TEXT_Y 61
#endif
void Deck_Yes_No_0(DeckConfirmWork* w, u8* a) {
    w->textSlotCount = 0;
    w->textSlotCount2 = 0;
    InitTextSlots(w->textSlots, 0x50);
    InitTextSlots(w->textSlots2, 0x50);
    InitTextSlots(w->textSlots3, 0x50);
#ifdef VERSION_EU
    w->textSlotCount = LoadTextSlots(eu_0805E924(&gUnkEu_08890EC0), w->textSlots);
    w->textSlotCount2 = LoadTextSlots(eu_0805E924(&gUnkEu_08890E1C), w->textSlots2);
    w->textSlotCount3 = LoadTextSlots(eu_0805E924(&gUnkEu_08890E44), w->textSlots3);
#else
    w->textSlotCount = LoadTextSlots(gUnk_08159FBC, w->textSlots);
    w->textSlotCount2 = LoadTextSlots(gUnk_08159E10, w->textSlots2);
    w->textSlotCount3 = LoadTextSlots(gUnk_08159E18, w->textSlots3);
#endif
    w->palette = LoadObjPalette(gUnk_09614418, 32);
    w->tiles = LoadObjTiles(gUnk_093F8C8E, 0xC00);
    w->palette2 = LoadObjPalette(gCard00Palette, 32);
    w->x = (240 - GetTextSlotsWidth(w->textSlots, w->textSlotCount)) / 2;
    w->y = 66;
    w->x2 = (240 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2 - DECK_PROMPT_LEFT_DX;
    w->y2 = 88;
    w->x3 = (240 - GetTextSlotsWidth(w->textSlots3, w->textSlotCount3)) / 2 + DECK_PROMPT_RIGHT_DX;
    w->y3 = 88;
    w->unk_790 = 0;
    w->unk_7A4 = 0;
    w->active = a;
    a[0] = 1;
}

s32 DeckConfirmYesNoUpdate() {
    if ((GetKeysPressed() & A_BUTTON) || (GetKeysPressed() & B_BUTTON)) {
        return 0;
    }

    return 1;
}

void Deck_Clear_0(DeckConfirmWork* w, u8* a) {
    w->textSlotCount = 0;
    w->textSlotCount2 = 0;
    InitTextSlots(w->textSlots, 0x50);
    InitTextSlots(w->textSlots2, 0x50);
    InitTextSlots(w->textSlots3, 0x50);
#ifdef VERSION_EU
    w->textSlotCount = LoadTextSlots(eu_0805E924(&gUnkEu_08895E94), w->textSlots);
    w->textSlotCount2 = LoadTextSlots(eu_0805E924(&gUnkEu_08890E1C), w->textSlots2);
    w->textSlotCount3 = LoadTextSlots(eu_0805E924(&gUnkEu_08890E44), w->textSlots3);
#else
    w->textSlotCount = LoadTextSlots(gUnk_0815C1C2, w->textSlots);
    w->textSlotCount2 = LoadTextSlots(gUnk_08159E10, w->textSlots2);
    w->textSlotCount3 = LoadTextSlots(gUnk_08159E18, w->textSlots3);
#endif
    w->palette = LoadObjPalette(gUnk_09614418, 32);
    w->tiles = LoadObjTiles(gUnk_093F8C8E, 0xC00);
    w->palette2 = LoadObjPalette(gCard00Palette, 32);
    w->x = (240 - GetTextSlotsWidth(w->textSlots, w->textSlotCount)) / 2;
    w->x2 = (240 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2 - DECK_PROMPT_LEFT_DX;
    w->y2 = 88;
    w->x3 = (240 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount3)) / 2 + DECK_PROMPT_RIGHT_DX;
    w->y3 = 88;
    w->y = DECK_CLEAR_TEXT_Y;
    w->unk_790 = 0;
    w->unk_7A4 = 0;
    w->active = a;
    a[0] = 1;
}

void WriteCardSaveSlice(SaveLargeSlice* p) {
    s32 i;

    for (i = 0; i < 270; i++) {
        p->mapCardCounts[i] = gMapCardCounts[i];
    }

    for (i = 0; i < 999; i++) {
        p->cards[i] = gCardCollection[i];
    }

    for (i = 0; i < 3; i++) {
        memcpy(&p->decks[i], &gDecks[i], sizeof(Deck));
    }

    p->cardCount = gCardCount;
    p->activeDeck = GetActiveDeckIndex();
}

void ReadCardSaveSlice(SaveLargeSlice* p) {
    u16 i;

    for (i = 0; i < 0x10E; i++) {
        gMapCardCounts[i] = p->mapCardCounts[i];
    }

    for (i = 0; i < 0x3E7; i++) {
        gCardCollection[i] = p->cards[i];
    }

    for (i = 0; i < 3; i++) {
        gDecks[i] = p->decks[i];
    }

    gCardCount = p->cardCount;
    SetActiveDeckIndex(p->activeDeck);
}

void CopyMapCardInventory(SaveSmallSlice* p) {
    s32 i;

    for (i = 0; i <= 0x10D; i++) {
        p->unk_000[i] = gMapCardCounts[i];
    }
}

void RestoreMapCardInventory(SaveSmallSlice* p) {
    u16 i;

    for (i = 0; i <= 0x10D; i++) {
        gMapCardCounts[i] = p->unk_000[i];
    }
}

TaskDesc gTaskDescDeckEquip = {
    "Deck Equip",
    (TaskInitFunc)Deck_Equip_0,
    (TaskUpdateFunc)DeckConfirmUpdate,
    (TaskDrawFunc)DeckConfirmDraw,
    (TaskDestroyFunc)DeckConfirmDestroy,
    sizeof(DeckConfirmWork),
};

TaskDesc gTaskDescDeckYesNo = {
    "Deck_Yes_No",
    (TaskInitFunc)Deck_Yes_No_0,
    (TaskUpdateFunc)DeckConfirmYesNoUpdate,
    (TaskDrawFunc)DeckConfirmDraw,
    (TaskDestroyFunc)DeckConfirmDestroy,
    sizeof(DeckConfirmWork),
};

TaskDesc gTaskDescDeckClear = {
    "Deck_Clear",
    (TaskInitFunc)Deck_Clear_0,
    (TaskUpdateFunc)DeckConfirmYesNoUpdate,
    (TaskDrawFunc)DeckConfirmDraw,
    (TaskDestroyFunc)DeckConfirmDestroy,
    sizeof(DeckConfirmWork),
};

TaskDesc gTaskDescDeckErrorCp = {
    "Deck Error",
    (TaskInitFunc)DeckErrorCpInit,
    (TaskUpdateFunc)DeckConfirmUpdate,
    (TaskDrawFunc)DeckConfirmDraw,
    (TaskDestroyFunc)DeckConfirmDestroy,
    sizeof(DeckConfirmWork),
};

TaskDesc gTaskDescDeckErrorNoAttackCard = {
    "Deck Error",
    (TaskInitFunc)DeckErrorNoAttackCardInit,
    (TaskUpdateFunc)DeckConfirmUpdate,
    (TaskDrawFunc)DeckConfirmDraw,
    (TaskDestroyFunc)DeckConfirmDestroy,
    sizeof(DeckConfirmWork),
};

TaskDesc gTaskDescDeckErrorLastAttackCard = {
    "Deck Error",
    (TaskInitFunc)DeckErrorLastAttackCardInit,
    (TaskUpdateFunc)DeckConfirmUpdate,
    (TaskDrawFunc)DeckConfirmDraw,
    (TaskDestroyFunc)DeckConfirmDestroy,
    sizeof(DeckConfirmWork),
};

TaskDesc gTaskDescDeckErrorDeckFull = {
    "Deck Error",
    (TaskInitFunc)DeckErrorDeckFullInit,
    (TaskUpdateFunc)DeckConfirmUpdate,
    (TaskDrawFunc)DeckConfirmDraw,
    (TaskDestroyFunc)DeckConfirmDestroy,
    sizeof(DeckConfirmWork),
};

#ifdef VERSION_EU
u8* gUnkEu_09F73464[5] = { gUnkEu_090D1DA5, gUnkEu_090D1DA5, gUnkEu_090D1DA5, gUnkEu_090D1DA5, gUnkEu_090D1DA5 };
#endif
