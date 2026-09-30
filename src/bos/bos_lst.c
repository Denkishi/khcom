#include "bos6.h"
#include "sprites_bos6.h"
#include "gba/io_reg.h"
#include "bos7_api.h"
#include "fade.h"
#include "songs.h"
#include <stdlib.h>
#include "bos7.h"

static const EmyKind sBosLstEmyKind = { 40, 256, 8, 8, 0, 128, 0 };

static const BattleBackgroundDef sBosLstBattleBackgroundDef = {
    gUnk_09CC5054, 0x8000, { 0, 0 }, gUnk_09D69454, 0x140, { 0, 0 }, { gUnk_09D4B274, gUnk_09D4B274, gUnk_09D4B274, gUnk_09D4B274 }
};

static const LstAnimDef sLstAnimDefs[8] = {
    { gUnk_09D4DA74, 0, 8, { 0, 0, 0, 0 }, 3, 47, { 0, 0 }, -15, 17, 61, 65535, 60, { 0, 0 }, -43, -17, 80, 72, 0, 72, { 0, 0 } },
    { gUnk_09D4FA74, 0, 8, { 1, 0, 0, 0 }, 65533, 47, { 1, 0 }, 15, 17, 61, 1, 60, { 1, 0 }, 43, -17, 80, 184, 0, 72, { 0, 0 } },
    { gUnk_09D4E274, 0, 8, { 0, 0, 0, 0 }, 3, 47, { 0, 0 }, -15, 17, 61, 65535, 60, { 0, 0 }, -43, -17, 80, 72, 0, 72, { 0, 0 } },
    { gUnk_09D50274, 0, 8, { 1, 0, 0, 0 }, 65533, 47, { 1, 0 }, 15, 17, 61, 1, 60, { 1, 0 }, 43, -17, 80, 184, 0, 72, { 0, 0 } },
    { gUnk_09D4EA74, 0, 8, { 0, 0, 0, 0 }, 3, 47, { 0, 0 }, -15, 17, 61, 65535, 60, { 0, 0 }, -43, -17, 80, 72, 0, 72, { 0, 0 } },
    { gUnk_09D50A74, 0, 8, { 1, 0, 0, 0 }, 65533, 47, { 1, 0 }, 15, 17, 61, 1, 60, { 1, 0 }, 43, -17, 80, 184, 0, 72, { 0, 0 } },
    { gUnk_09D4F274, 0, 8, { 0, 0, 0, 0 }, 3, 47, { 0, 0 }, -15, 17, 61, 65535, 60, { 0, 0 }, -43, -17, 80, 72, 0, 72, { 0, 0 } },
    { gUnk_09D51274, 0, 8, { 1, 0, 0, 0 }, 65533, 47, { 1, 0 }, 15, 17, 61, 1, 60, { 1, 0 }, 43, -17, 80, 184, 0, 72, { 0, 0 } },
};

static const u16 sBosLstBodyFrames[48] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1,
};

static const u8 sBosLstAnimSheets[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };

static const s32 sBosLstBobZ[16] = { -1, -2, -3, -4, -5, -6, -7, -8, -7, -6, -5, -4, -3, -2, -1, 0 };

static void* const sBosLstBgFrames[18][2] = {
    { gUnk_09CC5054, gUnk_09D4DA74 },
    { gUnk_09CCD054, gUnk_09D51A74 },
    { gUnk_09CCD694, gUnk_09D52274 },
    { gUnk_09CCDC14, gUnk_09D52A74 },
    { gUnk_09CCE1D4, gUnk_09D53274 },
    { gUnk_09CCE7F4, gUnk_09D53A74 },
    { gUnk_09CCEDB4, gUnk_09D54274 },
    { gUnk_09CCF374, gUnk_09D54A74 },
    { gUnk_09CCFA54, gUnk_09D55274 },
    { gUnk_09CC5054, gUnk_09D4FA74 },
    { gUnk_09CCD054, gUnk_09D55A74 },
    { gUnk_09CCD694, gUnk_09D56274 },
    { gUnk_09CCDC14, gUnk_09D56A74 },
    { gUnk_09CCE1D4, gUnk_09D57274 },
    { gUnk_09CCE7F4, gUnk_09D57A74 },
    { gUnk_09CCEDB4, gUnk_09D58274 },
    { gUnk_09CCF374, gUnk_09D58A74 },
    { gUnk_09CCFA54, gUnk_09D59274 },
};

TaskDesc gTaskDescBosLst = {
    "task_bos_lst",
    (TaskInitFunc)task_bos_lst_0,
    (TaskUpdateFunc)task_bos_lst_1,
    (TaskDrawFunc)task_bos_lst_2,
    (TaskDestroyFunc)task_bos_lst_3,
    sizeof(BosLstWork),
};

s32 BosLstSquare(s32 x) {
    return x * x;
}

s32 BosLstSquare2(s32 x) {
    return x * x;
}

void BosLstAdvanceEventStep(Task* task) {
    BosLstWork* work = task->work;

    work->eventStep = 1;
}

void BosLstSetMode(BosLstWork* work, u16 a, u16 b) {
    u16 zero;

    zero = 0;
    work->moveMode = a;
    work->attackKind = b;
    work->cardRequests = zero;
    work->breakCount = zero;
}

void BosLstRequestCardUse(BosLstWork* work) {
    RequestEnemyCardUse(&work->body);
    work->cardRequests += 1;
}

void BosLstDestroyTasks(BosLstWork* work) {
    u32 i;

    for (i = 0; i < 0x20; i++) {
        if (work->lstTasks[i] != NULL) {
            TaskKill(&gBtlWork->taskPools[1], work->lstTasks[i]);
        }
        work->lstTasks[i] = 0;
    }
}

u8 BosLstSpawnFal(BosLstWork* work, s32 a) {
    LstFalArg s;
    u8 r;
    TaskPool* pool;
    s32 range;
    s32 d1;
    s32 d2;
    s32 d3;
    s32 d4;
    s32 d5;
    s32 d6;
    s32 d7;

    r = 0;
    if (work->hidden == 0) {
        s.kind = a;
        s.facing = work->facing;
        s.falCount = &work->falCount;
        s.x = work->x;
        s.y = work->y + 0x400;
        s.z = work->z - 0x1400;
        switch (a) {
        default:
            s.x += work->facing << 12;
            d1 = (GetRandom() % 21 << 8) + 0x800;
            s.y -= d1;
            d2 = (GetRandom() % 17 << 8) - 0x800;
            s.z += d2;
            pool = &gBtlWork->taskPools[1];
            break;
        case 4:
            range = 0x800;
            d3 = (GetRandom() % 17 << 8) - range;
            s.x += d3;
            d4 = (GetRandom() % 17 << 8) - range;
            s.z += d4;
            s.angle = work->defeatTimer * 4;
            pool = &work->tasks;
            break;
        case 5:
            d5 = (GetRandom() % 33 << 8) - 0x1000;
            s.x += d5;
            d6 = (GetRandom() % 21 << 8) + 0x800;
            s.y -= d6;
            d7 = (GetRandom() % 65 << 8) - 0x2000;
            s.z += d7;
            pool = &work->tasks;
            break;
        }
        TaskCreate(pool, &gTaskDescBosLstFal, &s);
        r = 1;
    }
    return r;
}

void BosLstSetAnim(BosLstWork* work, u16 a, u16 b, u8 c) {
    u16 id;
    u16 v;

    id = a;
    v = id * 2;
    if (work->facing < 0) {
        v ^= 1;
    }
    if (work->turned == 1) {
        v ^= 1;
    }
    switch (sBosLstAnimSheets[a]) {
    case 0:
        SetObjTileSource(work->tiles, gUnk_09C4B012);
        AnimChangeWithTables(&work->anim, v, b, gUnk_09EFAD3C, gUnk_09EFABB0);
        break;
    case 1:
        v -= 14;
        SetObjTileSource(work->tiles, gUnk_09C51CBC);
        AnimChangeWithTables(&work->anim, v, b, gUnk_09EFADBC, gUnk_09EFAD74);
        break;
    }
    if (c == 1) {
        AnimChange(&work->anim, v, b);
    } else {
        AnimReset(&work->anim);
        AnimStart(&work->anim, v, b);
    }
    work->animId = id;
    work->animFlags = b;
    work->animFacing = work->facing;
}

void BosLstSetFacing(BosLstWork* work, s16 a) {
    u8 f;

    if (work->facing != a) {
        work->facing = a;
        BosLstSetAnim(work, work->animId, work->animFlags, 1);
        f = 1;
        if (work->facing > 0) {
            f = (work->turned ^ f) != 0;
        } else if (work->turned == 0) {
            f = 0;
        }
        if (f == 1) {
            work->body.flags |= BTLOBJ_FLAG_FACING_LEFT;
            work->sub[0].body.flags |= BTLOBJ_FLAG_FACING_LEFT;
            work->sub[1].body.flags |= BTLOBJ_FLAG_FACING_LEFT;
        } else {
            work->body.flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            work->sub[0].body.flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            work->sub[1].body.flags &= ~BTLOBJ_FLAG_FACING_LEFT;
        }
    }
}

s16 BosLstFindActiveSub(BosLstWork* work) {
    s16 r;

    r = -1;
    if (work->sub[0].defeated == 0) {
        r = 0;
    } else if (work->sub[1].defeated == 0) {
        r = 1;
    }
    return r;
}

u8 BosLstSetSubAnim(BosLstWork* work, u16 a) {
    s16 i;
    u8 r;

    r = 0;
    if (work->subsDefeated == 1) {
        work->sub[0].animId = 2;
        work->sub[1].animId = 2;
    } else {
        if (a == 0) {
            i = 0;
            if (work->sub[i].defeated == 1) {
                work->sub[i].animId = 2;
            } else {
                work->sub[i].animId = 0;
            }
            work->sub[i].restartAnim = 1;
            i = 1;
            if (work->sub[i].defeated == 1) {
                work->sub[i].animId = 2;
            } else {
                work->sub[i].animId = 0;
            }
            work->sub[i].restartAnim = 1;
        } else {
            i = BosLstFindActiveSub(work);
            work->sub[i].animId = a;
            i = i ^ 1;
            if (work->sub[i].defeated == 1) {
                work->sub[i].animId = 2;
            } else {
                work->sub[i].animId = 0;
            }
            work->sub[i].restartAnim = 1;
        }
        r = 1;
    }
    return r;
}

void BosLstTickCardDelay(BosLstWork* work) {
    s32 t;
    BtlObj* pos;

    t = work->cardDelay;
    work->cardDelay = t - 0x100;
    if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
        work->cardDelay = t - 0x200;
    }
    if (work->facing > 0) {
        pos = gBtlWork->actor;
        if (pos->x > work->x + 0x1000) {
            work->cardDelay -= 0x80;
        }
    } else {
        pos = gBtlWork->actor;
        if (pos->x < work->x - 0x1000) {
            work->cardDelay -= 0x80;
        }
    }
}

void BosLstUpdateBob(BosLstWork* work) {
    work->offsetZ = sBosLstBobZ[(work->bobFrame >> 2) & 15] << 8;
    work->bobFrame += 1;
    if (work->inEvent == 1) {
        work->offsetZ -= 0x1800;
    }
}

void task_bos_lst_0(BosLstWork* work, TaskPool* pool) {
    BtlObj* pos;
    void* obj;
    void* anim;
    const void* tbl;
    void* p;
    BtlWork* g;
    u32 i;

    if (pool == NULL) {
        work->inEvent = 0;
        work->eventStep = 0;
        work->task = TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosLstFld, (void*)&sBosLstBattleBackgroundDef);
        work->state = 0;
        work->x = 0x14000;
        work->z = -0x5400;
    } else {
        work->inEvent = 1;
        work->eventStep = 0;
        work->task = TaskCreate(pool, &gTaskDescBosLstFld, (void*)&sBosLstBattleBackgroundDef);
        work->state = 7;
        work->x = 0x1D000;
        work->z = -0x14400;
    }
    work->hidden = 0;
    work->subsDefeated = 0;
    work->step = 0;
    BosLstSetMode(work, 2, 1);
    work->bodyCycle = 0;
    work->facing = 1;
    work->flash = 0;
    work->prevFlash = 0xFFFF;
    work->y = 0x1F000;
    work->offsetX = 0;
    work->offsetY = 0;
    work->offsetZ = 0;
    pos = gBtlWork->actor;
    work->actorX = pos->x;
    work->actorY = pos->y;
    work->actorZ = pos->z;
#ifdef VERSION_EU
    work->unk_004 = 0;
#endif
    work->timer = 0;
    work->bobFrame = 0;
    work->frameCount = 0;
    work->platformTimer = 0;
    work->cardRequests = 0;
    work->breakCount = 0;
    work->falCount = 0;
    work->unk_076 = 0;
    work->unk_078 = 0;
    work->cardDelay = 0x1E000;
    work->groundCount = 0;
    work->kamaCount = 0;
    work->dashCount = 0;
    work->bitRound = 0;
    work->playerOnPlatform = 0;
    work->platformStep = 0;
    work->sub[0].defeated = 0;
    work->sub[0].unk_001 = 1;
    work->sub[0].restartAnim = 1;
    work->sub[0].state = 0;
    work->sub[0].timer = 0;
    work->sub[0].hurtTimer = 0;
    work->sub[0].animId = 0;
    work->sub[0].curAnimId = -1;
    work->sub[1].defeated = 0;
    work->sub[1].unk_001 = 0;
    work->sub[1].restartAnim = 1;
    work->sub[1].state = 0;
    work->sub[1].timer = 0;
    work->sub[1].hurtTimer = 0;
    work->sub[1].animId = 0;
    work->sub[1].curAnimId = -1;
    work->sub[0].tiles = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EFADC4, 16), gUnk_09C53724);
    work->sub[1].tiles = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EFAE54, 16), gUnk_09C58590);
    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EFABB0, 0x62), gUnk_09C4B012);
    work->palette = LoadObjPalette(gUnk_09D69594, 0x60);
    i = 0;
    obj = &work->body;
    anim = &work->anim;
    for (; i < 32; i++) {
        work->lstTasks[i] = 0;
    }
    tbl = &sBosLstEmyKind;
    InitEnemyBtlObj(obj, tbl, work->x, work->y, work->z);
    work->body.flags |= 0x200000000400;
    SetBtlObjUnhittable(obj, 1);
    obj = &work->sub[0].body;
    InitEnemyBtlObj(obj, tbl, work->x, work->y, work->z);
    do {
        work->sub[0].body.flags |= 0x400;
        SetEnemyHpFromStats(obj, 40, 0x100);
    } while (0);
    obj = &work->sub[1].body;
    InitEnemyBtlObj(obj, tbl, work->x, work->y, work->z);
    work->sub[1].body.flags |= 0x400;
    SetEnemyHpFromStats(obj, 40, 0x100);
    ColliderInit(&work->collider, 8, 20, 20);
    p = &work->collider2;
    ColliderInit(p, 8, 28, 64);
    ColliderSetDisabled(p, 1);
    for (i = 0; (s32)i < 8; i++) {
        ColliderInit(&work->colliders[i], 7, 24, 4);
        ColliderSetDisabled(&work->colliders[i], 1);
    }
    work->turned = 0;
    work->animId = 0;
    work->animFlags = 0;
    work->bgFrame = 0xFFFF;
    work->hittableTimer = 0;
    AnimInit(anim, gUnk_09EFAD3C, gUnk_09EFABB0);
    BosLstSetAnim(work, 0, 1, 0);
    AnimInit(&work->sub[0].anim, gUnk_09EFAE1C, gUnk_09EFADC4);
    AnimStart(&work->sub[0].anim, 0, ANIM_FLAG_LOOP);
    AnimInit(&work->sub[1].anim, gUnk_09EFAEAC, gUnk_09EFAE54);
    AnimStart(&work->sub[1].anim, 0, ANIM_FLAG_LOOP);
    TaskPoolInit(&work->tasks, 0x60);
    SetBtlPaletteFadeExcluded(0, 1);
    SetBtlPaletteFadeExcluded(1, 1);
    SetBtlPaletteFadeExcluded(2, 1);
    SetBattleActorPosition(0xCC00, 0x1F000, 0);
    LoadBgMap(1, gUnk_09D34A74, 0x1000);
    LoadBgMap(1, gUnk_09D4DA74, 0x800);
    LoadBgMap(0, gUnk_09D4B274, 0x800);
    g = gBtlWork;
    g->bossX = work->x;
    g->bossY = work->y;
    g->bossZ = work->z;
    g->bossPriorityOffset = -16;
}
s32 BosLstApproachValue(s32 a, s32 b, s32 c, s32 d, s32 e) {
    if (c == 0) {
        c = Sqrt8((abs(a - b) << 8) / 768);
        if (c < d) {
            c = d;
        }
        if (c > e) {
            c = e;
        }
    }
    if (abs(a - b) < c) {
        a = b;
    } else if (a < b) {
        a += c;
    } else {
        a -= c;
    }
    return a;
}

void BosLstMoveMode0(BosLstWork* work) {
    if (work->facing > 0) {
        work->x = BosLstApproachValue(work->x, 0x14800, 0, 0x80, 0x200);
    } else {
        work->x = BosLstApproachValue(work->x, 0xA800, 0, 0x80, 0x200);
    }
    work->y = BosLstApproachValue(work->y, 0x1F000, 0, 0x80, 0x200);
    work->z = BosLstApproachValue(work->z, -0x5400, 0, 0x80, 0x400);
    if (work->z == -0x5400) {
        BosLstTickCardDelay(work);
        if (work->cardDelay < 0) {
            work->cardDelay = 0x400;
            if (!(gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION)) {
                BosLstRequestCardUse(work);
            }
        }
    }
}

void BosLstMoveMode1(BosLstWork* work) {
    BtlWork** pp;
    s32 y;

    if (work->subsDefeated == 0) {
        BosLstSetMode(work, 2, 1);
        work->kamaCount = 0;
    }
    pp = &gBtlWork;
    BosLstTickCardDelay(work);
    if (work->cardDelay < 0) {
        work->cardDelay = 0x400;
        if (((*pp)->flags & BTL_FLAG_PLAYER_CARD_ACTION) == 0) {
            work->groundVz = -0x1200;
            work->groundTargetX = (*pp)->actor->x - ((work->facing * 5) << 10);
            if (work->groundTargetX > 0x14000) {
                work->groundTargetX = 0x14000;
            }
            if (work->groundTargetX < 0xB000) {
                work->groundTargetX = 0xB000;
            }
            BosLstRequestCardUse(work);
        }
    }
    if (work->facing > 0) {
        if (work->x < 0x14800) {
            work->x = work->x + 192;
        }
    } else if (work->x > 0xA800) {
        work->x = work->x - 192;
    }
    y = 0x1F000;
    work->offsetX = (-gSineTable[((work->frameCount * 4) & 0xFF) + 64] / 16) << 8;
    work->y = BosLstApproachValue(work->y, y, 0, 0x100, 0x200);
    work->z = BosLstApproachValue(work->z, -0xA400, 0x400, 0x100, 0x200);
}

void BosLstMoveMode2(BosLstWork* work) {
    if (work->subsDefeated == 1) {
        BosLstSetMode(work, 3, 2);
        work->kamaCount = 0;
    }
    if (work->facing > 0) {
        work->x = BosLstApproachValue(work->x, 0x14800, 0, 0x80, 0x200);
    } else {
        work->x = BosLstApproachValue(work->x, 0xA800, 0, 0x80, 0x200);
    }
    work->y = BosLstApproachValue(work->y, 0x1F000, 0, 0x80, 0x200);
    work->z = BosLstApproachValue(work->z, -0x5400, 0, 0x80, 0x400);
    BosLstTickCardDelay(work);
    if (work->cardDelay < 0) {
        work->cardDelay = 0x400;
        if (!(gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION)) {
            BosLstRequestCardUse(work);
        }
    }
}

void BosLstMoveDash(BosLstWork* work) {
    s16 v;
    s16 n;
    s32 target;
    s32 dir;
    s32 dir2;

    if (work->subsDefeated == 0) {
        BosLstSetMode(work, 0, 3);
        return;
    }
    if (work->dashCount > 0) {
        work->step = 1;
    }
    if (work->facing > 0) {
        work->x = BosLstApproachValue(work->x, 0x14800, 0, 0x80, 0x100);
    } else {
        work->x = BosLstApproachValue(work->x, 0xA800, 0, 0x80, 0x100);
    }
    work->y = BosLstApproachValue(work->y, 0x1F000, 0, 0x100, 0x400);
    work->z = BosLstApproachValue(work->z, -0x5400, 0, 0x100, 0x400);
    if (work->step == 0) {
        BosLstTickCardDelay(work);
        if (work->cardDelay < 0) {
            work->cardDelay = 0x400;
            if ((gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) == 0) {
                work->step += 1;
                work->dashCount += 1;
                work->dashStep = 0;
                work->dashSpeed = 0;
                work->unk_0AC = 0;
                work->timer = 0;
            }
        }
        if (work->step == 0) {
            return;
        }
    }
    switch (work->dashStep) {
    case 0:
        if (work->state != 4) {
            if ((((s16)work->frameCount + 4) & 7) == 0) {
                BosLstSpawnFal(work, 0);
            }
        }
        if (work->z < -0x25400 || (work->facing > 0 && work->x < -0x7000) ||
            (work->facing < 0 && work->x > 0x26000)) {
            dir = work->facing;
            BosLstSetFacing(work, -dir);
            work->dashStep = 1;
            work->timer = 0;
            work->dashSpeed = 0;
            v = 27 - (work->hpRatio >> 4);
            if (work->sub[0].defeated == 1) {
                v += 8;
                work->dashSpeed = 0x100;
            }
            if (work->sub[1].defeated == 1) {
                v += 8;
                work->dashSpeed += 0x100;
            }
            if (work->facing < 0) {
                work->x = -0x1000;
            } else {
                work->x = 0x20000;
            }
            work->y = 0x1F000;
            work->z = (-64 - v) << 8;
            work->dashVz = 0xA0;
        } else {
            work->dashSpeed += 64;
            if (work->dashSpeed > 0x800) {
                work->dashSpeed = 0x800;
            }
            work->x -= (work->facing << 1) * work->dashSpeed;
            work->z -= (work->dashSpeed * 192) >> 8;
        }
        break;
    case 1:
        if (work->facing > 0) {
            work->x = BosLstApproachValue(work->x, 0x15800, 0, 0x100, 0x400);
        } else {
            work->x = BosLstApproachValue(work->x, 0x9800, 0, 0x100, 0x400);
        }
        work->y = BosLstApproachValue(work->y, 0x1F000, 0, 0x100, 0x400);
        work->timer += 1;
        if (work->timer == ((work->hpRatio * 60) >> 8) + 90) {
            work->dashStep = 2;
            work->timer = 0;
        }
        break;
    case 2:
        BosLstRequestCardUse(work);
        work->timer = 0;
        work->dashSpeed = (work->dashCount + 1) << 8;
        if (work->sub[0].defeated == 1) {
            work->dashSpeed += 0x100;
        }
        if (work->sub[1].defeated == 1) {
            work->dashSpeed += 0x100;
        }
        break;
    case 3:
    case 4:
        v = 39 - (work->hpRatio >> 4);
        if (work->sub[0].defeated == 1) {
            v += 8;
            work->dashSpeed += 0x100;
        }
        if (work->sub[1].defeated == 1) {
            v += 8;
            work->dashSpeed += 0x100;
        }
        work->z = (-64 - v) << 8;
        work->dashVz = 12;
        work->timer += 1;
        if (work->timer > 59) {
            n = 3;
            if (work->hpRatio <= 63) {
                n = 6;
            } else if (work->hpRatio <= 127) {
                n = 5;
            } else if (work->hpRatio <= 191) {
                n = 4;
            }
            work->dashCount += 1;
            if (work->dashCount >= n) {
                work->dashStep = 5;
                work->timer = 0;
                if (gBtlWork->actor->x < 0xF800) {
                    work->x = 0x14800;
                    BosLstSetFacing(work, 1);
                } else {
                    work->x = 0xA800;
                    BosLstSetFacing(work, -1);
                }
                work->y = 0x1F000;
                work->z = -0x25400;
            } else {
                if (work->subsDefeated == 1) {
                    work->dashStep = 2;
                } else {
                    work->dashStep = 1;
                }
                work->timer = 0;
                dir2 = work->facing;
                BosLstSetFacing(work, -dir2);
            }
        }
        break;
    case 5:
        work->z = BosLstApproachValue(work->z, target = -0x5400, 0, 0x200, 0x800);
        if (work->z == target) {
            BosLstSetMode(work, 0, 3);
            work->timer = 0;
            work->dashCount = 0;
        }
        break;
    }
}

u8 BosLstAnyBitFiring(BosLstWork* work, s32 idx) {
    s32 i;
    u8 r;

    r = 0;
    if (idx < 0) {
        for (i = 0; i < work->lstTaskCount; i++) {
            if (BosLstBitHasShots(work->lstTasks[i]) == 1) {
                r = 1;
                break;
            }
        }
    } else if (idx < work->lstTaskCount) {
        if (BosLstBitHasShots(work->lstTasks[idx]) == 1) {
            r = 1;
        }
    }
    return r;
}

#ifdef VERSION_EU
u8 eu_0810BA1C(BosLstWork* work, s32 idx) {
    s32 i;
    u8 r;

    r = 0;
    if (idx < 0) {
        for (i = 0; i < work->lstTaskCount; i++) {
            if (eu_0810F08C(work->lstTasks[i]) == 1) {
                r = 1;
                break;
            }
        }
    } else if (idx < work->lstTaskCount) {
        if (eu_0810F08C(work->lstTasks[idx]) == 1) {
            r = 1;
        }
    }
    return r;
}
#endif

u8 BosLstAnyBitAlive(BosLstWork* work) {
    s16 v;
    s32 i;

    v = 0;
    for (i = 0; i < work->lstTaskCount; i++) {
        v = BosLstBitMarkFirstAlive(work->lstTasks[i], v);
    }
    return v != 0;
}

void BosLstHoverBits(BosLstWork* work) {
    s32 i;

    for (i = 0; i < work->lstTaskCount; i++) {
        if (BosLstBitIsAlive(work->lstTasks[i]) == 1) {
            BosLstBitStartHover(work->lstTasks[i]);
        }
    }
}

u8 BosLstFireBits(BosLstWork* work, s32 idx, s16 a) {
    s32 i;
    u8 r;

    r = 0;
    if (idx < 0) {
        for (i = 0; i < work->lstTaskCount; i++) {
            if (BosLstBitIsAlive(work->lstTasks[i]) == 1) {
                BosLstBitStartFiring(work->lstTasks[i], a);
                r = 1;
            }
        }
    } else if (idx < work->lstTaskCount) {
        if (BosLstBitIsAlive(work->lstTasks[idx]) == 1) {
            BosLstBitStartFiring(work->lstTasks[idx], a);
            r = 1;
        }
    }
    return r;
}

void BosLstReturnBits(BosLstWork* work) {
    s32 i;

    for (i = 0; i < work->lstTaskCount; i++) {
        if (BosLstBitIsAlive(work->lstTasks[i]) == 1) {
            BosLstBitStartReturn(work->lstTasks[i]);
        }
    }
}

void BosLstInterruptBits(BosLstWork* work) {
    s32 i;
    u8 flag;

    flag = 1;
    for (i = 0; i < work->lstTaskCount; i++) {
        if (BosLstBitIsAlive(work->lstTasks[i]) == 1) {
            if (BosLstBitInterrupt(work->lstTasks[i], flag) == 1) {
                flag = 0;
            }
        }
    }
}

void BosLstMoveBits(BosLstWork* work) {
    LstBitArg s;
    BtlObj* obj;
    s32 i;
    s16* pBC;
    s16* pBE;
    s32 v;

    obj = &work->body;
    if (work->facing > 0) {
        work->x = BosLstApproachValue(work->x, 0x14800, 0, 0x100, 0x400);
    } else {
        work->x = BosLstApproachValue(work->x, 0xA800, 0, 0x100, 0x400);
    }
    work->y = BosLstApproachValue(work->y, 0x1F000, 0, 0x100, 0x400);
    work->z = BosLstApproachValue(work->z, -0x5400, 0, 0x100, 0x400);
    v = work->bitRound;
    pBE = &work->bitRound;
    pBC = &work->bitStep;
    if (v == 0) {
        work->lstTaskCount = 3;
        s.x = obj->x;
        s.y = obj->y - 0x1100;
        s.z = obj->z + 0x800;
        for (i = 0; i < work->lstTaskCount; i++) {
            s.kind = 0;
            s.index = i;
            s.facing = &work->facing;
            s.falCount = &work->falCount;
            s.unk_10 = &work->unk_004;
            s.x2 = s.x + (i << 11);
            s.y2 = obj->y + 0x1400;
            s.z2 = s.z + ((i << 2) << 8);
            work->lstTasks[i] = TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosLstBit, &s);
        }
        *pBC = 0;
        *pBE += 1;
        work->timer = 0;
        work->cardDelay = 0xC000;
        BosLstSetAnim(work, 5, 0, 1);
        m4aSongNumStart(SONG_VO_MARL_ATTACK01);
    }
    if (BosLstAnyBitAlive(work) == 0) {
        BosLstDestroyTasks(work);
        work->timer = 0;
        *pBC = 0;
        *pBE = 0;
        BosLstSetMode(work, 0, 5);
        BosLstSetAnim(work, 0, 1, 0);
    } else {
        switch (*pBC) {
        case 0:
            work->timer += 1;
            if (work->timer > 30) {
                work->timer = 0;
                *pBC += 1;
            }
            break;
        case 1:
            if (work->unk_004 <= 0) {
                work->cardDelay -= 0x100;
            }
            if (work->cardDelay <= 0) {
                work->cardDelay = 0x400;
#ifdef VERSION_EU
                if (eu_0810BA1C(work, -1) != 0) {
                    break;
                }
#endif
                if ((gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) == 0) {
                    BosLstRequestCardUse(work);
                    work->bitAttackStarted = 0;
                }
            } else if (((work->cardDelay >> 8) & 0x3F) == 0) {
                BosLstHoverBits(work);
            }
            break;
#ifdef VERSION_EU
        default:
            BosLstReturnBits(work);
            break;
#endif
        }
    }
}

s32 BosLstGetPlatformY(BosLstWork* work) {
    s32 base;
    s16 d;
    s32 r;

    base = work->y + work->offsetZ;
    r = base + 0x1A00;
    d = abs((gBtlWork->actor->x - work->x) >> 8);
    if (d > 23) {
        if (d <= 83) {
            r -= (d / 3) << 8;
        } else if (d <= 143) {
            r = base - 0x400;
        } else {
            base -= 0x400;
            r = base + (((d - 144) / 4) << 8);
        }
    }
    return r;
}

void BosLstMovePlatform(BosLstWork* work) {
    LstBitArg s;
    BtlObj* obj;
    s32 i;
    s32 st;
    s32 target;
    s32 k;
    u8 found;
    s32* pDC;
    s32* p4C;
    u16 v;
    s32 z;

    work->hittableTimer = 30;
    st = work->platformStep;
    switch (st) {
    case 0:
        work->z = BosLstApproachValue(work->z, target = -0x2000, 0x400, k = 0x100, 0x400);
        if (work->z != target) {
            break;
        }
        work->platformStep += 1;
        work->platformTimer = st;
        work->playerOnPlatform = 0;
        work->platformSpeed = k;
        work->bitRound = st;
        for (i = 0; i < 8; i++) {
            ColliderSetDisabled(&work->colliders[i], 0);
        }
    case 1:
        obj = &work->body;
        v = work->platformTimer;
        if (work->platformTimer == 0) {
            work->platformTimer = v + 1;
            work->lstTaskCount = 3;
            s.x = obj->x;
            s.y = obj->y - 0x1100;
            s.z = obj->z + 0x800;
            for (i = 0; i < work->lstTaskCount; i++) {
                s.kind = 1;
                s.index = i;
                s.facing = &work->facing;
                s.falCount = &work->falCount;
                s.unk_10 = &work->unk_004;
                s.x2 = s.x + (i << 11);
                s.y2 = obj->y + 0x1400;
                s.z2 = s.z + ((i << 2) << 8);
                work->lstTasks[i] = TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosLstBit, &s);
            }
        }
        if ((gBtlWork->flags & BTL_FLAG_PLAYER_OFFSCREEN) == 0) {
            work->platformTimer += 1;
        }
        found = 0;
        for (i = 0; i < 8; i++) {
            if (IsPlayerOnPlatform(&work->colliders[i]) == 1) {
                found = 1;
                break;
            }
        }
        if (found == 1) {
            if (work->playerOnPlatform == 0) {
                BosLstSetAnim(work, 2, 0, 1);
            }
            work->playerOnPlatform = found;
            work->z = BosLstApproachValue(work->z, -0x16800, 0, 0x100, 0x400);
        }
        if (work->playerOnPlatform == 1) {
            if (BosLstAnyBitAlive(work) == 1) {
                BosLstTickCardDelay(work);
                if (work->cardDelay < 0) {
                    work->cardDelay = 0x2000;
                    BosLstRequestCardUse(work);
                    work->bitAttackStarted = 0;
                } else if ((work->platformTimer & 0x1F) == 0) {
                    BosLstHoverBits(work);
                }
            } else {
                work->platformSpeed += 1;
            }
            work->platformSpeed += 1;
            if (work->platformSpeed > 0x900) {
                work->platformSpeed = 0x900;
            }
            BosLstFldSetScrollSpeed(work->task, work->platformSpeed);
        } else if (work->platformTimer > 180) {
            BosLstReturnBits(work);
            work->platformStep += 1;
            work->platformSpeed = 0;
        }
        if (work->platformTimer > 0x4AF ||
            (work->playerOnPlatform == 1 && (gBtlWork->flags & BTL_FLAG_PLAYER_OFFSCREEN) == 0 &&
             gBtlWork->actor->z > work->z + work->offsetZ + 0x1800)) {
            BosLstReturnBits(work);
            work->platformStep += 1;
        }
        work->y = BosLstApproachValue(work->y, 0x1F000, 0x100, 0x100, 0x400);
        break;
    case 2:
        p4C = &work->z;
        for (i = 0; i < 8; i++) {
            ColliderSetDisabled(&work->colliders[i], 1);
        }
        ApproachValueHalfSteps(p4C, -0x16800, 48);
        if (work->facing < 0) {
            if (work->x < 0x26000) {
                work->x += 0x800;
                return;
            }
        } else {
            if (work->x > -0x7000) {
                work->x -= 0x800;
                return;
            }
        }
        BosLstDestroyTasks(work);
        work->bitRound = 0;
        if (gBtlWork->actor->x < 0xF800) {
            work->x = 0x14800;
            BosLstSetFacing(work, 1);
        } else {
            work->x = 0xA800;
            BosLstSetFacing(work, -1);
        }
        work->y = 0x1F000;
        work->z = -0x26800;
        BosLstSetMode(work, 0, 3);
        work->playerOnPlatform = 0;
        work->platformStep = 0;
        work->platformTimer = 0;
        work->turned = 0;
        BosLstSetAnim(work, 0, 1, 0);
        break;
    }
}

u8 BosLstUpdateMove(BosLstWork* work) {
    switch (work->moveMode) {
    case 0:
        BosLstFldSetBgMode(work->task, 2, work->facing);
        BosLstMoveMode0(work);
        break;
    case 1:
        BosLstFldSetBgMode(work->task, 1, work->facing);
        BosLstMoveMode1(work);
        break;
    case 2:
        BosLstFldSetBgMode(work->task, 1, work->facing);
        BosLstMoveMode2(work);
        break;
    case 3:
        BosLstFldSetBgMode(work->task, 0, work->facing);
        BosLstMoveDash(work);
        break;
    case 4:
        BosLstFldSetBgMode(work->task, 2, work->facing);
        BosLstMoveBits(work);
        break;
    case 5:
        BosLstFldSetBgMode(work->task, 3, work->facing);
        BosLstMovePlatform(work);
        break;
    }
    BosLstUpdateBob(work);
    return 1;
}

u8 BosLstAttackGround(BosLstWork* work) {
    s32 v;
    u8 r;

    r = 1;
    v = work->hpRatio;
    if (work->step == 0) {
        work->step += 1;
        work->groundCount += 1;
        work->groundStep = 0;
        work->timer = 0;
    }
    switch (work->groundStep) {
    case 0:
        if (work->timer == 0) {
            m4aSongNumStart(SONG_VO_MARL_ATTACK03);
            work->timer += 1;
        }
        work->x = BosLstApproachValue(work->x, work->groundTargetX, 0, 384, 768);
        work->z += work->groundVz;
        work->groundVz += 320;
        if (work->z > -0x5400) {
            work->z = -0x5400;
            work->groundStep = 3;
            work->timer = 0;
        }
        break;
    case 1:
    case 2:
        break;
    case 3:
        BgFxStartMahluxiaGround(work->x + (work->facing << 12), work->y, 0, 268);
        m4aSongNumStart(SONG_EF_MARL_GROUND);
        work->groundStep = 4;
        work->timer = 0;
    case 4:
        work->timer += 1;
        if (work->timer <= 19) {
            if (ApplyAttackBox(268, gBtlWork->actor->x,
                              gBtlWork->actor->y, 0,
                              32, 32, (s16)(((v * 8) >> 8) + 8)) != 0) {
                m4aSongNumStart(SONG_BTL_MARL_GROUNDHIT);
            }
        }
        if (BgFxIsActive() == 0) {
            if (work->timer >= ((v * 30) >> 8) + 31) {
                work->groundStep = 5;
                work->timer = 0;
                if (work->groundCount > 2) {
                    if (work->subsDefeated == 0) {
                        BosLstSetMode(work, 2, 1);
                    } else {
                        BosLstSetMode(work, 3, 2);
                    }
                    work->groundCount = 0;
                    r = 0;
                }
            }
        }
        break;
    case 5:
        work->z = BosLstApproachValue(work->z, -0x5400, 0, 256, 1024);
        if (work->z == -0x5400) {
            work->groundStep = 1;
            work->timer = 0;
            r = 0;
        }
        break;
    }
    return r;
}

u8 BosLstAttackKama(BosLstWork* work) {
    BtlObj* sub;
    s16* p8C;
    s32 st;
    u16 v;
    s16 z;
    u8 r;

    r = 1;
    sub = &work->sub[BosLstFindActiveSub(work)].body;
    v = work->step;
    if (work->step == 0) {
        work->step = v + 1;
        work->kamaCount += 1;
        work->kamaStep = 0;
        work->timer = 0;
    }
    st = work->kamaStep;
    p8C = &work->kamaStep;
    switch (st) {
    case 0:
        if (work->timer == 0) {
            m4aSongNumStart(SONG_SND_712);
            BosLstSetSubAnim(work, 3);
        }
        work->timer += 1;
        if (work->timer > 30) {
            *p8C = 1;
            work->timer = 0;
            m4aSongNumStart(SONG_VO_MARL_ATTACK00);
        }
        break;
    case 1:
        work->timer += 1;
        work->x += work->facing * 0x600;
        work->z -= work->timer << 8;
        if (work->z < -0x1E000) {
            *p8C = 3;
            work->timer = 0;
            work->unk_094 = work->y;
            work->unk_098 = work->z;
            if (gBtlWork->actor->x > 0xF7FF) {
                work->kamaStartX = (GetRandom() % 41 << 8) + 0xB000;
                BosLstSetFacing(work, 1);
            } else {
                work->kamaStartX = (GetRandom() % 40 << 8) + 0x11800;
                BosLstSetFacing(work, -1);
            }
            BosLstSetSubAnim(work, 5);
            work->x = work->kamaStartX;
            work->kamaTargetX = gBtlWork->actor->x + work->facing * 0x3000;
            work->kamaTargetY = 0x1F000;
            work->kamaTargetZ = -0x5400;
        }
        break;
    case 2:
        z = 0;
        *p8C = 3;
        work->timer = z;
        work->kamaTargetX = gBtlWork->actor->x;
        work->kamaTargetY = 0x1F000;
        work->kamaTargetZ = -0x5400;
        break;
    case 3:
        if (work->timer <= 7) {
            ApproachValueHalfSteps(&work->kamaTargetX, gBtlWork->actor->x + work->facing * 0x3000, 8);
        }
        if (work->timer == 0) {
            work->kamaTargetY = BosLstApproachValue(work->kamaTargetY, gBtlWork->actor->y, 0x100, 0x100, 0x100);
        }
        work->x = BosLstApproachValue(work->x, work->kamaTargetX, 0, 0x100, 0x800);
        work->y = work->kamaTargetY;
        work->z = BosLstApproachValue(work->z, work->kamaTargetZ, 0, 0x1000, 0x1800);
        if (work->z == work->kamaTargetZ) {
            work->timer += 1;
            if (work->timer > 16) {
                *p8C = 4;
                work->timer = 0;
                work->unk_078 = 0;
                BosLstSetSubAnim(work, 4);
                BgFxStartKama(sub->x, work->kamaTargetY, sub->z + 0x2800, -(work->facing * 0x3000), 0x10A);
                m4aSongNumStart(SONG_EF_MARL_KAMAEF);
            }
        }
        break;
    case 4:
        switch (work->timer) {
        case 0:
            if (ApplyAttackBox(0x10A, sub->x - (work->facing << 13), work->kamaTargetY, sub->z, 48, 12, 64) != 0) {
                m4aSongNumStart(SONG_BTL_MARL_EFEHIT);
            }
        case 1:
        case 2:
        case 3:
            work->x -= work->facing << 9;
            work->z += 0x400;
            break;
        case 4:
        case 5:
        case 6:
            work->x -= work->facing * 0x300;
            work->z += 0x600;
            break;
        case 7:
        case 8:
        case 9:
            work->x -= work->facing << 9;
            work->z += 0x400;
            break;
        case 10:
        case 11:
            work->z -= 0x300;
            break;
        case 12:
        case 13:
            work->z -= 0x180;
            break;
        }
        work->timer += 1;
        if (BgFxIsActive() == 0) {
            *p8C = 5;
            work->timer = 0;
            BosLstSetSubAnim(work, 0);
        }
        break;
    case 5:
        if (work->kamaCount > 2) {
            BosLstSetMode(work, 3, 2);
            work->kamaCount = 0;
            r = 0;
        } else {
            z = 0;
            *p8C = z;
            work->timer = z;
            r = z;
        }
        break;
    }
    return r;
}

u8 BosLstAttackDash(BosLstWork* work) {
    u8 r;

    r = 1;
    if (work->step == 0) {
        BosLstSetAnim(work, 7, 0, 1);
        m4aSongNumStart(SONG_VO_MARL_ATTACK01);
        m4aSongNumStart(SONG_VO_MARL_ATTACK02);
        work->step += 1;
    }
    BosLstSpawnFal(work, 1);
    if (work->timer == 30) {
        m4aSongNumStart(SONG_SND_711);
    }
    if (work->timer > 30) {
        work->dashSpeed += 32;
        if (work->dashSpeed > 0x800) {
            work->dashSpeed = 0x800;
        }
        work->x = work->x - work->facing * work->dashSpeed;
        if (work->facing > 0) {
            if (work->x <= -0x8000) {
                r = 0;
            }
        } else if (work->x >= 0x27000) {
            r = 0;
        }
        if (work->dashVz > 0) {
            work->dashVz = work->dashVz + 8;
        } else {
            work->dashVz = work->dashVz - 8;
        }
        work->z += work->dashVz;
        if (ApplyAttackBox(0x10B, work->x, work->y, work->z + 0x4000, 12, 32, 64) != 0) {
            m4aSongNumStart(SONG_BTL_MON_HIT06);
        }
        if (r == 0) {
            work->dashStep = 4;
            work->timer = 0;
            BosLstSetAnim(work, 0, 1, 1);
        }
    } else {
        work->timer += 1;
    }
    return r;
}

u8 BosLstAttackCtr(BosLstWork* work) {
    LstCtrArg s;
    BtlObj* obj;
    s16 ang;
    s32 i;
    u8 r;

    obj = &work->body;
    r = 1;
    switch (work->step) {
    case 0:
        m4aSongNumStart(SONG_SND_709);
        if (work->facing > 0) {
            BgFxStartLstCtrFlipped(obj->x - 0x1800, obj->y - 0x400, obj->z, 256);
        } else {
            BgFxStartLstCtr(obj->x + 0x1800, obj->y - 0x400, obj->z, 256);
        }
        work->timer = 0;
        work->step += 1;
        break;
    case 1:
        BosLstSetAnim(work, 6, 0, 1);
        m4aSongNumStart(SONG_VO_MARL_ATTACK01);
        work->step += 1;
        break;
    case 2:
        work->timer += 1;
        if (work->timer == 32) {
            work->ctrCount = 3 - work->breakCount;
            if (work->ctrCount <= 0) {
                work->ctrCount = 1;
            }
            if (work->sub[0].defeated == 1) {
                work->ctrCount += 1;
            }
            if (work->sub[1].defeated == 1) {
                work->ctrCount += 1;
            }
            ang = ((work->hpRatio * 30) / 256) + 30;
            if (ang <= 44) {
                ang = 45;
            }
            s.x = obj->x;
            s.y = obj->y + 0x800;
            s.z = obj->z - 0x1000;
            for (i = 0; i < work->ctrCount; i++) {
                s.unk_00 = &work->unk_004;
                s.count = work->ctrCount;
                s.index = i;
                s.delay = i * ang + 90;
                work->lstTasks[i] = TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosLstCtr, &s);
            }
            work->unk_004 = 0;
            work->timer = 0;
            work->step += 1;
        }
        break;
    default:
        r = 0;
        for (i = 0; i < work->ctrCount; i++) {
            if (BosLstCtrIsActive(work->lstTasks[i]) == 1) {
                r = 1;
                break;
            }
        }
        if (r == 0) {
            BosLstDestroyTasks(work);
            BosLstSetMode(work, 4, 4);
            BosLstSetAnim(work, 0, 1, 0);
        }
        break;
    }
    BosLstUpdateBob(work);
    return r;
}

u8 BosLstAttackBits(BosLstWork* work) {
    s16 f;
    u8 r;

    r = 1;
    if (work->bitAttackStarted == 0) {
        work->bitAttackStarted += 1;
        if (work->bitRound <= 1) {
            work->bitStep = 1;
        } else {
            work->bitStep = 0;
        }
        work->timer = 0;
    }
    if (BosLstAnyBitAlive(work) == 0) {
        BosLstDestroyTasks(work);
        BosLstSetMode(work, 0, 5);
        work->bitRound = 0;
        work->bitStep = 3;
        work->timer = 0;
    }
    switch (work->bitStep) {
    case 0:
        if (work->timer == 0) {
            BosLstHoverBits(work);
        }
        work->timer += 1;
        if (work->timer > 59) {
            work->bitStep = 1;
            work->timer = 0;
        }
        break;
    case 1:
        f = 1;
        if (work->sub[0].defeated == 1) {
            f = 2;
        }
        if (work->sub[1].defeated == 1) {
            f++;
        }
        switch (work->timer) {
        case 0:
            if (work->attackKind == 6) {
                BosLstFireBits(work, -1, 1);
                break;
            }
            if (BosLstAnyBitFiring(work, 1) == 0) {
                if (BosLstFireBits(work, 1, f) == 1) {
                    break;
                }
            }
        case 12:
            if (BosLstAnyBitFiring(work, 0) == 0) {
                if (BosLstFireBits(work, 0, f) == 1) {
                    break;
                }
            }
        case 24:
            if (BosLstAnyBitFiring(work, 2) == 0) {
                BosLstFireBits(work, 2, f);
            }
            break;
        }
        work->timer += 1;
        if (BosLstAnyBitFiring(work, -1) == 0) {
            work->timer = 0;
            if (work->bitRound > 6) {
                work->bitStep = 2;
            } else {
                if (work->moveMode != 5) {
                    work->bitRound += 1;
                }
                r = 0;
            }
        }
        break;
    case 2:
        if (work->timer == 30) {
            BosLstReturnBits(work);
        }
        work->timer += 1;
        if (work->timer > 74) {
            work->bitStep = 3;
            work->timer = 0;
        }
        break;
    case 3:
        BosLstDestroyTasks(work);
        BosLstSetMode(work, 0, 5);
        work->bitRound = 0;
        r = 0;
        break;
    }
    BosLstUpdateBob(work);
    return r;
}

u8 BosLstAttackHanabira(BosLstWork* work) {
    s16 s;
    u8 r;

    r = 1;
    s = work->step;
    switch (s) {
    case 0:
        BosLstSetAnim(work, 4, 0, 1);
        m4aSongNumStart(SONG_VO_MARL_ATTACK03);
        work->step += 1;
        work->timer = 0;
        break;
    case 1:
        work->timer += 1;
        if (work->timer > 120) {
            work->step += 1;
            work->timer = 0;
        }
        break;
    case 2:
        if (AnimIsFinished(&work->anim) == 1) {
            BgFxStartHanabira(work->x, work->y, work->z - 0x2000, 270);
            m4aSongNumStart(SONG_EF_MARL_HANABIRA);
            work->step += 1;
            work->timer = 0;
        }
        break;
    case 3:
        if (BgFxIsActive() == 0) {
            BosLstSetAnim(work, 0, 1, 0);
            r = 0;
        }
        if (r == 0) {
            if (work->subsDefeated == 1) {
                BosLstSetMode(work, 1, 0);
            } else {
                BosLstSetMode(work, 2, 1);
            }
        }
        break;
    }
    if (work->z > -0x5400) {
        work->z = work->z - 0x400;
    }
    BosLstUpdateBob(work);
    return r;
}

u8 BosLstUpdateAttack(BosLstWork* work) {
    void* p;
    s16 t;
    u8 d;

    p = &work->body;
    t = work->hpRatio;
    if (t <= 63) {
        t = 64;
    }
    switch (work->attackKind) {
    case 0:
        d = BosLstAttackGround(work);
        if (d != 0) {
            return 1;
        }
        ClearBtlObjActionFlags(p);
        work->state = d;
        work->step = d;
        work->cardDelay = ((t * 15) >> 4) << 8;
        return 1;
    case 1:
        d = BosLstAttackKama(work);
        if (d != 0) {
            return 1;
        }
        ClearBtlObjActionFlags(p);
        work->state = d;
        work->step = d;
        work->cardDelay = ((t * 15) >> 4) << 8;
        return 1;
    case 2:
        d = BosLstAttackDash(work);
        if (d != 0) {
            return 1;
        }
        ClearBtlObjActionFlags(p);
        work->state = d;
        work->step = d;
        work->cardDelay = ((t * 15) >> 4) << 8;
        return 1;
    case 3:
        d = BosLstAttackCtr(work);
        if (d != 0) {
            return 1;
        }
        ClearBtlObjActionFlags(p);
        work->state = d;
        work->step = d;
        work->cardDelay = ((t * 15) >> 4) << 8;
        return 1;
    case 4:
    case 6:
        d = BosLstAttackBits(work);
        if (d != 0) {
            return 1;
        }
        ClearBtlObjActionFlags(p);
        work->state = d;
        work->step = d;
        work->cardDelay = 0x5A00;
        return 1;
    case 5:
        d = BosLstAttackHanabira(work);
        if (d != 0) {
            return 1;
        }
        ClearBtlObjActionFlags(p);
        work->state = d;
        work->step = d;
        work->cardDelay = ((t * 15) >> 4) << 8;
        return 1;
    default:
        ClearBtlObjActionFlags(p);
        work->state = 0;
        work->step = 0;
        work->cardDelay = ((t * 15) >> 4) << 8;
        return 1;
    }
    return 1;
}

u8 BosLstUpdateHurt(BosLstWork* work) {
    void* p;

    p = &work->body;
    if (AnimIsFinished(&work->anim) == 1) {
        ClearBtlObjActionFlags(p);
        BosLstSetAnim(work, 0, 1, 1);
        work->state = 0;
    }
    return 1;
}

u8 func_0810E984(BosLstWork* work) {
    ClearBtlObjActionFlags(&work->body);
    work->state = 0;
    work->step = 0;
    return 1;
}

u8 BosLstUpdateBreak(BosLstWork* work) {
    LstSpawn3 s;
    BtlObj* obj;

    obj = &work->body;
    ClearBtlObjActionFlags(obj);
    work->breakCount += 1;
    work->unk_078 = 0;
    if (work->animId != 2) {
        BosLstSetAnim(work, 0, 1, 0);
    }
    BosLstSetSubAnim(work, 0);
    work->cardDelay = ((((work->hpRatio * 240) >> 9) + 120) << 8);
    if (work->subsDefeated == 1) {
        work->hittableTimer = 120;
    }
    if (work->moveMode < 4 || work->moveMode > 5) {
        BosLstDestroyTasks(work);
    }
    switch (work->moveMode) {
    case 0:
        switch (work->attackKind) {
        case 3:
            if (work->breakCount > 2) {
                BosLstSetMode(work, 4, 4);
            }
            break;
        case 5:
            if (work->subsDefeated == 0) {
                BosLstSetMode(work, 2, 1);
            } else {
                BosLstSetMode(work, 1, 0);
            }
            break;
        }
        break;
    case 1:
        if (work->groundCount + work->breakCount > 3) {
            work->groundCount = 0;
            BosLstSetMode(work, 3, 2);
            work->y = 0x1F000;
            work->z = -0x5400;
        }
        break;
    case 2:
        work->y = 0x1F000;
        work->z = -0x5400;
        if (work->kamaCount + work->breakCount > 3) {
            work->kamaCount = 0;
            BosLstSetMode(work, 3, 2);
        }
        break;
    case 3:
        work->dashCount = 0;
        BosLstSetMode(work, 5, 6);
        work->platformTimer = 0;
        if (gBtlWork->actor->x < 0xF800) {
            work->x = 0x15000;
            BosLstSetFacing(work, -1);
        } else {
            work->x = 0xA000;
            BosLstSetFacing(work, 1);
        }
        work->y = 0x1F000;
        work->z = -0x5400;
        break;
    case 4:
        BosLstInterruptBits(work);
        break;
    case 5:
        work->hittableTimer = 0;
        BosLstInterruptBits(work);
        break;
    }
    work->state = 0;
    work->step = 0;
    s.x = work->x + work->offsetX;
    s.y = work->y + work->offsetY;
    s.z = (work->z + work->offsetZ) - ((obj->height >> 1) << 8);
    s.kind = 9;
    TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBtlPop, &s);
    return 1;
}

u8 BosLstUpdateDefeat(BosLstWork* work) {
    u8 r;
    s32 i;
    s32 d1;
    s32 d2;
    s32 range;

    r = 1;
    SetBtlObjUnhittable(&work->body, 1);
    work->platformSpeed = 0;
    BosLstDestroyTasks(work);
    work->x = BosLstApproachValue(work->x, 0xF800, 0x80, 0x100, 0x100);
    work->y = BosLstApproachValue(work->y, 0x1F000, 0x80, 0x100, 0x100);
    if ((work->defeatTimer & 7) == 0) {
        BosLstSpawnFal(work, 4);
    }
    if ((work->defeatTimer & 7) == 4) {
        BosLstSpawnFal(work, 5);
    }
    work->defeatTimer += 1;
    if (work->z >= -0x5500 || work->step > 4) {
        BosLstFldSetCameraMode(work->task, 2);
    } else {
        BosLstFldSetCameraMode(work->task, 1);
    }
    switch (work->step) {
    case 0:
        work->timer = 0;
        BeginBossDefeat(&work->body);
        m4aSongNumStart(SONG_SND_713);
        m4aSongNumStart(SONG_EV_FLASH00);
        BosLstSetAnim(work, 3, 0, 0);
        work->step += 1;
    case 1:
        work->z = BosLstApproachValue(work->z, -0x5400, 0x80, 0x100, 0x140);
        if (work->timer & 0x20) {
            range = 0x200;
            d1 = (GetRandom() % 5 << 8) - range;
            work->offsetX = d1;
            d2 = (GetRandom() % 5 << 8) - range;
            work->offsetZ = d2;
        } else {
            work->offsetX = 0;
            work->offsetZ = 0;
        }
        work->timer += 1;
        if (work->timer <= 63) {
            break;
        }
        for (i = 0; i < 8; i++) {
            ColliderSetDisabled(&work->colliders[i], 1);
        }
        work->playerOnPlatform = 0;
        work->step += 1;
        work->timer = 0;
    case 2:
        work->z = BosLstApproachValue(work->z, -0x5400, 0x80, 0x100, 0x140);
        if (work->timer & 0x10) {
            range = 0x400;
            d1 = (GetRandom() % 9 << 8) - range;
            work->offsetX = d1;
            d2 = (GetRandom() % 9 << 8) - range;
            work->offsetZ = d2;
        } else {
            work->offsetX = 0;
            work->offsetZ = 0;
        }
        work->timer += 1;
        if (work->timer > 180) {
            work->step += 1;
            work->timer = 0;
        }
        break;
    case 3:
        BgFxStartHumDefeat(work->x, -0x800 + work->y + work->z);
        m4aSongNumStart(SONG_SND_718);
        FadeToAmount(0, gBtlWork->fadeAmount, 8);
        work->step += 1;
        work->timer = 0;
    case 4:
        work->timer += 1;
        if (work->timer <= 39) {
            range = 0x600;
            d1 = (GetRandom() % 13 << 8) - range;
            work->offsetX = d1;
            d2 = (GetRandom() % 13 << 8) - range;
            work->offsetZ = d2;
        } else {
            work->offsetX = 0;
            work->offsetZ = 0;
        }
        if (work->timer <= 199) {
            switch (work->timer) {
            case 40:
                for (i = 0; i < 8; i++) {
                    BosLstSpawnFal(work, 5);
                }
                FadeStartOut(2, 4);
                m4aSongNumStart(SONG_SND_720);
                break;
            case 120:
            case 170:
            case 190:
                for (i = 0; i < 8; i++) {
                    BosLstSpawnFal(work, 5);
                }
                FadeStartOut(2, 2);
                m4aSongNumStart(SONG_SND_720);
                break;
            case 44:
                FadeStartIn(2, 4);
                break;
            case 122:
            case 172:
            case 192:
                FadeStartIn(2, 2);
                break;
            }
        } else {
            for (i = 0; i < 80; i++) {
                BosLstSpawnFal(work, 5);
            }
            FadeStartIn(2, 60);
            FadeLock();
            m4aSongNumStart(SONG_SND_719);
            gBtlWork->flags |= BTL_FLAG_STOP_BGFX;
            work->hidden = 1;
            work->step += 1;
            work->timer = 0;
        }
        break;
    case 5:
        work->timer += 1;
        if (work->timer > 90) {
            work->step += 1;
            work->timer = 0;
        }
        break;
    case 6:
    default:
        work->timer += 1;
        if (work->timer > 210) {
            EndBossDefeat();
            r = 0;
        }
        break;
    }
    return r;
}

u8 BosLstUpdateEvent(BosLstWork* work) {
    switch (work->eventStep) {
    case 0:
        work->x = BosLstApproachValue(work->x, 0x1D000, 0, 0x80, 0x200);
        work->y = BosLstApproachValue(work->y, 0x1F000, 0, 0x80, 0x200);
        work->z = BosLstApproachValue(work->z, -0x14400, 0, 0x80, 0x400);
        BosLstFldSetBgMode(work->task, 4, work->facing);
        break;
    case 1:
        work->x = BosLstApproachValue(work->x, 0x15500, 0, 0x80, 0x200);
        work->y = BosLstApproachValue(work->y, 0x1F000, 0, 0x80, 0x200);
        work->z = BosLstApproachValue(work->z, -0x8400, 0, 0x80, 0x400);
        BosLstFldSetBgMode(work->task, 0, work->facing);
        break;
    }
    BosLstUpdateBob(work);
    return 1;
}

void BosLstUpdateSub(BosLstWork* work, LstSub* p) {
    LstSnpArg s;
    BtlObj* obj;
    u8 f;

    obj = &p->body;
    if (p->restartAnim == 1) {
        p->anim.animId = 0xFFFF;
        p->curAnimId = -1;
        p->restartAnim = 0;
    }
    if (p->animId == p->curAnimId) {
        switch (p->animId) {
        case 3:
        case 4:
            break;
        default:
            if (AnimIsFinished(&p->anim) == 1) {
                if (p->defeated == 1) {
                    p->animId = 2;
                } else {
                    p->animId = 0;
                }
            }
            break;
        }
    }
    f = 1;
    switch (p->animId) {
    case 1:
    case 3:
    case 4:
    case 6:
        f = 0;
        break;
    }
    if (work->facing > 0) {
        if (p->unk_001 == 1) {
            AnimChangeWithTables(&p->anim, p->animId * 2, f, gUnk_09EFAE1C, gUnk_09EFADC4);
        } else {
            AnimChangeWithTables(&p->anim, p->animId * 2, f, gUnk_09EFAEAC, gUnk_09EFAE54);
        }
    } else {
        if (p->unk_001 == 1) {
            AnimChangeWithTables(&p->anim, p->animId * 2 + 1, f, gUnk_09EFAEAC, gUnk_09EFAE54);
        } else {
            AnimChangeWithTables(&p->anim, p->animId * 2 + 1, f, gUnk_09EFAE1C, gUnk_09EFADC4);
        }
    }
    p->curAnimId = p->animId;
    AnimUpdate(&p->anim);
    switch (p->animId) {
    default:
        SetBtlObjUnhittable(obj, 1);
        break;
    case 0:
        SetBtlObjUnhittable(obj, 0);
        break;
    case 2:
        SetBtlObjUnhittable(obj, 1);
        return;
    }
    switch (UpdateBtlObjReaction(obj)) {
    case 5:
        p->state = 1;
        p->timer = 0;
        break;
    case 1:
    case 6:
    case 7:
        work->cardDelay = work->cardDelay * 3;
        work->cardDelay = work->cardDelay / 4;
        p->hurtTimer = 20;
        work->unk_076 = 20;
        if (p->state == 5) {
            ClearBtlObjActionFlags(obj);
        } else {
            p->state = 3;
            p->timer = 0;
        }
        break;
    case 3:
        p->state = 4;
        p->timer = 0;
        p->restartAnim = 1;
        p->animId = 6;
        s.x = p->body.x;
        s.y = p->body.y;
        s.z = p->body.z;
        s.facing = work->facing;
        TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosLstSnp, &s);
        break;
    case 4:
        p->state = 2;
        p->timer = 0;
        break;
    }
    switch (p->state) {
    case 0:
        break;
    case 3:
        p->timer += 1;
        if (p->timer > 20) {
            ClearBtlObjActionFlags(obj);
            p->state = 0;
            p->timer = 0;
        }
        break;
    case 1:
    case 2:
    case 5:
        ClearBtlObjActionFlags(obj);
        p->state = 0;
        p->timer = 0;
        break;
    case 4:
        p->defeated = 1;
        p->hurtTimer = 0;
        break;
    }
}

u8 task_bos_lst_1(BosLstWork* work) {
    s16 sx;
    s16 sy;
    u8 r;
    BtlObj* obj;
    BtlObj* pos;
    BtlObj* sub;
    LstSub* s;
    BtlWork** gp;
    s32 v;
    BtlObj* p2;
    s32 t;
    s32 y;
    s32 lim;
    s16 anim;
    s16 idx;
    s32 i;
    s32 k;
    s32 j;

    obj = &work->body;
    r = 1;
    work->offsetX = work->offsetX / 512;
    work->hpRatio = (work->body.hp * 255) / work->body.maxHp;
    gp = &gBtlWork;
    pos = (*gp)->actor;
    pos->flags |= BTLOBJ_FLAG_HIDE_SHADOW;
    (*gp)->bossPriorityOffset = -16;
    if (work->playerOnPlatform == 1) {
        y = BosLstGetPlatformY(work);
        p2 = (*gp)->actor;
        p2->y = y;
        if (((*gp)->flags & BTL_FLAG_PLAYER_OFFSCREEN) == 0) {
            t = (work->platformSpeed * 70) >> 8;
            v = p2->x + t * work->facing;
            p2->x = v;
            if (work->facing < 0) {
                lim = work->x - 0x2000;
                if (v > lim) {
                    p2->x = lim;
                }
            } else {
                lim = work->x + 0x2000;
                if (v < lim) {
                    p2->x = lim;
                }
            }
        }
    }
    anim = sBosLstBodyFrames[work->bodyCycle] << 1;
    idx = 0;
    if (work->facing < 0) {
        anim |= 1;
        idx = 1;
    }
    idx = (s16)idx;
    work->hittableTimer -= 1;
    if (work->hittableTimer < 0) {
        work->hittableTimer = 0;
    }
    SetBtlObjUnhittable(&work->body, 1);
    if (work->sub[0].defeated == 1 && work->sub[1].defeated == 1) {
        work->subsDefeated = 1;
        if (work->moveMode == 5) {
            if (work->turned == 1) {
                SetBtlObjUnhittable(&work->body, 0);
            }
        } else if (work->hittableTimer > 0) {
            SetBtlObjUnhittable(&work->body, 0);
        }
    } else {
        work->subsDefeated = 0;
    }
    switch (UpdateBtlObjReaction(obj)) {
    case 5:
        work->state = 1;
        work->step = 0;
        break;
    case 1:
    case 6:
    case 7:
        work->cardDelay = work->cardDelay * 3;
        work->cardDelay = work->cardDelay / 4;
        work->unk_076 = 20;
        BosLstSpawnFal(work, 0);
        BosLstSpawnFal(work, 0);
        BosLstSpawnFal(work, 0);
        BosLstSpawnFal(work, 0);
        work->platformSpeed += 0x80;
        BosLstSetAnim(work, 1, 0, 0);
        if (work->state == 5) {
            ClearBtlObjActionFlags(obj);
        } else {
            work->state = 3;
        }
        break;
    case 3:
        work->state = 4;
        work->step = 0;
        work->defeatTimer = 0;
        break;
    case 4:
        work->state = 2;
        work->step = 0;
        break;
    }
    switch (work->state) {
    case 0:
        BosLstUpdateMove(work);
        break;
    case 1:
        BosLstUpdateAttack(work);
        break;
    case 3:
        BosLstUpdateHurt(work);
        break;
    case 5:
        func_0810E984(work);
        break;
    case 2:
        BosLstUpdateBreak(work);
        break;
    case 4:
        r = BosLstUpdateDefeat(work);
        break;
    case 7:
        BosLstUpdateEvent(work);
        break;
    case 6:
    default:
        break;
    }
    BosLstUpdateSub(work, &work->sub[0]);
    BosLstUpdateSub(work, &work->sub[1]);
    obj->x = work->x + work->offsetX;
    obj->y = work->y + work->offsetY;
    obj->z = work->z + work->offsetZ;
    k = idx;
    if (work->sub[k].defeated == 0) {
        sub = &work->sub[k].body;
        sub->x = work->x + work->offsetX + (sLstAnimDefs[anim].subX << 8);
        sub->y = work->y + work->offsetY + (sLstAnimDefs[anim].subY << 8);
        sub->z = work->z + work->offsetZ + (sLstAnimDefs[anim].subZ << 8);
    }
    j = idx ^ 1;
    if (work->sub[j].defeated == 0) {
        s = &work->sub[j];
        sub = &s->body;
        sub->x = work->x + work->offsetX + (sLstAnimDefs[anim].sub2X << 8);
        sub->y = work->y + work->offsetY + (sLstAnimDefs[anim].sub2Y << 8);
        sub->z = work->z + work->offsetZ + (sLstAnimDefs[anim].sub2Z << 8);
    }
    ColliderSetPosition(&obj->collider, obj->x + (work->facing << 10), obj->y, obj->z);
    ColliderSetPosition(&work->collider, obj->x, obj->y - 0x1000, obj->z + 0x1800);
    ColliderSetPosition(&work->collider2, obj->x, obj->y - 0x1000, obj->z + 0x4000);
    for (i = 0; i < 8; i++) {
        ColliderSetPosition(&work->colliders[i], work->x + ((i << 12) + 0x1800) * work->facing, work->y, work->z);
    }
    switch (work->animId) {
    case 1:
        if (AnimIsFinished(&work->anim) == 1) {
            BosLstSetAnim(work, 0, 1, 0);
        }
        break;
    case 2:
        if (AnimIsFinished(&work->anim) == 1) {
            work->turned = 1;
            BosLstSetAnim(work, 0, 1, 0);
        }
        break;
    }
    AnimUpdate(&work->anim);
    work->bodyCycle += 1;
    work->bodyCycle = (u32)work->bodyCycle % 48;
    gBtlWork->bossX = work->x;
    gBtlWork->bossY = work->y;
    gBtlWork->bossZ = work->z;
    if (work->state != 4 && (work->frameCount & 0xF) == 0) {
        WorldToScreen(&sx, &sy, work->x + work->offsetX, work->y + work->offsetY, work->z + work->offsetZ);
        if (sy < -16) {
            BosLstSpawnFal(work, 2);
        } else if (work->playerOnPlatform == 1) {
            BosLstSpawnFal(work, 3);
        } else {
            BosLstSpawnFal(work, 0);
        }
    }
    work->frameCount += 1;
    TaskPoolUpdate(&work->tasks);
    return r;
}

void task_bos_lst_2(BosLstWork* work) {
    s16 sx;
    s16 sy;
    u32 fill;
    s16 idx;
    vu32* dma;
    u32* src;
    LstSub* sub;
    s16 anim;
    s16 n;
    s32 k;
    s32 j;
    u16 v;
    u16 w;

    TaskPoolDraw(&work->tasks);
    anim = sBosLstBodyFrames[work->bodyCycle] << 1;
    idx = 0;
    if (work->facing < 0) {
        anim |= 1;
        idx = 1;
    }
    idx = (s16)idx;
    if (StepHitFlash(&work->body) != 0 || StepHitFlash(&work->sub[0].body) != 0 ||
        StepHitFlash(&work->sub[1].body) != 0) {
        work->flash = 1;
    } else {
        work->flash = 0;
    }
    if ((s16)work->flash != (s16)work->prevFlash) {
        if ((s16)work->flash == 0) {
            LoadPalette(gUnk_09D69454, (void*)0x05000000, 0x60);
            LoadPalette(gUnk_09D69594, (void*)(0x05000200 + ((work->palette->index & 15) << 5)), 0x60);
        } else {
            LoadPalette(gUnk_08F69BC4, (void*)0x05000000, 32);
            LoadPalette(gUnk_08F69BC4, (void*)0x05000020, 32);
            LoadPalette(gUnk_08F69BC4, (void*)0x05000040, 32);
            LoadPalette(gUnk_08F69BC4, (void*)(0x05000200 + ((work->palette->index & 15) << 5)), 32);
            LoadPalette(gUnk_08F69BC4, (void*)(0x05000220 + ((work->palette->index & 15) << 5)), 32);
            LoadPalette(gUnk_08F69BC4, (void*)(0x05000240 + ((work->palette->index & 15) << 5)), 32);
        }
        work->prevFlash = work->flash;
    }
    if (work->hidden == 1 || (work->unk_078 & 1)) {
        DisableBg(1);
        return;
    }
    WorldToScreen(&sx, &sy, work->x + work->offsetX - (sLstAnimDefs[anim].bgX << 8),
                  work->y + work->offsetY - (sLstAnimDefs[anim].bgY << 8),
                  work->z + work->offsetZ - (sLstAnimDefs[anim].bgZ << 8));
    SetBgScroll(1, (u16)(-sx), (u16)(-sy));
    if ((u16)(sy + 255) > 0x19E || (u16)(sx + 255) > 0x1FE) {
        DisableBg(1);
    } else {
        if (work->turned == 1) {
            n = 8;
        } else {
            switch (AnimGetGfxIndex(&work->anim)) {
            case 58:
                n = 1;
                break;
            case 59:
                n = 2;
                break;
            case 60:
                n = 3;
                break;
            case 61:
                n = 4;
                break;
            case 62:
                n = 5;
                break;
            case 63:
                n = 6;
                break;
            case 64:
                n = 7;
                break;
            case 28:
            case 29:
                n = 8;
                break;
            default:
                n = 0;
                break;
            }
        }
        if ((s16)work->bgFrame != n) {
            LoadBgTiles(1, sBosLstBgFrames[n][0], 0xC00);
            work->bgFrame = n;
        }
        if (work->facing < 0) {
            n += 9;
        }
        dma = (vu32*)REG_ADDR_DMA3;
        dma[0] = (u32)sLstAnimDefs[anim].bgMap;
        dma[1] = (u32)work->bgMap;
        dma[2] = (DMA_ENABLE << 16) | 0x400;
        dma[2];
        src = sBosLstBgFrames[n][1];
        dma[0] = (u32)src;
        dma[1] = (u32)work->bgMap;
        dma[2] = (DMA_ENABLE << 16) | 0x140;
        dma[2];
        if (work->facing > 0) {
            dma[0] = (u32)(src + 160);
            dma[1] = (u32)work->unk_B24;
        } else {
            dma[0] = (u32)(src + 169);
            dma[1] = (u32)work->unk_B48;
        }
        dma[2] = (DMA_ENABLE << 16) | 0xE;
        dma[2];
        if (sy < 0) {
            fill = 0;
            CpuFastSet(&fill, work->bgMap, ((((-sy) >> 3) << 4) & 0x1FFFFF) | 0x1000000);
        } else if (sy <= 159) {
            fill = 0;
            CpuFastSet(&fill, work->bgMap + ((20 - (sy >> 3)) << 6), ((((sy >> 3) + 12) << 4) & 0x1FFFFF) | 0x1000000);
        }
        LoadBgMap(1, work->bgMap, 0x800);
    }
    WorldToScreen(&sx, &sy, work->x + work->offsetX, work->y + work->offsetY, work->z + work->offsetZ);
    DrawSprite(sx + sLstAnimDefs[anim].spriteX, sy + sLstAnimDefs[anim].spriteY, AnimGetGfx(&work->anim), work->tiles, work->palette, 0,
               GetBattleSpritePriorityFlags(work->y + work->offsetY + (gBtlWork->bossPriorityOffset << 8)),
               (u16)(-0x1004 - (((work->y + work->offsetY + (gBtlWork->bossPriorityOffset << 8)) >> 8) << 2)));
    WorldToScreen(&sx, &sy, work->x + work->offsetX, work->y + work->offsetY, work->z + work->offsetZ);
    k = idx;
    v = work->sub[k].hurtTimer;
    if (work->sub[k].hurtTimer > 0) {
        work->sub[k].hurtTimer = v - 1;
    }
    sub = &work->sub[k];
    DrawSprite(sx + sLstAnimDefs[anim].subSpriteX, sy + sLstAnimDefs[anim].subSpriteY, AnimGetGfx(&sub->anim), work->sub[0].tiles, work->palette, 0,
               GetBattleSpritePriorityFlags(work->y + work->offsetY),
               (u16)(-0x1004 - (((work->y + work->offsetY) >> 8) << 2)));
    j = idx ^ 1;
    w = work->sub[j].hurtTimer;
    if (work->sub[j].hurtTimer > 0) {
        work->sub[j].hurtTimer = w - 1;
    }
    sub = &work->sub[j];
    DrawSprite(sx + sLstAnimDefs[anim].sub2SpriteX, sy + sLstAnimDefs[anim].sub2SpriteY, AnimGetGfx(&sub->anim), work->sub[1].tiles, work->palette, 0,
               GetBattleSpritePriorityFlags(work->y + work->offsetY - 0x1100),
               (u16)(-0x1004 - (((work->y + work->offsetY - 0x1100) >> 8) << 2)));
}

void task_bos_lst_3(BosLstWork* work) {
    s32 i;

    ReleaseEnemyBtlObj(&work->body);
    ReleaseEnemyBtlObj(&work->sub[0].body);
    ReleaseEnemyBtlObj(&work->sub[1].body);
    ColliderUnregister(&work->collider);
    ColliderUnregister(&work->collider2);
    for (i = 0; i < 8; i++) {
        ColliderUnregister(&work->colliders[i]);
    }
    BosLstDestroyTasks(work);
    ReleaseObjTiles(work->sub[0].tiles);
    ReleaseObjTiles(work->sub[1].tiles);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}
