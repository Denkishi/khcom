#ifndef GUARD_CONTINUE_UI_H
#define GUARD_CONTINUE_UI_H

#include "continue_types.h"
#include "taskpool.h"
#include "types.h"

extern TaskDesc gTaskDescContinueSora;
extern TaskDesc gTaskDescContinueRiku;

void LoadContinueCursorPalette(s32 a);
void ContinueSora_0(ContinueWork* p);
void ContinueRiku_0(ContinueWork* p);

#endif
