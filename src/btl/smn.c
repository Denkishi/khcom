#include "task_descriptors.h"
#include "display.h"
#include "smn.h"
#include "frd.h"
#include "anim.h"
#include "smn_api.h"
#include "task_animation_assets.h"
#include "sprites_cloud.h"
#include "sprites_evt.h"
#include "sprites_smn.h"

const AnimDef gSmnCloudAnimDefs[8] = {
    { gCroud01Frames, gCroud01Anims, gCroud01Tiles, 0, { 0, 0, 0 } },
    { gCroud02Frames, gCroud02Anims, gCroud02Tiles, 0, { 0, 0, 0 } },
    { gCroud10Frames, gCroud10Anims, gCroud10Tiles, 0, { 0, 0, 0 } },
    { gCroud11Frames, gCroud11Anims, gCroud11Tiles, 0, { 0, 0, 0 } },
    { gCroud12Frames, gCroud12Anims, gCroud12Tiles, 0, { 0, 0, 0 } },
    { gCroud13Frames, gCroud13Anims, gCroud13Tiles, 0, { 0, 0, 0 } },
    { gCroud01Frames, gCroud01Anims, gCroud01Tiles, 1, { 0, 0, 0 } },
    { gCroud02Frames, gCroud02Anims, gCroud02Tiles, 1, { 0, 0, 0 } },
};

TaskDesc gTaskDescSmnCloud = {
    "task_smn_cloud",
    (TaskInitFunc)task_smn_cloud_0,
    (TaskUpdateFunc)task_smn_cloud_1,
    (TaskDrawFunc)task_smn_cloud_2,
    (TaskDestroyFunc)task_smn_cloud_3,
    sizeof(SmnCloudWork),
};

const AnimDef gSmnBambiAnimDef = { gBanb00Frames, gBanb00Anims, gBanb00Tiles, 0, { 0, 0, 0 } };

TaskDesc gTaskDescSmnBambi = {
    "task_smn_bambi",
    (TaskInitFunc)task_smn_bambi_0,
    (TaskUpdateFunc)task_smn_bambi_1,
    (TaskDrawFunc)task_smn_bambi_2,
    (TaskDestroyFunc)task_smn_bambi_3,
    sizeof(SmnBambiWork),
};

const AnimDef gSmnTinkAnimDefs[3] = {
    { gTinkF00Frames, gTinkF00Anims, gTinkF00Tiles, 1, { 0, 0, 0 } },
    { gTinkF00Frames, gTinkF00Anims, gTinkF00Tiles, 2, { 0, 0, 0 } },
    { gTinkF00Frames, gTinkF00Anims, gTinkF00Tiles, 3, { 0, 0, 0 } },
};

TaskDesc gTaskDescSmnTink = {
    "task_smn_tink",
    (TaskInitFunc)task_smn_tink_0,
    (TaskUpdateFunc)task_smn_tink_1,
    (TaskDrawFunc)task_smn_tink_2,
    (TaskDestroyFunc)task_smn_tink_3,
    sizeof(SmnTinkWork),
};

TaskDesc gTaskDescSmnTinkeff = {
    "task_smn_tinkeff",
    (TaskInitFunc)task_smn_tinkeff_0,
    (TaskUpdateFunc)task_smn_tinkeff_1,
    (TaskDrawFunc)task_smn_tinkeff_2,
    (TaskDestroyFunc)task_smn_tinkeff_3,
    sizeof(SmnTinkeffWork),
};

const AnimDef gSmnSimbaAnimDef = { gShinba10Frames, gShinba10Anims, gShinba10Tiles, 0, { 0, 0, 0 } };

TaskDesc gTaskDescSmnSimba = {
    "task_smn_simba",
    (TaskInitFunc)task_smn_simba_0,
    (TaskUpdateFunc)task_smn_simba_1,
    (TaskDrawFunc)task_smn_simba_2,
    (TaskDestroyFunc)task_smn_simba_3,
    sizeof(SmnSimbaWork),
};

const AnimDef gSmnMushuAnimDefs[4] = {
    { gMushu10Frames, gMushu10Anims, gMushu10Tiles, 0, { 0, 0, 0 } },
    { gMushu10Frames, gMushu10Anims, gMushu10Tiles, 1, { 0, 0, 0 } },
    { gMushu10Frames, gMushu10Anims, gMushu10Tiles, 2, { 0, 0, 0 } },
    { gMushu10Frames, gMushu10Anims, gMushu10Tiles, 3, { 0, 0, 0 } },
};

const AnimDef gUnk_0813EABC = { gMushu10Frames, gMushu10Anims, gMushu10Tiles, 4, { 0, 0, 0 } };

TaskDesc gTaskDescSmnMushu = {
    "task_smn_mushu",
    (TaskInitFunc)task_smn_mushu_0,
    (TaskUpdateFunc)task_smn_mushu_1,
    (TaskDrawFunc)task_smn_mushu_2,
    (TaskDestroyFunc)task_smn_mushu_3,
    sizeof(SmnMushuWork),
};

const AnimDef gSmnDumboAnimDefs[3] = {
    { gUnk_09EDE848, gUnk_09EDE86C, gUnk_088ABF88, 0, { 0, 0, 0 } },
    { gUnk_09EDE848, gUnk_09EDE86C, gUnk_088ABF88, 1, { 0, 0, 0 } },
    { gUnk_09EDE848, gUnk_09EDE86C, gUnk_088ABF88, 2, { 0, 0, 0 } },
};

TaskDesc gTaskDescSmnDumbo = {
    "task_smn_dumbo",
    (TaskInitFunc)task_smn_dumbo_0,
    (TaskUpdateFunc)task_smn_dumbo_1,
    (TaskDrawFunc)task_smn_dumbo_2,
    (TaskDestroyFunc)task_smn_dumbo_3,
    sizeof(SmnDumboWork),
};

const AnimDef gSmnGenieAnimDefs[2] = {
    { gGenie00Frames, gGenie00Anims, gGenie00Tiles, 0, { 0, 0, 0 } },
    { gGenie00Frames, gGenie00Anims, gGenie00Tiles, 1, { 0, 0, 0 } },
};

TaskDesc gTaskDescSmnGenie = {
    "task_smn_genie",
    (TaskInitFunc)task_smn_genie_0,
    (TaskUpdateFunc)task_smn_genie_1,
    (TaskDrawFunc)task_smn_genie_2,
    (TaskDestroyFunc)task_smn_genie_3,
    sizeof(SmnGenieWork),
};

const AnimDef gSmnKingAnimDefs[3] = {
    { gMickey10Frames, gMickey10Anims, gMickey10Tiles, 0, { 0, 0, 0 } },
    { gMickey10Frames, gMickey10Anims, gMickey10Tiles, 1, { 0, 0, 0 } },
    { gMickey10Frames, gMickey10Anims, gMickey10Tiles, 2, { 0, 0, 0 } },
};

void task_smn_cloud_0(SmnCloudWork* work, SmnArgs* args) {
    BtlObj* body;
    BtlObj* obj;

    body = &work->body;

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= 0x200000;
        obj = gBtlWork->actor;
        work->tiles = gBtlWork->tiles;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= 0x200000;
        obj = gRikuBtlWork->actor;
        work->tiles = gRikuBtlWork->tiles;
    }

    body->x = obj->originX;
    body->y = obj->originY;
    body->z = obj->originZ;
    body->groundZ = obj->originZ;

    if (obj->flags & 4) {
        body->flags = 4;
    } else {
        body->flags = 0;
    }

    work->variant = args->variant;
    work->palette = LoadObjPalette(gCroudPalette, 32);
    work->unk_15C = 0;
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(gSmnCloudAnimDefs, &work->anim, 0, 0, work->tiles);
    work->state = 0;
    work->stateTimer = 0;
    work->speed = 0;
    work->unk_158 = 0;
    work->scaleX = 10;
    work->scaleY = 10;
    work->animating = 0;
    work->unk_160 = 0;
    work->target = 0;
    work->attackCount = 0;
    work->targetIndex = 0;
    TaskPoolInit(&work->tasks, 2);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

u8 task_smn_cloud_1(SmnCloudWork* work) {
    BtlObj* body = &work->body;
    BtlWork* owner;
    s32 x;
    s32 dz;
    s32 targetZ;
    s32 pixelX;
    owner = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    if (owner->flags & 0x40000000) return 0;
    if (work->state == 4) BtlMapFollowPosition(body->x, body->y, body->z + 0x2000);
    else BtlMapFollowPosition(body->x, body->y, body->z);
    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            work->steps = 12;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_UP);
        }
        ApproachValue(&work->scaleX, 256, work->steps);
        work->scaleY = work->scaleX;
        if (work->steps <= 0) {
            work->stateTimer = 0;
            switch (work->variant) {
            case 0:
                work->state = 2;
                work->animating = 1;
                break;
            case 1:
                work->state = 1;
                work->animating = 1;
                break;
            case 2:
                work->state = 3;
                work->animating = 1;
                break;
            default:
                work->state = 6;
                break;
            }
        } else {
            work->stateTimer++;
            work->steps--;
        }
        break;
    case 5:
        if (work->stateTimer == 0) {
            work->steps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_DOWN);
        }
        ApproachValue(&work->scaleX, 25, work->steps);
        work->scaleY = work->scaleX;
        if (work->steps <= 0) return 0;
        work->stateTimer++;
        work->steps--;
        break;
    case 6:
        if (work->stateTimer == 0) work->steps = 8;
        ApproachValue(&work->scaleX, 10, work->steps);
        ApproachValue(&work->scaleY, 512, work->steps);
        if (--work->steps <= 0) {
            work->state = 7;
            work->stateTimer = 0;
            m4aSongNumStart(SONG_EF_TELEP);
        } else work->stateTimer++;
        break;
    case 7: {
        BtlObj* target;
        if (work->stateTimer == 0) {
            target = SmnCloudPickTeleportTarget(work);
            work->steps = 8;
            if (target != 0) {
                body->y = target->y;
                body->z = target->groundZ;
                body->groundZ = target->groundZ;
                if (target->flags & 4) {
                    body->x = target->x + 0x2000;
                    body->flags |= 4;
                } else {
                    body->x = target->x - 0x2000;
                    body->flags &= ~4ULL;
                }
            }
        }
        ApproachValue(&work->scaleX, 256, work->steps);
        ApproachValue(&work->scaleY, 256, work->steps);
        if (--work->steps <= 0) {
            work->animating = 1;
            work->state = 1;
            work->stateTimer = 0;
        } else work->stateTimer++;
        break;
    }
    case 1:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(gSmnCloudAnimDefs, &work->anim, 0, 0, work->tiles);
        } else if ((s16)work->unk_160 == 0 && AnimIsFinished(&work->anim)) {
            AnimChangeWithDef(gSmnCloudAnimDefs, &work->anim, 1, 0, work->tiles);
            work->unk_160++;
        } else if (AnimIsFinished(&work->anim)) {
            work->state = 5;
            work->stateTimer = 0;
            break;
        }
        if (work->anim.timer == 0) {
            if ((s16)work->unk_160 == 0) {
                switch (AnimGetFrame(&work->anim)) {
                case 2:
                    m4aSongNumStart(SONG_VO_KU_ATTACK00);
                    break;
                case 6:
                    if (body->flags & 4 ? ApplyAttackBox(151, body->x - 0x2800, body->y, body->z, 24, 24, 48) : ApplyAttackBox(151, body->x + 0x2800, body->y, body->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT00);
                        FadeStartIn(2, 20);
                        if (body->flags & 4) {
                            SetBattleZoom(6, 0x133, body->x - 0x2000, body->y - 0x1800 + body->z);
                        } else {
                            SetBattleZoom(6, 0x133, body->x + 0x2000, body->y - 0x1800 + body->z);
                        }
                    }
                    break;
                case 7:
                    SetBattleZoom(6, 256, gBtlWork->x2, gBtlWork->y2);
                    break;
                case 9:
                    m4aSongNumStart(SONG_VO_KU_ATTACK01);
                    break;
                }
            } else {
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    MakeOpponentsHittable();
                    if (body->flags & 4 ? ApplyAttackBox(151, body->x - 0x2800, body->y, body->z, 24, 24, 48) : ApplyAttackBox(151, body->x + 0x2800, body->y, body->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT01);
                        FadeStartIn(2, 20);
                        if (body->flags & 4) {
                            SetBattleZoom(6, 0x133, body->x - 0x2000, body->y - 0x1800 + body->z);
                        } else {
                            SetBattleZoom(6, 0x133, body->x + 0x2000, body->y - 0x1800 + body->z);
                        }
                    }
                    break;
                case 1:
                    SetBattleZoom(6, 256, gBtlWork->x2, gBtlWork->y2);
                    break;
                case 4:
                    m4aSongNumStart(SONG_VO_KU_ATTACK02);
                    break;
                case 5:
                    MakeOpponentsHittable();
                    if (body->flags & 4 ? ApplyAttackBox(151, body->x - 0x2800, body->y, body->z, 24, 24, 48) : ApplyAttackBox(151, body->x + 0x2800, body->y, body->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT02);
                        FadeStartIn(2, 50);
                        if (body->flags & 4) {
                            SetBattleZoom(6, 512, body->x - 0x2000, body->y - 0x1800 + body->z);
                        } else {
                            SetBattleZoom(6, 512, body->x + 0x2000, body->y - 0x1800 + body->z);
                        }
                    }
                    break;
                case 6:
                    SetBattleZoom(6, 256, gBtlWork->x2, gBtlWork->y2);
                    break;
                }
            }
        }
        work->stateTimer++;
        break;
    case 2:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(gSmnCloudAnimDefs, &work->anim, 6, 0, work->tiles);
        } else if ((s16)work->unk_160 == 0 && AnimIsFinished(&work->anim)) {
            AnimChangeWithDef(gSmnCloudAnimDefs, &work->anim, 7, 0, work->tiles);
            work->unk_160++;
        } else if (AnimIsFinished(&work->anim)) {
            work->state = 5;
            work->stateTimer = 0;
            break;
        }
        if (work->anim.timer == 0) {
            if ((s16)work->unk_160 == 0) {
                switch (AnimGetFrame(&work->anim)) {
                case 2:
                    m4aSongNumStart(SONG_VO_KU_ATTACK00);
                    break;
                case 6:
                    if (body->flags & 4 ? ApplyAttackBox(151, body->x - 0x2800, body->y, body->z, 24, 24, 48) : ApplyAttackBox(151, body->x + 0x2800, body->y, body->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT00);
                        FadeStartIn(2, 20);
                        if (body->flags & 4) {
                            SetBattleZoom(6, 0x133, body->x - 0x2000, body->y - 0x1800 + body->z);
                        } else {
                            SetBattleZoom(6, 0x133, body->x + 0x2000, body->y - 0x1800 + body->z);
                        }
                    }
                    break;
                case 7:
                    SetBattleZoom(6, 256, gBtlWork->x2, gBtlWork->y2);
                    break;
                case 9:
                    m4aSongNumStart(SONG_VO_KU_ATTACK01);
                    break;
                }
            } else {
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    MakeOpponentsHittable();
                    if (body->flags & 4 ? ApplyAttackBox(151, body->x - 0x2800, body->y, body->z, 24, 24, 48) : ApplyAttackBox(151, body->x + 0x2800, body->y, body->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT01);
                        FadeStartIn(2, 20);
                        if (body->flags & 4) {
                            SetBattleZoom(6, 0x133, body->x - 0x2000, body->y - 0x1800 + body->z);
                        } else {
                            SetBattleZoom(6, 0x133, body->x + 0x2000, body->y - 0x1800 + body->z);
                        }
                    }
                    break;
                case 1:
                    SetBattleZoom(6, 256, gBtlWork->x2, gBtlWork->y2);
                    break;
                }
            }
        }
        work->stateTimer++;
        break;
    case 3:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(gSmnCloudAnimDefs, &work->anim, 2, 1, work->tiles);
            work->speed = 0;
        }
        if (body->flags & 4) pixelX = gBtlWork->xMin + 50;
        else pixelX = gBtlWork->xMax - 50;
        x = pixelX * 256;
        targetZ = -0xC800;
        body->x += (x - body->x) >> 4;
        dz = (targetZ - body->z) >> 3;
        if (dz > work->speed) dz = work->speed;
        if (dz < -work->speed) dz = -work->speed;
        body->z += dz;
        work->speed += 128;
        if ((body->z - targetZ >= 0 ? body->z - targetZ : targetZ - body->z) < 0x1000) {
            work->state = 4;
            work->stateTimer = 0;
        } else work->stateTimer++;
        break;
    case 4: {
        BtlObj* target;
        if (work->stateTimer == 0) {
            target = SmnCloudNextTarget(work);
            work->target = target;
            if (target == 0) {
                work->state = 5;
                work->stateTimer = 0;
                break;
            }
            work->targetX = target->x;
            work->targetY = target->y;
            work->targetZ = target->z - 0x1000;
            MakeOpponentsHittable();
            switch ((s16)work->attackCount) {
            case 0:
                m4aSongNumStart(SONG_VO_KU_ATTACK00);
                AnimChangeWithDef(gSmnCloudAnimDefs, &work->anim, 3, 0, work->tiles);
                break;
            case 1:
                m4aSongNumStart(SONG_VO_KU_ATTACK01);
                AnimChangeWithDef(gSmnCloudAnimDefs, &work->anim, 4, 0, work->tiles);
                break;
            case 2:
            default:
                m4aSongNumStart(SONG_VO_KU_ATTACK02);
                AnimChangeWithDef(gSmnCloudAnimDefs, &work->anim, 5, 0, work->tiles);
                break;
            }
            if (body->x < work->targetX) body->flags &= ~4ULL;
            else body->flags |= 4;
        }
        body->x += (work->targetX - body->x) >> 3;
        body->y += (work->targetY - body->y) >> 3;
        body->z += (work->targetZ - body->z) >> 3;
        if (work->anim.timer == 0) {
            switch ((s16)work->attackCount) {
            case 0:
                if (AnimGetFrame(&work->anim) == 4) {
                    if (body->flags & 4 ? ApplyAttackBox(152, body->x - 0x1800, body->y, body->z, 40, 24, 48) : ApplyAttackBox(152, body->x + 0x1800, body->y, body->z, 40, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT00);
                        FadeStartIn(2, 20);
                    }
                }
                break;
            case 1:
                if (AnimGetFrame(&work->anim) == 3) {
                    MakeOpponentsHittable();
                    if (body->flags & 4 ? ApplyAttackBox(152, body->x - 0x1800, body->y, body->z, 40, 24, 48) : ApplyAttackBox(152, body->x + 0x1800, body->y, body->z, 40, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT01);
                        FadeStartIn(2, 20);
                    }
                }
                break;
            case 2:
            default:
                if (AnimGetFrame(&work->anim) == 3) {
                    MakeOpponentsHittable();
                    if (body->flags & 4 ? ApplyAttackBox(152, body->x - 0x1800, body->y, body->z, 40, 24, 48) : ApplyAttackBox(152, body->x + 0x1800, body->y, body->z, 40, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT02);
                        FadeStartIn(2, 20);
                    }
                }
                break;
            }
        }
        if (work->stateTimer > 23 && AnimIsFinished(&work->anim)) {
            work->stateTimer = 0;
            if ((s16)++work->attackCount > 2) work->state = 5;
            else work->state = 3;
        } else work->stateTimer++;
        break;
    }
    }
    body->groundZ = 0;
    ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);
    if (body->z > body->groundZ) body->z = body->groundZ;
    if (work->animating != 0) AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_smn_cloud_2(SmnCloudWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);
    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (work->scaleX == 256 && work->scaleY == work->scaleX) {
        if (body->flags & 4) {
            sclY = gBtlWork->scale;
            sclX = sclY;
        } else if (gBtlWork->scale == work->scaleY) {
            sclY = gBtlWork->scale;
            sclX = sclY;
            flags |= 1;
        } else {
            sclY = gBtlWork->scale;
            sclX = -sclY;
        }
    } else if (body->flags & 4) {
        sclX = gBtlWork->scale * work->scaleX >> 8;
        sclY = gBtlWork->scale * work->scaleY >> 8;
    } else {
        sclX = -(gBtlWork->scale * work->scaleX >> 8);
        sclY = gBtlWork->scale * work->scaleY >> 8;
    }

    if (sclY == 256 && sclX == sclY) {
        affine = 0;
    } else if (sclY <= 255) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_smn_cloud_3(SmnCloudWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= 0xFFFFFFFFFFDFFFFF;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

void SmnBambiPickHopTarget(SmnBambiWork* work) {
    work->targetX = work->body.x + gSineTable[work->angle] * 80;
    work->targetY = work->body.y + -gSineTable[work->angle + 0x40] * 40;
    work->angle += GetRandom() % 0x21 + 0x20;

    if (work->targetX - work->body.x > 0) {
        work->body.flags |= 4;
    } else {
        work->body.flags &= 0xFFFFFFFFFFFFFFFB;
    }
}

void task_smn_bambi_0(SmnBambiWork* work, SmnArgs* args) {
    BtlObj* body;
    BtlObj* obj;

    body = &work->body;

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= 0x200000;
        obj = gBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= 0x200000;
        obj = gRikuBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    }

    body->x = (gBtlWork->xMin
                    + GetRandom() % (gBtlWork->xMax - gBtlWork->xMin + 1)) << 8;
    body->y = (gBtlWork->yMin
                    + GetRandom() % (gBtlWork->yMax - gBtlWork->yMin + 1)) << 8;
    body->z = obj->originZ;
    body->groundZ = obj->originZ;

    if (obj->flags & 4) {
        body->flags = 0;
        work->angle = 0xC0;
    } else {
        body->flags = 4;
        work->angle = 0x40;
    }

    work->variant = args->variant;
    work->palette = LoadObjPalette(gBanbPalette, 32);
    work->vz = 0;
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(&gSmnBambiAnimDef, &work->anim, 0, 0, work->tiles);
    work->state = 0;
    work->stateTimer = 0;
    work->steps = 0;
    work->unk_14C = 0;
    work->unk_150 = 0;
    work->scale = 10;
    work->animating = 0;
    work->unk_160 = 0;
    work->target = 0;
    work->targetIndex = 0;
    m4aSongNumStart(SONG_VO_SR_SUMMON00);
    TaskPoolInit(&work->tasks, 2);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

u8 SmnBambiApplyGravity(SmnBambiWork* work) {
    BtlObj* body;

    body = &work->body;
    body->groundZ = 0;
    ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);
    body->z += work->vz;
    work->vz += 0x33;

    if (body->z > body->groundZ) {
        body->z = body->groundZ;
        work->vz = 0;
        return 1;
    }

    return 0;
}

BtlObj* SmnBambiNextTarget(SmnBambiWork* work) {
    BtlObj* list[10];
    BtlObj* p;
    s16 count;

    if (gBtlWork->flags & 0x4000) {
        if (work->mainSide != 0) {
            p = gRikuBtlWork->actor;
        } else {
            p = gBtlWork->actor;
        }

        if (p->hp <= 0) {
            return 0;
        }

        return p;
    }

    count = 0;
    p = ListPoolFirst(&gBtlWork->pool);

    while (p != 0) {
        if (!(p->flags & 0x01000000)) {
            list[count] = p;
            count++;
            if (count > 9) {
                break;
            }
        }
        p = ListPoolNext(&p->node);
    }

    if (count == 0) {
        return 0;
    }

    p = list[work->targetIndex % count];
    work->targetIndex++;
    return p;
}
u8 task_smn_bambi_1(SmnBambiWork* work) {
    BtlObj* body;
    BtlWork* obj;
    SmnPrizeArgs args;

    body = &work->body;
    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;

    if (obj->flags & 0x40000000) {
        return 0;
    }

    switch (work->state) {
    case 0:
        if (work->mainSide != 0) {
            BtlMapFollowPosition(body->x, body->y, body->z);
        }

        if (work->stateTimer == 0) {
            work->steps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_UP);
        }

        ApproachValue(&work->scale, 256, work->steps);

        if (work->steps > 0) {
            work->stateTimer++;
            work->steps--;
        } else {
            if (work->variant == 3) {
                work->state = 2;
            } else {
                work->state = 1;
            }

            work->stateTimer = 0;
            work->animating = 1;
        }
        break;
    case 3:
        if (work->stateTimer == 0) {
            work->steps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_DOWN);
        }

        do {
            ApproachValue(&work->scale, 25, work->steps);
        } while (0);

        if (work->steps <= 0) {
            return 0;
        }

        work->stateTimer++;
        work->steps--;
        break;
    case 2:
        if (work->stateTimer == 0) {
            AnimStart(&work->anim, 0, 0);
            work->vz = -0x480;
            m4aSongNumStart(SONG_BTL_BBI_JUMP);
            work->target = SmnBambiNextTarget(work);
            work->steps = 0;
        }

        if (work->vz > 0) {
            MakeOpponentsHittable();

            if (ApplyAttackBox(0x76, body->x, body->y, body->z - 0x400, 8, 8, 2) != 0) {
                BgFxStartFriendHit(body->x, body->y, body->z);
                AnimStart(&work->anim, 0, 0);
                work->vz = -0x400;
                m4aSongNumStart(SONG_BTL_BBI_JUMP);
                m4aSongNumStart(SONG_BTL_BANBIHIT);
                work->target = SmnBambiNextTarget(work);
                work->steps++;
            }
        }

        if (SmnBambiApplyGravity(work)) {
            AnimStart(&work->anim, 0, 0);
            work->vz = -0x480;
            m4aSongNumStart(SONG_BTL_BBI_JUMP);
            work->target = SmnBambiNextTarget(work);
            work->steps++;
        }

        if ((work->vz > 0 && work->steps > 7) || work->target == 0) {
            work->state = 3;
            work->stateTimer = 0;
        } else {
            if (body->x < work->target->x) {
                body->flags |= 4;
            } else {
                body->flags &= 0xFFFFFFFFFFFFFFFB;
            }

            body->x += (work->target->x - body->x) >> 4;
            body->y += (work->target->y - body->y) >> 4;
            ClampBattlePosition(&body->x, &body->y, -16, 0);
            work->stateTimer++;
        }
        break;
    case 1:
        if (work->unk_14C == 0) {
            AnimStart(&work->anim, 0, 0);
            SmnBambiPickHopTarget(work);
            work->steps = 30;
        }

        if (work->variant == 2) {
            ApplyAttackBox(0x75, body->x, body->y, body->z, 8, 8, 8);
        } else {
            ApplyAttackBox(0x74, body->x, body->y, body->z, 8, 8, 8);
        }

        if (work->unk_14C > 4) {
            if (work->unk_14C == 5) {
                work->vz = -0x300;
                m4aSongNumStart(SONG_BTL_BBI_JUMP);
            }

            if (work->steps > 0) {
                ApproachValueHalfSteps(&body->x, work->targetX, work->steps);
                ApproachValueHalfSteps(&body->y, work->targetY, work->steps);
                work->steps--;
            }
        }

        SmnBambiApplyGravity(work);
        ClampBattlePosition(&body->x, &body->y, -16, 0);

        if (AnimIsFinished(&work->anim)) {
            work->unk_14C = 0;
            work->stateTimer++;
            args.x = body->x;
            args.y = body->y;
            args.z = body->z;

            if (work->variant == 0) {
                args.kind = 1;
            } else {
                args.kind = 2;
            }

            args.noTimeout = 0;
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPrize, &args);
        } else {
            work->unk_14C++;
        }

        if (work->stateTimer > 4) {
            work->state = 3;
            work->stateTimer = 0;
        }
        break;
    }

    if (work->animating != 0) {
        AnimUpdate(&work->anim);
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_smn_bambi_2(SmnBambiWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);

    if (body->flags & 4) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (gBtlWork->scale == 256 && work->scale == gBtlWork->scale) {
        sclY = work->scale;
        sclX = sclY;
        flags |= 1;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    sclX = sclX * work->scale >> 8;
    sclY = sclY * work->scale >> 8;

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (sclX <= 256 && sclY <= 256) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_smn_bambi_3(SmnBambiWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= 0xFFFFFFFFFFDFFFFF;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

void task_smn_tink_0(SmnTinkWork* work, SmnArgs* args) {
    BtlObj* body;
    BtlObj* obj;
    s32 t;

    body = &work->body;

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= 0x200000;
        obj = gBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= 0x200000;
        obj = gRikuBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    }

    body->x = obj->originX;
    body->y = obj->originY;
    body->z = obj->originZ - 0x3000;
#ifdef VERSION_EU
    body->groundZ = 0;
#else
    body->groundZ = obj->originZ;
#endif

    if (obj->flags & 4) {
        body->flags = 0x80004;
    } else {
        body->flags = 0x80000;
    }

    work->variant = args->variant;
    work->palette = LoadObjPalette(gTinkPalette, 32);
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(gSmnTinkAnimDefs, &work->anim, 0, 1, work->tiles);
    work->state = 0;
    work->stateTimer = 0;
    work->steps = 0;
    work->scale = 10;
    work->animating = 0;
    work->unk_150 = 0;
    work->flyAngle = 0;
    work->frameCount = 0;

    if (work->mainSide != 0) {
        work->actor = gBtlWork->actor;
    } else {
        work->actor = gRikuBtlWork->actor;
    }

    m4aSongNumStart(SONG_VO_SR_SUMMON00);
    work->healHp = work->actor->hp << 8;

    switch (args->variant) {
    case 0:
        t = 0x4C;
        work->healFrames = 0xB4;
        break;
    case 1:
        t = 0x99;
        work->healFrames = 0x12C;
        break;
    case 2:
    default:
        t = 0x100;
        work->healFrames = 0x1A4;
        break;
    }

    if (work->actor->btl->hcEffect == 0x27) {
        t = 332 * t >> 8;
    }

    work->healTarget = work->actor->maxHp * t + work->healHp;

    if (work->healTarget > work->actor->maxHp << 8) {
        work->healTarget = work->actor->maxHp << 8;
    }

    TaskPoolInit(&work->tasks, 15);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

void SmnTinkSpawnSparkle(SmnTinkWork* work) {
    if (work->frameCount % 3 == 0) {
        TaskCreate(&work->tasks, &gTaskDescSmnTinkeff, &work->body);
    }
}
u8 task_smn_tink_1(SmnTinkWork* work) {
    BtlObj* body;
    BtlObj* p;
    s32 x;
    s32 y;
    s32 z;
    s32 d;
    s32 t;

    body = &work->body;
    if ((work->mainSide != 0 ? gBtlWork->flags : gRikuBtlWork->flags) & 0x40000000) {
        return 0;
    }

    if (work->healFrames <= 0) {
        if (work->state != 1) {
            work->state = 1;
            work->stateTimer = 0;
        }
    } else {
        ApproachValue(&work->healHp, work->healTarget, work->healFrames);
        work->actor->hp = work->healHp >> 8;
        work->healFrames--;
    }

    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            work->steps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_UP);
        }

        ApproachValue(&work->scale, 256, work->steps);

        if (work->steps <= 0) {
            work->state = 2;
            work->stateTimer = 0;
            work->animating = 1;
            m4aSongNumStart(SONG_EF_TINK_LOOP);
        } else {
            work->stateTimer++;
            work->steps--;
        }
        break;
    case 1:
        if (work->stateTimer == 0) {
            work->steps = 20;
            m4aSongNumStop(SONG_EF_TINK_LOOP);
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_DOWN);
        }

        ApproachValue(&work->scale, 25, work->steps);

        if (work->steps <= 0) {
            return 0;
        }

        work->stateTimer++;
        work->steps--;
        break;
    case 2:
        SmnTinkSpawnSparkle(work);

        if (work->stateTimer == 0) {
            AnimChangeWithDef(gSmnTinkAnimDefs, &work->anim, 0, 1, work->tiles);
            work->hoverZ = body->z;
            work->steps = 30;
        } else {
            body->z += (work->hoverZ + gSineTable[work->stateTimer & 0xFF] * 12
                             - body->z) >> 2;
        }

        if (work->actor->x < body->x) {
            body->flags |= 4;
        } else {
            body->flags &= 0xFFFFFFFFFFFFFFFB;
        }

        if (work->steps-- <= 0) {
            work->stateTimer = 0;
            work->state = 3;
        } else {
            work->stateTimer++;
        }
        break;
    case 3:
        SmnTinkSpawnSparkle(work);

        if (work->stateTimer == 0) {
            AnimChangeWithDef(gSmnTinkAnimDefs, &work->anim, 1, 1, work->tiles);
        }

        p = work->actor;
        x = p->x + gSineTable[((u16)work->stateTimer * 4) & 0xFF] * 32;
        y = p->y + gSineTable[(((u16)work->stateTimer * 4) & 0xFF) + 64] * -16;
        z = (p->z - 0x1E00) + gSineTable[(u16)work->stateTimer * 2 & 0xFF] * 16;

        if (x < body->x) {
            body->flags |= 4;
        } else {
            body->flags &= 0xFFFFFFFFFFFFFFFB;
        }

        d = (x - body->x) >> 3;

        if (d > 0x400) {
            d = 0x400;
        } else if (d < -0x400) {
            d = -0x400;
        }

        body->x += d;
        d = (y - body->y) >> 3;

        if (d > 0x200) {
            d = 0x200;
        } else if (d < -0x200) {
            d = -0x200;
        }

        body->y += d;
        body->z += (z - body->z) >> 3;
        t = work->stateTimer % 60;

        if (t == 0) {
            switch (GetRandom() % 3) {
            case 0:
                work->speed = 0x280;
                work->state = 4;
                work->stateTimer = t;
                break;
            case 1:
                work->state = 2;
                work->stateTimer = t;
                break;
            case 2:
            default:
                work->stateTimer++;
                break;
            }
        } else {
            work->stateTimer++;
        }
        break;
    case 4:
        SmnTinkSpawnSparkle(work);

        if (work->stateTimer == 0) {
            AnimChangeWithDef(gSmnTinkAnimDefs, &work->anim, 2, 0, work->tiles);

            if (body->flags & 4) {
                work->flyAngle = 0xC0;
            } else {
                work->flyAngle = 0x40;
            }
        }

        body->x += gSineTable[(u8)work->flyAngle] * work->speed >> 8;
        body->z += -gSineTable[(u8)work->flyAngle + 0x40] * work->speed >> 8;

        if (body->flags & 4) {
            work->flyAngle += 7;
        } else {
            work->flyAngle -= 7;
        }

        if (AnimIsFinished(&work->anim)) {
            AnimChangeWithDef(gSmnTinkAnimDefs, &work->anim, 1, 1, work->tiles);
            work->state = 3;
            work->stateTimer = 1;
        } else {
            work->stateTimer++;
        }
        break;
    }

    ClampBattlePosition(&body->x, &body->y, -16, 0);

    if (work->animating != 0) {
        AnimUpdate(&work->anim);
    }

    TaskPoolUpdate(&work->tasks);
    work->frameCount++;
    return 1;
}

void task_smn_tink_2(SmnTinkWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);

    if (body->flags & 4) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (gBtlWork->scale == 256 && work->scale == gBtlWork->scale) {
        sclY = work->scale;
        sclX = sclY;
        flags |= 1;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    sclX = sclX * work->scale >> 8;
    sclY = sclY * work->scale >> 8;

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (sclX <= 256 && sclY <= 256) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_smn_tink_3(SmnTinkWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= 0xFFFFFFFFFFDFFFFF;
    m4aSongNumStop(SONG_EF_TINK_LOOP);
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

static inline s32 GetTinkEffectOffset(void) {
    return ((u16)(GetRandom() % 9) << 8) - 0x400;
}

void task_smn_tinkeff_0(SmnTinkeffWork* work, BtlObj* args) {
    work->x = args->x + GetTinkEffectOffset();
    work->y = args->y + GetTinkEffectOffset();
    work->z = args->z;
    work->vz = (u16)(GetRandom() % 0xE8) + 0x4C;
    work->tiles = LoadObjTiles(gUnk_088A5D7A, 0x200);
    work->palette = LoadObjPalette(gBStatesPalette, 32);
    AnimInit(&work->anim, gUnk_09EDE7E4, gUnk_09EDE7B4);

    switch ((u16)(GetRandom() % 3)) {
    case 0:
        AnimStart(&work->anim, 0, 1);
        break;
    case 1:
        AnimStart(&work->anim, 1, 1);
        break;
    case 2:
        AnimStart(&work->anim, 2, 1);
        break;
    }
}

u8 task_smn_tinkeff_1(SmnTinkeffWork* work) {
    work->z += work->vz;

    if (AnimIsFinished(&work->anim)) {
        return 0;
    }

    AnimUpdate(&work->anim);
    return 1;
}

void task_smn_tinkeff_2(SmnTinkeffWork* work) {
    void* gfx;
    s16 sx;
    s16 sy;

    gfx = AnimGetGfx(&work->anim);
    WorldToScreen(&sx, &sy, work->x, work->y, work->z);
    DrawSprite(sx, sy, gfx, work->tiles, work->palette, 0, 0x800,
               -4100 - ((work->y >> 8) * 4));
}

void task_smn_tinkeff_3(SmnTinkeffWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_smn_simba_0(SmnSimbaWork* work, SmnArgs* args) {
    BtlObj* body;
    BtlObj* obj;

    body = &work->body;

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= 0x200000;
        obj = gBtlWork->actor;
        work->tiles = gBtlWork->tiles;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= 0x200000;
        obj = gRikuBtlWork->actor;
        work->tiles = gRikuBtlWork->tiles;
    }

    body->x = obj->originX;
    body->y = obj->originY;
    body->z = obj->originZ;
    body->groundZ = obj->originZ;

    if (obj->flags & 4) {
        body->flags = 0x20004;
    } else {
        body->flags = 0x20000;
    }

    work->variant = args->variant;
    work->palette = LoadObjPalette(gShinbaPalette, 32);
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(&gSmnSimbaAnimDef, &work->anim, 0, 0, work->tiles);
    work->state = 0;
    work->stateTimer = 0;
    work->steps = 0;
    work->unk_14C = 0;
    work->scale = 10;
    work->animating = 0;
    TaskPoolInit(&work->tasks, 2);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

u8 task_smn_simba_1(SmnSimbaWork* work) {
    BtlObj* body;
    BtlWork* obj;

    body = &work->body;
    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;

    if (obj->flags & 0x40000000) {
        do {
            return 0;
        } while (0);
    }

    BtlMapFollowPosition(body->x, body->y, body->z);

    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            work->steps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_UP);
        }

        ApproachValue(&work->scale, 256, work->steps);

        if (work->steps > 0) {
            work->stateTimer++;
            work->steps--;
        } else {
            work->state = 1;
            work->stateTimer = 0;
            work->animating = 1;
        }
        break;
    case 2:
        if (work->stateTimer == 0) {
            work->steps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_DOWN);
        }

        ApproachValue(&work->scale, 25, work->steps);

        if (work->steps <= 0) {
            return 0;
        }

        work->stateTimer++;
        work->steps--;
        break;
    case 1:
        switch (work->stateTimer) {
        case 0:
            if (body->flags & 4) {
                SetBattleZoom(30, 0x133, body->x - 0x1400,
                              body->y + body->z - 0x1400);
            } else {
                SetBattleZoom(30, 0x133, body->x + 0x1400,
                              body->y + body->z - 0x1400);
            }
            break;
        case 50:
            switch (work->variant) {
            case 0:
                m4aSongNumStart(SONG_BTL_SIMBA_ROA0);
                break;
            case 1:
                m4aSongNumStart(SONG_BTL_SIMBA_ROA1);
                break;
            case 2:
            default:
                m4aSongNumStart(SONG_BTL_SIMBA_ROA2);
                break;
            }

            BtlMapStartShake();
            FadeFromAmount(5, 8, 20);
            SetBattleZoom(30, 0xCC, 0x10000, 0x15E00);

            if (body->flags & 4) {
                BgFxStartShockwave(body->x - 0x1400, body->y + body->z - 0x1400, 1);
            } else {
                BgFxStartShockwave(body->x + 0x1400, body->y + body->z - 0x1400, 0);
            }

            switch (work->variant) {
            case 0:
                if (body->flags & 4) {
                    ApplyAttackBox(0x99, body->x - 0x8000, body->y, body->z,
                                  0x80, 0x100, 0x100);
                } else {
                    ApplyAttackBox(0x99, body->x + 0x8000, body->y, body->z,
                                  0x80, 0x100, 0x100);
                }
                break;
            case 1:
                if (body->flags & 4) {
                    ApplyAttackBox(0x9A, body->x - 0x8000, body->y, body->z,
                                  0x80, 0x100, 0x100);
                } else {
                    ApplyAttackBox(0x9A, body->x + 0x8000, body->y, body->z,
                                  0x80, 0x100, 0x100);
                }
                break;
            case 2:
            default:
                if (body->flags & 4) {
                    ApplyAttackBox(0x9B, body->x - 0x8000, body->y, body->z,
                                  0x80, 0x100, 0x100);
                } else {
                    ApplyAttackBox(0x9B, body->x + 0x8000, body->y, body->z,
                                  0x80, 0x100, 0x100);
                }
                break;
            }
            break;
        }

        if (AnimIsFinished(&work->anim)) {
            SetBattleZoom(8, 256, gBtlWork->x2, gBtlWork->y2);
            work->state = 2;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    }

    if (work->animating != 0) {
        AnimUpdate(&work->anim);
    }

    ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);

    if (body->z > body->groundZ) {
        body->z = body->groundZ;
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_smn_simba_2(SmnSimbaWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);

    if (body->flags & 4) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (gBtlWork->scale == 256 && work->scale == gBtlWork->scale) {
        sclY = work->scale;
        sclX = sclY;
        flags |= 1;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    sclX = sclX * work->scale >> 8;
    sclY = sclY * work->scale >> 8;

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (sclX <= 256 && sclY <= 256) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_smn_simba_3(SmnSimbaWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= 0xFFFFFFFFFFDFFFFF;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

void task_smn_mushu_0(SmnMushuWork* work, SmnArgs* args) {
    BtlObj* body;
    BtlObj* obj;

    body = &work->body;

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= 0x200000;
        obj = gBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= 0x200000;
        obj = gRikuBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    }

    body->x = obj->x;
    body->y = obj->y;
    body->z = obj->z - 0x2200;
    body->groundZ = obj->groundZ;

    if (obj->flags & 4) {
        body->flags = 4;
    } else {
        body->flags = 0;
    }

    work->variant = args->variant;
    work->palette = LoadObjPalette(gMushuPalette, 32);
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(gSmnMushuAnimDefs, &work->anim, 0, 1, work->tiles);
    work->state = 0;
    work->stateTimer = 0;
    work->unk_14A = 0;
    work->scale = 10;
    work->animating = 0;
    work->unk_150 = 0;

    if (work->mainSide != 0) {
        work->actor = gBtlWork->actor;
    } else {
        work->actor = gRikuBtlWork->actor;
    }

    m4aSongNumStart(SONG_VO_SR_SUMMON00);
    TaskPoolInit(&work->tasks, 3);
}

u8 task_smn_mushu_1(SmnMushuWork* work) {
    BtlObj* body;
    BtlWork* obj;
    s32 px;
    s32 py;
    s32 pz;
    s32 x;
    s32 y;
    s32 z;
    s32 n;
    u16 v1;
    u16 v2;

    body = &work->body;
    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;

    if (obj->flags & 0x40000000) {
        return 0;
    }

    px = body->x;
    py = body->y;
    pz = body->z;
    body->x = work->actor->x;
    body->y = work->actor->y;
    body->z = work->actor->z - 0x2200;

    if (work->actor->flags & 4) {
        body->flags |= 4;
    } else {
        body->flags &= 0xFFFFFFFFFFFFFFFB;
    }

    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            work->unk_14A = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_UP);
        }

        ApproachValue(&work->scale, 256, work->unk_14A);

        if (work->unk_14A > 0) {
            work->stateTimer++;
            work->unk_14A--;
        } else {
            work->state = 3;
            work->stateTimer = 0;
            work->animating = 1;
        }
        break;
    case 1:
        if (work->stateTimer == 0) {
            work->unk_14A = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_DOWN);
        }

        ApproachValue(&work->scale, 25, work->unk_14A);

        if (work->unk_14A <= 0) {
            return 0;
        }

        work->stateTimer++;
        work->unk_14A--;
        break;
    case 3:
        AnimChangeWithDef(gSmnMushuAnimDefs, &work->anim, 2, 0, work->tiles);

        if (AnimIsFinished(&work->anim)) {
            work->state = 2;
            work->stateTimer = 0;
        }
        break;
    case 2:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(gSmnMushuAnimDefs, &work->anim, 3, 1, work->tiles);

            switch (work->variant) {
            case 0:
                work->unk_14A = 0x78;
                break;
            case 1:
                work->unk_14A = 0xF0;
                break;
            case 2:
            default:
                work->unk_14A = 0x1E0;
                break;
            }
        }

        if (AnimGetGfxIndex(&work->anim) == 5 && work->anim.timer == 0) {
            if (body->flags & 4) {
                x = body->x - 0xC800;
            } else {
                x = body->x + 0xC800;
            }

            y = body->y;
            z = 0;

            switch (work->variant) {
            case 0:
                n = 0x9D;
                break;
            case 1:
                n = 0x9E;
                break;
            case 2:
            default:
                n = 0x9F;
                break;
            }

            MakeOpponentsHittable();
            m4aSongNumStart(SONG_EF_MU_FIRE);

            if (body->flags & 4) {
                BgFxStartFire(0, body->x - 0x3800, body->y, body->z - 0x800,
                              x, y, z, 1, n);
            } else {
                BgFxStartFire(0, body->x + 0x3800, body->y, body->z - 0x800,
                              x, y, z, 0, n);
            }
        }

        BgAnimGetFrameState(&v1, &v2);

        if (v1 <= 3) {
            BgFxAddPosition(body->x - px, body->y - py, body->z - pz);
        }

        if (work->stateTimer > work->unk_14A) {
            work->state = 1;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    }

    if (work->animating != 0) {
        AnimUpdate(&work->anim);
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_smn_mushu_2(SmnMushuWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);

    if (body->flags & 4) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (gBtlWork->scale == 256 && work->scale == gBtlWork->scale) {
        sclY = work->scale;
        sclX = sclY;
        flags |= 1;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    sclX = sclX * work->scale >> 8;
    sclY = sclY * work->scale >> 8;

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (sclX <= 256 && sclY <= 256) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4101 - ((body->y >> 8) * 4));
    TaskPoolDraw(&work->tasks);
}

void task_smn_mushu_3(SmnMushuWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= 0xFFFFFFFFFFDFFFFF;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

void task_smn_dumbo_0(SmnDumboWork* work, SmnArgs* args) {
    BtlObj* body;
    BtlObj* obj;

    body = &work->body;

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= 0x200000;
        obj = gBtlWork->actor;
        work->tiles = gBtlWork->tiles;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= 0x200000;
        obj = gRikuBtlWork->actor;
        work->tiles = gRikuBtlWork->tiles;
    }

    body->x = obj->originX;
    body->y = obj->originY;
    body->z = obj->originZ;
    body->groundZ = obj->originZ;

    if (obj->flags & 4) {
        body->flags = 0x20004;
    } else {
        body->flags = 0x20000;
    }

    work->variant = args->variant;
    work->palette = LoadObjPalette(gDamboPalette, 32);
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(gSmnDumboAnimDefs, &work->anim, 0, 0, work->tiles);
    work->state = 0;
    work->stateTimer = 0;
    work->steps = 0;
    work->unk_14C = 0;
    work->scale = 10;
    work->animating = 0;
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

u8 task_smn_dumbo_1(SmnDumboWork* work) {
    BtlObj* body;
    BtlWork* obj;

    body = &work->body;
    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;

    if (obj->flags & 0x40000000) {
        return 0;
    }

    BtlMapFollowPosition(body->x, body->y, body->z);

    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            work->steps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_UP);
        }

        ApproachValue(&work->scale, 256, work->steps);

        if (work->steps > 0) {
            work->stateTimer++;
            work->steps--;
        } else {
            work->state = 2;
            work->stateTimer = 0;
            work->animating = 1;
        }
        break;
    case 1:
        if (work->stateTimer == 0) {
            work->steps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_DOWN);
        }

        ApproachValue(&work->scale, 25, work->steps);

        if (work->steps <= 0) {
            return 0;
        }

        work->stateTimer++;
        work->steps--;
        break;
    case 2:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(gSmnDumboAnimDefs, &work->anim, 0, 0, work->tiles);
        }

        if (AnimIsFinished(&work->anim)) {
            work->state = 3;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 3:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(gSmnDumboAnimDefs, &work->anim, 1, 1, work->tiles);

            if (body->flags & 4) {
                BgFxStartDumboSplash(work->variant, body->x - 0x1C00, body->y,
                              body->z - 0x1B00, 0, 0x9C);
            } else {
                BgFxStartDumboSplash(work->variant, body->x + 0x1C00, body->y,
                              body->z - 0x1B00, 1, 0x9C);
            }

            m4aSongNumStart(SONG_EF_DAMBO_SPLOOP);
        } else if (BgFxIsActive() == 0) {
            m4aSongNumStop(SONG_EF_DAMBO_SPLOOP);
            work->state = 4;
            work->stateTimer = 0;
            break;
        }

        work->stateTimer++;
        break;
    case 4:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(gSmnDumboAnimDefs, &work->anim, 2, 0, work->tiles);
        }

        if (AnimIsFinished(&work->anim)) {
            work->state = 1;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    }

    if (work->animating != 0) {
        AnimUpdate(&work->anim);
    }

    ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);

    if (body->z > body->groundZ) {
        body->z = body->groundZ;
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_smn_dumbo_2(SmnDumboWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);

    if (body->flags & 4) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (gBtlWork->scale == 256 && work->scale == gBtlWork->scale) {
        sclY = work->scale;
        sclX = sclY;
        flags |= 1;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    sclX = sclX * work->scale >> 8;
    sclY = sclY * work->scale >> 8;

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (sclX <= 256 && sclY <= 256) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_smn_dumbo_3(SmnDumboWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= 0xFFFFFFFFFFDFFFFF;
    m4aSongNumStop(SONG_EF_DAMBO_SPLOOP);
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

void task_smn_genie_0(SmnGenieWork* work, SmnArgs* args) {
    BtlObj* body;
    BtlObj* obj;

    body = &work->body;

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= 0x200000;
        obj = gBtlWork->actor;
        work->tiles = gBtlWork->tiles;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= 0x200000;
        obj = gRikuBtlWork->actor;
        work->tiles = gRikuBtlWork->tiles;
    }

    if (obj->flags & 4) {
        body->flags = 0x20004;
        body->x = obj->originX + 0x3700;
    } else {
        body->flags = 0x20000;
        body->x = obj->originX - 0x3700;
    }

    body->y = obj->originY;
    body->z = obj->originZ - 0x2800;
    body->groundZ = obj->originZ;
    work->variant = args->variant;
    work->palette = LoadObjPalette(gGeniePalette, 32);
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(gSmnGenieAnimDefs, &work->anim, 0, 0, work->tiles);
    work->state = 0;
    work->stateTimer = 0;
    work->steps = 0;
    work->scale = 10;
    work->animating = 0;
    work->speedX = 0;
    work->speedY = 0;

    switch (args->variant) {
    case 0:
        work->attacksLeft = 1;
        break;
    case 1:
        work->attacksLeft = 2;
        break;
    case 2:
    default:
        work->attacksLeft = 3;
        break;
    }

    work->targetIndex = 0;
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

BtlObj* SmnGenieNextTarget(SmnGenieWork* work) {
    BtlObj* list[10];
    BtlObj* p;
    s16 count;

    if (gBtlWork->flags & 0x4000) {
        if (work->mainSide != 0) {
            p = gRikuBtlWork->actor;
        } else {
            p = gBtlWork->actor;
        }

        if (p->hp <= 0) {
            return 0;
        }

        return p;
    }

    count = 0;
    p = ListPoolFirst(&gBtlWork->pool);

    while (p != 0) {
        if (!(p->flags & 0x01000000)) {
            list[count] = p;
            count++;
            if (count > 9) {
                break;
            }
        }
        p = ListPoolNext(&p->node);
    }

    if (count == 0) {
        return 0;
    }

    p = list[work->targetIndex % count];
    work->targetIndex++;
    return p;
}

void SmnGenieFollowTarget(SmnGenieWork* work) {
    BtlObj* body;
    BtlObj* obj;
    s32 tx;
    s32 ty;
    s32 zt;
    s32 v;
    s32 lim;

    obj = work->target;
    body = &work->body;

    if (obj == 0) {
        return;
    }

    if (obj->x < body->x) {
        body->flags |= 4;
    } else {
        body->flags &= 0xFFFFFFFFFFFFFFFB;
    }

    if (obj->x > 0x10000) {
        tx = obj->x - 0x3700;
    } else {
        tx = obj->x + 0x3700;
    }

    ty = obj->y;
    zt = body->groundZ - 0x200;
    v = (tx - body->x) >> 3;
    lim = work->speedX;

    if (v > lim) {
        v = lim;
        work->speedX = lim + 0x4C;
    } else if (v < -lim) {
        v = -lim;
        work->speedX = lim + 0x4C;
    } else {
        work->speedX = abs(v);
    }

    body->x += v;
    v = (ty - body->y) >> 3;
    lim = work->speedY;

    if (v > lim) {
        v = lim;
        work->speedY = lim + 0x4C;
    } else if (v < -lim) {
        v = -lim;
        work->speedY = lim + 0x4C;
    } else {
        work->speedY = abs(v);
    }

    body->y += v;
    body->z += (zt - gSineTable[(work->stateTimer * 2) & 0xFF] * 8 - body->z) >> 3;
}
u8 task_smn_genie_1(SmnGenieWork* work) {
    BtlObj* body = &work->body;
    s32 height;
    s32 x;
    s32 y;
    s32 z;
    if ((work->mainSide != 0 ? gBtlWork->flags : gRikuBtlWork->flags) & 0x40000000) {
        return 0;
    }
    BtlMapFollowPosition(body->x, body->y, body->z);
    if (gBtlWork->boundsCallback != 0) {
        gBtlWork->boundsCallback(&body->x, &body->y, &body->z, &body->groundZ);
        if (body->z > body->groundZ) {
            body->z = body->groundZ;
        }
    }
    switch (work->state) {
    case 0:
        if ((s16)work->stateTimer == 0) {
            work->steps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_UP);
        }
        ApproachValue(&work->scale, 256, work->steps);
        if (work->steps <= 0) {
            work->state = 2;
            work->stateTimer = 0;
            work->animating = 1;
        } else {
            work->stateTimer++;
            work->steps--;
        }
        break;
    case 1:
        if ((s16)work->stateTimer == 0) {
            AnimChangeWithDef(gSmnGenieAnimDefs, &work->anim, 0, 0, work->tiles);
            work->steps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_DOWN);
        }
        ApproachValue(&work->scale, 25, work->steps);
        if (work->steps <= 0) {
            return 0;
        }
        work->stateTimer++;
        work->steps--;
        break;
    case 2:
        if ((s16)work->stateTimer == 0) {
            gBtlWork->flags |= 0x40000;
            AnimChangeWithDef(gSmnGenieAnimDefs, &work->anim, 0, 0, work->tiles);
        }
        height = ((u32)gSineTable[(work->stateTimer * 2) & 255] << 3) + 0xC00;
        body->z += (body->groundZ - height - body->z) >> 3;
        if ((s16)work->stateTimer > 10) {
            work->target = SmnGenieNextTarget(work);
            if (work->target == 0 || (s16)work->attacksLeft-- <= 0) {
                work->state = 1;
                work->stateTimer = 0;
            } else {
                work->state = 3;
                work->stateTimer = 0;
            }
        } else {
            work->stateTimer++;
        }
        break;
    case 3:
        AnimChangeWithDef(gSmnGenieAnimDefs, &work->anim, 0, 0, work->tiles);
        SmnGenieFollowTarget(work);
        if ((s16)work->stateTimer > 40) {
            work->fired = 0;
            switch ((u16)(GetRandom() % 3)) {
            case 0:
                work->state = 4;
                break;
            case 1:
                work->state = 5;
                break;
            case 2:
            default:
                work->state = 6;
                break;
            }
            gBtlWork->flags &= ~0x40000ULL;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 4:
        if ((s16)work->stateTimer == 0) {
            m4aSongNumStart(SONG_VO_GE_ATTACK00);
            AnimChangeWithDef(gSmnGenieAnimDefs, &work->anim, 1, 0, work->tiles);
        }
        if (work->fired == 0) {
            SmnGenieFollowTarget(work);
            if (AnimGetFrame(&work->anim) == 6 && work->anim.timer == 0) {
                if (work->target != 0) {
                    x = work->target->x;
                    y = work->target->y;
                    z = 0;
                } else {
                    if (body->flags & 4) {
                        x = body->x - 0x5000;
                    } else {
                        x = body->x + 0x5000;
                    }
                    y = body->y;
                    z = 0;
                }
                if (body->flags & 4) {
                    BgFxStartThunder(1, body->x - 0xD00, body->y, body->z - 0x6E00, x, y, z, 146);
                } else {
                    BgFxStartThunder(1, body->x + 0xD00, body->y, body->z - 0x6E00, x, y, z, 146);
                }
                work->fired = 1;
            }
        } else {
            BgAnimIsStopped();
        }
        if (work->fired != 0 && !BgFxIsActive()) {
            work->state = 2;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 5:
        if ((s16)work->stateTimer == 0) {
            m4aSongNumStart(SONG_VO_GE_ATTACK01);
            AnimChangeWithDef(gSmnGenieAnimDefs, &work->anim, 1, 0, work->tiles);
        }
        if (work->fired == 0) {
            SmnGenieFollowTarget(work);
            if (AnimGetFrame(&work->anim) == 6 && work->anim.timer == 0) {
                if (work->target != 0) {
                    x = work->target->x;
                    y = work->target->y;
                    z = 0;
                } else {
                    if (body->flags & 4) {
                        x = body->x - 0x5000;
                    } else {
                        x = body->x + 0x5000;
                    }
                    y = body->y;
                    z = 0;
                }
                if (body->flags & 4) {
                    BgFxStartGravity(1, body->x - 0xD00, body->y, body->z - 0x6E00, x, y, z, 1, 148);
                } else {
                    BgFxStartGravity(1, body->x + 0xD00, body->y, body->z - 0x6E00, x, y, z, 0, 148);
                }
                work->fired = 1;
                FadeStartOut(6, 8);
            }
        } else {
            BgAnimIsStopped();
        }
        if (work->fired != 0 && !BgFxIsActive()) {
            FadeStartIn(6, 8);
            work->state = 2;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 6:
        if ((s16)work->stateTimer == 0) {
            AnimChangeWithDef(gSmnGenieAnimDefs, &work->anim, 1, 0, work->tiles);
            m4aSongNumStart(SONG_VO_GE_ATTACK02);
        }
        if (work->fired == 0) {
            SmnGenieFollowTarget(work);
            if (AnimIsFinished(&work->anim)) {
                if (work->target != 0) {
                    x = work->target->x;
                    y = work->target->y;
                    z = work->target->z - work->target->centerHeight * 256;
                } else {
                    if (body->flags & 4) {
                        x = body->x - 0x5000;
                    } else {
                        x = body->x + 0x5000;
                    }
                    y = body->y;
                    z = -0x1000;
                }
                BgFxStartStop(1, x, y, z, 147);
                work->fired = 1;
            }
        }
        if (work->fired != 0 && !BgFxIsActive()) {
            work->state = 2;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    }
    ClampBattlePosition(&body->x, &body->y, 0, -10);
    if (work->animating != 0) {
        AnimUpdate(&work->anim);
    }
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_smn_genie_2(SmnGenieWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);

    if (body->flags & 4) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (gBtlWork->scale == 256 && work->scale == gBtlWork->scale) {
        sclY = work->scale;
        sclX = sclY;
        flags |= 1;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    sclX = sclX * work->scale >> 8;
    sclY = sclY * work->scale >> 8;

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (sclX <= 256 && sclY <= 256) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_smn_genie_3(SmnGenieWork* work) {
    gBtlWork->flags |= 0x40000;

    if (work->mainSide != 0) {
        gBtlWork->flags &= 0xFFFFFFFFFFDFFFFF;
    } else {
        gRikuBtlWork->flags &= 0xFFFFFFFFFFDFFFFF;
    }

    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

void task_smn_king_0(SmnKingWork* work, SmnArgs* args) {
    BtlObj* body;
    BtlObj* obj;

    body = &work->body;

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= 0x200000;
        obj = gBtlWork->actor;
        work->tiles = gBtlWork->tiles;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= 0x200000;
        obj = gRikuBtlWork->actor;
        work->tiles = gRikuBtlWork->tiles;
    }

    body->x = obj->originX;
    body->y = obj->originY;
    body->z = obj->originZ - 0x4000;
    body->groundZ = 0;
    body->flags = obj->flags & 4;
    work->variant = args->variant;
    work->palette = LoadObjPalette(gMickeyPalette, 32);
    work->vz = 0;
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(gSmnKingAnimDefs, &work->anim, 0, 0, work->tiles);
    work->state = 0;
    work->stateTimer = 0;
    work->steps = 0;
    work->unk_14C = 0;
    work->scale = 10;
    work->animating = 0;
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

u8 SmnKingApplyGravity(SmnKingWork* work) {
    BtlObj* body;

    body = &work->body;
    ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);
    body->z += work->vz;
    work->vz += 0x33;

    if (body->z > body->groundZ) {
        body->z = body->groundZ;
        work->vz = 0;
        return 1;
    }

    return 0;
}

u8 task_smn_king_1(SmnKingWork* work) {
    BtlObj* body = &work->body;
    BtlWork* obj;
    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    if (obj->flags & 0x40000000) {
        return 0;
    }
    BtlMapFollowPosition(body->x, body->y, body->z);
    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            work->steps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_UP);
        }
        ApproachValue(&work->scale, 256, work->steps);
        if (work->steps <= 0) {
            work->state = 2;
            work->stateTimer = 0;
            work->animating = 1;
        } else {
            work->stateTimer++;
            work->steps--;
        }
        break;
    case 1:
        if (work->stateTimer == 0) {
            work->steps = 30;
            BgFxStartSummon(body->x, body->y, body->z);
            m4aSongNumStart(SONG_EF_SUMMON_DOWN);
        }
        ApproachValue(&work->scale, 25, work->steps);
        if (work->steps <= 0) {
            return 0;
        }
        work->stateTimer++;
        work->steps--;
        break;
    case 2:
        AnimChangeWithDef(gSmnKingAnimDefs, &work->anim, 1, 0, work->tiles);
        if (SmnKingApplyGravity(work)) {
            work->state = 4;
            work->stateTimer = 0;
            FadeToAmount(0, gBtlWork->fadeAmount, 8);
        }
        break;
    case 4:
        AnimChangeWithDef(gSmnKingAnimDefs, &work->anim, 2, 0, work->tiles);
        if (AnimGetFrame(&work->anim) == 5 && work->anim.timer == 3) {
            BgFxStartFlash(body->x, body->y, body->z - 0x1300);
            ApplyAttackBox(3, body->x, body->y, body->z, 256, 256, 256);
            m4aSongNumStart(SONG_EF_TLIMIT01);
            switch (work->variant) {
            case 0:
                gBtlWork->actor->hp += gBtlWork->actor->maxHp / 5;
                func_08076284();
                break;
            case 1:
                gBtlWork->actor->hp += gBtlWork->actor->maxHp / 2;
                func_08076290();
                break;
            case 2:
            default:
                gBtlWork->actor->hp += gBtlWork->actor->maxHp;
                func_0807629C();
                break;
            }
            CreateBtlPopTask(gBtlWork->actor, 10);
            if (gBtlWork->actor->hp > gBtlWork->actor->maxHp) {
                gBtlWork->actor->hp = gBtlWork->actor->maxHp;
            }
        }
        ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);
        if (AnimIsFinished(&work->anim)) {
            work->state = 5;
            work->stateTimer = 0;
        }
        break;
    case 5:
        ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);
        if (work->stateTimer > 60) {
            FadeToOriginal(0, 8);
            work->state = 1;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    }
    if (body->z > body->groundZ) {
        body->z = body->groundZ;
    }
    if (work->animating != 0) {
        AnimUpdate(&work->anim);
    }
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_smn_king_2(SmnKingWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);

    if (body->flags & 4) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (gBtlWork->scale == 256 && work->scale == gBtlWork->scale) {
        sclY = work->scale;
        sclX = sclY;
        flags |= 1;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    sclX = sclX * work->scale >> 8;
    sclY = sclY * work->scale >> 8;

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (sclX <= 256 && sclY <= 256) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_smn_king_3(SmnKingWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= 0xFFFFFFFFFFDFFFFF;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

u8 FrdDonaldApplyGravity(FrdDonaldWork* work) {
    BtlObj* body;

    body = &work->body;
    ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);
    body->z += work->vz;
    work->vz += 0x33;

    if (body->z > body->groundZ) {
        body->z = body->groundZ;
        work->vz = 0;
        return 1;
    }

    return 0;
}

void UpdateDonaldFlame(BtlObj* body, u8 a, s16 b, s16 c) {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
    s32 t;
    s16 p;
    s16 q;
    s16 r;

    y = body->y;
    z = body->z - (c * 256);
    w = 0x180;

    if (body->flags & 4) {
        x = body->x + (b * 256);
        t = -0x180;
    } else {
        x = body->x - (b * 256);
        t = w;
    }

    BgFxSetPosition(x, y, z);
    BgFxSetScale(t, w);

    if (a != 0) {
        if (gBtlWork->battleId == 0x98) {
            p = 0x20;
            q = 0x20;
            r = 0x30;
        } else {
            p = 0x0A;
            q = 0x0A;
            r = 0x0A;
        }

        if (ApplyAttackBox(0x84, x, y, z, p, q, r) != 0) {
            m4aSongNumStart(SONG_EF_FIRE01);
        }
    }
}

TaskDesc gTaskDescSmnKing = {
    "task_smn_king",
    (TaskInitFunc)task_smn_king_0,
    (TaskUpdateFunc)task_smn_king_1,
    (TaskDrawFunc)task_smn_king_2,
    (TaskDestroyFunc)task_smn_king_3,
    sizeof(SmnKingWork),
};
