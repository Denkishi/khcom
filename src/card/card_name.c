#include "card_localized_data.h"
#include "msg_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "msg_api.h"
#include "card_battle.h"
#include "mode_test_api.h"
#include "m4a_song.h"
#include "game_state.h"
#include "text.h"
#include "monsgage.h"
#include "fade.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "display.h"
#include "engine_math.h"
#include "listpool.h"
#include "anim.h"
#include "obj.h"
#include "text_types.h"
#include "taskpool.h"
#include "key.h"
#include "malloc.h"
#include "card.h"
#include "card_message_assets.h"
#include "game.h"
#include "bos4_api.h"
#include "sprites_card.h"
#include "premium_card_effect.h"

PrintLine* gPrintLines;

u8 gPrintLineCount;

u8 gPrintBg;

u8 gUnk_02034ADA[6];

void PremireEffectSetOrbitPos(PremiumCardEffectWork* w);
void PremireEffectMoveToCenter(PremiumCardEffectWork* w);
void PremireEffectMoveFalling(PremiumCardEffectWork* w);

#include "premium_message.inc"
void CardName_0(CardNameWork* w) {
    PremireChanceCardWork* q = gCardListWork->selectedCard;
    ObjPalette* pal;
    s32 v;
    s16 t;

    InitTextSlots(w->textSlots, 32);
    InitTextSlots(w->textSlots2, 32);
#ifdef VERSION_EU
    InitTextSlots(w->textSlots3, 32);
#else
    InitTextSlots(w->textSlots3, 2);
#endif
    w->textPalette = LoadTextPalette(1);
#ifdef VERSION_EU
    w->textSlotCount = LoadTextSlots(eu_0805E924(q->cardDef->name), w->textSlots);
    w->textSlotCount2 = LoadTextSlots((u16*)gUnkEu_09F6602C.strings[gLanguage], w->textSlots2);
#else
    w->textSlotCount = LoadTextSlots(q->cardDef->name, w->textSlots);
#ifdef VERSION_JP
    w->textSlotCount3 = LoadTextSlots((u16*)gUnkJp_09009748, w->textSlots3);
    w->textSlotCount2 = LoadTextSlots((u16*)gUnkJp_0900974C, w->textSlots2);
#else
    w->textSlotCount2 = LoadTextSlots((u16*)gUnk_090362A4, w->textSlots2);
#endif
#endif
#ifndef VERSION_JP
    w->palette = LoadObjPalette(gUnk_09614798, 32);
#endif

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
    case LANGUAGE_GERMAN:
    case LANGUAGE_ITALIAN:
        w->textSlotCount3 = 0;
        v = (230 - GetTextSlotsWidth(w->textSlots, w->textSlotCount)) / 2;
        w->nameX = v;
        t = (u16)w->nameX + GetTextSlotsWidth(w->textSlots, w->textSlotCount);
        w->suffixX = t;
        v = (240 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2;
        w->messageX = v;
        break;
    case LANGUAGE_FRENCH:
        w->textSlotCount3 = LoadTextSlots((u16*)gUnkEu_090CF648, w->textSlots3);
        v = (230 - GetTextSlotsWidth(w->textSlots, w->textSlotCount)) / 2;
        w->nameX = v;
        t = (u16)w->nameX + GetTextSlotsWidth(w->textSlots, w->textSlotCount);
        w->suffixX = t;
        v = (240 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2;
        w->messageX = v;
        break;
    case LANGUAGE_SPANISH:
        w->textSlotCount3 = LoadTextSlots((u16*)gUnkEu_090CF64D, w->textSlots3);
        v = (230 - GetTextSlotsWidth(w->textSlots, w->textSlotCount)) / 2;
        w->nameX = v;
        w->suffixX = v - 3;
        v = (240 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2;
        w->messageX = v;
        break;
    default:
        w->textSlotCount3 = 0;
        break;
    }
#else
    v = (230 - GetTextSlotsWidth(w->textSlots, w->textSlotCount)) / 2;
    w->nameX = v;
    t = (u16)w->nameX + GetTextSlotsWidth(w->textSlots, w->textSlotCount);
    w->suffixX = t;
    v = (240 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) / 2;
    w->messageX = v;
#endif
    w->tiles = LoadObjTiles(gUnk_093F98AC, 0x1800);
    pal = LoadObjPalette(gCard00Palette, 32);
    w->palette2 = pal;
    FadeSetPaletteExcluded(pal->index + 16, 1);
    FadeSetPaletteExcluded(w->textPalette->index + 16, 1);
}

s32 CardName_1(void) {
    return 1;
}

void CardName_2(CardNameWork* w) {
    void** p = &gUnk_09EF1278[2];

    DrawSprite(120, 126, *p, w->tiles, w->palette2, 0, 0, 50);
#ifdef VERSION_JP
    DrawTextSlots(w->nameX, 115, w->textSlots, w->textPalette, 30, w->textSlotCount);
#else
    DrawTextSlots(w->nameX, 115, w->textSlots, w->palette, 30, w->textSlotCount);
#endif
#ifndef VERSION_US
    DrawTextSlots(w->suffixX, 115, w->textSlots3, w->textPalette, 30, w->textSlotCount3);
#endif
    DrawTextSlots(w->messageX, 130, w->textSlots2, w->textPalette, 30, w->textSlotCount2);
}

void CardName_3(CardNameWork* w) {
    FreeTextSlots(w->textSlots, 32);
    FreeTextSlots(w->textSlots2, 32);
#ifdef VERSION_EU
    FreeTextSlots(w->textSlots3, 32);
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->textPalette);
    ReleaseObjPalette(w->palette2);
    ReleaseObjPalette(w->palette);
#else
    FreeTextSlots(w->textSlots3, 2);
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->textPalette);
    ReleaseObjPalette(w->palette2);
#ifndef VERSION_JP
    ReleaseObjPalette(w->palette);
#endif
#endif
}

void PremireEffectInit(PremiumCardEffectWork* w, s16* a) {
    w->tiles = AllocObjTiles(128, 0);
    w->palette = LoadObjPalette(gUnk_09619158, 32);
    SetObjTileSource(w->tiles, gUnk_093F762E);
    AnimInit(&w->anim, gUnk_09EF1260, gUnk_09EF1230);
    AnimStart(&w->anim, GetRandom() % 3, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    w->centerX = a[1] << 8;
    w->centerY = a[2] << 8;
    w->fallY = 0;
    w->radius = a[0] << 8;
    w->angle = a[3];
    w->speed = GetRandom() % 0x181 + 0x100;
    w->x = 0;
    w->y = 0;
    w->unk_38 = 0;
    w->fallSpeed = -(GetRandom() % 0x81 + 0x200);
    gCardListWork->effectCount++;
}

void PremireEffectConvergeInit(PremiumCardEffectWork* w, s16* a) {
    w->tiles = AllocObjTiles(128, 0);
    w->palette = LoadObjPalette(gUnk_09619158, 32);
    SetObjTileSource(w->tiles, gUnk_093F762E);
    AnimInit(&w->anim, gUnk_09EF1260, gUnk_09EF1230);
    AnimStart(&w->anim, GetRandom() % 3, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    w->centerX = a[1] << 8;
    w->centerY = a[2] << 8;
    w->fallY = 0;
    w->radius = a[0] << 8;
    w->angle = a[3];
    w->speed = GetRandom() % 0x81 + 0x200;
    w->x = 0;
    w->y = 0;
    w->unk_38 = 0;
    w->fallSpeed = -(GetRandom() % 0x81 + 0x200);
    PremireEffectSetOrbitPos(w);
    gCardListWork->effectCount++;
}

s32 PremireEffectSpiralUpdate(PremiumCardEffectWork* w) {
    PremireEffectSetOrbitPos(w);
    w->angle += 8;

    if (w->radius > 0) {
        w->radius += -0x180;
        w->gfx = AnimUpdate(&w->anim);
        return 1;
    }

    return 0;
}

s32 Premire_EFFECT2_1(PremiumCardEffectWork* w) {
    PremireEffectMoveFalling(w);
    w->gfx = AnimUpdate(&w->anim);

    if (w->y > 0xB400) {
        return 0;
    }

    return 1;
}

s32 PremireEffectConvergeUpdate(PremiumCardEffectWork* w) {
    PremireEffectMoveToCenter(w);
    w->angle += 8;
    w->gfx = AnimUpdate(&w->anim);

    if (w->radius <= 0x800) {
        return 0;
    }

    return 1;
}

void PremireEffectDraw(PremiumCardEffectWork* w) {
    DrawSprite(w->x >> 8, w->y >> 8, w->gfx, w->tiles, w->palette, 0, 0, 0);
}

void PremireEffectDestroy(PremiumCardEffectWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    gCardListWork->effectCount--;
}

void PremireEffectSetOrbitPos(PremiumCardEffectWork* w) {
    w->x = gSineTable[w->angle & 0xFF] * (w->radius >> 8) + w->centerX;
    w->y = -gSineTable[(w->angle & 0xFF) + 64] * (w->radius >> 8) + w->centerY;
}

void PremireEffectMoveFalling(PremiumCardEffectWork* w) {
    w->fallSpeed += 30;
    w->fallY += w->fallSpeed;
    w->centerX += gSineTable[w->angle & 0xFF] * (w->speed >> 8);
    w->centerY += -gSineTable[(w->angle & 0xFF) + 64] * (w->speed >> 8);
    w->x = w->centerX;
    w->y = w->centerY + w->fallY;
}

void PremireEffectMoveToCenter(PremiumCardEffectWork* w) {
    s32 v;
    s32 d;

    w->vx = w->centerX - w->x;
    w->vy = w->centerY - w->y;
    w->radius = NormalizeVector2D8(&w->vx, &w->vy);
    v = w->speed;
    d = v >> 8;
    w->x += w->vx * d;
    w->y += w->vy * d;

    if (w->radius > 0) {
        w->speed = v - 2;
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
    gPrintBg = bg;
    p = &gPrintLines;
    *p = EwramAlloc(sizeof(PrintLine) * 32);
}

void FreePrintLayer(void) {
    EwramFree(gPrintLines);
}

u8 GetStringLength(u8* p) {
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

void PrintString(u8 a, u8 b, u8 c, u8* s) {
    u8 n;
    u8 i;

    if (gPrintLineCount < 32) {
        n = GetStringLength(s);

        if (n > 32) {
            n = 32;
        }

        for (i = 0; i < n; i++) {
            gPrintLines[gPrintLineCount].tilemap[i] = s[i];
            gPrintLines[gPrintLineCount].tilemap[i] |= c << 12;
        }

        gPrintLines[gPrintLineCount].x = a;
        gPrintLines[gPrintLineCount].y = b;
        gPrintLines[gPrintLineCount].palette = c;
        gPrintLines[gPrintLineCount].length = n;
        RequestTilemapRectCopy(gPrintLines[gPrintLineCount].tilemap, GetBgScreenBase(gPrintBg), 0, 0,
                      gPrintLines[gPrintLineCount].x,
                      gPrintLines[gPrintLineCount].y,
                      (s8)gPrintLines[gPrintLineCount].length, 1);
        gPrintLineCount++;
    }
}

void ResetPrintLines(void) {
    gPrintLineCount = 0;
}

void ClearPrintLines(void) {
    s16 i;

    for (i = 0; i < gPrintLineCount; i++) {
        gPrintLines[i].length = 0;
        gPrintLines[i].x = 0;
        gPrintLines[i].y = 0;
        gPrintLines[i].palette = 0;
        gPrintLines[i].tilemap[0] = 0;
    }

    gPrintLineCount = 0;
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
