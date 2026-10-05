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
#ifdef VERSION_EU
        &gCardMessageText000ByLanguage,
#else
        gDonaldTalkText00,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText001ByLanguage,
#else
        gDonaldTalkText01,
#endif
        0,
    },
    {
        1, 3, 4, 3,
#ifdef VERSION_EU
        &gCardMessageText002ByLanguage,
#else
        gDonaldTalkText02,
#endif
        0,
    },
    {
        1, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText003ByLanguage,
#else
        gDonaldTalkText03,
#endif
        0,
    },
    {
        1, 3, 3, 3,
#ifdef VERSION_EU
        &gCardMessageText004ByLanguage,
#else
        gDonaldTalkText04,
#endif
        0,
    },
    {
        1, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText005ByLanguage,
#else
        gDonaldTalkText05,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText006ByLanguage,
#else
        gDonaldTalkText06,
#endif
        0,
    },
    {
        1, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText007ByLanguage,
#else
        gDonaldTalkText07,
#endif
        0,
    },
    {
        1, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText008ByLanguage,
#else
        gDonaldTalkText08,
#endif
        0,
    },
    {
        1, 3, 3, 3,
#ifdef VERSION_EU
        &gCardMessageText009ByLanguage,
#else
        gDonaldTalkText09,
#endif
        0,
    },
    {
        1, 3, 3, 3,
#ifdef VERSION_EU
        &gCardMessageText010ByLanguage,
#else
        gDonaldTalkText10,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText011ByLanguage,
#else
        gDonaldTalkText11,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText012ByLanguage,
#else
        gDonaldTalkText12,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText013ByLanguage,
#else
        gDonaldTalkText13,
#endif
        0,
    },
    {
        1, 3, 3, 3,
#ifdef VERSION_EU
        &gCardMessageText014ByLanguage,
#else
        gDonaldTalkText14,
#endif
        0,
    },
    {
        1, 3, 4, 3,
#ifdef VERSION_EU
        &gCardMessageText015ByLanguage,
#else
        gDonaldTalkText15,
#endif
        0,
    },
    {
        1, 3, 2, 3,
#ifdef VERSION_EU
        &gCardMessageText016ByLanguage,
#else
        gDonaldTalkText16,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText017ByLanguage,
#else
        gDonaldTalkText17,
#endif
        0,
    },
    {
        1, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText018ByLanguage,
#else
        gDonaldTalkText18,
#endif
        0,
    },
    {
        1, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText019ByLanguage,
#else
        gDonaldTalkText19,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText020ByLanguage,
#else
        gDonaldTalkText20,
#endif
        0,
    },
    {
        1, 3, 2, 3,
#ifdef VERSION_EU
        &gCardMessageText021ByLanguage,
#else
        gDonaldTalkText21,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText022ByLanguage,
#else
        gDonaldTalkText22,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText023ByLanguage,
#else
        gDonaldTalkText23,
#endif
        0,
    },
    {
        1, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText024ByLanguage,
#else
        gDonaldExitHallTalkText,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText025ByLanguage,
#else
        gGoofyTalkText00,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText026ByLanguage,
#else
        gGoofyTalkText01,
#endif
        0,
    },
    {
        2, 3, 3, 3,
#ifdef VERSION_EU
        &gCardMessageText027ByLanguage,
#else
        gGoofyTalkText02,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText028ByLanguage,
#else
        gGoofyTalkText03,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText029ByLanguage,
#else
        gGoofyTalkText04,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText030ByLanguage,
#else
        gGoofyTalkText05,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText031ByLanguage,
#else
        gGoofyTalkText06,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText032ByLanguage,
#else
        gGoofyTalkText07,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText033ByLanguage,
#else
        gGoofyTalkText08,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText034ByLanguage,
#else
        gGoofyTalkText09,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText035ByLanguage,
#else
        gGoofyTalkText10,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText036ByLanguage,
#else
        gGoofyTalkText11,
#endif
        0,
    },
    {
        2, 3, 4, 3,
#ifdef VERSION_EU
        &gCardMessageText037ByLanguage,
#else
        gGoofyTalkText12,
#endif
        0,
    },
    {
        2, 3, 3, 3,
#ifdef VERSION_EU
        &gCardMessageText038ByLanguage,
#else
        gGoofyTalkText13,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText039ByLanguage,
#else
        gGoofyTalkText14,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText040ByLanguage,
#else
        gGoofyTalkText15,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText041ByLanguage,
#else
        gGoofyTalkText16,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText042ByLanguage,
#else
        gGoofyTalkText17,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText043ByLanguage,
#else
        gGoofyTalkText18,
#endif
        0,
    },
    {
        2, 3, 4, 3,
#ifdef VERSION_EU
        &gCardMessageText044ByLanguage,
#else
        gGoofyTalkText19,
#endif
        0,
    },
    {
        2, 3, 3, 3,
#ifdef VERSION_EU
        &gCardMessageText045ByLanguage,
#else
        gGoofyTalkText20,
#endif
        0,
    },
    {
        2, 3, 2, 3,
#ifdef VERSION_EU
        &gCardMessageText046ByLanguage,
#else
        gGoofyTalkText21,
#endif
        0,
    },
    {
        2, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText047ByLanguage,
#else
        gGoofyTalkText22,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText048ByLanguage,
#else
        gGoofyTalkText23,
#endif
        0,
    },
    {
        2, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText049ByLanguage,
#else
        gGoofyExitHallTalkText,
#endif
        0,
    },
    {
        60, 3, 4, 3,
#ifdef VERSION_EU
        &gCardMessageText050ByLanguage,
#else
        gNamineTalkText0,
#endif
        0,
    },
    {
        60, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText051ByLanguage,
#else
        gNamineTalkText1,
#endif
        0,
    },
    {
        27, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText052ByLanguage,
#else
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
#ifdef VERSION_EU
        &gCardMessageText054ByLanguage,
#else
        gPigletTalkText,
#endif
        0,
    },
    {
        48, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText055ByLanguage,
#else
        gOwlTalkText,
#endif
        0,
    },
    {
        50, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText056ByLanguage,
#else
        gEeyoreTalkText0,
#endif
        0,
    },
    {
        50, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText057ByLanguage,
#else
        gEeyoreTalkText1,
#endif
        0,
    },
    {
        51, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText058ByLanguage,
#else
        gRooTalkText,
#endif
        0,
    },
    {
        49, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText059ByLanguage,
#else
        gRabbitTalkText0,
#endif
        0,
    },
    {
        49, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText060ByLanguage,
#else
        gRabbitTalkText1,
#endif
        0,
    },
    {
        61, 3, 4, 3,
#ifdef VERSION_EU
        &gCardMessageText061ByLanguage,
#else
        gMickeyTalkText0,
#endif
        0,
    },
    {
        61, 3, 1, 3,
#ifdef VERSION_EU
        &gCardMessageText062ByLanguage,
#else
        gMickeyTalkText1,
#endif
        0,
    },
    {
        61, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText063ByLanguage,
#else
        gMickeyTalkText2,
#endif
        0,
    },
    {
        7, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText064ByLanguage,
#else
        gMsTopShopOptionText,
#endif
        0,
    },
    {
        7, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText065ByLanguage,
#else
        gMsTopChargeOptionText,
#endif
        0,
    },
    {
        7, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText066ByLanguage,
#else
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
#ifdef VERSION_EU
        &gCardMessageText069ByLanguage,
#else
        gPoohLeaveWorldText,
#endif
        CARD_MSG_FLAG_CHOICE_AT_END | CARD_MSG_FLAG_CHOICE_WINDOW,
    },
    {
        3, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText070ByLanguage,
#else
        gWorldselectTutorialText0,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText071ByLanguage,
#else
        gWorldselectTutorialText1,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText072ByLanguage,
#else
        gRobeTutorialText00,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText073ByLanguage,
#else
        gRobeTutorialText01,
#endif
        0,
    },
    {
        62, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText074ByLanguage,
#else
        gRobeTutorialText02,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText075ByLanguage,
#else
        gRobeTutorialText03,
#endif
        0,
    },
    {
        62, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText076ByLanguage,
#else
        gRobeTutorialText04,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText077ByLanguage,
#else
        gRobeTutorialText05,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText078ByLanguage,
#else
        gRobeTutorialText06,
#endif
        0,
    },
    {
        62, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText079ByLanguage,
#else
        gRobeTutorialText07,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText080ByLanguage,
#else
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
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText082ByLanguage,
#else
        gRobeTutorialText10,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText083ByLanguage,
#else
        gRobeTutorialText11,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText084ByLanguage,
#else
        gRobeTutorialText12,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText085ByLanguage,
#else
        gRobeTutorialText13,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText086ByLanguage,
#else
        gRobeTutorialText14,
#endif
        0,
    },
    {
        62, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText087ByLanguage,
#else
        gRobeTutorialText15,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText088ByLanguage,
#else
        gRobeTutorialText16,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText089ByLanguage,
#else
        gRobeTutorialText17,
#endif
        0,
    },
    {
        62, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText090ByLanguage,
#else
        gRobeTutorialText18,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText091ByLanguage,
#else
        gRobeTutorialText19,
#endif
        0,
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText092ByLanguage,
#else
        gRobeTutorialText20,
#endif
        0,
    },
    {
        62, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText093ByLanguage,
#else
        gRobeTutorialText21,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        3, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText094ByLanguage,
#else
        gRobeTutorialText22,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText095ByLanguage,
#else
        gMapSelectTutorialText0,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText096ByLanguage,
#else
        gMapSelectTutorialText1,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText097ByLanguage,
#else
        gMapSelectTutorialText2,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText098ByLanguage,
#else
        gMapSelectTutorialText3,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText099ByLanguage,
#else
        gMapSelectValueTutorialText0,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText100ByLanguage,
#else
        gMapSelectValueTutorialText1,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText101ByLanguage,
#else
        gMapSelectValueTutorialText2,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText102ByLanguage,
#else
        gMapSelectValueTutorialText3,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText103ByLanguage,
#else
        gSavePointTutorialText,
#endif
#ifdef VERSION_JP
        0,
#else
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
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText105ByLanguage,
#else
        gQuickSaveTutorialText,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText106ByLanguage,
#else
        gMapTutorialText0,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText107ByLanguage,
#else
        gMapTutorialText1,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText108ByLanguage,
#else
        gMapTutorialText2,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText109ByLanguage,
#else
        gMapSelectEventDoorTutorialText0,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText110ByLanguage,
#else
        gMapSelectEventDoorTutorialText1,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText111ByLanguage,
#else
        gMapSelectEventDoorTutorialText2,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText112ByLanguage,
#else
        gMapSelectEventDoorTutorialText3,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText113ByLanguage,
#else
        gMapSelectEventDoorTutorialText4,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText114ByLanguage,
#else
        gLeonTutorialText00,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText115ByLanguage,
#else
        gLeonTutorialText01,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText116ByLanguage,
#else
        gLeonTutorialText02,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText117ByLanguage,
#else
        gLeonTutorialText03,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText118ByLanguage,
#else
        gLeonTutorialText04,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText119ByLanguage,
#else
        gLeonTutorialText05,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText120ByLanguage,
#else
        gLeonTutorialText06,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText121ByLanguage,
#else
        gLeonTutorialText07,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText122ByLanguage,
#else
        gLeonTutorialText08,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText123ByLanguage,
#else
        gLeonTutorialText09,
#endif
        0,
    },
    {
        62, 1, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText124ByLanguage,
#else
        gLeonTutorialText10,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        31, 1, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText125ByLanguage,
#else
        gLeonTutorialText11,
#endif
        0,
    },
    {
        62, 1, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText126ByLanguage,
#else
        gLeonTutorialText12,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        31, 1, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText127ByLanguage,
#else
        gLeonTutorialText13,
#endif
        0,
    },
    {
        31, 0, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText128ByLanguage,
#else
        gLeonTutorialText14,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText129ByLanguage,
#else
        gMsTopIntroText0,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText130ByLanguage,
#else
        gMsTopIntroText1,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText131ByLanguage,
#else
        gMsTopIntroText2,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText132ByLanguage,
#else
        gWarpPointTutorialText,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText133ByLanguage,
#else
        gLearnedWarpinatorText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText134ByLanguage,
#else
        gLearnedTerrorText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText135ByLanguage,
#else
        gLearnedSynchroText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText136ByLanguage,
#else
        gLearnedBindText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText137ByLanguage,
#else
        gLearnedIdyllRompText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText138ByLanguage,
#else
        gLearnedTrinityLimitText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText139ByLanguage,
#else
        gLearnedConfuseText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText140ByLanguage,
#else
        gLearnedThunderRaidText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText141ByLanguage,
#else
        gLearnedGiftedMiracleText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText142ByLanguage,
#else
        gLearnedGravityRaidText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText143ByLanguage,
#else
        gLearnedFireRaidText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText144ByLanguage,
#else
        gLearnedAquaSplashText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText145ByLanguage,
#else
        gLearnedBlizzardRaidText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText146ByLanguage,
#else
        gLearnedStopRaidText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText147ByLanguage,
#else
        gLearnedShockImpactText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText148ByLanguage,
#else
        gLearnedHomingBlizzaraText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText149ByLanguage,
#else
        gLearnedQuakeText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText150ByLanguage,
#else
        gLearnedBlazingDonaldText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText151ByLanguage,
#else
        gLearnedHomingFiraText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText152ByLanguage,
#else
        gLearnedTeleportText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText153ByLanguage,
#else
        gLearnedTornadoText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText154ByLanguage,
#else
        gLearnedCrossSlashPlusText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText155ByLanguage,
#else
        gLearnedReflectRaidText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText156ByLanguage,
#else
        gLearnedFiragaBreakText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText157ByLanguage,
#else
        gLearnedWarpText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText158ByLanguage,
#else
        gLearnedJudgmentText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText159ByLanguage,
#else
        gObtainedElixirText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText160ByLanguage,
#else
        gObtainedSpellbinderText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText161ByLanguage,
#else
        gObtainedGenieText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText162ByLanguage,
#else
        gObtainedCloudText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText163ByLanguage,
#else
        gObtainedOathkeeperText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText164ByLanguage,
#else
        gObtainedOblivionText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText165ByLanguage,
#else
        gObtainedBambiText,
#endif
        CARD_MSG_FLAG_CHOICE_AT_END,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText166ByLanguage,
#else
        gEventSaveConfirmText,
#endif
        CARD_MSG_FLAG_CHOICE_AT_END,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText167ByLanguage,
#else
        gMapStairTutorialText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText168ByLanguage,
#else
        gObtainedKeyOfBeginningsText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText169ByLanguage,
#else
        gObtainedKeyOfGuidanceText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText170ByLanguage,
#else
        gObtainedKeyToTruthText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText171ByLanguage,
#else
        gObtainedKeyToRewardsText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText172ByLanguage,
#else
        gObtainedTinkerBellText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText173ByLanguage,
#else
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
#ifdef VERSION_EU
        &gCardMessageText175ByLanguage,
#else
        gObtainedSimbaText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText176ByLanguage,
#else
        gSaveDataLostText,
#endif
        0,
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText177ByLanguage,
#else
        gRikuDeckTutorialText,
#endif
#ifdef VERSION_JP
        0,
#else
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
    },
    {
        62, 3, 0, 3,
#ifdef VERSION_EU
        &gCardMessageText178ByLanguage,
#else
        gRikuBattleTutorialText,
#endif
        0,
    },
#ifndef VERSION_EU
    {
        62, 3, 0, 3,
#ifndef VERSION_EU
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
