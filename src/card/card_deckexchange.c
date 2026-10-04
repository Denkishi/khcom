/**
 * card_deckexchange.c
 * Link Card Trade Screen
 */

#include "macros.h"
#include "registration_data.h"
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
#include "card_deck.h"
#include "card_deckexchange.h"
#include "ms_charge.h"

#ifndef VERSION_EU
u16 gSioTradeCardId EWRAM_COMMON(4);
#endif

#ifndef VERSION_EU
static const s16 sDeckExchangeTabPointerX[3] = { 116, 116, 116 };

static const s16 sDeckExchangeTabPointerY[3] = { 56, 104, 148 };

const s16 gUnk_09041F10[5] = { 12, 28, 42, 56, 70 };

static const s16 sDeckExchangeFilterTabX[6] = { 172, 172, 188, 202, 216, 230 };

const s16 gUnk_09041F26[5] = { 64, 82, 100, 118, 136 };

static const s16 sDeckExchangeValueGridX[2] = { 80, 128 };

static const s16 sDeckExchangeValueGridY[5] = { 80, 88, 96, 104, 112 };

static const u16 sUnk_09041F3E[4] = { 45, 93, 141, 30 };

void deckexchange_0(DeckExchangeWork* work, void* a) {
    u16 n;

    CpuFill32(0, work, sizeof(DeckExchangeWork));
    work->tiles7 = NULL;
    work->tiles4 = NULL;
    work->tiles5 = NULL;
    work->tiles6 = NULL;
    work->palette2 = NULL;
    work->palette3 = NULL;
    work->tiles8 = NULL;
    work->palette6 = NULL;
    work->palette7 = NULL;
    work->palette4 = NULL;
    work->unk_4C0 = NULL;
    work->unk_4C4 = NULL;
    work->entries = NULL;
    work->resultOut = a;
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
    ListPoolInit(&work->pool);
    TaskPoolInit(&work->tasks, 99);
    TaskPoolInit(&work->tasks2, 1);
    work->deckIndex = GetActiveDeckIndex();
    CreateDeckExchangeDeckGridCards(work, 0);
    work->tiles = AllocObjTiles(0x120, NULL);
    SetObjTileSource(work->tiles, gUnk_090A4664);
    AnimInit(&work->anim, gUnk_09EEB03C, gUnk_09EEB008);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    work->x2 = sDeckExchangeTabPointerX[0] << 8;
    work->y2 = sDeckExchangeTabPointerY[0] << 8;
    work->handFlags = 0;
    work->tiles3 = LoadObjTiles(gUnk_090A44C4, 32);
    work->palette = LoadObjPalette(gUnk_09614418, 32);
    work->tiles2 = AllocObjTiles(0x280, NULL);
    SetDeckExchangeFrameCursor(work, 0);
    work->palette4 = LoadObjPalette(gUnk_09614438, 32);
    work->step = 0;
    work->cursorCol = 0;
    work->cursorRow = 0;
    work->prevCursorCol = 0;
    work->prevCursorRow = 0;
    work->timer = 4;
    work->commandCursor = 0;
    work->mode = 0;
    work->view = 0;
    work->deckAttackCount = CountActiveDeckCardsOfCategory(0);
    work->deckMagicCount = CountActiveDeckCardsOfCategory(1);
    work->deckItemCount = CountActiveDeckCardsOfCategory(2);
    work->deckEnemyCount = CountActiveDeckCardsOfCategory(3);
    work->categoryFilter = 0;
    work->entryCount = 0;
    work->popupActive = 0;
    work->exitRequested = 0;
    work->barSlideTimer = 16;
    work->bannerSlideTimer = 16;
    work->unk_6A4 = 0;
    work->unk_6AC = -0x800;
    work->unk_6A8 = 0;
    work->unk_6B0 = 0xA000;
    work->unk_6B4 = -0x8000;
    work->holding = 0;
    work->x7 = 8;
    work->y7 = 113;
    work->textSlotCount5 = 0;
    work->unk_6C4 = 79;
    n = sUnk_09041F3E[work->deckIndex];
    work->unk_6C6 = n;
    work->unk_6C8 = 225;
    n = sUnk_09041F3E[work->deckIndex];
    work->unk_6CA = n;
    work->unk_70F = 0;
    work->inputDelay = 0;
    work->textSlotCount = 0;
    work->textSlotCount2 = 0;
    work->textSlotCount3 = 0;
    work->textSlotCount4 = 0;
    InitTextSlots(work->textSlots, 8);
    InitTextSlots(work->textSlots2, 8);
    InitTextSlots(work->textSlots3, 8);
    InitTextSlots(work->textSlots4, 30);
    InitTextSlots(work->textSlots5, 90);
}

u8 deckexchange_1(DeckExchangeWork* work, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 16);

    switch (work->step) {
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
        work->step = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeLoadBgs);
        return 1;
    }

    work->step++;
}

u8 UpdateDeckExchangeLoadBgs(DeckExchangeWork* work, void* a) {
    FadeStartIn(FADE_MODE_BLACK, 16);

    switch (work->step) {
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
        work->step = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeLoadDeckInfo);
        return 1;
    }

    work->step++;
    SetBgScroll(0, (u16)-88, (u16)-16);
    SetBgScroll(1, (u16)-88, (u16)-64);
    SetBgScroll(2, (u16)-88, (u16)-112);
    return 1;
}

u8 UpdateDeckExchangeLoadDeckInfo(DeckExchangeWork* work, void* a) {
    s32 v;

    FadeStartIn(FADE_MODE_BLACK, 16);

    switch (work->step) {
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
        DrawDeckCategoryCount(work->deckAttackCount, 0);
        break;
    case 5:
        DrawDeckCategoryCount(work->deckMagicCount, 1);
        break;
    case 6:
        DrawDeckCategoryCount(work->deckItemCount, 2);
        break;
    case 7:
        DrawDeckCategoryCount(work->deckEnemyCount, 3);
        break;
    case 8:
        HighlightDeckExchangeDeckTab(work, work->deckIndex);
        break;
    case 9:
        DrawDeckExchangeDeckCardCount(0);
        DrawDeckExchangeDeckCardCount(1);
        DrawDeckExchangeDeckCardCount(2);
        break;
    case 10:
        DrawDeckExchangeEquipMarker(GetActiveDeckIndex());
        DrawDeckExchangeCardTotals();
        work->x = 0x4800;
        work->y = 0x2800;
        v = work->deckIndex;
        work->cursorRow = v;
        ApproachValue(&work->x2, sDeckExchangeTabPointerX[work->cursorCol] << 8, work->timer);
        ApproachValue(&work->y2, sDeckExchangeTabPointerY[work->cursorRow] << 8, work->timer);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeOpenCollection);
        work->view = 1;
        SetDeckExchangeHandAnim(work);
        LoadDeckExchangeDeckNameTexts(work);
        break;
    }

    work->step++;
    return 1;
}

u8 UpdateDeckExchangeValueSelect(DeckExchangeWork* work, void* a) {
    s8 n;
    s32 m;

    if (work->popupActive != 0) {
        TaskPoolUpdate(&work->tasks);
        TaskPoolUpdate(&work->tasks2);

        if (GetKeysPressed() & START_BUTTON) {
            work->exitRequested = 1;
        }

        return 1;
    }

    if (work->exitRequested) {
        if ((u8)CheckDeckExchangeCpCost(work) && CheckDeckExchangeHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        work->exitRequested = 0;
    }

    work->gfx = AnimUpdate(&work->anim);
    work->gfx2 = AnimUpdate(&work->anim2);

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
        if (work->cursorCol > 0) {
            work->cursorCol--;
            work->timer = 4;

            if ((u8)MoveDeckExchangeValueCursor(work, 32)) {
                m4aSongNumStart(SONG_SYS_CLICK);
            }
        }

        DrawDeckExchangeValueCpCost(work);
        break;
    case DPAD_RIGHT:
        if (work->cursorCol <= 0) {
            work->cursorCol++;
            work->timer = 4;

            if ((u8)MoveDeckExchangeValueCursor(work, 16)) {
                m4aSongNumStart(SONG_SYS_CLICK);
            }
        }

        DrawDeckExchangeValueCpCost(work);
        break;
    case DPAD_UP:
        n = work->cursorRow;

        if (work->cursorRow > 0) {
            work->cursorRow--;
        }

        work->timer = 4;
        MoveDeckExchangeValueCursor(work, 64);

        if (n != work->cursorRow) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        DrawDeckExchangeValueCpCost(work);
        break;
    case DPAD_DOWN:
        n = work->cursorRow;

        if (work->cursorRow <= 3) {
            work->cursorRow++;
        }

        work->timer = 4;
        MoveDeckExchangeValueCursor(work, 128);

        if (n != work->cursorRow) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        DrawDeckExchangeValueCpCost(work);
        break;
    }

    switch (GetKeysPressed()) {
    case B_BUTTON:
        SetDeckExchangeFrameCursor(work, 0);
        m = (s8)work->savedCol;
        work->cursorCol = m;
        m = (s8)work->savedRow;
        work->cursorRow = m;
        work->x2 = gCollectionGridColumnX[work->cursorCol] << 8;
        work->y2 = gCollectionGridRowY[work->cursorRow] << 8;
        ShowDeckExchangeCardPreview(work);
        work->view = 9;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeGrid);
        return 1;
    case A_BUTTON:
        if (!(u8)TakeTradeCard(work)) {
            return 1;
        }

        DrawDeckExchangeCardTotals();
        CountCardsNotInDeckByCategory(3, work->collectionCategoryCounts);
        DrawCollectionCategoryCount(work->collectionCategoryCounts[0], 0);
        DrawCollectionCategoryCount(work->collectionCategoryCounts[1], 1);
        DrawCollectionCategoryCount(work->collectionCategoryCounts[2], 2);
        DrawCollectionCategoryCount(work->collectionCategoryCounts[3], 3);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeClose);
        DrawDeckExchangeValueCpCost(work);
        work->timer = 4;
        break;
    case START_BUTTON:
        if ((u8)CheckDeckExchangeCpCost(work) && CheckDeckExchangeHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
        }

        return 1;
    }

    if (work->timer != 0) {
        ApproachValue(&work->x2, sDeckExchangeValueGridX[work->cursorCol] << 8, work->timer);
        ApproachValue(&work->y2, (sDeckExchangeValueGridY[work->cursorRow] - 16) << 8, work->timer);
        work->timer--;
    }

    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&work->tasks2);
    return 1;
}

u8 UpdateDeckExchangeCollectionFilter(DeckExchangeWork* work, void* a) {
    s32 i;

    work->gfx = AnimUpdate(&work->anim);

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
        if (work->cursorCol > 1) {
            work->cursorCol--;
            work->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICK);
            work->categoryFilter = work->cursorCol;
            DrawDeckExchangeCollectionFilterTab(work->categoryFilter, work->mode);
            ClearDeckExchangeCardGrid(work);
            work->gridEntryCount = CreateDeckExchangeCollectionGridCards(work, work->categoryFilter, 1);
        }

        for (i = 0; i < 10; i++) {
            DrawValueCount(0, i);
        }

        break;
    case DPAD_RIGHT:
        if (work->cursorCol < 5) {
            work->cursorCol++;
            work->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICK);
            work->categoryFilter = work->cursorCol;
            DrawDeckExchangeCollectionFilterTab(work->categoryFilter, work->mode);
            ClearDeckExchangeCardGrid(work);
            work->gridEntryCount = CreateDeckExchangeCollectionGridCards(work, work->categoryFilter, 1);
        }

        for (i = 0; i < 10; i++) {
            DrawValueCount(0, i);
        }

        break;
    case DPAD_DOWN:
        if (work->gridEntryCount != 0) {
            work->cursorCol = 0;
            work->cursorRow = 0;
            work->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            ShowDeckExchangeCardPreview(work);
            work->view = 9;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeGrid);
            work->x = 0xA000;
            work->y = 0x2800;
            work->scrollRowEnd = 4;
            return 1;
        }

        m4aSongNumStart(SONG_SYS_BEEP);
        break;
    case B_BUTTON:
        if (work->gridEntryCount != 0) {
            work->cursorCol = 0;
            work->cursorRow = 0;
            work->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            ShowDeckExchangeCardPreview(work);
            work->view = 9;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeGrid);
            work->x = 0xA000;
            work->y = 0x2800;
            work->scrollRowEnd = 4;
            return 1;
        }

        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeClose);
        m4aSongNumStart(SONG_SYS_CLOSE);
        return 1;
    case START_BUTTON:
        if ((u8)CheckDeckExchangeCpCost(work) && CheckDeckExchangeHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
        }

        return 1;
    }

    if (work->timer != 0) {
        ApproachValue(&work->x2, sDeckExchangeFilterTabX[work->cursorCol] << 8, work->timer);
        ApproachValue(&work->y2, 0x1E00, work->timer);
        work->timer--;
    }

    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&work->tasks2);
    return 1;
}

u8 UpdateDeckExchangeOpenCollection(DeckExchangeWork* work, void* a) {
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
    CountCardsNotInDeckByCategory(3, work->collectionCategoryCounts);
    DrawCollectionCategoryCount(work->collectionCategoryCounts[0], 0);
    DrawCollectionCategoryCount(work->collectionCategoryCounts[1], 1);
    DrawCollectionCategoryCount(work->collectionCategoryCounts[2], 2);
    DrawCollectionCategoryCount(work->collectionCategoryCounts[3], 3);
    work->view = 9;
    SetDeckExchangeFrameCursor(work, 0);
    ClearDeckExchangeCardGrid(work);
    work->step = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeBuildList);
    work->unk_6C4 = 0xFFFE;
    work->unk_6C6 = 142;
    work->unk_6C8 = 142;
    work->unk_6CA = 142;
    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&work->tasks2);
    return 1;
}

u8 UpdateDeckExchangeBuildList(DeckExchangeWork* work, void* a) {
    u16 i;
    u16 j;
    u16 n;

    FadeStartIn(FADE_MODE_BLACK, 16);

    switch (work->step) {
    case 0:
        work->entryCount = 286;
        work->kindEntries = EwramAlloc(work->entryCount * sizeof(CardKindEntry));
        CpuFill32(0, work->kindEntries, work->entryCount * sizeof(CardKindEntry));
        break;
    case 1:
        CountCardsNotInDeckByKind(work->kindEntries, work->deckIndex, 0, work->entryCount, work->unk_4F4);
        break;
    case 2:
        work->entryCount = ListCardsNotInDeckByKind(work->kindEntries, work->deckIndex, 0, work->entryCount, work->unk_4F4);
        break;
    case 3:
        work->entries = EwramAlloc(work->entryCount * sizeof(CardKindEntry));

        for (i = 0, n = 0; i < 286; i++) {
            if (work->kindEntries[i].count != 0) {
                work->entries[n] = work->kindEntries[i];
                work->entries[n].indices = EwramAlloc(work->kindEntries[i].indexCount * 2);

                for (j = 0; j < work->kindEntries[i].indexCount; j++) {
                    work->entries[n].indices[j] = work->kindEntries[i].indices[j];
                }

                n++;
            }
        }

        break;
    case 4:
        for (i = 0; i < 286; i++) {
            if (work->kindEntries[i].count != 0) {
                EwramFree(work->kindEntries[i].indices);
            }
        }

        EwramFree(work->kindEntries);
        break;
    case 5:
        work->categoryFilter = 5;
        work->gridEntryCount = CreateDeckExchangeCollectionGridCards(work, 5, 1);
        SetDeckExchangeHandAnim(work);
        work->x2 = gCollectionGridColumnX[0] << 8;
        work->y2 = gCollectionGridRowY[0] << 8;
        work->mode = 2;
        work->cursorCol = 0;
        work->cursorRow = 0;
        ShowDeckExchangeCardPreview(work);

        if (work->gridEntryCount != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeGrid);
        } else {
            work->cursorCol = work->categoryFilter;
            work->timer = 4;
            work->view = 10;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeCollectionFilter);
        }

        break;
    }

    work->step++;
    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&work->tasks2);
    return 1;
}

u8 UpdateDeckExchangeGrid(DeckExchangeWork* work, void* a) {
    s32 i;

    work->gfx = AnimUpdate(&work->anim);
    work->gfx2 = AnimUpdate(&work->anim2);

    if (work->popupActive != 0) {
        TaskPoolUpdate(&work->tasks);
        TaskPoolUpdate(&work->tasks2);

        if (GetKeysPressed() & START_BUTTON) {
            work->exitRequested = 1;
        }

        return 1;
    }

    if (work->exitRequested) {
        if ((u8)CheckDeckExchangeCpCost(work) && CheckDeckExchangeHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        work->exitRequested = 0;
    }

    switch (GetKeysRepeat()) {
    case DPAD_UP:
        if (work->cursorRow > 0) {
            if (IsDeckExchangeCardAt(work, work->cursorCol, work->cursorRow - 1)) {
                work->cursorRow--;
                work->timer = 4;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            }
        } else {
            if (!ScrollDeckExchangeGridUp(work)) {
                UpdateDeckExchangeGridScrollBar(work);
                work->cursorCol = work->categoryFilter;
                work->timer = 4;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
                work->view = 10;

                for (i = 0; i < 10; i++) {
                    DrawValueCount(0, i);
                }

                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeCollectionFilter);
                return 1;
            }

            UpdateDeckExchangeGridScrollBar(work);
        }

        ShowDeckExchangeCardPreview(work);
        break;
    case DPAD_DOWN:
        if (work->cursorRow < 3) {
            if (IsDeckExchangeCardAt(work, work->cursorCol, work->cursorRow + 1)) {
                work->cursorRow++;
                work->timer = 4;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            }
        } else if (IsDeckExchangeCardAt(work, work->cursorCol, work->cursorRow + 1)) {
            ScrollDeckExchangeGridDown(work);
            UpdateDeckExchangeGridScrollBar(work);
        }

        ShowDeckExchangeCardPreview(work);
        break;
    case DPAD_LEFT:
        if (work->cursorCol > 0 && IsDeckExchangeCardAt(work, work->cursorCol - 1, work->cursorRow)) {
            work->cursorCol--;
            work->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        ShowDeckExchangeCardPreview(work);
        break;
    case DPAD_RIGHT:
        if (work->cursorCol > 1) {
            work->timer = 4;
            return 1;
        }

        if (IsDeckExchangeCardAt(work, work->cursorCol + 1, work->cursorRow)) {
            work->cursorCol++;
            work->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        ShowDeckExchangeCardPreview(work);
        break;
    }

    switch (GetKeysPressed()) {
    case A_BUTTON:
        if (IsDeckExchangeCardAtCursor(work)) {
            work->savedCol = work->cursorCol;
            work->savedRow = work->cursorRow;
            work->cursorCol = 0;
            work->cursorRow = 0;
            SetDeckExchangeFrameCursor(work, 1);
            work->view = 11;
            m4aSongNumStart(SONG_SYS_KETTEI);

            if ((u8)MoveDeckExchangeValueCursor(work, 0)) {
                DrawDeckExchangeValueCpCost(work);
                work->x2 = sDeckExchangeValueGridX[work->cursorCol] << 8;
                work->y2 = (sDeckExchangeValueGridY[work->cursorRow] - 16) << 8;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeValueSelect);
                return 1;
            }

            work->cursorCol = (s8)work->savedCol;
            work->cursorRow = (s8)work->savedRow;
            SetDeckExchangeFrameCursor(work, 0);
            work->view = 9;
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
        if ((u8)CheckDeckExchangeCpCost(work) && CheckDeckExchangeHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
        }

        return 1;
    }

    if (GetKeysPressed() & SELECT_BUTTON) {
        ResetDeckExchangeGridScroll(work);
        work->cursorCol = work->categoryFilter;
        work->timer = 4;
        work->x = 0xA000;
        work->y = 0x2800;
        work->scrollRowEnd = 4;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
        work->view = 10;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeCollectionFilter);
        return 1;
    }

    if (work->timer != 0) {
        ApproachValue(&work->x2, gCollectionGridColumnX[work->cursorCol] << 8, work->timer);
        ApproachValue(&work->y2, gCollectionGridRowY[work->cursorRow] << 8, work->timer);
        work->timer--;
    }

    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&work->tasks2);
    return 1;
}

u8 UpdateDeckExchangeClose(DeckExchangeWork* work, void* a) {
    FadeStartOut(FADE_MODE_BLACK, 16);
    work->categoryFilter = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateDeckExchangeFadeOut);
    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&work->tasks2);
    return 1;
}

u8 UpdateDeckExchangeFadeOut(DeckExchangeWork* work) {
    if (!FadeIsActive()) {
        ClearDeckExchangeCardGrid(work);
        return 0;
    }

    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&work->tasks2);
    return 1;
}

void DrawDeckExchangeDeckNames(DeckExchangeWork* work, u8 b) {
    if (!b) {
        switch (work->deckIndex) {
        case 0:
            DrawTextSlots(work->x4, work->y4, work->textSlots, work->palette, 20, work->textSlotCount);
            DrawTextSlots(work->x5, work->y5, work->textSlots2, work->palette4, 20, work->textSlotCount2);
            DrawTextSlots(work->x6, work->y6, work->textSlots3, work->palette4, 20, work->textSlotCount3);
            break;
        case 1:
            DrawTextSlots(work->x4, work->y4, work->textSlots, work->palette4, 20, work->textSlotCount);
            DrawTextSlots(work->x5, work->y5, work->textSlots2, work->palette, 20, work->textSlotCount2);
            DrawTextSlots(work->x6, work->y6, work->textSlots3, work->palette4, 20, work->textSlotCount3);
            break;
        case 2:
            DrawTextSlots(work->x4, work->y4, work->textSlots, work->palette4, 20, work->textSlotCount);
            DrawTextSlots(work->x5, work->y5, work->textSlots2, work->palette4, 20, work->textSlotCount2);
            DrawTextSlots(work->x6, work->y6, work->textSlots3, work->palette, 20, work->textSlotCount3);
            break;
        }
    } else {
        switch (work->deckIndex) {
        case 0:
            DrawTextSlots(work->x4, work->y4, work->textSlots, work->palette, 20, work->textSlotCount);
            break;
        case 1:
            DrawTextSlots(work->x5, work->y5, work->textSlots2, work->palette, 20, work->textSlotCount2);
            break;
        case 2:
            DrawTextSlots(work->x6, work->y6, work->textSlots3, work->palette, 20, work->textSlotCount3);
            break;
        }
    }
}

void DrawDeckExchangeCardDescription(DeckExchangeWork* work) {
    DrawTextSlots(work->x7, work->y7, work->textSlots5, work->palette, 20, work->textSlotCount5);
}

void deckexchange_2(DeckExchangeWork* work) {
    if (work->popupActive == 0) {
        DrawSprite((work->x2 >> 8) - 16, (work->y2 >> 8) - 30, work->gfx, work->tiles, work->palette, NULL, work->handFlags, 3);
    }

    DrawSprite(work->x >> 8, work->y >> 8, gUnk_09EEB000[0], work->tiles3, work->palette, NULL, SPRITE_PRIORITY(2), 10);

    switch (work->view) {
    case 0:
        if (work->holding != 0) {
            DrawSprite((work->x3 >> 8) - 16, (work->y3 >> 8) - 20, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);
        }

        DrawSprite((work->x2 >> 8) - 16, (work->y2 >> 8) - 20, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);
    case 1:
    case 2:
    case 3:
        DrawDeckExchangeDeckNames(work, 0);
        break;
    case 4:
        DrawDeckExchangeDeckNames(work, 1);
        DrawSprite((work->x2 >> 8) - 16, (work->y2 >> 8) - 20, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);

        if (work->tiles4 != NULL) {
            if (work->popupActive == 0) {
                DrawSprite((work->x2 >> 8) - 16, (work->y2 >> 8) - 20, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);
            }

            DrawSprite(24, 82, work->gfx3, work->tiles4, work->palette2, NULL, 0, 20);
            DrawSprite(24, 82, work->gfx4, work->tiles5, work->palette3, NULL, 0, 21);
            DrawTextSlots(10, 116, work->textSlots4, work->palette4, 20, work->textSlotCount4);
        }

        break;
    case 7:
        DrawDeckExchangeDeckNames(work, 1);
        DrawSprite((work->x2 >> 8) - 16, (work->y2 >> 8) - 20, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);

        if (work->tiles4 != NULL) {
            DrawSprite(164, 82, work->gfx3, work->tiles4, work->palette2, NULL, 0, 20);
            DrawSprite(164, 82, work->gfx4, work->tiles5, work->palette3, NULL, 0, 21);

            if (work->tiles6 != NULL) {
                DrawSprite(164, 82, work->gfx5, work->tiles6, work->palette2, NULL, 0, 19);
            }

            DrawTextSlots(100, 116, work->textSlots4, work->palette4, 20, work->textSlotCount4);
        }

        break;
    case 5:
        DrawSprite((work->x2 >> 8) - 26, (work->y2 >> 8) - 13, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);
        DrawDeckExchangeDeckNames(work, 1);

        if (work->tiles4 != NULL) {
            DrawSprite(24, 82, work->gfx3, work->tiles4, work->palette2, NULL, 0, 20);
            DrawSprite(24, 82, work->gfx4, work->tiles5, work->palette3, NULL, 0, 21);
            DrawTextSlots(10, 116, work->textSlots4, work->palette4, 20, work->textSlotCount4);
        }

        break;
    case 6:
        DrawDeckExchangeDeckNames(work, 1);

        if (work->tiles4 != NULL) {
            DrawSprite(24, 82, work->gfx3, work->tiles4, work->palette2, NULL, 0, 20);
            DrawSprite(24, 82, work->gfx4, work->tiles5, work->palette3, NULL, 0, 21);
            DrawTextSlots(10, 116, work->textSlots4, work->palette4, 20, work->textSlotCount4);
        }

        break;
    case 8:
        DrawDeckExchangeDeckNames(work, 1);

        if (work->tiles4 != NULL) {
            DrawSprite(164, 82, work->gfx3, work->tiles4, work->palette2, NULL, 0, 20);
            DrawSprite(164, 82, work->gfx4, work->tiles5, work->palette3, NULL, 0, 21);

            if (work->tiles6 != NULL) {
                DrawSprite(164, 82, work->gfx5, work->tiles6, work->palette2, NULL, 0, 19);
            }

            DrawTextSlots(100, 116, work->textSlots4, work->palette4, 20, work->textSlotCount4);
        }

        break;
    case 9:
        DrawSprite((work->x2 >> 8) - 16, (work->y2 >> 8) - 20, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);
        DrawDeckExchangeCardDescription(work);

        if (work->tiles4 != NULL) {
            DrawSprite(24, 66, work->gfx3, work->tiles4, work->palette2, NULL, 0, 20);
            DrawSprite(24, 66, work->gfx4, work->tiles5, work->palette3, NULL, 0, 21);
            DrawTextSlots(10, 100, work->textSlots4, work->palette4, 20, work->textSlotCount4);
        }

        break;
    case 11:
        DrawSprite((work->x2 >> 8) - 26, (work->y2 >> 8) - 13, work->gfx2, work->tiles2, work->palette4, NULL, 0, 8);
        DrawDeckExchangeCardDescription(work);

        if (work->tiles4 != NULL) {
            DrawSprite(24, 66, work->gfx3, work->tiles4, work->palette2, NULL, 0, 20);
            DrawSprite(24, 66, work->gfx4, work->tiles5, work->palette3, NULL, 0, 21);
            DrawTextSlots(10, 100, work->textSlots4, work->palette4, 20, work->textSlotCount4);
        }

        break;
    }

    TaskPoolDraw(&work->tasks);
    TaskPoolDraw(&work->tasks2);
}

void deckexchange_3(DeckExchangeWork* work) {
    ObjPalette** p;

    if (work->tiles8 != NULL) {
        ReleaseObjTiles(work->tiles8);
    }

    if (work->palette5 != NULL) {
        ReleaseObjPalette(work->palette5);
    }

    if (work->tiles9 != NULL) {
        ReleaseObjTiles(work->tiles9);
    }

    if (work->palette6 != NULL) {
        ReleaseObjPalette(work->palette6);
    }

    if (work->palette7 != NULL) {
        ReleaseObjPalette(work->palette7);
    }

    p = &work->palette4;

    if (*p != NULL) {
        ReleaseObjPalette(*p);
    }

    ReleaseDeckExchangeCardPreview(work);
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles3);
    ReleaseObjPalette(work->palette);
    FreeTextSlots(work->textSlots, 8);
    FreeTextSlots(work->textSlots2, 8);
    FreeTextSlots(work->textSlots3, 8);
    FreeTextSlots(work->textSlots4, 30);
    FreeTextSlots(work->textSlots5, 90);
    ReleaseObjPalette(*p);
    TaskPoolDestroy(&work->tasks);
    TaskPoolDestroy(&work->tasks2);
    FreeDeckExchangeCollectionEntries(work);
    *work->resultOut = 6;
}

void CreateDeckExchangeDeckGridCards(DeckExchangeWork* work, u8 kind) {
    DeckCard2Args args;
    u16* cards;
    u8 i;
    s8 x;
    s8 y;

    cards = GetDeck(work->deckIndex)->cards;
    x = 0;
    y = 0;

    for (i = 0; i < DECK_SIZE; i++) {
        if (cards[i] != 0xFFFF) {
            if (kind == 0) {
                args.pool = &work->pool;
                args.cardId = gCardCollection[cards[i]] & 0x8FFF;
                args.col = x;
                args.row = y;
                args.panel = 0;
                args.slot = &cards[i];
                TaskCreate(&work->tasks, &gTaskDescDeckCard2, &args);
                x++;
            } else if (gCardDefs[gCardCollection[cards[i]] & CARD_ID_MASK].category == kind - 1) {
                args.pool = &work->pool;
                args.cardId = gCardCollection[cards[i]] & 0x8FFF;
                args.col = x;
                args.row = y;
                args.panel = 0;
                args.slot = &cards[i];
                TaskCreate(&work->tasks, &gTaskDescDeckCard2, &args);
                x++;
            }

            if (x > 2) {
                x = 0;
                y++;
            }
        }
    }

    work->x = 0x4800;
    work->y = 0x2800;
    work->scrollRowEnd = 4;
    SetDeckExchangeGridRowCount(work, y * 3 + x);
}

s32 CreateDeckExchangeCollectionGridCards(DeckExchangeWork* work, u8 kind, u8 c) {
    DeckCard2Args args;
    u16 i;
    s8 x;
    s8 y;

    x = 0;
    y = 0;

    for (i = 0; i < work->entryCount; i++) {
        if (kind == 5) {
            if (work->entries[i].kind <= 77) {
                args.pool = &work->pool;
                args.cardId = GetCardIdForKind(work->entries[i].kind);
                args.col = x;
                args.row = y;
                args.panel = 1;
                args.slot = NULL;
                TaskCreate(&work->tasks, &gTaskDescDeckCard2, &args);
                x++;
            }
        } else {
            args.pool = &work->pool;
            args.cardId = GetCardIdForKind(work->entries[i].kind);

            if (gCardDefs[args.cardId].category == kind - 1 && work->entries[i].kind <= 77) {
                args.col = x;
                args.row = y;
                args.panel = 1;
                args.slot = NULL;
                TaskCreate(&work->tasks, &gTaskDescDeckCard2, &args);
                x++;
            }
        }

        if (x > 2) {
            x = 0;
            y++;
        }
    }

    work->x = 0xA000;
    work->y = 0x2800;
    work->scrollRowEnd = 4;
    SetDeckExchangeGridRowCount(work, y * 3 + x);
}

s32 GetCardIdForKind(s32 a) {
    u32 i;

    for (i = 0; i < 950; i++) {
        if (gCardDefs[i].kind == a) {
            return i;
        }
    }
}

void ClearDeckExchangeCardGrid(DeckExchangeWork* work) {
    DeckCard2Work* node;

    node = ListPoolFirst(&work->pool);

    while (node != NULL) {
        node->done = 1;
        node = ListPoolNext(&node->node);
    }

    TaskPoolUpdate(&work->tasks);
}

void ScrollDeckExchangeGridDown(DeckExchangeWork* work) {
    DeckCard2Work* node;

    node = ListPoolFirst(&work->pool);

    if (work->scrollRowEnd == 33) {
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
    work->scrollRowEnd++;
    work->y += 0x300;

    if (work->y > 0x7C00) {
        work->y = 0x7C00;
    }

    if (work->holding != 0) {
        work->heldRow--;
    }
}

u8 ScrollDeckExchangeGridUp(DeckExchangeWork* work) {
    DeckCard2Work* node;

    node = ListPoolFirst(&work->pool);

    if (node == NULL) {
        work->y -= 0x300;

        if (work->y < 0x2800) {
            work->y = 0x2800;
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
    work->scrollRowEnd--;
    work->y -= 0x300;

    if (work->y < 0x2800) {
        work->y = 0x2800;
    }

    return 1;
}

void SetDeckExchangeHandAnim(DeckExchangeWork* work) {
    u16 t;

    switch (work->view) {
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
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        work->handFlags &= ~SPRITE_FLAG_HFLIP;
        break;
    case 1:
    case 3:
        AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);
        t = work->handFlags | SPRITE_FLAG_HFLIP;
        work->handFlags = t;
        break;
    }
}

void HighlightDeckExchangeDeckTab(DeckExchangeWork* work, u8 b) {
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
        work->x4 = 100;
        work->y4 = 25;
        work->x5 = 102;
        work->y5 = 75;
        work->x6 = 102;
        work->y6 = 122;
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
        work->x4 = 102;
        work->y4 = 27;
        work->x5 = 100;
        work->y5 = 73;
        work->x6 = 102;
        work->y6 = 122;
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
        work->x4 = 102;
        work->y4 = 27;
        work->x5 = 102;
        work->y5 = 75;
        work->x6 = 100;
        work->y6 = 121;
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

void LoadDeckExchangeDeckNameTexts(DeckExchangeWork* work) {
    InitTextSlots(work->textSlots, 8);
    InitTextSlots(work->textSlots2, 8);
    InitTextSlots(work->textSlots3, 8);
    work->textSlotCount = LoadTextSlots(GetDeckName(0), work->textSlots);
    work->textSlotCount2 = LoadTextSlots(GetDeckName(1), work->textSlots2);
    work->textSlotCount3 = LoadTextSlots(GetDeckName(2), work->textSlots3);
}

void LoadDeckExchangeCardNameText(DeckExchangeWork* work, s32 id) {
    const CardDef* def;

    def = &gCardDefs[id];
    work->textSlotCount4 = LoadTextSlots(def->name, work->textSlots4);

    switch (def->category) {
    case 0:
        LoadPalette(gUnk_09614458, (void*)(work->palette4->index * 32 + OBJ_PLTT),
                    work->palette4->count << 5);
        break;
    case 1:
        LoadPalette(gUnk_09614478, (void*)(work->palette4->index * 32 + OBJ_PLTT),
                    work->palette4->count << 5);
        break;
    case 2:
        LoadPalette(gUnk_09614498, (void*)(work->palette4->index * 32 + OBJ_PLTT),
                    work->palette4->count << 5);
        break;
    case 3:
        LoadPalette(gUnk_096144B8, (void*)(work->palette4->index * 32 + OBJ_PLTT),
                    work->palette4->count << 5);
        break;
    }
}

void ShowDeckExchangeCardPreview(DeckExchangeWork* work) {
    DeckCard2Work* node;
    const CardDef* def;
    s32 id;
    u8 i;
    u8 j;
    void* dst;

    id = 0xFFFF;
    node = ListPoolFirst(&work->pool);

    while (node != NULL) {
        if (node->args.row == work->cursorRow && node->args.col == work->cursorCol) {
            id = node->args.cardId;
            break;
        }

        node = ListPoolNext(&node->node);
    }

    ReleaseDeckExchangeCardPreview(work);

    if (id != 0xFFFF) {
        def = &gCardDefs[id & CARD_ID_MASK];
        work->tiles4 = LoadObjTiles(gCardBacks[def->category].tiles, 0x300);
        work->tiles5 = LoadObjTiles(def->tiles, 0x200);
        work->palette3 = LoadObjPalette(def->palette, 32);
        work->palette2 = LoadObjPalette(gCard00Palette, 32);
        work->gfx3 = gCardBacks[def->category].gfx;
        work->gfx4 = def->gfx;

        for (i = 0; i < work->entryCount; i++) {
            if (work->entries[i].kind == def->kind) {
                break;
            }
        }

        work->entryIndex = i;
        dst = gUnk_05000160;
        LoadPalette(&gUnk_09614118[def->category * 16 + 0x100], dst, 32);

        for (j = 0; j < 10; j++) {
            DrawValueCount(work->entries[i].valueCounts[j], j);
        }

        LoadDeckExchangeCardNameText(work, id);
        LoadDeckExchangeCardDescriptionText(work, id);

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

void ReleaseDeckExchangeCardPreview(DeckExchangeWork* work) {
    if (work->tiles7 != NULL) {
        ReleaseObjTiles(work->tiles7);
        work->tiles7 = NULL;
    }

    if (work->tiles4 != NULL) {
        ReleaseObjTiles(work->tiles4);
        ReleaseObjPalette(work->palette2);
        ReleaseObjTiles(work->tiles5);
        ReleaseObjPalette(work->palette3);

        if (work->tiles6 != NULL) {
            ReleaseObjTiles(work->tiles6);
            work->tiles6 = NULL;
        }

        work->tiles4 = NULL;
        work->palette2 = NULL;
        work->tiles5 = NULL;
        work->palette3 = NULL;
    }
}

void DrawDeckExchangeValueCpCost(DeckExchangeWork* work) {
    DrawDeckExchangeCpCost(GetCardCpCost(
        GetCardIdForKind(work->entries[work->entryIndex].kind) +
        work->cursorCol * 5 + (u16)work->cursorRow));
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

s32 MoveDeckExchangeValueCursor(DeckExchangeWork* work, u16 key) {
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

    idx = work->cursorCol * 5 + (u8)work->cursorRow;
    tbl = (u8*)&work->entries[work->entryIndex];
    row0 = work->cursorCol;
    r0 = work->cursorCol;
    c0 = work->cursorRow;

    if (*(u16*)&tbl[idx << 1] != 0) {
        return 1;
    }

    switch (key) {
    case 0x40:
        do {
            if (work->cursorRow > 0) {
                work->cursorRow = work->cursorRow - 1;
            } else {
                work->cursorRow = 4;
            }

            idx = work->cursorCol * 5 + (u8)work->cursorRow;

            if (work->cursorCol == r0 && work->cursorRow == c0) {
                return 0;
            }
        } while (*(u16*)&tbl[idx << 1] == 0);

        break;
    case 0x80:
        do {
            if (work->cursorRow <= 3) {
                work->cursorRow = work->cursorRow + 1;
            } else {
                work->cursorRow = 0;
            }

            idx = work->cursorCol * 5 + (u8)work->cursorRow;

            if (work->cursorCol == r0 && work->cursorRow == c0) {
                return 0;
            }
        } while (*(u16*)&tbl[idx << 1] == 0);

        break;
    case 0x20:
        if (*(u16*)&tbl[work->cursorRow << 1] != 0) {
            if ((s16)row0 > 0) {
                work->cursorCol = row0 - 1;
            }

            return 1;
        }

        sum = 0;

        for (i = 0; i < 5; i++) {
            sum += *(u16*)&tbl[i * 2];
        }

        if (sum == 0) {
            work->cursorCol = 1;
            return 0;
        }

        p = (u8*)&work->cursorRow;
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

        work->cursorRow = n;
        break;
    case 0x10:
        if (*(u16*)&tbl[(work->cursorRow + 5) << 1] != 0) {
            if ((s16)row0 <= 0) {
                work->cursorCol = row0 + 1;
            }

            return 1;
        }

        sum = 0;

        for (i = 5; i < 10; i++) {
            sum += *(u16*)&tbl[i * 2];
        }

        if (sum == 0) {
            work->cursorCol = 0;
            return 0;
        }

        p = (u8*)&work->cursorRow;
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

        work->cursorRow = n;
        break;
    case 0:
        do {
            if (work->cursorRow <= 3) {
                work->cursorRow = work->cursorRow + 1;
            } else {
                work->cursorRow = 0;
            }

            idx = work->cursorCol * 5 + (u8)work->cursorRow;

            if (work->cursorCol == r0 && work->cursorRow == c0) {
                if (work->cursorCol <= 0) {
                    work->cursorCol = work->cursorCol + 1;
                } else {
                    work->cursorCol = 0;
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

void FreeDeckExchangeCollectionEntries(DeckExchangeWork* work) {
    u16 i;

    if (work->entries != NULL) {
        for (i = 0; i < work->entryCount; i++) {
            EwramFree(work->entries[i].indices);
        }

        EwramFree(work->entries);
        work->entries = NULL;
    }
}

void SetDeckExchangeFrameCursor(DeckExchangeWork* work, u8 kind) {
    switch (kind) {
    case 0:
        SetObjTileSource(work->tiles2, gUnk_090A4A0C);
        AnimInit(&work->anim2, gUnk_09EEB064, gUnk_09EEB050);
        AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
        work->gfx2 = AnimGetGfx(&work->anim2);
        break;
    case 1:
        SetObjTileSource(work->tiles2, gUnk_090A51F6);
        AnimInit(&work->anim2, gUnk_09EEB07C, gUnk_09EEB068);
        AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
        work->gfx2 = AnimGetGfx(&work->anim2);
        break;
    }
}

s32 TakeTradeCard(DeckExchangeWork* work) {
    u16 idx;
    CardKindEntry* e;
    u16 i;
    s32 card;
    u16 id;
    const CardDef* def;
    u16 kind;

    idx = work->cursorCol * 5 + work->cursorRow;
    e = &work->entries[work->entryIndex];

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

s32 CheckDeckExchangeCpCost(DeckExchangeWork* work) {
    if (GetDeckCpCost(GetActiveDeckIndex()) > gGameState.progression.cp) {
        TaskCreate(&work->tasks2, &gTaskDescDeckErrorCp, &work->popupActive);
        m4aSongNumStart(SONG_SYS_BEEP);

        return 0;
    }

    return 1;
}

u8 CheckDeckExchangeHasAttackCard(DeckExchangeWork* work) {
    if (CountActiveDeckCardsOfCategory(0) == 0) {
        m4aSongNumStart(SONG_SYS_BEEP);
        TaskCreate(&work->tasks2, &gTaskDescDeckErrorNoAttackCard, &work->popupActive);
        return 0;
    }

    return 1;
}

void ResetDeckExchangeGridScroll(DeckExchangeWork* work) {
    DeckCard2Work* node;
    s16 x;
    s16 y;

    node = ListPoolFirst(&work->pool);
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

    work->y = 0x2800;
    work->scrollRowEnd = 4;
}

u8 IsDeckExchangeCardAtCursor(DeckExchangeWork* work) {
    DeckCard2Work* node;

    node = ListPoolFirst(&work->pool);

    while (node != NULL) {
        if (node->args.col == work->cursorCol &&
            node->args.row == work->cursorRow) {
            return 1;
        }

        node = ListPoolNext(&node->node);
    }

    return 0;
}

u8 IsDeckExchangeCardAt(DeckExchangeWork* work, s16 x, s16 y) {
    DeckCard2Work* node;

    node = ListPoolFirst(&work->pool);

    while (node != NULL) {
        if (node->args.col == x && node->args.row == y) {
            return 1;
        }

        node = ListPoolNext(&node->node);
    }

    return 0;
}

u8 FindDeckExchangeCardInDirection(DeckExchangeWork* work, s16 x, s16 y, u16 dir) {
    DeckCard2Work* n;

    for (n = ListPoolFirst(&work->pool); n != NULL; n = ListPoolNext(&n->node)) {
        if (n->args.col == x && n->args.row == y) {
            return 1;
        }
    }

    switch (dir) {
    case 0x40:
        return FindDeckExchangeCardInDirection(work, x, y - 1, 0x40);
    case 0x80:
        return FindDeckExchangeCardInDirection(work, x, y + 1, 0x80);
    case 0x20:
        return FindDeckExchangeCardInDirection(work, x - 1, y, 0x20);
    case 0x10:
        return FindDeckExchangeCardInDirection(work, x + 1, y, 0x10);
    }

    return 0;
}

void LoadDeckExchangeCardDescriptionText(DeckExchangeWork* work, u16 index) {
    const CardDef* d;

    d = &gCardDefs[index];
    work->textSlotCount5 = LoadTextSlots((void*)gCardKindDescriptions[d->kind], work->textSlots5);
}

void SetDeckExchangeGridRowCount(DeckExchangeWork* work, s16 n) {
    work->rowCount = n / 3;

    if (n % 3 != 0) {
        work->rowCount = n / 3 + 1;
    }
}

void UpdateDeckExchangeGridScrollBar(DeckExchangeWork* work) {
    s32 t;

    t = 0x5400 / (work->rowCount - 4);
    work->y = t * (work->scrollRowEnd - 4) + 0x2800;

    if (work->y > 0x7C00) {
        work->y = 0x7C00;
    }

    if (work->y < 0x2800) {
        work->y = 0x2800;
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
