/**
 * bos_tm_body.c
 * Trickmaster Boss Body
 */

#include "macros.h"
#include "boss_tm.h"
#include "sprites_boss_tm.h"
#include "card_api.h"
#include "engine_math.h"
#include "system_state.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "obj.h"
#include "obj_api.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"
#include "sprite_palettes.h"

BtlObj gBosTmBodyObjCopy EWRAM_COMMON(16);

static const EmyKind sBosTmEmyKind = { 34, 1300, 28, 14, 20, 40, EMY_KIND_FLAG_NO_COLLIDER };

static u8 sBosTmBodyAngles[11] = { 0, 2, 5, 15, 18, 20, 20, 18, 15, 5, 2 };

static s16 sBosTmBodyIdleZ[8] = { 8, -8, -12, 12, 8, -8, -12, 12 };

static s16 sBosTmBodyWalkZ[10] = { -11, -8, -10, 10, 19, -11, -8, -10, 10, 19 };

static TmBodyStep sBosTmBodyRecoilSteps[3] = {
    { -8, 0, 246, { 0, 0, 0 }, -3, 2, 246, { 0, 0, 0 }, -6, 2, { 0, 0 }, 0, -6, 2, { 0, 0 }, 0 },
    { -6, 8, 246, { 0, 0, 0 }, -2, 7, 246, { 0, 0, 0 }, -6, 6, { 0, 0 }, 0, -6, 6, { 0, 0 }, 0 },
    { -4, 0, 246, { 0, 0, 0 }, 0, 0, 246, { 0, 0, 0 }, -3, 0, { 0, 0 }, 0, -3, 0, { 0, 0 }, 0 },
};

TmBodyStep gUnk_09EF1DE8 = { 0, 0, 0, { 0, 0, 0 }, 0, 0, 0, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0, 0, 0, { 0, 0 }, 0 };

static s16 sBosTmBodyRecoilZ[3] = { 15, 6, 0 };

s16 gUnk_09EF1E0E = -8;

s16 gUnk_09EF1E10 = -20;

s16 gUnk_09EF1E12 = -28;

static TmBodyStep sBosTmBodyThrowSteps[16] = {
    { 2, -11, 15, { 0, 0, 0 }, 0, -11, 5, { 0, 0, 0 }, 0, -7, { 0, 0 }, 0, 0, -7, { 0, 0 }, 0 },
    { 7, -12, 15, { 0, 0, 0 }, 5, -12, 5, { 0, 0, 0 }, 4, -8, { 0, 0 }, 1, 4, -8, { 0, 0 }, 1 },
    { 1, -6, 15, { 0, 0, 0 }, -2, -6, 5, { 0, 0, 0 }, 5, -5, { 0, 0 }, 2, 5, -7, { 0, 0 }, 2 },
    { 4, 2, 15, { 0, 0, 0 }, 1, 0, 5, { 0, 0, 0 }, 1, 2, { 0, 0 }, 3, 1, 2, { 0, 0 }, 3 },
    { -4, -2, 241, { 0, 0, 0 }, -1, 0, 251, { 0, 0, 0 }, -6, -2, { 0, 0 }, 2, -6, -2, { 0, 0 }, 2 },
    { -2, 0, 241, { 0, 0, 0 }, -1, -1, 251, { 0, 0, 0 }, 0, -4, { 0, 0 }, 2, 0, -4, { 0, 0 }, 2 },
    { -6, -1, 241, { 0, 0, 0 }, -2, 0, 251, { 0, 0, 0 }, -4, -2, { 0, 0 }, 2, -4, -2, { 0, 0 }, 2 },
    { -2, 1, 241, { 0, 0, 0 }, 0, 2, 251, { 0, 0, 0 }, 0, 2, { 0, 0 }, 1, 0, 2, { 0, 0 }, 1 },
    { -6, 5, 248, { 0, 0, 0 }, 0, 6, 248, { 0, 0, 0 }, -2, 8, { 0, 0 }, 1, -2, 8, { 0, 0 }, 1 },
    { -5, 14, 248, { 0, 0, 0 }, -3, 14, 248, { 0, 0, 0 }, -7, 13, { 0, 0 }, 1, -7, 13, { 0, 0 }, 1 },
    { -4, 12, 248, { 0, 0, 0 }, -1, 11, 248, { 0, 0, 0 }, -2, 11, { 0, 0 }, 0, -2, 11, { 0, 0 }, 0 },
    { -6, 13, 248, { 0, 0, 0 }, -2, 9, 248, { 0, 0, 0 }, -5, 9, { 0, 0 }, 0, -5, 9, { 0, 0 }, 0 },
    { 1, 6, 248, { 0, 0, 0 }, 1, 10, 248, { 0, 0, 0 }, -1, 11, { 0, 0 }, 0, -1, 11, { 0, 0 }, 0 },
    { 0, -2, 8, { 0, 0, 0 }, -1, 0, 10, { 0, 0, 0 }, 1, -1, { 0, 0 }, 0, 1, -1, { 0, 0 }, 0 },
    { 7, -11, 8, { 0, 0, 0 }, 2, -12, 10, { 0, 0, 0 }, 7, -14, { 0, 0 }, 0, 7, -14, { 0, 0 }, 0 },
    { -4, -8, 9, { 0, 0, 0 }, 4, -9, 10, { 0, 0, 0 }, 5, -7, { 0, 0 }, 0, 5, -7, { 0, 0 }, 0 },
};

TmBodyStep gUnk_09EF2014 = { 0, 0, 0, { 0, 0, 0 }, 0, 0, 0, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0, 0, 0, { 0, 0 }, 0 };

static TmBodyStep sBosTmBodySpinSteps[9] = {
    { 0, 2, 0, { 0, 0, 0 }, 0, 2, 0, { 0, 0, 0 }, 0, 2, { 0, 0 }, 0, 0, 2, { 0, 0 }, 0 },
    { -8, 6, 246, { 0, 0, 0 }, -3, 7, 246, { 0, 0, 0 }, -6, 7, { 0, 0 }, 0, -6, 7, { 0, 0 }, 0 },
    { -6, 8, 246, { 0, 0, 0 }, -2, 9, 246, { 0, 0, 0 }, -6, 9, { 0, 0 }, 0, -6, 9, { 0, 0 }, 0 },
    { -4, 0, 246, { 0, 0, 0 }, 0, 0, 246, { 0, 0, 0 }, -3, 0, { 0, 0 }, 0, -3, 0, { 0, 0 }, 0 },
    { 2, -2, 8, { 0, 0, 0 }, -1, 0, 10, { 0, 0, 0 }, 1, -1, { 0, 0 }, 0, 1, -1, { 0, 0 }, 0 },
    { 9, -11, 8, { 0, 0, 0 }, 2, -12, 10, { 0, 0, 0 }, 7, -14, { 0, 0 }, 0, 7, -14, { 0, 0 }, 0 },
    { 6, -8, 9, { 0, 0, 0 }, 4, -9, 10, { 0, 0, 0 }, 5, -7, { 0, 0 }, 0, 5, -7, { 0, 0 }, 0 },
    { 2, -11, 15, { 0, 0, 0 }, 0, -11, 5, { 0, 0, 0 }, 0, -7, { 0, 0 }, 1, 0, -7, { 0, 0 }, 1 },
    { 7, -12, 15, { 0, 0, 0 }, 5, -12, 5, { 0, 0, 0 }, 4, -8, { 0, 0 }, 2, 4, -8, { 0, 0 }, 2 },
};

TmBodyStep gUnk_09EF2154 = { 0, 0, 0, { 0, 0, 0 }, 0, 0, 0, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0, 0, 0, { 0, 0 }, 0 };

TmBodyStep gUnk_09EF2174 = { 0, 0, 0, { 0, 0, 0 }, 0, 0, 0, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0, 0, 0, { 0, 0 }, 0 };

static s8 sBosTmActionChoices[4] = { 1, 3, 9, 4 };

TaskDesc gTaskDescBosTmBody = {
    "task_bos_tm_body",
    (TaskInitFunc)task_bos_tm_body_0,
    (TaskUpdateFunc)task_bos_tm_body_1,
    (TaskDrawFunc)task_bos_tm_body_2,
    (TaskDestroyFunc)task_bos_tm_body_3,
    sizeof(TmBodyWork),
};

void BosTmBodyResetTimers(TmBodyWork* work) {
    work->tm->stepTimer = 0;
    work->tm->step = 0;
    work->tm->stateTimer = 0;
}

void BosTmBodyInitEnemy(BtlObj* p, s16 a, s16 b, s16 c) {
    p->x = a << 8;
    p->y = b << 8;
    p->z = (c << 8) + 0x1900;
    InitEnemyBtlObj(p, &sBosTmEmyKind, p->x, p->y, p->z);
    p->radiusX = 14;
    p->radiusY = 40;
    p->height = 28;
    p->flags |= 0x400;
    p->flags |= BTLOBJ_FLAG_FACING_LEFT;
}

void BosTmBodySetObjPos(BtlObj* p, s16 a, s16 b, s16 c) {
    p->x = a << 8;
    p->y = b << 8;
    p->z = c << 8;
}

void BosTmBodyReleaseEnemy(BtlObj* a) {
    ReleaseEnemyBtlObj(a);
}

void BosTmBodyUpdateAngle(TmBodyWork* work) {
    work->angleTimer++;

    if (work->angleTimer > 5) {
        work->angleTimer = 0;
        work->angleStep++;

        if (work->angleStep > 10) {
            work->angleStep = 0;
        }

        work->angle = sBosTmBodyAngles[work->angleStep];
    }
}

void BosTmBodyPlaceParts(TmBodyWork* work) {
    if (work->tm->flags & TM_FLAG_FACING_LEFT) {
        work->body.x = work->tm->x2 + 0x400;
        work->body2.x = work->tm->x2;
        work->body3.x = work->tm->x2 + 0xC00;
        work->body4.x = work->tm->x2 - 0x100;
    } else {
        work->body.x = work->tm->x2 - 0x400;
        work->body2.x = work->tm->x2;
        work->body3.x = work->tm->x2 - 0xC00;
        work->body4.x = work->tm->x2 + 0x100;
    }

    work->body.y = work->tm->y2;
    work->body2.y = work->tm->y2;
    work->body3.y = work->tm->y2 + 0x100;
    work->body4.y = work->tm->y2 - 0x400;
    work->body.z = work->tm->z2 - 0x2200;
    work->body2.z = work->tm->z2 + 0x900;
    work->body3.z = work->tm->z2 - 0x2100;
    work->body4.z = work->tm->z2 - 0x1E00;
}

void BosTmBodyResetPose(TmBodyWork* work) {
    work->angle = 0;
    work->angle2 = 0;
    work->gfx3 = gUnk_09EF397C[0];
    work->gfx4 = gUnk_09EF3960[0];
    work->tm->x2 = work->tm->baseX;
    work->tm->y2 = work->tm->baseY;
    work->tm->z2 = work->tm->baseZ;
    BosTmBodyPlaceParts(work);
}

void BosTmBodySetDefeatPose(TmBodyWork* work) {
    TmWork* src;
    s32 dz;

    work->angle = 226;
    work->angle2 = 226;
    work->gfx3 = gUnk_09EF397C[0];
    work->gfx4 = gUnk_09EF3960[0];
    dz = 0xF00;
    src = work->tm;

    if (src->flags & TM_FLAG_FACING_LEFT) {
        work->tm->x2 = work->tm->baseX - 0xA00;
        work->tm->y2 = work->tm->baseY;
        work->tm->z2 = work->tm->baseZ + dz;
        work->body.x = work->tm->baseX - 0xF00;
        work->body2.x = work->tm->x2 + 0x500;
        work->body3.x = work->tm->x2 + 0x400;
        work->body4.x = work->tm->x2 - 0x900;
    } else {
        work->tm->x2 = work->tm->baseX + 0xA00;
        work->tm->y2 = work->tm->baseY;
        work->tm->z2 = work->tm->baseZ + 0xF00;
        work->body.x = work->tm->baseX + 0xF00;
        work->body2.x = work->tm->x2 - 0x500;
        work->body3.x = work->tm->x2 - 0x400;
        work->body4.x = work->tm->x2 + 0x900;
    }

    work->body.z = work->tm->z2 - 0x1F00;
    work->body2.z = work->tm->z2 + 0xE00;
    work->body3.z = work->tm->z2 - 0x1F00;
    work->body4.z = work->tm->z2 - 0x1C00;
}

void BosTmBodySetBreakPose(TmBodyWork* work) {
    work->angle = 30;
    work->angle2 = 10;
    work->gfx3 = gUnk_09EF397C[0];
    work->gfx4 = gUnk_09EF3960[0];

    if (work->tm->flags & TM_FLAG_FACING_LEFT) {
        work->tm->x2 = work->tm->baseX + 0xA00;
        work->tm->y2 = work->tm->baseY;
        work->tm->z2 = work->tm->baseZ + 0xF00;
        work->body.x = work->tm->baseX + 0xB00;
        work->body2.x = work->tm->x2 - 0x500;
        work->body3.x = work->tm->x2 + 0x900;
        work->body4.x = work->tm->x2 - 0x400;
    } else {
        work->tm->x2 = work->tm->baseX - 0xA00;
        work->tm->y2 = work->tm->baseY;
        work->tm->z2 = work->tm->baseZ + 0xF00;
        work->body.x = work->tm->baseX - 0xB00;
        work->body2.x = work->tm->x2 + 0x500;
        work->body3.x = work->tm->x2 - 0x900;
        work->body4.x = work->tm->x2 + 0x400;
    }

    work->body.z = work->tm->z2 - 0x2200;
    work->body2.z = work->tm->z2 + 0x900;
    work->body3.z = work->tm->z2 - 0x1F00;
    work->body4.z = work->tm->z2 - 0x1C00;
}

void BosTmBodyApplyThrowStep(TmBodyWork* work, s16 a) {
    if (work->tm->flags & TM_FLAG_FACING_LEFT) {
        work->angle += sBosTmBodyThrowSteps[a].dAngle;
        work->angle2 += sBosTmBodyThrowSteps[a].dAngle2;
        work->body.x += sBosTmBodyThrowSteps[a].dx << 8;
        work->body2.x += sBosTmBodyThrowSteps[a].dx2 << 8;
        work->body3.x += sBosTmBodyThrowSteps[a].dx3 << 8;
        work->body4.x += sBosTmBodyThrowSteps[a].dx4 << 8;
        work->tm->x2 += sBosTmBodyThrowSteps[a].dx3 << 8;
    } else {
        work->angle += sBosTmBodyThrowSteps[a].dAngle;
        work->angle2 += sBosTmBodyThrowSteps[a].dAngle2;
        work->body.x -= sBosTmBodyThrowSteps[a].dx << 8;
        work->body2.x -= sBosTmBodyThrowSteps[a].dx2 << 8;
        work->body3.x -= sBosTmBodyThrowSteps[a].dx3 << 8;
        work->body4.x -= sBosTmBodyThrowSteps[a].dx4 << 8;
        work->tm->x2 -= sBosTmBodyThrowSteps[a].dx3 << 8;
    }

    work->body.z += sBosTmBodyThrowSteps[a].dz << 8;
    work->body2.z += sBosTmBodyThrowSteps[a].dz2 << 8;
    work->body3.z += sBosTmBodyThrowSteps[a].dz3 << 8;
    work->body4.z += sBosTmBodyThrowSteps[a].dz4 << 8;
    work->tm->z2 += sBosTmBodyThrowSteps[a].dz2 << 8;
    work->gfx3 = gUnk_09EF397C[sBosTmBodyThrowSteps[a].gfx3Index];
    work->gfx4 = gUnk_09EF3960[sBosTmBodyThrowSteps[a].gfx4Index];
}

void BosTmBodySetWalkPose(TmBodyWork* work) {
    work->angle = 0;
    work->angle2 = 0;
    work->gfx3 = gUnk_09EF397C[0];
    work->gfx4 = gUnk_09EF3960[0];
    work->tm->x2 = work->tm->baseX;
    work->tm->y2 = work->tm->baseY;
    work->tm->z2 = work->tm->baseZ - 0x1500;
    BosTmBodyPlaceParts(work);
}

void BosTmBodyWalk(TmBodyWork* work) {
    if (work->tm->stepTimer == 0) {
        work->tm->baseX += work->tm->vx;
        work->tm->baseY += work->tm->vy;
        work->tm->x2 = work->tm->baseX;
        work->tm->y2 = work->tm->baseY;
        work->tm->z2 += sBosTmBodyWalkZ[work->tm->step] << 8;
        BosTmBodyPlaceParts(work);
    }

    BosTmBodyUpdateAngle(work);
}

void BosTmBodyUpdateRecoil(TmBodyWork* work) {
    s16 i;
    s16 j;

    if (work->tm->hitCount == 1) {
        work->tm->step = 0;
        work->tm->stepTimer = 0;

        if (work->tm->flags & TM_FLAG_FACING_LEFT) {
            work->angle = sBosTmBodyRecoilSteps[work->tm->step].dAngle;
            work->angle2 = sBosTmBodyRecoilSteps[work->tm->step].dAngle2;
            work->body.x = work->tm->baseX + ((sBosTmBodyRecoilSteps[work->tm->step].dx + 4) << 8);
            work->body2.x = work->tm->baseX + (sBosTmBodyRecoilSteps[work->tm->step].dx2 << 8);
            work->body3.x = work->tm->baseX + ((sBosTmBodyRecoilSteps[work->tm->step].dx3 + 12) << 8);
            work->body4.x = work->tm->baseX + ((sBosTmBodyRecoilSteps[work->tm->step].dx4 - 1) << 8);
            work->tm->x2 = work->tm->baseX + (sBosTmBodyRecoilSteps[work->tm->step].dx3 << 8);
        } else {
            work->angle = sBosTmBodyRecoilSteps[work->tm->step].dAngle;
            work->angle2 = sBosTmBodyRecoilSteps[work->tm->step].dAngle2;
            work->body.x = work->tm->baseX + ((-4 - sBosTmBodyRecoilSteps[work->tm->step].dx) << 8);
            work->body2.x = work->tm->baseX - (sBosTmBodyRecoilSteps[work->tm->step].dx2 << 8);
            work->body3.x = work->tm->baseX + ((-12 - sBosTmBodyRecoilSteps[work->tm->step].dx3) << 8);
            work->body4.x = work->tm->baseX + ((1 - sBosTmBodyRecoilSteps[work->tm->step].dx4) << 8);
            work->tm->x2 = work->tm->baseX - (sBosTmBodyRecoilSteps[work->tm->step].dx3 << 8);
        }

        work->body.z = work->tm->baseZ + ((sBosTmBodyRecoilSteps[work->tm->step].dz - 34 + sBosTmBodyRecoilZ[2]) << 8);
        work->body2.z = work->tm->baseZ + ((sBosTmBodyRecoilSteps[work->tm->step].dz2 + 9 + sBosTmBodyRecoilZ[2]) << 8);
        work->body3.z = work->tm->baseZ + ((sBosTmBodyRecoilSteps[work->tm->step].dz3 - 33 + sBosTmBodyRecoilZ[2]) << 8);
        work->body4.z = work->tm->baseZ + ((sBosTmBodyRecoilSteps[work->tm->step].dz4 - 30 + sBosTmBodyRecoilZ[2]) << 8);
        work->tm->z2 = work->tm->baseZ + ((sBosTmBodyRecoilSteps[work->tm->step].dz2 + 0 + sBosTmBodyRecoilZ[2]) << 8);
    } else {
        if (work->tm->step < 3) {
            if (work->tm->flags & TM_FLAG_FACING_LEFT) {
                work->angle += sBosTmBodyRecoilSteps[work->tm->step].dAngle;
                work->angle2 += sBosTmBodyRecoilSteps[work->tm->step].dAngle2;
                work->body.x += sBosTmBodyRecoilSteps[work->tm->step].dx << 8;
                work->body2.x += sBosTmBodyRecoilSteps[work->tm->step].dx2 << 8;
                work->body3.x += sBosTmBodyRecoilSteps[work->tm->step].dx3 << 8;
                work->body4.x += sBosTmBodyRecoilSteps[work->tm->step].dx4 << 8;
                work->tm->x2 += sBosTmBodyRecoilSteps[work->tm->step].dx3 << 8;
            } else {
                work->angle += sBosTmBodyRecoilSteps[work->tm->step].dAngle;
                work->angle2 += sBosTmBodyRecoilSteps[work->tm->step].dAngle2;
                work->body.x -= sBosTmBodyRecoilSteps[work->tm->step].dx << 8;
                work->body2.x -= sBosTmBodyRecoilSteps[work->tm->step].dx2 << 8;
                work->body3.x -= sBosTmBodyRecoilSteps[work->tm->step].dx3 << 8;
                work->body4.x -= sBosTmBodyRecoilSteps[work->tm->step].dx4 << 8;
                work->tm->x2 -= sBosTmBodyRecoilSteps[work->tm->step].dx3 << 8;
            }

            j = 2 - work->tm->step;
            work->body.z += (sBosTmBodyRecoilSteps[work->tm->step].dz + sBosTmBodyRecoilZ[j]) << 8;
            work->body2.z += (sBosTmBodyRecoilSteps[work->tm->step].dz2 + sBosTmBodyRecoilZ[j]) << 8;
            work->body3.z += (sBosTmBodyRecoilSteps[work->tm->step].dz3 + sBosTmBodyRecoilZ[j]) << 8;
            work->body4.z += (sBosTmBodyRecoilSteps[work->tm->step].dz4 + sBosTmBodyRecoilZ[j]) << 8;
            work->tm->z2 += (sBosTmBodyRecoilSteps[work->tm->step].dz2 + sBosTmBodyRecoilZ[j]) << 8;
        }

        if (work->tm->hurtTimer < 3) {
            i = work->tm->hurtTimer;

            if (work->tm->flags & TM_FLAG_FACING_LEFT) {
                work->angle -= sBosTmBodyRecoilSteps[i].dAngle;
                work->angle2 -= sBosTmBodyRecoilSteps[i].dAngle2;
                work->body.x -= sBosTmBodyRecoilSteps[i].dx << 8;
                work->body2.x -= sBosTmBodyRecoilSteps[i].dx2 << 8;
                work->body3.x -= sBosTmBodyRecoilSteps[i].dx3 << 8;
                work->body4.x -= sBosTmBodyRecoilSteps[i].dx4 << 8;
                work->tm->x2 -= sBosTmBodyRecoilSteps[i].dx3 << 8;
            } else {
                work->angle -= sBosTmBodyRecoilSteps[i].dAngle;
                work->angle2 -= sBosTmBodyRecoilSteps[i].dAngle2;
                work->body.x += sBosTmBodyRecoilSteps[i].dx << 8;
                work->body2.x += sBosTmBodyRecoilSteps[i].dx2 << 8;
                work->body3.x += sBosTmBodyRecoilSteps[i].dx3 << 8;
                work->body4.x += sBosTmBodyRecoilSteps[i].dx4 << 8;
                work->tm->x2 += sBosTmBodyRecoilSteps[i].dx3 << 8;
            }

            j = 2 - i;
            work->body.z -= (sBosTmBodyRecoilSteps[i].dz + sBosTmBodyRecoilZ[j]) << 8;
            work->body2.z -= (sBosTmBodyRecoilSteps[i].dz2 + sBosTmBodyRecoilZ[j]) << 8;
            work->body3.z -= (sBosTmBodyRecoilSteps[i].dz3 + sBosTmBodyRecoilZ[j]) << 8;
            work->body4.z -= (sBosTmBodyRecoilSteps[i].dz4 + sBosTmBodyRecoilZ[j]) << 8;
            work->tm->z2 -= (sBosTmBodyRecoilSteps[i].dz2 + sBosTmBodyRecoilZ[j]) << 8;
        }
    }
}

void BosTmBodyApplySpinStep(TmBodyWork* work, s16 a) {
    if (work->tm->flags & TM_FLAG_FACING_LEFT) {
        work->angle += sBosTmBodySpinSteps[a].dAngle;
        work->angle2 += sBosTmBodySpinSteps[a].dAngle2;
        work->body.x += sBosTmBodySpinSteps[a].dx << 8;
        work->body2.x += sBosTmBodySpinSteps[a].dx2 << 8;
        work->body3.x += sBosTmBodySpinSteps[a].dx3 << 8;
        work->body4.x += sBosTmBodySpinSteps[a].dx4 << 8;
        work->tm->x2 += sBosTmBodySpinSteps[a].dx3 << 8;
    } else {
        work->angle += sBosTmBodySpinSteps[a].dAngle;
        work->angle2 += sBosTmBodySpinSteps[a].dAngle2;
        work->body.x -= sBosTmBodySpinSteps[a].dx << 8;
        work->body2.x -= sBosTmBodySpinSteps[a].dx2 << 8;
        work->body3.x -= sBosTmBodySpinSteps[a].dx3 << 8;
        work->body4.x -= sBosTmBodySpinSteps[a].dx4 << 8;
        work->tm->x2 -= sBosTmBodySpinSteps[a].dx3 << 8;
    }

    work->body.z += sBosTmBodySpinSteps[a].dz << 8;
    work->body2.z += sBosTmBodySpinSteps[a].dz2 << 8;
    work->body3.z += sBosTmBodySpinSteps[a].dz3 << 8;
    work->body4.z += sBosTmBodySpinSteps[a].dz4 << 8;
    work->tm->z2 += sBosTmBodySpinSteps[a].dz2 << 8;
    work->gfx3 = gUnk_09EF397C[sBosTmBodySpinSteps[a].gfx3Index];
    work->gfx4 = gUnk_09EF3960[sBosTmBodySpinSteps[a].gfx4Index];
}

s32 GetAbsoluteDifference(s32 a, s32 b) {
    if (a > b) {
        return a - b;
    }

    if (a < b) {
        return b - a;
    }

    return 0;
}

void BosTmBodyChooseAction(TmBodyWork* work) {
    s32 st;
    s32 next;
    u16 rnd;

    if (work->tm->flags & TM_FLAG_SWITCHING_SIDES) {
        work->tm->state = work->tm->resumeState;
        return;
    }

    if (work->body2.hp < work->body2.maxHp / 2) {
        st = work->tm->tableState;

        if (st == 2) {
            if (work->tm->flags & TM_FLAG_TABLE_JUST_RAISED) {
                work->tm->state = 1;
                work->tm->flags = work->tm->flags & ~TM_FLAG_TABLE_JUST_RAISED;
            } else if (GetAbsoluteDifference(gBtlWork->actor->x, work->tm->baseX) <= 0x1DFF) {
                rnd = GetRandom() % 100;

                if (rnd > 20) {
                    work->tm->state = 9;
                } else {
                    work->tm->state = 1;
                }
            } else {
                work->tm->state = sBosTmActionChoices[GetRandom() % 4];

                if (work->tm->state == 3) {
                    work->tm->state = st;
                }

                if (work->tm->state == 4) {
                    work->tm->state = 1;
                }
            }
        } else if (st == 0) {
            if (GetAbsoluteDifference(gBtlWork->actor->x, work->tm->baseX) <= 0x1DFF) {
                rnd = GetRandom() % 100;

                if (rnd > 30) {
                    work->tm->state = 9;
                } else {
                    work->tm->state = 1;
                }
            } else {
                work->tm->state = sBosTmActionChoices[GetRandom() % 4];

                if (work->tm->state == 4) {
                    if (work->tm->flags & TM_FLAG_FACING_LEFT) {
                        work->tm->flags |= TM_FLAG_SWITCHING_SIDES;
                        work->tm->state = 4;
                        work->tm->resumeState = 4;
                    } else {
                        work->tm->flags |= TM_FLAG_SWITCHING_SIDES;
                        work->tm->state = 6;
                        work->tm->resumeState = 6;
                    }

                    next = work->tm->state;

                    if (next == 3) {
                        rnd = GetRandom() % 100;

                        if (rnd <= 49) {
                            work->tm->state = 11;
                        } else {
                            work->tm->state = next;
                        }
                    }
                }
            }
        } else {
            rnd = GetRandom() % 100;

            if (rnd <= 59) {
                work->tm->state = 9;
            } else {
                work->tm->state = 10;
            }
        }

        st = work->tm->state;

        if (st == 1) {
            rnd = GetRandom() % 100;

            if (rnd <= 59) {
                work->tm->state = st;
            } else {
                work->tm->state = 10;
            }
        }
    } else {
        st = work->tm->tableState;

        if (st == 2) {
            if (work->tm->flags & TM_FLAG_TABLE_JUST_RAISED) {
                work->tm->state = 1;
                work->tm->flags = work->tm->flags & ~TM_FLAG_TABLE_JUST_RAISED;
            } else if (GetAbsoluteDifference(gBtlWork->actor->x, work->tm->baseX) <= 0x1DFF) {
                rnd = GetRandom() % 100;

                if (rnd > 20) {
                    work->tm->state = 9;
                } else {
                    work->tm->state = 1;
                }
            } else {
                work->tm->state = sBosTmActionChoices[GetRandom() % 4];

                if (work->tm->state == 3) {
                    work->tm->state = st;
                }

                if (work->tm->state == 4) {
                    work->tm->state = 1;
                }
            }
        } else if (st == 0) {
            if (GetAbsoluteDifference(gBtlWork->actor->x, work->tm->baseX) <= 0x1DFF) {
                rnd = GetRandom() % 100;

                if (rnd > 30) {
                    work->tm->state = 9;
                } else {
                    work->tm->state = 1;
                }
            } else {
                work->tm->state = sBosTmActionChoices[GetRandom() % 4];

                if (work->tm->state == 4) {
                    if (work->tm->flags & TM_FLAG_FACING_LEFT) {
                        work->tm->flags |= TM_FLAG_SWITCHING_SIDES;
                        work->tm->state = 4;
                        work->tm->resumeState = 4;
                    } else {
                        work->tm->flags |= TM_FLAG_SWITCHING_SIDES;
                        work->tm->state = 6;
                        work->tm->resumeState = 6;
                    }
                }
            }
        } else {
            work->tm->state = 9;
        }
    }
}

void BosTmBodyUpdateReaction(BtlObj* a, TmBodyWork* work) {
    u16 t;

    if (a->hp <= 0) {
        return;
    }

    if (work->tm->baseX < 0x8E00 || work->tm->baseX > 0x16F00) {
        a->flags |= BTLOBJ_FLAG_INTANGIBLE;
    } else {
        a->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
    }

    switch (UpdateBtlObjReaction(a)) {
    case BTL_REACTION_CARD_ACTION:
        BosTmBodyResetTimers(work);
        BosTmBodyRollBossCard(work);
        BosTmBodyChooseAction(work);
        work->tm->flags &= ~TM_FLAG_HURT;
        break;
    case BTL_REACTION_CARD_BROKEN:
        work->tm->stateTimer = 0;
        work->tm->state = 14;
        break;
    case BTL_REACTION_HURT:
    case BTL_REACTION_STUNNED:
    case BTL_REACTION_GRAVITY:
        work->hp = a->hp;
        work->tm->flags |= TM_FLAG_HURT;
        work->tm->hitCount++;

        if (work->prevHp - work->hp >= 9999) {
            work->tm->hurtTimer = 55;
            work->tm->state = 12;
            work->tm->flags &= ~TM_FLAG_HURT_NO_RECOIL;
        } else if (work->tm->state != 12) {
            work->tm->hurtTimer = 20;
            work->tm->flags |= TM_FLAG_HURT_NO_RECOIL;
        }

        break;
    case BTL_REACTION_DEFEATED:
    case BTL_REACTION_GRAVITY_DEFEATED:
        BeginBossDefeat(a);
        work->tm->step = 0;
        work->tm->state = 13;
        break;
    }

    if (work->tm->flags & TM_FLAG_HURT) {
        work->tm->hurtTimer--;

        if (work->tm->hurtTimer <= 0) {
            work->tm->hitCount = 0;
            work->tm->flags &= ~TM_FLAG_HURT;
            ClearBtlObjActionFlags(a);

            if (work->tm->flags & TM_FLAG_HURT_NO_RECOIL) {
                work->tm->flags &= ~TM_FLAG_HURT_NO_RECOIL;
            } else {
                BosTmBodyResetTimers(work);
                t = work->tm->flags & TM_FLAG_SWITCHING_SIDES;

                if (t) {
                    BosTmBodySetWalkPose(work);
                    work->tm->state = 8;
                } else {
                    BosTmBodyResetPose(work);
                    work->tm->state = 0;
                }
            }
        }
    }

    work->prevHp = a->hp;
}

void task_bos_tm_body_0(TmBodyWork* work, TmWork* arg) {
    work->tiles = LoadObjTiles(gUnk_09652E84, 0x1D80);
    work->palette = LoadObjPalette(gBoss03objPalette, 0x60);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    work->gfx = gUnk_09EF3950[0];
    work->gfx2 = gUnk_09EF3958[0];
    work->gfx3 = gUnk_09EF397C[0];
    work->gfx4 = gUnk_09EF3960[0];
    work->tm = arg;
    work->tm->tileIndex = work->tiles->index;
    work->tm->tileCount += work->tiles->count;
    work->tm->paletteIndex = work->palette->index;
    work->unk_480 = 0;
    work->angleStep = 0;
    work->angleTimer = 0;
    work->unk_486 = 0;
    work->angle = 0;
    work->angle2 = 0;
    work->angle3 = 0;
    work->angle4 = 0;
    work->unk_488 = 0;
    work->hp = 1300;
    work->prevHp = 1300;
    work->unk_48E = 0;
    work->unk_490 = 10;
    work->unk_492 = 0;

    if (work->tm->flags & TM_FLAG_IN_EVENT) {
        BosTmBodySetObjPos(&work->body, work->tm->x + 4, work->tm->y,
                      work->tm->z - 34);
        BosTmBodySetObjPos(&work->body2, work->tm->x, work->tm->y,
                      work->tm->z + 9);
        BosTmBodySetObjPos(&work->body3, work->tm->x + 12, work->tm->y + 1,
                      work->tm->z - 33);
        BosTmBodySetObjPos(&work->body4, work->tm->x - 1, work->tm->y - 4,
                      work->tm->z - 30);
    } else {
        BosTmBodySetObjPos(&work->body, work->tm->x + 4, work->tm->y,
                      work->tm->z - 34);
        BosTmBodyInitEnemy(&work->body2, work->tm->x, work->tm->y,
                      work->tm->z - 16);
        BosTmBodySetObjPos(&work->body3, work->tm->x + 12, work->tm->y + 1,
                      work->tm->z - 33);
        BosTmBodySetObjPos(&work->body4, work->tm->x - 1, work->tm->y - 4,
                      work->tm->z - 30);
        gBosTmBodyObjCopy = work->body2;
    }
}

u8 task_bos_tm_body_1(TmBodyWork* work) {
    s16* table;
    u16 n;
    u16 flags;

    if (!(work->tm->flags & TM_FLAG_IN_EVENT)) {
        BosTmBodyUpdateReaction(&work->body2, work);
    }

    switch (work->tm->state) {
    case 0:
    case 15:
        if (work->tm->stateTimer == 0) {
            BosTmBodyResetPose(work);
        } else {
            if (gBtlWork->phase && (u16)(GetRandom() % 80) == 0) {
                RequestEnemyCardUse(&work->body2);
            }

            if (work->tm->stepTimer == 0) {
                table = sBosTmBodyIdleZ;
                work->tm->z2 += table[work->tm->step] << 8;
                work->body.z = work->tm->z2 - 0x2200;
                work->body2.z = work->tm->z2 + 0x900;
                work->body3.z = work->tm->z2 - 0x2100;
                work->body4.z = work->tm->z2 - 0x1E00;
            }

            BosTmBodyUpdateAngle(work);
        }

        break;
    case 4:
        if (work->tm->stateTimer == 0) {
            BosTmBodySetWalkPose(work);
            work->tm->vx = -0x900;
            work->tm->vy = 0;
        } else {
            BosTmBodyWalk(work);

            if (work->tm->baseX <= 0x8E00) {
                work->tm->flags &= ~TM_FLAG_FACING_LEFT;
                work->body2.flags &= ~BTLOBJ_FLAG_FACING_LEFT;
                work->tm->state = 5;
                work->tm->resumeState = 5;
                BosTmBodyResetTimers(work);
                BosTmBodySetWalkPose(work);
                work->tm->vx = 0x900;
                work->tm->vy = 0;
            }
        }

        break;
    case 5:
        if (work->tm->stateTimer == 0) {
            BosTmBodySetWalkPose(work);
            work->tm->vx = 0x900;
            work->tm->vy = 0;
        } else {
            BosTmBodyWalk(work);

            if (work->tm->baseX > 0x9FFF) {
                ClearBtlObjActionFlags(&work->body2);
                work->tm->flags &= ~TM_FLAG_SWITCHING_SIDES;
                work->tm->state = 0;
                work->tm->resumeState = 16;
                BosTmBodyResetTimers(work);
                BosTmBodyResetPose(work);
            }
        }

        break;
    case 6:
        if (work->tm->stateTimer == 0) {
            BosTmBodySetWalkPose(work);
            work->tm->vx = 0x900;
            work->tm->vy = 0;
        } else {
            BosTmBodyWalk(work);

            if (work->tm->baseX > 0x16EFF) {
                work->tm->flags |= TM_FLAG_FACING_LEFT;
                work->body2.flags |= BTLOBJ_FLAG_FACING_LEFT;
                work->tm->state = 7;
                work->tm->resumeState = 7;
                BosTmBodyResetTimers(work);
                BosTmBodySetWalkPose(work);
                work->tm->vx = -0x900;
                work->tm->vy = 0;
            }
        }

        break;
    case 7:
        if (work->tm->stateTimer == 0) {
            BosTmBodySetWalkPose(work);
            work->tm->vx = -0x900;
            work->tm->vy = 0;
        } else {
            BosTmBodyWalk(work);

            if (work->tm->baseX <= 0x15D00) {
                ClearBtlObjActionFlags(&work->body2);
                work->tm->flags &= ~TM_FLAG_SWITCHING_SIDES;
                work->tm->state = 0;
                work->tm->resumeState = 16;
                BosTmBodyResetTimers(work);
                BosTmBodyResetPose(work);
            }
        }

        break;
    case 1:
    case 10:
        if (work->tm->stateTimer == 0) {
            BosTmBodyResetPose(work);
        } else if (work->tm->flags & TM_FLAG_ATTACK_DONE) {
            work->tm->flags &= ~TM_FLAG_ATTACK_DONE;
            ClearBtlObjActionFlags(&work->body2);
            work->tm->state = 0;
            BosTmBodyResetTimers(work);
            work->tm->z2 = (s16)work->tm->z << 8;
        }

        break;
    case 2:
    case 3:
        if (work->tm->stateTimer == 0) {
            BosTmBodyResetPose(work);
        } else {
            n = work->tm->step;

            if (work->tm->step <= 3) {
                BosTmBodyApplyThrowStep(work, work->tm->step);
            } else if (n >= 66 && n <= 74) {
                BosTmBodyApplyThrowStep(work, n - 62);
            } else if (n >= 98 && n <= 100) {
                BosTmBodyApplyThrowStep(work, n - 85);
            }

            if (work->tm->flags & TM_FLAG_ATTACK_DONE) {
                work->tm->flags &= ~TM_FLAG_ATTACK_DONE;
                ClearBtlObjActionFlags(&work->body2);
                work->tm->state = 0;
                BosTmBodyResetTimers(work);
                BosTmBodyResetPose(work);
            }
        }

        break;
    case 11:
        if (work->tm->stateTimer == 0) {
            BosTmBodyResetPose(work);
        } else {
            n = work->tm->step;

            if (work->tm->step <= 3) {
                BosTmBodyApplyThrowStep(work, work->tm->step);
            } else if (n >= 96 && n <= 104) {
                BosTmBodyApplyThrowStep(work, n - 92);
            } else if (n >= 128 && n <= 130) {
                BosTmBodyApplyThrowStep(work, n - 115);
            }

            if (work->tm->flags & TM_FLAG_ATTACK_DONE) {
                work->tm->flags &= ~TM_FLAG_ATTACK_DONE;
                ClearBtlObjActionFlags(&work->body2);
                work->tm->state = 0;
                BosTmBodyResetTimers(work);
                BosTmBodyResetPose(work);
            }
        }

        break;
    case 9:
        if (work->tm->stateTimer == 0) {
            BosTmBodyResetPose(work);
        } else {
            n = work->tm->step;

            if (work->tm->step <= 2) {
                BosTmBodyApplySpinStep(work, work->tm->step);
            } else if (n >= 41 && n <= 46) {
                BosTmBodyApplySpinStep(work, n - 38);
            }

            if (work->tm->flags & TM_FLAG_ATTACK_DONE) {
                work->tm->flags &= ~TM_FLAG_ATTACK_DONE;
                ClearBtlObjActionFlags(&work->body2);
                work->tm->state = 0;
                BosTmBodyResetTimers(work);
                BosTmBodyResetPose(work);
            }
        }

        break;
    case 12:
        BosTmBodyUpdateRecoil(work);
        break;
    case 14:
        if (work->tm->stateTimer == 0) {
            BosTmBodySetBreakPose(work);

            if (work->tm->flags & TM_FLAG_SWITCHING_SIDES) {
                RequestBossCardValue(9);
            }
        } else if (work->tm->stateTimer > 59) {
            BosTmBodyResetTimers(work);
            work->tm->flags &= ~TM_FLAG_GIMMICK_DROP_ROLLED;
            flags = work->tm->flags & TM_FLAG_SWITCHING_SIDES;

            if (flags) {
                ClearBtlObjActionFlags(&work->body2);
                BosTmBodySetBreakPose(work);
                work->tm->state = 8;
            } else {
                ClearBtlObjActionFlags(&work->body2);
                BosTmBodyResetPose(work);
                work->tm->state = 0;
            }
        } else if (!(work->tm->flags & TM_FLAG_GIMMICK_DROP_ROLLED) && work->tm->tableState == 0 && (work->tm->flags & TM_FLAG_HURT)) {
            if ((u16)(GetRandom() % 100) <= 30) {
                DropGimmickCard(0, work->tm->baseX, work->tm->baseY, work->tm->baseZ);
                work->tm->flags |= TM_FLAG_GIMMICK_DROP_ROLLED;
            } else {
                work->tm->flags |= TM_FLAG_GIMMICK_DROP_ROLLED;
            }
        }

        break;
    case 8:
        RequestEnemyCardUse(&work->body2);
        break;
    case 13:
        if (work->tm->step == 0) {
            BosTmBodySetDefeatPose(work);
        }

        break;
    case 16:
    case 17:
        break;
    }

    return 1;
}

void task_bos_tm_body_2(TmBodyWork* work) {
    BtlObj* s0;
    BtlObj* s1;
    BtlObj* s2;
    BtlObj* s3;
    ObjAffine* a1;
    ObjAffine* a2;
    u16 mode;
    void* pal;
    s16 x;
    s16 y;

    if (work->tm->flags & TM_FLAG_FACING_LEFT) {
        a1 = AllocObjAffine(work->angle, 0x100, 0x100, 1);
        a2 = AllocObjAffine(work->angle2, 0x100, 0x100, 1);
        mode = 0x800;
    } else {
        a1 = AllocObjAffine(work->angle, -0x100, 0x100, 1);
        a2 = AllocObjAffine(work->angle2, -0x100, 0x100, 1);
        mode = 0x801;
    }

    if (gBtlWork->paused) {
        pal = work->palette;
    } else if (work->tm->flags & TM_FLAG_HURT) {
        if (gFrameCounter & 1) {
            pal = work->palette2;
        } else {
            pal = work->palette;
        }
    } else {
        pal = work->palette;
    }

    s0 = &work->body;
    s1 = &work->body2;
    s2 = &work->body3;
    s3 = &work->body4;
    WorldToScreen(&x, &y, s0->x, s0->y, s0->z);
    DrawSprite(x, y, work->gfx, work->tiles, pal, a1, SPRITE_PRIORITY(2),
               -4101 - (s0->y >> 8) * 4);
    WorldToScreen(&x, &y, s1->x, s1->y, s1->z - 0x1900);
    DrawSprite(x, y, work->gfx2, work->tiles, pal, a2, SPRITE_PRIORITY(2),
               -4100 - (s1->y >> 8) * 4);
    WorldToScreen(&x, &y, s2->x, s2->y, s2->z);
    DrawSprite(x, y, work->gfx3, work->tiles, pal, NULL, mode,
               -4100 - (s2->y >> 8) * 4);
    WorldToScreen(&x, &y, s3->x, s3->y, s3->z);
    DrawSprite(x, y, work->gfx4, work->tiles, pal, NULL, mode,
               -4100 - (s3->y >> 8) * 4);
}

void task_bos_tm_body_3(TmBodyWork* work) {
    if ((work->tm->flags & TM_FLAG_IN_EVENT) == 0) {
        BosTmBodyReleaseEnemy(&work->body2);
    }

    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
}

void BosTmBodyRollBossCard(TmBodyWork* work) {
    if (work->body2.hp < work->body2.maxHp / 2) {
        if (GetRandom() % 100 <= 9) {
            RequestBossCardValue(1);
        } else if (GetRandom() % 90 <= 19) {
            RequestBossCardValue(GetRandom() % 2 + 7);
        } else {
            RequestBossCardValue(GetRandom() % 4 + 3);
        }
    } else if (GetRandom() % 100 <= 29) {
        RequestBossCardValue(GetRandom() % 3 + 6);
    } else {
        RequestBossCardValue(GetRandom() % 6 + 1);
    }
}
