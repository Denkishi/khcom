/**
 * hum_laxene.c
 * Larxene Boss
 */

#include "system_state.h"
#include "fade.h"
#include "obj_api.h"
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

static const u32 sHumLaxeneStockMoves[2][3] = {
    { 36, 38, 38 },
    { 37, 37, 36 },
};

static const AnimDef sHumLaxeneAnimDefs[15] = {
    { gLaxineIdleFrames, gLaxineIdleAnims, gLaxineIdleTiles, 0 },
    { gLaxineMoveFrames, gLaxineMoveAnims, gLaxineMoveTiles, 0 },
    { gLaxineMoveFrames, gLaxineMoveAnims, gLaxineMoveTiles, 1 },
    { gLaxineDamageFrames, gLaxineDamageAnims, gLaxineDamageTiles, 0 },
    { gLaxineRenzokFrames, gLaxineRenzokAnims, gLaxineRenzokTiles, 1 },
    { gLaxineRenzokFrames, gLaxineRenzokAnims, gLaxineRenzokTiles, 2 },
    { gLaxineMagicFrames, gLaxineMagicAnims, gLaxineMagicTiles, 0 },
    { gLaxineMagicFrames, gLaxineMagicAnims, gLaxineMagicTiles, 1 },
    { gLaxineMagicFrames, gLaxineMagicAnims, gLaxineMagicTiles, 2 },
    { gLaxineMagicFrames, gLaxineMagicAnims, gLaxineMagicTiles, 3 },
    { gLaxineMagicFrames, gLaxineMagicAnims, gLaxineMagicTiles, 4 },
    { gLaxineMagicFrames, gLaxineMagicAnims, gLaxineMagicTiles, 5 },
    { gLaxineKnifethrowFrames, gLaxineKnifethrowAnims, gLaxineKnifethrowTiles, 0 },
    { gLaxineRenzokFrames, gLaxineRenzokAnims, gLaxineRenzokTiles, 3 },
    { gLaxineRenzokFrames, gLaxineRenzokAnims, gLaxineRenzokTiles, 4 },
};

static const HumDef sHumLaxeneDef = { 128, gLaxinePalette, 0, { 49, 99, 60, 14, 46, 99, 0 } };

TaskDesc gTaskDescHumLaxene = {
    "task_hum_laxene",
    (TaskInitFunc)task_hum_laxene_0,
    (TaskUpdateFunc)task_hum_laxene_1,
    (TaskDrawFunc)task_hum_laxene_2,
    (TaskDestroyFunc)task_hum_laxene_3,
    sizeof(LaxeneWork),
};

static TaskDesc sTaskDescHumLaxeneKnf = {
    "task_hum_laxene_knf",
    (TaskInitFunc)task_hum_laxene_knf_0,
    (TaskUpdateFunc)task_hum_laxene_knf_1,
    (TaskDrawFunc)task_hum_laxene_knf_2,
    (TaskDestroyFunc)task_hum_laxene_knf_3,
    sizeof(LaxeneKnfWork),
};

void LaxeneHover(HumWork* work, s32 hoverZ) {
    BtlObj* act;
    s32 t;

    if (hoverZ != 0) {
        act = &work->actor;
        t = hoverZ + gSineTable[gFrameCounter * 4 % 256] * 6;
        work->vz = 0;
        act->z += (t - act->z) >> 3;
    }
}

void CreateHumLaxeneKnfTask(LaxeneWork* work, s16 dx, s16 dz) {
    BtlObj* act = &work->base.actor;
    VixenNdlArgs args;

    if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
        args.x = act->x + (dx << 8);
        args.facingLeft = 1;
    } else {
        args.x = act->x - (dx << 8);
        args.facingLeft = 0;
    }

    args.z = act->z + (dz << 8);
    args.y = act->y;
    TaskCreate(&work->tasks, &sTaskDescHumLaxeneKnf, &args);
}

void task_hum_laxene_0(LaxeneWork* work) {
    HumInit(&work->base, &sHumLaxeneDef);
    work->flags = 0;
    work->hoverZ = -0x3000;
    work->scaleSteps = 0;
    work->base.actor.flags |= BTLOBJ_FLAG_IMMUNE_BIND;
    work->base.stockMoves = sHumLaxeneStockMoves[0];
    TaskPoolInit(&work->tasks, 12);
}

u8 task_hum_laxene_1(LaxeneWork* work) {
    LaxeneWork* w;
    BtlObj* act;
    s32 x;
    s32 y;
    s32 z;
    s16 d;
    s32 u;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &x, &y, &z);

    switch (HumUpdateReaction(&work->base)) {
    case 5:
        work->base.stateTimer = 0;
        work->base.steps = 0;

        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
            work->base.state = 21;
            break;
        case 37:
            work->base.state = 30;
            break;
        case 38:
        case 39:
            if (act->hp < (act->maxHp >> 1)) {
                work->base.state = 31;
            } else {
                work->base.state = 22;
            }

            break;
        case 0xF49D2735:
            work->base.state = 25;
            break;
        case 0xF35CFF3F:
            work->base.steps = GetRandom() % 4 + 4;
            work->base.state = 32;
            m4aSongNumStart(SONG_SND_284);
            break;
        }

        break;
    case 4:
        m4aSongNumStop(SONG_EF_RAC_BEEM);
        work->base.scaleX = 256;
        work->base.scaleY = 256;
        break;
    }

    if (gBtlWork->battleId == 163) {
        if (HumChooseCardAction(&work->base, 15, 80, 80, 50)) {
            work->base.stockMoves = sHumLaxeneStockMoves[0];
        }
    } else if (HumChooseCardAction(&work->base, 5, 80, 80, 50)) {
        if (GetRandom() % 2) {
            work->base.stockMoves = sHumLaxeneStockMoves[0];
        } else {
            work->base.stockMoves = sHumLaxeneStockMoves[1];
        }
    }

    switch (work->base.state) {
    case 12:
    case 18:
        AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        break;
    case 17:
        AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        break;
    case 0:
        AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        HumFaceTarget(&work->base, 5);

        if (func_08081828() == 0) {
            if (GetRandom() % 30 == 0) {
                work->base.state = 8;
                work->base.stateTimer = 0;
            } else {
                work->base.stateTimer++;
            }
        }

        break;
    case 8:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 1, 0, w->base.tiles);
            work->base.targetX = (gBtlWork->xMin + GetRandom() % (gBtlWork->xMax - gBtlWork->xMin + 1)) << 8;
            work->base.targetY = (gBtlWork->yMin + GetRandom() % (gBtlWork->yMax - gBtlWork->yMin + 1)) << 8;
            work->base.targetZ = -((GetRandom() % 71) << 8);

            if (act->btl->hcEffect == 50) {
                work->base.steps = 12;
            } else {
                work->base.steps = 25;
            }

            w->hoverZ = 0;
        } else if (AnimIsFinished(&work->base.anim)) {
            AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 2, ANIM_FLAG_LOOP, w->base.tiles);
        }

        ApproachValue(&act->x, work->base.targetX, work->base.steps);
        ApproachValue(&act->y, work->base.targetY, work->base.steps);
        ApproachValue(&act->z, work->base.targetZ, work->base.steps);
        work->base.steps--;

        if (work->base.steps <= 0) {
            work->base.state = 0;
            work->base.stateTimer = 0;
            w->hoverZ = act->z;
            break;
        }

        work->base.vz = 0;

        if (act->x < work->base.targetX) {
            act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
        } else {
            act->flags |= BTLOBJ_FLAG_FACING_LEFT;
        }

        work->base.stateTimer++;
        break;
    case 1:
    case 3:
    case 9:
    case 11:
    case 14:
        w->hoverZ = 0;
        AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
        break;
    case 25:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
            w->hoverZ = 0;
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 26;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 26:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 7, ANIM_FLAG_LOOP, w->base.tiles);

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                BgFxStartThunder(0, act->x + 0x400, act->y, act->z - 0x5000, act->x,
                    act->y, act->z - 0x5000, 0x135);
            } else {
                BgFxStartThunder(0, act->x - 0x400, act->y, act->z - 0x5000, act->x,
                    act->y, act->z - 0x5000, 0x135);
            }
        }

        if (BgFxIsActive()) {
            work->base.stateTimer++;
        } else {
            work->base.stateTimer = 0;
            work->base.state = 27;
        }

        break;
    case 27:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
        }

        HumFaceTarget(&work->base, 1);

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 28;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 28:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 10, ANIM_FLAG_LOOP, w->base.tiles);
            m4aSongNumStart(SONG_EF_RAC_BEEM);

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                BgFxStartLaxeneBeam(act->x - 0x1000, act->y, act->z - 0x3000, 1, 310);
            } else {
                BgFxStartLaxeneBeam(act->x + 0x1000, act->y, act->z - 0x3000, 0, 310);
            }
        }

        u = (y - act->y) >> 3;
        act->y += u;
        BgFxAddPosition(0, u, 0);

        if (BgFxIsActive()) {
            work->base.stateTimer++;
        } else {
            m4aSongNumStop(SONG_EF_RAC_BEEM);
            work->base.stateTimer = 0;
            work->base.state = 29;
        }

        break;
    case 29:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 11, 0, w->base.tiles);
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
            AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
            w->hoverZ = 0;
            m4aSongNumStart(SONG_SND_283);
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 23;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 23:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 7, ANIM_FLAG_LOOP, w->base.tiles);

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                BgFxStartThunder(1, act->x + 0x400, act->y, act->z - 0x5000, x, y, 0, 0x135);
            } else {
                BgFxStartThunder(1, act->x - 0x400, act->y, act->z - 0x5000, x, y, 0, 0x135);
            }
        }

        if (BgFxIsActive()) {
            work->base.stateTimer++;
        } else {
            work->base.stateTimer = 0;
            work->base.state = 24;
        }

        break;
    case 24:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 8, 0, w->base.tiles);
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 30:
        if (work->base.stateTimer == 0) {
            m4aSongNumStart(SONG_SND_285);
            AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
            FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
            w->hoverZ = 0;
            work->base.vz = 0x400;
        }

        MakeOpponentsHittable();

        switch (work->base.stateTimer) {
        case 28:
            CreateHumLaxeneKnfTask(w, -38, -11);
            break;
        case 32:
            CreateHumLaxeneKnfTask(w, -37, -25);
            break;
        case 36:
            CreateHumLaxeneKnfTask(w, -32, -38);
            break;
        case 44:
            CreateHumLaxeneKnfTask(w, -36, -18);
            break;
        case 48:
            CreateHumLaxeneKnfTask(w, -35, -32);
            break;
        case 52:
            CreateHumLaxeneKnfTask(w, -30, -45);
            break;
        }

        if (work->base.stateTimer > 120) {
            FadeToOriginal(FADE_MODE_BLACK, 8);
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 21:
        if (work->base.stateTimer == 0) {
            AnimReset(&work->base.anim);

            if (work->base.steps == 0) {
                AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            }

            w->hoverZ = 0;
            w->flags &= ~LAXENE_FLAG_ATTACK_HIT;
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                d = 13;
                break;
            case 3:
                d = -1;
                break;
            case 4:
                d = -4;
                break;
            case 5:
                d = -3;
                break;
            case 9:
                d = -2;
                break;
            case 10:
                d = -3;
                break;
            default:
                d = 0;
                break;
            }

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                act->x -= d << 8;
            } else {
                act->x += d << 8;
            }
        }

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            s32 v = act->x - 0x1000;
            act->x += (x - v) >> 4;
        } else {
            s32 v = act->x + 0x1000;
            act->x += (x - v) >> 4;
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                MakeOpponentsHittable();

                if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(0x131, act->x - 0x1800, act->y, act->z, 8, 24, 50)
                    : ApplyAttackBox(0x131, act->x + 0x1800, act->y, act->z, 8, 24, 50)) {
                    m4aSongNumStart(SONG_BTL_RAC_HIT);
                    w->flags |= LAXENE_FLAG_ATTACK_HIT;
                }

                break;
            case 8:
                MakeOpponentsHittable();

                if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(0x132, act->x - 0x1000, act->y, act->z, 16, 24, 50)
                    : ApplyAttackBox(0x132, act->x + 0x1000, act->y, act->z, 16, 24, 50)) {
                    m4aSongNumStart(SONG_BTL_RAC_HIT);
                    w->flags |= LAXENE_FLAG_ATTACK_HIT;
                }

                break;
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;

            if (work->base.steps <= 0 && (w->flags & LAXENE_FLAG_ATTACK_HIT)) {
                work->base.state = 21;
                work->base.steps++;
            } else {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
            }
        } else {
            work->base.stateTimer++;
        }

        break;
    case 31:
        if (work->base.stateTimer == 0) {
            AnimReset(&work->base.anim);

            if ((work->base.steps & 1) == 0) {
                AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 13, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 14, 0, w->base.tiles);
            }

            w->hoverZ = 0;
            w->flags &= ~LAXENE_FLAG_ATTACK_HIT;
            act->originX = act->x;
            work->base.vz = 0x400;
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                d = 13;
                break;
            case 3:
                d = -1;
                break;
            case 4:
                d = -4;
                break;
            case 5:
                d = -3;
                break;
            case 9:
                d = -2;
                break;
            case 10:
                d = -3;
                break;
            default:
                d = 0;
                break;
            }

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                act->x -= d << 8;
            } else {
                act->x += d << 8;
            }
        }

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            s32 v = act->x - 0x1000;
            act->x += (x - v) >> 3;
        } else {
            s32 v = act->x + 0x1000;
            act->x += (x - v) >> 3;
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                MakeOpponentsHittable();

                if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(0x131, act->x - 0x1800, act->y, act->z, 8, 24, 50)
                    : ApplyAttackBox(0x131, act->x + 0x1800, act->y, act->z, 8, 24, 50)) {
                    m4aSongNumStart(SONG_BTL_RAC_HIT);
                    w->flags |= LAXENE_FLAG_ATTACK_HIT;

                    if (work->base.steps == 4) {
                        MakeOpponentsHittable();
                        BgFxStartThunderStrike(x, y, 0, 0x137);
                    }
                }

                break;
            case 8:
                MakeOpponentsHittable();

                if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(0x132, act->x - 0x1000, act->y, act->z, 16, 24, 50)
                    : ApplyAttackBox(0x132, act->x + 0x1000, act->y, act->z, 16, 24, 50)) {
                    m4aSongNumStart(SONG_BTL_RAC_HIT);
                    w->flags |= LAXENE_FLAG_ATTACK_HIT;

                    if (work->base.steps == 4) {
                        MakeOpponentsHittable();
                        BgFxStartThunderStrike(x, y, z, 0x137);
                    }
                }

                break;
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;

            if (w->flags & LAXENE_FLAG_ATTACK_HIT) {
                if (work->base.steps > 3) {
                    ClearBtlObjActionFlags(act);
                    work->base.state = 0;
                } else {
                    work->base.state = 31;
                    work->base.steps++;
                }
            } else {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
            }
        } else {
            work->base.stateTimer++;
        }

        break;
    case 32:
        if (work->base.stateTimer == 0) {
            act->flags ^= BTLOBJ_FLAG_FACING_LEFT;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                s32 t = ((GetRandom() % 57) << 8) + 0x1800;
                act->x = x + t;
            } else {
                s32 t = ((GetRandom() % 57) << 8) + 0x1800;
                act->x = x - t;
            }

            {
                s32 t = ((GetRandom() % 27) << 8) - 0xD00;
                act->y = y + t;
            }

            act->z = 0;
            AnimReset(&work->base.anim);

            if ((GetRandom() & 1) == 0) {
                AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 13, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 14, 0, w->base.tiles);
            }

            w->hoverZ = 0;
            w->flags &= ~LAXENE_FLAG_ATTACK_HIT;
            w->scaleSteps = 8;
            work->base.scaleX = 5;
            work->base.scaleY = 384;
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                d = 13;
                break;
            case 3:
                d = -1;
                break;
            case 4:
                d = -4;
                break;
            case 5:
                d = -3;
                break;
            case 9:
                d = -2;
                break;
            case 10:
                d = -3;
                break;
            default:
                d = 0;
                break;
            }

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                act->x -= d << 8;
            } else {
                act->x += d << 8;
            }
        }

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            s32 v = act->x - 0x1000;
            act->x += (x - v) >> 3;
        } else {
            s32 v = act->x + 0x1000;
            act->x += (x - v) >> 3;
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                MakeOpponentsHittable();

                if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(0x131, act->x - 0x1800, act->y, act->z, 8, 24, 50)
                    : ApplyAttackBox(0x131, act->x + 0x1800, act->y, act->z, 8, 24, 50)) {
                    m4aSongNumStart(SONG_BTL_RAC_HIT);
                    w->flags |= LAXENE_FLAG_ATTACK_HIT;
                }

                break;
            case 8:
                MakeOpponentsHittable();

                if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(0x132, act->x - 0x1000, act->y, act->z, 16, 24, 50)
                    : ApplyAttackBox(0x132, act->x + 0x1000, act->y, act->z, 16, 24, 50)) {
                    m4aSongNumStart(SONG_BTL_RAC_HIT);
                    w->flags |= LAXENE_FLAG_ATTACK_HIT;
                }

                break;
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.steps--;

            if (work->base.steps > 0) {
                if (GetRandom() % 6 != 0) {
                    work->base.state = 32;
                } else {
                    work->base.state = 33;
                }
            } else {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
            }
        } else {
            work->base.stateTimer++;
        }

        break;
    case 33:
        if (work->base.stateTimer == 0) {
            m4aSongNumStart(SONG_SND_285);
            act->flags ^= BTLOBJ_FLAG_FACING_LEFT;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                s32 t = ((GetRandom() % 41) << 8) + 0x5000;
                act->x = x + t;
            } else {
                s32 t = ((GetRandom() % 41) << 8) + 0x5000;
                act->x = x - t;
            }

            {
                s32 t = ((GetRandom() % 49) << 8) - 0x1800;
                act->y = y + t;
            }

            act->z = 0;
            AnimReset(&work->base.anim);
            AnimChangeWithDef(sHumLaxeneAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
            FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
            w->hoverZ = 0;
            work->base.vz = 0x400;
            w->scaleSteps = 8;
            work->base.scaleX = 5;
            work->base.scaleY = 384;
        }

        MakeOpponentsHittable();

        switch (work->base.stateTimer) {
        case 28:
            CreateHumLaxeneKnfTask(w, -38, -11);
            break;
        case 32:
            CreateHumLaxeneKnfTask(w, -37, -25);
            break;
        case 36:
            CreateHumLaxeneKnfTask(w, -32, -38);
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            FadeToOriginal(FADE_MODE_BLACK, 8);
            work->base.stateTimer = 0;
            work->base.steps--;

            if (work->base.steps <= 0) {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
            } else if (GetRandom() & 10) {
                work->base.state = 32;
            } else {
                work->base.state = 33;
            }
        } else {
            work->base.stateTimer++;
        }

        break;
    }

    if (!(act->flags & BTLOBJ_FLAG_HURT) && act->badStatus != BAD_STATUS_STOP) {
        LaxeneHover(&work->base, w->hoverZ);
    }

    TaskPoolUpdate(&w->tasks);

    if ((s16)w->scaleSteps > 0) {
        ApproachValue(&work->base.scaleX, 256, w->scaleSteps);
        ApproachValue(&work->base.scaleY, 256, w->scaleSteps);
        w->scaleSteps--;
    }

    return HumUpdate(&work->base);
}

void task_hum_laxene_2(LaxeneWork* work) {
    HumDraw(&work->base);
    TaskPoolDraw(&work->tasks);
}

void task_hum_laxene_3(LaxeneWork* work) {
    m4aSongNumStop(SONG_EF_RAC_BEEM);
    HumReleaseResources(&work->base);
    TaskPoolDestroy(&work->tasks);
}

void task_hum_laxene_knf_0(LaxeneKnfWork* work, VixenNdlArgs* args) {
    work->palette = LoadObjPalette(gLaxinePalette, 0x20);
    work->tiles = LoadObjTiles(gLaxineKnifeTiles, 0x2C0);
    AnimInit(&work->anim, gLaxineKnifeAnims, gLaxineKnifeFrames);
    AnimStart(&work->anim, 0, 0);

    if (args->facingLeft != 0) {
        work->facingLeft = 1;
    } else {
        work->facingLeft = 0;
    }

    work->x = args->x;
    work->y = args->y;
    work->z = args->z;
    work->timer = 0;
    work->onScreen = 1;
    work->state = 0;
    work->playerPrevX = gBtlWork->actor->x;
    work->playerPrevY = gBtlWork->actor->y;
    work->playerPrevZ = gBtlWork->actor->z;
    work->vx = GetRandom() % 897 + 0x800;
    m4aSongNumStart(SONG_EF_RAC_3TR);
}

u8 task_hum_laxene_knf_1(LaxeneKnfWork* work) {
    BtlObj* c;

    if ((gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) == 0) {
        return 0;
    }

    if (!work->onScreen) {
        return 0;
    }

    switch (work->state) {
    case 0:
        if (ApplyAttackBox(0x133, work->x, work->y, work->z, 1, 6, 2)) {
            m4aSongNumStart(SONG_BTL_RAC_HIT);
            work->timer = 0;
            work->state = 1;
            BgFxStartThunderHit(work->x, work->y, work->z + 0x1000);
        } else {
            if (work->facingLeft) {
                work->x = work->x - work->vx;
            } else {
                work->x = work->x + work->vx;
            }

            work->timer++;
        }

        break;
    case 1:
        if ((s16)work->timer == 0) {
            AnimStart(&work->anim, 1, 0);
        }

        c = gBtlWork->actor;
        work->x += c->x - work->playerPrevX;
        work->y += c->y - work->playerPrevY;
        work->z += c->z - work->playerPrevZ;

        if ((s16)work->timer > 30) {
            return 0;
        }

        work->timer++;
        break;
    }

    AnimUpdate(&work->anim);
    work->playerPrevX = gBtlWork->actor->x;
    work->playerPrevY = gBtlWork->actor->y;
    work->playerPrevZ = gBtlWork->actor->z;
    return 1;
}

void task_hum_laxene_knf_2(LaxeneKnfWork* work) {
    s16 x;
    s16 y;
    void* gfx;
    u16 attr;

    gfx = AnimGetGfx(&work->anim);

    if (work->facingLeft) {
        attr = GetBattleSpritePriorityFlags(work->y);
    } else {
        attr = GetBattleSpritePriorityFlags(work->y) | 1;
    }

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gfx, work->tiles, work->palette, NULL, attr,
        -0x1004 - (work->y >> 8) * 4);

    if (IsRectOutsideScreen(x, y, 2, 2, 32, 32)) {
        work->onScreen = 0;
    }
}

void task_hum_laxene_knf_3(LaxeneKnfWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}
