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
struct UnkStruct_080ABA80;
struct CardDisplayWork;
struct MapcardWork;
struct EventKey;
struct SaveLargeSlice;
struct SaveSmallSlice;
struct BtlPrizeSrc;

void Mapcard_2(struct MapcardWork* w);
void Level_Up_3(struct LevelUpWork* w);
void mode_sio_battle_0(s32 a);
void mode_sio_battle_1(void);
void mode_sio_battle_2(void);

void InitRikuDeckForWorld(u8 a);
void SelectPrevSoraCard(struct CardBattleWork* w, u8 b, u8 c);
void func_0807B3C4(s32 a);
u8 GetSoraCardListIndex(void);
u8 GetSoraStockCount(void);
void LoadPremiumCardGfx(struct CardBattleState* p);
void RequestRikuPotion(void);
void RequestRikuHiPotion(void);
void RequestRikuMegaPotion(void);
void RequestRikuEther(void);
void RequestRikuMegaEther(void);
void RequestRikuElixir(void);
void RequestRikuMegalixir(void);
void RequestRikuNextCard(void);
void RequestRikuPrevCard(void);
void RequestRikuCardUse(void);
void RequestRikuCardStock(void);
void RequestRikuStockUse(void);
void RequestOpenRikuCards(void);
void RequestCloseRikuCards(void);
u8 IsRikuReloadCardSelected(void);
u8 func_08081828(void);
void RequestBossCardValue(u8 a);
void RequestBossCardRandom(void);
u8 func_08083920(void);
s16 ObtainCard(u16 cardId);
u8* GetDeckName(u8 index);
s16 CountActiveDeckCards(s32 index);
u16 GetDeckCardCount(u8 index);
void InitSoraDecks(void);
void InitDebugDecks(void);
void func_08085FB0(void);
s32 AddMapCard(u16 a);
u16 CountRegularMapCards(void);
void InitMapCardInventory(void);
void ResetSelectedMapCard(void);
void* GetRoomName(u16 a);
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
void PrintString(u8 a, u8 b, u8 c, u8* s);
void PrintNumber(u16 x, u16 y, u16 color, s32 value);
u8 CreateLevelUpEffectTask(struct BtlObj* p, struct TaskPool* pool);
void WriteCardSaveSlice(struct SaveLargeSlice* p);
void ReadCardSaveSlice(struct SaveLargeSlice* p);
void CopyMapCardInventory(struct SaveSmallSlice* p);
void RestoreMapCardInventory(struct SaveSmallSlice* p);
void CreateCardMessageTask(void* pool, u32 a, u16 b);
void CreateSysmsgwinTask(void* pool, u16 b);
void ResetMessageWindowFlags(void);
u8 IsMessageWindowOpen(void);
u8 IsMessageWindowAnswerYes(void);
u8 CloseMessageWindow(void);
s32 ResolveActiveCardsMove(s32* out);
s32 LookupStockName(struct CardDisplayWork** cards, u8 count, u8 kind, struct UnkStruct_080ABA80* arr, u8* flag);
s32 LookupLinkStockName(struct CardDisplayWork** cards, u8 count, u8 kind, struct UnkStruct_080ABA80* arr, u8* flag, s32 b);
s32 LookupStockPairName(struct UnkStruct_080ABA80* cards, u8* output, u8 count);

void ClearSioBattleFileLoaded(void);

struct CardListWork;

extern u8 gBossCardRequestValue;
extern u8 gBossCardRequest;
extern Deck gDecks[3];
extern u16 gCardCollection[999];
extern Deck* gLinkPartnerDeck;
extern void* gLinkSendDeck;
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
extern s8 gSioDebugMode;
extern u8 gSioBattleFileLoaded;

#endif
