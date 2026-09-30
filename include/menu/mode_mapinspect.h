#ifndef GUARD_MODE_MAPINSPECT_H
#define GUARD_MODE_MAPINSPECT_H

#include "types.h"
#include "ms_types.h"
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
