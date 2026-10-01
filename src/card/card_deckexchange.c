#include "macros.h"
#include "registration_data.h"
#include "mode_test_api.h"
#include "m4a_song.h"
#include "game_state.h"
#include "text.h"
#include "fade.h"
#include "obj_api.h"
#include "display.h"
#include "engine_math.h"
#include "listpool.h"
#include "anim.h"
#include "obj.h"
#include "taskpool.h"
#include "key.h"
#include "gba/syscall.h"
#include "malloc.h"
#include "card.h"
#include "sprites_deck_menu.h"
#include "gba/keys.h"
#include "songs.h"
#include "card_api.h"
#include "card_def_data.h"
#include "card_types.h"
#include "gba/defines.h"
#include "mode_battle_data.h"
#include "player_progression_types.h"
#include "types.h"
#include "gba/macro.h"
#include <stddef.h>

#ifndef VERSION_EU
u16 gSioTradeCardId EWRAM_COMMON(4);
#endif

u8 UpdateDeckExchangeFadeOut(DeckExchangeWork* w);
u8 UpdateDeckExchangeGrid(DeckExchangeWork* w, void* a);
u8 UpdateDeckExchangeClose(DeckExchangeWork* w, void* a);
u8 UpdateDeckExchangeBuildList(DeckExchangeWork* w, void* a);
void ClearDeckExchangeCardGrid(DeckExchangeWork* w);
void DrawDeckExchangeCpCost(u8 a);
void LoadDeckExchangeCardDescriptionText(DeckExchangeWork* w, u16 index);
void SetDeckExchangeGridRowCount(DeckExchangeWork* w, s16 n);
u8 UpdateDeckExchangeLoadBgs(DeckExchangeWork* w, void* a);
s32 TakeTradeCard(DeckExchangeWork* w);
void DrawDeckExchangeEquipMarker(u8 a);
void DrawDeckExchangeCardTotals();
u8 UpdateDeckExchangeOpenCollection(DeckExchangeWork* w, void* a);
u16 CountCollectionCards();
u16 CountCardsInDecks();
void ClearCardCollectionSlot(u16* p);
u8 GetActiveDeckIndex();
void CreateDeckExchangeDeckGridCards(DeckExchangeWork* w, u8 kind);
s32 CreateDeckExchangeCollectionGridCards(DeckExchangeWork* w, u8 kind, u8 c);
s32 GetCardIdForKind(s32 a);
void ShowDeckExchangeCardPreview(DeckExchangeWork* w);
void ReleaseDeckExchangeCardPreview(DeckExchangeWork* w);
void DrawDeckExchangeValueCpCost(DeckExchangeWork* w);
s32 MoveDeckExchangeValueCursor(DeckExchangeWork* w, u16 key);
void FreeDeckExchangeCollectionEntries(DeckExchangeWork* w);
s32 CheckDeckExchangeCpCost(DeckExchangeWork* w);
u8 CheckDeckExchangeHasAttackCard(DeckExchangeWork* w);
void ResetDeckExchangeGridScroll(DeckExchangeWork* w);
u8 IsDeckExchangeCardAtCursor(DeckExchangeWork* w);
u8 IsDeckExchangeCardAt(DeckExchangeWork* w, s16 x, s16 y);
void UpdateDeckExchangeGridScrollBar(DeckExchangeWork* w);
#ifndef VERSION_EU
static const s16 sDeckExchangeTabPointerX[3] = { 116, 116, 116 };

static const s16 sDeckExchangeTabPointerY[3] = { 56, 104, 148 };

const s16 gUnk_09041F10[5] = { 12, 28, 42, 56, 70 };

static const s16 sDeckExchangeFilterTabX[6] = { 172, 172, 188, 202, 216, 230 };

const s16 gUnk_09041F26[5] = { 64, 82, 100, 118, 136 };

static const s16 sDeckExchangeValueGridX[2] = { 80, 128 };

static const s16 sDeckExchangeValueGridY[5] = { 80, 88, 96, 104, 112 };

static const u16 sUnk_09041F3E[4] = { 45, 93, 141, 30 };

void deckexchange_0(DeckExchangeWork* w, void* a) {
    u16 n;

    CpuFill32(0, w, sizeof(DeckExchangeWork));
    w->tiles7 = NULL;
    w->tiles4 = NULL;
    w->tiles5 = NULL;
    w->tiles6 = NULL;
    w->palette2 = NULL;
    w->palette3 = NULL;
    w->tiles8 = NULL;
    w->palette6 = NULL;
    w->palette7 = NULL;
    w->palette4 = NULL;
    w->unk_4C0 = NULL;
    w->unk_4C4 = NULL;
    w->entries = NULL;
    w->resultOut = a;
    SetBgMode0();
    SetBackdropColor(0, 0, 0);
    SetupBg(0, 3, 31, 0);
    SetupBg(1, 2, 23, 0);
    SetupBg(2, 1, 15, 0);
    SetupBg(3, 0, 30, 0);
    SetBgPriority(0, 0);
    SetBgPriority(1, 1);
    SetBgPriority(2, 2);
    FadeStartIn(FADE_MODE_BLACK, 16);
    ListPoolInit(&w->pool);
    TaskPoolInit(&w->tasks, 99);
    TaskPoolInit(&w->tasks2, 1);
    w->deckIndex = GetActiveDeckIndex();
    CreateDeckExchangeDeckGridCards(w, 0);
    w->tiles = AllocObjTiles(0x120, NULL);
    SetObjTileSource(w->tiles, gUnk_090A4664);
    AnimInit(&w->anim, gUnk_09EEB03C, gUnk_09EEB008);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    w->x2 = sDeckExchangeTabPointerX[0] << 8;
    w->y2 = sDeckExchangeTabPointerY[0] << 8;
    w->handFlags = 0;
    w->tiles3 = LoadObjTiles(gUnk_090A44C4, 32);
    w->palette = LoadObjPalette(gUnk_09614418, 32);
    w->tiles2 = AllocObjTiles(0x280, NULL);
    SetDeckExchangeFrameCursor(w, 0);
    w->palette4 = LoadObjPalette(gUnk_09614438, 32);
    w->step = 0;
    w->cursorCol = 0;
    w->cursorRow = 0;
    w->unk_6F2 = 0;
    w->unk_6F3 = 0;
    w->timer = 4;
    w->unk_707 = 0;
    w->mode = 0;
    w->view = 0;
    w->deckAttackCount = CountActiveDeckCardsOfCategory(0);
    w->deckMagicCount = CountActiveDeckCardsOfCategory(1);
    w->deckItemCount = CountActiveDeckCardsOfCategory(2);
    w->deckEnemyCount = CountActiveDeckCardsOfCategory(3);
    w->categoryFilter = 0;
    w->entryCount = 0;
    w->popupActive = 0;
    w->exitRequested = 0;
    w->unk_711 = 16;
    w->unk_712 = 16;
    w->unk_6A4 = 0;
    w->unk_6AC = -0x800;
    w->unk_6A8 = 0;
    w->unk_6B0 = 0xA000;
    w->unk_6B4 = -0x8000;
    w->holding = 0;
    w->x7 = 8;
    w->y7 = 113;
    w->textSlotCount5 = 0;
    w->unk_6C4 = 79;
    n = sUnk_09041F3E[w->deckIndex];
    w->unk_6C6 = n;
    w->unk_6C8 = 225;
    n = sUnk_09041F3E[w->deckIndex];
    w->unk_6CA = n;
    w->unk_70F = 0;
    w->unk_713 = 0;
    w->textSlotCount = 0;
    w->textSlotCount2 = 0;
    w->textSlotCount3 = 0;
    w->textSlotCount4 = 0;
    InitTextSlots(w->textSlots, 8);
    InitTextSlots(w->textSlots2, 8);
    InitTextSlots(w->textSlots3, 8);
    InitTextSlots(w->textSlots4, 30);
    InitTextSlots(w->textSlots5, 90);
}

u8 deckexchange_1(DeckExchangeWork* w, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 16);

    switch (w->step) {
    case 0:
        RequestDma3Clear(GetBgCharBase(0), 0x1000);
        break;
    case 1:
        RequestDma3Clear(GetBgCharBase(0) + 0x1000, 0x1000);
        break;
    case 2:
        RequestDma3Clear(GetBgCharBase(0) + 0x2000, 0x1000);
        break;
    case 3:
        RequestDma3Clear(GetBgCharBase(0) + 0x3000, 0x1000);
        break;
    case 4:
        RequestDma3Clear(GetBgCharBase(1), 0x1000);
        break;
    case 5:
        RequestDma3Clear(GetBgCharBase(1) + 0x1000, 0x1000);
        break;
    case 6:
        RequestDma3Clear(GetBgCharBase(1) + 0x2000, 0x1000);
        break;
    case 7:
        RequestDma3Clear(GetBgCharBase(1) + 0x3000, 0x1000);
        break;
    case 8:
        RequestDma3Clear(GetBgCharBase(2), 0x1000);
        break;
    case 9:
        RequestDma3Clear(GetBgCharBase(2) + 0x1000, 0x1000);
        break;
    case 10:
        RequestDma3Clear(GetBgCharBase(2) + 0x2000, 0x1000);
        break;
    case 11:
        RequestDma3Clear(GetBgCharBase(2) + 0x3000, 0x1000);
        break;
    case 12:
        RequestDma3Clear(GetBgCharBase(3), 0x1000);
        break;
    case 13:
        RequestDma3Clear(GetBgCharBase(3) + 0x1000, 0x1000);
        break;
    case 14:
        RequestDma3Clear(GetBgCharBase(3) + 0x2000, 0x1000);
        break;
    case 15:
        RequestDma3Clear(GetBgCharBase(3) + 0x3000, 0x1000);
        w->step = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeLoadBgs);
        return 1;
    }

    w->step++;
}

u8 UpdateDeckExchangeLoadBgs(DeckExchangeWork* w, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 16);

    switch (w->step) {
    case 0:
        LoadBgTiles(3, gUnk_09402F78, 0x2000);
        break;
    case 1:
        RequestDma3Copy(&gUnk_09402F78[0x2000],
                        (u8*)GetBgCharBase(3) + 0x2000, 0x2000);
        break;
    case 2:
        LoadBgPalette(3, gUnk_09614118, 0x1E0);
        break;
    case 3:
        LoadBgTiles(0, gUnk_09406F78, 0xC00);
        break;
    case 4:
        LoadBgMap(0, gUnk_08125E24, 0x800);
        break;
    case 5:
        LoadBgTiles(1, &gUnk_09406F78[0xC00], 0x2000);
        break;
    case 6:
        RequestDma3Copy(&gUnk_09406F78[0x2C00],
                        (u8*)GetBgCharBase(1) + 0x2000, 0x1E20);
        break;
    case 7:
        LoadBgMap(1, gUnk_08125E24, 0x800);
        break;
    case 8:
        LoadBgTiles(2, &gUnk_09406F78[0x4A20], 0x2000);
        break;
    case 9:
        RequestDma3Copy(&gUnk_09406F78[0x6A20],
                        (u8*)GetBgCharBase(2) + 0x2000, 0x1E20);
        break;
    case 10:
        LoadBgMap(2, gUnk_08125E24, 0x800);
        break;
    case 12:
        w->step = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeLoadDeckInfo);
        return 1;
    }

    w->step++;
    SetBgScroll(0, (u16)-88, (u16)-16);
    SetBgScroll(1, (u16)-88, (u16)-64);
    SetBgScroll(2, (u16)-88, (u16)-112);
    return 1;
}

u8 UpdateDeckExchangeLoadDeckInfo(DeckExchangeWork* w, void* a) {
    s32 v;

    FadeStartIn(FADE_MODE_BLACK, 16);

    switch (w->step) {
    case 1:
        LoadBgMap(0, &gUnk_095192B8[0x400], 0x180);
        break;
    case 2:
        LoadBgMap(1, &gUnk_095192B8[0x800], 0x180);
        break;
    case 3:
        LoadBgMap(2, &gUnk_095192B8[0xC00], 0x180);
        break;
    case 4:
        DrawDeckCategoryCount(w->deckAttackCount, 0);
        break;
    case 5:
        DrawDeckCategoryCount(w->deckMagicCount, 1);
        break;
    case 6:
        DrawDeckCategoryCount(w->deckItemCount, 2);
        break;
    case 7:
        DrawDeckCategoryCount(w->deckEnemyCount, 3);
        break;
    case 8:
        HighlightDeckExchangeDeckTab(w, w->deckIndex);
        break;
    case 9:
        DrawDeckExchangeDeckCardCount(0);
        DrawDeckExchangeDeckCardCount(1);
        DrawDeckExchangeDeckCardCount(2);
        break;
    case 10:
        DrawDeckExchangeEquipMarker(GetActiveDeckIndex());
        DrawDeckExchangeCardTotals();
        w->x = 0x4800;
        w->y = 0x2800;
        v = w->deckIndex;
        w->cursorRow = v;
        ApproachValue(&w->x2, sDeckExchangeTabPointerX[w->cursorCol] << 8, w->timer);
        ApproachValue(&w->y2, sDeckExchangeTabPointerY[w->cursorRow] << 8, w->timer);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeOpenCollection);
        w->view = 1;
        SetDeckExchangeHandAnim(w);
        LoadDeckExchangeDeckNameTexts(w);
        break;
    }

    w->step++;
    return 1;
}

u8 UpdateDeckExchangeValueSelect(DeckExchangeWork* w, void* a) {
    s8 n;
    s32 m;

    if (w->popupActive != 0) {
        TaskPoolUpdate(&w->tasks);
        TaskPoolUpdate(&w->tasks2);

        if (GetKeysPressed() & START_BUTTON) {
            w->exitRequested = 1;
        }

        return 1;
    }

    if (w->exitRequested != 0) {
        if ((u8)CheckDeckExchangeCpCost(w) != 0 && CheckDeckExchangeHasAttackCard(w) != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        w->exitRequested = 0;
    }

    w->gfx = AnimUpdate(&w->anim);
    w->gfx2 = AnimUpdate(&w->anim2);

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
        if (w->cursorCol > 0) {
            w->cursorCol--;
            w->timer = 4;

            if ((u8)MoveDeckExchangeValueCursor(w, 32) != 0) {
                m4aSongNumStart(SONG_SYS_CLICK);
            }
        }

        DrawDeckExchangeValueCpCost(w);
        break;
    case DPAD_RIGHT:
        if (w->cursorCol <= 0) {
            w->cursorCol++;
            w->timer = 4;

            if ((u8)MoveDeckExchangeValueCursor(w, 16) != 0) {
                m4aSongNumStart(SONG_SYS_CLICK);
            }
        }

        DrawDeckExchangeValueCpCost(w);
        break;
    case DPAD_UP:
        n = w->cursorRow;

        if (w->cursorRow > 0) {
            w->cursorRow--;
        }

        w->timer = 4;
        MoveDeckExchangeValueCursor(w, 64);

        if (n != w->cursorRow) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        DrawDeckExchangeValueCpCost(w);
        break;
    case DPAD_DOWN:
        n = w->cursorRow;

        if (w->cursorRow <= 3) {
            w->cursorRow++;
        }

        w->timer = 4;
        MoveDeckExchangeValueCursor(w, 128);

        if (n != w->cursorRow) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        DrawDeckExchangeValueCpCost(w);
        break;
    }

    switch (GetKeysPressed()) {
    case B_BUTTON:
        SetDeckExchangeFrameCursor(w, 0);
        m = (s8)w->savedCol;
        w->cursorCol = m;
        m = (s8)w->savedRow;
        w->cursorRow = m;
        w->x2 = gCollectionGridColumnX[w->cursorCol] << 8;
        w->y2 = gCollectionGridRowY[w->cursorRow] << 8;
        ShowDeckExchangeCardPreview(w);
        w->view = 9;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeGrid);
        return 1;
    case A_BUTTON:
        if ((u8)TakeTradeCard(w) == 0) {
            return 1;
        }

        DrawDeckExchangeCardTotals();
        CountCardsNotInDeckByCategory(3, w->collectionCategoryCounts);
        DrawCollectionCategoryCount(w->collectionCategoryCounts[0], 0);
        DrawCollectionCategoryCount(w->collectionCategoryCounts[1], 1);
        DrawCollectionCategoryCount(w->collectionCategoryCounts[2], 2);
        DrawCollectionCategoryCount(w->collectionCategoryCounts[3], 3);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeClose);
        DrawDeckExchangeValueCpCost(w);
        w->timer = 4;
        break;
    case START_BUTTON:
        if ((u8)CheckDeckExchangeCpCost(w) != 0 && CheckDeckExchangeHasAttackCard(w) != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
        }

        return 1;
    }

    if (w->timer != 0) {
        ApproachValue(&w->x2, sDeckExchangeValueGridX[w->cursorCol] << 8, w->timer);
        ApproachValue(&w->y2, (sDeckExchangeValueGridY[w->cursorRow] - 16) << 8, w->timer);
        w->timer--;
    }

    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    return 1;
}

u8 UpdateDeckExchangeCollectionFilter(DeckExchangeWork* w, void* a) {
    s32 i;

    w->gfx = AnimUpdate(&w->anim);

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
        if (w->cursorCol > 1) {
            w->cursorCol--;
            w->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICK);
            w->categoryFilter = w->cursorCol;
            DrawDeckExchangeCollectionFilterTab(w->categoryFilter, w->mode);
            ClearDeckExchangeCardGrid(w);
            w->gridEntryCount = CreateDeckExchangeCollectionGridCards(w, w->categoryFilter, 1);
        }

        for (i = 0; i < 10; i++) {
            DrawValueCount(0, i);
        }

        break;
    case DPAD_RIGHT:
        if (w->cursorCol < 5) {
            w->cursorCol++;
            w->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICK);
            w->categoryFilter = w->cursorCol;
            DrawDeckExchangeCollectionFilterTab(w->categoryFilter, w->mode);
            ClearDeckExchangeCardGrid(w);
            w->gridEntryCount = CreateDeckExchangeCollectionGridCards(w, w->categoryFilter, 1);
        }

        for (i = 0; i < 10; i++) {
            DrawValueCount(0, i);
        }

        break;
    case DPAD_DOWN:
        if (w->gridEntryCount != 0) {
            w->cursorCol = 0;
            w->cursorRow = 0;
            w->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            ShowDeckExchangeCardPreview(w);
            w->view = 9;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeGrid);
            w->x = 0xA000;
            w->y = 0x2800;
            w->scrollRowEnd = 4;
            return 1;
        }

        m4aSongNumStart(SONG_SYS_BEEP);
        break;
    case B_BUTTON:
        if (w->gridEntryCount != 0) {
            w->cursorCol = 0;
            w->cursorRow = 0;
            w->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            ShowDeckExchangeCardPreview(w);
            w->view = 9;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeGrid);
            w->x = 0xA000;
            w->y = 0x2800;
            w->scrollRowEnd = 4;
            return 1;
        }

        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeClose);
        m4aSongNumStart(SONG_SYS_CLOSE);
        return 1;
    case START_BUTTON:
        if ((u8)CheckDeckExchangeCpCost(w) != 0 && CheckDeckExchangeHasAttackCard(w) != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
        }

        return 1;
    }

    if (w->timer != 0) {
        ApproachValue(&w->x2, sDeckExchangeFilterTabX[w->cursorCol] << 8, w->timer);
        ApproachValue(&w->y2, 0x1E00, w->timer);
        w->timer--;
    }

    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    return 1;
}

u8 UpdateDeckExchangeOpenCollection(DeckExchangeWork* w, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 4);
    SetupBg(3, 0, 30, 0);
    SetupBg(2, 0, 15, 0);
    SetupBg(1, 0, 23, 0);
    SetupBg(0, 0, 31, 0);
    SetBgScroll(0, 0, 0);
    SetBgScroll(1, 0, 0);
    SetBgScroll(2, 0, 16);
    LoadBgMap(3, gUnk_09515AB8, 0x800);
    LoadBgMap(2, gUnk_095182B8, 0x800);
    LoadBgMap(1, gUnk_09514AB8, 0x800);
    DisableBg(0);
    CountCardsNotInDeckByCategory(3, w->collectionCategoryCounts);
    DrawCollectionCategoryCount(w->collectionCategoryCounts[0], 0);
    DrawCollectionCategoryCount(w->collectionCategoryCounts[1], 1);
    DrawCollectionCategoryCount(w->collectionCategoryCounts[2], 2);
    DrawCollectionCategoryCount(w->collectionCategoryCounts[3], 3);
    w->view = 9;
    SetDeckExchangeFrameCursor(w, 0);
    ClearDeckExchangeCardGrid(w);
    w->step = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeBuildList);
    w->unk_6C4 = 0xFFFE;
    w->unk_6C6 = 142;
    w->unk_6C8 = 142;
    w->unk_6CA = 142;
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    return 1;
}

u8 UpdateDeckExchangeBuildList(DeckExchangeWork* w, void* a) {
    u16 i;
    u16 j;
    u16 n;

    FadeStartIn(FADE_MODE_BLACK, 16);

    switch (w->step) {
    case 0:
        w->entryCount = 286;
        w->kindEntries = EwramAlloc(w->entryCount * sizeof(CardKindEntry));
        CpuFill32(0, w->kindEntries, w->entryCount * sizeof(CardKindEntry));
        break;
    case 1:
        CountCardsNotInDeckByKind(w->kindEntries, w->deckIndex, 0, w->entryCount, w->unk_4F4);
        break;
    case 2:
        w->entryCount = ListCardsNotInDeckByKind(w->kindEntries, w->deckIndex, 0, w->entryCount, w->unk_4F4);
        break;
    case 3:
        w->entries = EwramAlloc(w->entryCount * sizeof(CardKindEntry));

        for (i = 0, n = 0; i < 286; i++) {
            if (w->kindEntries[i].count != 0) {
                w->entries[n] = w->kindEntries[i];
                w->entries[n].indices = EwramAlloc(w->kindEntries[i].indexCount * 2);

                for (j = 0; j < w->kindEntries[i].indexCount; j++) {
                    w->entries[n].indices[j] = w->kindEntries[i].indices[j];
                }

                n++;
            }
        }

        break;
    case 4:
        for (i = 0; i < 286; i++) {
            if (w->kindEntries[i].count != 0) {
                EwramFree(w->kindEntries[i].indices);
            }
        }

        EwramFree(w->kindEntries);
        break;
    case 5:
        w->categoryFilter = 5;
        w->gridEntryCount = CreateDeckExchangeCollectionGridCards(w, 5, 1);
        SetDeckExchangeHandAnim(w);
        w->x2 = gCollectionGridColumnX[0] << 8;
        w->y2 = gCollectionGridRowY[0] << 8;
        w->mode = 2;
        w->cursorCol = 0;
        w->cursorRow = 0;
        ShowDeckExchangeCardPreview(w);

        if (w->gridEntryCount != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeGrid);
        } else {
            w->cursorCol = w->categoryFilter;
            w->timer = 4;
            w->view = 10;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeCollectionFilter);
        }

        break;
    }

    w->step++;
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    return 1;
}

u8 UpdateDeckExchangeGrid(DeckExchangeWork* w, void* a) {
    s32 i;

    w->gfx = AnimUpdate(&w->anim);
    w->gfx2 = AnimUpdate(&w->anim2);

    if (w->popupActive != 0) {
        TaskPoolUpdate(&w->tasks);
        TaskPoolUpdate(&w->tasks2);

        if (GetKeysPressed() & START_BUTTON) {
            w->exitRequested = 1;
        }

        return 1;
    }

    if (w->exitRequested != 0) {
        if ((u8)CheckDeckExchangeCpCost(w) != 0 && CheckDeckExchangeHasAttackCard(w) != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        w->exitRequested = 0;
    }

    switch (GetKeysRepeat()) {
    case DPAD_UP:
        if (w->cursorRow > 0) {
            if (IsDeckExchangeCardAt(w, w->cursorCol, w->cursorRow - 1) != 0) {
                w->cursorRow--;
                w->timer = 4;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            }
        } else {
            if (ScrollDeckExchangeGridUp(w) == 0) {
                UpdateDeckExchangeGridScrollBar(w);
                w->cursorCol = w->categoryFilter;
                w->timer = 4;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
                w->view = 10;

                for (i = 0; i < 10; i++) {
                    DrawValueCount(0, i);
                }

                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeCollectionFilter);
                return 1;
            }

            UpdateDeckExchangeGridScrollBar(w);
        }

        ShowDeckExchangeCardPreview(w);
        break;
    case DPAD_DOWN:
        if (w->cursorRow < 3) {
            if (IsDeckExchangeCardAt(w, w->cursorCol, w->cursorRow + 1) != 0) {
                w->cursorRow++;
                w->timer = 4;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            }
        } else if (IsDeckExchangeCardAt(w, w->cursorCol, w->cursorRow + 1) != 0) {
            ScrollDeckExchangeGridDown(w);
            UpdateDeckExchangeGridScrollBar(w);
        }

        ShowDeckExchangeCardPreview(w);
        break;
    case DPAD_LEFT:
        if (w->cursorCol > 0 && IsDeckExchangeCardAt(w, w->cursorCol - 1, w->cursorRow) != 0) {
            w->cursorCol--;
            w->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        ShowDeckExchangeCardPreview(w);
        break;
    case DPAD_RIGHT:
        if (w->cursorCol > 1) {
            w->timer = 4;
            return 1;
        }

        if (IsDeckExchangeCardAt(w, w->cursorCol + 1, w->cursorRow) != 0) {
            w->cursorCol++;
            w->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        ShowDeckExchangeCardPreview(w);
        break;
    }

    switch (GetKeysPressed()) {
    case A_BUTTON:
        if (IsDeckExchangeCardAtCursor(w) != 0) {
            w->savedCol = w->cursorCol;
            w->savedRow = w->cursorRow;
            w->cursorCol = 0;
            w->cursorRow = 0;
            SetDeckExchangeFrameCursor(w, 1);
            w->view = 11;
            m4aSongNumStart(SONG_SYS_KETTEI);

            if ((u8)MoveDeckExchangeValueCursor(w, 0) != 0) {
                DrawDeckExchangeValueCpCost(w);
                w->x2 = sDeckExchangeValueGridX[w->cursorCol] << 8;
                w->y2 = (sDeckExchangeValueGridY[w->cursorRow] - 16) << 8;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeValueSelect);
                return 1;
            }

            w->cursorCol = (s8)w->savedCol;
            w->cursorRow = (s8)w->savedRow;
            SetDeckExchangeFrameCursor(w, 0);
            w->view = 9;
            m4aSongNumStart(SONG_SYS_BEEP);
            return 1;
        }

        m4aSongNumStart(SONG_SYS_BEEP);
        return 1;
    case B_BUTTON:
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeClose);
        m4aSongNumStart(SONG_SYS_CLOSE);
        return 1;
    case START_BUTTON:
        if ((u8)CheckDeckExchangeCpCost(w) != 0 && CheckDeckExchangeHasAttackCard(w) != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
        }

        return 1;
    }

    if (GetKeysPressed() & SELECT_BUTTON) {
        ResetDeckExchangeGridScroll(w);
        w->cursorCol = w->categoryFilter;
        w->timer = 4;
        w->x = 0xA000;
        w->y = 0x2800;
        w->scrollRowEnd = 4;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
        w->view = 10;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeCollectionFilter);
        return 1;
    }

    if (w->timer != 0) {
        ApproachValue(&w->x2, gCollectionGridColumnX[w->cursorCol] << 8, w->timer);
        ApproachValue(&w->y2, gCollectionGridRowY[w->cursorRow] << 8, w->timer);
        w->timer--;
    }

    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    return 1;
}

u8 UpdateDeckExchangeClose(DeckExchangeWork* w, void* a) {
    FadeStartOut(FADE_MODE_BLACK, 16);
    w->categoryFilter = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeFadeOut);
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    return 1;
}

u8 UpdateDeckExchangeFadeOut(DeckExchangeWork* w) {
    if (FadeIsActive() == 0) {
        ClearDeckExchangeCardGrid(w);
        return 0;
    }

    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    return 1;
}

void DrawDeckExchangeDeckNames(DeckExchangeWork* w, u8 b) {
    if (b == 0) {
        switch (w->deckIndex) {
        case 0:
            DrawTextSlots(w->x4, w->y4, w->textSlots, w->palette, 20, w->textSlotCount);
            DrawTextSlots(w->x5, w->y5, w->textSlots2, w->palette4, 20, w->textSlotCount2);
            DrawTextSlots(w->x6, w->y6, w->textSlots3, w->palette4, 20, w->textSlotCount3);
            break;
        case 1:
            DrawTextSlots(w->x4, w->y4, w->textSlots, w->palette4, 20, w->textSlotCount);
            DrawTextSlots(w->x5, w->y5, w->textSlots2, w->palette, 20, w->textSlotCount2);
            DrawTextSlots(w->x6, w->y6, w->textSlots3, w->palette4, 20, w->textSlotCount3);
            break;
        case 2:
            DrawTextSlots(w->x4, w->y4, w->textSlots, w->palette4, 20, w->textSlotCount);
            DrawTextSlots(w->x5, w->y5, w->textSlots2, w->palette4, 20, w->textSlotCount2);
            DrawTextSlots(w->x6, w->y6, w->textSlots3, w->palette, 20, w->textSlotCount3);
            break;
        }
    } else {
        switch (w->deckIndex) {
        case 0:
            DrawTextSlots(w->x4, w->y4, w->textSlots, w->palette, 20, w->textSlotCount);
            break;
        case 1:
            DrawTextSlots(w->x5, w->y5, w->textSlots2, w->palette, 20, w->textSlotCount2);
            break;
        case 2:
            DrawTextSlots(w->x6, w->y6, w->textSlots3, w->palette, 20, w->textSlotCount3);
            break;
        }
    }
}

void DrawDeckExchangeCardDescription(DeckExchangeWork* w) {
    DrawTextSlots(w->x7, w->y7, w->textSlots5, w->palette, 20, w->textSlotCount5);
}

void deckexchange_2(DeckExchangeWork* w) {
    if (w->popupActive == 0) {
        DrawSprite((w->x2 >> 8) - 16, (w->y2 >> 8) - 30, w->gfx, w->tiles, w->palette, NULL, w->handFlags, 3);
    }

    DrawSprite(w->x >> 8, w->y >> 8, gUnk_09EEB000, w->tiles3, w->palette, NULL, SPRITE_PRIORITY(2), 10);

    switch (w->view) {
    case 0:
        if (w->holding != 0) {
            DrawSprite((w->x3 >> 8) - 16, (w->y3 >> 8) - 20, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);
        }

        DrawSprite((w->x2 >> 8) - 16, (w->y2 >> 8) - 20, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);
    case 1:
    case 2:
    case 3:
        DrawDeckExchangeDeckNames(w, 0);
        break;
    case 4:
        DrawDeckExchangeDeckNames(w, 1);
        DrawSprite((w->x2 >> 8) - 16, (w->y2 >> 8) - 20, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);

        if (w->tiles4 != NULL) {
            if (w->popupActive == 0) {
                DrawSprite((w->x2 >> 8) - 16, (w->y2 >> 8) - 20, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);
            }

            DrawSprite(24, 82, w->gfx3, w->tiles4, w->palette2, NULL, 0, 20);
            DrawSprite(24, 82, w->gfx4, w->tiles5, w->palette3, NULL, 0, 21);
            DrawTextSlots(10, 116, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }

        break;
    case 7:
        DrawDeckExchangeDeckNames(w, 1);
        DrawSprite((w->x2 >> 8) - 16, (w->y2 >> 8) - 20, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);

        if (w->tiles4 != NULL) {
            DrawSprite(164, 82, w->gfx3, w->tiles4, w->palette2, NULL, 0, 20);
            DrawSprite(164, 82, w->gfx4, w->tiles5, w->palette3, NULL, 0, 21);

            if (w->tiles6 != NULL) {
                DrawSprite(164, 82, w->gfx5, w->tiles6, w->palette2, NULL, 0, 19);
            }

            DrawTextSlots(100, 116, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }

        break;
    case 5:
        DrawSprite((w->x2 >> 8) - 26, (w->y2 >> 8) - 13, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);
        DrawDeckExchangeDeckNames(w, 1);

        if (w->tiles4 != NULL) {
            DrawSprite(24, 82, w->gfx3, w->tiles4, w->palette2, NULL, 0, 20);
            DrawSprite(24, 82, w->gfx4, w->tiles5, w->palette3, NULL, 0, 21);
            DrawTextSlots(10, 116, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }

        break;
    case 6:
        DrawDeckExchangeDeckNames(w, 1);

        if (w->tiles4 != NULL) {
            DrawSprite(24, 82, w->gfx3, w->tiles4, w->palette2, NULL, 0, 20);
            DrawSprite(24, 82, w->gfx4, w->tiles5, w->palette3, NULL, 0, 21);
            DrawTextSlots(10, 116, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }

        break;
    case 8:
        DrawDeckExchangeDeckNames(w, 1);

        if (w->tiles4 != NULL) {
            DrawSprite(164, 82, w->gfx3, w->tiles4, w->palette2, NULL, 0, 20);
            DrawSprite(164, 82, w->gfx4, w->tiles5, w->palette3, NULL, 0, 21);

            if (w->tiles6 != NULL) {
                DrawSprite(164, 82, w->gfx5, w->tiles6, w->palette2, NULL, 0, 19);
            }

            DrawTextSlots(100, 116, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }

        break;
    case 9:
        DrawSprite((w->x2 >> 8) - 16, (w->y2 >> 8) - 20, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);
        DrawDeckExchangeCardDescription(w);

        if (w->tiles4 != NULL) {
            DrawSprite(24, 66, w->gfx3, w->tiles4, w->palette2, NULL, 0, 20);
            DrawSprite(24, 66, w->gfx4, w->tiles5, w->palette3, NULL, 0, 21);
            DrawTextSlots(10, 100, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }

        break;
    case 11:
        DrawSprite((w->x2 >> 8) - 26, (w->y2 >> 8) - 13, w->gfx2, w->tiles2, w->palette4, NULL, 0, 8);
        DrawDeckExchangeCardDescription(w);

        if (w->tiles4 != NULL) {
            DrawSprite(24, 66, w->gfx3, w->tiles4, w->palette2, NULL, 0, 20);
            DrawSprite(24, 66, w->gfx4, w->tiles5, w->palette3, NULL, 0, 21);
            DrawTextSlots(10, 100, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }

        break;
    }

    TaskPoolDraw(&w->tasks);
    TaskPoolDraw(&w->tasks2);
}

void deckexchange_3(DeckExchangeWork* w) {
    ObjPalette** p;

    if (w->tiles8 != NULL) {
        ReleaseObjTiles(w->tiles8);
    }

    if (w->palette5 != NULL) {
        ReleaseObjPalette(w->palette5);
    }

    if (w->tiles9 != NULL) {
        ReleaseObjTiles(w->tiles9);
    }

    if (w->palette6 != NULL) {
        ReleaseObjPalette(w->palette6);
    }

    if (w->palette7 != NULL) {
        ReleaseObjPalette(w->palette7);
    }

    p = &w->palette4;

    if (*p != NULL) {
        ReleaseObjPalette(*p);
    }

    ReleaseDeckExchangeCardPreview(w);
    ReleaseObjTiles(w->tiles);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjTiles(w->tiles3);
    ReleaseObjPalette(w->palette);
    FreeTextSlots(w->textSlots, 8);
    FreeTextSlots(w->textSlots2, 8);
    FreeTextSlots(w->textSlots3, 8);
    FreeTextSlots(w->textSlots4, 30);
    FreeTextSlots(w->textSlots5, 90);
    ReleaseObjPalette(*p);
    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->tasks2);
    FreeDeckExchangeCollectionEntries(w);
    *w->resultOut = 6;
}

void CreateDeckExchangeDeckGridCards(DeckExchangeWork* w, u8 kind) {
    DeckCard2Args args;
    u16* cards;
    u8 i;
    s8 x;
    s8 y;

    cards = GetDeck(w->deckIndex)->cards;
    x = 0;
    y = 0;

    for (i = 0; i < DECK_SIZE; i++) {
        if (cards[i] != 0xFFFF) {
            if (kind == 0) {
                args.pool = &w->pool;
                args.cardId = gCardCollection[cards[i]] & 0x8FFF;
                args.col = x;
                args.row = y;
                args.panel = 0;
                args.slot = &cards[i];
                TaskCreate(&w->tasks, &gTaskDescDeckCard2, &args);
                x++;
            } else if (gCardDefs[gCardCollection[cards[i]] & CARD_ID_MASK].category == kind - 1) {
                args.pool = &w->pool;
                args.cardId = gCardCollection[cards[i]] & 0x8FFF;
                args.col = x;
                args.row = y;
                args.panel = 0;
                args.slot = &cards[i];
                TaskCreate(&w->tasks, &gTaskDescDeckCard2, &args);
                x++;
            }

            if (x > 2) {
                x = 0;
                y++;
            }
        }
    }

    w->x = 0x4800;
    w->y = 0x2800;
    w->scrollRowEnd = 4;
    SetDeckExchangeGridRowCount(w, y * 3 + x);
}

s32 CreateDeckExchangeCollectionGridCards(DeckExchangeWork* w, u8 kind, u8 c) {
    DeckCard2Args args;
    u16 i;
    s8 x;
    s8 y;

    x = 0;
    y = 0;

    for (i = 0; i < w->entryCount; i++) {
        if (kind == 5) {
            if (w->entries[i].kind <= 77) {
                args.pool = &w->pool;
                args.cardId = GetCardIdForKind(w->entries[i].kind);
                args.col = x;
                args.row = y;
                args.panel = 1;
                args.slot = NULL;
                TaskCreate(&w->tasks, &gTaskDescDeckCard2, &args);
                x++;
            }
        } else {
            args.pool = &w->pool;
            args.cardId = GetCardIdForKind(w->entries[i].kind);

            if (gCardDefs[args.cardId].category == kind - 1 && w->entries[i].kind <= 77) {
                args.col = x;
                args.row = y;
                args.panel = 1;
                args.slot = NULL;
                TaskCreate(&w->tasks, &gTaskDescDeckCard2, &args);
                x++;
            }
        }

        if (x > 2) {
            x = 0;
            y++;
        }
    }

    w->x = 0xA000;
    w->y = 0x2800;
    w->scrollRowEnd = 4;
    SetDeckExchangeGridRowCount(w, y * 3 + x);
}

s32 GetCardIdForKind(s32 a) {
    u32 i;

    for (i = 0; i < 950; i++) {
        if (gCardDefs[i].kind == a) {
            return i;
        }
    }
}

void ClearDeckExchangeCardGrid(DeckExchangeWork* w) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    while (node != NULL) {
        node->done = 1;
        node = ListPoolNext(&node->node);
    }

    TaskPoolUpdate(&w->tasks);
}

void ScrollDeckExchangeGridDown(DeckExchangeWork* w) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    if (w->scrollRowEnd == 33) {
        return;
    }

    while (node != NULL) {
        node->args.row--;

        if (node->args.row < 0) {
            node->y = 0x20000;
            DeckCard2ReleaseGfx(node);
        }

        node = ListPoolNext(&node->node);
    }

    m4aSongNumStart(SONG_SYS_CLICKI04B);
    w->scrollRowEnd++;
    w->y += 0x300;

    if (w->y > 0x7C00) {
        w->y = 0x7C00;
    }

    if (w->holding != 0) {
        w->heldRow--;
    }
}

u8 ScrollDeckExchangeGridUp(DeckExchangeWork* w) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    if (node == NULL) {
        w->y -= 0x300;

        if (w->y < 0x2800) {
            w->y = 0x2800;
            return 0;
        }

        return 1;
    }

    if (node->args.row == 0) {
        return 0;
    }

    do {
        node->args.row++;

        if (node->args.row > 3) {
            node->y = 0x20000;
            DeckCard2ReleaseGfx(node);
        }

        node = ListPoolNext(&node->node);
    } while (node != NULL);

    m4aSongNumStart(SONG_SYS_CLICKI04B);
    w->scrollRowEnd--;
    w->y -= 0x300;

    if (w->y < 0x2800) {
        w->y = 0x2800;
    }

    return 1;
}

void SetDeckExchangeHandAnim(DeckExchangeWork* w) {
    u16 t;

    switch (w->view) {
    case 0:
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
        w->handFlags &= ~SPRITE_FLAG_HFLIP;
        break;
    case 1:
    case 3:
        AnimStart(&w->anim, 2, ANIM_FLAG_LOOP);
        t = w->handFlags | SPRITE_FLAG_HFLIP;
        w->handFlags = t;
        break;
    }
}

void HighlightDeckExchangeDeckTab(DeckExchangeWork* w, u8 b) {
    u16* pal;

    switch (b) {
    case 0:
        pal = (u16*)(BG_PLTT + 8 * PLTT_SIZE_4BPP);
        LoadPalette(gUnk_096142F8, pal, 32);
        pal = (u16*)(BG_PLTT + 9 * PLTT_SIZE_4BPP);
        LoadPalette(gUnk_09614118 + 0x90, pal, 32);
        pal = (u16*)(BG_PLTT + 10 * PLTT_SIZE_4BPP);
        LoadPalette(gUnk_09614118 + 0xA0, pal, 32);
        LoadBgMap(0, gUnk_09519AB8 + 0xC0, 0x180);
        LoadBgMap(1, gUnk_0951A2B8, 0x180);
        LoadBgMap(2, gUnk_0951AAB8, 0x180);
        SetBgScroll(0, (u16)-76, (u16)-14);
        SetBgScroll(1, (u16)-88, (u16)-64);
        SetBgScroll(2, (u16)-88, (u16)-112);
        w->x4 = 100;
        w->y4 = 25;
        w->x5 = 102;
        w->y5 = 75;
        w->x6 = 102;
        w->y6 = 122;
        break;
    case 1:
        pal = (u16*)(BG_PLTT + 9 * PLTT_SIZE_4BPP);
        LoadPalette(gUnk_096142F8, pal, 32);
        pal = (u16*)(BG_PLTT + 8 * PLTT_SIZE_4BPP);
        LoadPalette(gUnk_09614118 + 0x80, pal, 32);
        pal = (u16*)(BG_PLTT + 10 * PLTT_SIZE_4BPP);
        LoadPalette(gUnk_09614118 + 0xA0, pal, 32);
        LoadBgMap(0, gUnk_09519AB8, 0x180);
        LoadBgMap(1, gUnk_0951A2B8 + 0xC0, 0x180);
        LoadBgMap(2, gUnk_0951AAB8, 0x180);
        SetBgScroll(0, (u16)-88, (u16)-16);
        SetBgScroll(1, (u16)-76, (u16)-62);
        SetBgScroll(2, (u16)-88, (u16)-112);
        w->x4 = 102;
        w->y4 = 27;
        w->x5 = 100;
        w->y5 = 73;
        w->x6 = 102;
        w->y6 = 122;
        break;
    case 2:
        pal = (u16*)(BG_PLTT + 10 * PLTT_SIZE_4BPP);
        LoadPalette(gUnk_096142F8, pal, 32);
        pal = (u16*)(BG_PLTT + 8 * PLTT_SIZE_4BPP);
        LoadPalette(gUnk_09614118 + 0x80, pal, 32);
        pal = (u16*)(BG_PLTT + 9 * PLTT_SIZE_4BPP);
        LoadPalette(gUnk_09614118 + 0x90, pal, 32);
        LoadBgMap(0, gUnk_09519AB8, 0x180);
        LoadBgMap(1, gUnk_0951A2B8, 0x180);
        LoadBgMap(2, gUnk_0951AAB8 + 0xC0, 0x180);
        SetBgScroll(0, (u16)-88, (u16)-16);
        SetBgScroll(1, (u16)-88, (u16)-64);
        SetBgScroll(2, (u16)-76, (u16)-110);
        w->x4 = 102;
        w->y4 = 27;
        w->x5 = 102;
        w->y5 = 75;
        w->x6 = 100;
        w->y6 = 121;
        break;
    }
}

void DrawDeckExchangeDeckCardCount(u8 deck) {
    u8 d[2];
    u8 e[2];
    u8* base;
    u16 n;

    base = NULL;
    n = GetDeckCardCount(deck);
    d[0] = n / 10;
    d[1] = n - (u16)(n / 10) * 10;
    e[0] = 9;
    e[1] = 9;

    switch (deck) {
    case 0:
        base = GetBgCharBase(0);
        break;
    case 1:
        base = GetBgCharBase(1);
        break;
    case 2:
        base = GetBgCharBase(2);
        break;
    }

    RequestDma3Copy(&gUnk_0940F938[(d[0] + 1) * 32], base + 0x20, 32);
    RequestDma3Copy(&gUnk_0940F938[(d[1] + 1) * 32], base + 0x40, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[0] + 1) * 32], base + 0x60, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[1] + 1) * 32], base + 0x80, 32);
}

void DrawDeckExchangeEquipMarker(u8 mode) {
    u8* bg0;
    u8* bg1;
    u8* bg2;

    bg0 = GetBgCharBase(0);
    bg1 = GetBgCharBase(1);
    bg2 = GetBgCharBase(2);

    switch (mode) {
    case 0:
        RequestDma3Copy(gUnk_0940FC58, bg0 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_0940FC58 + 0x400, bg1 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_0940FC58 + 0x400, bg2 + 0x1A0, 0x1E0);
        break;
    case 1:
        RequestDma3Copy(gUnk_09410058, bg0 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_09410058 - 0x400, bg1 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_09410058, bg2 + 0x1A0, 0x1E0);
        break;
    case 2:
        RequestDma3Copy(gUnk_09410058, bg0 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_09410058, bg1 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_09410058 - 0x400, bg2 + 0x1A0, 0x1E0);
        break;
    }
}

void DrawDeckExchangeDeckCpCost(u8 kind) {
    u8 d[3];
    u8 e[3];
    u8* base;
    u16 n;
    u8* ep;

    base = NULL;
    n = GetDeckCpCost(kind);
    d[0] = n / 100;
    d[1] = n / 10 - d[0] * 10;
    d[2] = n - d[0] * 100 - d[1] * 10;
    ep = e;
    ep[0] = gGameState.progression.cp / 100;
    ep[1] = gGameState.progression.cp / 10 - ep[0] * 10;
    ep[2] = gGameState.progression.cp - ep[0] * 100 - ep[1] * 10;

    switch (kind) {
    case 0:
        base = GetBgCharBase(0);
        break;
    case 1:
        base = GetBgCharBase(1);
        break;
    case 2:
        base = GetBgCharBase(2);
        break;
    }

    RequestDma3Copy(&gUnk_0940F938[(d[0] + 1) * 32], base + 0xA0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d[1] + 1) * 32], base + 0xC0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d[2] + 1) * 32], base + 0xE0, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[0] + 1) * 32], base + 0x100, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[1] + 1) * 32], base + 0x120, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[2] + 1) * 32], base + 0x140, 32);
}

void DrawDeckExchangeCollectionFilterTab(u8 kind, u8 slot) {
    u8* dst;

    dst = (u8*)GetBgScreenBase(3) + 0xA8;

    switch (kind) {
    case 5:
        RequestDma3Copy(gUnk_095152B8 + slot * 128, dst, 20);
        RequestDma3Copy(gUnk_095152B8 + 0x20 + slot * 128, dst + 0x40, 20);
        break;
    case 4:
        RequestDma3Copy(gUnk_095152CC + slot * 128, dst, 20);
        RequestDma3Copy(gUnk_095152CC + 0x20 + slot * 128, dst + 0x40, 20);
        break;
    case 3:
        RequestDma3Copy(gUnk_095152E0 + slot * 128, dst, 20);
        RequestDma3Copy(gUnk_095152E0 + 0x20 + slot * 128, dst + 0x40, 20);
        break;
    case 2:
        RequestDma3Copy(gUnk_09515338 + slot * 128, dst, 20);
        RequestDma3Copy(gUnk_09515338 + 0x20 + slot * 128, dst + 0x40, 20);
        break;
    case 1:
        RequestDma3Copy(gUnk_0951534C + slot * 128, dst, 20);
        RequestDma3Copy(gUnk_0951534C + 0x20 + slot * 128, dst + 0x40, 20);
        break;
    }
}

void DrawDeckExchangeCardTotals() {
    u8 d1[3];
    u8 d2[3];
    u16 a;
    u16 b;

    u8* base;

    a = CountCardsInDecks();
    b = CountCollectionCards();

    d1[0] = a / 100;
    d1[1] = a / 10 - d1[0] * 10;
    d1[2] = a - d1[0] * 100 - d1[1] * 10;
    d2[0] = b / 100;
    d2[1] = b / 10 - d2[0] * 10;
    d2[2] = b - d2[0] * 100 - d2[1] * 10;
    base = GetBgCharBase(3);
    RequestDma3Copy(&gUnk_0940F938[(d1[0] + 1) * 32], base + 0x2A0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d1[1] + 1) * 32], base + 0x2C0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d1[2] + 1) * 32], base + 0x2E0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d2[0] + 1) * 32], base + 0x300, 32);
    RequestDma3Copy(&gUnk_0940F938[(d2[1] + 1) * 32], base + 0x320, 32);
    RequestDma3Copy(&gUnk_0940F938[(d2[2] + 1) * 32], base + 0x340, 32);
}

void LoadDeckExchangeDeckNameTexts(DeckExchangeWork* w) {
    InitTextSlots(w->textSlots, 8);
    InitTextSlots(w->textSlots2, 8);
    InitTextSlots(w->textSlots3, 8);
    w->textSlotCount = LoadTextSlots(GetDeckName(0), w->textSlots);
    w->textSlotCount2 = LoadTextSlots(GetDeckName(1), w->textSlots2);
    w->textSlotCount3 = LoadTextSlots(GetDeckName(2), w->textSlots3);
}

void LoadDeckExchangeCardNameText(DeckExchangeWork* w, s32 id) {
    const CardDef* def;

    def = &gCardDefs[id];
    w->textSlotCount4 = LoadTextSlots(def->name, w->textSlots4);

    switch (def->category) {
    case 0:
        LoadPalette(gUnk_09614458, (void*)(w->palette4->index * 32 + OBJ_PLTT),
                    w->palette4->count << 5);
        break;
    case 1:
        LoadPalette(gUnk_09614478, (void*)(w->palette4->index * 32 + OBJ_PLTT),
                    w->palette4->count << 5);
        break;
    case 2:
        LoadPalette(gUnk_09614498, (void*)(w->palette4->index * 32 + OBJ_PLTT),
                    w->palette4->count << 5);
        break;
    case 3:
        LoadPalette(gUnk_096144B8, (void*)(w->palette4->index * 32 + OBJ_PLTT),
                    w->palette4->count << 5);
        break;
    }
}

void ShowDeckExchangeCardPreview(DeckExchangeWork* w) {
    DeckCard2Work* node;
    const CardDef* def;
    s32 id;
    u8 i;
    u8 j;
    void* dst;

    id = 0xFFFF;
    node = ListPoolFirst(&w->pool);

    while (node != NULL) {
        if (node->args.row == w->cursorRow && node->args.col == w->cursorCol) {
            id = node->args.cardId;
            break;
        }

        node = ListPoolNext(&node->node);
    }

    ReleaseDeckExchangeCardPreview(w);

    if (id != 0xFFFF) {
        def = &gCardDefs[id & CARD_ID_MASK];
        w->tiles4 = LoadObjTiles(gCardBacks[def->category].tiles, 0x300);
        w->tiles5 = LoadObjTiles(def->tiles, 0x200);
        w->palette3 = LoadObjPalette(def->palette, 32);
        w->palette2 = LoadObjPalette(gCard00Palette, 32);
        w->gfx3 = gCardBacks[def->category].gfx;
        w->gfx4 = def->gfx;

        for (i = 0; i < w->entryCount; i++) {
            if (w->entries[i].kind == def->kind) {
                break;
            }
        }

        w->entryIndex = i;
        dst = gUnk_05000160;
        LoadPalette(&gUnk_09614118[def->category * 16 + 0x100], dst, 32);

        for (j = 0; j < 10; j++) {
            DrawValueCount(w->entries[i].valueCounts[j], j);
        }

        LoadDeckExchangeCardNameText(w, id);
        LoadDeckExchangeCardDescriptionText(w, id);

        if (def->kind > 46) {
            LoadBgMap(2, gUnk_09518AB8, 0x800);
            DrawDeckExchangeCpCost(0);
        } else {
            LoadBgMap(2, gUnk_095182B8, 0x800);
            DrawDeckExchangeCpCost(0);
        }
    } else {
        for (j = 0; j < 10; j++) {
            DrawValueCount(0, j);
        }

        DrawDeckExchangeCpCost(0);
    }
}

void ReleaseDeckExchangeCardPreview(DeckExchangeWork* w) {
    if (w->tiles7 != NULL) {
        ReleaseObjTiles(w->tiles7);
        w->tiles7 = NULL;
    }

    if (w->tiles4 != NULL) {
        ReleaseObjTiles(w->tiles4);
        ReleaseObjPalette(w->palette2);
        ReleaseObjTiles(w->tiles5);
        ReleaseObjPalette(w->palette3);

        if (w->tiles6 != NULL) {
            ReleaseObjTiles(w->tiles6);
            w->tiles6 = NULL;
        }

        w->tiles4 = NULL;
        w->palette2 = NULL;
        w->tiles5 = NULL;
        w->palette3 = NULL;
    }
}

void DrawDeckExchangeValueCpCost(DeckExchangeWork* w) {
    DrawDeckExchangeCpCost(GetCardCpCost(
        GetCardIdForKind(w->entries[w->entryIndex].kind) +
        w->cursorCol * 5 + (u16)w->cursorRow));
}

void DrawDeckExchangeCpCost(u8 a) {
    u8 d[2];
    u8* base;

    base = GetBgCharBase(3);

    if (a != 0) {
        d[0] = a / 10;
        d[1] = a - d[0] * 10;
        RequestDma3Copy(&gUnk_0940FA98[(d[0] + 3) * 32], base + 0xCE0, 32);
        RequestDma3Copy(&gUnk_0940FA98[(d[1] + 3) * 32], base + 0xD00, 32);
    } else {
        RequestDma3Copy(gUnk_0940FAD8, base + 0xCE0, 32);
        RequestDma3Copy(gUnk_0940FAD8, base + 0xD00, 32);
    }
}

u32 SumDeckExchangeValueCounts(u16* data) {
    u32 sum;
    u16* p;
    s32 i;

    sum = 0;
    p = data;
    i = 9;

    do {
        sum += *p++;
    } while (--i >= 0);

    return sum;
}

s32 MoveDeckExchangeValueCursor(DeckExchangeWork* w, u16 key) {
    u8* tbl;
    u8 idx;
    u8 r0;
    u8 c0;
    u16 row0;
    s32 sum;
    s32 i;
    s8 d;
    s8 n;
    s32 ofs;
    s32 k;
    u8* p;

    idx = w->cursorCol * 5 + (u8)w->cursorRow;
    tbl = (u8*)&w->entries[w->entryIndex];
    row0 = w->cursorCol;
    r0 = w->cursorCol;
    c0 = w->cursorRow;

    if (*(u16*)&tbl[idx << 1] != 0) {
        return 1;
    }

    switch (key) {
    case 0x40:
        do {
            if (w->cursorRow > 0) {
                w->cursorRow = w->cursorRow - 1;
            } else {
                w->cursorRow = 4;
            }

            idx = w->cursorCol * 5 + (u8)w->cursorRow;

            if (w->cursorCol == r0 && w->cursorRow == c0) {
                return 0;
            }
        } while (*(u16*)&tbl[idx << 1] == 0);

        break;
    case 0x80:
        do {
            if (w->cursorRow <= 3) {
                w->cursorRow = w->cursorRow + 1;
            } else {
                w->cursorRow = 0;
            }

            idx = w->cursorCol * 5 + (u8)w->cursorRow;

            if (w->cursorCol == r0 && w->cursorRow == c0) {
                return 0;
            }
        } while (*(u16*)&tbl[idx << 1] == 0);

        break;
    case 0x20:
        if (*(u16*)&tbl[w->cursorRow << 1] != 0) {
            if ((s16)row0 > 0) {
                w->cursorCol = row0 - 1;
            }

            return 1;
        }

        sum = 0;

        for (i = 0; i < 5; i++) {
            sum += *(u16*)&tbl[i * 2];
        }

        if (sum == 0) {
            w->cursorCol = 1;
            return 0;
        }

        p = (u8*)&w->cursorRow;
        d = -1;
        k = *p + d;

        for (;;) {
            n = k;

            if (n < 0) {
                n = 0;
            }

            if (n > 4) {
                n = 4;
            }

            ofs = n;

            if (*(u16*)&tbl[ofs *= 2] != 0) {
                break;
            }

            if (d < 0) {
                d = -d;
            } else {
                d++;
                d = -d;
            }

            k = *p + d;
        }

        w->cursorRow = n;
        break;
    case 0x10:
        if (*(u16*)&tbl[(w->cursorRow + 5) << 1] != 0) {
            if ((s16)row0 <= 0) {
                w->cursorCol = row0 + 1;
            }

            return 1;
        }

        sum = 0;

        for (i = 5; i < 10; i++) {
            sum += *(u16*)&tbl[i * 2];
        }

        if (sum == 0) {
            w->cursorCol = 0;
            return 0;
        }

        p = (u8*)&w->cursorRow;
        d = -1;
        k = *p + d;

        for (;;) {
            n = k;

            if (n < 0) {
                n = 0;
            }

            if (n > 4) {
                n = 4;
            }

            ofs = n;
            ofs *= 2;

            if (*(u16*)&tbl[ofs += 10] != 0) {
                break;
            }

            if (d < 0) {
                d = -d;
            } else {
                d++;
                d = -d;
            }

            k = *p + d;
        }

        w->cursorRow = n;
        break;
    case 0:
        do {
            if (w->cursorRow <= 3) {
                w->cursorRow = w->cursorRow + 1;
            } else {
                w->cursorRow = 0;
            }

            idx = w->cursorCol * 5 + (u8)w->cursorRow;

            if (w->cursorCol == r0 && w->cursorRow == c0) {
                if (w->cursorCol <= 0) {
                    w->cursorCol = w->cursorCol + 1;
                } else {
                    w->cursorCol = 0;
                }

                if (SumDeckExchangeValueCounts((u16*)tbl) == 0) {
                    return 0;
                }
            }
        } while (*(u16*)&tbl[idx << 1] == 0);

        break;
    }

    return 1;
}

void FreeDeckExchangeCollectionEntries(DeckExchangeWork* w) {
    u16 i;

    if (w->entries != NULL) {
        for (i = 0; i < w->entryCount; i++) {
            EwramFree(w->entries[i].indices);
        }

        EwramFree(w->entries);
        w->entries = NULL;
    }
}

void SetDeckExchangeFrameCursor(DeckExchangeWork* w, u8 kind) {
    switch (kind) {
    case 0:
        SetObjTileSource(w->tiles2, gUnk_090A4A0C);
        AnimInit(&w->anim2, gUnk_09EEB064, gUnk_09EEB050);
        AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
        w->gfx2 = AnimGetGfx(&w->anim2);
        break;
    case 1:
        SetObjTileSource(w->tiles2, gUnk_090A51F6);
        AnimInit(&w->anim2, gUnk_09EEB07C, gUnk_09EEB068);
        AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
        w->gfx2 = AnimGetGfx(&w->anim2);
        break;
    }
}

s32 TakeTradeCard(DeckExchangeWork* w) {
    u16 idx;
    CardKindEntry* e;
    u16 i;
    s32 card;
    u16 id;
    const CardDef* def;
    u16 kind;

    idx = w->cursorCol * 5 + w->cursorRow;
    e = &w->entries[w->entryIndex];

    if (e->valueCounts[idx] == 0) {
        m4aSongNumStart(SONG_SYS_BEEP);
        return 1;
    }

    for (i = 0; i < e->count; i++) {
        card = e->indices[i];

        if (card != 0xFFFF) {
            id = gCardCollection[card] & CARD_ID_MASK;
            def = &gCardDefs[id];

            if (id > 0x1C1) {
                if (idx == 0) {
                    gSioTradeCardId = gCardCollection[card] & CARD_ID_MASK;
                    ClearCardCollectionSlot(&gCardCollection[card]);
                    e->indices[i] = 0xFFFF;
                    e->valueCounts[0]--;
                    DrawValueCount(e->valueCounts[0], 0);
                    m4aSongNumStart(SONG_SYS_KETTEI);
                    return 1;
                }
            } else {
                kind = def->value;

                if (kind == idx) {
                    gSioTradeCardId = gCardCollection[card] & CARD_ID_MASK;
                    ClearCardCollectionSlot(&gCardCollection[card]);
                    e->indices[i] = 0xFFFF;
                    e->valueCounts[kind]--;
                    DrawValueCount(e->valueCounts[kind], kind);
                    m4aSongNumStart(SONG_SYS_KETTEI);
                    return 1;
                }
            }
        }
    }

    m4aSongNumStart(SONG_SYS_BEEP);
    return 1;
}

s32 CheckDeckExchangeCpCost(DeckExchangeWork* w) {
    if (GetDeckCpCost(GetActiveDeckIndex()) > gGameState.progression.cp) {
        TaskCreate(&w->tasks2, &gTaskDescDeckErrorCp, &w->popupActive);
        m4aSongNumStart(SONG_SYS_BEEP);

        return 0;
    }

    return 1;
}

u8 CheckDeckExchangeHasAttackCard(DeckExchangeWork* w) {
    if (CountActiveDeckCardsOfCategory(0) == 0) {
        m4aSongNumStart(SONG_SYS_BEEP);
        TaskCreate(&w->tasks2, &gTaskDescDeckErrorNoAttackCard, &w->popupActive);
        return 0;
    }

    return 1;
}

void ResetDeckExchangeGridScroll(DeckExchangeWork* w) {
    DeckCard2Work* node;
    s16 x;
    s16 y;

    node = ListPoolFirst(&w->pool);
    x = 0;
    y = 0;

    while (node != NULL) {
        node->args.col = x;
        node->args.row = y;
        x++;

        if (x > 2) {
            x = 0;
            y++;
        }

        node = ListPoolNext(&node->node);
    }

    w->y = 0x2800;
    w->scrollRowEnd = 4;
}

u8 IsDeckExchangeCardAtCursor(DeckExchangeWork* w) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    while (node != NULL) {
        if (node->args.col == w->cursorCol &&
            node->args.row == w->cursorRow) {
            return 1;
        }

        node = ListPoolNext(&node->node);
    }

    return 0;
}

u8 IsDeckExchangeCardAt(DeckExchangeWork* w, s16 x, s16 y) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    while (node != NULL) {
        if (node->args.col == x && node->args.row == y) {
            return 1;
        }

        node = ListPoolNext(&node->node);
    }

    return 0;
}

u8 FindDeckExchangeCardInDirection(DeckExchangeWork* w, s16 x, s16 y, u16 dir) {
    DeckCard2Work* n;

    for (n = ListPoolFirst(&w->pool); n != NULL; n = ListPoolNext(&n->node)) {
        if (n->args.col == x && n->args.row == y) {
            return 1;
        }
    }

    switch (dir) {
    case 0x40:
        return FindDeckExchangeCardInDirection(w, x, y - 1, 0x40);
    case 0x80:
        return FindDeckExchangeCardInDirection(w, x, y + 1, 0x80);
    case 0x20:
        return FindDeckExchangeCardInDirection(w, x - 1, y, 0x20);
    case 0x10:
        return FindDeckExchangeCardInDirection(w, x + 1, y, 0x10);
    }

    return 0;
}

void LoadDeckExchangeCardDescriptionText(DeckExchangeWork* w, u16 index) {
    const CardDef* d;

    d = &gCardDefs[index];
    w->textSlotCount5 = LoadTextSlots((void*)gCardKindDescriptions[d->kind], w->textSlots5);
}

void SetDeckExchangeGridRowCount(DeckExchangeWork* w, s16 n) {
    w->rowCount = n / 3;

    if (n % 3 != 0) {
        w->rowCount = n / 3 + 1;
    }
}

void UpdateDeckExchangeGridScrollBar(DeckExchangeWork* w) {
    s32 t;

    t = 0x5400 / (w->rowCount - 4);
    w->y = t * (w->scrollRowEnd - 4) + 0x2800;

    if (w->y > 0x7C00) {
        w->y = 0x7C00;
    }

    if (w->y < 0x2800) {
        w->y = 0x2800;
    }
}
#endif

#ifndef VERSION_EU
TaskDesc gTaskDescDeckexchange = {
    "deckexchange",
    (TaskInitFunc)deckexchange_0,
    (TaskUpdateFunc)deckexchange_1,
    (TaskDrawFunc)deckexchange_2,
    (TaskDestroyFunc)deckexchange_3,
    sizeof(DeckExchangeWork),
};
#endif
