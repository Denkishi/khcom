/**
 * card_sysmsgwin.c
 * System Message Window
 */

#include "system_state.h"
#include "msg_api.h"
#include "m4a_song.h"
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
#include "key.h"
#include "card.h"
#include "sprites_deck_menu.h"
#include "sprites_evt.h"
#include "sprites_msg.h"
#include "sprites_map.h"
#include "sprites_card.h"
#include "gba/keys.h"
#include "songs.h"
#include "jiminy_data.h"
#include "common_text.h"
#include "card_message_data.h"
#include "types.h"
#include "gba/defines.h"
#include "gba/macro.h"
#include <stddef.h>
#include "card_sysmsgwin.h"
#include "sprite_palettes.h"

static SysMsgWinWork* sActiveSysmsgwin;

static const s32 sSysmsgwinTextY[4] = { 0xE00, 0x6C00, 0xE00, 0x6C00 };

void sysmsgwin_0(SysMsgWinWork* work, CardMessageArgs* a) {
    CpuFill32(0, work, sizeof(SysMsgWinWork));
    work->args = *a;
    work->messageDef = &gCardMessageDefs[work->args.messageId];

    if (work->messageDef->flags & CARD_MSG_FLAG_ALT_HIGHLIGHT) {
        work->glyphPaletteIndex = InitCardMsgGlyphSprites(1, 1);
    } else {
        work->glyphPaletteIndex = InitCardMsgGlyphSprites(1, 0);
    }

    FadeSetPaletteExcluded(work->glyphPaletteIndex + 16, 1);
    work->unk_13C = 0;
    work->steps = 8;
    work->shownChars = 0;
    work->charTimer = 0;
    work->charCount = 0;
    work->unk_143 = 0;
    work->nextText = NULL;
    work->tiles3 = NULL;
    work->palette = NULL;
    work->tiles4 = NULL;
    work->palette2 = NULL;
    work->tiles2 = NULL;
    work->palette4 = NULL;
    work->tiles = NULL;
    work->palette3 = NULL;
    work->textPalette = NULL;
    work->unk_142 = 1;
    work->waitIconVisible = 1;
    work->choiceVisible = 0;
    work->textSlotCount = 0;
    work->textSlotCount2 = 0;
    work->messagePending = 0;
    work->keepOpen = 1;
#ifdef VERSION_JP
    work->charCount = LayoutCardMsgGlyphsPageSjis(0x2E00, gMsgwinTextY[work->messageDef->positionIndex],
                                   (TextChar*)work->messageDef->text, &work->nextText);
#else
    if (work->nextText != NULL) {
        work->charCount = LayoutCardMsgGlyphsPage(0x2E00, sSysmsgwinTextY[work->messageDef->positionIndex] - 0x200,
                                       (TextChar*)LANGSTR(work->messageDef->text), &work->nextText);
    } else {
        work->charCount = LayoutCardMsgGlyphsPage(0x2E00, sSysmsgwinTextY[work->messageDef->positionIndex] - 0x200,
                                       (TextChar*)LANGSTR(work->messageDef->text), &work->nextText);
    }
#endif

    InitTextSlots(work->textSlots, 10);
    InitTextSlots(work->textSlots2, 10);
    gMessageWindowOpen = 1;
    gMessageWindowAnswerYes = 0;
    work->shownChars = work->charCount;

    switch (work->args.mode) {
    case 0:
        work->tiles3 = AllocObjTiles(0x40, NULL);
        work->palette = LoadObjPalette(gBStatesPalette, 32);
        FadeSetPaletteExcluded(work->palette->index + 16, 1);
        SetObjTileSource(work->tiles3, gFEventTiles);
        AnimInit(&work->anim2, gFEventAnims, gFEventFrames);
        AnimStart(&work->anim2, 2, ANIM_FLAG_LOOP);
        work->gfx4 = AnimGetGfx(&work->anim2);
        SetBgPriority(work->args.bg, 0);
        break;
    case 1:
        SetBgPriority(work->args.bg, 0);
        break;
    case 2:
        work->tiles3 = AllocObjTiles(0x40, NULL);
        work->palette = LoadObjPalette(gBStatesPalette, 32);
        FadeSetPaletteExcluded(work->palette->index + 16, 1);
        SetObjTileSource(work->tiles3, gFEventTiles);
        AnimInit(&work->anim2, gFEventAnims, gFEventFrames);
        AnimStart(&work->anim2, 2, ANIM_FLAG_LOOP);
        work->gfx4 = AnimGetGfx(&work->anim2);
        break;
    }

    sActiveSysmsgwin = work;
}

u8 sysmsgwin_1(SysMsgWinWork* work, void* a) {
    void* pal;

    switch (work->args.mode) {
    case 0:
    case 1:
        pal = &gUnk_050001C0[0x20];
        LoadBgTiles(work->args.bg, gSysMsgWinTiles, 0x140);
        LoadBgMap(work->args.bg, gSysMsgWinMap, 0x800);
        LoadPalette(gCard00Palette, pal, 32);

        switch (work->messageDef->positionIndex) {
        case 0:
        case 2:
            SetBgScroll(work->args.bg, (u16)-24, 0);
            break;
        case 1:
        case 3:
            SetBgScroll(work->args.bg, (u16)-24, (u16)-94);
            break;
        default:
            SetBgScroll(work->args.bg, (u16)-24, (u16)-94);
            break;
        }

        break;
    case 2:
    case 3:
        switch (work->messageDef->positionIndex) {
        case 0:
        case 2:
            work->frameX = 0x7800;
            work->frameY = 0x2200;
            break;
        case 1:
        default:
            work->frameX = 0x7800;
            work->frameY = 0x7E00;
            break;
        }

        work->tiles2 = LoadObjTiles(gUnk_093F98AC, 0x1800);

        if (work->tiles2 == NULL) {
            work->fallbackFrame = 1;
            work->tiles2 = LoadObjTiles(gSysMsgWinFallbackTiles, 0x680);
        } else {
            work->fallbackFrame = 0;
        }

        work->palette4 = LoadObjPalette(gCard00Palette, 32);
        FadeSetPaletteExcluded(work->palette4->index + 16, 1);
        break;
    }

    switch (work->args.mode) {
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

u8 UpdateSysmsgwinWaitInput(SysMsgWinWork* work, void* a) {
    u16* pal;

    if (work->tiles3 != NULL) {
        work->gfx4 = AnimUpdate(&work->anim2);
    }

    if (GetKeysPressed() & A_BUTTON) {
        m4aSongNumStart(SONG_SYS_KETTEI);

        if (work->nextText != NULL) {
#ifdef VERSION_JP
            work->charCount = LayoutCardMsgGlyphsPageSjis(0x2E00, gMsgwinTextY[work->messageDef->positionIndex],
                                           work->nextText, &work->nextText);
#else
            work->charCount = LayoutCardMsgGlyphsPage(0x2E00, sSysmsgwinTextY[work->messageDef->positionIndex] - 0x200,
                                           work->nextText, &work->nextText);
#endif
            work->shownChars = work->charCount;
        } else if (!(work->messageDef->flags & CARD_MSG_FLAG_CHOICE_AT_END)) {
            AnimStart(&work->anim2, 3, ANIM_FLAG_LOOP);
            work->unk_142 = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinClose);
            work->closeTimer = 0;
            work->steps = 8;
        } else {
            ReleaseObjTiles(work->tiles3);
            ReleaseObjPalette(work->palette);
            work->tiles3 = NULL;
            work->palette = NULL;
            work->tiles4 = AllocObjTiles(0x120, NULL);
            pal = gUnk_09614418;
            work->palette2 = LoadObjPalette(pal, 32);
#ifdef VERSION_EU
            FadeSetPaletteExcluded(work->palette2->index + 16, 1);
#else
            FadeSetPaletteExcluded(work->palette4->index + 16, 1);
#endif
            LoadObjPaletteBank(work->palette2->index, pal);
            SetObjTileSource(work->tiles4, gHandCursorTiles);
            AnimInit(&work->anim3, gHandCursorAnims, gHandCursorFrames);
            AnimStart(&work->anim3, 2, ANIM_FLAG_LOOP);
            work->gfx = AnimGetGfx(&work->anim3);
            work->choice = 1;
            work->x = 0x5800;
            work->cursorY = gMsgwaitYesnoCursorY[work->choice] - 0x500;
#ifdef VERSION_EU
            work->textSlotCount = LoadTextSlots(GetLocalizedString(&gUnkEu_08890E1C), work->textSlots);
            work->textSlotCount2 = LoadTextSlots(GetLocalizedString(&gUnkEu_08890E44), work->textSlots2);
#else
            work->textSlotCount = LoadTextSlots(gUnk_08159E10, work->textSlots);
            work->textSlotCount2 = LoadTextSlots(gUnk_08159E18, work->textSlots2);
#endif
            work->textPalette = LoadTextPalette(1);
            work->choiceVisible = 1;
            work->tiles = LoadObjTiles(gUnk_093F7C9C, 0xFC0);
            work->palette3 = LoadObjPalette(gCard00Palette, 32);
#ifdef VERSION_EU
            FadeSetPaletteExcluded(work->palette3->index + 16, 1);
#else
            FadeSetPaletteExcluded(work->palette4->index + 16, 1);
#endif
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinChoice);
        }
    }

    return 1;
}

s32 UpdateSysmsgwinClose(SysMsgWinWork* work) {
    if (work->tiles3 != NULL) {
        work->gfx4 = AnimUpdate(&work->anim2);
    }

    work->closeTimer += 1;

    if (work->closeTimer > 15) {
        work->waitIconVisible = 0;
        return 0;
    }

    return 1;
}

u8 UpdateSysmsgwinChoice(SysMsgWinWork* work, void* a) {
    work->gfx = AnimUpdate(&work->anim3);

    switch (GetKeysPressed()) {
    case DPAD_UP:
        if (work->choice != 0) {
            work->choice--;
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        work->cursorSteps = 4;
        break;
    case DPAD_DOWN:
        if (work->choice == 0) {
            work->choice++;
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        work->cursorSteps = 4;
        break;
    case A_BUTTON:
    case START_BUTTON:
        m4aSongNumStart(SONG_SYS_KETTEI);

        if (work->choice == 0) {
            gMessageWindowAnswerYes = 1;
        } else {
            gMessageWindowAnswerYes = 0;
        }

        work->unk_142 = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinClose);
        break;
    }

    if (work->cursorSteps != 0) {
        ApproachValue(&work->cursorY, gMsgwaitYesnoCursorY[work->choice] - 0x500, work->cursorSteps);
        work->cursorSteps--;
    }

    return 1;
}

void sysmsgwin_2(SysMsgWinWork* work) {
    DrawCardMsgGlyphs(work->shownChars);

    switch (work->args.mode) {
    case 2:
    case 3:
        if (work->tiles2 != NULL) {
            if (work->fallbackFrame != 0) {
                DrawSprite(work->frameX >> 8, work->frameY >> 8, (&gUnk_09EF12E8[2])[0],
                           work->tiles2, work->palette4, NULL, 0, 10);
            } else {
                DrawSprite(work->frameX >> 8, work->frameY >> 8, (&gUnk_09EF1278[2])[0],
                           work->tiles2, work->palette4, NULL, 0, 10);
            }
        }

        break;
    }

    if (work->tiles3 != NULL) {
        if (work->waitIconVisible) {
            DrawSprite(120, gMsgwaitIconPos[work->messageDef->positionIndex][1] >> 8, work->gfx4,
                       work->tiles3, work->palette, NULL, 0, 5);
        }
    }

    if (work->tiles4 != NULL) {
        DrawSprite(work->x >> 8, work->cursorY >> 8, work->gfx,
                   work->tiles4, work->palette2, NULL, SPRITE_FLAG_HFLIP, 5);
    }

    if (work->choiceVisible) {
        DrawSprite(120, 75, gUnk_09EF126C[1], work->tiles, work->palette3, NULL, 0, 10);
        DrawTextSlots((240 - GetTextSlotsWidth(work->textSlots, work->textSlotCount)) >> 1, 62, work->textSlots,
                      work->textPalette, 0, work->textSlotCount);
        DrawTextSlots((240 - GetTextSlotsWidth(work->textSlots2, work->textSlotCount2)) >> 1, 77, work->textSlots2,
                      work->textPalette, 0, work->textSlotCount2);
    }
}

void sysmsgwin_3(SysMsgWinWork* work) {
    if (work->args.mode <= 1) {
        DisableBg(work->args.bg);
    }

    FreeCardMsgGlyphSprites();

    if (work->tiles3 != NULL) {
        ReleaseObjTiles(work->tiles3);
    }

    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
    }

    if (work->tiles4 != NULL) {
        ReleaseObjTiles(work->tiles4);
    }

    if (work->palette2 != NULL) {
        ReleaseObjPalette(work->palette2);
    }

    if (work->tiles != NULL) {
        ReleaseObjTiles(work->tiles);
    }

    if (work->tiles2 != NULL) {
        ReleaseObjTiles(work->tiles2);
    }

    if (work->palette4 != NULL) {
        ReleaseObjPalette(work->palette4);
    }

    if (work->palette3 != NULL) {
        ReleaseObjPalette(work->palette3);
    }

    if (work->textPalette != NULL) {
        ReleaseObjPalette(work->textPalette);
    }

    FreeTextSlots(work->textSlots, 10);
    FreeTextSlots(work->textSlots2, 10);
    gMessageWindowOpen = 0;
    sActiveSysmsgwin = NULL;
}

u8 UpdateSysmsgwinPersistent(SysMsgWinWork* work, void* a) {
#ifndef VERSION_JP
    TextChar** p;
#endif

    if (work->keepOpen == 0) {
        return 0;
    }

    if (work->messagePending == 1) {
        work->messagePending = 0;
        work->messageDef = &gCardMessageDefs[work->args.messageId];
#ifdef VERSION_JP
        work->charCount = LayoutCardMsgGlyphsPageSjis(
            0x2E00,
            gMsgwinTextY[work->messageDef->positionIndex],
            (TextChar*)(work->messageDef->text),
            &work->nextText);
#else
        p = &work->nextText;

        if (*p != NULL) {
            work->charCount = LayoutCardMsgGlyphsPage(
                0x2E00,
                sSysmsgwinTextY[work->messageDef->positionIndex] - 0x200,
                *p, p);
        } else {
            work->charCount = LayoutCardMsgGlyphsPage(
                0x2E00,
                sSysmsgwinTextY[work->messageDef->positionIndex] - 0x200,
                (TextChar*)LANGSTR(work->messageDef->text),
                p);
        }
#endif

        work->shownChars = work->charCount;
    }

    return 1;
}

s32 ReplaceSysmsgwinMessage(CardMessageArgs* src) {
    if (sActiveSysmsgwin != NULL) {
        sActiveSysmsgwin->args = *src;
        sActiveSysmsgwin->messagePending = 1;

        return 1;
    }

    return 0;
}

s32 CloseSysmsgwin() {
    if (sActiveSysmsgwin != NULL) {
        sActiveSysmsgwin->keepOpen = 0;
        return 1;
    }

    return 0;
}

void sysmsgwinChoice_0(SysMsgWinWork* work, CardMessageArgs* a) {
    CpuFill32(0, work, sizeof(SysMsgWinWork));
    work->args = *a;
    work->messageDef = &gCardMessageDefs[work->args.messageId];
    work->glyphPaletteIndex = InitCardMsgGlyphSprites(1, 0);
    FadeSetPaletteExcluded(work->glyphPaletteIndex + 16, 1);
    work->unk_13C = 0;
    work->steps = 8;
    work->shownChars = 0;
    work->charTimer = 0;
    work->charCount = 0;
    work->unk_143 = 0;
    work->nextText = NULL;
    work->tiles3 = NULL;
    work->palette = NULL;
    work->tiles4 = NULL;
    work->palette2 = NULL;
    work->tiles2 = NULL;
    work->palette4 = NULL;
    work->tiles = NULL;
    work->palette3 = NULL;
    work->textPalette = NULL;
    work->unk_142 = 1;
    work->waitIconVisible = 1;
    work->choiceVisible = 0;
    work->textSlotCount = 0;
    work->textSlotCount2 = 0;
    work->messagePending = 0;
    work->keepOpen = 1;
#ifdef VERSION_JP
    work->charCount = LayoutCardMsgGlyphsPageSjis(0x4000, 0x4000, (TextChar*)work->messageDef->text, &work->nextText);
#else
    if (work->nextText != NULL) {
#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
        case LANGUAGE_FRENCH:
            work->charCount = LayoutCardMsgGlyphsPage(0x4D00, 0x4000, (TextChar*)LANGSTR(work->messageDef->text), &work->nextText);
            break;
        case LANGUAGE_GERMAN:
            work->charCount = LayoutCardMsgGlyphsPage(0x4100, 0x4000, (TextChar*)LANGSTR(work->messageDef->text), &work->nextText);
            break;
        case LANGUAGE_SPANISH:
            work->charCount = LayoutCardMsgGlyphsPage(0x4400, 0x4000, (TextChar*)LANGSTR(work->messageDef->text), &work->nextText);
            break;
        case LANGUAGE_ITALIAN:
            work->charCount = LayoutCardMsgGlyphsPage(0x4600, 0x4000, (TextChar*)LANGSTR(work->messageDef->text), &work->nextText);
            break;
        default:
            work->charCount = LayoutCardMsgGlyphsPage(0x4D00, 0x4000, (TextChar*)LANGSTR(work->messageDef->text), &work->nextText);
            break;
        }
#else
        work->charCount = LayoutCardMsgGlyphsPage(0x4D00, 0x4000, (TextChar*)LANGSTR(work->messageDef->text), &work->nextText);
#endif
    } else {
#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
        case LANGUAGE_FRENCH:
            work->charCount = LayoutCardMsgGlyphsPage(0x4D00, 0x4000, (TextChar*)LANGSTR(work->messageDef->text), &work->nextText);
            break;
        case LANGUAGE_GERMAN:
            work->charCount = LayoutCardMsgGlyphsPage(0x4100, 0x4000, (TextChar*)LANGSTR(work->messageDef->text), &work->nextText);
            break;
        case LANGUAGE_SPANISH:
            work->charCount = LayoutCardMsgGlyphsPage(0x4400, 0x4000, (TextChar*)LANGSTR(work->messageDef->text), &work->nextText);
            break;
        case LANGUAGE_ITALIAN:
            work->charCount = LayoutCardMsgGlyphsPage(0x4600, 0x4000, (TextChar*)LANGSTR(work->messageDef->text), &work->nextText);
            break;
        default:
            work->charCount = LayoutCardMsgGlyphsPage(0x4D00, 0x4000, (TextChar*)LANGSTR(work->messageDef->text), &work->nextText);
            break;
        }
#else
        work->charCount = LayoutCardMsgGlyphsPage(0x4D00, 0x4000, (TextChar*)LANGSTR(work->messageDef->text), &work->nextText);
#endif
    }
#endif

    InitTextSlots(work->textSlots, 10);
    InitTextSlots(work->textSlots2, 10);
    gMessageWindowOpen = 1;
    gMessageWindowAnswerYes = 0;
    work->shownChars = work->charCount;
    sActiveSysmsgwin = work;
}

u8 sysmsgwinChoice_1(SysMsgWinWork* work, void* a) {
    void* pal;

    switch (work->args.mode) {
    case 0:
    case 1:
        pal = (void*)(BG_PLTT + 15 * PLTT_SIZE_4BPP);
        LoadBgTiles(work->args.bg, gConfirmWinTiles, 0x140);
        LoadBgMap(work->args.bg, gConfirmWinMap, 0x800);
        LoadPalette(gCard00Palette, pal, 32);

        switch (work->messageDef->positionIndex) {
        case 0:
        case 2:
            SetBgScroll(work->args.bg, 0, 0);
            break;
        case 1:
        case 3:
            SetBgScroll(work->args.bg, 0, 0);
            break;
        default:
            SetBgScroll(work->args.bg, 0, 0);
            break;
        }

        break;
    case 2:
    case 3:
        switch (work->messageDef->positionIndex) {
        case 0:
        case 2:
            work->frameX = 0x7800;
            work->frameY = 0x2000;
            break;
        case 1:
        default:
            work->frameX = 0x7800;
            work->frameY = 0x8200;
            break;
        }

        work->tiles2 = LoadObjTiles(gUnk_093F8C8E, 0xC00);
        work->palette4 = LoadObjPalette(gCard00Palette, 32);
        FadeSetPaletteExcluded(work->palette4->index + 16, 1);
        break;
    }

    if (work->args.mode == 0 || work->args.mode == 2) {
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinChoiceSetup);
    }

    return 1;
}

u8 UpdateSysmsgwinChoiceSetup(SysMsgWinWork* work, void* a) {
    u16* pal;

    work->tiles4 = AllocObjTiles(0x120, NULL);
    pal = gUnk_09614418;
    work->palette2 = LoadObjPalette(pal, 32);
#ifdef VERSION_EU
    FadeSetPaletteExcluded(work->palette2->index + 16, 1);
#else
    FadeSetPaletteExcluded(work->palette4->index + 16, 1);
#endif
    LoadObjPaletteBank(work->palette2->index, pal);
    SetObjTileSource(work->tiles4, gHandCursorTiles);
    AnimInit(&work->anim3, gHandCursorAnims, gHandCursorFrames);
    AnimStart(&work->anim3, 2, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim3);
    work->choice = 1;
    work->x = 0x8500;
    work->cursorY = 0x5000;
#ifdef VERSION_EU
    work->textSlotCount = LoadTextSlots(GetLocalizedString(&gUnkEu_08890E1C), work->textSlots);
    work->textSlotCount2 = LoadTextSlots(GetLocalizedString(&gUnkEu_08890E44), work->textSlots2);
#else
    work->textSlotCount = LoadTextSlots(gUnk_08159E10, work->textSlots);
    work->textSlotCount2 = LoadTextSlots(gUnk_08159E18, work->textSlots2);
#endif
    work->textPalette = LoadTextPalette(1);
    work->choiceVisible = 1;
    work->tiles = LoadObjTiles(gUnk_093F7C9C, 0xFC0);
    work->palette3 = LoadObjPalette(gCard00Palette, 32);
#ifdef VERSION_EU
    FadeSetPaletteExcluded(work->palette3->index + 16, 1);
#else
    FadeSetPaletteExcluded(work->palette4->index + 16, 1);
#endif
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinChoiceInput);
    return 1;
}

s32 UpdateSysmsgwinChoiceClose(SysMsgWinWork* work) {
    if (work->tiles3 != NULL) {
        work->gfx4 = AnimUpdate(&work->anim2);
    }

    work->closeTimer += 1;

    if (work->closeTimer > 15) {
        work->waitIconVisible = 0;
        return 0;
    }

    return 1;
}

u8 UpdateSysmsgwinChoiceInput(SysMsgWinWork* work, void* a) {
    s32 tbl[2];

    *(u64*)tbl = *(u64*)gSysmsgwinChoiceCursorX;
    work->gfx = AnimUpdate(&work->anim3);

    switch (GetKeysPressed()) {
    case DPAD_LEFT:
        if (work->choice != 0) {
            work->choice--;
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        work->cursorSteps = 1;
        break;
    case DPAD_RIGHT:
        if (work->choice == 0) {
            work->choice++;
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        work->cursorSteps = 1;
        break;
    }

    switch (GetKeysPressed()) {
    case A_BUTTON:
    case START_BUTTON:
        m4aSongNumStart(SONG_SYS_KETTEI);

        if (work->choice == 0) {
            gMessageWindowAnswerYes = 1;
        } else {
            gMessageWindowAnswerYes = 0;
        }

        work->unk_142 = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinChoiceClose);
        break;
    case B_BUTTON:
        m4aSongNumStart(SONG_SYS_CLOSE);
        gMessageWindowAnswerYes = 0;
        work->unk_142 = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateSysmsgwinChoiceClose);
        break;
    }

    if (work->cursorSteps != 0) {
        ApproachValue(&work->x, tbl[work->choice], work->cursorSteps);
        work->cursorSteps--;
    }

    return 1;
}

void sysmsgwinChoice_2(SysMsgWinWork* work) {
    DrawCardMsgGlyphs(work->shownChars);

    switch (work->args.mode) {
    case 2:
    case 3:
        if (work->tiles2 != NULL) {
            DrawSprite(work->frameX >> 8, work->frameY >> 8, gUnk_09EF1278[0], work->tiles2, work->palette4, NULL, 0, 20);
        }

        break;
    }

    if (work->tiles3 != NULL && work->waitIconVisible) {
        DrawSprite(120, gMsgwaitIconPos[work->messageDef->positionIndex][1] >> 8, work->gfx4, work->tiles3, work->palette, NULL, 0, 10);
    }

    if (work->tiles4 != NULL) {
        DrawSprite(work->x >> 8, work->cursorY >> 8, work->gfx, work->tiles4, work->palette2, NULL, SPRITE_FLAG_HFLIP, 10);
    }

    DrawTextSlots(89, 86, work->textSlots, work->textPalette, 0, work->textSlotCount);
    DrawTextSlots(135, 86, work->textSlots2, work->textPalette, 0, work->textSlotCount2);
}

void sysmsgwinChoice_3(SysMsgWinWork* work) {
    if (work->args.mode <= 1) {
        DisableBg(work->args.bg);
    }

    FreeCardMsgGlyphSprites();

    if (work->tiles3 != NULL) {
        ReleaseObjTiles(work->tiles3);
    }

    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
    }

    if (work->tiles4 != NULL) {
        ReleaseObjTiles(work->tiles4);
    }

    if (work->palette2 != NULL) {
        ReleaseObjPalette(work->palette2);
    }

    if (work->tiles != NULL) {
        ReleaseObjTiles(work->tiles);
    }

    if (work->tiles2 != NULL) {
        ReleaseObjTiles(work->tiles2);
    }

    if (work->palette4 != NULL) {
        ReleaseObjPalette(work->palette4);
    }

    if (work->palette3 != NULL) {
        ReleaseObjPalette(work->palette3);
    }

    if (work->textPalette != NULL) {
        ReleaseObjPalette(work->textPalette);
    }

    FreeTextSlots(work->textSlots, 10);
    FreeTextSlots(work->textSlots2, 10);
    gMessageWindowOpen = 0;
    sActiveSysmsgwin = NULL;
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
