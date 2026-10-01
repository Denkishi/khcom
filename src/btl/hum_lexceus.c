#include "system_state.h"
#include "obj_api.h"
#include "hum.h"
#include "sprites_btl.h"
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
#include "mode_chkobj_assets.h"
#include "obj.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

static const u32 sHumLexceusStockMoves[3] = {
    36, 37, 36,
};

static const AnimDef sHumLexceusAnimDefs[10] = {
    { gRexeusIdlFrames, gRexeusIdlAnims, gRexeusIdlTiles, 0, { 0, 0, 0 } },
    { gRexeusMovFrames, gRexeusMovAnims, gRexeusMovTiles, 0, { 0, 0, 0 } },
    { gRexeusDmgFrames, gRexeusDmgAnims, gRexeusDmgTiles, 0, { 0, 0, 0 } },
    { gRexeusCmb1Frames, gRexeusCmb1Anims, gRexeusCmb1Tiles, 0, { 0, 0, 0 } },
    { gRexeusCmb2Frames, gRexeusCmb2Anims, gRexeusCmb2Tiles, 1, { 0, 0, 0 } },
    { gRexeusTmhFrames, gRexeusTmhAnims, gRexeusTmhTiles, 0, { 0, 0, 0 } },
    { gRexeusTmhFrames, gRexeusTmhAnims, gRexeusTmhTiles, 1, { 0, 0, 0 } },
    { gRexeusRckFrames, gRexeusRckAnims, gRexeusRckTiles, 0, { 0, 0, 0 } },
    { gRexeusRckFrames, gRexeusRckAnims, gRexeusRckTiles, 1, { 0, 0, 0 } },
    { gRexeusImpFrames, gRexeusImpAnims, gRexeusImpTiles, 0, { 0, 0, 0 } },
};

static const HumDef sHumLexceusDef = { 128, 0, gRexeusPalette, 0, { 53, 99, 70, 24, 52, 99, EMY_KIND_FLAG_LARGE_BODY } };

TaskDesc gTaskDescHumLexceus = {
    "task_hum_lexceus",
    (TaskInitFunc)task_hum_lexceus_0,
    (TaskUpdateFunc)task_hum_lexceus_1,
    (TaskDrawFunc)task_hum_lexceus_2,
    (TaskDestroyFunc)task_hum_lexceus_3,
    sizeof(LexceusWork),
};

static TaskDesc sTaskDescHumLexTmh = {
    "task_hum_lex_tmh",
    (TaskInitFunc)task_hum_lex_tmh_0,
    (TaskUpdateFunc)task_hum_lex_tmh_1,
    (TaskDrawFunc)task_hum_lex_tmh_2,
    (TaskDestroyFunc)task_hum_lex_tmh_3,
    sizeof(LexTmhWork),
};

static TaskDesc sTaskDescHumLexTmh0 = {
    "task_hum_lex_tmh0",
    (TaskInitFunc)task_hum_lex_tmh0_0,
    (TaskUpdateFunc)task_hum_lex_tmh0_1,
    (TaskDrawFunc)task_hum_lex_tmh0_2,
    (TaskDestroyFunc)task_hum_lex_tmh0_3,
    sizeof(LexTmh0Work),
};

static TaskDesc sTaskDescHumLexRock = {
    "task_hum_lex_rock",
    (TaskInitFunc)task_hum_lex_rock_0,
    (TaskUpdateFunc)task_hum_lex_rock_1,
    (TaskDrawFunc)task_hum_lex_rock_2,
    (TaskDestroyFunc)task_hum_lex_rock_3,
    sizeof(LexRockWork),
};

void LexceusHover(HumWork* work, s32 a) {
    BtlObj* act;
    s32 t;

    if (a != 0) {
        act = &work->actor;
        t = a + gSineTable[gFrameCounter * 4 % 256] * 3;
        work->vz = 0;
        act->z += (t - act->z) >> 4;
    }
}

void task_hum_lexceus_0(LexceusWork* work) {
    HumInit(&work->base, &sHumLexceusDef);
    work->flags = 0;
    work->hoverZ = 0;
    work->scaleSteps = 0;
    work->tiltSteps = 0;
    work->tilt = 0;
    work->targetTilt = 0;
    work->tiltSlide = 0;
    work->base.stockMoves = sHumLexceusStockMoves;
    TaskPoolInit(&work->tasks, 3);
}

u8 task_hum_lexceus_1(LexceusWork* work) {
    LexceusWork* w;
    BtlObj* act;
    BtlObj* p;
    VixenNdlArgs a1;
    VixenNdlArgs a2;
    s32 x;
    s32 y;
    s32 z;
    s16 dx;
    s16 dy;

    w = work;
    act = &work->base.actor;
    p = gBtlWork->actor;
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
            work->base.state = 23;
            break;
        case 38:
        case 39:
            work->base.state = 27;
            break;
        case 0xF85E3F85:
            work->base.state = 25;
            break;
        }

        break;
    case 4:
        work->base.scaleX = work->targetScaleX = 0x100;
        work->base.scaleY = work->targetScaleY = 0x100;
        work->scaleSteps = 0;

        if (work->targetTilt != 0) {
            work->targetTilt = 0;
            work->tiltSteps = 420;
        }

        break;
    }

    HumChooseCardAction(&work->base, 3, 40, 40, 20);
    w->hoverZ = 0;

    switch (work->base.state) {
    case 12:
        AnimChangeWithDef(sHumLexceusAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        break;
    case 17:
    case 18:
        AnimChangeWithDef(sHumLexceusAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        break;
    case 0:
        AnimChangeWithDef(sHumLexceusAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);

        if (func_08081828()) {
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            if (GetRandom() % 80 == 0) {
                work->base.state = 8;
                work->base.stateTimer = 0;
                break;
            }
        }

        HumFaceTarget(&work->base, 10);
        work->base.stateTimer++;
        break;
    case 8:
        AnimChangeWithDef(sHumLexceusAnimDefs, &w->base.anim, 1, ANIM_FLAG_LOOP, w->base.tiles);
        w->hoverZ = -0x1000;
        work->base.targetX = x;
        work->base.targetY = y;

        if (AnimIsFinished(&work->base.anim)) {
            if (HumMoveToward(&work->base, work->base.targetX, work->base.targetY, 0x100)) {
                work->base.state = 0;
                work->base.stateTimer = 0;
                break;
            }
        }

        HumFaceTarget(&work->base, 10);
        work->base.stateTimer++;
        break;
    case 1:
        act->vx = act->vy = 0;
        work->base.vz = 0;

        if (work->base.stateTimer > 5) {
            break;
        }

        work->base.stateTimer = 6;
        act->invincibleTimer = 30;
        break;
    case 3:
    case 9:
    case 11:
    case 14:
        AnimChangeWithDef(sHumLexceusAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        break;
    case 25:
        if (work->base.stateTimer == 0) {
            m4aSongNumStart(SONG_SND_286);
            AnimChangeWithDef(sHumLexceusAnimDefs, &w->base.anim, 7, 0, w->base.tiles);
            gBtlWork->flags &= ~0x100000;
        }

        switch (AnimGetFrame(&work->base.anim)) {
        case 2:
            if (work->base.anim.timer == 0) {
                m4aSongNumStart(SONG_BTL_LEC_ROCKB2);
            }

            break;
        case 3:
            if (work->base.anim.timer == 0) {
                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    a1.x = act->x - 0x2000;
                    a1.facingLeft = 1;
                } else {
                    a1.x = act->x + 0x2000;
                    a1.facingLeft = 0;
                }

                a1.y = act->y;
                a1.z = 0;
                w->task = TaskCreate(&w->tasks, &sTaskDescHumLexRock, &a1);
            }

            break;
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
            AnimChangeWithDef(sHumLexceusAnimDefs, &w->base.anim, 8, 0, w->base.tiles);
            gBtlWork->flags |= 0x100000;
        }

        if (IsTaskActiveNamed(w->task, sTaskDescHumLexRock.name)) {
            break;
        }

        if (!AnimIsFinished(&work->base.anim)) {
            break;
        }

        work->base.stateTimer = 0;
        work->base.state = 0;
        ClearBtlObjActionFlags(act);
        break;
    case 23:
        if (work->base.stateTimer == 0) {
            w->hoverZ = 0;
            AnimChangeWithDef(sHumLexceusAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            w->flags &= ~LEXCEUS_FLAG_WEAPON_THROWN;
            w->task = NULL;
            m4aSongNumStart(SONG_SND_287);
        }

        if (AnimGetFrame(&work->base.anim) == 3) {
            if (work->base.anim.timer == 2) {
                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    a1.x = act->x - 0x1800;
                    a1.facingLeft = 1;
                } else {
                    a1.x = act->x + 0x1800;
                    a1.facingLeft = 0;
                }

                a1.y = act->y;
                a1.z = act->z - 0x6000;
                w->flags |= LEXCEUS_FLAG_WEAPON_THROWN;
                w->task = TaskCreate(&w->tasks, &sTaskDescHumLexTmh, &a1);
            }
        }

        if (w->flags & LEXCEUS_FLAG_WEAPON_THROWN) {
            if (IsTaskActiveNamed(w->task, sTaskDescHumLexTmh.name) == 0) {
                work->base.stateTimer = 0;
                work->base.state = 24;
                break;
            }
        }

        work->base.stateTimer++;
        break;
    case 24:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumLexceusAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
        }

        if (AnimGetFrame(&work->base.anim) == 2) {
            if (work->base.anim.timer == 10) {
                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    a2.x = act->x - 0x700;
                    a2.facingLeft = 1;
                } else {
                    a2.x = act->x + 0x700;
                    a2.facingLeft = 0;
                }

                a2.y = act->y;
                a2.z = act->z;
                TaskCreate(&w->tasks, &sTaskDescHumLexTmh0, &a2);
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }

        work->base.stateTimer++;
        break;
    case 21:
        if (work->base.stateTimer == 0) {
            w->hoverZ = 0;
            AnimReset(&work->base.anim);
            AnimChangeWithDef(sHumLexceusAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
            w->flags &= ~(LEXCEUS_FLAG_ATTACK_HIT | LEXCEUS_FLAG_COMBO_FOLLOWUP);

#ifdef VERSION_EU
            if (act->btl->hcEffect == 49) {
                act->btl->hcEffectCount--;
            }
#endif
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetFrame(&work->base.anim)) {
            case 3:
                dx = 9;
                dy = 0;
                break;
            case 4:
                dx = 13;
                dy = 0;
                break;
            case 5:
                dx = 6;
                dy = 6;
                break;
            case 7:
                dx = -21;
                dy = -6;
                break;
            default:
                dx = 0;
                dy = 0;
                break;
            }

            if (!AnimIsFinished(&work->base.anim)) {
                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    act->x = act->x - (dx << 8);
                } else {
                    act->x = act->x + (dx << 8);
                }

                act->y = act->y + (dy << 8);
            }

            if (work->base.anim.timer == 0) {
                if (AnimGetGfxIndex(&work->base.anim) == 5) {
                    MakeOpponentsHittable();

                    if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                        ? ApplyAttackBox(0x144, act->x - 0x3C00, act->y, act->z, 24, 20, 30)
                        : ApplyAttackBox(0x144, act->x + 0x3C00, act->y, act->z, 24, 20, 30)) {
                        m4aSongNumStart(SONG_BTL_LEC_HIT);
                        w->flags |= LEXCEUS_FLAG_ATTACK_HIT;
                    }
                }
            }
        }

        if (w->flags & LEXCEUS_FLAG_ATTACK_HIT) {
            if (AnimGetFrame(&work->base.anim) == 6) {
                if (work->base.anim.timer == 19) {
                    w->flags |= LEXCEUS_FLAG_COMBO_FOLLOWUP;
                }
            }
        }

        if (w->flags & LEXCEUS_FLAG_COMBO_FOLLOWUP) {
            work->base.stateTimer = 0;
            work->base.state = 22;
            work->base.steps++;
        } else if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 22:
        if (work->base.stateTimer == 0) {
            w->hoverZ = 0;
            AnimReset(&work->base.anim);
            AnimChangeWithDef(sHumLexceusAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            w->flags &= ~LEXCEUS_FLAG_ATTACK_HIT;

#ifdef VERSION_EU
            if (act->btl->hcEffect == 49) {
                act->btl->hcEffectCount--;
            }
#endif
        }

        if (work->base.anim.timer == 0) {
            if (AnimGetGfxIndex(&work->base.anim) == 1) {
                MakeOpponentsHittable();

                if (act->btl->hcEffect == 49) {
                    if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                        ? ApplyAttackBox(0x149, act->x - 0x2800, act->y, act->z, 24, 20, 55)
                        : ApplyAttackBox(0x149, act->x + 0x2800, act->y, act->z, 24, 20, 55)) {
                        m4aSongNumStart(SONG_BTL_LEC_HIT);
                        w->flags |= LEXCEUS_FLAG_ATTACK_HIT;
                    }
                } else {
                    if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                        ? ApplyAttackBox(0x145, act->x - 0x2800, act->y, act->z, 24, 20, 55)
                        : ApplyAttackBox(0x145, act->x + 0x2800, act->y, act->z, 24, 20, 55)) {
                        m4aSongNumStart(SONG_BTL_LEC_HIT);
                        w->flags |= LEXCEUS_FLAG_ATTACK_HIT;
                    }
                }
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                act->x = act->x - 0x1900;
            } else {
                act->x = act->x + 0x1900;
            }

            AnimChangeWithDef(sHumLexceusAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
            work->base.stateTimer = 0;
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 27:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumLexceusAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
            w->hoverZ = 0;
            w->cameraBaseY = gBtlWork->y;
        }

        if (AnimGetFrame(&work->base.anim) == 3) {
            if (work->base.anim.timer == 0) {
                m4aSongNumStart(SONG_SND_288);
            }
        }

        switch (AnimGetFrame(&work->base.anim)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            HumFaceTarget(&work->base, 1);
            break;
        case 5:
            if (work->base.anim.timer == 0) {
                m4aSongNumStart(SONG_EF_AIRO);

                if ((act->flags & BTLOBJ_FLAG_FACING_LEFT) == 0) {
                    w->targetTilt = -0x800;
                } else {
                    w->targetTilt = 0x800;
                }

                w->tiltSteps = 10;

                if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    BgFxStartLexceusGround(act->x - 0x3000, act->y + 0xE00, 0, 0x147);
                } else {
                    BgFxStartLexceusGround(act->x + 0x3000, act->y + 0xE00, 0, 0x147);
                }
            }

            if (work->base.stateTimer % 6 <= 2) {
                gBtlWork->y2 = w->cameraBaseY - 0x4000;
            } else {
                gBtlWork->y2 = w->cameraBaseY + 0x4000;
            }

            break;
        case 6:
            if (work->base.stateTimer % 6 <= 2) {
                gBtlWork->y2 = w->cameraBaseY - 0x3000;
            } else {
                gBtlWork->y2 = w->cameraBaseY + 0x3000;
            }

            break;
        case 7:
            if (work->base.stateTimer % 6 <= 2) {
                gBtlWork->y2 = w->cameraBaseY - 0x2000;
            } else {
                gBtlWork->y2 = w->cameraBaseY + 0x2000;
            }

            break;
        case 8:
            if (work->base.stateTimer % 6 <= 2) {
                gBtlWork->y2 = w->cameraBaseY - 0x1000;
            } else {
                gBtlWork->y2 = w->cameraBaseY + 0x1000;
            }

            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
            w->targetTilt = 0;
            w->tiltSteps = 420;
        } else {
            work->base.stateTimer++;
        }

        break;
    }

    if (!(act->flags & BTLOBJ_FLAG_HURT)) {
        if (act->badStatus != BAD_STATUS_STOP) {
            LexceusHover(&work->base, w->hoverZ);
        }
    }

    if ((s16)w->tiltSteps > 0) {
        ApproachValue(&w->tilt, w->targetTilt, w->tiltSteps);
        w->tiltSteps--;
    }

    gBtlWork->rotation = w->tilt >> 8;

    if (p->z >= p->groundZ && p->hp > 0 && p->badStatus != BAD_STATUS_STOP && !(p->flags & BTLOBJ_FLAG_IN_CARD_ACTION)) {
        w->tiltSlide += (GetAngleDiff(0, gBtlWork->rotation) * 64 - w->tiltSlide) >> 4;
        p->x -= w->tiltSlide;
    } else {
        w->tiltSlide = 0;
    }

    TaskPoolUpdate(&w->tasks);
    return HumUpdate(&work->base);
}

void task_hum_lexceus_2(LexceusWork* work) {
    HumDraw(&work->base);

    if (work->scaleSteps > 0) {
        ApproachValue(&work->base.scaleX, work->targetScaleX, work->scaleSteps);
        ApproachValue(&work->base.scaleY, work->targetScaleY, work->scaleSteps);
        work->scaleSteps--;
    }

    TaskPoolDraw(&work->tasks);
}

void task_hum_lexceus_3(LexceusWork* work) {
    HumReleaseResources(&work->base);
    TaskPoolDestroy(&work->tasks);
}

void task_hum_lex_tmh_0(LexTmhWork* work, VixenNdlArgs* args) {
    work->palette = LoadObjPalette(gRexeusPalette, 0x20);
    work->tiles = AllocObjTiles(0x400, gRexeusTmhAxTiles);
    AnimInit(&work->anim, gRexeusTmhAxAnims, gRexeusTmhAxFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);

    if (args->facingLeft != 0) {
        work->facingLeft = 1;
    } else {
        work->facingLeft = 0;
    }

    work->x = args->x;
    work->y = args->y;
    work->z = args->z;
    work->targetX = gBtlWork->targetX + (GetRandom() % 65 - 32) * 256;
    work->targetY = gBtlWork->targetY + (GetRandom() % 33 - 16) * 256;
    work->state = 0;
    work->timer = 0;
    work->done = 0;
    work->vz = -0x980;
    work->tiles2 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    work->palette2 = LoadObjPalette(gBStatesPalette, 0x20);
    m4aSongNumStart(SONG_BTL_LEC_THRSW);
}

u8 task_hum_lex_tmh_1(LexTmhWork* work) {
    if ((gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) == 0) {
        return 0;
    }

    if (work->done != 0) {
        return 0;
    }

    switch (work->state) {
    case 0:
        work->x += (work->targetX - work->x) >> 4;
        work->y += (work->targetY - work->y) >> 4;
        work->z += work->vz;
        work->vz += 64;

        if (ApplyAttackBox(0x146, work->x, work->y, work->z, 16, 12, 16)) {
            m4aSongNumStart(SONG_BTL_LEC_THRHIT);
            work->timer = 0;
            work->state = 1;
        } else if (work->z >= 0) {
            m4aSongNumStart(SONG_BTL_LEC_THR);
            work->timer = 0;
            work->state = 1;
        } else {
            work->timer++;
        }

        break;
    case 1:
        if (work->timer == 0) {
            work->vz = -work->vz >> 1;

            if (gBtlWork->targetX < work->x) {
                work->flyLeft = 1;
            } else {
                work->flyLeft = 0;
            }
        }

        if (work->x < (gBtlWork->xMin - 32) << 8 ||
            work->x > (gBtlWork->xMax + 32) << 8) {
            work->done = 1;
        }

        if (work->flyLeft != 0) {
            work->x += -0x400;
        } else {
            work->x += 0x400;
        }

        work->y += (gBtlWork->targetY - work->y) >> 4;
        work->z += work->vz;
        work->vz += 64;

        if (ApplyAttackBox(0x146, work->x, work->y, work->z, 16, 12, 16)) {
            m4aSongNumStart(SONG_BTL_LEC_THRHIT);
        }

        if (work->z >= 0) {
            m4aSongNumStart(SONG_BTL_LEC_THR);
            work->vz = -work->vz >> 1;
            work->z = 0;
        }

        work->timer++;
        break;
    }

    AnimUpdate(&work->anim);
    return 1;
}

void task_hum_lex_tmh_2(LexTmhWork* work) {
    s16 x;
    s16 y;
    void* gfx;
    u16 attr;
    ObjAffine* affine;
    s32 scale;

    gfx = AnimGetGfx(&work->anim);

    if (work->facingLeft != 0) {
        attr = GetBattleSpritePriorityFlags(work->y);
    } else {
        attr = GetBattleSpritePriorityFlags(work->y) | 1;
    }

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gfx, work->tiles, work->palette, NULL, attr,
        -0x1004 - (work->y >> 8) * 4);

    if (work->z >= 0) {
        affine = NULL;
    } else {
        scale = 0x100 - (-work->z) / 256;

        if (scale <= 75) {
            scale = 76;
        }

        affine = AllocObjAffine(0, scale, scale, 0);
    }

    WorldToScreen(&x, &y, work->x, work->y, 0);
    DrawSprite(x, y, gUnk_08B22BA8, work->tiles2, work->palette2, affine, attr, 0xFFF0);
}

void task_hum_lex_tmh_3(LexTmhWork* work) {
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette2);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_hum_lex_tmh0_0(LexTmh0Work* work, VixenNdlArgs* args) {
    work->palette = LoadObjPalette(gRexeusPalette, 0x20);
    work->tiles = AllocObjTiles(0x400, gRexeusTmhTiles);
    AnimInit(&work->anim, gRexeusTmhAnims, gRexeusTmhFrames);
    AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);

    if (args->facingLeft != 0) {
        work->facingLeft = 1;
    } else {
        work->facingLeft = 0;
    }

    work->x = args->x;
    work->y = args->y;
    work->z = args->z;
    work->scale = 10;
    work->steps = 21;
    m4aSongNumStart(SONG_BTL_LEC_WEPUP);
}

u8 task_hum_lex_tmh0_1(LexTmh0Work* work) {
    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) {
        ApproachValue(&work->scale, 0x100, work->steps--);

        if (work->steps > 0) {
            AnimUpdate(&work->anim);
            return 1;
        }
    }

    return 0;
}

void task_hum_lex_tmh0_2(LexTmh0Work* work) {
    void* gfx;
    u16 attr;
    s32 sx;
    s32 h;
    ObjAffine* affine;
    s16 x;
    s16 y;

    gfx = AnimGetGfx(&work->anim);
    attr = GetBattleSpritePriorityFlags(work->y);
    h = work->scale;

    if (h == 0x100) {
        if (work->facingLeft == 0) {
            attr |= 1;
        }

        sx = h;
    } else {
        if (work->facingLeft != 0) {
            sx = h;
        } else {
            sx = -h;
        }
    }

    affine = AllocObjAffine(0, sx, 0x100, 0);
    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gfx, work->tiles, work->palette, affine, attr,
        -0x100C - (work->y >> 8) * 4);
}

void task_hum_lex_tmh0_3(LexTmh0Work* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_hum_lex_rock_0(LexRockWork* work, VixenNdlArgs* args) {
    if (args->facingLeft != 0) {
        work->facingLeft = 1;
    } else {
        work->facingLeft = 0;
    }

    work->x = args->x;
    work->y = args->y;
    work->z = args->z;
    work->state = 0;
    work->rockCount = 0;
    work->tiles = LoadObjTiles(gUnk_08B22CE4, 0x200);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    work->blinking = 0;
}

u8 task_hum_lex_rock_1(LexRockWork* work) {
    s32 i;
    s32 range;
    LexRockSub* e;
    u32 v;

    if ((gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) == 0) {
        return 0;
    }

    switch (work->state) {
    case 0:
        work->rockCount = 1;
        work->palette2 = LoadObjPalette(gRexeusRock01Palette, 0x20);
        work->tiles2[0] = AllocObjTiles(0xDC0, gRexeusRock01Tiles);
        AnimInit(&work->anim[0], gRexeusRock01Anims, gRexeusRock01Frames);
        AnimStart(&work->anim[0], 0, 0);
        work->state++;
        break;
    case 1:
        if (!AnimIsFinished(&work->anim[0])) {
            break;
        }

        work->state++;
        break;
    case 2:
        ReleaseObjTiles(work->tiles2[0]);
        ReleaseObjPalette(work->palette2);
        work->rockCount = 1;
        work->palette2 = LoadObjPalette(gRexeusRock02Palette, 0x20);
        work->tiles2[0] = AllocObjTiles(0xDC0, gRexeusRock02Tiles);
        AnimInit(&work->anim[0], gRexeusRock02Anims, gRexeusRock02Frames);
        AnimStart(&work->anim[0], 0, 0);
        work->z -= 0x4000;
        work->state++;
        break;
    case 3:
        if (gBtlWork->flags & 0x100000) {
            m4aSongNumStart(SONG_BTL_LEC_JMPKUEIKU);
            work->state += 2;
        }

        break;
    case 4:
        if (!AnimIsFinished(&work->anim[0])) {
            break;
        }

        work->state++;
        break;
    case 5:
        work->rockCount = 12;
        ReleaseObjTiles(work->tiles2[0]);

        for (i = 0; i < 12; i++) {
            e = &work->sub[i];
            work->tiles2[i] = AllocObjTiles(0xC0, gRexeusRock02Tiles);
            AnimInit(&work->anim[i], gRexeusRock02Anims, gRexeusRock02Frames);
            AnimStart(&work->anim[i], GetRandom() % 5 + 2, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START);

            if (work->facingLeft != 0) {
                e->vx = -(GetRandom() % 0x501 + 0x300);
            } else {
                e->vx = GetRandom() % 0x501 + 0x300;
            }

            e->vy = GetRandom() % 0x801 - 0x400;
            e->x = work->x + ((GetRandom() % 17 - 8) << 8);
            e->y = work->y + ((GetRandom() % 17 - 8) << 8);
            e->z = work->z + ((GetRandom() % 17 - 8) << 8);
            e->hasHit = 0;

            if (GetRandom() % 2) {
                e->vz = -(GetRandom() % 0x701 + 0x100);
            } else {
                e->vz = GetRandom() % 1 + 0x300;
            }
        }

        work->state++;
        work->timer = 0;
        break;
    case 6:
        if (work->blinking == 0) {
            MakeOpponentsHittable();

            for (i = 0; i < 12; i++) {
                e = &work->sub[i];
                e->x += e->vx;
                e->y += e->vy;
                e->z += e->vz;
                e->vz += 64;

                if (e->z > 0) {
                    e->z = 0;
                    e->vz = -(e->vz >> 1);
                }

                v = ClampBattlePosition(&e->x, &e->y, 0, 0);

                switch (v) {
                case 3:
                case 4:
                    e->vy = -e->vy;
                    break;
                case 1:
                case 2:
                    e->vx = -e->vx;
                    break;
                }

                if (e->hasHit == 0) {
                    if (ApplyAttackBox(0x148, e->x, e->y, e->z, 4, 4, 4)) {
                        m4aSongNumStart(SONG_BTL_MON_HIT02);
                        e->hasHit = 1;
                    }
                }
            }
        }

        if (work->timer == 80) {
            work->blinking = 1;
        }

        if (work->timer > 100) {
            return 0;
        }

        work->timer++;
        break;
    }

    for (i = 0; i < work->rockCount; i++) {
        AnimUpdate(&work->anim[i]);
    }

    return 1;
}

void task_hum_lex_rock_2(LexRockWork* work) {
    void* gfx;
    u16 attr;
    s16 x;
    s16 y;
    s32 i;
    LexRockSub* e;

    if (work->blinking != 0 && (work->timer & 1)) {
        return;
    }

    if (work->rockCount == 1) {
        gfx = AnimGetGfx(&work->anim[0]);

        if (work->facingLeft != 0) {
            attr = GetBattleSpritePriorityFlags(work->y);
        } else {
            attr = GetBattleSpritePriorityFlags(work->y) | 1;
        }

        WorldToScreen(&x, &y, work->x, work->y, work->z);
        DrawSprite(x, y, gfx, work->tiles2[0], work->palette2, NULL, attr,
            -0x1006 - (work->y >> 8) * 4);
    } else if (work->rockCount == 12) {
        for (i = 0; i < work->rockCount; i++) {
            e = &work->sub[i];
            gfx = AnimGetGfx(&work->anim[i]);

            if (work->facingLeft != 0) {
                attr = GetBattleSpritePriorityFlags(e->y);
            } else {
                attr = GetBattleSpritePriorityFlags(e->y) | 1;
            }

            WorldToScreen(&x, &y, e->x, e->y,
                e->z);
            DrawSprite(x, y, gfx, work->tiles2[i], work->palette2, NULL, attr,
                -0x1006 - (e->y >> 8) * 4);
            WorldToScreen(&x, &y, e->x, e->y, 0);
            DrawSprite(x, y, gUnk_08B22CBC, work->tiles, work->palette, NULL, attr, 0xFFFE);
        }
    }
}

void task_hum_lex_rock_3(LexRockWork* work) {
    s32 i;

    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);

    if (work->rockCount != 0) {
        ReleaseObjPalette(work->palette2);

        for (i = 0; i < work->rockCount; i++) {
            ReleaseObjTiles(work->tiles2[i]);
        }
    }
}
