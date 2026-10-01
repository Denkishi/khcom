#include "obj_api.h"
#include "btl3.h"
#include "smn.h"
#include "sprites_btl.h"
#include "btl3_tasks.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "engine_math.h"
#include "listpool.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

static const AnimDef sBtlBadstatusAnimDefs[5] = {
    { gUnk_09EE12E8, gUnk_09EE130C, gUnk_08B21CFC, 0, { 0, 0, 0 } },
    { gUnk_09EE12D4, gUnk_09EE12E4, gUnk_08B21ACE, 0, { 0, 0, 0 } },
    { gUnk_09EE1318, gUnk_09EE132C, gUnk_08B2213C, 0, { 0, 0, 0 } },
    { gUnk_09EE1330, gUnk_09EE1360, gUnk_08B223E8, 0, { 0, 0, 0 } },
    { gUnk_09EE1368, gUnk_09EE137C, gUnk_08B229A8, 0, { 0, 0, 0 } },
};

void task_btl_badstatus_0(BtlBadStatusWork* work, BtlObj* obj) {
    work->status = 0;
    work->actor = obj;
    work->tiles = AllocObjTiles(128, NULL);
    work->palette = LoadObjPalette(gBStatesPalette, 32);
    work->palette2 = LoadObjPalette(gCard00Palette, 32);
    work->palette3 = work->palette;
    AnimInit(&work->anim, NULL, NULL);
    AnimChangeWithDef(sBtlBadstatusAnimDefs, &work->anim, 0, ANIM_FLAG_LOOP, work->tiles);
}

u8 task_btl_badstatus_1(BtlBadStatusWork* work) {
    BtlObj* obj;
    u32 state;

    obj = work->actor;
    state = obj->badStatus;

    if (state == 0) {
        return 1;
    }

    if (state != work->status) {
        work->status = state;

        switch (state) {
        case 2:
            AnimChangeWithDef(sBtlBadstatusAnimDefs, &work->anim, 0, ANIM_FLAG_LOOP, work->tiles);
            work->palette3 = work->palette;
            break;
        case 5:
            AnimChangeWithDef(sBtlBadstatusAnimDefs, &work->anim, 2, ANIM_FLAG_LOOP, work->tiles);
            work->palette3 = work->palette2;
            break;
        case 3:
            AnimChangeWithDef(sBtlBadstatusAnimDefs, &work->anim, 3, ANIM_FLAG_LOOP, work->tiles);
            work->palette3 = work->palette;
            break;
        case 4:
            AnimChangeWithDef(sBtlBadstatusAnimDefs, &work->anim, 4, ANIM_FLAG_LOOP, work->tiles);
            work->palette3 = work->palette2;
            break;
        case 1:
        default:
            AnimChangeWithDef(sBtlBadstatusAnimDefs, &work->anim, 1, ANIM_FLAG_LOOP, work->tiles);
            work->palette3 = work->palette;
            break;
        }
    }

    obj->badStatusTimer--;

    if (obj->badStatusTimer <= 0) {
        obj->badStatus = BAD_STATUS_NONE;
        work->status = 0;
    }

    return 1;
}

void task_btl_badstatus_2(BtlBadStatusWork* work) {
    BtlObj* obj;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;

    obj = work->actor;

    if (obj->badStatus != BAD_STATUS_NONE) {
        flags = GetBattleSpritePriorityFlags(obj->y);

        if (gBtlWork->paused != 0) {
            gfx = AnimGetGfx(&work->anim);
        } else {
            gfx = AnimUpdate(&work->anim);
        }

        WorldToScreen(&sx, &sy, obj->x, obj->y,
                      obj->z - ((obj->height + 8) << 8));
        DrawSprite(sx, sy, gfx, work->tiles, work->palette3, NULL, flags,
                   -4101 - ((obj->y >> 8) * 4));
    }
}

void task_btl_badstatus_3(BtlBadStatusWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
}

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

TaskDesc gTaskDescBtlBadstatus = {
    "task_btl_badstatus",
    (TaskInitFunc)task_btl_badstatus_0,
    (TaskUpdateFunc)task_btl_badstatus_1,
    (TaskDrawFunc)task_btl_badstatus_2,
    (TaskDestroyFunc)task_btl_badstatus_3,
    sizeof(BtlBadStatusWork),
};
