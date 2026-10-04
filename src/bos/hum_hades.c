/**
 * hum_hades.c
 * Hades Boss
 */

#include "system_state.h"
#include "obj_api.h"
#include "hum.h"
#include "sprites_evt.h"
#include "sprites_hum.h"
#include "hum_common.h"
#include "songs.h"
#include "hum_tasks.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "display.h"
#include "engine_math.h"
#include "hum_types.h"
#include "m4a_song.h"
#include "obj.h"
#include "taskpool.h"
#include "types.h"
#include "sprite_palettes.h"

static const u32 sHumHadesStockMoves[3] = {
    36, 36, 36,
};

static const u32 sHumHadesAngryStockMoves[3] = {
    37, 36, 37,
};

static const AnimDef sHumHadesAnimDefs[10] = {
    { gHadesFloatFollowFrames, gHadesFloatFollowAnims, gHadesFloatFollowTiles, 0 },
    { gHadesFloatBackFrames, gHadesFloatBackAnims, gHadesFloatBackTiles, 0 },
    { gHadesDamageFrames, gHadesDamageAnims, gHadesDamageTiles, 0 },
    { gHadesFirashotFrames, gHadesFirashotAnims, gHadesFirashotTiles, 0 },
    { gHadesFigaballFrames, gHadesFigaballAnims, gHadesFigaballTiles, 0 },
    { gHadesNailofframeFrames, gHadesNailofframeAnims, gHadesNailofframeTiles, 0 },
    { gHadesAngryFrames, gHadesAngryAnims, gHadesAngryTiles, 0 },
    { gHadesFramespreadFrames, gHadesFramespreadAnims, gHadesFramespreadTiles, 1 },
    { gHadesFramespreadFrames, gHadesFramespreadAnims, gHadesFramespreadTiles, 2 },
    { gHadesFramespreadFrames, gHadesFramespreadAnims, gHadesFramespreadTiles, 3 },
};

static const AnimDef sHumHadesEffectAnimDefs[5] = {
    { gHadesAngryHiFrames, gHadesAngryHiAnims, gHadesAngryHiTiles, 0 },
    { gHadesNailFrameFrames, gHadesNailFrameAnims, gHadesNailFrameTiles, 0 },
    { gHadesFigaballBallFrames, gHadesFigaballBallAnims, gHadesFigaballBallTiles, 0 },
    { gHadesFigaballBallFrames, gHadesFigaballBallAnims, gHadesFigaballBallTiles, 1 },
    { gHadesFirashotFiraFrames, gHadesFirashotFiraAnims, gHadesFirashotFiraTiles, 0 },
};

static const HumSubDef sHumHadesSubDef = { gBStatesPalette, 75 };

static const HumDef sHumHadesDef = {
#ifdef VERSION_EU
        100
#else
        128
#endif
    , gHadesPalette, 0, { 44, 99, 90, 14, 52, 99, EMY_KIND_FLAG_LARGE_BODY } };

TaskDesc gTaskDescHumHades = {
    "task_hum_hades",
    (TaskInitFunc)task_hum_hades_0,
    (TaskUpdateFunc)task_hum_hades_1,
    (TaskDrawFunc)task_hum_hades_2,
    (TaskDestroyFunc)task_hum_hades_3,
    sizeof(HadesWork),
};

void HadesHover(HumWork* work, s32 a) {
    BtlObj* act = &work->actor;
    s32 t;

    if (a != 0) {
        t = a + gSineTable[gFrameCounter * 4 % 256] * 4;
        work->vz = 0;
        act->z += (t - act->z) >> 4;
    }
}

void HadesEndAttack(HadesWork* work) {
    BtlObj* act = &work->base.actor;

    if (work->angryAttacks > 2) {
        LoadObjPaletteBank(work->base.palette->index, gHadesPalette);
        work->base.paletteData = gHadesPalette;
        work->flags &= ~HADES_FLAG_ANGRY;
        work->base.stockMoves = sHumHadesStockMoves;
    } else {
        work->angryAttacks++;
    }

    ClearBtlObjActionFlags(act);
}

void task_hum_hades_0(HadesWork* work) {
    HumInit(&work->base, &sHumHadesDef);
    HumSubInit(&work->base, &work->sub, &sHumHadesSubDef);
    work->base.actor.flags |= BTLOBJ_FLAG_ABSORB_FIRE;
    work->base.flags |= HUM_FLAG_BOSS_DEATH;
    work->flags = 0;
    work->hoverZ = -0xA00;
    work->sub.flags |= (HUM_SUB_FLAG_IN_FRONT | HUM_SUB_FLAG_HIDDEN);
    work->tiles = AllocObjTiles(0x80, gHadesFramespreadHiTiles);
    work->tiles2 = AllocObjTiles(0x280, gHadesFramespreadHiTiles);
    work->tiles3 = AllocObjTiles(0x3A0, gHadesFramespreadHiTiles);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    AnimInit(&work->anim, gHadesFramespreadHiAnims, gHadesFramespreadHiFrames);
    AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);
    AnimInit(&work->anim2, gHadesFramespreadHiAnims, gHadesFramespreadHiFrames);
    AnimStart(&work->anim2, 1, ANIM_FLAG_LOOP);
    AnimInit(&work->anim3, gHadesFramespreadHiAnims, gHadesFramespreadHiFrames);
    AnimStart(&work->anim3, 0, ANIM_FLAG_LOOP);
    work->base.stockMoves = sHumHadesStockMoves;
}

u8 task_hum_hades_1(HadesWork* work) {
    HadesWork* w;
    BtlObj* act;
    s32 x;
    s32 y;
    s32 z;
    s16 p;
    s16 q;
    s16 r;
    s16 s;
    u16 frame;
    u8 t;
    u8 ret;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &x, &y, &z);

    switch (HumUpdateReaction(&work->base)) {
    case 5:
        work->base.stateTimer = 0;

        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
        case 38:
            if (w->flags & HADES_FLAG_ANGRY) {
                work->base.state = 21;
            } else {
                work->base.state = 20;
            }

            break;
        case 37:
        case 39:
            if (w->flags & HADES_FLAG_ANGRY) {
                work->base.state = 24;
            } else {
                work->base.state = 20;
            }

            break;
        case 0xEE5B96E5:
        case 0xEEFB96EF:
            if (w->flags & HADES_FLAG_ANGRY) {
                work->base.state = 22;
            } else {
                work->base.state = 19;
            }

            break;
        }

        break;
    case 4:
        work->sub.flags |= HUM_SUB_FLAG_HIDDEN;
        work->flags &= ~HADES_FLAG_FLAMES_ACTIVE;
        break;
    }

    if (w->flags & HADES_FLAG_ANGRY) {
        HumChooseCardAction(&work->base, 3, 40, 40, 24);
    } else {
        HumChooseCardAction(&work->base, 15, 40, 40, 24);
    }

    w->hoverZ = -0xA00;

    switch (work->base.state) {
    case 12:
    case 17:
    case 18:
        AnimChangeWithDef(sHumHadesAnimDefs, &w->base.anim, 1, ANIM_FLAG_LOOP, w->base.tiles);
        break;
    case 0:
    case 8:
        t = -((u8)work->base.stateTimer * 2);
        work->base.targetX = x + gSineTable[t] * 90;
        work->base.targetY = y + (-gSineTable[t + 64]) * 45;

        if (w->flags & HADES_FLAG_ANGRY) {
            HumMoveToward(&work->base, work->base.targetX, work->base.targetY, 0x333);
        } else {
            HumMoveToward(&work->base, work->base.targetX, work->base.targetY, 0x140);
        }

        HumFaceTarget(&work->base, 5);

        if (AnimIsFinished(&work->base.anim)) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                if (work->base.targetX < act->x) {
                    AnimChangeWithDef(sHumHadesAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
                } else {
                    AnimChangeWithDef(sHumHadesAnimDefs, &w->base.anim, 1, ANIM_FLAG_LOOP, w->base.tiles);
                }
            } else {
                if (work->base.targetX < act->x) {
                    AnimChangeWithDef(sHumHadesAnimDefs, &w->base.anim, 1, ANIM_FLAG_LOOP, w->base.tiles);
                } else {
                    AnimChangeWithDef(sHumHadesAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
                }
            }
        }

        work->base.stateTimer++;
        break;
    case 1:
    case 3:
    case 9:
    case 11:
    case 14:
        w->hoverZ = 0;
        AnimChangeWithDef(sHumHadesAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        break;
    case 19:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHadesAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
            AnimReset(&w->sub.anim);
            AnimChangeWithDef(sHumHadesEffectAnimDefs, &w->base.sub->anim, 0, 0, w->base.sub->tiles);
            w->sub.flags &= ~HUM_SUB_FLAG_HIDDEN;
        }

        w->sub.x = act->x;
        w->sub.y = act->y;
        w->sub.z = act->z;

        if (AnimGetFrame(&w->sub.anim) == 1 && w->sub.anim.timer == 0) {
            m4aSongNumStart(SONG_BTL_HA_IKARI);
        }

        if (AnimGetFrame(&work->base.anim) == 5 && work->base.anim.timer == 0) {
            LoadObjPaletteBank(work->base.palette->index, gHadesAngryPalette);
            work->base.paletteData = gHadesAngryPalette;
            w->flags |= HADES_FLAG_ANGRY;
            work->base.stockMoves = sHumHadesAngryStockMoves;
            w->angryAttacks = 0;
        }

        if (AnimIsFinished(&work->base.anim)) {
            w->sub.flags |= HUM_SUB_FLAG_HIDDEN;
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 22:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHadesAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            AnimReset(&w->sub.anim);
            AnimChangeWithDef(sHumHadesEffectAnimDefs, &w->base.sub->anim, 2, 0, w->base.sub->tiles);
            w->sub.flags &= ~HUM_SUB_FLAG_HIDDEN;
            m4aSongNumStart(SONG_VO_HA_ATTACK00);
            m4aSongNumStart(SONG_BTL_HA_FIREENTRY);
        }

        w->sub.x = act->x;
        w->sub.y = act->y;
        w->sub.z = act->z;

        if (AnimIsFinished(&w->sub.anim)) {
            work->base.state = 23;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 23:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHadesEffectAnimDefs, &w->base.sub->anim, 3, ANIM_FLAG_LOOP, w->base.sub->tiles);

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                w->sub.x -= 0xA00;
            } else {
                w->sub.x += 0xA00;
            }

            w->sub.z -= 0x4E00;
            w->subVz = 0;
            m4aSongNumStart(SONG_BTL_HA_BALLSHOT);
        }

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            w->sub.x -= 0x700;
        } else {
            w->sub.x += 0x700;
        }

        w->sub.y += (y - w->sub.y) >> 4;
        w->sub.z += w->subVz;
        w->subVz += 89;

        if (w->sub.z + 0xF00 > 0) {
            w->sub.z = -0xF00;
            w->subVz = -(w->subVz >> 1);
        }

        if (ApplyAttackBox(0x120, w->sub.x, w->sub.y, w->sub.z, 16, 16, 16)) {
            m4aSongNumStart(SONG_EF_TARU_BOMB);
        }

        if (w->sub.x < (gBtlWork->xMin - 32) << 8 || w->sub.x > (gBtlWork->xMax + 32) << 8) {
            w->sub.flags |= HUM_SUB_FLAG_HIDDEN;
            HadesEndAttack(w);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 24:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHadesAnimDefs, &w->base.anim, 7, 0, w->base.tiles);

#ifdef VERSION_EU
            if (act->btl->hcEffect == 8) {
                act->btl->hcEffectCount--;
            }
#endif
        }

        if (AnimGetFrame(&work->base.anim) == 4) {
            work->base.state = 25;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 25:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHadesAnimDefs, &w->base.anim, 8, ANIM_FLAG_LOOP, w->base.tiles);
            w->scale = 10;
            work->base.steps = 8;
            w->flags = (w->flags & ~HADES_FLAG_FLAMES_ENDING) | HADES_FLAG_FLAMES_ACTIVE;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                w->sub2[0].x = w->sub2[0].x2 = w->sub2[0].x3 = act->x - 0x2800;
                w->sub2[0].y = w->sub2[0].y2 = w->sub2[0].y3 = act->y;
                w->sub2[0].z = w->sub2[0].z2 = w->sub2[0].z3 = act->z - 0x3600;
                w->sub2[1].x = w->sub2[1].x2 = w->sub2[1].x3 = act->x + 0x600;
                w->sub2[1].y = w->sub2[1].y2 = w->sub2[1].y3 = act->y;
                w->sub2[1].z = w->sub2[1].z2 = w->sub2[1].z3 = act->z - 0x3400;
            } else {
                w->sub2[0].x = w->sub2[0].x2 = w->sub2[0].x3 = act->x + 0x2800;
                w->sub2[0].y = w->sub2[0].y2 = w->sub2[0].y3 = act->y;
                w->sub2[0].z = w->sub2[0].z2 = w->sub2[0].z3 = act->z - 0x3600;
                w->sub2[1].x = w->sub2[1].x2 = w->sub2[1].x3 = act->x - 0x600;
                w->sub2[1].y = w->sub2[1].y2 = w->sub2[1].y3 = act->y;
                w->sub2[1].z = w->sub2[1].z2 = w->sub2[1].z3 = act->z - 0x3400;
            }

            m4aSongNumStart(SONG_BTL_LEC_ROCKB1);
        }

        w->hoverZ = 0;

        if (work->base.steps > 0) {
            if (w->flags & HADES_FLAG_FLAMES_ENDING) {
                ApproachValue(&w->scale, 10, work->base.steps);
            } else {
                ApproachValue(&w->scale, 0x100, work->base.steps);
            }

            work->base.steps--;
        }

        if (work->base.stateTimer == 180) {
            w->flags |= HADES_FLAG_FLAMES_ENDING;
            work->base.steps = 8;
        }

        HumFaceTarget(&work->base, 8);
        act->y += (y - act->y) >> 4;
        act->x += gSineTable[(u8)work->base.stateTimer];
        w->sub2[0].groundY = act->y;
        w->sub2[1].groundY = act->y;

        if (w->flags & HADES_FLAG_FLAMES_ACTIVE) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                p = 44;
                q = -50;
                r = 2;
                s = -44;
                break;
            case 3:
                p = 44;
                q = -39;
                r = 33;
                s = -32;
                break;
            case 4:
                p = 46;
                q = -42;
                r = 21;
                s = -32;
                break;
            case 5:
                p = 46;
                q = -50;
                r = -3;
                s = -30;
                break;
            case 6:
                p = 48;
                q = -43;
                r = -2;
                s = -30;
                break;
            case 7:
                p = 45;
                q = -43;
                r = 2;
                s = -31;
                break;
            case 8:
                p = 42;
                q = -48;
                r = 19;
                s = -34;
                break;
            case 9:
            default:
                p = 33;
                q = -49;
                r = 20;
                s = -41;
                break;
            }

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                w->sub2[0].x += (act->x - (p << 8) - w->sub2[0].x) >> 1;
                w->sub2[1].x += (act->x - (r << 8) - w->sub2[1].x) >> 1;
            } else {
                w->sub2[0].x += (act->x + (p << 8) - w->sub2[0].x) >> 1;
                w->sub2[1].x += (act->x + (r << 8) - w->sub2[1].x) >> 1;
            }

            w->sub2[0].y += (act->y - w->sub2[0].y) >> 1;
            w->sub2[1].y += (act->y - w->sub2[1].y) >> 1;
            w->sub2[0].z += (act->z + (q << 8) - w->sub2[0].z) >> 1;
            w->sub2[1].z += (act->z + (s << 8) - w->sub2[1].z) >> 1;

            {
                s32 v = w->scale;
                p = p + (v * 14 >> 8);
                q = q + (v * 10 >> 8);
                r = r + (v * 8 >> 8);
                s = s + (v * 12 >> 8);
            }

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                w->sub2[0].x2 += (act->x - (p << 8) - w->sub2[0].x2) >> 3;
                w->sub2[1].x2 += (act->x - (r << 8) - w->sub2[1].x2) >> 3;
            } else {
                w->sub2[0].x2 += (act->x + (p << 8) - w->sub2[0].x2) >> 3;
                w->sub2[1].x2 += (act->x + (r << 8) - w->sub2[1].x2) >> 3;
            }

            w->sub2[0].y2 += (act->y - w->sub2[0].y2) >> 3;
            w->sub2[1].y2 += (act->y - w->sub2[1].y2) >> 3;
            w->sub2[0].z2 += (act->z + (q << 8) - w->sub2[0].z2) >> 3;
            w->sub2[1].z2 += (act->z + (s << 8) - w->sub2[1].z2) >> 3;

            {
                s32 v = w->scale;
                p = p + (v * 24 >> 8);
                q = q + (v * 20 >> 8);
                r = r + (v * 10 >> 8);
                s = s + (v * 20 >> 8);
            }

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                w->sub2[0].x3 += (act->x - (p << 8) - w->sub2[0].x3) >> 4;
                w->sub2[1].x3 += (act->x - (r << 8) - w->sub2[1].x3) >> 4;
            } else {
                w->sub2[0].x3 += (act->x + (p << 8) - w->sub2[0].x3) >> 4;
                w->sub2[1].x3 += (act->x + (r << 8) - w->sub2[1].x3) >> 4;
            }

            w->sub2[0].y3 += (act->y - w->sub2[0].y3) >> 4;
            w->sub2[1].y3 += (act->y - w->sub2[1].y3) >> 4;
            w->sub2[0].z3 += (act->z + (q << 8) - w->sub2[0].z3) >> 4;
            w->sub2[1].z3 += (act->z + (s << 8) - w->sub2[1].z3) >> 4;
        }

#ifndef VERSION_EU
        if (act->btl->hcEffect == 8 && act->hp < act->maxHp >> 1) {
            gBtlWork->damageScale = 0x200;
        }
#endif

        if (w->scale == 0x100) {
            if (ApplyAttackBox(0x121, w->sub2[0].x3, w->sub2[0].groundY, w->sub2[0].z3, 16, 16, 16)) {
                m4aSongNumStart(SONG_EF_FIRE01);
            }

            if (ApplyAttackBox(0x121, w->sub2[1].x3, w->sub2[1].groundY, w->sub2[1].z3, 16, 16, 16)) {
                m4aSongNumStart(SONG_EF_FIRE01);
            }
        }

#ifndef VERSION_EU
        gBtlWork->damageScale = 0;
#endif

        if ((w->flags & HADES_FLAG_FLAMES_ENDING) && work->base.steps <= 0) {
            w->flags &= ~HADES_FLAG_FLAMES_ACTIVE;
            work->base.state = 26;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 26:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHadesAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
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
            AnimChangeWithDef(sHumHadesAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            AnimReset(&w->sub.anim);
            AnimChangeWithDef(sHumHadesEffectAnimDefs, &w->base.sub->anim, 1, 0, w->base.sub->tiles);
            w->sub.flags &= ~HUM_SUB_FLAG_HIDDEN;

#ifdef VERSION_EU
            if (act->btl->hcEffect == 8) {
                act->btl->hcEffectCount--;
            }
#endif
        }

        w->sub.x = act->x;
        w->sub.y = act->y;
        w->sub.z = act->z;

        frame = AnimGetFrame(&w->sub.anim);

        switch (frame) {
        case 2:
        case 3:
        case 4:
#ifndef VERSION_EU
            if (act->btl->hcEffect == 8 && act->hp < act->maxHp >> 1) {
                gBtlWork->damageScale = 0x200;
            }
#endif

            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                ? ApplyAttackBox(0x11F, act->x - 0x1E00, act->y, act->z, 30, 16, 60)
                : ApplyAttackBox(0x11F, act->x + 0x1E00, act->y, act->z, 30, 16, 60)) {
                m4aSongNumStart(SONG_EF_FIRE01);
            }

#ifndef VERSION_EU
            gBtlWork->damageScale = 0;
#endif
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            w->sub.flags |= HUM_SUB_FLAG_HIDDEN;
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 20:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumHadesAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
            AnimReset(&w->sub.anim);
            AnimChangeWithDef(sHumHadesEffectAnimDefs, &w->base.sub->anim, 4, 0, w->base.sub->tiles);
            w->sub.flags &= ~HUM_SUB_FLAG_HIDDEN;
            w->sub.x = act->x;
            w->sub.y = act->y;
            w->sub.z = act->z;
            m4aSongNumStart(SONG_VO_HA_ATTACK01);

#ifdef VERSION_EU
            if (act->btl->hcEffect == 8) {
                act->btl->hcEffectCount--;
            }
#endif
        }

        switch (AnimGetFrame(&w->sub.anim)) {
        case 1:
            if (w->sub.anim.timer == 0) {
                m4aSongNumStart(SONG_EF_HA_FINGFIRE);
            }

            break;
        case 2:
#ifndef VERSION_EU
            if (act->btl->hcEffect == 8 && act->hp < act->maxHp >> 1) {
                gBtlWork->damageScale = 0x200;
            }
#endif

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                ApplyAttackBox(0x11E, act->x - 0x2000, act->y, act->z, 24, 16, 60);
            } else {
                ApplyAttackBox(0x11E, act->x + 0x2000, act->y, act->z, 24, 16, 60);
            }

#ifndef VERSION_EU
            gBtlWork->damageScale = 0;
#endif
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            w->sub.flags |= HUM_SUB_FLAG_HIDDEN;
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    }

    if (!(act->flags & BTLOBJ_FLAG_HURT) && act->badStatus != BAD_STATUS_STOP) {
        HadesHover(&work->base, w->hoverZ);
    }

    if (w->flags & HADES_FLAG_FLAMES_ACTIVE) {
        AnimUpdate(&w->anim);
        AnimUpdate(&w->anim2);
        AnimUpdate(&w->anim3);
    }

    ret = HumUpdate(&work->base);
    return ret;
}

void task_hum_hades_2(HadesWork* work) {
    BtlObj* act;
    HadesSub* e;
    void* gfx;
    u16 attr;
    s32 sx;
    ObjAffine* affine;
    s16 x;
    s16 y;
    s32 i;

    HumDraw(&work->base);

    if ((work->flags & HADES_FLAG_FLAMES_ACTIVE) == 0) {
        return;
    }

    act = &work->base.actor;

    for (i = 0; i < 2; i++) {
        e = &work->sub2[i];
        attr = GetBattleSpritePriorityFlags(e->groundY);

        if (work->scale == 0x100) {
            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT) == 0) {
                attr |= 1;
            }

            sx = work->scale;
        } else {
            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT) == 0) {
                sx = work->scale;
            } else {
                sx = -work->scale;
            }
        }

        affine = AllocObjAffine(0, sx, work->scale, 0);
        gfx = AnimGetGfx(&work->anim);
        WorldToScreen(&x, &y, e->x, e->y, e->z);
        DrawSprite(x, y, gfx, work->tiles, work->palette, affine, attr,
            -0x1005 - (e->groundY >> 8) * 4);
        gfx = AnimGetGfx(&work->anim2);
        WorldToScreen(&x, &y, e->x2, e->y2, e->z2);
        DrawSprite(x, y, gfx, work->tiles2, work->palette, affine, attr,
            -0x1006 - (e->groundY >> 8) * 4);
        gfx = AnimGetGfx(&work->anim3);
        WorldToScreen(&x, &y, e->x3, e->y3, e->z3);
        DrawSprite(x, y, gfx, work->tiles3, work->palette, affine, attr,
            -0x1007 - (e->groundY >> 8) * 4);
    }
}

void task_hum_hades_3(HadesWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles3);
    ReleaseObjPalette(work->palette);
    HumReleaseResources(&work->base);
}
