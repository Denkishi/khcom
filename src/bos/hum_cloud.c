/**
 * hum_cloud.c
 * Cloud Boss
 */

#include "system_state.h"
#include "fade.h"
#include "hum.h"
#include "sprites_cloud.h"
#include "sprites_hum.h"
#include "hum_common.h"
#include "songs.h"
#include "hum_tasks.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "card_api.h"
#include "engine_math.h"
#include "hum_types.h"
#include "m4a_song.h"
#include "mode_chkobj_assets.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

static const u32 sHumCloudStockMoves[2][3] = {
    { 37, 37, 37 },
    { 37, 36, 37 },
};

static const AnimDef sHumCloudAnimDefs[20] = {
    { gCroudBt00Frames, gCroudBt00Anims, gCroudBt00Tiles, 0, { 0, 0, 0 } },
    { gCroudBt01Frames, gCroudBt01Anims, gCroudBt01Tiles, 0, { 0, 0, 0 } },
    { gCroudBt02Frames, gCroudBt02Anims, gCroudBt02Tiles, 0, { 0, 0, 0 } },
    { gCroudBt03Frames, gCroudBt03Anims, gCroudBt03Tiles, 0, { 0, 0, 0 } },
    { gCroudBt03Frames, gCroudBt03Anims, gCroudBt03Tiles, 1, { 0, 0, 0 } },
    { gCroudBt03Frames, gCroudBt03Anims, gCroudBt03Tiles, 2, { 0, 0, 0 } },
    { gCroudBt03Frames, gCroudBt03Anims, gCroudBt03Tiles, 3, { 0, 0, 0 } },
    { gCroudBt03Frames, gCroudBt03Anims, gCroudBt03Tiles, 4, { 0, 0, 0 } },
    { gCroud01Frames, gCroud01Anims, gCroud01Tiles, 2, { 0, 0, 0 } },
    { gCroud01Frames, gCroud01Anims, gCroud01Tiles, 2, { 0, 0, 0 } },
    { gCroud00Frames, gCroud00Anims, gCroud00Tiles, 0, { 0, 0, 0 } },
    { gCroud00Frames, gCroud00Anims, gCroud00Tiles, 1, { 0, 0, 0 } },
    { gCroud00Frames, gCroud00Anims, gCroud00Tiles, 2, { 0, 0, 0 } },
    { gCroud00Frames, gCroud00Anims, gCroud00Tiles, 3, { 0, 0, 0 } },
    { gCroud10Frames, gCroud10Anims, gCroud10Tiles, 0, { 0, 0, 0 } },
    { gCroud11Frames, gCroud11Anims, gCroud11Tiles, 0, { 0, 0, 0 } },
    { gCroud12Frames, gCroud12Anims, gCroud12Tiles, 0, { 0, 0, 0 } },
    { gCroud13Frames, gCroud13Anims, gCroud13Tiles, 0, { 0, 0, 0 } },
    { gCroud01Frames, gCroud01Anims, gCroud01Tiles, 0, { 0, 0, 0 } },
    { gCroud02Frames, gCroud02Anims, gCroud02Tiles, 0, { 0, 0, 0 } },
};

static const HumDef sHumCloudDef = { 128, 0, gCroudPalette, 0, { 43, 99, 38, 14, 24, 99, 0 } };

TaskDesc gTaskDescHumCloud = {
    "task_hum_cloud",
    (TaskInitFunc)task_hum_cloud_0,
    (TaskUpdateFunc)task_hum_cloud_1,
    (TaskDrawFunc)task_hum_cloud_2,
    (TaskDestroyFunc)task_hum_cloud_3,
    sizeof(CloudWork),
};

void CloudJumpOffset(CloudWork* work, s16 a, s32 b) {
    CloudWork* w = work;
    BtlObj* obj = &work->base.actor;

    if (obj->flags & BTLOBJ_FLAG_FACING_LEFT) {
        work->base.targetX = obj->x - (a << 8);
    } else {
        work->base.targetX = obj->x + (a << 8);
    }

    w->base.targetY = obj->y;
    w->base.state = 0x19;
    w->base.stateTimer = 0;
    work->speed = -b;
    work->state = 0;
}

void CloudJumpTo(CloudWork* work, s32 a, s32 b) {
    work->base.targetX = a;
    work->base.targetY = b;
    work->base.state = 0x19;
    work->base.stateTimer = 0;
    work->speed = -0x500;
    work->nextState = 0;
}

void CloudLeapTo(CloudWork* work, s32 a, s32 b) {
    work->base.targetX = a;
    work->base.targetY = b;
    work->base.state = 0x21;
    work->base.stateTimer = 0;
}

s32 CloudTryJumpAway(CloudWork* work) {
    s32 x;
    s32 y;
    BtlObj* obj;

    obj = gBtlWork->actor;

    if (GetRandom() % 60 == 0) {
        GetEnemyTargetPosition(&work->base.actor, &x, &y, NULL);
        HumFaceTarget(&work->base, 1);

        if (HumIsInPlayerReach(&work->base, 0x100, 0x100, 0x100)) {
            if (gBtlWork->flags & BTL_FLAG_PLAYER_AIRBORNE) {
                CloudJumpOffset(work, -0x63, 0x280);
            } else if (GetRandom() & 1) {
                if (obj->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    CloudJumpTo(work, x + 0x2800, y);
                } else {
                    CloudJumpTo(work, x - 0x2800, y);
                }
            } else {
                CloudJumpOffset(work, -0x50, 0x500);
            }

            return 1;
        }
    }

    return 0;
}

void task_hum_cloud_0(CloudWork* work, void* obj) {
    HumInit(&work->base, &sHumCloudDef);
    work->speed = 0;
    work->base.stockMoves = sHumCloudStockMoves[0];
}

u8 task_hum_cloud_1(CloudWork* work) {
    CloudWork* w;
    BtlObj* act;
    s32 x;
    s32 y;
    s32 z;
    u8 ret;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &x, &y, &z);

    switch (HumUpdateReaction(&work->base)) {
    case 5:
        work->base.stateTimer = 0;

        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
        case 38:
            if (act->z < 0) {
                work->base.state = 21;
            } else {
                work->base.state = 19;
            }

            break;
        case 37:
        case 39:
            if (act->z < 0) {
                work->base.state = 21;
            } else {
                work->base.state = 20;
            }

            break;
        case 0xEB3ACEB3:
            work->base.state = 31;
            break;
        case 0xEB3AA6B3:
            work->base.state = 28;
            break;
        }

        break;
    case 4:
        work->nextState = 0;
        break;
    }

    if (HumChooseCardAction(&work->base, 8, 32, 32, 24)) {
        if (GetRandom() % 2) {
            work->base.stockMoves = sHumCloudStockMoves[0];
        } else {
            work->base.stockMoves = sHumCloudStockMoves[1];
        }
    }

    switch (work->base.state) {
    case 12:
    case 18:
        AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        break;
    case 17: {
        AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START, w->base.tiles);

        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            if ((u8)CloudTryJumpAway(w)) {
                break;
            }
        }

        if ((act->x - x >= 0) ? act->x - x <= 0x4FFF : x - act->x <= 0x4FFF) {
            if (x <= 0xFFFF) {
                CloudLeapTo(w, (gBtlWork->xMax - 40) << 8,
                    (gBtlWork->yMin + gBtlWork->yMax) << 7);
            } else {
                CloudLeapTo(w, (gBtlWork->xMin + 40) << 8,
                    (gBtlWork->yMin + gBtlWork->yMax) << 7);
            }
        }

        break;
    }
    case 0:
        AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START, w->base.tiles);

        if (func_08081828()) {
            break;
        }

        if ((u16)(GetRandom() % 60) == 0) {
            work->base.state = 8;
            work->base.stateTimer = 0;
            break;
        }

        if (HumIsNearAreaEdge(&work->base, 40)) {
            CloudLeapTo(w, 0x10000,
                (gBtlWork->yMin + gBtlWork->yMax) << 7);
            break;
        }

        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            if ((u8)CloudTryJumpAway(w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 30);
        }

        work->base.stateTimer++;
        break;
    case 8: {
        AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 1, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START, w->base.tiles);
        work->base.targetX = x;
        work->base.targetY = y;

        if (HumMoveToward(&work->base, work->base.targetX, y, 0x133)) {
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }

        if ((u16)(GetRandom() % 150) == 0) {
            if ((act->x - x >= 0) ? act->x - x > 70 : x - act->x > 70) {
                CloudJumpTo(w, x, y);
                break;
            }
        }

        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            if ((u8)CloudTryJumpAway(w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 30);
        }

        work->base.stateTimer++;
        break;
    }
    case 1:
    case 3:
    case 9:
    case 11:
    case 14:
        AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        break;
    case 19:
        if (work->base.stateTimer == 0) {
            AnimReset(&work->base.anim);
            AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 8, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_MKU_ATTACK00);
            MakeOpponentsHittable();
        }

        if (AnimGetFrame(&work->base.anim) == 6) {
            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                ? ApplyAttackBox(0x11A, act->x - 9216, act->y, act->z, 24, 16, 50)
                : ApplyAttackBox(0x11A, act->x + 9216, act->y, act->z, 24, 16, 50)) {
                m4aSongNumStart(SONG_EF_KU_ATT00);
            }
        } else if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }

        work->base.stateTimer++;
        break;
    case 20:
        if (work->base.stateTimer == 0) {
            AnimReset(&work->base.anim);
            AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_MKU_ATTACK01);
            MakeOpponentsHittable();
        }

        if (AnimGetFrame(&work->base.anim) == 6) {
            if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                ? ApplyAttackBox(0x11A, act->x - 8192, act->y, act->z, 22, 16, 50)
                : ApplyAttackBox(0x11A, act->x + 8192, act->y, act->z, 22, 16, 50)) {
                m4aSongNumStart(SONG_EF_KU_ATT01);
            }
        } else if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }

        work->base.stateTimer++;
        break;
    case 25:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
        }

        if (work->base.stateTimer > 3) {
            work->base.stateTimer = 0;
            work->base.state = 26;
            work->base.vz = w->speed;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 26: {
        s32 d;

        act->x += (work->base.targetX - act->x) >> 4;
        act->y += (work->base.targetY - act->y) >> 4;
        d = work->base.vz;

        if (d < 0) {
            if (d <= -0x200) {
                AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            }
        } else if (d <= 0x1FF) {
            AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
        } else {
            AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
        }

        if (act->z >= 0) {
            work->base.stateTimer = 0;
            work->base.state = 27;
        } else {
            HumFaceTarget(&work->base, 1);
            work->base.stateTimer++;
        }

        break;
    }
    case 27:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 7, 0, w->base.tiles);
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = w->nextState;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 33: {
        s32 d;

        if (work->base.stateTimer == 0) {
            work->base.vz = -0x500;
        }

        d = work->base.vz;

        if (d < 0) {
            if (d > -0x200) {
                AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            }
        }

        if (work->base.vz > 0) {
            work->base.stateTimer = 0;
            work->base.state = 34;
        } else {
            work->base.stateTimer++;
        }

        break;
    }
    case 34: {
        s32 d;

        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 14, 0, w->base.tiles);
            w->speed = 0;
            work->base.targetZ = act->z;
        }

        ret = HumMoveToward(&work->base, work->base.targetX, work->base.targetY, w->speed);

        if (ret) {
            work->base.state = 26;
            w->nextState = 0;
            work->base.stateTimer = 0;
        } else {
            w->speed += 76;

            if ((s32)w->speed > 0x800) {
                w->speed = 0x800;
            }

            d = (work->base.targetX - act->x) >> 3;

            if (d < 0) {
                d = -d;
            }

            if (d < (s32)w->speed) {
                w->speed = d;
            }

            {
                s32 v = work->base.targetZ + SIN(gFrameCounter * 4) * 12;
            work->base.vz = 0;
            act->z += (v - act->z) >> 3;
            }

            if (act->x < work->base.targetX) {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            } else {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            }

            work->base.stateTimer++;
        }

        break;
    }
    case 21: {
        s32 d;

        if (work->base.stateTimer == 0) {
            AnimReset(&work->base.anim);
            AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 10, 0, w->base.tiles);
        }

        act->z += (gSineTable[gFrameCounter % 256] * 10 - (d = act->z + 0x2C00)) >> 3;

        if (act->x < x) {
            s32 d = act->x + 0x2100;
            act->x += (x - d) >> 3;
        } else {
            s32 d = act->x - 0x2100;
            act->x += (x - d) >> 3;
        }

        act->y += (y - act->y) >> 4;
        work->base.vz = 0;

        if (work->base.stateTimer > 30) {
            work->base.state = 22;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    }
    case 22:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 11, 0, w->base.tiles);
        }

        work->base.vz = 0;

        if (work->base.stateTimer > 8) {
            work->base.vz = 0x500;
            work->base.state = 23;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 23:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
        }

        if (act->z >= 0) {
            work->base.state = 24;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 24:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 13, 0, w->base.tiles);
        }

        if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
            ? ApplyAttackBox(0x11A, act->x - 0x2000, act->y, act->z, 22, 16, 30)
            : ApplyAttackBox(0x11A, act->x + 0x2000, act->y, act->z, 22, 16, 30)) {
            m4aSongNumStart(SONG_EF_KU_ATT02);
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 31:
        if (act->z >= act->groundZ) {
            s32 v;
            work->base.targetX = x + (v = ((u16)(GetRandom() % 41) << 8) - 0x1400);
            work->base.targetY = y;
            work->base.state = 25;
            work->base.stateTimer = 0;
            w->speed = -0x500;
            w->nextState = 32;
        }

        break;
    case 32: {
        s32 d;

        if (work->base.stateTimer == 0) {
            w->attackPhase = 0;
            AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 18, 0, w->base.tiles);
        } else if ((s16)w->attackPhase == 0 && AnimIsFinished(&work->base.anim)) {
            AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 19, 0, w->base.tiles);
            w->attackPhase++;
        } else if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            w->nextState = 0;
            work->base.stateTimer = 0;
            break;
        }

        HumFaceTarget(&work->base, 1);

        if (work->base.anim.timer == 0) {
            if ((s16)w->attackPhase == 0) {
                switch (AnimGetFrame(&work->base.anim)) {
                case 2:
                    m4aSongNumStart(SONG_VO_MKU_ATTACK00);
                    break;
                case 6:
                    if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                        ? ApplyAttackBox(0x11B, act->x - 0x2800, act->y, act->z, 24, 24, 48)
                        : ApplyAttackBox(0x11B, act->x + 0x2800, act->y, act->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT00);
                        FadeStartIn(FADE_MODE_ADD_WHITE, 20);

                        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                            SetBattleZoom(6, 0x133, act->x - 0x2000, (d = act->z - 0x1800, act->y + d));
                        } else {
                            SetBattleZoom(6, 0x133, act->x + 0x2000, (d = act->z - 0x1800, act->y + d));
                        }
                    }

                    break;
                case 7:
                    SetBattleZoom(6, 0x100, gBtlWork->x2, gBtlWork->y2);
                    break;
                case 9:
                    m4aSongNumStart(SONG_VO_MKU_ATTACK01);
                    break;
                }
            } else {
                switch (AnimGetFrame(&work->base.anim)) {
                case 0:
                    MakeOpponentsHittable();

                    if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                        ? ApplyAttackBox(0x11B, act->x - 0x2800, act->y, act->z, 24, 24, 48)
                        : ApplyAttackBox(0x11B, act->x + 0x2800, act->y, act->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT01);
                        FadeStartIn(FADE_MODE_ADD_WHITE, 20);

                        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                            SetBattleZoom(6, 0x133, act->x - 0x2000, (d = act->z - 0x1800, act->y + d));
                        } else {
                            SetBattleZoom(6, 0x133, act->x + 0x2000, (d = act->z - 0x1800, act->y + d));
                        }
                    }

                    break;
                case 1:
                    SetBattleZoom(6, 0x100, gBtlWork->x2, gBtlWork->y2);
                    break;
                case 4:
                    m4aSongNumStart(SONG_VO_MKU_ATTACK02);
                    break;
                case 5:
                    MakeOpponentsHittable();

                    if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                        ? ApplyAttackBox(0x11C, act->x - 0x2800, act->y, act->z, 24, 24, 48)
                        : ApplyAttackBox(0x11C, act->x + 0x2800, act->y, act->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT02);
                        FadeStartIn(FADE_MODE_ADD_WHITE, 50);

                        if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                            SetBattleZoom(6, 0x200, act->x - 0x2000, (d = act->z - 0x1800, act->y + d));
                        } else {
                            SetBattleZoom(6, 0x200, act->x + 0x2000, (d = act->z - 0x1800, act->y + d));
                        }
                    }

                    break;
                case 6:
                    SetBattleZoom(6, 0x100, gBtlWork->x2, gBtlWork->y2);
                    break;
                }
            }
        }

        work->base.stateTimer++;
        break;
    }
    case 28: {
        s32 d;

        if (work->base.stateTimer == 0) {
            work->base.vz = -0x500;
        }

        d = work->base.vz;

        if (d < 0) {
            if (d > -0x200) {
                AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            }
        }

        if (work->base.vz > 0) {
            work->base.stateTimer = 0;
            work->base.state = 29;
            w->state = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    }
    case 29: {
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 14, 0, w->base.tiles);
            w->speed = 0;

            if (act->flags & BTLOBJ_FLAG_FACING_LEFT) {
                work->base.targetX = (gBtlWork->xMin + 50) << 8;
            } else {
                work->base.targetX = (gBtlWork->xMax - 50) << 8;
            }

            work->base.targetY = act->y;
            work->base.targetZ = -0xC800;
        }

        work->base.vz = 0;
        act->x += (work->base.targetX - act->x) >> 4;
        act->y += (work->base.targetY - act->y) >> 4;

        {
            s32 v;
        v = (work->base.targetZ - act->z) >> 3;

        if (v > (s32)w->speed) {
            v = w->speed;
        }

        if (v < -(s32)w->speed) {
            v = -w->speed;
        }

        act->z += v;
        }

        w->speed += 0x80;

        if ((act->z - work->base.targetZ >= 0) ? act->z - work->base.targetZ <= 0xFFF : work->base.targetZ - act->z <= 0xFFF) {
            work->base.state = 30;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    }
    case 30:
        if (work->base.stateTimer == 0) {
            work->base.targetX = x;
            work->base.targetY = y;
            work->base.targetZ = z - 0x1000;
            MakeOpponentsHittable();

            switch ((s16)w->state) {
            case 0:
                m4aSongNumStart(SONG_VO_MKU_ATTACK00);
                AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 15, 0, w->base.tiles);
                break;
            case 1:
                m4aSongNumStart(SONG_VO_MKU_ATTACK01);
                AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 16, 0, w->base.tiles);
                break;
            case 2:
            default:
                m4aSongNumStart(SONG_VO_MKU_ATTACK02);
                AnimChangeWithDef(sHumCloudAnimDefs, &w->base.anim, 17, 0, w->base.tiles);
                break;
            }

            if (act->x < work->base.targetX) {
                act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            } else {
                act->flags |= BTLOBJ_FLAG_FACING_LEFT;
            }
        }

        work->base.vz = 0;
        act->x += (work->base.targetX - act->x) >> 3;
        act->y += (work->base.targetY - act->y) >> 3;
        act->z += (work->base.targetZ - act->z) >> 3;

        if (work->base.anim.timer == 0) {
            switch ((s16)w->state) {
            case 0:
                if (AnimGetFrame(&work->base.anim) == 4) {
                    if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                        ? ApplyAttackBox(0x11D, act->x - 0x2800, act->y, act->z, 24, 24, 48)
                        : ApplyAttackBox(0x11D, act->x + 0x2800, act->y, act->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT00);
                        FadeStartIn(FADE_MODE_ADD_WHITE, 20);
                    }
                }

                break;
            case 1:
                if (AnimGetFrame(&work->base.anim) == 3) {
                    MakeOpponentsHittable();

                    if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                        ? ApplyAttackBox(0x11D, act->x - 0x2800, act->y, act->z, 24, 24, 48)
                        : ApplyAttackBox(0x11D, act->x + 0x2800, act->y, act->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT01);
                        FadeStartIn(FADE_MODE_ADD_WHITE, 20);
                    }
                }

                break;
            case 2:
            default:
                if (AnimGetFrame(&work->base.anim) == 3) {
                    MakeOpponentsHittable();

                    if ((act->flags & BTLOBJ_FLAG_FACING_LEFT)
                        ? ApplyAttackBox(0x11D, act->x - 0x2800, act->y, act->z, 24, 24, 48)
                        : ApplyAttackBox(0x11D, act->x + 0x2800, act->y, act->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT02);
                        FadeStartIn(FADE_MODE_ADD_WHITE, 20);
                    }
                }

                break;
            }
        }

        if (work->base.stateTimer > 23 && AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            w->state++;

            if ((s16)w->state > 2) {
                ClearBtlObjActionFlags(act);
                work->base.state = 26;
                w->nextState = 0;
            } else {
                work->base.state = 29;
            }
        } else {
            work->base.stateTimer++;
        }

        break;
    }

    return HumUpdate(&work->base);
}

void task_hum_cloud_2(HumWork* work) {
    HumDraw(work);
}

void task_hum_cloud_3(HumWork* work) {
    HumReleaseResources(work);
}
