#ifndef GUARD_PC_API_H
#define GUARD_PC_API_H

#include "types.h"

struct CloudWork;

void CloudJumpTo(struct CloudWork* work, s32 a, s32 b);
void CloudLeapTo(struct CloudWork* work, s32 a, s32 b);
s32 CloudTryJumpAway(struct CloudWork* work);

#endif
