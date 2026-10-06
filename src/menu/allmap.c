/**
 * allmap.c
 * Floor Map Screen Tasks
 */

#include "macros.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
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
#include "allmap_types.h"
#include "anim.h"
#include "card_ui_types.h"
#include "display.h"
#include "field_state.h"
#include "key.h"
#include "m4a_song.h"
#include "map_types.h"
#include "obj.h"
#include "poo_api.h"
#include "taskpool.h"
#include "text.h"
#include "types.h"
#include <stddef.h>
#include "default_bg_map.h"
#include "sprite_palettes.h"

#define sAllmapState ((AllmapState*)gSharedModeWork)

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
    gAllmapBarTitleFrame0,
    gAllmapBarTitleFrame1,
    gAllmapBarTitleFrame4,
    gAllmapBarTitleFrame3,
    gAllmapBarTitleFrame2,
};

static void* sAllmapBarBgMapsByLanguage[5] = {
    gAllmapBarBgEnglishMap,
    gAllmapBarBgFrenchMap,
    gAllmapBarBgGermanMap,
    gAllmapBarBgItalianMap,
    gAllmapBarBgSpanishMap,
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

s32 GetAllmapRoomPaletteOffset(u8 room) {
    u8 r = 0;

    if (GetEventRoomKind(room) == 1 || GetEventRoomKind(room) == 4) {
        r = 1;
    }

    return r << 5;
}

void task_allmap_room_0(AllmapRoomWork* work, AllmapRoomArg* arg) {
    void* pal;

    work->x = arg->x;
    work->y = arg->y;
    work->dropY = -arg->y << 8;
    work->dropTargetY = arg->y << 8;
    work->room = arg->room;
    work->asSprite = arg->asSprite;
    work->shape = SetupAllmapRoomDoors(work);

    if (!work->asSprite) {
        work->tiles = LoadObjTiles(gAllmapRoomTiles, 0x2400);
        work->gfx2 = NULL;
    } else {
        work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gAllmapRoomFrames, 17), gAllmapRoomTiles);
        work->gfx2 = gAllmapRoomFrames[work->shape];
    }

    if (!work->asSprite && work->room == gMapFloorState.room) {
        pal = gAllmapCurrentRoomPalettes;
    } else {
        pal = gAllmapRoomPalettes + GetAllmapRoomPaletteOffset(work->room);
    }

    work->palette = LoadObjPalette(pal, 32);
}

s32 task_allmap_room_1() {
    return 1;
}

void task_allmap_room_2(AllmapRoomWork* work) {
    s32 i;
    s16 x;
    s16 y;
    u16 g;
    u16 h;

    if (!work->asSprite) {
        x = work->x * 24 - gAllmapCameraX;
        y = work->y * 24 - gAllmapCameraY;
        g = 0x800;
        h = -4100 - work->y * 4;
    } else {
        if ((gFieldState->flags & FIELD_FLAG_ROOM_CREATE) != 0) {
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
        DrawSprite(x, y, work->gfx2, work->tiles, work->palette, NULL, g, h);
    }

    for (i = 0; i < 4; i++) {
        if (work->gfx[i] != NULL) {
            work->gfx[i] = AnimUpdate(&work->anim[i]);
            DrawSprite(x, y, work->gfx[i], work->tiles2[i], work->palette, NULL, g, i - 4 + h);
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

u8 AllmapDoorHasCardInfo(u8 room, u8 side) {
    if (GetEventRoomKind(room) != 0) {
        if (TestAllmapRoomFlag(room, FLOOR_ROOM_FLAG_EVENT_DONE) != 0) {
            return 0;
        }
    }

    if (TestAllmapRoomFlag(room, FLOOR_ROOM_FLAG_VISITED) != 0) {
        return AllmapDoorExists(room, side);
    }

    return 0;
}

u8 AllmapDoorHasKeyInfo(u8 room, u8 side) {
    if (GetEventRoomKind(room) == 0) {
        if (TestAllmapRoomFlag(room, FLOOR_ROOM_FLAG_VISITED) == 0) {
            return 0;
        }
    } else {
        if (TestAllmapRoomFlag(room, FLOOR_ROOM_FLAG_EVENT_DONE) != 0) {
            return 0;
        }

        if (TestAllmapRoomFlag(room, FLOOR_ROOM_FLAG_VISITED) == 0) {
            return 0;
        }
    }

    if (AllmapDoorExists(room, side)) {
        return AllmapDoorIsOpen(room, side) == 0;
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
    work->tiles = LoadObjTiles(gAllmapCursorTiles, 0xC0);
    work->palette = LoadObjPalette(gAllmapObjPalette, 32);
    AnimInit(&work->anim, gAllmapCursorAnims, gAllmapCursorFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    work->moveSteps = 0;
}

s32 task_allmap_cursor_1(AllmapCursorWork* work) {
    s32 x;
    s32 y;

    if (gAllmapModeState == ALLMAP_MODE_STATE_INTRO) {
        if (gAllmapCursorDropTimer > 6) {
            ApproachValue(&work->dropY, work->dropTargetY, gAllmapCursorDropTimer - 7);
        } else if (gAllmapCursorDropTimer > 3) {
            ApproachValueHalfSteps(&work->dropY, work->dropTargetY - 0x800, gAllmapCursorDropTimer - 3);
        } else {
            ApproachValueHalfSteps(&work->dropY, work->dropTargetY, gAllmapCursorDropTimer);
        }
    }

    if (gAllmapModeState != ALLMAP_MODE_STATE_ACTIVE) {
        work->gfx = gAllmapCursorFrames[0];
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

    if (IsStockMesDispActive()) {
        return;
    }

    if (gAllmapModeState != ALLMAP_MODE_STATE_ACTIVE) {
        x = work->screenX;
        y = work->dropY >> 8;
    } else {
        x = work->drawX >> 8;
        y = work->drawY >> 8;
    }

    DrawSprite(x - 15, y - 22, work->gfx, work->tiles, work->palette, NULL, 0, 49);
}

void task_allmap_cursor_3(AllmapCursorWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

s16 AllmapDrawRoomnameFrame(u16 width) {
    u8* base;
    u16* p;
    s16 v;
    s16 q;
    u8* dst;

    v = 120 - width;

    if (v < 0) {
        v = 0;
    }

    q = v / 8;
    base = GetBgScreenBase(2);
    dst = base + 28;
    p = gAllmapRoomnameFrameMap - q;
    RequestDma3Copy(p, dst, 32);
    dst = base + 92;
    p += 32;
    RequestDma3Copy(p, dst, 32);
    dst = base + 156;
    p += 32;
    RequestDma3Copy(p, dst, 32);
    return v - v % 8 / 2;
}

s32 GetAllmapRoomnamePaletteOffset(u8 nameId) {
    switch (GetRoomCardBackIndex(nameId)) {
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

void task_allmap_roomname_0(AllmapRoomnameWork* work, u8* nameId) {
    u16 pal;

    InitTextSlots(work->textSlots, ALLMAP_ROOMNAME_TEXT_SLOTS);
    work->textSlotCount = LoadTextSlots(GetRoomName(nameId[0]), work->textSlots);
    pal = GetAllmapRoomnamePaletteOffset(nameId[0]);
    work->palette = LoadObjPalette(gAllmapRoomnamePalettes + pal, 32);
    LoadPalette(gAllmapRoomnameBgPalettes + pal, gUnk_05000160, 32);
    work->x = AllmapDrawRoomnameFrame(GetTextSlotsWidth(work->textSlots, work->textSlotCount));
}

s32 task_allmap_roomname_1() {
    return 1;
}

void task_allmap_roomname_2(AllmapRoomnameWork* work) {
    DrawTextSlots(work->x + 117, 3, work->textSlots, work->palette, 50, work->textSlotCount);
}

void task_allmap_roomname_3(AllmapRoomnameWork* work) {
    FreeTextSlots(work->textSlots, ALLMAP_ROOMNAME_TEXT_SLOTS);
    ReleaseObjPalette(work->palette);
}

void AllmapClearRoomnameFrame() {
    u8* base;
    u16* p;
    u8* dst;

    base = GetBgScreenBase(2);
    dst = base + 28;
    p = gDefaultBgMap;
    RequestDma3Copy(p, dst, 32);
    dst = base + 92;
    p += 32;
    RequestDma3Copy(p, dst, 32);
    dst = base + 156;
    p += 32;
    RequestDma3Copy(p, dst, 32);
}

enum AllmapBarState {
    ALLMAP_BAR_STATE_BARS_IN,
    ALLMAP_BAR_STATE_TITLE_IN,
    ALLMAP_BAR_STATE_IDLE,
    ALLMAP_BAR_STATE_TITLE_OUT,
    ALLMAP_BAR_STATE_BARS_OUT
};

void AllmapBarStartClose(AllmapBarWork* work) {
    work->closing = 1;

    if (work->state == ALLMAP_BAR_STATE_BARS_IN) {
        work->state = ALLMAP_BAR_STATE_BARS_OUT;
    } else {
        work->state = ALLMAP_BAR_STATE_TITLE_OUT;
    }

    if (work->steps == 0) {
        work->steps = 16;
    }

    LoadBgMap(3, gAllmapBackdropMap, 0x500);
    work->targetY = -0x800;
    work->targetY2 = 0xA000;
    work->targetX = -0x8000;
}

void task_allmap_bar_0(AllmapBarWork* work) {
    gStockMesDispWork = work;
#ifdef VERSION_EU
    work->tiles = LoadObjTiles(gAllmapBarTitleTiles, 0xDC0);
#else
    work->tiles = LoadObjTiles(gAllmapBarTitleTiles, 0x2C0);
#endif
    work->tiles2 = LoadObjTiles(gAllmapBarBandTiles, 0xC0);
    work->palette = LoadObjPalette(gAllmapObjPalette, 32);
    work->steps = 16;
    work->state = ALLMAP_BAR_STATE_BARS_IN;
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
    FadeStartOut(FADE_MODE_BLACK, 16);
    FadeLock();
}

s32 task_allmap_bar_1(AllmapBarWork* work) {
    s32 i;

    switch (work->state) {
    case ALLMAP_BAR_STATE_BARS_IN:
        ApproachValue(&work->y, work->targetY, work->steps);
        ApproachValue(&work->y2, work->targetY2, work->steps);
        work->steps--;

        if (work->steps == 0) {
            work->steps = 16;
            work->state = ALLMAP_BAR_STATE_TITLE_IN;
        }

        break;
    case ALLMAP_BAR_STATE_TITLE_IN:
        ApproachValue(&work->x, work->targetX, work->steps);
        work->steps--;

        if (work->steps == 0) {
#ifdef VERSION_EU
            LoadBgMap(3, sAllmapBarBgMapsByLanguage[gLanguage], 0x500);
#else
            LoadBgMap(3, gAllmapBarBgMap, 0x500);
#endif
            work->state = ALLMAP_BAR_STATE_IDLE;
            gAllmapModeState = ALLMAP_MODE_STATE_INTRO;
        }

        break;
    case ALLMAP_BAR_STATE_TITLE_OUT:
        ApproachValue(&work->x, work->targetX, work->steps);
        work->steps--;

        if (work->steps == 0) {
            work->steps = 16;
            work->state = ALLMAP_BAR_STATE_BARS_OUT;
        }

        break;
    case ALLMAP_BAR_STATE_BARS_OUT:
        if (!FadeIsActive() && !work->fadeStarted) {
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
            gAllmapModeState = ALLMAP_MODE_STATE_FADE;
            return 0;
        }

        break;
    case ALLMAP_BAR_STATE_IDLE:
        if (work->closing) {
            break;
        }

        if (gAllmapModeState != ALLMAP_MODE_STATE_ACTIVE) {
            break;
        }

        if ((GetKeysPressed() & START_BUTTON) != 0) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            AllmapBarFadeOut(work);
            gAllmapModeState = ALLMAP_MODE_STATE_FADE;
            AllmapClearRoomnameFrame();
            SetAllmapReturnToMenu(0);
            return 0;
        }

        if ((GetKeysPressed() & B_BUTTON) != 0 && !IsStockMesDispActive()) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            AllmapBarStartClose(work);
            gAllmapModeState = ALLMAP_MODE_STATE_BAR_SLIDE;
            AllmapClearRoomnameFrame();
            SetAllmapReturnToMenu(1);
        }

        break;
    }

    return 1;
}

void task_allmap_bar_2(AllmapBarWork* work) {
    if (work->state == ALLMAP_BAR_STATE_IDLE) {
        return;
    }

#ifdef VERSION_EU
    DrawSprite(work->x >> 8, 0, sAllmapBarSprites[gLanguage], work->tiles, work->palette, NULL,
        SPRITE_PRIORITY(3), 1000);
#else
    DrawSprite(work->x >> 8, 0, gAllmapBarTitleFrame0, work->tiles, work->palette, NULL, SPRITE_PRIORITY(3), 1000);
#endif
    DrawSprite(128, work->y >> 8, gAllmapBarBandFrame0, work->tiles2, work->palette, NULL, SPRITE_PRIORITY(3), 1001);
    DrawSprite(128, work->y2 >> 8, gAllmapBarBandFrame1, work->tiles2, work->palette, NULL, SPRITE_PRIORITY(3), 1002);
}

void task_allmap_bar_3(AllmapBarWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette);
}

u8 AllmapHasDoorInfo(AllmapCursorPos pos) {
    AllmapCursorPos p;
    s32 i;
    u8 r;
    u8 v;

    for (i = 0; i < 4; i++) {
        p.x = pos.x + sAllmapDirDeltas[i][0];
        p.y = pos.y + sAllmapDirDeltas[i][1];
        r = GetAllmapRoomAt(p);

        if (r != 255) {
            if (GetEventRoomKind(GetAllmapRoomAt(pos)) == 2) {
                v = AllmapDoorHasKeyInfo(r, sAllmapReverseDoors[i]);
            } else {
                v = AllmapDoorHasCardInfo(r, sAllmapReverseDoors[i]);
            }

            if (v) {
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

        if (room != MAP_ROOM_NONE && AllmapDoorHasCardInfo(room, sAllmapReverseDoors[i])) {
            n = GetMapRoomCardValue(room) + 1;

            if (n == 10) {
                n = 0;
            }

            work->doors[i].sprite.tiles = AllocKeyValueTiles(n);
            work->doors[i].sprite.palette = LoadObjPalette(gDoorCardPalette, 32);
            work->doors[i].sprite.gfx = NULL;
            work->doors[i].sprite.tiles2 = LoadObjTiles(gCardOutlineWhiteTiles, 0x600);
            work->doors[i].sprite.palette2 = LoadObjPalette(gDoorCardPalette, 32);
            work->doors[i].sprite.gfx2 = gCardOutlineWhiteFrames[0];
            FadeSetPaletteExcluded(work->doors[i].sprite.palette->index + 16, 1);
            FadeSetPaletteExcluded(work->doors[i].sprite.palette2->index + 16, 1);
            work->gfx2[i] = gAllmapDoorinfoArrowFrames[i];
            work->count++;
        } else {
            work->gfx2[i] = NULL;
        }
    }

    if (work->count != 0) {
        work->tiles = LoadObjTiles(gAllmapDoorinfoArrowTiles, 0x80);
        work->palette = LoadObjPalette(gAllmapObjPalette, 32);
        FadeSetPaletteExcluded(work->palette->index + 16, 1);
        work->tiles2 = LoadObjTiles(gAllmapRoomTiles, 0x2400);
        work->gfx = gAllmapRoomFrames[0];
        InitObjPaletteAtSlot(work->palette2, 15, gAllmapRoomPalettes, 32);
        FadeSetPaletteExcluded(work->palette2->index + 16, 1);
    }
}

s32 GetAllmapKeyCardX(u16 count, s32 index) {
    s16 tbl[4][4];

    memcpy(tbl, sAllmapKeyCardX, sizeof(tbl));
    return tbl[count - 1][index] << 8;
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

        if (room != MAP_ROOM_NONE && AllmapDoorHasKeyInfo(room, sAllmapReverseDoors[i])) {
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

    work->tiles2 = LoadObjTiles(gAllmapRoomTiles, 0x2400);

    if (GetEventRoomKind(work->room) == 1 || GetEventRoomKind(work->room) == 4) {
        work->gfx = gAllmapRoomFrames[1];
        InitObjPaletteAtSlot(work->palette2, 15, gAllmapEventRoomPalette, 32);
    } else {
        work->gfx = gAllmapRoomFrames[0];
        InitObjPaletteAtSlot(work->palette2, 15, gAllmapRoomPalettes, 32);
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
    FadeToAmount(FADE_MODE_BLACK, 14, 8);
}

s32 task_allmap_doorinfo_1(AllmapDoorinfoWork* work) {
    if ((GetKeysPressed() & B_BUTTON) != 0 && !work->closing) {
        work->closing = 1;
        m4aSongNumStart(SONG_SYS_CLOSE);
        work->steps = 8 - work->steps;
        work->targetX = work->roomX << 8;
        work->targetY = work->roomY << 8;
        FadeToOriginal(FADE_MODE_BLACK, 8);
    }

    if (work->steps != 0) {
        ApproachValue(&work->x, work->targetX, work->steps);
        ApproachValue(&work->y, work->targetY, work->steps);
        work->steps--;
    }

    if (work->closing && work->steps == 0) {
        return 0;
    }

    return 1;
}

void AllmapDoorinfoDrawDoors(AllmapDoorinfoWork* work) {
    s32 i;

    if (gAllmapModeState == ALLMAP_MODE_STATE_FADE) {
        return;
    }

    for (i = 0; i < 4; i++) {
        if (work->gfx2[i] != NULL && work->steps == 0) {
            DrawSprite(work->x >> 8, work->y >> 8, work->gfx2[i], work->tiles, work->palette, NULL, 0, i + 51);
            sAllmapDoorOffsetX = sAllmapDoorCardOffsets[i][0];
            sAllmapDoorOffsetY = sAllmapDoorCardOffsets[i][1];
            DrawSprite(sAllmapDoorOffsetX + (work->x >> 8), sAllmapDoorOffsetY + (work->y >> 8), work->doors[i].sprite.gfx, work->doors[i].sprite.tiles, work->doors[i].sprite.palette, NULL, 0, i + 40);
            DrawSprite((work->x >> 8) + sAllmapDoorOffsetX, (work->y >> 8) + sAllmapDoorOffsetY, work->doors[i].sprite.gfx2, work->doors[i].sprite.tiles2, work->doors[i].sprite.palette2, NULL, 0, i + 30);
        }
    }

    DrawSprite(work->x >> 8, work->y >> 8, work->gfx, work->tiles2, work->palette2, NULL, 0, 20);
}

void AllmapDoorinfoDrawKeys(AllmapDoorinfoWork* work) {
    s32 i;

    if (work->steps == 0) {
        for (i = 0; i < work->count; i++) {
            DrawLayeredCardSprite(&work->doors[i].sprite, 0);
        }
    }

    DrawSprite(work->x >> 8, work->y >> 8, work->gfx, work->tiles2, work->palette2, NULL, 0, 20);
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

    if (!work->closing) {
        FadeToOriginal(FADE_MODE_BLACK, 8);
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
    work->tiles = LoadObjTiles(gAllmapPushaTiles, 0x80);
    work->palette = LoadObjPalette(gAllmapObjPalette, 32);
    work->gfx = gAllmapPushaFrame0;
    work->angle = 0;
    TaskPoolInit(&work->tasks, 1);
    work->task = NULL;
}

s32 task_allmap_pusha_1(AllmapPushaWork* work) {
    if (!IsStockMesDispActive() && (GetKeysPressed() & A_BUTTON) != 0) {
        m4aSongNumStart(SONG_SYS_KETTEI);
        work->task = TaskCreate(&work->tasks, &gTaskDescAllmapDoorinfo, &work->cursor->pos);
    }

    work->y2 = gSineTable[(u8)work->angle] >> 8;
    work->angle += 16;
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_allmap_pusha_2(AllmapPushaWork* work) {
    if (IsStockMesDispActive()) {
        TaskPoolDraw(&work->tasks);
    } else {
        work->x = work->cursor->pos.x * 24 - gAllmapCameraX;
        work->y = work->cursor->pos.y * 24 - gAllmapCameraY;
        DrawSprite(work->x, work->y - work->y2 + 2, work->gfx, work->tiles, work->palette, NULL, 0, 48);
    }
}

void task_allmap_pusha_3(AllmapPushaWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
    ClearStockMesDispWork();
}

u8 IsStockMesDispActive() {
    if (gStockMesDispWork == NULL || !IsTaskActive(((AllmapPushaWork*)gStockMesDispWork)->task)) {
        return 0;
    }

    return 1;
}

void ClearStockMesDispWork() {
    gStockMesDispWork = NULL;
}

void AllmapDrawRoomTiles(s16 x, s16 y, s32 shape, u8 selected) {
    AllmapCursorPos p;
    u16* map;
    s16 x8;
    s16 y8;
    s32 i;
    s32 j;
    u8 room;
    u16 tile;
    s16 ofs;

    if ((x & 1) != 0) {
        map = gAllmapBg0Map;
    } else {
        map = gAllmapBg1Map;
    }

    x8 = (x * 24 - sAllmapState->originX) / 8;
    y8 = (y * 24 - sAllmapState->originY) / 8;
    p.x = x;
    p.y = y;
    room = GetAllmapRoomAt(p);
    tile = shape * 16;

    if (TestAllmapRoomFlag(room, FLOOR_ROOM_FLAG_EVENT_DONE) != 0 || TestAllmapRoomFlag(room, FLOOR_ROOM_FLAG_VISITED) != 0 || AllmapHasDoorInfo(p)) {
        if (selected) {
            tile += 0x2000;
        } else if (shape == 1) {
            tile += 0x1000;
        } else if (shape == 17) {
            tile += 0xF000;
        }
    } else if (shape == 1 || shape == 17) {
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

void InitAllmap() {
    s32 i;
    s32 j;
    AllmapCursorPos arg;
    AllmapRoomWork* w;
    AllmapRoomWork* c;
    void** state = &gSharedModeWork;

    *state = EwramAlloc(sizeof(AllmapState));
    sAllmapState->lastRoom = MAP_ROOM_NONE;
    sAllmapState->moveSpeed = 0x400;
    gAllmapCursorRoom = gMapFloorState.room;
    TaskPoolInit(&sAllmapState->tasks, 35);
    sAllmapState->pushaTask = NULL;
    sAllmapState->roomnameTask = NULL;

    for (i = 0; i < 32; i++) {
        sAllmapState->roomTasks[i] = NULL;
    }

    sAllmapState->minX = sAllmapState->maxX = 32;
    sAllmapState->minY = sAllmapState->maxY = 32;
    AllmapAddRoom(0, 32, 32);
    sAllmapState->scrollX = 0;
    sAllmapState->scrollY = 0;
    AllmapSetBounds(sAllmapState->minX, sAllmapState->maxX, sAllmapState->minY, sAllmapState->maxY);
    sAllmapState->introScrollY = (sAllmapState->scrollY + 160) << 8;
    sAllmapState->introTargetY = sAllmapState->scrollY << 8;
    gAllmapCameraX = sAllmapState->originX + sAllmapState->scrollX;
    gAllmapCameraY = sAllmapState->originY + sAllmapState->scrollY;
    sAllmapCameraFixedX = (sAllmapState->originX + sAllmapState->scrollX) << 8;
    sAllmapCameraFixedY = (sAllmapState->originY + sAllmapState->scrollY) << 8;

    for (j = 0; j < 32; j++) {
        if (IsTaskActive(sAllmapState->roomTasks[j])) {
            w = sAllmapState->roomTasks[j]->work;
            AllmapDrawRoomTiles(w->x, w->y, w->shape, j == gAllmapCursorRoom);
        }
    }

    RedrawBgMapAt(0, sAllmapState->scrollX - sAllmapState->originX % 8, sAllmapState->scrollY - sAllmapState->originY % 8);
    RedrawBgMapAt(1, sAllmapState->scrollX - sAllmapState->originX % 8, sAllmapState->scrollY - sAllmapState->originY % 8);
    c = sAllmapState->roomTasks[gAllmapCursorRoom]->work;
    arg.x = c->x;
    arg.y = c->y;
    sAllmapState->cursorTask = TaskCreate(&sAllmapState->tasks, &sTaskDescAllmapCursor, &arg);
    AllmapInitDropOffsets();
}

void AllmapUpdateCamera(AllmapState* state) {
    s32 tx;
    s32 ty;
    s32 dx;
    s32 dy;
    s32 px;
    s32 py;

    tx = (state->originX + state->scrollX) << 8;
    ty = (state->originY + state->scrollY) << 8;
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

void UpdateAllmap() {
    s16 x;
    s16 y;

    if (!FadeIsActive() && gAllmapModeState == ALLMAP_MODE_STATE_ACTIVE) {
        AllmapHandleInput();
    }

    if (gAllmapModeState == ALLMAP_MODE_STATE_INTRO) {
        if (gAllmapScrollInTimer > 6) {
            ApproachValue(&sAllmapState->introScrollY, sAllmapState->introTargetY - 0x200, gAllmapScrollInTimer - 7);
        } else if (gAllmapScrollInTimer & 1) {
            ApproachValue(&sAllmapState->introScrollY, sAllmapState->introTargetY, 1);
        } else {
            ApproachValue(&sAllmapState->introScrollY, sAllmapState->introTargetY - 0x200, 1);
        }

        sAllmapState->scrollY = sAllmapState->introScrollY >> 8;
    }

    if (gAllmapModeState == ALLMAP_MODE_STATE_ACTIVE) {
        AllmapUpdateCamera(sAllmapState);
    } else {
        gAllmapCameraX = sAllmapState->originX + sAllmapState->scrollX;
        gAllmapCameraY = sAllmapState->originY + sAllmapState->scrollY;
        sAllmapCameraFixedX = (sAllmapState->originX + sAllmapState->scrollX) << 8;
        sAllmapCameraFixedY = (sAllmapState->originY + sAllmapState->scrollY) << 8;
    }

    x = gAllmapCameraX - sAllmapState->originX;
    y = gAllmapCameraY - sAllmapState->originY;
    ScrollBgMapTo(0, x - sAllmapState->originX % 8, y - sAllmapState->originY % 8);
    ScrollBgMapTo(1, x - sAllmapState->originX % 8, y - sAllmapState->originY % 8);
    TaskPoolUpdate(&sAllmapState->tasks);
    TaskPoolDraw(&sAllmapState->tasks);
}

void DestroyAllmap() {
    TaskPoolDestroy(&sAllmapState->tasks);
    EwramFree(gSharedModeWork);
}

u16 GetAllmapMoveSpeed() {
    if ((GetKeysHeld() & R_BUTTON) != 0) {
        return sAllmapState->moveSpeed >> 7;
    }

    return sAllmapState->moveSpeed >> 8;
}

void AllmapInitDropOffsets() {
    AllmapRoomWork* w;
    AllmapCursorWork* c;
    s32 base;
    u8 i;

    base = (sAllmapState->maxY * 24 - gAllmapCameraY) << 9;

    for (i = 0; i < 32; i++) {
        if (IsTaskActive(sAllmapState->roomTasks[i])) {
            w = sAllmapState->roomTasks[i]->work;
            w->dropTargetY = (w->y * 24 - gAllmapCameraY) << 8;
            w->dropY = w->dropTargetY - base;
        }
    }

    if (IsTaskActive(sAllmapState->cursorTask)) {
        c = sAllmapState->cursorTask->work;
        c->dropY = c->dropTargetY - base;
    }
}

s32 GetAllmapRoomAt(AllmapCursorPos pos) {
    AllmapRoomWork* w;
    u8 i;

    for (i = 0; i < 32; i++) {
        if (IsTaskActive(sAllmapState->roomTasks[i])) {
            w = sAllmapState->roomTasks[i]->work;

            if (pos.x == w->x && pos.y == w->y) {
                return i;
            }
        }
    }

    return MAP_ROOM_NONE;
}

void AllmapCenterOnRoom() {
    AllmapRoomWork* w;

    w = sAllmapState->roomTasks[gAllmapCursorRoom]->work;
    sAllmapState->scrollY = w->y * 24 - sAllmapState->originY - 69;

    if (sAllmapState->scrollY < 0 || sAllmapState->height <= 159) {
        sAllmapState->scrollY = 0;
    } else if (sAllmapState->scrollY > sAllmapState->height - 160) {
        sAllmapState->scrollY = sAllmapState->height - 160;
    }

    if ((s16)(w->y * 24 - sAllmapState->originY) <= 15) {
        sAllmapState->scrollY -= 16;
    }

    sAllmapState->scrollX = w->x * 24 - sAllmapState->originX - 104;

    if (sAllmapState->scrollX < 0 || sAllmapState->width <= 239) {
        sAllmapState->scrollX = 0;
    } else if (sAllmapState->scrollX > sAllmapState->width - 240) {
        sAllmapState->scrollX = sAllmapState->width - 240;
    }
}

void AllmapHandleInput() {
    AllmapCursorWork* c;
    AllmapCursorPos p;
    MapFloorRoom* d;
    u8 moved;
    u8 r;

    moved = 0;
    c = sAllmapState->cursorTask->work;
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

    if (sAllmapState->lastRoom == r) {
        return;
    }

    sAllmapState->lastRoom = r;
    gAllmapCursorRoom = r;

    if (moved) {
        m4aSongNumStart(SONG_SYS_CLICK);
        AllmapCenterOnRoom();
    }

    if (IsTaskActive(sAllmapState->roomnameTask)) {
        TaskKill(&sAllmapState->tasks, sAllmapState->roomnameTask);
    }

    d = GetMapFloorRoom(r);

    if (d->nameId != 26 && (TestAllmapRoomFlag(r, FLOOR_ROOM_FLAG_VISITED) != 0 || TestAllmapRoomFlag(r, FLOOR_ROOM_FLAG_EVENT_DONE) != 0)) {
        sAllmapState->roomnameTask = TaskCreate(&sAllmapState->tasks, &sTaskDescAllmapRoomname, &d->nameId);
    } else {
        sAllmapState->roomnameTask = NULL;
        AllmapClearRoomnameFrame();
    }

    if (IsTaskActive(sAllmapState->pushaTask)) {
        TaskKill(&sAllmapState->tasks, sAllmapState->pushaTask);
    }

    if (AllmapHasDoorInfo(c->pos)) {
        sAllmapState->pushaTask = TaskCreate(&sAllmapState->tasks, &gTaskDescAllmapPusha, c);
    }
}

void AllmapAddRoom(u8 id, u16 x, u16 y) {
    AllmapRoomArg arg;
    u8* d;
    u8 room;

    d = GetMapRoomLinks(id);

    if (IsTaskActive(sAllmapState->roomTasks[id])) {
        return;
    }

    if (sAllmapState->maxX < x) {
        sAllmapState->maxX = x;
    }

    if (sAllmapState->minX > x) {
        sAllmapState->minX = x;
    }

    if (sAllmapState->maxY < y) {
        sAllmapState->maxY = y;
    }

    if (sAllmapState->minY > y) {
        sAllmapState->minY = y;
    }

    arg.x = x;
    arg.y = y;
    arg.room = id;
    arg.asSprite = 0;
    sAllmapState->roomTasks[id] = TaskCreate(&sAllmapState->tasks, &sTaskDescAllmapRoom, &arg);

    room = d[0];

    if ((u8)(room + 3) > 2) {
        AllmapAddRoom(room, x + 1, y - 1);
    }

    room = d[1];

    if ((u8)(room + 3) > 2) {
        AllmapAddRoom(room, x - 1, y + 1);
    }

    room = d[2];

    if ((u8)(room + 3) > 2) {
        AllmapAddRoom(room, x + 1, y + 1);
    }

    room = d[3];

    if ((u8)(room + 3) > 2) {
        AllmapAddRoom(room, x - 1, y - 1);
    }
}

void AllmapSetBounds(u16 minX, u16 maxX, u16 minY, u16 maxY) {
    u16 dx;
    u16 dy;

    sAllmapState->height = (maxY - minY) * 24 + 32;

    if (sAllmapState->height <= 159) {
        dy = (160 - sAllmapState->height) / 2;
    } else {
        dy = 0;
    }

    sAllmapState->width = (maxX - minX) * 24 + 32;

    if (sAllmapState->width <= 239) {
        dx = (240 - sAllmapState->width) / 2;
    } else {
        dx = 0;
    }

    sAllmapState->originX = minX * 24 - dx;
    sAllmapState->originY = minY * 24 - dy;
    AllmapCenterOnRoom();
}

u8 TestAllmapRoomFlag(u8 room, u16 flag) {
    return *(u8*)GetMapFloorRoom(room) & flag;
}

void* GetAllmapRoomWork(u8 room) {
    return sAllmapState->roomTasks[room]->work;
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
