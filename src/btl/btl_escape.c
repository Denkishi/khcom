#include "system_state.h"
#include "btl2.h"
#include "sprites_btl.h"
#include "sprites_btl_hud.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "game_state.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

void task_btl_escape_0(BtlEscapeWork* work) {
    void** p;

    work->progressMax = 0x5A00;
#ifdef VERSION_EU
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);

    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        work->tiles = LoadObjTiles(gUnk_08B1EB1C, 0x240);
        p = gUnk_09EE11A4;
        break;
    case LANGUAGE_FRENCH:
        work->tiles = LoadObjTiles(gUnkEu_08B51D50, 0x240);
        p = gUnkEu_09F5C20C;
        break;
    case LANGUAGE_SPANISH:
        work->tiles = LoadObjTiles(gUnkEu_08B51FB8, 0x240);
        p = gUnkEu_09F5C21C;
        break;
    case LANGUAGE_ITALIAN:
        work->tiles = LoadObjTiles(gUnkEu_08B52220, 0x240);
        p = gUnkEu_09F5C22C;
        break;
    case LANGUAGE_GERMAN:
    default:
        work->tiles = LoadObjTiles(gUnkEu_08B52488, 0x240);
        p = gUnkEu_09F5C23C;
        break;
    }
#else
    work->tiles = LoadObjTiles(gUnk_08B1EB1C, 0x240);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    p = gUnk_09EE11A4;
#endif
    work->gfx = p[0];
    work->gfx2 = p[2];
    work->gfx3 = p[1];
    work->progressRatio = 0;
    work->progress = 0;
    work->visible = 0;
    work->timer = 0;
}

s32 task_btl_escape_1(BtlEscapeWork* work) {
    if (gBtlWork->flags & BTL_FLAG_STOP_SPAWNING) {
        return 0;
    }

    if (!(gBtlWork->flags & BTL_FLAG_PUSHING_EDGE)) {
        if (work->visible) {
            work->progress = 0;
            work->visible = 0;
            work->timer = 0;
        }
    } else {
        if (work->timer <= 15) {
            work->timer++;
            work->visible = 0;
        } else {
            work->visible = 1;
            work->progressRatio = (work->progress << 8) / work->progressMax;

            if (work->progress >= work->progressMax) {
                gGameState.flags |= GAME_FLAG_BATTLE_NOT_WON;
                gBtlWork->flags |= BTL_FLAG_ESCAPED;
                gBtlWork->flags |= BTL_FLAG_BATTLE_OVER;
                work->visible = 0;
            } else {
                work->progress += 256;
            }
        }
    }

    return 1;
}

void task_btl_escape_2(BtlEscapeWork* work) {
    BtlObj* actor;
    s16 x;
    s16 y;
    s32 v;
    ObjAffine* aff;

    if (!work->visible) {
        return;
    }

    actor = gBtlWork->actor;

    if (actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
        WorldToScreen(&x, &y, actor->x - 768, actor->y, actor->z - 10240);
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, 0, 2);
    } else {
        WorldToScreen(&x, &y, actor->x - 3072, actor->y, actor->z - 10240);
        DrawSprite(x, y, work->gfx2, work->tiles, work->palette, NULL, 0, 2);
    }

    if (work->progressRatio > 0) {
        v = work->progressRatio * 2;

        if (v > 256) {
            aff = AllocObjAffine(0, v, 256, 1);
        } else {
            aff = AllocObjAffine(0, v, 256, 0);
        }

        DrawSprite(x, y, work->gfx3, work->tiles, work->palette, aff, 0, 1);
    }
}

void task_btl_escape_3(BtlEscapeWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

TaskDesc gTaskDescBtlEscape = {
    "task_btl_escape",
    (TaskInitFunc)task_btl_escape_0,
    (TaskUpdateFunc)task_btl_escape_1,
    (TaskDrawFunc)task_btl_escape_2,
    (TaskDestroyFunc)task_btl_escape_3,
    sizeof(BtlEscapeWork),
};
