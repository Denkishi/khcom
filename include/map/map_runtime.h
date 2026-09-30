#ifndef GUARD_MAP_RUNTIME_H
#define GUARD_MAP_RUNTIME_H

#include "map_types.h"
#include "text_types.h"

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
void SetHallDefaultSpawn(void);
void UpdateWorldFriendFlags(void);
MapFloorDef* GetMapFloorDef(u8 a);
u8* GetMapRoomLinks(u8 a);
MapEventDoor* GetMapEventDoor(u8 a);
MapFloorRoom* GetMapFloorRoom(u8 index);
u8 GetMapRoomLink(u8 a, u8 b);
u16 GetMapDoorFlags(u8 a, u8 b);
void UpdateGameWorld(void);
void SetWorldJiminyFlags(void);
void SetFloorJiminyFlags(void);
void AdvanceFloorStory(void);
void AdvanceToExitHall(void);
u8 func_080DF49C(void);
u8 GetCurrentEventDoorKeyKind(void);
u8 SelectCurrentEventDoor(void);
u8 GetEventRoomKind(u8 a);
s32 GetMapRoomCardValue(u8 a);
void SetCardlessRoomType(u8 a);
u8 GetRandomRoomType(void);
void CreateMapRoom(u8 a, UnkStruct_080DF640* p);
void LoadMapRoomState(MapRoomState* p, u8 a);
void SetCurrentMapRoom(u8 a, u8 b);
u8 GetProgressFloor(void);
void* GetMapWorldName(u8 index);
void EnterEntranceHall(void);
void EnterExitHall(void);
void InitMapFloorState(u8 a, u8 b);
void MarkPastEventRoomsDone(void);
void GoToFloor(u8 a);
void GoToNextFloor(void);
void GoToPreviousFloor(void);
void WarpToFloor(u8 a);
void SetFloorWorld(u8 a);
void EnterFloorWorld(void);
void StoreMapFloorState(void);
void InitStartFloor(u8 a, u8 b);
void ResetMapFloors(void);
MapDoor* GetMapDoor(u8 a);
MapCell* FieldCellAt(s32 x, s32 y);
u8 IsFldPosBlocked(FldPos* p);
u8 GetMapWalkOutMode(void);
void EndMapWalkOut(void);
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
