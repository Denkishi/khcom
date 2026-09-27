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
#include "sprites_btl.h"
#include "sprites_card_pictures.h"

void CreateCardNameDisplay(void* a, void* b);
u8 func_08096288(PrizeCardWork* w, void* a);
u8 func_08096390(PrizeCardWork* w);
u8 func_0809612C(PrizeCardWork* w, void* a);
void func_080960D8(PrizeCardWork* w);
void func_08096700(TaskPool* pool, PrizeCardTaskArgs* args);
u16 func_08096D48(u16 a, s32 b);
s16 func_08084458(u16 cardId);

const u8 gUnk_090359E8[8] = { 1, 1, 4, 2, 5, 3, 3, 2 };

static void PrizeCard_0(PrizeCardWork* w, PrizeCardTaskArgs* p) {
    PrizeCardTaskArgs args;
    CardDef* def;
    CardBack* back;
    Collider* q;

    args = *p;
    w->cardId = args.cardId;
    def = &gCardDefs[args.cardId];
    w->tiles = LoadObjTiles(def->tiles, 0x300);
    w->palette = LoadObjPalette(def->palette, 32);
    w->stat = *(CardStat*)&def->unk_1C;

    if (gCardDefs[w->cardId].flags & 12) {
        back = &gUnk_08F709B0[3];
    } else {
        back = &gUnk_08F709B0[w->stat.unk_0E];
    }

    w->tiles2 = LoadObjTiles(back->tiles, 0x280);
    w->tiles3 = LoadObjTiles(back->tiles3, 0x600);
    w->palette2 = LoadObjPalette(gCard00Palette, 32);
    w->tiles4 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    w->tiles5 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    w->palette3 = LoadObjPalette(gBStatesPalette, 32);
    w->pos.x = args.x;
    w->pos.y = args.y;
    w->pos.z = args.z;
    w->pos.unk_0C = 0;
    w->unk_F6 = 24;
    func_080DFF4C(&w->pos);
    w->unk_CC = -(GetRandom() % 129 + 0x300);
    w->unk_D0 = GetRandom() % 129 + 0x80;
    w->unk_F4 = GetRandom() % 256;
    w->scaleX = 0x80;
    w->scaleY = 0x80;
    w->unk_F2 = 0x80;
    w->unk_F7 = 0;
    w->unk_F8 = 0;
    q = &w->collider;
    ColliderInit(q, 5, 30, 10);
    ColliderSetDisabled(q, 1);
    ColliderSetPosition(q, w->pos.x, w->pos.y, w->pos.z);
    w->unk_F9 = 0;
    w->unk_FC[0] = 0;
    w->unk_FA = 0;
    w->unk_FB = 0;
    TaskPoolInit(&w->tasks, 1);
}
static u8 PrizeCard_1(PrizeCardWork* w, void* a) {
    s32 k = 112;
    s16 x;
    s16 y;

    w->prevPos = w->pos;
    w->unk_CC += 0x38;
    w->pos.z += w->unk_CC;
    w->pos.x += (gSineTable[(u8)w->unk_F4] * w->unk_D0) >> 8;
    w->pos.y += (-gSineTable[(u8)w->unk_F4 + 0x40] * w->unk_D0) >> 8;

    if (func_080DFBDC(&w->pos) != 0) {
        w->unk_F4 = w->unk_F4 + k + GetRandom() % 33;

        do {
            w->pos.x = w->prevPos.x;
            w->pos.y = w->prevPos.y;
        } while (0);
    } else {
        w->pos.unk_0C = func_080DFF1C(&w->pos);
    }

    if (w->pos.z - 0x800 > w->pos.unk_0C) {
        w->pos.z = w->pos.unk_0C - 0x800;
        w->unk_CC = -((w->unk_CC * 217) >> 8);

        if (w->unk_CC > -0x200) {
            w->unk_CC = -0x200;
        }
    }

    if (w->collider.unk_2C != 0) {
        w->unk_FC[0] = 1;
        m4aSongNumStart(SONG_SYS_ITEMGET);

        if (w->cardId <= 0x1C1) {
            func_08084458(w->cardId);
        }

        SetTaskUpdate(a, (TaskUpdateFunc)func_0809612C);
        x = (w->pos.x >> 8) - (gFieldState->x >> 8);
        y = (w->pos.y >> 8) + (w->pos.z >> 8) - (gFieldState->y >> 8);
        w->pos.x = x << 8;
        w->pos.y = y << 8;
        ColliderSetDisabled(&w->collider, 1);
        w->unk_FA = 16;
        w->unk_E4 = 50;
        func_080960D8(w);
        return 1;
    }

    ColliderSetPosition(&w->collider, w->pos.x, w->pos.y, w->pos.z);
    w->x = (w->pos.x >> 8) - (gFieldState->x >> 8);
    w->y2 = (w->pos.y >> 8) + (w->pos.z >> 8) - (gFieldState->y >> 8);
    w->x2 = (w->pos.x >> 8) - (gFieldState->x >> 8);
    w->y = (w->pos.y >> 8) + (w->pos.unk_0C >> 8) - (gFieldState->y >> 8);
    w->unk_E4 = -0x1004 - (w->pos.y >> 8) * 4;
    func_08096638(w);
    w->unk_F8 += 2;

    if (w->unk_F9 == 20) {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->unk_F9 <= 59) {
        w->unk_F9++;
    }

    if (gFieldState->flags & 0x40000) {
        return 0;
    }

    return 1;
}
void func_080960D8(PrizeCardWork* w) {
    s32 cx = 0x7800;
    s32 cy = 0x5000;
    s32 v[2];

    v[0] = cx - w->pos.x;
    v[1] = cy - w->pos.y;
    w->unk_DC = NormalizeVector2D8(&v[0], &v[1]);
    w->unk_D4 = -v[0];
    w->unk_D8 = -v[1];
    w->unk_D0 = 0x300;
    w->unk_CC = 2;
}
u8 func_0809612C(PrizeCardWork* w, void* a) {
    s32 v[2];

    if (w->unk_D0 < 0) {
        v[0] = 0x7800 - w->pos.x;
        v[1] = 0x5000 - w->pos.y;
        NormalizeVector2D8(&v[0], &v[1]);
        w->unk_D4 = -v[0];
        w->unk_D8 = -v[1];

        if (w->unk_DC <= 0x7FF) {
            w->unk_FA = 0;
            w->unk_F6 = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)func_08096288);
#ifdef VERSION_EU
            CreateCardNameDisplay(&w->tasks, eu_0805E924(gCardDefs[w->cardId].name));
#else
            CreateCardNameDisplay(&w->tasks, gCardDefs[w->cardId].name);
#endif
        }
    }

    w->pos.x += (w->unk_D4 * w->unk_D0) >> 8;
    w->pos.y += (w->unk_D8 * w->unk_D0) >> 8;
    w->unk_F6 += 32;
    w->unk_F7 += (64 - w->unk_F7) >> 4;
    w->unk_F8 = 0;
    w->unk_DC = VectorLength2D(0x7800 - w->pos.x, 0x5000 - w->pos.y);
    w->unk_D0 -= w->unk_CC;
    w->unk_CC += 2;

    if (w->unk_F2 <= 255) {
        w->unk_F2 += 3;
    }

    w->x = w->pos.x >> 8;
    w->y2 = w->pos.y >> 8;
    func_08096638(w);

    if (gFieldState->flags & 0x40000) {
        return 0;
    }

    return 1;
}
u8 func_08096288(PrizeCardWork* w, void* a) {
    s32 v;

    v = w->unk_F6 << 8;
    ApproachValue(&w->unk_F7, 0, w->unk_FA);
    ApproachValue(&v, 0, w->unk_FA);
    ApproachValue(&w->pos.x, 0x7800, w->unk_FA);
    ApproachValue(&w->pos.y, 0x5800, w->unk_FA);
    w->unk_F6 = v >> 8;

    if (w->unk_FA != 0) {
        w->unk_FA--;
    }

    if (w->unk_F2 <= 255) {
        w->unk_F2 += 2;
    } else {
        w->unk_F2 = 256;
    }

    w->x = w->pos.x >> 8;
    w->y2 = w->pos.y >> 8;
    func_08096638(w);
    w->unk_FB++;

    if (w->cardId > 0x1C2) {
        if (w->unk_FB == 120) {
            w->unk_FB = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)func_08096390);
        }
    } else if (w->unk_FB == 30) {
        w->unk_FB = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08096390);
    }

    TaskPoolUpdate(&w->tasks);

    if (gFieldState->flags & 0x40000) {
        return 0;
    }

    return 1;
}
u8 func_08096390(PrizeCardWork* w) {
    w->unk_F6 += 32;
    w->unk_EA = (gFieldState->actor.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    w->unk_EC = (gFieldState->actor.fieldPosition.y >> 8) + (gFieldState->actor.fieldPosition.z >> 8) -
                (gFieldState->y >> 8);
    w->x += (w->unk_EA - w->x) >> 3;
    w->y2 += (w->unk_EC - w->y2) >> 3;
    w->scaleX -= 10;
    w->scaleY -= 10;

    if (w->scaleX > 10 && !(gFieldState->flags & 0x40000)) {
        return 1;
    }

    return 0;
}
static void PrizeCard_2(PrizeCardWork* w) {
    u16 pal;
    s32 affine;
    void* gfx;
    CardBack* back;
    CardDef* def;
    s16 v;
    s32 t;

    t = w->unk_FC[0];
    pal = 0;

    if (t == 0) {
        pal = 0x800;
    }

    if (w->scaleX == 0x100 && w->unk_F6 == 0) {
        affine = 0;
    } else {
        affine = AllocObjAffine(w->unk_F6, w->scaleX, w->scaleY, 1);
    }

    def = &gCardDefs[w->cardId];
    DrawSprite(w->x, (u16)w->y2 - 8, def->gfx, w->tiles, w->palette,
               affine, pal, (u16)(w->unk_E4 + 1));
    back = &gUnk_08F709B0[w->stat.unk_0E];
    DrawSprite(w->x, (u16)w->y2 - 8, back->gfx, w->tiles2, w->palette2,
               affine, pal, (u16)w->unk_E4);
    gfx = gUnk_09EE981C[w->stat.unk_04];
    DrawSprite(w->x, (u16)w->y2 - 8, gfx, w->tiles4, w->palette2, affine,
               pal, (u16)(w->unk_E4 - 1));

    if (w->unk_FC[0] == 0) {
        v = 204 - ((w->pos.unk_0C - w->pos.z) >> 7);

        if (v <= 2) {
            v = 2;
        }

        DrawSprite(w->x2, w->y, gUnk_09EE1380[0],
                   w->tiles5, w->palette3, AllocObjAffine(0, v, v, 0), pal,
                   (u16)(w->unk_E4 + 2));
    }

    TaskPoolDraw(&w->tasks);
}

static void PrizeCard_3(PrizeCardWork* w) {
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
}

void func_08096638(PrizeCardWork* w) {
    w->scaleX = (-gSineTable[((w->unk_F8 + 0x80) & 0xFF) + 0x40] * w->unk_F2) >> 8;
    w->scaleY = (-gSineTable[((w->unk_F7 + 0x80) & 0xFF) + 0x40] * w->unk_F2) >> 8;

    if ((u16)(w->scaleX + 2) <= 4) {
        w->scaleX = 2;
    }

    if ((u16)(w->scaleY + 2) <= 4) {
        w->scaleY = 2;
    }
}

void func_080966B4(TaskPool* pool, s32 x, s32 y, s32 z) {
    PrizeCardTaskArgs args;

    args.x = x;
    args.y = y;
    args.z = z;
    args.cardId = func_08096D48(gGameState.world, 0);
    func_08096700(pool, &args);
}
void func_080966E4(TaskPool* pool, s32 x, s32 y, s32 z, s32 cardId) {
    PrizeCardTaskArgs args;

    args.x = x;
    args.y = y;
    args.z = z;
    args.cardId = cardId;
    func_08096700(pool, &args);
}

void func_08096700(TaskPool* pool, PrizeCardTaskArgs* args) {
    TaskCreate(pool, &gUnk_09EE75D8, args);
}

TaskDesc gUnk_09EE75D8 = {
    "PrizeCard",
    (TaskInitFunc)PrizeCard_0,
    (TaskUpdateFunc)PrizeCard_1,
    (TaskFunc)PrizeCard_2,
    (TaskFunc)PrizeCard_3,
    sizeof(PrizeCardWork),
};
