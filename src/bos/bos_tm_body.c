#include "macros.h"
#include "boss_tm.h"
#include "boss_tm_assets.h"
#include "sprites_boss_tm.h"
#include "card_api.h"
#include "engine_math.h"
#include "system_state.h"
#include "acgtrans.h"

BtlObj gBosTmBodyObjCopy EWRAM_COMMON(16);

static const EmyKind sBosTmEmyKind = { 34, 1300, 28, 14, 20, 40, 1 };

static u8 sBosTmBodyAngles[11] = { 0, 2, 5, 15, 18, 20, 20, 18, 15, 5, 2 };

static s16 sBosTmBodyIdleZ[8] = { 8, -8, -12, 12, 8, -8, -12, 12 };

static s16 sBosTmBodyWalkZ[10] = { -11, -8, -10, 10, 19, -11, -8, -10, 10, 19 };

static TmBodyStep sUnk_09EF1D88[3] = {
    { -8, 0, 246, { 0, 0, 0 }, -3, 2, 246, { 0, 0, 0 }, -6, 2, { 0, 0 }, 0, -6, 2, { 0, 0 }, 0 },
    { -6, 8, 246, { 0, 0, 0 }, -2, 7, 246, { 0, 0, 0 }, -6, 6, { 0, 0 }, 0, -6, 6, { 0, 0 }, 0 },
    { -4, 0, 246, { 0, 0, 0 }, 0, 0, 246, { 0, 0, 0 }, -3, 0, { 0, 0 }, 0, -3, 0, { 0, 0 }, 0 },
};

TmBodyStep gUnk_09EF1DE8 = { 0, 0, 0, { 0, 0, 0 }, 0, 0, 0, { 0, 0, 0 }, 0, 0, { 0, 0 }, 0, 0, 0, { 0, 0 }, 0 };

static s16 sUnk_09EF1E08[3] = { 15, 6, 0 };

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

static TmBodyStep sUnk_09EF2034[9] = {
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

void BosTmBodyResetTimers(TmBodyWork* p) {
    p->tm->stepTimer = 0;
    p->tm->step = 0;
    p->tm->stateTimer = 0;
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
    p->flags |= 4;
}

void BosTmBodySetObjPos(BtlObj* p, s16 a, s16 b, s16 c) {
    p->x = a << 8;
    p->y = b << 8;
    p->z = c << 8;
}

void BosTmBodyReleaseEnemy(BtlObj* a) {
    ReleaseEnemyBtlObj(a);
}

void BosTmBodyUpdateAngle(TmBodyWork* p) {
    p->angleTimer++;
    if (p->angleTimer > 5) {
        p->angleTimer = 0;
        p->angleStep++;
        if (p->angleStep > 10) {
            p->angleStep = 0;
        }
        p->angle = sBosTmBodyAngles[p->angleStep];
    }
}

void BosTmBodyPlaceParts(TmBodyWork* p) {
    if (p->tm->flags & 0x20) {
        p->body.x = p->tm->x2 + 0x400;
        p->body2.x = p->tm->x2;
        p->body3.x = p->tm->x2 + 0xC00;
        p->body4.x = p->tm->x2 - 0x100;
    } else {
        p->body.x = p->tm->x2 - 0x400;
        p->body2.x = p->tm->x2;
        p->body3.x = p->tm->x2 - 0xC00;
        p->body4.x = p->tm->x2 + 0x100;
    }
    p->body.y = p->tm->y2;
    p->body2.y = p->tm->y2;
    p->body3.y = p->tm->y2 + 0x100;
    p->body4.y = p->tm->y2 - 0x400;
    p->body.z = p->tm->z2 - 0x2200;
    p->body2.z = p->tm->z2 + 0x900;
    p->body3.z = p->tm->z2 - 0x2100;
    p->body4.z = p->tm->z2 - 0x1E00;
}

void BosTmBodyResetPose(TmBodyWork* p) {
    p->angle = 0;
    p->angle2 = 0;
    p->gfx3 = gUnk_09EF397C[0];
    p->gfx4 = gUnk_09EF3960[0];
    p->tm->x2 = p->tm->baseX;
    p->tm->y2 = p->tm->baseY;
    p->tm->z2 = p->tm->baseZ;
    BosTmBodyPlaceParts(p);
}

void BosTmBodySetDefeatPose(TmBodyWork* p) {
    TmWork* src;
    s32 dz;

    p->angle = 226;
    p->angle2 = 226;
    p->gfx3 = gUnk_09EF397C[0];
    p->gfx4 = gUnk_09EF3960[0];
    dz = 0xF00;
    src = p->tm;

    if (src->flags & 0x20) {
        p->tm->x2 = p->tm->baseX - 0xA00;
        p->tm->y2 = p->tm->baseY;
        p->tm->z2 = p->tm->baseZ + dz;
        p->body.x = p->tm->baseX - 0xF00;
        p->body2.x = p->tm->x2 + 0x500;
        p->body3.x = p->tm->x2 + 0x400;
        p->body4.x = p->tm->x2 - 0x900;
    } else {
        p->tm->x2 = p->tm->baseX + 0xA00;
        p->tm->y2 = p->tm->baseY;
        p->tm->z2 = p->tm->baseZ + 0xF00;
        p->body.x = p->tm->baseX + 0xF00;
        p->body2.x = p->tm->x2 - 0x500;
        p->body3.x = p->tm->x2 - 0x400;
        p->body4.x = p->tm->x2 + 0x900;
    }
    p->body.z = p->tm->z2 - 0x1F00;
    p->body2.z = p->tm->z2 + 0xE00;
    p->body3.z = p->tm->z2 - 0x1F00;
    p->body4.z = p->tm->z2 - 0x1C00;
}

void BosTmBodySetBreakPose(TmBodyWork* p) {
    p->angle = 30;
    p->angle2 = 10;
    p->gfx3 = gUnk_09EF397C[0];
    p->gfx4 = gUnk_09EF3960[0];

    if (p->tm->flags & 0x20) {
        p->tm->x2 = p->tm->baseX + 0xA00;
        p->tm->y2 = p->tm->baseY;
        p->tm->z2 = p->tm->baseZ + 0xF00;
        p->body.x = p->tm->baseX + 0xB00;
        p->body2.x = p->tm->x2 - 0x500;
        p->body3.x = p->tm->x2 + 0x900;
        p->body4.x = p->tm->x2 - 0x400;
    } else {
        p->tm->x2 = p->tm->baseX - 0xA00;
        p->tm->y2 = p->tm->baseY;
        p->tm->z2 = p->tm->baseZ + 0xF00;
        p->body.x = p->tm->baseX - 0xB00;
        p->body2.x = p->tm->x2 + 0x500;
        p->body3.x = p->tm->x2 - 0x900;
        p->body4.x = p->tm->x2 + 0x400;
    }
    p->body.z = p->tm->z2 - 0x2200;
    p->body2.z = p->tm->z2 + 0x900;
    p->body3.z = p->tm->z2 - 0x1F00;
    p->body4.z = p->tm->z2 - 0x1C00;
}

void BosTmBodyApplyThrowStep(TmBodyWork* p, s16 a) {
    if (p->tm->flags & 0x20) {
        p->angle += sBosTmBodyThrowSteps[a].dAngle;
        p->angle2 += sBosTmBodyThrowSteps[a].dAngle2;
        p->body.x += sBosTmBodyThrowSteps[a].dx << 8;
        p->body2.x += sBosTmBodyThrowSteps[a].dx2 << 8;
        p->body3.x += sBosTmBodyThrowSteps[a].dx3 << 8;
        p->body4.x += sBosTmBodyThrowSteps[a].dx4 << 8;
        p->tm->x2 += sBosTmBodyThrowSteps[a].dx3 << 8;
    } else {
        p->angle += sBosTmBodyThrowSteps[a].dAngle;
        p->angle2 += sBosTmBodyThrowSteps[a].dAngle2;
        p->body.x -= sBosTmBodyThrowSteps[a].dx << 8;
        p->body2.x -= sBosTmBodyThrowSteps[a].dx2 << 8;
        p->body3.x -= sBosTmBodyThrowSteps[a].dx3 << 8;
        p->body4.x -= sBosTmBodyThrowSteps[a].dx4 << 8;
        p->tm->x2 -= sBosTmBodyThrowSteps[a].dx3 << 8;
    }
    p->body.z += sBosTmBodyThrowSteps[a].dz << 8;
    p->body2.z += sBosTmBodyThrowSteps[a].dz2 << 8;
    p->body3.z += sBosTmBodyThrowSteps[a].dz3 << 8;
    p->body4.z += sBosTmBodyThrowSteps[a].dz4 << 8;
    p->tm->z2 += sBosTmBodyThrowSteps[a].dz2 << 8;
    p->gfx3 = gUnk_09EF397C[sBosTmBodyThrowSteps[a].gfx3Index];
    p->gfx4 = gUnk_09EF3960[sBosTmBodyThrowSteps[a].gfx4Index];
}

void BosTmBodySetWalkPose(TmBodyWork* p) {
    p->angle = 0;
    p->angle2 = 0;
    p->gfx3 = gUnk_09EF397C[0];
    p->gfx4 = gUnk_09EF3960[0];
    p->tm->x2 = p->tm->baseX;
    p->tm->y2 = p->tm->baseY;
    p->tm->z2 = p->tm->baseZ - 0x1500;
    BosTmBodyPlaceParts(p);
}

void BosTmBodyWalk(TmBodyWork* p) {
    if (p->tm->stepTimer == 0) {
        p->tm->baseX += p->tm->vx;
        p->tm->baseY += p->tm->vy;
        p->tm->x2 = p->tm->baseX;
        p->tm->y2 = p->tm->baseY;
        p->tm->z2 += sBosTmBodyWalkZ[p->tm->step] << 8;
        BosTmBodyPlaceParts(p);
    }
    BosTmBodyUpdateAngle(p);
}

void func_080B8A00(TmBodyWork* p) {
    s16 i;
    s16 j;

    if (p->tm->hitCount == 1) {
        p->tm->step = 0;
        p->tm->stepTimer = 0;
        if (p->tm->flags & 0x20) {
            p->angle = sUnk_09EF1D88[p->tm->step].dAngle;
            p->angle2 = sUnk_09EF1D88[p->tm->step].dAngle2;
            p->body.x = p->tm->baseX + ((sUnk_09EF1D88[p->tm->step].dx + 4) << 8);
            p->body2.x = p->tm->baseX + (sUnk_09EF1D88[p->tm->step].dx2 << 8);
            p->body3.x = p->tm->baseX + ((sUnk_09EF1D88[p->tm->step].dx3 + 12) << 8);
            p->body4.x = p->tm->baseX + ((sUnk_09EF1D88[p->tm->step].dx4 - 1) << 8);
            p->tm->x2 = p->tm->baseX + (sUnk_09EF1D88[p->tm->step].dx3 << 8);
        } else {
            p->angle = sUnk_09EF1D88[p->tm->step].dAngle;
            p->angle2 = sUnk_09EF1D88[p->tm->step].dAngle2;
            p->body.x = p->tm->baseX + ((-4 - sUnk_09EF1D88[p->tm->step].dx) << 8);
            p->body2.x = p->tm->baseX - (sUnk_09EF1D88[p->tm->step].dx2 << 8);
            p->body3.x = p->tm->baseX + ((-12 - sUnk_09EF1D88[p->tm->step].dx3) << 8);
            p->body4.x = p->tm->baseX + ((1 - sUnk_09EF1D88[p->tm->step].dx4) << 8);
            p->tm->x2 = p->tm->baseX - (sUnk_09EF1D88[p->tm->step].dx3 << 8);
        }
        p->body.z = p->tm->baseZ + ((sUnk_09EF1D88[p->tm->step].dz - 34 + sUnk_09EF1E08[2]) << 8);
        p->body2.z = p->tm->baseZ + ((sUnk_09EF1D88[p->tm->step].dz2 + 9 + sUnk_09EF1E08[2]) << 8);
        p->body3.z = p->tm->baseZ + ((sUnk_09EF1D88[p->tm->step].dz3 - 33 + sUnk_09EF1E08[2]) << 8);
        p->body4.z = p->tm->baseZ + ((sUnk_09EF1D88[p->tm->step].dz4 - 30 + sUnk_09EF1E08[2]) << 8);
        p->tm->z2 = p->tm->baseZ + ((sUnk_09EF1D88[p->tm->step].dz2 + 0 + sUnk_09EF1E08[2]) << 8);
    } else {
        if (p->tm->step < 3) {
            if (p->tm->flags & 0x20) {
                p->angle += sUnk_09EF1D88[p->tm->step].dAngle;
                p->angle2 += sUnk_09EF1D88[p->tm->step].dAngle2;
                p->body.x += sUnk_09EF1D88[p->tm->step].dx << 8;
                p->body2.x += sUnk_09EF1D88[p->tm->step].dx2 << 8;
                p->body3.x += sUnk_09EF1D88[p->tm->step].dx3 << 8;
                p->body4.x += sUnk_09EF1D88[p->tm->step].dx4 << 8;
                p->tm->x2 += sUnk_09EF1D88[p->tm->step].dx3 << 8;
            } else {
                p->angle += sUnk_09EF1D88[p->tm->step].dAngle;
                p->angle2 += sUnk_09EF1D88[p->tm->step].dAngle2;
                p->body.x -= sUnk_09EF1D88[p->tm->step].dx << 8;
                p->body2.x -= sUnk_09EF1D88[p->tm->step].dx2 << 8;
                p->body3.x -= sUnk_09EF1D88[p->tm->step].dx3 << 8;
                p->body4.x -= sUnk_09EF1D88[p->tm->step].dx4 << 8;
                p->tm->x2 -= sUnk_09EF1D88[p->tm->step].dx3 << 8;
            }
            j = 2 - p->tm->step;
            p->body.z += (sUnk_09EF1D88[p->tm->step].dz + sUnk_09EF1E08[j]) << 8;
            p->body2.z += (sUnk_09EF1D88[p->tm->step].dz2 + sUnk_09EF1E08[j]) << 8;
            p->body3.z += (sUnk_09EF1D88[p->tm->step].dz3 + sUnk_09EF1E08[j]) << 8;
            p->body4.z += (sUnk_09EF1D88[p->tm->step].dz4 + sUnk_09EF1E08[j]) << 8;
            p->tm->z2 += (sUnk_09EF1D88[p->tm->step].dz2 + sUnk_09EF1E08[j]) << 8;
        }
        if (p->tm->hurtTimer < 3) {
            i = p->tm->hurtTimer;
            if (p->tm->flags & 0x20) {
                p->angle -= sUnk_09EF1D88[i].dAngle;
                p->angle2 -= sUnk_09EF1D88[i].dAngle2;
                p->body.x -= sUnk_09EF1D88[i].dx << 8;
                p->body2.x -= sUnk_09EF1D88[i].dx2 << 8;
                p->body3.x -= sUnk_09EF1D88[i].dx3 << 8;
                p->body4.x -= sUnk_09EF1D88[i].dx4 << 8;
                p->tm->x2 -= sUnk_09EF1D88[i].dx3 << 8;
            } else {
                p->angle -= sUnk_09EF1D88[i].dAngle;
                p->angle2 -= sUnk_09EF1D88[i].dAngle2;
                p->body.x += sUnk_09EF1D88[i].dx << 8;
                p->body2.x += sUnk_09EF1D88[i].dx2 << 8;
                p->body3.x += sUnk_09EF1D88[i].dx3 << 8;
                p->body4.x += sUnk_09EF1D88[i].dx4 << 8;
                p->tm->x2 += sUnk_09EF1D88[i].dx3 << 8;
            }
            j = 2 - i;
            p->body.z -= (sUnk_09EF1D88[i].dz + sUnk_09EF1E08[j]) << 8;
            p->body2.z -= (sUnk_09EF1D88[i].dz2 + sUnk_09EF1E08[j]) << 8;
            p->body3.z -= (sUnk_09EF1D88[i].dz3 + sUnk_09EF1E08[j]) << 8;
            p->body4.z -= (sUnk_09EF1D88[i].dz4 + sUnk_09EF1E08[j]) << 8;
            p->tm->z2 -= (sUnk_09EF1D88[i].dz2 + sUnk_09EF1E08[j]) << 8;
        }
    }
}

void func_080B8FF4(TmBodyWork* p, s16 a) {
    if (p->tm->flags & 0x20) {
        p->angle += sUnk_09EF2034[a].dAngle;
        p->angle2 += sUnk_09EF2034[a].dAngle2;
        p->body.x += sUnk_09EF2034[a].dx << 8;
        p->body2.x += sUnk_09EF2034[a].dx2 << 8;
        p->body3.x += sUnk_09EF2034[a].dx3 << 8;
        p->body4.x += sUnk_09EF2034[a].dx4 << 8;
        p->tm->x2 += sUnk_09EF2034[a].dx3 << 8;
    } else {
        p->angle += sUnk_09EF2034[a].dAngle;
        p->angle2 += sUnk_09EF2034[a].dAngle2;
        p->body.x -= sUnk_09EF2034[a].dx << 8;
        p->body2.x -= sUnk_09EF2034[a].dx2 << 8;
        p->body3.x -= sUnk_09EF2034[a].dx3 << 8;
        p->body4.x -= sUnk_09EF2034[a].dx4 << 8;
        p->tm->x2 -= sUnk_09EF2034[a].dx3 << 8;
    }
    p->body.z += sUnk_09EF2034[a].dz << 8;
    p->body2.z += sUnk_09EF2034[a].dz2 << 8;
    p->body3.z += sUnk_09EF2034[a].dz3 << 8;
    p->body4.z += sUnk_09EF2034[a].dz4 << 8;
    p->tm->z2 += sUnk_09EF2034[a].dz2 << 8;
    p->gfx3 = gUnk_09EF397C[sUnk_09EF2034[a].gfx3Index];
    p->gfx4 = gUnk_09EF3960[sUnk_09EF2034[a].gfx4Index];
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
void BosTmBodyChooseAction(TmBodyWork* p) {
    s32 st;
    s32 next;
    u16 rnd;

    if (p->tm->flags & 0x40) {
        p->tm->state = p->tm->resumeState;
        return;
    }

    if (p->body2.hp < p->body2.maxHp / 2) {
        st = p->tm->tableState;

        if (st == 2) {
            if (p->tm->flags & 0x10) {
                p->tm->state = 1;
                p->tm->flags = p->tm->flags & ~0x10;
            } else if (GetAbsoluteDifference(gBtlWork->actor->x, p->tm->baseX) <= 0x1DFF) {
                rnd = GetRandom() % 100;

                if (rnd > 20) {
                    p->tm->state = 9;
                } else {
                    p->tm->state = 1;
                }
            } else {
                p->tm->state = sBosTmActionChoices[GetRandom() % 4];

                if (p->tm->state == 3) {
                    p->tm->state = st;
                }

                if (p->tm->state == 4) {
                    p->tm->state = 1;
                }
            }
        } else if (st == 0) {
            if (GetAbsoluteDifference(gBtlWork->actor->x, p->tm->baseX) <= 0x1DFF) {
                rnd = GetRandom() % 100;

                if (rnd > 30) {
                    p->tm->state = 9;
                } else {
                    p->tm->state = 1;
                }
            } else {
                p->tm->state = sBosTmActionChoices[GetRandom() % 4];

                if (p->tm->state == 4) {
                    if (p->tm->flags & 0x20) {
                        p->tm->flags |= 0x40;
                        p->tm->state = 4;
                        p->tm->resumeState = 4;
                    } else {
                        p->tm->flags |= 0x40;
                        p->tm->state = 6;
                        p->tm->resumeState = 6;
                    }
                    next = p->tm->state;

                    if (next == 3) {
                        rnd = GetRandom() % 100;

                        if (rnd <= 49) {
                            p->tm->state = 11;
                        } else {
                            p->tm->state = next;
                        }
                    }
                }
            }
        } else {
            rnd = GetRandom() % 100;

            if (rnd <= 59) {
                p->tm->state = 9;
            } else {
                p->tm->state = 10;
            }
        }
        st = p->tm->state;

        if (st == 1) {
            rnd = GetRandom() % 100;

            if (rnd <= 59) {
                p->tm->state = st;
            } else {
                p->tm->state = 10;
            }
        }
    } else {
        st = p->tm->tableState;

        if (st == 2) {
            if (p->tm->flags & 0x10) {
                p->tm->state = 1;
                p->tm->flags = p->tm->flags & ~0x10;
            } else if (GetAbsoluteDifference(gBtlWork->actor->x, p->tm->baseX) <= 0x1DFF) {
                rnd = GetRandom() % 100;

                if (rnd > 20) {
                    p->tm->state = 9;
                } else {
                    p->tm->state = 1;
                }
            } else {
                p->tm->state = sBosTmActionChoices[GetRandom() % 4];

                if (p->tm->state == 3) {
                    p->tm->state = st;
                }

                if (p->tm->state == 4) {
                    p->tm->state = 1;
                }
            }
        } else if (st == 0) {
            if (GetAbsoluteDifference(gBtlWork->actor->x, p->tm->baseX) <= 0x1DFF) {
                rnd = GetRandom() % 100;

                if (rnd > 30) {
                    p->tm->state = 9;
                } else {
                    p->tm->state = 1;
                }
            } else {
                p->tm->state = sBosTmActionChoices[GetRandom() % 4];

                if (p->tm->state == 4) {
                    if (p->tm->flags & 0x20) {
                        p->tm->flags |= 0x40;
                        p->tm->state = 4;
                        p->tm->resumeState = 4;
                    } else {
                        p->tm->flags |= 0x40;
                        p->tm->state = 6;
                        p->tm->resumeState = 6;
                    }
                }
            }
        } else {
            p->tm->state = 9;
        }
    }
}

void _080B949C(BtlObj* a, TmBodyWork* b) {
    u16 t;

    if (a->hp <= 0) {
        return;
    }

    if (b->tm->baseX < 0x8E00 || b->tm->baseX > 0x16F00) {
        a->flags |= 0x100;
    } else {
        a->flags &= ~0x100;
    }

    switch (UpdateBtlObjReaction(a)) {
    case 5:
        BosTmBodyResetTimers(b);
        BosTmBodyRollBossCard(b);
        BosTmBodyChooseAction(b);
        b->tm->flags &= ~1;
        break;
    case 4:
        b->tm->stateTimer = 0;
        b->tm->state = 14;
        break;
    case 1:
    case 6:
    case 7:
        b->hp = a->hp;
        b->tm->flags |= 1;
        b->tm->hitCount++;

        if (b->prevHp - b->hp >= 9999) {
            b->tm->hurtTimer = 55;
            b->tm->state = 12;
            b->tm->flags &= ~4;
        } else if (b->tm->state != 12) {
            b->tm->hurtTimer = 20;
            b->tm->flags |= 4;
        }
        break;
    case 3:
    case 8:
        BeginBossDefeat(a);
        b->tm->step = 0;
        b->tm->state = 13;
        break;
    }

    if (b->tm->flags & 1) {
        b->tm->hurtTimer--;

        if (b->tm->hurtTimer <= 0) {
            b->tm->hitCount = 0;
            b->tm->flags &= ~1;
            ClearBtlObjActionFlags(a);

            if (b->tm->flags & 4) {
                b->tm->flags &= ~4;
            } else {
                BosTmBodyResetTimers(b);
                t = b->tm->flags & 0x40;

                if (t) {
                    BosTmBodySetWalkPose(b);
                    b->tm->state = 8;
                } else {
                    BosTmBodyResetPose(b);
                    b->tm->state = 0;
                }
            }
        }
    }
    b->prevHp = a->hp;
}

void task_bos_tm_body_0(TmBodyWork* work, TmWork* arg) {
    work->tiles = LoadObjTiles(gUnk_09652E84, 0x1D80);
    work->palette = LoadObjPalette(gBoss03objPalette, 0x60);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    work->gfx = gUnk_09EF3950;
    work->gfx2 = gUnk_09EF3958;
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

    if (work->tm->flags & 8) {
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

    if (!(work->tm->flags & 8)) {
        _080B949C(&work->body2, work);
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
                work->tm->flags &= ~0x20;
                work->body2.flags &= ~4;
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
                work->tm->flags &= ~0x40;
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
                work->tm->flags |= 0x20;
                work->body2.flags |= 4;
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
                work->tm->flags &= ~0x40;
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
        } else if (work->tm->flags & 2) {
            work->tm->flags &= ~2;
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
            if (work->tm->flags & 2) {
                work->tm->flags &= ~2;
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
            if (work->tm->flags & 2) {
                work->tm->flags &= ~2;
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
                func_080B8FF4(work, work->tm->step);
            } else if (n >= 41 && n <= 46) {
                func_080B8FF4(work, n - 38);
            }
            if (work->tm->flags & 2) {
                work->tm->flags &= ~2;
                ClearBtlObjActionFlags(&work->body2);
                work->tm->state = 0;
                BosTmBodyResetTimers(work);
                BosTmBodyResetPose(work);
            }
        }
        break;
    case 12:
        func_080B8A00(work);
        break;
    case 14:
        if (work->tm->stateTimer == 0) {
            BosTmBodySetBreakPose(work);
            if (work->tm->flags & 0x40) {
                RequestBossCardValue(9);
            }
        } else if (work->tm->stateTimer > 59) {
            BosTmBodyResetTimers(work);
            work->tm->flags &= ~0x80;
            flags = work->tm->flags & 0x40;
            if (flags) {
                ClearBtlObjActionFlags(&work->body2);
                BosTmBodySetBreakPose(work);
                work->tm->state = 8;
            } else {
                ClearBtlObjActionFlags(&work->body2);
                BosTmBodyResetPose(work);
                work->tm->state = 0;
            }
        } else if (!(work->tm->flags & 0x80) && work->tm->tableState == 0 && (work->tm->flags & 1)) {
            if ((u16)(GetRandom() % 100) <= 30) {
                _0801C1F8(0, work->tm->baseX, work->tm->baseY, work->tm->baseZ);
                work->tm->flags |= 0x80;
            } else {
                work->tm->flags |= 0x80;
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

    if (work->tm->flags & 0x20) {
        a1 = AllocObjAffine(work->angle, 0x100, 0x100, 1);
        a2 = AllocObjAffine(work->angle2, 0x100, 0x100, 1);
        mode = 0x800;
    } else {
        a1 = AllocObjAffine(work->angle, -0x100, 0x100, 1);
        a2 = AllocObjAffine(work->angle2, -0x100, 0x100, 1);
        mode = 0x801;
    }

    if (gBtlWork->paused != 0) {
        pal = work->palette;
    } else if (work->tm->flags & 1) {
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
    DrawSprite(x, y, work->gfx, work->tiles, pal, a1, 0x800,
               (u16)(-4101 - (s0->y >> 8) * 4));
    WorldToScreen(&x, &y, s1->x, s1->y, s1->z - 0x1900);
    DrawSprite(x, y, work->gfx2, work->tiles, pal, a2, 0x800,
               (u16)(-4100 - (s1->y >> 8) * 4));
    WorldToScreen(&x, &y, s2->x, s2->y, s2->z);
    DrawSprite(x, y, work->gfx3, work->tiles, pal, 0, mode,
               (u16)(-4100 - (s2->y >> 8) * 4));
    WorldToScreen(&x, &y, s3->x, s3->y, s3->z);
    DrawSprite(x, y, work->gfx4, work->tiles, pal, 0, mode,
               (u16)(-4100 - (s3->y >> 8) * 4));
}

void task_bos_tm_body_3(TmBodyWork* work) {
    if ((work->tm->flags & 8) == 0) {
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
