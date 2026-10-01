#include "system_state.h"
#include "btl2.h"
#include "sprites_btl.h"
#include "sprites_btl_hud.h"
#include "anim.h"
#include "battle_actor.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

void task_btl_pop_0(BtlPopWork* work, BtlPremireSrc* src) {
#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        switch (src->kind) {
        case 0:
            work->tiles = LoadObjTiles(gUnkEu_08B4A794, 0x100);
            AnimInit(&work->anim, gUnk_09EE11C0, gUnk_09EE11BC);
            break;
        case 2:
            work->tiles = LoadObjTiles(gUnkEu_08B4A680, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5BE10, gUnkEu_09F5BE0C);
            break;
        case 9:
            work->tiles = LoadObjTiles(gUnkEu_08B4A8AE, 0x180);
            AnimInit(&work->anim, gUnk_09EE11C8, gUnk_09EE11C4);
            break;
        case 10:
            work->tiles = LoadObjTiles(gUnk_08B1F13A, 0x140);
            AnimInit(&work->anim, gUnk_09EE11D0, gUnk_09EE11CC);
            break;
        default:
            work->tiles = LoadObjTiles(gUnkEu_08B4A680, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5BE10, gUnkEu_09F5BE0C);
            break;
        }

        break;
    case LANGUAGE_FRENCH:
        switch (src->kind) {
        case 0:
            work->tiles = LoadObjTiles(gUnkEu_08B51368, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1C0, gUnkEu_09F5C1BC);
            break;
        case 2:
            work->tiles = LoadObjTiles(gUnkEu_08B517B8, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1E0, gUnkEu_09F5C1DC);
            break;
        case 9:
            work->tiles = LoadObjTiles(gUnkEu_08B4A8AE, 0x180);
            AnimInit(&work->anim, gUnk_09EE11C8, gUnk_09EE11C4);
            break;
        case 10:
            work->tiles = LoadObjTiles(gUnkEu_08B50F18, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1A0, gUnkEu_09F5C19C);
            break;
        default:
            work->tiles = LoadObjTiles(gUnkEu_08B517B8, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1E0, gUnkEu_09F5C1DC);
            break;
        }

        break;
    case LANGUAGE_GERMAN:
        switch (src->kind) {
        case 0:
            work->tiles = LoadObjTiles(gUnkEu_08B516A4, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1D8, gUnkEu_09F5C1D4);
            break;
        case 2:
            work->tiles = LoadObjTiles(gUnkEu_08B51A74, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1F8, gUnkEu_09F5C1F4);
            break;
        case 9:
            work->tiles = LoadObjTiles(gUnkEu_08B50D82, 0x180);
            AnimInit(&work->anim, gUnkEu_09F5C198, gUnkEu_09F5C194);
            break;
        case 10:
            work->tiles = LoadObjTiles(gUnkEu_08B51254, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1B8, gUnkEu_09F5C1B4);
            break;
        default:
            work->tiles = LoadObjTiles(gUnkEu_08B51A74, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1F8, gUnkEu_09F5C1F4);
            break;
        }

        break;
    case LANGUAGE_ITALIAN:
        switch (src->kind) {
        case 0:
            work->tiles = LoadObjTiles(gUnkEu_08B51590, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1D0, gUnkEu_09F5C1CC);
            break;
        case 2:
            work->tiles = LoadObjTiles(gUnkEu_08B519E0, 0x80);
            AnimInit(&work->anim, gUnkEu_09F5C1F0, gUnkEu_09F5C1EC);
            break;
        case 9:
            work->tiles = LoadObjTiles(gUnkEu_08B50BE6, 0x180);
            AnimInit(&work->anim, gUnkEu_09F5C190, gUnkEu_09F5C18C);
            break;
        case 10:
            work->tiles = LoadObjTiles(gUnkEu_08B51140, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1B0, gUnkEu_09F5C1AC);
            break;
        default:
            work->tiles = LoadObjTiles(gUnkEu_08B519E0, 0x80);
            AnimInit(&work->anim, gUnkEu_09F5C1F0, gUnkEu_09F5C1EC);
            break;
        }

        break;
    case LANGUAGE_SPANISH:
    default:
        switch (src->kind) {
        case 0:
            work->tiles = LoadObjTiles(gUnkEu_08B5147C, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1C8, gUnkEu_09F5C1C4);
            break;
        case 2:
            work->tiles = LoadObjTiles(gUnkEu_08B518CC, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1E8, gUnkEu_09F5C1E4);
            break;
        case 9:
            work->tiles = LoadObjTiles(gUnkEu_08B50A4A, 0x180);
            AnimInit(&work->anim, gUnkEu_09F5C188, gUnkEu_09F5C184);
            break;
        case 10:
            work->tiles = LoadObjTiles(gUnkEu_08B5102C, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1A8, gUnkEu_09F5C1A4);
            break;
        default:
            work->tiles = LoadObjTiles(gUnkEu_08B518CC, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1E8, gUnkEu_09F5C1E4);
            break;
        }

        break;
    }

    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
#else
    switch (src->kind) {
    case 0:
        work->tiles = LoadObjTiles(gUnk_08B1F020, 0x100);
        AnimInit(&work->anim, gUnk_09EE11D0, gUnk_09EE11CC);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    case 1:
        work->tiles = LoadObjTiles(gUnk_08B1ED76, 0x180);
        AnimInit(&work->anim, gUnk_09EE11C0, gUnk_09EE11BC);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    case 2:
        work->tiles = LoadObjTiles(gUnk_08B1EF0C, 0x100);
        AnimInit(&work->anim, gUnk_09EE11C8, gUnk_09EE11C4);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    case 3:
        work->tiles = LoadObjTiles(gUnk_08B1F13A, 0x180);
        AnimInit(&work->anim, gUnk_09EE11D8, gUnk_09EE11D4);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    case 5:
        work->tiles = LoadObjTiles(gUnk_08B1F7AC, 0x500);
        AnimInit(&work->anim, gUnk_09EE1204, gUnk_09EE11F4);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    case 6:
        work->tiles = LoadObjTiles(gUnk_08B1F7AC, 0x500);
        AnimInit(&work->anim, gUnk_09EE1204, gUnk_09EE11F4);
        AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);
        break;
    case 7:
        work->tiles = LoadObjTiles(gUnk_08B1F7AC, 0x500);
        AnimInit(&work->anim, gUnk_09EE1204, gUnk_09EE11F4);
        AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
        break;
    case 8:
        work->tiles = LoadObjTiles(gUnk_08B1F7AC, 0x500);
        AnimInit(&work->anim, gUnk_09EE1204, gUnk_09EE11F4);
        AnimStart(&work->anim, 3, ANIM_FLAG_LOOP);
        break;
    case 9:
        work->tiles = LoadObjTiles(gUnk_08B1F472, 0x180);
        AnimInit(&work->anim, gUnk_09EE11E8, gUnk_09EE11E4);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    case 10:
        work->tiles = LoadObjTiles(gUnk_08B1F60E, 0x140);
        AnimInit(&work->anim, gUnk_09EE11F0, gUnk_09EE11EC);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    case 4:
    default:
        work->tiles = LoadObjTiles(gUnk_08B1F2D6, 0x180);
        AnimInit(&work->anim, gUnk_09EE11E0, gUnk_09EE11DC);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    }
#endif

    work->gfx = AnimGetGfx(&work->anim);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    work->x = src->x;
    work->y = src->y;
    work->z = src->z;
    work->timer = 0;
}

s32 task_btl_pop_1(BtlPopWork* work) {
    work->z -= 0xC0;

    if (work->timer > 49) {
        return 0;
    }

    work->timer++;
    work->gfx = AnimUpdate(&work->anim);
    return 1;
}

void task_btl_pop_2(BtlPopWork* work) {
    s16 x;
    s16 y;

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_FLAG_NO_MOSAIC, 5);
}

void task_btl_pop_3(BtlPopWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

TaskDesc gTaskDescBtlPop = {
    "task_btl_pop",
    (TaskInitFunc)task_btl_pop_0,
    (TaskUpdateFunc)task_btl_pop_1,
    (TaskDrawFunc)task_btl_pop_2,
    (TaskDestroyFunc)task_btl_pop_3,
    sizeof(BtlPopWork),
};
