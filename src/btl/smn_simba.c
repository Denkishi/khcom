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
#include "engine_math.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

static const AnimDef sSmnSimbaAnimDef = { gShinba10Frames, gShinba10Anims, gShinba10Tiles, 0, { 0, 0, 0 } };

TaskDesc gTaskDescSmnSimba = {
    "task_smn_simba",
    (TaskInitFunc)task_smn_simba_0,
    (TaskUpdateFunc)task_smn_simba_1,
    (TaskDrawFunc)task_smn_simba_2,
    (TaskDestroyFunc)task_smn_simba_3,
    sizeof(SmnSimbaWork),
};

void task_smn_simba_0(SmnSimbaWork* work, SmnArgs* args) {
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
    body->z = obj->originZ;
    body->groundZ = obj->originZ;

    if (obj->flags & BTLOBJ_FLAG_FACING_LEFT) {
        body->flags = (BTLOBJ_FLAG_FACING_LEFT | BTLOBJ_FLAG_LARGE_SHADOW);
    } else {
        body->flags = BTLOBJ_FLAG_LARGE_SHADOW;
    }

    work->variant = args->variant;
    work->palette = LoadObjPalette(gShinbaPalette, 32);
    AnimInit(&work->anim, NULL, NULL);
    AnimChangeWithDef(&sSmnSimbaAnimDef, &work->anim, 0, 0, work->tiles);
    work->state = 0;
    work->stateTimer = 0;
    work->steps = 0;
    work->unk_14C = 0;
    work->scale = 10;
    work->animating = 0;
    TaskPoolInit(&work->tasks, 2);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

u8 task_smn_simba_1(SmnSimbaWork* work) {
    BtlObj* body;
    BtlWork* obj;

    body = &work->body;
    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;

    if (obj->flags & BTL_FLAG_DISMISS_SUMMONS) {
        // fakematch
        do {
            return 0;
        } while (0);
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

        if (work->steps > 0) {
            work->stateTimer++;
            work->steps--;
        } else {
            work->state = 1;
            work->stateTimer = 0;
            work->animating = 1;
        }

        break;
    case 2:
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
    case 1:
        switch (work->stateTimer) {
        case 0:
            if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
                SetBattleZoom(30, 0x133, body->x - 0x1400,
                              body->y + body->z - 0x1400);
            } else {
                SetBattleZoom(30, 0x133, body->x + 0x1400,
                              body->y + body->z - 0x1400);
            }

            break;
        case 50:
            switch (work->variant) {
            case 0:
                m4aSongNumStart(SONG_BTL_SIMBA_ROA0);
                break;
            case 1:
                m4aSongNumStart(SONG_BTL_SIMBA_ROA1);
                break;
            case 2:
            default:
                m4aSongNumStart(SONG_BTL_SIMBA_ROA2);
                break;
            }

            BtlMapStartShake();
            FadeFromAmount(FADE_MODE_GREEN, 8, 20);
            SetBattleZoom(30, 0xCC, 0x10000, 0x15E00);

            if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
                BgFxStartShockwave(body->x - 0x1400, body->y + body->z - 0x1400, 1);
            } else {
                BgFxStartShockwave(body->x + 0x1400, body->y + body->z - 0x1400, 0);
            }

            switch (work->variant) {
            case 0:
                if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    ApplyAttackBox(0x99, body->x - 0x8000, body->y, body->z,
                                  0x80, 0x100, 0x100);
                } else {
                    ApplyAttackBox(0x99, body->x + 0x8000, body->y, body->z,
                                  0x80, 0x100, 0x100);
                }

                break;
            case 1:
                if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    ApplyAttackBox(0x9A, body->x - 0x8000, body->y, body->z,
                                  0x80, 0x100, 0x100);
                } else {
                    ApplyAttackBox(0x9A, body->x + 0x8000, body->y, body->z,
                                  0x80, 0x100, 0x100);
                }

                break;
            case 2:
            default:
                if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    ApplyAttackBox(0x9B, body->x - 0x8000, body->y, body->z,
                                  0x80, 0x100, 0x100);
                } else {
                    ApplyAttackBox(0x9B, body->x + 0x8000, body->y, body->z,
                                  0x80, 0x100, 0x100);
                }

                break;
            }

            break;
        }

        if (AnimIsFinished(&work->anim)) {
            SetBattleZoom(8, 256, gBtlWork->x2, gBtlWork->y2);
            work->state = 2;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    }

    if (work->animating != 0) {
        AnimUpdate(&work->anim);
    }

    ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);

    if (body->z > body->groundZ) {
        body->z = body->groundZ;
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_smn_simba_2(SmnSimbaWork* work) {
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

void task_smn_simba_3(SmnSimbaWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= ~BTL_FLAG_SUMMON_ACTIVE;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}
