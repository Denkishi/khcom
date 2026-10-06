/**
 * card_battle.c
 * Sora Card Battle Interface
 */

#include "macros.h"
#include "registration_data.h"
#include "card_api.h"
#include <string.h>
#include "card_battle.h"
#include "m4a_song.h"
#include "fade.h"
#include "engine_math.h"
#include "listpool.h"
#include "card.h"
#include "obj_api.h"
#include "malloc.h"
#include "anim.h"
#include "sprites_card_pictures.h"
#include "sprites_card.h"
#include "obj_resource_types.h"
#include "songs.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "card_def_data.h"
#include "card_label_data.h"
#include "card_types.h"
#include "game_state.h"
#include "obj.h"
#include "taskpool.h"
#include "types.h"
#include "gba/macro.h"
#include <stddef.h>
#include "lockon.h"
#include "sprite_palettes.h"
#include "tutorial_deck.h"

static CardDisplayWork* sSoraSelectedCard;
static u32 sSoraCardRequest;
static u32 sSoraCardReloadRequest;
CardBattleState* gCardBattleState EWRAM_COMMON(4);

const s32 gSoraCardRingAngles[4] = {
    -0x2000, 0, 0x1000, 0x8000,
};

const s32 gSoraCardSwingAngles[4] = {
    0x2000, 0xE000, 0xA000, 0x6000,
};

static const u16 sSoraStockValueX[4] = {
    40, 52, 64, 0,
};

const StockKeys gSoraEmptyKeys = {
    { -1, -1, -1, -1, -1, -1 },
};

void RequestSoraKingReload0() {
    sSoraCardReloadRequest = CARD_REQUEST_KING_RELOAD_0;
}

void RequestSoraKingReload1() {
    sSoraCardReloadRequest = CARD_REQUEST_KING_RELOAD_1;
}

void RequestSoraKingReload2() {
    sSoraCardReloadRequest = CARD_REQUEST_KING_RELOAD_2;
}

u8 GetSoraListIndex() {
    return gCardBattleState->soraListIndex;
}

void RequestSoraPotion() {
    sSoraCardReloadRequest = CARD_REQUEST_POTION;
}

void RequestSoraHiPotion() {
    sSoraCardReloadRequest = CARD_REQUEST_HI_POTION;
}

void RequestSoraMegaPotion() {
    sSoraCardReloadRequest = CARD_REQUEST_MEGA_POTION;
}

void RequestSoraEther() {
    sSoraCardReloadRequest = CARD_REQUEST_ETHER;
}

void RequestSoraMegaEther() {
    sSoraCardReloadRequest = CARD_REQUEST_MEGA_ETHER;
}

void RequestSoraElixir() {
    sSoraCardReloadRequest = CARD_REQUEST_ELIXIR;
}

void RequestSoraMegalixir() {
    sSoraCardReloadRequest = CARD_REQUEST_MEGALIXIR;
}

void RequestSoraRemoveItemCards() {
    sSoraCardReloadRequest = CARD_REQUEST_REMOVE_ITEM_CARDS;
}

void RequestSoraNextCard() {
    sSoraCardRequest = CARD_REQUEST_NEXT_CARD;
}

void RequestSoraPrevCard() {
    sSoraCardRequest = CARD_REQUEST_PREV_CARD;
}

void RequestSoraCardUse() {
    sSoraCardRequest = CARD_REQUEST_USE_CARD;
}

void RequestSoraCardStock() {
    sSoraCardRequest = CARD_REQUEST_STOCK_CARD;
}

void RequestSoraStockUse() {
    sSoraCardRequest = CARD_REQUEST_USE_STOCK;
}

void func_08076354() {
    sSoraCardRequest = CARD_REQUEST_NOP;
}

void RequestOpenCards() {
    sSoraCardRequest = CARD_REQUEST_OPEN_CARDS;
    RequestOpenRikuCards();
}

void RequestCloseCards() {
    sSoraCardRequest = CARD_REQUEST_CLOSE_CARDS;
    RequestCloseRikuCards();
}

void RequestCycleSoraCardList() {
    sSoraCardRequest = CARD_REQUEST_CYCLE_LIST;
}

void RequestSwitchSoraCardList() {
    sSoraCardRequest = CARD_REQUEST_SWITCH_LIST;
}

void RequestSoraAutoCycle60() {
    sSoraCardRequest = CARD_REQUEST_AUTO_CYCLE_60;
}

void RequestSoraAutoCycle180() {
    sSoraCardRequest = CARD_REQUEST_AUTO_CYCLE_180;
}

void RequestSoraAutoCycle300() {
    sSoraCardRequest = CARD_REQUEST_AUTO_CYCLE_300;
}

void ClearSoraCardRequest() {
    sSoraCardRequest = CARD_REQUEST_NONE;
}

u8 IsSoraReloadCardSelected() {
    if (sSoraSelectedCard != NULL && (sSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD)) {
        return 1;
    }

    return 0;
}

void SetSoraReloadCharging() {
    // @bug Called before the card battle state exists (NULL write).
    if (sSoraSelectedCard != NULL) {
        if ((sSoraSelectedCard->flags & (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED | CARD_DISP_FLAG_RELOAD_GAUGE)) == (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED | CARD_DISP_FLAG_RELOAD_GAUGE)) {
            gCardBattleState->soraReloadCharging = 1;
        } else {
            gCardBattleState->soraReloadCharging = 0;
        }
    } else {
        gCardBattleState->soraReloadCharging = 0;
    }
}

void func_08076438() {
}

u8 IsSoraSelectionEmpty() {
    if (sSoraSelectedCard != NULL) {
        return sSoraSelectedCard->flags & CARD_DISP_FLAG_NO_CARD;
    }

    return 0;
}

void CreateCardBattleState() {
    gCardBattleState = EwramAlloc(sizeof(CardBattleState));
    CpuFill32(0, gCardBattleState, sizeof(CardBattleState));
    gCardBattleState->activeCards[0] = NULL;
    gCardBattleState->activeCards[1] = NULL;
    gCardBattleState->activeCards[2] = NULL;
    gCardBattleState->activeCards[3] = NULL;
    gCardBattleState->activeCards[4] = NULL;
    gCardBattleState->activeCards[5] = NULL;
    gCardBattleState->unk_0B0 = 145;
    gCardBattleState->unk_0B4 = 145;
    gCardBattleState->pickedFriendCardId = 950;
    gCardBattleState->pickedGimmickCardId = 950;
    gCardBattleState->unk_0C0 = 0;
    gCardBattleState->activeValue = 0;
    gCardBattleState->soraStockName = 106;
    gCardBattleState->rikuStockName = 106;
    gCardBattleState->unk_0C8 = 256;
    gCardBattleState->unk_0CA = 256;
    gCardBattleState->soraHcEffect = 0;
    gCardBattleState->rikuHcEffect = 0;
    gCardBattleState->activeCardCount = 0;
    gCardBattleState->unk_0D1 = 0;
    gCardBattleState->soraListIndex = 0;
    gCardBattleState->soraStockCount = 0;
    gCardBattleState->rikuListIndex = 0;
    gCardBattleState->rikuStockCount = 0;
    gCardBattleState->friendCardCount = 0;
    gCardBattleState->nextEnemyCardIndex = 0;
    gCardBattleState->unk_0D8 = 0;
    gCardBattleState->unk_0D9 = 0;
    gCardBattleState->gimmickCardCount = 0;
    gCardBattleState->enemyCardUsed = 0;
    gCardBattleState->soraStockActive = 0;
    gCardBattleState->rikuStockActive = 0;
    gCardBattleState->enemyCardUsed = 0;
    gCardBattleState->soraStockNameShown = 0;
    gCardBattleState->rikuStockNameShown = 0;
    gCardBattleState->unk_0E5 = 0;
    gCardBattleState->unk_0E6 = 0;
    gCardBattleState->levelUpShown = 0;
    gCardBattleState->addedFriendCards[0] = 0;
    gCardBattleState->addedFriendCards[1] = 0;
    gCardBattleState->cardsOpen = 0;
    gCardBattleState->soraHcEffectReplaced = 0;
    gCardBattleState->rikuHcEffectReplaced = 0;
    gCardBattleState->unk_0ED = 0;
    gCardBattleState->soraStockedCount = 0;
    gCardBattleState->rikuStockedCount = 0;
    gCardBattleState->darkModeReady = 0;
    gCardBattleState->rikuCardsLeft = 0;
    gCardBattleState->soraReloadGauge = 0;
    gCardBattleState->rikuReloadGauge = 0;
    gCardBattleState->soraReloadCounter = 0;
    gCardBattleState->rikuReloadCounter = 0;
    gCardBattleState->soraGaugeFullFrame = 4;
    gCardBattleState->rikuGaugeFullFrame = 4;
    gCardBattleState->soraGaugeAnim = 2;
    gCardBattleState->rikuGaugeAnim = 2;
    gCardBattleState->reloadGaugeFull[0] = 0;
    gCardBattleState->reloadGaugeFull[1] = 0;
    TaskPoolInit(&gCardBattleState->tasks, 6);
    gCardBattleState->tiles[0] = LoadObjTiles(gCardBacks[0].tiles, 640);
    gCardBattleState->tiles[1] = LoadObjTiles(gCardBacks[1].tiles, 640);
    gCardBattleState->tiles[2] = LoadObjTiles(gCardBacks[2].tiles, 640);
    gCardBattleState->tiles[3] = LoadObjTiles(gCardBacks[3].tiles, 640);
    gCardBattleState->tiles5 = LoadObjTiles(gCardValueDigitTiles, 320);
    gCardBattleState->tiles6 = LoadObjTiles(gCardPremiumValueDigitTiles, 320);
    gCardBattleState->tiles7 = LoadObjTiles(gCardModifiedValueDigitTiles, 320);
    gCardBattleState->palette = LoadObjPalette(gCard00Palette, 32);
    gCardBattleState->palette2 = LoadObjPalette(gBStatesPalette, 32);
    FadeSetPaletteExcluded(((ObjPaletteHeader*)gCardBattleState->palette)->index + 16, 1);
    LoadPremiumCardGfx(gCardBattleState);
}

CardSlot* FindNextAvailableSlot(CardBattleWork* work, u8 listIndex, u16* index) {
    CardSlot* slot;
    s16 i;
    u16 cur;
    s16 next;

    i = *index;

    if (work->slots[listIndex][i].unk_06 == 0 && !work->slots[listIndex][i].stocked) {
        if (!work->slots[listIndex][i].used && !work->slots[listIndex][i].removed) {
            return &work->slots[listIndex][(s16)*index];
        }
    }

    cur = *index;
    next = cur + 1;

    if (next >= work->slotCounts[listIndex]) {
        next = 0;
    }

    while (next != (s16)cur) {
        i = next;

        if (work->slots[listIndex][i].unk_06 == 0 && !work->slots[listIndex][i].stocked) {
            if (!work->slots[listIndex][i].used && !work->slots[listIndex][i].removed) {
                slot = &work->slots[listIndex][i];
                *index = next;
                return slot;
            }
        }

        next = i + 1;

        if (next >= work->slotCounts[listIndex]) {
            next = 0;
        }
    }

    return NULL;
}

CardSlot* FindPrevAvailableSlot(CardBattleWork* work, u8 listIndex, u16* index) {
    CardSlot* slot;
    s16 i;
    u16 cur;
    s16 next;

    i = *index;

    if (work->slots[listIndex][i].unk_06 == 0 && !work->slots[listIndex][i].stocked) {
        if (!work->slots[listIndex][i].used && !work->slots[listIndex][i].removed) {
            return &work->slots[listIndex][(s16)*index];
        }
    }

    cur = *index;
    next = cur - 1;

    if (next < 0) {
        next = work->slotCounts[listIndex] - 1;
    }

    while (next != (s16)cur) {
        i = next;

        if (work->slots[listIndex][i].unk_06 == 0 && !work->slots[listIndex][i].stocked) {
            if (!work->slots[listIndex][i].used && !work->slots[listIndex][i].removed) {
                slot = &work->slots[listIndex][i];
                *index = next;
                return slot;
            }
        }

        next = i - 1;

        if (next < 0) {
            next = work->slotCounts[listIndex] - 1;
        }
    }

    return NULL;
}

void CreateSoraCardRing(CardBattleWork* work, u8 listIndex) {
    CardDisplayArgs arg;
    s16 n;
    s16 count = 0;
    u16 old;
    CardSlot* slot;
    CardDisplayWork* card;
    CardDisplayWork* node;

    if (work->cursors[listIndex] != 0xFFFF) {
        u32 index = work->cursors[listIndex];
        n = index;
        old = index;
        slot = FindNextAvailableSlot(work, listIndex, &n);

        if (slot != NULL) {
            arg.pool = &work->cardDisplays[listIndex];
            arg.index = n;
            arg.listIndex = listIndex;
            arg.slot = slot;
            arg.reloadCount = work->reloadCounts[listIndex];

            if (slot->cardId == CARD_ID_RELOAD) {
                TaskCreate(&work->tasks, &gTaskDescCardReload, &arg);
            } else {
                TaskCreate(&work->tasks, &gTaskDescCardSora, &arg);
            }

            slot->unk_06 = 1;
            old = n;
            n = old + 1;
            count++;
        }

        if (n >= work->slotCounts[listIndex]) {
            n = 0;
        }

        slot = FindNextAvailableSlot(work, listIndex, &n);

        if (slot != NULL && n != work->cursors[listIndex]) {
            arg.pool = &work->cardDisplays[listIndex];
            arg.index = n;
            arg.listIndex = listIndex;
            arg.slot = slot;
            arg.reloadCount = work->reloadCounts[listIndex];

            if (slot->cardId == CARD_ID_RELOAD) {
                TaskCreate(&work->tasks, &gTaskDescCardReload, &arg);
            } else {
                TaskCreate(&work->tasks, &gTaskDescCardSora, &arg);
            }

            slot->unk_06 = 1;
            old = n;
            count++;
        }

        n = work->cursors[listIndex] - 1;

        if (n < 0) {
            n = work->slotCounts[listIndex] - 1;
        }

        slot = FindPrevAvailableSlot(work, listIndex, &n);

        if (slot != NULL && n != work->cursors[listIndex] && n != (s16)old) {
            arg.pool = &work->cardDisplays[listIndex];
            arg.index = n;
            arg.listIndex = listIndex;
            arg.slot = slot;
            arg.reloadCount = work->reloadCounts[listIndex];

            if (slot->cardId == CARD_ID_RELOAD) {
                TaskCreate(&work->tasks, &gTaskDescCardReload, &arg);
            } else {
                TaskCreate(&work->tasks, &gTaskDescCardSora, &arg);
            }

            slot->unk_06 = 1;
            count++;
        }
    }

    switch (count) {
        case 0:
            arg.pool = &work->cardDisplays[listIndex];
            arg.index = 0xFFFF;
            arg.slot = work->slots[listIndex];
            arg.listIndex = listIndex;
            TaskCreate(&work->tasks, &gTaskDescCardNotHave, &arg);
            card = ListPoolFirst(&work->cardDisplays[listIndex]);
            card->ringAngleTarget = card->ringAngle = gSoraCardRingAngles[1];
            card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
            card->ringIndex = 1;
            card->priority = 50;
            card->flags |= (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_VISIBLE);
            break;
        case 1:
            card = ListPoolFirst(&work->cardDisplays[listIndex]);
            card->ringAngleTarget = card->ringAngle = gSoraCardRingAngles[1];
            card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
            card->ringIndex = 1;
            card->priority = 50;
            card->flags |= CARD_DISP_FLAG_VISIBLE;
            break;
        case 2:
            card = ListPoolFirst(&work->cardDisplays[listIndex]);
            card->ringAngleTarget = card->ringAngle = gSoraCardRingAngles[1];
            card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
            card->priority = 50;
            card->ringIndex = 1;
            card->flags |= CARD_DISP_FLAG_VISIBLE;
            card = ListPoolNext(&card->node);
            card->ringAngleTarget = card->ringAngle = gSoraCardRingAngles[0];
            card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
            card->priority = 60;
            card->ringIndex = 0;
            card->flags |= CARD_DISP_FLAG_VISIBLE;
            break;
        case 3:
            card = ListPoolFirst(&work->cardDisplays[listIndex]);
            card->ringAngleTarget = card->ringAngle = gSoraCardRingAngles[1];
            card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
            card->priority = 50;
            card->ringIndex = 1;
            card->flags |= CARD_DISP_FLAG_VISIBLE;
            card = ListPoolNext(&card->node);
            card->ringAngleTarget = card->ringAngle = gSoraCardRingAngles[2];
            card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
            card->priority = 60;
            card->ringIndex = 2;
            card->flags |= CARD_DISP_FLAG_VISIBLE;
            card = ListPoolNext(&card->node);
            card->ringAngleTarget = card->ringAngle = gSoraCardRingAngles[0];
            card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
            card->priority = 60;
            card->ringIndex = 0;
            card->flags |= CARD_DISP_FLAG_VISIBLE;
            break;
    }

    node = ListPoolFirst(&work->cardDisplays[listIndex]);

    while (node != NULL) {
        // @bug A "not have" display has no slot (NULL write).
        node->args.slot->unk_06 = 0;
        node = ListPoolNext(&node->node);
    }

    work->selectedCards[listIndex] = ListPoolFirst(&work->cardDisplays[listIndex]);

    {
        CardDisplayWork** active = &sSoraSelectedCard;
        *active = ListPoolFirst(&work->cardDisplays[listIndex]);
    }

    sSoraSelectedCard->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
}

static void cardbattle_0(CardBattleWork* work) {
    u8 i;

    CpuFill32(0, work, sizeof(CardBattleWork));
    // @bug gCardBattleState is only allocated further down (NULL write).
    gCardBattleState->soraWork = work;
    gBtlWork->hcEffect = 0;
    ResetBossCardValue();
    ClearSoraCardPlayFlags();
    work->tiles = AllocSpriteFrameTiles(128);
    work->palette = LoadObjPalette(gBStatesPalette, 32);
    UpdateSpriteFrameTiles(work->tiles, gStockValueFrames[0], gStockValueTiles);
    TaskPoolInit(&work->tasks, 30);
    work->stockCount = 0;
    work->listIndex = 0;
    work->reloadPending[0] = 0;
    work->reloadPending[1] = 0;
    work->reloadPending[2] = 0;
    work->reloadPending[3] = 0;
    work->revCountShown[0] = 1;
    work->revCountShown[1] = 0;
    work->revCountShown[2] = 0;
    work->revCountShown[3] = 0;
    work->stockValue = 0;
    work->xSteps = 0;
    work->x = sSoraStockValueX[0];
    work->cardsClosed = 0;

    for (i = 0; i < 3; i++) {
        work->playedCards[i] = NULL;
        work->stock[i] = NULL;
    }

    for (i = 0; i < 4; i++) {
        work->selectedCards[i] = NULL;
        work->slots[i] = NULL;
    }

    work->stockNameChecked = 0;

    if (gBtlWork->flags & BTL_FLAG_TUTORIAL) {
        work->slotCounts[0] = gTutorialDeck.cardCount + 15;
        work->cardsLeft[0] = gTutorialDeck.cardCount + 1;
        work->slotCounts[3] = work->cardsLeft[3] = 0;
        work->slotCounts[2] = work->cardsLeft[2] = 0;
        work->slotCounts[1] = work->cardsLeft[1] = 0;
        InitSoraTutorialCardList(work, 0);
        InitSoraTutorialCardList(work, 1);
    } else {
        work->slotCounts[0] = CountActiveDeckCards(0) + 15;
        work->cardsLeft[0] = CountActiveDeckCards(0) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountActiveDeckCards(1);
        work->slotCounts[2] = work->cardsLeft[2] = 0;
        work->slotCounts[1] = work->cardsLeft[1] = 0;
        InitSoraCardList(work, 0);
        InitSoraCardList(work, 1);
    }

    work->reloadCounts[2] = work->reloadCounts[1] = work->reloadCounts[0] = 0;
    CreateCardBattleState();
    CreateREVCOUNTTask(&work->tasks, (u8*)&work->listIndex, &work->cardsLeft[work->listIndex], &work->revCountShown[work->listIndex], 1);
    ListPoolInit(&work->cardDisplays[0]);
    ListPoolInit(&work->cardDisplays[1]);
    ListPoolInit(&work->cardDisplays[2]);
    ListPoolInit(&work->cardDisplays[3]);
    CreateSoraCardRing(work, work->listIndex);
    sSoraCardRequest = CARD_REQUEST_NONE;
    sSoraCardReloadRequest = CARD_REQUEST_NONE;
    CreateBosscardTask(&work->tasks);
    work->actionTaken = 0;

    if (gGameState.flags & GAME_FLAG_DARK_POINTS_LOCKED) {
        return;
    }

    if (gGameState.flags & GAME_FLAG_RIKU) {
        TaskCreate(&work->tasks, &gTaskDescDarkPoint, NULL);
    }
}

s32 IsSoraOnlyStockLeft(CardBattleWork* work) {
    if (CountAvailableCards(work, 0) == 0 && work->cardsLeft[0] <= 1 && work->stockCount != 0) {
        return 1;
    }

    return 0;
}

s32 cardbattleSora_1(CardBattleWork* work, Task* task) {
    StockKeys data;
    u8 flag[4];
    StockKeys cards;
    u8 output[6];
    u8 i;
    u8 found;
    s32 position;
    u16 result;
    s32 stockName;
    ReloadArgs args;
    BtlObj* actor;

    if (gBtlWork->phase == BTL_PHASE_END) {
        if (gBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
            gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
        }

        return 0;
    }

    if (work->xSteps != 0) {
        position = work->x * 256;
        ApproachValue(&position, (s16)sSoraStockValueX[work->stockCount - 1] * 256, work->xSteps);
        work->x = position >> 8;
        work->xSteps--;
    }

    if (!work->cardsClosed) {
        if (sSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
            if (sSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_DONE) {
            if (gBtlWork->hcEffect == 9) {
                RemoveSoraCardDisplays(work);
                TaskPoolUpdate(&work->tasks);

                if (gBtlWork->hcEffect != 25) {
                    IncrementReloadCount(work);

                    if (gBtlWork->hcEffect == 10) {
                        work->reloadCounts[work->listIndex] -= 2;

                        if (work->reloadCounts[work->listIndex] < 0) {
                            work->reloadCounts[work->listIndex] = 0;
                        }
                    }
                }

                gCardBattleState->soraReloadCounter = work->reloadCounts[work->listIndex];
                gCardBattleState->soraReloadGauge = 0;
                gCardBattleState->soraGaugeFullFrame = 4;
                ResetCardSlotsForReload(work, 0);
                work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
                work->cursors[0] = 0;
                CreateSoraCardRing(work, 0);
                TickSoraHcEffectOnReload();
            } else {
                gBtlWork->flags |= BTL_FLAG_RELOADING;
                RemoveSoraCardDisplays(work);

                if (gBtlWork->hcEffect != 25) {
                    IncrementReloadCount(work);

                    if (gBtlWork->hcEffect == 10) {
                        work->reloadCounts[work->listIndex] -= 2;

                        if (work->reloadCounts[work->listIndex] < 0) {
                            work->reloadCounts[work->listIndex] = 0;
                        }
                    }
                }

                gCardBattleState->soraReloadCounter = work->reloadCounts[work->listIndex];
                gCardBattleState->soraReloadGauge = 0;
                gCardBattleState->soraGaugeFullFrame = 4;
                ClearUsedCardSlots(work, 0);
                work->cursors[work->listIndex] = 0;
                work->cardsLeft[work->listIndex] = 0;
                work->reloadPending[work->listIndex] = 1;
                sSoraSelectedCard = NULL;
                sSoraCardRequest = CARD_REQUEST_NONE;
            }
            }
        }

        switch (sSoraCardRequest) {
        case CARD_REQUEST_NONE:
            break;
        case CARD_REQUEST_NEXT_CARD:
            sSoraCardRequest = CARD_REQUEST_NONE;

            if (work->cardsLeft[work->listIndex] > 2) {
                if (sSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED) {
                    SelectNextSoraCard(work, work->listIndex);
                }
            } else if (work->cardsLeft[work->listIndex] > 1 && (sSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED)) {
                SelectOtherSoraCard(work, work->listIndex, 4);
            }

            break;
        case CARD_REQUEST_PREV_CARD:
            sSoraCardRequest = CARD_REQUEST_NONE;

            if (work->cardsLeft[work->listIndex] > 2) {
                if (sSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED) {
                    SelectPrevSoraCard(work, work->listIndex, 4);
                }
            } else if (work->cardsLeft[work->listIndex] > 1 && (sSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED)) {
                SelectOtherSoraCard(work, work->listIndex, 4);
            }

            break;
        case CARD_REQUEST_STOCK_CARD:
            sSoraCardRequest = CARD_REQUEST_NONE;

            if (!(sSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD)) {
                if (work->stockCount == 3) {
                    UseSoraStock(work);
                } else if (sSoraSelectedCard->cardDef->category == 3) {
                    m4aSongNumStart(SONG_SYS_BEEP);
                } else if (work->reloadPending[work->listIndex] == 0) {
                    if (!(sSoraSelectedCard->flags & CARD_DISP_FLAG_NO_CARD)) {
                        if (CanUseSoraSelectedCard()) {
                            if (work->cardsLeft[work->listIndex] > 0 && work->stockCount <= 2 && !gCardBattleState->soraStockActive) {
                                StockSoraCard(work);
                            }
                        } else if (sSoraSelectedCard->flags & CARD_DISP_FLAG_OPEN) {
                            m4aSongNumStart(SONG_SYS_BEEP);
                        }
                    } else if (sSoraSelectedCard->flags & CARD_DISP_FLAG_OPEN) {
                        m4aSongNumStart(SONG_SYS_BEEP);
                    }
                }
            } else if (work->stockCount != 0) {
                UseSoraStock(work);
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }

            work->actionTaken = 1;
            break;
        case CARD_REQUEST_USE_CARD:
            sSoraCardRequest = CARD_REQUEST_NONE;

            if (sSoraSelectedCard->cardDef->category != 3 && !(sSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD)) {
                if (work->reloadPending[work->listIndex] == 0) {
                    if (sSoraSelectedCard->cardDef->flags & CARD_DEF_FLAG_GIMMICK) {
                        UseSoraGimmickCard(work);
                    } else if (!(sSoraSelectedCard->flags & CARD_DISP_FLAG_NO_CARD)) {
                        if (CanUseSoraSelectedCard()) {
                            UseSoraCard(work);
                        } else if (sSoraSelectedCard->flags & CARD_DISP_FLAG_OPEN) {
                            m4aSongNumStart(SONG_SYS_BEEP);
                        }
                    } else if (sSoraSelectedCard->flags & CARD_DISP_FLAG_OPEN) {
                        m4aSongNumStart(SONG_SYS_BEEP);
                    }
                }
            } else if (sSoraSelectedCard->cardDef->category == 3 && !(sSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD)) {
                UseSoraHeartlessCard(work);
            } else if (gGameState.flags & GAME_FLAG_RIKU) {
                RemoveSoraCardDisplays(work);
                sSoraSelectedCard = NULL;
                gBtlWork->flags |= BTL_FLAG_RELOADING;
                work->cardsLeft[work->listIndex] = 0;
                work->reloadPending[work->listIndex] = 1;
            }

            work->actionTaken = 1;
            break;
        case CARD_REQUEST_USE_STOCK:
            sSoraCardRequest = CARD_REQUEST_NONE;

            if (work->stockCount != 0) {
                UseSoraStock(work);
            } else if (!(gBtlWork->flags & BTL_FLAG_CARD_ACTIVE)) {
                m4aSongNumStart(SONG_SYS_BEEP);
            }

            work->actionTaken = 1;
            break;
        case CARD_REQUEST_OPEN_CARDS:
            sSoraCardRequest = CARD_REQUEST_NONE;
            OpenSoraCards(work);
            break;
        case CARD_REQUEST_CLOSE_CARDS:
            work->revCountShown[work->listIndex] = 0;
            work->reloadShown = 0;
            CloseSoraCards(work);
            break;
        case CARD_REQUEST_NOP:
            sSoraCardRequest = CARD_REQUEST_NONE;
            break;
        case CARD_REQUEST_CYCLE_LIST:
            sSoraCardRequest = CARD_REQUEST_NONE;
            CycleSoraCardList(work);
            work->actionTaken = 1;
            break;
        case CARD_REQUEST_SWITCH_LIST:
            sSoraCardRequest = CARD_REQUEST_NONE;
            SwitchSoraCardList(work);
            work->actionTaken = 1;
            break;
        case CARD_REQUEST_AUTO_CYCLE_60:
            work->timer = 60;
            sSoraCardRequest = CARD_REQUEST_NONE;
            SetTaskUpdate(task, (TaskUpdateFunc)UpdateSoraAutoCycle);
            break;
        case CARD_REQUEST_AUTO_CYCLE_180:
            work->timer = 180;
            sSoraCardRequest = CARD_REQUEST_NONE;
            SetTaskUpdate(task, (TaskUpdateFunc)UpdateSoraAutoCycle);
            break;
        case CARD_REQUEST_AUTO_CYCLE_300:
            work->timer = 300;
            sSoraCardRequest = CARD_REQUEST_NONE;
            SetTaskUpdate(task, (TaskUpdateFunc)UpdateSoraAutoCycle);
            break;
        default:
            sSoraCardRequest = CARD_REQUEST_NONE;
            break;
        }

        switch (sSoraCardReloadRequest) {
        case CARD_REQUEST_KING_RELOAD_0:
            sSoraCardReloadRequest = CARD_REQUEST_NONE;

            if (work->listIndex == 0) {
                RemoveSoraCardDisplays(work);
                sSoraSelectedCard = NULL;
            } else {
                RemoveSoraCardDisplays(work);
                work->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
                sSoraSelectedCard = NULL;
            }

            gBtlWork->flags |= BTL_FLAG_RELOADING;
            work->cardsLeft[0] = 0;
            work->reloadPending[0] = 1;
            m4aSongNumStart(SONG_SYS_CHAGEF2);

            if (FadeGetAmount() == 0) {
                FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
            }

            break;
        case CARD_REQUEST_KING_RELOAD_1:
            sSoraCardReloadRequest = CARD_REQUEST_NONE;

            if (work->listIndex == 0) {
                RemoveSoraCardDisplays(work);
                sSoraSelectedCard = NULL;
            } else {
                RemoveSoraCardDisplays(work);
                work->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
                sSoraSelectedCard = NULL;
            }

            m4aSongNumStart(SONG_SYS_CHAGEF2);

            if (FadeGetAmount() == 0) {
                FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
            }

            gBtlWork->flags |= BTL_FLAG_RELOADING;
            work->cardsLeft[0] = 0;
            work->reloadPending[0] = 1;
            break;
        case CARD_REQUEST_KING_RELOAD_2:
            sSoraCardReloadRequest = CARD_REQUEST_NONE;

            if (work->listIndex == 0) {
                RemoveSoraCardDisplays(work);
                sSoraSelectedCard = NULL;
            } else {
                RemoveSoraCardDisplays(work);
                work->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
                sSoraSelectedCard = NULL;
            }

            m4aSongNumStart(SONG_SYS_CHAGEF2);

            if (FadeGetAmount() == 0) {
                FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
            }

            gBtlWork->flags |= BTL_FLAG_RELOADING;
            work->cardsLeft[0] = 0;
            work->reloadPending[0] = 1;
            break;
        case CARD_REQUEST_POTION:
            sSoraCardReloadRequest = CARD_REQUEST_NONE;
            RestoreCardsForPotion(work);

            if (work->listIndex == 0) {
                RemoveSoraCardDisplays(work);
            } else {
                RemoveSoraCardDisplays(work);
                work->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
            }

            TaskPoolUpdate(&work->tasks);
            ClearUsedCardSlots(work, 0);
            work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
            work->cursors[0] = 0;
            CreateSoraCardRing(work, 0);

#ifdef VERSION_EU
            if (work->revCountShown[work->listIndex] == 0) {
                CreateREVCOUNTTask(&work->tasks, (u8*)&work->listIndex, &work->cardsLeft[work->listIndex], &work->revCountShown[work->listIndex], 1);
            }
#endif

            TickSoraHcEffectOnReload();
            break;
        case CARD_REQUEST_HI_POTION:
            sSoraCardReloadRequest = CARD_REQUEST_NONE;
            RestoreCardsForHiPotion(work);

            if (work->listIndex == 0) {
                RemoveSoraCardDisplays(work);
            } else {
                RemoveSoraCardDisplays(work);
                work->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
            }

            TaskPoolUpdate(&work->tasks);
            ClearUsedCardSlots(work, 0);
            work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
            work->cursors[0] = 0;
            CreateSoraCardRing(work, 0);

#ifdef VERSION_EU
            if (work->revCountShown[work->listIndex] == 0) {
                CreateREVCOUNTTask(&work->tasks, (u8*)&work->listIndex, &work->cardsLeft[work->listIndex], &work->revCountShown[work->listIndex], 1);
            }
#endif

            TickSoraHcEffectOnReload();
            break;
        case CARD_REQUEST_MEGA_POTION:
            sSoraCardReloadRequest = CARD_REQUEST_NONE;
            RestoreCardsForMegaPotion(work);
            work->reloadCounts[0] = 0;
            ResetSoraReloadGauge(work);

            if (work->listIndex == 0) {
                RemoveSoraCardDisplays(work);
            } else {
                RemoveSoraCardDisplays(work);
                work->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
            }

            TaskPoolUpdate(&work->tasks);
            ClearUsedCardSlots(work, 0);
            work->cursors[0] = 0;
            work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
            CreateSoraCardRing(work, 0);

#ifdef VERSION_EU
            if (work->revCountShown[work->listIndex] == 0) {
                CreateREVCOUNTTask(&work->tasks, (u8*)&work->listIndex, &work->cardsLeft[work->listIndex], &work->revCountShown[work->listIndex], 1);
            }
#endif

            TickSoraHcEffectOnReload();
            break;
        case CARD_REQUEST_ETHER:
            sSoraCardReloadRequest = CARD_REQUEST_NONE;
            RestoreCardsForEther(work);

            if (work->listIndex == 0) {
                RemoveSoraCardDisplays(work);
            } else {
                RemoveSoraCardDisplays(work);
                work->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
            }

            TaskPoolUpdate(&work->tasks);
            ClearUsedCardSlots(work, 0);
            work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
            work->cursors[0] = 0;
            CreateSoraCardRing(work, 0);

#ifdef VERSION_EU
            if (work->revCountShown[work->listIndex] == 0) {
                CreateREVCOUNTTask(&work->tasks, (u8*)&work->listIndex, &work->cardsLeft[work->listIndex], &work->revCountShown[work->listIndex], 1);
            }
#endif

            TickSoraHcEffectOnReload();
            break;
        case CARD_REQUEST_MEGA_ETHER:
            sSoraCardReloadRequest = CARD_REQUEST_NONE;
            RestoreCardsForMegaEther(work);
            work->reloadCounts[0] = 0;
            ResetSoraReloadGauge(work);

            if (work->listIndex == 0) {
                RemoveSoraCardDisplays(work);
            } else {
                RemoveSoraCardDisplays(work);
                work->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
            }

            TaskPoolUpdate(&work->tasks);
            ClearUsedCardSlots(work, 0);
            work->cursors[0] = 0;
            work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
            CreateSoraCardRing(work, 0);

#ifdef VERSION_EU
            if (work->revCountShown[work->listIndex] == 0) {
                CreateREVCOUNTTask(&work->tasks, (u8*)&work->listIndex, &work->cardsLeft[work->listIndex], &work->revCountShown[work->listIndex], 1);
            }
#endif

            TickSoraHcEffectOnReload();
            break;
        case CARD_REQUEST_ELIXIR:
            sSoraCardReloadRequest = CARD_REQUEST_NONE;
            RestoreCardsForElixir(work);

            if (work->listIndex == 0) {
                RemoveSoraCardDisplays(work);
            } else {
                RemoveSoraCardDisplays(work);
                work->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
            }

            TaskPoolUpdate(&work->tasks);
            ClearUsedCardSlots(work, 0);
            work->cursors[0] = 0;
            work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
            CreateSoraCardRing(work, 0);

#ifdef VERSION_EU
            if (work->revCountShown[work->listIndex] == 0) {
                CreateREVCOUNTTask(&work->tasks, (u8*)&work->listIndex, &work->cardsLeft[work->listIndex], &work->revCountShown[work->listIndex], 1);
            }
#endif

            TickSoraHcEffectOnReload();
            break;
        case CARD_REQUEST_MEGALIXIR:
            sSoraCardReloadRequest = CARD_REQUEST_NONE;
            RestoreCardsForElixir(work);
            work->reloadCounts[0] = 0;
            ResetSoraReloadGauge(work);

            if (work->listIndex == 0) {
                RemoveSoraCardDisplays(work);
            } else {
                RemoveSoraCardDisplays(work);
                work->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
            }

            TaskPoolUpdate(&work->tasks);
            ClearUsedCardSlots(work, 0);
            work->cursors[0] = 0;
            work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
            CreateSoraCardRing(work, 0);

#ifdef VERSION_EU
            if (work->revCountShown[work->listIndex] == 0) {
                CreateREVCOUNTTask(&work->tasks, (u8*)&work->listIndex, &work->cardsLeft[work->listIndex], &work->revCountShown[work->listIndex], 1);
            }
#endif

            TickSoraHcEffectOnReload();
            break;
        case CARD_REQUEST_REMOVE_ITEM_CARDS:
            sSoraCardReloadRequest = CARD_REQUEST_NONE;
            RemoveItemCards(work);

            if (work->listIndex == 0) {
                work->reloadCounts[0] = 0;
                RemoveSoraCardDisplays(work);
                sSoraSelectedCard = NULL;
            } else {
                RemoveSoraCardDisplays(work);
                work->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
                sSoraSelectedCard = NULL;
            }

            m4aSongNumStart(SONG_SYS_CHAGEF2);

            if (FadeGetAmount() == 0) {
                FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
            }

            gBtlWork->flags |= BTL_FLAG_RELOADING;
            work->cardsLeft[0] = 0;
            work->reloadPending[0] = 1;
            break;
        default:
            sSoraCardReloadRequest = CARD_REQUEST_NONE;
            break;
        }

        if (gCardBattleState->pickedFriendCardId != 950 && work->actionTaken == 0 && work->reloadPending[work->listIndex] == 0) {
            gBtlWork->flags |= 0x20000000000LL;
            AddPickedCardToSoraDeck(work);
        }

        if (gCardBattleState->pickedGimmickCardId != 950 && work->actionTaken == 0 && work->reloadPending[work->listIndex] == 0) {
            AddPickedCardToSoraDeck(work);
        }

        if (work->reloadPending[work->listIndex] != 0) {
            if (sSoraSelectedCard != NULL) {
                if (sSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_DONE) {
                    sSoraSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
                    BeginSoraReloadDeal(work);
                    work->reloadPending[work->listIndex] = 0;
                    work->reloadShown = 1;
                    SetTaskUpdate(task, (TaskUpdateFunc)UpdateSoraReloadDeal);
                    TaskPoolUpdate(&work->tasks);
                    TaskPoolUpdate(&gCardBattleState->tasks);
                    args.slot = work->listIndex;
                    args.state = &work->reloadShown;
                    args.mode = 1;
                    TaskCreate(&work->tasks, &gTaskDescRELOAD, &args);
                    return 1;
                }
            } else {
                BeginSoraReloadDeal(work);
                work->reloadPending[work->listIndex] = 0;
                SetTaskUpdate(task, (TaskUpdateFunc)UpdateSoraReloadDeal);
                TaskPoolUpdate(&work->tasks);
                TaskPoolUpdate(&gCardBattleState->tasks);
                return 1;
            }
        } else if (sSoraSelectedCard != NULL && (sSoraSelectedCard->flags & (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_SETTLED)) == (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_SETTLED) && CountAvailableCards(work, work->listIndex) != 0) {
            work->reloadPending[work->listIndex] = 1;
            sSoraSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
            actor = gBtlWork->actor;

            if (actor->hp > 3) {
                actor->hp -= 2;
            }

            gBtlWork->flags |= BTL_FLAG_RELOADING;

            if (gBtlWork->hcEffect != 25) {
                IncrementReloadCount(work);

                if (gBtlWork->hcEffect == 10) {
                    work->reloadCounts[work->listIndex] -= 2;

                    if (work->reloadCounts[work->listIndex] < 0) {
                        work->reloadCounts[work->listIndex] = 0;
                    }
                }
            }
        }

        if (work->stockNameChecked == 0 && AreCardsSettled(work->stock, work->stockCount)) {
            data = gSoraEmptyKeys;

            if (!(gBtlWork->flags & BTL_FLAG_VS_BATTLE)) {
                result = LookupStockName(work->stock, work->stockCount, work->stockValue, &data, flag);
            } else {
                result = LookupLinkStockName(work->stock, work->stockCount, work->stockValue, &data, flag, 0);
            }

            if (result != 108) {
                gCardBattleState->soraStockName = result;

                if (result <= 105) {
                    if (result != 107) {
                        for (i = 0; i < work->stockCount; i++) {
                            work->stock[i]->flags |= CARD_DISP_FLAG_STOCK_NAMED;
                        }

                        if (!gCardBattleState->soraStockNameShown) {
                            TaskCreate(&work->tasks, &gTaskDescStockNameSora, NULL);
                            gCardBattleState->soraStockNameShown = 1;
                        }
                    } else {
                        for (i = 0; i < work->stockCount; i++) {
                            work->stock[i]->flags |= CARD_DISP_FLAG_STOCK_NAMED;
                        }

                        if (!gCardBattleState->soraStockNameShown) {
                            TaskCreate(&work->tasks, &gTaskDescStockNameSora, &data);
                            gCardBattleState->soraStockNameShown = 1;
                        }
                    }
                } else if (work->stockCount == 3) {
                    cards = gSoraEmptyKeys;
                    memset(output, 0, sizeof(output));
                    found = 0;

                    for (i = 0; i < work->stockCount; i++) {
                        cards.keys[i] = work->stock[i]->cardDef->catalogNumber;
                    }

                    stockName = LookupStockPairName(&cards, output, work->stockCount);

                    switch (stockName) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 11:
                    case 15:
                    case 17:
                    case 19:
                    case 21:
                    case 23:
                    case 25:
                    case 27:
                    case 29:
                    case 31:
                    case 33:
                    case 35:
                    case 37:
                    case 39:
                    case 41:
                    case 43:
                    case 44:
                        gCardBattleState->soraStockName = stockName;
                        found = 1;
                        break;
                    }

                    if (!found) {
                        for (i = 0; i < work->stockCount; i++) {
                            work->stock[i]->flags &= ~CARD_DISP_FLAG_STOCK_NAMED;
                        }

                        if (gCardBattleState->soraStockNameShown) {
                            gCardBattleState->soraStockNameShown = 0;
                        }
                    } else {
                        for (i = 0; i < work->stockCount; i++) {
                            work->stock[i]->flags |= CARD_DISP_FLAG_STOCK_NAMED;
                        }

                        if (!gCardBattleState->soraStockNameShown) {
                            TaskCreate(&work->tasks, &gTaskDescStockNameSora, NULL);
                            gCardBattleState->soraStockNameShown = 1;
                        }
                    }
                }
            }

            work->stockNameChecked = 1;
        }
    }

    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&gCardBattleState->tasks);
    gCardBattleState->soraStockCount = work->stockCount;
    work->actionTaken = 0;

    if (gBtlWork->flags & BTL_FLAG_DARK_MODE_CHANGED) {
        gBtlWork->flags &= ~BTL_FLAG_DARK_MODE_CHANGED;
        work->stockNameChecked = 0;
    }

    return 1;
}

static void cardbattle_2(CardBattleWork* work) {
    gCardBattleState->gfx = AnimUpdate(&gCardBattleState->anim);
    gCardBattleState->gfx2 = AnimUpdate(&gCardBattleState->anim2);

    if (gCardBattleState->cardsOpen && work->stockCount != 0 && work->stockValue != 0) {
        DrawSprite(work->x, 4, gStockValueFrames[0], work->tiles, work->palette, NULL, SPRITE_FLAG_NO_MOSAIC,
                   12);
    }

    TaskPoolDraw(&work->tasks);
    TaskPoolDraw(&gCardBattleState->tasks);
}

static void cardbattle_3(CardBattleWork* work) {
    u8 i;

    TaskPoolDestroy(&work->tasks);
    TaskPoolDestroy(&gCardBattleState->tasks);

    for (i = 0; i < 4; i++) {
        if (work->slots[i] != NULL) {
            EwramFree(work->slots[i]);
        }
    }

    ReleaseObjTiles(gCardBattleState->tiles7);
    ReleaseObjTiles(gCardBattleState->tiles6);
    ReleaseObjTiles(gCardBattleState->tiles5);
    ReleaseObjPalette(gCardBattleState->palette);
    ReleaseObjPalette(gCardBattleState->palette2);
    ReleaseObjTiles(gCardBattleState->premiumTiles);
    ReleaseObjTiles(gCardBattleState->premiumTiles2);
    ReleaseObjTiles(gCardBattleState->tiles[0]);
    ReleaseObjTiles(gCardBattleState->tiles[1]);
    ReleaseObjTiles(gCardBattleState->tiles[2]);
    ReleaseObjTiles(gCardBattleState->tiles[3]);
    EwramFree(gCardBattleState);
    gCardBattleState = NULL;
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

s32 UpdateSoraReloadDeal(CardBattleWork* work, Task* task) {
    CardDisplayArgs arg;
    CardDisplayWork* card;
    CardSlot* slot;
    s16 n;
    s16 selectedIndex;
    s16 nextIndex;
    s8 k;

    selectedIndex = 255;
    nextIndex = 255;

    if (gBtlWork->phase == BTL_PHASE_END) {
        if (gRikuBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
            gRikuBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
        }

        m4aSongNumStop(SONG_SYS_RELOAD);

        return 0;
    }

    if ((s16)sSoraSelectedCard->timer == 0) {
        if (CountAvailableCardSlots(work, work->listIndex) > work->dealtCount) {
            sSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
            card = ListPoolFirst(&work->cardDisplays[work->listIndex]);

            while (card != NULL) {
                card->ringIndex++;
                card->ringAngleTarget = gSoraCardRingAngles[card->ringIndex];
                card->timer = 4;
                card->priority += 4;
                card = ListPoolNext(&card->node);
            }

            n = sSoraSelectedCard->args.index - 1;
            slot = FindPrevAvailableSlot(work, work->listIndex, &n);

            if (slot != NULL) {
                arg.pool = &work->cardDisplays[work->listIndex];
                arg.index = n;
                arg.listIndex = work->listIndex;
                arg.slot = slot;
                arg.reloadCount = work->reloadCounts[work->listIndex];

                if (slot->cardId == CARD_ID_RELOAD) {
                    card = TaskCreate(&work->tasks, &gTaskDescCardReload, &arg)->work;
                } else {
                    card = TaskCreate(&work->tasks, &gTaskDescCardSora, &arg)->work;
                }

                card->ringAngleTarget = card->ringAngle = gSoraCardRingAngles[1];
                card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
                card->ringIndex = 1;
                card->timer = 8;
                card->priority = 50;
                card->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_DEALING | CARD_DISP_FLAG_VISIBLE);
                sSoraSelectedCard = card;
                work->dealtCount++;
                work->cardsLeft[work->listIndex]++;
            }
        } else {
            card = ListPoolFirst(&work->cardDisplays[work->listIndex]);

            while (card != NULL) {
                k = card->ringIndex;

                if (k == 1) {
                    selectedIndex = card->args.index;
                }

                if (k == 2) {
                    nextIndex = card->args.index;
                }

                card = ListPoolNext(&card->node);
            }

            n = work->slotCounts[work->listIndex] - 1;
            slot = FindPrevAvailableSlot(work, work->listIndex, &n);

            if (slot != NULL && n != selectedIndex && n != nextIndex) {
                arg.pool = &work->cardDisplays[work->listIndex];
                arg.index = n;
                arg.listIndex = work->listIndex;
                arg.slot = slot;
                arg.reloadCount = work->reloadCounts[work->listIndex];

                if (slot->cardId == CARD_ID_RELOAD) {
                    card = TaskCreate(&work->tasks, &gTaskDescCardReload, &arg)->work;
                } else {
                    card = TaskCreate(&work->tasks, &gTaskDescCardSora, &arg)->work;
                }

                card->ringAngle = gSoraCardRingAngles[3];
                card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
                card->ringIndex = 0;
                card->ringAngleTarget = gSoraCardRingAngles[0];
                card->priority = 60;
                card->flags |= CARD_DISP_FLAG_VISIBLE;
            }

            gBtlWork->flags &= ~BTL_FLAG_RELOADING;
            gBtlWork->flags &= ~0x100;
            work->reloadShown = 0;
            m4aSongNumStop(SONG_SYS_RELOAD);
            sSoraCardRequest = CARD_REQUEST_NONE;
            SetTaskUpdate(task, (TaskUpdateFunc)cardbattleSora_1);
        }
    }

    if (sSoraCardRequest == CARD_REQUEST_CLOSE_CARDS) {
        work->revCountShown[work->listIndex] = 0;
        work->reloadShown = 0;
        CloseSoraCards(work);
        m4aSongNumStop(SONG_SYS_RELOAD);
    }

    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&gCardBattleState->tasks);

    return 1;
}

u16 gRandomHcEffects[47] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 23, 24, 25, 26, 27, 28, 29, 30, 31, 34, 35, 36, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 53,
};

TaskDesc gTaskDescCardBattleSora = {
    "cardbattle",
    (TaskInitFunc)cardbattle_0,
    (TaskUpdateFunc)cardbattleSora_1,
    (TaskDrawFunc)cardbattle_2,
    (TaskDestroyFunc)cardbattle_3,
    sizeof(CardBattleWork),
};

const s32 gSoraCardLayout[5][2] = {
    { -0x3A00, 0xD400 },
    { 0x4000, 0x1800 },
    { 0x3400, 0x1800 },
    { 0x2800, 0x1800 },
    { -0x1400, 0xB800 },
};

const s32 gRikuCardLayout[6][2] = {
    { 0x12A00, 0xD400 },
    { 0xB000, 0x1800 },
    { 0xBC00, 0x1800 },
    { 0xC800, 0x1800 },
    { 0x10400, 0xB800 },
    { 0xD800, 0x8000 },
};

const s32 gPlayedCardCenter[2] = {
    0x7800, 0x8C00,
};

const s32 gPlayedCardAngles[3] = {
    0x5A00, 0, 0xAC00,
};

u8 AreCardsSettled(CardDisplayWork** stock, u8 stockCount) {
    u8 count;
    u8 i;

    i = 0;
    count = 0;

    for (; i < stockCount; i++) {
        if (stock[i]->flags & CARD_DISP_FLAG_SETTLED) {
            count++;
        }
    }

    if (stockCount == count) {
        return 1;
    }

    return 0;
}

void ClearSoraCardPlayFlags() {
    gBtlWork->flags &= ~BTL_FLAG_CARD_ACTIVE;
    gBtlWork->flags &= ~0x100;
    gBtlWork->flags &= ~0x200;
    gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_START;
}

void LoadActiveDeckCardSlots(CardSlot* slots, s32 deckIndex) {
    u16* cardIds;
    u16 n;
    u16 i;

    n = CountActiveDeckCards(deckIndex);
    cardIds = EwramAlloc(n * 2);
    CpuFill16(0, cardIds, n * 2);
    CopyActiveDeckCards(deckIndex, cardIds);

    for (i = 0; i < n; i++) {
        slots[i].unk_06 = 0;
        slots[i].stocked = 0;
        slots[i].removed = 0;
        slots[i].cardId = cardIds[i];
        slots[i].index = i;
        slots[i].restoreOnReload = 0;
    }

    if (deckIndex == 0) {
        slots[n].unk_06 = 0;
        slots[n].stocked = 0;
        slots[n].removed = 0;
        slots[n].cardId = CARD_ID_RELOAD;
        slots[n].index = n;
        slots[n].restoreOnReload = 0;
    }

    EwramFree(cardIds);
}

void LoadTutorialDeckCardSlots(CardSlot* slots) {
    u16 n;
    u16 i;

    n = gTutorialDeck.cardCount;

    for (i = 0; i < n; i++) {
        slots[i].unk_06 = 0;
        slots[i].stocked = 0;
        slots[i].removed = 0;
        slots[i].cardId = gTutorialDeckCardIds[gTutorialDeck.cards[i]];
        slots[i].index = i;
        slots[i].restoreOnReload = 0;
    }

    slots[n].unk_06 = 0;
    slots[n].stocked = 0;
    slots[n].removed = 0;
    slots[n].cardId = CARD_ID_RELOAD;
    slots[n].index = n;
    slots[n].restoreOnReload = 0;
}

void ShuffleCardSlots(CardSlot* slots, u8 count) {
    CardSlot first;
    CardSlot second;
    u8 i;
    u8 firstIndex;
    u8 secondIndex;

    for (i = 0; i < count; i++) {
        firstIndex = GetRandom() % count;
        secondIndex = GetRandom() % count;

        if (firstIndex != secondIndex) {
            first = slots[firstIndex];
            second = slots[secondIndex];
            slots[firstIndex] = second;
            slots[secondIndex] = first;
        }
    }
}

void InitSoraTutorialCardList(CardBattleWork* work, s32 mode) {
    u16 n = gTutorialDeck.cardCount;

    switch (mode) {
    case 0: {
        CardSlot* slots;
        u16 i;

        slots = EwramAlloc((n + 15) * sizeof(CardSlot));
        work->slots[0] = slots;
        CpuFill32(0, slots, (n + 15) * sizeof(CardSlot));

        for (i = 0; i < n + 1; i++) {
            work->slots[0][i].unk_06 = 0;
            work->slots[0][i].stocked = 0;
            work->slots[0][i].removed = 0;
            work->slots[0][i].used = 0;
        }

        for (i = n + 1; i < n + 15; i++) {
            work->slots[0][i].unk_06 = 1;
            work->slots[0][i].stocked = 1;
            work->slots[0][i].removed = 1;
            work->slots[0][i].used = 1;
        }

        LoadTutorialDeckCardSlots(work->slots[0]);
        work->cursors[0] = 0;
        break;
    }
    case 1: {
        CardSlot* slot;
        u16* cursor;
        s32 k;

        slot = EwramAlloc(sizeof(CardSlot));
        work->slots[3] = slot;
        CpuFill32(0, slot, sizeof(CardSlot));
        work->slots[3]->cardId = 0x30FF;
        cursor = &work->cursors[3];
        k = 0xFFFF;
        *cursor = k;
        break;
    }
    }
}

void InitSoraCardList(CardBattleWork* work, s32 mode) {
    u16 n = CountActiveDeckCards(mode);

    switch (mode) {
    case 0:
        if (n != 0) {
            CardSlot* slots;
            u8 i;

            slots = EwramAlloc((n + 15) * sizeof(CardSlot));
            work->slots[0] = slots;
            CpuFill32(0, slots, (n + 15) * sizeof(CardSlot));

            for (i = 0; i < n + 1; i++) {
                work->slots[0][i].unk_06 = 0;
                work->slots[0][i].cardId = CARD_ID_NONE;
                work->slots[0][i].stocked = 0;
                work->slots[0][i].removed = 0;
                work->slots[0][i].used = 0;
            }

            for (i = n + 1; i < n + 15; i++) {
                work->slots[0][i].unk_06 = 1;
                work->slots[0][i].cardId = CARD_ID_NONE;
                work->slots[0][i].stocked = 1;
                work->slots[0][i].removed = 1;
                work->slots[0][i].used = 1;
            }

            LoadActiveDeckCardSlots(work->slots[0], 0);
            work->cursors[0] = 0;
        } else {
            CardSlot* slot;
            u16* cursor;
            s32 k;

            slot = EwramAlloc(sizeof(CardSlot));
            work->slots[0] = slot;
            CpuFill32(0, slot, sizeof(CardSlot));
            work->slots[0]->cardId = 0xFF;
            cursor = &work->cursors[0];
            k = 0xFFFF;
            *cursor = k;
        }

        break;
    case 1:
        if (n != 0) {
            CardSlot* slots;
            u8 i;

            slots = EwramAlloc(n * sizeof(CardSlot));
            work->slots[3] = slots;

            for (i = 0; i < n; i++) {
                work->slots[3][i].unk_06 = 0;
                work->slots[3][i].cardId = CARD_ID_NONE;
                work->slots[3][i].stocked = 0;
                work->slots[3][i].removed = 0;
                work->slots[3][i].used = 0;
            }

            LoadActiveDeckCardSlots(work->slots[3], 1);
            work->cursors[3] = 0;
        } else {
            CardSlot* slot;
            u16* cursor;
            s32 k;

            slot = EwramAlloc(sizeof(CardSlot));
            work->slots[3] = slot;
            CpuFill32(0, slot, sizeof(CardSlot));
            work->slots[3]->cardId = 0x30FF;
            cursor = &work->cursors[3];
            k = 0xFFFF;
            *cursor = k;
        }

        break;
    }
}

u16 CountAvailableCardSlots(CardBattleWork* work, u8 listIndex) {
    u16 count;
    u16 i;
    u16 max;

    max = work->slotCounts[listIndex];
    count = 0;

    for (i = 0; i < max; i++) {
        if (work->slots[listIndex][i].unk_06 == 0 && !work->slots[listIndex][i].stocked && !work->slots[listIndex][i].used && !work->slots[listIndex][i].removed) {
            count++;
        }
    }

    return count;
}

u16 CountAvailableCards(CardBattleWork* work, u8 listIndex) {
    u16 count;
    u16 i;
    u16 max;

    max = work->slotCounts[listIndex];
    count = 0;

    for (i = 0; i < max; i++) {
        if (work->slots[listIndex][i].unk_06 == 0 && !work->slots[listIndex][i].stocked && !work->slots[listIndex][i].used && !work->slots[listIndex][i].removed && work->slots[listIndex][i].cardId != CARD_ID_RELOAD) {
            count++;
        }
    }

    if (sSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD) {
        if (work->cardsLeft[work->listIndex] == 1) {
            count = 0;
        }
    }

    return count;
}

u16 CountRemainingAttackCards(CardBattleWork* work, u8 listIndex) {
    CardSlot* slots;
    u16 count;
    u16 i;
    u16 n;

    n = work->slotCounts[listIndex];
    count = 0;

    for (i = 0; i < n; i++) {
        slots = work->slots[listIndex];

        if (!slots[i].removed) {
            if (slots[i].cardId != CARD_ID_RELOAD) {
                if (gCardDefs[slots[i].cardId & CARD_ID_MASK].category == 0) {
                    count++;
                }
            }
        }
    }

    return count;
}

void ClearUsedCardSlots(CardBattleWork* work, u8 listIndex) {
    u8 i;

    for (i = 0; i < work->slotCounts[listIndex]; i++) {
        if (!work->slots[listIndex][i].stocked) {
            work->slots[listIndex][i].used = 0;
        }
    }
}

void ResetCardSlotsForReload(CardBattleWork* work, u8 listIndex) {
    u8 i;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        for (i = 0; i < work->slotCounts[listIndex]; i++) {
            if (!work->slots[listIndex][i].stocked) {
                work->slots[listIndex][i].used = 0;
                work->slots[listIndex][i].unk_06 = 0;
            }

            if (!(gBtlWork->flags & BTL_FLAG_DARK_MODE)) {
                if (work->slots[listIndex][i].restoreOnReload == 1) {
                    work->slots[listIndex][i].removed = 0;
                    work->slots[listIndex][i].restoreOnReload = 0;
                }
            }
        }
    } else {
        for (i = 0; i < work->slotCounts[listIndex]; i++) {
            if (!work->slots[listIndex][i].stocked) {
                work->slots[listIndex][i].used = 0;
                work->slots[listIndex][i].unk_06 = 0;
            }
        }
    }
}

void BeginSoraReloadDeal(CardBattleWork* work) {
    CardDisplayArgs args;
    CardDisplayWork* card;
    CardSlot* slot;
    u16 n;
    s32 z;

    z = 0;
    work->dealtCount = z;
    ResetCardSlotsForReload(work, work->listIndex);

    if (CountAvailableCardSlots(work, work->listIndex) != z) {
        n = work->slotCounts[work->listIndex] - 1;
        slot = FindPrevAvailableSlot(work, work->listIndex, &n);

        if (slot != NULL) {
            args.pool = &work->cardDisplays[work->listIndex];
            args.index = n;
            args.listIndex = work->listIndex;
            args.slot = slot;
            args.reloadCount = work->reloadCounts[work->listIndex];

            if (slot->cardId == CARD_ID_RELOAD) {
                card = TaskCreate(&work->tasks, &gTaskDescCardReload, &args)->work;
            } else {
                card = TaskCreate(&work->tasks, &gTaskDescCardSora, &args)->work;
            }

            card->ringAngleTarget = card->ringAngle = gSoraCardRingAngles[1];
            card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
            card->ringIndex = 1;
            card->timer = 8;
            card->priority = 50;
            card->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_DEALING | CARD_DISP_FLAG_VISIBLE);
            sSoraSelectedCard = card;
            work->dealtCount++;
            work->cardsLeft[work->listIndex]++;
        }

        m4aSongNumStart(SONG_SYS_RELOAD);
    } else {
        args.pool = &work->cardDisplays[work->listIndex];
        args.index = 0xFFFF;
        args.slot = work->slots[work->listIndex];
        args.listIndex = work->listIndex;
        card = TaskCreate(&work->tasks, &gTaskDescCardNotHave, &args)->work;
        card->ringAngleTarget = card->ringAngle = gSoraCardRingAngles[1];
        card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
        card->priority = 50;
        card->flags |= (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
        sSoraSelectedCard = card;
    }

    z = work->listIndex;

    if (work->cardsLeft[z] > 0) {
        if (work->revCountShown[z] == 0) {
            CreateREVCOUNTTask(&work->tasks, &work->listIndex, &work->cardsLeft[z], &work->revCountShown[z], 1);
        }
    }

    TickSoraHcEffectOnReload();
}

void AddPickedCardToSoraDeck(CardBattleWork* work) {
    CardDisplayWork* node;
    CardSlot* slots;
    s32 z;

    slots = work->slots[0];

    if (gCardBattleState->pickedGimmickCardId == 0x28F) {
        slots[work->slotCounts[0] - 5].cardId = 0x28F;
        slots[work->slotCounts[0] - 5].index = work->slotCounts[0] - 5;
        slots[work->slotCounts[0] - 5].unk_06 = 0;
        slots[work->slotCounts[0] - 5].stocked = 0;
        slots[work->slotCounts[0] - 5].removed = 0;
        slots[work->slotCounts[0] - 5].used = 0;
        gCardBattleState->pickedGimmickCardId = 0x3B6;
    } else {
        slots[work->slotCounts[0] - 14 + gCardBattleState->addedFriendCards[0]].cardId = gCardBattleState->pickedFriendCardId;
        slots[work->slotCounts[0] - 14 + gCardBattleState->addedFriendCards[0]].index = gCardBattleState->addedFriendCards[0] + (work->slotCounts[0] - 14);
        slots[work->slotCounts[0] - 14 + gCardBattleState->addedFriendCards[0]].unk_06 = 0;
        slots[work->slotCounts[0] - 14 + gCardBattleState->addedFriendCards[0]].stocked = 0;
        slots[work->slotCounts[0] - 14 + gCardBattleState->addedFriendCards[0]].removed = 0;
        slots[work->slotCounts[0] - 14 + gCardBattleState->addedFriendCards[0]].used = 0;
        gCardBattleState->pickedFriendCardId = 0x3B6;
        gCardBattleState->addedFriendCards[0]++;
    }

    work->cardsLeft[0]++;
    work->cursors[0] = work->slotCounts[0] - 1;

    if (work->listIndex == 0) {
        work->cursors[0] = sSoraSelectedCard->args.index;
        node = ListPoolFirst(&work->cardDisplays[0]);

        while (node != NULL) {
            node->command = CARD_DISP_COMMAND_REMOVE;
            node = ListPoolNext(&node->node);
        }

        TaskPoolUpdate(&work->tasks);
        CreateSoraCardRing(work, 0);
        z = work->listIndex;

        if (work->revCountShown[z] == 0) {
            CreateREVCOUNTTask(&work->tasks, &work->listIndex, &work->cardsLeft[z], &work->revCountShown[z], 1);
        }
    }
}

void SelectOtherSoraCard(CardBattleWork* work, u8 listIndex, u8 timer) {
    CardDisplayWork* node;

    m4aSongNumStart(SONG_SYS_CLICKI04B);
    node = ListPoolFirst(&work->cardDisplays[listIndex]);

    while (node != NULL) {
        switch (node->ringIndex) {
        case 0:
            node->ringIndex++;
            break;
        case 1:
            node->ringIndex--;
            break;
        case 2:
            node->ringIndex--;
            break;
        }

        node->ringAngleTarget = gSoraCardRingAngles[node->ringIndex];
        node->timer = timer;
        node->flags &= ~CARD_DISP_FLAG_SELECTED;

        if (node->ringIndex == 1) {
            sSoraSelectedCard = node;
            node->flags |= CARD_DISP_FLAG_SELECTED;
        }

        node = ListPoolNext(&node->node);
    }
}

void SelectPrevSoraCard(CardBattleWork* work, u8 listIndex, u8 timer) {
    CardDisplayArgs args;
    CardDisplayWork* card;
    CardDisplayWork* newCard;
    CardSlot* slot;
    s16 prev;
    s32 foundIndex;
    s32 cur;
    s16 n;

    m4aSongNumStart(SONG_SYS_CLICKI04B);
    sSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
    prev = sSoraSelectedCard->args.index;
    card = ListPoolFirst(&work->cardDisplays[listIndex]);

    while (card != NULL) {
        if (card->ringIndex == 0) {
            sSoraSelectedCard = card;
            break;
        }

        card = ListPoolNext(&card->node);
    }

    sSoraSelectedCard->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
    cur = (s16)sSoraSelectedCard->args.index;
    n = cur - 1;

    if (n < 0) {
        n = work->slotCounts[listIndex] - 1;
    }

    slot = FindPrevAvailableSlot(work, listIndex, &n);

    if (slot != NULL) {
        foundIndex = n;

        if (foundIndex != cur && foundIndex != prev) {
            args.pool = &work->cardDisplays[listIndex];
            args.index = n;
            args.listIndex = listIndex;
            args.slot = slot;
            args.reloadCount = work->reloadCounts[listIndex];

            if (slot->cardId == CARD_ID_RELOAD) {
                newCard = TaskCreate(&work->tasks, &gTaskDescCardReload, &args)->work;
            } else {
                newCard = TaskCreate(&work->tasks, &gTaskDescCardSora, &args)->work;
            }

            newCard->ringAngleTarget = newCard->ringAngle = gSoraCardRingAngles[3];
            newCard->swingAngleTarget = newCard->swingAngle = gSoraCardSwingAngles[0];
            newCard->ringIndex = 3;
            newCard->priority = 60;
            newCard->flags |= CARD_DISP_FLAG_VISIBLE;
        }
    }

    card = ListPoolFirst(&work->cardDisplays[listIndex]);

    while (card != NULL) {
        card->ringIndex++;

        if (card->ringIndex > 3) {
            card->ringIndex = 0;
        }

        card->priority += 4;
        card->ringAngleTarget = gSoraCardRingAngles[card->ringIndex];
        card->timer = timer;
        card = ListPoolNext(&card->node);
    }

    sSoraSelectedCard->priority = 50;
}

void SelectNextSoraCard(CardBattleWork* work, u8 listIndex) {
    CardDisplayArgs args;
    CardDisplayWork* card;
    CardDisplayWork* newCard;
    CardSlot* slot;
    s16 prev;
    s32 foundIndex;
    s32 cur;
    s16 n;

    m4aSongNumStart(SONG_SYS_CLICKI04B);
    sSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
    prev = sSoraSelectedCard->args.index;
    card = ListPoolFirst(&work->cardDisplays[listIndex]);

    while (card != NULL) {
        if (card->ringIndex == 2) {
            sSoraSelectedCard = card;
            break;
        }

        card = ListPoolNext(&card->node);
    }

    sSoraSelectedCard->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
    cur = (s16)sSoraSelectedCard->args.index;
    n = cur + 1;

    if (n >= work->slotCounts[listIndex]) {
        n = 0;
    }

    slot = FindNextAvailableSlot(work, listIndex, &n);

    if (slot != NULL) {
        foundIndex = n;

        if (foundIndex != cur && foundIndex != prev) {
            args.pool = &work->cardDisplays[work->listIndex];
            args.index = n;
            args.listIndex = listIndex;
            args.slot = slot;
            args.reloadCount = work->reloadCounts[listIndex];

            if (slot->cardId == CARD_ID_RELOAD) {
                newCard = TaskCreate(&work->tasks, &gTaskDescCardReload, &args)->work;
            } else {
                newCard = TaskCreate(&work->tasks, &gTaskDescCardSora, &args)->work;
            }

            newCard->ringAngleTarget = newCard->ringAngle = gSoraCardRingAngles[3];
            newCard->swingAngleTarget = newCard->swingAngle = gSoraCardSwingAngles[0];
            newCard->ringIndex = 3;
            newCard->priority = 60;
            newCard->flags |= CARD_DISP_FLAG_VISIBLE;
        }
    }

    card = ListPoolFirst(&work->cardDisplays[listIndex]);

    while (card != NULL) {
        card->ringIndex--;

        if (card->ringIndex < 0) {
            card->ringIndex = 3;
        }

        card->priority += 4;
        card->ringAngleTarget = gSoraCardRingAngles[card->ringIndex];
        card->timer = 4;
        card = ListPoolNext(&card->node);
    }

    sSoraSelectedCard->priority = 50;
}

void ApplyTrickmasterToSoraCard(CardBattleWork* work) {
    if (gBtlWork->flags & (BTL_FLAG_HUM_BATTLE | BTL_FLAG_VS_BATTLE)) {
        if (gRikuBtlWork->hcEffect == 0x30) {
            if (sSoraSelectedCard->value != 0) {
                sSoraSelectedCard->value -= gCardBattleState->activeValue;
            }

            gRikuBtlWork->hcEffectCount--;
        }
    }
}

void ApplyTrickmasterToSoraStock(CardBattleWork* work) {
    u8 dmg = gCardBattleState->activeValue;
    u8 i;

    if (gBtlWork->flags & (BTL_FLAG_HUM_BATTLE | BTL_FLAG_VS_BATTLE)) {
        if (gRikuBtlWork->hcEffect == 0x30) {
            if (work->stockValue != 0) {
                for (i = 0; i < work->stockCount; i++) {
                    CardDisplayWork* card = work->stock[i];
                    s32 remaining;

                    if (card->value > dmg) {
                        card->value -= dmg;
                        break;
                    }

                    remaining = dmg - card->value;
                    card->value = 0;
                    dmg = remaining;
                }
            }

            gRikuBtlWork->hcEffectCount--;
        }
    }
}

u16 GetRandomHcEffect() {
    u16 i;

    i = GetRandom() % 47;

    return gRandomHcEffects[i];
}

u16 GetNextRandomHcEffect(u16* index) {
    u16 hcEffect;
    u16 i;

    i = *index;
    hcEffect = gRandomHcEffects[i];
    *index = i + 1;

    if (*index > 46) {
        *index = 0;
    }

    return hcEffect;
}

void TrySoraCardBreak(CardBattleWork* work) {
    s8 n;
    u8 skip;
    u8 i;

#ifdef VERSION_EU
    s32 j;
    s32 k;
#endif

    if (gBtlWork->hcEffect == 1) {
        n = sSoraSelectedCard->value + 1;

        if (n > 9) {
            n = 9;
        }

        if (sSoraSelectedCard->value < 9) {
            TaskCreate(&gCardBattleState->tasks, &gTaskDescNumberPlus, &sSoraSelectedCard->cardDef);
        }

        sSoraSelectedCard->value = n;
        sSoraSelectedCard->valueModified = 1;
    } else if (gBtlWork->hcEffect == 21) {
        if (sSoraSelectedCard->value != 0) {
            n = sSoraSelectedCard->value - 1;
            sSoraSelectedCard->value--;
            sSoraSelectedCard->valueModified = 1;
        } else {
            n = 0;
            sSoraSelectedCard->valueModified = 1;
        }
    } else {
        n = sSoraSelectedCard->value;
    }

    if (gCardBattleState->activeValue > n && n != 0) {
        return;
    }

    skip = 0;

    if (gBtlWork->flags & (BTL_FLAG_HUM_BATTLE | BTL_FLAG_VS_BATTLE)) {
        if (gRikuBtlWork->hcEffect == 2 && gCardBattleState->activeCards[0]->cardDef->category == 0 &&
            !gCardBattleState->rikuStockActive) {
            skip = 1;
        }

#ifdef VERSION_EU
        if (gRikuBtlWork->hcEffect == 20) {
            for (j = 0; j < gCardBattleState->activeCardCount; j++) {
                if (gCardBattleState->activeCards[j]->cardDef->move == 22) {
                    skip = 1;
                }
            }
        }

        if (gRikuBtlWork->hcEffect == 29) {
            for (k = 0; k < gCardBattleState->activeCardCount; k++) {
                if (gCardBattleState->activeCards[k]->cardDef->category == 2 &&
                    !(gCardBattleState->activeCards[k]->cardDef->flags & CARD_DEF_FLAG_FRIEND)) {
                    skip = 1;
                }
            }
        }
#else
        if (gRikuBtlWork->hcEffect == 20 && gCardBattleState->activeCards[0]->cardDef->move == 22 &&
            !gCardBattleState->rikuStockActive) {
            skip = 1;
        }

        if (gRikuBtlWork->hcEffect == 29 && gCardBattleState->activeCards[0]->cardDef->category == 2 &&
            !gCardBattleState->rikuStockActive) {
            skip = 1;
        }
#endif
    }

    if (skip) {
        return;
    }

    for (i = 0; i < gCardBattleState->activeCardCount; i++) {
        gCardBattleState->activeCards[i]->flags |= CARD_DISP_FLAG_BROKEN;
    }

    gBtlWork->flags |= BTL_FLAG_CARD_BREAK;

    if (gCardBattleState->activeValue != n) {
        if (n == 0) {
            if (gCardBattleState->activeValue > 9) {
                gBtlWork->breakDifference = 9;
            } else {
                gBtlWork->breakDifference = gCardBattleState->activeValue;
            }
        } else if (n - gCardBattleState->activeValue > 9) {
            gBtlWork->breakDifference = 9;
        } else {
            gBtlWork->breakDifference = n - gCardBattleState->activeValue;
        }

        m4aSongNumStart(SONG_BTL_GARD);
        gBtlWork->flags |= BTL_FLAG_CARD_PLAY_START;
        gBtlWork->flags |= BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
        sSoraSelectedCard->flags |= CARD_DISP_FLAG_IN_PLAY;
        ApplyTrickmasterToSoraCard(work);
        gCardBattleState->activeCards[0] = sSoraSelectedCard;
        gCardBattleState->activeCardCount = 1;
        gCardBattleState->activeValue = sSoraSelectedCard->value;
        gBtlWork->soraOwnsPlay = 1;

        if (!(gGameState.flags & GAME_FLAG_DARK_POINTS_LOCKED) && AddBreakDarkPoints() && !(gBtlWork->flags & BTL_FLAG_DARK_MODE)) {
            gCardBattleState->darkModeReady = 1;
        }
    } else {
        ApplyTrickmasterToSoraCard(work);
        gBtlWork->breakDifference = 0;
        gBtlWork->flags &= ~BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_START;
        m4aSongNumStart(SONG_SYS_DROW);
        gBtlWork->soraOwnsPlay = 1;
        gCardBattleState->activeCards[0] = sSoraSelectedCard;
        gCardBattleState->activeCardCount = 1;
        gCardBattleState->activeValue = sSoraSelectedCard->value;
    }
}

extern BtlWork* gBtlWorkAlias __asm__("gBtlWork");

s32 UseSoraCard(CardBattleWork* work) {
    CardDisplayArgs args;
    u16 index;
    CardDisplayWork* card;
    CardSlot* slot;
    u8 found;
    u32 prev;
    u32 other;
    BtlWork* btl;
    u64 flags;

    btl = gBtlWorkAlias;
    flags = btl->flags;

    if ((flags & BTL_FLAG_CARD_ACTIVE) == 0) {
        gCardBattleState->activeCards[0] = sSoraSelectedCard;

        if (btl->hcEffect == 1) {
            gCardBattleState->activeValue = sSoraSelectedCard->value + 1;

            if (sSoraSelectedCard->value < 9) {
                TaskCreate(&gCardBattleState->tasks, &gTaskDescNumberPlus, &sSoraSelectedCard->cardDef);
            }

            sSoraSelectedCard->value++;

            if (sSoraSelectedCard->value > 9) {
                sSoraSelectedCard->value = 9;
            }

            if (gCardBattleState->activeValue > 9) {
                gCardBattleState->activeValue = 9;
            }

            sSoraSelectedCard->valueModified = 1;
        } else if (btl->hcEffect == 21) {
            if (sSoraSelectedCard->value != 0) {
                sSoraSelectedCard->value--;
                sSoraSelectedCard->valueModified = 1;
                gCardBattleState->activeValue = sSoraSelectedCard->value;
            } else {
                sSoraSelectedCard->valueModified = 1;
                gCardBattleState->activeValue = 0;
            }
        } else {
            gCardBattleState->activeValue = sSoraSelectedCard->value;
        }

        gCardBattleState->activeCardCount = 1;
        sSoraSelectedCard->flags |= CARD_DISP_FLAG_IN_PLAY;
        gBtlWork->soraOwnsPlay = 1;
        gBtlWork->flags |= BTL_FLAG_CARD_PLAY_START;
        gBtlWork->flags |= BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags |= BTL_FLAG_PLAYER_CARD_BUSY;
    } else {
        if (btl->soraOwnsPlay == 1) {
            return 1;
        }

        if ((flags & BTL_FLAG_CARD_PLAY_ENDED) == 0) {
            TrySoraCardBreak(work);
        } else {
            TrySoraCardBreak(work);
        }

        gBtlWork->flags |= BTL_FLAG_PLAYER_CARD_BUSY;
    }

    work->cardsLeft[work->listIndex]--;

    if (work->cardsLeft[work->listIndex] == 1) {
        sSoraSelectedCard->args.slot->unk_0B = 1;
    }

    if ((sSoraSelectedCard->cardDef->flags & CARD_DEF_FLAG_ITEM) && (sSoraSelectedCard->flags & CARD_DISP_FLAG_IN_PLAY)) {
        sSoraSelectedCard->args.slot->removed = 1;
    }

    if (sSoraSelectedCard->cardDef->flags & CARD_DEF_FLAG_FRIEND) {
        sSoraSelectedCard->args.slot->removed = 1;
    }

    if (sSoraSelectedCard->premium == 1) {
        sSoraSelectedCard->args.slot->removed = 1;

        if (CountRemainingAttackCards(work, 0) == 0) {
            sSoraSelectedCard->args.slot->removed = 0;
        }
    }

    work->playedCards[0] = sSoraSelectedCard;
    sSoraSelectedCard->command = CARD_DISP_COMMAND_PLAY;
    sSoraSelectedCard->priority = 50;
    sSoraSelectedCard->args.slot->used = 1;
    sSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SETTLED;
    TickSoraHcEffectOnCardUse();

    if (gBtlWork->hcEffect == 37) {
        u16 hcEffect = GetRandomHcEffect();
        SyncSoraHcEffect(work);
        gCardBattleState->soraHcEffect = hcEffect;
        func_0807B458(work, gCardBattleState->soraHcEffect);
        ApplySoraHcEffect(work);
        gBtlWork->hcEffectCount = gHcEffectDefs[gBtlWork->hcEffect].count;
    }

    other = 0xFF;
    index = other;
    found = 0;
    sSoraSelectedCard = NULL;

    card = ListPoolFirst(&work->cardDisplays[work->listIndex]);

    while (card != NULL) {
        if (card->ringIndex == 2) {
            card->ringIndex--;
            card->timer = 4;
            card->ringAngleTarget = gSoraCardRingAngles[card->ringIndex];
            card->priority = 50;
            sSoraSelectedCard = card;
            found = 1;
            break;
        }

        card = ListPoolNext(&card->node);
    }

    if (sSoraSelectedCard == NULL) {
        card = ListPoolFirst(&work->cardDisplays[work->listIndex]);

        while (card != NULL) {
            if (card->ringIndex == 0) {
                card->ringIndex++;
                card->timer = 4;
                card->ringAngleTarget = gSoraCardRingAngles[card->ringIndex];
                card->priority = 50;
                sSoraSelectedCard = card;
                break;
            }

            card = ListPoolNext(&card->node);
        }
    }

    if (found) {
        prev = sSoraSelectedCard->args.index;
        index = prev + 1;

        if (index >= work->slotCounts[work->listIndex]) {
            index = 0;
        }

        for (card = ListPoolFirst(&work->cardDisplays[work->listIndex]); card != NULL; card = ListPoolNext(&card->node)) {
            if (card->ringIndex == 0) {
                other = card->args.index;
                break;
            }
        }

        slot = FindNextAvailableSlot(work, work->listIndex, &index);

        if (slot != NULL && index != prev && index != other) {
            args.pool = &work->cardDisplays[work->listIndex];
            args.index = index;
            args.listIndex = work->listIndex;
            args.slot = slot;
            args.reloadCount = work->reloadCounts[work->listIndex];

            if (slot->cardId == CARD_ID_RELOAD) {
                card = TaskCreate(&work->tasks, &gTaskDescCardReload, &args)->work;
            } else {
                card = TaskCreate(&work->tasks, &gTaskDescCardSora, &args)->work;
            }

            card->ringAngle = gSoraCardRingAngles[3];
            card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
            card->ringIndex = 2;
            card->ringAngleTarget = gSoraCardRingAngles[2];
            card->priority = 60;
            card->timer = 4;
            card->flags |= CARD_DISP_FLAG_VISIBLE;
        }
    }

    sSoraSelectedCard->flags |= CARD_DISP_FLAG_SELECTED;

    if (gBtlWork->hcEffect == 40 && (sSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD) && work->cardsLeft[work->listIndex] == 1) {
        RemoveSoraCardDisplays(work);
        sSoraSelectedCard = NULL;
        gBtlWork->flags |= BTL_FLAG_RELOADING;
        work->cardsLeft[0] = 0;
        work->reloadPending[0] = 1;
        m4aSongNumStart(SONG_SYS_CHAGEF2);

        if (FadeGetAmount() == 0) {
            FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
        }
    }

    return 1;
}

s32 UseSoraHeartlessCard(CardBattleWork* work) {
    CardDisplayArgs args;
    u16 index;
    CardDisplayWork* card;
    CardSlot* slot;
    u8 found;
    u32 prev;
    u32 other;

    if (sSoraSelectedCard->flags & CARD_DISP_FLAG_NO_CARD) {
        return 1;
    }

    m4aSongNumStart(SONG_SYS_CLICKI04);

    if (gCardBattleState->soraHcEffect == 0) {
        gCardBattleState->soraHcEffect = sSoraSelectedCard->cardDef->move;
        func_0807B458(work, gCardBattleState->soraHcEffect);
        ApplySoraHcEffect(work);
    } else {
        SyncSoraHcEffect(work);
        gCardBattleState->soraHcEffect = sSoraSelectedCard->cardDef->move;
        func_0807B458(work, gCardBattleState->soraHcEffect);
        ApplySoraHcEffect(work);
        gCardBattleState->soraHcEffectReplaced = 1;
    }

    sSoraSelectedCard->args.slot->removed = 1;
    sSoraSelectedCard->command = CARD_DISP_COMMAND_HEARTLESS;
    sSoraSelectedCard->args.slot->used = 1;
    sSoraSelectedCard->priority = 50;
    sSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SETTLED;

    if (work->stockValue != 0) {
        UpdateSpriteFrameTiles(work->tiles, gStockValueFrames[0], gStockValueTiles + ((work->stockValue - 1) << 7));
        work->xSteps = 8;
    }

    work->cardsLeft[work->listIndex]--;
    other = 0xFF;
    index = other;
    found = 0;
    sSoraSelectedCard = NULL;

    card = ListPoolFirst(&work->cardDisplays[work->listIndex]);

    while (card != NULL) {
        if (card->ringIndex == 2) {
            card->ringIndex--;
            card->timer = 4;
            card->ringAngleTarget = gSoraCardRingAngles[card->ringIndex];
            card->priority = 50;
            sSoraSelectedCard = card;
            found = 1;
            break;
        }

        card = ListPoolNext(&card->node);
    }

    if (sSoraSelectedCard == NULL) {
        card = ListPoolFirst(&work->cardDisplays[work->listIndex]);

        while (card != NULL) {
            if (card->ringIndex == 0) {
                card->ringIndex++;
                card->timer = 4;
                card->ringAngleTarget = gSoraCardRingAngles[card->ringIndex];
                card->priority = 50;
                sSoraSelectedCard = card;
                break;
            }

            card = ListPoolNext(&card->node);
        }
    }

    if (sSoraSelectedCard == NULL) {
        args.pool = &work->cardDisplays[work->listIndex];
        args.index = 0xFFFF;
        args.slot = work->slots[work->listIndex];
        args.listIndex = work->listIndex;
        card = TaskCreate(&work->tasks, &gTaskDescCardNotHave, &args)->work;
        card->ringAngleTarget = card->ringAngle = gSoraCardRingAngles[1];
        card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
        card->priority = 50;
        card->flags |= (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
        sSoraSelectedCard = card;
        return 0;
    }

    if (found) {
        prev = sSoraSelectedCard->args.index;
        index = prev + 1;

        if (index >= work->slotCounts[work->listIndex]) {
            index = 0;
        }

        for (card = ListPoolFirst(&work->cardDisplays[work->listIndex]); card != NULL; card = ListPoolNext(&card->node)) {
            if (card->ringIndex == 0) {
                other = card->args.index;
                break;
            }
        }

        slot = FindNextAvailableSlot(work, work->listIndex, &index);

        if (slot != NULL && index != prev && index != other) {
            args.pool = &work->cardDisplays[work->listIndex];
            args.index = index;
            args.listIndex = work->listIndex;
            args.slot = slot;
            args.reloadCount = work->reloadCounts[work->listIndex];

            if (slot->cardId == CARD_ID_RELOAD) {
                card = TaskCreate(&work->tasks, &gTaskDescCardReload, &args)->work;
            } else {
                card = TaskCreate(&work->tasks, &gTaskDescCardSora, &args)->work;
            }

            card->ringAngle = gSoraCardRingAngles[3];
            card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
            card->ringIndex = 2;
            card->ringAngleTarget = gSoraCardRingAngles[2];
            card->priority = 60;
            card->timer = 4;
            card->flags |= CARD_DISP_FLAG_VISIBLE;
        }
    }

    sSoraSelectedCard->flags |= CARD_DISP_FLAG_SELECTED;
    return 1;
}

s32 UseSoraGimmickCard(CardBattleWork* work) {
    CardDisplayArgs args;
    u16 index;
    CardDisplayWork* card;
    CardSlot* slot;
    u8 found;
    u32 prev;
    u32 other;

    if (sSoraSelectedCard->flags & CARD_DISP_FLAG_NO_CARD) {
        return 1;
    }

    gBtlWork->flags |= BTL_FLAG_GIMMICK_CARD_ACTIVE;
    m4aSongNumStart(SONG_SYS_CLICKI04);
    sSoraSelectedCard->args.slot->removed = 1;
    sSoraSelectedCard->command = CARD_DISP_COMMAND_GIMMICK;
    sSoraSelectedCard->args.slot->used = 1;
    sSoraSelectedCard->priority = 50;
    sSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SETTLED;
    work->cardsLeft[work->listIndex]--;
    other = 0xFF;
    index = other;
    found = 0;
    sSoraSelectedCard = NULL;

    card = ListPoolFirst(&work->cardDisplays[work->listIndex]);

    while (card != NULL) {
        if (card->ringIndex == 2) {
            card->ringIndex--;
            card->timer = 4;
            card->ringAngleTarget = gSoraCardRingAngles[card->ringIndex];
            card->priority = 50;
            sSoraSelectedCard = card;
            found = 1;
            break;
        }

        card = ListPoolNext(&card->node);
    }

    if (sSoraSelectedCard == NULL) {
        card = ListPoolFirst(&work->cardDisplays[work->listIndex]);

        while (card != NULL) {
            if (card->ringIndex == 0) {
                card->ringIndex++;
                card->timer = 4;
                card->ringAngleTarget = gSoraCardRingAngles[card->ringIndex];
                card->priority = 50;
                sSoraSelectedCard = card;
                break;
            }

            card = ListPoolNext(&card->node);
        }
    }

    if (found) {
        prev = sSoraSelectedCard->args.index;
        index = prev + 1;

        if (index >= work->slotCounts[work->listIndex]) {
            index = 0;
        }

        for (card = ListPoolFirst(&work->cardDisplays[work->listIndex]); card != NULL; card = ListPoolNext(&card->node)) {
            if (card->ringIndex == 0) {
                other = card->args.index;
                break;
            }
        }

        slot = FindNextAvailableSlot(work, work->listIndex, &index);

        if (slot != NULL && index != prev && index != other) {
            args.pool = &work->cardDisplays[work->listIndex];
            args.index = index;
            args.listIndex = work->listIndex;
            args.slot = slot;
            args.reloadCount = work->reloadCounts[work->listIndex];

            if (slot->cardId == CARD_ID_RELOAD) {
                card = TaskCreate(&work->tasks, &gTaskDescCardReload, &args)->work;
            } else {
                card = TaskCreate(&work->tasks, &gTaskDescCardSora, &args)->work;
            }

            card->ringAngle = gSoraCardRingAngles[3];
            card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
            card->ringIndex = 2;
            card->ringAngleTarget = gSoraCardRingAngles[2];
            card->priority = 60;
            card->timer = 4;
            card->flags |= CARD_DISP_FLAG_VISIBLE;
        }
    }

    sSoraSelectedCard->flags |= CARD_DISP_FLAG_SELECTED;
    gCardBattleState->gimmickCardCount--;
    return 1;
}

s32 StockSoraCard(CardBattleWork* work) {
    CardDisplayArgs args;
    u16 index;
    CardDisplayWork* card;
    CardSlot* slot;
    u8 found;
    u32 prev;
    u32 other;
    u8 n;
    u32 active;

    if (!(sSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED)) {
        return 1;
    }

    if ((u16)(sSoraSelectedCard->cardDef->flags & CARD_DEF_FLAG_GIMMICK)) {
        m4aSongNumStart(SONG_SYS_BEEP);
        return 1;
    }

    if (gCardBattleState->unk_0B4 == 112 || gCardBattleState->unk_0B4 == 109) {
        return 1;
    }

    work->stockNameChecked = 0;
    gCardBattleState->soraStockNameShown = 0;
    m4aSongNumStart(SONG_SYS_KETEI2);
    sSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SETTLED;
    sSoraSelectedCard->flags |= CARD_DISP_FLAG_STOCKED;
    sSoraSelectedCard->command = CARD_DISP_COMMAND_STOCK;
    sSoraSelectedCard->stockIndex = work->stockCount;
    sSoraSelectedCard->priority = 50 - (3 - work->stockCount) * 4;
    work->stock[work->stockCount] = sSoraSelectedCard;
    gCardBattleState->soraStockedCards[gCardBattleState->soraStockedCount] = sSoraSelectedCard;
    sSoraSelectedCard->args.slot->stocked = active = 1;
    sSoraSelectedCard->args.slot->used = active;

    if (gBtlWork->hcEffect == 1) {
        n = sSoraSelectedCard->value + 1;

        if (n > 9) {
            n = 9;
        }

        sSoraSelectedCard->valueModified = active;
        sSoraSelectedCard->value = n;

        if (sSoraSelectedCard->value < 9) {
            TaskCreate(&gCardBattleState->tasks, &gTaskDescNumberPlus, &sSoraSelectedCard->cardDef);
        }
    } else if (gBtlWork->hcEffect == 21) {
        if (sSoraSelectedCard->value != 0) {
            n = sSoraSelectedCard->value - 1;
            sSoraSelectedCard->value--;
            sSoraSelectedCard->valueModified = active;
        } else {
            n = 0;
            sSoraSelectedCard->valueModified = active;
        }
    } else {
        n = sSoraSelectedCard->value;
    }

    work->stockValue += n;
    work->stockCount++;
    gCardBattleState->soraStockedCount++;

    if (work->stockValue != 0) {
        UpdateSpriteFrameTiles(work->tiles, gStockValueFrames[0], gStockValueTiles + ((work->stockValue - 1) << 7));
        work->xSteps = 8;
    }

    work->cardsLeft[work->listIndex]--;

    if (sSoraSelectedCard->cardDef->flags & CARD_DEF_FLAG_FRIEND) {
        sSoraSelectedCard->args.slot->removed = 1;
    }

    if (gBtlWork->hcEffect == 37) {
        u16 hcEffect = GetRandomHcEffect();
        SyncSoraHcEffect(work);
        gCardBattleState->soraHcEffect = hcEffect;
        func_0807B458(work, gCardBattleState->soraHcEffect);
        ApplySoraHcEffect(work);
        gBtlWork->hcEffectCount = gHcEffectDefs[gBtlWork->hcEffect].count;
    }

    other = 0xFF;
    index = other;
    found = 0;
    sSoraSelectedCard = NULL;

    card = ListPoolFirst(&work->cardDisplays[work->listIndex]);

    while (card != NULL) {
        if (card->ringIndex == 2) {
            card->ringIndex--;
            card->timer = 4;
            card->ringAngleTarget = gSoraCardRingAngles[card->ringIndex];
            card->priority = 50;
            sSoraSelectedCard = card;
            found = 1;
            break;
        }

        card = ListPoolNext(&card->node);
    }

    if (sSoraSelectedCard == NULL) {
        card = ListPoolFirst(&work->cardDisplays[work->listIndex]);

        while (card != NULL) {
            if (card->ringIndex == 0) {
                card->ringIndex++;
                card->timer = 4;
                card->ringAngleTarget = gSoraCardRingAngles[card->ringIndex];
                card->priority = 50;
                sSoraSelectedCard = card;
                break;
            }

            card = ListPoolNext(&card->node);
        }
    }

    if (found) {
        prev = sSoraSelectedCard->args.index;
        index = prev + 1;

        if (index >= work->slotCounts[work->listIndex]) {
            index = 0;
        }

        for (card = ListPoolFirst(&work->cardDisplays[work->listIndex]); card != NULL; card = ListPoolNext(&card->node)) {
            if (card->ringIndex == 0) {
                other = card->args.index;
                break;
            }
        }

        slot = FindNextAvailableSlot(work, work->listIndex, &index);

        if (slot != NULL && index != prev && index != other) {
            args.pool = &work->cardDisplays[work->listIndex];
            args.index = index;
            args.listIndex = work->listIndex;
            args.slot = slot;
            args.reloadCount = work->reloadCounts[work->listIndex];

            if (slot->cardId == CARD_ID_RELOAD) {
                card = TaskCreate(&work->tasks, &gTaskDescCardReload, &args)->work;
            } else {
                card = TaskCreate(&work->tasks, &gTaskDescCardSora, &args)->work;
            }

            card->ringAngle = gSoraCardRingAngles[3];
            card->swingAngleTarget = card->swingAngle = gSoraCardSwingAngles[0];
            card->ringIndex = 2;
            card->ringAngleTarget = gSoraCardRingAngles[2];
            card->priority = 60;
            card->timer = 4;
            card->flags |= CARD_DISP_FLAG_VISIBLE;
        }
    }

    sSoraSelectedCard->flags |= CARD_DISP_FLAG_SELECTED;

    if (gBtlWork->hcEffect == 40 && (sSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD) && work->cardsLeft[work->listIndex] == 1) {
        RemoveSoraCardDisplays(work);
        sSoraSelectedCard = NULL;
        work->cardsLeft[0] = 0;
        work->reloadPending[0] = 1;
        m4aSongNumStart(SONG_SYS_CHAGEF2);

        if (FadeGetAmount() == 0) {
            FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
        }
    }

    return 1;
}

void RemoveSoraCardDisplays(CardBattleWork* work) {
    CardDisplayWork* node;
    u8 i;

    for (i = 0; i < 4; i++) {
        node = ListPoolFirst(&work->cardDisplays[i]);

        while (node != NULL) {
            if (node->command < CARD_DISP_COMMAND_PLAY || node->command > CARD_DISP_COMMAND_STOCK) {
                node->command = CARD_DISP_COMMAND_REMOVE;
            }

            node = ListPoolNext(&node->node);
        }
    }

    if (sSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
        sSoraSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
    }
}

void RemoveIdleSoraCardDisplays(CardBattleWork* work) {
    CardDisplayWork* node;
    u8 i;

    for (i = 0; i < 4; i++) {
        node = ListPoolFirst(&work->cardDisplays[i]);

        while (node != NULL) {
            if (node->command == CARD_DISP_COMMAND_NONE) {
                node->command = CARD_DISP_COMMAND_REMOVE;
            }

            node = ListPoolNext(&node->node);
        }
    }
}

void OpenSoraCards(CardBattleWork* work) {
    CardDisplayWork* node;
    u8 i;

    for (i = 0; i < work->stockCount; i++) {
        work->stock[i]->flags |= CARD_DISP_FLAG_OPEN;
    }

    for (i = 0; i < 4; i++) {
        node = ListPoolFirst(&work->cardDisplays[i]);

        while (node != NULL) {
            node->flags |= CARD_DISP_FLAG_OPEN;
            node = ListPoolNext(&node->node);
        }
    }

    gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
    gCardBattleState->cardsOpen = 1;
    work->cardsClosed = 0;
}

void CloseSoraCards(CardBattleWork* work) {
    CardDisplayWork* node;
    u8 i;

    for (i = 0; i < work->stockCount; i++) {
        work->stock[i]->flags &= ~CARD_DISP_FLAG_OPEN;
    }

    for (i = 0; i < 4; i++) {
        node = ListPoolFirst(&work->cardDisplays[i]);

        while (node != NULL) {
            node->flags &= ~CARD_DISP_FLAG_OPEN;
            node = ListPoolNext(&node->node);
        }
    }

    gCardBattleState->soraHcEffect = 0;
    gBtlWork->flags |= BTL_FLAG_CARD_PLAY_ENDED;
    gCardBattleState->cardsOpen = 0;
    gCardBattleState->soraStockNameShown = 0;
    work->cardsClosed = 1;
}

void TrySoraStockBreak(CardBattleWork* work) {
#ifdef VERSION_EU
    CardDisplayWork* previous[3];
#endif
    StockKeys stockKeys;
    u8 flag;
    u16 total;
    u8 i;
    u8 n;
    u8 skip;
    s32 result;
    CardDisplayWork** activeCard;
#ifdef VERSION_EU
    u8 previousCount;
    s32 j;
    s32 k;
#endif

    n = work->stockValue;
    total = 0;
    stockKeys = gSoraEmptyKeys;

    if (gCardBattleState->activeValue > n && n != 0) {
        return;
    }

    skip = 0;

    if (gBtlWork->flags & (BTL_FLAG_HUM_BATTLE | BTL_FLAG_VS_BATTLE)) {
        if (gRikuBtlWork->hcEffect == 2 && gCardBattleState->activeCards[0]->cardDef->category == 0 &&
            !gCardBattleState->rikuStockActive) {
            skip = 1;
        }

#ifdef VERSION_EU
        if (gRikuBtlWork->hcEffect == 20) {
            for (j = 0; j < gCardBattleState->activeCardCount; j++) {
                if (gCardBattleState->activeCards[j]->cardDef->move == 22) {
                    skip = 1;
                }
            }
        }

        if (gRikuBtlWork->hcEffect == 29) {
            for (k = 0; k < gCardBattleState->activeCardCount; k++) {
                if (gCardBattleState->activeCards[k]->cardDef->category == 2 &&
                    !(gCardBattleState->activeCards[k]->cardDef->flags & CARD_DEF_FLAG_FRIEND)) {
                    skip = 1;
                }
            }
        }
#else
        if (gRikuBtlWork->hcEffect == 20 && gCardBattleState->activeCards[0]->cardDef->move == 22 &&
            !gCardBattleState->rikuStockActive) {
            skip = 1;
        }

        if (gRikuBtlWork->hcEffect == 29 && gCardBattleState->activeCards[0]->cardDef->category == 2 &&
            !gCardBattleState->rikuStockActive) {
            skip = 1;
        }
#endif
    }

    if (skip) {
        return;
    }

    for (i = 0; i < gCardBattleState->activeCardCount; i++) {
        gCardBattleState->activeCards[i]->flags |= CARD_DISP_FLAG_BROKEN;
    }

    gBtlWork->flags |= BTL_FLAG_CARD_BREAK;

    if (gCardBattleState->activeValue != n) {
        if (n == 0) {
            if (gCardBattleState->activeValue > 9) {
                gBtlWork->breakDifference = 9;
            } else {
                gBtlWork->breakDifference = gCardBattleState->activeValue;
            }
        } else {
            if (n - gCardBattleState->activeValue > 9) {
                gBtlWork->breakDifference = 9;
            } else {
                gBtlWork->breakDifference = n - (u8)gCardBattleState->activeValue;
            }
        }

        if (!(gGameState.flags & GAME_FLAG_DARK_POINTS_LOCKED) && AddBreakDarkPoints() && !(gBtlWork->flags & BTL_FLAG_DARK_MODE)) {
            gCardBattleState->darkModeReady = 1;
        }

        gBtlWork->flags |= BTL_FLAG_CARD_PLAY_START;
        gBtlWork->flags |= BTL_FLAG_PLAYER_CARD_BUSY;
        gBtlWork->flags |= BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
        ApplyTrickmasterToSoraStock(work);

#ifndef VERSION_EU
        if (!(gBtlWork->flags & BTL_FLAG_VS_BATTLE)) {
            result = LookupStockName(work->stock, work->stockCount, work->stockValue, &stockKeys, &flag);
        } else {
            result = LookupLinkStockName(work->stock, work->stockCount, work->stockValue, &stockKeys, &flag, 0);
        }

        if ((u16)result == 52 && (gBtlWork->flags & (BTL_FLAG_HUM_BATTLE | BTL_FLAG_VS_BATTLE))) {
            for (i = 0; i < gCardBattleState->activeCardCount; i++) {
                if (gCardBattleState->activeCards[i]->args.slot->used == 1) {
                    gCardBattleState->activeCards[i]->args.slot->removed = 1;
                    gCardBattleState->activeCards[i]->flags |= 0x80000000;
                }
            }
        }
#endif

        for (i = 0; i < work->stockCount; i++) {
            total += work->stock[i]->value;
        }

        gCardBattleState->activeValue = total;
#ifdef VERSION_EU
        previousCount = gCardBattleState->activeCardCount;
#endif
        gCardBattleState->activeCardCount = work->stockCount;

        for (i = 0; i < work->stockCount; i++) {
#ifdef VERSION_EU
            previous[i] = gCardBattleState->activeCards[i];
#endif
            activeCard = gCardBattleState->activeCards;
            activeCard += i;
            *activeCard = work->stock[i];
            work->stock[i]->flags |= CARD_DISP_FLAG_IN_PLAY;

            if (work->stock[i]->cardDef->flags & CARD_DEF_FLAG_ITEM) {
                work->stock[i]->args.slot->removed = 1;
            }
        }

        gBtlWork->soraOwnsPlay = 1;
        gCardBattleState->soraStockActive = 1;
        m4aSongNumStart(SONG_BTL_GARD);

#ifdef VERSION_EU
        if (!(gBtlWork->flags & BTL_FLAG_VS_BATTLE)) {
            result = LookupStockName(work->stock, work->stockCount, work->stockValue, &stockKeys, &flag);
        } else {
            result = LookupLinkStockName(work->stock, work->stockCount, work->stockValue, &stockKeys, &flag, 0);
        }

        if ((u16)result == 52 && (gBtlWork->flags & (BTL_FLAG_HUM_BATTLE | BTL_FLAG_VS_BATTLE))) {
            for (i = 0; i < previousCount; i++) {
                if (previous[i]->args.slot->used == 1) {
                    previous[i]->args.slot->removed = 1;
                    previous[i]->flags |= 0x80000000;
                }
            }
        }
#endif

        return;
    }

    gBtlWork->breakDifference = 0;
    ApplyTrickmasterToSoraStock(work);
    m4aSongNumStart(SONG_SYS_DROW);
    gBtlWork->flags &= ~BTL_FLAG_CARD_ACTIVE;
    gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
    gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_START;
    gCardBattleState->soraStockActive = 0;
    gBtlWork->soraOwnsPlay = 1;
}

void UseSoraStock(CardBattleWork* work) {
    CardDisplayWork** activeCard;
    CardDisplayWork* empty;
    u64 flags;
    u8 i;
    u8 n;

    for (i = 0, n = 0; i < work->stockCount; i++) {
        if (work->stock[i]->flags & CARD_DISP_FLAG_SETTLED) {
            n++;
        }
    }

    if (n < work->stockCount) {
        return;
    }

    gCardBattleState->unk_0C0 = 0;
    gCardBattleState->soraStockNameShown = 0;
    work->stockNameChecked = 0;
    flags = gBtlWork->flags;

    if ((flags & BTL_FLAG_CARD_ACTIVE) == 0) {
        gCardBattleState->activeCardCount = work->stockCount;

        for (i = 0; i < work->stockCount; i++) {
            activeCard = gCardBattleState->activeCards;
            activeCard += i;
            *activeCard = work->stock[i];
            work->stock[i]->priority = i * 4 + 50;

            if (work->stock[i]->cardDef->flags & CARD_DEF_FLAG_ITEM) {
                work->stock[i]->args.slot->removed = 1;
            }

            work->stock[i]->flags |= (CARD_DISP_FLAG_IN_PLAY | CARD_DISP_FLAG_UNOPPOSED);
        }

        gCardBattleState->activeValue = work->stockValue;
        gBtlWork->soraOwnsPlay = 1;
        gBtlWork->flags |= BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags |= BTL_FLAG_CARD_PLAY_START;
        gBtlWork->flags |= BTL_FLAG_PLAYER_CARD_BUSY;
        gCardBattleState->soraStockActive = 1;
    } else {
        if (gBtlWork->soraOwnsPlay == 1) {
            return;
        }

        if ((flags & BTL_FLAG_CARD_PLAY_ENDED) == 0) {
            TrySoraStockBreak(work);
            gBtlWork->flags |= BTL_FLAG_PLAYER_CARD_BUSY;
        } else {
            TrySoraStockBreak(work);
            gBtlWork->flags |= BTL_FLAG_PLAYER_CARD_BUSY;
        }
    }

    for (i = 0; i < work->stockCount; i++) {
        work->stock[i]->args.slot->stocked = 0;

        if (work->stock[i]->cardDef->flags & CARD_DEF_FLAG_ITEM) {
            work->stock[i]->args.slot->removed = 1;
        } else if (i == 0 && gBtlWork->hcEffect != 15) {
            work->stock[0]->args.slot->removed = 1;
        }
    }

    if (CountRemainingAttackCards(work, 0) == 0) {
        for (i = 0; i < work->stockCount; i++) {
            if (work->stock[i]->args.listIndex == 0) {
                work->stock[i]->args.slot->removed = 0;
                break;
            }
        }
    }

    i = 0;

    if (i < work->stockCount) {
        do {
            empty = NULL;
            n = i;
            work->playedCards[n] = work->stock[n];
            work->stock[n]->command = CARD_DISP_COMMAND_PLAY;
            work->stock[n] = empty;
            i = ++n;
        } while (i < work->stockCount);
    }

    TickSoraHcEffectOnCardUse();
    work->stockCount = 0;
    gCardBattleState->soraStockedCount = 0;
    work->stockValue = 0;
    ClearStockedCardSlots(work);
    work->stockNameChecked = 0;
}

void ClearStockedCardSlots(CardBattleWork* work) {
    CardSlot* slots;
    u8 i;
    u8 j;

    for (i = 0; i < 4; i++) {
        slots = work->slots[i];

        // @bug? Should be slotCounts[i].
        for (j = 0; j < work->slotCounts[j]; j++) {
            slots[j].stocked = 0;
        }
    }
}

u8 CountSoraCardDisplays(CardBattleWork* work, u8 listIndex) {
    CardDisplayWork* node;
    u8 count;

    count = 0;
    node = ListPoolFirst(&work->cardDisplays[listIndex]);

    while (node != NULL) {
        count++;
        node = ListPoolNext(&node->node);
    }

    return count;
}

u8 CountSoraCardDisplaysByCategory(CardBattleWork* work, u8 kind) {
    CardDisplayWork* node;
    u8 count;

    count = 0;
    node = ListPoolFirst(&work->cardDisplays[kind]);

    while (node != NULL) {
        if ((node->flags & (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_RELOAD_GAUGE)) == 0) {
            if (kind == 2) {
                count++;
            } else if (node->cardDef->category == kind) {
                count++;
            }
        }

        node = ListPoolNext(&node->node);
    }

    return count;
}

void SwitchSoraCardList(CardBattleWork* work) {
    CardDisplayWork* node = NULL;

    if (!(sSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED)) {
        return;
    }

    m4aSongNumStart(SONG_SYS_CANSEL);

    if (gBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
        gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
    }

    work->revCountShown[work->listIndex] = 0;

    if (work->reloadPending[work->listIndex] == 0) {
        work->cursors[work->listIndex] = sSoraSelectedCard->args.index;
        node = ListPoolFirst(&work->cardDisplays[work->listIndex]);

        while (node != NULL) {
            node->swingSteps = 4;
            node->swingAngleTarget = gSoraCardSwingAngles[3];
            node->command = CARD_DISP_COMMAND_REMOVE;
            node->flags &= ~CARD_DISP_FLAG_SELECTED;
            node = ListPoolNext(&node->node);
        }
    } else {
        work->selectedCards[work->listIndex] = sSoraSelectedCard;
        sSoraSelectedCard->swingAngleTarget = gSoraCardSwingAngles[3];
        sSoraSelectedCard->swingSteps = 4;
        sSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
    }

    switch (work->listIndex) {
    case 0:
        work->listIndex = 3;
        break;
    case 3:
        work->listIndex = 0;
        break;
    }

    if (work->reloadPending[work->listIndex] == 0) {
        CreateSoraCardRing(work, work->listIndex);
        node = ListPoolFirst(&work->cardDisplays[work->listIndex]);

        while (node != NULL) {
            node->swingAngleTarget = gSoraCardSwingAngles[0];
            node->swingAngle = gSoraCardSwingAngles[0];
            node->swingSteps = 1;
            node->timer = 1;
            node = ListPoolNext(&node->node);
        }

        if (work->revCountShown[work->listIndex] == 0) {
            if (work->listIndex != 0) {
                if (work->cardsLeft[work->listIndex] > 0) {
                    CreateREVCOUNTTask(&work->tasks, &work->listIndex, &work->cardsLeft[work->listIndex], &work->revCountShown[work->listIndex], 1);
                }
            } else {
                if (work->cardsLeft[work->listIndex] > 1) {
                    CreateREVCOUNTTask(&work->tasks, &work->listIndex, &work->cardsLeft[work->listIndex], &work->revCountShown[work->listIndex], 1);
                }
            }
        }
    } else {
        sSoraSelectedCard = work->selectedCards[work->listIndex];
        sSoraSelectedCard->swingAngleTarget = gSoraCardSwingAngles[0];
        sSoraSelectedCard->swingAngle = gSoraCardSwingAngles[1];
        sSoraSelectedCard->swingSteps = 1;
        sSoraSelectedCard->timer = 1;
        sSoraSelectedCard->flags |= CARD_DISP_FLAG_SELECTED;
    }

    gCardBattleState->soraListIndex = work->listIndex;
}

void CycleSoraCardList(CardBattleWork* work) {
    CardDisplayWork* node = NULL;

    m4aSongNumStart(SONG_SYS_CANSEL);

    if (gBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
        gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
    }

    work->revCountShown[work->listIndex] = 0;

    if (work->reloadPending[work->listIndex] == 0) {
        work->cursors[work->listIndex] = sSoraSelectedCard->args.index;
        node = ListPoolFirst(&work->cardDisplays[work->listIndex]);

        while (node != NULL) {
            node->swingSteps = 12;
            node->swingAngleTarget = gSoraCardSwingAngles[1];
            node->command = CARD_DISP_COMMAND_REMOVE;
            node = ListPoolNext(&node->node);
        }
    } else {
        work->selectedCards[work->listIndex] = sSoraSelectedCard;
        sSoraSelectedCard->swingAngleTarget = gSoraCardSwingAngles[3];
        sSoraSelectedCard->swingSteps = 12;
        sSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
    }

    switch (work->listIndex) {
    case 0:
        work->listIndex = 2;
        break;
    case 1:
        work->listIndex = 0;
        break;
    case 2:
        work->listIndex = 3;
        break;
    case 3:
        work->listIndex = 1;
        break;
    }

    if (work->reloadPending[work->listIndex] == 0) {
        CreateSoraCardRing(work, work->listIndex);
        node = ListPoolFirst(&work->cardDisplays[work->listIndex]);

        while (node != NULL) {
            node->swingSteps = 12;
            node->swingAngleTarget = gSoraCardSwingAngles[0];
            node->swingAngle = gSoraCardSwingAngles[0];
            node->timer = 12;
            node = ListPoolNext(&node->node);
        }

        if (work->revCountShown[work->listIndex] == 0 && work->cardsLeft[work->listIndex] > 0) {
            CreateREVCOUNTTask(&work->tasks, &work->listIndex, &work->cardsLeft[work->listIndex], &work->revCountShown[work->listIndex], 1);
        }
    } else {
        sSoraSelectedCard = work->selectedCards[work->listIndex];
        sSoraSelectedCard->swingAngleTarget = gSoraCardSwingAngles[0];
        sSoraSelectedCard->swingAngle = gSoraCardSwingAngles[1];
        sSoraSelectedCard->swingSteps = 12;
        sSoraSelectedCard->timer = 12;
        sSoraSelectedCard->flags |= CARD_DISP_FLAG_SELECTED;
    }

    gCardBattleState->soraListIndex = work->listIndex;
}

void IncrementReloadCount(CardBattleWork* work) {
    s16* reloadCount;

    switch (work->listIndex) {
    case 0:
        work->reloadCounts[0]++;
        break;
    case 1:
        work->reloadCounts[1]++;
        break;
    case 2:
        break;
    }

    reloadCount = &work->reloadCounts[0];
    reloadCount += work->listIndex;

    if (*reloadCount > 2) {
        *reloadCount = 2;
    }
}

void func_0807B3C4(s32 a) {
}

u8 GetSoraCardListIndex() {
    u8 result;

    if (gCardBattleState == NULL) {
        result = 0xFF;
    } else {
        result = gCardBattleState->soraListIndex;
    }

    return result;
}

u8 GetSoraStockCount() {
    u8 result;

    if (gCardBattleState == NULL) {
        result = 0;
    } else {
        result = gCardBattleState->soraStockCount;
    }

    return result;
}

u8 GetRikuStockCount() {
    if (gCardBattleState != NULL) {
        return gCardBattleState->rikuStockCount;
    }

    return 0;
}

void CreateBosscardTask(TaskPool* pool) {
    BtlObj* obj;
    u32 kind;

    obj = ListPoolFirst(&gBtlWork->pool);

    while (obj != NULL) {
        kind = obj->kind;

        switch (kind) {
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
            TaskCreate(pool, &gTaskDescBosscard, &kind);
            return;
        }

        obj = ListPoolNext(&obj->node);
    }
}

void func_0807B458(CardBattleWork* work, u16 hcEffect) {
}

void SyncSoraHcEffect(CardBattleWork* work) {
    gBtlWork->hcEffect = gCardBattleState->soraHcEffect;
}

void ApplySoraHcEffect(CardBattleWork* work) {
    u32* hcEffect;
    u16* soraHcEffect;
    s16* reloadCount;
    s16* reloadCounts;

    if (gBtlWork->flags & (BTL_FLAG_HUM_BATTLE | BTL_FLAG_VS_BATTLE)) {
        if (gRikuBtlWork->hcEffect != 41) {
            gBtlWork->hcEffect = gCardBattleState->soraHcEffect;
        } else {
            gBtlWork->hcEffect = 0;
            gCardBattleState->soraHcEffect = 0;
        }

        hcEffect = &gBtlWork->hcEffect;

        if (*hcEffect == 41) {
#ifdef VERSION_EU
            if (gRikuBtlWork->hcEffect == 47 && (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION)) {
                gRikuBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;
            }
#endif

            gCardBattleState->rikuHcEffect = 0;
            gRikuBtlWork->hcEffect = 0;
            gRikuBtlWork->hcEffectCount = 0;
            gBtlWork->hcEffect = 0;
            gBtlWork->hcEffectCount = 0;
        }

        soraHcEffect = &gCardBattleState->soraHcEffect;

        if (*soraHcEffect == 45) {
            if (gRikuBtlWork->hcEffect != 0) {
                gBtlWork->hcEffect = gRikuBtlWork->hcEffect;
                gCardBattleState->soraHcEffect = gCardBattleState->rikuHcEffect;
            } else {
                gBtlWork->hcEffect = 0;
                gCardBattleState->rikuHcEffect = 0;
            }
        }

        if (gBtlWork->hcEffect == 47) {
            reloadCounts = &work->reloadCounts[0];
            reloadCount = reloadCounts;
            *reloadCount++ = 2;
            *reloadCount = 2;
        }
    } else {
        if (gCardBattleState->soraHcEffect != 41 && gCardBattleState->soraHcEffect != 45) {
            gBtlWork->hcEffect = gCardBattleState->soraHcEffect;
        } else {
            gBtlWork->hcEffect = 0;
        }
    }
}

u8 UpdateSoraAutoCycle(CardBattleWork* work, void* task) {
    s16 cardsLeft;

    cardsLeft = work->cardsLeft[work->listIndex];

    if (cardsLeft > 2) {
        if (sSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED) {
            SelectPrevSoraCard(work, work->listIndex, 2);
        }
    } else if (cardsLeft > 1) {
        if (sSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED) {
            SelectOtherSoraCard(work, work->listIndex, 2);
        }
    }

    work->timer--;

    if (work->timer <= 0) {
        SetTaskUpdate(task, (TaskUpdateFunc)cardbattleSora_1);
    }

    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&gCardBattleState->tasks);
    return 1;
}

u8 CanUseSoraSelectedCard() {
    if (gBtlWork->hcEffect == 38) {
        if (sSoraSelectedCard->cardDef->category != 1) {
            return 1;
        }

        if (!(sSoraSelectedCard->cardDef->flags & CARD_DEF_FLAG_SUMMON)) {
            return 1;
        }

        return 0;
    } else if (gBtlWork->hcEffect == 39) {
        if (sSoraSelectedCard->cardDef->category != 1) {
            return 1;
        }

        if (sSoraSelectedCard->cardDef->flags & CARD_DEF_FLAG_SUMMON) {
            return 1;
        }

        return 0;
    }

    return 1;
}

void LoadPremiumCardGfx(CardBattleState* state) {
    state->premiumTiles = AllocObjTiles(0x280, NULL);
    SetObjTileSource(state->premiumTiles, gCardPremiumTiles);
    AnimInit(&state->anim, gCardPremiumAnims, gCardPremiumFrames);
    AnimStart(&state->anim, 0, ANIM_FLAG_LOOP);
    state->gfx = AnimGetGfx(&state->anim);
    state->premiumTiles2 = AllocObjTiles(0x100, NULL);
    SetObjTileSource(state->premiumTiles2, gCardPremiumSmallTiles);
    AnimInit(&state->anim2, gCardPremiumSmallAnims, gCardPremiumSmallFrames);
    AnimStart(&state->anim2, 0, ANIM_FLAG_LOOP);
    state->gfx2 = AnimGetGfx(&state->anim2);
}

void ResetSoraReloadGauge(CardBattleWork* work) {
    CardBattleState* state;

    state = gCardBattleState;
    state->soraReloadGauge = 0;
    state->soraReloadCounter = 0;
    state->soraGaugeFullFrame = 4;
    state->soraGaugeAnim = 2;
    state->reloadGaugeFull[0] = 0;
}

void RestoreCardsForPotion(CardBattleWork* work) {
    CardSlot* slots;
    s32 i;
    u32 id;
    u8 category;

    slots = work->slots[0];

    for (i = 0; i < work->slotCounts[0]; i++) {
        id = slots[i].cardId;

        if (id != 0xFFFF) {
            if (id != 0xFFFE) {
                category = gCardDefs[id & CARD_ID_MASK].category;

                if (category == 0) {
                    if (!slots[i].removed) {
                        slots[i].unk_06 = 0;
                    }
                } else if (category == 1) {
                    if (slots[i].removed == 1 || slots[i].stocked == 1 || slots[i].used == 1) {
                        slots[i].unk_06 = 1;
                    }
                }
            }
        }
    }
}

void RestoreCardsForHiPotion(CardBattleWork* work) {
    CardSlot* slots;
    s32 i;
    u32 id;
    u8 category;

    slots = work->slots[0];

    for (i = 0; i < work->slotCounts[0]; i++) {
        id = slots[i].cardId;

        if (id != 0xFFFF) {
            if (id != 0xFFFE) {
                category = gCardDefs[id & CARD_ID_MASK].category;

                if (category == 0) {
                    slots[i].removed = 0;
                    slots[i].unk_06 = 0;
                } else if (category != 2) {
                    if (slots[i].used == 1 || slots[i].removed == 1 || slots[i].stocked == 1) {
                        slots[i].unk_06 = 1;
                    }
                }
            }
        }
    }
}

void RestoreCardsForMegaPotion(CardBattleWork* work) {
    CardSlot* slots;
    s32 i;
    u32 id;
    u8 category;

    slots = work->slots[0];

    for (i = 0; i < work->slotCounts[0]; i++) {
        id = slots[i].cardId;

        if (id != 0xFFFF) {
            if (id != 0xFFFE) {
                category = gCardDefs[id & CARD_ID_MASK].category;

                if (category == 0) {
                    slots[i].unk_06 = 0;
                    slots[i].removed = 0;
                } else if (category != 2) {
                    if (slots[i].used == 1 || slots[i].removed == 1 || slots[i].stocked == 1) {
                        slots[i].unk_06 = 1;
                    }
                }
            }
        }
    }
}

void RestoreCardsForEther(CardBattleWork* work) {
    CardSlot* slots;
    s32 i;
    u32 id;
    u8 category;

    slots = work->slots[0];

    for (i = 0; i < work->slotCounts[0]; i++) {
        id = slots[i].cardId;

        if (id != 0xFFFF) {
            if (id != 0xFFFE) {
                category = gCardDefs[id & CARD_ID_MASK].category;

                if (category == 1) {
                    if (!slots[i].removed) {
                        slots[i].unk_06 = 0;
                    }
                } else if (category != 2) {
                    if (slots[i].removed == 1 || slots[i].stocked == 1 || slots[i].used == 1) {
                        slots[i].unk_06 = 1;
                    }
                }
            }
        }
    }
}

void RestoreCardsForMegaEther(CardBattleWork* work) {
    CardSlot* slots;
    s32 i;
    u32 id;
    u8 category;

    slots = work->slots[0];

    for (i = 0; i < work->slotCounts[0]; i++) {
        id = slots[i].cardId;

        if (id != 0xFFFF) {
            if (id != 0xFFFE) {
                category = gCardDefs[id & CARD_ID_MASK].category;

                if (category == 1) {
                    slots[i].unk_06 = 0;
                    slots[i].removed = 0;
                } else if (category != 2) {
                    if (slots[i].used == 1 || slots[i].removed == 1 || slots[i].stocked == 1) {
                        slots[i].unk_06 = 1;
                    }
                }
            }
        }
    }
}

void RestoreCardsForElixir(CardBattleWork* work) {
    CardSlot* slots;
    s32 i;

    slots = work->slots[0];

    for (i = 0; i < work->slotCounts[0]; i++) {
        if (slots[i].cardId != CARD_ID_NONE) {
            if (slots[i].cardId != CARD_ID_RELOAD) {
                if (gCardDefs[slots[i].cardId & CARD_ID_MASK].category != 2) {
                    slots[i].unk_06 = 0;
                    slots[i].removed = 0;
                }
            }
        }
    }
}

void RemoveItemCards(CardBattleWork* work) {
    CardSlot* slots;
    s32 i;

    slots = work->slots[0];

    for (i = 0; i < work->slotCounts[0]; i++) {
        if (slots[i].cardId != CARD_ID_NONE) {
            if (slots[i].cardId != CARD_ID_RELOAD) {
                if (gCardDefs[slots[i].cardId & CARD_ID_MASK].flags & CARD_DEF_FLAG_ITEM) {
                    if (!slots[i].removed) {
                        slots[i].restoreOnReload = 1;
                    }

                    slots[i].removed = 1;
                }
            }
        }
    }
}

u8 AddBreakDarkPoints() {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        if (!(gBtlWork->flags & BTL_FLAG_DARK_MODE)) {
            gBtlWork->darkPoints += gBtlWork->breakDifference;
        } else if (gBtlWork->breakDifference < 0) {
            gBtlWork->darkPoints += gBtlWork->breakDifference;
        }

        if (gBtlWork->darkPoints > 999) {
            gBtlWork->darkPoints = 999;
        } else if (gBtlWork->darkPoints < 0) {
            gBtlWork->darkPoints = 0;
        }
    }

    if (gBtlWork->darkPoints > 29 && !(gBtlWork->flags & BTL_FLAG_DARK_MODE)) {
        return 1;
    }

    return 0;
}

void TickSoraHcEffectOnReload() {
    switch (gBtlWork->hcEffect) {
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 16:
    case 17:
    case 19:
    case 20:
    case 21:
    case 24:
    case 25:
    case 29:
    case 30:
    case 31:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 42:
    case 51:
    case 53:
        gBtlWork->hcEffectCount--;
        break;
    }
}

void TickSoraHcEffectOnCardUse() {
    if (gBtlWork->hcEffect == 50) {
        gBtlWork->hcEffectCount--;
    }
}

void SoraCardInit(CardDisplayWork* work, CardDisplayArgs* args) {
    u16 index;

    CpuFill32(0, work, sizeof(CardDisplayWork));
    work->tiles = NULL;
    work->tiles2 = NULL;
    work->tiles3 = NULL;
    work->tiles4 = NULL;
    work->tiles5 = NULL;
    work->palette2 = NULL;
    work->palette = NULL;
    work->children = NULL;
    work->args = *args;
    work->flags = 0;
    index = work->args.index;

    if ((s16)index != -1) {
        LookupSoraCardDef(&work->args, &work->cardDef, index);

        if (work->args.slot->cardId == CARD_ID_RELOAD) {
            work->flags |= CARD_DISP_FLAG_RELOAD_CARD;
        }
    } else {
        work->flags = CARD_DISP_FLAG_NO_CARD;
    }

    // @bug A "not have" display has no slot (NULL read).
    if (work->args.slot->cardId & 0x8000) {
        work->premium = 1;
    } else {
        work->premium = 0;
    }

    work->scaleX = 0x100;
    work->scaleY = 0x100;
    work->bobAngle = 0;
    work->angle = 0;
    work->ringAngle = 0;
    work->ringAngleTarget = 0;
    work->ringRadius = 0;
    work->ringRadiusTarget = 0;
    work->swingAngle = 0;
    work->swingAngleTarget = 0;
    work->command = CARD_DISP_COMMAND_NONE;
    work->priority = 60;
    work->timer = 4;
    work->phase = CARD_STOCK_PHASE_RISE;
    work->ringRadius = 0;
    work->ringRadiusTarget = 0x2400;
    work->swingSteps = 0;
    work->ringCenterX = gSoraCardLayout[0][0];
    work->ringCenterY = gSoraCardLayout[0][1];
    work->x = gSoraCardLayout[4][0];
    work->y = gSoraCardLayout[4][1];

    if (work->cardDef != NULL) {
        work->value = work->cardDef->value;
    } else {
        work->value = 0;
    }

    work->valueModified = 0;
    work->flags |= CARD_DISP_FLAG_OPEN;
    work->flags &= ~CARD_DISP_FLAG_SETTLED;
    LinkSoraCardDisplay(work);
}

u8 SoraCardUpdate(CardDisplayWork* work, void* task) {
    u8 (*fn)(CardDisplayWork*, void*);

    if (work->flags & CARD_DISP_FLAG_DEALING) {
        if (!(work->flags & CARD_DISP_FLAG_GFX_LOADED)) {
            LoadCardDisplayGfx(work);
            work->flags |= CARD_DISP_FLAG_GFX_LOADED;
        }

        if (work->flags & CARD_DISP_FLAG_DEALING) {
            work->timer = 8;
            UpdateSoraCardValue(work);
            SetTaskUpdate(task, (TaskUpdateFunc)SoraCardDeal);
            return 1;
        }
    }

    if ((s16)work->timer == 0) {
        if (IsCardDisplayOffScreen(work)) {
            ListPoolRemove(&work->node, work->args.pool);
            return 0;
        }

        if (!(work->flags & CARD_DISP_FLAG_GFX_LOADED)) {
            LoadCardDisplayGfx(work);
            work->flags |= CARD_DISP_FLAG_GFX_LOADED;
            fn = SoraCardUpdateLoaded;
            SetTaskUpdate(task, (TaskUpdateFunc)fn);
            return fn(work, task);
        }
    }

    if (work->flags & CARD_DISP_FLAG_FROZEN) {
        return 1;
    }

    if (!(work->flags & CARD_DISP_FLAG_OPEN)) {
        work->flags &= ~CARD_DISP_FLAG_SETTLED;
        SetTaskUpdate(task, (TaskUpdateFunc)SoraCardClosed);
    }

    UpdateSoraCardRingPosition(work);
    work->bobAngle += 4;
    return DispatchSoraCardCommand(work, task);
}

u8 SoraCardUpdateLoaded(CardDisplayWork* work, void* task) {
    if (IsCardDisplayOffScreen(work)) {
        ListPoolRemove(&work->node, work->args.pool);
        return 0;
    }

    if (work->flags & CARD_DISP_FLAG_FROZEN) {
        return 1;
    }

    if (!(work->flags & CARD_DISP_FLAG_OPEN)) {
        work->flags &= ~CARD_DISP_FLAG_SETTLED;
        SetTaskUpdate(task, (TaskUpdateFunc)SoraCardClosed);
    }

    UpdateSoraCardRingPosition(work);
    work->bobAngle += 4;
    return DispatchSoraCardCommand(work, task);
}

static void card_2(CardDisplayWork* work) {
    s16 y;
    void* gfx;
    ObjAffine* affine;
    u8 j;
    u8 k;
    u16 attr;

    attr = 0x410;

    if (IsMessageWindowOpen() == 1) {
        y = work->y >> 8;
    } else {
        y = (work->y >> 8) + (gSineTable[work->bobAngle] >> 8);
    }

    gfx = work->cardDef->gfx;

    if (!(work->flags & CARD_DISP_FLAG_VISIBLE)) {
        return;
    }

    if (!(work->flags & CARD_DISP_FLAG_GFX_LOADED)) {
        return;
    }

    if (!(work->flags & CARD_DISP_FLAG_STOCKED)) {
        affine = AllocObjAffine(work->angle, work->scaleX, work->scaleY, 0);
        DrawSprite(work->x >> 8, y, gCardBacks[work->cardDef->category].gfx, gCardBattleState->tiles[work->cardDef->category], gCardBattleState->palette, affine, attr, work->priority - 1);
        DrawSprite(work->x >> 8, y, gfx, work->tiles, work->palette, affine, attr, work->priority);
        j = work->value;

        if (work->cardDef->category == 3) {
            return;
        }

        if (work->valueModified) {
            DrawSprite(work->x >> 8, y, gCardModifiedValueDigitFrames[j], gCardBattleState->tiles7, gCardBattleState->palette2, affine, attr, work->priority - 2);
        } else if (work->premium) {
            DrawSprite(work->x >> 8, y, gCardPremiumValueDigitFrames[j], gCardBattleState->tiles6, gCardBattleState->palette2, affine, attr, work->priority - 2);
        } else {
            DrawSprite(work->x >> 8, y, gCardValueDigitFrames[j], gCardBattleState->tiles5, gCardBattleState->palette, affine, attr, work->priority - 2);
        }

        if (work->premium) {
            DrawSprite(work->x >> 8, y, gCardBattleState->gfx, gCardBattleState->premiumTiles, gCardBattleState->palette, affine, attr, work->priority - 3);
        }

        return;
    }

    affine = AllocObjAffine(0, work->scaleX, work->scaleY, 0);
    DrawSprite(work->x >> 8, y, work->cardDef->gfx2, work->tiles, work->palette, affine, attr, work->priority);
    k = work->value;

    if (work->cardDef->category == 3) {
        return;
    }

    if (work->valueModified) {
        DrawSprite((work->x >> 8) - 3, y - 4, gCardValueDigitFrames[k], gCardBattleState->tiles7, gCardBattleState->palette2, affine, attr, work->priority - 10);

        if (work->premium) {
            DrawSprite(work->x >> 8, y, gCardBattleState->gfx2, gCardBattleState->premiumTiles2, gCardBattleState->palette, affine, attr, work->priority - 11);
        }
    } else if (work->premium) {
        DrawSprite((work->x >> 8) - 3, y - 4, gCardValueDigitFrames[k], gCardBattleState->tiles6, gCardBattleState->palette2, affine, attr, work->priority - 10);
        DrawSprite(work->x >> 8, y, gCardBattleState->gfx2, gCardBattleState->premiumTiles2, gCardBattleState->palette, affine, attr, work->priority - 11);
    } else {
        DrawSprite((work->x >> 8) - 3, y - 4, gCardValueDigitFrames[k], gCardBattleState->tiles5, gCardBattleState->palette, affine, attr, work->priority - 10);
    }
}

void card_not_have_2(CardDisplayWork* work) {
    void* gfx;
    u16 y;

    gfx = gCardBacks[work->args.listIndex].gfx2;

    if (IsMessageWindowOpen() == 1) {
        y = work->y >> 8;
    } else {
        y = (work->y >> 8) + (gSineTable[work->bobAngle] >> 8);
    }

    if (work->flags & CARD_DISP_FLAG_GFX_LOADED) {
        DrawSprite(work->x >> 8, y, gfx, work->tiles2, gCardBattleState->palette, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, work->priority - 1);
    }
}

void SoraCardDestroy(CardDisplayWork* work) {
    ReleaseCardDisplayGfx(work);
}

void SyncCardDisplayGfx(CardDisplayWork* work) {
    if (work->command != CARD_DISP_COMMAND_STOCK) {
        if (IsCardDisplayOffScreen(work)) {
            if (work->flags & CARD_DISP_FLAG_GFX_LOADED) {
                ReleaseCardDisplayGfx(work);
                work->flags &= ~CARD_DISP_FLAG_GFX_LOADED;
            }
        } else {
            if (!(work->flags & CARD_DISP_FLAG_GFX_LOADED)) {
                LoadCardDisplayGfx(work);
                work->flags |= CARD_DISP_FLAG_GFX_LOADED;
            }
        }
    }
}

void LoadCardDisplayGfx(CardDisplayWork* work) {
    const CardDef* def;
    void* tiles;
    void* pal;
    u32 noCard;

    noCard = work->flags & CARD_DISP_FLAG_NO_CARD;

    if (noCard != 0) {
        work->tiles = NULL;
        work->palette = NULL;
        work->palette2 = NULL;
        work->tiles2 = LoadObjTiles(gCardBacks[work->args.listIndex].tiles2, 640);
    } else {
        def = work->cardDef;
        tiles = def->tiles;
        pal = def->palette;
        work->tiles = LoadObjTiles(tiles, 512);
        work->palette = LoadObjPalette(pal, 32);
        work->tiles2 = NULL;
    }
}

void ReleaseCardDisplayGfx(CardDisplayWork* work) {
    if (work->tiles != NULL) {
        ReleaseObjTiles(work->tiles);
    }

    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
    }

    if (work->tiles2 != NULL) {
        ReleaseObjTiles(work->tiles2);
    }

    if (work->tiles3 != NULL) {
        ReleaseObjTiles(work->tiles3);
    }

    if (work->tiles4 != NULL) {
        ReleaseObjTiles(work->tiles4);
    }

    work->tiles = NULL;
    work->palette = NULL;
    work->palette2 = NULL;
    work->tiles2 = NULL;
    work->tiles3 = NULL;
    work->tiles4 = NULL;
}

u8 SoraCardWaitPlayEnd(CardDisplayWork* work, void* task) {
    if (gBtlWork->flags & BTL_FLAG_CARD_PLAY_ENDED) {
        work->timer = 8;
        work->spinSpeed = 8;
        gCardBattleState->activeCardCount = 0;
        gCardBattleState->activeValue = 0;
        gBtlWork->flags &= ~BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
        gBtlWork->flags &= ~BTL_FLAG_PLAYER_CARD_BUSY;

        if (work->cardDef->category == 0) {
            TickSoraHcEffectOnAttackEnd();
        }

        SetTaskUpdate(task, (TaskUpdateFunc)SoraCardShrinkAway);
    } else if (work->flags & CARD_DISP_FLAG_BROKEN) {
        work->priority -= 4;
        work->ringRadius = 0x500;
        work->timer = 0x100;
        work->ringAngle = -16;
        work->spinSpeed = 0xFF;
        SetTaskUpdate(task, (TaskUpdateFunc)SoraCardBreakFall);
    }

    return 1;
}

u8 SoraCardMoveToPlay(CardDisplayWork* work, void* task) {
    ApproachValue(&work->x, 0x7800, work->timer);
    ApproachValue(&work->y, 0x8400, work->timer);

    if ((s16)work->timer > 0) {
        work->timer--;
    } else {
        work->timer |= 0xFFFF;
    }

    if (gBtlWork->flags & BTL_FLAG_CARD_ACTIVE) {
        if (work->flags & CARD_DISP_FLAG_IN_PLAY) {
            if ((s16)work->timer == 0) {
                SetTaskUpdate(task, (TaskUpdateFunc)SoraCardWaitPlayEnd);
            }
        } else if ((s16)work->timer <= 2) {
            work->priority -= 4;
            work->ringRadius = 0x500;
            work->timer = 0x100;
            work->ringAngle = -16;
            work->spinSpeed = 0xFF;
            work->flags |= CARD_DISP_FLAG_IN_PLAY;
            SetTaskUpdate(task, (TaskUpdateFunc)SoraCardFlyOff);

            if (work->cardDef->flags & CARD_DEF_FLAG_ITEM) {
                work->args.slot->unk_06 = 0;
            }

            m4aSongNumStart(SONG_SYS_DROW);
        }
    } else if ((s16)work->timer <= 2) {
        work->priority -= 4;
        work->ringRadius = 0x500;
        work->timer = 0x100;
        work->ringAngle = -16;
        work->spinSpeed = 0xFF;
        SetTaskUpdate(task, (TaskUpdateFunc)SoraCardFlyOff);
    }

    return 1;
}

u8 SoraStockWaitPlayEnd(CardDisplayWork* work, void* task) {
    ApproachValue(&work->ringCenterX, gPlayedCardCenter[0], work->timer);
    ApproachValue(&work->ringCenterY, gPlayedCardCenter[1], work->timer);
    ApproachValue(&work->ringRadius, work->ringRadiusTarget, work->timer);
    ApproachValue(&work->scaleX, 0x100, work->timer);
    ApproachValue(&work->scaleY, 0x100, work->timer);

    if ((s16)work->timer > 0) {
        work->timer--;
    } else {
        work->timer = 0;
    }

    UpdateSoraPlayedCardPosition(work);

    switch (work->stockIndex) {
    case 0:
        work->priority = 50;
        break;
    case 1:
        work->priority = 40;
        break;
    case 2:
        work->priority = 60;
        break;
    }

    if (work->flags & CARD_DISP_FLAG_BROKEN) {
        work->priority -= 4;
        work->ringRadius = 0x500;
        work->timer = 0x100;
        work->ringAngle = -16;
        work->spinSpeed = 0xFF;
        gCardBattleState->soraStockActive = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)SoraCardBreakFall);
    }

    if (gBtlWork->flags & BTL_FLAG_CARD_PLAY_ENDED) {
        work->timer = 8;
        work->spinSpeed = 8;
        gCardBattleState->activeCardCount--;
        gCardBattleState->activeValue = 0;

        if (gCardBattleState->activeCardCount == 0) {
            gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
            gBtlWork->flags &= ~BTL_FLAG_CARD_ACTIVE;
            TickSoraHcEffectOnPlayEnd();
        }

        gCardBattleState->soraStockActive = 0;
        gBtlWork->flags &= ~BTL_FLAG_PLAYER_CARD_BUSY;
        SetTaskUpdate(task, (TaskUpdateFunc)SoraCardShrinkAway);
    }

    return 1;
}

u8 SoraStockHold(CardDisplayWork* work, void* task) {
    u8 (*fn)(CardDisplayWork*, void*);

    SyncCardDisplayGfx(work);

    if (!(work->flags & CARD_DISP_FLAG_STOCK_NAMED)) {
        fn = SoraStockMoveToSlot;
        SetTaskUpdate(task, (TaskUpdateFunc)fn);
        return fn(work, task);
    }

    if (work->flags & 0x40000000) {
        SetTaskUpdate(task, (TaskUpdateFunc)SoraStockVanish);
        return 1;
    }

    if (work->command == CARD_DISP_COMMAND_PLAY) {
        if (work->flags & CARD_DISP_FLAG_UNOPPOSED) {
            work->timer = 15;
            work->ringRadiusTarget = 0x800;
            work->ringRadius = 0;
            work->ringAngleTarget = gPlayedCardAngles[work->stockIndex] * 2;
            work->ringAngle = 0;
            work->ringCenterX = work->x;
            work->ringCenterY = work->y;
            fn = SoraStockWaitPlayEnd;
        } else {
            work->timer = 15;
            work->ringRadiusTarget = 0x800;
            work->ringRadius = 0;
            work->ringAngleTarget = gPlayedCardAngles[work->stockIndex] * 2;
            work->ringAngle = 0;
            work->ringCenterX = work->x;
            work->ringCenterY = work->y;
            work->priority += work->stockIndex * 3;
            fn = SoraStockMoveToPlay;
        }

        SetTaskUpdate(task, (TaskUpdateFunc)fn);
        work->flags &= ~CARD_DISP_FLAG_STOCKED;
        RefreshSoraCardDisplayGfx(work);
        return fn(work, task);
    }

    if ((s16)work->timer > 0) {
        work->timer--;
        return 1;
    }

    if (work->flags & CARD_DISP_FLAG_OPEN) {
        switch (work->phase) {
        case CARD_STOCK_PHASE_RISE:
            work->y -= 0x80;

            if (work->y <= gSoraCardLayout[3 - work->stockIndex][1] - 0x200) {
                work->y = gSoraCardLayout[3 - work->stockIndex][1] - 0x200;
                work->phase = CARD_STOCK_PHASE_DROP;
            }

            break;
        case CARD_STOCK_PHASE_DROP:
            work->y += 0x200;

            if (work->y >= gSoraCardLayout[3 - work->stockIndex][1]) {
                work->y = gSoraCardLayout[3 - work->stockIndex][1];
                work->phase = CARD_STOCK_PHASE_RISE;
                work->timer = 16;
            }

            break;
        }
    } else {
        ApproachValue(&work->x, gSoraCardLayout[4][0], work->timer);
        ApproachValue(&work->y, gSoraCardLayout[4][1], work->timer);
    }

    work->bobAngle += 4;
    return 1;
}

u8 SoraStockMoveToSlot(CardDisplayWork* work, void* task) {
    u8 (*fn)(CardDisplayWork*, void*);
    u16 timer;

    if (gBtlWork->paused == 1) {
        return 1;
    }

    SyncCardDisplayGfx(work);

    if (work->flags & CARD_DISP_FLAG_OPEN) {
        ApproachValue(&work->x, gSoraCardLayout[3 - work->stockIndex][0], work->timer);
        ApproachValue(&work->scaleY, 179, work->timer);
        ApproachValue(&work->y, gSoraCardLayout[3 - work->stockIndex][1], work->timer);
        ApproachValue(&work->scaleX, 179, work->timer);
    } else {
        ApproachValue(&work->x, gSoraCardLayout[4][0], work->timer);
        ApproachValue(&work->y, gSoraCardLayout[4][1], work->timer);
    }

    timer = work->timer;

    if ((s16)timer > 0) {
        work->timer = timer - 1;
        work->flags &= ~CARD_DISP_FLAG_SETTLED;
    } else {
        work->timer = 0;
        work->scaleX = 0x100;
        work->scaleY = 0x100;
        work->flags |= CARD_DISP_FLAG_SETTLED;

        if (work->flags & CARD_DISP_FLAG_STOCK_NAMED) {
            work->timer = work->stockIndex * 8;
            fn = SoraStockHold;
            SetTaskUpdate(task, (TaskUpdateFunc)fn);
            return fn(work, task);
        }
    }

    if (work->flags & 0x40000000) {
        SetTaskUpdate(task, (TaskUpdateFunc)SoraStockVanish);
        return 1;
    }

    if (work->command == CARD_DISP_COMMAND_PLAY) {
        if (work->flags & CARD_DISP_FLAG_UNOPPOSED) {
            work->timer = 15;
            work->ringRadiusTarget = 0x800;
            work->ringRadius = 0;
            work->ringAngleTarget = gPlayedCardAngles[work->stockIndex] * 2;
            work->ringAngle = 0;
            work->ringCenterX = work->x;
            work->ringCenterY = work->y;
            fn = SoraStockWaitPlayEnd;
        } else {
            work->timer = 15;
            work->ringRadiusTarget = 0x800;
            work->ringRadius = 0;
            work->ringAngleTarget = gPlayedCardAngles[work->stockIndex] * 2;
            work->ringAngle = 0;
            work->ringCenterX = work->x;
            work->ringCenterY = work->y;
            fn = SoraStockMoveToPlay;
        }

        SetTaskUpdate(task, (TaskUpdateFunc)fn);
        work->flags &= ~CARD_DISP_FLAG_STOCKED;
        RefreshSoraCardDisplayGfx(work);
        return fn(work, task);
    }

    work->bobAngle += 4;
    return 1;
}

u8 SoraCardDeal(CardDisplayWork* work, void* task) {
    if (!(work->flags & CARD_DISP_FLAG_OPEN)) {
        if (work->flags & CARD_DISP_FLAG_RELOAD_CARD) {
            SetTaskUpdate(task, (TaskUpdateFunc)SoraReloadCardClosed);
            return SoraReloadCardClosed(work, task);
        } else {
            SetTaskUpdate(task, (TaskUpdateFunc)SoraCardClosed);
            return SoraCardClosed(work, task);
        }
    }

    UpdateSoraCardRingPosition(work);
    work->timer--;

    if (work->timer == 0) {
        work->flags &= ~CARD_DISP_FLAG_DEALING;

        if (work->flags & CARD_DISP_FLAG_RELOAD_CARD) {
            gCardBattleState->soraReloadCharging = 0;
            SetTaskUpdate(task, (TaskUpdateFunc)card_reload_1);
        } else {
            SetTaskUpdate(task, (TaskUpdateFunc)SoraCardUpdate);
        }
    }

    return 1;
}

u8 SoraCardClosed(CardDisplayWork* work, void* task) {
    u8 (*fn)(CardDisplayWork*, void*);

    if (work->command == CARD_DISP_COMMAND_REMOVE) {
        return 0;
    }

    work->ringRadius += (0 - work->ringRadius) >> 1;
    work->x += (gSoraCardLayout[4][0] - work->x) >> 1;
    work->y += (gSoraCardLayout[4][1] - work->y) >> 1;

    if (work->flags & CARD_DISP_FLAG_OPEN) {
        fn = SoraCardUpdate;
        SetTaskUpdate(task, (TaskUpdateFunc)fn);
        return fn(work, task);
    }

    return 1;
}

void UpdateSoraCardRingPosition(CardDisplayWork* work) {
    s32 angle;

    ApproachValue(&work->swingAngle, work->swingAngleTarget, work->swingSteps);

    if (work->swingSteps != 0) {
        work->swingSteps--;
    }

    work->ringRadius += (work->ringRadiusTarget - work->ringRadius) >> 1;

    if ((s16)work->timer > 0) {
        ApproachValue(&work->ringAngle, work->ringAngleTarget, work->timer);
        work->timer--;
        work->flags &= ~CARD_DISP_FLAG_SETTLED;
        gCardBattleState->soraReloadCharging = 0;
    } else {
        work->flags |= CARD_DISP_FLAG_SETTLED;
    }

    work->ringCenterX = SIN(work->swingAngle >> 8) * 80 + gSoraCardLayout[0][0];
    work->ringCenterY = -COS(work->swingAngle >> 8) * 80 + gSoraCardLayout[0][1];
    angle = ((work->ringAngle >> 8) + 0x20) & 0xFF;
    work->x = gSineTable[angle] * (work->ringRadius >> 8) + work->ringCenterX;
    work->y = -gSineTable[angle + 0x40] * (work->ringRadius >> 8) + work->ringCenterY;
}

void UpdateCardDisplayFlip(CardDisplayWork* work) {
    if (work->flags & CARD_DISP_FLAG_VISIBLE) {
        if (work->flags & CARD_DISP_FLAG_SELECTED) {
            if (work->flags & CARD_DISP_FLAG_FACE_DOWN) {
                if (work->scaleX > 2) {
                    work->scaleX -= 64;

                    if (work->scaleX <= 2) {
                        work->scaleX = 2;
                    }
                } else {
                    work->scaleX = 2;
                    work->flags &= ~CARD_DISP_FLAG_FACE_DOWN;

                    if (!(work->flags & CARD_DISP_FLAG_GFX_LOADED)) {
                        LoadCardDisplayGfx(work);
                        work->flags |= CARD_DISP_FLAG_GFX_LOADED;
                    }
                }
            } else {
                if (work->scaleX <= 255) {
                    work->scaleX += 64;

                    if (work->scaleX > 256) {
                        work->scaleX = 256;
                    }
                } else {
                    work->scaleX = 256;
                }
            }
        } else {
            if (!(work->flags & CARD_DISP_FLAG_FACE_DOWN)) {
                if (work->scaleX > 2) {
                    work->scaleX -= 64;

                    if (work->scaleX <= 2) {
                        work->scaleX = 2;
                    }
                } else {
                    work->scaleX = 2;
                    work->flags |= CARD_DISP_FLAG_FACE_DOWN;

                    if (work->flags & CARD_DISP_FLAG_GFX_LOADED) {
                        ReleaseCardDisplayGfx(work);
                        work->flags &= ~CARD_DISP_FLAG_GFX_LOADED;
                    }
                }
            } else {
                if (work->scaleX <= 255) {
                    work->scaleX += 64;

                    if (work->scaleX > 256) {
                        work->scaleX = 256;
                    }
                } else {
                    work->scaleX = 256;
                }
            }
        }
    }
}

u8 SoraCardShrinkAway(CardDisplayWork* work) {
    ApproachValue(&work->y, 0x8200, work->timer);

    if ((s16)work->timer > 0) {
        work->timer--;
    } else {
        work->timer = 0;
    }

    if ((s16)work->timer == 0) {
        work->timer = 0;
        work->angle += work->spinSpeed;
        work->spinSpeed++;

        if (work->scaleX <= 25) {
            return 0;
        }

        work->scaleX -= 25;
        work->scaleY -= 25;
    }

    return 1;
}

u8 IsCardDisplayOffScreen(CardDisplayWork* work) {
    if (work->x > 0x10000) {
        return 1;
    }

    if (work->x < -0x1000) {
        return 1;
    }

    if (work->y > 0xC000) {
        return 1;
    }

    if (work->y < -0x2000) {
        return 1;
    }

    return 0;
}

u8 SoraCardFlyOff(CardDisplayWork* work) {
    work->command = CARD_DISP_COMMAND_NONE;
    work->y -= work->ringRadius;
    work->ringRadius -= (s16)work->timer;
    work->timer++;
    work->x -= COS(work->ringAngle);
    work->angle += work->spinSpeed;
    work->scaleX -= 5;
    work->scaleY -= 5;

    if (IsCardDisplayOffScreen(work)) {
        work->flags &= ~CARD_DISP_FLAG_VISIBLE;
        ReleaseCardDisplayGfx(work);
        gBtlWork->flags &= ~BTL_FLAG_PLAYER_CARD_BUSY;
        work->flags &= ~CARD_DISP_FLAG_GFX_LOADED;
        return 0;
    }

    return 1;
}

u8 SoraStockStartUnopposedPlay(CardDisplayWork* work, void* task) {
    s32 z;

    work->timer = 15;
    z = 0;
    work->ringRadiusTarget = 0x800;
    work->ringRadius = z;
    work->ringAngleTarget = gPlayedCardAngles[work->stockIndex] * 2;
    work->ringAngle = z;
    work->ringCenterX = work->x;
    work->ringCenterY = work->y;
    SetTaskUpdate(task, (TaskUpdateFunc)SoraStockWaitPlayEnd);
    return 1;
}

u8 SoraStockMoveToPlay(CardDisplayWork* work, void* task) {
    ApproachValue(&work->ringCenterX, gPlayedCardCenter[0], work->timer);
    ApproachValue(&work->ringCenterY, gPlayedCardCenter[1], work->timer);
    ApproachValue(&work->ringRadius, work->ringRadiusTarget, work->timer);
    ApproachValue(&work->scaleX, 0x100, work->timer);
    ApproachValue(&work->scaleY, 0x100, work->timer);

    if ((s16)work->timer > 0) {
        work->timer--;
    } else {
        work->timer = 0;
    }

    UpdateSoraPlayedCardPosition(work);

    if (gBtlWork->flags & BTL_FLAG_CARD_ACTIVE) {
        if (work->flags & CARD_DISP_FLAG_IN_PLAY) {
            if ((s16)work->timer == 0) {
                SetTaskUpdate(task, (TaskUpdateFunc)SoraStockWaitPlayEnd);
            }
        } else if ((s16)work->timer <= 2) {
            work->priority -= 4;
            work->ringRadius = 0x500;
            work->timer = 0x100;
            work->ringAngle = -16;
            work->spinSpeed = 0xFF;
            gCardBattleState->unk_0C0 = 0;
            gCardBattleState->soraStockActive = 0;
            SetTaskUpdate(task, (TaskUpdateFunc)SoraCardFlyOff);
        }
    } else if ((s16)work->timer <= 2) {
        work->priority -= 4;
        work->ringRadius = 0x500;
        work->timer = 0x100;
        work->ringAngle = -16;
        work->spinSpeed = 0xFF;
        gCardBattleState->soraStockActive = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)SoraCardFlyOff);
    }

    return 1;
}

void UpdateSoraPlayedCardPosition(CardDisplayWork* work) {
    s32 wrappedAngle;

    if (work->ringAngleTarget - work->ringAngle > 0x7F00) {
        work->ringAngle += 0x10000;
    }

    if (work->ringAngleTarget - work->ringAngle <= 255) {
        wrappedAngle = work->ringAngle - 0x10000;

        if (work->ringAngleTarget - wrappedAngle < work->ringAngle - work->ringAngleTarget) {
            work->ringAngle = wrappedAngle;
        }
    }

    work->ringAngle += (work->ringAngleTarget - work->ringAngle) >> 2;
    work->x = SIN(work->ringAngle >> 8) * (work->ringRadius >> 8) + work->ringCenterX;
    work->y = -COS(work->ringAngle >> 8) * (work->ringRadius >> 8) + work->ringCenterY;
}

u8 DispatchSoraCardCommand(CardDisplayWork* work, void* task) {
    switch (work->command) {
    case CARD_DISP_COMMAND_PLAY:
        if (!(work->flags & CARD_DISP_FLAG_GFX_LOADED)) {
            LoadCardDisplayGfx(work);
            work->flags |= CARD_DISP_FLAG_GFX_LOADED;
        }

        UpdateSoraCardRingPosition(work);
        work->timer = 10;
        work->priority -= 4;
        ListPoolRemove(&work->node, work->args.pool);
        SetTaskUpdate(task, (TaskUpdateFunc)SoraCardMoveToPlay);
        return 1;
    case CARD_DISP_COMMAND_STOCK:
        if (!(work->flags & CARD_DISP_FLAG_GFX_LOADED)) {
            LoadCardDisplayGfx(work);
            work->flags |= CARD_DISP_FLAG_GFX_LOADED;
        }

        work->timer = 8;
        work->priority -= 4;
        LoadSoraCardDisplayGfx2(work);
        work->flags |= CARD_DISP_FLAG_STOCKED;
        work->flags |= CARD_DISP_FLAG_GFX_LOADED;
        ListPoolRemove(&work->node, work->args.pool);
        SetTaskUpdate(task, (TaskUpdateFunc)SoraStockMoveToSlot);
        return 1;
    case CARD_DISP_COMMAND_FLY_OFF:
        work->priority -= 4;
        work->ringRadius = 0x500;
        work->timer = 0x100;
        work->ringAngle = -16;
        work->spinSpeed = 0xFF;
        SetTaskUpdate(task, (TaskUpdateFunc)SoraCardFlyOff);
        break;
    case CARD_DISP_COMMAND_REMOVE:
        work->ringRadius = 0x500;
        work->timer = 0x100;
        ListPoolRemove(&work->node, work->args.pool);
        return 0;
    case CARD_DISP_COMMAND_HEARTLESS:
        work->timer = 10;
        work->priority -= 4;
        ListPoolRemove(&work->node, work->args.pool);
        SetTaskUpdate(task, (TaskUpdateFunc)SoraHeartlessCardShow);
        return 1;
    case CARD_DISP_COMMAND_GIMMICK:
        work->timer = 10;
        work->priority -= 4;
        ListPoolRemove(&work->node, work->args.pool);
        SetTaskUpdate(task, (TaskUpdateFunc)SoraGimmickCardLaunch);
        return 1;
    }

    UpdateSoraCardValue(work);
    return 1;
}

void LookupSoraCardDef(CardDisplayArgs* args, const CardDef** out, u8 index) {
    u32* pickedFriendCardId;

    if (args->slot != NULL) {
        if (args->slot->cardId != CARD_ID_NONE) {
            if (args->slot->cardId != CARD_ID_RELOAD) {
                *out = &gCardDefs[args->slot->cardId & CARD_ID_MASK];
            } else {
                *out = NULL;
            }
        } else {
            *out = NULL;
        }
    } else {
        pickedFriendCardId = &gCardBattleState->pickedFriendCardId;
        *out = &gCardDefs[*pickedFriendCardId & CARD_ID_MASK];
        *pickedFriendCardId = 0x3B6;
    }
}

void LinkSoraCardDisplay(CardDisplayWork* work) {
    ListNodeInit(&work->node, work->args.pool, work);
    ListPoolAppend(&work->node, work->args.pool);
}

u8 SoraCardBreakFall(CardDisplayWork* work, void* task) {
    work->command = CARD_DISP_COMMAND_NONE;
    work->y -= work->ringRadius;
    work->ringRadius -= (s16)work->timer >> 1;
    work->timer++;
    work->x -= 0x200;
    work->angle += 16;

    if (!(work->flags & CARD_DISP_FLAG_SPIN_MIRRORED)) {
        work->scaleX -= 10;

        if (work->scaleX >= -2 && work->scaleX <= 2) {
            work->scaleX = -10;
        }

        if (work->scaleX <= -0x100) {
            work->scaleX = -0x100;
            work->flags |= CARD_DISP_FLAG_SPIN_MIRRORED;
        }
    } else {
        work->scaleX -= 10;

        if (work->scaleX >= -2 && work->scaleX <= 2) {
            work->scaleX = 10;
        }

        if (work->scaleX >= 0x100) {
            work->scaleX = 0x100;
            work->flags &= ~CARD_DISP_FLAG_SPIN_MIRRORED;
        }
    }

    if (IsCardDisplayOffScreen(work)) {
        work->flags &= ~CARD_DISP_FLAG_VISIBLE;
        ReleaseCardDisplayGfx(work);
        work->flags &= ~CARD_DISP_FLAG_GFX_LOADED;
        gBtlWork->flags &= ~BTL_FLAG_PLAYER_CARD_BUSY;
        return 0;
    }

    return 1;
}

void LoadSoraCardDisplayGfx2(CardDisplayWork* work) {
    void* tiles;
    void* pal;

    ReleaseCardDisplayGfx(work);
    tiles = work->cardDef->tiles2;
    pal = work->cardDef->palette2;
    work->tiles = LoadObjTiles(tiles, 256);
    work->palette = LoadObjPalette(pal, 32);
}

void RefreshSoraCardDisplayGfx(CardDisplayWork* work) {
    if (work->tiles != NULL) {
        ReleaseObjTiles(work->tiles);
    }

    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
    }

    work->tiles = NULL;
    work->palette = NULL;
    LoadCardDisplayGfx(work);
}

u8 SoraHeartlessCardShow(CardDisplayWork* work) {
    u8 arg;

    work->command = CARD_DISP_COMMAND_NONE;
    ApproachValue(&work->x, 0x1800, work->timer);
    ApproachValue(&work->scaleY, 0x99, work->timer);
    ApproachValue(&work->y, 0x6400, work->timer);
    ApproachValue(&work->scaleX, 0x99, work->timer);

    if ((s16)work->timer > 0) {
        work->timer--;
        return 1;
    }

    arg = 1;
    gBtlWork->hcEffectCount = gHcEffectDefs[gBtlWork->hcEffect].count;
    TaskCreate(&gCardBattleState->tasks, &gTaskDescHCEffectName, &arg);
    return 0;
}

u8 SoraGimmickCardLaunch(CardDisplayWork* work, void* task) {
    s16 sx;
    s16 sy;
    s32 dx;
    s32 dy;
    s32 x;
    s32 y;

    ApproachValue(&work->x, 0x1800, work->timer);
    ApproachValue(&work->y, 0x6400, work->timer);

    if ((s16)work->timer > 0) {
        work->timer--;
    } else {
        WorldToScreen(&sx, &sy, gBtlWork->gimmickX, gBtlWork->gimmickY, gBtlWork->gimmickZ);
        x = sx;
        y = sy;
        dx = (x << 8) - work->x;
        dy = (y << 8) - work->y;
        work->ringRadius = NormalizeVector2D8(&dx, &dy);
        work->ringCenterX = -dx;
        work->ringCenterY = -dy;
        work->ringRadiusTarget = 0x300;
        work->angle = 0;
        work->ringAngleTarget = 25;
        gBtlWork->hitStop = 10000;
        FadeStartOut(FADE_MODE_WHITE_BLEND, 1);
        m4aSongNumStart(SONG_BTL_GMIC_OK);
        FadeLock();
        gBtlWork->flags |= BTL_FLAG_BGFX_PAUSED;
        SetTaskUpdate(task, (TaskUpdateFunc)SoraGimmickCardFly);
    }

    return 1;
}

u8 SoraGimmickCardFly(CardDisplayWork* work, void* task) {
    s16 sx;
    s16 sy;
    s32 dx;
    s32 dy;
    s32 x;
    s32 y;

    WorldToScreen(&sx, &sy, gBtlWork->gimmickX, gBtlWork->gimmickY, gBtlWork->gimmickZ);
    x = sx;
    y = sy;

    if (work->ringRadiusTarget < 0) {
        dx = (x << 8) - work->x;
        dy = (y << 8) - work->y;
        NormalizeVector2D8(&dx, &dy);
        work->ringCenterX = -dx;
        work->ringCenterY = -dy;
    }

    work->angle += 24;

    if (work->scaleX > 24) {
        work->scaleX -= 12;
        work->scaleY -= 12;
    } else {
        work->scaleX = 25;
        work->scaleY = 25;
    }

    work->x += (work->ringCenterX * work->ringRadiusTarget) >> 8;
    work->y += (work->ringCenterY * work->ringRadiusTarget) >> 8;
    work->ringRadius = VectorLength2D((x << 8) - work->x, (y << 8) - work->y);
    work->ringRadiusTarget -= work->ringAngleTarget;
    work->ringAngleTarget += 2;

    if (work->ringRadius <= 0x800) {
        gBtlWork->freezeTimer = 15;
        gBtlWork->hitStop = 15;
        m4aSongNumStart(SONG_SYS_CLICKI04);
        SetTaskUpdate(task, (TaskUpdateFunc)SoraGimmickCardHit);
    }

    return 1;
}

u8 SoraGimmickCardHit(CardDisplayWork* work) {
    if (gBtlWork->hitStop == 0) {
        FadeStartIn(FADE_MODE_WHITE_BLEND, 8);
        FadeLock();
        gBtlWork->flags &= ~BTL_FLAG_BGFX_PAUSED;

        if (work->cardDef->move == 140) {
            SetGimmickFlag(0);
        }

        gBtlWork->flags &= ~BTL_FLAG_GIMMICK_CARD_ACTIVE;
        return 0;
    }

    return 1;
}

u8 SoraStockVanish(CardDisplayWork* work) {
    s32 result;

    if (work->scaleX <= 25) {
        work->args.slot->stocked = result = 0;
        return result;
    }

    work->scaleX -= 12;
    work->scaleY += 12;

    if (work->scaleY > 0x1FF) {
        work->scaleY = 0x200;
    }

    return 1;
}

void card_reload_0(CardDisplayWork* work, CardDisplayArgs* args) {
    CpuFill32(0, work, sizeof(CardDisplayWork));
    work->tiles = NULL;
    work->tiles2 = NULL;
    work->tiles3 = NULL;
    work->tiles4 = NULL;
    work->tiles5 = NULL;
    work->palette2 = NULL;
    work->palette = NULL;
    work->children = NULL;
    work->reloadGauge = EwramAlloc(sizeof(ReloadGauge));
    CpuFill32(0, work->reloadGauge, sizeof(ReloadGauge));
    work->args = *args;
    work->reloadGauge->chargeTick = 0;
    work->flags = (CARD_DISP_FLAG_OPEN | CARD_DISP_FLAG_RELOAD_CARD | CARD_DISP_FLAG_RELOAD_GAUGE);
    work->cardDef = NULL;
    work->scaleX = 0x100;
    work->scaleY = 0x100;
    work->bobAngle = 0;
    work->angle = 0;
    work->stockIndex = 0;
    work->ringAngle = 0;
    work->ringAngleTarget = 0;
    work->swingAngle = 0;
    work->swingAngleTarget = 0;
    work->command = CARD_DISP_COMMAND_NONE;
    work->priority = 60;
    work->timer = 4;
    work->phase = 0;
    work->ringRadius = 0;
    work->ringRadiusTarget = 0x2400;
    work->swingSteps = 0;
    work->ringCenterX = gSoraCardLayout[0][0];
    work->ringCenterY = gSoraCardLayout[0][1];
    work->x = gSoraCardLayout[4][0];
    work->y = gSoraCardLayout[4][1];
    work->flags &= ~CARD_DISP_FLAG_SETTLED;
    gCardBattleState->soraReloadCharging = 0;
    LinkSoraCardDisplay(work);
}

u8 SoraReloadCardClosed(CardDisplayWork* work, void* task) {
    u8 (*fn)(CardDisplayWork*, void*);

    if (work->command == CARD_DISP_COMMAND_REMOVE) {
        return 0;
    }

    work->ringRadius += (0 - work->ringRadius) >> 1;
    work->x += (gSoraCardLayout[4][0] - work->x) >> 1;
    work->y += (gSoraCardLayout[4][1] - work->y) >> 1;

    if (work->flags & CARD_DISP_FLAG_OPEN) {
        fn = card_reload_1;
        SetTaskUpdate(task, (TaskUpdateFunc)fn);
        return fn(work, task);
    }

    return 1;
}

u8 card_reload_1(CardDisplayWork* work, void* task) {
    if (work->flags & CARD_DISP_FLAG_DEALING) {
        work->timer = 8;
        SetTaskUpdate(task, (TaskUpdateFunc)SoraCardDeal);
        return 1;
    }

    if ((s16)work->timer == 0) {
        if (IsCardDisplayOffScreen(work)) {
            ListPoolRemove(&work->node, work->args.pool);
            return 0;
        }

        if (!(work->flags & CARD_DISP_FLAG_GFX_LOADED)) {
            LoadSoraReloadCardGfx(work);
            work->flags |= CARD_DISP_FLAG_GFX_LOADED;
        }
    }

    if (work->flags & CARD_DISP_FLAG_FROZEN) {
        return 1;
    }

    if (!(work->flags & CARD_DISP_FLAG_OPEN)) {
        work->flags &= ~CARD_DISP_FLAG_SETTLED;
        SetTaskUpdate(task, (TaskUpdateFunc)SoraReloadCardClosed);
    }

    UpdateSoraReloadGauge(work);
    UpdateSoraCardRingPosition(work);
    work->bobAngle += 4;
    return DispatchSoraCardCommand(work, task);
}

void InitSoraReloadCounterAnim(ReloadGauge* gauge, void* tiles, u8 listIndex, s8 count) {
    AnimInit(&gauge->anim, gReloadCounterWhiteAnims, gReloadCounterWhiteFrames);

    if (count >= 0) {
        AnimStart(&gauge->anim, count, 0);
    } else {
        AnimStart(&gauge->anim, 0, 0);
    }

    gauge->gfx3 = AnimGetGfx(&gauge->anim);
}

void SetSoraReloadCounterAnim(ReloadGauge* gauge, s32 count) {
    void* gfx;

    if ((u16)count <= 18) {
        AnimStart(&gauge->anim, count, 0);
        gfx = AnimGetGfx(&gauge->anim);
    } else {
        gfx = NULL;
    }

    gauge->gfx3 = gfx;
}

void LoadSoraReloadCardGfx(CardDisplayWork* work) {
    ReloadGauge* gauge;

    gauge = work->reloadGauge;
    work->tiles = AllocObjTiles(0x80, NULL);
    SetObjTileSource(work->tiles, gReloadCounterWhiteTiles);
    InitSoraReloadCounterAnim(work->reloadGauge, work->tiles, work->args.listIndex, gCardBattleState->soraReloadCounter);
    work->palette = NULL;
    work->tiles2 = LoadObjTiles(gReloadCardGreenTiles, 0x280);
    work->palette2 = NULL;
    work->tiles3 = AllocObjTiles(0x200, NULL);
    SetObjTileSource(work->tiles3, gRiCardF0RedTiles);
    work->tiles4 = AllocObjTiles(0x80, NULL);
    SetObjTileSource(work->tiles4, gRiCardF0RedTiles);
    AnimInit(&gauge->anim2, gRiCardF0RedAnims, gRiCardF0RedFrames);
    AnimStart(&gauge->anim2, 1, ANIM_FLAG_LOOP);
    gauge->gfx = gRiCardF0RedFrames[3];
    AnimInit(&gauge->anim3, gRiCardF0RedAnims, gRiCardF0RedFrames);
    AnimStart(&gauge->anim3, gCardBattleState->soraGaugeAnim, ANIM_FLAG_LOOP);
    gauge->gfx2 = gRiCardF0RedFrames[gCardBattleState->soraGaugeFullFrame + 2];
}

void card_reload_2(CardDisplayWork* work) {
    ReloadGauge* gauge;
    s16 y;
    ObjAffine* affine;
    s32 attr;

    if (work->flags & CARD_DISP_FLAG_GFX_LOADED) {
        gauge = work->reloadGauge;

        if (IsMessageWindowOpen() == 1) {
            y = work->y >> 8;
        } else {
            y = (work->y >> 8) + (gSineTable[work->bobAngle] >> 8);
        }

        attr = 0x410;
        DrawSprite(work->x >> 8, y, gCardBacks[3].gfx2, work->tiles2,
                   gCardBattleState->palette, NULL, attr, work->priority);

        if (!(gGameState.flags & GAME_FLAG_RIKU) && gauge->gfx3 != NULL) {
            DrawSprite(work->x >> 8, y, gauge->gfx3, work->tiles,
                       gCardBattleState->palette, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, work->priority - 2);
        }

        if ((s32)gCardBattleState->soraReloadGauge > 0) {
            affine = AllocObjAffine(0, work->scaleX, gCardBattleState->soraReloadGauge, 0);

            if (gauge->gfx != NULL) {
                DrawSprite(work->x >> 8, y + 17, gauge->gfx, work->tiles3,
                           gCardBattleState->palette, affine, SPRITE_PRIORITY(1),
                           work->priority - 1);
            }

            if (gCardBattleState->reloadGaugeFull[0] == 1 && gauge->gfx2 != NULL) {
                DrawSprite(work->x >> 8, y, gauge->gfx2, work->tiles4,
                           gCardBattleState->palette, NULL, SPRITE_PRIORITY(1),
                           work->priority - 1);
            }
        }
    }
}

void card_reload_3(CardDisplayWork* work) {
    ReleaseCardDisplayGfx(work);
    EwramFree(work->reloadGauge);

    if (gBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
        gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
    }
}

void AdvanceSoraReloadGaugeAnim(ReloadGauge* gauge, CardDisplayWork* work) {
    if (gCardBattleState->soraGaugeAnim <= 7) {
        gCardBattleState->soraGaugeAnim++;
    }

    AnimStart(&gauge->anim3, gCardBattleState->soraGaugeAnim, ANIM_FLAG_LOOP | ANIM_FLAG_KEEP_FRAME);
}

void ResetSoraReloadGaugeAnim(ReloadGauge* gauge) {
    gCardBattleState->soraGaugeAnim = 2;
    AnimStart(&gauge->anim3, 2, ANIM_FLAG_LOOP | ANIM_FLAG_KEEP_FRAME);
}

void SetSoraReloadGaugeIdleFrames(ReloadGauge* gauge, CardDisplayWork* work) {
    gauge->gfx = gRiCardF0RedFrames[3];
    gauge->gfx2 = gRiCardF0RedFrames[gCardBattleState->soraGaugeFullFrame + 2];
}

void UpdateSoraReloadGaugeAnims(ReloadGauge* gauge, CardDisplayWork* work) {
    gauge->gfx = AnimUpdate(&gauge->anim2);
    gauge->gfx2 = AnimUpdate(&gauge->anim3);
}

void UpdateSoraReloadGauge(CardDisplayWork* work) {
    ReloadGauge* gauge = work->reloadGauge;
    u8 reloadCharging = 0;

    if ((work->flags & (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) == (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) {
        reloadCharging = gCardBattleState->soraReloadCharging;
        gCardBattleState->soraReloadCharging = 0;
    } else {
        gCardBattleState->soraReloadCharging = 0;
    }

    if ((work->flags & (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) == (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) {
        if (reloadCharging == 1) {
            if ((s8)gauge->chargeTick == 2) {
                if (!(gBtlWork->flags & BTL_FLAG_RELOAD_CHARGING)) {
                    m4aSongNumStart(SONG_SYS_CHAGE);
                    gBtlWork->flags |= BTL_FLAG_RELOAD_CHARGING;
                }

                if (gCardBattleState->reloadGaugeFull[0] == 0) {
                    if (gBtlWork->hcEffect == 43) {
                        gCardBattleState->soraReloadGauge += 12;
                    } else {
                        gCardBattleState->soraReloadGauge += 25;
                    }

                    if ((s32)gCardBattleState->soraReloadGauge > 0x100) {
                        gCardBattleState->soraReloadGauge = 0x100;
                        gCardBattleState->reloadGaugeFull[0] = 1;
                    }
                } else {
                    gCardBattleState->soraGaugeFullFrame += 3;
                    AdvanceSoraReloadGaugeAnim(work->reloadGauge, work);

                    if (gCardBattleState->soraGaugeFullFrame == 22) {
                        gCardBattleState->soraGaugeFullFrame = 4;
                        gCardBattleState->soraReloadGauge = 0;
                        gCardBattleState->reloadGaugeFull[0] = 0;
                        gCardBattleState->soraReloadCounter--;
                        work->phase = reloadCharging;
                        ResetSoraReloadGaugeAnim(work->reloadGauge);
                        m4aSongNumStart(SONG_SYS_CHAGEF1);
                        SetSoraReloadCounterAnim(work->reloadGauge, (s16)gCardBattleState->soraReloadCounter);
                    }
                }

                gauge->chargeTick = 0;
            }

            UpdateSoraReloadGaugeAnims(work->reloadGauge, work);
            gauge->chargeTick++;
        } else {
            SetSoraReloadGaugeIdleFrames(work->reloadGauge, work);
            gauge->chargeTick = 0;
            m4aSongNumStop(SONG_SYS_CHAGE);
            gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
        }
    } else {
        gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
    }

    if ((s16)gCardBattleState->soraReloadCounter < 0) {
        gCardBattleState->soraReloadGauge = 0;
        gCardBattleState->soraGaugeFullFrame = 4;
        gCardBattleState->soraGaugeAnim = 2;
        gCardBattleState->reloadGaugeFull[0] = 0;

        if (!(work->flags & CARD_DISP_FLAG_RELOAD_DONE)) {
            work->flags |= CARD_DISP_FLAG_RELOAD_DONE;
            m4aSongNumStart(SONG_SYS_CHAGEF2);
        }

        if (FadeGetAmount() == 0) {
            FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
        }

        gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
    }
}

void UpdateSoraCardValue(CardDisplayWork* work) {
    // @bug A "not have" display has no cardDef (NULL read).
    if (gBtlWork->hcEffect == 16) {
        if (work->flags & CARD_DISP_FLAG_SELECTED) {
            work->valueModified = 1;
            work->value = GetRandom() % 10;
        } else {
            work->valueModified = 0;
            work->value = work->cardDef->value;
        }
    } else if (gBtlWork->hcEffect == 17) {
        work->valueModified = 1;
        work->value = 0;
    } else if (gBtlWork->hcEffect == 31) {
        work->valueModified = 1;
        work->value = 10 - work->cardDef->value;

        if (work->value == 10) {
            work->value = 0;
        }
    } else {
        work->value = work->cardDef->value;

        switch (gGameState.roomEffect) {
        case 7:
            if (work->cardDef->category == 1) {
                work->value += 2;

                if (work->value > 9) {
                    work->value = 9;
                }

                work->valueModified = 1;
            }

            break;
        case 8:
            if (work->cardDef->category == 2 && (work->cardDef->flags & CARD_DEF_FLAG_ITEM)) {
                work->value += 2;

                if (work->value > 9) {
                    work->value = 9;
                }

                work->valueModified = 1;
            }

            break;
        case 9:
            if (work->cardDef->category == 0) {
                work->value += 2;

                if (work->value > 9) {
                    work->value = 9;
                }

                work->valueModified = 1;
            }

            break;
        default:
            work->valueModified = 0;
            work->value = work->cardDef->value;
            break;
        }
    }
}

void TickSoraHcEffectOnPlayEnd() {
    BtlWork* btl;

    btl = gBtlWork;

    switch ((u32)btl->hcEffect) {
    case 15:
    case 28:
    case 47:
        btl->hcEffectCount--;
        break;
    }
}

void TickSoraHcEffectOnAttackEnd() {
    if (gBtlWork->hcEffect == 2) {
        gBtlWork->hcEffectCount--;
    }
}

TaskDesc gTaskDescCardSora = {
    "card",
    (TaskInitFunc)SoraCardInit,
    (TaskUpdateFunc)SoraCardUpdate,
    (TaskDrawFunc)card_2,
    (TaskDestroyFunc)SoraCardDestroy,
    sizeof(CardDisplayWork),
};

TaskDesc gTaskDescCardNotHave = {
    "card_not_have",
    (TaskInitFunc)SoraCardInit,
    (TaskUpdateFunc)SoraCardUpdate,
    (TaskDrawFunc)card_not_have_2,
    (TaskDestroyFunc)SoraCardDestroy,
    sizeof(CardDisplayWork),
};

TaskDesc gTaskDescCardReload = {
    "card_reload",
    (TaskInitFunc)card_reload_0,
    (TaskUpdateFunc)card_reload_1,
    (TaskDrawFunc)card_reload_2,
    (TaskDestroyFunc)card_reload_3,
    sizeof(CardDisplayWork),
};
