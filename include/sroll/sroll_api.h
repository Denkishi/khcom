#ifndef GUARD_SROLL_API_H
#define GUARD_SROLL_API_H

#include "types.h"

struct SrollInit;
struct Task;
struct SrollWork;

void SrollBCharSetMotion(struct Task* task, s32 v);
s32 SrollTextMeasureWidth(struct SrollWork* w, const u8* s);
void SrollTextSelectFont(struct SrollWork* w, u32 mode);
void SrollTextInit(struct SrollWork* w, const struct SrollInit* a);
void SrollTextSetColors(struct SrollWork* w, u16 a, u16 b, u16 c, u16 d);
void SrollTextClearRect(struct SrollWork* w, u16 x, u16 y, u16 cw, u16 ch, u8 flush);
void SrollTextDrawStringAtPixelX(struct SrollWork* w, u16 x, u16 y, u8* s, u8 flush);
void ScanlineDmaReset();
void ScanlineDmaInit(vu16* dst, void* src, u32 cnt);
void ScanlineDmaQueueBuffer(void* src);
void ScanlineDmaEnable();
void ScanlineDmaDisable();
void BlockAudioStart();
void BlockAudioUpdate();
void BlockAudioStop();

s32* GetDecodedAudioBuffer();
s32 GetDecodedAudioReadPosition();
void SetDecodedAudioReadPosition(s32 pos);

#endif
