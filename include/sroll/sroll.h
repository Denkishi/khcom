#ifndef GUARD_SROLL_H
#define GUARD_SROLL_H

#include "registration_data.h"
#include "system_state.h"

#include "evt_object_types.h"

#include "obj.h"

#include "anim.h"
#include "obj_api.h"
#include "engine.h"
#include "gba/syscall.h"
#include "main.h"
#include "types.h"
#include "taskpool.h"

struct EvtObjParam;

typedef struct DmaStream {
    u8 enabled;
    u8 swapPending;
    u8 unk_02[0x2];
    void (*update)(void);
    vu16* dst;
    s32 srcIdx;
    u8* src[2];
    u8* dmaSrc;
    u32 cnt;
} DmaStream;

typedef struct SrollShift {
    u32 shift;
    u32 spillShift;
} SrollShift;

typedef struct SrollMask {
    u32 keepLeft;
    u32 keepNext;
    u32 keepRight;
} SrollMask;

typedef struct SrollBlit {
    s32 x;
    s32 width;
    u8* src;
    u32* dst;
    u32* colors;
    u32 buf[32];
} SrollBlit;

typedef struct SrollANameWork {
    u16 unk_00;
    s16 kind;
    s16 timer;
    u8 unk_06[0x2];
    s32 x;
    s32 y;
    s32 targetX;
    s32 targetY;
    void* tiles;
    ObjPalette* palette;
    AnimState anim;
} SrollANameWork;

typedef struct SrollANameArg {
    s16 kind;
    u16 unk_02;
    u16 nameIndex;
    u8 unk_06[0x2];
    s32 x;
    s32 y;
    s32 targetX;
    s32 targetY;
} SrollANameArg;

typedef struct SrollBCharWork {
    s32 motion;
    s32 motionTimer;
    EvtObj* obj;
    void* tiles;
    ObjPalette* palette;
    AnimState anim;
    TaskPool tasks;
} SrollBCharWork;

typedef struct SrollBLogoWork {
    s32 x;
    s32 y;
    s32* scrollY;
    s32 scrollSpeed;
    void* tiles;
    ObjPalette* palette;
    AnimState anim;
} SrollBLogoWork;

typedef struct SrollBLogoArg {
    s32 x;
    s32 y;
    s32* scrollY;
    s32 scrollSpeed;
    u16 animId;
} SrollBLogoArg;

typedef struct SrollBSecnWork {
    s32 unk_00;
    s32 x;
    s32 y;
    s32* scrollY;
    s32 scrollSpeed;
    void* tiles;
    ObjPalette* palette;
    AnimState anim;
    AnimState anim2;
} SrollBSecnWork;

typedef struct SrollBSecnArg {
    s32 index;
    s32 x;
    s32 y;
    s32* scrollY;
    s32 scrollSpeed;
} SrollBSecnArg;

typedef struct SrollBCrtnWork {
    s32 timer;
    u16 kind;
    u8 unk_06[0x2];
    s32 x;
    s32 y;
    void* tiles;
    ObjPalette* palette;
    AnimState anim;
} SrollBCrtnWork;

typedef struct SrollCCharWork {
    s32 unk_00;
    u8 unk_04[0x14];
    void* tiles;
    ObjPalette* palette;
    AnimState anim[5];
} SrollCCharWork;

typedef struct SrollBCrtnArg {
    u16 kind;
    u8 unk_02[0x2];
    s32 x;
    s32 y;
} SrollBCrtnArg;

typedef struct SrollTmrWork {
    u8 visible;
    u8 unk_01[0x3];
    s32 frameCount;
    void* tiles;
    ObjPalette* palette;
} SrollTmrWork;

typedef struct SrollInit {
    u32 unk_00;
    u32 font;
    u16 clearTile;
    u16 frameTileBase;
    u16 textTileBase;
    u8 unk_0E[0x2];
    u8* unk_10;
    u8* tilemapBuffer;
    u8* tileData;
    u8* tilemap;
    u16 fgColor;
    u16 shadowColor;
    u16 bgColor;
    u16 edgeColor;
    u32 frameStyle;
    u16 windowX;
    u16 windowY;
    u16 windowWidth;
    u16 windowHeight;
    u16 textX;
    u16 textY;
    u16 textWidth;
    u16 textHeight;
} SrollInit;

typedef struct SrollFont {
    u16 bpp;
    u16 height;
    u8* pages;
    u8* glyphs;
    u8* widths;
    u32 glyphCount;
    u8 unk_14;
} SrollFont;

typedef struct SrollWork {
    u16 flags;
    u16 fgColor;
    u16 shadowColor;
    u16 bgColor;
    u16 edgeColor;
    u16 mapWidth;
    u32 frameStyle;
    u16 windowX;
    u16 windowY;
    u16 windowWidth;
    u16 windowHeight;
    u16 textX;
    u16 textY;
    u16 textWidth;
    u16 textHeight;
    u16 x;
    u16 y;
    u16 glyphHeight;
    u16 glyphBpp;
    u16 writeIdx;
    u16 readIdx;
    u16 clearTile;
    u16 frameTileBase;
    u16 textTileBase;
    u16 unk_32;
    u8* fontPages;
    u8* fontGlyphs;
    u8* fontWidths;
    u32 fontGlyphCount;
    u8 unk_44;
    u8 unk_45[0x3];
    u8* unk_48;
    u8* tilemapBuffer;
    u8* tileData;
    u8* tilemap;
    u16 charQueue[0x100];
} SrollWork;

extern void* gUnk_09A54218[][2];

extern void* const gSrollSecnSprites[][4];
extern const s32 gSrollBCharSwayOffsets[16];
extern const s32 gSrollBCharHopOffsets[16];
extern SrollShift gUnk_09A54C78[];
extern SrollMask gUnk_09A54918[][8];
extern void (*gUnk_09A54CB8[])(u32*, u8*, u32*, s32);
extern void (*gUnk_09A54CDC[])(u32*, u8*, u32*, s32);
extern u8 gUnk_05000220[];
extern u8 gUnk_08F69BE4[];
extern u8 gFEventTiles[];
extern u8 gUnk_09C8D47A[];
extern u8 gUnk_09C8F1FA[];
extern u8 gUnk_09D6CF34[];
extern u8 gUnk_09D6CF54[];
extern u8 gUnk_09D6D034[];
extern u8 gUnk_09D6D114[];
extern const SrollFont gUnk_09A5B440[];
extern const u16 gUnk_09A5B470[];
extern u32 gBlockAudioData[];

void task_sroll_a_name_0(SrollANameWork* w, SrollANameArg* a);
void task_sroll_a_name_2(SrollANameWork* w);
void task_sroll_a_name_3(SrollANameWork* w);
void task_sroll_b_char_3(SrollBCharWork* w);
void task_sroll_b_crtn_3(SrollBCrtnWork* w);
void task_sroll_c_char_3(SrollCCharWork* w);
u8 task_sroll_a_name_1(SrollANameWork* w);
void task_sroll_b_crtn_0(SrollBCrtnWork* w, SrollBCrtnArg* a);
u8 task_sroll_b_crtn_1(SrollBCrtnWork* w);
void task_sroll_b_crtn_2(SrollBCrtnWork* w);
void task_sroll_b_logo_3(SrollBLogoWork* w);
void task_sroll_b_char_0(SrollBCharWork* w, struct EvtObjParam* a);
s32 task_sroll_b_char_1(SrollBCharWork* w);
void task_sroll_b_char_2(SrollBCharWork* w);
void task_sroll_b_logo_0(SrollBLogoWork* w, SrollBLogoArg* a);
void SrollBCharChangeAnim(SrollBCharWork* w);
void task_sroll_c_char_0(SrollCCharWork* w, s32 kind);
void SrollTextClearWindowImmediate(SrollWork* w);
void SrollTextClearWindow(SrollWork* w, u8 flush);
void SrollTextResetWindow(SrollWork* w, u8 flush);
u8* SrollTextEnqueueString(SrollWork* w, u8* s);
u8 SrollTextProcessNextChar(SrollWork* w);
void SrollTextDrawQueued(SrollWork* w, u8 flush);
void SrollTextFlushTilemap(SrollWork* w);
void SrollTextDrawString(SrollWork* w, u8* s, u8 flush);
void SrollTextDrawStringAtTile(SrollWork* w, u16 x, u16 y, u8* s, u8 flush);
u8* SrollTextGetTilemap(SrollWork* w);
u8 task_sroll_b_logo_1(SrollBLogoWork* w);
void task_sroll_b_logo_2(SrollBLogoWork* w);
void task_sroll_b_secn_0(SrollBSecnWork* w, SrollBSecnArg* a);
u8 task_sroll_b_secn_1(SrollBSecnWork* w);
void task_sroll_b_secn_2(SrollBSecnWork* w);
void task_sroll_b_secn_3(SrollBSecnWork* w);
u8 task_sroll_c_char_1(SrollCCharWork* w);
void task_sroll_c_char_2(SrollCCharWork* w);
void task_sroll_tmr_0(SrollTmrWork* w, void* arg);
u8 task_sroll_tmr_1(SrollTmrWork* w);
void VBlankIntrBlockAudio(void);
void func_081154A0(u32* dst, u8* src, u32* pal, s32 x);
void func_081154EC(u32* dst, u8* src, u32* pal, s32 x);
void func_08115548(u32* dst, u8* src, u32* pal, s32 x);
void func_081155B0(u32* dst, u8* src, u32* pal, s32 x);
void func_08115628(u32* dst, u8* src, u32* pal, s32 x);
void func_081156AC(u32* dst, u8* src, u32* pal, s32 x);
void func_08115740(u32* dst, u8* src, u32* pal, s32 x);
void func_081159B0(u32* dst, u16* src, u32* pal, s32 x);
void func_081159FC(u32* dst, u16* src, u32* pal, s32 x);
void func_08115A5C(u32* dst, u16* src, u32* pal, s32 x);
u32 SrollTextBlit1bpp(SrollBlit* w);
u32 SrollTextBlit2bpp(SrollBlit* w);
void task_sroll_tmr_2(SrollTmrWork* w);
void task_sroll_tmr_3(SrollTmrWork* w);
u16 ParseLowercaseHexDigit(u16 c);
void SrollTextDrawNextGlyph(SrollWork* w, u8 flush);
void SrollTextClearTextArea(SrollWork* w);
u32 SrollTextBlitGlyph(SrollWork* w, u32* dst, u8* src, s32 width);
void SrollTextDrawFrame(SrollWork* w);
void SrollTextDrawFrameTailLeft(SrollWork* w);
void SrollTextDrawFrameTailRight(SrollWork* w);
u16 SrollTextGetGlyphIndex(u16 c, u8* font);
u8 SrollTextGetGlyphWidth(u16 c, u8* font, u8* widths, u32 count);
u8* SrollTextGetGlyphAddress(u16 c, u8* font, u8* base, u16 a, u16 b);
void SrollTextClearQueue(SrollWork* w);
u8 SrollTextQueueIsEmpty(SrollWork* w);
void SrollTextEnqueueChar(SrollWork* w, u16 c);
u16 SrollTextDequeueChar(SrollWork* w);
void SrollTextSetCursorTile(SrollWork* w, u16 x, u16 y);
void SrollTextSetCursorPixelX(SrollWork* w, u16 x);
u16 SrollTextMapSingleByteChar(u8 c);
void ScanlineDmaUpdate(void);
void ScanlineDmaPrime32Bit(void);
void ScanlineDmaPrime16Bit(void);
void BlockAudioVBlank(void);
u16 GetBlockAudioSampleRate(void);
u32* GetBlockAudioData(void);
u8* ReadNextAudioBlock(u32** p);
s32 AudioBlockStreamInit(u32* src);
s32 AudioBlockStreamUpdate(void);

#endif /* GUARD_SROLL_H */
