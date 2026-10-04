#ifndef GUARD_CARD_WORLDSELECT_H
#define GUARD_CARD_WORLDSELECT_H

#include "card.h"
#include "taskpool.h"
#include "types.h"

u8 UpdateMapSelectSetup(MapSelectWork* work, void* a);
u8 UpdateMapSelectSlideIn(MapSelectWork* work, void* a);
u8 UpdateMapSelectValueInput(MapSelectWork* work, void* a);
u8 UpdateMapSelectLeaveValues(MapSelectWork* work, void* a);
u8 UpdateMapSelectKindInput(MapSelectWork* work, void* a);
u8 UpdateMapSelectClose(MapSelectWork* work);
void CreateMapSelectCards(MapSelectWork* work);
void HandleMapSelectKindCursor(MapSelectWork* work);
void ApplyMapSelectPageScroll(MapSelectWork* work);
s32 SelectNearestMapSelectCard(MapSelectWork* work);
s32 RemoveMapCard(u16 a);
void CreateMapCardSelection(TaskPool* pool, u8* p);
void LoadMapSelectKindPalette(u16 a, MapSelectWork* work);
void LoadMapSelectGridPalette(u16 a, MapSelectWork* work);
s32 LoadMapSelectValueCounts(u16 a, MapSelectWork* work);
void HandleMapSelectValueCursor(MapSelectWork* work);
u8 UpdateMapSelectEventDoorTutorial(MapSelectWork* work, void* a);
s32 func_080948F0(MapcardWork* work, void* a);
void AimMapcardAtDoor(MapcardWork* work);
u8 UpdateMapcardFlyToDoor(MapcardWork* work, void* a);
void UpdateMapcardRise(MapcardWork* work);
void func_08094DEC(MapcardWork* work);
u8 func_08094E4C(MapcardWork* work);
MapcardWork* CreateMapCard(MapcardArgs* args, TaskPool* pool);
void LinkMapcardNode(MapcardWork* work);
u8 UpdateReloadGageIdle(CardDisplayWork* work, void* a);
void UpdateReloadGageRingPosition(CardDisplayWork* work);
void StepReloadGageSine(ReloadGauge* p);
void InitReloadGageCounterAnim(ReloadGauge* p, void* a, u8 b, s32 count);
void SetReloadGageCounterAnim(ReloadGauge* p, s32 count);
s32 UpdateReloadGageSlide(ReloadGauge* p, CardDisplayWork* work);
void InitReloadGageAnims(ReloadGauge* p, CardDisplayWork* work, u8 idx);
void UpdateReloadGageAnims(ReloadGauge* p, CardDisplayWork* work);
void SetReloadGageIdleFrames(ReloadGauge* p, CardDisplayWork* work);
void AdvanceReloadGageAnim(ReloadGauge* p, CardDisplayWork* work);
void ResetReloadGageAnim(ReloadGauge* p);

#endif
