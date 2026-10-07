#include "rogue.h"
#include "engine_math.h"
#include "obj.h"
#include "sprite.h"

// Faster versions of the routines a battle spends most of its frame in. Each
// does exactly what the original does; they are written for the processor
// they run on, which pays for every function call, 16-bit local and software
// division.

extern struct SpriteWork* gSpriteWork;

// Width and height of an OBJ in pixels, by its shape and size bits. The
// fourth shape does not exist and is drawn as nothing.
static const u8 sObjSize[16][2] = {
    { 8, 8 }, { 16, 16 }, { 32, 32 }, { 64, 64 }, { 16, 8 }, { 32, 8 }, { 32, 16 }, { 64, 32 },
    { 8, 16 }, { 8, 32 }, { 16, 32 }, { 32, 64 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
};

// Writes the frame's sprites to the OAM: func_08002F50, without a function
// call or a switch for each piece of each sprite.
void RogueBuildOam(void) {
    struct SpriteWork* work = gSpriteWork;
    SpriteEntry** entries;
    u16* oam;
    s32 emitted;
    s32 count;
    s32 i;
    u32 mosaic;

    if (work->unk_2BAE != 0) {
        return;
    }

    oam = (u16*)0x07000000;

    for (i = 0; i < work->affineCount; i++) {
        oam[3] = work->affine[i].pa;
        oam[7] = work->affine[i].pb;
        oam[11] = work->affine[i].pc;
        oam[15] = work->affine[i].pd;
        oam += 16;
    }

    work->affineCount = 0;
    emitted = 0;
    oam = (u16*)0x07000000;
    count = work->entryCount;
    entries = work->sortPtrs;
    mosaic = work->unk_2BAF;

    for (i = 0; i < count; i++) {
        SpriteEntry* entry = entries[i];
        const u16* parts = entry->sprite;
        const ObjAffine* affine = entry->affine;
        const ObjTiles* tiles = entry->tiles;
        s32 partCount = *parts++;
        u32 tileOffset = 0;
        u32 flags;
        u32 allocated = tiles->allocated;
        u32 tileIndex = tiles->index;
        u32 paletteIndex = ((ObjPalette*)entry->palette)->index;
        s32 entryX = (s16)entry->x;
        s32 entryY = (s16)entry->y;

        if (mosaic != 0 && (entry->flags & 0x10) == 0) {
            entry->flags |= 8;
        }

        flags = entry->flags;

        for (; partCount > 0; partCount--) {
            u32 attr0 = *parts++;
            u32 attr1 = *parts++;
            u32 attr2 = *parts++;
            const u8* size = sObjSize[((attr0 >> 14) << 2) | (attr1 >> 14)];
            s32 width = size[0];
            s32 height = size[1];
            u32 tileCount = (u32)(width * height) >> 6;
            s32 x = (s32)(attr1 << 23) >> 23;
            s32 y = (s8)attr0;
            u32 out0;
            u32 out2;
            u32 palette;

            if (affine != 0) {
                s32 xx;
                s32 yy;

                x += width >> 1;
                y += height >> 1;

                if (affine->angle != 0) {
                    s32 sinIndex = -affine->angle;
                    s32 cosIndex = (s16)(sinIndex + 64) & 255;

                    sinIndex &= 255;
                    xx = (s32)((u32)gSineTable[cosIndex] * x + (u32)gSineTable[sinIndex] * y);
                    yy = (s32)((u32)gSineTable[cosIndex + 64] * x + (u32)gSineTable[sinIndex + 64] * y);
                    xx = (s32)((u32)affine->sx * xx) >> 8;
                    yy = (s32)((u32)affine->sy * yy) >> 8;
                } else {
                    xx = (s32)((u32)affine->sx * x);
                    yy = (s32)((u32)affine->sy * y);
                }

                x = (s16)(xx >> 8) - (width >> 1);
                y = (s16)(yy >> 8) - (height >> 1);

                if (affine->doubleSize != 0) {
                    x -= width >> 1;
                    y -= height >> 1;
                    width <<= 1;
                    height <<= 1;
                    attr0 |= 0x300;
                } else {
                    attr0 |= 0x100;
                }

                attr1 |= affine->index << 9;
            } else {
                if (flags & 2) {
                    attr1 ^= 0x2000;
                    y = -y - height;
                }

                if (flags & 1) {
                    attr1 ^= 0x1000;
                    x = -x - width;
                }
            }

            x = (s16)(x + entryX);
            y = (s16)(y + entryY);

            if (x > 239 || x <= -width || y > 159 || y <= -height) {
                if (allocated) {
                    tileOffset += tileCount;
                }

                continue;
            }

            palette = (attr2 >> 12) + paletteIndex;

            if (allocated) {
                out2 = (attr2 & 0xC00) | ((tileOffset + tileIndex) & 0xFFFF) | (palette << 12);
                tileOffset += tileCount;
            } else {
                out2 = (((attr2 & 0xFFF) + tileIndex) & 0xFFFF) | (palette << 12);
            }

            out0 = (attr0 & 0xFF00) | (y & 0xFF);
            out0 |= (flags & 8) << 9;
            out0 |= (flags & 4) << 8;
            oam[0] = out0;
            oam[1] = (attr1 & 0xFE00) | (x & 0x1FF);
            oam[2] = out2 | (flags & 0xC00);
            oam += 4;
            emitted++;
        }
    }

    for (i = emitted; i < 128; i++) {
        *oam = 0x200;
        oam += 4;
    }

    work->entryCount = 0;
}

// The square root of a 24.8 number as one: Sqrt8, which divided once for
// each step of Newton's method. This finds the same root a bit at a time.
s32 RogueSqrt8(s32 a) {
    u32 n = (u32)a << 8;
    u32 root = 0;
    u32 bit = 1 << 30;

    while (bit > n) {
        bit >>= 2;
    }

    while (bit != 0) {
        if (n >= root + bit) {
            n -= root + bit;
            root = (root >> 1) + bit;
        } else {
            root >>= 1;
        }

        bit >>= 2;
    }

    return root;
}
