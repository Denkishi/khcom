#include "task_descriptors.h"
#include "smn.h"
#include "anim.h"
#include "sprites_cloud.h"
#include "btl_api.h"
#include "fade.h"
#include "songs.h"
#include "smn_cloud_api.h"
#include "smn_tasks.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "engine_math.h"
#include "listpool.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

static const AnimDef sSmnCloudAnimDefs[8] = {
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

BtlObj* SmnCloudNextTarget(SmnCloudWork* work) {
    BtlObj* list[10];
    BtlObj* p;
    s16 count;

    if (gBtlWork->flags & BTL_FLAG_VS_BATTLE) {
        if (work->mainSide != 0) {
            p = gRikuBtlWork->actor;
        } else {
            p = gBtlWork->actor;
        }

        if (p->hp <= 0) {
            return NULL;
        }

        return p;
    }

    count = 0;
    p = ListPoolFirst(&gBtlWork->pool);

    while (p != NULL) {
        if (!(p->flags & BTLOBJ_FLAG_UNHITTABLE)) {
            list[count] = p;
            count++;

            if (count > 9) {
                break;
            }
        }

        p = ListPoolNext(&p->node);
    }

    if (count == 0) {
        return NULL;
    }

    p = list[work->targetIndex % count];
    work->targetIndex++;
    return p;
}

BtlObj* SmnCloudPickTeleportTarget(SmnCloudWork* work) {
    BtlObj* list[10];
    BtlObj* p;
    s16 count;
    s32 d;

    if (gBtlWork->flags & BTL_FLAG_VS_BATTLE) {
        if (work->mainSide != 0) {
            p = gRikuBtlWork->actor;
        } else {
            p = gBtlWork->actor;
        }

        if (p->hp <= 0) {
            return NULL;
        }

        return p;
    }

    count = 0;
    p = ListPoolFirst(&gBtlWork->pool);

    while (p != NULL) {
        if (!(p->flags & BTLOBJ_FLAG_UNHITTABLE)) {
            d = work->body.z - p->z;

            if (d >= 0 ? d <= 0x3000 : p->z - work->body.z <= 0x3000) {
                list[count] = p;
                count++;

                if (count > 9) {
                    break;
                }
            }
        }

        p = ListPoolNext(&p->node);
    }

    if (count == 0) {
        return NULL;
    }

    p = list[GetRandom() % count];
    return p;
}

void task_smn_cloud_0(SmnCloudWork* work, SmnArgs* args) {
    BtlObj* body;
    BtlObj* obj;

    body = &work->body;

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= BTL_FLAG_SUMMON_ACTIVE;
        obj = gBtlWork->actor;
        work->tiles = gBtlWork->tiles;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= BTL_FLAG_SUMMON_ACTIVE;
        obj = gRikuBtlWork->actor;
        work->tiles = gRikuBtlWork->tiles;
    }

    body->x = obj->originX;
    body->y = obj->originY;
    body->z = obj->originZ;
    body->groundZ = obj->originZ;

    if (obj->flags & BTLOBJ_FLAG_FACING_LEFT) {
        body->flags = BTLOBJ_FLAG_FACING_LEFT;
    } else {
        body->flags = 0;
    }

    work->variant = args->variant;
    work->palette = LoadObjPalette(gCroudPalette, 32);
    work->unk_15C = 0;
    AnimInit(&work->anim, NULL, NULL);
    AnimChangeWithDef(sSmnCloudAnimDefs, &work->anim, 0, 0, work->tiles);
    work->state = 0;
    work->stateTimer = 0;
    work->speed = 0;
    work->unk_158 = 0;
    work->scaleX = 10;
    work->scaleY = 10;
    work->animating = 0;
    work->unk_160 = 0;
    work->target = NULL;
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

    if (owner->flags & BTL_FLAG_DISMISS_SUMMONS) return 0;

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

            if (target != NULL) {
                body->y = target->y;
                body->z = target->groundZ;
                body->groundZ = target->groundZ;

                if (target->flags & BTLOBJ_FLAG_FACING_LEFT) {
                    body->x = target->x + 0x2000;
                    body->flags |= BTLOBJ_FLAG_FACING_LEFT;
                } else {
                    body->x = target->x - 0x2000;
                    body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
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
            AnimChangeWithDef(sSmnCloudAnimDefs, &work->anim, 0, 0, work->tiles);
        } else if ((s16)work->unk_160 == 0 && AnimIsFinished(&work->anim)) {
            AnimChangeWithDef(sSmnCloudAnimDefs, &work->anim, 1, 0, work->tiles);
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
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT ? ApplyAttackBox(151, body->x - 0x2800, body->y, body->z, 24, 24, 48) : ApplyAttackBox(151, body->x + 0x2800, body->y, body->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT00);
                        FadeStartIn(FADE_MODE_ADD_WHITE, 20);

                        if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
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

                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT ? ApplyAttackBox(151, body->x - 0x2800, body->y, body->z, 24, 24, 48) : ApplyAttackBox(151, body->x + 0x2800, body->y, body->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT01);
                        FadeStartIn(FADE_MODE_ADD_WHITE, 20);

                        if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
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

                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT ? ApplyAttackBox(151, body->x - 0x2800, body->y, body->z, 24, 24, 48) : ApplyAttackBox(151, body->x + 0x2800, body->y, body->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT02);
                        FadeStartIn(FADE_MODE_ADD_WHITE, 50);

                        if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
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
            AnimChangeWithDef(sSmnCloudAnimDefs, &work->anim, 6, 0, work->tiles);
        } else if ((s16)work->unk_160 == 0 && AnimIsFinished(&work->anim)) {
            AnimChangeWithDef(sSmnCloudAnimDefs, &work->anim, 7, 0, work->tiles);
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
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT ? ApplyAttackBox(151, body->x - 0x2800, body->y, body->z, 24, 24, 48) : ApplyAttackBox(151, body->x + 0x2800, body->y, body->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT00);
                        FadeStartIn(FADE_MODE_ADD_WHITE, 20);

                        if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
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

                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT ? ApplyAttackBox(151, body->x - 0x2800, body->y, body->z, 24, 24, 48) : ApplyAttackBox(151, body->x + 0x2800, body->y, body->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT01);
                        FadeStartIn(FADE_MODE_ADD_WHITE, 20);

                        if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
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
            AnimChangeWithDef(sSmnCloudAnimDefs, &work->anim, 2, ANIM_FLAG_LOOP, work->tiles);
            work->speed = 0;
        }

        if (body->flags & BTLOBJ_FLAG_FACING_LEFT) pixelX = gBtlWork->xMin + 50;
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

            if (target == NULL) {
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
                AnimChangeWithDef(sSmnCloudAnimDefs, &work->anim, 3, 0, work->tiles);
                break;
            case 1:
                m4aSongNumStart(SONG_VO_KU_ATTACK01);
                AnimChangeWithDef(sSmnCloudAnimDefs, &work->anim, 4, 0, work->tiles);
                break;
            case 2:
            default:
                m4aSongNumStart(SONG_VO_KU_ATTACK02);
                AnimChangeWithDef(sSmnCloudAnimDefs, &work->anim, 5, 0, work->tiles);
                break;
            }

            if (body->x < work->targetX) body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            else body->flags |= BTLOBJ_FLAG_FACING_LEFT;
        }

        body->x += (work->targetX - body->x) >> 3;
        body->y += (work->targetY - body->y) >> 3;
        body->z += (work->targetZ - body->z) >> 3;

        if (work->anim.timer == 0) {
            switch ((s16)work->attackCount) {
            case 0:
                if (AnimGetFrame(&work->anim) == 4) {
                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT ? ApplyAttackBox(152, body->x - 0x1800, body->y, body->z, 40, 24, 48) : ApplyAttackBox(152, body->x + 0x1800, body->y, body->z, 40, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT00);
                        FadeStartIn(FADE_MODE_ADD_WHITE, 20);
                    }
                }

                break;
            case 1:
                if (AnimGetFrame(&work->anim) == 3) {
                    MakeOpponentsHittable();

                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT ? ApplyAttackBox(152, body->x - 0x1800, body->y, body->z, 40, 24, 48) : ApplyAttackBox(152, body->x + 0x1800, body->y, body->z, 40, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT01);
                        FadeStartIn(FADE_MODE_ADD_WHITE, 20);
                    }
                }

                break;
            case 2:
            default:
                if (AnimGetFrame(&work->anim) == 3) {
                    MakeOpponentsHittable();

                    if (body->flags & BTLOBJ_FLAG_FACING_LEFT ? ApplyAttackBox(152, body->x - 0x1800, body->y, body->z, 40, 24, 48) : ApplyAttackBox(152, body->x + 0x1800, body->y, body->z, 40, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT02);
                        FadeStartIn(FADE_MODE_ADD_WHITE, 20);
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
        if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
            sclY = gBtlWork->scale;
            sclX = sclY;
        } else if (gBtlWork->scale == work->scaleY) {
            sclY = gBtlWork->scale;
            sclX = sclY;
            flags |= SPRITE_FLAG_HFLIP;
        } else {
            sclY = gBtlWork->scale;
            sclX = -sclY;
        }
    } else if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
        sclX = gBtlWork->scale * work->scaleX >> 8;
        sclY = gBtlWork->scale * work->scaleY >> 8;
    } else {
        sclX = -(gBtlWork->scale * work->scaleX >> 8);
        sclY = gBtlWork->scale * work->scaleY >> 8;
    }

    if (sclY == 256 && sclX == sclY) {
        affine = NULL;
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
    obj->flags &= ~BTL_FLAG_SUMMON_ACTIVE;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}
