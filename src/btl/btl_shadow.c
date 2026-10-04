/**
 * btl_shadow.c
 * Battle Actor Shadow
 */

#include "btl2.h"
#include "sprites_btl.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "sprite_palettes.h"

void task_btl_shadow_0(BtlShadowWork* work, BtlObj* actor) {
    work->actor = actor;

    if (actor->flags & BTLOBJ_FLAG_SMALL_SHADOW) {
        work->tiles = LoadObjTiles(gUnk_08B22CE4, 0x200);
        work->gfx = gUnk_08B22CBC;
    } else if (actor->flags & BTLOBJ_FLAG_LARGE_SHADOW) {
        work->tiles = LoadObjTiles(gUnk_08B22EFE, 0x140);
        work->gfx = gUnk_08B22EE4;
    } else {
        work->tiles = LoadObjTiles(gUnk_08B22BBC, 0x100);
        work->gfx = gUnk_08B22BA8;
    }

    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
}

s32 task_btl_shadow_1() {
    return 1;
}

void task_btl_shadow_2(BtlShadowWork* work) {
    BtlObj* actor = work->actor;
    s16 x;
    s16 y;
    u16 anim;
    ObjAffine* aff;

    if (actor->shadowPriority != 0) {
        if (!(actor->flags & 0x0000000402000000)) {
            anim = GetBattleSpritePriorityFlags(actor->y);

            if (actor->z >= 0 && gBtlWork->scale == 0x100) {
                aff = NULL;
            } else {
                s32 sc = 0x100 - (actor->groundZ - actor->z) / 128;
                sc = (gBtlWork->scale * sc) >> 8;

                if (sc <= 127) {
                    sc = 128;
                }

                aff = AllocObjAffine(0, sc, sc, sc > 0x100);
            }

            WorldToScreen(&x, &y, actor->x, actor->y, actor->groundZ);
            DrawSprite(x, y, work->gfx, work->tiles, work->palette, aff, anim, actor->shadowPriority);
        }
    }
}

void task_btl_shadow_3(BtlShadowWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

TaskDesc gTaskDescBtlShadow = {
    "task_btl_shadow",
    (TaskInitFunc)task_btl_shadow_0,
    (TaskUpdateFunc)task_btl_shadow_1,
    (TaskDrawFunc)task_btl_shadow_2,
    (TaskDestroyFunc)task_btl_shadow_3,
    sizeof(BtlShadowWork),
};
