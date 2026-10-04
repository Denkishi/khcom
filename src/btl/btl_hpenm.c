#include "system_state.h"
#include "btl2.h"
#include "sprites_btl_hud.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

void task_btl_hpenm_0(BtlHpenmWork* work) {
    work->tiles = AllocObjTiles(0x140, gBHpgagETiles);
    work->tiles2 = AllocObjTiles(0x80, gBHpgagETiles);
    work->tiles3 = AllocObjTiles(0x20, gBHpgagETiles);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    work->visible = 0;
    work->hpRatio = 0x100;
    work->actor = NULL;
    work->gaugeSize = 0;
    work->gaugeLayer = 0;
}

s32 task_btl_hpenm_1(BtlHpenmWork* work) {
    BtlObj* actor;

    if (gBtlWork->phase == 4) {
        return 0;
    }

    if (gBtlWork->flags & BTL_FLAG_HUM_BATTLE) {
        actor = gRikuBtlWork->actor;
        work->visible = 1;
    } else {
        if (gBtlWork->actor2 == NULL) {
            if (work->visible) {
                work->visible = 0;
            }

            return 1;
        }

        work->visible = 1;
        actor = gBtlWork->actor2;
    }

    if (actor->parent != NULL) {
        actor = actor->parent;
    }

    if (work->actor != actor) {
        work->actor = actor;
        work->displayHp = actor->hp;

        if (actor->maxHp <= 80) {
            work->gaugeSize = 0;
        } else if (actor->maxHp <= 160) {
            work->gaugeSize = 1;
        } else if (actor->maxHp <= 240) {
            work->gaugeSize = 2;
        } else if (actor->maxHp <= 320) {
            work->gaugeSize = 3;
        } else if (actor->maxHp <= 400) {
            work->gaugeSize = 4;
        } else if (actor->maxHp <= 480) {
            work->gaugeSize = 5;
        } else if (actor->maxHp <= 560) {
            work->gaugeSize = 6;
        } else {
            work->gaugeSize = 7;
        }
    } else if (work->displayHp < actor->hp) {
        work->displayHp += 5;

        if (work->displayHp > actor->hp) {
            work->displayHp = actor->hp;
        }
    } else if (work->displayHp > actor->hp) {
        work->displayHp -= 5;

        if (work->displayHp < actor->hp) {
            work->displayHp = actor->hp;
        }
    }

    if (work->displayHp <= 560) {
        work->gaugeLayer = 0;
    } else if (work->displayHp <= 1120) {
        work->gaugeLayer = 1;
    } else if (work->displayHp <= 1680) {
        work->gaugeLayer = 2;
    } else {
        work->gaugeLayer = 3;
    }

    switch (work->gaugeLayer) {
    case 3:
        work->hpRatio = ((work->displayHp - 1680) << 8) / 560;
        break;
    case 2:
        work->hpRatio = ((work->displayHp - 1120) << 8) / 560;
        break;
    case 1:
        work->hpRatio = ((work->displayHp - 560) << 8) / 560;
        break;
    case 0:
        if (work->gaugeSize <= 6) {
            work->hpRatio = (work->displayHp << 8) / actor->maxHp;
        } else {
            work->hpRatio = (work->displayHp << 8) / 560;
        }

        break;
    }

    return 1;
}

void task_btl_hpenm_2(BtlHpenmWork* work) {
    void* gfx;
    void* bar;
    s32 v;
    ObjAffine* aff;

    if (!work->visible) {
        return;
    }

    switch (work->gaugeLayer) {
    case 3:
#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
        case LANGUAGE_FRENCH:
            gfx = gBHpgagEFrame12Eu;
            break;
        case LANGUAGE_SPANISH:
            gfx = gBHpgagEFrame22Eu;
            break;
        case LANGUAGE_ITALIAN:
            gfx = gBHpgagEFrame31Eu;
            break;
        case LANGUAGE_GERMAN:
        default:
            gfx = gBHpgagEFrame40Eu;
            break;
        }

        bar = gBHpgagEFrame9Eu;
#else
        gfx = gBHpgagEFrame12;
        bar = gBHpgagEFrame9;
#endif
        break;
    case 2:
#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
        case LANGUAGE_FRENCH:
            gfx = gBHpgagEFrame11Eu;
            break;
        case LANGUAGE_SPANISH:
            gfx = gBHpgagEFrame21Eu;
            break;
        case LANGUAGE_ITALIAN:
            gfx = gBHpgagEFrame30Eu;
            break;
        case LANGUAGE_GERMAN:
        default:
            gfx = gBHpgagEFrame39Eu;
            break;
        }

        bar = gBHpgagEFrame8Eu;
#else
        gfx = gBHpgagEFrame11;
        bar = gBHpgagEFrame8;
#endif
        break;
    case 1:
#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
        case LANGUAGE_FRENCH:
            gfx = gBHpgagEFrame10Eu;
            break;
        case LANGUAGE_SPANISH:
            gfx = gBHpgagEFrame20Eu;
            break;
        case LANGUAGE_ITALIAN:
            gfx = gBHpgagEFrame29Eu;
            break;
        case LANGUAGE_GERMAN:
        default:
            gfx = gBHpgagEFrame38Eu;
            break;
        }

        bar = gBHpgagEFrame7Eu;
#else
        gfx = gBHpgagEFrame10;
        bar = gBHpgagEFrame7;
#endif
        break;
    case 0:
    default:
#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
        case LANGUAGE_FRENCH:
            switch (work->gaugeSize) {
            case 0:
            case 1:
                gfx = gBHpgagEFrame1Eu;
                break;
            case 2:
                gfx = gBHpgagEFrame2Eu;
                break;
            case 3:
                gfx = gBHpgagEFrame3Eu;
                break;
            case 4:
                gfx = gBHpgagEFrame4Eu;
                break;
            case 5:
                gfx = gBHpgagEFrame5Eu;
                break;
            case 6:
            default:
                gfx = gBHpgagEFrame6Eu;
                break;
            }

            break;
        case LANGUAGE_SPANISH:
            switch (work->gaugeSize) {
            case 0:
            case 1:
                gfx = gBHpgagEFrame14Eu;
                break;
            case 2:
                gfx = gBHpgagEFrame15Eu;
                break;
            case 3:
                gfx = gBHpgagEFrame16Eu;
                break;
            case 4:
                gfx = gBHpgagEFrame17Eu;
                break;
            case 5:
                gfx = gBHpgagEFrame18Eu;
                break;
            case 6:
            default:
                gfx = gBHpgagEFrame19Eu;
                break;
            }

            break;
        case LANGUAGE_ITALIAN:
            switch (work->gaugeSize) {
            case 0:
            case 1:
                gfx = gBHpgagEFrame23Eu;
                break;
            case 2:
                gfx = gBHpgagEFrame24Eu;
                break;
            case 3:
                gfx = gBHpgagEFrame25Eu;
                break;
            case 4:
                gfx = gBHpgagEFrame26Eu;
                break;
            case 5:
                gfx = gBHpgagEFrame27Eu;
                break;
            case 6:
            default:
                gfx = gBHpgagEFrame28Eu;
                break;
            }

            break;
        case LANGUAGE_GERMAN:
        default:
            switch (work->gaugeSize) {
            case 0:
            case 1:
                gfx = gBHpgagEFrame32Eu;
                break;
            case 2:
                gfx = gBHpgagEFrame33Eu;
                break;
            case 3:
                gfx = gBHpgagEFrame34Eu;
                break;
            case 4:
                gfx = gBHpgagEFrame35Eu;
                break;
            case 5:
                gfx = gBHpgagEFrame36Eu;
                break;
            case 6:
            default:
                gfx = gBHpgagEFrame37Eu;
                break;
            }

            break;
        }

        bar = gBHpgagEFrame0Eu;
#else
        switch (work->gaugeSize) {
        case 0:
        case 1:
            gfx = gBHpgagEFrame1;
            break;
        case 2:
            gfx = gBHpgagEFrame2;
            break;
        case 3:
            gfx = gBHpgagEFrame3;
            break;
        case 4:
            gfx = gBHpgagEFrame4;
            break;
        case 5:
            gfx = gBHpgagEFrame5;
            break;
        case 6:
            gfx = gBHpgagEFrame6;
            break;
        default:
            gfx = gBHpgagEFrame6;
            break;
        }

        bar = gBHpgagEFrame0;
#endif
        break;
    }

    DrawSprite(236, 2, gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 3);
#ifdef VERSION_EU
    DrawSprite(236, 2, gBHpgagEFrame13Eu, work->tiles3, work->palette, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 1);
#else
    DrawSprite(236, 2, gBHpgagEFrame13, work->tiles3, work->palette, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 1);
#endif

    switch (work->gaugeSize) {
    case 0:
    case 1:
        v = (work->hpRatio * 72) >> 8;
        break;
    case 2:
        v = (work->hpRatio * 109) >> 8;
        break;
    case 3:
        v = (work->hpRatio * 146) >> 8;
        break;
    case 4:
        v = (work->hpRatio * 182) >> 8;
        break;
    case 5:
        v = (work->hpRatio * 219) >> 8;
        break;
    case 6:
        v = work->hpRatio;
        break;
    default:
        v = work->hpRatio;
        break;
    }

    v *= 2;

    if (work->displayHp > 0) {
        if (v <= 9) {
            v = 10;
        }

        if (v > 0x100) {
            aff = AllocObjAffine(0, v, 0x100, 1);
        } else {
            aff = AllocObjAffine(0, v, 0x100, 0);
        }

        DrawSprite(217, 6, bar, work->tiles2, work->palette, aff, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 2);
    }
}

void task_btl_hpenm_3(BtlHpenmWork* work) {
    ReleaseObjTiles(work->tiles3);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

TaskDesc gTaskDescBtlHpenm = {
    "task_btl_hpenm",
    (TaskInitFunc)task_btl_hpenm_0,
    (TaskUpdateFunc)task_btl_hpenm_1,
    (TaskDrawFunc)task_btl_hpenm_2,
    (TaskDestroyFunc)task_btl_hpenm_3,
    sizeof(BtlHpenmWork),
};
