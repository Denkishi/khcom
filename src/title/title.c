#include "registration_data.h"
#include "system_state.h"
#include "title_api.h"
#include "pallet.h"
#include "title.h"
#include "gba/keys.h"
#include "sprites_title.h"
#include "songs.h"
#include <string.h>
#include "anim.h"
#include "engine_math.h"
#include "game_state.h"
#include "key.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "title_types.h"
#include "types.h"

#ifdef VERSION_EU
extern void** gTitleLumiSpritesEu[5];
extern void** gTitleLumiSpritesAltEu[5];
#endif

TaskDesc gTaskDescTitleLogo = {
    "task_title_logo",
    (TaskInitFunc)task_title_logo_0,
    (TaskUpdateFunc)task_title_logo_1,
    (TaskDrawFunc)task_title_logo_2,
    (TaskDestroyFunc)task_title_logo_3,
    sizeof(TitleLogoWork),
};

TaskDesc gTaskDescTitleObj = {
    "task_title_obj",
    (TaskInitFunc)task_title_obj_0,
    (TaskUpdateFunc)task_title_obj_1,
    (TaskDrawFunc)task_title_obj_2,
    (TaskDestroyFunc)task_title_obj_3,
    sizeof(TitleObjWork),
};

static const s32 sTitleMenuChoiceOrder[4] = {4, 5, 1, 2};

#ifdef VERSION_EU
static void** sTitleMenuEntrySpritesEu[5] = {
    gUnkEu_09F81B78,
    gUnkEu_09F81B94,
    gUnkEu_09F81BE8,
    gUnkEu_09F81BCC,
    gUnkEu_09F81BB0,
};
#endif

TaskDesc gTaskDescTitleMenu = {
    "task_title_menu",
    (TaskInitFunc)task_title_menu_0,
    (TaskUpdateFunc)task_title_menu_1,
    (TaskDrawFunc)task_title_menu_2,
    (TaskDestroyFunc)task_title_menu_3,
    sizeof(TitleMenuWork),
};

static const s16 sTitleLumiLevels[3] = {-7, 0, 3};

u8 gTitleLogoScaleDone;
u8 gTitleObjSlideDone __attribute__((aligned(4)));

void TitleLogoLoadSprites(TitleLogoWork* work) {
    work->sprites[0].tiles = LoadObjTiles(gUnk_0976E9F4, 0x240);
    work->sprites[0].gfx = gUnk_09EF659C;

    if (gGameState.flags & GAME_FLAG_RIKU_TITLE) {
        work->sprites[1].tiles = LoadObjTiles(gUnk_09776076, 0x43C0);
        work->sprites[1].gfx = gUnk_09EF669C;
        work->sprites[1].palette = LoadObjPalette(gUnk_0984AA18, 0x20);
    } else {
        work->sprites[1].tiles = LoadObjTiles(gUnk_0976EC54, 0xE0);
        work->sprites[1].gfx = gUnk_09EF65A4;
        work->sprites[1].palette = LoadObjPalette(gUnk_0984A6D8, 0x20);
    }

    work->sprites[2].tiles = LoadObjTiles(gUnk_0976ED5A, 0x380);
    work->sprites[2].gfx = gUnk_09EF65AC;
    work->sprites[3].tiles = LoadObjTiles(gUnk_0976F0F6, 0xC0);
    work->sprites[3].gfx = gUnk_09EF65B4;
    work->sprites[4].tiles = LoadObjTiles(gUnk_0976F1F0, 0xAC0);
    work->sprites[4].gfx = gUnk_09EF65BC;
    work->sprites[5].tiles = LoadObjTiles(gUnk_0976FD96, 0x1140);
    work->sprites[5].gfx = gUnk_09EF65C4;
    work->sprites[0].palette = LoadObjPalette(gUnk_0984A6B8, 0x20);
    work->sprites[2].palette = LoadObjPalette(gUnk_0984A6F8, 0x20);
    work->sprites[3].palette = LoadObjPalette(gUnk_0984A6F8, 0x20);
    work->sprites[4].palette = LoadObjPalette(gUnk_0984A718, 0x20);
    work->sprites[5].palette = LoadObjPalette(gUnk_0984A738, 0x20);
    work->scale = 0;
    work->unk_48 = 0xC00;
    work->unk_50 = 0;
    gTitleLogoScaleDone = 0;
}

void task_title_logo_0(TitleLogoWork* work) {
    TitleLogoLoadSprites(work);
}

u8 task_title_logo_1(TitleLogoWork* work) {
    if (IsTitleLogoShown() && gTitleLogoScaleDone == 0) {
        work->unk_48 -= 76;
        work->scale += 6;

        if (work->scale > 255) {
            work->scale = 0x100;
            work->unk_48 = 0;
            gTitleLogoScaleDone = 1;
        }
    }

    return 1;
}

void task_title_logo_2(TitleLogoWork* work) {
    s32 i;
    ObjAffine* affine;
    s16 x;
    s16 y;

    for (i = 0; i < 6; i++) {
#ifndef VERSION_JP
        if (i == 1 && !(gGameState.flags & GAME_FLAG_RIKU_TITLE)) {
            continue;
        }
#endif

        if (gGameState.flags & GAME_FLAG_RIKU_TITLE) {
            x = 0xA4;
        } else {
            x = 0x50;
        }

        y = 70;

        if (i == 0) {
            x++;
        }

        if (i == 1) {
            if (work->scale == 0) {
                continue;
            }

            affine = AllocObjAffine(0, 0x100, work->scale, 0);

            if (gGameState.flags & GAME_FLAG_RIKU_TITLE) {
                y = 86;
                x--;
            } else {
                y = 87;
            }
        } else {
            affine = 0;
        }

        DrawSprite(x, y, work->sprites[i].gfx, work->sprites[i].tiles, work->sprites[i].palette, affine, 0, i + 20);
    }
}

void task_title_logo_3(TitleLogoWork* work) {
    s32 i;

    for (i = 0; i < 6; i++) {
        ReleaseObjTiles(work->sprites[i].tiles);
        ReleaseObjPalette(work->sprites[i].palette);
    }
}

void func_080D6548(u8* src, u16* dst, u16 size) {
    while (size != 0) {
        *dst = src[0] + (src[2] << 8);
        dst++;
        src += 4;
        size -= 4;
    }
}

u8 IsTitleLogoScaleDone() {
    return gTitleLogoScaleDone;
}

void task_title_obj_0(TitleObjWork* work) {
    s32 t;

    t = (gGameState.flags & GAME_FLAG_RIKU_TITLE) ? 0x20 : 0;
#ifdef VERSION_EU
    work->sprites[0].palette = LoadObjPalette(gUnk_0984A718, 0x20);

    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        work->sprites[0].tiles = LoadObjTiles(gUnkEu_09750AF8, 0x3C0);
        work->sprites[0].gfx = gUnkEu_09F81C54[0];
        break;
    case LANGUAGE_FRENCH:
        work->sprites[0].tiles = LoadObjTiles(gUnkEu_09750EE4, 0x3C0);
        work->sprites[0].gfx = gUnkEu_09F81C5C[0];
        break;
    case LANGUAGE_GERMAN:
        work->sprites[0].tiles = LoadObjTiles(gUnkEu_09751ADE, 0x400);
        work->sprites[0].gfx = gUnkEu_09F81C74[0];
        break;
    case LANGUAGE_ITALIAN:
        work->sprites[0].tiles = LoadObjTiles(gUnkEu_097516F8, 0x3C0);
        work->sprites[0].gfx = gUnkEu_09F81C6C[0];
        break;
    case LANGUAGE_SPANISH:
        work->sprites[0].tiles = LoadObjTiles(gUnkEu_097512CA, 0x400);
        work->sprites[0].gfx = gUnkEu_09F81C64[0];
        break;
    case 5:
    case 6:
        break;
    }
#else
    work->sprites[0].tiles = LoadObjTiles(gUnk_09771060, 0x3C0);
    work->sprites[0].palette = LoadObjPalette(gUnk_0984A718, 0x20);
    work->sprites[0].gfx = gUnk_09EF65E0[0];
#endif

    if (gGameState.flags & GAME_FLAG_RIKU_TITLE) {
#ifdef VERSION_EU
        if (gLanguage == LANGUAGE_SPANISH || gLanguage == LANGUAGE_GERMAN) {
            work->sprites[0].x = 0xB500;
        } else {
            work->sprites[0].x = 0xBA00;
        }
#else
        work->sprites[0].x = 0xBA00;
#endif
        work->sprites[0].y = 0x76;
    } else {
        work->sprites[0].x = 0x3D00;
        work->sprites[0].y = 0x77;
    }

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        work->sprites[1].tiles = LoadObjTiles(gUnkEu_0973F402, 0x700);
        break;
    case LANGUAGE_FRENCH:
        work->sprites[1].tiles = LoadObjTiles(gUnkEu_0973FC6A, 0x7A0);
        break;
    case LANGUAGE_GERMAN:
        work->sprites[1].tiles = LoadObjTiles(gUnkEu_097415E8, 0x800);
        break;
    case LANGUAGE_ITALIAN:
        work->sprites[1].tiles = LoadObjTiles(gUnkEu_09740D62, 0x700);
        break;
    case LANGUAGE_SPANISH:
        work->sprites[1].tiles = LoadObjTiles(gUnkEu_09740536, 0x700);
        break;
    case 5:
    case 6:
        break;
    }
#else
    work->sprites[1].tiles = LoadObjTiles(gUnk_09771666, 0x700);
#endif
    work->sprites[1].palette = LoadObjPalette(&gUnk_0984A778[t], 0x20);
    work->sprites[1].x = -0x7800;
    work->sprites[1].targetX = 0x7C00;
    work->sprites[1].y = 0xA0;

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        AnimInit(&work->anim, gUnkEu_09F81A1C, gUnkEu_09F81A08);
        break;
    case LANGUAGE_FRENCH:
        AnimInit(&work->anim, gUnkEu_09F81A34, gUnkEu_09F81A20);
        break;
    case LANGUAGE_GERMAN:
        AnimInit(&work->anim, gUnkEu_09F81A7C, gUnkEu_09F81A68);
        break;
    case LANGUAGE_ITALIAN:
        AnimInit(&work->anim, gUnkEu_09F81A64, gUnkEu_09F81A50);
        break;
    case LANGUAGE_SPANISH:
        AnimInit(&work->anim, gUnkEu_09F81A4C, gUnkEu_09F81A38);
        break;
    case 5:
    case 6:
        break;
    }
#else
    AnimInit(&work->anim, gUnk_09EF6604, gUnk_09EF65F0);
#endif
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->sprites[1].gfx = AnimGetGfx(&work->anim);
#ifdef VERSION_EU
    work->sprites[2].tiles = LoadObjTiles(gUnkEu_0973EEFE, 0x100);
#else
    work->sprites[2].tiles = LoadObjTiles(gUnk_0977143A, 0x100);
#endif
    work->sprites[2].palette = LoadObjPalette(&gUnk_0984A778[t], 0x20);
#ifdef VERSION_EU
    work->sprites[2].gfx = gUnk_09EF65E0[0];
#else
    work->sprites[2].gfx = gUnk_09EF65E8[0];
#endif
    work->sprites[2].x = 0x15800;
    work->sprites[2].targetX = 0xB800;
    work->sprites[2].y = 0x91;
    work->slideTimer = 30;
    gTitleObjSlideDone = 0;
    work->slideDelay = 0;
}

u8 task_title_obj_1(TitleObjWork* work) {
    if (IsTitleIntroDone()) {
        if (work->slideDelay != 0) {
            work->slideDelay--;
        } else if (work->slideTimer != 0) {
            ApproachValue(&work->sprites[1].x, work->sprites[1].targetX, work->slideTimer);
            ApproachValue(&work->sprites[2].x, work->sprites[2].targetX, work->slideTimer);
            work->slideTimer--;

            if (work->slideTimer == 0) {
                gTitleObjSlideDone = 1;
            }
        }
    }

    return 1;
}

#ifdef VERSION_JP
#define TITLE_OBJ_DRAW_COUNT 3
#else
#define TITLE_OBJ_DRAW_COUNT 2
#endif

void task_title_obj_2(TitleObjWork* work) {
    s32 i;

    work->sprites[1].gfx = AnimUpdate(&work->anim);

    for (i = 0; i < TITLE_OBJ_DRAW_COUNT; i++) {
        DrawSprite(work->sprites[i].x >> 8, work->sprites[i].y, work->sprites[i].gfx,
                   work->sprites[i].tiles, work->sprites[i].palette, 0, 0, i);
    }
}

void task_title_obj_3(TitleObjWork* work) {
    s32 i;

    for (i = 0; i < 3; i++) {
        ReleaseObjTiles(work->sprites[i].tiles);
        ReleaseObjPalette(work->sprites[i].palette);
    }
}

u8 IsTitleObjSlideDone() {
    return gTitleObjSlideDone;
}

void task_title_menu_0(TitleMenuWork* work, s16* arg) {
    s32 t;
    u8* pal;
    u8* pal2;

    t = (gGameState.flags & GAME_FLAG_RIKU_TITLE) ? 0x20 : 0;
    work->choice = arg;

    if (arg[0] == 0) {
        if (gGameState.flags & GAME_FLAG_SORA_CLEAR) {
            work->layout = 4;
            arg[0] = 4;
        } else {
            work->layout = 1;
        }
    } else if (arg[0] == 3) {
        work->layout = 2;
    } else if (gGameState.flags & GAME_FLAG_SORA_CLEAR) {
        work->layout = 3;
    } else {
        work->layout = 0;
    }

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        work->tiles = LoadObjTiles(gUnkEu_09748BA6, 0x1600);
        break;
    case LANGUAGE_FRENCH:
        work->tiles = LoadObjTiles(gUnkEu_0974A284, 0xFA0);
        break;
    case LANGUAGE_GERMAN:
        work->tiles = LoadObjTiles(gUnkEu_0974D47A, 0xEE0);
        break;
    case LANGUAGE_ITALIAN:
        work->tiles = LoadObjTiles(gUnkEu_0974C504, 0xEA0);
        break;
    case LANGUAGE_SPANISH:
        work->tiles = LoadObjTiles(gUnkEu_0974B306, 0x1120);
        break;
    case 5:
    case 6:
        break;
    }
#else
#ifdef VERSION_JP
    work->tiles = LoadObjTiles(gUnk_09773E1A, 0x2C00);
#else
    work->tiles = LoadObjTiles(gUnk_09773E1A, 0x1600);
#endif
#endif
    work->palette = LoadObjPalette(gUnk_0984A7F8, 0x20);
    TitleCopyToPaletteBuffer(work->palette->index + 16, gUnk_0984A7F8, 0x20);
#ifdef VERSION_EU
    work->tiles2[0] = LoadObjTiles(gUnkEu_0973F058, 0x280);

    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        work->tiles2[1] = LoadObjTiles(gUnkEu_09741E9A, 0xB20);
        break;
    case LANGUAGE_FRENCH:
        work->tiles2[1] = LoadObjTiles(gUnkEu_09742A74, 0xCE0);
        break;
    case LANGUAGE_GERMAN:
        work->tiles2[1] = LoadObjTiles(gUnkEu_0974507E, 0xA60);
        break;
    case LANGUAGE_ITALIAN:
        work->tiles2[1] = LoadObjTiles(gUnkEu_097445AC, 0xA20);
        break;
    case LANGUAGE_SPANISH:
        work->tiles2[1] = LoadObjTiles(gUnkEu_09743812, 0xCE0);
        break;
    case 5:
    case 6:
        break;
    }

    work->tiles2[2] = LoadObjTiles(gUnkEu_09745B92, 0x700);
#else
    work->tiles2[0] = LoadObjTiles(gUnk_09771DC0, 0x280);
    work->tiles2[1] = LoadObjTiles(gUnk_097720F2, 0xB20);
#ifdef VERSION_JP
    work->tiles2[2] = LoadObjTiles(gUnk_09772CC6, 0xE00);
#else
    work->tiles2[2] = LoadObjTiles(gUnk_09772CC6, 0x700);
#endif
#endif
    pal = &gUnk_0984A778[t];
    work->palette2[0] = LoadObjPalette(pal, 0x20);
    work->palette2[1] = LoadObjPalette(pal, 0x20);
    pal2 = &gUnk_0984A7B8[t];
    work->palette2[2] = LoadObjPalette(pal2, 0x20);
    TitleCopyToPaletteBuffer(work->palette2[0]->index + 16, pal, 0x20);
    TitleCopyToPaletteBuffer(work->palette2[2]->index + 16, pal2, 0x20);
#ifdef VERSION_EU
    AnimInit(&work->anim, gUnkEu_09F81A04, gUnk_09EF65E8);
#else
    AnimInit(&work->anim, gUnk_09EF661C, gUnk_09EF6608);
#endif
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx[0] = AnimGetGfx(&work->anim);

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        work->gfx[1] = gUnkEu_09F81A80[work->choice[0]];
        break;
    case LANGUAGE_FRENCH:
        work->gfx[1] = gUnkEu_09F81A9C[work->choice[0]];
        break;
    case LANGUAGE_GERMAN:
        work->gfx[1] = gUnkEu_09F81AF0[work->choice[0]];
        break;
    case LANGUAGE_ITALIAN:
        work->gfx[1] = gUnkEu_09F81AD4[work->choice[0]];
        break;
    case LANGUAGE_SPANISH:
        work->gfx[1] = gUnkEu_09F81AB8[work->choice[0]];
        break;
    case 5:
    case 6:
        break;
    }

    work->gfx[2] = gUnkEu_09F81B0C[work->choice[0]];
#else
    work->gfx[1] = gUnk_09EF6620[work->choice[0]];
    work->gfx[2] = gUnk_09EF663C[work->choice[0]];
#endif
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescTitleLumichange, 0);
}

s16 TitleMenuChoiceRow(s16 a) {
    s16 i;

    for (i = 0; i <= 3; i++) {
        if (a == sTitleMenuChoiceOrder[i]) {
            break;
        }
    }

    if (i > 3) {
        i = 0;
    }

    return i;
}

void TitleMenuMoveBasic(s16* p) {
    s16 max;
    u16 keys;

    max = (gGameState.flags & GAME_FLAG_SORA_CLEAR) ? 2 : 1;
    keys = GetKeysPressed() & DPAD_UP;

    if (keys != 0) {
        m4aSongNumStart(SONG_SYS_CLICK);
        (*p)--;

        if (*p < 0) {
            *p = max;
        }
    } else if (GetKeysPressed() & DPAD_DOWN) {
        m4aSongNumStart(SONG_SYS_CLICK);
        *p = *p + 1;

        if (*p > max) {
            *p = 0;
        }
    }
}

void TitleMenuMoveOrdered(s16* p, s16 count) {
    s16 i;

    if (GetKeysPressed() & DPAD_UP) {
        m4aSongNumStart(SONG_SYS_CLICK);
        i = TitleMenuChoiceRow(*p);
        i--;

        if (i < 0) {
            i = count;
        }
    } else if (GetKeysPressed() & DPAD_DOWN) {
        m4aSongNumStart(SONG_SYS_CLICK);
        i = TitleMenuChoiceRow(*p);
        i++;

        if (i > count) {
            i = 0;
        }
    } else {
        return;
    }

    *p = sTitleMenuChoiceOrder[i];
}

u8 task_title_menu_1(TitleMenuWork* work) {
    if (work->layout == 0) {
        TitleMenuMoveBasic(work->choice);
    } else if (work->layout == 3) {
        TitleMenuMoveOrdered(work->choice, 3);
    } else if (work->layout == 4) {
        TitleMenuMoveOrdered(work->choice, 1);
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void TitleMenuDrawBasic(TitleMenuWork* work) {
    s32 i;
    s32 t;
    s16 y;
    s16 count;

    y = 32;
    t = gGameState.flags & GAME_FLAG_SORA_CLEAR;
    count = 3;

    if (t == 0) {
        count = 2;
        y = 48;
    }

    for (i = 0; i < count; i++) {
#ifdef VERSION_EU
        void** spr = sTitleMenuEntrySpritesEu[gLanguage];

        DrawSprite(work->x, y, spr[i], work->tiles, work->palette, 0, SPRITE_PRIORITY(1), i + 100);
#else
        DrawSprite(work->x, y, gUnk_09EF6668[i], work->tiles, work->palette, 0, SPRITE_PRIORITY(1), i + 100);
#endif
        y += 24;
    }

    if (gGameState.flags & GAME_FLAG_SORA_CLEAR) {
        y = work->choice[0] * 24 + 32;
    } else {
        y = work->choice[0] * 24 + 48;
    }

    for (i = 0; i < 3; i++) {
        DrawSprite(work->x, y, work->gfx[i], work->tiles2[i], work->palette2[i], 0, 0, i);
    }
}

void TitleMenuDrawFull(TitleMenuWork* work) {
    s32 i;
    s16 y;

    y = 16;

    for (i = 0; i < 4; i++) {
#ifdef VERSION_EU
        void** spr = sTitleMenuEntrySpritesEu[gLanguage];

        DrawSprite(work->x, y, spr[sTitleMenuChoiceOrder[i]], work->tiles, work->palette, 0, SPRITE_PRIORITY(1), i + 100);
#else
        DrawSprite(work->x, y, gUnk_09EF6668[sTitleMenuChoiceOrder[i]], work->tiles, work->palette, 0, SPRITE_PRIORITY(1), i + 100);
#endif
        y += 24;
    }

    y = TitleMenuChoiceRow(work->choice[0]) * 24 + 16;

    for (i = 0; i < 3; i++) {
        DrawSprite(work->x, y, work->gfx[i], work->tiles2[i], work->palette2[i], 0, 0, i);
    }
}

void TitleMenuDrawNewGame(TitleMenuWork* work) {
    s32 i;
    s16 y;

    y = 48;

    for (i = 0; i < 2; i++) {
#ifdef VERSION_EU
        void** spr = sTitleMenuEntrySpritesEu[gLanguage];

        DrawSprite(work->x, y, spr[sTitleMenuChoiceOrder[i]], work->tiles, work->palette, 0, SPRITE_PRIORITY(1), i + 100);
#else
        DrawSprite(work->x, y, gUnk_09EF6668[sTitleMenuChoiceOrder[i]], work->tiles, work->palette, 0, SPRITE_PRIORITY(1), i + 100);
#endif
        y += 24;
    }

    y = TitleMenuChoiceRow(work->choice[0]) * 24 + 48;

    for (i = 0; i < 3; i++) {
        DrawSprite(work->x, y, work->gfx[i], work->tiles2[i], work->palette2[i], 0, 0, i);
    }
}

void TitleMenuDrawSingle(TitleMenuWork* work) {
    s32 i;
    s16 y;

    y = 56;

#ifdef VERSION_EU
    {
        void** spr = sTitleMenuEntrySpritesEu[gLanguage];

        DrawSprite(work->x, y, spr[work->choice[0]], work->tiles, work->palette, 0, SPRITE_PRIORITY(1), 100);
    }
#else
    DrawSprite(work->x, y, gUnk_09EF6668[work->choice[0]], work->tiles, work->palette, 0, SPRITE_PRIORITY(1), 100);
#endif

    for (i = 0; i < 3; i++) {
        DrawSprite(work->x, y, work->gfx[i], work->tiles2[i], work->palette2[i], 0, 0, i);
    }
}

void task_title_menu_2(TitleMenuWork* work) {
    work->gfx[0] = AnimUpdate(&work->anim);

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        work->gfx[1] = gUnkEu_09F81A80[work->choice[0]];
        break;
    case LANGUAGE_FRENCH:
        work->gfx[1] = gUnkEu_09F81A9C[work->choice[0]];
        break;
    case LANGUAGE_GERMAN:
        work->gfx[1] = gUnkEu_09F81AF0[work->choice[0]];
        break;
    case LANGUAGE_ITALIAN:
        work->gfx[1] = gUnkEu_09F81AD4[work->choice[0]];
        break;
    case LANGUAGE_SPANISH:
        work->gfx[1] = gUnkEu_09F81AB8[work->choice[0]];
        break;
    case 5:
    case 6:
        break;
    }

    work->gfx[2] = gUnkEu_09F81B0C[work->choice[0]];
#else
    work->gfx[1] = gUnk_09EF6620[work->choice[0]];
    work->gfx[2] = gUnk_09EF663C[work->choice[0]];
#endif

    if (gGameState.flags & GAME_FLAG_RIKU_TITLE) {
        work->x = 120;
    } else {
        work->x = 0;
    }

    if (work->layout == 0) {
        TitleMenuDrawBasic(work);
    } else if (work->layout == 3) {
        TitleMenuDrawFull(work);
    } else if (work->layout == 4) {
        TitleMenuDrawNewGame(work);
    } else {
        TitleMenuDrawSingle(work);
    }

    TaskPoolDraw(&work->tasks);
}

void task_title_menu_3(TitleMenuWork* work) {
    s32 i;

    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);

    for (i = 0; i < 3; i++) {
        ReleaseObjTiles(work->tiles2[i]);
        ReleaseObjPalette(work->palette2[i]);
    }

    TaskPoolDestroy(&work->tasks);
}

void task_title_lumichange_0(TitleLumiChangeWork* work) {
    if (gGameState.flags & GAME_FLAG_RIKU_TITLE) {
#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            work->tiles = LoadObjTiles(gUnkEu_0974E3CC, 0x840);
            break;
        case LANGUAGE_FRENCH:
            work->tiles = LoadObjTiles(gUnkEu_0974EC7C, 0x740);
            break;
        case LANGUAGE_GERMAN:
            work->tiles = LoadObjTiles(gUnkEu_0975038C, 0x740);
            break;
        case LANGUAGE_ITALIAN:
            work->tiles = LoadObjTiles(gUnkEu_0974FBDC, 0x740);
            break;
        case LANGUAGE_SPANISH:
            work->tiles = LoadObjTiles(gUnkEu_0974F42C, 0x740);
            break;
        case 5:
        case 6:
            break;
        }
#else
        work->tiles = LoadObjTiles(gUnk_0977548C, 0x840);
#endif
        work->palette = LoadObjPalette(gUnk_0984A7D8, 0x20);
    } else {
#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            work->tiles = LoadObjTiles(gUnkEu_097462F2, 0x940);
            break;
        case LANGUAGE_FRENCH:
            work->tiles = LoadObjTiles(gUnkEu_09746CA4, 0x740);
            break;
        case LANGUAGE_GERMAN:
            work->tiles = LoadObjTiles(gUnkEu_097483B4, 0x740);
            break;
        case LANGUAGE_ITALIAN:
            work->tiles = LoadObjTiles(gUnkEu_09747C04, 0x740);
            break;
        case LANGUAGE_SPANISH:
            work->tiles = LoadObjTiles(gUnkEu_09747454, 0x740);
            break;
        case 5:
        case 6:
            break;
        }
#else
        work->tiles = LoadObjTiles(gUnk_09773426, 0x940);
#endif
        work->palette = LoadObjPalette(gUnk_0984A7B8, 0x20);
    }
}

u8 task_title_lumichange_1(TitleLumiChangeWork* work) {
    s16 tbl[3];
    s16 v;
    u32 i;
    s32 j;

    v = GetPaletteEffect();
    memcpy(tbl, sTitleLumiLevels, sizeof(tbl));

    switch (GetKeysPressed() & (L_BUTTON | R_BUTTON)) {
    case R_BUTTON:
        for (i = 0; i < 3; i++) {
            if (v < tbl[i]) {
                v = tbl[i];
                m4aSongNumStart(SONG_SYS_CANSEL);
                break;
            }
        }

        break;
    case L_BUTTON:
        for (j = 2; j > -1; j--) {
            if (v > tbl[j]) {
                v = tbl[j];
                m4aSongNumStart(SONG_SYS_CANSEL);
                break;
            }
        }

        break;
    }

    if (GetKeysPressed() & (L_BUTTON | R_BUTTON)) {
        SetPaletteEffect(v);
        TitleLoadPaletteBuffer();
    }

    return 1;
}

void task_title_lumichange_2(TitleLumiChangeWork* work) {
    s16 v;
    void** tbl;
    s16 x;

    v = GetPaletteEffect();

#ifdef VERSION_EU
    {
        void** a = gTitleLumiSpritesEu[gLanguage];
        void** b = gTitleLumiSpritesAltEu[gLanguage];

        tbl = (gGameState.flags & GAME_FLAG_RIKU_TITLE) ? b : a;
    }
#else
    tbl = (gGameState.flags & GAME_FLAG_RIKU_TITLE) ? gUnk_09EF6684 : gUnk_09EF6658;
#endif

    if (v < 0) {
        work->gfx = tbl[0];
    } else if (v == 0) {
        work->gfx = tbl[1];
    } else if (v > 0) {
        work->gfx = tbl[2];
    }

    x = (gGameState.flags & GAME_FLAG_RIKU_TITLE) ? 240 : 0;
    DrawSprite(x, 0x8F, work->gfx, work->tiles, work->palette, 0, SPRITE_PRIORITY(1), 100);
}

void task_title_lumichange_3(TitleLumiChangeWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

#ifdef VERSION_EU
void** gTitleLumiSpritesEu[5] = {
    gUnkEu_09F81B28,
    gUnkEu_09F81B38,
    gUnkEu_09F81B68,
    gUnkEu_09F81B58,
    gUnkEu_09F81B48,
};

void** gTitleLumiSpritesAltEu[5] = {
    gUnkEu_09F81C04,
    gUnkEu_09F81C14,
    gUnkEu_09F81C44,
    gUnkEu_09F81C34,
    gUnkEu_09F81C24,
};
#endif

TaskDesc gTaskDescTitleLumichange = {
    "task_title_lumichange",
    (TaskInitFunc)task_title_lumichange_0,
    (TaskUpdateFunc)task_title_lumichange_1,
    (TaskDrawFunc)task_title_lumichange_2,
    (TaskDestroyFunc)task_title_lumichange_3,
    sizeof(TitleLumiChangeWork),
};
