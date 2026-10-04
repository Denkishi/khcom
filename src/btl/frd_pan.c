/**
 * frd_pan.c
 * Peter Pan Battle Ally
 */

#include "task_descriptors.h"
#include "frd.h"
#include "sprites_frd.h"
#include "world_types.h"
#include "btl_api.h"
#include "fade.h"
#include "songs.h"
#include "frd_tasks.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "engine_math.h"
#include "game_state.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "sprite_palettes.h"

static const AnimDef sFrdPanAnimDefs[4] = {
    { gPeterTukiFrames, gPeterTukiAnims, gPeterTukiTiles, 0 },
    { gPeterTukiFrames, gPeterTukiAnims, gPeterTukiTiles, 1 },
    { gPeterTukiFrames, gPeterTukiAnims, gPeterTukiTiles, 2 },
    { gPeterTukiFrames, gPeterTukiAnims, gPeterTukiTiles, 3 },
};

TaskDesc gTaskDescFrdPan = {
    "task_frd_pan",
    (TaskInitFunc)task_frd_pan_0,
    (TaskUpdateFunc)task_frd_pan_1,
    (TaskDrawFunc)task_frd_pan_2,
    (TaskDestroyFunc)task_frd_pan_3,
    sizeof(FrdPanWork),
};

void task_frd_pan_0(FrdPanWork* work, FrdArgs* args) {
    BtlObj* body;

    body = &work->body;
    m4aSongNumStart(SONG_VO_SR_SUMMON08);

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= BTL_FLAG_SUMMON_ACTIVE;
        work->actor = gBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= BTL_FLAG_SUMMON_ACTIVE;
        work->actor = gRikuBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    }

    work->variant = args->variant;
    work->state = 0;
    work->stateTimer = 0;
    work->steps = 0;
    work->unk_158 = 0;

    if (work->actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
        body->x = (gBtlWork->xMax + 0x30) << 8;
        body->flags = (BTLOBJ_FLAG_FACING_LEFT | BTLOBJ_FLAG_LARGE_SHADOW);
        work->vx = -0x800;
        work->flyLeft = 0;
    } else {
        body->x = (gBtlWork->xMin - 0x30) << 8;
        body->flags = BTLOBJ_FLAG_LARGE_SHADOW;
        work->vx = 0x800;
        work->flyLeft = 1;
    }

    work->targetX = 0x10000;
    body->y = work->actor->y;
    body->groundZ = 0;
    work->hoverZ = -0x2000;
    body->z = -0x2000;
    work->palette = LoadObjPalette(gPeterPalette, 32);
    AnimInit(&work->anim, NULL, NULL);
    AnimChangeWithDef(sFrdPanAnimDefs, &work->anim, 0, 0, work->tiles);
    TaskPoolInit(&work->tasks, 15);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);

    switch (work->variant) {
    case 0:
        work->duration = 0x78;
        break;
    case 1:
        work->duration = 0xF0;
        break;
    case 2:
    default:
        work->duration = 0x1E0;
        break;
    }
}

void FrdPanSpawnSparkle(FrdPanWork* work) {
    BtlObj sub;

    if (work->stateTimer % 3 == 0) {
        sub.x = work->body.x;
        sub.y = work->body.y;
        sub.z = work->body.z;

        switch (AnimGetGfxIndex(&work->anim)) {
        case 1:
        case 2:
            sub.z -= 0x800;
            break;
        case 3:
        case 4:
            sub.z -= 0x1800;

            if (work->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                sub.x += 0x2000;
            } else {
                sub.x -= 0x2000;
            }

            break;
        case 5:
        default:
            sub.z -= 0x1000;

            if (work->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                sub.x += 0x1000;
            } else {
                sub.x -= 0x1000;
            }

            break;
        }

        TaskCreate(&work->tasks, &gTaskDescSmnTinkeff, &sub);
    }
}

void FrdPanHover(FrdPanWork* work) {
    BtlObj* body;

    body = &work->body;
    body->z += ((work->hoverZ + (SIN((u16)work->stateTimer * 2) << 4)) - body->z) >> 2;
}

u8 task_frd_pan_1(FrdPanWork* work) {
    BtlObj* body = &work->body;
    BtlWork* owner;
    BtlObj* target;
    s32 ground;
    s32 y;
    s32 z;

    if (gGameState.world != WORLD_NEVER_LAND) {
        return 0;
    }

    owner = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    target = owner->actor2;

    if (owner->flags & BTL_FLAG_DISMISS_SUMMONS) {
        return 0;
    }

    if (gBtlWork->boundsCallback != NULL) {
        ground = body->groundZ;
        gBtlWork->boundsCallback(&body->x, &body->y, &body->z, &ground);

        if (ground != body->groundZ) {
            work->hoverZ = body->groundZ - 0x1000;
            body->groundZ = ground;
        }
    }

    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdPanAnimDefs, &work->anim, 0, 0, work->tiles);
            work->steps = 30;
        }

        ApproachValueHalfSteps(&body->x, work->targetX, work->steps);
        FrdPanHover(work);

        if (work->steps <= 0) {
            work->state = 3;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
            work->steps--;
        }

        break;
    case 1:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdPanAnimDefs, &work->anim, 0, 0, work->tiles);
        }

        FrdPanHover(work);

        if (AnimIsFinished(&work->anim)) {
            work->stateTimer = 0;
            work->state = 2;
        } else {
            work->stateTimer++;
        }

        break;
    case 2:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdPanAnimDefs, &work->anim, 0, 0, work->tiles);

            if (!(body->flags & BTLOBJ_FLAG_FACING_LEFT)) {
                work->targetX = (gBtlWork->xMin - 64) * 256;
            } else {
                work->targetX = (gBtlWork->xMax + 64) * 256;
            }

            work->steps = 30;
        }

        work->hoverZ -= 0x400;
        ApproachValue(&body->x, work->targetX, work->steps);
        FrdPanHover(work);

        if (work->steps <= 0) {
            return 0;
        }

        work->stateTimer++;
        work->steps--;
        break;
    case 3:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdPanAnimDefs, &work->anim, 1, 0, work->tiles);
        }

        FrdPanHover(work);

        if (AnimIsFinished(&work->anim)) {
            work->stateTimer = 0;
            work->state = 4;
            m4aSongNumStart(SONG_VO_PP_ATTACK00);
        } else {
            work->stateTimer++;
        }

        break;
    case 4:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdPanAnimDefs, &work->anim, 2, ANIM_FLAG_LOOP, work->tiles);
            work->steps = 70;
            FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
        }

        SelectLockonTarget();

        if (gBtlWork->flags & BTL_FLAG_VS_BATTLE) {
            BtlObj* other = work->mainSide != 0 ? gRikuBtlWork->actor : gBtlWork->actor;
            y = other->y;
            z = other->z;
        } else if (target != NULL) {
            y = target->y;
            z = target->z;
        } else {
            y = work->actor->y;
            z = work->actor->z;
        }

        body->y += (y - body->y) >> 5;
        work->hoverZ += (z - work->hoverZ) >> 5;
        FrdPanHover(work);

        if (work->flyLeft) {
            ApproachValue(&work->vx, -0x800, work->steps);
        } else {
            ApproachValue(&work->vx, 0x800, work->steps);
        }

        body->x += work->vx;

        if (--work->steps <= 0) {
            work->steps = 70;
            work->flyLeft = !work->flyLeft;
        }

        if (work->vx < 0) {
            body->flags |= BTLOBJ_FLAG_FACING_LEFT;
        } else {
            body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
        }

        if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
            if (ApplyAttackBox(150, body->x - 0x1C00, body->y, body->z - 0x1400, 20, 20, 20)) {
                m4aSongNumStart(SONG_BTL_PP_SWORDHIT);
            }
        } else {
            if (ApplyAttackBox(150, body->x + 0x1C00, body->y, body->z - 0x1400, 20, 20, 20)) {
                m4aSongNumStart(SONG_BTL_PP_SWORDHIT);
            }
        }

        if (work->stateTimer > work->duration) {
            work->stateTimer = 0;
            work->state = 5;
        } else {
            work->stateTimer++;
        }

        break;
    case 5:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdPanAnimDefs, &work->anim, 3, 0, work->tiles);
        }

        FrdPanHover(work);

        if (AnimIsFinished(&work->anim)) {
            work->stateTimer = 0;
            work->state = 1;
            FadeToOriginal(FADE_MODE_BLACK, 8);
        } else {
            work->stateTimer++;
        }

        break;
    }

    FrdPanSpawnSparkle(work);
    AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_frd_pan_2(FrdPanWork* work) {
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
    } else if (gBtlWork->scale == 256) {
        sclY = gBtlWork->scale;
        sclX = sclY;
        flags |= SPRITE_FLAG_HFLIP;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (gBtlWork->scale == 256) {
        affine = NULL;
    } else if (gBtlWork->scale <= 255) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_frd_pan_3(FrdPanWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= ~BTL_FLAG_SUMMON_ACTIVE;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}
