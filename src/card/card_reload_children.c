/**
 * card_reload_children.c
 * Card Reload, Boss Prize and Scrollbar
 */

#include "registration_data.h"
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
#include "card.h"
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
#include "lockon.h"
#include "card_reload_children.h"
#include "sprite_palettes.h"

static const s16 sSoraReloadChildOffsetX[4] = { 16, 29, 42, 51 };

static const s16 sRikuReloadChildOffsetX[4] = { -16, -29, -42, -51 };

static const s16 sReloadChildOffsetY[4] = { 0, 0, 0, 24 };

void RELOAD_CHILDREN_0(ReloadChildWork* work, ReloadChildArgs* a) {
    work->args = *a;
    work->tiles = LoadObjTiles(gReloadChildTiles[work->args.listIndex], 128);
    work->palette = LoadObjPalette(gCard00Palette, 32);
    work->tiles2 = NULL;

    switch (work->args.side) {
    case 1:
        if ((s8)work->args.index <= 3) {
            work->offsetX = sSoraReloadChildOffsetX[(s8)work->args.index] << 8;
            work->offsetY = sReloadChildOffsetY[(s8)work->args.index] << 8;
        } else {
            work->offsetX = sSoraReloadChildOffsetX[3] << 8;
            work->offsetY = sReloadChildOffsetY[3] << 8;
        }

        break;
    case 2:
        if ((s8)work->args.index <= 3) {
            work->offsetX = sRikuReloadChildOffsetX[(s8)work->args.index] << 8;
            work->offsetY = sReloadChildOffsetY[(s8)work->args.index] << 8;
        } else {
            work->offsetX = sRikuReloadChildOffsetX[3] << 8;
            work->offsetY = sReloadChildOffsetY[3] << 8;
        }

        break;
    }

    ListNodeInit(&work->node, work->args.pool, work);
    ListPoolAppend(&work->node, work->args.pool);
    work->retractTimer = 0;
}

u8 RELOAD_CHILDREN_1(ReloadChildWork* work, void* a) {
    u8 (*fn)(ReloadChildWork*, void*);

    if (work->args.flags & RELOAD_CHILD_FLAG_IDLE) {
        work->retractTimer++;

        if (work->retractTimer == 30) {
            work->steps = 8;
            fn = UpdateReloadChildRetracted;
            SetTaskUpdate(a, (TaskUpdateFunc)fn);
            return fn(work, a);
        }
    }

    if (work->args.flags & RELOAD_CHILD_FLAG_SHIFTED) {
        work->steps = 8;
        work->args.flags &= ~RELOAD_CHILD_FLAG_SHIFTED;
    }

    if (work->args.index <= 3) {
        switch (work->args.side) {
        case 1:
            ApproachValue(&work->offsetX, sSoraReloadChildOffsetX[(s8)work->args.index] << 8, work->steps);
            break;
        case 2:
            ApproachValue(&work->offsetX, sRikuReloadChildOffsetX[(s8)work->args.index] << 8, work->steps);
            break;
        }

        ApproachValue(&work->offsetY, sReloadChildOffsetY[(s8)work->args.index] << 8, work->steps);
    } else if ((s8)work->args.index < 0) {
        ListPoolRemove(&work->node, work->args.pool);
        work->tiles2 = LoadObjTiles(gCardBacks[work->args.listIndex].tiles2, 0xD00);
        work->steps = 8;
        work->scale = 0x66;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateReloadChildAbsorb);
        return 1;
    }

    if (work->steps != 0) {
        work->steps--;
    }

    work->angle += 8;
    return 1;
}

u8 UpdateReloadChildRetracted(ReloadChildWork* work, void* a) {
    u8 (*f)(ReloadChildWork*, void*);
    u16 v;

    v = work->args.flags & RELOAD_CHILD_FLAG_IDLE;

    if (v == 0) {
        work->steps = 8;
        f = RELOAD_CHILDREN_1;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        work->retractTimer = 0;
        return f(work, a);
    }

    switch (work->args.side) {
    case 1:
        ApproachValue(&work->offsetX, sSoraReloadChildOffsetX[(s8)work->args.index] << 8, work->steps);
        break;
    case 2:
        ApproachValue(&work->offsetX, sRikuReloadChildOffsetX[(s8)work->args.index] << 8, work->steps);
        break;
    }

    ApproachValue(&work->offsetY, sReloadChildOffsetY[3] << 8, work->steps);

    if (work->steps != 0) {
        work->steps--;
    }

    return 1;
}

s32 UpdateReloadChildAbsorb(ReloadChildWork* work) {
    ApproachValue(&work->offsetX, 0, work->steps);
    ApproachValue(&work->offsetY, 0, work->steps);
    ApproachValue(&work->scale, 256, work->steps);

    if (work->steps != 0) {
        work->steps--;
        return 1;
    }

    return 0;
}

void RELOAD_CHILDREN_2(ReloadChildWork* work) {
    s16 x;
    s16 y;
    ObjAffine* aff;

    if (work->args.index <= 3) {
        x = (work->offsetX + *work->args.parentX) >> 8;
        y = (work->offsetY + *work->args.parentY) >> 8;
        DrawSprite(x, y + (gSineTable[work->angle] >> 8), gUnk_09EEA344[0], work->tiles, work->palette, NULL, 0, 50);
    }

    if ((s8)work->args.index < 0) {
        x = (work->offsetX + *work->args.parentX) >> 8;
        y = (work->offsetY + *work->args.parentY) >> 8;
        aff = AllocObjAffine(0, work->scale, work->scale, 0);
        DrawSprite(x, y + (gSineTable[work->angle] >> 8), gCardBacks[work->args.listIndex].gfx2, work->tiles2, work->palette, aff, 0, 49);
    }
}

void RELOAD_CHILDREN_3(ReloadChildWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);

    if (work->tiles2 != NULL) {
        ReleaseObjTiles(work->tiles2);
    }
}

void REV_COUNT_0(RevCountWork* work, RevCountArgs* a) {
    s16* count;
    s16* count2;
    void** row;
    u8 idx;

    CpuFill32(0, work, sizeof(RevCountWork));
    work->args = *a;
    idx = work->args.list;
    work->list = idx;
    work->tiles = AllocSpriteFrameTiles(320);
    work->palette = LoadObjPalette(gCard00Palette, 32);

    if (work->list == 0) {
        count = work->args.count;

        if (*count >= 2 && *count <= 100) {
            row = gRevCountSprites[work->list];
            UpdateSpriteFrameTiles(work->tiles, row[*count - 2], gRevCountTileSources[work->list]);
        } else if (*count > 100) {
            row = gRevCountSprites[work->list];
            UpdateSpriteFrameTiles(work->tiles, row[98], gRevCountTileSources[work->list]);
        } else {
            row = gRevCountSprites[work->list];
            UpdateSpriteFrameTiles(work->tiles, row[0], gRevCountTileSources[work->list]);
        }
    } else {
        count2 = work->args.count;

        if (*count2 >= 1 && *count2 <= 99) {
            row = gRevCountSprites[work->list];
            UpdateSpriteFrameTiles(work->tiles, row[*count2 - 1], gRevCountTileSources[work->list]);
        } else {
            row = gRevCountSprites[work->list];
            UpdateSpriteFrameTiles(work->tiles, row[0], gRevCountTileSources[work->list]);
        }
    }

    work->gfx = AnimGetGfx(&work->anim);
    work->shownCount = *work->args.count;

    switch (work->args.side) {
    case 1:
        work->x = -0x2000;
        work->y = 0x9800;
        break;
    case 2:
        work->x = 0x11000;
        work->y = 0x9800;
        break;
    }

    work->steps = 8;
}

u8 REV_COUNT_1(RevCountWork* work, void* a) {
    s16* count;
    void** row;

    count = work->args.count;

    if (*count != (s16)work->shownCount) {
        if (work->list == 0) {
            if (*count >= 2 && *count <= 100) {
                row = gRevCountSprites[work->list];
                UpdateSpriteFrameTiles(work->tiles, row[*count - 2],
                              gRevCountTileSources[work->list]);
            } else {
                u8 (*f)(RevCountWork*, void*);

                work->steps = 8;
                f = UpdateRevCountEmpty;
                SetTaskUpdate(a, (TaskUpdateFunc)f);
                work->shownCount = *work->args.count;
                return f(work, a);
            }
        } else {
            if (*count >= 1 && *count <= 99) {
                row = gRevCountSprites[work->list];
                UpdateSpriteFrameTiles(work->tiles, row[*count - 1],
                              gRevCountTileSources[work->list]);
            } else {
                u8 (*f)(RevCountWork*, void*);

                work->steps = 8;
                f = UpdateRevCountEmpty;
                SetTaskUpdate(a, (TaskUpdateFunc)f);
                work->shownCount = *work->args.count;
                return f(work, a);
            }
        }

        work->shownCount = *work->args.count;
    } else if (*count <= 0) {
        u8 (*f)(RevCountWork*, void*);

        work->steps = 8;
        f = UpdateRevCountEmpty;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        work->shownCount = *work->args.count;
        return f(work, a);
    }

    switch (work->args.side) {
    case 1:
        ApproachValue(&work->x, 0, work->steps);
        break;
    case 2:
        ApproachValue(&work->x, 0xD800, work->steps);
        break;
    }

    if (work->steps != 0) {
        work->steps--;
    }

    if (work->args.list != *work->args.shownList) {
        u8 (*f)(RevCountWork*, void*);

        f = (u8 (*)(RevCountWork*, void*))UpdateRevCountListChanged;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        work->steps = 8;
        return f(work, a);
    }

    if (gBtlWork->phase == 4) {
        work->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateRevCountHidden);
    }

    if (*work->args.visible == 0) {
        work->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateRevCountHidden);
    }

    return 1;
}

u8 UpdateRevCountListChanged(RevCountWork* work) {
    switch (work->args.side) {
    case 1:
        ApproachValue(&work->x, -0x2000, work->steps);
        break;
    case 2:
        ApproachValue(&work->x, 0x11000, work->steps);
        break;
    }

    if (work->steps != 0) {
        work->steps--;
    }

    if (work->args.list == *work->args.shownList && *work->args.count > 0) {
        return 0;
    }

    return 1;
}

u8 UpdateRevCountHidden(RevCountWork* work, void* a) {
    u8 (*f)(RevCountWork*, void*);

    switch (work->args.side) {
    case 1:
        ApproachValue(&work->x, -0x2000, work->steps);
        break;
    case 2:
        ApproachValue(&work->x, 0x11000, work->steps);
        break;
    }

    if (work->steps == 0) {
        return 0;
    }

    work->steps--;

    if (*work->args.visible == 1) {
        work->steps = 8;
        f = REV_COUNT_1;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        return f(work, a);
    }

    return 1;
}

u8 UpdateRevCountEmpty(RevCountWork* work, void* a) {
    u8 (*f)(RevCountWork*, void*);

    switch (work->args.side) {
    case 1:
        ApproachValue(&work->x, -0x2000, work->steps);
        break;
    case 2:
        ApproachValue(&work->x, 0x11000, work->steps);
        break;
    }

    if (work->steps != 0) {
        work->steps--;
    }

    // fakematch
    do {
        if (work->list == 0) {
            if (*work->args.count > 1) {
                f = REV_COUNT_1;
                SetTaskUpdate(a, (TaskUpdateFunc)f);
                work->steps = 8;
                return f(work, a);
            }
        } else {
            if (*work->args.count > 0) {
                f = REV_COUNT_1;
                SetTaskUpdate(a, (TaskUpdateFunc)f);
                work->steps = 8;
                return f(work, a);
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

void REV_COUNT_2(RevCountWork* work) {
    DrawSprite(work->x >> 8, work->y >> 8, NULL, work->tiles, work->palette, NULL, REV_COUNT_SPRITE_FLAGS, 15);
}

void REV_COUNT_3(RevCountWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
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

void RELOAD_0(ReloadWork* work, ReloadArgs* a) {
    work->tiles = AllocObjTiles(0xA0, NULL);
    work->palette = LoadObjPalette(gCard00Palette, 32);
    work->args = *a;
    SetObjTileSource(work->tiles, gReloadTiles[work->args.slot]);
    AnimInit(&work->anim, gReloadAnims[work->args.slot], gReloadFrames[work->args.slot]);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);

    switch (work->args.mode) {
    case 1:
        work->x = -0x3000;
        work->y = 0x7E00;
        break;
    case 2:
        work->x = 0xB4800;
        work->y = 0x7E00;
        break;
    }

    work->steps = 6;
}

u8 RELOAD_1(ReloadWork* work, void* a) {
    work->gfx = AnimUpdate(&work->anim);

    switch (work->args.mode) {
    case 1:
        ApproachValue(&work->x, 0x1800, work->steps);
        break;
    case 2:
        ApproachValue(&work->x, 0xD800, work->steps);
        break;
    }

    if (work->steps != 0) {
        work->steps--;
    }

    if (*work->args.state == 0) {
        work->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateReloadSlideOut);
    }

    if (gBtlWork->phase == 4) {
        work->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateReloadSlideOut);
    }

    return 1;
}

u8 UpdateReloadSlideOut(ReloadWork* work) {
    work->gfx = AnimUpdate(&work->anim);

    switch (work->args.mode) {
    case 1:
        ApproachValue(&work->x, -0x3000, work->steps);
        break;
    case 2:
        ApproachValue(&work->x, 0x12000, work->steps);
        break;
    }

    if (work->steps != 0) {
        work->steps--;
        return 1;
    }

    return 0;
}

void RELOAD_2(ReloadWork* work) {
    DrawSprite(work->x >> 8, work->y >> 8, work->gfx, work->tiles, work->palette, NULL, 0, 10);
}

void RELOAD_3(ReloadWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void PrizeBoss_0(BossPrizeWork* work, PrizeCardTaskArgs* args) {
    const CardDef* def;
    const CardBack* back;
    Collider* p;

    work->cardId = args->cardId;
    def = &gCardDefs[args->cardId];
    work->tiles = LoadObjTiles(def->tiles, 0x300);
    work->palette = LoadObjPalette(def->palette, 32);
    work->stat = *(CardStat*)&def->kind;
    back = &gCardBacks[def->category];
    work->tiles2 = LoadObjTiles(back->tiles, 0x280);
    work->tiles3 = LoadObjTiles(back->tiles3, 0x600);
    work->palette2 = LoadObjPalette(gCard00Palette, 32);
    work->tiles4 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    work->tiles5 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    work->palette3 = LoadObjPalette(gBStatesPalette, 32);
    work->posX = args->x;
    work->posY = args->y;
    work->posZ = args->z;
    work->groundZ = 0;
    work->rotation = 24;
    work->vz = -(GetRandom() % 129 + 0x300);
    work->speed = GetRandom() % 129 + 0x80;
    work->unk_E4 = GetRandom() % 256;
    work->scaleX = 0x80;
    work->scaleY = 0x80;
    work->scale = 0x80;
    work->flipAngleY = 0;
    work->flipAngleX = 0;
    p = &work->collider;
    ColliderInit(p, 5, 8, 10);
    ColliderSetDisabled(p, 1);
    ColliderSetPosition(p, work->posX, work->posY, work->posZ);
    work->timer = 0;
    work->collected = 0;
    work->steps = 0;
    work->holdTimer = 0;
    work->effectCount = 0;
    work->effectTimer = 0;
    m4aSongNumStart(SONG_EF_BOSS_DEAD4);
    TaskPoolInit(&work->tasks, 10);
    gBtlWork->prizeCount++;
}

u8 PrizeBoss_1(BossPrizeWork* work, void* a) {
    s16 x;
    s16 y;

    if (work->posZ < 0) {
        work->posZ += 51;
        SpawnBossPrizeCardEffects(work);
    }

    if (gBtlWork->hcEffect == 6) {
        ColliderSetRadius(&work->collider, 30);
    } else {
        ColliderSetRadius(&work->collider, 10);
    }

    ColliderSetPosition(&work->collider, work->posX, work->posY, work->posZ);
    WorldToScreen(&work->x, &work->y, work->posX, work->posY, work->posZ);
    WorldToScreen(&work->x2, &work->y2, work->posX, work->posY, work->groundZ);
    work->priority = -0x1004 - (work->posY >> 8) * 4;
    UpdateBossPrizeScale(work);
    work->flipAngleX += 2;

    if (work->timer == 60) {
        ColliderSetDisabled(&work->collider, 0);
    }

    if (work->timer <= 59) {
        work->timer++;
    }

    if (work->collider.colliding) {
        work->collected = 1;
        m4aSongNumStart(SONG_SYS_ITEMGET);
        ObtainCard(work->cardId);

        if (gGameState.flags & GAME_FLAG_RIKU) {
            InitRikuDeckForWorld(gGameState.world);
        }

        SetTaskUpdate(a, (TaskUpdateFunc)UpdateBossPrizeFlight);
        WorldToScreen(&x, &y, work->posX, work->posY, work->posZ);
        work->posX = x << 8;
        work->posY = y << 8;
        ColliderSetDisabled(&work->collider, 1);
        work->steps = 16;
        work->priority = 50;
        AimBossPrizeAtCenter(work);
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void PrizeBoss_2(BossPrizeWork* work) {
    u16 pal;
    ObjAffine* affine;
    void* gfx;
    const CardBack* back;
    const CardDef* def;
    s16 v;

    pal = !work->collected ? GetBattleSpritePriorityFlags(work->posY) : 0;
    affine = AllocObjAffine(work->rotation, work->scaleX, work->scaleY, 1);
    def = &gCardDefs[work->cardId];
    DrawSprite(work->x, (u16)work->y - 8, def->gfx, work->tiles, work->palette, affine, pal,
               work->priority + 1);
    back = &gCardBacks[work->stat.category];
    DrawSprite(work->x, (u16)work->y - 8, back->gfx, work->tiles2, work->palette2, affine, pal,
               work->priority);
    gfx = gUnk_09EE981C[work->stat.value];

    if (def->category != 3) {
        DrawSprite(work->x, (u16)work->y - 8, gfx, work->tiles4, work->palette2, affine, pal,
                   work->priority - 1);
    }

    if (!work->collected) {
        v = 204 - ((work->groundZ - work->posZ) >> 7);

        if (v <= 2) {
            v = 2;
        }

        DrawSprite(work->x2, work->y2, gUnk_09EE1380[0], work->tiles5, work->palette3,
                   AllocObjAffine(0, v, v, 0), pal, work->priority + 2);
    }

    TaskPoolDraw(&work->tasks);
}

void PrizeBoss_3(BossPrizeWork* work) {
    FadeSetPaletteExcluded(work->palette2->index + 16, 0);
    FadeSetPaletteExcluded(work->palette->index + 16, 0);
    ColliderUnregister(&work->collider);
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles4);
    ReleaseObjTiles(work->tiles3);
    ReleaseObjTiles(work->tiles5);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
    ReleaseObjPalette(work->palette3);
    TaskPoolDestroy(&work->tasks);
    gBtlWork->prizeCount--;
}

void UpdateBossPrizeScale(BossPrizeWork* work) {
    work->scaleX = (-COS(work->flipAngleX + 0x80) * work->scale) >> 8;
    work->scaleY = (-COS(work->flipAngleY + 0x80) * work->scale) >> 8;

    if ((u16)(work->scaleX + 2) <= 4) {
        work->scaleX = 2;
    }

    if ((u16)(work->scaleY + 2) <= 4) {
        work->scaleY = 2;
    }
}

void AimBossPrizeAtCenter(BossPrizeWork* work) {
    s16 x;
    s16 y;
    s32 dx;
    s32 dy;
    s32 tx;
    s32 ty;

    WorldToScreen(&x, &y, gBtlWork->actor->x, gBtlWork->actor->y, gBtlWork->actor->z);
    tx = 0x7800;
    ty = 0x5000;
    dx = tx - work->posX;
    dy = ty - work->posY;
    work->distance = NormalizeVector2D8(&dx, &dy);
    work->dirX = -dx;
    work->dirY = -dy;
    work->speed = 0x300;
    work->vz = 2;
}

u8 UpdateBossPrizeFlight(BossPrizeWork* work, void* a) {
    s32 dx;
    s32 dy;
    u8 z;
    u8 t;
    s32 x;
    s32 y;
    s16* q1;
    s16* q2;

    if (work->speed < 0) {
        dx = 0x7800 - work->posX;
        dy = 0x5000 - work->posY;
        NormalizeVector2D8(&dx, &dy);
        work->dirX = -dx;
        work->dirY = -dy;

        if (work->distance <= 0x7FF) {
            work->steps = 0;
            work->rotation = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateBossPrizeShow);
#ifdef VERSION_EU
            CreateCardNameDisplay(&work->tasks, GetLocalizedString(gCardDefs[work->cardId].name));
#else
            CreateCardNameDisplay(&work->tasks, gCardDefs[work->cardId].name);
#endif
        }
    }

    work->posX += (work->dirX * work->speed) >> 8;
    work->posY += (work->dirY * work->speed) >> 8;
    t = work->rotation + 32;
    z = 0;
    work->rotation = t;
    work->flipAngleY += (64 - work->flipAngleY) >> 4;
    work->flipAngleX = z;
    work->distance = VectorLength2D(0x7800 - work->posX, 0x5000 - work->posY);
    work->speed -= work->vz;
    work->vz += 2;

    if (work->scale <= 0xFF) {
        work->scale += 3;
    }

    x = work->posX >> 8;
    q1 = &work->x;
    *q1 = x;
    y = work->posY >> 8;
    q2 = &work->y;
    *q2 = y;
    UpdateBossPrizeScale(work);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 UpdateBossPrizeShow(BossPrizeWork* work, void* a) {
    s32 v;
    u16 t;
    s32 c;

    v = work->rotation << 8;
    ApproachValue((s32*)&work->flipAngleY, 0, work->steps);
    ApproachValue(&v, 0, work->steps);
    ApproachValue(&work->posX, 0x7800, work->steps);
    ApproachValue(&work->posY, 0x5800, work->steps);
    work->rotation = v >> 8;

    if (work->steps != 0) {
        work->steps--;
    }

    t = work->scale;

    if ((s16)t <= 0xFF) {
        work->scale = t + 2;
    } else {
        c = 0x100;
        work->scale = c;
    }

    work->x = work->posX >> 8;
    work->y = work->posY >> 8;
    UpdateBossPrizeScale(work);
    work->holdTimer++;

    if ((u32)work->cardId > 0x1C2) {
        if (work->holdTimer == 120) {
            work->holdTimer = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateBossPrizeShrink);
        }
    } else {
        if (work->holdTimer == 30) {
            work->holdTimer = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateBossPrizeShrink);
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 UpdateBossPrizeShrink(BossPrizeWork* work) {
    work->rotation += 32;
    WorldToScreen(&work->x3, &work->y3, gBtlWork->actor->x, gBtlWork->actor->y, gBtlWork->actor->z);
    work->x += (work->x3 - work->x) >> 3;
    work->y += (work->y3 - work->y) >> 3;
    work->scaleX -= 10;
    work->scaleY -= 10;

    if (work->scaleX <= 10) {
        return 0;
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void SpawnBossPrizeCardEffects(BossPrizeWork* work) {
    CardEffectArgs args;

    if (!work->collected) {
        if (work->effectTimer == 8) {
            if (work->effectCount <= 3) {
                args.x = work->posX;
                args.y = work->posY;
                args.z = work->posZ;
                args.screenSpace = work->collected;
                args.count = &work->effectCount;
                TaskCreate(&work->tasks, &gTaskDescCardEFFECT, &args);
            }

            work->effectTimer = 0;
        } else {
            work->effectTimer++;
        }
    } else {
        if (work->effectTimer == 8) {
            if (work->effectCount <= 7) {
                args.x = work->posX;
                args.y = work->posY;
                args.z = work->posZ;
                args.screenSpace = work->collected;
                args.count = &work->effectCount;
                TaskCreate(&work->tasks, &gTaskDescCardEFFECT, &args);
            }

            work->effectTimer = 0;
        } else {
            work->effectTimer++;
        }
    }
}

void Card_EFFECT_0(CardEffectWork* work, CardEffectArgs* a) {
    work->args = *a;

    if (!work->args.screenSpace) {
        work->posX = a->x + ((GetRandom() % 9 - 4) << 8);
        work->posY = a->y;
        work->posZ = a->z - 0x800;
    } else {
        work->posX = a->x + ((GetRandom() % 33 - 16) << 8);
        work->posY = a->y - 0x1000;
        work->posZ = 0;
    }

    work->tiles = AllocObjTiles(0x80, NULL);
    work->palette = LoadObjPalette(gUnk_09619158, 32);
    SetObjTileSource(work->tiles, gUnk_093F762E);
    AnimInit(&work->anim, gUnk_09EF1260, gUnk_09EF1230);
    AnimStart(&work->anim, GetRandom() % 3, 0);
    work->gfx = AnimGetGfx(&work->anim);
    (*work->args.count)++;
}

u8 Card_EFFECT_1(CardEffectWork* work) {
    work->gfx = AnimUpdate(&work->anim);

    if (!work->args.screenSpace) {
        WorldToScreen(&work->x, &work->y, work->posX, work->posY, work->posZ);
        work->posZ -= 0x100;
    } else {
        work->x = work->posX >> 8;
        work->y = work->posY >> 8;
        work->posY -= 0x100;
    }

    if (AnimIsFinished(&work->anim)) {
        return 0;
    }

    return 1;
}

void Card_EFFECT_2(CardEffectWork* work) {
    s16 t;
    s32 z;

    t = -4100 - ((work->y >> 8) * 4);
    z = 0;
    work->priority = t;
    DrawSprite(work->x, work->y, work->gfx, work->tiles, work->palette, NULL, z, work->priority);
}

void Card_EFFECT_3(CardEffectWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    work->args.count[0]--;
}

void scrollbar_0(ScrollBarWork* work, u16* args) {
    work->unk_08 = args[0];
    work->unk_0A = args[1];
    work->unk_0C = args[2];
    work->position = args[3];
    work->remaining = args[4];
    work->active = 1;
    work->unk_0E = 0;
    work->unk_17 = 0;
}

u8 scrollbar_1(ScrollBarWork* work) {
    return work->active;
}

void scrollbar_2() {
}

void scrollbar_3() {
}

void ScrollbarRequestClose(ScrollBarWork* work) {
    if (work != NULL) {
        work->active = 0;
    }
}

void ScrollbarAdvance(ScrollBarWork* work) {
    if (work != NULL) {
        if (work->remaining != 0) {
            work->position++;
            work->remaining--;
        } else {
            work->remaining = work->count - 1;
            work->position = 0;
        }
    }
}

void ScrollbarRetreat(ScrollBarWork* work) {
    if (work != NULL) {
        if (work->position != 0) {
            work->position--;
            work->remaining++;
        } else {
            work->position = work->count - 1;
            work->remaining = 0;
        }
    }
}

void ScrollbarDecrementCount(ScrollBarWork* work) {
    if (work != NULL) {
        work->count--;
    }
}

void ScrollbarIncrementCount(ScrollBarWork* work) {
    if (work != NULL) {
        work->count++;
    }
}

void func_08099FE8(ScrollBarWork* work, u16 b, u8 c) {
    if (work != NULL) {
        work->unk_0E = b;
        work->unk_17 = c;
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

AnimHeader** gUnk_09EE76E0 = gUnk_09EEA750;

AnimHeader** gUnk_09EE76E4 = gUnk_09EEABA8;

AnimHeader** gUnk_09EE76E8 = gUnk_09EEA97C;

AnimHeader** gUnk_09EE76EC = gUnk_09EEADD4;

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
