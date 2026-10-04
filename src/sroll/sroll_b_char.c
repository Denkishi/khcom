/**
 * sroll_b_char.c
 * Staff Roll Credit Characters
 */

#include "sroll.h"
#include "evt.h"
#include "fade.h"
#include "anim.h"
#include "evt_object_types.h"
#include "evt_types.h"
#include "obj.h"
#include "obj_api.h"
#include "registration_data.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"

static s32 Square(s32 x) {
    return x * x;
}

void SrollBCharSetMotion(Task* task, s32 v) {
    ((SrollBCharWork*)task->work)->motion = v;
}

void SrollBCharChangeAnim(SrollBCharWork* work) {
    const EvtObjAnim* def;
    const EvtAnimDef* gfx;

    def = work->obj->animEntry;
    gfx = def->animDef;
    AnimChangeWithTables(&work->anim, def->animId, def->flags, gfx->anims, gfx->gfxTable);
    SetObjTileSource(work->tiles, gfx->tiles);
    work->obj->flags &= ~EVTOBJ_FLAG_ANIM_CHANGED;
}

void task_sroll_b_char_0(SrollBCharWork* work, EvtObjParam* a) {
    const EvtObjRes* res;
    AnimState* anim;

    res = a->res;
    work->motion = 0;
    work->motionTimer = 0;
    work->obj = a->obj;
    work->tiles = AllocObjTiles(res->tileCount * 32, NULL);
    work->palette = LoadObjPalette(res->palette, 32);
    anim = &work->anim;
    AnimInit(anim, NULL, NULL);
    work->obj->anim = anim;
    work->obj->paletteIndex = work->palette->index;
    SrollBCharChangeAnim(work);
    TaskPoolInit(&work->tasks, 4);
}

s32 task_sroll_b_char_1(SrollBCharWork* work) {
    SrollBCrtnArg a;

    if (work->obj->flags & EVTOBJ_FLAG_ANIM_CHANGED) {
        SrollBCharChangeAnim(work);
    }

    if ((work->obj->drawFlags & SPRITE_FLAG_BLEND) == 0) {
        FadeSetPaletteExcluded((work->palette->index & 15) + 16, 0);
    } else {
        FadeSetPaletteExcluded((work->palette->index & 15) + 16, 1);
    }

    AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);

    switch (work->motion) {
    case 1:
        work->obj->x -= 128;
        work->obj->y += 128;
        break;
    case 2:
        work->obj->z = gSrollBCharHopOffsets[(work->motionTimer >> 2) & 15] << 8;
        work->motionTimer++;
        break;
    case 3:
        if ((work->motionTimer & 3) == 0) {
            a.kind = 2;
            a.x = work->obj->x;
            a.y = work->obj->y;
            TaskCreate(&work->tasks, &gTaskDescSrollBCrtn, &a);
        }

        work->obj->z = (gSrollBCharHopOffsets[(work->motionTimer >> 2) & 15] << 8) >> 2;
        work->motionTimer++;
        break;
    case 4:
        work->obj->x += 128;
        work->obj->y -= 128;
        break;
    case 5:
        work->obj->x += (gSrollBCharSwayOffsets[(work->motionTimer >> 2) & 15] << 8) >> 2;
        work->motionTimer++;
        break;
    }

    return 1;
}

void task_sroll_b_char_2(SrollBCharWork* work) {
    EvtObj* obj;
    void* gfx;
    u16 x;
    u16 y;

    obj = work->obj;

    if ((obj->flags & EVTOBJ_FLAG_HIDDEN) == 0) {
        x = obj->x >> 8;
        y = (obj->y + obj->z) >> 8;
        gfx = AnimGetGfx(&work->anim);
        DrawSprite(x, y, gfx, work->tiles, work->palette,
                   AllocObjAffine(obj->angle, obj->scaleX, obj->scaleY, 1), obj->drawFlags, 0xFF0);
        TaskPoolDraw(&work->tasks);
    }
}

void task_sroll_b_char_3(SrollBCharWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

const s32 gSrollBCharSwayOffsets[16] = { -1, -2, -3, -4, -3, -2, -1, 0, 1, 2, 3, 4, 3, 2, 1, 0 };

const s32 gSrollBCharHopOffsets[16] = { -1, -2, -3, -4, -5, -6, -7, -8, -7, -6, -5, -4, -3, -2, -1, 0 };

TaskDesc gTaskDescSrollBChar = {
    "task_sroll_b_char",
    (TaskInitFunc)task_sroll_b_char_0,
    (TaskUpdateFunc)task_sroll_b_char_1,
    (TaskDrawFunc)task_sroll_b_char_2,
    (TaskDestroyFunc)task_sroll_b_char_3,
    sizeof(SrollBCharWork),
};
