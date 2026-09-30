#include "macros.h"
#include "localized_resource_assets.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "task.h"
#include "obj_api.h"
#include "allmap.h"
#include "gba/keys.h"
#include "allmap_api.h"
#include "sprites_allmap.h"
#include "sprites_card_pictures.h"
#include "engine_math.h"
#include "card_api.h"
#include "malloc.h"
#include "fade.h"
#include "mode_allmap_api.h"
#include "map_runtime.h"
#include "songs.h"
#include <string.h>

u8 gAllmapCursorRoom EWRAM_COMMON(4);
s16 gAllmapCameraY EWRAM_COMMON(4);
s16 gAllmapCameraX EWRAM_COMMON(4);

static TaskDesc sTaskDescAllmapRoom = {
    "task_allmap_room",
    (TaskInitFunc)task_allmap_room_0,
    (TaskUpdateFunc)task_allmap_room_1,
    (TaskDrawFunc)task_allmap_room_2,
    (TaskDestroyFunc)task_allmap_room_3,
    sizeof(AllmapRoomWork),
};

static TaskDesc sTaskDescAllmapCursor = {
    "task_allmap_cursor",
    (TaskInitFunc)task_allmap_cursor_0,
    (TaskUpdateFunc)task_allmap_cursor_1,
    (TaskDrawFunc)task_allmap_cursor_2,
    (TaskDestroyFunc)task_allmap_cursor_3,
    sizeof(AllmapCursorWork),
};

static TaskDesc sTaskDescAllmapRoomname = {
    "task_allmap_roomname",
    (TaskInitFunc)task_allmap_roomname_0,
    (TaskUpdateFunc)task_allmap_roomname_1,
    (TaskDrawFunc)task_allmap_roomname_2,
    (TaskDestroyFunc)task_allmap_roomname_3,
    sizeof(AllmapRoomnameWork),
};

#ifdef VERSION_EU
static void* sAllmapBarSprites[5] = {
    gUnkEu_09738538,
    gUnkEu_09738554,
    gUnkEu_09738590,
    gUnkEu_0973857A,
    gUnkEu_09738564,
};

static void* sUnkEu_09F80138[5] = {
    gUnkEu_0980F840,
    gUnkEu_0980FD40,
    gUnkEu_09810C40,
    gUnkEu_09810740,
    gUnkEu_09810240,
};
#endif

TaskDesc gTaskDescAllmapBar = {
    "task_allmap_bar",
    (TaskInitFunc)task_allmap_bar_0,
    (TaskUpdateFunc)task_allmap_bar_1,
    (TaskDrawFunc)task_allmap_bar_2,
    (TaskDestroyFunc)task_allmap_bar_3,
    sizeof(AllmapBarWork),
};

static const s16 sAllmapDoorCardOffsets[4][2] = {
    {-24, 48},
    {56, 48},
    {56, -19},
    {-24, -19},
};

const s16 gUnk_096FDC20[4][2] = {
    {16, -16},
    {-16, -16},
    {-16, 16},
    {16, 16},
};

static const u16 sAllmapDirDeltas[4][2] = {
    {0xFFFF, 1},
    {1, 1},
    {1, 0xFFFF},
    {0xFFFF, 0xFFFF},
};

static const u32 sAllmapReverseDoors[4] = {0, 3, 1, 2};

static const s16 sAllmapKeyCardX[4][4] = {
    {120, 0, 0, 0},
    {104, 136, 0, 0},
    {88, 120, 152, 0},
    {72, 104, 136, 168},
};

static s32 sAllmapDoorOffsetX;
static s32 sAllmapDoorOffsetY;
static s32 sAllmapCameraFixedX;
static s32 sAllmapCameraFixedY;

void task_allmap_room_0(AllmapRoomWork* work, AllmapRoomArg* arg) {
    void* pal;

    work->x = arg->x;
    work->y = arg->y;
    work->unk_090 = -arg->y << 8;
    work->unk_094 = arg->y << 8;
    work->room = arg->room;
    work->asSprite = arg->asSprite;
    work->shape = SetupAllmapRoomDoors(work);

    if (work->asSprite == 0) {
        work->tiles = LoadObjTiles(gUnk_0976B340, 0x2400);
        work->gfx2 = 0;
    } else {
        work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF6424, 17), gUnk_0976B340);
        work->gfx2 = gUnk_09EF6424[work->shape];
    }

    if (work->asSprite == 0 && work->room == gMapFloorState.room) {
        pal = gUnk_0984A138;
    } else {
        pal = gUnk_0984A0F8 + GetAllmapRoomPaletteOffset(work->room);
    }
    work->palette = LoadObjPalette(pal, 32);
}

s32 task_allmap_room_1(void) {
    return 1;
}

void task_allmap_room_2(AllmapRoomWork* work) {
    s32 i;
    s16 x;
    s16 y;
    u16 g;
    u16 h;

    if (work->asSprite == 0) {
        x = work->x * 24 - gAllmapCameraX;
        y = work->y * 24 - gAllmapCameraY;
        g = 0x800;
        h = -4100 - work->y * 4;
    } else {
        if ((gFieldState->flags & 0x40000) != 0) {
            return;
        }
        x = work->x;
        y = work->y;
        g = 0;
        h = 80;
    }

    if (x < -32 || x > 240) {
        return;
    }

    if (y < -32) {
        return;
    }

    if (y > 160) {
        return;
    }

    if (work->gfx2 != NULL) {
        DrawSprite(x, y, work->gfx2, work->tiles, work->palette, 0, g, h);
    }

    for (i = 0; i < 4; i++) {
        if (work->gfx[i] != NULL) {
            work->gfx[i] = AnimUpdate(&work->anim[i]);
            DrawSprite(x, y, work->gfx[i], work->tiles2[i], work->palette, 0, g, i - 4 + h);
        }
    }
}

void task_allmap_room_3(AllmapRoomWork* work) {
    s32 i;

    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);

    for (i = 0; i < 4; i++) {
        if (work->tiles2[i] != NULL) {
            ReleaseObjTiles(work->tiles2[i]);
        }
    }
}

void* CreateAllmapRoomTask(TaskPool* pool) {
    AllmapRoomArg arg;

    arg.x = 208;
    arg.y = 0;
    arg.room = gMapFloorState.room;
    arg.asSprite = 1;
    return TaskCreate(pool, &sTaskDescAllmapRoom, &arg);
}

u8 func_080D3A70(u8 a, u8 b) {
    if (GetEventRoomKind(a) != 0) {
        if (TestAllmapRoomFlag(a, 8) != 0) {
            return 0;
        }
    }

    if (TestAllmapRoomFlag(a, 2) != 0) {
        return func_080D3564(a, b);
    }
    return 0;
}

u8 func_080D3AB8(u8 a, u8 b) {
    if (GetEventRoomKind(a) == 0) {
        if (TestAllmapRoomFlag(a, 2) == 0) {
            return 0;
        }
    } else {
        if (TestAllmapRoomFlag(a, 8) != 0) {
            return 0;
        }
        if (TestAllmapRoomFlag(a, 2) == 0) {
            return 0;
        }
    }

    if (func_080D3564(a, b) != 0) {
        return func_080D358C(a, b) == 0;
    }

    return 0;
}

void task_allmap_cursor_0(AllmapCursorWork* work, AllmapCursorPos* arg) {
    work->pos = *arg;
    work->screenX = work->pos.x * 24 + 16 - gAllmapCameraX;
    work->screenY = work->pos.y * 24 + 11 - gAllmapCameraY;
    work->dropY = -work->screenY << 8;
    work->dropTargetY = work->screenY << 8;
    work->x = work->drawX = work->screenX << 8;
    work->y = work->drawY = work->screenY << 8;
    work->tiles = LoadObjTiles(gUnk_0976D7C0, 0xC0);
    work->palette = LoadObjPalette(gUnk_0984A1D8, 32);
    AnimInit(&work->anim, gUnk_09EF64C4, gUnk_09EF64B4);
    AnimStart(&work->anim, 0, 1);
    work->gfx = AnimGetGfx(&work->anim);
    work->moveSteps = 0;
}

s32 task_allmap_cursor_1(AllmapCursorWork* work) {
    s32 x;
    s32 y;

    if (gAllmapModeState == 2) {
        if (gAllmapCursorDropTimer > 6) {
            ApproachValue(&work->dropY, work->dropTargetY, gAllmapCursorDropTimer - 7);
        } else if (gAllmapCursorDropTimer > 3) {
            ApproachValueHalfSteps(&work->dropY, work->dropTargetY - 0x800, gAllmapCursorDropTimer - 3);
        } else {
            ApproachValueHalfSteps(&work->dropY, work->dropTargetY, gAllmapCursorDropTimer);
        }
    }

    if (gAllmapModeState != 3) {
        work->gfx = gUnk_09EF64B4[0];
        return 1;
    }
    work->gfx = AnimUpdate(&work->anim);
    x = (work->pos.x * 24 + 16 - gAllmapCameraX) << 8;
    y = (work->pos.y * 24 + 11 - gAllmapCameraY) << 8;
    if (x != work->x || y != work->y) {
        work->x = x;
        work->y = y;
        work->moveSteps = 4;
    }

    if (work->moveSteps != 0) {
        ApproachValue(&work->drawX, work->x, work->moveSteps);
        ApproachValue(&work->drawY, work->y, work->moveSteps);
        work->moveSteps--;
    }
    return 1;
}

void task_allmap_cursor_2(AllmapCursorWork* work) {
    s16 x;
    s16 y;

    if (IsStockMesDispActive() != 0) {
        return;
    }

    if (gAllmapModeState != 3) {
        x = work->screenX;
        y = work->dropY >> 8;
    } else {
        x = work->drawX >> 8;
        y = work->drawY >> 8;
    }
    DrawSprite(x - 15, y - 22, work->gfx, work->tiles, work->palette, 0, 0, 49);
}

void task_allmap_cursor_3(AllmapCursorWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

s16 AllmapDrawRoomnameFrame(u16 a) {
    u8* base;
    u8* p;
    s16 v;
    s16 q;
    u8* dst;

    v = 120 - a;

    if (v < 0) {
        v = 0;
    }
    q = v / 8;
    base = GetBgScreenBase(2);
    dst = base + 28;
    p = gUnk_0983B7B4 - q * 2;
    RequestDma3Copy(p, dst, 32);
    dst = base + 92;
    p += 64;
    RequestDma3Copy(p, dst, 32);
    dst = base + 156;
    p += 64;
    RequestDma3Copy(p, dst, 32);
    return v - v % 8 / 2;
}
s32 GetAllmapRoomnamePaletteOffset(u8 a) {
    switch (GetRoomCardBackIndex(a)) {
    case 1:
        return 64;
    case 2:
        return 96;
    case 4:
        return 0;
    case 0:
    case 3:
    default:
        return 32;
    }
}

void task_allmap_roomname_0(AllmapRoomnameWork* work, u8* arg) {
    u16 pal;

    InitTextSlots(work->textSlots, ALLMAP_ROOMNAME_TEXT_SLOTS);
    work->textSlotCount = LoadTextSlots(GetRoomName(arg[0]), work->textSlots);
    pal = GetAllmapRoomnamePaletteOffset(arg[0]);
    work->palette = LoadObjPalette(gUnk_0984A1F8 + pal, 32);
    LoadPalette(gUnk_0984A078 + pal, gUnk_05000160, 32);
    work->x = AllmapDrawRoomnameFrame(GetTextSlotsWidth(work->textSlots, work->textSlotCount));
}

s32 task_allmap_roomname_1(void) {
    return 1;
}

void task_allmap_roomname_2(AllmapRoomnameWork* work) {
    DrawTextSlots(work->x + 117, 3, work->textSlots, work->palette, 50, work->textSlotCount);
}

void task_allmap_roomname_3(AllmapRoomnameWork* work) {
    FreeTextSlots(work->textSlots, ALLMAP_ROOMNAME_TEXT_SLOTS);
    ReleaseObjPalette(work->palette);
}

void AllmapClearRoomnameFrame(void) {
    u8* base;
    u8* p;
    u8* dst;

    base = GetBgScreenBase(2);
    dst = base + 28;
    p = (u8*)gUnk_08125E24;
    RequestDma3Copy(p, dst, 32);
    dst = base + 92;
    p += 64;
    RequestDma3Copy(p, dst, 32);
    dst = base + 156;
    p += 64;
    RequestDma3Copy(p, dst, 32);
}

void AllmapBarStartClose(AllmapBarWork* work) {
    work->closing = 1;

    if (work->state == 0) {
        work->state = 4;
    } else {
        work->state = 3;
    }

    if (work->steps == 0) {
        work->steps = 16;
    }
    LoadBgMap(3, gUnk_0983AD98, 0x500);
    work->targetY = -0x800;
    work->targetY2 = 0xA000;
    work->targetX = -0x8000;
}

void task_allmap_bar_0(AllmapBarWork* work) {
    gStockMesDispWork = work;
#ifdef VERSION_EU
    work->tiles = LoadObjTiles(gUnk_0976D8A6, 0xDC0);
#else
    work->tiles = LoadObjTiles(gUnk_0976D8A6, 0x2C0);
#endif
    work->tiles2 = LoadObjTiles(gUnk_0976DBDA, 0xC0);
    work->palette = LoadObjPalette(gUnk_0984A1D8, 32);
    work->steps = 16;
    work->state = 0;
    work->y = -0x800;
    work->y2 = 0xA000;
    work->x = -0x8000;
    work->targetY = 0;
    work->targetY2 = 0x9800;
    work->targetX = 0;
    work->closing = 0;
    work->fadeStarted = 0;
}

void AllmapBarFadeOut(AllmapBarWork* work) {
    FadeStartOut(0, 16);
    FadeLock();
}

s32 task_allmap_bar_1(AllmapBarWork* work) {
    s32 i;

    switch (work->state) {
    case 0:
        ApproachValue(&work->y, work->targetY, work->steps);
        ApproachValue(&work->y2, work->targetY2, work->steps);
        work->steps--;
        if (work->steps == 0) {
            work->steps = 16;
            work->state = 1;
        }
        break;
    case 1:
        ApproachValue(&work->x, work->targetX, work->steps);
        work->steps--;
        if (work->steps == 0) {
#ifdef VERSION_EU
            LoadBgMap(3, sUnkEu_09F80138[gLanguage], 0x500);
#else
            LoadBgMap(3, gUnk_0983B298, 0x500);
#endif
            work->state = 2;
            gAllmapModeState = 2;
        }
        break;
    case 3:
        ApproachValue(&work->x, work->targetX, work->steps);
        work->steps--;
        if (work->steps == 0) {
            work->steps = 16;
            work->state = 4;
        }
        break;
    case 4:
        if (FadeIsActive() == 0 && work->fadeStarted == 0) {
            for (i = 0; i < 32; i++) {
                FadeSetPaletteExcluded(i, 0);
            }
            AllmapBarFadeOut(work);
            work->fadeStarted = 1;
        }
        ApproachValue(&work->y, work->targetY, work->steps);
        ApproachValue(&work->y2, work->targetY2, work->steps);
        work->steps--;
        if (work->steps == 0) {
            gAllmapModeState = 0;
            return 0;
        }
        break;
    case 2:
        if (work->closing != 0) {
            break;
        }

        if (gAllmapModeState != 3) {
            break;
        }

        if ((GetKeysPressed() & START_BUTTON) != 0) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            AllmapBarFadeOut(work);
            gAllmapModeState = 0;
            AllmapClearRoomnameFrame();
            SetAllmapReturnToMenu(0);
            return 0;
        }

        if ((GetKeysPressed() & B_BUTTON) != 0 && IsStockMesDispActive() == 0) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            AllmapBarStartClose(work);
            gAllmapModeState = 1;
            AllmapClearRoomnameFrame();
            SetAllmapReturnToMenu(1);
        }
        break;
    }
    return 1;
}

void task_allmap_bar_2(AllmapBarWork* work) {
    if (work->state == 2) {
        return;
    }
#ifdef VERSION_EU
    DrawSprite(work->x >> 8, 0, sAllmapBarSprites[gLanguage], work->tiles, work->palette, 0,
        0xC00, 1000);
#else
    DrawSprite(work->x >> 8, 0, gUnk_0976D880, work->tiles, work->palette, 0, 0xC00, 1000);
#endif
    DrawSprite(128, work->y >> 8, gUnk_0976DB68, work->tiles2, work->palette, 0, 0xC00, 1001);
    DrawSprite(128, work->y2 >> 8, gUnk_0976DB9C, work->tiles2, work->palette, 0, 0xC00, 1002);
}

void task_allmap_bar_3(AllmapBarWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette);
}

u8 AllmapHasDoorInfo(AllmapCursorPos a) {
    AllmapCursorPos p;
    s32 i;
    u8 r;
    u8 v;

    for (i = 0; i < 4; i++) {
        p.x = a.x + sAllmapDirDeltas[i][0];
        p.y = a.y + sAllmapDirDeltas[i][1];
        r = GetAllmapRoomAt(p);
        if (r != 255) {
            if (GetEventRoomKind(GetAllmapRoomAt(a)) == 2) {
                v = func_080D3AB8(r, sAllmapReverseDoors[i]);
            } else {
                v = func_080D3A70(r, sAllmapReverseDoors[i]);
            }

            if (v != 0) {
                return 1;
            }
        }
    }
    return 0;
}

void AllmapDoorinfoLoadDoors(AllmapDoorinfoWork* work) {
    s32 i;
    AllmapCursorPos pos;
    u8 room;
    u8 n;

    work->count = 0;

    for (i = 0; i < 4; i++) {
        pos.x = work->pos.x + sAllmapDirDeltas[i][0];
        pos.y = work->pos.y + sAllmapDirDeltas[i][1];
        room = GetAllmapRoomAt(pos);

        if (room != 0xFF && func_080D3A70(room, sAllmapReverseDoors[i])) {
            n = GetMapRoomCardValue(room) + 1;

            if (n == 10) {
                n = 0;
            }

            work->doors[i].sprite.tiles = AllocKeyValueTiles(n);
            work->doors[i].sprite.palette = LoadObjPalette(gUnk_09618D38, 32);
            work->doors[i].sprite.gfx = 0;
            work->doors[i].sprite.tiles2 = LoadObjTiles(gUnk_0905E3BA, 0x600);
            work->doors[i].sprite.palette2 = LoadObjPalette(gUnk_09618D38, 32);
            work->doors[i].sprite.gfx2 = gUnk_09EE97F4[0];
            FadeSetPaletteExcluded(work->doors[i].sprite.palette->index + 16, 1);
            FadeSetPaletteExcluded(work->doors[i].sprite.palette2->index + 16, 1);
            work->gfx2[i] = gUnk_09EF64E8[i];
            work->count++;
        } else {
            work->gfx2[i] = 0;
        }
    }

    if (work->count != 0) {
        work->tiles = LoadObjTiles(gUnk_0976DD62, 0x80);
        work->palette = LoadObjPalette(gUnk_0984A1D8, 32);
        FadeSetPaletteExcluded(work->palette->index + 16, 1);
        work->tiles2 = LoadObjTiles(gUnk_0976B340, 0x2400);
        work->gfx = gUnk_09EF6424[0];
        InitObjPaletteAtSlot(work->palette2, 15, gUnk_0984A0F8, 32);
        FadeSetPaletteExcluded(work->palette2->index + 16, 1);
    }
}

s32 GetAllmapKeyCardX(u16 a, s32 b) {
    s16 tbl[4][4];

    memcpy(tbl, sAllmapKeyCardX, sizeof(tbl));
    return tbl[a - 1][b] << 8;
}

void AllmapDoorinfoLoadKeys(AllmapDoorinfoWork* work) {
    s32 i;
    AllmapCursorPos pos;
    u8 room;
    EventKeyCard* e;

    for (i = 0; i < 4; i++) {
        pos.x = work->pos.x + sAllmapDirDeltas[i][0];
        pos.y = work->pos.y + sAllmapDirDeltas[i][1];
        room = GetAllmapRoomAt(pos);

        if (room != 0xFF && func_080D3AB8(room, sAllmapReverseDoors[i])) {
            break;
        }
    }

    if (i == 4) {
        work->count = 0;
    } else {
        SelectEventDoor(work->room, sAllmapReverseDoors[i]);
        work->count = CountRemainingEventKeys();
    }

    for (i = 0; i < work->count; i++) {
        e = &work->doors[i];
        InitEventKeyCard(e, GetEventKey(i));
        SetLayeredCardSpritePos(GetAllmapKeyCardX(work->count, i), 0x6800, &e->sprite);

        if (work->doors[i].sprite.palette != NULL) {
            FadeSetPaletteExcluded(work->doors[i].sprite.palette->index + 16, 1);
        }

        if (work->doors[i].sprite.palette2 != NULL) {
            FadeSetPaletteExcluded(work->doors[i].sprite.palette2->index + 16, 1);
        }

        if (work->doors[i].sprite.palette3 != NULL) {
            FadeSetPaletteExcluded(work->doors[i].sprite.palette3->index + 16, 1);
        }
    }

    work->tiles2 = LoadObjTiles(gUnk_0976B340, 0x2400);

    if (GetEventRoomKind(work->room) == 1 || GetEventRoomKind(work->room) == 4) {
        work->gfx = gUnk_09EF6424[1];
        InitObjPaletteAtSlot(work->palette2, 15, gUnk_0984A118, 32);
    } else {
        work->gfx = gUnk_09EF6424[0];
        InitObjPaletteAtSlot(work->palette2, 15, gUnk_0984A0F8, 32);
    }

    FadeSetPaletteExcluded(work->palette2->index + 16, 1);
}

void task_allmap_doorinfo_0(AllmapDoorinfoWork* work, AllmapCursorPos* arg) {
    s32 i;

    for (i = 0; i < 32; i++) {
        FadeSetPaletteExcluded(i, 0);
    }
    work->palette2 = EwramAlloc(sizeof(ObjPalette));
    work->pos = *arg;
    work->room = GetAllmapRoomAt(*arg);
    work->roomX = work->pos.x * 24 - gAllmapCameraX;
    work->roomY = work->pos.y * 24 - gAllmapCameraY;
    work->targetX = 0x6800;

    if (GetEventRoomKind(work->room) == 1 || GetEventRoomKind(work->room) == 4 || GetEventRoomKind(work->room) == 2) {
        work->targetY = 0x2100;
        AllmapDoorinfoLoadKeys(work);
    } else {
        work->targetY = 0x4200;
        AllmapDoorinfoLoadDoors(work);
    }
    work->steps = 8;
    work->x = work->roomX << 8;
    work->y = work->roomY << 8;
    work->closing = 0;
    FadeToAmount(0, 14, 8);
}

s32 task_allmap_doorinfo_1(AllmapDoorinfoWork* work) {
    if ((GetKeysPressed() & B_BUTTON) != 0 && work->closing == 0) {
        work->closing = 1;
        m4aSongNumStart(SONG_SYS_CLOSE);
        work->steps = 8 - work->steps;
        work->targetX = work->roomX << 8;
        work->targetY = work->roomY << 8;
        FadeToOriginal(0, 8);
    }

    if (work->steps != 0) {
        ApproachValue(&work->x, work->targetX, work->steps);
        ApproachValue(&work->y, work->targetY, work->steps);
        work->steps--;
    }

    if (work->closing != 0 && work->steps == 0) {
        return 0;
    }
    return 1;
}

void AllmapDoorinfoDrawDoors(AllmapDoorinfoWork* work) {
    s32 i;

    if (gAllmapModeState == 0) {
        return;
    }

    for (i = 0; i < 4; i++) {
        if (work->gfx2[i] != NULL && work->steps == 0) {
            DrawSprite(work->x >> 8, work->y >> 8, work->gfx2[i], work->tiles, work->palette, 0, 0, i + 51);
            sAllmapDoorOffsetX = sAllmapDoorCardOffsets[i][0];
            sAllmapDoorOffsetY = sAllmapDoorCardOffsets[i][1];
            DrawSprite(sAllmapDoorOffsetX + (work->x >> 8), sAllmapDoorOffsetY + (work->y >> 8), work->doors[i].sprite.gfx, work->doors[i].sprite.tiles, work->doors[i].sprite.palette, 0, 0, i + 40);
            DrawSprite((work->x >> 8) + sAllmapDoorOffsetX, (work->y >> 8) + sAllmapDoorOffsetY, work->doors[i].sprite.gfx2, work->doors[i].sprite.tiles2, work->doors[i].sprite.palette2, 0, 0, i + 30);
        }
    }
    DrawSprite(work->x >> 8, work->y >> 8, work->gfx, work->tiles2, work->palette2, 0, 0, 20);
}

void AllmapDoorinfoDrawKeys(AllmapDoorinfoWork* work) {
    s32 i;

    if (work->steps == 0) {
        for (i = 0; i < work->count; i++) {
            DrawLayeredCardSprite(&work->doors[i].sprite, 0);
        }
    }
    DrawSprite(work->x >> 8, work->y >> 8, work->gfx, work->tiles2, work->palette2, 0, 0, 20);
}

void task_allmap_doorinfo_2(AllmapDoorinfoWork* work) {
    if (GetEventRoomKind(work->room) == 1 || GetEventRoomKind(work->room) == 4 || GetEventRoomKind(work->room) == 2) {
        AllmapDoorinfoDrawKeys(work);
    } else {
        AllmapDoorinfoDrawDoors(work);
    }
}

void task_allmap_doorinfo_3(AllmapDoorinfoWork* work) {
    s32 i;

    if (work->closing == 0) {
        FadeToOriginal(0, 8);
    }
    ReleaseObjTiles(work->tiles2);

    if (GetEventRoomKind(work->room) == 1 || GetEventRoomKind(work->room) == 4 || GetEventRoomKind(work->room) == 2) {
        for (i = 0; i < work->count; i++) {
            ReleaseLayeredCardSprite(&work->doors[i].sprite);
        }
    } else {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);

        for (i = 0; i < 4; i++) {
            if (work->gfx2[i] != NULL) {
                ReleaseObjTiles(work->doors[i].sprite.tiles);
                ReleaseObjPalette(work->doors[i].sprite.palette);
                ReleaseObjTiles(work->doors[i].sprite.tiles2);
                ReleaseObjPalette(work->doors[i].sprite.palette2);
            }
        }
    }

    for (i = 0; i < 32; i++) {
        FadeSetPaletteExcluded(i, 1);
    }
    FadeSetPaletteExcluded(10, 0);
    EwramFree(work->palette2);
}

void task_allmap_pusha_0(AllmapPushaWork* work, AllmapCursorWork* arg) {
    gStockMesDispWork = work;
    work->cursor = arg;
    work->x = arg->pos.x * 24 - gAllmapCameraX;
    work->y = arg->pos.y * 24 - gAllmapCameraY;
    work->tiles = LoadObjTiles(gUnk_0976DCB0, 0x80);
    work->palette = LoadObjPalette(gUnk_0984A1D8, 32);
    work->gfx = gUnk_0976DC9C;
    work->angle = 0;
    TaskPoolInit(&work->tasks, 1);
    work->task = 0;
}

s32 task_allmap_pusha_1(AllmapPushaWork* work) {
    if (IsStockMesDispActive() == 0 && (GetKeysPressed() & A_BUTTON) != 0) {
        m4aSongNumStart(SONG_SYS_KETTEI);
        work->task = TaskCreate(&work->tasks, &gTaskDescAllmapDoorinfo, &work->cursor->pos);
    }
    work->y2 = gSineTable[(u8)work->angle] >> 8;
    work->angle += 16;
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_allmap_pusha_2(AllmapPushaWork* work) {
    if (IsStockMesDispActive() != 0) {
        TaskPoolDraw(&work->tasks);
    } else {
        work->x = work->cursor->pos.x * 24 - gAllmapCameraX;
        work->y = work->cursor->pos.y * 24 - gAllmapCameraY;
        DrawSprite(work->x, work->y - work->y2 + 2, work->gfx, work->tiles, work->palette, 0, 0, 48);
    }
}

void task_allmap_pusha_3(AllmapPushaWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
    ClearStockMesDispWork();
}

u8 IsStockMesDispActive(void) {
    if (gStockMesDispWork == NULL || IsTaskActive(((AllmapPushaWork*)gStockMesDispWork)->task) == 0) {
        return 0;
    }
    return 1;
}

void ClearStockMesDispWork(void) {
    gStockMesDispWork = 0;
}

void AllmapDrawRoomTiles(s16 a, s16 b, s32 c, u8 d) {
    AllmapCursorPos p;
    u16* map;
    s16 x8;
    s16 y8;
    s32 i;
    s32 j;
    u8 room;
    u16 tile;
    s16 ofs;

    if ((a & 1) != 0) {
        map = gAllmapBg0Map;
    } else {
        map = gAllmapBg1Map;
    }
    x8 = (a * 24 - ((AllmapState*)gUnk_0203C4B4)->originX) / 8;
    y8 = (b * 24 - ((AllmapState*)gUnk_0203C4B4)->originY) / 8;
    p.x = a;
    p.y = b;
    room = GetAllmapRoomAt(p);
    tile = c * 16;

    if (TestAllmapRoomFlag(room, 8) != 0 || TestAllmapRoomFlag(room, 2) != 0 || AllmapHasDoorInfo(p) != 0) {
        if (d != 0) {
            tile += 0x2000;
        } else if (c == 1) {
            tile += 0x1000;
        } else if (c == 17) {
            tile += 0xF000;
        }
    } else if (c == 1 || c == 17) {
        tile += 0xF000;
    } else {
        tile += 0xE000;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            ofs = (y8 + i) / 32 * 2048 + (y8 + i) % 32 * 32 + (x8 + j) / 32 * 1024 + (x8 + j) % 32;
            map[ofs] = tile;
            tile++;
        }
    }
}
void InitAllmap(void) {
    s32 i;
    s32 j;
    AllmapCursorPos arg;
    AllmapRoomWork* w;
    AllmapRoomWork* c;
    void** state = &gUnk_0203C4B4;

    *state = EwramAlloc(sizeof(AllmapState));
    ((AllmapState*)gUnk_0203C4B4)->lastRoom = 0xFF;
    ((AllmapState*)gUnk_0203C4B4)->unk_BC = 0x400;
    gAllmapCursorRoom = gMapFloorState.room;
    TaskPoolInit(&((AllmapState*)gUnk_0203C4B4)->tasks, 35);
    ((AllmapState*)gUnk_0203C4B4)->pushaTask = 0;
    ((AllmapState*)gUnk_0203C4B4)->roomnameTask = 0;

    for (i = 0; i < 32; i++) {
        ((AllmapState*)gUnk_0203C4B4)->roomTasks[i] = 0;
    }

    ((AllmapState*)gUnk_0203C4B4)->minX = ((AllmapState*)gUnk_0203C4B4)->maxX = 32;
    ((AllmapState*)gUnk_0203C4B4)->minY = ((AllmapState*)gUnk_0203C4B4)->maxY = 32;
    AllmapAddRoom(0, 32, 32);
    ((AllmapState*)gUnk_0203C4B4)->scrollX = 0;
    ((AllmapState*)gUnk_0203C4B4)->scrollY = 0;
    AllmapSetBounds(((AllmapState*)gUnk_0203C4B4)->minX, ((AllmapState*)gUnk_0203C4B4)->maxX, ((AllmapState*)gUnk_0203C4B4)->minY, ((AllmapState*)gUnk_0203C4B4)->maxY);
    ((AllmapState*)gUnk_0203C4B4)->introScrollY = (((AllmapState*)gUnk_0203C4B4)->scrollY + 160) << 8;
    ((AllmapState*)gUnk_0203C4B4)->introTargetY = ((AllmapState*)gUnk_0203C4B4)->scrollY << 8;
    gAllmapCameraX = ((AllmapState*)gUnk_0203C4B4)->originX + ((AllmapState*)gUnk_0203C4B4)->scrollX;
    gAllmapCameraY = ((AllmapState*)gUnk_0203C4B4)->originY + ((AllmapState*)gUnk_0203C4B4)->scrollY;
    sAllmapCameraFixedX = (((AllmapState*)gUnk_0203C4B4)->originX + ((AllmapState*)gUnk_0203C4B4)->scrollX) << 8;
    sAllmapCameraFixedY = (((AllmapState*)gUnk_0203C4B4)->originY + ((AllmapState*)gUnk_0203C4B4)->scrollY) << 8;

    for (j = 0; j < 32; j++) {
        if (IsTaskActive(((AllmapState*)gUnk_0203C4B4)->roomTasks[j])) {
            w = ((AllmapState*)gUnk_0203C4B4)->roomTasks[j]->work;
            AllmapDrawRoomTiles(w->x, w->y, w->shape, j == gAllmapCursorRoom);
        }
    }

    RedrawBgMapAt(0, ((AllmapState*)gUnk_0203C4B4)->scrollX - ((AllmapState*)gUnk_0203C4B4)->originX % 8, ((AllmapState*)gUnk_0203C4B4)->scrollY - ((AllmapState*)gUnk_0203C4B4)->originY % 8);
    RedrawBgMapAt(1, ((AllmapState*)gUnk_0203C4B4)->scrollX - ((AllmapState*)gUnk_0203C4B4)->originX % 8, ((AllmapState*)gUnk_0203C4B4)->scrollY - ((AllmapState*)gUnk_0203C4B4)->originY % 8);
    c = ((AllmapState*)gUnk_0203C4B4)->roomTasks[gAllmapCursorRoom]->work;
    arg.x = c->x;
    arg.y = c->y;
    ((AllmapState*)gUnk_0203C4B4)->cursorTask = TaskCreate(gUnk_0203C4B4, &sTaskDescAllmapCursor, &arg);
    func_080D53F8();
}
void AllmapUpdateCamera(AllmapState* s) {
    s32 tx;
    s32 ty;
    s32 dx;
    s32 dy;
    s32 px;
    s32 py;

    tx = (s->originX + s->scrollX) << 8;
    ty = (s->originY + s->scrollY) << 8;
    dx = (tx - sAllmapCameraFixedX) >> 3;
    dy = (ty - sAllmapCameraFixedY) >> 3;

    if (dx > 0x800) {
        dx = 0x800;
    } else if (dx < -0x800) {
        dx = -0x800;
    }

    if (dy > 0x800) {
        dy = 0x800;
    } else if (dy < -0x800) {
        dy = -0x800;
    }
    px = sAllmapCameraFixedX;
    py = sAllmapCameraFixedY;
    sAllmapCameraFixedX += dx;
    sAllmapCameraFixedY += dy;

    if ((px - sAllmapCameraFixedX >= 0 ? px - sAllmapCameraFixedX : sAllmapCameraFixedX - px) <= 7) {
        sAllmapCameraFixedX = tx;
    }

    if ((py - sAllmapCameraFixedY >= 0 ? py - sAllmapCameraFixedY : sAllmapCameraFixedY - py) <= 7) {
        sAllmapCameraFixedY = ty;
    }
    gAllmapCameraX = sAllmapCameraFixedX >> 8;
    gAllmapCameraY = sAllmapCameraFixedY >> 8;
}
void UpdateAllmap(void) {
    s16 x;
    s16 y;

    if (FadeIsActive() == 0 && gAllmapModeState == 3) {
        AllmapHandleInput();
    }

    if (gAllmapModeState == 2) {
        if (gAllmapScrollInTimer > 6) {
            ApproachValue(&((AllmapState*)gUnk_0203C4B4)->introScrollY, ((AllmapState*)gUnk_0203C4B4)->introTargetY - 0x200, gAllmapScrollInTimer - 7);
        } else if (gAllmapScrollInTimer & 1) {
            ApproachValue(&((AllmapState*)gUnk_0203C4B4)->introScrollY, ((AllmapState*)gUnk_0203C4B4)->introTargetY, 1);
        } else {
            ApproachValue(&((AllmapState*)gUnk_0203C4B4)->introScrollY, ((AllmapState*)gUnk_0203C4B4)->introTargetY - 0x200, 1);
        }

        ((AllmapState*)gUnk_0203C4B4)->scrollY = ((AllmapState*)gUnk_0203C4B4)->introScrollY >> 8;
    }

    if (gAllmapModeState == 3) {
        AllmapUpdateCamera(gUnk_0203C4B4);
    } else {
        gAllmapCameraX = ((AllmapState*)gUnk_0203C4B4)->originX + ((AllmapState*)gUnk_0203C4B4)->scrollX;
        gAllmapCameraY = ((AllmapState*)gUnk_0203C4B4)->originY + ((AllmapState*)gUnk_0203C4B4)->scrollY;
        sAllmapCameraFixedX = (((AllmapState*)gUnk_0203C4B4)->originX + ((AllmapState*)gUnk_0203C4B4)->scrollX) << 8;
        sAllmapCameraFixedY = (((AllmapState*)gUnk_0203C4B4)->originY + ((AllmapState*)gUnk_0203C4B4)->scrollY) << 8;
    }

    x = gAllmapCameraX - ((AllmapState*)gUnk_0203C4B4)->originX;
    y = gAllmapCameraY - ((AllmapState*)gUnk_0203C4B4)->originY;
    ScrollBgMapTo(0, x - ((AllmapState*)gUnk_0203C4B4)->originX % 8, y - ((AllmapState*)gUnk_0203C4B4)->originY % 8);
    ScrollBgMapTo(1, x - ((AllmapState*)gUnk_0203C4B4)->originX % 8, y - ((AllmapState*)gUnk_0203C4B4)->originY % 8);
    TaskPoolUpdate(&((AllmapState*)gUnk_0203C4B4)->tasks);
    TaskPoolDraw(&((AllmapState*)gUnk_0203C4B4)->tasks);
}

void DestroyAllmap(void) {
    TaskPoolDestroy(&((AllmapState*)gUnk_0203C4B4)->tasks);
    EwramFree(gUnk_0203C4B4);
}

u16 func_080D53C4(void) {
    if ((GetKeysHeld() & R_BUTTON) != 0) {
        return ((AllmapState*)gUnk_0203C4B4)->unk_BC >> 7;
    }
    return ((AllmapState*)gUnk_0203C4B4)->unk_BC >> 8;
}

void func_080D53F8(void) {
    AllmapRoomWork* w;
    AllmapCursorWork* c;
    s32 base;
    u8 i;

    base = (((AllmapState*)gUnk_0203C4B4)->maxY * 24 - gAllmapCameraY) << 9;

    for (i = 0; i < 32; i++) {
        if (IsTaskActive(((AllmapState*)gUnk_0203C4B4)->roomTasks[i]) != 0) {
            w = ((AllmapState*)gUnk_0203C4B4)->roomTasks[i]->work;
            w->unk_094 = (w->y * 24 - gAllmapCameraY) << 8;
            w->unk_090 = w->unk_094 - base;
        }
    }

    if (IsTaskActive(((AllmapState*)gUnk_0203C4B4)->cursorTask) != 0) {
        c = ((AllmapState*)gUnk_0203C4B4)->cursorTask->work;
        c->dropY = c->dropTargetY - base;
    }
}

s32 GetAllmapRoomAt(AllmapCursorPos a) {
    AllmapRoomWork* w;
    u8 i;

    for (i = 0; i < 32; i++) {
        if (IsTaskActive(((AllmapState*)gUnk_0203C4B4)->roomTasks[i]) != 0) {
            w = ((AllmapState*)gUnk_0203C4B4)->roomTasks[i]->work;
            if (a.x == w->x && a.y == w->y) {
                return i;
            }
        }
    }
    return 255;
}

void AllmapCenterOnRoom(void) {
    AllmapRoomWork* w;

    w = ((AllmapState*)gUnk_0203C4B4)->roomTasks[gAllmapCursorRoom]->work;
    ((AllmapState*)gUnk_0203C4B4)->scrollY = w->y * 24 - ((AllmapState*)gUnk_0203C4B4)->originY - 69;
    if (((AllmapState*)gUnk_0203C4B4)->scrollY < 0 || ((AllmapState*)gUnk_0203C4B4)->height <= 159) {
        ((AllmapState*)gUnk_0203C4B4)->scrollY = 0;
    } else if (((AllmapState*)gUnk_0203C4B4)->scrollY > ((AllmapState*)gUnk_0203C4B4)->height - 160) {
        ((AllmapState*)gUnk_0203C4B4)->scrollY = ((AllmapState*)gUnk_0203C4B4)->height - 160;
    }

    if ((s16)(w->y * 24 - ((AllmapState*)gUnk_0203C4B4)->originY) <= 15) {
        ((AllmapState*)gUnk_0203C4B4)->scrollY -= 16;
    }
    ((AllmapState*)gUnk_0203C4B4)->scrollX = w->x * 24 - ((AllmapState*)gUnk_0203C4B4)->originX - 104;
    if (((AllmapState*)gUnk_0203C4B4)->scrollX < 0 || ((AllmapState*)gUnk_0203C4B4)->width <= 239) {
        ((AllmapState*)gUnk_0203C4B4)->scrollX = 0;
    } else if (((AllmapState*)gUnk_0203C4B4)->scrollX > ((AllmapState*)gUnk_0203C4B4)->width - 240) {
        ((AllmapState*)gUnk_0203C4B4)->scrollX = ((AllmapState*)gUnk_0203C4B4)->width - 240;
    }
}

void AllmapHandleInput(void) {
    AllmapCursorWork* c;
    AllmapCursorPos p;
    MapFloorRoom* d;
    u8 moved;
    u8 r;

    moved = 0;
    c = ((AllmapState*)gUnk_0203C4B4)->cursorTask->work;
    p = c->pos;

    switch (GetKeysRepeat()) {
    case DPAD_UP:
        p.x++;
        p.y--;
        moved = 1;
        break;
    case DPAD_RIGHT:
        p.x++;
        p.y++;
        moved = 1;
        break;
    case DPAD_LEFT:
        p.x--;
        p.y--;
        moved = 1;
        break;
    case DPAD_DOWN:
        p.x--;
        p.y++;
        moved = 1;
        break;
    }
    r = GetAllmapRoomAt(p);
    if (r == 255) {
        return;
    }
    c->pos = p;

    if (((AllmapState*)gUnk_0203C4B4)->lastRoom == r) {
        return;
    }
    ((AllmapState*)gUnk_0203C4B4)->lastRoom = r;
    gAllmapCursorRoom = r;

    if (moved != 0) {
        m4aSongNumStart(SONG_SYS_CLICK);
        AllmapCenterOnRoom();
    }

    if (IsTaskActive(((AllmapState*)gUnk_0203C4B4)->roomnameTask) != 0) {
        TaskKill(gUnk_0203C4B4, ((AllmapState*)gUnk_0203C4B4)->roomnameTask);
    }
    d = GetMapFloorRoom(r);
    if (d->nameId != 26 && (TestAllmapRoomFlag(r, 2) != 0 || TestAllmapRoomFlag(r, 8) != 0)) {
        ((AllmapState*)gUnk_0203C4B4)->roomnameTask = TaskCreate(gUnk_0203C4B4, &sTaskDescAllmapRoomname, &d->nameId);
    } else {
        ((AllmapState*)gUnk_0203C4B4)->roomnameTask = 0;
        AllmapClearRoomnameFrame();
    }

    if (IsTaskActive(((AllmapState*)gUnk_0203C4B4)->pushaTask) != 0) {
        TaskKill(gUnk_0203C4B4, ((AllmapState*)gUnk_0203C4B4)->pushaTask);
    }

    if (AllmapHasDoorInfo(c->pos) != 0) {
        ((AllmapState*)gUnk_0203C4B4)->pushaTask = TaskCreate(gUnk_0203C4B4, &gTaskDescAllmapPusha, c);
    }
}

void AllmapAddRoom(u8 a, u16 b, u16 c) {
    AllmapRoomArg arg;
    u8* d;
    u8 room;

    d = GetMapRoomLinks(a);

    if (IsTaskActive(((AllmapState*)gUnk_0203C4B4)->roomTasks[a]) != 0) {
        return;
    }

    if (((AllmapState*)gUnk_0203C4B4)->maxX < b) {
        ((AllmapState*)gUnk_0203C4B4)->maxX = b;
    }

    if (((AllmapState*)gUnk_0203C4B4)->minX > b) {
        ((AllmapState*)gUnk_0203C4B4)->minX = b;
    }

    if (((AllmapState*)gUnk_0203C4B4)->maxY < c) {
        ((AllmapState*)gUnk_0203C4B4)->maxY = c;
    }

    if (((AllmapState*)gUnk_0203C4B4)->minY > c) {
        ((AllmapState*)gUnk_0203C4B4)->minY = c;
    }
    arg.x = b;
    arg.y = c;
    arg.room = a;
    arg.asSprite = 0;
    ((AllmapState*)gUnk_0203C4B4)->roomTasks[a] = TaskCreate(gUnk_0203C4B4, &sTaskDescAllmapRoom, &arg);

    room = d[0];
    if ((u8)(room + 3) > 2) {
        AllmapAddRoom(room, b + 1, c - 1);
    }

    room = d[1];
    if ((u8)(room + 3) > 2) {
        AllmapAddRoom(room, b - 1, c + 1);
    }

    room = d[2];
    if ((u8)(room + 3) > 2) {
        AllmapAddRoom(room, b + 1, c + 1);
    }

    room = d[3];
    if ((u8)(room + 3) > 2) {
        AllmapAddRoom(room, b - 1, c - 1);
    }
}

void AllmapSetBounds(u16 a, u16 b, u16 c, u16 d) {
    u16 dx;
    u16 dy;

    ((AllmapState*)gUnk_0203C4B4)->height = (d - c) * 24 + 32;
    if (((AllmapState*)gUnk_0203C4B4)->height <= 159) {
        dy = (160 - ((AllmapState*)gUnk_0203C4B4)->height) / 2;
    } else {
        dy = 0;
    }
    ((AllmapState*)gUnk_0203C4B4)->width = (b - a) * 24 + 32;
    if (((AllmapState*)gUnk_0203C4B4)->width <= 239) {
        dx = (240 - ((AllmapState*)gUnk_0203C4B4)->width) / 2;
    } else {
        dx = 0;
    }
    ((AllmapState*)gUnk_0203C4B4)->originX = a * 24 - dx;
    ((AllmapState*)gUnk_0203C4B4)->originY = c * 24 - dy;
    AllmapCenterOnRoom();
}

u8 TestAllmapRoomFlag(u8 a, u16 b) {
    return *(u8*)GetMapFloorRoom(a) & b;
}

void* GetAllmapRoomWork(u8 a) {
    return ((AllmapState*)gUnk_0203C4B4)->roomTasks[a]->work;
}

TaskDesc gTaskDescAllmapDoorinfo = {
    "task_allmap_doorinfo",
    (TaskInitFunc)task_allmap_doorinfo_0,
    (TaskUpdateFunc)task_allmap_doorinfo_1,
    (TaskDrawFunc)task_allmap_doorinfo_2,
    (TaskDestroyFunc)task_allmap_doorinfo_3,
    sizeof(AllmapDoorinfoWork),
};

TaskDesc gTaskDescAllmapPusha = {
    "task_allmap_pusha",
    (TaskInitFunc)task_allmap_pusha_0,
    (TaskUpdateFunc)task_allmap_pusha_1,
    (TaskDrawFunc)task_allmap_pusha_2,
    (TaskDestroyFunc)task_allmap_pusha_3,
    sizeof(AllmapPushaWork),
};
