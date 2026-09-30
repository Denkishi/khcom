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

void WorldSel_Before_0(WorldSelBeforeWork* w, WorldSelBeforeArgs* a) {
    u8 i;

    FadeToAmount(0, 16, 8);
    *(WorldSelBeforeArgs*)&w->x = *a;
    w->tiles = LoadObjTiles(gUnk_093FB0CC, 0xC0);
    w->palette = LoadObjPalette(gUnk_09619378, 32);
    w->tiles2 = LoadObjTiles(gUnk_093FB1AC, 0x4A0);
    w->palette2 = AllocObjPalette(32);
    w->spriteCount = 6;
    w->animStep = 0;
    w->animTimer = 0;
    w->risenCount = 0;
    UpdateAllocatedObjPalette(w->palette2, &gUnk_09619178[gWorldSelAnims[w->animStep].palette << 5]);
    FadeSetPaletteExcluded(w->palette->index + 16, 1);
    FadeSetPaletteExcluded(w->palette2->index + 16, 1);

    for (i = 0; i < w->spriteCount; i++) {
        w->angle[i] = 0x80;
        w->z2[i] = 0;
        w->x2[i] = gSineTable[w->angle[i]] * 24 + w->x;
        w->y2[i] = -gSineTable[w->angle[i] + 64] * 12 + w->y;
    }

    m4aSongNumStart(SONG_SND_212);
}
s32 WorldSel_Before_1(WorldSelBeforeWork* w) {
    u8 i;

    if (w->risenCount < w->spriteCount) {
        w->z2[w->risenCount] -= (s32)(24.0f / (256.0f / (float)w->spriteCount * 0.25f) * 256.0f);

        if (w->z2[w->risenCount] <= -6144) {
            w->risenCount++;
        }
    }

    for (i = 0; i < w->risenCount; i++) {
        w->x2[i] = gSineTable[w->angle[i]] * 24 + w->x;
        w->y2[i] = -gSineTable[w->angle[i] + 64] * 12 + w->y;
        w->angle[i] += 4;
    }

    if (++w->animTimer == gWorldSelAnims[w->animStep].duration) {
        do {
            w->animStep = w->animStep > 28 ? 0 : w->animStep + 1;
        } while (0);

        w->animTimer = 0;
        UpdateAllocatedObjPalette(w->palette2, &gUnk_09619178[gWorldSelAnims[w->animStep].palette << 5]);
    }

    return 1;
}
void WorldSel_Before_2(WorldSelBeforeWork* w) {
    u8 i;

    for (i = 0; i < w->spriteCount; i++) {
        DrawSprite((w->x2[i] >> 8) - (gFieldState->x >> 8),
                   (w->y2[i] >> 8) + ((w->z + w->z2[i]) >> 8) - (gFieldState->y >> 8),
                   (&gUnk_09EF1278[4])[0], w->tiles, w->palette, 0, 0x800,
                   (u16)(-0x1004 - (w->y2[i] >> 8) * 4));
    }

    DrawSprite((w->x >> 8) - (gFieldState->x >> 8) - 32,
               (w->y >> 8) + (w->z >> 8) - (gFieldState->y >> 8) - 16,
               (&gUnk_09EF1278[6])[0], w->tiles2, w->palette2, 0, 0x800,
               (u16)(-0x1004 - ((w->y - 512) >> 8) * 4));
}

void WorldSel_Before_3(WorldSelBeforeWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjPalette(w->palette);
    ReleaseObjPalette(w->palette2);
}
void func_080A581C(u8* work) {
    TaskCreate(&work[0x10], &gTaskDescWorldSelBefore, work);
}

void CreateWorldSelBeforeTask(void* a, s32 x, s32 y, s32 z) {
    WorldSelBeforeArgs args;

    args.x = x;
    args.y = y;
    args.z = z;
    TaskCreate(a, &gTaskDescWorldSelBefore, &args);
}

WorldSelAnim gWorldSelAnims[30] = {
    { 0, 10, { 0, 0 } },
    { 1, 6, { 0, 0 } },
    { 2, 4, { 0, 0 } },
    { 3, 4, { 0, 0 } },
    { 4, 4, { 0, 0 } },
    { 5, 4, { 0, 0 } },
    { 6, 4, { 0, 0 } },
    { 7, 4, { 0, 0 } },
    { 8, 4, { 0, 0 } },
    { 9, 4, { 0, 0 } },
    { 10, 4, { 0, 0 } },
    { 11, 4, { 0, 0 } },
    { 12, 4, { 0, 0 } },
    { 13, 4, { 0, 0 } },
    { 14, 6, { 0, 0 } },
    { 15, 10, { 0, 0 } },
    { 14, 6, { 0, 0 } },
    { 13, 4, { 0, 0 } },
    { 12, 4, { 0, 0 } },
    { 11, 4, { 0, 0 } },
    { 10, 4, { 0, 0 } },
    { 9, 4, { 0, 0 } },
    { 8, 4, { 0, 0 } },
    { 7, 4, { 0, 0 } },
    { 6, 4, { 0, 0 } },
    { 5, 4, { 0, 0 } },
    { 4, 4, { 0, 0 } },
    { 3, 4, { 0, 0 } },
    { 2, 4, { 0, 0 } },
    { 1, 6, { 0, 0 } },
};

TaskDesc gTaskDescWorldSelBefore = {
    "WorldSel Before",
    (TaskInitFunc)WorldSel_Before_0,
    (TaskUpdateFunc)WorldSel_Before_1,
    (TaskDrawFunc)WorldSel_Before_2,
    (TaskDestroyFunc)WorldSel_Before_3,
    sizeof(WorldSelBeforeWork),
};
