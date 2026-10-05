/**
 * btl_hpply.c
 * Player HP Gauge
 */

#include "m4a_song.h"
#include "btl2.h"
#include "sprites_btl.h"
#include "songs.h"
#include "anim.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "game_state.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "sprite_palettes.h"

void task_btl_hpply_0(BtlHpplyWork* work) {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        work->palette = LoadObjPalette(gRikuPalette, 0x20);
        work->tiles = AllocObjTiles(0x280, gBtlHpRikuFaceTiles);
        work->gfx = gBtlHpRikuFaceFrame0;
        AnimInit(&work->anim, gBtlHpRikuFaceAnims, gBtlHpRikuFaceFrames);
    } else {
        work->palette = LoadObjPalette(gSoraPalette, 0x20);
        work->tiles = AllocObjTiles(0x280, gBtlHpSoraFaceTiles);
        work->gfx = gBtlHpSoraFaceFrame0;
        AnimInit(&work->anim, gBtlHpSoraFaceAnims, gBtlHpSoraFaceFrames);
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

        work->gfx3 = NULL;
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
    } else if (flag) {
        AnimChange(&work->anim, 2, ANIM_FLAG_LOOP);
    } else {
        AnimChange(&work->anim, 0, ANIM_FLAG_LOOP);
    }

    if (work->firstUpdate) {
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

    if (flag) {
        if (!work->alarmPlaying) {
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

        if (work->alarmPlaying) {
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

    DrawSprite(4, 2, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 1);

    switch (work->gaugeMode) {
    case 0:
        DrawSprite(4, 2, work->gfx2, work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 4);
        break;
    case 1:
        DrawSprite(4, 2, gBHpgagFrame27, work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 4);
        DrawSprite(4, 2, work->gfx3, work->tiles3, work->palette2, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 3);
        break;
    case 2:
        DrawSprite(4, 2, work->gfx2, work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 4);
        DrawSprite(4, 2, work->gfx3, work->tiles3, work->palette2, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, 5);
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

TaskDesc gTaskDescBtlHpply = {
    "task_btl_hpply",
    (TaskInitFunc)task_btl_hpply_0,
    (TaskUpdateFunc)task_btl_hpply_1,
    (TaskDrawFunc)task_btl_hpply_2,
    (TaskDestroyFunc)task_btl_hpply_3,
    sizeof(BtlHpplyWork),
};
