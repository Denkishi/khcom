#ifndef GUARD_MODE_MAPINSPECT_H
#define GUARD_MODE_MAPINSPECT_H

#include "types.h"
#include "ms_types.h"
extern u16 gUnk_0815C136[];
extern u16 gCard00Palette[];

s16 GetMapInspectTabStart(s16 a);
s16 GetMapInspectSelectedIndex();
void MapInspectSelectFirstValue();
s16 GetMapInspectTabCount(s16 a);
u8 MapInspectCanDelete();
s16 GetMapInspectValueIndex(s16 a, s16 b);
s16 GetMapInspectSelectedValue();
u16 MapInspectReadMenuKeys();
void MapInspectSelectValueInColumn(MapCardInventoryEntry* p, u16 row);
void MapInspectDeleteCard();
u8 MapCardEntryIsEmpty(MapCardInventoryEntry* p);
u8 MapCardEntrySelectedValueIsEmpty(MapCardInventoryEntry* p);
void MapInspectSelectNextValue(MapCardInventoryEntry* p);
void MapInspectRemoveEntry(MapCardInventoryEntry* p);
void MapInspectHandleGridInput();
void MapInspectHandleTabInput();
void MapInspectHandleValueInput();
void MapInspectHandleConfirmInput();
void MapInspectHandleNoticeInput();
void MapInspectDraw();
void MapInspectBuildInventory();
struct MapCardInventoryEntry* GetMapInspectSelectedEntry();
void MapInspectDrawTab(s16 a);
void MapInspectDrawCardTotal();
void MapInspectDrawCategoryCounts();
void MapInspectDrawValueCounts();
void MapInspectLoadGrid();
void MapInspectLoadSelectedCard();

#endif /* GUARD_MODE_MAPINSPECT_H */
