#include "card_localized_data.h"
#include "msg_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "msg_api.h"
#include "card_battle.h"
#include "m4a_song.h"
#include "game_state.h"
#include "text.h"
#include "monsgage.h"
#include "fade.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "display.h"
#include "engine_math.h"
#include "listpool.h"
#include "anim.h"
#include "obj.h"
#include "text_types.h"
#include "taskpool.h"
#include "key.h"
#include "gba/syscall.h"
#include "card.h"
#include "card_message_assets.h"
#include <stddef.h>
#include "game.h"
#include "bos4_api.h"
#include "sprites_card.h"
#include "songs.h"
#include "jiminy_data.h"
#include "common_text.h"

u8 UpdateLvupMsgSlideIn(LvupMsgWork* w, void* a);

#ifdef VERSION_EU
static const u8 sLvupMsgPeriod[] = ".";
#elif defined(VERSION_US)
static const u16 sLvupMsgPeriod[2] = { '.', 0 };
#endif

void Lvup_msg_0(LvupMsgWork* w, StatIncreaseDisplayArgs* a) {
    StatIncreaseDisplayArgs args = *a;

    InitTextSlots(w->textSlots, 20);
    InitTextSlots(w->textSlots2, 20);
    InitTextSlots(w->textSlots3, 20);
#ifndef VERSION_JP
    InitTextSlots(w->textSlots4, 20);
    w->textSlotCount4 = LoadTextSlots((u16*)sLvupMsgPeriod, w->textSlots4);
#endif
    w->amount = a->amount;
    w->active = a->done;
    if (args.flags & 0x8000) {
#ifdef VERSION_EU
        w->textSlotCount = LoadTextSlots(eu_0805E924(&gUnk_0815A09A), w->textSlots);
#else
        w->textSlotCount = LoadTextSlots(gUnk_0815A09A, w->textSlots);
#endif
    } else if (args.flags & 0x4000) {
#ifdef VERSION_EU
        w->textSlotCount = LoadTextSlots(eu_0805E924(&gUnk_0815A198), w->textSlots);
#else
        w->textSlotCount = LoadTextSlots(gUnk_0815A198, w->textSlots);
#endif
    } else if (!(gGameState.flags & GAME_FLAG_RIKU)) {
#ifdef VERSION_EU
        w->textSlotCount = LoadTextSlots(eu_0805E924(&gUnk_0815A0EE), w->textSlots);
#else
        w->textSlotCount = LoadTextSlots(gUnk_0815A0EE, w->textSlots);
#endif
    } else {
#ifdef VERSION_EU
        w->textSlotCount = LoadTextSlots(eu_0805E924(&gUnk_0815A152), w->textSlots);
#else
        w->textSlotCount = LoadTextSlots(gUnk_0815A152, w->textSlots);
#endif
    }
    w->textSlotCount2 = LoadTwoDigitTextSlots((u8)w->amount, w->textSlots2);
#ifdef VERSION_EU
    if ((args.flags & 0x8000) && gLanguage == 4) {
        w->textSlotCount3 = LoadTextSlots(eu_0805E924(&gUnkEu_08895EDC), w->textSlots3);
    } else {
        w->textSlotCount3 = LoadTextSlots(eu_0805E924(&gUnk_0815A0A0), w->textSlots3);
    }
#else
    w->textSlotCount3 = LoadTextSlots(gUnk_0815A0A0, w->textSlots3);
#endif
    w->textPalette = LoadTextPalette(1);
    FadeSetPaletteExcluded(w->textPalette->index + 16, 1);
    w->x = 0x1000;
    w->x2 = 0x3000;
    w->x3 = 0x4200;
    w->y2 = 0xC800;
    w->y3 = 0xC800;
    w->y4 = 0xC800;
    w->y = 0xCE00;
    w->slideSteps = 14;
    w->unk_2B1 = 0;
    w->x = ((144 - (GetTextSlotsWidth(w->textSlots, w->textSlotCount)
#ifndef VERSION_JP
                         + GetTextSlotsWidth(w->textSlots4, w->textSlotCount4)
#endif
                         + GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)
                         + GetTextSlotsWidth(w->textSlots3, w->textSlotCount3))) / 2) << 8;
#ifdef VERSION_EU
    w->tiles = AllocSpriteFrameTiles(0x780);
    UpdateSpriteFrameTiles(w->tiles, gUnk_09EF126C[0], gUnk_093F7C9C);
#else
    w->tiles = LoadObjTiles(gUnk_093F7C9C, 0xFC0);
#endif
    w->palette = LoadObjPalette(gCard00Palette, 32);
}

s32 Lvup_msg_1(LvupMsgWork* w, void* a) {
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateLvupMsgSlideIn);
    w->unk_2B1++;
    return 1;
}
u8 UpdateLvupMsgSlideIn(LvupMsgWork* w, void* a) {
    s8* counter = &w->slideSteps;

    if (*counter > 0) {
        ApproachValue(&w->y, 0x6C00, *counter);
        ApproachValue(&w->y2, 0x6600, *counter);
        ApproachValue(&w->y3, 0x6600, *counter);
        ApproachValue(&w->y4, 0x6600, *counter);
        (*counter)--;
    } else if (*counter == 0) {
        m4aSongNumStart(SONG_SYS_CHAGEF2);
        w->slideSteps = -1;
    }

    if (*w->active == 0) {
        return 0;
    }
    return 1;
}
void Lvup_msg_2(LvupMsgWork* w) {
#ifdef VERSION_JP
    w->x2 = w->x + w->textSlotCount * 0xA00;
    w->x3 = w->x2 + w->textSlotCount2 * 0xA00;
#elif defined(VERSION_EU)
    switch (gLanguage) {
    case 0:
        w->x3 = w->x + ((GetTextSlotsWidth(w->textSlots, w->textSlotCount) + 3) << 8);
        w->x2 = w->x3 + ((GetTextSlotsWidth(w->textSlots3, w->textSlotCount3) + 3) << 8);
        DrawTextSlots((w->x2 >> 8) + GetTextSlotsWidth(w->textSlots2, w->textSlotCount2), w->y3 >> 8,
                      w->textSlots4, w->textPalette, 40, w->textSlotCount4);
        break;
    case 1:
        w->x3 = w->x + ((GetTextSlotsWidth(w->textSlots, w->textSlotCount) + 3) << 8);
        w->x2 = w->x3 + ((GetTextSlotsWidth(w->textSlots3, w->textSlotCount3) + 3) << 8);
        DrawTextSlots((w->x2 >> 8) + GetTextSlotsWidth(w->textSlots2, w->textSlotCount2), w->y3 >> 8,
                      w->textSlots4, w->textPalette, 40, w->textSlotCount4);
        break;
    case 2:
        w->x2 = w->x + ((GetTextSlotsWidth(w->textSlots, w->textSlotCount) + 3) << 8);
        w->x3 = w->x2 + ((GetTextSlotsWidth(w->textSlots2, w->textSlotCount2) + 3) << 8);
        break;
    case 3:
        w->x3 = w->x + ((GetTextSlotsWidth(w->textSlots, w->textSlotCount) + 3) << 8);
        w->x2 = w->x3 + ((GetTextSlotsWidth(w->textSlots3, w->textSlotCount3) + 3) << 8);
        DrawTextSlots((w->x2 >> 8) + GetTextSlotsWidth(w->textSlots2, w->textSlotCount2), w->y3 >> 8,
                      w->textSlots4, w->textPalette, 40, w->textSlotCount4);
        break;
    case 4:
        w->x3 = w->x + ((GetTextSlotsWidth(w->textSlots, w->textSlotCount) + 3) << 8);
        w->x2 = w->x3 + ((GetTextSlotsWidth(w->textSlots3, w->textSlotCount3) + 3) << 8);
        DrawTextSlots((w->x2 >> 8) + GetTextSlotsWidth(w->textSlots2, w->textSlotCount2), w->y3 >> 8,
                      w->textSlots4, w->textPalette, 40, w->textSlotCount4);
        break;
    }
#else
    w->x3 = w->x + ((GetTextSlotsWidth(w->textSlots, w->textSlotCount) + 3) << 8);
    w->x2 = w->x3 + ((GetTextSlotsWidth(w->textSlots3, w->textSlotCount3) + 3) << 8);
#endif
#ifdef VERSION_EU
    DrawSprite(72, w->y >> 8, 0, w->tiles, w->palette, 0, 0, 41);
#else
    DrawSprite(72, w->y >> 8, gUnk_09EF126C[0], w->tiles, w->palette, 0, 0, 41);
#endif
    DrawTextSlots(w->x >> 8, w->y2 >> 8, w->textSlots, w->textPalette, 40, w->textSlotCount);
    DrawTextSlots(w->x2 >> 8, w->y3 >> 8, w->textSlots2, w->textPalette, 40, w->textSlotCount2);
    DrawTextSlots(w->x3 >> 8, w->y4 >> 8, w->textSlots3, w->textPalette, 40, w->textSlotCount3);
#ifdef VERSION_US
    DrawTextSlots((w->x2 >> 8) + GetTextSlotsWidth(w->textSlots2, w->textSlotCount2), w->y3 >> 8,
                  w->textSlots4, w->textPalette, 40, w->textSlotCount4);
#endif
}
void Lvup_msg_3(LvupMsgWork* w) {
    FreeTextSlots(w->textSlots, 20);
    FreeTextSlots(w->textSlots2, 20);
    FreeTextSlots(w->textSlots3, 20);
#ifndef VERSION_JP
    FreeTextSlots(w->textSlots4, 20);
#endif
    ReleaseObjPalette(w->textPalette);
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

TaskDesc gTaskDescLvupMsg = {
    "Lvup msg",
    (TaskInitFunc)Lvup_msg_0,
    (TaskUpdateFunc)Lvup_msg_1,
    (TaskDrawFunc)Lvup_msg_2,
    (TaskDestroyFunc)Lvup_msg_3,
    sizeof(LvupMsgWork),
};
