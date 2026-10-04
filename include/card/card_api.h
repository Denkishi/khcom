#ifndef GUARD_CARD_API_H
#define GUARD_CARD_API_H

#include "types.h"
#include "card_types.h"
#include "card_ui_types.h"

struct CardBattleState;
struct CardBattleWork;
struct LayeredCardSprite;
struct BtlObj;
struct LevelUpWork;
struct TaskPool;
struct StockKeys;
struct CardDisplayWork;
struct MapcardWork;
struct EventKey;
struct SaveLargeSlice;
struct SaveSmallSlice;
struct BtlPrizeSrc;

void Mapcard_2(struct MapcardWork* work);
void Level_Up_3(struct LevelUpWork* work);

void InitRikuDeckForWorld(u8 a);
void SelectPrevSoraCard(struct CardBattleWork* work, u8 b, u8 c);
void func_0807B3C4(s32 a);
u8 GetSoraCardListIndex();
u8 GetSoraStockCount();
void LoadPremiumCardGfx(struct CardBattleState* p);
void RequestRikuPotion();
void RequestRikuHiPotion();
void RequestRikuMegaPotion();
void RequestRikuEther();
void RequestRikuMegaEther();
void RequestRikuElixir();
void RequestRikuMegalixir();
void RequestRikuNextCard();
void RequestRikuPrevCard();
void RequestRikuCardUse();
void RequestRikuCardStock();
void RequestRikuStockUse();
void RequestOpenRikuCards();
void RequestCloseRikuCards();
u8 IsRikuReloadCardSelected();
u8 func_08081828();
void RequestBossCardValue(u8 a);
void RequestBossCardRandom();
u8 GetBossCardShownValue();
s16 ObtainCard(u16 cardId);
u8* GetDeckName(u8 index);
s16 CountActiveDeckCards(s32 index);
u16 GetDeckCardCount(u8 index);
void InitSoraDecks();
void InitDebugDecks();
void func_08085FB0();
s32 AddMapCard(u16 a);
u16 CountRegularMapCards();
void InitMapCardInventory();
void ResetSelectedMapCard();
const void* GetRoomName(u16 a);
void CreatePrizeCardTask(struct TaskPool* pool, struct BtlPrizeSrc* src);
void CreateBossPrizeCardTask(void* a, void* b);
void DrawLayeredCardSprite(struct LayeredCardSprite* p, u16 a);
void SetLayeredCardSpritePos(s32 x, s32 y, LayeredCardSprite* p);
void ReleaseLayeredCardSprite(LayeredCardSprite* p);
struct ObjTiles* AllocKeyValueTiles(u8 a);
void InitEventKeyCard(EventKeyCard* card, struct EventKey* key);
u8 GetRoomCardBackIndex(u16 n);
void CreateREVCOUNTTask(void* pool, u8* a, s16* b, u8* c, u8 d);
void CreateFriendCardTask(void* pool, s16 x, s16 y, s16 z, u8 idx);
void PrintString(u8 a, u8 b, u8 c, const u8* s);
void PrintNumber(u16 x, u16 y, u16 color, s32 value);
u8 CreateLevelUpEffectTask(struct BtlObj* p, struct TaskPool* pool);
void WriteCardSaveSlice(struct SaveLargeSlice* p);
void ReadCardSaveSlice(struct SaveLargeSlice* p);
void CopyMapCardInventory(struct SaveSmallSlice* p);
void RestoreMapCardInventory(struct SaveSmallSlice* p);
void CreateCardMessageTask(void* pool, u32 a, u16 b);
void CreateSysmsgwinTask(void* pool, u16 b);
void ResetMessageWindowFlags();
u8 IsMessageWindowOpen();
u8 IsMessageWindowAnswerYes();
u8 CloseMessageWindow();
s32 ResolveActiveCardsMove(s32* out);
s32 LookupStockName(struct CardDisplayWork** cards, u8 count, u8 kind, struct StockKeys* arr, u8* flag);
s32 LookupLinkStockName(struct CardDisplayWork** cards, u8 count, u8 kind, struct StockKeys* arr, u8* flag, s32 b);
s32 LookupStockPairName(struct StockKeys* cards, u8* output, u8 count);

struct CardListWork;

extern u8 gBossCardRequestValue;
extern u8 gBossCardRequest;
extern Deck gDecks[3];
extern u16 gCardCollection[999];
extern Deck* gLinkPartnerDeck;
extern Deck* gLinkSendDeck;
extern u16 gCardCount;
extern CardUiSpriteState gCardUiSpriteState;
extern MapCardUiResources gMapCardUiResources;
extern u8 gMapCardCounts[270];
extern struct CardListWork* gCardListWork;
extern u8 gMessageWindowOpen;
extern u8 gMessageWindowAnswerYes;
#ifndef VERSION_EU
extern u16 gSioTradeCardId;
#endif
extern u8 gRikuDeckTutorialState;

#endif
