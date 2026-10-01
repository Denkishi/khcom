#ifndef GUARD_ALLMAP_H
#define GUARD_ALLMAP_H

#include "obj.h"
#include "allmap_types.h"
#include "types.h"
#include "text_types.h"
#include "taskpool.h"
#include "anim.h"
#include "card_ui_types.h"

#ifdef VERSION_EU
#define ALLMAP_ROOMNAME_TEXT_SLOTS 36
#else
#define ALLMAP_ROOMNAME_TEXT_SLOTS 24
#endif

typedef struct AllmapRoomnameWork {
    TextSlot textSlots[ALLMAP_ROOMNAME_TEXT_SLOTS + 1];
    void* palette;
    u8 textSlotCount;
    u8 unk_0CD;
    u16 x;
} AllmapRoomnameWork;

typedef struct AllmapRoomArg {
    u32 x : 16;
    u32 y : 16;
    u32 room : 8;
    u32 unk_05 : 8;
    u32 asSprite : 16;
} AllmapRoomArg;

typedef struct AllmapBarWork {
    void* tiles;
    void* tiles2;
    void* palette;
    u16 steps;
    u8 unk_0E[0x02];
    s32 y;
    s32 targetY;
    s32 y2;
    s32 targetY2;
    s32 x;
    s32 targetX;
    u32 state;
    u8 closing;
    u8 fadeStarted;
    u8 unk_2E[0x802];
} AllmapBarWork;

typedef struct AllmapCursorPos {
    u16 x;
    u16 y;
} AllmapCursorPos;

typedef struct AllmapCursorWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s16 screenX;
    s16 screenY;
    s32 dropY;
    s32 dropTargetY;
    AllmapCursorPos pos;
    s32 x;
    s32 y;
    s32 drawX;
    s32 drawY;
    u16 moveSteps;
    u8 unk_46[0x02];
} AllmapCursorWork;

typedef struct AllmapState {
    TaskPool tasks;
    Task* roomTasks[32];
    Task* cursorTask;
    Task* roomnameTask;
    Task* pushaTask;
    s16 scrollX;
    s16 scrollY;
    s32 introScrollY;
    s32 introTargetY;
    s16 originX;
    s16 originY;
    s16 width;
    s16 height;
    u16 minX;
    u16 maxX;
    u16 minY;
    u16 maxY;
    s32 unk_BC;
    u8 lastRoom;
    u8 unk_C1[0x03];
} AllmapState;

typedef struct AllmapDoorinfoWork {
    AllmapCursorPos pos;
    u8 room;
    u8 unk_005[0x03];
    void* gfx2[4];
    void* tiles;
    EventKeyCard doors[4];
    ObjPalette* palette;
    void* tiles2;
    ObjPalette* palette2;
    void* gfx;
    s16 roomX;
    s16 roomY;
    u16 steps;
    u8 unk_102[0x02];
    s32 x;
    s32 y;
    s32 targetX;
    s32 targetY;
    u16 count;
    u8 closing;
    u8 unk_117;
} AllmapDoorinfoWork;

typedef struct AllmapPushaWork {
    void* tiles;
    void* palette;
    void* gfx;
    AllmapCursorWork* cursor;
    u16 angle;
    s16 y2;
    TaskPool tasks;
    Task* task;
    s16 x;
    s16 y;
} AllmapPushaWork;

void AllmapUpdateCamera(AllmapState* s);
void AllmapHandleInput();
void func_080D53F8();
void AllmapSetBounds(u16 a, u16 b, u16 c, u16 d);
u8 func_080D3A70(u8 a, u8 b);
u8 func_080D3AB8(u8 a, u8 b);
s16 AllmapDrawRoomnameFrame(u16 a);
s32 GetAllmapRoomnamePaletteOffset(u8 a);
void AllmapClearRoomnameFrame();
void AllmapBarStartClose(AllmapBarWork* work);
void AllmapBarFadeOut(AllmapBarWork* work);
u8 AllmapHasDoorInfo(AllmapCursorPos a);
void AllmapDoorinfoLoadDoors(AllmapDoorinfoWork* work);
void AllmapDoorinfoLoadKeys(AllmapDoorinfoWork* work);
void AllmapDoorinfoDrawDoors(AllmapDoorinfoWork* work);
void AllmapDoorinfoDrawKeys(AllmapDoorinfoWork* work);
u8 IsStockMesDispActive();
s32 GetAllmapRoomAt(AllmapCursorPos a);
void AllmapAddRoom(u8 a, u16 b, u16 c);

extern u8 gUnk_05000160[];
extern u8 gUnk_0976D880[];
extern u8 gUnk_0976DB68[];
extern u8 gUnk_0976DB9C[];
extern u8 gUnk_0976DC9C[];
extern u8 gUnk_0984A078[];
extern u8 gUnk_0984A0F8[];
extern u8 gUnk_0984A118[];
extern u8 gUnk_0984A138[];
extern u8 gUnk_0984A1D8[];
extern u8 gUnk_09618D38[];

extern u8 gAllmapCursorRoom;
extern s16 gAllmapCameraY;
extern s16 gAllmapCameraX;

void task_allmap_room_0(AllmapRoomWork* work, AllmapRoomArg* arg);
s32 task_allmap_room_1();
void task_allmap_room_2(AllmapRoomWork* work);
void task_allmap_room_3(AllmapRoomWork* work);
void task_allmap_cursor_0(AllmapCursorWork* work, AllmapCursorPos* arg);
s32 task_allmap_cursor_1(AllmapCursorWork* work);
void task_allmap_cursor_2(AllmapCursorWork* work);
void task_allmap_cursor_3(AllmapCursorWork* work);
void task_allmap_roomname_0(AllmapRoomnameWork* work, u8* arg);
s32 task_allmap_roomname_1();
void task_allmap_roomname_2(AllmapRoomnameWork* work);
void task_allmap_roomname_3(AllmapRoomnameWork* work);
void task_allmap_bar_0(AllmapBarWork* work);
s32 task_allmap_bar_1(AllmapBarWork* work);
void task_allmap_bar_2(AllmapBarWork* work);
void task_allmap_bar_3(AllmapBarWork* work);

#endif /* GUARD_ALLMAP_H */
