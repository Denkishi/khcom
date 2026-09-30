#ifndef GUARD_MS_CHARGE_API_H
#define GUARD_MS_CHARGE_API_H

#include "types.h"

typedef struct MsCard {
    u16 kind;
    u16 cardId;
    u16 category;
    s16 values[10][2];
    u8 premium;
    u8 unk_2F[0x1];
    u32 sortKey;
} MsCard;

MsCard* GetMsChargeSelectedCard(void);
void MsChargeLoadGrid(void);
void MsChargeLoadSelectedCard(void);
void MsChargeDrawPoints(void);
void MsChargeDrawCardCounts(void);
void MsChargeDrawCategoryCounts(void);
void MsChargeDrawValueCounts(void);
void MsChargeDrawTab(s16 a);
void MsChargeBuildCardList(void);
void MsChargeHandleGridInput(void);
void MsChargeHandleTabInput(void);
void MsChargeHandleValueInput(void);
void MsChargeHandleConfirmInput(void);
void MsChargeHandleNoticeInput(void);
void MsChargeDraw(void);

#endif
