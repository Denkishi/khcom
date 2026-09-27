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
#include "sprites_card.h"
#include "sprites_premire_chance.h"
#include "sprites_card_pictures.h"
#include "gba/io_reg.h"
#include "card_ids.h"

struct CardListWork* gCardListWork EWRAM_COMMON(4);

#ifdef VERSION_EU
extern void** gUnkEu_09F72BFC[5];
#endif
extern u8 gUnk_09618CD8[];
extern u8 gUnk_0908BB80[];
extern u8 gUnk_09613E98[];
extern u8 gUnk_0908BFB2[];
extern u8 gUnk_09618D18[];
#ifdef VERSION_EU
extern u8 gUnkEu_0916292A[];
extern u8 gUnkEu_091633A4[];
extern u8 gUnkEu_09162FB8[];
extern u8 gUnkEu_09162C8C[];

#define LANGSTR(x) (((void**)(x))[gLanguage])
#else
#define LANGSTR(x) (x)
#endif
void CreateCardNameDisplay(void* a, void* b);
u8 func_0809BE80(UnkStruct_0809BB4C* w, void* a);
void func_0809C294(UnkStruct_0809BB4C* w);
void ConvertActiveDeckCardToPremium(u16 index);
s16 func_08084458(u16 cardId);
void ConvertActiveDeckCardToPremium(u16 index);
Deck* GetActiveDeck(void);
void CreateCardNameDisplay(void* a, void* b);

const u32 gUnk_09036210[8] = {
    CARD_ID(CARD_GOOFY, 0),
    CARD_ID(CARD_DONALD_DUCK, 0),
    CARD_ID(CARD_ALADDIN, 0),
    CARD_ID(CARD_ARIEL, 0),
    CARD_ID(CARD_JACK, 0),
    CARD_ID(CARD_PETER_PAN, 0),
    CARD_ID(CARD_THE_BEAST, 0),
    CARD_ID(CARD_THE_KING, 0),
};

void Friend_card_0(UnkStruct_0809A02C* w, s32* args) {
    Collider* p;

    w->cardId = args[3];
    w->unk_38 = args[0];
    w->unk_3C = args[1];
    w->unk_40 = args[2];
    w->unk_44 = 0;
    w->unk_1C6 = GetRandom();
    w->unk_1A4 = -(GetRandom() % 129 + 0x300);
    w->unk_1A8 = GetRandom() % 129 + 0x80;
    w->unk_1C7 = 0;
    w->unk_1C8 = 0;
    w->unk_1C9 = 24;
    w->scaleX = 0x80;
    w->scaleY = 0x80;
    w->unk_1BC = 0x80;
    w->unk_1CA = 0;
    w->unk_1CB = 0;
    w->unk_1CC = 0;
    w->unk_1C4 = 0;
    w->unk_1CD = 1;
    w->cardDef = &gCardDefs[args[3]];

    if (w->cardDef->flags & 8) {
        w->unk_1CE = 3;
    } else {
        w->unk_1CE = w->cardDef->unk_2A;
    }

    w->palette = LoadObjPalette(gCard00Palette, 32);
    w->tiles3 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    w->tiles2 = LoadObjTiles(w->cardDef->tiles, 0x300);
    w->palette2 = LoadObjPalette(w->cardDef->palette, 32);
    w->tiles4 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    w->palette3 = LoadObjPalette(gBStatesPalette, 32);
    p = &w->collider;
    ColliderInit(p, 5, 8, 10);
    ColliderSetPosition(p, w->unk_38, w->unk_3C, w->unk_40);
    TaskPoolInit(&w->tasks, 1);
    gBtlWork->unk_0B0++;
}

void Heartless_card_0(UnkStruct_0809A02C* w, s32* args) {
    Collider* p;

    w->cardId = args[3];
    w->unk_38 = args[0];
    w->unk_3C = args[1];
    w->unk_40 = args[2];
    w->unk_44 = 0;
    w->unk_1C6 = GetRandom();
    w->unk_1A4 = -(GetRandom() % 129 + 0x300);
    w->unk_1A8 = GetRandom() % 129 + 0x80;
    w->unk_1C7 = 0;
    w->unk_1C8 = 0;
    w->unk_1C9 = 24;
    w->scaleX = 0x80;
    w->scaleY = 0x80;
    w->unk_1BC = 0x80;
    w->unk_1CA = 0;
    w->unk_1CB = 0;
    w->unk_1CC = 0;
    w->unk_1C4 = 0;
    w->unk_1CD = 1;
    w->cardDef = &gCardDefs[args[3]];

    if (w->cardDef->flags & 8) {
        w->unk_1CE = 3;
    } else {
        w->unk_1CE = w->cardDef->unk_2A;
    }

    w->tiles = LoadObjTiles(gUnk_08F709B0[w->unk_1CE].tiles, 0x280);
    w->palette = LoadObjPalette(gCard00Palette, 32);
    w->tiles3 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    w->tiles2 = LoadObjTiles(w->cardDef->tiles, 0x300);
    w->palette2 = LoadObjPalette(w->cardDef->palette, 32);
    w->tiles4 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    w->palette3 = LoadObjPalette(gBStatesPalette, 32);
    p = &w->collider;
    ColliderInit(p, 5, 8, 10);
    ColliderSetPosition(p, w->unk_38, w->unk_3C, w->unk_40);
    TaskPoolInit(&w->tasks, 1);
    gBtlWork->unk_0B0++;
}

void Gimmick_card_0(UnkStruct_0809A02C* w, GimmickCardArgs* args) {
    Collider* p;

    w->cardId = args->cardId;
    w->unk_38 = args->unk_00;
    w->unk_3C = args->unk_04;
    w->unk_40 = args->unk_08;
    w->unk_44 = 0;
    w->unk_1C6 = GetRandom();
    w->unk_1A4 = -((u16)(GetRandom() % 129) + 0x300);
    w->unk_1A8 = (u16)(GetRandom() % 129) + 0x80;
    w->unk_1C7 = 0;
    w->unk_1C8 = 0;
    w->unk_1C9 = 24;
    w->scaleX = 0x80;
    w->scaleY = 0x80;
    w->unk_1BC = 0x80;
    w->unk_1CA = 0;
    w->unk_1CB = 0;
    w->unk_1CC = 0;
    w->unk_1C4 = 0;
    w->unk_1CD = 1;
    w->cardDef = &gCardDefs[args->cardId];
    w->unk_1CE = w->cardDef->unk_2A;
    w->palette = LoadObjPalette(gCard00Palette, 32);
    w->tiles3 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    w->tiles2 = LoadObjTiles(w->cardDef->tiles, 0x300);
    w->palette2 = LoadObjPalette(w->cardDef->palette, 32);
    w->tiles4 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    w->palette3 = LoadObjPalette(gBStatesPalette, 32);
    p = &w->collider;
    ColliderInit(p, 5, 8, 10);
    ColliderSetPosition(p, w->unk_38, w->unk_3C, w->unk_40);
    TaskPoolInit(&w->tasks, 1);
    gBtlWork->unk_0B0++;
}

void func_0809A4E0(UnkStruct_0809A02C* w, u8 kind) {
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

    dx = tx - w->unk_38;
    dy = ty - w->unk_3C;
    w->unk_1AC = NormalizeVector2D8(&dx, &dy);
    w->unk_1B0 = -dx;
    w->unk_1B4 = -dy;
    w->unk_1A8 = 0x300;
    w->unk_1A4 = 2;
}

s32 Friend_card_1(UnkStruct_0809A02C* w, void* a) {
    s16 sx;
    s32 t;
    u16 n;
    s16 sy;

    if (gBtlWork->unk_0A0 == 4) {
        return 0;
    }

    w->unk_1A4 += gBtlWork->unk_12C;
    w->unk_40 += w->unk_1A4;
    w->unk_38 += (gSineTable[w->unk_1C6] * w->unk_1A8) >> 8;
    w->unk_3C += (-gSineTable[w->unk_1C6 + 64] * w->unk_1A8) >> 8;

    if (ClampBattlePosition(&w->unk_38, &w->unk_3C, -10, -10) != 0) {
        w->unk_1C6 = (u8)(w->unk_1C6 + 112) + GetRandom() % 33;
    }

    if (w->unk_40 - 0x800 > w->unk_44) {
        w->unk_40 = w->unk_44 - 0x800;
        w->unk_1A4 = -((204 * w->unk_1A4) >> 8);
        w->unk_1C6 = GetAngle(w->unk_38, w->unk_3C,
                               gBtlWork->actor->x,
                               gBtlWork->actor->y);
        w->unk_1C6 = (u8)(w->unk_1C6 + 224) + GetRandom() % 65;

        if (w->unk_1A4 > -0x200) {
            w->unk_1A4 = -0x200;
        }
    }

    if (gBtlWork->unk_0F4 == 6) {
        ColliderSetRadius(&w->collider, 50);
    } else {
        ColliderSetRadius(&w->collider, 10);
    }

    if ((u8)func_0801C6D4(&w->unk_38, &w->unk_3C, &w->unk_40,
                          &w->unk_44) != 0) {
        w->unk_1C6 = (u8)(w->unk_1C6 + 112) + GetRandom() % 33;
    }

    if (w->collider.unk_2C != 0) {
        m4aSongNumStart(SONG_SYS_ITEMGET);
#ifdef VERSION_EU
        w->unk_1C2 = 10;
#endif

        if (gUnk_02039DD4 != 0) {
            WorldToScreen(&sx, &sy, w->unk_38, w->unk_3C,
                          w->unk_40);
            w->unk_38 = sx << 8;
            w->unk_3C = sy << 8;
            w->unk_1CA = 1;
            ColliderSetDisabled(&w->collider, 1);
            func_0809A4E0(w, 0);
#ifdef VERSION_EU
            w->unk_1CD = 1;
#endif
            SetTaskUpdate(a, (TaskUpdateFunc)func_0809AB2C);
        }

        return 1;
    }

    ColliderSetPosition(&w->collider, w->unk_38, w->unk_3C,
                  w->unk_40);
    w->scaleX =
        (-gSineTable[((w->unk_1C7 + 128) & 0xFF) + 64] *
         w->unk_1BC) >> 8;
    w->scaleY =
        (-gSineTable[((w->unk_1C8 + 128) & 0xFF) + 64] *
         w->unk_1BC) >> 8;

    if ((u16)(w->scaleX + 2) <= 4) {
        w->scaleX = 2;
    }

    if ((u16)(w->scaleY + 2) <= 4) {
        w->scaleY = 2;
    }

    w->unk_1C7 += 2;
    w->unk_1C2 = -0x1004 - (w->unk_3C >> 8) * 4;
    TaskPoolUpdate(&w->tasks);

    if (gBtlWork->flags & 0x800000000) {
        return 1;
    }

    n = w->unk_1C4;

    if (n > 359) {
        return 0;
    }

    t = n + 1;
    w->unk_1C4 = t;

    if (w->unk_1C4 > 279 && t % 4 == 0) {
        w->unk_1CD ^= 1;
    }

    return 1;
}
s32 Gimmick_card_1(UnkStruct_0809A02C* w, void* a) {
    s16 sx;
    s32 t;
    u16 n;
    s16 sy;

    if (gBtlWork->unk_0A0 == 4) {
        return 0;
    }

    w->unk_1A4 += 56;
    w->unk_40 += w->unk_1A4;
    w->unk_38 += (gSineTable[w->unk_1C6] * w->unk_1A8) >> 8;
    w->unk_3C += (-gSineTable[w->unk_1C6 + 64] * w->unk_1A8) >> 8;

    if (ClampBattlePosition(&w->unk_38, &w->unk_3C, -10, -10) != 0) {
        w->unk_1C6 = (u8)(w->unk_1C6 + 112) + GetRandom() % 33;
    }

    if (w->unk_40 - 0x800 > w->unk_44) {
        w->unk_40 = w->unk_44 - 0x800;
        w->unk_1A4 = -((204 * w->unk_1A4) >> 8);
        w->unk_1C6 = GetAngle(w->unk_38, w->unk_3C,
                               gBtlWork->actor->x,
                               gBtlWork->actor->y);
        w->unk_1C6 = (u8)(w->unk_1C6 + 224) + GetRandom() % 65;

        if (w->unk_1A4 > -0x200) {
            w->unk_1A4 = -0x200;
        }
    }

    if (gBtlWork->unk_0F4 == 6) {
        ColliderSetRadius(&w->collider, 50);
    } else {
        ColliderSetRadius(&w->collider, 10);
    }

    if ((u8)func_0801C6D4(&w->unk_38, &w->unk_3C, &w->unk_40,
                          &w->unk_44) != 0) {
        w->unk_1C6 = (u8)(w->unk_1C6 + 112) + GetRandom() % 33;
    }

    if (w->collider.unk_2C != 0) {
        m4aSongNumStart(SONG_SYS_ITEMGET);
#ifdef VERSION_EU
        w->unk_1C2 = 10;
#endif

        if (gUnk_02039DD4 != 0) {
            WorldToScreen(&sx, &sy, w->unk_38, w->unk_3C,
                          w->unk_40);
            w->unk_38 = sx << 8;
            w->unk_3C = sy << 8;
            w->unk_1CA = 1;
            ColliderSetDisabled(&w->collider, 1);
            func_0809A4E0(w, 0);
#ifdef VERSION_EU
            w->unk_1CD = 1;
#endif
            SetTaskUpdate(a, (TaskUpdateFunc)func_0809AB2C);
        }

        return 1;
    }

    ColliderSetPosition(&w->collider, w->unk_38, w->unk_3C,
                  w->unk_40);
    w->scaleX =
        (-gSineTable[((w->unk_1C7 + 128) & 0xFF) + 64] *
         w->unk_1BC) >> 8;
    w->scaleY =
        (-gSineTable[((w->unk_1C8 + 128) & 0xFF) + 64] *
         w->unk_1BC) >> 8;

    if ((u16)(w->scaleX + 2) <= 4) {
        w->scaleX = 2;
    }

    if ((u16)(w->scaleY + 2) <= 4) {
        w->scaleY = 2;
    }

    w->unk_1C7 += 2;
    w->unk_1C2 = -0x1004 - (w->unk_3C >> 8) * 4;
    TaskPoolUpdate(&w->tasks);

    n = w->unk_1C4;

    if (n > 359) {
        *(u8*)&gUnk_02039DD4->unk_0DC -= 1;
        return 0;
    }

    t = n + 1;
    w->unk_1C4 = t;

    if (w->unk_1C4 > 279 && t % 4 == 0) {
        w->unk_1CD ^= 1;
    }

    return 1;
}
u8 func_0809AB2C(UnkStruct_0809A02C* w) {
    s32 dx;
    s32 dy;
    u16 t;

    if (gBtlWork->unk_0A0 == 4) {
        return 0;
    }

    if (w->unk_1A8 < 0) {
        dx = -w->unk_38;
        dy = 0xA000 - w->unk_3C;
        NormalizeVector2D8(&dx, &dy);
        w->unk_1B0 = -dx;
        w->unk_1B4 = -dy;

        if (w->unk_1AC < 0x800) {
            if (w->cardId >= 655 && w->cardId <= 659) {
                gUnk_02039DD4->unk_0BC = w->cardId;
            } else {
                gUnk_02039DD4->unk_0B8 = w->cardId;
            }

            return 0;
        }
    }

    w->unk_38 += (w->unk_1B0 * w->unk_1A8) >> 8;
    w->unk_3C += (w->unk_1B4 * w->unk_1A8) >> 8;
    w->unk_1C9 += 32;
    w->unk_1C8 += (64 - w->unk_1C8) >> 4;
    w->unk_1C7 = 0;
    w->unk_1AC = VectorLength2D(-w->unk_38, 0xA000 - w->unk_3C);
    w->unk_1A8 -= w->unk_1A4;
    w->unk_1A4 += 2;
    t = w->unk_1BC;

    if ((s16)t <= 255) {
        w->unk_1BC = t + 3;
    }

    w->scaleX = (-gSineTable[((w->unk_1C7 + 128) & 0xFF) + 64] * w->unk_1BC) >> 8;
    w->scaleY = (-gSineTable[((w->unk_1C8 + 128) & 0xFF) + 64] * w->unk_1BC) >> 8;

    if ((u16)(w->scaleX + 2) <= 4) {
        w->scaleX = 2;
    }

    if ((u16)(w->scaleY + 2) <= 4) {
        w->scaleY = 2;
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 func_0809ACDC(UnkStruct_0809A02C* w) {
    s16 x;
    s16 y;

    w->unk_1C9 += 32;
    WorldToScreen(&x, &y, gBtlWork->actor->x, gBtlWork->actor->y, gBtlWork->actor->z);
    w->unk_38 += ((x << 8) - w->unk_38) >> 3;
    w->unk_3C += ((y << 8) - w->unk_3C) >> 3;
    w->scaleX -= 10;
    w->scaleY -= 10;

    if (w->scaleX <= 10) {
        return 0;
    }

    return 1;
}

s32 func_0809AD60(UnkStruct_0809A02C* w, void* a) {
    w->unk_1C4 += 1;

    if (w->unk_1C4 == 60) {
        SetTaskUpdate(a, (TaskUpdateFunc)func_0809ACDC);
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}
s32 func_0809AD98(UnkStruct_0809A02C* w, void* a) {
    s32 dx = 0;
    s32 dy = 0;
    s32 v;
    u16 t;

    if (w->unk_1A8 < 0) {
        dx = 0x7800 - w->unk_38;
        dy = 0x5000 - w->unk_3C;
        NormalizeVector2D8(&dx, &dy);
        w->unk_1B0 = -dx;
        w->unk_1B4 = -dy;

        if (w->unk_1AC < 0x800) {
            w->unk_1C8 = 0;
            w->unk_1C9 = 0;
            w->unk_1C7 = 0;
            w->unk_38 = 0x7800;
            w->unk_3C = 0x5000;
            *(u16*)&w->scaleX = v = 0x100;
            *(u16*)&w->scaleY = v;
#ifdef VERSION_EU
            CreateCardNameDisplay(&w->tasks, eu_0805E924(gCardDefs[w->cardId].name));
#else
            CreateCardNameDisplay(&w->tasks, gCardDefs[w->cardId].name);
#endif
            SetTaskUpdate(a, (TaskUpdateFunc)func_0809AD60);
            w->unk_1C4 = 0;
            w->unk_1C2 = 50;
            return 1;
        }
    }

    w->unk_38 += (w->unk_1B0 * w->unk_1A8) >> 8;
    w->unk_3C += (w->unk_1B4 * w->unk_1A8) >> 8;
    w->unk_1C9 += 32;
    w->unk_1C8 += (64 - w->unk_1C8) >> 4;
    w->unk_1C7 = 0;
    w->unk_1AC = VectorLength2D(0x7800 - w->unk_38, 0x5000 - w->unk_3C);
    w->unk_1A8 -= w->unk_1A4;
    w->unk_1A4 += 2;
    t = w->unk_1BC;

    if ((s16)t <= 255) {
        w->unk_1BC = t + 3;
    }

    w->scaleX = (-gSineTable[((w->unk_1C7 + 128) & 0xFF) + 64] * w->unk_1BC) >> 8;
    w->scaleY = (-gSineTable[((w->unk_1C8 + 128) & 0xFF) + 64] * w->unk_1BC) >> 8;

    if ((u16)(w->scaleX + 2) <= 4) {
        w->scaleX = 2;
    }

    if ((u16)(w->scaleY + 2) <= 4) {
        w->scaleY = 2;
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}
s32 Heartless_card_1(UnkStruct_0809A02C* w, void* a) {
    s16 x;
    s16 y;

    w->unk_1A4 += 0x38;
    w->unk_40 += w->unk_1A4;
    w->unk_38 += (gSineTable[w->unk_1C6] * w->unk_1A8) >> 8;
    w->unk_3C += (-gSineTable[w->unk_1C6 + 64] * w->unk_1A8) >> 8;

    if (ClampBattlePosition(&w->unk_38, &w->unk_3C, -10, -10) != 0) {
        w->unk_1C6 = (u8)(w->unk_1C6 + 0x70) + GetRandom() % 33;
    }

    if (w->unk_40 - 0x800 > w->unk_44) {
        w->unk_40 = w->unk_44 - 0x800;
        w->unk_1A4 = -((w->unk_1A4 * 204) >> 8);
        w->unk_1C6 = GetAngle(w->unk_38, w->unk_3C, gBtlWork->actor->x, gBtlWork->actor->y);
        w->unk_1C6 = (u8)(w->unk_1C6 + 0xE0) + GetRandom() % 65;

        if (w->unk_1A4 > -0x200) {
            w->unk_1A4 = -0x200;
        }
    }

    if (gBtlWork->unk_0F4 == 6) {
        ColliderSetRadius(&w->collider, 50);
    } else {
        ColliderSetRadius(&w->collider, 10);
    }

    if (func_0801C6D4(&w->unk_38, &w->unk_3C, &w->unk_40, &w->unk_44)) {
        w->unk_1C6 = (u8)(w->unk_1C6 + 0x70) + GetRandom() % 33;
    }

    if (w->collider.unk_2C != 0) {
        m4aSongNumStart(SONG_SYS_ITEMGET);
#ifdef VERSION_EU
        w->unk_1C2 = 10;
#endif
        func_08084458(w->cardId);
        WorldToScreen(&x, &y, w->unk_38, w->unk_3C, w->unk_40);
        w->unk_38 = x << 8;
        w->unk_3C = y << 8;
        w->unk_1CA = 1;
        ColliderSetDisabled(&w->collider, 1);
        func_0809A4E0(w, 1);
        SetTaskUpdate(a, (TaskUpdateFunc)func_0809AD98);
        return 1;
    }

    ColliderSetPosition(&w->collider, w->unk_38, w->unk_3C, w->unk_40);
    w->scaleX = (-gSineTable[((w->unk_1C7 + 128) & 0xFF) + 64] * w->unk_1BC) >> 8;
    w->scaleY = (-gSineTable[((w->unk_1C8 + 128) & 0xFF) + 64] * w->unk_1BC) >> 8;

    if ((u16)(w->scaleX + 2) <= 4) {
        w->scaleX = 2;
    }

    if ((u16)(w->scaleY + 2) <= 4) {
        w->scaleY = 2;
    }

    w->unk_1C7 += 2;
    w->unk_1C2 = -0x1004 - ((w->unk_3C >> 8) << 2);
    TaskPoolUpdate(&w->tasks);
    return 1;
}
void func_0809B200(UnkStruct_0809A02C* w) {
    s16 x;
    s16 y;
    s32 affine;
    s16 v;
    u8 kind;

    if (w->unk_1CD != 0) {
        if (w->unk_1CA == 0) {
            w->unk_1D0 = GetBattleSpritePriorityFlags(w->unk_3C);
            WorldToScreen(&x, &y, w->unk_38, w->unk_3C,
                          w->unk_40);
        } else {
            w->unk_1D0 = 0;
            x = w->unk_38 >> 8;
            y = w->unk_3C >> 8;
        }

        affine = AllocObjAffine(w->unk_1C9, w->scaleX,
                                w->scaleY, 0);
        DrawSprite(x, (u16)y - 8,
                   gUnk_08F709B0[w->cardDef->unk_2A].gfx,
                   gUnk_02039DD4->tiles[w->cardDef->unk_2A],
                   w->palette, affine,
                   w->unk_1D0, w->unk_1C2);
        DrawSprite(x, (u16)y - 8, w->cardDef->gfx,
                   w->tiles2, w->palette2, affine,
                   w->unk_1D0, (u16)(w->unk_1C2 + 1));
        kind = w->cardDef->unk_20;
        DrawSprite(x, (u16)y - 8, gUnk_09EE981C[kind],
                   w->tiles3, w->palette, affine,
                   w->unk_1D0, (u16)(w->unk_1C2 - 2));
        v = 204 - ((w->unk_44 - w->unk_40) >> 7);

        if (v <= 2) {
            v = 2;
        }

        if (w->unk_1CA == 0) {
            WorldToScreen(&w->x, &w->y,
                          w->unk_38, w->unk_3C,
                          w->unk_44);
            DrawSprite(w->x, w->y,
                       gUnk_09EE1380[0], w->tiles4,
                       w->palette3, AllocObjAffine(0, v, v, 0),
                       w->unk_1D0, (u16)(w->unk_1C2 + 2));
        }

        TaskPoolDraw(&w->tasks);
    }
}
void Heartless_card_2(UnkStruct_0809A02C* w) {
    s16 x;
    s16 y;
    s32 affine;
    s16 v;

    if (w->unk_1CD != 0) {
        if (w->unk_1CA == 0) {
            w->unk_1D0 = GetBattleSpritePriorityFlags(w->unk_3C);
            WorldToScreen(&x, &y, w->unk_38, w->unk_3C,
                          w->unk_40);
        } else {
            w->unk_1D0 = 0;
            x = w->unk_38 >> 8;
            y = w->unk_3C >> 8;
        }

        affine = AllocObjAffine(w->unk_1C9, w->scaleX,
                                w->scaleY, 0);
        DrawSprite(x, (u16)y - 8,
                   gUnk_08F709B0[w->cardDef->unk_2A].gfx,
                   w->tiles, w->palette, affine,
                   w->unk_1D0, w->unk_1C2);
        DrawSprite(x, (u16)y - 8, w->cardDef->gfx,
                   w->tiles2, w->palette2, affine,
                   w->unk_1D0, (u16)(w->unk_1C2 + 1));
        v = 204 - ((w->unk_44 - w->unk_40) >> 7);

        if (v <= 2) {
            v = 2;
        }

        if (w->unk_1CA == 0) {
            WorldToScreen(&w->x, &w->y,
                          w->unk_38, w->unk_3C,
                          w->unk_44);
            DrawSprite(w->x, w->y,
                       gUnk_09EE1380[0], w->tiles4,
                       w->palette3, AllocObjAffine(0, v, v, 0),
                       w->unk_1D0, (u16)(w->unk_1C2 + 2));
        }

        TaskPoolDraw(&w->tasks);
    }
}

void func_0809B59C(UnkStruct_0809A02C* w) {
    ReleaseObjPalette(w->palette);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjPalette(w->palette2);
    ReleaseObjTiles(w->tiles4);
    ReleaseObjPalette(w->palette3);
    ColliderUnregister(&w->collider);
    TaskPoolDestroy(&w->tasks);
    gUnk_02039DD4->unk_0D6 = 0;
    gBtlWork->unk_0B0--;
}

void Heartless_card_3(UnkStruct_0809A02C* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjPalette(w->palette2);
    ReleaseObjTiles(w->tiles4);
    ReleaseObjPalette(w->palette3);
    ColliderUnregister(&w->collider);
    TaskPoolDestroy(&w->tasks);
    gBtlWork->unk_0B0--;
}

void func_0809B644(void* pool, s16 x, s16 y, s16 z, u8 idx) {
    s32 args[4];

    if (gUnk_02039DD4 != 0) {
        if (gUnk_02039DD4->unk_0DA[0] <= 4) {
            if (gUnk_02039DD4->unk_0D6 == 0) {
                args[0] = (s16)x << 8;
                args[1] = (s16)y << 8;
                args[2] = (s16)z << 8;
                args[3] = gUnk_09036210[idx] + GetRandom() % 9;
                TaskCreate(pool, &gTaskDescFriendCard, args);
                gUnk_02039DD4->unk_0D6++;
            }
        }
    }
}

void CreateHeartlessCardTask(void* pool, s16 a, s16 b, s16 c, u16 d) {
    s32 args[4];
    const s32* t;

    t = gUnk_09EE275C[d];
    args[0] = a << 8;
    args[1] = b << 8;
    args[2] = c << 8;
    args[3] = t[0];
    TaskCreate(pool, &gTaskDescHeartlessCard, args);
}

void CreateGimmickCardTask(void* pool, s16 a, s16 b, s16 c, u16 d) {
    s32 args[4];

    if (gUnk_02039DD4 != 0 && gUnk_02039DD4->unk_0DC == 0) {
        gUnk_02039DD4->unk_0DC++;
        args[0] = (s16)a << 8;
        args[1] = (s16)b << 8;
        args[2] = (s16)c << 8;
        args[3] = d;
        TaskCreate(pool, &gTaskDescGimmickCard, args);
    }
}

void func_0809B76C(StockNameWork* w, const s32* src) {
    u8 i;
    s32* dst;
    s32* q;
    const s32* s;
    s32 z;
    ObjTiles* obj;

    if (src != 0) {
        s = src;

        for (i = 0; i < 6; i++) {
            dst = w->unk_18;
            q = &dst[i];
            *q = s[i];
        }

        w->unk_30 = 1;
    } else {
        w->unk_30 = 0;
    }

    z = 0;
    w->unk_11 = z;
    w->unk_04 = z;
    obj = AllocSpriteFrameTiles(0x3C0);
    w->tiles = obj;

    if (w->unk_30 == 0) {
#ifdef VERSION_EU
        void** t;
        void* u;

        t = (void**)LANGSTR(gUnk_08F7CF18[gUnk_02039DD4->unk_0C4].sprites);
        u = LANGSTR(gUnk_08F7CF18[gUnk_02039DD4->unk_0C4].tiles);
        UpdateSpriteFrameTiles(obj, t[gUnk_08F7CF18[gUnk_02039DD4->unk_0C4].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(obj, gUnk_08F7CF18[gUnk_02039DD4->unk_0C4].sprites[gUnk_08F7CF18[gUnk_02039DD4->unk_0C4].spriteIndex], gUnk_08F7CF18[gUnk_02039DD4->unk_0C4].tiles);
#endif
    } else {
#ifdef VERSION_EU
        void** t;
        void* u;

        t = (void**)LANGSTR(gUnk_08F7CF18[w->unk_18[0]].sprites);
        u = LANGSTR(gUnk_08F7CF18[w->unk_18[0]].tiles);
        UpdateSpriteFrameTiles(obj, t[gUnk_08F7CF18[w->unk_18[0]].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(obj, gUnk_08F7CF18[w->unk_18[0]].sprites[gUnk_08F7CF18[w->unk_18[0]].spriteIndex], gUnk_08F7CF18[w->unk_18[0]].tiles);
#endif
    }

    w->palette = LoadObjPalette(gBStatesPalette, 32);
    w->unk_31 = 1;
    w->unk_14 = gUnk_02039DD4->unk_0C4;
}

u8 func_0809B840(StockNameWork* w) {
#ifdef VERSION_EU
    void** t = (void**)LANGSTR(gUnk_08F7CF18[w->unk_18[w->unk_11]].sprites);
    void* u = LANGSTR(gUnk_08F7CF18[w->unk_18[w->unk_11]].tiles);
#endif

    if (gUnk_02039DD4->unk_0E3 == 0 || gUnk_02039DD4->unk_0C4 != w->unk_14) {
        return 0;
    }

    if ((gFrameCounter >> 5) & 1) {
        w->unk_31 = 1;
    } else {
        w->unk_31 = 0;
    }

    if (w->unk_30 == 1 && w->unk_31 != 0) {
        w->unk_11++;

        if (w->unk_18[w->unk_11] == -1) {
            w->unk_11 = 0;
        }

#ifdef VERSION_EU
        UpdateSpriteFrameTiles(w->tiles, t[gUnk_08F7CF18[w->unk_18[w->unk_11]].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(w->tiles, gUnk_08F7CF18[w->unk_18[w->unk_11]].sprites[gUnk_08F7CF18[w->unk_18[w->unk_11]].spriteIndex], gUnk_08F7CF18[w->unk_18[w->unk_11]].tiles);
#endif
    }

    return 1;
}

void func_0809B8F0(StockNameWork* w) {
    if (w->unk_31 != 0) {
        DrawSprite(64, 14, 0, w->tiles, w->palette, 0,
#ifdef VERSION_EU
                   0x410,
#else
                   0,
#endif
                   10);
    }
}
void func_0809B920(StockNameWork* w, const s32* src) {
    u8 i;
    s32* dst;
    s32* q;
    const s32* s;
    s32 z;
    ObjTiles* obj;

    if (src != 0) {
        s = src;

        for (i = 0; i < 6; i++) {
            dst = w->unk_18;
            q = &dst[i];
            *q = s[i];
        }

        w->unk_30 = 1;
    } else {
        w->unk_30 = 0;
    }

    z = 0;
    w->unk_11 = z;
    w->unk_04 = z;
    obj = AllocSpriteFrameTiles(0x3C0);
    w->tiles = obj;

    if (w->unk_30 == 0) {
#ifdef VERSION_EU
        void** t;
        void* u;

        t = (void**)LANGSTR(gUnk_08F7CF18[gUnk_02039DD4->unk_0C6].sprites);
        u = LANGSTR(gUnk_08F7CF18[gUnk_02039DD4->unk_0C6].tiles);
        UpdateSpriteFrameTiles(obj, t[gUnk_08F7CF18[gUnk_02039DD4->unk_0C6].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(obj, gUnk_08F7CF18[gUnk_02039DD4->unk_0C6].sprites[gUnk_08F7CF18[gUnk_02039DD4->unk_0C6].spriteIndex], gUnk_08F7CF18[gUnk_02039DD4->unk_0C6].tiles);
#endif
    } else {
#ifdef VERSION_EU
        void** t;
        void* u;

        t = (void**)LANGSTR(gUnk_08F7CF18[w->unk_18[0]].sprites);
        u = LANGSTR(gUnk_08F7CF18[w->unk_18[0]].tiles);
        UpdateSpriteFrameTiles(obj, t[gUnk_08F7CF18[w->unk_18[0]].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(obj, gUnk_08F7CF18[w->unk_18[0]].sprites[gUnk_08F7CF18[w->unk_18[0]].spriteIndex], gUnk_08F7CF18[w->unk_18[0]].tiles);
#endif
    }

    w->palette = LoadObjPalette(gBStatesPalette, 32);
    w->unk_31 = 1;
    w->unk_14 = gUnk_02039DD4->unk_0C6;
}

u8 func_0809B9F4(StockNameWork* w) {
#ifdef VERSION_EU
    void** t = (void**)LANGSTR(gUnk_08F7CF18[w->unk_18[w->unk_11]].sprites);
    void* u = LANGSTR(gUnk_08F7CF18[w->unk_18[w->unk_11]].tiles);
#endif

    if (gUnk_02039DD4->unk_0E4 == 0 || gUnk_02039DD4->unk_0C6 != w->unk_14) {
        return 0;
    }

    if ((gFrameCounter >> 5) & 1) {
        w->unk_31 = 0;
    } else {
        w->unk_31 = 1;
    }

    if (w->unk_30 == 1 && w->unk_31 != 0) {
        w->unk_11++;

        if (w->unk_18[w->unk_11] == -1) {
            w->unk_11 = 0;
        }

#ifdef VERSION_EU
        UpdateSpriteFrameTiles(w->tiles, t[gUnk_08F7CF18[w->unk_18[w->unk_11]].spriteIndex], u);
#else
        UpdateSpriteFrameTiles(w->tiles, gUnk_08F7CF18[w->unk_18[w->unk_11]].sprites[gUnk_08F7CF18[w->unk_18[w->unk_11]].spriteIndex], gUnk_08F7CF18[w->unk_18[w->unk_11]].tiles);
#endif
    }

    return 1;
}

void func_0809BAA4(StockNameWork* w) {
    if (gUnk_02039B9C->unk_0F4 != 28 && w->unk_31 != 0) {
        DrawSprite(120, 14, 0, w->tiles, w->palette, 0, 0, 10);
    }
}
void func_0809BAE4(StockNameWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    gUnk_02039DD4->unk_0D9 = 0;
    w->unk_31 = 0;
    gUnk_02039DD4->unk_0CA = 256;
}
void func_0809BB18(StockNameWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    gUnk_02039DD4->unk_0D8 = 0;
    w->unk_31 = 0;
    gUnk_02039DD4->unk_0C8 = 256;
}

void func_0809BB4C(UnkStruct_0809BB4C* w) {
    u8 n = 0;
    u8 i;
    s32 j;
    u16* cards;
    u32 zero0 = 0;
    u32 zero1;
    u32 zero2;

    CpuSet(&zero0, w, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(UnkStruct_0809BB4C) / 4);
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
    AnimStart(&w->anim, 0, 1);
    w->gfx = AnimGetGfx(&w->anim);
#ifdef VERSION_EU
    switch (gLanguage) {
    case 1:
        w->tiles = LoadObjTiles(gUnkEu_0916292A, 0x340);
        break;
    case 2:
        w->tiles = LoadObjTiles(gUnkEu_091633A4, 0x3C0);
        break;
    case 3:
        w->tiles = LoadObjTiles(gUnkEu_09162FB8, 0x3C0);
        break;
    case 4:
        w->tiles = LoadObjTiles(gUnkEu_09162C8C, 0x300);
        break;
    case 0:
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
    AnimStart(&w->anim2, 0, 1);
    w->gfx2 = AnimGetGfx(&w->anim2);
    w->tiles4 = LoadObjTiles(gUnk_0905F03C, 0x80);
    w->palette4 = LoadObjPalette(gBStatesPalette, 32);
    FadeToAmount(0, 16, 16);
    FadeSetPaletteExcluded((u16)(w->palette->index + 16), 1);
    FadeSetPaletteExcluded((u16)(w->palette3->index + 16), 1);
    FadeSetPaletteExcluded((u16)(w->palette2->index + 16), 1);
    FadeSetPaletteExcluded((u16)(w->palette4->index + 16), 1);

#ifdef VERSION_EU
    for (i = 0, n = 0; i < DECK_SIZE; i++) {
#else
    for (i = 0; i < DECK_SIZE; i++) {
#endif
        if (cards[i] != 0xFFFF) {
            if (!(gCardCollection[cards[i]] & 0x8000)) {
                if (gCardDefs[gCardCollection[cards[i]] & CARD_ID_MASK].unk_2A != 3) {
                    if (gCardDefs[gCardCollection[cards[i]] & CARD_ID_MASK].unk_2A != 2) {
                        w->slots[n].cardId = gCardCollection[cards[i]] & CARD_ID_MASK;
                        w->slots[n].unk_04 = i;
                        w->slots[n].unk_06 = n;
                        w->slots[n].unk_07 = 0;
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
                    if (gCardDefs[gCardCollection[cards[j]] & CARD_ID_MASK].unk_2A != 3) {
                        if (gCardDefs[gCardCollection[cards[j]] & CARD_ID_MASK].unk_2A != 2) {
                            w->slots[n].cardId = gCardCollection[cards[j]] & CARD_ID_MASK;
                            w->slots[n].unk_04 = j;
                            w->slots[n].unk_06 = n;
                            w->slots[n].unk_07 = 0;
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

    w->unk_50 = n;
    TaskPoolInit(&w->tasks, w->unk_50 + 1);
    ListPoolInit(&gCardListWork->cards);
    gCardListWork->selectedCard = 0;
    gCardListWork->effectCount = 0;
    TaskPoolInit(&gCardListWork->effectTasks, 24);
    func_0809C294(w);
    w->unk_51 = 10;
    w->unk_52 = 0;
    w->unk_84 = 0;
    w->unk_85 = 1;
    w->unk_86 = 1;
    w->unk_87 = 0;
    w->unk_8A = 0;
    w->unk_8B = 16;
    w->unk_8C = 16;
    w->unk_30 = -0x80;
    w->unk_34 = -0x800;
    w->unk_38 = 0xA000;
}

u8 func_0809BE80(UnkStruct_0809BB4C* w, void* a) {
    UnkStruct_0809C534* n;
    s32 t;
    s32 z;

    if (w->unk_85 != 0) {
        if ((GetKeysPressed() & A_BUTTON) && w->unk_84 == 0) {
            w->unk_84 = 1;
            m4aSongNumStart(SONG_SYS_ITEMGET);
        }

        if ((GetKeysPressed() & B_BUTTON) && w->unk_84 != 1) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            w->unk_8B = 16;
            w->unk_8C = 16;
            SetTaskUpdate(a, (TaskUpdateFunc)func_0809C4B0);
            n = (UnkStruct_0809C534*)ListPoolFirst(&gCardListWork->cards);

            while (n != 0) {
                n->unk_55 |= 0xFF;
                w->unk_86 = 0;
                n = (UnkStruct_0809C534*)ListPoolNext(&n->node);
            }

            TaskPoolUpdate(&w->tasks);
            TaskPoolUpdate(&gCardListWork->effectTasks);
            z = 0;
            w->unk_87 = 1;
            w->unk_85 = z;
            return 1;
        }
    }

    n = (UnkStruct_0809C534*)ListPoolFirst(&gCardListWork->cards);

    if (w->unk_84 == 0) {
        while (n != 0) {
            t = n->unk_53;

            if (t == 0) {
                m4aSongNumStart(SONG_SYS_CLICK);

                if (n->unk_52 < w->unk_50 - 1) {
                    n->unk_52++;
                } else {
                    n->unk_52 = t;
                }

                n->unk_53 = w->unk_51;
                w->unk_52 = 1;
            }

            n = (UnkStruct_0809C534*)ListPoolNext(&n->node);
        }
    } else {
        w->unk_87 = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0809C2D0);
    }

    if (w->unk_51 == 4 || w->unk_51 == 10) {
        w->unk_85 = 1;
    } else {
        w->unk_85 = 0;
    }

    if (w->unk_52 != 0) {
        if (w->unk_51 > 4) {
            w->unk_51--;
        }

        w->unk_52 = 0;
    }

    w->gfx = AnimUpdate(&w->anim);
    w->gfx2 = AnimUpdate(&w->anim2);
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&gCardListWork->effectTasks);
    return 1;
}

u8 func_0809C078(UnkStruct_0809BB4C* w, void* a) {
    s32 v;
    u8* p;
    UnkStruct_0809C534* n;

    n = (UnkStruct_0809C534*)ListPoolFirst(&gCardListWork->cards);

    if (n != 0 && n->unk_55 == 1) {
        SetTaskUpdate(a, (TaskUpdateFunc)func_0809BE80);
    }

    p = &w->unk_8C;

    if (*p != 0) {
        ApproachValue(&w->unk_34, 0, *p);
        ApproachValue(&w->unk_38, 0x9800, *p);
    } else {
        v = w->unk_30 << 8;
        p = &w->unk_8B;
        ApproachValue(&v, 0, *p);
        w->unk_30 = v >> 8;
    }

    (*p)--;
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&gCardListWork->effectTasks);
    return 1;
}

void func_0809C110(UnkStruct_0809BB4C* w) {
    if (w->unk_87 == 0) {
        DrawSprite(62, 50, w->gfx, w->tiles2, w->palette2, 0, 0, 0);
        DrawSprite(53, 64, w->gfx2, w->tiles3, w->palette3, 0, 0, 0);
    }

    if (w->unk_85 != 0) {
        DrawSprite(88, 70, gUnk_09EE98EC[0], w->tiles4, w->palette4, 0, 0, 0);
    }

#ifdef VERSION_EU
    DrawSprite(w->unk_30, 0, gUnkEu_09F72BFC[gLanguage][0], w->tiles, w->palette, 0, 0, 0);
#else
    DrawSprite(w->unk_30, 0, gUnk_09EEA16C[0], w->tiles, w->palette, 0, 0, 0);
#endif
    DrawSprite(120, w->unk_34 >> 8, gUnk_09EEA174[0], w->tiles5, w->palette, 0, 0, 60);
    DrawSprite(120, w->unk_38 >> 8, gUnk_09EEA174[1], w->tiles5, w->palette, 0, 0, 60);
    TaskPoolDraw(&w->tasks);
    TaskPoolDraw(&gCardListWork->effectTasks);
}

void func_0809C1EC(UnkStruct_0809BB4C* w) {
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
    func_0800FDD0(0xF5);
    TaskPoolDestroy(&w->tasks);
}

void func_0809C294(UnkStruct_0809BB4C* w) {
    u8 i;

    for (i = 0; i < w->unk_50; i++) {
        w->slots[i].unk_06 = i;
        TaskCreate(&w->tasks, &gUnk_09EE781C, &w->slots[i]);
    }
}
u8 func_0809C2D0(UnkStruct_0809BB4C* w, void* a) {
    UnkStruct_0809C534* n;
    TaskPool* pool;
    u8 z;
    u8 t;
    u8* q;

    n = (UnkStruct_0809C534*)ListPoolFirst(&gCardListWork->cards);
    w->gfx = AnimUpdate(&w->anim);
    w->gfx2 = AnimUpdate(&w->anim2);
    w->unk_51 = 0;
    w->unk_8A++;
    w->unk_85 = 0;

    if (w->unk_86 != 0) {
        while (n != 0) {
            if (n->unk_53 == 0) {
                if (n->unk_52 == 3) {
                    n->unk_55 = 2;
                    ConvertActiveDeckCardToPremium(n->unk_48);
                } else {
                    n->unk_55 = 3;
                }

                w->unk_86 = 0;
            }

            n = (UnkStruct_0809C534*)ListPoolNext(&n->node);
        }
    }

    t = w->unk_8A;
    pool = &w->tasks;

    if (t == 30) {
        q = &w->unk_87;
        z = 0;
        *q = 1;
        SetBgPriority(2, 0);
        BgAnimInit(2, 0x8000, 0x80);
        BgAnimStart(&gUnk_09EDA9A8, 120, 60);
        w->unk_88 = BgAnimGetDuration(&gUnk_09EDA9A8);
        w->unk_89 = z;
        gBldCnt = (BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_OBJ);
        gBldAlpha = 0x1010;
        BgAnimUpdate();
        FadeSetPaletteExcluded(10, 1);
        FadeSetPaletteExcluded(11, 1);
        FadeSetPaletteExcluded(12, 1);
        FadeSetPaletteExcluded(13, 1);
        FadeSetPaletteExcluded(14, 1);
        FadeSetPaletteExcluded(15, 1);
        TaskCreate(pool, &gTaskDescCardName, 0);
        SetTaskUpdate(a, (TaskUpdateFunc)func_0809C448);
    }

    TaskPoolUpdate(pool);
    TaskPoolUpdate(&gCardListWork->effectTasks);
    return 1;
}

u8 func_0809C448(UnkStruct_0809BB4C* w, void* a) {
    ListPoolFirst(&gCardListWork->cards);
    BgAnimUpdate();
    w->gfx = AnimUpdate(&w->anim);
    w->gfx2 = AnimUpdate(&w->anim2);
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&gCardListWork->effectTasks);

    if ((GetKeysPressed() & A_BUTTON)
#ifdef VERSION_EU
        && w->unk_89 > 8
#endif
    ) {
        w->unk_8B = 16;
        w->unk_8C = 16;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0809C4B0);
    }

#ifdef VERSION_EU
    if (w->unk_89 <= 254) {
        w->unk_89++;
    }
#endif

    return 1;
}

u8 func_0809C4B0(UnkStruct_0809BB4C* w, void* a) {
    s32 v;
    u8* p;

    p = &w->unk_8B;

    if (*p != 0) {
        v = w->unk_30 << 8;
        ApproachValue(&v, -0x8000, *p);
        w->unk_30 = v >> 8;
    } else {
        p = &w->unk_8C;

        if (*p == 0) {
            return 0;
        }

        ApproachValue(&w->unk_34, -0x800, *p);
        ApproachValue(&w->unk_38, 0xA000, *p);
    }

    (*p)--;
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&gCardListWork->effectTasks);
    return 1;
}

struct UnkStruct_0809BB4C;
void func_0809BB4C(struct UnkStruct_0809BB4C* w);

TaskDesc gTaskDescFriendCard = {
    "Friend card",
    (TaskInitFunc)Friend_card_0,
    (TaskUpdateFunc)Friend_card_1,
    (TaskFunc)func_0809B200,
    (TaskFunc)func_0809B59C,
    sizeof(UnkStruct_0809A02C),
};

TaskDesc gTaskDescHeartlessCard = {
    "Heartless card",
    (TaskInitFunc)Heartless_card_0,
    (TaskUpdateFunc)Heartless_card_1,
    (TaskFunc)Heartless_card_2,
    (TaskFunc)Heartless_card_3,
    sizeof(UnkStruct_0809A02C),
};

TaskDesc gTaskDescGimmickCard = {
    "Gimmick card",
    (TaskInitFunc)Gimmick_card_0,
    (TaskUpdateFunc)Gimmick_card_1,
    (TaskFunc)func_0809B200,
    (TaskFunc)func_0809B59C,
    sizeof(UnkStruct_0809A02C),
};

TaskDesc gUnk_09EE77D4 = {
    "StockName",
    (TaskInitFunc)func_0809B76C,
    (TaskUpdateFunc)func_0809B840,
    (TaskFunc)func_0809B8F0,
    (TaskFunc)func_0809BB18,
    sizeof(StockNameWork),
};

TaskDesc gUnk_09EE77EC = {
    "StockName",
    (TaskInitFunc)func_0809B920,
    (TaskUpdateFunc)func_0809B9F4,
    (TaskFunc)func_0809BAA4,
    (TaskFunc)func_0809BAE4,
    sizeof(StockNameWork),
};
#ifdef VERSION_EU
void** gUnkEu_09F72BFC[5] = { gUnk_09EEA16C, &gUnkEu_09F75FB4, &gUnkEu_09F75FCC, &gUnkEu_09F75FC4, &gUnkEu_09F75FBC };
#endif

TaskDesc gUnk_09EE7804 = {
    "Premire Chance",
    (TaskInitFunc)func_0809BB4C,
    (TaskUpdateFunc)func_0809C078,
    (TaskFunc)func_0809C110,
    (TaskFunc)func_0809C1EC,
    sizeof(UnkStruct_0809BB4C),
};
