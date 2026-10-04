#ifndef GUARD_CARD_RIKU_TUTORIAL_H
#define GUARD_CARD_RIKU_TUTORIAL_H

#include "card.h"
#include "types.h"

u8 FindStockPairsInCombo(s32* a, u8* b);
s32 GetStockMove(s32 a);
s32 IsThreeDistinctAttackCards(CardDisplayWork** p, u8 b);
s32 IsThreeAttackCardsNoMove18(CardDisplayWork** p, u8 b);
s32 IsAttackDonaldGoofyAnyOrder(CardDisplayWork** p, u8 b);
s32 IsKindPairThenNonSummonOfCategory(CardDisplayWork** p, u8 b, u16 c, u16 d, u8 e);
s32 IsKindPairThenSummon(CardDisplayWork** p, u8 b, u16 c, u16 d);
s32 IsKindThenTwoAttackCards(CardDisplayWork** p, u16 c, u8 b);
s32 IsKindThenTwoOfCategory(CardDisplayWork** p, u16 c, u8 e, u8 b);
s32 IsFireMushuAttack(CardDisplayWork** p, u8 b);
s32 IsTwoSummonsThenKind(CardDisplayWork** p, u8 b, u16 c);
s32 IsSimbaMushuItem(CardDisplayWork** p, u8 b);
s32 IsSummonMagicJackOrBambiBlizzardItem(CardDisplayWork** p, u8 b);
s32 IsGenieTinkerBellSummon(CardDisplayWork** p, u8 b);
s32 IsMegaEtherMegalixirItem(CardDisplayWork** p, u8 b);
s32 IsFireDonaldMagic(CardDisplayWork** p, u8 b);
s32 IsCloudStopAttack(CardDisplayWork** p, u8 b);
s32 IsAeroFireMagic(CardDisplayWork** p, u8 b);
s32 IsAeroBlizzardMagic(CardDisplayWork** p, u8 b);
s32 IsTwoMagicThenPeterPan(CardDisplayWork** p, u8 b);
u8 IsLinkSideStockLearned(s32 a, s32 b);

#endif
