/**
 * card_deckmenu2_riku.c
 * Riku Deck Menu
 */

#include "card_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "m4a_song.h"
#include "game_state.h"
#include "text.h"
#include "monsgage.h"
#include "fade.h"
#include "obj_api.h"
#include "display.h"
#include "engine_math.h"
#include "listpool.h"
#include "anim.h"
#include "obj.h"
#include "taskpool.h"
#include "key.h"
#include "malloc.h"
#include "card.h"
#include "sprites_deck_menu.h"
#include "sprites_card_pictures.h"
#include "gba/keys.h"
#include "songs.h"
#include "card_api.h"
#include "card_def_data.h"
#include "card_types.h"
#include "gba/defines.h"
#include "mode_battle_data.h"
#include "player_progression_types.h"
#include "types.h"
#include <stddef.h>
#include "card_deckmenu2_riku.h"
#include "ms_charge.h"
#include "card_map_anim.h"
#include "card_deckmenu2.h"

#ifdef VERSION_EU
static const u16 sRikuDeckTitleBannerTileSizes[5] = { 0x320, 0x320, 0x320, 0x320, 0x320 };
#endif

static const s16 sRikuDeckTabPointerX[3] = { 116, 116, 116 };

static const s16 sRikuDeckTabPointerY[3] = { 56, 104, 148 };

const s16 gUnk_09041EC0[5] = { 12, 28, 42, 56, 70 };

const s16 gRikuDeckFilterTabX[6] = { 172, 172, 188, 202, 216, 230 };

const s16 gUnk_09041ED6[5] = { 64, 82, 100, 118, 136 };

const s16 gRikuDeckValueGridX[2] = { 80, 128 };

const s16 gRikuDeckValueGridY[5] = { 80, 88, 96, 104, 112 };

static const u16 sUnk_09041EEE[4] = { 45, 93, 141, 30 };

static void Deckmenu2_0(RikuDeckMenuWork* work, void* a) {
    u16 v;

    work->resultOut = a;
    SetBgMode0();
    SetBackdropColor(0, 0, 0);
    SetupBg(0, 0, 31, 0);
#ifdef VERSION_EU
    SetupBg(1, 0, 29, 0);
    SetupBg(2, 0, 28, 0);
#else
    SetupBg(1, 2, 23, 0);
    SetupBg(2, 1, 15, 0);
#endif
    SetupBg(3, 0, 30, 0);
    RequestDma3Clear(GetBgCharBase(0), 0x4000);
    RequestDma3Clear(GetBgCharBase(1), 0x4000);
    RequestDma3Clear(GetBgCharBase(2), 0x4000);
    RequestDma3Clear(GetBgCharBase(3), 0x4000);
    SetBgPriority(0, 0);
    SetBgPriority(1, 1);
    SetBgPriority(2, 2);
    FadeStartIn(FADE_MODE_BLACK, 16);
    ListPoolInit(&work->pool);
    TaskPoolInit(&work->taskpool, 99);
    TaskPoolInit(&work->cardpool, 1);
    work->deckIndex = GetActiveDeckIndex();
    CreateRikuDeckGridCards(work, 0);
    work->tiles = AllocObjTiles(0x120, NULL);
    SetObjTileSource(work->tiles, gUnk_090A4664);
    AnimInit(&work->anim2, gUnk_09EEB03C, gUnk_09EEB008);
    AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim2);
    work->x = sRikuDeckTabPointerX[0] << 8;
    work->y = sRikuDeckTabPointerY[0] << 8;
    work->handFlags = 0;
    work->tiles4 = LoadObjTiles(gUnk_090A44C4, 32);
    work->palette = LoadObjPalette(gUnk_09614418, 32);
    work->handVisible = 0;
    work->tiles2 = AllocObjTiles(0x280, NULL);
    SetRikuDeckMenuFrameCursor(work, 0);
    work->palette4 = LoadObjPalette(gUnk_09614438, 32);
    work->tiles10 = NULL;
    work->tiles7 = NULL;
    work->tiles8 = NULL;
    work->tiles9 = NULL;
    work->palette5 = NULL;
    work->palette6 = NULL;
    work->tiles3 = NULL;
    work->palette2 = NULL;
    work->cursorCol = 0;
    work->cursorRow = 0;
    work->prevCursorCol = 0;
    work->prevCursorRow = 0;
    work->timer = 4;
    work->commandCursor = 0;
    work->cursorCard = NULL;
    work->prevCursorCard = NULL;
    work->mode = 0;
    work->view = 0;
    work->deckAttackCount = CountActiveDeckCardsOfCategory(0);
    work->deckMagicCount = CountActiveDeckCardsOfCategory(1);
    work->deckItemCount = CountActiveDeckCardsOfCategory(2);
    work->deckEnemyCount = CountActiveDeckCardsOfCategory(3);
    work->categoryFilter = 0;
    work->entryCount = 0;
    work->entries = NULL;
    work->popupActive = 0;
    work->exitRequested = 0;
    work->barSlideTimer = 16;
    work->bannerSlideTimer = 16;
    work->x5 = 0x7800;
    work->y5 = -0x800;
    work->x6 = 0xA400;
    work->y6 = 0xA000;
    work->x7 = -0x8000;
    work->holding = 0;
#ifdef VERSION_EU
    work->tiles12 = LoadObjTiles(gRikuDeckTitleBannerTiles[gLanguage], sRikuDeckTitleBannerTileSizes[gLanguage]);
#else
    work->tiles12 = LoadObjTiles(gUnk_090A418E, 0x320);
#endif
    work->tiles6 = LoadObjTiles(gUnk_090A583E, 0x620);
    work->palette3 = LoadObjPalette(gUnk_096144F8, 32);
    work->unk_4BC = 79;
    v = sUnk_09041EEE[work->deckIndex];
    work->unk_4BE = v;
    work->unk_4C0 = 225;
    v = sUnk_09041EEE[work->deckIndex];
    work->unk_4C2 = v;
    work->unk_503 = 0;
    work->inputDelay = 0;
    work->textSlotCount = 0;
    work->textSlotCount2 = 0;
    work->textSlotCount3 = 0;
    work->textSlotCount4 = 0;
    work->result = 0;
    InitTextSlots(work->textSlots, 8);
    InitTextSlots(work->textSlots2, 8);
    InitTextSlots(work->textSlots3, 8);
    InitTextSlots(work->textSlots4, 30);
    InitTextSlots(work->textSlots5, 60);
    work->descriptionX = 94;
    work->descriptionY = 126;
    work->previewShown = 0;
}

void DrawRikuCardDescription(RikuDeckMenuWork* work) {
    DrawTextSlots(work->descriptionX, work->descriptionY, work->textSlots5,
                  work->palette, 20, work->textSlotCount5);
}

void LoadRikuCardDescriptionText(RikuDeckMenuWork* work, u16 card) {
    const CardDef* d;
    void* s;

    d = &gCardDefs[card];
    s = gCardKindDescriptions[d->kind];
    work->textSlotCount5 = LoadTextSlots(LANGSTR(s), work->textSlots5);
}

u8 UpdateRikuDeckMenuLoadBgs(RikuDeckMenuWork* work, void* a) {
#ifdef VERSION_EU
    LoadBgTiles(3, gUnk_09402F78, 0x5400);

    switch (gLanguage) {
    case LANGUAGE_FRENCH:
        RequestDma3Copy(gUnkEu_094E20E4, (u8*)GetBgCharBase(3) + 0x3800, 0x1C00);
        break;
    case LANGUAGE_GERMAN:
        RequestDma3Copy(gUnkEu_094E74E4, (u8*)GetBgCharBase(3) + 0x3800, 0x1C00);
        break;
    case LANGUAGE_ITALIAN:
        RequestDma3Copy(gUnkEu_094E58E4, (u8*)GetBgCharBase(3) + 0x3800, 0x1C00);
        break;
    case LANGUAGE_SPANISH:
        RequestDma3Copy(gUnkEu_094E3CE4, (u8*)GetBgCharBase(3) + 0x3800, 0x1C00);
        break;
    }

    LoadBgPalette(3, gUnk_09614118, 0x1E0);
    LoadBgMap(3, gUnk_0951B2B8, 0x800);
    LoadBgMap(0, gUnk_08125E24, 0x800);
    LoadBgMap(1, gUnk_08125E24, 0x800);
    LoadBgMap(2, gUnk_08125E24, 0x800);
#else
    LoadBgTiles(3, gUnk_09402F78, 0x4000);
    LoadBgPalette(3, gUnk_09614118, 0x1E0);
    LoadBgMap(3, gUnk_0951B2B8, 0x800);
    LoadBgMap(0, gUnk_08125E24, 0x800);
    LoadBgTiles(1, gUnk_09406F78, 0xC00);
    LoadBgMap(1, gUnk_08125E24, 0x800);
    LoadBgMap(2, gUnk_08125E24, 0x800);
#endif
    SetBgScroll(0, (u16)-88, (u16)-108);
    SetBgScroll(1, (u16)-88, (u16)-16);
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuLoadDeckInfo);
    return 1;
}

u8 UpdateRikuDeckMenuLoadDeckInfo(RikuDeckMenuWork* work, void* a) {
    u8* base;
    u16* pal;

    base = GetBgCharBase(1);
    pal = (u16*)(BG_PLTT + 8 * PLTT_SIZE_4BPP);
    LoadPalette(gUnk_096142F8, pal, 32);
#ifdef VERSION_EU
    RequestDma3Copy(gRikuDeckEquipMarkerTiles[gLanguage] + 0x20, base + 0x2D80, 0x1E0);
    LoadBgMap(0, gUnk_095172B8, 0x800);
    LoadBgMap(1, gUnk_09516AB8, 0x800);
#else
    RequestDma3Copy(gUnk_0940FC58, base + 0x1A0, 0x1E0);
    LoadBgMap(0, gUnk_09516AB8 + 0x400, 0x800);
    LoadBgMap(1, gUnk_0951B2B8 + 0x400, 0x800);
#endif
    DrawRikuDeckCategoryCount(work->deckAttackCount, 0);
    DrawRikuDeckCategoryCount(work->deckMagicCount, 1);
    DrawRikuDeckCategoryCount(work->deckItemCount, 2);
    DrawRikuDeckCategoryCount(work->deckEnemyCount, 3);
    DrawRikuDeckCardCount(0);
    DrawRikuCardTotals();
    work->x2 = 0x4800;
    work->y2 = 0x2800;
    work->cursorRow = work->deckIndex;
    ApproachValue(&work->x, sRikuDeckTabPointerX[work->cursorCol] << 8, work->timer);
    ApproachValue(&work->y, sRikuDeckTabPointerY[work->cursorRow] << 8, work->timer);
    work->view = 1;
    SetRikuDeckMenuHandAnim(work);
    LoadRikuDeckNameTexts(work);
    work->step = 0;
    work->timer = 16;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuSlideIn);
    return 1;
}

u8 UpdateRikuDeckMenuSlideIn(RikuDeckMenuWork* work, void* a) {
    u8 n;

    if (!FadeIsActive()) {
        switch (work->step) {
        case 0:
            ApproachValue(&work->y5, 0, work->timer);
            ApproachValue(&work->y6, 0x9800, work->timer);
            work->timer--;

            if (work->timer == 0) {
                work->timer = 16;
                work->step++;
            }

            break;
        case 1:
            ApproachValue(&work->x7, 0, work->timer);
            n = --work->timer;

            if (n == 0) {
                LoadBgMap(3, gUnk_095162B8, 0x800);
                ReleaseObjTiles(work->tiles12);
                work->tiles12 = NULL;
                ReleaseObjTiles(work->tiles6);
                work->tiles6 = NULL;
                ReleaseObjPalette(work->palette3);
                work->palette3 = NULL;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuEnterDeckGrid);
            }

            break;
        }
    }

    return 1;
}

u8 UpdateRikuDeckMenuEnterDeckGrid(RikuDeckMenuWork* work, void* a) {
    work->x = gDeckGridColumnX[work->cursorCol] << 8;
    work->y = gDeckGridRowY[work->cursorRow] << 8;
    work->view = 0;
    SetRikuDeckMenuHandAnim(work);
    ShowRikuDeckCardPreview(work);
    work->handVisible = 1;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuDeckGrid);
    return 1;
}

u8 UpdateRikuDeckMenuDeckGrid(RikuDeckMenuWork* work, void* a) {
    u16 x;

    work->gfx = AnimUpdate(&work->anim2);
    work->gfx2 = AnimUpdate(&work->anim3);

    if (FadeIsActive()) {
        TaskPoolUpdate(&work->taskpool);
        return 1;
    }

    if (work->popupActive != 0) {
        ApproachValue(&work->x, gDeckGridColumnX[work->cursorCol] << 8, work->timer);
        ApproachValue(&work->y, gDeckGridRowY[work->cursorRow] << 8, work->timer);

        if (work->timer != 0) {
            work->timer--;
        }

        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            work->exitRequested = 1;
        }

        work->inputDelay = 4;
        return 1;
    }

    if (work->inputDelay > 0) {
        TaskPoolUpdate(&work->taskpool);
        TaskPoolUpdate(&work->cardpool);
        work->inputDelay--;
        return 1;
    }

    if (work->exitRequested) {
        if (CheckRikuDeckCpCost(work) && CheckRikuDeckHasAttackCard(work)) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuFadeOut);
            FadeStartOut(FADE_MODE_BLACK, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        work->exitRequested = 0;
    }

    switch (GetKeysRepeat()) {
    case DPAD_UP:
        if (work->cursorRow > 0) {
            (work->cursorRow)--;
            work->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        } else {
            ScrollRikuGridUp(work);
        }

        ShowRikuDeckCardPreview(work);
        break;
    case DPAD_DOWN:
        if (work->cursorRow <= 2) {
            (work->cursorRow)++;
            work->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        } else {
            ScrollRikuGridDown(work);

            if (work->holding != 0) {
                if ((u16)work->heldRow <= 3) {
                    work->y3 = gDeckGridRowY[work->heldRow] << 8;
                } else {
                    work->y3 = 0xFFFF0000;
                }
            }
        }

        ShowRikuDeckCardPreview(work);
        break;
    case DPAD_LEFT:
        if (work->cursorCol > 0) {
            (work->cursorCol)--;
            work->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        ShowRikuDeckCardPreview(work);
        break;
    case DPAD_RIGHT:
        if (work->cursorCol <= 1) {
            (work->cursorCol)++;
            work->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        ShowRikuDeckCardPreview(work);
        break;
    case START_BUTTON:
        work->result = 7;
        m4aSongNumStart(SONG_SYS_CANSEL);
        FadeStartOut(FADE_MODE_BLACK, 4);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuFadeOut);
        return 1;
    case B_BUTTON:
        work->result = 8;
        m4aSongNumStart(SONG_SYS_CANSEL);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuStartSlideOut);
        return 1;
    }

    work->cursorCard = GetRikuCardAtCursor(work);
    ApproachValue(&work->x, gDeckGridColumnX[work->cursorCol] << 8, work->timer);
    ApproachValue(&work->y, gDeckGridRowY[work->cursorRow] << 8, work->timer);

    if (work->timer != 0) {
        work->timer--;
    }

    work->prevCursorCard = work->cursorCard;
    x = work->cursorCol;
    work->prevCursorCol = x;
    x = work->cursorRow;
    work->prevCursorRow = x;
    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

s32 UpdateRikuDeckMenuFadeOut(RikuDeckMenuWork* work) {
    if (!FadeIsActive()) {
        return 0;
    }

    TaskPoolUpdate(&work->taskpool);
    TaskPoolUpdate(&work->cardpool);
    return 1;
}

u8 UpdateRikuDeckMenuStartSlideOut(RikuDeckMenuWork* work, void* a) {
#ifdef VERSION_EU
    work->tiles12 = LoadObjTiles(gRikuDeckTitleBannerTiles[gLanguage], sRikuDeckTitleBannerTileSizes[gLanguage]);
#else
    work->tiles12 = LoadObjTiles(gUnk_090A418E, 0x320);
#endif
    work->tiles6 = LoadObjTiles(gUnk_090A583E, 0x620);
    work->palette3 = LoadObjPalette(gUnk_096144F8, 32);
    LoadBgMap(3, gUnk_0951B2B8, 0x800);
    work->x5 = 0x7800;
    work->y5 = 0;
    work->x6 = 0xA400;
    work->y6 = 0x9800;
    work->x7 = 0;
    work->barSlideTimer = 16;
    work->bannerSlideTimer = 16;
    work->handVisible = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuSlideOut);
    return 1;
}

u8 UpdateRikuDeckMenuSlideOut(RikuDeckMenuWork* work, void* a) {
    u8* p;

    p = &work->bannerSlideTimer;

    if ((s8)*p > 0) {
        ApproachValue(&work->x7, -0x8000, (s8)*p);
        (*p)--;
    } else {
        p = &work->barSlideTimer;

        if ((s8)*p > 0) {
            ApproachValue(&work->y5, -0x800, (s8)*p);
            ApproachValue(&work->y6, 0xA000, (s8)*p);
            (*p)--;
        } else {
            FadeStartOut(FADE_MODE_BLACK, 4);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuFadeOut);
        }
    }

    return 1;
}

static void Deckmenu2_2(RikuDeckMenuWork* work) {
    if (work->tiles12 != NULL) {
#ifdef VERSION_EU
        DrawSprite(work->x7 >> 8, 0, gRikuDeckTitleBannerSprites[gLanguage][0], work->tiles12, work->palette3, NULL, 0, 10);
#elif defined(VERSION_JP)
        DrawSprite(work->x7 >> 8, 0, gUnk_09EEAFF0[0], work->tiles12, work->palette3, NULL, 0, 10);
#else
        DrawSprite(work->x7 >> 8, 0, gUnk_09EEAFF8[0], work->tiles12, work->palette3, NULL, 0, 10);
#endif
    }

    if (work->tiles6 != NULL) {
        DrawSprite(work->x5 >> 8, work->y5 >> 8, gUnk_09EEB080[0], work->tiles6,
                   work->palette3, NULL, SPRITE_PRIORITY(3), 10000);
        DrawSprite(work->x6 >> 8, work->y6 >> 8, gUnk_09EEB080[1], work->tiles6,
                   work->palette3, NULL, SPRITE_PRIORITY(3), 10000);
    }

    if (work->handVisible) {
        DrawSprite((work->x >> 8) - 16, (work->y >> 8) - 30, work->gfx,
                   work->tiles, work->palette, NULL, work->handFlags, 3);
        DrawSprite((work->x >> 8) - 16, (work->y >> 8) - 20, work->gfx2,
                   work->tiles2, work->palette4, NULL, 0, 8);
    }

    DrawSprite(work->x2 >> 8, work->y2 >> 8, gUnk_09EEB000[0], work->tiles4,
               work->palette, NULL, SPRITE_PRIORITY(2), 10);

    if (work->tiles7 != NULL) {
        DrawSprite(168, 86, work->gfx4, work->tiles7, work->palette5, NULL, 0, 20);
    }

    if (work->tiles8 != NULL) {
        DrawSprite(168, 86, work->gfx5, work->tiles8, work->palette6, NULL, 0, 21);
    }

    if (work->tiles9 != NULL) {
        DrawSprite(168, 86, work->gfx6, work->tiles9, work->palette5, NULL, 0, 19);
    }

    if (work->previewShown) {
        if (work->textSlotCount4 != 0) {
            DrawTextSlots(100, 112, work->textSlots4, work->palette4, 20, work->textSlotCount4);
        }

        DrawRikuCardDescription(work);
    }

    TaskPoolDraw(&work->taskpool);
    TaskPoolDraw(&work->cardpool);
}

static void Deckmenu2_3(RikuDeckMenuWork* work) {
    ClearRikuCardGrid(work);
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles4);
    ReleaseObjPalette(work->palette);
    ReleaseRikuCommandMenuGfx(work);

    if (work->tiles12 != NULL) {
        ReleaseObjTiles(work->tiles12);
    }

    if (work->tiles6 != NULL) {
        ReleaseObjTiles(work->tiles6);
    }

    if (work->palette3 != NULL) {
        ReleaseObjPalette(work->palette3);
    }

    FreeTextSlots(work->textSlots, 8);
    FreeTextSlots(work->textSlots2, 8);
    FreeTextSlots(work->textSlots3, 8);
    FreeTextSlots(work->textSlots4, 30);
    FreeTextSlots(work->textSlots5, 60);
    ReleaseObjPalette(work->palette4);
    TaskPoolDestroy(&work->taskpool);
    TaskPoolDestroy(&work->cardpool);
    FreeRikuCollectionEntries(work);
    *work->resultOut = work->result;
}

void CreateRikuDeckGridCards(RikuDeckMenuWork* work, u8 kind) {
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
                TaskCreate(&work->taskpool, &gTaskDescDeckCard2, &args);
                x++;
            } else if (gCardDefs[gCardCollection[cards[i]] & CARD_ID_MASK].category == kind - 1) {
                args.pool = &work->pool;
                args.cardId = gCardCollection[cards[i]] & 0x8FFF;
                args.col = x;
                args.row = y;
                args.panel = 0;
                args.slot = &cards[i];
                TaskCreate(&work->taskpool, &gTaskDescDeckCard2, &args);
                x++;
            }

            if (x > 2) {
                x = 0;
                y++;
            }
        }
    }

    work->x2 = 0x4800;
    work->y2 = 0x2800;
    work->scrollRowEnd = 4;
}

void ClearRikuCardGrid(RikuDeckMenuWork* work) {
    DeckCard2Work* node;

    node = ListPoolFirst(&work->pool);

    while (node != NULL) {
        node->done = 1;
        node = ListPoolNext(&node->node);
    }

    TaskPoolUpdate(&work->taskpool);
}

void ScrollRikuGridDown(RikuDeckMenuWork* work) {
    DeckCard2Work* node;

    node = ListPoolFirst(&work->pool);

    if ((s8)work->scrollRowEnd == 33) {
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
    work->y2 += 0x300;

    if (work->y2 > 0x7C00) {
        work->y2 = 0x7C00;
    }

    if (work->holding != 0) {
        work->heldRow--;
    }
}

u8 ScrollRikuGridUp(RikuDeckMenuWork* work) {
    DeckCard2Work* node;

    node = ListPoolFirst(&work->pool);

    if (node == NULL) {
        work->y2 -= 0x300;

        if (work->y2 < 0x2800) {
            work->y2 = 0x2800;
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
    work->y2 -= 0x300;

    if (work->y2 < 0x2800) {
        work->y2 = 0x2800;
    }

    return 1;
}

DeckCard2Work* GetRikuCardAtCursor(RikuDeckMenuWork* work) {
    DeckCard2Work* node;

    node = ListPoolFirst(&work->pool);

    while (node != NULL) {
        if (work->cursorCol == node->args.col &&
            work->cursorRow == node->args.row) {
            return node;
        }

        node = ListPoolNext(&node->node);
    }

    return NULL;
}

void DrawRikuDeckCategoryCount(u8 a, u8 b) {
    u8 d[2];
    u8* base;

    d[0] = a / 10;
    d[1] = a - (u8)(a / 10) * 10;
    base = GetBgCharBase(3);
    RequestDma3Copy(&gUnk_0940F7B8[(d[0] + 1) * 32], base + (b * 64 + 0x360), 32);
    RequestDma3Copy(&gUnk_0940F7B8[(d[1] + 1) * 32], base + (b * 64 + 0x360) + 32, 32);
}

void SetRikuDeckMenuHandAnim(RikuDeckMenuWork* work) {
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
        AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
        work->handFlags &= ~SPRITE_FLAG_HFLIP;
        break;
    case 1:
    case 3:
        AnimStart(&work->anim2, 2, ANIM_FLAG_LOOP);
        t = work->handFlags | SPRITE_FLAG_HFLIP;
        work->handFlags = t;
        break;
    }
}

void DrawRikuDeckCardCount(u8 deck) {
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
        base = GetBgCharBase(1);
        break;
    case 1:
        base = GetBgCharBase(1);
        break;
    case 2:
        base = GetBgCharBase(1);
        break;
    }

#ifdef VERSION_EU
    RequestDma3Copy(&gUnk_0940F938[(d[0] + 1) * 32], base + 0x2C00, 32);
    RequestDma3Copy(&gUnk_0940F938[(d[1] + 1) * 32], base + 0x2C20, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[0] + 1) * 32], base + 0x2C40, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[1] + 1) * 32], base + 0x2C60, 32);
#else
    RequestDma3Copy(&gUnk_0940F938[(d[0] + 1) * 32], base + 0x20, 32);
    RequestDma3Copy(&gUnk_0940F938[(d[1] + 1) * 32], base + 0x40, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[0] + 1) * 32], base + 0x60, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[1] + 1) * 32], base + 0x80, 32);
#endif
}

void DrawRikuCardTotals() {
    u8 d[3];
    u8 e[3];
    u16 a;
    u16 b;
    u8* base;

    a = CountCardsInDecks();
    b = CountCollectionCards();
    d[0] = a / 100;
    d[1] = a / 10 - d[0] * 10;
    d[2] = a - d[0] * 100 - d[1] * 10;
    e[0] = b / 100;
    e[1] = b / 10 - e[0] * 10;
    e[2] = b - e[0] * 100 - e[1] * 10;
    base = GetBgCharBase(3);
    RequestDma3Copy(&gUnk_0940F938[(d[0] + 1) * 32], base + 0x2A0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d[1] + 1) * 32], base + 0x2C0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d[2] + 1) * 32], base + 0x2E0, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[0] + 1) * 32], base + 0x300, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[1] + 1) * 32], base + 0x320, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[2] + 1) * 32], base + 0x340, 32);
}

void LoadRikuDeckNameTexts(RikuDeckMenuWork* work) {
    FreeTextSlots(work->textSlots, 8);
    FreeTextSlots(work->textSlots2, 8);
    FreeTextSlots(work->textSlots3, 8);
    work->textSlotCount = LoadTextSlots(GetDeckName(0), work->textSlots);
    work->textSlotCount2 = LoadTextSlots(GetDeckName(1), work->textSlots2);
    work->textSlotCount3 = LoadTextSlots(GetDeckName(2), work->textSlots3);
}

void LoadRikuCardNameText(RikuDeckMenuWork* work, s32 id) {
    const CardDef* def;

    def = &gCardDefs[id];
#ifdef VERSION_EU
    work->textSlotCount4 = LoadTextSlots(GetLocalizedString(def->name), work->textSlots4);
#else
    work->textSlotCount4 = LoadTextSlots(def->name, work->textSlots4);
#endif

    switch (def->category) {
    case 0:
        LoadPalette(gUnk_09614458,
                    (void*)(work->palette4->index * 32 +
                            OBJ_PLTT),
                    work->palette4->count << 5);
        break;
    case 1:
        LoadPalette(gUnk_09614478,
                    (void*)(work->palette4->index * 32 +
                            OBJ_PLTT),
                    work->palette4->count << 5);
        break;
    case 2:
        LoadPalette(gUnk_09614498,
                    (void*)(work->palette4->index * 32 +
                            OBJ_PLTT),
                    work->palette4->count << 5);
        break;
    case 3:
        LoadPalette(gUnk_096144B8,
                    (void*)(work->palette4->index * 32 +
                            OBJ_PLTT),
                    work->palette4->count << 5);
        break;
    }
}

void ReleaseRikuCardPreview(RikuDeckMenuWork* work) {
    if (work->tiles10 != NULL) {
        ReleaseObjTiles(work->tiles10);
        work->tiles10 = NULL;
    }

    if (work->tiles7 != NULL) {
        ReleaseObjTiles(work->tiles7);
        ReleaseObjPalette(work->palette5);
        ReleaseObjTiles(work->tiles8);
        ReleaseObjPalette(work->palette6);

        if (work->tiles9 != NULL) {
            ReleaseObjTiles(work->tiles9);
            work->tiles9 = NULL;
        }

        work->tiles7 = NULL;
        work->palette5 = NULL;
        work->tiles8 = NULL;
        work->palette6 = NULL;
    }
}

void ShowRikuDeckCardPreview(RikuDeckMenuWork* work) {
    DeckCard2Work* node;
    const CardDef* def;
    void* dst;
    u16 id;
    u32 t;

    id = 0xFFFF;
    node = ListPoolFirst(&work->pool);

    while (node != NULL) {
        if (node->args.row == work->cursorRow && node->args.col == work->cursorCol) {
            id = node->args.cardId;
            break;
        }

        node = ListPoolNext(&node->node);
    }

    ReleaseRikuCardPreview(work);

    if (id != 0xFFFF) {
        if (id & 0x8000) {
            work->tiles10 = AllocObjTiles(0x280, NULL);
            SetObjTileSource(work->tiles10, gUnk_0908B1B4);
            AnimInit(&work->anim, gUnk_09EEA164, gUnk_09EEA148);
            AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
            work->gfx3 = AnimGetGfx(&work->anim);
        }

        t = id & CARD_ID_MASK;
        def = &gCardDefs[t];
        work->tiles7 = LoadObjTiles(gCardBacks[def->category].tiles, 768);
        work->tiles8 = LoadObjTiles(def->tiles, 512);
        work->palette6 = LoadObjPalette(def->palette, 32);
        work->palette5 = LoadObjPalette(gCard00Palette, 32);
        work->gfx4 = gCardBacks[def->category].gfx;
        work->gfx5 = def->gfx;

        if (def->category != 3) {
            work->tiles9 = LoadObjTiles(gUnk_0905EAE8, 480);
            work->gfx6 = gUnk_09EE981C[def->value];
        }

        DrawRikuCpCost(def->cpCost);
        dst = gUnk_05000160;
        LoadPalette(&gUnk_09614118[def->category * 16 + 0x100], dst, 32);
        LoadRikuCardNameText(work, t);
        LoadRikuCardDescriptionText(work, t);
        work->previewShown = 1;
    } else {
        DrawRikuCpCost(0);
        work->previewShown = 0;
    }
}

void DrawRikuCpCost(u8 a) {
    u8 v[2];
    u8* base;

    base = GetBgCharBase(3);

    if (a != 0) {
        v[0] = a / 10;
        v[1] = a - v[0] * 10;
        RequestDma3Copy(&gUnk_0940FA98[(v[0] + 3) * 32], base + 0xCE0, 32);
        RequestDma3Copy(&gUnk_0940FA98[(v[1] + 3) * 32], base + 0xD00, 32);
    } else {
        RequestDma3Copy(gUnk_0940FAD8, base + 0xCE0, 32);
        RequestDma3Copy(gUnk_0940FAD8, base + 0xD00, 32);
    }
}

void FreeRikuCollectionEntries(RikuDeckMenuWork* work) {
    CardKindEntry** p;
    u16 i;

    if (work->entries != NULL) {
        for (i = 0; i < work->entryCount; i++) {
            EwramFree(work->entries[i].indices);
        }

        p = &work->entries;
        EwramFree(*p);
        *p = NULL;
    }
}

void ReleaseRikuCommandMenuGfx(RikuDeckMenuWork* work) {
    if (work->tiles3 != NULL) {
        ReleaseObjTiles(work->tiles3);
        ReleaseObjPalette(work->palette2);
        work->tiles3 = NULL;
        work->palette2 = NULL;
    }
}

void SetRikuDeckMenuFrameCursor(RikuDeckMenuWork* work, u8 mode) {
    switch (mode) {
    case 0:
        SetObjTileSource(work->tiles2, gUnk_090A4A0C);
        AnimInit(&work->anim3, gUnk_09EEB064, gUnk_09EEB050);
        AnimStart(&work->anim3, 0, ANIM_FLAG_LOOP);
        work->gfx2 = AnimGetGfx(&work->anim3);
        break;
    case 1:
        SetObjTileSource(work->tiles2, gUnk_090A51F6);
        AnimInit(&work->anim3, gUnk_09EEB07C, gUnk_09EEB068);
        AnimStart(&work->anim3, 0, ANIM_FLAG_LOOP);
        work->gfx2 = AnimGetGfx(&work->anim3);
        break;
    }
}

u8 CheckRikuDeckCpCost(RikuDeckMenuWork* work) {
    if (GetDeckCpCost(GetActiveDeckIndex()) > gGameState.progression.cp) {
        TaskCreate(&work->cardpool, &gTaskDescDeckErrorCp, &work->popupActive);
        m4aSongNumStart(SONG_SYS_BEEP);
        return 0;
    }

    return 1;
}

u8 CheckRikuDeckHasAttackCard(RikuDeckMenuWork* work) {
    if (CountActiveDeckCardsOfCategory(0) == 0) {
        m4aSongNumStart(SONG_SYS_BEEP);
        TaskCreate(&work->cardpool, &gTaskDescDeckErrorNoAttackCard, &work->popupActive);
        return 0;
    }

    return 1;
}

u8 FindRikuCardInDirection(RikuDeckMenuWork* work, s16 x, s16 y, u16 dir) {
    DeckCard2Work* node;

    node = ListPoolFirst(&work->pool);

    while (node != NULL) {
        if (node->args.col == x && node->args.row == y) {
            return 1;
        }

        node = ListPoolNext(&node->node);
    }

    switch (dir) {
    case 64:
        return FindRikuCardInDirection(work, x, y - 1, 64);
    case 128:
        return FindRikuCardInDirection(work, x, y + 1, 128);
    case 32:
        return FindRikuCardInDirection(work, x - 1, y, 32);
    case 16:
        return FindRikuCardInDirection(work, x + 1, y, 16);
    }

    return 0;
}

#ifdef VERSION_EU
void* gRikuDeckTitleBannerTiles[5] = { gUnk_090A418E, gUnkEu_091926B2, gUnkEu_0919308A, gUnkEu_09192D42, gUnkEu_091929FA };

void** gRikuDeckTitleBannerSprites[5] = {
    gUnk_09EEAFF8,
    gUnkEu_09F77100,
    gUnkEu_09F77118,
    gUnkEu_09F77110,
    gUnkEu_09F77108,
};

u8* gRikuDeckEquipMarkerTiles[5] = { gUnkEu_094EAD64, gUnkEu_094E90E4, gUnkEu_094EA2E4, gUnkEu_094E9CE4, gUnkEu_094E96E4 };
#endif

TaskDesc gTaskDescDeckmenu2Riku = {
    "Deckmenu2",
    (TaskInitFunc)Deckmenu2_0,
    (TaskUpdateFunc)UpdateRikuDeckMenuLoadBgs,
    (TaskDrawFunc)Deckmenu2_2,
    (TaskDestroyFunc)Deckmenu2_3,
    sizeof(RikuDeckMenuWork),
};
