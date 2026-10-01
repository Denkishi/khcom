#include "macros.h"
#include "bos2.h"
#include "sprites_bos2.h"
#include "system_state.h"
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
#include "display.h"
#include "engine_math.h"
#include "gba/defines.h"
#include "m4a_song.h"
#include "mode_battle_data.h"
#include "obj.h"
#include "obj_api.h"
#include "pallet.h"
#include "registration_data.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

void* gBosJfMajinMapBlockTable[4] EWRAM_COMMON(16);
void* gBosJfMajinMapBlocks EWRAM_COMMON(4);
u8 gUnk_0203B504[12] EWRAM_COMMON(4);
u8 gBosJfMajinMapBuffer[0x800] EWRAM_COMMON(16);

void BosJfMajinSetBgFrame(u8 a, u16 b, JfMajinWork* work) {
    BosJfMajinCopyBgMap(a, work);
    SetBgMapBlocks(1, gBosJfMajinMapBlocks, 2, 2);
    LoadBgTiles(1, gBosJfMajinFrameTiles[a], b * 32);
    work->jf->flags &= ~JF_FLAG_NEEDS_BG_CLIP;
}

void BosJfMajinCopyBgMap(u8 a, JfMajinWork* work) {
    s16 n;

    if (work->jf->body.z < -0x8000) {
        RequestDma3Copy(gBosJfMajinFrameMaps[a], gBosJfMajinMapBuffer, 0x800);
    } else {
        n = ((work->jf->body.z >> 8) + 0x88) / 8 + work->extraClipRows;

        if (n > 0x20) {
            RequestDma3Clear(gBosJfMajinMapBuffer, 0x800);
        } else {
            RequestDma3Copy(gBosJfMajinFrameMaps[a], gBosJfMajinMapBuffer, (0x20 - n) * 64);
            RequestDma3Clear(gBosJfMajinMapBuffer + (0x20 - n) * 64, n * 64);
        }
    }
}

void BosJfMajinUpdateBgClip(u8 a, JfMajinWork* work) {
    s16 n;

    if (work->jf->body.z >= -0x8000) {
        n = ((work->jf->body.z >> 8) + 0x88) / 8 + work->extraClipRows;

        if (n > 0x20) {
            RequestDma3Clear(gBosJfMajinMapBuffer, 0x800);
        } else {
            RequestDma3Copy(gBosJfMajinFrameMaps[a], gBosJfMajinMapBuffer, (0x20 - n) * 64);
            RequestDma3Clear(gBosJfMajinMapBuffer + (0x20 - n) * 64, n * 64);
        }

        SetBgMapBlocks(1, gBosJfMajinMapBlocks, 2, 2);
    }
}

#define GET_ACTOR_POSITION(actor, out_x, out_y, out_z) do { \
    (out_x) = (actor)->x; \
    (out_y) = (actor)->y; \
    (out_z) = (actor)->z; \
} while (0)
void task_bos_jf_majin_0(JfMajinWork* work, void* p) {
    JfWork* arg = p;
    s32 x;
    union {
        s32 coordinate;
        BtlWork* bounds;
    } y;
    s32 z;

    work->jf = arg;
    GET_ACTOR_POSITION(&arg->body, x, y.coordinate, z);
    work->step = 0;
    work->stepTimer = 0;
    work->moveSteps = 0;
    work->x = x;
    work->y2 = y.coordinate;
    work->z = z;
    work->baseFrame = 0;
    work->leftLevel = gBosJfLeftPillarLevel;
    work->middleLevel = gBosJfMiddlePillarLevel;
    work->rightLevel = gBosJfRightPillarLevel;
    work->leftTarget = gBosJfLeftPillarLevel;
    work->middleTarget = gBosJfMiddlePillarLevel;
    work->rightTarget = gBosJfRightPillarLevel;
    work->beamAngle = 0;
    work->beamLength = 0;
    work->beamScale = 0x133;
    work->extraClipRows = 0;
    gBosJfMajinMapBlockTable[0] = gUnk_08125E24;
    gBosJfMajinMapBlockTable[1] = gUnk_08125E24;
    gBosJfMajinMapBlockTable[2] = gUnk_08125E24;
    gBosJfMajinMapBlockTable[3] = gBosJfMajinMapBuffer;
    RequestDma3Copy(gUnk_096CAC64, gBosJfMajinMapBuffer, 0x800);
    gBosJfMajinMapBlocks = gBosJfMajinMapBlockTable;
    LoadBgPalette(1, gUnk_096FB584, 32);
    LoadBgTiles(1, gUnk_09665C04, 0x2700);
    SetBgMapBlocks(1, gBosJfMajinMapBlocks, 2, 2);
    work->tiles = LoadObjTiles(gUnk_09682AA4, 0x2800);
    work->palette = LoadObjPalette(gUnk_096FB5A4, 0x60);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    work->spriteVisible = 1;
    work->unk_30 = 0x2A200;
    work->unk_34 = 0x12600;
    work->y = 0;
    work->idleStep = 0;
    x = 0x308;
    AnimInit(&work->anim, gUnk_09EF3B40, gUnk_09EF3A48);
    AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    y.bounds = gBtlWork;
    ScrollBgMapTo(1, ((y.bounds->viewX - arg->body.x) >> 8) + x,
                  ((z = y.bounds->viewY - (arg->body.y + arg->body.z)) >> 8) + 0x126);
    TaskPoolInit(&work->tasks, 2);
    TaskCreate(&work->tasks, &gTaskDescBosJfBorderline, work->jf);
}

#undef GET_ACTOR_POSITION
u8 task_bos_jf_majin_1(JfMajinWork* work) {
    JfWork* jf = work->jf;

    jf->flags |= JF_FLAG_NEEDS_BG_CLIP;

    switch (work->jf->state) {
    case 0:
        BosJfMajinUpdateIdle(work);
        break;
    case 1:
        BosJfMajinUpdateSwitchSide(work);
        break;
    case 2:
        BosJfMajinUpdateRockAttack(work);
        break;
    case 3:
        BosJfMajinUpdateSlam(work);
        break;
    case 4:
        BosJfMajinUpdateBeam(work);
        break;
    case 5:
        BosJfMajinUpdateSweepBeam(work);
        break;
    case 8:
        func_080BFDD4(work);
        break;
    case 6:
        BosJfMajinUpdatePillars(work);
        break;
    case 7:
        BosJfMajinUpdateBreak(work);
        break;
    case 9:
        BosJfMajinUpdateDefeat(work);
        break;
    case 10:
        BosJfMajinUpdateEventIdle(work);
        break;
    case 11:
        BosJfMajinUpdateGimmick(work);
        break;
    }

    ColliderSetPosition(&jf->body.collider, jf->body.x, jf->body.y, jf->body.z);
    TaskPoolUpdate(&work->tasks);

    if (work->jf->flags & JF_FLAG_NEEDS_BG_CLIP) {
        if (work->jf->state != 6) {
            BosJfMajinUpdateBgClip(work->jf->bgFrame, work);
        }
    }

    return 1;
}

void task_bos_jf_majin_2(JfMajinWork* work) {
    JfWork* jf = work->jf;
    void* gfx;
    u16 pal;
    s16 x;
    s16 y;

    if (gBtlWork->paused == 0) {
        if (jf->flags & JF_FLAG_HURT) {
            if (gFrameCounter & 1) {
                LoadPaletteWithEffect(gUnk_08F69BC4, (void*)PLTT, 32);
                gfx = work->palette2;
            } else {
                LoadPaletteWithEffect(gUnk_096FB584, (void*)PLTT, 32);
                gfx = work->palette;
            }
        } else {
            gfx = work->palette;
        }
    } else {
        LoadPaletteWithEffect(gUnk_096FB584, (void*)PLTT, 32);
        gfx = work->palette;
    }

    ScrollBgMapTo(1, ((gBtlWork->viewX - jf->body.x) >> 8) + 776,
                  ((gBtlWork->viewY - (jf->body.y + jf->body.z)) >> 8) + 294);

    if (work->spriteVisible == 1) {
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            pal = GetBattleSpritePriorityFlags(jf->body.y);
        } else {
            pal = GetBattleSpritePriorityFlags(jf->body.y);
            pal |= 1;
        }

        WorldToScreen(&x, &y, jf->body.x, jf->body.y, jf->body.z);
        DrawSprite(x, work->y + (y - 61), work->gfx, work->tiles, gfx, NULL, pal,
                   -4100 - (jf->body.y >> 8) * 4);
    }

    TaskPoolDraw(&work->tasks);
}

void task_bos_jf_majin_3(JfMajinWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
    TaskPoolDestroy(&work->tasks);
}

s32 BosJfGetActorPillar() {
    s32 v = gBtlWork->actor->x;

    if (v < 0x1EA00) {
        return 0;
    }

    if (v < 0x22200) {
        return 1;
    }

    return 2;
}

s32 BosJfMajinGetActorPillarDistance(JfMajinWork* work) {
    s32 v;

    if (work->jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
        v = gBtlWork->actor->x;

        if (v < 0x1EA00) {
            return 2;
        }

        if (v < 0x22200) {
            return 1;
        }

        return 0;
    }

    v = gBtlWork->actor->x;

    if (v > 0x22200) {
        return 2;
    }

    if (v > 0x1EA00) {
        return 1;
    }

    return 0;
}

void BosJfMajinUpdateIdle(JfMajinWork* work) {
    JfWork* jf = work->jf;

    if (jf->stateStep == 0) {
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            jf->bgFrame = 8;
            work->baseFrame = 8;
        } else {
            jf->bgFrame = 28;
            work->baseFrame = 28;
        }

        work->jf->bgFrameTimer = 0;
        BosJfMajinSetBgFrame(work->jf->bgFrame, 0x80, work);
        work->idleStep = 0;
        work->spriteVisible = 1;
        work->jf->stateStep++;
    } else {
        if (jf->bgFrameTimer >= gBosJfMajinFrameDurations[jf->bgFrame]) {
            jf->bgFrameTimer = 0;
            work->jf->bgFrame++;
            work->idleStep++;

            if (work->jf->bgFrame > work->baseFrame + 5) {
                work->jf->bgFrame = work->baseFrame;
                work->idleStep = 0;
            }

            BosJfMajinSetBgFrame(work->jf->bgFrame, 0x80, work);
        }

        work->jf->bgFrameTimer++;
        work->gfx = AnimUpdate(&work->anim);
        work->y = gBosJfMajinIdleOffsets[work->idleStep];

        if (gBtlWork->phase != 0) {
            if (GetRandom() % 80 == 0) {
                BosJfMajinChooseAttack(work);
                work->jf->stateStep = 0;
            }
        }
    }
}

void BosJfMajinUpdateSwitchSide(JfMajinWork* work) {
    JfWork* jf = work->jf;

    if (jf->stateStep == 0) {
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            jf->bgFrame = 0;
        } else {
            jf->bgFrame = 7;
        }

        work->jf->bgFrameTimer = 0;
        BosJfMajinSetBgFrame(work->jf->bgFrame, 0xA0, work);
        work->step = 0;
        work->stepTimer = 0;
        work->spriteVisible = 0;
        work->jf->stateStep++;
    } else {
        switch (work->step) {
        case 0:
            if (jf->bgFrameTimer >= gBosJfMajinFrameDurations[jf->bgFrame]) {
                jf->bgFrameTimer = 0;

                if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                    work->jf->bgFrame++;

                    if (work->jf->bgFrame > 7) {
                        work->jf->bgFrame = 0;
                    }
                } else {
                    work->jf->bgFrame--;

                    if (work->jf->bgFrame < 0) {
                        work->jf->bgFrame = 7;
                    }
                }

                BosJfMajinSetBgFrame(work->jf->bgFrame, 0xA0, work);
            }

            work->jf->bgFrameTimer++;
            jf->body.z += 0x400;
            work->stepTimer++;

            if (work->stepTimer > 40) {
                work->stepTimer = 0;
                work->step++;
            }

            if (work->stepTimer == 21) {
                jf->body.flags |= BTLOBJ_FLAG_UNHITTABLE;
            }

            break;
        case 1:
            work->stepTimer++;

            if (work->stepTimer > 60) {
                work->stepTimer = 0;
                work->jf->bgFrameTimer = 0;

                if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                    jf->body.flags &= ~BTLOBJ_FLAG_FACING_LEFT;
                    jf->body.x = 0x16A00;
                    work->jf->bgFrame = 3;
                } else {
                    jf->body.flags |= BTLOBJ_FLAG_FACING_LEFT;
                    jf->body.x = 0x2A200;
                    work->jf->bgFrame = 3;
                }

                BosJfMajinSetBgFrame(work->jf->bgFrame, 0xA0, work);
                m4aSongNumStart(SONG_BTL_JF_UP);
                work->step++;
            }

            break;
        case 2:
            if (jf->bgFrameTimer >= gBosJfMajinFrameDurations[jf->bgFrame]) {
                jf->bgFrameTimer = 0;

                if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                    work->jf->bgFrame++;

                    if (work->jf->bgFrame > 7) {
                        work->jf->bgFrame = 0;
                    }
                } else {
                    work->jf->bgFrame--;

                    if (work->jf->bgFrame < 0) {
                        work->jf->bgFrame = 7;
                    }
                }

                BosJfMajinSetBgFrame(work->jf->bgFrame, 0xA0, work);
            }

            work->jf->bgFrameTimer++;
            jf->body.z -= 0x400;
            work->stepTimer++;

            if (work->stepTimer > 40) {
                work->stepTimer = 0;
                work->step++;
            }

            if (work->stepTimer == 22) {
                jf->body.flags &= ~BTLOBJ_FLAG_UNHITTABLE;
            }

            break;
        default:
            work->jf->stateStep = 0;
            work->jf->state = 0;
            break;
        }
    }
}

void BosJfMajinUpdateRockAttack(JfMajinWork* work) {
    JfWork* jf = work->jf;
    BtlObj* q = &jf->sub;

    if (jf->stateStep == 0) {
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            jf->bgFrame = 0;
            work->baseFrame = 14;
        } else {
            jf->bgFrame = 7;
            work->baseFrame = 34;
        }

        work->jf->bgFrameTimer = 0;
        BosJfMajinSetBgFrame(work->jf->bgFrame, 0xA0, work);
        work->step = 0;
        work->stepTimer = 0;
        work->spriteVisible = 0;
        work->jf->stateStep++;
    } else {
        switch (work->step) {
        case 0:
            if (work->jf->bgFrameTimer >= gBosJfMajinFrameDurations[work->jf->bgFrame]) {
                work->jf->bgFrameTimer = 0;

                if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                    work->jf->bgFrame++;

                    if (work->jf->bgFrame > 7) {
                        work->jf->bgFrame = 0;
                    }
                } else {
                    work->jf->bgFrame--;

                    if (work->jf->bgFrame < 0) {
                        work->jf->bgFrame = 7;
                    }
                }

                BosJfMajinSetBgFrame(work->jf->bgFrame, 0xA0, work);
            }

            work->jf->bgFrameTimer++;
            jf->body.z += 0x400;
            work->stepTimer++;

            if (work->stepTimer > 60) {
                work->stepTimer = 0;
                work->step++;
            }

            if (work->stepTimer == 23) {
                jf->body.flags |= BTLOBJ_FLAG_UNHITTABLE;
            }

            break;
        case 1:
            if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                work->jf->bgFrame = 14;
                work->z = -0x2000 - ((gBosJfRightPillarLevel + 1) << 11);
            } else {
                work->jf->bgFrame = 34;
                work->z = -0x2000 - ((gBosJfLeftPillarLevel + 1) << 11);
            }

            work->jf->bgFrameTimer = 0;
            work->task = TaskCreate(&work->tasks, &gTaskDescBosJfRock, work->jf);
            BosJfMajinSetBgFrame(work->jf->bgFrame, 0xA0, work);
            work->moveSteps = 120;
            work->step++;
            break;
        case 2:
            if (work->moveSteps > 0) {
                ApproachValue(&jf->body.z, work->z, work->moveSteps);
                work->moveSteps--;

                if (work->moveSteps == 30) {
                    jf->body.flags &= ~BTLOBJ_FLAG_UNHITTABLE;
                }
            } else {
                work->step++;
            }

            break;
        case 3:
            if (work->jf->bgFrameTimer >= gBosJfMajinFrameDurations[work->jf->bgFrame]) {
                work->jf->bgFrameTimer = 0;
                work->jf->bgFrame++;

                if (work->jf->bgFrame > work->baseFrame + 4) {
                    if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                        work->jf->bgFrame = 8;
                    } else {
                        work->jf->bgFrame = 28;
                    }

                    work->spriteVisible = 1;
                    work->step++;
                }

                BosJfMajinSetBgFrame(work->jf->bgFrame, 0xA0, work);
            }

            work->jf->bgFrameTimer++;
            break;
        case 4:
            if (IsTaskActive(work->task) == 0) {
                work->z = -0x3800;
                work->moveSteps = 10;
                work->step++;
            }

            break;
        case 5:
            if (work->moveSteps > 0) {
                ApproachValue(&jf->body.z, work->z, work->moveSteps);
                work->moveSteps--;
            } else {
                work->step++;
            }

            break;
        default:
            ClearBtlObjActionFlags(q);
            work->jf->stateStep = 0;
            work->jf->state = 6;
            break;
        }
    }
}

void BosJfMajinUpdateSlam(JfMajinWork* work) {
    JfWork* jf = work->jf;
    BtlObj* q = &jf->sub;

    if (jf->stateStep == 0) {
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            jf->bgFrame = 19;
            work->jf->bgFrameTimer = 0;
            work->baseFrame = 19;
            work->x = 0x27A00;
            work->z = -0x5200 - ((gBosJfRightPillarLevel + 1) << 11);
        } else {
            jf->bgFrame = 39;
            work->jf->bgFrameTimer = 0;
            work->baseFrame = 39;
            work->x = 0x19200;
            work->z = -0x5200 - ((gBosJfLeftPillarLevel + 1) << 11);
        }

        BosJfMajinSetBgFrame(work->jf->bgFrame, 0xA0, work);
        work->step = 0;
        work->stepTimer = 0;
        work->moveSteps = 40;
        work->spriteVisible = 0;
        work->jf->stateStep++;
    } else {
        switch (work->step) {
        case 0:
            if (work->moveSteps > 0) {
                ApproachValue(&jf->body.x, work->x, work->moveSteps);
                ApproachValue(&jf->body.z, work->z, work->moveSteps);
                work->moveSteps--;

                if (work->jf->bgFrameTimer >= gBosJfMajinFrameDurations[work->jf->bgFrame]) {
                    work->jf->bgFrameTimer = 0;
                    work->jf->bgFrame++;

                    if (work->jf->bgFrame >= work->baseFrame + 1) {
                        work->jf->bgFrame = work->baseFrame + 1;
                    }

                    BosJfMajinSetBgFrame(work->jf->bgFrame, 0xA0, work);
                }

                work->jf->bgFrameTimer++;
            } else {
                work->step++;
            }

            break;
        case 1:
            work->stepTimer++;

            if (work->stepTimer > 20) {
                work->stepTimer = 0;
                work->extraClipRows = 1;
                work->step++;
            }

            break;
        case 2:
            jf->body.z += 0xA00;

            if (work->jf->bgFrameTimer >= gBosJfMajinFrameDurations[work->jf->bgFrame]) {
                work->jf->bgFrameTimer = 0;
                work->jf->bgFrame++;

                if (work->jf->bgFrame == work->baseFrame + 4) {
                    work->extraClipRows = 0;
                    work->step++;
                }

                BosJfMajinSetBgFrame(work->jf->bgFrame, 0xA0, work);
            }

            work->jf->bgFrameTimer++;
            break;
        case 3:
            if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                BgFxStartGroundImpact(jf->body.x - 0x3000, jf->body.y + jf->body.z + 0x1800);
                ApplyAttackBox(0xE8, jf->body.x - 0x3000, jf->body.y, jf->body.z + 0x1800, 30, 30, 30);
            } else {
                BgFxStartGroundImpact(jf->body.x + 0x3000, jf->body.y + jf->body.z + 0x1800);
                ApplyAttackBox(0xE8, jf->body.x + 0x3000, jf->body.y, jf->body.z + 0x1800, 30, 30, 30);
            }

            BtlMapStartShake();
            m4aSongNumStart(SONG_BTL_LB_RUMB);
            work->stepTimer = 0;
            work->step++;
            break;
        case 4:
            if (work->stepTimer == 10) {
                work->jf->bgFrame = work->baseFrame + 5;
                BosJfMajinSetBgFrame(work->jf->bgFrame, 0xA0, work);
            }

            if (work->stepTimer > 20) {
                work->stepTimer = 0;

                if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                    work->x = 0x2A200;
                } else {
                    work->x = 0x16A00;
                }

                work->z = -0x3800;
                work->moveSteps = 10;
                work->step++;
            }

            work->stepTimer++;
            break;
        case 5:
            if (work->moveSteps > 0) {
                ApproachValue(&jf->body.x, work->x, work->moveSteps);
                ApproachValue(&jf->body.z, work->z, work->moveSteps);
                work->moveSteps--;
            } else {
                work->step++;
            }

            break;
        default:
            ClearBtlObjActionFlags(q);
            work->jf->stateStep = 0;
            work->jf->state = 6;
            break;
        }
    }
}

void BosJfMajinUpdateBeam(JfMajinWork* work) {
    JfWork* jf = work->jf;
    BtlObj* q = &jf->sub;

    if (jf->stateStep == 0) {
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            jf->bgFrame = 25;
            work->jf->bgFrameTimer = 0;
            work->baseFrame = 25;
            work->x = 0x2A200;
            work->z = -0x2400 - ((gBosJfRightPillarLevel + 1) << 11);
        } else {
            jf->bgFrame = 45;
            work->jf->bgFrameTimer = 0;
            work->baseFrame = 45;
            work->x = 0x16A00;
            work->z = -0x2400 - ((gBosJfLeftPillarLevel + 1) << 11);
        }

        BosJfMajinSetBgFrame(work->jf->bgFrame, 0x80, work);
        work->step = 0;
        work->stepTimer = 0;
        work->moveSteps = 40;
        work->spriteVisible = 0;
        work->jf->stateStep++;
    } else {
        switch (work->step) {
        case 0:
            if (work->moveSteps > 0) {
                ApproachValue(&jf->body.z, work->z, work->moveSteps);
                work->moveSteps--;
            } else {
                work->step++;
            }

            break;
        case 1:
            if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                jf->body.x += 0x100;
            } else {
                jf->body.x -= 0x100;
            }

            work->stepTimer++;

            if (work->stepTimer > 20) {
                work->stepTimer = 0;
                work->jf->bgFrame = work->baseFrame + 1;
                BosJfMajinSetBgFrame(work->jf->bgFrame, 0x80, work);
                work->moveSteps = 2;
                work->step++;
            }

            break;
        case 2:
            if (work->moveSteps > 0) {
                ApproachValue(&jf->body.x, work->x, work->moveSteps);
                work->moveSteps--;
            } else {
                work->step++;
                work->moveSteps = 0;
            }

            break;
        case 3:
            if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                BgFxStartJfMajinBeam(jf->body.x - 0x1A00, jf->body.y, jf->body.z - 0x3100, 0x133, 160, 45);
            } else {
                BgFxStartJfMajinBeam(jf->body.x + 0x1A00, jf->body.y, jf->body.z - 0x3100, 0x133, 96, 45);
            }

            m4aSongNumStart(SONG_EF_JF_BEEM);
            jf->body.x = (work->x - 0x100) + (work->moveSteps++ % 2) * 0x200;
            work->stepTimer = 0;
            work->step++;
            break;
        case 4:
            jf->body.x = (work->x - 0x100) + (work->moveSteps++ % 2) * 0x200;

            if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                BgFxSetPosition(jf->body.x - 0x1A00, jf->body.y, jf->body.z - 0x3100);
            } else {
                BgFxSetPosition(jf->body.x + 0x1A00, jf->body.y, jf->body.z - 0x3100);
            }

            if (work->stepTimer > 10 && work->stepTimer % 10 == 9) {
                if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                    ApplyAttackBox(0xE9, jf->body.x - 0x6400, jf->body.y + 0xA00, jf->body.z + 0x2000, 20, 20, 20);
                } else {
                    ApplyAttackBox(0xE9, jf->body.x + 0x6400, jf->body.y + 0xA00, jf->body.z + 0x2000, 20, 20, 20);
                }
            }

            if (work->stepTimer > 80) {
                work->stepTimer = 0;
                work->z = -0x3800;
                work->moveSteps = 10;
                work->jf->bgFrame = work->baseFrame + 2;
                BosJfMajinSetBgFrame(work->jf->bgFrame, 0x80, work);
                work->step++;
            }

            work->stepTimer++;
            break;
        case 5:
            if (work->moveSteps > 0) {
                ApproachValue(&jf->body.x, work->x, work->moveSteps);
                ApproachValue(&jf->body.z, work->z, work->moveSteps);
                work->moveSteps--;
            } else {
                work->step++;
            }

            break;
        default:
            ClearBtlObjActionFlags(q);
            work->jf->stateStep = 0;
            work->jf->state = 6;
            break;
        }
    }
}

void BosJfMajinUpdateSweepBeam(JfMajinWork* work) {
    JfWork* jf = work->jf;
    BtlObj* q = &jf->sub;

    if (jf->stateStep == 0) {
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            jf->bgFrame = 25;
            work->jf->bgFrameTimer = 0;
            work->baseFrame = 25;
            work->x = 0x2A200;
            work->y2 = gBtlWork->actor->y - 0x1400;
            work->z = -0x2400 - ((gBosJfRightPillarLevel + 1) << 11);
        } else {
            jf->bgFrame = 45;
            work->jf->bgFrameTimer = 0;
            work->baseFrame = 45;
            work->x = 0x16A00;
            work->y2 = gBtlWork->actor->y - 0x1400;
            work->z = -0x2400 - ((gBosJfLeftPillarLevel + 1) << 11);
        }

        BosJfMajinSetBgFrame(work->jf->bgFrame, 0x80, work);
        work->step = 0;
        work->stepTimer = 0;
        work->moveSteps = 40;
        work->spriteVisible = 0;
        work->jf->stateStep++;
    } else {
        switch (work->step) {
        case 0:
            BtlMapSetCameraTarget(jf->body.x, jf->body.y + jf->body.z);

            if (work->moveSteps > 0) {
                ApproachValue(&jf->body.y, work->y2, work->moveSteps);
                ApproachValue(&jf->body.z, work->z, work->moveSteps);
                work->moveSteps--;
            } else {
                work->step++;
            }

            break;
        case 1:
            if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                jf->body.x += 0x100;
            } else {
                jf->body.x -= 0x100;
            }

            work->stepTimer++;

            if (work->stepTimer > 20) {
                work->stepTimer = 0;
                work->jf->bgFrame = work->baseFrame + 1;
                BosJfMajinSetBgFrame(work->jf->bgFrame, 0x80, work);
                work->moveSteps = 2;
                work->step++;
            }

            break;
        case 2:
            if (work->moveSteps > 0) {
                ApproachValue(&jf->body.x, work->x, work->moveSteps);
                work->moveSteps--;
            } else {
                work->step++;
                work->moveSteps = 0;
            }

            break;
        case 3:
            if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                work->beamAngle = 148;
                work->beamScale = 0x100;
                BgFxStartJfMajinBeam(jf->body.x - 0x1A00, jf->body.y, jf->body.z - 0x3100, 0x100, work->beamAngle, 45);
                BgFxSetScale(0x133, 0x100);
            } else {
                work->beamAngle = 108;
                work->beamScale = 0x133;
                BgFxStartJfMajinBeam(jf->body.x + 0x1A00, jf->body.y, jf->body.z - 0x3100, 0x100, work->beamAngle, 45);
                BgFxSetScale(0x133, 0x100);
            }

            m4aSongNumStart(SONG_EF_JF_BEEM);
            jf->body.x = (work->x - 0x100) + (work->moveSteps++ % 2) * 0x200;
            work->stepTimer = 0;
            work->beamLength = 0;
            work->step++;
            break;
        case 4:
            work->moveSteps++;

            if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                jf->body.x = (work->x - 0x100) + (work->moveSteps % 2) * 0x200;
                BgFxSetPosition(jf->body.x - 0x1A00, jf->body.y, jf->body.z - 0x3100);

                if (work->beamAngle <= 173 && work->moveSteps % 2 == 0) {
                    work->beamAngle++;
                    BgFxSetAngle(work->beamAngle);
                    work->beamLength++;
                    work->beamScale = gBosJfMajinBeamScales[work->beamLength];
                    BgFxSetScale(0x133, work->beamScale);
                }
            } else {
                jf->body.x = (work->x - 0x100) + (work->moveSteps % 2) * 0x200;
                BgFxSetPosition(jf->body.x + 0x1A00, jf->body.y, jf->body.z - 0x3100);

                if (work->beamAngle > 82 && work->moveSteps % 2 == 0) {
                    work->beamAngle--;
                    BgFxSetAngle(work->beamAngle);
                    work->beamLength++;
                    work->beamScale = gBosJfMajinBeamScales[work->beamLength];
                    BgFxSetScale(0x133, work->beamScale);
                }
            }

            if (work->stepTimer >= 11 && work->stepTimer <= 50) {
                if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                    ApplyAttackBox(0xEA, jf->body.x - 0x3200 - work->beamLength * 3 * 512, jf->body.y + 0xA00, jf->body.z + 0x2C00, 20, 20, 20);
                } else {
                    ApplyAttackBox(0xEA, jf->body.x + 0x3200 + work->beamLength * 3 * 512, jf->body.y + 0xA00, jf->body.z + 0x2C00, 20, 20, 20);
                }
            }

            if (work->stepTimer > 80) {
                work->stepTimer = 0;
                work->y2 = 0x15E00;
                work->z = -0x3800;
                work->moveSteps = 10;
                work->jf->bgFrame = work->baseFrame + 2;
                BosJfMajinSetBgFrame(work->jf->bgFrame, 0x80, work);
                work->step++;
            } else {
                work->stepTimer++;
            }

            break;
        case 5:
            if (work->moveSteps > 0) {
                ApproachValue(&jf->body.x, work->x, work->moveSteps);
                ApproachValue(&jf->body.y, work->y2, work->moveSteps);
                ApproachValue(&jf->body.z, work->z, work->moveSteps);
                work->moveSteps--;
            } else {
                work->step++;
            }

            break;
        default:
            ClearBtlObjActionFlags(q);
            work->jf->stateStep = 0;
            work->jf->state = 6;
            break;
        }
    }
}

void func_080BFDD4(JfMajinWork* work) {
}

void BosJfMajinUpdateBreak(JfMajinWork* work) {
    JfWork* jf = work->jf;
    BtlObj* q = &jf->sub;

    if (jf->stateStep == 0) {
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            jf->body.x = 0x2A200;
            jf->bgFrame = 8;
        } else {
            jf->body.x = 0x16A00;
            jf->bgFrame = 28;
        }

        jf->body.y = 0x15E00;
        jf->body.z = -0x3800;
        work->jf->bgFrameTimer = 0;
        BosJfMajinSetBgFrame(work->jf->bgFrame, 0x80, work);
        work->idleStep = 0;
        work->spriteVisible = 1;
        work->extraClipRows = 0;
        jf->body.flags &= ~BTLOBJ_FLAG_UNHITTABLE;
        CreateBtlPopTask(&jf->body, 9);
        work->jf->stateStep++;
    } else if (jf->stateStep > 60) {
        ClearBtlObjActionFlags(q);
        work->jf->stateStep = 0;

        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            work->jf->bgFrame = 8;
        } else {
            work->jf->bgFrame = 28;
        }

        work->jf->bgFrameTimer = 0;
        work->jf->state = 6;
    } else {
        work->jf->stateStep++;
    }
}

void BosJfMajinUpdateGimmick(JfMajinWork* work) {
    JfWork* jf = work->jf;
    BtlObj* q = &jf->sub;

    if (jf->stateStep == 0) {
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            jf->body.x = 0x2A200;
            jf->bgFrame = 8;
        } else {
            jf->body.x = 0x16A00;
            jf->bgFrame = 28;
        }

        jf->body.y = 0x15E00;
        jf->body.z = -0x3800;
        work->jf->bgFrameTimer = 0;
        BosJfMajinSetBgFrame(work->jf->bgFrame, 0x80, work);
        work->idleStep = 0;
        work->spriteVisible = 1;
        work->extraClipRows = 0;
        jf->body.flags &= ~BTLOBJ_FLAG_UNHITTABLE;
        work->jf->stateStep++;
    } else {
        ClearBtlObjActionFlags(q);
        work->jf->stateStep = 0;

        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            work->jf->bgFrame = 8;
        } else {
            work->jf->bgFrame = 28;
        }

        work->jf->bgFrameTimer = 0;
        work->jf->state = 6;
    }
}

void BosJfMajinUpdateDefeat(JfMajinWork* work) {
    JfWork* jf = work->jf;
    BtlObj* q = &jf->sub;
    PrizeCardArg fx;
    s32 v;

    if (jf->stateStep == 0) {
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            jf->bgFrame = 8;
            v = 0x2A200;
        } else {
            jf->bgFrame = 28;
            v = 0x16A00;
        }

        jf->body.x = v;

        jf->body.y = 0x15E00;
        jf->body.z = -0x3800;
        BosJfMajinSetBgFrame(work->jf->bgFrame, 0x80, work);
        work->spriteVisible = 1;
        BtlMapSetCameraTarget(jf->body.x, jf->body.y + jf->body.z);
        BeginBossDefeat(&jf->body);
        work->step = 0;
        work->moveSteps = 0;
        work->jf->stateStep++;
        return;
    }

    switch (work->step) {
    case 0:
        BtlMapSetCameraTarget(jf->body.x, jf->body.y + jf->body.z);

        if (work->moveSteps > 1) {
            work->moveSteps = 0;
            work->step++;
        } else {
            work->moveSteps++;
        }

        break;
    case 1:
        BtlMapSetCameraTarget(jf->body.x, jf->body.y + jf->body.z);

        if (FadeIsActive() != 0) {
            break;
        }

        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            BgFxStartBossDeath(jf->body.x - 0x800, jf->body.y + jf->body.z - 0x800);
        } else {
            BgFxStartBossDeath(jf->body.x + 0x800, jf->body.y + jf->body.z - 0x800);
        }

        FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
        work->step++;
        break;
    case 2:
        BtlMapSetCameraTarget(jf->body.x, jf->body.y + jf->body.z);

        if (work->moveSteps <= 119) {
            work->moveSteps++;
        } else {
            BgFxStartBossDeathFlash();
            work->step++;
        }

        break;
    case 3:
        if (BgFxIsActive() == 0) {
            if (q->x < 0x1B200) {
                q->x = 0x1BA00;
            }

            if (q->x > 0x25A00) {
                q->x = 0x25200;
            }

            fx.x = q->x;
            fx.y = q->y;
            fx.z = -0x7800;
            CreateBossPrizeCardTask(&gBtlWork->taskPools[0], &fx);
#ifdef VERSION_EU
            DropBossPrizes(q);
#else
            DropBossPrizes(&jf->body);
#endif
            gBosJfLeftPillarLevel = 0;
            gBosJfMiddlePillarLevel = 0;
            gBosJfRightPillarLevel = 0;
            BosJfDrawPillars();
            jf->body.x = 0;
            jf->body.y = 0;
            jf->body.z = 0;
            ScrollBgMapTo(1, (gBtlWork->viewX >> 8) + 776, (gBtlWork->viewY >> 8) + 294);
            work->step++;
        } else {
            BtlMapSetCameraTarget(jf->body.x, jf->body.y + jf->body.z);
        }

        break;
    default:
        EndBossDefeat();
        work->jf->flags |= JF_FLAG_DEFEAT_DONE;
        break;
    }
}

u8 BosJfStepPillarLevel(u16* p, s16 b, u8 c, u8 d) {
    if ((s16)*p == b) {
        return 1;
    }

    if ((s16)*p > b) {
        *p = *p - 1;
    } else {
        BtlObj* q;
        s32 v;

        *p = *p + 1;

        if (c == d) {
            q = gBtlWork->actor;
            v = -(((s16)*p + 1) << 11);

            if (q->z >= v) {
                q->z = v;
            }
        }
    }

    return 0;
}

void BosJfMajinUpdatePillars(JfMajinWork* work) {
    JfWork* jf = work->jf;
    BtlObj* s = &work->jf->sub;
    s16 n = 0;
    s16 m;
    u8 v;

    if (jf->gimmickTimer > 0) {
        jf->stateStep = 0;
        work->jf->state = 0;
        return;
    }

    switch (jf->stateStep) {
    case 0:
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            jf->bgFrame = 8;
            work->baseFrame = 8;
        } else {
            jf->bgFrame = 28;
            work->baseFrame = 28;
        }

        work->jf->bgFrameTimer = 0;
        BosJfMajinSetBgFrame(work->jf->bgFrame, 0x80, work);
        work->idleStep = 0;
        work->spriteVisible = 1;

        if (work->jf->flags & JF_FLAG_GIMMICK_PENDING) {
            work->jf->flags &= ~JF_FLAG_GIMMICK_PENDING;
            work->jf->pillarPhase = 2;
            m = 14;
        } else if (s->hp < s->maxHp / 2) {
            switch (work->jf->pillarPhase) {
            case 0:
                m = GetRandom() & 1;
                break;
            case 1:
            case 2:
                m = GetRandom() % 6 + 2;
                break;
            case 3:
                m = GetRandom() % 6 + 8;
                break;
            default:
                m = 0;
                break;
            }
        } else if (work->jf->pillarPhase == 0) {
            m = GetRandom() % 6 + 8;
        } else {
            m = GetRandom() % 8;
        }

        work->leftLevel = gBosJfLeftPillarLevel;
        work->middleLevel = gBosJfMiddlePillarLevel;
        work->rightLevel = gBosJfRightPillarLevel;
        work->leftTarget = gBosJfPillarPatterns[m][0];
        work->middleTarget = gBosJfPillarPatterns[m][1];
        work->rightTarget = gBosJfPillarPatterns[m][2];
        work->step = 0;
        work->stepTimer = 0;
        work->moveSteps = 0;
        BosJfStartShake(60);
        work->jf->stateStep++;
        break;
    case 1:
        work->stepTimer++;

        if (work->stepTimer > 80) {
            work->stepTimer = 0;
            m4aSongNumStart(SONG_BTL_IRON_GIMICBREAK);
            work->jf->stateStep++;
        }

        break;
    default:
        work->stepTimer++;

        if (work->stepTimer <= 1) {
            return;
        }

        work->stepTimer = 0;
        v = BosJfGetActorPillar();
        n += (s8)BosJfStepPillarLevel(&work->leftLevel, work->leftTarget, v, 0);
        n += (s8)BosJfStepPillarLevel(&work->middleLevel, work->middleTarget, v, 1);
        n += (s8)BosJfStepPillarLevel(&work->rightLevel, work->rightTarget, v, 2);

        if (n == 3) {
            if (s->hp < s->maxHp / 2) {
                switch (work->jf->pillarPhase) {
                case 0:
                    work->jf->pillarPhase = 3;
                    break;
                case 1:
                    work->jf->pillarPhase = 0;
                    break;
                case 2:
                    work->jf->pillarPhase = 0;
                    work->jf->gimmickTimer = 300;
                    break;
                case 3:
                    work->jf->pillarPhase = 1;
                    break;
                }
            } else {
                switch (work->jf->pillarPhase) {
                case 0:
                    work->jf->pillarPhase = 1;
                    break;
                case 1:
                    work->jf->pillarPhase = 0;
                    break;
                case 2:
                    work->jf->pillarPhase = 0;
                    work->jf->gimmickTimer = 300;
                    break;
                }
            }

            work->jf->stateStep = 0;
            work->jf->state = 0;
        } else {
            gBosJfLeftPillarLevel = work->leftLevel;
            gBosJfMiddlePillarLevel = work->middleLevel;
            gBosJfRightPillarLevel = work->rightLevel;
            BosJfDrawPillars();
        }

        break;
    }
}

void BosJfMajinUpdateEventIdle(JfMajinWork* work) {
    if (work->jf->stateStep == 0) {
        work->jf->bgFrame = 8;
        work->baseFrame = 8;
        work->jf->bgFrameTimer = 0;
        BosJfMajinSetBgFrame(work->jf->bgFrame, 0x80, work);
        work->idleStep = 0;
        work->spriteVisible = 1;
        work->jf->stateStep++;
    } else {
        if (work->jf->bgFrameTimer >= gBosJfMajinFrameDurations[work->jf->bgFrame]) {
            work->jf->bgFrameTimer = 0;
            work->jf->bgFrame++;
            work->idleStep++;

            if (work->jf->bgFrame > work->baseFrame + 5) {
                work->jf->bgFrame = work->baseFrame;
                work->idleStep = 0;
            }

            BosJfMajinSetBgFrame(work->jf->bgFrame, 0x80, work);
        }

        work->jf->bgFrameTimer++;
        work->gfx = AnimUpdate(&work->anim);
        work->y = gBosJfMajinIdleOffsets[work->idleStep];
    }
}

void BosJfMajinChooseAttack(JfMajinWork* work) {
    BtlObj* s = &work->jf->sub;
    u8 v;
    s32 r;

    if (s->hp < s->maxHp / 2) {
        if (GetRandom() % 100 <= 9) {
            RequestBossCardValue(1);
        } else if (GetRandom() % 90 <= 19) {
            RequestBossCardValue(GetRandom() % 2 + 7);
        } else {
            RequestBossCardValue(GetRandom() % 4 + 3);
        }

        if (gBosJfLeftPillarLevel == gBosJfMiddlePillarLevel && gBosJfLeftPillarLevel == gBosJfRightPillarLevel && GetRandom() % 100 <= 79) {
            RequestEnemyCardUse(s);
            work->jf->attackState = 5;
        } else {
            v = BosJfMajinGetActorPillarDistance(work);

            switch (v) {
            case 0:
                RequestEnemyCardUse(s);
                r = (s16)(GetRandom() % 100);

                if (r <= 39) {
                    RequestEnemyCardUse(s);
                    work->jf->attackState = 3;
                } else if (r <= 79) {
                    RequestEnemyCardUse(s);
                    work->jf->attackState = 4;
                } else {
                    RequestEnemyCardUse(s);
                    work->jf->attackState = 2;
                }

                break;
            case 1:
                RequestEnemyCardUse(s);
                work->jf->attackState = 2;
                break;
            case 2:
                if (GetRandom() % 100 <= 49) {
                    work->jf->state = 1;
                } else {
                    RequestEnemyCardUse(s);
                    work->jf->attackState = 2;
                }

                break;
            }
        }
    } else {
        if (GetRandom() % 100 <= 29) {
            RequestBossCardValue(GetRandom() % 3 + 6);
        } else {
            RequestBossCardValue(GetRandom() % 6 + 1);
        }

        if (gBosJfLeftPillarLevel == gBosJfMiddlePillarLevel && gBosJfLeftPillarLevel == gBosJfRightPillarLevel && GetRandom() % 100 <= 19) {
            RequestEnemyCardUse(s);
            work->jf->attackState = 5;
        } else {
            v = BosJfMajinGetActorPillarDistance(work);

            switch (v) {
            case 0:
                RequestEnemyCardUse(s);

                if (GetRandom() % 100 <= 59) {
                    RequestEnemyCardUse(s);
                    work->jf->attackState = 3;
                } else {
                    RequestEnemyCardUse(s);
                    work->jf->attackState = 4;
                }

                break;
            case 1:
                if (GetRandom() % 100 <= 79) {
                    RequestEnemyCardUse(s);
                    work->jf->attackState = 2;
                } else {
                    RequestEnemyCardUse(s);
                    work->jf->attackState = 4;
                }

                break;
            case 2:
                if (GetRandom() % 100 <= 69) {
                    work->jf->state = 1;
                } else {
                    RequestEnemyCardUse(s);
                    work->jf->attackState = 2;
                }

                break;
            }
        }
    }
}

void task_bos_jf_rock_0(JfRockWork* work, JfWork* arg) {
    work->jf = arg;
    work->body.x = arg->body.x;
    work->body.y = arg->body.y + 0x500;
    work->body.z = arg->body.z - 0x4800;
    work->body.groundZ = 0;
    work->body.shadowPriority = 0xFE00;
    work->body.flags = BTLOBJ_FLAG_LARGE_SHADOW;
    work->targetX = 0;
    work->targetY = 0;
    work->targetZ = 0;
    work->vx = 0;
    work->vy = 0;
    work->vz = 0;
    work->accelZ = 0;
    work->paletteFrame = 0;
    work->paletteTimer = 0;
    work->shadowVisible = 0;

    if (arg->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
        work->x2 = arg->body.x + 0x2000;
        work->y2 = arg->body.y + 0xA00;
        work->z2 = arg->body.z - 0x1900;
        work->targetZ = -((gBosJfRightPillarLevel + 1) << 11) - 0x2000;
    } else {
        work->x2 = arg->body.x - 0x2000;
        work->y2 = arg->body.y + 0xA00;
        work->z2 = arg->body.z - 0x1900;
        work->targetZ = -0x2000 - ((gBosJfLeftPillarLevel + 1) << 11);
    }

    work->visible2 = 0;
    work->gfx2Index = 0;
    work->visible = 0;
    work->animIndex = 0;
    work->riseSteps = 120;
    work->throwTimer = 0;
    work->state = 0;
    work->tiles = LoadObjTiles(gUnk_09682AA4, 0x2800);
    work->palette = LoadObjPalette(gUnk_096FB5A4, 0x60);
    AnimInit(&work->anim, gUnk_09EF3B40, gUnk_09EF3A48);
    AnimStart(&work->anim, gBosJfRockAnims[work->animIndex], 0);
    work->gfx = AnimGetGfx(&work->anim);
    work->tiles2 = LoadObjTiles(gUnk_09682AA4, 0x2800);
    work->palette2 = LoadObjPalette(gUnk_096FB5A4, 0x60);
    work->gfx2 = gUnk_09EF3A48[gBosJfRockGfx2Frames[work->gfx2Index]];
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBosJfShadow, &work->body);
}

u8 task_bos_jf_rock_1(JfRockWork* work) {
    JfWork* jf = work->jf;
    BtlObj* b;
    s16 n;

    switch (work->state) {
    case 0:
        if (work->riseSteps > 40) {
            BtlMapSetCameraTarget(work->body.x, work->body.y + work->body.z - 0x2000);
        }

        work->paletteTimer++;

        if (work->paletteTimer > 2) {
            work->paletteTimer = 0;
            work->paletteFrame++;

            if (work->paletteFrame > 8) {
                work->paletteFrame = 0;
            }

            LoadObjPaletteBank(work->palette->index + 2, gUnk_096FB604 + (work->paletteFrame << 5));
        }

        if (work->riseSteps > 0) {
            ApproachValue(&work->body.z, work->targetZ - 0x4800, work->riseSteps);
            ApproachValue(&work->z2, work->targetZ - 0x1C00, work->riseSteps);
            work->riseSteps--;

            if (work->body.z <= -0xC00) {
                work->animIndex = 8;
                work->visible = 1;
            } else {
                n = 8 - ((work->body.z >> 8) + 12) / 8;

                if (n < 0) {
                    work->animIndex = 0;
                    work->visible = 0;
                } else {
                    work->animIndex = n;
                    work->visible = 1;
                }
            }

            AnimStart(&work->anim, gBosJfRockAnims[work->animIndex], 0);
            work->gfx = AnimGetGfx(&work->anim);

            if (work->z2 <= -0x1000) {
                work->gfx2Index = 11;
                work->visible2 = 1;
            } else {
                n = 11 - ((work->z2 >> 8) + 16) / 8;

                if (n < 0) {
                    work->gfx2Index = 0;
                    work->visible2 = 0;
                } else {
                    work->gfx2Index = n;
                    work->visible2 = 1;
                }
            }

            work->gfx2 = gUnk_09EF3A48[gBosJfRockGfx2Frames[work->gfx2Index]];
        } else {
            work->targetX = (b = gBtlWork->actor)->x;
            work->targetY = b->y;
            work->targetZ = b->z;
            work->vx = (work->targetX - work->body.x) / 40;
            work->vy = (work->targetY - work->body.y) / 40;
            work->vz = 0;
            work->accelZ = (work->targetZ - work->body.z) / 820;
            work->state++;
        }

        if (work->jf->state == 7 || work->jf->state == 11) {
            m4aSongNumStart(SONG_EF_FIRE01);
            work->visible2 = 0;
            work->riseSteps = 0;
            work->state = 5;
        }

        break;
    case 1:
        work->paletteTimer++;

        if (work->paletteTimer > 2) {
            work->paletteTimer = 0;
            work->paletteFrame++;

            if (work->paletteFrame > 8) {
                work->paletteFrame = 0;
            }

            LoadObjPaletteBank(work->palette->index + 2, gUnk_096FB604 + (work->paletteFrame << 5));
        }

        work->throwTimer++;

        if (work->throwTimer > 3) {
            work->throwTimer = 0;

            if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
                work->x2 = jf->body.x + 0x1000;
                work->y2 = jf->body.y + 0xA00;
                work->z2 = jf->body.z - 0x1000;
            } else {
                work->x2 = jf->body.x - 0x1000;
                work->y2 = jf->body.y + 0xA00;
                work->z2 = jf->body.z - 0x1000;
            }

            work->gfx2 = gUnk_09EF3A48[15];
            m4aSongNumStart(SONG_BTL_JF_BALLTHR);
            work->shadowVisible = 1;
            work->state++;
        }

        if (work->jf->state == 7 || work->jf->state == 11) {
            m4aSongNumStart(SONG_EF_FIRE01);
            work->visible2 = 0;
            work->shadowVisible = 0;
            work->riseSteps = 0;
            work->state = 5;
        }

        break;
    case 2:
        work->paletteTimer++;

        if (work->paletteTimer > 2) {
            work->paletteTimer = 0;
            work->paletteFrame++;

            if (work->paletteFrame > 8) {
                work->paletteFrame = 0;
            }

            LoadObjPaletteBank(work->palette->index + 2, gUnk_096FB604 + (work->paletteFrame << 5));
        }

        work->body.x += work->vx;
        work->body.y += work->vy;
        work->body.z += work->vz;
        work->vz += work->accelZ;

        if (work->throwTimer == 7) {
            work->visible2 = 0;
        }

        if (ApplyAttackBox(231, work->body.x, work->body.y, work->body.z - 0x2000, 28, 28, 28) == 1) {
            m4aSongNumStart(SONG_EF_JF_BALLHIT);
            BgFxStartExplosion(work->body.x - 0x800, work->body.y + work->body.z - 0x2400, 0);
            work->shadowVisible = 0;
            work->state = 3;
        }

        if (work->jf->state == 7 || work->jf->state == 11) {
            m4aSongNumStart(SONG_EF_FIRE01);
            work->visible2 = 0;
            work->shadowVisible = 0;
            work->riseSteps = 0;
            work->state = 5;
        }

        switch ((s8)BosJfRockTestPillars(work->body.x, work->body.y, work->body.z - 0x2000)) {
        case 1:
            m4aSongNumStart(SONG_EF_FIRE01);
            BgFxStartExplosion(work->body.x - 0x800, work->body.y + work->body.z - 0x2400, 0);
            work->shadowVisible = 0;
            work->state = 3;
            break;
        case 2:
            work->shadowVisible = 0;
            work->state = 4;
            break;
        }

        work->throwTimer++;
        break;
    case 5:
        if (MosaicIsActive() == 0) {
            if (work->riseSteps == 0) {
                BgFxStartExplosion(work->body.x - 0x800, work->body.y + work->body.z - 0x2400, 0);
                work->riseSteps++;
            } else {
                if (AnimIsFinished(&work->anim)) {
                    return 0;
                }

                work->gfx = AnimUpdate(&work->anim);
            }
        }

        break;
    case 3:
        if (AnimIsFinished(&work->anim)) {
            return 0;
        }

        work->gfx = AnimUpdate(&work->anim);
        break;
    default:
        return 0;
    }

    BosJfGetGroundZ(&work->body.x, &work->body.y, &work->body.z, &work->body.groundZ);
    TaskPoolUpdate(&work->tasks);

    return 1;
}

void task_bos_jf_rock_2(JfRockWork* work) {
    JfWork* jf = work->jf;
    u16 pal;
    s32 prio;
    s16 x;
    s16 y;

    if (work->visible == 1) {
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            if (work->body.x <= 0x259FF) {
                pal = GetBattleSpritePriorityFlags(work->body.y);
                prio = 0xFD00;
            } else {
                pal = 0x400;
                prio = 0xFFF5;
            }
        } else if (work->body.x > 0x1B200) {
            pal = GetBattleSpritePriorityFlags(work->body.y);
            prio = 0xFD00;
        } else {
            pal = 0x400;
            prio = 0xFFF5;
        }

        WorldToScreen(&x, &y, work->body.x, work->body.y, work->body.z);
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, pal, prio);
    }

    if (work->visible2 == 1) {
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            pal = 0x400;
        } else {
            pal = 0x400;
            pal |= 1;
        }

        WorldToScreen(&x, &y, work->x2, work->y2, work->z2);
        DrawSprite(x, y, work->gfx2, work->tiles2, work->palette2, NULL, pal, 0xFFF2);
    }

    if (work->shadowVisible == 1) {
        TaskPoolDraw(&work->tasks);
    }
}

void task_bos_jf_rock_3(JfRockWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette2);
    TaskPoolDestroy(&work->tasks);
}

u8 BosJfRockTestPillars(s32 a, s32 b, s32 c) {
    s32 t0 = -((gBosJfLeftPillarLevel + 1) << 11);
    s32 t1 = -((gBosJfMiddlePillarLevel + 1) << 11);
    s32 t2 = -((gBosJfRightPillarLevel + 1) << 11);
    s32 hi = a + 0x1C00;
    s32 lo = a - 0x1C00;
    s32 zh = c + 0x1C00;
    s32 zl = c - 0x1C00;

    if (zh >= t0 && hi > 0x1B200 && lo < 0x1EA00) {
        return 1;
    }

    if (zh >= t1 && hi > 0x1EA00 && lo < 0x22200) {
        return 1;
    }

    if (zh >= t2 && hi > 0x22200 && lo < 0x25A00) {
        return 1;
    }

    if (zl > 0 || lo > 0x2CA00 || hi < 0x14200) {
        return 2;
    }

    return 0;
}

void task_bos_jf_borderline_0(JfBorderlineWork* work, JfWork* arg) {
    work->jf = arg;
    BosJfBorderlineUpdateLayout(work);
    work->offsetY = 0xA00;
    work->offsetZ = 0x3600;
    work->x = arg->body.x + work->offsetX;
    work->y = arg->body.y + work->offsetY;
    work->z = arg->body.z + work->offsetZ;
    work->unk_0B0 = 0;
    work->unk_0B2 = 0;
    work->unk_0B4 = 0;
    work->wide = 0;
    work->tiles = LoadObjTiles(gUnk_09682AA4, 0x2800);
    work->palette = LoadObjPalette(gUnk_096FB5A4, 0x60);
    AnimInit(&work->anim, gUnk_09EF3B40, gUnk_09EF3A48);
    AnimStart(&work->anim, 27, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    AnimInit(&work->anim2, gUnk_09EF3B40, gUnk_09EF3A48);
    AnimStart(&work->anim2, 8, ANIM_FLAG_LOOP);
    work->gfx2 = AnimGetGfx(&work->anim2);
    AnimInit(&work->anim3, gUnk_09EF3B40, gUnk_09EF3A48);
    AnimStart(&work->anim3, 7, ANIM_FLAG_LOOP);
    work->gfx3 = AnimGetGfx(&work->anim3);
    AnimInit(&work->anim4, gUnk_09EF3B40, gUnk_09EF3A48);
    AnimStart(&work->anim4, 28, ANIM_FLAG_LOOP);
    work->gfx4 = AnimGetGfx(&work->anim4);
    AnimInit(&work->anim5, gUnk_09EF3B40, gUnk_09EF3A48);
    AnimStart(&work->anim5, 6, ANIM_FLAG_LOOP);
    work->gfx5 = AnimGetGfx(&work->anim5);
    SetBtlPaletteFadeExcluded(work->palette->index + 16, 0);
}

u8 task_bos_jf_borderline_1(JfBorderlineWork* work) {
    JfWork* p = work->jf;

    BosJfBorderlineUpdateLayout(work);
    work->x = p->body.x + work->offsetX;
    work->y = p->body.y + work->offsetY;
    work->gfx = AnimUpdate(&work->anim);
    work->gfx2 = AnimUpdate(&work->anim2);
    work->gfx3 = AnimUpdate(&work->anim3);
    work->gfx4 = AnimUpdate(&work->anim4);
    work->gfx5 = AnimUpdate(&work->anim5);

    return 1;
}

void task_bos_jf_borderline_2(JfBorderlineWork* work) {
    s16 sx;
    s16 sy;

    WorldToScreen(&sx, &sy, work->x, work->y, work->z);

    switch (work->wide) {
    case 0:
        DrawSprite(sx - 16, sy - 1, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        DrawSprite(sx - 16, sy - 1, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        DrawSprite(sx, sy + 1, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        DrawSprite(sx + 16, sy - 1, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        DrawSprite(sx + 16, sy - 1, work->gfx2, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        DrawSprite(sx - 8, sy + 4, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        DrawSprite(sx - 8, sy + 4, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFF60);
        DrawSprite(sx + 8, sy + 4, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFF60);
        DrawSprite(sx + 8, sy + 4, work->gfx2, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        break;
    case 1:
        DrawSprite(sx - 40, sy - 1, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        DrawSprite(sx - 40, sy - 1, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        DrawSprite(sx - 24, sy + 1, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        DrawSprite(sx - 8, sy + 2, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        DrawSprite(sx + 8, sy + 2, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        DrawSprite(sx + 24, sy + 1, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        DrawSprite(sx + 40, sy - 1, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        DrawSprite(sx + 40, sy - 1, work->gfx2, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        DrawSprite(sx - 32, sy + 4, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        DrawSprite(sx - 32, sy + 4, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFF60);
        DrawSprite(sx - 16, sy + 6, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFF60);
        DrawSprite(sx, sy + 7, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFF60);
        DrawSprite(sx + 16, sy + 6, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFF60);
        DrawSprite(sx + 32, sy + 4, work->gfx3, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFF60);
        DrawSprite(sx + 32, sy - 4, work->gfx2, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1),
            0xFFF0);
        break;
    }

    DrawSprite(sx, sy - 8, work->gfx5, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1), 0xFF00);
}

void task_bos_jf_borderline_3(JfBorderlineWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void BosJfBorderlineUpdateLayout(JfBorderlineWork* work) {
    JfWork* jf = work->jf;

    switch (jf->state) {
    case 0:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            work->offsetX = -0x500;
        } else {
            work->offsetX = 0x500;
        }

        break;
    case 3:
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            work->offsetX = -0x100;
        } else {
            work->offsetX = 0x100;
        }

        break;
    case 4:
    case 5:
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            work->offsetX = 0x1000;
        } else {
            work->offsetX = -0x1000;
        }

        break;
    case 1:
    case 2:
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            work->offsetX = -0xA00;
        } else {
            work->offsetX = 0xA00;
        }

        work->wide = 1;
        return;
    default:
        if (jf->body.flags & BTLOBJ_FLAG_FACING_LEFT) {
            work->offsetX = -0x500;
        } else {
            work->offsetX = 0x500;
        }

        break;
    }

    work->wide = 0;
}

void task_bos_dsd_0(DsdWork* work, void* arg) {
    s32 v;
    DsdWork* w;
    BtlObj* p1;
    BtlObj* p2;
    BtlWork* btl;

    work->flags = 0;

    if (arg != NULL) {
        work->flags = DSD_FLAG_IN_EVENT;
    }

    TaskPoolInit(&work->tasks, 4);

    if (work->flags & DSD_FLAG_IN_EVENT) {
        TaskCreate(&work->tasks, &gTaskDescBosDsdMap, NULL);
    } else {
        TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosDsdMap, work);
    }

    work->unk_390 = 0;
    work->unk_392 = 0;

    if (work->flags & DSD_FLAG_IN_EVENT) {
        work->state = 9;
    } else {
        work->state = 1;
    }

    work->attackState = 1;
    work->lastState = 1;
    work->attackCycle = 0;
    work->unk_34C = 0;
    work->timer = 0;
    work->stateStep = 0;
    work->unk_352 = 0;
    work->bgFrame = 0;
    work->bgFrameTimer = 0;
    work->hpPhase = 0;
    work->driftX = -51;
    v = (s16)(work->flags & DSD_FLAG_IN_EVENT);

    if (v != 0) {
        work->bodyX = 0xDC00;
        work->bodyY = 0x16800;
        work->bodyZ = -0x6400;
        w = work;
        InitEnemyBtlObj(&w->body[0], &gBosDsdEmyKind, work->bodyX, work->bodyY, work->bodyZ);
        p1 = &w->body[1];
        InitEnemyBtlObj(p1, &gBosDsdEmyKind, 0xDC00, 0x16800, -0x8C00);
        p2 = &w->body[2];
        InitEnemyBtlObj(p2, &gBosDsdEmyKind, 0x9000, 0x16800, 0);
        TaskCreate(&w->tasks, &gTaskDescBosDsdMain, w);
    } else {
        work->bodyX = 0xDC00;
        work->bodyY = 0x16800;
        work->bodyZ = -0x6400;
        w = work;
        InitEnemyBtlObj(&w->body[0], &gBosDsdEmyKind, work->bodyX, work->bodyY, work->bodyZ);
        w->body[0].flags |= BTLOBJ_FLAG_UNHITTABLE;
        w->body[0].flags |= BTLOBJ_FLAG_FACING_LEFT;
        p1 = &w->body[1];
        InitEnemyBtlObj(p1, &gBosDsdEmyKind, 0xDC00, 0x16800, -0x8C00);
        p1->flags |= BTLOBJ_FLAG_FACING_LEFT;
        p1->flags |= 0x400;
        p1->centerHeight = v;
        p1->radiusX = 16;
        p1->radiusY = 16;
        p1->height = 16;
        p2 = &w->body[2];
        InitEnemyBtlObj(p2, &gBosDsdEmyKind, 0x9000, 0x16800, v);
        p2->flags |= (BTLOBJ_FLAG_FACING_LEFT | BTLOBJ_FLAG_UNHITTABLE | BTLOBJ_FLAG_RESIST_FIRE | BTLOBJ_FLAG_RESIST_BLIZZARD | BTLOBJ_FLAG_RESIST_THUNDER | BTLOBJ_FLAG_RESIST_PHYSICAL);
        p2->centerHeight = v;
        p2->radiusX = 16;
        p2->radiusY = 16;
        p2->height = 32;
        ColliderInit(&p2->collider, 7, 16, 32);
        ColliderSetPosition(&p2->collider, p2->x, p2->y, p2->z);
        ColliderSetDisabled(&p2->collider, 1);
        SetBtlObjParent(p2, p1);
        gBtlWork->bossPriorityOffset = v;
        SetBtlPaletteFadeExcluded(0, 1);
        SetBattleActorPosition(0x6400, 0x16800, 0);
        SetGimmickTarget(0x2800, 0x16800, 0);
        TaskCreate(&w->tasks, &gTaskDescBosDsdMain, w);
        btl = gBtlWork;
        btl->bossX = w->body[0].x;
        btl->bossY = w->body[0].y;
        btl->bossZ = w->body[0].z;
    }
}

u8 task_bos_dsd_1(DsdWork* work) {
    BtlWork* q;
    BtlObj* a = work->body;
    BtlObj* b = &work->body[1];

    if (work->flags & DSD_FLAG_IN_EVENT) {
        TaskPoolUpdate(&work->tasks);
        return 1;
    }

    switch (UpdateBtlObjReaction(b)) {
    case BTL_REACTION_CARD_ACTION:
        work->state = 2;
        b->flags |= BTLOBJ_FLAG_UNHITTABLE;
        work->stateStep = 0;
        break;
    case BTL_REACTION_HURT:
    case BTL_REACTION_STUNNED:
    case BTL_REACTION_GRAVITY:
        work->flags |= DSD_FLAG_HURT;
        work->timer = 20;
        break;
    case BTL_REACTION_DEFEATED:
    case BTL_REACTION_GRAVITY_DEFEATED:
        work->state = 11;
        work->stateStep = 0;
        break;
    case BTL_REACTION_CARD_BROKEN:
        work->state = 8;
        work->stateStep = 0;
        break;
    }

    if (work->flags & DSD_FLAG_HURT) {
        work->timer--;

        if ((s16)work->timer <= 0) {
            work->unk_34C = 0;
            work->flags &= ~DSD_FLAG_HURT;
            LoadPaletteWithEffect(gUnk_096FB744, (void*)PLTT, 32);
            ClearBtlObjActionFlags(b);

            if (b->hp > 0) {
                switch (work->state) {
                case 0:
                case 1:
                case 4:
                case 5:
                case 8:
                    break;
                default:
                    work->state = 0;
                    work->stateStep = 0;
                    break;
                }
            }
        }
    }

    if (ConsumeGimmickFlag(0)) {
        work->flags |= DSD_FLAG_PLATFORM_ACTIVE;
        TaskCreate(&work->tasks, &gTaskDescBosDsdIta, work);
    }

    if (work->state == 4) {
        if (gBtlWork->actor->z <= -0x1000) {
            gBtlWork->bossPriorityOffset = -30;
        } else {
            gBtlWork->bossPriorityOffset = 0;
        }
    } else {
        gBtlWork->bossPriorityOffset = 0;
    }

    TaskPoolUpdate(&work->tasks);
    q = gBtlWork;
    q->bossX = a->x;
    q->bossY = a->y;
    q->bossZ = a->z;

    if (work->flags & DSD_FLAG_DEFEAT_DONE) {
        return 0;
    }

    return 1;
}

void task_bos_dsd_2(DsdWork* work) {
    TaskPoolDraw(&work->tasks);
}

void task_bos_dsd_3(DsdWork* work) {
    BtlObj* a;
    BtlObj* b;

    a = &work->body[1];
    b = &work->body[2];
    TaskPoolDestroy(&work->tasks);
    ColliderUnregister(&work->body[2].collider);
    ReleaseEnemyBtlObj(&work->body[0]);
    ReleaseEnemyBtlObj(a);
    ReleaseEnemyBtlObj(b);
}

const s16 gBosJfMajinFrameDurations[49] = {
    9, 9, 8, 8, 8, 8, 8, 8, 30, 6, 6, 12, 6, 6, 2, 8,
    8, 8, 8, 12, 2, 2, 2, 2, 12, 12, 12, 12, 30, 6, 6, 12,
    6, 6, 2, 8, 8, 8, 8, 12, 2, 2, 2, 2, 12, 12, 12, 12,
    0,
};

const s8 gBosJfMajinIdleOffsets[6] = { 0, -1, -2, -2, -1, 0 };

const u16 gBosJfPillarPatterns[16][3] = {
    { 0, 0, 0 },
    { 7, 7, 7 },
    { 7, 0, 0 },
    { 0, 7, 0 },
    { 0, 0, 7 },
    { 7, 7, 0 },
    { 7, 0, 7 },
    { 0, 7, 7 },
    { 0, 7, 14 },
    { 0, 14, 7 },
    { 7, 0, 14 },
    { 7, 14, 0 },
    { 14, 0, 7 },
    { 14, 7, 0 },
    { 14, 14, 14 },
    { 0, 0, 0 },
};

void* gBosJfMajinFrameMaps[48] __attribute__((aligned(4))) = {
    gUnk_096D5C64,
    gUnk_096D6464,
    gUnk_096D6C64,
    gUnk_096D7464,
    gUnk_096D7C64,
    gUnk_096D8464,
    gUnk_096D8C64,
    gUnk_096D9464,
    gUnk_096CAC64,
    gUnk_096CB464,
    gUnk_096CBC64,
    gUnk_096CC464,
    gUnk_096CCC64,
    gUnk_096CD464,
    gUnk_096D0C64,
    gUnk_096D1464,
    gUnk_096D1C64,
    gUnk_096D2464,
    gUnk_096D2C64,
    gUnk_096D9C64,
    gUnk_096DA464,
    gUnk_096DAC64,
    gUnk_096DB464,
    gUnk_096DBC64,
    gUnk_096DC464,
    gUnk_096DFC64,
    gUnk_096E0464,
    gUnk_096E0C64,
    gUnk_096CDC64,
    gUnk_096CE464,
    gUnk_096CEC64,
    gUnk_096CF464,
    gUnk_096CFC64,
    gUnk_096D0464,
    gUnk_096D3464,
    gUnk_096D3C64,
    gUnk_096D4464,
    gUnk_096D4C64,
    gUnk_096D5464,
    gUnk_096DCC64,
    gUnk_096DD464,
    gUnk_096DDC64,
    gUnk_096DE464,
    gUnk_096DEC64,
    gUnk_096DF464,
    gUnk_096E1464,
    gUnk_096E1C64,
    gUnk_096E2464,
};

const u16* gUnk_09EF28CC __attribute__((aligned(4))) = gUnk_08125E24;

void* gBosJfMajinFrameTiles[48] __attribute__((aligned(4))) = {
    gUnk_09671DE4,
    gUnk_09672CE4,
    gUnk_09673964,
    gUnk_096748A4,
    gUnk_09675A24,
    gUnk_09676984,
    gUnk_09677604,
    gUnk_096784C4,
    gUnk_09665C04,
    gUnk_09668304,
    gUnk_09669164,
    gUnk_09669F64,
    gUnk_0966ADA4,
    gUnk_0966BB64,
    gUnk_0966C944,
    gUnk_0966DAC4,
    gUnk_0966EBA4,
    gUnk_0966FAE4,
    gUnk_09670C64,
    gUnk_09679584,
    gUnk_0967A764,
    gUnk_0967B924,
    gUnk_0967CA84,
    gUnk_0967DC04,
    gUnk_0967ED84,
    gUnk_0967FF04,
    gUnk_09680E24,
    gUnk_09681C64,
    gUnk_09665C04,
    gUnk_09668304,
    gUnk_09669164,
    gUnk_09669F64,
    gUnk_0966ADA4,
    gUnk_0966BB64,
    gUnk_0966C944,
    gUnk_0966DAC4,
    gUnk_0966EBA4,
    gUnk_0966FAE4,
    gUnk_09670C64,
    gUnk_09679584,
    gUnk_0967A764,
    gUnk_0967B924,
    gUnk_0967CA84,
    gUnk_0967DC04,
    gUnk_0967ED84,
    gUnk_0967FF04,
    gUnk_09680E24,
    gUnk_09681C64,
};

void* gUnk_09EF2990 __attribute__((aligned(4))) = NULL;

u32 gBosJfMajinBeamScales[27] __attribute__((aligned(4))) = { 256, 266, 276, 286, 296, 307, 317, 327, 337, 348, 358, 368, 378, 389, 399, 409, 419, 432, 445, 458, 471, 486, 501, 517, 532, 547, 563 };

u32 gUnk_09EF2A00 __attribute__((aligned(4))) = 578;

u32 gUnk_09EF2A04 __attribute__((aligned(4))) = 593;

u32 gUnk_09EF2A08 __attribute__((aligned(4))) = 609;

u32 gUnk_09EF2A0C __attribute__((aligned(4))) = 622;

u32 gUnk_09EF2A10 __attribute__((aligned(4))) = 637;

u32 gUnk_09EF2A14 __attribute__((aligned(4))) = 652;

u32 gUnk_09EF2A18 __attribute__((aligned(4))) = 668;

u32 gUnk_09EF2A1C __attribute__((aligned(4))) = 683;

TaskDesc gTaskDescBosJfMajin = {
    "task_bos_jf_majin",
    (TaskInitFunc)task_bos_jf_majin_0,
    (TaskUpdateFunc)task_bos_jf_majin_1,
    (TaskDrawFunc)task_bos_jf_majin_2,
    (TaskDestroyFunc)task_bos_jf_majin_3,
    sizeof(JfMajinWork),
};

s8 gBosJfRockAnims[9] __attribute__((aligned(1))) = { 9, 10, 11, 12, 13, 14, 15, 26, 0 };

s8 gUnk_09EF2A41 __attribute__((aligned(1))) = -1;

s16 gBosJfRockGfx2Frames[12] __attribute__((aligned(2))) = { 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 55 };

TaskDesc gTaskDescBosJfRock = {
    "task_bos_jf_rock",
    (TaskInitFunc)task_bos_jf_rock_0,
    (TaskUpdateFunc)task_bos_jf_rock_1,
    (TaskDrawFunc)task_bos_jf_rock_2,
    (TaskDestroyFunc)task_bos_jf_rock_3,
    sizeof(JfRockWork),
};

TaskDesc gTaskDescBosJfBorderline = {
    "task_bos_jf_borderline",
    (TaskInitFunc)task_bos_jf_borderline_0,
    (TaskUpdateFunc)task_bos_jf_borderline_1,
    (TaskDrawFunc)task_bos_jf_borderline_2,
    (TaskDestroyFunc)task_bos_jf_borderline_3,
    sizeof(JfBorderlineWork),
};

const EmyKind gBosDsdEmyKind = { 38, 1000, 16, 16, 40, 60, 0 };

TaskDesc gTaskDescBosDsd = {
    "task_bos_dsd",
    (TaskInitFunc)task_bos_dsd_0,
    (TaskUpdateFunc)task_bos_dsd_1,
    (TaskDrawFunc)task_bos_dsd_2,
    (TaskDestroyFunc)task_bos_dsd_3,
    sizeof(DsdWork),
};
