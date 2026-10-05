/**
 * btl_lockon.c
 * Battle Lock-On Cursor and Area Marker
 */

#include "task_descriptors.h"
#include "obj_api.h"
#include "btl.h"
#include "btl_api.h"
#include "sprites_btl.h"
#include "btl_tasks.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "listpool.h"
#include "obj.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "sprite_palettes.h"

TaskDesc gTaskDescBtlLockon = {
    "task_btl_lockon",
    (TaskInitFunc)task_btl_lockon_0,
    (TaskUpdateFunc)task_btl_lockon_1,
    (TaskDrawFunc)task_btl_lockon_2,
    (TaskDestroyFunc)task_btl_lockon_3,
    sizeof(BtlLockonWork),
};

TaskDesc gTaskDescBtlArea = {
    "task_btl_area",
    (TaskInitFunc)task_btl_area_0,
    (TaskUpdateFunc)task_btl_area_1,
    (TaskDrawFunc)task_btl_area_2,
    (TaskDestroyFunc)task_btl_area_3,
    sizeof(BtlAreaWork),
};

void task_btl_lockon_0(BtlLockonWork* work) {
    work->tiles = LoadObjTiles(gBtlLockonTiles, 0x180);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    AnimInit(&work->anim, gBtlLockonAnims, gBtlLockonFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    work->timer = 0;
    gBtlWork->actor2 = NULL;
}

void SelectLockonTarget() {
    BtlObj* p;
    BtlObj* e;
    s32 min;

    p = gBtlWork->actor;
    min = 0x40000;
    gBtlWork->actor2 = NULL;
    e = ListPoolFirst(&gBtlWork->pool);

    if (p->flags & BTLOBJ_FLAG_FACING_LEFT) {
        for (; e != NULL; e = ListPoolNext(&e->node)) {
            if (p->x < e->x || p->x - e->x > 0x9600 ||
                (p->y - e->y >= 0 ? p->y - e->y > 0x1800
                                              : e->y - p->y > 0x1800) ||
                (p->z - e->z >= 0 ? p->z - e->z > 0x6400
                                              : e->z - p->z > 0x6400) ||
                (e->flags & BTLOBJ_FLAG_UNHITTABLE) || p->x - e->x >= min) {
                continue;
            }

            gBtlWork->actor2 = e;
            min = p->x - e->x;
        }

        if (gBtlWork->actor2 == NULL) {
            min = 0x40000;
            e = ListPoolFirst(&gBtlWork->pool);

            for (; e != NULL; e = ListPoolNext(&e->node)) {
                if (p->x > e->x || e->x - p->x > 0x5A00 ||
                    (p->y - e->y >= 0 ? p->y - e->y > 0x1800
                                                  : e->y - p->y > 0x1800) ||
                    (p->z - e->z >= 0 ? p->z - e->z > 0x6400
                                                  : e->z - p->z > 0x6400) ||
                    (e->flags & BTLOBJ_FLAG_UNHITTABLE) || e->x - p->x >= min) {
                    continue;
                }

                gBtlWork->actor2 = e;
                min = e->x - p->x;
            }
        }
    } else {
        for (; e != NULL; e = ListPoolNext(&e->node)) {
            if (p->x > e->x || e->x - p->x > 0x9600 ||
                (p->y - e->y >= 0 ? p->y - e->y > 0x1800
                                              : e->y - p->y > 0x1800) ||
                (p->z - e->z >= 0 ? p->z - e->z > 0x6400
                                              : e->z - p->z > 0x6400) ||
                (e->flags & BTLOBJ_FLAG_UNHITTABLE) || e->x - p->x >= min) {
                continue;
            }

            gBtlWork->actor2 = e;
            min = e->x - p->x;
        }

        if (gBtlWork->actor2 == NULL) {
            min = 0x40000;
            e = ListPoolFirst(&gBtlWork->pool);

            for (; e != NULL; e = ListPoolNext(&e->node)) {
                if (p->x < e->x || p->x - e->x > 0x5A00 ||
                    (p->y - e->y >= 0 ? p->y - e->y > 0x1800
                                                  : e->y - p->y > 0x1800) ||
                    (p->z - e->z >= 0 ? p->z - e->z > 0x6400
                                                  : e->z - p->z > 0x6400) ||
                    (e->flags & BTLOBJ_FLAG_UNHITTABLE) || p->x - e->x >= min) {
                    continue;
                }

                gBtlWork->actor2 = e;
                min = p->x - e->x;
            }
        }
    }
}

u8 task_btl_lockon_1(BtlLockonWork* work) {
    if ((gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) == 0) {
        SelectLockonTarget();
    }

    if (gBtlWork->actor2 != NULL) {
        work->gfx = AnimUpdate(&work->anim);

        if (gBtlWork->actor2->flags & BTLOBJ_FLAG_UNHITTABLE) {
            gBtlWork->actor2 = NULL;
        }
    }

    if (work->timer != 0) {
        work->timer--;
    }

    return 1;
}

void task_btl_lockon_2(BtlLockonWork* work) {
    BtlObj* e;
    s16 x;
    s16 y;

    e = gBtlWork->actor2;

    if (e != NULL) {
        WorldToScreen(&x, &y, e->x + (e->centerOffsetX << 8), e->y,
                      e->z - (e->centerHeight << 8));
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_FLAG_NO_MOSAIC, 16);
    }
}

void task_btl_lockon_3(BtlLockonWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_btl_area_0(BtlAreaWork* work) {
    work->visible = 0;
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    work->tiles = LoadObjTiles(gBtlAreaTiles, 0xE0);
    work->timer = 0;
    work->enabled = 1;
}

u8 task_btl_area_1(BtlAreaWork* work) {
    if (!work->enabled) {
        work->visible = 0;
        return 1;
    }

    if (gBtlWork->areaUpdated) {
        work->timer = 20;
        gBtlWork->areaUpdated = 0;
    }

    if (work->timer > 0) {
        work->visible = 1;
    } else {
        work->visible = 0;
    }

    if (work->timer > 0) {
        work->timer--;
    }

    return 1;
}

void task_btl_area_2(BtlAreaWork* work) {
    BtlObj* e;
    s16 x;
    s16 y;

    if (!work->visible) {
        return;
    }

    WorldToScreen(&x, &y, gBtlWork->x3 - (gBtlWork->areaHalfX << 8),
                  gBtlWork->y3 - (gBtlWork->areaHalfY << 8), gBtlWork->z3);
    DrawSprite(x, y, gBtlAreaFrame0, work->tiles, work->palette, NULL, 0, 0x101);
    WorldToScreen(&x, &y, gBtlWork->x3 + (gBtlWork->areaHalfX << 8),
                  gBtlWork->y3 - (gBtlWork->areaHalfY << 8), gBtlWork->z3);
    DrawSprite(x, y, gBtlAreaFrame1, work->tiles, work->palette, NULL, 0, 0x101);
    WorldToScreen(&x, &y, gBtlWork->x3 - (gBtlWork->areaHalfX << 8),
                  gBtlWork->y3 + (gBtlWork->areaHalfY << 8), gBtlWork->z3);
    DrawSprite(x, y, gBtlAreaFrame3, work->tiles, work->palette, NULL, 0, 0x101);
    WorldToScreen(&x, &y, gBtlWork->x3 + (gBtlWork->areaHalfX << 8),
                  gBtlWork->y3 + (gBtlWork->areaHalfY << 8), gBtlWork->z3);
    DrawSprite(x, y, gBtlAreaFrame2, work->tiles, work->palette, NULL, 0, 0x101);
    WorldToScreen(&x, &y, gBtlWork->x3, gBtlWork->y3, gBtlWork->z3);
    DrawSprite(x, y, gBtlAreaFrame5, work->tiles, work->palette, NULL, 0, 0x101);
    WorldToScreen(&x, &y, gBtlWork->x3, gBtlWork->y3,
                  gBtlWork->z3 - (gBtlWork->areaHalfZ << 8));
    DrawSprite(x, y, gBtlAreaFrame4, work->tiles, work->palette, NULL, 0, 0x101);
    WorldToScreen(&x, &y, gBtlWork->x3, gBtlWork->y3,
                  gBtlWork->z3 + (gBtlWork->areaHalfZ << 8));
    DrawSprite(x, y, gBtlAreaFrame4, work->tiles, work->palette, NULL, SPRITE_FLAG_VFLIP, 0x101);

    if (gBtlWork->soraOwnsPlay) {
        e = ListPoolFirst(&gBtlWork->pool);

        while (e != NULL) {
            WorldToScreen(&x, &y, e->x - (e->radiusX << 8),
                          e->y - (e->radiusY << 8), e->z);
            DrawSprite(x, y, gBtlAreaFrame0, work->tiles, work->palette, NULL, 0, 0x101);
            WorldToScreen(&x, &y, e->x + (e->radiusX << 8),
                          e->y - (e->radiusY << 8), e->z);
            DrawSprite(x, y, gBtlAreaFrame1, work->tiles, work->palette, NULL, 0, 0x101);
            WorldToScreen(&x, &y, e->x - (e->radiusX << 8),
                          e->y + (e->radiusY << 8), e->z);
            DrawSprite(x, y, gBtlAreaFrame3, work->tiles, work->palette, NULL, 0, 0x101);
            WorldToScreen(&x, &y, e->x + (e->radiusX << 8),
                          e->y + (e->radiusY << 8), e->z);
            DrawSprite(x, y, gBtlAreaFrame2, work->tiles, work->palette, NULL, 0, 0x101);
            WorldToScreen(&x, &y, e->x, e->y, e->z);
            DrawSprite(x, y, gBtlAreaFrame5, work->tiles, work->palette, NULL, 0, 0x101);
            WorldToScreen(&x, &y, e->x, e->y,
                          e->z - (e->height << 8));
            DrawSprite(x, y, gBtlAreaFrame4, work->tiles, work->palette, NULL, 0, 0x101);
            e = ListPoolNext(&e->node);
        }
    } else {
        e = gBtlWork->actor;
        WorldToScreen(&x, &y, e->x - (e->radiusX << 8),
                      e->y - (e->radiusY << 8), e->z);
        DrawSprite(x, y, gBtlAreaFrame0, work->tiles, work->palette, NULL, 0, 0x101);
        WorldToScreen(&x, &y, e->x + (e->radiusX << 8),
                      e->y - (e->radiusY << 8), e->z);
        DrawSprite(x, y, gBtlAreaFrame1, work->tiles, work->palette, NULL, 0, 0x101);
        WorldToScreen(&x, &y, e->x - (e->radiusX << 8),
                      e->y + (e->radiusY << 8), e->z);
        DrawSprite(x, y, gBtlAreaFrame3, work->tiles, work->palette, NULL, 0, 0x101);
        WorldToScreen(&x, &y, e->x + (e->radiusX << 8),
                      e->y + (e->radiusY << 8), e->z);
        DrawSprite(x, y, gBtlAreaFrame2, work->tiles, work->palette, NULL, 0, 0x101);
        WorldToScreen(&x, &y, e->x, e->y, e->z);
        DrawSprite(x, y, gBtlAreaFrame5, work->tiles, work->palette, NULL, 0, 0x101);
        WorldToScreen(&x, &y, e->x, e->y,
                      e->z - (e->height << 8));
        DrawSprite(x, y, gBtlAreaFrame4, work->tiles, work->palette, NULL, 0, 0x101);
    }
}

void task_btl_area_3(BtlAreaWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}
