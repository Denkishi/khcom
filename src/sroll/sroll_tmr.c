#include "audio_block_codec.h"
#include "pcm_audio.h"
#include "m4a.h"
#include "sroll.h"
#include "sprites_staff_roll.h"
#include "gba/io_reg.h"
#include "gba/keys.h"
#include "sroll_api.h"
#include "fade.h"
#include <stddef.h>
#include "display.h"
#include "gba/macro.h"
#include "gba/syscall.h"
#include "intr.h"
#include "key.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"

static DmaStream sDmaStream;
static u8 sBlockAudioPlaying;
static s32 sDecodedAudioBuffer[0x810];
static u32* sAudioBlockNext;
static s32 sDecodedAudioWritePosition;
static s32 sDecodedAudioReadPosition;

static s32 Square(s32 x) {
    return x * x;
}

void task_sroll_tmr_0(SrollTmrWork* w, void* arg) {
    w->visible = 0;
    w->frameCount = 0;
    w->tiles = LoadObjTiles(gUnk_09C904B4, 352);
    w->palette = LoadObjPalette(gUnk_09D6D114, 32);
}

u8 task_sroll_tmr_1(SrollTmrWork* w) {
    u8 r;

    r = 1;

    if (GetKeysPressed() & SELECT_BUTTON) {
        if (w->visible == 1) {
            w->visible = 0;
        } else {
            w->visible = r;
        }
    }

    FadeSetPaletteExcluded((w->palette->index & 15) + 16, 1);
    w->frameCount++;
    return r;
}

void task_sroll_tmr_2(SrollTmrWork* w) {
    s32 t;
    u16 h;
    u16 m;
    u16 s;
    u16 z;

    if (w->visible == 0) {
        return;
    }

    t = w->frameCount;
    h = t / 3600;
    m = t / 60 % 60;
    s = t % 60;
    z = 0;
    DrawSprite(8, 8, gUnk_09EFBAE8[h / 10 % 10], w->tiles, w->palette, NULL, z, z);
    DrawSprite(16, 8, gUnk_09EFBAE8[h % 10], w->tiles, w->palette, NULL, z, z);
    DrawSprite(24, 8, gUnk_09EFBAE8[10], w->tiles, w->palette, NULL, z, z);
    DrawSprite(32, 8, gUnk_09EFBAE8[m / 10], w->tiles, w->palette, NULL, z, z);
    DrawSprite(40, 8, gUnk_09EFBAE8[m % 10], w->tiles, w->palette, NULL, z, z);
    DrawSprite(48, 8, gUnk_09EFBAE8[10], w->tiles, w->palette, NULL, z, z);
    DrawSprite(56, 8, gUnk_09EFBAE8[s / 10], w->tiles, w->palette, NULL, z, z);
    DrawSprite(64, 8, gUnk_09EFBAE8[s % 10], w->tiles, w->palette, NULL, z, z);
}

void task_sroll_tmr_3(SrollTmrWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void func_0811549C() {
}

void func_081154A0(u32* dst, u8* src, u32* pal, s32 x) {
    SrollShift* t;
    s32 i;
    u32 v;
    u32 c;

    t = &gUnk_09A54C78[x];

    for (i = 0; i <= 7; i++) {
        c = src[i] << 24;
        v = pal[(c >> 31) & 1];
        dst[i] |= v << t->shift;
        dst[i + 8] |= v >> t->spillShift;
    }
}

void func_081154EC(u32* dst, u8* src, u32* pal, s32 x) {
    SrollShift* t;
    s32 i;
    u32 v;
    u32 c;

    t = &gUnk_09A54C78[x];

    for (i = 0; i <= 7; i++) {
        c = src[i] << 24;
        v = pal[(c >> 31) & 1];
        v |= pal[(c >> 30) & 1] << 4;
        dst[i] |= v << t->shift;
        dst[i + 8] |= v >> t->spillShift;
    }
}

void func_08115548(u32* dst, u8* src, u32* pal, s32 x) {
    SrollShift* t;
    s32 i;
    u32 v;
    u32 c;

    t = &gUnk_09A54C78[x];

    for (i = 0; i <= 7; i++) {
        c = src[i] << 24;
        v = pal[(c >> 31) & 1];
        v |= pal[(c >> 30) & 1] << 4;
        v |= pal[(c >> 29) & 1] << 8;
        dst[i] |= v << t->shift;
        dst[i + 8] |= v >> t->spillShift;
    }
}

void func_081155B0(u32* dst, u8* src, u32* pal, s32 x) {
    SrollShift* t;
    s32 i;
    u32 v;
    u32 c;

    t = &gUnk_09A54C78[x];

    for (i = 0; i <= 7; i++) {
        c = src[i] << 24;
        v = pal[(c >> 31) & 1];
        v |= pal[(c >> 30) & 1] << 4;
        v |= pal[(c >> 29) & 1] << 8;
        v |= pal[(c >> 28) & 1] << 12;
        dst[i] |= v << t->shift;
        dst[i + 8] |= v >> t->spillShift;
    }
}

void func_08115628(u32* dst, u8* src, u32* pal, s32 x) {
    SrollShift* t;
    s32 i;
    u32 v;
    u32 c;

    t = &gUnk_09A54C78[x];

    for (i = 0; i <= 7; i++) {
        c = src[i] << 24;
        v = pal[(c >> 31) & 1];
        v |= pal[(c >> 30) & 1] << 4;
        v |= pal[(c >> 29) & 1] << 8;
        v |= pal[(c >> 28) & 1] << 12;
        v |= pal[(c >> 27) & 1] << 16;
        dst[i] |= v << t->shift;
        dst[i + 8] |= v >> t->spillShift;
    }
}

void func_081156AC(u32* dst, u8* src, u32* pal, s32 x) {
    SrollShift* t;
    s32 i;
    u32 v;
    u32 c;

    t = &gUnk_09A54C78[x];

    for (i = 0; i <= 7; i++) {
        c = src[i] << 24;
        v = pal[(c >> 31) & 1];
        v |= pal[(c >> 30) & 1] << 4;
        v |= pal[(c >> 29) & 1] << 8;
        v |= pal[(c >> 28) & 1] << 12;
        v |= pal[(c >> 27) & 1] << 16;
        v |= pal[(c >> 26) & 1] << 20;
        dst[i] |= v << t->shift;
        dst[i + 8] |= v >> t->spillShift;
    }
}

void func_08115740(u32* dst, u8* src, u32* pal, s32 x) {
    SrollShift* t;
    s32 i;
    u32 v;
    u32 c;

    t = &gUnk_09A54C78[x];

    for (i = 0; i <= 7; i++) {
        c = src[i] << 24;
        v = pal[(c >> 31) & 1];
        v |= pal[(c >> 30) & 1] << 4;
        v |= pal[(c >> 29) & 1] << 8;
        v |= pal[(c >> 28) & 1] << 12;
        v |= pal[(c >> 27) & 1] << 16;
        v |= pal[(c >> 26) & 1] << 20;
        v |= pal[(c >> 25) & 1] << 24;
        dst[i] |= v << t->shift;
        dst[i + 8] |= v >> t->spillShift;
    }
}

void func_081157E0(u32* dst, u8* src, u32* pal, s32 x) {
    SrollShift* t;
    s32 i;
    u32 v;

    t = &gUnk_09A54C78[x];

    for (i = 0; i <= 7; i++) {
        v = pal[(src[i] >> 7) & 1];
        v |= pal[(src[i] >> 6) & 1] << 4;
        v |= pal[(src[i] >> 5) & 1] << 8;
        v |= pal[(src[i] >> 4) & 1] << 12;
        v |= pal[(src[i] >> 3) & 1] << 16;
        v |= pal[(src[i] >> 2) & 1] << 20;
        v |= pal[(src[i] >> 1) & 1] << 24;
        v |= pal[src[i] & 1] << 28;
        dst[i] |= v << t->shift;
        dst[i + 8] |= v >> t->spillShift;
    }
}

u32 SrollTextBlit1bpp(SrollBlit* w) {
    SrollMask* m;
    u32* d;
    u32* p;
    u32 k;
    s32 e;
    u32 r;

    e = w->x + w->width;
    p = w->buf;
    d = w->dst;
    m = &gUnk_09A54918[w->width][w->x];
    k = m->keepLeft | m->keepRight;
    p[0] = d[0] & k;
    p[1] = d[1] & k;
    p[2] = d[2] & k;
    p[3] = d[3] & k;
    p[4] = d[4] & k;
    p[5] = d[5] & k;
    p[6] = d[6] & k;
    p[7] = d[7] & k;

    if (e > 8) {
        k = m->keepNext;
        p[8] = d[8] & k;
        p[9] = d[9] & k;
        p[10] = d[10] & k;
        p[11] = d[11] & k;
        p[12] = d[12] & k;
        p[13] = d[13] & k;
        p[14] = d[14] & k;
        p[15] = d[15] & k;
    }

    gUnk_09A54CB8[w->width](p, w->src, w->colors, w->x);
    d[0] = p[0];
    d[1] = p[1];
    d[2] = p[2];
    d[3] = p[3];
    d[4] = p[4];
    d[5] = p[5];
    d[6] = p[6];
    d[7] = p[7];

    if (e > 8) {
        d[8] = p[8];
        d[9] = p[9];
        d[10] = p[10];
        d[11] = p[11];
        d[12] = p[12];
        d[13] = p[13];
        d[14] = p[14];
        d[15] = p[15];
    }

    r = 1;

    if (e > 8) {
        r = 2;
    }

    return r;
}

void func_081159AC() {
}

void func_081159B0(u32* dst, u16* src, u32* pal, s32 x) {
    SrollShift* t;
    u32* d;
    u16* s;
    s32 i;
    u32 v;
    u32 c;

    t = &gUnk_09A54C78[x];
    d = dst;
    s = src;

    for (i = 0; i <= 7; i++) {
        c = *s << 16;
        v = pal[(c >> 22) & 3];
        d[0] |= v << t->shift;
        d[8] |= v >> t->spillShift;
        d++;
        s++;
    }
}

void func_081159FC(u32* dst, u16* src, u32* pal, s32 x) {
    SrollShift* t;
    s32 i;
    u32 v;
    u32 c;

    t = &gUnk_09A54C78[x];

    for (i = 0; i <= 7; i++) {
        c = src[i] << 16;
        v = pal[(c >> 22) & 3];
        v |= pal[(c >> 20) & 3] << 4;
        dst[i] |= v << t->shift;
        dst[i + 8] |= v >> t->spillShift;
    }
}

void func_08115A5C(u32* dst, u16* src, u32* pal, s32 x) {
    SrollShift* t;
    s32 i;
    u32 v;
    u32 c;

    t = &gUnk_09A54C78[x];

    for (i = 0; i <= 7; i++) {
        c = src[i] << 16;
        v = pal[(c >> 22) & 3];
        v |= pal[(c >> 20) & 3] << 4;
        v |= pal[(c >> 18) & 3] << 8;
        dst[i] |= v << t->shift;
        dst[i + 8] |= v >> t->spillShift;
    }
}

void func_08115AD4(u32* dst, u16* src, u32* pal, s32 x) {
    SrollShift* t;
    s32 i;
    u32 v;

    t = &gUnk_09A54C78[x];

    for (i = 0; i <= 7; i++) {
        v = pal[(src[i] >> 6) & 3];
        v |= pal[(src[i] >> 4) & 3] << 4;
        v |= pal[(src[i] >> 2) & 3] << 8;
        v |= pal[src[i] & 3] << 12;
        dst[i] |= v << t->shift;
        dst[i + 8] |= v >> t->spillShift;
    }
}

void func_08115B6C(u32* dst, u16* src, u32* pal, s32 x) {
    SrollShift* t;
    s32 i;
    u32 v;

    t = &gUnk_09A54C78[x];

    for (i = 0; i <= 7; i++) {
        v = pal[(src[i] >> 6) & 3];
        v |= pal[(src[i] >> 4) & 3] << 4;
        v |= pal[(src[i] >> 2) & 3] << 8;
        v |= pal[src[i] & 3] << 12;
        v |= pal[(src[i] >> 14) & 3] << 16;
        dst[i] |= v << t->shift;
        dst[i + 8] |= v >> t->spillShift;
    }
}

void func_08115C04(u32* dst, u16* src, u32* pal, s32 x) {
    SrollShift* t;
    s32 i;
    u32 v;

    t = &gUnk_09A54C78[x];

    for (i = 0; i <= 7; i++) {
        v = pal[(src[i] >> 6) & 3];
        v |= pal[(src[i] >> 4) & 3] << 4;
        v |= pal[(src[i] >> 2) & 3] << 8;
        v |= pal[src[i] & 3] << 12;
        v |= pal[(src[i] >> 14) & 3] << 16;
        v |= pal[(src[i] >> 12) & 3] << 20;
        dst[i] |= v << t->shift;
        dst[i + 8] |= v >> t->spillShift;
    }
}

void func_08115CAC(u32* dst, u16* src, u32* pal, s32 x) {
    SrollShift* t;
    s32 i;
    u32 v;

    t = &gUnk_09A54C78[x];

    for (i = 0; i <= 7; i++) {
        v = pal[(src[i] >> 6) & 3];
        v |= pal[(src[i] >> 4) & 3] << 4;
        v |= pal[(src[i] >> 2) & 3] << 8;
        v |= pal[src[i] & 3] << 12;
        v |= pal[(src[i] >> 14) & 3] << 16;
        v |= pal[(src[i] >> 12) & 3] << 20;
        v |= pal[(src[i] >> 10) & 3] << 24;
        dst[i] |= v << t->shift;
        dst[i + 8] |= v >> t->spillShift;
    }
}

void func_08115D60(u32* dst, u16* src, u32* pal, s32 x) {
    SrollShift* t;
    s32 i;
    u32 v;

    t = &gUnk_09A54C78[x];

    for (i = 0; i <= 7; i++) {
        v = pal[(src[i] >> 6) & 3];
        v |= pal[(src[i] >> 4) & 3] << 4;
        v |= pal[(src[i] >> 2) & 3] << 8;
        v |= pal[src[i] & 3] << 12;
        v |= pal[(src[i] >> 14) & 3] << 16;
        v |= pal[(src[i] >> 12) & 3] << 20;
        v |= pal[(src[i] >> 10) & 3] << 24;
        v |= pal[(src[i] >> 8) & 3] << 28;
        dst[i] |= v << t->shift;
        dst[i + 8] |= v >> t->spillShift;
    }
}

u32 SrollTextBlit2bpp(SrollBlit* w) {
    SrollMask* m;
    u32* d;
    u32* p;
    u32 k;
    s32 e;
    u32 r;

    e = w->x + w->width;
    p = w->buf;
    d = w->dst;
    m = &gUnk_09A54918[w->width][w->x];
    k = m->keepLeft | m->keepRight;
    p[0] = d[0] & k;
    p[1] = d[1] & k;
    p[2] = d[2] & k;
    p[3] = d[3] & k;
    p[4] = d[4] & k;
    p[5] = d[5] & k;
    p[6] = d[6] & k;
    p[7] = d[7] & k;

    if (e > 8) {
        k = m->keepNext;
        p[8] = d[8] & k;
        p[9] = d[9] & k;
        p[10] = d[10] & k;
        p[11] = d[11] & k;
        p[12] = d[12] & k;
        p[13] = d[13] & k;
        p[14] = d[14] & k;
        p[15] = d[15] & k;
    }

    gUnk_09A54CDC[w->width](p, w->src, w->colors, w->x);
    d[0] = p[0];
    d[1] = p[1];
    d[2] = p[2];
    d[3] = p[3];
    d[4] = p[4];
    d[5] = p[5];
    d[6] = p[6];
    d[7] = p[7];

    if (e > 8) {
        d[8] = p[8];
        d[9] = p[9];
        d[10] = p[10];
        d[11] = p[11];
        d[12] = p[12];
        d[13] = p[13];
        d[14] = p[14];
        d[15] = p[15];
    }

    r = 1;

    if (e > 8) {
        r = 2;
    }

    return r;
}

u16 SrollTextGetGlyphIndex(u16 c, u8* font) {
    u16 result;
    s32 off;
    s32 hi;
    s32 a;
    s32 b;
    u8 v;

    result = 0;
    off = (c & 0x7F00) >> 6;
    hi = font[off + 1] << 8;
    a = font[off] | hi;
    hi = font[off + 3] << 8;
    b = font[off + 2] | hi;

    if (a != 0xFFFF) {
        if (font[(u16)(a + 0xFFC0 + (c & 0xFF))] != 0xFF) {
            v = font[(u16)(a + 0xFFC0 + (c & 0xFF))];
            result = b + v;
        }
    }

    return result;
}

u8 SrollTextGetGlyphWidth(u16 c, u8* font, u8* widths, u32 count) {
    u8 w;

    w = 0;

    if (widths != NULL) {
        u16 idx = SrollTextGetGlyphIndex(c, font);

        if (idx < count) {
            w = widths[idx];
        }
    }

    if (w == 0) {
        w = 8;
    }

    return w;
}

s32 SrollTextMeasureWidth(SrollWork* w, u8* s) {
    s32 total;
    u16 c;
    s32 hi;

    total = 0;

    while (*s != 0) {
        if (*s & 0x80) {
            hi = s[0] << 8;
            c = s[1] | hi;
            s += 2;
        } else {
            c = SrollTextMapSingleByteChar(s[0]);
            s += 1;
        }

        total += SrollTextGetGlyphWidth(c, w->fontPages, w->fontWidths, w->fontGlyphCount);
    }

    return total;
}

u8* SrollTextGetGlyphAddress(u16 c, u8* font, u8* base, u16 a, u16 b) {
    return base + SrollTextGetGlyphIndex(c, font) * (a << 3) * b;
}

u32 SrollTextBlitGlyph(SrollWork* w, u32* dst, u8* src, s32 width) {
    SrollBlit b;
    u32 pal[16];
    u32 bg;
    u32 r;
    u16 c;
    u16 n;

    r = 0;
    pal[0] = c = w->bgColor;
    pal[1] = w->fgColor;
    pal[2] = w->shadowColor;
    pal[3] = w->edgeColor;
    bg = (c << 4) | c;
    bg |= bg << 8;
    bg |= bg << 16;
    b.x = w->x & 7;
    b.width = width;
    b.src = src;
    b.dst = dst;
    b.colors = pal;
    n = w->glyphHeight;

    if (n-- != 0) {
        do {
            if (b.x == 0) {
                CpuFastFill(bg, b.dst, 32);
            }

            switch (w->glyphBpp) {
            case 1:
                r = SrollTextBlit1bpp(&b);
                break;
            case 2:
                r = SrollTextBlit2bpp(&b);
                break;
            }

            b.src += w->glyphBpp * 8;
            b.dst += w->textWidth * 8;
        } while (n-- != 0);
    }

    return r;
}

void SrollTextSelectFont(SrollWork* w, u32 mode) {
    if (mode > 1) {
        mode = 0;
    }

    w->glyphBpp = gUnk_09A5B440[mode].bpp;
    w->glyphHeight = gUnk_09A5B440[mode].height;
    w->fontPages = gUnk_09A5B440[mode].pages;
    w->fontGlyphs = gUnk_09A5B440[mode].glyphs;
    w->fontWidths = gUnk_09A5B440[mode].widths;
    w->fontGlyphCount = gUnk_09A5B440[mode].glyphCount;
    w->unk_44 = gUnk_09A5B440[mode].unk_14;
    SrollTextSetCursorTile(w, w->x, w->y);
}

void SrollTextInit(SrollWork* w, SrollInit* a) {
    SrollTextSelectFont(w, a->font);
    SrollTextSetColors(w, a->fgColor, a->shadowColor, a->bgColor, a->edgeColor);
    w->mapWidth = 32;
    w->flags = 0;
    w->frameStyle = a->frameStyle;
    w->windowX = a->windowX;
    w->windowY = a->windowY;
    w->windowWidth = a->windowWidth;
    w->windowHeight = a->windowHeight;
    w->textX = a->textX;
    w->textY = a->textY;
    w->textWidth = a->textWidth;
    w->textHeight = a->textHeight;
    w->clearTile = a->clearTile;
    w->frameTileBase = a->frameTileBase;
    w->textTileBase = a->textTileBase;
    w->unk_48 = a->unk_10;
    w->tilemapBuffer = a->tilemapBuffer;
    w->tileData = a->tileData;
    w->tilemap = a->tilemap;
    SrollTextClearQueue(w);
    SrollTextResetWindow(w, 1);
}

void SrollTextClearWindowImmediate(SrollWork* w) {
    SrollTextClearWindow(w, 1);
}

void SrollTextClearQueue(SrollWork* w) {
    w->writeIdx = 0;
    w->readIdx = 0;
}

u8 SrollTextQueueIsEmpty(SrollWork* w) {
    u8 r;

    r = 0;

    if (w->writeIdx == w->readIdx) {
        r = 1;
    }

    return r;
}

void SrollTextEnqueueChar(SrollWork* w, u16 c) {
    w->charQueue[w->writeIdx] = c;
    w->writeIdx = (w->writeIdx + 1) & 0xFF;
}

u16 SrollTextDequeueChar(SrollWork* w) {
    u16 c;

    if (w->writeIdx == w->readIdx) {
        return 0;
    }

    c = w->charQueue[w->readIdx];
    w->readIdx = (w->readIdx + 1) & 0xFF;
    return c;
}

void SrollTextSetCursorTile(SrollWork* w, u16 x, u16 y) {
    if (x >= w->textWidth) {
        x = 0;
    }

    if (y + w->glyphHeight > w->textHeight) {
        y = 0;
    }

    w->x = x * 8;
    w->y = y;
}

void SrollTextSetCursorPixelX(SrollWork* w, u16 x) {
    if (x >= w->textWidth * 8) {
        x = 0;
    }

    w->x = x;
}

void SrollTextSetColors(SrollWork* w, u16 a, u16 b, u16 c, u16 d) {
    w->fgColor = a;
    w->shadowColor = b;
    w->bgColor = c;
    w->edgeColor = d;
}

void SrollTextClearWindow(SrollWork* w, u8 flush) {
    u16* p;
    u16 i;

    p = (u16*)(SrollTextGetTilemap(w) + w->windowY * w->mapWidth * 2 + w->windowX * 2);

    for (i = 0; i < w->windowHeight; i++) {
        CpuFill16(w->clearTile, p, w->windowWidth * 2);
        p += w->mapWidth;
    }

    if (flush == 1) {
        SrollTextFlushTilemap(w);
    }
}

void SrollTextDrawFrame(SrollWork* w) {
    u16* p;
    u16 i;
    u16 t;

    p = (u16*)(SrollTextGetTilemap(w) + w->windowY * w->mapWidth * 2 + w->windowX * 2);
    t = w->frameTileBase + 1;
    CpuFill16(t + 2, p + 1, (u32)(w->windowWidth - 2) << 1);
    p[0] = t + 1;
    p[w->windowWidth - 1] = t + 3;
    p += w->mapWidth;

    for (i = 1; i < w->windowHeight - 1; i++) {
        CpuFill16(t, p + 1, (u32)(w->windowWidth - 2) << 1);
        p[0] = t + 4;
        p[w->windowWidth - 1] = t + 5;
        p += w->mapWidth;
    }

    CpuFill16(t + 7, p + 1, (u32)(w->windowWidth - 2) << 1);
    p[0] = t + 6;
    p[w->windowWidth - 1] = t + 8;
}

void SrollTextDrawFrameTailLeft(SrollWork* w) {
    u16* p;
    u16 i;
    u16 t;

    p = (u16*)(SrollTextGetTilemap(w) + w->windowY * w->mapWidth * 2 + w->windowX * 2);
    t = w->frameTileBase + 1;
    CpuFill16(t + 2, p + 2, (u32)(w->windowWidth - 3) << 1);
    p[1] = t + 1;
    p[w->windowWidth - 1] = t + 3;
    p += w->mapWidth;

    for (i = 1; i < w->windowHeight - 2; i++) {
        CpuFill16(t, p + 2, (u32)(w->windowWidth - 3) << 1);
        p[1] = t + 4;
        p[w->windowWidth - 1] = t + 5;
        p += w->mapWidth;
    }

    CpuFill16(t, p + 2, (u32)(w->windowWidth - 3) << 1);
    p[0] = t + 10;
    p[1] = t + 11;
    p[w->windowWidth - 1] = t + 5;
    p += w->mapWidth;

    CpuFill16(t + 7, p + 2, (u32)(w->windowWidth - 3) << 1);
    p[1] = t + 6;
    p[w->windowWidth - 1] = t + 8;
}

void SrollTextDrawFrameTailRight(SrollWork* w) {
    u16* p;
    u16 i;
    u16 t;

    p = (u16*)(SrollTextGetTilemap(w) + w->windowY * w->mapWidth * 2 + w->windowX * 2);
    t = w->frameTileBase + 1;
    CpuFill16(t + 2, p + 1, (u32)(w->windowWidth - 3) << 1);
    p[0] = t + 1;
    p[w->windowWidth - 2] = t + 3;
    p += w->mapWidth;

    for (i = 1; i < w->windowHeight - 2; i++) {
        CpuFill16(t, p + 1, (u32)(w->windowWidth - 3) << 1);
        p[0] = t + 4;
        p[w->windowWidth - 2] = t + 5;
        p += w->mapWidth;
    }

    CpuFill16(t, p + 1, (u32)(w->windowWidth - 3) << 1);
    p[0] = t + 4;
    p[w->windowWidth - 2] = (t | 0x400) + 11;
    p[w->windowWidth - 1] = (t | 0x400) + 10;
    p += w->mapWidth;

    CpuFill16(t + 7, p + 1, (u32)(w->windowWidth - 3) << 1);
    p[0] = t + 6;
    p[w->windowWidth - 2] = t + 8;
}

void SrollTextClearTextArea(SrollWork* w) {
    u16* p;
    u16 i;
    u16 t;

    p = (u16*)(SrollTextGetTilemap(w) + w->textY * w->mapWidth * 2 + w->textX * 2);
    t = w->frameTileBase + 1;

    for (i = 0; i < w->textHeight; i++) {
        CpuFill16(t, p, w->textWidth * 2);
        p += w->mapWidth;
    }
}

void SrollTextResetWindow(SrollWork* w, u8 flush) {
    u16 t;

    switch (w->frameStyle) {
    case 1:
        SrollTextDrawFrame(w);
        break;
    case 2:
        SrollTextDrawFrameTailLeft(w);
        break;
    case 3:
        SrollTextDrawFrameTailRight(w);
        break;
    default:
        SrollTextClearTextArea(w);
        break;
    }

    SrollTextSetCursorTile(w, 0, 0);

    if (flush == 1) {
        SrollTextFlushTilemap(w);
    } else {
        t = w->flags | SROLL_FLAG_TILEMAP_DIRTY;
        w->flags = t;
    }
}

void SrollTextClearRect(SrollWork* w, u16 x, u16 y, u16 cw, u16 ch, u8 flush) {
    u16* p;
    u16 i;
    u16 t;
    u16 v;

    if (x >= w->textWidth) {
        return;
    }

    if (y >= w->textHeight) {
        return;
    }

    if (x + cw > w->textWidth) {
        cw = w->textWidth - x;
    }

    if (y + ch > w->textHeight) {
        ch = w->textHeight - y;
    }

    p = (u16*)(SrollTextGetTilemap(w) + (w->textY + y) * w->mapWidth * 2 + (w->textX + x) * 2);
    v = w->frameTileBase + 1;
    i = 0;

    while (i < ch) {
        CpuFill16(v, p, (u32)(cw << 1));
        p += w->mapWidth;
        i++;
    }

    if (flush == 1) {
        SrollTextFlushTilemap(w);
    } else {
        t = w->flags | SROLL_FLAG_TILEMAP_DIRTY;
        w->flags = t;
    }
}

void func_081167CC() {
}

u16 ParseLowercaseHexDigit(u16 c) {
    u16 v;

    v = c;

    if ((u16)(v - '0') <= 9) {
        v -= '0';
    } else {
        v -= 'a';
        v += 10;
    }

    return v;
}

u8* SrollTextEnqueueString(SrollWork* w, u8* s) {
    s32 hi;

    while (*s != 0) {
        if (*s & 0x80) {
            hi = s[0] << 8;
            SrollTextEnqueueChar(w, s[1] | hi);
            s += 2;
        } else {
            SrollTextEnqueueChar(w, SrollTextMapSingleByteChar(s[0]));
            s += 1;
        }
    }

    return s + 1;
}

u8 SrollTextProcessNextChar(SrollWork* w) {
    u16 v[2];
    u16* p;
    u32 off;
    u8* g;
    u32 n;
    u16 c;
    u16 t;
    u16 i;
    u8 r;
    u8 wd;

    r = 0;

    if (w->x >= w->textWidth * 8) {
        w->x = 0;
    }

    c = SrollTextDequeueChar(w);

    if (c & 0xFF00) {
        off = (w->y * w->textWidth + (w->x >> 3)) * 32;
        g = SrollTextGetGlyphAddress(c, w->fontPages, w->fontGlyphs, w->glyphBpp, w->glyphHeight);
        wd = SrollTextGetGlyphWidth(c, w->fontPages, w->fontWidths, w->fontGlyphCount);
        n = SrollTextBlitGlyph(w, (u32*)(w->tileData + off), g, wd);
        t = w->y * w->textWidth + (w->x >> 3) + w->textTileBase;
        p = (u16*)(SrollTextGetTilemap(w) +
                   ((w->textY + w->y) * w->mapWidth + ((w->x >> 3) + w->textX)) * 2);

        for (i = 0; i < w->glyphHeight; i++) {
            if (n == 1) {
                p[0] = t;
            } else {
                p[0] = t;
                p[1] = t + 1;
            }

            p += w->mapWidth;
            t += w->textWidth;
        }

        w->x += wd;
        w->flags |= SROLL_FLAG_TILEMAP_DIRTY;
        r = 1;
    } else {
        switch (c) {
        case '@':
            v[0] = SrollTextDequeueChar(w);
            v[1] = SrollTextDequeueChar(w);

            switch (v[0]) {
            case 'F':
                SrollTextSelectFont(w, ParseLowercaseHexDigit(v[1]));
                break;
            case 'f':
                w->fgColor = ParseLowercaseHexDigit(v[1]);
                break;
            case 's':
                w->shadowColor = ParseLowercaseHexDigit(v[1]);
                break;
            case 'b':
                w->bgColor = ParseLowercaseHexDigit(v[1]);
                break;
            case 'e':
                w->edgeColor = ParseLowercaseHexDigit(v[1]);
                break;
            }

            break;
        case 0:
            break;
        case '\n':
            w->x = 0;
            w->y += w->glyphHeight;

            if (w->y + w->glyphHeight > w->textHeight) {
                w->y = 0;
            }

            break;
        }
    }

    return r;
}

void SrollTextDrawNextGlyph(SrollWork* w, u8 flush) {
    u8 r;

    r = 0;

    while (!SrollTextQueueIsEmpty(w) && r == 0) {
        r = SrollTextProcessNextChar(w);
    }

    if (flush == 1 && (w->flags & SROLL_FLAG_TILEMAP_DIRTY)) {
        SrollTextFlushTilemap(w);
    }
}

void SrollTextDrawQueued(SrollWork* w, u8 flush) {
    while (!SrollTextQueueIsEmpty(w)) {
        SrollTextProcessNextChar(w);
    }

    if (flush == 1 && (w->flags & SROLL_FLAG_TILEMAP_DIRTY)) {
        SrollTextFlushTilemap(w);
    }
}

u8* SrollTextGetTilemap(SrollWork* w) {
    u8* v;

    v = w->tilemapBuffer;

    if (v == NULL) {
        v = w->tilemap;
    }

    return v;
}

void SrollTextFlushTilemap(SrollWork* w) {
    u32 off;

    if (w->tilemapBuffer != NULL) {
        off = w->windowY * w->mapWidth * 2;
        RequestDma3Copy(w->tilemapBuffer + off, w->tilemap + off, w->windowHeight * w->mapWidth * 2);
    }

    w->flags &= ~SROLL_FLAG_TILEMAP_DIRTY;
}

void SrollTextDrawString(SrollWork* w, u8* s, u8 flush) {
    SrollTextDrawQueued(w, 0);
    SrollTextEnqueueString(w, s);
    SrollTextDrawQueued(w, 0);

    if (flush == 1 && (w->flags & SROLL_FLAG_TILEMAP_DIRTY)) {
        SrollTextFlushTilemap(w);
    }
}

void SrollTextDrawStringAtTile(SrollWork* w, u16 x, u16 y, u8* s, u8 flush) {
    SrollTextDrawQueued(w, 0);
    SrollTextSetCursorTile(w, x, y);
    SrollTextEnqueueString(w, s);
    SrollTextDrawQueued(w, 0);

    if (flush == 1 && (w->flags & SROLL_FLAG_TILEMAP_DIRTY)) {
        SrollTextFlushTilemap(w);
    }
}

void SrollTextDrawStringAtPixelX(SrollWork* w, u16 x, u16 y, u8* s, u8 flush) {
    u32 off;
    u8* g;
    s32 n;

    SrollTextDrawQueued(w, 0);
    SrollTextSetCursorTile(w, x >> 3, y);
    n = x & 7;

    if (n != 0) {
        off = (w->y * w->textWidth + (x >> 3)) * 32;
        g = SrollTextGetGlyphAddress(0x8140, w->fontPages, w->fontGlyphs, w->glyphBpp, w->glyphHeight);
        SrollTextBlitGlyph(w, (u32*)(w->tileData + off), g, n);
    }

    SrollTextSetCursorPixelX(w, x);
    SrollTextEnqueueString(w, s);
    SrollTextDrawQueued(w, 0);

    if ((w->x & 7) != 0) {
        off = (w->y * w->textWidth + (w->x >> 3)) * 32;
        g = SrollTextGetGlyphAddress(0x8140, w->fontPages, w->fontGlyphs, w->glyphBpp, w->glyphHeight);
        SrollTextBlitGlyph(w, (u32*)(w->tileData + off), g, 8 - (w->x & 7));
    }

    if (flush == 1 && (w->flags & SROLL_FLAG_TILEMAP_DIRTY)) {
        SrollTextFlushTilemap(w);
    }
}

u16 SrollTextMapSingleByteChar(u8 c) {
    return gUnk_09A5B470[c];
}

void ScanlineDmaReset() {

    DmaStop(0);
    sDmaStream.enabled = 0;
    sDmaStream.swapPending = 0;
    sDmaStream.update = NULL;
    sDmaStream.dst = NULL;
    sDmaStream.srcIdx = 0;
    sDmaStream.src[0] = NULL;
    sDmaStream.src[1] = NULL;
    sDmaStream.cnt = 0;
}

void ScanlineDmaUpdate() {
    u8* src;

    DmaStop(0);

    if (sDmaStream.enabled != 0) {
        if (sDmaStream.swapPending != 0) {
            sDmaStream.srcIdx ^= 1;
            src = sDmaStream.src[sDmaStream.srcIdx];
            sDmaStream.dmaSrc = src;

            if (!(sDmaStream.cnt & CPU_SET_SRC_FIXED)) {
                if (sDmaStream.cnt & CPU_SET_32BIT) {
                    sDmaStream.dmaSrc = src + 4;
                } else {
                    sDmaStream.dmaSrc = src + 2;
                }
            }

            sDmaStream.swapPending = 0;
        }

        if (sDmaStream.src[sDmaStream.srcIdx] != NULL && sDmaStream.dst != NULL &&
            sDmaStream.cnt != 0) {
            DmaSet(0, sDmaStream.dmaSrc, sDmaStream.dst, sDmaStream.cnt);
        }

        if (sDmaStream.update != NULL) {
            sDmaStream.update();
        }
    }
}

void ScanlineDmaPrime32Bit() {
    *sDmaStream.dst = *(u32*)sDmaStream.src[sDmaStream.srcIdx];
}

void ScanlineDmaPrime16Bit() {
    *sDmaStream.dst = *(u16*)sDmaStream.src[sDmaStream.srcIdx];
}

void ScanlineDmaInit(vu16* dst, u8* src, u32 cnt) {
    ScanlineDmaReset();
    sDmaStream.src[0] = src;
    sDmaStream.src[1] = src;
    sDmaStream.dmaSrc = src;

    if (cnt & CPU_SET_32BIT) {
        sDmaStream.update = ScanlineDmaPrime32Bit;

        if (!(cnt & CPU_SET_SRC_FIXED)) {
            sDmaStream.dmaSrc = src + 4;
        }
    } else {
        sDmaStream.update = ScanlineDmaPrime16Bit;

        if (!(cnt & CPU_SET_SRC_FIXED)) {
            sDmaStream.dmaSrc = src + 2;
        }
    }

    sDmaStream.dst = dst;
    sDmaStream.cnt = cnt;
}

void ScanlineDmaQueueBuffer(u8* src) {
    sDmaStream.src[sDmaStream.srcIdx ^ 1] = src;
    sDmaStream.swapPending = 1;
}

void ScanlineDmaEnable() {
    sDmaStream.enabled = 1;
}

void ScanlineDmaDisable() {
    sDmaStream.enabled = 0;
}

void BlockAudioStart() {
    sBlockAudioPlaying = 1;
    AudioBlockStreamInit(GetBlockAudioData());
    PcmPlaybackInit(GetBlockAudioSampleRate());
    SetVBlankCallback(VBlankIntrBlockAudio);
    PcmPlaybackStart();
}

void BlockAudioUpdate() {
    if (sBlockAudioPlaying == 1) {
        sBlockAudioPlaying = AudioBlockStreamUpdate();

        if (sBlockAudioPlaying == 0) {
            BlockAudioStop();
        }
    }
}

void BlockAudioVBlank() {
    if (sBlockAudioPlaying == 1) {
        PcmPlaybackUpdate();
    }
}

void BlockAudioStop() {
    ResetVBlankCallback();
    PcmPlaybackStop();
    m4aSoundInit();
    m4aSoundVSyncOn();
}

u16 GetBlockAudioSampleRate() {
    return 21024;
}

u32* GetBlockAudioData() {
    return gBlockAudioData;
}

u8* ReadNextAudioBlock(u32** p) {
    u32* base;
    u32* q;
    u32 v;

    base = *p;
    q = base;
    v = *q++;

    if ((v & 0xFF) != 0x53) {
        *p = NULL;
        return NULL;
    }

    *p = (u32*)((u8*)base + (((v >> 8) & 0xFF00) << 2) + ((v >> 24) << 2));
    return (u8*)q;
}

s32 AudioBlockStreamInit(u32* src) {
    s32* p;
    u8* q;

    for (p = sDecodedAudioBuffer; p < sDecodedAudioBuffer + 0x810;) {
        *p++ = 0;
    }

    sAudioBlockNext = src;

    for (sDecodedAudioWritePosition = 0; sDecodedAudioWritePosition <= 0x7FF; sDecodedAudioWritePosition += 0x200) {
        if (sAudioBlockNext != NULL) {
            q = ReadNextAudioBlock(&sAudioBlockNext);

            if (q != NULL) {
                DecodeAudioBlock(q, sDecodedAudioBuffer, sDecodedAudioWritePosition);
            }
        }
    }

    sDecodedAudioWritePosition &= 0x7FF;
    sDecodedAudioReadPosition = 0;
    return sAudioBlockNext != NULL;
}

s32 AudioBlockStreamUpdate() {
    u8* q;

    if (sDecodedAudioReadPosition > sDecodedAudioWritePosition + 0x200 || sDecodedAudioReadPosition < sDecodedAudioWritePosition) {
        if (sAudioBlockNext != NULL) {
            q = ReadNextAudioBlock(&sAudioBlockNext);

            if (q != NULL) {
                DecodeAudioBlock(q, sDecodedAudioBuffer, sDecodedAudioWritePosition);
            }

            sDecodedAudioWritePosition = (sDecodedAudioWritePosition + 0x200) & 0x7FF;
        }
    }

    return sAudioBlockNext != NULL;
}

s32* GetDecodedAudioBuffer() {
    return sDecodedAudioBuffer;
}

s32 GetDecodedAudioReadPosition() {
    return sDecodedAudioReadPosition;
}

void SetDecodedAudioReadPosition(s32 pos) {
    sDecodedAudioReadPosition = pos;
}

TaskDesc gTaskDescSrollTmr = {
    "task_sroll_tmr",
    (TaskInitFunc)task_sroll_tmr_0,
    (TaskUpdateFunc)task_sroll_tmr_1,
    (TaskDrawFunc)task_sroll_tmr_2,
    (TaskDestroyFunc)task_sroll_tmr_3,
    sizeof(SrollTmrWork),
};
