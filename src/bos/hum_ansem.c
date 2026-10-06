/**
 * hum_ansem.c
 * Ansem Boss
 */

#include "system_state.h"
#include "fade.h"
#include "hum.h"
#include "sprites_hum.h"
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
#include "engine_math.h"
#include "hum_types.h"
#include "m4a_song.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "sprite_palettes.h"

static const u32 sHumAnsemStockMovesA[3] = {
    36, 37, 37,
};

static const u32 sHumAnsemStockMovesB[3] = {
    36, 37, 36,
};

static const AnimDef sHumAnsemAnimDefs[7] = {
    { gAnsemBt00Frames, gAnsemBt00Anims, gAnsemBt00Tiles, 0 },
    { gAnsemBt01Frames, gAnsemBt01Anims, gAnsemBt01Tiles, 0 },
    { gAnsemBt03Frames, gAnsemBt03Anims, gAnsemBt03Tiles, 0 },
    { gAnsemBt04Frames, gAnsemBt04Anims, gAnsemBt04Tiles, 0 },
    { gAnsemBt05Frames, gAnsemBt05Anims, gAnsemBt05Tiles, 0 },
    { gAnsemBt05Frames, gAnsemBt05Anims, gAnsemBt05Tiles, 1 },
    { gAnsemBt05Frames, gAnsemBt05Anims, gAnsemBt05Tiles, 2 },
};

static const AnimDef sHumAnsemBackAnimDefs[10] = {
    { gAnsembackBt00Frames, gAnsembackBt00Anims, gAnsembackBt00Tiles, 0 },
    { gAnsembackBt01Frames, gAnsembackBt01Anims, gAnsembackBt01Tiles, 0 },
    { gAnsembackBt02Frames, gAnsembackBt02Anims, gAnsembackBt02Tiles, 0 },
    { gAnsembackBt03Frames, gAnsembackBt03Anims, gAnsembackBt03Tiles, 0 },
    { gAnsembackBt03bFrames, gAnsembackBt03bAnims, gAnsembackBt03bTiles, 1 },
    { gAnsembackBt03bFrames, gAnsembackBt03bAnims, gAnsembackBt03bTiles, 0 },
    { gAnsembackBt04Frames, gAnsembackBt04Anims, gAnsembackBt04Tiles, 0 },
    { gAnsembackBt05Frames, gAnsembackBt05Anims, gAnsembackBt05Tiles, 0 },
    { gAnsembackBt05Frames, gAnsembackBt05Anims, gAnsembackBt05Tiles, 1 },
    { gAnsembackBt05Frames, gAnsembackBt05Anims, gAnsembackBt05Tiles, 2 },
};

static const HumSubDef sHumAnsemSubDef = { gAnsembackPalette, 128 };

static const HumDef sHumAnsemDef = { 80, gAnsemPalette, 0, { 52, 99, 65, 14, 42, 99, 0 } };

TaskDesc gTaskDescHumAnsem = {
    "task_hum_ansem",
    (TaskInitFunc)task_hum_ansem_0,
    (TaskUpdateFunc)task_hum_ansem_1,
    (TaskDrawFunc)task_hum_ansem_2,
    (TaskDestroyFunc)task_hum_ansem_3,
    sizeof(AnsemWork),
};

void AnsemHover(HumWork* work, s32 hoverZ) {
    BtlObj* act = &work->actor;
    s32 t;

    if (hoverZ != 0) {
        t = hoverZ + gSineTable[gFrameCounter * 4 % 256] * 8;
        work->vz = 0;
        act->z += (t - act->z) >> 4;
    }
}

void AnsemPlaceSub(AnsemWork* work) {
    BtlObj* act = &work->base.actor;

    if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
        work->subOffsetX += (0x1800 - work->subOffsetX) >> 3;
    } else {
        work->subOffsetX += (-0x1800 - work->subOffsetX) >> 3;
    }

    work->subOffsetZ += (-0x1200 - work->subOffsetZ) >> 3;
    work->sub.x = act->x + work->subOffsetX;
    work->sub.y = act->y;
    work->sub.z = act->z + work->subOffsetZ;
}

void task_hum_ansem_0(AnsemWork* work) {
    HumInit(&work->base, &sHumAnsemDef);
    HumSubInit(&work->base, &work->sub, &sHumAnsemSubDef);
    work->hoverZ = -0xC00;
    work->subOffsetX = 0;
    work->base.boundsMargin = -50;
    work->base.stockMoves = sHumAnsemStockMovesA;
}

u8 task_hum_ansem_1(AnsemWork* work) {
    AnsemWork* w;
    BtlObj* act;
    s32 x;
    s32 y;
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &x, &y, NULL);

    switch (HumUpdateReaction(&work->base)) {
    case 5:
        work->base.stateTimer = 0;
        act->flags &= ~(BTLOBJ_FLAG_GUARD_PHYSICAL | BTLOBJ_FLAG_INVULNERABLE);
        MakeOpponentsHittable();

        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
        case 38:
            work->base.state = 20;
            break;
        case 37:
        case 39:
            work->base.state = 25;
            break;
        case 0xFADEB7A3:
            work->base.state = 26;
            work->repeatCount = 0;
            break;
        case 0xFA3EB7A3:
            work->base.state = 21;
            work->repeatCount = 0;
            break;
        }

        break;
    case 4:
        act->flags &= ~(BTLOBJ_FLAG_GUARD_PHYSICAL | BTLOBJ_FLAG_INVULNERABLE);
        work->sub.flags &= ~(HUM_SUB_FLAG_IN_FRONT | HUM_SUB_FLAG_OWN_DEPTH);
        break;
    }

    if (gBtlWork->battleId == 166) {
        HumChooseCardAction(&work->base, 30, 80, 80, 24);
    } else if (HumChooseCardAction(&work->base, 2, 80, 80, 24)) {
        if (GetRandom() % 2) {
            work->base.stockMoves = sHumAnsemStockMovesA;
        } else {
            work->base.stockMoves = sHumAnsemStockMovesB;
        }
    }

    switch (work->base.state) {
    case 12:
    case 18:
        AnimChangeWithDef(sHumAnsemAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        AnimChangeWithDef(sHumAnsemBackAnimDefs, &w->base.sub->anim, 0, ANIM_FLAG_LOOP, w->base.sub->tiles);
        break;
    case 17:
        AnimChangeWithDef(sHumAnsemAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        AnimChangeWithDef(sHumAnsemBackAnimDefs, &w->base.sub->anim, 0, ANIM_FLAG_LOOP, w->base.sub->tiles);
        w->hoverZ = -0x5000;
        break;
    case 0:
        AnimChangeWithDef(sHumAnsemAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        AnimChangeWithDef(sHumAnsemBackAnimDefs, &w->base.sub->anim, 0, ANIM_FLAG_LOOP, w->base.sub->tiles);
        w->hoverZ = -0xC00;

        if (func_08081828()) {
            break;
        }

        if (gBtlWork->battleId == 177) {
            if ((u16)(GetRandom() % 15) == 0) {
                if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
                    work->base.state = 29;
                    work->base.stateTimer = 0;
                    break;
                }
            }
        }

        if ((u16)(GetRandom() % 80) == 0) {
            work->base.state = 8;
            work->base.stateTimer = 0;
            break;
        }

        HumFaceTarget(&work->base, 3);
        work->base.stateTimer++;
        break;
    case 8:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumAnsemAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
            AnimChangeWithDef(sHumAnsemBackAnimDefs, &w->base.sub->anim, 0, ANIM_FLAG_LOOP, w->base.sub->tiles);
            w->hoverZ = -0xC00;
            work->base.targetY = y;

            if (act->x < x) {
                work->base.targetX = x - 0x7800;
            } else {
                work->base.targetX = x + 0x7800;
            }
        }

        if (gBtlWork->battleId == 177) {
            if ((u16)(GetRandom() % 30) == 0) {
                if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
                    work->base.state = 29;
                    work->base.stateTimer = 0;
                    break;
                }
            }
        }

        if (HumMoveToward(&work->base, work->base.targetX, work->base.targetY, 0x300)) {
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }

        HumFaceTarget(&work->base, 1);
        work->base.stateTimer++;
        break;
    case 1:
    case 3:
    case 9:
    case 11:
    case 14:
        w->hoverZ = 0;
        AnimChangeWithDef(sHumAnsemAnimDefs, &w->base.anim, 1, 0, w->base.tiles);
        AnimChangeWithDef(sHumAnsemBackAnimDefs, &w->base.sub->anim, 1, 0, w->base.sub->tiles);
        break;
    case 2:
        if (gBtlWork->battleId != 177) {
            break;
        }

        if (!(gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION)) {
            break;
        }

        if (!(GetRandom() % 2)) {
            break;
        }

        work->base.state = 29;
        work->base.stateTimer = 0;
        break;
    case 20:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumAnsemAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
            AnimChangeWithDef(sHumAnsemBackAnimDefs, &w->base.sub->anim, 2, 0, w->base.sub->tiles);
            w->hoverZ = -0x800;
            m4aSongNumStart(SONG_VO_AN_ATTACK00);
        }

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            s32 d = act->x - 0x2800;
            act->x = act->x + ((x - d) >> 4);
        } else {
            s32 d = act->x + 0x2800;
            act->x = act->x + ((x - d) >> 4);
        }

        act->y += (y - act->y) >> 4;

        switch (AnimGetFrame(&w->sub.anim)) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                act->x -= 0x100;
            } else {
                act->x += 0x100;
            }

            break;
        case 4:
            w->sub.flags |= HUM_SUB_FLAG_IN_FRONT;

            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                ? ApplyAttackBox(0x140, act->x - 0x2000, act->y, act->z, 20, 12, 24)
                : ApplyAttackBox(0x140, act->x + 0x2000, act->y, act->z, 20, 12, 24)) {
                m4aSongNumStart(SONG_BTL_MON_HIT06);
            }

            break;
        }

        if (AnimIsFinished(&w->sub.anim)) {
            w->sub.flags &= ~HUM_SUB_FLAG_IN_FRONT;
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 21:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumAnsemAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
            AnimChangeWithDef(sHumAnsemBackAnimDefs, &w->base.sub->anim, 3, 0, w->base.sub->tiles);
            w->subRiseSpeed = 0;
            FadeStartOut(FADE_MODE_DARK_MAGENTA, 90);
            m4aSongNumStart(SONG_BTL_AN_STANDENTRY);
            w->hoverZ = -0xC00;
        }

        switch (AnimGetFrame(&w->sub.anim)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            AnsemPlaceSub(w);
            break;
        default:
            w->subRiseSpeed += 25;
            w->sub.z -= w->subRiseSpeed;
            break;
        }

        if (AnimIsFinished(&w->sub.anim)) {
            work->base.state = 22;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 22:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumAnsemAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
            AnimChangeWithDef(sHumAnsemBackAnimDefs, &w->base.sub->anim, 5, 0, w->base.sub->tiles);
        }

        w->subRiseSpeed += 25;
        w->sub.z -= w->subRiseSpeed;

        if (w->sub.z < -0x12C00) {
            work->base.state = 23;
            work->base.stateTimer = 0;
            break;
        }

        work->base.stateTimer++;
        break;
    case 23:
        if (work->base.stateTimer == 0) {
            AnimReset(&w->sub.anim);
            AnimChangeWithDef(sHumAnsemAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
            AnimChangeWithDef(sHumAnsemBackAnimDefs, &w->base.sub->anim, 4, 0, w->base.sub->tiles);
            w->subRiseSpeed = 0x800;
            w->sub.x = x + (d = ((u16)(GetRandom() % 65) << 8) - 0x2000);
            w->sub.y = y;
            w->sub.z = 0;
            w->sub.flags |= HUM_SUB_FLAG_OWN_DEPTH;
            m4aSongNumStart(SONG_EF_AN_STANDUP);
        }

        switch (AnimGetFrame(&w->sub.anim)) {
        case 5:
            if (w->sub.anim.timer == 4) {
                m4aSongNumStart(SONG_EF_BOSS_DEADL);
            }

            break;
        case 6:
            w->subRiseSpeed += 25;
            w->sub.z -= w->subRiseSpeed;
            break;
        }

        if ((s16)(work->base.stateTimer % 10) == 0) {
            MakeOpponentsHittable();
        }

        switch (AnimGetFrame(&w->sub.anim)) {
        case 2:
        case 3:
            if (ApplyAttackBox(0x141, w->sub.x, w->sub.y,
                    w->sub.z - 0x800, 20, 16, 8)) {
                m4aSongNumStart(SONG_BTL_MON_HIT06);
            }

            break;
        case 4:
            if (ApplyAttackBox(0x141, w->sub.x, w->sub.y,
                    w->sub.z - 0x1000, 20, 16, 16)) {
                m4aSongNumStart(SONG_BTL_MON_HIT00);
            }

            break;
        case 5:
            if (ApplyAttackBox(0x141, w->sub.x, w->sub.y,
                    w->sub.z - 0x2000, 20, 16, 32)) {
                m4aSongNumStart(SONG_BTL_MON_HIT00);
            }

            break;
        case 6:
            if (ApplyAttackBox(0x141, w->sub.x, w->sub.y,
                    w->sub.z - 0x3000, 20, 16, 48)) {
                m4aSongNumStart(SONG_BTL_MON_HIT00);
            }

            break;
        }

        if (w->sub.z < -0x12C00) {
            w->sub.flags &= ~HUM_SUB_FLAG_OWN_DEPTH;
            work->base.stateTimer = 0;

            if (w->repeatCount > 6) {
                work->base.state = 24;
                break;
            }

            work->base.state = 23;
            w->repeatCount++;
            break;
        }

        work->base.stateTimer++;
        break;
    case 24:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumAnsemBackAnimDefs, &w->base.sub->anim, 0, ANIM_FLAG_LOOP, w->base.sub->tiles);
            w->steps = 30;
        }

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            ApproachValueHalfSteps(&w->sub.x, act->x + 0x1800, w->steps);
        } else {
            ApproachValueHalfSteps(&w->sub.x, act->x - 0x1800, w->steps);
        }

        ApproachValueHalfSteps(&w->sub.y, act->y, w->steps);
        ApproachValueHalfSteps(&w->sub.z, act->z, w->steps);
        w->steps--;

        if (w->steps <= 0) {
            FadeStartIn(FADE_MODE_BLACK, 30);
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 29:
        if (work->base.stateTimer == 0) {
            AnimReset(&w->sub.anim);
            AnimChangeWithDef(sHumAnsemBackAnimDefs, &w->base.sub->anim, 7, 0, w->base.sub->tiles);
            w->sub.flags |= HUM_SUB_FLAG_IN_FRONT;
            act->originX = act->x;
            act->flags |= BTLOBJ_FLAG_CARD_USE_BLOCKED;
        }

        HumFaceTarget(&work->base, 1);

        if (AnimGetFrame(&w->sub.anim) != 0) {
            act->flags |= (BTLOBJ_FLAG_GUARD_PHYSICAL | BTLOBJ_FLAG_INVULNERABLE);

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                s32 d = act->x - 0x1000;
                act->x = act->x + ((act->originX - d) >> 2);
            } else {
                s32 d = act->x + 0x1000;
                act->x = act->x + ((act->originX - d) >> 2);
            }

            w->subOffsetX += (0 - w->subOffsetX) >> 2;
            w->subOffsetZ += (0 - w->subOffsetZ) >> 2;
            w->sub.x = act->x + w->subOffsetX;
            w->sub.y = act->y;
            w->sub.z = act->z + w->subOffsetZ;
        }

        if (work->base.stateTimer == 25) {
            act->flags &= ~BTLOBJ_FLAG_CARD_USE_BLOCKED;
        }

        if (work->base.stateTimer > 50) {
            w->sub.flags &= ~HUM_SUB_FLAG_IN_FRONT;
            act->flags &= ~(BTLOBJ_FLAG_GUARD_PHYSICAL | BTLOBJ_FLAG_INVULNERABLE);
            work->base.stateTimer = 0;
            work->base.state = 0;
            break;
        }

        work->base.stateTimer++;
        break;
    case 26:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumAnsemAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            AnimChangeWithDef(sHumAnsemBackAnimDefs, &w->base.sub->anim, 7, 0, w->base.sub->tiles);
            w->hoverZ = -0xC00;
            m4aSongNumStart(SONG_VO_AN_ATTACK01);
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 27;
            break;
        }

        work->base.stateTimer++;
        break;
    case 27:
        if (work->base.stateTimer == 0) {
            if (act->x <= 0xFFFF) {
                work->base.targetX = (gBtlWork->xMax - 48) << 8;
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            } else {
                work->base.targetX = (gBtlWork->xMin + 48) << 8;
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            }

            work->base.targetY = y;
            AnimReset(&work->base.anim);
            AnimReset(&w->sub.anim);
            AnimChangeWithDef(sHumAnsemAnimDefs, &w->base.anim, 5, ANIM_FLAG_LOOP, w->base.tiles);
            AnimChangeWithDef(sHumAnsemBackAnimDefs, &w->base.sub->anim, 8, ANIM_FLAG_LOOP, w->base.sub->tiles);
            w->hoverZ = -0xC00;
            w->steps = 40;
            BgFxStartAnsemRush(w->sub.x, w->sub.y,
                w->sub.z - 0x2100, act->flags & BTLOBJ_FLAG_FACING_LEFT);
        }

        a = w->sub.x;
        b = w->sub.y;
        c = w->sub.z;

        if (w->steps > 0) {
            ApproachValue(&act->x, work->base.targetX, w->steps);
            ApproachValueHalfSteps(&act->y, work->base.targetY, w->steps);
        }

        w->steps--;

        if (work->base.stateTimer > 5) {
            w->sub.flags |= HUM_SUB_FLAG_IN_FRONT;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                w->subOffsetX += (-0x2200 - w->subOffsetX) >> 3;
            } else {
                w->subOffsetX += (0x2200 - w->subOffsetX) >> 3;
            }

            w->subOffsetZ += (0 - w->subOffsetZ) >> 3;
            w->sub.x = act->x + w->subOffsetX;
            w->sub.y = act->y;
            w->sub.z = act->z + w->subOffsetZ;
        } else {
            AnsemPlaceSub(w);
        }

        if (ApplyAttackBox(0x143, w->sub.x, w->sub.y,
                w->sub.z, 32, 16, 32)) {
            m4aSongNumStart(SONG_BTL_MON_HIT02);
        }

        BgFxAddPosition(w->sub.x - a, w->sub.y - b, w->sub.z - c);

        if (w->steps <= 0) {
            w->sub.flags &= ~HUM_SUB_FLAG_IN_FRONT;
            work->base.stateTimer = 0;

            if (w->repeatCount > 3) {
                work->base.state = 28;
                break;
            }

            work->base.state = 27;
            w->repeatCount++;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 28:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumAnsemAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
            AnimChangeWithDef(sHumAnsemBackAnimDefs, &w->base.sub->anim, 9, 0, w->base.sub->tiles);
            w->hoverZ = -0xC00;
        }

        if (!AnimIsFinished(&work->base.anim)) {
            break;
        }

        ClearBtlObjActionFlags(act);
        work->base.state = 0;
        work->base.stateTimer = 0;
        break;
    case 25:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumAnsemAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
            AnimChangeWithDef(sHumAnsemBackAnimDefs, &w->base.sub->anim, 6, 0, w->base.sub->tiles);
            FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
            w->hoverZ = -0xC00;
        }

        if (work->base.stateTimer == 20) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                BgFxStartAnsemWave(act->x, act->y, 0, 1, 0x142);
            } else {
                BgFxStartAnsemWave(act->x, act->y, 0, 0, 0x142);
            }
        }

        switch (AnimGetFrame(&w->sub.anim)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            AnsemPlaceSub(w);
            break;
        case 5:
            if (w->sub.anim.timer == 0) {
                w->steps = 8;
            }

            if (w->steps > 0) {
                ApproachValueHalfSteps(&w->sub.z, act->z - 0x3000, w->steps);
                w->steps--;
            }

            break;
        case 6:
            if (w->sub.anim.timer == 0) {
                w->steps = 8;
            }

            if (w->steps > 0) {
                ApproachValueHalfSteps(&w->sub.z, act->z - 0x1000, w->steps);
                w->steps--;
            }

            break;
        }

        if (AnimIsFinished(&w->sub.anim)) {
            if (!BgFxIsActive()) {
                ClearBtlObjActionFlags(act);
                FadeToOriginal(FADE_MODE_BLACK, 8);
                work->base.state = 0;
                work->base.stateTimer = 0;
                break;
            }
        }

        work->base.stateTimer++;
        break;
    }

    if (!(act->flags & BTLOBJ_FLAG_HURT) && act->badStatus != BAD_STATUS_STOP) {
        AnsemHover(&work->base, w->hoverZ);
    }

    switch (work->base.state) {
    case 21:
    case 22:
    case 23:
    case 25:
    case 27:
    case 29:
        break;
    default:
        AnsemPlaceSub(w);
        break;
    }

    return HumUpdate(&work->base);
}

void task_hum_ansem_2(HumWork* work) {
    HumDraw(work);
}

void task_hum_ansem_3(HumWork* work) {
    HumReleaseResources(work);
}
