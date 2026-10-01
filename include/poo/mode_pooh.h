#ifndef GUARD_MODE_POOH_H
#define GUARD_MODE_POOH_H

#include "types.h"
#include "pooh_actor_types.h"

extern u8 gPoohPalette[];
extern u8 gTrap0001Palette[];
extern u8 gTrap0002Palette[];
extern u8 gTrap0003Palette[];

void BackdropFadeToOriginal(u32 a, u16 b);
void BackdropFadeToAmount(u32 a, u16 b, u16 c);
u8 BackdropFadeIsActive();
void BackdropFadeFromAmount(u32 a, u16 b, u16 c);
void SetPooStartPositions();
void SetPooReentryPositions();
void mode_pooh_0(s32 arg);
void mode_pooh_1();
void mode_pooh_2();
u16 CountPooPrizes();
void SetPoohDir5Left(PoohWork* w);
void SetPoohDir8(PoohWork* w);
void SetPoohDir2(PoohWork* w);
void SetPoohDir3(PoohWork* w);
u8 IsAngleFacingRight(u8 a);
u8 GetPoohLookColumn(PoohWork* w);

#endif /* GUARD_MODE_POOH_H */
