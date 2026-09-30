#ifndef GUARD_BTL_API_H
#define GUARD_BTL_API_H

#include "types.h"

void SelectLockonTarget(void);
void BtlMapResetShake(void);
void BtlMapStartShake(void);
void BtlMapUpdateShake(void);
s32 BtlMapGetShake(void);
void BtlMapSetCameraTarget(s32 a, s32 b);
void BtlMapFollowPosition(s32 a, s32 b, s32 c);

#endif
