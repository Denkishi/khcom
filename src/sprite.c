#include "obj_api.h"
#include "display.h"
#include "gba/syscall.h"
#include "listpool.h"
#include "malloc.h"
#include "sprite.h"
#include "gba/io_reg.h"
#include <stddef.h>
#include "gba/oam.h"

static const u8 sSpriteHeapName[8] = "SPRITE";

SpriteWork* gSpriteWork;

void SpriteInit(void) {
    u32 zero;

    SetIwramHeapName(sSpriteHeapName);
    gSpriteWork = IwramAlloc(sizeof(SpriteWork));
    zero = 0;
    CpuSet(&zero, gSpriteWork, CPU_SET_SRC_FIXED | CPU_SET_32BIT | (sizeof(SpriteWork) / 4));
}

void SpriteFree(void) {
    IwramFree(gSpriteWork);
}

u16 GetObjTileCount(u16 a, u16 b) {
    switch ((((u32)b << 16) | a) & OAM_SHAPE_SIZE(OAM_SHAPE_MASK, 3)) {
    case OAM_SHAPE_SIZE(OAM_SHAPE_SQUARE, 0):
        return 1;
    case OAM_SHAPE_SIZE(OAM_SHAPE_SQUARE, 2):
        return 0x10;
    case OAM_SHAPE_SIZE(OAM_SHAPE_SQUARE, 3):
        return 0x40;
    case OAM_SHAPE_SIZE(OAM_SHAPE_HORIZONTAL, 0):
    case OAM_SHAPE_SIZE(OAM_SHAPE_VERTICAL, 0):
        return 2;
    case OAM_SHAPE_SIZE(OAM_SHAPE_SQUARE, 1):
    case OAM_SHAPE_SIZE(OAM_SHAPE_HORIZONTAL, 1):
    case OAM_SHAPE_SIZE(OAM_SHAPE_VERTICAL, 1):
        return 4;
    case OAM_SHAPE_SIZE(OAM_SHAPE_HORIZONTAL, 2):
    case OAM_SHAPE_SIZE(OAM_SHAPE_VERTICAL, 2):
        return 8;
    case OAM_SHAPE_SIZE(OAM_SHAPE_HORIZONTAL, 3):
    case OAM_SHAPE_SIZE(OAM_SHAPE_VERTICAL, 3):
        return 0x20;
    }

    return 0;
}

void SortSpriteEntries(SpriteEntry** arr, s32 lo, s32 hi) {
    SpriteEntry* t;
    u16 pivot;
    s32 i;
    s32 j;

    pivot = arr[(lo + hi) >> 1]->priority;
    i = lo;
    j = hi;

    for (;;) {
        while (arr[i]->priority < pivot) {
            i++;
        }

        while (pivot < arr[j]->priority) {
            j--;
        }

        if (i >= j) {
            break;
        }

        t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
        i++;
        j--;
    }

    if (lo < i - 1) {
        SortSpriteEntries(arr, lo, i - 1);
    }

    if (j + 1 < hi) {
        SortSpriteEntries(arr, j + 1, hi);
    }
}

void EnableObj(void) {
    gDispCnt |= DISPCNT_OBJ_ON;
}

void DisableObj(void) {
    gDispCnt &= ~DISPCNT_OBJ_ON;
}

void SetObjTileRange(u16 a, u16 b) {
    s32 v;

    gSpriteWork->tilePool.rangeStart = a;
    v = a + b;
    gSpriteWork->tilePool.rangeEnd = v;

    if ((u16)v > 0x400) {
        gSpriteWork->tilePool.rangeEnd = 0x400;
    }
}

void SetObjPaletteRange(u16 a, u16 b) {
    s32 v;

    gSpriteWork->palettePool.rangeStart = a;
    v = a + b;
    gSpriteWork->palettePool.rangeEnd = v;

    if ((u16)v > 0x10) {
        gSpriteWork->palettePool.rangeEnd = 0x10;
    }
}

void SpriteReset(void) {
    s32 i;

    EnableObj();
    ListPoolInit(&gSpriteWork->tilePool);

    for (i = 0; i < 128; i++) {
        ListPoolAddFree(&gSpriteWork->tiles[i].node, &gSpriteWork->tilePool, &gSpriteWork->tiles[i]);
    }

    ListPoolInit(&gSpriteWork->palettePool);

    for (i = 0; i < 16; i++) {
        ListPoolAddFree(&gSpriteWork->palettes[i].node, &gSpriteWork->palettePool,
                      &gSpriteWork->palettes[i]);
    }

    gSpriteWork->entryCount = 0;
    gSpriteWork->affineCount = 0;
    gSpriteWork->sortLo = 0;
    SetObjMosaicSize(0, 0);
    gSpriteWork->oamUpdatesPaused = 0;
    gSpriteWork->mosaicEnabled = 0;
    SetObjTileRange(0, 0x400);
    SetObjPaletteRange(0, 0x10);
}

u8 DrawSpriteSharedTiles(s16 x, s16 y, void* c, void* obj, void* e, ObjAffine* f, u16 g, u16 h) {
    SpriteWork* p;

    if (e != NULL && c != NULL) {
        p = gSpriteWork;
        p->entries[p->entryCount].x = x;
        p->entries[p->entryCount].y = y;
        p->entries[p->entryCount].tiles = obj;
        p->entries[p->entryCount].palette = e;
        p->entries[p->entryCount].affine = f;
        p->entries[p->entryCount].flags = g;
        p->entries[p->entryCount].priority = h;
        p->entries[p->entryCount].sprite = c;
        p->sortPtrs[p->entryCount] = &p->entries[p->entryCount];
        p->entryCount += 1;
        return 1;
    }

    return 0;
}
