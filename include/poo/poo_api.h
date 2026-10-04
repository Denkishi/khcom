#ifndef GUARD_POO_API_H
#define GUARD_POO_API_H

#include "types.h"
#include "pooh_actor_types.h"

struct PooPos;

extern const PooHitBox gPoohHitBox;

void SetPoohAction(struct PoohWork* w, u32 b);
void func_080CA35C();
void func_080CA368(s32 a, u16 b, u16 c);
void MovePooCamera(s32 a, s32 b);
void InitPooNodes();
void ClearPooPrizesDropped();
void InitPooState();
void SetPooStatePooh(struct PooPos* p, s32 b);
void SetPooStatePos2(struct PooPos* p);
u8 IsPooEventDone(s32 a);
void SetPooFlag(s32 a);
u8 IsPooFlagSet(s32 a);
void GetPooState(void* p);
void SetPooState(const void* p);
u8 IsPooAltImageActive();
void FreePoohInteractions();
void InitPoohInteractions();
void AllmapVCountCallback();
void AllmapCyclePalette();
void AllmapLoadWorldBg();
void AllmapLoadFloorTiles();

struct PooNode;

extern u8 gPooAttackActive;
extern s32 gPoohRequestX;
extern u16 gPoohGaugeTimer;
extern u16 gPoohGauge;
extern s32 gPoohRequestY;
extern struct PooPos* gPoohPos;
extern u32 gPoohRequest;
extern u32 gUnk_0203C3F4;
extern u16 gPooScrollY;
extern s32 gPooCameraX;
extern s32 gPooCameraFocusY;
extern s32 gPooCameraFocusX;
extern s32 gPooCameraY;
extern u16 gPooScrollX;
extern struct PooNode* gPooSoraNode;
extern void* gPooSoraCollider;
extern PooActor gPooActor;
extern void* gStockMesDispWork;
extern PooState gPooState;
extern void* gSharedModeWork;

#endif
