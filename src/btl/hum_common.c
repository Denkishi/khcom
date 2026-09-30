#include "mode_vsbattle.h"
#include "hum_common.h"
#include "prize_types.h"
#include "btl_api.h"
#include "fade.h"
#include "songs.h"

void HumInit(HumWork* work, const HumDef* def) {
    BtlObj* actor = &work->actor;

    s32 a = 0x14000;
    s32 b = 0x18100;
    s32 z = 0;

    InitEnemyBtlObj(actor, &def->kind, a, b, z);
    actor->attackOffset = 0;
    actor->attackRangeX = 0;
    actor->attackRangeY = 0;
    actor->cardInterval = 1;
    actor->flags |= BTLOBJ_FLAG_HUM_BOSS;

    if (gBtlWork->actor->x < actor->x) {
        actor->flags |= BTLOBJ_FLAG_FACING_LEFT;
    }

    work->def = def;
    work->tiles = AllocObjTiles(def->tileCount * 32, 0);
    work->palette = LoadObjPalette(def->palette, 32);
    work->paletteData = def->palette;
    work->stateTimer = 0;
    work->steps = 0;
    work->flags = 0;
    work->vz = 0;
    actor->vx = 0;
    actor->vy = 0;
    work->targetX = 0;
    work->targetY = 0;
    work->targetZ = 0;
    work->boundsMargin = 0xFFF0;
    work->unk_17C = 1;
    AnimInit(&work->anim, 0, 0);
    TaskPoolInit(&work->tasks, 3);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, actor);
    TaskCreate(&work->tasks, &gTaskDescBtlBadstatus, actor);
    work->state = 12;
    work->scaleX = 0x100;
    work->scaleY = 0x100;
    work->sub = 0;
    work->sub2 = 0;
    work->stockMoves = 0;
    gRikuBtlWork->actor = actor;
    gBtlWork->actor3 = actor;
    actor->btl = gRikuBtlWork;
    actor->flags |= (BTLOBJ_FLAG_IMMUNE_TERROR | BTLOBJ_FLAG_IMMUNE_CONFUSE);
}

void HumSubInit(HumWork* work, HumSub* sub, const HumSubDef* def) {
    if (work->sub == NULL) {
        work->sub = sub;
    } else {
        work->sub2 = sub;
    }

    sub->tiles = AllocObjTiles(def->tileCount * 32, 0);
    sub->palette2 = sub->palette = LoadObjPalette(def->palette, 32);
    sub->x = work->actor.x;
    sub->y = work->actor.y;
    sub->z = work->actor.z;
    sub->flags = 0;
    AnimInit(&sub->anim, 0, 0);
}

void HumSubReleaseGraphics(HumSub* sub) {
    if (sub != NULL) {
        ReleaseObjTiles(sub->tiles);
        ReleaseObjPalette(sub->palette);
    }
}

void HumReleaseResources(HumWork* work) {
    if (gBtlWork->actor2 == &work->actor) {
        gBtlWork->actor2 = 0;
    }

    HumSubReleaseGraphics(work->sub);
    HumSubReleaseGraphics(work->sub2);
    gBtlWork->actor3 = 0;
    ReleaseEnemyBtlObj(&work->actor);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

void HumStartKnockback(HumWork* work) {
    work->vz = -work->actor.knockbackLift * 3;
    work->actor.vx = ((gSineTable[work->actor.angle] << 1) * work->actor.knockbackSpeed) >> 8;
    work->actor.vy = ((-gSineTable[work->actor.angle + 0x40] << 1) * work->actor.knockbackSpeed) >> 8;
}

s32 _0800E434(HumWork* work) {
    BtlObj* actor = &work->actor;
    s32 r;

    actor->prevX = actor->x;
    actor->prevY = actor->y;
    r = UpdateBtlObjReaction(actor);

    switch (r) {
    case BTL_REACTION_CARD_ACTION:
        work->flags |= HUM_FLAG_PASS_THROUGH;
        gRikuBtlWork->flags &= ~BTL_FLAG_DISMISS_SUMMONS;
        work->itemIndex = 0;
        work->stateTimer = 0;
        AnimReset(&work->anim);
        break;
    case BTL_REACTION_WARPED:
        FadeStartIn(FADE_MODE_ADD_WHITE, 20);
        gBtlWork->hitStop = 15;

        if (actor->badStatus != BAD_STATUS_STUN) {
            actor->badStatus = BAD_STATUS_STUN;
            actor->badStatusTimer = 0x168;
        }

        work->state = 11;
        work->stateTimer = 0;
        break;
    case BTL_REACTION_STUNNED:
        HumStartKnockback(work);
        work->state = 11;
        work->stateTimer = 0;
        break;
    case BTL_REACTION_GRAVITY:
    case BTL_REACTION_GRAVITY_DEFEATED:
        work->state = 14;
        work->stateTimer = 0;
        break;
    case BTL_REACTION_HURT:
        HumStartKnockback(work);
        work->state = 1;
        work->stateTimer = 0;
        break;
    case BTL_REACTION_DEFEATED:
        work->flags |= HUM_FLAG_PASS_THROUGH;
        work->state = 3;
        work->stateTimer = 0;
        break;
    case BTL_REACTION_HEALED:
        work->state = 10;
        work->stateTimer = 0;
        break;
    case BTL_REACTION_CARD_BROKEN:
        work->state = 9;
        work->stateTimer = 0;
        break;
    case BTL_REACTION_STOPPED:
        if (work->state != 13) {
            work->state = 13;
            work->stateTimer = 0;
            actor->vx = actor->vy = 0;
        }
        break;
    }

    return r;
}

void HumSubUpdateAnimation(HumSub* sub) {
    if (sub != NULL) {
        if (!(sub->flags & HUM_SUB_FLAG_HIDDEN)) {
            sub->gfx = AnimUpdate(&sub->anim);
        }
    }
}


s32 HumUpdate(HumWork* work) {
    BtlObj* actor = &work->actor;
    s32 x;

    GetEnemyTargetPosition(actor, &x, 0, 0);

    switch (work->state) {
    case 12:
        if (work->stateTimer > 100) {
            work->state = 0;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 1:
        if (work->stateTimer == 0) {
            AnimReset(&work->anim);
        }
        if (work->stateTimer > 10) {
            ClearBtlObjActionFlags(actor);
            work->state = 2;
            work->stateTimer = 0;

            if (actor->x < x) {
                if (actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    if (GetRandom() % 3 == 0) {
                        actor->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
                    }
                }
            } else {
                if (!(actor->flags & BTLOBJ_FLAG_FACING_LEFT)) {
                    if (GetRandom() % 3 == 0) {
                        actor->flags |= BTLOBJ_FLAG_FACING_LEFT;
                    }
                }
            }
            HumChooseCardAction(work, 3, 64, 64, 32);
        } else {
            work->stateTimer++;
        }
        break;
    case 2:
        if (AnimIsFinished(&work->anim)) {
            work->state = 0;
            work->stateTimer = 0;
        }
        break;
    case 14:
        if (work->stateTimer == 0) {
            AnimReset(&work->anim);
            ColliderSetDisabled(&actor->collider, 1);
            actor->flags |= BTLOBJ_FLAG_INTANGIBLE;
            work->anim.frame = 0;
            work->anim.timer = 0;
            work->vz = 0x400;
            actor->vx = 0;
            actor->vy = 0;
            work->steps = 10;
        }
        ApproachValue(&work->scaleY, 64, work->steps--);

        if (work->steps > 0) {
            work->stateTimer++;
        } else {
            work->stateTimer = 0;
            work->state = 15;
        }
        break;
    case 15:
        if (work->stateTimer > 44) {
            if (actor->hp <= 0) {
                work->state = 3;
            } else {
                work->state = 16;
            }
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 16:
        if (work->stateTimer == 0) {
            ColliderSetDisabled(&actor->collider, 0);
            work->steps = 10;
        }
        ApproachValueHalfSteps(&work->scaleY, 0x100, work->steps--);

        if (work->steps <= 0) {
            actor->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
            ClearBtlObjActionFlags(actor);
            work->state = 0;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 11:
        if (work->stateTimer == 0) {
            AnimReset(&work->anim);
            work->stateTimer++;
        }
        if (AnimIsFinished(&work->anim)) {
            actor->flags &= ~BTLOBJ_FLAG_HIT_LOCKED;
            actor->flags &= ~BTLOBJ_FLAG_HURT;
        }
        if (GetRandom() % 3 == 0) {
            actor->badStatusTimer -= 6;
        }
        if (actor->badStatus != BAD_STATUS_STUN) {
            ClearBtlObjActionFlags(actor);
            work->state = 0;
            work->stateTimer = 0;
        }
        break;
    case 9:
        if (AnimIsFinished(&work->anim) && work->stateTimer > 60) {
            ClearBtlObjActionFlags(actor);
            work->state = 0;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 10:
        if (work->stateTimer == 0) {
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
            work->state = 0;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 18:
        if (work->stateTimer == 23) {
            BgFxStartPotion(actor->x, actor->y, actor->z - ((actor->height - 48) << 8));
        }
        if (work->stateTimer > 23 && BgFxIsActive() == 0) {
            switch (work->itemIndex) {
            case 0:
                RequestRikuPotion();
                break;
            case 1:
                RequestRikuHiPotion();
                break;
            case 2:
                RequestRikuMegaPotion();
                break;
            case 3:
                RequestRikuEther();
                break;
            case 4:
                RequestRikuMegaEther();
                break;
            case 5:
                RequestRikuElixir();
                break;
            default:
                RequestRikuMegalixir();
                break;
            }
            ClearBtlObjActionFlags(actor);
            work->state = 0;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 13:
        if (actor->badStatus != BAD_STATUS_STOP) {
            work->state = 0;
            ClearBtlObjActionFlags(actor);
        }
        break;
    case 3:
        if (work->stateTimer == 0) {
            BeginBossDefeat(actor);

            if (!(work->flags & HUM_FLAG_BOSS_DEATH)) {
                m4aSongNumStart(SONG_BTL_GF_LOOP);
            }
            SetBattleZoom(1, 0x100, gBtlWork->x2, gBtlWork->y2);
        }
        if (FadeIsActive() == 0) {
            work->stateTimer = 0;

            if (work->flags & HUM_FLAG_BOSS_DEATH) {
                work->state = 6;
            } else {
                work->state = 4;
            }
        } else {
            BtlMapFollowPosition(actor->x, actor->y, actor->z);
            work->stateTimer++;
        }
        break;
    case 4:
        if (work->stateTimer == 0) {
            BgFxStartHumDefeat(actor->x, actor->y + actor->z - (actor->centerHeight << 8));
            FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
        }
        BtlMapFollowPosition(actor->x, actor->y, actor->z);
        work->vz = 0;

        if (work->stateTimer > 150) {
            work->stateTimer = 0;
            work->state = 5;
        } else {
            work->stateTimer++;
        }
        break;
    case 5:
        if (work->stateTimer == 0) {
            PrizeCardArg arg;

            FadeStartIn(FADE_MODE_ADD_WHITE, 60);
            FadeLock();
            m4aSongNumStart(SONG_BTL_KU_JUMP);
            gBtlWork->flags |= BTL_FLAG_STOP_BGFX;
            EndBossDefeat();
            DropBossPrizes(actor);
            arg.x = actor->x;
            arg.y = actor->y;
            arg.z = -0x4600;
            CreateBossPrizeCardTask(&gBtlWork->taskPools[0], &arg);
            return 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 6:
        if (work->stateTimer == 0) {
            BgFxStartBossDeath(actor->x, actor->y + actor->z - (actor->centerHeight << 8));
            FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
        }
        BtlMapFollowPosition(actor->x, actor->y, actor->z);
        work->vz = 0;

        if (work->stateTimer > 150) {
            work->stateTimer = 0;
            work->state = 7;
            BgFxStartBossDeathFlash();
        } else {
            work->stateTimer++;
        }
        break;
    case 7:
        BtlMapFollowPosition(actor->x, actor->y, actor->z);

        if (BgFxIsActive() == 0) {
            PrizeCardArg arg2;

            EndBossDefeat();
#ifdef VERSION_EU
            ClampBattlePosition(&actor->x, &actor->y, (s16)(work->boundsMargin - 8), -16);
#endif
            DropBossPrizes(actor);
            arg2.x = actor->x;
            arg2.y = actor->y;
            arg2.z = -0x4600;
            CreateBossPrizeCardTask(&gBtlWork->taskPools[0], &arg2);
            return 0;
        }
        work->stateTimer++;
        break;
    case 0:
        work->flags &= ~HUM_FLAG_PASS_THROUGH;

        if (IsRikuReloadCardSelected()) {
            work->stateTimer = 0;
            work->state = 17;
        }
        break;
    case 17:
        SetRikuReloadCharging();

        if (IsRikuReloadCardSelected() == 0) {
            work->stateTimer = 0;
            work->state = 0;
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
        if (actor->collider.colliding != 0 && !(work->flags & HUM_FLAG_PASS_THROUGH) && !(actor->collider.other->flags & COLLIDER_FLAG_PASS_THROUGH)) {
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

    if (!(work->flags & HUM_FLAG_IGNORE_BOUNDS)) {
        switch (ClampBattlePosition(&actor->x, &actor->y, work->boundsMargin, 0)) {
        case 1:
        case 2:
            actor->vx = -(actor->vx >> 1);
            work->flags |= HUM_FLAG_AT_FIELD_EDGE;
            break;
        case 3:
        case 4:
            actor->vy = -(actor->vy >> 1);
            work->flags |= HUM_FLAG_AT_FIELD_EDGE;
            break;
        default:
            work->flags &= ~HUM_FLAG_AT_FIELD_EDGE;
            break;
        }
    }

    if (actor->badStatus != BAD_STATUS_STOP) {
        work->gfx = AnimUpdate(&work->anim);
        HumSubUpdateAnimation(work->sub);
        HumSubUpdateAnimation(work->sub2);
    }

    if (actor->badStatus == BAD_STATUS_BIND) {
        actor->x = actor->prevX;
        actor->y = actor->prevY;
    }

    TaskPoolUpdate(&work->tasks);
    ColliderSetPosition(&actor->collider, actor->x, actor->y, actor->z);
    return 1;
}
