#include "bos6.h"
#include "sprites_bos6.h"

const s16 gBosPcFltSine[256] = {
    0, 6, 12, 18, 25, 31, 37, 43, 49, 56, 62, 68, 74, 80, 86, 92,
    97, 103, 109, 115, 120, 126, 131, 136, 142, 147, 152, 157, 162, 167, 171, 176,
    181, 185, 189, 193, 197, 201, 205, 209, 212, 216, 219, 222, 225, 228, 231, 234,
    236, 238, 241, 243, 244, 246, 248, 249, 251, 252, 253, 254, 254, 255, 255, 255,
    256, 255, 255, 255, 254, 254, 253, 252, 251, 249, 248, 246, 244, 243, 241, 238,
    236, 234, 231, 228, 225, 222, 219, 216, 212, 209, 205, 201, 197, 193, 189, 185,
    181, 176, 171, 167, 162, 157, 152, 147, 142, 136, 131, 126, 120, 115, 109, 103,
    97, 92, 86, 80, 74, 68, 62, 56, 49, 43, 37, 31, 25, 18, 12, 6,
    0, -6, -12, -18, -25, -31, -37, -43, -49, -56, -62, -68, -74, -80, -86, -92,
    -97, -103, -109, -115, -120, -126, -131, -136, -142, -147, -152, -157, -162, -167, -171, -176,
    -181, -185, -189, -193, -197, -201, -205, -209, -212, -216, -219, -222, -225, -228, -231, -234,
    -236, -238, -241, -243, -244, -246, -248, -249, -251, -252, -253, -254, -254, -255, -255, -255,
    -256, -255, -255, -255, -254, -254, -253, -252, -251, -249, -248, -246, -244, -243, -241, -238,
    -236, -234, -231, -228, -225, -222, -219, -216, -212, -209, -205, -201, -197, -193, -189, -185,
    -181, -176, -171, -167, -162, -157, -152, -147, -142, -136, -131, -126, -120, -115, -109, -103,
    -97, -92, -86, -80, -74, -68, -62, -56, -49, -43, -37, -31, -25, -18, -12, -6,
};

const s16 gBosPcFltCosine[256] = {
    256, 255, 255, 255, 254, 254, 253, 252, 251, 249, 248, 246, 244, 243, 241, 238,
    236, 234, 231, 228, 225, 222, 219, 216, 212, 209, 205, 201, 197, 193, 189, 185,
    181, 176, 171, 167, 162, 157, 152, 147, 142, 136, 131, 126, 120, 115, 109, 103,
    97, 92, 86, 80, 74, 68, 62, 56, 49, 43, 37, 31, 25, 18, 12, 6,
    0, -6, -12, -18, -25, -31, -37, -43, -49, -56, -62, -68, -74, -80, -86, -92,
    -97, -103, -109, -115, -120, -126, -131, -136, -142, -147, -152, -157, -162, -167, -171, -176,
    -181, -185, -189, -193, -197, -201, -205, -209, -212, -216, -219, -222, -225, -228, -231, -234,
    -236, -238, -241, -243, -244, -246, -248, -249, -251, -252, -253, -254, -254, -255, -255, -255,
    -256, -255, -255, -255, -254, -254, -253, -252, -251, -249, -248, -246, -244, -243, -241, -238,
    -236, -234, -231, -228, -225, -222, -219, -216, -212, -209, -205, -201, -197, -193, -189, -185,
    -181, -176, -171, -167, -162, -157, -152, -147, -142, -136, -131, -126, -120, -115, -109, -103,
    -97, -92, -86, -80, -74, -68, -62, -56, -49, -43, -37, -31, -25, -18, -12, -6,
    0, 6, 12, 18, 25, 31, 37, 43, 49, 56, 62, 68, 74, 80, 86, 92,
    97, 103, 109, 115, 120, 126, 131, 136, 142, 147, 152, 157, 162, 167, 171, 176,
    181, 185, 189, 193, 197, 201, 205, 209, 212, 216, 219, 222, 225, 228, 231, 234,
    236, 238, 241, 243, 244, 246, 248, 249, 251, 252, 253, 254, 254, 255, 255, 255,
};

const PcFltFrameDef gBosPcFltFrameDefs[12] = {
    { -16, -16, 0, 0 },
    { -16, 0, 24, 11 },
    { -16, 2, 24, 13 },
    { -16, 4, 21, 14 },
    { -16, 6, 16, 15 },
    { -16, 7, 12, 0 },
    { -10, 3, 16, 17 },
    { -10, 4, 16, 18 },
    { -10, 5, 14, 19 },
    { -10, 6, 12, 20 },
    { -10, 7, 8, 0 },
    { -16, 1, 24, 12 },
};

TaskDesc gTaskDescBosPcFlt = {
    "task_bos_pc_flt",
    (TaskInitFunc)task_bos_pc_flt_0,
    (TaskUpdateFunc)task_bos_pc_flt_1,
    (TaskDrawFunc)task_bos_pc_flt_2,
    (TaskDestroyFunc)task_bos_pc_flt_3,
    sizeof(PcFltWork),
};

s32 BosPcFltSquare(s32 x) {
    return x * x;
}

s32 BosPcFltSquare2(s32 x) {
    return x * x;
}

void BosPcFltGetPosition(Task* task, s32* a, s32* b, s32* c) {
    PcFltWork* work;

    work = task->work;
    *a = work->x;
    *b = work->y;
    *c = work->z;
}

u8 BosPcFltIsSubmerged(Task* task) {
    PcFltWork* work;

    work = task->work;
    if (work->state == 8 && AnimGetGfxIndex(&work->anim) == 0) {
        return 1;
    }
    return 0;
}

u8 BosPcFltIsPlayerOn(Task* task) {
    PcFltWork* work;
    u8 r;

    work = task->work;
    r = 0;
    if (IsPlayerOnPlatform(&work->collider) == 1) {
        r = 1;
    }
    return r;
}

void BosPcFltUpdateFloat(PcFltWork* work) {
    AnimState* anim;

    work->z = work->baseZ;
    if (work->shared->unk_02 == 0) {
        if (IsPlayerOnPlatform(&work->collider) == 1) {
            work->z += 0x200;
            if (work->playerOnPlatform != 1) {
                work->playerOnPlatform = 1;
                AnimChange(&work->anim, 8, 0);
            }
            work->sinkTimer -= 2;
            if (work->sinkTimer < 0) {
                work->state = 1;
                work->playerOnPlatform = 0;
                work->timer = 0;
                work->sinkTimer = 360;
                AnimChange(&work->anim, 7, 0);
            }
        } else {
            if (work->playerOnPlatform == 1) {
                work->sinkTimer -= 120;
                AnimChange(&work->anim, 1, 0);
            } else {
                work->sinkTimer += 1;
                if (work->sinkTimer > 720) {
                    work->sinkTimer = 720;
                }
            }
            work->playerOnPlatform = 0;
        }
    } else {
        work->state = 5;
        work->playerOnPlatform = 0;
        work->timer = 0;
        AnimChange(&work->anim, 5, 0);
    }
}

void BosPcFltUpdateSink(PcFltWork* work) {
    AnimState* anim;

    work->z = work->baseZ;
    anim = &work->anim;
    if (AnimIsFinished(anim) == 1) {
        work->state = 2;
        work->timer = 0;
        AnimReset(anim);
        AnimChange(anim, 3, 0);
    }
}

void BosPcFltUpdateSinkEnd(PcFltWork* work) {
    work->z = work->baseZ;
    if (AnimIsFinished(&work->anim) == 1) {
        work->state = 3;
        work->playerOnPlatform = 0;
        work->timer = 60;
    }
}

void BosPcFltUpdateSubmerged(PcFltWork* work) {
    work->z = work->baseZ + 0x1000;
    work->timer -= 1;
    if (work->timer < 0) {
        if (work->shared->unk_02 == 0) {
            work->state = 4;
            work->timer = 0;
            AnimChange(&work->anim, 4, 0);
        } else {
            work->state = 6;
            work->timer = 0;
            AnimChange(&work->anim, 9, 0);
        }
    }
}

void BosPcFltUpdateRise(PcFltWork* work) {
    AnimState* anim;

    work->z = work->baseZ;
    anim = &work->anim;
    if (AnimIsFinished(anim) == 1) {
        work->state = 0;
        AnimReset(anim);
        AnimChange(anim, 1, 0);
    }
}

void func_0810B9DC(PcFltWork* work) {
    AnimState* anim;

    work->z = work->baseZ;
    anim = &work->anim;
    if (AnimIsFinished(anim) == 1) {
        work->state = 6;
        work->timer = 0;
        AnimReset(anim);
        AnimChange(anim, 2, 0);
    }
}

void func_0810BA14(PcFltWork* work) {
    work->z = work->baseZ;
    if (work->shared->unk_02 == 0) {
        work->state = 7;
        work->timer = 0;
        AnimChange(&work->anim, 6, 0);
    }
}

void func_0810BA3C(PcFltWork* work) {
    AnimState* anim;

    work->z = work->baseZ;
    anim = &work->anim;
    if (AnimIsFinished(anim) == 1) {
        work->state = 0;
        work->timer = 0;
        AnimReset(anim);
        AnimChange(anim, 1, 0);
    }
}

void BosPcFltUpdateGimmick(PcFltWork* work) {
    AnimState* anim;
    u8 fin;
    u16 id;

    work->z = work->baseZ;
    if (work->timer == 0) {
        anim = &work->anim;
        fin = AnimIsFinished(anim);
        if (fin == 1) {
            id = AnimGetGfxIndex(anim);
            if (id != 0) {
                AnimReset(anim);
                AnimChange(anim, gBosPcFltFrameDefs[id].nextAnim, 0);
            } else {
                work->timer = 1;
            }
        }
    } else if (work->shared->gimmickTimer <= 119) {
        work->state = 3;
        work->playerOnPlatform = 0;
        work->timer = work->index * 30;
    }
}

void BosPcFltUpdateMotion(PcFltWork* work) {
    s32 f;

    if ((gBtlWork->flags & 0x20000000) || (gBtlWork->flags & 0x40) ||
        work->shared->fltStopTimer > 0) {
        f = -1;
    } else {
        f = work->unk_007;
    }
    if (work->state != 8 && work->shared->gimmickTimer > 0x257) {
        work->state = 8;
        work->playerOnPlatform = 0;
        work->timer = 0;
        work->sinkTimer = 360;
    }
    if (work->shared->unk_02 == 0) {
        if (work->centerX > 0xF400) {
            work->centerX -= 32;
        }
        if (work->centerY > 0x15400) {
            work->centerY -= 32;
        }
        if (work->radiusX <= 0x3FFF) {
            work->radiusX += 64;
        }
        if (work->radiusY <= 0x1FFF) {
            work->radiusY += 32;
        }
    } else {
        if (work->centerX <= 0x103FF) {
            work->centerX += 32;
        }
        if (work->centerY <= 0x153FF) {
            work->centerY += 32;
        }
        if (work->radiusX > 0x3400) {
            work->radiusX -= 64;
        }
        if (work->radiusY > 0x1E00) {
            work->radiusY -= 32;
        }
    }
    if (f >= 0) {
        work->x = (((gBosPcFltCosine[work->orbitAngle >> 8] * (work->radiusX >> 8)) >> 8) + (work->centerX >> 8)) << 8;
        work->y = (((gBosPcFltSine[work->orbitAngle >> 8] * (work->radiusY >> 8)) >> 8) + (work->centerY >> 8)) << 8;
        work->orbitAngle = work->orbitAngle - (((work->shared->hpRatio * 3) << 4) / 256 - 112);
    }
    switch (work->state) {
    case 0:
        BosPcFltUpdateFloat(work);
        break;
    case 1:
        BosPcFltUpdateSink(work);
        break;
    case 2:
        BosPcFltUpdateSinkEnd(work);
        break;
    case 3:
        BosPcFltUpdateSubmerged(work);
        break;
    case 4:
        BosPcFltUpdateRise(work);
        break;
    case 5:
        func_0810B9DC(work);
        break;
    case 6:
        func_0810BA14(work);
        break;
    case 7:
        func_0810BA3C(work);
        break;
    case 8:
        BosPcFltUpdateGimmick(work);
        break;
    }
    if (IsPlayerOnPlatform(&work->collider) == 1) {
        work->playerOnPlatform = 1;
    }
}

void BosPcFltSyncCollider(PcFltWork* work) {
    Collider* p;

    p = &work->collider;
    ColliderSetPosition(p, work->x, work->y + 0x200, 0);
    ColliderSetHeight(p, -work->z >> 8);
    if (work->z > 0) {
        ColliderSetDisabled(p, 1);
    } else {
        ColliderSetDisabled(p, 0);
    }
}

void task_bos_pc_flt_0(PcFltWork* work, PcFltInit* arg) {
    AnimState* anim;

    work->tiles = LoadObjTiles(gUnk_09CB8F54, 0xDC0);
    work->palette = LoadObjPalette(gUnk_09D693D4, 0x60);
    anim = &work->anim;
    AnimInit(anim, gUnk_09EFBBEC, gUnk_09EFBBBC);
    AnimStart(anim, 1, 0);
    ColliderInit(&work->collider, 7, 26, 4);
    work->playerOnPlatform = 0;
    work->timer = 0;
    work->index = arg->index;
    work->state = 0;
    work->unk_006 = 0;
    work->unk_007 = 0;
    work->orbitAngle = (arg->index << 14) + arg->angle;
    work->centerX = 0xF400;
    work->centerY = 0x15400;
    work->radiusX = 0x4000;
    work->radiusY = 0x2000;
    work->sinkTimer = 720;
    work->baseX = arg->x;
    work->baseY = arg->y;
    work->baseZ = arg->z;
    work->shared = arg->shared;
    BosPcFltUpdateMotion(work);
    BosPcFltSyncCollider(work);
}

u8 task_bos_pc_flt_1(PcFltWork* work) {
    AnimState* anim;
    u16 id;

    BosPcFltUpdateMotion(work);
    anim = &work->anim;
    AnimUpdate(anim);
    id = AnimGetGfxIndex(anim);
    if (id == 0) {
        work->z += 0x1000;
    } else {
        work->z += gBosPcFltFrameDefs[id].z << 8;
        ColliderSetRadius(&work->collider, gBosPcFltFrameDefs[id].radius);
    }
    BosPcFltSyncCollider(work);
    work->unk_007 = work->shared->hpRatio & 1;
    return 1;
}

void task_bos_pc_flt_2(PcFltWork* work) {
    s16 sx;
    s16 sy;
    u16 id;
    u16 g;
    u16 h;

    if (work->z <= 0) {
        id = AnimGetGfxIndex(&work->anim);
        WorldToScreen(&sx, &sy, work->x,
            work->y + (gBosPcFltFrameDefs[id].drawY << 8), work->z);
        if (gBtlWork->platform != 0) {
            g = GetBattleSpritePriorityFlags(work->y + (gBosPcFltFrameDefs[id].drawY << 8));
            h = (-0x1004 - ((work->y >> 8) << 2)) | 3;
        } else {
            g = GetBattleSpritePriorityFlags(work->y);
            h = -0x1004 - ((work->y >> 8) << 2);
        }
        DrawSprite(sx, sy, AnimGetGfx(&work->anim), work->tiles,
                   work->palette, 0, g, h);
    }
}

void task_bos_pc_flt_3(PcFltWork* work) {
    ColliderUnregister(&work->collider);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}
