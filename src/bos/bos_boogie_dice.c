/**
 * bos_boogie_dice.c
 * Oogie Boogie Boss Dice and Gimmicks
 */

#include "macros.h"
#include "bos4.h"
#include "sprites_bos4.h"
#include "system_state.h"
#include "btl_api.h"
#include "songs.h"
#include <string.h>
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_bg_types.h"
#include "battle_work.h"
#include "bos4_api.h"
#include "bos_boogie.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "card_api.h"
#include "display.h"
#include "engine_math.h"
#include "m4a_song.h"
#include "map_types.h"
#include "obj.h"
#include "obj_api.h"
#include "registration_data.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "bos_boogie_dice.h"

u16 gBosBoogieSakuOpenTime EWRAM_COMMON(4);
u8 gBosBoogieDiceFace EWRAM_COMMON(4);
struct BtlObj* gBosBoogieActor EWRAM_COMMON(4);
u16 gBosBoogieDiceBreakCount EWRAM_COMMON(4);
u8 gBosBoogieDiceFaceReady EWRAM_COMMON(4);
u8 gBosBoogieGimmickCardDropped EWRAM_COMMON(4);
u8 gBosBoogieAttackHit EWRAM_COMMON(4);
u8 gBosBoogieTaskKnockedDown EWRAM_COMMON(4);
u8 gBosBoogieKnivesRetract EWRAM_COMMON(4);
u8 gBosBoogieKnivesMoveRight EWRAM_COMMON(4);
u8 gBosUrsulaActive EWRAM_COMMON(4);
s32 gBosUrsulaBaseZ EWRAM_COMMON(4);
u8 gMapChkUseParams EWRAM_COMMON(4);
MapFloorState gMapFloorState EWRAM_COMMON(16);

static const EmyKind sBosBoogieDiceEmyKind = { 39, 0, 16, 16, 0, 0, EMY_KIND_FLAG_NO_COLLIDER };

TaskDesc gTaskDescBosBoogieDice = {
    "task_bos_boogie_dice",
    (TaskInitFunc)task_bos_boogie_dice_0,
    (TaskUpdateFunc)task_bos_boogie_dice_1,
    (TaskDrawFunc)task_bos_boogie_dice_2,
    (TaskDestroyFunc)task_bos_boogie_dice_3,
    sizeof(BoogieDiceWork),
};

static void* const sBoogieDiceFaces[6][3] = {
#if defined(VERSION_US)
    { gUnkUs_09EF67A8, gUnkUs_09EF679C, gUnk_097976DC },
    { gUnkUs_09EF67B8, gUnkUs_09EF67AC, gUnk_09797D0C },
    { gUnkUs_09EF67C8, gUnkUs_09EF67BC, gUnk_0979833C },
    { gUnkUs_09EF67D8, gUnkUs_09EF67CC, gUnk_0979896C },
    { gUnkUs_09EF67E8, gUnkUs_09EF67DC, gUnk_09798F9C },
    { gUnkUs_09EF67F8, gUnkUs_09EF67EC, gUnk_097995CC },
#elif defined(VERSION_JP)
    { gUnkJp_09ECDB94, gUnkJp_09ECDB88, gUnk_097976DC },
    { gUnkJp_09ECDBA4, gUnkJp_09ECDB98, gUnk_09797D0C },
    { gUnkJp_09ECDBB4, gUnkJp_09ECDBA8, gUnk_0979833C },
    { gUnkJp_09ECDBC4, gUnkJp_09ECDBB8, gUnk_0979896C },
    { gUnkJp_09ECDBD4, gUnkJp_09ECDBC8, gUnk_09798F9C },
    { gUnkJp_09ECDBE4, gUnkJp_09ECDBD8, gUnk_097995CC },
#else
    { gUnkEu_09F81D90, gUnkEu_09F81D84, gUnk_097976DC },
    { gUnkEu_09F81DA0, gUnkEu_09F81D94, gUnk_09797D0C },
    { gUnkEu_09F81DB0, gUnkEu_09F81DA4, gUnk_0979833C },
    { gUnkEu_09F81DC0, gUnkEu_09F81DB4, gUnk_0979896C },
    { gUnkEu_09F81DD0, gUnkEu_09F81DC4, gUnk_09798F9C },
    { gUnkEu_09F81DE0, gUnkEu_09F81DD4, gUnk_097995CC },
#endif
};

static const EmyKind sBosBoogieExplosiondiceEmyKind = { 39, 0, 16, 16, 0, 0, 0 };

static TaskDesc sTaskDescBosBoogieExplosiondice = {
    "task_bos_boogie_explosiondice",
    (TaskInitFunc)task_bos_boogie_explosiondice_0,
    (TaskUpdateFunc)task_bos_boogie_explosiondice_1,
    (TaskDrawFunc)task_bos_boogie_explosiondice_2,
    (TaskDestroyFunc)task_bos_boogie_explosiondice_3,
    sizeof(BoogieExplosiondiceWork),
};

TaskDesc gTaskDescBosBoogieSaku = {
    "task_bos_boogie_saku",
    (TaskInitFunc)task_bos_boogie_saku_0,
    (TaskUpdateFunc)task_bos_boogie_saku_1,
    (TaskDrawFunc)task_bos_boogie_saku_2,
    (TaskDestroyFunc)task_bos_boogie_saku_3,
    sizeof(BoogieSakuWork),
};

TaskDesc gTaskDescBosBoogieMap = {
    "task_bos_boogie_map",
    (TaskInitFunc)task_bos_boogie_map_0,
    (TaskUpdateFunc)task_bos_boogie_map_1,
    NULL,
    NULL,
    sizeof(BoogieMapWork),
};

static const BosMapanimeFrame sBosBoogieMapanimeFrames[5] = { { 5, 0 }, { 5, 1 }, { 5, 2 }, { 5, 3 }, { 5, 4 } };

static const BosMapanimeDef sBosBoogieMapanimeDef0 = { sBosBoogieMapanimeFrames, 5, 0, gUnk_097ED478, 0x7C00, 0x0100, 0x0300, 0, 0 };

static const BosMapanimeDef sBosBoogieMapanimeDef1 = { sBosBoogieMapanimeFrames, 5, 0, gUnk_097ED578, 0x7D00, 0x0100, 0x0300, 0, 0 };

static const BosMapanimeDef sBosBoogieMapanimeDef2 = { sBosBoogieMapanimeFrames, 5, 0, gUnk_097ED678, 0x7E00, 0x0100, 0x0300, 0, 0 };

TaskDesc gTaskDescBosBoogieMapanime = {
    "task_bos_boogie_mapanime",
    (TaskInitFunc)task_bos_boogie_mapanime_0,
    (TaskUpdateFunc)task_bos_boogie_mapanime_1,
    (TaskDrawFunc)task_bos_boogie_mapanime_2,
    (TaskDestroyFunc)task_bos_boogie_mapanime_3,
    sizeof(BoogieMapanimeWork),
};

static const EmyKind sBosBoogieDiskEmyKind = { 39, 0, 16, 16, 0, 0, EMY_KIND_FLAG_LARGE_BODY };

TaskDesc gTaskDescBosBoogieDisk = {
    "task_bos_boogie_disk",
    (TaskInitFunc)task_bos_boogie_disk_0,
    (TaskUpdateFunc)task_bos_boogie_disk_1,
    (TaskDrawFunc)task_bos_boogie_disk_2,
    (TaskDestroyFunc)task_bos_boogie_disk_3,
    sizeof(BoogieDiskWork),
};

static const EmyKind sBosBoogieKnifeEmyKind = { 39, 0, 192, 16, 0, 0, 0 };

static TaskDesc sTaskDescBosBoogieKnife = {
    "task_bos_boogie_knife",
    (TaskInitFunc)task_bos_boogie_knife_0,
    (TaskUpdateFunc)task_bos_boogie_knife_1,
    (TaskDrawFunc)task_bos_boogie_knife_2,
    (TaskDestroyFunc)task_bos_boogie_knife_3,
    sizeof(BoogieKnifeWork),
};

static const EmyKind sBosBoogieKnifereaderEmyKind = { 39, 0, 0, 0, 0, 0, 0 };

TaskDesc gTaskDescBosBoogieKnifereader = {
    "task_bos_boogie_knifereader",
    (TaskInitFunc)task_bos_boogie_knifereader_0,
    (TaskUpdateFunc)task_bos_boogie_knifereader_1,
    (TaskDrawFunc)task_bos_boogie_knifereader_2,
    (TaskDestroyFunc)task_bos_boogie_knifereader_3,
    sizeof(BoogieKnifereaderWork),
};

static const EmyKind sBosBoogieKaihukuEmyKind = { 39, 0, 16, 16, 0, 0, 0 };

TaskDesc gTaskDescBosBoogieKaihuku = {
    "task_bos_boogie_kaihuku",
    (TaskInitFunc)task_bos_boogie_kaihuku_0,
    (TaskUpdateFunc)task_bos_boogie_kaihuku_1,
    (TaskDrawFunc)task_bos_boogie_kaihuku_2,
    (TaskDestroyFunc)task_bos_boogie_kaihuku_3,
    sizeof(BoogieKaihukuWork),
};

u8 ClampBoogieDicePosition(s32* a, s32* b, s16 c, u16 d) {
    u8 r;

    r = 0;

    if (*a < (128 - c) << 8) {
        *a = (128 - c) << 8;
        r = 1;
    }

    if (*a > (c + 368) << 8) {
        *a = (c + 368) << 8;
        r = 1;
    }

    if (*b < (576 - (s16)d) << 8) {
        *b = (576 - (s16)d) << 8;
        r = 1;
    }

    if (*b > ((s16)d + 632) << 8) {
        *b = ((s16)d + 632) << 8;
        r = 1;
    }

    return r;
}

u8 BosBoogieDiceIsHeld(BoogieDiceWork* work) {
    if (work->state == 3) {
        if (work->parent->state == 9) {
            if (AnimGetFrame(&work->parent->anim) <= 2) {
                if (!AnimIsFinished(&work->parent->anim)) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void BosBoogieDiceGrow(BoogieDiceWork* work) {
    if (work->scaleY <= 255) {
        work->scaleY += 8;
    }

    if (work->scaleX <= 255) {
        work->scaleX += 8;
    }
}

void task_bos_boogie_dice_0(BoogieDiceWork* work, BoogieWork* arg) {
    BtlObj* p = &arg->actor;
    s32 c;
    s32 d;
    s32 e;
    u16 r;

    work->follower = arg->diceFollower;
    work->parent = arg;
    work->state = 10;
    work->timer = 0;
    work->vz = -0x4CC;
    work->speed = GetRandom() % 437 + 0x4C;
    work->angle = GetRandom() % 0x78 + 0x44;
    work->scaleY = 0x33;
    work->scaleX = 0x33;
    work->y = 0;
    work->counted = 0;
    gBosBoogieDiceFaceReady = 0;
    c = p->x;
    d = 0x24000;
    e = p->z - 0x3800;
    InitEnemyBtlObj(&work->obj, &sBosBoogieDiceEmyKind, c, d, e);
    ColliderInit(&work->obj.collider, 3, sBosBoogieDiceEmyKind.radius, sBosBoogieDiceEmyKind.height);
    work->obj.flags |= 0x400;
#ifdef VERSION_EU
    work->obj.flags |= BTLOBJ_FLAG_INTANGIBLE;
#else
    work->obj.flags |= BTLOBJ_FLAG_HIT_LOCKED;
#endif
    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF6788, 4), gUnk_09796EAA);
    work->palette = LoadObjPalette(gUnk_0984AF98, 32);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    AnimInit(&work->anim, gUnk_09EF6798, gUnk_09EF6788);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    r = GetRandom();
    AnimSetFrame(&work->anim, r & 3);
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBosShadow, &work->obj);

    if (!work->follower) {
        RequestEnemyCardUse(&work->obj);
    }
}

u8 task_bos_boogie_dice_1(BoogieDiceWork* work) {
    BtlObj* p = &work->obj;

    if (!work->follower) {
        switch (UpdateBtlObjReaction(p)) {
        case BTL_REACTION_CARD_ACTION:
            work->state = 3;
            work->timer = 0;
            break;
        case BTL_REACTION_CARD_BROKEN:
            work->state = 0;
            work->timer = 0;
            gBosBoogieSakuOpenTime += 180;
            break;
        case BTL_REACTION_HEALED:
        default:
            if (ConsumeGimmickFlag(0)) {
                BosBoogieApplyGimmick();

                if (work->state == 3) {
                    work->state = 0;
                    work->timer = 0;
                }
            }

            break;
        case BTL_REACTION_HURT:
        case BTL_REACTION_DEFEATED:
        case BTL_REACTION_STUNNED:
        case BTL_REACTION_GRAVITY:
        case BTL_REACTION_GRAVITY_DEFEATED:
            work->state = 2;
            work->timer = 0;
            break;
        }
    } else {
        switch (GetBoogieDiceState()) {
        case 3:
            if (work->state != 3) {
                work->state = 3;
                work->timer = 0;
            }

            break;
        case 0:
            if (work->state != 0) {
                work->state = 0;
                work->timer = 0;
            }

            break;
        case 1:
            if (work->state == 3) {
                work->state = 0;
                work->timer = 0;
            }

            break;
        }

        switch ((u32)UpdateBtlObjReaction(p)) {
        case BTL_REACTION_HURT:
        case BTL_REACTION_DEFEATED:
        case BTL_REACTION_STUNNED:
        case BTL_REACTION_GRAVITY:
        case BTL_REACTION_GRAVITY_DEFEATED:
            work->state = 2;
            work->timer = 0;
            break;
        }
    }

    switch (work->state) {
    case 3:
        if (BosBoogieDiceIsHeld(work)) {
            return 1;
        }

#ifdef VERSION_EU
        p->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
#else
        p->flags &= ~BTLOBJ_FLAG_HIT_LOCKED;
#endif
        BosBoogieDiceGrow(work);
        work->vz += 51;
        p->z += work->vz;
        p->x += gSineTable[work->angle] * work->speed >> 8;
        p->y += -gSineTable[work->angle + 0x40] * work->speed >> 8;

        if (p->collider.colliding && work->scaleY > 255 && work->scaleX > 255) {
            work->speed = work->speed * 230 >> 8;
            p->x += p->collider.pushX;
            p->y += p->collider.pushY;
            work->angle = work->angle + (100 + GetRandom() % 57);
        }

        if (ClampBoogieDicePosition(&p->x, &p->y, 0, 0)) {
            work->angle = work->angle + (100 + GetRandom() % 57);
        }

        if (p->z > 0) {
            p->z = 0;
            work->vz = -(work->vz * 179 >> 8);
            work->speed = work->speed * 212 >> 8;

            if (work->vz >= -25) {
                RollBoogieDice(work);
                work->state = 4;
                p->flags |= BTLOBJ_FLAG_INTANGIBLE;

                if (!work->follower) {
                    ClearBtlObjActionFlags(p);
                }
            }
        }

        break;
    case 0:
#ifdef VERSION_EU
        p->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
#else
        p->flags &= ~BTLOBJ_FLAG_HIT_LOCKED;
#endif

        if (work->timer == 0 && !work->follower) {
            ClearBtlObjActionFlags(p);
            gBosBoogieDiceBreakCount++;
            work->counted = 1;
        }

        work->timer++;
        BosBoogieDiceGrow(work);

        if (p->collider.colliding && work->scaleY > 255 && work->scaleX > 255) {
            work->speed = work->speed * 230 >> 8;
            p->x += p->collider.pushX;
            p->y += p->collider.pushY;
            work->angle = work->angle + (100 + GetRandom() % 57);
        }

        work->vz += 51;
        p->z += work->vz;

        if (p->z > 0) {
            p->z = 0;
            work->vz = -(work->vz * 128 >> 8);
            work->timer = 0;
            work->state = 1;
        }

        break;
    case 1:
        if (work->timer > 59) {
            work->state = 6;
            break;
        }

        work->timer++;
        work->vz += 51;
        p->x += gSineTable[work->angle] * work->speed >> 8;
        p->y += -gSineTable[work->angle + 0x40] * work->speed >> 8;

        if (p->collider.colliding && work->scaleY > 255 && work->scaleX > 255) {
            work->speed = work->speed * 230 >> 8;
            p->x += p->collider.pushX;
            p->y += p->collider.pushY;
            work->angle = work->angle + (100 + GetRandom() % 57);
        }

        if (ClampBoogieDicePosition(&p->x, &p->y, 0, 0)) {
            work->angle = work->angle + (100 + GetRandom() % 57);
        }

        if (p->z > 0) {
            p->z = 0;
            work->vz = -(work->vz * 179 >> 8);
        }

        break;
    case 2:
        if (!work->follower && !gBosBoogieGimmickCardDropped && GetRandom() % 16 <= 7) {
            gBosBoogieGimmickCardDropped = 1;
            DropGimmickCard(0, p->x, p->y, p->z);
        }

        SetBtlObjUnhittable(p, 1);

        return 0;
    case 4:
        if (AnimIsFinished(&work->anim)) {
            work->state = 5;
            work->timer = 0;
        }

        break;
    case 5:
        if (work->timer > 20) {
            work->state = 6;
            break;
        }

        work->timer++;
        break;
    case 6:
        SetBtlObjUnhittable(p, 1);
        work->scaleY -= 12;
        work->y += 96;

        if (work->scaleY <= 127) {
            work->state = 7;
            work->vz = -0x4CC;
            work->timer = 0;
        }

        break;
    case 7:
        if (work->timer > 10) {
            work->state = 8;
            work->timer = 0;
            break;
        }

        work->timer++;
        break;
    case 8:
        work->vz += 51;
        p->z += work->vz;
        work->scaleY += 25;
        work->y -= 200;

        if (work->scaleY > 255) {
            work->state = 9;
            work->timer = 0;
        } else if (work->scaleY <= 178) {
            break;
        }
    case 9:
        work->scaleX -= 38;

        if (work->scaleX <= 24) {
            BgFxStartDarkDeathBlend(p->x, p->y + p->z, 0x100, 8, 16);

            return 0;
        }

        break;
    case 10:
        if (work->timer > 30) {
            return 0;
        }

        work->timer++;
        break;
    }

    AnimUpdate(&work->anim);

    if (work->state == 1) {
        AnimUpdate(&work->anim);
    }

    ColliderSetPosition(&p->collider, p->x, p->y, p->z);
    TaskPoolUpdate(&work->tasks);

    return 1;
}

void task_bos_boogie_dice_2(BoogieDiceWork* work) {
    BtlObj* p = &work->obj;
    s16 x;
    s16 y;
    u16 c;
    void* pal;
    ObjAffine* aff;
    s32 a;
    s32 b;

    if (BosBoogieDiceIsHeld(work)) {
        return;
    }

    c = GetBattleSpritePriorityFlags(p->y);

    if (StepHitFlash(p)) {
        pal = work->palette2;
    } else {
        pal = work->palette;
    }

    a = work->scaleX;

    if (a > 0x100) {
        a = 0x100;
    }

    b = work->scaleY;

    if (b > 0x100) {
        b = 0x100;
    }

    aff = AllocObjAffine(0, a, b, 0);
    WorldToScreen(&x, &y, p->x, p->y, p->z);
    DrawSprite(x, (work->y >> 8) + y, AnimGetGfx(&work->anim), work->tiles, pal,
        aff, c, -0x1004 - (p->y >> 8) * 4);
    TaskPoolDraw(&work->tasks);
}

void task_bos_boogie_dice_3(BoogieDiceWork* work) {
    if (!work->counted && gBosBoogieDiceBreakCount != 3 && !work->follower && work->state != 10) {
        gBosBoogieDiceFaceReady = 1;
    }

    ColliderUnregister(&work->obj.collider);
    ReleaseEnemyBtlObj(&work->obj);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
    TaskPoolDestroy(&work->tasks);
}

void RollBoogieDice(BoogieDiceWork* work) {
    void* tbl[6][3];
    u8 n;

    memcpy(tbl, sBoogieDiceFaces, sizeof(tbl));

    switch (GetRandom() % 4) {
    case 0:
        n = 5;
        break;
    case 1:
        n = 3;
        break;
    case 2:
        n = 0;
        break;
    default:
        switch (GetRandom() % 3) {
        case 0:
            n = 1;
            break;
        case 1:
            n = 2;
            break;
        default:
            n = 4;
            break;
        }

        break;
    }

    if (!work->follower) {
        gBosBoogieDiceFace = n;
    }

    AnimChangeWithTables(&work->anim, 0, 0, tbl[n][0], tbl[n][1]);
    SetObjTileSource(work->tiles, tbl[n][2]);
}

u8 BosBoogieExplosiondiceIsHeld(BoogieExplosiondiceWork* work) {
    BoogieWork* boogie = work->boogie;

    if (boogie->animationIndex == 3 && AnimGetFrame(&boogie->anim) <= 2) {
        return 1;
    }

    return 0;
}

void task_bos_boogie_explosiondice_0(BoogieExplosiondiceWork* work, BoogieWork* arg) {
    BtlObj* p;

    work->boogie = arg;
    work->state = 0;
    work->timer = 0;
    work->vz = 0;
    work->speed = GetRandom() % 437 + 76;
    work->angle = GetRandom() % 128 + 0x40;
    p = gBtlWork->actor;
    work->obj.x = p->x;
    work->obj.y = p->y;
    work->obj.z = -0xA000;
    ColliderInit(&work->obj.collider, 8, sBosBoogieExplosiondiceEmyKind.radius, sBosBoogieExplosiondiceEmyKind.height);
    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF6774, 4), gUnk_0979666A);
    work->palette = LoadObjPalette(gUnk_0984AF98, 32);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    AnimInit(&work->anim, gUnk_09EF6784, gUnk_09EF6774);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBosShadow, &work->obj);
}

u8 task_bos_boogie_explosiondice_1(BoogieExplosiondiceWork* work) {
    BtlObj* p = &work->obj;

    if (BosBoogieExplosiondiceIsHeld(work)) {
        return 1;
    }

    switch (work->state) {
    case 0:
        work->vz += 51;
        p->z += work->vz;

        if (p->z > -0x2000) {
            BgFxStartExplosion(p->x, p->y + p->z, 0);
            return 0;
        }

        break;
    case 2:
        if (!BgFxIsActive()) {
            return 0;
        }

        break;
    }

    AnimUpdate(&work->anim);
    ColliderSetPosition(&p->collider, p->x, p->y, p->z);
    TaskPoolUpdate(&work->tasks);

    return 1;
}

void task_bos_boogie_explosiondice_2(BoogieExplosiondiceWork* work) {
    BtlObj* p = &work->obj;
    u8 f = BosBoogieExplosiondiceIsHeld(work);
    s16 x;
    s16 y;
    u16 c;
    void* pal;

    if (f || work->state == 1) {
        return;
    }

    c = GetBattleSpritePriorityFlags(p->y);
    pal = work->palette;
    WorldToScreen(&x, &y, p->x, p->y, p->z);
    DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, pal, NULL, c,
        -0x1004 - (p->y >> 8) * 4);
    TaskPoolDraw(&work->tasks);
}

void task_bos_boogie_explosiondice_3(BoogieExplosiondiceWork* work) {
    ColliderUnregister(&work->obj.collider);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
    TaskPoolDestroy(&work->tasks);
}

u8 BosBoogieIsActorPastSaku() {
    if (gBtlWork->actor->y <= 0x23EFF) {
        return 1;
    }

    return 0;
}

void task_bos_boogie_saku_0(BoogieSakuWork* work, BoogieWork* arg) {
    work->boogie = arg;
    work->tiles = LoadObjTiles(gSakuTiles, 0x2E0);
    work->palette = LoadObjPalette(gBoss02objPalette, 32);
    AnimInit(&work->anim, gSakuAnims, gSakuFrames);
    AnimStart(&work->anim, 0, 0);
    work->openTimer = 0;
    TaskPoolInit(&work->tasks, 1);
    work->task = NULL;
    work->closePending = 0;
}

u8 task_bos_boogie_saku_1(BoogieSakuWork* work) {
    u8 f;

    if (gBosBoogieDiceBreakCount > 2 && AnimIsFinished(&work->anim)) {
        if (work->openTimer < gBosBoogieSakuOpenTime) {
            if (work->openTimer == 0) {
                BtlMapStartShake();
            }

            work->openTimer++;
            SetBattleBounds(0x80, 0x170, 0x228, 0x278);

            if (BosBoogieIsActorPastSaku()) {
                SetBtlObjUnhittable(&work->boogie->actor, 0);
            } else {
                SetBtlObjUnhittable(&work->boogie->actor, 1);
            }
        } else if (work->boogie->state != 4) {
            work->closePending = 1;
            gBosBoogieDiceBreakCount = 0;
            work->openTimer = 0;
            gBosBoogieSakuOpenTime = 0;
            SetBtlObjUnhittable(&work->boogie->actor, 1);

            if (BosBoogieIsActorPastSaku()) {
                work->task = TaskCreate(&work->tasks, &sTaskDescBosBoogieExplosiondice, work->boogie);
            }
        }
    }

    if (gBosBoogieDiceBreakCount <= 2 && !IsTaskActive(work->task)) {
        SetBattleBounds(0x80, 0x170, 0x240, 0x278);

        if (gBosBoogieDiceBreakCount != 0) {
            AnimChange(&work->anim, gBosBoogieDiceBreakCount, 0);
        } else if (work->closePending) {
            AnimChange(&work->anim, 3, 0);
            work->closePending = 0;
        }
    }

    f = AnimIsFinished(&work->anim);

    if (gBosBoogieDiceBreakCount > 2
            || (gBosBoogieDiceBreakCount == 0 && AnimGetId(&work->anim) == 3
                && !IsTaskActive(work->task))) {
        AnimUpdate(&work->anim);
    }

    if (!f && AnimIsFinished(&work->anim)) {
        m4aSongNumStart(SONG_BTL_BU_SAKU);

        if (AnimGetId(&work->anim) == 3) {
            AnimChange(&work->anim, 0, 0);
        }
    }

    TaskPoolUpdate(&work->tasks);

    return 1;
}

void BosBoogieSakuDrawAt(BoogieSakuWork* work, s32 a, u16 b) {
    s16 x;
    s16 y;

    WorldToScreen(&x, &y, a, 0x23F00, -0x2000);
    DrawSprite(x, y + 1, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL, b, 0xE700);
    TaskPoolDraw(&work->tasks);
}

void task_bos_boogie_saku_2(BoogieSakuWork* work) {
    u16 v = GetBattleSpritePriorityFlags(0x23F00);

    BosBoogieSakuDrawAt(work, 0xA800, v);
    BosBoogieSakuDrawAt(work, 0xF800, v);
    BosBoogieSakuDrawAt(work, 0x14800, v);
}

void task_bos_boogie_saku_3(BoogieSakuWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

void task_bos_boogie_map_0(BoogieMapWork* work, BattleBackgroundDef* arg) {
    LoadBgTiles(0, arg->tiles, arg->tilesSize);
    LoadBgPalette(0, arg->palette, arg->paletteSize);
    SetBgMapBlocks(0, &arg->map, 2, 2);
    gBtlWork->scale = 0x100;
    gBtlWork->zoomScale = 0x100;
    gBtlWork->x = 0xF800;
    gBtlWork->y = 0x21000;
    gBtlWork->viewX = 0xF800;
    gBtlWork->viewY = 0x21000;
    gBtlWork->x2 = 0xF800;
    gBtlWork->y2 = 0x21000;
    gBtlWork->zoomX = 0xF800;
    gBtlWork->zoomY = 0x21000;
    gBtlWork->zoomSteps = 15;
    gBtlWork->rotation = 0;
    BtlMapResetShake();
    ScrollBgMapTo(0, gBtlWork->viewX >> 8, gBtlWork->viewY >> 8);
}

u8 task_bos_boogie_map_1() {
    s32 a;
    s32 b;

    BtlMapUpdateShake();
    a = (gBtlWork->x2 - gBtlWork->x) >> 3;
    b = (gBtlWork->y2 - gBtlWork->y) >> 3;

    if (a > 0x500) {
        a = 0x500;
    } else if (a < -0x500) {
        a = -0x500;
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

    if (gBtlWork->viewY - 0x5000 < 0x18C00) {
        gBtlWork->viewY = 0x1DC00;
    } else if (gBtlWork->viewY + 0x5000 > 0x27800) {
        gBtlWork->viewY = 0x22800;
    }

    gBtlWork->viewY += BtlMapGetShake();
    ScrollBgMapTo(0, (gBtlWork->viewX >> 8) + 8, (gBtlWork->viewY >> 8) - 0x108);

    return 1;
}

void task_bos_boogie_mapanime_0(BoogieMapanimeWork* work) {
    BosMapanimeInit(&work->anims[0], &sBosBoogieMapanimeDef0);
    BosMapanimeInit(&work->anims[1], &sBosBoogieMapanimeDef1);
    BosMapanimeInit(&work->anims[2], &sBosBoogieMapanimeDef2);
}

u8 task_bos_boogie_mapanime_1(BoogieMapanimeWork* work) {
    u32 i;
    u8 r = 0;

    for (i = gBosBoogieDiceBreakCount; i <= 2; i++) {
        r = BosMapanimeUpdate(&work->anims[i], work->anims[i].def, r);
    }

    return 1;
}

void task_bos_boogie_mapanime_2() {
}

void task_bos_boogie_mapanime_3() {
}

u8 ClampBoogieDiskPosition(s32* x, s32* y, s16 w, s16 h, s32 z) {
    u8 r = 0;

    if (*x < (0x80 - w) << 8) {
        *x = (0x80 - w) << 8;
        r = 1;
    }

    if (*x > (w + 0x170) << 8) {
        *x = (w + 0x170) << 8;
        r = 1;
    }

    if (*y < (0x240 - h) << 8) {
        *y = (0x240 - h) << 8;
        r = 1;
    }

    if (*y > (0x278 - h) << 8) {
        *y = (0x278 - h) << 8;
        r = 1;
    }

    return r;
}

void task_bos_boogie_disk_0(BoogieDiskWork* work, BtlObj* arg) {
    s32 x;
    s32 v;
    s32 d;
    s32 e;

    work->state = 2;
    work->timer = 0;
    work->angle = 0;
    work->vz = -0x200;

    if (gBtlWork->actor->x < 0xF800) {
        x = gBtlWork->actor->x + 0xF000;
        work->vx = -0x266;
    } else {
        x = gBtlWork->actor->x - 0xF000;
        work->vx = 0x266;
    }

    work->vy = 0x133;
    v = arg->maxHp;

    if (arg->hp < (s16)(v / 3)) {
        work->vx *= 3;
        work->vy *= 3;
    } else if (arg->hp < v * 2 / 3) {
        work->vx *= 2;
        work->vy *= 2;
    }

    d = gBtlWork->actor->y;
    e = -0x1000;
    InitEnemyBtlObj(&work->obj, &sBosBoogieDiskEmyKind, x, d, e);
    work->obj.flags |= 0x400;
    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gNokogiriFrames, 8), gNokogiriTiles);
    work->palette = LoadObjPalette(gKaifukuPalette, 32);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    AnimInit(&work->anim, gNokogiriAnims, gNokogiriFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBosShadow, &work->obj);
    RequestEnemyCardUse(&work->obj);
    m4aSongNumStart(SONG_BTL_BU_KAITEN);
}

u8 task_bos_boogie_disk_1(BoogieDiskWork* work) {
    BtlObj* p = &work->obj;

    switch (UpdateBtlObjReaction(p)) {
    case BTL_REACTION_CARD_ACTION:
        work->state = 0;
        work->timer = 0;
        break;
    case BTL_REACTION_HEALED:
    default:
        if (!ConsumeGimmickFlag(0)) {
            break;
        }

        BosBoogieApplyGimmick();
    case BTL_REACTION_HURT:
    case BTL_REACTION_DEFEATED:
    case BTL_REACTION_CARD_BROKEN:
    case BTL_REACTION_STUNNED:
    case BTL_REACTION_GRAVITY:
    case BTL_REACTION_GRAVITY_DEFEATED:
        if (work->state != 1) {
            work->state = 1;
            work->timer = 0;
        }

        break;
    }

    switch (work->state) {
    case 0:
        p->y += work->vy;

        if (ClampBoogieDiskPosition(&p->x, &p->y, 0x20, -0x10, p->z)) {
            work->vy = -work->vy;
        }

        p->x += work->vx;

        if ((work->vx > 0 && p->x > 0x19000)
                || (work->vx <= 0 && p->x < 0x6000)) {
            ClearBtlObjActionFlags(p);

            return 0;
        }

        if (ApplyAttackBox(0x105, p->x, p->y, p->z, 0x20, 0x10, 1) == 1) {
            gBosBoogieAttackHit = 1;
            m4aSongNumStart(SONG_BTL_MON_SWORD01);
        }

        break;
    case 1:
        if (p->z >= 0) {
            gBosBoogieTaskKnockedDown = 1;
            ClearBtlObjActionFlags(p);

            return 0;
        }

        work->timer++;
        p->x -= work->vx;
        work->angle += 0x19;
        p->z += work->vz;
        work->vz += 0x42;

        if (p->z > 0) {
            p->z = 0;
        }

        break;
    case 2:
        if ((s16)work->timer > 30) {
            return 0;
        }

        work->timer++;
        break;
    }

    AnimUpdate(&work->anim);
    ColliderSetPosition(&p->collider, p->x, p->y, p->z);
    TaskPoolUpdate(&work->tasks);

    return 1;
}

void task_bos_boogie_disk_2(BoogieDiskWork* work) {
    BtlObj* p = &work->obj;
    s16 x;
    s16 y;
    u16 c = GetBattleSpritePriorityFlags(p->y);
    void* pal = work->palette;
    ObjAffine* obj = AllocObjAffineAngle(work->angle, 1);

    WorldToScreen(&x, &y, p->x, p->y, p->z);
    DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, pal, obj, c,
        -0x1004 - (p->y >> 8) * 4);
    TaskPoolDraw(&work->tasks);
}

void task_bos_boogie_disk_3(BoogieDiskWork* work) {
    ReleaseEnemyBtlObj(&work->obj);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
    TaskPoolDestroy(&work->tasks);
}

void BosBoogieKnifeAttack(BoogieKnifeWork* work) {
    BtlObj* p = &work->obj;
    s32 dy;

    if (gBosBoogieKnivesMoveRight) {
        work->scaleX = 0x100;
        work->drawOffsetX = 0;
        dy = 0x2000;
    } else {
        work->scaleX = -0x100;
        work->drawOffsetX = 0;
        dy = -0x2000;
    }

    if (ApplyAttackBox(0x106, p->x - dy, p->y, p->z - 0x1000, 4, 0x1C, 0x10) == 1) {
        gBosBoogieAttackHit = 1;
        m4aSongNumStart(SONG_EF_KU_ATT04);
    }
}

void task_bos_boogie_knife_0(BoogieKnifeWork* work, s32* arg) {
    BtlObj* p;
    s32 v;

    work->state = 0;
    work->timer = 0;

    if (gBosBoogieKnivesMoveRight) {
        work->vx = 0x133;
    } else {
        work->vx = -0x133;
    }

    work->vz = 0;
    work->gravity = 0x42;
    work->bounceVz = -0x500;
    p = gBosBoogieActor;
    v = p->maxHp;

    if (p->hp < (s16)(v / 3)) {
        work->gravity = (work->gravity * 0x300) >> 8;
        work->bounceVz = -0xA00;
    } else if (p->hp < v * 2 / 3) {
        work->gravity = (work->gravity * 0x200) >> 8;
        work->bounceVz = -0x780;
    }

    work->obj.y = 0x25C00;
    work->obj.z = -0xC000;
    work->obj.x = *arg;
    ColliderInit(&work->obj.collider, 8, sBosBoogieKnifeEmyKind.radius, sBosBoogieKnifeEmyKind.height);
    work->tiles = LoadObjTiles(gKnifeTiles, 0xC40);
    work->palette = LoadObjPalette(gKnifePalette, 32);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    AnimInit(&work->anim, gKnifeAnims, gKnifeFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
}

u8 task_bos_boogie_knife_1(BoogieKnifeWork* work) {
    BtlObj* p = &work->obj;

    if (gBosBoogieKnivesRetract) {
        work->state = 2;
    }

    switch (work->state) {
    case 0:
        p->z += work->vz;
        work->vz += work->gravity;

        if (p->z < 0) {
            BosBoogieKnifeAttack(work);
        } else {
            p->z = 0;
            work->state = 1;
            work->vz = work->bounceVz;
        }

        break;
    case 1:
        p->x += work->vx;
        p->z += work->vz;
        work->vz += work->gravity;
        work->timer++;

        if (p->z < 0) {
            BosBoogieKnifeAttack(work);
        } else {
            p->z = 0;
            work->vz = work->bounceVz;

            if ((s16)work->timer > 199.99999f) {
                work->state = 2;
            } else {
                BosBoogieKnifeAttack(work);
            }
        }

        break;
    case 2:
        p->z -= 0x800;

        if (p->z < -0xC000) {
            return 0;
        }

        break;
    }

    AnimUpdate(&work->anim);
    ColliderSetPosition(&p->collider, p->x, p->y, p->z);

    return 1;
}

void task_bos_boogie_knife_2(BoogieKnifeWork* work) {
    BtlObj* p = &work->obj;
    s16 x;
    s16 y;
    u16 c;
    void* pal;
    ObjAffine* aff;

    WorldToScreen(&x, &y, p->x + work->drawOffsetX, p->y - 0x2400, p->z);

    if ((u16)(x + 0x20) > 0x130) {
        return;
    }

    c = GetBattleSpritePriorityFlags(p->y);

    if (gBosBoogieKnivesRetract && (gFrameCounter & 1) != 0 && !gBtlWork->paused) {
        pal = work->palette2;
    } else {
        pal = work->palette;
    }

    aff = AllocObjAffine(0, work->scaleX, 0x100, 0);
    DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, pal, aff, c,
        -0x1004 - (p->y >> 8) * 4);
}

void task_bos_boogie_knife_3(BoogieKnifeWork* work) {
    ColliderUnregister(&work->obj.collider);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
}

u8 BosBoogieKnifeIsLanded(BoogieKnifeWork* work) {
    if (work->obj.z >= 0) {
        return 1;
    }

    return 0;
}

u8 BosBoogieAnyKnifeActive(BoogieKnifereaderWork* work) {
    s32 i;

    for (i = 0; i <= 4; i++) {
        if (IsTaskActive(work->knives[i])) {
            return 1;
        }
    }

    return 0;
}

void BosBoogieSpawnKnives(BoogieKnifereaderWork* work) {
    s32 i;
    s32 v;

    if (GetRandom() % 16 > 7) {
        gBosBoogieKnivesMoveRight = 1;
        v = -0x4000;

        for (i = 0; i <= 4; i++) {
            work->knives[i] = TaskCreate(&work->tasks, &sTaskDescBosBoogieKnife, &v);
            v += 0x6800;
        }
    } else {
        gBosBoogieKnivesMoveRight = 0;
        v = 0x23000;

        for (i = 0; i <= 4; i++) {
            work->knives[i] = TaskCreate(&work->tasks, &sTaskDescBosBoogieKnife, &v);
            v += -0x6800;
        }
    }
}

void task_bos_boogie_knifereader_0(BoogieKnifereaderWork* work) {
    s32 i;

    work->state = 2;
    work->timer = 0;
    gBosBoogieKnivesRetract = 0;
    TaskPoolInit(&work->tasks, 5);

    for (i = 0; i < 5; i++) {
        work->knives[i] = NULL;
    }

    InitEnemyBtlObj(&work->obj, &sBosBoogieKnifereaderEmyKind, 0xF800, 0x24000, 0);
    SetBtlObjUnhittable(&work->obj, 1);
    RequestEnemyCardUse(&work->obj);
}

u8 task_bos_boogie_knifereader_1(BoogieKnifereaderWork* work) {
    s32 i;
    BtlObj* e = &work->obj;
    void* pool;
    s32 checkKnives;

    switch (UpdateBtlObjReaction(e)) {
    case BTL_REACTION_CARD_ACTION:
        work->state = 0;
        work->timer = 0;
        break;
    case BTL_REACTION_HEALED:
    default:
        if (!ConsumeGimmickFlag(0)) {
            break;
        }

        BosBoogieApplyGimmick();
    case BTL_REACTION_HURT:
    case BTL_REACTION_DEFEATED:
    case BTL_REACTION_CARD_BROKEN:
    case BTL_REACTION_STUNNED:
    case BTL_REACTION_GRAVITY:
    case BTL_REACTION_GRAVITY_DEFEATED:
        if (work->state != 1) {
            work->state = 1;
            work->timer = 0;
        }

        break;
    }

    switch (work->state) {
    case 2:
        if ((s16)work->timer > 30) {
            return 0;
        }

        work->timer++;
        checkKnives = 0;
        break;
    case 1:
        gBosBoogieKnivesRetract = 1;
        checkKnives = 1;
        break;
    case 0:
        if ((s16)work->timer == 0) {
            work->timer++;
            BosBoogieSpawnKnives(work);
            checkKnives = 0;
            break;
        }
    default:
        checkKnives = 1;
        break;
    }

    if (!checkKnives) {
        pool = &work->tasks;
        TaskPoolUpdate(pool);
        return 1;
    }

    if (!BosBoogieAnyKnifeActive(work)) {
        ClearBtlObjActionFlags(e);

        return 0;
    }

    for (i = 0; i <= 4; i++) {
        pool = &work->tasks;

        if (IsTaskActive(work->knives[i])) {
            if (BosBoogieKnifeIsLanded(work->knives[i]->work)) {
                m4aSongNumStart(SONG_BTL_BU_TRAP);
            }

            break;
        }
    }

    TaskPoolUpdate(pool);

    return 1;
}

void task_bos_boogie_knifereader_2(BoogieKnifereaderWork* work) {
    TaskPoolDraw(&work->tasks);
}

void task_bos_boogie_knifereader_3(BoogieKnifereaderWork* work) {
    ReleaseEnemyBtlObj(&work->obj);
    TaskPoolDestroy(&work->tasks);
}

void task_bos_boogie_kaihuku_0(BoogieKaihukuWork* work, BoogieWork* arg) {
    s32 c;
    s32 d;
    s32 e;

    work->state = 2;
    work->timer = 0;
    work->boogie = arg;
    work->vz = 0;
    c = arg->actor.x;
    d = arg->actor.y + 0x100;
    e = arg->actor.z - 0x7C00;
    InitEnemyBtlObj(&work->obj, &sBosBoogieKaihukuEmyKind, c, d, e);
    work->obj.flags |= 0x400;
    work->tiles = LoadObjTiles(gKaifukuTiles, 0x400);
    work->palette = LoadObjPalette(gKaifukuPalette, 32);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    AnimInit(&work->anim, gKaifukuAnims, gKaifukuFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    RequestEnemyCardUse(&work->obj);
}

u8 task_bos_boogie_kaihuku_1(BoogieKaihukuWork* work) {
    BtlObj* p = &work->obj;
    BoogieWork* arg = work->boogie;
    BtlObj* q = &arg->actor;

    switch (UpdateBtlObjReaction(p)) {
    case BTL_REACTION_CARD_ACTION:
        work->state = 0;
        work->timer = 0;
        break;
    case BTL_REACTION_HEALED:
    default:
        if (!ConsumeGimmickFlag(0)) {
            break;
        }

        BosBoogieApplyGimmick();
    case BTL_REACTION_HURT:
    case BTL_REACTION_DEFEATED:
    case BTL_REACTION_CARD_BROKEN:
    case BTL_REACTION_STUNNED:
    case BTL_REACTION_GRAVITY:
    case BTL_REACTION_GRAVITY_DEFEATED:
        if (work->state != 1) {
            work->state = 1;
            work->timer = 0;
        }

        break;
    }

    switch (work->state) {
    case 0:
        BtlMapSetCameraTarget(p->x, p->y + p->z);

        if ((s16)work->timer == 0) {
            BgFxStartBoogieKaihuku(p->x, p->y, p->z + 0x2800, 0x199);
            m4aSongNumStart(SONG_BTL_BU_KAIFUKU);
            work->timer++;
            break;
        }

        if (BgFxIsActive()) {
            break;
        }

        CreateBtlPopTask(q, 10);
        arg = work->boogie;
        arg->actor.hp += arg->actor.maxHp / 16;
        arg = work->boogie;

        if (arg->actor.hp > arg->actor.maxHp) {
            arg->actor.hp = arg->actor.maxHp;
        }

        return 0;
    case 1:
        if (p->z >= 0) {
            gBosBoogieTaskKnockedDown = 1;
            ClearBtlObjActionFlags(p);

            return 0;
        }

        work->timer++;
        p->z += work->vz;
        work->vz += 0x42;

        if (p->z < -0x2000) {
            p->z = 0;
        }

        break;
    case 2:
        if ((s16)work->timer > 30) {
            return 0;
        }

        work->timer++;
        break;
    }

    AnimUpdate(&work->anim);
    ColliderSetPosition(&p->collider, p->x, p->y, p->z);

    return 1;
}

void task_bos_boogie_kaihuku_2(BoogieKaihukuWork* work) {
    BtlObj* p = &work->obj;
    void* d;
    u16 v;
    s16 x;
    s16 y;

    if (work->state != 2) {
        v = GetBattleSpritePriorityFlags(p->y);
        d = work->palette;
        WorldToScreen(&x, &y, p->x, p->y, p->z);
        DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, d, NULL, v, -0x1004 - (p->y >> 8) * 4);
    }
}

void task_bos_boogie_kaihuku_3(BoogieKaihukuWork* work) {
    ReleaseEnemyBtlObj(&work->obj);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
}
