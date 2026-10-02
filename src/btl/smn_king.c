#include "task_descriptors.h"
#include "smn.h"
#include "anim.h"
#include "sprites_smn.h"
#include "btl_api.h"
#include "fade.h"
#include "songs.h"
#include "smn_tasks.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "card_battle.h"
#include "engine_math.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

static const AnimDef sSmnKingAnimDefs[3] = {
    { gMickey10Frames, gMickey10Anims, gMickey10Tiles, 0, { 0, 0, 0 } },
    { gMickey10Frames, gMickey10Anims, gMickey10Tiles, 1, { 0, 0, 0 } },
    { gMickey10Frames, gMickey10Anims, gMickey10Tiles, 2, { 0, 0, 0 } },
};

void task_smn_king_0(SmnKingWork* work, SmnArgs* args) {
    BtlObj* body;
    BtlObj* obj;

    body = &work->body;

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= BTL_FLAG_SUMMON_ACTIVE;
        obj = gBtlWork->actor;
        work->tiles = gBtlWork->tiles;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= BTL_FLAG_SUMMON_ACTIVE;
        obj = gRikuBtlWork->actor;
        work->tiles = gRikuBtlWork->tiles;
    }

    body->x = obj->originX;
    body->y = obj->originY;
    body->z = obj->originZ - 0x4000;
    body->groundZ = 0;
    body->flags = obj->flags & BTLOBJ_FLAG_FACING_LEFT;
    work->variant = args->variant;
    work->palette = LoadObjPalette(gMickeyPalette, 32);
    work->vz = 0;
    AnimInit(&work->anim, NULL, NULL);
    AnimChangeWithDef(sSmnKingAnimDefs, &work->anim, 0, 0, work->tiles);
    work->state = 0;
    work->stateTimer = 0;
    work->steps = 0;
    work->unk_14C = 0;
    work->scale = 10;
    work->animating = 0;
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

u8 SmnKingApplyGravity(SmnKingWork* work) {
    BtlObj* body;

    body = &work->body;
    ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);
    body->z += work->vz;
    work->vz += 0x33;

    if (body->z > body->groundZ) {
        body->z = body->groundZ;
        work->vz = 0;
        return 1;
    }

    return 0;
}

u8 task_smn_king_1(SmnKingWork* work) {
    BtlObj* body = &work->body;
    BtlWork* obj;
    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;

    if (obj->flags & BTL_FLAG_DISMISS_SUMMONS) {
        return 0;
    }

    BtlMapFollowPosition(body->x, body->y, body->z);

    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            work->steps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_UP);
        }

        ApproachValue(&work->scale, 256, work->steps);

        if (work->steps <= 0) {
            work->state = 2;
            work->stateTimer = 0;
            work->animating = 1;
        } else {
            work->stateTimer++;
            work->steps--;
        }

        break;
    case 1:
        if (work->stateTimer == 0) {
            work->steps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_DOWN);
        }

        ApproachValue(&work->scale, 25, work->steps);

        if (work->steps <= 0) {
            return 0;
        }

        work->stateTimer++;
        work->steps--;
        break;
    case 2:
        AnimChangeWithDef(sSmnKingAnimDefs, &work->anim, 1, 0, work->tiles);

        if (SmnKingApplyGravity(work)) {
            work->state = 4;
            work->stateTimer = 0;
            FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
        }

        break;
    case 4:
        AnimChangeWithDef(sSmnKingAnimDefs, &work->anim, 2, 0, work->tiles);

        if (AnimGetFrame(&work->anim) == 5 && work->anim.timer == 3) {
            BgFxStartFlash(body->x, body->y, body->z - 0x1300);
            ApplyAttackBox(3, body->x, body->y, body->z, 256, 256, 256);
            m4aSongNumStart(SONG_EF_TLIMIT01);

            switch (work->variant) {
            case 0:
                gBtlWork->actor->hp += gBtlWork->actor->maxHp / 5;
                RequestSoraKingReload0();
                break;
            case 1:
                gBtlWork->actor->hp += gBtlWork->actor->maxHp / 2;
                RequestSoraKingReload1();
                break;
            case 2:
            default:
                gBtlWork->actor->hp += gBtlWork->actor->maxHp;
                RequestSoraKingReload2();
                break;
            }

            CreateBtlPopTask(gBtlWork->actor, 10);

            if (gBtlWork->actor->hp > gBtlWork->actor->maxHp) {
                gBtlWork->actor->hp = gBtlWork->actor->maxHp;
            }
        }

        ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);

        if (AnimIsFinished(&work->anim)) {
            work->state = 5;
            work->stateTimer = 0;
        }

        break;
    case 5:
        ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);

        if (work->stateTimer > 60) {
            FadeToOriginal(FADE_MODE_BLACK, 8);
            work->state = 1;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    }

    if (body->z > body->groundZ) {
        body->z = body->groundZ;
    }

    if (work->animating != 0) {
        AnimUpdate(&work->anim);
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_smn_king_2(SmnKingWork* work) {
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
               -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_smn_king_3(SmnKingWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= ~BTL_FLAG_SUMMON_ACTIVE;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

TaskDesc gTaskDescSmnKing = {
    "task_smn_king",
    (TaskInitFunc)task_smn_king_0,
    (TaskUpdateFunc)task_smn_king_1,
    (TaskDrawFunc)task_smn_king_2,
    (TaskDestroyFunc)task_smn_king_3,
    sizeof(SmnKingWork),
};
