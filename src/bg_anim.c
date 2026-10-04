#include "pallet.h"
#include "gba/syscall.h"
#include <stddef.h>
#include "bg_animation_types.h"
#include "display.h"
#include "types.h"

static BgAnimationDef* sBgAnimCurrent;
static u16 sBgAnimFrameTimer;
static u16 sBgAnimFrame;
static s32 sBgAnimBg;
static u16 sBgAnimFrameBytes;
static u16 sBgAnimFramesPerChunk;
static s16 sBgAnimScrollX;
static s16 sBgAnimScrollY;
static u8 sBgAnimStopped;
static u16 sBgAnimMapSize;
static u8 sBgAnimAffine;
static u32 sBgAnimScaleX;
static u32 sBgAnimScaleY;
static u8 sBgAnimRotation;
static s16 sBgAnimLoopStartFrame;
static s16 sBgAnimStopFrame;
static u16 sBgAnimFrameDuration;

void BgAnimInit(s32 bg, u16 b, u16 c) {
    sBgAnimBg = bg;
    sBgAnimCurrent = NULL;
    sBgAnimScrollX = 0;
    sBgAnimScrollY = 0;
    sBgAnimStopped = 1;

    if (c == 0) {
        sBgAnimAffine = 0;

        switch (b) {
        case 0x4000:
        case 0x8000:
            sBgAnimMapSize = 0x1000;
            break;
        case 0xC000:
            sBgAnimMapSize = 0x2000;
            break;
        case 0:
        default:
            sBgAnimMapSize = 0x800;
            break;
        }
    } else {
        sBgAnimAffine = 1;

        switch (b) {
        case 0x4000:
            sBgAnimMapSize = 0x400;
            break;
        case 0x8000:
            sBgAnimMapSize = 0x1000;
            break;
        case 0xC000:
            sBgAnimMapSize = 0x4000;
            break;
        case 0:
        default:
            sBgAnimMapSize = 0x100;
            break;
        }
    }

    SetBgSize(bg, b);
    DisableBg(bg);
}

void BgAnimSetPosition(s16 x, s16 y) {
    if (sBgAnimAffine) {
        sBgAnimScrollX = -x;
        sBgAnimScrollY = -y;
    } else {
        sBgAnimScrollX = (sBgAnimCurrent->originX << 2) - x;
        sBgAnimScrollY = (sBgAnimCurrent->originY << 2) - y;
    }
}

void BgAnimSetTransform(u8 a, s32 b, s32 c) {
    sBgAnimRotation = a;
    sBgAnimScaleX = b;
    sBgAnimScaleY = c;
}

void BgAnimStart(BgAnimationDef* a, s32 x, s32 y) {
    sBgAnimCurrent = a;
    BgAnimSetPosition(x, y);

    if (sBgAnimAffine) {
        sBgAnimFrameBytes = a->tilesPerFrame << 6;
    } else {
        sBgAnimFrameBytes = a->tilesPerFrame << 5;
    }

    sBgAnimFramesPerChunk = 0x8000 / sBgAnimFrameBytes;
    sBgAnimLoopStartFrame = -1;
    sBgAnimStopFrame = -1;
    sBgAnimFrameTimer = 0;
    sBgAnimFrame = 0;
    sBgAnimStopped = 0;
    sBgAnimFrameDuration = a->frameDuration;

    if (sBgAnimAffine) {
        sBgAnimScaleX = 0x100;
        sBgAnimScaleY = 0x100;
        sBgAnimRotation = 0;
    }

    PushPaletteEffect(0);
    LoadBgPalette(sBgAnimBg, a->palette, a->paletteSize);
    PopPaletteEffect();
    LoadBgMap(sBgAnimBg, a->tilemap, sBgAnimMapSize);
}

void BgAnimApplyAffineTransform(s32 bg, u8 rot, s32 sx, s32 sy, s16 cx, s16 cy) {
    BgAffineSrcData src;
    BgAffineDstData dst;

    src.texX = sBgAnimCurrent->originX << 10;
    src.texY = sBgAnimCurrent->originY << 10;
    src.scrX = -cx;
    src.scrY = -cy;
    src.sx = 0x10000 / sx;
    src.sy = 0x10000 / sy;
    src.alpha = -rot << 8;
    BgAffineSet(&src, &dst, 1);

    switch (bg) {
    case 2:
        gBg2PA = dst.pa;
        gBg2PB = dst.pb;
        gBg2PC = dst.pc;
        gBg2PD = dst.pd;
        gBg2X = dst.dx;
        gBg2Y = dst.dy;
        break;
    case 3:
        gBg3PA = dst.pa;
        gBg3PB = dst.pb;
        gBg3PC = dst.pc;
        gBg3PD = dst.pd;
        gBg3X = dst.dx;
        gBg3Y = dst.dy;
        break;
    }
}

void BgAnimUpdate() {
    u8* src;
    u16 q;
    u16 off;
    u16 len;
    s16 over;
    s32 vis;

    if (sBgAnimCurrent == NULL) {
        return;
    }

    if (sBgAnimFrame >= sBgAnimCurrent->frameCount) {
        if (sBgAnimLoopStartFrame >= 0) {
            sBgAnimFrame = sBgAnimLoopStartFrame;
            sBgAnimFrameTimer = 0;
        } else {
            BgAnimStop();
        }

        return;
    }

    if (sBgAnimAffine) {
        BgAnimApplyAffineTransform(sBgAnimBg, sBgAnimRotation, sBgAnimScaleX, sBgAnimScaleY, sBgAnimScrollX, sBgAnimScrollY);
        vis = 1;
    } else {
        SetBgScroll(sBgAnimBg, (u16)sBgAnimScrollX, (u16)sBgAnimScrollY);

        if (sBgAnimScrollX > -256 && sBgAnimScrollX < 128 && sBgAnimScrollY < 128 && sBgAnimScrollY > -256) {
            vis = 1;
        } else {
            vis = 0;
        }
    }

    if (vis) {
        EnableBg(sBgAnimBg);

        if (sBgAnimFrameTimer == 0) {
            q = sBgAnimFrame / sBgAnimFramesPerChunk;
            off = sBgAnimFrame % sBgAnimFramesPerChunk * sBgAnimFrameBytes;
            src = (u8*)sBgAnimCurrent->chunks[q].data + off;
            over = off + sBgAnimFrameBytes - sBgAnimCurrent->chunks[q].size;

            if (over > 0) {
                len = sBgAnimFrameBytes - over;
                RequestDma3Copy(src, GetBgCharBase(sBgAnimBg), len);
                RequestDma3Clear((u8*)GetBgCharBase(sBgAnimBg) + len, over);
            } else {
                RequestDma3Copy(src, GetBgCharBase(sBgAnimBg), sBgAnimFrameBytes);
            }
        }
    } else {
        DisableBg(sBgAnimBg);
    }

    sBgAnimFrameTimer++;

    if (sBgAnimFrameTimer >= sBgAnimFrameDuration) {
        sBgAnimFrameTimer = 0;

        if (sBgAnimFrame != sBgAnimStopFrame) {
            sBgAnimFrame++;
        }
    }
}

void BgAnimSetFrameDuration(u16 a) {
    sBgAnimFrameDuration = a;
}

void BgAnimSetLoopStartFrame(u16 a) {
    sBgAnimLoopStartFrame = a;
}

void BgAnimSetStopFrame(u16 a) {
    sBgAnimStopFrame = a;
}

void BgAnimStop() {
    sBgAnimCurrent = NULL;
    sBgAnimStopped = 1;
    DisableBg(sBgAnimBg);
}

u8 BgAnimIsStopped() {
    return sBgAnimStopped;
}

void BgAnimGetFrameState(u16* a, u16* b) {
    if (a != NULL) {
        *a = sBgAnimFrame;
    }

    if (b != NULL) {
        *b = sBgAnimFrameTimer;
    }
}

u32 BgAnimGetDuration(BgAnimationDef* p) {
    return (u32)p->frameCount * p->frameDuration;
}

BgAnimationDef* BgAnimGetCurrent() {
    return sBgAnimCurrent;
}
