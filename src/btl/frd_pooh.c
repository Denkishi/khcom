/**
 * frd_pooh.c
 * Winnie the Pooh Battle Ally
 */

#include "frd_pooh.h"
#include "sprites_pooh.h"
#include "btl_api.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "engine_math.h"
#include "obj.h"
#include "obj_api.h"
#include <stddef.h>
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"

#ifdef VERSION_EU

static const AnimDef sFrdPoohAnimDefsEu[18] = {
    { gPoohFf01Frames, gPoohFf01Anims, gPoohFf01Tiles, 0, { 0, 0, 0 } },
    { gPoohFr01Frames, gPoohFr01Anims, gPoohFr01Tiles, 0, { 0, 0, 0 } },
    { gPoohRr01Frames, gPoohRr01Anims, gPoohRr01Tiles, 0, { 0, 0, 0 } },
    { gPoohBr01Frames, gPoohBr01Anims, gPoohBr01Tiles, 0, { 0, 0, 0 } },
    { gPoohBb01Frames, gPoohBb01Anims, gPoohBb01Tiles, 0, { 0, 0, 0 } },
    { gPoohLl10Frames, gPoohLl10Anims, gPoohLl10Tiles, 0, { 0, 0, 0 } },
    { gPoohBl07Frames, gPoohBl07Anims, gPoohBl07Tiles, 0, { 0, 0, 0 } },
    { gPoohLl04Frames, gPoohLl04Anims, gPoohLl04Tiles, 0, { 0, 0, 0 } },
    { gPoohLl04aFrames, gPoohLl04aAnims, gPoohLl04aTiles, 0, { 0, 0, 0 } },
    { gPoohFl06Frames, gPoohFl06Anims, gPoohFl06Tiles, 0, { 0, 0, 0 } },
    { gPoohFf00Frames, gPoohFf00Anims, gPoohFf00Tiles, 0, { 0, 0, 0 } },
    { gPoohFf00FrFrames, gPoohFf00FrAnims, gPoohFf00FrTiles, 0, { 0, 0, 0 } },
    { gPoohFf00RrFrames, gPoohFf00RrAnims, gPoohFf00RrTiles, 0, { 0, 0, 0 } },
    { gPoohBb00BrFrames, gPoohBb00BrAnims, gPoohBb00BrTiles, 0, { 0, 0, 0 } },
    { gPoohBb00Frames, gPoohBb00Anims, gPoohBb00Tiles, 0, { 0, 0, 0 } },
    { gPoohBb00BlFrames, gPoohBb00BlAnims, gPoohBb00BlTiles, 0, { 0, 0, 0 } },
    { gPoohFf00LlFrames, gPoohFf00LlAnims, gPoohFf00LlTiles, 0, { 0, 0, 0 } },
    { gPoohFf00FlFrames, gPoohFf00FlAnims, gPoohFf00FlTiles, 0, { 0, 0, 0 } },
};

u8 eu_08060C44(FrdPoohWork* work) {
    FrdPoohBody* body;
    body = &work->body;
    ApplyBattleBounds(&body->x, &body->y, &body->z, &body->ground);
    body->z += work->velocity;
    work->velocity += 0x33;

    if (body->z > body->ground) {
        body->z = body->ground;
        work->velocity = 0;
        return 1;
    }

    return 0;
}

void task_frd_pooh_0(FrdPoohWork* work, FrdPoohArgs* args) {
    FrdPoohBody* body;
    body = &work->body;

    if (args->side != 0) {
        work->side = 1;
        gBtlWork->flags |= BTL_FLAG_SUMMON_ACTIVE;
        work->actor = gBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    } else {
        work->side = args->side;
        gRikuBtlWork->flags |= BTL_FLAG_SUMMON_ACTIVE;
        work->actor = gRikuBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    }

    work->card = args->card;
    work->counter = 0;
    work->velocity = 0;

    if (work->actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
        body->x = (gBtlWork->xMax + 48) * 256;
        body->flags = BTLOBJ_FLAG_FACING_LEFT;
    } else {
        body->x = (gBtlWork->xMin - 48) * 256;
        body->flags = 0;
    }

    body->y = work->actor->y;
    body->z = 0;
    body->ground = 0;
    work->state = 0;
    work->targetX = work->actor->x;
    work->targetY = work->actor->y;
    work->palette = LoadObjPalette(gPoohPalette, 32);
    AnimInit(&work->anim, NULL, NULL);
    AnimChangeWithDef(sFrdPoohAnimDefsEu, &work->anim, 0, 0, work->tiles);
    ColliderInit(&body->collider, 3, 10, 32);
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

u8 task_frd_pooh_1(FrdPoohWork* work) {
    FrdPoohBody* body;
    BtlWork* battle;
    body = &work->body;
    battle = work->side != 0 ? gBtlWork : gRikuBtlWork;

    if (battle->flags & BTL_FLAG_DISMISS_SUMMONS) {
        return 0;
    }

    BtlMapFollowPosition(body->x, body->y, body->z);

    switch (work->state) {
    case 0: {
        s32 flip = 0;
        u8 angle = GetAngle(body->x, body->y, work->targetX, work->targetY);

        switch (((angle + 16) & 255) >> 5) {
        case 0:
            AnimChangeWithDef(sFrdPoohAnimDefsEu, &work->anim, 4, ANIM_FLAG_LOOP, work->tiles);
            flip = 1;
            break;
        case 1:
            AnimChangeWithDef(sFrdPoohAnimDefsEu, &work->anim, 3, ANIM_FLAG_LOOP, work->tiles);
            flip = 1;
            break;
        case 2:
            AnimChangeWithDef(sFrdPoohAnimDefsEu, &work->anim, 2, ANIM_FLAG_LOOP, work->tiles);
            flip = 1;
            break;
        case 3:
            AnimChangeWithDef(sFrdPoohAnimDefsEu, &work->anim, 1, ANIM_FLAG_LOOP, work->tiles);
            flip = 1;
            break;
        case 4:
            AnimChangeWithDef(sFrdPoohAnimDefsEu, &work->anim, 0, ANIM_FLAG_LOOP, work->tiles);
            flip = 0;
            break;
        case 5:
            AnimChangeWithDef(sFrdPoohAnimDefsEu, &work->anim, 1, ANIM_FLAG_LOOP, work->tiles);
            flip = 0;
            break;
        case 6:
            AnimChangeWithDef(sFrdPoohAnimDefsEu, &work->anim, 2, ANIM_FLAG_LOOP, work->tiles);
            flip = 0;
            break;
        case 7:
            AnimChangeWithDef(sFrdPoohAnimDefsEu, &work->anim, 3, ANIM_FLAG_LOOP, work->tiles);
            flip = 0;
            break;
        }

        if (flip) body->flags |= BTLOBJ_FLAG_FACING_LEFT;
        else body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;

        body->x += gSineTable[angle] * 128 >> 8;
        body->y += -gSineTable[angle + 64] * 128 >> 8;
        ApplyAttackBox(110, body->x, body->y, body->z, 20, 10, 64);

        if ((body->x - work->targetX >= 0 ? body->x - work->targetX : work->targetX - body->x) < 0x800 &&
            (body->y - work->targetY >= 0 ? body->y - work->targetY : work->targetY - body->y) < 0x800) {
            work->targetX = (gBtlWork->xMin + GetRandom() % (gBtlWork->xMax - gBtlWork->xMin + 1)) * 256;
            work->targetY = (gBtlWork->yMin + GetRandom() % (gBtlWork->yMax - gBtlWork->yMin + 1)) * 256;
        }

        if ((u16)(GetRandom() % 300u) == 0) work->state = 1;

        break;
    }
    case 1: {
        u8 angle;
        work->targetX = work->actor->x;
        work->targetY = work->actor->y;
        AnimChangeWithDef(sFrdPoohAnimDefsEu, &work->anim, 5, ANIM_FLAG_LOOP, work->tiles);
        angle = GetAngle(body->x, body->y, work->targetX, work->targetY);

        if (work->targetX < body->x) body->flags |= BTLOBJ_FLAG_FACING_LEFT;
        else body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;

        body->x += gSineTable[angle] * 0x133 >> 8;
        body->y += -gSineTable[angle + 64] * 0x133 >> 8;
        ApplyAttackBox(110, body->x, body->y, body->z, 20, 10, 64);

        if (ColliderIsTouchingType(&body->collider, 1)) {
            work->state = 2;
            ColliderSetDisabled(&body->collider, 1);
            work->bob = 0;
        }

        break;
    }
    case 2:
        AnimChangeWithDef(sFrdPoohAnimDefsEu, &work->anim, 6, 0, work->tiles);

        if (AnimIsFinished(&work->anim)) {
            if (work->actor->flags & BTLOBJ_FLAG_FACING_LEFT) body->flags |= BTLOBJ_FLAG_FACING_LEFT;
            else body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;

            if ((u16)(GetRandom() % 200u) == 0) work->state = 5;
        }

        if (body->flags & BTLOBJ_FLAG_FACING_LEFT) body->x = work->actor->x + 0xA00;
        else body->x = work->actor->x - 0xA00;

        body->y = work->actor->y + 0x800;
        body->z = work->actor->z + work->bob;
        work->bob += (-0x1C00 - work->bob) >> 3;
        break;
    case 5:
        AnimChangeWithDef(sFrdPoohAnimDefsEu, &work->anim, 9, 0, work->tiles);

        if (work->actor->flags & BTLOBJ_FLAG_FACING_LEFT) body->flags |= BTLOBJ_FLAG_FACING_LEFT;
        else body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;

        body->x = work->actor->x;
        body->y = work->actor->y + 0x800;
        body->z = work->actor->z + work->bob - 0xC00;

        if (work->counter > 180) {
            work->state = 6;
            work->counter = 120;
            work->animcounter = 0;
            work->scale = 0;
            BgFxStartJfMajinBeam(body->x, body->y, body->z - 0x1A00, 0x180, 0x80, 80);
        } else work->counter++;

        break;
    case 6: {
        s32 frame;

        if (work->actor->flags & BTLOBJ_FLAG_FACING_LEFT) body->flags |= BTLOBJ_FLAG_FACING_LEFT;
        else body->flags &= ~BTLOBJ_FLAG_FACING_LEFT;

        body->x = work->actor->x;
        body->y = work->actor->y + 0x800;
        body->z = work->actor->z + work->bob - 0xC00;
        frame = (work->animcounter >> 8) & 7;
        AnimChangeWithDef(sFrdPoohAnimDefsEu, &work->anim, frame + 10, 0, work->tiles);
        ApproachValue(&work->animcounter, 0x800, work->counter);
        ApproachValue(&work->scale, 0x10000, work->counter);
        BgFxSetAngle(-(work->scale >> 8) - 128);
        BgFxSetPosition(body->x, body->y, body->z - 0x1A00);

        if (--work->counter <= 0) {
            work->state = 3;
            work->counter = 0;
            work->velocity = -0x380;
            work->speed = 0x500;
            work->bounce = 0;
        }

        break;
    }
    case 3:
        AnimChangeWithDef(sFrdPoohAnimDefsEu, &work->anim, 7, 0, work->tiles);

        if (body->flags & BTLOBJ_FLAG_FACING_LEFT) body->x -= work->speed;
        else body->x += work->speed;

        work->speed -= 0x33;

        if (work->speed <= 0) {
            work->speed = 0;

            if (AnimIsFinished(&work->anim)) {
                work->state = 4;
                ColliderSetDisabled(&body->collider, 0);
            }
        }

        if (eu_08060C44(work) && !work->bounce) {
            work->bounce = 1;
            BtlMapStartShake();
        }

        ApplyAttackBox(162, body->x, body->y, body->z, 30, 25, 10);
        break;
    case 4:
        AnimChangeWithDef(sFrdPoohAnimDefsEu, &work->anim, 8, 0, work->tiles);

        if (AnimIsFinished(&work->anim)) work->state = 0;

        break;
    }

    AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    ColliderSetPosition(&body->collider, body->x, body->y, body->z);
    return 1;
}

void task_frd_pooh_2(FrdPoohWork* work) {
    FrdPoohBody* body;
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
    } else if (gBtlWork->scale == 256) {
        sclY = gBtlWork->scale;
        sclX = sclY;
        flags |= SPRITE_FLAG_HFLIP;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (gBtlWork->scale == 256) {
        affine = NULL;
    } else if (gBtlWork->scale <= 255) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4100 - ((body->y >> 8) * 4));
    body->depth = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_frd_pooh_3(FrdPoohWork* work) {
    BtlWork* battle;
    ColliderUnregister(&work->body.collider);
    battle = work->side != 0 ? gBtlWork : gRikuBtlWork;
    battle->flags &= ~BTL_FLAG_SUMMON_ACTIVE;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

TaskDesc gTaskDescFrdPoohEu = {
    "task_frd_pooh",
    (TaskInitFunc)task_frd_pooh_0,
    (TaskUpdateFunc)task_frd_pooh_1,
    (TaskDrawFunc)task_frd_pooh_2,
    (TaskDestroyFunc)task_frd_pooh_3,
    sizeof(FrdPoohWork),
};

#endif
