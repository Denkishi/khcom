/**
 * room_name.c
 * Room Name Display
 */

#include "text.h"
#include "monsgage.h"
#include "room_name.h"
#include "sprites_map.h"
#include "sprites_map_tasks.h"
#include "map_text_data.h"
#include "jiminy_data.h"
#include "common_text.h"
#include "field_state.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include "sprite_palettes.h"
#include "text_types.h"

const MapNameText* gRoomNames[28] = {
    LOCALIZED(gRoomNameTeemingDarkness),
    LOCALIZED(gRoomNameTranquilDarkness),
    LOCALIZED(gRoomNameGuardedTrove),
    LOCALIZED(gRoomNameLoomingDarkness),
    LOCALIZED(gRoomNameSleepingDarkness),
    LOCALIZED(gRoomNameMomentsReprieve),
    LOCALIZED(gRoomNameFeebleDarkness),
    LOCALIZED(gRoomNameAlmightyDarkness),
    LOCALIZED(gRoomNameCalmBounty),
    LOCALIZED(gRoomNameFalseBounty),
    LOCALIZED(gRoomNameMoogleRoom),
    LOCALIZED(gRoomNameSorcerousWaking),
    LOCALIZED(gRoomNameMartialWaking),
    LOCALIZED(gRoomNameAlchemicWaking),
    LOCALIZED(gRoomNameMeetingGround),
    LOCALIZED(gRoomNameMinglingWorlds),
    LOCALIZED(gRoomNameStrongInitiative),
    LOCALIZED(gRoomNameLastingDaze),
    LOCALIZED(gRoomNameStagnantSpace),
    LOCALIZED(gRoomNamePremiumRoom),
    LOCALIZED(gRoomNameWhiteRoom),
    LOCALIZED(gRoomNameBlackRoom),
    LOCALIZED(gRoomNameKeyOfBeginnings),
    LOCALIZED(gRoomNameKeyOfGuidance),
    LOCALIZED(gRoomNameKeyToTruth),
    LOCALIZED(gRoomNameKeyToRewards),
    LOCALIZED(gRoomNameUnknownPlace),
    LOCALIZED(gRoomNameHiddenChamber),
};

void task_room_name_0(RoomNameWork* work, s32 arg) {
    work->tiles = LoadObjTiles(gMapNameBarTiles, 0x800);
    work->palette = LoadObjPalette(gMapFloorNamePalette, 0x20);
    work->gfx = gMapNameBarFrames[0];
    work->nameId = arg;
    work->x2 = 0x5C00;
    work->y2 = 0x8A00;
    work->x = 0x7800;
    work->y = 0x8A00;
    work->unk_20 = 0x400;
    work->unk_24 = 0x19;
    work->timer = 0;
    work->unk_2C = 0;
    work->state = 0;
    work->scaleY = 0x19;
    InitTextSlots(work->textSlots, 0x24);
    work->palette2 = LoadTextPalette(1);
#ifdef VERSION_EU
    work->textSlotCount = LoadTextSlots(GetLocalizedString(gRoomNames[work->nameId]), work->textSlots);
#else
    work->textSlotCount = LoadTextSlots(gRoomNames[work->nameId], work->textSlots);
#endif
}

u8 task_room_name_1(RoomNameWork* work) {
    if (gFieldState->flags & (FIELD_FLAG_MENU_OPEN | FIELD_FLAG_ROOM_CREATE)) {
        return 0;
    }

    switch (work->state) {
    case 0:
        work->timer++;

        if (work->timer > 0x27) {
            work->timer = 0;
            work->state++;
        }

        break;
    case 1:
        work->timer++;

        if (work->timer > 1) {
            work->timer = 0;
            work->y2 -= 0x99;
            work->scaleY += 0x19;

            if (work->scaleY > 0xFF) {
                work->scaleY = 0x100;
                work->state++;
            }
        }

        break;
    case 2:
        work->timer++;

        if (work->timer > 0xB3) {
            work->timer = 0;
            work->state++;
        }

        break;
    case 3:
        work->timer++;

        if (work->timer > 1) {
            work->timer = 0;
            work->y2 += 0x99;
            work->scaleY -= 0x19;

            if (work->scaleY <= 0x19) {
                work->scaleY = 0x19;
                return 0;
            }
        }

        break;
    }

    return 1;
}

void task_room_name_2(RoomNameWork* work) {
    ObjAffine* affine;

    if (work->state != 0) {
        affine = AllocObjAffine(0, 0x100, work->scaleY, 0);
        DrawSprite(work->x >> 8, work->y >> 8, work->gfx, work->tiles, work->palette, affine, 0, 0x3C);
        DrawTextSlots(work->x2 >> 8, work->y2 >> 8, work->textSlots, work->palette2, 0x32, work->textSlotCount);
    }
}

void task_room_name_3(RoomNameWork* work) {
    ReleaseObjTiles(work->tiles);
    FreeTextSlots(work->textSlots, 0x24);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
}

TaskDesc gTaskDescRoomName = {
    "task_room_name",
    (TaskInitFunc)task_room_name_0,
    (TaskUpdateFunc)task_room_name_1,
    (TaskDrawFunc)task_room_name_2,
    (TaskDestroyFunc)task_room_name_3,
    sizeof(RoomNameWork),
};
