/**
 * lockon.c
 * Field Lock-On Cursor
 */

#include "mode_test.h"
#include "sprites_mode_test.h"
#include "malloc.h"
#include "anim.h"
#include "engine_math.h"
#include "field_state.h"
#include "fld_types.h"
#include "gba/syscall.h"
#include "listpool.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "lockon.h"

void task_lockon_0(LockonWork* work) {
    s32 i;

    gLockonDoorPosition = EwramAlloc(12);
    work->tiles = AllocObjTiles(0x80, NULL);
    work->palette = LoadObjPalette(gUnk_08F69BE4, 0x20);
    SetObjTileSource(work->tiles, gUnk_090D7C84);
    AnimInit(&work->anim, gUnk_09EEC66C, gUnk_09EEC660);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);

    for (i = 0; i < 8; i++) {
        work->targets[i] = NULL;
    }

    work->targetCount = 0;
    work->selected = -1;
    work->timer = 0;
    work->unk_30 = 0;
    work->unk_4C = 0;
}

u8 task_lockon_1(LockonWork* work) {
    FldObj* o;
    s8 count;
    s8 i;
    s8 nsel;
    s8 list[8];
    s32 px;
    s32 py;
    s32 dx;
    s32 dy;
    s32 ox;
    s32 oy;

    i = 0;
    o = ListPoolFirst(&gFieldState->actor.pool);

    if (gFieldState->flags & FIELD_FLAG_NO_LOCKON) {
        gFieldState->lockonTarget = NULL;
        return 1;
    }

    LockonClearTargets(work);

    if (work->prevSelected != work->selected) {
        work->unk_30 = 0;
    }

    px = gFieldState->actor.fieldPosition.x;
    py = gFieldState->actor.fieldPosition.y;
    count = 0;

    if ((gFieldState->flags & FIELD_FLAG_HOLD_LOCKON) == 0) {
        while (o != NULL) {
            ox = o->fieldPosition.x;
            oy = o->fieldPosition.y;
            dx = px - ox;
            dy = py - oy;

            if (VectorLength2D(dx, dy) <= 0x3000 && (dx > -0x8000 && dx < 0x8000) && (dy > -0x8000 && dy < 0x8000) && o->fieldPosition.ground == gFieldState->actor.fieldPosition.ground) {
                if (o->kind == 3) {
                    gLockonDoorPosition[0] = o->fieldPosition.x;
                    gLockonDoorPosition[1] = o->fieldPosition.y;
                    gLockonDoorPosition[2] = o->fieldPosition.z;
                    work->targets[count++] = o;
                    work->targetCount++;
                } else {
                    work->targets[count++] = o;
                    work->targetCount++;
                }
            }

            if (count > 6) {
                break;
            }

            o = ListPoolNext(&o->node);
        }

        if (work->targetCount != 0) {
            nsel = 0;

            for (i = 0; i < work->targetCount; i++) {
                if (LockonIsInFront(gFieldState->actor.angle, px, py, work->targets[i])) {
                    work->selected = i;
                    list[nsel++] = i;
                }
            }

            if (nsel > 1) {
                work->selected = LockonPickNearest(px, py, work, nsel, list);
            }
        }
    }

    if (work->selected >= 0) {
        gFieldState->lockonTarget = work->targets[work->selected];
    } else {
        gFieldState->lockonTarget = NULL;
        work->unk_30 = 0;
    }

    work->prevSelected = work->selected;
    work->gfx = AnimUpdate(&work->anim);
    return 1;
}

#define CLAMP_LABEL(v, edge, limit, dest) \
    do { \
        if ((edge) > (limit)) { \
            (v) = (dest); \
        } \
    } while (0)
void task_lockon_2(LockonWork* work) {
    FldObj* obj;
    s32 x;
    s32 y;
    union {
        s32 coord;
        u8 counter;
    } x2, y2;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        return;
    }

    obj = work->targets[work->selected];

    if (obj->kind == 2) {
        return;
    }

    x = (obj->fieldPosition.x >> 8) - (gFieldState->x >> 8);
    x2.coord = x + 12;
    y = (obj->fieldPosition.y >> 8) + (obj->fieldPosition.z >> 8) - (gFieldState->y >> 8) - obj->height;
    y2.coord = y - 8;

    CLAMP_LABEL(x2.coord, x + 60, 240, 192);
    CLAMP_LABEL(y2.coord, y, 160, 152);

    x2.counter = work->timer++;
    y2.counter = x2.counter;

    if (y2.counter > 10) {
        work->timer = 0;
    }

    if (gFieldState->lockonTarget == NULL) {
        return;
    }

    if (work->selected < 0) {
        return;
    }

#ifdef VERSION_EU
    {
        FldObj* obj = work->targets[work->selected];
        s32 projectedY = (obj->fieldPosition.y >> 8) + (obj->fieldPosition.z >> 8) - (gFieldState->y >> 8);

        DrawSprite((obj->fieldPosition.x >> 8) - (gFieldState->x >> 8), projectedY - obj->height + 40, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1), -0x100E - (((s16)projectedY >> 8) << 2));
    }
#else
    obj = work->targets[work->selected];
    DrawSprite((obj->fieldPosition.x >> 8) - (gFieldState->x >> 8), (obj->fieldPosition.y >> 8) + (obj->fieldPosition.z >> 8) - (gFieldState->y >> 8) - obj->height + 40, work->gfx, work->tiles, work->palette, NULL, 0, -0x100E - ((work->targets[work->selected]->fieldPosition.y >> 8) << 2));
#endif
}

#undef CLAMP_LABEL
void task_lockon_3(LockonWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    gFieldState->lockonTarget = NULL;
    EwramFree(gLockonDoorPosition);
    gLockonDoorPosition = NULL;
}

s32 VectorLength2D(s32 a, s32 b) {
    return (u16)Sqrt(a * a + b * b);
}

s32 NormalizeVector2D8(s32* x, s32* y) {
    s32 d = VectorLength2D(*x, *y);

    if (d > 0) {
        *x = (*x << 8) / d;
        *y = (*y << 8) / d;
    }

    return d;
}

s8 LockonPickNearest(s32 a, s32 b, LockonWork* work, s8 n, s8* list) {
    s8 i;
    s8 best;
    s32 bestDist;
    FldObj* o;
    s32 dist;
    s32 dx;
    s32 dy;

    best = -1;
    bestDist = 0x10000;

    for (i = 0; i < n; i++) {
        o = work->targets[list[i]];

        if (o != NULL) {
            dx = o->fieldPosition.x;
            dy = o->fieldPosition.y;
            dist = VectorLength2D(dx - a, dy - b);

            if (bestDist > dist) {
                bestDist = dist;
                best = i;
            }
        }
    }

    if (best != -1) {
        return list[best];
    }

    return best;
}

void LockonClearTargets(LockonWork* work) {
    s8 i;

    if ((gFieldState->flags & FIELD_FLAG_HOLD_LOCKON) == 0) {
        work->selected = -1;

        for (i = 0; i < 8; i++) {
            work->targets[i] = NULL;
        }

        work->targetCount = 0;
    }
}

u8 LockonIsInFront(u16 a, s32 b, s32 c, FldObj* d) {
    s32 x;
    s32 y;
    s32 sn;
    s32 cs;
    s32 dot;

    if (d != NULL) {
        x = d->fieldPosition.x - b;
        y = d->fieldPosition.y - c;
        sn = gSineTable[a & 0xFF];
        cs = -gSineTable[(a & 0xFF) + 0x40];
        NormalizeVector2D8(&x, &y);
        dot = (sn * x >> 8) + (y * cs >> 8);

        if (d->kind == 3) {
            if (dot > 99) {
                return 1;
            }
        } else {
            if (dot > 19) {
                return 1;
            }
        }
    }

    return 0;
}

void LockonGetDoorScreenPos(s32* x, s32* y) {
    if (gLockonDoorPosition != NULL) {
        *x = (gLockonDoorPosition[0] >> 8) - (gFieldState->x >> 8);
        *y = (gLockonDoorPosition[1] >> 8) + (gLockonDoorPosition[2] >> 8) - (gFieldState->y >> 8) - 24;
    } else {
        *x = 0;
        *y = 0;
    }
}

TaskDesc gTaskDescLockon = {
    "task_lockon",
    (TaskInitFunc)task_lockon_0,
    (TaskUpdateFunc)task_lockon_1,
    (TaskDrawFunc)task_lockon_2,
    (TaskDestroyFunc)task_lockon_3,
    sizeof(LockonWork),
};
