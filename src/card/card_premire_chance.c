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
#include "sprites_card_pictures.h"

s32 func_0809CBD0(UnkStruct_0809C534* w);
void func_0809CAC8(UnkStruct_0809C534* w);
void func_0809C9A4(UnkStruct_0809C534* w);
void func_0809CA1C(UnkStruct_0809C534* w);
u8 func_0809C9F4(UnkStruct_0809C534* w);
u8 func_0809CB78(UnkStruct_0809C534* w, void* a);

const s16 gUnk_09036278[9] = { 0, 11, 23, 34, 46, 57, 68, 79, 90 };

const u8 gUnk_0903628A[9] = { 6, 4, 2, 0, 2, 4, 6, 8, 12 };

void func_0809C534(UnkStruct_0809C534* w, CardSlot* a) {
    CardDef* def;

    w->unk_54 = 0;
    w->tiles4 = 0;

    if (a->unk_06 <= 8) {
        w->angle = gUnk_09036278[a->unk_06];
    } else {
        w->angle = -0x20;
    }

    w->unk_52 = a->unk_06;
    w->unk_48 = a->unk_04;
    def = &gCardDefs[a->cardId];
    w->cardDef = def;

    if (def->flags & 0xC) {
        w->cardBack = &gUnk_08F709B0[1];
    } else {
        w->cardBack = &gUnk_08F709B0[def->unk_2A];
    }

    w->radius = 0;
    func_0809C9A4(w);
    ListNodeInit(&w->node, &gCardListWork->cards, w);
    ListPoolAppend(&w->node, &gCardListWork->cards);
    w->unk_55 = 0;
    w->scaleX = 0x100;
    w->scaleY = 0x100;
    w->x2 = 0;
    w->y2 = 0;
    w->unk_53 = 32;
    w->unk_74 = 0;
}
u8 func_0809C620(UnkStruct_0809C534* w, void* a) {
    s32 v;
    u8 (*fn)(UnkStruct_0809C534*, void*);
    u16 lim;

    v = w->angle << 8;

    if (w->unk_52 <= 8) {
        ApproachValue(&v, gUnk_09036278[w->unk_52] << 8, w->unk_53);
        w->angle = v >> 8;
    } else {
        lim = 0xFFE0;
        w->angle = lim;
    }

    if (w->unk_53 != 0) {
        w->unk_53--;
    }

    func_0809C9A4(w);

    if (func_0809C9F4(w)) {
        func_0809CA1C(w);
    } else {
        func_0809CAC8(w);
    }

    if (w->unk_52 == 3) {
        gCardListWork->selectedCard = w;
    }

    switch (w->unk_55) {
    case 2:
        gCardListWork->unk_29 = 0;
        w->unk_53 = 8;
        fn = func_0809CB0C;
        SetTaskUpdate(a, (TaskUpdateFunc)fn);
        return fn(w, a);
    case 3:
        w->unk_53 = 10;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0809CBF8);
        break;
    }

    return 1;
}

u8 func_0809C710(UnkStruct_0809C534* w, void* a) {
    s32 v;

    v = w->radius << 8;
    ApproachValue(&v, 0x6800, w->unk_53);
    w->radius = v >> 8;
    w->unk_53--;
    func_0809C9A4(w);

    if (w->unk_52 <= 8) {
        func_0809CA1C(w);
    } else {
        func_0809CAC8(w);
    }

    if (w->unk_53 == 0) {
        w->unk_55 = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0809C620);
    }

    return 1;
}

void func_0809C78C(UnkStruct_0809C534* w) {
    ObjAffine* affine;

    if (w->unk_55 == 0xFF) {
        return;
    }

    if (w->unk_54 != 0) {
        affine = AllocObjAffine(0, w->scaleX, w->scaleY, 1);
        DrawSprite(w->x + w->x2, w->y + w->y2, w->cardDef->gfx, w->tiles, w->palette2, affine, 0x400,
                   gUnk_0903628A[w->unk_52] + 70);
        DrawSprite(w->x + w->x2, w->y + w->y2, w->cardBack->gfx, w->tiles2, w->palette3, affine, 0x400,
                   gUnk_0903628A[w->unk_52] + 69);

        if (w->unk_74 == 0) {
            DrawSprite(w->x + w->x2, w->y + w->y2, gUnk_09EE981C[w->cardDef->unk_20], w->tiles3, w->palette3,
                       affine, 0x400, gUnk_0903628A[w->unk_52] + 68);
        } else {
            DrawSprite(w->x + w->x2, w->y + w->y2, gUnk_09EE9894[w->cardDef->unk_20], w->tiles5, w->palette,
                       affine, 0x400, gUnk_0903628A[w->unk_52] + 68);
        }
    }

    if (w->unk_55 == 2 && w->tiles4 != 0) {
        DrawSprite(w->x + w->x2, w->y + w->y2, w->gfx, w->tiles4, w->palette3, 0, 0x400,
                   gUnk_0903628A[w->unk_52] + 67);
    }
}
void func_0809C98C(UnkStruct_0809C534* w) {
    func_0809CAC8(w);

    if (w->tiles4 != 0) {
        ReleaseObjTiles(w->tiles4);
    }
}

void func_0809C9A4(UnkStruct_0809C534* w) {
    w->x = (gSineTable[(u8)w->angle] * w->radius) >> 8;
    w->y = ((-gSineTable[(u8)w->angle + 64] * w->radius) >> 8) + 160;
}

u8 func_0809C9F4(UnkStruct_0809C534* w) {
    if (w->x >= 0) {
        if (w->x <= 240) {
            if (w->y >= 0) {
                if (w->y <= 160) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void func_0809CA1C(UnkStruct_0809C534* w) {
    if (w->unk_54 == 0) {
        w->tiles2 = LoadObjTiles(w->cardBack->tiles, 0x280);
        w->palette3 = LoadObjPalette(gCard00Palette, 32);
        w->tiles = LoadObjTiles(w->cardDef->tiles, 0x200);
        w->palette2 = LoadObjPalette(w->cardDef->palette, 32);
        w->tiles3 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
        w->tiles5 = LoadObjTiles(gUnk_0905ED36, 0x140);
        w->palette = LoadObjPalette(gBStatesPalette, 32);
        FadeSetPaletteExcluded(w->palette->index + 16, 1);
        FadeSetPaletteExcluded(w->palette3->index + 16, 1);
        FadeSetPaletteExcluded(w->palette2->index + 16, 1);
        w->unk_54 = 1;
    }
}

void func_0809CAC8(UnkStruct_0809C534* w) {
    if (w->unk_54 != 0) {
        ReleaseObjTiles(w->tiles2);
        ReleaseObjPalette(w->palette3);
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette2);
        ReleaseObjTiles(w->tiles3);
        ReleaseObjPalette(w->palette);
        ReleaseObjTiles(w->tiles5);
        w->unk_54 = 0;
    }
}

u8 func_0809CB0C(UnkStruct_0809C534* w, void* a) {
    s32 x;
    s32 y;

    x = w->x << 8;
    y = w->y << 8;
    ApproachValue(&x, 0x7800, w->unk_53);
    ApproachValue(&y, 0x4600, w->unk_53);
    w->x = x >> 8;
    w->y = y >> 8;
    w->unk_53--;

    if (w->unk_53 == 0) {
        SetTaskUpdate(a, (TaskUpdateFunc)func_0809CB78);
    }

    return 1;
}

u8 func_0809CB78(UnkStruct_0809C534* w, void* a) {
    w->tiles4 = AllocObjTiles(640, 0);
    SetObjTileSource(w->tiles4, gUnk_0908B1B4);
    AnimInit(&w->anim, gUnk_09EEA164, gUnk_09EEA148);
    AnimStart(&w->anim, 0, 1);
    w->gfx = AnimGetGfx(&w->anim);
    SetTaskUpdate(a, (TaskUpdateFunc)func_0809CBD0);
    return 1;
}

s32 func_0809CBD0(UnkStruct_0809C534* w) {
    w->gfx = AnimUpdate(&w->anim);

    if (w->anim.timer == 0 && w->anim.frame == 4) {
        w->unk_74 = 1;
    }

    return 1;
}

u8 func_0809CBF8(UnkStruct_0809C534* w, void* a) {
    s32 v;

    v = w->angle << 8;

    if (w->unk_52 <= 2) {
        ApproachValue(&v, -0x2000, w->unk_53);
    }

    if ((u8)w->unk_52 >= 4 && (u8)w->unk_52 <= 7) {
        ApproachValue(&v, 0x4400, w->unk_53);
    }

    w->angle = v >> 8;

    if (w->unk_53 != 0) {
        w->unk_53--;
    }

    func_0809C9A4(w);

    if (func_0809C9F4(w)) {
        func_0809CA1C(w);
    } else {
        func_0809CAC8(w);
    }

    return 1;
}

TaskDesc gUnk_09EE781C = {
    "Premire Chance",
    (TaskInitFunc)func_0809C534,
    (TaskUpdateFunc)func_0809C710,
    (TaskDrawFunc)func_0809C78C,
    (TaskDestroyFunc)func_0809C98C,
    sizeof(UnkStruct_0809C534),
};
