#ifndef GUARD_DISPLAY_H
#define GUARD_DISPLAY_H

#include "types.h"

void SetBgMode0();
void SetBgMode1();
void SetBgMode2();
void SetBgMode3();
void EnableBg(s32 bg);
void DisableBg(s32 bg);
void SetupBg(s32 bg, u8 charBase, u8 screenBase, u8 palette);
void LoadBgTiles(s32 bg, void* src, u16 size);
void LoadBgPalette(s32 bg, void* src, u16 size);
void LoadBgMap(s32 bg, const void* src, u16 size);
void* GetBgCharBase(s32 bg);
void* GetBgScreenBase(s32 bg);
void SetBgScroll(s32 bg, s32 x, s32 y);
void SetBgPriority(s32 bg, u16 priority);
u8 RequestDma3Copy(const void* src, void* dst, u16 size);
void LoadPalette(const void* src, void* dst, u16 size);
void LoadObjPaletteBank(u16 bank, void* src);
void SetBlendAlpha(u16 a, u16 b);

void SetBackdropColor(u32 r, u32 g, u32 b);
void SetBgBlend(s32 bg, u16 a, u16 b);
void SetBgSize(s32 bg, u16 size);
void SetBgAffine(s32 bg, u8 rot, s32 sx, s32 sy, s32 dx, s32 dy);
void SetBgMapBlocks(s32 bg, const void* src, u8 w, u8 h);
void RedrawBgMapAt(s32 bg, u16 x, u16 y);
void ScrollBgMapTo(s32 bg, u16 x, u16 y);
void SetBgColorMode(s32 bg, u16 mode);
void SetBgOverflow(s32 bg, u8 on);
void SetObjMosaicSize(u8 x, u8 y);

#ifdef VERSION_EU
void eu_080059D4(s32 bg, void* src);
void eu_080059F4(s32 bg, void* src);
#endif

struct BgAnimationDef;

void MosaicReset();
void BgAnimSetTransform(u8 a, s32 b, s32 c);
void BgAnimSetLoopStartFrame(u16 a);
void BgAnimStop();
void MosaicStartIn(u16 frames, u16 size);
void MosaicStartOut(u16 frames, u16 size);
u8 MosaicIsActive();
u8 BgAnimIsStopped();
void BgAnimGetFrameState(u16* a, u16* b);
u32 BgAnimGetDuration(struct BgAnimationDef* p);
struct BgAnimationDef* BgAnimGetCurrent();
void VTransReset();
void BgReset();
u8 RequestTilemapRectCopy(void* src, void* dst, u8 x, u8 y, u8 w, u8 h, s8 sw, s8 sh);
void BgAnimSetPosition(s16 x, s16 y);
void BgAnimUpdate();
void BgAnimInit(s32 bg, u16 b, u16 c);
void BgAnimStart(struct BgAnimationDef* a, s32 x, s32 y);
u8 RequestDma3Clear(void* a, u16 b);

#ifdef VERSION_EU
u8 eu_08005A1C(s32 bg, const void* src, u8 w, u8 h);
void eu_08005ADC(s32 bg);
#endif

struct BgWork;
struct FadeWork;

extern u16 gLastBackdropColor;
extern u8 gBgPaletteBank[4];
extern struct BgWork* gBgWork;
extern u16 gBackdropColor;
extern u16 gBg2Cnt;
extern u16 gBg3PB;
extern u16 gBg3VOfs;
extern u16 gBg3PA;
extern u16 gWin1V;
extern u16 gWin1H;
extern u32 gBg2Y;
extern u16 gBg2PB;
extern u16 gBg0VOfs;
extern vu16 gDispCnt;
extern u16 gBg3PC;
extern u16 gBg1Cnt;
extern u16 gBg0Cnt;
extern u16 gBg2PA;
extern u16 gBg2PC;
extern u16 gWin0V;
extern u16 gBldY;
extern u16 gBg2HOfs;
extern u32 gBg3X;
extern vu16 gMosaic;
extern u32 gBg2X;
extern u16 gWin0H;
extern u16 gBg2VOfs;
extern u16 gBg1HOfs;
extern u16 gBg3Cnt;
extern u16 gBg3PD;
extern u16 gBg0HOfs;
extern u16 gWinOut;
extern u16 gBg2PD;
extern u16 gWinIn;
extern u16 gBldCnt;
extern u16 gBg1VOfs;
extern u16 gBg3HOfs;
extern u32 gBg3Y;
extern vu16 gBldAlpha;
extern struct FadeWork* gFadeWork;

void CommitDisplayRegs();
void FlushDma3Queue();
u8 QueueVTransCallback(void (*a)());
void FlushDma3QueueWithCpu();
void MosaicUpdate();
void SortSprites();

#endif
