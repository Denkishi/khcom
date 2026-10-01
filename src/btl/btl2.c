#include "system_state.h"
#include "display.h"
#include "m4a_song.h"
#include "btl2.h"
#include "gba/keys.h"
#include "sprites_btl.h"
#include "sprites_btl_hud.h"
#include "fade.h"
#include "songs.h"
#include <stdlib.h>
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "bg_animation_data.h"
#include "engine_math.h"
#include "game_state.h"
#include "key.h"
#include "m4a_catalog_data.h"
#include "obj.h"
#include "obj_api.h"
#include "player_progression_types.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

void task_btl_shadow_0(BtlShadowWork* work, BtlObj* actor) {
    work->actor = actor;

    if (actor->flags & BTLOBJ_FLAG_SMALL_SHADOW) {
        work->tiles = LoadObjTiles(gUnk_08B22CE4, 0x200);
        work->gfx = gUnk_08B22CBC;
    } else if (actor->flags & BTLOBJ_FLAG_LARGE_SHADOW) {
        work->tiles = LoadObjTiles(gUnk_08B22EFE, 0x140);
        work->gfx = gUnk_08B22EE4;
    } else {
        work->tiles = LoadObjTiles(gUnk_08B22BBC, 0x100);
        work->gfx = gUnk_08B22BA8;
    }

    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
}

s32 task_btl_shadow_1() {
    return 1;
}

void task_btl_shadow_2(BtlShadowWork* work) {
    BtlObj* actor = work->actor;
    s16 x;
    s16 y;
    u16 anim;
    ObjAffine* aff;

    if (actor->shadowPriority != 0) {
        if (!(actor->flags & 0x0000000402000000)) {
            anim = GetBattleSpritePriorityFlags(actor->y);

            if (actor->z >= 0 && gBtlWork->scale == 0x100) {
                aff = 0;
            } else {
                s32 sc = 0x100 - (actor->groundZ - actor->z) / 128;
                sc = (gBtlWork->scale * sc) >> 8;

                if (sc <= 127) {
                    sc = 128;
                }

                aff = AllocObjAffine(0, sc, sc, sc > 0x100);
            }

            WorldToScreen(&x, &y, actor->x, actor->y, actor->groundZ);
            DrawSprite(x, y, work->gfx, work->tiles, work->palette, aff, anim, actor->shadowPriority);
        }
    }
}

void task_btl_shadow_3(BtlShadowWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_btl_hpply_0(BtlHpplyWork* work) {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        work->palette = LoadObjPalette(gRikuPalette, 0x20);
        work->tiles = AllocObjTiles(0x280, gUnk_08B21438);
        work->gfx = gUnk_08B213F0;
        AnimInit(&work->anim, gUnk_09EE12C8, gUnk_09EE12BC);
    } else {
        work->palette = LoadObjPalette(gSoraPalette, 0x20);
        work->tiles = AllocObjTiles(0x280, gUnk_08B20D6E);
        work->gfx = gUnk_08B20D20;
        AnimInit(&work->anim, gUnk_09EE12B0, gUnk_09EE12A4);
    }

    work->palette2 = LoadObjPalette(gBStatesPalette, 0x20);
    work->tiles2 = AllocObjTiles(0x280, gBHpgagTiles);
    work->tiles3 = AllocObjTiles(0x120, gBHpgagTiles);
    work->tiles4 = AllocObjTiles(0x80, gBHpgagTiles);
    work->gfx2 = gBHpgagFrame1;
    AnimInit(&work->anim2, gBHpgagAnims, gBHpgagFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);

    if (gBtlWork->actor->maxHp <= 40) {
        work->gaugeSize = 0;
        work->gaugeMode = 0;
    } else if (gBtlWork->actor->maxHp <= 80) {
        work->gaugeSize = 1;
        work->gaugeMode = 0;
    } else if (gBtlWork->actor->maxHp <= 120) {
        work->gaugeSize = 2;
        work->gaugeMode = 0;
    } else if (gBtlWork->actor->maxHp <= 160) {
        work->gaugeSize = 3;
        work->gaugeMode = 0;
    } else if (gBtlWork->actor->maxHp <= 200) {
        work->gaugeSize = 4;
        work->gaugeMode = 0;
    } else if (gBtlWork->actor->maxHp <= 240) {
        work->gaugeSize = 5;
        work->gaugeMode = 0;
    } else if (gBtlWork->actor->maxHp <= 280) {
        work->gaugeSize = 6;
        work->gaugeMode = 0;
    } else if (gBtlWork->actor->maxHp <= 320) {
        work->gaugeSize = 0;
        work->gaugeMode = 1;
    } else if (gBtlWork->actor->maxHp <= 360) {
        work->gaugeSize = 1;
        work->gaugeMode = 1;
    } else if (gBtlWork->actor->maxHp <= 400) {
        work->gaugeSize = 2;
        work->gaugeMode = 1;
    } else if (gBtlWork->actor->maxHp <= 440) {
        work->gaugeSize = 3;
        work->gaugeMode = 1;
    } else if (gBtlWork->actor->maxHp <= 480) {
        work->gaugeSize = 4;
        work->gaugeMode = 1;
    } else if (gBtlWork->actor->maxHp <= 520) {
        work->gaugeSize = 5;
        work->gaugeMode = 1;
    } else if (gBtlWork->actor->maxHp <= 560) {
        work->gaugeSize = 6;
        work->gaugeMode = 1;
    } else {
        work->gaugeSize = 6;
        work->gaugeMode = 1;
    }

    if (work->gaugeMode == 0) {
        switch (work->gaugeSize) {
        case 0:
        case 1:
            AnimStart(&work->anim2, 1, ANIM_FLAG_LOOP);
            break;
        case 2:
            AnimStart(&work->anim2, 3, ANIM_FLAG_LOOP);
            break;
        case 3:
            AnimStart(&work->anim2, 5, ANIM_FLAG_LOOP);
            break;
        case 4:
            AnimStart(&work->anim2, 7, ANIM_FLAG_LOOP);
            break;
        case 5:
            AnimStart(&work->anim2, 9, ANIM_FLAG_LOOP);
            break;
        case 6:
            AnimStart(&work->anim2, 11, ANIM_FLAG_LOOP);
            break;
        default:
            AnimStart(&work->anim2, 11, ANIM_FLAG_LOOP);
            break;
        }

        work->gfx3 = 0;
    } else {
        AnimStart(&work->anim2, 11, ANIM_FLAG_LOOP);

        switch (work->gaugeSize) {
        case 0:
            work->gfx3 = gBHpgagFrame19;
            break;
        case 1:
            work->gfx3 = gBHpgagFrame20;
            break;
        case 2:
            work->gfx3 = gBHpgagFrame21;
            break;
        case 3:
            work->gfx3 = gBHpgagFrame22;
            break;
        case 4:
            work->gfx3 = gBHpgagFrame23;
            break;
        case 5:
            work->gfx3 = gBHpgagFrame24;
            break;
        case 6:
            work->gfx3 = gBHpgagFrame25;
            break;
        default:
            work->gfx3 = gBHpgagFrame25;
            break;
        }
    }

    work->hpRatio = 0x100;
    work->firstUpdate = 1;
    work->unk_5C = 1;
    work->timer = 0;
    work->prevHp = 0;
    work->displayHp = 0;
    work->alarmPlaying = 0;
}

s32 task_btl_hpply_1(BtlHpplyWork* work) {
    BtlObj* actor;
    s32 flag;

    actor = gBtlWork->actor;

    if (actor == NULL) {
        return 0;
    }

    if (gBtlWork->flags & BTL_FLAG_FIELD_HIDDEN) {
        return 0;
    }

    if (work->gaugeMode != 1 && work->hpRatio <= 63) {
        flag = 1;
    } else {
        flag = 0;
    }

    if (actor->hp < work->prevHp) {
        work->timer = 44;
    }

    if (work->timer != 0) {
        AnimChange(&work->anim, 1, ANIM_FLAG_LOOP);
        work->timer--;
    } else if (flag != 0) {
        AnimChange(&work->anim, 2, ANIM_FLAG_LOOP);
    } else {
        AnimChange(&work->anim, 0, ANIM_FLAG_LOOP);
    }

    if (work->firstUpdate != 0) {
        work->firstUpdate = 0;
        work->displayHp = actor->hp;
    } else if (work->displayHp < actor->hp) {
        work->displayHp += 3;

        if (work->displayHp > actor->hp) {
            work->displayHp = actor->hp;
        }
    } else if (work->displayHp > actor->hp) {
        work->displayHp -= 3;

        if (work->displayHp < actor->hp) {
            work->displayHp = actor->hp;
        }
    }

    if (work->gaugeMode == 1) {
        if (work->displayHp <= 280) {
            work->gaugeMode = 2;
        }
    } else if (work->gaugeMode == 2) {
        if (work->displayHp > 280) {
            work->gaugeMode = 1;
        }
    }

    switch (work->gaugeMode) {
    case 0:
        work->hpRatio = (work->displayHp << 8) / actor->maxHp;
        break;
    case 1:
        work->hpRatio = ((work->displayHp - 280) << 8) / (actor->maxHp - 280);
        break;
    case 2:
        work->hpRatio = (work->displayHp << 8) / 280;
        break;
    }

    if (flag != 0) {
        if (work->alarmPlaying == 0) {
            work->alarmPlaying = 1;
            m4aSongNumStart(SONG_SYS_ALART);
        }

        if (work->gaugeMode == 0) {
            switch (work->gaugeSize) {
            case 0:
            case 1:
                AnimChange(&work->anim2, 2, ANIM_FLAG_LOOP);
                break;
            case 2:
                AnimChange(&work->anim2, 4, ANIM_FLAG_LOOP);
                break;
            case 3:
                AnimChange(&work->anim2, 6, ANIM_FLAG_LOOP);
                break;
            case 4:
                AnimChange(&work->anim2, 8, ANIM_FLAG_LOOP);
                break;
            case 5:
                AnimChange(&work->anim2, 10, ANIM_FLAG_LOOP);
                break;
            case 6:
                AnimChange(&work->anim2, 12, ANIM_FLAG_LOOP);
                break;
            default:
                AnimChange(&work->anim2, 12, ANIM_FLAG_LOOP);
                break;
            }
        } else {
            AnimChange(&work->anim2, 12, ANIM_FLAG_LOOP);
        }
    } else {
        if (work->gaugeMode == 0) {
            switch (work->gaugeSize) {
            case 0:
            case 1:
                AnimChange(&work->anim2, 1, ANIM_FLAG_LOOP);
                break;
            case 2:
                AnimChange(&work->anim2, 3, ANIM_FLAG_LOOP);
                break;
            case 3:
                AnimChange(&work->anim2, 5, ANIM_FLAG_LOOP);
                break;
            case 4:
                AnimChange(&work->anim2, 7, ANIM_FLAG_LOOP);
                break;
            case 5:
                AnimChange(&work->anim2, 9, ANIM_FLAG_LOOP);
                break;
            case 6:
                AnimChange(&work->anim2, 11, ANIM_FLAG_LOOP);
                break;
            default:
                AnimChange(&work->anim2, 11, ANIM_FLAG_LOOP);
                break;
            }
        } else {
            AnimChange(&work->anim2, 11, ANIM_FLAG_LOOP);
        }

        if (work->alarmPlaying != 0) {
            work->alarmPlaying = 0;
            m4aSongNumStop(SONG_SYS_ALART);
        }
    }

    work->gfx = AnimUpdate(&work->anim);
    work->gfx2 = AnimUpdate(&work->anim2);
    work->prevHp = actor->hp;
    return 1;
}

void task_btl_hpply_2(BtlHpplyWork* work) {
    s32 v;
    ObjAffine* aff;

    DrawSprite(4, 2, work->gfx, work->tiles, work->palette, 0, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 1);

    switch (work->gaugeMode) {
    case 0:
        DrawSprite(4, 2, work->gfx2, work->tiles2, work->palette2, 0, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 4);
        break;
    case 1:
        DrawSprite(4, 2, gBHpgagFrame27, work->tiles2, work->palette2, 0, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 4);
        DrawSprite(4, 2, work->gfx3, work->tiles3, work->palette2, 0, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 3);
        break;
    case 2:
        DrawSprite(4, 2, work->gfx2, work->tiles2, work->palette2, 0, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 4);
        DrawSprite(4, 2, work->gfx3, work->tiles3, work->palette2, 0, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 5);
        break;
    }

    switch (work->gaugeMode) {
    case 2:
        v = work->hpRatio;
        break;
    case 0:
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

        break;
    case 1:
    default:
        switch (work->gaugeSize) {
        case 0:
            v = (work->hpRatio * 36) >> 8;
            break;
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

        if (work->gaugeMode == 1) {
            DrawSprite(31, 9, gBHpgagFrame26, work->tiles4, work->palette2, aff, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 2);
        } else {
            DrawSprite(31, 6, gBHpgagFrame0, work->tiles4, work->palette2, aff, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 2);
        }
    }
}

void task_btl_hpply_3(BtlHpplyWork* work) {
    m4aSongNumStop(SONG_SYS_ALART);
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles3);
    ReleaseObjTiles(work->tiles4);
    ReleaseObjPalette(work->palette2);
    ReleaseObjPalette(work->palette);
}

void task_btl_hpenm_0(BtlHpenmWork* work) {
    work->tiles = AllocObjTiles(0x140, gBHpgagETiles);
    work->tiles2 = AllocObjTiles(0x80, gBHpgagETiles);
    work->tiles3 = AllocObjTiles(0x20, gBHpgagETiles);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    work->visible = 0;
    work->hpRatio = 0x100;
    work->actor = 0;
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
            if (work->visible != 0) {
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

    if (work->visible == 0) {
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

    DrawSprite(236, 2, gfx, work->tiles, work->palette, 0, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 3);
#ifdef VERSION_EU
    DrawSprite(236, 2, gBHpgagEFrame13Eu, work->tiles3, work->palette, 0, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 1);
#else
    DrawSprite(236, 2, gBHpgagEFrame13, work->tiles3, work->palette, 0, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 1);
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

void task_btl_pause_0(BtlPauseWork* work) {
#ifdef VERSION_EU
    void** p;

    work->palette = LoadObjPalette(gBStatesPalette, 0x20);

    if (gLanguage <= LANGUAGE_GERMAN) {
        work->tiles = LoadObjTiles(gUnk_08B1E7F4, 0x180);
        p = gUnk_09EE115C;
    } else {
        work->tiles = LoadObjTiles(gUnkEu_08B51BA8, 0x180);
        p = gUnkEu_09F5C1FC;
    }

    work->gfx = p[0];
    work->gfx2 = p[1];
#else
    work->tiles = LoadObjTiles(gUnk_08B1E7F4, 0x180);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    work->gfx = gUnk_09EE115C[0];
    work->gfx2 = gUnk_09EE115C[1];
#endif
    work->visible = 0;
    work->steps = 0;
    work->unk_26 = 0;
    gBtlWork->flags |= BTL_FLAG_PAUSE_DISABLED;
}

s32 task_btl_pause_1(BtlPauseWork* work) {
    s32 paused;

    if (GetKeysPressed() & START_BUTTON) {
        if (!(gBtlWork->flags & BTL_FLAG_PAUSE_DISABLED)) {
            gBtlWork->paused = gBtlWork->paused == 0 ? 1 : 0;
        }
    }

    paused = gBtlWork->paused;

    if (paused != 0) {
        if (work->visible == 0) {
            FadeSetPaused(1);
            work->visible = 1;
            work->x = -0x4000;
            work->y = 0x5000;
            work->x2 = 0x13000;
            work->y2 = 0x5000;
            work->steps = 14;
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, 0xFF, 0x80);
        m4aMPlayVolumeControl(&gMPlayInfo1, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo2, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo3, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo4, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo5, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo6, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo7, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo8, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo9, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo10, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo11, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo12, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo16, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo17, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo18, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo19, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo20, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo21, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo22, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo23, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo24, 0xFF, 0);
        m4aMPlayVolumeControl(&gMPlayInfo25, 0xFF, 0);
        } else {
            ApproachValue(&work->x, 0x7800, work->steps);
            ApproachValue(&work->x2, 0x7800, work->steps);

            if (work->steps > 1) {
                work->steps--;
            }
        }
    } else if (work->visible != 0) {
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo1, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo2, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo3, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo4, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo5, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo6, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo7, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo8, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo9, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo10, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo11, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo12, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo16, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo17, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo18, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo19, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo20, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo21, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo22, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo23, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo24, 0xFF, 0x100);
        m4aMPlayVolumeControl(&gMPlayInfo25, 0xFF, 0x100);
        work->visible = paused;
        FadeSetPaused(0);
    }

    return 1;
}

void task_btl_pause_2(BtlPauseWork* work) {
    if (work->visible != 0) {
        DrawSprite(work->x >> 8, work->y >> 8, work->gfx, work->tiles, work->palette, 0, 0, 0);
        DrawSprite(work->x2 >> 8, work->y2 >> 8, work->gfx2, work->tiles, work->palette, 0, 0, 0);
    }
}

void task_btl_pause_3(BtlPauseWork* work) {
    FadeSetPaused(0);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_btl_pop_0(BtlPopWork* work, BtlPremireSrc* src) {
#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        switch (src->kind) {
        case 0:
            work->tiles = LoadObjTiles(gUnkEu_08B4A794, 0x100);
            AnimInit(&work->anim, gUnk_09EE11C0, gUnk_09EE11BC);
            break;
        case 2:
            work->tiles = LoadObjTiles(gUnkEu_08B4A680, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5BE10, gUnkEu_09F5BE0C);
            break;
        case 9:
            work->tiles = LoadObjTiles(gUnkEu_08B4A8AE, 0x180);
            AnimInit(&work->anim, gUnk_09EE11C8, gUnk_09EE11C4);
            break;
        case 10:
            work->tiles = LoadObjTiles(gUnk_08B1F13A, 0x140);
            AnimInit(&work->anim, gUnk_09EE11D0, gUnk_09EE11CC);
            break;
        default:
            work->tiles = LoadObjTiles(gUnkEu_08B4A680, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5BE10, gUnkEu_09F5BE0C);
            break;
        }

        break;
    case LANGUAGE_FRENCH:
        switch (src->kind) {
        case 0:
            work->tiles = LoadObjTiles(gUnkEu_08B51368, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1C0, gUnkEu_09F5C1BC);
            break;
        case 2:
            work->tiles = LoadObjTiles(gUnkEu_08B517B8, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1E0, gUnkEu_09F5C1DC);
            break;
        case 9:
            work->tiles = LoadObjTiles(gUnkEu_08B4A8AE, 0x180);
            AnimInit(&work->anim, gUnk_09EE11C8, gUnk_09EE11C4);
            break;
        case 10:
            work->tiles = LoadObjTiles(gUnkEu_08B50F18, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1A0, gUnkEu_09F5C19C);
            break;
        default:
            work->tiles = LoadObjTiles(gUnkEu_08B517B8, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1E0, gUnkEu_09F5C1DC);
            break;
        }

        break;
    case LANGUAGE_GERMAN:
        switch (src->kind) {
        case 0:
            work->tiles = LoadObjTiles(gUnkEu_08B516A4, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1D8, gUnkEu_09F5C1D4);
            break;
        case 2:
            work->tiles = LoadObjTiles(gUnkEu_08B51A74, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1F8, gUnkEu_09F5C1F4);
            break;
        case 9:
            work->tiles = LoadObjTiles(gUnkEu_08B50D82, 0x180);
            AnimInit(&work->anim, gUnkEu_09F5C198, gUnkEu_09F5C194);
            break;
        case 10:
            work->tiles = LoadObjTiles(gUnkEu_08B51254, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1B8, gUnkEu_09F5C1B4);
            break;
        default:
            work->tiles = LoadObjTiles(gUnkEu_08B51A74, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1F8, gUnkEu_09F5C1F4);
            break;
        }

        break;
    case LANGUAGE_ITALIAN:
        switch (src->kind) {
        case 0:
            work->tiles = LoadObjTiles(gUnkEu_08B51590, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1D0, gUnkEu_09F5C1CC);
            break;
        case 2:
            work->tiles = LoadObjTiles(gUnkEu_08B519E0, 0x80);
            AnimInit(&work->anim, gUnkEu_09F5C1F0, gUnkEu_09F5C1EC);
            break;
        case 9:
            work->tiles = LoadObjTiles(gUnkEu_08B50BE6, 0x180);
            AnimInit(&work->anim, gUnkEu_09F5C190, gUnkEu_09F5C18C);
            break;
        case 10:
            work->tiles = LoadObjTiles(gUnkEu_08B51140, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1B0, gUnkEu_09F5C1AC);
            break;
        default:
            work->tiles = LoadObjTiles(gUnkEu_08B519E0, 0x80);
            AnimInit(&work->anim, gUnkEu_09F5C1F0, gUnkEu_09F5C1EC);
            break;
        }

        break;
    case LANGUAGE_SPANISH:
    default:
        switch (src->kind) {
        case 0:
            work->tiles = LoadObjTiles(gUnkEu_08B5147C, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1C8, gUnkEu_09F5C1C4);
            break;
        case 2:
            work->tiles = LoadObjTiles(gUnkEu_08B518CC, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1E8, gUnkEu_09F5C1E4);
            break;
        case 9:
            work->tiles = LoadObjTiles(gUnkEu_08B50A4A, 0x180);
            AnimInit(&work->anim, gUnkEu_09F5C188, gUnkEu_09F5C184);
            break;
        case 10:
            work->tiles = LoadObjTiles(gUnkEu_08B5102C, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1A8, gUnkEu_09F5C1A4);
            break;
        default:
            work->tiles = LoadObjTiles(gUnkEu_08B518CC, 0x100);
            AnimInit(&work->anim, gUnkEu_09F5C1E8, gUnkEu_09F5C1E4);
            break;
        }

        break;
    }

    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
#else
    switch (src->kind) {
    case 0:
        work->tiles = LoadObjTiles(gUnk_08B1F020, 0x100);
        AnimInit(&work->anim, gUnk_09EE11D0, gUnk_09EE11CC);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    case 1:
        work->tiles = LoadObjTiles(gUnk_08B1ED76, 0x180);
        AnimInit(&work->anim, gUnk_09EE11C0, gUnk_09EE11BC);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    case 2:
        work->tiles = LoadObjTiles(gUnk_08B1EF0C, 0x100);
        AnimInit(&work->anim, gUnk_09EE11C8, gUnk_09EE11C4);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    case 3:
        work->tiles = LoadObjTiles(gUnk_08B1F13A, 0x180);
        AnimInit(&work->anim, gUnk_09EE11D8, gUnk_09EE11D4);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    case 5:
        work->tiles = LoadObjTiles(gUnk_08B1F7AC, 0x500);
        AnimInit(&work->anim, gUnk_09EE1204, gUnk_09EE11F4);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    case 6:
        work->tiles = LoadObjTiles(gUnk_08B1F7AC, 0x500);
        AnimInit(&work->anim, gUnk_09EE1204, gUnk_09EE11F4);
        AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);
        break;
    case 7:
        work->tiles = LoadObjTiles(gUnk_08B1F7AC, 0x500);
        AnimInit(&work->anim, gUnk_09EE1204, gUnk_09EE11F4);
        AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
        break;
    case 8:
        work->tiles = LoadObjTiles(gUnk_08B1F7AC, 0x500);
        AnimInit(&work->anim, gUnk_09EE1204, gUnk_09EE11F4);
        AnimStart(&work->anim, 3, ANIM_FLAG_LOOP);
        break;
    case 9:
        work->tiles = LoadObjTiles(gUnk_08B1F472, 0x180);
        AnimInit(&work->anim, gUnk_09EE11E8, gUnk_09EE11E4);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    case 10:
        work->tiles = LoadObjTiles(gUnk_08B1F60E, 0x140);
        AnimInit(&work->anim, gUnk_09EE11F0, gUnk_09EE11EC);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    case 4:
    default:
        work->tiles = LoadObjTiles(gUnk_08B1F2D6, 0x180);
        AnimInit(&work->anim, gUnk_09EE11E0, gUnk_09EE11DC);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        break;
    }
#endif

    work->gfx = AnimGetGfx(&work->anim);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    work->x = src->x;
    work->y = src->y;
    work->z = src->z;
    work->timer = 0;
}

s32 task_btl_pop_1(BtlPopWork* work) {
    work->z -= 0xC0;

    if (work->timer > 49) {
        return 0;
    }

    work->timer++;
    work->gfx = AnimUpdate(&work->anim);
    return 1;
}

void task_btl_pop_2(BtlPopWork* work) {
    s16 x;
    s16 y;

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, 0, SPRITE_FLAG_NO_MOSAIC, 5);
}

void task_btl_pop_3(BtlPopWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_btl_escape_0(BtlEscapeWork* work) {
    void** p;

    work->progressMax = 0x5A00;
#ifdef VERSION_EU
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);

    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        work->tiles = LoadObjTiles(gUnk_08B1EB1C, 0x240);
        p = gUnk_09EE11A4;
        break;
    case LANGUAGE_FRENCH:
        work->tiles = LoadObjTiles(gUnkEu_08B51D50, 0x240);
        p = gUnkEu_09F5C20C;
        break;
    case LANGUAGE_SPANISH:
        work->tiles = LoadObjTiles(gUnkEu_08B51FB8, 0x240);
        p = gUnkEu_09F5C21C;
        break;
    case LANGUAGE_ITALIAN:
        work->tiles = LoadObjTiles(gUnkEu_08B52220, 0x240);
        p = gUnkEu_09F5C22C;
        break;
    case LANGUAGE_GERMAN:
    default:
        work->tiles = LoadObjTiles(gUnkEu_08B52488, 0x240);
        p = gUnkEu_09F5C23C;
        break;
    }
#else
    work->tiles = LoadObjTiles(gUnk_08B1EB1C, 0x240);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    p = gUnk_09EE11A4;
#endif
    work->gfx = p[0];
    work->gfx2 = p[2];
    work->gfx3 = p[1];
    work->progressRatio = 0;
    work->progress = 0;
    work->visible = 0;
    work->timer = 0;
}

s32 task_btl_escape_1(BtlEscapeWork* work) {
    if (gBtlWork->flags & BTL_FLAG_STOP_SPAWNING) {
        return 0;
    }

    if (!(gBtlWork->flags & BTL_FLAG_PUSHING_EDGE)) {
        if (work->visible != 0) {
            work->progress = 0;
            work->visible = 0;
            work->timer = 0;
        }
    } else {
        if (work->timer <= 15) {
            work->timer++;
            work->visible = 0;
        } else {
            work->visible = 1;
            work->progressRatio = (work->progress << 8) / work->progressMax;

            if (work->progress >= work->progressMax) {
                gGameState.flags |= GAME_FLAG_BATTLE_NOT_WON;
                gBtlWork->flags |= BTL_FLAG_ESCAPED;
                gBtlWork->flags |= BTL_FLAG_BATTLE_OVER;
                work->visible = 0;
            } else {
                work->progress += 256;
            }
        }
    }

    return 1;
}

void task_btl_escape_2(BtlEscapeWork* work) {
    BtlObj* actor;
    s16 x;
    s16 y;
    s32 v;
    ObjAffine* aff;

    if (work->visible == 0) {
        return;
    }

    actor = gBtlWork->actor;

    if (actor->flags & BTLOBJ_FLAG_FACING_LEFT) {
        WorldToScreen(&x, &y, actor->x - 768, actor->y, actor->z - 10240);
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, 0, 0, 2);
    } else {
        WorldToScreen(&x, &y, actor->x - 3072, actor->y, actor->z - 10240);
        DrawSprite(x, y, work->gfx2, work->tiles, work->palette, 0, 0, 2);
    }

    if (work->progressRatio > 0) {
        v = work->progressRatio * 2;

        if (v > 256) {
            aff = AllocObjAffine(0, v, 256, 1);
        } else {
            aff = AllocObjAffine(0, v, 256, 0);
        }

        DrawSprite(x, y, work->gfx3, work->tiles, work->palette, aff, 0, 1);
    }
}

void task_btl_escape_3(BtlEscapeWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_btl_prize_0(BtlPrizeWork* work, BtlPremireSrc* src) {
    u8 angle;
    s32 spd;

    work->x = src->x;
    work->y = src->y;
    work->z = src->z;
    work->groundZ = 0;

    if (gBtlWork->boundsCallback != NULL) {
        gBtlWork->boundsCallback(&work->x, &work->y, &work->z, &work->groundZ);
    }

    work->vz = -(GetRandom() % 897 + 768);
    angle = GetRandom();

    work->tiles = LoadObjTiles(gBPuraizuTiles, 0x340);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    work->timer = 0;
    work->gfx2 = gBPuraizuFrame0;
    work->flags = (BTL_PRIZE_FLAG_SPRITE_VISIBLE | BTL_PRIZE_FLAG_DRAW_SHADOW);

    if (src->noTimeout != 0) {
        work->flags = (BTL_PRIZE_FLAG_SPRITE_VISIBLE | BTL_PRIZE_FLAG_DRAW_SHADOW | BTL_PRIZE_FLAG_NO_TIMEOUT);
    }

    switch (src->kind) {
    case 0:
        work->gfx = gBPuraizuFrame1;
        work->healAmount = 0;
        work->exp = 1400;
        work->bounceSpeed = 1280;
        spd = 384;
        break;
    case 1:
        work->gfx = gBPuraizuFrame2;
        work->healAmount = 3;
        work->exp = 0;
        work->bounceSpeed = 0x300;
        spd = 76;
        break;
    case 2:
        work->gfx = gBPuraizuFrame3;
        work->healAmount = 10;
        work->exp = 0;
        work->bounceSpeed = 0x300;
        spd = 76;
        break;
    case 3:
        work->gfx = gBPuraizuFrame4;
        work->healAmount = 0;
        work->exp = 1;
        work->bounceSpeed = 0x400;
        spd = 128;
        break;
    case 4:
        work->gfx = gBPuraizuFrame5;
        work->healAmount = 0;
        work->exp = 10;
        work->bounceSpeed = 0x400;
        spd = 128;
        break;
    case 5:
        work->gfx = gBPuraizuFrame6;
        work->healAmount = 0;
        work->exp = 60;
        work->bounceSpeed = 0x400;
        spd = 128;
        break;
    case 6:
        work->gfx = gBPuraizuFrame7;
        work->healAmount = 0;
        work->exp = 5;
        work->bounceSpeed = 0x400;
        spd = 179;
        break;
    case 7:
        work->gfx = gBPuraizuFrame8;
        work->healAmount = 0;
        work->exp = 30;
        work->bounceSpeed = 0x400;
        spd = 179;
        break;
    case 8:
    default:
        work->gfx = gBPuraizuFrame9;
        work->healAmount = 0;
        work->exp = 199;
        work->bounceSpeed = 0x400;
        spd = 179;
        break;
    }

    work->collected = 0;
    work->orbitRadius = 0x100;
    gBtlWork->prizeCount++;
    work->vx = (gSineTable[angle] * spd) >> 8;
    work->vy = (-gSineTable[angle + 64] * spd) >> 8;

    if (abs(work->vx) <= 50) {
        if (work->vx < 0) {
            work->vx = -(GetRandom() % 78 + 51);
        } else {
            work->vx = GetRandom() % 78 + 51;
        }
    }

    work->actor = gBtlWork->actor;
}

#define DIST(a, b) ((a) - (b) >= 0 ? (a) - (b) : (b) - (a))
s32 task_btl_prize_1(BtlPrizeWork* work) {
    s32 hit;
    s32 near;
    s32 range;
    s32 d1;
    s32 d2;
    s32 vz;
    s32 tx;
    s32 ty;
    s32 tz;
    u64 f;
    u64 bit;

    if (gBtlWork->flags & BTL_FLAG_FIELD_HIDDEN) {
        return 0;
    }

    if (work->collected == 0) {
        if (!(work->flags & BTL_PRIZE_FLAG_NO_MOVE)) {
            if (gBtlWork->boundsCallback != NULL) {
                gBtlWork->boundsCallback(&work->x, &work->y, &work->z, &work->groundZ);
            }

            work->z += work->vz;
            vz = work->vz - 15;
            work->vz = vz + gBtlWork->gravity;

            switch (ClampBattlePosition(&work->x, &work->y, 0, 0)) {
            case 1:
            case 2:
                work->vx = -work->vx;
                break;
            case 3:
            case 4:
                work->vy = -work->vy;
                break;
            }

            work->x += work->vx;
            work->y += work->vy;

            if (work->z > work->groundZ) {
                work->flags &= ~BTL_PRIZE_FLAG_DRAW_SHADOW;
                work->z = work->groundZ;
                work->vz = -((work->bounceSpeed >> 1) + GetRandom() % (work->bounceSpeed - (work->bounceSpeed >> 1) + 1));
            } else {
                work->flags |= BTL_PRIZE_FLAG_DRAW_SHADOW;
            }
        }

        if (work->flags & BTL_PRIZE_FLAG_CAN_COLLECT) {
            hit = 0;
            f = gBtlWork->flags;

            if (f & BTL_FLAG_VS_BATTLE) {
                d1 = DIST(work->x, gBtlWork->actor->x);
                d2 = DIST(work->x, gRikuBtlWork->actor->x);

                if (d1 == d2) {
                    bit = f & BTL_FLAG_VS_LINK_PARENT;
                    near = bit != 0;
                } else {
                    near = 1;

                    if (d1 < d2) {
                        near = 0;
                    }
                }

                if (near) {
                    if (gRikuBtlWork->hcEffect == 6) {
                        range = 0x10000;
                    } else {
                        range = 0x2800;
                    }

                    if (DIST(gRikuBtlWork->actor->x, work->x) < range &&
                        DIST(gRikuBtlWork->actor->y, work->y) < (range >> 1) &&
                        DIST(gRikuBtlWork->actor->z, work->z) < 12800) {
                        work->actor = gRikuBtlWork->actor;
                        hit = 1;
                    } else {
                        if (gBtlWork->hcEffect == 6) {
                            range = 0x10000;
                        } else {
                            range = 0x2800;
                        }

                        if (DIST(gBtlWork->actor->x, work->x) < range &&
                            DIST(gBtlWork->actor->y, work->y) < (range >> 1) &&
                            DIST(gBtlWork->actor->z, work->z) < 12800) {
                            hit = 1;
                        }
                    }
                } else {
                    if (gBtlWork->hcEffect == 6) {
                        range = 0x10000;
                    } else {
                        range = 0x2800;
                    }

                    if (DIST(gBtlWork->actor->x, work->x) < range &&
                        DIST(gBtlWork->actor->y, work->y) < (range >> 1) &&
                        DIST(gBtlWork->actor->z, work->z) < 12800) {
                        hit = 1;
                    } else {
                        if (gRikuBtlWork->hcEffect == 6) {
                            range = 0x10000;
                        } else {
                            range = 0x2800;
                        }

                        if (DIST(gRikuBtlWork->actor->x, work->x) < range &&
                            DIST(gRikuBtlWork->actor->y, work->y) < (range >> 1) &&
                            DIST(gRikuBtlWork->actor->z, work->z) < 12800) {
                            work->actor = gRikuBtlWork->actor;
                            hit = 1;
                        }
                    }
                }
            } else {
                if (gBtlWork->hcEffect == 6) {
                    range = 0x10000;
                } else {
                    range = 0x2800;
                }

                if (DIST(gBtlWork->actor->x, work->x) < range &&
                    DIST(gBtlWork->actor->y, work->y) < (range >> 1) &&
                    DIST(gBtlWork->actor->z, work->z) < 12800) {
                    hit = 1;
                }
            }

            if (hit) {
                m4aSongNumStart(SONG_SYS_POWER_GET);

                if (gBtlWork->flags & BTL_FLAG_VS_BATTLE) {
                    work->actor->hp += work->healAmount;

                    if (work->actor->hp > work->actor->maxHp) {
                        work->actor->hp = work->actor->maxHp;
                    }
                } else {
                    work->actor->hp += work->healAmount;

                    if (work->actor->hp > work->actor->maxHp) {
                        work->actor->hp = work->actor->maxHp;
                    }

                    gGameState.progression.exp += work->exp;
                }

                work->collected = 1;
                work->timer = 0;
                work->angle = GetAngle(work->actor->x, work->actor->y, work->x, work->y);
                work->flags &= ~BTL_PRIZE_FLAG_DRAW_SHADOW;
                work->flags |= BTL_PRIZE_FLAG_SPRITE_VISIBLE;
                work->spinSpeed = GetRandom() % 6 + 5;
                return 1;
            }

            if (!(work->flags & BTL_PRIZE_FLAG_NO_TIMEOUT)) {
                if (work->timer > 360 && (work->timer & 3) == 0) {
                    work->flags ^= BTL_PRIZE_FLAG_SPRITE_VISIBLE;
                }

                if (work->timer > 420) {
                    return 0;
                }
            }
        } else {
            if (work->timer > 10) {
                work->flags |= BTL_PRIZE_FLAG_CAN_COLLECT;
            }
        }

        work->timer++;
    } else {
        tx = work->actor->x + ((gSineTable[work->angle] * (work->orbitRadius << 5)) >> 8);
        ty = work->actor->y + ((-gSineTable[work->angle + 64] * (work->orbitRadius << 4)) >> 8);
        tz = work->actor->z - ((work->timer >> 1) << 8);
        work->angle += work->spinSpeed;
        work->x += (tx - work->x) >> 2;
        work->y += (ty - work->y) >> 2;
        work->z += (tz - work->z) >> 2;
        work->orbitRadius -= 2;

        if (work->timer > 60) {
            return 0;
        }

        work->timer++;
    }

    return 1;
}

void task_btl_prize_2(BtlPrizeWork* work) {
    s16 x;
    s16 y;
    ObjAffine* aff;

    if (work->flags & BTL_PRIZE_FLAG_SPRITE_VISIBLE) {
        s32 pri = 0x800;

        WorldToScreen(&x, &y, work->x, work->y, work->z);
        aff = AllocObjAffine(0, gBtlWork->scale, gBtlWork->scale, 1);
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, aff, pri,
                   (u16)(-4100 - (work->y >> 8) * 4));

        if (work->flags & BTL_PRIZE_FLAG_DRAW_SHADOW) {
            WorldToScreen(&x, &y, work->x, work->y, work->groundZ);
            DrawSprite(x, y, work->gfx2, work->tiles, work->palette, aff, pri, 0xFFFF);
        }
    }
}

void task_btl_prize_3(BtlPrizeWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    gBtlWork->prizeCount--;
}

void task_btl_premire_0(BtlPremireWork* work, BtlPremireSrc* src) {
    u8 angle;
    s32 spd;

    work->x = src->x;
    work->y = src->y;
    work->z = src->z;
    work->groundZ = 0;

    if (gBtlWork->boundsCallback != NULL) {
        gBtlWork->boundsCallback(&work->x, &work->y, &work->z, &work->groundZ);
    }

    work->vz = -(GetRandom() % 897 + 768);
    angle = GetRandom();

    work->tiles = LoadObjTiles(gBPuraizuTiles, 0x340);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    AnimInit(&work->anim, gBPuraizuAnims, gBPuraizuFrames);
    AnimStart(&work->anim, 10, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    work->timer = 0;
    work->gfx2 = gBPuraizuFrame0;
    work->flags = (BTL_PRIZE_FLAG_SPRITE_VISIBLE | BTL_PRIZE_FLAG_DRAW_SHADOW);

    if (src->noTimeout != 0) {
        work->flags = (BTL_PRIZE_FLAG_SPRITE_VISIBLE | BTL_PRIZE_FLAG_DRAW_SHADOW | BTL_PRIZE_FLAG_NO_TIMEOUT);
    }

    work->bounceSpeed = 0x400;
    spd = 384;
    work->collected = 0;
    work->orbitRadius = 0x100;
    gBtlWork->prizeCount++;
    work->vx = (gSineTable[angle] * spd) >> 8;
    work->vy = (-gSineTable[angle + 64] * spd) >> 8;
    work->actor = gBtlWork->actor;
}

s32 task_btl_premire_1(BtlPremireWork* work) {
    s32 hit;
    s32 range;
    s32 vz;
    s32 tx;
    s32 ty;
    s32 tz;
    u64 f;

    if (gBtlWork->flags & BTL_FLAG_FIELD_HIDDEN) {
        return 0;
    }

    if (work->collected == 0) {
        if (!(work->flags & BTL_PRIZE_FLAG_NO_MOVE)) {
            if (gBtlWork->boundsCallback != NULL) {
                gBtlWork->boundsCallback(&work->x, &work->y, &work->z, &work->groundZ);
            }

            work->z += work->vz;
            vz = work->vz - 15;
            work->vz = vz + gBtlWork->gravity;

            switch (ClampBattlePosition(&work->x, &work->y, 0, 0)) {
            case 1:
            case 2:
                work->vx = -work->vx;
                break;
            case 3:
            case 4:
                work->vy = -work->vy;
                break;
            }

            work->x += work->vx;
            work->y += work->vy;

            if (work->z > work->groundZ) {
                work->flags &= ~BTL_PRIZE_FLAG_DRAW_SHADOW;
                work->z = work->groundZ;
                work->vz = -((work->bounceSpeed >> 1) + GetRandom() % (work->bounceSpeed - (work->bounceSpeed >> 1) + 1));
            } else {
                work->flags |= BTL_PRIZE_FLAG_DRAW_SHADOW;
            }
        }

        if (work->flags & BTL_PRIZE_FLAG_CAN_COLLECT) {
            hit = 0;
            f = gBtlWork->flags;

            if (f & BTL_FLAG_VS_BATTLE) {
                if (f & BTL_FLAG_VS_LINK_PARENT) {
                    if (gRikuBtlWork->hcEffect == 6) {
                        range = 0x10000;
                    } else {
                        range = 0x2000;
                    }

                    if (DIST(gRikuBtlWork->actor->x, work->x) < range &&
                        DIST(gRikuBtlWork->actor->y, work->y) < (range >> 1) &&
                        DIST(gRikuBtlWork->actor->z, work->z) < 12800) {
                        work->actor = gRikuBtlWork->actor;
                        hit = 1;
                    } else {
                        if (gBtlWork->hcEffect == 6) {
                            range = 0x10000;
                        } else {
                            range = 0x2000;
                        }

                        if (DIST(gBtlWork->actor->x, work->x) < range &&
                            DIST(gBtlWork->actor->y, work->y) < (range >> 1) &&
                            DIST(gBtlWork->actor->z, work->z) < 12800) {
                            hit = 1;
                        }
                    }
                } else {
                    if (gBtlWork->hcEffect == 6) {
                        range = 0x10000;
                    } else {
                        range = 0x2000;
                    }

                    if (DIST(gBtlWork->actor->x, work->x) < range &&
                        DIST(gBtlWork->actor->y, work->y) < (range >> 1) &&
                        DIST(gBtlWork->actor->z, work->z) < 12800) {
                        hit = 1;
                    } else {
                        if (gRikuBtlWork->hcEffect == 6) {
                            range = 0x10000;
                        } else {
                            range = 0x2000;
                        }

                        if (DIST(gRikuBtlWork->actor->x, work->x) < range &&
                            DIST(gRikuBtlWork->actor->y, work->y) < (range >> 1) &&
                            DIST(gRikuBtlWork->actor->z, work->z) < 12800) {
                            work->actor = gRikuBtlWork->actor;
                            hit = 1;
                        }
                    }
                }
            } else {
                if (gBtlWork->hcEffect == 6) {
                    range = 0x10000;
                } else {
                    range = 0x2000;
                }

                if (DIST(gBtlWork->actor->x, work->x) < range &&
                    DIST(gBtlWork->actor->y, work->y) < (range >> 1) &&
                    DIST(gBtlWork->actor->z, work->z) < 12800) {
                    hit = 1;
                }
            }

            if (hit) {
                m4aSongNumStart(SONG_SYS_POWER_GET);
                gBtlWork->flags |= BTL_FLAG_PREMIRE_COLLECTED;
                work->timer = 0;
                work->collected = 1;
                work->timer = 0;
                work->angle = GetAngle(work->actor->x, work->actor->y, work->x, work->y);
                work->flags &= ~BTL_PRIZE_FLAG_DRAW_SHADOW;
                work->flags |= BTL_PRIZE_FLAG_SPRITE_VISIBLE;
                work->spinSpeed = GetRandom() % 6 + 5;
                work->gfx = AnimUpdate(&work->anim);
                return 1;
            }

            if (!(work->flags & BTL_PRIZE_FLAG_NO_TIMEOUT)) {
                if (work->timer > 360 && (work->timer & 3) == 0) {
                    work->flags ^= BTL_PRIZE_FLAG_SPRITE_VISIBLE;
                }

                if (work->timer > 420) {
                    return 0;
                }
            }
        } else {
            if (work->timer > 10) {
                work->flags |= BTL_PRIZE_FLAG_CAN_COLLECT;
            }
        }

        work->timer++;
    } else {
        tx = work->actor->x + ((gSineTable[work->angle] * (work->orbitRadius << 5)) >> 8);
        ty = work->actor->y + ((-gSineTable[work->angle + 64] * (work->orbitRadius << 4)) >> 8);
        tz = work->actor->z - ((work->timer >> 1) << 8);
        work->angle += work->spinSpeed;
        work->x += (tx - work->x) >> 2;
        work->y += (ty - work->y) >> 2;
        work->z += (tz - work->z) >> 2;
        work->orbitRadius -= 2;

        if (work->timer > 60) {
            return 0;
        }

        work->timer++;
    }

    work->gfx = AnimUpdate(&work->anim);
    return 1;
}

void task_btl_premire_2(BtlPremireWork* work) {
    s16 x;
    s16 y;
    ObjAffine* aff;

    if (work->flags & BTL_PRIZE_FLAG_SPRITE_VISIBLE) {
        u16 anim = GetBattleSpritePriorityFlags(work->y);

        WorldToScreen(&x, &y, work->x, work->y, work->z);
        aff = AllocObjAffine(0, gBtlWork->scale, gBtlWork->scale, 1);
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, aff, anim,
                   (u16)(-4100 - (work->y >> 8) * 4));

        if (work->flags & BTL_PRIZE_FLAG_DRAW_SHADOW) {
            WorldToScreen(&x, &y, work->x, work->y, work->groundZ);
            DrawSprite(x, y, work->gfx2, work->tiles, work->palette, aff, anim, 0xFFFF);
        }
    }
}

void task_btl_premire_3(BtlPremireWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    gBtlWork->prizeCount--;
}

void task_btl_start_0(BtlStartWork* work) {
    BgAnimStart(&gBgAnimDefBtlStart, 120, 72);
    BgAnimSetTransform(0, 0x200, 0x200);
    SetBgBlend(gBtlWork->bg, 16, 16);
    SetBattleZoom(1, 0x200, 0x10000, 0x14000);
    FadeStartIn(FADE_MODE_BLACK, 60);
    work->timer = 0;
    m4aSongNumStart(SONG_SYS_ENCOUNT);
    SetBgPriority(gBtlWork->bg, 0);
}

s32 task_btl_start_1(BtlStartWork* work) {
    if (work->timer <= 20) {
        FadeStartIn(FADE_MODE_BLACK, 40);
    }

    switch (work->timer) {
    case 34:
        SetBattleZoom(35, 0x100, gBtlWork->x2, gBtlWork->y2);
        break;
    case 43:
        FadeStartIn(FADE_MODE_ADD_WHITE, 30);
        break;
    case 74:
        return 0;
    }

    work->timer++;
    return 1;
}

TaskDesc gTaskDescBtlShadow = {
    "task_btl_shadow",
    (TaskInitFunc)task_btl_shadow_0,
    (TaskUpdateFunc)task_btl_shadow_1,
    (TaskDrawFunc)task_btl_shadow_2,
    (TaskDestroyFunc)task_btl_shadow_3,
    sizeof(BtlShadowWork),
};

TaskDesc gTaskDescBtlHpply = {
    "task_btl_hpply",
    (TaskInitFunc)task_btl_hpply_0,
    (TaskUpdateFunc)task_btl_hpply_1,
    (TaskDrawFunc)task_btl_hpply_2,
    (TaskDestroyFunc)task_btl_hpply_3,
    sizeof(BtlHpplyWork),
};

TaskDesc gTaskDescBtlHpenm = {
    "task_btl_hpenm",
    (TaskInitFunc)task_btl_hpenm_0,
    (TaskUpdateFunc)task_btl_hpenm_1,
    (TaskDrawFunc)task_btl_hpenm_2,
    (TaskDestroyFunc)task_btl_hpenm_3,
    sizeof(BtlHpenmWork),
};

TaskDesc gTaskDescBtlPause = {
    "task_btl_pause",
    (TaskInitFunc)task_btl_pause_0,
    (TaskUpdateFunc)task_btl_pause_1,
    (TaskDrawFunc)task_btl_pause_2,
    (TaskDestroyFunc)task_btl_pause_3,
    sizeof(BtlPauseWork),
};

TaskDesc gTaskDescBtlPop = {
    "task_btl_pop",
    (TaskInitFunc)task_btl_pop_0,
    (TaskUpdateFunc)task_btl_pop_1,
    (TaskDrawFunc)task_btl_pop_2,
    (TaskDestroyFunc)task_btl_pop_3,
    sizeof(BtlPopWork),
};

TaskDesc gTaskDescBtlEscape = {
    "task_btl_escape",
    (TaskInitFunc)task_btl_escape_0,
    (TaskUpdateFunc)task_btl_escape_1,
    (TaskDrawFunc)task_btl_escape_2,
    (TaskDestroyFunc)task_btl_escape_3,
    sizeof(BtlEscapeWork),
};

TaskDesc gTaskDescBtlPrize = {
    "task_btl_prize",
    (TaskInitFunc)task_btl_prize_0,
    (TaskUpdateFunc)task_btl_prize_1,
    (TaskDrawFunc)task_btl_prize_2,
    (TaskDestroyFunc)task_btl_prize_3,
    sizeof(BtlPrizeWork),
};

TaskDesc gTaskDescBtlPremire = {
    "task_btl_premire",
    (TaskInitFunc)task_btl_premire_0,
    (TaskUpdateFunc)task_btl_premire_1,
    (TaskDrawFunc)task_btl_premire_2,
    (TaskDestroyFunc)task_btl_premire_3,
    sizeof(BtlPremireWork),
};

TaskDesc gTaskDescBtlStart = {
    "task_btl_start",
    (TaskInitFunc)task_btl_start_0,
    (TaskUpdateFunc)task_btl_start_1,
    NULL,
    NULL,
    sizeof(BtlStartWork),
};
