#ifndef GUARD_CARD_MSGWIN_H
#define GUARD_CARD_MSGWIN_H

#include "card.h"
#include "types.h"

u8 UpdateCardMsgwinLoadText(CardMsgWinWork* work, void* a);
u8 UpdateCardMsgwinWaitInput(CardMsgWinWork* work, void* a);
u8 UpdateCardMsgwinTypingPersistent(CardMsgWinWork* work, void* a);
u8 UpdateCardMsgwinPersistent(CardMsgWinWork* work, void* a);
void ShowPersistentCardMessage(void* pool, u32 a, u16 b);

#endif
