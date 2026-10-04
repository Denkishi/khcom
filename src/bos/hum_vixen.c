/**
 * hum_vixen.c
 * Vexen Boss
 */

#include "system_state.h"
#include "fade.h"
#include "obj_api.h"
#include "hum.h"
#include "sprites_hum.h"
#include "hum_common.h"
#include "songs.h"
#include <stdlib.h>
#include "hum_tasks.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "card_api.h"
#include "engine_math.h"
#include "game_state.h"
#include "hum_types.h"
#include "m4a_song.h"
#include "mode_chkobj_assets.h"
#include "obj.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

static const u32 sHumVixenStockMovesA[3] = {
    36, 37, 36,
};

static const u32 sHumVixenStockMovesB[3] = {
    37, 36, 36,
};

static const u32 sHumVixenStockMovesC[3] = {
    36, 36, 37,
};

static const u32 sHumVixenStockMovesD[3] = {
    36, 36, 36,
};

static const AnimDef sHumVixenAnimDefs[15] = {
    { gVixenS1Frames, gVixenS1Anims, gVixenS1Tiles, 0, { 0, 0, 0 } },
    { gVixenW1Frames, gVixenW1Anims, gVixenW1Tiles, 0, { 0, 0, 0 } },
    { gVixenD1Frames, gVixenD1Anims, gVixenD1Tiles, 0, { 0, 0, 0 } },
    { gVixenA1Frames, gVixenA1Anims, gVixenA1Tiles, 0, { 0, 0, 0 } },
    { gVixenM1bFrames, gVixenM1bAnims, gVixenM1bTiles, 0, { 0, 0, 0 } },
    { gVixenM2aFrames, gVixenM2aAnims, gVixenM2aTiles, 0, { 0, 0, 0 } },
    { gVixenM2aFrames, gVixenM2aAnims, gVixenM2aTiles, 2, { 0, 0, 0 } },
    { gVixenM2aFrames, gVixenM2aAnims, gVixenM2aTiles, 3, { 0, 0, 0 } },
    { gVixenM4Frames, gVixenM4Anims, gVixenM4Tiles, 0, { 0, 0, 0 } },
    { gVixenM1aFrames, gVixenM1aAnims, gVixenM1aTiles, 0, { 0, 0, 0 } },
    { gVixenM1aFrames, gVixenM1aAnims, gVixenM1aTiles, 1, { 0, 0, 0 } },
    { gVixenM1aFrames, gVixenM1aAnims, gVixenM1aTiles, 2, { 0, 0, 0 } },
    { gUnk_09EE2098, gUnk_09EE20A8, gUnk_08C08E48, 0, { 0, 0, 0 } },
    { gUnk_09EE2098, gUnk_09EE20A8, gUnk_08C08E48, 1, { 0, 0, 0 } },
    { gUnk_09EE2098, gUnk_09EE20A8, gUnk_08C08E48, 2, { 0, 0, 0 } },
};

static const HumDef sHumVixenDef = { 83, 0, gVixenPalette, 0, { 50, 99, 80, 14, 48, 99, 0 } };

TaskDesc gTaskDescHumVixen = {
    "task_hum_vixen",
    (TaskInitFunc)task_hum_vixen_0,
    (TaskUpdateFunc)task_hum_vixen_1,
    (TaskDrawFunc)task_hum_vixen_2,
    (TaskDestroyFunc)task_hum_vixen_3,
    sizeof(VixenWork),
};

static TaskDesc sTaskDescHumVixenNdl = {
    "task_hum_vixen_ndl",
    (TaskInitFunc)task_hum_vixen_ndl_0,
    (TaskUpdateFunc)task_hum_vixen_ndl_1,
    (TaskDrawFunc)task_hum_vixen_ndl_2,
    (TaskDestroyFunc)task_hum_vixen_ndl_3,
    sizeof(VixenNdlWork),
};

static TaskDesc sTaskDescHumVixenIce = {
    "task_hum_vixen_ice",
    (TaskInitFunc)task_hum_vixen_ice_0,
    (TaskUpdateFunc)task_hum_vixen_ice_1,
    (TaskDrawFunc)task_hum_vixen_ice_2,
    (TaskDestroyFunc)task_hum_vixen_ice_3,
    sizeof(VixenIceWork),
};

static const AnimDef sHumVixenFrzAnimDefs[13] = {
    { gVixenReitouFrames, gVixenReitouAnims, gVixenReitouTiles, 0, { 0, 0, 0 } },
    { gVixenReitouFrames, gVixenReitouAnims, gVixenReitouTiles, 1, { 0, 0, 0 } },
    { gReitouSoraFrames, gReitouSoraAnims, gReitouSoraTiles, 0, { 0, 0, 0 } },
    { gVixenReitouFrames, gVixenReitouAnims, gVixenReitouTiles, 2, { 0, 0, 0 } },
    { gReitouSoraFrames, gReitouSoraAnims, gReitouSoraTiles, 1, { 0, 0, 0 } },
    { gVixenReitouFrames, gVixenReitouAnims, gVixenReitouTiles, 3, { 0, 0, 0 } },
    { gReitouSoraFrames, gReitouSoraAnims, gReitouSoraTiles, 2, { 0, 0, 0 } },
    { gReitouRikuFrames, gReitouRikuAnims, gReitouRikuTiles, 0, { 0, 0, 0 } },
    { gReitouRikuFrames, gReitouRikuAnims, gReitouRikuTiles, 1, { 0, 0, 0 } },
    { gReitouRikuFrames, gReitouRikuAnims, gReitouRikuTiles, 2, { 0, 0, 0 } },
    { gReitouNiseFrames, gReitouNiseAnims, gReitouNiseTiles, 0, { 0, 0, 0 } },
    { gReitouNiseFrames, gReitouNiseAnims, gReitouNiseTiles, 1, { 0, 0, 0 } },
    { gReitouNiseFrames, gReitouNiseAnims, gReitouNiseTiles, 2, { 0, 0, 0 } },
};

static TaskDesc sTaskDescHumVixenFrz = {
    "task_hum_vixen_frz",
    (TaskInitFunc)task_hum_vixen_frz_0,
    (TaskUpdateFunc)task_hum_vixen_frz_1,
    (TaskDrawFunc)task_hum_vixen_frz_2,
    (TaskDestroyFunc)task_hum_vixen_frz_3,
    sizeof(VixenFrzWork),
};

static const VixenFrgDef sVixenFrgDefs[15] = {
    { 12, -29, 3, 0 },
    { 5, -37, 0, 0 },
    { -16, -24, 3, 2 },
    { -18, -6, 0, 1 },
    { 14, -4, 5, 0 },
    { 17, -5, 4, 0 },
    { -12, -44, 5, 1 },
    { -16, -40, 2, 0 },
    { 8, 0, 1, 0 },
    { 0, -13, 2, 2 },
    { -4, -24, 5, 0 },
    { 8, -12, 5, 0 },
    { 4, -48, 5, 3 },
    { -7, -39, 4, 1 },
    { 3, -54, 1, 1 },
};

static TaskDesc sTaskDescHumVixenFrg = {
    "task_hum_vixen_frg",
    (TaskInitFunc)task_hum_vixen_frg_0,
    (TaskUpdateFunc)task_hum_vixen_frg_1,
    (TaskDrawFunc)task_hum_vixen_frg_2,
    (TaskDestroyFunc)task_hum_vixen_frg_3,
    sizeof(VixenFrgWork),
};

void VixenPlaceGroundIce(VixenWork* work) {
    VixenSub* p;
    s32 i;

    m4aSongNumStart(SONG_BTL_VIC_GROUNDICE);
    p = work->sub;

    for (i = 0; i < 3; i++) {
        p[i].pending = p[i].active = 1;
        p[i].x = (gBtlWork->xMin + 32 +
            GetRandom() % (gBtlWork->xMax - gBtlWork->xMin - 0x3F)) << 8;
        p[i].y = (gBtlWork->yMin + 16 +
            GetRandom() % (gBtlWork->yMax - gBtlWork->yMin - 0x1F)) << 8;
    }
}

void VixenCreateIceTasks(VixenWork* work) {
    VixenSub* p;
    s32 i;
    u8 z;

    z = 0;
    p = work->sub;

    for (i = 0; i < 3; i++) {
        p->active = z;
        p->pending = z;
        TaskCreate(&work->tasks, &sTaskDescHumVixenIce, &work->sub[i]);
        p++;
    }
}

void VixenHover(HumWork* work, s32 a) {
    BtlObj* act;
    s32 t;

    if (a != 0) {
        act = &work->actor;
        t = a + gSineTable[gFrameCounter * 4 % 256] * 3;
        work->vz = 0;
        act->z += (t - act->z) >> 4;
    }
}

void task_hum_vixen_0(VixenWork* work) {
    HumInit(&work->base, &sHumVixenDef);
    work->hoverZ = 0;
    work->base.actor.flags |= BTLOBJ_FLAG_IMMUNE_BLIZZARD;
    work->flags = 0;
    TaskPoolInit(&work->tasks, 15);
    VixenCreateIceTasks(work);
    work->base.stockMoves = sHumVixenStockMovesA;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        gBtlWork->tiles2 = AllocObjTiles(0x840, NULL);
    }
}

u8 task_hum_vixen_1(VixenWork* work) {
    VixenWork* w;
    BtlObj* act;
    VixenNdlArgs args;
    s32 x;
    s32 y;
    s32 z;
    s32 s;
    u8 ang;
    s32 d;
    s32 v;
    s32 cx;
    s32 ax;
    u16 t;
    u8 r;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &x, &y, &z);

    switch ((u32)HumUpdateReaction(&work->base)) {
    case 5:
        work->base.stateTimer = 0;

        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
        case 38:
            w->base.state = 22;
            break;
        case 37:
        case 39:
            w->base.state = 21;
            break;
        case 0xF53D7753:
            work->base.state = 33;
            break;
        case 0xF53D4F5D:
            work->base.state = 28;
            break;
        case 0xF5DD4F53:
            work->base.state = 29;
            break;
        case 0xF53D4F53:
            work->base.state = 23;
            break;
        }

        break;
    case 4:
        m4aSongNumStop(SONG_BTL_VIC_ICEFALL);
        break;
    case 3:
    case 8:
        if (act->btl->hcEffect == 27) {
            w->base.state = 37;
            w->base.stateTimer = 0;
        }

        break;
    }

    switch (gBtlWork->battleId) {
    case 164:
        if (HumChooseCardAction(&w->base, 30, 40, 40, 24)) {
            w->base.stockMoves = sHumVixenStockMovesA;
        }

        break;
    case 175:
        if (HumChooseCardAction(&w->base, 5, 40, 40, 24)) {
            switch (GetRandom() % 3) {
            case 0:
                w->base.stockMoves = sHumVixenStockMovesA;
                break;
            case 1:
                w->base.stockMoves = sHumVixenStockMovesC;
                break;
            case 2:
                w->base.stockMoves = sHumVixenStockMovesD;
                break;
            }
        }

        break;
    case 176:
    default:
        if (HumChooseCardAction(&w->base, 30, 40, 40, 24)) {
            switch (GetRandom() % 3) {
            case 0:
                w->base.stockMoves = sHumVixenStockMovesA;
                break;
            case 1:
                w->base.stockMoves = sHumVixenStockMovesB;
                break;
            case 2:
                w->base.stockMoves = sHumVixenStockMovesD;
                break;
            }
        }

        break;
    }

    switch (w->base.state) {
    case 12:
    case 18:
        AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 0, ANIM_FLAG_LOOP, work->base.tiles);
        break;
    case 17:
        AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 0, ANIM_FLAG_LOOP, work->base.tiles);
        work->hoverZ = -0x4000;
        HumFaceTarget(&w->base, 20);
        break;
    case 0:
        AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 0, ANIM_FLAG_LOOP, work->base.tiles);
        work->hoverZ = 0;

        if (func_08081828() == 0) {
            HumFaceTarget(&w->base, 80);

            if (AnimIsFinished(&w->base.anim) && GetRandom() % 80 == 0) {
                w->base.state = 8;
                w->base.stateTimer = 0;
            } else {
                w->base.stateTimer++;
            }
        }

        break;
    case 8:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 1, ANIM_FLAG_LOOP, work->base.tiles);
            work->hoverZ = -0xF00;

            if (act->x <= 0xFFFF) {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
                w->base.targetX = (gBtlWork->xMax - 48) << 8;
            } else {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
                w->base.targetX = (gBtlWork->xMin + 48) << 8;
            }

            work->slideSpeed = 0;
        }

        work->slideSpeed += 17;

        if (work->slideSpeed > 0x199) {
            work->slideSpeed = 0x199;
        }

        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
            act->x -= work->slideSpeed;
        } else {
            act->x += work->slideSpeed;
        }

        if (w->base.flags & HUM_FLAG_AT_FIELD_EDGE) {
            work->flags ^= VIXEN_FLAG_SLIDE_DOWN;
        }

        if (work->flags & VIXEN_FLAG_SLIDE_DOWN) {
            act->y += work->slideSpeed;
        } else {
            act->y -= work->slideSpeed;
        }

        d = act->x - w->base.targetX;

        if ((d >= 0) ? d <= 0xBFF : w->base.targetX - act->x <= 0xBFF) {
            w->base.state = 0;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 1:
    case 3:
    case 9:
    case 11:
    case 14:
        AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 2, 0, work->base.tiles);
        break;
    case 21:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 3, 0, work->base.tiles);
            work->hoverZ = 0;
        }

        if (AnimGetFrame(&w->base.anim) == 3) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                s32 d = act->x + 0x3200;
                act->x += (act->originX - d) >> 2;
            } else {
                s32 d = act->x - 0x3200;
                act->x += (act->originX - d) >> 2;
            }

            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                ? ApplyAttackBox(312, act->x - 0x2000, act->y, act->z, 12, 12, 48)
                : ApplyAttackBox(312, act->x + 0x2000, act->y, act->z, 12, 12, 48)) {
                m4aSongNumStart(SONG_BTL_VIC_SWORDHIT);
            }
        }

        if (AnimIsFinished(&w->base.anim)) {
            ClearBtlObjActionFlags(act);
            w->base.state = 0;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 37:
        if (w->base.stateTimer == 0) {
            AnimReset(&w->base.anim);
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 2, 0, work->base.tiles);
        }

        if (AnimIsFinished(&w->base.anim)) {
            w->base.flags &= ~HUM_FLAG_PASS_THROUGH;
            act->btl->hcEffectCount--;
            v = 0;
            act->hp = act->maxHp / 4;
            act->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
            ClearBtlObjActionFlags(act);
            CreateBtlPopTask(act, 10);
            w->base.state = v;
            w->base.stateTimer = v;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 22:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 4, 0, work->base.tiles);
            work->hoverZ = 0;
        }

        if (AnimGetFrame(&w->base.anim) == 3 && w->base.anim.timer == 0) {
            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                BgFxStartBlizzard(1, act->x - 0x3700, act->y, act->z - 0x4000,
                    act->x - 0x6E00, act->y, -0x1400, 1, 0x139);
            } else {
                BgFxStartBlizzard(1, act->x + 0x3700, act->y, act->z - 0x4000,
                    act->x + 0x6E00, act->y, -0x1400, 0, 0x139);
            }
        }

        if (AnimIsFinished(&w->base.anim) && !BgFxIsActive()) {
            ClearBtlObjActionFlags(act);
            w->base.state = 0;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 23:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 5, 0, work->base.tiles);
            work->hoverZ = 0;
            work->needleCount = 0;
        }

        if (AnimIsFinished(&w->base.anim)) {
            w->base.stateTimer = 0;
            w->base.state = 24;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 24:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 6, ANIM_FLAG_LOOP, work->base.tiles);
        }

        if (w->base.stateTimer > 60) {
            w->base.stateTimer = 0;
            w->base.state = 25;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 25:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 7, 0, work->base.tiles);
        }

        if (AnimIsFinished(&w->base.anim)) {
            w->base.stateTimer = 0;
            w->base.state = 26;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 26:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 4, 0, work->base.tiles);

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                work->needleX = act->x - 0x2000;
                work->angle = 192;
            } else {
                work->needleX = act->x + 0x2000;
                work->angle = 64;
            }

            work->needleY = act->y;
            m4aSongNumStart(SONG_VO_VIC_ATTACK01);
            InitObjTilesAtSlot(&work->needleTiles, ((ObjTiles*)gBtlWork->tiles2)->index, gVixenE1Tiles, 0x7E0);
        }

        if (AnimGetFrame(&w->base.anim) > 2) {
            ang = GetAngle(work->needleX, work->needleY, x, y);
            ApproachAngle(&work->angle, ang, 3);
            s = abs(SIN((u16)w->base.stateTimer * 2));
            s += 384;
            work->needleX += (gSineTable[(u8)work->angle] * s) >> 8;
            work->needleY += (-gSineTable[(u8)work->angle + 64] * s) >> 8;
            ClampBattlePosition(&work->needleX, &work->needleY, 0, 0);
            HumFaceTarget(&w->base, 1);

            if (w->base.stateTimer % 9 == 0) {
                args.x = work->needleX;
                args.y = work->needleY;
                args.z = 0;
                args.facingLeft = work->needleCount % 8;
                args.tiles = &work->needleTiles;
                work->needleCount++;
                TaskCreate(&work->tasks, &sTaskDescHumVixenNdl, &args);
            }
        }

        if (w->base.stateTimer > 360 || (gBtlWork->actor->flags & BTLOBJ_FLAG_HURT)) {
            w->base.state = 27;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 27:
        if (w->base.stateTimer > 70) {
            ClearBtlObjActionFlags(act);
            w->base.state = 0;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 28:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 8, 0, work->base.tiles);
            work->hoverZ = 0;
            FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
        }

        if (AnimGetFrame(&w->base.anim) > 4 && !BgFxIsActive()) {
            m4aSongNumStart(SONG_VO_VIC_ATTACK02);
            m4aSongNumStart(SONG_BTL_VIC_ICEFALL);
            BgFxStartVixenIceFall(9999);
        }

        if (w->base.stateTimer % 15 == 0) {
            t = gBtlWork->actor->hp;

            if ((s16)t > 1) {
                gBtlWork->actor->hp = t - 1;
            }
        }

        if (w->base.stateTimer > 300 ||
            (w->base.stateTimer > 120 && gBtlWork->actor->hp <= 1)) {
            m4aSongNumStop(SONG_BTL_VIC_ICEFALL);
            FadeToOriginal(FADE_MODE_BLACK, 8);
            gBtlWork->flags |= BTL_FLAG_STOP_BGFX;
            ClearBtlObjActionFlags(act);
            w->base.state = 0;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 29:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 9, 0, work->base.tiles);
            work->hoverZ = 0;
        }

        if (AnimIsFinished(&w->base.anim)) {
            w->base.stateTimer = 0;
            w->base.state = 30;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 30:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 10, ANIM_FLAG_LOOP, work->base.tiles);
        }

        if (w->base.stateTimer > 60) {
            w->base.stateTimer = 0;
            w->base.state = 31;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 31:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 11, 0, work->base.tiles);
        }

        if (AnimIsFinished(&w->base.anim)) {
            w->base.stateTimer = 0;
            w->base.state = 32;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 32:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 4, 0, work->base.tiles);
        }

        if (AnimGetFrame(&w->base.anim) == 3 && w->base.anim.timer == 0) {
            FadeStartIn(FADE_MODE_WHITE, 60);
            VixenPlaceGroundIce(work);
        }

        if (AnimIsFinished(&w->base.anim) && !FadeIsActive()) {
            ClearBtlObjActionFlags(act);
            w->base.state = 0;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 33:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 12, 0, work->base.tiles);
            work->hoverZ = 0;
        }

        if (AnimIsFinished(&w->base.anim)) {
            w->base.stateTimer = 0;
            w->base.state = 34;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 34:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 13, ANIM_FLAG_LOOP, work->base.tiles);
        }

        if (w->base.stateTimer > 60) {
            w->base.stateTimer = 0;
            w->base.state = 35;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 35:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 14, 0, work->base.tiles);
            m4aSongNumStart(SONG_VO_VIC_ATTACK00);
        }

        if (AnimIsFinished(&w->base.anim)) {
            w->base.stateTimer = 0;
            w->base.state = 36;
        } else {
            w->base.stateTimer++;
        }

        break;
    case 36:
        if (w->base.stateTimer == 0) {
            AnimChangeWithDef(sHumVixenAnimDefs, &work->base.anim, 4, 0, work->base.tiles);
            work->task = NULL;
        }

        if (AnimGetFrame(&w->base.anim) == 3 && w->base.anim.timer == 0) {
            args.x = x;
            args.y = y;
            args.z = 0;
            work->task = TaskCreate(&work->tasks, &sTaskDescHumVixenFrz, &args);
        }

        if (AnimIsFinished(&w->base.anim) &&
            !IsTaskActiveNamed(work->task, sTaskDescHumVixenFrz.name)) {
            ClearBtlObjActionFlags(act);
            w->base.state = 0;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }

        break;
    }

    if (!(act->flags & BTLOBJ_FLAG_HURT) && act->badStatus != BAD_STATUS_STOP) {
        VixenHover(&w->base, work->hoverZ);
    }

    r = HumUpdate(&w->base);
    cx = gBtlWork->actor->x;
    ax = act->x;

    if ((cx < ax && (act->flags & BTLOBJ_FLAG_FACING_LEFT)) || (cx > ax && !(act->flags & BTLOBJ_FLAG_FACING_LEFT))) {
        act->flags |= BTLOBJ_FLAG_GUARD_PHYSICAL;
    } else {
        act->flags &= ~BTLOBJ_FLAG_GUARD_PHYSICAL;
    }

    TaskPoolUpdate(&work->tasks);
    return r;
}

void task_hum_vixen_2(VixenWork* work) {
    HumDraw(&work->base);
    TaskPoolDraw(&work->tasks);
}

void task_hum_vixen_3(VixenWork* work) {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        ReleaseObjTiles(gBtlWork->tiles2);
    }

    HumReleaseResources(&work->base);
    TaskPoolDestroy(&work->tasks);
}

void task_hum_vixen_ndl_0(VixenNdlWork* work, VixenNdlArgs* args) {
    work->palette = LoadObjPalette(gVixEPalette, 0x20);
    work->tiles = args->tiles;
    AnimInit(&work->anim, gVixenE1Anims, gVixenE1Frames);
    AnimStart(&work->anim, 0, 0);
    work->hitPhase = args->facingLeft;
    work->x = args->x;
    work->y = args->y + (GetRandom() % 11 - 5) * 256;
    work->z = args->z;
    work->hitDone = 0;
    m4aSongNumStart(SONG_BTL_VIC_ICEP);

    if ((GetRandom() & 1) != 0) {
        work->flipped = 1;
    } else {
        work->flipped = 0;
    }
}

u8 task_hum_vixen_ndl_1(VixenNdlWork* work) {
    if ((gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) == 0) {
        return 0;
    }

    if (AnimIsFinished(&work->anim)) {
        return 0;
    }

    switch (AnimGetFrame(&work->anim)) {
    case 1:
    case 2:
        if (!work->hitDone) {
            if (gFrameCounter % 8 == work->hitPhase) {
                ApplyAttackBox(0x13A, work->x, work->y, 0, 4, 4, 16);
            }
        }

        break;
    }

    if (gBtlWork->actor->flags & BTLOBJ_FLAG_HURT) {
        work->hitDone = 1;
    }

    AnimUpdate(&work->anim);
    return 1;
}

void task_hum_vixen_ndl_2(VixenNdlWork* work) {
    s16 x;
    s16 y;
    void* gfx;
    u16 attr;

    gfx = AnimGetGfx(&work->anim);
    attr = GetBattleSpritePriorityFlags(work->y);

    if (work->flipped) {
        attr |= 1;
    }

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gfx, work->tiles, work->palette, NULL, attr,
        -0x1004 - (work->y >> 8) * 4);
}

void task_hum_vixen_ndl_3(VixenNdlWork* work) {
    ReleaseObjPalette(work->palette);
}

void task_hum_vixen_ice_0(VixenIceWork* work, VixenSub* args) {
    work->palette = LoadObjPalette(gVixEPalette, 0x20);
    work->tiles = LoadObjTiles(gVixenE2Tiles, 0x800);
    work->sub = args;
    work->state = 3;
    AnimInit(&work->anim, gVixenE2Anims, gVixenE2Frames);
    AnimStart(&work->anim, 0, 0);
    ColliderInit(&work->collider, 12, 27, 1);
    ColliderSetDisabled(&work->collider, 1);
}

u8 task_hum_vixen_ice_1(VixenIceWork* work) {
    if (work->sub->active == 0) {
        if (work->sub->pending != 0) {
            FadeSetPaletteExcluded(work->palette->index + 16, 1);
            work->sub->pending = 0;
            ColliderSetDisabled(&work->collider, 1);
        }

        return 1;
    }

    if (work->sub->pending != 0) {
        FadeSetPaletteExcluded(work->palette->index + 16, 0);
        work->sub->pending = 0;
        work->state = 0;
        work->stateTimer = 0;
        work->scale = 10;

        switch (GetRandom() % 3) {
        case 0:
            work->targetScale = 0x100;
            break;
        case 1:
            work->targetScale = 0xC0;
            break;
        case 2:
            work->targetScale = 0x80;
            break;
        }
    }

    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            work->steps = 30;
            work->stateTimer++;
        }

        ApproachValue(&work->scale, work->targetScale, work->steps);
        work->steps--;

        if ((s16)work->steps <= 0) {
            ColliderSetDisabled(&work->collider, 0);
            work->state = 1;
            work->stateTimer = 0;
            work->lifetime = GetRandom() % 0x259 + 600;
        }

        break;
    case 1:
        if (work->stateTimer == 0) {
            AnimStart(&work->anim, 0, 0);
            work->stateTimer++;
        }

        if (GetRandom() % 300 == 0) {
            work->state = 2;
            work->stateTimer = 0;
        }

        break;
    case 2:
        if (work->stateTimer == 0) {
            AnimStart(&work->anim, 1, 0);
            work->stateTimer++;
        }

        if (AnimIsFinished(&work->anim)) {
            work->state = 1;
            work->stateTimer = 0;
        }

        break;
    }

    switch (work->state) {
    case 1:
    case 2:
        ApproachValue(&work->scale, 10, work->lifetime);
        work->lifetime--;

        if ((s16)work->lifetime <= 0) {
            work->sub->active = 0;
            work->sub->pending = 1;
        }

        ColliderSetRadius(&work->collider, work->scale * 27 >> 8);
        ColliderSetPosition(&work->collider, work->sub->x, work->sub->y, 0);
        break;
    }

    AnimUpdate(&work->anim);
    return 1;
}

void task_hum_vixen_ice_2(VixenIceWork* work) {
    s16 x;
    s16 y;
    void* gfx;
    s32 s;
    ObjAffine* affine;

    if (work->sub->active != 0) {
        gfx = AnimGetGfx(&work->anim);
        WorldToScreen(&x, &y, work->sub->x, work->sub->y, 0);
        s = work->scale * gBtlWork->scale >> 8;

        if (gBtlWork->rotation != 0 || s > 0x100) {
            affine = AllocObjAffine(gBtlWork->rotation, s, s, 1);
        } else {
            affine = AllocObjAffine(gBtlWork->rotation, s, s, 0);
        }

        DrawSprite(x, y, gfx, work->tiles, work->palette, affine, SPRITE_PRIORITY(2), 0xFFFF);
    }
}

void task_hum_vixen_ice_3(VixenIceWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

void task_hum_vixen_frz_0(VixenFrzWork* work, VixenNdlArgs* args) {
    work->palette = LoadObjPalette(gVixEPalette, 0x20);
    work->tiles = gBtlWork->tiles2;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        if (gBtlWork->flags & BTL_FLAG_DARK_MODE) {
            work->variant = 2;
        } else {
            work->variant = 1;
        }
    } else {
        work->variant = 0;
    }

    AnimInit(&work->anim, NULL, NULL);
    AnimChangeWithDef(sHumVixenFrzAnimDefs, &work->anim, 0, 0, work->tiles);
    work->state = 0;

    if (gBtlWork->actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
        work->flipped = 0;
    } else {
        work->flipped = 1;
    }

    m4aSongNumStart(SONG_EF_BURIZA02);
    work->x = args->x;
    work->y = args->y;
    work->z = args->z;
}

u8 task_hum_vixen_frz_1(VixenFrzWork* work) {
    VixenNdlArgs args;
    VixenNdlArgs args2;

    if ((gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) == 0) {
        return 0;
    }

    switch (work->state) {
    case 1:
        if (work->timer == 0) {
            switch (work->variant) {
            case 0:
                AnimChangeWithDef(sHumVixenFrzAnimDefs, &work->anim, 2, 0, work->tiles);
                break;
            case 1:
                AnimChangeWithDef(sHumVixenFrzAnimDefs, &work->anim, 7, 0, work->tiles);
                break;
            case 2:
                AnimChangeWithDef(sHumVixenFrzAnimDefs, &work->anim, 10, 0, work->tiles);
                break;
            }
        }

        work->x = gBtlWork->actor->x;
        work->y = gBtlWork->actor->y;
        work->z = gBtlWork->actor->z;

        if (AnimIsFinished(&work->anim)) {
            work->state = 2;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 2:
        if (work->timer == 0) {
            switch (work->variant) {
            case 0:
                AnimChangeWithDef(sHumVixenFrzAnimDefs, &work->anim, 4, 0, work->tiles);
                break;
            case 1:
                AnimChangeWithDef(sHumVixenFrzAnimDefs, &work->anim, 8, 0, work->tiles);
                break;
            case 2:
                AnimChangeWithDef(sHumVixenFrzAnimDefs, &work->anim, 11, 0, work->tiles);
                break;
            }
        }

        work->x = gBtlWork->actor->x;
        work->y = gBtlWork->actor->y;
        work->z = gBtlWork->actor->z;

        if (gBtlWork->flags & 0x100000) {
            work->state = 3;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 3:
        if (work->timer == 0) {
            switch (work->variant) {
            case 0:
                AnimChangeWithDef(sHumVixenFrzAnimDefs, &work->anim, 6, 0, work->tiles);
                break;
            case 1:
                AnimChangeWithDef(sHumVixenFrzAnimDefs, &work->anim, 9, 0, work->tiles);
                break;
            case 2:
                AnimChangeWithDef(sHumVixenFrzAnimDefs, &work->anim, 12, 0, work->tiles);
                break;
            }
        }

        work->x = gBtlWork->actor->x;
        work->y = gBtlWork->actor->y;
        work->z = gBtlWork->actor->z;

        if (AnimIsFinished(&work->anim)) {
            args.x = work->x;
            args.y = work->y;
            args.z = work->z;
            TaskCreate(&gBtlWork->taskPools[0], &sTaskDescHumVixenFrg, &args);
            work->state = 6;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 0:
        if (!AnimIsFinished(&work->anim)) {
            break;
        }

        if (TestAttackBox(work->x, work->y, work->z, 8, 8, 1)) {
            gBtlWork->actor->x = work->x;
            gBtlWork->actor->y = work->y;
            gBtlWork->actor->z = work->z;
            gBtlWork->actor->flags |= (BTLOBJ_FLAG_CARD_USE_BLOCKED | BTLOBJ_FLAG_FREEZE_PENDING);
            work->state = 1;
            gBtlWork->flags &= ~0x100000;
            work->timer = 0;
        } else {
            work->state = 4;
            work->timer = 0;
        }

        break;
    case 4:
        if (work->timer == 0) {
            AnimChangeWithDef(sHumVixenFrzAnimDefs, &work->anim, 1, 0, work->tiles);
        }

        if (AnimIsFinished(&work->anim)) {
            work->state = 5;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 5:
        if (work->timer == 0) {
            AnimChangeWithDef(sHumVixenFrzAnimDefs, &work->anim, 5, 0, work->tiles);
        }

        if (AnimIsFinished(&work->anim)) {
            args2.x = work->x;
            args2.y = work->y;
            args2.z = work->z;
            TaskCreate(&gBtlWork->taskPools[0], &sTaskDescHumVixenFrg, &args2);
            work->state = 6;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 6:
        if (work->timer > 80) {
            return 0;
        }

        work->timer++;
        break;
    }

    AnimUpdate(&work->anim);
    return 1;
}

void task_hum_vixen_frz_2(VixenFrzWork* work) {
    s16 x;
    s16 y;
    void* gfx;
    u16 attr;

    if (work->state != 6) {
        gfx = AnimGetGfx(&work->anim);
        attr = GetBattleSpritePriorityFlags(work->y) | work->flipped;
        WorldToScreen(&x, &y, work->x, work->y, work->z);
        DrawSprite(x, y, gfx, work->tiles, work->palette, NULL, attr,
            -0x1004 - (work->y >> 8) * 4);
    }
}

void task_hum_vixen_frz_3(VixenFrzWork* work) {
    ReleaseObjPalette(work->palette);
}

void task_hum_vixen_frg_0(VixenFrgWork* work, VixenNdlArgs* args) {
    VixenFrgSub* e;
    s32 i;
    s32 a;
    s32 b;

    InitObjTilesAtSlot(&work->tilesSlot, ((ObjTiles*)gBtlWork->tiles2)->index, gVixenReitouHahenTiles, 0x4C0);
    work->tiles = &work->tilesSlot;
    work->palette = LoadObjPalette(gVixEPalette, 0x20);
    work->timer = 0;
    work->blinking = 0;

    for (i = 0; i < 15; i++) {
        const VixenFrgDef* d = &sVixenFrgDefs[i];
        e = &work->sub[i];
        e->x = args->x + (d->x << 8);
        e->y = args->y;
        e->z = args->z + (d->z << 8);
        e->spriteFlags = d->spriteFlags;
        e->gfx = gVixenReitouHahenFrames[d->frame];
        e->vz = GetRandom() % 0x401 - 0x500;
        a = (u8)GetRandom();
        b = GetRandom() % 0x380;
        e->vx = gSineTable[a] * b >> 8;
        e->vy = -gSineTable[a + 64] * (b >> 1) >> 8;
    }

    m4aSongNumStart(SONG_EF_VIC_ICEBREAK);
}

u8 task_hum_vixen_frg_1(VixenFrgWork* work) {
    VixenFrgSub* e;
    s32 i;

    if (gBtlWork->flags & BTL_FLAG_SUMMON_ACTIVE) {
        return 0;
    }

    for (i = 0; i < 15; i++) {
        e = &work->sub[i];
        e->x += e->vx;
        e->y += e->vy;
        e->z += e->vz;
        e->vz += gBtlWork->gravity;

        if (e->z > 0) {
            e->z = 0;
            e->vz = -(e->vz >> 1);
            e->vx = e->vx >> 1;
            e->vy = e->vy >> 1;
        }

        ClampBattlePosition(&e->x, &e->y, 0, 0);
    }

    work->timer++;

    if (work->timer == 50) {
        work->blinking = 1;
    }

    if (work->timer > 70) {
        return 0;
    }

    return 1;
}

void task_hum_vixen_frg_2(VixenFrgWork* work) {
    VixenFrgSub* p;
    s16 x;
    s16 y;
    u16 attr;
    s32 i;

    if (work->blinking) {
        if (work->timer & 1) {
            return;
        }
    }

    p = work->sub;

    for (i = 0; i < 15; i++) {
        attr = GetBattleSpritePriorityFlags(p[i].y) | p[i].spriteFlags;
        WorldToScreen(&x, &y, p[i].x, p[i].y, p[i].z);
        DrawSprite(x, y, p[i].gfx, work->tiles, work->palette, NULL, attr,
            -0x1004 - (p[i].y >> 8) * 4);
    }
}

void task_hum_vixen_frg_3(VixenFrgWork* work) {
    ReleaseObjPalette(work->palette);
}
