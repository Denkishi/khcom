/**
 * bos_ursula_bubble.c
 * Ursula Boss Bubbles and Thunder
 */

#include "bos4.h"
#include "sprites_bos4.h"
#include "songs.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "bos4_api.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "display.h"
#include "engine_math.h"
#include "m4a_song.h"
#include "obj_api.h"
#include "poo_api.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"
#include "bos_ursula.h"
#include "sprite_palettes.h"

#ifdef VERSION_EU
static UrsulaBubbleWork* sUrsulaBubbleWork;
#endif

TaskDesc gTaskDescBosUrsulaBubble = {
    "task_bos_ursula_bubble",
    (TaskInitFunc)task_bos_ursula_bubble_0,
    (TaskUpdateFunc)task_bos_ursula_bubble_1,
    (TaskDrawFunc)task_bos_ursula_bubble_2,
    (TaskDestroyFunc)task_bos_ursula_bubble_3,
    sizeof(UrsulaBubbleWork),
};

static const EmyKind sBosUrsulaBubbleSingleEmyKind = { 35, 0, 1, 1, 0, 0, 0 };

static TaskDesc sTaskDescBosUrsulaBubbleSingle = {
    "task_bos_ursula_bubble_single",
    (TaskInitFunc)task_bos_ursula_bubble_single_0,
    (TaskUpdateFunc)task_bos_ursula_bubble_single_1,
    (TaskDrawFunc)task_bos_ursula_bubble_single_2,
    (TaskDestroyFunc)task_bos_ursula_bubble_single_3,
    sizeof(UrsulaBubbleSingleWork),
};

TaskDesc gTaskDescBosUrsulaThunder = {
    "task_bos_ursula_thunder",
    (TaskInitFunc)task_bos_ursula_thunder_0,
    (TaskUpdateFunc)task_bos_ursula_thunder_1,
    (TaskDrawFunc)task_bos_ursula_thunder_2,
    (TaskDestroyFunc)task_bos_ursula_thunder_3,
    sizeof(UrsulaThunderWork),
};

u16 BosUrsulaSpawnThreeBubbles(UrsulaBubbleWork* work) {
    s8 v = 0x60;

    if (BosUrsulaIsFacingLeft() != 0) {
        v = -v;
    }

    work->bubbles[0] = TaskCreate(&work->tasks, &sTaskDescBosUrsulaBubbleSingle, &v);
    v = 0x20;

    if (BosUrsulaIsFacingLeft() != 0) {
        v = -v;
    }

    work->bubbles[1] = TaskCreate(&work->tasks, &sTaskDescBosUrsulaBubbleSingle, &v);
    v = 0x40;

    if (BosUrsulaIsFacingLeft() != 0) {
        v = -v;
    }

    work->bubbles[2] = TaskCreate(&work->tasks, &sTaskDescBosUrsulaBubbleSingle, &v);

    return 3;
}

u16 BosUrsulaSpawnSixBubbles(UrsulaBubbleWork* work) {
    s8 v;
    s32 i;
    u8 a = 14;

    for (i = 0; i <= 5; i++) {
        v = a;

        if (BosUrsulaIsFacingLeft() != 0) {
            v = -v;
        }

        work->bubbles[i] = TaskCreate(&work->tasks, &sTaskDescBosUrsulaBubbleSingle, &v);
        a += 20;
    }

    return i;
}

u16 BosUrsulaSpawnTenBubbles(UrsulaBubbleWork* work) {
    s8 v;
    s32 i;
    u8 a = 240;

    for (i = 0; i <= 9; i++) {
        v = a;

        if (BosUrsulaIsFacingLeft() != 0) {
            v = -v;
        }

        work->bubbles[i] = TaskCreate(&work->tasks, &sTaskDescBosUrsulaBubbleSingle, &v);
        a += 16;
    }

    return i;
}

void task_bos_ursula_bubble_0(UrsulaBubbleWork* work) {
#ifdef VERSION_EU
    sUrsulaBubbleWork = work;
    AnimInit(&work->anim, gBosUrsulaBubbleAnims, gBosUrsulaBubbleFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    gBtlWork->tiles3 = AllocObjTiles(GetMaxSpriteTileBytes(gBosUrsulaBubbleFrames, 6), gBosUrsulaBubbleTiles);
#endif
    TaskPoolInit(&work->tasks, 10);
    work->bubbleCount = 0;

    switch (BosUrsulaGetHpPhase()) {
    case BOS_URSULA_HP_PHASE_LOW:
        work->bubbleCount = BosUrsulaSpawnTenBubbles(work);
        break;
    case BOS_URSULA_HP_PHASE_MID:
        work->bubbleCount += BosUrsulaSpawnSixBubbles(work);
        break;
    case BOS_URSULA_HP_PHASE_HIGH:
    default:
        work->bubbleCount += BosUrsulaSpawnThreeBubbles(work);
        break;
    }

    m4aSongNumStart(SONG_BTL_UR_BUBBLE);
}

u8 task_bos_ursula_bubble_1(UrsulaBubbleWork* work) {
    s32 i;

    TaskPoolUpdate(&work->tasks);

#ifdef VERSION_EU
    AnimUpdate(&work->anim);
#endif

    for (i = 0; i < work->bubbleCount; i++) {
        if (IsTaskActive(work->bubbles[i])) {
            break;
        }
    }

    if (i == work->bubbleCount) {
        return 0;
    }

    return 1;
}

void task_bos_ursula_bubble_2(UrsulaBubbleWork* work) {
    TaskPoolDraw(&work->tasks);
}

void task_bos_ursula_bubble_3(UrsulaBubbleWork* work) {
    TaskPoolDestroy(&work->tasks);
#ifdef VERSION_EU
    ReleaseObjTiles(gBtlWork->tiles3);
#endif
}

void BosUrsulaPopBubbles(UrsulaBubbleWork* work) {
    s32 i;

    for (i = 0; i < work->bubbleCount; i++) {
        if (IsTaskActive(work->bubbles[i])) {
            BosUrsulaBubblePop(work->bubbles[i]->work);
        }
    }
}

#ifdef VERSION_EU
void BosUrsulaBubbleAnimChange(u16 animId, u16 flags) {
    AnimChange(&sUrsulaBubbleWork->anim, animId, flags);
}

u16 BosUrsulaBubbleAnimGetId() {
    return AnimGetId(&sUrsulaBubbleWork->anim);
}

u8 BosUrsulaBubbleAnimIsFinished() {
    return AnimIsFinished(&sUrsulaBubbleWork->anim);
}

void* BosUrsulaBubbleAnimGetGfx() {
    return AnimGetGfx(&sUrsulaBubbleWork->anim);
}
#endif

enum BosUrsulaBubbleSingleState {
    BOS_URSULA_BUBBLE_SINGLE_STATE_LAUNCH,
    BOS_URSULA_BUBBLE_SINGLE_STATE_HOMING,
    BOS_URSULA_BUBBLE_SINGLE_STATE_POP
};

void task_bos_ursula_bubble_single_0(UrsulaBubbleSingleWork* work, u8* arg) {
    work->angle = *arg;
    work->speed = 0x333;
    InitEnemyBtlObj(&work->obj, &sBosUrsulaBubbleSingleEmyKind, gBtlWork->bossX,
        gBtlWork->bossY + 0x1000, gBtlWork->bossZ);
    SetBtlObjUnhittable(&work->obj, 1);
#ifdef VERSION_EU
    work->tiles = gBtlWork->tiles3;
#else
    work->tiles = LoadObjTiles(gBosUrsulaBubbleTiles, 0xA80);
#endif
    work->palette = LoadObjPalette(gBosUrsulaTakoPalette, 32);
    work->palette2 = LoadObjPalette(gHitFlashPalette, 32);
#ifdef VERSION_EU
    BosUrsulaBubbleAnimChange(0, 1);
#else
    AnimInit(&work->anim, gBosUrsulaBubbleAnims, gBosUrsulaBubbleFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
#endif
    work->state = BOS_URSULA_BUBBLE_SINGLE_STATE_LAUNCH;
    work->timer = 0x3C;
}

u8 task_bos_ursula_bubble_single_1(UrsulaBubbleSingleWork* work) {
    BtlObj* p = &work->obj;

    work->speed -= 12;

    if (work->speed < 0x166) {
        work->speed = 0x166;
    }

    if (work->state == BOS_URSULA_BUBBLE_SINGLE_STATE_LAUNCH) {
        p->x += gSineTable[(u8)work->angle] * work->speed >> 8;
        p->z += -gSineTable[(u8)work->angle + 0x40] * work->speed >> 8;
        work->timer--;

        if (p->z >= 0) {
            p->z = 0;
            work->timer = 0;
        }

        if (work->timer == 0) {
            work->timer = 180;
            work->state = BOS_URSULA_BUBBLE_SINGLE_STATE_HOMING;
        }
    }

    if (work->state == BOS_URSULA_BUBBLE_SINGLE_STATE_HOMING && work->timer != 0) {
        work->targetAngle = GetAngle(p->x, p->z,
            gBtlWork->actor->x, gBtlWork->actor->z);
        ApproachAngle(&work->angle, work->targetAngle, 4);
        p->x += gSineTable[(u8)work->angle] * work->speed >> 8;
        p->z += -gSineTable[(u8)work->angle + 0x40] * work->speed >> 8;

        if (work->timer <= 169) {
            ApproachValue(&p->y, gBtlWork->actor->y, 30);
        }

        if ((u32)p->x > 0x20800 || p->y > 0x20800) {
            return 0;
        }

        work->timer--;

        if (work->timer == 0) {
#ifdef VERSION_EU
            BosUrsulaBubbleAnimChange(1, 0);
#else
            AnimStart(&work->anim, 1, 0);
#endif
            SetBtlObjUnhittable(&work->obj, 1);
        }
    }

#ifdef VERSION_EU
    if (BosUrsulaBubbleAnimGetId() == 0
#else
    if (AnimGetId(&work->anim) == 0
#endif
            && ApplyAttackBox(0xF2, p->x, p->y, p->z, 1, 1, 1) == 1) {
        m4aSongNumStart(SONG_EF_UR_BUBBHIT);

        return 0;
    }

#ifdef VERSION_EU
    if (BosUrsulaBubbleAnimGetId() == 1 && BosUrsulaBubbleAnimIsFinished()) {
        return 0;
    }

#else
    if (AnimGetId(&work->anim) == 1 && AnimIsFinished(&work->anim)) {
        return 0;
    }

    AnimUpdate(&work->anim);
#endif
    ColliderSetPosition(&p->collider, p->x, p->y, p->z);

    return 1;
}

void task_bos_ursula_bubble_single_2(UrsulaBubbleSingleWork* work) {
    BtlObj* p = &work->obj;
    void* pal;
    u16 v;
    s16 x;
    s16 y;

    v = GetBattleSpritePriorityFlags(p->y);
    pal = StepHitFlash(p) ? work->palette2 : work->palette;
    WorldToScreen(&x, &y, p->x, p->y, p->z);
#ifdef VERSION_EU
    DrawSprite(x, y, BosUrsulaBubbleAnimGetGfx(), work->tiles, pal, NULL, v, -0x1004 - (p->y >> 8) * 4);
#else
    DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, pal, NULL, v, -0x1004 - (p->y >> 8) * 4);
#endif
}

void task_bos_ursula_bubble_single_3(UrsulaBubbleSingleWork* work) {
    ReleaseEnemyBtlObj(&work->obj);
#ifndef VERSION_EU
    ReleaseObjTiles(work->tiles);
#endif
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
}

void BosUrsulaBubblePop(UrsulaBubbleSingleWork* work) {
#ifdef VERSION_EU
    if (BosUrsulaBubbleAnimGetId() == 0) {
#else
    if (AnimGetId(&work->anim) == 0) {
#endif
        work->timer = 0;
#ifdef VERSION_EU
        BosUrsulaBubbleAnimChange(1, 0);
#else
        AnimStart(&work->anim, 1, 0);
#endif
        SetBtlObjUnhittable(&work->obj, 1);
        work->state = BOS_URSULA_BUBBLE_SINGLE_STATE_POP;
    }
}

void task_bos_ursula_thunder_0(UrsulaThunderWork* work) {
    BtlObj* p = gBtlWork->actor;

    work->x = p->x;
    work->y = p->y;
    work->z = p->z - 0x6000;
    BgFxStartUrsulaThunder(work->x, work->y, work->z);
    work->strikeStarted = 0;
}

u8 task_bos_ursula_thunder_1(UrsulaThunderWork* work) {
    if (!BgFxIsActive()) {
        if (work->strikeStarted) {
            return 0;
        }

        BgFxStartThunderStrike(work->x, work->y, 0, 244);
        work->strikeStarted = 1;
    }

    return 1;
}

void task_bos_ursula_thunder_2() {
}

void task_bos_ursula_thunder_3() {
}

void BosMapanimeInit(BosMapanimeState* anim, const BosMapanimeDef* def) {
    anim->timer = 0;
    anim->frameIndex = 0;
    anim->uploadPending = 1;
    anim->def = def;
}

u8 BosMapanimeUpdate(BosMapanimeState* anim, const BosMapanimeDef* def, u8 defer) {
    if (!anim->uploadPending) {
        anim->timer++;

        if (anim->timer > def->frames[anim->frameIndex].duration) {
            anim->timer = 0;
            anim->frameIndex++;

            if (anim->frameIndex >= def->frameCount) {
                anim->frameIndex = 0;
            }
        }
    }

    if (!defer) {
        if (anim->timer == 0 || anim->uploadPending) {
            RequestDma3Copy((u8*)def->tiles + def->frameSize * def->frames[anim->frameIndex].frame,
                (u8*)GetBgCharBase(def->bg) + def->destOffset, def->copySize);
            anim->uploadPending = 0;
        }
    } else if (anim->timer == 0) {
        anim->uploadPending = 1;
    }

    return defer;
}

u8 BosMapanimeIsAtEnd(BosMapanimeState* anim) {
    const BosMapanimeDef* q = anim->def;

    if (anim->timer + 1 > q->frames[anim->frameIndex].duration && anim->frameIndex + 1 >= q->frameCount) {
        return 1;
    }

    return 0;
}

u16 BosMapanimeGetFrameIndex(BosMapanimeState* anim) {
    return anim->frameIndex;
}

void ResetPooState() {
    InitPooState();
}

void SavePooState(void* state) {
    GetPooState(state);
}

void LoadPooState(const void* state) {
    SetPooState(state);
}
