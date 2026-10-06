/**
 * mode_premire.c
 * Enemy Card Effect Names and Level-Up Test
 */

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
#include "sprites_number_plus.h"
#include "battle_backgrounds.h"
#include "sprites_btl_hud.h"
#include "sprites_card.h"
#include "battle_work.h"
#include "card_api.h"
#include "card_label_data.h"
#include "mode.h"
#include <stddef.h>
#include "types.h"
#include "mode_premire.h"
#include "sprite_palettes.h"
#include "gba/io_reg.h"

static TaskPool sModePremireTasks;
#ifndef VERSION_EU
static u8 sUnk_02034AF4[4];
#endif

void Mode_Premire_0() {
    func_08085FB0();
    InitSoraDecks();
    SetBgMode2();
    SetupBg(3, 0, 12, 0);
    SetupBg(2, 2, 28, 10);
    SetBgSize(3, BGCNT_AFF512x512);
    LoadBgTiles(3, gBtlBgMonstroTiles, 0x4000);
    LoadBgPalette(3, gBtlBgMonstroPalette, 0x100);
#ifdef VERSION_EU
    LoadBgMapLz77(3, gBtlBgMonstroMap);
#else
    LoadBgMap(3, gBtlBgMonstroMap, 0x1000);
#endif
    SetBgAffine(3, 0, Q_8_8(1), Q_8_8(1), 0x10000, 0x16800);
    TaskPoolInit(&sModePremireTasks, 1);
    TaskCreate(&sModePremireTasks, &gTaskDescLevelUp, NULL);
}

void Mode_Premire_1() {
    TaskPoolUpdate(&sModePremireTasks);
    TaskPoolDraw(&sModePremireTasks);
}

void Mode_Premire_2() {
    TaskPoolDestroy(&sModePremireTasks);
}

u8 GetHcEffectCountUnit(HcEffectNameWork* work, u16 effect) {
    switch (effect) {
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

void HCEffectName_0(HcEffectNameWork* work, u8* arg) {
    void** tiles;

    work->side = arg[0];
    work->timer = 0;
    work->blinkInterval = 32;
    work->palette = LoadObjPalette(gBStatesPalette, sizeof(gBStatesPalette));
    work->tiles2 = AllocSpriteFrameTiles(0x3C0);
    work->tiles3 = AllocSpriteFrameTiles(32);
    work->randomIndex = 0;
    work->visible = 1;

    switch (work->side) {
    case 1:
        work->x = 48;
        work->effect = gCardBattleState->soraHcEffect;
#ifdef VERSION_EU
        work->countUnit = GetHcEffectCountUnit(work, gCardBattleState->soraHcEffect);
#endif
        tiles = LANGSTR(gHcEffectDefs[gCardBattleState->soraHcEffect].sprites);
        UpdateSpriteFrameTiles(work->tiles2, tiles[gHcEffectDefs[gCardBattleState->soraHcEffect].spriteIndex], LANGSTR(gHcEffectDefs[gCardBattleState->soraHcEffect].tiles));
#ifdef VERSION_EU
        UpdateSpriteFrameTiles(work->tiles3, gHcEffectCountUnitSpritesByLanguage[gLanguage][work->countUnit], gHcEffectCountUnitTilesByLanguage[gLanguage]);
#else
        work->countUnit = GetHcEffectCountUnit(work, gCardBattleState->soraHcEffect);
        UpdateSpriteFrameTiles(work->tiles3, gHcEffectCountUnitFrames[work->countUnit], gHcEffectCountUnitTiles);
#endif

        if (gCardBattleState->soraHcEffect == HC_EFFECT_NONE) {
            work->visible = 0;
        }

        break;
    case 2:
        work->x = 162;
        work->effect = gCardBattleState->rikuHcEffect;
#ifdef VERSION_EU
        work->countUnit = GetHcEffectCountUnit(work, gCardBattleState->rikuHcEffect);
#endif
        tiles = LANGSTR(gHcEffectDefs[gCardBattleState->rikuHcEffect].sprites);
        UpdateSpriteFrameTiles(work->tiles2, tiles[gHcEffectDefs[gCardBattleState->rikuHcEffect].spriteIndex], LANGSTR(gHcEffectDefs[gCardBattleState->rikuHcEffect].tiles));
#ifdef VERSION_EU
        UpdateSpriteFrameTiles(work->tiles3, gHcEffectCountUnitSpritesByLanguage[gLanguage][work->countUnit], gHcEffectCountUnitTilesByLanguage[gLanguage]);
#else
        work->countUnit = GetHcEffectCountUnit(work, gCardBattleState->rikuHcEffect);
        UpdateSpriteFrameTiles(work->tiles3, gHcEffectCountUnitFrames[work->countUnit], gHcEffectCountUnitTiles);
#endif

        if (gCardBattleState->rikuHcEffect == HC_EFFECT_NONE) {
            work->visible = 0;
        }

        break;
    }

    work->tiles = LoadObjTiles(gBtlExpNextTiles, sizeof(gBtlExpNextTiles));
    work->countThousands = 0;
    work->countHundreds = 0;
    work->countTens = 0;
    work->countOnes = 0;
}

u8 HCEffectName_1(HcEffectNameWork* work, void* task) {
    u8 done;
    s32 div;
    CardBattleState* state;

    done = IsHcEffectNameShuffling(work);

    if (done) {
#ifdef VERSION_EU
        SplitFourDigits(gBtlWork->hcEffectCount, &work->countThousands);
#endif
        SetTaskUpdate(task, (TaskUpdateFunc)UpdateHcEffectNameShuffle);
        return 1;
    }

    switch (work->side) {
    case 1:
        div = gHcEffectDefs[gBtlWork->hcEffect].count << 8;
        work->blinkInterval = (u32)(((s16)gBtlWork->hcEffectCount << 16) / div) >> 3;
        state = gCardBattleState;

        if (state->soraHcEffect == HC_EFFECT_NONE) {
            state->soraHcEffectReplaced = FALSE;
            return 0;
        }

        if (state->soraHcEffect != work->effect) {
            state->soraHcEffectReplaced = FALSE;
            return 0;
        }

        if (state->soraHcEffectReplaced == TRUE) {
            state->soraHcEffectReplaced = FALSE;
            return 0;
        }

        if ((s16)gBtlWork->hcEffectCount <= 0) {
            state->soraHcEffect = HC_EFFECT_NONE;
            gBtlWork->hcEffect = HC_EFFECT_NONE;
            state->soraHcEffectReplaced = FALSE;
            return 0;
        }

        SplitFourDigits(gBtlWork->hcEffectCount, &work->countThousands);
        break;
    case 2:
        div = gHcEffectDefs[gRikuBtlWork->hcEffect].count << 8;
        work->blinkInterval = (u32)(((s16)gRikuBtlWork->hcEffectCount << 16) / div) >> 3;
        state = gCardBattleState;

        if (state->rikuHcEffect == HC_EFFECT_NONE) {
            state->rikuHcEffectReplaced = FALSE;
            return 0;
        }

        if (state->rikuHcEffect != work->effect) {
            state->rikuHcEffectReplaced = FALSE;
            return 0;
        }

        if (state->rikuHcEffectReplaced == TRUE) {
            state->rikuHcEffectReplaced = FALSE;
            return 0;
        }

        if ((s16)gRikuBtlWork->hcEffectCount <= 0) {
            state->rikuHcEffect = HC_EFFECT_NONE;
            gRikuBtlWork->hcEffect = HC_EFFECT_NONE;
            state->rikuHcEffectReplaced = FALSE;
            return 0;
        }

        SplitFourDigits(gRikuBtlWork->hcEffectCount, &work->countThousands);
        break;
    }

    work->timer++;

    if ((s16)work->blinkInterval <= 2) {
        work->blinkInterval = 2;
    }

    if ((s16)work->timer >= (s16)work->blinkInterval) {
        work->visible ^= 1;
        work->timer = 0;
    }

    return 1;
}

u8 IsHcEffectNameShuffling(HcEffectNameWork* work) {
    if (work->side != 1) {
        if (work->side != 2) {
            return FALSE;
        }
    }

    if (work->effect != 37) {
        return FALSE;
    }

    return TRUE;
}

u8 UpdateHcEffectNameShuffle(HcEffectNameWork* work, void* task) {
    void** tiles;

    switch (work->side) {
    case 1:
        if (gCardBattleState->soraHcEffect != HC_EFFECT_RANDOM_FLUSH) {
            work->effect = gCardBattleState->soraHcEffect;

            if (gCardBattleState->soraHcEffect == HC_EFFECT_NONE) {
                gCardBattleState->soraHcEffectReplaced = FALSE;
                return 0;
            }

#ifdef VERSION_EU
            work->countUnit = GetHcEffectCountUnit(work, gCardBattleState->soraHcEffect);
#endif
            tiles = LANGSTR(gHcEffectDefs[gCardBattleState->soraHcEffect].sprites);
            UpdateSpriteFrameTiles(work->tiles2, tiles[gHcEffectDefs[gCardBattleState->soraHcEffect].spriteIndex],
                         LANGSTR(gHcEffectDefs[gCardBattleState->soraHcEffect].tiles));
#ifdef VERSION_EU
            UpdateSpriteFrameTiles(work->tiles3, gHcEffectCountUnitSpritesByLanguage[gLanguage][work->countUnit],
                         gHcEffectCountUnitTilesByLanguage[gLanguage]);
#else
            work->countUnit = GetHcEffectCountUnit(work, gCardBattleState->soraHcEffect);
            UpdateSpriteFrameTiles(work->tiles3, gHcEffectCountUnitFrames[work->countUnit], gHcEffectCountUnitTiles);
#endif
            SetTaskUpdate(task, (TaskUpdateFunc)HCEffectName_1);
        } else {
            u16 id = GetNextRandomHcEffect(&work->randomIndex);
            work->effect = id;
            tiles = LANGSTR(gHcEffectDefs[id].sprites);
            UpdateSpriteFrameTiles(work->tiles2, tiles[gHcEffectDefs[id].spriteIndex],
                         LANGSTR(gHcEffectDefs[id].tiles));
        }

        break;
    case 2:
        if (gCardBattleState->rikuHcEffect != HC_EFFECT_RANDOM_FLUSH) {
            work->effect = gCardBattleState->rikuHcEffect;

            if (gCardBattleState->rikuHcEffect == HC_EFFECT_NONE) {
                gCardBattleState->soraHcEffectReplaced = FALSE;
                return 0;
            }

#ifdef VERSION_EU
            work->countUnit = GetHcEffectCountUnit(work, gCardBattleState->rikuHcEffect);
#endif
            tiles = LANGSTR(gHcEffectDefs[gCardBattleState->rikuHcEffect].sprites);
            UpdateSpriteFrameTiles(work->tiles2, tiles[gHcEffectDefs[gCardBattleState->rikuHcEffect].spriteIndex],
                         LANGSTR(gHcEffectDefs[gCardBattleState->rikuHcEffect].tiles));
#ifdef VERSION_EU
            UpdateSpriteFrameTiles(work->tiles3, gHcEffectCountUnitSpritesByLanguage[gLanguage][work->countUnit],
                         gHcEffectCountUnitTilesByLanguage[gLanguage]);
#else
            work->countUnit = GetHcEffectCountUnit(work, gCardBattleState->rikuHcEffect);
            UpdateSpriteFrameTiles(work->tiles3, gHcEffectCountUnitFrames[work->countUnit], gHcEffectCountUnitTiles);
#endif
            SetTaskUpdate(task, (TaskUpdateFunc)HCEffectName_1);
        } else {
            u16 id = GetNextRandomHcEffect(&work->randomIndex);
            work->effect = id;
            tiles = LANGSTR(gHcEffectDefs[id].sprites);
            UpdateSpriteFrameTiles(work->tiles2, tiles[gHcEffectDefs[id].spriteIndex],
                         LANGSTR(gHcEffectDefs[id].tiles));
        }

        break;
    }

    return 1;
}

void HCEffectName_2(HcEffectNameWork* work) {
#ifdef VERSION_EU
    s32 pri;

    if (work->visible == 1) {
        pri = 0x410;
        DrawSprite(work->x, 0x90, NULL, work->tiles2, work->palette, NULL, pri, 10);
        DrawSprite(work->x, 0x8A, gBtlExpNextFrames[15], work->tiles, work->palette, NULL, pri, 10);
        DrawSprite(work->x + 8, 0x8A, gBtlExpNextFrames[work->countTens + 4], work->tiles, work->palette, NULL, pri, 10);
        DrawSprite(work->x + 16, 0x8A, gBtlExpNextFrames[work->countOnes + 4], work->tiles, work->palette, NULL, pri, 10);
        DrawSprite(work->x + 24, 0x8A, NULL, work->tiles3, work->palette, NULL, pri, 10);
        DrawSprite(work->x + 32, 0x8A, gBtlExpNextFrames[14], work->tiles, work->palette, NULL, pri, 10);
    }
#else
    if (work->visible == 1) {
        DrawSprite(work->x, 0x90, NULL, work->tiles2, work->palette, NULL, SPRITE_PRIORITY(1), 10);
        DrawSprite(work->x, 0x8A, gBtlExpNextFrames[15], work->tiles, work->palette, NULL, SPRITE_PRIORITY(1), 10);
        DrawSprite(work->x + 8, 0x8A, gBtlExpNextFrames[work->countTens + 4], work->tiles, work->palette, NULL, SPRITE_PRIORITY(1), 10);
        DrawSprite(work->x + 16, 0x8A, gBtlExpNextFrames[work->countOnes + 4], work->tiles, work->palette, NULL, SPRITE_PRIORITY(1), 10);
        DrawSprite(work->x + 24, 0x8A, NULL, work->tiles3, work->palette, NULL, SPRITE_PRIORITY(1), 10);
        DrawSprite(work->x + 32, 0x8A, gBtlExpNextFrames[14], work->tiles, work->palette, NULL, SPRITE_PRIORITY(1), 10);
    }
#endif
}

void HCEffectName_3(HcEffectNameWork* work) {
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles3);
    ReleaseObjPalette(work->palette);
    gCardBattleState->unk_0D8 = 0;
    gCardBattleState->unk_0E5 = 0;
    gCardBattleState->unk_0C8 = 256;
}

void NumberPlus_0(NumberPlusWork* work, NumberPlusArgs* args) {
    work->args = *args;
    work->tiles = LoadObjTiles(gNumberPlusTiles, sizeof(gNumberPlusTiles));
    work->palette = LoadObjPalette(gBStatesPalette, sizeof(gBStatesPalette));
    work->x = work->args.x >> 8;
    work->y = (work->args.y >> 8) - 20;
    work->steps = 16;
    work->unk_29 = 0;
}

s32 NumberPlus_1(NumberPlusWork* work) {
    s32 y;

    y = work->y << 8;

    if (work->steps != 0) {
        ApproachValue(&y, work->args.y - 0x2800, work->steps);
        work->y = y >> 8;
        work->steps--;
        return 1;
    }

    return 0;
}

void NumberPlus_2(NumberPlusWork* work) {
    DrawSprite(work->x, work->y, gNumberPlusFrames[0], work->tiles, work->palette, NULL, SPRITE_FLAG_NO_MOSAIC, 0);
}

void NumberPlus_3(NumberPlusWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

Mode gModePremire = {
    "Mode_Premire",
    (ModeInitFunc)Mode_Premire_0,
    Mode_Premire_1,
    Mode_Premire_2,
};

#ifdef VERSION_EU
void* gHcEffectCountUnitTilesByLanguage[5] = { gHcEffectCountUnitTiles, gHcEffectCountUnitFrenchTiles, gHcEffectCountUnitGermanTiles, gHcEffectCountUnitItalianTiles, gHcEffectCountUnitSpanishTiles };
void** gHcEffectCountUnitSpritesByLanguage[5] = { gHcEffectCountUnitFrames, gHcEffectCountUnitFrenchFrames, gHcEffectCountUnitSpanishFrames, gHcEffectCountUnitItalianFrames, gHcEffectCountUnitGermanFrames };
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
