#ifndef GUARD_CARD_DECK_H
#define GUARD_CARD_DECK_H

#include "card_types.h"

u8 GetActiveDeckIndex(void);
u16 CountCardsById(u16 cardId);
Deck* CreateLinkSendDeck(void);
Deck* CreateLinkPartnerDeck(void);

#endif
