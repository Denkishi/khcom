#ifndef GUARD_CARD_SYSMSGWIN_H
#define GUARD_CARD_SYSMSGWIN_H

#include "card.h"
#include "types.h"

u8 UpdateSysmsgwinWaitInput(SysMsgWinWork* work, void* a);
s32 UpdateSysmsgwinClose(SysMsgWinWork* work);
u8 UpdateSysmsgwinChoice(SysMsgWinWork* work, void* a);
u8 UpdateSysmsgwinPersistent(SysMsgWinWork* work, void* a);

#endif
