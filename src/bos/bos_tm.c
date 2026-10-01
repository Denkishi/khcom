#include "macros.h"
#include "registration_data.h"
#include "boss_tm.h"
#include "event_backgrounds.h"
#include "chara_types.h"
#include "chara_api.h"
#include <stddef.h>
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_bg_types.h"
#include "battle_work.h"
#include "gba/defines.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"

s16 gBosTmActorZ EWRAM_COMMON(4);
s16 gUnk_0203AB40 EWRAM_COMMON(4);
s16 gBosTmActorY EWRAM_COMMON(4);
s16 gUnk_0203AB48 EWRAM_COMMON(4);

static const BattleBackgroundDef sBosTmBattleBackgroundDef = {
    gUnk_0964AE84, 0x8000, { 0, 0 }, gUnk_096FB164, 0x140, { 0, 0 }, { gUnk_096BFC64, gUnk_096BFC64, gUnk_096BFC64, gUnk_096BFC64 }
};

TaskDesc gTaskDescBosTm = {
    "task_bos_tm",
    (TaskInitFunc)task_bos_tm_0,
    (TaskUpdateFunc)task_bos_tm_1,
    (TaskDrawFunc)task_bos_tm_2,
    (TaskDestroyFunc)task_bos_tm_3,
    sizeof(TmWork),
};

static Task* gBosTmBodyTask;
static Task* gBosTmArmTask;
static Task* gBosTmFootTask;
static Task* gBosTmTblTask;
static TaskPool gBosTmTaskPool;

void BosTmSetArmPositions(TmWork* w) {
    if (w->flags & TM_FLAG_FACING_LEFT) {
        w->arm.x = w->x2 + 0x1000;
        w->arm.x2 = w->x2 - 0x700;
        w->arm.y = w->y2 + 0x700;
        w->arm.y2 = w->y2 - 0x400;
        w->arm.z = w->z2 - 0x2200;
        w->arm.z2 = w->z2 - 0x1C00;
    } else {
        w->arm.x = w->x2 + 0x700;
        w->arm.x2 = w->x2 - 0xE00;
        w->arm.y = w->y2 - 0x400;
        w->arm.y2 = w->y2 + 0x700;
        w->arm.z = w->z2 - 0x1C00;
        w->arm.z2 = w->z2 - 0x2200;
    }
}

void task_bos_tm_0(TmWork* w, BtlObj* arg) {
    w->flags = 0;

    if (arg != NULL) {
        w->flags = TM_FLAG_IN_EVENT;
    }

    TaskPoolInit(&gBosTmTaskPool, 4);

    if (w->flags & TM_FLAG_IN_EVENT) {
        w->x = arg->x >> 8;
        w->y = arg->y >> 8;
        w->z = arg->z >> 8;
    } else {
        w->x = 0x15D;
        w->y = 0x16C;
        w->z = -0x3C;
        gBtlWork->bossX = w->x << 8;
        gBtlWork->bossY = 0x156 << 8;
        gBtlWork->bossZ = (s16)w->z << 8;
    }

    w->baseX = (s16)w->x << 8;
    w->baseY = (s16)w->y << 8;
    w->baseZ = (s16)w->z << 8;
    w->x2 = w->baseX;
    w->y2 = w->baseY;
    w->z2 = w->baseZ;
    w->vx = 0;
    w->vy = 0;
    w->step = 0;
    w->stepTimer = 0;
    w->hitCount = 0;
    w->hurtTimer = 55;
    w->stateTimer = 0;
    w->tableState = 0;
    w->flags |= (TM_FLAG_TABLE_JUST_RAISED | TM_FLAG_FACING_LEFT);
    w->unk_3B = 0;
    w->resumeState = 16;
    w->tileIndex = 0;
    w->tileCount = 0;
    w->paletteIndex = 0;
    w->arm.tm = w;
    BosTmSetArmPositions(w);

    if (w->flags & TM_FLAG_IN_EVENT) {
        w->state = 15;
        gBosTmBodyTask = TaskCreate(&gBosTmTaskPool, &gTaskDescBosTmBody, w);
        gBosTmFootTask = TaskCreate(&gBosTmTaskPool, &gTaskDescBosTmFoot, w);
        gBosTmArmTask = TaskCreate(&gBosTmTaskPool, &gTaskDescBosTmArm, &w->arm);
    } else {
        w->state = 0;
        TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosMap, (void*)&sBosTmBattleBackgroundDef);
        gBosTmTblTask = TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosTmTbl, w);
        gBosTmBodyTask = TaskCreate(&gBosTmTaskPool, &gTaskDescBosTmBody, w);
        gBosTmFootTask = TaskCreate(&gBosTmTaskPool, &gTaskDescBosTmFoot, w);
        gBosTmArmTask = TaskCreate(&gBosTmTaskPool, &gTaskDescBosTmArm, &w->arm);
        gBtlWork->bossPriorityOffset = 10;
    }
}

u8 task_bos_tm_1(TmWork* w) {
    CharaObjParam2 param;
    u16 t;

    switch (w->state) {
    case 0:
    case 15:
        w->stepTimer++;

        if (w->stepTimer > 8) {
            w->stepTimer = 0;
            w->step++;

            if (w->step > 7) {
                w->step = 0;
            }
        }

        break;
    case 12:
        w->step++;
        t = w->hitCount;

        if ((s16)t == 1) {
            w->hitCount = t + 1;
        }

        break;
    case 4:
    case 5:
    case 6:
    case 7:
        w->stepTimer++;

        if (w->stepTimer > 6) {
            w->stepTimer = 0;
            w->step++;

            if (w->step > 9) {
                w->step = 0;
            }
        }

        break;
    case 13:
        if (w->step != 0) {
            if (!CharaObjUpdateDefeat2()) {
                EndBossDefeat();
                return 0;
            }
        } else {
            param.tilesAddr = OBJ_VRAM0 + (w->tileIndex << 5);
            param.tileCount = w->tileCount;
            param.paletteAddr = OBJ_PLTT + (w->paletteIndex << 5);
            param.paletteSize = 0x60;
            param.x = w->x2;
            param.y = w->y2;
            param.z = w->z2;
            param.callback = BosTmDestroyParts;
            gBosTmBodyObjCopy.x = w->x2;
            gBosTmBodyObjCopy.y = w->y2;
            gBosTmBodyObjCopy.z = w->z2;
            param.prizeObj = &gBosTmBodyObjCopy;
            CharaObjInitDefeat2(&param);
            w->flags &= ~TM_FLAG_HURT;
            w->step++;
        }

        break;
    case 2:
    case 3:
    case 9:
    case 11:
        w->step++;
        break;
    case 17:
        break;
    }

    gBosTmActorY = gBtlWork->actor->y >> 8;
    gUnk_0203AB40 = gBtlWork->actor->originZ >> 8;
    gBosTmActorZ = gBtlWork->actor->z >> 8;
    gUnk_0203AB48 = gBtlWork->bossY >> 8;

    if ((gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) && w->state != 13) {
        if (gBtlWork->actor->originZ <= -0x2D00) {
            gBtlWork->bossPriorityOffset = -10;
        } else {
            gBtlWork->bossPriorityOffset = 10;
        }
    } else {
        if (gBtlWork->actor->z <= -0x2D00) {
            gBtlWork->bossPriorityOffset = -10;
        } else {
            gBtlWork->bossPriorityOffset = 10;
        }
    }

    TaskPoolUpdate(&gBosTmTaskPool);
    BosTmSetArmPositions(w);
    w->stateTimer++;
    return 1;
}

void task_bos_tm_2(TmWork* w) {
    TaskPoolDraw(&gBosTmTaskPool);
}

void task_bos_tm_3(TmWork* w) {
    TaskPoolDestroy(&gBosTmTaskPool);
}

void BosTmDestroyParts(void) {
    TaskKill(&gBtlWork->taskPools[1], gBosTmTblTask);
    TaskKill(&gBosTmTaskPool, gBosTmBodyTask);
    TaskKill(&gBosTmTaskPool, gBosTmFootTask);
    TaskKill(&gBosTmTaskPool, gBosTmArmTask);
}
