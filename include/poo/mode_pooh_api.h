#ifndef GUARD_MODE_POOH_API_H
#define GUARD_MODE_POOH_API_H

#include "types.h"

struct Collider;
struct PooPos;
struct PoohWork;

void BackdropFadeStartOut(u32 a, u16 b);
void BackdropFadeReset(void);
void BackdropFadeSetColor(u16 r, u16 g, u16 b);
void BackdropFadeStartIn(u32 a, u16 b);
void BackdropFadeUpdate(void);
void SetPooAttackPoint(s32 a, s32 b, s32 c);
u8 PooAttackHitsCollider(struct Collider* p);
void ExitPoohMode(u32 a);
void OpenPoohModeMessage(u16 a);
u16 SpawnPooPrizes(u8 kind, u8 count, s32 x, s32 y, s32 z);
void SetPooMapBeeVisible(u8 a);
u8 IsPooMapBeeVisible(void);
void SetPoohDir5Right(struct PoohWork* w);
void SetPoohAnimation(struct PoohWork* w, u32 anim);
u8 IsWithinPoohRadius(u16 x, u16 y, u16 px, u16 py);
s32 GetPooManhattanDistance(struct PooPos* a, struct PooPos* b);
void SetPoohPalette(struct PoohWork* w, u32 b);

#endif
