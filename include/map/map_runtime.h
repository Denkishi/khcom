#ifndef GUARD_MAP_RUNTIME_H
#define GUARD_MAP_RUNTIME_H

#include "map_types.h"
#include "text_types.h"
#include "fld_types.h"
#include "types.h"

typedef struct MapFloorDef {
    u8 entryRoom;
    u8 exitRoom;
    u8 unk_02;
    u8 unk_03;
    u8* links;
    MapEventDoor* eventDoors;
} MapFloorDef;

typedef struct UnkStruct_080DF640 {
    u16 kind;
    u16 value;
} UnkStruct_080DF640;

u8 GetOppositeDoorSide(u8 a);
void MarkEventRoomDone(MapEventDoor* p);
void SetHallDefaultSpawn();
void UpdateWorldFriendFlags();
MapFloorDef* GetMapFloorDef(u8 a);
u8* GetMapRoomLinks(u8 a);
MapEventDoor* GetMapEventDoor(u8 a);
MapFloorRoom* GetMapFloorRoom(u8 index);
u8 GetMapRoomLink(u8 a, u8 b);
u16 GetMapDoorFlags(u8 a, u8 b);
void UpdateGameWorld();
void SetWorldJiminyFlags();
void SetFloorJiminyFlags();
void AdvanceFloorStory();
void AdvanceToExitHall();
u8 func_080DF49C();
u8 GetCurrentEventDoorKeyKind();
u8 SelectCurrentEventDoor();
u8 GetEventRoomKind(u8 a);
s32 GetMapRoomCardValue(u8 a);
void SetCardlessRoomType(u8 a);
u8 GetRandomRoomType();
void CreateMapRoom(u8 a, UnkStruct_080DF640* p);
void LoadMapRoomState(MapRoomState* p, u8 a);
void SetCurrentMapRoom(u8 a, u8 b);
u8 GetProgressFloor();
void* GetMapWorldName(u8 index);
void EnterEntranceHall();
void EnterExitHall();
void InitMapFloorState(u8 a, u8 b);
void MarkPastEventRoomsDone();
void GoToFloor(u8 a);
void GoToNextFloor();
void GoToPreviousFloor();
void WarpToFloor(u8 a);
void SetFloorWorld(u8 a);
void EnterFloorWorld();
void StoreMapFloorState();
void InitStartFloor(u8 a, u8 b);
void ResetMapFloors();
MapDoor* GetMapDoor(u8 a);
MapCell* FieldCellAt(s32 x, s32 y);
u8 IsFldPosBlocked(FldPos* p);
u8 GetMapWalkOutMode();
void EndMapWalkOut();
u8 FldPosRevertIfBlocked(FldPos* p, s32 x, s32 y);
u8 MapFindOpenDoor(FldPos* p);
u8 IsAtTargetDoor(FldPos* p);
u8 _080DFE1C(FldPos* p);
s32 func_080DFE7C(s32 x, s32 y, s32 z);

#ifdef VERSION_EU
extern const LocalizedText gMapWorldNameEu_088926FC;
#endif

extern MapFloorDef gUnk_0984C868[];
extern MapFloorDef gUnk_0984CBD0[];

#endif
