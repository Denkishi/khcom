#ifndef GUARD_PLAYER_PROGRESSION_H
#define GUARD_PLAYER_PROGRESSION_H

#include "types.h"
#include "player_progression_types.h"

void AdvanceLevelExpThreshold(PlayerProgression* p);
void InitPlayerProgression();

u8 CanLevelUp();
void SetJiminyFlag(u32 a);
u8 IsLinkStockLearned(u32 a);
u8 IsLinkPartnerStockLearned(u32 a);
u8 IsStockNew(u32 a);
void LearnStock(u32 a);
u8 IsJiminyFlagSet(u32 a);
u8 IsJiminyFlagNew(u32 a);
void ClearJiminyFlagNew(u32 a);
u8 LevelUp();
void ClearStockNew(u32 a);
u8 IsStockLearned(u32 a);
void SetCardKindObtained(s32 a);
u8 IsCardKindObtained(s32 a);

#endif
