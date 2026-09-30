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
#include "battle_actor_types.h"
#include "battle_work.h"
#include "card_def_data.h"
#include "card_types.h"
#include "game_state.h"
#include "obj.h"
#include "taskpool.h"
#include "types.h"
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

void func_08076284(void) {
    gSoraCardReloadRequest = 14;
}

void func_08076290(void) {
    gSoraCardReloadRequest = 15;
}

void func_0807629C(void) {
    gSoraCardReloadRequest = 16;
}

u8 func_080762A8(void) {
    return gCardBattleState->soraListIndex;
}

void RequestSoraPotion(void) {
    gSoraCardReloadRequest = 17;
}

void RequestSoraHiPotion(void) {
    gSoraCardReloadRequest = 18;
}

void RequestSoraMegaPotion(void) {
    gSoraCardReloadRequest = 19;
}

void RequestSoraEther(void) {
    gSoraCardReloadRequest = 21;
}

void RequestSoraMegaEther(void) {
    gSoraCardReloadRequest = 22;
}

void RequestSoraElixir(void) {
    gSoraCardReloadRequest = 23;
}

void RequestSoraMegalixir(void) {
    gSoraCardReloadRequest = 24;
}

void func_0807630C(void) {
    gSoraCardReloadRequest = 20;
}

void RequestSoraNextCard(void) {
    gSoraCardRequest = 1;
}

void RequestSoraPrevCard(void) {
    gSoraCardRequest = 2;
}

void RequestSoraCardUse(void) {
    gSoraCardRequest = 3;
}

void RequestSoraCardStock(void) {
    gSoraCardRequest = 4;
}

void RequestSoraStockUse(void) {
    gSoraCardRequest = 5;
}

void func_08076354(void) {
    gSoraCardRequest = 8;
}

void RequestOpenCards(void) {
    gSoraCardRequest = 6;
    RequestOpenRikuCards();
}

void RequestCloseCards(void) {
    gSoraCardRequest = 7;
    RequestCloseRikuCards();
}

void RequestCycleSoraCardList(void) {
    gSoraCardRequest = 9;
}

void RequestSwitchSoraCardList(void) {
    gSoraCardRequest = 10;
}

void func_080763A0(void) {
    gSoraCardRequest = 11;
}

void func_080763AC(void) {
    gSoraCardRequest = 12;
}

void func_080763B8(void) {
    gSoraCardRequest = 13;
}

void ClearSoraCardRequest(void) {
    gSoraCardRequest = 0;
}

u8 IsSoraReloadCardSelected(void) {
    if (gSoraSelectedCard != NULL && (gSoraSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD)) {
        return 1;
    }

    return 0;
}

void SetSoraReloadCharging(void) {
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

void func_08076438(void) {
}

u8 IsSoraSelectionEmpty(void) {
    if (gSoraSelectedCard != NULL) {
        return gSoraSelectedCard->flags & CARD_DISP_FLAG_NO_CARD;
    }

    return 0;
}

void CreateCardBattleState(void) {
    u32 zero;

    gCardBattleState = EwramAlloc(sizeof(CardBattleState));
    zero = 0;
    CpuSet(&zero, gCardBattleState, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(CardBattleState) / 4);
    gCardBattleState->activeCards[0] = 0;
    gCardBattleState->activeCards[1] = 0;
    gCardBattleState->activeCards[2] = 0;
    gCardBattleState->activeCards[3] = 0;
    gCardBattleState->activeCards[4] = 0;
    gCardBattleState->activeCards[5] = 0;
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

    return 0;
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

    return 0;
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

    p = (CardDisplayWork*)ListPoolFirst(&w->cardDisplays[slot]);

    while (p != NULL) {
        // @bug A "not have" display has no slot (NULL write).
        p->args.slot->unk_06 = 0;
        p = (CardDisplayWork*)ListPoolNext(&p->node);
    }

    w->selectedCards[slot] = ListPoolFirst(&w->cardDisplays[slot]);

    {
        CardDisplayWork** active = &gSoraSelectedCard;
        *active = ListPoolFirst(&w->cardDisplays[slot]);
    }

    gSoraSelectedCard->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
}

static void cardbattle_0(CardBattleWork* w) {
    u32 zero = 0;
    u8 i;

    CpuSet(&zero, w, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(CardBattleWork) / 4);
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
        w->playedCards[i] = 0;
        w->stock[i] = 0;
    }

    for (i = 0; i < 4; i++) {
        w->selectedCards[i] = 0;
        w->slots[i] = 0;
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
        TaskCreate(&w->tasks, &gTaskDescDarkPoint, 0);
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
                gSoraSelectedCard = 0;
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
                gSoraSelectedCard = 0;
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
                gSoraSelectedCard = 0;
            } else {
                RemoveSoraCardDisplays(w);
                w->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
                gSoraSelectedCard = 0;
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
                gSoraSelectedCard = 0;
            } else {
                RemoveSoraCardDisplays(w);
                w->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
                gSoraSelectedCard = 0;
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
                gSoraSelectedCard = 0;
            } else {
                RemoveSoraCardDisplays(w);
                w->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
                gSoraSelectedCard = 0;
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
                gSoraSelectedCard = 0;
            } else {
                RemoveSoraCardDisplays(w);
                w->listIndex = 0;
#ifdef VERSION_EU
                gCardBattleState->soraListIndex = 0;
#endif
                gSoraSelectedCard = 0;
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
                            TaskCreate(&w->tasks, &gTaskDescStockNameSora, 0);
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
                            TaskCreate(&w->tasks, &gTaskDescStockNameSora, 0);
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
        DrawSprite(w->x, 4, gUnk_09EF12E8[0], w->tiles, w->palette, 0, SPRITE_FLAG_NO_MOSAIC,
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
    gCardBattleState = 0;
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
