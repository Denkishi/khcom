/**
 * hum_riku.c
 * Riku Replica Boss
 */

#include "fade.h"
#include "obj_api.h"
#include "hum.h"
#include "sprites_hum.h"
#include "gba/io_reg.h"
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
#include "mode_chkobj_assets.h"
#include "obj.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

static const u32 sHumRikuStockMoves[2][3] = {
    { 36, 36, 38 },
    { 37, 37, 39 },
};

static const AnimDef sHumRikuAnimDefs[21] = {
    { gNiserikuIdolFrames, gNiserikuIdolAnims, gNiserikuIdolTiles, 0, { 0, 0, 0 } },
    { gNiserikuRunFrames, gNiserikuRunAnims, gNiserikuRunTiles, 0, { 0, 0, 0 } },
    { gNiserikuDamageFrames, gNiserikuDamageAnims, gNiserikuDamageTiles, 0, { 0, 0, 0 } },
    { gNiserikuJumpFrames, gNiserikuJumpAnims, gNiserikuJumpTiles, 0, { 0, 0, 0 } },
    { gNiserikuJumpFrames, gNiserikuJumpAnims, gNiserikuJumpTiles, 1, { 0, 0, 0 } },
    { gNiserikuJumpFrames, gNiserikuJumpAnims, gNiserikuJumpTiles, 2, { 0, 0, 0 } },
    { gNiserikuJumpFrames, gNiserikuJumpAnims, gNiserikuJumpTiles, 3, { 0, 0, 0 } },
    { gNiserikuJumpFrames, gNiserikuJumpAnims, gNiserikuJumpTiles, 4, { 0, 0, 0 } },
    { gNiserikuDashFrames, gNiserikuDashAnims, gNiserikuDashTiles, 0, { 0, 0, 0 } },
    { gNiserikuFuriharaiFrames, gNiserikuFuriharaiAnims, gNiserikuFuriharaiTiles, 0, { 0, 0, 0 } },
    { gNiserikuTategiriFrames, gNiserikuTategiriAnims, gNiserikuTategiriTiles, 0, { 0, 0, 0 } },
    { gNiserikuKabutoFrames, gNiserikuKabutoAnims, gNiserikuKabutoTiles, 0, { 0, 0, 0 } },
    { gNiserikuKabutoFrames, gNiserikuKabutoAnims, gNiserikuKabutoTiles, 2, { 0, 0, 0 } },
    { gNiserikuDarkfigaFrames, gNiserikuDarkfigaAnims, gNiserikuDarkfigaTiles, 0, { 0, 0, 0 } },
    { gNiserikuYamiStartFrames, gNiserikuYamiStartAnims, gNiserikuYamiStartTiles, 0, { 0, 0, 0 } },
    { gNiserikuYamiStartFrames, gNiserikuYamiStartAnims, gNiserikuYamiStartTiles, 1, { 0, 0, 0 } },
    { gNiserikuYamiStartFrames, gNiserikuYamiStartAnims, gNiserikuYamiStartTiles, 2, { 0, 0, 0 } },
    { gNiserikuYamiIngFrames, gNiserikuYamiIngAnims, gNiserikuYamiIngTiles, 0, { 0, 0, 0 } },
    { gNiserikuYamiIngFrames, gNiserikuYamiIngAnims, gNiserikuYamiIngTiles, 1, { 0, 0, 0 } },
    { gNiserikuYamiIngFrames, gNiserikuYamiIngAnims, gNiserikuYamiIngTiles, 2, { 0, 0, 0 } },
    { gNiserikuYamiEndFrames, gNiserikuYamiEndAnims, gNiserikuYamiEndTiles, 0, { 0, 0, 0 } },
};

static const HumDef sHumRikuDef = { 64, 0, gNiserikuPalette, 0, { 45, 99, 38, 14, 24, 99, 0 } };

static const HumSubDef sHumRikuSubDef = { gNiserikuPalette, 64, 0 };

TaskDesc gTaskDescHumRiku = {
    "task_hum_riku",
    (TaskInitFunc)task_hum_riku_0,
    (TaskUpdateFunc)task_hum_riku_1,
    (TaskDrawFunc)task_hum_riku_2,
    (TaskDestroyFunc)task_hum_riku_3,
    sizeof(RikuWork),
};

void RikuJumpOffset(RikuWork* work, s16 a, s32 b) {
    HumWork* w = &work->base;
    BtlObj* act = &w->actor;

    if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
        work->base.targetX = act->x - (a << 8);
    } else {
        work->base.targetX = act->x + (a << 8);
    }

    w->targetY = act->y;
    w->state = 19;
    w->stateTimer = 0;
    work->unk_1C4 = -b;
    work->unk_1C8 = 0;
}

void RikuJumpTo(RikuWork* work, s32 a, s32 b) {
    work->base.targetX = a;
    work->base.targetY = b;
    work->base.state = 19;
    work->base.stateTimer = 0;
    work->unk_1C4 = -0x500;
}

u8 RikuTryJumpAway(RikuWork* work) {
    s32 v;
    s32 w;
    BtlObj* c;

    c = gBtlWork->actor;

    if (GetRandom() % 30 == 0) {
        GetEnemyTargetPosition(&work->base.actor, &v, &w, NULL);
        HumFaceTarget(&work->base, 1);

        if (HumIsInPlayerReach(&work->base, 0x100, 0x100, 0x100)) {
            if (gBtlWork->flags & BTL_FLAG_PLAYER_AIRBORNE) {
                RikuJumpOffset(work, -99, 0x280);
            } else if (GetRandom() & 1) {
                if (c->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    RikuJumpTo(work, v + 0x2800, w);
                } else {
                    RikuJumpTo(work, v - 0x2800, w);
                }
            } else {
                RikuJumpOffset(work, -80, 0x500);
            }

            return 1;
        }
    }

    return 0;
}

void RikuSaveAfterimage(RikuWork* work, RikuSpawn* dst) {
    BtlObj* act = &work->base.actor;

    dst->x = act->x;
    dst->y = act->y;
    dst->z = act->z;

    if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
        dst->flags |= RIKU_SPAWN_FLAG_FACING_LEFT;
    } else {
        dst->flags &= ~RIKU_SPAWN_FLAG_FACING_LEFT;
    }

    dst->anim = work->base.anim;
    dst->tileSrc = work->base.tiles->src;
    dst->scale = gBtlWork->scale;
}

void RikuDrawAfterimage(RikuWork* work, RikuSpawn* p) {
    BtlObj* act;
    HumSub* sub;
    void* gfx;
    u16 attr;
    s32 sx;
    s32 sy;
    ObjAffine* affine;
    s16 x;
    s16 y;
    u16 pri;

    sub = work->base.sub;
    gfx = AnimGetGfx(&p->anim);
    act = &work->base.actor;

    if (!BgFxIsActive()) {
        gBldCnt = (BLDCNT_TGT1_OBJ | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
        SetBlendAlpha(6, 12);
        attr = 0x804;
    } else {
        attr = GetBattleSpritePriorityFlags(act->y);
    }

    if (p->flags & RIKU_SPAWN_FLAG_FACING_LEFT) {
        sy = p->scale;
        sx = sy;
    } else if (p->scale == 0x100) {
        sy = p->scale;
        sx = sy;
        attr |= 1;
    } else {
        sx = -gBtlWork->scale;
        sy = gBtlWork->scale;
    }

    if (sy == 0x100 && sx == sy) {
        affine = NULL;
    } else if (sy <= 255) {
        affine = AllocObjAffine(0, sx, sy, 0);
    } else {
        affine = AllocObjAffine(0, sx, sy, 1);
    }

    pri = 0xFFF0;
    WorldToScreen(&x, &y, p->x, p->y, p->z);
    SetObjTileSource(sub->tiles, p->tileSrc);
    DrawSprite(x, y, gfx, sub->tiles, work->base.palette, affine, attr, pri);
}

void task_hum_riku_0(RikuWork* work) {
    HumInit(&work->base, &sHumRikuDef);
    HumSubInit(&work->base, &work->sub, &sHumRikuSubDef);
    work->unk_1C4 = 0;
    work->flags = 0;
    work->sub.flags |= (HUM_SUB_FLAG_IN_FRONT | HUM_SUB_FLAG_HIDDEN);
    work->unk_1CC = 0;

    if (gBtlWork->battleId != 0xA1) {
        work->base.stockMoves = sHumRikuStockMoves[0];
    }

    RikuSaveAfterimage(work, &work->spawns[0]);
    work->spawns[1] = work->spawns[0];
    work->spawns[2] = work->spawns[0];
    work->spawns[3] = work->spawns[0];
    work->spawns[4] = work->spawns[0];
    work->spawns[5] = work->spawns[0];
    work->spawns[6] = work->spawns[0];
    work->spawns[7] = work->spawns[0];
    work->spawns[8] = work->spawns[0];
}

u8 task_hum_riku_1(RikuWork* work) {
    RikuWork* w;
    BtlObj* act;
    s32 x;
    s32 y;
    s32 z;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &x, &y, &z);
    work->flags &= ~RIKU_FLAG_AFTERIMAGE;

    switch (HumUpdateReaction(&work->base)) {
    case 5:
        work->base.stateTimer = 0;

        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
            work->base.state = 24;
            break;
        case 37:
            work->base.state = 22;
            break;
        case 38:
            work->base.state = 23;
            break;
        case 39:
            work->base.state = 25;
            break;
        case 0xF0DBE6F9:
            work->base.state = 29;
            break;
        case 0xF17C0F03:
            work->base.state = 30;
            break;
        }

        break;
    case 4:
        work->base.flags &= ~HUM_FLAG_IGNORE_BOUNDS;
        work->base.scaleX = 256;
        break;
    }

    switch (gBtlWork->battleId) {
    case 161:
        HumChooseCardAction(&work->base, 20, 40, 40, 20);
        break;
    case 168:
    case 171:
        if (HumChooseCardAction(&work->base, 15, 40, 40, 20)) {
            work->base.stockMoves = sHumRikuStockMoves[0];
        }

        break;
    case 169:
        if (HumChooseCardAction(&work->base, 10, 40, 40, 20)) {
            work->base.stockMoves = sHumRikuStockMoves[0];
        }

        break;
    case 170:
    case 172:
        if (HumChooseCardAction(&work->base, 3, 40, 40, 20)) {
            if (GetRandom() % 2) {
                work->base.stockMoves = sHumRikuStockMoves[0];
            } else {
                work->base.stockMoves = sHumRikuStockMoves[1];
            }
        }

        break;
    }

    switch (work->base.state) {
    case 12:
    case 18:
        AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        break;
    case 17:
        AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START, w->base.tiles);

        if ((gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) && RikuTryJumpAway(w)) {
            break;
        }

        if ((act->x - x >= 0 ? act->x - x : x - act->x) <= 0x4FFF) {
            if (x < 0x10000) {
                RikuJumpTo(w, (gBtlWork->xMax - 40) << 8, (gBtlWork->yMin + gBtlWork->yMax) << 7);
            } else {
                RikuJumpTo(w, (gBtlWork->xMin + 40) << 8, (gBtlWork->yMin + gBtlWork->yMax) << 7);
            }
        }

        break;
    case 0:
        AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);

        if (func_08081828()) {
            break;
        }

        if (AnimIsFinished(&work->base.anim) && (u16)(GetRandom() % 60) == 0) {
            work->base.state = 8;
            work->base.stateTimer = 0;
            break;
        }

        if (HumIsNearAreaEdge(&work->base, 40)) {
            RikuJumpTo(w, 0x10000, (gBtlWork->yMin + gBtlWork->yMax) << 7);
            break;
        }

        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            if (RikuTryJumpAway(w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 60);
        }

        work->base.stateTimer++;
        break;
    case 8:
        AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 1, ANIM_FLAG_LOOP, w->base.tiles);
        work->base.targetX = x;
        work->base.targetY = y;

        if (HumMoveToward(&work->base, work->base.targetX, work->base.targetY, 512) && AnimIsFinished(&work->base.anim)) {
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }

        if ((u16)(GetRandom() % 500) == 0 && (act->x - x >= 0 ? act->x - x : x - act->x) > 70) {
            RikuJumpTo(w, x, y);
            break;
        }

        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            if (RikuTryJumpAway(w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 1);
        }

        work->base.stateTimer++;
        break;
    case 3:
    case 9:
    case 11:
    case 14:
        AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        break;
    case 1:
        AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 2, 0, w->base.tiles);

        if (work->base.stateTimer == 3) {
            switch ((s32)(u16)(GetRandom() % 3)) {
            case 0:
                m4aSongNumStart(SONG_VO_RK_DAMAGE00);
                break;
            case 1:
                m4aSongNumStart(SONG_VO_RK_DAMAGE01);
                break;
            case 2:
            default:
                m4aSongNumStart(SONG_VO_RK_DAMAGE02);
                break;
            }
        }

        break;
    case 30:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 14, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_RK_ATTACK08);
            m4aSongNumStart(SONG_BTL_AN_STANDENTRY);
            FadeStartOut(FADE_MODE_DARK_MAGENTA, 80);
        }

        work->base.vz = 0;
        act->z += (-0x2800 - act->z) >> 5;

        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 31;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 31: {
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 15, 0, w->base.tiles);
        }

        switch (AnimGetFrame(&work->base.anim)) {
        case 1:
        case 2:
            work->base.vz -= 179;
            break;
        }

        w->flags |= RIKU_FLAG_AFTERIMAGE;

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            s32 t = act->x - 0x3000;
            act->x += (act->originX - t) >> 3;
        } else {
            s32 t = act->x + 0x3000;
            act->x += (act->originX - t) >> 3;
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 32;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    }
    case 32:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 16, 0, w->base.tiles);
            work->base.flags |= HUM_FLAG_IGNORE_BOUNDS;
        }

        work->base.vz = 0;
        w->flags |= RIKU_FLAG_AFTERIMAGE;

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            act->x -= 0xC00;
        } else {
            act->x += 0xC00;
        }

        if (act->x < ((gBtlWork->xMin - 48) << 8) ||
            act->x > ((gBtlWork->xMax + 48) << 8)) {
            work->base.state = 33;
            work->base.stateTimer = 0;
            w->dashCount = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 33:
        if (work->base.stateTimer == 0) {
            act->flags ^= BTLOBJ_FLAG_FACING_LEFT;

            switch ((u16)(GetRandom() % 3)) {
            case 0:
                AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 17, ANIM_FLAG_LOOP, w->base.tiles);

                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    w->unk_1C4 = (u16)(GetRandom() % 17) + 184;
                } else {
                    w->unk_1C4 = (u16)(GetRandom() % 17) + 56;
                }

                act->y = y + (((u16)(GetRandom() % 33) - 16) << 8);
                break;
            case 1:
                AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 18, ANIM_FLAG_LOOP, w->base.tiles);

                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    w->unk_1C4 = (u16)(GetRandom() % 17) + 203;
                } else {
                    w->unk_1C4 = (u16)(GetRandom() % 17) + 37;
                }

                act->y = y + (((u16)(GetRandom() % 17) + 16) << 8);
                break;
            case 2:
                AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 19, ANIM_FLAG_LOOP, w->base.tiles);

                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    w->unk_1C4 = (u16)(GetRandom() % 17) + 165;
                } else {
                    w->unk_1C4 = (u16)(GetRandom() % 17) + 75;
                }

                act->y = y - (((u16)(GetRandom() % 17) + 16) << 8);
                break;
            }

            act->z = -0x1000;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                act->x = x + 0x6300;
                BgFxStartRikuLimit(act->x, act->y, act->z, 192);
            } else {
                act->x = x - 0x6300;
                BgFxStartRikuLimit(act->x, act->y, act->z, 64);
            }

            m4aSongNumStart(SONG_BTL_RK_LIMITENTRY);
            work->base.steps = 10;
            work->base.scaleX = 10;
        }

        work->base.vz = 0;
        BtlMapFollowPosition(gBtlWork->actor->x, gBtlWork->actor->y, gBtlWork->actor->z);
        ApproachValue(&work->base.scaleX, 256, work->base.steps);
        work->base.steps--;

        if (work->base.steps <= 0) {
            work->base.state = 34;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 34:
        if (work->base.stateTimer == 0) {
            m4aSongNumStart(SONG_EF_RK_LIMITMOV);
            MakeOpponentsHittable();
        }

        w->flags |= RIKU_FLAG_AFTERIMAGE;
        act->x += gSineTable[(u8)w->unk_1C4] * 12;
        act->y += -gSineTable[(u8)w->unk_1C4 + 64] * 12;

        if (ApplyAttackBox(295, act->x, act->y, act->z, 24, 16, 24)) {
            m4aSongNumStart(SONG_BTL_RK_HIT03);
        }

        work->base.vz = 0;
        BtlMapFollowPosition(gBtlWork->actor->x, gBtlWork->actor->y, gBtlWork->actor->z);

        if (work->base.stateTimer == 15 && (s16)w->dashCount > 4) {
            work->base.state = 35;
            work->base.stateTimer = 0;
        } else if (work->base.stateTimer > 30) {
            work->base.state = 33;
            work->base.stateTimer = 0;
            w->dashCount++;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 35:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 20, 0, w->base.tiles);
            work->base.steps = 40;
        }

        if (work->base.steps > 0) {
            ApproachValue(&act->x, act->originX, work->base.steps);
            ApproachValue(&act->y, act->originY, work->base.steps);
            ApproachValue(&act->z, act->originZ, work->base.steps);
            work->base.steps--;

            if (work->base.steps <= 0) {
                BgFxStartRikuLimitFinish(act->x, act->y - 0x2000, 0);
            }
        }

        if (!BgFxIsActive() && work->base.steps <= 0 && AnimIsFinished(&work->base.anim)) {
            work->base.flags &= ~HUM_FLAG_IGNORE_BOUNDS;
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            FadeStartIn(FADE_MODE_DARK_MAGENTA, 30);
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 24:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 10, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_RK_ATTACK02);
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 1:
                work->base.vz = -972;
                break;
            case 4:
                work->base.vz = 0x1000;

                if (act->flags & BTLOBJ_FLAG_FACING_LEFT ?
                    ApplyAttackBox(293, act->x - 0x2000, act->y, act->z, 28, 16, 16) :
                    ApplyAttackBox(293, act->x + 0x2000, act->y, act->z, 28, 16, 16)) {
                    m4aSongNumStart(SONG_BTL_RK_HIT00);
                }

                break;
            }
        }

        switch (AnimGetFrame(&work->base.anim)) {
        case 1:
        case 2:
        case 3: {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                s32 t = act->x + 0x3200;
                act->x += (act->originX - t) >> 3;
            } else {
                s32 t = act->x - 0x3200;
                act->x += (act->originX - t) >> 3;
            }

            break;
        }
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 29:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 13, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_RK_ATTACK08);
            w->flags &= ~RIKU_FLAG_FIRE_LAUNCHED;
            HumFaceTarget(&work->base, 1);
        }

        if (w->flags & RIKU_FLAG_FIRE_LAUNCHED) {
            BtlObj* p = gBtlWork->actor;

            if (p != NULL) {
                s32 follow = 0;

                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    if (p->x < act->x - 0x2000) {
                        follow = 1;
                    }
                } else {
                    if (p->x > act->x + 0x2000) {
                        follow = 1;
                    }
                }

                if (follow) {
                    BgFxSetTarget(p->x, p->y, p->z - (p->centerHeight << 8));
                }
            }
        }

        if (!(w->flags & RIKU_FLAG_FIRE_LAUNCHED) && work->base.anim.timer == 0) {
            s16 d = 0;
            s32 spawn = 0;

            switch (AnimGetFrame(&work->base.anim)) {
            case 0:
                d = -10;
                break;
            case 1:
                d = -24;
                break;
            case 4:
                d = 12;
                break;
            case 5:
                d = 15;
                break;
            case 6:
                d = 7;
                spawn = 1;
                break;
            }

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                act->x -= d << 8;
            } else {
                act->x += d << 8;
            }

            if (spawn) {
                w->flags |= RIKU_FLAG_FIRE_LAUNCHED;

                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    BgFxStartFire(3, act->x - 0x4A00, act->y, act->z - 0x1800,
                        act->originX - 0xC800, act->originY, act->z - 0x1800, 1, 296);
                } else {
                    BgFxStartFire(3, act->x + 0x4A00, act->y, act->z - 0x1800,
                        act->originX + 0xC800, act->originY, act->z - 0x1800, 0, 296);
                }
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        }

        if (AnimIsFinished(&work->base.anim) && !BgFxIsActive()) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 23:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
            m4aSongNumStart(GetRandom() % 2 + SONG_VO_RK_ATTACK04);
        }

        if (work->base.anim.timer == 0) {
            s32 d = 0;
            s32 hit = 0;

            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                d = 4;
                break;
            case 3:
                d = 16;
                hit = 1;
                break;
            case 4:
                d = 5;
                break;
            case 6:
                d = 1;
                break;
            case 7:
                d = 4;
                hit = 1;
                break;
            case 8:
                d = 6;
                break;
            case 9:
            case 10:
                d = 2;
                break;
            }

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                act->x -= d << 8;
            } else {
                act->x += d << 8;
            }

            if (hit) {
                MakeOpponentsHittable();

                if (act->flags & BTLOBJ_FLAG_FACING_LEFT ?
                    ApplyAttackBox(292, act->x - 0x1400, act->y, act->z, 30, 16, 16) :
                    ApplyAttackBox(292, act->x + 0x1400, act->y, act->z, 30, 16, 16)) {
                    m4aSongNumStart(SONG_BTL_RK_HIT01);
                }
            }
        }

        switch (AnimGetFrame(&work->base.anim)) {
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                act->x -= 256;
            } else {
                act->x += 256;
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
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 8, 0, w->base.tiles);
            m4aSongNumStart(GetRandom() % 2 + SONG_VO_RK_ATTACK04);
        }

        if (AnimGetGfxIndex(&work->base.anim) == 6) {
            w->flags |= RIKU_FLAG_AFTERIMAGE;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                s32 t = act->x + 0x5800;
                act->x += (act->originX - t) >> 2;
            } else {
                s32 t = act->x - 0x5800;
                act->x += (act->originX - t) >> 2;
            }
        }

        if (work->base.anim.timer == 0) {
            s16 d = 0;
            s32 hit = 0;
            s32 attack = 290;

            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 1:
                d = 15;
                break;
            case 2:
                d = 5;
                hit = 1;
                attack = 290;
                break;
            case 4:
                d = -5;
                break;
            case 5:
                d = 10;
                break;
            case 6:
                d = 20;
                hit = 1;
                attack = 291;
                break;
            case 7:
                d = -9;
                break;
            case 8:
                d = 6;
                break;
            case 9:
                d = 1;
                break;
            }

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                act->x -= d << 8;
            } else {
                act->x += d << 8;
            }

            if (hit) {
                MakeOpponentsHittable();

                if (act->flags & BTLOBJ_FLAG_FACING_LEFT ?
                    ApplyAttackBox(attack, act->x - 0x1400, act->y, act->z, 20, 8, 16) :
                    ApplyAttackBox(attack, act->x + 0x1400, act->y, act->z, 20, 8, 16)) {
                    m4aSongNumStart(SONG_BTL_RK_HIT01);

                    if (attack == 291) {
                        FadeStartIn(FADE_MODE_ADD_WHITE, 45);

                        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                            SetBattleZoom(6, 332, act->x - 0x2000, (act->y - 0x1800) + act->z);
                        } else {
                            SetBattleZoom(6, 332, act->x + 0x2000, (act->y - 0x1800) + act->z);
                        }
                    }
                }
            }
        }

        if (work->base.anim.timer == 2 && AnimGetGfxIndex(&work->base.anim) == 6) {
            SetBattleZoom(8, 256, gBtlWork->x2, gBtlWork->y2);
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 25:
        if (act->z < act->groundZ) {
            break;
        }

        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_RK_ATTACK02);
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 26;
            work->base.vz = -0x600;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 26:
        act->x += (x - act->x) >> 4;
        act->y += (y - act->y) >> 4;

        if (work->base.vz < 0) {
            if (work->base.vz > -0x200) {
                AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            }
        } else {
            work->base.stateTimer = 0;
            work->base.state = 27;
            break;
        }

        work->base.stateTimer++;
        break;
    case 27:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 11, 0, w->base.tiles);
            w->flags &= ~RIKU_FLAG_DIVE_HIT;
        }

        act->x += (x - act->x) >> 4;
        act->y += (y - act->y) >> 4;

        if (AnimGetFrame(&work->base.anim) > 1) {
            if (ApplyAttackBox(294, act->x, act->y, act->z, 10, 10, 4)) {
                m4aSongNumStart(SONG_BTL_RK_HIT02);
                w->flags |= RIKU_FLAG_DIVE_HIT;
            }
        }

        if ((w->flags & RIKU_FLAG_DIVE_HIT) || act->z >= act->groundZ) {
            work->base.stateTimer = 0;
            work->base.state = 28;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 28:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
            work->base.vz = -0x400;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                work->base.targetX = act->x + 0x3000;
            } else {
                work->base.targetX = act->x - 0x3000;
            }
        }

        act->x += (work->base.targetX - act->x) >> 3;

        if (AnimIsFinished(&work->base.anim) && act->z >= act->groundZ) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 19:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 20;
            work->base.vz = w->unk_1C4;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 20:
        act->x += (work->base.targetX - act->x) >> 4;
        act->y += (work->base.targetY - act->y) >> 4;

        if (work->base.vz < 0) {
            if (work->base.vz <= -0x200) {
                AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            }
        } else if (work->base.vz <= 0x1FF) {
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
        } else {
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
        }

        if (act->z >= 0) {
            work->base.stateTimer = 0;
            work->base.state = 21;
            break;
        }

        HumFaceTarget(&work->base, 1);
        work->base.stateTimer++;
        break;
    case 21:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumRikuAnimDefs, &w->base.anim, 7, 0, w->base.tiles);
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    }

    return HumUpdate(&work->base);
}

void task_hum_riku_2(RikuWork* work) {
    HumDraw(&work->base);

    if ((work->flags & RIKU_FLAG_AFTERIMAGE) && (work->sub.flags & HUM_SUB_FLAG_HIDDEN)) {
        switch (work->unk_1CC % 2) {
        case 0:
            RikuDrawAfterimage(work, &work->spawns[2]);
            break;
        case 1:
            RikuDrawAfterimage(work, &work->spawns[4]);
            break;
        }

        work->unk_1CC++;
    }

    work->spawns[4] = work->spawns[3];
    work->spawns[3] = work->spawns[2];
    work->spawns[2] = work->spawns[1];
    work->spawns[1] = work->spawns[0];
    RikuSaveAfterimage(work, &work->spawns[0]);
}

void task_hum_riku_3(HumWork* work) {
    HumReleaseResources(work);
}
