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

void AddSpriteTextLine(s32 x, s32 y, u8* str) {
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
    len = GetStringLength(str);

    if (len > 15) {
        len = 16;
    }

    sSpriteTextLines[sTextEntryCount].length = len;

    for (i = 0; i < len; i++) {
        s16 c;

        sSpriteTextLines[sTextEntryCount].glyphTiles[i] = AllocSpriteFrameTiles(32);
        c = str[i];

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

        if (str[i] == 37) {
            idx = 44;
        }

        UpdateSpriteFrameTiles(sSpriteTextLines[sTextEntryCount].glyphTiles[i], gSmallFontFrames[idx], gSmallFontTiles);
    }

    sSpriteTextLines[sTextEntryCount].palette = LoadObjPalette(gCommonObjPalette, 32);
    sTextEntryCount++;
}

#ifndef VERSION_EU
void AddSpriteTextLineFont1(s32 x, s32 y, u8* str) {
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
    len = GetStringLength(str);

    if (len > 15) {
        len = 16;
    }

    sSpriteTextLines[sTextEntryCount].length = len;

    for (i = 0, k = 0; i < len; i++) {
        s32 c = str[i];

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

void AddSpriteTextNumber(s32 x, s32 y, s32 value) {
    u8 buf[20];
    u8 i;

    if (value >= 0) {
        buf[0] = value / 10000000;
        buf[1] = value / 1000000 - buf[0] * 10;
        buf[2] = value / 100000 - buf[0] * 100 - buf[1] * 10;
        buf[3] = value / 10000 - buf[0] * 1000 - buf[1] * 100 - buf[2] * 10;
        buf[4] = value / 1000 - buf[0] * 10000 - buf[1] * 1000 - buf[2] * 100 - buf[3] * 10;
        buf[5] = value / 100 - buf[0] * 100000 - buf[1] * 10000 - buf[2] * 1000 - buf[3] * 100 - buf[4] * 10;
        buf[6] = value / 10 - buf[0] * 1000000 - buf[1] * 100000 - buf[2] * 10000 - buf[3] * 1000 - buf[4] * 100 - buf[5] * 10;
        buf[7] = value - (buf[0] * 10000000 + buf[1] * 1000000 + buf[2] * 100000 + buf[3] * 10000 + buf[4] * 1000 + buf[5] * 100 + buf[6] * 10);
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
        value = -value;
        buf[1] = value / 10000000;
        buf[2] = value / 1000000 - buf[1] * 10;
        buf[3] = value / 100000 - buf[1] * 100 - buf[2] * 10;
        buf[4] = value / 10000 - buf[1] * 1000 - buf[2] * 100 - buf[3] * 10;
        buf[5] = value / 1000 - buf[1] * 10000 - buf[2] * 1000 - buf[3] * 100 - buf[4] * 10;
        buf[6] = value / 100 - buf[1] * 100000 - buf[2] * 10000 - buf[3] * 1000 - buf[4] * 100 - buf[5] * 10;
        buf[7] = value / 10 - buf[1] * 1000000 - buf[2] * 100000 - buf[3] * 10000 - buf[4] * 1000 - buf[5] * 100 - buf[6] * 10;
        buf[8] = value - (buf[1] * 10000000 + buf[2] * 1000000 + buf[3] * 100000 + buf[4] * 10000 + buf[5] * 1000 + buf[6] * 100 + buf[7] * 10);
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
void* InitSpriteTextSlots(s32 mode) {
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

        switch (mode) {
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
void SetSpriteTextSlot(s32 x, s32 y, TextChar* text, u8 slot, u8 useAlternatePalette) {
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
    sSpriteTextLines[slot].useAlternatePalette = useAlternatePalette;

    while (*text != 0) {
        u16 v;
        v = *(u16*)text;
        v = (v >> 8) | (v << 8);
        text += 2;

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
void SetSpriteTextSlotXDigits(s32 x, s32 y, u8 value, u8 slot, u8 useAlternatePalette) {
    u8 buf[4];
    buf[0] = 0x78;
    buf[1] = value / 10;
    buf[2] = value - buf[1] * 10;
    buf[3] = 0;
    buf[1] += 0x30;
    buf[2] += 0x30;
    SetSpriteTextSlotAscii(x, y, buf, slot, useAlternatePalette);
}
#endif

#ifndef VERSION_EU
void SetSpriteTextSlotAscii(s32 x, s32 y, u8* str, u8 slot, u8 useAlternatePalette) {
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
    sSpriteTextLines[slot].useAlternatePalette = useAlternatePalette;
    len = GetStringLength(str);

    if (len > 15) {
        len = 16;
    }

    i = 0;
    j = 0;
    count = len;

    for (; i < len; i++) {
        if ((u8)(str[i] - 48) <= 9) {
            idx = (u8)(str[i] + 209);
        }

        if ((u8)(str[i] - 65) <= 25) {
            idx = (u8)(str[i] + 202);
        }

        if ((u8)(str[i] - 97) <= 25) {
            idx = (u8)(str[i] + 196);
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
void SetBgTextLineNumber(u8 x, u8 y, u8 glyphHeight, u8 value, u8 slot, u8 paletteIndex) {
    u8 buf[5];
    buf[1] = value / 10;
    buf[3] = value - buf[1] * 10;
    buf[0] = 0x82;
    buf[1] += 0x4F;
    buf[2] = 0x82;
    buf[3] += 0x4F;
    buf[4] = 0;
    SetBgTextLine(x, y, glyphHeight, buf, slot, paletteIndex);
}
#endif

#ifndef VERSION_EU
void SetBgTextLine(u8 x, u8 y, u8 glyphHeight, u8* text, u8 slot, u8 paletteIndex) {
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
    if (slot > 23) {
        return;
    }

    if (sBgTextLines == NULL) {
        return;
    }

    sBgTextLines[slot].x = x;
    sBgTextLines[slot].y = y;
    sBgTextLines[slot].glyphHeight = glyphHeight;
    sBgTextLines[slot].dirty = 1;
    sBgTextLines[slot].paletteIndex = paletteIndex;

    while (*text != 0) {
        w = *(u16*)text;
        w = (w >> 8) | (w << 8);
        text += 2;

        if (glyphHeight > 8) {
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

        sBgTextLines[slot].glyphs[j] = glyph;
        j++;
        i++;
    }

    sBgTextLines[slot].length = i;

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

u16 InitMsgGlyphSprites(s32 mode) {
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

        switch (mode) {
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

u16 InitMsgGlyphSpritesAltPalette5(s32 mode) {
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

        switch (mode) {
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

u16 InitMsgGlyphSpritesAltPalette3(s32 mode) {
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

        switch (mode) {
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

s32 GetMsgTextWidth(const TextChar* text) {
    u16 sum;
    s32 v;

    sum = 0;

    while (*text != 0) {
        v = 0;

        if (*text != 10) {
#ifdef VERSION_US
            if ((u16)(*text - 32) <= 223) {
#else
            if (*text > 31) {
#endif
                v = *text;
            } else {
                switch (*text) {
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

        text++;
    }

    return (s16)sum;
}

#ifdef VERSION_EU
#define MSG_LATIN_CODE(wide, byte) (byte)
#else
#define MSG_LATIN_CODE(wide, byte) (wide)
#endif
u8 LayoutMsgGlyphsPage(s32 x, s32 y, MsgLatinChar* text, MsgLatinChar** nextText) {
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

    while (*text != 0) {
        s32 v = 0;

        sMsgGlyphSprites[sTextEntryCount].x = x + cx;
        sMsgGlyphSprites[sTextEntryCount].y = y + cy;
        sMsgGlyphSprites[sTextEntryCount].visible = 1;

        if (*text == MSG_LATIN_CODE(0x4079, 29)) {
            f = 1;
            text++;
        }

        if (*text == MSG_LATIN_CODE(0x4000, 30)) {
            f = 0;
            text++;
        }

        sMsgGlyphSprites[sTextEntryCount].useAlternatePalette = f;

        if (*text == MSG_LATIN_CODE(10, 31)) {
            cx = 0;
            cy += 0xC00;
        } else {
#ifdef VERSION_EU
            v = *text;
#else
            if ((u16)(*text - 32) <= 223) {
                v = *text;
            } else {
                switch (*text) {
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

        text++;

        if (cy > 0x1800) {
            *nextText = text;
            return sTextEntryCount;
        }
    }

    *nextText = NULL;
    return sTextEntryCount;
}

u8 LayoutMsgGlyphs(s32 x, s32 y, const MsgLatinChar* text) {
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

    while (*text != 0) {
        s32 v = 0;

        sMsgGlyphSprites[sTextEntryCount].x = x + cx;
        sMsgGlyphSprites[sTextEntryCount].y = y + cy;
        sMsgGlyphSprites[sTextEntryCount].visible = 1;

        if (*text == MSG_LATIN_CODE(0x4079, 29)) {
            f = 1;
            text++;
        }

        if (*text == MSG_LATIN_CODE(0x4000, 30)) {
            f = 0;
            text++;
        }

        sMsgGlyphSprites[sTextEntryCount].useAlternatePalette = f;

        if (*text == MSG_LATIN_CODE(10, 31)) {
            cx = 0;
            cy += 0xC00;
        } else {
#ifdef VERSION_EU
            v = *text;
#else
            if ((u16)(*text - 32) <= 223) {
                v = *text;
            } else {
                switch (*text) {
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

        text++;
    }

    return sTextEntryCount;
}

#ifndef VERSION_EU
u8 LayoutMsgGlyphsSjis(s32 x, s32 y, const u8* text) {
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

    while (*text != 0) {
        u16 v;
        w = 0;
        sMsgGlyphSprites[sTextEntryCount].x = x + cx;
        sMsgGlyphSprites[sTextEntryCount].y = y + cy;

        sMsgGlyphSprites[sTextEntryCount].visible = 1;

        if (*(u16*)text == 0x6E6E) {
            cx = 0;
            cy += 0xC00;
            text += 2;
        } else {
            v = *(u16*)text;
            v = (v / 256) | (v << 8);
            text += 2;

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
u16 LoadTwoDigitTextTileArray(u8 value, void** out) {
    u8 buf[8];
    u8 q;
    q = value / 10;

    if (q != 0) {
        buf[1] = value / 10;
        buf[3] = value - buf[1] * 10;
        buf[0] = 0x82;
        buf[1] += 0x4F;
        buf[2] = 0x82;
        buf[3] += 0x4F;
        buf[4] = 0;
    } else {
        buf[1] = value + 0x4F;
        buf[0] = 0x82;
        buf[2] = 0;
    }

    return LoadTextTileArray((TextChar*)buf, out);
}
#endif

void InitTextTileArray(void** tiles, u8 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        *tiles++ = NULL;
    }
}

void FreeTextTileArray(void** tiles, u8 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        if (*tiles != NULL) {
            ReleaseObjTiles(*tiles);
            *tiles = NULL;
        }

        tiles++;
    }
}

u16 LoadTwoDigitTextSlots(u8 value, TextSlot* out) {
#ifdef VERSION_JP
    u8 buf[8];
    s32 q;

    q = value / 10;

    if ((u8)q != 0) {
        buf[1] = value / 10;
        buf[3] = value - buf[1] * 10;
        buf[0] = 0x82;
        buf[1] += 0x4F;
        buf[2] = 0x82;
        buf[3] += 0x4F;
        buf[4] = 0;
    } else {
        buf[1] = value + 0x4F;
        buf[0] = 0x82;
        buf[2] = 0;
    }
#else
    TextChar buf[4];
    TextChar* p;
    TextChar c;
    TextChar end;

    if (value > 9) {
        p = buf;
        c = value / 10 + '0';
        end = 0;
        p[0] = c;
        buf[1] = value - (u8)(value / 10) * 10 + '0';
        buf[2] = end;
    } else {
        buf[0] = value + '0';
        buf[1] = 0;
    }
#endif

    return LoadTextSlots(buf, out);
}

void InitTextSlots(TextSlot* slots, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        slots->tiles = NULL;
        slots->advance = 0;
        slots++;
    }
}

void FreeTextSlots(TextSlot* slots, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        if (slots->tiles != NULL) {
            ReleaseObjTiles(slots->tiles);
            slots->tiles = NULL;
        }

        slots->advance = 0;
        slots++;
    }
}

s16 GetTextSlotsWidth(TextSlot* slots, u8 n) {
    s16 x;
    s32 i;

    x = 0;

    for (i = 0; i < n; i++) {
        if (slots[i].tiles != NULL) {
            if (slots[i].advance != -1) {
                x += slots[i].advance;
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
s16 GetTextSlotsMaxLineWidth(TextSlot* slots, u8 n) {
    s16 max = 0;
    s16 x = 0;
    s32 i;

    for (i = 0; i < n; i++) {
        if (slots[i].tiles != NULL) {
            if (slots[i].advance != -1) {
                x += slots[i].advance;
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

s32 GetTextLength(const void* text) {
#ifdef VERSION_JP
    const u16* p = text;
    u16 n = 0;
#elif defined(VERSION_EU)
    u16 n = 0;
    const u8* p = text;
#else
    u16 n = 0;
    const u16* p = text;
#endif

    while (MSG_CHAR(p) != 0) {
        n++;
        p++;
    }

    return n;
}

u16 LoadTextSlots(const void* text, TextSlot* slots) {
#ifdef VERSION_JP
    return LoadJapaneseTextSlots(text, slots);
#else
    return LoadLatinTextSlots(text, slots);
#endif
}

s32 LoadLatinTextSlots(const u16* text, TextSlot* slots) {
    s32 n;

    n = 0;
    sTextEntryCount = n;

    while (MSG_CHAR(text) != 0) {
        s32 v = 0;

#ifdef VERSION_EU
        if (MSG_CHAR(text) == 31) {
#else
        if (MSG_CHAR(text) == 10) {
#endif
            if (slots->tiles != NULL) {
                ReleaseObjTiles(slots->tiles);
                slots->tiles = NULL;
            }

            slots->advance = 0;
        } else {
#ifdef VERSION_EU
            v = MSG_CHAR(text);
#else
#ifdef VERSION_JP
            if (MSG_CHAR(text) > 31) {
#else
            if ((u16)(MSG_CHAR(text) - 32) <= 223) {
#endif
                v = MSG_CHAR(text);
            } else {
                switch (MSG_CHAR(text)) {
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

            if (slots->tiles != NULL) {
                ReleaseObjTiles(slots->tiles);
                slots->tiles = NULL;
            }

            if (v != 32) {
                slots->advance = sLatinGlyphWidths.widths[v];
            } else {
                slots->advance = 255;
            }

            v = ((u16*)gMsgLatinFontFrames[v])[3];
            slots->tiles = LoadObjTiles(&gMsgLatinFontTiles[v * 32], 128);
            slots->useAlternatePalette = n;
        }

        sTextEntryCount++;
        slots++;
#if defined(VERSION_EU) || defined(VERSION_JP)
        text = (u16*)((u8*)text + 1);
#else
        text++;
#endif
    }

    return sTextEntryCount;
}

#ifndef VERSION_EU
s32 LoadJapaneseTextSlots(const u16* text, TextSlot* slots) {
    u8 buf[2];
    u16* c;
    u16 w;
    u8 t;
    u8 n;

    w = 0;
    t = 0;
    n = 0;

    while (MSG_CHAR(text) != 0) {
        u16 v;

#ifdef VERSION_JP
        buf[0] = ((u8*)text)[0];
        buf[1] = ((u8*)text)[1];
#else
        buf[0] = text[0];
        buf[1] = text[1];
#endif
        c = (u16*)buf;

        if (*c == 0x6E6E) {
#ifdef VERSION_JP
            text = (u16*)((u8*)text + 2);
#else
            text += 2;
#endif

            if (slots->tiles != NULL) {
                ReleaseObjTiles(slots->tiles);
            }

            slots->tiles = NULL;
            slots->advance = 0;
        } else {
            v = *c;
            v = (v / 256) | (v << 8);
#ifdef VERSION_JP
            text = (u16*)((u8*)text + 2);
#else
            text += 2;
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

            if (slots->tiles != NULL) {
                ReleaseObjTiles(slots->tiles);
                slots->tiles = NULL;
            }

            switch (t) {
            case 0:
                w = ((u16*)gMsgFontBank0Frames[w])[3];
                slots->tiles = LoadObjTiles(&gMsgFontBank0Tiles[w * 32], 128);
                break;
            case 1:
                w = ((u16*)gMsgFontBank1Frames[w])[3];
                slots->tiles = LoadObjTiles(&gMsgFontBank1Tiles[w * 32], 128);
                break;
            case 2:
                w = ((u16*)gMsgFontBank2Frames[w])[3];
                slots->tiles = LoadObjTiles(&gMsgFontBank2Tiles[w * 32], 128);
                break;
            case 3:
                w = ((u16*)gMsgFontBank3Frames[w])[3];
                slots->tiles = LoadObjTiles(&gMsgFontBank3Tiles[w * 32], 128);
                break;
            }

            slots->advance = 10;
        }

        slots++;
        n++;
    }

    return n;
}
#endif

#ifndef VERSION_EU
s32 LoadTextTileArray(TextChar* text, void** tiles) {
    u8 buf[2];
    u16* c;
    u16 w;
    u8 t;
    u8 n;

    w = 0;
    t = 0;
    n = 0;

    while (*text != 0) {
        u16 v;

        buf[0] = text[0];
        buf[1] = text[1];
        c = (u16*)buf;

        if (*c == 0x6E6E) {
            text += 2;

            if (*tiles != NULL) {
                ReleaseObjTiles(*tiles);
            }

            *tiles++ = NULL;
        } else {
            v = *c;
            v = (v / 256) | (v << 8);
            text += 2;

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

            if (*tiles != NULL) {
                ReleaseObjTiles(*tiles);
                *tiles = NULL;
            }

            switch (t) {
            case 0:
                w = ((u16*)gMsgFontBank0Frames[w])[3];
                *tiles = LoadObjTiles(&gMsgFontBank0Tiles[w * 32], 128);
                break;
            case 1:
                w = ((u16*)gMsgFontBank1Frames[w])[3];
                *tiles = LoadObjTiles(&gMsgFontBank1Tiles[w * 32], 128);
                break;
            case 2:
                w = ((u16*)gMsgFontBank2Frames[w])[3];
                *tiles = LoadObjTiles(&gMsgFontBank2Tiles[w * 32], 128);
                break;
            case 3:
                w = ((u16*)gMsgFontBank3Frames[w])[3];
                *tiles = LoadObjTiles(&gMsgFontBank3Tiles[w * 32], 128);
                break;
            }

            tiles++;
        }

        n++;
    }

    return n;
}
#endif

void* LoadTextPalette(s32 palette) {
    void* r = NULL;

    switch (palette) {
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

void DrawTextSlots(s16 x, s16 y, TextSlot* slots, void* palette, u16 priority, u8 n) {
    s16 x0 = x;
    s16 cy = y;
    u8 i;

#ifndef VERSION_JP
    cy -= 2;
#endif

    for (i = 0; i < n; i++) {
        if (slots->tiles == NULL) {
            cy += 12;
            x = x0;
        } else if (slots->advance != -1) {
            DrawSprite(x, cy, MSG_FONT_FRAMES[0], slots->tiles, palette, NULL, 0, priority);
            x += slots->advance;
        } else {
            x += 3;
        }

        slots++;
    }
}

void DrawTextSlotsUnsorted(s16 x, s16 y, TextSlot* slots, void* palette, s32 priority, u8 n) {
    s16 x0 = x;
    s16 cy = y;
    u8 i;

#ifndef VERSION_JP
    cy -= 2;
#endif

    for (i = 0; i < n; i++) {
        if (slots->tiles == NULL) {
            cy += 12;
            x = x0;
        } else if (slots->advance != -1) {
            DrawSpriteUnsorted(x, cy, MSG_FONT_FRAMES[0], slots->tiles, palette, 0);
            x += slots->advance;
        } else {
            x += 3;
        }

        slots++;
    }
}

void DrawTextSlotsWithFlags(s16 x, s32 y, TextSlot* slots, void* palette, u16 flags, u16 priority, u8 n) {
    s16 x0 = x;
    s16 cy = y;
    u8 i;

#ifndef VERSION_JP
    cy -= 2;
#endif

    for (i = 0; i < n; i++) {
        if (slots->tiles == NULL) {
            cy += 12;
            x = x0;
        } else if (slots->advance != -1) {
            DrawSprite(x, cy, MSG_FONT_FRAMES[0], slots->tiles, palette, NULL, flags, priority);
            x += slots->advance;
        } else {
            x += 3;
        }

        slots++;
    }
}

void DrawTextSlotsWithTwoPalettes(s16 x, s32 y, TextSlot* slots, void* palette, void* alternatePalette, u16 priority, u8 n) {
    s16 x0 = x;
    s16 cy = y;
    u8 i;

#ifndef VERSION_JP
    cy -= 2;
#endif

    for (i = 0; i < n; i++) {
        if (slots->tiles == NULL) {
            cy += 12;
            x = x0;
        } else if (slots->advance != -1) {
            if (slots->useAlternatePalette == 0) {
                DrawSprite(x, cy, MSG_FONT_FRAMES[0], slots->tiles, palette, NULL, 0, priority);
            } else {
                DrawSprite(x, cy, MSG_FONT_FRAMES[0], slots->tiles, alternatePalette, NULL, 0, priority);
            }

            x += slots->advance;
        } else {
            x += 3;
        }

        slots++;
    }
}

void DrawTextTileArray(s16 x, s32 y, void** tiles, void* palette, u16 priority, u8 n) {
    s16 cy = y;
    s16 x0 = x;
    u8 i;

    for (i = 0; i < n; i++) {
        if (*tiles == NULL) {
            cy += 12;
            x = x0;
        } else {
            DrawSprite(x, cy, MSG_FONT_FRAMES[0], *tiles, palette, NULL, 0, priority);
            x += 10;
        }

        tiles++;
    }
}

void DrawTextTileArrayWithTwoPalettes(s16 x, s32 y, void** tiles, void* palette, s32 alternatePalette, u16 priority, u8 n) {
    s16 cy = y;
    s16 x0 = x;
    u8 i;

    for (i = 0; i < n; i++) {
        if (*tiles == NULL) {
            cy += 12;
            x = x0;
        } else {
            DrawSprite(x, cy, MSG_FONT_FRAMES[0], *tiles, palette, NULL, 0, priority);
            x += 10;
        }

        tiles++;
    }
}

void* LoadSmallFontTiles() {
    return LoadObjTiles(gSmallFontTiles, 0x5A0);
}

void* LoadSmallFontPalette() {
    return LoadObjPalette(gCommonObjPalette, 0x20);
}

void FreeSmallFontResources(void* tiles, void* palette) {
    ReleaseObjTiles(tiles);
    ReleaseObjPalette(palette);
}

u16 EncodeSmallFontString(const u8* str, u16* out) {
    u16 g = 0;
    u8 n;
    u8 i;

    if (out == NULL) {
        return 0;
    }

    n = GetStringLength(str);

    for (i = 0; i < n; i++) {
        if ((u8)(str[i] - '0') <= 9) {
            g = str[i] - '0';
        }

        if ((u8)(str[i] - 'A') <= 25) {
            g = str[i] - 0x37;
        }

        if ((u8)(str[i] - 'a') <= 25) {
            g = str[i] - 0x57;
        }

        if (str[i] == '/') {
            g = 0x24;
        }

        if (str[i] == '-') {
            g = 0x25;
        }

        if (str[i] == '_') {
            g = 0x26;
        }

        if (str[i] == '.') {
            g = 0x27;
        }

        if (str[i] == '+') {
            g = 0x28;
        }

        if (str[i] == '!') {
            g = 0x29;
        }

        if (str[i] == '?') {
            g = 0x2A;
        }

        if (str[i] == '#') {
            g = 0x2B;
        }

        if (str[i] == '%') {
            g = 0x2C;
        }

        *out++ = g;
    }

    return n;
}

u16 FormatSmallFontDecimal(s32 value, u16* out) {
    s32 t[11];
    u8 s[12];
    s32 acc;
    s32 d;
    s32 i;

    acc = 0;

    if (value >= 0) {
        d = 1000000000;

        for (i = 0; i <= 9; i++) {
            t[i] = value / d - acc;
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
        t[i] = value / d - acc;
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

u16 FormatSmallFontHex(s32 value, u16* out) {
    u8 buf[11];
    u8* p;
    s32 i;

    buf[0] = '0';
    buf[1] = 'x';
    buf[2] = (value & 0xF0000000) >> 28;
    buf[3] = (value & 0x0F000000) >> 24;
    buf[4] = (value & 0x00F00000) >> 20;
    buf[5] = (value & 0x000F0000) >> 16;
    buf[6] = (value & 0x0000F000) >> 12;
    buf[7] = (value & 0x00000F00) >> 8;
    buf[8] = (value & 0x000000F0) >> 4;
    buf[9] = value & 0xF;
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

u16 FormatSmallFontBinary(u32 value, u16* out, u8 mode) {
    u8 a[2];
    u8 b[9];
    u8 c[17];
    u8 d[33];

    switch (mode) {
    case 0:
        a[0] = value;
        a[0] += '0';
        a[1] = 0;
        return EncodeSmallFontString(a, out);
    case 1:
        b[0] = (value >> 7) + '0';
        b[1] = ((value >> 6) & 1) + '0';
        b[2] = ((value >> 5) & 1) + '0';
        b[3] = ((value >> 4) & 1) + '0';
        b[4] = ((value >> 3) & 1) + '0';
        b[5] = ((value >> 2) & 1) + '0';
        b[6] = ((value >> 1) & 1) + '0';
        b[7] = (value & 1) + '0';
        b[8] = 0;
        return EncodeSmallFontString(b, out);
    case 2:
        c[0] = (value >> 15) + '0';
        c[1] = ((value >> 14) & 1) + '0';
        c[2] = ((value >> 13) & 1) + '0';
        c[3] = ((value >> 12) & 1) + '0';
        c[4] = ((value >> 11) & 1) + '0';
        c[5] = ((value >> 10) & 1) + '0';
        c[6] = ((value >> 9) & 1) + '0';
        c[7] = ((value >> 8) & 1) + '0';
        c[8] = ((value >> 7) & 1) + '0';
        c[9] = ((value >> 6) & 1) + '0';
        c[10] = ((value >> 5) & 1) + '0';
        c[11] = ((value >> 4) & 1) + '0';
        c[12] = ((value >> 3) & 1) + '0';
        c[13] = ((value >> 2) & 1) + '0';
        c[14] = ((value >> 1) & 1) + '0';
        c[15] = (value & 1) + '0';
        c[16] = 0;
        return EncodeSmallFontString(c, out);
    case 3:
        d[0] = (value >> 31) + '0';
        d[1] = ((value >> 30) & 1) + '0';
        d[2] = ((value >> 29) & 1) + '0';
        d[3] = ((value >> 28) & 1) + '0';
        d[4] = ((value >> 27) & 1) + '0';
        d[5] = ((value >> 26) & 1) + '0';
        d[6] = ((value >> 25) & 1) + '0';
        d[7] = ((value >> 24) & 1) + '0';
        d[8] = ((value >> 23) & 1) + '0';
        d[9] = ((value >> 22) & 1) + '0';
        d[10] = ((value >> 21) & 1) + '0';
        d[11] = ((value >> 20) & 1) + '0';
        d[12] = ((value >> 19) & 1) + '0';
        d[13] = ((value >> 18) & 1) + '0';
        d[14] = ((value >> 17) & 1) + '0';
        d[15] = ((value >> 16) & 1) + '0';
        d[16] = ((value >> 15) & 1) + '0';
        d[17] = ((value >> 14) & 1) + '0';
        d[18] = ((value >> 13) & 1) + '0';
        d[19] = ((value >> 12) & 1) + '0';
        d[20] = ((value >> 11) & 1) + '0';
        d[21] = ((value >> 10) & 1) + '0';
        d[22] = ((value >> 9) & 1) + '0';
        d[23] = ((value >> 8) & 1) + '0';
        d[24] = ((value >> 7) & 1) + '0';
        d[25] = ((value >> 6) & 1) + '0';
        d[26] = ((value >> 5) & 1) + '0';
        d[27] = ((value >> 4) & 1) + '0';
        d[28] = ((value >> 3) & 1) + '0';
        d[29] = ((value >> 2) & 1) + '0';
        d[30] = ((value >> 1) & 1) + '0';
        d[31] = (value & 1) + '0';
        return EncodeSmallFontString(d, out);
    }
}

s32 DrawSmallFontString(s16 x, s16 y, u16* str, void* tiles, void* palette, u16 priority, u8 n) {
    u8 i;

    for (i = 0; i < n; i++) {
        DrawSprite(x + i * 8, y, gSmallFontFrames[*str], tiles, palette, NULL, 0, priority);
        str++;
    }
}

void GetSjisGlyph(u16 code, u16* glyph, u8* bank) {
    switch (code & 0xFF00) {
    case 0x8200: {
        u16 v = code & 0xFF;

        if ((u16)(v - 96) <= 25) {
            *glyph = code + 0x7DAB;
        }

        if ((u16)(v - 129) <= 25) {
            *glyph = code + 0x7DA4;
        }

        if ((u16)(v - 79) <= 9) {
            *glyph = code + 0x7DB2;
        }

        if ((u16)(v - 159) <= 82) {
            *glyph = code + 0x7DA0;
        }

        *bank = 0;
        break;
    }
    case 0x8300: {
        u16 v = code & 0xFF;

        if ((u16)(v - 64) <= 62) {
            *glyph = code + 0x7D52;
        }

        if ((u16)(v - 128) <= 20) {
            *glyph = code + 0x7D51;
        }

        *bank = 0;
        break;
    }
    case 0x8700:
        switch (code & 0xFF) {
        case 0x56:
            *glyph = 143;
            *bank = 0;
            break;
        case 0x5D:
            *glyph = 142;
            *bank = 0;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x8800:
        switch (code & 0xFF) {
        case 0xC5:
            *glyph = 9;
            *bank = 1;
            break;
        case 0xC3:
            *glyph = 84;
            *bank = 1;
            break;
        case 0xF3:
            *glyph = 86;
            *bank = 1;
            break;
        case 0xEA:
            *glyph = 104;
            *bank = 1;
            break;
        case 0xF9:
            *glyph = 153;
            *bank = 1;
            break;
        case 0xE1:
            *glyph = 179;
            *bank = 1;
            break;
        case 0xC8:
            *glyph = 182;
            *bank = 1;
            break;
        case 0xAB:
            *glyph = 208;
            *bank = 1;
            break;
        case 0xF6:
            *glyph = 247;
            *bank = 1;
            break;
        case 0xB5:
            *glyph = 250;
            *bank = 1;
            break;
        case 0xD3:
            *glyph = 3;
            *bank = 2;
            break;
        case 0xC0:
            *glyph = 17;
            *bank = 2;
            break;
        case 0xCD:
            *glyph = 57;
            *bank = 2;
            break;
        case 0xE7:
            *glyph = 105;
            *bank = 2;
            break;
        case 0xF8:
            *glyph = 164;
            *bank = 2;
            break;
        case 0xF5:
            *glyph = 184;
            *bank = 2;
            break;
        case 0xA4:
            *glyph = 192;
            *bank = 2;
            break;
        case 0xA3:
            *glyph = 207;
            *bank = 2;
            break;
        case 0xC4:
            *glyph = 63;
            *bank = 3;
            break;
        case 0xAC:
            *glyph = 78;
            *bank = 3;
            break;
        case 0xDF:
            *glyph = 102;
            *bank = 3;
            break;
        case 0xDA:
            *glyph = 118;
            *bank = 3;
            break;
        case 0xD9:
            *glyph = 135;
            *bank = 3;
            break;
        case 0xCA:
            *glyph = 136;
            *bank = 3;
            break;
        case 0xD0:
            *glyph = 187;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x8900:
        switch (code & 0xFF) {
        case 0x9C:
            *glyph = 4;
            *bank = 1;
            break;
        case 0xAF:
            *glyph = 26;
            *bank = 1;
            break;
        case 0xBD:
            *glyph = 47;
            *bank = 1;
            break;
        case 0xA4:
            *glyph = 49;
            *bank = 1;
            break;
        case 0x69:
            *glyph = 74;
            *bank = 1;
            break;
        case 0x93:
            *glyph = 75;
            *bank = 1;
            break;
        case 0xF6:
            *glyph = 95;
            *bank = 1;
            break;
        case 0xEF:
            *glyph = 98;
            *bank = 1;
            break;
        case 0x52:
            *glyph = 103;
            *bank = 1;
            break;
        case 0xB4:
            *glyph = 107;
            *bank = 1;
            break;
        case 0xC6:
            *glyph = 121;
            *bank = 1;
            break;
        case 0x5E:
            *glyph = 124;
            *bank = 1;
            break;
        case 0x42:
            *glyph = 160;
            *bank = 1;
            break;
        case 0xBB:
            *glyph = 198;
            *bank = 1;
            break;
        case 0xEE:
            *glyph = 205;
            *bank = 1;
            break;
        case 0xBA:
            *glyph = 1;
            *bank = 2;
            break;
        case 0x98:
            *glyph = 8;
            *bank = 2;
            break;
        case 0xBC:
            *glyph = 15;
            *bank = 2;
            break;
        case 0xF0:
            *glyph = 61;
            *bank = 2;
            break;
        case 0xF1:
            *glyph = 65;
            *bank = 2;
            break;
        case 0xCA:
            *glyph = 89;
            *bank = 2;
            break;
        case 0x6A:
            *glyph = 101;
            *bank = 2;
            break;
        case 0xE4:
            *glyph = 104;
            *bank = 2;
            break;
        case 0xB9:
            *glyph = 120;
            *bank = 2;
            break;
        case 0xAE:
            *glyph = 124;
            *bank = 2;
            break;
        case 0xC1:
            *glyph = 152;
            *bank = 2;
            break;
        case 0x70:
            *glyph = 155;
            *bank = 2;
            break;
        case 0xF7:
            *glyph = 177;
            *bank = 2;
            break;
        case 0xDF:
            *glyph = 200;
            *bank = 2;
            break;
        case 0xE6:
            *glyph = 201;
            *bank = 2;
            break;
        case 0xBF:
            *glyph = 218;
            *bank = 2;
            break;
        case 0x65:
            *glyph = 240;
            *bank = 2;
            break;
        case 0x7A:
            *glyph = 244;
            *bank = 2;
            break;
        case 0xC8:
            *glyph = 13;
            *bank = 3;
            break;
        case 0x41:
            *glyph = 51;
            *bank = 3;
            break;
        case 0x8F:
            *glyph = 55;
            *bank = 3;
            break;
        case 0x9E:
            *glyph = 80;
            *bank = 3;
            break;
        case 0x45:
            *glyph = 113;
            *bank = 3;
            break;
        case 0xCE:
            *glyph = 129;
            *bank = 3;
            break;
        case 0x9F:
            *glyph = 142;
            *bank = 3;
            break;
        case 0xD7:
            *glyph = 148;
            *bank = 3;
            break;
        case 0xC2:
            *glyph = 150;
            *bank = 3;
            break;
        case 0x8A:
            *glyph = 154;
            *bank = 3;
            break;
        case 0xD4:
            *glyph = 181;
            *bank = 3;
            break;
        case 0xFC:
            *glyph = 188;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x8A00:
        switch (code & 0xFF) {
        case 0x4F:
            *glyph = 8;
            *bank = 1;
            break;
        case 0x6D:
            *glyph = 17;
            *bank = 1;
            break;
        case 0xB5:
            *glyph = 61;
            *bank = 1;
            break;
        case 0x4B:
            *glyph = 76;
            *bank = 1;
            break;
        case 0xA3:
            *glyph = 81;
            *bank = 1;
            break;
        case 0x45:
            *glyph = 83;
            *bank = 1;
            break;
        case 0xD4:
            *glyph = 101;
            *bank = 1;
            break;
        case 0x43:
            *glyph = 123;
            *bank = 1;
            break;
        case 0xEB:
            *glyph = 139;
            *bank = 1;
            break;
        case 0xB4:
            *glyph = 167;
            *bank = 1;
            break;
        case 0x79:
            *glyph = 188;
            *bank = 1;
            break;
        case 0x58:
            *glyph = 199;
            *bank = 1;
            break;
        case 0xAA:
            *glyph = 252;
            *bank = 1;
            break;
        case 0xB1:
            *glyph = 9;
            *bank = 2;
            break;
        case 0xEF:
            *glyph = 13;
            *bank = 2;
            break;
        case 0xE7:
            *glyph = 54;
            *bank = 2;
            break;
        case 0xE8:
            *glyph = 59;
            *bank = 2;
            break;
        case 0xC3:
            *glyph = 64;
            *bank = 2;
            break;
        case 0xC8:
            *glyph = 84;
            *bank = 2;
            break;
        case 0xF1:
            *glyph = 140;
            *bank = 2;
            break;
        case 0x6F:
            *glyph = 143;
            *bank = 2;
            break;
        case 0x4A:
            *glyph = 146;
            *bank = 2;
            break;
        case 0x51:
            *glyph = 149;
            *bank = 2;
            break;
        case 0xD6:
            *glyph = 178;
            *bank = 2;
            break;
        case 0x69:
            *glyph = 248;
            *bank = 2;
            break;
        case 0x47:
            *glyph = 3;
            *bank = 3;
            break;
        case 0x77:
            *glyph = 14;
            *bank = 3;
            break;
        case 0xEC:
            *glyph = 46;
            *bank = 3;
            break;
        case 0xAE:
            *glyph = 56;
            *bank = 3;
            break;
        case 0xED:
            *glyph = 76;
            *bank = 3;
            break;
        case 0xB7:
            *glyph = 85;
            *bank = 3;
            break;
        case 0x88:
            *glyph = 88;
            *bank = 3;
            break;
        case 0xA5:
            *glyph = 145;
            *bank = 3;
            break;
        case 0xFA:
            *glyph = 162;
            *bank = 3;
            break;
        case 0xAB:
            *glyph = 166;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x8B00:
        switch (code & 0xFF) {
        case 0x4C:
            *glyph = 25;
            *bank = 1;
            break;
        case 0x41:
            *glyph = 30;
            *bank = 1;
            break;
        case 0x43:
            *glyph = 38;
            *bank = 1;
            break;
        case 0x5E:
            *glyph = 62;
            *bank = 1;
            break;
        case 0xB3:
            *glyph = 70;
            *bank = 1;
            break;
        case 0xFC:
            *glyph = 72;
            *bank = 1;
            break;
        case 0xAD:
            *glyph = 73;
            *bank = 1;
            break;
        case 0x63:
            *glyph = 89;
            *bank = 1;
            break;
        case 0x9F:
            *glyph = 129;
            *bank = 1;
            break;
        case 0xDF:
            *glyph = 134;
            *bank = 1;
            break;
        case 0xA6:
            *glyph = 158;
            *bank = 1;
            break;
        case 0xEA:
            *glyph = 173;
            *bank = 1;
            break;
        case 0xE6:
            *glyph = 180;
            *bank = 1;
            break;
        case 0xBB:
            *glyph = 189;
            *bank = 1;
            break;
        case 0xC1:
            *glyph = 200;
            *bank = 1;
            break;
        case 0xB0:
            *glyph = 207;
            *bank = 1;
            break;
        case 0x4E:
            *glyph = 214;
            *bank = 1;
            break;
        case 0x86:
            *glyph = 221;
            *bank = 1;
            break;
        case 0x74:
            *glyph = 239;
            *bank = 1;
            break;
        case 0x7E:
            *glyph = 253;
            *bank = 1;
            break;
        case 0xB9:
            *glyph = 7;
            *bank = 2;
            break;
        case 0x46:
            *glyph = 19;
            *bank = 2;
            break;
        case 0x5A:
            *glyph = 24;
            *bank = 2;
            break;
        case 0x7D:
            *glyph = 27;
            *bank = 2;
            break;
        case 0x92:
            *glyph = 40;
            *bank = 2;
            break;
        case 0x96:
            *glyph = 43;
            *bank = 2;
            break;
        case 0x7B:
            *glyph = 66;
            *bank = 2;
            break;
        case 0xB6:
            *glyph = 88;
            *bank = 2;
            break;
        case 0xF3:
            *glyph = 99;
            *bank = 2;
            break;
        case 0x5D:
            *glyph = 108;
            *bank = 2;
            break;
        case 0xC8:
            *glyph = 126;
            *bank = 2;
            break;
        case 0xA3:
            *glyph = 153;
            *bank = 2;
            break;
        case 0x81:
            *glyph = 195;
            *bank = 2;
            break;
        case 0xEC:
            *glyph = 198;
            *bank = 2;
            break;
        case 0x91:
            *glyph = 203;
            *bank = 2;
            break;
        case 0x50:
            *glyph = 204;
            *bank = 2;
            break;
        case 0xF0:
            *glyph = 208;
            *bank = 2;
            break;
        case 0x8E:
            *glyph = 213;
            *bank = 2;
            break;
        case 0x70:
            *glyph = 214;
            *bank = 2;
            break;
        case 0xBF:
            *glyph = 220;
            *bank = 2;
            break;
        case 0xB5:
            *glyph = 235;
            *bank = 2;
            break;
        case 0x76:
            *glyph = 237;
            *bank = 2;
            break;
        case 0xF4:
            *glyph = 239;
            *bank = 2;
            break;
        case 0x40:
            *glyph = 254;
            *bank = 2;
            break;
        case 0x60:
            *glyph = 255;
            *bank = 2;
            break;
        case 0x83:
            *glyph = 5;
            *bank = 3;
            break;
        case 0x95:
            *glyph = 43;
            *bank = 3;
            break;
        case 0xEF:
            *glyph = 45;
            *bank = 3;
            break;
        case 0x4D:
            *glyph = 66;
            *bank = 3;
            break;
        case 0xBD:
            *glyph = 71;
            *bank = 3;
            break;
        case 0x90:
            *glyph = 99;
            *bank = 3;
            break;
        case 0x7A:
            *glyph = 123;
            *bank = 3;
            break;
        case 0x9B:
            *glyph = 131;
            *bank = 3;
            break;
        case 0xA5:
            *glyph = 158;
            *bank = 3;
            break;
        case 0x78:
            *glyph = 167;
            *bank = 3;
            break;
        case 0xE0:
            *glyph = 169;
            *bank = 3;
            break;
        case 0xC9:
            *glyph = 179;
            *bank = 3;
            break;
        case 0xCA:
            *glyph = 184;
            *bank = 3;
            break;
        case 0xCF:
            *glyph = 186;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x8C00:
        switch (code & 0xFF) {
        case 0x4E:
            *glyph = 6;
            *bank = 1;
            break;
        case 0xF5:
            *glyph = 11;
            *bank = 1;
            break;
        case 0xA9:
            *glyph = 12;
            *bank = 1;
            break;
        case 0x78:
            *glyph = 22;
            *bank = 1;
            break;
        case 0xAB:
            *glyph = 55;
            *bank = 1;
            break;
        case 0xBE:
            *glyph = 67;
            *bank = 1;
            break;
        case 0xAE:
            *glyph = 80;
            *bank = 1;
            break;
        case 0xB3:
            *glyph = 91;
            *bank = 1;
            break;
        case 0x76:
            *glyph = 116;
            *bank = 1;
            break;
        case 0x60:
            *glyph = 128;
            *bank = 1;
            break;
        case 0x9F:
            *glyph = 138;
            *bank = 1;
            break;
        case 0xFB:
            *glyph = 152;
            *bank = 1;
            break;
        case 0xC8:
            *glyph = 203;
            *bank = 1;
            break;
        case 0xC4:
            *glyph = 215;
            *bank = 1;
            break;
        case 0xBB:
            *glyph = 216;
            *bank = 1;
            break;
        case 0xA4:
            *glyph = 220;
            *bank = 1;
            break;
        case 0xC0:
            *glyph = 233;
            *bank = 1;
            break;
        case 0xB4:
            *glyph = 246;
            *bank = 1;
            break;
        case 0xB1:
            *glyph = 12;
            *bank = 2;
            break;
        case 0x69:
            *glyph = 33;
            *bank = 2;
            break;
        case 0x88:
            *glyph = 46;
            *bank = 2;
            break;
        case 0x59:
            *glyph = 49;
            *bank = 2;
            break;
        case 0xE4:
            *glyph = 60;
            *bank = 2;
            break;
        case 0x41:
            *glyph = 73;
            *bank = 2;
            break;
        case 0xE3:
            *glyph = 76;
            *bank = 2;
            break;
        case 0x8B:
            *glyph = 90;
            *bank = 2;
            break;
        case 0xFC:
            *glyph = 96;
            *bank = 2;
            break;
        case 0xDD:
            *glyph = 97;
            *bank = 2;
            break;
        case 0x57:
            *glyph = 106;
            *bank = 2;
            break;
        case 0xAF:
            *glyph = 111;
            *bank = 2;
            break;
        case 0x99:
            *glyph = 117;
            *bank = 2;
            break;
        case 0xB5:
            *glyph = 129;
            *bank = 2;
            break;
        case 0xB8:
            *glyph = 175;
            *bank = 2;
            break;
        case 0xE5:
            *glyph = 183;
            *bank = 2;
            break;
        case 0x8F:
            *glyph = 211;
            *bank = 2;
            break;
        case 0xB6:
            *glyph = 226;
            *bank = 2;
            break;
        case 0x8A:
            *glyph = 238;
            *bank = 2;
            break;
        case 0xC3:
            *glyph = 251;
            *bank = 2;
            break;
        case 0x79:
            *glyph = 9;
            *bank = 3;
            break;
        case 0xEB:
            *glyph = 19;
            *bank = 3;
            break;
        case 0x8C:
            *glyph = 31;
            *bank = 3;
            break;
        case 0x95:
            *glyph = 37;
            *bank = 3;
            break;
        case 0xF0:
            *glyph = 57;
            *bank = 3;
            break;
        case 0xCC:
            *glyph = 70;
            *bank = 3;
            break;
        case 0xF8:
            *glyph = 98;
            *bank = 3;
            break;
        case 0xEA:
            *glyph = 100;
            *bank = 3;
            break;
        case 0x82:
            *glyph = 122;
            *bank = 3;
            break;
        case 0xB9:
            *glyph = 171;
            *bank = 3;
            break;
        case 0x6E:
            *glyph = 172;
            *bank = 3;
            break;
        case 0x87:
            *glyph = 189;
            *bank = 3;
            break;
        case 0x5E:
            *glyph = 191;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x8D00:
        switch (code & 0xFF) {
        case 0x90:
            *glyph = 23;
            *bank = 1;
            break;
        case 0x73:
            *glyph = 31;
            *bank = 1;
            break;
        case 0xDF:
            *glyph = 46;
            *bank = 1;
            break;
        case 0x9E:
            *glyph = 127;
            *bank = 1;
            break;
        case 0xC5:
            *glyph = 133;
            *bank = 1;
            break;
        case 0xA2:
            *glyph = 143;
            *bank = 1;
            break;
        case 0x6C:
            *glyph = 157;
            *bank = 1;
            break;
        case 0xA1:
            *glyph = 164;
            *bank = 1;
            break;
        case 0xC4:
            *glyph = 187;
            *bank = 1;
            break;
        case 0xCB:
            *glyph = 228;
            *bank = 1;
            break;
        case 0xEC:
            *glyph = 230;
            *bank = 1;
            break;
        case 0x87:
            *glyph = 23;
            *bank = 2;
            break;
        case 0x8F:
            *glyph = 26;
            *bank = 2;
            break;
        case 0xD9:
            *glyph = 29;
            *bank = 2;
            break;
        case 0x91:
            *glyph = 38;
            *bank = 2;
            break;
        case 0x44:
            *glyph = 81;
            *bank = 2;
            break;
        case 0xA5:
            *glyph = 91;
            *bank = 2;
            break;
        case 0x72:
            *glyph = 134;
            *bank = 2;
            break;
        case 0x52:
            *glyph = 139;
            *bank = 2;
            break;
        case 0xB6:
            *glyph = 141;
            *bank = 2;
            break;
        case 0xC3:
            *glyph = 147;
            *bank = 2;
            break;
        case 0xCF:
            *glyph = 179;
            *bank = 2;
            break;
        case 0x58:
            *glyph = 202;
            *bank = 2;
            break;
        case 0x82:
            *glyph = 215;
            *bank = 2;
            break;
        case 0xDD:
            *glyph = 224;
            *bank = 2;
            break;
        case 0xD7:
            *glyph = 230;
            *bank = 2;
            break;
        case 0x48:
            *glyph = 231;
            *bank = 2;
            break;
        case 0x4C:
            *glyph = 243;
            *bank = 2;
            break;
        case 0xFB:
            *glyph = 250;
            *bank = 2;
            break;
        case 0x5C:
            *glyph = 15;
            *bank = 3;
            break;
        case 0x93:
            *glyph = 39;
            *bank = 3;
            break;
        case 0xBD:
            *glyph = 40;
            *bank = 3;
            break;
        case 0xAC:
            *glyph = 92;
            *bank = 3;
            break;
        case 0xDB:
            *glyph = 108;
            *bank = 3;
            break;
        case 0x55:
            *glyph = 121;
            *bank = 3;
            break;
        case 0xBB:
            *glyph = 128;
            *bank = 3;
            break;
        case 0xAA:
            *glyph = 185;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x8E00:
        switch (code & 0xFF) {
        case 0xB8:
            *glyph = 13;
            *bank = 1;
            break;
        case 0xA9:
            *glyph = 15;
            *bank = 1;
            break;
        case 0xD7:
            *glyph = 18;
            *bank = 1;
            break;
        case 0xD2:
            *glyph = 21;
            *bank = 1;
            break;
        case 0x9E:
            *glyph = 27;
            *bank = 1;
            break;
        case 0x76:
            *glyph = 28;
            *bank = 1;
            break;
        case 0x84:
            *glyph = 44;
            *bank = 1;
            break;
        case 0xA1:
            *glyph = 54;
            *bank = 1;
            break;
        case 0xA6:
            *glyph = 87;
            *bank = 1;
            break;
        case 0x71:
            *glyph = 102;
            *bank = 1;
            break;
        case 0xC0:
            *glyph = 111;
            *bank = 1;
            break;
        case 0x9F:
            *glyph = 155;
            *bank = 1;
            break;
        case 0x9D:
            *glyph = 156;
            *bank = 1;
            break;
        case 0x96:
            *glyph = 161;
            *bank = 1;
            break;
        case 0x8E:
            *glyph = 191;
            *bank = 1;
            break;
        case 0xE8:
            *glyph = 197;
            *bank = 1;
            break;
        case 0x6D:
            *glyph = 219;
            *bank = 1;
            break;
        case 0x70:
            *glyph = 232;
            *bank = 1;
            break;
        case 0xE6:
            *glyph = 241;
            *bank = 1;
            break;
        case 0xE3:
            *glyph = 249;
            *bank = 1;
            break;
        case 0x63:
            *glyph = 10;
            *bank = 2;
            break;
        case 0x64:
            *glyph = 22;
            *bank = 2;
            break;
        case 0xB6:
            *glyph = 28;
            *bank = 2;
            break;
        case 0xF1:
            *glyph = 31;
            *bank = 2;
            break;
        case 0x80:
            *glyph = 48;
            *bank = 2;
            break;
        case 0xE5:
            *glyph = 75;
            *bank = 2;
            break;
        case 0x4F:
            *glyph = 78;
            *bank = 2;
            break;
        case 0xD3:
            *glyph = 80;
            *bank = 2;
            break;
        case 0x67:
            *glyph = 86;
            *bank = 2;
            break;
        case 0x5A:
            *glyph = 87;
            *bank = 2;
            break;
        case 0xE7:
            *glyph = 102;
            *bank = 2;
            break;
        case 0xD8:
            *glyph = 112;
            *bank = 2;
            break;
        case 0x97:
            *glyph = 122;
            *bank = 2;
            break;
        case 0x8B:
            *glyph = 136;
            *bank = 2;
            break;
        case 0x51:
            *glyph = 151;
            *bank = 2;
            break;
        case 0x6E:
            *glyph = 166;
            *bank = 2;
            break;
        case 0x7E:
            *glyph = 169;
            *bank = 2;
            break;
        case 0xF3:
            *glyph = 194;
            *bank = 2;
            break;
        case 0xF4:
            *glyph = 199;
            *bank = 2;
            break;
        case 0x78:
            *glyph = 227;
            *bank = 2;
            break;
        case 0x55:
            *glyph = 242;
            *bank = 2;
            break;
        case 0xED:
            *glyph = 246;
            *bank = 2;
            break;
        case 0x40:
            *glyph = 16;
            *bank = 3;
            break;
        case 0x77:
            *glyph = 25;
            *bank = 3;
            break;
        case 0xCC:
            *glyph = 42;
            *bank = 3;
            break;
        case 0x91:
            *glyph = 50;
            *bank = 3;
            break;
        case 0xA8:
            *glyph = 81;
            *bank = 3;
            break;
        case 0xFB:
            *glyph = 124;
            *bank = 3;
            break;
        case 0xD4:
            *glyph = 125;
            *bank = 3;
            break;
        case 0x9A:
            *glyph = 140;
            *bank = 3;
            break;
        case 0xEA:
            *glyph = 146;
            *bank = 3;
            break;
        case 0x61:
            *glyph = 159;
            *bank = 3;
            break;
        case 0xCB:
            *glyph = 164;
            *bank = 3;
            break;
        case 0xBF:
            *glyph = 196;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x8F00:
        switch (code & 0xFF) {
        case 0x6F:
            *glyph = 29;
            *bank = 1;
            break;
        case 0xEA:
            *glyph = 32;
            *bank = 1;
            break;
        case 0x8A:
            *glyph = 33;
            *bank = 1;
            break;
        case 0x97:
            *glyph = 48;
            *bank = 1;
            break;
        case 0x95:
            *glyph = 68;
            *bank = 1;
            break;
        case 0xE3:
            *glyph = 183;
            *bank = 1;
            break;
        case 0xE4:
            *glyph = 185;
            *bank = 1;
            break;
        case 0x80:
            *glyph = 194;
            *bank = 1;
            break;
        case 0xD0:
            *glyph = 204;
            *bank = 1;
            break;
        case 0x50:
            *glyph = 217;
            *bank = 1;
            break;
        case 0xE7:
            *glyph = 224;
            *bank = 1;
            break;
        case 0x94:
            *glyph = 226;
            *bank = 1;
            break;
        case 0x64:
            *glyph = 236;
            *bank = 1;
            break;
        case 0xAD:
            *glyph = 21;
            *bank = 2;
            break;
        case 0x57:
            *glyph = 35;
            *bank = 2;
            break;
        case 0xD8:
            *glyph = 39;
            *bank = 2;
            break;
        case 0x9F:
            *glyph = 45;
            *bank = 2;
            break;
        case 0x89:
            *glyph = 63;
            *bank = 2;
            break;
        case 0x8F:
            *glyph = 70;
            *bank = 2;
            break;
        case 0x5D:
            *glyph = 83;
            *bank = 2;
            break;
        case 0xC1:
            *glyph = 142;
            *bank = 2;
            break;
        case 0xC4:
            *glyph = 144;
            *bank = 2;
            break;
        case 0x91:
            *glyph = 145;
            *bank = 2;
            break;
        case 0xE1:
            *glyph = 148;
            *bank = 2;
            break;
        case 0xF3:
            *glyph = 186;
            *bank = 2;
            break;
        case 0xE9:
            *glyph = 189;
            *bank = 2;
            break;
        case 0x49:
            *glyph = 190;
            *bank = 2;
            break;
        case 0xEE:
            *glyph = 191;
            *bank = 2;
            break;
        case 0xE6:
            *glyph = 196;
            *bank = 2;
            break;
        case 0x5B:
            *glyph = 206;
            *bank = 2;
            break;
        case 0x75:
            *glyph = 209;
            *bank = 2;
            break;
        case 0x68:
            *glyph = 225;
            *bank = 2;
            break;
        case 0xAC:
            *glyph = 229;
            *bank = 2;
            break;
        case 0x9D:
            *glyph = 233;
            *bank = 2;
            break;
        case 0x5A:
            *glyph = 0;
            *bank = 3;
            break;
        case 0xCE:
            *glyph = 2;
            *bank = 3;
            break;
        case 0x83:
            *glyph = 22;
            *bank = 3;
            break;
        case 0xF0:
            *glyph = 28;
            *bank = 3;
            break;
        case 0x70:
            *glyph = 84;
            *bank = 3;
            break;
        case 0xC6:
            *glyph = 130;
            *bank = 3;
            break;
        case 0x5C:
            *glyph = 139;
            *bank = 3;
            break;
        case 0xA2:
            *glyph = 165;
            *bank = 3;
            break;
        case 0xED:
            *glyph = 175;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x9000:
        switch (code & 0xFF) {
        case 0xD8:
            *glyph = 1;
            *bank = 1;
            break;
        case 0x53:
            *glyph = 3;
            *bank = 1;
            break;
        case 0x6C:
            *glyph = 43;
            *bank = 1;
            break;
        case 0xB0:
            *glyph = 65;
            *bank = 1;
            break;
        case 0xED:
            *glyph = 66;
            *bank = 1;
            break;
        case 0x5B:
            *glyph = 69;
            *bank = 1;
            break;
        case 0xA2:
            *glyph = 82;
            *bank = 1;
            break;
        case 0x51:
            *glyph = 94;
            *bank = 1;
            break;
        case 0xBA:
            *glyph = 97;
            *bank = 1;
            break;
        case 0xE0:
            *glyph = 112;
            *bank = 1;
            break;
        case 0x45:
            *glyph = 117;
            *bank = 1;
            break;
        case 0xB6:
            *glyph = 130;
            *bank = 1;
            break;
        case 0xB3:
            *glyph = 149;
            *bank = 1;
            break;
        case 0x4D:
            *glyph = 151;
            *bank = 1;
            break;
        case 0x48:
            *glyph = 169;
            *bank = 1;
            break;
        case 0xA8:
            *glyph = 175;
            *bank = 1;
            break;
        case 0xAC:
            *glyph = 184;
            *bank = 1;
            break;
        case 0x5E:
            *glyph = 231;
            *bank = 1;
            break;
        case 0x65:
            *glyph = 251;
            *bank = 1;
            break;
        case 0xE2:
            *glyph = 255;
            *bank = 1;
            break;
        case 0x56:
            *glyph = 4;
            *bank = 2;
            break;
        case 0x46:
            *glyph = 34;
            *bank = 2;
            break;
        case 0xD3:
            *glyph = 41;
            *bank = 2;
            break;
        case 0x67:
            *glyph = 44;
            *bank = 2;
            break;
        case 0xE6:
            *glyph = 68;
            *bank = 2;
            break;
        case 0x69:
            *glyph = 69;
            *bank = 2;
            break;
        case 0x62:
            *glyph = 71;
            *bank = 2;
            break;
        case 0x85:
            *glyph = 100;
            *bank = 2;
            break;
        case 0xB5:
            *glyph = 109;
            *bank = 2;
            break;
        case 0x94:
            *glyph = 173;
            *bank = 2;
            break;
        case 0x58:
            *glyph = 210;
            *bank = 2;
            break;
        case 0x84:
            *glyph = 20;
            *bank = 3;
            break;
        case 0xCC:
            *glyph = 21;
            *bank = 3;
            break;
        case 0x7D:
            *glyph = 23;
            *bank = 3;
            break;
        case 0xAF:
            *glyph = 35;
            *bank = 3;
            break;
        case 0xD4:
            *glyph = 49;
            *bank = 3;
            break;
        case 0xF5:
            *glyph = 73;
            *bank = 3;
            break;
        case 0x41:
            *glyph = 83;
            *bank = 3;
            break;
        case 0xC2:
            *glyph = 95;
            *bank = 3;
            break;
        case 0xB8:
            *glyph = 97;
            *bank = 3;
            break;
        case 0x5F:
            *glyph = 104;
            *bank = 3;
            break;
        case 0xC3:
            *glyph = 105;
            *bank = 3;
            break;
        case 0xAB:
            *glyph = 106;
            *bank = 3;
            break;
        case 0x44:
            *glyph = 109;
            *bank = 3;
            break;
        case 0xDA:
            *glyph = 127;
            *bank = 3;
            break;
        case 0x55:
            *glyph = 132;
            *bank = 3;
            break;
        case 0xA7:
            *glyph = 163;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x9100:
        switch (code & 0xFF) {
        case 0xE5:
            *glyph = 0;
            *bank = 1;
            break;
        case 0x7A:
            *glyph = 2;
            *bank = 1;
            break;
        case 0xDE:
            *glyph = 53;
            *bank = 1;
            break;
        case 0xD2:
            *glyph = 59;
            *bank = 1;
            break;
        case 0x52:
            *glyph = 64;
            *bank = 1;
            break;
        case 0xAB:
            *glyph = 90;
            *bank = 1;
            break;
        case 0xCC:
            *glyph = 135;
            *bank = 1;
            break;
        case 0x81:
            *glyph = 137;
            *bank = 1;
            break;
        case 0x7B:
            *glyph = 145;
            *bank = 1;
            break;
        case 0xA9:
            *glyph = 163;
            *bank = 1;
            break;
        case 0x9C:
            *glyph = 181;
            *bank = 1;
            break;
        case 0x8A:
            *glyph = 196;
            *bank = 1;
            break;
        case 0x66:
            *glyph = 201;
            *bank = 1;
            break;
        case 0xE8:
            *glyph = 212;
            *bank = 1;
            break;
        case 0x95:
            *glyph = 235;
            *bank = 1;
            break;
        case 0x4E:
            *glyph = 5;
            *bank = 2;
            break;
        case 0x4F:
            *glyph = 50;
            *bank = 2;
            break;
        case 0x9B:
            *glyph = 51;
            *bank = 2;
            break;
        case 0xA7:
            *glyph = 98;
            *bank = 2;
            break;
        case 0x84:
            *glyph = 103;
            *bank = 2;
            break;
        case 0xBD:
            *glyph = 107;
            *bank = 2;
            break;
        case 0xDD:
            *glyph = 113;
            *bank = 2;
            break;
        case 0xAE:
            *glyph = 115;
            *bank = 2;
            break;
        case 0x44:
            *glyph = 121;
            *bank = 2;
            break;
        case 0xAF:
            *glyph = 127;
            *bank = 2;
            break;
        case 0xCA:
            *glyph = 137;
            *bank = 2;
            break;
        case 0xBC:
            *glyph = 150;
            *bank = 2;
            break;
        case 0x88:
            *glyph = 154;
            *bank = 2;
            break;
        case 0x49:
            *glyph = 158;
            *bank = 2;
            break;
        case 0xC5:
            *glyph = 165;
            *bank = 2;
            break;
        case 0x67:
            *glyph = 170;
            *bank = 2;
            break;
        case 0x53:
            *glyph = 171;
            *bank = 2;
            break;
        case 0x5F:
            *glyph = 176;
            *bank = 2;
            break;
        case 0xD4:
            *glyph = 187;
            *bank = 2;
            break;
        case 0xCE:
            *glyph = 212;
            *bank = 2;
            break;
        case 0xB6:
            *glyph = 223;
            *bank = 2;
            break;
        case 0xB1:
            *glyph = 6;
            *bank = 3;
            break;
        case 0xA4:
            *glyph = 32;
            *bank = 3;
            break;
        case 0xE4:
            *glyph = 48;
            *bank = 3;
            break;
        case 0xE3:
            *glyph = 72;
            *bank = 3;
            break;
        case 0xB0:
            *glyph = 74;
            *bank = 3;
            break;
        case 0x97:
            *glyph = 86;
            *bank = 3;
            break;
        case 0x50:
            *glyph = 103;
            *bank = 3;
            break;
        case 0xBE:
            *glyph = 119;
            *bank = 3;
            break;
        case 0xF0:
            *glyph = 137;
            *bank = 3;
            break;
        case 0x77:
            *glyph = 149;
            *bank = 3;
            break;
        case 0x96:
            *glyph = 161;
            *bank = 3;
            break;
        case 0xAC:
            *glyph = 173;
            *bank = 3;
            break;
        case 0xE6:
            *glyph = 192;
            *bank = 3;
            break;
        case 0x9D:
            *glyph = 195;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x9200:
        switch (code & 0xFF) {
        case 0x86:
            *glyph = 10;
            *bank = 1;
            break;
        case 0x6D:
            *glyph = 14;
            *bank = 1;
            break;
        case 0x42:
            *glyph = 35;
            *bank = 1;
            break;
        case 0x40:
            *glyph = 39;
            *bank = 1;
            break;
        case 0x4E:
            *glyph = 40;
            *bank = 1;
            break;
        case 0x69:
            *glyph = 77;
            *bank = 1;
            break;
        case 0x6E:
            *glyph = 79;
            *bank = 1;
            break;
        case 0x8B:
            *glyph = 93;
            *bank = 1;
            break;
        case 0xB7:
            *glyph = 120;
            *bank = 1;
            break;
        case 0x54:
            *glyph = 122;
            *bank = 1;
            break;
        case 0xBC:
            *glyph = 132;
            *bank = 1;
            break;
        case 0x45:
            *glyph = 177;
            *bank = 1;
            break;
        case 0x75:
            *glyph = 178;
            *bank = 1;
            break;
        case 0xEA:
            *glyph = 206;
            *bank = 1;
            break;
        case 0xCA:
            *glyph = 222;
            *bank = 1;
            break;
        case 0x6B:
            *glyph = 225;
            *bank = 1;
            break;
        case 0xB2:
            *glyph = 245;
            *bank = 1;
            break;
        case 0xC9:
            *glyph = 254;
            *bank = 1;
            break;
        case 0xC7:
            *glyph = 6;
            *bank = 2;
            break;
        case 0x78:
            *glyph = 25;
            *bank = 2;
            break;
        case 0x50:
            *glyph = 85;
            *bank = 2;
            break;
        case 0x44:
            *glyph = 92;
            *bank = 2;
            break;
        case 0x8D:
            *glyph = 133;
            *bank = 2;
            break;
        case 0x87:
            *glyph = 135;
            *bank = 2;
            break;
        case 0xEF:
            *glyph = 138;
            *bank = 2;
            break;
        case 0x6C:
            *glyph = 219;
            *bank = 2;
            break;
        case 0x85:
            *glyph = 221;
            *bank = 2;
            break;
        case 0x6A:
            *glyph = 222;
            *bank = 2;
            break;
        case 0xF6:
            *glyph = 12;
            *bank = 3;
            break;
        case 0xBE:
            *glyph = 58;
            *bank = 3;
            break;
        case 0x66:
            *glyph = 69;
            *bank = 3;
            break;
        case 0x63:
            *glyph = 77;
            *bank = 3;
            break;
        case 0xA7:
            *glyph = 94;
            *bank = 3;
            break;
        case 0x5A:
            *glyph = 101;
            *bank = 3;
            break;
        case 0x8E:
            *glyph = 107;
            *bank = 3;
            break;
        case 0xE8:
            *glyph = 138;
            *bank = 3;
            break;
        case 0x65:
            *glyph = 153;
            *bank = 3;
            break;
        case 0xB4:
            *glyph = 157;
            *bank = 3;
            break;
        case 0xE1:
            *glyph = 178;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x9300:
        switch (code & 0xFF) {
        case 0x90:
            *glyph = 45;
            *bank = 1;
            break;
        case 0x9A:
            *glyph = 57;
            *bank = 1;
            break;
        case 0x96:
            *glyph = 63;
            *bank = 1;
            break;
        case 0xAE:
            *glyph = 100;
            *bank = 1;
            break;
        case 0x78:
            *glyph = 105;
            *bank = 1;
            break;
        case 0xFC:
            *glyph = 106;
            *bank = 1;
            break;
        case 0xC1:
            *glyph = 108;
            *bank = 1;
            break;
        case 0xE0:
            *glyph = 136;
            *bank = 1;
            break;
        case 0x7B:
            *glyph = 148;
            *bank = 1;
            break;
        case 0x60:
            *glyph = 150;
            *bank = 1;
            break;
        case 0xA6:
            *glyph = 168;
            *bank = 1;
            break;
        case 0x66:
            *glyph = 172;
            *bank = 1;
            break;
        case 0x47:
            *glyph = 202;
            *bank = 1;
            break;
        case 0x56:
            *glyph = 227;
            *bank = 1;
            break;
        case 0x6E:
            *glyph = 47;
            *bank = 2;
            break;
        case 0xAF:
            *glyph = 55;
            *bank = 2;
            break;
        case 0xAA:
            *glyph = 58;
            *bank = 2;
            break;
        case 0x61:
            *glyph = 67;
            *bank = 2;
            break;
        case 0xB4:
            *glyph = 72;
            *bank = 2;
            break;
        case 0xEF:
            *glyph = 82;
            *bank = 2;
            break;
        case 0xFA:
            *glyph = 131;
            *bank = 2;
            break;
        case 0xCB:
            *glyph = 159;
            *bank = 2;
            break;
        case 0xF1:
            *glyph = 168;
            *bank = 2;
            break;
        case 0x73:
            *glyph = 180;
            *bank = 2;
            break;
        case 0x7C:
            *glyph = 182;
            *bank = 2;
            break;
        case 0xC5:
            *glyph = 232;
            *bank = 2;
            break;
        case 0xCD:
            *glyph = 245;
            *bank = 2;
            break;
        case 0x49:
            *glyph = 252;
            *bank = 2;
            break;
        case 0x87:
            *glyph = 1;
            *bank = 3;
            break;
        case 0xB1:
            *glyph = 26;
            *bank = 3;
            break;
        case 0xB9:
            *glyph = 44;
            *bank = 3;
            break;
        case 0x5D:
            *glyph = 47;
            *bank = 3;
            break;
        case 0x54:
            *glyph = 61;
            *bank = 3;
            break;
        case 0x72:
            *glyph = 65;
            *bank = 3;
            break;
        case 0xE4:
            *glyph = 89;
            *bank = 3;
            break;
        case 0x79:
            *glyph = 90;
            *bank = 3;
            break;
        case 0xBE:
            *glyph = 93;
            *bank = 3;
            break;
        case 0xAC:
            *glyph = 126;
            *bank = 3;
            break;
        case 0xC7:
            *glyph = 134;
            *bank = 3;
            break;
        case 0x58:
            *glyph = 147;
            *bank = 3;
            break;
        case 0x8A:
            *glyph = 152;
            *bank = 3;
            break;
        case 0x64:
            *glyph = 170;
            *bank = 3;
            break;
        case 0x5F:
            *glyph = 190;
            *bank = 3;
            break;
        case 0xF7:
            *glyph = 197;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x9400:
        switch (code & 0xFF) {
        case 0xDE:
            *glyph = 41;
            *bank = 1;
            break;
        case 0xC6:
            *glyph = 42;
            *bank = 1;
            break;
        case 0x7A:
            *glyph = 144;
            *bank = 1;
            break;
        case 0xF5:
            *glyph = 195;
            *bank = 1;
            break;
        case 0x8E:
            *glyph = 218;
            *bank = 1;
            break;
        case 0x6A:
            *glyph = 223;
            *bank = 1;
            break;
        case 0xAD:
            *glyph = 229;
            *bank = 1;
            break;
        case 0xFC:
            *glyph = 240;
            *bank = 1;
            break;
        case 0x73:
            *glyph = 244;
            *bank = 1;
            break;
        case 0xDF:
            *glyph = 18;
            *bank = 2;
            break;
        case 0xBB:
            *glyph = 30;
            *bank = 2;
            break;
        case 0xF2:
            *glyph = 32;
            *bank = 2;
            break;
        case 0x92:
            *glyph = 36;
            *bank = 2;
            break;
        case 0xED:
            *glyph = 37;
            *bank = 2;
            break;
        case 0x43:
            *glyph = 42;
            *bank = 2;
            break;
        case 0x4F:
            *glyph = 52;
            *bank = 2;
            break;
        case 0x4C:
            *glyph = 53;
            *bank = 2;
            break;
        case 0x59:
            *glyph = 62;
            *bank = 2;
            break;
        case 0xB2:
            *glyph = 74;
            *bank = 2;
            break;
        case 0x97:
            *glyph = 114;
            *bank = 2;
            break;
        case 0x67:
            *glyph = 119;
            *bank = 2;
            break;
        case 0x46:
            *glyph = 160;
            *bank = 2;
            break;
        case 0xE9:
            *glyph = 205;
            *bank = 2;
            break;
        case 0x83:
            *glyph = 216;
            *bank = 2;
            break;
        case 0xE0:
            *glyph = 228;
            *bank = 2;
            break;
        case 0x5C:
            *glyph = 236;
            *bank = 2;
            break;
        case 0xD4:
            *glyph = 7;
            *bank = 3;
            break;
        case 0xBC:
            *glyph = 8;
            *bank = 3;
            break;
        case 0x96:
            *glyph = 10;
            *bank = 3;
            break;
        case 0xB1:
            *glyph = 11;
            *bank = 3;
            break;
        case 0xBD:
            *glyph = 24;
            *bank = 3;
            break;
        case 0x9B:
            *glyph = 41;
            *bank = 3;
            break;
        case 0x77:
            *glyph = 67;
            *bank = 3;
            break;
        case 0x9A:
            *glyph = 68;
            *bank = 3;
            break;
        case 0x4D:
            *glyph = 82;
            *bank = 3;
            break;
        case 0x4E:
            *glyph = 96;
            *bank = 3;
            break;
        case 0xF1:
            *glyph = 110;
            *bank = 3;
            break;
        case 0x7B:
            *glyph = 151;
            *bank = 3;
            break;
        case 0xA0:
            *glyph = 176;
            *bank = 3;
            break;
        case 0xE7:
            *glyph = 183;
            *bank = 3;
            break;
        case 0x65:
            *glyph = 193;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x9500:
        switch (code & 0xFF) {
        case 0xAA:
            *glyph = 16;
            *bank = 1;
            break;
        case 0x7C:
            *glyph = 37;
            *bank = 1;
            break;
        case 0x95:
            *glyph = 85;
            *bank = 1;
            break;
        case 0x73:
            *glyph = 88;
            *bank = 1;
            break;
        case 0xCF:
            *glyph = 92;
            *bank = 1;
            break;
        case 0xA8:
            *glyph = 96;
            *bank = 1;
            break;
        case 0xCA:
            *glyph = 109;
            *bank = 1;
            break;
        case 0xFB:
            *glyph = 110;
            *bank = 1;
            break;
        case 0x83:
            *glyph = 114;
            *bank = 1;
            break;
        case 0xB7:
            *glyph = 115;
            *bank = 1;
            break;
        case 0xA0:
            *glyph = 118;
            *bank = 1;
            break;
        case 0xC2:
            *glyph = 126;
            *bank = 1;
            break;
        case 0xE0:
            *glyph = 146;
            *bank = 1;
            break;
        case 0xF3:
            *glyph = 147;
            *bank = 1;
            break;
        case 0x40:
            *glyph = 165;
            *bank = 1;
            break;
        case 0xBD:
            *glyph = 171;
            *bank = 1;
            break;
        case 0x76:
            *glyph = 186;
            *bank = 1;
            break;
        case 0xF8:
            *glyph = 213;
            *bank = 1;
            break;
        case 0xD4:
            *glyph = 248;
            *bank = 1;
            break;
        case 0x69:
            *glyph = 2;
            *bank = 2;
            break;
        case 0x4B:
            *glyph = 16;
            *bank = 2;
            break;
        case 0xB5:
            *glyph = 56;
            *bank = 2;
            break;
        case 0xFA:
            *glyph = 110;
            *bank = 2;
            break;
        case 0x9A:
            *glyph = 116;
            *bank = 2;
            break;
        case 0x94:
            *glyph = 123;
            *bank = 2;
            break;
        case 0x89:
            *glyph = 157;
            *bank = 2;
            break;
        case 0xA1:
            *glyph = 172;
            *bank = 2;
            break;
        case 0xD6:
            *glyph = 234;
            *bank = 2;
            break;
        case 0x60:
            *glyph = 4;
            *bank = 3;
            break;
        case 0xF1:
            *glyph = 27;
            *bank = 3;
            break;
        case 0x82:
            *glyph = 38;
            *bank = 3;
            break;
        case 0xD0:
            *glyph = 59;
            *bank = 3;
            break;
        case 0x97:
            *glyph = 62;
            *bank = 3;
            break;
        case 0x90:
            *glyph = 75;
            *bank = 3;
            break;
        case 0x9C:
            *glyph = 87;
            *bank = 3;
            break;
        case 0xBA:
            *glyph = 111;
            *bank = 3;
            break;
        case 0x5C:
            *glyph = 116;
            *bank = 3;
            break;
        case 0x58:
            *glyph = 155;
            *bank = 3;
            break;
        case 0xB6:
            *glyph = 160;
            *bank = 3;
            break;
        case 0xD2:
            *glyph = 194;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x9600:
        switch (code & 0xFF) {
        case 0x59:
            *glyph = 5;
            *bank = 1;
            break;
        case 0x82:
            *glyph = 19;
            *bank = 1;
            break;
        case 0xB0:
            *glyph = 24;
            *bank = 1;
            break;
        case 0x6C:
            *glyph = 36;
            *bank = 1;
            break;
        case 0xBD:
            *glyph = 51;
            *bank = 1;
            break;
        case 0x7B:
            *glyph = 71;
            *bank = 1;
            break;
        case 0xBE:
            *glyph = 113;
            *bank = 1;
            break;
        case 0x40:
            *glyph = 125;
            *bank = 1;
            break;
        case 0x9E:
            *glyph = 131;
            *bank = 1;
            break;
        case 0xD9:
            *glyph = 142;
            *bank = 1;
            break;
        case 0xF1:
            *glyph = 162;
            *bank = 1;
            break;
        case 0x5C:
            *glyph = 170;
            *bank = 1;
            break;
        case 0xB3:
            *glyph = 176;
            *bank = 1;
            break;
        case 0xA1:
            *glyph = 190;
            *bank = 1;
            break;
        case 0xBC:
            *glyph = 193;
            *bank = 1;
            break;
        case 0xB2:
            *glyph = 209;
            *bank = 1;
            break;
        case 0xE2:
            *glyph = 211;
            *bank = 1;
            break;
        case 0xDF:
            *glyph = 242;
            *bank = 1;
            break;
        case 0xF2:
            *glyph = 243;
            *bank = 1;
            break;
        case 0x5D:
            *glyph = 0;
            *bank = 2;
            break;
        case 0xAD:
            *glyph = 14;
            *bank = 2;
            break;
        case 0xDA:
            *glyph = 79;
            *bank = 2;
            break;
        case 0xCA:
            *glyph = 94;
            *bank = 2;
            break;
        case 0xC0:
            *glyph = 125;
            *bank = 2;
            break;
        case 0x88:
            *glyph = 130;
            *bank = 2;
            break;
        case 0xEC:
            *glyph = 161;
            *bank = 2;
            break;
        case 0xBB:
            *glyph = 163;
            *bank = 2;
            break;
        case 0x96:
            *glyph = 167;
            *bank = 2;
            break;
        case 0x57:
            *glyph = 174;
            *bank = 2;
            break;
        case 0x9C:
            *glyph = 185;
            *bank = 2;
            break;
        case 0xC2:
            *glyph = 197;
            *bank = 2;
            break;
        case 0xF0:
            *glyph = 217;
            *bank = 2;
            break;
        case 0xA7:
            *glyph = 253;
            *bank = 2;
            break;
        case 0xF3:
            *glyph = 18;
            *bank = 3;
            break;
        case 0xA2:
            *glyph = 29;
            *bank = 3;
            break;
        case 0x4B:
            *glyph = 33;
            *bank = 3;
            break;
        case 0xE9:
            *glyph = 36;
            *bank = 3;
            break;
        case 0x64:
            *glyph = 52;
            *bank = 3;
            break;
        case 0xC5:
            *glyph = 53;
            *bank = 3;
            break;
        case 0xBA:
            *glyph = 54;
            *bank = 3;
            break;
        case 0x60:
            *glyph = 91;
            *bank = 3;
            break;
        case 0xD8:
            *glyph = 117;
            *bank = 3;
            break;
        case 0xFB:
            *glyph = 120;
            *bank = 3;
            break;
        case 0x87:
            *glyph = 143;
            *bank = 3;
            break;
        case 0x68:
            *glyph = 199;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x9700:
        switch (code & 0xFF) {
        case 0xE1:
            *glyph = 7;
            *bank = 1;
            break;
        case 0x45:
            *glyph = 20;
            *bank = 1;
            break;
        case 0x46:
            *glyph = 34;
            *bank = 1;
            break;
        case 0x6C:
            *glyph = 50;
            *bank = 1;
            break;
        case 0xDF:
            *glyph = 52;
            *bank = 1;
            break;
        case 0x88:
            *glyph = 56;
            *bank = 1;
            break;
        case 0x70:
            *glyph = 60;
            *bank = 1;
            break;
        case 0x79:
            *glyph = 78;
            *bank = 1;
            break;
        case 0xC7:
            *glyph = 99;
            *bank = 1;
            break;
        case 0x9D:
            *glyph = 140;
            *bank = 1;
            break;
        case 0x52:
            *glyph = 141;
            *bank = 1;
            break;
        case 0x44:
            *glyph = 154;
            *bank = 1;
            break;
        case 0xCD:
            *glyph = 159;
            *bank = 1;
            break;
        case 0x5C:
            *glyph = 166;
            *bank = 1;
            break;
        case 0xA3:
            *glyph = 174;
            *bank = 1;
            break;
        case 0x98:
            *glyph = 192;
            *bank = 1;
            break;
        case 0x76:
            *glyph = 237;
            *bank = 1;
            break;
        case 0x8A:
            *glyph = 11;
            *bank = 2;
            break;
        case 0x74:
            *glyph = 77;
            *bank = 2;
            break;
        case 0x8E:
            *glyph = 93;
            *bank = 2;
            break;
        case 0xA7:
            *glyph = 95;
            *bank = 2;
            break;
        case 0x68:
            *glyph = 118;
            *bank = 2;
            break;
        case 0xE7:
            *glyph = 128;
            *bank = 2;
            break;
        case 0x56:
            *glyph = 132;
            *bank = 2;
            break;
        case 0x59:
            *glyph = 156;
            *bank = 2;
            break;
        case 0x90:
            *glyph = 181;
            *bank = 2;
            break;
        case 0xE2:
            *glyph = 193;
            *bank = 2;
            break;
        case 0x4C:
            *glyph = 241;
            *bank = 2;
            break;
        case 0xDE:
            *glyph = 247;
            *bank = 2;
            break;
        case 0xB7:
            *glyph = 249;
            *bank = 2;
            break;
        case 0x63:
            *glyph = 17;
            *bank = 3;
            break;
        case 0xA0:
            *glyph = 30;
            *bank = 3;
            break;
        case 0xAC:
            *glyph = 34;
            *bank = 3;
            break;
        case 0x83:
            *glyph = 60;
            *bank = 3;
            break;
        case 0x5E:
            *glyph = 64;
            *bank = 3;
            break;
        case 0xBC:
            *glyph = 79;
            *bank = 3;
            break;
        case 0x7A:
            *glyph = 112;
            *bank = 3;
            break;
        case 0x64:
            *glyph = 115;
            *bank = 3;
            break;
        case 0xB9:
            *glyph = 144;
            *bank = 3;
            break;
        case 0x8B:
            *glyph = 156;
            *bank = 3;
            break;
        case 0xAA:
            *glyph = 174;
            *bank = 3;
            break;
        case 0xCA:
            *glyph = 180;
            *bank = 3;
            break;
        case 0xA6:
            *glyph = 182;
            *bank = 3;
            break;
        case 0x6E:
            *glyph = 198;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x9800:
        switch (code & 0xFF) {
        case 0x41:
            *glyph = 58;
            *bank = 1;
            break;
        case 0x62:
            *glyph = 119;
            *bank = 1;
            break;
        case 0x5E:
            *glyph = 234;
            *bank = 1;
            break;
        case 0x63:
            *glyph = 238;
            *bank = 1;
            break;
        case 0x59:
            *glyph = 162;
            *bank = 2;
            break;
        case 0x66:
            *glyph = 188;
            *bank = 2;
            break;
        case 0x72:
            *glyph = 133;
            *bank = 3;
            break;
        case 0x48:
            *glyph = 141;
            *bank = 3;
            break;
        case 0x42:
            *glyph = 168;
            *bank = 3;
            break;
        case 0x61:
            *glyph = 177;
            *bank = 3;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    case 0x9C00:
        switch (code & 0xFF) {
        case 0xC9:
            *glyph = 210;
            *bank = 1;
            break;
        default:
            *glyph = 0;
            *bank = 0;
            break;
        }

        break;
    default:
        *glyph = 0;
        *bank = 0;
        break;
    }
}

void SplitFourDigits(s16 value, u8* out) {
    s16 acc = 0;
    s16 div;
    s16 i;

    if (value >= 0) {
        div = 1000;

        for (i = 0; i < 4; i++) {
            u8* q = &out[i];
            *q = value / div - acc;
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

u8 LayoutCardMsgGlyphsPage(s32 x, s32 y, MsgLatinChar* text, MsgLatinChar** nextText) {
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

    while (*text != 0) {
        s32 v;

        sCardMsgGlyphSprites[sTextEntryCount].x = x + cx;
        sCardMsgGlyphSprites[sTextEntryCount].y = y + cy;
        sCardMsgGlyphSprites[sTextEntryCount].visible = 1;

        if (*text == MSG_LATIN_CODE(0x4079, 29)) {
            f = 1;
            text++;
        }

        if (*text == MSG_LATIN_CODE(0x4000, 30)) {
            f = 0;
            text++;
        }

        if (*text == MSG_LATIN_CODE(10, 31)) {
            cx = 0;
            cy += 0xC00;
        } else {
#ifdef VERSION_EU
            v = *text;
#else
            if ((u16)(*text - 32) <= 223) {
                v = *text;
            } else {
                switch (*text) {
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

        text++;

        if (cy > 0x1800) {
            *nextText = text;
            return sTextEntryCount;
        }
    }

    *nextText = NULL;
    return sTextEntryCount;
}

#ifndef VERSION_EU
u8 LayoutCardMsgGlyphsPageSjis(s32 x, s32 y, u8* text, u8** nextText) {
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

    while (*text != 0) {
        u16 v;
        w = 0;
        sCardMsgGlyphSprites[sTextEntryCount].x = x + cx;
        sCardMsgGlyphSprites[sTextEntryCount].y = y + cy;
        sCardMsgGlyphSprites[sTextEntryCount].visible = 1;
        sCardMsgGlyphSprites[sTextEntryCount].useAlternatePalette = 0;

        if (*(u16*)text == 0x6E6E) {
            cx = 0;
            cy += 0xC00;
            text += 2;
        } else {
            v = *(u16*)text;
            v = (v / 256) | (v << 8);
            text += 2;

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
            if (*text != 0) {
                v = *(u16*)text;

                if ((u16)((v / 256) | (v << 8)) == 0x8142) {
                    *nextText = NULL;
                } else {
                    *nextText = text;
                    return sTextEntryCount;
                }
            } else {
                *nextText = NULL;
            }
        }
    }

    *nextText = NULL;
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

void DrawMsgGlyphsWithPalette(u8 n, void* palette) {
    u8 i;

    for (i = 0; i < n; i++) {
        TextGlyphSprite* b = sMsgGlyphSprites;

        if (b[i].visible == 1) {
            s32 x = b[i].x;
            s32 y = b[i].y;

            if (b[i].tiles != NULL) {
                if (!b[i].useAlternatePalette) {
                    DrawSpriteUnsorted(x >> 8, y >> 8, MSG_FONT_FRAMES[0], b[i].tiles, palette, 0);
                } else {
                    DrawSpriteUnsorted(x >> 8, y >> 8, MSG_FONT_FRAMES[0], b[i].tiles,
                                  b[i].alternatePalette, 0);
                }
            }
        }
    }
}

u16 FormatSmallFontHex16(s16 value, u16* out) {
    u8 buf[8];
    u8* p;
    s32 i;

    buf[0] = (value & 0xF000) >> 12;
    buf[1] = (value & 0x0F00) >> 8;
    buf[2] = (value & 0x00F0) >> 4;
    buf[3] = value & 0xF;
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
s32 CopySjisGlyphsToVram(const TextChar* str) {
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

    while (*str != 0) {
        u16 v;
        buf[0] = str[0];
        buf[1] = str[1];
        c = (u16*)buf;

        if (*c == 0x6E6E) {
            str += 2;
        } else {
            v = *c;
            v = (v / 256) | (v << 8);
            str += 2;

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
s32 CopySjisGlyphsToVramAt(const TextChar* str, u16 tile) {
    u8 buf[2];
    u16* c;
    u16 w;
    u8 t;
    u8* dst;
    u8 n;
    w = 0;
    dst = (u8*)(OBJ_VRAM0 + 512 * TILE_SIZE_4BPP) + tile * 32;
    t = 0;
    n = 0;

    while (*str != 0) {
        u16 v;
        buf[0] = str[0];
        buf[1] = str[1];
        c = (u16*)buf;

        if (*c == 0x6E6E) {
            str += 2;
        } else {
            v = *c;
            v = (v / 256) | (v << 8);
            str += 2;

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

u8 CopyLatinGlyphsToVram(const TextChar* str, u16* widths, u16 tile) {
    u8* dst = (u8*)(OBJ_VRAM0 + 512 * TILE_SIZE_4BPP) + tile * 32;
    s32 flag = 0;
    sTextEntryCount = 0;
    *widths = 0;

    while (*str != 0) {
        s32 v = 0;

#ifdef VERSION_EU
        if (*str == 31) {
#else
        if (*str == 10) {
#endif
            *widths = 0;
        } else {
#ifdef VERSION_EU
            v = *str;
#else
#ifdef VERSION_JP
            if (*str > 31) {
#else
            if ((u16)(*str - 32) <= 223) {
#endif
                v = *str;
            } else {
                switch (*str) {
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
                *widths = sLatinGlyphWidths.widths[v];
                v = ((u16*)gMsgLatinFontFrames[v])[3];
                CpuCopy16(&gMsgLatinFontTiles[v * 32], dst, 0x80);
                dst += 128;
                sTextEntryCount++;
                widths++;
                flag = 1;
            } else if (flag) {
                widths[-1] += 3;
            }
        }

        str++;
    }

    return sTextEntryCount;
}
