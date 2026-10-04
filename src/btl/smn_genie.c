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

static const AnimDef sSmnGenieAnimDefs[2] = {
    { gGenie00Frames, gGenie00Anims, gGenie00Tiles, 0, { 0, 0, 0 } },
    { gGenie00Frames, gGenie00Anims, gGenie00Tiles, 1, { 0, 0, 0 } },
};

TaskDesc gTaskDescSmnGenie = {
    "task_smn_genie",
    (TaskInitFunc)task_smn_genie_0,
    (TaskUpdateFunc)task_smn_genie_1,
    (TaskDrawFunc)task_smn_genie_2,
    (TaskDestroyFunc)task_smn_genie_3,
    sizeof(SmnGenieWork),
};

void task_smn_genie_0(SmnGenieWork* work, SmnArgs* args) {
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

    if (obj->flags & BTLOBJ_FLAG_FACING_LEFT) {
        body->flags = (BTLOBJ_FLAG_FACING_LEFT | BTLOBJ_FLAG_LARGE_SHADOW);
        body->x = obj->originX + 0x3700;
    } else {
        body->flags = BTLOBJ_FLAG_LARGE_SHADOW;
        body->x = obj->originX - 0x3700;
    }

    body->y = obj->originY;
    body->z = obj->originZ - 0x2800;
    body->groundZ = obj->originZ;
    work->variant = args->variant;
    work->palette = LoadObjPalette(gGeniePalette, 32);
    AnimInit(&work->anim, NULL, NULL);
    AnimChangeWithDef(sSmnGenieAnimDefs, &work->anim, 0, 0, work->tiles);
    work->state = 0;
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
    BtlObj* p;
    s16 count;

    if (gBtlWork->flags & BTL_FLAG_VS_BATTLE) {
        if (work->mainSide != 0) {
            p = gRikuBtlWork->actor;
        } else {
            p = gBtlWork->actor;
        }

        if (p->hp <= 0) {
            return NULL;
        }

        return p;
    }

    count = 0;
    p = ListPoolFirst(&gBtlWork->pool);

    while (p != NULL) {
        if (!(p->flags & BTLOBJ_FLAG_UNHITTABLE)) {
            list[count] = p;
            count++;

            if (count > 9) {
                break;
            }
        }

        p = ListPoolNext(&p->node);
    }

    if (count == 0) {
        return NULL;
    }

    p = list[work->targetIndex % count];
    work->targetIndex++;
    return p;
}

void SmnGenieFollowTarget(SmnGenieWork* work) {
    BtlObj* body;
    BtlObj* obj;
    s32 tx;
    s32 ty;
    s32 zt;
    s32 v;
    s32 lim;

    obj = work->target;
    body = &work->body;

    if (obj == NULL) {
        return;
    }

    if (obj->x < body->x) {
        body->flags |= BTLOBJ_FLAG_FACING_LEFT;
    } else {
        body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
    }

    if (obj->x > 0x10000) {
        tx = obj->x - 0x3700;
    } else {
        tx = obj->x + 0x3700;
    }

    ty = obj->y;
    zt = body->groundZ - 0x200;
    v = (tx - body->x) >> 3;
    lim = work->speedX;

    if (v > lim) {
        v = lim;
        work->speedX = lim + 0x4C;
    } else if (v < -lim) {
        v = -lim;
        work->speedX = lim + 0x4C;
    } else {
        work->speedX = abs(v);
    }

    body->x += v;
    v = (ty - body->y) >> 3;
    lim = work->speedY;

    if (v > lim) {
        v = lim;
        work->speedY = lim + 0x4C;
    } else if (v < -lim) {
        v = -lim;
        work->speedY = lim + 0x4C;
    } else {
        work->speedY = abs(v);
    }

    body->y += v;
    body->z += (zt - gSineTable[(work->stateTimer * 2) & 0xFF] * 8 - body->z) >> 3;
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
    case 0:
        if ((s16)work->stateTimer == 0) {
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
    case 2:
        if ((s16)work->stateTimer == 0) {
            gBtlWork->flags |= BTL_FLAG_ENEMY_MOVE_ENABLED;
            AnimChangeWithDef(sSmnGenieAnimDefs, &work->anim, 0, 0, work->tiles);
        }

        height = ((u32)gSineTable[(work->stateTimer * 2) & 255] << 3) + 0xC00;
        body->z += (body->groundZ - height - body->z) >> 3;

        if ((s16)work->stateTimer > 10) {
            work->target = SmnGenieNextTarget(work);

            if (work->target == NULL || work->attacksLeft-- <= 0) {
                work->state = 1;
                work->stateTimer = 0;
            } else {
                work->state = 3;
                work->stateTimer = 0;
            }
        } else {
            work->stateTimer++;
        }

        break;
    case 3:
        AnimChangeWithDef(sSmnGenieAnimDefs, &work->anim, 0, 0, work->tiles);
        SmnGenieFollowTarget(work);

        if ((s16)work->stateTimer > 40) {
            work->fired = 0;

            switch ((u16)(GetRandom() % 3)) {
            case 0:
                work->state = 4;
                break;
            case 1:
                work->state = 5;
                break;
            case 2:
            default:
                work->state = 6;
                break;
            }

            gBtlWork->flags &= ~BTL_FLAG_ENEMY_MOVE_ENABLED;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    case 4:
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
            work->state = 2;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    case 5:
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
            work->state = 2;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    case 6:
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
            work->state = 2;
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
