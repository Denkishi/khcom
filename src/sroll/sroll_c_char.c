/**
 * sroll_c_char.c
 * Staff Roll Ending Character
 */

#include "sroll.h"
#include "sprites_staff_roll.h"
#include "anim.h"
#include "obj_api.h"
#include <stddef.h>
#include "system_state.h"
#include "taskpool.h"
#include "types.h"
#include "sprite_palettes.h"

static s32 Square(s32 x) {
    return x * x;
}

void task_sroll_c_char_0(SrollCCharWork* work, s32 kind) {
    AnimState* p;
    s32 i;

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
#endif
    if (kind == 0) {
#ifdef VERSION_JP
        work->tiles = LoadObjTiles(gSrollSoraEpilogueTiles, 200 * 16);
#else
        work->tiles = LoadObjTiles(gSrollSoraEpilogueTiles, 154 * 32);
#endif
        work->palette = LoadObjPalette(gUnk_09D6CF54, 224);

        for (i = 0, p = work->anim; i <= 4; i++) {
            AnimInit(p, gSrollSoraEpilogueAnims, gSrollSoraEpilogueFrames);
            AnimStart(p, i, 0);
            p++;
        }
    } else {
#ifdef VERSION_JP
        work->tiles = LoadObjTiles(gSrollRikuEpilogueTiles, 200 * 16);
#else
        work->tiles = LoadObjTiles(gSrollRikuEpilogueTiles, 146 * 32);
#endif
        work->palette = LoadObjPalette(gUnk_09D6D034, 224);

        for (i = 0, p = work->anim; i <= 4; i++) {
            AnimInit(p, gSrollRikuEpilogueAnims, gSrollRikuEpilogueFrames);
            AnimStart(p, i, 0);
            p++;
        }
    }

#ifdef VERSION_EU
        break;
    case LANGUAGE_FRENCH:
        if (kind == 0) {
            work->tiles = LoadObjTiles(gSrollSoraEpilogueFrenchTiles, 168 * 32);
            work->palette = LoadObjPalette(gUnk_09D6CF54, 224);

            for (i = 0, p = work->anim; i <= 4; i++) {
                AnimInit(p, gSrollSoraEpilogueFrenchAnims, gSrollSoraEpilogueFrenchFrames);
                AnimStart(p, i, 0);
                p++;
            }
        } else {
            work->tiles = LoadObjTiles(gSrollRikuEpilogueFrenchTiles, 158 * 32);
            work->palette = LoadObjPalette(gUnk_09D6D034, 224);

            for (i = 0, p = work->anim; i <= 4; i++) {
                AnimInit(p, gSrollRikuEpilogueFrenchAnims, gSrollRikuEpilogueFrenchFrames);
                AnimStart(p, i, 0);
                p++;
            }
        }

        break;
    case LANGUAGE_SPANISH:
        if (kind == 0) {
            work->tiles = LoadObjTiles(gSrollSoraEpilogueSpanishTiles, 167 * 32);
            work->palette = LoadObjPalette(gUnk_09D6CF54, 224);

            for (i = 0, p = work->anim; i <= 4; i++) {
                AnimInit(p, gSrollSoraEpilogueSpanishAnims, gSrollSoraEpilogueSpanishFrames);
                AnimStart(p, i, 0);
                p++;
            }
        } else {
            work->tiles = LoadObjTiles(gSrollRikuEpilogueSpanishTiles, 186 * 32);
            work->palette = LoadObjPalette(gUnk_09D6D034, 224);

            for (i = 0, p = work->anim; i <= 4; i++) {
                AnimInit(p, gSrollRikuEpilogueSpanishAnims, gSrollRikuEpilogueSpanishFrames);
                AnimStart(p, i, 0);
                p++;
            }
        }

        break;
    case LANGUAGE_ITALIAN:
        if (kind == 0) {
            work->tiles = LoadObjTiles(gSrollSoraEpilogueItalianTiles, 142 * 32);
            work->palette = LoadObjPalette(gUnk_09D6CF54, 224);

            for (i = 0, p = work->anim; i <= 4; i++) {
                AnimInit(p, gSrollSoraEpilogueItalianAnims, gSrollSoraEpilogueItalianFrames);
                AnimStart(p, i, 0);
                p++;
            }
        } else {
            work->tiles = LoadObjTiles(gSrollRikuEpilogueItalianTiles, 162 * 32);
            work->palette = LoadObjPalette(gUnk_09D6D034, 224);

            for (i = 0, p = work->anim; i <= 4; i++) {
                AnimInit(p, gSrollRikuEpilogueItalianAnims, gSrollRikuEpilogueItalianFrames);
                AnimStart(p, i, 0);
                p++;
            }
        }

        break;
    case LANGUAGE_GERMAN:
    default:
        if (kind == 0) {
            work->tiles = LoadObjTiles(gSrollSoraEpilogueGermanTiles, 188 * 32);
            work->palette = LoadObjPalette(gUnk_09D6CF54, 224);

            for (i = 0, p = work->anim; i <= 4; i++) {
                AnimInit(p, gSrollSoraEpilogueGermanAnims, gSrollSoraEpilogueGermanFrames);
                AnimStart(p, i, 0);
                p++;
            }
        } else {
            work->tiles = LoadObjTiles(gSrollRikuEpilogueGermanTiles, 190 * 32);
            work->palette = LoadObjPalette(gUnk_09D6D034, 224);

            for (i = 0, p = work->anim; i <= 4; i++) {
                AnimInit(p, gSrollRikuEpilogueGermanAnims, gSrollRikuEpilogueGermanFrames);
                AnimStart(p, i, 0);
                p++;
            }
        }

        break;
    }
#endif
}

u8 task_sroll_c_char_1(SrollCCharWork* work) {
    AnimState* p;
    s32 i;

    p = work->anim;

    for (i = 4; i >= 0; i--) {
        AnimUpdate(p);
        p++;
    }

    return 1;
}

void task_sroll_c_char_2(SrollCCharWork* work) {
    AnimState* p;
    s32 i;
    u16 flags;

    flags = 0;
    p = work->anim;

    for (i = 4; i >= 0; i--) {
        DrawSprite(120, 80, AnimGetGfx(p), work->tiles, work->palette, NULL, flags, 0xFF0);
        p++;
    }
}

void task_sroll_c_char_3(SrollCCharWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

TaskDesc gTaskDescSrollCChar = {
    "task_sroll_c_char",
    (TaskInitFunc)task_sroll_c_char_0,
    (TaskUpdateFunc)task_sroll_c_char_1,
    (TaskDrawFunc)task_sroll_c_char_2,
    (TaskDestroyFunc)task_sroll_c_char_3,
    sizeof(SrollCCharWork),
};
