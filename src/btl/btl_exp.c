/**
 * btl_exp.c
 * Experience Point Display
 */

#include "system_state.h"
#include "btl4.h"
#include "sprites_btl_hud.h"
#include "battle_work.h"
#include "game_state.h"
#include "obj.h"
#include "obj_api.h"
#include "player_progression_types.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "sprite_palettes.h"

void* GetExpDigitGfx(s32 digit, u8 leading) {
    switch (digit) {
    case 0:
        if (leading) {
            return gUnk_08B25E6E;
        }

        break;
    case 1:
        return gUnk_08B25E78;
    case 2:
        return gUnk_08B25E82;
    case 3:
        return gUnk_08B25E8C;
    case 4:
        return gUnk_08B25E96;
    case 5:
        return gUnk_08B25EA0;
    case 6:
        return gUnk_08B25EAA;
    case 7:
        return gUnk_08B25EB4;
    case 8:
        return gUnk_08B25EBE;
    case 9:
        return gUnk_08B25EC8;
    }

    return NULL;
}

void BtlExpSetNumber(BtlExpWork* work, u32 value) {
    void* d0;
    void* d1;
    void* d2;
    void* d3;
    u8 flag;

    d0 = GetExpDigitGfx(value / 10000, 0);
    work->gfx2[0] = d0;
    value %= 10000;
    flag = d0 != NULL;

    d1 = GetExpDigitGfx(value / 1000, flag);
    work->gfx2[1] = d1;
    value %= 1000;

    if (d1 != NULL) {
        flag = 1;
    }

    d2 = GetExpDigitGfx(value / 100, flag);
    work->gfx2[2] = d2;
    value %= 100;

    if (d2 != NULL) {
        flag = 1;
    }

    d3 = GetExpDigitGfx(value / 10, flag);
    work->gfx2[3] = d3;
    value %= 10;

    if (d3 != NULL) {
        flag = 1;
    }

#ifdef VERSION_JP
    work->gfx2[4] = gUnk_09EE1538[value + 4];
#else
    work->gfx2[4] = gUnk_09EE157C[value + 4];
#endif
    work->gfx2[5] = gUnk_08B25ED2;
}

void task_btl_exp_0(BtlExpWork* work) {
    s32 i;

    work->palette = LoadObjPalette(gBStatesPalette, 32);
#ifdef VERSION_EU
    work->tiles = AllocObjTiles(0xC0, gUnk_08B25EF0);
#else
    work->tiles = AllocObjTiles(0xA0, gUnk_08B25EF0);
#endif
    work->gfx = NULL;

    for (i = 0; i <= 5; i++) {
        work->tiles2[i] = AllocObjTiles(32, gUnk_08B25EF0);
        work->gfx2[i] = NULL;
    }

    work->timer = 0;
    work->level = gGameState.progression.level;
    work->lastExp = gGameState.progression.exp;
    work->state = 0;
    work->gainedExp = 0;
}

s32 task_btl_exp_1(BtlExpWork* work) {
    if (gBtlWork->flags & BTL_FLAG_FIELD_HIDDEN) {
        return 0;
    }

    if (work->level < gGameState.progression.level) {
        BtlExpSetNumber(work, gGameState.progression.level);

#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            work->gfx = gUnk_08B25E40;
            break;
        case LANGUAGE_FRENCH:
            work->gfx = gUnkEu_08B55CFE;
            break;
        case LANGUAGE_SPANISH:
            work->gfx = gUnkEu_08B55D18;
            break;
        case LANGUAGE_ITALIAN:
            work->gfx = gUnkEu_08B55D32;
            break;
        case LANGUAGE_GERMAN:
        default:
            work->gfx = gUnkEu_08B55D66;
            break;
        }
#else
        work->gfx = gUnk_08B25E40;
#endif
        work->timer = 0;
        work->state = 3;
        work->level = gGameState.progression.level;
        work->gainedExp = 0;
    }

    if (work->state != 3) {
        if (work->lastExp < gGameState.progression.exp) {
            work->gainedExp += gGameState.progression.exp - work->lastExp;
            BtlExpSetNumber(work, work->gainedExp);

#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                work->gfx = gUnk_08B25E54;
                break;
            case LANGUAGE_FRENCH:
                work->gfx = gUnk_08B25E54;
                break;
            case LANGUAGE_SPANISH:
                work->gfx = gUnk_08B25E54;
                break;
            case LANGUAGE_ITALIAN:
                work->gfx = gUnkEu_08B55D4C;
                break;
            case LANGUAGE_GERMAN:
            default:
                work->gfx = gUnkEu_08B55D80;
                break;
            }
#else
            work->gfx = gUnk_08B25E54;
#endif
            work->timer = 0;
            work->state = 1;
            work->lastExp = gGameState.progression.exp;
        }
    }

    switch (work->state) {
    case 0:
        break;
    case 3:
        if (work->timer > 100) {
            if (gGameState.progression.level > 98) {
                work->state = 0;
            } else {
                work->state = 2;
                BtlExpSetNumber(work, gGameState.progression.nextExp - gGameState.progression.exp);

#ifdef VERSION_EU
                switch (gLanguage) {
                case LANGUAGE_ENGLISH:
                    work->gfx = gUnk_08B25E5E;
                    break;
                case LANGUAGE_FRENCH:
                    work->gfx = gUnkEu_08B55D08;
                    break;
                case LANGUAGE_SPANISH:
                    work->gfx = gUnkEu_08B55D22;
                    break;
                case LANGUAGE_ITALIAN:
                    work->gfx = gUnkEu_08B55D3C;
                    break;
                case LANGUAGE_GERMAN:
                default:
                    work->gfx = gUnkEu_08B55D70;
                    break;
                }
#else
                work->gfx = gUnk_08B25E5E;
#endif
            }

            work->timer = 0;
            work->gainedExp = 0;
        } else {
            work->timer++;
        }

        break;
    case 1:
        if (work->timer > 60) {
            if (gGameState.progression.level > 98) {
                work->state = 0;
            } else {
                work->state = 2;
                BtlExpSetNumber(work, gGameState.progression.nextExp - gGameState.progression.exp);

#ifdef VERSION_EU
                switch (gLanguage) {
                case LANGUAGE_ENGLISH:
                    work->gfx = gUnk_08B25E5E;
                    break;
                case LANGUAGE_FRENCH:
                    work->gfx = gUnkEu_08B55D08;
                    break;
                case LANGUAGE_SPANISH:
                    work->gfx = gUnkEu_08B55D22;
                    break;
                case LANGUAGE_ITALIAN:
                    work->gfx = gUnkEu_08B55D3C;
                    break;
                case LANGUAGE_GERMAN:
                default:
                    work->gfx = gUnkEu_08B55D70;
                    break;
                }
#else
                work->gfx = gUnk_08B25E5E;
#endif
            }

            work->timer = 0;
            work->gainedExp = 0;
        } else {
            work->timer++;
        }

        break;
    case 2:
        if (work->timer > 100) {
            work->timer = 0;
            work->state = 0;
        } else {
            work->timer++;
        }

        break;
    }

    return 1;
}

void task_btl_exp_2(BtlExpWork* work) {
    s32 i;
    s16 x;
    u16 y;

    if (work->state != 0) {
        y = 40;
        x = 0;
        DrawSprite(0, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, x);

#ifdef VERSION_JP
        x = 32;
#else
        if (work->state == 2) {
#ifdef VERSION_EU
            x = 48;
#else
            x = 40;
#endif
        } else {
            x = 32;
        }
#endif

        for (i = 0; i <= 5; i++) {
            if (work->gfx2[i] != NULL) {
                DrawSprite(x, y, work->gfx2[i], work->tiles2[i], work->palette, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 0);
                x += 8;
            }
        }
    }
}

void task_btl_exp_3(BtlExpWork* work) {
    s32 i;

    for (i = 0; i < 6; i++) {
        ReleaseObjTiles(work->tiles2[i]);
    }

    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

TaskDesc gTaskDescBtlExp = {
    "task_btl_exp",
    (TaskInitFunc)task_btl_exp_0,
    (TaskUpdateFunc)task_btl_exp_1,
    (TaskDrawFunc)task_btl_exp_2,
    (TaskDestroyFunc)task_btl_exp_3,
    sizeof(BtlExpWork),
};
