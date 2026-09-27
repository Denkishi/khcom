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

u8 func_080A2024(EventBgEffectWork* w, void* a);
void func_080A1E4C(EventBgEffectWork* w);

const EventBgEffectDef gUnk_0903803C = {
    &gUnk_09EE7998[0], gUnk_094233B8 + 0x500, gUnk_096148D8 + 0x20, 0x8C0, 0x20, { 1, 1, 0, 0 }, NULL, 0, -1,
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
    &gUnk_09EE7998[1], gUnk_094233B8 + 0xDC0, gUnk_096148D8 + 0x40, 0x800, 0x20, { 1, 1, 0, 0 }, gUnk_09038058, 8, -1,
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
    &gUnk_09EE7998[2], gUnk_094233B8 + 0x4C80, gUnk_096148D8 + 0x60, 0xC00, 0x20, { 1, 1, 0, 0 }, gUnk_09038094, 8, -1,
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
    &gUnk_09EE7998[3], gUnk_094233B8 + 0xFAE0, gUnk_096148D8 + 0xA0, 0x800, 0x20, { 1, 1, 0, 0 }, gUnk_090380D0, 10, -1,
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
    &gUnk_09EE7998[4], gUnk_094233B8 + 0xAAE0, gUnk_096148D8 + 0x80, 0x800, 0x20, { 1, 1, 0, 0 }, gUnk_09038114, 10, -1,
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
    &gUnk_09EE7998[5], gUnk_094233B8 + 0x14AE0, gUnk_096148D8 + 0xC0, 0xC00, 0x20, { 1, 1, 0, 0 }, gUnk_09038158, 16, -1,
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
    &gUnk_09EE7998[6], gUnk_094233B8 + 0x19D80, gUnk_096148D8 + 0xE0, 0x1000, 0x20, { 1, 1, 0, 0 }, gUnk_090381B4, 6, 2,
};

void func_080A1DAC(EventBgEffectWork* w) {
    const EventBgEffectEntry* e;
    const EventBgEffectDef* d;

    e = &w->entries[w->unk_14];
    d = gUnk_09EE79B4[e->unk_02];
    w->unk_12 = e->unk_02;
    LoadBgTiles(0, d->tiles, d->tilesSize);
    LoadBgPalette(0, d->palette, d->paletteSize);
    LoadBgMap(0, d->maps[0], 0x800);
    SetBgScroll(0, (u16)((gEventState->x >> 8) - (e->unk_04 >> 8)), (u16)((gEventState->y >> 8) - (e->unk_08 >> 8)));

    if (d->frames != 0) {
        w->unk_15 = 1;
    }

    SetBgBlend(0, 16, 16);
    gEventState->unk_80 = 1;
    w->unk_0E = w->unk_0C = w->unk_16 = 0;
}

void func_080A1E4C(EventBgEffectWork* w) {
    LoadBgTiles(0, gUnk_094233B8, 1280);
    LoadBgPalette(0, gUnk_096148D8, 32);
    LoadBgMap(0, gUnk_08125E24, 2048);
}

void func_080A1E80(EventBgEffectWork* w) {
    const EventBgEffectEntry* p;
    u16 v;
    u8 i;

    v = 16;
    p = &w->entries[w->unk_14];

    for (i = 16; i <= 31; i++) {
        FadeSetPaletteExcluded(i, 1);
    }

    FadeSetPaletteExcluded(14, 1);

    if (p->unk_04 > 0) {
        v = p->unk_04;
    }

    if (*(u16*)p->flags & 0x10) {
        FadeStartOut(0, v);
    } else {
        FadeToAmount(0, 16, v);
    }
}

void func_080A1ED8(EventBgEffectWork* w) {
    const EventBgEffectEntry* t;
    u16 v;

    v = 16;
    t = &w->entries[w->unk_14];
    FadeSetPaletteExcluded(14, 1);

    if (t->unk_04 > 0) {
        v = t->unk_04;
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
    w->unk_13 = t;
    w->unk_14 = z;
    w->unk_15 = z;
    w->entries = gUnk_09EE3FB4[w->unk_13]->bgEffects;
}
u8 EV_BG_EFFECT_1(EventBgEffectWork* w, void* a) {
    const EventBgEffectEntry* e;
    const EventBgEffectEntry* cur;
    u8 i;

    e = w->entries;

    if (e == 0) {
        return 0;
    }

    if (*(u16*)e[w->unk_14].unk_00 <= gEventState->unk_6C && !(*(u16*)e[w->unk_14].flags & 0x8000)) {
        w->unk_14++;
        cur = &e[w->unk_14];

        if (*(u16*)cur->flags & 1) {
            func_080A1DAC(w);

            if (w->unk_15 != 0) {
                SetTaskUpdate(a, (TaskUpdateFunc)func_080A2024);
            }
        }

        if (*(u16*)cur->flags & 4) {
            func_080A1E80(w);
        }

        if (*(u16*)cur->flags & 8) {
            func_080A1ED8(w);
            w->unk_16 = 1;
        }

        if (*(u16*)cur->flags & 2) {
            func_080A1E4C(w);
            gEventState->unk_80 = 0;
            gBldCnt = gEventState->unk_6E;
            gBldAlpha = gEventState->unk_70;
        }
    }

    if (w->unk_16 == 1) {
        if (!FadeIsActive()) {
            w->unk_16 = 0;

            for (i = 16; i < 32; i++) {
                FadeSetPaletteExcluded(i, 0);
            }
        }
    }

    return 1;
}

u8 func_080A2024(EventBgEffectWork* w, void* a) {
    const EventBgEffectEntry* p;

    p = &w->entries[w->unk_14];
    SetBgScroll(0, (u16)((gEventState->x >> 8) - (p->unk_04 >> 8)),
                (u16)((gEventState->y >> 8) - (p->unk_08 >> 8)));

    if (func_080A207C(w) == 0) {
        SetTaskUpdate(a, (TaskUpdateFunc)EV_BG_EFFECT_1);
    }

    return 1;
}

u8 func_080A207C(EventBgEffectWork* w) {
    const EventBgEffectDef* d;
    const EventBgEffectFrame* tbl;

    if (w->unk_15 == 0) {
        return 0;
    }

    d = gUnk_09EE79B4[w->unk_12];
    tbl = d->frames;

    if (w->unk_0C < tbl[w->unk_0E].duration) {
        w->unk_0C++;
    } else {
        w->unk_0C = 0;

        if (w->unk_0E < d->frameCount - 1) {
            w->unk_0E++;
            RequestDma3Copy(d->tiles + tbl[w->unk_0E].tilesOffset, (void*)GetBgCharBase(0), d->tilesSize);
        } else {
            if (d->loopFrame == -1) {
                w->unk_15 = 0;
                return 0;
            }

            w->unk_0E = d->loopFrame;
            RequestDma3Copy(d->tiles + tbl[w->unk_0E].tilesOffset, (void*)GetBgCharBase(0), d->tilesSize);
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

const EventBgEffectDef* gUnk_09EE79B4[8] = {
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
    (TaskFunc)EV_BG_EFFECT_2,
    (TaskFunc)EV_BG_EFFECT_3,
    sizeof(EventBgEffectWork),
};
