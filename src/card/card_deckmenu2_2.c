#include "card_localized_data.h"
#include "msg_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "msg_api.h"
#include "card_battle.h"
#include "player_progression.h"
#include "m4a_song.h"
#include "game_state.h"
#include "text.h"
#include "monsgage.h"
#include "fade.h"
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
#include "malloc.h"
#include "card.h"
#include "card_message_assets.h"
#include <stddef.h>
#include "game.h"
#include "bos4_api.h"
#include "sprites_deck_menu.h"
#include "sprites_card_pictures.h"
#include "gba/keys.h"
#include "songs.h"

#ifdef VERSION_EU
extern void* gRikuDeckTitleBannerTiles[];
extern u8* gRikuDeckEquipMarkerTiles[];

#define LANGSTR(x) (((void**)(x))[gLanguage])
#else
#define LANGSTR(x) (x)
#endif
u16 CountActiveDeckCardsOfCategory(u8 slot);
void ReleaseRikuCardPreview(RikuDeckMenuWork* w);
void DrawRikuCpCost(u8 a);
void LoadRikuCardNameText(RikuDeckMenuWork* w, s32 id);
void LoadRikuCardDescriptionText(RikuDeckMenuWork* w, u16 card);
void DeckCard2ReleaseGfx(DeckCard2Work* node);
void ShowRikuDeckCardPreview(RikuDeckMenuWork* w);
u8 UpdateRikuDeckMenuDeckGrid(RikuDeckMenuWork* w, void* a);
s32 UpdateRikuDeckMenuFadeOut(RikuDeckMenuWork* w);
u8 CheckRikuDeckCpCost(RikuDeckMenuWork* w);
u8 CheckRikuDeckHasAttackCard(RikuDeckMenuWork* w);
DeckCard2Work* GetRikuCardAtCursor(RikuDeckMenuWork* w);
u8 UpdateRikuDeckMenuLoadDeckInfo(RikuDeckMenuWork* w, void* a);
void ClearRikuCardGrid(RikuDeckMenuWork* w);
void ReleaseRikuCommandMenuGfx(RikuDeckMenuWork* w);
void FreeRikuCollectionEntries(RikuDeckMenuWork* w);
void CreateRikuDeckGridCards(RikuDeckMenuWork* w, u8 kind);
void SetRikuDeckMenuFrameCursor(RikuDeckMenuWork* w, u8 mode);
u16 CountCollectionCards(void);
u16 CountCardsInDecks(void);
Deck* GetDeck(u8 index);
u16 GetDeckCpCost(u8 index);
u8* GetDeckName(u8 index);
u16 CountActiveDeckCardsOfCategory(u8 slot);
u16 GetDeckCardCount(u8 index);
u8 GetActiveDeckIndex(void);
void DeckCard2ReleaseGfx(DeckCard2Work* node);

#ifdef VERSION_EU
const u16 gRikuDeckTitleBannerTileSizes[5] = { 0x320, 0x320, 0x320, 0x320, 0x320 };
#endif

const s16 gRikuDeckTabPointerX[3] = { 116, 116, 116 };

const s16 gRikuDeckTabPointerY[3] = { 56, 104, 148 };

const s16 gUnk_09041EC0[5] = { 12, 28, 42, 56, 70 };

const s16 gUnk_09041ECA[6] = { 172, 172, 188, 202, 216, 230 };

const s16 gUnk_09041ED6[5] = { 64, 82, 100, 118, 136 };

const s16 gUnk_09041EE0[2] = { 80, 128 };

const s16 gUnk_09041EE4[5] = { 80, 88, 96, 104, 112 };

const u16 gUnk_09041EEE[4] = { 45, 93, 141, 30 };

static void Deckmenu2_0(RikuDeckMenuWork* w, void* a) {
    u16 v;

    w->resultOut = a;
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
    FadeStartIn(0, 16);
    ListPoolInit(&w->pool);
    TaskPoolInit(&w->taskpool, 99);
    TaskPoolInit(&w->cardpool, 1);
    w->deckIndex = GetActiveDeckIndex();
    CreateRikuDeckGridCards(w, 0);
    w->tiles = AllocObjTiles(0x120, 0);
    SetObjTileSource(w->tiles, gUnk_090A4664);
    AnimInit(&w->anim2, gUnk_09EEB03C, gUnk_09EEB008);
    AnimStart(&w->anim2, 0, 1);
    w->gfx = AnimGetGfx(&w->anim2);
    w->x = gRikuDeckTabPointerX[0] << 8;
    w->y = gRikuDeckTabPointerY[0] << 8;
    w->handFlags = 0;
    w->tiles4 = LoadObjTiles(gUnk_090A44C4, 32);
    w->palette = LoadObjPalette(gUnk_09614418, 32);
    w->handVisible = 0;
    w->tiles2 = AllocObjTiles(0x280, 0);
    SetRikuDeckMenuFrameCursor(w, 0);
    w->palette4 = LoadObjPalette(gUnk_09614438, 32);
    w->tiles10 = 0;
    w->tiles7 = 0;
    w->tiles8 = 0;
    w->tiles9 = 0;
    w->palette5 = 0;
    w->palette6 = 0;
    w->tiles3 = 0;
    w->palette2 = 0;
    w->cursorCol = 0;
    w->cursorRow = 0;
    w->unk_4E8 = 0;
    w->unk_4E9 = 0;
    w->timer = 4;
    w->unk_500 = 0;
    w->cursorCard = 0;
    w->prevCursorCard = 0;
    w->unk_4FF = 0;
    w->view = 0;
    w->deckAttackCount = CountActiveDeckCardsOfCategory(0);
    w->deckMagicCount = CountActiveDeckCardsOfCategory(1);
    w->deckItemCount = CountActiveDeckCardsOfCategory(2);
    w->deckEnemyCount = CountActiveDeckCardsOfCategory(3);
    w->unk_4F9 = 0;
    w->entryCount = 0;
    w->entries = 0;
    w->popupActive = 0;
    w->exitRequested = 0;
    w->barSlideTimer = 16;
    w->bannerSlideTimer = 16;
    w->x5 = 0x7800;
    w->y5 = -0x800;
    w->x6 = 0xA400;
    w->y6 = 0xA000;
    w->x7 = -0x8000;
    w->holding = 0;
#ifdef VERSION_EU
    w->tiles12 = LoadObjTiles(gRikuDeckTitleBannerTiles[gLanguage], gRikuDeckTitleBannerTileSizes[gLanguage]);
#else
    w->tiles12 = LoadObjTiles(gUnk_090A418E, 0x320);
#endif
    w->tiles6 = LoadObjTiles(gUnk_090A583E, 0x620);
    w->palette3 = LoadObjPalette(gUnk_096144F8, 32);
    w->unk_4BC = 79;
    v = gUnk_09041EEE[w->deckIndex];
    w->unk_4BE = v;
    w->unk_4C0 = 225;
    v = gUnk_09041EEE[w->deckIndex];
    w->unk_4C2 = v;
    w->unk_503 = 0;
    w->inputDelay = 0;
    w->textSlotCount = 0;
    w->textSlotCount2 = 0;
    w->textSlotCount3 = 0;
    w->textSlotCount4 = 0;
    w->result = 0;
    InitTextSlots(w->textSlots, 8);
    InitTextSlots(w->textSlots2, 8);
    InitTextSlots(w->textSlots3, 8);
    InitTextSlots(w->textSlots4, 30);
    InitTextSlots(w->textSlots5, 60);
    w->descriptionX = 94;
    w->descriptionY = 126;
    w->previewShown = 0;
}

void DrawRikuCardDescription(RikuDeckMenuWork* w) {
    DrawTextSlots(w->descriptionX, w->descriptionY, w->textSlots5,
                  w->palette, 20, w->textSlotCount5);
}

void LoadRikuCardDescriptionText(RikuDeckMenuWork* w, u16 card) {
    CardDef* d;
    void* s;

    d = &gCardDefs[card];
    s = gCardKindDescriptions[d->kind];
    w->textSlotCount5 = LoadTextSlots(LANGSTR(s), w->textSlots5);
}

u8 UpdateRikuDeckMenuLoadBgs(RikuDeckMenuWork* w, void* a) {
#ifdef VERSION_EU
    LoadBgTiles(3, gUnk_09402F78, 0x5400);

    switch (gLanguage) {
    case 1:
        RequestDma3Copy(gUnkEu_094E20E4, (u8*)GetBgCharBase(3) + 0x3800, 0x1C00);
        break;
    case 2:
        RequestDma3Copy(gUnkEu_094E74E4, (u8*)GetBgCharBase(3) + 0x3800, 0x1C00);
        break;
    case 3:
        RequestDma3Copy(gUnkEu_094E58E4, (u8*)GetBgCharBase(3) + 0x3800, 0x1C00);
        break;
    case 4:
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

u8 UpdateRikuDeckMenuLoadDeckInfo(RikuDeckMenuWork* w, void* a) {
    u8* base;
    u16* pal;

    base = (u8*)GetBgCharBase(1);
    pal = (u16*)0x05000100;
    LoadPalette(gUnk_09614118 + 0x1E0, pal, 32);
#ifdef VERSION_EU
    RequestDma3Copy(gRikuDeckEquipMarkerTiles[gLanguage] + 0x20, base + 0x2D80, 0x1E0);
    LoadBgMap(0, gUnk_095172B8, 0x800);
    LoadBgMap(1, gUnk_09516AB8, 0x800);
#else
    RequestDma3Copy(gUnk_0940FC58, base + 0x1A0, 0x1E0);
    LoadBgMap(0, gUnk_09516AB8 + 0x800, 0x800);
    LoadBgMap(1, gUnk_0951B2B8 + 0x800, 0x800);
#endif
    DrawRikuDeckCategoryCount(w->deckAttackCount, 0);
    DrawRikuDeckCategoryCount(w->deckMagicCount, 1);
    DrawRikuDeckCategoryCount(w->deckItemCount, 2);
    DrawRikuDeckCategoryCount(w->deckEnemyCount, 3);
    DrawRikuDeckCardCount(0);
    DrawRikuCardTotals();
    w->x2 = 0x4800;
    w->y2 = 0x2800;
    w->cursorRow = w->deckIndex;
    ApproachValue(&w->x, gRikuDeckTabPointerX[w->cursorCol] << 8, w->timer);
    ApproachValue(&w->y, gRikuDeckTabPointerY[w->cursorRow] << 8, w->timer);
    w->view = 1;
    SetRikuDeckMenuHandAnim(w);
    LoadRikuDeckNameTexts(w);
    w->step = 0;
    w->timer = 16;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuSlideIn);
    return 1;
}

u8 UpdateRikuDeckMenuSlideIn(RikuDeckMenuWork* w, void* a) {
    u8 n;

    if (FadeIsActive() == 0) {
        switch (w->step) {
        case 0:
            ApproachValue(&w->y5, 0, w->timer);
            ApproachValue(&w->y6, 0x9800, w->timer);
            w->timer--;

            if (w->timer == 0) {
                w->timer = 16;
                w->step++;
            }
            break;
        case 1:
            ApproachValue(&w->x7, 0, w->timer);
            n = --w->timer;

            if (n == 0) {
                LoadBgMap(3, gUnk_095162B8, 0x800);
                ReleaseObjTiles(w->tiles12);
                w->tiles12 = 0;
                ReleaseObjTiles(w->tiles6);
                w->tiles6 = 0;
                ReleaseObjPalette(w->palette3);
                w->palette3 = 0;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuEnterDeckGrid);
            }
            break;
        }
    }

    return 1;
}

u8 UpdateRikuDeckMenuEnterDeckGrid(RikuDeckMenuWork* w, void* a) {
    w->x = gDeckGridColumnX[w->cursorCol] << 8;
    w->y = gDeckGridRowY[w->cursorRow] << 8;
    w->view = 0;
    SetRikuDeckMenuHandAnim(w);
    ShowRikuDeckCardPreview(w);
    w->handVisible = 1;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuDeckGrid);
    return 1;
}

u8 UpdateRikuDeckMenuDeckGrid(RikuDeckMenuWork* w, void* a) {
    u16 x;

    w->gfx = AnimUpdate(&w->anim2);
    w->gfx2 = AnimUpdate(&w->anim3);

    if (FadeIsActive() != 0) {
        TaskPoolUpdate(&w->taskpool);
        return 1;
    }

    if (w->popupActive != 0) {
        ApproachValue(&w->x, gDeckGridColumnX[w->cursorCol] << 8, w->timer);
        ApproachValue(&w->y, gDeckGridRowY[w->cursorRow] << 8, w->timer);

        if (w->timer != 0) {
            w->timer--;
        }

        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);

        if (GetKeysPressed() & START_BUTTON) {
            w->exitRequested = 1;
        }
        w->inputDelay = 4;
        return 1;
    }

    if (w->inputDelay > 0) {
        TaskPoolUpdate(&w->taskpool);
        TaskPoolUpdate(&w->cardpool);
        w->inputDelay--;
        return 1;
    }

    if (w->exitRequested != 0) {
        if (CheckRikuDeckCpCost(w) != 0 && CheckRikuDeckHasAttackCard(w) != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuFadeOut);
            FadeStartOut(0, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }
        w->exitRequested = 0;
    }

    switch (GetKeysRepeat()) {
    case DPAD_UP:
        if (w->cursorRow > 0) {
            (w->cursorRow)--;
            w->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        } else {
            ScrollRikuGridUp(w);
        }
        ShowRikuDeckCardPreview(w);
        break;
    case DPAD_DOWN:
        if (w->cursorRow <= 2) {
            (w->cursorRow)++;
            w->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        } else {
            ScrollRikuGridDown(w);

            if (w->holding != 0) {
                if ((u16)w->heldRow <= 3) {
                    w->y3 = gDeckGridRowY[w->heldRow] << 8;
                } else {
                    w->y3 = 0xFFFF0000;
                }
            }
        }
        ShowRikuDeckCardPreview(w);
        break;
    case DPAD_LEFT:
        if (w->cursorCol > 0) {
            (w->cursorCol)--;
            w->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }
        ShowRikuDeckCardPreview(w);
        break;
    case DPAD_RIGHT:
        if (w->cursorCol <= 1) {
            (w->cursorCol)++;
            w->timer = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }
        ShowRikuDeckCardPreview(w);
        break;
    case START_BUTTON:
        w->result = 7;
        m4aSongNumStart(SONG_SYS_CANSEL);
        FadeStartOut(0, 4);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuFadeOut);
        return 1;
    case B_BUTTON:
        w->result = 8;
        m4aSongNumStart(SONG_SYS_CANSEL);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuStartSlideOut);
        return 1;
    }

    w->cursorCard = GetRikuCardAtCursor(w);
    ApproachValue(&w->x, gDeckGridColumnX[w->cursorCol] << 8, w->timer);
    ApproachValue(&w->y, gDeckGridRowY[w->cursorRow] << 8, w->timer);

    if (w->timer != 0) {
        w->timer--;
    }

    w->prevCursorCard = w->cursorCard;
    x = w->cursorCol;
    w->unk_4E8 = x;
    x = w->cursorRow;
    w->unk_4E9 = x;
    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

s32 UpdateRikuDeckMenuFadeOut(RikuDeckMenuWork* w) {
    if (FadeIsActive() == 0) {
        return 0;
    }

    TaskPoolUpdate(&w->taskpool);
    TaskPoolUpdate(&w->cardpool);
    return 1;
}

u8 UpdateRikuDeckMenuStartSlideOut(RikuDeckMenuWork* w, void* a) {
#ifdef VERSION_EU
    w->tiles12 = LoadObjTiles(gRikuDeckTitleBannerTiles[gLanguage], gRikuDeckTitleBannerTileSizes[gLanguage]);
#else
    w->tiles12 = LoadObjTiles(gUnk_090A418E, 0x320);
#endif
    w->tiles6 = LoadObjTiles(gUnk_090A583E, 0x620);
    w->palette3 = LoadObjPalette(gUnk_096144F8, 32);
    LoadBgMap(3, gUnk_0951B2B8, 0x800);
    w->x5 = 0x7800;
    w->y5 = 0;
    w->x6 = 0xA400;
    w->y6 = 0x9800;
    w->x7 = 0;
    w->barSlideTimer = 16;
    w->bannerSlideTimer = 16;
    w->handVisible = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuSlideOut);
    return 1;
}

u8 UpdateRikuDeckMenuSlideOut(RikuDeckMenuWork* w, void* a) {
    u8* p;

    p = &w->bannerSlideTimer;

    if ((s8)*p > 0) {
        ApproachValue(&w->x7, -0x8000, (u16)(s8)*p);
        (*p)--;
    } else {
        p = &w->barSlideTimer;

        if ((s8)*p > 0) {
            ApproachValue(&w->y5, -0x800, (u16)(s8)*p);
            ApproachValue(&w->y6, 0xA000, (u16)(s8)*p);
            (*p)--;
        } else {
            FadeStartOut(0, 4);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuDeckMenuFadeOut);
        }
    }

    return 1;
}

static void Deckmenu2_2(RikuDeckMenuWork* w) {
    if (w->tiles12 != 0) {
#ifdef VERSION_EU
        DrawSprite(w->x7 >> 8, 0, gRikuDeckTitleBannerSprites[gLanguage][0], w->tiles12, w->palette3, 0, 0, 10);
#elif defined(VERSION_JP)
        DrawSprite(w->x7 >> 8, 0, gUnk_09EEAFF0, w->tiles12, w->palette3, 0, 0, 10);
#else
        DrawSprite(w->x7 >> 8, 0, gUnk_09EEAFF8, w->tiles12, w->palette3, 0, 0, 10);
#endif
    }

    if (w->tiles6 != 0) {
        DrawSprite(w->x5 >> 8, w->y5 >> 8, gUnk_09EEB080[0], w->tiles6,
                   w->palette3, 0, 0xC00, 10000);
        DrawSprite(w->x6 >> 8, w->y6 >> 8, gUnk_09EEB080[1], w->tiles6,
                   w->palette3, 0, 0xC00, 10000);
    }

    if (w->handVisible != 0) {
        DrawSprite((w->x >> 8) - 16, (w->y >> 8) - 30, w->gfx,
                   w->tiles, w->palette, 0, w->handFlags, 3);
        DrawSprite((w->x >> 8) - 16, (w->y >> 8) - 20, w->gfx2,
                   w->tiles2, w->palette4, 0, 0, 8);
    }

    DrawSprite(w->x2 >> 8, w->y2 >> 8, gUnk_09EEB000, w->tiles4,
               w->palette, 0, 0x800, 10);

    if (w->tiles7 != 0) {
        DrawSprite(168, 86, w->gfx4, w->tiles7, w->palette5, 0, 0, 20);
    }

    if (w->tiles8 != 0) {
        DrawSprite(168, 86, w->gfx5, w->tiles8, w->palette6, 0, 0, 21);
    }

    if (w->tiles9 != 0) {
        DrawSprite(168, 86, w->gfx6, w->tiles9, w->palette5, 0, 0, 19);
    }

    if (w->previewShown != 0) {
        if (w->textSlotCount4 != 0) {
            DrawTextSlots(100, 112, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }

        DrawRikuCardDescription(w);
    }

    TaskPoolDraw(&w->taskpool);
    TaskPoolDraw(&w->cardpool);
}

static void Deckmenu2_3(RikuDeckMenuWork* w) {
    ClearRikuCardGrid(w);
    ReleaseObjTiles(w->tiles);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjTiles(w->tiles4);
    ReleaseObjPalette(w->palette);
    ReleaseRikuCommandMenuGfx(w);

    if (w->tiles12 != 0) {
        ReleaseObjTiles(w->tiles12);
    }

    if (w->tiles6 != 0) {
        ReleaseObjTiles(w->tiles6);
    }

    if (w->palette3 != 0) {
        ReleaseObjPalette(w->palette3);
    }

    FreeTextSlots(w->textSlots, 8);
    FreeTextSlots(w->textSlots2, 8);
    FreeTextSlots(w->textSlots3, 8);
    FreeTextSlots(w->textSlots4, 30);
    FreeTextSlots(w->textSlots5, 60);
    ReleaseObjPalette(w->palette4);
    TaskPoolDestroy(&w->taskpool);
    TaskPoolDestroy(&w->cardpool);
    FreeRikuCollectionEntries(w);
    *w->resultOut = w->result;
}

void CreateRikuDeckGridCards(RikuDeckMenuWork* w, u8 kind) {
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
                TaskCreate(&w->taskpool, &gTaskDescDeckCard2, &args);
                x++;
            } else if (gCardDefs[gCardCollection[cards[i]] & CARD_ID_MASK].category == kind - 1) {
                args.pool = &w->pool;
                args.cardId = gCardCollection[cards[i]] & 0x8FFF;
                args.col = x;
                args.row = y;
                args.panel = 0;
                args.slot = &cards[i];
                TaskCreate(&w->taskpool, &gTaskDescDeckCard2, &args);
                x++;
            }
            if (x > 2) {
                x = 0;
                y++;
            }
        }
    }
    w->x2 = 0x4800;
    w->y2 = 0x2800;
    w->scrollRowEnd = 4;
}
void ClearRikuCardGrid(RikuDeckMenuWork* w) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    while (node != 0) {
        node->done = 1;
        node = ListPoolNext(&node->node);
    }

    TaskPoolUpdate(&w->taskpool);
}

void ScrollRikuGridDown(RikuDeckMenuWork* w) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    if ((s8)w->scrollRowEnd == 33) {
        return;
    }

    while (node != 0) {
        node->args.row--;

        if (node->args.row < 0) {
            node->y = 0x20000;
            DeckCard2ReleaseGfx(node);
        }

        node = ListPoolNext(&node->node);
    }

    m4aSongNumStart(SONG_SYS_CLICKI04B);
    w->scrollRowEnd++;
    w->y2 += 0x300;

    if (w->y2 > 0x7C00) {
        w->y2 = 0x7C00;
    }

    if (w->holding != 0) {
        w->heldRow--;
    }
}

u8 ScrollRikuGridUp(RikuDeckMenuWork* w) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    if (node == 0) {
        w->y2 -= 0x300;

        if (w->y2 < 0x2800) {
            w->y2 = 0x2800;
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
    } while (node != 0);

    m4aSongNumStart(SONG_SYS_CLICKI04B);
    w->scrollRowEnd--;
    w->y2 -= 0x300;

    if (w->y2 < 0x2800) {
        w->y2 = 0x2800;
    }

    return 1;
}

DeckCard2Work* GetRikuCardAtCursor(RikuDeckMenuWork* w) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    while (node != 0) {
        if (w->cursorCol == node->args.col &&
            w->cursorRow == node->args.row) {
            return node;
        }

        node = ListPoolNext(&node->node);
    }

    return 0;
}

void DrawRikuDeckCategoryCount(u8 a, u8 b) {
    u8 d[2];
    u8* base;

    d[0] = a / 10;
    d[1] = a - (u8)(a / 10) * 10;
    base = (u8*)GetBgCharBase(3);
    RequestDma3Copy(&gUnk_0940F7B8[(d[0] + 1) * 32], base + (b * 64 + 0x360), 32);
    RequestDma3Copy(&gUnk_0940F7B8[(d[1] + 1) * 32], base + (b * 64 + 0x360) + 32, 32);
}

void SetRikuDeckMenuHandAnim(RikuDeckMenuWork* w) {
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
        AnimStart(&w->anim2, 0, 1);
        w->handFlags &= ~1;
        break;
    case 1:
    case 3:
        AnimStart(&w->anim2, 2, 1);
        t = w->handFlags | 1;
        w->handFlags = t;
        break;
    }
}

void DrawRikuDeckCardCount(u8 deck) {
    u8 d[2];
    u8 e[2];
    u8* base;
    u16 n;

    base = 0;
    n = GetDeckCardCount(deck);
    d[0] = n / 10;
    d[1] = n - (u16)(n / 10) * 10;
    e[0] = 9;
    e[1] = 9;

    switch (deck) {
    case 0:
        base = (u8*)GetBgCharBase(1);
        break;
    case 1:
        base = (u8*)GetBgCharBase(1);
        break;
    case 2:
        base = (u8*)GetBgCharBase(1);
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

void DrawRikuCardTotals(void) {
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
    base = (u8*)GetBgCharBase(3);
    RequestDma3Copy(&gUnk_0940F938[(d[0] + 1) * 32], base + 0x2A0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d[1] + 1) * 32], base + 0x2C0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d[2] + 1) * 32], base + 0x2E0, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[0] + 1) * 32], base + 0x300, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[1] + 1) * 32], base + 0x320, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[2] + 1) * 32], base + 0x340, 32);
}

void LoadRikuDeckNameTexts(RikuDeckMenuWork* w) {
    FreeTextSlots(w->textSlots, 8);
    FreeTextSlots(w->textSlots2, 8);
    FreeTextSlots(w->textSlots3, 8);
    w->textSlotCount = LoadTextSlots(GetDeckName(0), w->textSlots);
    w->textSlotCount2 = LoadTextSlots(GetDeckName(1), w->textSlots2);
    w->textSlotCount3 = LoadTextSlots(GetDeckName(2), w->textSlots3);
}

void LoadRikuCardNameText(RikuDeckMenuWork* w, s32 id) {
    CardDef* def;

    def = &gCardDefs[id];
#ifdef VERSION_EU
    w->textSlotCount4 = LoadTextSlots(eu_0805E924(def->name), w->textSlots4);
#else
    w->textSlotCount4 = LoadTextSlots(def->name, w->textSlots4);
#endif

    switch (def->category) {
    case 0:
        LoadPalette(gUnk_09614458,
                    (void*)(w->palette4->index * 32 +
                            0x05000200),
                    (u16)(w->palette4->count << 5));
        break;
    case 1:
        LoadPalette(gUnk_09614478,
                    (void*)(w->palette4->index * 32 +
                            0x05000200),
                    (u16)(w->palette4->count << 5));
        break;
    case 2:
        LoadPalette(gUnk_09614498,
                    (void*)(w->palette4->index * 32 +
                            0x05000200),
                    (u16)(w->palette4->count << 5));
        break;
    case 3:
        LoadPalette(gUnk_096144B8,
                    (void*)(w->palette4->index * 32 +
                            0x05000200),
                    (u16)(w->palette4->count << 5));
        break;
    }
}

void ReleaseRikuCardPreview(RikuDeckMenuWork* w) {
    if (w->tiles10 != 0) {
        ReleaseObjTiles(w->tiles10);
        w->tiles10 = 0;
    }

    if (w->tiles7 != 0) {
        ReleaseObjTiles(w->tiles7);
        ReleaseObjPalette(w->palette5);
        ReleaseObjTiles(w->tiles8);
        ReleaseObjPalette(w->palette6);

        if (w->tiles9 != 0) {
            ReleaseObjTiles(w->tiles9);
            w->tiles9 = 0;
        }

        w->tiles7 = 0;
        w->palette5 = 0;
        w->tiles8 = 0;
        w->palette6 = 0;
    }
}

void ShowRikuDeckCardPreview(RikuDeckMenuWork* w) {
    DeckCard2Work* node;
    CardDef* def;
    void* dst;
    u16 id;
    u32 t;

    id = 0xFFFF;
    node = ListPoolFirst(&w->pool);

    while (node != 0) {
        if (node->args.row == w->cursorRow && node->args.col == w->cursorCol) {
            id = node->args.cardId;
            break;
        }

        node = ListPoolNext(&node->node);
    }

    ReleaseRikuCardPreview(w);

    if (id != 0xFFFF) {
        if (id & 0x8000) {
            w->tiles10 = AllocObjTiles(0x280, 0);
            SetObjTileSource(w->tiles10, gUnk_0908B1B4);
            AnimInit(&w->anim, gUnk_09EEA164, gUnk_09EEA148);
            AnimStart(&w->anim, 0, 1);
            w->gfx3 = AnimGetGfx(&w->anim);
        }

        t = id & CARD_ID_MASK;
        def = &gCardDefs[t];
        w->tiles7 = LoadObjTiles(gCardBacks[def->category].tiles, 768);
        w->tiles8 = LoadObjTiles(def->tiles, 512);
        w->palette6 = LoadObjPalette(def->palette, 32);
        w->palette5 = LoadObjPalette(gCard00Palette, 32);
        w->gfx4 = gCardBacks[def->category].gfx;
        w->gfx5 = def->gfx;

        if (def->category != 3) {
            w->tiles9 = LoadObjTiles(gUnk_0905EAE8, 480);
            w->gfx6 = gUnk_09EE981C[def->value];
        }

        DrawRikuCpCost(def->cpCost);
        dst = gUnk_05000160;
        LoadPalette(&gUnk_09614118[def->category * 32 + 0x200], dst, 32);
        LoadRikuCardNameText(w, t);
        LoadRikuCardDescriptionText(w, t);
        w->previewShown = 1;
    } else {
        DrawRikuCpCost(0);
        w->previewShown = 0;
    }
}

void DrawRikuCpCost(u8 a) {
    u8 v[2];
    u8* base;

    base = (u8*)GetBgCharBase(3);

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
void FreeRikuCollectionEntries(RikuDeckMenuWork* w) {
    CardKindEntry** p;
    u16 i;

    if (w->entries != 0) {
        for (i = 0; i < w->entryCount; i++) {
            EwramFree(w->entries[i].indices);
        }

        p = &w->entries;
        EwramFree(*p);
        *p = 0;
    }
}
void ReleaseRikuCommandMenuGfx(RikuDeckMenuWork* w) {
    if (w->tiles3 != 0) {
        ReleaseObjTiles(w->tiles3);
        ReleaseObjPalette(w->palette2);
        w->tiles3 = 0;
        w->palette2 = 0;
    }
}
void SetRikuDeckMenuFrameCursor(RikuDeckMenuWork* w, u8 mode) {
    switch (mode) {
    case 0:
        SetObjTileSource(w->tiles2, gUnk_090A4A0C);
        AnimInit(&w->anim3, gUnk_09EEB064, gUnk_09EEB050);
        AnimStart(&w->anim3, 0, 1);
        w->gfx2 = AnimGetGfx(&w->anim3);
        break;
    case 1:
        SetObjTileSource(w->tiles2, gUnk_090A51F6);
        AnimInit(&w->anim3, gUnk_09EEB07C, gUnk_09EEB068);
        AnimStart(&w->anim3, 0, 1);
        w->gfx2 = AnimGetGfx(&w->anim3);
        break;
    }
}
u8 CheckRikuDeckCpCost(RikuDeckMenuWork* w) {
    if (GetDeckCpCost(GetActiveDeckIndex()) > gGameState.progression.cp) {
        TaskCreate(&w->cardpool, &gTaskDescDeckErrorCp, &w->popupActive);
        m4aSongNumStart(SONG_SYS_BEEP);
        return 0;
    }

    return 1;
}
u8 CheckRikuDeckHasAttackCard(RikuDeckMenuWork* w) {
    if (CountActiveDeckCardsOfCategory(0) == 0) {
        m4aSongNumStart(SONG_SYS_BEEP);
        TaskCreate(&w->cardpool, &gTaskDescDeckErrorNoAttackCard, &w->popupActive);
        return 0;
    }

    return 1;
}
u8 FindRikuCardInDirection(RikuDeckMenuWork* w, s16 x, s16 y, u16 dir) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    while (node != 0) {
        if (node->args.col == x && node->args.row == y) {
            return 1;
        }

        node = ListPoolNext(&node->node);
    }

    switch (dir) {
    case 64:
        return FindRikuCardInDirection(w, x, y - 1, 64);
    case 128:
        return FindRikuCardInDirection(w, x, y + 1, 128);
    case 32:
        return FindRikuCardInDirection(w, x - 1, y, 32);
    case 16:
        return FindRikuCardInDirection(w, x + 1, y, 16);
    }

    return 0;
}

static void Deckmenu2_0(RikuDeckMenuWork* w, void* a);

#ifdef VERSION_EU
void* gRikuDeckTitleBannerTiles[5] = { gUnk_090A418E, gUnkEu_091926B2, gUnkEu_0919308A, gUnkEu_09192D42, gUnkEu_091929FA };

void** gRikuDeckTitleBannerSprites[5] = {
    &gUnk_09EEAFF8,
    &gUnkEu_09F77100,
    &gUnkEu_09F77118,
    &gUnkEu_09F77110,
    &gUnkEu_09F77108,
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
