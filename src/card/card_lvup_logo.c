/**
 * card_lvup_logo.c
 * Level-Up Logo and Effects
 */

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
#include "sprite_palettes.h"

static u8 sLvupLogoActive;

void TrackLevelUpEffectTarget(LevelUpEffectWork* work) {
    s16 x;
    s16 y;
    BtlObj* t;

    t = work->target;

    if (t != NULL) {
        WorldToScreen(&x, &y, t->x, t->y, t->z);
        work->targetX = x;
        work->targetY = y - 16;
    }
}

void LVUP_EFFECT_0(LevelUpEffectWork* work, LevelUpEffectArgs* arg) {
    s32 i;
    LevelUpEffectArgs args;

    work->target = arg->target;
    work->targetX = arg->x;
    work->targetY = arg->y;
    work->radius = 30;
    work->unk_97 = arg->unk_08;
    TrackLevelUpEffectTarget(work);

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        work->tiles = LoadObjTiles(gLvupLogoTiles, 0x3E0);
        break;
    case LANGUAGE_FRENCH:
        work->tiles = LoadObjTiles(gLvupLogoFrenchTiles, 0x3E0);
        break;
    case LANGUAGE_GERMAN:
        work->tiles = LoadObjTiles(gLvupLogoGermanTiles, 0x3E0);
        break;
    case LANGUAGE_ITALIAN:
        work->tiles = LoadObjTiles(gLvupLogoItalianTiles, 0x3E0);
        break;
    case LANGUAGE_SPANISH:
        work->tiles = LoadObjTiles(gLvupLogoSpanishTiles, 0x3E0);
        break;
    default:
        work->tiles = LoadObjTiles(gLvupLogoTiles, 0x3E0);
        break;
    }
#else
    work->tiles = LoadObjTiles(gLvupLogoTiles, 0x3E0);
#endif
    work->palette = LoadObjPalette(gCard00Palette, 32);

    for (i = 0; i < 4; i++) {
        work->centerX[i] = (work->targetX << 8) + gLvupEffectStartOffsetX[i];
        work->centerY[i] = (work->targetY << 8) + gLvupEffectStartOffsetY[i];
        work->angle[i] = gLvupEffectStartAngles[i];
        work->x[i] = work->radius * SIN(work->angle[i]) + work->centerX[i];
        work->y[i] = -COS(work->angle[i]) * work->radius + work->centerY[i];
        work->unk_54[i] = 0;
    }

    work->frame = 0;
    work->timer = 0;
    work->gatherSteps = 24;
    TaskPoolInit(&work->tasks, 4);

    if (work->target != NULL && !sLvupLogoActive) {
        args.x = work->x[0];
        args.y = work->y[0];
        args.target = work->target;
        args.tiles = work->tiles;
        args.palette = work->palette;
        TaskCreate(&work->tasks, &gTaskDescLvupLogo, &args);
        sLvupLogoActive = 1;
    }
}

u8 LVUP_EFFECT_1(LevelUpEffectWork* work, void* task) {
    s32 i;

    TrackLevelUpEffectTarget(work);

    if ((s8)work->gatherSteps > 0) {
        for (i = 0; i < 4; i++) {
            ApproachValue(&work->centerX[i], work->targetX << 8, (s8)work->gatherSteps);
            ApproachValue(&work->centerY[i], work->targetY << 8, (s8)work->gatherSteps);
        }

        work->gatherSteps--;
    } else {
        for (i = 0; i < 4; i++) {
            work->angle[i] += 6;
            work->centerX[i] = work->targetX << 8;
            work->centerY[i] = work->targetY << 8;
        }

        if ((s16)work->angle[0] > 0x100) {
            work->radius--;
        }
    }

    for (i = 0; i < 4; i++) {
        work->x[i] = SIN(work->angle[i]) * work->radius + work->centerX[i];
        work->y[i] = -COS(work->angle[i]) * work->radius + work->centerY[i];
    }

    work->timer++;
    TaskPoolUpdate(&work->tasks);

    if (work->radius == 0) {
        for (i = 0; i < 4; i++) {
            switch (i) {
            case 0:
                work->speed[0] = 0x300;
                work->vy[0] = -0x180;
                work->angle[0] = 8;
                break;
            case 1:
                work->speed[1] = 0x300;
                work->vy[1] = -0x180;
                work->angle[1] = -8;
                break;
            case 2:
                work->speed[2] = 0x300;
                work->vy[2] = -0x180;
                work->angle[2] = 16;
                break;
            case 3:
                work->speed[3] = 0x300;
                work->vy[3] = -0x180;
                work->angle[3] = -16;
                break;
            }
        }

        work->frame = 1;
        SetTaskUpdate(task, (TaskUpdateFunc)UpdateLevelUpEffectScatter);
    }

    return 1;
}

u8 UpdateLevelUpEffectScatter(LevelUpEffectWork* work) {
    s32 i;

    for (i = 0; i < 4; i++) {
        work->vy[i] += 25;
        work->y[i] += work->vy[i];
        work->x[i] += gSineTable[(u8)work->angle[i]] * (work->speed[i] >> 8);
    }

    work->timer++;

    if (work->timer % 8 == 0 && (s8)work->timer > 1) {
        work->frame++;
    }

    TaskPoolUpdate(&work->tasks);

    if (work->y[0] > 0xA000) {
        return 0;
    }

    return 1;
}

void LVUP_EFFECT_2(LevelUpEffectWork* work) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (work->frame <= 5) {
#ifdef VERSION_EU
            DrawSprite(work->x[i] >> 8, work->y[i] >> 8, gLvupEffectSpritesByLanguage[gLanguage][work->frame], work->tiles, work->palette, NULL, 0, 20);
#else
            DrawSprite(work->x[i] >> 8, work->y[i] >> 8, gLvupEffectSprites[work->frame], work->tiles, work->palette, NULL, 0, 20);
#endif
        }
    }

    TaskPoolDraw(&work->tasks);
}

void LVUP_EFFECT_3(LevelUpEffectWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);

    if (gBtlWork->flags & BTL_FLAG_LEVEL_UP_EFFECT) {
        gBtlWork->flags &= ~BTL_FLAG_LEVEL_UP_EFFECT;
    }
}

void* gLvupEffectSprites[6] = { gLvupLogoFrame1, gLvupLogoFrame2, gLvupLogoFrame3, gLvupLogoFrame4, gLvupLogoFrame5, gLvupLogoFrame6 };
#ifdef VERSION_EU
static void* sLvupEffectSpritesFrench[6] = { gLvupLogoFrenchFrame1, gLvupLogoFrenchFrame2, gLvupLogoFrenchFrame3, gLvupLogoFrenchFrame4, gLvupLogoFrenchFrame5, gLvupLogoFrenchFrame6 };

static void* sLvupEffectSpritesSpanish[6] = { gLvupLogoSpanishFrame1, gLvupLogoSpanishFrame2, gLvupLogoSpanishFrame3, gLvupLogoSpanishFrame4, gLvupLogoSpanishFrame5, gLvupLogoSpanishFrame6 };

static void* sLvupEffectSpritesItalian[6] = { gLvupLogoItalianFrame1, gLvupLogoItalianFrame2, gLvupLogoItalianFrame3, gLvupLogoItalianFrame4, gLvupLogoItalianFrame5, gLvupLogoItalianFrame6 };

static void* sLvupEffectSpritesGerman[6] = { gLvupLogoGermanFrame1, gLvupLogoGermanFrame2, gLvupLogoGermanFrame3, gLvupLogoGermanFrame4, gLvupLogoGermanFrame5, gLvupLogoGermanFrame6 };

void** gLvupEffectSpritesByLanguage[5] = { gLvupEffectSprites, sLvupEffectSpritesFrench, sLvupEffectSpritesGerman, sLvupEffectSpritesItalian, sLvupEffectSpritesSpanish };
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

void Lvup_Logo_0(LevelUpEffectWork* work, LevelUpEffectArgs* args) {
    work->x[0] = args->x;
    work->targetX = args->x;
    work->y[0] = args->y;
    work->targetY = args->y;
    work->target = args->target;

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        work->tiles = LoadObjTiles(gLvupLogoTiles, 0x3E0);
        break;
    case LANGUAGE_FRENCH:
        work->tiles = LoadObjTiles(gLvupLogoFrenchTiles, 0x3E0);
        break;
    case LANGUAGE_GERMAN:
        work->tiles = LoadObjTiles(gLvupLogoGermanTiles, 0x3E0);
        break;
    case LANGUAGE_ITALIAN:
        work->tiles = LoadObjTiles(gLvupLogoItalianTiles, 0x3E0);
        break;
    case LANGUAGE_SPANISH:
        work->tiles = LoadObjTiles(gLvupLogoSpanishTiles, 0x3E0);
        break;
    default:
        work->tiles = LoadObjTiles(gLvupLogoTiles, 0x3E0);
        break;
    }
#else
    work->tiles = LoadObjTiles(gLvupLogoTiles, 0x3E0);
#endif
    LoadObjPalette(gCard00Palette, 32);
    work->tiles = args->tiles;
    work->palette = args->palette;
    FadeSetPaletteExcluded(args->palette->index + 16, 1);
    work->frame = 0;
    work->timer = 0;
    work->vy[0] = -0x280;
    m4aSongNumStart(SONG_BTL_LVUP);
}

s32 Lvup_Logo_1(LevelUpEffectWork* work) {
    work->y[0] += work->vy[0];
    work->vy[0] += 25;
    TrackLevelUpEffectTarget(work);
    work->x[0] = work->targetX << 8;
    work->timer++;

    if ((s8)work->timer == 60) {
        return 0;
    }

    return 1;
}

void Lvup_Logo_2(LevelUpEffectWork* work) {
    DrawSprite(work->x[0] >> 8, work->y[0] >> 8, gLvupLogoFrames[work->frame], work->tiles, work->palette, NULL, 0, 10);
}

void Lvup_Logo_3(LevelUpEffectWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    sLvupLogoActive = 0;
}

u8 CreateLevelUpEffectTask(BtlObj* target, TaskPool* pool) {
    LevelUpEffectArgs args;

    sLvupLogoActive = 0;

    if (gBtlWork->flags & BTL_FLAG_LEVEL_UP_EFFECT) {
        return 0;
    }

    args.x = target->x;
    args.y = target->y;
    args.unk_08 = 0;
    args.target = target;
    TaskCreate(pool, &gTaskDescLVUPEFFECT, &args);
    gBtlWork->flags |= BTL_FLAG_LEVEL_UP_EFFECT;
    return 1;
}

void LoadEventMapObjectGfx(EventMapObjectWork* work, EventBackgroundDef* background) {
    EventMapObjectDef* q;
    EventMapObjectPlacement* entries;
    u8 i;

    q = background->mapObjects;
    entries = q->placements;

    for (i = 0; i < 10; i++) {
        work->tiles[i] = NULL;
        work->palettes[i] = NULL;
    }

    for (i = 0; i < q->placementCount; i++) {
        if (work->tiles[entries[i].spriteIndex] == NULL) {
            work->tiles[entries[i].spriteIndex] = LoadObjTiles(q->tileResources[entries[i].spriteIndex].data, q->tileResources[entries[i].spriteIndex].size);
            work->palettes[entries[i].spriteIndex] = LoadObjPalette(q->paletteResources[entries[i].spriteIndex].data, q->paletteResources[entries[i].spriteIndex].size);
        }
    }
}

void ReleaseEventMapObjectGfx(EventMapObjectWork* work) {
    u8 i;

    for (i = 0; i <= 9; i++) {
        if (work->tiles[i] != NULL) {
            ReleaseObjTiles(work->tiles[i]);
            ReleaseObjPalette(work->palettes[i]);
        }
    }
}

void Ev_mapObj_0(EventMapObjectWork* work, u8* arg) {
    EventBackgroundDef* t;

    work->background = arg[0];
    t = gEventBackgroundDefs[work->background];

    if (t->mapObjects != NULL) {
        LoadEventMapObjectGfx(work, t);
        work->definition = t->mapObjects;
    }
}

u8 Ev_mapObj_1(EventMapObjectWork* work) {
    EventMapObjectDef* p;
    EventMapObjectPlacement* q;
    u8 i;

    p = work->definition;
    q = p->placements;

    for (i = 0; i < p->placementCount; i++) {
        FadeSetPaletteExcluded(work->palettes[q[i].spriteIndex]->index + 16, 0);
    }

    return 1;
}

void Ev_mapObj_2(EventMapObjectWork* work) {
    EventMapObjectDef* q;
    EventMapObjectPlacement* entries;
    EventMapObjectPlacement* e;
    u8 i;

    q = work->definition;
    entries = q->placements;

    for (i = 0; i < q->placementCount; i++) {
        e = &entries[i];
        DrawSprite(e->x - (gEventState->x >> 8), e->y - (gEventState->y >> 8), q->sprites[e->spriteIndex], work->tiles[e->spriteIndex], work->palettes[e->spriteIndex], NULL, SPRITE_PRIORITY(2), -0x1004 - e->y * 4);
    }
}

void Ev_mapObj_3(EventMapObjectWork* work) {
    ReleaseEventMapObjectGfx(work);
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

void* gEventBgEffectMaps[7] = { gEventBgEffect0Map, gEventBgEffect1Map, gEventBgEffect2Map, gEventBgEffect3Map, gEventBgEffect4Map, gEventBgEffect5Map, gEventBgEffect6Map };
