#ifndef GUARD_CARD_ENEMY_H
#define GUARD_CARD_ENEMY_H

#include "card.h"
#include "types.h"

u8 EnemyCardDeal(CardDisplayWork* work, void* a);
u8 EnemyCardClosed(CardDisplayWork* work, void* a);
u8 EnemyCardShrinkAway(CardDisplayWork* work);
void SetBossCardValue(u16 a);
u16 GetBossCardValue();

#endif
