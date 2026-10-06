/**
 * card_friend_card.c
 * Card Pickups, Sleight Names and Premium Bonus
 */

#include "macros.h"
#include "registration_data.h"
#include "system_state.h"
#include "card_battle.h"
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
#include "malloc.h"
#include "card.h"
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
#include "gba/macro.h"
#include "sprite_palettes.h"
#include <stddef.h>
#include "lockon.h"
#include "card_friend_card.h"

struct CardListWork* gCardListWork EWRAM_COMMON(4);

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

void Friend_card_0(PickupCardWork* work, s32* args) {
    Collider* p;

    work->cardId = args[3];
    work->posX = args[0];
    work->posY = args[1];
    work->posZ = args[2];
    work->floor = 0;
    work->moveAngle = GetRandom();
    work->vz = -(GetRandom() % 129 + 0x300);
    work->speed = GetRandom() % 129 + 0x80;
    work->flipAngleX = 0;
    work->flipAngleY = 0;
    work->angle = 24;
    work->scaleX = 0x80;
    work->scaleY = 0x80;
    work->scale = 0x80;
    work->screenSpace = 0;
    work->unk_1CB = 0;
    work->unk_1CC = 0;
    work->timer = 0;
    work->visible = 1;
    work->cardDef = &gCardDefs[args[3]];

    if (work->cardDef->flags & CARD_DEF_FLAG_FRIEND) {
        work->backCategory = 3;
    } else {
        work->backCategory = work->cardDef->category;
    }

    work->palette = LoadObjPalette(gCard00Palette, 32);
    work->tiles3 = LoadObjTiles(gCardValueDigitTiles, 0x1E0);
    work->tiles2 = LoadObjTiles(work->cardDef->tiles, 0x300);
    work->palette2 = LoadObjPalette(work->cardDef->palette, 32);
    work->tiles4 = LoadObjTiles(gBtlShadowTiles, 0x100);
    work->palette3 = LoadObjPalette(gBStatesPalette, 32);
    p = &work->collider;
    ColliderInit(p, 5, 8, 10);
    ColliderSetPosition(p, work->posX, work->posY, work->posZ);
    TaskPoolInit(&work->tasks, 1);
    gBtlWork->prizeCount++;
}

void Heartless_card_0(PickupCardWork* work, s32* args) {
    Collider* p;

    work->cardId = args[3];
    work->posX = args[0];
    work->posY = args[1];
    work->posZ = args[2];
    work->floor = 0;
    work->moveAngle = GetRandom();
    work->vz = -(GetRandom() % 129 + 0x300);
    work->speed = GetRandom() % 129 + 0x80;
    work->flipAngleX = 0;
    work->flipAngleY = 0;
    work->angle = 24;
    work->scaleX = 0x80;
    work->scaleY = 0x80;
    work->scale = 0x80;
    work->screenSpace = 0;
    work->unk_1CB = 0;
    work->unk_1CC = 0;
    work->timer = 0;
    work->visible = 1;
    work->cardDef = &gCardDefs[args[3]];

    if (work->cardDef->flags & CARD_DEF_FLAG_FRIEND) {
        work->backCategory = 3;
    } else {
        work->backCategory = work->cardDef->category;
    }

    work->tiles = LoadObjTiles(gCardBacks[work->backCategory].tiles, 0x280);
    work->palette = LoadObjPalette(gCard00Palette, 32);
    work->tiles3 = LoadObjTiles(gCardValueDigitTiles, 0x1E0);
    work->tiles2 = LoadObjTiles(work->cardDef->tiles, 0x300);
    work->palette2 = LoadObjPalette(work->cardDef->palette, 32);
    work->tiles4 = LoadObjTiles(gBtlShadowTiles, 0x100);
    work->palette3 = LoadObjPalette(gBStatesPalette, 32);
    p = &work->collider;
    ColliderInit(p, 5, 8, 10);
    ColliderSetPosition(p, work->posX, work->posY, work->posZ);
    TaskPoolInit(&work->tasks, 1);
    gBtlWork->prizeCount++;
}

void Gimmick_card_0(PickupCardWork* work, GimmickCardArgs* args) {
    Collider* p;

    work->cardId = args->cardId;
    work->posX = args->x;
    work->posY = args->y;
    work->posZ = args->z;
    work->floor = 0;
    work->moveAngle = GetRandom();
    work->vz = -((u16)(GetRandom() % 129) + 0x300);
    work->speed = (u16)(GetRandom() % 129) + 0x80;
    work->flipAngleX = 0;
    work->flipAngleY = 0;
    work->angle = 24;
    work->scaleX = 0x80;
    work->scaleY = 0x80;
    work->scale = 0x80;
    work->screenSpace = 0;
    work->unk_1CB = 0;
    work->unk_1CC = 0;
    work->timer = 0;
    work->visible = 1;
    work->cardDef = &gCardDefs[args->cardId];
    work->backCategory = work->cardDef->category;
    work->palette = LoadObjPalette(gCard00Palette, 32);
    work->tiles3 = LoadObjTiles(gCardValueDigitTiles, 0x1E0);
    work->tiles2 = LoadObjTiles(work->cardDef->tiles, 0x300);
    work->palette2 = LoadObjPalette(work->cardDef->palette, 32);
    work->tiles4 = LoadObjTiles(gBtlShadowTiles, 0x100);
    work->palette3 = LoadObjPalette(gBStatesPalette, 32);
    p = &work->collider;
    ColliderInit(p, 5, 8, 10);
    ColliderSetPosition(p, work->posX, work->posY, work->posZ);
    TaskPoolInit(&work->tasks, 1);
    gBtlWork->prizeCount++;
}

void StartPickupCardFlight(PickupCardWork* work, u8 kind) {
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

    dx = tx - work->posX;
    dy = ty - work->posY;
    work->distance = NormalizeVector2D8(&dx, &dy);
    work->dirX = -dx;
    work->dirY = -dy;
    work->speed = 0x300;
    work->vz = 2;
}

s32 Friend_card_1(PickupCardWork* work, void* task) {
    s16 sx;
    s32 t;
    u16 n;
    s16 sy;

    if (gBtlWork->phase == 4) {
        return 0;
    }

    work->vz += gBtlWork->gravity;
    work->posZ += work->vz;
    work->posX += (gSineTable[work->moveAngle] * work->speed) >> 8;
    work->posY += (-gSineTable[work->moveAngle + 64] * work->speed) >> 8;

    if (ClampBattlePosition(&work->posX, &work->posY, -10, -10) != 0) {
        work->moveAngle = (u8)(work->moveAngle + 112) + GetRandom() % 33;
    }

    if (work->posZ - 0x800 > work->floor) {
        work->posZ = work->floor - 0x800;
        work->vz = -((204 * work->vz) >> 8);
        work->moveAngle = GetAngle(work->posX, work->posY,
                               gBtlWork->actor->x,
                               gBtlWork->actor->y);
        work->moveAngle = (u8)(work->moveAngle + 224) + GetRandom() % 65;

        if (work->vz > -0x200) {
            work->vz = -0x200;
        }
    }

    if (gBtlWork->hcEffect == 6) {
        ColliderSetRadius(&work->collider, 50);
    } else {
        ColliderSetRadius(&work->collider, 10);
    }

    if (ApplyBattleBounds(&work->posX, &work->posY, &work->posZ,
                          &work->floor) != 0) {
        work->moveAngle = (u8)(work->moveAngle + 112) + GetRandom() % 33;
    }

    if (work->collider.colliding) {
        m4aSongNumStart(SONG_SYS_ITEMGET);

#ifdef VERSION_EU
        work->priority = 10;
#endif

        if (gCardBattleState != NULL) {
            WorldToScreen(&sx, &sy, work->posX, work->posY,
                          work->posZ);
            work->posX = sx << 8;
            work->posY = sy << 8;
            work->screenSpace = 1;
            ColliderSetDisabled(&work->collider, 1);
            StartPickupCardFlight(work, 0);
#ifdef VERSION_EU
            work->visible = 1;
#endif
            SetTaskUpdate(task, (TaskUpdateFunc)FlyPickupCardToDeck);
        }

        return 1;
    }

    ColliderSetPosition(&work->collider, work->posX, work->posY,
                  work->posZ);
    work->scaleX =
        (-COS(work->flipAngleX + 128) *
         work->scale) >> 8;
    work->scaleY =
        (-COS(work->flipAngleY + 128) *
         work->scale) >> 8;

    if ((u16)(work->scaleX + 2) <= 4) {
        work->scaleX = 2;
    }

    if ((u16)(work->scaleY + 2) <= 4) {
        work->scaleY = 2;
    }

    work->flipAngleX += 2;
    work->priority = -0x1004 - (work->posY >> 8) * 4;
    TaskPoolUpdate(&work->tasks);

    if (gBtlWork->flags & BTL_FLAG_TUTORIAL) {
        return 1;
    }

    n = work->timer;

    if (n > 359) {
        return 0;
    }

    t = n + 1;
    work->timer = t;

    if (work->timer > 279 && t % 4 == 0) {
        work->visible ^= 1;
    }

    return 1;
}

s32 Gimmick_card_1(PickupCardWork* work, void* task) {
    s16 sx;
    s32 t;
    u16 n;
    s16 sy;

    if (gBtlWork->phase == 4) {
        return 0;
    }

    work->vz += 56;
    work->posZ += work->vz;
    work->posX += (gSineTable[work->moveAngle] * work->speed) >> 8;
    work->posY += (-gSineTable[work->moveAngle + 64] * work->speed) >> 8;

    if (ClampBattlePosition(&work->posX, &work->posY, -10, -10) != 0) {
        work->moveAngle = (u8)(work->moveAngle + 112) + GetRandom() % 33;
    }

    if (work->posZ - 0x800 > work->floor) {
        work->posZ = work->floor - 0x800;
        work->vz = -((204 * work->vz) >> 8);
        work->moveAngle = GetAngle(work->posX, work->posY,
                               gBtlWork->actor->x,
                               gBtlWork->actor->y);
        work->moveAngle = (u8)(work->moveAngle + 224) + GetRandom() % 65;

        if (work->vz > -0x200) {
            work->vz = -0x200;
        }
    }

    if (gBtlWork->hcEffect == 6) {
        ColliderSetRadius(&work->collider, 50);
    } else {
        ColliderSetRadius(&work->collider, 10);
    }

    if (ApplyBattleBounds(&work->posX, &work->posY, &work->posZ,
                          &work->floor) != 0) {
        work->moveAngle = (u8)(work->moveAngle + 112) + GetRandom() % 33;
    }

    if (work->collider.colliding) {
        m4aSongNumStart(SONG_SYS_ITEMGET);

#ifdef VERSION_EU
        work->priority = 10;
#endif

        if (gCardBattleState != NULL) {
            WorldToScreen(&sx, &sy, work->posX, work->posY,
                          work->posZ);
            work->posX = sx << 8;
            work->posY = sy << 8;
            work->screenSpace = 1;
            ColliderSetDisabled(&work->collider, 1);
            StartPickupCardFlight(work, 0);
#ifdef VERSION_EU
            work->visible = 1;
#endif
            SetTaskUpdate(task, (TaskUpdateFunc)FlyPickupCardToDeck);
        }

        return 1;
    }

    ColliderSetPosition(&work->collider, work->posX, work->posY,
                  work->posZ);
    work->scaleX =
        (-COS(work->flipAngleX + 128) *
         work->scale) >> 8;
    work->scaleY =
        (-COS(work->flipAngleY + 128) *
         work->scale) >> 8;

    if ((u16)(work->scaleX + 2) <= 4) {
        work->scaleX = 2;
    }

    if ((u16)(work->scaleY + 2) <= 4) {
        work->scaleY = 2;
    }

    work->flipAngleX += 2;
    work->priority = -0x1004 - (work->posY >> 8) * 4;
    TaskPoolUpdate(&work->tasks);

    n = work->timer;

    if (n > 359) {
        gCardBattleState->gimmickCardCount -= 1;
        return 0;
    }

    t = n + 1;
    work->timer = t;

    if (work->timer > 279 && t % 4 == 0) {
        work->visible ^= 1;
    }

    return 1;
}

u8 FlyPickupCardToDeck(PickupCardWork* work) {
    s32 dx;
    s32 dy;
    u16 t;

    if (gBtlWork->phase == 4) {
        return 0;
    }

    if (work->speed < 0) {
        dx = -work->posX;
        dy = 0xA000 - work->posY;
        NormalizeVector2D8(&dx, &dy);
        work->dirX = -dx;
        work->dirY = -dy;

        if (work->distance < 0x800) {
            if (work->cardId >= 655 && work->cardId <= 659) {
                gCardBattleState->pickedGimmickCardId = work->cardId;
            } else {
                gCardBattleState->pickedFriendCardId = work->cardId;
            }

            return 0;
        }
    }

    work->posX += (work->dirX * work->speed) >> 8;
    work->posY += (work->dirY * work->speed) >> 8;
    work->angle += 32;
    work->flipAngleY += (64 - work->flipAngleY) >> 4;
    work->flipAngleX = 0;
    work->distance = VectorLength2D(-work->posX, 0xA000 - work->posY);
    work->speed -= work->vz;
    work->vz += 2;
    t = work->scale;

    if ((s16)t <= 255) {
        work->scale = t + 3;
    }

    work->scaleX = (-COS(work->flipAngleX + 128) * work->scale) >> 8;
    work->scaleY = (-COS(work->flipAngleY + 128) * work->scale) >> 8;

    if ((u16)(work->scaleX + 2) <= 4) {
        work->scaleX = 2;
    }

    if ((u16)(work->scaleY + 2) <= 4) {
        work->scaleY = 2;
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 FlyHeartlessCardToPlayer(PickupCardWork* work) {
    s16 x;
    s16 y;

    work->angle += 32;
    WorldToScreen(&x, &y, gBtlWork->actor->x, gBtlWork->actor->y, gBtlWork->actor->z);
    work->posX += ((x << 8) - work->posX) >> 3;
    work->posY += ((y << 8) - work->posY) >> 3;
    work->scaleX -= 10;
    work->scaleY -= 10;

    if (work->scaleX <= 10) {
        return 0;
    }

    return 1;
}

s32 WaitHeartlessCardName(PickupCardWork* work, void* task) {
    work->timer += 1;

    if (work->timer == 60) {
        SetTaskUpdate(task, (TaskUpdateFunc)FlyHeartlessCardToPlayer);
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

s32 FlyHeartlessCardToCenter(PickupCardWork* work, void* task) {
    s32 dx = 0;
    s32 dy = 0;
    u16 t;

    if (work->speed < 0) {
        dx = 0x7800 - work->posX;
        dy = 0x5000 - work->posY;
        NormalizeVector2D8(&dx, &dy);
        work->dirX = -dx;
        work->dirY = -dy;

        if (work->distance < 0x800) {
            work->flipAngleY = 0;
            work->angle = 0;
            work->flipAngleX = 0;
            work->posX = 0x7800;
            work->posY = 0x5000;
            work->scaleX = 0x100;
            work->scaleY = 0x100;
#ifdef VERSION_EU
            CreateCardNameDisplay(&work->tasks, GetLocalizedString(gCardDefs[work->cardId].name));
#else
            CreateCardNameDisplay(&work->tasks, gCardDefs[work->cardId].name);
#endif
            SetTaskUpdate(task, (TaskUpdateFunc)WaitHeartlessCardName);
            work->timer = 0;
            work->priority = 50;
            return 1;
        }
    }

    work->posX += (work->dirX * work->speed) >> 8;
    work->posY += (work->dirY * work->speed) >> 8;
    work->angle += 32;
    work->flipAngleY += (64 - work->flipAngleY) >> 4;
    work->flipAngleX = 0;
    work->distance = VectorLength2D(0x7800 - work->posX, 0x5000 - work->posY);
    work->speed -= work->vz;
    work->vz += 2;
    t = work->scale;

    if ((s16)t <= 255) {
        work->scale = t + 3;
    }

    work->scaleX = (-COS(work->flipAngleX + 128) * work->scale) >> 8;
    work->scaleY = (-COS(work->flipAngleY + 128) * work->scale) >> 8;

    if ((u16)(work->scaleX + 2) <= 4) {
        work->scaleX = 2;
    }

    if ((u16)(work->scaleY + 2) <= 4) {
        work->scaleY = 2;
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

s32 Heartless_card_1(PickupCardWork* work, void* task) {
    s16 x;
    s16 y;

    work->vz += 0x38;
    work->posZ += work->vz;
    work->posX += (gSineTable[work->moveAngle] * work->speed) >> 8;
    work->posY += (-gSineTable[work->moveAngle + 64] * work->speed) >> 8;

    if (ClampBattlePosition(&work->posX, &work->posY, -10, -10) != 0) {
        work->moveAngle = (u8)(work->moveAngle + 0x70) + GetRandom() % 33;
    }

    if (work->posZ - 0x800 > work->floor) {
        work->posZ = work->floor - 0x800;
        work->vz = -((work->vz * 204) >> 8);
        work->moveAngle = GetAngle(work->posX, work->posY, gBtlWork->actor->x, gBtlWork->actor->y);
        work->moveAngle = (u8)(work->moveAngle + 0xE0) + GetRandom() % 65;

        if (work->vz > -0x200) {
            work->vz = -0x200;
        }
    }

    if (gBtlWork->hcEffect == 6) {
        ColliderSetRadius(&work->collider, 50);
    } else {
        ColliderSetRadius(&work->collider, 10);
    }

    if (ApplyBattleBounds(&work->posX, &work->posY, &work->posZ, &work->floor)) {
        work->moveAngle = (u8)(work->moveAngle + 0x70) + GetRandom() % 33;
    }

    if (work->collider.colliding) {
        m4aSongNumStart(SONG_SYS_ITEMGET);
#ifdef VERSION_EU
        work->priority = 10;
#endif
        ObtainCard(work->cardId);
        WorldToScreen(&x, &y, work->posX, work->posY, work->posZ);
        work->posX = x << 8;
        work->posY = y << 8;
        work->screenSpace = 1;
        ColliderSetDisabled(&work->collider, 1);
        StartPickupCardFlight(work, 1);
        SetTaskUpdate(task, (TaskUpdateFunc)FlyHeartlessCardToCenter);
        return 1;
    }

    ColliderSetPosition(&work->collider, work->posX, work->posY, work->posZ);
    work->scaleX = (-COS(work->flipAngleX + 128) * work->scale) >> 8;
    work->scaleY = (-COS(work->flipAngleY + 128) * work->scale) >> 8;

    if ((u16)(work->scaleX + 2) <= 4) {
        work->scaleX = 2;
    }

    if ((u16)(work->scaleY + 2) <= 4) {
        work->scaleY = 2;
    }

    work->flipAngleX += 2;
    work->priority = -0x1004 - ((work->posY >> 8) << 2);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void PickupCardDraw(PickupCardWork* work) {
    s16 x;
    u16 y;
    ObjAffine* affine;
    s16 v;
    u8 kind;

    if (work->visible != 0) {
        if (!work->screenSpace) {
            work->spriteFlags = GetBattleSpritePriorityFlags(work->posY);
            WorldToScreen(&x, &y, work->posX, work->posY,
                          work->posZ);
        } else {
            work->spriteFlags = 0;
            x = work->posX >> 8;
            y = work->posY >> 8;
        }

        affine = AllocObjAffine(work->angle, work->scaleX,
                                work->scaleY, 0);
        DrawSprite(x, y - 8,
                   gCardBacks[work->cardDef->category].gfx,
                   gCardBattleState->tiles[work->cardDef->category],
                   work->palette, affine,
                   work->spriteFlags, work->priority);
        DrawSprite(x, y - 8, work->cardDef->gfx,
                   work->tiles2, work->palette2, affine,
                   work->spriteFlags, work->priority + 1);
        kind = work->cardDef->value;
        DrawSprite(x, y - 8, gCardValueDigitFrames[kind],
                   work->tiles3, work->palette, affine,
                   work->spriteFlags, work->priority - 2);
        v = 204 - ((work->floor - work->posZ) >> 7);

        if (v <= 2) {
            v = 2;
        }

        if (!work->screenSpace) {
            WorldToScreen(&work->x, &work->y,
                          work->posX, work->posY,
                          work->floor);
            DrawSprite(work->x, work->y,
                       gBtlShadowFrames[0], work->tiles4,
                       work->palette3, AllocObjAffine(0, v, v, 0),
                       work->spriteFlags, work->priority + 2);
        }

        TaskPoolDraw(&work->tasks);
    }
}

void Heartless_card_2(PickupCardWork* work) {
    s16 x;
    u16 y;
    ObjAffine* affine;
    s16 v;

    if (work->visible != 0) {
        if (!work->screenSpace) {
            work->spriteFlags = GetBattleSpritePriorityFlags(work->posY);
            WorldToScreen(&x, &y, work->posX, work->posY,
                          work->posZ);
        } else {
            work->spriteFlags = 0;
            x = work->posX >> 8;
            y = work->posY >> 8;
        }

        affine = AllocObjAffine(work->angle, work->scaleX,
                                work->scaleY, 0);
        DrawSprite(x, y - 8,
                   gCardBacks[work->cardDef->category].gfx,
                   work->tiles, work->palette, affine,
                   work->spriteFlags, work->priority);
        DrawSprite(x, y - 8, work->cardDef->gfx,
                   work->tiles2, work->palette2, affine,
                   work->spriteFlags, work->priority + 1);
        v = 204 - ((work->floor - work->posZ) >> 7);

        if (v <= 2) {
            v = 2;
        }

        if (!work->screenSpace) {
            WorldToScreen(&work->x, &work->y,
                          work->posX, work->posY,
                          work->floor);
            DrawSprite(work->x, work->y,
                       gBtlShadowFrames[0], work->tiles4,
                       work->palette3, AllocObjAffine(0, v, v, 0),
                       work->spriteFlags, work->priority + 2);
        }

        TaskPoolDraw(&work->tasks);
    }
}

void PickupCardDestroy(PickupCardWork* work) {
    ReleaseObjPalette(work->palette);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette2);
    ReleaseObjTiles(work->tiles4);
    ReleaseObjPalette(work->palette3);
    ColliderUnregister(&work->collider);
    TaskPoolDestroy(&work->tasks);
    // @bug Leaving a battle frees gCardBattleState before this card is destroyed (NULL write).
    gCardBattleState->friendCardCount = 0;
    gBtlWork->prizeCount--;
}

void Heartless_card_3(PickupCardWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette2);
    ReleaseObjTiles(work->tiles4);
    ReleaseObjPalette(work->palette3);
    ColliderUnregister(&work->collider);
    TaskPoolDestroy(&work->tasks);
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

void CreateHeartlessCardTask(void* pool, s16 x, s16 y, s16 z, u16 kind) {
    s32 args[4];
    const s32* t;

    t = gEnemyCardIds[kind];
    args[0] = x << 8;
    args[1] = y << 8;
    args[2] = z << 8;
    args[3] = t[0];
    TaskCreate(pool, &gTaskDescHeartlessCard, args);
}

void CreateGimmickCardTask(void* pool, s16 x, s16 y, s16 z, u16 cardId) {
    s32 args[4];

    if (gCardBattleState != NULL && gCardBattleState->gimmickCardCount == 0) {
        gCardBattleState->gimmickCardCount++;
        args[0] = x << 8;
        args[1] = y << 8;
        args[2] = z << 8;
        args[3] = cardId;
        TaskCreate(pool, &gTaskDescGimmickCard, args);
    }
}

void StockNameSora_0(StockNameWork* work, const s32* src) {
    u8 i;
    s32* dst;
    s32* q;
    const s32* s;
    s32 z;
    ObjTiles* obj;

    if (src != NULL) {
        s = src;

        for (i = 0; i < 6; i++) {
            dst = work->stockNames;
            q = &dst[i];
            *q = s[i];
        }

        work->cycling = 1;
    } else {
        work->cycling = 0;
    }

    z = 0;
    work->stockNameIndex = z;
    work->unk_04 = z;
    obj = AllocSpriteFrameTiles(0x3C0);
    work->tiles = obj;

    if (!work->cycling) {
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

        t = (void**)LANGSTR(gStockNameSprites[work->stockNames[0]].sprites);
        u = LANGSTR(gStockNameSprites[work->stockNames[0]].tiles);
        UpdateSpriteFrameTiles(obj, t[gStockNameSprites[work->stockNames[0]].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(obj, gStockNameSprites[work->stockNames[0]].sprites[gStockNameSprites[work->stockNames[0]].spriteIndex], gStockNameSprites[work->stockNames[0]].tiles);
#endif
    }

    work->palette = LoadObjPalette(gBStatesPalette, 32);
    work->visible = 1;
    work->stockName = gCardBattleState->soraStockName;
}

u8 StockNameSora_1(StockNameWork* work) {
#ifdef VERSION_EU
    void** t = (void**)LANGSTR(gStockNameSprites[work->stockNames[work->stockNameIndex]].sprites);
    void* u = LANGSTR(gStockNameSprites[work->stockNames[work->stockNameIndex]].tiles);
#endif

    if (!gCardBattleState->soraStockNameShown || gCardBattleState->soraStockName != work->stockName) {
        return 0;
    }

    if ((gFrameCounter >> 5) & 1) {
        work->visible = 1;
    } else {
        work->visible = 0;
    }

    if (work->cycling == 1 && work->visible) {
        work->stockNameIndex++;

        if (work->stockNames[work->stockNameIndex] == -1) {
            work->stockNameIndex = 0;
        }

#ifdef VERSION_EU
        UpdateSpriteFrameTiles(work->tiles, t[gStockNameSprites[work->stockNames[work->stockNameIndex]].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(work->tiles, gStockNameSprites[work->stockNames[work->stockNameIndex]].sprites[gStockNameSprites[work->stockNames[work->stockNameIndex]].spriteIndex], gStockNameSprites[work->stockNames[work->stockNameIndex]].tiles);
#endif
    }

    return 1;
}

void StockNameSora_2(StockNameWork* work) {
    if (work->visible) {
        DrawSprite(64, 14, NULL, work->tiles, work->palette, NULL,
#ifdef VERSION_EU
                   SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC,
#else
                   0,
#endif
                   10);
    }
}

void StockNameRiku_0(StockNameWork* work, const s32* src) {
    u8 i;
    s32* dst;
    s32* q;
    const s32* s;
    s32 z;
    ObjTiles* obj;

    if (src != NULL) {
        s = src;

        for (i = 0; i < 6; i++) {
            dst = work->stockNames;
            q = &dst[i];
            *q = s[i];
        }

        work->cycling = 1;
    } else {
        work->cycling = 0;
    }

    z = 0;
    work->stockNameIndex = z;
    work->unk_04 = z;
    obj = AllocSpriteFrameTiles(0x3C0);
    work->tiles = obj;

    if (!work->cycling) {
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

        t = (void**)LANGSTR(gStockNameSprites[work->stockNames[0]].sprites);
        u = LANGSTR(gStockNameSprites[work->stockNames[0]].tiles);
        UpdateSpriteFrameTiles(obj, t[gStockNameSprites[work->stockNames[0]].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(obj, gStockNameSprites[work->stockNames[0]].sprites[gStockNameSprites[work->stockNames[0]].spriteIndex], gStockNameSprites[work->stockNames[0]].tiles);
#endif
    }

    work->palette = LoadObjPalette(gBStatesPalette, 32);
    work->visible = 1;
    work->stockName = gCardBattleState->rikuStockName;
}

u8 StockNameRiku_1(StockNameWork* work) {
#ifdef VERSION_EU
    void** t = (void**)LANGSTR(gStockNameSprites[work->stockNames[work->stockNameIndex]].sprites);
    void* u = LANGSTR(gStockNameSprites[work->stockNames[work->stockNameIndex]].tiles);
#endif

    if (!gCardBattleState->rikuStockNameShown || gCardBattleState->rikuStockName != work->stockName) {
        return 0;
    }

    if ((gFrameCounter >> 5) & 1) {
        work->visible = 0;
    } else {
        work->visible = 1;
    }

    if (work->cycling == 1 && work->visible) {
        work->stockNameIndex++;

        if (work->stockNames[work->stockNameIndex] == -1) {
            work->stockNameIndex = 0;
        }

#ifdef VERSION_EU
        UpdateSpriteFrameTiles(work->tiles, t[gStockNameSprites[work->stockNames[work->stockNameIndex]].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(work->tiles, gStockNameSprites[work->stockNames[work->stockNameIndex]].sprites[gStockNameSprites[work->stockNames[work->stockNameIndex]].spriteIndex], gStockNameSprites[work->stockNames[work->stockNameIndex]].tiles);
#endif
    }

    return 1;
}

void StockNameRiku_2(StockNameWork* work) {
    if (gRikuBtlWork->hcEffect != 28 && work->visible) {
        DrawSprite(120, 14, NULL, work->tiles, work->palette, NULL, 0, 10);
    }
}

void StockNameRiku_3(StockNameWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    gCardBattleState->unk_0D9 = 0;
    work->visible = 0;
    gCardBattleState->unk_0CA = 256;
}

void StockNameSora_3(StockNameWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    gCardBattleState->unk_0D8 = 0;
    work->visible = 0;
    gCardBattleState->unk_0C8 = 256;
}

void Premire_Chance_0(PremireChanceWork* work) {
    u8 n = 0;
    u8 i;
    s32 j;
    u16* cards;

    CpuFill32(0, work, sizeof(PremireChanceWork));
    gCardListWork = EwramAlloc(sizeof(CardListWork));
    work->slots = EwramAlloc(sizeof(CardSlot) * 100);
    CpuFill32(0, gCardListWork, sizeof(CardListWork));
    CpuFill32(0, work->slots, sizeof(CardSlot) * 100);
    cards = GetActiveDeck()->cards;
    work->tiles2 = AllocObjTiles(0x120, NULL);
    work->palette2 = LoadObjPalette(gSmallHandCursorPalette, 32);
    SetObjTileSource(work->tiles2, gSmallHandCursorTiles);
    AnimInit(&work->anim, gSmallHandCursorAnims, gSmallHandCursorFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_FRENCH:
        work->tiles = LoadObjTiles(gPremireChanceTitleFrenchTiles, 0x340);
        break;
    case LANGUAGE_GERMAN:
        work->tiles = LoadObjTiles(gPremireChanceTitleGermanTiles, 0x3C0);
        break;
    case LANGUAGE_ITALIAN:
        work->tiles = LoadObjTiles(gPremireChanceTitleItalianTiles, 0x3C0);
        break;
    case LANGUAGE_SPANISH:
        work->tiles = LoadObjTiles(gPremireChanceTitleSpanishTiles, 0x300);
        break;
    case LANGUAGE_ENGLISH:
        work->tiles = LoadObjTiles(gPremireChanceTitleTiles, 0x3C0);
        break;
    default:
        work->tiles = LoadObjTiles(gPremireChanceTitleTiles, 0x3C0);
        break;
    }
#else
    work->tiles = LoadObjTiles(gPremireChanceTitleTiles, 0x3C0);
#endif
    work->palette = LoadObjPalette(gPremireChancePalette, 32);
    work->tiles5 = LoadObjTiles(gPremireChanceBarTiles, 0x3C0);
    work->tiles3 = AllocObjTiles(0x3C0, NULL);
    work->palette3 = LoadObjPalette(gCardSelectBoxPalette, 32);
    SetObjTileSource(work->tiles3, gCardSelectBoxTiles);
    AnimInit(&work->anim2, gCardSelectBoxAnims, gCardSelectBoxFrames);
    AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
    work->gfx2 = AnimGetGfx(&work->anim2);
    work->tiles4 = LoadObjTiles(gAButtonIconTiles, 0x80);
    work->palette4 = LoadObjPalette(gBStatesPalette, 32);
    FadeToAmount(FADE_MODE_BLACK, 16, 16);
    FadeSetPaletteExcluded(work->palette->index + 16, 1);
    FadeSetPaletteExcluded(work->palette3->index + 16, 1);
    FadeSetPaletteExcluded(work->palette2->index + 16, 1);
    FadeSetPaletteExcluded(work->palette4->index + 16, 1);

#ifdef VERSION_EU
    for (i = 0, n = 0; i < DECK_SIZE; i++) {
#else
    for (i = 0; i < DECK_SIZE; i++) {
#endif
        if (cards[i] != 0xFFFF) {
            if (!(gCardCollection[cards[i]] & 0x8000)) {
                if (gCardDefs[gCardCollection[cards[i]] & CARD_ID_MASK].category != 3) {
                    if (gCardDefs[gCardCollection[cards[i]] & CARD_ID_MASK].category != 2) {
                        work->slots[n].cardId = gCardCollection[cards[i]] & CARD_ID_MASK;
                        work->slots[n].index = i;
                        work->slots[n].unk_06 = n;
                        work->slots[n].stocked = 0;
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
                            work->slots[n].cardId = gCardCollection[cards[j]] & CARD_ID_MASK;
                            work->slots[n].index = j;
                            work->slots[n].unk_06 = n;
                            work->slots[n].stocked = 0;
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

    work->cardCount = n;
    TaskPoolInit(&work->tasks, work->cardCount + 1);
    ListPoolInit(&gCardListWork->cards);
    gCardListWork->selectedCard = NULL;
    gCardListWork->effectCount = 0;
    TaskPoolInit(&gCardListWork->effectTasks, 24);
    CreatePremireChanceCardTasks(work);
    work->spinDelay = 10;
    work->advanced = 0;
    work->stopped = 0;
    work->inputEnabled = 1;
    work->resultPending = 1;
    work->cursorHidden = 0;
    work->stopTimer = 0;
    work->titleSteps = 16;
    work->slideSteps = 16;
    work->titleX = -0x80;
    work->topY = -0x800;
    work->bottomY = 0xA000;
}

u8 UpdatePremireChanceSpin(PremireChanceWork* work, void* task) {
    PremireChanceCardWork* n;
    s32 t;
    s32 z;

    if (work->inputEnabled != 0) {
        if ((GetKeysPressed() & A_BUTTON) && !work->stopped) {
            work->stopped = 1;
            m4aSongNumStart(SONG_SYS_ITEMGET);
        }

        if ((GetKeysPressed() & B_BUTTON) && work->stopped != 1) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            work->titleSteps = 16;
            work->slideSteps = 16;
            SetTaskUpdate(task, (TaskUpdateFunc)UpdatePremireChanceClose);
            n = ListPoolFirst(&gCardListWork->cards);

            while (n != NULL) {
                n->state |= PREMIRE_CHANCE_CARD_STATE_HIDDEN;
                work->resultPending = 0;
                n = ListPoolNext(&n->node);
            }

            TaskPoolUpdate(&work->tasks);
            TaskPoolUpdate(&gCardListWork->effectTasks);
            z = 0;
            work->cursorHidden = 1;
            work->inputEnabled = z;
            return 1;
        }
    }

    n = ListPoolFirst(&gCardListWork->cards);

    if (!work->stopped) {
        while (n != NULL) {
            t = n->steps;

            if (t == 0) {
                m4aSongNumStart(SONG_SYS_CLICK);

                if (n->position < work->cardCount - 1) {
                    n->position++;
                } else {
                    n->position = t;
                }

                n->steps = work->spinDelay;
                work->advanced = 1;
            }

            n = ListPoolNext(&n->node);
        }
    } else {
        work->cursorHidden = 1;
        SetTaskUpdate(task, (TaskUpdateFunc)UpdatePremireChanceStop);
    }

    if (work->spinDelay == 4 || work->spinDelay == 10) {
        work->inputEnabled = 1;
    } else {
        work->inputEnabled = 0;
    }

    if (work->advanced) {
        if (work->spinDelay > 4) {
            work->spinDelay--;
        }

        work->advanced = 0;
    }

    work->gfx = AnimUpdate(&work->anim);
    work->gfx2 = AnimUpdate(&work->anim2);
    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&gCardListWork->effectTasks);
    return 1;
}

u8 Premire_Chance_1(PremireChanceWork* work, void* task) {
    s32 v;
    u8* p;
    PremireChanceCardWork* n;

    n = ListPoolFirst(&gCardListWork->cards);

    if (n != NULL && n->state == PREMIRE_CHANCE_CARD_STATE_SPIN) {
        SetTaskUpdate(task, (TaskUpdateFunc)UpdatePremireChanceSpin);
    }

    p = &work->slideSteps;

    if (*p != 0) {
        ApproachValue(&work->topY, 0, *p);
        ApproachValue(&work->bottomY, 0x9800, *p);
    } else {
        v = work->titleX << 8;
        p = &work->titleSteps;
        ApproachValue(&v, 0, *p);
        work->titleX = v >> 8;
    }

    (*p)--;
    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&gCardListWork->effectTasks);
    return 1;
}

void Premire_Chance_2(PremireChanceWork* work) {
    if (work->cursorHidden == 0) {
        DrawSprite(62, 50, work->gfx, work->tiles2, work->palette2, NULL, 0, 0);
        DrawSprite(53, 64, work->gfx2, work->tiles3, work->palette3, NULL, 0, 0);
    }

    if (work->inputEnabled != 0) {
        DrawSprite(88, 70, gAButtonIconFrames[0], work->tiles4, work->palette4, NULL, 0, 0);
    }

#ifdef VERSION_EU
    DrawSprite(work->titleX, 0, gPremireChanceTitles[gLanguage][0], work->tiles, work->palette, NULL, 0, 0);
#else
    DrawSprite(work->titleX, 0, gPremireChanceTitleFrames[0], work->tiles, work->palette, NULL, 0, 0);
#endif
    DrawSprite(120, work->topY >> 8, gPremireChanceBarFrames[0], work->tiles5, work->palette, NULL, 0, 60);
    DrawSprite(120, work->bottomY >> 8, gPremireChanceBarFrames[1], work->tiles5, work->palette, NULL, 0, 60);
    TaskPoolDraw(&work->tasks);
    TaskPoolDraw(&gCardListWork->effectTasks);
}

void Premire_Chance_3(PremireChanceWork* work) {
    TaskPoolDestroy(&gCardListWork->effectTasks);
    EwramFree(work->slots);
    EwramFree(gCardListWork);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles3);
    ReleaseObjTiles(work->tiles4);
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles5);
    FadeSetPaletteExcluded(work->palette->index + 16, 0);
    FadeSetPaletteExcluded(work->palette3->index + 16, 0);
    FadeSetPaletteExcluded(work->palette2->index + 16, 0);
    FadeSetPaletteExcluded(work->palette4->index + 16, 0);
    ReleaseObjPalette(work->palette2);
    ReleaseObjPalette(work->palette3);
    ReleaseObjPalette(work->palette4);
    ReleaseObjPalette(work->palette);
    SetJiminyFlag(0xF5);
    TaskPoolDestroy(&work->tasks);
}

void CreatePremireChanceCardTasks(PremireChanceWork* work) {
    u8 i;

    for (i = 0; i < work->cardCount; i++) {
        work->slots[i].unk_06 = i;
        TaskCreate(&work->tasks, &gTaskDescPremireChanceCard, &work->slots[i]);
    }
}

u8 UpdatePremireChanceStop(PremireChanceWork* work, void* task) {
    PremireChanceCardWork* n;
    TaskPool* pool;
    u8 z;
    u8 t;
    u8* q;

    n = ListPoolFirst(&gCardListWork->cards);
    work->gfx = AnimUpdate(&work->anim);
    work->gfx2 = AnimUpdate(&work->anim2);
    work->spinDelay = 0;
    work->stopTimer++;
    work->inputEnabled = 0;

    if (work->resultPending) {
        while (n != NULL) {
            if (n->steps == 0) {
                if (n->position == 3) {
                    n->state = PREMIRE_CHANCE_CARD_STATE_TO_CENTER;
                    ConvertActiveDeckCardToPremium(n->deckIndex);
                } else {
                    n->state = PREMIRE_CHANCE_CARD_STATE_MOVE_AWAY;
                }

                work->resultPending = 0;
            }

            n = ListPoolNext(&n->node);
        }
    }

    t = work->stopTimer;
    pool = &work->tasks;

    if (t == 30) {
        q = &work->cursorHidden;
        z = 0;
        *q = 1;
        SetBgPriority(2, 0);
        BgAnimInit(2, 0x8000, 0x80);
        BgAnimStart(&gBgAnimDefPremireChance, 120, 60);
        work->bgAnimDuration = BgAnimGetDuration(&gBgAnimDefPremireChance);
        work->resultTimer = z;
        gBldCnt = (BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_OBJ);
        gBldAlpha = BLDALPHA_BLEND(16, 16);
        BgAnimUpdate();
        FadeSetPaletteExcluded(10, 1);
        FadeSetPaletteExcluded(11, 1);
        FadeSetPaletteExcluded(12, 1);
        FadeSetPaletteExcluded(13, 1);
        FadeSetPaletteExcluded(14, 1);
        FadeSetPaletteExcluded(15, 1);
        TaskCreate(pool, &gTaskDescCardName, NULL);
        SetTaskUpdate(task, (TaskUpdateFunc)UpdatePremireChanceResult);
    }

    TaskPoolUpdate(pool);
    TaskPoolUpdate(&gCardListWork->effectTasks);
    return 1;
}

u8 UpdatePremireChanceResult(PremireChanceWork* work, void* task) {
    ListPoolFirst(&gCardListWork->cards);
    BgAnimUpdate();
    work->gfx = AnimUpdate(&work->anim);
    work->gfx2 = AnimUpdate(&work->anim2);
    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&gCardListWork->effectTasks);

    if ((GetKeysPressed() & A_BUTTON)
#ifdef VERSION_EU
        && work->resultTimer > 8
#endif
    ) {
        work->titleSteps = 16;
        work->slideSteps = 16;
        SetTaskUpdate(task, (TaskUpdateFunc)UpdatePremireChanceClose);
    }

#ifdef VERSION_EU
    if (work->resultTimer <= 254) {
        work->resultTimer++;
    }
#endif

    return 1;
}

u8 UpdatePremireChanceClose(PremireChanceWork* work, void* task) {
    s32 v;
    u8* p;

    p = &work->titleSteps;

    if (*p != 0) {
        v = work->titleX << 8;
        ApproachValue(&v, -0x8000, *p);
        work->titleX = v >> 8;
    } else {
        p = &work->slideSteps;

        if (*p == 0) {
            return 0;
        }

        ApproachValue(&work->topY, -0x800, *p);
        ApproachValue(&work->bottomY, 0xA000, *p);
    }

    (*p)--;
    TaskPoolUpdate(&work->tasks);
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
void** gPremireChanceTitles[5] = { gPremireChanceTitleFrames, gPremireChanceTitleFrenchFrames, gPremireChanceTitleGermanFrames, gPremireChanceTitleItalianFrames, gPremireChanceTitleSpanishFrames };
#endif

TaskDesc gTaskDescPremireChance = {
    "Premire Chance",
    (TaskInitFunc)Premire_Chance_0,
    (TaskUpdateFunc)Premire_Chance_1,
    (TaskDrawFunc)Premire_Chance_2,
    (TaskDestroyFunc)Premire_Chance_3,
    sizeof(PremireChanceWork),
};
