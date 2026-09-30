#ifndef GUARD_MS_CHARGE_H
#define GUARD_MS_CHARGE_H

#include "ms_charge_api.h"
#include "types.h"

extern u8 gUnk_09A3DE7C[];

u16 CountCollectionCards(void);
u16 CountCardsInDecks(void);
void ClearCardCollectionSlot(u16* p);

s16 GetMsChargeTabStart(s16 a);
s16 GetMsChargeTabCount(s16 a);
s16 GetMsChargeSelectedIndex(void);
void MsChargeSelectFirstValue(void);
s16 GetMsChargeValueIndex(s16 a, s16 b);
s16 GetMsChargeSelectedValue(void);
u16 GetMsChargeCardPoints(u16 index);
void MsChargeSellCard(void);
u8 MsCardIsEmpty(MsCard* card);
u8 MsCardSelectedValueIsEmpty(MsCard* card);
void MsChargeSelectNextValue(MsCard* card);
void MsChargeRemoveCard(MsCard* card);
s32 FindMsCard(u16 id, u8 flag, s16 count);
s32 MsChargeReadMenuKeys(void);
s32 MsChargeSelectValueInColumn(MsCard* card, u16 col);

extern u8 gMoguFl00Tiles[];
extern u8 gCard00Palette[];
extern u8 gMoguPalette[];
void mode_ms_charge_1(void);
void mode_ms_charge_2(void);
void mode_ms_charge_0(void);

#ifdef VERSION_EU
extern u8 gUnkEu_092D1F74[];
extern u8 gUnkEu_099AEE98[];
#endif

#endif
