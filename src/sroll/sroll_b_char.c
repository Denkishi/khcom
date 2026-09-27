#include "sroll.h"
#include "evt.h"

static s32 Square(s32 x) {
    return x * x;
}

void func_081149B0(Task* task, s32 v) {
    ((SrollBCharWork*)task->work)->unk_00 = v;
}

void func_081149B8(SrollBCharWork* w) {
    const EvtObjAnim* def;
    EvtAnimDef* gfx;

    def = w->obj->animEntry;
    gfx = def->animDef;
    AnimChangeWithTables(&w->anim, def->animId, def->flags, gfx->anims, gfx->gfxTable);
    SetObjTileSource(w->tiles, gfx->tiles);
    w->obj->flags &= 0xFFFE;
}

void task_sroll_b_char_0(SrollBCharWork* w, EvtObjParam* a) {
    EvtObjRes* res;
    AnimState* anim;

    res = a->res;
    w->unk_00 = 0;
    w->unk_04 = 0;
    w->obj = a->obj;
    w->tiles = AllocObjTiles((u16)(res->tileCount * 32), 0);
    w->palette = LoadObjPalette(res->palette, 32);
    anim = &w->anim;
    AnimInit(anim, 0, 0);
    w->obj->anim = anim;
    w->obj->unk_1C = w->palette->index;
    func_081149B8(w);
    TaskPoolInit(&w->tasks, 4);
}

s32 task_sroll_b_char_1(SrollBCharWork* w) {
    SrollBCrtnArg a;

    if (w->obj->flags & 1) {
        func_081149B8(w);
    }

    if ((w->obj->unk_16 & 4) == 0) {
        FadeSetPaletteExcluded((w->palette->index & 15) + 16, 0);
    } else {
        FadeSetPaletteExcluded((w->palette->index & 15) + 16, 1);
    }

    AnimUpdate(&w->anim);
    TaskPoolUpdate(&w->tasks);

    switch (w->unk_00) {
    case 1:
        w->obj->x -= 128;
        w->obj->y += 128;
        break;
    case 2:
        w->obj->z = gUnk_09A5430C[(w->unk_04 >> 2) & 15] << 8;
        w->unk_04++;
        break;
    case 3:
        if ((w->unk_04 & 3) == 0) {
            a.unk_00 = 2;
            a.x = w->obj->x;
            a.y = w->obj->y;
            TaskCreate(&w->tasks, &gTaskDescSrollBCrtn, &a);
        }

        w->obj->z = (gUnk_09A5430C[(w->unk_04 >> 2) & 15] << 8) >> 2;
        w->unk_04++;
        break;
    case 4:
        w->obj->x += 128;
        w->obj->y -= 128;
        break;
    case 5:
        w->obj->x += (gUnk_09A542CC[(w->unk_04 >> 2) & 15] << 8) >> 2;
        w->unk_04++;
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

    if ((obj->flags & 2) == 0) {
        x = obj->x >> 8;
        y = (obj->y + obj->z) >> 8;
        gfx = AnimGetGfx(&w->anim);
        DrawSprite(x, y, gfx, w->tiles, w->palette,
                   AllocObjAffine(obj->angle, obj->scaleX, obj->scaleY, 1), obj->unk_16, 0xFF0);
        TaskPoolDraw(&w->tasks);
    }
}

void task_sroll_b_char_3(SrollBCharWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    TaskPoolDestroy(&w->tasks);
}

const s32 gUnk_09A542CC[16] = { -1, -2, -3, -4, -3, -2, -1, 0, 1, 2, 3, 4, 3, 2, 1, 0 };

const s32 gUnk_09A5430C[16] = { -1, -2, -3, -4, -5, -6, -7, -8, -7, -6, -5, -4, -3, -2, -1, 0 };

TaskDesc gTaskDescSrollBChar = {
    "task_sroll_b_char",
    (TaskInitFunc)task_sroll_b_char_0,
    (TaskUpdateFunc)task_sroll_b_char_1,
    (TaskFunc)task_sroll_b_char_2,
    (TaskFunc)task_sroll_b_char_3,
    sizeof(SrollBCharWork),
};
