#include "task_descriptors.h"
#include "display.h"
#include "smn.h"
#include "anim.h"
#include "sprites_smn.h"
#include "songs.h"
#include "smn_tasks.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_effect.h"
#include "engine_math.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

static const AnimDef sSmnMushuAnimDefs[4] = {
    { gMushu10Frames, gMushu10Anims, gMushu10Tiles, 0, { 0, 0, 0 } },
    { gMushu10Frames, gMushu10Anims, gMushu10Tiles, 1, { 0, 0, 0 } },
    { gMushu10Frames, gMushu10Anims, gMushu10Tiles, 2, { 0, 0, 0 } },
    { gMushu10Frames, gMushu10Anims, gMushu10Tiles, 3, { 0, 0, 0 } },
};

const AnimDef gUnk_0813EABC = { gMushu10Frames, gMushu10Anims, gMushu10Tiles, 4, { 0, 0, 0 } };

TaskDesc gTaskDescSmnMushu = {
    "task_smn_mushu",
    (TaskInitFunc)task_smn_mushu_0,
    (TaskUpdateFunc)task_smn_mushu_1,
    (TaskDrawFunc)task_smn_mushu_2,
    (TaskDestroyFunc)task_smn_mushu_3,
    sizeof(SmnMushuWork),
};

void task_smn_mushu_0(SmnMushuWork* work, SmnArgs* args) {
    BtlObj* body;
    BtlObj* obj;

    body = &work->body;

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= BTL_FLAG_SUMMON_ACTIVE;
        obj = gBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= BTL_FLAG_SUMMON_ACTIVE;
        obj = gRikuBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    }

    body->x = obj->x;
    body->y = obj->y;
    body->z = obj->z - 0x2200;
    body->groundZ = obj->groundZ;

    if (obj->flags & BTLOBJ_FLAG_FACING_LEFT) {
        body->flags = BTLOBJ_FLAG_FACING_LEFT;
    } else {
        body->flags = 0;
    }

    work->variant = args->variant;
    work->palette = LoadObjPalette(gMushuPalette, 32);
    AnimInit(&work->anim, NULL, NULL);
    AnimChangeWithDef(sSmnMushuAnimDefs, &work->anim, 0, ANIM_FLAG_LOOP, work->tiles);
    work->state = 0;
    work->stateTimer = 0;
    work->scaleSteps = 0;
    work->scale = 10;
    work->animating = 0;
    work->unk_150 = 0;

    if (work->mainSide != 0) {
        work->actor = gBtlWork->actor;
    } else {
        work->actor = gRikuBtlWork->actor;
    }

    m4aSongNumStart(SONG_VO_SR_SUMMON00);
    TaskPoolInit(&work->tasks, 3);
}

u8 task_smn_mushu_1(SmnMushuWork* work) {
    BtlObj* body;
    BtlWork* obj;
    s32 px;
    s32 py;
    s32 pz;
    s32 x;
    s32 y;
    s32 z;
    s32 n;
    u16 v1;
    u16 v2;

    body = &work->body;
    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;

    if (obj->flags & BTL_FLAG_DISMISS_SUMMONS) {
        return 0;
    }

    px = body->x;
    py = body->y;
    pz = body->z;
    body->x = work->actor->x;
    body->y = work->actor->y;
    body->z = work->actor->z - 0x2200;

    if (work->actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
        body->flags |= BTLOBJ_FLAG_FACING_LEFT;
    } else {
        body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
    }

    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            work->scaleSteps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_UP);
        }

        ApproachValue(&work->scale, 256, work->scaleSteps);

        if (work->scaleSteps > 0) {
            work->stateTimer++;
            work->scaleSteps--;
        } else {
            work->state = 3;
            work->stateTimer = 0;
            work->animating = 1;
        }

        break;
    case 1:
        if (work->stateTimer == 0) {
            work->scaleSteps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_DOWN);
        }

        ApproachValue(&work->scale, 25, work->scaleSteps);

        if (work->scaleSteps <= 0) {
            return 0;
        }

        work->stateTimer++;
        work->scaleSteps--;
        break;
    case 3:
        AnimChangeWithDef(sSmnMushuAnimDefs, &work->anim, 2, 0, work->tiles);

        if (AnimIsFinished(&work->anim)) {
            work->state = 2;
            work->stateTimer = 0;
        }

        break;
    case 2:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sSmnMushuAnimDefs, &work->anim, 3, ANIM_FLAG_LOOP, work->tiles);

            switch (work->variant) {
            case 0:
                work->scaleSteps = 0x78;
                break;
            case 1:
                work->scaleSteps = 0xF0;
                break;
            case 2:
            default:
                work->scaleSteps = 0x1E0;
                break;
            }
        }

        if (AnimGetGfxIndex(&work->anim) == 5 && work->anim.timer == 0) {
            if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
                x = body->x - 0xC800;
            } else {
                x = body->x + 0xC800;
            }

            y = body->y;
            z = 0;

            switch (work->variant) {
            case 0:
                n = 0x9D;
                break;
            case 1:
                n = 0x9E;
                break;
            case 2:
            default:
                n = 0x9F;
                break;
            }

            MakeOpponentsHittable();
            m4aSongNumStart(SONG_EF_MU_FIRE);

            if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
                BgFxStartFire(0, body->x - 0x3800, body->y, body->z - 0x800,
                              x, y, z, 1, n);
            } else {
                BgFxStartFire(0, body->x + 0x3800, body->y, body->z - 0x800,
                              x, y, z, 0, n);
            }
        }

        BgAnimGetFrameState(&v1, &v2);

        if (v1 <= 3) {
            BgFxAddPosition(body->x - px, body->y - py, body->z - pz);
        }

        if (work->stateTimer > work->scaleSteps) {
            work->state = 1;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    }

    if (work->animating != 0) {
        AnimUpdate(&work->anim);
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_smn_mushu_2(SmnMushuWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);

    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (gBtlWork->scale == 256 && work->scale == gBtlWork->scale) {
        sclY = work->scale;
        sclX = sclY;
        flags |= SPRITE_FLAG_HFLIP;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    sclX = sclX * work->scale >> 8;
    sclY = sclY * work->scale >> 8;

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (sclX <= 256 && sclY <= 256) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4101 - ((body->y >> 8) * 4));
    TaskPoolDraw(&work->tasks);
}

void task_smn_mushu_3(SmnMushuWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= ~BTL_FLAG_SUMMON_ACTIVE;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}
