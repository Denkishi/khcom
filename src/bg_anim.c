#include "pallet.h"
#include "gba/syscall.h"
#include <stddef.h>
#include "bg_animation_types.h"
#include "display.h"
#include "types.h"

BgAnimationDef* gBgAnimCurrent;
u16 gBgAnimFrameTimer;
u16 gBgAnimFrame;
s32 gBgAnimBg;
u16 gBgAnimFrameBytes;
u16 gBgAnimFramesPerChunk;
s16 gBgAnimScrollX;
s16 gBgAnimScrollY;
u8 gBgAnimStopped;
u16 gBgAnimMapSize;
u8 gBgAnimAffine;
u32 gBgAnimScaleX;
u32 gBgAnimScaleY;
u8 gBgAnimRotation;
s16 gBgAnimLoopStartFrame;
s16 gBgAnimStopFrame;
u16 gBgAnimFrameDuration;

void BgAnimInit(s32 bg, u16 b, u16 c) {
    gBgAnimBg = bg;
    gBgAnimCurrent = NULL;
    gBgAnimScrollX = 0;
    gBgAnimScrollY = 0;
    gBgAnimStopped = 1;

    if (c == 0) {
        gBgAnimAffine = 0;

        switch (b) {
        case 0x4000:
        case 0x8000:
            gBgAnimMapSize = 0x1000;
            break;
        case 0xC000:
            gBgAnimMapSize = 0x2000;
            break;
        case 0:
        default:
            gBgAnimMapSize = 0x800;
            break;
        }
    } else {
        gBgAnimAffine = 1;

        switch (b) {
        case 0x4000:
            gBgAnimMapSize = 0x400;
            break;
        case 0x8000:
            gBgAnimMapSize = 0x1000;
            break;
        case 0xC000:
            gBgAnimMapSize = 0x4000;
            break;
        case 0:
        default:
            gBgAnimMapSize = 0x100;
            break;
        }
    }

    SetBgSize(bg, b);
    DisableBg(bg);
}

void BgAnimSetPosition(s16 x, s16 y) {
    if (gBgAnimAffine != 0) {
        gBgAnimScrollX = -x;
        gBgAnimScrollY = -y;
    } else {
        gBgAnimScrollX = (gBgAnimCurrent->originX << 2) - x;
        gBgAnimScrollY = (gBgAnimCurrent->originY << 2) - y;
    }
}

void BgAnimSetTransform(u8 a, s32 b, s32 c) {
    gBgAnimRotation = a;
    gBgAnimScaleX = b;
    gBgAnimScaleY = c;
}

void BgAnimStart(BgAnimationDef* a, s32 x, s32 y) {
    gBgAnimCurrent = a;
    BgAnimSetPosition(x, y);

    if (gBgAnimAffine != 0) {
        gBgAnimFrameBytes = a->tilesPerFrame << 6;
    } else {
        gBgAnimFrameBytes = a->tilesPerFrame << 5;
    }

    gBgAnimFramesPerChunk = 0x8000 / gBgAnimFrameBytes;
    gBgAnimLoopStartFrame = -1;
    gBgAnimStopFrame = -1;
    gBgAnimFrameTimer = 0;
    gBgAnimFrame = 0;
    gBgAnimStopped = 0;
    gBgAnimFrameDuration = a->frameDuration;

    if (gBgAnimAffine != 0) {
        gBgAnimScaleX = 0x100;
        gBgAnimScaleY = 0x100;
        gBgAnimRotation = 0;
    }

    PushPaletteEffect(0);
    LoadBgPalette(gBgAnimBg, a->palette, a->paletteSize);
    PopPaletteEffect();
    LoadBgMap(gBgAnimBg, a->tilemap, gBgAnimMapSize);
}

void BgAnimApplyAffineTransform(s32 bg, u8 rot, s32 sx, s32 sy, s16 cx, s16 cy) {
    BgAffineSrcData src;
    BgAffineDstData dst;

    src.texX = gBgAnimCurrent->originX << 10;
    src.texY = gBgAnimCurrent->originY << 10;
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

    if (gBgAnimCurrent == NULL) {
        return;
    }

    if (gBgAnimFrame >= gBgAnimCurrent->frameCount) {
        if (gBgAnimLoopStartFrame >= 0) {
            gBgAnimFrame = gBgAnimLoopStartFrame;
            gBgAnimFrameTimer = 0;
        } else {
            BgAnimStop();
        }

        return;
    }

    if (gBgAnimAffine != 0) {
        BgAnimApplyAffineTransform(gBgAnimBg, gBgAnimRotation, gBgAnimScaleX, gBgAnimScaleY, gBgAnimScrollX, gBgAnimScrollY);
        vis = 1;
    } else {
        SetBgScroll(gBgAnimBg, (u16)gBgAnimScrollX, (u16)gBgAnimScrollY);

        if (gBgAnimScrollX > -256 && gBgAnimScrollX < 128 && gBgAnimScrollY < 128 && gBgAnimScrollY > -256) {
            vis = 1;
        } else {
            vis = 0;
        }
    }

    if (vis != 0) {
        EnableBg(gBgAnimBg);

        if (gBgAnimFrameTimer == 0) {
            q = gBgAnimFrame / gBgAnimFramesPerChunk;
            off = gBgAnimFrame % gBgAnimFramesPerChunk * gBgAnimFrameBytes;
            src = (u8*)gBgAnimCurrent->chunks[q].data + off;
            over = off + gBgAnimFrameBytes - gBgAnimCurrent->chunks[q].size;

            if (over > 0) {
                len = gBgAnimFrameBytes - over;
                RequestDma3Copy(src, GetBgCharBase(gBgAnimBg), len);
                RequestDma3Clear((u8*)GetBgCharBase(gBgAnimBg) + len, over);
            } else {
                RequestDma3Copy(src, GetBgCharBase(gBgAnimBg), gBgAnimFrameBytes);
            }
        }
    } else {
        DisableBg(gBgAnimBg);
    }

    gBgAnimFrameTimer++;

    if (gBgAnimFrameTimer >= gBgAnimFrameDuration) {
        gBgAnimFrameTimer = 0;

        if (gBgAnimFrame != gBgAnimStopFrame) {
            gBgAnimFrame++;
        }
    }
}

void BgAnimSetFrameDuration(u16 a) {
    gBgAnimFrameDuration = a;
}

void BgAnimSetLoopStartFrame(u16 a) {
    gBgAnimLoopStartFrame = a;
}

void BgAnimSetStopFrame(u16 a) {
    gBgAnimStopFrame = a;
}

void BgAnimStop() {
    gBgAnimCurrent = NULL;
    gBgAnimStopped = 1;
    DisableBg(gBgAnimBg);
}

u8 BgAnimIsStopped() {
    return gBgAnimStopped;
}

void BgAnimGetFrameState(u16* a, u16* b) {
    if (a != NULL) {
        *a = gBgAnimFrame;
    }

    if (b != NULL) {
        *b = gBgAnimFrameTimer;
    }
}

u32 BgAnimGetDuration(BgAnimationDef* p) {
    return (u32)p->frameCount * p->frameDuration;
}

BgAnimationDef* BgAnimGetCurrent() {
    return gBgAnimCurrent;
}
