#include "macros.h"
#include "card_localized_data.h"
#include "msg_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "msg_api.h"
#include "mode_sio_api.h"
#include "card_battle.h"
#include "mode_test_api.h"
#include "player_progression.h"
#include "m4a_song.h"
#include "game_state.h"
#include <string.h>
#include "text.h"
#include "monsgage.h"
#include "fade.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "display.h"
#include "engine_math.h"
#include "listpool.h"
#include "anim.h"
#include "obj.h"
#include "text_types.h"
#include "taskpool.h"
#include "key.h"
#include "gba/syscall.h"
#include "malloc.h"
#include "card.h"
#include "card_reload_assets.h"
#include "map_card_assets.h"
#include "card_localized_assets.h"
#include "card_help_assets.h"
#include "card_message_assets.h"
#include "card_description_assets.h"
#include <stddef.h>
#include "game.h"
#include "bos4_api.h"
#include "sprites_msg.h"
#include "evt.h"

u8 UpdateEventBgEffectAnim(EventBgEffectWork* w, void* a);
void ClearEventBgEffect(EventBgEffectWork* w);

const EventBgEffectDef gUnk_0903803C = {
    &gEventBgEffectMaps[0], gUnk_094233B8 + 0x500, gUnk_096148D8 + 0x20, 0x8C0, 0x20, { 1, 1, 0, 0 }, NULL, 0, -1,
};

const EventBgEffectFrame gUnk_09038058[8] = {
    { 6, 0 },
    { 6, 0x800 },
    { 6, 0x1000 },
    { 6, 0x1800 },
    { 6, 0x2000 },
    { 6, 0x2800 },
    { 6, 0x3000 },
    { 6, 0x3800 },
};

const EventBgEffectDef gUnk_09038078 = {
    &gEventBgEffectMaps[1], gUnk_094233B8 + 0xDC0, gUnk_096148D8 + 0x40, 0x800, 0x20, { 1, 1, 0, 0 }, gUnk_09038058, 8, -1,
};

const EventBgEffectFrame gUnk_09038094[8] = {
    { 6, 0 },
    { 6, 0xC00 },
    { 6, 0x1800 },
    { 6, 0x2400 },
    { 6, 0x3000 },
    { 6, 0x3C00 },
    { 6, 0x4800 },
    { 6, 0x5400 },
};

const EventBgEffectDef gUnk_090380B4 = {
    &gEventBgEffectMaps[2], gUnk_094233B8 + 0x4C80, gUnk_096148D8 + 0x60, 0xC00, 0x20, { 1, 1, 0, 0 }, gUnk_09038094, 8, -1,
};

const EventBgEffectFrame gUnk_090380D0[10] = {
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

const EventBgEffectDef gUnk_090380F8 = {
    &gEventBgEffectMaps[3], gUnk_094233B8 + 0xFAE0, gUnk_096148D8 + 0xA0, 0x800, 0x20, { 1, 1, 0, 0 }, gUnk_090380D0, 10, -1,
};

const EventBgEffectFrame gUnk_09038114[10] = {
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

const EventBgEffectDef gUnk_0903813C = {
    &gEventBgEffectMaps[4], gUnk_094233B8 + 0xAAE0, gUnk_096148D8 + 0x80, 0x800, 0x20, { 1, 1, 0, 0 }, gUnk_09038114, 10, -1,
};

const EventBgEffectFrame gUnk_09038158[16] = {
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

const EventBgEffectDef gUnk_09038198 = {
    &gEventBgEffectMaps[5], gUnk_094233B8 + 0x14AE0, gUnk_096148D8 + 0xC0, 0xC00, 0x20, { 1, 1, 0, 0 }, gUnk_09038158, 16, -1,
};

const EventBgEffectFrame gUnk_090381B4[6] = {
    { 6, 0 },
    { 6, 0x1000 },
    { 6, 0x2000 },
    { 6, 0x3000 },
    { 6, 0x4000 },
    { 6, 0x5000 },
};

const EventBgEffectDef gUnk_090381CC = {
    &gEventBgEffectMaps[6], gUnk_094233B8 + 0x19D80, gUnk_096148D8 + 0xE0, 0x1000, 0x20, { 1, 1, 0, 0 }, gUnk_090381B4, 6, 2,
};

void LoadEventBgEffect(EventBgEffectWork* w) {
    const EventBgEffectEntry* e;
    const EventBgEffectDef* d;

    e = &w->entries[w->entry];
    d = gEventBgEffectDefs[e->effect];
    w->effect = e->effect;
    LoadBgTiles(0, d->tiles, d->tilesSize);
    LoadBgPalette(0, d->palette, d->paletteSize);
    LoadBgMap(0, d->maps[0], 0x800);
    SetBgScroll(0, (u16)((gEventState->x >> 8) - (e->x >> 8)), (u16)((gEventState->y >> 8) - (e->y >> 8)));

    if (d->frames != 0) {
        w->animating = 1;
    }

    SetBgBlend(0, 16, 16);
    gEventState->unk_80 = 1;
    w->frame = w->frameTimer = w->fadingIn = 0;
}

void ClearEventBgEffect(EventBgEffectWork* w) {
    LoadBgTiles(0, gUnk_094233B8, 1280);
    LoadBgPalette(0, gUnk_096148D8, 32);
    LoadBgMap(0, gUnk_08125E24, 2048);
}

void StartEventBgEffectFadeOut(EventBgEffectWork* w) {
    const EventBgEffectEntry* p;
    u16 v;
    u8 i;

    v = 16;
    p = &w->entries[w->entry];

    for (i = 16; i <= 31; i++) {
        FadeSetPaletteExcluded(i, 1);
    }

    FadeSetPaletteExcluded(14, 1);

    if (p->x > 0) {
        v = p->x;
    }

    if (*(u16*)p->flags & 0x10) {
        FadeStartOut(0, v);
    } else {
        FadeToAmount(0, 16, v);
    }
}

void StartEventBgEffectFadeIn(EventBgEffectWork* w) {
    const EventBgEffectEntry* t;
    u16 v;

    v = 16;
    t = &w->entries[w->entry];
    FadeSetPaletteExcluded(14, 1);

    if (t->x > 0) {
        v = t->x;
    }

    if (*(u16*)t->flags & 0x10) {
        FadeStartIn(0, v);
    } else {
        FadeToOriginal(0, v);
    }
}
void EV_BG_EFFECT_0(EventBgEffectWork* w, u8* b) {
    u8 t;
    u8 z;

    t = b[0];
    z = 0;
    w->eventId = t;
    w->entry = z;
    w->animating = z;
    w->entries = gEventSequenceDefs[w->eventId]->bgEffects;
}
u8 EV_BG_EFFECT_1(EventBgEffectWork* w, void* a) {
    const EventBgEffectEntry* e;
    const EventBgEffectEntry* cur;
    u8 i;

    e = w->entries;

    if (e == 0) {
        return 0;
    }

    if (*(u16*)e[w->entry].frame <= gEventState->frame && !(*(u16*)e[w->entry].flags & 0x8000)) {
        w->entry++;
        cur = &e[w->entry];

        if (*(u16*)cur->flags & 1) {
            LoadEventBgEffect(w);

            if (w->animating != 0) {
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateEventBgEffectAnim);
            }
        }

        if (*(u16*)cur->flags & 4) {
            StartEventBgEffectFadeOut(w);
        }

        if (*(u16*)cur->flags & 8) {
            StartEventBgEffectFadeIn(w);
            w->fadingIn = 1;
        }

        if (*(u16*)cur->flags & 2) {
            ClearEventBgEffect(w);
            gEventState->unk_80 = 0;
            gBldCnt = gEventState->bldCnt;
            gBldAlpha = gEventState->bldAlpha;
        }
    }

    if (w->fadingIn == 1) {
        if (!FadeIsActive()) {
            w->fadingIn = 0;

            for (i = 16; i < 32; i++) {
                FadeSetPaletteExcluded(i, 0);
            }
        }
    }

    return 1;
}

u8 UpdateEventBgEffectAnim(EventBgEffectWork* w, void* a) {
    const EventBgEffectEntry* p;

    p = &w->entries[w->entry];
    SetBgScroll(0, (u16)((gEventState->x >> 8) - (p->x >> 8)),
                (u16)((gEventState->y >> 8) - (p->y >> 8)));

    if (StepEventBgEffectAnim(w) == 0) {
        SetTaskUpdate(a, (TaskUpdateFunc)EV_BG_EFFECT_1);
    }

    return 1;
}

u8 StepEventBgEffectAnim(EventBgEffectWork* w) {
    const EventBgEffectDef* d;
    const EventBgEffectFrame* tbl;

    if (w->animating == 0) {
        return 0;
    }

    d = gEventBgEffectDefs[w->effect];
    tbl = d->frames;

    if (w->frameTimer < tbl[w->frame].duration) {
        w->frameTimer++;
    } else {
        w->frameTimer = 0;

        if (w->frame < d->frameCount - 1) {
            w->frame++;
            RequestDma3Copy(d->tiles + tbl[w->frame].tilesOffset, (void*)GetBgCharBase(0), d->tilesSize);
        } else {
            if (d->loopFrame == -1) {
                w->animating = 0;
                return 0;
            }

            w->frame = d->loopFrame;
            RequestDma3Copy(d->tiles + tbl[w->frame].tilesOffset, (void*)GetBgCharBase(0), d->tilesSize);
        }
    }

    return 1;
}

void EV_BG_EFFECT_2(void) {
}
void EV_BG_EFFECT_3(void) {
}
void CreateEVBGEFFECTTask(u8* work) {
    TaskCreate(&work[0x10], &gTaskDescEVBGEFFECT, work);
}

const EventBgEffectDef* gEventBgEffectDefs[8] = {
    &gUnk_0903803C,
    &gUnk_09038078,
    &gUnk_090380B4,
    &gUnk_090380F8,
    &gUnk_0903813C,
    &gUnk_09038198,
    &gUnk_090381CC,
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
