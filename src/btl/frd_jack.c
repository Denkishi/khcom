/**
 * frd_jack.c
 * Jack Skellington Battle Ally
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
#include "btl_effect.h"
#include "engine_math.h"
#include "game_state.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "sprite_palettes.h"

static const AnimDef sFrdJackAnimDefs[5] = {
    { gUnk_09EDE594, gUnk_09EDE5B4, gUnk_08875122, 0 },
    { gUnk_09EDE594, gUnk_09EDE5B4, gUnk_08875122, 1 },
    { gUnk_09EDE594, gUnk_09EDE5B4, gUnk_08875122, 2 },
    { gUnk_09EDE594, gUnk_09EDE5B4, gUnk_08875122, 3 },
    { gUnk_09EDE594, gUnk_09EDE5B4, gUnk_08875122, 4 },
};

TaskDesc gTaskDescFrdJack = {
    "task_frd_jack",
    (TaskInitFunc)task_frd_jack_0,
    (TaskUpdateFunc)task_frd_jack_1,
    (TaskDrawFunc)task_frd_jack_2,
    (TaskDestroyFunc)task_frd_jack_3,
    sizeof(FrdJackWork),
};

u8 FrdJackApplyGravity(FrdJackWork* work) {
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

void task_frd_jack_0(FrdJackWork* work, FrdArgs* args) {
    BtlObj* body;

    body = &work->body;
    m4aSongNumStart(SONG_VO_SR_SUMMON07);

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
    work->vz = 0;

    if (work->actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
        work->targetX = work->actor->x - 0x3000;
        body->x = (gBtlWork->xMax + 0x30) << 8;
        body->flags = BTLOBJ_FLAG_FACING_LEFT;
    } else {
        work->targetX = work->actor->x + 0x3000;
        body->x = (gBtlWork->xMin - 0x30) << 8;
        body->flags = 0;
    }

    body->y = work->actor->y;
    body->z = -0x5000;
    body->groundZ = 0;
    work->rotation = 0;
    work->palette = LoadObjPalette(gJackPalette, 32);
    AnimInit(&work->anim, NULL, NULL);
    AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 0, 0, work->tiles);

    switch (args->variant) {
    case 0:
        work->repeatsLeft = 0;
        break;
    case 1:
        work->repeatsLeft = 1;
        break;
    case 2:
    default:
        work->repeatsLeft = 2;
        break;
    }

    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

u8 task_frd_jack_1(FrdJackWork* work) {
    BtlObj* body = &work->body;
    BtlWork* owner;
    BtlObj* target;

    if (gGameState.world != WORLD_HALLOWEEN_TOWN) return 0;

    if (work->mainSide != 0) {
        owner = gBtlWork;
        target = owner->actor2;
    } else {
        owner = gRikuBtlWork;
        target = owner->actor2;
    }

    if (owner->flags & BTL_FLAG_DISMISS_SUMMONS) return 0;

    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 1, 0, work->tiles);
            work->stateTimer++;
        }

        body->x += (work->targetX - body->x) >> 4;
        ClampBattlePosition(&body->x, &body->y, -16, 0);

        if (FrdJackApplyGravity(work)) {
            work->state = 1;
            work->stateTimer = 0;
            m4aSongNumStart(SONG_VO_JC_ATTACK00);
        }

        break;
    case 1:
        if (work->stateTimer == 0) AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 2, 0, work->tiles);

        if (AnimIsFinished(&work->anim)) {
            u16 spell;
            SelectLockonTarget();
            spell = GetRandom();
            spell &= 3;

            switch (spell) {
            case 0:
                work->state = 4;
                break;
            case 1:
                work->state = 5;
                break;
            case 2:
                work->state = 6;
                break;
            case 3:
                work->state = 7;
                break;
            }

            work->stateTimer = 0;
        } else work->stateTimer++;

        break;
    case 2:
        if (work->repeatsLeft > 0) {
            work->state = 8;
            work->stateTimer = 0;
            work->repeatsLeft--;
        } else {
            if (work->stateTimer == 0) AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 4, 0, work->tiles);

            if (AnimIsFinished(&work->anim)) {
                work->state = 3;
                work->stateTimer = 0;
            } else work->stateTimer++;
        }

        break;
    case 3:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 3, 0, work->tiles);

            if (!(body->flags & BTLOBJ_FLAG_FACING_LEFT)) work->targetX = (gBtlWork->xMin - 64) * 256;
            else work->targetX = (gBtlWork->xMax + 64) * 256;

            work->vz = -0x500;
            work->steps = 30;
        }

        ApproachValue(&body->x, work->targetX, work->steps);
        FrdJackApplyGravity(work);

        if (work->steps <= 0) return 0;

        work->stateTimer++;
        work->steps--;
        break;
    case 8:
        if (work->stateTimer == 0) AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 4, 0, work->tiles);

        if (AnimIsFinished(&work->anim)) {
            work->state = 9;
            GetRandom();
            m4aSongNumStart(SONG_VO_JC_ATTACK00);
            work->stateTimer = 0;
        } else work->stateTimer++;

        break;
    case 9:
        if (work->stateTimer == 0) {
            if (work->actor->flags & BTLOBJ_FLAG_FACING_LEFT) work->targetX = work->actor->x - 0x2D00;
            else work->targetX = work->actor->x + 0x2D00;

            work->targetY = work->actor->y;
            work->vz = -0x500;
            work->steps = 45;

            if (work->targetX > body->x) {
                if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    work->rotationTarget = 256;
                } else {
                    work->rotationTarget = -256;
                }
            } else {
                if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    work->rotationTarget = -256;
                } else {
                    work->rotationTarget = 256;
                }
            }

            work->stateTimer++;
        }

        FrdJackApplyGravity(work);

        if (work->vz > 0) AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 1, 0, work->tiles);
        else AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 3, 0, work->tiles);

        if (work->steps > 0) {
            ApproachValueHalfSteps(&body->x, work->targetX, work->steps);
            ApproachValueHalfSteps(&body->y, work->targetY, work->steps);

            if (work->steps <= 39) ApproachValueHalfSteps(&work->rotation, work->rotationTarget, work->steps);

            work->steps--;
        }

        if (body->z >= body->groundZ && work->steps <= 0) {
            work->stateTimer = 0;
            work->rotation = 0;
            work->state = 10;
        }

        break;
    case 10:
        if (work->stateTimer == 0) AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 2, 0, work->tiles);

        if (AnimIsFinished(&work->anim)) {
            u16 spell;
            SelectLockonTarget();
            spell = GetRandom();
            spell &= 3;

            switch (spell) {
            case 0:
                work->state = 4;
                break;
            case 1:
                work->state = 5;
                break;
            case 2:
                work->state = 6;
                break;
            case 3:
                work->state = 7;
                break;
            }

            work->stateTimer = 0;
        } else work->stateTimer++;

        break;
    case 4:
        {
            s32 x, y, z;

            if (work->stateTimer == 0) {
                AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 0, 0, work->tiles);
                AnimReset(&work->anim);

                if (target != NULL) {
                    if (target->x < body->x) body->flags |= BTLOBJ_FLAG_FACING_LEFT;
                    else body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
                }
            }

            if (work->stateTimer == 44) {
                if (target != NULL) {
                    x = target->x;
                    y = target->y;
                    z = target->z - target->centerHeight * 256;

                    if (x < body->x) body->flags |= BTLOBJ_FLAG_FACING_LEFT;
                    else body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
                } else {
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) x = body->x - 0xC800;
                    else x = body->x + 0xC800;

                    y = body->y;
                    z = body->z - 0x1800;
                }

                switch (work->variant) {
                case 0:
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) BgFxStartFire(0, body->x - 0x4A00, body->y, body->z - 0x1800, x, y, z, 1, 133);
                    else BgFxStartFire(0, body->x + 0x4A00, body->y, body->z - 0x1800, x, y, z, 0, 133);

                    break;
                case 1:
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) BgFxStartFire(1, body->x - 0x4A00, body->y, body->z - 0x1800, x, y, z, 1, 134);
                    else BgFxStartFire(1, body->x + 0x4A00, body->y, body->z - 0x1800, x, y, z, 0, 134);

                    break;
                case 2:
                default:
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) BgFxStartFire(2, body->x - 0x4A00, body->y, body->z - 0x1800, x, y, z, 1, 135);
                    else BgFxStartFire(2, body->x + 0x4A00, body->y, body->z - 0x1800, x, y, z, 0, 135);

                    break;
                }
            }

            if (work->stateTimer > 44) {
                if (!BgFxIsActive()) {
                    work->state = 2;
                    work->stateTimer = 0;
                    break;
                }

                if (target != NULL) BgFxSetTarget(target->x, target->y, target->z - target->centerHeight * 256);
            }

            work->stateTimer++;
            break;
        }
    case 7:
        {
            s32 x, y, z;

            if (work->stateTimer == 0) {
                AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 0, 0, work->tiles);
                AnimReset(&work->anim);

                if (target != NULL) {
                    if (target->x < body->x) body->flags |= BTLOBJ_FLAG_FACING_LEFT;
                    else body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
                }

                FadeToAmount(FADE_MODE_ADD_WHITE, 13, 60);
            }

            if (work->stateTimer == 44) {
                if (target != NULL) {
                    x = target->x;
                    y = target->y;
                    z = target->groundZ;

                    if (x < body->x) body->flags |= BTLOBJ_FLAG_FACING_LEFT;
                    else body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
                } else {
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) x = body->x - 0x4000;
                    else x = body->x + 0x4000;

                    y = body->y;
                    z = body->groundZ;
                }

                switch (work->variant) {
                case 0:
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) BgFxStartGravity(0, body->x - 0x2800, body->y, body->z - 0x1800, x, y, z, 1, 142);
                    else BgFxStartGravity(0, body->x + 0x2800, body->y, body->z - 0x1800, x, y, z, 0, 142);

                    break;
                case 1:
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) BgFxStartGravity(1, body->x - 0x2800, body->y, body->z - 0x1800, x, y, z, 1, 143);
                    else BgFxStartGravity(1, body->x + 0x2800, body->y, body->z - 0x1800, x, y, z, 0, 143);

                    break;
                case 2:
                default:
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) BgFxStartGravity(2, body->x - 0x2800, body->y, body->z - 0x1800, x, y, z, 1, 144);
                    else BgFxStartGravity(2, body->x + 0x2800, body->y, body->z - 0x1800, x, y, z, 0, 144);

                    break;
                }
            }

            if (work->stateTimer > 44 && !BgFxIsActive()) {
                FadeToOriginal(FADE_MODE_ADD_WHITE, 20);
                work->state = 2;
                work->stateTimer = 0;
            } else work->stateTimer++;

            break;
        }
    case 5:
        {
            s32 x, y, z;

            if (work->stateTimer == 0) {
                AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 0, 0, work->tiles);
                AnimReset(&work->anim);

                if (target != NULL) {
                    if (target->x < body->x) body->flags |= BTLOBJ_FLAG_FACING_LEFT;
                    else body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
                }
            }

            if (work->stateTimer == 44) {
                if (target != NULL) {
                    x = target->x;
                    y = target->y;
                    z = target->z - target->centerHeight * 256;

                    if (x < body->x) body->flags |= BTLOBJ_FLAG_FACING_LEFT;
                    else body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
                } else {
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) x = body->x - 0x6400;
                    else x = body->x + 0x6400;

                    y = body->y;
                    z = body->z - 0x1800;
                }

                switch (work->variant) {
                case 0:
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) BgFxStartBlizzard(0, body->x - 0x4A00, body->y, body->z - 0x1800, x, y, z, 1, 136);
                    else BgFxStartBlizzard(0, body->x + 0x4A00, body->y, body->z - 0x1800, x, y, z, 0, 136);

                    break;
                case 1:
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) BgFxStartBlizzard(1, body->x - 0x4A00, body->y, body->z - 0x1800, x, y, z, 1, 137);
                    else BgFxStartBlizzard(1, body->x + 0x4A00, body->y, body->z - 0x1800, x, y, z, 0, 137);

                    break;
                case 2:
                default:
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) BgFxStartBlizzard(2, body->x - 0x4A00, body->y, body->z - 0x1800, x, y, z, 1, 138);
                    else BgFxStartBlizzard(2, body->x + 0x4A00, body->y, body->z - 0x1800, x, y, z, 0, 138);

                    break;
                }
            }

            if (work->stateTimer > 44) {
                if (!BgFxIsActive()) {
                    work->state = 2;
                    work->stateTimer = 0;
                    break;
                }

                if (target != NULL) BgFxSetTarget(target->x, target->y, target->z - target->centerHeight * 256);
            }

            work->stateTimer++;
            break;
        }
    case 6:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 0, 0, work->tiles);
            AnimReset(&work->anim);

            if (target != NULL) {
                if (target->x < body->x) body->flags |= BTLOBJ_FLAG_FACING_LEFT;
                else body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }
        }

        if (work->stateTimer == 44) {
            switch (work->variant) {
            case 0:
                {
                    s32 x, y, z;

                    if (target != NULL) {
                        x = target->x;
                        y = target->y;
                        z = target->groundZ;
                    } else {
                        if (body->flags & BTLOBJ_FLAG_FACING_LEFT) x = body->x - 0x5000;
                        else x = body->x + 0x5000;

                        y = body->y;
                        z = 0;
                    }

                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) BgFxStartThunder(0, body->x - 0x2800, body->y, body->z - 0x1800, x, y, z, 139);
                    else BgFxStartThunder(0, body->x + 0x2800, body->y, body->z - 0x1800, x, y, z, 139);

                    break;
                }
            case 1:
                if (body->flags & BTLOBJ_FLAG_FACING_LEFT) BgFxStartWideThunder(1, body->x - 0x2800, body->y, body->z - 0x1800, body->groundZ, 140);
                else BgFxStartWideThunder(1, body->x + 0x2800, body->y, body->z - 0x1800, body->groundZ, 140);

                break;
            case 2:
            default:
                if (body->flags & BTLOBJ_FLAG_FACING_LEFT) BgFxStartWideThunder(2, body->x - 0x2800, body->y, body->z - 0x1800, body->groundZ, 141);
                else BgFxStartWideThunder(2, body->x + 0x2800, body->y, body->z - 0x1800, body->groundZ, 141);

                break;
            }
        }

        if (work->stateTimer == 64) SetBattleZoom(15, 148, 0x10000, 0x12C00);

        if (work->stateTimer > 44 && !BgFxIsActive()) {
            work->state = 2;
            SetBattleZoom(15, 256, gBtlWork->x2, gBtlWork->y2);
            work->stateTimer = 0;
        } else work->stateTimer++;

        break;
    }

    AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_frd_jack_2(FrdJackWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;
    u8 angle;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);
    angle = work->rotation;

    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (angle == 0 && gBtlWork->scale == 256) {
        sclY = gBtlWork->scale;
        sclX = sclY;
        flags |= SPRITE_FLAG_HFLIP;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (angle != 0) {
        affine = AllocObjAffine(angle, sclX, sclY, 1);
    } else if (gBtlWork->scale == 256) {
        affine = NULL;
    } else if (gBtlWork->scale <= 255) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
        sx = sx + (SIN((u16)(angle + 128)) * 5 >> 5);
    } else {
        sx = sx - (SIN((u16)(angle + 128)) * 5 >> 5);
    }

    sy = sy + (-COS((u16)(angle + 128)) * 5 >> 5) - 40;
    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags, -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_frd_jack_3(FrdJackWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= ~BTL_FLAG_SUMMON_ACTIVE;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}
