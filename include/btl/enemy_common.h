#ifndef GUARD_ENEMY_COMMON_H
#define GUARD_ENEMY_COMMON_H

#include "types.h"

struct EmyDef;
struct EmyObj;
struct EmyWork;

void EmyInit(struct EmyWork* work, const struct EmyDef* def, struct EmyObj* obj);
s16 EmyLungeAttack(struct EmyWork* work, s16 a, s16 b, s16 c, s32 d, s16 e, u16 f, s16 g, s16 h, u16 i);
void EmyReturnToIdle(struct EmyWork* work);
void EmyStartKnockback(struct EmyWork* work);
u8 EmyUpdateReaction(struct EmyWork* work);
void EmyFinishSpawn(struct EmyWork* work);
s32 EmyUpdateCommonStates(struct EmyWork* work);
void EmyDraw(struct EmyWork* work);
void EmyReleaseResources(struct EmyWork* work);

#endif
