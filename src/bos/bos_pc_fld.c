#include "bos6.h"
#include "sprites_bos6.h"
#include "sprites_staff_roll.h"
#include "btl_api.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_bg_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "display.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

static u8 sBosPcFldShakeActive;
static s16 sBosPcFldShakePattern;
static s16 sBosPcFldShakeStep;
static s32 sBosPcFldShakeOffset;

static const s8 sUnk_09A4CA94[33] = {
    4, 4, 4, 4, -4, -4, -4, -4, 3, 3, 3, 3, -3, -3, -3, -3, 2, 2, 2, 2, -2, -2, -2, -2, 1, 1, 1, 1, -1, -1, -1, -1, 0,
};

static const s8 sUnk_09A4CAB5[9] = {
    1, 2, 2, 1, -1, -2, -2, -1, 0,
};

static const u16 sBosPcFldPaletteCycleNext[3] = {
    1, 2, 0,
};

static const s16 sBosPcFldPaletteCycleFrames[3] = {
    6, 6, 6,
};

static const s8* sBosPcFldShakePatterns[2] = { sUnk_09A4CA94, sUnk_09A4CAB5 };

TaskDesc gTaskDescBosPcFld = {
    "task_bos_pc_fld",
    (TaskInitFunc)task_bos_pc_fld_0,
    (TaskUpdateFunc)task_bos_pc_fld_1,
    (TaskDrawFunc)task_bos_pc_fld_2,
    (TaskDestroyFunc)task_bos_pc_fld_3,
    sizeof(PcFldWork),
};

static s32 Square(s32 x) {
    return x * x;
}

void BosPcFldSetPaletteCycle(Task* task, u8 v) {
    PcFldWork* work = task->work;

    work->paletteCycle = v;
}

void BosPcFldEnableObject(Task* task, u8 a) {
    PcFldWork* work;
    ObjPalette* pal;

    work = task->work;

    if (a == 1) {
        a = 0;
    } else {
        a = 1;
    }

    ColliderSetDisabled(&work->collider, a);

    if (a == 0) {
        if (work->tiles == NULL) {
            work->tiles = LoadObjTiles(gUnk_09CC4E54, 0x200);
        }

        if (work->palette == NULL) {
            pal = LoadObjPalette(gUnk_09D693D4, 0x60);
            work->palette = pal;
            LoadPalette(gUnk_09D69434, gUnk_05000220 + pal->index * 32, 32);
        }
    }
}

void BosPcFldResetShake() {
    sBosPcFldShakeActive = 0;
    sBosPcFldShakePattern = 0;
    sBosPcFldShakeStep = 0;
    sBosPcFldShakeOffset = 0;
}

void BosPcFldStartShake(s16 a) {
    sBosPcFldShakeActive = 1;
    sBosPcFldShakePattern = a;
    sBosPcFldShakeStep = 0;
    sBosPcFldShakeOffset = 0;
}

void BosPcFldUpdateShake() {
    const s8* p;

    if (sBosPcFldShakeActive != 0) {
        p = sBosPcFldShakePatterns[sBosPcFldShakePattern];
        sBosPcFldShakeOffset += ((p[sBosPcFldShakeStep] << 12) - sBosPcFldShakeOffset) >> 3;
        sBosPcFldShakeStep += 1;

        if (p[sBosPcFldShakeStep] == 0) {
            sBosPcFldShakeActive = 0;
            sBosPcFldShakeOffset = 0;
        }
    }
}

s32 BosPcFldGetShake() {
    return sBosPcFldShakeOffset;
}

void BosPcFldResetPaletteCycle(PcFldWork* work) {
    u16 zero;

    zero = 0;
    work->paletteCycle = zero;
    work->paletteIndex = zero;
    work->paletteTimer = zero;
}

void BosPcFldUpdatePaletteCycle(PcFldWork* work) {
    u16 t;
    u16 zero;

    if (work->paletteCycle != 0) {
        if (work->paletteTimer > sBosPcFldPaletteCycleFrames[work->paletteIndex]) {
            t = sBosPcFldPaletteCycleNext[work->paletteIndex];
            zero = 0;
            work->paletteIndex = t;
            work->paletteTimer = zero;
        }

        work->paletteTimer += 1;
    }
}

void BosPcFldLoadPaletteCycle(PcFldWork* work) {
    if (work->paletteCycle != 0) {
        LoadPalette(gUnk_09D69374 + work->paletteIndex * 32, gUnk_05000080, 32);
    }
}

void BosPcFldStopPaletteCycle(PcFldWork* work) {
    work->paletteCycle = 0;
}

void task_bos_pc_fld_0(PcFldWork* work, PcBattleBackgroundDef* arg) {
    Collider* p;

    LoadBgTiles(0, arg->tiles, arg->tilesSize);
    LoadBgPalette(0, arg->palette, arg->paletteSize);
    SetBgMapBlocks(0, &arg->map, 2, 3);
    gBtlWork->scale = 0x100;
    gBtlWork->zoomScale = 0x100;
    gBtlWork->x = 0x11400;
    gBtlWork->y = 0x15300;
    gBtlWork->viewX = 0x11400;
    gBtlWork->viewY = 0x15300;
    gBtlWork->x2 = 0x11400;
    gBtlWork->y2 = 0x15300;
    gBtlWork->zoomX = 0x11400;
    gBtlWork->zoomY = 0x15300;
    gBtlWork->zoomSteps = 15;
    gBtlWork->rotation = 0;
    BtlMapResetShake();
    BosPcFldResetShake();
    ScrollBgMapTo(0, gBtlWork->viewX >> 8, gBtlWork->viewY >> 8);
    BosPcFldResetPaletteCycle(work);
    BosPcFldUpdatePaletteCycle(work);
    work->tiles = 0;
    work->palette = 0;
    p = &work->collider;
    ColliderInit(p, 6, 40, 8);
    ColliderSetPosition(p, 0x17400, 0x15400, 0);
    ColliderSetDisabled(p, 1);
}

u8 task_bos_pc_fld_1(PcFldWork* work) {
    s32 t;
    s32 u;
    s32 dx;
    s32 dy;
    BtlObj* pos;

    BtlMapUpdateShake();
    BosPcFldUpdateShake();
    pos = gBtlWork->actor;
    u = gBtlWork->viewX - 0x7800;
    t = pos->x - u;

    if (t < 0) {
        t = 0;
    }

    gBtlWork->x2 = t / 2 + 0xF000;
    dx = (gBtlWork->x2 - gBtlWork->x) >> 3;
    dy = (gBtlWork->y2 - gBtlWork->y) >> 3;

    if (dx > 0x500) {
        dx += 0x500;
    } else if (dx < -0x500) {
        dx -= 0x500;
    }

    gBtlWork->x += dx;
    gBtlWork->y += dy;
    gBtlWork->viewX = gBtlWork->x;
    gBtlWork->viewY = gBtlWork->y;

    if (gBtlWork->viewX - 0x7800 < gBtlWork->xMin * 256) {
        gBtlWork->viewX = (gBtlWork->xMin + 120) * 256;
    } else if (gBtlWork->viewX + 0x7800 > gBtlWork->xMax * 256) {
        gBtlWork->viewX = (gBtlWork->xMax - 120) * 256;
    }

    if (gBtlWork->viewY + 0x3000 < gBtlWork->yMin * 256) {
        gBtlWork->viewY = (gBtlWork->yMin - 48) * 256;
    } else if (gBtlWork->viewY + 0x5000 > gBtlWork->yMax * 256) {
        gBtlWork->viewY = (gBtlWork->yMax - 80) * 256;
    }

    gBtlWork->viewY += BtlMapGetShake();
    gBtlWork->viewY += BosPcFldGetShake();
    ScrollBgMapTo(0, (gBtlWork->viewX >> 8) + 8, (gBtlWork->viewY >> 8) + 40);
    BosPcFldUpdatePaletteCycle(work);
    return 1;
}

void task_bos_pc_fld_2(PcFldWork* work) {
    s16 sx;
    s16 sy;
    BtlObj* pos;
    u32 x;
    u32 y;
    s32 z;

    BosPcFldLoadPaletteCycle(work);
    pos = gBtlWork->actor;

    if (pos->z >= -0x100) {
        if ((pos->flags & BTLOBJ_FLAG_HIT_LOCKED) == 0) {
            if (work->tiles != NULL) {
                if (work->palette != NULL) {
                    x = 0x17000;
                    y = 0x14800;
                    z = -0x800;
                    WorldToScreen(&sx, &sy, x, y, z);
                    DrawSprite(sx, sy, gUnk_09EFBEB8, work->tiles,
                        work->palette, 0, GetBattleSpritePriorityFlags(y),
                        (u16)(-0x1004 - (s32)(y >> 6)));
                }
            }
        }
    }
}

void task_bos_pc_fld_3(PcFldWork* work) {
    BosPcFldStopPaletteCycle(work);
    ColliderUnregister(&work->collider);

    if (work->tiles != NULL) {
        ReleaseObjTiles(work->tiles);
    }

    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
    }
}
