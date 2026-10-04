/**
 * ev_bg_effect.c
 * Event Background Effects
 */

#include "registration_data.h"
#include "fade.h"
#include "display.h"
#include "taskpool.h"
#include "card.h"
#include "sprites_msg.h"
#include "evt_obj.h"
#include "evt_types.h"
#include "msg_types.h"
#include "sprite_palettes.h"
#include "types.h"
#include <stddef.h>
#include "ev_bg_effect.h"
#include "default_bg_map.h"

static const EventBgEffectDef sEventBgEffect0Def = {
    &gEventBgEffectMaps[0], gEventBgEffect0Tiles, gEventBgEffect0Palette, 0x8C0, 0x20, { 1, 1, 0, 0 }, NULL, 0, -1,
};

static const EventBgEffectFrame sEventBgEffect1Frames[8] = {
    { 6, 0 },
    { 6, 0x800 },
    { 6, 0x1000 },
    { 6, 0x1800 },
    { 6, 0x2000 },
    { 6, 0x2800 },
    { 6, 0x3000 },
    { 6, 0x3800 },
};

static const EventBgEffectDef sEventBgEffect1Def = {
    &gEventBgEffectMaps[1], gEventBgEffect1Tiles, gEventBgEffect1Palette, 0x800, 0x20, { 1, 1, 0, 0 }, sEventBgEffect1Frames, 8, -1,
};

static const EventBgEffectFrame sEventBgEffect2Frames[8] = {
    { 6, 0 },
    { 6, 0xC00 },
    { 6, 0x1800 },
    { 6, 0x2400 },
    { 6, 0x3000 },
    { 6, 0x3C00 },
    { 6, 0x4800 },
    { 6, 0x5400 },
};

static const EventBgEffectDef sEventBgEffect2Def = {
    &gEventBgEffectMaps[2], gEventBgEffect2Tiles, gEventBgEffect2Palette, 0xC00, 0x20, { 1, 1, 0, 0 }, sEventBgEffect2Frames, 8, -1,
};

static const EventBgEffectFrame sEventBgEffect3Frames[10] = {
    { 6, 0 },
    { 6, 0x800 },
    { 6, 0x1000 },
    { 6, 0x1800 },
    { 6, 0x2000 },
    { 6, 0x2800 },
    { 6, 0x3000 },
    { 6, 0x3800 },
    { 6, 0x4000 },
    { 6, 0x4800 },
};

static const EventBgEffectDef sEventBgEffect3Def = {
    &gEventBgEffectMaps[3], gEventBgEffect3Tiles, gEventBgEffect3Palette, 0x800, 0x20, { 1, 1, 0, 0 }, sEventBgEffect3Frames, 10, -1,
};

static const EventBgEffectFrame sEventBgEffect4Frames[10] = {
    { 6, 0 },
    { 6, 0x800 },
    { 6, 0x1000 },
    { 6, 0x1800 },
    { 6, 0x2000 },
    { 6, 0x2800 },
    { 6, 0x3000 },
    { 6, 0x3800 },
    { 6, 0x4000 },
    { 6, 0x4800 },
};

static const EventBgEffectDef sEventBgEffect4Def = {
    &gEventBgEffectMaps[4], gEventBgEffect4Tiles, gEventBgEffect4Palette, 0x800, 0x20, { 1, 1, 0, 0 }, sEventBgEffect4Frames, 10, -1,
};

static const EventBgEffectFrame sEventBgEffect5Frames[16] = {
    { 6, 0 },
    { 6, 0xC00 },
    { 6, 0x1800 },
    { 6, 0x2400 },
    { 6, 0x3000 },
    { 6, 0x3C00 },
    { 6, 0x4800 },
    { 6, 0x3000 },
    { 6, 0x3C00 },
    { 6, 0x4800 },
    { 6, 0x3000 },
    { 6, 0x3C00 },
    { 6, 0x4800 },
    { 6, 0x3000 },
    { 6, 0x3C00 },
    { 6, 0x4800 },
};

static const EventBgEffectDef sEventBgEffect5Def = {
    &gEventBgEffectMaps[5], gEventBgEffect5Tiles, gEventBgEffect5Palette, 0xC00, 0x20, { 1, 1, 0, 0 }, sEventBgEffect5Frames, 16, -1,
};

static const EventBgEffectFrame sEventBgEffect6Frames[6] = {
    { 6, 0 },
    { 6, 0x1000 },
    { 6, 0x2000 },
    { 6, 0x3000 },
    { 6, 0x4000 },
    { 6, 0x5000 },
};

static const EventBgEffectDef sEventBgEffect6Def = {
    &gEventBgEffectMaps[6], gEventBgEffect6Tiles, gEventBgEffect6Palette, 0x1000, 0x20, { 1, 1, 0, 0 }, sEventBgEffect6Frames, 6, 2,
};

void LoadEventBgEffect(EventBgEffectWork* work) {
    const EventBgEffectEntry* e;
    const EventBgEffectDef* d;

    e = &work->entries[work->entry];
    d = gEventBgEffectDefs[e->effect];
    work->effect = e->effect;
    LoadBgTiles(0, d->tiles, d->tilesSize);
    LoadBgPalette(0, d->palette, d->paletteSize);
    LoadBgMap(0, d->maps[0], 0x800);
    SetBgScroll(0, (u16)((gEventState->x >> 8) - (e->x >> 8)), (u16)((gEventState->y >> 8) - (e->y >> 8)));

    if (d->frames != NULL) {
        work->animating = 1;
    }

    SetBgBlend(0, 16, 16);
    gEventState->bgEffectActive = 1;
    work->frame = work->frameTimer = work->fadingIn = 0;
}

void ClearEventBgEffect(EventBgEffectWork* work) {
    LoadBgTiles(0, gMsgwinTiles, 1280);
    LoadBgPalette(0, gMsgwinPalette, 32);
    LoadBgMap(0, gUnk_08125E24, 2048);
}

void StartEventBgEffectFadeOut(EventBgEffectWork* work) {
    const EventBgEffectEntry* p;
    u16 v;
    u8 i;

    v = 16;
    p = &work->entries[work->entry];

    for (i = 16; i <= 31; i++) {
        FadeSetPaletteExcluded(i, 1);
    }

    FadeSetPaletteExcluded(14, 1);

    if (p->x > 0) {
        v = p->x;
    }

    if (p->flags & 0x10) {
        FadeStartOut(FADE_MODE_BLACK, v);
    } else {
        FadeToAmount(FADE_MODE_BLACK, 16, v);
    }
}

void StartEventBgEffectFadeIn(EventBgEffectWork* work) {
    const EventBgEffectEntry* t;
    u16 v;

    v = 16;
    t = &work->entries[work->entry];
    FadeSetPaletteExcluded(14, 1);

    if (t->x > 0) {
        v = t->x;
    }

    if (t->flags & 0x10) {
        FadeStartIn(FADE_MODE_BLACK, v);
    } else {
        FadeToOriginal(FADE_MODE_BLACK, v);
    }
}

void EV_BG_EFFECT_0(EventBgEffectWork* work, u8* b) {
    u8 t;
    u8 z;

    t = b[0];
    z = 0;
    work->eventId = t;
    work->entry = z;
    work->animating = z;
    work->entries = gEventSequenceDefs[work->eventId]->bgEffects;
}

u8 EV_BG_EFFECT_1(EventBgEffectWork* work, void* a) {
    const EventBgEffectEntry* e;
    const EventBgEffectEntry* cur;
    u8 i;

    e = work->entries;

    if (e == NULL) {
        return 0;
    }

    if (e[work->entry].frame <= gEventState->frame && !(e[work->entry].flags & 0x8000)) {
        work->entry++;
        cur = &e[work->entry];

        if (cur->flags & 1) {
            LoadEventBgEffect(work);

            if (work->animating != 0) {
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateEventBgEffectAnim);
            }
        }

        if (cur->flags & 4) {
            StartEventBgEffectFadeOut(work);
        }

        if (cur->flags & 8) {
            StartEventBgEffectFadeIn(work);
            work->fadingIn = 1;
        }

        if (cur->flags & 2) {
            ClearEventBgEffect(work);
            gEventState->bgEffectActive = 0;
            gBldCnt = gEventState->bldCnt;
            gBldAlpha = gEventState->bldAlpha;
        }
    }

    if (work->fadingIn == 1) {
        if (!FadeIsActive()) {
            work->fadingIn = 0;

            for (i = 16; i < 32; i++) {
                FadeSetPaletteExcluded(i, 0);
            }
        }
    }

    return 1;
}

u8 UpdateEventBgEffectAnim(EventBgEffectWork* work, void* a) {
    const EventBgEffectEntry* p;

    p = &work->entries[work->entry];
    SetBgScroll(0, (u16)((gEventState->x >> 8) - (p->x >> 8)),
                (u16)((gEventState->y >> 8) - (p->y >> 8)));

    if (!StepEventBgEffectAnim(work)) {
        SetTaskUpdate(a, (TaskUpdateFunc)EV_BG_EFFECT_1);
    }

    return 1;
}

u8 StepEventBgEffectAnim(EventBgEffectWork* work) {
    const EventBgEffectDef* d;
    const EventBgEffectFrame* tbl;

    if (work->animating == 0) {
        return 0;
    }

    d = gEventBgEffectDefs[work->effect];
    tbl = d->frames;

    if (work->frameTimer < tbl[work->frame].duration) {
        work->frameTimer++;
    } else {
        work->frameTimer = 0;

        if (work->frame < d->frameCount - 1) {
            work->frame++;
            RequestDma3Copy(d->tiles + tbl[work->frame].tilesOffset, GetBgCharBase(0), d->tilesSize);
        } else {
            if (d->loopFrame == -1) {
                work->animating = 0;
                return 0;
            }

            work->frame = d->loopFrame;
            RequestDma3Copy(d->tiles + tbl[work->frame].tilesOffset, GetBgCharBase(0), d->tilesSize);
        }
    }

    return 1;
}

void EV_BG_EFFECT_2() {
}

void EV_BG_EFFECT_3() {
}

void CreateEVBGEFFECTTask(u8* work) {
    TaskCreate((TaskPool*)&work[0x10], &gTaskDescEVBGEFFECT, work);
}

const EventBgEffectDef* gEventBgEffectDefs[8] = {
    &sEventBgEffect0Def,
    &sEventBgEffect1Def,
    &sEventBgEffect2Def,
    &sEventBgEffect3Def,
    &sEventBgEffect4Def,
    &sEventBgEffect5Def,
    &sEventBgEffect6Def,
    NULL,
};

TaskDesc gTaskDescEVBGEFFECT = {
    "EV_BG_EFFECT",
    (TaskInitFunc)EV_BG_EFFECT_0,
    (TaskUpdateFunc)EV_BG_EFFECT_1,
    (TaskDrawFunc)EV_BG_EFFECT_2,
    (TaskDestroyFunc)EV_BG_EFFECT_3,
    sizeof(EventBgEffectWork),
};
