#include "task_descriptors.h"
#include "emy.h"
#include "sprites_emy.h"
#include "system_state.h"
#include "enemy_common.h"
#include "songs.h"
#include "player_progression.h"
#include "emy_tasks.h"
#include "anim.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "enemy_types.h"
#include "engine_math.h"
#include "m4a_song.h"
#include "mode_chkobj_assets.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>

static const AnimDef sEmy07CommonAnimDefs[3] = {
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl03Frames, gEmy07Fl03Anims, gEmy07Fl03Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0, { 0, 0, 0 } },
};

static const AnimDef sEmy07AnimDefs[7] = {
    { gEmy07Fl05Frames, gEmy07Fl05Anims, gEmy07Fl05Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl04Frames, gEmy07Fl04Anims, gEmy07Fl04Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl04tFrames, gEmy07Fl04tAnims, gEmy07Fl04tTiles, 0, { 0, 0, 0 } },
    { gEmy07Fl07Frames, gEmy07Fl07Anims, gEmy07Fl07Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl06Frames, gEmy07Fl06Anims, gEmy07Fl06Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl08Frames, gEmy07Fl08Anims, gEmy07Fl08Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl02Frames, gEmy07Fl02Anims, gEmy07Fl02Tiles, 0, { 0, 0, 0 } },
};

static const EmyDef sEmy07Def = { gEmy07Palette, sEmy07CommonAnimDefs, 0, 130, 20, 20, 0, 0, 0, 1, 0, { 6, 40, 32, 12, 16, 100, 0 } };

TaskDesc gTaskDescEmy07 = {
    "task_emy_07",
    (TaskInitFunc)task_emy_07_0,
    (TaskUpdateFunc)task_emy_07_1,
    (TaskDrawFunc)task_emy_07_2,
    (TaskDestroyFunc)task_emy_07_3,
    sizeof(Emy07Work),
};

void task_emy_07_0(Emy07Work* work, void* obj) {
    EmyInit(&work->base, &sEmy07Def, obj);
    work->successCount = 0;
    work->unk_186 = 0;
    work->base.idleState = 0x12;
    work->base.actor.flags |= BTLOBJ_FLAG_NEVER_USES_CARDS;
    work->rewarded = 0;
}

u8 task_emy_07_1(Emy07Work* work) {
    Emy07Work* w;
    BtlObj* act;
    EmySpawn spawn;
    u32 state;
    s32 pos;
    s32 pos2;

    w = work;
    act = &work->base.actor;
    state = work->base.state;

#ifdef VERSION_EU
    act->hp = 0x7FFF;
#endif

    EmyUpdateReaction(&work->base);

#ifdef VERSION_EU
    act->hp = act->maxHp;
#endif

    switch (work->base.state) {
    case 1:
    case 3:
    case 15:
        work->base.state = 26;

        switch (state) {
        case 21:
            w->unk_186 = 0;

            if (act->hitFlags & ATTACK_FLAG_ELEMENT_FIRE) {
                ClearBtlObjActionFlags(act);
                work->base.state = 20;
                work->base.stateTimer = 0;
            }

            break;
        case 22:
            w->unk_186 = 0;

            if (act->hitFlags & ATTACK_FLAG_ELEMENT_BLIZZARD) {
                ClearBtlObjActionFlags(act);
                work->base.state = 20;
                work->base.stateTimer = 0;
            }

            break;
        case 23:
            w->unk_186 = 1;

            if (act->hitFlags & ATTACK_FLAG_ELEMENT_THUNDER) {
                ClearBtlObjActionFlags(act);
                work->base.state = 20;
                work->base.stateTimer = 0;
            }

            break;
        }

        act->hp = act->maxHp;
        ColliderSetDisabled(&act->collider, 0);
        break;
    }

    switch (work->base.state) {
    case 18:
        AnimChangeWithDef(w->base.def->animDef, &w->base.anim, 0, ANIM_FLAG_LOOP | ANIM_FLAG_RANDOM_START,
            w->base.tiles);
        GetEnemyTargetPosition(act, &pos, NULL, NULL);

        if (act->x < pos) {
            act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
        } else {
            act->flags |= BTLOBJ_FLAG_FACING_LEFT;
        }

        if (GetRandom() % 60 == 0) {
            work->base.stateTimer = 0;

            switch (GetRandom() % 3) {
            case 1:
                work->base.state = 22;
                break;
            case 2:
                work->base.state = 23;
                break;
            case 0:
            default:
                work->base.state = 21;
                break;
            }
        } else {
            work->base.stateTimer++;
        }

        break;
    case 21:
        AnimChangeWithDef(sEmy07AnimDefs, &w->base.anim, 3, ANIM_FLAG_LOOP, w->base.tiles);

        if (work->base.stateTimer > 300) {
            work->base.stateTimer = 0;
            work->base.state = 18;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 22:
        AnimChangeWithDef(sEmy07AnimDefs, &w->base.anim, 4, ANIM_FLAG_LOOP, w->base.tiles);

        if (work->base.stateTimer > 300) {
            work->base.stateTimer = 0;
            work->base.state = 18;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 23:
        AnimChangeWithDef(sEmy07AnimDefs, &w->base.anim, 5, ANIM_FLAG_LOOP, w->base.tiles);

        if (work->base.stateTimer > 300) {
            work->base.stateTimer = 0;
            work->base.state = 18;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 20:
        if (w->unk_186 != 0) {
            AnimChangeWithDef(sEmy07AnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        } else {
            AnimChangeWithDef(sEmy07AnimDefs, &w->base.anim, 1, 0, w->base.tiles);
        }

        if (work->base.stateTimer == 0) {
            m4aSongNumStart(SONG_BTL_WM_OK);
            work->base.stateTimer = 1;
            act->flags |= BTLOBJ_FLAG_INTANGIBLE;
        }

        if (w->successCount == 2 && gFrameCounter % 10 == 0) {
            spawn.facingLeft = 1;
            spawn.hitPhase = 0;
            spawn.x = act->x;
            spawn.y = act->y;
            spawn.z = act->z - (act->height << 8);
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescBtlPrize,
                &spawn);
        }

        if (AnimIsFinished(&work->base.anim)) {
            w->successCount++;

            if (w->successCount > 2) {
                work->base.stateTimer = 0;
                work->base.state = 25;
                w->rewarded = 1;
                SetJiminyFlag(110);
            } else {
                work->base.stateTimer = 0;
                work->base.state = 18;
                act->flags &= ~BTLOBJ_FLAG_INTANGIBLE;
            }
        }

        break;
    case 26:
        if (work->base.stateTimer == 0) {
            AnimChangeWithDef(w->base.def->animDef, &w->base.anim, 1, 0,
                w->base.tiles);
        }

        GetEnemyTargetPosition(act, &pos2, NULL, NULL);

        if (act->x < pos2) {
            act->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
        } else {
            act->flags |= BTLOBJ_FLAG_FACING_LEFT;
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            act->flags |= BTLOBJ_FLAG_INTANGIBLE;
            work->base.stateTimer = 0;
            work->base.state = 19;
        } else {
            work->base.stateTimer++;
        }

        break;
    case 19:
        AnimChangeWithDef(sEmy07AnimDefs, &w->base.anim, 0, 0, w->base.tiles);

        if (work->base.stateTimer == 0) {
            act->flags |= BTLOBJ_FLAG_INTANGIBLE;
            work->base.stateTimer = 1;
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 25;
        }

        break;
    case 25:
        AnimChangeWithDef(sEmy07AnimDefs, &w->base.anim, 6, 0, w->base.tiles);

        if (AnimIsFinished(&work->base.anim)) {
            if (w->rewarded != 0) {
                DropEnemyPrizes(act);
                TryDropPremireCard(act);
            }

            return 0;
        }

        break;
    }

    return EmyUpdateCommonStates(&work->base);
}

void task_emy_07_2(EmyWork* work) {
    EmyDraw(work);
}

void task_emy_07_3(EmyWork* work) {
    EmyReleaseResources(work);
}
