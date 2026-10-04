/**
 * btl_pop_cb.c
 * Riku Card Break Popup
 */

#include "system_state.h"
#include "btl4.h"
#include "sprites_btl.h"
#include "sprites_btl_hud.h"
#include "battle_actor.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "sprite_palettes.h"

void task_btl_pop_cb_0(BtlPopCbWork* work, BtlPopSrc* src) {
#ifdef VERSION_EU
    work->palette = LoadObjPalette(gBStatesPalette, 32);

    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
    case LANGUAGE_FRENCH:
        work->tiles = AllocObjTiles(0x200, gUnkEu_08B4AC46);

        switch (src->number) {
        case 0:
            work->gfx = gUnkEu_08B4AB9C;
            break;
        case 1:
            work->gfx = gUnkEu_08B4ABAC;
            break;
        case 2:
            work->gfx = gUnkEu_08B4ABBC;
            break;
        case 3:
            work->gfx = gUnkEu_08B4ABCC;
            break;
        case 4:
            work->gfx = gUnkEu_08B4ABDC;
            break;
        case 5:
            work->gfx = gUnkEu_08B4ABEC;
            break;
        case 6:
            work->gfx = gUnkEu_08B4ABFC;
            break;
        case 7:
            work->gfx = gUnkEu_08B4AC0C;
            break;
        case 8:
            work->gfx = gUnkEu_08B4AC1C;
            break;
        case 9:
        default:
            work->gfx = gUnkEu_08B4AC2C;
            break;
        }

        break;
    case LANGUAGE_SPANISH:
        work->tiles = AllocObjTiles(0x200, gUnkEu_08B52782);

        switch (src->number) {
        case 0:
            work->gfx = gUnkEu_08B526D8;
            break;
        case 1:
            work->gfx = gUnkEu_08B526E8;
            break;
        case 2:
            work->gfx = gUnkEu_08B526F8;
            break;
        case 3:
            work->gfx = gUnkEu_08B52708;
            break;
        case 4:
            work->gfx = gUnkEu_08B52718;
            break;
        case 5:
            work->gfx = gUnkEu_08B52728;
            break;
        case 6:
            work->gfx = gUnkEu_08B52738;
            break;
        case 7:
            work->gfx = gUnkEu_08B52748;
            break;
        case 8:
            work->gfx = gUnkEu_08B52758;
            break;
        case 9:
        default:
            work->gfx = gUnkEu_08B52768;
            break;
        }

        break;
    case LANGUAGE_ITALIAN:
        work->tiles = AllocObjTiles(0x200, gUnkEu_08B533BE);

        switch (src->number) {
        case 0:
            work->gfx = gUnkEu_08B53314;
            break;
        case 1:
            work->gfx = gUnkEu_08B53324;
            break;
        case 2:
            work->gfx = gUnkEu_08B53334;
            break;
        case 3:
            work->gfx = gUnkEu_08B53344;
            break;
        case 4:
            work->gfx = gUnkEu_08B53354;
            break;
        case 5:
            work->gfx = gUnkEu_08B53364;
            break;
        case 6:
            work->gfx = gUnkEu_08B53374;
            break;
        case 7:
            work->gfx = gUnkEu_08B53384;
            break;
        case 8:
            work->gfx = gUnkEu_08B53394;
            break;
        case 9:
        default:
            work->gfx = gUnkEu_08B533A4;
            break;
        }

        break;
    case LANGUAGE_GERMAN:
    default:
        work->tiles = AllocObjTiles(0x200, gUnkEu_08B53FFA);

        switch (src->number) {
        case 0:
            work->gfx = gUnkEu_08B53F50;
            break;
        case 1:
            work->gfx = gUnkEu_08B53F60;
            break;
        case 2:
            work->gfx = gUnkEu_08B53F70;
            break;
        case 3:
            work->gfx = gUnkEu_08B53F80;
            break;
        case 4:
            work->gfx = gUnkEu_08B53F90;
            break;
        case 5:
            work->gfx = gUnkEu_08B53FA0;
            break;
        case 6:
            work->gfx = gUnkEu_08B53FB0;
            break;
        case 7:
            work->gfx = gUnkEu_08B53FC0;
            break;
        case 8:
            work->gfx = gUnkEu_08B53FD0;
            break;
        case 9:
        default:
            work->gfx = gUnkEu_08B53FE0;
            break;
        }

        break;
    }
#else
    work->tiles = AllocObjTiles(0x200, gUnk_08B1FD66);
    work->palette = LoadObjPalette(gBStatesPalette, 32);

    switch (src->number) {
    case 0:
        work->gfx = gUnk_08B1FCBC;
        break;
    case 1:
        work->gfx = gUnk_08B1FCCC;
        break;
    case 2:
        work->gfx = gUnk_08B1FCDC;
        break;
    case 3:
        work->gfx = gUnk_08B1FCEC;
        break;
    case 4:
        work->gfx = gUnk_08B1FCFC;
        break;
    case 5:
        work->gfx = gUnk_08B1FD0C;
        break;
    case 6:
        work->gfx = gUnk_08B1FD1C;
        break;
    case 7:
        work->gfx = gUnk_08B1FD2C;
        break;
    case 8:
        work->gfx = gUnk_08B1FD3C;
        break;
    case 9:
    default:
        work->gfx = gUnk_08B1FD4C;
        break;
    }
#endif

    work->x = src->x;
    work->y = src->y;
    work->z = src->z;
    work->timer = 0;
}

s32 task_btl_pop_cb_1(BtlPopCbWork* work) {
    work->z -= 192;

    if (work->timer > 49) {
        return 0;
    }

    work->timer++;
    return 1;
}

void task_btl_pop_cb_2(BtlPopCbWork* work) {
    s16 x;
    s16 y;

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_FLAG_NO_MOSAIC, 5);
}

void task_btl_pop_cb_3(BtlPopCbWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

TaskDesc gTaskDescBtlPopCb = {
    "task_btl_pop_cb",
    (TaskInitFunc)task_btl_pop_cb_0,
    (TaskUpdateFunc)task_btl_pop_cb_1,
    (TaskDrawFunc)task_btl_pop_cb_2,
    (TaskDestroyFunc)task_btl_pop_cb_3,
    sizeof(BtlPopCbWork),
};
