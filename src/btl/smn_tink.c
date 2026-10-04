#include "task_descriptors.h"
#include "smn.h"
#include "anim.h"
#include "sprites_evt.h"
#include "sprites_smn.h"
#include "songs.h"
#include "smn_tasks.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_effect.h"
#include "engine_math.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

static const AnimDef sSmnTinkAnimDefs[3] = {
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

void task_smn_tink_0(SmnTinkWork* work, SmnArgs* args) {
    BtlObj* body;
    BtlObj* obj;
    s32 t;

    body = &work->body;

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= BTL_FLAG_SUMMON_ACTIVE;
        obj = gBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= BTL_FLAG_SUMMON_ACTIVE;
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

    if (obj->flags & BTLOBJ_FLAG_FACING_LEFT) {
        body->flags = (BTLOBJ_FLAG_FACING_LEFT | BTLOBJ_FLAG_SMALL_SHADOW);
    } else {
        body->flags = BTLOBJ_FLAG_SMALL_SHADOW;
    }

    work->variant = args->variant;
    work->palette = LoadObjPalette(gTinkPalette, 32);
    AnimInit(&work->anim, NULL, NULL);
    AnimChangeWithDef(sSmnTinkAnimDefs, &work->anim, 0, ANIM_FLAG_LOOP, work->tiles);
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

    if ((work->mainSide != 0 ? gBtlWork->flags : gRikuBtlWork->flags) & BTL_FLAG_DISMISS_SUMMONS) {
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
            AnimChangeWithDef(sSmnTinkAnimDefs, &work->anim, 0, ANIM_FLAG_LOOP, work->tiles);
            work->hoverZ = body->z;
            work->steps = 30;
        } else {
            body->z += (work->hoverZ + gSineTable[work->stateTimer & 0xFF] * 12
                             - body->z) >> 2;
        }

        if (work->actor->x < body->x) {
            body->flags |= BTLOBJ_FLAG_FACING_LEFT;
        } else {
            body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
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
            AnimChangeWithDef(sSmnTinkAnimDefs, &work->anim, 1, ANIM_FLAG_LOOP, work->tiles);
        }

        p = work->actor;
        x = p->x + gSineTable[((u16)work->stateTimer * 4) & 0xFF] * 32;
        y = p->y + gSineTable[(((u16)work->stateTimer * 4) & 0xFF) + 64] * -16;
        z = (p->z - 0x1E00) + gSineTable[(u16)work->stateTimer * 2 & 0xFF] * 16;

        if (x < body->x) {
            body->flags |= BTLOBJ_FLAG_FACING_LEFT;
        } else {
            body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
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
            AnimChangeWithDef(sSmnTinkAnimDefs, &work->anim, 2, 0, work->tiles);

            if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
                work->flyAngle = 0xC0;
            } else {
                work->flyAngle = 0x40;
            }
        }

        body->x += gSineTable[(u8)work->flyAngle] * work->speed >> 8;
        body->z += -gSineTable[(u8)work->flyAngle + 0x40] * work->speed >> 8;

        if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
            work->flyAngle += 7;
        } else {
            work->flyAngle -= 7;
        }

        if (AnimIsFinished(&work->anim)) {
            AnimChangeWithDef(sSmnTinkAnimDefs, &work->anim, 1, ANIM_FLAG_LOOP, work->tiles);
            work->state = 3;
            work->stateTimer = 1;
        } else {
            work->stateTimer++;
        }

        break;
    }

    ClampBattlePosition(&body->x, &body->y, -16, 0);

    if (work->animating) {
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

    if (body->flags & BTLOBJ_FLAG_FACING_LEFT) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (gBtlWork->scale == 256 && work->scale == gBtlWork->scale) {
        sclY = work->scale;
        sclX = sclY;
        flags |= SPRITE_FLAG_HFLIP;
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
    obj->flags &= ~BTL_FLAG_SUMMON_ACTIVE;
    m4aSongNumStop(SONG_EF_TINK_LOOP);
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

static inline s32 GetTinkEffectOffset() {
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
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    case 1:
        AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
        break;
    case 2:
        AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);
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
    DrawSprite(sx, sy, gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2),
               -4100 - ((work->y >> 8) * 4));
}

void task_smn_tinkeff_3(SmnTinkeffWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}
