/**
 * sroll_b_secn.c
 * Staff Roll Section Headers
 */

#include "sroll.h"
#include "sprites_staff_roll.h"
#include "fade.h"
#include <stdlib.h>
#include "anim.h"
#include "engine_math.h"
#include "obj_api.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"
#include "sprite_palettes.h"

static s32 Square(s32 x) {
    return x * x;
}

void task_sroll_b_secn_0(SrollBSecnWork* work, SrollBSecnArg* a) {
    u32 i;

    work->timer = 0;
    work->x = a->x;
    work->y = a->y;
    work->scrollY = a->scrollY;
    work->scrollSpeed = a->scrollSpeed;

    if (a->index < 0) {
#ifdef VERSION_JP
        work->tiles = LoadObjTiles(gUnk_09C87A10, 590 * 32);
#else
        work->tiles = LoadObjTiles(gUnk_09C87A10, 606 * 32);
#endif
        work->palette = LoadObjPalette(gUnk_09D6CF34, 32);
        AnimInit(&work->anim, gUnk_09EFB834, gUnk_09EFB828);
        AnimStart(&work->anim, 0, 0);
        AnimInit(&work->anim2, gUnk_09EFB834, gUnk_09EFB828);
        AnimStart(&work->anim2, 0, 0);
    } else {
        work->tiles = LoadObjTiles(gSrollSecnSprites[a->index].tiles, gSrollSecnSprites[a->index].tileSize);
        work->palette = LoadObjPalette(gUnk_09D6BE74, 256);
        AnimInit(&work->anim, gSrollSecnSprites[a->index].anims, gSrollSecnSprites[a->index].gfxTable);
        AnimStart(&work->anim, 0, 0);
        AnimInit(&work->anim2, gSrollSecnSprites[a->index].anims, gSrollSecnSprites[a->index].gfxTable);
        AnimStart(&work->anim2, 1, 0);
    }

    for (i = 0; i < 8; i++) {
        FadeSetPaletteExcluded((work->palette->index + i) % 16 + 16, 1);
    }
}

u8 task_sroll_b_secn_1(SrollBSecnWork* work) {
    u8 r;
    s16 y;

    r = 1;
    y = (work->y >> 8) - (*work->scrollY >> 8);

    if (y <= -32) {
        r = 0;
    }

    if (y <= 159) {
        ApproachValueHalfSteps(&work->x, 0x7800, 20);

        if (abs(work->x - 0x7800) <= 255) {
            work->x = 0x7800;
        }

        if (work->x == 0x7800) {
            AnimUpdate(&work->anim);
            AnimUpdate(&work->anim2);
        }
    }

    work->timer++;
    return r;
}

void task_sroll_b_secn_2(SrollBSecnWork* work) {
    u16 y;

    y = (work->y >> 8) - (*work->scrollY >> 8);
    DrawSprite(120, y, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL, 0, 0xEF0);
    DrawSprite(120, y, AnimGetGfx(&work->anim2), work->tiles, work->palette, NULL, 0, 0xEE0);
}

void task_sroll_b_secn_3(SrollBSecnWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

const SrollSecnSprite gSrollSecnSprites[] = {
    { gUnk_09C5D922, 27 * 32, gUnk_09EFAF98, gUnk_09EFAF78 },
    { gUnk_09C5DD46, 24 * 32, gUnk_09EFAFC0, gUnk_09EFAFA0 },
    { gUnk_09C5E15E, 37 * 32, gUnk_09EFAFE8, gUnk_09EFAFC8 },
    { gUnk_09C5E6E6, 27 * 32, gUnk_09EFB010, gUnk_09EFAFF0 },
    { gUnk_09C5EB5E, 39 * 32, gUnk_09EFB038, gUnk_09EFB018 },
    { gUnk_09C5F12C, 35 * 32, gUnk_09EFB060, gUnk_09EFB040 },
    { gUnk_09C5F678, 41 * 32, gUnk_09EFB088, gUnk_09EFB068 },
    { gUnk_09C5FC54, 21 * 32, gUnk_09EFB0B0, gUnk_09EFB090 },
    { gUnk_09C6000A, 39 * 32, gUnk_09EFB0D8, gUnk_09EFB0B8 },
    { gUnk_09C60662, 61 * 32, gUnk_09EFB100, gUnk_09EFB0E0 },
    { gUnk_09C60F20, 47 * 32, gUnk_09EFB128, gUnk_09EFB108 },
#ifdef VERSION_EU
    { gUnkEu_09CE57D2, 61 * 32, gUnkEu_09F87594, gUnkEu_09F87574 },
#endif
    { gUnk_09C61676, 61 * 32, gUnk_09EFB150, gUnk_09EFB130 },
#ifdef VERSION_JP
    { gUnk_09C61F2E, 41 * 32, gUnk_09EFB178, gUnk_09EFB158 },
#endif
    { gUnk_09C6259C, 50 * 32, gUnk_09EFB1A0, gUnk_09EFB180 },
    { gUnk_09C62CC8, 35 * 32, gUnk_09EFB1C8, gUnk_09EFB1A8 },
    { gUnk_09C63244, 47 * 32, gUnk_09EFB1F0, gUnk_09EFB1D0 },
#ifdef VERSION_JP
    { gUnkJp_09C5DC00, 57 * 32, gUnkJp_09ED2C8C, gUnkJp_09ED2C6C },
    { gUnkJp_09C5E4D2, 83 * 32, gUnkJp_09ED2CB4, gUnkJp_09ED2C94 },
    { gUnkJp_09C5F020, 41 * 32, gUnkJp_09ED2CDC, gUnkJp_09ED2CBC },
    { gUnkJp_09C5F6C2, 71 * 32, gUnkJp_09ED2D04, gUnkJp_09ED2CE4 },
    { gUnkJp_09C6012C, 77 * 32, gUnkJp_09ED2D2C, gUnkJp_09ED2D0C },
#endif
    { gUnk_09C853DA, 79 * 32, gUnk_09EFB780, gUnk_09EFB760 },
#ifndef VERSION_JP
    { gUnk_09C85EDE, 48 * 32, gUnk_09EFB7A8, gUnk_09EFB788 },
    { gUnk_09C865FC, 44 * 32, gUnk_09EFB7D0, gUnk_09EFB7B0 },
#endif
    { gUnk_09C86C68, 41 * 32, gUnk_09EFB7F8, gUnk_09EFB7D8 },
    { gUnk_09C872D4, 50 * 32, gUnk_09EFB820, gUnk_09EFB800 },
};

TaskDesc gTaskDescSrollBSecn = {
    "task_sroll_b_secn",
    (TaskInitFunc)task_sroll_b_secn_0,
    (TaskUpdateFunc)task_sroll_b_secn_1,
    (TaskDrawFunc)task_sroll_b_secn_2,
    (TaskDestroyFunc)task_sroll_b_secn_3,
    sizeof(SrollBSecnWork),
};
