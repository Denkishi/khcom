#include "hum.h"
#include "sprites_evt.h"
#include "sprites_hum.h"
#include "hum_common.h"
#include "actor_localized_data.h"
#include "hum_tasks.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "game_state.h"
#include "hum_types.h"
#include "mode_chkobj_assets.h"
#include "player_progression_types.h"
#include "taskpool.h"
#include "types.h"

static const AnimDef sHumLeonAnimDefs[5] = {
    { gReonFl00Frames, gReonFl00Anims, gReonFl00Tiles, 0, { 0, 0, 0 } },
    { gUnk_09EE25D0, gUnk_09EE25E4, gUnk_08C6668E, 0, { 0, 0, 0 } },
    { gUnk_09EE25D0, gUnk_09EE25E4, gUnk_08C6668E, 3, { 0, 0, 0 } },
    { gUnk_09EE25D0, gUnk_09EE25E4, gUnk_08C6668E, 1, { 0, 0, 0 } },
    { gUnk_09EE25D0, gUnk_09EE25E4, gUnk_08C6668E, 2, { 0, 0, 0 } },
};

static const HumDef sHumLeonDef = { 128, 0, gReonPalette, 0, { 41, 99, 64, 14, 40, 99, 0 } };

TaskDesc gTaskDescHumLeon = {
    "task_hum_leon",
    (TaskInitFunc)task_hum_leon_0,
    (TaskUpdateFunc)task_hum_leon_1,
    (TaskDrawFunc)task_hum_leon_2,
    (TaskDestroyFunc)task_hum_leon_3,
    sizeof(LeonWork),
};

void task_hum_leon_0(LeonWork* work) {
    HumInit(&work->base, &sHumLeonDef);
    work->flashTimer = 0;
    work->unk_18A = 0;
    AnimChangeWithDef(sHumLeonAnimDefs, &work->base.anim, 0, ANIM_FLAG_LOOP, work->base.tiles);
    work->savedLearnedStocks = gGameState.progression.learnedStocks;
    work->savedLearnedStocks2 = gGameState.progression.learnedStocks2;
    gGameState.progression.learnedStocks = 0;
    gGameState.progression.learnedStocks2 = 0;
}

u8 task_hum_leon_1(LeonWork* work) {
    LeonWork* w;
    BtlObj* act;
    s32 x;
    s32 y;
    s32 z;
    s32 a;
    s32 b;
    s32 c;
    u8 r;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &a, &b, &c);

    switch (HumUpdateReaction(&work->base)) {
    case 4:
        break;
    case 5:
        work->base.state = 19;
        work->base.stateTimer = 0;
        break;
    }

    HumFaceTarget(&work->base, 1);

    switch (work->base.state) {
    case 12:
        AnimChangeWithDef(sHumLeonAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
        break;
    case 0:
        if (gBtlWork->flags & 0x20000000000) {
            if (w->unk_18A == 0) {
                AnimChangeWithDef(sHumLeonAnimDefs, &w->base.anim, 1, 0, w->base.tiles);
                w->unk_18A = 1;
            } else if (AnimIsFinished(&work->base.anim)) {
                AnimChangeWithDef(sHumLeonAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
            }
        } else {
            if (w->unk_18A != 0) {
                AnimChangeWithDef(sHumLeonAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
                w->unk_18A = 0;
            } else if (AnimIsFinished(&work->base.anim)) {
                AnimChangeWithDef(sHumLeonAnimDefs, &w->base.anim, 0, ANIM_FLAG_LOOP, w->base.tiles);
            }
        }

        if (gBtlWork->flags & 0x100000) {
            if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
                work->base.state = 20;
                work->base.stateTimer = 0;
            }
        }

        break;
    case 1:
        if (work->base.stateTimer == 0) {
            ClearBtlObjActionFlags(act);
            AnimChangeWithDef(sHumLeonAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            work->base.stateTimer = 8;
        }

        break;
    case 2:
        if (gBtlWork->flags & 0x100000) {
            if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
                work->base.state = 20;
                work->base.stateTimer = 0;
            }
        }

        break;
    case 20:
        if (work->base.stateTimer > 10) {
            gBtlWork->rikuKeys |= RIKU_KEY_USE_CARD;
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 19:
        if (work->base.stateTimer > 80) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }

        break;
    default:
        AnimChangeWithDef(sHumLeonAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
        HumFaceTarget(&work->base, 1);
        break;
    }

    if ((s16)w->flashTimer > 0) {
        w->flashTimer--;
        act->flags |= BTLOBJ_FLAG_HURT;
    } else {
        act->flags &= ~BTLOBJ_FLAG_HURT;
    }

    x = act->x;
    y = act->y;
    z = act->z;
    r = HumUpdate(&work->base);
    act->x = x;
    act->y = y;
    act->z = z;
    return r;
}

void task_hum_leon_2(HumWork* work) {
    HumDraw(work);
}

void task_hum_leon_3(LeonWork* work) {
    gGameState.progression.learnedStocks = work->savedLearnedStocks;
    gGameState.progression.learnedStocks2 = work->savedLearnedStocks2;
    HumReleaseResources(&work->base);
}
