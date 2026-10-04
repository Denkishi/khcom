/**
 * emy_21.c
 * Barrel Spider Enemy
 */

#include "task_descriptors.h"
#include "emy.h"
#include "sprites_emy.h"
#include "enemy_common.h"
#include "songs.h"
#include "emy_tasks.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "enemy_types.h"
#include "m4a_song.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "sprite_palettes.h"

static const AnimDef sEmy21CommonAnimDefs[3] = {
    { gEmy2100Frames, gEmy2100Anims, gEmy2100Tiles, 0, { 0, 0, 0 } },
    { gEmy2102Frames, gEmy2102Anims, gEmy2102Tiles, 0, { 0, 0, 0 } },
    { gEmy2101Frames, gEmy2101Anims, gEmy2101Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy21AnimDefs[4] = {
    { gEmy2110Frames, gEmy2110Anims, gEmy2110Tiles, 0, { 0, 0, 0 } },
    { gEmy2111Frames, gEmy2111Anims, gEmy2111Tiles, 0, { 0, 0, 0 } },
    { gEmy2111Frames, gEmy2111Anims, gEmy2111Tiles, 1, { 0, 0, 0 } },
    { gEmy2111fFrames, gEmy2111fAnims, gEmy2111fTiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy21Def = { gEmy21Palette, sEmy21CommonAnimDefs, 396, 130, 20, 20, 80, 80, 16, 5, 0, { 14, 40, 32, 16, 16, 100, 0 } };

TaskDesc gTaskDescEmy21 = {
    "task_emy_21",
    (TaskInitFunc)task_emy_21_0,
    (TaskUpdateFunc)task_emy_21_1,
    (TaskDrawFunc)task_emy_21_2,
    (TaskDestroyFunc)task_emy_21_3,
    sizeof(Emy21Work),
};

void task_emy_21_0(Emy21Work* work, void* obj) {
    EmyInit(&work->base, &sEmy21Def, obj);
    work->dashSpeed = 0;
}

u8 task_emy_21_1(Emy21Work* work) {
    Emy21Work* w;
    BtlObj* act;
    s32 pos;
    s32 d;

    w = work;
    act = &work->base.actor;

    if (EmyUpdateReaction(&work->base)) {
        GetEnemyTargetPosition(act, &pos, NULL, NULL);
        d = pos - act->x;

        if (d >= 0 ? d <= 0x3FFF : act->x - pos <= 0x3FFF) {
            work->base.state = 0x12;
        } else {
            work->base.state = 0x14;
        }
    } else if (work->base.state == 5 && work->base.stateTimer == 0) {
        m4aSongNumStop(SONG_EF_TARU_BOMB);
    }

    switch (work->base.state) {
    case 0x12:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sEmy21AnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        }

        if (work->base.stateTimer > 29) {
            work->base.stateTimer = 0;
            work->base.state = 0x13;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 0x13: {
        u16 t;

        t = work->base.stateTimer;

        if (t >= 12 && t <= 39) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                ApplyAttackBox(0xBD, act->x, act->y, act->z, 30, 30, 32);
            } else {
                ApplyAttackBox(0xBD, act->x, act->y, act->z, 30, 30, 32);
            }
        }

        switch (work->base.stateTimer) {
        case 2:
            MakeOpponentsHittable();
            BgFxStartExplosion(work->base.actor.x, work->base.actor.y,
                work->base.actor.z - 0x1000);
            break;
        case 40:
            ClearBtlObjActionFlags(act);
            return 0;
        }

        work->base.stateTimer++;
        break;
    }
    case 0x14:
        AnimChangeWithDef(sEmy21AnimDefs, &w->base.anim, 1, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 0x15;
        }

        break;
    case 0x15:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sEmy21AnimDefs, &w->base.anim, 2, ANIM_FLAG_LOOP, w->base.tiles);
            w->dashSpeed = 0;
        }

        act->x = act->flags & BTLOBJ_FLAG_FACING_LEFT ? act->x - w->dashSpeed : act->x + w->dashSpeed;
        w->dashSpeed += 43;

        if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
            ? ApplyAttackBox(0xBE, act->x, act->y, act->z, 20, 32, 32)
            : ApplyAttackBox(0xBE, act->x, act->y, act->z, 20, 32, 32)) {
            work->base.stateTimer = 0;
            work->base.state = 0x13;
        } else if (work->base.stateTimer > 28) {
            work->base.stateTimer = 0;
            work->base.state = 0x16;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 0x16:
        AnimChangeWithDef(sEmy21AnimDefs, &w->base.anim, 3, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 0x13;
            break;
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetFrame(&work->base.anim)) {
            case 0:
            case 1:
                act->x -= 0x380;
                act->y += 0x80;
                break;
            case 2:
                act->x -= 0x680;
                act->y += 0x280;
                break;
            case 3:
                act->x -= 0x500;
                act->y += 0x280;
                break;
            case 4:
                act->x -= 0x580;
                act->y += 0xC0;
                break;
            case 5:
                act->x -= 0x280;
                act->y += 0x3C0;
                break;
            case 6:
                act->x -= 0x180;
                break;
            case 7:
                act->x += 0x80;
                act->y += 0x40;
                break;
            }
        }

        act->x = act->flags & BTLOBJ_FLAG_FACING_LEFT ? act->x - w->dashSpeed : act->x + w->dashSpeed;
        w->dashSpeed -= 46;

        if (w->dashSpeed < 0) {
            w->dashSpeed = 0;
        }

        work->base.stateTimer++;
        break;
    }

    return EmyUpdateCommonStates(&work->base);
}

void task_emy_21_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_21_3(EmyWork* work) {
    EmyReleaseResources(work);
}
