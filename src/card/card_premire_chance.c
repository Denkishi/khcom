#include "fade.h"
#include "obj_api.h"
#include "engine_math.h"
#include "listpool.h"
#include "anim.h"
#include "obj.h"
#include "taskpool.h"
#include "card.h"
#include "game.h"
#include "sprites_card_pictures.h"
#include "card_def_data.h"
#include "card_types.h"
#include "types.h"
#include <stddef.h>

s32 UpdatePremireChanceCardAnim(PremireChanceCardWork* w);
void ReleasePremireChanceCardGfx(PremireChanceCardWork* w);
void UpdatePremireChanceCardPos(PremireChanceCardWork* w);
void LoadPremireChanceCardGfx(PremireChanceCardWork* w);
u8 IsPremireChanceCardOnScreen(PremireChanceCardWork* w);
u8 StartPremireChanceCardAnim(PremireChanceCardWork* w, void* a);

static const s16 sPremireChanceCardAngles[9] = { 0, 11, 23, 34, 46, 57, 68, 79, 90 };

static const u8 sPremireChanceCardPriorities[9] = { 6, 4, 2, 0, 2, 4, 6, 8, 12 };

void PremireChanceCard_0(PremireChanceCardWork* w, CardSlot* a) {
    CardDef* def;

    w->gfxLoaded = 0;
    w->tiles4 = 0;

    if (a->unk_06 <= 8) {
        w->angle = sPremireChanceCardAngles[a->unk_06];
    } else {
        w->angle = -0x20;
    }

    w->position = a->unk_06;
    w->deckIndex = a->index;
    def = &gCardDefs[a->cardId];
    w->cardDef = def;

    if (def->flags & (CARD_DEF_FLAG_SUMMON | CARD_DEF_FLAG_FRIEND)) {
        w->cardBack = &gCardBacks[1];
    } else {
        w->cardBack = &gCardBacks[def->category];
    }

    w->radius = 0;
    UpdatePremireChanceCardPos(w);
    ListNodeInit(&w->node, &gCardListWork->cards, w);
    ListPoolAppend(&w->node, &gCardListWork->cards);
    w->state = 0;
    w->scaleX = 0x100;
    w->scaleY = 0x100;
    w->x2 = 0;
    w->y2 = 0;
    w->steps = 32;
    w->premium = 0;
}

u8 UpdatePremireChanceCardSpin(PremireChanceCardWork* w, void* a) {
    s32 v;
    u8 (*fn)(PremireChanceCardWork*, void*);
    u16 lim;

    v = w->angle << 8;

    if (w->position <= 8) {
        ApproachValue(&v, sPremireChanceCardAngles[w->position] << 8, w->steps);
        w->angle = v >> 8;
    } else {
        lim = 0xFFE0;
        w->angle = lim;
    }

    if (w->steps != 0) {
        w->steps--;
    }

    UpdatePremireChanceCardPos(w);

    if (IsPremireChanceCardOnScreen(w)) {
        LoadPremireChanceCardGfx(w);
    } else {
        ReleasePremireChanceCardGfx(w);
    }

    if (w->position == 3) {
        gCardListWork->selectedCard = w;
    }

    switch (w->state) {
    case 2:
        gCardListWork->unk_29 = 0;
        w->steps = 8;
        fn = UpdatePremireChanceCardToCenter;
        SetTaskUpdate(a, (TaskUpdateFunc)fn);
        return fn(w, a);
    case 3:
        w->steps = 10;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdatePremireChanceCardMoveAway);
        break;
    }

    return 1;
}

u8 PremireChanceCard_1(PremireChanceCardWork* w, void* a) {
    s32 v;

    v = w->radius << 8;
    ApproachValue(&v, 0x6800, w->steps);
    w->radius = v >> 8;
    w->steps--;
    UpdatePremireChanceCardPos(w);

    if (w->position <= 8) {
        LoadPremireChanceCardGfx(w);
    } else {
        ReleasePremireChanceCardGfx(w);
    }

    if (w->steps == 0) {
        w->state = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdatePremireChanceCardSpin);
    }

    return 1;
}

void PremireChanceCard_2(PremireChanceCardWork* w) {
    ObjAffine* affine;

    if (w->state == 0xFF) {
        return;
    }

    if (w->gfxLoaded != 0) {
        affine = AllocObjAffine(0, w->scaleX, w->scaleY, 1);
        DrawSprite(w->x + w->x2, w->y + w->y2, w->cardDef->gfx, w->tiles, w->palette2, affine, SPRITE_PRIORITY(1),
                   sPremireChanceCardPriorities[w->position] + 70);
        DrawSprite(w->x + w->x2, w->y + w->y2, w->cardBack->gfx, w->tiles2, w->palette3, affine, SPRITE_PRIORITY(1),
                   sPremireChanceCardPriorities[w->position] + 69);

        if (w->premium == 0) {
            DrawSprite(w->x + w->x2, w->y + w->y2, gUnk_09EE981C[w->cardDef->value], w->tiles3, w->palette3,
                       affine, SPRITE_PRIORITY(1), sPremireChanceCardPriorities[w->position] + 68);
        } else {
            DrawSprite(w->x + w->x2, w->y + w->y2, gUnk_09EE9894[w->cardDef->value], w->tiles5, w->palette,
                       affine, SPRITE_PRIORITY(1), sPremireChanceCardPriorities[w->position] + 68);
        }
    }

    if (w->state == 2 && w->tiles4 != NULL) {
        DrawSprite(w->x + w->x2, w->y + w->y2, w->gfx, w->tiles4, w->palette3, 0, SPRITE_PRIORITY(1),
                   sPremireChanceCardPriorities[w->position] + 67);
    }
}

void PremireChanceCard_3(PremireChanceCardWork* w) {
    ReleasePremireChanceCardGfx(w);

    if (w->tiles4 != NULL) {
        ReleaseObjTiles(w->tiles4);
    }
}

void UpdatePremireChanceCardPos(PremireChanceCardWork* w) {
    w->x = (gSineTable[(u8)w->angle] * w->radius) >> 8;
    w->y = ((-gSineTable[(u8)w->angle + 64] * w->radius) >> 8) + 160;
}

u8 IsPremireChanceCardOnScreen(PremireChanceCardWork* w) {
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

void LoadPremireChanceCardGfx(PremireChanceCardWork* w) {
    if (w->gfxLoaded == 0) {
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
        w->gfxLoaded = 1;
    }
}

void ReleasePremireChanceCardGfx(PremireChanceCardWork* w) {
    if (w->gfxLoaded != 0) {
        ReleaseObjTiles(w->tiles2);
        ReleaseObjPalette(w->palette3);
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette2);
        ReleaseObjTiles(w->tiles3);
        ReleaseObjPalette(w->palette);
        ReleaseObjTiles(w->tiles5);
        w->gfxLoaded = 0;
    }
}

u8 UpdatePremireChanceCardToCenter(PremireChanceCardWork* w, void* a) {
    s32 x;
    s32 y;

    x = w->x << 8;
    y = w->y << 8;
    ApproachValue(&x, 0x7800, w->steps);
    ApproachValue(&y, 0x4600, w->steps);
    w->x = x >> 8;
    w->y = y >> 8;
    w->steps--;

    if (w->steps == 0) {
        SetTaskUpdate(a, (TaskUpdateFunc)StartPremireChanceCardAnim);
    }

    return 1;
}

u8 StartPremireChanceCardAnim(PremireChanceCardWork* w, void* a) {
    w->tiles4 = AllocObjTiles(640, 0);
    SetObjTileSource(w->tiles4, gUnk_0908B1B4);
    AnimInit(&w->anim, gUnk_09EEA164, gUnk_09EEA148);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    SetTaskUpdate(a, (TaskUpdateFunc)UpdatePremireChanceCardAnim);
    return 1;
}

s32 UpdatePremireChanceCardAnim(PremireChanceCardWork* w) {
    w->gfx = AnimUpdate(&w->anim);

    if (w->anim.timer == 0 && w->anim.frame == 4) {
        w->premium = 1;
    }

    return 1;
}

u8 UpdatePremireChanceCardMoveAway(PremireChanceCardWork* w, void* a) {
    s32 v;

    v = w->angle << 8;

    if (w->position <= 2) {
        ApproachValue(&v, -0x2000, w->steps);
    }

    if ((u8)w->position >= 4 && (u8)w->position <= 7) {
        ApproachValue(&v, 0x4400, w->steps);
    }

    w->angle = v >> 8;

    if (w->steps != 0) {
        w->steps--;
    }

    UpdatePremireChanceCardPos(w);

    if (IsPremireChanceCardOnScreen(w)) {
        LoadPremireChanceCardGfx(w);
    } else {
        ReleasePremireChanceCardGfx(w);
    }

    return 1;
}

TaskDesc gTaskDescPremireChanceCard = {
    "Premire Chance",
    (TaskInitFunc)PremireChanceCard_0,
    (TaskUpdateFunc)PremireChanceCard_1,
    (TaskDrawFunc)PremireChanceCard_2,
    (TaskDestroyFunc)PremireChanceCard_3,
    sizeof(PremireChanceCardWork),
};
