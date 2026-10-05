/**
 * msg.c
 * Text and Glyph Rendering
 */

#include "msg.h"
#include "sprites_msg.h"
#include "malloc.h"
#include "fade.h"
#include "display.h"
#include "msg_api.h"
#include "msg_types.h"
#include "obj_api.h"
#include "text.h"
#include "text_types.h"
#include "types.h"
#include "gba/defines.h"
#include "gba/macro.h"
#include <stddef.h>
#include "sprite_palettes.h"

static SpriteTextLine* sSpriteTextLines;
static TextGlyphSprite* sMsgGlyphSprites;
static TextGlyphSprite* sCardMsgGlyphSprites;
#ifndef VERSION_EU
static BgTextLine* sBgTextLines;
#endif
static u8 sTextEntryCount;
static u8 sBgTextDrawQueued;

static const GlyphWidthTable sLatinGlyphWidths = {
    {
        0, 4, 4, 5, 5, 6, 8, 8, 8, 6, 6, 6, 8, 8, 8, 8,
        8, 8, 7, 8, 8, 8, 8, 8, 6, 12, 0, 0, 0, 0, 0, 0,
        3, 2, 5, 8, 6, 7, 7, 3, 4, 4, 6, 6, 3, 6, 3, 5,
        6, 4, 6, 6, 6, 6, 6, 6, 6, 6, 3, 3, 5, 6, 5, 6,
        8, 6, 6, 6, 6, 5, 5, 6, 6, 4, 6, 6, 6, 7, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 8, 7, 6, 6, 3, 5, 3, 6, 6,
        3, 6, 6, 5, 6, 6, 5, 6, 6, 2, 4, 5, 3, 6, 6, 6,
        6, 6, 5, 6, 5, 6, 6, 8, 6, 6, 6, 4, 2, 4, 8, 7,
        7, 7, 3, 6,
#ifdef VERSION_EU
        5,
#else
        4,
#endif
        9, 6, 6, 5, 9, 6, 4, 9, 4, 6, 7,
        7, 3, 3, 5, 5, 7, 7, 8, 5, 9, 6, 4, 8, 7, 6, 6,
        0, 2, 6, 7, 5, 6, 2, 5, 4, 8, 4, 6, 6, 4, 8, 6,
        5, 6, 5, 5, 3, 7, 7, 3, 3, 4, 4, 6, 7, 7, 8, 5,
        6, 6, 6, 6, 6, 6, 9, 6, 5, 5, 5, 5, 3, 3, 4, 4,
        7, 6, 6, 6, 6, 6, 6, 7, 8, 6, 6, 6, 6, 6, 5, 6,
        6, 6, 6, 6, 6, 6, 8, 5, 6, 6, 6, 6, 3, 3, 4, 4,
        6, 6, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 6, 5, 6,
    },
};

void InitSpriteTextLines() {
    u8 i;
    u8 j;

    sSpriteTextLines = EwramAlloc(sizeof(SpriteTextLine) * 45);
    sTextEntryCount = 0;

    for (i = 0; i < 45; i++) {
        sSpriteTextLines[i].x = 0;
        sSpriteTextLines[i].y = 0;
        sSpriteTextLines[i].palette = NULL;
        sSpriteTextLines[i].length = 0;

        for (j = 0; j < 16; j++) {
            sSpriteTextLines[i].glyphTiles[j] = NULL;
        }
    }
}

void AddSpriteTextLine(s32 x, s32 y, u8* s) {
    u8 i;
    u8 len;
    u8 idx;

    idx = 0;

    if (sTextEntryCount > 44) {
        return;
    }

    if (sSpriteTextLines == NULL) {
        return;
    }

    sSpriteTextLines[sTextEntryCount].x = x;
    sSpriteTextLines[sTextEntryCount].y = y;
    sSpriteTextLines[sTextEntryCount].font = 0;
    len = GetStringLength(s);

    if (len > 15) {
        len = 16;
    }

    sSpriteTextLines[sTextEntryCount].length = len;

    for (i = 0; i < len; i++) {
        s16 c;

        sSpriteTextLines[sTextEntryCount].glyphTiles[i] = AllocSpriteFrameTiles(32);
        c = s[i];

        if ((u8)(c - 48) <= 9) {
            idx = c - 48;
        }

        if ((u8)(c - 65) <= 25) {
            idx = c - 55;
        }

        if (c == 47) {
            idx = 36;
        }

        if (c == 45) {
            idx = 37;
        }

        if (c == 95) {
            idx = 38;
        }

        if (c == 46) {
            idx = 39;
        }

        if (c == 43) {
            idx = 40;
        }

        if (c == 33) {
            idx = 41;
        }

        if (c == 63) {
            idx = 42;
        }

        if (c == 35) {
            idx = 43;
        }

        if (s[i] == 37) {
            idx = 44;
        }

        UpdateSpriteFrameTiles(sSpriteTextLines[sTextEntryCount].glyphTiles[i], gSmallFontFrames[idx], gSmallFontTiles);
    }

    sSpriteTextLines[sTextEntryCount].palette = LoadObjPalette(gCommonObjPalette, 32);
    sTextEntryCount++;
}

#ifndef VERSION_EU
void AddSpriteTextLineFont1(s32 x, s32 y, u8* s) {
    u8 i;
    u8 len;
    u8 k;
    u8 idx;
    idx = 0;

    if (sTextEntryCount > 44) {
        return;
    }

    if (sSpriteTextLines == NULL) {
        return;
    }

    sSpriteTextLines[sTextEntryCount].x = x;
    sSpriteTextLines[sTextEntryCount].y = y;
    sSpriteTextLines[sTextEntryCount].font = 1;
    len = GetStringLength(s);

    if (len > 15) {
        len = 16;
    }

    sSpriteTextLines[sTextEntryCount].length = len;

    for (i = 0, k = 0; i < len; i++) {
        s32 c = s[i];

        if ((u8)(c - 48) <= 9) {
            idx = c - 48;
        }

        if ((u8)(c - 65) <= 25) {
            idx = c - 52;
        }

        sSpriteTextLines[sTextEntryCount].glyphTiles[k] = AllocSpriteFrameTiles(128);
        UpdateSpriteFrameTiles(sSpriteTextLines[sTextEntryCount].glyphTiles[k], gMsgFontBank0Frames[idx], gMsgFontBank0Tiles);
        k++;
    }

    sSpriteTextLines[sTextEntryCount].palette = LoadObjPalette(&gUnk_096147D8[0x10], 32);
    sTextEntryCount++;
}
#endif

void AddSpriteTextNumber(s32 x, s32 y, s32 n) {
    u8 buf[20];
    u8 i;

    if (n >= 0) {
        buf[0] = n / 10000000;
        buf[1] = n / 1000000 - buf[0] * 10;
        buf[2] = n / 100000 - buf[0] * 100 - buf[1] * 10;
        buf[3] = n / 10000 - buf[0] * 1000 - buf[1] * 100 - buf[2] * 10;
        buf[4] = n / 1000 - buf[0] * 10000 - buf[1] * 1000 - buf[2] * 100 - buf[3] * 10;
        buf[5] = n / 100 - buf[0] * 100000 - buf[1] * 10000 - buf[2] * 1000 - buf[3] * 100 - buf[4] * 10;
        buf[6] = n / 10 - buf[0] * 1000000 - buf[1] * 100000 - buf[2] * 10000 - buf[3] * 1000 - buf[4] * 100 - buf[5] * 10;
        buf[7] = n - (buf[0] * 10000000 + buf[1] * 1000000 + buf[2] * 100000 + buf[3] * 10000 + buf[4] * 1000 + buf[5] * 100 + buf[6] * 10);
        buf[0] += 0x30;
        buf[1] += 0x30;
        buf[2] += 0x30;
        buf[3] += 0x30;
        buf[4] += 0x30;
        buf[5] += 0x30;
        buf[6] += 0x30;
        buf[7] += 0x30;
        buf[8] = 0;

        for (i = 0; i <= 6; i++) {
            if (buf[i] > 0x30) {
                break;
            }
        }

        AddSpriteTextLine(x, y, &buf[i]);
    } else {
        n = -n;
        buf[1] = n / 10000000;
        buf[2] = n / 1000000 - buf[1] * 10;
        buf[3] = n / 100000 - buf[1] * 100 - buf[2] * 10;
        buf[4] = n / 10000 - buf[1] * 1000 - buf[2] * 100 - buf[3] * 10;
        buf[5] = n / 1000 - buf[1] * 10000 - buf[2] * 1000 - buf[3] * 100 - buf[4] * 10;
        buf[6] = n / 100 - buf[1] * 100000 - buf[2] * 10000 - buf[3] * 1000 - buf[4] * 100 - buf[5] * 10;
        buf[7] = n / 10 - buf[1] * 1000000 - buf[2] * 100000 - buf[3] * 10000 - buf[4] * 1000 - buf[5] * 100 - buf[6] * 10;
        buf[8] = n - (buf[1] * 10000000 + buf[2] * 1000000 + buf[3] * 100000 + buf[4] * 10000 + buf[5] * 1000 + buf[6] * 100 + buf[7] * 10);
        buf[0] = 0x2D;
        buf[1] += 0x30;
        buf[2] += 0x30;
        buf[3] += 0x30;
        buf[4] += 0x30;
        buf[5] += 0x30;
        buf[6] += 0x30;
        buf[7] += 0x30;
        buf[8] += 0x30;
        buf[9] = 0;

        for (i = 1; i <= 7; i++) {
            if (buf[i] > 0x30) {
                break;
            }
        }

        buf[i - 1] = 0x2D;
        AddSpriteTextLine(x, y, &buf[i - 1]);
    }
}

void DrawSpriteTextLines() {
    s32 x;
    s32 y;
    s32 step;
    u8 i;
    u8 j;

    step = 8;

    for (i = 0; i < sTextEntryCount; i++) {
        switch (sSpriteTextLines[i].font) {
        case 0:
            step = 8;
            break;
        case 1:
            step = 10;
            break;
        }

        x = sSpriteTextLines[i].x;
        y = sSpriteTextLines[i].y;

        for (j = 0; j < sSpriteTextLines[i].length; j++) {
            DrawSprite((x >> 8) + j * step, y >> 8, NULL, sSpriteTextLines[i].glyphTiles[j], sSpriteTextLines[i].palette, NULL, 0, 50);
            ReleaseObjTiles(sSpriteTextLines[i].glyphTiles[j]);
        }

        ReleaseObjPalette(sSpriteTextLines[i].palette);
    }

    sTextEntryCount = 0;
}

void ClearSpriteTextLines() {
    u8 i;
    u8 j;

    for (i = 0; i < sTextEntryCount; i++) {
        sSpriteTextLines[i].x = 0;
        sSpriteTextLines[i].y = 0;
        ReleaseObjPalette(sSpriteTextLines[i].palette);

        for (j = 0; j < sSpriteTextLines[i].length; j++) {
            ReleaseObjTiles(sSpriteTextLines[i].glyphTiles[j]);
        }
    }

    sTextEntryCount = 0;
}

void FreeSpriteTextLines() {
    ClearSpriteTextLines();

    if (sSpriteTextLines != NULL) {
        EwramFree(sSpriteTextLines);
    }

    sSpriteTextLines = NULL;
}

#ifndef VERSION_EU
void* InitSpriteTextSlots(s32 a) {
    u8 i;
    u8 j;
    sSpriteTextLines = EwramAlloc(sizeof(SpriteTextLine) * 24);
    sTextEntryCount = 0;

    for (i = 0; i < 24; i++) {
        sSpriteTextLines[i].x = 0;
        sSpriteTextLines[i].y = 0;
        sSpriteTextLines[i].palette = NULL;
        sSpriteTextLines[i].length = 0;
        sSpriteTextLines[i].visible = 0;
        sSpriteTextLines[i].unk_53 = 0;

        for (j = 0; j < 16; j++) {
            sSpriteTextLines[i].glyphTiles[j] = NULL;
        }

        switch (a) {
        case 0:
            sSpriteTextLines[i].palette = LoadObjPalette(gTextWhitePalette, 32);
            break;
        case 1:
            sSpriteTextLines[i].palette = LoadObjPalette(gTextGrayPalette, 32);
            break;
        case 2:
            sSpriteTextLines[i].palette = LoadObjPalette(gTextBrownPalette, 32);
            break;
        }
    }

    return sSpriteTextLines->palette;
}
#endif

#ifndef VERSION_EU
void SetSpriteTextSlot(s32 x, s32 y, TextChar* s, u8 slot, u8 a) {
    u16 g;
    u16 lo;
    u8 kind;
    u8 i;
    u8 j;
    g = 0;
    i = 0;
    j = 0;

    if (slot > 23) {
        return;
    }

    if (sSpriteTextLines == NULL) {
        return;
    }

    sSpriteTextLines[slot].x = x;
    sSpriteTextLines[slot].y = y;
    sSpriteTextLines[slot].font = 1;
    sSpriteTextLines[slot].visible = 1;
    sSpriteTextLines[slot].unk_53 = i;
    sSpriteTextLines[slot].useAlternatePalette = a;

    while (*s != 0) {
        u16 v;
        v = *(u16*)s;
        v = (v >> 8) | (v << 8);
        s += 2;

        switch (v & 0xFF00) {
        case 0x8100:
            v &= 0xFF;

            switch (v) {
            case 0x40:
                g = 0;
                break;
            case 0x41:
                g = 0xF5;
                break;
            case 0x42:
                g = 0xF6;
                break;
            case 0x45:
                g = 0xF9;
                break;
            case 0x48:
                g = 0xF1;
                break;
            case 0x49:
                g = 0xF0;
                break;
            case 0x5B:
                g = 0xFD;
                break;
            case 0x5C:
                g = 0xFC;
                break;
            case 0x60:
                g = 0xFE;
                break;
            case 0x63:
                g = 0xFB;
                break;
            case 0x75:
                g = 0xE8;
                break;
            case 0x76:
                g = 0xE9;
                break;
            case 0x77:
                g = 0xEA;
                break;
            case 0x78:
                g = 0xEB;
                break;
            case 0x69:
                g = 0xEC;
                break;
            case 0x6A:
                g = 0xED;
                break;
            case 0xA8:
                g = 0xE7;
                break;
            case 0xA9:
                g = 0xE6;
                break;
            }

            kind = 0;
            break;
        case 0x8200:
            lo = v & 0xFF;

            if (lo >= 0x60 && lo <= 0x79) {
                g = v + 0x7DAB;
            }

            if (lo >= 0x81 && lo <= 0x9A) {
                g = v + 0x7DA4;
            }

            if (lo >= 0x4F && lo <= 0x58) {
                g = v + 0x7DB2;
            }

            if (lo >= 0x9F && lo <= 0xF1) {
                g = v + 0x7DA0;
            }

            kind = 0;
            break;
        case 0x8300:
            lo = v & 0xFF;

            if (lo >= 0x40 && lo <= 0x7E) {
                g = v + 0x7D52;
            }

            if (lo >= 0x80 && lo <= 0x94) {
                g = v + 0x7D51;
            }

            kind = 0;
            break;
        case 0x8800:
            v &= 0xFF;

            if (v == 0xC5) {
                g = 9;
            }

            kind = 1;
            break;
        case 0x8900:
            switch (v & 0xFF) {
            case 0x9C:
                g = 4;
                break;
            case 0xA4:
                g = 0x31;
                break;
            case 0xAF:
                g = 0x1A;
                break;
            case 0xBD:
                g = 0x2F;
                break;
            }

            kind = 1;
            break;
        case 0x8A00:
            switch (v & 0xFF) {
            case 0x4F:
                g = 8;
                break;
            case 0x6D:
                g = 0x11;
                break;
            }

            kind = 1;
            break;
        case 0x8B00:
            switch (v & 0xFF) {
            case 0x41:
                g = 0x1E;
                break;
            case 0x43:
                g = 0x26;
                break;
            case 0x4C:
                g = 0x19;
                break;
            }

            kind = 1;
            break;
        case 0x8C00:
            switch (v & 0xFF) {
            case 0x4E:
                g = 6;
                break;
            case 0x78:
                g = 0x16;
                break;
            case 0xF5:
                g = 0x0B;
                break;
            case 0xAB:
                g = 0x37;
                break;
            case 0xA9:
                g = 0x0C;
                break;
            }

            kind = 1;
            break;
        case 0x8D00:
            switch (v & 0xFF) {
            case 0x73:
                g = 0x1F;
                break;
            case 0x90:
                g = 0x17;
                break;
            case 0xDF:
                g = 0x2E;
                break;
            }

            kind = 1;
            break;
        case 0x8E00:
            switch (v & 0xFF) {
            case 0xB8:
                g = 0x0D;
                break;
            case 0x76:
                g = 0x1C;
                break;
            case 0x84:
                g = 0x2C;
                break;
            case 0x9E:
                g = 0x1B;
                break;
            case 0xA1:
                g = 0x36;
                break;
            case 0xA9:
                g = 0x0F;
                break;
            case 0xD2:
                g = 0x15;
                break;
            case 0xD7:
                g = 0x12;
                break;
            }

            kind = 1;
            break;
        case 0x8F00:
            switch (v & 0xFF) {
            case 0x6F:
                g = 0x1D;
                break;
            case 0x8A:
                g = 0x21;
                break;
            case 0x97:
                g = 0x30;
                break;
            case 0xEA:
                g = 0x20;
                break;
            }

            kind = 1;
            break;
        case 0x9000:
            switch (v & 0xFF) {
            case 0x53:
                g = 3;
                break;
            case 0xD8:
                g = 1;
                break;
            case 0x6C:
                g = 0x2B;
                break;
            }

            kind = 1;
            break;
        case 0x9100:
            switch (v & 0xFF) {
            case 0xDE:
                g = 0x35;
                break;
            case 0xE5:
                g = 0;
                break;
            case 0x7A:
                g = 2;
                break;
            }

            kind = 1;
            break;
        case 0x9200:
            switch (v & 0xFF) {
            case 0x40:
                g = 0x27;
                break;
            case 0x42:
                g = 0x23;
                break;
            case 0x4E:
                g = 0x28;
                break;
            case 0x6D:
                g = 0x0E;
                break;
            case 0x86:
                g = 0x0A;
                break;
            }

            kind = 1;
            break;
        case 0x9300:
            v &= 0xFF;

            if (v == 0x90) {
                g = 45;
            }

            kind = 1;
            break;
        case 0x9400:
            switch (v & 0xFF) {
            case 0xDE:
                g = 0x29;
                break;
            case 0xC6:
                g = 0x2A;
                break;
            }

            kind = 1;
            break;
        case 0x9500:
            switch (v & 0xFF) {
            case 0x7C:
                g = 0x25;
                break;
            case 0xAA:
                g = 0x10;
                break;
            }

            kind = 1;
            break;
        case 0x9600:
            switch (v & 0xFF) {
            case 0x59:
                g = 5;
                break;
            case 0x6C:
                g = 0x24;
                break;
            case 0x82:
                g = 0x13;
                break;
            case 0xBD:
                g = 0x33;
                break;
            case 0xB0:
                g = 0x18;
                break;
            }

            kind = 1;
            break;
        case 0x9700:
            switch (v & 0xFF) {
            case 0x45:
                g = 0x14;
                break;
            case 0x46:
                g = 0x22;
                break;
            case 0x6C:
                g = 0x32;
                break;
            case 0x88:
                g = 0x38;
                break;
            case 0xDF:
                g = 0x34;
                break;
            case 0xE1:
                g = 7;
                break;
            }

            kind = 1;
            break;
        default:
            g = 0;
            kind = 0;
            break;
        }

        if (sSpriteTextLines[slot].glyphTiles[j] != NULL) {
            ReleaseObjTiles(sSpriteTextLines[slot].glyphTiles[j]);
        }

        g = ((u16*)gMsgFontBank0Frames[g])[3];

        switch (kind) {
        case 0:
            sSpriteTextLines[slot].glyphTiles[j] = LoadObjTiles(&gMsgFontBank0Tiles[g * 32], 128);
            break;
        case 1:
            sSpriteTextLines[slot].glyphTiles[j] = LoadObjTiles(&gMsgFontBank1Tiles[g * 32], 128);
            break;
        }

        j++;
        i++;
    }

    for (j = i; j < 16; j++) {
        if (sSpriteTextLines[slot].glyphTiles[j] != NULL) {
            ReleaseObjTiles(sSpriteTextLines[slot].glyphTiles[j]);
            sSpriteTextLines[slot].glyphTiles[j] = NULL;
        }
    }

    sSpriteTextLines[slot].length = i;
}
#endif

#ifndef VERSION_EU
void SetSpriteTextSlotXDigits(s32 a, s32 b, u8 v, u8 d, u8 e) {
    u8 buf[4];
    buf[0] = 0x78;
    buf[1] = v / 10;
    buf[2] = v - buf[1] * 10;
    buf[3] = 0;
    buf[1] += 0x30;
    buf[2] += 0x30;
    SetSpriteTextSlotAscii(a, b, buf, d, e);
}
#endif

#ifndef VERSION_EU
void SetSpriteTextSlotAscii(s32 x, s32 y, u8* s, u8 slot, u8 a) {
    u8 i;
    u8 len;
    u8 j;
    s16 idx;
    u8 count;
    idx = 0;

    if (slot > 23) {
        return;
    }

    if (sSpriteTextLines == NULL) {
        return;
    }

    sSpriteTextLines[slot].x = x;
    sSpriteTextLines[slot].y = y;
    sSpriteTextLines[slot].font = 2;
    sSpriteTextLines[slot].visible = 1;
    sSpriteTextLines[slot].useAlternatePalette = a;
    len = GetStringLength(s);

    if (len > 15) {
        len = 16;
    }

    i = 0;
    j = 0;
    count = len;

    for (; i < len; i++) {
        if ((u8)(s[i] - 48) <= 9) {
            idx = (u8)(s[i] + 209);
        }

        if ((u8)(s[i] - 65) <= 25) {
            idx = (u8)(s[i] + 202);
        }

        if ((u8)(s[i] - 97) <= 25) {
            idx = (u8)(s[i] + 196);
        }

        if (sSpriteTextLines[slot].glyphTiles[j] != NULL) {
            ReleaseObjTiles(sSpriteTextLines[slot].glyphTiles[j]);
        }

        idx = ((u8*)gMsgFontBank0Frames[idx])[6];
        sSpriteTextLines[slot].glyphTiles[j] = LoadObjTiles(&gMsgFontBank0Tiles[idx * 32], 128);
        j++;
    }

    len = count;

    for (j = len; j < 16; j++) {
        if (sSpriteTextLines[slot].glyphTiles[j] != NULL) {
            ReleaseObjTiles(sSpriteTextLines[slot].glyphTiles[j]);
            sSpriteTextLines[slot].glyphTiles[j] = NULL;
        }
    }

    sSpriteTextLines[slot].length = len;
}
#endif

#ifndef VERSION_EU
void DrawSpriteTextSlots() {
    s32 x;
    s32 y;
    void* g;
    u8 i;
    u8 j;
    u8 dx;

    for (i = 0; i < 24; i++) {
        if (sSpriteTextLines[i].visible != 1) {
            continue;
        }

        if (sSpriteTextLines[i].useAlternatePalette == 0) {
            g = sSpriteTextLines[i].palette;
        } else {
            g = sSpriteTextLines[i].alternatePalette;
        }

        x = sSpriteTextLines[i].x;
        y = sSpriteTextLines[i].y;
        dx = 0;

        for (j = 0; j < sSpriteTextLines[i].length; j++) {
            DrawSprite((x >> 8) + dx, y >> 8, gMsgFontBank0Frames[0], sSpriteTextLines[i].glyphTiles[j], g, NULL, 0, 50);

            if (sSpriteTextLines[i].font == 1) {
                dx += 10;
            } else if (sSpriteTextLines[i].font == 2) {
                dx += 10;
            }
        }
    }
}
#endif

#ifndef VERSION_EU
void HideSpriteTextSlot(u8 i) {
    sSpriteTextLines[i].visible = 0;
}

void ShowSpriteTextSlot(u8 i) {
    if (sSpriteTextLines[i].length != 0) {
        sSpriteTextLines[i].visible = 1;
    }
}

void SetSpriteTextSlotPosition(s32 x, s32 y, u8 i) {
    sSpriteTextLines[i].x = x;
    sSpriteTextLines[i].y = y;
}
#endif

#ifndef VERSION_EU
void FreeSpriteTextSlots() {
    u8 i;
    u8 j;

    for (i = 0; i < 24; i++) {
        for (j = 0; j < 16; j++) {
            if (sSpriteTextLines[i].glyphTiles[j] != NULL) {
                ReleaseObjTiles(sSpriteTextLines[i].glyphTiles[j]);
            }
        }

        FadeSetPaletteExcluded(sSpriteTextLines[i].palette->index, 0);
        ReleaseObjPalette(sSpriteTextLines[i].palette);
    }

    EwramFree(sSpriteTextLines);
    sSpriteTextLines = NULL;
}
#endif

#ifndef VERSION_EU
void InitBgTextLines(u8 bg) {
    u8 i;
    u8 j;
    GetBgCharBase(bg);
    GetBgScreenBase(bg);
    sBgTextLines = EwramAlloc(sizeof(BgTextLine) * 10);

    for (i = 0; i < 10; i++) {
        sBgTextLines[i].x = 0;
        sBgTextLines[i].y = 0;
        sBgTextLines[i].length = 0;
        sBgTextLines[i].bg = bg;
        sBgTextLines[i].glyphHeight = 16;
        sBgTextLines[i].dirty = 0;

        for (j = 0; j < 16; j++) {
            sBgTextLines[i].glyphs[j] = 0;
        }
    }

    sBgTextDrawQueued = 0;
}
#endif

#ifndef VERSION_EU
void SetBgTextLineNumber(u8 a, u8 b, u8 c, u8 d, u8 e, u8 f) {
    u8 buf[5];
    buf[1] = d / 10;
    buf[3] = d - buf[1] * 10;
    buf[0] = 0x82;
    buf[1] += 0x4F;
    buf[2] = 0x82;
    buf[3] += 0x4F;
    buf[4] = 0;
    SetBgTextLine(a, b, c, buf, e, f);
}
#endif

#ifndef VERSION_EU
void SetBgTextLine(u8 a, u8 b, u8 c, u8* s, u8 e, u8 f) {
    u32 off = 0x7DAB;
    u16 glyph;
    u8 i;
    u8 j;
    u16 w;
    u16 lo;
    glyph = 0;
    i = 0;
    j = 0;

    // @bug? Only 10 lines are allocated.
    if (e > 23) {
        return;
    }

    if (sBgTextLines == NULL) {
        return;
    }

    sBgTextLines[e].x = a;
    sBgTextLines[e].y = b;
    sBgTextLines[e].glyphHeight = c;
    sBgTextLines[e].dirty = 1;
    sBgTextLines[e].paletteIndex = f;

    while (*s != 0) {
        w = *(u16*)s;
        w = (w >> 8) | (w << 8);
        s += 2;

        if (c > 8) {
            switch (w & 0xFF00) {
            case 0x8100:
                if ((w & 0xFF) > 0x5A) {
                    glyph = 0xFD;
                }

                if ((w & 0xFF) == 0x40) {
                    glyph = 0xFFFF;
                }

                break;
            case 0x8200:
                lo = w & 0xFF;

                if (lo >= 0x60 && lo <= 0x79) {
                    glyph = w + off;
                }

                if (lo >= 0x81 && lo <= 0x9A) {
                    glyph = w + 0x7DA4;
                }

                if (lo >= 0x4F && lo <= 0x58) {
                    glyph = w + 0x7DB2;
                }

                if (lo >= 0x9F && lo <= 0xF1) {
                    glyph = w + 0x7DA0;
                }

                break;
            case 0x8300:
                lo = w & 0xFF;

                if (lo >= 0x40 && lo <= 0x7E) {
                    glyph = w + 0x7D52;
                }

                if (lo >= 0x80 && lo <= 0x94) {
                    glyph = w + 0x7D51;
                }

                break;
            }
        } else {
            switch (w & 0xFF00) {
            case 0x8100:
                w &= 0xFF;

                if (w == 0x40) {
                    glyph = 0xFFFF;
                }

                break;
            case 0x8200:
                lo = w & 0xFF;

                if (lo >= 0x4F && lo <= 0x58) {
                    glyph = w + 0x7DC1;
                }

                if (lo >= 0x81 && lo <= 0x84) {
                    glyph = w + 0x7D99;
                }

                if (lo == 0x98) {
                    glyph = 15;
                }

                break;
            }
        }

        sBgTextLines[e].glyphs[j] = glyph;
        j++;
        i++;
    }

    sBgTextLines[e].length = i;

    if (!sBgTextDrawQueued) {
        QueueVTransCallback(DrawBgTextLines);
        sBgTextDrawQueued = 1;
    }
}
#endif

#ifndef VERSION_EU
void DrawBgTextLines() {
    u8* screen;
    u8 n;
    u8 k;
    u16* src;
    u8* dst;
    u8* p;
    u8 tx;
    u8 ty;
    u8 sx;
    u8 h;
    u16 glyph;
    u8 sy;
    u8 y;
    u8 yy;
    u8 pal;
    u32 cur;
    u32 pix;
    u16 tile;

    for (n = 0; n < 10; n++) {
        if (sBgTextLines[n].dirty != 1) {
            continue;
        }

        sBgTextLines[n].dirty = 0;

        for (k = 0; k < sBgTextLines[n].length; k++) {
            glyph = sBgTextLines[n].glyphs[k];
            pal = sBgTextLines[n].paletteIndex;
            h = sBgTextLines[n].glyphHeight;

            if (h > 8) {
                tx = (k * 12 + sBgTextLines[n].x) >> 3;
                ty = sBgTextLines[n].y >> 3;
                sx = k * 12 + sBgTextLines[n].x - tx * 8;
                sy = sBgTextLines[n].y - ty * 8;
                dst = (u8*)GetBgCharBase(sBgTextLines[n].bg) + (tx + 1) * 32 + ty * 1024;
                screen = GetBgScreenBase(sBgTextLines[n].bg);
                tile = ((u16*)gMsgFontBank0Frames[glyph])[3];
                src = (u16*)&gMsgFontBank0Tiles[tile * 32];
                p = dst;

                for (y = sy, yy = 0; y < sy + h; y++, yy += 2) {
                    if (glyph == 0xFFFF) {
                        pix = 0;
                        cur = 0;
                    } else {
                        s32 q;
                        cur = *(u32*)(p + (y & 7) * 4 + (u8)(y >> 3) * 1024);
                        q = yy & 15;
                        q += (u16)((yy >> 4) * 32);
                        pix = src[q] | ((u32)src[q + 1] << 16);
                    }

                    *(u32*)(p + (y & 7) * 4 + (u8)(y >> 3) * 1024) = cur | (pix << (sx * 4));

                    if (sx != 0) {
                        *(u32*)(p + (y & 7) * 4 + (u8)(y >> 3) * 1024 + 32) = pix >> (32 - sx * 4);
                    }
                }

                {
                    s32 t0;
                    s32 ty1;
                    s32 t1;
                    s32 tx2;
                    t0 = ty * 32;
                    *(u16*)(screen + tx * 2 + ty * 64) = (tx + 1 + t0) | (pal << 12);
                    ty1 = ty + 1;
                    t1 = ty1 * 32;
                    *(u16*)(screen + tx * 2 + ty1 * 64) = (tx + 1 + t1) | (pal << 12);

                    if (sy != 0) {
                        s32 r = ty + 2;
                        s32 t = r * 32;
                        *(u16*)(screen + tx * 2 + r * 64) = (tx + 1 + t) | (pal << 12);
                    }

                    tx2 = tx + 2;

                    if (sx != 0) {
                        *(u16*)(screen + tx * 2 + ty * 64 + 2) = (tx2 + t0) | (pal << 12);
                        *(u16*)(screen + tx * 2 + ty1 * 64 + 2) = (tx2 + t1) | (pal << 12);

                        if (sy != 0) {
                            s32 r = ty + 2;
                            s32 t = r * 32;
                            *(u16*)(screen + tx * 2 + r * 64 + 2) = (tx2 + t) | (pal << 12);
                        }
                    }
                }

                for (y = sy, yy = 0; y < sy + h; y++, yy += 2) {
                    if (glyph == 0xFFFF) {
                        cur = 0;
                        pix = 0;
                    } else {
                        cur = *(u32*)(p + (y & 7) * 4 + (u8)(y >> 3) * 1024 + 32);
                        pix = src[(yy & 15) + (yy >> 4) * 32 + 16] |
                              ((u32)src[(yy & 15) + (yy >> 4) * 32 + 17] << 16);
                    }

                    *(u32*)(p + (y & 7) * 4 + (u8)(y >> 3) * 1024 + 32) = cur | (pix << (sx * 4));

                    if (sy != 0) {
                        s32 r = ty + 2;
                        s32 t = r * 32;
                        *(u16*)(screen + tx * 2 + r * 64 + 2) = (tx + 2 + t) | (pal << 12);
                    }

                    if (sx != 0) {
                        *(u32*)(p + (y & 7) * 4 + (u8)(y >> 3) * 1024 + 64) = pix >> (32 - sx * 4);
                        *(u16*)(screen + tx * 2 + ty * 64 + 4) = (tx + 3 + ty * 32) | (pal << 12);

                        {
                            s32 ty1 = ty + 1;
                            s32 t1 = ty1 * 32;
                            *(u16*)(screen + tx * 2 + ty1 * 64 + 4) = (tx + 3 + t1) | (pal << 12);

                            if (sy != 0) {
                                s32 r = ty + 2;
                                *(u16*)(screen + tx * 2 + r * 64 + 4) = (tx + 3 + r * 32) | (pal << 12);
                            }
                        }
                    }
                }

                {
                    s32 tx2;
                    s32 t0;
                    s32 ty1;
                    s32 t1;
                    tx2 = tx + 2;
                    t0 = ty * 32;
                    *(u16*)(screen + tx * 2 + ty * 64 + 2) = (tx2 + t0) | (pal << 12);
                    ty1 = ty + 1;
                    t1 = ty1 * 32;
                    *(u16*)(screen + tx * 2 + ty1 * 64 + 2) = (tx2 + t1) | (pal << 12);

                    if (sx != 0) {
                        *(u16*)(screen + tx * 2 + ty * 64 + 4) = (tx + 3 + t0) | (pal << 12);
                        *(u16*)(screen + tx * 2 + ty1 * 64 + 4) = (tx + 3 + t1) | (pal << 12);

                        if (sy != 0) {
                            s32 r = ty + 2;
                            s32 t = r * 32;
                            *(u16*)(screen + tx * 2 + r * 64 + 4) = (tx + 3 + t) | (pal << 12);
                        }
                    }
                }
            } else {
                tx = (k * 8 + sBgTextLines[n].x) >> 3;
                ty = sBgTextLines[n].y >> 3;
                sx = k * 8 + sBgTextLines[n].x - tx * 8;
                sy = sBgTextLines[n].y - ty * 8;
                dst = (u8*)GetBgCharBase(sBgTextLines[n].bg) + (tx + 1) * 32 + ty * 1024;
                screen = GetBgScreenBase(sBgTextLines[n].bg);
                tile = ((u16*)gBgTextSmallFontFrames[glyph])[3];
                src = (u16*)&gBgTextSmallFontTiles[tile * 32];
                p = dst;

                for (y = sy, yy = 0; y < sy + h; y++, yy += 2) {
                    if (glyph == 0xFFFF) {
                        cur = 0;
                        pix = 0;
                    } else {
                        s32 q;
                        cur = *(u32*)(p + (y & 7) * 4 + (u8)(y >> 3) * 1024);
                        q = yy & 15;
                        q += (yy >> 4) * 32;
                        pix = src[q] | ((u32)src[q + 1] << 16);
                    }

                    *(u32*)(p + (y & 7) * 4 + (u8)(y >> 3) * 1024) = cur | (pix << (sx * 4));

                    if (sx != 0) {
                        *(u32*)(p + (y & 7) * 4 + (u8)(y >> 3) * 1024 + 32) = pix >> (32 - sx * 4);
                    }
                }

                {
                    s32 t0;
                    s32 ty1;
                    s32 t1;
                    t0 = ty * 32;
                    *(u16*)(screen + tx * 2 + ty * 64) = (tx + 1 + t0) | (pal << 12);
                    ty1 = ty + 1;
                    t1 = ty1 * 32;
                    *(u16*)(screen + tx * 2 + ty1 * 64) = (tx + 1 + t1) | (pal << 12);

                    if (sy != 0) {
                        s32 r = ty + 2;
                        s32 t = r * 32;
                        *(u16*)(screen + tx * 2 + r * 64) = (tx + 1 + t) | (pal << 12);
                    }

                    if (sx != 0) {
                        *(u16*)(screen + tx * 2 + ty * 64 + 2) = (tx + 2 + ty * 32) | (pal << 12);
                        *(u16*)(screen + tx * 2 + ty1 * 64 + 2) = (tx + 2 + ty1 * 32) | (pal << 12);

                        if (sy != 0) {
                            s32 r = ty + 2;
                            s32 t = r * 32;
                            *(u16*)(screen + tx * 2 + r * 64 + 2) = (tx + 2 + t) | (pal << 12);
                        }
                    }
                }
            }
        }
    }

    sBgTextDrawQueued = 0;
}
#endif

#ifndef VERSION_EU
void FreeBgTextLines() {
    EwramFree(sBgTextLines);
    sBgTextLines = NULL;
}
#endif

u16 InitMsgGlyphSprites(s32 a) {
    s32 i;

    sMsgGlyphSprites = EwramAlloc(sizeof(TextGlyphSprite) * 128);

    for (i = 0; i < 128; i++) {
        sMsgGlyphSprites[i].x = 0;
        sMsgGlyphSprites[i].y = 0;
        sMsgGlyphSprites[i].tiles = NULL;
        sMsgGlyphSprites[i].palette = NULL;
        sMsgGlyphSprites[i].alternatePalette = NULL;
        sMsgGlyphSprites[i].visible = 0;
        sMsgGlyphSprites[i].useAlternatePalette = 0;

        switch (a) {
        case 0:
            sMsgGlyphSprites[i].palette = LoadObjPalette(gTextBrownPalette, 32);
            break;
        case 1:
            sMsgGlyphSprites[i].palette = LoadObjPalette(gTextWhitePalette, 32);
            break;
        case 2:
            sMsgGlyphSprites[i].palette = LoadObjPalette(gTextGrayPalette, 32);
            break;
        }

        FadeSetPaletteExcluded(sMsgGlyphSprites[i].palette->index + 16, 1);
    }

    sTextEntryCount = 0;
    return sMsgGlyphSprites->palette->index;
}

u16 InitMsgGlyphSpritesAltPalette5(s32 a) {
    s32 i;

    sMsgGlyphSprites = EwramAlloc(sizeof(TextGlyphSprite) * 128);

    for (i = 0; i < 128; i++) {
        sMsgGlyphSprites[i].x = 0;
        sMsgGlyphSprites[i].y = 0;
        sMsgGlyphSprites[i].tiles = NULL;
        sMsgGlyphSprites[i].palette = NULL;
        sMsgGlyphSprites[i].alternatePalette = NULL;
        sMsgGlyphSprites[i].visible = 0;
        sMsgGlyphSprites[i].useAlternatePalette = 0;

        switch (a) {
        case 0:
            sMsgGlyphSprites[i].palette = LoadObjPalette(gTextBrownPalette, 32);
            break;
        case 1:
            sMsgGlyphSprites[i].palette = LoadObjPalette(gTextWhitePalette, 32);
            break;
        case 2:
            sMsgGlyphSprites[i].palette = LoadObjPalette(gTextGrayPalette, 32);
            break;
        }

        sMsgGlyphSprites[i].alternatePalette = LoadTextPalette(5);
        FadeSetPaletteExcluded(sMsgGlyphSprites[i].palette->index + 16, 1);
        FadeSetPaletteExcluded(sMsgGlyphSprites[i].alternatePalette->index + 16, 1);
    }

    sTextEntryCount = 0;
    return sMsgGlyphSprites->palette->index;
}

u16 InitMsgGlyphSpritesAltPalette3(s32 a) {
    s32 i;

    sMsgGlyphSprites = EwramAlloc(sizeof(TextGlyphSprite) * 128);

    for (i = 0; i < 128; i++) {
        sMsgGlyphSprites[i].x = 0;
        sMsgGlyphSprites[i].y = 0;
        sMsgGlyphSprites[i].tiles = NULL;
        sMsgGlyphSprites[i].palette = NULL;
        sMsgGlyphSprites[i].alternatePalette = NULL;
        sMsgGlyphSprites[i].visible = 0;
        sMsgGlyphSprites[i].useAlternatePalette = 0;

        switch (a) {
        case 0:
            sMsgGlyphSprites[i].palette = LoadObjPalette(gTextBrownPalette, 32);
            break;
        case 1:
            sMsgGlyphSprites[i].palette = LoadObjPalette(gTextWhitePalette, 32);
            break;
        case 2:
            sMsgGlyphSprites[i].palette = LoadObjPalette(gTextGrayPalette, 32);
            break;
        }

        sMsgGlyphSprites[i].alternatePalette = LoadTextPalette(3);
        FadeSetPaletteExcluded(sMsgGlyphSprites[i].palette->index + 16, 1);
        FadeSetPaletteExcluded(sMsgGlyphSprites[i].alternatePalette->index + 16, 1);
    }

    sTextEntryCount = 0;
    return sMsgGlyphSprites->palette->index;
}

s32 GetMsgTextWidth(const TextChar* a) {
    u16 sum;
    s32 v;

    sum = 0;

    while (*a != 0) {
        v = 0;

        if (*a != 10) {
#ifdef VERSION_US
            if ((u16)(*a - 32) <= 223) {
#else
            if (*a > 31) {
#endif
                v = *a;
            } else {
                switch (*a) {
                case 0xE000:
                    v = 25;
                    break;
                case 0x2191:
                    v = 10;
                    break;
                case 0x2193:
                    v = 11;
                    break;
                case 0x2190:
                    v = 12;
                    break;
                case 0x2192:
                    v = 13;
                    break;
                case 0x300C:
                    v = 1;
                    break;
                case 0x300D:
                    v = 2;
                    break;
                case 0x300E:
                    v = 3;
                    break;
                case 0x300F:
                    v = 4;
                    break;
                case 0x203B:
                    v = 6;
                    break;
                case 0x266A:
                    v = 18;
                    break;
                case 0x2642:
                    v = 8;
                    break;
                case 0x2640:
                    v = 9;
                    break;
                case 0x2605:
                    v = 21;
                    break;
                }
            }

            sum = sLatinGlyphWidths.widths[v] + ((sum << 16) >> 16);
        }

        a++;
    }

    return (s16)sum;
}

#ifdef VERSION_EU
#define MSG_LATIN_CODE(wide, byte) (byte)
#else
#define MSG_LATIN_CODE(wide, byte) (wide)
#endif
u8 LayoutMsgGlyphsPage(s32 x, s32 y, MsgLatinChar* s, MsgLatinChar** d) {
    s32 cx;
    s32 cy;
    s32 f;

    cx = 0;
    cy = 0;
    f = 0;

    if (sMsgGlyphSprites == NULL) {
        return 0;
    }

    sTextEntryCount = 0;

    while (*s != 0) {
        s32 v = 0;

        sMsgGlyphSprites[sTextEntryCount].x = x + cx;
        sMsgGlyphSprites[sTextEntryCount].y = y + cy;
        sMsgGlyphSprites[sTextEntryCount].visible = 1;

        if (*s == MSG_LATIN_CODE(0x4079, 29)) {
            f = 1;
            s++;
        }

        if (*s == MSG_LATIN_CODE(0x4000, 30)) {
            f = 0;
            s++;
        }

        sMsgGlyphSprites[sTextEntryCount].useAlternatePalette = f;

        if (*s == MSG_LATIN_CODE(10, 31)) {
            cx = 0;
            cy += 0xC00;
        } else {
#ifdef VERSION_EU
            v = *s;
#else
            if ((u16)(*s - 32) <= 223) {
                v = *s;
            } else {
                switch (*s) {
                case 0xE000:
                    v = 25;
                    break;
                case 0x2191:
                    v = 10;
                    break;
                case 0x2193:
                    v = 11;
                    break;
                case 0x2190:
                    v = 12;
                    break;
                case 0x2192:
                    v = 13;
                    break;
                case 0x300C:
                    v = 1;
                    break;
                case 0x300D:
                    v = 2;
                    break;
                case 0x300E:
                    v = 3;
                    break;
                case 0x300F:
                    v = 4;
                    break;
                case 0x203B:
                    v = 6;
                    break;
                case 0x266A:
                    v = 18;
                    break;
                case 0x2642:
                    v = 8;
                    break;
                case 0x2640:
                    v = 9;
                    break;
                case 0x2605:
                    v = 21;
                    break;
                case 0x25A0:
                    v = 17;
                    break;
                }
            }
#endif

            if (sMsgGlyphSprites[sTextEntryCount].tiles != NULL) {
                ReleaseObjTiles(sMsgGlyphSprites[sTextEntryCount].tiles);
                sMsgGlyphSprites[sTextEntryCount].tiles = NULL;
            }

            cx += (s16)sLatinGlyphWidths.widths[v] << 8;

            if (v != 32) {
                v = ((u16*)gMsgLatinFontFrames[v])[3];
                sMsgGlyphSprites[sTextEntryCount].tiles = LoadObjTiles(&gMsgLatinFontTiles[v * 32], 128);
            }

            sTextEntryCount++;

            if (cx > 0x9B00) {
                cx = 0;
                cy += 0xC00;
            }
        }

        s++;

        if (cy > 0x1800) {
            *d = s;
            return sTextEntryCount;
        }
    }

    *d = NULL;
    return sTextEntryCount;
}

u8 LayoutMsgGlyphs(s32 x, s32 y, const MsgLatinChar* s) {
    s32 cx;
    s32 cy;
    s32 f;

    cx = 0;
    cy = 0;
    f = 0;

    if (sMsgGlyphSprites == NULL) {
        return 0;
    }

    sTextEntryCount = 0;

    while (*s != 0) {
        s32 v = 0;

        sMsgGlyphSprites[sTextEntryCount].x = x + cx;
        sMsgGlyphSprites[sTextEntryCount].y = y + cy;
        sMsgGlyphSprites[sTextEntryCount].visible = 1;

        if (*s == MSG_LATIN_CODE(0x4079, 29)) {
            f = 1;
            s++;
        }

        if (*s == MSG_LATIN_CODE(0x4000, 30)) {
            f = 0;
            s++;
        }

        sMsgGlyphSprites[sTextEntryCount].useAlternatePalette = f;

        if (*s == MSG_LATIN_CODE(10, 31)) {
            cx = 0;
            cy += 0xC00;
        } else {
#ifdef VERSION_EU
            v = *s;
#else
            if ((u16)(*s - 32) <= 223) {
                v = *s;
            } else {
                switch (*s) {
                case 0xE000:
                    v = 25;
                    break;
                case 0x2191:
                    v = 10;
                    break;
                case 0x2193:
                    v = 11;
                    break;
                case 0x2190:
                    v = 12;
                    break;
                case 0x2192:
                    v = 13;
                    break;
                case 0x300C:
                    v = 1;
                    break;
                case 0x300D:
                    v = 2;
                    break;
                case 0x300E:
                    v = 3;
                    break;
                case 0x300F:
                    v = 4;
                    break;
                case 0x203B:
                    v = 6;
                    break;
                case 0x266A:
                    v = 18;
                    break;
                case 0x2642:
                    v = 8;
                    break;
                case 0x2640:
                    v = 9;
                    break;
                case 0x2605:
                    v = 21;
                    break;
                case 0x25A0:
                    v = 17;
                    break;
                }
            }
#endif

            if (sMsgGlyphSprites[sTextEntryCount].tiles != NULL) {
                ReleaseObjTiles(sMsgGlyphSprites[sTextEntryCount].tiles);
                sMsgGlyphSprites[sTextEntryCount].tiles = NULL;
            }

            cx += (s16)sLatinGlyphWidths.widths[v] << 8;

            if (v != 32) {
                v = ((u16*)gMsgLatinFontFrames[v])[3];
                sMsgGlyphSprites[sTextEntryCount].tiles = LoadObjTiles(&gMsgLatinFontTiles[v * 32], 128);
            }

            sTextEntryCount++;

            if (cx > 0x9B00) {
                cx = 0;
                cy += 0xC00;
            }
        }

        s++;
    }

    return sTextEntryCount;
}

#ifndef VERSION_EU
u8 LayoutMsgGlyphsSjis(s32 x, s32 y, const u8* s) {
    u16 w;
    u8 t;
    s32 cx;
    s32 cy;
    s32 px;
    w = 0;
    t = 0;
    cx = 0;
    cy = 0;
    px = 0;

    if (sMsgGlyphSprites == NULL) {
        return 0;
    }

    sTextEntryCount = 0;

    while (*s != 0) {
        u16 v;
        w = 0;
        sMsgGlyphSprites[sTextEntryCount].x = x + cx;
        sMsgGlyphSprites[sTextEntryCount].y = y + cy;

        sMsgGlyphSprites[sTextEntryCount].visible = 1;

        if (*(u16*)s == 0x6E6E) {
            cx = 0;
            cy += 0xC00;
            s += 2;
        } else {
            v = *(u16*)s;
            v = (v / 256) | (v << 8);
            s += 2;

            if ((v & 0xFF00) == 0x8100) {
                switch (v & 0xFF) {
                case 0x40:
                    w = 0;
                    t = 0;
                    break;
                case 0x41:
                    w = 0xF5;
                    t = 0;
                    break;
                case 0x42:
                    w = 0xF6;
                    t = 0;
                    break;
                case 0x44:
                    w = 0xF7;
                    t = 0;
                    break;
                case 0x45:
                    w = 0xF9;
                    t = 0;
                    break;
                case 0x48:
                    w = 0xF1;
                    t = 0;
                    break;
                case 0x49:
                    w = 0xF0;
                    t = 0;
                    break;
                case 0x58:
                    w = 20;
                    t = 2;
                    break;
                case 0x5B:
                    w = 0xFD;
                    t = 0;
                    break;
                case 0x5C:
                    w = 0xFC;
                    t = 0;
                    break;
                case 0x60:
                    w = 0xFE;
                    t = 0;
                    break;
                case 0x63:
                    w = 0xFB;
                    t = 0;
                    break;
                case 0x75:
                    w = 0xE8;
                    t = 0;
                    break;
                case 0x76:
                    w = 0xE9;
                    t = 0;
                    break;
                case 0x77:
                    w = 0xEA;
                    t = 0;
                    break;
                case 0x78:
                    w = 0xEB;
                    t = 0;
                    break;
                case 0x66:
                    w = 0xFF;
                    t = 0;
                    break;
                case 0x69:
                    w = 0xEC;
                    t = 0;
                    break;
                case 0x6A:
                    w = 0xED;
                    t = 0;
                    break;
                case 0xA8:
                    w = 0xE7;
                    t = 0;
                    break;
                case 0xA9:
                    w = 0xE6;
                    t = 0;
                    break;
                case 0x7B:
                    w = 0xDF;
                    t = 0;
                    break;
                case 0x7C:
                    w = 0xFC;
                    t = 0;
                    break;
                case 0xA6:
                    w = 0xEE;
                    t = 0;
                    break;
                case 0x81:
                    w = 0xEF;
                    t = 0;
                    break;
                case 0x93:
                    w = 0xF2;
                    t = 0;
                    break;
                case 0x96:
                    w = 0xF4;
                    t = 0;
                    break;
                case 0x5E:
                    w = 0xF3;
                    t = 0;
                    break;
                case 0x43:
                    w = 0xF8;
                    t = 0;
                    break;
                case 0x9A:
                    w = 0x8E;
                    t = 0;
                    break;
                }

                if (sTextEntryCount != 0 &&
                    (v == 0x8141 || v == 0x8142 || v > 0x8177 || v == 0x8144 ||
                     (v == 0x8148 || v == 0x8149)) &&
                    cx == 0 && cy > 0) {
                    cx = px;
                    cx += 0xA00;
                    cy -= 0xC00;
                    sMsgGlyphSprites[sTextEntryCount].x = x + cx;
                    sMsgGlyphSprites[sTextEntryCount].y = y + cy;
                }
            } else {
                GetSjisGlyph(v, &w, &t);
            }

            if (sMsgGlyphSprites[sTextEntryCount].tiles != NULL) {
                ReleaseObjTiles(sMsgGlyphSprites[sTextEntryCount].tiles);
            }

            px = cx;

            if ((u16)(v - 0x8260) <= 58) {
                cx += 0xA00;
            } else {
                cx += 0xA00;
            }

            if (cx > 0x8C00) {
                cx = 0;
                cy += 0xC00;
            }

            switch (t) {
            case 0:
                w = ((u16*)gMsgFontBank0Frames[w])[3];
                sMsgGlyphSprites[sTextEntryCount].tiles = LoadObjTiles(&gMsgFontBank0Tiles[w * 32], 128);
                break;
            case 1:
                w = ((u16*)gMsgFontBank1Frames[w])[3];
                sMsgGlyphSprites[sTextEntryCount].tiles = LoadObjTiles(&gMsgFontBank1Tiles[w * 32], 128);
                break;
            case 2:
                w = ((u16*)gMsgFontBank2Frames[w])[3];
                sMsgGlyphSprites[sTextEntryCount].tiles = LoadObjTiles(&gMsgFontBank2Tiles[w * 32], 128);
                break;
            case 3:
                w = ((u16*)gMsgFontBank3Frames[w])[3];
                sMsgGlyphSprites[sTextEntryCount].tiles = LoadObjTiles(&gMsgFontBank3Tiles[w * 32], 128);
                break;
            }

            sTextEntryCount++;
        }
    }

    return sTextEntryCount;
}
#endif

#ifdef VERSION_EU
#define MSG_FONT_FRAMES gMsgLatinFontFrames
#else
#define MSG_FONT_FRAMES gMsgFontBank0Frames
#endif

void DrawMsgGlyphs(u8 n) {
    u8 i;

    for (i = 0; i < n; i++) {
        TextGlyphSprite* b = sMsgGlyphSprites;

        if (b[i].visible == 1) {
            s32 x = b[i].x;
            s32 y = b[i].y;

            if (b[i].useAlternatePalette) {
                if (b[i].tiles != NULL) {
                    DrawSpriteUnsorted(x >> 8, y >> 8, MSG_FONT_FRAMES[0], b[i].tiles, b[i].alternatePalette, 0);
                }
            } else {
                if (b[i].tiles != NULL) {
                    DrawSpriteUnsorted(x >> 8, y >> 8, MSG_FONT_FRAMES[0], b[i].tiles, b[i].palette, 0);
                }
            }
        }
    }
}

void FreeMsgGlyphSprites() {
    u8 i;

    for (i = 0; i < 128; i++) {
        if (sMsgGlyphSprites[i].tiles != NULL) {
            ReleaseObjTiles(sMsgGlyphSprites[i].tiles);
        }

        if (sMsgGlyphSprites[i].palette != NULL) {
            ReleaseObjPalette(sMsgGlyphSprites[i].palette);
        }

        if (sMsgGlyphSprites[i].alternatePalette != NULL) {
            ReleaseObjPalette(sMsgGlyphSprites[i].alternatePalette);
        }
    }

    EwramFree(sMsgGlyphSprites);
}

void HideMsgGlyphs() {
    u8 i;

    for (i = 0; i < 128; i++) {
        sMsgGlyphSprites[i].visible = 0;
    }
}

#ifndef VERSION_EU
u16 LoadTwoDigitTextTileArray(u8 v, void** out) {
    u8 buf[8];
    u8 q;
    q = v / 10;

    if (q != 0) {
        buf[1] = v / 10;
        buf[3] = v - buf[1] * 10;
        buf[0] = 0x82;
        buf[1] += 0x4F;
        buf[2] = 0x82;
        buf[3] += 0x4F;
        buf[4] = 0;
    } else {
        buf[1] = v + 0x4F;
        buf[0] = 0x82;
        buf[2] = 0;
    }

    return LoadTextTileArray((TextChar*)buf, out);
}
#endif

void InitTextTileArray(void** p, u8 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        *p++ = NULL;
    }
}

void FreeTextTileArray(void** p, u8 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        if (*p != NULL) {
            ReleaseObjTiles(*p);
            *p = NULL;
        }

        p++;
    }
}

u16 LoadTwoDigitTextSlots(u8 v, TextSlot* out) {
#ifdef VERSION_JP
    u8 buf[8];
    s32 q;

    q = v / 10;

    if ((u8)q != 0) {
        buf[1] = v / 10;
        buf[3] = v - buf[1] * 10;
        buf[0] = 0x82;
        buf[1] += 0x4F;
        buf[2] = 0x82;
        buf[3] += 0x4F;
        buf[4] = 0;
    } else {
        buf[1] = v + 0x4F;
        buf[0] = 0x82;
        buf[2] = 0;
    }
#else
    TextChar buf[4];
    TextChar* p;
    TextChar c;
    TextChar end;

    if (v > 9) {
        p = buf;
        c = v / 10 + '0';
        end = 0;
        p[0] = c;
        buf[1] = v - (u8)(v / 10) * 10 + '0';
        buf[2] = end;
    } else {
        buf[0] = v + '0';
        buf[1] = 0;
    }
#endif

    return LoadTextSlots(buf, out);
}

void InitTextSlots(TextSlot* p, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        p->tiles = NULL;
        p->advance = 0;
        p++;
    }
}

void FreeTextSlots(TextSlot* p, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        if (p->tiles != NULL) {
            ReleaseObjTiles(p->tiles);
            p->tiles = NULL;
        }

        p->advance = 0;
        p++;
    }
}

s16 GetTextSlotsWidth(TextSlot* p, u8 n) {
    s16 x;
    s32 i;

    x = 0;

    for (i = 0; i < n; i++) {
        if (p[i].tiles != NULL) {
            if (p[i].advance != -1) {
                x += p[i].advance;
            } else {
                x += 3;
            }
        } else {
            return x;
        }
    }

    return x;
}

#ifdef VERSION_EU
s16 GetTextSlotsMaxLineWidth(TextSlot* p, u8 n) {
    s16 max = 0;
    s16 x = 0;
    s32 i;

    for (i = 0; i < n; i++) {
        if (p[i].tiles != NULL) {
            if (p[i].advance != -1) {
                x += p[i].advance;
            } else {
                x += 3;
            }
        } else {
            if (x > max) {
                max = x;
            }

            x = 0;
        }
    }

    if (max > x) {
        return max;
    }

    return x;
}
#endif

#if defined(VERSION_JP) || defined(VERSION_EU)
#define MSG_CHAR(p) (*(u8*)(p))
#else
#define MSG_CHAR(p) (*(p))
#endif

s32 GetTextLength(const void* s) {
#ifdef VERSION_JP
    const u16* p = s;
    u16 n = 0;
#elif defined(VERSION_EU)
    u16 n = 0;
    const u8* p = s;
#else
    u16 n = 0;
    const u16* p = s;
#endif

    while (MSG_CHAR(p) != 0) {
        n++;
        p++;
    }

    return n;
}

u16 LoadTextSlots(const void* a, TextSlot* b) {
#ifdef VERSION_JP
    return LoadJapaneseTextSlots(a, b);
#else
    return LoadLatinTextSlots(a, b);
#endif
}

s32 LoadLatinTextSlots(const u16* a, TextSlot* b) {
    s32 n;

    n = 0;
    sTextEntryCount = n;

    while (MSG_CHAR(a) != 0) {
        s32 v = 0;

#ifdef VERSION_EU
        if (MSG_CHAR(a) == 31) {
#else
        if (MSG_CHAR(a) == 10) {
#endif
            if (b->tiles != NULL) {
                ReleaseObjTiles(b->tiles);
                b->tiles = NULL;
            }

            b->advance = 0;
        } else {
#ifdef VERSION_EU
            v = MSG_CHAR(a);
#else
#ifdef VERSION_JP
            if (MSG_CHAR(a) > 31) {
#else
            if ((u16)(MSG_CHAR(a) - 32) <= 223) {
#endif
                v = MSG_CHAR(a);
            } else {
                switch (MSG_CHAR(a)) {
                case 0xE000:
                    v = 25;
                    break;
                case 0x2191:
                    v = 10;
                    break;
                case 0x2193:
                    v = 11;
                    break;
                case 0x2190:
                    v = 12;
                    break;
                case 0x2192:
                    v = 13;
                    break;
                case 0x300C:
                    v = 1;
                    break;
                case 0x300D:
                    v = 2;
                    break;
                case 0x300E:
                    v = 3;
                    break;
                case 0x300F:
                    v = 4;
                    break;
                case 0x203B:
                    v = 6;
                    break;
                case 0x266A:
                    v = 18;
                    break;
                case 0x2642:
                    v = 8;
                    break;
                case 0x2640:
                    v = 9;
                    break;
                case 0x2605:
                    v = 21;
                    break;
                case 0x25A0:
                    v = 17;
                    break;
                default:
                    v = 0;
                    break;
                }
            }
#endif

            if (b->tiles != NULL) {
                ReleaseObjTiles(b->tiles);
                b->tiles = NULL;
            }

            if (v != 32) {
                b->advance = sLatinGlyphWidths.widths[v];
            } else {
                b->advance = 255;
            }

            v = ((u16*)gMsgLatinFontFrames[v])[3];
            b->tiles = LoadObjTiles(&gMsgLatinFontTiles[v * 32], 128);
            b->useAlternatePalette = n;
        }

        sTextEntryCount++;
        b++;
#if defined(VERSION_EU) || defined(VERSION_JP)
        a = (u16*)((u8*)a + 1);
#else
        a++;
#endif
    }

    return sTextEntryCount;
}

#ifndef VERSION_EU
s32 LoadJapaneseTextSlots(const u16* a, TextSlot* b) {
    u8 buf[2];
    u16* c;
    u16 w;
    u8 t;
    u8 n;

    w = 0;
    t = 0;
    n = 0;

    while (MSG_CHAR(a) != 0) {
        u16 v;

#ifdef VERSION_JP
        buf[0] = ((u8*)a)[0];
        buf[1] = ((u8*)a)[1];
#else
        buf[0] = a[0];
        buf[1] = a[1];
#endif
        c = (u16*)buf;

        if (*c == 0x6E6E) {
#ifdef VERSION_JP
            a = (u16*)((u8*)a + 2);
#else
            a += 2;
#endif

            if (b->tiles != NULL) {
                ReleaseObjTiles(b->tiles);
            }

            b->tiles = NULL;
            b->advance = 0;
        } else {
            v = *c;
            v = (v / 256) | (v << 8);
#ifdef VERSION_JP
            a = (u16*)((u8*)a + 2);
#else
            a += 2;
#endif

            if ((v & 0xFF00) == 0x8100) {
                v &= 0xFF;

                switch (v) {
                case 0x40:
                    w = 0;
                    t = 0;
                    break;
                case 0x41:
                    w = 0xF5;
                    t = 0;
                    break;
                case 0x42:
                    w = 0xF6;
                    t = 0;
                    break;
                case 0x45:
                    w = 0xF9;
                    t = 0;
                    break;
                case 0x46:
                    w = 0xFA;
                    t = 0;
                    break;
                case 0x48:
                    w = 0xF1;
                    t = 0;
                    break;
                case 0x49:
                    w = 0xF0;
                    t = 0;
                    break;
                case 0x58:
                    w = 20;
                    t = 2;
                    break;
                case 0x5B:
                    w = 0xFD;
                    t = 0;
                    break;
                case 0x5C:
                    w = 0xFC;
                    t = 0;
                    break;
                case 0x60:
                    w = 0xFE;
                    t = 0;
                    break;
                case 0x63:
                    w = 0xFB;
                    t = 0;
                    break;
                case 0x75:
                    w = 0xE8;
                    t = 0;
                    break;
                case 0x76:
                    w = 0xE9;
                    t = 0;
                    break;
                case 0x77:
                    w = 0xEA;
                    t = 0;
                    break;
                case 0x78:
                    w = 0xEB;
                    t = 0;
                    break;
                case 0x66:
                    w = 0xFF;
                    t = 0;
                    break;
                case 0x69:
                    w = 0xEC;
                    t = 0;
                    break;
                case 0x6A:
                    w = 0xED;
                    t = 0;
                    break;
                case 0xA8:
                    w = 0xE7;
                    t = 0;
                    break;
                case 0xA9:
                    w = 0xE6;
                    t = 0;
                    break;
                case 0x7B:
                    w = 0xDF;
                    t = 0;
                    break;
                case 0x7C:
                    w = 0xFC;
                    t = 0;
                    break;
                case 0xA6:
                    w = 0xEE;
                    t = 0;
                    break;
                case 0x81:
                    w = 0xEF;
                    t = 0;
                    break;
                case 0x93:
                    w = 0xF2;
                    t = 0;
                    break;
                case 0x96:
                    w = 0xF4;
                    t = 0;
                    break;
                case 0x5E:
                    w = 0xF3;
                    t = 0;
                    break;
                case 0x43:
                    w = 0xF8;
                    t = 0;
                    break;
                case 0x9A:
                    w = 0x8E;
                    t = 0;
                    break;
                }
            } else {
                GetSjisGlyph(v, &w, &t);
            }

            if (b->tiles != NULL) {
                ReleaseObjTiles(b->tiles);
                b->tiles = NULL;
            }

            switch (t) {
            case 0:
                w = ((u16*)gMsgFontBank0Frames[w])[3];
                b->tiles = LoadObjTiles(&gMsgFontBank0Tiles[w * 32], 128);
                break;
            case 1:
                w = ((u16*)gMsgFontBank1Frames[w])[3];
                b->tiles = LoadObjTiles(&gMsgFontBank1Tiles[w * 32], 128);
                break;
            case 2:
                w = ((u16*)gMsgFontBank2Frames[w])[3];
                b->tiles = LoadObjTiles(&gMsgFontBank2Tiles[w * 32], 128);
                break;
            case 3:
                w = ((u16*)gMsgFontBank3Frames[w])[3];
                b->tiles = LoadObjTiles(&gMsgFontBank3Tiles[w * 32], 128);
                break;
            }

            b->advance = 10;
        }

        b++;
        n++;
    }

    return n;
}
#endif

#ifndef VERSION_EU
s32 LoadTextTileArray(TextChar* a, void** p) {
    u8 buf[2];
    u16* c;
    u16 w;
    u8 t;
    u8 n;

    w = 0;
    t = 0;
    n = 0;

    while (*a != 0) {
        u16 v;

        buf[0] = a[0];
        buf[1] = a[1];
        c = (u16*)buf;

        if (*c == 0x6E6E) {
            a += 2;

            if (*p != NULL) {
                ReleaseObjTiles(*p);
            }

            *p++ = NULL;
        } else {
            v = *c;
            v = (v / 256) | (v << 8);
            a += 2;

            if ((v & 0xFF00) == 0x8100) {
                v &= 0xFF;

                switch (v) {
                case 0x40:
                    w = 0;
                    t = 0;
                    break;
                case 0x41:
                    w = 0xF5;
                    t = 0;
                    break;
                case 0x42:
                    w = 0xF6;
                    t = 0;
                    break;
                case 0x45:
                    w = 0xF9;
                    t = 0;
                    break;
                case 0x46:
                    w = 0xFA;
                    t = 0;
                    break;
                case 0x48:
                    w = 0xF1;
                    t = 0;
                    break;
                case 0x49:
                    w = 0xF0;
                    t = 0;
                    break;
                case 0x58:
                    w = 20;
                    t = 2;
                    break;
                case 0x5B:
                    w = 0xFD;
                    t = 0;
                    break;
                case 0x5C:
                    w = 0xFC;
                    t = 0;
                    break;
                case 0x60:
                    w = 0xFE;
                    t = 0;
                    break;
                case 0x63:
                    w = 0xFB;
                    t = 0;
                    break;
                case 0x75:
                    w = 0xE8;
                    t = 0;
                    break;
                case 0x76:
                    w = 0xE9;
                    t = 0;
                    break;
                case 0x77:
                    w = 0xEA;
                    t = 0;
                    break;
                case 0x78:
                    w = 0xEB;
                    t = 0;
                    break;
                case 0x66:
                    w = 0xFF;
                    t = 0;
                    break;
                case 0x69:
                    w = 0xEC;
                    t = 0;
                    break;
                case 0x6A:
                    w = 0xED;
                    t = 0;
                    break;
                case 0xA8:
                    w = 0xE7;
                    t = 0;
                    break;
                case 0xA9:
                    w = 0xE6;
                    t = 0;
                    break;
                case 0x7B:
                    w = 0xDF;
                    t = 0;
                    break;
                case 0x7C:
                    w = 0xFC;
                    t = 0;
                    break;
                case 0xA6:
                    w = 0xEE;
                    t = 0;
                    break;
                case 0x81:
                    w = 0xEF;
                    t = 0;
                    break;
                case 0x93:
                    w = 0xF2;
                    t = 0;
                    break;
                case 0x96:
                    w = 0xF4;
                    t = 0;
                    break;
                case 0x5E:
                    w = 0xF3;
                    t = 0;
                    break;
                case 0x43:
                    w = 0xF8;
                    t = 0;
                    break;
                case 0x9A:
                    w = 0x8E;
                    t = 0;
                    break;
                }
            } else {
                GetSjisGlyph(v, &w, &t);
            }

            if (*p != NULL) {
                ReleaseObjTiles(*p);
                *p = NULL;
            }

            switch (t) {
            case 0:
                w = ((u16*)gMsgFontBank0Frames[w])[3];
                *p = LoadObjTiles(&gMsgFontBank0Tiles[w * 32], 128);
                break;
            case 1:
                w = ((u16*)gMsgFontBank1Frames[w])[3];
                *p = LoadObjTiles(&gMsgFontBank1Tiles[w * 32], 128);
                break;
            case 2:
                w = ((u16*)gMsgFontBank2Frames[w])[3];
                *p = LoadObjTiles(&gMsgFontBank2Tiles[w * 32], 128);
                break;
            case 3:
                w = ((u16*)gMsgFontBank3Frames[w])[3];
                *p = LoadObjTiles(&gMsgFontBank3Tiles[w * 32], 128);
                break;
            }

            p++;
        }

        n++;
    }

    return n;
}
#endif

void* LoadTextPalette(s32 a) {
    void* r = NULL;

    switch (a) {
    case 0:
        r = LoadObjPalette(gTextBrownPalette, 32);
        break;
    case 1:
        r = LoadObjPalette(gTextWhitePalette, 32);
        break;
    case 2:
        r = LoadObjPalette(gTextGrayPalette, 32);
        break;
    case 3:
        r = LoadObjPalette(gTextYellowPalette, 32);
        break;
    case 4:
        r = LoadObjPalette(gTextGreenPalette, 32);
        break;
    case 5:
        r = LoadObjPalette(gTextCyanPalette, 32);
        break;
    }

    return r;
}

void DrawTextSlots(s16 x, s16 y, TextSlot* p, void* d, u16 h, u8 n) {
    s16 x0 = x;
    s16 cy = y;
    u8 i;

#ifndef VERSION_JP
    cy -= 2;
#endif

    for (i = 0; i < n; i++) {
        if (p->tiles == NULL) {
            cy += 12;
            x = x0;
        } else if (p->advance != -1) {
            DrawSprite(x, cy, MSG_FONT_FRAMES[0], p->tiles, d, NULL, 0, h);
            x += p->advance;
        } else {
            x += 3;
        }

        p++;
    }
}

void DrawTextSlotsUnsorted(s16 x, s16 y, TextSlot* p, void* d, s32 e, u8 n) {
    s16 x0 = x;
    s16 cy = y;
    u8 i;

#ifndef VERSION_JP
    cy -= 2;
#endif

    for (i = 0; i < n; i++) {
        if (p->tiles == NULL) {
            cy += 12;
            x = x0;
        } else if (p->advance != -1) {
            DrawSpriteUnsorted(x, cy, MSG_FONT_FRAMES[0], p->tiles, d, 0);
            x += p->advance;
        } else {
            x += 3;
        }

        p++;
    }
}

void DrawTextSlotsWithFlags(s16 x, s32 y, TextSlot* p, void* d, u16 g, u16 h, u8 n) {
    s16 x0 = x;
    s16 cy = y;
    u8 i;

#ifndef VERSION_JP
    cy -= 2;
#endif

    for (i = 0; i < n; i++) {
        if (p->tiles == NULL) {
            cy += 12;
            x = x0;
        } else if (p->advance != -1) {
            DrawSprite(x, cy, MSG_FONT_FRAMES[0], p->tiles, d, NULL, g, h);
            x += p->advance;
        } else {
            x += 3;
        }

        p++;
    }
}

void DrawTextSlotsWithTwoPalettes(s16 x, s32 y, TextSlot* p, void* d, void* e, u16 h, u8 n) {
    s16 x0 = x;
    s16 cy = y;
    u8 i;

#ifndef VERSION_JP
    cy -= 2;
#endif

    for (i = 0; i < n; i++) {
        if (p->tiles == NULL) {
            cy += 12;
            x = x0;
        } else if (p->advance != -1) {
            if (p->useAlternatePalette == 0) {
                DrawSprite(x, cy, MSG_FONT_FRAMES[0], p->tiles, d, NULL, 0, h);
            } else {
                DrawSprite(x, cy, MSG_FONT_FRAMES[0], p->tiles, e, NULL, 0, h);
            }

            x += p->advance;
        } else {
            x += 3;
        }

        p++;
    }
}

void DrawTextTileArray(s16 x, s32 y, void** p, void* d, u16 h, u8 n) {
    s16 cy = y;
    s16 x0 = x;
    u8 i;

    for (i = 0; i < n; i++) {
        if (*p == NULL) {
            cy += 12;
            x = x0;
        } else {
            DrawSprite(x, cy, MSG_FONT_FRAMES[0], *p, d, NULL, 0, h);
            x += 10;
        }

        p++;
    }
}

void DrawTextTileArrayWithTwoPalettes(s16 x, s32 y, void** p, void* d, s32 e, u16 h, u8 n) {
    s16 cy = y;
    s16 x0 = x;
    u8 i;

    for (i = 0; i < n; i++) {
        if (*p == NULL) {
            cy += 12;
            x = x0;
        } else {
            DrawSprite(x, cy, MSG_FONT_FRAMES[0], *p, d, NULL, 0, h);
            x += 10;
        }

        p++;
    }
}

void* LoadSmallFontTiles() {
    return LoadObjTiles(gSmallFontTiles, 0x5A0);
}

void* LoadSmallFontPalette() {
    return LoadObjPalette(gCommonObjPalette, 0x20);
}

void FreeSmallFontResources(void* a, void* b) {
    ReleaseObjTiles(a);
    ReleaseObjPalette(b);
}

u16 EncodeSmallFontString(const u8* s, u16* out) {
    u16 g = 0;
    u8 n;
    u8 i;

    if (out == NULL) {
        return 0;
    }

    n = GetStringLength(s);

    for (i = 0; i < n; i++) {
        if ((u8)(s[i] - '0') <= 9) {
            g = s[i] - '0';
        }

        if ((u8)(s[i] - 'A') <= 25) {
            g = s[i] - 0x37;
        }

        if ((u8)(s[i] - 'a') <= 25) {
            g = s[i] - 0x57;
        }

        if (s[i] == '/') {
            g = 0x24;
        }

        if (s[i] == '-') {
            g = 0x25;
        }

        if (s[i] == '_') {
            g = 0x26;
        }

        if (s[i] == '.') {
            g = 0x27;
        }

        if (s[i] == '+') {
            g = 0x28;
        }

        if (s[i] == '!') {
            g = 0x29;
        }

        if (s[i] == '?') {
            g = 0x2A;
        }

        if (s[i] == '#') {
            g = 0x2B;
        }

        if (s[i] == '%') {
            g = 0x2C;
        }

        *out++ = g;
    }

    return n;
}

u16 FormatSmallFontDecimal(s32 v, u16* out) {
    s32 t[11];
    u8 s[12];
    s32 acc;
    s32 d;
    s32 i;

    acc = 0;

    if (v >= 0) {
        d = 1000000000;

        for (i = 0; i <= 9; i++) {
            t[i] = v / d - acc;
            acc = (acc + t[i]) * 10;
            d /= 10;
        }

        for (i = 0; i <= 9; i++) {
            s[i] = t[i] + '0';
        }

        s[10] = 0;

        for (i = 0; i <= 9; i++) {
            if (s[i] > '0') {
                break;
            }
        }

        return EncodeSmallFontString(&s[i], out);
    }

    d = -1000000000;

    for (i = 1; i <= 10; i++) {
        t[i] = v / d - acc;
        acc = (acc + t[i]) * 10;
        d /= 10;
    }

    s[0] = '-';

    for (i = 1; i <= 10; i++) {
        s[i] = t[i] + '0';
    }

    s[11] = 0;

    for (i = 1; i <= 10; i++) {
        if (s[i] > '0') {
            break;
        }
    }

    s[i - 1] = '-';
    return EncodeSmallFontString(&s[i - 1], out);
}

u16 FormatSmallFontHex(s32 v, u16* out) {
    u8 buf[11];
    u8* p;
    s32 i;

    buf[0] = '0';
    buf[1] = 'x';
    buf[2] = (v & 0xF0000000) >> 28;
    buf[3] = (v & 0x0F000000) >> 24;
    buf[4] = (v & 0x00F00000) >> 20;
    buf[5] = (v & 0x000F0000) >> 16;
    buf[6] = (v & 0x0000F000) >> 12;
    buf[7] = (v & 0x00000F00) >> 8;
    buf[8] = (v & 0x000000F0) >> 4;
    buf[9] = v & 0xF;
    buf[10] = 0;
    p = &buf[2];

    for (i = 0; i < 8; i++) {
        if (*p <= 9) {
            *p += 0x30;
        } else {
            *p += 0x37;
        }

        p++;
    }

    return EncodeSmallFontString(buf, out);
}

u16 FormatSmallFontBinary(u32 v, u16* out, u8 mode) {
    u8 a[2];
    u8 b[9];
    u8 c[17];
    u8 d[33];

    switch (mode) {
    case 0:
        a[0] = v;
        a[0] += '0';
        a[1] = 0;
        return EncodeSmallFontString(a, out);
    case 1:
        b[0] = (v >> 7) + '0';
        b[1] = ((v >> 6) & 1) + '0';
        b[2] = ((v >> 5) & 1) + '0';
        b[3] = ((v >> 4) & 1) + '0';
        b[4] = ((v >> 3) & 1) + '0';
        b[5] = ((v >> 2) & 1) + '0';
        b[6] = ((v >> 1) & 1) + '0';
        b[7] = (v & 1) + '0';
        b[8] = 0;
        return EncodeSmallFontString(b, out);
    case 2:
        c[0] = (v >> 15) + '0';
        c[1] = ((v >> 14) & 1) + '0';
        c[2] = ((v >> 13) & 1) + '0';
        c[3] = ((v >> 12) & 1) + '0';
        c[4] = ((v >> 11) & 1) + '0';
        c[5] = ((v >> 10) & 1) + '0';
        c[6] = ((v >> 9) & 1) + '0';
        c[7] = ((v >> 8) & 1) + '0';
        c[8] = ((v >> 7) & 1) + '0';
        c[9] = ((v >> 6) & 1) + '0';
        c[10] = ((v >> 5) & 1) + '0';
        c[11] = ((v >> 4) & 1) + '0';
        c[12] = ((v >> 3) & 1) + '0';
        c[13] = ((v >> 2) & 1) + '0';
        c[14] = ((v >> 1) & 1) + '0';
        c[15] = (v & 1) + '0';
        c[16] = 0;
        return EncodeSmallFontString(c, out);
    case 3:
        d[0] = (v >> 31) + '0';
        d[1] = ((v >> 30) & 1) + '0';
        d[2] = ((v >> 29) & 1) + '0';
        d[3] = ((v >> 28) & 1) + '0';
        d[4] = ((v >> 27) & 1) + '0';
        d[5] = ((v >> 26) & 1) + '0';
        d[6] = ((v >> 25) & 1) + '0';
        d[7] = ((v >> 24) & 1) + '0';
        d[8] = ((v >> 23) & 1) + '0';
        d[9] = ((v >> 22) & 1) + '0';
        d[10] = ((v >> 21) & 1) + '0';
        d[11] = ((v >> 20) & 1) + '0';
        d[12] = ((v >> 19) & 1) + '0';
        d[13] = ((v >> 18) & 1) + '0';
        d[14] = ((v >> 17) & 1) + '0';
        d[15] = ((v >> 16) & 1) + '0';
        d[16] = ((v >> 15) & 1) + '0';
        d[17] = ((v >> 14) & 1) + '0';
        d[18] = ((v >> 13) & 1) + '0';
        d[19] = ((v >> 12) & 1) + '0';
        d[20] = ((v >> 11) & 1) + '0';
        d[21] = ((v >> 10) & 1) + '0';
        d[22] = ((v >> 9) & 1) + '0';
        d[23] = ((v >> 8) & 1) + '0';
        d[24] = ((v >> 7) & 1) + '0';
        d[25] = ((v >> 6) & 1) + '0';
        d[26] = ((v >> 5) & 1) + '0';
        d[27] = ((v >> 4) & 1) + '0';
        d[28] = ((v >> 3) & 1) + '0';
        d[29] = ((v >> 2) & 1) + '0';
        d[30] = ((v >> 1) & 1) + '0';
        d[31] = (v & 1) + '0';
        return EncodeSmallFontString(d, out);
    }
}

s32 DrawSmallFontString(s16 x, s16 y, u16* s, void* d, void* e, u16 h, u8 n) {
    u8 i;

    for (i = 0; i < n; i++) {
        DrawSprite(x + i * 8, y, gSmallFontFrames[*s], d, e, NULL, 0, h);
        s++;
    }
}

void GetSjisGlyph(u16 a, u16* b, u8* c) {
    switch (a & 0xFF00) {
    case 0x8200: {
        u16 v = a & 0xFF;

        if ((u16)(v - 96) <= 25) {
            *b = a + 0x7DAB;
        }

        if ((u16)(v - 129) <= 25) {
            *b = a + 0x7DA4;
        }

        if ((u16)(v - 79) <= 9) {
            *b = a + 0x7DB2;
        }

        if ((u16)(v - 159) <= 82) {
            *b = a + 0x7DA0;
        }

        *c = 0;
        break;
    }
    case 0x8300: {
        u16 v = a & 0xFF;

        if ((u16)(v - 64) <= 62) {
            *b = a + 0x7D52;
        }

        if ((u16)(v - 128) <= 20) {
            *b = a + 0x7D51;
        }

        *c = 0;
        break;
    }
    case 0x8700:
        switch (a & 0xFF) {
        case 0x56:
            *b = 143;
            *c = 0;
            break;
        case 0x5D:
            *b = 142;
            *c = 0;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x8800:
        switch (a & 0xFF) {
        case 0xC5:
            *b = 9;
            *c = 1;
            break;
        case 0xC3:
            *b = 84;
            *c = 1;
            break;
        case 0xF3:
            *b = 86;
            *c = 1;
            break;
        case 0xEA:
            *b = 104;
            *c = 1;
            break;
        case 0xF9:
            *b = 153;
            *c = 1;
            break;
        case 0xE1:
            *b = 179;
            *c = 1;
            break;
        case 0xC8:
            *b = 182;
            *c = 1;
            break;
        case 0xAB:
            *b = 208;
            *c = 1;
            break;
        case 0xF6:
            *b = 247;
            *c = 1;
            break;
        case 0xB5:
            *b = 250;
            *c = 1;
            break;
        case 0xD3:
            *b = 3;
            *c = 2;
            break;
        case 0xC0:
            *b = 17;
            *c = 2;
            break;
        case 0xCD:
            *b = 57;
            *c = 2;
            break;
        case 0xE7:
            *b = 105;
            *c = 2;
            break;
        case 0xF8:
            *b = 164;
            *c = 2;
            break;
        case 0xF5:
            *b = 184;
            *c = 2;
            break;
        case 0xA4:
            *b = 192;
            *c = 2;
            break;
        case 0xA3:
            *b = 207;
            *c = 2;
            break;
        case 0xC4:
            *b = 63;
            *c = 3;
            break;
        case 0xAC:
            *b = 78;
            *c = 3;
            break;
        case 0xDF:
            *b = 102;
            *c = 3;
            break;
        case 0xDA:
            *b = 118;
            *c = 3;
            break;
        case 0xD9:
            *b = 135;
            *c = 3;
            break;
        case 0xCA:
            *b = 136;
            *c = 3;
            break;
        case 0xD0:
            *b = 187;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x8900:
        switch (a & 0xFF) {
        case 0x9C:
            *b = 4;
            *c = 1;
            break;
        case 0xAF:
            *b = 26;
            *c = 1;
            break;
        case 0xBD:
            *b = 47;
            *c = 1;
            break;
        case 0xA4:
            *b = 49;
            *c = 1;
            break;
        case 0x69:
            *b = 74;
            *c = 1;
            break;
        case 0x93:
            *b = 75;
            *c = 1;
            break;
        case 0xF6:
            *b = 95;
            *c = 1;
            break;
        case 0xEF:
            *b = 98;
            *c = 1;
            break;
        case 0x52:
            *b = 103;
            *c = 1;
            break;
        case 0xB4:
            *b = 107;
            *c = 1;
            break;
        case 0xC6:
            *b = 121;
            *c = 1;
            break;
        case 0x5E:
            *b = 124;
            *c = 1;
            break;
        case 0x42:
            *b = 160;
            *c = 1;
            break;
        case 0xBB:
            *b = 198;
            *c = 1;
            break;
        case 0xEE:
            *b = 205;
            *c = 1;
            break;
        case 0xBA:
            *b = 1;
            *c = 2;
            break;
        case 0x98:
            *b = 8;
            *c = 2;
            break;
        case 0xBC:
            *b = 15;
            *c = 2;
            break;
        case 0xF0:
            *b = 61;
            *c = 2;
            break;
        case 0xF1:
            *b = 65;
            *c = 2;
            break;
        case 0xCA:
            *b = 89;
            *c = 2;
            break;
        case 0x6A:
            *b = 101;
            *c = 2;
            break;
        case 0xE4:
            *b = 104;
            *c = 2;
            break;
        case 0xB9:
            *b = 120;
            *c = 2;
            break;
        case 0xAE:
            *b = 124;
            *c = 2;
            break;
        case 0xC1:
            *b = 152;
            *c = 2;
            break;
        case 0x70:
            *b = 155;
            *c = 2;
            break;
        case 0xF7:
            *b = 177;
            *c = 2;
            break;
        case 0xDF:
            *b = 200;
            *c = 2;
            break;
        case 0xE6:
            *b = 201;
            *c = 2;
            break;
        case 0xBF:
            *b = 218;
            *c = 2;
            break;
        case 0x65:
            *b = 240;
            *c = 2;
            break;
        case 0x7A:
            *b = 244;
            *c = 2;
            break;
        case 0xC8:
            *b = 13;
            *c = 3;
            break;
        case 0x41:
            *b = 51;
            *c = 3;
            break;
        case 0x8F:
            *b = 55;
            *c = 3;
            break;
        case 0x9E:
            *b = 80;
            *c = 3;
            break;
        case 0x45:
            *b = 113;
            *c = 3;
            break;
        case 0xCE:
            *b = 129;
            *c = 3;
            break;
        case 0x9F:
            *b = 142;
            *c = 3;
            break;
        case 0xD7:
            *b = 148;
            *c = 3;
            break;
        case 0xC2:
            *b = 150;
            *c = 3;
            break;
        case 0x8A:
            *b = 154;
            *c = 3;
            break;
        case 0xD4:
            *b = 181;
            *c = 3;
            break;
        case 0xFC:
            *b = 188;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x8A00:
        switch (a & 0xFF) {
        case 0x4F:
            *b = 8;
            *c = 1;
            break;
        case 0x6D:
            *b = 17;
            *c = 1;
            break;
        case 0xB5:
            *b = 61;
            *c = 1;
            break;
        case 0x4B:
            *b = 76;
            *c = 1;
            break;
        case 0xA3:
            *b = 81;
            *c = 1;
            break;
        case 0x45:
            *b = 83;
            *c = 1;
            break;
        case 0xD4:
            *b = 101;
            *c = 1;
            break;
        case 0x43:
            *b = 123;
            *c = 1;
            break;
        case 0xEB:
            *b = 139;
            *c = 1;
            break;
        case 0xB4:
            *b = 167;
            *c = 1;
            break;
        case 0x79:
            *b = 188;
            *c = 1;
            break;
        case 0x58:
            *b = 199;
            *c = 1;
            break;
        case 0xAA:
            *b = 252;
            *c = 1;
            break;
        case 0xB1:
            *b = 9;
            *c = 2;
            break;
        case 0xEF:
            *b = 13;
            *c = 2;
            break;
        case 0xE7:
            *b = 54;
            *c = 2;
            break;
        case 0xE8:
            *b = 59;
            *c = 2;
            break;
        case 0xC3:
            *b = 64;
            *c = 2;
            break;
        case 0xC8:
            *b = 84;
            *c = 2;
            break;
        case 0xF1:
            *b = 140;
            *c = 2;
            break;
        case 0x6F:
            *b = 143;
            *c = 2;
            break;
        case 0x4A:
            *b = 146;
            *c = 2;
            break;
        case 0x51:
            *b = 149;
            *c = 2;
            break;
        case 0xD6:
            *b = 178;
            *c = 2;
            break;
        case 0x69:
            *b = 248;
            *c = 2;
            break;
        case 0x47:
            *b = 3;
            *c = 3;
            break;
        case 0x77:
            *b = 14;
            *c = 3;
            break;
        case 0xEC:
            *b = 46;
            *c = 3;
            break;
        case 0xAE:
            *b = 56;
            *c = 3;
            break;
        case 0xED:
            *b = 76;
            *c = 3;
            break;
        case 0xB7:
            *b = 85;
            *c = 3;
            break;
        case 0x88:
            *b = 88;
            *c = 3;
            break;
        case 0xA5:
            *b = 145;
            *c = 3;
            break;
        case 0xFA:
            *b = 162;
            *c = 3;
            break;
        case 0xAB:
            *b = 166;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x8B00:
        switch (a & 0xFF) {
        case 0x4C:
            *b = 25;
            *c = 1;
            break;
        case 0x41:
            *b = 30;
            *c = 1;
            break;
        case 0x43:
            *b = 38;
            *c = 1;
            break;
        case 0x5E:
            *b = 62;
            *c = 1;
            break;
        case 0xB3:
            *b = 70;
            *c = 1;
            break;
        case 0xFC:
            *b = 72;
            *c = 1;
            break;
        case 0xAD:
            *b = 73;
            *c = 1;
            break;
        case 0x63:
            *b = 89;
            *c = 1;
            break;
        case 0x9F:
            *b = 129;
            *c = 1;
            break;
        case 0xDF:
            *b = 134;
            *c = 1;
            break;
        case 0xA6:
            *b = 158;
            *c = 1;
            break;
        case 0xEA:
            *b = 173;
            *c = 1;
            break;
        case 0xE6:
            *b = 180;
            *c = 1;
            break;
        case 0xBB:
            *b = 189;
            *c = 1;
            break;
        case 0xC1:
            *b = 200;
            *c = 1;
            break;
        case 0xB0:
            *b = 207;
            *c = 1;
            break;
        case 0x4E:
            *b = 214;
            *c = 1;
            break;
        case 0x86:
            *b = 221;
            *c = 1;
            break;
        case 0x74:
            *b = 239;
            *c = 1;
            break;
        case 0x7E:
            *b = 253;
            *c = 1;
            break;
        case 0xB9:
            *b = 7;
            *c = 2;
            break;
        case 0x46:
            *b = 19;
            *c = 2;
            break;
        case 0x5A:
            *b = 24;
            *c = 2;
            break;
        case 0x7D:
            *b = 27;
            *c = 2;
            break;
        case 0x92:
            *b = 40;
            *c = 2;
            break;
        case 0x96:
            *b = 43;
            *c = 2;
            break;
        case 0x7B:
            *b = 66;
            *c = 2;
            break;
        case 0xB6:
            *b = 88;
            *c = 2;
            break;
        case 0xF3:
            *b = 99;
            *c = 2;
            break;
        case 0x5D:
            *b = 108;
            *c = 2;
            break;
        case 0xC8:
            *b = 126;
            *c = 2;
            break;
        case 0xA3:
            *b = 153;
            *c = 2;
            break;
        case 0x81:
            *b = 195;
            *c = 2;
            break;
        case 0xEC:
            *b = 198;
            *c = 2;
            break;
        case 0x91:
            *b = 203;
            *c = 2;
            break;
        case 0x50:
            *b = 204;
            *c = 2;
            break;
        case 0xF0:
            *b = 208;
            *c = 2;
            break;
        case 0x8E:
            *b = 213;
            *c = 2;
            break;
        case 0x70:
            *b = 214;
            *c = 2;
            break;
        case 0xBF:
            *b = 220;
            *c = 2;
            break;
        case 0xB5:
            *b = 235;
            *c = 2;
            break;
        case 0x76:
            *b = 237;
            *c = 2;
            break;
        case 0xF4:
            *b = 239;
            *c = 2;
            break;
        case 0x40:
            *b = 254;
            *c = 2;
            break;
        case 0x60:
            *b = 255;
            *c = 2;
            break;
        case 0x83:
            *b = 5;
            *c = 3;
            break;
        case 0x95:
            *b = 43;
            *c = 3;
            break;
        case 0xEF:
            *b = 45;
            *c = 3;
            break;
        case 0x4D:
            *b = 66;
            *c = 3;
            break;
        case 0xBD:
            *b = 71;
            *c = 3;
            break;
        case 0x90:
            *b = 99;
            *c = 3;
            break;
        case 0x7A:
            *b = 123;
            *c = 3;
            break;
        case 0x9B:
            *b = 131;
            *c = 3;
            break;
        case 0xA5:
            *b = 158;
            *c = 3;
            break;
        case 0x78:
            *b = 167;
            *c = 3;
            break;
        case 0xE0:
            *b = 169;
            *c = 3;
            break;
        case 0xC9:
            *b = 179;
            *c = 3;
            break;
        case 0xCA:
            *b = 184;
            *c = 3;
            break;
        case 0xCF:
            *b = 186;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x8C00:
        switch (a & 0xFF) {
        case 0x4E:
            *b = 6;
            *c = 1;
            break;
        case 0xF5:
            *b = 11;
            *c = 1;
            break;
        case 0xA9:
            *b = 12;
            *c = 1;
            break;
        case 0x78:
            *b = 22;
            *c = 1;
            break;
        case 0xAB:
            *b = 55;
            *c = 1;
            break;
        case 0xBE:
            *b = 67;
            *c = 1;
            break;
        case 0xAE:
            *b = 80;
            *c = 1;
            break;
        case 0xB3:
            *b = 91;
            *c = 1;
            break;
        case 0x76:
            *b = 116;
            *c = 1;
            break;
        case 0x60:
            *b = 128;
            *c = 1;
            break;
        case 0x9F:
            *b = 138;
            *c = 1;
            break;
        case 0xFB:
            *b = 152;
            *c = 1;
            break;
        case 0xC8:
            *b = 203;
            *c = 1;
            break;
        case 0xC4:
            *b = 215;
            *c = 1;
            break;
        case 0xBB:
            *b = 216;
            *c = 1;
            break;
        case 0xA4:
            *b = 220;
            *c = 1;
            break;
        case 0xC0:
            *b = 233;
            *c = 1;
            break;
        case 0xB4:
            *b = 246;
            *c = 1;
            break;
        case 0xB1:
            *b = 12;
            *c = 2;
            break;
        case 0x69:
            *b = 33;
            *c = 2;
            break;
        case 0x88:
            *b = 46;
            *c = 2;
            break;
        case 0x59:
            *b = 49;
            *c = 2;
            break;
        case 0xE4:
            *b = 60;
            *c = 2;
            break;
        case 0x41:
            *b = 73;
            *c = 2;
            break;
        case 0xE3:
            *b = 76;
            *c = 2;
            break;
        case 0x8B:
            *b = 90;
            *c = 2;
            break;
        case 0xFC:
            *b = 96;
            *c = 2;
            break;
        case 0xDD:
            *b = 97;
            *c = 2;
            break;
        case 0x57:
            *b = 106;
            *c = 2;
            break;
        case 0xAF:
            *b = 111;
            *c = 2;
            break;
        case 0x99:
            *b = 117;
            *c = 2;
            break;
        case 0xB5:
            *b = 129;
            *c = 2;
            break;
        case 0xB8:
            *b = 175;
            *c = 2;
            break;
        case 0xE5:
            *b = 183;
            *c = 2;
            break;
        case 0x8F:
            *b = 211;
            *c = 2;
            break;
        case 0xB6:
            *b = 226;
            *c = 2;
            break;
        case 0x8A:
            *b = 238;
            *c = 2;
            break;
        case 0xC3:
            *b = 251;
            *c = 2;
            break;
        case 0x79:
            *b = 9;
            *c = 3;
            break;
        case 0xEB:
            *b = 19;
            *c = 3;
            break;
        case 0x8C:
            *b = 31;
            *c = 3;
            break;
        case 0x95:
            *b = 37;
            *c = 3;
            break;
        case 0xF0:
            *b = 57;
            *c = 3;
            break;
        case 0xCC:
            *b = 70;
            *c = 3;
            break;
        case 0xF8:
            *b = 98;
            *c = 3;
            break;
        case 0xEA:
            *b = 100;
            *c = 3;
            break;
        case 0x82:
            *b = 122;
            *c = 3;
            break;
        case 0xB9:
            *b = 171;
            *c = 3;
            break;
        case 0x6E:
            *b = 172;
            *c = 3;
            break;
        case 0x87:
            *b = 189;
            *c = 3;
            break;
        case 0x5E:
            *b = 191;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x8D00:
        switch (a & 0xFF) {
        case 0x90:
            *b = 23;
            *c = 1;
            break;
        case 0x73:
            *b = 31;
            *c = 1;
            break;
        case 0xDF:
            *b = 46;
            *c = 1;
            break;
        case 0x9E:
            *b = 127;
            *c = 1;
            break;
        case 0xC5:
            *b = 133;
            *c = 1;
            break;
        case 0xA2:
            *b = 143;
            *c = 1;
            break;
        case 0x6C:
            *b = 157;
            *c = 1;
            break;
        case 0xA1:
            *b = 164;
            *c = 1;
            break;
        case 0xC4:
            *b = 187;
            *c = 1;
            break;
        case 0xCB:
            *b = 228;
            *c = 1;
            break;
        case 0xEC:
            *b = 230;
            *c = 1;
            break;
        case 0x87:
            *b = 23;
            *c = 2;
            break;
        case 0x8F:
            *b = 26;
            *c = 2;
            break;
        case 0xD9:
            *b = 29;
            *c = 2;
            break;
        case 0x91:
            *b = 38;
            *c = 2;
            break;
        case 0x44:
            *b = 81;
            *c = 2;
            break;
        case 0xA5:
            *b = 91;
            *c = 2;
            break;
        case 0x72:
            *b = 134;
            *c = 2;
            break;
        case 0x52:
            *b = 139;
            *c = 2;
            break;
        case 0xB6:
            *b = 141;
            *c = 2;
            break;
        case 0xC3:
            *b = 147;
            *c = 2;
            break;
        case 0xCF:
            *b = 179;
            *c = 2;
            break;
        case 0x58:
            *b = 202;
            *c = 2;
            break;
        case 0x82:
            *b = 215;
            *c = 2;
            break;
        case 0xDD:
            *b = 224;
            *c = 2;
            break;
        case 0xD7:
            *b = 230;
            *c = 2;
            break;
        case 0x48:
            *b = 231;
            *c = 2;
            break;
        case 0x4C:
            *b = 243;
            *c = 2;
            break;
        case 0xFB:
            *b = 250;
            *c = 2;
            break;
        case 0x5C:
            *b = 15;
            *c = 3;
            break;
        case 0x93:
            *b = 39;
            *c = 3;
            break;
        case 0xBD:
            *b = 40;
            *c = 3;
            break;
        case 0xAC:
            *b = 92;
            *c = 3;
            break;
        case 0xDB:
            *b = 108;
            *c = 3;
            break;
        case 0x55:
            *b = 121;
            *c = 3;
            break;
        case 0xBB:
            *b = 128;
            *c = 3;
            break;
        case 0xAA:
            *b = 185;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x8E00:
        switch (a & 0xFF) {
        case 0xB8:
            *b = 13;
            *c = 1;
            break;
        case 0xA9:
            *b = 15;
            *c = 1;
            break;
        case 0xD7:
            *b = 18;
            *c = 1;
            break;
        case 0xD2:
            *b = 21;
            *c = 1;
            break;
        case 0x9E:
            *b = 27;
            *c = 1;
            break;
        case 0x76:
            *b = 28;
            *c = 1;
            break;
        case 0x84:
            *b = 44;
            *c = 1;
            break;
        case 0xA1:
            *b = 54;
            *c = 1;
            break;
        case 0xA6:
            *b = 87;
            *c = 1;
            break;
        case 0x71:
            *b = 102;
            *c = 1;
            break;
        case 0xC0:
            *b = 111;
            *c = 1;
            break;
        case 0x9F:
            *b = 155;
            *c = 1;
            break;
        case 0x9D:
            *b = 156;
            *c = 1;
            break;
        case 0x96:
            *b = 161;
            *c = 1;
            break;
        case 0x8E:
            *b = 191;
            *c = 1;
            break;
        case 0xE8:
            *b = 197;
            *c = 1;
            break;
        case 0x6D:
            *b = 219;
            *c = 1;
            break;
        case 0x70:
            *b = 232;
            *c = 1;
            break;
        case 0xE6:
            *b = 241;
            *c = 1;
            break;
        case 0xE3:
            *b = 249;
            *c = 1;
            break;
        case 0x63:
            *b = 10;
            *c = 2;
            break;
        case 0x64:
            *b = 22;
            *c = 2;
            break;
        case 0xB6:
            *b = 28;
            *c = 2;
            break;
        case 0xF1:
            *b = 31;
            *c = 2;
            break;
        case 0x80:
            *b = 48;
            *c = 2;
            break;
        case 0xE5:
            *b = 75;
            *c = 2;
            break;
        case 0x4F:
            *b = 78;
            *c = 2;
            break;
        case 0xD3:
            *b = 80;
            *c = 2;
            break;
        case 0x67:
            *b = 86;
            *c = 2;
            break;
        case 0x5A:
            *b = 87;
            *c = 2;
            break;
        case 0xE7:
            *b = 102;
            *c = 2;
            break;
        case 0xD8:
            *b = 112;
            *c = 2;
            break;
        case 0x97:
            *b = 122;
            *c = 2;
            break;
        case 0x8B:
            *b = 136;
            *c = 2;
            break;
        case 0x51:
            *b = 151;
            *c = 2;
            break;
        case 0x6E:
            *b = 166;
            *c = 2;
            break;
        case 0x7E:
            *b = 169;
            *c = 2;
            break;
        case 0xF3:
            *b = 194;
            *c = 2;
            break;
        case 0xF4:
            *b = 199;
            *c = 2;
            break;
        case 0x78:
            *b = 227;
            *c = 2;
            break;
        case 0x55:
            *b = 242;
            *c = 2;
            break;
        case 0xED:
            *b = 246;
            *c = 2;
            break;
        case 0x40:
            *b = 16;
            *c = 3;
            break;
        case 0x77:
            *b = 25;
            *c = 3;
            break;
        case 0xCC:
            *b = 42;
            *c = 3;
            break;
        case 0x91:
            *b = 50;
            *c = 3;
            break;
        case 0xA8:
            *b = 81;
            *c = 3;
            break;
        case 0xFB:
            *b = 124;
            *c = 3;
            break;
        case 0xD4:
            *b = 125;
            *c = 3;
            break;
        case 0x9A:
            *b = 140;
            *c = 3;
            break;
        case 0xEA:
            *b = 146;
            *c = 3;
            break;
        case 0x61:
            *b = 159;
            *c = 3;
            break;
        case 0xCB:
            *b = 164;
            *c = 3;
            break;
        case 0xBF:
            *b = 196;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x8F00:
        switch (a & 0xFF) {
        case 0x6F:
            *b = 29;
            *c = 1;
            break;
        case 0xEA:
            *b = 32;
            *c = 1;
            break;
        case 0x8A:
            *b = 33;
            *c = 1;
            break;
        case 0x97:
            *b = 48;
            *c = 1;
            break;
        case 0x95:
            *b = 68;
            *c = 1;
            break;
        case 0xE3:
            *b = 183;
            *c = 1;
            break;
        case 0xE4:
            *b = 185;
            *c = 1;
            break;
        case 0x80:
            *b = 194;
            *c = 1;
            break;
        case 0xD0:
            *b = 204;
            *c = 1;
            break;
        case 0x50:
            *b = 217;
            *c = 1;
            break;
        case 0xE7:
            *b = 224;
            *c = 1;
            break;
        case 0x94:
            *b = 226;
            *c = 1;
            break;
        case 0x64:
            *b = 236;
            *c = 1;
            break;
        case 0xAD:
            *b = 21;
            *c = 2;
            break;
        case 0x57:
            *b = 35;
            *c = 2;
            break;
        case 0xD8:
            *b = 39;
            *c = 2;
            break;
        case 0x9F:
            *b = 45;
            *c = 2;
            break;
        case 0x89:
            *b = 63;
            *c = 2;
            break;
        case 0x8F:
            *b = 70;
            *c = 2;
            break;
        case 0x5D:
            *b = 83;
            *c = 2;
            break;
        case 0xC1:
            *b = 142;
            *c = 2;
            break;
        case 0xC4:
            *b = 144;
            *c = 2;
            break;
        case 0x91:
            *b = 145;
            *c = 2;
            break;
        case 0xE1:
            *b = 148;
            *c = 2;
            break;
        case 0xF3:
            *b = 186;
            *c = 2;
            break;
        case 0xE9:
            *b = 189;
            *c = 2;
            break;
        case 0x49:
            *b = 190;
            *c = 2;
            break;
        case 0xEE:
            *b = 191;
            *c = 2;
            break;
        case 0xE6:
            *b = 196;
            *c = 2;
            break;
        case 0x5B:
            *b = 206;
            *c = 2;
            break;
        case 0x75:
            *b = 209;
            *c = 2;
            break;
        case 0x68:
            *b = 225;
            *c = 2;
            break;
        case 0xAC:
            *b = 229;
            *c = 2;
            break;
        case 0x9D:
            *b = 233;
            *c = 2;
            break;
        case 0x5A:
            *b = 0;
            *c = 3;
            break;
        case 0xCE:
            *b = 2;
            *c = 3;
            break;
        case 0x83:
            *b = 22;
            *c = 3;
            break;
        case 0xF0:
            *b = 28;
            *c = 3;
            break;
        case 0x70:
            *b = 84;
            *c = 3;
            break;
        case 0xC6:
            *b = 130;
            *c = 3;
            break;
        case 0x5C:
            *b = 139;
            *c = 3;
            break;
        case 0xA2:
            *b = 165;
            *c = 3;
            break;
        case 0xED:
            *b = 175;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x9000:
        switch (a & 0xFF) {
        case 0xD8:
            *b = 1;
            *c = 1;
            break;
        case 0x53:
            *b = 3;
            *c = 1;
            break;
        case 0x6C:
            *b = 43;
            *c = 1;
            break;
        case 0xB0:
            *b = 65;
            *c = 1;
            break;
        case 0xED:
            *b = 66;
            *c = 1;
            break;
        case 0x5B:
            *b = 69;
            *c = 1;
            break;
        case 0xA2:
            *b = 82;
            *c = 1;
            break;
        case 0x51:
            *b = 94;
            *c = 1;
            break;
        case 0xBA:
            *b = 97;
            *c = 1;
            break;
        case 0xE0:
            *b = 112;
            *c = 1;
            break;
        case 0x45:
            *b = 117;
            *c = 1;
            break;
        case 0xB6:
            *b = 130;
            *c = 1;
            break;
        case 0xB3:
            *b = 149;
            *c = 1;
            break;
        case 0x4D:
            *b = 151;
            *c = 1;
            break;
        case 0x48:
            *b = 169;
            *c = 1;
            break;
        case 0xA8:
            *b = 175;
            *c = 1;
            break;
        case 0xAC:
            *b = 184;
            *c = 1;
            break;
        case 0x5E:
            *b = 231;
            *c = 1;
            break;
        case 0x65:
            *b = 251;
            *c = 1;
            break;
        case 0xE2:
            *b = 255;
            *c = 1;
            break;
        case 0x56:
            *b = 4;
            *c = 2;
            break;
        case 0x46:
            *b = 34;
            *c = 2;
            break;
        case 0xD3:
            *b = 41;
            *c = 2;
            break;
        case 0x67:
            *b = 44;
            *c = 2;
            break;
        case 0xE6:
            *b = 68;
            *c = 2;
            break;
        case 0x69:
            *b = 69;
            *c = 2;
            break;
        case 0x62:
            *b = 71;
            *c = 2;
            break;
        case 0x85:
            *b = 100;
            *c = 2;
            break;
        case 0xB5:
            *b = 109;
            *c = 2;
            break;
        case 0x94:
            *b = 173;
            *c = 2;
            break;
        case 0x58:
            *b = 210;
            *c = 2;
            break;
        case 0x84:
            *b = 20;
            *c = 3;
            break;
        case 0xCC:
            *b = 21;
            *c = 3;
            break;
        case 0x7D:
            *b = 23;
            *c = 3;
            break;
        case 0xAF:
            *b = 35;
            *c = 3;
            break;
        case 0xD4:
            *b = 49;
            *c = 3;
            break;
        case 0xF5:
            *b = 73;
            *c = 3;
            break;
        case 0x41:
            *b = 83;
            *c = 3;
            break;
        case 0xC2:
            *b = 95;
            *c = 3;
            break;
        case 0xB8:
            *b = 97;
            *c = 3;
            break;
        case 0x5F:
            *b = 104;
            *c = 3;
            break;
        case 0xC3:
            *b = 105;
            *c = 3;
            break;
        case 0xAB:
            *b = 106;
            *c = 3;
            break;
        case 0x44:
            *b = 109;
            *c = 3;
            break;
        case 0xDA:
            *b = 127;
            *c = 3;
            break;
        case 0x55:
            *b = 132;
            *c = 3;
            break;
        case 0xA7:
            *b = 163;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x9100:
        switch (a & 0xFF) {
        case 0xE5:
            *b = 0;
            *c = 1;
            break;
        case 0x7A:
            *b = 2;
            *c = 1;
            break;
        case 0xDE:
            *b = 53;
            *c = 1;
            break;
        case 0xD2:
            *b = 59;
            *c = 1;
            break;
        case 0x52:
            *b = 64;
            *c = 1;
            break;
        case 0xAB:
            *b = 90;
            *c = 1;
            break;
        case 0xCC:
            *b = 135;
            *c = 1;
            break;
        case 0x81:
            *b = 137;
            *c = 1;
            break;
        case 0x7B:
            *b = 145;
            *c = 1;
            break;
        case 0xA9:
            *b = 163;
            *c = 1;
            break;
        case 0x9C:
            *b = 181;
            *c = 1;
            break;
        case 0x8A:
            *b = 196;
            *c = 1;
            break;
        case 0x66:
            *b = 201;
            *c = 1;
            break;
        case 0xE8:
            *b = 212;
            *c = 1;
            break;
        case 0x95:
            *b = 235;
            *c = 1;
            break;
        case 0x4E:
            *b = 5;
            *c = 2;
            break;
        case 0x4F:
            *b = 50;
            *c = 2;
            break;
        case 0x9B:
            *b = 51;
            *c = 2;
            break;
        case 0xA7:
            *b = 98;
            *c = 2;
            break;
        case 0x84:
            *b = 103;
            *c = 2;
            break;
        case 0xBD:
            *b = 107;
            *c = 2;
            break;
        case 0xDD:
            *b = 113;
            *c = 2;
            break;
        case 0xAE:
            *b = 115;
            *c = 2;
            break;
        case 0x44:
            *b = 121;
            *c = 2;
            break;
        case 0xAF:
            *b = 127;
            *c = 2;
            break;
        case 0xCA:
            *b = 137;
            *c = 2;
            break;
        case 0xBC:
            *b = 150;
            *c = 2;
            break;
        case 0x88:
            *b = 154;
            *c = 2;
            break;
        case 0x49:
            *b = 158;
            *c = 2;
            break;
        case 0xC5:
            *b = 165;
            *c = 2;
            break;
        case 0x67:
            *b = 170;
            *c = 2;
            break;
        case 0x53:
            *b = 171;
            *c = 2;
            break;
        case 0x5F:
            *b = 176;
            *c = 2;
            break;
        case 0xD4:
            *b = 187;
            *c = 2;
            break;
        case 0xCE:
            *b = 212;
            *c = 2;
            break;
        case 0xB6:
            *b = 223;
            *c = 2;
            break;
        case 0xB1:
            *b = 6;
            *c = 3;
            break;
        case 0xA4:
            *b = 32;
            *c = 3;
            break;
        case 0xE4:
            *b = 48;
            *c = 3;
            break;
        case 0xE3:
            *b = 72;
            *c = 3;
            break;
        case 0xB0:
            *b = 74;
            *c = 3;
            break;
        case 0x97:
            *b = 86;
            *c = 3;
            break;
        case 0x50:
            *b = 103;
            *c = 3;
            break;
        case 0xBE:
            *b = 119;
            *c = 3;
            break;
        case 0xF0:
            *b = 137;
            *c = 3;
            break;
        case 0x77:
            *b = 149;
            *c = 3;
            break;
        case 0x96:
            *b = 161;
            *c = 3;
            break;
        case 0xAC:
            *b = 173;
            *c = 3;
            break;
        case 0xE6:
            *b = 192;
            *c = 3;
            break;
        case 0x9D:
            *b = 195;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x9200:
        switch (a & 0xFF) {
        case 0x86:
            *b = 10;
            *c = 1;
            break;
        case 0x6D:
            *b = 14;
            *c = 1;
            break;
        case 0x42:
            *b = 35;
            *c = 1;
            break;
        case 0x40:
            *b = 39;
            *c = 1;
            break;
        case 0x4E:
            *b = 40;
            *c = 1;
            break;
        case 0x69:
            *b = 77;
            *c = 1;
            break;
        case 0x6E:
            *b = 79;
            *c = 1;
            break;
        case 0x8B:
            *b = 93;
            *c = 1;
            break;
        case 0xB7:
            *b = 120;
            *c = 1;
            break;
        case 0x54:
            *b = 122;
            *c = 1;
            break;
        case 0xBC:
            *b = 132;
            *c = 1;
            break;
        case 0x45:
            *b = 177;
            *c = 1;
            break;
        case 0x75:
            *b = 178;
            *c = 1;
            break;
        case 0xEA:
            *b = 206;
            *c = 1;
            break;
        case 0xCA:
            *b = 222;
            *c = 1;
            break;
        case 0x6B:
            *b = 225;
            *c = 1;
            break;
        case 0xB2:
            *b = 245;
            *c = 1;
            break;
        case 0xC9:
            *b = 254;
            *c = 1;
            break;
        case 0xC7:
            *b = 6;
            *c = 2;
            break;
        case 0x78:
            *b = 25;
            *c = 2;
            break;
        case 0x50:
            *b = 85;
            *c = 2;
            break;
        case 0x44:
            *b = 92;
            *c = 2;
            break;
        case 0x8D:
            *b = 133;
            *c = 2;
            break;
        case 0x87:
            *b = 135;
            *c = 2;
            break;
        case 0xEF:
            *b = 138;
            *c = 2;
            break;
        case 0x6C:
            *b = 219;
            *c = 2;
            break;
        case 0x85:
            *b = 221;
            *c = 2;
            break;
        case 0x6A:
            *b = 222;
            *c = 2;
            break;
        case 0xF6:
            *b = 12;
            *c = 3;
            break;
        case 0xBE:
            *b = 58;
            *c = 3;
            break;
        case 0x66:
            *b = 69;
            *c = 3;
            break;
        case 0x63:
            *b = 77;
            *c = 3;
            break;
        case 0xA7:
            *b = 94;
            *c = 3;
            break;
        case 0x5A:
            *b = 101;
            *c = 3;
            break;
        case 0x8E:
            *b = 107;
            *c = 3;
            break;
        case 0xE8:
            *b = 138;
            *c = 3;
            break;
        case 0x65:
            *b = 153;
            *c = 3;
            break;
        case 0xB4:
            *b = 157;
            *c = 3;
            break;
        case 0xE1:
            *b = 178;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x9300:
        switch (a & 0xFF) {
        case 0x90:
            *b = 45;
            *c = 1;
            break;
        case 0x9A:
            *b = 57;
            *c = 1;
            break;
        case 0x96:
            *b = 63;
            *c = 1;
            break;
        case 0xAE:
            *b = 100;
            *c = 1;
            break;
        case 0x78:
            *b = 105;
            *c = 1;
            break;
        case 0xFC:
            *b = 106;
            *c = 1;
            break;
        case 0xC1:
            *b = 108;
            *c = 1;
            break;
        case 0xE0:
            *b = 136;
            *c = 1;
            break;
        case 0x7B:
            *b = 148;
            *c = 1;
            break;
        case 0x60:
            *b = 150;
            *c = 1;
            break;
        case 0xA6:
            *b = 168;
            *c = 1;
            break;
        case 0x66:
            *b = 172;
            *c = 1;
            break;
        case 0x47:
            *b = 202;
            *c = 1;
            break;
        case 0x56:
            *b = 227;
            *c = 1;
            break;
        case 0x6E:
            *b = 47;
            *c = 2;
            break;
        case 0xAF:
            *b = 55;
            *c = 2;
            break;
        case 0xAA:
            *b = 58;
            *c = 2;
            break;
        case 0x61:
            *b = 67;
            *c = 2;
            break;
        case 0xB4:
            *b = 72;
            *c = 2;
            break;
        case 0xEF:
            *b = 82;
            *c = 2;
            break;
        case 0xFA:
            *b = 131;
            *c = 2;
            break;
        case 0xCB:
            *b = 159;
            *c = 2;
            break;
        case 0xF1:
            *b = 168;
            *c = 2;
            break;
        case 0x73:
            *b = 180;
            *c = 2;
            break;
        case 0x7C:
            *b = 182;
            *c = 2;
            break;
        case 0xC5:
            *b = 232;
            *c = 2;
            break;
        case 0xCD:
            *b = 245;
            *c = 2;
            break;
        case 0x49:
            *b = 252;
            *c = 2;
            break;
        case 0x87:
            *b = 1;
            *c = 3;
            break;
        case 0xB1:
            *b = 26;
            *c = 3;
            break;
        case 0xB9:
            *b = 44;
            *c = 3;
            break;
        case 0x5D:
            *b = 47;
            *c = 3;
            break;
        case 0x54:
            *b = 61;
            *c = 3;
            break;
        case 0x72:
            *b = 65;
            *c = 3;
            break;
        case 0xE4:
            *b = 89;
            *c = 3;
            break;
        case 0x79:
            *b = 90;
            *c = 3;
            break;
        case 0xBE:
            *b = 93;
            *c = 3;
            break;
        case 0xAC:
            *b = 126;
            *c = 3;
            break;
        case 0xC7:
            *b = 134;
            *c = 3;
            break;
        case 0x58:
            *b = 147;
            *c = 3;
            break;
        case 0x8A:
            *b = 152;
            *c = 3;
            break;
        case 0x64:
            *b = 170;
            *c = 3;
            break;
        case 0x5F:
            *b = 190;
            *c = 3;
            break;
        case 0xF7:
            *b = 197;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x9400:
        switch (a & 0xFF) {
        case 0xDE:
            *b = 41;
            *c = 1;
            break;
        case 0xC6:
            *b = 42;
            *c = 1;
            break;
        case 0x7A:
            *b = 144;
            *c = 1;
            break;
        case 0xF5:
            *b = 195;
            *c = 1;
            break;
        case 0x8E:
            *b = 218;
            *c = 1;
            break;
        case 0x6A:
            *b = 223;
            *c = 1;
            break;
        case 0xAD:
            *b = 229;
            *c = 1;
            break;
        case 0xFC:
            *b = 240;
            *c = 1;
            break;
        case 0x73:
            *b = 244;
            *c = 1;
            break;
        case 0xDF:
            *b = 18;
            *c = 2;
            break;
        case 0xBB:
            *b = 30;
            *c = 2;
            break;
        case 0xF2:
            *b = 32;
            *c = 2;
            break;
        case 0x92:
            *b = 36;
            *c = 2;
            break;
        case 0xED:
            *b = 37;
            *c = 2;
            break;
        case 0x43:
            *b = 42;
            *c = 2;
            break;
        case 0x4F:
            *b = 52;
            *c = 2;
            break;
        case 0x4C:
            *b = 53;
            *c = 2;
            break;
        case 0x59:
            *b = 62;
            *c = 2;
            break;
        case 0xB2:
            *b = 74;
            *c = 2;
            break;
        case 0x97:
            *b = 114;
            *c = 2;
            break;
        case 0x67:
            *b = 119;
            *c = 2;
            break;
        case 0x46:
            *b = 160;
            *c = 2;
            break;
        case 0xE9:
            *b = 205;
            *c = 2;
            break;
        case 0x83:
            *b = 216;
            *c = 2;
            break;
        case 0xE0:
            *b = 228;
            *c = 2;
            break;
        case 0x5C:
            *b = 236;
            *c = 2;
            break;
        case 0xD4:
            *b = 7;
            *c = 3;
            break;
        case 0xBC:
            *b = 8;
            *c = 3;
            break;
        case 0x96:
            *b = 10;
            *c = 3;
            break;
        case 0xB1:
            *b = 11;
            *c = 3;
            break;
        case 0xBD:
            *b = 24;
            *c = 3;
            break;
        case 0x9B:
            *b = 41;
            *c = 3;
            break;
        case 0x77:
            *b = 67;
            *c = 3;
            break;
        case 0x9A:
            *b = 68;
            *c = 3;
            break;
        case 0x4D:
            *b = 82;
            *c = 3;
            break;
        case 0x4E:
            *b = 96;
            *c = 3;
            break;
        case 0xF1:
            *b = 110;
            *c = 3;
            break;
        case 0x7B:
            *b = 151;
            *c = 3;
            break;
        case 0xA0:
            *b = 176;
            *c = 3;
            break;
        case 0xE7:
            *b = 183;
            *c = 3;
            break;
        case 0x65:
            *b = 193;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x9500:
        switch (a & 0xFF) {
        case 0xAA:
            *b = 16;
            *c = 1;
            break;
        case 0x7C:
            *b = 37;
            *c = 1;
            break;
        case 0x95:
            *b = 85;
            *c = 1;
            break;
        case 0x73:
            *b = 88;
            *c = 1;
            break;
        case 0xCF:
            *b = 92;
            *c = 1;
            break;
        case 0xA8:
            *b = 96;
            *c = 1;
            break;
        case 0xCA:
            *b = 109;
            *c = 1;
            break;
        case 0xFB:
            *b = 110;
            *c = 1;
            break;
        case 0x83:
            *b = 114;
            *c = 1;
            break;
        case 0xB7:
            *b = 115;
            *c = 1;
            break;
        case 0xA0:
            *b = 118;
            *c = 1;
            break;
        case 0xC2:
            *b = 126;
            *c = 1;
            break;
        case 0xE0:
            *b = 146;
            *c = 1;
            break;
        case 0xF3:
            *b = 147;
            *c = 1;
            break;
        case 0x40:
            *b = 165;
            *c = 1;
            break;
        case 0xBD:
            *b = 171;
            *c = 1;
            break;
        case 0x76:
            *b = 186;
            *c = 1;
            break;
        case 0xF8:
            *b = 213;
            *c = 1;
            break;
        case 0xD4:
            *b = 248;
            *c = 1;
            break;
        case 0x69:
            *b = 2;
            *c = 2;
            break;
        case 0x4B:
            *b = 16;
            *c = 2;
            break;
        case 0xB5:
            *b = 56;
            *c = 2;
            break;
        case 0xFA:
            *b = 110;
            *c = 2;
            break;
        case 0x9A:
            *b = 116;
            *c = 2;
            break;
        case 0x94:
            *b = 123;
            *c = 2;
            break;
        case 0x89:
            *b = 157;
            *c = 2;
            break;
        case 0xA1:
            *b = 172;
            *c = 2;
            break;
        case 0xD6:
            *b = 234;
            *c = 2;
            break;
        case 0x60:
            *b = 4;
            *c = 3;
            break;
        case 0xF1:
            *b = 27;
            *c = 3;
            break;
        case 0x82:
            *b = 38;
            *c = 3;
            break;
        case 0xD0:
            *b = 59;
            *c = 3;
            break;
        case 0x97:
            *b = 62;
            *c = 3;
            break;
        case 0x90:
            *b = 75;
            *c = 3;
            break;
        case 0x9C:
            *b = 87;
            *c = 3;
            break;
        case 0xBA:
            *b = 111;
            *c = 3;
            break;
        case 0x5C:
            *b = 116;
            *c = 3;
            break;
        case 0x58:
            *b = 155;
            *c = 3;
            break;
        case 0xB6:
            *b = 160;
            *c = 3;
            break;
        case 0xD2:
            *b = 194;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x9600:
        switch (a & 0xFF) {
        case 0x59:
            *b = 5;
            *c = 1;
            break;
        case 0x82:
            *b = 19;
            *c = 1;
            break;
        case 0xB0:
            *b = 24;
            *c = 1;
            break;
        case 0x6C:
            *b = 36;
            *c = 1;
            break;
        case 0xBD:
            *b = 51;
            *c = 1;
            break;
        case 0x7B:
            *b = 71;
            *c = 1;
            break;
        case 0xBE:
            *b = 113;
            *c = 1;
            break;
        case 0x40:
            *b = 125;
            *c = 1;
            break;
        case 0x9E:
            *b = 131;
            *c = 1;
            break;
        case 0xD9:
            *b = 142;
            *c = 1;
            break;
        case 0xF1:
            *b = 162;
            *c = 1;
            break;
        case 0x5C:
            *b = 170;
            *c = 1;
            break;
        case 0xB3:
            *b = 176;
            *c = 1;
            break;
        case 0xA1:
            *b = 190;
            *c = 1;
            break;
        case 0xBC:
            *b = 193;
            *c = 1;
            break;
        case 0xB2:
            *b = 209;
            *c = 1;
            break;
        case 0xE2:
            *b = 211;
            *c = 1;
            break;
        case 0xDF:
            *b = 242;
            *c = 1;
            break;
        case 0xF2:
            *b = 243;
            *c = 1;
            break;
        case 0x5D:
            *b = 0;
            *c = 2;
            break;
        case 0xAD:
            *b = 14;
            *c = 2;
            break;
        case 0xDA:
            *b = 79;
            *c = 2;
            break;
        case 0xCA:
            *b = 94;
            *c = 2;
            break;
        case 0xC0:
            *b = 125;
            *c = 2;
            break;
        case 0x88:
            *b = 130;
            *c = 2;
            break;
        case 0xEC:
            *b = 161;
            *c = 2;
            break;
        case 0xBB:
            *b = 163;
            *c = 2;
            break;
        case 0x96:
            *b = 167;
            *c = 2;
            break;
        case 0x57:
            *b = 174;
            *c = 2;
            break;
        case 0x9C:
            *b = 185;
            *c = 2;
            break;
        case 0xC2:
            *b = 197;
            *c = 2;
            break;
        case 0xF0:
            *b = 217;
            *c = 2;
            break;
        case 0xA7:
            *b = 253;
            *c = 2;
            break;
        case 0xF3:
            *b = 18;
            *c = 3;
            break;
        case 0xA2:
            *b = 29;
            *c = 3;
            break;
        case 0x4B:
            *b = 33;
            *c = 3;
            break;
        case 0xE9:
            *b = 36;
            *c = 3;
            break;
        case 0x64:
            *b = 52;
            *c = 3;
            break;
        case 0xC5:
            *b = 53;
            *c = 3;
            break;
        case 0xBA:
            *b = 54;
            *c = 3;
            break;
        case 0x60:
            *b = 91;
            *c = 3;
            break;
        case 0xD8:
            *b = 117;
            *c = 3;
            break;
        case 0xFB:
            *b = 120;
            *c = 3;
            break;
        case 0x87:
            *b = 143;
            *c = 3;
            break;
        case 0x68:
            *b = 199;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x9700:
        switch (a & 0xFF) {
        case 0xE1:
            *b = 7;
            *c = 1;
            break;
        case 0x45:
            *b = 20;
            *c = 1;
            break;
        case 0x46:
            *b = 34;
            *c = 1;
            break;
        case 0x6C:
            *b = 50;
            *c = 1;
            break;
        case 0xDF:
            *b = 52;
            *c = 1;
            break;
        case 0x88:
            *b = 56;
            *c = 1;
            break;
        case 0x70:
            *b = 60;
            *c = 1;
            break;
        case 0x79:
            *b = 78;
            *c = 1;
            break;
        case 0xC7:
            *b = 99;
            *c = 1;
            break;
        case 0x9D:
            *b = 140;
            *c = 1;
            break;
        case 0x52:
            *b = 141;
            *c = 1;
            break;
        case 0x44:
            *b = 154;
            *c = 1;
            break;
        case 0xCD:
            *b = 159;
            *c = 1;
            break;
        case 0x5C:
            *b = 166;
            *c = 1;
            break;
        case 0xA3:
            *b = 174;
            *c = 1;
            break;
        case 0x98:
            *b = 192;
            *c = 1;
            break;
        case 0x76:
            *b = 237;
            *c = 1;
            break;
        case 0x8A:
            *b = 11;
            *c = 2;
            break;
        case 0x74:
            *b = 77;
            *c = 2;
            break;
        case 0x8E:
            *b = 93;
            *c = 2;
            break;
        case 0xA7:
            *b = 95;
            *c = 2;
            break;
        case 0x68:
            *b = 118;
            *c = 2;
            break;
        case 0xE7:
            *b = 128;
            *c = 2;
            break;
        case 0x56:
            *b = 132;
            *c = 2;
            break;
        case 0x59:
            *b = 156;
            *c = 2;
            break;
        case 0x90:
            *b = 181;
            *c = 2;
            break;
        case 0xE2:
            *b = 193;
            *c = 2;
            break;
        case 0x4C:
            *b = 241;
            *c = 2;
            break;
        case 0xDE:
            *b = 247;
            *c = 2;
            break;
        case 0xB7:
            *b = 249;
            *c = 2;
            break;
        case 0x63:
            *b = 17;
            *c = 3;
            break;
        case 0xA0:
            *b = 30;
            *c = 3;
            break;
        case 0xAC:
            *b = 34;
            *c = 3;
            break;
        case 0x83:
            *b = 60;
            *c = 3;
            break;
        case 0x5E:
            *b = 64;
            *c = 3;
            break;
        case 0xBC:
            *b = 79;
            *c = 3;
            break;
        case 0x7A:
            *b = 112;
            *c = 3;
            break;
        case 0x64:
            *b = 115;
            *c = 3;
            break;
        case 0xB9:
            *b = 144;
            *c = 3;
            break;
        case 0x8B:
            *b = 156;
            *c = 3;
            break;
        case 0xAA:
            *b = 174;
            *c = 3;
            break;
        case 0xCA:
            *b = 180;
            *c = 3;
            break;
        case 0xA6:
            *b = 182;
            *c = 3;
            break;
        case 0x6E:
            *b = 198;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x9800:
        switch (a & 0xFF) {
        case 0x41:
            *b = 58;
            *c = 1;
            break;
        case 0x62:
            *b = 119;
            *c = 1;
            break;
        case 0x5E:
            *b = 234;
            *c = 1;
            break;
        case 0x63:
            *b = 238;
            *c = 1;
            break;
        case 0x59:
            *b = 162;
            *c = 2;
            break;
        case 0x66:
            *b = 188;
            *c = 2;
            break;
        case 0x72:
            *b = 133;
            *c = 3;
            break;
        case 0x48:
            *b = 141;
            *c = 3;
            break;
        case 0x42:
            *b = 168;
            *c = 3;
            break;
        case 0x61:
            *b = 177;
            *c = 3;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    case 0x9C00:
        switch (a & 0xFF) {
        case 0xC9:
            *b = 210;
            *c = 1;
            break;
        default:
            *b = 0;
            *c = 0;
            break;
        }

        break;
    default:
        *b = 0;
        *c = 0;
        break;
    }
}

void SplitFourDigits(s16 v, u8* out) {
    s16 acc = 0;
    s16 div;
    s16 i;

    if (v >= 0) {
        div = 1000;

        for (i = 0; i < 4; i++) {
            u8* q = &out[i];
            *q = v / div - acc;
            acc = (acc + *q) * 10;
            div /= 10;
        }
    }
}

u16 InitCardMsgGlyphSprites(s32 mode, s32 flag) {
    s32 i;

    sCardMsgGlyphSprites = EwramAlloc(sizeof(TextGlyphSprite) * 128);

    for (i = 0; i < 128; i++) {
        sCardMsgGlyphSprites[i].x = 0;
        sCardMsgGlyphSprites[i].y = 0;
        sCardMsgGlyphSprites[i].tiles = NULL;
        sCardMsgGlyphSprites[i].palette = NULL;
        sCardMsgGlyphSprites[i].alternatePalette = NULL;
        sCardMsgGlyphSprites[i].visible = 0;

        switch (mode) {
        case 0:
            sCardMsgGlyphSprites[i].palette = LoadObjPalette(gTextBrownPalette, 0x20);
            break;
        case 1:
            sCardMsgGlyphSprites[i].palette = LoadObjPalette(gTextWhitePalette, 0x20);
            break;
        case 2:
            sCardMsgGlyphSprites[i].palette = LoadObjPalette(gTextGrayPalette, 0x20);
            break;
        }

        if (!flag) {
            sCardMsgGlyphSprites[i].alternatePalette = LoadTextPalette(3);
        } else {
            sCardMsgGlyphSprites[i].alternatePalette = LoadTextPalette(5);
        }

        FadeSetPaletteExcluded(sCardMsgGlyphSprites[i].palette->index + 0x10, 1);
        FadeSetPaletteExcluded(sCardMsgGlyphSprites[i].alternatePalette->index + 0x10, 1);
    }

    sTextEntryCount = 0;
    return sCardMsgGlyphSprites[0].palette->index;
}

u8 LayoutCardMsgGlyphsPage(s32 x, s32 y, MsgLatinChar* s, MsgLatinChar** d) {
    s32 cx;
    s32 cy;
    s32 f;

    cx = 0;
    cy = 0;
    f = 0;

    if (sCardMsgGlyphSprites == NULL) {
        return 0;
    }

    sTextEntryCount = 0;

    while (*s != 0) {
        s32 v;

        sCardMsgGlyphSprites[sTextEntryCount].x = x + cx;
        sCardMsgGlyphSprites[sTextEntryCount].y = y + cy;
        sCardMsgGlyphSprites[sTextEntryCount].visible = 1;

        if (*s == MSG_LATIN_CODE(0x4079, 29)) {
            f = 1;
            s++;
        }

        if (*s == MSG_LATIN_CODE(0x4000, 30)) {
            f = 0;
            s++;
        }

        if (*s == MSG_LATIN_CODE(10, 31)) {
            cx = 0;
            cy += 0xC00;
        } else {
#ifdef VERSION_EU
            v = *s;
#else
            if ((u16)(*s - 32) <= 223) {
                v = *s;
            } else {
                switch (*s) {
                case 0xE000:
                    v = 25;
                    break;
                case 0x2191:
                    v = 10;
                    break;
                case 0x2193:
                    v = 11;
                    break;
                case 0x2190:
                    v = 12;
                    break;
                case 0x2192:
                    v = 13;
                    break;
                case 0x300C:
                    v = 1;
                    break;
                case 0x300D:
                    v = 2;
                    break;
                case 0x300E:
                    v = 3;
                    break;
                case 0x300F:
                    v = 4;
                    break;
                case 0x203B:
                    v = 6;
                    break;
                case 0x266A:
                    v = 18;
                    break;
                case 0x2642:
                    v = 8;
                    break;
                case 0x2640:
                    v = 9;
                    break;
                case 0x2605:
                    v = 21;
                    break;
                case 0x25A0:
                    v = 17;
                    break;
                default:
                    v = 0;
                    break;
                }
            }
#endif

            sCardMsgGlyphSprites[sTextEntryCount].useAlternatePalette = f;

            if (sCardMsgGlyphSprites[sTextEntryCount].tiles != NULL) {
                ReleaseObjTiles(sCardMsgGlyphSprites[sTextEntryCount].tiles);
                sCardMsgGlyphSprites[sTextEntryCount].tiles = NULL;
            }

            cx += (s16)sLatinGlyphWidths.widths[v] << 8;

            if (v != 32) {
                v = ((u16*)gMsgLatinFontFrames[v])[3];
                sCardMsgGlyphSprites[sTextEntryCount].tiles = LoadObjTiles(&gMsgLatinFontTiles[v * 32], 128);
            }

            sTextEntryCount++;

            if (cx > 0x9B00) {
                cx = 0;
                cy += 0xC00;
            }
        }

        s++;

        if (cy > 0x1800) {
            *d = s;
            return sTextEntryCount;
        }
    }

    *d = NULL;
    return sTextEntryCount;
}

#ifndef VERSION_EU
u8 LayoutCardMsgGlyphsPageSjis(s32 x, s32 y, u8* s, u8** d) {
    u16 w;
    u8 t;
    s32 cx;
    s32 cy;
    s32 px;
    w = 0;
    t = 0;
    cx = 0;
    cy = 0;
    px = 0;

    if (sCardMsgGlyphSprites == NULL) {
        return 0;
    }

    sTextEntryCount = 0;

    while (*s != 0) {
        u16 v;
        w = 0;
        sCardMsgGlyphSprites[sTextEntryCount].x = x + cx;
        sCardMsgGlyphSprites[sTextEntryCount].y = y + cy;
        sCardMsgGlyphSprites[sTextEntryCount].visible = 1;
        sCardMsgGlyphSprites[sTextEntryCount].useAlternatePalette = 0;

        if (*(u16*)s == 0x6E6E) {
            cx = 0;
            cy += 0xC00;
            s += 2;
        } else {
            v = *(u16*)s;
            v = (v / 256) | (v << 8);
            s += 2;

            if ((v & 0xFF00) == 0x8100) {
                switch (v & 0xFF) {
                case 0x40:
                    w = 0;
                    t = 0;
                    break;
                case 0x41:
                    w = 0xF5;
                    t = 0;
                    break;
                case 0x42:
                    w = 0xF6;
                    t = 0;
                    break;
                case 0x44:
                    w = 0xF7;
                    t = 0;
                    break;
                case 0x45:
                    w = 0xF9;
                    t = 0;
                    break;
                case 0x48:
                    w = 0xF1;
                    t = 0;
                    break;
                case 0x49:
                    w = 0xF0;
                    t = 0;
                    break;
                case 0x58:
                    w = 20;
                    t = 2;
                    break;
                case 0x5B:
                    w = 0xFD;
                    t = 0;
                    break;
                case 0x5C:
                    w = 0xFC;
                    t = 0;
                    break;
                case 0x60:
                    w = 0xFE;
                    t = 0;
                    break;
                case 0x63:
                    w = 0xFB;
                    t = 0;
                    break;
                case 0x75:
                    w = 0xE8;
                    t = 0;
                    break;
                case 0x76:
                    w = 0xE9;
                    t = 0;
                    break;
                case 0x77:
                    w = 0xEA;
                    t = 0;
                    break;
                case 0x78:
                    w = 0xEB;
                    t = 0;
                    break;
                case 0x66:
                    w = 0xFF;
                    t = 0;
                    break;
                case 0x69:
                    w = 0xEC;
                    t = 0;
                    break;
                case 0x6A:
                    w = 0xED;
                    t = 0;
                    break;
                case 0xA8:
                    w = 0xE7;
                    t = 0;
                    break;
                case 0xA9:
                    w = 0xE6;
                    t = 0;
                    break;
                case 0x7B:
                    w = 0xDF;
                    t = 0;
                    break;
                case 0x7C:
                    w = 0xFC;
                    t = 0;
                    break;
                case 0xA6:
                    w = 0xEE;
                    t = 0;
                    break;
                case 0x81:
                    w = 0xEF;
                    t = 0;
                    break;
                case 0x93:
                    w = 0xF2;
                    t = 0;
                    break;
                case 0x96:
                    w = 0xF4;
                    t = 0;
                    break;
                case 0x5E:
                    w = 0xF3;
                    t = 0;
                    break;
                case 0x43:
                    w = 0xF8;
                    t = 0;
                    break;
                case 0x9A:
                    w = 0x8E;
                    t = 0;
                    break;
                }

                if (sTextEntryCount != 0 &&
                    (v == 0x8141 || v == 0x8142 || v > 0x8177 || v == 0x8144 ||
                     (v == 0x8148 || v == 0x8149)) &&
                    cx == 0 && cy > 0) {
                    cx = px + 0xA00;
                    cy -= 0xC00;
                    sCardMsgGlyphSprites[sTextEntryCount].x = x + cx;
                    sCardMsgGlyphSprites[sTextEntryCount].y = y + cy;
                }
            } else {
                GetSjisGlyph(v, &w, &t);
            }

            if (sCardMsgGlyphSprites[sTextEntryCount].tiles != NULL) {
                ReleaseObjTiles(sCardMsgGlyphSprites[sTextEntryCount].tiles);
            }

            px = cx;
            cx += 0xA00;

            if (cx > 0x8C00) {
                cx = 0;
                cy += 0xC00;
            }

            switch (t) {
            case 0:
                w = ((u16*)gMsgFontBank0Frames[w])[3];
                sCardMsgGlyphSprites[sTextEntryCount].tiles = LoadObjTiles(&gMsgFontBank0Tiles[w * 32], 128);
                break;
            case 1:
                w = ((u16*)gMsgFontBank1Frames[w])[3];
                sCardMsgGlyphSprites[sTextEntryCount].tiles = LoadObjTiles(&gMsgFontBank1Tiles[w * 32], 128);
                break;
            case 2:
                w = ((u16*)gMsgFontBank2Frames[w])[3];
                sCardMsgGlyphSprites[sTextEntryCount].tiles = LoadObjTiles(&gMsgFontBank2Tiles[w * 32], 128);
                break;
            case 3:
                w = ((u16*)gMsgFontBank3Frames[w])[3];
                sCardMsgGlyphSprites[sTextEntryCount].tiles = LoadObjTiles(&gMsgFontBank3Tiles[w * 32], 128);
                break;
            }

            sTextEntryCount++;
        }

        if (cy > 0x1800) {
            if (*s != 0) {
                v = *(u16*)s;

                if ((u16)((v / 256) | (v << 8)) == 0x8142) {
                    *d = NULL;
                } else {
                    *d = s;
                    return sTextEntryCount;
                }
            } else {
                *d = NULL;
            }
        }
    }

    *d = NULL;
    return sTextEntryCount;
}
#endif

void DrawCardMsgGlyphs(u8 n) {
    u8 i;

    for (i = 0; i < n; i++) {
        TextGlyphSprite* b = sCardMsgGlyphSprites;

        if (b[i].visible == 1) {
            s32 x = b[i].x;
            s32 y = b[i].y;

            if (b[i].tiles != NULL) {
                if (!b[i].useAlternatePalette) {
                    DrawSprite(x >> 8, y >> 8, MSG_FONT_FRAMES[0], b[i].tiles, b[i].palette, NULL, 0, 0);
                } else {
                    DrawSprite(x >> 8, y >> 8, MSG_FONT_FRAMES[0], b[i].tiles, b[i].alternatePalette, NULL, 0, 0);
                }
            }
        }
    }
}

void FreeCardMsgGlyphSprites() {
    u8 i;

    for (i = 0; i < 128; i++) {
        if (sCardMsgGlyphSprites[i].tiles != NULL) {
            ReleaseObjTiles(sCardMsgGlyphSprites[i].tiles);
        }

        if (sCardMsgGlyphSprites[i].palette != NULL) {
            ReleaseObjPalette(sCardMsgGlyphSprites[i].palette);
        }

        if (sCardMsgGlyphSprites[i].alternatePalette != NULL) {
            ReleaseObjPalette(sCardMsgGlyphSprites[i].alternatePalette);
        }
    }

    EwramFree(sCardMsgGlyphSprites);
}

void DrawMsgGlyphsWithPalette(u8 n, void* a) {
    u8 i;

    for (i = 0; i < n; i++) {
        TextGlyphSprite* b = sMsgGlyphSprites;

        if (b[i].visible == 1) {
            s32 x = b[i].x;
            s32 y = b[i].y;

            if (b[i].tiles != NULL) {
                if (!b[i].useAlternatePalette) {
                    DrawSpriteUnsorted(x >> 8, y >> 8, MSG_FONT_FRAMES[0], b[i].tiles, a, 0);
                } else {
                    DrawSpriteUnsorted(x >> 8, y >> 8, MSG_FONT_FRAMES[0], b[i].tiles,
                                  b[i].alternatePalette, 0);
                }
            }
        }
    }
}

u16 FormatSmallFontHex16(s16 v, u16* out) {
    u8 buf[8];
    u8* p;
    s32 i;

    buf[0] = (v & 0xF000) >> 12;
    buf[1] = (v & 0x0F00) >> 8;
    buf[2] = (v & 0x00F0) >> 4;
    buf[3] = v & 0xF;
    buf[4] = 0;
    p = buf;

    for (i = 0; i < 4; i++) {
        if (*p <= 9) {
            *p += 0x30;
        } else {
            *p += 0x37;
        }

        p++;
    }

    return EncodeSmallFontString(buf, out);
}

#ifndef VERSION_EU
s32 CopySjisGlyphsToVram(const TextChar* a) {
    u8 buf[2];
    u16* c;
    u16 w;
    u8 t;
    u8* dst;
    u8 n;
    w = 0;
    dst = (u8*)(OBJ_VRAM0 + 512 * TILE_SIZE_4BPP);
    t = 0;
    n = 0;

    while (*a != 0) {
        u16 v;
        buf[0] = a[0];
        buf[1] = a[1];
        c = (u16*)buf;

        if (*c == 0x6E6E) {
            a += 2;
        } else {
            v = *c;
            v = (v / 256) | (v << 8);
            a += 2;

            if ((v & 0xFF00) == 0x8100) {
                v &= 0xFF;

                switch (v) {
        case 0x40:
            w = 0;
            t = 0;
            break;
        case 0x41:
            w = 0xF5;
            t = 0;
            break;
        case 0x42:
            w = 0xF6;
            t = 0;
            break;
        case 0x45:
            w = 0xF9;
            t = 0;
            break;
        case 0x46:
            w = 0xFA;
            t = 0;
            break;
        case 0x48:
            w = 0xF1;
            t = 0;
            break;
        case 0x49:
            w = 0xF0;
            t = 0;
            break;
        case 0x58:
            w = 20;
            t = 2;
            break;
        case 0x5B:
            w = 0xFD;
            t = 0;
            break;
        case 0x5C:
            w = 0xFC;
            t = 0;
            break;
        case 0x60:
            w = 0xFE;
            t = 0;
            break;
        case 0x63:
            w = 0xFB;
            t = 0;
            break;
        case 0x75:
            w = 0xE8;
            t = 0;
            break;
        case 0x76:
            w = 0xE9;
            t = 0;
            break;
        case 0x77:
            w = 0xEA;
            t = 0;
            break;
        case 0x78:
            w = 0xEB;
            t = 0;
            break;
        case 0x66:
            w = 0xFF;
            t = 0;
            break;
        case 0x69:
            w = 0xEC;
            t = 0;
            break;
        case 0x6A:
            w = 0xED;
            t = 0;
            break;
        case 0xA8:
            w = 0xE7;
            t = 0;
            break;
        case 0xA9:
            w = 0xE6;
            t = 0;
            break;
        case 0x7B:
            w = 0xDF;
            t = 0;
            break;
        case 0x7C:
            w = 0xFC;
            t = 0;
            break;
        case 0xA6:
            w = 0xEE;
            t = 0;
            break;
        case 0x81:
            w = 0xEF;
            t = 0;
            break;
        case 0x93:
            w = 0xF2;
            t = 0;
            break;
        case 0x96:
            w = 0xF4;
            t = 0;
            break;
        case 0x5E:
            w = 0xF3;
            t = 0;
            break;
        case 0x43:
            w = 0xF8;
            t = 0;
            break;
        case 0x9A:
            w = 0x8E;
            t = 0;
            break;
                }
            } else {
                GetSjisGlyph(v, &w, &t);
            }

            switch (t) {
        case 0:
            w = ((u16*)gMsgFontBank0Frames[w])[3];
            CpuCopy16(&gMsgFontBank0Tiles[w * 32], dst, 0x80);
            break;
        case 1:
            w = ((u16*)gMsgFontBank1Frames[w])[3];
            CpuCopy16(&gMsgFontBank1Tiles[w * 32], dst, 0x80);
            break;
        case 2:
            w = ((u16*)gMsgFontBank2Frames[w])[3];
            CpuCopy16(&gMsgFontBank2Tiles[w * 32], dst, 0x80);
            break;
        case 3:
            w = ((u16*)gMsgFontBank3Frames[w])[3];
            CpuCopy16(&gMsgFontBank3Tiles[w * 32], dst, 0x80);
            break;
            }

            dst += 128;
        }

        n++;
    }

    return n;
}
#endif

#ifndef VERSION_EU
s32 CopySjisGlyphsToVramAt(const TextChar* a, u16 b) {
    u8 buf[2];
    u16* c;
    u16 w;
    u8 t;
    u8* dst;
    u8 n;
    w = 0;
    dst = (u8*)(OBJ_VRAM0 + 512 * TILE_SIZE_4BPP) + b * 32;
    t = 0;
    n = 0;

    while (*a != 0) {
        u16 v;
        buf[0] = a[0];
        buf[1] = a[1];
        c = (u16*)buf;

        if (*c == 0x6E6E) {
            a += 2;
        } else {
            v = *c;
            v = (v / 256) | (v << 8);
            a += 2;

            if ((v & 0xFF00) == 0x8100) {
                v &= 0xFF;

                switch (v) {
                case 0x40:
                    w = 0;
                    t = 0;
                    break;
                case 0x41:
                    w = 0xF5;
                    t = 0;
                    break;
                case 0x42:
                    w = 0xF6;
                    t = 0;
                    break;
                case 0x45:
                    w = 0xF9;
                    t = 0;
                    break;
                case 0x46:
                    w = 0xFA;
                    t = 0;
                    break;
                case 0x48:
                    w = 0xF1;
                    t = 0;
                    break;
                case 0x49:
                    w = 0xF0;
                    t = 0;
                    break;
                case 0x58:
                    w = 20;
                    t = 2;
                    break;
                case 0x5B:
                    w = 0xFD;
                    t = 0;
                    break;
                case 0x5C:
                    w = 0xFC;
                    t = 0;
                    break;
                case 0x60:
                    w = 0xFE;
                    t = 0;
                    break;
                case 0x63:
                    w = 0xFB;
                    t = 0;
                    break;
                case 0x75:
                    w = 0xE8;
                    t = 0;
                    break;
                case 0x76:
                    w = 0xE9;
                    t = 0;
                    break;
                case 0x77:
                    w = 0xEA;
                    t = 0;
                    break;
                case 0x78:
                    w = 0xEB;
                    t = 0;
                    break;
                case 0x66:
                    w = 0xFF;
                    t = 0;
                    break;
                case 0x69:
                    w = 0xEC;
                    t = 0;
                    break;
                case 0x6A:
                    w = 0xED;
                    t = 0;
                    break;
                case 0xA8:
                    w = 0xE7;
                    t = 0;
                    break;
                case 0xA9:
                    w = 0xE6;
                    t = 0;
                    break;
                case 0x7B:
                    w = 0xDF;
                    t = 0;
                    break;
                case 0x7C:
                    w = 0xFC;
                    t = 0;
                    break;
                case 0xA6:
                    w = 0xEE;
                    t = 0;
                    break;
                case 0x81:
                    w = 0xEF;
                    t = 0;
                    break;
                case 0x93:
                    w = 0xF2;
                    t = 0;
                    break;
                case 0x96:
                    w = 0xF4;
                    t = 0;
                    break;
                case 0x5E:
                    w = 0xF3;
                    t = 0;
                    break;
                case 0x43:
                    w = 0xF8;
                    t = 0;
                    break;
                case 0x9A:
                    w = 0x8E;
                    t = 0;
                    break;
                }
            } else {
                GetSjisGlyph(v, &w, &t);
            }

            switch (t) {
            case 0:
                w = ((u16*)gMsgFontBank0Frames[w])[3];
                CpuCopy16(&gMsgFontBank0Tiles[w * 32], dst, 0x80);
                break;
            case 1:
                w = ((u16*)gMsgFontBank1Frames[w])[3];
                CpuCopy16(&gMsgFontBank1Tiles[w * 32], dst, 0x80);
                break;
            case 2:
                w = ((u16*)gMsgFontBank2Frames[w])[3];
                CpuCopy16(&gMsgFontBank2Tiles[w * 32], dst, 0x80);
                break;
            case 3:
                w = ((u16*)gMsgFontBank3Frames[w])[3];
                CpuCopy16(&gMsgFontBank3Tiles[w * 32], dst, 0x80);
                break;
            }

            dst += 128;
        }

        n++;
    }

    return n;
}
#endif

u8 CopyLatinGlyphsToVram(const TextChar* a, u16* b, u16 tile) {
    u8* dst = (u8*)(OBJ_VRAM0 + 512 * TILE_SIZE_4BPP) + tile * 32;
    s32 flag = 0;
    sTextEntryCount = 0;
    *b = 0;

    while (*a != 0) {
        s32 v = 0;

#ifdef VERSION_EU
        if (*a == 31) {
#else
        if (*a == 10) {
#endif
            *b = 0;
        } else {
#ifdef VERSION_EU
            v = *a;
#else
#ifdef VERSION_JP
            if (*a > 31) {
#else
            if ((u16)(*a - 32) <= 223) {
#endif
                v = *a;
            } else {
                switch (*a) {
                case 0xE000:
                    v = 25;
                    break;
                case 0x2191:
                    v = 10;
                    break;
                case 0x2193:
                    v = 11;
                    break;
                case 0x2190:
                    v = 12;
                    break;
                case 0x2192:
                    v = 13;
                    break;
                case 0x300C:
                    v = 1;
                    break;
                case 0x300D:
                    v = 2;
                    break;
                case 0x300E:
                    v = 3;
                    break;
                case 0x300F:
                    v = 4;
                    break;
                case 0x203B:
                    v = 6;
                    break;
                case 0x266A:
                    v = 18;
                    break;
                case 0x2642:
                    v = 8;
                    break;
                case 0x2640:
                    v = 9;
                    break;
                case 0x2605:
                    v = 21;
                    break;
                case 0x25A0:
                    v = 17;
                    break;
                default:
                    v = 0;
                    break;
                }
            }
#endif

            if (v != 32) {
                *b = sLatinGlyphWidths.widths[v];
                v = ((u16*)gMsgLatinFontFrames[v])[3];
                CpuCopy16(&gMsgLatinFontTiles[v * 32], dst, 0x80);
                dst += 128;
                sTextEntryCount++;
                b++;
                flag = 1;
            } else if (flag) {
                b[-1] += 3;
            }
        }

        a++;
    }

    return sTextEntryCount;
}
