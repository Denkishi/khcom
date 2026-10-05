/**
 * sroll_b_logo.c
 * Staff Roll Logo
 */

#include "sroll.h"
#include "sprites_staff_roll.h"
#include "fade.h"
#include "anim.h"
#include "obj_api.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"

static s32 Square(s32 x) {
    return x * x;
}

void task_sroll_b_logo_0(SrollBLogoWork* work, SrollBLogoArg* a) {
    AnimState* anim;
    u32 i;

    work->x = a->x;
    work->y = a->y;
    work->scrollY = a->scrollY;
    work->scrollSpeed = a->scrollSpeed;
#ifdef VERSION_EU
    work->palette = LoadObjPalette(gSrollLogoPalettes, 64);
    work->tiles = LoadObjTiles(gSrollLogoTiles, 94 * 32);
#else
    work->tiles = LoadObjTiles(gSrollLogoTiles, 94 * 32);
    work->palette = LoadObjPalette(gSrollLogoPalettes, 64);
#endif
    anim = &work->anim;
    AnimInit(anim, gSrollLogoAnims, gSrollLogoFrames);
    AnimStart(anim, a->animId, 0);

    for (i = 0; i < 2; i++) {
        FadeSetPaletteExcluded((work->palette->index + i) % 16 + 16, 1);
    }
}

u8 task_sroll_b_logo_1(SrollBLogoWork* work) {
    u8 r;

    r = 1;

    if ((s16)((work->y >> 8) - (*work->scrollY >> 8)) <= -32) {
        r = 0;
    }

    AnimUpdate(&work->anim);
    return r;
}

void task_sroll_b_logo_2(SrollBLogoWork* work) {
    u16 y;

    y = (work->y >> 8) - (*work->scrollY >> 8);
    DrawSprite(work->x >> 8, y, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL, 0, 0xFF0);
}

void task_sroll_b_logo_3(SrollBLogoWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

TaskDesc gTaskDescSrollBLogo = {
    "task_sroll_b_logo",
    (TaskInitFunc)task_sroll_b_logo_0,
    (TaskUpdateFunc)task_sroll_b_logo_1,
    (TaskDrawFunc)task_sroll_b_logo_2,
    (TaskDestroyFunc)task_sroll_b_logo_3,
    sizeof(SrollBLogoWork),
};
