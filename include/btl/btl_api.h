#ifndef GUARD_BTL_API_H
#define GUARD_BTL_API_H

#include "types.h"

void SelectLockonTarget();
void BtlMapResetShake();
void BtlMapStartShake();
void BtlMapUpdateShake();
s32 BtlMapGetShake();
void BtlMapSetCameraTarget(s32 a, s32 b);
void BtlMapFollowPosition(s32 a, s32 b, s32 c);

#endif
