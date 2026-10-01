#include "macros.h"
#include "registration_data.h"
#include "system_state.h"
#include "card_battle.h"
#include "mode_test_api.h"
#include "player_progression.h"
#include "m4a_song.h"
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
#include "taskpool.h"
#include "key.h"
#include "gba/syscall.h"
#include "malloc.h"
#include "card.h"
#include "game.h"
#include "sprites_btl.h"
#include "sprites_card.h"
#include "sprites_premire_chance.h"
#include "sprites_card_pictures.h"
#include "gba/io_reg.h"
#include "card_ids.h"
#include "gba/keys.h"
#include "songs.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "bg_animation_data.h"
#include "boss_card_data.h"
#include "card_api.h"
#include "card_def_data.h"
#include "card_label_data.h"
#include "card_types.h"
#include "card_ui_types.h"
#include "types.h"
#include <stddef.h>

struct CardListWork* gCardListWork EWRAM_COMMON(4);

extern u8 gUnk_09618CD8[];
extern u8 gUnk_09613E98[];
extern u8 gUnk_09618D18[];
#ifdef VERSION_EU

#define LANGSTR(x) (((void**)(x))[gLanguage])
#else
#define LANGSTR(x) (x)
#endif
void CreatePremireChanceCardTasks(PremireChanceWork* w);

static const u32 sFriendCardIds[8] = {
    CARD_ID(CARD_GOOFY, 0),
    CARD_ID(CARD_DONALD_DUCK, 0),
    CARD_ID(CARD_ALADDIN, 0),
    CARD_ID(CARD_ARIEL, 0),
    CARD_ID(CARD_JACK, 0),
    CARD_ID(CARD_PETER_PAN, 0),
    CARD_ID(CARD_THE_BEAST, 0),
    CARD_ID(CARD_THE_KING, 0),
};

void Friend_card_0(PickupCardWork* w, s32* args) {
    Collider* p;

    w->cardId = args[3];
    w->posX = args[0];
    w->posY = args[1];
    w->posZ = args[2];
    w->floor = 0;
    w->moveAngle = GetRandom();
    w->unk_1A4 = -(GetRandom() % 129 + 0x300);
    w->speed = GetRandom() % 129 + 0x80;
    w->flipAngleX = 0;
    w->flipAngleY = 0;
    w->angle = 24;
    w->scaleX = 0x80;
    w->scaleY = 0x80;
    w->scale = 0x80;
    w->screenSpace = 0;
    w->unk_1CB = 0;
    w->unk_1CC = 0;
    w->timer = 0;
    w->visible = 1;
    w->cardDef = &gCardDefs[args[3]];

    if (w->cardDef->flags & CARD_DEF_FLAG_FRIEND) {
        w->backCategory = 3;
    } else {
        w->backCategory = w->cardDef->category;
    }

    w->palette = LoadObjPalette(gCard00Palette, 32);
    w->tiles3 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    w->tiles2 = LoadObjTiles(w->cardDef->tiles, 0x300);
    w->palette2 = LoadObjPalette(w->cardDef->palette, 32);
    w->tiles4 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    w->palette3 = LoadObjPalette(gBStatesPalette, 32);
    p = &w->collider;
    ColliderInit(p, 5, 8, 10);
    ColliderSetPosition(p, w->posX, w->posY, w->posZ);
    TaskPoolInit(&w->tasks, 1);
    gBtlWork->prizeCount++;
}

void Heartless_card_0(PickupCardWork* w, s32* args) {
    Collider* p;

    w->cardId = args[3];
    w->posX = args[0];
    w->posY = args[1];
    w->posZ = args[2];
    w->floor = 0;
    w->moveAngle = GetRandom();
    w->unk_1A4 = -(GetRandom() % 129 + 0x300);
    w->speed = GetRandom() % 129 + 0x80;
    w->flipAngleX = 0;
    w->flipAngleY = 0;
    w->angle = 24;
    w->scaleX = 0x80;
    w->scaleY = 0x80;
    w->scale = 0x80;
    w->screenSpace = 0;
    w->unk_1CB = 0;
    w->unk_1CC = 0;
    w->timer = 0;
    w->visible = 1;
    w->cardDef = &gCardDefs[args[3]];

    if (w->cardDef->flags & CARD_DEF_FLAG_FRIEND) {
        w->backCategory = 3;
    } else {
        w->backCategory = w->cardDef->category;
    }

    w->tiles = LoadObjTiles(gCardBacks[w->backCategory].tiles, 0x280);
    w->palette = LoadObjPalette(gCard00Palette, 32);
    w->tiles3 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    w->tiles2 = LoadObjTiles(w->cardDef->tiles, 0x300);
    w->palette2 = LoadObjPalette(w->cardDef->palette, 32);
    w->tiles4 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    w->palette3 = LoadObjPalette(gBStatesPalette, 32);
    p = &w->collider;
    ColliderInit(p, 5, 8, 10);
    ColliderSetPosition(p, w->posX, w->posY, w->posZ);
    TaskPoolInit(&w->tasks, 1);
    gBtlWork->prizeCount++;
}

void Gimmick_card_0(PickupCardWork* w, GimmickCardArgs* args) {
    Collider* p;

    w->cardId = args->cardId;
    w->posX = args->x;
    w->posY = args->y;
    w->posZ = args->z;
    w->floor = 0;
    w->moveAngle = GetRandom();
    w->unk_1A4 = -((u16)(GetRandom() % 129) + 0x300);
    w->speed = (u16)(GetRandom() % 129) + 0x80;
    w->flipAngleX = 0;
    w->flipAngleY = 0;
    w->angle = 24;
    w->scaleX = 0x80;
    w->scaleY = 0x80;
    w->scale = 0x80;
    w->screenSpace = 0;
    w->unk_1CB = 0;
    w->unk_1CC = 0;
    w->timer = 0;
    w->visible = 1;
    w->cardDef = &gCardDefs[args->cardId];
    w->backCategory = w->cardDef->category;
    w->palette = LoadObjPalette(gCard00Palette, 32);
    w->tiles3 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    w->tiles2 = LoadObjTiles(w->cardDef->tiles, 0x300);
    w->palette2 = LoadObjPalette(w->cardDef->palette, 32);
    w->tiles4 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    w->palette3 = LoadObjPalette(gBStatesPalette, 32);
    p = &w->collider;
    ColliderInit(p, 5, 8, 10);
    ColliderSetPosition(p, w->posX, w->posY, w->posZ);
    TaskPoolInit(&w->tasks, 1);
    gBtlWork->prizeCount++;
}

void StartPickupCardFlight(PickupCardWork* w, u8 kind) {
    s32 dx;
    s32 dy;
    s32 tx;
    s32 ty;

    if (kind == 1) {
        tx = 0x7800;
        ty = 0x5000;
    } else {
        tx = 0;
        ty = 0xA000;
    }

    dx = tx - w->posX;
    dy = ty - w->posY;
    w->distance = NormalizeVector2D8(&dx, &dy);
    w->dirX = -dx;
    w->dirY = -dy;
    w->speed = 0x300;
    w->unk_1A4 = 2;
}

s32 Friend_card_1(PickupCardWork* w, void* a) {
    s16 sx;
    s32 t;
    u16 n;
    s16 sy;

    if (gBtlWork->phase == 4) {
        return 0;
    }

    w->unk_1A4 += gBtlWork->gravity;
    w->posZ += w->unk_1A4;
    w->posX += (gSineTable[w->moveAngle] * w->speed) >> 8;
    w->posY += (-gSineTable[w->moveAngle + 64] * w->speed) >> 8;

    if (ClampBattlePosition(&w->posX, &w->posY, -10, -10) != 0) {
        w->moveAngle = (u8)(w->moveAngle + 112) + GetRandom() % 33;
    }

    if (w->posZ - 0x800 > w->floor) {
        w->posZ = w->floor - 0x800;
        w->unk_1A4 = -((204 * w->unk_1A4) >> 8);
        w->moveAngle = GetAngle(w->posX, w->posY,
                               gBtlWork->actor->x,
                               gBtlWork->actor->y);
        w->moveAngle = (u8)(w->moveAngle + 224) + GetRandom() % 65;

        if (w->unk_1A4 > -0x200) {
            w->unk_1A4 = -0x200;
        }
    }

    if (gBtlWork->hcEffect == 6) {
        ColliderSetRadius(&w->collider, 50);
    } else {
        ColliderSetRadius(&w->collider, 10);
    }

    if (ApplyBattleBounds(&w->posX, &w->posY, &w->posZ,
                          &w->floor) != 0) {
        w->moveAngle = (u8)(w->moveAngle + 112) + GetRandom() % 33;
    }

    if (w->collider.colliding != 0) {
        m4aSongNumStart(SONG_SYS_ITEMGET);

#ifdef VERSION_EU
        w->priority = 10;
#endif

        if (gCardBattleState != NULL) {
            WorldToScreen(&sx, &sy, w->posX, w->posY,
                          w->posZ);
            w->posX = sx << 8;
            w->posY = sy << 8;
            w->screenSpace = 1;
            ColliderSetDisabled(&w->collider, 1);
            StartPickupCardFlight(w, 0);
#ifdef VERSION_EU
            w->visible = 1;
#endif
            SetTaskUpdate(a, (TaskUpdateFunc)FlyPickupCardToDeck);
        }

        return 1;
    }

    ColliderSetPosition(&w->collider, w->posX, w->posY,
                  w->posZ);
    w->scaleX =
        (-gSineTable[((w->flipAngleX + 128) & 0xFF) + 64] *
         w->scale) >> 8;
    w->scaleY =
        (-gSineTable[((w->flipAngleY + 128) & 0xFF) + 64] *
         w->scale) >> 8;

    if ((u16)(w->scaleX + 2) <= 4) {
        w->scaleX = 2;
    }

    if ((u16)(w->scaleY + 2) <= 4) {
        w->scaleY = 2;
    }

    w->flipAngleX += 2;
    w->priority = -0x1004 - (w->posY >> 8) * 4;
    TaskPoolUpdate(&w->tasks);

    if (gBtlWork->flags & BTL_FLAG_TUTORIAL) {
        return 1;
    }

    n = w->timer;

    if (n > 359) {
        return 0;
    }

    t = n + 1;
    w->timer = t;

    if (w->timer > 279 && t % 4 == 0) {
        w->visible ^= 1;
    }

    return 1;
}

s32 Gimmick_card_1(PickupCardWork* w, void* a) {
    s16 sx;
    s32 t;
    u16 n;
    s16 sy;

    if (gBtlWork->phase == 4) {
        return 0;
    }

    w->unk_1A4 += 56;
    w->posZ += w->unk_1A4;
    w->posX += (gSineTable[w->moveAngle] * w->speed) >> 8;
    w->posY += (-gSineTable[w->moveAngle + 64] * w->speed) >> 8;

    if (ClampBattlePosition(&w->posX, &w->posY, -10, -10) != 0) {
        w->moveAngle = (u8)(w->moveAngle + 112) + GetRandom() % 33;
    }

    if (w->posZ - 0x800 > w->floor) {
        w->posZ = w->floor - 0x800;
        w->unk_1A4 = -((204 * w->unk_1A4) >> 8);
        w->moveAngle = GetAngle(w->posX, w->posY,
                               gBtlWork->actor->x,
                               gBtlWork->actor->y);
        w->moveAngle = (u8)(w->moveAngle + 224) + GetRandom() % 65;

        if (w->unk_1A4 > -0x200) {
            w->unk_1A4 = -0x200;
        }
    }

    if (gBtlWork->hcEffect == 6) {
        ColliderSetRadius(&w->collider, 50);
    } else {
        ColliderSetRadius(&w->collider, 10);
    }

    if (ApplyBattleBounds(&w->posX, &w->posY, &w->posZ,
                          &w->floor) != 0) {
        w->moveAngle = (u8)(w->moveAngle + 112) + GetRandom() % 33;
    }

    if (w->collider.colliding != 0) {
        m4aSongNumStart(SONG_SYS_ITEMGET);

#ifdef VERSION_EU
        w->priority = 10;
#endif

        if (gCardBattleState != NULL) {
            WorldToScreen(&sx, &sy, w->posX, w->posY,
                          w->posZ);
            w->posX = sx << 8;
            w->posY = sy << 8;
            w->screenSpace = 1;
            ColliderSetDisabled(&w->collider, 1);
            StartPickupCardFlight(w, 0);
#ifdef VERSION_EU
            w->visible = 1;
#endif
            SetTaskUpdate(a, (TaskUpdateFunc)FlyPickupCardToDeck);
        }

        return 1;
    }

    ColliderSetPosition(&w->collider, w->posX, w->posY,
                  w->posZ);
    w->scaleX =
        (-gSineTable[((w->flipAngleX + 128) & 0xFF) + 64] *
         w->scale) >> 8;
    w->scaleY =
        (-gSineTable[((w->flipAngleY + 128) & 0xFF) + 64] *
         w->scale) >> 8;

    if ((u16)(w->scaleX + 2) <= 4) {
        w->scaleX = 2;
    }

    if ((u16)(w->scaleY + 2) <= 4) {
        w->scaleY = 2;
    }

    w->flipAngleX += 2;
    w->priority = -0x1004 - (w->posY >> 8) * 4;
    TaskPoolUpdate(&w->tasks);

    n = w->timer;

    if (n > 359) {
        gCardBattleState->gimmickCardCount -= 1;
        return 0;
    }

    t = n + 1;
    w->timer = t;

    if (w->timer > 279 && t % 4 == 0) {
        w->visible ^= 1;
    }

    return 1;
}

u8 FlyPickupCardToDeck(PickupCardWork* w) {
    s32 dx;
    s32 dy;
    u16 t;

    if (gBtlWork->phase == 4) {
        return 0;
    }

    if (w->speed < 0) {
        dx = -w->posX;
        dy = 0xA000 - w->posY;
        NormalizeVector2D8(&dx, &dy);
        w->dirX = -dx;
        w->dirY = -dy;

        if (w->distance < 0x800) {
            if (w->cardId >= 655 && w->cardId <= 659) {
                gCardBattleState->pickedGimmickCardId = w->cardId;
            } else {
                gCardBattleState->pickedFriendCardId = w->cardId;
            }

            return 0;
        }
    }

    w->posX += (w->dirX * w->speed) >> 8;
    w->posY += (w->dirY * w->speed) >> 8;
    w->angle += 32;
    w->flipAngleY += (64 - w->flipAngleY) >> 4;
    w->flipAngleX = 0;
    w->distance = VectorLength2D(-w->posX, 0xA000 - w->posY);
    w->speed -= w->unk_1A4;
    w->unk_1A4 += 2;
    t = w->scale;

    if ((s16)t <= 255) {
        w->scale = t + 3;
    }

    w->scaleX = (-gSineTable[((w->flipAngleX + 128) & 0xFF) + 64] * w->scale) >> 8;
    w->scaleY = (-gSineTable[((w->flipAngleY + 128) & 0xFF) + 64] * w->scale) >> 8;

    if ((u16)(w->scaleX + 2) <= 4) {
        w->scaleX = 2;
    }

    if ((u16)(w->scaleY + 2) <= 4) {
        w->scaleY = 2;
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 FlyHeartlessCardToPlayer(PickupCardWork* w) {
    s16 x;
    s16 y;

    w->angle += 32;
    WorldToScreen(&x, &y, gBtlWork->actor->x, gBtlWork->actor->y, gBtlWork->actor->z);
    w->posX += ((x << 8) - w->posX) >> 3;
    w->posY += ((y << 8) - w->posY) >> 3;
    w->scaleX -= 10;
    w->scaleY -= 10;

    if (w->scaleX <= 10) {
        return 0;
    }

    return 1;
}

s32 WaitHeartlessCardName(PickupCardWork* w, void* a) {
    w->timer += 1;

    if (w->timer == 60) {
        SetTaskUpdate(a, (TaskUpdateFunc)FlyHeartlessCardToPlayer);
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

s32 FlyHeartlessCardToCenter(PickupCardWork* w, void* a) {
    s32 dx = 0;
    s32 dy = 0;
    u16 t;

    if (w->speed < 0) {
        dx = 0x7800 - w->posX;
        dy = 0x5000 - w->posY;
        NormalizeVector2D8(&dx, &dy);
        w->dirX = -dx;
        w->dirY = -dy;

        if (w->distance < 0x800) {
            w->flipAngleY = 0;
            w->angle = 0;
            w->flipAngleX = 0;
            w->posX = 0x7800;
            w->posY = 0x5000;
            w->scaleX = 0x100;
            w->scaleY = 0x100;
#ifdef VERSION_EU
            CreateCardNameDisplay(&w->tasks, eu_0805E924(gCardDefs[w->cardId].name));
#else
            CreateCardNameDisplay(&w->tasks, gCardDefs[w->cardId].name);
#endif
            SetTaskUpdate(a, (TaskUpdateFunc)WaitHeartlessCardName);
            w->timer = 0;
            w->priority = 50;
            return 1;
        }
    }

    w->posX += (w->dirX * w->speed) >> 8;
    w->posY += (w->dirY * w->speed) >> 8;
    w->angle += 32;
    w->flipAngleY += (64 - w->flipAngleY) >> 4;
    w->flipAngleX = 0;
    w->distance = VectorLength2D(0x7800 - w->posX, 0x5000 - w->posY);
    w->speed -= w->unk_1A4;
    w->unk_1A4 += 2;
    t = w->scale;

    if ((s16)t <= 255) {
        w->scale = t + 3;
    }

    w->scaleX = (-gSineTable[((w->flipAngleX + 128) & 0xFF) + 64] * w->scale) >> 8;
    w->scaleY = (-gSineTable[((w->flipAngleY + 128) & 0xFF) + 64] * w->scale) >> 8;

    if ((u16)(w->scaleX + 2) <= 4) {
        w->scaleX = 2;
    }

    if ((u16)(w->scaleY + 2) <= 4) {
        w->scaleY = 2;
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

s32 Heartless_card_1(PickupCardWork* w, void* a) {
    s16 x;
    s16 y;

    w->unk_1A4 += 0x38;
    w->posZ += w->unk_1A4;
    w->posX += (gSineTable[w->moveAngle] * w->speed) >> 8;
    w->posY += (-gSineTable[w->moveAngle + 64] * w->speed) >> 8;

    if (ClampBattlePosition(&w->posX, &w->posY, -10, -10) != 0) {
        w->moveAngle = (u8)(w->moveAngle + 0x70) + GetRandom() % 33;
    }

    if (w->posZ - 0x800 > w->floor) {
        w->posZ = w->floor - 0x800;
        w->unk_1A4 = -((w->unk_1A4 * 204) >> 8);
        w->moveAngle = GetAngle(w->posX, w->posY, gBtlWork->actor->x, gBtlWork->actor->y);
        w->moveAngle = (u8)(w->moveAngle + 0xE0) + GetRandom() % 65;

        if (w->unk_1A4 > -0x200) {
            w->unk_1A4 = -0x200;
        }
    }

    if (gBtlWork->hcEffect == 6) {
        ColliderSetRadius(&w->collider, 50);
    } else {
        ColliderSetRadius(&w->collider, 10);
    }

    if (ApplyBattleBounds(&w->posX, &w->posY, &w->posZ, &w->floor)) {
        w->moveAngle = (u8)(w->moveAngle + 0x70) + GetRandom() % 33;
    }

    if (w->collider.colliding != 0) {
        m4aSongNumStart(SONG_SYS_ITEMGET);
#ifdef VERSION_EU
        w->priority = 10;
#endif
        ObtainCard(w->cardId);
        WorldToScreen(&x, &y, w->posX, w->posY, w->posZ);
        w->posX = x << 8;
        w->posY = y << 8;
        w->screenSpace = 1;
        ColliderSetDisabled(&w->collider, 1);
        StartPickupCardFlight(w, 1);
        SetTaskUpdate(a, (TaskUpdateFunc)FlyHeartlessCardToCenter);
        return 1;
    }

    ColliderSetPosition(&w->collider, w->posX, w->posY, w->posZ);
    w->scaleX = (-gSineTable[((w->flipAngleX + 128) & 0xFF) + 64] * w->scale) >> 8;
    w->scaleY = (-gSineTable[((w->flipAngleY + 128) & 0xFF) + 64] * w->scale) >> 8;

    if ((u16)(w->scaleX + 2) <= 4) {
        w->scaleX = 2;
    }

    if ((u16)(w->scaleY + 2) <= 4) {
        w->scaleY = 2;
    }

    w->flipAngleX += 2;
    w->priority = -0x1004 - ((w->posY >> 8) << 2);
    TaskPoolUpdate(&w->tasks);
    return 1;
}

void PickupCardDraw(PickupCardWork* w) {
    s16 x;
    s16 y;
    ObjAffine* affine;
    s16 v;
    u8 kind;

    if (w->visible != 0) {
        if (w->screenSpace == 0) {
            w->spriteFlags = GetBattleSpritePriorityFlags(w->posY);
            WorldToScreen(&x, &y, w->posX, w->posY,
                          w->posZ);
        } else {
            w->spriteFlags = 0;
            x = w->posX >> 8;
            y = w->posY >> 8;
        }

        affine = AllocObjAffine(w->angle, w->scaleX,
                                w->scaleY, 0);
        DrawSprite(x, (u16)y - 8,
                   gCardBacks[w->cardDef->category].gfx,
                   gCardBattleState->tiles[w->cardDef->category],
                   w->palette, affine,
                   w->spriteFlags, w->priority);
        DrawSprite(x, (u16)y - 8, w->cardDef->gfx,
                   w->tiles2, w->palette2, affine,
                   w->spriteFlags, w->priority + 1);
        kind = w->cardDef->value;
        DrawSprite(x, (u16)y - 8, gUnk_09EE981C[kind],
                   w->tiles3, w->palette, affine,
                   w->spriteFlags, w->priority - 2);
        v = 204 - ((w->floor - w->posZ) >> 7);

        if (v <= 2) {
            v = 2;
        }

        if (w->screenSpace == 0) {
            WorldToScreen(&w->x, &w->y,
                          w->posX, w->posY,
                          w->floor);
            DrawSprite(w->x, w->y,
                       gUnk_09EE1380[0], w->tiles4,
                       w->palette3, AllocObjAffine(0, v, v, 0),
                       w->spriteFlags, w->priority + 2);
        }

        TaskPoolDraw(&w->tasks);
    }
}

void Heartless_card_2(PickupCardWork* w) {
    s16 x;
    s16 y;
    ObjAffine* affine;
    s16 v;

    if (w->visible != 0) {
        if (w->screenSpace == 0) {
            w->spriteFlags = GetBattleSpritePriorityFlags(w->posY);
            WorldToScreen(&x, &y, w->posX, w->posY,
                          w->posZ);
        } else {
            w->spriteFlags = 0;
            x = w->posX >> 8;
            y = w->posY >> 8;
        }

        affine = AllocObjAffine(w->angle, w->scaleX,
                                w->scaleY, 0);
        DrawSprite(x, (u16)y - 8,
                   gCardBacks[w->cardDef->category].gfx,
                   w->tiles, w->palette, affine,
                   w->spriteFlags, w->priority);
        DrawSprite(x, (u16)y - 8, w->cardDef->gfx,
                   w->tiles2, w->palette2, affine,
                   w->spriteFlags, w->priority + 1);
        v = 204 - ((w->floor - w->posZ) >> 7);

        if (v <= 2) {
            v = 2;
        }

        if (w->screenSpace == 0) {
            WorldToScreen(&w->x, &w->y,
                          w->posX, w->posY,
                          w->floor);
            DrawSprite(w->x, w->y,
                       gUnk_09EE1380[0], w->tiles4,
                       w->palette3, AllocObjAffine(0, v, v, 0),
                       w->spriteFlags, w->priority + 2);
        }

        TaskPoolDraw(&w->tasks);
    }
}

void PickupCardDestroy(PickupCardWork* w) {
    ReleaseObjPalette(w->palette);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjPalette(w->palette2);
    ReleaseObjTiles(w->tiles4);
    ReleaseObjPalette(w->palette3);
    ColliderUnregister(&w->collider);
    TaskPoolDestroy(&w->tasks);
    // @bug Leaving a battle frees gCardBattleState before this card is destroyed (NULL write).
    gCardBattleState->friendCardCount = 0;
    gBtlWork->prizeCount--;
}

void Heartless_card_3(PickupCardWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjPalette(w->palette2);
    ReleaseObjTiles(w->tiles4);
    ReleaseObjPalette(w->palette3);
    ColliderUnregister(&w->collider);
    TaskPoolDestroy(&w->tasks);
    gBtlWork->prizeCount--;
}

void CreateFriendCardTask(void* pool, s16 x, s16 y, s16 z, u8 idx) {
    s32 args[4];

    if (gCardBattleState != NULL) {
        if (gCardBattleState->addedFriendCards[0] <= 4) {
            if (gCardBattleState->friendCardCount == 0) {
                args[0] = x << 8;
                args[1] = y << 8;
                args[2] = z << 8;
                args[3] = sFriendCardIds[idx] + GetRandom() % 9;
                TaskCreate(pool, &gTaskDescFriendCard, args);
                gCardBattleState->friendCardCount++;
            }
        }
    }
}

void CreateHeartlessCardTask(void* pool, s16 a, s16 b, s16 c, u16 d) {
    s32 args[4];
    const s32* t;

    t = gEnemyCardIds[d];
    args[0] = a << 8;
    args[1] = b << 8;
    args[2] = c << 8;
    args[3] = t[0];
    TaskCreate(pool, &gTaskDescHeartlessCard, args);
}

void CreateGimmickCardTask(void* pool, s16 a, s16 b, s16 c, u16 d) {
    s32 args[4];

    if (gCardBattleState != NULL && gCardBattleState->gimmickCardCount == 0) {
        gCardBattleState->gimmickCardCount++;
        args[0] = a << 8;
        args[1] = b << 8;
        args[2] = c << 8;
        args[3] = d;
        TaskCreate(pool, &gTaskDescGimmickCard, args);
    }
}

void StockNameSora_0(StockNameWork* w, const s32* src) {
    u8 i;
    s32* dst;
    s32* q;
    const s32* s;
    s32 z;
    ObjTiles* obj;

    if (src != NULL) {
        s = src;

        for (i = 0; i < 6; i++) {
            dst = w->stockNames;
            q = &dst[i];
            *q = s[i];
        }

        w->cycling = 1;
    } else {
        w->cycling = 0;
    }

    z = 0;
    w->stockNameIndex = z;
    w->unk_04 = z;
    obj = AllocSpriteFrameTiles(0x3C0);
    w->tiles = obj;

    if (w->cycling == 0) {
#ifdef VERSION_EU
        void** t;
        void* u;

        t = (void**)LANGSTR(gStockNameSprites[gCardBattleState->soraStockName].sprites);
        u = LANGSTR(gStockNameSprites[gCardBattleState->soraStockName].tiles);
        UpdateSpriteFrameTiles(obj, t[gStockNameSprites[gCardBattleState->soraStockName].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(obj, gStockNameSprites[gCardBattleState->soraStockName].sprites[gStockNameSprites[gCardBattleState->soraStockName].spriteIndex], gStockNameSprites[gCardBattleState->soraStockName].tiles);
#endif
    } else {
#ifdef VERSION_EU
        void** t;
        void* u;

        t = (void**)LANGSTR(gStockNameSprites[w->stockNames[0]].sprites);
        u = LANGSTR(gStockNameSprites[w->stockNames[0]].tiles);
        UpdateSpriteFrameTiles(obj, t[gStockNameSprites[w->stockNames[0]].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(obj, gStockNameSprites[w->stockNames[0]].sprites[gStockNameSprites[w->stockNames[0]].spriteIndex], gStockNameSprites[w->stockNames[0]].tiles);
#endif
    }

    w->palette = LoadObjPalette(gBStatesPalette, 32);
    w->visible = 1;
    w->stockName = gCardBattleState->soraStockName;
}

u8 StockNameSora_1(StockNameWork* w) {
#ifdef VERSION_EU
    void** t = (void**)LANGSTR(gStockNameSprites[w->stockNames[w->stockNameIndex]].sprites);
    void* u = LANGSTR(gStockNameSprites[w->stockNames[w->stockNameIndex]].tiles);
#endif

    if (gCardBattleState->soraStockNameShown == 0 || gCardBattleState->soraStockName != w->stockName) {
        return 0;
    }

    if ((gFrameCounter >> 5) & 1) {
        w->visible = 1;
    } else {
        w->visible = 0;
    }

    if (w->cycling == 1 && w->visible != 0) {
        w->stockNameIndex++;

        if (w->stockNames[w->stockNameIndex] == -1) {
            w->stockNameIndex = 0;
        }

#ifdef VERSION_EU
        UpdateSpriteFrameTiles(w->tiles, t[gStockNameSprites[w->stockNames[w->stockNameIndex]].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(w->tiles, gStockNameSprites[w->stockNames[w->stockNameIndex]].sprites[gStockNameSprites[w->stockNames[w->stockNameIndex]].spriteIndex], gStockNameSprites[w->stockNames[w->stockNameIndex]].tiles);
#endif
    }

    return 1;
}

void StockNameSora_2(StockNameWork* w) {
    if (w->visible != 0) {
        DrawSprite(64, 14, 0, w->tiles, w->palette, 0,
#ifdef VERSION_EU
                   SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC,
#else
                   0,
#endif
                   10);
    }
}

void StockNameRiku_0(StockNameWork* w, const s32* src) {
    u8 i;
    s32* dst;
    s32* q;
    const s32* s;
    s32 z;
    ObjTiles* obj;

    if (src != NULL) {
        s = src;

        for (i = 0; i < 6; i++) {
            dst = w->stockNames;
            q = &dst[i];
            *q = s[i];
        }

        w->cycling = 1;
    } else {
        w->cycling = 0;
    }

    z = 0;
    w->stockNameIndex = z;
    w->unk_04 = z;
    obj = AllocSpriteFrameTiles(0x3C0);
    w->tiles = obj;

    if (w->cycling == 0) {
#ifdef VERSION_EU
        void** t;
        void* u;

        t = (void**)LANGSTR(gStockNameSprites[gCardBattleState->rikuStockName].sprites);
        u = LANGSTR(gStockNameSprites[gCardBattleState->rikuStockName].tiles);
        UpdateSpriteFrameTiles(obj, t[gStockNameSprites[gCardBattleState->rikuStockName].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(obj, gStockNameSprites[gCardBattleState->rikuStockName].sprites[gStockNameSprites[gCardBattleState->rikuStockName].spriteIndex], gStockNameSprites[gCardBattleState->rikuStockName].tiles);
#endif
    } else {
#ifdef VERSION_EU
        void** t;
        void* u;

        t = (void**)LANGSTR(gStockNameSprites[w->stockNames[0]].sprites);
        u = LANGSTR(gStockNameSprites[w->stockNames[0]].tiles);
        UpdateSpriteFrameTiles(obj, t[gStockNameSprites[w->stockNames[0]].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(obj, gStockNameSprites[w->stockNames[0]].sprites[gStockNameSprites[w->stockNames[0]].spriteIndex], gStockNameSprites[w->stockNames[0]].tiles);
#endif
    }

    w->palette = LoadObjPalette(gBStatesPalette, 32);
    w->visible = 1;
    w->stockName = gCardBattleState->rikuStockName;
}

u8 StockNameRiku_1(StockNameWork* w) {
#ifdef VERSION_EU
    void** t = (void**)LANGSTR(gStockNameSprites[w->stockNames[w->stockNameIndex]].sprites);
    void* u = LANGSTR(gStockNameSprites[w->stockNames[w->stockNameIndex]].tiles);
#endif

    if (gCardBattleState->rikuStockNameShown == 0 || gCardBattleState->rikuStockName != w->stockName) {
        return 0;
    }

    if ((gFrameCounter >> 5) & 1) {
        w->visible = 0;
    } else {
        w->visible = 1;
    }

    if (w->cycling == 1 && w->visible != 0) {
        w->stockNameIndex++;

        if (w->stockNames[w->stockNameIndex] == -1) {
            w->stockNameIndex = 0;
        }

#ifdef VERSION_EU
        UpdateSpriteFrameTiles(w->tiles, t[gStockNameSprites[w->stockNames[w->stockNameIndex]].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(w->tiles, gStockNameSprites[w->stockNames[w->stockNameIndex]].sprites[gStockNameSprites[w->stockNames[w->stockNameIndex]].spriteIndex], gStockNameSprites[w->stockNames[w->stockNameIndex]].tiles);
#endif
    }

    return 1;
}

void StockNameRiku_2(StockNameWork* w) {
    if (gRikuBtlWork->hcEffect != 28 && w->visible != 0) {
        DrawSprite(120, 14, 0, w->tiles, w->palette, 0, 0, 10);
    }
}

void StockNameRiku_3(StockNameWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    gCardBattleState->unk_0D9 = 0;
    w->visible = 0;
    gCardBattleState->unk_0CA = 256;
}

void StockNameSora_3(StockNameWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    gCardBattleState->unk_0D8 = 0;
    w->visible = 0;
    gCardBattleState->unk_0C8 = 256;
}

void Premire_Chance_0(PremireChanceWork* w) {
    u8 n = 0;
    u8 i;
    s32 j;
    u16* cards;
    u32 zero0 = 0;
    u32 zero1;
    u32 zero2;

    CpuSet(&zero0, w, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(PremireChanceWork) / 4);
    gCardListWork = EwramAlloc(sizeof(CardListWork));
    w->slots = EwramAlloc(sizeof(CardSlot) * 100);
    zero1 = 0;
    CpuSet(&zero1, gCardListWork, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(CardListWork) / 4);
    zero2 = 0;
    CpuSet(&zero2, w->slots, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(CardSlot) * 100 / 4);
    cards = GetActiveDeck()->cards;
    w->tiles2 = AllocObjTiles(0x120, 0);
    w->palette2 = LoadObjPalette(gUnk_09618CD8, 32);
    SetObjTileSource(w->tiles2, gUnk_093F4578);
    AnimInit(&w->anim, gUnk_09EF1170, gUnk_09EF1150);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_FRENCH:
        w->tiles = LoadObjTiles(gUnkEu_0916292A, 0x340);
        break;
    case LANGUAGE_GERMAN:
        w->tiles = LoadObjTiles(gUnkEu_091633A4, 0x3C0);
        break;
    case LANGUAGE_ITALIAN:
        w->tiles = LoadObjTiles(gUnkEu_09162FB8, 0x3C0);
        break;
    case LANGUAGE_SPANISH:
        w->tiles = LoadObjTiles(gUnkEu_09162C8C, 0x300);
        break;
    case LANGUAGE_ENGLISH:
        w->tiles = LoadObjTiles(gUnk_0908BB80, 0x3C0);
        break;
    default:
        w->tiles = LoadObjTiles(gUnk_0908BB80, 0x3C0);
        break;
    }
#else
    w->tiles = LoadObjTiles(gUnk_0908BB80, 0x3C0);
#endif
    w->palette = LoadObjPalette(gUnk_09613E98, 32);
    w->tiles5 = LoadObjTiles(gUnk_0908BFB2, 0x3C0);
    w->tiles3 = AllocObjTiles(0x3C0, 0);
    w->palette3 = LoadObjPalette(gUnk_09618D18, 32);
    SetObjTileSource(w->tiles3, gUnk_093F47E4);
    AnimInit(&w->anim2, gUnk_09EF1194, gUnk_09EF1180);
    AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
    w->gfx2 = AnimGetGfx(&w->anim2);
    w->tiles4 = LoadObjTiles(gUnk_0905F03C, 0x80);
    w->palette4 = LoadObjPalette(gBStatesPalette, 32);
    FadeToAmount(FADE_MODE_BLACK, 16, 16);
    FadeSetPaletteExcluded(w->palette->index + 16, 1);
    FadeSetPaletteExcluded(w->palette3->index + 16, 1);
    FadeSetPaletteExcluded(w->palette2->index + 16, 1);
    FadeSetPaletteExcluded(w->palette4->index + 16, 1);

#ifdef VERSION_EU
    for (i = 0, n = 0; i < DECK_SIZE; i++) {
#else
    for (i = 0; i < DECK_SIZE; i++) {
#endif
        if (cards[i] != 0xFFFF) {
            if (!(gCardCollection[cards[i]] & 0x8000)) {
                if (gCardDefs[gCardCollection[cards[i]] & CARD_ID_MASK].category != 3) {
                    if (gCardDefs[gCardCollection[cards[i]] & CARD_ID_MASK].category != 2) {
                        w->slots[n].cardId = gCardCollection[cards[i]] & CARD_ID_MASK;
                        w->slots[n].index = i;
                        w->slots[n].unk_06 = n;
                        w->slots[n].stocked = 0;
                        n++;
                    }
                }
            }
        }
    }

    if (n < 10) {
        j = 0;

        do {
            if (cards[j] != 0xFFFF) {
                if (!(gCardCollection[cards[j]] & 0x8000)) {
                    if (gCardDefs[gCardCollection[cards[j]] & CARD_ID_MASK].category != 3) {
                        if (gCardDefs[gCardCollection[cards[j]] & CARD_ID_MASK].category != 2) {
                            w->slots[n].cardId = gCardCollection[cards[j]] & CARD_ID_MASK;
                            w->slots[n].index = j;
                            w->slots[n].unk_06 = n;
                            w->slots[n].stocked = 0;
                            n++;
                        }
                    }
                }
            }

            j++;

            if (j > 98) {
                j = 0;
            }
        } while (n < 10);
    }

    w->cardCount = n;
    TaskPoolInit(&w->tasks, w->cardCount + 1);
    ListPoolInit(&gCardListWork->cards);
    gCardListWork->selectedCard = 0;
    gCardListWork->effectCount = 0;
    TaskPoolInit(&gCardListWork->effectTasks, 24);
    CreatePremireChanceCardTasks(w);
    w->spinDelay = 10;
    w->advanced = 0;
    w->stopped = 0;
    w->inputEnabled = 1;
    w->resultPending = 1;
    w->unk_87 = 0;
    w->stopTimer = 0;
    w->titleSteps = 16;
    w->slideSteps = 16;
    w->titleX = -0x80;
    w->topY = -0x800;
    w->bottomY = 0xA000;
}

u8 UpdatePremireChanceSpin(PremireChanceWork* w, void* a) {
    PremireChanceCardWork* n;
    s32 t;
    s32 z;

    if (w->inputEnabled != 0) {
        if ((GetKeysPressed() & A_BUTTON) && w->stopped == 0) {
            w->stopped = 1;
            m4aSongNumStart(SONG_SYS_ITEMGET);
        }

        if ((GetKeysPressed() & B_BUTTON) && w->stopped != 1) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            w->titleSteps = 16;
            w->slideSteps = 16;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdatePremireChanceClose);
            n = ListPoolFirst(&gCardListWork->cards);

            while (n != NULL) {
                n->state |= 0xFF;
                w->resultPending = 0;
                n = ListPoolNext(&n->node);
            }

            TaskPoolUpdate(&w->tasks);
            TaskPoolUpdate(&gCardListWork->effectTasks);
            z = 0;
            w->unk_87 = 1;
            w->inputEnabled = z;
            return 1;
        }
    }

    n = ListPoolFirst(&gCardListWork->cards);

    if (w->stopped == 0) {
        while (n != NULL) {
            t = n->steps;

            if (t == 0) {
                m4aSongNumStart(SONG_SYS_CLICK);

                if (n->position < w->cardCount - 1) {
                    n->position++;
                } else {
                    n->position = t;
                }

                n->steps = w->spinDelay;
                w->advanced = 1;
            }

            n = ListPoolNext(&n->node);
        }
    } else {
        w->unk_87 = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdatePremireChanceStop);
    }

    if (w->spinDelay == 4 || w->spinDelay == 10) {
        w->inputEnabled = 1;
    } else {
        w->inputEnabled = 0;
    }

    if (w->advanced != 0) {
        if (w->spinDelay > 4) {
            w->spinDelay--;
        }

        w->advanced = 0;
    }

    w->gfx = AnimUpdate(&w->anim);
    w->gfx2 = AnimUpdate(&w->anim2);
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&gCardListWork->effectTasks);
    return 1;
}

u8 Premire_Chance_1(PremireChanceWork* w, void* a) {
    s32 v;
    u8* p;
    PremireChanceCardWork* n;

    n = ListPoolFirst(&gCardListWork->cards);

    if (n != NULL && n->state == 1) {
        SetTaskUpdate(a, (TaskUpdateFunc)UpdatePremireChanceSpin);
    }

    p = &w->slideSteps;

    if (*p != 0) {
        ApproachValue(&w->topY, 0, *p);
        ApproachValue(&w->bottomY, 0x9800, *p);
    } else {
        v = w->titleX << 8;
        p = &w->titleSteps;
        ApproachValue(&v, 0, *p);
        w->titleX = v >> 8;
    }

    (*p)--;
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&gCardListWork->effectTasks);
    return 1;
}

void Premire_Chance_2(PremireChanceWork* w) {
    if (w->unk_87 == 0) {
        DrawSprite(62, 50, w->gfx, w->tiles2, w->palette2, 0, 0, 0);
        DrawSprite(53, 64, w->gfx2, w->tiles3, w->palette3, 0, 0, 0);
    }

    if (w->inputEnabled != 0) {
        DrawSprite(88, 70, gUnk_09EE98EC[0], w->tiles4, w->palette4, 0, 0, 0);
    }

#ifdef VERSION_EU
    DrawSprite(w->titleX, 0, gPremireChanceTitles[gLanguage][0], w->tiles, w->palette, 0, 0, 0);
#else
    DrawSprite(w->titleX, 0, gUnk_09EEA16C[0], w->tiles, w->palette, 0, 0, 0);
#endif
    DrawSprite(120, w->topY >> 8, gUnk_09EEA174[0], w->tiles5, w->palette, 0, 0, 60);
    DrawSprite(120, w->bottomY >> 8, gUnk_09EEA174[1], w->tiles5, w->palette, 0, 0, 60);
    TaskPoolDraw(&w->tasks);
    TaskPoolDraw(&gCardListWork->effectTasks);
}

void Premire_Chance_3(PremireChanceWork* w) {
    TaskPoolDestroy(&gCardListWork->effectTasks);
    EwramFree(w->slots);
    EwramFree(gCardListWork);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjTiles(w->tiles3);
    ReleaseObjTiles(w->tiles4);
    ReleaseObjTiles(w->tiles);
    ReleaseObjTiles(w->tiles5);
    FadeSetPaletteExcluded(w->palette->index + 16, 0);
    FadeSetPaletteExcluded(w->palette3->index + 16, 0);
    FadeSetPaletteExcluded(w->palette2->index + 16, 0);
    FadeSetPaletteExcluded(w->palette4->index + 16, 0);
    ReleaseObjPalette(w->palette2);
    ReleaseObjPalette(w->palette3);
    ReleaseObjPalette(w->palette4);
    ReleaseObjPalette(w->palette);
    SetJiminyFlag(0xF5);
    TaskPoolDestroy(&w->tasks);
}

void CreatePremireChanceCardTasks(PremireChanceWork* w) {
    u8 i;

    for (i = 0; i < w->cardCount; i++) {
        w->slots[i].unk_06 = i;
        TaskCreate(&w->tasks, &gTaskDescPremireChanceCard, &w->slots[i]);
    }
}

u8 UpdatePremireChanceStop(PremireChanceWork* w, void* a) {
    PremireChanceCardWork* n;
    TaskPool* pool;
    u8 z;
    u8 t;
    u8* q;

    n = ListPoolFirst(&gCardListWork->cards);
    w->gfx = AnimUpdate(&w->anim);
    w->gfx2 = AnimUpdate(&w->anim2);
    w->spinDelay = 0;
    w->stopTimer++;
    w->inputEnabled = 0;

    if (w->resultPending != 0) {
        while (n != NULL) {
            if (n->steps == 0) {
                if (n->position == 3) {
                    n->state = 2;
                    ConvertActiveDeckCardToPremium(n->deckIndex);
                } else {
                    n->state = 3;
                }

                w->resultPending = 0;
            }

            n = ListPoolNext(&n->node);
        }
    }

    t = w->stopTimer;
    pool = &w->tasks;

    if (t == 30) {
        q = &w->unk_87;
        z = 0;
        *q = 1;
        SetBgPriority(2, 0);
        BgAnimInit(2, 0x8000, 0x80);
        BgAnimStart(&gBgAnimDefPremireChance, 120, 60);
        w->bgAnimDuration = BgAnimGetDuration(&gBgAnimDefPremireChance);
        w->resultTimer = z;
        gBldCnt = (BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_OBJ);
        gBldAlpha = BLDALPHA_BLEND(16, 16);
        BgAnimUpdate();
        FadeSetPaletteExcluded(10, 1);
        FadeSetPaletteExcluded(11, 1);
        FadeSetPaletteExcluded(12, 1);
        FadeSetPaletteExcluded(13, 1);
        FadeSetPaletteExcluded(14, 1);
        FadeSetPaletteExcluded(15, 1);
        TaskCreate(pool, &gTaskDescCardName, 0);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdatePremireChanceResult);
    }

    TaskPoolUpdate(pool);
    TaskPoolUpdate(&gCardListWork->effectTasks);
    return 1;
}

u8 UpdatePremireChanceResult(PremireChanceWork* w, void* a) {
    ListPoolFirst(&gCardListWork->cards);
    BgAnimUpdate();
    w->gfx = AnimUpdate(&w->anim);
    w->gfx2 = AnimUpdate(&w->anim2);
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&gCardListWork->effectTasks);

    if ((GetKeysPressed() & A_BUTTON)
#ifdef VERSION_EU
        && w->resultTimer > 8
#endif
    ) {
        w->titleSteps = 16;
        w->slideSteps = 16;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdatePremireChanceClose);
    }

#ifdef VERSION_EU
    if (w->resultTimer <= 254) {
        w->resultTimer++;
    }
#endif

    return 1;
}

u8 UpdatePremireChanceClose(PremireChanceWork* w, void* a) {
    s32 v;
    u8* p;

    p = &w->titleSteps;

    if (*p != 0) {
        v = w->titleX << 8;
        ApproachValue(&v, -0x8000, *p);
        w->titleX = v >> 8;
    } else {
        p = &w->slideSteps;

        if (*p == 0) {
            return 0;
        }

        ApproachValue(&w->topY, -0x800, *p);
        ApproachValue(&w->bottomY, 0xA000, *p);
    }

    (*p)--;
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&gCardListWork->effectTasks);
    return 1;
}

TaskDesc gTaskDescFriendCard = {
    "Friend card",
    (TaskInitFunc)Friend_card_0,
    (TaskUpdateFunc)Friend_card_1,
    (TaskDrawFunc)PickupCardDraw,
    (TaskDestroyFunc)PickupCardDestroy,
    sizeof(PickupCardWork),
};

TaskDesc gTaskDescHeartlessCard = {
    "Heartless card",
    (TaskInitFunc)Heartless_card_0,
    (TaskUpdateFunc)Heartless_card_1,
    (TaskDrawFunc)Heartless_card_2,
    (TaskDestroyFunc)Heartless_card_3,
    sizeof(PickupCardWork),
};

TaskDesc gTaskDescGimmickCard = {
    "Gimmick card",
    (TaskInitFunc)Gimmick_card_0,
    (TaskUpdateFunc)Gimmick_card_1,
    (TaskDrawFunc)PickupCardDraw,
    (TaskDestroyFunc)PickupCardDestroy,
    sizeof(PickupCardWork),
};

TaskDesc gTaskDescStockNameSora = {
    "StockName",
    (TaskInitFunc)StockNameSora_0,
    (TaskUpdateFunc)StockNameSora_1,
    (TaskDrawFunc)StockNameSora_2,
    (TaskDestroyFunc)StockNameSora_3,
    sizeof(StockNameWork),
};

TaskDesc gTaskDescStockNameRiku = {
    "StockName",
    (TaskInitFunc)StockNameRiku_0,
    (TaskUpdateFunc)StockNameRiku_1,
    (TaskDrawFunc)StockNameRiku_2,
    (TaskDestroyFunc)StockNameRiku_3,
    sizeof(StockNameWork),
};

#ifdef VERSION_EU
void** gPremireChanceTitles[5] = { gUnk_09EEA16C, &gUnkEu_09F75FB4, &gUnkEu_09F75FCC, &gUnkEu_09F75FC4, &gUnkEu_09F75FBC };
#endif

TaskDesc gTaskDescPremireChance = {
    "Premire Chance",
    (TaskInitFunc)Premire_Chance_0,
    (TaskUpdateFunc)Premire_Chance_1,
    (TaskDrawFunc)Premire_Chance_2,
    (TaskDestroyFunc)Premire_Chance_3,
    sizeof(PremireChanceWork),
};
