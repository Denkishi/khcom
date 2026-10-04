#ifndef GUARD_CARD_PRIZE_CARD_H
#define GUARD_CARD_PRIZE_CARD_H

#include "card.h"
#include "taskpool.h"
#include "types.h"

void AimFieldPrizeCardAtCenter(PrizeCardWork* work);
u8 UpdateFieldPrizeCardFlight(PrizeCardWork* work, void* a);
u8 UpdateFieldPrizeCardShow(PrizeCardWork* work, void* a);
u8 UpdateFieldPrizeCardShrink(PrizeCardWork* work);
void CreateFieldPrizeCardTask(TaskPool* pool, PrizeCardTaskArgs* args);

#endif
