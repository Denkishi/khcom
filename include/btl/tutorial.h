#ifndef GUARD_TUTORIAL_H
#define GUARD_TUTORIAL_H

#include "types.h"
#include "anim.h"

enum TutorialFlag {
    TUTORIAL_FLAG_CARD_ACTION_ACTIVE = 0x2,
    TUTORIAL_FLAG_SHOW_ARROW = 0x4
};

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

void TutorialOpenMessage(u16 a);
void TutorialOpenPersistentMessage(u16 a);
void TutorialRestoreBgMode();
void TutorialQueueMessage(TutorialWork* work, u16 b, u32 c);
void TutorialQueuePersistentMessage(TutorialWork* work, u16 b, u32 c);
void TutorialCloseMessage();
void TutorialWait(TutorialWork* work, u16 b, u32 c);
void TutorialShowArrow(TutorialWork* work, u16 b, u16 c, u16 d);
void TutorialHideArrow(TutorialWork* work);
void task_tutorial_0(TutorialWork* work, s32 arg1);
s32 task_tutorial_1(TutorialWork* work);
void task_tutorial_2(TutorialWork* work);
void task_tutorial_3(TutorialWork* work);

#endif /* GUARD_TUTORIAL_H */
