#include "display.h"
#include "mode_vsbattle.h"
#include "enemy_common.h"
#include "system_state.h"
#include "gba/io_reg.h"
#include "fade.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "enemy_types.h"
#include "engine_math.h"
#include "game_state.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include <stddef.h>
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"

u16 gEnemyTileCounts[54] = {
    32, 32, 32, 32, 32, 34, 28, 24, 32,
    44, 50, 44, 52, 46, 72, 80, 88, 74,
    76, 43, 86, 86, 88, 72, 74, 106, 110,
    89, 100, 50, 50, 33, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 80, 80, 128, 128, 128, 128, 128, 128,
};

void EmyInit(EmyWork* work, const EmyDef* def, EmyObj* obj) {
    BtlObj* actor = &work->actor;
    u16 t;

    InitEnemyBtlObj(actor, &def->kind, obj->x, obj->y, obj->z);
    actor->attackOffset = def->attackOffset;
    actor->attackRangeX = def->attackRangeX;
    actor->attackRangeY = def->attackRangeY;
    actor->cardInterval = def->cardInterval;

    if (gBtlWork->actor->x < actor->x) {
        actor->flags |= BTLOBJ_FLAG_FACING_LEFT;
    }

    actor->flags |= (BTLOBJ_FLAG_INTANGIBLE | BTLOBJ_FLAG_CARD_USE_BLOCKED);
    t = gEnemyTileCounts[actor->kind];
    work->def = def;
    work->tiles = AllocObjTiles(t * 32, NULL);
    work->palette = LoadObjPalette(def->palette, 32);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    work->idleState = 0;
    work->state = 11;
    work->stateTimer = 0;
    work->steps = 0;
    work->flags = 0;
    work->visible = 1;
    work->angle = 0;
    work->speed = def->speed;
    work->vz = 0;
    actor->vx = 0;
    actor->vy = 0;
    work->spriteFlags = 0;

    if (actor->flags & BTLOBJ_FLAG_LARGE_SHADOW) {
        work->fxScale = 281;
    } else {
        work->fxScale = 0x100;
    }

    work->x = 0;
    work->y = 0;
    work->hoverZ = 0;
    AnimInit(&work->anim, NULL, NULL);
    AnimChangeWithDef(work->def->animDef, &work->anim, 0, ANIM_FLAG_LOOP, work->tiles);
    work->gfx = AnimGetGfx(&work->anim);
    TaskPoolInit(&work->tasks, 3);

    if (!(def->flags & EMY_DEF_FLAG_NO_SHADOW)) {
        TaskCreate(&work->tasks, &gTaskDescBtlShadow, actor);
    }

    TaskCreate(&work->tasks, &gTaskDescBtlBadstatus, actor);

    if (def->flags & EMY_DEF_FLAG_NO_SCALE_IN) {
        work->scaleX = 0x100;
        work->scaleY = 0x100;
    } else {
        work->scaleX = 0x80;
        work->scaleY = 0x80;
    }

    gBtlWork->enemyTileCount += t;
    gBtlWork->pendingEnemies--;
}

s16 EmyLungeAttack(EmyWork* work, s16 a, s16 b, s16 c, s32 d, s16 e, u16 f, s16 g, s16 h, u16 i) {
    BtlObj* actor = &work->actor;
    s32 ret;
    s32 v;
    s32 target;
    s16 steps;

    ret = 0;

    if (work->stateTimer == 0) {
        work->flags &= ~EMY_FLAG_LUNGE_HIT;
    }

    if (work->stateTimer >= a) {
        if (work->stateTimer < a + b) {
            steps = (a + b) - work->stateTimer;
            target = actor->originY;

            if (work->actor.flags & BTLOBJ_FLAG_FACING_LEFT) {
                v = actor->originX - (e << 8);
            } else {
                v = actor->originX + (e << 8);
            }

            if (actor->badStatus != BAD_STATUS_BIND) {
                ApproachValueHalfSteps(&actor->x, v, steps);
                ApproachValueHalfSteps(&actor->y, target, steps);
            }

            if (!(work->flags & EMY_FLAG_LUNGE_HIT)) {
                if (actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    if (ApplyAttackBox(d, actor->x - (g << 8), actor->y, actor->z + (h << 8), i, i / 2, i) != 0) {
                        m4aSongNumStart(f);
                        work->flags |= EMY_FLAG_LUNGE_HIT;
                        ret = 1;
                    }
                } else {
                    if (ApplyAttackBox(d, actor->x + (g << 8), actor->y, actor->z + (h << 8), i, i / 2, i) != 0) {
                        m4aSongNumStart(f);
                        ret = 1;
                        work->flags |= EMY_FLAG_LUNGE_HIT;
                    }
                }
            }
        } else if (work->stateTimer > a + b + c) {
            EmyReturnToIdle(work);
            return 2;
        }
    }

    work->stateTimer++;
    return ret;
}

void EmyReturnToIdle(EmyWork* work) {
    ClearBtlObjActionFlags(&work->actor);
    work->state = work->idleState;
    work->stateTimer = 0;
}

void EmyStartKnockback(EmyWork* work) {
    work->vz = -work->actor.knockbackLift * 3;
    work->actor.vx = ((gSineTable[work->actor.angle] << 1) * work->actor.knockbackSpeed) >> 8;
    work->actor.vy = ((-gSineTable[work->actor.angle + 0x40] << 1) * work->actor.knockbackSpeed) >> 8;
}

u8 EmyUpdateReaction(EmyWork* work) {
    BtlObj* actor = &work->actor;

    actor->prevX = actor->x;
    actor->prevY = actor->y;

    if (work->state == 3) {
        return 0;
    }

    if (work->state == 10) {
        return 0;
    }

    switch (UpdateBtlObjReaction(actor)) {
    case BTL_REACTION_STUNNED:
        EmyStartKnockback(work);
        work->state = 9;
        work->stateTimer = 0;
        break;
    case BTL_REACTION_GRAVITY:
        work->state = 15;
        work->stateTimer = 0;
        break;
    case BTL_REACTION_GRAVITY_DEFEATED:
        SetBtlObjUnhittable(actor, 1);
        work->state = 15;
        work->stateTimer = 0;
        break;
    case BTL_REACTION_HURT:
        EmyStartKnockback(work);
        work->state = 1;
        work->stateTimer = 0;
        break;
    case BTL_REACTION_WARPED:
        SetBtlObjUnhittable(actor, 1);
        work->state = 10;
        work->stateTimer = 0;
        break;
    case BTL_REACTION_DEFEATED:
        SetBtlObjUnhittable(actor, 1);
        EmyStartKnockback(work);
        work->state = 3;
        work->stateTimer = 0;
        break;
    case BTL_REACTION_TERRIFIED:
        work->state = 13;
        work->stateTimer = 0;
        break;
    case BTL_REACTION_HEALED:
        if (work->state != 12) {
            work->state = 6;
            work->stateTimer = 0;
        }

        break;
    case BTL_REACTION_CARD_ACTION:
        work->stateTimer = 0;
        return 1;
    case BTL_REACTION_CARD_BROKEN:
        work->state = 5;
        work->stateTimer = 0;
        work->visible = 1;
        break;
    case BTL_REACTION_STOPPED:
        if (work->state != 12) {
            work->state = 12;
            work->stateTimer = 0;
            actor->vx = actor->vy = 0;
        }

        break;
    }

    return 0;
}

void EmyFinishSpawn(EmyWork* work) {
    BtlObj* actor = &work->actor;

    if (gGameState.flags & GAME_FLAG_FIRST_STRIKE) {
        actor->flags |= (BTLOBJ_FLAG_DAMAGE_PENDING | BTLOBJ_FLAG_STUN_PENDING);

        if (gGameState.roomEffect == 3) {
            actor->damage = (actor->maxHp * 204) >> 8;
        } else {
            actor->damage = (actor->maxHp * 25) >> 8;
        }

        actor->hitFlags = ATTACK_FLAG_INFLICT_STUN;
        gBtlWork->pendingHitStop = 0;
        actor->knockbackSpeed = 0;
        actor->knockbackLift = 0;
    }

    work->state = work->idleState;
    work->stateTimer = 0;
    actor->flags &= ~(BTLOBJ_FLAG_INTANGIBLE | BTLOBJ_FLAG_CARD_USE_BLOCKED);
}

s32 EmyUpdateCommonStates(EmyWork* work) {
    BtlObj* actor = &work->actor;
    s32 x;
    s32 y;
    s32 z;

    GetEnemyTargetPosition(actor, &x, &y, &z);

    if (gBtlWork->flags & BTL_FLAG_FIELD_HIDDEN) {
        return 0;
    }

    switch (work->state) {
    case 11:
        if (work->stateTimer == 0) {
            work->steps = 18;
        }

        work->vz = 0;
        ApproachValue(&work->scaleY, 0x100, work->steps--);
        work->scaleX = work->scaleY;

        if (work->steps <= 0) {
            EmyFinishSpawn(work);
        } else {
            work->stateTimer++;
        }

        break;
    case 8:
        work->vz = 0;
        AnimChangeWithDef(work->def->animDef, &work->anim, 2, ANIM_FLAG_LOOP, work->tiles);
        TryEnemyCardUse(actor);
        actor->z += ((work->hoverZ + gSineTable[gFrameCounter & 0xFF] * 10) - actor->z) >> 4;

        if (GetRandom() % work->def->turnInterval == 0) {
            if (actor->x > x) {
                actor->flags |= BTLOBJ_FLAG_FACING_LEFT;
            } else {
                actor->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }
        }

        if (gBtlWork->flags & BTL_FLAG_ENEMY_MOVE_ENABLED) {
            s32 tx;
            s32 ty;
            s32 d;

            tx = work->x;
            ty = work->y;
            work->speed += 51;
            d = (tx - actor->x) >> 5;

            if (d > work->speed) {
                d = work->speed;
            } else if (d < -work->speed) {
                d = -work->speed;
            }

            actor->x += d;
            d = (ty - actor->y) >> 5;

            if (d > work->speed) {
                d = work->speed;
            } else if (d < -work->speed) {
                d = -work->speed;
            }

            actor->y += d;

            if (work->stateTimer > 64) {
                work->state = work->idleState;
            } else {
                work->stateTimer++;
            }
        }

        break;
    case 7:
        work->vz = 0;
        AnimChangeWithDef(work->def->animDef, &work->anim, 0, ANIM_FLAG_LOOP, work->tiles);
        TryEnemyCardUse(actor);
        actor->z += ((work->hoverZ + gSineTable[gFrameCounter * 2 & 0xFF] * 12) - actor->z) >> 4;

        if (GetRandom() % work->def->turnInterval == 0) {
            if (actor->x > x) {
                actor->flags |= BTLOBJ_FLAG_FACING_LEFT;
            } else {
                actor->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }
        }

        if (GetRandom() % work->def->moveInterval == 0) {
            work->speed = 0;
            work->state = 8;

            if (GetRandom() % 2 == 0) {
                s32 lo;

                work->x = x - ((actor->attackOffset + ((lo = -actor->attackRangeX) + GetRandom() % (actor->attackRangeX - lo + 1))) << 8);
            } else {
                s32 lo;

                work->x = x + ((actor->attackOffset + ((lo = -actor->attackRangeX) + GetRandom() % (actor->attackRangeX - lo + 1))) << 8);
            }

            work->y = y + ((GetRandom() % 121 - 60) << 8);
            work->hoverZ = -((GetRandom() % 49 + 16) << 8);
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    case 13:
        if (work->stateTimer == 0) {
            AnimReset(&work->anim);
            AnimChangeWithDef(work->def->animDef, &work->anim, 1, 0, work->tiles);
            actor->originX = actor->x;
            actor->originY = actor->y;
        }

        switch (work->stateTimer % 4) {
        case 0:
            actor->x = actor->originX + 0x100;
            actor->y = actor->originY;
            break;
        case 1:
            actor->x = actor->originX - 0x100;
            actor->y = actor->originY;
            break;
        case 2:
            actor->x = actor->originX;
            actor->y = actor->originY + 0x100;
            break;
        case 3:
            actor->x = actor->originX;
            actor->y = actor->originY - 0x100;
            break;
        }

        if (AnimIsFinished(&work->anim)) {
            ClearBtlObjActionFlags(actor);
            work->state = 14;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    case 14:
        if (gBtlWork->flags & BTL_FLAG_ENEMY_MOVE_ENABLED) {
            s32 tx;
            s32 ty;

            if (work->stateTimer == 0) {
                AnimChangeWithDef(work->def->animDef, &work->anim, 2, ANIM_FLAG_LOOP, work->tiles);
            }

            if (x < 0x10000) {
                tx = x >> 1;
            } else {
                tx = (x + 0x20000) >> 1;
            }

            if (y < ((gBtlWork->yMin + gBtlWork->yMax) >> 1) << 8) {
                ty = (gBtlWork->yMin << 8) - 0x4000;
            } else {
                ty = (gBtlWork->yMax << 8) + 0x4000;
            }

            work->angle = GetAngle(tx, ty, actor->x, actor->y);
            actor->x += ((gSineTable[work->angle] << 1) * work->def->speed) >> 8;
            actor->y += ((-gSineTable[work->angle + 64] << 1) * work->def->speed) >> 8;

            if ((s8)work->angle >= 0) {
                actor->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            } else {
                actor->flags |= BTLOBJ_FLAG_FACING_LEFT;
            }

            if (actor->badStatus != BAD_STATUS_TERROR) {
                work->state = work->idleState;
                work->stateTimer = 0;
            } else {
                work->stateTimer++;
            }
        }

        break;
    case 4:
        if (gBtlWork->flags & BTL_FLAG_ENEMY_MOVE_ENABLED) {
            s32 px;
            s32 tx;
            s32 ty;
            s32 d;

            AnimChangeWithDef(work->def->animDef, &work->anim, 2, ANIM_FLAG_LOOP, work->tiles);
            TryEnemyCardUse(actor);
            px = x;
            tx = px + work->x;
            ty = y;

            if (tx < (gBtlWork->xMin + 32) << 8) {
                tx = px + ((actor->attackOffset + actor->attackRangeX) << 8);
            } else if (tx > (gBtlWork->xMax - 32) << 8) {
                tx = ty - ((actor->attackOffset + actor->attackRangeX) << 8);
            }

            if (GetRandom() % 100 == 0) {
                if (GetRandom() % 2 == 0) {
                    s32 lo;

                    work->x = -((actor->attackOffset + ((lo = -actor->attackRangeX) + GetRandom() % (actor->attackRangeX - lo + 1))) << 8);
                } else {
                    s32 lo;

                    work->x = ((actor->attackOffset + ((lo = -actor->attackRangeX) + GetRandom() % (actor->attackRangeX - lo + 1))) << 8);
                }
            } else {
                if ((tx - actor->x >= 0 ? tx - actor->x : actor->x - tx) > 0x400
                    || (ty - actor->y >= 0 ? ty - actor->y : actor->y - ty) > 0x400) {
                    work->angle = GetAngle(actor->x, actor->y, tx, ty);
                    actor->x += (gSineTable[work->angle] * work->speed) >> 8;
                    actor->y += (-gSineTable[work->angle + 64] * work->speed) >> 8;
                } else if (AnimIsFinished(&work->anim)) {
                    work->state = work->idleState;
                }
            }

            if (GetRandom() % work->def->turnInterval == 0) {
                if (actor->x > x) {
                    actor->flags |= BTLOBJ_FLAG_FACING_LEFT;
                } else {
                    actor->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
                }
            }
        }

        break;
    case 0:
        AnimChangeWithDef(work->def->animDef, &work->anim, 0, ANIM_FLAG_LOOP, work->tiles);
        TryEnemyCardUse(actor);

        if (GetRandom() % work->def->moveInterval == 0) {
            work->state = 4;

            if (GetRandom() % 2 == 0) {
                s32 lo;

                work->x = -((actor->attackOffset + ((lo = -actor->attackRangeX) + GetRandom() % (actor->attackRangeX - lo + 1))) << 8);
            } else {
                s32 lo;

                work->x = ((actor->attackOffset + ((lo = -actor->attackRangeX) + GetRandom() % (actor->attackRangeX - lo + 1))) << 8);
            }
        }

        if (GetRandom() % work->def->turnInterval == 0) {
            if (actor->x > x) {
                actor->flags |= BTLOBJ_FLAG_FACING_LEFT;
            } else {
                actor->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }
        }

        break;
    case 12:
        if (actor->badStatus != BAD_STATUS_STOP) {
            work->state = work->idleState;
            ClearBtlObjActionFlags(actor);
        }

        break;
    case 9:
        if (work->stateTimer == 0) {
            AnimReset(&work->anim);
            AnimChangeWithDef(work->def->animDef, &work->anim, 1, 0, work->tiles);
            work->stateTimer++;
        }

        if (AnimIsFinished(&work->anim)) {
            actor->flags &= ~BTLOBJ_FLAG_HIT_LOCKED;
            actor->flags &= ~BTLOBJ_FLAG_HURT;
        }

        if (GetRandom() % 10 == 0) {
            actor->badStatusTimer--;
        }

        if (actor->badStatus != BAD_STATUS_STUN) {
            ClearBtlObjActionFlags(actor);
            work->state = work->idleState;
            work->stateTimer = 0;
        }

        break;
    case 1:
        if (work->stateTimer == 0) {
            AnimReset(&work->anim);
            AnimChangeWithDef(work->def->animDef, &work->anim, 1, 0, work->tiles);
        }

        if (work->stateTimer >= work->def->hitStunFrames) {
            s32 ok = 0;

            ClearBtlObjActionFlags(actor);
            work->state = 2;
            work->stateTimer = 0;

            if (actor->x < x) {
                if (actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    if (GetRandom() % 5 == 0) {
                        actor->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
                        ok = 1;
                    }
                } else {
                    ok = 1;
                }
            } else {
                if (actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    ok = 1;
                } else {
                    if (GetRandom() % 5 == 0) {
                        actor->flags |= BTLOBJ_FLAG_FACING_LEFT;
                        ok = 1;
                    }
                }
            }

            if (ok == 0) {
                break;
            }

            if (GetRandom() % 4 == 0) {
                RequestEnemyCardUse(actor);
            }
        } else {
            work->stateTimer++;
        }

        break;
    case 2:
        if (AnimIsFinished(&work->anim)) {
            work->state = work->idleState;
            work->stateTimer = 0;
        }

        break;
    case 15:
        if (work->stateTimer == 0) {
            ColliderSetDisabled(&actor->collider, 1);
            actor->flags |= BTLOBJ_FLAG_INTANGIBLE;
            AnimChangeWithDef(work->def->animDef, &work->anim, 1, 0, work->tiles);
            work->anim.frame = 0;
            work->anim.timer = 0;
            work->vz = 0x400;
            actor->vx = 0;
            actor->vy = 0;
            work->steps = 10;
        }

        ApproachValue(&work->scaleY, 64, work->steps--);

        if (work->steps <= 0) {
            work->stateTimer = 0;
            work->state = 16;
        } else {
            work->stateTimer++;
        }

        break;
    case 16:
        if (work->stateTimer > 44) {
            if (actor->hp <= 0) {
                work->state = 3;
            } else {
                work->state = 17;
            }

            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    case 17:
        if (work->stateTimer == 0) {
            ColliderSetDisabled(&actor->collider, 0);
            work->steps = 10;
        }

        ApproachValueHalfSteps(&work->scaleY, 0x100, work->steps--);

        if (work->steps <= 0) {
            actor->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
            ClearBtlObjActionFlags(actor);
            work->state = work->idleState;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    case 6:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(work->def->animDef, &work->anim, 0, ANIM_FLAG_LOOP, work->tiles);
            work->scaleX = 0x100;
            work->scaleY = 0x100;
            actor->vx = 0;
            actor->vy = 0;
        }

        work->vz = 0;

        if (work->stateTimer == 40) {
            CreateBtlPopTask(actor, 10);
            actor->hp -= actor->damage;

            if (actor->hp > actor->maxHp) {
                actor->hp = actor->maxHp;
            }

            ClearBtlObjActionFlags(actor);
            work->state = work->idleState;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    case 10:
        if (work->stateTimer == 0) {
            work->steps = 16;
        }

        actor->z -= (16 - work->steps) << 8;

        if (BgAnimIsStopped()) {
            gBldCnt = (BLDCNT_TGT1_OBJ | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
            work->spriteFlags = SPRITE_FLAG_BLEND;
            SetBlendAlpha(16 - work->steps, work->steps);
        } else {
            work->spriteFlags &= ~SPRITE_FLAG_BLEND;
        }

        ApproachValue(&work->scaleX, 10, work->steps);
        ApproachValue(&work->scaleY, 0x200, work->steps);
        work->steps--;

        if (work->steps <= 0) {
            if (gBtlWork->enemyCount == 1 && gBtlWork->pendingEnemies <= 0) {
                BgAnimStop();
                FadeStartIn(FADE_MODE_ADD_WHITE, 20);
                FadeLock();
            }

            DropEnemyPrizes(actor);
            SetEnemyJiminyFlag(actor);
            return 0;
        } else {
            work->stateTimer++;
        }

        break;
    case 3:
        if (work->stateTimer == 0) {
            s32 t;

            AnimChangeWithDef(work->def->animDef, &work->anim, 1, 0, work->tiles);

            if (actor->flags & BTLOBJ_FLAG_NO_DEATH_FX) {
                work->stateTimer++;
                break;
            }

            if (actor->vx != 0) {
                break;
            }

            if (actor->vy != 0) {
                break;
            }

            if (actor->z != actor->groundZ) {
                break;
            }

            if (BgFxIsActive()) {
                break;
            }

            t = (actor->height / 2) * work->fxScale;

            if (work->flags & EMY_FLAG_DARK_DEATH) {
                BgFxStartDarkDeath(actor->x, actor->y, actor->z - t, work->fxScale);
            } else {
                BgFxStartEnemyDeath(actor->x, actor->y, actor->z - t, work->fxScale);
            }

            work->stateTimer++;
        } else if (work->stateTimer > 0) {
            if (gBtlWork->enemyCount == 1 && gBtlWork->pendingEnemies <= 0) {
                FadeStartIn(FADE_MODE_ADD_WHITE, 20);
                FadeLock();
            }

            DropEnemyPrizes(actor);

            if (gGameState.roomEffect == 6) {
                if (GetRandom() % 10 == 0) {
                    TryDropPremireCard(actor);
                }
            } else {
                if (GetRandom() % 1000 == 0) {
                    TryDropPremireCard(actor);
                }
            }

            gBtlWork->flags |= BTL_FLAG_ENEMY_DEFEATED;
            SetEnemyJiminyFlag(actor);
            return 0;
        }

        break;
    case 5:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(work->def->animDef, &work->anim, 1, 0, work->tiles);
        }

        if (AnimIsFinished(&work->anim) && work->stateTimer > 40) {
            ClearBtlObjActionFlags(actor);
            work->state = work->idleState;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }

        break;
    }

    if (actor->badStatus != BAD_STATUS_STOP) {
        actor->z += work->vz;
        work->vz += gBtlWork->gravity;

        if (actor->z > 0) {
            actor->z = 0;
            work->vz = 0;
        }

        if (actor->collider.colliding != 0 && !(actor->flags & BTLOBJ_FLAG_IN_CARD_ACTION) && !(actor->collider.other->flags & COLLIDER_FLAG_PASS_THROUGH)) {
            actor->x += actor->collider.pushX >> 1;
            actor->y += actor->collider.pushY >> 1;
        }
    }

    if (actor->vx > 0) {
        actor->x += actor->vx;
        actor->vx -= 17;

        if (actor->vx < 0) {
            actor->vx = 0;
        }
    } else if (actor->vx < 0) {
        actor->x += actor->vx;
        actor->vx += 17;

        if (actor->vx > 0) {
            actor->vx = 0;
        }
    }

    if (actor->vy > 0) {
        actor->y += actor->vy;
        actor->vy -= 17;

        if (actor->vy < 0) {
            actor->vy = 0;
        }
    } else if (actor->vy < 0) {
        actor->y += actor->vy;
        actor->vy += 17;

        if (actor->vy > 0) {
            actor->vy = 0;
        }
    }

    switch (ClampBattlePosition(&actor->x, &actor->y, -20, 0)) {
    case 1:
    case 2:
        work->flags |= EMY_FLAG_AT_FIELD_EDGE;
        actor->vx = -(actor->vx >> 1);
        break;
    case 3:
    case 4:
        work->flags |= EMY_FLAG_AT_FIELD_EDGE;
        actor->vy = -(actor->vy >> 1);
        break;
    default:
        work->flags &= ~EMY_FLAG_AT_FIELD_EDGE;
        break;
    }

    if (actor->flags & BTLOBJ_FLAG_IN_CARD_ACTION) {
        work->gfx = AnimUpdate(&work->anim);
    } else if (actor->badStatus != BAD_STATUS_STOP) {
        if (gBtlWork->flags & BTL_FLAG_ENEMY_FRAME_CHANGED) {
            if (!AnimIsFrameEnding(&work->anim)) {
                work->gfx = AnimUpdate(&work->anim);
            }
        } else {
            if (AnimIsFrameEnding(&work->anim)) {
                gBtlWork->flags |= BTL_FLAG_ENEMY_FRAME_CHANGED;
            }

            work->gfx = AnimUpdate(&work->anim);
        }
    }

    if (actor->badStatus == BAD_STATUS_BIND) {
        actor->x = actor->prevX;
        actor->y = actor->prevY;
    }

    TaskPoolUpdate(&work->tasks);
    ColliderSetPosition(&actor->collider, actor->x, actor->y, actor->z);
    return 1;
}

void EmyDraw(EmyWork* work) {
    if (work->visible != 0) {
        BtlObj* actor;
        u16 g;
        ObjAffine* affine;
        s32 sx;
        s32 sy;
        s16 x;
        s16 y;

        actor = &work->actor;
        g = GetBattleSpritePriorityFlags(actor->y) | work->spriteFlags;
        WorldToScreen(&x, &y, actor->x, actor->y, actor->z);

        if (work->scaleX == 0x100 && work->scaleY == 0x100) {
            if (actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
                sy = gBtlWork->scale;
                sx = sy;
            } else if (gBtlWork->scale == 0x100) {
                sy = gBtlWork->scale;
                sx = sy;
                g |= 1;
            } else {
                sy = gBtlWork->scale;
                sx = -sy;
            }
        } else {
            if (actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
                sx = (gBtlWork->scale * work->scaleX) >> 8;
                sy = gBtlWork->scale;
                sy = (sy * work->scaleY) >> 8;
            } else {
                sx = -((gBtlWork->scale * work->scaleX) >> 8);
                sy = gBtlWork->scale;
                sy = (sy * work->scaleY) >> 8;
            }
        }

        if (sy == 0x100 && sx == sy) {
            affine = NULL;
        } else if (sy < 256) {
            affine = AllocObjAffine(0, sx, sy, 0);
        } else {
            affine = AllocObjAffine(0, sx, sy, 1);
        }

        if (StepHitFlash(actor) != 0) {
            DrawSprite(x, y, work->gfx, work->tiles, work->palette2, affine, g, (-4100 - ((actor->y >> 8) << 2)) | 3);
        } else {
            DrawSprite(x, y, work->gfx, work->tiles, work->palette, affine, g, (-4100 - ((actor->y >> 8) << 2)) | 3);
        }

        TaskPoolDraw(&work->tasks);
    }
}

void EmyReleaseResources(EmyWork* work) {
    gBtlWork->enemyTileCount -= gEnemyTileCounts[work->actor.kind];

    if (gBtlWork->actor2 == &work->actor) {
        gBtlWork->actor2 = NULL;
    }

    ReleaseEnemyBtlObj(&work->actor);

    if (gBtlWork->enemyCount == 0) {
        if (gBtlWork->pendingEnemies <= 0) {
            if (gBtlWork->actor->hp > 0) {
                gBtlWork->flags |= BTL_FLAG_BATTLE_OVER;
            }
        }
    }

    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
    TaskPoolDestroy(&work->tasks);
}
