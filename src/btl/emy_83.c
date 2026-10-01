#include "task_descriptors.h"
#include "emy.h"
#include "sprites_emy.h"
#include "enemy_common.h"
#include "songs.h"
#include "emy_tasks.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "enemy_types.h"
#include "engine_math.h"
#include "m4a_song.h"
#include "mode_chkobj_assets.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

static const AnimDef sEmy83CommonAnimDefs[3] = {
    { gEmy8300Frames, gEmy8300Anims, gEmy8300Tiles, 0, { 0, 0, 0 } },
    { gEmy8302Frames, gEmy8302Anims, gEmy8302Tiles, 0, { 0, 0, 0 } },
    { gEmy8300Frames, gEmy8300Anims, gEmy8300Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy83AnimDefs[4] = {
    { gEmy8310Frames, gEmy8310Anims, gEmy8310Tiles, 0, { 0, 0, 0 } },
    { gEmy8311Frames, gEmy8311Anims, gEmy8311Tiles, 0, { 0, 0, 0 } },
    { gEmy8311Frames, gEmy8311Anims, gEmy8311Tiles, 1, { 0, 0, 0 } },
    { gEmy8311Frames, gEmy8311Anims, gEmy8311Tiles, 2, { 0, 0, 0 } },
};

static const EmyDef sEmy83Def = { gEmy83Palette, sEmy83CommonAnimDefs, 192, 130, 20, 20, 50, 50, 50, 10, 0, { 31, 66, 35, 12, 24, 100, 0 } };

TaskDesc gTaskDescEmy83 = {
    "task_emy_83",
    (TaskInitFunc)task_emy_83_0,
    (TaskUpdateFunc)task_emy_83_1,
    (TaskDrawFunc)task_emy_83_2,
    (TaskDestroyFunc)task_emy_83_3,
    sizeof(Emy83Work),
};

static TaskDesc sTaskDescEmy83B = {
    "task_emy_83_b",
    (TaskInitFunc)task_emy_83_b_0,
    (TaskUpdateFunc)task_emy_83_b_1,
    (TaskDrawFunc)task_emy_83_b_2,
    (TaskDestroyFunc)task_emy_83_b_3,
    sizeof(Emy83bWork),
};

static TaskDesc sTaskDescEmy83S = {
    "task_emy_83_s",
    (TaskInitFunc)task_emy_83_s_0,
    (TaskUpdateFunc)task_emy_83_s_1,
    (TaskDrawFunc)task_emy_83_s_2,
    (TaskDestroyFunc)task_emy_83_s_3,
    sizeof(Emy83sWork),
};

void task_emy_83_0(Emy83Work* work, void* obj) {
    EmyInit(&work->base, &sEmy83Def, obj);
    work->task = NULL;
    work->base.idleState = 0x16;
    TaskPoolInit(&work->tasks, 4);
}

u8 task_emy_83_1(Emy83Work* work) {
    Emy83Work* w;
    BtlObj* act;
    u16 r;
    u16 c;
    EmySpawn spawn;
    s32 pos;
    s32 x;
    s32 y;
    s32 z;
    u8 ret;

    w = work;
    act = &work->base.actor;

    if (EmyUpdateReaction(&work->base)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->base.state = 0x12;
            w->task = NULL;
            break;
        case 1:
            work->base.state = 0x13;
            w->shotCount = 0;
            break;
        }
    }

    switch (work->base.state) {
    case 0x16:
        AnimChangeWithDef(w->base.def->animDef, &w->base.anim, 0, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START, w->base.tiles);
        TryEnemyCardUse(act);
        GetEnemyTargetPosition(act, &pos, NULL, NULL);

        if (act->x < pos) {
            act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
        } else {
            act->flags |= BTLOBJ_FLAG_FACING_LEFT;
        }

        break;
    case 0x12:
        AnimChangeWithDef(sEmy83AnimDefs, &w->base.anim, 0, 0, w->base.tiles);
        c = work->base.anim.timer;

        if (c == 0) {
            switch (AnimGetFrame(&work->base.anim)) {
            case 3:
                GetEnemyTargetPosition(act, &w->targetX, &w->targetY, NULL);
                break;
            case 5:
                spawn.x = w->targetX;
                spawn.y = w->targetY;
                spawn.z = c;
                w->task = TaskCreate(&w->tasks, &sTaskDescEmy83B, &spawn);
                break;
            }
        }

        if (AnimIsFinished(&work->base.anim) && !IsTaskActiveNamed(w->task, sTaskDescEmy83B.name)) {
            EmyReturnToIdle(&work->base);
        }

        break;
    case 0x13:
        AnimChangeWithDef(sEmy83AnimDefs, &w->base.anim, 1, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 0x14;
        }

        break;
    case 0x14:
        AnimChangeWithDef(sEmy83AnimDefs, &w->base.anim, 2, ANIM_FLAG_LOOP, w->base.tiles);

        if (AnimGetGfxIndex(&work->base.anim) == 6 && work->base.anim.timer == 0) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                spawn.x = act->x - 0x1000;
                spawn.facingLeft = 1;
            } else {
                spawn.x = act->x + 0x1000;
                spawn.facingLeft = 0;
            }

            spawn.y = act->y;
            spawn.z = act->z - 0x1200;
            spawn.hitPhase = 0;
            TaskCreate(&w->tasks, &sTaskDescEmy83S, &spawn);
            spawn.hitPhase = 1;
            TaskCreate(&w->tasks, &sTaskDescEmy83S, &spawn);
            spawn.hitPhase = 2;
            TaskCreate(&w->tasks, &sTaskDescEmy83S, &spawn);
            w->shotCount++;
        }

        if (w->shotCount > 2 && AnimIsFinished(&work->base.anim)) {
            work->base.state = 0x15;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 0x15:
        AnimChangeWithDef(sEmy83AnimDefs, &w->base.anim, 3, 0, w->base.tiles);

        if (work->base.stateTimer > 0x28) {
            EmyReturnToIdle(&work->base);
        } else {
            work->base.stateTimer++;
        }

        break;
    }

    TaskPoolUpdate(&w->tasks);
    x = act->x;
    y = act->y;
    z = act->z;
    ret = EmyUpdateCommonStates(&work->base);

    if (work->base.state != 0x0B) {
        act->x = x;
        act->y = y;
        act->z = z;
    }

    return ret;
}

void task_emy_83_2(Emy83Work* work) {
    EmyDraw(&work->base);
    TaskPoolDraw(&work->tasks);
}

void task_emy_83_3(Emy83Work* work) {
    TaskPoolDestroy(&work->tasks);
    EmyReleaseResources(&work->base);
}

void task_emy_83_b_0(Emy83bWork* work, EmySpawn* spawn) {
    work->state = 0;
    work->palette = LoadObjPalette(gEmy83Palette, 0x20);
    work->tiles = AllocObjTiles(0x80, gEmy8310bTiles);
    AnimInit(&work->anim, gEmy8310bAnims, gEmy8310bFrames);
    AnimStart(&work->anim, 0, 0);
    work->x = spawn->x;
    work->y = spawn->y;
    work->z = spawn->z;
    work->timer = 0;
    ColliderInit(&work->collider, 0x0C, 4, 0x10);
}

u8 task_emy_83_b_1(Emy83bWork* work) {
    if ((gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) == 0) {
        return 0;
    }

    switch (work->state) {
    case 0:
        if (work->timer > 0x0F) {
            work->state = 1;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 1:
        if (work->timer == 0) {
            AnimStart(&work->anim, 1, 0);
        }

        if (AnimGetFrame(&work->anim) == 1 && work->anim.timer == 0) {
            if (ApplyAttackBox(0xE0, work->x, work->y, work->z, 4, 4, 0x10)) {
                m4aSongNumStart(SONG_BTL_HANE_HIT);
            }
        }

        if (work->timer > 0x1D) {
            work->state = 2;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 2:
    default:
        if (work->timer == 0) {
            AnimStart(&work->anim, 2, 0);
        }

        if (AnimIsFinished(&work->anim)) {
            return 0;
        }

        work->timer++;
        break;
    }

    ColliderSetPosition(&work->collider, work->x, work->y, work->z);
    AnimUpdate(&work->anim);
    return 1;
}

void task_emy_83_b_2(Emy83bWork* work) {
    void* gfx;
    u16 pri;
    s16 x;
    s16 y;

    gfx = AnimGetGfx(&work->anim);
    pri = GetBattleSpritePriorityFlags(work->y);
    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gfx, work->tiles, work->palette, NULL, pri,
        -0x1004 - ((work->y + 0x400) >> 8) * 4);
}

void task_emy_83_b_3(Emy83bWork* work) {
    ColliderUnregister(&work->collider);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_emy_83_s_0(Emy83sWork* work, EmySpawn* spawn) {
    work->palette = LoadObjPalette(gEmy83Palette, 0x20);
    work->tiles = LoadObjTiles(gEmy8311bTiles, 0x40);
    work->x = spawn->x;
    work->y = spawn->y;
    work->z = spawn->z;
    work->vz = 0;
    work->frameCount = 0;

    if (spawn->facingLeft != 0) {
        work->vx = -(GetRandom() % 0x4CE + 0x133);
    } else {
        work->vx = GetRandom() % 0x4CE + 0x133;
    }

    work->vy = GetRandom() % 0x201 - 0x100;
    work->hitPhase = spawn->hitPhase;
}

u8 task_emy_83_s_1(Emy83sWork* work) {
    s32 x;
    s32 y;

    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) {
        x = work->x + work->vx;
        work->x = x;
        y = work->y + work->vy;
        work->y = y;

        if (work->frameCount % 3 == work->hitPhase) {
            if (ApplyAttackBox(0xE1, x, y, work->z, 2, 2, 2) != 0) {
                m4aSongNumStart(SONG_BTL_KAMITUKI);
            }
        }

        work->z += work->vz;
        work->vz += 0x14;

        if (work->z < 0) {
            work->frameCount++;
            return 1;
        }
    }

    return 0;
}

void task_emy_83_s_2(Emy83sWork* work) {
    u16 pri;
    s16 x;
    s16 y;

    pri = GetBattleSpritePriorityFlags(work->y);
    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gEmy8311bFrame0, work->tiles, work->palette, NULL, pri,
        -0x1004 - ((work->y + 0x400) >> 8) * 4);
    WorldToScreen(&x, &y, work->x, work->y, 0);
    DrawSprite(x, y, gEmy8311bFrame1, work->tiles, work->palette, NULL, pri, -2);
}

void task_emy_83_s_3(Emy83sWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}
