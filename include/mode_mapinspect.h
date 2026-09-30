#ifndef GUARD_MODE_MAPINSPECT_H
#define GUARD_MODE_MAPINSPECT_H

#include "registration_data.h"
#include "card_description_data.h"
#include "map_card_data.h"
#include "card_ui_types.h"
#include "card_api.h"
#include "key.h"
#include "mode.h"
#include "m4a.h"

#include "obj.h"

#include "map_api.h"

#include "game_state.h"
#include "text.h"
#include "obj_api.h"
#include "display.h"
#include "types.h"
#include "engine_math.h"
#include "text_types.h"
#include "ms_types.h"
#include "main.h"
#include "anim.h"
extern u16 gUnk_08159E10[];
extern u16 gUnk_08159E18[];
extern u16 gUnk_08159FBC[];
extern u16 gUnk_0815C136[];
extern u8 gCard00Palette[];

s16 GetMapInspectTabStart(s16 a);
s16 GetMapInspectSelectedIndex(void);
void MapInspectSelectFirstValue(void);
s16 GetMapInspectTabCount(s16 a);
u8 MapInspectCanDelete(void);
s16 GetMapInspectValueIndex(s16 a, s16 b);
s16 GetMapInspectSelectedValue(void);
u16 MapInspectReadMenuKeys(void);
void MapInspectSelectValueInColumn(MapCardInventoryEntry* p, u16 row);
void MapInspectDeleteCard(void);
u8 MapCardEntryIsEmpty(MapCardInventoryEntry* p);
u8 MapCardEntrySelectedValueIsEmpty(MapCardInventoryEntry* p);
void MapInspectSelectNextValue(MapCardInventoryEntry* p);
void MapInspectRemoveEntry(MapCardInventoryEntry* p);
void MapInspectHandleGridInput(void);
void MapInspectHandleTabInput(void);
void MapInspectHandleValueInput(void);
void MapInspectHandleConfirmInput(void);
void MapInspectHandleNoticeInput(void);
void MapInspectDraw(void);
void MapInspectBuildInventory(void);
struct MapCardInventoryEntry* GetMapInspectSelectedEntry(void);
void MapInspectDrawTab(s16 a);
void MapInspectDrawCardTotal(void);
void MapInspectDrawCategoryCounts(void);
void MapInspectDrawValueCounts(void);
void MapInspectLoadGrid(void);
void MapInspectLoadSelectedCard(void);

#endif /* GUARD_MODE_MAPINSPECT_H */
