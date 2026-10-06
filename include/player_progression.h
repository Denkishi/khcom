#ifndef GUARD_PLAYER_PROGRESSION_H
#define GUARD_PLAYER_PROGRESSION_H

#include "types.h"
#include "player_progression_types.h"

void AdvanceLevelExpThreshold(PlayerProgression* progression);
void InitPlayerProgression();

u8 CanLevelUp();
void SetJiminyFlag(u32 flag);
u8 IsLinkStockLearned(u32 stock);
u8 IsLinkPartnerStockLearned(u32 stock);
u8 IsStockNew(u32 stock);
void LearnStock(u32 stock);
u8 IsJiminyFlagSet(u32 flag);
u8 IsJiminyFlagNew(u32 flag);
void ClearJiminyFlagNew(u32 flag);
u8 LevelUp();
void ClearStockNew(u32 stock);
u8 IsStockLearned(u32 stock);
void SetCardKindObtained(s32 kind);
u8 IsCardKindObtained(s32 kind);

#endif
