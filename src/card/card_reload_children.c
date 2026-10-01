#include "registration_data.h"
#include "mode_test_api.h"
#include "m4a_song.h"
#include "game_state.h"
#include "monsgage.h"
#include "fade.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "engine_math.h"
#include "listpool.h"
#include "anim.h"
#include "obj.h"
#include "taskpool.h"
#include "gba/syscall.h"
#include "card.h"
#include "game.h"
#include "sprites_btl.h"
#include "sprites_card_pictures.h"
#include "sprites_card.h"
#include "songs.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "card_api.h"
#include "card_def_data.h"
#include "card_types.h"
#include "types.h"
#include "gba/macro.h"
#include <stddef.h>

s32 UpdateReloadChildAbsorb(ReloadChildWork* w);
u8 UpdateReloadSlideOut(ReloadWork* w);

static const s16 sSoraReloadChildOffsetX[4] = { 16, 29, 42, 51 };

static const s16 sRikuReloadChildOffsetX[4] = { -16, -29, -42, -51 };

static const s16 sReloadChildOffsetY[4] = { 0, 0, 0, 24 };

void RELOAD_CHILDREN_0(ReloadChildWork* w, ReloadChildArgs* a) {
    w->args = *a;
    w->tiles = LoadObjTiles(gReloadChildTiles[w->args.listIndex], 128);
    w->palette = LoadObjPalette(gCard00Palette, 32);
    w->tiles2 = NULL;

    switch (w->args.side) {
    case 1:
        if ((s8)w->args.index <= 3) {
            w->offsetX = sSoraReloadChildOffsetX[(s8)w->args.index] << 8;
            w->offsetY = sReloadChildOffsetY[(s8)w->args.index] << 8;
        } else {
            w->offsetX = sSoraReloadChildOffsetX[3] << 8;
            w->offsetY = sReloadChildOffsetY[3] << 8;
        }

        break;
    case 2:
        if ((s8)w->args.index <= 3) {
            w->offsetX = sRikuReloadChildOffsetX[(s8)w->args.index] << 8;
            w->offsetY = sReloadChildOffsetY[(s8)w->args.index] << 8;
        } else {
            w->offsetX = sRikuReloadChildOffsetX[3] << 8;
            w->offsetY = sReloadChildOffsetY[3] << 8;
        }

        break;
    }

    ListNodeInit(&w->node, w->args.pool, w);
    ListPoolAppend(&w->node, w->args.pool);
    w->retractTimer = 0;
}

u8 RELOAD_CHILDREN_1(ReloadChildWork* w, void* a) {
    u8 (*fn)(ReloadChildWork*, void*);

    if (w->args.flags & RELOAD_CHILD_FLAG_IDLE) {
        w->retractTimer++;

        if (w->retractTimer == 30) {
            w->steps = 8;
            fn = UpdateReloadChildRetracted;
            SetTaskUpdate(a, (TaskUpdateFunc)fn);
            return fn(w, a);
        }
    }

    if (w->args.flags & RELOAD_CHILD_FLAG_SHIFTED) {
        w->steps = 8;
        w->args.flags &= ~RELOAD_CHILD_FLAG_SHIFTED;
    }

    if (w->args.index <= 3) {
        switch (w->args.side) {
        case 1:
            ApproachValue(&w->offsetX, sSoraReloadChildOffsetX[(s8)w->args.index] << 8, w->steps);
            break;
        case 2:
            ApproachValue(&w->offsetX, sRikuReloadChildOffsetX[(s8)w->args.index] << 8, w->steps);
            break;
        }

        ApproachValue(&w->offsetY, sReloadChildOffsetY[(s8)w->args.index] << 8, w->steps);
    } else if ((s8)w->args.index < 0) {
        ListPoolRemove(&w->node, w->args.pool);
        w->tiles2 = LoadObjTiles(gCardBacks[w->args.listIndex].tiles2, 0xD00);
        w->steps = 8;
        w->scale = 0x66;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateReloadChildAbsorb);
        return 1;
    }

    if (w->steps != 0) {
        w->steps--;
    }

    w->angle += 8;
    return 1;
}

u8 UpdateReloadChildRetracted(ReloadChildWork* w, void* a) {
    u8 (*f)(ReloadChildWork*, void*);
    u16 v;

    v = w->args.flags & RELOAD_CHILD_FLAG_IDLE;

    if (v == 0) {
        w->steps = 8;
        f = RELOAD_CHILDREN_1;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        w->retractTimer = 0;
        return f(w, a);
    }

    switch (w->args.side) {
    case 1:
        ApproachValue(&w->offsetX, sSoraReloadChildOffsetX[(s8)w->args.index] << 8, w->steps);
        break;
    case 2:
        ApproachValue(&w->offsetX, sRikuReloadChildOffsetX[(s8)w->args.index] << 8, w->steps);
        break;
    }

    ApproachValue(&w->offsetY, sReloadChildOffsetY[3] << 8, w->steps);

    if (w->steps != 0) {
        w->steps--;
    }

    return 1;
}

s32 UpdateReloadChildAbsorb(ReloadChildWork* w) {
    ApproachValue(&w->offsetX, 0, w->steps);
    ApproachValue(&w->offsetY, 0, w->steps);
    ApproachValue(&w->scale, 256, w->steps);

    if (w->steps != 0) {
        w->steps--;
        return 1;
    }

    return 0;
}

void RELOAD_CHILDREN_2(ReloadChildWork* w) {
    s16 x;
    s16 y;
    ObjAffine* aff;

    if (w->args.index <= 3) {
        x = (w->offsetX + *w->args.parentX) >> 8;
        y = (w->offsetY + *w->args.parentY) >> 8;
        DrawSprite(x, y + (gSineTable[w->angle] >> 8), gUnk_09EEA344[0], w->tiles, w->palette, NULL, 0, 50);
    }

    if ((s8)w->args.index < 0) {
        x = (w->offsetX + *w->args.parentX) >> 8;
        y = (w->offsetY + *w->args.parentY) >> 8;
        aff = AllocObjAffine(0, w->scale, w->scale, 0);
        DrawSprite(x, y + (gSineTable[w->angle] >> 8), gCardBacks[w->args.listIndex].gfx2, w->tiles2, w->palette, aff, 0, 49);
    }
}

void RELOAD_CHILDREN_3(ReloadChildWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);

    if (w->tiles2 != NULL) {
        ReleaseObjTiles(w->tiles2);
    }
}

void REV_COUNT_0(RevCountWork* w, RevCountArgs* a) {
    s16* count;
    s16* count2;
    void** row;
    u8 idx;

    CpuFill32(0, w, sizeof(RevCountWork));
    w->args = *a;
    idx = w->args.list;
    w->list = idx;
    w->tiles = AllocSpriteFrameTiles(320);
    w->palette = LoadObjPalette(gCard00Palette, 32);

    if (w->list == 0) {
        count = w->args.count;

        if (*count >= 2 && *count <= 100) {
            row = gRevCountSprites[w->list];
            UpdateSpriteFrameTiles(w->tiles, row[*count - 2], gRevCountTileSources[w->list]);
        } else if (*count > 100) {
            row = gRevCountSprites[w->list];
            UpdateSpriteFrameTiles(w->tiles, row[98], gRevCountTileSources[w->list]);
        } else {
            row = gRevCountSprites[w->list];
            UpdateSpriteFrameTiles(w->tiles, row[0], gRevCountTileSources[w->list]);
        }
    } else {
        count2 = w->args.count;

        if (*count2 >= 1 && *count2 <= 99) {
            row = gRevCountSprites[w->list];
            UpdateSpriteFrameTiles(w->tiles, row[*count2 - 1], gRevCountTileSources[w->list]);
        } else {
            row = gRevCountSprites[w->list];
            UpdateSpriteFrameTiles(w->tiles, row[0], gRevCountTileSources[w->list]);
        }
    }

    w->gfx = AnimGetGfx(&w->anim);
    w->shownCount = *w->args.count;

    switch (w->args.side) {
    case 1:
        w->x = -0x2000;
        w->y = 0x9800;
        break;
    case 2:
        w->x = 0x11000;
        w->y = 0x9800;
        break;
    }

    w->steps = 8;
}

u8 REV_COUNT_1(RevCountWork* w, void* a) {
    s16* count;
    void** row;

    count = w->args.count;

    if (*count != (s16)w->shownCount) {
        if (w->list == 0) {
            if (*count >= 2 && *count <= 100) {
                row = gRevCountSprites[w->list];
                UpdateSpriteFrameTiles(w->tiles, row[*count - 2],
                              gRevCountTileSources[w->list]);
            } else {
                u8 (*f)(RevCountWork*, void*);

                w->steps = 8;
                f = UpdateRevCountEmpty;
                SetTaskUpdate(a, (TaskUpdateFunc)f);
                w->shownCount = *w->args.count;
                return f(w, a);
            }
        } else {
            if (*count >= 1 && *count <= 99) {
                row = gRevCountSprites[w->list];
                UpdateSpriteFrameTiles(w->tiles, row[*count - 1],
                              gRevCountTileSources[w->list]);
            } else {
                u8 (*f)(RevCountWork*, void*);

                w->steps = 8;
                f = UpdateRevCountEmpty;
                SetTaskUpdate(a, (TaskUpdateFunc)f);
                w->shownCount = *w->args.count;
                return f(w, a);
            }
        }

        w->shownCount = *w->args.count;
    } else if (*count <= 0) {
        u8 (*f)(RevCountWork*, void*);

        w->steps = 8;
        f = UpdateRevCountEmpty;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        w->shownCount = *w->args.count;
        return f(w, a);
    }

    switch (w->args.side) {
    case 1:
        ApproachValue(&w->x, 0, w->steps);
        break;
    case 2:
        ApproachValue(&w->x, 0xD800, w->steps);
        break;
    }

    if (w->steps != 0) {
        w->steps--;
    }

    if (w->args.list != *w->args.shownList) {
        u8 (*f)(RevCountWork*, void*);

        f = (u8 (*)(RevCountWork*, void*))UpdateRevCountListChanged;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        w->steps = 8;
        return f(w, a);
    }

    if (gBtlWork->phase == 4) {
        w->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateRevCountHidden);
    }

    if (*w->args.visible == 0) {
        w->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateRevCountHidden);
    }

    return 1;
}

u8 UpdateRevCountListChanged(RevCountWork* w) {
    switch (w->args.side) {
    case 1:
        ApproachValue(&w->x, -0x2000, w->steps);
        break;
    case 2:
        ApproachValue(&w->x, 0x11000, w->steps);
        break;
    }

    if (w->steps != 0) {
        w->steps--;
    }

    if (w->args.list == *w->args.shownList && *w->args.count > 0) {
        return 0;
    }

    return 1;
}

u8 UpdateRevCountHidden(RevCountWork* w, void* a) {
    u8 (*f)(RevCountWork*, void*);

    switch (w->args.side) {
    case 1:
        ApproachValue(&w->x, -0x2000, w->steps);
        break;
    case 2:
        ApproachValue(&w->x, 0x11000, w->steps);
        break;
    }

    if (w->steps == 0) {
        return 0;
    }

    w->steps--;

    if (*w->args.visible == 1) {
        w->steps = 8;
        f = REV_COUNT_1;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        return f(w, a);
    }

    return 1;
}

u8 UpdateRevCountEmpty(RevCountWork* w, void* a) {
    u8 (*f)(RevCountWork*, void*);

    switch (w->args.side) {
    case 1:
        ApproachValue(&w->x, -0x2000, w->steps);
        break;
    case 2:
        ApproachValue(&w->x, 0x11000, w->steps);
        break;
    }

    if (w->steps != 0) {
        w->steps--;
    }

    do {
        if (w->list == 0) {
            if (*w->args.count > 1) {
                f = REV_COUNT_1;
                SetTaskUpdate(a, (TaskUpdateFunc)f);
                w->steps = 8;
                return f(w, a);
            }
        } else {
            if (*w->args.count > 0) {
                f = REV_COUNT_1;
                SetTaskUpdate(a, (TaskUpdateFunc)f);
                w->steps = 8;
                return f(w, a);
            }
        }

        return 1;
    } while (0);
}

#ifdef VERSION_EU
#define REV_COUNT_SPRITE_FLAGS (SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC)
#else
#define REV_COUNT_SPRITE_FLAGS SPRITE_PRIORITY(1)
#endif

void REV_COUNT_2(RevCountWork* w) {
    DrawSprite(w->x >> 8, w->y >> 8, NULL, w->tiles, w->palette, NULL, REV_COUNT_SPRITE_FLAGS, 15);
}

void REV_COUNT_3(RevCountWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void CreateREVCOUNTTask(void* pool, u8* a, s16* b, u8* c, u8 d) {
    RevCountArgs args;

    c[0] = 1;
    args.shownList = a;
    args.count = b;
    args.visible = c;
    args.list = a[0];
    args.side = d;
    TaskCreate(pool, &gTaskDescREVCOUNT, &args);
}

void RELOAD_0(ReloadWork* w, ReloadArgs* a) {
    w->tiles = AllocObjTiles(0xA0, NULL);
    w->palette = LoadObjPalette(gCard00Palette, 32);
    w->args = *a;
    SetObjTileSource(w->tiles, gReloadTiles[w->args.slot]);
    AnimInit(&w->anim, gReloadAnims[w->args.slot], gReloadFrames[w->args.slot]);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);

    switch (w->args.mode) {
    case 1:
        w->x = -0x3000;
        w->y = 0x7E00;
        break;
    case 2:
        w->x = 0xB4800;
        w->y = 0x7E00;
        break;
    }

    w->steps = 6;
}

u8 RELOAD_1(ReloadWork* w, void* a) {
    w->gfx = AnimUpdate(&w->anim);

    switch (w->args.mode) {
    case 1:
        ApproachValue(&w->x, 0x1800, w->steps);
        break;
    case 2:
        ApproachValue(&w->x, 0xD800, w->steps);
        break;
    }

    if (w->steps != 0) {
        w->steps--;
    }

    if (*w->args.state == 0) {
        w->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateReloadSlideOut);
    }

    if (gBtlWork->phase == 4) {
        w->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateReloadSlideOut);
    }

    return 1;
}

u8 UpdateReloadSlideOut(ReloadWork* w) {
    w->gfx = AnimUpdate(&w->anim);

    switch (w->args.mode) {
    case 1:
        ApproachValue(&w->x, -0x3000, w->steps);
        break;
    case 2:
        ApproachValue(&w->x, 0x12000, w->steps);
        break;
    }

    if (w->steps != 0) {
        w->steps--;
        return 1;
    }

    return 0;
}

void RELOAD_2(ReloadWork* w) {
    DrawSprite(w->x >> 8, w->y >> 8, w->gfx, w->tiles, w->palette, NULL, 0, 10);
}

void RELOAD_3(ReloadWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void PrizeBoss_0(BossPrizeWork* w, PrizeCardTaskArgs* args) {
    const CardDef* def;
    const CardBack* back;
    Collider* p;

    w->cardId = args->cardId;
    def = &gCardDefs[args->cardId];
    w->tiles = LoadObjTiles(def->tiles, 0x300);
    w->palette = LoadObjPalette(def->palette, 32);
    w->stat = *(CardStat*)&def->kind;
    back = &gCardBacks[def->category];
    w->tiles2 = LoadObjTiles(back->tiles, 0x280);
    w->tiles3 = LoadObjTiles(back->tiles3, 0x600);
    w->palette2 = LoadObjPalette(gCard00Palette, 32);
    w->tiles4 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    w->tiles5 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    w->palette3 = LoadObjPalette(gBStatesPalette, 32);
    w->posX = args->x;
    w->posY = args->y;
    w->posZ = args->z;
    w->groundZ = 0;
    w->rotation = 24;
    w->vz = -(GetRandom() % 129 + 0x300);
    w->speed = GetRandom() % 129 + 0x80;
    w->unk_E4 = GetRandom() % 256;
    w->scaleX = 0x80;
    w->scaleY = 0x80;
    w->scale = 0x80;
    w->flipAngleY = 0;
    w->flipAngleX = 0;
    p = &w->collider;
    ColliderInit(p, 5, 8, 10);
    ColliderSetDisabled(p, 1);
    ColliderSetPosition(p, w->posX, w->posY, w->posZ);
    w->timer = 0;
    w->collected = 0;
    w->steps = 0;
    w->holdTimer = 0;
    w->effectCount = 0;
    w->effectTimer = 0;
    m4aSongNumStart(SONG_EF_BOSS_DEAD4);
    TaskPoolInit(&w->tasks, 10);
    gBtlWork->prizeCount++;
}

u8 PrizeBoss_1(BossPrizeWork* w, void* a) {
    s16 x;
    s16 y;

    if (w->posZ < 0) {
        w->posZ += 51;
        SpawnBossPrizeCardEffects(w);
    }

    if (gBtlWork->hcEffect == 6) {
        ColliderSetRadius(&w->collider, 30);
    } else {
        ColliderSetRadius(&w->collider, 10);
    }

    ColliderSetPosition(&w->collider, w->posX, w->posY, w->posZ);
    WorldToScreen(&w->x, &w->y, w->posX, w->posY, w->posZ);
    WorldToScreen(&w->x2, &w->y2, w->posX, w->posY, w->groundZ);
    w->priority = -0x1004 - (w->posY >> 8) * 4;
    UpdateBossPrizeScale(w);
    w->flipAngleX += 2;

    if (w->timer == 60) {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->timer <= 59) {
        w->timer++;
    }

    if (w->collider.colliding != 0) {
        w->collected = 1;
        m4aSongNumStart(SONG_SYS_ITEMGET);
        ObtainCard(w->cardId);

        if (gGameState.flags & GAME_FLAG_RIKU) {
            InitRikuDeckForWorld(gGameState.world);
        }

        SetTaskUpdate(a, (TaskUpdateFunc)UpdateBossPrizeFlight);
        WorldToScreen(&x, &y, w->posX, w->posY, w->posZ);
        w->posX = x << 8;
        w->posY = y << 8;
        ColliderSetDisabled(&w->collider, 1);
        w->steps = 16;
        w->priority = 50;
        AimBossPrizeAtCenter(w);
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

void PrizeBoss_2(BossPrizeWork* w) {
    u16 pal;
    ObjAffine* affine;
    void* gfx;
    const CardBack* back;
    const CardDef* def;
    s16 v;

    pal = w->collected == 0 ? GetBattleSpritePriorityFlags(w->posY) : 0;
    affine = AllocObjAffine(w->rotation, w->scaleX, w->scaleY, 1);
    def = &gCardDefs[w->cardId];
    DrawSprite(w->x, (u16)w->y - 8, def->gfx, w->tiles, w->palette, affine, pal,
               w->priority + 1);
    back = &gCardBacks[w->stat.category];
    DrawSprite(w->x, (u16)w->y - 8, back->gfx, w->tiles2, w->palette2, affine, pal,
               w->priority);
    gfx = gUnk_09EE981C[w->stat.value];

    if (def->category != 3) {
        DrawSprite(w->x, (u16)w->y - 8, gfx, w->tiles4, w->palette2, affine, pal,
                   w->priority - 1);
    }

    if (w->collected == 0) {
        v = 204 - ((w->groundZ - w->posZ) >> 7);

        if (v <= 2) {
            v = 2;
        }

        DrawSprite(w->x2, w->y2, gUnk_09EE1380[0], w->tiles5, w->palette3,
                   AllocObjAffine(0, v, v, 0), pal, w->priority + 2);
    }

    TaskPoolDraw(&w->tasks);
}

void PrizeBoss_3(BossPrizeWork* w) {
    FadeSetPaletteExcluded(w->palette2->index + 16, 0);
    FadeSetPaletteExcluded(w->palette->index + 16, 0);
    ColliderUnregister(&w->collider);
    ReleaseObjTiles(w->tiles);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjTiles(w->tiles4);
    ReleaseObjTiles(w->tiles3);
    ReleaseObjTiles(w->tiles5);
    ReleaseObjPalette(w->palette);
    ReleaseObjPalette(w->palette2);
    ReleaseObjPalette(w->palette3);
    TaskPoolDestroy(&w->tasks);
    gBtlWork->prizeCount--;
}

void UpdateBossPrizeScale(BossPrizeWork* w) {
    w->scaleX = (-gSineTable[((w->flipAngleX + 0x80) & 0xFF) + 0x40] * w->scale) >> 8;
    w->scaleY = (-gSineTable[((w->flipAngleY + 0x80) & 0xFF) + 0x40] * w->scale) >> 8;

    if ((u16)(w->scaleX + 2) <= 4) {
        w->scaleX = 2;
    }

    if ((u16)(w->scaleY + 2) <= 4) {
        w->scaleY = 2;
    }
}

void AimBossPrizeAtCenter(BossPrizeWork* w) {
    s16 x;
    s16 y;
    s32 dx;
    s32 dy;
    s32 tx;
    s32 ty;

    WorldToScreen(&x, &y, gBtlWork->actor->x, gBtlWork->actor->y, gBtlWork->actor->z);
    tx = 0x7800;
    ty = 0x5000;
    dx = tx - w->posX;
    dy = ty - w->posY;
    w->distance = NormalizeVector2D8(&dx, &dy);
    w->dirX = -dx;
    w->dirY = -dy;
    w->speed = 0x300;
    w->vz = 2;
}

u8 UpdateBossPrizeFlight(BossPrizeWork* w, void* a) {
    s32 dx;
    s32 dy;
    u8 z;
    u8 t;
    s32 x;
    s32 y;
    s16* q1;
    s16* q2;

    if (w->speed < 0) {
        dx = 0x7800 - w->posX;
        dy = 0x5000 - w->posY;
        NormalizeVector2D8(&dx, &dy);
        w->dirX = -dx;
        w->dirY = -dy;

        if (w->distance <= 0x7FF) {
            w->steps = 0;
            w->rotation = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateBossPrizeShow);
#ifdef VERSION_EU
            CreateCardNameDisplay(&w->tasks, eu_0805E924(gCardDefs[w->cardId].name));
#else
            CreateCardNameDisplay(&w->tasks, gCardDefs[w->cardId].name);
#endif
        }
    }

    w->posX += (w->dirX * w->speed) >> 8;
    w->posY += (w->dirY * w->speed) >> 8;
    t = w->rotation + 32;
    z = 0;
    w->rotation = t;
    w->flipAngleY += (64 - w->flipAngleY) >> 4;
    w->flipAngleX = z;
    w->distance = VectorLength2D(0x7800 - w->posX, 0x5000 - w->posY);
    w->speed -= w->vz;
    w->vz += 2;

    if (w->scale <= 0xFF) {
        w->scale += 3;
    }

    x = w->posX >> 8;
    q1 = &w->x;
    *q1 = x;
    y = w->posY >> 8;
    q2 = &w->y;
    *q2 = y;
    UpdateBossPrizeScale(w);
    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 UpdateBossPrizeShow(BossPrizeWork* w, void* a) {
    s32 v;
    u16 t;
    s32 c;

    v = w->rotation << 8;
    ApproachValue((s32*)&w->flipAngleY, 0, w->steps);
    ApproachValue(&v, 0, w->steps);
    ApproachValue(&w->posX, 0x7800, w->steps);
    ApproachValue(&w->posY, 0x5800, w->steps);
    w->rotation = v >> 8;

    if (w->steps != 0) {
        w->steps--;
    }

    t = w->scale;

    if ((s16)t <= 0xFF) {
        w->scale = t + 2;
    } else {
        c = 0x100;
        w->scale = c;
    }

    w->x = w->posX >> 8;
    w->y = w->posY >> 8;
    UpdateBossPrizeScale(w);
    w->holdTimer++;

    if ((u32)w->cardId > 0x1C2) {
        if (w->holdTimer == 120) {
            w->holdTimer = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateBossPrizeShrink);
        }
    } else {
        if (w->holdTimer == 30) {
            w->holdTimer = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateBossPrizeShrink);
        }
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 UpdateBossPrizeShrink(BossPrizeWork* w) {
    w->rotation += 32;
    WorldToScreen(&w->x3, &w->y3, gBtlWork->actor->x, gBtlWork->actor->y, gBtlWork->actor->z);
    w->x += (w->x3 - w->x) >> 3;
    w->y += (w->y3 - w->y) >> 3;
    w->scaleX -= 10;
    w->scaleY -= 10;

    if (w->scaleX <= 10) {
        return 0;
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

void SpawnBossPrizeCardEffects(BossPrizeWork* w) {
    CardEffectArgs args;

    if (w->collected == 0) {
        if (w->effectTimer == 8) {
            if (w->effectCount <= 3) {
                args.x = w->posX;
                args.y = w->posY;
                args.z = w->posZ;
                args.screenSpace = w->collected;
                args.count = &w->effectCount;
                TaskCreate(&w->tasks, &gTaskDescCardEFFECT, &args);
            }

            w->effectTimer = 0;
        } else {
            w->effectTimer++;
        }
    } else {
        if (w->effectTimer == 8) {
            if (w->effectCount <= 7) {
                args.x = w->posX;
                args.y = w->posY;
                args.z = w->posZ;
                args.screenSpace = w->collected;
                args.count = &w->effectCount;
                TaskCreate(&w->tasks, &gTaskDescCardEFFECT, &args);
            }

            w->effectTimer = 0;
        } else {
            w->effectTimer++;
        }
    }
}

void Card_EFFECT_0(CardEffectWork* w, CardEffectArgs* a) {
    w->args = *a;

    if (w->args.screenSpace == 0) {
        w->posX = a->x + ((GetRandom() % 9 - 4) << 8);
        w->posY = a->y;
        w->posZ = a->z - 0x800;
    } else {
        w->posX = a->x + ((GetRandom() % 33 - 16) << 8);
        w->posY = a->y - 0x1000;
        w->posZ = 0;
    }

    w->tiles = AllocObjTiles(0x80, NULL);
    w->palette = LoadObjPalette(gUnk_09619158, 32);
    SetObjTileSource(w->tiles, gUnk_093F762E);
    AnimInit(&w->anim, gUnk_09EF1260, gUnk_09EF1230);
    AnimStart(&w->anim, GetRandom() % 3, 0);
    w->gfx = AnimGetGfx(&w->anim);
    (*w->args.count)++;
}

u8 Card_EFFECT_1(CardEffectWork* w) {
    w->gfx = AnimUpdate(&w->anim);

    if (w->args.screenSpace == 0) {
        WorldToScreen(&w->x, &w->y, w->posX, w->posY, w->posZ);
        w->posZ -= 0x100;
    } else {
        w->x = w->posX >> 8;
        w->y = w->posY >> 8;
        w->posY -= 0x100;
    }

    if (AnimIsFinished(&w->anim)) {
        return 0;
    }

    return 1;
}

void Card_EFFECT_2(CardEffectWork* w) {
    s16 t;
    s32 z;

    t = -4100 - ((w->y >> 8) * 4);
    z = 0;
    w->priority = t;
    DrawSprite(w->x, w->y, w->gfx, w->tiles, w->palette, NULL, z, w->priority);
}

void Card_EFFECT_3(CardEffectWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    w->args.count[0]--;
}

void scrollbar_0(ScrollBarWork* w, u16* args) {
    w->unk_08 = args[0];
    w->unk_0A = args[1];
    w->unk_0C = args[2];
    w->position = args[3];
    w->remaining = args[4];
    w->active = 1;
    w->unk_0E = 0;
    w->unk_17 = 0;
}

u8 scrollbar_1(ScrollBarWork* w) {
    return w->active;
}

void scrollbar_2() {
}

void scrollbar_3() {
}

void ScrollbarRequestClose(ScrollBarWork* w) {
    if (w != NULL) {
        w->active = 0;
    }
}

void ScrollbarAdvance(ScrollBarWork* w) {
    if (w != NULL) {
        if (w->remaining != 0) {
            w->position++;
            w->remaining--;
        } else {
            w->remaining = w->count - 1;
            w->position = 0;
        }
    }
}

void ScrollbarRetreat(ScrollBarWork* w) {
    if (w != NULL) {
        if (w->position != 0) {
            w->position--;
            w->remaining++;
        } else {
            w->position = w->count - 1;
            w->remaining = 0;
        }
    }
}

void ScrollbarDecrementCount(ScrollBarWork* w) {
    if (w != NULL) {
        w->count--;
    }
}

void ScrollbarIncrementCount(ScrollBarWork* w) {
    if (w != NULL) {
        w->count++;
    }
}

void func_08099FE8(ScrollBarWork* w, u16 b, u8 c) {
    if (w != NULL) {
        w->unk_0E = b;
        w->unk_17 = c;
    }
}

ScrollBarWork* CreateScrollbar(void* pool, u16 a, u16 b, u16 c, u16 d, u16 e) {
    u16 args[5];

    args[0] = a;
    args[1] = b;
    args[2] = c;
    args[3] = d;
    args[4] = e;
    return TaskCreate(pool, &gTaskDescScrollbar, args)->work;
}

void* gReloadChildTiles[4] = {
    gUnk_090994A4,
    gUnk_0909937C,
    gUnk_09099410,
    gUnk_09099538,
};

TaskDesc gTaskDescReloadChildren = {
    "RELOAD_CHILDREN",
    (TaskInitFunc)RELOAD_CHILDREN_0,
    (TaskUpdateFunc)RELOAD_CHILDREN_1,
    (TaskDrawFunc)RELOAD_CHILDREN_2,
    (TaskDestroyFunc)RELOAD_CHILDREN_3,
    sizeof(ReloadChildWork),
};

void* gRevCountTileSources[4] = {
    gUnk_0909D2AC,
    gUnk_0909D2AC,
    gUnk_0909D2AC,
    gUnk_0909D2AC,
};

void** gRevCountSprites[4] = {
    gUnk_09EEA5C4,
    gUnk_09EEA5C4,
    gUnk_09EEA5C4,
    gUnk_09EEA5C4,
};

AnimHeader** gUnk_09EE76E0 = &gUnk_09EEA750;

AnimHeader** gUnk_09EE76E4 = &gUnk_09EEABA8;

AnimHeader** gUnk_09EE76E8 = &gUnk_09EEA97C;

AnimHeader** gUnk_09EE76EC = &gUnk_09EEADD4;

TaskDesc gTaskDescREVCOUNT = {
    "REV_COUNT",
    (TaskInitFunc)REV_COUNT_0,
    (TaskUpdateFunc)REV_COUNT_1,
    (TaskDrawFunc)REV_COUNT_2,
    (TaskDestroyFunc)REV_COUNT_3,
    sizeof(RevCountWork),
};

void* gReloadTiles[3] = {
    gUnk_0909885E,
    gUnk_09098E0E,
    gUnk_09098B36,
};

AnimHeader** gReloadAnims[3] = {
    gUnk_09EEA304,
    gUnk_09EEA32C,
    gUnk_09EEA318,
};

void** gReloadFrames[3] = {
    gUnk_09EEA2F4,
    gUnk_09EEA31C,
    gUnk_09EEA308,
};

TaskDesc gTaskDescRELOAD = {
    "RELOAD",
    (TaskInitFunc)RELOAD_0,
    (TaskUpdateFunc)RELOAD_1,
    (TaskDrawFunc)RELOAD_2,
    (TaskDestroyFunc)RELOAD_3,
    sizeof(ReloadWork),
};

TaskDesc gTaskDescPrizeBoss = {
    "PrizeBoss",
    (TaskInitFunc)PrizeBoss_0,
    (TaskUpdateFunc)PrizeBoss_1,
    (TaskDrawFunc)PrizeBoss_2,
    (TaskDestroyFunc)PrizeBoss_3,
    sizeof(BossPrizeWork),
};

TaskDesc gTaskDescCardEFFECT = {
    "Card_EFFECT",
    (TaskInitFunc)Card_EFFECT_0,
    (TaskUpdateFunc)Card_EFFECT_1,
    (TaskDrawFunc)Card_EFFECT_2,
    (TaskDestroyFunc)Card_EFFECT_3,
    sizeof(CardEffectWork),
};

TaskDesc gTaskDescScrollbar = {
    "scrollbar",
    (TaskInitFunc)scrollbar_0,
    (TaskUpdateFunc)scrollbar_1,
    (TaskDrawFunc)scrollbar_2,
    (TaskDestroyFunc)scrollbar_3,
    sizeof(ScrollBarWork),
};
