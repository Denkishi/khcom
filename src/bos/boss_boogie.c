#include "boss_boogie.h"
#include "bos4_api.h"
#include "registration_data.h"
#include "card_api.h"
#include "engine_math.h"
#include "fade.h"
#include "btl_effect.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "battle_work.h"
#include "battle_bg_types.h"
#include "prize_types.h"
#include "boss_map_block_assets.h"
#include "copyright_screens.h"
#include "sprites_evt.h"
#include "sprites_title.h"
#include "songs.h"
#include "anim.h"
#include "battle_actor_types.h"
#include "listpool.h"
#include "m4a_song.h"
#include "obj.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"
#include "bos4.h"
#include "btl.h"
#include <stddef.h>

static BoogieWork* sBoogieWork;

#if defined(VERSION_US)
static const StatusAnimDef sBosBoogieAnimDefs[9] = {
    { gUnkUs_09EF66C4, gUnkUs_09EF66A8, gUnk_0977A53C, 0, 0 },
    { gUnkUs_09EF66E8, gUnkUs_09EF66C8, gUnk_0977F7B4, 0, 0 },
    { gUnkUs_09EF6710, gUnkUs_09EF66EC, gUnk_097856FA, 0, 0 },
    { gUnkUs_09EF6710, gUnkUs_09EF66EC, gUnk_097856FA, 1, 0 },
    { gUnk_09EF672C, gUnk_09EF6718, gUnk_0978A4E8, 0, 0 },
    { gUnkUs_09EF6750, gUnkUs_09EF6738, gUnk_0978DF7A, 0, 0 },
    { gUnkUs_09EF676C, gUnkUs_09EF6754, gUnk_097920CA, 0, 0 },
    { gUnkUs_09EF676C, gUnkUs_09EF6754, gUnk_097920CA, 1, 0 },
    { gUnk_09EF672C, gUnk_09EF6718, gUnk_0978A4E8, 2, 0 },
};
#elif defined(VERSION_JP)
static const StatusAnimDef sBosBoogieAnimDefs[9] = {
    { gUnkJp_09ECDAB0, gUnkJp_09ECDA94, gUnk_0977A53C, 0, 0 },
    { gUnkJp_09ECDAD4, gUnkJp_09ECDAB4, gUnk_0977F7B4, 0, 0 },
    { gUnkJp_09ECDAFC, gUnkJp_09ECDAD8, gUnk_097856FA, 0, 0 },
    { gUnkJp_09ECDAFC, gUnkJp_09ECDAD8, gUnk_097856FA, 1, 0 },
    { gUnk_09EF672C, gUnk_09EF6718, gUnk_0978A4E8, 0, 0 },
    { gUnkJp_09ECDB3C, gUnkJp_09ECDB24, gUnk_0978DF7A, 0, 0 },
    { gUnkJp_09ECDB58, gUnkJp_09ECDB40, gUnk_097920CA, 0, 0 },
    { gUnkJp_09ECDB58, gUnkJp_09ECDB40, gUnk_097920CA, 1, 0 },
    { gUnk_09EF672C, gUnk_09EF6718, gUnk_0978A4E8, 2, 0 },
};
#elif defined(VERSION_EU)
static const StatusAnimDef sBosBoogieAnimDefs[9] = {
    { gUnkEu_09F81CAC, gUnkEu_09F81C90, gUnkEu_09756750, 0, 0 },
    { gUnkEu_09F81CD0, gUnkEu_09F81CB0, gUnkEu_0975B9C8, 0, 0 },
    { gUnkEu_09F81CF8, gUnkEu_09F81CD4, gUnkEu_0976190E, 0, 0 },
    { gUnkEu_09F81CF8, gUnkEu_09F81CD4, gUnkEu_0976190E, 1, 0 },
    { gUnk_09EF672C, gUnk_09EF6718, gUnk_0978A4E8, 0, 0 },
    { gUnkEu_09F81D38, gUnkEu_09F81D20, gUnkEu_0976A18E, 0, 0 },
    { gUnkEu_09F81D54, gUnkEu_09F81D3C, gUnkEu_0976E2DE, 0, 0 },
    { gUnkEu_09F81D54, gUnkEu_09F81D3C, gUnkEu_0976E2DE, 1, 0 },
    { gUnk_09EF672C, gUnk_09EF6718, gUnk_0978A4E8, 2, 0 },
};
#endif

#if defined(VERSION_US)
static const StatusObjDef sBosBoogieSpriteDefs[6] = {
    { gUnkUs_09EF66A8, 7, 0 },
    { gUnkUs_09EF66C8, 8, 0 },
    { gUnkUs_09EF66EC, 9, 0 },
    { gUnk_09EF6718, 5, 0 },
    { gUnkUs_09EF6738, 6, 0 },
    { gUnkUs_09EF6754, 6, 0 },
};
#elif defined(VERSION_JP)
static const StatusObjDef sBosBoogieSpriteDefs[6] = {
    { gUnkJp_09ECDA94, 7, 0 },
    { gUnkJp_09ECDAB4, 8, 0 },
    { gUnkJp_09ECDAD8, 9, 0 },
    { gUnk_09EF6718, 5, 0 },
    { gUnkJp_09ECDB24, 6, 0 },
    { gUnkJp_09ECDB40, 6, 0 },
};
#elif defined(VERSION_EU)
static const StatusObjDef sBosBoogieSpriteDefs[6] = {
    { gUnkEu_09F81C90, 7, 0 },
    { gUnkEu_09F81CB0, 8, 0 },
    { gUnkEu_09F81CD4, 9, 0 },
    { gUnk_09EF6718, 5, 0 },
    { gUnkEu_09F81D20, 6, 0 },
    { gUnkEu_09F81D3C, 6, 0 },
};
#endif

static const EmyKind sBosBoogieEmyKind = { 39, 0, 68, 16, 32, 0, EMY_KIND_FLAG_LARGE_BODY };

#if defined(VERSION_US)
static const BattleBackgroundDef sBosBoogieBattleBackgroundDef = {
    gUnk_097E05B8 + 0x4FC0, 0x7F00, { 0, 0 }, gUnk_0984AE38, 0x140, { 0, 0 },
    { gBossMapBlockUs_08125E24, gUnk_09841F98 + 0x800, gBossMapBlockUs_08125E24, gUnk_09841F98 + 0x400 },
};
#elif defined(VERSION_JP)
static const BattleBackgroundDef sBosBoogieBattleBackgroundDef = {
    gUnk_097E05B8 + 0x4FC0, 0x7F00, { 0, 0 }, gUnkJp_097FFB0C, 0x140, { 0, 0 },
    { gBossMapBlockJp_08125EA0, gUnk_09841F98 + 0x800, gBossMapBlockJp_08125EA0, gUnk_09841F98 + 0x400 },
};
#elif defined(VERSION_EU)
static const BattleBackgroundDef sBosBoogieBattleBackgroundDef = {
    gUnk_097E05B8 + 0x4FC0, 0x7F00, { 0, 0 }, gUnkEu_0981F4E0, 0x140, { 0, 0 },
    { gBossMapBlockEu_08124944, gUnk_09841F98 + 0x800, gBossMapBlockEu_08124944, gUnk_09841F98 + 0x400 },
};
#endif

void BosBoogieApplyDiceFace(BoogieWork* work) {
    if (gBosBoogieDiceBreakCount <= 2) {
        gBosBoogieAttackHit = 0;
        gBosBoogieTaskKnockedDown = 0;

        if (gBosBoogieDiceFace == 0) {
            work->state = 8;
            work->task = TaskCreate(&work->tasks, &gTaskDescBosBoogieDisk, &work->actor);
        } else if (gBosBoogieDiceFace == 1) {
            work->state = 6;
            work->timer = 0;
            SpawnEnemy(18, 0xA000, 0x24000, 0);
            SpawnEnemy(18, 0x15000, 0x24000, 0);
        } else if (gBosBoogieDiceFace == 2) {
            work->state = 6;
            work->timer = 0;
            SpawnEnemy(17, 0xA000, 0x24000, 0);
            SpawnEnemy(17, 0x15000, 0x24000, 0);
        } else if (gBosBoogieDiceFace == 3) {
            work->state = 8;
            work->task = TaskCreate(&work->tasks, &gTaskDescBosBoogieKnifereader, NULL);
        } else if (gBosBoogieDiceFace == 4) {
            work->state = 6;
            work->timer = 0;
            SpawnEnemy(15, 0xA000, 0x24000, 0);
            SpawnEnemy(15, 0x15000, 0x24000, 0);
        } else {
            work->state = 8;
            work->task = TaskCreate(&work->tasks, &gTaskDescBosBoogieKaihuku, work);
        }
    }
}

void SetBoogieAnimation(BoogieWork* work, s32 a, u16 b) {
    if (work->animationIndex != a) {
        work->animationIndex = a;
        AnimChangeWithTables(&work->anim, sBosBoogieAnimDefs[a].animId, b, sBosBoogieAnimDefs[a].anims, sBosBoogieAnimDefs[a].gfxTable);
        SetObjTileSource(work->tiles, sBosBoogieAnimDefs[a].tiles);
    }
}

u8 ClampBoogiePosition(s32* a, s32* b) {
    u8 r;

    r = 0;

    if (*a < 0xA000) {
        *a = 0xA000;
        r = 1;
    }

    if (*a > 0x15000) {
        *a = 0x15000;
        r = 1;
    }

    if (*b < 0x22800) {
        *b = 0x22800;
        r = 1;
    }

    if (*b > 0x22800) {
        *b = 0x22800;
        r = 1;
    }

    return r;
}

void task_bos_boogie_0(BoogieWork* work) {
    u8 i;
    u16 sz;
    u16 t;

    sBoogieWork = work;
    TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosBoogieMap, (void*)&sBosBoogieBattleBackgroundDef);
    work->state = 0;
    work->timer = 0;
    gBosBoogieDiceFaceReady = 0;
    gBosBoogieGimmickCardDropped = 0;
    gBosBoogieSakuOpenTime = 0;
    work->cardRequested = 0;
    gBosBoogieActor = &work->actor;
    gBosBoogieDiceBreakCount = 0;
    SetBattleBounds(128, 368, 576, 632);
    InitEnemyBtlObj(&work->actor, &sBosBoogieEmyKind, 0x15000, 0x22800, -0x2000);
    work->actor.groundZ = -0x2000;
    work->actor.flags |= BTLOBJ_FLAG_FACING_LEFT;
    SetBtlObjUnhittable(&work->actor, 1);
    work->vx = 0;
    work->vy = 0;
    work->vz = 0;
    work->palette = LoadObjPalette(gBoss02objPalette, 0x20);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 0x20);
    sz = 0;

    for (i = 0; i <= 5; i++) {
        t = GetMaxSpriteTileBytes(sBosBoogieSpriteDefs[i].sprites, sBosBoogieSpriteDefs[i].spriteCount);

        if (sz < t) {
            sz = t;
        }
    }

    work->tiles = AllocObjTiles(sz, NULL);
    AnimInit(&work->anim, NULL, NULL);
    work->animationIndex = 9;
    SetBoogieAnimation(work, 0, 1);
    TaskPoolInit(&work->tasks, 7);
    TaskCreate(&work->tasks, &gTaskDescBosShadow, &work->actor);
    TaskCreate(&work->tasks, &gTaskDescBosBoogieMapanime, NULL);
    TaskCreate(&work->tasks, &gTaskDescBosBoogieSaku, work);
    work->dice = NULL;
    work->task = NULL;
    work->dice2 = NULL;
    work->dice3 = NULL;
    gBtlWork->bossX = work->actor.x;
    gBtlWork->bossY = work->actor.y;
    gBtlWork->bossZ = work->actor.z;
}

u8 task_bos_boogie_1(BoogieWork* work) {
    BtlObj* a = &work->actor;
    PrizeCardArg fx;
    u16 random;

    switch (UpdateBtlObjReaction(a)) {
    case BTL_REACTION_CARD_ACTION:
        work->state = 1;
        work->timer = 0;
        break;
    case BTL_REACTION_HURT:
    case BTL_REACTION_STUNNED:
    case BTL_REACTION_GRAVITY:
        work->state = 3;
        work->timer = 0;
        break;
    case BTL_REACTION_DEFEATED:
    case BTL_REACTION_GRAVITY_DEFEATED:
        if (work->state != 4) {
            work->state = 4;
            work->defeatStep = 0;
            work->timer = 0;
        }

        break;
    case BTL_REACTION_CARD_BROKEN:
        work->state = 2;
        work->timer = 0;
        break;
    default:
        if (gBosBoogieDiceFaceReady != 0 && work->state != 4) {
            work->state = 5;
            work->timer = 0;
        }

        break;
    }

    switch (work->state) {
    case 3:
        if (work->timer == 0) {
            AnimReset(&work->anim);
            SetBoogieAnimation(work, 4, 1);
            work->vz = -((a->knockbackLift << 9) >> 8);
            work->vx = ((gSineTable[a->angle] * 375) >> 8) * a->knockbackSpeed >> 8;
            work->vy = ((-gSineTable[a->angle + 64] * 375) >> 8) * a->knockbackSpeed >> 8;
            work->timer++;
        }

        if (AnimIsFinished(&work->anim)) {
            ClearBtlObjActionFlags(a);
            work->state = 0;
            work->timer = 0;
        }

        break;
    case 4:
        SetBoogieAnimation(work, 8, 0);

        switch (work->defeatStep) {
        case 0:
            if (work->timer <= 1) {
                work->timer++;
            } else {
                work->defeatStep = 1;
            }

            break;
        case 1:
            BeginBossDefeat(a);
            work->defeatStep = 2;
            break;
        case 2:
            if (FadeIsActive() == 0) {
                BgFxStartBossDeath(a->x, a->y + a->z - ((s16)sBosBoogieEmyKind.centerHeight << 8));
                SetBtlPaletteFadeExcluded(work->palette->index + 16, 0);
                FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
                work->defeatStep = 3;
                work->timer = 0;
            }

            break;
        case 3:
            if (work->timer <= 119) {
                work->timer++;
            } else {
                work->defeatStep = 4;
                BgFxStartBossDeathFlash();
            }

            break;
        case 4:
            if (BgFxIsActive() == 0) {
                fx.x = a->x;
                fx.y = 0x24000;
                fx.z = -0x6400;
                CreateBossPrizeCardTask(&gBtlWork->taskPools[0], &fx);
                EndBossDefeat();
                DropBossPrizes(a);
                return 0;
            }

            break;
        }

        break;
    case 0:
        SetBoogieAnimation(work, 0, 1);

        if (AnimIsFinished(&work->anim)) {
            random = GetRandom();

            if ((random & 15) <= 7 && FadeIsActive() == 0) {
                work->state = 11;

                if (work->cardRequested != 0) {
                    RequestBossCardRandom();
                    work->cardRequested = 0;
                }

                work->timer = 0;
                SetBoogieAnimation(work, 1, 1);
            } else {
                AnimReset(&work->anim);
            }
        }

        break;
    case 11:
        SetBoogieAnimation(work, 1, 1);
        work->timer++;

        if (gBosBoogieDiceBreakCount <= 2 && !IsTaskActive(work->dice) &&
            !IsTaskActive(work->dice2) && !IsTaskActive(work->dice3) &&
            !IsTaskActive(work->task) && gBtlWork->enemyTileCount <= 0 && work->cardRequested == 0) {
            random = GetRandom() % 100;

            if (random == 0) {
                RequestBossCardValue(8);
                work->cardRequested = 1;
                work->timer = 0;
            }
        }

        if (func_08083920() == 8) {
            if (work->cardRequested != 0) {
#ifdef VERSION_EU
                if (ConsumeGimmickFlag(0)) {
                    BosBoogieApplyGimmick();
                    break;
                }
#endif

                RequestBossCardRandom();
                work->cardRequested = 0;
                work->diceFollower = 0;
                work->dice = TaskCreate(&work->tasks, &gTaskDescBosBoogieDice, work);
                work->diceFollower = 1;
                work->dice2 = TaskCreate(&work->tasks, &gTaskDescBosBoogieDice, work);
                work->dice3 = TaskCreate(&work->tasks, &gTaskDescBosBoogieDice, work);
                SetBoogieAnimation(work, 2, 1);
                m4aSongNumStart(SONG_VO_BO_ATTACK00);
                work->state = 9;
                work->timer = 0;

#ifndef VERSION_EU
                if (ConsumeGimmickFlag(0)) {
                    gBosBoogieGimmickCardDropped = 0;
                }
#endif

                break;
            }
        } else if (work->cardRequested != 0 && work->timer > 10) {
            RequestBossCardRandom();
            work->cardRequested = 0;
        }

        random = GetRandom();

        if ((random & 255) == 0 && work->cardRequested == 0) {
            work->state = 0;
            work->timer = 0;
        } else if (a->flags & BTLOBJ_FLAG_FACING_LEFT) {
            a->x -= 256;

            if (a->x <= 0xA000) {
                a->x = 0xA000;
                a->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            }
        } else {
            a->x += 256;

            if (a->x >= 0x15000) {
                a->x = 0x15000;
                a->flags |= BTLOBJ_FLAG_FACING_LEFT;
            }
        }

        break;
    case 5:
        gBosBoogieDiceFaceReady = 0;
        SetBoogieAnimation(work, 6, 0);

        if (ConsumeGimmickFlag(0)) {
            BosBoogieApplyGimmick();
            work->state = 0;
            work->timer = 0;
        } else if (AnimIsFinished(&work->anim)) {
            BosBoogieApplyDiceFace(work);
        }

        break;
    case 6:
        if (work->timer > 29) {
            work->state = 7;
        } else {
            work->timer++;
        }

        break;
    case 8:
        if (gBosBoogieAttackHit != 0) {
            work->state = 10;
            work->timer = 0;
        } else if (gBosBoogieTaskKnockedDown != 0) {
            work->state = 0;
            work->timer = 0;
        } else if (!IsTaskActive(work->task)) {
            work->state = 7;
            work->timer = 0;
        }

        break;
    case 7:
        SetBoogieAnimation(work, 7, 0);

        if (AnimIsFinished(&work->anim)) {
            work->state = 0;
            work->timer = 0;
        }

        break;
    case 9:
        SetBoogieAnimation(work, 2, 1);

        if (work->timer == 0) {
            m4aSongNumStart(SONG_BTL_BU_XAI);
        }

        work->timer++;

        if (AnimIsFinished(&work->anim)) {
            work->state = 0;
            work->timer = 0;
        }

        break;
    case 10:
        gBosBoogieAttackHit = 0;
        SetBoogieAnimation(work, 5, 1);

        if (AnimIsFinished(&work->anim)) {
            work->state = 0;
            work->timer = 0;
        }

        break;
    }

    AnimUpdate(&work->anim);
    a->z += work->vz;
    work->vz += 66;

    if (a->z > -0x2000) {
        a->z = -0x2000;
        work->vz = 0;
    }

    if (work->vx > 0) {
        a->x += work->vx;
        work->vx -= 17;

        if (work->vx < 0) {
            work->vx = 0;
        }
    } else if (work->vx < 0) {
        a->x += work->vx;
        work->vx += 17;

        if (work->vx > 0) {
            work->vx = 0;
        }
    }

    if (work->vy > 0) {
        a->y += work->vy / 2;
        work->vy -= 17;

        if (work->vy < 0) {
            work->vy = 0;
        }
    } else if (work->vy < 0) {
        a->y += work->vy / 2;
        work->vy += 17;

        if (work->vy > 0) {
            work->vy = 0;
        }
    }

    ClampBoogiePosition(&a->x, &a->y);
    ColliderSetPosition(&a->collider, a->x, a->y, a->z);
    TaskPoolUpdate(&work->tasks);

    if (ConsumeGimmickFlag(0)) {
        BosBoogieApplyGimmick();
    }

    gBtlWork->bossX = a->x;
    gBtlWork->bossY = a->y;
    gBtlWork->bossZ = a->z;
    return 1;
}

void task_bos_boogie_2(BoogieWork* work) {
    BtlObj* a;
    u16 f;
    void* pal;
    s16 x;
    s16 y;

    a = &work->actor;
    f = GetBattleSpritePriorityFlags(a->y);

    if (!(a->flags & BTLOBJ_FLAG_FACING_LEFT)) {
        f |= 1;
    }

    if (StepHitFlash(a) && work->state != 4) {
        pal = work->palette2;
    } else {
        pal = work->palette;
    }

    WorldToScreen(&x, &y, a->x, a->y, a->z);
    DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, pal, NULL, f, -4100 - (a->y >> 8) * 4);
    TaskPoolDraw(&work->tasks);
}

void task_bos_boogie_3(BoogieWork* work) {
    ReleaseEnemyBtlObj(&work->actor);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
    TaskPoolDestroy(&work->tasks);
}

void BosBoogieRemoveOtherEnemies() {
    BtlObj* t;

    t = ListPoolFirst(&gBtlWork->pool);

    while (t != NULL) {
        if (t->kind != 39) {
            t->flags |= BTLOBJ_FLAG_WARP_PENDING;
            t->hitFlags = 0;
        }

        t = ListPoolNext(&t->node);
    }
}

void BosBoogieApplyGimmick() {
    BosBoogieRemoveOtherEnemies();
    gBosBoogieGimmickCardDropped = 0;

    if (gBosBoogieDiceBreakCount <= 2) {
        gBosBoogieDiceBreakCount = 3;
        gBosBoogieSakuOpenTime += 540;
    }
}

u32 GetBoogieDiceState() {
    if (IsTaskActive(sBoogieWork->dice) != 0) {
        return ((BoogieDiceWork*)sBoogieWork->dice->work)->state;
    }

    return 11;
}

TaskDesc gTaskDescBosBoogie = {
    "task_bos_boogie",
    (TaskInitFunc)task_bos_boogie_0,
    (TaskUpdateFunc)task_bos_boogie_1,
    (TaskDrawFunc)task_bos_boogie_2,
    (TaskDestroyFunc)task_bos_boogie_3,
    sizeof(BoogieWork),
};
