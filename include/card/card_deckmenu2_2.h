#ifndef GUARD_CARD_DECKMENU2_2_H
#define GUARD_CARD_DECKMENU2_2_H

#include "card.h"
#include "types.h"

u8 UpdateRikuDeckMenuLoadDeckInfo(RikuDeckMenuWork* work, void* a);
u8 UpdateRikuDeckMenuDeckGrid(RikuDeckMenuWork* work, void* a);
s32 UpdateRikuDeckMenuFadeOut(RikuDeckMenuWork* work);
void CreateRikuDeckGridCards(RikuDeckMenuWork* work, u8 kind);
void ClearRikuCardGrid(RikuDeckMenuWork* work);
DeckCard2Work* GetRikuCardAtCursor(RikuDeckMenuWork* work);
void ShowRikuDeckCardPreview(RikuDeckMenuWork* work);
void DrawRikuCpCost(u8 a);
void FreeRikuCollectionEntries(RikuDeckMenuWork* work);
void ReleaseRikuCommandMenuGfx(RikuDeckMenuWork* work);
void SetRikuDeckMenuFrameCursor(RikuDeckMenuWork* work, u8 mode);
u8 CheckRikuDeckCpCost(RikuDeckMenuWork* work);
u8 CheckRikuDeckHasAttackCard(RikuDeckMenuWork* work);

#endif
