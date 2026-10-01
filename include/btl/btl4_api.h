#ifndef GUARD_BTL4_API_H
#define GUARD_BTL4_API_H

#include "types.h"

struct TutorialWork;

void TutorialOpenMessage(u16 a);
void TutorialOpenPersistentMessage(u16 a);
void TutorialRestoreBgMode();
void TutorialQueueMessage(struct TutorialWork* p, u16 b, u32 c);
void TutorialQueuePersistentMessage(struct TutorialWork* p, u16 b, u32 c);
void TutorialCloseMessage();
void TutorialWait(struct TutorialWork* p, u16 b, u32 c);
void TutorialShowArrow(struct TutorialWork* p, u16 b, u16 c, u16 d);
void TutorialHideArrow(struct TutorialWork* p);

#endif
