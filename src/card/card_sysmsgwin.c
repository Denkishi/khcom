#include "card_localized_data.h"
#include "msg_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "msg_api.h"
#include "card_battle.h"
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
#include "gba/syscall.h"
#include "card.h"
#include "card_message_assets.h"
#include <stddef.h>
#include "game.h"
#include "bos4_api.h"
#include "sprites_deck_menu.h"
#include "sprites_evt.h"
#include "sprites_msg.h"
#include "sprites_map.h"
#include "sprites_card.h"
#include "gba/keys.h"
#include "songs.h"
#include "jiminy_data.h"
#include "common_text.h"

SysMsgWinWork* gActiveSysmsgwin;
#ifndef VERSION_EU
u8 gUnk_02034B04[4];
#endif

#ifdef VERSION_EU

#define LANGSTR(x) (((void**)(x))[gLanguage])
#else
#define LANGSTR(x) (x)
#endif
u8 UpdateSysmsgwinWaitInput(SysMsgWinWork* w, void* a);
s32 UpdateSysmsgwinClose(SysMsgWinWork* w);
u8 UpdateSysmsgwinChoice(SysMsgWinWork* w, void* a);
u8 UpdateSysmsgwinPersistent(SysMsgWinWork* w, void* a);

static const s32 sSysmsgwinTextY[4] = { 0xE00, 0x6C00, 0xE00, 0x6C00 };

void sysmsgwin_0(SysMsgWinWork* w, CardMessageArgs* a) {
    vu32 zero = 0;

    CpuSet((void*)&zero, w, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(SysMsgWinWork) / 4);
    w->args = *a;
    w->messageDef = &gCardMessageDefs[w->args.messageId];
    if (w->messageDef->flags & 4) {
        w->glyphPaletteIndex = InitCardMsgGlyphSprites(1, 1);
    } else {
        w->glyphPaletteIndex = InitCardMsgGlyphSprites(1, 0);
    }
    FadeSetPaletteExcluded(w->glyphPaletteIndex + 16, 1);
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
    w->textPalette = 0;
    w->unk_142 = 1;
    w->waitIconVisible = 1;
    w->choiceVisible = 0;
    w->textSlotCount = 0;
    w->textSlotCount2 = 0;
    w->messagePending = 0;
    w->unk_146[0] = 1;
#ifdef VERSION_JP
    w->unk_138[3] = LayoutCardMsgGlyphsPageSjis(0x2E00, gMsgwinTextY[w->messageDef->positionIndex],
                                   (TextChar*)w->messageDef->text, &w->nextText);
#else
    if (w->nextText != NULL) {
        w->unk_138[3] = LayoutCardMsgGlyphsPage(0x2E00, sSysmsgwinTextY[w->messageDef->positionIndex] - 0x200,
                                       (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
    } else {
        w->unk_138[3] = LayoutCardMsgGlyphsPage(0x2E00, sSysmsgwinTextY[w->messageDef->positionIndex] - 0x200,
                                       (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
    }
#endif
    InitTextSlots(w->textSlots, 10);
    InitTextSlots(w->textSlots2, 10);
    gMessageWindowOpen = 1;
    gMessageWindowAnswerYes = 0;
    w->unk_138[1] = w->unk_138[3];
    switch (w->args.mode) {
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
    gActiveSysmsgwin = w;
}

u8 sysmsgwin_1(SysMsgWinWork* w, void* a) {
    void* pal;

    switch (w->args.mode) {
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
            w->frameX = 0x7800;
            w->frameY = 0x2200;
            break;
        case 1:
        default:
            w->frameX = 0x7800;
            w->frameY = 0x7E00;
            break;
        }

        w->tiles2 = LoadObjTiles(&gUnk_093F8C8E[0xC1E], 0x1800);

        if (w->tiles2 == NULL) {
            w->unk_146[1] = 1;
            w->tiles2 = LoadObjTiles(&gUnk_0950E2F8[0x140], 0x680);
        } else {
            w->unk_146[1] = 0;
        }

        w->palette4 = LoadObjPalette(gCard00Palette, 32);
        FadeSetPaletteExcluded(w->palette4->index + 16, 1);
        break;
    }

    switch (w->args.mode) {
    case 0:
    case 2:
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinWaitInput);
        break;
    case 1:
    case 3:
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinPersistent);
        break;
    }

    return 1;
}

u8 UpdateSysmsgwinWaitInput(SysMsgWinWork* w, void* a) {
    u8* pal;

    if (w->tiles3 != NULL) {
        w->gfx4 = AnimUpdate(&w->anim2);
    }

    if (GetKeysPressed() & A_BUTTON) {
        m4aSongNumStart(SONG_SYS_KETTEI);
        if (w->nextText != NULL) {
#ifdef VERSION_JP
            w->unk_138[3] = LayoutCardMsgGlyphsPageSjis(0x2E00, gMsgwinTextY[w->messageDef->positionIndex],
                                           w->nextText, &w->nextText);
#else
            w->unk_138[3] = LayoutCardMsgGlyphsPage(0x2E00, sSysmsgwinTextY[w->messageDef->positionIndex] - 0x200,
                                           w->nextText, &w->nextText);
#endif
            w->unk_138[1] = w->unk_138[3];
        } else if (!(w->messageDef->flags & 1)) {
            AnimStart(&w->anim2, 3, 1);
            w->unk_142 = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinClose);
            w->closeTimer = 0;
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
            w->choice = 1;
            w->x = 0x5800;
            w->cursorY = gMsgwaitYesnoCursorY[w->choice] - 0x500;
#ifdef VERSION_EU
            w->textSlotCount = LoadTextSlots(eu_0805E924(&gUnkEu_08890E1C), w->textSlots);
            w->textSlotCount2 = LoadTextSlots(eu_0805E924(&gUnkEu_08890E44), w->textSlots2);
#else
            w->textSlotCount = LoadTextSlots(gUnk_08159E10, w->textSlots);
            w->textSlotCount2 = LoadTextSlots(gUnk_08159E18, w->textSlots2);
#endif
            w->textPalette = LoadTextPalette(1);
            w->choiceVisible = 1;
            w->tiles = LoadObjTiles(gUnk_093F7C9C, 0xFC0);
            w->palette3 = LoadObjPalette(gCard00Palette, 32);
#ifdef VERSION_EU
            FadeSetPaletteExcluded(w->palette3->index + 16, 1);
#else
            FadeSetPaletteExcluded(w->palette4->index + 16, 1);
#endif
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinChoice);
        }
    }
    return 1;
}
s32 UpdateSysmsgwinClose(SysMsgWinWork* w) {
    if (w->tiles3 != NULL) {
        w->gfx4 = AnimUpdate(&w->anim2);
    }

    w->closeTimer += 1;

    if (w->closeTimer > 15) {
        w->waitIconVisible = 0;
        return 0;
    }

    return 1;
}
u8 UpdateSysmsgwinChoice(SysMsgWinWork* w, void* a) {
    w->gfx = AnimUpdate(&w->anim3);

    switch (GetKeysPressed()) {
    case DPAD_UP:
        if (w->choice != 0) {
            w->choice--;
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        w->cursorSteps = 4;
        break;
    case DPAD_DOWN:
        if (w->choice == 0) {
            w->choice++;
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        w->cursorSteps = 4;
        break;
    case A_BUTTON:
    case START_BUTTON:
        m4aSongNumStart(SONG_SYS_KETTEI);

        if (w->choice == 0) {
            gMessageWindowAnswerYes = 1;
        } else {
            gMessageWindowAnswerYes = 0;
        }

        w->unk_142 = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinClose);
        break;
    }

    if (w->cursorSteps != 0) {
        ApproachValue(&w->cursorY, gMsgwaitYesnoCursorY[w->choice] - 0x500, w->cursorSteps);
        w->cursorSteps--;
    }

    return 1;
}

void sysmsgwin_2(SysMsgWinWork* w) {
    DrawCardMsgGlyphs(w->unk_138[1]);

    switch (w->args.mode) {
    case 2:
    case 3:
        if (w->tiles2 != NULL) {
            if (w->unk_146[1] != 0) {
                DrawSprite(w->frameX >> 8, w->frameY >> 8, (&gUnk_09EF12E8[2])[0],
                           w->tiles2, w->palette4, 0, 0, 10);
            } else {
                DrawSprite(w->frameX >> 8, w->frameY >> 8, (&gUnk_09EF1278[2])[0],
                           w->tiles2, w->palette4, 0, 0, 10);
            }
        }
        break;
    }

    if (w->tiles3 != NULL) {
        if (w->waitIconVisible != 0) {
            DrawSprite(120, gMsgwaitIconPos[w->messageDef->positionIndex][1] >> 8, w->gfx4,
                       w->tiles3, w->palette, 0, 0, 5);
        }
    }

    if (w->tiles4 != NULL) {
        DrawSprite(w->x >> 8, w->cursorY >> 8, w->gfx,
                   w->tiles4, w->palette2, 0, 1, 5);
    }

    if (w->choiceVisible != 0) {
        DrawSprite(120, 75, gUnk_09EF126C[1], w->tiles, w->palette3, 0, 0, 10);
        DrawTextSlots((240 - GetTextSlotsWidth(w->textSlots, w->textSlotCount)) >> 1, 62, w->textSlots,
                      w->textPalette, 0, w->textSlotCount);
        DrawTextSlots((240 - GetTextSlotsWidth(w->textSlots2, w->textSlotCount2)) >> 1, 77, w->textSlots2,
                      w->textPalette, 0, w->textSlotCount2);
    }
}

void sysmsgwin_3(SysMsgWinWork* w) {
    if (w->args.mode <= 1) {
        DisableBg(w->args.bg);
    }

    FreeCardMsgGlyphSprites();

    if (w->tiles3 != NULL) {
        ReleaseObjTiles(w->tiles3);
    }

    if (w->palette != NULL) {
        ReleaseObjPalette(w->palette);
    }

    if (w->tiles4 != NULL) {
        ReleaseObjTiles(w->tiles4);
    }

    if (w->palette2 != NULL) {
        ReleaseObjPalette(w->palette2);
    }

    if (w->tiles != NULL) {
        ReleaseObjTiles(w->tiles);
    }

    if (w->tiles2 != NULL) {
        ReleaseObjTiles(w->tiles2);
    }

    if (w->palette4 != NULL) {
        ReleaseObjPalette(w->palette4);
    }

    if (w->palette3 != NULL) {
        ReleaseObjPalette(w->palette3);
    }

    if (w->textPalette != NULL) {
        ReleaseObjPalette(w->textPalette);
    }

    FreeTextSlots(w->textSlots, 10);
    FreeTextSlots(w->textSlots2, 10);
    gMessageWindowOpen = 0;
    gActiveSysmsgwin = 0;
}
u8 UpdateSysmsgwinPersistent(SysMsgWinWork* w, void* a) {
#ifndef VERSION_JP
    TextChar** p;
#endif

    if (w->unk_146[0] == 0) {
        return 0;
    }

    if (w->messagePending == 1) {
        w->messagePending = 0;
        w->messageDef = &gCardMessageDefs[w->args.messageId];
#ifdef VERSION_JP
        w->unk_138[3] = LayoutCardMsgGlyphsPageSjis(
            0x2E00,
            gMsgwinTextY[w->messageDef->positionIndex],
            (TextChar*)(w->messageDef->text),
            &w->nextText);
#else
        p = &w->nextText;

        if (*p != NULL) {
            w->unk_138[3] = LayoutCardMsgGlyphsPage(
                0x2E00,
                sSysmsgwinTextY[w->messageDef->positionIndex] - 0x200,
                *p, p);
        } else {
            w->unk_138[3] = LayoutCardMsgGlyphsPage(
                0x2E00,
                sSysmsgwinTextY[w->messageDef->positionIndex] - 0x200,
                (TextChar*)LANGSTR(w->messageDef->text),
                p);
        }
#endif

        w->unk_138[1] = w->unk_138[3];
    }

    return 1;
}
s32 ReplaceSysmsgwinMessage(CardMessageArgs* src) {
    if (gActiveSysmsgwin != NULL) {
        gActiveSysmsgwin->args = *src;
        gActiveSysmsgwin->messagePending = 1;

        return 1;
    }

    return 0;
}

s32 CloseSysmsgwin(void) {
    if (gActiveSysmsgwin != NULL) {
        gActiveSysmsgwin->unk_146[0] = 0;
        return 1;
    }

    return 0;
}
void sysmsgwinChoice_0(SysMsgWinWork* w, CardMessageArgs* a) {
    vu32 zero = 0;

    CpuSet((void*)&zero, w, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(SysMsgWinWork) / 4);
    w->args = *a;
    w->messageDef = &gCardMessageDefs[w->args.messageId];
    w->glyphPaletteIndex = InitCardMsgGlyphSprites(1, 0);
    FadeSetPaletteExcluded(w->glyphPaletteIndex + 16, 1);
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
    w->textPalette = 0;
    w->unk_142 = 1;
    w->waitIconVisible = 1;
    w->choiceVisible = 0;
    w->textSlotCount = 0;
    w->textSlotCount2 = 0;
    w->messagePending = 0;
    w->unk_146[0] = 1;
#ifdef VERSION_JP
    w->unk_138[3] = LayoutCardMsgGlyphsPageSjis(0x4000, 0x4000, (TextChar*)w->messageDef->text, &w->nextText);
#else
    if (w->nextText != NULL) {
#ifdef VERSION_EU
        switch (gLanguage) {
        case 0:
        case 1:
            w->unk_138[3] = LayoutCardMsgGlyphsPage(0x4D00, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        case 2:
            w->unk_138[3] = LayoutCardMsgGlyphsPage(0x4100, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        case 4:
            w->unk_138[3] = LayoutCardMsgGlyphsPage(0x4400, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        case 3:
            w->unk_138[3] = LayoutCardMsgGlyphsPage(0x4600, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        default:
            w->unk_138[3] = LayoutCardMsgGlyphsPage(0x4D00, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        }
#else
        w->unk_138[3] = LayoutCardMsgGlyphsPage(0x4D00, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
#endif
    } else {
#ifdef VERSION_EU
        switch (gLanguage) {
        case 0:
        case 1:
            w->unk_138[3] = LayoutCardMsgGlyphsPage(0x4D00, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        case 2:
            w->unk_138[3] = LayoutCardMsgGlyphsPage(0x4100, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        case 4:
            w->unk_138[3] = LayoutCardMsgGlyphsPage(0x4400, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        case 3:
            w->unk_138[3] = LayoutCardMsgGlyphsPage(0x4600, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        default:
            w->unk_138[3] = LayoutCardMsgGlyphsPage(0x4D00, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
            break;
        }
#else
        w->unk_138[3] = LayoutCardMsgGlyphsPage(0x4D00, 0x4000, (TextChar*)LANGSTR(w->messageDef->text), &w->nextText);
#endif
    }
#endif
    InitTextSlots(w->textSlots, 10);
    InitTextSlots(w->textSlots2, 10);
    gMessageWindowOpen = 1;
    gMessageWindowAnswerYes = 0;
    w->unk_138[1] = w->unk_138[3];
    gActiveSysmsgwin = w;
}

u8 sysmsgwinChoice_1(SysMsgWinWork* w, void* a) {
    void* pal;
    switch (w->args.mode) {
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
            w->frameX = 0x7800;
            w->frameY = 0x2000;
            break;
        case 1:
        default:
            w->frameX = 0x7800;
            w->frameY = 0x8200;
            break;
        }
        w->tiles2 = LoadObjTiles(gUnk_093F8C8E, 0xC00);
        w->palette4 = LoadObjPalette(gCard00Palette, 32);
        FadeSetPaletteExcluded(w->palette4->index + 16, 1);
        break;
    }
    if (w->args.mode == 0 || w->args.mode == 2) {
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinChoiceSetup);
    }
    return 1;
}

u8 UpdateSysmsgwinChoiceSetup(SysMsgWinWork* w, void* a) {
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
    w->choice = 1;
    w->x = 0x8500;
    w->cursorY = 0x5000;
#ifdef VERSION_EU
    w->textSlotCount = LoadTextSlots(eu_0805E924(&gUnkEu_08890E1C), w->textSlots);
    w->textSlotCount2 = LoadTextSlots(eu_0805E924(&gUnkEu_08890E44), w->textSlots2);
#else
    w->textSlotCount = LoadTextSlots(gUnk_08159E10, w->textSlots);
    w->textSlotCount2 = LoadTextSlots(gUnk_08159E18, w->textSlots2);
#endif
    w->textPalette = LoadTextPalette(1);
    w->choiceVisible = 1;
    w->tiles = LoadObjTiles(gUnk_093F7C9C, 0xFC0);
    w->palette3 = LoadObjPalette(gCard00Palette, 32);
#ifdef VERSION_EU
    FadeSetPaletteExcluded(w->palette3->index + 16, 1);
#else
    FadeSetPaletteExcluded(w->palette4->index + 16, 1);
#endif
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinChoiceInput);
    return 1;
}
s32 UpdateSysmsgwinChoiceClose(SysMsgWinWork* w) {
    if (w->tiles3 != NULL) {
        w->gfx4 = AnimUpdate(&w->anim2);
    }

    w->closeTimer += 1;

    if (w->closeTimer > 15) {
        w->waitIconVisible = 0;
        return 0;
    }

    return 1;
}
u8 UpdateSysmsgwinChoiceInput(SysMsgWinWork* w, void* a) {
    s32 tbl[2];

    *(u64*)tbl = *(u64*)gSysmsgwinChoiceCursorX;
    w->gfx = AnimUpdate(&w->anim3);

    switch (GetKeysPressed()) {
    case DPAD_LEFT:
        if (w->choice != 0) {
            w->choice--;
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        w->cursorSteps = 1;
        break;
    case DPAD_RIGHT:
        if (w->choice == 0) {
            w->choice++;
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        w->cursorSteps = 1;
        break;
    }

    switch (GetKeysPressed()) {
    case A_BUTTON:
    case START_BUTTON:
        m4aSongNumStart(SONG_SYS_KETTEI);

        if (w->choice == 0) {
            gMessageWindowAnswerYes = 1;
        } else {
            gMessageWindowAnswerYes = 0;
        }

        w->unk_142 = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinChoiceClose);
        break;
    case B_BUTTON:
        m4aSongNumStart(SONG_SYS_CLOSE);
        gMessageWindowAnswerYes = 0;
        w->unk_142 = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinChoiceClose);
        break;
    }

    if (w->cursorSteps != 0) {
        ApproachValue(&w->x, tbl[w->choice], w->cursorSteps);
        w->cursorSteps--;
    }

    return 1;
}
void sysmsgwinChoice_2(SysMsgWinWork* w) {
    DrawCardMsgGlyphs(w->unk_138[1]);

    switch (w->args.mode) {
    case 2:
    case 3:
        if (w->tiles2 != NULL) {
            DrawSprite(w->frameX >> 8, w->frameY >> 8, gUnk_09EF1278[0], w->tiles2, w->palette4, 0, 0, 20);
        }
        break;
    }

    if (w->tiles3 != NULL && w->waitIconVisible != 0) {
        DrawSprite(120, gMsgwaitIconPos[w->messageDef->positionIndex][1] >> 8, w->gfx4, w->tiles3, w->palette, 0, 0, 10);
    }

    if (w->tiles4 != NULL) {
        DrawSprite(w->x >> 8, w->cursorY >> 8, w->gfx, w->tiles4, w->palette2, 0, 1, 10);
    }

    DrawTextSlots(89, 86, w->textSlots, w->textPalette, 0, w->textSlotCount);
    DrawTextSlots(135, 86, w->textSlots2, w->textPalette, 0, w->textSlotCount2);
}

void sysmsgwinChoice_3(SysMsgWinWork* w) {
    if (w->args.mode <= 1) {
        DisableBg(w->args.bg);
    }

    FreeCardMsgGlyphSprites();

    if (w->tiles3 != NULL) {
        ReleaseObjTiles(w->tiles3);
    }

    if (w->palette != NULL) {
        ReleaseObjPalette(w->palette);
    }

    if (w->tiles4 != NULL) {
        ReleaseObjTiles(w->tiles4);
    }

    if (w->palette2 != NULL) {
        ReleaseObjPalette(w->palette2);
    }

    if (w->tiles != NULL) {
        ReleaseObjTiles(w->tiles);
    }

    if (w->tiles2 != NULL) {
        ReleaseObjTiles(w->tiles2);
    }

    if (w->palette4 != NULL) {
        ReleaseObjPalette(w->palette4);
    }

    if (w->palette3 != NULL) {
        ReleaseObjPalette(w->palette3);
    }

    if (w->textPalette != NULL) {
        ReleaseObjPalette(w->textPalette);
    }

    FreeTextSlots(w->textSlots, 10);
    FreeTextSlots(w->textSlots2, 10);
    gMessageWindowOpen = 0;
    gActiveSysmsgwin = 0;
}

TaskDesc gTaskDescSysmsgwin = {
    "sysmsgwin",
    (TaskInitFunc)sysmsgwin_0,
    (TaskUpdateFunc)sysmsgwin_1,
    (TaskDrawFunc)sysmsgwin_2,
    (TaskDestroyFunc)sysmsgwin_3,
    sizeof(SysMsgWinWork),
};

TaskDesc gTaskDescSysmsgwinChoice = {
    "sysmsgwin",
    (TaskInitFunc)sysmsgwinChoice_0,
    (TaskUpdateFunc)sysmsgwinChoice_1,
    (TaskDrawFunc)sysmsgwinChoice_2,
    (TaskDestroyFunc)sysmsgwinChoice_3,
    sizeof(SysMsgWinWork),
};

const s32 gSysmsgwinChoiceCursorX[2] = { 0x5000, 0x8000 };
