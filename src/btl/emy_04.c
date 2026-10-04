/**
 * emy_04.c
 * Green Requiem Enemy
 */

#include "task_descriptors.h"
#include "emy.h"
#include "sprites_emy.h"
#include "enemy_common.h"
#include "emy_tasks.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_effect.h"
#include "enemy_types.h"
#include "listpool.h"
#include "mode_chkobj_assets.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

static const AnimDef sEmy04CommonAnimDefs[3] = {
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 0, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 3, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 2, { 0, 0, 0 } },
};

static const AnimDef sEmy04AnimDef = { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 4, { 0, 0, 0 } };

static const EmyDef sEmy04Def = { gEmy04Palette, sEmy04CommonAnimDefs, 332, 130, 20, 20, 0, 0, 0, 200, 0, { 4, 27, 24, 12, 4, 100, EMY_KIND_FLAG_NO_ENEMY_COLLISION } };

TaskDesc gTaskDescEmy04 = {
    "task_emy_04",
    (TaskInitFunc)task_emy_04_0,
    (TaskUpdateFunc)task_emy_04_1,
    (TaskDrawFunc)task_emy_04_2,
    (TaskDestroyFunc)task_emy_04_3,
    sizeof(Emy04Work),
};

void task_emy_04_0(Emy04Work* work, void* obj) {
    EmyInit(&work->base, &sEmy04Def, obj);
    work->base.idleState = 7;
    work->unk_184 = 0;
    work->healCount = 0;
}

u8 task_emy_04_1(Emy04Work* work) {
    Emy04Work* w;
    BtlObj* act;
    BtlObj* p;
    BtlObj* best;
    s16 bestv;

    w = work;
    act = &work->base.actor;

    if (EmyUpdateReaction(&work->base)) {
        work->base.state = 0x12;
    }

    switch (work->base.state) {
    case 0x12:
        AnimChangeWithDef(&sEmy04AnimDef, &work->base.anim, 0, 0, work->base.tiles);
        work->base.vz = 0;

        if (work->healCount > 2) {
            CreateBtlPopTask(act, 2);
            EmyReturnToIdle(&work->base);
            break;
        }

        if (work->base.stateTimer == 3) {
            best = NULL;
            bestv = 0;

            for (p = ListPoolFirst(&gBtlWork->pool); p != NULL;
                    p = ListPoolNext(&p->node)) {
                if (!(p->flags & BTLOBJ_FLAG_INTANGIBLE)) {
                    if (bestv < p->maxHp - p->hp) {
                        bestv = p->maxHp - p->hp;
                        best = p;
                    }
                }
            }

            if (best == NULL) {
                best = act;
            }

            if (best->hp == best->maxHp) {
                CreateBtlPopTask(act, 2);
                EmyReturnToIdle(&work->base);
                break;
            }

            best->flags |= BTLOBJ_FLAG_HEAL_PENDING;
            best->damage = -0x1E;
            BgFxStartCure(0, best->x, best->y, best->z);
            w->healCount++;
        }

        if (work->base.stateTimer > 0x0D) {
            if (!BgFxIsActive()) {
                EmyReturnToIdle(&work->base);
            }
        } else {
            work->base.stateTimer++;
        }

        break;
    }

    return EmyUpdateCommonStates(&work->base);
}

void task_emy_04_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_04_3(EmyWork* work) {
    EmyReleaseResources(work);
}
