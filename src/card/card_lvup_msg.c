/**
 * card_lvup_msg.c
 * Level-Up Message
 */

#include "system_state.h"
#include "m4a_song.h"
#include "game_state.h"
#include "text.h"
#include "monsgage.h"
#include "fade.h"
#include "obj_api.h"
#include "engine_math.h"
#include "obj.h"
#include "taskpool.h"
#include "card.h"
#include "sprites_card.h"
#include "songs.h"
#include "jiminy_data.h"
#include "common_text.h"
#include "msg.h"
#include <stddef.h>
#include "types.h"
#include "card_lvup_msg.h"

#ifdef VERSION_EU
static const u8 sLvupMsgPeriod[] = ".";
#elif defined(VERSION_US)
static const u16 sLvupMsgPeriod[2] = { '.', 0 };
#endif

void Lvup_msg_0(LvupMsgWork* work, StatIncreaseDisplayArgs* a) {
    StatIncreaseDisplayArgs args = *a;

    InitTextSlots(work->textSlots, 20);
    InitTextSlots(work->textSlots2, 20);
    InitTextSlots(work->textSlots3, 20);
#ifndef VERSION_JP
    InitTextSlots(work->textSlots4, 20);
    work->textSlotCount4 = LoadTextSlots(sLvupMsgPeriod, work->textSlots4);
#endif
    work->amount = a->amount;
    work->active = a->done;

    if (args.flags & STAT_INCREASE_FLAG_MAX_HP) {
#ifdef VERSION_EU
        work->textSlotCount = LoadTextSlots(GetLocalizedString(&gUnk_0815A09A), work->textSlots);
#else
        work->textSlotCount = LoadTextSlots(gUnk_0815A09A, work->textSlots);
#endif
    } else if (args.flags & STAT_INCREASE_FLAG_DP) {
#ifdef VERSION_EU
        work->textSlotCount = LoadTextSlots(GetLocalizedString(&gUnk_0815A198), work->textSlots);
#else
        work->textSlotCount = LoadTextSlots(gUnk_0815A198, work->textSlots);
#endif
    } else if (!(gGameState.flags & GAME_FLAG_RIKU)) {
#ifdef VERSION_EU
        work->textSlotCount = LoadTextSlots(GetLocalizedString(&gUnk_0815A0EE), work->textSlots);
#else
        work->textSlotCount = LoadTextSlots(gUnk_0815A0EE, work->textSlots);
#endif
    } else {
#ifdef VERSION_EU
        work->textSlotCount = LoadTextSlots(GetLocalizedString(&gUnk_0815A152), work->textSlots);
#else
        work->textSlotCount = LoadTextSlots(gUnk_0815A152, work->textSlots);
#endif
    }

    work->textSlotCount2 = LoadTwoDigitTextSlots(work->amount, work->textSlots2);

#ifdef VERSION_EU
    if ((args.flags & STAT_INCREASE_FLAG_MAX_HP) && gLanguage == LANGUAGE_SPANISH) {
        work->textSlotCount3 = LoadTextSlots(GetLocalizedString(&gUnkEu_08895EDC), work->textSlots3);
    } else {
        work->textSlotCount3 = LoadTextSlots(GetLocalizedString(&gUnk_0815A0A0), work->textSlots3);
    }
#else
    work->textSlotCount3 = LoadTextSlots(gUnk_0815A0A0, work->textSlots3);
#endif
    work->textPalette = LoadTextPalette(1);
    FadeSetPaletteExcluded(work->textPalette->index + 16, 1);
    work->x = 0x1000;
    work->x2 = 0x3000;
    work->x3 = 0x4200;
    work->y2 = 0xC800;
    work->y3 = 0xC800;
    work->y4 = 0xC800;
    work->y = 0xCE00;
    work->slideSteps = 14;
    work->unk_2B1 = 0;
    work->x = ((144 - (GetTextSlotsWidth(work->textSlots, work->textSlotCount)
#ifndef VERSION_JP
                         + GetTextSlotsWidth(work->textSlots4, work->textSlotCount4)
#endif
                         + GetTextSlotsWidth(work->textSlots2, work->textSlotCount2)
                         + GetTextSlotsWidth(work->textSlots3, work->textSlotCount3))) / 2) << 8;
#ifdef VERSION_EU
    work->tiles = AllocSpriteFrameTiles(0x780);
    UpdateSpriteFrameTiles(work->tiles, gUnk_09EF126C[0], gUnk_093F7C9C);
#else
    work->tiles = LoadObjTiles(gUnk_093F7C9C, 0xFC0);
#endif
    work->palette = LoadObjPalette(gCard00Palette, 32);
}

s32 Lvup_msg_1(LvupMsgWork* work, void* a) {
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateLvupMsgSlideIn);
    work->unk_2B1++;
    return 1;
}

u8 UpdateLvupMsgSlideIn(LvupMsgWork* work, void* a) {
    s8* counter = &work->slideSteps;

    if (*counter > 0) {
        ApproachValue(&work->y, 0x6C00, *counter);
        ApproachValue(&work->y2, 0x6600, *counter);
        ApproachValue(&work->y3, 0x6600, *counter);
        ApproachValue(&work->y4, 0x6600, *counter);
        (*counter)--;
    } else if (*counter == 0) {
        m4aSongNumStart(SONG_SYS_CHAGEF2);
        work->slideSteps = -1;
    }

    if (*work->active == 0) {
        return 0;
    }

    return 1;
}

void Lvup_msg_2(LvupMsgWork* work) {
#ifdef VERSION_JP
    work->x2 = work->x + work->textSlotCount * 0xA00;
    work->x3 = work->x2 + work->textSlotCount2 * 0xA00;
#elif defined(VERSION_EU)
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        work->x3 = work->x + ((GetTextSlotsWidth(work->textSlots, work->textSlotCount) + 3) << 8);
        work->x2 = work->x3 + ((GetTextSlotsWidth(work->textSlots3, work->textSlotCount3) + 3) << 8);
        DrawTextSlots((work->x2 >> 8) + GetTextSlotsWidth(work->textSlots2, work->textSlotCount2), work->y3 >> 8,
                      work->textSlots4, work->textPalette, 40, work->textSlotCount4);
        break;
    case LANGUAGE_FRENCH:
        work->x3 = work->x + ((GetTextSlotsWidth(work->textSlots, work->textSlotCount) + 3) << 8);
        work->x2 = work->x3 + ((GetTextSlotsWidth(work->textSlots3, work->textSlotCount3) + 3) << 8);
        DrawTextSlots((work->x2 >> 8) + GetTextSlotsWidth(work->textSlots2, work->textSlotCount2), work->y3 >> 8,
                      work->textSlots4, work->textPalette, 40, work->textSlotCount4);
        break;
    case LANGUAGE_GERMAN:
        work->x2 = work->x + ((GetTextSlotsWidth(work->textSlots, work->textSlotCount) + 3) << 8);
        work->x3 = work->x2 + ((GetTextSlotsWidth(work->textSlots2, work->textSlotCount2) + 3) << 8);
        break;
    case LANGUAGE_ITALIAN:
        work->x3 = work->x + ((GetTextSlotsWidth(work->textSlots, work->textSlotCount) + 3) << 8);
        work->x2 = work->x3 + ((GetTextSlotsWidth(work->textSlots3, work->textSlotCount3) + 3) << 8);
        DrawTextSlots((work->x2 >> 8) + GetTextSlotsWidth(work->textSlots2, work->textSlotCount2), work->y3 >> 8,
                      work->textSlots4, work->textPalette, 40, work->textSlotCount4);
        break;
    case LANGUAGE_SPANISH:
        work->x3 = work->x + ((GetTextSlotsWidth(work->textSlots, work->textSlotCount) + 3) << 8);
        work->x2 = work->x3 + ((GetTextSlotsWidth(work->textSlots3, work->textSlotCount3) + 3) << 8);
        DrawTextSlots((work->x2 >> 8) + GetTextSlotsWidth(work->textSlots2, work->textSlotCount2), work->y3 >> 8,
                      work->textSlots4, work->textPalette, 40, work->textSlotCount4);
        break;
    }
#else
    work->x3 = work->x + ((GetTextSlotsWidth(work->textSlots, work->textSlotCount) + 3) << 8);
    work->x2 = work->x3 + ((GetTextSlotsWidth(work->textSlots3, work->textSlotCount3) + 3) << 8);
#endif
#ifdef VERSION_EU
    DrawSprite(72, work->y >> 8, NULL, work->tiles, work->palette, NULL, 0, 41);
#else
    DrawSprite(72, work->y >> 8, gUnk_09EF126C[0], work->tiles, work->palette, NULL, 0, 41);
#endif
    DrawTextSlots(work->x >> 8, work->y2 >> 8, work->textSlots, work->textPalette, 40, work->textSlotCount);
    DrawTextSlots(work->x2 >> 8, work->y3 >> 8, work->textSlots2, work->textPalette, 40, work->textSlotCount2);
    DrawTextSlots(work->x3 >> 8, work->y4 >> 8, work->textSlots3, work->textPalette, 40, work->textSlotCount3);
#ifdef VERSION_US
    DrawTextSlots((work->x2 >> 8) + GetTextSlotsWidth(work->textSlots2, work->textSlotCount2), work->y3 >> 8,
                  work->textSlots4, work->textPalette, 40, work->textSlotCount4);
#endif
}

void Lvup_msg_3(LvupMsgWork* work) {
    FreeTextSlots(work->textSlots, 20);
    FreeTextSlots(work->textSlots2, 20);
    FreeTextSlots(work->textSlots3, 20);
#ifndef VERSION_JP
    FreeTextSlots(work->textSlots4, 20);
#endif
    ReleaseObjPalette(work->textPalette);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

TaskDesc gTaskDescLvupMsg = {
    "Lvup msg",
    (TaskInitFunc)Lvup_msg_0,
    (TaskUpdateFunc)Lvup_msg_1,
    (TaskDrawFunc)Lvup_msg_2,
    (TaskDestroyFunc)Lvup_msg_3,
    sizeof(LvupMsgWork),
};
