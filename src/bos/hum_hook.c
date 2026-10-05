/**
 * hum_hook.c
 * Captain Hook Boss
 */

#include "fade.h"
#include "obj_api.h"
#include "pallet.h"
#include "hum.h"
#include "sprites_btl.h"
#include "sprites_evt.h"
#include "sprites_hum.h"
#include "btl_api.h"
#include "hum_common.h"
#include "songs.h"
#include "hum_tasks.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "card_api.h"
#include "display.h"
#include "engine_math.h"
#include "hum_types.h"
#include "m4a_song.h"
#include "obj.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "sprite_palettes.h"

static const u32 sHumHookStockMovesA[3] = {
    36, 36, 38,
};

static const u32 sHumHookStockMovesB[3] = {
    37, 37, 38,
};

static const AnimDef sHumHookAnimDefs[15] = {
    { gHookBt00Frames, gHookBt00Anims, gHookBt00Tiles, 0 },
    { gHookBt01Frames, gHookBt01Anims, gHookBt01Tiles, 0 },
    { gHookBt02Frames, gHookBt02Anims, gHookBt02Tiles, 0 },
    { gHookBt03Frames, gHookBt03Anims, gHookBt03Tiles, 0 },
    { gHookBt03Frames, gHookBt03Anims, gHookBt03Tiles, 1 },
    { gHookBt03Frames, gHookBt03Anims, gHookBt03Tiles, 2 },
    { gHookBt03Frames, gHookBt03Anims, gHookBt03Tiles, 3 },
    { gHookBt03Frames, gHookBt03Anims, gHookBt03Tiles, 4 },
    { gHookBt10Frames, gHookBt10Anims, gHookBt10Tiles, 0 },
    { gHookBt11Frames, gHookBt11Anims, gHookBt11Tiles, 1 },
    { gHookBt11Frames, gHookBt11Anims, gHookBt11Tiles, 0 },
    { gHookBt11Frames, gHookBt11Anims, gHookBt11Tiles, 2 },
    { gHookBt12Frames, gHookBt12Anims, gHookBt12Tiles, 0 },
    { gHookF03Frames, gHookF03Anims, gHookF03Tiles, 2 },
    { gHookF03Frames, gHookF03Anims, gHookF03Tiles, 3 },
};

static const HumDef sHumHookDef = { 128, gHookPalette, 0, { 42, 99, 38, 14, 24, 99, 0 } };

static const u8 sHumHookRollAmplitudes[8] = {
    0, 4, 4, 6, 8, 10, 8, 6,
};

TaskDesc gTaskDescHumHook = {
    "task_hum_hook",
    (TaskInitFunc)task_hum_hook_0,
    (TaskUpdateFunc)task_hum_hook_1,
    (TaskDrawFunc)task_hum_hook_2,
    (TaskDestroyFunc)task_hum_hook_3,
    sizeof(HookWork),
};

static TaskDesc sTaskDescHumHookMoon = {
    "task_hum_hook_moon",
    (TaskInitFunc)task_hum_hook_moon_0,
    (TaskUpdateFunc)task_hum_hook_moon_1,
    (TaskDrawFunc)task_hum_hook_moon_2,
    (TaskDestroyFunc)task_hum_hook_moon_3,
    sizeof(HookMoonWork),
};

static TaskDesc sTaskDescHumHookBomb = {
    "task_hum_hook_bomb",
    (TaskInitFunc)task_hum_hook_bomb_0,
    (TaskUpdateFunc)task_hum_hook_bomb_1,
    (TaskDrawFunc)task_hum_hook_bomb_2,
    (TaskDestroyFunc)task_hum_hook_bomb_3,
    sizeof(HookBombWork),
};

void HookJumpOffset(CloudWork* work, s16 a, s32 b) {
    HumWork* w = &work->base;
    BtlObj* act = &w->actor;

    if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
        work->base.targetX = act->x - (a << 8);
    } else {
        work->base.targetX = act->x + (a << 8);
    }

    w->targetY = act->y;
    w->state = 0x16;
    w->stateTimer = 0;
    work->speed = -b;
}

void HookJumpTo(CloudWork* work, s32 a, s32 b) {
    work->base.targetX = a;
    work->base.targetY = b;
    work->base.state = 0x16;
    work->base.stateTimer = 0;
    work->speed = -0x680;
}

u8 HookTryJumpAway(CloudWork* work) {
    s32 x;
    s32 y;
    BtlObj* c;

    c = gBtlWork->actor;
    GetEnemyTargetPosition(&work->base.actor, &x, &y, NULL);
    HumFaceTarget(&work->base, 1);

    if (HumIsInPlayerReach(&work->base, 0x100, 0x100, 0x100)) {
        if (gBtlWork->flags & BTL_FLAG_PLAYER_AIRBORNE) {
            HookJumpOffset(work, -99, 0x280);
        } else if (GetRandom() & 1) {
            if (c->flags & BTLOBJ_FLAG_FACING_LEFT) {
                HookJumpTo(work, x + 0x2800, y);
            } else {
                HookJumpTo(work, x - 0x2800, y);
            }
        } else {
            HookJumpOffset(work, -80, 0x500);
        }

        return 1;
    }

    return 0;
}

void task_hum_hook_0(HookWork* work, void* arg) {
    TaskCreate(&gBtlWork->taskPools[0], &sTaskDescHumHookMoon, NULL);
    HumInit(&work->base, &sHumHookDef);
    work->base.actor.flags |= BTLOBJ_FLAG_IMMUNE_THUNDER;

    if (GetRandom() % 2) {
        work->base.stockMoves = sHumHookStockMovesA;
    } else {
        work->base.stockMoves = sHumHookStockMovesB;
    }

    work->base.flags |= HUM_FLAG_BOSS_DEATH;
    work->speed = 0;
    work->playerSlide = 0;
    work->slide = 0;
    work->angle = 0;
    work->rollLevel = 0;
    work->flags = 0;
    TaskPoolInit(&work->tasks, 3);
}

u8 task_hum_hook_1(HookWork* work) {
    HookWork* w;
    BtlObj* act;
    BtlObj* c;
    VixenNdlArgs args;
    s32 x;
    s32 y;
    s32 z;
    u16 f;
    u8 a;

    w = work;
    act = &work->base.actor;
    c = gBtlWork->actor;
    GetEnemyTargetPosition(act, &x, &y, &z);

    if (HumUpdateReaction(&work->base) == 5) {
        work->base.stateTimer = 0;

        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
            work->base.state = 20;
            break;
        case 37:
            work->base.state = 21;
            break;
        case 38:
            work->base.state = 19;
            break;
        case 39:
            work->base.state = 25;
            break;
        case 0xED1AF6BD:
            work->base.state = 26;
            break;
        case 0xED1B1EC7:
            work->base.state = 29;
            work->base.steps = 0;
            break;
        }
    }

    if (HumChooseCardAction(&work->base, 13, 40, 40, 24)) {
        if (GetRandom() % 2) {
            w->base.stockMoves = sHumHookStockMovesA;
        } else {
            w->base.stockMoves = sHumHookStockMovesB;
        }
    }

    switch (work->base.state) {
    case 12:
    case 18:
        AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        break;
    case 17: {
        s32 d;

        AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START, w->base.tiles);

        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            if (HookTryJumpAway((CloudWork*)w)) {
                break;
            }
        }

        d = act->x - x;

        if ((d >= 0) ? d <= 0x3FFF : (d = x - act->x) <= 0x3FFF) {
            if (x <= 0xFFFF) {
                HookJumpTo((CloudWork*)w, (gBtlWork->xMax - 40) << 8,
                    (gBtlWork->yMin + gBtlWork->yMax) << 7);
            } else {
                HookJumpTo((CloudWork*)w, (gBtlWork->xMin + 40) << 8,
                    (gBtlWork->yMin + gBtlWork->yMax) << 7);
            }
        }

        break;
    }
    case 0:
        AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START, w->base.tiles);

        if (func_08081828()) {
            break;
        }

        if (GetRandom() % 150 == 0) {
            work->base.state = 8;
            work->base.stateTimer = 0;
            break;
        }

        if (HumIsNearAreaEdge(&work->base, 40)) {
            HookJumpTo((CloudWork*)w, 0x10000,
                (gBtlWork->yMin + gBtlWork->yMax) << 7);
            break;
        }

        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            if (HookTryJumpAway((CloudWork*)w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 8);
        }

        work->base.stateTimer++;
        break;
    case 8:
        AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 1, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START, w->base.tiles);
        work->base.targetX = x;
        work->base.targetY = y;

        if (HumMoveToward(&work->base, work->base.targetX, y, 358)) {
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }

        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            if (HookTryJumpAway((CloudWork*)w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 8);
        }

        work->base.stateTimer++;
        break;
    case 3:
        AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        gBtlWork->rotation = 0;
        break;
    case 1:
    case 9:
    case 11:
    case 14:
        AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        break;
    case 2:
        if (func_08081828() == 0) {
            break;
        }

        if (GetRandom() % 10 != 0) {
            break;
        }

        if (x <= 0xFFFF) {
            work->base.targetX = (gBtlWork->xMax - 40) << 8;
        } else {
            work->base.targetX = (gBtlWork->xMin + 40) << 8;
        }

        work->base.targetY = (gBtlWork->yMin + gBtlWork->yMax) << 7;
        work->base.state = 23;
        work->base.stateTimer = 0;
        work->base.vz = -0x680;
        break;
    case 26:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 11, ANIM_FLAG_LOOP, w->base.tiles);
        }

        BtlMapFollowPosition(act->x, act->y, act->z);
        HumFaceTarget(&work->base, 1);

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            s32 d = act->x - 0x1000;
            act->x += (x - d) >> 4;
        } else {
            s32 d = act->x + 0x1000;
            act->x += (x - d) >> 4;
        }

        act->y += (y - act->y) >> 4;

        if (work->base.anim.timer == 0) {
            switch (AnimGetFrame(&work->base.anim)) {
            case 2:
            case 4:
            case 7:
                MakeOpponentsHittable();

                if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(280, act->x - 0x1400, act->y, act->z, 20, 20, 50)
                    : ApplyAttackBox(280, act->x + 0x1400, act->y, act->z, 20, 20, 50)) {
                    m4aSongNumStart(SONG_BTL_MON_SWORD00);
                }

                break;
            }
        }

        if (work->base.stateTimer > 120) {
            work->base.state = 27;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 27:
        BtlMapFollowPosition(act->x, act->y, act->z);

        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
        }

        HumFaceTarget(&work->base, 1);

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            s32 d = act->x - 0x1000;
            act->x += (x - d) >> 4;
        } else {
            s32 d = act->x + 0x1000;
            act->x += (x - d) >> 4;
        }

        act->y += (y - act->y) >> 4;

        if (work->base.anim.timer == 0 && AnimGetFrame(&work->base.anim) == 3) {
            MakeOpponentsHittable();

            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                ? ApplyAttackBox(0x119, act->x - 0x1400, act->y, act->z, 20, 20, 50)
                : ApplyAttackBox(0x119, act->x + 0x1400, act->y, act->z, 20, 20, 50)) {
                m4aSongNumStart(SONG_BTL_MON_SWORD00);
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 28;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 28:
        BtlMapFollowPosition(act->x, act->y, act->z);

        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
            w->bombTask = NULL;
            w->bombTask2 = NULL;
            w->bombTask3 = NULL;
            w->flags &= ~(HOOK_FLAG_BOMB_THROWN | HOOK_FLAG_POST_THROW_ANIM);
            m4aSongNumStart(SONG_VO_HO_VOICE00);
        }

        if ((w->flags & HOOK_FLAG_BOMB_THROWN) == 0) {
            if (AnimGetFrame(&work->base.anim) == 6 && work->base.anim.timer == 0) {
                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    args.x = act->x - 0x3200;
                    args.y = act->y;
                    args.z = act->z - 0x1C00;
                    args.facingLeft = 1;
                    args.variant = 1;
                } else {
                    args.x = act->x + 0x3200;
                    args.y = act->y;
                    args.z = act->z - 0x1C00;
                    args.facingLeft = 0;
                    args.variant = 1;
                }

                w->bombTask = TaskCreate(&w->tasks, &sTaskDescHumHookBomb, &args);
                w->bombTask2 = TaskCreate(&w->tasks, &sTaskDescHumHookBomb, &args);
                w->bombTask3 = TaskCreate(&w->tasks, &sTaskDescHumHookBomb, &args);
                w->flags |= HOOK_FLAG_BOMB_THROWN;
            }
        } else if (w->flags & HOOK_FLAG_POST_THROW_ANIM) {
            if (AnimIsFinished(&work->base.anim)) {
                AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 14, ANIM_FLAG_LOOP, w->base.tiles);
            }
        } else {
            if (AnimIsFinished(&work->base.anim)) {
                AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 13, 0, w->base.tiles);
                w->flags |= HOOK_FLAG_POST_THROW_ANIM;
            }
        }

        if ((w->flags & HOOK_FLAG_BOMB_THROWN) &&
            !IsTaskActiveNamed(w->bombTask, sTaskDescHumHookBomb.name) &&
            !IsTaskActiveNamed(w->bombTask2, sTaskDescHumHookBomb.name) &&
            !IsTaskActiveNamed(w->bombTask3, sTaskDescHumHookBomb.name)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 25:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
            w->bombTask = NULL;
            w->flags &= ~(HOOK_FLAG_BOMB_THROWN | HOOK_FLAG_POST_THROW_ANIM);
            m4aSongNumStart(SONG_VO_HO_VOICE00);
        }

        if ((w->flags & HOOK_FLAG_BOMB_THROWN) == 0) {
            if (AnimGetFrame(&work->base.anim) == 6 && work->base.anim.timer == 0) {
                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    args.x = act->x - 0x3200;
                    args.y = act->y;
                    args.z = act->z - 0x1C00;
                    args.facingLeft = 1;
                    args.variant = 0;
                } else {
                    args.x = act->x + 0x3200;
                    args.y = act->y;
                    args.z = act->z - 0x1C00;
                    args.facingLeft = 0;
                    args.variant = 0;
                }

                w->bombTask = TaskCreate(&w->tasks, &sTaskDescHumHookBomb, &args);
                w->flags |= HOOK_FLAG_BOMB_THROWN;
            }
        } else if (w->flags & HOOK_FLAG_POST_THROW_ANIM) {
            if (AnimIsFinished(&work->base.anim)) {
                AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 14, ANIM_FLAG_LOOP, w->base.tiles);
            }
        } else {
            if (AnimIsFinished(&work->base.anim)) {
                AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 13, 0, w->base.tiles);
                w->flags |= HOOK_FLAG_POST_THROW_ANIM;
            }
        }

        if ((w->flags & HOOK_FLAG_BOMB_THROWN) &&
            !IsTaskActiveNamed(w->bombTask, sTaskDescHumHookBomb.name)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 29:
        if (work->base.stateTimer == 0) {
            AnimReset(&work->base.anim);
            AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
            w->bombTask = NULL;
            w->flags &= ~HOOK_FLAG_BOMB_THROWN;
            m4aSongNumStart(SONG_VO_HO_VOICE00);
        }

        HumFaceTarget(&work->base, 1);

        if ((w->flags & HOOK_FLAG_BOMB_THROWN) == 0) {
            if (AnimGetFrame(&work->base.anim) == 6 && work->base.anim.timer == 0) {
                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    args.x = act->x - 0x3200;
                    args.y = act->y;
                    args.z = act->z - 0x1C00;
                    args.facingLeft = 1;
                    args.variant = 2;
                } else {
                    args.x = act->x + 0x3200;
                    args.y = act->y;
                    args.z = act->z - 0x1C00;
                    args.facingLeft = 0;
                    args.variant = 2;
                }

                w->bombTask = TaskCreate(&w->tasks, &sTaskDescHumHookBomb, &args);
                w->flags |= HOOK_FLAG_BOMB_THROWN;
            }
        }

        if (w->flags & HOOK_FLAG_BOMB_THROWN) {
            if (work->base.steps <= 4) {
                work->base.stateTimer = 0;
                work->base.steps++;
                work->base.state = 29;
            } else {
                if (!IsTaskActiveNamed(w->bombTask, sTaskDescHumHookBomb.name)) {
                    work->base.stateTimer = 0;
                    ClearBtlObjActionFlags(act);
                    work->base.state = 0;
                }
            }
        } else {
            work->base.stateTimer++;
        }

        break;
    case 20:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_HO_VOICE00);
        }

        f = AnimGetFrame(&work->base.anim);

        if (f > 1) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                s32 d = act->x + 0x1400;
                act->x += (act->originX - d) >> 3;
            } else {
                s32 d = act->x - 0x1400;
                act->x += (act->originX - d) >> 3;
            }
        }

        if (f == 2) {
            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                ? ApplyAttackBox(0x115, act->x - 0x2000, act->y, act->z, 16, 16, 50)
                : ApplyAttackBox(0x115, act->x + 0x2000, act->y, act->z, 16, 16, 50)) {
                m4aSongNumStart(SONG_BTL_MON_SWORD00);
            }
        } else if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }

        work->base.stateTimer++;
        break;
    case 19:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 8, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_HO_VOICE01);
        }

        f = AnimGetFrame(&work->base.anim);

        if (f >= 3 && f <= 5) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                s32 d = act->x + 0x4000;
                act->x += (act->originX - d) >> 3;
            } else {
                s32 d = act->x - 0x4000;
                act->x += (act->originX - d) >> 3;
            }
        }

        switch (f) {
        case 4:
        case 5:
            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                ? ApplyAttackBox(0x115, act->x - 0x4400, act->y, act->z, 20, 16, 50)
                : ApplyAttackBox(0x115, act->x + 0x4400, act->y, act->z, 20, 16, 50)) {
                m4aSongNumStart(SONG_BTL_MON_SWORD00);
            }

            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 21:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 10, 0, w->base.tiles);
        }

        HumFaceTarget(&work->base, 1);
        f = AnimGetFrame(&work->base.anim);

        switch (f) {
        case 2:
        case 6:
            if (work->base.anim.timer == 0) {
                if (GetRandom() & 1) {
                    m4aSongNumStart(SONG_VO_HO_VOICE00);
                } else {
                    m4aSongNumStart(SONG_VO_HO_VOICE01);
                }

                a = GetAngle(act->x, act->y, x, y);
                work->base.targetX = act->x + gSineTable[a] * 50;
                work->base.targetY = act->y + -gSineTable[a + 64] * 50;
                MakeOpponentsHittable();
            }

            act->x += (work->base.targetX - act->x) >> 3;
            act->y += (work->base.targetY - act->y) >> 3;

            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                ? ApplyAttackBox(278, act->x - 0x1000, act->y, act->z, 32, 24, 70)
                : ApplyAttackBox(278, act->x + 0x1000, act->y, act->z, 32, 24, 70)) {
                m4aSongNumStart(SONG_BTL_MON_SWORD01);
            }

            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 22:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 23;
            work->base.vz = w->speed;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 23: {
        s32 d;

        act->x += (work->base.targetX - act->x) >> 4;
        act->y += (work->base.targetY - act->y) >> 4;
        d = work->base.vz;

        if (d < 0) {
            if (d > -0x200) {
                AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            }
        } else if (d <= 0x1FF) {
            AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
        } else {
            AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
        }

        if (act->z >= 0) {
            work->base.stateTimer = 0;
            work->base.state = 24;
        } else {
            HumFaceTarget(&work->base, 1);
            work->base.stateTimer++;
        }

        break;
    }
    case 24:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHookAnimDefs, &w->base.anim, 7, 0, w->base.tiles);
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    }

    if (act->hp > 0) {
        gBtlWork->rotation = (SIN(w->angle / 2) * sHumHookRollAmplitudes[w->rollLevel]) >> 8;

        {
            s32 t;

            t = w->angle + 1;
            w->angle = t;

            if ((t & 511) == 0) {
                w->rollLevel++;

                if (w->rollLevel > 7) {
                    w->rollLevel = 1;
                }
            }
        }

        if (c->z >= c->groundZ && c->hp > 0 && c->badStatus != BAD_STATUS_STOP &&
            !(c->flags & BTLOBJ_FLAG_IN_CARD_ACTION)) {
            w->playerSlide += ((GetAngleDiff(0, gBtlWork->rotation) << 6) - w->playerSlide) >> 4;
            c->x -= w->playerSlide;
        } else {
            w->playerSlide = 0;
        }

        if (act->z >= act->groundZ && act->hp > 0 && act->badStatus != BAD_STATUS_STOP &&
            !(act->flags & BTLOBJ_FLAG_IN_CARD_ACTION)) {
            w->slide += ((GetAngleDiff(0, gBtlWork->rotation) << 6) - w->slide) >> 4;
            act->x -= w->slide;
        } else {
            w->slide = 0;
        }
    }

    TaskPoolUpdate(&w->tasks);
    return HumUpdate(&work->base);
}

void task_hum_hook_2(HookWork* work) {
    TaskPoolDraw(&work->tasks);
    HumDraw(&work->base);
}

void task_hum_hook_3(HookWork* work) {
    TaskPoolDestroy(&work->tasks);
    HumReleaseResources(&work->base);
    gBtlWork->rotation = 0;
}

void task_hum_hook_moon_0(HookMoonWork* work) {
    work->tiles = LoadObjTiles(gHumHookMoonTiles, 0xC00);
    PushPaletteEffect(0);
    work->palette = LoadObjPalette(gUnk_08F6DC64, 0x20);
    PopPaletteEffect();
    SetBtlPaletteFadeExcluded(work->palette->index + 16, 0);
    work->backdropSet = 0;
    work->angle = 0;
}

u8 task_hum_hook_moon_1(HookMoonWork* work) {
    work->angle++;
    return 1;
}

void task_hum_hook_moon_2(HookMoonWork* work) {
    s16 x;
    s16 y;
    u16 v;
    u16 t;
    s32 s;

    x = 248 - (gBtlWork->viewX >> 9);
    y = 208 - (gBtlWork->viewY >> 9);
    s = gSineTable[(u8)work->angle];
    y += s >> 5;
    DrawSprite(x + 64, y - 28, gHumHookMoonFrame0, work->tiles, work->palette, NULL, SPRITE_PRIORITY(3), 0xFFFF);
    DrawSprite(x - 144, y, gHumHookMoonFrame1, work->tiles, work->palette, NULL, SPRITE_PRIORITY(3), 0xFFFE);
    DrawSprite(x - 88, y, gHumHookMoonFrame1, work->tiles, work->palette, NULL, SPRITE_PRIORITY(3), 0xFFFE);
    DrawSprite(x - 32, y, gHumHookMoonFrame1, work->tiles, work->palette, NULL, SPRITE_PRIORITY(3), 0xFFFE);
    DrawSprite(x + 24, y, gHumHookMoonFrame1, work->tiles, work->palette, NULL, SPRITE_PRIORITY(3), 0xFFFE);
    DrawSprite(x + 80, y, gHumHookMoonFrame1, work->tiles, work->palette, NULL, SPRITE_PRIORITY(3), 0xFFFE);
    v = FadeGetAmount();

    if (v != 0) {
        switch (FadeGetColor()) {
        case 0:
            t = 9 - v;

            if ((s16)t < 0) {
                t = 0;
            }

            SetBackdropColor(0, 0, t);
            break;
        case 0x7FFF:
            t = v + 9;

            if ((s16)t > 31) {
                t = 31;
            }

            SetBackdropColor(v, v, t);
            break;
        case 31:
            SetBackdropColor(v, 0, 9);
            break;
        case 0x7C00:
            t = v + 9;

            if ((s16)t > 31) {
                t = 31;
            }

            SetBackdropColor(0, 0, t);
            break;
        case 0x3E0:
            SetBackdropColor(0, v, 9);
            break;
        }

        work->backdropSet = 1;
    } else if (work->backdropSet) {
        SetBackdropColor(0, 0, 9);
        work->backdropSet = v;
    }
}

void task_hum_hook_moon_3(HookMoonWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_hum_hook_bomb_0(HookBombWork* work, VixenNdlArgs* args) {
    if (args->facingLeft != 0) {
        work->facingLeft = 1;
    } else {
        work->facingLeft = 0;
    }

    work->palette = LoadObjPalette(gPBakudanPalette, 0x20);
    work->tiles = AllocObjTiles(0x280, gPBakudanTiles);
    AnimInit(&work->anim, gPBakudanAnims, gPBakudanFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->x = args->x;
    work->y = args->y;
    work->z = args->z;
    work->variant = args->variant;
    work->timer = 0;
    work->bounceCount = 0;
    work->speed = GetRandom() % 0x201 + 0x14C;
    work->vz = -(GetRandom() % 0x201 + 0x100);

    switch (work->variant) {
    case 0:
        work->angle = GetAngle(work->x, work->y,
            gBtlWork->targetX, gBtlWork->targetY);
        work->maxBounces = GetRandom() % 3 + 1;
        work->state = 0;
        break;
    case 2:
        work->angle = GetAngle(work->x, work->y,
            gBtlWork->targetX, gBtlWork->targetY);
        work->maxBounces = 0;
        work->state = 1;
        break;
    case 1:
    default:
        work->angle = GetRandom();
        work->maxBounces = GetRandom() % 5 + 4;
        work->state = 0;
        break;
    }

    work->tiles2 = LoadObjTiles(gBtlShadowSmallTiles, 0x200);
    work->palette2 = LoadObjPalette(gBStatesPalette, 0x20);
    work->visible = 1;
}

u8 task_hum_hook_bomb_1(HookBombWork* work) {
    if ((gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) == 0) {
        return 0;
    }

    switch (work->state) {
    case 0:
        work->x += gSineTable[work->angle] * work->speed >> 8;
        work->y += -gSineTable[work->angle + 64] * work->speed >> 8;
        work->z += work->vz;
        work->vz += 64;

        if (work->z > 0) {
            work->z = 0;

            if (work->bounceCount >= work->maxBounces) {
                work->timer = 0;
                work->state = 1;
                break;
            }

            work->vz = -(GetRandom() % 0x301 + 0x200);

            if (work->variant == 0) {
                work->angle = GetAngle(work->x, work->y,
                    gBtlWork->targetX, gBtlWork->targetY);
            } else {
                work->angle = GetRandom();
            }

            work->bounceCount++;
        }

        if (TestAttackBox(work->x, work->y, work->z, 2, 2, 2)) {
            work->timer = 0;
            work->state = 1;
            break;
        }

        work->timer++;
        break;
    default:
        if (work->timer == 0) {
            AnimStart(&work->anim, 1, 0);
        }

        if (work->timer <= 17) {
            work->x += gSineTable[work->angle] * work->speed >> 8;
            work->y += -gSineTable[work->angle + 64] * work->speed >> 8;
            work->z += work->vz;
            work->vz += 64;

            if (work->z > 0) {
                work->z = 0;
                work->vz = -(GetRandom() % 0x301 + 0x200);
                work->angle = GetAngle(work->x, work->y,
                    gBtlWork->targetX, gBtlWork->targetY);
            }
        } else if (work->timer == 18) {
            MakeOpponentsHittable();
            BgFxStartExplosion(work->x, work->y, work->z);
            work->visible = 0;
        } else if (work->timer > 18) {
            if (ApplyAttackBox(0x117, work->x, work->y, work->z, 24, 24, 24)) {
                m4aSongNumStart(SONG_BTL_BW_PACHIN);
            }
        }

        if (work->timer > 17 && !BgFxIsActive()) {
            return 0;
        }

        work->timer++;
        break;
    }

    if (ClampBattlePosition(&work->x, &work->y, 0, 0)) {
        work->angle = (u8)(work->angle + 118) + GetRandom() % 21;
    }

    AnimUpdate(&work->anim);
    return 1;
}

void task_hum_hook_bomb_2(HookBombWork* work) {
    void* gfx;
    u16 attr;
    s16 x;
    s16 y;

    if (!work->visible) {
        return;
    }

    gfx = AnimGetGfx(&work->anim);
    attr = GetBattleSpritePriorityFlags(work->y);

    if (!work->facingLeft) {
        attr |= 1;
    }

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gfx, work->tiles, work->palette, NULL, attr,
        -0x1004 - ((work->y + 0x800) >> 8) * 4);
    WorldToScreen(&x, &y, work->x, work->y, 0);
    DrawSprite(x, y, gBtlShadowSmallFrame0, work->tiles2, work->palette2, NULL, attr, 0xFFF0);
}

void task_hum_hook_bomb_3(HookBombWork* work) {
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette2);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}
