#include "macros.h"
#include "card_localized_data.h"
#include "msg_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "msg_api.h"
#include "mode_sio_api.h"
#include "card_battle.h"
#include "mode_test_api.h"
#include "player_progression.h"
#include "m4a_song.h"
#include "game_state.h"
#include <string.h>
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
#include "gba/syscall.h"
#include "malloc.h"
#include "card.h"
#include "card_reload_assets.h"
#include "map_card_assets.h"
#include "card_localized_assets.h"
#include "card_help_assets.h"
#include "card_message_assets.h"
#include "card_description_assets.h"
#include <stddef.h>
#include "game.h"
#include "bos4_api.h"
#include "sprites_deck_menu.h"
#include "sprites_evt.h"
#include "sprites_msg.h"
#include "sprites_map.h"
#include "sprites_card.h"

SysMsgWinWork* gUnk_02034B00;
#ifndef VERSION_EU
u8 gUnk_02034B04[4];
#endif

#ifdef VERSION_EU
extern void* gUnkEu_08890E1C[];
extern void* gUnkEu_08890E44[];

#define LANGSTR(x) (((void**)(x))[gLanguage])
#else
#define LANGSTR(x) (x)
#endif
u8 func_080A470C(SysMsgWinWork* w, void* a);
s32 func_080A4910(SysMsgWinWork* w);
u8 func_080A4958(SysMsgWinWork* w, void* a);
u8 func_080A4CC8(SysMsgWinWork* w, void* a);
s32 func_080A5150(SysMsgWinWork* w);
u8 func_0806BB44(s32 x, s32 y, MsgLatinChar* s, MsgLatinChar** d);
#ifdef VERSION_JP
u8 func_0806BDB8(s32 x, s32 y, u8* s, u8** d);
#endif

const s32 gUnk_09041E80[4] = { 0xE00, 0x6C00, 0xE00, 0x6C00 };

void func_080A430C(SysMsgWinWork* w, CardMessageArgs* a) {
    vu32 zero = 0;

    CpuSet((void*)&zero, w, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(SysMsgWinWork) / 4);
    w->args = *a;
    w->messageDef = &gCardMessageDefs[w->args.messageId];
    if (w->messageDef->flags & 4) {
        w->unk_134 = func_0806BA74(1, 1);
    } else {
        w->unk_134 = func_0806BA74(1, 0);
    }
    FadeSetPaletteExcluded(w->unk_134 + 16, 1);
    w->unk_138[4] = 0;
    w->unk_138[0] = 8;
    w->unk_138[1] = 0;
    w->unk_138[2] = 0;
    w->unk_138[3] = 0;
    w->unk_143 = 0;
    w->nextText = 0;
    w->tiles3 = 0;
    w->palette = 0;
    w->tiles4 = 0;
    w->palette2 = 0;
    w->tiles2 = 0;
    w->palette4 = 0;
    w->tiles = 0;
    w->palette3 = 0;
    w->unk_0C0 = 0;
    w->unk_142 = 1;
    w->unk_141 = 1;
    w->unk_144 = 0;
    w->unk_13F = 0;
    w->unk_140 = 0;
    w->unk_145 = 0;
    w->unk_146[0] = 1;
#ifdef VERSION_JP
    w->unk_138[3] = func_0806BDB8(0x2E00, gUnk_09033CB8[w->messageDef->positionIndex],
                                   (TextChar*)w->messageDef->text, &w->nextText);
#else
    if (w->nextText != 0) {
        w->unk_138[3] = func_0806BB44(0x2E00, gUnk_09041E80[w->messageDef->positionIndex] - 0x200,
                                       (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
    } else {
        w->unk_138[3] = func_0806BB44(0x2E00, gUnk_09041E80[w->messageDef->positionIndex] - 0x200,
                                       (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
    }
#endif
    InitTextSlots(w->textSlots, 10);
    InitTextSlots(w->textSlots2, 10);
    gUnk_0203A9D4 = 1;
    gUnk_0203A9D8 = 0;
    w->unk_138[1] = w->unk_138[3];
    switch (w->args.unk_07) {
    case 0:
        w->tiles3 = AllocObjTiles(0x40, 0);
        w->palette = LoadObjPalette(gBStatesPalette, 32);
        FadeSetPaletteExcluded(w->palette->index + 16, 1);
        SetObjTileSource(w->tiles3, gFEventTiles);
        AnimInit(&w->anim2, gFEventAnims, gFEventFrames);
        AnimStart(&w->anim2, 2, 1);
        w->gfx4 = AnimGetGfx(&w->anim2);
        SetBgPriority(w->args.bg, 0);
        break;
    case 1:
        SetBgPriority(w->args.bg, 0);
        break;
    case 2:
        w->tiles3 = AllocObjTiles(0x40, 0);
        w->palette = LoadObjPalette(gBStatesPalette, 32);
        FadeSetPaletteExcluded(w->palette->index + 16, 1);
        SetObjTileSource(w->tiles3, gFEventTiles);
        AnimInit(&w->anim2, gFEventAnims, gFEventFrames);
        AnimStart(&w->anim2, 2, 1);
        w->gfx4 = AnimGetGfx(&w->anim2);
        break;
    }
    gUnk_02034B00 = w;
}

u8 func_080A4578(SysMsgWinWork* w, void* a) {
    void* pal;

    switch (w->args.unk_07) {
    case 0:
    case 1:
        pal = &gUnk_050001C0[0x20];
        LoadBgTiles(w->args.bg, gUnk_0950E2F8, 0x140);
        LoadBgMap(w->args.bg, gUnk_096112B8, 0x800);
        LoadPalette(gCard00Palette, pal, 32);

        switch ((u32)w->messageDef->positionIndex) {
        case 0:
        case 2:
            SetBgScroll(w->args.bg, (u16)-24, 0);
            break;
        case 1:
        case 3:
            SetBgScroll(w->args.bg, (u16)-24, (u16)-94);
            break;
        default:
            SetBgScroll(w->args.bg, (u16)-24, (u16)-94);
            break;
        }
        break;
    case 2:
    case 3:
        switch ((u32)w->messageDef->positionIndex) {
        case 0:
        case 2:
            w->unk_120 = 0x7800;
            w->unk_124 = 0x2200;
            break;
        case 1:
        default:
            w->unk_120 = 0x7800;
            w->unk_124 = 0x7E00;
            break;
        }

        w->tiles2 = LoadObjTiles(&gUnk_093F8C8E[0xC1E], 0x1800);

        if (w->tiles2 == 0) {
            w->unk_146[1] = 1;
            w->tiles2 = LoadObjTiles(&gUnk_0950E2F8[0x140], 0x680);
        } else {
            w->unk_146[1] = 0;
        }

        w->palette4 = LoadObjPalette(gCard00Palette, 32);
        FadeSetPaletteExcluded(w->palette4->index + 16, 1);
        break;
    }

    switch (w->args.unk_07) {
    case 0:
    case 2:
        SetTaskUpdate(a, (TaskUpdateFunc)func_080A470C);
        break;
    case 1:
    case 3:
        SetTaskUpdate(a, (TaskUpdateFunc)func_080A4CC8);
        break;
    }

    return 1;
}

u8 func_080A470C(SysMsgWinWork* w, void* a) {
    u8* pal;

    if (w->tiles3 != 0) {
        w->gfx4 = AnimUpdate(&w->anim2);
    }

    if (GetKeysPressed() & A_BUTTON) {
        m4aSongNumStart(SONG_SYS_KETTEI);
        if (w->nextText != 0) {
#ifdef VERSION_JP
            w->unk_138[3] = func_0806BDB8(0x2E00, gUnk_09033CB8[w->messageDef->positionIndex],
                                           w->nextText, &w->nextText);
#else
            w->unk_138[3] = func_0806BB44(0x2E00, gUnk_09041E80[w->messageDef->positionIndex] - 0x200,
                                           w->nextText, &w->nextText);
#endif
            w->unk_138[1] = w->unk_138[3];
        } else if (!(w->messageDef->flags & 1)) {
            AnimStart(&w->anim2, 3, 1);
            w->unk_142 = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)func_080A4910);
            w->unk_136 = 0;
            w->unk_138[0] = 8;
        } else {
            ReleaseObjTiles(w->tiles3);
            ReleaseObjPalette(w->palette);
            w->tiles3 = 0;
            w->palette = 0;
            w->tiles4 = AllocObjTiles(0x120, 0);
            pal = gUnk_09614418;
            w->palette2 = LoadObjPalette(pal, 32);
#ifdef VERSION_EU
            FadeSetPaletteExcluded(w->palette2->index + 16, 1);
#else
            FadeSetPaletteExcluded(w->palette4->index + 16, 1);
#endif
            LoadObjPaletteBank(w->palette2->index, pal);
            SetObjTileSource(w->tiles4, gUnk_090A4664);
            AnimInit(&w->anim3, gUnk_09EEB03C, gUnk_09EEB008);
            AnimStart(&w->anim3, 2, 1);
            w->gfx = AnimGetGfx(&w->anim3);
            w->unk_13D = 1;
            w->x = 0x5800;
            w->unk_11C = gUnk_09033D28[w->unk_13D] - 0x500;
#ifdef VERSION_EU
            w->unk_13F = LoadTextSlots(eu_0805E924(gUnkEu_08890E1C), w->textSlots);
            w->unk_140 = LoadTextSlots(eu_0805E924(gUnkEu_08890E44), w->textSlots2);
#else
            w->unk_13F = LoadTextSlots(gUnk_08159E10, w->textSlots);
            w->unk_140 = LoadTextSlots(gUnk_08159E18, w->textSlots2);
#endif
            w->unk_0C0 = _08066468(1);
            w->unk_144 = 1;
            w->tiles = LoadObjTiles(gUnk_093F7C9C, 0xFC0);
            w->palette3 = LoadObjPalette(gCard00Palette, 32);
#ifdef VERSION_EU
            FadeSetPaletteExcluded(w->palette3->index + 16, 1);
#else
            FadeSetPaletteExcluded(w->palette4->index + 16, 1);
#endif
            SetTaskUpdate(a, (TaskUpdateFunc)func_080A4958);
        }
    }
    return 1;
}
s32 func_080A4910(SysMsgWinWork* w) {
    if (w->tiles3 != 0) {
        w->gfx4 = AnimUpdate(&w->anim2);
    }

    w->unk_136 += 1;

    if (w->unk_136 > 15) {
        w->unk_141 = 0;
        return 0;
    }

    return 1;
}
u8 func_080A4958(SysMsgWinWork* w, void* a) {
    w->gfx = AnimUpdate(&w->anim3);

    switch (GetKeysPressed()) {
    case DPAD_UP:
        if (w->unk_13D != 0) {
            w->unk_13D--;
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        w->unk_13E = 4;
        break;
    case DPAD_DOWN:
        if (w->unk_13D == 0) {
            w->unk_13D++;
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        w->unk_13E = 4;
        break;
    case A_BUTTON:
    case START_BUTTON:
        m4aSongNumStart(SONG_SYS_KETTEI);

        if (w->unk_13D == 0) {
            gUnk_0203A9D8 = 1;
        } else {
            gUnk_0203A9D8 = 0;
        }

        w->unk_142 = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080A4910);
        break;
    }

    if (w->unk_13E != 0) {
        ApproachValue(&w->unk_11C, gUnk_09033D28[w->unk_13D] - 0x500, w->unk_13E);
        w->unk_13E--;
    }

    return 1;
}

void func_080A4A50(SysMsgWinWork* w) {
    func_0806C2C0(w->unk_138[1]);

    switch (w->args.unk_07) {
    case 2:
    case 3:
        if (w->tiles2 != 0) {
            if (w->unk_146[1] != 0) {
                DrawSprite(w->unk_120 >> 8, w->unk_124 >> 8, (&gUnk_09EF12E8[2])[0],
                           w->tiles2, w->palette4, 0, 0, 10);
            } else {
                DrawSprite(w->unk_120 >> 8, w->unk_124 >> 8, (&gUnk_09EF1278[2])[0],
                           w->tiles2, w->palette4, 0, 0, 10);
            }
        }
        break;
    }

    if (w->tiles3 != 0) {
        if (w->unk_141 != 0) {
            DrawSprite(120, gUnk_09033D08[w->messageDef->positionIndex][1] >> 8, w->gfx4,
                       w->tiles3, w->palette, 0, 0, 5);
        }
    }

    if (w->tiles4 != 0) {
        DrawSprite(w->x >> 8, w->unk_11C >> 8, w->gfx,
                   w->tiles4, w->palette2, 0, 1, 5);
    }

    if (w->unk_144 != 0) {
        DrawSprite(120, 75, gUnk_09EF126C[1], w->tiles, w->palette3, 0, 0, 10);
        DrawTextSlots((240 - GetTextSlotsWidth(w->textSlots, w->unk_13F)) >> 1, 62, w->textSlots,
                      w->unk_0C0, 0, w->unk_13F);
        DrawTextSlots((240 - GetTextSlotsWidth(w->textSlots2, w->unk_140)) >> 1, 77, w->textSlots2,
                      w->unk_0C0, 0, w->unk_140);
    }
}

void func_080A4C1C(SysMsgWinWork* w) {
    if (w->args.unk_07 <= 1) {
        DisableBg(w->args.bg);
    }

    func_0806C34C();

    if (w->tiles3 != 0) {
        ReleaseObjTiles(w->tiles3);
    }

    if (w->palette != 0) {
        ReleaseObjPalette(w->palette);
    }

    if (w->tiles4 != 0) {
        ReleaseObjTiles(w->tiles4);
    }

    if (w->palette2 != 0) {
        ReleaseObjPalette(w->palette2);
    }

    if (w->tiles != 0) {
        ReleaseObjTiles(w->tiles);
    }

    if (w->tiles2 != 0) {
        ReleaseObjTiles(w->tiles2);
    }

    if (w->palette4 != 0) {
        ReleaseObjPalette(w->palette4);
    }

    if (w->palette3 != 0) {
        ReleaseObjPalette(w->palette3);
    }

    if (w->unk_0C0 != 0) {
        ReleaseObjPalette(w->unk_0C0);
    }

    FreeTextSlots(w->textSlots, 10);
    FreeTextSlots(w->textSlots2, 10);
    gUnk_0203A9D4 = 0;
    gUnk_02034B00 = 0;
}
u8 func_080A4CC8(SysMsgWinWork* w, void* a) {
#ifndef VERSION_JP
    TextChar** p;
#endif

    if (w->unk_146[0] == 0) {
        return 0;
    }

    if (w->unk_145 == 1) {
        w->unk_145 = 0;
        w->messageDef = &gCardMessageDefs[w->args.messageId];
#ifdef VERSION_JP
        w->unk_138[3] = func_0806BDB8(
            0x2E00,
            gUnk_09033CB8[w->messageDef->positionIndex],
            (TextChar*)(w->messageDef->text),
            &w->nextText);
#else
        p = &w->nextText;

        if (*p != 0) {
            w->unk_138[3] = func_0806BB44(
                0x2E00,
                gUnk_09041E80[w->messageDef->positionIndex] - 0x200,
                *p, p);
        } else {
            w->unk_138[3] = func_0806BB44(
                0x2E00,
                gUnk_09041E80[w->messageDef->positionIndex] - 0x200,
                (TextChar*)LANGSTR(w->messageDef->text),
                p);
        }
#endif

        w->unk_138[1] = w->unk_138[3];
    }

    return 1;
}
s32 func_080A4D7C(CardMessageArgs* src) {
    if (gUnk_02034B00 != 0) {
        gUnk_02034B00->args = *src;
        gUnk_02034B00->unk_145 = 1;

        return 1;
    }

    return 0;
}

s32 func_080A4DAC(void) {
    if (gUnk_02034B00 != 0) {
        gUnk_02034B00->unk_146[0] = 0;
        return 1;
    }

    return 0;
}
void func_080A4DCC(SysMsgWinWork* w, CardMessageArgs* a) {
    vu32 zero = 0;

    CpuSet((void*)&zero, w, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(SysMsgWinWork) / 4);
    w->args = *a;
    w->messageDef = &gCardMessageDefs[w->args.messageId];
    w->unk_134 = func_0806BA74(1, 0);
    FadeSetPaletteExcluded(w->unk_134 + 16, 1);
    w->unk_138[4] = 0;
    w->unk_138[0] = 8;
    w->unk_138[1] = 0;
    w->unk_138[2] = 0;
    w->unk_138[3] = 0;
    w->unk_143 = 0;
    w->nextText = 0;
    w->tiles3 = 0;
    w->palette = 0;
    w->tiles4 = 0;
    w->palette2 = 0;
    w->tiles2 = 0;
    w->palette4 = 0;
    w->tiles = 0;
    w->palette3 = 0;
    w->unk_0C0 = 0;
    w->unk_142 = 1;
    w->unk_141 = 1;
    w->unk_144 = 0;
    w->unk_13F = 0;
    w->unk_140 = 0;
    w->unk_145 = 0;
    w->unk_146[0] = 1;
#ifdef VERSION_JP
    w->unk_138[3] = func_0806BDB8(0x4000, 0x4000, (TextChar*)w->messageDef->text, &w->nextText);
#else
    if (w->nextText != 0) {
#ifdef VERSION_EU
        switch (gLanguage) {
        case 0:
        case 1:
            w->unk_138[3] = func_0806BB44(0x4D00, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        case 2:
            w->unk_138[3] = func_0806BB44(0x4100, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        case 4:
            w->unk_138[3] = func_0806BB44(0x4400, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        case 3:
            w->unk_138[3] = func_0806BB44(0x4600, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        default:
            w->unk_138[3] = func_0806BB44(0x4D00, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        }
#else
        w->unk_138[3] = func_0806BB44(0x4D00, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
#endif
    } else {
#ifdef VERSION_EU
        switch (gLanguage) {
        case 0:
        case 1:
            w->unk_138[3] = func_0806BB44(0x4D00, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        case 2:
            w->unk_138[3] = func_0806BB44(0x4100, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        case 4:
            w->unk_138[3] = func_0806BB44(0x4400, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        case 3:
            w->unk_138[3] = func_0806BB44(0x4600, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        default:
            w->unk_138[3] = func_0806BB44(0x4D00, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        }
#else
        w->unk_138[3] = func_0806BB44(0x4D00, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
#endif
    }
#endif
    InitTextSlots(w->textSlots, 10);
    InitTextSlots(w->textSlots2, 10);
    gUnk_0203A9D4 = 1;
    gUnk_0203A9D8 = 0;
    w->unk_138[1] = w->unk_138[3];
    gUnk_02034B00 = w;
}

u8 func_080A4F14(SysMsgWinWork* w, void* a) {
    void* pal;
    switch (w->args.unk_07) {
    case 0:
    case 1:
        pal = (void*)0x050001E0;
        LoadBgTiles(w->args.bg, gUnk_099597E4, 0x140);
        LoadBgMap(w->args.bg, gUnk_09985F44, 0x800);
        LoadPalette(gCard00Palette, pal, 32);
        switch ((u32)w->messageDef->positionIndex) {
        case 0:
        case 2:
            SetBgScroll(w->args.bg, 0, 0);
            break;
        case 1:
        case 3:
            SetBgScroll(w->args.bg, 0, 0);
            break;
        default:
            SetBgScroll(w->args.bg, 0, 0);
            break;
        }
        break;
    case 2:
    case 3:
        switch ((u32)w->messageDef->positionIndex) {
        case 0:
        case 2:
            w->unk_120 = 0x7800;
            w->unk_124 = 0x2000;
            break;
        case 1:
        default:
            w->unk_120 = 0x7800;
            w->unk_124 = 0x8200;
            break;
        }
        w->tiles2 = LoadObjTiles(gUnk_093F8C8E, 0xC00);
        w->palette4 = LoadObjPalette(gCard00Palette, 32);
        FadeSetPaletteExcluded(w->palette4->index + 16, 1);
        break;
    }
    if (w->args.unk_07 == 0 || w->args.unk_07 == 2) {
        SetTaskUpdate(a, (TaskUpdateFunc)func_080A5034);
    }
    return 1;
}

u8 func_080A5034(SysMsgWinWork* w, void* a) {
    u8* pal;

    w->tiles4 = AllocObjTiles(0x120, 0);
    pal = gUnk_09614418;
    w->palette2 = LoadObjPalette(pal, 32);
#ifdef VERSION_EU
    FadeSetPaletteExcluded(w->palette2->index + 16, 1);
#else
    FadeSetPaletteExcluded(w->palette4->index + 16, 1);
#endif
    LoadObjPaletteBank(w->palette2->index, pal);
    SetObjTileSource(w->tiles4, gUnk_090A4664);
    AnimInit(&w->anim3, gUnk_09EEB03C, gUnk_09EEB008);
    AnimStart(&w->anim3, 2, 1);
    w->gfx = AnimGetGfx(&w->anim3);
    w->unk_13D = 1;
    w->x = 0x8500;
    w->unk_11C = 0x5000;
#ifdef VERSION_EU
    w->unk_13F = LoadTextSlots(eu_0805E924(gUnkEu_08890E1C), w->textSlots);
    w->unk_140 = LoadTextSlots(eu_0805E924(gUnkEu_08890E44), w->textSlots2);
#else
    w->unk_13F = LoadTextSlots(gUnk_08159E10, w->textSlots);
    w->unk_140 = LoadTextSlots(gUnk_08159E18, w->textSlots2);
#endif
    w->unk_0C0 = _08066468(1);
    w->unk_144 = 1;
    w->tiles = LoadObjTiles(gUnk_093F7C9C, 0xFC0);
    w->palette3 = LoadObjPalette(gCard00Palette, 32);
#ifdef VERSION_EU
    FadeSetPaletteExcluded(w->palette3->index + 16, 1);
#else
    FadeSetPaletteExcluded(w->palette4->index + 16, 1);
#endif
    SetTaskUpdate(a, (TaskUpdateFunc)func_080A5198);
    return 1;
}
s32 func_080A5150(SysMsgWinWork* w) {
    if (w->tiles3 != 0) {
        w->gfx4 = AnimUpdate(&w->anim2);
    }

    w->unk_136 += 1;

    if (w->unk_136 > 15) {
        w->unk_141 = 0;
        return 0;
    }

    return 1;
}
u8 func_080A5198(SysMsgWinWork* w, void* a) {
    s32 tbl[2];

    *(u64*)tbl = *(u64*)gUnk_09041E9C;
    w->gfx = AnimUpdate(&w->anim3);

    switch (GetKeysPressed()) {
    case DPAD_LEFT:
        if (w->unk_13D != 0) {
            w->unk_13D--;
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        w->unk_13E = 1;
        break;
    case DPAD_RIGHT:
        if (w->unk_13D == 0) {
            w->unk_13D++;
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        w->unk_13E = 1;
        break;
    }

    switch (GetKeysPressed()) {
    case A_BUTTON:
    case START_BUTTON:
        m4aSongNumStart(SONG_SYS_KETTEI);

        if (w->unk_13D == 0) {
            gUnk_0203A9D8 = 1;
        } else {
            gUnk_0203A9D8 = 0;
        }

        w->unk_142 = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080A5150);
        break;
    case B_BUTTON:
        m4aSongNumStart(SONG_SYS_CLOSE);
        gUnk_0203A9D8 = 0;
        w->unk_142 = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080A5150);
        break;
    }

    if (w->unk_13E != 0) {
        ApproachValue(&w->x, tbl[w->unk_13D], w->unk_13E);
        w->unk_13E--;
    }

    return 1;
}
void func_080A52BC(SysMsgWinWork* w) {
    func_0806C2C0(w->unk_138[1]);

    switch (w->args.unk_07) {
    case 2:
    case 3:
        if (w->tiles2 != 0) {
            DrawSprite(w->unk_120 >> 8, w->unk_124 >> 8, gUnk_09EF1278[0], w->tiles2, w->palette4, 0, 0, 20);
        }
        break;
    }

    if (w->tiles3 != 0 && w->unk_141 != 0) {
        DrawSprite(120, gUnk_09033D08[w->messageDef->positionIndex][1] >> 8, w->gfx4, w->tiles3, w->palette, 0, 0, 10);
    }

    if (w->tiles4 != 0) {
        DrawSprite(w->x >> 8, w->unk_11C >> 8, w->gfx, w->tiles4, w->palette2, 0, 1, 10);
    }

    DrawTextSlots(89, 86, w->textSlots, w->unk_0C0, 0, w->unk_13F);
    DrawTextSlots(135, 86, w->textSlots2, w->unk_0C0, 0, w->unk_140);
}

void func_080A53E4(SysMsgWinWork* w) {
    if (w->args.unk_07 <= 1) {
        DisableBg(w->args.bg);
    }

    func_0806C34C();

    if (w->tiles3 != 0) {
        ReleaseObjTiles(w->tiles3);
    }

    if (w->palette != 0) {
        ReleaseObjPalette(w->palette);
    }

    if (w->tiles4 != 0) {
        ReleaseObjTiles(w->tiles4);
    }

    if (w->palette2 != 0) {
        ReleaseObjPalette(w->palette2);
    }

    if (w->tiles != 0) {
        ReleaseObjTiles(w->tiles);
    }

    if (w->tiles2 != 0) {
        ReleaseObjTiles(w->tiles2);
    }

    if (w->palette4 != 0) {
        ReleaseObjPalette(w->palette4);
    }

    if (w->palette3 != 0) {
        ReleaseObjPalette(w->palette3);
    }

    if (w->unk_0C0 != 0) {
        ReleaseObjPalette(w->unk_0C0);
    }

    FreeTextSlots(w->textSlots, 10);
    FreeTextSlots(w->textSlots2, 10);
    gUnk_0203A9D4 = 0;
    gUnk_02034B00 = 0;
}

TaskDesc gUnk_09EE8E30 = {
    "sysmsgwin",
    (TaskInitFunc)func_080A430C,
    (TaskUpdateFunc)func_080A4578,
    (TaskFunc)func_080A4A50,
    (TaskFunc)func_080A4C1C,
    sizeof(SysMsgWinWork),
};

TaskDesc gUnk_09EE8E48 = {
    "sysmsgwin",
    (TaskInitFunc)func_080A4DCC,
    (TaskUpdateFunc)func_080A4F14,
    (TaskFunc)func_080A52BC,
    (TaskFunc)func_080A53E4,
    sizeof(SysMsgWinWork),
};

const s32 gUnk_09041E9C[2] = { 0x5000, 0x8000 };
