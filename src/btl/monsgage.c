#include "system_state.h"
#include "monsgage.h"
#include "obj_api.h"
#include "game.h"
#include "sprites_btl_hud.h"
#include "battle_work.h"
#include "obj.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"

#ifdef VERSION_EU
void* eu_0805E924(const void* strings) {
    void* const* s = strings;

    switch (gLanguage) {
    case LANGUAGE_ITALIAN:
        return s[3];
    case LANGUAGE_FRENCH:
        return s[1];
    case LANGUAGE_SPANISH:
        return s[4];
    case LANGUAGE_GERMAN:
        return s[2];
    case LANGUAGE_ENGLISH:
    default:
        return s[0];
    }
}

void* eu_0805E968(const void* text) {
    void* const* s = text;

    switch (gLanguage) {
    case LANGUAGE_ITALIAN:
        return s[3];
    case LANGUAGE_FRENCH:
        return s[1];
    case LANGUAGE_SPANISH:
        return s[4];
    case LANGUAGE_GERMAN:
        return s[2];
    case LANGUAGE_ENGLISH:
    default:
        return s[0];
    }
}

s32 eu_0805E9AC(const void* text) {
    const u16* s = text;

    switch (gLanguage) {
    case LANGUAGE_ITALIAN:
        return s[13];
    case LANGUAGE_FRENCH:
        return s[11];
    case LANGUAGE_SPANISH:
        return s[14];
    case LANGUAGE_GERMAN:
        return s[12];
    case LANGUAGE_ENGLISH:
    default:
        return s[10];
    }
}
#endif

void task_monsgage_0(MonsgageWork* work) {
    work->tiles = AllocObjTiles(0x200, gUnk_08B255B4);
    work->tiles2 = AllocObjTiles(0x80, gUnk_08B255B4);
    work->palette = LoadObjPalette(gBStatesPalette, 32);
    work->shownValue = 0;
    work->value = 0;
    work->gfx = gUnk_08B2556C;
    work->gfx2 = gUnk_08B2557C;
    work->timer = 0;
    work->state = 0;
    work->visible = 1;
}

s32 task_monsgage_1(MonsgageWork* work) {
    if (gBtlWork->phase != 0) {
        if (gBtlWork->phase == 4) {
            return 0;
        }

        switch (work->state) {
        case 0:
            if (work->timer == 0) {
                work->visible = 1;
                work->gfx2 = gUnk_08B2557C;
            }

#ifdef VERSION_EU
            if (gBtlWork->flags & BTL_FLAG_ENEMY_DEFEATED) {
                gBtlWork->flags &= ~BTL_FLAG_ENEMY_DEFEATED;
                work->value += 20;

                if (work->value > 255) {
                    work->value = 256;
                    work->state = 2;
                    work->timer = 0;
                    break;
                }
            } else if (work->timer > 120) {
                work->state = 1;
                work->timer = 0;
                break;
            }

            work->timer++;
#else
            if (work->timer > 120) {
                work->state = 1;
                work->timer = 0;
            } else {
                work->timer++;
            }
#endif

            break;
        case 1:
            if (work->timer == 0) {
                work->gfx2 = gUnk_08B25586;
            }

            if (work->timer % 8 < 4) {
                work->visible = 1;
            } else {
                work->visible = 0;
            }

            if ((work->timer % 4) == 0) {
                work->value--;

                if (work->value < 0) {
                    work->value = 0;
                }
            }

            if (gBtlWork->flags & BTL_FLAG_ENEMY_DEFEATED) {
                gBtlWork->flags &= ~BTL_FLAG_ENEMY_DEFEATED;
                work->timer = 0;
#ifdef VERSION_EU
                work->value += 20;
#else
                work->value += 25;
#endif

                if (work->value <= 255) {
                    work->state = 0;
                } else {
                    work->value = 256;
                    work->state = 2;
                }
            } else {
                work->timer++;
            }

            break;
        case 2:
            if (work->timer == 0) {
                work->gfx2 = gUnk_08B25590;
                work->gfx = gUnk_08B2559A;
                gBtlWork->flags |= BTL_FLAG_STOP_SPAWNING;
                gBtlWork->flags |= 0x100000;
            }

            if (work->timer % 8 < 4) {
                work->visible = 1;
            } else {
                work->visible = 0;
            }

            if (work->timer > 99 && gBtlWork->enemyCount == 0) {
                gBtlWork->flags |= BTL_FLAG_BATTLE_OVER;
            }

            work->timer++;
            break;
        }

        work->shownValue += (work->value - work->shownValue) >> 2;
    }

    return 1;
}

void task_monsgage_2(MonsgageWork* work) {
    ObjAffine* affine;

    if (gBtlWork->phase != 0) {
        DrawSprite(172, 12, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 3);

        if (work->visible != 0) {
            if (work->shownValue * 2 > 4) {
                if (work->shownValue * 2 > 256) {
                    affine = AllocObjAffine(0, work->shownValue * 2, 256, 1);
                } else {
                    affine = AllocObjAffine(0, work->shownValue * 2, 256, 0);
                }

                DrawSprite(174, 16, work->gfx2, work->tiles2, work->palette, affine, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 2);
            }
        }
    }
}

void task_monsgage_3(MonsgageWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette);
}

TaskDesc gTaskDescMonsgage = {
    "task_monsgage",
    (TaskInitFunc)task_monsgage_0,
    (TaskUpdateFunc)task_monsgage_1,
    (TaskDrawFunc)task_monsgage_2,
    (TaskDestroyFunc)task_monsgage_3,
    sizeof(MonsgageWork),
};
