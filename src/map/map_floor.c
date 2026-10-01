#include "monsgage.h"
#include "map_tasks.h"
#include "sprites_map.h"
#include "sprites_map_tasks.h"
#include "sprite_palettes.h"
#include "common_text.h"
#include "field_state.h"
#include "game_state.h"
#include "map.h"
#include "map_text_data.h"
#include "obj_api.h"
#include "registration_data.h"
#include "taskpool.h"
#include "text.h"
#include "types.h"
#include <stddef.h>

extern const MapNameText* gFloorNames[13];
extern const MapNameText* gBasementFloorNames[12];

const void* GetFloorName() {
#ifdef VERSION_EU
    if (gGameState.flags & GAME_FLAG_RIKU) {
        return eu_0805E924(gBasementFloorNames[gGameState.floor]);
    }

    return eu_0805E924(gFloorNames[gGameState.floor]);
#else
    if (gGameState.flags & GAME_FLAG_RIKU) {
        return gBasementFloorNames[gGameState.floor];
    }

    return gFloorNames[gGameState.floor];
#endif
}

void Task_MapFloor_0(MapFloorWork* w) {
    gFieldState->flags |= FIELD_FLAG_FREEZE_PLAYER;
    gFieldState->flags |= FIELD_FLAG_FREEZE_ENEMIES;
    w->tiles = LoadObjTiles(gUnk_0993AF64, 0x800);
    w->palette = LoadObjPalette(gUnk_099910C4, 32);
    w->gfx = gUnk_09EF8DA4[0];
    w->timer = 120;
#ifdef VERSION_EU
    InitTextSlots(w->textSlots, 60);
#else
    InitTextSlots(w->textSlots, 40);
#endif
    w->palette2 = LoadTextPalette(1);
    w->textSlotCount = LoadTextSlots(GetFloorName(), w->textSlots);
    w->textX = (240 - GetTextSlotsWidth(w->textSlots, w->textSlotCount)) / 2;
}

s32 Task_MapFloor_1(MapFloorWork* w) {
    u16* p = &w->timer;

    if (*p != 0) {
        (*p)--;
        return 1;
    }

    return 0;
}

void Task_MapFloor_2(MapFloorWork* w) {
    DrawSprite(120, 138, w->gfx, w->tiles, w->palette, NULL, 0, 0x3C);
    DrawTextSlots(w->textX, 0x85, w->textSlots, w->palette2, 50, w->textSlotCount);
}

void Task_MapFloor_3(MapFloorWork* w) {
    ReleaseObjPalette(w->palette);
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette2);
#ifdef VERSION_EU
    FreeTextSlots(w->textSlots, 60);
#else
    FreeTextSlots(w->textSlots, 40);
#endif
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_ENEMIES;
    gFieldState->flags &= ~FIELD_FLAG_FREEZE_PLAYER;
}

const MapNameText* gFloorNames[13] = {
#if defined(VERSION_US)
    gMapNameTextUs_0815B5F6,
    gMapNameTextUs_0815B630,
    gMapNameTextUs_0815B66C,
    gMapNameTextUs_0815B6A6,
    gMapNameTextUs_0815B6E2,
    gMapNameTextUs_0815B71C,
    gMapNameTextUs_0815B756,
    gMapNameTextUs_0815B794,
    gMapNameTextUs_0815B7D0,
    gMapNameTextUs_0815B80A,
    gMapNameTextUs_0815B844,
    gMapNameTextUs_0815B884,
    gMapNameTextUs_0815B8C2,
#elif defined(VERSION_JP)
    gMapNameTextJp_0814F52C,
    gMapNameTextJp_0814F53C,
    gMapNameTextJp_0814F54C,
    gMapNameTextJp_0814F55C,
    gMapNameTextJp_0814F56C,
    gMapNameTextJp_0814F57C,
    gMapNameTextJp_0814F58C,
    gMapNameTextJp_0814F59C,
    gMapNameTextJp_0814F5AC,
    gMapNameTextJp_0814F5BC,
    gMapNameTextJp_0814F5D0,
    gMapNameTextJp_0814F5E4,
    gMapNameTextJp_0814F5F8,
#elif defined(VERSION_EU)
    &gMapNameEu_08893480,
    &gMapNameEu_0889352C,
    &gMapNameEu_088935D8,
    &gMapNameEu_08893684,
    &gMapNameEu_08893730,
    &gMapNameEu_088937DC,
    &gMapNameEu_0889388C,
    &gMapNameEu_08893938,
    &gMapNameEu_088939E4,
    &gMapNameEu_08893A94,
    &gMapNameEu_08893B48,
    &gMapNameEu_08893BFC,
    &gMapNameEu_08893CB8,
#endif
};

const MapNameText* gBasementFloorNames[12] = {
#if defined(VERSION_US)
    gMapNameTextUs_0815B906,
    gMapNameTextUs_0815B948,
    gMapNameTextUs_0815B98A,
    gMapNameTextUs_0815B9C6,
    gMapNameTextUs_0815BA04,
    gMapNameTextUs_0815BA44,
    gMapNameTextUs_0815BA84,
    gMapNameTextUs_0815BAC0,
    gMapNameTextUs_0815BAFE,
    gMapNameTextUs_0815BB3C,
    gMapNameTextUs_0815BB7C,
    gMapNameTextUs_0815BBB8,
#elif defined(VERSION_JP)
    gMapNameTextJp_0814F60C,
    gMapNameTextJp_0814F624,
    gMapNameTextJp_0814F63C,
    gMapNameTextJp_0814F654,
    gMapNameTextJp_0814F668,
    gMapNameTextJp_0814F67C,
    gMapNameTextJp_0814F690,
    gMapNameTextJp_0814F6A4,
    gMapNameTextJp_0814F6B8,
    gMapNameTextJp_0814F6CC,
    gMapNameTextJp_0814F6E0,
    gMapNameTextJp_0814F6F4,
#elif defined(VERSION_EU)
    &gMapNameEu_08893D78,
    &gMapNameEu_08893E38,
    &gMapNameEu_08893EF4,
    &gMapNameEu_08893FAC,
    &gMapNameEu_08894068,
    &gMapNameEu_08894124,
    &gMapNameEu_088941DC,
    &gMapNameEu_08894294,
    &gMapNameEu_0889434C,
    &gMapNameEu_08894408,
    &gMapNameEu_088944C0,
    &gMapNameEu_08894578,
#endif
};

TaskDesc gTaskDescMapFloor = {
    "Task_MapFloor",
    (TaskInitFunc)Task_MapFloor_0,
    (TaskUpdateFunc)Task_MapFloor_1,
    (TaskDrawFunc)Task_MapFloor_2,
    (TaskDestroyFunc)Task_MapFloor_3,
    sizeof(MapFloorWork),
};
