#include "macros.h"
#include "boss_map_block_assets.h"
#include "bos4.h"
#include "sprites_bos4.h"
#include "gba/io_reg.h"
#include "system_state.h"
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
#include "boss_boogie.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "card_api.h"
#include "display.h"
#include "engine_math.h"
#include "listpool.h"
#include "m4a_song.h"
#include "map_types.h"
#include "obj.h"
#include "obj_api.h"
#include "registration_data.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

void task_bos_boogie_saku_2(BoogieSakuWork* work);
u8 task_bos_ursula_1(UrsulaWork* work);

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

static const BosMapanimeDef sUnk_096FE034 = { sBosBoogieMapanimeFrames, 5, 0, gUnk_097ED478, 0X7C00, 0X0100, 0X0300, 0, 0 };

static const BosMapanimeDef sUnk_096FE04C = { sBosBoogieMapanimeFrames, 5, 0, gUnk_097ED578, 0X7D00, 0X0100, 0X0300, 0, 0 };

static const BosMapanimeDef sUnk_096FE064 = { sBosBoogieMapanimeFrames, 5, 0, gUnk_097ED678, 0X7E00, 0X0100, 0X0300, 0, 0 };

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

static const EmyKind sBosUrsulaEmyKind = { 35, 0, 32, 24, 0, 0, 0 };

static const BattleBackgroundDef sBosUrsulaBattleBackgroundDef = {
    gUnk_097EE378, 0x7000, { 0, 0 }, gUnk_0984AFF8, 0xe0, { 0, 0 }, { gUnk_09843798, gUnk_09843F98, gUnk_09844798, gUnk_09844F98 }
};

static const u16* sBosUrsulaMapBlocksLeft[12] = {
#if defined(VERSION_US)
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_09845798,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
#elif defined(VERSION_JP)
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_097FAC6C,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
#elif defined(VERSION_EU)
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_09819E40,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
#endif
};

static const u16* sBosUrsulaMapBlocksHurtLeft[12] = {
#if defined(VERSION_US)
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_09845F98,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
#elif defined(VERSION_JP)
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_097FB46C,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
#elif defined(VERSION_EU)
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_0981A640,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
#endif
};

static const u16* sBosUrsulaMapBlocksRight[12] = {
#if defined(VERSION_US)
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_09846798,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
#elif defined(VERSION_JP)
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_097FBC6C,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
#elif defined(VERSION_EU)
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_0981AE40,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
#endif
};

static const u16* sBosUrsulaMapBlocksHurtRight[12] = {
#if defined(VERSION_US)
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_09846F98,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_08125E24,
#elif defined(VERSION_JP)
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_097FC46C,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_08125EA0,
#elif defined(VERSION_EU)
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_0981B640,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_08124944,
#endif
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

static const BosMapanimeDef sBosUrsulaMapanimeIdle = { sBosUrsulaMapanimeIdleFrames, 6, 0, gUnk_097F5378, 0X0C00, 0X0300, 0X0400, 0, 0 };

static const BosMapanimeDef sBosUrsulaMapanimeWindup = { sBosUrsulaMapanimeWindupFrames, 12, 0, gUnk_097F5E78, 0X0C00, 0X0860, 0X0C00, 0, 0 };

static const BosMapanimeDef sBosUrsulaMapanimeBubble = { sBosUrsulaMapanimeBubbleFrames, 5, 0, gUnk_097F8AD8, 0X0C00, 0X0860, 0X0C00, 0, 0 };

static const BosMapanimeDef sBosUrsulaMapanimeCharge = { sBosUrsulaMapanimeChargeFrames, 5, 0, gUnk_097FC338, 0X0C00, 0X0860, 0X0C00, 0, 0 };

static const BosMapanimeDef sBosUrsulaMapanimeRecover = { sBosUrsulaMapanimeRecoverFrames, 1, 0, gUnk_097EEF78, 0X0C00, 0X0860, 0X0C00, 0, 0 };

static TaskDesc sTaskDescBosUrsulaMapanime = {
    "task_bos_ursula_mapanime",
    (TaskInitFunc)task_bos_ursula_mapanime_0,
    (TaskUpdateFunc)task_bos_ursula_mapanime_1,
    (TaskDrawFunc)task_bos_ursula_mapanime_2,
    (TaskDestroyFunc)task_bos_ursula_mapanime_3,
    sizeof(UrsulaMapanimeWork),
};

UrsulaWork* gUrsulaWork;

UrsulaMapanimeWork* gUrsulaMapanimeWork;

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

    if (work->follower == 0) {
        RequestEnemyCardUse(&work->obj);
    }
}

u8 task_bos_boogie_dice_1(BoogieDiceWork* work) {
    BtlObj* p = &work->obj;

    if (work->follower == 0) {
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
            if (ConsumeGimmickFlag(0) != 0) {
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
        if (BosBoogieDiceIsHeld(work) != 0) {
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

        if (p->collider.colliding != 0 && work->scaleY > 255 && work->scaleX > 255) {
            work->speed = work->speed * 230 >> 8;
            p->x += p->collider.pushX;
            p->y += p->collider.pushY;
            work->angle = work->angle + (100 + GetRandom() % 57);
        }

        if (ClampBoogieDicePosition(&p->x, &p->y, 0, 0) != 0) {
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

                if (work->follower == 0) {
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

        if ((s16)work->timer == 0 && work->follower == 0) {
            ClearBtlObjActionFlags(p);
            gBosBoogieDiceBreakCount++;
            work->counted = 1;
        }

        work->timer++;
        BosBoogieDiceGrow(work);

        if (p->collider.colliding != 0 && work->scaleY > 255 && work->scaleX > 255) {
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
        if ((s16)work->timer > 59) {
            work->state = 6;
            break;
        }

        work->timer++;
        work->vz += 51;
        p->x += gSineTable[work->angle] * work->speed >> 8;
        p->y += -gSineTable[work->angle + 0x40] * work->speed >> 8;

        if (p->collider.colliding != 0 && work->scaleY > 255 && work->scaleX > 255) {
            work->speed = work->speed * 230 >> 8;
            p->x += p->collider.pushX;
            p->y += p->collider.pushY;
            work->angle = work->angle + (100 + GetRandom() % 57);
        }

        if (ClampBoogieDicePosition(&p->x, &p->y, 0, 0) != 0) {
            work->angle = work->angle + (100 + GetRandom() % 57);
        }

        if (p->z > 0) {
            p->z = 0;
            work->vz = -(work->vz * 179 >> 8);
        }

        break;
    case 2:
        if (work->follower == 0 && gBosBoogieGimmickCardDropped == 0 && GetRandom() % 16 <= 7) {
            gBosBoogieGimmickCardDropped = 1;
            _0801C1F8(0, p->x, p->y, p->z);
        }

        SetBtlObjUnhittable(p, 1);

        return 0;
    case 4:
        if (AnimIsFinished(&work->anim) != 0) {
            work->state = 5;
            work->timer = 0;
        }

        break;
    case 5:
        if ((s16)work->timer > 20) {
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
        if ((s16)work->timer > 10) {
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
        if ((s16)work->timer > 30) {
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

    if (BosBoogieDiceIsHeld(work) != 0) {
        return;
    }

    c = GetBattleSpritePriorityFlags(p->y);

    if (StepHitFlash(p) != 0) {
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
    if (work->counted == 0 && gBosBoogieDiceBreakCount != 3 && work->follower == 0 && work->state != 10) {
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

    if (work->follower == 0) {
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
    work->unk_154 = GetRandom() % 437 + 76;
    work->unk_158 = GetRandom() % 128 + 0x40;
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

    if (BosBoogieExplosiondiceIsHeld(work) != 0) {
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
        if (BgFxIsActive() == 0) {
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

    if (f != 0 || work->state == 1) {
        return;
    }

    c = GetBattleSpritePriorityFlags(p->y);
    pal = work->palette;
    WorldToScreen(&x, &y, p->x, p->y, p->z);
    DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, pal, 0, c,
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

u8 BosBoogieIsActorPastSaku(void) {
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
    work->task = 0;
    work->closePending = 0;
}

u8 task_bos_boogie_saku_1(BoogieSakuWork* work) {
    u8 f;

    if (gBosBoogieDiceBreakCount > 2 && AnimIsFinished(&work->anim) != 0) {
        if (work->openTimer < gBosBoogieSakuOpenTime) {
            if (work->openTimer == 0) {
                BtlMapStartShake();
            }

            work->openTimer++;
            SetBattleBounds(0x80, 0x170, 0x228, 0x278);

            if (BosBoogieIsActorPastSaku() != 0) {
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

            if (BosBoogieIsActorPastSaku() != 0) {
                work->task = TaskCreate(&work->tasks, &sTaskDescBosBoogieExplosiondice, work->boogie);
            }
        }
    }

    if (gBosBoogieDiceBreakCount <= 2 && IsTaskActive(work->task) == 0) {
        SetBattleBounds(0x80, 0x170, 0x240, 0x278);

        if (gBosBoogieDiceBreakCount != 0) {
            AnimChange(&work->anim, gBosBoogieDiceBreakCount, 0);
        } else if (work->closePending != 0) {
            AnimChange(&work->anim, 3, 0);
            work->closePending = 0;
        }
    }

    f = AnimIsFinished(&work->anim);

    if (gBosBoogieDiceBreakCount > 2
            || (gBosBoogieDiceBreakCount == 0 && AnimGetId(&work->anim) == 3
                && IsTaskActive(work->task) == 0)) {
        AnimUpdate(&work->anim);
    }

    if (f == 0 && AnimIsFinished(&work->anim) != 0) {
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
    DrawSprite(x, y + 1, AnimGetGfx(&work->anim), work->tiles, work->palette, 0, b, 0xE700);
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

u8 task_bos_boogie_map_1(void) {
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
    BosMapanimeInit(&work->anims[0], &sUnk_096FE034);
    BosMapanimeInit(&work->anims[1], &sUnk_096FE04C);
    BosMapanimeInit(&work->anims[2], &sUnk_096FE064);
}

u8 task_bos_boogie_mapanime_1(BoogieMapanimeWork* work) {
    u32 i;
    u8 r = 0;

    for (i = gBosBoogieDiceBreakCount; i <= 2; i++) {
        r = BosMapanimeUpdate(&work->anims[i], work->anims[i].def, r);
    }

    return 1;
}

void task_bos_boogie_mapanime_2(void) {
}

void task_bos_boogie_mapanime_3(void) {
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
        if (ConsumeGimmickFlag(0) == 0) {
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

        if (ClampBoogieDiskPosition(&p->x, &p->y, 0x20, -0x10, p->z) != 0) {
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

    if (gBosBoogieKnivesMoveRight != 0) {
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

    if (gBosBoogieKnivesMoveRight != 0) {
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

    if (gBosBoogieKnivesRetract != 0) {
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

    if (gBosBoogieKnivesRetract != 0 && (gFrameCounter & 1) != 0 && gBtlWork->paused == 0) {
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
        if (IsTaskActive(work->knives[i]) != 0) {
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
        work->knives[i] = 0;
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
        if (ConsumeGimmickFlag(0) == 0) {
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

    if (checkKnives == 0) {
        pool = &work->tasks;
        TaskPoolUpdate(pool);
        return 1;
    }

    if (BosBoogieAnyKnifeActive(work) == 0) {
        ClearBtlObjActionFlags(e);

        return 0;
    }

    for (i = 0; i <= 4; i++) {
        pool = &work->tasks;

        if (IsTaskActive(work->knives[i]) != 0) {
            if (BosBoogieKnifeIsLanded(work->knives[i]->work) != 0) {
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
        if (ConsumeGimmickFlag(0) == 0) {
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

        if (BgFxIsActive() != 0) {
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
        DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, d, 0, v, -0x1004 - (p->y >> 8) * 4);
    }
}

void task_bos_boogie_kaihuku_3(BoogieKaihukuWork* work) {
    ReleaseEnemyBtlObj(&work->obj);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
}

void BosUrsulaUpdateMapBlocks(UrsulaWork* work) {
    if (work->state >= 3 && work->state <= 4) {
        if (work->obj.x > gBtlWork->actor->x) {
            if (work->mapBlocks != sBosUrsulaMapBlocksHurtLeft) {
                work->mapBlocks = sBosUrsulaMapBlocksHurtLeft;
                SetBgMapBlocks(0, sBosUrsulaMapBlocksHurtLeft, 4, 3);
            } else {
                BosUrsulaStartAttack(0);
            }
        } else {
            if (work->mapBlocks != sBosUrsulaMapBlocksHurtRight) {
                work->mapBlocks = sBosUrsulaMapBlocksHurtRight;
                SetBgMapBlocks(0, sBosUrsulaMapBlocksHurtRight, 4, 3);
            } else {
                BosUrsulaStartAttack(0);
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
    if (work->gimmickTimer == 0 && BosUrsulaTakoIsBusy(work->tako->work) == 0 && BosUrsulaTakoIsBusy(work->tako2->work) == 0) {
        return 1;
    }

    return 0;
}

void task_bos_ursula_0(UrsulaWork* work) {
    u8 v;

    gUrsulaWork = work;
    gBosUrsulaActive = 1;
    TaskCreate(&gBtlWork->taskPools[1], &sTaskDescBosUrsulaMap, (void*)&sBosUrsulaBattleBackgroundDef);
    TaskCreate(&gBtlWork->taskPools[0], &sTaskDescBosUrsulaBorder, 0);
    work->state = 0;
    work->timer = 0;
    work->mapBlocks = 0;
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
    TaskCreate(&work->tasks, &sTaskDescBosUrsulaMapanime, 0);
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
        return 1;
    }

    return 3;
}

s32 BosUrsulaChooseAttackPhase1(UrsulaWork* work) {
    if (work->obj.x - 0x3800 < gBtlWork->actor->x && gBtlWork->actor->x < work->obj.x + 0x3800) {
        return 3;
    }

    if (work->obj.x - 0x6800 < gBtlWork->actor->x && gBtlWork->actor->x < work->obj.x + 0x6800) {
        return 2;
    }

    return 1;
}

s32 BosUrsulaChooseAttackPhase2(UrsulaWork* work) {
    if (gBtlWork->actor->z <= -0x5000) {
        return 3;
    } else {
        if (work->obj.x - 0x3800 < gBtlWork->actor->x && gBtlWork->actor->x < work->obj.x + 0x3800) {
            if ((u16)(GetRandom() % 100) < 50) {
                return 3;
            }

            return 1;
        }
    }

    if (work->obj.x - 0x8000 < gBtlWork->actor->x && gBtlWork->actor->x < work->obj.x + 0x8000) {
        return 2;
    }

    return 1;
}

s32 BosUrsulaChooseAttack(UrsulaWork* work) {
    switch (BosUrsulaGetHpPhase()) {
    case 0:
        return BosUrsulaChooseAttackPhase0(work);
    case 1:
        return BosUrsulaChooseAttackPhase1(work);
    case 2:
    default:
        return BosUrsulaChooseAttackPhase2(work);
    }
}

void BosUrsulaRecoverPendingTakos(UrsulaWork* work) {
    if (work->takoRecoverPending != 0) {
        BosUrsulaTakoEndDown(work->tako->work);
        BosUrsulaTakoEndDown(work->tako2->work);
        work->takoRecoverPending = 0;
    }
}

void BosUrsulaUpdateTakoRecovery(UrsulaWork* work) {
    if (work->gimmickTimer == 0 && BosUrsulaTakoIsStoodOn(work->tako->work) == 0 && BosUrsulaTakoIsStoodOn(work->tako2->work) == 0) {
        BosUrsulaRecoverPendingTakos(work);
        work->takoRecoverPending = 1;
    } else {
        work->takoRecoverPending = 0;
    }
}

u16 BosUrsulaGetCardInterval(void) {
    switch (BosUrsulaGetHpPhase()) {
    case 0:
        return 150;
    case 1:
        return 120;
    case 2:
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
        work->state = 1;
        work->timer = 0;
        break;
    case BTL_REACTION_HURT:
    case BTL_REACTION_STUNNED:
    case BTL_REACTION_GRAVITY:
        BosUrsulaUpdateTakoRecovery(work);
        work->state = 3;
        work->timer = 0;
        break;
    case BTL_REACTION_DEFEATED:
    case BTL_REACTION_GRAVITY_DEFEATED:
        work->state = 4;
        work->timer = 0;
        break;
    case BTL_REACTION_CARD_BROKEN:
        work->state = 2;
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

        if (work->state == 1) {
            work->state = 2;
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

            if (work->gimmickTimer == 0 && work->state == 4) {
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
    case 1:
        if ((s16)work->timer == 0) {
            BosUrsulaStartAttack(BosUrsulaChooseAttack(work));
            work->timer = 1;
        } else {
            if (BosUrsulaIsCharging()) {
                BosUrsulaMoveForward(work);
            }

            if (!BosUrsulaIsAttacking()) {
                ClearBtlObjActionFlags(p);
                work->state = 0;
            }
        }

        break;
    case 2:
        ClearBtlObjActionFlags(p);
        work->state = 0;
        BosUrsulaStartAttack(0);
        break;
    case 3:
        if ((s16)work->timer > 20) {
            ClearBtlObjActionFlags(p);

            if (BosUrsulaGetHpPhase() == 1 && !BosUrsulaIsGimmickActive()) {
                work->state = 5;
            } else {
                work->state = 0;
            }

            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 4:
        if ((s16)work->timer == 0) {
            BeginBossDefeat(p);
            BosUrsulaUpdateMapBlocks(work);
            work->timer++;
        } else if ((s16)work->timer == 1) {
            work->timer++;
        } else if ((s16)work->timer == 2) {
            if (BosUrsulaIsFacingLeft()) {
                x = p->x + 0x1400;
            } else {
                x = p->x - 0x1C00;
            }

            BgFxStartBossDeath(x, p->y + p->z + 0x1C00);
            FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
            work->timer++;
        } else if ((s16)work->timer == 3) {
            if (!FadeIsActive()) {
                work->timer++;
            }
        } else if ((s16)work->timer < 124) {
            work->timer++;

            if ((s16)work->timer == 124) {
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
    case 0:
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
                work->state = 5;
            }

            if (BosUrsulaGetHpPhase() == 2) {
                if (((p->x - gBtlWork->actor->x) >= 0 ? p->x - gBtlWork->actor->x : -(p->x - gBtlWork->actor->x)) > 0x6800) {
                    work->state = 5;
                }
            }
        }

        BosUrsulaUpdateBob(work);
        break;
    case 5:
        if (BosUrsulaIsGimmickActive()) {
            BosUrsulaUpdateBob(work);
        } else {
            if (!BosUrsulaMoveForward(work)) {
                p->flags ^= BTLOBJ_FLAG_FACING_LEFT;
            }

            if (BosUrsulaGetHpPhase() == 2 && p->x > 0x6800 && p->x < 0x19800) {
                if (((p->x - gBtlWork->actor->x) >= 0 ? p->x - gBtlWork->actor->x : -(p->x - gBtlWork->actor->x)) < 0x6800 && BosUrsulaIsGuarded(work)) {
                    RequestEnemyCardUse(&work->obj);
                    work->state = 0;
                }
            }

            if ((!(p->flags & BTLOBJ_FLAG_FACING_LEFT) && p->x == 0x6800) || ((p->flags & BTLOBJ_FLAG_FACING_LEFT) && p->x == 0x19800)) {
                work->state = 0;
            }
        }

        break;
    }

    if (work->state != 4) {
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

u8 BosUrsulaIsFacingLeft(void) {
    return gUrsulaWork->obj.flags & BTLOBJ_FLAG_FACING_LEFT;
}

u8 BosUrsulaIsGimmickActive(void) {
    if (gUrsulaWork->gimmickTimer == 0) {
        return 0;
    }

    return 1;
}

u8 BosUrsulaObjectsGone(void) {
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

u8 BosUrsulaIsGimmickStarting(void) {
    if (BosUrsulaObjectsGone() != 0 || BosUrsulaIsGimmickActive() == 0 || gUrsulaWork->gimmickDelay == 0) {
        return 0;
    }

    return 1;
}

u8 func_080DC5B0(void) {
    if (BosUrsulaIsGimmickActive() != 0 && (gUrsulaWork->sinkSteps != 0 || gUrsulaWork->riseSteps != 0 || gUrsulaWork->unk_15C != 0)) {
        return 1;
    }

    return 0;
}

u32 BosUrsulaGetHpPhase(void) {
    UrsulaWork* work = gUrsulaWork;

    if (work->obj.hp > (s16)(work->obj.maxHp / 3) * 2) {
        return 0;
    }

    if (work->obj.hp > (s16)(work->obj.maxHp / 3)) {
        return 1;
    }

    return 2;
}

u8 BosUrsulaIsDefeated(void) {
    if (gUrsulaWork->state == 4) {
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

    if (BosUrsulaIsGimmickStarting() != 0) {
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

    if (func_080DC5B0() != 0 && work->viewYMaxTarget == 0x1E000) {
        work->viewYMaxTarget = 0x22000;
        work->viewYMaxSteps = 20;
    } else if (func_080DC5B0() == 0 && work->viewYMaxTarget == 0x22000) {
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

    if (v > 0xA0 || gBosUrsulaActive == 0) {
        gDispCnt &= ~DISPCNT_WIN0_ON;
    } else {
        gDispCnt |= DISPCNT_WIN0_ON;
        gWin0V = (v << 8) | 0xA0;
    }

    return 1;
}

void task_bos_ursula_map_3(void) {
}

void task_bos_ursula_border_0(UrsulaBorderWork* work) {
    work->tiles = LoadObjTiles(gUnk_0979D0B6, 0x800);
    work->palette = LoadObjPalette(gUnk_0984B0D8, 0x20);
    SetBtlPaletteFadeExcluded(work->palette->index + 16, 0);
}

s32 task_bos_ursula_border_1(void) {
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
    DrawSprite(a, b, gUnk_0979D090, work->tiles, work->palette, 0, SPRITE_PRIORITY(2), 0xFB00);
    DrawSprite(c, d, gUnk_0979D8B8, work->tiles, work->palette, 0, SPRITE_PRIORITY(2), 0xFB00);
}

void task_bos_ursula_border_3(UrsulaBorderWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void BosUrsulaTakoGetPosition(s32* a, s32* b, s32* c, UrsulaTakoWork* d) {
    s32* p;
    s32 t;

    *a = gBtlWork->bossX + d->offsetX;

    if (d->isLeft != 0) {
        if (BosUrsulaIsFacingLeft() != 0) {
            *a += -0x2200;
        } else {
            *a += -0x3600;
        }
    } else {
        if (BosUrsulaIsFacingLeft() != 0) {
            *a += 0x3600;
        } else {
            *a += 0x2200;
        }
    }

    *b = gBtlWork->bossY;
    p = &gBtlWork->bossZ;
    t = d->offsetZ + 0x5000;
    *c = *p + t;
}

s32 BosUrsulaGetTakoPlatformRadius(u8 a) {
    if (a == BosUrsulaIsFacingLeft()) {
        return 12;
    }

    return 6;
}

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

    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF6860, 6), gUnk_0979E344);
    work->palette = LoadObjPalette(gUnk_0984B0F8, 32);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    AnimInit(&work->anim, gUnk_09EF68A0, gUnk_09EF6860);
    AnimStart(&work->anim, (u16)(work->animBase + 4), ANIM_FLAG_LOOP);
    work->state = 0;
    ColliderInit(&work->collider, 7, (u16)BosUrsulaGetTakoPlatformRadius(work->isLeft), 1);
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
    } else if (work->state <= 1) {
        SetBtlObjUnhittable(p, 0);
    }

    if (BosUrsulaIsDefeated()) {
        return 1;
    }

    switch (UpdateBtlObjReaction(p)) {
    case BTL_REACTION_CARD_ACTION:
        work->state = 7;
        work->timer = 0;
        RequestBossCardRandom();
        break;
    case BTL_REACTION_HURT:
    case BTL_REACTION_STUNNED:
    case BTL_REACTION_GRAVITY:
        work->state = 1;
        work->timer = 0;
        break;
    case BTL_REACTION_DEFEATED:
    case BTL_REACTION_GRAVITY_DEFEATED:
        work->state = 2;
        work->timer = 0;
        break;
    case BTL_REACTION_CARD_BROKEN:
        ClearBtlObjActionFlags(p);
        work->state = 0;
        RequestBossCardRandom();
        break;
    }

    switch (work->state) {
    case 0:
        AnimChange(&work->anim, (u16)(work->animBase + 4), ANIM_FLAG_LOOP);
        break;
    case 1:
        if (work->timer == 0) {
            AnimChange(&work->anim, (u16)(work->animBase + 7), 0);
        }

        work->timer++;

        if (AnimIsFinished(&work->anim)) {
            ClearBtlObjActionFlags(p);
            work->state = 0;
            work->timer = 0;
        }

        break;
    case 2:
        if (AnimGetId(&work->anim) == (s16)work->animBase + 4) {
            if (AnimGetFrame(&work->anim) == 0 && AnimIsFrameEnding(&work->anim)) {
                AnimStart(&work->anim, (u16)(work->animBase + 5), ANIM_FLAG_LOOP);
                SetBtlObjUnhittable(p, 1);

                if ((u16)(GetRandom() % 100) <= 19) {
                    _0801C1F8(0, p->x, p->y, p->z);
                }
            }
        } else if (AnimGetId(&work->anim) == (s16)work->animBase + 5) {
            if (AnimIsFinished(&work->anim)) {
                ClearBtlObjActionFlags(p);
                work->state = 3;
                work->timer = 0;
            }
        } else {
            AnimStart(&work->anim, (u16)(work->animBase + 4), ANIM_FLAG_LOOP);
        }

        break;
    case 3:
        if (work->timer > 180) {
            work->state = 4;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 4:
        if (work->timer > 180) {
            AnimStart(&work->anim, (u16)(work->animBase + 6), 0);
            work->state = 5;
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
    case 5:
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

            work->state = 6;
            work->timer = 0;
        } else {
            ApproachValue(&work->offsetZ, 0, work->timer);
            ApproachValue(&work->offsetX, 0, work->timer);
            work->timer--;
        }

        break;
    case 6:
        if (work->timer > 30) {
            work->state = 0;
        } else {
            work->timer++;
        }

        break;
    case 7:
        AnimChange(&work->anim, (u16)(work->animBase + 6), 0);

        if (AnimIsFinished(&work->anim) || BosUrsulaIsGimmickActive()) {
            work->state = 0;
            AnimStart(&work->anim, (u16)(work->animBase + 4), ANIM_FLAG_LOOP);
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

    if (work->state == 3 && gBtlWork->actor->z <= -0x2000 && gBtlWork->actor->z > -0x3000) {
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

    if (work->state != 4 && BosUrsulaIsGimmickActive() == 0) {
        pal = StepHitFlash(p) != 0 ? work->palette2 : work->palette;
        WorldToScreen(&x, &y, p->x, p->y, p->z);
        DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, pal, 0, SPRITE_PRIORITY(2), 0xFC00);
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
    if (work->state <= 1) {
        return 0;
    }

    return 1;
}

void BosUrsulaTakoEndDown(UrsulaTakoWork* work) {
    if (work->state >= 3 && work->state <= 4) {
        work->state = 4;
        work->timer = 180;
    }
}

u8 BosUrsulaTakoIsStoodOn(UrsulaTakoWork* work) {
    if (work->collider.standFlags & COLLIDER_STAND_STOOD_ON) {
        return 1;
    }

    return 0;
}

void BosUrsulaBacktakoGetPosition(s32* a, s32* b, s32* c, UrsulaBacktakoWork* d) {
    s32* p;
    s32 t;

    *a = gBtlWork->bossX + d->offsetX;

    if (d->isLeft != 0) {
        if (BosUrsulaIsFacingLeft() != 0) {
            *a += -0x4A00;
        } else {
            *a += -0x5E00;
        }
    } else {
        if (BosUrsulaIsFacingLeft() != 0) {
            *a += 0x5E00;
        } else {
            *a += 0x4A00;
        }
    }

    *b = gBtlWork->bossY + 0x800;
    p = &gBtlWork->bossZ;
    t = d->offsetZ + 0x5000;
    *c = *p + t;
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

    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF6860, 8), gUnk_0979E344);
    work->palette = LoadObjPalette(gUnk_0984B0F8, 32);
    AnimInit(&work->anim, gUnk_09EF68A0, gUnk_09EF6860);
    AnimStart(&work->anim, (u16)(work->animBase + 4), ANIM_FLAG_LOOP);
    AnimSetFrame(&work->anim, GetRandom() % work->anim.frameCount + 1);
}

u8 task_bos_ursula_backtako_1(UrsulaBacktakoWork* work) {
    if (BosUrsulaIsDefeated() == 0) {
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

    if (f != 0) {
        return;
    }

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, work->palette, 0, SPRITE_PRIORITY(3),
        0xFE00);
    WorldToScreen(&x, &y, work->x2, work->y2, work->z2);
    DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, work->palette, 0, SPRITE_PRIORITY(3) | SPRITE_FLAG_HFLIP,
        0xFE00);
}

void task_bos_ursula_backtako_3(UrsulaBacktakoWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_bos_ursula_mapanime_0(UrsulaMapanimeWork* work) {
    gUrsulaMapanimeWork = work;
    TaskPoolInit(&work->tasks, 1);
    work->task = 0;
    work->attack = 4;
    BosUrsulaStartAttack(0);
}

u8 task_bos_ursula_mapanime_1(UrsulaMapanimeWork* work) {
    s32 d;

    BosMapanimeUpdate(&work->anim, work->anim.def, 0);

    if (BosMapanimeIsAtEnd(&work->anim) != 0) {
        if (work->anim.def == &sBosUrsulaMapanimeWindup) {
            if (work->attack == 1) {
                BosMapanimeInit(&work->anim, &sBosUrsulaMapanimeBubble);
                work->attack = 4;
            } else if (work->attack == 2) {
                BosMapanimeInit(&work->anim, &sBosUrsulaMapanimeCharge);
                work->attack = 4;
            }
        } else if (work->anim.def == &sBosUrsulaMapanimeBubble
                || work->anim.def == &sBosUrsulaMapanimeCharge) {
            BosMapanimeInit(&work->anim, &sBosUrsulaMapanimeRecover);
            work->attack = 4;
        } else if (work->anim.def == &sBosUrsulaMapanimeRecover) {
            BosMapanimeInit(&work->anim, &sBosUrsulaMapanimeIdle);
            work->attack = 0;
        }
    }

    if (work->anim.def == &sBosUrsulaMapanimeCharge && BosMapanimeGetFrameIndex(&work->anim) == 2) {
        if (work->attackSpawned == 0) {
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
            && work->attackSpawned == 0) {
        work->attackSpawned = 1;
        work->task = TaskCreate(&work->tasks, &gTaskDescBosUrsulaBubble, 0);
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

void BosUrsulaStartAttack(s32 a) {
    if (IsTaskActive(gUrsulaMapanimeWork->task) != 0) {
        if (strcmp(GetTaskName(gUrsulaMapanimeWork->task), "task_bos_ursula_bubble") == 0) {
            BosUrsulaPopBubbles(gUrsulaMapanimeWork->task->work);
        } else {
            TaskKill(&gUrsulaMapanimeWork->tasks, gUrsulaMapanimeWork->task);
        }
    }

    if (a == 3) {
        gUrsulaMapanimeWork->task = TaskCreate(&gUrsulaMapanimeWork->tasks, &gTaskDescBosUrsulaThunder, 0);
    } else if (gUrsulaMapanimeWork->attack != a) {
        gUrsulaMapanimeWork->attack = a;

        if (a == 0) {
            BosMapanimeInit(&gUrsulaMapanimeWork->anim, &sBosUrsulaMapanimeRecover);
            gUrsulaMapanimeWork->attackSpawned = 1;
        } else {
            BosMapanimeInit(&gUrsulaMapanimeWork->anim, &sBosUrsulaMapanimeWindup);
            gUrsulaMapanimeWork->attackSpawned = 0;
            m4aSongNumStart(SONG_VO_UR_ATTACK00);
        }
    }
}

u8 BosUrsulaIsAttacking(void) {
    if (gUrsulaMapanimeWork->anim.def == &sBosUrsulaMapanimeBubble || gUrsulaMapanimeWork->anim.def == &sBosUrsulaMapanimeCharge || gUrsulaMapanimeWork->anim.def == &sBosUrsulaMapanimeWindup) {
        return 1;
    }

    return IsTaskActive(gUrsulaMapanimeWork->task);
}

u8 BosUrsulaIsCharging(void) {
    if (gUrsulaMapanimeWork->anim.def == &sBosUrsulaMapanimeCharge && BosMapanimeGetFrameIndex(&gUrsulaMapanimeWork->anim) == 2) {
        return 1;
    }

    return 0;
}
