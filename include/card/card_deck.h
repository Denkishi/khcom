#ifndef GUARD_CARD_DECK_H
#define GUARD_CARD_DECK_H

#include "card_types.h"
#include "types.h"

u8 GetActiveDeckIndex();
u16 CountCardsById(u16 cardId);
Deck* CreateLinkSendDeck();
Deck* CreateLinkPartnerDeck();
u8 IsActiveDeckAllPremium();
u8 HasNonPremiumCardsInActiveDeck();
u8 IsCardCollectionFull();

#endif
