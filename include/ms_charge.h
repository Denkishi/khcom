#ifndef GUARD_MS_CHARGE_H
#define GUARD_MS_CHARGE_H

#include "card_def_data.h"

#include "registration_data.h"
#include "map_card_data.h"
#include "obj.h"
#include "card_ui_types.h"
#include "card_api.h"
#include "map_api.h"
#include "game_state.h"
#include "malloc.h"
#include "anim.h"
#include "mode.h"

#include "card_description_data.h"

#include "card_types.h"

#include "ms_types.h"

#include "ms_charge_api.h"
#include "mode_ms_top_api.h"

#include "mode_test_api.h"

#include "display.h"
#include "engine_math.h"

#include <string.h>
#include "text.h"
#include "fade.h"
#include "obj_api.h"
#include "types.h"
#include "text_types.h"
#include "key.h"
#include "engine.h"
#include "m4a.h"

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
extern u16 gUnk_08159E10[];
extern u16 gUnk_08159E18[];
extern u16 gUnk_08159F38[];
extern u16 gUnk_0815C204[];
extern u8 gCard00Palette[];
extern u8 gMoguPalette[];
void mode_ms_charge_1(void);
void mode_ms_charge_2(void);
void mode_ms_charge_0(void);

#endif
