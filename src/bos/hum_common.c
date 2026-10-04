/**
 * hum_common.c
 * Humanoid Boss Common Routines
 */

#include "prize_types.h"
#include "btl_api.h"
#include "fade.h"
#include "songs.h"
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
#include "obj_api.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "battle.h"
#include "display.h"
#include "field_state.h"
#include "hum_common.h"
#include "macros.h"
#include "obj.h"
#include "romcri_backgrounds.h"
#include "card_battle_riku.h"
#include "sprite_palettes.h"

BtlWork* gRikuBtlWork EWRAM_COMMON(4);
FieldState* gFieldState EWRAM_COMMON(4);

static const u8 sHumReloadPaletteCycle[8] = { 0, 1, 2, 3, 4, 3, 2, 1 };

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
    work->tiles = AllocObjTiles(def->tileCount * 32, NULL);
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
    AnimInit(&work->anim, NULL, NULL);
    TaskPoolInit(&work->tasks, 3);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, actor);
    TaskCreate(&work->tasks, &gTaskDescBtlBadstatus, actor);
    work->state = 12;
    work->scaleX = 0x100;
    work->scaleY = 0x100;
    work->sub = NULL;
    work->sub2 = NULL;
    work->stockMoves = NULL;
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

    sub->tiles = AllocObjTiles(def->tileCount * 32, NULL);
    sub->palette2 = sub->palette = LoadObjPalette(def->palette, 32);
    sub->x = work->actor.x;
    sub->y = work->actor.y;
    sub->z = work->actor.z;
    sub->flags = 0;
    AnimInit(&sub->anim, NULL, NULL);
}

void HumSubReleaseGraphics(HumSub* sub) {
    if (sub != NULL) {
        ReleaseObjTiles(sub->tiles);
        ReleaseObjPalette(sub->palette);
    }
}

void HumReleaseResources(HumWork* work) {
    if (gBtlWork->actor2 == &work->actor) {
        gBtlWork->actor2 = NULL;
    }

    HumSubReleaseGraphics(work->sub);
    HumSubReleaseGraphics(work->sub2);
    gBtlWork->actor3 = NULL;
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

s32 HumUpdateReaction(HumWork* work) {
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

    GetEnemyTargetPosition(actor, &x, NULL, NULL);

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

        if (work->stateTimer > 23 && !BgFxIsActive()) {
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

        if (!FadeIsActive()) {
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

        if (!BgFxIsActive()) {
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

        if (!IsRikuReloadCardSelected()) {
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

        if (actor->collider.colliding && !(work->flags & HUM_FLAG_PASS_THROUGH) && !(actor->collider.other->flags & COLLIDER_FLAG_PASS_THROUGH)) {
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

void HumDrawSub(HumWork* work, HumSub* s) {
    s16 x;
    s16 y;
    BtlObj* c;
    u16 attr;
    ObjAffine* affine;
    u16 prio;
    s32 sx;
    s32 sy;

    if (s == NULL) {
        return;
    }

    if (s->flags & HUM_SUB_FLAG_HIDDEN) {
        return;
    }

    c = &work->actor;
    attr = GetBattleSpritePriorityFlags(s->y);

    if (c->flags & BTLOBJ_FLAG_FACING_LEFT) {
        sy = gBtlWork->scale;
        sx = sy;
    } else {
        sy = gBtlWork->scale;

        if (sy == 0x100) {
            sx = sy;
            attr |= 1;
        } else {
            sx = -sy;
        }
    }

    if (sy == 0x100 && sx == 0x100) {
        affine = NULL;
    } else if (sy <= 0xFF) {
        affine = AllocObjAffine(0, sx, sy, 0);
    } else {
        affine = AllocObjAffine(0, sx, sy, 1);
    }

    if (s->flags & HUM_SUB_FLAG_OWN_DEPTH) {
        prio = (-0x1004 - (s->y >> 8) * 4) | 3;
    } else if (s->flags & HUM_SUB_FLAG_IN_FRONT) {
        prio = ((-0x1004 - (c->y >> 8) * 4) | 3) - 1;
    } else {
        prio = ((-0x1004 - (c->y >> 8) * 4) | 3) + 1;
    }

    WorldToScreen(&x, &y, s->x, s->y, s->z);
    DrawSprite(x, y, s->gfx, s->tiles, s->palette2, affine, attr, prio);
}

void HumDraw(HumWork* work) {
    s16 x;
    s16 y;
    BtlObj* c = &work->actor;
    u16 attr;
    ObjAffine* affine;
    s32 sx;
    s32 sy;
    s32 g;
    s16 idx;

    if (work->flags & HUM_FLAG_BEHIND_BG_FX) {
        attr = 0x800;
    } else {
        attr = GetBattleSpritePriorityFlags(c->y);
    }

    WorldToScreen(&x, &y, c->x, c->y, c->z);

    if (work->scaleX == 0x100 && work->scaleY == 0x100) {
        if (c->flags & BTLOBJ_FLAG_FACING_LEFT) {
            sy = gBtlWork->scale;
            sx = sy;
        } else {
            sy = gBtlWork->scale;

            if (sy == 0x100) {
                sx = sy;
                attr |= 1;
            } else {
                sx = -sy;
            }
        }
    } else {
        if (c->flags & BTLOBJ_FLAG_FACING_LEFT) {
            sx = (gBtlWork->scale * work->scaleX >> 8);
            g = gBtlWork->scale;
            sy = g * work->scaleY >> 8;
        } else {
            sx = -(gBtlWork->scale * work->scaleX >> 8);
            g = gBtlWork->scale;
            sy = g * work->scaleY >> 8;
        }
    }

    if (sy == 0x100 && sx == 0x100) {
        affine = NULL;
    } else if (sy <= 0xFF) {
        affine = AllocObjAffine(0, sx, sy, 0);
    } else {
        affine = AllocObjAffine(0, sx, sy, 1);
    }

    if (work->state == 17) {
        idx = (work->stateTimer >> 2) % 8;

        if (work->stateTimer & 1) {
            work->flags |= HUM_FLAG_FLASH_PALETTE;
            LoadObjPaletteBank(work->palette->index, gUnk_08F6DA04 + 16 + sHumReloadPaletteCycle[idx] * 16);
        } else {
            work->flags &= ~HUM_FLAG_FLASH_PALETTE;
            LoadObjPaletteBank(work->palette->index, work->paletteData);
        }
    } else if (StepHitFlash(c)) {
        work->flags |= HUM_FLAG_FLASH_PALETTE;
        LoadObjPaletteBank(work->palette->index, gUnk_08F69BC4);
    } else if (work->flags & HUM_FLAG_FLASH_PALETTE) {
        work->flags &= ~HUM_FLAG_FLASH_PALETTE;
        LoadObjPaletteBank(work->palette->index, work->paletteData);
    }

    DrawSprite(x, y, work->gfx, work->tiles, work->palette, affine, attr, (-0x1004 - (c->y >> 8) * 4) | 3);
    HumDrawSub(work, work->sub);
    HumDrawSub(work, work->sub2);
    TaskPoolDraw(&work->tasks);
}

void HandleRikuAiCardInput() {
    BtlObj* c = gRikuBtlWork->actor;
    u8 keys;
    u16 t;

    if (gRikuBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
        return;
    }

    t = gRikuBtlWork->listSwitchTimer;

    if ((s16)t > 0) {
        gRikuBtlWork->listSwitchTimer = t - 1;

        if (gRikuBtlWork->listSwitchTimer == 0) {
            RequestSwitchRikuCardList();
        }

        return;
    }

    keys = gBtlWork->rikuKeys;
    gBtlWork->rikuKeys = 0;

    if (keys & RIKU_KEY_NEXT_CARD) {
        RequestRikuNextCard();
    }

    if (keys & RIKU_KEY_PREV_CARD) {
        RequestRikuPrevCard();
    }

    if (keys & RIKU_KEY_SWITCH_LIST) {
        RequestSwitchRikuCardList();
    }

    if (c->flags & BTLOBJ_FLAG_CARD_USE_BLOCKED) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_BUSY) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_CARD_BREAK) {
        return;
    }

    if (c->flags & BTLOBJ_FLAG_DAMAGE_PENDING) {
        return;
    }

    if (keys & RIKU_KEY_STOCK) {
        if (GetRikuStockCount() > 2) {
            RequestRikuStockUse();
        } else {
            RequestRikuCardStock();
        }
    }

    if (keys & RIKU_KEY_USE_CARD) {
        RequestRikuCardUse();

        if (GetRikuCardListIndex() == 3 && !IsRikuSelectionEmpty()) {
            gRikuBtlWork->listSwitchTimer = 15;
        }
    }
}

#ifdef VERSION_EU
void HandleRikuTutorialCardInput() {
    BtlObj* c = gRikuBtlWork->actor;
    u8 keys;
    keys = gBtlWork->rikuKeys;
    gBtlWork->rikuKeys = 0;

    if (c->flags & BTLOBJ_FLAG_CARD_USE_BLOCKED) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_BUSY) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_CARD_BREAK) {
        return;
    }

    if (c->flags & BTLOBJ_FLAG_DAMAGE_PENDING) {
        return;
    }

    if (keys & RIKU_KEY_USE_CARD) {
        RequestRikuCardUse();
    }
}
#endif

void HumFaceTarget(HumWork* work, u16 n) {
    s32 v;
    GetEnemyTargetPosition(&work->actor, &v, NULL, NULL);

    if (GetRandom() % n == 0) {
        if (work->actor.x > v) {
            work->actor.flags |= BTLOBJ_FLAG_FACING_LEFT;
        } else {
            work->actor.flags &= ~BTLOBJ_FLAG_FACING_LEFT;
        }
    }
}

u8 HumMoveToward(HumWork* work, s32 x, s32 y, s32 spd) {
    u8 ang = GetAngle(work->actor.x, work->actor.y, x, y);

    work->actor.x += gSineTable[ang] * spd >> 8;
    work->actor.y += -gSineTable[ang + 64] * spd >> 8;

    if (work->actor.x - x >= 0 ? work->actor.x - x > 0x1E00 : x - work->actor.x > 0x1E00) {
        return 0;
    }

    if (work->actor.y - y >= 0 ? work->actor.y - y > 0x1000 : y - work->actor.y > 0x1000) {
        return 0;
    }

    return 1;
}

u8 HumIsTargetInReach(HumWork* work, s16 a, u16 b, u16 r) {
    s32 v0;
    s32 v1;
    BtlObj* c = &work->actor;
    s32 d;
    s32 t;
    s32 bb;
    s32 rr;

    GetEnemyTargetPosition(c, &v0, &v1, NULL);
    rr = r << 8;
    d = c->y - v1;

    if (d >= 0 ? d > rr : v1 - c->y > rr) {
        return 0;
    }

    if (c->flags & BTLOBJ_FLAG_FACING_LEFT) {
        t = c->x - (a << 8);
        bb = b << 8;

        if (t - bb > v0) {
            return 0;
        }

        if (t + bb < v0) {
            return 0;
        }
    } else {
        t = c->x + (a << 8);
        bb = b << 8;

        if (t + bb < v0) {
            return 0;
        }

        if (t - bb > v0) {
            return 0;
        }
    }

    return 1;
}

u8 HumIsNearAreaEdge(HumWork* work, u16 b) {
    if (work->actor.x < (gBtlWork->xMin + b) << 8) {
        return 1;
    }

    if (work->actor.x > (gBtlWork->xMax - b) << 8) {
        return 1;
    }

    return 0;
}

u8 HumIsInPlayerReach(HumWork* work, s16 a, u16 b, u16 r) {
    s32 v0;
    s32 v1;
    BtlObj* c = &work->actor;
    BtlObj* o = gBtlWork->actor;
    s32 d;
    s32 t;
    s32 bb;
    s32 rr;

    GetEnemyTargetPosition(c, &v0, &v1, NULL);
    rr = r << 8;
    d = c->y - v1;

    if (d >= 0 ? d > rr : v1 - c->y > rr) {
        return 0;
    }

    if (o->flags & BTLOBJ_FLAG_FACING_LEFT) {
        t = v0 - (a << 8);
        bb = b << 8;

        if (t - bb > c->x) {
            return 0;
        }

        if (t + bb < c->x) {
            return 0;
        }
    } else {
        t = v0 + (a << 8);
        bb = b << 8;

        if (t + bb < c->x) {
            return 0;
        }

        if (t - bb > c->x) {
            return 0;
        }
    }

    return 1;
}

u8 HumChooseCardAction(HumWork* work, u16 interval, u16 offset, u16 width, u16 depth) {
    u32 value;
    u32 cards;
    u32 id;
    s32 count;
    s32 n;

    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) {
        return 0;
    }

    if ((s16)gRikuBtlWork->listSwitchTimer > 0) {
        return 0;
    }

    if ((u16)((u32)GetRandom() % interval) != 0) {
        return 0;
    }

    value = GetRikuSelectedCardValue();
    cards = GetRikuStockCount();
    id = GetRikuSelectedMove();
    count = GetRikuCardsLeft();

    switch (id) {
    case 47:
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
        n = count >> 1;

        if (n <= 0) {
            n = 1;
        }

        if (GetRandom() % n == 0) {
            gBtlWork->rikuKeys |= RIKU_KEY_USE_CARD;
        } else {
            gBtlWork->rikuKeys |= RIKU_KEY_NEXT_CARD;
        }

        return 0;
    }

    if (IsRikuReloadCardSelected()) {
        if (count > 1 && (u16)(GetRandom() % 20U) == 0) {
            gBtlWork->rikuKeys |= RIKU_KEY_NEXT_CARD;
        }

        return 0;
    }

    if (GetRikuCardListIndex() == 3) {
        if ((GetRandom() & 3) == 0) {
            if (count <= 0) {
                work->flags |= HUM_FLAG_ENEMY_CARDS_SPENT;
                gBtlWork->rikuKeys |= RIKU_KEY_SWITCH_LIST;
            } else {
                gBtlWork->rikuKeys |= RIKU_KEY_USE_CARD;

                if (count == 1) {
                    work->flags |= HUM_FLAG_ENEMY_CARDS_SPENT;
                }
            }
        } else if (count > 1) {
            gBtlWork->rikuKeys |= RIKU_KEY_NEXT_CARD;
        }

        return 0;
    }

    if (!(work->flags & HUM_FLAG_ENEMY_CARDS_SPENT) && gRikuBtlWork->hcEffect == 0
        && (u16)(GetRandom() % 60U) == 0) {
        gBtlWork->rikuKeys |= RIKU_KEY_SWITCH_LIST;
        return 0;
    }

    if (cards > 2) {
        if ((u16)(GetRandom() % 6U) == 0) {
            gBtlWork->rikuKeys |= RIKU_KEY_STOCK;
            return 1;
        }
    } else if (GetRandom() % 2 == 0) {
        if (count <= 1 && cards != 0) {
            gBtlWork->rikuKeys |= RIKU_KEY_STOCK;
            return 1;
        }

        // @bug unk_184 is NULL for humanoid bosses without a card table (NULL read).
        if (value == 0 || work->stockMoves[cards] != id) {
            gBtlWork->rikuKeys |= RIKU_KEY_NEXT_CARD;
        } else {
            gBtlWork->rikuKeys |= RIKU_KEY_STOCK;
        }

        return 0;
    }

    if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
        if (HumIsTargetInReach(work, offset, width, depth)) {
            if (GetActiveCardValue() <= value || value == 0) {
                gBtlWork->rikuKeys |= RIKU_KEY_USE_CARD;
            }
        } else if (GetActiveCardValue() == value) {
            gBtlWork->rikuKeys |= RIKU_KEY_USE_CARD;
        }
    } else if (HumIsTargetInReach(work, offset, width, depth)) {
        gBtlWork->rikuKeys |= RIKU_KEY_USE_CARD;
    }

    return 0;
}

s32 HumResolveCardMove(HumWork* work) {
    s32 buf[6];
    s32 id = ResolveActiveCardsMove(buf);

    if (id == 145) {
        if (!(gRikuBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE)) {
            gRikuBtlWork->flags |= BTL_FLAG_STOCK_SEQUENCE;
            gRikuBtlWork->stockMove = 0;
        }

        id = buf[gRikuBtlWork->stockMove];
        gRikuBtlWork->stockMove++;
    }

    work->stateTimer = 0;

    switch (id) {
    case 47:
        work->state = 18;
        work->itemIndex = 0;
        break;
    case 48:
        work->state = 18;
        work->itemIndex = 1;
        break;
    case 49:
        work->state = 18;
        work->itemIndex = 2;
        break;
    case 50:
        work->state = 18;
        work->itemIndex = 3;
        break;
    case 51:
        work->state = 18;
        work->itemIndex = 4;
        break;
    case 52:
        work->state = 18;
        work->itemIndex = 5;
        break;
    case 53:
        work->state = 18;
        work->itemIndex = 6;
        break;
    }

    return id;
}
