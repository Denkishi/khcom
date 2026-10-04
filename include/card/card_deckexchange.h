#ifndef GUARD_CARD_DECKEXCHANGE_H
#define GUARD_CARD_DECKEXCHANGE_H

#include "card.h"
#include "types.h"

u8 UpdateDeckExchangeLoadBgs(DeckExchangeWork* work, void* a);
u8 UpdateDeckExchangeOpenCollection(DeckExchangeWork* work, void* a);
u8 UpdateDeckExchangeBuildList(DeckExchangeWork* work, void* a);
u8 UpdateDeckExchangeGrid(DeckExchangeWork* work, void* a);
u8 UpdateDeckExchangeClose(DeckExchangeWork* work, void* a);
u8 UpdateDeckExchangeFadeOut(DeckExchangeWork* work);
void CreateDeckExchangeDeckGridCards(DeckExchangeWork* work, u8 kind);
s32 CreateDeckExchangeCollectionGridCards(DeckExchangeWork* work, u8 kind, u8 c);
s32 GetCardIdForKind(s32 a);
void ClearDeckExchangeCardGrid(DeckExchangeWork* work);
void DrawDeckExchangeEquipMarker(u8 a);
void DrawDeckExchangeCardTotals();
void ShowDeckExchangeCardPreview(DeckExchangeWork* work);
void ReleaseDeckExchangeCardPreview(DeckExchangeWork* work);
void DrawDeckExchangeValueCpCost(DeckExchangeWork* work);
void DrawDeckExchangeCpCost(u8 a);
s32 MoveDeckExchangeValueCursor(DeckExchangeWork* work, u16 key);
void FreeDeckExchangeCollectionEntries(DeckExchangeWork* work);
s32 TakeTradeCard(DeckExchangeWork* work);
s32 CheckDeckExchangeCpCost(DeckExchangeWork* work);
u8 CheckDeckExchangeHasAttackCard(DeckExchangeWork* work);
void ResetDeckExchangeGridScroll(DeckExchangeWork* work);
u8 IsDeckExchangeCardAtCursor(DeckExchangeWork* work);
u8 IsDeckExchangeCardAt(DeckExchangeWork* work, s16 x, s16 y);
void LoadDeckExchangeCardDescriptionText(DeckExchangeWork* work, u16 index);
void SetDeckExchangeGridRowCount(DeckExchangeWork* work, s16 n);
void UpdateDeckExchangeGridScrollBar(DeckExchangeWork* work);

#endif
