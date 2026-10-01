#include "registration_data.h"
#include "system_state.h"
#include "msg_api.h"
#include "card_battle.h"
#include "obj_api.h"
#include "display.h"
#include "engine_math.h"
#include "obj.h"
#include "taskpool.h"
#include "card.h"
#include "game.h"
#include "sprites_number_plus.h"
#include "battle_backgrounds.h"
#include "sprites_btl_hud.h"
#include "sprites_card.h"
#include "battle_work.h"
#include "card_api.h"
#include "card_label_data.h"
#include "mode.h"
#include "types.h"

TaskPool gModePremireTasks;
#ifndef VERSION_EU
u8 gUnk_02034AF4[4];
#endif

#ifdef VERSION_EU

#define LANGSTR(x) (((void**)(x))[gLanguage])
#else
#define LANGSTR(x) (x)
#endif
u8 IsHcEffectNameShuffling(HcEffectNameWork* w);
u8 UpdateHcEffectNameShuffle(HcEffectNameWork* w, void* a);

void Mode_Premire_0() {
    func_08085FB0();
    InitSoraDecks();
    SetBgMode2();
    SetupBg(3, 0, 12, 0);
    SetupBg(2, 2, 28, 10);
    SetBgSize(3, 0x8000);
#ifdef VERSION_EU
    LoadBgTiles(3, gUnk_08C8C824, 0x4000);
    LoadBgPalette(3, gUnk_08F68A84, 0x100);
    eu_080059F4(3, gUnk_08EF4384);
#else
    LoadBgTiles(3, gUnk_08C8C824, 0x4000);
    LoadBgPalette(3, gUnk_08F68A84, 0x100);
    LoadBgMap(3, gUnk_08EF4384, 0x1000);
#endif
    SetBgAffine(3, 0, 0x100, 0x100, 0x10000, 0x16800);
    TaskPoolInit(&gModePremireTasks, 1);
    TaskCreate(&gModePremireTasks, &gTaskDescLevelUp, 0);
}

void Mode_Premire_1() {
    TaskPoolUpdate(&gModePremireTasks);
    TaskPoolDraw(&gModePremireTasks);
}

void Mode_Premire_2() {
    TaskPoolDestroy(&gModePremireTasks);
}

u8 GetHcEffectCountUnit(HcEffectNameWork* w, u16 n) {
    switch (n) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 16:
    case 17:
    case 19:
    case 20:
    case 21:
    case 24:
    case 25:
    case 29:
    case 30:
    case 31:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 42:
    case 51:
    case 53:
        return 6;
    case 41:
    case 45:
    case 50:
        return 2;
    case 18:
    case 46:
        return 3;
    case 15:
    case 28:
    case 47:
        return 5;
    case 23:
    case 26:
    case 27:
        return 4;
    case 48:
        return 1;
    }

    return 0;
}

void HCEffectName_0(HcEffectNameWork* w, u8* a) {
    void** tiles;

    w->side = a[0];
    w->timer = 0;
    w->blinkInterval = 32;
    w->palette = LoadObjPalette(gBStatesPalette, 32);
    w->tiles2 = AllocSpriteFrameTiles(0x3C0);
    w->tiles3 = AllocSpriteFrameTiles(32);
    w->randomIndex = 0;
    w->visible = 1;

    switch (w->side) {
    case 1:
        w->x = 48;
        w->effect = gCardBattleState->soraHcEffect;
#ifdef VERSION_EU
        w->countUnit = GetHcEffectCountUnit(w, gCardBattleState->soraHcEffect);
#endif
        tiles = LANGSTR(gHcEffectDefs[gCardBattleState->soraHcEffect].sprites);
        UpdateSpriteFrameTiles(w->tiles2, tiles[gHcEffectDefs[gCardBattleState->soraHcEffect].spriteIndex], LANGSTR(gHcEffectDefs[gCardBattleState->soraHcEffect].tiles));
#ifdef VERSION_EU
        UpdateSpriteFrameTiles(w->tiles3, gHcEffectCountUnitSpritesByLanguage[gLanguage][w->countUnit], gHcEffectCountUnitTilesByLanguage[gLanguage]);
#else
        w->countUnit = GetHcEffectCountUnit(w, gCardBattleState->soraHcEffect);
        UpdateSpriteFrameTiles(w->tiles3, gUnk_09EF12C8[w->countUnit], gUnk_093FB954);
#endif

        if (gCardBattleState->soraHcEffect == 0) {
            w->visible = 0;
        }

        break;
    case 2:
        w->x = 162;
        w->effect = gCardBattleState->rikuHcEffect;
#ifdef VERSION_EU
        w->countUnit = GetHcEffectCountUnit(w, gCardBattleState->rikuHcEffect);
#endif
        tiles = LANGSTR(gHcEffectDefs[gCardBattleState->rikuHcEffect].sprites);
        UpdateSpriteFrameTiles(w->tiles2, tiles[gHcEffectDefs[gCardBattleState->rikuHcEffect].spriteIndex], LANGSTR(gHcEffectDefs[gCardBattleState->rikuHcEffect].tiles));
#ifdef VERSION_EU
        UpdateSpriteFrameTiles(w->tiles3, gHcEffectCountUnitSpritesByLanguage[gLanguage][w->countUnit], gHcEffectCountUnitTilesByLanguage[gLanguage]);
#else
        w->countUnit = GetHcEffectCountUnit(w, gCardBattleState->rikuHcEffect);
        UpdateSpriteFrameTiles(w->tiles3, gUnk_09EF12C8[w->countUnit], gUnk_093FB954);
#endif

        if (gCardBattleState->rikuHcEffect == 0) {
            w->visible = 0;
        }

        break;
    }

    w->tiles = LoadObjTiles(gUnk_08B25ADE, 0x360);
    w->countThousands = 0;
    w->countHundreds = 0;
    w->countTens = 0;
    w->countOnes = 0;
}

u8 HCEffectName_1(HcEffectNameWork* w, void* a) {
    u8 done;
    s32 div;
    CardBattleState* d;

    done = IsHcEffectNameShuffling(w);

    if (done != 0) {
#ifdef VERSION_EU
        SplitFourDigits((s16)gBtlWork->hcEffectCount, &w->countThousands);
#endif
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateHcEffectNameShuffle);
        return 1;
    }

    switch (w->side) {
    case 1:
        div = gHcEffectDefs[gBtlWork->hcEffect].count << 8;
        w->blinkInterval = (u32)(((s16)gBtlWork->hcEffectCount << 16) / div) >> 3;
        d = gCardBattleState;

        if (d->soraHcEffect == 0) {
            d->soraHcEffectReplaced = 0;
            return 0;
        }

        if (d->soraHcEffect != w->effect) {
            d->soraHcEffectReplaced = 0;
            return 0;
        }

        if (d->soraHcEffectReplaced == 1) {
            d->soraHcEffectReplaced = 0;
            return 0;
        }

        if ((s16)gBtlWork->hcEffectCount <= 0) {
            d->soraHcEffect = 0;
            gBtlWork->hcEffect = 0;
            d->soraHcEffectReplaced = 0;
            return 0;
        }

        SplitFourDigits((s16)gBtlWork->hcEffectCount, &w->countThousands);
        break;
    case 2:
        div = gHcEffectDefs[gRikuBtlWork->hcEffect].count << 8;
        w->blinkInterval = (u32)(((s16)gRikuBtlWork->hcEffectCount << 16) / div) >> 3;
        d = gCardBattleState;

        if (d->rikuHcEffect == 0) {
            d->rikuHcEffectReplaced = 0;
            return 0;
        }

        if (d->rikuHcEffect != w->effect) {
            d->rikuHcEffectReplaced = 0;
            return 0;
        }

        if (d->rikuHcEffectReplaced == 1) {
            d->rikuHcEffectReplaced = 0;
            return 0;
        }

        if ((s16)gRikuBtlWork->hcEffectCount <= 0) {
            d->rikuHcEffect = 0;
            gRikuBtlWork->hcEffect = 0;
            d->rikuHcEffectReplaced = 0;
            return 0;
        }

        SplitFourDigits((s16)gRikuBtlWork->hcEffectCount, &w->countThousands);
        break;
    }

    w->timer++;

    if ((s16)w->blinkInterval <= 2) {
        w->blinkInterval = 2;
    }

    if ((s16)w->timer >= (s16)w->blinkInterval) {
        w->visible ^= 1;
        w->timer = 0;
    }

    return 1;
}

u8 IsHcEffectNameShuffling(HcEffectNameWork* w) {
    if (w->side != 1) {
        if (w->side != 2) {
            return 0;
        }
    }

    if (w->effect != 37) {
        return 0;
    }

    return 1;
}

u8 UpdateHcEffectNameShuffle(HcEffectNameWork* w, void* a) {
    void** tiles;

    switch (w->side) {
    case 1:
        if (gCardBattleState->soraHcEffect != 37) {
            w->effect = gCardBattleState->soraHcEffect;

            if (gCardBattleState->soraHcEffect == 0) {
                gCardBattleState->soraHcEffectReplaced = 0;
                return 0;
            }

#ifdef VERSION_EU
            w->countUnit = GetHcEffectCountUnit(w, gCardBattleState->soraHcEffect);
#endif
            tiles = LANGSTR(gHcEffectDefs[gCardBattleState->soraHcEffect].sprites);
            UpdateSpriteFrameTiles(w->tiles2, tiles[gHcEffectDefs[gCardBattleState->soraHcEffect].spriteIndex],
                         LANGSTR(gHcEffectDefs[gCardBattleState->soraHcEffect].tiles));
#ifdef VERSION_EU
            UpdateSpriteFrameTiles(w->tiles3, gHcEffectCountUnitSpritesByLanguage[gLanguage][w->countUnit],
                         gHcEffectCountUnitTilesByLanguage[gLanguage]);
#else
            w->countUnit = GetHcEffectCountUnit(w, gCardBattleState->soraHcEffect);
            UpdateSpriteFrameTiles(w->tiles3, gUnk_09EF12C8[w->countUnit], gUnk_093FB954);
#endif
            SetTaskUpdate(a, (TaskUpdateFunc)HCEffectName_1);
        } else {
            u16 id = GetNextRandomHcEffect(&w->randomIndex);
            w->effect = id;
            tiles = LANGSTR(gHcEffectDefs[id].sprites);
            UpdateSpriteFrameTiles(w->tiles2, tiles[gHcEffectDefs[id].spriteIndex],
                         LANGSTR(gHcEffectDefs[id].tiles));
        }

        break;
    case 2:
        if (gCardBattleState->rikuHcEffect != 37) {
            w->effect = gCardBattleState->rikuHcEffect;

            if (gCardBattleState->rikuHcEffect == 0) {
                gCardBattleState->soraHcEffectReplaced = 0;
                return 0;
            }

#ifdef VERSION_EU
            w->countUnit = GetHcEffectCountUnit(w, gCardBattleState->rikuHcEffect);
#endif
            tiles = LANGSTR(gHcEffectDefs[gCardBattleState->rikuHcEffect].sprites);
            UpdateSpriteFrameTiles(w->tiles2, tiles[gHcEffectDefs[gCardBattleState->rikuHcEffect].spriteIndex],
                         LANGSTR(gHcEffectDefs[gCardBattleState->rikuHcEffect].tiles));
#ifdef VERSION_EU
            UpdateSpriteFrameTiles(w->tiles3, gHcEffectCountUnitSpritesByLanguage[gLanguage][w->countUnit],
                         gHcEffectCountUnitTilesByLanguage[gLanguage]);
#else
            w->countUnit = GetHcEffectCountUnit(w, gCardBattleState->rikuHcEffect);
            UpdateSpriteFrameTiles(w->tiles3, gUnk_09EF12C8[w->countUnit], gUnk_093FB954);
#endif
            SetTaskUpdate(a, (TaskUpdateFunc)HCEffectName_1);
        } else {
            u16 id = GetNextRandomHcEffect(&w->randomIndex);
            w->effect = id;
            tiles = LANGSTR(gHcEffectDefs[id].sprites);
            UpdateSpriteFrameTiles(w->tiles2, tiles[gHcEffectDefs[id].spriteIndex],
                         LANGSTR(gHcEffectDefs[id].tiles));
        }

        break;
    }

    return 1;
}

void HCEffectName_2(HcEffectNameWork* w) {
#ifdef VERSION_EU
    s32 pri;

    if (w->visible == 1) {
        pri = 0x410;
        DrawSprite(w->x, 0x90, 0, w->tiles2, w->palette, 0, pri, 10);
        DrawSprite(w->x, 0x8A, gUnk_09EE1538[15], w->tiles, w->palette, 0, pri, 10);
        DrawSprite(w->x + 8, 0x8A, gUnk_09EE1538[w->countTens + 4], w->tiles, w->palette, 0, pri, 10);
        DrawSprite(w->x + 16, 0x8A, gUnk_09EE1538[w->countOnes + 4], w->tiles, w->palette, 0, pri, 10);
        DrawSprite(w->x + 24, 0x8A, 0, w->tiles3, w->palette, 0, pri, 10);
        DrawSprite(w->x + 32, 0x8A, gUnk_09EE1538[14], w->tiles, w->palette, 0, pri, 10);
    }
#else
    if (w->visible == 1) {
        DrawSprite(w->x, 0x90, 0, w->tiles2, w->palette, 0, SPRITE_PRIORITY(1), 10);
        DrawSprite(w->x, 0x8A, gUnk_09EE1538[15], w->tiles, w->palette, 0, SPRITE_PRIORITY(1), 10);
        DrawSprite(w->x + 8, 0x8A, gUnk_09EE1538[w->countTens + 4], w->tiles, w->palette, 0, SPRITE_PRIORITY(1), 10);
        DrawSprite(w->x + 16, 0x8A, gUnk_09EE1538[w->countOnes + 4], w->tiles, w->palette, 0, SPRITE_PRIORITY(1), 10);
        DrawSprite(w->x + 24, 0x8A, 0, w->tiles3, w->palette, 0, SPRITE_PRIORITY(1), 10);
        DrawSprite(w->x + 32, 0x8A, gUnk_09EE1538[14], w->tiles, w->palette, 0, SPRITE_PRIORITY(1), 10);
    }
#endif
}

void HCEffectName_3(HcEffectNameWork* w) {
    ReleaseObjTiles(w->tiles2);
    ReleaseObjTiles(w->tiles);
    ReleaseObjTiles(w->tiles3);
    ReleaseObjPalette(w->palette);
    gCardBattleState->unk_0D8 = 0;
    gCardBattleState->unk_0E5 = 0;
    gCardBattleState->unk_0C8 = 256;
}

void NumberPlus_0(NumberPlusWork* w, NumberPlusArgs* args) {
    w->args = *args;
    w->tiles = LoadObjTiles(gUnk_090451C0, 128);
    w->palette = LoadObjPalette(gBStatesPalette, 32);
    w->x = w->args.x >> 8;
    w->y = (w->args.y >> 8) - 20;
    w->steps = 16;
    w->unk_29 = 0;
}

s32 NumberPlus_1(NumberPlusWork* w) {
    s32 v;

    v = w->y << 8;

    if (w->steps != 0) {
        ApproachValue(&v, w->args.y - 0x2800, w->steps);
        w->y = v >> 8;
        w->steps--;
        return 1;
    }

    return 0;
}

void NumberPlus_2(NumberPlusWork* w) {
    DrawSprite(w->x, w->y, gUnk_09EE91A8[0], w->tiles, w->palette, 0, SPRITE_FLAG_NO_MOSAIC, 0);
}

void NumberPlus_3(NumberPlusWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

Mode gModePremire = {
    "Mode_Premire",
    (ModeInitFunc)Mode_Premire_0,
    Mode_Premire_1,
    Mode_Premire_2,
};

#ifdef VERSION_EU
void* gHcEffectCountUnitTilesByLanguage[5] = { gUnk_093FB954, gUnkEu_094CE490, gUnkEu_094CE820, gUnkEu_094CE6F0, gUnkEu_094CE5C0 };
void** gHcEffectCountUnitSpritesByLanguage[5] = { gUnk_09EF12C8, gUnkEu_09F7C55C, gUnkEu_09F7C57C, gUnkEu_09F7C59C, gUnkEu_09F7C5BC };
#endif

TaskDesc gTaskDescHCEffectName = {
    "HCEffectName",
    (TaskInitFunc)HCEffectName_0,
    (TaskUpdateFunc)HCEffectName_1,
    (TaskDrawFunc)HCEffectName_2,
    (TaskDestroyFunc)HCEffectName_3,
    sizeof(HcEffectNameWork),
};

TaskDesc gTaskDescNumberPlus = {
    "NumberPlus",
    (TaskInitFunc)NumberPlus_0,
    (TaskUpdateFunc)NumberPlus_1,
    (TaskDrawFunc)NumberPlus_2,
    (TaskDestroyFunc)NumberPlus_3,
    sizeof(NumberPlusWork),
};
