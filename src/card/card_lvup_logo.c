#include "registration_data.h"
#include "system_state.h"
#include "m4a_song.h"
#include "fade.h"
#include "obj_api.h"
#include "obj.h"
#include "taskpool.h"
#include "card.h"
#include "sprites_level_up.h"
#include "evt_types.h"
#include "songs.h"
#include "bos6.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "engine_math.h"
#include "event_background_types.h"
#include "event_index_data.h"
#include "types.h"
#include <stddef.h>

static u8 sLvupLogoActive;

void TrackLevelUpEffectTarget(LevelUpEffectWork* w) {
    s16 x;
    s16 y;
    BtlObj* t;

    t = w->target;

    if (t != NULL) {
        WorldToScreen(&x, &y, t->x, t->y, t->z);
        w->targetX = x;
        w->targetY = y - 16;
    }
}

void LVUP_EFFECT_0(LevelUpEffectWork* w, LevelUpEffectArgs* a) {
    s32 i;
    LevelUpEffectArgs args;

    w->target = a->target;
    w->targetX = a->x;
    w->targetY = a->y;
    w->radius = 30;
    w->unk_97 = a->unk_08;
    TrackLevelUpEffectTarget(w);

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        w->tiles = LoadObjTiles(gUnk_0908C686, 0x3E0);
        break;
    case LANGUAGE_FRENCH:
        w->tiles = LoadObjTiles(gUnkEu_0916F992, 0x3E0);
        break;
    case LANGUAGE_GERMAN:
        w->tiles = LoadObjTiles(gUnkEu_0917063A, 0x3E0);
        break;
    case LANGUAGE_ITALIAN:
        w->tiles = LoadObjTiles(gUnkEu_09170202, 0x3E0);
        break;
    case LANGUAGE_SPANISH:
        w->tiles = LoadObjTiles(gUnkEu_0916FDCA, 0x3E0);
        break;
    default:
        w->tiles = LoadObjTiles(gUnk_0908C686, 0x3E0);
        break;
    }
#else
    w->tiles = LoadObjTiles(gUnk_0908C686, 0x3E0);
#endif
    w->palette = LoadObjPalette(gCard00Palette, 32);

    for (i = 0; i < 4; i++) {
        w->centerX[i] = (w->targetX << 8) + gLvupEffectStartOffsetX[i];
        w->centerY[i] = (w->targetY << 8) + gLvupEffectStartOffsetY[i];
        w->angle[i] = gLvupEffectStartAngles[i];
        w->x[i] = w->radius * gSineTable[w->angle[i] & 0xFF] + w->centerX[i];
        w->y[i] = -gSineTable[(w->angle[i] & 0xFF) + 64] * w->radius + w->centerY[i];
        w->unk_54[i] = 0;
    }

    w->frame = 0;
    w->timer = 0;
    w->gatherSteps = 24;
    TaskPoolInit(&w->tasks, 4);

    if (w->target != NULL && !sLvupLogoActive) {
        args.x = w->x[0];
        args.y = w->y[0];
        args.target = w->target;
        args.tiles = w->tiles;
        args.palette = w->palette;
        TaskCreate(&w->tasks, &gTaskDescLvupLogo, &args);
        sLvupLogoActive = 1;
    }
}

u8 LVUP_EFFECT_1(LevelUpEffectWork* w, void* a) {
    s32 i;

    TrackLevelUpEffectTarget(w);

    if ((s8)w->gatherSteps > 0) {
        for (i = 0; i < 4; i++) {
            ApproachValue(&w->centerX[i], w->targetX << 8, (s8)w->gatherSteps);
            ApproachValue(&w->centerY[i], w->targetY << 8, (s8)w->gatherSteps);
        }

        w->gatherSteps--;
    } else {
        for (i = 0; i < 4; i++) {
            w->angle[i] += 6;
            w->centerX[i] = w->targetX << 8;
            w->centerY[i] = w->targetY << 8;
        }

        if ((s16)w->angle[0] > 0x100) {
            w->radius--;
        }
    }

    for (i = 0; i < 4; i++) {
        w->x[i] = gSineTable[w->angle[i] & 0xFF] * w->radius + w->centerX[i];
        w->y[i] = -gSineTable[(w->angle[i] & 0xFF) + 64] * w->radius + w->centerY[i];
    }

    w->timer++;
    TaskPoolUpdate(&w->tasks);

    if (w->radius == 0) {
        for (i = 0; i < 4; i++) {
            switch (i) {
            case 0:
                w->speed[0] = 0x300;
                w->vy[0] = -0x180;
                w->angle[0] = 8;
                break;
            case 1:
                w->speed[1] = 0x300;
                w->vy[1] = -0x180;
                w->angle[1] = -8;
                break;
            case 2:
                w->speed[2] = 0x300;
                w->vy[2] = -0x180;
                w->angle[2] = 16;
                break;
            case 3:
                w->speed[3] = 0x300;
                w->vy[3] = -0x180;
                w->angle[3] = -16;
                break;
            }
        }

        w->frame = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateLevelUpEffectScatter);
    }

    return 1;
}

u8 UpdateLevelUpEffectScatter(LevelUpEffectWork* w) {
    s32 i;

    for (i = 0; i < 4; i++) {
        w->vy[i] += 25;
        w->y[i] += w->vy[i];
        w->x[i] += gSineTable[(u8)w->angle[i]] * (w->speed[i] >> 8);
    }

    w->timer++;

    if (w->timer % 8 == 0 && (s8)w->timer > 1) {
        w->frame++;
    }

    TaskPoolUpdate(&w->tasks);

    if (w->y[0] > 0xA000) {
        return 0;
    }

    return 1;
}

void LVUP_EFFECT_2(LevelUpEffectWork* w) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (w->frame <= 5) {
#ifdef VERSION_EU
            DrawSprite(w->x[i] >> 8, w->y[i] >> 8, gLvupEffectSpritesByLanguage[gLanguage][w->frame], w->tiles, w->palette, NULL, 0, 20);
#else
            DrawSprite(w->x[i] >> 8, w->y[i] >> 8, gLvupEffectSprites[w->frame], w->tiles, w->palette, NULL, 0, 20);
#endif
        }
    }

    TaskPoolDraw(&w->tasks);
}

void LVUP_EFFECT_3(LevelUpEffectWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    TaskPoolDestroy(&w->tasks);

    if (gBtlWork->flags & BTL_FLAG_LEVEL_UP_EFFECT) {
        gBtlWork->flags &= ~BTL_FLAG_LEVEL_UP_EFFECT;
    }
}

#ifdef VERSION_EU
void* gLvupEffectSprites[6] = { gUnkEu_09163774, gUnkEu_0916377E, gUnkEu_09163788, gUnkEu_09163792, gUnkEu_0916379C, gUnkEu_091637A6 };

static void* sLvupEffectSpritesFrench[6] = { gUnkEu_0916F94C, gUnkEu_0916F956, gUnkEu_0916F960, gUnkEu_0916F96A, gUnkEu_0916F974, gUnkEu_0916F97E };

static void* sLvupEffectSpritesSpanish[6] = { gUnkEu_0916FD84, gUnkEu_0916FD8E, gUnkEu_0916FD98, gUnkEu_0916FDA2, gUnkEu_0916FDAC, gUnkEu_0916FDB6 };

static void* sLvupEffectSpritesItalian[6] = { gUnkEu_091701BC, gUnkEu_091701C6, gUnkEu_091701D0, gUnkEu_091701DA, gUnkEu_091701E4, gUnkEu_091701EE };

static void* sLvupEffectSpritesGerman[6] = { gUnkEu_091705F4, gUnkEu_091705FE, gUnkEu_09170608, gUnkEu_09170612, gUnkEu_0917061C, gUnkEu_09170626 };

void** gLvupEffectSpritesByLanguage[5] = { gLvupEffectSprites, sLvupEffectSpritesFrench, sLvupEffectSpritesGerman, sLvupEffectSpritesItalian, sLvupEffectSpritesSpanish };
#elif defined(VERSION_JP)
void* gLvupEffectSprites[6] = { gUnkJp_09047EB0, gUnkJp_09047EBA, gUnkJp_09047EC4, gUnkJp_09047ECE, gUnkJp_09047ED8, gUnkJp_09047EE2 };
#else
void* gLvupEffectSprites[6] = { gUnkUs_0908C640, gUnkUs_0908C64A, gUnkUs_0908C654, gUnkUs_0908C65E, gUnkUs_0908C668, gUnkUs_0908C672 };
#endif

TaskDesc gTaskDescLVUPEFFECT = {
    "LVUP_EFFECT",
    (TaskInitFunc)LVUP_EFFECT_0,
    (TaskUpdateFunc)LVUP_EFFECT_1,
    (TaskDrawFunc)LVUP_EFFECT_2,
    (TaskDestroyFunc)LVUP_EFFECT_3,
    sizeof(LevelUpEffectWork),
};

const s32 gLvupEffectStartOffsetX[4] = { -0xF000, 0xF000, 0, 0 };

const s32 gLvupEffectStartOffsetY[4] = { 0, 0, -0xF000, 0xF000 };

const u16 gLvupEffectStartAngles[4] = { 0, 128, 64, 192 };

void Lvup_Logo_0(LevelUpEffectWork* w, LevelUpEffectArgs* a) {
    w->x[0] = a->x;
    w->targetX = a->x;
    w->y[0] = a->y;
    w->targetY = a->y;
    w->target = a->target;

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        w->tiles = LoadObjTiles(gUnk_0908C686, 0x3E0);
        break;
    case LANGUAGE_FRENCH:
        w->tiles = LoadObjTiles(gUnkEu_0916F992, 0x3E0);
        break;
    case LANGUAGE_GERMAN:
        w->tiles = LoadObjTiles(gUnkEu_0917063A, 0x3E0);
        break;
    case LANGUAGE_ITALIAN:
        w->tiles = LoadObjTiles(gUnkEu_09170202, 0x3E0);
        break;
    case LANGUAGE_SPANISH:
        w->tiles = LoadObjTiles(gUnkEu_0916FDCA, 0x3E0);
        break;
    default:
        w->tiles = LoadObjTiles(gUnk_0908C686, 0x3E0);
        break;
    }
#else
    w->tiles = LoadObjTiles(gUnk_0908C686, 0x3E0);
#endif
    LoadObjPalette(gCard00Palette, 32);
    w->tiles = a->tiles;
    w->palette = a->palette;
    FadeSetPaletteExcluded(a->palette->index + 16, 1);
    w->frame = 0;
    w->timer = 0;
    w->vy[0] = -0x280;
    m4aSongNumStart(SONG_BTL_LVUP);
}

s32 Lvup_Logo_1(LevelUpEffectWork* w) {
    w->y[0] += w->vy[0];
    w->vy[0] += 25;
    TrackLevelUpEffectTarget(w);
    w->x[0] = w->targetX << 8;
    w->timer++;

    if ((s8)w->timer == 60) {
        return 0;
    }

    return 1;
}

void Lvup_Logo_2(LevelUpEffectWork* w) {
    DrawSprite(w->x[0] >> 8, w->y[0] >> 8, gUnk_09EEA19C[w->frame], w->tiles, w->palette, NULL, 0, 10);
}

void Lvup_Logo_3(LevelUpEffectWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    sLvupLogoActive = 0;
}

u8 CreateLevelUpEffectTask(BtlObj* p, TaskPool* pool) {
    LevelUpEffectArgs args;

    sLvupLogoActive = 0;

    if (gBtlWork->flags & BTL_FLAG_LEVEL_UP_EFFECT) {
        return 0;
    }

    args.x = p->x;
    args.y = p->y;
    args.unk_08 = 0;
    args.target = p;
    TaskCreate(pool, &gTaskDescLVUPEFFECT, &args);
    gBtlWork->flags |= BTL_FLAG_LEVEL_UP_EFFECT;
    return 1;
}

void LoadEventMapObjectGfx(EventMapObjectWork* w, EventBackgroundDef* t) {
    EventMapObjectDef* q;
    EventMapObjectPlacement* entries;
    u8 i;

    q = t->mapObjects;
    entries = q->placements;

    for (i = 0; i < 10; i++) {
        w->tiles[i] = NULL;
        w->palettes[i] = NULL;
    }

    for (i = 0; i < q->placementCount; i++) {
        if (w->tiles[entries[i].spriteIndex] == NULL) {
            w->tiles[entries[i].spriteIndex] = LoadObjTiles(q->tileResources[entries[i].spriteIndex].data, q->tileResources[entries[i].spriteIndex].size);
            w->palettes[entries[i].spriteIndex] = LoadObjPalette(q->paletteResources[entries[i].spriteIndex].data, q->paletteResources[entries[i].spriteIndex].size);
        }
    }
}

void ReleaseEventMapObjectGfx(EventMapObjectWork* w) {
    u8 i;

    for (i = 0; i <= 9; i++) {
        if (w->tiles[i] != NULL) {
            ReleaseObjTiles(w->tiles[i]);
            ReleaseObjPalette(w->palettes[i]);
        }
    }
}

void Ev_mapObj_0(EventMapObjectWork* w, u8* a) {
    EventBackgroundDef* t;

    w->background = a[0];
    t = gEventBackgroundDefs[w->background];

    if (t->mapObjects != NULL) {
        LoadEventMapObjectGfx(w, t);
        w->definition = t->mapObjects;
    }
}

u8 Ev_mapObj_1(EventMapObjectWork* w) {
    EventMapObjectDef* p;
    EventMapObjectPlacement* q;
    u8 i;

    p = w->definition;
    q = p->placements;

    for (i = 0; i < p->placementCount; i++) {
        FadeSetPaletteExcluded(w->palettes[q[i].spriteIndex]->index + 16, 0);
    }

    return 1;
}

void Ev_mapObj_2(EventMapObjectWork* w) {
    EventMapObjectDef* q;
    EventMapObjectPlacement* entries;
    EventMapObjectPlacement* e;
    u8 i;

    q = w->definition;
    entries = q->placements;

    for (i = 0; i < q->placementCount; i++) {
        e = &entries[i];
        DrawSprite(e->x - (gEventState->x >> 8), e->y - (gEventState->y >> 8), q->sprites[e->spriteIndex], w->tiles[e->spriteIndex], w->palettes[e->spriteIndex], NULL, SPRITE_PRIORITY(2), -0x1004 - e->y * 4);
    }
}

void Ev_mapObj_3(EventMapObjectWork* w) {
    ReleaseEventMapObjectGfx(w);
}

TaskDesc gTaskDescLvupLogo = {
    "Lvup_Logo",
    (TaskInitFunc)Lvup_Logo_0,
    (TaskUpdateFunc)Lvup_Logo_1,
    (TaskDrawFunc)Lvup_Logo_2,
    (TaskDestroyFunc)Lvup_Logo_3,
    sizeof(LevelUpEffectWork),
};

TaskDesc gTaskDescEvMapObj = {
    "Ev_mapObj",
    (TaskInitFunc)Ev_mapObj_0,
    (TaskUpdateFunc)Ev_mapObj_1,
    (TaskDrawFunc)Ev_mapObj_2,
    (TaskDestroyFunc)Ev_mapObj_3,
    sizeof(EventMapObjectWork),
};

void* gEventBgEffectMaps[7] = { gUnk_0951F2B8, gUnk_0951FAB8, gUnk_095202B8, gUnk_095212B8, gUnk_09520AB8, gUnk_09521AB8, gUnk_095222B8 };
