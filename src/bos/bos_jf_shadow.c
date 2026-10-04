/**
 * bos_jf_shadow.c
 * Jafar Boss Shadow
 */

#include "macros.h"
#include "bos_jf_shadow.h"
#include "sprites_btl.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "game.h"
#include "obj.h"
#include "obj_api.h"
#include "save_types.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"

u16 gUnk_0203C3BC EWRAM_COMMON(4);
u16 gUnk_0203C3C0 EWRAM_COMMON(4);

void task_bos_jf_shadow_0(JfShadowWork* work, BtlObj* obj) {
    work->actor = obj;
    work->tiles = LoadObjTiles(gUnk_08B22EFE, 0x140);
    work->gfx = gUnk_08B22EE4;
    work->palette = LoadObjPalette(gBStatesPalette, 32);
}

s32 task_bos_jf_shadow_1() {
    return 1;
}

void task_bos_jf_shadow_2(JfShadowWork* work) {
    BtlObj* obj;
    s16 x;
    s16 y;
    s32 size;
    s32 flip;
    u16 frame;
    ObjAffine* sprite;

    obj = work->actor;

    if (obj->shadowPriority == 0) {
        return;
    }

    if (obj->flags & 0x402000000) {
        return;
    }

    frame = GetBattleSpritePriorityFlags(obj->y);

    if (obj->z >= 0 && gBtlWork->scale == 0x100) {
        sprite = NULL;
    } else {
        size = 0x200 - ((obj->groundZ - obj->z) / 128);

        if (size <= 127) {
            size = 128;
        }

        flip = 0;

        if (size > 0x100) {
            flip = 1;
        }

        sprite = AllocObjAffine(0, size, size, flip);
    }

    WorldToScreen(&x, &y, obj->x, obj->y, obj->groundZ);
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, sprite, frame, obj->shadowPriority);
}

void task_bos_jf_shadow_3(JfShadowWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void ResetSaveSliceE6C() {
    gUnk_0203C3C0 = 0;
    gUnk_0203C3BC = 0;
}

void WriteSaveSliceE6C(SaveSliceE6C* out) {
    out->unk_00 = gUnk_0203C3C0;
    out->unk_02 = gUnk_0203C3BC;
}

void ReadSaveSliceE6C(SaveSliceE6C* in) {
    gUnk_0203C3C0 = in->unk_00;
    gUnk_0203C3BC = in->unk_02;
}

TaskDesc gTaskDescBosJfShadow = {
    "task_bos_jf_shadow",
    (TaskInitFunc)task_bos_jf_shadow_0,
    (TaskUpdateFunc)task_bos_jf_shadow_1,
    (TaskDrawFunc)task_bos_jf_shadow_2,
    (TaskDestroyFunc)task_bos_jf_shadow_3,
    sizeof(JfShadowWork),
};
