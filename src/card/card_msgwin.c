/**
 * card_msgwin.c
 * Card Message Window
 */

#include "macros.h"
#include "msg_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "msg_api.h"
#include "m4a_song.h"
#include "text.h"
#include "monsgage.h"
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
#include "sprites_card.h"
#include "gba/keys.h"
#include "songs.h"
#include "card_message_text.h"
#include "event_text.h"
#include "jiminy_data.h"
#include "common_text.h"
#include "card_api.h"
#include "card_message_data.h"
#include "msg_portrait_data.h"
#include "sprite_palettes.h"
#include "types.h"
#include "gba/macro.h"
#include <stddef.h>
#include "card_msgwin.h"

static CardMsgWinWork* sActiveCardMsgwin;

u8 gMessageWindowOpen EWRAM_COMMON(4);

u8 gMessageWindowAnswerYes EWRAM_COMMON(4);

static void msgwin_0(CardMsgWinWork* work, CardMessageArgs* a) {
    CpuFill32(0, work, sizeof(CardMsgWinWork));
    work->glyphPaletteIndex = InitCardMsgGlyphSprites(0, 0);
    work->args = *a;
    work->messageDef = &gCardMessageDefs[work->args.messageId];
    work->tiles3 = NULL;
    work->palette = NULL;
    work->tiles4 = NULL;
    work->palette2 = NULL;
    work->tiles = NULL;
    work->palette3 = NULL;
    work->tiles2 = NULL;
    work->palette4 = NULL;
    work->textPalette = NULL;
    work->x = gMsgwinClosedScrollX[work->messageDef->positionIndex];
    work->faceX = 0;
    work->faceY = 0;
    work->cursorX = 0;
    work->cursorY = 0;
    work->gfx = NULL;
    work->gfx2 = NULL;
    work->gfx3 = NULL;
    work->nextText = NULL;
    work->glyphPaletteIndex = 0;
    work->closeTimer = 0;
    work->steps = 8;
    work->shownChars = 0;
    work->charTimer = 0;
    work->charCount = 0;
    work->choice = 0;
    work->cursorSteps = 0;
    work->textSlotCounts[0] = 0;
    work->textSlotCounts[1] = 0;
    work->waitIconVisible = 1;
    work->textVisible = 0;
    work->unk_14A[0] = 0;
    work->unk_14A[1] = 0;
    work->unk_14C = 0;
    work->faceFlip = 0;
    work->messagePending = 0;
    work->keepOpen = 1;

    switch (work->messageDef->positionIndex) {
    case 0:
    case 1:
        work->faceFlip = 1;
        break;
    case 2:
    case 3:
        work->faceFlip = 0;
        break;
    }

    gMessageWindowOpen = 1;
    gMessageWindowAnswerYes = 0;
    SetBgScroll(work->args.bg, 0, 0);

    switch (work->args.mode) {
    case 0:
    case 1:
        SetBgPriority(work->args.bg, 0);
        break;
    case 2:
    case 3:
        break;
    }

    sActiveCardMsgwin = work;
}

u8 UpdateCardMsgwinOpen(CardMsgWinWork* work, void* a) {
    const MsgFaceAnim* tbl;

    ApproachValue(&work->x, gMsgwinOpenScrollX[work->messageDef->positionIndex], work->steps);
    ApproachValue(&work->faceX, gMsgfaceShownX[work->messageDef->positionIndex], work->steps);
    ScrollBgMapTo(work->args.bg, work->x, 0);
    work->gfx = AnimUpdate(&work->anim);

    if (work->steps != 0) {
        work->steps--;
    } else {
        tbl = gMsgFaceAnims[work->messageDef->portraitId];

        if (tbl[work->messageDef->expressionId].animCount > 1) {
            AnimStart(&work->anim, 1, tbl[work->messageDef->expressionId].animFlags);
        }

        switch (work->args.mode) {
        case 0:
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateCardMsgwinTyping);
            break;
        case 1:
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateCardMsgwinTypingPersistent);
            break;
        }
    }

    return 1;
}

static u8 msgwin_1(CardMsgWinWork* work, void* a) {
    LoadBgTiles(work->args.bg, gMsgwinTiles, 1280);
    LoadBgPalette(work->args.bg, gMsgwinPalette, 32);
    SetBgMapBlocks(work->args.bg, gMsgwinMapBlocks[work->messageDef->positionIndex], 2, 1);
    ScrollBgMapTo(work->args.bg, work->x, 0);
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateCardMsgwinLoadText);
    return 1;
}

u8 UpdateCardMsgwinLoadText(CardMsgWinWork* work, void* a) {
#ifdef VERSION_JP
    work->charCount = LayoutCardMsgGlyphsPageSjis(gMsgwinTextX[work->messageDef->positionIndex],
                               gMsgwinTextY[work->messageDef->positionIndex],
                               (TextChar*)work->messageDef->text,
                               &work->nextText);
#else
    TextChar** p;

    p = &work->nextText;

    if (*p != NULL) {
        work->charCount = LayoutCardMsgGlyphsPage(gMsgwinTextX[work->messageDef->positionIndex],
                                   gMsgwinTextY[work->messageDef->positionIndex] - 0x200,
                                   *p, p);
    } else {
        work->charCount = LayoutCardMsgGlyphsPage(gMsgwinTextX[work->messageDef->positionIndex],
                                   gMsgwinTextY[work->messageDef->positionIndex] - 0x200,
                                   (TextChar*)LANGSTR(work->messageDef->text), p);
    }
#endif

    InitTextSlots(work->textSlots, 10);
    InitTextSlots(work->textSlots2, 10);
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateCardMsgwinLoadFace);

    return 1;
}

u8 UpdateCardMsgwinLoadFace(CardMsgWinWork* work, void* a) {
    CardMessageDef* sel;
    const MsgFaceAnim* e;

    work->textVisible = 1;
    sel = work->messageDef;

    if (sel->portraitId != 62) {
        e = gMsgFaceAnims[sel->portraitId];
        work->tiles3 = AllocObjTiles(0xD80, NULL);
        work->palette = LoadObjPalette(e[work->messageDef->expressionId].palette, 32);
        SetObjTileSource(work->tiles3, e[work->messageDef->expressionId].tiles);
        AnimInit(&work->anim, e[work->messageDef->expressionId].anims, e[work->messageDef->expressionId].gfxTable);
        AnimStart(&work->anim, 0, e[work->messageDef->expressionId].animFlags);
        work->gfx = AnimGetGfx(&work->anim);
        work->faceX = gMsgfaceHiddenX[work->messageDef->positionIndex];
        work->faceY = gMsgfaceY[work->messageDef->positionIndex];
    } else {
        work->tiles3 = NULL;
        work->palette = NULL;
    }

    SetTaskUpdate(a, (TaskUpdateFunc)UpdateCardMsgwinOpen);
    return 1;
}

static void msgwin_2(CardMsgWinWork* work) {
    void** p;

    if (work->textVisible) {
        DrawCardMsgGlyphs(work->shownChars);
    }

    if (work->tiles3 != NULL) {
        if (work->faceFlip) {
            DrawSprite(work->faceX >> 8, work->faceY >> 8, work->gfx, work->tiles3, work->palette, NULL, SPRITE_FLAG_HFLIP, 0);
        } else {
            DrawSprite(work->faceX >> 8, work->faceY >> 8, work->gfx, work->tiles3, work->palette, NULL, 0, 0);
        }

        if (work->tiles4 != NULL && work->waitIconVisible) {
            DrawSprite(gMsgwaitIconPos[work->messageDef->positionIndex][0] >> 8, gMsgwaitIconPos[work->messageDef->positionIndex][1] >> 8,
                       work->gfx2, work->tiles4, work->palette2, NULL, 0, 10);
        }
    }

    if (work->tiles != NULL) {
        DrawSprite(work->cursorX >> 8, work->cursorY >> 8, work->gfx3, work->tiles, work->palette3, NULL, SPRITE_FLAG_HFLIP, 9);
    }

    if (work->tiles2 != NULL) {
        p = gMsgBoxFrames;
        DrawSprite(120, 80, p[1], work->tiles2, work->palette4, NULL, 0, 10);
        DrawTextSlots((240 - work->textSlotCounts[0] * 10) >> 1, 67, work->textSlots, work->textPalette, 0, work->textSlotCounts[0]);
        DrawTextSlots((240 - work->textSlotCounts[1] * 10) >> 1, 82, work->textSlots2, work->textPalette, 0, work->textSlotCounts[1]);
    }
}

static void msgwin_3(CardMsgWinWork* work) {
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

    if (work->palette3 != NULL) {
        ReleaseObjPalette(work->palette3);
    }

    if (work->tiles2 != NULL) {
        ReleaseObjTiles(work->tiles2);
    }

    if (work->palette4 != NULL) {
        ReleaseObjPalette(work->palette4);
    }

    if (work->textPalette != NULL) {
        ReleaseObjPalette(work->textPalette);
    }

    FreeTextSlots(work->textSlots, 10);
    FreeTextSlots(work->textSlots2, 10);
    gMessageWindowOpen = 0;
    sActiveCardMsgwin = NULL;
}

u8 UpdateCardMsgwinTyping(CardMsgWinWork* work, void* a) {
    CardMessageDef* sel;
    const MsgFaceAnim* e;

    work->gfx = AnimUpdate(&work->anim);

    if (GetKeysPressed() & A_BUTTON) {
        work->shownChars = work->charCount;
    }

    work->charTimer++;
    sel = work->messageDef;

    if (work->charTimer >= sel->charDelay) {
        if (work->shownChars < work->charCount) {
            work->shownChars++;
            m4aSongNumStart(SONG_SYS_MESSAGE);
        } else {
            e = gMsgFaceAnims[sel->portraitId];
            AnimStart(&work->anim, 0, e[sel->expressionId].animFlags);

            if (work->tiles4 == NULL) {
                work->tiles4 = AllocObjTiles(0x40, NULL);
                work->palette2 = LoadObjPalette(gCommonObjPalette, 32);
                SetObjTileSource(work->tiles4, gFEventTiles);
                AnimInit(&work->anim2, gFEventAnims, gFEventFrames);
                AnimStart(&work->anim2, 2, ANIM_FLAG_LOOP);
                work->gfx2 = AnimGetGfx(&work->anim2);
            }

            work->waitIconVisible = 1;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateCardMsgwinWaitInput);
        }

        work->charTimer = 0;
    }

    return 1;
}

u8 UpdateCardMsgwinWaitInput(CardMsgWinWork* work, void* a) {
    const MsgFaceAnim* e;
    u16* pal;

    work->gfx2 = AnimUpdate(&work->anim2);
    work->gfx = AnimUpdate(&work->anim);

    if (GetKeysPressed() & A_BUTTON) {
        m4aSongNumStart(SONG_SYS_KETTEI);

        if (work->nextText != NULL) {
#ifdef VERSION_JP
            *((u8*)work + offsetof(CardMsgWinWork, charCount)) = LayoutCardMsgGlyphsPageSjis(gMsgwinTextX[work->messageDef->positionIndex],
                                      gMsgwinTextY[work->messageDef->positionIndex],
                                      work->nextText, &work->nextText);
#else
            *((u8*)work + offsetof(CardMsgWinWork, charCount)) = LayoutCardMsgGlyphsPage(gMsgwinTextX[work->messageDef->positionIndex],
                                      gMsgwinTextY[work->messageDef->positionIndex] - 0x200,
                                      work->nextText, &work->nextText);
#endif
            work->charTimer = 0;
            work->shownChars = 0;
            e = gMsgFaceAnims[work->messageDef->portraitId];

            if (e[work->messageDef->expressionId].animCount > 1) {
                AnimStart(&work->anim, 1, e[work->messageDef->expressionId].animFlags);
            }

            work->waitIconVisible = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateCardMsgwinTyping);
        } else if (!(work->messageDef->flags & CARD_MSG_FLAG_CHOICE_AT_END)) {
            AnimStart(&work->anim2, 3, ANIM_FLAG_LOOP);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateCardMsgwinClose);
            work->closeTimer = 0;
            work->steps = 8;
        } else {
            ReleaseObjTiles(work->tiles4);
            ReleaseObjPalette(work->palette2);
            work->tiles4 = NULL;
            work->palette2 = NULL;
            work->tiles = AllocObjTiles(0x120, NULL);
            pal = gDialogBoxPalette;
            work->palette3 = LoadObjPalette(pal, 32);
            LoadObjPaletteBank(work->palette3->index, pal);
            SetObjTileSource(work->tiles, gHandCursorTiles);
            AnimInit(&work->anim3, gHandCursorAnims, gHandCursorFrames);
            AnimStart(&work->anim3, 2, ANIM_FLAG_LOOP);
            work->gfx3 = AnimGetGfx(&work->anim3);
            work->tiles2 = LoadObjTiles(gMsgBoxTiles, 0xFC0);
            work->palette4 = LoadObjPalette(gCard00Palette, 32);
            work->choice = 0;
            work->cursorX = 0x5800;
            work->cursorY = gMsgwaitYesnoCursorY[work->choice];
#ifdef VERSION_EU
            work->textSlotCounts[0] = LoadTextSlots(GetLocalizedString(&gYesChoiceTextByLanguage), work->textSlots);
            work->textSlotCounts[1] = LoadTextSlots(GetLocalizedString(&gNoChoiceTextByLanguage), work->textSlots2);
#else
            work->textSlotCounts[0] = LoadTextSlots(gYesChoiceText, work->textSlots);
            work->textSlotCounts[1] = LoadTextSlots(gNoChoiceText, work->textSlots2);
#endif
            work->textPalette = LoadTextPalette(1);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateCardMsgwinChoice);
        }
    }

    return 1;
}

u8 UpdateCardMsgwinClose(CardMsgWinWork* work) {
    if (work->tiles4 != NULL) {
        work->gfx2 = AnimUpdate(&work->anim2);
    }

    work->gfx = AnimUpdate(&work->anim);
    work->closeTimer++;

    if (work->closeTimer > 15) {
        work->textVisible = 0;
        work->waitIconVisible = 0;
        ApproachValue(&work->x, gMsgwinClosedScrollX[work->messageDef->positionIndex], work->steps);
        ApproachValue(&work->faceX, gMsgfaceHiddenX[work->messageDef->positionIndex], work->steps);
        ScrollBgMapTo(work->args.bg, work->x, 0);

        if (work->steps == 0) {
            return 0;
        }

        work->steps--;
    }

    return 1;
}

u8 UpdateCardMsgwinChoice(CardMsgWinWork* work, void* a) {
    work->gfx = AnimUpdate(&work->anim);
    work->gfx3 = AnimUpdate(&work->anim3);

    switch (GetKeysRepeat()) {
    case DPAD_UP:
    case DPAD_DOWN:
        work->choice ^= 1;
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

        SetTaskUpdate(a, (TaskUpdateFunc)UpdateCardMsgwinClose);
        break;
    }

    if (work->cursorSteps != 0) {
        ApproachValue(&work->cursorY, gMsgwaitYesnoCursorY[work->choice], work->cursorSteps);
        work->cursorSteps--;
    }

    return 1;
}

u8 UpdateCardMsgwinTypingPersistent(CardMsgWinWork* work, void* a) {
    const MsgFaceAnim* e;

    work->gfx = AnimUpdate(&work->anim);

    if (GetKeysPressed() & A_BUTTON) {
        work->shownChars = work->charCount;
    }

    work->charTimer++;

    if (work->charTimer >= work->messageDef->charDelay) {
        if (work->shownChars < work->charCount) {
            work->shownChars++;
            m4aSongNumStart(SONG_SYS_MESSAGE);
        } else {
            e = gMsgFaceAnims[work->messageDef->portraitId];
            AnimStart(&work->anim, 0, e[work->messageDef->expressionId].animFlags);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateCardMsgwinPersistent);
        }

        work->charTimer = 0;
    }

    return 1;
}

u8 UpdateCardMsgwinPersistent(CardMsgWinWork* work, void* a) {
#ifndef VERSION_JP
    TextChar** p;
#endif
    work->gfx = AnimUpdate(&work->anim);

    if (!work->keepOpen) {
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateCardMsgwinClose);
    } else if (work->messagePending == 1) {
        work->messagePending = 0;
        work->messageDef = &gCardMessageDefs[work->args.messageId];
#ifdef VERSION_JP
        work->charCount = LayoutCardMsgGlyphsPageSjis(gMsgwinTextX[work->messageDef->positionIndex],
                                   gMsgwinTextY[work->messageDef->positionIndex],
                                   (TextChar*)work->messageDef->text, &work->nextText);
#else
        p = &work->nextText;

        if (*p != NULL) {
            work->charCount = LayoutCardMsgGlyphsPage(gMsgwinTextX[work->messageDef->positionIndex],
                                       gMsgwinTextY[work->messageDef->positionIndex] - 0x200, *p, p);
        } else {
            work->charCount = LayoutCardMsgGlyphsPage(gMsgwinTextX[work->messageDef->positionIndex],
                                       gMsgwinTextY[work->messageDef->positionIndex] - 0x200,
                                       (TextChar*)LANGSTR(work->messageDef->text), p);
        }
#endif

        work->shownChars = work->charCount;
    }

    return 1;
}

s32 ReplaceCardMsgwinMessage(CardMessageArgs* src) {
    if (sActiveCardMsgwin != NULL) {
        sActiveCardMsgwin->args = *src;
        sActiveCardMsgwin->messagePending = 1;

        return 1;
    }

    return 0;
}

void CreateCardMessageTask(void* pool, u32 a, u16 b) {
    CardMessageArgs args;

    args.bg = a;
    args.messageId = b;
    args.mode = 0;

    if (gCardMessageDefs[b].portraitId == 62) {
        if (gCardMessageDefs[b].flags & CARD_MSG_FLAG_CHOICE_WINDOW) {
            TaskCreate(pool, &gTaskDescSysmsgwinChoice, &args);
        } else {
            TaskCreate(pool, &gTaskDescSysmsgwin, &args);
        }
    } else {
        TaskCreate(pool, &gTaskDescCardMsgwin, &args);
    }
}

void CreateSysmsgwinTask(void* pool, u16 b) {
    CardMessageArgs args;

    args.bg = 0;
    args.messageId = b;
    args.mode = 2;

    if (gCardMessageDefs[b].flags & CARD_MSG_FLAG_CHOICE_WINDOW) {
        TaskCreate(pool, &gTaskDescSysmsgwinChoice, &args);
    } else {
        TaskCreate(pool, &gTaskDescSysmsgwin, &args);
    }
}

void CreatePersistentSysmsgwinTask(void* pool, u16 a) {
    CardMessageArgs args;

    IsMessageWindowOpen();
    args.bg = 0;
    args.messageId = a;
    args.mode = 3;
    TaskCreate(pool, &gTaskDescSysmsgwin, &args);
}

void ShowPersistentCardMessage(void* pool, u32 a, u16 b) {
    CardMessageArgs args;

    args.bg = a;
    args.messageId = b;
    args.mode = 1;

    if (IsMessageWindowOpen()) {
        if (!(u8)ReplaceCardMsgwinMessage(&args)) {
            ReplaceSysmsgwinMessage(&args);
        }
    } else if (gCardMessageDefs[b].portraitId == 62) {
        TaskCreate(pool, &gTaskDescSysmsgwin, &args);
    } else {
        TaskCreate(pool, &gTaskDescCardMsgwin, &args);
    }
}

void ResetMessageWindowFlags() {
    gMessageWindowOpen = 0;
    gMessageWindowAnswerYes = 0;
}

u8 IsMessageWindowOpen() {
    return gMessageWindowOpen;
}

u8 IsMessageWindowAnswerYes() {
    return gMessageWindowAnswerYes;
}

u8 CloseMessageWindow() {
    if (sActiveCardMsgwin != NULL) {
        sActiveCardMsgwin->keepOpen = 0;
        return 1;
    }

    return CloseSysmsgwin();
}

CardMessageDef gCardMessageDefs[] = {
    {
        1, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText000ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText00,
#elif defined(VERSION_US)
        gDonaldTalkText00,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText001ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText01,
#elif defined(VERSION_US)
        gDonaldTalkText01,
#endif
        0,
    },
    {
        1, 3, 4, 3,
#if defined(VERSION_EU)
        &gCardMessageText002ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText02,
#elif defined(VERSION_US)
        gDonaldTalkText02,
#endif
        0,
    },
    {
        1, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText003ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText03,
#elif defined(VERSION_US)
        gDonaldTalkText03,
#endif
        0,
    },
    {
        1, 3, 3, 3,
#if defined(VERSION_EU)
        &gCardMessageText004ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText04,
#elif defined(VERSION_US)
        gDonaldTalkText04,
#endif
        0,
    },
    {
        1, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText005ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText05,
#elif defined(VERSION_US)
        gDonaldTalkText05,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText006ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText06,
#elif defined(VERSION_US)
        gDonaldTalkText06,
#endif
        0,
    },
    {
        1, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText007ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText07,
#elif defined(VERSION_US)
        gDonaldTalkText07,
#endif
        0,
    },
    {
        1, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText008ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText08,
#elif defined(VERSION_US)
        gDonaldTalkText08,
#endif
        0,
    },
    {
        1, 3, 3, 3,
#if defined(VERSION_EU)
        &gCardMessageText009ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText09,
#elif defined(VERSION_US)
        gDonaldTalkText09,
#endif
        0,
    },
    {
        1, 3, 3, 3,
#if defined(VERSION_EU)
        &gCardMessageText010ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText10,
#elif defined(VERSION_US)
        gDonaldTalkText10,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText011ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText11,
#elif defined(VERSION_US)
        gDonaldTalkText11,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText012ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText12,
#elif defined(VERSION_US)
        gDonaldTalkText12,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText013ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText13,
#elif defined(VERSION_US)
        gDonaldTalkText13,
#endif
        0,
    },
    {
        1, 3, 3, 3,
#if defined(VERSION_EU)
        &gCardMessageText014ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText14,
#elif defined(VERSION_US)
        gDonaldTalkText14,
#endif
        0,
    },
    {
        1, 3, 4, 3,
#if defined(VERSION_EU)
        &gCardMessageText015ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText15,
#elif defined(VERSION_US)
        gDonaldTalkText15,
#endif
        0,
    },
    {
        1, 3, 2, 3,
#if defined(VERSION_EU)
        &gCardMessageText016ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText16,
#elif defined(VERSION_US)
        gDonaldTalkText16,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText017ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText17,
#elif defined(VERSION_US)
        gDonaldTalkText17,
#endif
        0,
    },
    {
        1, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText018ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText18,
#elif defined(VERSION_US)
        gDonaldTalkText18,
#endif
        0,
    },
    {
        1, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText019ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText19,
#elif defined(VERSION_US)
        gDonaldTalkText19,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText020ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText20,
#elif defined(VERSION_US)
        gDonaldTalkText20,
#endif
        0,
    },
    {
        1, 3, 2, 3,
#if defined(VERSION_EU)
        &gCardMessageText021ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText21,
#elif defined(VERSION_US)
        gDonaldTalkText21,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText022ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText22,
#elif defined(VERSION_US)
        gDonaldTalkText22,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText023ByLanguage,
#elif defined(VERSION_JP)
        gDonaldTalkText23,
#elif defined(VERSION_US)
        gDonaldTalkText23,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText024ByLanguage,
#elif defined(VERSION_JP)
        gDonaldExitHallTalkText,
#elif defined(VERSION_US)
        gDonaldExitHallTalkText,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText025ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText00,
#elif defined(VERSION_US)
        gGoofyTalkText00,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText026ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText01,
#elif defined(VERSION_US)
        gGoofyTalkText01,
#endif
        0,
    },
    {
        2, 3, 3, 3,
#if defined(VERSION_EU)
        &gCardMessageText027ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText02,
#elif defined(VERSION_US)
        gGoofyTalkText02,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText028ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText03,
#elif defined(VERSION_US)
        gGoofyTalkText03,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText029ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText04,
#elif defined(VERSION_US)
        gGoofyTalkText04,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText030ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText05,
#elif defined(VERSION_US)
        gGoofyTalkText05,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText031ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText06,
#elif defined(VERSION_US)
        gGoofyTalkText06,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText032ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText07,
#elif defined(VERSION_US)
        gGoofyTalkText07,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText033ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText08,
#elif defined(VERSION_US)
        gGoofyTalkText08,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText034ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText09,
#elif defined(VERSION_US)
        gGoofyTalkText09,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText035ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText10,
#elif defined(VERSION_US)
        gGoofyTalkText10,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText036ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText11,
#elif defined(VERSION_US)
        gGoofyTalkText11,
#endif
        0,
    },
    {
        2, 3, 4, 3,
#if defined(VERSION_EU)
        &gCardMessageText037ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText12,
#elif defined(VERSION_US)
        gGoofyTalkText12,
#endif
        0,
    },
    {
        2, 3, 3, 3,
#if defined(VERSION_EU)
        &gCardMessageText038ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText13,
#elif defined(VERSION_US)
        gGoofyTalkText13,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText039ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText14,
#elif defined(VERSION_US)
        gGoofyTalkText14,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText040ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText15,
#elif defined(VERSION_US)
        gGoofyTalkText15,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText041ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText16,
#elif defined(VERSION_US)
        gGoofyTalkText16,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText042ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText17,
#elif defined(VERSION_US)
        gGoofyTalkText17,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText043ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText18,
#elif defined(VERSION_US)
        gGoofyTalkText18,
#endif
        0,
    },
    {
        2, 3, 4, 3,
#if defined(VERSION_EU)
        &gCardMessageText044ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText19,
#elif defined(VERSION_US)
        gGoofyTalkText19,
#endif
        0,
    },
    {
        2, 3, 3, 3,
#if defined(VERSION_EU)
        &gCardMessageText045ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText20,
#elif defined(VERSION_US)
        gGoofyTalkText20,
#endif
        0,
    },
    {
        2, 3, 2, 3,
#if defined(VERSION_EU)
        &gCardMessageText046ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText21,
#elif defined(VERSION_US)
        gGoofyTalkText21,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText047ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText22,
#elif defined(VERSION_US)
        gGoofyTalkText22,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText048ByLanguage,
#elif defined(VERSION_JP)
        gGoofyTalkText23,
#elif defined(VERSION_US)
        gGoofyTalkText23,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText049ByLanguage,
#elif defined(VERSION_JP)
        gGoofyExitHallTalkText,
#elif defined(VERSION_US)
        gGoofyExitHallTalkText,
#endif
        0,
    },
    {
        60, 3, 4, 3,
#if defined(VERSION_EU)
        &gCardMessageText050ByLanguage,
#elif defined(VERSION_JP)
        gNamineTalkText0,
#elif defined(VERSION_US)
        gNamineTalkText0,
#endif
        0,
    },
    {
        60, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText051ByLanguage,
#elif defined(VERSION_JP)
        gNamineTalkText1,
#elif defined(VERSION_US)
        gNamineTalkText1,
#endif
        0,
    },
    {
        27, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText052ByLanguage,
#elif defined(VERSION_JP)
        gRikuReplicaTalkText,
#elif defined(VERSION_US)
        gRikuReplicaTalkText,
#endif
        0,
    },
    {
        36, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText053ByLanguage,
#elif defined(VERSION_JP)
        gPoohTalkText,
#elif defined(VERSION_US)
        gEventTextUs_0900868C,
#endif
        CARD_MSG_FLAG_CHOICE_AT_END,
    },
    {
        47, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText054ByLanguage,
#elif defined(VERSION_JP)
        gPigletTalkText,
#elif defined(VERSION_US)
        gPigletTalkText,
#endif
        0,
    },
    {
        48, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText055ByLanguage,
#elif defined(VERSION_JP)
        gOwlTalkText,
#elif defined(VERSION_US)
        gOwlTalkText,
#endif
        0,
    },
    {
        50, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText056ByLanguage,
#elif defined(VERSION_JP)
        gEeyoreTalkText0,
#elif defined(VERSION_US)
        gEeyoreTalkText0,
#endif
        0,
    },
    {
        50, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText057ByLanguage,
#elif defined(VERSION_JP)
        gEeyoreTalkText1,
#elif defined(VERSION_US)
        gEeyoreTalkText1,
#endif
        0,
    },
    {
        51, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText058ByLanguage,
#elif defined(VERSION_JP)
        gRooTalkText,
#elif defined(VERSION_US)
        gRooTalkText,
#endif
        0,
    },
    {
        49, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText059ByLanguage,
#elif defined(VERSION_JP)
        gRabbitTalkText0,
#elif defined(VERSION_US)
        gRabbitTalkText0,
#endif
        0,
    },
    {
        49, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText060ByLanguage,
#elif defined(VERSION_JP)
        gRabbitTalkText1,
#elif defined(VERSION_US)
        gRabbitTalkText1,
#endif
        0,
    },
    {
        61, 3, 4, 3,
#if defined(VERSION_EU)
        &gCardMessageText061ByLanguage,
#elif defined(VERSION_JP)
        gMickeyTalkText0,
#elif defined(VERSION_US)
        gMickeyTalkText0,
#endif
        0,
    },
    {
        61, 3, 1, 3,
#if defined(VERSION_EU)
        &gCardMessageText062ByLanguage,
#elif defined(VERSION_JP)
        gMickeyTalkText1,
#elif defined(VERSION_US)
        gMickeyTalkText1,
#endif
        0,
    },
    {
        61, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText063ByLanguage,
#elif defined(VERSION_JP)
        gMickeyTalkText2,
#elif defined(VERSION_US)
        gMickeyTalkText2,
#endif
        0,
    },
    {
        7, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText064ByLanguage,
#elif defined(VERSION_JP)
        gMsTopShopOptionText,
#elif defined(VERSION_US)
        gMsTopShopOptionText,
#endif
        0,
    },
    {
        7, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText065ByLanguage,
#elif defined(VERSION_JP)
        gMsTopChargeOptionText,
#elif defined(VERSION_US)
        gMsTopChargeOptionText,
#endif
        0,
    },
    {
        7, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText066ByLanguage,
#elif defined(VERSION_JP)
        gMsTopFreePackText,
#elif defined(VERSION_US)
        gMsTopFreePackText,
#endif
        0,
    },
    {
        7, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText065ByLanguage,
#elif defined(VERSION_JP)
        gMsTopNothingToSellText,
#elif defined(VERSION_US)
        gCardMessageNoText,
#endif
        0,
    },
    {
        7, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText065ByLanguage,
#elif defined(VERSION_JP)
        gMsTopNothingToTradeText,
#elif defined(VERSION_US)
        gCardMessageNoText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText069ByLanguage,
#elif defined(VERSION_JP)
        gPoohLeaveWorldText,
#elif defined(VERSION_US)
        gPoohLeaveWorldText,
#endif
        CARD_MSG_FLAG_CHOICE_AT_END | CARD_MSG_FLAG_CHOICE_WINDOW,
    },
    {
        3, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText070ByLanguage,
#elif defined(VERSION_JP)
        gWorldselectTutorialText0,
#elif defined(VERSION_US)
        gWorldselectTutorialText0,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText071ByLanguage,
#elif defined(VERSION_JP)
        gWorldselectTutorialText1,
#elif defined(VERSION_US)
        gWorldselectTutorialText1,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText072ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText00,
#elif defined(VERSION_US)
        gRobeTutorialText00,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText073ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText01,
#elif defined(VERSION_US)
        gRobeTutorialText01,
#endif
        0,
    },
    {
        62, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText074ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText02,
#elif defined(VERSION_US)
        gRobeTutorialText02,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText075ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText03,
#elif defined(VERSION_US)
        gRobeTutorialText03,
#endif
        0,
    },
    {
        62, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText076ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText04,
#elif defined(VERSION_US)
        gRobeTutorialText04,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText077ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText05,
#elif defined(VERSION_US)
        gRobeTutorialText05,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText078ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText06,
#elif defined(VERSION_US)
        gRobeTutorialText06,
#endif
        0,
    },
    {
        62, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText079ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText07,
#elif defined(VERSION_US)
        gRobeTutorialText07,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText080ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText08,
#elif defined(VERSION_US)
        gRobeTutorialText08,
#endif
        0,
    },
    {
        62, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText081ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText04,
#elif defined(VERSION_US)
        gRobeTutorialText09,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText082ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText10,
#elif defined(VERSION_US)
        gRobeTutorialText10,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText083ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText11,
#elif defined(VERSION_US)
        gRobeTutorialText11,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText084ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText12,
#elif defined(VERSION_US)
        gRobeTutorialText12,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText085ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText13,
#elif defined(VERSION_US)
        gRobeTutorialText13,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText086ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText14,
#elif defined(VERSION_US)
        gRobeTutorialText14,
#endif
        0,
    },
    {
        62, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText087ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText15,
#elif defined(VERSION_US)
        gRobeTutorialText15,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText088ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText16,
#elif defined(VERSION_US)
        gRobeTutorialText16,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText089ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText17,
#elif defined(VERSION_US)
        gRobeTutorialText17,
#endif
        0,
    },
    {
        62, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText090ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText18,
#elif defined(VERSION_US)
        gRobeTutorialText18,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText091ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText19,
#elif defined(VERSION_US)
        gRobeTutorialText19,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText092ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText20,
#elif defined(VERSION_US)
        gRobeTutorialText20,
#endif
        0,
    },
    {
        62, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText093ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText21,
#elif defined(VERSION_US)
        gRobeTutorialText21,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText094ByLanguage,
#elif defined(VERSION_JP)
        gRobeTutorialText22,
#elif defined(VERSION_US)
        gRobeTutorialText22,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText095ByLanguage,
#elif defined(VERSION_JP)
        gMapSelectTutorialText0,
#elif defined(VERSION_US)
        gMapSelectTutorialText0,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText096ByLanguage,
#elif defined(VERSION_JP)
        gMapSelectTutorialText1,
#elif defined(VERSION_US)
        gMapSelectTutorialText1,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText097ByLanguage,
#elif defined(VERSION_JP)
        gMapSelectTutorialText2,
#elif defined(VERSION_US)
        gMapSelectTutorialText2,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText098ByLanguage,
#elif defined(VERSION_JP)
        gMapSelectTutorialText3,
#elif defined(VERSION_US)
        gMapSelectTutorialText3,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText099ByLanguage,
#elif defined(VERSION_JP)
        gMapSelectValueTutorialText0,
#elif defined(VERSION_US)
        gMapSelectValueTutorialText0,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText100ByLanguage,
#elif defined(VERSION_JP)
        gMapSelectValueTutorialText1,
#elif defined(VERSION_US)
        gMapSelectValueTutorialText1,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText101ByLanguage,
#elif defined(VERSION_JP)
        gMapSelectValueTutorialText2,
#elif defined(VERSION_US)
        gMapSelectValueTutorialText2,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText102ByLanguage,
#elif defined(VERSION_JP)
        gMapSelectValueTutorialText3,
#elif defined(VERSION_US)
        gMapSelectValueTutorialText3,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText103ByLanguage,
#elif defined(VERSION_JP)
        gSavePointTutorialText,
#elif defined(VERSION_US)
        gSavePointTutorialText,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText103ByLanguage,
#elif defined(VERSION_JP)
        gSaveMenuTutorialText,
#elif defined(VERSION_US)
        gSavePointTutorialText,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText105ByLanguage,
#elif defined(VERSION_JP)
        gQuickSaveTutorialText,
#elif defined(VERSION_US)
        gQuickSaveTutorialText,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText106ByLanguage,
#elif defined(VERSION_JP)
        gMapTutorialText0,
#elif defined(VERSION_US)
        gMapTutorialText0,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText107ByLanguage,
#elif defined(VERSION_JP)
        gMapTutorialText1,
#elif defined(VERSION_US)
        gMapTutorialText1,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText108ByLanguage,
#elif defined(VERSION_JP)
        gMapTutorialText2,
#elif defined(VERSION_US)
        gMapTutorialText2,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText109ByLanguage,
#elif defined(VERSION_JP)
        gMapSelectEventDoorTutorialText0,
#elif defined(VERSION_US)
        gMapSelectEventDoorTutorialText0,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText110ByLanguage,
#elif defined(VERSION_JP)
        gMapSelectEventDoorTutorialText1,
#elif defined(VERSION_US)
        gMapSelectEventDoorTutorialText1,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText111ByLanguage,
#elif defined(VERSION_JP)
        gMapSelectEventDoorTutorialText2,
#elif defined(VERSION_US)
        gMapSelectEventDoorTutorialText2,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText112ByLanguage,
#elif defined(VERSION_JP)
        gMapSelectEventDoorTutorialText3,
#elif defined(VERSION_US)
        gMapSelectEventDoorTutorialText3,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText113ByLanguage,
#elif defined(VERSION_JP)
        gMapSelectEventDoorTutorialText4,
#elif defined(VERSION_US)
        gMapSelectEventDoorTutorialText4,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText114ByLanguage,
#elif defined(VERSION_JP)
        gLeonTutorialText00,
#elif defined(VERSION_US)
        gLeonTutorialText00,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText115ByLanguage,
#elif defined(VERSION_JP)
        gLeonTutorialText01,
#elif defined(VERSION_US)
        gLeonTutorialText01,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText116ByLanguage,
#elif defined(VERSION_JP)
        gLeonTutorialText02,
#elif defined(VERSION_US)
        gLeonTutorialText02,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText117ByLanguage,
#elif defined(VERSION_JP)
        gLeonTutorialText03,
#elif defined(VERSION_US)
        gLeonTutorialText03,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText118ByLanguage,
#elif defined(VERSION_JP)
        gLeonTutorialText04,
#elif defined(VERSION_US)
        gLeonTutorialText04,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText119ByLanguage,
#elif defined(VERSION_JP)
        gLeonTutorialText05,
#elif defined(VERSION_US)
        gLeonTutorialText05,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText120ByLanguage,
#elif defined(VERSION_JP)
        gLeonTutorialText06,
#elif defined(VERSION_US)
        gLeonTutorialText06,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText121ByLanguage,
#elif defined(VERSION_JP)
        gLeonTutorialText07,
#elif defined(VERSION_US)
        gLeonTutorialText07,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText122ByLanguage,
#elif defined(VERSION_JP)
        gLeonTutorialText08,
#elif defined(VERSION_US)
        gLeonTutorialText08,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText123ByLanguage,
#elif defined(VERSION_JP)
        gLeonTutorialText09,
#elif defined(VERSION_US)
        gLeonTutorialText09,
#endif
        0,
    },
    {
        62, 1, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText124ByLanguage,
#elif defined(VERSION_JP)
        gLeonTutorialText10,
#elif defined(VERSION_US)
        gLeonTutorialText10,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        31, 1, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText125ByLanguage,
#elif defined(VERSION_JP)
        gLeonTutorialText11,
#elif defined(VERSION_US)
        gLeonTutorialText11,
#endif
        0,
    },
    {
        62, 1, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText126ByLanguage,
#elif defined(VERSION_JP)
        gLeonTutorialText12,
#elif defined(VERSION_US)
        gLeonTutorialText12,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        31, 1, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText127ByLanguage,
#elif defined(VERSION_JP)
        gLeonTutorialText13,
#elif defined(VERSION_US)
        gLeonTutorialText13,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText128ByLanguage,
#elif defined(VERSION_JP)
        gLeonTutorialText14,
#elif defined(VERSION_US)
        gLeonTutorialText14,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText129ByLanguage,
#elif defined(VERSION_JP)
        gMsTopIntroText0,
#elif defined(VERSION_US)
        gMsTopIntroText0,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText130ByLanguage,
#elif defined(VERSION_JP)
        gMsTopIntroText1,
#elif defined(VERSION_US)
        gMsTopIntroText1,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText131ByLanguage,
#elif defined(VERSION_JP)
        gMsTopIntroText2,
#elif defined(VERSION_US)
        gMsTopIntroText2,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText132ByLanguage,
#elif defined(VERSION_JP)
        gWarpPointTutorialText,
#elif defined(VERSION_US)
        gWarpPointTutorialText,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText133ByLanguage,
#elif defined(VERSION_JP)
        gLearnedWarpinatorText,
#elif defined(VERSION_US)
        gLearnedWarpinatorText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText134ByLanguage,
#elif defined(VERSION_JP)
        gLearnedTerrorText,
#elif defined(VERSION_US)
        gLearnedTerrorText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText135ByLanguage,
#elif defined(VERSION_JP)
        gLearnedSynchroText,
#elif defined(VERSION_US)
        gLearnedSynchroText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText136ByLanguage,
#elif defined(VERSION_JP)
        gLearnedBindText,
#elif defined(VERSION_US)
        gLearnedBindText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText137ByLanguage,
#elif defined(VERSION_JP)
        gLearnedIdyllRompText,
#elif defined(VERSION_US)
        gLearnedIdyllRompText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText138ByLanguage,
#elif defined(VERSION_JP)
        gLearnedTrinityLimitText,
#elif defined(VERSION_US)
        gLearnedTrinityLimitText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText139ByLanguage,
#elif defined(VERSION_JP)
        gLearnedConfuseText,
#elif defined(VERSION_US)
        gLearnedConfuseText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText140ByLanguage,
#elif defined(VERSION_JP)
        gLearnedThunderRaidText,
#elif defined(VERSION_US)
        gLearnedThunderRaidText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText141ByLanguage,
#elif defined(VERSION_JP)
        gLearnedGiftedMiracleText,
#elif defined(VERSION_US)
        gLearnedGiftedMiracleText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText142ByLanguage,
#elif defined(VERSION_JP)
        gLearnedGravityRaidText,
#elif defined(VERSION_US)
        gLearnedGravityRaidText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText143ByLanguage,
#elif defined(VERSION_JP)
        gLearnedFireRaidText,
#elif defined(VERSION_US)
        gLearnedFireRaidText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText144ByLanguage,
#elif defined(VERSION_JP)
        gLearnedAquaSplashText,
#elif defined(VERSION_US)
        gLearnedAquaSplashText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText145ByLanguage,
#elif defined(VERSION_JP)
        gLearnedBlizzardRaidText,
#elif defined(VERSION_US)
        gLearnedBlizzardRaidText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText146ByLanguage,
#elif defined(VERSION_JP)
        gLearnedStopRaidText,
#elif defined(VERSION_US)
        gLearnedStopRaidText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText147ByLanguage,
#elif defined(VERSION_JP)
        gLearnedShockImpactText,
#elif defined(VERSION_US)
        gLearnedShockImpactText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText148ByLanguage,
#elif defined(VERSION_JP)
        gLearnedHomingBlizzaraText,
#elif defined(VERSION_US)
        gLearnedHomingBlizzaraText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText149ByLanguage,
#elif defined(VERSION_JP)
        gLearnedQuakeText,
#elif defined(VERSION_US)
        gLearnedQuakeText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText150ByLanguage,
#elif defined(VERSION_JP)
        gLearnedBlazingDonaldText,
#elif defined(VERSION_US)
        gLearnedBlazingDonaldText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText151ByLanguage,
#elif defined(VERSION_JP)
        gLearnedHomingFiraText,
#elif defined(VERSION_US)
        gLearnedHomingFiraText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText152ByLanguage,
#elif defined(VERSION_JP)
        gLearnedTeleportText,
#elif defined(VERSION_US)
        gLearnedTeleportText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText153ByLanguage,
#elif defined(VERSION_JP)
        gLearnedTornadoText,
#elif defined(VERSION_US)
        gLearnedTornadoText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText154ByLanguage,
#elif defined(VERSION_JP)
        gLearnedCrossSlashPlusText,
#elif defined(VERSION_US)
        gLearnedCrossSlashPlusText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText155ByLanguage,
#elif defined(VERSION_JP)
        gLearnedReflectRaidText,
#elif defined(VERSION_US)
        gLearnedReflectRaidText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText156ByLanguage,
#elif defined(VERSION_JP)
        gLearnedFiragaBreakText,
#elif defined(VERSION_US)
        gLearnedFiragaBreakText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText157ByLanguage,
#elif defined(VERSION_JP)
        gLearnedWarpText,
#elif defined(VERSION_US)
        gLearnedWarpText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText158ByLanguage,
#elif defined(VERSION_JP)
        gLearnedJudgmentText,
#elif defined(VERSION_US)
        gLearnedJudgmentText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText159ByLanguage,
#elif defined(VERSION_JP)
        gObtainedElixirText,
#elif defined(VERSION_US)
        gObtainedElixirText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText160ByLanguage,
#elif defined(VERSION_JP)
        gObtainedSpellbinderText,
#elif defined(VERSION_US)
        gObtainedSpellbinderText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText161ByLanguage,
#elif defined(VERSION_JP)
        gObtainedGenieText,
#elif defined(VERSION_US)
        gObtainedGenieText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText162ByLanguage,
#elif defined(VERSION_JP)
        gObtainedCloudText,
#elif defined(VERSION_US)
        gObtainedCloudText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText163ByLanguage,
#elif defined(VERSION_JP)
        gObtainedOathkeeperText,
#elif defined(VERSION_US)
        gObtainedOathkeeperText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText164ByLanguage,
#elif defined(VERSION_JP)
        gObtainedOblivionText,
#elif defined(VERSION_US)
        gObtainedOblivionText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText165ByLanguage,
#elif defined(VERSION_JP)
        gObtainedBambiText,
#elif defined(VERSION_US)
        gObtainedBambiText,
#endif
        CARD_MSG_FLAG_CHOICE_AT_END,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText166ByLanguage,
#elif defined(VERSION_JP)
        gEventSaveConfirmText,
#elif defined(VERSION_US)
        gEventSaveConfirmText,
#endif
        CARD_MSG_FLAG_CHOICE_AT_END,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText167ByLanguage,
#elif defined(VERSION_JP)
        gMapStairTutorialText,
#elif defined(VERSION_US)
        gMapStairTutorialText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText168ByLanguage,
#elif defined(VERSION_JP)
        gObtainedKeyOfBeginningsText,
#elif defined(VERSION_US)
        gObtainedKeyOfBeginningsText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText169ByLanguage,
#elif defined(VERSION_JP)
        gObtainedKeyOfGuidanceText,
#elif defined(VERSION_US)
        gObtainedKeyOfGuidanceText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText170ByLanguage,
#elif defined(VERSION_JP)
        gObtainedKeyToTruthText,
#elif defined(VERSION_US)
        gObtainedKeyToTruthText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText171ByLanguage,
#elif defined(VERSION_JP)
        gObtainedKeyToRewardsText,
#elif defined(VERSION_US)
        gObtainedKeyToRewardsText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText172ByLanguage,
#elif defined(VERSION_JP)
        gObtainedTinkerBellText,
#elif defined(VERSION_US)
        gObtainedTinkerBellText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText173ByLanguage,
#elif defined(VERSION_JP)
        gObtainedWorldCardText,
#elif defined(VERSION_US)
        gObtainedWorldCardText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText174ByLanguage,
#elif defined(VERSION_JP)
        gObtainedWorldCardText,
#elif defined(VERSION_US)
        gObtainedWorldCardsText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText175ByLanguage,
#elif defined(VERSION_JP)
        gObtainedSimbaText,
#elif defined(VERSION_US)
        gObtainedSimbaText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText176ByLanguage,
#elif defined(VERSION_JP)
        gSaveDataLostText,
#elif defined(VERSION_US)
        gSaveDataLostText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText177ByLanguage,
#elif defined(VERSION_JP)
        gRikuDeckTutorialText,
#elif defined(VERSION_US)
        gRikuDeckTutorialText,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#if defined(VERSION_EU)
        &gCardMessageText178ByLanguage,
#elif defined(VERSION_JP)
        gRikuBattleTutorialText,
#elif defined(VERSION_US)
        gRikuBattleTutorialText,
#endif
        0,
    },
#ifndef VERSION_EU
    {
        62, 3, 0, 3,
#if defined(VERSION_JP)
        gQuickSaveCompleteText,
#elif defined(VERSION_US)
        gQuickSaveCompleteText,
#endif
        0,
    },
#endif
};

TaskDesc gTaskDescCardMsgwin = {
    "msgwin",
    (TaskInitFunc)msgwin_0,
    (TaskUpdateFunc)msgwin_1,
    (TaskDrawFunc)msgwin_2,
    (TaskDestroyFunc)msgwin_3,
    sizeof(CardMsgWinWork),
};
