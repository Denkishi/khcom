/**
 * bos_ursula.c
 * Ursula Boss
 */

#include "bos4.h"
#include "sprites_bos4.h"
#include "gba/io_reg.h"
#include "prize_types.h"
#include "btl_api.h"
#include "fade.h"
#include "songs.h"
#include <string.h>
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_bg_types.h"
#include "battle_work.h"
#include "bos4_api.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "card_api.h"
#include "display.h"
#include "engine_math.h"
#include "listpool.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "registration_data.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "bos_ursula.h"
#include "sprite_palettes.h"
#include "default_bg_map.h"

static const EmyKind sBosUrsulaEmyKind = { 35, 0, 32, 24, 0, 0, 0 };

static const BattleBackgroundDef sBosUrsulaBattleBackgroundDef = {
    gBosUrsulaBgTiles, 0x7000, gBosUrsulaBgPalettes, 0xe0, { gBosUrsulaBgMap0, gBosUrsulaBgMap1, gBosUrsulaBgMap2, gBosUrsulaBgMap3 }
};

static const u16* sBosUrsulaMapBlocksLeft[12] = {
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gBosUrsulaLeftMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
};

static const u16* sBosUrsulaMapBlocksHurtLeft[12] = {
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gBosUrsulaHurtLeftMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
};

static const u16* sBosUrsulaMapBlocksRight[12] = {
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gBosUrsulaRightMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
};

static const u16* sBosUrsulaMapBlocksHurtRight[12] = {
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gBosUrsulaHurtRightMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
};

TaskDesc gTaskDescBosUrsula = {
    "task_bos_ursula",
    (TaskInitFunc)task_bos_ursula_0,
    (TaskUpdateFunc)task_bos_ursula_1,
    (TaskDrawFunc)task_bos_ursula_2,
    (TaskDestroyFunc)task_bos_ursula_3,
    sizeof(UrsulaWork),
};

static TaskDesc sTaskDescBosUrsulaMap = {
    "task_bos_ursula_map",
    (TaskInitFunc)task_bos_ursula_map_0,
    (TaskUpdateFunc)task_bos_ursula_map_1,
    NULL,
    (TaskDestroyFunc)task_bos_ursula_map_3,
    sizeof(UrsulaMapWork),
};

static TaskDesc sTaskDescBosUrsulaBorder = {
    "task_bos_ursula_border",
    (TaskInitFunc)task_bos_ursula_border_0,
    (TaskUpdateFunc)task_bos_ursula_border_1,
    (TaskDrawFunc)task_bos_ursula_border_2,
    (TaskDestroyFunc)task_bos_ursula_border_3,
    sizeof(UrsulaBorderWork),
};

static const EmyKind sBosUrsulaTakoEmyKind = { 35, 0, 48, 16, 24, 0, EMY_KIND_FLAG_NO_COLLIDER };

static TaskDesc sTaskDescBosUrsulaTako = {
    "task_bos_ursula_tako",
    (TaskInitFunc)task_bos_ursula_tako_0,
    (TaskUpdateFunc)task_bos_ursula_tako_1,
    (TaskDrawFunc)task_bos_ursula_tako_2,
    (TaskDestroyFunc)task_bos_ursula_tako_3,
    sizeof(UrsulaTakoWork),
};

static TaskDesc sTaskDescBosUrsulaBacktako = {
    "task_bos_ursula_backtako",
    (TaskInitFunc)task_bos_ursula_backtako_0,
    (TaskUpdateFunc)task_bos_ursula_backtako_1,
    (TaskDrawFunc)task_bos_ursula_backtako_2,
    (TaskDestroyFunc)task_bos_ursula_backtako_3,
    sizeof(UrsulaBacktakoWork),
};

static const BosMapanimeFrame sBosUrsulaMapanimeIdleFrames[6] = { { 60, 0 }, { 4, 1 }, { 6, 2 }, { 20, 0 }, { 4, 1 }, { 6, 2 } };

static const BosMapanimeFrame sBosUrsulaMapanimeWindupFrames[12] = { { 5, 0 }, { 5, 1 }, { 5, 2 }, { 5, 3 }, { 5, 2 }, { 5, 1 }, { 5, 2 }, { 5, 3 }, { 5, 2 }, { 5, 1 }, { 5, 2 }, { 5, 3 } };

static const BosMapanimeFrame sBosUrsulaMapanimeBubbleFrames[5] = { { 10, 0 }, { 10, 1 }, { 10, 2 }, { 10, 3 }, { 10, 4 } };

static const BosMapanimeFrame sBosUrsulaMapanimeChargeFrames[5] = { { 10, 0 }, { 10, 1 }, { 120, 2 }, { 10, 3 }, { 10, 4 } };

static const BosMapanimeFrame sBosUrsulaMapanimeRecoverFrames[1] = { { 0, 0 } };

static const BosMapanimeDef sBosUrsulaMapanimeIdle = { sBosUrsulaMapanimeIdleFrames, 6, gBosUrsulaMapanimeIdleTiles, 0x0C00, 0x0300, 0x0400, 0 };

static const BosMapanimeDef sBosUrsulaMapanimeWindup = { sBosUrsulaMapanimeWindupFrames, 12, gBosUrsulaMapanimeWindupTiles, 0x0C00, 0x0860, 0x0C00, 0 };

static const BosMapanimeDef sBosUrsulaMapanimeBubble = { sBosUrsulaMapanimeBubbleFrames, 5, gBosUrsulaMapanimeBubbleTiles, 0x0C00, 0x0860, 0x0C00, 0 };

static const BosMapanimeDef sBosUrsulaMapanimeCharge = { sBosUrsulaMapanimeChargeFrames, 5, gBosUrsulaMapanimeChargeTiles, 0x0C00, 0x0860, 0x0C00, 0 };

static const BosMapanimeDef sBosUrsulaMapanimeRecover = { sBosUrsulaMapanimeRecoverFrames, 1, gBosUrsulaMapanimeRecoverTiles, 0x0C00, 0x0860, 0x0C00, 0 };

static TaskDesc sTaskDescBosUrsulaMapanime = {
    "task_bos_ursula_mapanime",
    (TaskInitFunc)task_bos_ursula_mapanime_0,
    (TaskUpdateFunc)task_bos_ursula_mapanime_1,
    (TaskDrawFunc)task_bos_ursula_mapanime_2,
    (TaskDestroyFunc)task_bos_ursula_mapanime_3,
    sizeof(UrsulaMapanimeWork),
};

static UrsulaWork* sUrsulaWork;

static UrsulaMapanimeWork* sUrsulaMapanimeWork;

enum BosUrsulaState {
    BOS_URSULA_STATE_IDLE,
    BOS_URSULA_STATE_ATTACK,
    BOS_URSULA_STATE_CANCEL,
    BOS_URSULA_STATE_HURT,
    BOS_URSULA_STATE_DEFEATED,
    BOS_URSULA_STATE_MOVE
};

enum BosUrsulaAttack {
    BOS_URSULA_ATTACK_NONE,
    BOS_URSULA_ATTACK_BUBBLE,
    BOS_URSULA_ATTACK_CHARGE,
    BOS_URSULA_ATTACK_THUNDER,
    BOS_URSULA_ATTACK_BUSY
};

void BosUrsulaUpdateMapBlocks(UrsulaWork* work) {
    if (work->state >= BOS_URSULA_STATE_HURT && work->state <= BOS_URSULA_STATE_DEFEATED) {
        if (work->obj.x > gBtlWork->actor->x) {
            if (work->mapBlocks != sBosUrsulaMapBlocksHurtLeft) {
                work->mapBlocks = sBosUrsulaMapBlocksHurtLeft;
                SetBgMapBlocks(0, sBosUrsulaMapBlocksHurtLeft, 4, 3);
            } else {
                BosUrsulaStartAttack(BOS_URSULA_ATTACK_NONE);
            }
        } else {
            if (work->mapBlocks != sBosUrsulaMapBlocksHurtRight) {
                work->mapBlocks = sBosUrsulaMapBlocksHurtRight;
                SetBgMapBlocks(0, sBosUrsulaMapBlocksHurtRight, 4, 3);
            } else {
                BosUrsulaStartAttack(BOS_URSULA_ATTACK_NONE);
            }
        }
    } else if (BosUrsulaIsFacingLeft() != 0) {
        if (work->mapBlocks != sBosUrsulaMapBlocksLeft) {
            work->mapBlocks = sBosUrsulaMapBlocksLeft;
            SetBgMapBlocks(0, sBosUrsulaMapBlocksLeft, 4, 3);
        }
    } else {
        if (work->mapBlocks != sBosUrsulaMapBlocksRight) {
            work->mapBlocks = sBosUrsulaMapBlocksRight;
            SetBgMapBlocks(0, sBosUrsulaMapBlocksRight, 4, 3);
        }
    }
}

u8 BosUrsulaIsGuarded(UrsulaWork* work) {
    if (work->gimmickTimer == 0 && !BosUrsulaTakoIsBusy(work->tako->work) && !BosUrsulaTakoIsBusy(work->tako2->work)) {
        return 1;
    }

    return 0;
}

void task_bos_ursula_0(UrsulaWork* work) {
    u8 v;

    sUrsulaWork = work;
    gBosUrsulaActive = 1;
    TaskCreate(&gBtlWork->taskPools[1], &sTaskDescBosUrsulaMap, (void*)&sBosUrsulaBattleBackgroundDef);
    TaskCreate(&gBtlWork->taskPools[0], &sTaskDescBosUrsulaBorder, NULL);
    work->state = BOS_URSULA_STATE_IDLE;
    work->timer = 0;
    work->mapBlocks = NULL;
    work->takoRecoverPending = 0;
    work->bobTimer = 0;
    work->bobTarget = 0;
    work->bobZ = 0;
    work->gimmickTimer = 0;
    SetBattleBounds(0, 0x200, 0x1A8, 0x1E0);
    SetBattleActorPosition(0x10000, 0x1A800, 0);
    gBtlWork->bossPriorityOffset = 0xFF00;
    gBosUrsulaBaseZ = -0x5000;
    InitEnemyBtlObj(&work->obj, &sBosUrsulaEmyKind, 0x10000, 0x19800, -0x5000);
    work->obj.groundZ = 0;
    work->obj.flags |= BTLOBJ_FLAG_FACING_LEFT;
    SetBtlObjUnhittable(&work->obj, 1);
    BosUrsulaUpdateMapBlocks(work);
    RedrawBgMapAt(0, (gBtlWork->viewX - (work->obj.x - 0x12000)) >> 8,
        (gBtlWork->viewY - (work->obj.y + work->obj.z - 0x12000)) >> 8);
    SetBtlPaletteFadeExcluded(0, 1);
    SetBtlPaletteFadeExcluded(1, 1);
    gBtlWork->bossX = work->obj.x;
    gBtlWork->bossY = work->obj.y;
    gBtlWork->bossZ = work->obj.z;
    TaskPoolInit(&work->tasks, 5);
    v = 1;
    work->tako = TaskCreate(&work->tasks, &sTaskDescBosUrsulaTako, &v);
    v = 0;
    work->tako2 = TaskCreate(&work->tasks, &sTaskDescBosUrsulaTako, &v);
    TaskCreate(&work->tasks, &sTaskDescBosUrsulaMapanime, NULL);
    v = 1;
    TaskCreate(&work->tasks, &sTaskDescBosUrsulaBacktako, &v);
    work->gimmickDelay = 0;
}

void BosUrsulaUpdateBob(UrsulaWork* work) {
    BtlObj* p = &work->obj;

    if ((s16)work->bobTimer == 0) {
        work->bobTimer = 32;

        if (work->bobTarget == 0) {
            work->bobTarget = -0x400;
        } else {
            work->bobTarget = 0;
        }
    }

    ApproachValue(&work->bobZ, work->bobTarget, work->bobTimer);
    p->z = gBosUrsulaBaseZ + work->bobZ;
    work->bobTimer--;
}

u8 BosUrsulaMoveForward(UrsulaWork* work) {
    BtlObj* p = &work->obj;

    BosUrsulaUpdateBob(work);

    if (BosUrsulaIsFacingLeft() != 0) {
        p->x -= 0x100;

        if (p->x <= -0x9800) {
            p->x = -0x9800;
            return 0;
        }
    } else {
        p->x += 0x100;

        if (p->x >= 0x28000) {
            p->x = 0x28000;
            return 0;
        }
    }

    return 1;
}

s32 BosUrsulaChooseAttackPhase0(UrsulaWork* work) {
    BtlObj* p = gBtlWork->actor;

    if (p->x < work->obj.x - 0x5000 || work->obj.x + 0x5000 < p->x) {
        return BOS_URSULA_ATTACK_BUBBLE;
    }

    return BOS_URSULA_ATTACK_THUNDER;
}

s32 BosUrsulaChooseAttackPhase1(UrsulaWork* work) {
    if (work->obj.x - 0x3800 < gBtlWork->actor->x && gBtlWork->actor->x < work->obj.x + 0x3800) {
        return BOS_URSULA_ATTACK_THUNDER;
    }

    if (work->obj.x - 0x6800 < gBtlWork->actor->x && gBtlWork->actor->x < work->obj.x + 0x6800) {
        return BOS_URSULA_ATTACK_CHARGE;
    }

    return BOS_URSULA_ATTACK_BUBBLE;
}

s32 BosUrsulaChooseAttackPhase2(UrsulaWork* work) {
    if (gBtlWork->actor->z <= -0x5000) {
        return BOS_URSULA_ATTACK_THUNDER;
    } else {
        if (work->obj.x - 0x3800 < gBtlWork->actor->x && gBtlWork->actor->x < work->obj.x + 0x3800) {
            if ((u16)(GetRandom() % 100) < 50) {
                return BOS_URSULA_ATTACK_THUNDER;
            }

            return BOS_URSULA_ATTACK_BUBBLE;
        }
    }

    if (work->obj.x - 0x8000 < gBtlWork->actor->x && gBtlWork->actor->x < work->obj.x + 0x8000) {
        return BOS_URSULA_ATTACK_CHARGE;
    }

    return BOS_URSULA_ATTACK_BUBBLE;
}

s32 BosUrsulaChooseAttack(UrsulaWork* work) {
    switch (BosUrsulaGetHpPhase()) {
    case BOS_URSULA_HP_PHASE_HIGH:
        return BosUrsulaChooseAttackPhase0(work);
    case BOS_URSULA_HP_PHASE_MID:
        return BosUrsulaChooseAttackPhase1(work);
    case BOS_URSULA_HP_PHASE_LOW:
    default:
        return BosUrsulaChooseAttackPhase2(work);
    }
}

void BosUrsulaRecoverPendingTakos(UrsulaWork* work) {
    if (work->takoRecoverPending) {
        BosUrsulaTakoEndDown(work->tako->work);
        BosUrsulaTakoEndDown(work->tako2->work);
        work->takoRecoverPending = 0;
    }
}

void BosUrsulaUpdateTakoRecovery(UrsulaWork* work) {
    if (work->gimmickTimer == 0 && !BosUrsulaTakoIsStoodOn(work->tako->work) && !BosUrsulaTakoIsStoodOn(work->tako2->work)) {
        BosUrsulaRecoverPendingTakos(work);
        work->takoRecoverPending = 1;
    } else {
        work->takoRecoverPending = 0;
    }
}

u16 BosUrsulaGetCardInterval() {
    switch (BosUrsulaGetHpPhase()) {
    case BOS_URSULA_HP_PHASE_HIGH:
        return 150;
    case BOS_URSULA_HP_PHASE_MID:
        return 120;
    case BOS_URSULA_HP_PHASE_LOW:
    default:
        return 100;
    }
}

u8 task_bos_ursula_1(UrsulaWork* work) {
    BtlObj* p = &work->obj;
    PrizeCardArg pos;
    s32 x;
    u16 chance;

    switch (UpdateBtlObjReaction(p)) {
    case BTL_REACTION_CARD_ACTION:
        work->state = BOS_URSULA_STATE_ATTACK;
        work->timer = 0;
        break;
    case BTL_REACTION_HURT:
    case BTL_REACTION_STUNNED:
    case BTL_REACTION_GRAVITY:
        BosUrsulaUpdateTakoRecovery(work);
        work->state = BOS_URSULA_STATE_HURT;
        work->timer = 0;
        break;
    case BTL_REACTION_DEFEATED:
    case BTL_REACTION_GRAVITY_DEFEATED:
        work->state = BOS_URSULA_STATE_DEFEATED;
        work->timer = 0;
        break;
    case BTL_REACTION_CARD_BROKEN:
        work->state = BOS_URSULA_STATE_CANCEL;
        break;
    }

    if (ConsumeGimmickFlag(0)) {
        if (work->gimmickTimer == 0) {
            work->gimmickCameraX = gBtlWork->viewX;
            work->gimmickViewY = gBtlWork->viewY;
            work->gimmickCameraY = gBtlWork->viewY;
            work->sinkSteps = 40;
            work->riseSteps = 40;
            work->unk_15C = 20;
            work->sinkZ = 0;
            work->gimmickDelay = 9;
        }

        work->gimmickTimer = 300;

        if (work->state == BOS_URSULA_STATE_ATTACK) {
            work->state = BOS_URSULA_STATE_CANCEL;
        }
    }

    if (work->gimmickTimer == 0) {
        gBosUrsulaBaseZ = -0x5000;
    } else if (work->gimmickDelay == 0) {
        if (work->sinkSteps != 0) {
            ApproachValue((s32*)&work->sinkZ, 0x3800, work->sinkSteps);
            ApproachValue((s32*)&work->gimmickCameraY, work->gimmickViewY + 0x3800, work->sinkSteps >> 1);
            BtlMapSetCameraTarget(work->gimmickCameraX, work->gimmickCameraY);
            work->sinkSteps--;
        } else {
            if (work->gimmickTimer == 300) {
                BtlMapStartShake();
            }

            work->gimmickTimer--;

            if (work->gimmickTimer == 0 && work->state == BOS_URSULA_STATE_DEFEATED) {
                work->gimmickTimer = 1;
            }

            if (work->gimmickTimer > 280) {
                BtlMapSetCameraTarget(work->gimmickCameraX, work->gimmickCameraY);
            }
        }

        if (work->gimmickTimer == 0 && work->riseSteps != 0) {
            work->gimmickTimer++;
            ApproachValue((s32*)&work->sinkZ, 0, work->riseSteps);
            work->riseSteps--;
        }

        gBosUrsulaBaseZ = work->sinkZ - 0x5000;
    } else {
        work->gimmickDelay--;
    }

    if (BosUrsulaIsGuarded(work)) {
        SetBtlObjUnhittable(&work->obj, 1);
    } else {
        SetBtlObjUnhittable(&work->obj, 0);
    }

    switch (work->state) {
    case BOS_URSULA_STATE_ATTACK:
        if (work->timer == 0) {
            BosUrsulaStartAttack(BosUrsulaChooseAttack(work));
            work->timer = 1;
        } else {
            if (BosUrsulaIsCharging()) {
                BosUrsulaMoveForward(work);
            }

            if (!BosUrsulaIsAttacking()) {
                ClearBtlObjActionFlags(p);
                work->state = BOS_URSULA_STATE_IDLE;
            }
        }

        break;
    case BOS_URSULA_STATE_CANCEL:
        ClearBtlObjActionFlags(p);
        work->state = BOS_URSULA_STATE_IDLE;
        BosUrsulaStartAttack(BOS_URSULA_ATTACK_NONE);
        break;
    case BOS_URSULA_STATE_HURT:
        if (work->timer > 20) {
            ClearBtlObjActionFlags(p);

            if (BosUrsulaGetHpPhase() == BOS_URSULA_HP_PHASE_MID && !BosUrsulaIsGimmickActive()) {
                work->state = BOS_URSULA_STATE_MOVE;
            } else {
                work->state = BOS_URSULA_STATE_IDLE;
            }

            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case BOS_URSULA_STATE_DEFEATED:
        if (work->timer == 0) {
            BeginBossDefeat(p);
            BosUrsulaUpdateMapBlocks(work);
            work->timer++;
        } else if (work->timer == 1) {
            work->timer++;
        } else if (work->timer == 2) {
            if (BosUrsulaIsFacingLeft()) {
                x = p->x + 0x1400;
            } else {
                x = p->x - 0x1C00;
            }

            BgFxStartBossDeath(x, p->y + p->z + 0x1C00);
            FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
            work->timer++;
        } else if (work->timer == 3) {
            if (!FadeIsActive()) {
                work->timer++;
            }
        } else if (work->timer < 124) {
            work->timer++;

            if (work->timer == 124) {
                BgFxStartBossDeathFlash();
            }
        } else if (!BgFxIsActive()) {
            pos.x = p->x;

            if (pos.x < 0x2000) {
                pos.x = 0x2000;
            }

            if (pos.x > 0x1E000) {
                pos.x = 0x1E000;
            }

            pos.y = 0x1A800;
            pos.z = p->z;
            CreateBossPrizeCardTask(&gBtlWork->taskPools[0], &pos);
            EndBossDefeat();
            DropBossPrizes(p);
            DisableBg(0);
            gBosUrsulaActive = 0;
            return 0;
        }

        break;
    case BOS_URSULA_STATE_IDLE:
        if (work->obj.x > gBtlWork->actor->x) {
            p->flags |= BTLOBJ_FLAG_FACING_LEFT;
        } else {
            p->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
        }

        if (!BosUrsulaIsGimmickActive()) {
            if (BosUrsulaIsGuarded(work)) {
                chance = BosUrsulaGetCardInterval();

                if ((u16)(GetRandom() % chance) == 0) {
                    RequestEnemyCardUse(&work->obj);
                }
            }

            if ((u32)p->x > 0x20000) {
                work->state = BOS_URSULA_STATE_MOVE;
            }

            if (BosUrsulaGetHpPhase() == BOS_URSULA_HP_PHASE_LOW) {
                if (((p->x - gBtlWork->actor->x) >= 0 ? p->x - gBtlWork->actor->x : -(p->x - gBtlWork->actor->x)) > 0x6800) {
                    work->state = BOS_URSULA_STATE_MOVE;
                }
            }
        }

        BosUrsulaUpdateBob(work);
        break;
    case BOS_URSULA_STATE_MOVE:
        if (BosUrsulaIsGimmickActive()) {
            BosUrsulaUpdateBob(work);
        } else {
            if (!BosUrsulaMoveForward(work)) {
                p->flags ^= BTLOBJ_FLAG_FACING_LEFT;
            }

            if (BosUrsulaGetHpPhase() == BOS_URSULA_HP_PHASE_LOW && p->x > 0x6800 && p->x < 0x19800) {
                if (((p->x - gBtlWork->actor->x) >= 0 ? p->x - gBtlWork->actor->x : -(p->x - gBtlWork->actor->x)) < 0x6800 && BosUrsulaIsGuarded(work)) {
                    RequestEnemyCardUse(&work->obj);
                    work->state = BOS_URSULA_STATE_IDLE;
                }
            }

            if ((!(p->flags & BTLOBJ_FLAG_FACING_LEFT) && p->x == 0x6800) || ((p->flags & BTLOBJ_FLAG_FACING_LEFT) && p->x == 0x19800)) {
                work->state = BOS_URSULA_STATE_IDLE;
            }
        }

        break;
    }

    if (work->state != BOS_URSULA_STATE_DEFEATED) {
        BosUrsulaUpdateMapBlocks(work);
    }

    if (BosUrsulaIsGuarded(work)) {
        ColliderSetPosition(&p->collider, p->x, p->y, p->z);
    } else {
        ColliderSetPosition(&p->collider, p->x, p->y + 0x1000, p->z - 0x1000);
    }

    gBtlWork->bossX = p->x;
    gBtlWork->bossY = p->y;
    gBtlWork->bossZ = p->z;
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_bos_ursula_2(UrsulaWork* work) {
    BtlObj* p = &work->obj;
    s32 d = 0;

    if (BosUrsulaIsFacingLeft() != 0 && work->mapBlocks == sBosUrsulaMapBlocksHurtRight) {
        d = -0x1000;
    } else if (BosUrsulaIsFacingLeft() == 0 && work->mapBlocks == sBosUrsulaMapBlocksHurtLeft) {
        d = 0x1000;
    }

    ScrollBgMapTo(0, (gBtlWork->viewX - (p->x - 0x12000) + d) >> 8,
        (gBtlWork->viewY - (p->y + p->z - 0x12000)) >> 8);
    TaskPoolDraw(&work->tasks);
}

void task_bos_ursula_3(UrsulaWork* work) {
    ReleaseEnemyBtlObj(&work->obj);
    TaskPoolDestroy(&work->tasks);
    gDispCnt &= ~DISPCNT_WIN0_ON;
}

u8 BosUrsulaIsFacingLeft() {
    return sUrsulaWork->obj.flags & BTLOBJ_FLAG_FACING_LEFT;
}

u8 BosUrsulaIsGimmickActive() {
    if (sUrsulaWork->gimmickTimer == 0) {
        return 0;
    }

    return 1;
}

u8 BosUrsulaObjectsGone() {
    BtlObj* p;
    u8 r = 1;

    for (p = ListPoolFirst(&gBtlWork->pool); p != NULL; p = ListPoolNext(&p->node)) {
        if (p->kind == 0x23) {
            r = 0;
            break;
        }
    }

    return r;
}

u8 BosUrsulaIsGimmickStarting() {
    if (BosUrsulaObjectsGone() || !BosUrsulaIsGimmickActive() || sUrsulaWork->gimmickDelay == 0) {
        return 0;
    }

    return 1;
}

u8 BosUrsulaIsGimmickInProgress() {
    if (BosUrsulaIsGimmickActive() && (sUrsulaWork->sinkSteps != 0 || sUrsulaWork->riseSteps != 0 || sUrsulaWork->unk_15C != 0)) {
        return 1;
    }

    return 0;
}

u32 BosUrsulaGetHpPhase() {
    UrsulaWork* work = sUrsulaWork;

    if (work->obj.hp > (s16)(work->obj.maxHp / 3) * 2) {
        return BOS_URSULA_HP_PHASE_HIGH;
    }

    if (work->obj.hp > (s16)(work->obj.maxHp / 3)) {
        return BOS_URSULA_HP_PHASE_MID;
    }

    return BOS_URSULA_HP_PHASE_LOW;
}

u8 BosUrsulaIsDefeated() {
    if (sUrsulaWork->state == BOS_URSULA_STATE_DEFEATED) {
        return 1;
    }

    return 0;
}

void task_bos_ursula_map_0(UrsulaMapWork* work, BattleBackgroundDef* arg) {
    SetupBg(0, 0, 0x1A, 0);
    SetupBg(1, 0, 0x18, 0);
    SetBgPriority(1, 3);
    SetBgPriority(0, 2);
    LoadBgTiles(1, arg->tiles, arg->tilesSize);
    LoadBgPalette(1, arg->palette, arg->paletteSize);
    SetBgMapBlocks(1, arg->map, 2, 2);
    gBtlWork->scale = 0x100;
    gBtlWork->zoomScale = 0x100;
    gBtlWork->x = 0x10000;
    gBtlWork->y = 0x17100;
    gBtlWork->viewX = 0x10000;
    gBtlWork->viewY = 0x17100;
    gBtlWork->x2 = 0x10000;
    gBtlWork->y2 = 0x17100;
    gBtlWork->zoomX = 0x10000;
    gBtlWork->zoomY = 0x17100;
    gBtlWork->zoomSteps = 0x0F;
    gBtlWork->rotation = 0;
    BtlMapResetShake();
    ScrollBgMapTo(1, gBtlWork->viewX >> 8, gBtlWork->viewY >> 8);
    gDispCnt |= DISPCNT_WIN0_ON;
    gWin0H = WIN_RANGE(0, 240);
    gWin0V = WIN_RANGE(80, 160);
    gWinIn = (WININ_WIN0_BG1 | WININ_WIN0_BG2 | WININ_WIN0_BG3 | WININ_WIN0_OBJ | WININ_WIN0_CLR);
    gWinOut = (WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_BG2 | WINOUT_WIN01_BG3 | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
    work->viewYMax = 0x1E000;
    work->viewYMaxTarget = 0x1E000;
    work->viewYMaxSteps = 0;
}

u8 task_bos_ursula_map_1(UrsulaMapWork* work) {
    s32 a;
    s32 b;
    u8 v;

    if (BosUrsulaIsGimmickStarting()) {
        return 1;
    }

    BtlMapUpdateShake();
    a = (gBtlWork->x2 - gBtlWork->x) >> 3;
    b = (gBtlWork->y2 - gBtlWork->y) >> 3;

    if (a > 0x500) {
        a = 0x500;
    } else if (a < -0x500) {
        a = -0x500;
    }

    if (b > 0x500) {
        b = 0x500;
    } else if (b < -0x500) {
        b = -0x500;
    }

    gBtlWork->x += a;
    gBtlWork->y += b;
    gBtlWork->viewX = gBtlWork->x;
    gBtlWork->viewY = gBtlWork->y;

    if (gBtlWork->viewX - 0x7800 < gBtlWork->xMin * 256) {
        gBtlWork->viewX = (gBtlWork->xMin + 0x78) << 8;
    } else if (gBtlWork->viewX + 0x7800 > gBtlWork->xMax * 256) {
        gBtlWork->viewX = (gBtlWork->xMax - 0x78) << 8;
    }

    if (BosUrsulaIsGimmickInProgress() && work->viewYMaxTarget == 0x1E000) {
        work->viewYMaxTarget = 0x22000;
        work->viewYMaxSteps = 20;
    } else if (!BosUrsulaIsGimmickInProgress() && work->viewYMaxTarget == 0x22000) {
        work->viewYMaxTarget = 0x1E000;
        work->viewYMaxSteps = 20;
    }

    if (work->viewYMaxSteps != 0) {
        ApproachValue(&work->viewYMax, work->viewYMaxTarget, work->viewYMaxSteps);
        work->viewYMaxSteps--;
    }

    if (gBtlWork->viewY - 0x5000 < 0x8800) {
        gBtlWork->viewY = 0xD800;
    } else if (gBtlWork->viewY + 0x5000 > work->viewYMax) {
        gBtlWork->viewY = work->viewYMax - 0x5000;
    }

    gBtlWork->viewY += BtlMapGetShake();
    ScrollBgMapTo(1, (gBtlWork->viewX >> 8) - 0x78, (gBtlWork->viewY >> 8) - 0x50);
    v = -0x18 - (gBtlWork->viewY >> 8);

    if (v > 0xA0 || !gBosUrsulaActive) {
        gDispCnt &= ~DISPCNT_WIN0_ON;
    } else {
        gDispCnt |= DISPCNT_WIN0_ON;
        gWin0V = (v << 8) | 0xA0;
    }

    return 1;
}

void task_bos_ursula_map_3() {
}

void task_bos_ursula_border_0(UrsulaBorderWork* work) {
    work->tiles = LoadObjTiles(gBosUrsulaBorderTiles, 0x800);
    work->palette = LoadObjPalette(gBosUrsulaBorderPalette, 0x20);
    SetBtlPaletteFadeExcluded(work->palette->index + 16, 0);
}

s32 task_bos_ursula_border_1() {
    return 1;
}

void task_bos_ursula_border_2(UrsulaBorderWork* work) {
    s16 a;
    s16 b;
    s16 c;
    s16 d;

    GetBattleSpritePriorityFlags(0x19800);
    WorldToScreen(&a, &b, 0x8000, 0x19800, -0x800);
    WorldToScreen(&c, &d, 0x18000, 0x19800, -0x800);
    DrawSprite(a, b, gBosUrsulaBorderFrame0, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), 0xFB00);
    DrawSprite(c, d, gUnk_0979D8B8, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), 0xFB00);
}

void task_bos_ursula_border_3(UrsulaBorderWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void BosUrsulaTakoGetPosition(s32* x, s32* y, s32* z, UrsulaTakoWork* work) {
    s32* p;
    s32 t;

    *x = gBtlWork->bossX + work->offsetX;

    if (work->isLeft != 0) {
        if (BosUrsulaIsFacingLeft() != 0) {
            *x += -0x2200;
        } else {
            *x += -0x3600;
        }
    } else {
        if (BosUrsulaIsFacingLeft() != 0) {
            *x += 0x3600;
        } else {
            *x += 0x2200;
        }
    }

    *y = gBtlWork->bossY;
    p = &gBtlWork->bossZ;
    t = work->offsetZ + 0x5000;
    *z = *p + t;
}

s32 BosUrsulaGetTakoPlatformRadius(u8 isLeft) {
    if (isLeft == BosUrsulaIsFacingLeft()) {
        return 12;
    }

    return 6;
}

enum BosUrsulaTakoState {
    BOS_URSULA_TAKO_STATE_IDLE,
    BOS_URSULA_TAKO_STATE_HURT,
    BOS_URSULA_TAKO_STATE_COLLAPSE,
    BOS_URSULA_TAKO_STATE_DOWN,
    BOS_URSULA_TAKO_STATE_SUBMERGED,
    BOS_URSULA_TAKO_STATE_RESURFACE,
    BOS_URSULA_TAKO_STATE_RESURFACE_WAIT,
    BOS_URSULA_TAKO_STATE_ATTACK
};

void task_bos_ursula_tako_0(UrsulaTakoWork* work, u8* arg) {
    s32 x;
    s32 y;
    s32 z;

    work->isLeft = *arg;
    work->offsetX = 0;
    work->offsetZ = 0;
    BosUrsulaTakoGetPosition(&x, &y, &z, work);
    InitEnemyBtlObj(&work->obj, &sBosUrsulaTakoEmyKind, x, y, z);
    ColliderInit(&work->collider2, 7, 0x28, 0x20);

    if (work->isLeft != 0) {
        work->animBase = 0xFFFC;
        work->obj.flags |= BTLOBJ_FLAG_FACING_LEFT;
        work->collider2OffsetX = -0x2800;
    } else {
        work->animBase = 0;
        work->collider2OffsetX = 0x2800;
    }

    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gBosUrsulaTakoFrames, 6), gBosUrsulaTakoTiles);
    work->palette = LoadObjPalette(gBosUrsulaTakoPalette, 32);
    work->palette2 = LoadObjPalette(gHitFlashPalette, 32);
    AnimInit(&work->anim, gBosUrsulaTakoAnims, gBosUrsulaTakoFrames);
    AnimStart(&work->anim, work->animBase + 4, ANIM_FLAG_LOOP);
    work->state = BOS_URSULA_TAKO_STATE_IDLE;
    ColliderInit(&work->collider, 7, BosUrsulaGetTakoPlatformRadius(work->isLeft), 1);
    ColliderSetPosition(&work->collider, work->obj.x, work->obj.y + 0x1000, -0x3800);
    SetEnemyHpFromStats(&work->obj, 35, 51);
}

u8 task_bos_ursula_tako_1(UrsulaTakoWork* work) {
    BtlObj* p = &work->obj;
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dz;

    if (BosUrsulaIsGimmickActive()) {
        SetBtlObjUnhittable(p, 1);
    } else if (work->state <= BOS_URSULA_TAKO_STATE_HURT) {
        SetBtlObjUnhittable(p, 0);
    }

    if (BosUrsulaIsDefeated()) {
        return 1;
    }

    switch (UpdateBtlObjReaction(p)) {
    case BTL_REACTION_CARD_ACTION:
        work->state = BOS_URSULA_TAKO_STATE_ATTACK;
        work->timer = 0;
        RequestBossCardRandom();
        break;
    case BTL_REACTION_HURT:
    case BTL_REACTION_STUNNED:
    case BTL_REACTION_GRAVITY:
        work->state = BOS_URSULA_TAKO_STATE_HURT;
        work->timer = 0;
        break;
    case BTL_REACTION_DEFEATED:
    case BTL_REACTION_GRAVITY_DEFEATED:
        work->state = BOS_URSULA_TAKO_STATE_COLLAPSE;
        work->timer = 0;
        break;
    case BTL_REACTION_CARD_BROKEN:
        ClearBtlObjActionFlags(p);
        work->state = BOS_URSULA_TAKO_STATE_IDLE;
        RequestBossCardRandom();
        break;
    }

    switch (work->state) {
    case BOS_URSULA_TAKO_STATE_IDLE:
        AnimChange(&work->anim, work->animBase + 4, ANIM_FLAG_LOOP);
        break;
    case BOS_URSULA_TAKO_STATE_HURT:
        if (work->timer == 0) {
            AnimChange(&work->anim, work->animBase + 7, 0);
        }

        work->timer++;

        if (AnimIsFinished(&work->anim)) {
            ClearBtlObjActionFlags(p);
            work->state = BOS_URSULA_TAKO_STATE_IDLE;
            work->timer = 0;
        }

        break;
    case BOS_URSULA_TAKO_STATE_COLLAPSE:
        if (AnimGetId(&work->anim) == (s16)work->animBase + 4) {
            if (AnimGetFrame(&work->anim) == 0 && AnimIsFrameEnding(&work->anim)) {
                AnimStart(&work->anim, work->animBase + 5, ANIM_FLAG_LOOP);
                SetBtlObjUnhittable(p, 1);

                if ((u16)(GetRandom() % 100) <= 19) {
                    DropGimmickCard(0, p->x, p->y, p->z);
                }
            }
        } else if (AnimGetId(&work->anim) == (s16)work->animBase + 5) {
            if (AnimIsFinished(&work->anim)) {
                ClearBtlObjActionFlags(p);
                work->state = BOS_URSULA_TAKO_STATE_DOWN;
                work->timer = 0;
            }
        } else {
            AnimStart(&work->anim, work->animBase + 4, ANIM_FLAG_LOOP);
        }

        break;
    case BOS_URSULA_TAKO_STATE_DOWN:
        if (work->timer > 180) {
            work->state = BOS_URSULA_TAKO_STATE_SUBMERGED;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case BOS_URSULA_TAKO_STATE_SUBMERGED:
        if (work->timer > 180) {
            AnimStart(&work->anim, work->animBase + 6, 0);
            work->state = BOS_URSULA_TAKO_STATE_RESURFACE;
            work->offsetZ = 0x800;

            if (work->isLeft) {
                work->offsetX = -0x2AA;
            } else {
                work->offsetX = 0x2AA;
            }

            work->timer = 30;
        } else {
            work->timer++;
        }

        break;
    case BOS_URSULA_TAKO_STATE_RESURFACE:
        AnimReset(&work->anim);

        if (work->timer == 5) {
            ReleaseEnemyBtlObj(&work->obj);
            BosUrsulaTakoGetPosition(&x, &y, &z, work);
            InitEnemyBtlObj(&work->obj, &sBosUrsulaTakoEmyKind, x, y, z);
            work->obj.flags |= 0x400;
            SetEnemyHpFromStats(&work->obj, 35, 25);
        }

        if (work->timer == 0) {
            if (!BosUrsulaIsGimmickActive()) {
                RequestEnemyCardUse(&work->obj);
            }

            work->state = BOS_URSULA_TAKO_STATE_RESURFACE_WAIT;
            work->timer = 0;
        } else {
            ApproachValue(&work->offsetZ, 0, work->timer);
            ApproachValue(&work->offsetX, 0, work->timer);
            work->timer--;
        }

        break;
    case BOS_URSULA_TAKO_STATE_RESURFACE_WAIT:
        if (work->timer > 30) {
            work->state = BOS_URSULA_TAKO_STATE_IDLE;
        } else {
            work->timer++;
        }

        break;
    case BOS_URSULA_TAKO_STATE_ATTACK:
        AnimChange(&work->anim, work->animBase + 6, 0);

        if (AnimIsFinished(&work->anim) || BosUrsulaIsGimmickActive()) {
            work->state = BOS_URSULA_TAKO_STATE_IDLE;
            AnimStart(&work->anim, work->animBase + 4, ANIM_FLAG_LOOP);
            ClearBtlObjActionFlags(p);
        } else {
            if (AnimGetFrame(&work->anim) == 1) {
                dx = 0x800;

                if (work->isLeft) {
                    dx = -0x800;
                }

                dz = -0x6000;
            } else if (AnimGetFrame(&work->anim) == 0) {
                dx = -0x1800;

                if (work->isLeft) {
                    dx = 0x1800;
                }

                dz = -0x3800;
            } else {
                dx = 0x1800;

                if (work->isLeft) {
                    dx = -0x1800;
                }

                dz = -0x3800;
            }

            if (ApplyAttackBox(241, p->x + dx, p->y + 0x1000, p->z + dz, 24, 16, 8) == 1) {
                m4aSongNumStart(SONG_BTL_HANE_HIT);
            }
        }

        break;
    }

    AnimUpdate(&work->anim);
    BosUrsulaTakoGetPosition(&p->x, &p->y, &p->z, work);

    if (work->state - 3 <= 4 && gBtlWork->actor->z < -0x5000 && !BosUrsulaIsGimmickActive()) {
        ColliderSetDisabled(&work->collider, 0);
        ColliderSetPosition(&work->collider, work->obj.x, work->obj.y + 0x1000, -0x5000);
    } else {
        ColliderSetDisabled(&work->collider, 1);
    }

    if (work->state == BOS_URSULA_TAKO_STATE_DOWN && gBtlWork->actor->z <= -0x2000 && gBtlWork->actor->z > -0x3000) {
        ColliderSetDisabled(&work->collider2, 0);
        ColliderSetPosition(&work->collider2, work->obj.x + work->collider2OffsetX, work->obj.y + 0x1000, 0);
    } else {
        ColliderSetDisabled(&work->collider2, 1);
    }

    return 1;
}

void task_bos_ursula_tako_2(UrsulaTakoWork* work) {
    BtlObj* p = &work->obj;
    void* pal;
    s16 x;
    s16 y;

    if (work->state != BOS_URSULA_TAKO_STATE_SUBMERGED && !BosUrsulaIsGimmickActive()) {
        pal = StepHitFlash(p) ? work->palette2 : work->palette;
        WorldToScreen(&x, &y, p->x, p->y, p->z);
        DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, pal, NULL, SPRITE_PRIORITY(2), 0xFC00);
    }
}

void task_bos_ursula_tako_3(UrsulaTakoWork* work) {
    ReleaseEnemyBtlObj(&work->obj);
    ColliderUnregister(&work->collider2);
    ColliderUnregister(&work->collider);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
}

u8 BosUrsulaTakoIsBusy(UrsulaTakoWork* work) {
    if (work->state <= BOS_URSULA_TAKO_STATE_HURT) {
        return 0;
    }

    return 1;
}

void BosUrsulaTakoEndDown(UrsulaTakoWork* work) {
    if (work->state >= BOS_URSULA_TAKO_STATE_DOWN && work->state <= BOS_URSULA_TAKO_STATE_SUBMERGED) {
        work->state = BOS_URSULA_TAKO_STATE_SUBMERGED;
        work->timer = 180;
    }
}

u8 BosUrsulaTakoIsStoodOn(UrsulaTakoWork* work) {
    if (work->collider.standFlags & COLLIDER_STAND_STOOD_ON) {
        return 1;
    }

    return 0;
}

void BosUrsulaBacktakoGetPosition(s32* x, s32* y, s32* z, UrsulaBacktakoWork* work) {
    s32* p;
    s32 t;

    *x = gBtlWork->bossX + work->offsetX;

    if (work->isLeft != 0) {
        if (BosUrsulaIsFacingLeft() != 0) {
            *x += -0x4A00;
        } else {
            *x += -0x5E00;
        }
    } else {
        if (BosUrsulaIsFacingLeft() != 0) {
            *x += 0x5E00;
        } else {
            *x += 0x4A00;
        }
    }

    *y = gBtlWork->bossY + 0x800;
    p = &gBtlWork->bossZ;
    t = work->offsetZ + 0x5000;
    *z = *p + t;
}

void task_bos_ursula_backtako_0(UrsulaBacktakoWork* work, u8* arg) {
    work->isLeft = *arg;
    work->offsetX = 0;
    work->offsetZ = 0;
    BosUrsulaBacktakoGetPosition(&work->x, &work->y, &work->z, work);
    work->isLeft = work->isLeft == 0 ? 1 : 0;
    BosUrsulaBacktakoGetPosition(&work->x2, &work->y2, &work->z2, work);
    work->isLeft = work->isLeft == 0 ? 1 : 0;

    if (work->isLeft != 0) {
        work->animBase = 0xFFFC;
    } else {
        work->animBase = 0;
    }

    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gBosUrsulaTakoFrames, 8), gBosUrsulaTakoTiles);
    work->palette = LoadObjPalette(gBosUrsulaTakoPalette, 32);
    AnimInit(&work->anim, gBosUrsulaTakoAnims, gBosUrsulaTakoFrames);
    AnimStart(&work->anim, work->animBase + 4, ANIM_FLAG_LOOP);
    AnimSetFrame(&work->anim, GetRandom() % work->anim.frameCount + 1);
}

u8 task_bos_ursula_backtako_1(UrsulaBacktakoWork* work) {
    if (!BosUrsulaIsDefeated()) {
        BosUrsulaBacktakoGetPosition(&work->x, &work->y, &work->z, work);
        work->isLeft = work->isLeft == 0 ? 1 : 0;
        BosUrsulaBacktakoGetPosition(&work->x2, &work->y2, &work->z2, work);
        work->isLeft = work->isLeft == 0 ? 1 : 0;
        AnimUpdate(&work->anim);
    }

    return 1;
}

void task_bos_ursula_backtako_2(UrsulaBacktakoWork* work) {
    s16 x;
    s16 y;
    u8 f = BosUrsulaIsGimmickActive();

    if (f) {
        return;
    }

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL, SPRITE_PRIORITY(3),
        0xFE00);
    WorldToScreen(&x, &y, work->x2, work->y2, work->z2);
    DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL, SPRITE_PRIORITY(3) | SPRITE_FLAG_HFLIP,
        0xFE00);
}

void task_bos_ursula_backtako_3(UrsulaBacktakoWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_bos_ursula_mapanime_0(UrsulaMapanimeWork* work) {
    sUrsulaMapanimeWork = work;
    TaskPoolInit(&work->tasks, 1);
    work->task = NULL;
    work->attack = BOS_URSULA_ATTACK_BUSY;
    BosUrsulaStartAttack(BOS_URSULA_ATTACK_NONE);
}

u8 task_bos_ursula_mapanime_1(UrsulaMapanimeWork* work) {
    s32 d;

    BosMapanimeUpdate(&work->anim, work->anim.def, 0);

    if (BosMapanimeIsAtEnd(&work->anim)) {
        if (work->anim.def == &sBosUrsulaMapanimeWindup) {
            if (work->attack == BOS_URSULA_ATTACK_BUBBLE) {
                BosMapanimeInit(&work->anim, &sBosUrsulaMapanimeBubble);
                work->attack = BOS_URSULA_ATTACK_BUSY;
            } else if (work->attack == BOS_URSULA_ATTACK_CHARGE) {
                BosMapanimeInit(&work->anim, &sBosUrsulaMapanimeCharge);
                work->attack = BOS_URSULA_ATTACK_BUSY;
            }
        } else if (work->anim.def == &sBosUrsulaMapanimeBubble
                || work->anim.def == &sBosUrsulaMapanimeCharge) {
            BosMapanimeInit(&work->anim, &sBosUrsulaMapanimeRecover);
            work->attack = BOS_URSULA_ATTACK_BUSY;
        } else if (work->anim.def == &sBosUrsulaMapanimeRecover) {
            BosMapanimeInit(&work->anim, &sBosUrsulaMapanimeIdle);
            work->attack = BOS_URSULA_ATTACK_NONE;
        }
    }

    if (work->anim.def == &sBosUrsulaMapanimeCharge && BosMapanimeGetFrameIndex(&work->anim) == 2) {
        if (!work->attackSpawned) {
            work->attackSpawned = 1;
            BgFxStartUrsulaBeam(gBtlWork->bossX, gBtlWork->bossY + 0xC00,
                gBtlWork->bossZ, BosUrsulaIsFacingLeft(), 0x266, 0x78);
        } else {
            BgFxSetPosition(gBtlWork->bossX, gBtlWork->bossY + 0xC00,
                gBtlWork->bossZ);
        }

        d = BosUrsulaIsFacingLeft() != 0 ? -0x5000 : 0x5000;
        ApplyAttackBox(0xF3, gBtlWork->bossX + d, 0x1C400, 0, 0x18, 0x38, 0x50);
    }

    if (work->anim.def == &sBosUrsulaMapanimeBubble && BosMapanimeGetFrameIndex(&work->anim) == 2
            && !work->attackSpawned) {
        work->attackSpawned = 1;
        work->task = TaskCreate(&work->tasks, &gTaskDescBosUrsulaBubble, NULL);
    }

    TaskPoolUpdate(&work->tasks);

    return 1;
}

void task_bos_ursula_mapanime_2(UrsulaMapanimeWork* work) {
    TaskPoolDraw(&work->tasks);
}

void task_bos_ursula_mapanime_3(UrsulaMapanimeWork* work) {
    TaskPoolDestroy(&work->tasks);
}

void BosUrsulaStartAttack(s32 attack) {
    if (IsTaskActive(sUrsulaMapanimeWork->task)) {
        if (strcmp(GetTaskName(sUrsulaMapanimeWork->task), "task_bos_ursula_bubble") == 0) {
            BosUrsulaPopBubbles(sUrsulaMapanimeWork->task->work);
        } else {
            TaskKill(&sUrsulaMapanimeWork->tasks, sUrsulaMapanimeWork->task);
        }
    }

    if (attack == BOS_URSULA_ATTACK_THUNDER) {
        sUrsulaMapanimeWork->task = TaskCreate(&sUrsulaMapanimeWork->tasks, &gTaskDescBosUrsulaThunder, NULL);
    } else if (sUrsulaMapanimeWork->attack != attack) {
        sUrsulaMapanimeWork->attack = attack;

        if (attack == BOS_URSULA_ATTACK_NONE) {
            BosMapanimeInit(&sUrsulaMapanimeWork->anim, &sBosUrsulaMapanimeRecover);
            sUrsulaMapanimeWork->attackSpawned = 1;
        } else {
            BosMapanimeInit(&sUrsulaMapanimeWork->anim, &sBosUrsulaMapanimeWindup);
            sUrsulaMapanimeWork->attackSpawned = 0;
            m4aSongNumStart(SONG_VO_UR_ATTACK00);
        }
    }
}

u8 BosUrsulaIsAttacking() {
    if (sUrsulaMapanimeWork->anim.def == &sBosUrsulaMapanimeBubble || sUrsulaMapanimeWork->anim.def == &sBosUrsulaMapanimeCharge || sUrsulaMapanimeWork->anim.def == &sBosUrsulaMapanimeWindup) {
        return 1;
    }

    return IsTaskActive(sUrsulaMapanimeWork->task);
}

u8 BosUrsulaIsCharging() {
    if (sUrsulaMapanimeWork->anim.def == &sBosUrsulaMapanimeCharge && BosMapanimeGetFrameIndex(&sUrsulaMapanimeWork->anim) == 2) {
        return 1;
    }

    return 0;
}
