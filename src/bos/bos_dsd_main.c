/**
 * bos_dsd_main.c
 * Darkside Boss Body
 */

#include "bos2.h"
#include "boss_map_block_assets.h"
#include "sprites_bos2.h"
#include "sprites_btl.h"
#include "system_state.h"
#include "chara_types.h"
#include "btl_api.h"
#include "fade.h"
#include "songs.h"
#include "acgtrans.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "card_api.h"
#include "chara_api.h"
#include "display.h"
#include "engine_math.h"
#include "gba/defines.h"
#include "listpool.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "pallet.h"
#include "registration_data.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "default_bg_map.h"
#include "sprite_palettes.h"

extern const u16* gBosDsdFrameMaps[46][4];
extern void* gBosDsdFrameTiles[37];
extern const u16* gBosDsdMapBlocks[4];

void BosDsdSetBgMap(u8 index) {
    SetBgMapBlocks(1, gBosDsdFrameMaps[index], 2, 2);
}

void BosDsdSetBgFrame(u8 index, u16 a) {
    SetBgMapBlocks(1, gBosDsdFrameMaps[index], 2, 2);
    LoadBgTiles(1, gBosDsdFrameTiles[index], a * 32);
}

void task_bos_dsd_main_0(DsdMainWork* work, DsdWork* arg) {
    BtlObj* s = &work->body;

    work->dsd = arg;
    SetBgPriority(1, 1);
    SetBgPriority(0, 3);
    work->dsd->state = arg->state;
    work->unk_008 = 0;
    work->stepTimer = 0;
    work->moveSteps = 0;
    work->baseFrame = 0;
    work->spriteVisible = 1;
    work->energy2Task = NULL;
    work->lastBreakDifference = gBtlWork->breakDifference;
    SetBgMapBlocks(1, gBosDsdFrameMaps, 2, 2);
    work->tiles = LoadObjTiles(gUnk_096983E4, 0x12A0);
    AnimInit(&work->anim, gUnk_09EF3C34, gUnk_09EF3C20);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    arg->body[0].y++;
    arg->body[0].y--;
    work->tiles2 = LoadObjTiles(gUnk_096983E4, 0x12A0);
    AnimInit(&work->anim2, gUnk_09EF3C4C, gUnk_09EF3C38);
    AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
    work->gfx2 = AnimGetGfx(&work->anim2);
    work->palette = LoadObjPalette(gUnk_096FB8C4, 32);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    work->dsd->tiles = AllocObjTiles(0x800, gUnk_096A2F04);
    work->dsd->palette = LoadObjPalette(gUnk_096FB8E4, 32);
    work->dsd->tiles2 = LoadObjTiles(gUnk_096869A4, 0x740);
    work->dsd->palette2 = LoadObjPalette(gUnk_096FB864, 32);
    work->dsd->palette3 = LoadObjPalette(gUnk_096FB884, 32);
    work->dsd->tiles3 = LoadObjTiles(gUnk_08B22CE4, 0x200);
    work->dsd->palette4 = LoadObjPalette(gBStatesPalette, 32);
    s->x = 0xDC00;
    s->y = 0x16800;
    s->z = 0;
    ColliderInit(&s->collider, 8, 24, 100);
    ColliderSetPosition(&s->collider, s->x, s->y, s->z);
    ScrollBgMapTo(1, ((gBtlWork->viewX - arg->body[0].x) >> 8) + 100,
                  ((gBtlWork->viewY - (arg->body[0].y + arg->body[0].z)) >> 8) + 280);
    TaskPoolInit(&work->tasks, 10);
    BosDsdMainResetPose(work);
}

u8 task_bos_dsd_main_1(DsdMainWork* work) {
    DsdWork* d = work->dsd;
    BtlObj* p = &work->body;

    BosDsdMainUpdateDrift(work);

    switch (work->dsd->state) {
    case 0:
        work->dsd->lastState = work->dsd->state;
        BosDsdMainUpdateReturn(work);
        break;
    case 1:
        work->dsd->lastState = work->dsd->state;
        BosDsdMainUpdateIdle(work);
        break;
    case 2:
        work->dsd->lastState = work->dsd->state;
        BosDsdMainUpdateAttackStart(work);
        break;
    case 3:
        work->dsd->lastState = work->dsd->state;
        BosDsdMainUpdateApproach(work);
        break;
    case 4:
        work->dsd->lastState = work->dsd->state;
        BosDsdMainUpdateShockwave(work);
        break;
    case 5:
        work->dsd->lastState = work->dsd->state;
        BosDsdMainUpdateCircleAttack(work);
        break;
    case 6:
        work->dsd->lastState = work->dsd->state;
        BosDsdMainUpdateEnergy1Attack(work);
        break;
    case 7:
        work->dsd->lastState = work->dsd->state;
        BosDsdMainUpdateEnergy2Attack(work);
        break;
    case 8:
        BosDsdMainUpdateBreak(work);
        break;
    case 9:
        BosDsdMainUpdateEventIdle(work);
        break;
    case 10:
        BosDsdMainUpdateState10(work);
        break;
    case 11:
        BosDsdMainUpdateDefeat(work);
        break;
    }

    ColliderSetPosition(&d->body[0].collider, d->body[0].x, d->body[0].y, d->body[0].z);
    ColliderSetPosition(&p->collider, p->x, p->y, p->z);
    TaskPoolUpdate(&work->tasks);
    work->lastBreakDifference = gBtlWork->breakDifference;

    return 1;
}

void task_bos_dsd_main_2(DsdMainWork* work) {
    DsdWork* d = work->dsd;
    void* gfx;
    s16 x;
    s16 y;

    if (gBtlWork->paused) {
        LoadPaletteWithEffect(gUnk_096FB744, (void*)PLTT, 32);
        gfx = work->palette;
    } else if (d->flags & DSD_FLAG_HURT) {
        if (gFrameCounter & 1) {
            LoadPaletteWithEffect(gUnk_08F69BC4, (void*)PLTT, 32);
            gfx = work->palette2;
        } else {
            LoadPaletteWithEffect(gUnk_096FB744, (void*)PLTT, 32);
            gfx = work->palette;
        }
    } else {
        gfx = work->palette;
    }

    ScrollBgMapTo(1, ((gBtlWork->viewX - d->body[0].x) >> 8) + 100,
                  ((gBtlWork->viewY - (d->body[0].y + d->body[0].z)) >> 8) + 280);

    if (work->spriteVisible == 1) {
        GetBattleSpritePriorityFlags(d->body[0].y);
        WorldToScreen(&x, &y, d->body[0].x, d->body[0].y, -0x6400);
        DrawSprite(x - 96, y + 20, work->gfx, work->tiles, gfx, NULL, SPRITE_PRIORITY(1),
                   -4101 - (d->body[0].y >> 8) * 4);
        DrawSprite(x - 96, y + 20, work->gfx2, work->tiles2, gfx, NULL, SPRITE_PRIORITY(2),
                   -4099 - (d->body[0].y >> 8) * 4);
    }

    TaskPoolDraw(&work->tasks);
}

void task_bos_dsd_main_3(DsdMainWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
    ReleaseObjTiles(work->dsd->tiles);
    ReleaseObjPalette(work->dsd->palette);
    ReleaseObjTiles(work->dsd->tiles2);
    ReleaseObjPalette(work->dsd->palette2);
    ReleaseObjPalette(work->dsd->palette3);
    ReleaseObjTiles(work->dsd->tiles3);
    ReleaseObjPalette(work->dsd->palette4);
    ColliderUnregister(&work->body.collider);
    TaskPoolDestroy(&work->tasks);
}

void BosDsdMainUpdateDrift(DsdMainWork* work) {
    BtlObj* q = &work->dsd->body[1];

    if (q->hp > 0) {
        if (GetRandom() % 30 == 0) {
            TaskCreate(&work->tasks, &gTaskDescBosDsdRock, work->dsd);
        }

        if ((work->dsd->flags & DSD_FLAG_PLAYER_ON_PLATFORM) == 0) {
            gBtlWork->actor->x += work->dsd->driftX;
        }

        if (work->lastBreakDifference != gBtlWork->breakDifference) {
            if (gBtlWork->breakDifference > 0) {
                work->dsd->flags |= DSD_FLAG_DRIFT_CHANGED;

                if (gBtlWork->breakDifference > 14) {
                    work->dsd->driftX = 0x180;
                } else {
                    work->dsd->driftX = (gBtlWork->breakDifference << 8) / 10;
                }
            } else if (gBtlWork->breakDifference < 0) {
                work->dsd->flags |= DSD_FLAG_DRIFT_CHANGED;
                work->dsd->driftX = (gBtlWork->breakDifference << 9) / 10;
            } else {
                work->dsd->flags &= ~DSD_FLAG_DRIFT_CHANGED;
            }
        } else {
            work->dsd->flags &= ~DSD_FLAG_DRIFT_CHANGED;
        }
    }
}

void BosDsdMainResetPose(DsdMainWork* work) {
    DsdWork* p = work->dsd;
    BtlObj* q = &p->body[1];

    p->bgFrame = 0;
    work->baseFrame = 0;
    work->dsd->bgFrameTimer = 0;
    BosDsdSetBgFrame(0, 0x60);
    work->spriteVisible = 1;
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
    p->body[0].z = -0x6400;
    q->z = -0x8C00;
}

void BosDsdMainUpdateIdleFrames(DsdMainWork* work) {
    DsdWork* d = work->dsd;
    BtlObj* q = &d->body[1];

    if (d->bgFrameTimer >= gBosDsdFrameDurations[d->bgFrame]) {
        d->bgFrameTimer = 0;
        work->dsd->bgFrame++;

        if (work->dsd->bgFrame > work->baseFrame + 7) {
            work->dsd->bgFrame = work->baseFrame;
        }

        BosDsdSetBgFrame(work->dsd->bgFrame, 0x60);
        d->body[0].z += gBosDsdIdleBob[work->dsd->bgFrame] << 8;
        q->z += gBosDsdIdleBob[work->dsd->bgFrame] << 8;
    }

    work->dsd->bgFrameTimer++;
    work->gfx = AnimUpdate(&work->anim);
    work->gfx2 = AnimUpdate(&work->anim2);
}

void BosDsdMainUpdateIdle(DsdMainWork* work) {
    BosDsdMainUpdateIdleFrames(work);

    if (gBtlWork->phase != 0) {
        if (GetRandom() % 80 == 0) {
            BosDsdMainChooseAttack(work);
        }
    }
}

void BosDsdMainBeginTransition(DsdMainWork* work, s32 x, s32 y, s32 z) {
    BtlObj* q = &work->dsd->body[1];

    FadeSetPaletteExcluded(0, 0);
    FadeSetPaletteExcluded(0x13, 0);
    FadeToAmount(FADE_MODE_BLACK, 0x14, 8);
    BgFxStartDsdTransition(x - 0x1400, y, z - 0xA00, 0x100);
    m4aSongNumStart(SONG_SND_721);
    q->flags |= BTLOBJ_FLAG_UNHITTABLE;
}

void BosDsdMainEndTransition(DsdMainWork* work) {
    BtlObj* q = &work->dsd->body[1];

    FadeToOriginal(FADE_MODE_BLACK, 8);
    FadeSetPaletteExcluded(0, 1);
    FadeSetPaletteExcluded(19, 1);
    q->flags &= ~BTLOBJ_FLAG_UNHITTABLE;
}

void BosDsdMainUpdateAttackStart(DsdMainWork* work) {
    DsdWork* d = work->dsd;
    BtlObj* q = &d->body[1];
    BtlObj* p = &work->body;

    switch (d->stateStep) {
    case 0:
        BosDsdMainBeginTransition(work, d->body[0].x, d->body[0].y, d->body[0].z);
        work->stepTimer = 0;
        work->dsd->stateStep++;
        break;
    case 1:
        work->stepTimer++;

        if (work->stepTimer > 11) {
            DisableBg(1);
            work->spriteVisible = 0;
            work->dsd->stateStep++;
        }

        break;
    case 2:
        switch (d->attackState) {
        case 4:
        case 5:
            CreateBgTileTransferTask(&work->tasks, 1, 0, 0x2C8, 8, gUnk_09699684);
            break;
        case 6:
            CreateBgTileTransferTask(&work->tasks, 1, 0, 0x280, 8, gUnk_096A3F44);
            break;
        case 7:
            CreateBgTileTransferTask(&work->tasks, 1, 0, 0x200, 8, gUnk_096A8BA4);
            break;
        }

        work->stepTimer = 0;
        work->dsd->stateStep++;
        break;
    case 3:
        work->stepTimer++;

        if (work->stepTimer > 9) {
            work->stepTimer = 0;
            d->stateStep++;
        }

        break;
    default:
        work->dsd->stateStep = 0;

        switch (work->dsd->attackState) {
        case 4:
        case 5:
            p->x = 0xDC00;
            p->y = 0x16800;
            p->z = -0x4000;
            work->dsd->state = 3;
            break;
        case 6:
            p->x = 0xBC00;
            p->y = 0x16800;
            p->z = 0;
            work->dsd->state = 6;
            break;
        case 7:
            p->x = 0xDC00;
            p->y = 0x16800;
            p->z = 0;
            work->dsd->state = 7;
            break;
        }

        q->flags &= ~BTLOBJ_FLAG_UNHITTABLE;
        break;
    }
}

void BosDsdMainUpdateReturn(DsdMainWork* work) {
    DsdWork* d = work->dsd;
    BtlObj* q = &d->body[1];
    BtlObj* p = &work->body;

    switch (d->stateStep) {
    case 0:
        BosDsdMainBeginTransition(work, d->body[0].x, d->body[0].y, d->body[0].z);
        work->stepTimer = 0;
        work->dsd->stateStep++;
        break;
    case 1:
        work->stepTimer++;

        if (work->stepTimer > 4) {
            DisableBg(1);
            work->dsd->stateStep++;
        }

        break;
    case 2:
        CreateBgTileTransferTask(&work->tasks, 1, 0, 0x120, 3, gUnk_096874E4);
        work->stepTimer = 0;
        work->dsd->stateStep++;
        break;
    case 3:
        work->stepTimer++;

        if (work->stepTimer > 4) {
            work->stepTimer = 0;
            BosDsdMainResetPose(work);
            d->body[0].x = 0xDC00;
            q->x = 0xDC00;
            p->x = 0xDC00;
            p->y = 0x16800;
            p->z = 0;
            work->dsd->stateStep++;
        }

        break;
    case 4:
        if (!BgFxIsActive()) {
            BosDsdMainEndTransition(work);
            work->dsd->stateStep++;
        }

        break;
    default:
        d->stateStep = 0;
        work->dsd->state = 1;
        break;
    }
}

void BosDsdMainUpdateApproach(DsdMainWork* work) {
    DsdWork* d = work->dsd;
    BtlObj* q = &d->body[1];

    switch (d->stateStep) {
    case 0:
        work->dsd->bgFrame = 8;
        work->baseFrame = 8;
        work->dsd->bgFrameTimer = 0;
        work->stepTimer = 0;
        work->moveSteps = 30;
        BosDsdSetBgFrame(8, 0x80);
        EnableBg(1);
        d->body[0].x = 0x13C00;
        d->body[0].y = 0x16800;
        d->body[0].z = -0xAC00;
        q->x = 0x13C00;
        q->y = 0x16800;
        q->z = -0xD400;
        work->dsd->stateStep++;
        break;
    case 1:
        if (BgFxIsActive()) {
            break;
        }

        BosDsdMainEndTransition(work);
        work->dsd->stateStep++;
        break;
    case 2:
        if ((s16)work->moveSteps > 0) {
            ApproachValue(&d->body[0].x, 0xDC00, work->moveSteps);
            ApproachValue(&d->body[0].z, -0x9400, work->moveSteps);
            ApproachValue(&q->x, 0xDC00, work->moveSteps);
            ApproachValue(&q->z, -0xBC00, work->moveSteps);
            BtlMapSetCameraTarget(d->body[0].x, d->body[0].y + d->body[0].z);
            work->moveSteps--;
        } else {
            work->stepTimer = 0;
            work->dsd->bgFrame = 9;
            BosDsdSetBgFrame(work->dsd->bgFrame, 0x80);
            q->x = 0xEC00;
            q->z = -0x9400;
            work->dsd->stateStep++;
        }

        break;
    case 3:
        work->stepTimer++;

        if (work->stepTimer > 3) {
            work->stepTimer = 0;
            work->dsd->bgFrame = 10;
            BosDsdSetBgFrame(work->dsd->bgFrame, 0x80);
            q->x = 0xFC00;
            q->z = -0x9400;
            work->dsd->stateStep++;
        }

        break;
    case 4:
        work->stepTimer++;

        if (work->stepTimer > 1) {
            work->stepTimer = 0;
            d->body[0].x += 0x100;
            d->body[0].z += -0x100;
            work->dsd->stateStep++;
        }

        break;
    case 5:
        work->stepTimer++;

        if (work->stepTimer > 1) {
            work->stepTimer = 0;
            d->body[0].x += -0x100;
            d->body[0].z += 0x100;
            work->dsd->stateStep++;
        }

        break;
    case 6:
        work->stepTimer++;

        if (work->stepTimer > 25) {
            work->stepTimer = 0;
            work->dsd->bgFrame = 11;
            BosDsdSetBgFrame(work->dsd->bgFrame, 0x80);
            q->x = 0xEC00;
            q->z = -0x9400;
            work->dsd->stateStep++;
        }

        break;
    case 7:
        work->stepTimer++;

        if (work->stepTimer > 3) {
            work->stepTimer = 0;
            work->dsd->bgFrame = 12;
            BosDsdSetBgFrame(work->dsd->bgFrame, 0x80);
            q->x = 0xB400;
            q->z = -0x8400;
            work->dsd->stateStep++;
        }

        break;
    case 8:
        work->stepTimer++;

        if (work->stepTimer > 3) {
            work->stepTimer = 0;
            work->dsd->stateStep++;
        }

        break;
    default:
        d->stateStep = 0;
        work->dsd->state = work->dsd->attackState;
        break;
    }
}

void BosDsdMainLoopFrames(DsdMainWork* work) {
    if (work->dsd->bgFrameTimer >= gBosDsdFrameDurations[work->dsd->bgFrame]) {
        work->dsd->bgFrameTimer = 0;
        work->dsd->bgFrame++;

        if (work->dsd->bgFrame > work->baseFrame + 7) {
            work->dsd->bgFrame = work->baseFrame;
        }

        BosDsdSetBgFrame(work->dsd->bgFrame, 0x80);
    }

    work->dsd->bgFrameTimer++;
}

void BosDsdMainUpdateShockwave(DsdMainWork* work) {
    DsdWork* d = work->dsd;
    BtlObj* a = &d->body[1];
    BtlObj* b = &d->body[2];

    switch (d->stateStep) {
    case 0:
        work->dsd->bgFrame = 13;
        work->baseFrame = 13;
        work->dsd->bgFrameTimer = 0;
        work->stepTimer = 0;
        BosDsdSetBgFrame(13, 0x80);
        b->x = 0x7600;
        b->y = 0x16800;
        b->z = 0;
        b->flags &= ~BTLOBJ_FLAG_UNHITTABLE;
        BtlMapStartShake();
        m4aSongNumStart(SONG_EF_AIRO);
        BgFxStartLexceusGround(0x7800, 0x16800, 0, 0x100);
        ColliderSetDisabled(&b->collider, 0);
        work->dsd->stateStep++;
        break;
    case 1:
        BosDsdMainLoopFrames(work);
        work->stepTimer++;

        if (work->stepTimer > 1) {
            work->stepTimer = 0;
            d->body[0].x += -0x100;
            d->body[0].z += 0x100;
            work->dsd->stateStep++;
        }

        break;
    case 2:
        BosDsdMainLoopFrames(work);
        work->stepTimer++;

        if (work->stepTimer > 1) {
            work->stepTimer = 0;
            d->body[0].x += 0x100;
            d->body[0].z += -0x100;
            work->dsd->stateStep++;
        }

        break;
    case 3:
        BosDsdMainLoopFrames(work);

        if (!BgFxIsActive()) {
            ClearBtlObjActionFlags(a);
            work->stepTimer = 0;
            work->dsd->stateStep++;
        }

        break;
    case 4:
        BosDsdMainLoopFrames(work);
        work->stepTimer++;

        if (work->stepTimer > 179) {
            work->stepTimer = 0;
            work->dsd->stateStep++;
        }

        break;
    case 5:
        BosDsdSetBgFrame(8, 0x80);
        b->flags |= BTLOBJ_FLAG_UNHITTABLE;
        ColliderSetDisabled(&b->collider, 1);
        work->dsd->stateStep++;
        break;
    default:
        d->stateStep = 0;
        work->dsd->state = 0;
        break;
    }
}

void BosDsdMainUpdateCircleAttack(DsdMainWork* work) {
    DsdWork* d = work->dsd;
    BtlObj* a = &d->body[1];
    BtlObj* b = &d->body[2];
    BtlObj* e;

    switch (d->stateStep) {
    case 0:
        work->dsd->bgFrame = 21;
        work->baseFrame = 21;
        work->dsd->bgFrameTimer = 0;
        BosDsdSetBgFrame(work->dsd->bgFrame, 0x80);
        TaskCreate(&work->tasks, &gTaskDescBosDsdCircle, work->dsd);
        BgFxStartGroundImpact(0x8000, 0x15400);
        ApplyAttackBox(0x101, 0x8000, 0x16800, -0x1400, 16, 16, 16);
        m4aSongNumStart(SONG_EF_DS_BEEM);
        work->dsd->stateStep++;
        break;
    case 1:
        if (++work->dsd->bgFrameTimer >= gBosDsdFrameDurations[work->dsd->bgFrame]) {
            work->dsd->bgFrameTimer = 0;
            work->dsd->bgFrame++;
            a->z += 0x600;

            if (work->dsd->bgFrame > work->baseFrame + 6) {
                work->dsd->bgFrame = work->baseFrame + 6;
                work->dsd->stateStep++;
            }

            BosDsdSetBgFrame(work->dsd->bgFrame, 0x80);
        }

        break;
    case 2:
        work->dsd->bgFrame = 28;
        work->baseFrame = 28;
        work->dsd->bgFrameTimer = 0;
        work->stepTimer = 0;
        ClearBtlObjActionFlags(a);
        b->x = 0x9000;
        b->y = 0x16800;
        b->z = 0;
        b->flags &= ~BTLOBJ_FLAG_UNHITTABLE;
        work->dsd->stateStep++;
        break;
    case 3:
        if (++work->dsd->bgFrameTimer >= gBosDsdFrameDurations[work->dsd->bgFrame]) {
            work->dsd->bgFrameTimer = 0;
            work->dsd->bgFrame++;

            if (work->dsd->bgFrame > work->baseFrame + 6) {
                work->dsd->bgFrame = work->baseFrame;
            }

            BosDsdSetBgFrame(work->dsd->bgFrame, 0x80);
        }

        work->stepTimer++;

        if (work->stepTimer > 299) {
            work->dsd->stateStep++;
        }

        break;
    case 4:
        work->dsd->bgFrame = 27;
        work->baseFrame = 27;
        work->dsd->bgFrameTimer = 0;
        work->stepTimer = 0;
        b->flags |= BTLOBJ_FLAG_UNHITTABLE;
        work->dsd->stateStep++;
        break;
    case 5:
        if (++work->dsd->bgFrameTimer >= gBosDsdFrameDurations[work->dsd->bgFrame]) {
            work->dsd->bgFrameTimer = 0;
            work->dsd->bgFrame--;
            a->z -= 0x600;

            if (work->dsd->bgFrame < work->baseFrame - 6) {
                work->dsd->bgFrame = work->baseFrame - 6;

                if (gBtlWork->enemyTileCount <= 0 && (work->dsd->flags & DSD_FLAG_PLATFORM_ACTIVE) == 0) {
                    DropGimmickCard(0, d->body[0].x, d->body[0].y, d->body[0].z);
                }

                work->dsd->stateStep++;
            }

            BosDsdSetBgFrame(work->dsd->bgFrame, 0x80);
        }

        break;
    case 6:
        work->stepTimer = 0;
        BosDsdSetBgFrame(8, 0x80);
        e = ListPoolFirst(&gBtlWork->pool);

        while (e != NULL) {
            if (e->kind == 0) {
                e->flags |= BTLOBJ_FLAG_WARP_PENDING;
                m4aSongNumStart(SONG_BTL_DARKDEAD);
            }

            e = ListPoolNext(&e->node);
        }

        work->dsd->stateStep++;
        break;
    default:
        d->stateStep = 0;
        work->dsd->state = 0;
        break;
    }
}

void BosDsdMainLoopMapFrames(DsdMainWork* work) {
    if (work->dsd->bgFrameTimer >= gBosDsdFrameDurations[work->dsd->bgFrame]) {
        work->dsd->bgFrameTimer = 0;
        work->dsd->bgFrame++;

        if (work->dsd->bgFrame > work->baseFrame + 4) {
            work->dsd->bgFrame = work->baseFrame;
        }

        BosDsdSetBgMap(work->dsd->bgFrame);
    }

    work->dsd->bgFrameTimer++;
}

void BosDsdMainUpdateEnergy1Attack(DsdMainWork* work) {
    DsdWork* d = work->dsd;
    BtlObj* q = &d->body[1];

    switch (d->stateStep) {
    case 0:
        work->dsd->bgFrame = 36;
        work->baseFrame = 36;
        work->dsd->bgFrameTimer = 0;
        work->moveSteps = 30;
        work->spriteVisible = 0;
        BosDsdSetBgMap(work->dsd->bgFrame);
        q->x = 0xDC00;
        q->z = -0x6000;
        work->dsd->stateStep++;
        break;
    case 1:
        if (BgFxIsActive()) {
            break;
        }

        BosDsdMainEndTransition(work);
        work->stepTimer = 0;
        work->moveSteps = 0;
        work->dsd->stateStep++;
        break;
    case 2:
        BosDsdMainLoopMapFrames(work);
        work->energy1Task = TaskCreate(&work->tasks, &gTaskDescBosDsdEnergy1, work->dsd);
        work->dsd->stateStep++;
        break;
    case 3:
        BosDsdMainLoopMapFrames(work);

        if (IsTaskActive(work->energy1Task)) {
            break;
        }

        if (work->dsd->hpPhase == 0) {
            work->dsd->stateStep = 6;
            break;
        }

        work->stepTimer++;

        if (work->stepTimer > 4) {
            work->stepTimer = 0;
            work->energy1Task2 = TaskCreate(&work->tasks, &gTaskDescBosDsdEnergy1, work->dsd);
            work->dsd->stateStep++;
        }

        break;
    case 4:
        BosDsdMainLoopMapFrames(work);

        if (IsTaskActive(work->energy1Task2)) {
            break;
        }

        if (work->dsd->hpPhase == 1) {
            work->dsd->stateStep = 6;
            break;
        }

        work->stepTimer++;

        if (work->stepTimer > 4) {
            work->stepTimer = 0;
            work->energy1Task3 = TaskCreate(&work->tasks, &gTaskDescBosDsdEnergy1, work->dsd);
            work->dsd->stateStep++;
        }

        break;
    case 5:
        BosDsdMainLoopMapFrames(work);

        if (IsTaskActive(work->energy1Task3)) {
            break;
        }

        work->dsd->stateStep++;
        break;
    case 6:
        BosDsdMainLoopMapFrames(work);
        ClearBtlObjActionFlags(q);
        work->dsd->stateStep++;
        break;
    default:
        d->stateStep = 0;
        work->dsd->state = 0;
        break;
    }
}

void BosDsdMainUpdateEnergy2Attack(DsdMainWork* work) {
    DsdWork* d = work->dsd;
    BtlObj* q = &d->body[1];

    switch (d->stateStep) {
    case 0:
        work->dsd->bgFrame = 41;
        work->baseFrame = 41;
        work->dsd->bgFrameTimer = 0;
        work->moveSteps = 30;
        work->spriteVisible = 0;
        BosDsdSetBgMap(work->dsd->bgFrame);
        work->stepTimer = 0;
        q->x = 0xE400;
        q->z = -0x5C00;
        work->dsd->stateStep++;
        break;
    case 1:
        if (BgFxIsActive()) {
            break;
        }

        BosDsdMainEndTransition(work);
        work->moveSteps = 0;
        work->dsd->stateStep++;
        break;
    case 2:
        BosDsdMainLoopMapFrames(work);
        LoadPalette(gUnk_096FB744, (void*)PLTT, 32);
        work->energy2Task = TaskCreate(&work->tasks, &gTaskDescBosDsdEnergy2, work->dsd);
        work->dsd->stateStep++;
        break;
    case 3:
        BosDsdMainLoopMapFrames(work);

        if (IsTaskActive(work->energy2Task)) {
            break;
        }

        work->dsd->stateStep++;
        break;
    case 4:
        BosDsdMainLoopMapFrames(work);
        ClearBtlObjActionFlags(q);
        work->dsd->stateStep++;
        break;
    default:
        d->stateStep = 0;
        work->dsd->state = 0;
        break;
    }
}

void BosDsdMainUpdateState10(DsdMainWork* work) {
}

void BosDsdMainUpdateBreak(DsdMainWork* work) {
    DsdWork* d = work->dsd;
    BtlObj* a = &d->body[1];
    BtlObj* b = &d->body[2];

    if (d->lastState == 2 || d->lastState == 3) {
        ClearBtlObjActionFlags(a);
        b->flags |= BTLOBJ_FLAG_UNHITTABLE;
        ColliderSetDisabled(&b->collider, 1);
        work->dsd->stateStep = 0;
        work->dsd->state = 0;
    } else if (d->stateStep > 60) {
        ClearBtlObjActionFlags(a);
        b->flags |= BTLOBJ_FLAG_UNHITTABLE;
        ColliderSetDisabled(&b->collider, 1);
        work->dsd->stateStep = 0;
        work->dsd->state = 0;
    } else {
        d->stateStep++;
    }
}

void BosDsdMainUpdateDefeat(DsdMainWork* work) {
    DsdWork* d = work->dsd;
    BtlObj* a = &d->body[1];
    BtlObj* b = &d->body[2];
    BtlObj* c = &work->body;
    BtlObj* e;
    CharaObjParam param;

    switch (d->stateStep) {
    case 0:
        e = ListPoolFirst(&gBtlWork->pool);

        while (e != NULL) {
            if (e->kind == 0) {
                e->flags |= BTLOBJ_FLAG_WARP_PENDING;
                m4aSongNumStart(SONG_BTL_DARKDEAD);
            }

            e = ListPoolNext(&e->node);
        }

        work->dsd->stateStep++;
        break;
    case 1:
        BeginBossDefeat(a);
        ColliderSetDisabled(&a->collider, 1);
        ColliderSetDisabled(&b->collider, 1);
        ColliderSetDisabled(&c->collider, 1);
        FadeSetPaletteExcluded(0, 0);
        FadeSetPaletteExcluded(19, 0);
        FadeToAmount(FADE_MODE_BLACK, 20, 8);
        BgFxStartDsdTransition(a->x - 0x1400, a->y, a->z - 0xA00, 0x100);
        m4aSongNumStart(SONG_SND_721);
        work->stepTimer = 0;
        work->dsd->stateStep++;
        BtlMapSetCameraTarget(d->body[0].x - 0x1400, d->body[0].y + d->body[0].z + 0x3000);
        break;
    case 2:
        BtlMapSetCameraTarget(d->body[0].x - 0x1400, d->body[0].y + d->body[0].z + 0x3000);
        work->stepTimer++;

        if (work->stepTimer > 11) {
            DisableBg(1);
            work->spriteVisible = 0;
            work->dsd->stateStep++;
        }

        break;
    case 3:
        BosDsdSetBgFrame(36, 0xE0);
        EnableBg(1);
        BtlMapSetCameraTarget(d->body[0].x - 0x1400, d->body[0].y + d->body[0].z + 0x3000);
        work->dsd->stateStep++;
        break;
    case 4:
        BtlMapSetCameraTarget(d->body[0].x - 0x1400, d->body[0].y + d->body[0].z + 0x3000);

        if (BgFxIsActive()) {
            break;
        }

        FadeToOriginal(FADE_MODE_BLACK, 8);
        FadeSetPaletteExcluded(0, 1);
        FadeSetPaletteExcluded(19, 1);
        work->dsd->stateStep++;
        break;
    case 5:
        BtlMapSetCameraTarget(d->body[0].x - 0x1400, d->body[0].y + d->body[0].z + 0x3000);
        work->dsd->stateStep++;
        break;
    case 6:
        BtlMapSetCameraTarget(d->body[0].x - 0x1400, d->body[0].y + d->body[0].z + 0x3000);
        param.tilesAddr = 0;
        param.tileCount = 0;
        param.tilesAddr2 = 0;
        param.tileCount2 = 0;
        param.tilesAddr3 = 0;
        param.tileCount3 = 0;
        param.paletteAddr = 0;
        param.paletteSize = 0;
        param.tilesAddr4 = VRAM;
        param.tileCount4 = 0xE0;
        param.paletteAddr2 = PLTT;
        param.paletteSize2 = 32;
        param.x = d->body[0].x - 0x1400;
        param.y = d->body[0].y;
        param.z = d->body[0].z + 0x3000;
        param.callback = NULL;
        param.prizeObj = a;
        param.flags = 1;
        CharaObjInitDefeat(&param);
        work->dsd->stateStep++;
        break;
    case 7:
        if (!CharaObjUpdateDefeat()) {
            d->body[0].x = 300;
            d->body[0].y = 0;
            d->body[0].z = 0;
            ScrollBgMapTo(1, ((gBtlWork->viewX - 300) >> 8) + 100, (gBtlWork->viewY >> 8) + 280);
            EndBossDefeat();
            work->dsd->stateStep++;
        } else {
            BtlMapSetCameraTarget(d->body[0].x - 0x1800, d->body[0].y + d->body[0].z + 0x3000);
        }

        break;
    default:
        d->flags |= DSD_FLAG_DEFEAT_DONE;
        break;
    }
}

void BosDsdMainUpdateEventIdle(DsdMainWork* work) {
    BosDsdMainUpdateIdleFrames(work);
}

void BosDsdMainChooseAttack(DsdMainWork* work) {
    DsdWork* d = work->dsd;
    BtlObj* a = &d->body[1];

    if (a->hp < a->maxHp / 3) {
        d->hpPhase = 2;

        if (GetRandom() % 100 <= 9) {
            RequestBossCardValue(1);
        } else if (GetRandom() % 90 <= 49) {
            RequestBossCardValue(GetRandom() % 2 + 8);
        } else {
            RequestBossCardValue(GetRandom() % 3 + 5);
        }
    } else if (a->hp < a->maxHp / 3 * 2) {
        d->hpPhase = 1;

        if (GetRandom() % 100 <= 29) {
            RequestBossCardValue(GetRandom() % 2 + 8);
        } else {
            RequestBossCardValue(GetRandom() % 3 + 4);
        }
    } else {
        d->hpPhase = 0;

        if (GetRandom() % 100 <= 59) {
            RequestBossCardValue(GetRandom() % 3 + 7);
        } else {
            RequestBossCardValue(GetRandom() % 4 + 3);
        }
    }

    switch (work->dsd->attackCycle) {
    case 0:
        work->dsd->attackState = 5;
        break;
    case 1:
        work->dsd->attackState = 6;
        break;
    case 2:
        work->dsd->attackState = 4;
        break;
    case 3:
        work->dsd->attackState = 7;
        break;
    default:
        work->dsd->attackState = 0;
        break;
    }

    work->dsd->attackCycle++;

    if (work->dsd->attackCycle > 3) {
        work->dsd->attackCycle = 0;
    }

    RequestEnemyCardUse(a);
}

void task_bos_dsd_map_0() {
    LoadBgTiles(0, gUnk_096874E4, 0x8000);
    LoadBgPalette(0, gUnk_096FB744, 0x120);
    SetBgMapBlocks(0, gBosDsdMapBlocks, 2, 2);
    gBtlWork->scale = 0x100;
    gBtlWork->zoomScale = 0x100;
    gBtlWork->x = 0xA000;
    gBtlWork->y = 0x13600;
    gBtlWork->viewX = 0xA000;
    gBtlWork->viewY = 0x13600;
    gBtlWork->x2 = 0xA000;
    gBtlWork->y2 = 0x13600;
    gBtlWork->zoomX = 0xA000;
    gBtlWork->zoomY = 0x13600;
    gBtlWork->zoomSteps = 0xF;
    gBtlWork->rotation = 0;
    BtlMapResetShake();
    ScrollBgMapTo(0, gBtlWork->viewX >> 8, gBtlWork->viewY >> 8);
}

u8 task_bos_dsd_map_1() {
    s32 dx;
    s32 dy;

    BtlMapUpdateShake();
    dx = (gBtlWork->x2 - gBtlWork->x) >> 3;
    dy = (gBtlWork->y2 - gBtlWork->y) >> 3;

    if (dx > 0x500) {
        dx = 0x500;
    } else if (dx < -0x500) {
        dx = -0x500;
    }

    gBtlWork->x += dx;
    gBtlWork->y += dy;
    gBtlWork->viewX = gBtlWork->x;
    gBtlWork->viewY = gBtlWork->y;

    if (gBtlWork->viewX < (gBtlWork->xMin + 0x78) << 8) {
        gBtlWork->viewX = (gBtlWork->xMin + 0x78) << 8;
    } else if (gBtlWork->viewX > (gBtlWork->xMax - 0x78) << 8) {
        gBtlWork->viewX = (gBtlWork->xMax - 0x78) << 8;
    }

    if (gBtlWork->viewY < 0x5000) {
        gBtlWork->viewY = 0x5000;
    } else if (gBtlWork->viewY > (gBtlWork->yMax - 0x50) << 8) {
        gBtlWork->viewY = (gBtlWork->yMax - 0x50) << 8;
    }

    gBtlWork->viewY += BtlMapGetShake();
    ScrollBgMapTo(0, (gBtlWork->viewX >> 8) - 0x78, (gBtlWork->viewY >> 8) - 0x28);

    return 1;
}

const s16 gBosDsdFrameDurations[47] = {
    10, 10, 10, 10, 10, 10, 10, 10, 4, 2, 2, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 4, 4, 4, 4, 4, 4, 4, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0,
};

const s8 gBosDsdIdleBob[10] = { -1, 1, 1, 1, 1, -1, -1, -1, 0, 0 };

const u16* gBosDsdFrameMaps[46][4] = {
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E3C64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E4464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E4C64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E5464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E5C64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E5464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E4C64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E4464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E7464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E6C64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E6464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E6C64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E7464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E7C64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E8464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E8C64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E9464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E9C64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E9464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E8C64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096E8464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096EA464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096EAC64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096EB464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096EBC64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096EC464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096ECC64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096ED464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096EDC64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096EE464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096EEC64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096EF464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096EFC64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096EF464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096EEC64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096EE464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096F0464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096F0C64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096F1464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096F1C64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096F2464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096F2C64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096F3464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096F3C64, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096F4464, gUnk_08125E24 },
    { gUnk_08125E24, gUnk_08125E24, gUnk_096F4C64, gUnk_08125E24 },
};

const u16* gUnk_09EF2D84 = gUnk_08125E24;

const u16* gUnk_09EF2D88 = gUnk_08125E24;

const u16* gUnk_09EF2D8C = gUnk_08125E24;

const u16* gUnk_09EF2D90 = gUnk_08125E24;

void* gBosDsdFrameTiles[37] = {
    gUnk_096874E4,
    gUnk_0968F4E4,
    gUnk_096918A4,
    gUnk_09693C64,
    gUnk_09696024,
    gUnk_09693C64,
    gUnk_096918A4,
    gUnk_0968F4E4,
    gUnk_09699684,
    gUnk_09699684,
    gUnk_09699684,
    gUnk_09699684,
    gUnk_09699684,
    gUnk_09699684,
    gUnk_0969EF04,
    gUnk_0969FF04,
    gUnk_096A0F04,
    gUnk_096A1F04,
    gUnk_096A0F04,
    gUnk_0969FF04,
    gUnk_0969EF04,
    gUnk_09699684,
    gUnk_09699684,
    gUnk_09699684,
    gUnk_09699684,
    gUnk_09699684,
    gUnk_09699684,
    gUnk_09699684,
    gUnk_09699684,
    gUnk_0969EF04,
    gUnk_0969FF04,
    gUnk_096A0F04,
    gUnk_096A1F04,
    gUnk_096A0F04,
    gUnk_0969FF04,
    gUnk_0969EF04,
    gUnk_096A3F44,
};

void* gUnk_09EF2E28 = gUnk_096A3F44;

void* gUnk_09EF2E2C = gUnk_096A3F44;

void* gUnk_09EF2E30 = gUnk_096A3F44;

void* gUnk_09EF2E34 = gUnk_096A3F44;

void* gUnk_09EF2E38 = gUnk_096A8BA4;

void* gUnk_09EF2E3C = gUnk_096A8BA4;

void* gUnk_09EF2E40 = gUnk_096A8BA4;

void* gUnk_09EF2E44 = gUnk_096A8BA4;

void* gUnk_09EF2E48 = gUnk_096A8BA4;

void* gUnk_09EF2E4C = NULL;

TaskDesc gTaskDescBosDsdMain = {
    "task_bos_dsd_main",
    (TaskInitFunc)task_bos_dsd_main_0,
    (TaskUpdateFunc)task_bos_dsd_main_1,
    (TaskDrawFunc)task_bos_dsd_main_2,
    (TaskDestroyFunc)task_bos_dsd_main_3,
    sizeof(DsdMainWork),
};

const u16* gBosDsdMapBlocks[4] = {
#if defined(VERSION_US)
    gBossMapBlockUs_096E2C64,
    gBossMapBlockUs_08125E24,
    gBossMapBlockUs_096E3464,
    gBossMapBlockUs_08125E24,
#elif defined(VERSION_JP)
    gBossMapBlockJp_0969B440,
    gBossMapBlockJp_08125EA0,
    gBossMapBlockJp_0969BC40,
    gBossMapBlockJp_08125EA0,
#elif defined(VERSION_EU)
    gBossMapBlockEu_096AA98C,
    gBossMapBlockEu_08124944,
    gBossMapBlockEu_096AB18C,
    gBossMapBlockEu_08124944,
#endif
};

TaskDesc gTaskDescBosDsdMap = {
    "task_bos_dsd_map",
    (TaskInitFunc)task_bos_dsd_map_0,
    (TaskUpdateFunc)task_bos_dsd_map_1,
    NULL,
    NULL,
    sizeof(DsdMapWork),
};
