/**
 * bos_lst_bit.c
 * Marluxia Final Form Laser Bits
 */

#include "bos7.h"
#include "sprites_bos7.h"
#include "sprites_bos6.h"
#include "boss_lst_data.h"
#include "songs.h"
#include <stdlib.h>
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "bos7_api.h"
#include "btl_collision.h"
#include "engine_math.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "registration_data.h"
#include "taskpool.h"
#include "types.h"

static const EmyKind sBosLstBitEmyKind = { 0, 1, 8, 8, 0, 128, 0 };

static const s32 sBosLstBitTanTable[32] = {
    6, 12, 18, 25, 31, 37, 44, 50, 57, 64, 70, 77, 84, 91, 98, 106,
    113, 121, 128, 136, 145, 153, 162, 171, 180, 189, 199, 210, 220, 232, 243, 256,
};

static const s32 sBosLstBitHoverY[3] = { 0, -8, 8 };

static const s32 sBosLstBitBobZ[16] = { -1, -2, -3, -4, -5, -6, -7, -8, -7, -6, -5, -4, -3, -2, -1, 0 };

static LstAnimSet sLstAnimSets[4] = {
    { 5, 0, 4, 5 },
    { 5, 0, 4, 12 },
    { 5, 0, 4, 13 },
    { 5, 0, 4, 14 },
};

TaskDesc gTaskDescBosLstBit = {
    "task_bos_lst_bit",
    (TaskInitFunc)task_bos_lst_bit_0,
    (TaskUpdateFunc)task_bos_lst_bit_1,
    (TaskDrawFunc)task_bos_lst_bit_2,
    (TaskDestroyFunc)task_bos_lst_bit_3,
    sizeof(LstState),
};

s32 BosLstBitSquare(s32 x) {
    return x * x;
}

s32 BosLstBitSquare2(s32 x) {
    return x * x;
}

u8 BosLstBitSpawnFal(LstState* work, s32 kind) {
    LstFalArg arg;
    u8 result;

    result = 0;

    if (work->kind != 0) {
        return 0;
    }

    if ((s16)*work->falCount <= 31) {
        arg.kind = 0;

        if (kind == 1) {
            arg.x = work->targetX;
            arg.y = work->targetY;
            arg.z = work->targetZ;
        } else {
            arg.x = work->x;
            arg.y = work->y;
            arg.z = work->z;
        }

        arg.facing = *work->facing;
        arg.falCount = work->falCount;
        TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosLstFal, &arg);
        result = 1;
    }

    return result;
}

u8 BosLstBitIsAlive(Task* task) {
    LstState* s;
    u8 result;

    s = task->work;
    result = 1;

    if (s->obj.hp <= 0 || s->state == 6) {
        result = 0;
    }

    return result;
}

u8 BosLstBitHasShots(Task* task) {
    LstState* s;
    u8 result;

    s = task->work;
    result = BosLstBitIsAlive(task);

    if (result == 1 && s->shots <= 0) {
        result = 0;
    }

    return result;
}

#ifdef VERSION_EU
u8 BosLstBitIsScaling(Task* task) {
    LstState* s;
    u8 result;
    s = task->work;
    result = BosLstBitIsAlive(task);

    if (result == 1 && (s->scaleX == 0x100 || s->scaleY == 0x100)) {
        result = 0;
    }

    return result;
}
#endif

s16 BosLstBitMarkFirstAlive(Task* task, s16 a) {
    LstState* s;

    s = task->work;

    if (BosLstBitIsAlive(task) == 1 && a == 0) {
        s->index = a;
        a = 1;
    }

    return a;
}

void BosLstBitStartHover(Task* task) {
    LstState* s;
    u16 zero;

    s = task->work;
    zero = 0;
    s->state = 1;
    s->unk_004 = zero;
    s->timer = zero;
    s->unk_008 = zero;
}

void BosLstBitStartFiring(Task* task, s16 a) {
    LstState* s;
    u16 zero;

    s = task->work;
    zero = 0;
    s->state = 2;
    s->unk_004 = zero;
    s->timer = zero;
    s->unk_008 = zero;
    s->shots = a;
}

void BosLstBitStartReturn(Task* task) {
    LstState* s;
    u16 zero;

    s = task->work;

#ifdef VERSION_EU
    if ((u16)(s->state - 5) > 1) {
#endif
        zero = 0;
        s->state = 5;
        s->unk_004 = zero;
        s->timer = zero;
        s->unk_008 = zero;
#ifdef VERSION_EU
    }
#endif
}

u8 BosLstBitInterrupt(Task* task, u8 a) {
    LstState* s;
    u8 result;

    s = task->work;
    result = 0;
    BosLstLsrStop(s->lsrTask);
    BosLstLsrStop(s->lsrTask2);
    BosLstLsrStop(s->lsrTask3);
    s->shots = 0;

    if (s->state >= 5 && s->state <= 6) {
        return 0;
    }

    if (a == 1 && s->index == 0) {
        s->obj.hp = 0;
        SetBtlObjUnhittable(&s->obj, 1);
        BosLstBitSpawnFal(s, 0);
        BosLstBitSpawnFal(s, 0);
        result = 1;
    }

#ifdef VERSION_EU
    AnimReset(&s->anim);
    AnimChange(&s->anim, sLstAnimSets[s->animSet].idleAnim, ANIM_FLAG_LOOP);

    if (s->state != 0 && s->state != 5) {
        s->state = 7;
        s->unk_004 = 0;
        s->timer = 0;
        s->unk_008 = 0;

        if (gBtlWork->actor->z > -0xC000) {
            s->targetZ = -0x6000;
        } else {
            s->targetZ = gBtlWork->bossZ - 0x5000;
        }
    }
#else
    s->state = 7;
    s->unk_004 = 0;
    s->timer = 0;
    s->unk_008 = 0;
#endif

    return result;
}

s32 BosLstBitAtanLookup(s32 a, s32 b) {
    s32 v;
    s32 step;
    s32 i;

    if (a == 0 || b == 0) {
        return 0;
    }

    v = (b << 8) / a;

    if (v <= sBosLstBitTanTable[0]) {
        return 0;
    }

    step = 8;
    i = 16;

    while (step != 0 && v != sBosLstBitTanTable[i]) {
        if (v < sBosLstBitTanTable[i]) {
            i -= step;
        } else {
            i += step;
        }

        step /= 2;
    }

    return i;
}

s32 BosLstBitAngleBetween(s32 x0, s32 y0, s32 x1, s32 y1) {
    s32 dx;
    s32 dy;
    s32 a;

    dx = x0 - x1;
    dy = y0 - y1;

    if (abs(dx) >= abs(dy)) {
        a = BosLstBitAtanLookup(abs(dx), abs(dy));
    } else {
        a = 63 - BosLstBitAtanLookup(abs(dy), abs(dx));
    }

    if (dx >= 0) {
        if (dy >= 0) {
            a = 63 - a;
            a = a + 192;
        }
    } else if (dy >= 0) {
        a = a + 128;
    } else {
        a = 63 - a;
        a = a + 64;
    }

    a = 255 - a;
    a = a + 65;

    return a & 255;
}

s32 BosLstBitAngleDiff(u8 a, u8 b) {
    s32 d;

    if (a > b) {
        d = a - b;

        if (d > 128) {
            d = d - 256;
        }

        return -d;
    }

    d = b - a;

    if (d > 128) {
        d = d - 256;
    }

    return d;
}

void task_bos_lst_bit_0(LstState* work, LstBitArg* arg) {
    LstLsrArg sub;
    BtlObj* p;
    TaskPool* pool;

    work->animSet = 0;
    work->state = 0;
    work->unk_004 = 0;
    work->timer = 0;
    work->unk_008 = 0;
    work->hurtTimer = 0;
    work->bobFrame = 0;
    work->kind = arg->kind;
    work->index = arg->index;
    work->shots = 0;
    work->falTimer = GetRandom() % 32;
    work->facing = arg->facing;
    work->falCount = arg->falCount;
    work->unk_024 = arg->unk_10;
    work->x = arg->x;
    work->y = arg->y;
    work->z = arg->z;
    work->startX = arg->x;
    work->startY = arg->y;
    work->startZ = arg->z;
    work->bobZ = 0;
    work->targetX = arg->x2;
    work->targetY = arg->y2;
    work->targetZ = arg->z2;
    p = gBtlWork->actor;
    work->actorX = p->x;
    work->actorY = p->y;
    work->actorZ = p->z;
    work->angle = arg->index << 7;
    work->scaleX = 2;
    work->scaleY = 2;
    work->tiles = LoadObjTiles(gUnk_09CD0334, 0x900);
    work->palette = LoadObjPalette(gUnk_09D69594, 0x60);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 0x20);
    AnimInit(&work->anim, gUnk_09EFBF18, gUnk_09EFBEC4);
    AnimStart(&work->anim, sLstAnimSets[work->animSet].idleAnim, ANIM_FLAG_LOOP);
    InitEnemyBtlObj(&work->obj, &sBosLstBitEmyKind, work->x, work->y, work->z);
    pool = &work->tasks;
    TaskPoolInit(pool, 4);
    sub.kind = work->kind;
    sub.facing = work->facing;
    sub.falCount = work->falCount;
    work->lsrTask = TaskCreate(pool, &gTaskDescBosLstLsr, &sub);
    work->lsrTask2 = TaskCreate(pool, &gTaskDescBosLstLsr, &sub);
    work->lsrTask3 = TaskCreate(pool, &gTaskDescBosLstLsr, &sub);
}

void BosLstBitHandleHit(LstState* work) {
    BtlObj* obj;

    obj = &work->obj;

    switch (UpdateBtlObjReaction(obj)) {
    case BTL_REACTION_HURT:
    case BTL_REACTION_STUNNED:
    case BTL_REACTION_GRAVITY:
        work->hurtTimer = 20;
        BosLstBitSpawnFal(work, 0);
        ClearBtlObjActionFlags(obj);
        break;
    case BTL_REACTION_DEFEATED:
        SetBtlObjUnhittable(&work->obj, 1);
        BosLstBitSpawnFal(work, 0);
        BosLstBitSpawnFal(work, 0);
        ClearBtlObjActionFlags(obj);
        break;
    case BTL_REACTION_CARD_ACTION:
        ClearBtlObjActionFlags(obj);
        break;
    case BTL_REACTION_CARD_BROKEN:
        ClearBtlObjActionFlags(obj);
        break;
    case BTL_REACTION_HEALED:
        break;
    }
}

u8 task_bos_lst_bit_1(LstState* work) {
    Vec3 a;
    Vec3 b;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    BtlObj* p;
    s32 d;
    u8 dir;
    BtlObj* obj;

    obj = &work->obj;

    if (obj->hp <= 0) {
        SetBtlObjUnhittable(obj, 1);
        return 1;
    }

    BosLstBitHandleHit(work);

    switch (work->state) {
    case 0:
        ApproachValueHalfSteps(&work->x, work->targetX, 20);
        ApproachValueHalfSteps(&work->y, work->targetY, 20);
        ApproachValueHalfSteps(&work->z, work->targetZ, 20);
        ApproachValueHalfSteps(&work->scaleX, 0x100, 32);
        ApproachValueHalfSteps(&work->scaleY, 0x100, 32);
        work->timer++;

        if (work->timer > 29) {
            work->state = 1;
            work->unk_004 = 0;
            work->timer = 0;
            work->unk_008 = 0;
            work->scaleX = 0x100;
            work->scaleY = 0x100;
        }

        break;
    case 1:
        if (work->timer == 0) {
            if (gBtlWork->flags & BTL_FLAG_PLAYER_OFFSCREEN) {
                work->targetX = (GetRandom() % 113 << 8) + 0xC000;
#ifndef VERSION_EU
                work->targetY = gBtlWork->actor->y;
#endif
            } else if (work->kind == 0) {
                work->targetX = (GetRandom() % 113 << 8) + 0xC000;
                work->targetY = gBtlWork->actor->y + (sBosLstBitHoverY[work->index] << 8);
            } else {
                work->targetX = gBtlWork->actor->x;
                work->targetY = gBtlWork->actor->y;
            }

            AnimReset(&work->anim);
            AnimChange(&work->anim, sLstAnimSets[work->animSet].idleAnim, ANIM_FLAG_LOOP);
        }

        if (!(gBtlWork->flags & BTL_FLAG_PLAYER_OFFSCREEN)) {
            if (gBtlWork->actor->z > -0xC000) {
                work->targetZ = -0x6000;
            } else {
                work->targetZ = gBtlWork->bossZ - 0x5000;
            }
        }

        work->timer++;

        if ((work->falTimer & 31) == 0) {
            BosLstBitSpawnFal(work, 0);
        }

        ApproachValueHalfSteps(&work->x, work->targetX, 20);
        ApproachValueHalfSteps(&work->y, work->targetY, 20);
        ApproachValueHalfSteps(&work->z, work->targetZ, 20);
        break;
    case 2:
        if (work->timer == 0) {
            work->targetX = gBtlWork->actor->x;
            work->targetY = gBtlWork->actor->y;

            if (gBtlWork->actor->z > -0xC000) {
                work->targetZ = 0;
            } else {
                work->targetZ = gBtlWork->bossZ;
            }

            AnimReset(&work->anim);
            AnimChange(&work->anim, sLstAnimSets[work->animSet].chargeAnim, 0);
        }

        work->timer++;

        if (AnimGetId(&work->anim) == (s16)sLstAnimSets[work->animSet].chargeAnim && AnimIsFinished(&work->anim) == 1) {
            work->state = 3;
            work->timer = 0;
            work->unk_018 = 1;
            work->fireAngle = work->aimAngle;
            work->fireX = work->x + work->orbitX;
            work->fireY = work->y + work->orbitY;
            work->fireZ = work->z + work->orbitZ;
            m4aSongNumStart(SONG_SND_708);
            AnimReset(&work->anim);
            AnimChange(&work->anim, sLstAnimSets[work->animSet].idleAnim, ANIM_FLAG_LOOP);
        }

        break;
    case 3:
        if (work->timer == 0) {
            if (!BosLstLsrIsFiring(work->lsrTask)) {
                a.x = work->fireX;
                a.y = work->fireY;
                a.z = work->fireZ;
                b.x = work->targetX;
                b.y = work->targetY;
                b.z = work->targetZ;
                BosLstLsrFire(work->lsrTask, &a, &b, work->fireAngle, 0);
            }

            work->timer++;
        } else {
            work->targetX = gBtlWork->actor->x;
            work->targetY = gBtlWork->actor->y;

            if (gBtlWork->actor->z > -0xC000) {
                work->targetZ = 0;
            } else {
                work->targetZ = gBtlWork->bossZ;
            }

            if (!BosLstLsrIsFiring(work->lsrTask)) {
                if (work->shots > 1) {
                    work->state = 2;
                    work->timer = 0;
                    work->shots--;
                } else {
                    work->shots = 0;
                }
            }
        }

        break;
    case 4:
        if (work->timer > 14) {
            break;
        }

        ApplyAttackBox(0x10D, work->targetX, work->targetY, work->targetZ, 8, 8, 8);

        if ((work->timer & 3) == 0) {
            BosLstBitSpawnFal(work, 1);
        }

        if (abs(work->targetX - gBtlWork->actor->x) < 0x180) {
            work->targetX = gBtlWork->actor->x;
        } else if (work->targetX > gBtlWork->actor->x) {
            work->targetX = work->targetX - 0x180;
        } else if (work->targetX < gBtlWork->actor->x) {
            work->targetX = work->targetX + 0x180;
        }

        if (abs(work->targetY - gBtlWork->actor->y) < 0x180) {
            work->targetY = gBtlWork->actor->y;
        } else if (work->targetY > gBtlWork->actor->y) {
            work->targetY = work->targetY - 0x180;
        } else if (work->targetY < gBtlWork->actor->y) {
            work->targetY = work->targetY + 0x180;
        }

        work->timer++;
        break;
    case 5:
        work->targetX = gBtlWork->bossX;
        work->targetY = gBtlWork->bossY - 0x1400;
        work->targetZ = gBtlWork->bossZ;
        ApproachValueHalfSteps(&work->x, work->targetX, 16);
        ApproachValueHalfSteps(&work->y, work->targetY, 16);
        ApproachValueHalfSteps(&work->z, work->targetZ, 16);
        ApproachValueHalfSteps(&work->scaleX, 0x200, 16);
        ApproachValueHalfSteps(&work->scaleY, 2, 16);
        work->timer++;

        if (work->timer > 59) {
            work->state = 6;
            work->unk_004 = 0;
            work->timer = 0;
            work->unk_008 = 0;
        }

        break;
    case 6:
        work->scaleX = 0x100;
        work->scaleY = 0x100;
        AnimReset(&work->anim);
        AnimChange(&work->anim, 4, ANIM_FLAG_LOOP);
        break;
    case 7:
        AnimChange(&work->anim, sLstAnimSets[work->animSet].idleAnim, ANIM_FLAG_LOOP);
        break;
    }

    WorldToScreen(&x1, &y1, work->x + work->orbitX, work->y + work->orbitY,
                  work->z + work->orbitZ);

    if (gBtlWork->flags & BTL_FLAG_PLAYER_OFFSCREEN) {
        WorldToScreen(&x2, &y2, work->actorX, work->actorY, work->actorZ);
        work->angle += 2;
    } else {
        if (work->kind == 0) {
            switch (work->state) {
            case 2:
            case 3:
                work->angle += 2;
                WorldToScreen(&x2, &y2, work->targetX, work->targetY, work->targetZ);
                break;
            default:
                work->angle += 2;
                WorldToScreen(&x2, &y2, gBtlWork->actor->x, gBtlWork->actor->y,
                              gBtlWork->actor->z);
                break;
            }
        } else {
            switch (work->state) {
            case 2:
            case 3:
            case 4:
                work->angle += 6;
                WorldToScreen(&x2, &y2, work->targetX, work->targetY, work->targetZ);
                break;
            default:
                work->angle += 2;
                WorldToScreen(&x2, &y2, gBtlWork->actor->x, gBtlWork->actor->y,
                              gBtlWork->actor->z);
                break;
            }
        }

        work->actorX = gBtlWork->actor->x;
        work->actorY = gBtlWork->actor->y;
        work->actorZ = gBtlWork->actor->z;
    }

    work->angle &= 0xFF;

    if (work->kind == 0) {
        work->orbitX = (-gSineTable[(work->angle & 0xFF) + 64] * 3 >> 6) << 8;
        work->orbitY = (gSineTable[work->angle & 0xFF] * 3 >> 6) << 8;
        work->orbitZ = work->orbitZ / 2;
    } else if (work->index == 0) {
        work->orbitX = work->orbitX / 2;
        work->orbitY = work->orbitY / 2;
        work->orbitZ = work->orbitZ / 2;
    } else {
        work->orbitX = (-gSineTable[(work->angle & 0xFF) + 64] >> 3) << 8;
        work->orbitY = (gSineTable[work->angle & 0xFF] * 3 >> 6) << 8;
        work->orbitZ = 0x800;
    }

    work->bobZ = sBosLstBitBobZ[(work->bobFrame >> 2) & 15] << 8;
    dir = BosLstBitAngleBetween(x2, y2, x1, y1);
    d = BosLstBitAngleDiff(work->aimAngle, dir);

    if (abs(d) <= 1) {
        work->aimAngle = dir;
    } else {
        work->aimAngle += d / 2;
    }

    obj->x = work->x + work->orbitX;
    obj->y = work->y + work->orbitY;
    obj->z = work->z + work->orbitZ + work->bobZ;
    AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    work->falTimer++;
    work->bobFrame++;

    return 1;
}

void task_bos_lst_bit_2(LstState* work) {
    s16 x;
    s16 y;
    void* pal;
    ObjAffine* affine;
    u16 prio;
    u16 z;
    void* gfx;

    if (work->obj.hp <= 0) {
        return;
    }

    pal = work->palette;

    if ((work->hurtTimer & 1) != 0) {
        pal = work->palette2;
    }

    if (work->hurtTimer > 0) {
        work->hurtTimer = work->hurtTimer - 1;
    }

    WorldToScreen(&x, &y, work->x + work->orbitX, work->y + work->orbitY,
                  work->z + work->orbitZ + work->bobZ);
    prio = GetBattleSpritePriorityFlags(work->y);
    z = -0x1004 - (work->y >> 8) * 4;
    affine = AllocObjAffine(work->aimAngle, work->scaleX, work->scaleY, 0);
    gfx = AnimGetGfx(&work->anim);
    DrawSprite(x, y, gfx, work->tiles, pal, affine, prio, z);
    TaskPoolDraw(&work->tasks);
}

void task_bos_lst_bit_3(LstBitWork* work) {
    ReleaseEnemyBtlObj(&work->obj);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
    TaskPoolDestroy(&work->tasks);
}
