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

void SrollBCharChangeAnim(SrollBCharWork* w) {
    const EvtObjAnim* def;
    const EvtAnimDef* gfx;

    def = w->obj->animEntry;
    gfx = def->animDef;
    AnimChangeWithTables(&w->anim, def->animId, def->flags, gfx->anims, gfx->gfxTable);
    SetObjTileSource(w->tiles, gfx->tiles);
    w->obj->flags &= ~EVTOBJ_FLAG_ANIM_CHANGED;
}

void task_sroll_b_char_0(SrollBCharWork* w, EvtObjParam* a) {
    const EvtObjRes* res;
    AnimState* anim;

    res = a->res;
    w->motion = 0;
    w->motionTimer = 0;
    w->obj = a->obj;
    w->tiles = AllocObjTiles(res->tileCount * 32, NULL);
    w->palette = LoadObjPalette(res->palette, 32);
    anim = &w->anim;
    AnimInit(anim, NULL, NULL);
    w->obj->anim = anim;
    w->obj->paletteIndex = w->palette->index;
    SrollBCharChangeAnim(w);
    TaskPoolInit(&w->tasks, 4);
}

s32 task_sroll_b_char_1(SrollBCharWork* w) {
    SrollBCrtnArg a;

    if (w->obj->flags & EVTOBJ_FLAG_ANIM_CHANGED) {
        SrollBCharChangeAnim(w);
    }

    if ((w->obj->drawFlags & SPRITE_FLAG_BLEND) == 0) {
        FadeSetPaletteExcluded((w->palette->index & 15) + 16, 0);
    } else {
        FadeSetPaletteExcluded((w->palette->index & 15) + 16, 1);
    }

    AnimUpdate(&w->anim);
    TaskPoolUpdate(&w->tasks);

    switch (w->motion) {
    case 1:
        w->obj->x -= 128;
        w->obj->y += 128;
        break;
    case 2:
        w->obj->z = gSrollBCharHopOffsets[(w->motionTimer >> 2) & 15] << 8;
        w->motionTimer++;
        break;
    case 3:
        if ((w->motionTimer & 3) == 0) {
            a.kind = 2;
            a.x = w->obj->x;
            a.y = w->obj->y;
            TaskCreate(&w->tasks, &gTaskDescSrollBCrtn, &a);
        }

        w->obj->z = (gSrollBCharHopOffsets[(w->motionTimer >> 2) & 15] << 8) >> 2;
        w->motionTimer++;
        break;
    case 4:
        w->obj->x += 128;
        w->obj->y -= 128;
        break;
    case 5:
        w->obj->x += (gSrollBCharSwayOffsets[(w->motionTimer >> 2) & 15] << 8) >> 2;
        w->motionTimer++;
        break;
    }

    return 1;
}

void task_sroll_b_char_2(SrollBCharWork* w) {
    EvtObj* obj;
    void* gfx;
    u16 x;
    u16 y;

    obj = w->obj;

    if ((obj->flags & EVTOBJ_FLAG_HIDDEN) == 0) {
        x = obj->x >> 8;
        y = (obj->y + obj->z) >> 8;
        gfx = AnimGetGfx(&w->anim);
        DrawSprite(x, y, gfx, w->tiles, w->palette,
                   AllocObjAffine(obj->angle, obj->scaleX, obj->scaleY, 1), obj->drawFlags, 0xFF0);
        TaskPoolDraw(&w->tasks);
    }
}

void task_sroll_b_char_3(SrollBCharWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    TaskPoolDestroy(&w->tasks);
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
