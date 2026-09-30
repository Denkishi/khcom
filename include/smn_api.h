#ifndef GUARD_SMN_API_H
#define GUARD_SMN_API_H

#include "battle_actor_types.h"

struct FrdDonaldWork;

u8 FrdDonaldApplyGravity(struct FrdDonaldWork* work);
void UpdateDonaldFlame(BtlObj* body, u8 a, s16 b, s16 c);

#endif
