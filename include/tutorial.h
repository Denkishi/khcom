#ifndef GUARD_TUTORIAL_H
#define GUARD_TUTORIAL_H

#include "battle_localized_data.h"

#include "card_api.h"

#include "movie_text.h"
#include "card_battle.h"

#include "obj_api.h"
#include "btl_effect.h"
#include "display.h"
#include "types.h"
#include "engine_math.h"
#include "anim.h"
#include "game.h"
#include "btl4_api.h"

typedef struct TutorialWork {
    u16 flags;
    u16 message;
    u32 state;
    u32 nextState;
    s16 timer;
    s16 unk_00E;
    s16 inputCooldown;
    u16 arrowX;
    u16 arrowY;
    u8 unk_016[0x2];
    void* tiles;
    void* palette;
    AnimState anim;
} TutorialWork;

void task_tutorial_0(TutorialWork* work, s32 arg1);
s32 task_tutorial_1(TutorialWork* work);
void task_tutorial_2(TutorialWork* work);
void task_tutorial_3(TutorialWork* work);

#endif /* GUARD_TUTORIAL_H */
