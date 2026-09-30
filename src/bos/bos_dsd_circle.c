#include "bos2.h"
#include "sprites_bos2.h"
#include "sprites_btl.h"
#include "btl_api.h"
#include "fade.h"
#include "songs.h"

void task_bos_dsd_circle_0(DsdCircleWork* work, void* arg) {
    work->dsd = arg;
    work->x = (gBosDsdCircleOffsetsX[0] << 8) + 0xDC00;
    work->y = (gBosDsdCircleOffsetsY[0] << 8) + 0x16800;
    work->z = 0;
    work->paletteTimer = 0;
    work->paletteFrame = 0;
    work->frame = 0;
    work->summonTimer = 0;
    work->endTimer = 0;
    work->gfx = gUnk_09EF3C50[0];
}

u8 task_bos_dsd_circle_1(DsdCircleWork* work) {
    DsdWork* d = work->dsd;

    if (d->state == 8 || d->state == 0) {
        if (work->endTimer > 66) {
            return 0;
        }

        work->endTimer++;
        return 1;
    }

    switch (d->stateStep) {
    case 1:
        work->frame = work->dsd->bgFrame - 21;
        work->gfx = gUnk_09EF3C50[work->frame];
        work->x = (gBosDsdCircleOffsetsX[work->frame] << 8) + 0xDC00;
        work->y = (gBosDsdCircleOffsetsY[work->frame] << 8) + 0x16800;
        break;
    case 2:
        break;
    case 3:
        work->paletteTimer++;

        if (work->paletteTimer >= gBosDsdCirclePaletteDurations[work->paletteFrame]) {
            work->paletteTimer = 0;
            work->paletteFrame++;

            if (work->paletteFrame > 7) {
                work->paletteFrame = 0;
            }

            LoadObjPaletteBank(work->dsd->palette->index,
                               &gUnk_096FB904[work->paletteFrame * 32]);
        }

        if (work->summonTimer == 60 || work->summonTimer == 110) {
            SpawnEnemy(0, work->x + ((GetRandom() % 101 - 50) << 8),
                          work->y + ((GetRandom() % 17 - 8) << 8), 0);
        }

        work->summonTimer++;
        break;
    case 4:
        LoadObjPaletteBank(work->dsd->palette->index, gUnk_096FB904);
        work->frame = work->dsd->bgFrame - 21;
        break;
    case 5:
        work->frame = work->dsd->bgFrame - 21;
        work->gfx = gUnk_09EF3C50[work->frame];
        work->x = (gBosDsdCircleOffsetsX[work->frame] << 8) + 0xDC00;
        work->y = (gBosDsdCircleOffsetsY[work->frame] << 8) + 0x16800;
        break;
    case 6:
        work->frame = 0;
        work->gfx = gUnk_09EF3C50[work->frame];
        work->x = (gBosDsdCircleOffsetsX[work->frame] << 8) + 0xDC00;
        work->y = (gBosDsdCircleOffsetsY[work->frame] << 8) + 0x16800;
        break;
    case 7:
        return 0;
    }

    if (work->dsd->state == 11) {
        if (BgFxIsActive() == 1) {
            BgAnimStop();
        }

        return 0;
    }

    return 1;
}

void task_bos_dsd_circle_2(DsdCircleWork* work) {
    s16 x;
    s16 y;

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, work->gfx, work->dsd->tiles, work->dsd->palette, 0, 0xC00, 0xFFFF);
}

void task_bos_dsd_circle_3(void) {
}

void task_bos_dsd_energy1_0(DsdEnergy1Work* work, void* arg) {
    work->dsd = arg;
    work->x = 0xBC00;
    work->y = 0x16800;
    work->z = -0x2400;
    work->unk_10 = 0;
    work->unk_14 = 0;
    work->unk_18 = 0;
    work->angle = 0xF4;
    work->targetAngle = 0xF4;
    work->speed = 0x800;
    work->unk_30 = 0x19;
    work->state = 0;
    work->unk_36 = 0;
    work->timer = 0;
    work->chargeTime = 0xF;
    work->unk_3A = 0x3C;
    work->visible = 0;
    work->vx = gSineTable[work->angle] * work->speed >> 8;
    work->vy = 0;
    work->vz = -gSineTable[work->angle + 0x40] * work->speed >> 8;
    work->gfx = gUnk_08B22CBC;
}

u8 task_bos_dsd_energy1_1(DsdEnergy1Work* work) {
    switch (work->state) {
    case 0:
        BgFxStartEnemySpawn(work->x, work->y, work->z, 0x100);
        work->state++;
        break;
    case 1:
        if (BgFxIsActive() != 0) {
            break;
        }

        BgFxStartDsdEnergy(work->x, work->y, work->z, 0x100, work->chargeTime, 0);
        m4aSongNumStart(SONG_SND_701);
        work->state++;
        break;
    case 2:
        work->timer++;

        if (work->timer >= work->chargeTime) {
            work->visible = 1;
            work->timer = 0;
            work->unk_36 = 10;
            work->vy = (gBtlWork->targetY - work->y) / 15;
            work->state++;
        }
        break;
    case 3:
        BosDsdEnergy1UpdateArc(work);
        break;
    case 4:
        BosDsdEnergy1UpdateHoming(work);
        break;
    case 5:
        BgFxAddPosition(work->vx, work->vy, work->vz);
        work->x += work->vx;
        work->y += work->vy;
        work->z += work->vz;
        break;
    }

    if (ApplyAttackBox(0x102, work->x, work->y, work->z, 16, 16, 16) == 1) {
        BgFxSignalEnd(0);
        m4aSongNumStart(SONG_EF_RAC_BEEMENTRY);
        work->visible = 0;
        return 0;
    }

    if (work->z >= -0x800 || work->x <= -0x2000 || work->x > 0x11FFF ||
        work->dsd->state == 8 || work->dsd->state == 11) {
        BgFxSignalEnd(0);
        work->visible = 0;
        return 0;
    }

    return 1;
}

void task_bos_dsd_energy1_2(DsdEnergy1Work* work) {
    ObjAffine* affine;
    s32 scale;
    s32 flag;
    s16 x;
    s16 y;

    if (work->visible == 1) {
        if (work->z >= 0 && gBtlWork->scale == 0x100) {
            affine = 0;
        } else {
            scale = 0x200 - -work->z / 128;

            if (scale <= 0x7F) {
                scale = 0x80;
            }

            flag = 0;

            if (scale > 0x100) {
                flag = 1;
            }

            affine = AllocObjAffine(0, scale, scale, flag);
        }

        WorldToScreen(&x, &y, work->x, work->y, 0);
        DrawSprite(x, y, work->gfx, work->dsd->tiles3, work->dsd->palette4, affine, 0xC00, 0xFFF0);
    }
}

void task_bos_dsd_energy1_3(void) {
}

void BosDsdEnergy1UpdateArc(DsdEnergy1Work* work) {
    work->vx = gSineTable[work->angle] * work->speed >> 8;
    work->vz = -gSineTable[work->angle + 0x40] * work->speed >> 8;
    work->speed -= 76;
    work->angle -= 3;
    work->x += work->vx;
    work->y += work->vy;
    work->z += work->vz;
    BgFxAddPosition(work->vx, work->vy, work->vz);

    if (work->timer > 15) {
        work->state++;
    } else {
        work->timer++;
    }
}

void BosDsdEnergy1UpdateHoming(DsdEnergy1Work* work) {
    u16 d;

    if (work->retargetTimer > 0) {
        work->retargetTimer = 0;
        work->targetAngle = GetAngle(work->x, work->z, gBtlWork->targetX, gBtlWork->targetZ);

        if (work->targetAngle >= work->angle) {
            d = work->targetAngle - work->angle;

            if ((s16)d > 10) {
                d = 10;
            }
        } else {
            d = work->targetAngle - work->angle;

            if ((s16)d < -10) {
                d = -10;
            }
        }

        work->angle += d;
        work->vx = gSineTable[work->angle] * work->speed >> 8;
        work->vy = 0;
        work->vz = -gSineTable[work->angle + 0x40] * work->speed >> 8;
    }

    work->retargetTimer++;
    work->speed += 25;
    BgFxAddPosition(work->vx, work->vy, work->vz);
    work->x += work->vx;
    work->y += work->vy;
    work->z += work->vz;
}

void task_bos_dsd_energy2_0(DsdEnergy2Work* work, void* arg) {
    work->dsd = arg;
    work->x = 0xBC00;
    work->y = 0x16800;
    work->z = -0x2C00;
    work->state = 0;
    work->unk_2E = 0;
    work->timer = 0;
    work->chargeTime = 0xF;
    work->scaleX = 0x80;
    work->scaleY = 0x80;
    work->vx = 0;
    work->vy = 0;
    work->vz = -0x500;
    work->dropCount = 0;
    work->visible = 0;
    work->gfx = gUnk_08B22CBC;
    BgFxStartDsdEnergy(work->x, work->y, work->z, work->scaleX, work->chargeTime, 0);
    m4aSongNumStart(SONG_SND_704);

    switch (work->dsd->hpPhase) {
    case 1:
        work->dropTotal = 5;
        break;
    case 2:
        work->dropTotal = 7;
        break;
    case 0:
    default:
        work->dropTotal = 3;
        break;
    }
}

u8 task_bos_dsd_energy2_1(DsdEnergy2Work* work) {
    BtlObj* p;

    switch (work->state) {
    case 0:
        BgFxSetScale(work->scaleX, work->scaleY);
        work->scaleX += 25;
        work->scaleY += 25;

        if (work->timer >= work->chargeTime) {
            BtlMapSetCameraTarget(work->x, work->y + work->z);
            work->state++;
        } else {
            work->timer++;
        }
        break;
    case 1:
        BgFxAddPosition(work->vx, work->vy, work->vz);
        work->x += work->vx;
        work->y += work->vy;
        work->z += work->vz;
        BtlMapSetCameraTarget(work->x, work->y + work->z);

        if (work->z <= -0xF000) {
            work->state++;
        }
        break;
    case 2:
        BgFxStartMahluxiaGround(work->x, work->y, work->z, 0x103);
        m4aSongNumStart(SONG_SND_705);
        BtlMapSetCameraTarget(work->x, work->y + work->z);
        work->state++;
        break;
    case 3:
        BtlMapSetCameraTarget(work->x, work->y + work->z);

        if (BgFxIsActive() == 0) {
            work->state++;
        }
        break;
    case 4:
        FadeToAmount(0, gBtlWork->fadeAmount, 8);
        work->state++;
        break;
    case 5:
        work->x = (p = gBtlWork->actor)->x + (-0x4000 + GetRandom() % 0x8001);

        if (work->x < -0xFFF || work->x > 0x10FFF) {
            work->x = p->x;
        }

        work->y = gBtlWork->actor->y - 0x2400 + GetRandom() % 0x4001;
        work->z = -0xF000;
        work->vz = 0x600;
        BgFxStartDsdEnergy(work->x, work->y, work->z, 0x100, work->chargeTime, 0);
        work->visible = 1;
        work->timer = 0;
        work->state++;
        break;
    case 6:
        BgFxAddPosition(0, 0, work->vz);
        work->z += work->vz;

        if (ApplyAttackBox(0x104, work->x, work->y, work->z, 16, 16, 16) == 1) {
            m4aSongNumStart(SONG_BTL_RK_LIMITENTRY);
            BgFxSignalEnd(0);
            work->visible = 0;
            work->state = 7;
        }

        if (work->z >= -0x800) {
            BgFxSignalEnd(0);
            m4aSongNumStart(SONG_SND_703);
            work->visible = 0;
            work->state = 7;
        }

        work->timer++;
        break;
    case 7:
        if (work->dropCount >= (s8)work->dropTotal - 1) {
            if (BgFxIsActive() == 0) {
                BgAnimStop();
                FadeToOriginal(0, 8);
                work->state++;
            }

            return 1;
        }

        if (work->timer > 49) {
            work->timer = 0;
            work->dropCount++;
            work->state = 5;
        } else {
            work->timer++;
        }
        break;
    default:
        return 0;
    }

    if (work->dsd->state == 8 || work->dsd->state == 11) {
        if (BgFxIsActive() == 1) {
            BgAnimStop();
            FadeToOriginal(0, 8);
        }

        work->visible = 0;
        return 0;
    }

    return 1;
}

void task_bos_dsd_energy2_2(DsdEnergy2Work* work) {
    ObjAffine* affine;
    s32 scale;
    s32 flag;
    s16 x;
    s16 y;

    if (work->visible == 1) {
        if (work->z >= 0 && gBtlWork->scale == 0x100) {
            affine = 0;
        } else {
            scale = 0x200 - -work->z / 128;

            if (scale <= 0x7F) {
                scale = 0x80;
            }

            flag = 0;

            if (scale > 0x100) {
                flag = 1;
            }

            affine = AllocObjAffine(0, scale, scale, flag);
        }

        WorldToScreen(&x, &y, work->x + 0x100, work->y, 0);
        DrawSprite(x, y, work->gfx, work->dsd->tiles3, work->dsd->palette4, affine, 0xC00, 0xFFF0);
    }
}

void task_bos_dsd_energy2_3(void) {
}

const s8 gBosDsdCirclePaletteDurations[10] = { 6, 12, 10, 9, 7, 8, 9, 10, 0, 0 };

const s16 gBosDsdCircleOffsetsX[9] = { -97, -98, -98, -94, -92, -88, -82, 0, 0 };

const s16 gBosDsdCircleOffsetsY[10] = { 2, 2, 2, 0, 0, 0, -1, 0, 0, 0 };

TaskDesc gTaskDescBosDsdCircle = {
    "task_bos_dsd_circle",
    (TaskInitFunc)task_bos_dsd_circle_0,
    (TaskUpdateFunc)task_bos_dsd_circle_1,
    (TaskDrawFunc)task_bos_dsd_circle_2,
    (TaskDestroyFunc)task_bos_dsd_circle_3,
    sizeof(DsdCircleWork),
};

TaskDesc gTaskDescBosDsdEnergy1 = {
    "task_bos_dsd_energy1",
    (TaskInitFunc)task_bos_dsd_energy1_0,
    (TaskUpdateFunc)task_bos_dsd_energy1_1,
    (TaskDrawFunc)task_bos_dsd_energy1_2,
    (TaskDestroyFunc)task_bos_dsd_energy1_3,
    sizeof(DsdEnergy1Work),
};

TaskDesc gTaskDescBosDsdEnergy2 = {
    "task_bos_dsd_energy2",
    (TaskInitFunc)task_bos_dsd_energy2_0,
    (TaskUpdateFunc)task_bos_dsd_energy2_1,
    (TaskDrawFunc)task_bos_dsd_energy2_2,
    (TaskDestroyFunc)task_bos_dsd_energy2_3,
    sizeof(DsdEnergy2Work),
};
