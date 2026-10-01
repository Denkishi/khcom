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
#include "game.h"
#include "obj_api.h"
#include "gba/syscall.h"
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
#include "mode_test_api.h"
#include "obj.h"
#include "taskpool.h"
#include "types.h"
#include "gba/macro.h"
#include <stddef.h>

s32 UpdateSoraReloadDeal(CardBattleWork* w, Task* task);

CardDisplayWork* gSoraSelectedCard;
u32 gSoraCardRequest;
u32 gSoraCardReloadRequest;
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

const UnkStruct_080ABA80 gUnk_09033FD0 = {
    { -1, -1, -1, -1, -1, -1 },
};

void func_08076284() {
    gSoraCardReloadRequest = 14;
}

void func_08076290() {
    gSoraCardReloadRequest = 15;
}

void func_0807629C() {
    gSoraCardReloadRequest = 16;
}

u8 func_080762A8() {
    return gCardBattleState->soraListIndex;
}

void RequestSoraPotion() {
    gSoraCardReloadRequest = 17;
}

void RequestSoraHiPotion() {
    gSoraCardReloadRequest = 18;
}

void RequestSoraMegaPotion() {
    gSoraCardReloadRequest = 19;
}

void RequestSoraEther() {
    gSoraCardReloadRequest = 21;
}

void RequestSoraMegaEther() {
    gSoraCardReloadRequest = 22;
}

void RequestSoraElixir() {
    gSoraCardReloadRequest = 23;
}

void RequestSoraMegalixir() {
    gSoraCardReloadRequest = 24;
}

void func_0807630C() {
    gSoraCardReloadRequest = 20;
}

void RequestSoraNextCard() {
    gSoraCardRequest = 1;
}

void RequestSoraPrevCard() {
    gSoraCardRequest = 2;
}

void RequestSoraCardUse() {
    gSoraCardRequest = 3;
}

void RequestSoraCardStock() {
    gSoraCardRequest = 4;
}

void RequestSoraStockUse() {
    gSoraCardRequest = 5;
}

void func_08076354() {
    gSoraCardRequest = 8;
}

void RequestOpenCards() {
    gSoraCardRequest = 6;
    RequestOpenRikuCards();
}

void RequestCloseCards() {
    gSoraCardRequest = 7;
    RequestCloseRikuCards();
}

void RequestCycleSoraCardList() {
    gSoraCardRequest = 9;
}

void RequestSwitchSoraCardList() {
    gSoraCardRequest = 10;
}

void func_080763A0() {
    gSoraCardRequest = 11;
}

void func_080763AC() {
    gSoraCardRequest = 12;
}

void func_080763B8() {
    gSoraCardRequest = 13;
}

void ClearSoraCardRequest() {
    gSoraCardRequest = 0;
}

u8 IsSoraReloadCardSelected() {
    if (gSoraSelectedCard != NULL && (gSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD)) {
        return 1;
    }

    return 0;
}

void SetSoraReloadCharging() {
    // @bug Called before the card battle state exists (NULL write).
    if (gSoraSelectedCard != NULL) {
        if ((gSoraSelectedCard->flags & (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED | CARD_DISP_FLAG_RELOAD_GAUGE)) == (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED | CARD_DISP_FLAG_RELOAD_GAUGE)) {
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
    if (gSoraSelectedCard != NULL) {
        return gSoraSelectedCard->flags & CARD_DISP_FLAG_NO_CARD;
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
    gCardBattleState->unk_0E9 = 0;
    gCardBattleState->addedFriendCards[0] = 0;
    gCardBattleState->addedFriendCards[1] = 0;
    gCardBattleState->cardsOpen = 0;
    gCardBattleState->soraHcEffectReplaced = 0;
    gCardBattleState->rikuHcEffectReplaced = 0;
    gCardBattleState->unk_0ED = 0;
    gCardBattleState->unk_0DE = 0;
    gCardBattleState->unk_0DF = 0;
    gCardBattleState->unk_0EE = 0;
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
    gCardBattleState->tiles5 = LoadObjTiles(gUnk_0905EAE8, 320);
    gCardBattleState->tiles6 = LoadObjTiles(gUnk_0905ED36, 320);
    gCardBattleState->tiles7 = LoadObjTiles(gUnk_0905EEE6, 320);
    gCardBattleState->palette = LoadObjPalette(gCard00Palette, 32);
    gCardBattleState->palette2 = LoadObjPalette(gBStatesPalette, 32);
    FadeSetPaletteExcluded(((ObjPaletteHeader*)gCardBattleState->palette)->index + 16, 1);
    LoadPremiumCardGfx(gCardBattleState);
}

CardSlot* FindNextAvailableSlot(CardBattleWork* w, u8 slot, u16* n) {
    CardSlot* e;
    s16 i;
    u16 cur;
    u16 next;

    i = *n;

    if (w->slots[slot][i].unk_06 == 0 && w->slots[slot][i].stocked == 0) {
        if (w->slots[slot][i].used == 0 && w->slots[slot][i].removed == 0) {
            return &w->slots[slot][(s16)*n];
        }
    }

    cur = *n;
    next = cur + 1;

    if ((s16)next >= w->slotCounts[slot]) {
        next = 0;
    }

    while ((s16)next != (s16)cur) {
        i = next;

        if (w->slots[slot][i].unk_06 == 0 && w->slots[slot][i].stocked == 0) {
            if (w->slots[slot][i].used == 0 && w->slots[slot][i].removed == 0) {
                e = &w->slots[slot][i];
                *n = next;
                return e;
            }
        }

        next = i + 1;

        if ((s16)next >= w->slotCounts[slot]) {
            next = 0;
        }
    }

    return NULL;
}

CardSlot* FindPrevAvailableSlot(CardBattleWork* w, u8 slot, u16* n) {
    CardSlot* e;
    s16 i;
    u16 cur;
    u16 next;

    i = *n;

    if (w->slots[slot][i].unk_06 == 0 && w->slots[slot][i].stocked == 0) {
        if (w->slots[slot][i].used == 0 && w->slots[slot][i].removed == 0) {
            return &w->slots[slot][(s16)*n];
        }
    }

    cur = *n;
    next = cur - 1;

    if ((s16)next < 0) {
        next = w->slotCounts[slot] - 1;
    }

    while ((s16)next != (s16)cur) {
        i = next;

        if (w->slots[slot][i].unk_06 == 0 && w->slots[slot][i].stocked == 0) {
            if (w->slots[slot][i].used == 0 && w->slots[slot][i].removed == 0) {
                e = &w->slots[slot][i];
                *n = next;
                return e;
            }
        }

        next = i - 1;

        if ((s16)next < 0) {
            next = w->slotCounts[slot] - 1;
        }
    }

    return NULL;
}

void CreateSoraCardRing(CardBattleWork* w, u8 slot) {
    CardDisplayArgs arg;
    u16 n;
    s16 count = 0;
    u16 old;
    CardSlot* c;
    CardDisplayWork* e;
    CardDisplayWork* p;

    if (w->cursors[slot] != 0xFFFF) {
        u32 index = w->cursors[slot];
        n = index;
        old = index;
        c = FindNextAvailableSlot(w, slot, &n);

        if (c != NULL) {
            arg.pool = &w->cardDisplays[slot];
            arg.index = n;
            arg.listIndex = slot;
            arg.slot = c;
            arg.reloadCount = w->reloadCounts[slot];

            if (c->cardId == CARD_ID_RELOAD) {
                TaskCreate(&w->tasks, &gTaskDescCardReload, &arg);
            } else {
                TaskCreate(&w->tasks, &gTaskDescCardSora, &arg);
            }

            c->unk_06 = 1;
            old = n;
            n = old + 1;
            count++;
        }

        if ((s16)n >= w->slotCounts[slot]) {
            n = 0;
        }

        c = FindNextAvailableSlot(w, slot, &n);

        if (c != NULL && (s16)n != w->cursors[slot]) {
            arg.pool = &w->cardDisplays[slot];
            arg.index = n;
            arg.listIndex = slot;
            arg.slot = c;
            arg.reloadCount = w->reloadCounts[slot];

            if (c->cardId == CARD_ID_RELOAD) {
                TaskCreate(&w->tasks, &gTaskDescCardReload, &arg);
            } else {
                TaskCreate(&w->tasks, &gTaskDescCardSora, &arg);
            }

            c->unk_06 = 1;
            old = n;
            count++;
        }

        n = w->cursors[slot] - 1;

        if ((s16)n < 0) {
            n = w->slotCounts[slot] - 1;
        }

        c = FindPrevAvailableSlot(w, slot, &n);

        if (c != NULL && (s16)n != w->cursors[slot] && (s16)n != (s16)old) {
            arg.pool = &w->cardDisplays[slot];
            arg.index = n;
            arg.listIndex = slot;
            arg.slot = c;
            arg.reloadCount = w->reloadCounts[slot];

            if (c->cardId == CARD_ID_RELOAD) {
                TaskCreate(&w->tasks, &gTaskDescCardReload, &arg);
            } else {
                TaskCreate(&w->tasks, &gTaskDescCardSora, &arg);
            }

            c->unk_06 = 1;
            count++;
        }
    }

    switch (count) {
        case 0:
            arg.pool = &w->cardDisplays[slot];
            arg.index = 0xFFFF;
            arg.slot = w->slots[slot];
            arg.listIndex = slot;
            TaskCreate(&w->tasks, &gTaskDescCardNotHave, &arg);
            e = ListPoolFirst(&w->cardDisplays[slot]);
            e->unk_80 = e->unk_7C = gSoraCardRingAngles[1];
            e->swingAngleTarget = e->swingAngle = gSoraCardSwingAngles[0];
            e->ringIndex = 1;
            e->priority = 50;
            e->flags |= (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_VISIBLE);
            break;
        case 1:
            e = ListPoolFirst(&w->cardDisplays[slot]);
            e->unk_80 = e->unk_7C = gSoraCardRingAngles[1];
            e->swingAngleTarget = e->swingAngle = gSoraCardSwingAngles[0];
            e->ringIndex = 1;
            e->priority = 50;
            e->flags |= CARD_DISP_FLAG_VISIBLE;
            break;
        case 2:
            e = ListPoolFirst(&w->cardDisplays[slot]);
            e->unk_80 = e->unk_7C = gSoraCardRingAngles[1];
            e->swingAngleTarget = e->swingAngle = gSoraCardSwingAngles[0];
            e->priority = 50;
            e->ringIndex = 1;
            e->flags |= CARD_DISP_FLAG_VISIBLE;
            e = ListPoolNext(&e->node);
            e->unk_80 = e->unk_7C = gSoraCardRingAngles[0];
            e->swingAngleTarget = e->swingAngle = gSoraCardSwingAngles[0];
            e->priority = 60;
            e->ringIndex = 0;
            e->flags |= CARD_DISP_FLAG_VISIBLE;
            break;
        case 3:
            e = ListPoolFirst(&w->cardDisplays[slot]);
            e->unk_80 = e->unk_7C = gSoraCardRingAngles[1];
            e->swingAngleTarget = e->swingAngle = gSoraCardSwingAngles[0];
            e->priority = 50;
            e->ringIndex = 1;
            e->flags |= CARD_DISP_FLAG_VISIBLE;
            e = ListPoolNext(&e->node);
            e->unk_80 = e->unk_7C = gSoraCardRingAngles[2];
            e->swingAngleTarget = e->swingAngle = gSoraCardSwingAngles[0];
            e->priority = 60;
            e->ringIndex = 2;
            e->flags |= CARD_DISP_FLAG_VISIBLE;
            e = ListPoolNext(&e->node);
            e->unk_80 = e->unk_7C = gSoraCardRingAngles[0];
            e->swingAngleTarget = e->swingAngle = gSoraCardSwingAngles[0];
            e->priority = 60;
            e->ringIndex = 0;
            e->flags |= CARD_DISP_FLAG_VISIBLE;
            break;
    }

    p = ListPoolFirst(&w->cardDisplays[slot]);

    while (p != NULL) {
        // @bug A "not have" display has no slot (NULL write).
        p->args.slot->unk_06 = 0;
        p = ListPoolNext(&p->node);
    }

    w->selectedCards[slot] = ListPoolFirst(&w->cardDisplays[slot]);

    {
        CardDisplayWork** active = &gSoraSelectedCard;
        *active = ListPoolFirst(&w->cardDisplays[slot]);
    }

    gSoraSelectedCard->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
}

static void cardbattle_0(CardBattleWork* w) {
    u8 i;

    CpuFill32(0, w, sizeof(CardBattleWork));
    // @bug gCardBattleState is only allocated further down (NULL write).
    gCardBattleState->soraWork = w;
    gBtlWork->hcEffect = 0;
    ResetBossCardValue();
    func_080782EC();
    w->tiles = AllocSpriteFrameTiles(128);
    w->palette = LoadObjPalette(gBStatesPalette, 32);
    UpdateSpriteFrameTiles(w->tiles, gUnk_09EF12E8[0], gUnk_093FBAB8);
    TaskPoolInit(&w->tasks, 30);
    w->stockCount = 0;
    w->listIndex = 0;
    w->reloadPending[0] = 0;
    w->reloadPending[1] = 0;
    w->reloadPending[2] = 0;
    w->reloadPending[3] = 0;
    w->revCountShown[0] = 1;
    w->revCountShown[1] = 0;
    w->revCountShown[2] = 0;
    w->revCountShown[3] = 0;
    w->stockValue = 0;
    w->unk_C4[3] = 0;
    w->x = sSoraStockValueX[0];
    w->cardsClosed = 0;

    for (i = 0; i < 3; i++) {
        w->playedCards[i] = NULL;
        w->stock[i] = NULL;
    }

    for (i = 0; i < 4; i++) {
        w->selectedCards[i] = NULL;
        w->slots[i] = NULL;
    }

    w->unk_C4[1] = 0;

    if (gBtlWork->flags & BTL_FLAG_TUTORIAL) {
        w->slotCounts[0] = gUnk_09041FA0.cardCount + 15;
        w->cardsLeft[0] = gUnk_09041FA0.cardCount + 1;
        w->slotCounts[3] = w->cardsLeft[3] = 0;
        w->slotCounts[2] = w->cardsLeft[2] = 0;
        w->slotCounts[1] = w->cardsLeft[1] = 0;
        InitSoraTutorialCardList(w, 0);
        InitSoraTutorialCardList(w, 1);
    } else {
        w->slotCounts[0] = CountActiveDeckCards(0) + 15;
        w->cardsLeft[0] = CountActiveDeckCards(0) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountActiveDeckCards(1);
        w->slotCounts[2] = w->cardsLeft[2] = 0;
        w->slotCounts[1] = w->cardsLeft[1] = 0;
        InitSoraCardList(w, 0);
        InitSoraCardList(w, 1);
    }

    w->reloadCounts[2] = w->reloadCounts[1] = w->reloadCounts[0] = 0;
    CreateCardBattleState();
    CreateREVCOUNTTask(&w->tasks, (u8*)&w->listIndex, &w->cardsLeft[w->listIndex], &w->revCountShown[w->listIndex], 1);
    ListPoolInit(&w->cardDisplays[0]);
    ListPoolInit(&w->cardDisplays[1]);
    ListPoolInit(&w->cardDisplays[2]);
    ListPoolInit(&w->cardDisplays[3]);
    CreateSoraCardRing(w, w->listIndex);
    gSoraCardRequest = 0;
    gSoraCardReloadRequest = 0;
    CreateBosscardTask(&w->tasks);
    w->unk_C4[4] = 0;

    if (gGameState.flags & GAME_FLAG_DARK_POINTS_LOCKED) {
        return;
    }

    if (gGameState.flags & GAME_FLAG_RIKU) {
        TaskCreate(&w->tasks, &gTaskDescDarkPoint, NULL);
    }
}

s32 func_08076F4C(CardBattleWork* w) {
    if (CountAvailableCards(w, 0) == 0 && w->cardsLeft[0] <= 1 && w->stockCount != 0) {
        return 1;
    }

    return 0;
}

s32 cardbattleSora_1(CardBattleWork* w, Task* task) {
    UnkStruct_080ABA80 data;
    u8 flag[4];
    UnkStruct_080ABA80 cards;
    u8 output[6];
    u8 i;
    u8 found;
    s32 position;
    u16 result;
    s32 kind;
    ReloadArgs args;
    BtlObj* actor;

    if (gBtlWork->phase == 4) {
        if (gBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
            gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
        }

        return 0;
    }

    if (w->unk_C4[3] != 0) {
        position = w->x * 256;
        ApproachValue(&position, (s16)sSoraStockValueX[w->stockCount - 1] * 256, w->unk_C4[3]);
        w->x = position >> 8;
        w->unk_C4[3]--;
    }

    if (w->cardsClosed == 0) {
        if (gSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
            if (gSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_DONE) {
            if (gBtlWork->hcEffect == 9) {
                RemoveSoraCardDisplays(w);
                TaskPoolUpdate(&w->tasks);

                if (gBtlWork->hcEffect != 25) {
                    IncrementReloadCount(w);

                    if (gBtlWork->hcEffect == 10) {
                        w->reloadCounts[w->listIndex] -= 2;

                        if (w->reloadCounts[w->listIndex] < 0) {
                            w->reloadCounts[w->listIndex] = 0;
                        }
                    }
                }

                gCardBattleState->soraReloadCounter = w->reloadCounts[w->listIndex];
                gCardBattleState->soraReloadGauge = 0;
                gCardBattleState->soraGaugeFullFrame = 4;
                ResetCardSlotsForReload(w, 0);
                w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
                w->cursors[0] = 0;
                CreateSoraCardRing(w, 0);
                TickSoraHcEffectOnReload();
            } else {
                gBtlWork->flags |= BTL_FLAG_RELOADING;
                RemoveSoraCardDisplays(w);

                if (gBtlWork->hcEffect != 25) {
                    IncrementReloadCount(w);

                    if (gBtlWork->hcEffect == 10) {
                        w->reloadCounts[w->listIndex] -= 2;

                        if (w->reloadCounts[w->listIndex] < 0) {
                            w->reloadCounts[w->listIndex] = 0;
                        }
                    }
                }

                gCardBattleState->soraReloadCounter = w->reloadCounts[w->listIndex];
                gCardBattleState->soraReloadGauge = 0;
                gCardBattleState->soraGaugeFullFrame = 4;
                ClearUsedCardSlots(w, 0);
                w->cursors[w->listIndex] = 0;
                w->cardsLeft[w->listIndex] = 0;
                w->reloadPending[w->listIndex] = 1;
                gSoraSelectedCard = NULL;
                gSoraCardRequest = 0;
            }
            }
        }

        switch (gSoraCardRequest) {
        case 0:
            break;
        case 1:
            gSoraCardRequest = 0;

            if (w->cardsLeft[w->listIndex] > 2) {
                if (gSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED) {
                    SelectNextSoraCard(w, w->listIndex);
                }
            } else if (w->cardsLeft[w->listIndex] > 1 && (gSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED)) {
                SelectOtherSoraCard(w, w->listIndex, 4);
            }

            break;
        case 2:
            gSoraCardRequest = 0;

            if (w->cardsLeft[w->listIndex] > 2) {
                if (gSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED) {
                    SelectPrevSoraCard(w, w->listIndex, 4);
                }
            } else if (w->cardsLeft[w->listIndex] > 1 && (gSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED)) {
                SelectOtherSoraCard(w, w->listIndex, 4);
            }

            break;
        case 4:
            gSoraCardRequest = 0;

            if (!(gSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD)) {
                if (w->stockCount == 3) {
                    UseSoraStock(w);
                } else if (gSoraSelectedCard->cardDef->category == 3) {
                    m4aSongNumStart(SONG_SYS_BEEP);
                } else if (w->reloadPending[w->listIndex] == 0) {
                    if (!(gSoraSelectedCard->flags & CARD_DISP_FLAG_NO_CARD)) {
                        if (CanUseSoraSelectedCard() != 0) {
                            if (w->cardsLeft[w->listIndex] > 0 && w->stockCount <= 2 && gCardBattleState->soraStockActive == 0) {
                                StockSoraCard(w);
                            }
                        } else if (gSoraSelectedCard->flags & CARD_DISP_FLAG_OPEN) {
                            m4aSongNumStart(SONG_SYS_BEEP);
                        }
                    } else if (gSoraSelectedCard->flags & CARD_DISP_FLAG_OPEN) {
                        m4aSongNumStart(SONG_SYS_BEEP);
                    }
                }
            } else if (w->stockCount != 0) {
                UseSoraStock(w);
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }

            w->unk_C4[4] = 1;
            break;
        case 3:
            gSoraCardRequest = 0;

            if (gSoraSelectedCard->cardDef->category != 3 && !(gSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD)) {
                if (w->reloadPending[w->listIndex] == 0) {
                    if (gSoraSelectedCard->cardDef->flags & CARD_DEF_FLAG_GIMMICK) {
                        UseSoraGimmickCard(w);
                    } else if (!(gSoraSelectedCard->flags & CARD_DISP_FLAG_NO_CARD)) {
                        if (CanUseSoraSelectedCard() != 0) {
                            UseSoraCard(w);
                        } else if (gSoraSelectedCard->flags & CARD_DISP_FLAG_OPEN) {
                            m4aSongNumStart(SONG_SYS_BEEP);
                        }
                    } else if (gSoraSelectedCard->flags & CARD_DISP_FLAG_OPEN) {
                        m4aSongNumStart(SONG_SYS_BEEP);
                    }
                }
            } else if (gSoraSelectedCard->cardDef->category == 3 && !(gSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD)) {
                UseSoraHeartlessCard(w);
            } else if (gGameState.flags & GAME_FLAG_RIKU) {
                RemoveSoraCardDisplays(w);
                gSoraSelectedCard = NULL;
                gBtlWork->flags |= BTL_FLAG_RELOADING;
                w->cardsLeft[w->listIndex] = 0;
                w->reloadPending[w->listIndex] = 1;
            }

            w->unk_C4[4] = 1;
            break;
        case 5:
            gSoraCardRequest = 0;

            if (w->stockCount != 0) {
                UseSoraStock(w);
            } else if (!(gBtlWork->flags & BTL_FLAG_CARD_ACTIVE)) {
                m4aSongNumStart(SONG_SYS_BEEP);
            }

            w->unk_C4[4] = 1;
            break;
        case 6:
            gSoraCardRequest = 0;
            OpenSoraCards(w);
            break;
        case 7:
            w->revCountShown[w->listIndex] = 0;
            w->unk_C4[0] = 0;
            CloseSoraCards(w);
            break;
        case 8:
            gSoraCardRequest = 0;
            break;
        case 9:
            gSoraCardRequest = 0;
            CycleSoraCardList(w);
            w->unk_C4[4] = 1;
            break;
        case 10:
            gSoraCardRequest = 0;
            SwitchSoraCardList(w);
            w->unk_C4[4] = 1;
            break;
        case 11:
            w->timer = 60;
            gSoraCardRequest = 0;
            SetTaskUpdate(task, (TaskUpdateFunc)func_0807B578);
            break;
        case 12:
            w->timer = 180;
            gSoraCardRequest = 0;
            SetTaskUpdate(task, (TaskUpdateFunc)func_0807B578);
            break;
        case 13:
            w->timer = 300;
            gSoraCardRequest = 0;
            SetTaskUpdate(task, (TaskUpdateFunc)func_0807B578);
            break;
        default:
            gSoraCardRequest = 0;
            break;
        }

        switch (gSoraCardReloadRequest) {
        case 14:
            gSoraCardReloadRequest = 0;

            if (w->listIndex == 0) {
                RemoveSoraCardDisplays(w);
                gSoraSelectedCard = NULL;
            } else {
                RemoveSoraCardDisplays(w);
                w->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
                gSoraSelectedCard = NULL;
            }

            gBtlWork->flags |= BTL_FLAG_RELOADING;
            w->cardsLeft[0] = 0;
            w->reloadPending[0] = 1;
            m4aSongNumStart(SONG_SYS_CHAGEF2);

            if (FadeGetAmount() == 0) {
                FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
            }

            break;
        case 15:
            gSoraCardReloadRequest = 0;

            if (w->listIndex == 0) {
                RemoveSoraCardDisplays(w);
                gSoraSelectedCard = NULL;
            } else {
                RemoveSoraCardDisplays(w);
                w->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
                gSoraSelectedCard = NULL;
            }

            m4aSongNumStart(SONG_SYS_CHAGEF2);

            if (FadeGetAmount() == 0) {
                FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
            }

            gBtlWork->flags |= BTL_FLAG_RELOADING;
            w->cardsLeft[0] = 0;
            w->reloadPending[0] = 1;
            break;
        case 16:
            gSoraCardReloadRequest = 0;

            if (w->listIndex == 0) {
                RemoveSoraCardDisplays(w);
                gSoraSelectedCard = NULL;
            } else {
                RemoveSoraCardDisplays(w);
                w->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
                gSoraSelectedCard = NULL;
            }

            m4aSongNumStart(SONG_SYS_CHAGEF2);

            if (FadeGetAmount() == 0) {
                FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
            }

            gBtlWork->flags |= BTL_FLAG_RELOADING;
            w->cardsLeft[0] = 0;
            w->reloadPending[0] = 1;
            break;
        case 17:
            gSoraCardReloadRequest = 0;
            RestoreCardsForPotion(w);

            if (w->listIndex == 0) {
                RemoveSoraCardDisplays(w);
            } else {
                RemoveSoraCardDisplays(w);
                w->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
            }

            TaskPoolUpdate(&w->tasks);
            ClearUsedCardSlots(w, 0);
            w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
            w->cursors[0] = 0;
            CreateSoraCardRing(w, 0);

#ifdef VERSION_EU
            if (w->revCountShown[w->listIndex] == 0) {
                CreateREVCOUNTTask(&w->tasks, (u8*)&w->listIndex, &w->cardsLeft[w->listIndex], &w->revCountShown[w->listIndex], 1);
            }
#endif

            TickSoraHcEffectOnReload();
            break;
        case 18:
            gSoraCardReloadRequest = 0;
            RestoreCardsForHiPotion(w);

            if (w->listIndex == 0) {
                RemoveSoraCardDisplays(w);
            } else {
                RemoveSoraCardDisplays(w);
                w->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
            }

            TaskPoolUpdate(&w->tasks);
            ClearUsedCardSlots(w, 0);
            w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
            w->cursors[0] = 0;
            CreateSoraCardRing(w, 0);

#ifdef VERSION_EU
            if (w->revCountShown[w->listIndex] == 0) {
                CreateREVCOUNTTask(&w->tasks, (u8*)&w->listIndex, &w->cardsLeft[w->listIndex], &w->revCountShown[w->listIndex], 1);
            }
#endif

            TickSoraHcEffectOnReload();
            break;
        case 19:
            gSoraCardReloadRequest = 0;
            RestoreCardsForMegaPotion(w);
            w->reloadCounts[0] = 0;
            ResetSoraReloadGauge(w);

            if (w->listIndex == 0) {
                RemoveSoraCardDisplays(w);
            } else {
                RemoveSoraCardDisplays(w);
                w->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
            }

            TaskPoolUpdate(&w->tasks);
            ClearUsedCardSlots(w, 0);
            w->cursors[0] = 0;
            w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
            CreateSoraCardRing(w, 0);

#ifdef VERSION_EU
            if (w->revCountShown[w->listIndex] == 0) {
                CreateREVCOUNTTask(&w->tasks, (u8*)&w->listIndex, &w->cardsLeft[w->listIndex], &w->revCountShown[w->listIndex], 1);
            }
#endif

            TickSoraHcEffectOnReload();
            break;
        case 21:
            gSoraCardReloadRequest = 0;
            RestoreCardsForEther(w);

            if (w->listIndex == 0) {
                RemoveSoraCardDisplays(w);
            } else {
                RemoveSoraCardDisplays(w);
                w->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
            }

            TaskPoolUpdate(&w->tasks);
            ClearUsedCardSlots(w, 0);
            w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
            w->cursors[0] = 0;
            CreateSoraCardRing(w, 0);

#ifdef VERSION_EU
            if (w->revCountShown[w->listIndex] == 0) {
                CreateREVCOUNTTask(&w->tasks, (u8*)&w->listIndex, &w->cardsLeft[w->listIndex], &w->revCountShown[w->listIndex], 1);
            }
#endif

            TickSoraHcEffectOnReload();
            break;
        case 22:
            gSoraCardReloadRequest = 0;
            RestoreCardsForMegaEther(w);
            w->reloadCounts[0] = 0;
            ResetSoraReloadGauge(w);

            if (w->listIndex == 0) {
                RemoveSoraCardDisplays(w);
            } else {
                RemoveSoraCardDisplays(w);
                w->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
            }

            TaskPoolUpdate(&w->tasks);
            ClearUsedCardSlots(w, 0);
            w->cursors[0] = 0;
            w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
            CreateSoraCardRing(w, 0);

#ifdef VERSION_EU
            if (w->revCountShown[w->listIndex] == 0) {
                CreateREVCOUNTTask(&w->tasks, (u8*)&w->listIndex, &w->cardsLeft[w->listIndex], &w->revCountShown[w->listIndex], 1);
            }
#endif

            TickSoraHcEffectOnReload();
            break;
        case 23:
            gSoraCardReloadRequest = 0;
            RestoreCardsForElixir(w);

            if (w->listIndex == 0) {
                RemoveSoraCardDisplays(w);
            } else {
                RemoveSoraCardDisplays(w);
                w->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
            }

            TaskPoolUpdate(&w->tasks);
            ClearUsedCardSlots(w, 0);
            w->cursors[0] = 0;
            w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
            CreateSoraCardRing(w, 0);

#ifdef VERSION_EU
            if (w->revCountShown[w->listIndex] == 0) {
                CreateREVCOUNTTask(&w->tasks, (u8*)&w->listIndex, &w->cardsLeft[w->listIndex], &w->revCountShown[w->listIndex], 1);
            }
#endif

            TickSoraHcEffectOnReload();
            break;
        case 24:
            gSoraCardReloadRequest = 0;
            RestoreCardsForElixir(w);
            w->reloadCounts[0] = 0;
            ResetSoraReloadGauge(w);

            if (w->listIndex == 0) {
                RemoveSoraCardDisplays(w);
            } else {
                RemoveSoraCardDisplays(w);
                w->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
            }

            TaskPoolUpdate(&w->tasks);
            ClearUsedCardSlots(w, 0);
            w->cursors[0] = 0;
            w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
            CreateSoraCardRing(w, 0);

#ifdef VERSION_EU
            if (w->revCountShown[w->listIndex] == 0) {
                CreateREVCOUNTTask(&w->tasks, (u8*)&w->listIndex, &w->cardsLeft[w->listIndex], &w->revCountShown[w->listIndex], 1);
            }
#endif

            TickSoraHcEffectOnReload();
            break;
        case 20:
            gSoraCardReloadRequest = 0;
            RemoveItemCards(w);

            if (w->listIndex == 0) {
                w->reloadCounts[0] = 0;
                RemoveSoraCardDisplays(w);
                gSoraSelectedCard = NULL;
            } else {
                RemoveSoraCardDisplays(w);
                w->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
                gSoraSelectedCard = NULL;
            }

            m4aSongNumStart(SONG_SYS_CHAGEF2);

            if (FadeGetAmount() == 0) {
                FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
            }

            gBtlWork->flags |= BTL_FLAG_RELOADING;
            w->cardsLeft[0] = 0;
            w->reloadPending[0] = 1;
            break;
        default:
            gSoraCardReloadRequest = 0;
            break;
        }

        if (gCardBattleState->pickedFriendCardId != 950 && w->unk_C4[4] == 0 && w->reloadPending[w->listIndex] == 0) {
            gBtlWork->flags |= 0x20000000000LL;
            AddPickedCardToSoraDeck(w);
        }

        if (gCardBattleState->pickedGimmickCardId != 950 && w->unk_C4[4] == 0 && w->reloadPending[w->listIndex] == 0) {
            AddPickedCardToSoraDeck(w);
        }

        if (w->reloadPending[w->listIndex] != 0) {
            if (gSoraSelectedCard != NULL) {
                if (gSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_DONE) {
                    gSoraSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
                    BeginSoraReloadDeal(w);
                    w->reloadPending[w->listIndex] = 0;
                    w->unk_C4[0] = 1;
                    SetTaskUpdate(task, (TaskUpdateFunc)UpdateSoraReloadDeal);
                    TaskPoolUpdate(&w->tasks);
                    TaskPoolUpdate(&gCardBattleState->tasks);
                    args.slot = w->listIndex;
                    args.state = &w->unk_C4[0];
                    args.mode = 1;
                    TaskCreate(&w->tasks, &gTaskDescRELOAD, &args);
                    return 1;
                }
            } else {
                BeginSoraReloadDeal(w);
                w->reloadPending[w->listIndex] = 0;
                SetTaskUpdate(task, (TaskUpdateFunc)UpdateSoraReloadDeal);
                TaskPoolUpdate(&w->tasks);
                TaskPoolUpdate(&gCardBattleState->tasks);
                return 1;
            }
        } else if (gSoraSelectedCard != NULL && (gSoraSelectedCard->flags & (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_SETTLED)) == (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_SETTLED) && CountAvailableCards(w, w->listIndex) != 0) {
            w->reloadPending[w->listIndex] = 1;
            gSoraSelectedCard->command = 7;
            actor = gBtlWork->actor;

            if (actor->hp > 3) {
                actor->hp -= 2;
            }

            gBtlWork->flags |= BTL_FLAG_RELOADING;

            if (gBtlWork->hcEffect != 25) {
                IncrementReloadCount(w);

                if (gBtlWork->hcEffect == 10) {
                    w->reloadCounts[w->listIndex] -= 2;

                    if (w->reloadCounts[w->listIndex] < 0) {
                        w->reloadCounts[w->listIndex] = 0;
                    }
                }
            }
        }

        if (w->unk_C4[1] == 0 && AreCardsSettled(w->stock, w->stockCount) != 0) {
            data = gUnk_09033FD0;

            if (!(gBtlWork->flags & BTL_FLAG_VS_BATTLE)) {
                result = LookupStockName(w->stock, w->stockCount, w->stockValue, &data, flag);
            } else {
                result = LookupLinkStockName(w->stock, w->stockCount, w->stockValue, &data, flag, 0);
            }

            if (result != 108) {
                gCardBattleState->soraStockName = result;

                if (result <= 105) {
                    if (result != 107) {
                        for (i = 0; i < w->stockCount; i++) {
                            w->stock[i]->flags |= CARD_DISP_FLAG_STOCK_NAMED;
                        }

                        if (gCardBattleState->soraStockNameShown == 0) {
                            TaskCreate(&w->tasks, &gTaskDescStockNameSora, NULL);
                            gCardBattleState->soraStockNameShown = 1;
                        }
                    } else {
                        for (i = 0; i < w->stockCount; i++) {
                            w->stock[i]->flags |= CARD_DISP_FLAG_STOCK_NAMED;
                        }

                        if (gCardBattleState->soraStockNameShown == 0) {
                            TaskCreate(&w->tasks, &gTaskDescStockNameSora, &data);
                            gCardBattleState->soraStockNameShown = 1;
                        }
                    }
                } else if (w->stockCount == 3) {
                    cards = gUnk_09033FD0;
                    memset(output, 0, sizeof(output));
                    found = 0;

                    for (i = 0; i < w->stockCount; i++) {
                        cards.unk_00[i] = w->stock[i]->cardDef->unk_28;
                    }

                    kind = LookupStockPairName(&cards, output, w->stockCount);

                    switch (kind) {
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
                        gCardBattleState->soraStockName = kind;
                        found = 1;
                        break;
                    }

                    if (found == 0) {
                        for (i = 0; i < w->stockCount; i++) {
                            w->stock[i]->flags &= ~CARD_DISP_FLAG_STOCK_NAMED;
                        }

                        if (gCardBattleState->soraStockNameShown != 0) {
                            gCardBattleState->soraStockNameShown = 0;
                        }
                    } else {
                        for (i = 0; i < w->stockCount; i++) {
                            w->stock[i]->flags |= CARD_DISP_FLAG_STOCK_NAMED;
                        }

                        if (gCardBattleState->soraStockNameShown == 0) {
                            TaskCreate(&w->tasks, &gTaskDescStockNameSora, NULL);
                            gCardBattleState->soraStockNameShown = 1;
                        }
                    }
                }
            }

            w->unk_C4[1] = 1;
        }
    }

    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&gCardBattleState->tasks);
    gCardBattleState->soraStockCount = w->stockCount;
    w->unk_C4[4] = 0;

    if (gBtlWork->flags & BTL_FLAG_DARK_MODE_CHANGED) {
        gBtlWork->flags &= ~BTL_FLAG_DARK_MODE_CHANGED;
        w->unk_C4[1] = 0;
    }

    return 1;
}

static void cardbattle_2(CardBattleWork* w) {
    gCardBattleState->gfx = AnimUpdate(&gCardBattleState->anim);
    gCardBattleState->gfx2 = AnimUpdate(&gCardBattleState->anim2);

    if (gCardBattleState->cardsOpen != 0 && w->stockCount != 0 && w->stockValue != 0) {
        DrawSprite(w->x, 4, gUnk_09EF12E8[0], w->tiles, w->palette, NULL, SPRITE_FLAG_NO_MOSAIC,
                   12);
    }

    TaskPoolDraw(&w->tasks);
    TaskPoolDraw(&gCardBattleState->tasks);
}

static void cardbattle_3(CardBattleWork* w) {
    u8 i;

    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&gCardBattleState->tasks);

    for (i = 0; i < 4; i++) {
        if (w->slots[i] != NULL) {
            EwramFree(w->slots[i]);
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
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

s32 UpdateSoraReloadDeal(CardBattleWork* w, Task* task) {
    CardDisplayArgs arg;
    CardDisplayWork* e;
    CardSlot* c;
    u16 n;
    s16 a;
    s16 b;
    s8 k;

    a = 255;
    b = 255;

    if (gBtlWork->phase == 4) {
        if (gRikuBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
            gRikuBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
        }

        m4aSongNumStop(SONG_SYS_RELOAD);

        return 0;
    }

    if ((s16)gSoraSelectedCard->timer == 0) {
        if (CountAvailableCardSlots(w, w->listIndex) > w->unk_C4[2]) {
            gSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
            e = ListPoolFirst(&w->cardDisplays[w->listIndex]);

            while (e != NULL) {
                e->ringIndex++;
                e->unk_80 = gSoraCardRingAngles[e->ringIndex];
                e->timer = 4;
                e->priority += 4;
                e = ListPoolNext(&e->node);
            }

            n = gSoraSelectedCard->args.index - 1;
            c = FindPrevAvailableSlot(w, w->listIndex, &n);

            if (c != NULL) {
                arg.pool = &w->cardDisplays[w->listIndex];
                arg.index = n;
                arg.listIndex = w->listIndex;
                arg.slot = c;
                arg.reloadCount = w->reloadCounts[w->listIndex];

                if (c->cardId == CARD_ID_RELOAD) {
                    e = TaskCreate(&w->tasks, &gTaskDescCardReload, &arg)->work;
                } else {
                    e = TaskCreate(&w->tasks, &gTaskDescCardSora, &arg)->work;
                }

                e->unk_80 = e->unk_7C = gSoraCardRingAngles[1];
                e->swingAngleTarget = e->swingAngle = gSoraCardSwingAngles[0];
                e->ringIndex = 1;
                e->timer = 8;
                e->priority = 50;
                e->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_DEALING | CARD_DISP_FLAG_VISIBLE);
                gSoraSelectedCard = e;
                w->unk_C4[2]++;
                w->cardsLeft[w->listIndex]++;
            }
        } else {
            e = ListPoolFirst(&w->cardDisplays[w->listIndex]);

            while (e != NULL) {
                k = e->ringIndex;

                if (k == 1) {
                    a = e->args.index;
                }

                if (k == 2) {
                    b = e->args.index;
                }

                e = ListPoolNext(&e->node);
            }

            n = w->slotCounts[w->listIndex] - 1;
            c = FindPrevAvailableSlot(w, w->listIndex, &n);

            if (c != NULL && (s16)n != a && (s16)n != b) {
                arg.pool = &w->cardDisplays[w->listIndex];
                arg.index = n;
                arg.listIndex = w->listIndex;
                arg.slot = c;
                arg.reloadCount = w->reloadCounts[w->listIndex];

                if (c->cardId == CARD_ID_RELOAD) {
                    e = TaskCreate(&w->tasks, &gTaskDescCardReload, &arg)->work;
                } else {
                    e = TaskCreate(&w->tasks, &gTaskDescCardSora, &arg)->work;
                }

                e->unk_7C = gSoraCardRingAngles[3];
                e->swingAngleTarget = e->swingAngle = gSoraCardSwingAngles[0];
                e->ringIndex = 0;
                e->unk_80 = gSoraCardRingAngles[0];
                e->priority = 60;
                e->flags |= CARD_DISP_FLAG_VISIBLE;
            }

            gBtlWork->flags &= ~BTL_FLAG_RELOADING;
            gBtlWork->flags &= ~0x100;
            w->unk_C4[0] = 0;
            m4aSongNumStop(SONG_SYS_RELOAD);
            gSoraCardRequest = 0;
            SetTaskUpdate(task, (TaskUpdateFunc)cardbattleSora_1);
        }
    }

    if (gSoraCardRequest == 7) {
        w->revCountShown[w->listIndex] = 0;
        w->unk_C4[0] = 0;
        CloseSoraCards(w);
        m4aSongNumStop(SONG_SYS_RELOAD);
    }

    TaskPoolUpdate(&w->tasks);
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

u8 IsCardDisplayOffScreen(CardDisplayWork* p);
void ReleaseCardDisplayGfx(CardDisplayWork* p);
void LookupSoraCardDef(CardDisplayArgs* a, CardDef** out, u8 index);
void LinkSoraCardDisplay(CardDisplayWork* p);
void LoadSoraCardDisplayGfx2(CardDisplayWork* p);
void UpdateSoraCardValue(CardDisplayWork* w);
void TickSoraHcEffectOnPlayEnd();
void RemoveSoraCardDisplays(CardBattleWork* w);
void ClearStockedCardSlots(CardBattleWork* w);
void TickSoraHcEffectOnCardUse();
void LoadCardDisplayGfx(CardDisplayWork* p);
u8 func_0807C934(CardDisplayWork* p, void* a);
u8 func_0807D810(CardDisplayWork* p);
void RefreshSoraCardDisplayGfx(CardDisplayWork* p);
void func_0807B458(CardBattleWork* w, u16 value);
void func_0807B45C(CardBattleWork* w);
void ApplySoraHcEffect(CardBattleWork* w);
void UpdateSoraCardRingPosition(CardDisplayWork* p);
u8 DispatchSoraCardCommand(CardDisplayWork* p, void* a);
u8 func_0807D584(CardDisplayWork* p, void* a);
u8 func_0807D7B0(CardDisplayWork* p);
void UpdateSoraReloadGauge(CardDisplayWork* p);
void TickSoraHcEffectOnAttackEnd();
u8 func_0807CE04(CardDisplayWork* p);
void func_0807D0F4(CardDisplayWork* p);

u8 AreCardsSettled(CardDisplayWork** p, u8 n) {
    u8 count;
    u8 i;

    i = 0;
    count = 0;

    for (; i < n; i++) {
        if (p[i]->flags & CARD_DISP_FLAG_SETTLED) {
            count++;
        }
    }

    if (n == count) {
        return 1;
    }

    return 0;
}

void func_080782EC() {
    gBtlWork->flags &= ~BTL_FLAG_CARD_ACTIVE;
    gBtlWork->flags &= ~0x100;
    gBtlWork->flags &= ~0x200;
    gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_START;
}

void LoadActiveDeckCardSlots(CardSlot* slots, s32 deckIndex) {
    u16* buf;
    u16 n;
    u16 i;

    n = CountActiveDeckCards(deckIndex);
    buf = EwramAlloc(n * 2);
    CpuFill16(0, buf, n * 2);
    CopyActiveDeckCards(deckIndex, buf);

    for (i = 0; i < n; i++) {
        slots[i].unk_06 = 0;
        slots[i].stocked = 0;
        slots[i].removed = 0;
        slots[i].cardId = buf[i];
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

    EwramFree(buf);
}

void LoadTutorialDeckCardSlots(CardSlot* slots) {
    u16 n;
    u16 i;

    n = gUnk_09041FA0.cardCount;

    for (i = 0; i < n; i++) {
        slots[i].unk_06 = 0;
        slots[i].stocked = 0;
        slots[i].removed = 0;
        slots[i].cardId = gUnk_09041F70[gUnk_09041FA0.cards[i]];
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

void ShuffleCardSlots(CardSlot* slots, u8 n) {
    CardSlot a;
    CardSlot b;
    u8 i;
    u8 x;
    u8 y;

    for (i = 0; i < n; i++) {
        x = GetRandom() % n;
        y = GetRandom() % n;

        if (x != y) {
            a = slots[x];
            b = slots[y];
            slots[x] = b;
            slots[y] = a;
        }
    }
}

void InitSoraTutorialCardList(CardBattleWork* w, s32 mode) {
    u16 n = gUnk_09041FA0.cardCount;

    switch (mode) {
    case 0: {
        CardSlot* slots;
        u16 i;

        slots = EwramAlloc((n + 15) * sizeof(CardSlot));
        w->slots[0] = slots;
        CpuFill32(0, slots, (n + 15) * sizeof(CardSlot));

        for (i = 0; i < n + 1; i++) {
            w->slots[0][i].unk_06 = 0;
            w->slots[0][i].stocked = 0;
            w->slots[0][i].removed = 0;
            w->slots[0][i].used = 0;
        }

        for (i = n + 1; i < n + 15; i++) {
            w->slots[0][i].unk_06 = 1;
            w->slots[0][i].stocked = 1;
            w->slots[0][i].removed = 1;
            w->slots[0][i].used = 1;
        }

        LoadTutorialDeckCardSlots(w->slots[0]);
        w->cursors[0] = 0;
        break;
    }
    case 1: {
        CardSlot* slot;
        u16* q;
        s32 k;

        slot = EwramAlloc(sizeof(CardSlot));
        w->slots[3] = slot;
        CpuFill32(0, slot, sizeof(CardSlot));
        w->slots[3]->cardId = 0x30FF;
        q = &w->cursors[3];
        k = 0xFFFF;
        *q = k;
        break;
    }
    }
}

void InitSoraCardList(CardBattleWork* w, s32 mode) {
    u16 n = CountActiveDeckCards(mode);

    switch (mode) {
    case 0:
        if (n != 0) {
            CardSlot* slots;
            u8 i;

            slots = EwramAlloc((n + 15) * sizeof(CardSlot));
            w->slots[0] = slots;
            CpuFill32(0, slots, (n + 15) * sizeof(CardSlot));

            for (i = 0; i < n + 1; i++) {
                w->slots[0][i].unk_06 = 0;
                w->slots[0][i].cardId = CARD_ID_NONE;
                w->slots[0][i].stocked = 0;
                w->slots[0][i].removed = 0;
                w->slots[0][i].used = 0;
            }

            for (i = n + 1; i < n + 15; i++) {
                w->slots[0][i].unk_06 = 1;
                w->slots[0][i].cardId = CARD_ID_NONE;
                w->slots[0][i].stocked = 1;
                w->slots[0][i].removed = 1;
                w->slots[0][i].used = 1;
            }

            LoadActiveDeckCardSlots(w->slots[0], 0);
            w->cursors[0] = 0;
        } else {
            CardSlot* slot;
            u16* q;
            s32 k;

            slot = EwramAlloc(sizeof(CardSlot));
            w->slots[0] = slot;
            CpuFill32(0, slot, sizeof(CardSlot));
            w->slots[0]->cardId = 0xFF;
            q = &w->cursors[0];
            k = 0xFFFF;
            *q = k;
        }

        break;
    case 1:
        if (n != 0) {
            CardSlot* slots;
            u8 i;

            slots = EwramAlloc(n * sizeof(CardSlot));
            w->slots[3] = slots;

            for (i = 0; i < n; i++) {
                w->slots[3][i].unk_06 = 0;
                w->slots[3][i].cardId = CARD_ID_NONE;
                w->slots[3][i].stocked = 0;
                w->slots[3][i].removed = 0;
                w->slots[3][i].used = 0;
            }

            LoadActiveDeckCardSlots(w->slots[3], 1);
            w->cursors[3] = 0;
        } else {
            CardSlot* slot;
            u16* q;
            s32 k;

            slot = EwramAlloc(sizeof(CardSlot));
            w->slots[3] = slot;
            CpuFill32(0, slot, sizeof(CardSlot));
            w->slots[3]->cardId = 0x30FF;
            q = &w->cursors[3];
            k = 0xFFFF;
            *q = k;
        }

        break;
    }
}

u16 CountAvailableCardSlots(CardBattleWork* w, u8 n) {
    u16 count;
    u16 i;
    u16 max;

    max = w->slotCounts[n];
    count = 0;

    for (i = 0; i < max; i++) {
        if (w->slots[n][i].unk_06 == 0 && w->slots[n][i].stocked == 0 && w->slots[n][i].used == 0 && w->slots[n][i].removed == 0) {
            count++;
        }
    }

    return count;
}

u16 CountAvailableCards(CardBattleWork* w, u8 n) {
    u16 count;
    u16 i;
    u16 max;

    max = w->slotCounts[n];
    count = 0;

    for (i = 0; i < max; i++) {
        if (w->slots[n][i].unk_06 == 0 && w->slots[n][i].stocked == 0 && w->slots[n][i].used == 0 && w->slots[n][i].removed == 0 && w->slots[n][i].cardId != CARD_ID_RELOAD) {
            count++;
        }
    }

    if (gSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD) {
        if (w->cardsLeft[w->listIndex] == 1) {
            count = 0;
        }
    }

    return count;
}

u16 CountRemainingAttackCards(CardBattleWork* w, u8 b) {
    CardSlot* c;
    u16 count;
    u16 i;
    u16 n;

    n = w->slotCounts[b];
    count = 0;

    for (i = 0; i < n; i++) {
        c = w->slots[b];

        if (c[i].removed == 0) {
            if (c[i].cardId != CARD_ID_RELOAD) {
                if (gCardDefs[c[i].cardId & CARD_ID_MASK].category == 0) {
                    count++;
                }
            }
        }
    }

    return count;
}

void ClearUsedCardSlots(CardBattleWork* w, u8 b) {
    u8 i;

    for (i = 0; i < w->slotCounts[b]; i++) {
        if (w->slots[b][i].stocked == 0) {
            w->slots[b][i].used = 0;
        }
    }
}

void ResetCardSlotsForReload(CardBattleWork* w, u8 n) {
    u8 i;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        for (i = 0; i < w->slotCounts[n]; i++) {
            if (w->slots[n][i].stocked == 0) {
                w->slots[n][i].used = 0;
                w->slots[n][i].unk_06 = 0;
            }

            if (!(gBtlWork->flags & BTL_FLAG_DARK_MODE)) {
                if (w->slots[n][i].restoreOnReload == 1) {
                    w->slots[n][i].removed = 0;
                    w->slots[n][i].restoreOnReload = 0;
                }
            }
        }
    } else {
        for (i = 0; i < w->slotCounts[n]; i++) {
            if (w->slots[n][i].stocked == 0) {
                w->slots[n][i].used = 0;
                w->slots[n][i].unk_06 = 0;
            }
        }
    }
}

void BeginSoraReloadDeal(CardBattleWork* w) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    CardSlot* c;
    u16 n;
    s32 z;

    z = 0;
    w->unk_C4[2] = z;
    ResetCardSlotsForReload(w, w->listIndex);

    if (CountAvailableCardSlots(w, w->listIndex) != z) {
        n = w->slotCounts[w->listIndex] - 1;
        c = FindPrevAvailableSlot(w, w->listIndex, &n);

        if (c != NULL) {
            args.pool = &w->cardDisplays[w->listIndex];
            args.index = n;
            args.listIndex = w->listIndex;
            args.slot = c;
            args.reloadCount = w->reloadCounts[w->listIndex];

            if (c->cardId == CARD_ID_RELOAD) {
                p = TaskCreate(&w->tasks, &gTaskDescCardReload, &args)->work;
            } else {
                p = TaskCreate(&w->tasks, &gTaskDescCardSora, &args)->work;
            }

            p->unk_80 = p->unk_7C = gSoraCardRingAngles[1];
            p->swingAngleTarget = p->swingAngle = gSoraCardSwingAngles[0];
            p->ringIndex = 1;
            p->timer = 8;
            p->priority = 50;
            p->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_DEALING | CARD_DISP_FLAG_VISIBLE);
            gSoraSelectedCard = p;
            w->unk_C4[2]++;
            w->cardsLeft[w->listIndex]++;
        }

        m4aSongNumStart(SONG_SYS_RELOAD);
    } else {
        args.pool = &w->cardDisplays[w->listIndex];
        args.index = 0xFFFF;
        args.slot = w->slots[w->listIndex];
        args.listIndex = w->listIndex;
        p = TaskCreate(&w->tasks, &gTaskDescCardNotHave, &args)->work;
        p->unk_80 = p->unk_7C = gSoraCardRingAngles[1];
        p->swingAngleTarget = p->swingAngle = gSoraCardSwingAngles[0];
        p->priority = 50;
        p->flags |= (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
        gSoraSelectedCard = p;
    }

    z = w->listIndex;

    if (w->cardsLeft[z] > 0) {
        if (w->revCountShown[z] == 0) {
            CreateREVCOUNTTask(&w->tasks, &w->listIndex, &w->cardsLeft[z], &w->revCountShown[z], 1);
        }
    }

    TickSoraHcEffectOnReload();
}

void AddPickedCardToSoraDeck(CardBattleWork* w) {
    CardDisplayWork* node;
    CardSlot* c;
    s32 z;

    c = w->slots[0];

    if (gCardBattleState->pickedGimmickCardId == 0x28F) {
        c[w->slotCounts[0] - 5].cardId = 0x28F;
        c[w->slotCounts[0] - 5].index = w->slotCounts[0] - 5;
        c[w->slotCounts[0] - 5].unk_06 = 0;
        c[w->slotCounts[0] - 5].stocked = 0;
        c[w->slotCounts[0] - 5].removed = 0;
        c[w->slotCounts[0] - 5].used = 0;
        gCardBattleState->pickedGimmickCardId = 0x3B6;
    } else {
        c[w->slotCounts[0] - 14 + gCardBattleState->addedFriendCards[0]].cardId = gCardBattleState->pickedFriendCardId;
        c[w->slotCounts[0] - 14 + gCardBattleState->addedFriendCards[0]].index = gCardBattleState->addedFriendCards[0] + (w->slotCounts[0] - 14);
        c[w->slotCounts[0] - 14 + gCardBattleState->addedFriendCards[0]].unk_06 = 0;
        c[w->slotCounts[0] - 14 + gCardBattleState->addedFriendCards[0]].stocked = 0;
        c[w->slotCounts[0] - 14 + gCardBattleState->addedFriendCards[0]].removed = 0;
        c[w->slotCounts[0] - 14 + gCardBattleState->addedFriendCards[0]].used = 0;
        gCardBattleState->pickedFriendCardId = 0x3B6;
        gCardBattleState->addedFriendCards[0]++;
    }

    w->cardsLeft[0]++;
    w->cursors[0] = w->slotCounts[0] - 1;

    if (w->listIndex == 0) {
        w->cursors[0] = gSoraSelectedCard->args.index;
        node = ListPoolFirst(&w->cardDisplays[0]);

        while (node != NULL) {
            node->command = 7;
            node = ListPoolNext(&node->node);
        }

        TaskPoolUpdate(&w->tasks);
        CreateSoraCardRing(w, 0);
        z = w->listIndex;

        if (w->revCountShown[z] == 0) {
            CreateREVCOUNTTask(&w->tasks, &w->listIndex, &w->cardsLeft[z], &w->revCountShown[z], 1);
        }
    }
}

void SelectOtherSoraCard(CardBattleWork* w, u8 kind, u8 c) {
    CardDisplayWork* node;

    m4aSongNumStart(SONG_SYS_CLICKI04B);
    node = ListPoolFirst(&w->cardDisplays[kind]);

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

        node->unk_80 = gSoraCardRingAngles[node->ringIndex];
        node->timer = c;
        node->flags &= ~CARD_DISP_FLAG_SELECTED;

        if (node->ringIndex == 1) {
            gSoraSelectedCard = node;
            node->flags |= CARD_DISP_FLAG_SELECTED;
        }

        node = ListPoolNext(&node->node);
    }
}

void SelectPrevSoraCard(CardBattleWork* w, u8 b, u8 c) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    CardDisplayWork* q;
    CardSlot* slot;
    s16 prev;
    s32 v;
    s32 cur;
    u16 n;

    m4aSongNumStart(SONG_SYS_CLICKI04B);
    gSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
    prev = gSoraSelectedCard->args.index;
    p = ListPoolFirst(&w->cardDisplays[b]);

    while (p != NULL) {
        if (p->ringIndex == 0) {
            gSoraSelectedCard = p;
            break;
        }

        p = ListPoolNext(&p->node);
    }

    gSoraSelectedCard->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
    cur = (s16)gSoraSelectedCard->args.index;
    n = cur - 1;

    if ((s16)n < 0) {
        n = w->slotCounts[b] - 1;
    }

    slot = FindPrevAvailableSlot(w, b, &n);

    if (slot != NULL) {
        v = (s16)n;

        if (v != cur && v != prev) {
            args.pool = &w->cardDisplays[b];
            args.index = n;
            args.listIndex = b;
            args.slot = slot;
            args.reloadCount = w->reloadCounts[b];

            if (slot->cardId == CARD_ID_RELOAD) {
                q = TaskCreate(&w->tasks, &gTaskDescCardReload, &args)->work;
            } else {
                q = TaskCreate(&w->tasks, &gTaskDescCardSora, &args)->work;
            }

            q->unk_80 = q->unk_7C = gSoraCardRingAngles[3];
            q->swingAngleTarget = q->swingAngle = gSoraCardSwingAngles[0];
            q->ringIndex = 3;
            q->priority = 60;
            q->flags |= CARD_DISP_FLAG_VISIBLE;
        }
    }

    p = ListPoolFirst(&w->cardDisplays[b]);

    while (p != NULL) {
        p->ringIndex++;

        if (p->ringIndex > 3) {
            p->ringIndex = 0;
        }

        p->priority += 4;
        p->unk_80 = gSoraCardRingAngles[p->ringIndex];
        p->timer = c;
        p = ListPoolNext(&p->node);
    }

    gSoraSelectedCard->priority = 50;
}

void SelectNextSoraCard(CardBattleWork* w, u8 b) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    CardDisplayWork* q;
    CardSlot* c;
    s16 prev;
    s32 v;
    s32 cur;
    u16 n;

    m4aSongNumStart(SONG_SYS_CLICKI04B);
    gSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
    prev = gSoraSelectedCard->args.index;
    p = ListPoolFirst(&w->cardDisplays[b]);

    while (p != NULL) {
        if (p->ringIndex == 2) {
            gSoraSelectedCard = p;
            break;
        }

        p = ListPoolNext(&p->node);
    }

    gSoraSelectedCard->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
    cur = (s16)gSoraSelectedCard->args.index;
    n = cur + 1;

    if ((s16)n >= w->slotCounts[b]) {
        n = 0;
    }

    c = FindNextAvailableSlot(w, b, &n);

    if (c != NULL) {
        v = (s16)n;

        if (v != cur && v != prev) {
            args.pool = &w->cardDisplays[w->listIndex];
            args.index = n;
            args.listIndex = b;
            args.slot = c;
            args.reloadCount = w->reloadCounts[b];

            if (c->cardId == CARD_ID_RELOAD) {
                q = TaskCreate(&w->tasks, &gTaskDescCardReload, &args)->work;
            } else {
                q = TaskCreate(&w->tasks, &gTaskDescCardSora, &args)->work;
            }

            q->unk_80 = q->unk_7C = gSoraCardRingAngles[3];
            q->swingAngleTarget = q->swingAngle = gSoraCardSwingAngles[0];
            q->ringIndex = 3;
            q->priority = 60;
            q->flags |= CARD_DISP_FLAG_VISIBLE;
        }
    }

    p = ListPoolFirst(&w->cardDisplays[b]);

    while (p != NULL) {
        p->ringIndex--;

        if (p->ringIndex < 0) {
            p->ringIndex = 3;
        }

        p->priority += 4;
        p->unk_80 = gSoraCardRingAngles[p->ringIndex];
        p->timer = 4;
        p = ListPoolNext(&p->node);
    }

    gSoraSelectedCard->priority = 50;
}

void func_080791C0(CardBattleWork* w) {
    if (gBtlWork->flags & (BTL_FLAG_HUM_BATTLE | BTL_FLAG_VS_BATTLE)) {
        if (gRikuBtlWork->hcEffect == 0x30) {
            if (gSoraSelectedCard->value != 0) {
                gSoraSelectedCard->value -= gCardBattleState->activeValue;
            }

            gRikuBtlWork->hcEffectCount--;
        }
    }
}

void func_08079218(CardBattleWork* w) {
    u8 dmg = gCardBattleState->activeValue;
    u8 i;

    if (gBtlWork->flags & (BTL_FLAG_HUM_BATTLE | BTL_FLAG_VS_BATTLE)) {
        if (gRikuBtlWork->hcEffect == 0x30) {
            if (w->stockValue != 0) {
                for (i = 0; i < w->stockCount; i++) {
                    CardDisplayWork* c = w->stock[i];
                    s32 t;

                    if (c->value > dmg) {
                        c->value -= dmg;
                        break;
                    }

                    t = dmg - c->value;
                    c->value = 0;
                    dmg = t;
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

u16 GetNextRandomHcEffect(u16* p) {
    u16 v;
    u16 i;

    i = *p;
    v = gRandomHcEffects[i];
    *p = i + 1;

    if (*p > 46) {
        *p = 0;
    }

    return v;
}

void TrySoraCardBreak(CardBattleWork* w) {
    s8 n;
    u8 skip;
    u8 i;

#ifdef VERSION_EU
    s32 j;
    s32 k;
#endif

    if (gBtlWork->hcEffect == 1) {
        n = gSoraSelectedCard->value + 1;

        if (n > 9) {
            n = 9;
        }

        if (gSoraSelectedCard->value < 9) {
            TaskCreate(&gCardBattleState->tasks, &gTaskDescNumberPlus, &gSoraSelectedCard->cardDef);
        }

        gSoraSelectedCard->value = n;
        gSoraSelectedCard->valueModified = 1;
    } else if (gBtlWork->hcEffect == 21) {
        if (gSoraSelectedCard->value != 0) {
            n = gSoraSelectedCard->value - 1;
            gSoraSelectedCard->value--;
            gSoraSelectedCard->valueModified = 1;
        } else {
            n = 0;
            gSoraSelectedCard->valueModified = 1;
        }
    } else {
        n = gSoraSelectedCard->value;
    }

    if (gCardBattleState->activeValue > n && n != 0) {
        return;
    }

    skip = 0;

    if (gBtlWork->flags & (BTL_FLAG_HUM_BATTLE | BTL_FLAG_VS_BATTLE)) {
        if (gRikuBtlWork->hcEffect == 2 && gCardBattleState->activeCards[0]->cardDef->category == 0 &&
            gCardBattleState->rikuStockActive == 0) {
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
            gCardBattleState->rikuStockActive == 0) {
            skip = 1;
        }

        if (gRikuBtlWork->hcEffect == 29 && gCardBattleState->activeCards[0]->cardDef->category == 2 &&
            gCardBattleState->rikuStockActive == 0) {
            skip = 1;
        }
#endif
    }

    if (skip != 0) {
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
        gSoraSelectedCard->flags |= CARD_DISP_FLAG_IN_PLAY;
        func_080791C0(w);
        gCardBattleState->activeCards[0] = gSoraSelectedCard;
        gCardBattleState->activeCardCount = 1;
        gCardBattleState->activeValue = gSoraSelectedCard->value;
        gBtlWork->soraOwnsPlay = 1;

        if (!(gGameState.flags & GAME_FLAG_DARK_POINTS_LOCKED) && AddBreakDarkPoints() != 0 && !(gBtlWork->flags & BTL_FLAG_DARK_MODE)) {
            gCardBattleState->unk_0EE = 1;
        }
    } else {
        func_080791C0(w);
        gBtlWork->breakDifference = 0;
        gBtlWork->flags &= ~BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_START;
        m4aSongNumStart(SONG_SYS_DROW);
        gBtlWork->soraOwnsPlay = 1;
        gCardBattleState->activeCards[0] = gSoraSelectedCard;
        gCardBattleState->activeCardCount = 1;
        gCardBattleState->activeValue = gSoraSelectedCard->value;
    }
}

extern BtlWork* gBtlWorkAlias __asm__("gBtlWork");

s32 UseSoraCard(CardBattleWork* w) {
    CardDisplayArgs args;
    u16 id;
    CardDisplayWork* e;
    CardSlot* c;
    u8 found;
    u32 prev;
    u32 other;
    BtlWork* b;
    u64 flags;

    b = gBtlWorkAlias;
    flags = b->flags;

    if ((flags & BTL_FLAG_CARD_ACTIVE) == 0) {
        gCardBattleState->activeCards[0] = gSoraSelectedCard;

        if (b->hcEffect == 1) {
            gCardBattleState->activeValue = gSoraSelectedCard->value + 1;

            if (gSoraSelectedCard->value < 9) {
                TaskCreate(&gCardBattleState->tasks, &gTaskDescNumberPlus, &gSoraSelectedCard->cardDef);
            }

            gSoraSelectedCard->value++;

            if (gSoraSelectedCard->value > 9) {
                gSoraSelectedCard->value = 9;
            }

            if (gCardBattleState->activeValue > 9) {
                gCardBattleState->activeValue = 9;
            }

            gSoraSelectedCard->valueModified = 1;
        } else if (b->hcEffect == 21) {
            if (gSoraSelectedCard->value != 0) {
                gSoraSelectedCard->value--;
                gSoraSelectedCard->valueModified = 1;
                gCardBattleState->activeValue = gSoraSelectedCard->value;
            } else {
                gSoraSelectedCard->valueModified = 1;
                gCardBattleState->activeValue = 0;
            }
        } else {
            gCardBattleState->activeValue = gSoraSelectedCard->value;
        }

        gCardBattleState->activeCardCount = 1;
        gSoraSelectedCard->flags |= CARD_DISP_FLAG_IN_PLAY;
        gBtlWork->soraOwnsPlay = 1;
        gBtlWork->flags |= BTL_FLAG_CARD_PLAY_START;
        gBtlWork->flags |= BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags |= BTL_FLAG_PLAYER_CARD_BUSY;
    } else {
        if (b->soraOwnsPlay == 1) {
            return 1;
        }

        if ((flags & BTL_FLAG_CARD_PLAY_ENDED) == 0) {
            TrySoraCardBreak(w);
        } else {
            TrySoraCardBreak(w);
        }

        gBtlWork->flags |= BTL_FLAG_PLAYER_CARD_BUSY;
    }

    w->cardsLeft[w->listIndex]--;

    if (w->cardsLeft[w->listIndex] == 1) {
        gSoraSelectedCard->args.slot->unk_0B = 1;
    }

    if ((gSoraSelectedCard->cardDef->flags & CARD_DEF_FLAG_ITEM) && (gSoraSelectedCard->flags & CARD_DISP_FLAG_IN_PLAY)) {
        gSoraSelectedCard->args.slot->removed = 1;
    }

    if (gSoraSelectedCard->cardDef->flags & CARD_DEF_FLAG_FRIEND) {
        gSoraSelectedCard->args.slot->removed = 1;
    }

    if (gSoraSelectedCard->premium == 1) {
        gSoraSelectedCard->args.slot->removed = 1;

        if (CountRemainingAttackCards(w, 0) == 0) {
            gSoraSelectedCard->args.slot->removed = 0;
        }
    }

    w->playedCards[0] = gSoraSelectedCard;
    gSoraSelectedCard->command = 5;
    gSoraSelectedCard->priority = 50;
    gSoraSelectedCard->args.slot->used = 1;
    gSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SETTLED;
    TickSoraHcEffectOnCardUse();

    if (gBtlWork->hcEffect == 37) {
        u16 v = GetRandomHcEffect();
        func_0807B45C(w);
        gCardBattleState->soraHcEffect = v;
        func_0807B458(w, gCardBattleState->soraHcEffect);
        ApplySoraHcEffect(w);
        gBtlWork->hcEffectCount = gHcEffectDefs[gBtlWork->hcEffect].count;
    }

    other = 0xFF;
    id = other;
    found = 0;
    gSoraSelectedCard = NULL;

    e = ListPoolFirst(&w->cardDisplays[w->listIndex]);

    while (e != NULL) {
        if (e->ringIndex == 2) {
            e->ringIndex--;
            e->timer = 4;
            e->unk_80 = gSoraCardRingAngles[e->ringIndex];
            e->priority = 50;
            gSoraSelectedCard = e;
            found = 1;
            break;
        }

        e = ListPoolNext(&e->node);
    }

    if (gSoraSelectedCard == NULL) {
        e = ListPoolFirst(&w->cardDisplays[w->listIndex]);

        while (e != NULL) {
            if (e->ringIndex == 0) {
                e->ringIndex++;
                e->timer = 4;
                e->unk_80 = gSoraCardRingAngles[e->ringIndex];
                e->priority = 50;
                gSoraSelectedCard = e;
                break;
            }

            e = ListPoolNext(&e->node);
        }
    }

    if (found) {
        prev = gSoraSelectedCard->args.index;
        id = prev + 1;

        if (id >= w->slotCounts[w->listIndex]) {
            id = 0;
        }

        for (e = ListPoolFirst(&w->cardDisplays[w->listIndex]); e != NULL; e = ListPoolNext(&e->node)) {
            if (e->ringIndex == 0) {
                other = e->args.index;
                break;
            }
        }

        c = FindNextAvailableSlot(w, w->listIndex, &id);

        if (c != NULL && id != prev && id != other) {
            args.pool = &w->cardDisplays[w->listIndex];
            args.index = id;
            args.listIndex = w->listIndex;
            args.slot = c;
            args.reloadCount = w->reloadCounts[w->listIndex];

            if (c->cardId == CARD_ID_RELOAD) {
                e = TaskCreate(&w->tasks, &gTaskDescCardReload, &args)->work;
            } else {
                e = TaskCreate(&w->tasks, &gTaskDescCardSora, &args)->work;
            }

            e->unk_7C = gSoraCardRingAngles[3];
            e->swingAngleTarget = e->swingAngle = gSoraCardSwingAngles[0];
            e->ringIndex = 2;
            e->unk_80 = gSoraCardRingAngles[2];
            e->priority = 60;
            e->timer = 4;
            e->flags |= CARD_DISP_FLAG_VISIBLE;
        }
    }

    gSoraSelectedCard->flags |= CARD_DISP_FLAG_SELECTED;

    if (gBtlWork->hcEffect == 40 && (gSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD) && w->cardsLeft[w->listIndex] == 1) {
        RemoveSoraCardDisplays(w);
        gSoraSelectedCard = NULL;
        gBtlWork->flags |= BTL_FLAG_RELOADING;
        w->cardsLeft[0] = 0;
        w->reloadPending[0] = 1;
        m4aSongNumStart(SONG_SYS_CHAGEF2);

        if (FadeGetAmount() == 0) {
            FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
        }
    }

    return 1;
}

s32 UseSoraHeartlessCard(CardBattleWork* w) {
    CardDisplayArgs args;
    u16 id;
    CardDisplayWork* e;
    CardSlot* c;
    u8 found;
    u32 prev;
    u32 other;

    if (gSoraSelectedCard->flags & CARD_DISP_FLAG_NO_CARD) {
        return 1;
    }

    m4aSongNumStart(SONG_SYS_CLICKI04);

    if (gCardBattleState->soraHcEffect == 0) {
        gCardBattleState->soraHcEffect = gSoraSelectedCard->cardDef->move;
        func_0807B458(w, gCardBattleState->soraHcEffect);
        ApplySoraHcEffect(w);
    } else {
        func_0807B45C(w);
        gCardBattleState->soraHcEffect = gSoraSelectedCard->cardDef->move;
        func_0807B458(w, gCardBattleState->soraHcEffect);
        ApplySoraHcEffect(w);
        gCardBattleState->soraHcEffectReplaced = 1;
    }

    gSoraSelectedCard->args.slot->removed = 1;
    gSoraSelectedCard->command = 10;
    gSoraSelectedCard->args.slot->used = 1;
    gSoraSelectedCard->priority = 50;
    gSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SETTLED;

    if (w->stockValue != 0) {
        UpdateSpriteFrameTiles(w->tiles, gUnk_09EF12E8[0], gUnk_093FBAB8 + ((w->stockValue - 1) << 7));
        w->unk_C4[3] = 8;
    }

    w->cardsLeft[w->listIndex]--;
    other = 0xFF;
    id = other;
    found = 0;
    gSoraSelectedCard = NULL;

    e = ListPoolFirst(&w->cardDisplays[w->listIndex]);

    while (e != NULL) {
        if (e->ringIndex == 2) {
            e->ringIndex--;
            e->timer = 4;
            e->unk_80 = gSoraCardRingAngles[e->ringIndex];
            e->priority = 50;
            gSoraSelectedCard = e;
            found = 1;
            break;
        }

        e = ListPoolNext(&e->node);
    }

    if (gSoraSelectedCard == NULL) {
        e = ListPoolFirst(&w->cardDisplays[w->listIndex]);

        while (e != NULL) {
            if (e->ringIndex == 0) {
                e->ringIndex++;
                e->timer = 4;
                e->unk_80 = gSoraCardRingAngles[e->ringIndex];
                e->priority = 50;
                gSoraSelectedCard = e;
                break;
            }

            e = ListPoolNext(&e->node);
        }
    }

    if (gSoraSelectedCard == NULL) {
        args.pool = &w->cardDisplays[w->listIndex];
        args.index = 0xFFFF;
        args.slot = w->slots[w->listIndex];
        args.listIndex = w->listIndex;
        e = TaskCreate(&w->tasks, &gTaskDescCardNotHave, &args)->work;
        e->unk_80 = e->unk_7C = gSoraCardRingAngles[1];
        e->swingAngleTarget = e->swingAngle = gSoraCardSwingAngles[0];
        e->priority = 50;
        e->flags |= (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
        gSoraSelectedCard = e;
        return 0;
    }

    if (found) {
        prev = gSoraSelectedCard->args.index;
        id = prev + 1;

        if (id >= w->slotCounts[w->listIndex]) {
            id = 0;
        }

        for (e = ListPoolFirst(&w->cardDisplays[w->listIndex]); e != NULL; e = ListPoolNext(&e->node)) {
            if (e->ringIndex == 0) {
                other = e->args.index;
                break;
            }
        }

        c = FindNextAvailableSlot(w, w->listIndex, &id);

        if (c != NULL && id != prev && id != other) {
            args.pool = &w->cardDisplays[w->listIndex];
            args.index = id;
            args.listIndex = w->listIndex;
            args.slot = c;
            args.reloadCount = w->reloadCounts[w->listIndex];

            if (c->cardId == CARD_ID_RELOAD) {
                e = TaskCreate(&w->tasks, &gTaskDescCardReload, &args)->work;
            } else {
                e = TaskCreate(&w->tasks, &gTaskDescCardSora, &args)->work;
            }

            e->unk_7C = gSoraCardRingAngles[3];
            e->swingAngleTarget = e->swingAngle = gSoraCardSwingAngles[0];
            e->ringIndex = 2;
            e->unk_80 = gSoraCardRingAngles[2];
            e->priority = 60;
            e->timer = 4;
            e->flags |= CARD_DISP_FLAG_VISIBLE;
        }
    }

    gSoraSelectedCard->flags |= CARD_DISP_FLAG_SELECTED;
    return 1;
}

s32 UseSoraGimmickCard(CardBattleWork* w) {
    CardDisplayArgs args;
    u16 id;
    CardDisplayWork* e;
    CardSlot* c;
    u8 found;
    u32 prev;
    u32 other;

    if (gSoraSelectedCard->flags & CARD_DISP_FLAG_NO_CARD) {
        return 1;
    }

    gBtlWork->flags |= BTL_FLAG_GIMMICK_CARD_ACTIVE;
    m4aSongNumStart(SONG_SYS_CLICKI04);
    gSoraSelectedCard->args.slot->removed = 1;
    gSoraSelectedCard->command = 11;
    gSoraSelectedCard->args.slot->used = 1;
    gSoraSelectedCard->priority = 50;
    gSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SETTLED;
    w->cardsLeft[w->listIndex]--;
    other = 0xFF;
    id = other;
    found = 0;
    gSoraSelectedCard = NULL;

    e = ListPoolFirst(&w->cardDisplays[w->listIndex]);

    while (e != NULL) {
        if (e->ringIndex == 2) {
            e->ringIndex--;
            e->timer = 4;
            e->unk_80 = gSoraCardRingAngles[e->ringIndex];
            e->priority = 50;
            gSoraSelectedCard = e;
            found = 1;
            break;
        }

        e = ListPoolNext(&e->node);
    }

    if (gSoraSelectedCard == NULL) {
        e = ListPoolFirst(&w->cardDisplays[w->listIndex]);

        while (e != NULL) {
            if (e->ringIndex == 0) {
                e->ringIndex++;
                e->timer = 4;
                e->unk_80 = gSoraCardRingAngles[e->ringIndex];
                e->priority = 50;
                gSoraSelectedCard = e;
                break;
            }

            e = ListPoolNext(&e->node);
        }
    }

    if (found) {
        prev = gSoraSelectedCard->args.index;
        id = prev + 1;

        if (id >= w->slotCounts[w->listIndex]) {
            id = 0;
        }

        for (e = ListPoolFirst(&w->cardDisplays[w->listIndex]); e != NULL; e = ListPoolNext(&e->node)) {
            if (e->ringIndex == 0) {
                other = e->args.index;
                break;
            }
        }

        c = FindNextAvailableSlot(w, w->listIndex, &id);

        if (c != NULL && id != prev && id != other) {
            args.pool = &w->cardDisplays[w->listIndex];
            args.index = id;
            args.listIndex = w->listIndex;
            args.slot = c;
            args.reloadCount = w->reloadCounts[w->listIndex];

            if (c->cardId == CARD_ID_RELOAD) {
                e = TaskCreate(&w->tasks, &gTaskDescCardReload, &args)->work;
            } else {
                e = TaskCreate(&w->tasks, &gTaskDescCardSora, &args)->work;
            }

            e->unk_7C = gSoraCardRingAngles[3];
            e->swingAngleTarget = e->swingAngle = gSoraCardSwingAngles[0];
            e->ringIndex = 2;
            e->unk_80 = gSoraCardRingAngles[2];
            e->priority = 60;
            e->timer = 4;
            e->flags |= CARD_DISP_FLAG_VISIBLE;
        }
    }

    gSoraSelectedCard->flags |= CARD_DISP_FLAG_SELECTED;
    gCardBattleState->gimmickCardCount--;
    return 1;
}

s32 StockSoraCard(CardBattleWork* w) {
    CardDisplayArgs args;
    u16 id;
    CardDisplayWork* e;
    CardSlot* c;
    u8 found;
    u32 prev;
    u32 other;
    u8 n;
    u32 active;

    if (!(gSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED)) {
        return 1;
    }

    if ((u16)(gSoraSelectedCard->cardDef->flags & CARD_DEF_FLAG_GIMMICK)) {
        m4aSongNumStart(SONG_SYS_BEEP);
        return 1;
    }

    if (gCardBattleState->unk_0B4 == 112 || gCardBattleState->unk_0B4 == 109) {
        return 1;
    }

    w->unk_C4[1] = 0;
    gCardBattleState->soraStockNameShown = 0;
    m4aSongNumStart(SONG_SYS_KETEI2);
    gSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SETTLED;
    gSoraSelectedCard->flags |= CARD_DISP_FLAG_STOCKED;
    gSoraSelectedCard->command = 6;
    gSoraSelectedCard->stockIndex = w->stockCount;
    gSoraSelectedCard->priority = 50 - (3 - w->stockCount) * 4;
    w->stock[w->stockCount] = gSoraSelectedCard;
    gCardBattleState->unk_018[gCardBattleState->unk_0DE] = gSoraSelectedCard;
    gSoraSelectedCard->args.slot->stocked = active = 1;
    gSoraSelectedCard->args.slot->used = active;

    if (gBtlWork->hcEffect == 1) {
        n = gSoraSelectedCard->value + 1;

        if (n > 9) {
            n = 9;
        }

        gSoraSelectedCard->valueModified = active;
        gSoraSelectedCard->value = n;

        if (gSoraSelectedCard->value < 9) {
            TaskCreate(&gCardBattleState->tasks, &gTaskDescNumberPlus, &gSoraSelectedCard->cardDef);
        }
    } else if (gBtlWork->hcEffect == 21) {
        if (gSoraSelectedCard->value != 0) {
            n = gSoraSelectedCard->value - 1;
            gSoraSelectedCard->value--;
            gSoraSelectedCard->valueModified = active;
        } else {
            n = 0;
            gSoraSelectedCard->valueModified = active;
        }
    } else {
        n = gSoraSelectedCard->value;
    }

    w->stockValue += n;
    w->stockCount++;
    gCardBattleState->unk_0DE++;

    if (w->stockValue != 0) {
        UpdateSpriteFrameTiles(w->tiles, gUnk_09EF12E8[0], gUnk_093FBAB8 + ((w->stockValue - 1) << 7));
        w->unk_C4[3] = 8;
    }

    w->cardsLeft[w->listIndex]--;

    if (gSoraSelectedCard->cardDef->flags & CARD_DEF_FLAG_FRIEND) {
        gSoraSelectedCard->args.slot->removed = 1;
    }

    if (gBtlWork->hcEffect == 37) {
        u16 v = GetRandomHcEffect();
        func_0807B45C(w);
        gCardBattleState->soraHcEffect = v;
        func_0807B458(w, gCardBattleState->soraHcEffect);
        ApplySoraHcEffect(w);
        gBtlWork->hcEffectCount = gHcEffectDefs[gBtlWork->hcEffect].count;
    }

    other = 0xFF;
    id = other;
    found = 0;
    gSoraSelectedCard = NULL;

    e = ListPoolFirst(&w->cardDisplays[w->listIndex]);

    while (e != NULL) {
        if (e->ringIndex == 2) {
            e->ringIndex--;
            e->timer = 4;
            e->unk_80 = gSoraCardRingAngles[e->ringIndex];
            e->priority = 50;
            gSoraSelectedCard = e;
            found = 1;
            break;
        }

        e = ListPoolNext(&e->node);
    }

    if (gSoraSelectedCard == NULL) {
        e = ListPoolFirst(&w->cardDisplays[w->listIndex]);

        while (e != NULL) {
            if (e->ringIndex == 0) {
                e->ringIndex++;
                e->timer = 4;
                e->unk_80 = gSoraCardRingAngles[e->ringIndex];
                e->priority = 50;
                gSoraSelectedCard = e;
                break;
            }

            e = ListPoolNext(&e->node);
        }
    }

    if (found) {
        prev = gSoraSelectedCard->args.index;
        id = prev + 1;

        if (id >= w->slotCounts[w->listIndex]) {
            id = 0;
        }

        for (e = ListPoolFirst(&w->cardDisplays[w->listIndex]); e != NULL; e = ListPoolNext(&e->node)) {
            if (e->ringIndex == 0) {
                other = e->args.index;
                break;
            }
        }

        c = FindNextAvailableSlot(w, w->listIndex, &id);

        if (c != NULL && id != prev && id != other) {
            args.pool = &w->cardDisplays[w->listIndex];
            args.index = id;
            args.listIndex = w->listIndex;
            args.slot = c;
            args.reloadCount = w->reloadCounts[w->listIndex];

            if (c->cardId == CARD_ID_RELOAD) {
                e = TaskCreate(&w->tasks, &gTaskDescCardReload, &args)->work;
            } else {
                e = TaskCreate(&w->tasks, &gTaskDescCardSora, &args)->work;
            }

            e->unk_7C = gSoraCardRingAngles[3];
            e->swingAngleTarget = e->swingAngle = gSoraCardSwingAngles[0];
            e->ringIndex = 2;
            e->unk_80 = gSoraCardRingAngles[2];
            e->priority = 60;
            e->timer = 4;
            e->flags |= CARD_DISP_FLAG_VISIBLE;
        }
    }

    gSoraSelectedCard->flags |= CARD_DISP_FLAG_SELECTED;

    if (gBtlWork->hcEffect == 40 && (gSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD) && w->cardsLeft[w->listIndex] == 1) {
        RemoveSoraCardDisplays(w);
        gSoraSelectedCard = NULL;
        w->cardsLeft[0] = 0;
        w->reloadPending[0] = 1;
        m4aSongNumStart(SONG_SYS_CHAGEF2);

        if (FadeGetAmount() == 0) {
            FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
        }
    }

    return 1;
}

void RemoveSoraCardDisplays(CardBattleWork* w) {
    CardDisplayWork* node;
    u8 i;

    for (i = 0; i < 4; i++) {
        node = ListPoolFirst(&w->cardDisplays[i]);

        while (node != NULL) {
            if (node->command < 5 || node->command > 6) {
                node->command = 7;
            }

            node = ListPoolNext(&node->node);
        }
    }

    if (gSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
        gSoraSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
    }
}

void func_0807A684(CardBattleWork* w) {
    CardDisplayWork* node;
    u8 i;

    for (i = 0; i < 4; i++) {
        node = ListPoolFirst(&w->cardDisplays[i]);

        while (node != NULL) {
            if (node->command == 0) {
                node->command = 7;
            }

            node = ListPoolNext(&node->node);
        }
    }
}

void OpenSoraCards(CardBattleWork* w) {
    CardDisplayWork* node;
    u8 i;

    for (i = 0; i < w->stockCount; i++) {
        w->stock[i]->flags |= CARD_DISP_FLAG_OPEN;
    }

    for (i = 0; i < 4; i++) {
        node = ListPoolFirst(&w->cardDisplays[i]);

        while (node != NULL) {
            node->flags |= CARD_DISP_FLAG_OPEN;
            node = ListPoolNext(&node->node);
        }
    }

    gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
    gCardBattleState->cardsOpen = 1;
    w->cardsClosed = 0;
}

void CloseSoraCards(CardBattleWork* w) {
    CardDisplayWork* node;
    u8 i;

    for (i = 0; i < w->stockCount; i++) {
        w->stock[i]->flags &= ~CARD_DISP_FLAG_OPEN;
    }

    for (i = 0; i < 4; i++) {
        node = ListPoolFirst(&w->cardDisplays[i]);

        while (node != NULL) {
            node->flags &= ~CARD_DISP_FLAG_OPEN;
            node = ListPoolNext(&node->node);
        }
    }

    gCardBattleState->soraHcEffect = 0;
    gBtlWork->flags |= BTL_FLAG_CARD_PLAY_ENDED;
    gCardBattleState->cardsOpen = 0;
    gCardBattleState->soraStockNameShown = 0;
    w->cardsClosed = 1;
}

void TrySoraStockBreak(CardBattleWork* w) {
#ifdef VERSION_EU
    CardDisplayWork* previous[3];
#endif
    UnkStruct_080ABA80 arr;
    u8 flag;
    u16 total;
    u8 i;
    u8 n;
    u8 skip;
    s32 r;
    CardDisplayWork** q;
#ifdef VERSION_EU
    u8 previousCount;
    s32 j;
    s32 k;
#endif

    n = w->stockValue;
    total = 0;
    arr = gUnk_09033FD0;

    if (gCardBattleState->activeValue > n && n != 0) {
        return;
    }

    skip = 0;

    if (gBtlWork->flags & (BTL_FLAG_HUM_BATTLE | BTL_FLAG_VS_BATTLE)) {
        if (gRikuBtlWork->hcEffect == 2 && gCardBattleState->activeCards[0]->cardDef->category == 0 &&
            gCardBattleState->rikuStockActive == 0) {
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
            gCardBattleState->rikuStockActive == 0) {
            skip = 1;
        }

        if (gRikuBtlWork->hcEffect == 29 && gCardBattleState->activeCards[0]->cardDef->category == 2 &&
            gCardBattleState->rikuStockActive == 0) {
            skip = 1;
        }
#endif
    }

    if (skip != 0) {
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

        if (!(gGameState.flags & GAME_FLAG_DARK_POINTS_LOCKED) && AddBreakDarkPoints() != 0 && !(gBtlWork->flags & BTL_FLAG_DARK_MODE)) {
            gCardBattleState->unk_0EE = 1;
        }

        gBtlWork->flags |= BTL_FLAG_CARD_PLAY_START;
        gBtlWork->flags |= BTL_FLAG_PLAYER_CARD_BUSY;
        gBtlWork->flags |= BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
        func_08079218(w);

#ifndef VERSION_EU
        if (!(gBtlWork->flags & BTL_FLAG_VS_BATTLE)) {
            r = LookupStockName(w->stock, w->stockCount, w->stockValue, &arr, &flag);
        } else {
            r = LookupLinkStockName(w->stock, w->stockCount, w->stockValue, &arr, &flag, 0);
        }

        if ((u16)r == 52 && (gBtlWork->flags & (BTL_FLAG_HUM_BATTLE | BTL_FLAG_VS_BATTLE))) {
            for (i = 0; i < gCardBattleState->activeCardCount; i++) {
                if (gCardBattleState->activeCards[i]->args.slot->used == 1) {
                    gCardBattleState->activeCards[i]->args.slot->removed = 1;
                    gCardBattleState->activeCards[i]->flags |= 0x80000000;
                }
            }
        }
#endif

        for (i = 0; i < w->stockCount; i++) {
            total += w->stock[i]->value;
        }

        gCardBattleState->activeValue = total;
#ifdef VERSION_EU
        previousCount = gCardBattleState->activeCardCount;
#endif
        gCardBattleState->activeCardCount = w->stockCount;

        for (i = 0; i < w->stockCount; i++) {
#ifdef VERSION_EU
            previous[i] = gCardBattleState->activeCards[i];
#endif
            q = gCardBattleState->activeCards;
            q += i;
            *q = w->stock[i];
            w->stock[i]->flags |= CARD_DISP_FLAG_IN_PLAY;

            if (w->stock[i]->cardDef->flags & CARD_DEF_FLAG_ITEM) {
                w->stock[i]->args.slot->removed = 1;
            }
        }

        gBtlWork->soraOwnsPlay = 1;
        gCardBattleState->soraStockActive = 1;
        m4aSongNumStart(SONG_BTL_GARD);

#ifdef VERSION_EU
        if (!(gBtlWork->flags & BTL_FLAG_VS_BATTLE)) {
            r = LookupStockName(w->stock, w->stockCount, w->stockValue, &arr, &flag);
        } else {
            r = LookupLinkStockName(w->stock, w->stockCount, w->stockValue, &arr, &flag, 0);
        }

        if ((u16)r == 52 && (gBtlWork->flags & (BTL_FLAG_HUM_BATTLE | BTL_FLAG_VS_BATTLE))) {
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
    func_08079218(w);
    m4aSongNumStart(SONG_SYS_DROW);
    gBtlWork->flags &= ~BTL_FLAG_CARD_ACTIVE;
    gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
    gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_START;
    gCardBattleState->soraStockActive = 0;
    gBtlWork->soraOwnsPlay = 1;
}

void UseSoraStock(CardBattleWork* w) {
    CardDisplayWork** q;
    CardDisplayWork* p;
    u64 flags;
    u8 i;
    u8 n;

    for (i = 0, n = 0; i < w->stockCount; i++) {
        if (w->stock[i]->flags & CARD_DISP_FLAG_SETTLED) {
            n++;
        }
    }

    if (n < w->stockCount) {
        return;
    }

    gCardBattleState->unk_0C0 = 0;
    gCardBattleState->soraStockNameShown = 0;
    w->unk_C4[1] = 0;
    flags = gBtlWork->flags;

    if ((flags & BTL_FLAG_CARD_ACTIVE) == 0) {
        gCardBattleState->activeCardCount = w->stockCount;

        for (i = 0; i < w->stockCount; i++) {
            q = gCardBattleState->activeCards;
            q += i;
            *q = w->stock[i];
            w->stock[i]->priority = i * 4 + 50;

            if (w->stock[i]->cardDef->flags & CARD_DEF_FLAG_ITEM) {
                w->stock[i]->args.slot->removed = 1;
            }

            w->stock[i]->flags |= (CARD_DISP_FLAG_IN_PLAY | CARD_DISP_FLAG_UNOPPOSED);
        }

        gCardBattleState->activeValue = w->stockValue;
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
            TrySoraStockBreak(w);
            gBtlWork->flags |= BTL_FLAG_PLAYER_CARD_BUSY;
        } else {
            TrySoraStockBreak(w);
            gBtlWork->flags |= BTL_FLAG_PLAYER_CARD_BUSY;
        }
    }

    for (i = 0; i < w->stockCount; i++) {
        w->stock[i]->args.slot->stocked = 0;

        if (w->stock[i]->cardDef->flags & CARD_DEF_FLAG_ITEM) {
            w->stock[i]->args.slot->removed = 1;
        } else if (i == 0 && gBtlWork->hcEffect != 15) {
            w->stock[0]->args.slot->removed = 1;
        }
    }

    if (CountRemainingAttackCards(w, 0) == 0) {
        for (i = 0; i < w->stockCount; i++) {
            if (w->stock[i]->args.listIndex == 0) {
                w->stock[i]->args.slot->removed = 0;
                break;
            }
        }
    }

    i = 0;

    if (i < w->stockCount) {
        do {
            p = NULL;
            n = i;
            w->playedCards[n] = w->stock[n];
            w->stock[n]->command = 5;
            w->stock[n] = p;
            i = ++n;
        } while (i < w->stockCount);
    }

    TickSoraHcEffectOnCardUse();
    w->stockCount = 0;
    gCardBattleState->unk_0DE = 0;
    w->stockValue = 0;
    ClearStockedCardSlots(w);
    w->unk_C4[1] = 0;
}

void ClearStockedCardSlots(CardBattleWork* w) {
    CardSlot* c;
    u8 i;
    u8 j;

    for (i = 0; i < 4; i++) {
        c = w->slots[i];

        // @bug? Should be slotCounts[i].
        for (j = 0; j < w->slotCounts[j]; j++) {
            c[j].stocked = 0;
        }
    }
}

u8 func_0807AEC4(CardBattleWork* w, u8 n) {
    CardDisplayWork* node;
    u8 count;

    count = 0;
    node = ListPoolFirst(&w->cardDisplays[n]);

    while (node != NULL) {
        count++;
        node = ListPoolNext(&node->node);
    }

    return count;
}

u8 func_0807AEF4(CardBattleWork* w, u8 kind) {
    CardDisplayWork* node;
    u8 count;

    count = 0;
    node = ListPoolFirst(&w->cardDisplays[kind]);

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

void SwitchSoraCardList(CardBattleWork* w) {
    CardDisplayWork* node = NULL;

    if (!(gSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED)) {
        return;
    }

    m4aSongNumStart(SONG_SYS_CANSEL);

    if (gBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
        gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
    }

    w->revCountShown[w->listIndex] = 0;

    if (w->reloadPending[w->listIndex] == 0) {
        w->cursors[w->listIndex] = gSoraSelectedCard->args.index;
        node = ListPoolFirst(&w->cardDisplays[w->listIndex]);

        while (node != NULL) {
            node->swingSteps = 4;
            node->swingAngleTarget = gSoraCardSwingAngles[3];
            node->command = 7;
            node->flags &= ~CARD_DISP_FLAG_SELECTED;
            node = ListPoolNext(&node->node);
        }
    } else {
        w->selectedCards[w->listIndex] = gSoraSelectedCard;
        gSoraSelectedCard->swingAngleTarget = gSoraCardSwingAngles[3];
        gSoraSelectedCard->swingSteps = 4;
        gSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
    }

    switch (w->listIndex) {
    case 0:
        w->listIndex = 3;
        break;
    case 3:
        w->listIndex = 0;
        break;
    }

    if (w->reloadPending[w->listIndex] == 0) {
        CreateSoraCardRing(w, w->listIndex);
        node = ListPoolFirst(&w->cardDisplays[w->listIndex]);

        while (node != NULL) {
            node->swingAngleTarget = gSoraCardSwingAngles[0];
            node->swingAngle = gSoraCardSwingAngles[0];
            node->swingSteps = 1;
            node->timer = 1;
            node = ListPoolNext(&node->node);
        }

        if (w->revCountShown[w->listIndex] == 0) {
            if (w->listIndex != 0) {
                if (w->cardsLeft[w->listIndex] > 0) {
                    CreateREVCOUNTTask(&w->tasks, &w->listIndex, &w->cardsLeft[w->listIndex], &w->revCountShown[w->listIndex], 1);
                }
            } else {
                if (w->cardsLeft[w->listIndex] > 1) {
                    CreateREVCOUNTTask(&w->tasks, &w->listIndex, &w->cardsLeft[w->listIndex], &w->revCountShown[w->listIndex], 1);
                }
            }
        }
    } else {
        gSoraSelectedCard = w->selectedCards[w->listIndex];
        gSoraSelectedCard->swingAngleTarget = gSoraCardSwingAngles[0];
        gSoraSelectedCard->swingAngle = gSoraCardSwingAngles[1];
        gSoraSelectedCard->swingSteps = 1;
        gSoraSelectedCard->timer = 1;
        gSoraSelectedCard->flags |= CARD_DISP_FLAG_SELECTED;
    }

    gCardBattleState->soraListIndex = w->listIndex;
}

void CycleSoraCardList(CardBattleWork* w) {
    CardDisplayWork* node = NULL;

    m4aSongNumStart(SONG_SYS_CANSEL);

    if (gBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
        gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
    }

    w->revCountShown[w->listIndex] = 0;

    if (w->reloadPending[w->listIndex] == 0) {
        w->cursors[w->listIndex] = gSoraSelectedCard->args.index;
        node = ListPoolFirst(&w->cardDisplays[w->listIndex]);

        while (node != NULL) {
            node->swingSteps = 12;
            node->swingAngleTarget = gSoraCardSwingAngles[1];
            node->command = 7;
            node = ListPoolNext(&node->node);
        }
    } else {
        w->selectedCards[w->listIndex] = gSoraSelectedCard;
        gSoraSelectedCard->swingAngleTarget = gSoraCardSwingAngles[3];
        gSoraSelectedCard->swingSteps = 12;
        gSoraSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
    }

    switch (w->listIndex) {
    case 0:
        w->listIndex = 2;
        break;
    case 1:
        w->listIndex = 0;
        break;
    case 2:
        w->listIndex = 3;
        break;
    case 3:
        w->listIndex = 1;
        break;
    }

    if (w->reloadPending[w->listIndex] == 0) {
        CreateSoraCardRing(w, w->listIndex);
        node = ListPoolFirst(&w->cardDisplays[w->listIndex]);

        while (node != NULL) {
            node->swingSteps = 12;
            node->swingAngleTarget = gSoraCardSwingAngles[0];
            node->swingAngle = gSoraCardSwingAngles[0];
            node->timer = 12;
            node = ListPoolNext(&node->node);
        }

        if (w->revCountShown[w->listIndex] == 0 && w->cardsLeft[w->listIndex] > 0) {
            CreateREVCOUNTTask(&w->tasks, &w->listIndex, &w->cardsLeft[w->listIndex], &w->revCountShown[w->listIndex], 1);
        }
    } else {
        gSoraSelectedCard = w->selectedCards[w->listIndex];
        gSoraSelectedCard->swingAngleTarget = gSoraCardSwingAngles[0];
        gSoraSelectedCard->swingAngle = gSoraCardSwingAngles[1];
        gSoraSelectedCard->swingSteps = 12;
        gSoraSelectedCard->timer = 12;
        gSoraSelectedCard->flags |= CARD_DISP_FLAG_SELECTED;
    }

    gCardBattleState->soraListIndex = w->listIndex;
}

void IncrementReloadCount(CardBattleWork* w) {
    s16* c;

    switch (w->listIndex) {
    case 0:
        w->reloadCounts[0]++;
        break;
    case 1:
        w->reloadCounts[1]++;
        break;
    case 2:
        break;
    }

    c = &w->reloadCounts[0];
    c += w->listIndex;

    if (*c > 2) {
        *c = 2;
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
    BtlObj* t;
    u32 v;

    t = ListPoolFirst(&gBtlWork->pool);

    while (t != NULL) {
        v = t->kind;

        switch (v) {
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
            TaskCreate(pool, &gTaskDescBosscard, &v);
            return;
        }

        t = ListPoolNext(&t->node);
    }
}

void func_0807B458(CardBattleWork* w, u16 value) {
}

void func_0807B45C(CardBattleWork* w) {
    gBtlWork->hcEffect = gCardBattleState->soraHcEffect;
}

void ApplySoraHcEffect(CardBattleWork* w) {
    u32* p;
    u16* c;
    s16* q;
    s16* q2;

    if (gBtlWork->flags & (BTL_FLAG_HUM_BATTLE | BTL_FLAG_VS_BATTLE)) {
        if (gRikuBtlWork->hcEffect != 41) {
            gBtlWork->hcEffect = gCardBattleState->soraHcEffect;
        } else {
            gBtlWork->hcEffect = 0;
            gCardBattleState->soraHcEffect = 0;
        }

        p = &gBtlWork->hcEffect;

        if (*p == 41) {
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

        c = &gCardBattleState->soraHcEffect;

        if (*c == 45) {
            if (gRikuBtlWork->hcEffect != 0) {
                gBtlWork->hcEffect = gRikuBtlWork->hcEffect;
                gCardBattleState->soraHcEffect = gCardBattleState->rikuHcEffect;
            } else {
                gBtlWork->hcEffect = 0;
                gCardBattleState->rikuHcEffect = 0;
            }
        }

        if (gBtlWork->hcEffect == 47) {
            q2 = &w->reloadCounts[0];
            q = q2;
            *q++ = 2;
            *q = 2;
        }
    } else {
        if (gCardBattleState->soraHcEffect != 41 && gCardBattleState->soraHcEffect != 45) {
            gBtlWork->hcEffect = gCardBattleState->soraHcEffect;
        } else {
            gBtlWork->hcEffect = 0;
        }
    }
}

u8 func_0807B578(CardBattleWork* w, void* a) {
    s16 v;

    v = w->cardsLeft[w->listIndex];

    if (v > 2) {
        if (gSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED) {
            SelectPrevSoraCard(w, w->listIndex, 2);
        }
    } else if (v > 1) {
        if (gSoraSelectedCard->flags & CARD_DISP_FLAG_SETTLED) {
            SelectOtherSoraCard(w, w->listIndex, 2);
        }
    }

    w->timer--;

    if (w->timer <= 0) {
        SetTaskUpdate(a, (TaskUpdateFunc)cardbattleSora_1);
    }

    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&gCardBattleState->tasks);
    return 1;
}

u8 CanUseSoraSelectedCard() {
    if (gBtlWork->hcEffect == 38) {
        if (gSoraSelectedCard->cardDef->category != 1) {
            return 1;
        }

        if (!(gSoraSelectedCard->cardDef->flags & CARD_DEF_FLAG_SUMMON)) {
            return 1;
        }

        return 0;
    } else if (gBtlWork->hcEffect == 39) {
        if (gSoraSelectedCard->cardDef->category != 1) {
            return 1;
        }

        if (gSoraSelectedCard->cardDef->flags & CARD_DEF_FLAG_SUMMON) {
            return 1;
        }

        return 0;
    }

    return 1;
}

void LoadPremiumCardGfx(CardBattleState* p) {
    p->premiumTiles = AllocObjTiles(0x280, NULL);
    SetObjTileSource(p->premiumTiles, gUnk_0908B1B4);
    AnimInit(&p->anim, gUnk_09EEA164, gUnk_09EEA148);
    AnimStart(&p->anim, 0, ANIM_FLAG_LOOP);
    p->gfx = AnimGetGfx(&p->anim);
    p->premiumTiles2 = AllocObjTiles(0x100, NULL);
    SetObjTileSource(p->premiumTiles2, gUnk_0908C3CE);
    AnimInit(&p->anim2, gUnk_09EEA198, gUnk_09EEA180);
    AnimStart(&p->anim2, 0, ANIM_FLAG_LOOP);
    p->gfx2 = AnimGetGfx(&p->anim2);
}

void ResetSoraReloadGauge(CardBattleWork* w) {
    CardBattleState* p;

    p = gCardBattleState;
    p->soraReloadGauge = 0;
    p->soraReloadCounter = 0;
    p->soraGaugeFullFrame = 4;
    p->soraGaugeAnim = 2;
    p->reloadGaugeFull[0] = 0;
}

void RestoreCardsForPotion(CardBattleWork* w) {
    CardSlot* c;
    s32 i;
    u32 id;
    u8 t;

    c = w->slots[0];

    for (i = 0; i < w->slotCounts[0]; i++) {
        id = c[i].cardId;

        if (id != 0xFFFF) {
            if (id != 0xFFFE) {
                t = gCardDefs[id & CARD_ID_MASK].category;

                if (t == 0) {
                    if (c[i].removed == 0) {
                        c[i].unk_06 = 0;
                    }
                } else if (t == 1) {
                    if (c[i].removed == 1 || c[i].stocked == 1 || c[i].used == 1) {
                        c[i].unk_06 = 1;
                    }
                }
            }
        }
    }
}

void RestoreCardsForHiPotion(CardBattleWork* w) {
    CardSlot* c;
    s32 i;
    u32 id;
    u8 t;

    c = w->slots[0];

    for (i = 0; i < w->slotCounts[0]; i++) {
        id = c[i].cardId;

        if (id != 0xFFFF) {
            if (id != 0xFFFE) {
                t = gCardDefs[id & CARD_ID_MASK].category;

                if (t == 0) {
                    c[i].removed = 0;
                    c[i].unk_06 = 0;
                } else if (t != 2) {
                    if (c[i].used == 1 || c[i].removed == 1 || c[i].stocked == 1) {
                        c[i].unk_06 = 1;
                    }
                }
            }
        }
    }
}

void RestoreCardsForMegaPotion(CardBattleWork* w) {
    CardSlot* c;
    s32 i;
    u32 id;
    u8 t;

    c = w->slots[0];

    for (i = 0; i < w->slotCounts[0]; i++) {
        id = c[i].cardId;

        if (id != 0xFFFF) {
            if (id != 0xFFFE) {
                t = gCardDefs[id & CARD_ID_MASK].category;

                if (t == 0) {
                    c[i].unk_06 = 0;
                    c[i].removed = 0;
                } else if (t != 2) {
                    if (c[i].used == 1 || c[i].removed == 1 || c[i].stocked == 1) {
                        c[i].unk_06 = 1;
                    }
                }
            }
        }
    }
}

void RestoreCardsForEther(CardBattleWork* w) {
    CardSlot* c;
    s32 i;
    u32 id;
    u8 t;

    c = w->slots[0];

    for (i = 0; i < w->slotCounts[0]; i++) {
        id = c[i].cardId;

        if (id != 0xFFFF) {
            if (id != 0xFFFE) {
                t = gCardDefs[id & CARD_ID_MASK].category;

                if (t == 1) {
                    if (c[i].removed == 0) {
                        c[i].unk_06 = 0;
                    }
                } else if (t != 2) {
                    if (c[i].removed == 1 || c[i].stocked == 1 || c[i].used == 1) {
                        c[i].unk_06 = 1;
                    }
                }
            }
        }
    }
}

void RestoreCardsForMegaEther(CardBattleWork* w) {
    CardSlot* c;
    s32 i;
    u32 id;
    u8 t;

    c = w->slots[0];

    for (i = 0; i < w->slotCounts[0]; i++) {
        id = c[i].cardId;

        if (id != 0xFFFF) {
            if (id != 0xFFFE) {
                t = gCardDefs[id & CARD_ID_MASK].category;

                if (t == 1) {
                    c[i].unk_06 = 0;
                    c[i].removed = 0;
                } else if (t != 2) {
                    if (c[i].used == 1 || c[i].removed == 1 || c[i].stocked == 1) {
                        c[i].unk_06 = 1;
                    }
                }
            }
        }
    }
}

void RestoreCardsForElixir(CardBattleWork* w) {
    CardSlot* c;
    s32 i;

    c = w->slots[0];

    for (i = 0; i < w->slotCounts[0]; i++) {
        if (c[i].cardId != CARD_ID_NONE) {
            if (c[i].cardId != CARD_ID_RELOAD) {
                if (gCardDefs[c[i].cardId & CARD_ID_MASK].category != 2) {
                    c[i].unk_06 = 0;
                    c[i].removed = 0;
                }
            }
        }
    }
}

void RemoveItemCards(CardBattleWork* w) {
    CardSlot* c;
    s32 i;

    c = w->slots[0];

    for (i = 0; i < w->slotCounts[0]; i++) {
        if (c[i].cardId != CARD_ID_NONE) {
            if (c[i].cardId != CARD_ID_RELOAD) {
                if (gCardDefs[c[i].cardId & CARD_ID_MASK].flags & CARD_DEF_FLAG_ITEM) {
                    if (c[i].removed == 0) {
                        c[i].restoreOnReload = 1;
                    }

                    c[i].removed = 1;
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

void SoraCardInit(CardDisplayWork* p, CardDisplayArgs* a) {
    u16 v;

    CpuFill32(0, p, sizeof(CardDisplayWork));
    p->tiles = NULL;
    p->tiles2 = NULL;
    p->tiles3 = NULL;
    p->tiles4 = NULL;
    p->tiles5 = NULL;
    p->palette2 = NULL;
    p->palette = NULL;
    p->children = NULL;
    p->args = *a;
    p->flags = 0;
    v = p->args.index;

    if ((s16)v != -1) {
        LookupSoraCardDef(&p->args, &p->cardDef, v);

        if (p->args.slot->cardId == CARD_ID_RELOAD) {
            p->flags |= CARD_DISP_FLAG_RELOAD_CARD;
        }
    } else {
        p->flags = CARD_DISP_FLAG_NO_CARD;
    }

    // @bug A "not have" display has no slot (NULL read).
    if (p->args.slot->cardId & 0x8000) {
        p->premium = 1;
    } else {
        p->premium = 0;
    }

    p->scaleX = 0x100;
    p->scaleY = 0x100;
    p->bobAngle = 0;
    p->angle = 0;
    p->unk_7C = 0;
    p->unk_80 = 0;
    p->unk_84 = 0;
    p->unk_88 = 0;
    p->swingAngle = 0;
    p->swingAngleTarget = 0;
    p->command = 0;
    p->priority = 60;
    p->timer = 4;
    p->unk_A2 = 0;
    p->unk_84 = 0;
    p->unk_88 = 0x2400;
    p->swingSteps = 0;
    p->unk_8C = gSoraCardLayout[0][0];
    p->unk_90 = gSoraCardLayout[0][1];
    p->x = gSoraCardLayout[4][0];
    p->y = gSoraCardLayout[4][1];

    if (p->cardDef != NULL) {
        p->value = p->cardDef->value;
    } else {
        p->value = 0;
    }

    p->valueModified = 0;
    p->flags |= CARD_DISP_FLAG_OPEN;
    p->flags &= ~CARD_DISP_FLAG_SETTLED;
    LinkSoraCardDisplay(p);
}

u8 SoraCardUpdate(CardDisplayWork* p, void* a) {
    u8 (*fn)(CardDisplayWork*, void*);

    if (p->flags & CARD_DISP_FLAG_DEALING) {
        if (!(p->flags & CARD_DISP_FLAG_GFX_LOADED)) {
            LoadCardDisplayGfx(p);
            p->flags |= CARD_DISP_FLAG_GFX_LOADED;
        }

        if (p->flags & CARD_DISP_FLAG_DEALING) {
            p->timer = 8;
            UpdateSoraCardValue(p);
            SetTaskUpdate(a, (TaskUpdateFunc)func_0807CB24);
            return 1;
        }
    }

    if ((s16)p->timer == 0) {
        if (IsCardDisplayOffScreen(p)) {
            ListPoolRemove(&p->node, p->args.pool);
            return 0;
        }

        if (!(p->flags & CARD_DISP_FLAG_GFX_LOADED)) {
            LoadCardDisplayGfx(p);
            p->flags |= CARD_DISP_FLAG_GFX_LOADED;
            fn = func_0807BE54;
            SetTaskUpdate(a, (TaskUpdateFunc)fn);
            return fn(p, a);
        }
    }

    if (p->flags & CARD_DISP_FLAG_FROZEN) {
        return 1;
    }

    if (!(p->flags & CARD_DISP_FLAG_OPEN)) {
        p->flags &= ~CARD_DISP_FLAG_SETTLED;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807CBC0);
    }

    UpdateSoraCardRingPosition(p);
    p->bobAngle += 4;
    return DispatchSoraCardCommand(p, a);
}

u8 func_0807BE54(CardDisplayWork* p, void* a) {
    if (IsCardDisplayOffScreen(p)) {
        ListPoolRemove(&p->node, p->args.pool);
        return 0;
    }

    if (p->flags & CARD_DISP_FLAG_FROZEN) {
        return 1;
    }

    if (!(p->flags & CARD_DISP_FLAG_OPEN)) {
        p->flags &= ~CARD_DISP_FLAG_SETTLED;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807CBC0);
    }

    UpdateSoraCardRingPosition(p);
    p->bobAngle += 4;
    return DispatchSoraCardCommand(p, a);
}

static void card_2(CardDisplayWork* p) {
    s16 y;
    void* gfx;
    ObjAffine* aff;
    u8 j;
    u8 k;
    u16 attr;

    attr = 0x410;

    if (IsMessageWindowOpen() == 1) {
        y = p->y >> 8;
    } else {
        y = (p->y >> 8) + (gSineTable[p->bobAngle] >> 8);
    }

    gfx = p->cardDef->gfx;

    if (!(p->flags & CARD_DISP_FLAG_VISIBLE)) {
        return;
    }

    if (!(p->flags & CARD_DISP_FLAG_GFX_LOADED)) {
        return;
    }

    if (!(p->flags & CARD_DISP_FLAG_STOCKED)) {
        aff = AllocObjAffine(p->angle, p->scaleX, p->scaleY, 0);
        DrawSprite(p->x >> 8, y, gCardBacks[p->cardDef->category].gfx, gCardBattleState->tiles[p->cardDef->category], gCardBattleState->palette, aff, attr, p->priority - 1);
        DrawSprite(p->x >> 8, y, gfx, p->tiles, p->palette, aff, attr, p->priority);
        j = p->value;

        if (p->cardDef->category == 3) {
            return;
        }

        if (p->valueModified != 0) {
            DrawSprite(p->x >> 8, y, gUnk_09EE98C0[j], gCardBattleState->tiles7, gCardBattleState->palette2, aff, attr, p->priority - 2);
        } else if (p->premium != 0) {
            DrawSprite(p->x >> 8, y, gUnk_09EE9894[j], gCardBattleState->tiles6, gCardBattleState->palette2, aff, attr, p->priority - 2);
        } else {
            DrawSprite(p->x >> 8, y, gUnk_09EE981C[j], gCardBattleState->tiles5, gCardBattleState->palette, aff, attr, p->priority - 2);
        }

        if (p->premium != 0) {
            DrawSprite(p->x >> 8, y, gCardBattleState->gfx, gCardBattleState->premiumTiles, gCardBattleState->palette, aff, attr, p->priority - 3);
        }

        return;
    }

    aff = AllocObjAffine(0, p->scaleX, p->scaleY, 0);
    DrawSprite(p->x >> 8, y, p->cardDef->gfx2, p->tiles, p->palette, aff, attr, p->priority);
    k = p->value;

    if (p->cardDef->category == 3) {
        return;
    }

    if (p->valueModified != 0) {
        DrawSprite((p->x >> 8) - 3, y - 4, gUnk_09EE981C[k], gCardBattleState->tiles7, gCardBattleState->palette2, aff, attr, p->priority - 10);

        if (p->premium != 0) {
            DrawSprite(p->x >> 8, y, gCardBattleState->gfx2, gCardBattleState->premiumTiles2, gCardBattleState->palette, aff, attr, p->priority - 11);
        }
    } else if (p->premium != 0) {
        DrawSprite((p->x >> 8) - 3, y - 4, gUnk_09EE981C[k], gCardBattleState->tiles6, gCardBattleState->palette2, aff, attr, p->priority - 10);
        DrawSprite(p->x >> 8, y, gCardBattleState->gfx2, gCardBattleState->premiumTiles2, gCardBattleState->palette, aff, attr, p->priority - 11);
    } else {
        DrawSprite((p->x >> 8) - 3, y - 4, gUnk_09EE981C[k], gCardBattleState->tiles5, gCardBattleState->palette, aff, attr, p->priority - 10);
    }
}

void card_not_have_2(CardDisplayWork* p) {
    void* gfx;
    u16 y;

    gfx = gCardBacks[p->args.listIndex].gfx2;

    if (IsMessageWindowOpen() == 1) {
        y = p->y >> 8;
    } else {
        y = (p->y >> 8) + (gSineTable[p->bobAngle] >> 8);
    }

    if (p->flags & CARD_DISP_FLAG_GFX_LOADED) {
        DrawSprite(p->x >> 8, y, gfx, p->tiles2, gCardBattleState->palette, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, p->priority - 1);
    }
}

void SoraCardDestroy(CardDisplayWork* p) {
    ReleaseCardDisplayGfx(p);
}

void SyncCardDisplayGfx(CardDisplayWork* p) {
    if (p->command != 6) {
        if (IsCardDisplayOffScreen(p) != 0) {
            if (p->flags & CARD_DISP_FLAG_GFX_LOADED) {
                ReleaseCardDisplayGfx(p);
                p->flags &= ~CARD_DISP_FLAG_GFX_LOADED;
            }
        } else {
            if (!(p->flags & CARD_DISP_FLAG_GFX_LOADED)) {
                LoadCardDisplayGfx(p);
                p->flags |= CARD_DISP_FLAG_GFX_LOADED;
            }
        }
    }
}

void LoadCardDisplayGfx(CardDisplayWork* p) {
    CardDef* d;
    void* tiles;
    void* pal;
    u32 f;

    f = p->flags & CARD_DISP_FLAG_NO_CARD;

    if (f != 0) {
        p->tiles = NULL;
        p->palette = NULL;
        p->palette2 = NULL;
        p->tiles2 = LoadObjTiles(gCardBacks[p->args.listIndex].tiles2, 640);
    } else {
        d = p->cardDef;
        tiles = d->tiles;
        pal = d->palette;
        p->tiles = LoadObjTiles(tiles, 512);
        p->palette = LoadObjPalette(pal, 32);
        p->tiles2 = NULL;
    }
}

void ReleaseCardDisplayGfx(CardDisplayWork* p) {
    if (p->tiles != NULL) {
        ReleaseObjTiles(p->tiles);
    }

    if (p->palette != NULL) {
        ReleaseObjPalette(p->palette);
    }

    if (p->tiles2 != NULL) {
        ReleaseObjTiles(p->tiles2);
    }

    if (p->tiles3 != NULL) {
        ReleaseObjTiles(p->tiles3);
    }

    if (p->tiles4 != NULL) {
        ReleaseObjTiles(p->tiles4);
    }

    p->tiles = NULL;
    p->palette = NULL;
    p->palette2 = NULL;
    p->tiles2 = NULL;
    p->tiles3 = NULL;
    p->tiles4 = NULL;
}

u8 func_0807C3E8(CardDisplayWork* p, void* a) {
    if (gBtlWork->flags & BTL_FLAG_CARD_PLAY_ENDED) {
        p->timer = 8;
        p->unk_9E = 8;
        gCardBattleState->activeCardCount = 0;
        gCardBattleState->activeValue = 0;
        gBtlWork->flags &= ~BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
        gBtlWork->flags &= ~BTL_FLAG_PLAYER_CARD_BUSY;

        if (p->cardDef->category == 0) {
            TickSoraHcEffectOnAttackEnd();
        }

        SetTaskUpdate(a, (TaskUpdateFunc)func_0807CE04);
    } else if (p->flags & CARD_DISP_FLAG_BROKEN) {
        p->priority -= 4;
        p->unk_84 = 0x500;
        p->timer = 0x100;
        p->unk_7C = -16;
        p->unk_9E = 0xFF;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807D3A0);
    }

    return 1;
}

u8 func_0807C4BC(CardDisplayWork* p, void* a) {
    ApproachValue(&p->x, 0x7800, p->timer);
    ApproachValue(&p->y, 0x8400, p->timer);

    if ((s16)p->timer > 0) {
        p->timer--;
    } else {
        p->timer |= 0xFFFF;
    }

    if (gBtlWork->flags & BTL_FLAG_CARD_ACTIVE) {
        if (p->flags & CARD_DISP_FLAG_IN_PLAY) {
            if ((s16)p->timer == 0) {
                SetTaskUpdate(a, (TaskUpdateFunc)func_0807C3E8);
            }
        } else if ((s16)p->timer <= 2) {
            p->priority -= 4;
            p->unk_84 = 0x500;
            p->timer = 0x100;
            p->unk_7C = -16;
            p->unk_9E = 0xFF;
            p->flags |= CARD_DISP_FLAG_IN_PLAY;
            SetTaskUpdate(a, (TaskUpdateFunc)func_0807CE9C);

            if (p->cardDef->flags & CARD_DEF_FLAG_ITEM) {
                p->args.slot->unk_06 = 0;
            }

            m4aSongNumStart(SONG_SYS_DROW);
        }
    } else if ((s16)p->timer <= 2) {
        p->priority -= 4;
        p->unk_84 = 0x500;
        p->timer = 0x100;
        p->unk_7C = -16;
        p->unk_9E = 0xFF;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807CE9C);
    }

    return 1;
}

u8 func_0807C5D8(CardDisplayWork* w, void* a) {
    ApproachValue(&w->unk_8C, gPlayedCardCenter[0], w->timer);
    ApproachValue(&w->unk_90, gPlayedCardCenter[1], w->timer);
    ApproachValue(&w->unk_84, w->unk_88, w->timer);
    ApproachValue(&w->scaleX, 0x100, w->timer);
    ApproachValue(&w->scaleY, 0x100, w->timer);

    if ((s16)w->timer > 0) {
        w->timer--;
    } else {
        w->timer = 0;
    }

    func_0807D0F4(w);

    switch (w->stockIndex) {
    case 0:
        w->priority = 50;
        break;
    case 1:
        w->priority = 40;
        break;
    case 2:
        w->priority = 60;
        break;
    }

    if (w->flags & CARD_DISP_FLAG_BROKEN) {
        w->priority -= 4;
        w->unk_84 = 0x500;
        w->timer = 0x100;
        w->unk_7C = -16;
        w->unk_9E = 0xFF;
        gCardBattleState->soraStockActive = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807D3A0);
    }

    if (gBtlWork->flags & BTL_FLAG_CARD_PLAY_ENDED) {
        w->timer = 8;
        w->unk_9E = 8;
        gCardBattleState->activeCardCount--;
        gCardBattleState->activeValue = 0;

        if (gCardBattleState->activeCardCount == 0) {
            gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
            gBtlWork->flags &= ~BTL_FLAG_CARD_ACTIVE;
            TickSoraHcEffectOnPlayEnd();
        }

        gCardBattleState->soraStockActive = 0;
        gBtlWork->flags &= ~BTL_FLAG_PLAYER_CARD_BUSY;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807CE04);
    }

    return 1;
}

u8 func_0807C75C(CardDisplayWork* p, void* a) {
    u8 (*fn)(CardDisplayWork*, void*);

    SyncCardDisplayGfx(p);

    if (!(p->flags & CARD_DISP_FLAG_STOCK_NAMED)) {
        fn = func_0807C934;
        SetTaskUpdate(a, (TaskUpdateFunc)fn);
        return fn(p, a);
    }

    if (p->flags & 0x40000000) {
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807D810);
        return 1;
    }

    if (p->command == 5) {
        if (p->flags & CARD_DISP_FLAG_UNOPPOSED) {
            p->timer = 15;
            p->unk_88 = 0x800;
            p->unk_84 = 0;
            p->unk_80 = gPlayedCardAngles[p->stockIndex] * 2;
            p->unk_7C = 0;
            p->unk_8C = p->x;
            p->unk_90 = p->y;
            fn = func_0807C5D8;
        } else {
            p->timer = 15;
            p->unk_88 = 0x800;
            p->unk_84 = 0;
            p->unk_80 = gPlayedCardAngles[p->stockIndex] * 2;
            p->unk_7C = 0;
            p->unk_8C = p->x;
            p->unk_90 = p->y;
            p->priority += p->stockIndex * 3;
            fn = func_0807CFA8;
        }

        SetTaskUpdate(a, (TaskUpdateFunc)fn);
        p->flags &= ~CARD_DISP_FLAG_STOCKED;
        RefreshSoraCardDisplayGfx(p);
        return fn(p, a);
    }

    if ((s16)p->timer > 0) {
        p->timer--;
        return 1;
    }

    if (p->flags & CARD_DISP_FLAG_OPEN) {
        switch (p->unk_A2) {
        case 0:
            p->y -= 0x80;

            if (p->y <= gSoraCardLayout[3 - p->stockIndex][1] - 0x200) {
                p->y = gSoraCardLayout[3 - p->stockIndex][1] - 0x200;
                p->unk_A2 = 1;
            }

            break;
        case 1:
            p->y += 0x200;

            if (p->y >= gSoraCardLayout[3 - p->stockIndex][1]) {
                p->y = gSoraCardLayout[3 - p->stockIndex][1];
                p->unk_A2 = 0;
                p->timer = 16;
            }

            break;
        }
    } else {
        ApproachValue(&p->x, gSoraCardLayout[4][0], p->timer);
        ApproachValue(&p->y, gSoraCardLayout[4][1], p->timer);
    }

    p->bobAngle += 4;
    return 1;
}

u8 func_0807C934(CardDisplayWork* p, void* a) {
    u8 (*fn)(CardDisplayWork*, void*);
    u16 t;

    if (gBtlWork->paused == 1) {
        return 1;
    }

    SyncCardDisplayGfx(p);

    if (p->flags & CARD_DISP_FLAG_OPEN) {
        ApproachValue(&p->x, gSoraCardLayout[3 - p->stockIndex][0], p->timer);
        ApproachValue(&p->scaleY, 179, p->timer);
        ApproachValue(&p->y, gSoraCardLayout[3 - p->stockIndex][1], p->timer);
        ApproachValue(&p->scaleX, 179, p->timer);
    } else {
        ApproachValue(&p->x, gSoraCardLayout[4][0], p->timer);
        ApproachValue(&p->y, gSoraCardLayout[4][1], p->timer);
    }

    t = p->timer;

    if ((s16)t > 0) {
        p->timer = t - 1;
        p->flags &= ~CARD_DISP_FLAG_SETTLED;
    } else {
        p->timer = 0;
        p->scaleX = 0x100;
        p->scaleY = 0x100;
        p->flags |= CARD_DISP_FLAG_SETTLED;

        if (p->flags & CARD_DISP_FLAG_STOCK_NAMED) {
            p->timer = p->stockIndex * 8;
            fn = func_0807C75C;
            SetTaskUpdate(a, (TaskUpdateFunc)fn);
            return fn(p, a);
        }
    }

    if (p->flags & 0x40000000) {
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807D810);
        return 1;
    }

    if (p->command == 5) {
        if (p->flags & CARD_DISP_FLAG_UNOPPOSED) {
            p->timer = 15;
            p->unk_88 = 0x800;
            p->unk_84 = 0;
            p->unk_80 = gPlayedCardAngles[p->stockIndex] * 2;
            p->unk_7C = 0;
            p->unk_8C = p->x;
            p->unk_90 = p->y;
            fn = func_0807C5D8;
        } else {
            p->timer = 15;
            p->unk_88 = 0x800;
            p->unk_84 = 0;
            p->unk_80 = gPlayedCardAngles[p->stockIndex] * 2;
            p->unk_7C = 0;
            p->unk_8C = p->x;
            p->unk_90 = p->y;
            fn = func_0807CFA8;
        }

        SetTaskUpdate(a, (TaskUpdateFunc)fn);
        p->flags &= ~CARD_DISP_FLAG_STOCKED;
        RefreshSoraCardDisplayGfx(p);
        return fn(p, a);
    }

    p->bobAngle += 4;
    return 1;
}

u8 func_0807CB24(CardDisplayWork* p, void* a) {
    if (!(p->flags & CARD_DISP_FLAG_OPEN)) {
        if (p->flags & CARD_DISP_FLAG_RELOAD_CARD) {
            SetTaskUpdate(a, (TaskUpdateFunc)func_0807D930);
            return func_0807D930(p, a);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)func_0807CBC0);
            return func_0807CBC0(p, a);
        }
    }

    UpdateSoraCardRingPosition(p);
    p->timer--;

    if (p->timer == 0) {
        p->flags &= ~CARD_DISP_FLAG_DEALING;

        if (p->flags & CARD_DISP_FLAG_RELOAD_CARD) {
            gCardBattleState->soraReloadCharging = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)card_reload_1);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)SoraCardUpdate);
        }
    }

    return 1;
}

u8 func_0807CBC0(CardDisplayWork* p, void* a) {
    u8 (*f)(CardDisplayWork*, void*);

    if (p->command == 7) {
        return 0;
    }

    p->unk_84 += (0 - p->unk_84) >> 1;
    p->x += (gSoraCardLayout[4][0] - p->x) >> 1;
    p->y += (gSoraCardLayout[4][1] - p->y) >> 1;

    if (p->flags & CARD_DISP_FLAG_OPEN) {
        f = SoraCardUpdate;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        return f(p, a);
    }

    return 1;
}

void UpdateSoraCardRingPosition(CardDisplayWork* p) {
    s32 angle;

    ApproachValue(&p->swingAngle, p->swingAngleTarget, p->swingSteps);

    if (p->swingSteps != 0) {
        p->swingSteps--;
    }

    p->unk_84 += (p->unk_88 - p->unk_84) >> 1;

    if ((s16)p->timer > 0) {
        ApproachValue(&p->unk_7C, p->unk_80, p->timer);
        p->timer--;
        p->flags &= ~CARD_DISP_FLAG_SETTLED;
        gCardBattleState->soraReloadCharging = 0;
    } else {
        p->flags |= CARD_DISP_FLAG_SETTLED;
    }

    p->unk_8C = gSineTable[(p->swingAngle >> 8) & 0xFF] * 80 + gSoraCardLayout[0][0];
    p->unk_90 = -gSineTable[((p->swingAngle >> 8) & 0xFF) + 0x40] * 80 + gSoraCardLayout[0][1];
    angle = ((p->unk_7C >> 8) + 0x20) & 0xFF;
    p->x = gSineTable[angle] * (p->unk_84 >> 8) + p->unk_8C;
    p->y = -gSineTable[angle + 0x40] * (p->unk_84 >> 8) + p->unk_90;
}

void UpdateCardDisplayFlip(CardDisplayWork* p) {
    if (p->flags & CARD_DISP_FLAG_VISIBLE) {
        if (p->flags & CARD_DISP_FLAG_SELECTED) {
            if (p->flags & CARD_DISP_FLAG_FACE_DOWN) {
                if (p->scaleX > 2) {
                    p->scaleX -= 64;

                    if (p->scaleX <= 2) {
                        p->scaleX = 2;
                    }
                } else {
                    p->scaleX = 2;
                    p->flags &= ~CARD_DISP_FLAG_FACE_DOWN;

                    if (!(p->flags & CARD_DISP_FLAG_GFX_LOADED)) {
                        LoadCardDisplayGfx(p);
                        p->flags |= CARD_DISP_FLAG_GFX_LOADED;
                    }
                }
            } else {
                if (p->scaleX <= 255) {
                    p->scaleX += 64;

                    if (p->scaleX > 256) {
                        p->scaleX = 256;
                    }
                } else {
                    p->scaleX = 256;
                }
            }
        } else {
            if (!(p->flags & CARD_DISP_FLAG_FACE_DOWN)) {
                if (p->scaleX > 2) {
                    p->scaleX -= 64;

                    if (p->scaleX <= 2) {
                        p->scaleX = 2;
                    }
                } else {
                    p->scaleX = 2;
                    p->flags |= CARD_DISP_FLAG_FACE_DOWN;

                    if (p->flags & CARD_DISP_FLAG_GFX_LOADED) {
                        ReleaseCardDisplayGfx(p);
                        p->flags &= ~CARD_DISP_FLAG_GFX_LOADED;
                    }
                }
            } else {
                if (p->scaleX <= 255) {
                    p->scaleX += 64;

                    if (p->scaleX > 256) {
                        p->scaleX = 256;
                    }
                } else {
                    p->scaleX = 256;
                }
            }
        }
    }
}

u8 func_0807CE04(CardDisplayWork* p) {
    ApproachValue(&p->y, 0x8200, p->timer);

    if ((s16)p->timer > 0) {
        p->timer--;
    } else {
        p->timer = 0;
    }

    if ((s16)p->timer == 0) {
        p->timer = 0;
        p->angle += p->unk_9E;
        p->unk_9E++;

        if (p->scaleX <= 25) {
            return 0;
        }

        p->scaleX -= 25;
        p->scaleY -= 25;
    }

    return 1;
}

u8 IsCardDisplayOffScreen(CardDisplayWork* p) {
    if (p->x > 0x10000) {
        return 1;
    }

    if (p->x < -0x1000) {
        return 1;
    }

    if (p->y > 0xC000) {
        return 1;
    }

    if (p->y < -0x2000) {
        return 1;
    }

    return 0;
}

u8 func_0807CE9C(CardDisplayWork* p) {
    p->command = 0;
    p->y -= p->unk_84;
    p->unk_84 -= (s16)p->timer;
    p->timer++;
    p->x -= gSineTable[(p->unk_7C & 0xFF) + 0x40];
    p->angle += p->unk_9E;
    p->scaleX -= 5;
    p->scaleY -= 5;

    if (IsCardDisplayOffScreen(p)) {
        p->flags &= ~CARD_DISP_FLAG_VISIBLE;
        ReleaseCardDisplayGfx(p);
        gBtlWork->flags &= ~BTL_FLAG_PLAYER_CARD_BUSY;
        p->flags &= ~CARD_DISP_FLAG_GFX_LOADED;
        return 0;
    }

    return 1;
}

u8 func_0807CF4C(CardDisplayWork* p, void* a) {
    s32 z;

    p->timer = 15;
    z = 0;
    p->unk_88 = 0x800;
    p->unk_84 = z;
    p->unk_80 = gPlayedCardAngles[p->stockIndex] * 2;
    p->unk_7C = z;
    p->unk_8C = p->x;
    p->unk_90 = p->y;
    SetTaskUpdate(a, (TaskUpdateFunc)func_0807C5D8);
    return 1;
}

u8 func_0807CFA8(CardDisplayWork* p, void* a) {
    ApproachValue(&p->unk_8C, gPlayedCardCenter[0], p->timer);
    ApproachValue(&p->unk_90, gPlayedCardCenter[1], p->timer);
    ApproachValue(&p->unk_84, p->unk_88, p->timer);
    ApproachValue(&p->scaleX, 0x100, p->timer);
    ApproachValue(&p->scaleY, 0x100, p->timer);

    if ((s16)p->timer > 0) {
        p->timer--;
    } else {
        p->timer = 0;
    }

    func_0807D0F4(p);

    if (gBtlWork->flags & BTL_FLAG_CARD_ACTIVE) {
        if (p->flags & CARD_DISP_FLAG_IN_PLAY) {
            if ((s16)p->timer == 0) {
                SetTaskUpdate(a, (TaskUpdateFunc)func_0807C5D8);
            }
        } else if ((s16)p->timer <= 2) {
            p->priority -= 4;
            p->unk_84 = 0x500;
            p->timer = 0x100;
            p->unk_7C = -16;
            p->unk_9E = 0xFF;
            gCardBattleState->unk_0C0 = 0;
            gCardBattleState->soraStockActive = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)func_0807CE9C);
        }
    } else if ((s16)p->timer <= 2) {
        p->priority -= 4;
        p->unk_84 = 0x500;
        p->timer = 0x100;
        p->unk_7C = -16;
        p->unk_9E = 0xFF;
        gCardBattleState->soraStockActive = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807CE9C);
    }

    return 1;
}

void func_0807D0F4(CardDisplayWork* p) {
    s32 t;

    if (p->unk_80 - p->unk_7C > 0x7F00) {
        p->unk_7C += 0x10000;
    }

    if (p->unk_80 - p->unk_7C <= 255) {
        t = p->unk_7C - 0x10000;

        if (p->unk_80 - t < p->unk_7C - p->unk_80) {
            p->unk_7C = t;
        }
    }

    p->unk_7C += (p->unk_80 - p->unk_7C) >> 2;
    p->x = gSineTable[(p->unk_7C >> 8) & 0xFF] * (p->unk_84 >> 8) + p->unk_8C;
    p->y = -gSineTable[((p->unk_7C >> 8) & 0xFF) + 64] * (p->unk_84 >> 8) + p->unk_90;
}

u8 DispatchSoraCardCommand(CardDisplayWork* w, void* a) {
    switch (w->command) {
    case 5:
        if (!(w->flags & CARD_DISP_FLAG_GFX_LOADED)) {
            LoadCardDisplayGfx(w);
            w->flags |= CARD_DISP_FLAG_GFX_LOADED;
        }

        UpdateSoraCardRingPosition(w);
        w->timer = 10;
        w->priority -= 4;
        ListPoolRemove(&w->node, w->args.pool);
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807C4BC);
        return 1;
    case 6:
        if (!(w->flags & CARD_DISP_FLAG_GFX_LOADED)) {
            LoadCardDisplayGfx(w);
            w->flags |= CARD_DISP_FLAG_GFX_LOADED;
        }

        w->timer = 8;
        w->priority -= 4;
        LoadSoraCardDisplayGfx2(w);
        w->flags |= CARD_DISP_FLAG_STOCKED;
        w->flags |= CARD_DISP_FLAG_GFX_LOADED;
        ListPoolRemove(&w->node, w->args.pool);
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807C934);
        return 1;
    case 8:
        w->priority -= 4;
        w->unk_84 = 0x500;
        w->timer = 0x100;
        w->unk_7C = -16;
        w->unk_9E = 0xFF;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807CE9C);
        break;
    case 7:
        w->unk_84 = 0x500;
        w->timer = 0x100;
        ListPoolRemove(&w->node, w->args.pool);
        return 0;
    case 10:
        w->timer = 10;
        w->priority -= 4;
        ListPoolRemove(&w->node, w->args.pool);
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807D4E4);
        return 1;
    case 11:
        w->timer = 10;
        w->priority -= 4;
        ListPoolRemove(&w->node, w->args.pool);
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807D584);
        return 1;
    }

    UpdateSoraCardValue(w);
    return 1;
}

void LookupSoraCardDef(CardDisplayArgs* a, CardDef** out, u8 index) {
    u32* q;

    if (a->slot != NULL) {
        if (a->slot->cardId != CARD_ID_NONE) {
            if (a->slot->cardId != CARD_ID_RELOAD) {
                *out = &gCardDefs[a->slot->cardId & CARD_ID_MASK];
            } else {
                *out = NULL;
            }
        } else {
            *out = NULL;
        }
    } else {
        q = &gCardBattleState->pickedFriendCardId;
        *out = &gCardDefs[*q & CARD_ID_MASK];
        *q = 0x3B6;
    }
}

void LinkSoraCardDisplay(CardDisplayWork* p) {
    ListNodeInit(&p->node, p->args.pool, p);
    ListPoolAppend(&p->node, p->args.pool);
}

u8 func_0807D3A0(CardDisplayWork* p, void* a) {
    p->command = 0;
    p->y -= p->unk_84;
    p->unk_84 -= (s16)p->timer >> 1;
    p->timer++;
    p->x -= 0x200;
    p->angle += 16;

    if (!(p->flags & CARD_DISP_FLAG_SPIN_MIRRORED)) {
        p->scaleX -= 10;

        if (p->scaleX >= -2 && p->scaleX <= 2) {
            p->scaleX = -10;
        }

        if (p->scaleX <= -0x100) {
            p->scaleX = -0x100;
            p->flags |= CARD_DISP_FLAG_SPIN_MIRRORED;
        }
    } else {
        p->scaleX -= 10;

        if (p->scaleX >= -2 && p->scaleX <= 2) {
            p->scaleX = 10;
        }

        if (p->scaleX >= 0x100) {
            p->scaleX = 0x100;
            p->flags &= ~CARD_DISP_FLAG_SPIN_MIRRORED;
        }
    }

    if (IsCardDisplayOffScreen(p)) {
        p->flags &= ~CARD_DISP_FLAG_VISIBLE;
        ReleaseCardDisplayGfx(p);
        p->flags &= ~CARD_DISP_FLAG_GFX_LOADED;
        gBtlWork->flags &= ~BTL_FLAG_PLAYER_CARD_BUSY;
        return 0;
    }

    return 1;
}

void LoadSoraCardDisplayGfx2(CardDisplayWork* p) {
    void* tiles;
    void* pal;

    ReleaseCardDisplayGfx(p);
    tiles = p->cardDef->tiles2;
    pal = p->cardDef->palette2;
    p->tiles = LoadObjTiles(tiles, 256);
    p->palette = LoadObjPalette(pal, 32);
}

void RefreshSoraCardDisplayGfx(CardDisplayWork* p) {
    if (p->tiles != NULL) {
        ReleaseObjTiles(p->tiles);
    }

    if (p->palette != NULL) {
        ReleaseObjPalette(p->palette);
    }

    p->tiles = NULL;
    p->palette = NULL;
    LoadCardDisplayGfx(p);
}

u8 func_0807D4E4(CardDisplayWork* p) {
    u8 arg;

    p->command = 0;
    ApproachValue(&p->x, 0x1800, p->timer);
    ApproachValue(&p->scaleY, 0x99, p->timer);
    ApproachValue(&p->y, 0x6400, p->timer);
    ApproachValue(&p->scaleX, 0x99, p->timer);

    if ((s16)p->timer > 0) {
        p->timer--;
        return 1;
    }

    arg = 1;
    gBtlWork->hcEffectCount = gHcEffectDefs[gBtlWork->hcEffect].count;
    TaskCreate(&gCardBattleState->tasks, &gTaskDescHCEffectName, &arg);
    return 0;
}

u8 func_0807D584(CardDisplayWork* p, void* a) {
    s16 sx;
    s16 sy;
    s32 dx;
    s32 dy;
    s32 x;
    s32 y;

    ApproachValue(&p->x, 0x1800, p->timer);
    ApproachValue(&p->y, 0x6400, p->timer);

    if ((s16)p->timer > 0) {
        p->timer--;
    } else {
        WorldToScreen(&sx, &sy, gBtlWork->gimmickX, gBtlWork->gimmickY, gBtlWork->gimmickZ);
        x = sx;
        y = sy;
        dx = (x << 8) - p->x;
        dy = (y << 8) - p->y;
        p->unk_84 = NormalizeVector2D8(&dx, &dy);
        p->unk_8C = -dx;
        p->unk_90 = -dy;
        p->unk_88 = 0x300;
        p->angle = 0;
        p->unk_80 = 25;
        gBtlWork->hitStop = 10000;
        FadeStartOut(FADE_MODE_WHITE_BLEND, 1);
        m4aSongNumStart(SONG_BTL_GMIC_OK);
        FadeLock();
        gBtlWork->flags |= BTL_FLAG_BGFX_PAUSED;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807D68C);
    }

    return 1;
}

u8 func_0807D68C(CardDisplayWork* p, void* a) {
    s16 sx;
    s16 sy;
    s32 dx;
    s32 dy;
    s32 x;
    s32 y;

    WorldToScreen(&sx, &sy, gBtlWork->gimmickX, gBtlWork->gimmickY, gBtlWork->gimmickZ);
    x = sx;
    y = sy;

    if (p->unk_88 < 0) {
        dx = (x << 8) - p->x;
        dy = (y << 8) - p->y;
        NormalizeVector2D8(&dx, &dy);
        p->unk_8C = -dx;
        p->unk_90 = -dy;
    }

    p->angle += 24;

    if (p->scaleX > 24) {
        p->scaleX -= 12;
        p->scaleY -= 12;
    } else {
        p->scaleX = 25;
        p->scaleY = 25;
    }

    p->x += (p->unk_8C * p->unk_88) >> 8;
    p->y += (p->unk_90 * p->unk_88) >> 8;
    p->unk_84 = VectorLength2D((x << 8) - p->x, (y << 8) - p->y);
    p->unk_88 -= p->unk_80;
    p->unk_80 += 2;

    if (p->unk_84 <= 0x800) {
        gBtlWork->freezeTimer = 15;
        gBtlWork->hitStop = 15;
        m4aSongNumStart(SONG_SYS_CLICKI04);
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807D7B0);
    }

    return 1;
}

u8 func_0807D7B0(CardDisplayWork* p) {
    if (gBtlWork->hitStop == 0) {
        FadeStartIn(FADE_MODE_WHITE_BLEND, 8);
        FadeLock();
        gBtlWork->flags &= ~BTL_FLAG_BGFX_PAUSED;

        if (p->cardDef->move == 140) {
            SetGimmickFlag(0);
        }

        gBtlWork->flags &= ~BTL_FLAG_GIMMICK_CARD_ACTIVE;
        return 0;
    }

    return 1;
}

u8 func_0807D810(CardDisplayWork* p) {
    s32 r;

    if (p->scaleX <= 25) {
        p->args.slot->stocked = r = 0;
        return r;
    }

    p->scaleX -= 12;
    p->scaleY += 12;

    if (p->scaleY > 0x1FF) {
        p->scaleY = 0x200;
    }

    return 1;
}

void card_reload_0(CardDisplayWork* p, CardDisplayArgs* a) {
    CpuFill32(0, p, sizeof(CardDisplayWork));
    p->tiles = NULL;
    p->tiles2 = NULL;
    p->tiles3 = NULL;
    p->tiles4 = NULL;
    p->tiles5 = NULL;
    p->palette2 = NULL;
    p->palette = NULL;
    p->children = NULL;
    p->reloadGauge = EwramAlloc(sizeof(ReloadGauge));
    CpuFill32(0, p->reloadGauge, sizeof(ReloadGauge));
    p->args = *a;
    p->reloadGauge->chargeTick = 0;
    p->flags = (CARD_DISP_FLAG_OPEN | CARD_DISP_FLAG_RELOAD_CARD | CARD_DISP_FLAG_RELOAD_GAUGE);
    p->cardDef = NULL;
    p->scaleX = 0x100;
    p->scaleY = 0x100;
    p->bobAngle = 0;
    p->angle = 0;
    p->stockIndex = 0;
    p->unk_7C = 0;
    p->unk_80 = 0;
    p->swingAngle = 0;
    p->swingAngleTarget = 0;
    p->command = 0;
    p->priority = 60;
    p->timer = 4;
    p->unk_A2 = 0;
    p->unk_84 = 0;
    p->unk_88 = 0x2400;
    p->swingSteps = 0;
    p->unk_8C = gSoraCardLayout[0][0];
    p->unk_90 = gSoraCardLayout[0][1];
    p->x = gSoraCardLayout[4][0];
    p->y = gSoraCardLayout[4][1];
    p->flags &= ~CARD_DISP_FLAG_SETTLED;
    gCardBattleState->soraReloadCharging = 0;
    LinkSoraCardDisplay(p);
}

u8 func_0807D930(CardDisplayWork* p, void* a) {
    u8 (*f)(CardDisplayWork*, void*);

    if (p->command == 7) {
        return 0;
    }

    p->unk_84 += (0 - p->unk_84) >> 1;
    p->x += (gSoraCardLayout[4][0] - p->x) >> 1;
    p->y += (gSoraCardLayout[4][1] - p->y) >> 1;

    if (p->flags & CARD_DISP_FLAG_OPEN) {
        f = card_reload_1;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        return f(p, a);
    }

    return 1;
}

u8 card_reload_1(CardDisplayWork* p, void* a) {
    if (p->flags & CARD_DISP_FLAG_DEALING) {
        p->timer = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807CB24);
        return 1;
    }

    if ((s16)p->timer == 0) {
        if (IsCardDisplayOffScreen(p)) {
            ListPoolRemove(&p->node, p->args.pool);
            return 0;
        }

        if (!(p->flags & CARD_DISP_FLAG_GFX_LOADED)) {
            LoadSoraReloadCardGfx(p);
            p->flags |= CARD_DISP_FLAG_GFX_LOADED;
        }
    }

    if (p->flags & CARD_DISP_FLAG_FROZEN) {
        return 1;
    }

    if (!(p->flags & CARD_DISP_FLAG_OPEN)) {
        p->flags &= ~CARD_DISP_FLAG_SETTLED;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0807D930);
    }

    UpdateSoraReloadGauge(p);
    UpdateSoraCardRingPosition(p);
    p->bobAngle += 4;
    return DispatchSoraCardCommand(p, a);
}

void InitSoraReloadCounterAnim(ReloadGauge* p, void* a, u8 b, s8 c) {
    AnimInit(&p->anim, gUnk_09EEA4E0, gUnk_09EEA494);

    if (c >= 0) {
        AnimStart(&p->anim, c, 0);
    } else {
        AnimStart(&p->anim, 0, 0);
    }

    p->gfx3 = AnimGetGfx(&p->anim);
}

void SetSoraReloadCounterAnim(ReloadGauge* p, s32 a) {
    void* gfx;

    if ((u16)a <= 18) {
        AnimStart(&p->anim, a, 0);
        gfx = AnimGetGfx(&p->anim);
    } else {
        gfx = NULL;
    }

    p->gfx3 = gfx;
}

void LoadSoraReloadCardGfx(CardDisplayWork* p) {
    ReloadGauge* d;

    d = p->reloadGauge;
    p->tiles = AllocObjTiles(0x80, NULL);
    SetObjTileSource(p->tiles, gUnk_0909A4E0);
    InitSoraReloadCounterAnim(p->reloadGauge, p->tiles, p->args.listIndex, gCardBattleState->soraReloadCounter);
    p->palette = NULL;
    p->tiles2 = LoadObjTiles(gUnk_0909FDCA, 0x280);
    p->palette2 = NULL;
    p->tiles3 = AllocObjTiles(0x200, NULL);
    SetObjTileSource(p->tiles3, gRiCardF0RedTiles);
    p->tiles4 = AllocObjTiles(0x80, NULL);
    SetObjTileSource(p->tiles4, gRiCardF0RedTiles);
    AnimInit(&d->anim2, gRiCardF0RedAnims, gRiCardF0RedFrames);
    AnimStart(&d->anim2, 1, ANIM_FLAG_LOOP);
    d->gfx = gRiCardF0RedFrames[3];
    AnimInit(&d->anim3, gRiCardF0RedAnims, gRiCardF0RedFrames);
    AnimStart(&d->anim3, gCardBattleState->soraGaugeAnim, ANIM_FLAG_LOOP);
    d->gfx2 = gRiCardF0RedFrames[gCardBattleState->soraGaugeFullFrame + 2];
}

void card_reload_2(CardDisplayWork* p) {
    ReloadGauge* w;
    s16 y;
    ObjAffine* affine;
    s32 attr;

    if (p->flags & CARD_DISP_FLAG_GFX_LOADED) {
        w = p->reloadGauge;

        if (IsMessageWindowOpen() == 1) {
            y = p->y >> 8;
        } else {
            y = (p->y >> 8) + (gSineTable[p->bobAngle] >> 8);
        }

        attr = 0x410;
        DrawSprite(p->x >> 8, y, gCardBacks[3].gfx2, p->tiles2,
                   gCardBattleState->palette, NULL, attr, p->priority);

        if (!(gGameState.flags & GAME_FLAG_RIKU) && w->gfx3 != NULL) {
            DrawSprite(p->x >> 8, y, w->gfx3, p->tiles,
                       gCardBattleState->palette, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, p->priority - 2);
        }

        if ((s32)gCardBattleState->soraReloadGauge > 0) {
            affine = AllocObjAffine(0, p->scaleX, gCardBattleState->soraReloadGauge, 0);

            if (w->gfx != NULL) {
                DrawSprite(p->x >> 8, y + 17, w->gfx, p->tiles3,
                           gCardBattleState->palette, affine, SPRITE_PRIORITY(1),
                           p->priority - 1);
            }

            if (gCardBattleState->reloadGaugeFull[0] == 1 && w->gfx2 != NULL) {
                DrawSprite(p->x >> 8, y, w->gfx2, p->tiles4,
                           gCardBattleState->palette, NULL, SPRITE_PRIORITY(1),
                           p->priority - 1);
            }
        }
    }
}

void card_reload_3(CardDisplayWork* p) {
    ReleaseCardDisplayGfx(p);
    EwramFree(p->reloadGauge);

    if (gBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
        gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
    }
}

void AdvanceSoraReloadGaugeAnim(ReloadGauge* p, CardDisplayWork* w) {
    if (gCardBattleState->soraGaugeAnim <= 7) {
        gCardBattleState->soraGaugeAnim++;
    }

    AnimStart(&p->anim3, gCardBattleState->soraGaugeAnim, ANIM_FLAG_LOOP | ANIM_FLAG_KEEP_FRAME);
}

void ResetSoraReloadGaugeAnim(ReloadGauge* p) {
    gCardBattleState->soraGaugeAnim = 2;
    AnimStart(&p->anim3, 2, ANIM_FLAG_LOOP | ANIM_FLAG_KEEP_FRAME);
}

void func_0807DDCC(ReloadGauge* p, CardDisplayWork* w) {
    p->gfx = gRiCardF0RedFrames[3];
    p->gfx2 = gRiCardF0RedFrames[gCardBattleState->soraGaugeFullFrame + 2];
}

void func_0807DDF4(ReloadGauge* p, CardDisplayWork* w) {
    p->gfx = AnimUpdate(&p->anim2);
    p->gfx2 = AnimUpdate(&p->anim3);
}

void UpdateSoraReloadGauge(CardDisplayWork* p) {
    ReloadGauge* w = p->reloadGauge;
    u8 v = 0;

    if ((p->flags & (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) == (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) {
        v = gCardBattleState->soraReloadCharging;
        gCardBattleState->soraReloadCharging = 0;
    } else {
        gCardBattleState->soraReloadCharging = 0;
    }

    if ((p->flags & (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) == (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) {
        if (v == 1) {
            if ((s8)w->chargeTick == 2) {
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
                    AdvanceSoraReloadGaugeAnim(p->reloadGauge, p);

                    if (gCardBattleState->soraGaugeFullFrame == 22) {
                        gCardBattleState->soraGaugeFullFrame = 4;
                        gCardBattleState->soraReloadGauge = 0;
                        gCardBattleState->reloadGaugeFull[0] = 0;
                        gCardBattleState->soraReloadCounter--;
                        p->unk_A2 = v;
                        ResetSoraReloadGaugeAnim(p->reloadGauge);
                        m4aSongNumStart(SONG_SYS_CHAGEF1);
                        SetSoraReloadCounterAnim(p->reloadGauge, (s16)gCardBattleState->soraReloadCounter);
                    }
                }

                w->chargeTick = 0;
            }

            func_0807DDF4(p->reloadGauge, p);
            w->chargeTick++;
        } else {
            func_0807DDCC(p->reloadGauge, p);
            w->chargeTick = 0;
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

        if (!(p->flags & CARD_DISP_FLAG_RELOAD_DONE)) {
            p->flags |= CARD_DISP_FLAG_RELOAD_DONE;
            m4aSongNumStart(SONG_SYS_CHAGEF2);
        }

        if (FadeGetAmount() == 0) {
            FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
        }

        gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
    }
}

void UpdateSoraCardValue(CardDisplayWork* w) {
    // @bug A "not have" display has no cardDef (NULL read).
    if (gBtlWork->hcEffect == 16) {
        if (w->flags & CARD_DISP_FLAG_SELECTED) {
            w->valueModified = 1;
            w->value = GetRandom() % 10;
        } else {
            w->valueModified = 0;
            w->value = w->cardDef->value;
        }
    } else if (gBtlWork->hcEffect == 17) {
        w->valueModified = 1;
        w->value = 0;
    } else if (gBtlWork->hcEffect == 31) {
        w->valueModified = 1;
        w->value = 10 - w->cardDef->value;

        if (w->value == 10) {
            w->value = 0;
        }
    } else {
        w->value = w->cardDef->value;

        switch (gGameState.roomEffect) {
        case 7:
            if (w->cardDef->category == 1) {
                w->value += 2;

                if (w->value > 9) {
                    w->value = 9;
                }

                w->valueModified = 1;
            }

            break;
        case 8:
            if (w->cardDef->category == 2 && (w->cardDef->flags & CARD_DEF_FLAG_ITEM)) {
                w->value += 2;

                if (w->value > 9) {
                    w->value = 9;
                }

                w->valueModified = 1;
            }

            break;
        case 9:
            if (w->cardDef->category == 0) {
                w->value += 2;

                if (w->value > 9) {
                    w->value = 9;
                }

                w->valueModified = 1;
            }

            break;
        default:
            w->valueModified = 0;
            w->value = w->cardDef->value;
            break;
        }
    }
}

void TickSoraHcEffectOnPlayEnd() {
    BtlWork* p;

    p = gBtlWork;

    switch ((u32)p->hcEffect) {
    case 15:
    case 28:
    case 47:
        p->hcEffectCount--;
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
