/**
 * emy_00.c
 * Shadow Enemy
 */

#include "task_descriptors.h"
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
#include "game_state.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "sprite_palettes.h"

static const AnimDef sEmy00CommonAnimDefs[3] = {
    { gEmy00L00Frames, gEmy00L00Anims, gEmy00L00Tiles, 0 },
    { gEmy00L09Frames, gEmy00L09Anims, gEmy00L09Tiles, 0 },
    { gEmy00L02Frames, gEmy00L02Anims, gEmy00L02Tiles, 0 },
};

static const AnimDef sEmy00AnimDefs[7] = {
    { gEmy00L07Frames, gEmy00L07Anims, gEmy00L07Tiles, 1 },
    { gEmy00L12Frames, gEmy00L12Anims, gEmy00L12Tiles, 0 },
    { gEmy00L06Frames, gEmy00L06Anims, gEmy00L06Tiles, 1 },
    { gEmy00L06Frames, gEmy00L06Anims, gEmy00L06Tiles, 0 },
    { gEmy00L04Frames, gEmy00L04Anims, gEmy00L04Tiles, 0 },
    { gEmy00L10Frames, gEmy00L10Anims, gEmy00L10Tiles, 0 },
    { gEmy00L11Frames, gEmy00L11Anims, gEmy00L11Tiles, 0 },
};

static const EmyDef sEmy00Def = { gEmy00Palette, sEmy00CommonAnimDefs, 384, 130, 10, 20, 64, 32, 16, 10, EMY_DEF_FLAG_NO_SHADOW | EMY_DEF_FLAG_NO_SCALE_IN, { 0, 12, 32, 12, 16, 100, 0 } };

TaskDesc gTaskDescEmy00 = {
    "task_emy_00",
    (TaskInitFunc)task_emy_00_0,
    (TaskUpdateFunc)task_emy_00_1,
    (TaskDrawFunc)task_emy_00_2,
    (TaskDestroyFunc)task_emy_00_3,
    sizeof(EmyWork),
};

void task_emy_00_0(EmyWork* work, void* obj) {
    EmyInit(work, &sEmy00Def, obj);
    work->flags |= EMY_FLAG_DARK_DEATH;
    work->idleState = 0x12;
    work->state = 0x16;
}

u8 task_emy_00_1(EmyWork* work) {
    EmyWork* w;
    BtlObj* act;
    u16 r;
    s32 pos;
    s32 pos2;
    u8 ret;

    w = work;
    act = &work->actor;

    if (EmyUpdateReaction(work)) {
        r = GetRandom();

        switch (r & 1) {
        case 0:
            work->state = 24;
            break;
        case 1:
            work->state = 25;
            break;
        }
    }

    switch (w->state) {
    case 24:
        AnimChangeWithDef(sEmy00AnimDefs, &work->anim, 5, 0, work->tiles);
        EmyLungeAttack(w, 31, 18, 11, 165, 40, SONG_BTL_MON_HIT00, 0, 0, 24);
        break;
    case 25:
        AnimChangeWithDef(sEmy00AnimDefs, &work->anim, 6, 0, work->tiles);

        if (w->stateTimer == 10) {
            w->vz = -0x400;
        }

        EmyLungeAttack(w, 14, 35, 10, 166, 96, SONG_BTL_MON_HIT00, 0, 0, 24);
        break;
    case 19:
        AnimChangeWithDef(sEmy00AnimDefs, &work->anim, 0, 0, work->tiles);

        if (AnimIsFinished(&w->anim)) {
            w->state = 20;
            ColliderSetDisabled(&act->collider, 1);
            act->flags |= BTLOBJ_FLAG_INTANGIBLE;
            act->centerHeight = 0;
        }

        break;
    case 20:
        if (gBtlWork->flags & BTL_FLAG_ENEMY_MOVE_ENABLED) {
            GetEnemyTargetPosition(act, &pos, NULL, NULL);
            AnimChangeWithDef(sEmy00AnimDefs, &work->anim, 1, ANIM_FLAG_LOOP, work->tiles);
            act->x += gSineTable[w->angle] * w->speed >> 8;
            act->y += -gSineTable[w->angle + 64] * w->speed >> 8;

            if (w->stateTimer > 100) {
                w->state = 21;
                ColliderSetDisabled(&act->collider, 0);
                act->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
                act->centerHeight = 16;
                w->stateTimer = 0;
            } else {
                w->stateTimer++;
            }

            if (act->x > pos) {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            } else {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }
        }

        break;
    case 22:
        AnimChangeWithDef(sEmy00AnimDefs, &work->anim, 3, 0, work->tiles);

        if (w->stateTimer == 20) {
            act->flags &= ~BTLOBJ_FLAG_INTANGIBLE;

            if (gGameState.flags & GAME_FLAG_FIRST_STRIKE) {
                EmyFinishSpawn(w);
                break;
            }
        }

        if (AnimIsFinished(&w->anim)) {
            EmyFinishSpawn(w);
            break;
        }

        w->stateTimer++;
        break;
    case 21:
        AnimChangeWithDef(sEmy00AnimDefs, &work->anim, 2, 0, work->tiles);

        if (w->stateTimer == 30) {
            act->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
        }

        if (AnimIsFinished(&w->anim)) {
            act->flags &= ~(BTLOBJ_FLAG_INTANGIBLE | BTLOBJ_FLAG_CARD_USE_BLOCKED);
            w->state = 18;
#ifdef VERSION_EU
            w->stateTimer = 0;
#endif
        } else {
            w->stateTimer++;
        }

        break;
    case 18:
        if (w->stateTimer == 0) {
            ColliderSetDisabled(&act->collider, 0);
            act->flags &= ~(BTLOBJ_FLAG_INTANGIBLE | BTLOBJ_FLAG_CARD_USE_BLOCKED);
            AnimChangeWithDef(work->def->animDef, &work->anim, 0, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START,
                work->tiles);
        }

        TryEnemyCardUse(act);

        if (GetRandom() % 120 == 0) {
            w->state = 4;

            if (GetRandom() % 2 == 0) {
                w->x = -((act->attackOffset
                    + (-act->attackRangeX
                        + GetRandom() % (act->attackRangeX - -act->attackRangeX + 1)))
                    << 8);
            } else {
                w->x = (act->attackOffset
                    + (-act->attackRangeX
                        + GetRandom() % (act->attackRangeX - -act->attackRangeX + 1)))
                    << 8;
            }
        } else if (GetRandom() % 200 == 0) {
            w->state = 19;
            act->flags |= BTLOBJ_FLAG_CARD_USE_BLOCKED;
            w->angle = GetRandom();
            w->stateTimer = 0;
            break;
        }

        if (GetRandom() % w->def->turnInterval == 0) {
            GetEnemyTargetPosition(act, &pos2, NULL, NULL);

            if (act->x > pos2) {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            } else {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }
        }

        w->stateTimer++;
        break;
    }

    ret = EmyUpdateCommonStates(w);

    if (w->state == 14) {
        AnimChangeWithDef(sEmy00AnimDefs, &work->anim, 4, ANIM_FLAG_LOOP, work->tiles);
    }

    return ret;
}

void task_emy_00_2(EmyWork* work) {
    BtlObj* act;
    u16 pri;
    ObjAffine* affine;
    s32 rot;
    s32 scale;
    s32 zoom;
    s16 x;
    s16 y;

    if (work->visible) {
        act = &work->actor;
        pri = GetBattleSpritePriorityFlags(act->y) | work->spriteFlags;
        WorldToScreen(&x, &y, act->x, act->y, act->z);
        zoom = work->scaleY;

        if (zoom == 0x100) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                scale = gBtlWork->scale;
                rot = scale;
            } else if (gBtlWork->scale == zoom) {
                scale = zoom;
                rot = scale;
                pri |= 1;
            } else {
                rot = -gBtlWork->scale;
                scale = gBtlWork->scale;
            }
        } else {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                rot = gBtlWork->scale * work->scaleX >> 8;
                scale = gBtlWork->scale;
            } else {
                rot = -(gBtlWork->scale * work->scaleX >> 8);
                scale = gBtlWork->scale;
            }

            scale = scale * zoom >> 8;
        }

        if (scale == 0x100 && rot == scale) {
            affine = NULL;
        } else if (scale <= 0xFF) {
            affine = AllocObjAffine(0, rot, scale, 0);
        } else {
            affine = AllocObjAffine(0, rot, scale, 1);
        }

        if (StepHitFlash(act)) {
            DrawSprite(x, y, work->gfx, work->tiles, work->palette2, affine, pri,
                -0x1004 - (act->y >> 8) * 4);
        } else if (work->state == 0x14) {
            DrawSprite(x, y, work->gfx, work->tiles, work->palette, affine, pri, 0xFFFF);
        } else {
            DrawSprite(x, y, work->gfx, work->tiles, work->palette, affine, pri,
                -0x1004 - (act->y >> 8) * 4);
        }

        TaskPoolDraw(&work->tasks);
    }
}

void task_emy_00_3(EmyWork* work) {
    EmyReleaseResources(work);
}
