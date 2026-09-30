#include "bos6.h"
#include "sprites_bos6.h"
#include "fade.h"

TaskDesc gTaskDescBosPcAcd = {
    "task_bos_pc_acd",
    (TaskInitFunc)task_bos_pc_acd_0,
    (TaskUpdateFunc)task_bos_pc_acd_1,
    (TaskDrawFunc)task_bos_pc_acd_2,
    (TaskDestroyFunc)task_bos_pc_acd_3,
    sizeof(PcAcdWork),
};

s32 BosPcAcdSquare(s32 x) {
    return x * x;
}

s32 BosPcAcdSquare2(s32 x) {
    return x * x;
}

void BosPcAcdSetOff(Task* task, u8 v) {
    PcAcdWork* work = task->work;

    work->acdOff = v;
}

void task_bos_pc_acd_0(PcAcdWork* work, PcShared* arg) {
    AnimState* anim;

    work->unk_000 = 0;
    work->tiles = AllocObjTiles(0x300, gUnk_09C489E4);
    work->palette = LoadObjPalette(gUnk_09D693D4, 0x60);
    work->x = -1;
    work->y = -1;
    work->unk_014 = -1;
    work->shared = arg;
    anim = &work->anim;
    AnimInit(anim, gUnk_09EFABA4, gUnk_09EFAB68);

    if (work->shared->inEvent == 1) {
        work->acdOff = 1;
        AnimStart(anim, 1, 0);
    } else {
        work->acdOff = 0;
        AnimStart(anim, 0, 0);
    }
}

u8 task_bos_pc_acd_1(PcAcdWork* work) {
    AnimState* anim;
    s32 v;

    FadeSetPaletteExcluded(work->palette->index + 17, 0);
    FadeSetPaletteExcluded(work->palette->index + 18, 0);
    anim = &work->anim;
    AnimUpdate(anim);

    if (gBtlWork->actor->z >= 0) {
        if ((gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) == 0 ||
            (gBtlWork->flags & BTL_FLAG_SUMMON_ACTIVE) == 0) {
            if (work->x < 0 || AnimIsFinished(anim) == 1) {
                v = 0;

                if (work->acdOff == 1) {
                    v = 1;
                }

                AnimReset(anim);
                AnimStart(anim, v, 0);
            }
        }
    }

    return 1;
}

void task_bos_pc_acd_2(PcAcdWork* work) {
    s16 sx;
    s16 sy;
    BtlWork** gp;
    BtlObj* pos;
    PcShared* shared;
    AnimState* anim;
    void** tbl;
    s32 ofs;
    void* gfx;
    s32 ox;
    s32 oy;

    gp = &gBtlWork;
    pos = (*gp)->actor;
    pos->flags &= ~BTLOBJ_FLAG_HIDE_SHADOW;
    ox = 0;
    oy = 0;
    shared = work->shared;

    if (shared->inEvent == 1) {
        ox = gEventState->shakeX << 8;
        oy = gEventState->shakeY << 8;
    }

    work->x = pos->x;
    work->y = pos->y - 0x400;
    work->unk_014 = 0;

    if (shared->unk_04 == 1) {
        tbl = gUnk_09EFAB68;
        ofs = AnimGetGfxIndex(&work->anim) + 5;
        gfx = tbl[ofs];

        if ((*gp)->actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
            WorldToScreen(&sx, &sy, work->x - ox + 0x600, work->y - oy, 0);
        } else {
            WorldToScreen(&sx, &sy, work->x - ox + 0x200, work->y - oy, 0);
        }

        DrawSprite(sx, sy, gfx, work->tiles, work->palette, 0, GetBattleSpritePriorityFlags(work->y),
                   (u16)((-0x1004 - ((work->y >> 8) << 2)) | 3));
    } else if (pos->z >= 0) {
        if (((*gp)->flags & BTL_FLAG_PLAYER_CARD_ACTION) && ((*gp)->flags & BTL_FLAG_SUMMON_ACTIVE)) {
            return;
        }

        anim = &work->anim;

        if (AnimGetId(anim) == 1) {
            (*gp)->actor->flags |= BTLOBJ_FLAG_HIDE_SHADOW;

            if ((*gp)->actor->flags & BTLOBJ_FLAG_HIT_LOCKED) {
                return;
            }

            tbl = gUnk_09EFAB68;
            ofs = AnimGetGfxIndex(anim) + 5;
            gfx = tbl[ofs];

            if ((*gp)->actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
                WorldToScreen(&sx, &sy, work->x - ox + 0x600, work->y - oy, 0);
            } else {
                WorldToScreen(&sx, &sy, work->x - ox + 0x200, work->y - oy, 0);
            }

            DrawSprite(sx, sy, gfx, work->tiles, work->palette, 0, GetBattleSpritePriorityFlags(work->y),
                       (u16)((-0x1004 - ((work->y >> 8) << 2)) | 3));
        } else {
            WorldToScreen(&sx, &sy, work->x - ox, work->y - oy, 0);
            DrawSprite(sx, sy, AnimGetGfx(anim), work->tiles, work->palette, 0, GetBattleSpritePriorityFlags((*gp)->actor->y),
                       (u16)(-0x1004 - (((*gp)->actor->y >> 8) << 2)));
        }
    }
}

void task_bos_pc_acd_3(PcAcdWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}
