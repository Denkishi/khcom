#ifndef GUARD_MODE_ALLMAP_API_H
#define GUARD_MODE_ALLMAP_API_H

#include "types.h"

struct AllmapRoomWork;

void SetAllmapReturnToMenu(u8 a);
u8 AllmapDoorExists(u8 a, u8 b);
u8 AllmapDoorIsOpen(u8 a, u8 b);
s32 SetupAllmapRoomDoors(struct AllmapRoomWork* work);

extern u16* gAllmapBg0MapBlocks[8];
extern u32 gAllmapModeState;
extern u16* gAllmapBg1Map;
extern u16 gAllmapCursorDropTimer;
extern u16* gAllmapBg1MapBlocks[8];
extern u16* gAllmapBg0Map;
extern u16 gAllmapScrollInTimer;

#endif
