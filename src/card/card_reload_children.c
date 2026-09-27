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
#include "sprites_card.h"

extern void* gUnk_09EE7698[];
extern void* gUnk_09EE76C0[];
extern void** gUnk_09EE76D0[];
extern void* gUnk_09EE7708[];
extern AnimHeader** gUnk_09EE7714[];
extern void** gUnk_09EE7720[];
void CreateCardNameDisplay(void* a, void* b);
s32 func_08098BA4(ReloadChildWork* w);
u8 func_08099330(ReloadWork* w);
s16 func_08084458(u16 cardId);
void _08085D04(u8 a);
void CreateCardNameDisplay(void* a, void* b);

const s16 gUnk_090361B0[4] = { 16, 29, 42, 51 };

const s16 gUnk_090361B8[4] = { -16, -29, -42, -51 };

const s16 gUnk_090361C0[4] = { 0, 0, 0, 24 };

void RELOAD_CHILDREN_0(ReloadChildWork* w, ReloadChildArgs* a) {
    w->args = *a;
    w->tiles = LoadObjTiles(gUnk_09EE7698[w->args.unk_0D], 128);
    w->palette = LoadObjPalette(gCard00Palette, 32);
    w->tiles2 = 0;

    switch (w->args.unk_0E) {
    case 1:
        if ((s8)w->args.unk_0C <= 3) {
            w->unk_20 = gUnk_090361B0[(s8)w->args.unk_0C] << 8;
            w->unk_24 = gUnk_090361C0[(s8)w->args.unk_0C] << 8;
        } else {
            w->unk_20 = gUnk_090361B0[3] << 8;
            w->unk_24 = gUnk_090361C0[3] << 8;
        }
        break;
    case 2:
        if ((s8)w->args.unk_0C <= 3) {
            w->unk_20 = gUnk_090361B8[(s8)w->args.unk_0C] << 8;
            w->unk_24 = gUnk_090361C0[(s8)w->args.unk_0C] << 8;
        } else {
            w->unk_20 = gUnk_090361B8[3] << 8;
            w->unk_24 = gUnk_090361C0[3] << 8;
        }
        break;
    }

    ListNodeInit(&w->node, w->args.unk_00, w);
    ListPoolAppend(&w->node, w->args.unk_00);
    w->unk_46 = 0;
}

u8 RELOAD_CHILDREN_1(ReloadChildWork* w, void* a) {
    u8 (*fn)(ReloadChildWork*, void*);

    if (w->args.unk_10 & 2) {
        w->unk_46++;

        if (w->unk_46 == 30) {
            w->unk_44 = 8;
            fn = func_08098AE4;
            SetTaskUpdate(a, (TaskUpdateFunc)fn);
            return fn(w, a);
        }
    }

    if (w->args.unk_10 & 1) {
        w->unk_44 = 8;
        w->args.unk_10 &= ~1;
    }

    if (w->args.unk_0C <= 3) {
        switch (w->args.unk_0E) {
        case 1:
            ApproachValue(&w->unk_20, gUnk_090361B0[(s8)w->args.unk_0C] << 8, w->unk_44);
            break;
        case 2:
            ApproachValue(&w->unk_20, gUnk_090361B8[(s8)w->args.unk_0C] << 8, w->unk_44);
            break;
        }

        ApproachValue(&w->unk_24, gUnk_090361C0[(s8)w->args.unk_0C] << 8, w->unk_44);
    } else if ((s8)w->args.unk_0C < 0) {
        ListPoolRemove(&w->node, w->args.unk_00);
        w->tiles2 = LoadObjTiles(gUnk_08F709B0[w->args.unk_0D].tiles2, 0xD00);
        w->unk_44 = 8;
        w->scale = 0x66;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08098BA4);
        return 1;
    }

    if (w->unk_44 != 0) {
        w->unk_44--;
    }

    w->angle += 8;
    return 1;
}

u8 func_08098AE4(ReloadChildWork* w, void* a) {
    u8 (*f)(ReloadChildWork*, void*);
    u16 v;

    v = w->args.unk_10 & 2;

    if (v == 0) {
        w->unk_44 = 8;
        f = RELOAD_CHILDREN_1;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        w->unk_46 = 0;
        return f(w, a);
    }

    switch (w->args.unk_0E) {
    case 1:
        ApproachValue(&w->unk_20, gUnk_090361B0[(s8)w->args.unk_0C] << 8, w->unk_44);
        break;
    case 2:
        ApproachValue(&w->unk_20, gUnk_090361B8[(s8)w->args.unk_0C] << 8, w->unk_44);
        break;
    }

    ApproachValue(&w->unk_24, gUnk_090361C0[3] << 8, w->unk_44);

    if (w->unk_44 != 0) {
        w->unk_44--;
    }

    return 1;
}

s32 func_08098BA4(ReloadChildWork* w) {
    ApproachValue(&w->unk_20, 0, w->unk_44);
    ApproachValue(&w->unk_24, 0, w->unk_44);
    ApproachValue(&w->scale, 256, w->unk_44);

    if (w->unk_44 != 0) {
        w->unk_44--;
        return 1;
    }

    return 0;
}

void RELOAD_CHILDREN_2(ReloadChildWork* w) {
    s16 x;
    s16 y;
    ObjAffine* aff;

    if (w->args.unk_0C <= 3) {
        x = (w->unk_20 + *w->args.unk_04) >> 8;
        y = (w->unk_24 + *w->args.unk_08) >> 8;
        DrawSprite(x, y + (gSineTable[w->angle] >> 8), gUnk_09EEA344[0], w->tiles, w->palette, 0, 0, 50);
    }

    if ((s8)w->args.unk_0C < 0) {
        x = (w->unk_20 + *w->args.unk_04) >> 8;
        y = (w->unk_24 + *w->args.unk_08) >> 8;
        aff = AllocObjAffine(0, w->scale, w->scale, 0);
        DrawSprite(x, y + (gSineTable[w->angle] >> 8), gUnk_08F709B0[w->args.unk_0D].gfx2, w->tiles2, w->palette, aff, 0, 49);
    }
}

void RELOAD_CHILDREN_3(ReloadChildWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);

    if (w->tiles2 != 0) {
        ReleaseObjTiles(w->tiles2);
    }
}
void REV_COUNT_0(RevCountWork* w, RevCountArgs* a) {
    vu32 zero;
    s16* count;
    s16* count2;
    void** row;
    u8 idx;

    zero = 0;
    CpuSet((void*)&zero, w, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(RevCountWork) / 4);
    w->args = *a;
    idx = w->args.unk_0C;
    w->unk_24 = idx;
    w->tiles = AllocSpriteFrameTiles(320);
    w->palette = LoadObjPalette(gCard00Palette, 32);

    if (w->unk_24 == 0) {
        count = (s16*)w->args.unk_04;

        if (*count >= 2 && *count <= 100) {
            row = gUnk_09EE76D0[w->unk_24];
            UpdateSpriteFrameTiles(w->tiles, row[*count - 2], gUnk_09EE76C0[w->unk_24]);
        } else if (*count > 100) {
            row = gUnk_09EE76D0[w->unk_24];
            UpdateSpriteFrameTiles(w->tiles, row[98], gUnk_09EE76C0[w->unk_24]);
        } else {
            row = gUnk_09EE76D0[w->unk_24];
            UpdateSpriteFrameTiles(w->tiles, row[0], gUnk_09EE76C0[w->unk_24]);
        }
    } else {
        count2 = (s16*)w->args.unk_04;

        if (*count2 >= 1 && *count2 <= 99) {
            row = gUnk_09EE76D0[w->unk_24];
            UpdateSpriteFrameTiles(w->tiles, row[*count2 - 1], gUnk_09EE76C0[w->unk_24]);
        } else {
            row = gUnk_09EE76D0[w->unk_24];
            UpdateSpriteFrameTiles(w->tiles, row[0], gUnk_09EE76C0[w->unk_24]);
        }
    }

    w->gfx = AnimGetGfx(&w->anim);
    w->unk_26 = *(u16*)w->args.unk_04;

    switch (w->args.unk_0D) {
    case 1:
        w->x = -0x2000;
        w->y = 0x9800;
        break;
    case 2:
        w->x = 0x11000;
        w->y = 0x9800;
        break;
    }

    w->unk_28 = 8;
}

u8 REV_COUNT_1(RevCountWork* w, void* a) {
    s16* count;
    void** row;

    count = (s16*)w->args.unk_04;

    if (*count != (s16)w->unk_26) {
        if (w->unk_24 == 0) {
            if (*count >= 2 && *count <= 100) {
                row = gUnk_09EE76D0[w->unk_24];
                UpdateSpriteFrameTiles(w->tiles, row[*count - 2],
                              gUnk_09EE76C0[w->unk_24]);
            } else {
                u8 (*f)(RevCountWork*, void*);

                w->unk_28 = 8;
                f = func_080990CC;
                SetTaskUpdate(a, (TaskUpdateFunc)f);
                w->unk_26 = *(u16*)w->args.unk_04;
                return f(w, a);
            }
        } else {
            if (*count >= 1 && *count <= 99) {
                row = gUnk_09EE76D0[w->unk_24];
                UpdateSpriteFrameTiles(w->tiles, row[*count - 1],
                              gUnk_09EE76C0[w->unk_24]);
            } else {
                u8 (*f)(RevCountWork*, void*);

                w->unk_28 = 8;
                f = func_080990CC;
                SetTaskUpdate(a, (TaskUpdateFunc)f);
                w->unk_26 = *(u16*)w->args.unk_04;
                return f(w, a);
            }
        }

        w->unk_26 = *(u16*)w->args.unk_04;
    } else if (*count <= 0) {
        u8 (*f)(RevCountWork*, void*);

        w->unk_28 = 8;
        f = func_080990CC;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        w->unk_26 = *(u16*)w->args.unk_04;
        return f(w, a);
    }

    switch (w->args.unk_0D) {
    case 1:
        ApproachValue(&w->x, 0, w->unk_28);
        break;
    case 2:
        ApproachValue(&w->x, 0xD800, w->unk_28);
        break;
    }

    if (w->unk_28 != 0) {
        w->unk_28--;
    }

    if (w->args.unk_0C != *(u8*)w->args.unk_00) {
        u8 (*f)(RevCountWork*, void*);

        f = (u8 (*)(RevCountWork*, void*))func_08098FDC;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        w->unk_28 = 8;
        return f(w, a);
    }

    if (gBtlWork->unk_0A0 == 4) {
        w->unk_28 = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08099048);
    }

    if (*(u8*)w->args.unk_08 == 0) {
        w->unk_28 = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08099048);
    }

    return 1;
}

u8 func_08098FDC(RevCountWork* w) {
    switch (w->args.unk_0D) {
    case 1:
        ApproachValue(&w->x, -0x2000, w->unk_28);
        break;
    case 2:
        ApproachValue(&w->x, 0x11000, w->unk_28);
        break;
    }

    if (w->unk_28 != 0) {
        w->unk_28--;
    }

    if (w->args.unk_0C == *(u8*)w->args.unk_00 && *(s16*)w->args.unk_04 > 0) {
        return 0;
    }

    return 1;
}

u8 func_08099048(RevCountWork* w, void* a) {
    u8 (*f)(RevCountWork*, void*);

    switch (w->args.unk_0D) {
    case 1:
        ApproachValue(&w->x, -0x2000, w->unk_28);
        break;
    case 2:
        ApproachValue(&w->x, 0x11000, w->unk_28);
        break;
    }

    if (w->unk_28 == 0) {
        return 0;
    }

    w->unk_28--;

    if (*(u8*)w->args.unk_08 == 1) {
        w->unk_28 = 8;
        f = REV_COUNT_1;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        return f(w, a);
    }

    return 1;
}

u8 func_080990CC(RevCountWork* w, void* a) {
    u8 (*f)(RevCountWork*, void*);

    switch (w->args.unk_0D) {
    case 1:
        ApproachValue(&w->x, -0x2000, w->unk_28);
        break;
    case 2:
        ApproachValue(&w->x, 0x11000, w->unk_28);
        break;
    }

    if (w->unk_28 != 0) {
        w->unk_28--;
    }

    do {
        if (w->unk_24 == 0) {
            if (*(s16*)w->args.unk_04 > 1) {
                f = REV_COUNT_1;
                SetTaskUpdate(a, (TaskUpdateFunc)f);
                w->unk_28 = 8;
                return f(w, a);
            }
        } else {
            if (*(s16*)w->args.unk_04 > 0) {
                f = REV_COUNT_1;
                SetTaskUpdate(a, (TaskUpdateFunc)f);
                w->unk_28 = 8;
                return f(w, a);
            }
        }

        return 1;
    } while (0);
}

#ifdef VERSION_EU
#define REV_COUNT_SPRITE_FLAGS 0x410
#else
#define REV_COUNT_SPRITE_FLAGS 0x400
#endif

void REV_COUNT_2(RevCountWork* w) {
    DrawSprite(w->x >> 8, w->y >> 8, 0, w->tiles, w->palette, 0, REV_COUNT_SPRITE_FLAGS, 15);
}

void REV_COUNT_3(RevCountWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void CreateREVCOUNTTask(void* pool, u8* a, void* b, u8* c, u8 d) {
    RevCountArgs args;

    c[0] = 1;
    args.unk_00 = a;
    args.unk_04 = b;
    args.unk_08 = c;
    args.unk_0C = a[0];
    args.unk_0D = d;
    TaskCreate(pool, &gTaskDescREVCOUNT, &args);
}

void RELOAD_0(ReloadWork* w, ReloadArgs* a) {
    w->tiles = AllocObjTiles(0xA0, 0);
    w->palette = LoadObjPalette(gCard00Palette, 32);
    w->args = *a;
    SetObjTileSource(w->tiles, gUnk_09EE7708[w->args.slot]);
    AnimInit(&w->anim, gUnk_09EE7714[w->args.slot], gUnk_09EE7720[w->args.slot]);
    AnimStart(&w->anim, 0, 1);
    w->gfx = AnimGetGfx(&w->anim);

    switch (w->args.mode) {
    case 1:
        w->x = -0x3000;
        w->y = 0x7E00;
        break;
    case 2:
        w->x = 0xB4800;
        w->y = 0x7E00;
        break;
    }

    w->unk_34 = 6;
}

u8 RELOAD_1(ReloadWork* w, void* a) {
    w->gfx = AnimUpdate(&w->anim);

    switch (w->args.mode) {
    case 1:
        ApproachValue(&w->x, 0x1800, w->unk_34);
        break;
    case 2:
        ApproachValue(&w->x, 0xD800, w->unk_34);
        break;
    }

    if (w->unk_34 != 0) {
        w->unk_34--;
    }

    if (*w->args.state == 0) {
        w->unk_34 = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08099330);
    }

    if (gBtlWork->unk_0A0 == 4) {
        w->unk_34 = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08099330);
    }

    return 1;
}

u8 func_08099330(ReloadWork* w) {
    w->gfx = AnimUpdate(&w->anim);

    switch (w->args.mode) {
    case 1:
        ApproachValue(&w->x, -0x3000, w->unk_34);
        break;
    case 2:
        ApproachValue(&w->x, 0x12000, w->unk_34);
        break;
    }

    if (w->unk_34 != 0) {
        w->unk_34--;
        return 1;
    }

    return 0;
}

void RELOAD_2(ReloadWork* w) {
    DrawSprite(w->x >> 8, w->y >> 8, w->gfx, w->tiles, w->palette, 0, 0, 10);
}
void RELOAD_3(ReloadWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}
void PrizeBoss_0(BossPrizeWork* w, PrizeCardTaskArgs* args) {
    CardDef* def;
    CardBack* back;
    Collider* p;

    w->cardId = args->cardId;
    def = &gCardDefs[args->cardId];
    w->tiles = LoadObjTiles(def->tiles, 0x300);
    w->palette = LoadObjPalette(def->palette, 32);
    w->stat = *(CardStat*)&def->unk_1C;
    back = &gUnk_08F709B0[def->unk_2A];
    w->tiles2 = LoadObjTiles(back->tiles, 0x280);
    w->tiles3 = LoadObjTiles(back->tiles3, 0x600);
    w->palette2 = LoadObjPalette(gCard00Palette, 32);
    w->tiles4 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    w->tiles5 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    w->palette3 = LoadObjPalette(gBStatesPalette, 32);
    w->unk_A8 = args->x;
    w->unk_AC = args->y;
    w->unk_B0 = args->z;
    w->unk_B4 = 0;
    w->unk_E6 = 24;
    w->unk_BC = -(GetRandom() % 129 + 0x300);
    w->unk_C0 = GetRandom() % 129 + 0x80;
    w->unk_E4 = GetRandom() % 256;
    w->unk_D0 = 0x80;
    w->unk_D2 = 0x80;
    w->unk_E2 = 0x80;
    w->unk_E8 = 0;
    w->unk_E9 = 0;
    p = &w->collider;
    ColliderInit(p, 5, 8, 10);
    ColliderSetDisabled(p, 1);
    ColliderSetPosition(p, w->unk_A8, w->unk_AC, w->unk_B0);
    w->unk_EA = 0;
    w->unk_ED = 0;
    w->unk_EB = 0;
    w->unk_EC = 0;
    w->unk_EE = 0;
    w->unk_EF = 0;
    m4aSongNumStart(SONG_EF_BOSS_DEAD4);
    TaskPoolInit(&w->tasks, 10);
    gBtlWork->unk_0B0++;
}
u8 PrizeBoss_1(BossPrizeWork* w, void* a) {
    s16 x;
    s16 y;
    if (w->unk_B0 < 0) {
        w->unk_B0 += 51;
        func_08099CDC(w);
    }
    if (gBtlWork->unk_0F4 == 6) {
        ColliderSetRadius(&w->collider, 30);
    } else {
        ColliderSetRadius(&w->collider, 10);
    }
    ColliderSetPosition(&w->collider, w->unk_A8, w->unk_AC, w->unk_B0);
    WorldToScreen(&w->x, &w->y, w->unk_A8, w->unk_AC, w->unk_B0);
    WorldToScreen(&w->x2, &w->y2, w->unk_A8, w->unk_AC, w->unk_B4);
    w->priority = -0x1004 - (w->unk_AC >> 8) * 4;
    func_08099928(w);
    w->unk_E9 += 2;
    if (w->unk_EA == 60) {
        ColliderSetDisabled(&w->collider, 0);
    }
    if (w->unk_EA <= 59) {
        w->unk_EA++;
    }
    if (w->collider.unk_2C != 0) {
        w->unk_ED = 1;
        m4aSongNumStart(SONG_SYS_ITEMGET);
        func_08084458(*(u16*)&w->cardId);
        if (gGameState.flags & 8) {
            _08085D04(gGameState.world);
        }
        SetTaskUpdate(a, (TaskUpdateFunc)func_08099A18);
        WorldToScreen(&x, &y, w->unk_A8, w->unk_AC, w->unk_B0);
        w->unk_A8 = x << 8;
        w->unk_AC = y << 8;
        ColliderSetDisabled(&w->collider, 1);
        w->unk_EB = 16;
        w->priority = 50;
        func_080999A4(w);
    }
    TaskPoolUpdate(&w->tasks);
    return 1;
}

void PrizeBoss_2(BossPrizeWork* w) {
    u16 pal;
    ObjAffine* affine;
    void* gfx;
    CardBack* back;
    CardDef* def;
    s16 v;

    pal = w->unk_ED == 0 ? GetBattleSpritePriorityFlags(w->unk_AC) : 0;
    affine = AllocObjAffine(w->unk_E6, w->unk_D0, w->unk_D2, 1);
    def = &gCardDefs[w->cardId];
    DrawSprite(w->x, (u16)w->y - 8, def->gfx, w->tiles, w->palette, affine, pal,
               (u16)(w->priority + 1));
    back = &gUnk_08F709B0[w->stat.unk_0E];
    DrawSprite(w->x, (u16)w->y - 8, back->gfx, w->tiles2, w->palette2, affine, pal,
               w->priority);
    gfx = gUnk_09EE981C[w->stat.unk_04];

    if (def->unk_2A != 3) {
        DrawSprite(w->x, (u16)w->y - 8, gfx, w->tiles4, w->palette2, affine, pal,
                   (u16)(w->priority - 1));
    }

    if (w->unk_ED == 0) {
        v = 204 - ((w->unk_B4 - w->unk_B0) >> 7);

        if (v <= 2) {
            v = 2;
        }

        DrawSprite(w->x2, w->y2, gUnk_09EE1380[0], w->tiles5, w->palette3,
                   AllocObjAffine(0, v, v, 0), pal, (u16)(w->priority + 2));
    }

    TaskPoolDraw(&w->tasks);
}

void PrizeBoss_3(BossPrizeWork* w) {
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
    gBtlWork->unk_0B0--;
}

void func_08099928(BossPrizeWork* w) {
    w->unk_D0 = (-gSineTable[((w->unk_E9 + 0x80) & 0xFF) + 0x40] * w->unk_E2) >> 8;
    w->unk_D2 = (-gSineTable[((w->unk_E8 + 0x80) & 0xFF) + 0x40] * w->unk_E2) >> 8;

    if ((u16)(w->unk_D0 + 2) <= 4) {
        w->unk_D0 = 2;
    }

    if ((u16)(w->unk_D2 + 2) <= 4) {
        w->unk_D2 = 2;
    }
}

void func_080999A4(BossPrizeWork* w) {
    s16 x;
    s16 y;
    s32 dx;
    s32 dy;
    s32 tx;
    s32 ty;

    WorldToScreen(&x, &y, gBtlWork->actor->x, gBtlWork->actor->y, gBtlWork->actor->z);
    tx = 0x7800;
    ty = 0x5000;
    dx = tx - w->unk_A8;
    dy = ty - w->unk_AC;
    w->unk_CC = NormalizeVector2D8(&dx, &dy);
    w->unk_C4 = -dx;
    w->unk_C8 = -dy;
    w->unk_C0 = 0x300;
    w->unk_BC = 2;
}

u8 func_08099A18(BossPrizeWork* w, void* a) {
    s32 dx;
    s32 dy;
    u8 z;
    u8 t;
    s32 x;
    s32 y;
    s16* q1;
    s16* q2;

    if (w->unk_C0 < 0) {
        dx = 0x7800 - w->unk_A8;
        dy = 0x5000 - w->unk_AC;
        NormalizeVector2D8(&dx, &dy);
        w->unk_C4 = -dx;
        w->unk_C8 = -dy;

        if (w->unk_CC <= 0x7FF) {
            w->unk_EB = 0;
            w->unk_E6 = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)func_08099B60);
#ifdef VERSION_EU
            CreateCardNameDisplay(&w->tasks, eu_0805E924(gCardDefs[w->cardId].name));
#else
            CreateCardNameDisplay(&w->tasks, gCardDefs[w->cardId].name);
#endif
        }
    }

    w->unk_A8 += (w->unk_C4 * w->unk_C0) >> 8;
    w->unk_AC += (w->unk_C8 * w->unk_C0) >> 8;
    t = w->unk_E6 + 32;
    z = 0;
    w->unk_E6 = t;
    w->unk_E8 += (64 - w->unk_E8) >> 4;
    w->unk_E9 = z;
    w->unk_CC = VectorLength2D(0x7800 - w->unk_A8, 0x5000 - w->unk_AC);
    w->unk_C0 -= w->unk_BC;
    w->unk_BC += 2;

    if (w->unk_E2 <= 0xFF) {
        w->unk_E2 += 3;
    }

    x = w->unk_A8 >> 8;
    q1 = &w->x;
    *q1 = x;
    y = w->unk_AC >> 8;
    q2 = &w->y;
    *q2 = y;
    func_08099928(w);
    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 func_08099B60(BossPrizeWork* w, void* a) {
    s32 v;
    u16 t;
    s32 c;

    v = w->unk_E6 << 8;
    ApproachValue((s32*)&w->unk_E8, 0, w->unk_EB);
    ApproachValue(&v, 0, w->unk_EB);
    ApproachValue(&w->unk_A8, 0x7800, w->unk_EB);
    ApproachValue(&w->unk_AC, 0x5800, w->unk_EB);
    w->unk_E6 = v >> 8;

    if (w->unk_EB != 0) {
        w->unk_EB--;
    }

    t = w->unk_E2;

    if ((s16)t <= 0xFF) {
        w->unk_E2 = t + 2;
    } else {
        c = 0x100;
        w->unk_E2 = c;
    }

    w->x = w->unk_A8 >> 8;
    w->y = w->unk_AC >> 8;
    func_08099928(w);
    w->unk_EC++;

    if ((u32)w->cardId > 0x1C2) {
        if (w->unk_EC == 120) {
            w->unk_EC = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)func_08099C4C);
        }
    } else {
        if (w->unk_EC == 30) {
            w->unk_EC = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)func_08099C4C);
        }
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 func_08099C4C(BossPrizeWork* w) {
    w->unk_E6 += 32;
    WorldToScreen(&w->x3, &w->y3, gBtlWork->actor->x, gBtlWork->actor->y, gBtlWork->actor->z);
    w->x += (w->x3 - w->x) >> 3;
    w->y += (w->y3 - w->y) >> 3;
    w->unk_D0 -= 10;
    w->unk_D2 -= 10;

    if (w->unk_D0 <= 10) {
        return 0;
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

void func_08099CDC(BossPrizeWork* w) {
    CardEffectArgs args;

    if (w->unk_ED == 0) {
        if (w->unk_EF == 8) {
            if (w->unk_EE <= 3) {
                args.unk_00 = w->unk_A8;
                args.unk_04 = w->unk_AC;
                args.unk_08 = w->unk_B0;
                args.unk_0C = w->unk_ED;
                args.count = &w->unk_EE;
                TaskCreate(&w->tasks, &gTaskDescCardEFFECT, &args);
            }

            w->unk_EF = 0;
        } else {
            w->unk_EF++;
        }
    } else {
        if (w->unk_EF == 8) {
            if (w->unk_EE <= 7) {
                args.unk_00 = w->unk_A8;
                args.unk_04 = w->unk_AC;
                args.unk_08 = w->unk_B0;
                args.unk_0C = w->unk_ED;
                args.count = &w->unk_EE;
                TaskCreate(&w->tasks, &gTaskDescCardEFFECT, &args);
            }

            w->unk_EF = 0;
        } else {
            w->unk_EF++;
        }
    }
}

void Card_EFFECT_0(CardEffectWork* w, CardEffectArgs* a) {
    w->args = *a;

    if (w->args.unk_0C == 0) {
        w->unk_24 = a->unk_00 + ((GetRandom() % 9 - 4) << 8);
        w->unk_28 = a->unk_04;
        w->unk_2C = a->unk_08 - 0x800;
    } else {
        w->unk_24 = a->unk_00 + ((GetRandom() % 33 - 16) << 8);
        w->unk_28 = a->unk_04 - 0x1000;
        w->unk_2C = 0;
    }

    w->tiles = AllocObjTiles(0x80, 0);
    w->palette = LoadObjPalette(gUnk_09619158, 32);
    SetObjTileSource(w->tiles, gUnk_093F762E);
    AnimInit(&w->anim, gUnk_09EF1260, gUnk_09EF1230);
    AnimStart(&w->anim, GetRandom() % 3, 0);
    w->gfx = AnimGetGfx(&w->anim);
    (*w->args.count)++;
}

u8 Card_EFFECT_1(CardEffectWork* w) {
    w->gfx = AnimUpdate(&w->anim);

    if (w->args.unk_0C == 0) {
        WorldToScreen(&w->x, &w->y, w->unk_24, w->unk_28, w->unk_2C);
        w->unk_2C -= 0x100;
    } else {
        w->x = w->unk_24 >> 8;
        w->y = w->unk_28 >> 8;
        w->unk_28 -= 0x100;
    }

    if (AnimIsFinished(&w->anim)) {
        return 0;
    }

    return 1;
}

void Card_EFFECT_2(CardEffectWork* w) {
    s16 t;
    s32 z;

    t = -4100 - ((w->y >> 8) * 4);
    z = 0;
    w->priority = t;
    DrawSprite(w->x, w->y, w->gfx, w->tiles, w->palette, 0, z, w->priority);
}

void Card_EFFECT_3(CardEffectWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    w->args.count[0]--;
}

void scrollbar_0(ScrollBarWork* w, u16* args) {
    w->unk_08 = args[0];
    w->unk_0A = args[1];
    w->unk_0C = args[2];
    w->unk_10 = args[3];
    w->unk_12 = args[4];
    w->unk_16 = 1;
    w->unk_0E = 0;
    w->unk_17 = 0;
}

u8 scrollbar_1(ScrollBarWork* w) {
    return w->unk_16;
}
void scrollbar_2(void) {
}
void scrollbar_3(void) {
}
void ScrollbarRequestClose(ScrollBarWork* w) {
    if (w != 0) {
        w->unk_16 = 0;
    }
}
void ScrollbarAdvance(ScrollBarWork* w) {
    if (w != 0) {
        if (w->unk_12 != 0) {
            w->unk_10++;
            w->unk_12--;
        } else {
            w->unk_12 = w->unk_14 - 1;
            w->unk_10 = 0;
        }
    }
}
void ScrollbarRetreat(ScrollBarWork* w) {
    if (w != 0) {
        if (w->unk_10 != 0) {
            w->unk_10--;
            w->unk_12++;
        } else {
            w->unk_10 = w->unk_14 - 1;
            w->unk_12 = 0;
        }
    }
}
void func_08099FC8(ScrollBarWork* w) {
    if (w != 0) {
        w->unk_14--;
    }
}
void func_08099FD8(ScrollBarWork* w) {
    if (w != 0) {
        w->unk_14++;
    }
}
void func_08099FE8(ScrollBarWork* w, u16 b, u8 c) {
    if (w != 0) {
        w->unk_0E = b;
        w->unk_17 = c;
    }
}
ScrollBarWork* CreateScrollbar(void* pool, u16 a, u16 b, u16 c, u16 d, u16 e) {
    u16 args[5];

    args[0] = a;
    args[1] = b;
    args[2] = c;
    args[3] = d;
    args[4] = e;
    return TaskCreate(pool, &gTaskDescScrollbar, args)->work;
}

void* gUnk_09EE7698[4] = {
    gUnk_090994A4,
    gUnk_0909937C,
    gUnk_09099410,
    gUnk_09099538,
};

TaskDesc gTaskDescReloadChildren = {
    "RELOAD_CHILDREN",
    (TaskInitFunc)RELOAD_CHILDREN_0,
    (TaskUpdateFunc)RELOAD_CHILDREN_1,
    (TaskFunc)RELOAD_CHILDREN_2,
    (TaskFunc)RELOAD_CHILDREN_3,
    sizeof(ReloadChildWork),
};

void* gUnk_09EE76C0[4] = {
    gUnk_0909D2AC,
    gUnk_0909D2AC,
    gUnk_0909D2AC,
    gUnk_0909D2AC,
};

void** gUnk_09EE76D0[4] = {
    gUnk_09EEA5C4,
    gUnk_09EEA5C4,
    gUnk_09EEA5C4,
    gUnk_09EEA5C4,
};

AnimHeader** gUnk_09EE76E0 = &gUnk_09EEA750;

AnimHeader** gUnk_09EE76E4 = &gUnk_09EEABA8;

AnimHeader** gUnk_09EE76E8 = &gUnk_09EEA97C;

AnimHeader** gUnk_09EE76EC = &gUnk_09EEADD4;

TaskDesc gTaskDescREVCOUNT = {
    "REV_COUNT",
    (TaskInitFunc)REV_COUNT_0,
    (TaskUpdateFunc)REV_COUNT_1,
    (TaskFunc)REV_COUNT_2,
    (TaskFunc)REV_COUNT_3,
    sizeof(RevCountWork),
};

void* gUnk_09EE7708[3] = {
    gUnk_0909885E,
    gUnk_09098E0E,
    gUnk_09098B36,
};

AnimHeader** gUnk_09EE7714[3] = {
    gUnk_09EEA304,
    gUnk_09EEA32C,
    gUnk_09EEA318,
};

void** gUnk_09EE7720[3] = {
    gUnk_09EEA2F4,
    gUnk_09EEA31C,
    gUnk_09EEA308,
};

TaskDesc gTaskDescRELOAD = {
    "RELOAD",
    (TaskInitFunc)RELOAD_0,
    (TaskUpdateFunc)RELOAD_1,
    (TaskFunc)RELOAD_2,
    (TaskFunc)RELOAD_3,
    sizeof(ReloadWork),
};

TaskDesc gTaskDescPrizeBoss = {
    "PrizeBoss",
    (TaskInitFunc)PrizeBoss_0,
    (TaskUpdateFunc)PrizeBoss_1,
    (TaskFunc)PrizeBoss_2,
    (TaskFunc)PrizeBoss_3,
    sizeof(BossPrizeWork),
};

TaskDesc gTaskDescCardEFFECT = {
    "Card_EFFECT",
    (TaskInitFunc)Card_EFFECT_0,
    (TaskUpdateFunc)Card_EFFECT_1,
    (TaskFunc)Card_EFFECT_2,
    (TaskFunc)Card_EFFECT_3,
    sizeof(CardEffectWork),
};

TaskDesc gTaskDescScrollbar = {
    "scrollbar",
    (TaskInitFunc)scrollbar_0,
    (TaskUpdateFunc)scrollbar_1,
    (TaskFunc)scrollbar_2,
    (TaskFunc)scrollbar_3,
    sizeof(ScrollBarWork),
};
