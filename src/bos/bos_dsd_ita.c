/**
 * bos_dsd_ita.c
 * Darkside Boss Platform and Rocks
 */

#include "bos2.h"
#include "sprites_bos2.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "engine_math.h"
#include "obj.h"
#include "obj_api.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"

void task_bos_dsd_ita_0(DsdItaWork* work, void* arg) {
    work->dsd = arg;
    work->moveSteps = 0x1E;
    work->lifeTimer = 0;
    work->offTimer = 0;
    work->state = 0;
    work->x = 0x12C00;
    work->y = 0x17C00;
    work->z = -0x7800;
    work->vz = 0x100;
    work->gravity = 0x19;
    work->flags = 0;
    work->dipStep = 0;
    work->dipOffset = 0;
    ColliderInit(&work->collider, 7, 0x20, 3);
    ColliderSetPosition(&work->collider, work->x, work->y, work->z);
    work->gfx = gBosDsdItaFrames[0];
    work->gfx2 = gBosDsdItaShadowFrames[0];
}

u8 task_bos_dsd_ita_1(DsdItaWork* work) {
    BtlObj* a = &work->dsd->body[1];

    BosDsdItaUpdateRider(work);

    switch (work->state) {
    case 0:
        if (work->moveSteps > 0) {
            ApproachValue(&work->x, 0x1400, work->moveSteps);
            ApproachValue(&work->z, -0x1400, work->moveSteps);
            work->moveSteps--;
        } else {
            work->state = 1;
        }

        break;
    case 1:
        if (work->dsd->flags & DSD_FLAG_PLAYER_ON_PLATFORM) {
            work->state = 2;
        }

        BosDsdItaUpdateLifetime(work);
        break;
    case 2:
        if (work->dsd->flags & DSD_FLAG_PLAYER_ON_PLATFORM) {
            BosDsdItaMoveToward(&work->x, a->x - 12800);
            BosDsdItaMoveToward(&work->y, a->y);
            BosDsdItaMoveToward(&work->z, a->z + 0x500);
        } else if (work->offTimer > 49) {
            work->state = 3;
        } else {
            work->offTimer++;
        }

        BosDsdItaUpdateLifetime(work);
        break;
    case 3:
        if (work->z < 0) {
            work->z += work->vz;
            work->vz += work->gravity;
        } else {
            work->z = 0;
        }

        if (work->dsd->flags & DSD_FLAG_PLAYER_ON_PLATFORM) {
            work->offTimer = 0;
            work->state = 2;
        }

        BosDsdItaUpdateLifetime(work);
        break;
    case 4:
        if (work->moveSteps > 0) {
            ApproachValue(&work->x, -0x5000, work->moveSteps);
            ApproachValue(&work->z, -0x1400, work->moveSteps);
            work->moveSteps--;
        } else {
            work->state++;
        }

        break;
    default:
        work->dsd->flags &= ~DSD_FLAG_PLATFORM_ACTIVE;
        return 0;
    }

    ColliderSetPosition(&work->collider, work->x, work->y, work->z);

    return 1;
}

void task_bos_dsd_ita_2(DsdItaWork* work) {
    u16 pal;
    u16 prio;
    ObjAffine* affine;
    s32 scale;
    s32 flag;
    s16 x;
    s16 y;

    if (work->dsd->flags & DSD_FLAG_PLAYER_ON_PLATFORM) {
        pal = 0x800;
        prio = -4100 - ((work->y - 0x4000) >> 8) * 4;
    } else {
        pal = GetBattleSpritePriorityFlags(work->y);
        prio = -4102 - (work->y >> 8) * 4;
    }

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, work->gfx, work->dsd->tiles2, work->dsd->palette2, NULL, pal, prio);

    if (work->z >= 0 && gBtlWork->scale == 0x100) {
        affine = NULL;
    } else {
        scale = 0x100 - -work->z / 128;

        if (scale <= 0x7F) {
            scale = 0x80;
        }

        flag = 0;

        if (scale > 0x100) {
            flag = 1;
        }

        affine = AllocObjAffine(0, scale, scale, flag);
    }

    WorldToScreen(&x, &y, work->x, work->y, 0);
    DrawSprite(x, y, work->gfx2, work->dsd->tiles2, work->dsd->palette3, affine, SPRITE_PRIORITY(3), 0xFFF0);
}

void task_bos_dsd_ita_3(DsdItaWork* work) {
    ColliderUnregister(&work->collider);
}

void BosDsdItaUpdateRider(DsdItaWork* work) {
    s32 v;
    s16 k;

    if (gBtlWork->platform == &work->collider) {
        v = work->dsd->flags & DSD_FLAG_PLAYER_ON_PLATFORM;

        if (v == 0) {
            work->flags |= DSD_ITA_FLAG_SINKING;
            work->dsd->flags |= DSD_FLAG_PLAYER_ON_PLATFORM;
            work->dipStep = v;
        }
    } else if (work->dsd->flags & DSD_FLAG_PLAYER_ON_PLATFORM) {
        work->dsd->flags &= ~DSD_FLAG_PLAYER_ON_PLATFORM;
        work->flags |= DSD_ITA_FLAG_RISING;
        work->dipStep = 0;
    }

    if (work->flags & DSD_ITA_FLAG_RISING) {
        k = gBosDsdItaDipSteps[work->dipStep];
        work->dipOffset -= k << 8;

        if (k == 0) {
            work->flags &= ~DSD_ITA_FLAG_RISING;
            work->dipOffset = 0;
        } else {
            work->dipStep++;
        }
    } else if (work->flags & DSD_ITA_FLAG_SINKING) {
        k = gBosDsdItaDipSteps[work->dipStep];
        work->dipOffset += k << 8;

        if (k == 0) {
            work->flags &= ~DSD_ITA_FLAG_SINKING;
        } else {
            work->dipStep++;
        }
    }
}

void BosDsdItaUpdateLifetime(DsdItaWork* work) {
    if ((s16)work->lifeTimer >= 600) {
        work->moveSteps = 30;
        work->state = 4;
    } else {
        work->lifeTimer++;
    }

    if (work->dsd->state == 11) {
        work->state = 4;
    }
}

void BosDsdItaMoveToward(s32* value, s32 target) {
    s32 cur;
    s32 delta;

    cur = *value;
    delta = (target - cur) >> 1;

    if (target > cur) {
        if (delta > 0x4FF) {
            delta = 0x500;
        }
    } else if (target < cur) {
        if (delta <= -0x500) {
            delta = -0x500;
        }
    } else {
        return;
    }

    *value = cur + delta;
}

void task_bos_dsd_rock_0(DsdRockWork* work, DsdWork* arg) {
    s32 r;
    u8 ang;

    work->dsd = arg;
    work->front = GetRandom() % 2;
    work->gfx = gBosDsdItaFrames[GetRandom() % 3 + 1];

    if (work->dsd->driftX > 0) {
        if (work->front != 0) {
            r = GetRandom() % 0x301 + 0x700;
            ang = GetRandom() % 13 + 58;
            work->x = gBtlWork->viewX - 0x8800;
            work->y = (gBtlWork->yMax - 140) << 8;
        } else {
            r = GetRandom() % 0x201 + 0x400;
            ang = -(GetRandom() % 13 + 58);
            work->x = gBtlWork->viewX + 0x8800;
            work->y = (gBtlWork->yMin - 140) << 8;
        }
    } else {
        if (work->front != 0) {
            r = GetRandom() % 0x301 + 0x700;
            ang = -(GetRandom() % 13 + 58);
            work->x = gBtlWork->viewX + 0x8800;
            work->y = (gBtlWork->yMax - 140) << 8;
        } else {
            r = GetRandom() % 0x201 + 0x400;
            ang = GetRandom() % 13 + 58;
            work->x = gBtlWork->viewX - 0x8800;
            work->y = (gBtlWork->yMin - 140) << 8;
        }
    }

    work->z = (GetRandom() % 101) << 8;
    work->vx = gSineTable[ang] * r >> 8;
    work->vz = -gSineTable[ang + 0x40] * r >> 8;
}

u8 task_bos_dsd_rock_1(DsdRockWork* work) {
    if ((work->dsd->flags & DSD_FLAG_DRIFT_CHANGED) != 0) {
        work->vx = -work->vx;
        work->vz = -work->vz;
    } else {
        work->x += work->vx;
        work->z += work->vz;
    }

    if (work->x > gBtlWork->viewX + 0x8800 || work->x < gBtlWork->viewX - 0x8800) {
        return 0;
    }

    return 1;
}

void task_bos_dsd_rock_2(DsdRockWork* work) {
    ObjAffine* affine;
    s32 h;
    s32 prio;
    s16 x;
    s16 y;

    if (work->front != 0) {
        affine = NULL;
        h = 10;
        prio = 0x400;
    } else {
        affine = AllocObjAffine(0, 0x59, 0x59, 0);
        h = 0xFFF5;
        prio = 0xC00;
    }

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, work->gfx, work->dsd->tiles2, work->dsd->palette2, affine, prio, h);
}

void task_bos_dsd_rock_3() {
}

const s16 gBosDsdItaDipSteps[6] = { 3, 2, 1, 1, 0, 0 };

TaskDesc gTaskDescBosDsdIta = {
    "task_bos_dsd_ita",
    (TaskInitFunc)task_bos_dsd_ita_0,
    (TaskUpdateFunc)task_bos_dsd_ita_1,
    (TaskDrawFunc)task_bos_dsd_ita_2,
    (TaskDestroyFunc)task_bos_dsd_ita_3,
    sizeof(DsdItaWork),
};

TaskDesc gTaskDescBosDsdRock = {
    "task_bos_dsd_rock",
    (TaskInitFunc)task_bos_dsd_rock_0,
    (TaskUpdateFunc)task_bos_dsd_rock_1,
    (TaskDrawFunc)task_bos_dsd_rock_2,
    (TaskDestroyFunc)task_bos_dsd_rock_3,
    sizeof(DsdRockWork),
};
