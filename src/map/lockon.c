#include "registration_data.h"
#include "map_api.h"
#include "mode.h"
#include "m4a_song.h"
#include "mode_test.h"
#include "gba/keys.h"
#include "mode_test_api.h"
#include "sprites_mode_test.h"
#include "debug_font.h"
#include "malloc.h"

u8* gDebugTextTileDest;
u8 gDebugTextPaletteBank;
DebugTextLine* gDebugTextLines;
u8 gDebugTextLineCount;
u8 gUnk_02034A21;
s32 gUnk_02034A24;
s32 gUnk_02034A28;
void* gUnk_02034A2C;

void task_lockon_0(LockonWork* w) {
    s32 i;

    gLockonDoorPosition = EwramAlloc(12);
    w->tiles = AllocObjTiles(0x80, 0);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 0x20);
    SetObjTileSource(w->tiles, gUnk_090D7C84);
    AnimInit(&w->anim, gUnk_09EEC66C, gUnk_09EEC660);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);

    for (i = 0; i < 8; i++) {
        w->targets[i] = 0;
    }

    w->targetCount = 0;
    w->selected = -1;
    w->timer = 0;
    w->unk_30 = 0;
    w->unk_4C = 0;
}

u8 task_lockon_1(LockonWork* w) {
    FldObj* o;
    s8 count;
    s8 i;
    s8 nsel;
    s8 list[8];
    s32 px;
    s32 py;
    s32 dx;
    s32 dy;
    s32 ox;
    s32 oy;

    i = 0;
    o = ListPoolFirst(&gFieldState->actor.pool);

    if (gFieldState->flags & FIELD_FLAG_NO_LOCKON) {
        gFieldState->lockonTarget = 0;
        return 1;
    }

    LockonClearTargets(w);

    if (w->prevSelected != w->selected) {
        w->unk_30 = 0;
    }

    px = gFieldState->actor.fieldPosition.x;
    py = gFieldState->actor.fieldPosition.y;
    count = 0;

    if ((gFieldState->flags & FIELD_FLAG_HOLD_LOCKON) == 0) {
        while (o != NULL) {
            ox = o->fieldPosition.x;
            oy = o->fieldPosition.y;
            dx = px - ox;
            dy = py - oy;

            if (VectorLength2D(dx, dy) <= 0x3000 && (dx > -0x8000 && dx < 0x8000) && (dy > -0x8000 && dy < 0x8000) && o->fieldPosition.ground == gFieldState->actor.fieldPosition.ground) {
                if (o->kind == 3) {
                    gLockonDoorPosition[0] = o->fieldPosition.x;
                    gLockonDoorPosition[1] = o->fieldPosition.y;
                    gLockonDoorPosition[2] = o->fieldPosition.z;
                    w->targets[count++] = o;
                    w->targetCount++;
                } else {
                    w->targets[count++] = o;
                    w->targetCount++;
                }
            }

            if (count > 6) {
                break;
            }

            o = ListPoolNext(&o->node);
        }

        if (w->targetCount != 0) {
            nsel = 0;

            for (i = 0; i < w->targetCount; i++) {
                if (LockonIsInFront(gFieldState->actor.angle, px, py, w->targets[i])) {
                    w->selected = i;
                    list[nsel++] = i;
                }
            }

            if (nsel > 1) {
                w->selected = LockonPickNearest(px, py, w, nsel, list);
            }
        }
    }

    if (w->selected >= 0) {
        gFieldState->lockonTarget = w->targets[w->selected];
    } else {
        gFieldState->lockonTarget = 0;
        w->unk_30 = 0;
    }

    w->prevSelected = w->selected;
    w->gfx = AnimUpdate(&w->anim);
    return 1;
}

#define CLAMP_LABEL(v, edge, limit, dest) \
    do { \
        if ((edge) > (limit)) { \
            (v) = (dest); \
        } \
    } while (0)

void task_lockon_2(LockonWork* w) {
    FldObj* obj;
    s32 x;
    s32 y;
    union {
        s32 coord;
        u8 counter;
    } x2, y2;

    if (gFieldState->flags & FIELD_FLAG_ROOM_CREATE) {
        return;
    }

    obj = w->targets[w->selected];

    if (obj->kind == 2) {
        return;
    }

    x = (obj->fieldPosition.x >> 8) - (gFieldState->x >> 8);
    x2.coord = x + 12;
    y = (obj->fieldPosition.y >> 8) + (obj->fieldPosition.z >> 8) - (gFieldState->y >> 8) - obj->height;
    y2.coord = y - 8;

    CLAMP_LABEL(x2.coord, x + 60, 240, 192);
    CLAMP_LABEL(y2.coord, y, 160, 152);

    x2.counter = w->timer++;
    y2.counter = x2.counter;
    if (y2.counter > 10) {
        w->timer = 0;
    }

    if (gFieldState->lockonTarget == NULL) {
        return;
    }

    if (w->selected < 0) {
        return;
    }

#ifdef VERSION_EU
    {
        FldObj* obj = w->targets[w->selected];
        s32 projectedY = (obj->fieldPosition.y >> 8) + (obj->fieldPosition.z >> 8) - (gFieldState->y >> 8);

        DrawSprite((obj->fieldPosition.x >> 8) - (gFieldState->x >> 8), projectedY - obj->height + 40, w->gfx, w->tiles, w->palette, 0, 0x400, (u16)(-0x100E - (((s16)projectedY >> 8) << 2)));
    }
#else
    obj = w->targets[w->selected];
    DrawSprite((obj->fieldPosition.x >> 8) - (gFieldState->x >> 8), (obj->fieldPosition.y >> 8) + (obj->fieldPosition.z >> 8) - (gFieldState->y >> 8) - obj->height + 40, w->gfx, w->tiles, w->palette, 0, 0, (u16)(-0x100E - ((w->targets[w->selected]->fieldPosition.y >> 8) << 2)));
#endif
}

#undef CLAMP_LABEL

void task_lockon_3(LockonWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    gFieldState->lockonTarget = 0;
    EwramFree(gLockonDoorPosition);
    gLockonDoorPosition = 0;
}

s32 VectorLength2D(s32 a, s32 b) {
    return (u16)Sqrt(a * a + b * b);
}

s32 NormalizeVector2D8(s32* x, s32* y) {
    s32 d = VectorLength2D(*x, *y);

    if (d > 0) {
        *x = (*x << 8) / d;
        *y = (*y << 8) / d;
    }

    return d;
}

s8 LockonPickNearest(s32 a, s32 b, LockonWork* w, s8 n, s8* list) {
    s8 i;
    s8 best;
    s32 bestDist;
    FldObj* o;
    s32 dist;
    s32 dx;
    s32 dy;

    best = -1;
    bestDist = 0x10000;

    for (i = 0; i < n; i++) {
        o = w->targets[list[i]];

        if (o != NULL) {
            dx = o->fieldPosition.x;
            dy = o->fieldPosition.y;
            dist = VectorLength2D(dx - a, dy - b);

            if (bestDist > dist) {
                bestDist = dist;
                best = i;
            }
        }
    }

    if (best != -1) {
        return list[best];
    }

    return best;
}

void LockonClearTargets(LockonWork* w) {
    s8 i;

    if ((gFieldState->flags & FIELD_FLAG_HOLD_LOCKON) == 0) {
        w->selected = -1;

        for (i = 0; i < 8; i++) {
            w->targets[i] = 0;
        }

        w->targetCount = 0;
    }
}

u8 LockonIsInFront(u16 a, s32 b, s32 c, FldObj* d) {
    s32 x;
    s32 y;
    s32 sn;
    s32 cs;
    s32 dot;

    if (d != NULL) {
        x = d->fieldPosition.x - b;
        y = d->fieldPosition.y - c;
        sn = gSineTable[a & 0xFF];
        cs = -gSineTable[(a & 0xFF) + 0x40];
        NormalizeVector2D8(&x, &y);
        dot = (sn * x >> 8) + (y * cs >> 8);

        if (d->kind == 3) {
            if (dot > 99) {
                return 1;
            }
        } else {
            if (dot > 19) {
                return 1;
            }
        }
    }

    return 0;
}

void func_0805F728(s32* x, s32* y) {
    if (gLockonDoorPosition != NULL) {
        *x = (gLockonDoorPosition[0] >> 8) - (gFieldState->x >> 8);
        *y = (gLockonDoorPosition[1] >> 8) + (gLockonDoorPosition[2] >> 8) - (gFieldState->y >> 8) - 24;
    } else {
        *x = 0;
        *y = 0;
    }
}

void DebugTextClearBg(void) {
    s32 a;
    s32 b;
    void* charBase = GetBgCharBase(0);
    void* screenBase = GetBgScreenBase(0);

    a = 0;
    CpuFastSet(&a, charBase, 0x01001500);
    b = 0;
    CpuFastSet(&b, screenBase, 0x01000140);
}

void func_0805F7B0(s32 a) {
    gUnk_02034A24 = a;
}

void func_0805F7BC(void) {
    DebugTextClearBg();
}

void func_0805F7C8(u8 a) {
    gUnk_02034A2C = (u8*)GetBgCharBase(0) + (a << 12);
}

void DebugTextPrintFont2(u8 x, u8 y, u16* s) {
    u8 i;
    u16 c;

    for (i = 0; i <= 59 && (u8)*s != 0; i++, s++) {
        c = *s;
        c = (u8)(c >> 8) | (c << 8);

        switch (c & 0xFF00) {
        case 0x8100:
            gDebugTextLines[gDebugTextLineCount].glyphs[i] = c + 0x7EC0;
            break;
        case 0x8200:
            gDebugTextLines[gDebugTextLineCount].glyphs[i] = (c + 0x7DC0) | 0x400;
            break;
        }
    }

    gDebugTextLines[gDebugTextLineCount].x = x;
    gDebugTextLines[gDebugTextLineCount].y = y;
    gDebugTextLines[gDebugTextLineCount].length = i;
    gDebugTextLineCount++;
}

u8 func_0805F8F0(u8 a) {
    return a * 4 % 32;
}

void DebugTextClearLines(void) {
    u8 i;
    u8 j;

    for (i = 0; i <= 19; i++) {
        for (j = 0; j <= 60; j++) {
            gDebugTextLines[i].glyphs[j] = 0;
        }
    }
}

s32 func_0805F93C(u8 bg, u8 b, u8 c, u8 d, u8 e) {
    u8 i;
    u8 j;
    u8 r;
    u8 k;
    u16 col;
    u8* p;
    u32* dst;
    u32* src;
    u32 t;
    u32 ko;
    u32 ko4;
    u32 co;
    s32 n;

    j = 0;
    gDebugTextTileDest = (u8*)GetBgCharBase(bg) + c * 0x400 + (b + 1) * 32;
    b = ((b + d) >> 3) + 1;
    n = (s8)d + b;
    d = n;
    e += (c + e) >> 3;
    k = c & 7;
    col = (c >> 3) << 3;

    for (; j < e; j++) {
        for (i = 0; i < d; i++) {
            ko = k * 4;
            co = col * 4;
            ko4 = ko + 4;
            p = gDebugTextTileDest + i * 32 + j * 1024;
            dst = (u32*)(p + ko + co);
            src = (u32*)(p + ko4 + co);

            for (r = 0; r < 9; r++) {
                t = ((u32)dst & 0xFF) + 4;

                if (t == ((t >> 5) << 5)) {
                    *dst++ = *(u32*)((u8*)src + 0x3E0);
                    dst += 248;
                    src += 249;
                } else {
                    *dst++ = *src++;
                }
            }
        }

        k++;

        if (k == 8) {
            col += 0x100;
            k = 0;
        }
    }

    return 1;
}

void DebugTextLoadPalette(s32 a, void* b, s32 c, u8 d) {
    if (b != NULL) {
        LoadPalette(b, (void*)(d * 32 + 0x05000000), 32);
    }

    gDebugTextPaletteBank = d;
}

void DebugTextInit(u8 bg, u16 b, u16 c) {
    s32 fillA;
    s32 fillB;
    u8 i;
    u8 j;
    void* charBase = GetBgCharBase(bg);
    void* screenBase = GetBgScreenBase(bg);

    fillA = 0;
    CpuSet(&fillA, charBase, (b >> 2) | CPU_SET_32BIT | CPU_SET_SRC_FIXED);
    fillB = 0;
    CpuSet(&fillB, screenBase, (c >> 2) | CPU_SET_32BIT | CPU_SET_SRC_FIXED);

    gDebugTextLines = EwramAlloc(sizeof(DebugTextLine) * 20);
    gDebugTextLineCount = 0;

    for (i = 0; i <= 19; i++) {
        for (j = 0; j <= 60; j++) {
            gDebugTextLines[i].glyphs[j] = 0;
        }

        gDebugTextLines[i].x = 0;
        gDebugTextLines[i].y = 0;
        gDebugTextLines[i].unk_7C = 0;
        gDebugTextLines[i].length = 0;
    }

    func_0805F7B0(0);
    gUnk_02034A21 = 0;
    gDebugTextPaletteBank = 0;
    EnableBg(bg);
}

void func_0805FB78(s32 a) {
    gUnk_02034A28 = a;
}

void func_0805FB84(u8 x, u8 y, u32 c, u8 v) {
    u8 buf[8];

    buf[3] = v / 10;
    buf[5] = v - buf[3] * 10;
    buf[0] = 0x82;
    buf[1] = 0x98;
    buf[2] = 0x82;
    buf[3] += 0x4F;
    buf[4] = 0x82;
    buf[5] += 0x4F;
    buf[6] = 0;
    DebugTextPrint(x, y, c, buf);
}

void DebugTextPrintNumber(u8 x, u8 y, u32 c, u16 v) {
    u8 buf[8];

    buf[1] = v / 100;
    buf[3] = v / 10 - buf[1] * 10;
    buf[5] = v - (buf[1] * 100 + buf[3] * 10);
    buf[0] = 0x82;
    buf[1] += 0x4F;
    buf[2] = 0x82;
    buf[3] += 0x4F;
    buf[4] = 0x82;
    buf[5] += 0x4F;
    buf[6] = 0;
    DebugTextPrint(x, y, c, buf);
}

void DebugTextPrint(u8 x, u8 y, u32 c, const char* s) {
    u8 i = 0;
    s32 shift = 0;
    u16 character;

    switch (c) {
    case 0:
        shift = 1;
        break;
    case 1:
        shift = 0;
        break;
    case 2:
        gDebugTextLines[gDebugTextLineCount].font = c;
        DebugTextPrintFont2(x, y, (u16*)s);
        return;
    }
    if (gDebugTextLineCount > 19) {
        return;
    }
    while (*s != 0) {
        character = *(const u16*)s;
        character = (character >> 8) | (character << 8);
        switch (character & 0xFF00) {
        case 0x8100:
            if (character > 0x8146) {
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = character - 0x8146 + (0x42 >> shift);
            }
            switch (character) {
            case 0x8140:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 0;
                break;
            case 0x815E:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 1;
                break;
            case 0x815B:
            case 0x815C:
            case 0x815D:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 2;
                break;
            case 0x8151:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 3;
                break;
            case 0x8144:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 4;
                break;
            case 0x817B:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 5;
                break;
            case 0x8149:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 6;
                break;
            case 0x8148:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 7;
                break;
            case 0x8194:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 8;
                break;
            case 0x8193:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 9;
                break;
            case 0x818D:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 10;
                break;
            case 0x818B:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 11;
                break;
            case 0x8196:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 12;
                break;
            case 0x8168:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 13;
                break;
            case 0x8190:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 14;
                break;
            case 0x8195:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 15;
                break;
            case 0x8166:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 16;
                break;
            case 0x8169:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 17;
                break;
            case 0x816A:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 18;
                break;
            case 0x8181:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 19;
                break;
            case 0x8160:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 20;
                break;
            case 0x8162:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 21;
                break;
            case 0x8197:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 22;
                break;
            case 0x8165:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 23;
                break;
            case 0x8175:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 24;
                break;
            case 0x8176:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 25;
                break;
            case 0x816F:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 26;
                break;
            case 0x8170:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 27;
                break;
            case 0x8141:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 28;
                break;
            case 0x8142:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 29;
                break;
            case 0x8183:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 30;
                break;
            case 0x8184:
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = 31;
                break;
            }
            break;
        case 0x8200:
            if ((u16)(character - 0x824F) <= 9) {
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = character - 0x824F + (0x80 >> shift);
            }
            if ((u16)(character - 0x8260) <= 25) {
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = character - 0x8260 + (0xC0 >> shift);
            }
            if ((u16)(character - 0x8281) <= 25) {
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = character - 0x8281 + (0x100 >> shift);
            }
            if ((u16)(character - 0x829F) <= 31) {
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = character - 0x829F + (0x140 >> shift);
            }
            if ((u16)(character - 0x82BF) <= 31) {
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = character - 0x82BF + (0x180 >> shift);
            }
            if ((u16)(character - 0x82DF) <= 31) {
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = character - 0x82DF + (0x1C0 >> shift);
            }
            break;
        case 0x8300:
            if ((u16)(character - 0x8340) <= 31) {
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = character - 0x8340 + ((0x200 - shift * 192) >> shift);
            }
            if ((u16)(character - 0x8360) <= 30) {
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = character - 0x8360 + ((0x240 - shift * 192) >> shift);
            }
            if (character == 0x8380) {
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = ((0x25F - shift * 192) >> shift);
            }
            if ((u16)(character - 0x8381) <= 21) {
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = character - 0x8381 + ((0x280 - shift * 192) >> shift);
            }
            if ((u16)(character - 0x83BF) <= 1) {
                gDebugTextLines[gDebugTextLineCount].glyphs[i] = character - 0x83BF + (0x40 >> shift);
            }
            break;
        }
        i++;
        s += 2;
        if (i > 59) {
            break;
        }
    }
    gDebugTextLines[gDebugTextLineCount].x = x;
    gDebugTextLines[gDebugTextLineCount].y = y;
    gDebugTextLines[gDebugTextLineCount].length = i;
    gDebugTextLines[gDebugTextLineCount].font = c;
    gDebugTextLineCount++;
}
void func_08060470(u8 bg) {
    u8 n;
    u8 i;
    u8 k;
    u8 x;
    u8 y;
    u16* screen;
    u32* tiles;
    u32* src;

    screen = GetBgScreenBase(bg);

    for (n = 0; n < gDebugTextLineCount; n++) {
        tiles = (u32*)((u8*)GetBgCharBase(bg) + (n * 0x1000 + 0x2000));
        x = gDebugTextLines[n].x;
        y = gDebugTextLines[n].y;

        for (i = 0; i < gDebugTextLines[n].length; i++) {
            src = (u32*)&gUnk_0941DD38[gDebugTextLines[n].glyphs[i] * 32];

            for (k = 0; k < 8; k++) {
                tiles[k] = src[0];
                tiles[k + 0x100] = src[0x100];
                src++;
            }

            *(screen + x + i + (y << 5)) = (i + 0x100 + n * 128) | 0x1000;
            *(screen + x + i + ((y + 1) << 5)) = (i + 0x120 + n * 128) | 0x1000;
            tiles += 8;
        }
    }
}

void DebugTextClear(void) {
    gDebugTextLineCount = 0;
}

void DebugTextDraw(u8 bg) {
    void* charBase;
    u32 v;
    u32 mapRow;
    u8* screen;
    u8* font = 0;
    u8 n;
    u8 tileX;
    u8 tileY;
    u8 offsetX;
    u8 offsetY;
    s32 height = 0;
    u8* destination;
    u8 i;
    u8 row;
    u8 sourceRow;

    charBase = GetBgCharBase(bg);
    gDebugTextTileDest = charBase;
    screen = GetBgScreenBase(bg);
    for (n = 0; n < gDebugTextLineCount; n++) {
        tileX = gDebugTextLines[n].x >> 3;
        tileY = gDebugTextLines[n].y >> 3;
        offsetX = gDebugTextLines[n].x - tileX * 8;
        offsetY = gDebugTextLines[n].y - tileY * 8;
        gDebugTextTileDest = (u8*)GetBgCharBase(bg) + (tileX + 1 + tileY * 32) * 32;
        for (i = 0; i < gDebugTextLines[n].length; i++) {
            destination = gDebugTextTileDest + i * 32;
            switch (gDebugTextLines[n].font) {
            case 0:
                font = gUnk_0941BEB8 + gDebugTextLines[n].glyphs[i] * 32;
                height = 8;
                break;
            case 1:
                font = gUnk_0941DD38 + gDebugTextLines[n].glyphs[i] * 32;
                height = 10;
                break;
            case 2:
                font = gDebugFont2Banks[gDebugTextLines[n].glyphs[i] >> 10];
                height = 8;
                break;
            }
            for (row = offsetY, sourceRow = 0; row < offsetY + height; row++, sourceRow++) {
                if (offsetX == 0) {
                    if (gDebugTextLines[n].font != 2) {
                        ((CharTile*)(destination + (row & 7) * 4 + (row >> 3) * 0x400))->rows[0] = *(u32*)(font + (sourceRow & 7) * 4 + (sourceRow >> 3) * 0x400);
                    } else {
                        ((CharTile*)(destination + (row & 7) * 4 + (row >> 3) * 0x400))->rows[0] = *(u32*)(font + (sourceRow & 7) * 4 + (gDebugTextLines[n].glyphs[i] & 0x3FF) * 32);
                    }
                } else if (i != 0 || gUnk_02034A28 == 1) {
                    v = ((CharTile*)(destination + (row & 7) * 4 + (row >> 3) * 0x400))->rows[0];

                    if (gDebugTextLines[n].font != 2) {
                        ((CharTile*)(destination + (row & 7) * 4 + (row >> 3) * 0x400))->rows[0] = v | *(u32*)(font + (sourceRow & 7) * 4 + (sourceRow >> 3) * 0x400) << (offsetX * 4);
                        ((CharTile*)(destination + (row & 7) * 4 + (row >> 3) * 0x400))[1].rows[0] = *(u32*)(font + (sourceRow & 7) * 4 + (sourceRow >> 3) * 0x400) >> (32 - offsetX * 4);
                    } else {
                        ((CharTile*)(destination + (row & 7) * 4 + (row >> 3) * 0x400))->rows[0] = v | *(u32*)(font + (sourceRow & 7) * 4 + (gDebugTextLines[n].glyphs[i] & 0x3FF) * 32) << (offsetX * 4);
                        ((CharTile*)(destination + (row & 7) * 4 + (row >> 3) * 0x400))[1].rows[0] = *(u32*)(font + (sourceRow & 7) * 4 + (gDebugTextLines[n].glyphs[i] & 0x3FF) * 32) >> (32 - offsetX * 4);
                    }
                } else {
                    if (gDebugTextLines[n].font != 2) {
                        ((CharTile*)(destination + (row & 7) * 4 + (row >> 3) * 0x400))->rows[0] = *(u32*)(font + (sourceRow & 7) * 4 + (sourceRow >> 3) * 0x400) << (offsetX * 4);
                        ((CharTile*)(destination + (row & 7) * 4 + (row >> 3) * 0x400))[1].rows[0] = *(u32*)(font + (sourceRow & 7) * 4 + (sourceRow >> 3) * 0x400) >> (32 - offsetX * 4);
                    } else {
                        ((CharTile*)(destination + (row & 7) * 4 + (row >> 3) * 0x400))->rows[0] = *(u32*)(font + (sourceRow & 7) * 4 + (gDebugTextLines[n].glyphs[i] & 0x3FF) * 32) << (offsetX * 4);
                        ((CharTile*)(destination + (row & 7) * 4 + (row >> 3) * 0x400))[1].rows[0] = *(u32*)(font + (sourceRow & 7) * 4 + (gDebugTextLines[n].glyphs[i] & 0x3FF) * 32) >> (32 - offsetX * 4);
                    }
                }

                mapRow = (tileY + (u8)(row >> 3)) * 32;
                *(u16*)(screen + tileX * 2 + i * 2 + mapRow * 2) = (tileX + 1 + i + mapRow) | (gDebugTextPaletteBank << 12);
                *(u16*)(screen + tileX * 2 + i * 2 + mapRow * 2 + 2) = (tileX + 2 + i + mapRow) | (gDebugTextPaletteBank << 12);
            }
        }
    }

    DebugTextClearLines();
}

void DebugTextFree(void) {
    EwramFree(gDebugTextLines);
}

void DebugTextDestroy(void) {
    DebugTextFree();
}

u16 GetCardCpCost(u16 a) {
    s32 n;
    u16 v;
    CardStat* stat;

    if (a & 0x8000) {
        return gCardDefs[a & 0x0FFF].cpCost;
    }

    if ((a & 0x0FFF) <= 0x1C1) {
        stat = (CardStat*)&gCardDefs[a & 0x0FFF].kind;
        n = stat->value;

        if (n == 0) {
            n = 10;
        }

        n--;
        v = stat->cpCost;
        v += (v / 10) * n;
        return v;
    }

    return gCardDefs[a & 0x0FFF].cpCost;
}

u16 GetCardMooglePointValue(u16 a) {
    u16 v;

    if ((a & 0x8000) == 0) {
        v = GetCardCpCost(a) / 5 * 2;
    } else {
        v = GetCardCpCost(a & 0x0FFF) / 5 * 2 + 10;
    }

    return v;
}

TaskDesc gTaskDescLockon = {
    "task_lockon",
    (TaskInitFunc)task_lockon_0,
    (TaskUpdateFunc)task_lockon_1,
    (TaskDrawFunc)task_lockon_2,
    (TaskDestroyFunc)task_lockon_3,
    sizeof(LockonWork),
};

u8* gDebugFont2Banks[2] = { gUnk_08F6E190, gUnk_08F6F190 };
u8* gUnk_09EE26F4 = gWhiteStarText;
u8* gUnk_09EE26F8 = gBlackStarText;
u8* gUnk_09EE26FC = gWhiteCircleText;
u8* gUnk_09EE2700 = gBlackCircleText;
