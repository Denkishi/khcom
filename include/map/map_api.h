#ifndef GUARD_MAP_API_H
#define GUARD_MAP_API_H

#include "types.h"
#include "map_types.h"
#include "fld_types.h"

struct EventKey;
struct MapCardAttributes;
struct PrizeEntry;
struct MapCell;
struct MapProgress;

s32 GetFldPosGround(FldPos* p);
void FldPosInitGround(FldPos* p);
s32 GetLedgeAngleAt(s32 x, s32 y, s32 z);
void MapSetCameraTarget(s32 x, s32 y);
void MapMoveCameraTarget(s32 dx, s32 dy);
void SetMapAttackBox(s32 x, s32 y, s32 z);
void MapFreezeBg1();
FldObj* GetMapRoomDoor();
void RequestMapMode();
void ReturnToMap(u8 a);
struct MapCell* MapCellAt(s16 x, s16 y);
u8* GetMapRoomEvent(u8 a);
void LoadMapForm(u8 a);
MapDoor* MapGetDoor(u8 a);
struct MapCell* MapFixCellAt(s16 a, s16 b);
u8 MapCellMaskBitAt(struct MapCell* p, s32 x, s32 y);
u8 SelectEventDoor(u8 a, u8 b);
u8 CountRemainingEventKeys();
struct EventKey* GetEventKey(u8 a);
u8 DoorAcceptsMapCard(struct MapCardAttributes* p);
s32 PayEventKey(struct PrizeEntry* p);
u8 AreWorldPrizesCollected();
void CopyMapProgress(struct MapProgress* p);
void RestoreMapProgress(struct MapProgress* p);

struct MapGmkPlacement;

extern MapRoomState* gMapRoomState;
extern MapFloorState gMapFloorState;
extern MapFormDef gMapForm;
extern struct MapGmkPlacement* gMapGmkPlacements;

#endif
