/**
 * bos_dsd.c
 * Darkside Boss
 */

#include "bos2.h"
#include "sprites_bos2.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "card_api.h"
#include "gba/defines.h"
#include "pallet.h"
#include "registration_data.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

void task_bos_dsd_0(DsdWork* work, void* arg) {
    s32 v;
    DsdWork* w;
    BtlObj* p1;
    BtlObj* p2;
    BtlWork* btl;

    work->flags = 0;

    if (arg != NULL) {
        work->flags = DSD_FLAG_IN_EVENT;
    }

    TaskPoolInit(&work->tasks, 4);

    if (work->flags & DSD_FLAG_IN_EVENT) {
        TaskCreate(&work->tasks, &gTaskDescBosDsdMap, NULL);
    } else {
        TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosDsdMap, work);
    }

    work->unk_390 = 0;
    work->unk_392 = 0;

    if (work->flags & DSD_FLAG_IN_EVENT) {
        work->state = 9;
    } else {
        work->state = 1;
    }

    work->attackState = 1;
    work->lastState = 1;
    work->attackCycle = 0;
    work->hitCount = 0;
    work->timer = 0;
    work->stateStep = 0;
    work->stepTimer = 0;
    work->bgFrame = 0;
    work->bgFrameTimer = 0;
    work->hpPhase = 0;
    work->driftX = -51;
    v = (s16)(work->flags & DSD_FLAG_IN_EVENT);

    if (v != 0) {
        work->bodyX = 0xDC00;
        work->bodyY = 0x16800;
        work->bodyZ = -0x6400;
        w = work;
        InitEnemyBtlObj(&w->body[0], &gBosDsdEmyKind, work->bodyX, work->bodyY, work->bodyZ);
        p1 = &w->body[1];
        InitEnemyBtlObj(p1, &gBosDsdEmyKind, 0xDC00, 0x16800, -0x8C00);
        p2 = &w->body[2];
        InitEnemyBtlObj(p2, &gBosDsdEmyKind, 0x9000, 0x16800, 0);
        TaskCreate(&w->tasks, &gTaskDescBosDsdMain, w);
    } else {
        work->bodyX = 0xDC00;
        work->bodyY = 0x16800;
        work->bodyZ = -0x6400;
        w = work;
        InitEnemyBtlObj(&w->body[0], &gBosDsdEmyKind, work->bodyX, work->bodyY, work->bodyZ);
        w->body[0].flags |= BTLOBJ_FLAG_UNHITTABLE;
        w->body[0].flags |= BTLOBJ_FLAG_FACING_LEFT;
        p1 = &w->body[1];
        InitEnemyBtlObj(p1, &gBosDsdEmyKind, 0xDC00, 0x16800, -0x8C00);
        p1->flags |= BTLOBJ_FLAG_FACING_LEFT;
        p1->flags |= 0x400;
        p1->centerHeight = v;
        p1->radiusX = 16;
        p1->radiusY = 16;
        p1->height = 16;
        p2 = &w->body[2];
        InitEnemyBtlObj(p2, &gBosDsdEmyKind, 0x9000, 0x16800, v);
        p2->flags |= (BTLOBJ_FLAG_FACING_LEFT | BTLOBJ_FLAG_UNHITTABLE | BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_PHYSICAL);
        p2->centerHeight = v;
        p2->radiusX = 16;
        p2->radiusY = 16;
        p2->height = 32;
        ColliderInit(&p2->collider, 7, 16, 32);
        ColliderSetPosition(&p2->collider, p2->x, p2->y, p2->z);
        ColliderSetDisabled(&p2->collider, 1);
        SetBtlObjParent(p2, p1);
        gBtlWork->bossPriorityOffset = v;
        SetBtlPaletteFadeExcluded(0, 1);
        SetBattleActorPosition(0x6400, 0x16800, 0);
        SetGimmickTarget(0x2800, 0x16800, 0);
        TaskCreate(&w->tasks, &gTaskDescBosDsdMain, w);
        btl = gBtlWork;
        btl->bossX = w->body[0].x;
        btl->bossY = w->body[0].y;
        btl->bossZ = w->body[0].z;
    }
}

u8 task_bos_dsd_1(DsdWork* work) {
    BtlWork* q;
    BtlObj* a = work->body;
    BtlObj* b = &work->body[1];

    if (work->flags & DSD_FLAG_IN_EVENT) {
        TaskPoolUpdate(&work->tasks);
        return 1;
    }

    switch (UpdateBtlObjReaction(b)) {
    case BTL_REACTION_CARD_ACTION:
        work->state = 2;
        b->flags |= BTLOBJ_FLAG_UNHITTABLE;
        work->stateStep = 0;
        break;
    case BTL_REACTION_HURT:
    case BTL_REACTION_STUNNED:
    case BTL_REACTION_GRAVITY:
        work->flags |= DSD_FLAG_HURT;
        work->timer = 20;
        break;
    case BTL_REACTION_DEFEATED:
    case BTL_REACTION_GRAVITY_DEFEATED:
        work->state = 11;
        work->stateStep = 0;
        break;
    case BTL_REACTION_CARD_BROKEN:
        work->state = 8;
        work->stateStep = 0;
        break;
    }

    if (work->flags & DSD_FLAG_HURT) {
        work->timer--;

        if ((s16)work->timer <= 0) {
            work->hitCount = 0;
            work->flags &= ~DSD_FLAG_HURT;
            LoadPaletteWithEffect(gBosDsdBgPalette, (void*)PLTT, 32);
            ClearBtlObjActionFlags(b);

            if (b->hp > 0) {
                switch (work->state) {
                case 0:
                case 1:
                case 4:
                case 5:
                case 8:
                    break;
                default:
                    work->state = 0;
                    work->stateStep = 0;
                    break;
                }
            }
        }
    }

    if (ConsumeGimmickFlag(0)) {
        work->flags |= DSD_FLAG_PLATFORM_ACTIVE;
        TaskCreate(&work->tasks, &gTaskDescBosDsdIta, work);
    }

    if (work->state == 4) {
        if (gBtlWork->actor->z <= -0x1000) {
            gBtlWork->bossPriorityOffset = -30;
        } else {
            gBtlWork->bossPriorityOffset = 0;
        }
    } else {
        gBtlWork->bossPriorityOffset = 0;
    }

    TaskPoolUpdate(&work->tasks);
    q = gBtlWork;
    q->bossX = a->x;
    q->bossY = a->y;
    q->bossZ = a->z;

    if (work->flags & DSD_FLAG_DEFEAT_DONE) {
        return 0;
    }

    return 1;
}

void task_bos_dsd_2(DsdWork* work) {
    TaskPoolDraw(&work->tasks);
}

void task_bos_dsd_3(DsdWork* work) {
    BtlObj* a;
    BtlObj* b;

    a = &work->body[1];
    b = &work->body[2];
    TaskPoolDestroy(&work->tasks);
    ColliderUnregister(&work->body[2].collider);
    ReleaseEnemyBtlObj(&work->body[0]);
    ReleaseEnemyBtlObj(a);
    ReleaseEnemyBtlObj(b);
}

const EmyKind gBosDsdEmyKind = { 38, 1000, 16, 16, 40, 60, 0 };

TaskDesc gTaskDescBosDsd = {
    "task_bos_dsd",
    (TaskInitFunc)task_bos_dsd_0,
    (TaskUpdateFunc)task_bos_dsd_1,
    (TaskDrawFunc)task_bos_dsd_2,
    (TaskDestroyFunc)task_bos_dsd_3,
    sizeof(DsdWork),
};
