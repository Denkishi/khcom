#include "system_state.h"
#include "fade.h"
#include "obj_api.h"
#include "hum.h"
#include "sprites_hum.h"
#include "gba/io_reg.h"
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

static const u32 sHumMahluxiaStockMovesA[3] = {
    37, 36, 37,
};

static const u32 sHumMahluxiaStockMovesB[3] = {
    36, 37, 38,
};

static const AnimDef sHumMahluxiaAnimDefs[13] = {
    { gMaruxhaIdleFrames, gMaruxhaIdleAnims, gMaruxhaIdleTiles, 0, { 0, 0, 0 } },
    { gMaruxhaMoveFrames, gMaruxhaMoveAnims, gMaruxhaMoveTiles, 0, { 0, 0, 0 } },
    { gMaruxhaDamegeFrames, gMaruxhaDamegeAnims, gMaruxhaDamegeTiles, 0, { 0, 0, 0 } },
    { gMaruxhaAtk1Frames, gMaruxhaAtk1Anims, gMaruxhaAtk1Tiles, 0, { 0, 0, 0 } },
    { gMaruxhaAtk4Frames, gMaruxhaAtk4Anims, gMaruxhaAtk4Tiles, 0, { 0, 0, 0 } },
    { gMaruxhaAtk4Frames, gMaruxhaAtk4Anims, gMaruxhaAtk4Tiles, 1, { 0, 0, 0 } },
    { gMaruxhaAtk4Frames, gMaruxhaAtk4Anims, gMaruxhaAtk4Tiles, 2, { 0, 0, 0 } },
    { gMaruxhaAtk1Frames, gMaruxhaAtk1Anims, gMaruxhaAtk1Tiles, 1, { 0, 0, 0 } },
    { gMaruxhaAtk3Frames, gMaruxhaAtk3Anims, gMaruxhaAtk3Tiles, 0, { 0, 0, 0 } },
    { gMaruxhaAtk2Frames, gMaruxhaAtk2Anims, gMaruxhaAtk2Tiles, 0, { 0, 0, 0 } },
    { gMaruxhaAtk1Frames, gMaruxhaAtk1Anims, gMaruxhaAtk1Tiles, 2, { 0, 0, 0 } },
    { gMaruxhaAtk1Frames, gMaruxhaAtk1Anims, gMaruxhaAtk1Tiles, 3, { 0, 0, 0 } },
    { gMaruxhaAtk1Frames, gMaruxhaAtk1Anims, gMaruxhaAtk1Tiles, 4, { 0, 0, 0 } },
};

static const AnimDef sHumMahluxiaEffAnimDef = { gMaruxhaBtEff1Frames, gMaruxhaBtEff1Anims, gMaruxhaBtEff1Tiles, 0, { 0, 0, 0 } };

static const HumSubDef sHumMahluxiaSubDef = { gMaruxhaBtEffPalette, 90, 0 };

static const HumDef sHumMahluxiaDef = { 90, 0, gMaruxhaPalette, 0, { 51, 99, 60, 14, 40, 99, 0 } };

TaskDesc gTaskDescHumMahluxia = {
    "task_hum_mahluxia",
    (TaskInitFunc)task_hum_mahluxia_0,
    (TaskUpdateFunc)task_hum_mahluxia_1,
    (TaskDrawFunc)task_hum_mahluxia_2,
    (TaskDestroyFunc)task_hum_mahluxia_3,
    sizeof(MahluxiaWork),
};

void MahluxiaJumpOffset(MahluxiaWork* work, s16 a) {
    HumWork* w = &work->base;
    BtlObj* act = &w->actor;
    s32 v;

    GetEnemyTargetPosition(act, &v, NULL, NULL);

    if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
        w->targetX = act->x - (a << 8);
    } else {
        w->targetX = act->x + (a << 8);
    }

    w->state = 20;
    w->stateTimer = 0;
    work->hoverZ = -0x300;

    if (act->y < v) {
        w->targetY = (gBtlWork->yMin + 16) << 8;
    } else {
        w->targetY = (gBtlWork->yMax - 16) << 8;
    }
}

void MahluxiaSwingTo(MahluxiaWork* work, s32 a, u16 b) {
    work->base.targetX = a;
    work->swingAmplitude = b;
    work->base.state = 19;
    work->base.stateTimer = 0;
}

u8 MahluxiaTryJumpAway(MahluxiaWork* work) {
    s32 v;
    BtlObj* c;

    c = gBtlWork->actor;
    GetEnemyTargetPosition(&work->base.actor, &v, NULL, NULL);
    HumFaceTarget(&work->base, 1);

    if (HumIsInPlayerReach(&work->base, 0x100, 0x100, 0x100)) {
        if (gBtlWork->flags & BTL_FLAG_PLAYER_AIRBORNE) {
            MahluxiaJumpOffset(work, -128);
        } else if (GetRandom() & 1) {
            if (c->flags & BTLOBJ_FLAG_FACING_LEFT) {
                MahluxiaSwingTo(work, v + 0x2800, 48);
            } else {
                MahluxiaSwingTo(work, v - 0x2800, 48);
            }
        } else {
            MahluxiaJumpOffset(work, -128);
        }

        return 1;
    }

    return 0;
}

void MahluxiaSaveAfterimage(MahluxiaWork* work, RikuSpawn* dst) {
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

void MahluxiaDrawAfterimage(MahluxiaWork* work, RikuSpawn* p) {
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

    if (BgFxIsActive() == 0) {
        gBldCnt = (BLDCNT_TGT1_OBJ | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
        SetBlendAlpha(4, 14);
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

void MahluxiaHover(HumWork* work, s32 a) {
    BtlObj* act;
    s32 t;

    if (a != 0) {
        act = &work->actor;
        t = a + gSineTable[gFrameCounter * 4 % 256] * 3;
        work->vz = 0;
        act->z += (t - act->z) >> 4;
    }
}

void task_hum_mahluxia_0(MahluxiaWork* work) {
    HumInit(&work->base, &sHumMahluxiaDef);
    HumSubInit(&work->base, &work->sub, &sHumMahluxiaSubDef);
    work->flags = 0;
    work->hoverZ = -0x300;
    work->sub.flags |= (HUM_SUB_FLAG_IN_FRONT | HUM_SUB_FLAG_HIDDEN);
    work->unk_1D8 = 0;
    AnimChangeWithDef(sHumMahluxiaAnimDefs, &work->base.anim, 0, ANIM_FLAG_LOOP, work->base.tiles);
    MahluxiaSaveAfterimage(work, &work->spawns[0]);
    work->spawns[1] = work->spawns[0];
    work->spawns[2] = work->spawns[0];
    work->spawns[3] = work->spawns[0];
    work->spawns[4] = work->spawns[0];
    work->spawns[5] = work->spawns[0];
    work->spawns[6] = work->spawns[0];
    work->spawns[7] = work->spawns[0];
    work->spawns[8] = work->spawns[0];
    TaskPoolInit(&work->tasks, 22);
    work->base.stockMoves = sHumMahluxiaStockMovesB;
}

void MahluxiaSpawnFlower(MahluxiaWork* work) {
    BtlObj* act = &work->base.actor;
    VixenNdlArgs args;
    s32 range;

    if (gFrameCounter % 5 == 0) {
        args.x = act->x;
        args.y = act->y;
        args.z = act->z - (act->centerHeight << 8);
        range = 0x2000;
        args.x += ((GetRandom() % 65) << 8) - range;
        range = 0x1000;
        args.y += ((GetRandom() % 33) << 8) - range;
        args.z += ((GetRandom() % 41) << 8) - range;
        TaskCreate(&work->tasks, &gTaskDescHumMahluxiaFlw, &args);
    }
}

u8 task_hum_mahluxia_1(MahluxiaWork* work) {
    MahluxiaWork* w;
    BtlObj* act;
    s32 x;
    s32 y;
    s32 z;
    u16 n;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &x, &y, &z);
    work->flags &= ~MAHLUXIA_FLAG_AFTERIMAGE;

    switch (HumUpdateReaction(&work->base)) {
    case 5:
        work->base.stateTimer = 0;
        w->hoverZ = 0;

        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
            work->base.state = 21;
            break;
        case 37:
            work->base.state = 27;
            break;
        case 38:
        case 39:
            work->base.state = 28;
            break;
        case 0xF71D9F71:
            work->base.state = 26;
            break;
        case 0xF7BDC767:
            work->base.state = 22;
            break;
        }

        break;
    case 4:
        w->sub.flags |= HUM_SUB_FLAG_HIDDEN;
        break;
    }

    if (HumChooseCardAction(&work->base, 4, 40, 40, 24)) {
        if (GetRandom() % 2) {
            work->base.stockMoves = sHumMahluxiaStockMovesB;
        } else {
            work->base.stockMoves = sHumMahluxiaStockMovesA;
        }
    }

    switch (work->base.state) {
    case 12:
    case 18:
        AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        break;
    case 17:
        AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);

        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            if (MahluxiaTryJumpAway(w)) {
                break;
            }
        }

        if (act->x - x >= 0 ? act->x - x <= 0x4FFF : x - act->x <= 0x4FFF) {
            if (x <= 0xFFFF) {
                MahluxiaSwingTo(w, (gBtlWork->xMax - 60) << 8, 48);
            } else {
                MahluxiaSwingTo(w, (gBtlWork->xMin + 60) << 8, 48);
            }
        }

        break;
    case 0:
        AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        w->hoverZ = -0x300;

        if (func_08081828()) {
            break;
        }

        if (act->x - x >= 0 ? act->x - x > 0x2800 : x - act->x > 0x2800) {
            if (GetRandom() % 80 == 0) {
                work->base.state = 8;
                work->base.stateTimer = 0;
                break;
            }
        }

        if (HumIsNearAreaEdge(&work->base, 40)) {
            MahluxiaSwingTo(w, 0x10000, 48);
            break;
        }

        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            if (MahluxiaTryJumpAway(w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 8);
        }

        work->base.stateTimer++;
        break;
    case 8:
        AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 1, ANIM_FLAG_LOOP, w->base.tiles);
        work->base.targetX = x;
        work->base.targetY = y;

        if (HumMoveToward(&work->base, work->base.targetX, work->base.targetY, 358)) {
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }

        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            if (MahluxiaTryJumpAway(w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 30);
        }

        work->base.stateTimer++;
        break;
    case 1:
        MahluxiaSpawnFlower(w);
    case 3:
    case 9:
    case 11:
    case 14:
        AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        break;
    case 20:
        AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 1, 0, w->base.tiles);
        act->x += (work->base.targetX - act->x) >> 4;
        act->y += (work->base.targetY - act->y) >> 4;

        if ((work->base.flags & HUM_FLAG_AT_FIELD_EDGE)
                || (work->base.targetX - act->x >= 0
                    ? work->base.targetX - act->x <= 0x7FF
                    : act->x - work->base.targetX <= 0x7FF)) {
            work->base.stateTimer = 0;
            work->base.state = 0;
            break;
        }

        HumFaceTarget(&work->base, 1);
        MahluxiaSpawnFlower(w);
        w->flags |= MAHLUXIA_FLAG_AFTERIMAGE;
        work->base.stateTimer++;
        break;
    case 19:
        if (work->base.stateTimer == 0) {
            w->steps = 60;
            w->angle = 0;
            w->swingBaseY = act->y;

            if (((gBtlWork->yMin + gBtlWork->yMax) << 7) < act->y) {
                w->flags &= ~MAHLUXIA_FLAG_SWING_DOWN;
            } else {
                w->flags |= MAHLUXIA_FLAG_SWING_DOWN;
            }

            AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 1, ANIM_FLAG_LOOP, w->base.tiles);
        }

        if ((s16)w->steps != 0) {
            ApproachValueHalfSteps(&act->x, work->base.targetX, w->steps);
            ApproachValueHalfSteps(&w->angle, 128, w->steps);

            if (w->flags & MAHLUXIA_FLAG_SWING_DOWN) {
                act->y = w->swingBaseY + gSineTable[(u8)w->angle] * w->swingAmplitude;
            } else {
                act->y = w->swingBaseY - gSineTable[(u8)w->angle] * w->swingAmplitude;
            }

            w->steps--;
        }

        MahluxiaSpawnFlower(w);

        if ((s16)w->steps <= 0) {
            work->base.stateTimer = 0;
            work->base.state = 0;
            break;
        }

        HumFaceTarget(&work->base, 3);
        w->flags |= MAHLUXIA_FLAG_AFTERIMAGE;
        work->base.stateTimer++;
        break;
    case 22:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
        }

        w->flags |= MAHLUXIA_FLAG_AFTERIMAGE;

        if (!AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer++;
            break;
        }

        work->base.state = 23;
        work->base.stateTimer = 0;
        break;
    case 23:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 5, ANIM_FLAG_LOOP, w->base.tiles);
        }

        act->y += (y - act->y) >> 2;
        n = work->base.stateTimer;

        if ((s16)n > 60) {
            work->base.state = 24;
            work->base.stateTimer = 0;
            break;
        }

        work->base.stateTimer = n + 1;
        break;
    case 24:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
        }

        w->flags |= MAHLUXIA_FLAG_AFTERIMAGE;

        if (!AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer++;
            break;
        }

        work->base.state = 25;
        work->base.stateTimer = 0;
        break;
    case 25:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 7, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_MARL_ATTACK00);
        }

        w->flags |= MAHLUXIA_FLAG_AFTERIMAGE;

        switch (AnimGetFrame(&work->base.anim)) {
        case 1:
            if (work->base.anim.timer == 0) {
                HumFaceTarget(&work->base, 1);
                BgFxStartKama(act->x, act->y, act->z, x - act->x, 316);
            }

            break;
        case 2:
            if (work->base.anim.timer == 0) {
                if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(0x13B, act->x - 0x2800, act->y, act->z, 40, 12, 64)
                    : ApplyAttackBox(0x13B, act->x + 0x2800, act->y, act->z, 40, 12, 64)) {
                    m4aSongNumStart(SONG_EF_KU_ATT02);
                }
            }

            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            if (BgFxIsActive() == 0) {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
                work->base.stateTimer = 0;
                break;
            }
        }

        work->base.stateTimer++;
        break;
    case 28:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 10, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_MARL_ATTACK03);
        }

        w->flags |= MAHLUXIA_FLAG_AFTERIMAGE;

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            act->x = act->x - 0x105;
        } else {
            act->x = act->x + 0x105;
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 29;
            work->base.stateTimer = 0;
            break;
        }

        work->base.stateTimer++;
        break;
    case 29:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 11, 0, w->base.tiles);
            FadeStartIn(FADE_MODE_ADD_WHITE, 20);
            m4aSongNumStart(SONG_SND_706);
            FadeLock();
            gBtlWork->hitStop = 20;
            w->flags |= MAHLUXIA_FLAG_AFTERIMAGE;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                act->x -= 0x5000;
                ApplyAttackBox(0x13F, act->x + 0x2800, act->y, 0, 40, 16, 40);
            } else {
                act->x += 0x5000;
                ApplyAttackBox(0x13F, act->x - 0x2800, act->y, 0, 40, 16, 40);
            }
        }

        n = work->base.stateTimer;

        if ((s16)n > 60) {
            work->base.state = 30;
            work->base.stateTimer = 0;
            break;
        }

        work->base.stateTimer = n + 1;
        break;
    case 30:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
        }

        w->flags |= MAHLUXIA_FLAG_AFTERIMAGE;

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }

        work->base.stateTimer++;
        break;
    case 26:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 8, 0, w->base.tiles);
            w->flags &= ~MAHLUXIA_FLAG_EFFECT_LAUNCHED;
            m4aSongNumStart(SONG_VO_MARL_ATTACK01);
        }

        w->flags |= MAHLUXIA_FLAG_AFTERIMAGE;

        if (AnimGetFrame(&work->base.anim) == 4) {
            if (work->base.anim.timer == 0) {
                BgFxStartHanabira(act->x, act->y, act->z - 0x4D00, 318);
                w->flags |= MAHLUXIA_FLAG_EFFECT_LAUNCHED;
            }
        }

        if (w->flags & MAHLUXIA_FLAG_EFFECT_LAUNCHED) {
            MahluxiaSpawnFlower(w);
        }

        if (AnimIsFinished(&work->base.anim)) {
            if (BgFxIsActive() == 0) {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
                work->base.stateTimer = 0;
                break;
            }
        }

        work->base.stateTimer++;
        break;
    case 27:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_MARL_ATTACK03);
        }

        w->flags |= MAHLUXIA_FLAG_AFTERIMAGE;

        switch (AnimGetFrame(&work->base.anim)) {
        case 4:
            if (work->base.anim.timer == 0) {
                m4aSongNumStart(SONG_BTL_MARL_STAMP);

                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    BgFxStartMahluxiaGround(act->x + 0x1700, act->y, 0, 0x13D);
                } else {
                    BgFxStartMahluxiaGround(act->x - 0x1700, act->y, 0, 0x13D);
                }
            }

            break;
        case 5:
            if (work->base.anim.timer == 0) {
                m4aSongNumStart(SONG_EF_MARL_GROUND);
            }

            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            if (BgFxIsActive() == 0) {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
                work->base.stateTimer = 0;
                break;
            }
        }

        work->base.stateTimer++;
        break;
    case 21:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumMahluxiaAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
            w->flags &= ~MAHLUXIA_FLAG_EFFECT_LAUNCHED;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                w->sub.x = act->x - 0x4600;
            } else {
                w->sub.x = act->x + 0x4600;
            }

            w->sub.z = 0;
            w->subSpeed = 0;
            m4aSongNumStart(SONG_VO_MARL_ATTACK03);
        }

        switch (AnimGetFrame(&work->base.anim)) {
        case 0:
        case 1:
        case 2:
        case 3:
            w->flags |= MAHLUXIA_FLAG_AFTERIMAGE;
            act->y += (y - act->y) >> 2;
            w->sub.y = act->y;
            break;
        case 4:
            if (work->base.anim.timer == 0) {
                AnimReset(&w->sub.anim);
                AnimChangeWithDef(&sHumMahluxiaEffAnimDef, &w->base.sub->anim, 0, 0, w->base.sub->tiles);
                w->flags |= MAHLUXIA_FLAG_EFFECT_LAUNCHED;
                w->sub.flags &= ~HUM_SUB_FLAG_HIDDEN;
                m4aSongNumStart(SONG_EF_KU_ATT03);

                if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                    ? ApplyAttackBox(0x13B, act->x - 0x2800, act->y, act->z, 40, 12, 64)
                    : ApplyAttackBox(0x13B, act->x + 0x2800, act->y, act->z, 40, 12, 64)) {
                    m4aSongNumStart(SONG_EF_KU_ATT02);
                }
            }

            MahluxiaSpawnFlower(w);
            break;
        case 5:
        case 6:
            MahluxiaSpawnFlower(w);
            break;
        }

        if (w->flags & MAHLUXIA_FLAG_EFFECT_LAUNCHED) {
            w->subSpeed += 25;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                w->sub.x = w->sub.x - w->subSpeed;
            } else {
                w->sub.x = w->sub.x + w->subSpeed;
            }

            switch (AnimGetFrame(&w->sub.anim)) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                if (ApplyAttackBox(0x13B, w->sub.x, w->sub.y, w->sub.z, 8, 4, 64)) {
                    m4aSongNumStart(SONG_EF_MLC_SNICHIT);
                }

                break;
            default:
                if (ApplyAttackBox(0x13B, w->sub.x, w->sub.y, w->sub.z, 16, 4, 20)) {
                    m4aSongNumStart(SONG_EF_MLC_SNICHIT);
                }

                break;
            }

            if (w->sub.x < (gBtlWork->xMin - 32) << 8 ||
                w->sub.x > (gBtlWork->xMax + 32) << 8) {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
                work->base.stateTimer = 0;
                w->sub.flags |= HUM_SUB_FLAG_HIDDEN;
                break;
            }
        }

        work->base.stateTimer++;
        break;
    }

    if (!(act->flags & BTLOBJ_FLAG_HURT)) {
        if (act->badStatus != BAD_STATUS_STOP) {
            MahluxiaHover(&work->base, w->hoverZ);
        }
    }

    TaskPoolUpdate(&w->tasks);
    return HumUpdate(&work->base);
}

void task_hum_mahluxia_2(MahluxiaWork* work) {
    HumDraw(&work->base);

    if ((work->flags & MAHLUXIA_FLAG_AFTERIMAGE) && (work->sub.flags & HUM_SUB_FLAG_HIDDEN)) {
        switch (work->unk_1D8 % 12) {
        case 0:
        case 2:
        case 4:
        case 6:
        case 8:
        case 10:
            MahluxiaDrawAfterimage(work, &work->spawns[2]);
            break;
        case 1:
        case 3:
        case 7:
            MahluxiaDrawAfterimage(work, &work->spawns[4]);
            break;
        case 5:
        case 9:
            MahluxiaDrawAfterimage(work, &work->spawns[6]);
            break;
        case 11:
            MahluxiaDrawAfterimage(work, &work->spawns[8]);
            break;
        }

        work->unk_1D8++;
    }

    work->spawns[8] = work->spawns[7];
    work->spawns[7] = work->spawns[6];
    work->spawns[6] = work->spawns[5];
    work->spawns[5] = work->spawns[4];
    work->spawns[4] = work->spawns[3];
    work->spawns[3] = work->spawns[2];
    work->spawns[2] = work->spawns[1];
    work->spawns[1] = work->spawns[0];
    MahluxiaSaveAfterimage(work, &work->spawns[0]);
    TaskPoolDraw(&work->tasks);
}

void task_hum_mahluxia_3(MahluxiaWork* work) {
    HumReleaseResources(&work->base);
    TaskPoolDestroy(&work->tasks);
}
