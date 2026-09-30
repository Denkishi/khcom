#include "sroll.h"
#include "sprites_staff_roll.h"
#include "gba/io_reg.h"
#include "anim.h"
#include "display.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"

s32 func_08114748(s32 x) {
    return x * x;
}

s32 func_08114750(s32 x) {
    return x * x;
}

void task_sroll_a_name_0(SrollANameWork* w, SrollANameArg* a) {
    AnimState* anim;

    w->kind = a->kind;
    w->x = a->x;
    w->y = a->y;
    w->targetX = a->targetX;
    w->targetY = a->targetY;
    w->unk_00 = 0;
    w->timer = 0;

    switch (a->kind) {
    case 0:
#ifdef VERSION_JP
        w->tiles = LoadObjTiles(gUnk_09C638BE, 45 * 32);
#else
        w->tiles = LoadObjTiles(gUnk_09C638BE, 35 * 32);
#endif
        anim = &w->anim;
        AnimInit(anim, gUnk_09EFB200, gUnk_09EFB1F8);
        AnimStart(anim, a->unk_02, 0);
        break;
    case 1:
        w->tiles = LoadObjTiles(gUnk_09A54218[a->nameIndex].tiles, gUnk_09A54218[a->nameIndex].size);
        anim = &w->anim;
        AnimInit(anim, gUnk_09EFB244, gUnk_09EFB208);
        AnimStart(anim, a->unk_02, 0);
        break;
    case 2:
        w->tiles = LoadObjTiles(gUnk_09A54218[a->nameIndex].tiles, gUnk_09A54218[a->nameIndex].size);

        if (a->unk_02 == 1) {
            anim = &w->anim;
            AnimInit(anim, gUnk_09EFB5EC, gUnk_09EFB5B0);
        } else {
            anim = &w->anim;
            AnimInit(anim, gUnk_09EFB244, gUnk_09EFB208);
        }

        AnimStart(anim, 2, 0);
        gBldCnt = (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0);
        gBldAlpha = 0;
        break;
    }

    w->palette = LoadObjPalette(gUnk_09D6CD74, 64);
}

u8 task_sroll_a_name_1(SrollANameWork* w) {
    w->timer++;

    if (w->kind == 2) {
        if (w->timer <= 47) {
            gBldAlpha = w->timer / 3;
        } else {
            if (w->timer == 48) {
                gBldCnt = 0;
                gBldAlpha = 0;
            }

            AnimUpdate(&w->anim);
        }
    } else {
        AnimUpdate(&w->anim);
    }

    return 1;
}

void task_sroll_a_name_2(SrollANameWork* w) {
    s32 x;
    s32 y;
    u16 flags;
    s32 ofs;

    if (w->timer <= 29) {
        x = w->x + (w->targetX - w->x) * w->timer / 30;
        y = w->y + (w->targetY - w->y) * w->timer / 30;
    } else {
        x = w->targetX;
        y = w->targetY;
    }

    flags = 0;

    if (w->kind == 2) {
        flags = SPRITE_FLAG_BLEND;
        ofs = AnimGetFrame(&w->anim) * 32 + 32;
        LoadPalette(&gUnk_09D6CD74[ofs], (u8*)0x05000220 + ((w->palette->index & 15) * 32), 32);
    }

    DrawSprite(x >> 8, y >> 8, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, flags,
               0xFF0 - w->kind);
}

void task_sroll_a_name_3(SrollANameWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

TaskDesc gTaskDescSrollAName = {
    "task_sroll_a_name",
    (TaskInitFunc)task_sroll_a_name_0,
    (TaskUpdateFunc)task_sroll_a_name_1,
    (TaskDrawFunc)task_sroll_a_name_2,
    (TaskDestroyFunc)task_sroll_a_name_3,
    sizeof(SrollANameWork),
};
