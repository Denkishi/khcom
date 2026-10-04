#ifndef GUARD_ROOM_NAME_H
#define GUARD_ROOM_NAME_H

#include "types.h"
#include "text_types.h"

typedef struct RoomNameWork {
    void* tiles;
    void* palette;
    void* gfx;
    s32 x2;
    s32 y2;
    s32 x;
    s32 y;
    s32 scaleY;
    s32 unk_20;
    s32 unk_24;
    u8 state;
    u8 unk_29;
    u16 timer;
    u16 unk_2C;
    u8 unk_2E[0x2];
    s32 nameId;
    u8 textSlotCount;
    u8 unk_35[0x3];
    void* palette2;
    TextSlot textSlots[0x24];
} RoomNameWork;

void task_room_name_0(RoomNameWork* work, s32 arg);
u8 task_room_name_1(RoomNameWork* work);
void task_room_name_2(RoomNameWork* work);
void task_room_name_3(RoomNameWork* work);

#endif /* GUARD_ROOM_NAME_H */
