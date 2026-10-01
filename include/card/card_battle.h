#ifndef GUARD_CARD_BATTLE_H
#define GUARD_CARD_BATTLE_H

#include "types.h"
#include "anim.h"
#include "taskpool.h"

struct CardDisplayWork;
struct CardSlot;
struct CardBattleWork;

typedef struct CardBattleState {
    struct CardDisplayWork* activeCards[6];
    struct CardDisplayWork* soraStockedCards[3];
    struct CardDisplayWork* rikuStockedCards[3];
    void* tiles[4];
    void* premiumTiles;
    void* tiles5;
    void* tiles6;
    void* tiles7;
    void* premiumTiles2;
    void* palette;
    void* palette2;
    struct CardBattleWork* soraWork;
    struct CardBattleWork* rikuWork;
    AnimState anim;
    AnimState anim2;
    void* gfx;
    void* gfx2;
    TaskPool tasks;
    u32 unk_0B0;
    u32 unk_0B4;
    u32 pickedFriendCardId;
    u32 pickedGimmickCardId;
    u16 unk_0C0;
    s16 activeValue;
    u16 soraStockName;
    u16 rikuStockName;
    u16 unk_0C8;
    u16 unk_0CA;
    u16 soraHcEffect;
    u16 rikuHcEffect;
    u8 activeCardCount;
    u8 unk_0D1;
    u8 soraListIndex;
    u8 soraStockCount;
    u8 rikuListIndex;
    u8 rikuStockCount;
    u8 friendCardCount;
    u8 nextEnemyCardIndex;
    u8 unk_0D8;
    u8 unk_0D9;
    u8 addedFriendCards[0x02];
    u8 gimmickCardCount;
    u8 stockMoveCount;
    u8 soraStockedCount;
    u8 rikuStockedCount;
    u8 enemyCardUsed;
    u8 soraStockActive;
    u8 rikuStockActive;
    u8 soraStockNameShown;
    u8 rikuStockNameShown;
    u8 unk_0E5;
    u8 unk_0E6;
    u8 soraReloadCharging;
    u8 rikuReloadCharging;
    u8 unk_0E9;
    u8 cardsOpen;
    u8 soraHcEffectReplaced;
    u8 rikuHcEffectReplaced;
    u8 unk_0ED;
    u8 darkModeReady;
    u8 unk_0EF;
    u16 rikuCardsLeft;
    u8 unk_0F2[0x02];
    u32 soraReloadGauge;
    u32 rikuReloadGauge;
    u16 soraReloadCounter;
    u16 rikuReloadCounter;
    s16 soraGaugeFullFrame;
    s16 rikuGaugeFullFrame;
    s16 soraGaugeAnim;
    s16 rikuGaugeAnim;
    u8 reloadGaugeFull[0x04];
} CardBattleState;

typedef char CardBattleState_size[(sizeof(CardBattleState) == 0x10C) ? 1 : -1];

extern struct CardDisplayWork* gSoraSelectedCard;
extern CardBattleState* gCardBattleState;

void SetSoraReloadCharging();
void RequestSoraNextCard();
void RequestSoraPrevCard();
void RequestSoraCardUse();
void RequestSoraCardStock();
void RequestSoraStockUse();
void RequestSwitchSoraCardList();
u8 IsSoraReloadCardSelected();
u8 IsSoraSelectionEmpty();
void RequestOpenCards();
void RequestCloseCards();
void RequestSoraMegalixir();
void RequestSoraPotion();
void RequestSoraHiPotion();
void RequestSoraMegaPotion();
void RequestSoraEther();
void RequestSoraMegaEther();
void RequestSoraElixir();
void RequestSoraKingReload0();
void RequestSoraKingReload1();
void RequestSoraKingReload2();
void RequestSoraRemoveItemCards();
s32 cardbattleSora_1(struct CardBattleWork* w, Task* task);
struct CardSlot* FindNextAvailableSlot(struct CardBattleWork* w, u8 slot, u16* n);
struct CardSlot* FindPrevAvailableSlot(struct CardBattleWork* w, u8 slot, u16* n);
void CreateSoraCardRing(struct CardBattleWork* w, u8 slot);

#endif
