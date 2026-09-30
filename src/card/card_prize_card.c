#include "card_localized_data.h"
#include "msg_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "msg_api.h"
#include "card_battle.h"
#include "mode_test_api.h"
#include "m4a_song.h"
#include "game_state.h"
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
#include "card.h"
#include "card_message_assets.h"
#include <stddef.h>
#include "game.h"
#include "bos4_api.h"
#include "sprites_btl.h"
#include "sprites_card_pictures.h"
#include "songs.h"

u8 UpdateFieldPrizeCardShow(PrizeCardWork* w, void* a);
u8 UpdateFieldPrizeCardShrink(PrizeCardWork* w);
u8 UpdateFieldPrizeCardFlight(PrizeCardWork* w, void* a);
void AimFieldPrizeCardAtCenter(PrizeCardWork* w);
void CreateFieldPrizeCardTask(TaskPool* pool, PrizeCardTaskArgs* args);

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
    w->stat = *(CardStat*)&def->kind;

    if (gCardDefs[w->cardId].flags & 12) {
        back = &gCardBacks[3];
    } else {
        back = &gCardBacks[w->stat.category];
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
    w->pos.ground = 0;
    w->rotation = 24;
    FldPosInitGround(&w->pos);
    w->vz = -(GetRandom() % 129 + 0x300);
    w->speed = GetRandom() % 129 + 0x80;
    w->moveAngle = GetRandom() % 256;
    w->scaleX = 0x80;
    w->scaleY = 0x80;
    w->scale = 0x80;
    w->flipAngleY = 0;
    w->flipAngleX = 0;
    q = &w->collider;
    ColliderInit(q, 5, 30, 10);
    ColliderSetDisabled(q, 1);
    ColliderSetPosition(q, w->pos.x, w->pos.y, w->pos.z);
    w->timer = 0;
    w->collected[0] = 0;
    w->steps = 0;
    w->holdTimer = 0;
    TaskPoolInit(&w->tasks, 1);
}
static u8 PrizeCard_1(PrizeCardWork* w, void* a) {
    s32 k = 112;
    s16 x;
    s16 y;

    w->prevPos = w->pos;
    w->vz += 0x38;
    w->pos.z += w->vz;
    w->pos.x += (gSineTable[(u8)w->moveAngle] * w->speed) >> 8;
    w->pos.y += (-gSineTable[(u8)w->moveAngle + 0x40] * w->speed) >> 8;

    if (IsFldPosBlocked(&w->pos) != 0) {
        w->moveAngle = w->moveAngle + k + GetRandom() % 33;

        do {
            w->pos.x = w->prevPos.x;
            w->pos.y = w->prevPos.y;
        } while (0);
    } else {
        w->pos.ground = GetFldPosGround(&w->pos);
    }

    if (w->pos.z - 0x800 > w->pos.ground) {
        w->pos.z = w->pos.ground - 0x800;
        w->vz = -((w->vz * 217) >> 8);

        if (w->vz > -0x200) {
            w->vz = -0x200;
        }
    }

    if (w->collider.colliding != 0) {
        w->collected[0] = 1;
        m4aSongNumStart(SONG_SYS_ITEMGET);

        if (w->cardId <= 0x1C1) {
            ObtainCard(w->cardId);
        }

        SetTaskUpdate(a, (TaskUpdateFunc)UpdateFieldPrizeCardFlight);
        x = (w->pos.x >> 8) - (gFieldState->x >> 8);
        y = (w->pos.y >> 8) + (w->pos.z >> 8) - (gFieldState->y >> 8);
        w->pos.x = x << 8;
        w->pos.y = y << 8;
        ColliderSetDisabled(&w->collider, 1);
        w->steps = 16;
        w->priority = 50;
        AimFieldPrizeCardAtCenter(w);
        return 1;
    }

    ColliderSetPosition(&w->collider, w->pos.x, w->pos.y, w->pos.z);
    w->x = (w->pos.x >> 8) - (gFieldState->x >> 8);
    w->y2 = (w->pos.y >> 8) + (w->pos.z >> 8) - (gFieldState->y >> 8);
    w->x2 = (w->pos.x >> 8) - (gFieldState->x >> 8);
    w->y = (w->pos.y >> 8) + (w->pos.ground >> 8) - (gFieldState->y >> 8);
    w->priority = -0x1004 - (w->pos.y >> 8) * 4;
    UpdateFieldPrizeCardScale(w);
    w->flipAngleX += 2;

    if (w->timer == 20) {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->timer <= 59) {
        w->timer++;
    }

    if (gFieldState->flags & 0x40000) {
        return 0;
    }

    return 1;
}
void AimFieldPrizeCardAtCenter(PrizeCardWork* w) {
    s32 cx = 0x7800;
    s32 cy = 0x5000;
    s32 v[2];

    v[0] = cx - w->pos.x;
    v[1] = cy - w->pos.y;
    w->distance = NormalizeVector2D8(&v[0], &v[1]);
    w->dirX = -v[0];
    w->dirY = -v[1];
    w->speed = 0x300;
    w->vz = 2;
}
u8 UpdateFieldPrizeCardFlight(PrizeCardWork* w, void* a) {
    s32 v[2];

    if (w->speed < 0) {
        v[0] = 0x7800 - w->pos.x;
        v[1] = 0x5000 - w->pos.y;
        NormalizeVector2D8(&v[0], &v[1]);
        w->dirX = -v[0];
        w->dirY = -v[1];

        if (w->distance <= 0x7FF) {
            w->steps = 0;
            w->rotation = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateFieldPrizeCardShow);
#ifdef VERSION_EU
            CreateCardNameDisplay(&w->tasks, eu_0805E924(gCardDefs[w->cardId].name));
#else
            CreateCardNameDisplay(&w->tasks, gCardDefs[w->cardId].name);
#endif
        }
    }

    w->pos.x += (w->dirX * w->speed) >> 8;
    w->pos.y += (w->dirY * w->speed) >> 8;
    w->rotation += 32;
    w->flipAngleY += (64 - w->flipAngleY) >> 4;
    w->flipAngleX = 0;
    w->distance = VectorLength2D(0x7800 - w->pos.x, 0x5000 - w->pos.y);
    w->speed -= w->vz;
    w->vz += 2;

    if (w->scale <= 255) {
        w->scale += 3;
    }

    w->x = w->pos.x >> 8;
    w->y2 = w->pos.y >> 8;
    UpdateFieldPrizeCardScale(w);

    if (gFieldState->flags & 0x40000) {
        return 0;
    }

    return 1;
}
u8 UpdateFieldPrizeCardShow(PrizeCardWork* w, void* a) {
    s32 v;

    v = w->rotation << 8;
    ApproachValue(&w->flipAngleY, 0, w->steps);
    ApproachValue(&v, 0, w->steps);
    ApproachValue(&w->pos.x, 0x7800, w->steps);
    ApproachValue(&w->pos.y, 0x5800, w->steps);
    w->rotation = v >> 8;

    if (w->steps != 0) {
        w->steps--;
    }

    if (w->scale <= 255) {
        w->scale += 2;
    } else {
        w->scale = 256;
    }

    w->x = w->pos.x >> 8;
    w->y2 = w->pos.y >> 8;
    UpdateFieldPrizeCardScale(w);
    w->holdTimer++;

    if (w->cardId > 0x1C2) {
        if (w->holdTimer == 120) {
            w->holdTimer = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateFieldPrizeCardShrink);
        }
    } else if (w->holdTimer == 30) {
        w->holdTimer = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateFieldPrizeCardShrink);
    }

    TaskPoolUpdate(&w->tasks);

    if (gFieldState->flags & 0x40000) {
        return 0;
    }

    return 1;
}
u8 UpdateFieldPrizeCardShrink(PrizeCardWork* w) {
    w->rotation += 32;
    w->targetX = (gFieldState->actor.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    w->targetY = (gFieldState->actor.fieldPosition.y >> 8) + (gFieldState->actor.fieldPosition.z >> 8) -
                (gFieldState->y >> 8);
    w->x += (w->targetX - w->x) >> 3;
    w->y2 += (w->targetY - w->y2) >> 3;
    w->scaleX -= 10;
    w->scaleY -= 10;

    if (w->scaleX > 10 && !(gFieldState->flags & 0x40000)) {
        return 1;
    }

    return 0;
}
static void PrizeCard_2(PrizeCardWork* w) {
    u16 pal;
    ObjAffine* affine;
    void* gfx;
    CardBack* back;
    CardDef* def;
    s16 v;
    s32 t;

    t = w->collected[0];
    pal = 0;

    if (t == 0) {
        pal = 0x800;
    }

    if (w->scaleX == 0x100 && w->rotation == 0) {
        affine = 0;
    } else {
        affine = AllocObjAffine(w->rotation, w->scaleX, w->scaleY, 1);
    }

    def = &gCardDefs[w->cardId];
    DrawSprite(w->x, (u16)w->y2 - 8, def->gfx, w->tiles, w->palette,
               affine, pal, (u16)(w->priority + 1));
    back = &gCardBacks[w->stat.category];
    DrawSprite(w->x, (u16)w->y2 - 8, back->gfx, w->tiles2, w->palette2,
               affine, pal, (u16)w->priority);
    gfx = gUnk_09EE981C[w->stat.value];
    DrawSprite(w->x, (u16)w->y2 - 8, gfx, w->tiles4, w->palette2, affine,
               pal, (u16)(w->priority - 1));

    if (w->collected[0] == 0) {
        v = 204 - ((w->pos.ground - w->pos.z) >> 7);

        if (v <= 2) {
            v = 2;
        }

        DrawSprite(w->x2, w->y, gUnk_09EE1380[0],
                   w->tiles5, w->palette3, AllocObjAffine(0, v, v, 0), pal,
                   (u16)(w->priority + 2));
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

void UpdateFieldPrizeCardScale(PrizeCardWork* w) {
    w->scaleX = (-gSineTable[((w->flipAngleX + 0x80) & 0xFF) + 0x40] * w->scale) >> 8;
    w->scaleY = (-gSineTable[((w->flipAngleY + 0x80) & 0xFF) + 0x40] * w->scale) >> 8;

    if ((u16)(w->scaleX + 2) <= 4) {
        w->scaleX = 2;
    }

    if ((u16)(w->scaleY + 2) <= 4) {
        w->scaleY = 2;
    }
}

void SpawnRandomFieldPrizeCard(TaskPool* pool, s32 x, s32 y, s32 z) {
    PrizeCardTaskArgs args;

    args.x = x;
    args.y = y;
    args.z = z;
    args.cardId = PickPrizeMapCardForWorld(gGameState.world, 0);
    CreateFieldPrizeCardTask(pool, &args);
}
void SpawnFieldPrizeCard(TaskPool* pool, s32 x, s32 y, s32 z, s32 cardId) {
    PrizeCardTaskArgs args;

    args.x = x;
    args.y = y;
    args.z = z;
    args.cardId = cardId;
    CreateFieldPrizeCardTask(pool, &args);
}

void CreateFieldPrizeCardTask(TaskPool* pool, PrizeCardTaskArgs* args) {
    TaskCreate(pool, &gTaskDescFieldPrizeCard, args);
}

TaskDesc gTaskDescFieldPrizeCard = {
    "PrizeCard",
    (TaskInitFunc)PrizeCard_0,
    (TaskUpdateFunc)PrizeCard_1,
    (TaskDrawFunc)PrizeCard_2,
    (TaskDestroyFunc)PrizeCard_3,
    sizeof(PrizeCardWork),
};
