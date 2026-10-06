/**
 * smn_genie.c
 * Genie Summon
 */

#include "task_descriptors.h"
#include "display.h"
#include "smn.h"
#include "anim.h"
#include "sprites_smn.h"
#include "btl_api.h"
#include "fade.h"
#include "songs.h"
#include <stdlib.h>
#include "smn_tasks.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_effect.h"
#include "engine_math.h"
#include "listpool.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "sprite_palettes.h"

static const AnimDef sSmnGenieAnimDefs[2] = {
    { gGenie00Frames, gGenie00Anims, gGenie00Tiles, 0 },
    { gGenie00Frames, gGenie00Anims, gGenie00Tiles, 1 },
};

TaskDesc gTaskDescSmnGenie = {
    "task_smn_genie",
    (TaskInitFunc)task_smn_genie_0,
    (TaskUpdateFunc)task_smn_genie_1,
    (TaskDrawFunc)task_smn_genie_2,
    (TaskDestroyFunc)task_smn_genie_3,
    sizeof(SmnGenieWork),
};

enum SmnGenieState {
    SMN_GENIE_STATE_APPEAR,
    SMN_GENIE_STATE_VANISH,
    SMN_GENIE_STATE_IDLE,
    SMN_GENIE_STATE_FOLLOW,
    SMN_GENIE_STATE_CAST_THUNDER,
    SMN_GENIE_STATE_CAST_GRAVITY,
    SMN_GENIE_STATE_CAST_STOP
};

void task_smn_genie_0(SmnGenieWork* work, SmnArgs* args) {
    BtlObj* body;
    BtlObj* actor;

    body = &work->body;

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= BTL_FLAG_SUMMON_ACTIVE;
        actor = gBtlWork->actor;
        work->tiles = gBtlWork->tiles;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= BTL_FLAG_SUMMON_ACTIVE;
        actor = gRikuBtlWork->actor;
        work->tiles = gRikuBtlWork->tiles;
    }

    if (actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
        body->flags = (BTLOBJ_FLAG_FACING_LEFT | BTLOBJ_FLAG_LARGE_SHADOW);
        body->x = actor->originX + 0x3700;
    } else {
        body->flags = BTLOBJ_FLAG_LARGE_SHADOW;
        body->x = actor->originX - 0x3700;
    }

    body->y = actor->originY;
    body->z = actor->originZ - 0x2800;
    body->groundZ = actor->originZ;
    work->variant = args->variant;
    work->palette = LoadObjPalette(gGeniePalette, 32);
    AnimInit(&work->anim, NULL, NULL);
    AnimChangeWithDef(sSmnGenieAnimDefs, &work->anim, 0, 0, work->tiles);
    work->state = SMN_GENIE_STATE_APPEAR;
    work->stateTimer = 0;
    work->steps = 0;
    work->scale = 10;
    work->animating = 0;
    work->speedX = 0;
    work->speedY = 0;

    switch (args->variant) {
    case 0:
        work->attacksLeft = 1;
        break;
    case 1:
        work->attacksLeft = 2;
        break;
    case 2:
    default:
        work->attacksLeft = 3;
        break;
    }

    work->targetIndex = 0;
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

BtlObj* SmnGenieNextTarget(SmnGenieWork* work) {
    BtlObj* list[10];
    BtlObj* obj;
    s16 count;

    if (gBtlWork->flags & BTL_FLAG_VS_BATTLE) {
        if (work->mainSide != 0) {
            obj = gRikuBtlWork->actor;
        } else {
            obj = gBtlWork->actor;
        }

        if (obj->hp <= 0) {
            return NULL;
        }

        return obj;
    }

    count = 0;
    obj = ListPoolFirst(&gBtlWork->pool);

    while (obj != NULL) {
        if (!(obj->flags & BTLOBJ_FLAG_UNHITTABLE)) {
            list[count] = obj;
            count++;

            if (count > 9) {
                break;
            }
        }

        obj = ListPoolNext(&obj->node);
    }

    if (count == 0) {
        return NULL;
    }

    obj = list[work->targetIndex % count];
    work->targetIndex++;
    return obj;
}

void SmnGenieFollowTarget(SmnGenieWork* work) {
    BtlObj* body;
    BtlObj* target;
    s32 x;
    s32 y;
    s32 z;
    s32 delta;
    s32 speed;

    target = work->target;
    body = &work->body;

    if (target == NULL) {
        return;
    }

    if (target->x < body->x) {
        body->flags |= BTLOBJ_FLAG_FACING_LEFT;
    } else {
        body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
    }

    if (target->x > 0x10000) {
        x = target->x - 0x3700;
    } else {
        x = target->x + 0x3700;
    }

    y = target->y;
    z = body->groundZ - 0x200;
    delta = (x - body->x) >> 3;
    speed = work->speedX;

    if (delta > speed) {
        delta = speed;
        work->speedX = speed + 0x4C;
    } else if (delta < -speed) {
        delta = -speed;
        work->speedX = speed + 0x4C;
    } else {
        work->speedX = abs(delta);
    }

    body->x += delta;
    delta = (y - body->y) >> 3;
    speed = work->speedY;

    if (delta > speed) {
        delta = speed;
        work->speedY = speed + 0x4C;
    } else if (delta < -speed) {
        delta = -speed;
        work->speedY = speed + 0x4C;
    } else {
        work->speedY = abs(delta);
    }

    body->y += delta;
    body->z += (z - SIN(work->stateTimer * 2) * 8 - body->z) >> 3;
}

u8 task_smn_genie_1(SmnGenieWork* work) {
    BtlObj* body = &work->body;
    s32 height;
    s32 x;
    s32 y;
    s32 z;

    if ((work->mainSide != 0 ? gBtlWork->flags : gRikuBtlWork->flags) & BTL_FLAG_DISMISS_SUMMONS) {
        return 0;
    }

    BtlMapFollowPosition(body->x, body->y, body->z);

    if (gBtlWork->boundsCallback != NULL) {
        gBtlWork->boundsCallback(&body->x, &body->y, &body->z, &body->groundZ);

        if (body->z > body->groundZ) {
            body->z = body->groundZ;
        }
    }

    switch (work->state) {
    case SMN_GENIE_STATE_APPEAR:
        if ((s16)work->stateTimer == 0) {
            work->steps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_UP);
        }

        ApproachValue(&work->scale, 256, work->steps);

        if (work->steps <= 0) {
            work->state = SMN_GENIE_STATE_IDLE;
            work->stateTimer = 0;
            work->animating = 1;
        } else {
            work->stateTimer++;
            work->steps--;
        }

        break;
    case SMN_GENIE_STATE_VANISH:
        if ((s16)work->stateTimer == 0) {
            AnimChangeWithDef(sSmnGenieAnimDefs, &work->anim, 0, 0, work->tiles);
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
    case SMN_GENIE_STATE_IDLE:
        if ((s16)work->stateTimer == 0) {
            gBtlWork->flags |= BTL_FLAG_ENEMY_MOVE_ENABLED;
            AnimChangeWithDef(sSmnGenieAnimDefs, &work->anim, 0, 0, work->tiles);
        }

        height = ((u32)SIN(work->stateTimer * 2) << 3) + 0xC00;
        body->z += (body->groundZ - height - body->z) >> 3;

        if ((s16)work->stateTimer > 10) {
            work->target = SmnGenieNextTarget(work);

            if (work->target == NULL || work->attacksLeft-- <= 0) {
                work->state = SMN_GENIE_STATE_VANISH;
                work->stateTimer = 0;
            } else {
                work->state = SMN_GENIE_STATE_FOLLOW;
                work->stateTimer = 0;
            }
        } else {
            work->stateTimer++;
        }

        break;
    case SMN_GENIE_STATE_FOLLOW:
        AnimChangeWithDef(sSmnGenieAnimDefs, &work->anim, 0, 0, work->tiles);
        SmnGenieFollowTarget(work);

        if ((s16)work->stateTimer > 40) {
            work->fired = 0;

            switch ((u16)(GetRandom() % 3)) {
            case 0:
                work->state = SMN_GENIE_STATE_CAST_THUNDER;
                break;
            case 1:
                work->state = SMN_GENIE_STATE_CAST_GRAVITY;
                break;
            case 2:
            default:
                work->state = SMN_GENIE_STATE_CAST_STOP;
                break;
            }

            gBtlWork->flags &= ~BTL_FLAG_ENEMY_MOVE_ENABLED;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    case SMN_GENIE_STATE_CAST_THUNDER:
        if ((s16)work->stateTimer == 0) {
            m4aSongNumStart(SONG_VO_GE_ATTACK00);
            AnimChangeWithDef(sSmnGenieAnimDefs, &work->anim, 1, 0, work->tiles);
        }

        if (!work->fired) {
            SmnGenieFollowTarget(work);

            if (AnimGetFrame(&work->anim) == 6 && work->anim.timer == 0) {
                if (work->target != NULL) {
                    x = work->target->x;
                    y = work->target->y;
                    z = 0;
                } else {
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
                        x = body->x - 0x5000;
                    } else {
                        x = body->x + 0x5000;
                    }

                    y = body->y;
                    z = 0;
                }

                if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    BgFxStartThunder(1, body->x - 0xD00, body->y, body->z - 0x6E00, x, y, z, 146);
                } else {
                    BgFxStartThunder(1, body->x + 0xD00, body->y, body->z - 0x6E00, x, y, z, 146);
                }

                work->fired = 1;
            }
        } else {
            BgAnimIsStopped();
        }

        if (work->fired && !BgFxIsActive()) {
            work->state = SMN_GENIE_STATE_IDLE;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    case SMN_GENIE_STATE_CAST_GRAVITY:
        if ((s16)work->stateTimer == 0) {
            m4aSongNumStart(SONG_VO_GE_ATTACK01);
            AnimChangeWithDef(sSmnGenieAnimDefs, &work->anim, 1, 0, work->tiles);
        }

        if (!work->fired) {
            SmnGenieFollowTarget(work);

            if (AnimGetFrame(&work->anim) == 6 && work->anim.timer == 0) {
                if (work->target != NULL) {
                    x = work->target->x;
                    y = work->target->y;
                    z = 0;
                } else {
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
                        x = body->x - 0x5000;
                    } else {
                        x = body->x + 0x5000;
                    }

                    y = body->y;
                    z = 0;
                }

                if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    BgFxStartGravity(1, body->x - 0xD00, body->y, body->z - 0x6E00, x, y, z, 1, 148);
                } else {
                    BgFxStartGravity(1, body->x + 0xD00, body->y, body->z - 0x6E00, x, y, z, 0, 148);
                }

                work->fired = 1;
                FadeStartOut(FADE_MODE_GRAY, 8);
            }
        } else {
            BgAnimIsStopped();
        }

        if (work->fired && !BgFxIsActive()) {
            FadeStartIn(FADE_MODE_GRAY, 8);
            work->state = SMN_GENIE_STATE_IDLE;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    case SMN_GENIE_STATE_CAST_STOP:
        if ((s16)work->stateTimer == 0) {
            AnimChangeWithDef(sSmnGenieAnimDefs, &work->anim, 1, 0, work->tiles);
            m4aSongNumStart(SONG_VO_GE_ATTACK02);
        }

        if (!work->fired) {
            SmnGenieFollowTarget(work);

            if (AnimIsFinished(&work->anim)) {
                if (work->target != NULL) {
                    x = work->target->x;
                    y = work->target->y;
                    z = work->target->z - work->target->centerHeight * 256;
                } else {
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
                        x = body->x - 0x5000;
                    } else {
                        x = body->x + 0x5000;
                    }

                    y = body->y;
                    z = -0x1000;
                }

                BgFxStartStop(1, x, y, z, 147);
                work->fired = 1;
            }
        }

        if (work->fired && !BgFxIsActive()) {
            work->state = SMN_GENIE_STATE_IDLE;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    }

    ClampBattlePosition(&body->x, &body->y, 0, -10);

    if (work->animating) {
        AnimUpdate(&work->anim);
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_smn_genie_2(SmnGenieWork* work) {
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

void task_smn_genie_3(SmnGenieWork* work) {
    gBtlWork->flags |= BTL_FLAG_ENEMY_MOVE_ENABLED;

    if (work->mainSide != 0) {
        gBtlWork->flags &= ~BTL_FLAG_SUMMON_ACTIVE;
    } else {
        gRikuBtlWork->flags &= ~BTL_FLAG_SUMMON_ACTIVE;
    }

    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}
