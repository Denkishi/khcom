/**
 * card_name.c
 * Card Name, Premium Effect and Print Layer
 */

#include "msg_localized_data.h"
#include "system_state.h"
#include "text.h"
#include "monsgage.h"
#include "fade.h"
#include "obj_api.h"
#include "display.h"
#include "engine_math.h"
#include "anim.h"
#include "obj.h"
#include "text_types.h"
#include "taskpool.h"
#include "malloc.h"
#include "card.h"
#include "sprites_card.h"
#include "premium_card_effect.h"
#include "card_types.h"
#include "types.h"
#include <stddef.h>
#include "card_name.h"
#include "ui_text.h"
#include "default_bg_map.h"
#include "sprite_palettes.h"

static PrintLine* sPrintLines;

static u8 sPrintLineCount;

static u8 sPrintBg;


#include "premium_message.inc"
#include "lockon.h"
void CardName_0(CardNameWork* work) {
    PremireChanceCardWork* q = gCardListWork->selectedCard;
    ObjPalette* pal;
    s32 v;
    s16 t;

    InitTextSlots(work->textSlots, 32);
    InitTextSlots(work->textSlots2, 32);
#ifdef VERSION_EU
    InitTextSlots(work->textSlots3, 32);
#else
    InitTextSlots(work->textSlots3, 2);
#endif
    work->textPalette = LoadTextPalette(1);
#ifdef VERSION_EU
    work->textSlotCount = LoadTextSlots(GetLocalizedString(q->cardDef->name), work->textSlots);
    work->textSlotCount2 = LoadTextSlots((u16*)gBecamePremiumCardText.strings[gLanguage], work->textSlots2);
#else
    work->textSlotCount = LoadTextSlots(q->cardDef->name, work->textSlots);
#ifdef VERSION_JP
    work->textSlotCount3 = LoadTextSlots((u16*)gUnkJp_09009748, work->textSlots3);
    work->textSlotCount2 = LoadTextSlots((u16*)gUnkJp_0900974C, work->textSlots2);
#else
    work->textSlotCount2 = LoadTextSlots(gUnk_090362A4, work->textSlots2);
#endif
#endif
#ifndef VERSION_JP
    work->palette = LoadObjPalette(gUnk_09614798, 32);
#endif

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
    case LANGUAGE_GERMAN:
    case LANGUAGE_ITALIAN:
        work->textSlotCount3 = 0;
        v = (230 - GetTextSlotsWidth(work->textSlots, work->textSlotCount)) / 2;
        work->nameX = v;
        t = (u16)work->nameX + GetTextSlotsWidth(work->textSlots, work->textSlotCount);
        work->suffixX = t;
        v = (240 - GetTextSlotsWidth(work->textSlots2, work->textSlotCount2)) / 2;
        work->messageX = v;
        break;
    case LANGUAGE_FRENCH:
        work->textSlotCount3 = LoadTextSlots((u16*)gUnkEu_090CF648, work->textSlots3);
        v = (230 - GetTextSlotsWidth(work->textSlots, work->textSlotCount)) / 2;
        work->nameX = v;
        t = (u16)work->nameX + GetTextSlotsWidth(work->textSlots, work->textSlotCount);
        work->suffixX = t;
        v = (240 - GetTextSlotsWidth(work->textSlots2, work->textSlotCount2)) / 2;
        work->messageX = v;
        break;
    case LANGUAGE_SPANISH:
        work->textSlotCount3 = LoadTextSlots((u16*)gUnkEu_090CF64D, work->textSlots3);
        v = (230 - GetTextSlotsWidth(work->textSlots, work->textSlotCount)) / 2;
        work->nameX = v;
        work->suffixX = v - 3;
        v = (240 - GetTextSlotsWidth(work->textSlots2, work->textSlotCount2)) / 2;
        work->messageX = v;
        break;
    default:
        work->textSlotCount3 = 0;
        break;
    }
#else
    v = (230 - GetTextSlotsWidth(work->textSlots, work->textSlotCount)) / 2;
    work->nameX = v;
    t = (u16)work->nameX + GetTextSlotsWidth(work->textSlots, work->textSlotCount);
    work->suffixX = t;
    v = (240 - GetTextSlotsWidth(work->textSlots2, work->textSlotCount2)) / 2;
    work->messageX = v;
#endif
    work->tiles = LoadObjTiles(gUnk_093F98AC, 0x1800);
    pal = LoadObjPalette(gCard00Palette, 32);
    work->palette2 = pal;
    FadeSetPaletteExcluded(pal->index + 16, 1);
    FadeSetPaletteExcluded(work->textPalette->index + 16, 1);
}

s32 CardName_1() {
    return 1;
}

void CardName_2(CardNameWork* work) {
    void** p = &gUnk_09EF1278[2];

    DrawSprite(120, 126, *p, work->tiles, work->palette2, NULL, 0, 50);
#ifdef VERSION_JP
    DrawTextSlots(work->nameX, 115, work->textSlots, work->textPalette, 30, work->textSlotCount);
#else
    DrawTextSlots(work->nameX, 115, work->textSlots, work->palette, 30, work->textSlotCount);
#endif
#ifndef VERSION_US
    DrawTextSlots(work->suffixX, 115, work->textSlots3, work->textPalette, 30, work->textSlotCount3);
#endif
    DrawTextSlots(work->messageX, 130, work->textSlots2, work->textPalette, 30, work->textSlotCount2);
}

void CardName_3(CardNameWork* work) {
    FreeTextSlots(work->textSlots, 32);
    FreeTextSlots(work->textSlots2, 32);
#ifdef VERSION_EU
    FreeTextSlots(work->textSlots3, 32);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->textPalette);
    ReleaseObjPalette(work->palette2);
    ReleaseObjPalette(work->palette);
#else
    FreeTextSlots(work->textSlots3, 2);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->textPalette);
    ReleaseObjPalette(work->palette2);
#ifndef VERSION_JP
    ReleaseObjPalette(work->palette);
#endif
#endif
}

void PremireEffectInit(PremiumCardEffectWork* work, s16* a) {
    work->tiles = AllocObjTiles(128, NULL);
    work->palette = LoadObjPalette(gUnk_09619158, 32);
    SetObjTileSource(work->tiles, gUnk_093F762E);
    AnimInit(&work->anim, gUnk_09EF1260, gUnk_09EF1230);
    AnimStart(&work->anim, GetRandom() % 3, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    work->centerX = a[1] << 8;
    work->centerY = a[2] << 8;
    work->fallY = 0;
    work->radius = a[0] << 8;
    work->angle = a[3];
    work->speed = GetRandom() % 0x181 + 0x100;
    work->x = 0;
    work->y = 0;
    work->unk_38 = 0;
    work->fallSpeed = -(GetRandom() % 0x81 + 0x200);
    gCardListWork->effectCount++;
}

void PremireEffectConvergeInit(PremiumCardEffectWork* work, s16* a) {
    work->tiles = AllocObjTiles(128, NULL);
    work->palette = LoadObjPalette(gUnk_09619158, 32);
    SetObjTileSource(work->tiles, gUnk_093F762E);
    AnimInit(&work->anim, gUnk_09EF1260, gUnk_09EF1230);
    AnimStart(&work->anim, GetRandom() % 3, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    work->centerX = a[1] << 8;
    work->centerY = a[2] << 8;
    work->fallY = 0;
    work->radius = a[0] << 8;
    work->angle = a[3];
    work->speed = GetRandom() % 0x81 + 0x200;
    work->x = 0;
    work->y = 0;
    work->unk_38 = 0;
    work->fallSpeed = -(GetRandom() % 0x81 + 0x200);
    PremireEffectSetOrbitPos(work);
    gCardListWork->effectCount++;
}

s32 PremireEffectSpiralUpdate(PremiumCardEffectWork* work) {
    PremireEffectSetOrbitPos(work);
    work->angle += 8;

    if (work->radius > 0) {
        work->radius += -0x180;
        work->gfx = AnimUpdate(&work->anim);
        return 1;
    }

    return 0;
}

s32 Premire_EFFECT2_1(PremiumCardEffectWork* work) {
    PremireEffectMoveFalling(work);
    work->gfx = AnimUpdate(&work->anim);

    if (work->y > 0xB400) {
        return 0;
    }

    return 1;
}

s32 PremireEffectConvergeUpdate(PremiumCardEffectWork* work) {
    PremireEffectMoveToCenter(work);
    work->angle += 8;
    work->gfx = AnimUpdate(&work->anim);

    if (work->radius <= 0x800) {
        return 0;
    }

    return 1;
}

void PremireEffectDraw(PremiumCardEffectWork* work) {
    DrawSprite(work->x >> 8, work->y >> 8, work->gfx, work->tiles, work->palette, NULL, 0, 0);
}

void PremireEffectDestroy(PremiumCardEffectWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    gCardListWork->effectCount--;
}

void PremireEffectSetOrbitPos(PremiumCardEffectWork* work) {
    work->x = SIN(work->angle) * (work->radius >> 8) + work->centerX;
    work->y = -COS(work->angle) * (work->radius >> 8) + work->centerY;
}

void PremireEffectMoveFalling(PremiumCardEffectWork* work) {
    work->fallSpeed += 30;
    work->fallY += work->fallSpeed;
    work->centerX += SIN(work->angle) * (work->speed >> 8);
    work->centerY += -COS(work->angle) * (work->speed >> 8);
    work->x = work->centerX;
    work->y = work->centerY + work->fallY;
}

void PremireEffectMoveToCenter(PremiumCardEffectWork* work) {
    s32 v;
    s32 d;

    work->vx = work->centerX - work->x;
    work->vy = work->centerY - work->y;
    work->radius = NormalizeVector2D8(&work->vx, &work->vy);
    v = work->speed;
    d = v >> 8;
    work->x += work->vx * d;
    work->y += work->vy * d;

    if (work->radius > 0) {
        work->speed = v - 2;
    }
}

void InitPrintLayer(u8 bg) {
    PrintLine** p;

    SetBgScroll(bg, 0, 0);
    SetBackdropColor(0, 0, 0);
    LoadBgTiles(bg, gUnk_09036380, 0x1C00);
    LoadBgMap(bg, gUnk_08125E24, 0x800);
    LoadBgPalette(bg, gUnk_09036300, 0x80);
    EnableBg(bg);
    sPrintBg = bg;
    p = &sPrintLines;
    *p = EwramAlloc(sizeof(PrintLine) * 32);
}

void FreePrintLayer() {
    EwramFree(sPrintLines);
}

u8 GetStringLength(const u8* p) {
    u8 n;

    n = 0;

    if (p == NULL) {
        return 0;
    }

    while (*p++ != 0) {
        if (*p != 0) {
            n++;
        }
    }

    return n + 1;
}

void PrintString(u8 a, u8 b, u8 c, const u8* s) {
    u8 n;
    u8 i;

    if (sPrintLineCount < 32) {
        n = GetStringLength(s);

        if (n > 32) {
            n = 32;
        }

        for (i = 0; i < n; i++) {
            sPrintLines[sPrintLineCount].tilemap[i] = s[i];
            sPrintLines[sPrintLineCount].tilemap[i] |= c << 12;
        }

        sPrintLines[sPrintLineCount].x = a;
        sPrintLines[sPrintLineCount].y = b;
        sPrintLines[sPrintLineCount].palette = c;
        sPrintLines[sPrintLineCount].length = n;
        RequestTilemapRectCopy(sPrintLines[sPrintLineCount].tilemap, GetBgScreenBase(sPrintBg), 0, 0,
                      sPrintLines[sPrintLineCount].x,
                      sPrintLines[sPrintLineCount].y,
                      sPrintLines[sPrintLineCount].length, 1);
        sPrintLineCount++;
    }
}

void ResetPrintLines() {
    sPrintLineCount = 0;
}

void ClearPrintLines() {
    s16 i;

    for (i = 0; i < sPrintLineCount; i++) {
        sPrintLines[i].length = 0;
        sPrintLines[i].x = 0;
        sPrintLines[i].y = 0;
        sPrintLines[i].palette = 0;
        sPrintLines[i].tilemap[0] = 0;
    }

    sPrintLineCount = 0;
}

void PrintNumber(u16 x, u16 y, u16 color, s32 value) {
    s32 digits[8];
    u8 text[10];
    s32 i;

    if (value >= 0) {
        digits[0] = value / 10000000;
        digits[1] = value / 1000000 - 10 * digits[0];
        digits[2] = value / 100000 - 100 * digits[0] - 10 * digits[1];
        digits[3] = value / 10000 - 1000 * digits[0] - 100 * digits[1] - 10 * digits[2];
        digits[4] = value / 1000 - 10000 * digits[0] - 1000 * digits[1] - 100 * digits[2] - 10 * digits[3];
        digits[5] = value / 100 - 100000 * digits[0] - 10000 * digits[1] - 1000 * digits[2] - 100 * digits[3] - 10 * digits[4];
        digits[6] = value / 10 - 1000000 * digits[0] - 100000 * digits[1] - 10000 * digits[2] - 1000 * digits[3] - 100 * digits[4] - 10 * digits[5];
        digits[7] = value - (10000000 * digits[0] + 1000000 * digits[1] + 100000 * digits[2] + 10000 * digits[3] + 1000 * digits[4] + 100 * digits[5] + 10 * digits[6]);
        text[0] = digits[0] + '0';
        text[1] = digits[1] + '0';
        text[2] = digits[2] + '0';
        text[3] = digits[3] + '0';
        text[4] = digits[4] + '0';
        text[5] = digits[5] + '0';
        text[6] = digits[6] + '0';
        text[7] = digits[7] + '0';
        text[8] = 0;
        i = 0;

        if (text[i] <= '0') {
            do {
                i++;

                if (i > 6) {
                    break;
                }
            } while (text[i] <= '0');
        }

        PrintString(x, y, color, &text[i]);
    } else {
        digits[0] = value / -10000000;
        digits[1] = value / -1000000 - 10 * digits[0];
        digits[2] = value / -100000 - 100 * digits[0] - 10 * digits[1];
        digits[3] = value / -10000 - 1000 * digits[0] - 100 * digits[1] - 10 * digits[2];
        digits[4] = value / -1000 - 10000 * digits[0] - 1000 * digits[1] - 100 * digits[2] - 10 * digits[3];
        digits[5] = value / -100 - 100000 * digits[0] - 10000 * digits[1] - 1000 * digits[2] - 100 * digits[3] - 10 * digits[4];
        digits[6] = value / -10 - 1000000 * digits[0] - 100000 * digits[1] - 10000 * digits[2] - 1000 * digits[3] - 100 * digits[4] - 10 * digits[5];
        digits[7] = -value - (10000000 * digits[0] + 1000000 * digits[1] + 100000 * digits[2] + 10000 * digits[3] + 1000 * digits[4] + 100 * digits[5] + 10 * digits[6]);
        text[0] = '-';
        text[1] = digits[0] + '0';
        text[2] = digits[1] + '0';
        text[3] = digits[2] + '0';
        text[4] = digits[3] + '0';
        text[5] = digits[4] + '0';
        text[6] = digits[5] + '0';
        text[7] = digits[6] + '0';
        text[8] = digits[7] + '0';
        text[9] = 0;
        i = 1;

        if (text[i] <= '0') {
            do {
                i++;

                if (i > 7) {
                    break;
                }
            } while (text[i] <= '0');
        }

        text[--i] = '-';
        PrintString(x, y, color, &text[i]);
    }
}

void PrintBinary16(u16 a, u16 b, u16 c, u16 bits) {
    u16 v[16];
    u8 s[17];
    u16 i;
    u16 j;

    for (i = 0, j = 15; i < 16; i++, j--) {
        v[i] = bits & (1 << i);
        s[j] = (v[i] >> i) + '0';
    }

    s[16] = 0;
    PrintString(a, b, c, s);
}

void PrintHex32(u16 a, u16 b, u16 c, u32 v) {
    u8 s[11];
    s32 i;

    s[0] = '0';
    s[1] = 'x';
    s[2] = v >> 28;
    s[3] = (v & 0x0F000000) >> 24;
    s[4] = (v & 0x00F00000) >> 20;
    s[5] = (v & 0x000F0000) >> 16;
    s[6] = (v & 0x0000F000) >> 12;
    s[7] = (v & 0x00000F00) >> 8;
    s[8] = (v & 0x000000F0) >> 4;
    s[9] = v & 0x0000000F;

    for (i = 0; i < 8; i++) {
        s[i + 2] += s[i + 2] <= 9 ? '0' : '7';
    }

    s[10] = 0;
    PrintString(a, b, c, s);
}

TaskDesc gTaskDescCardName = {
    "CardName",
    (TaskInitFunc)CardName_0,
    (TaskUpdateFunc)CardName_1,
    (TaskDrawFunc)CardName_2,
    (TaskDestroyFunc)CardName_3,
    sizeof(CardNameWork),
};

TaskDesc gTaskDescPremireEFFECTSpiral = {
    "Premire_EFFECT",
    (TaskInitFunc)PremireEffectInit,
    (TaskUpdateFunc)PremireEffectSpiralUpdate,
    (TaskDrawFunc)PremireEffectDraw,
    (TaskDestroyFunc)PremireEffectDestroy,
    sizeof(PremiumCardEffectWork),
};

TaskDesc gTaskDescPremireEFFECT2 = {
    "Premire_EFFECT2",
    (TaskInitFunc)PremireEffectInit,
    (TaskUpdateFunc)Premire_EFFECT2_1,
    (TaskDrawFunc)PremireEffectDraw,
    (TaskDestroyFunc)PremireEffectDestroy,
    sizeof(PremiumCardEffectWork),
};

TaskDesc gTaskDescPremireEFFECTConverge = {
    "Premire_EFFECT",
    (TaskInitFunc)PremireEffectConvergeInit,
    (TaskUpdateFunc)PremireEffectConvergeUpdate,
    (TaskDrawFunc)PremireEffectDraw,
    (TaskDestroyFunc)PremireEffectDestroy,
    sizeof(PremiumCardEffectWork),
};
