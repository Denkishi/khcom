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
#include "gba/syscall.h"
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
#include "types.h"
#include "gba/macro.h"
#include <stddef.h>

static CardMsgWinWork* sActiveCardMsgwin;

u8 gMessageWindowOpen EWRAM_COMMON(4);

u8 gMessageWindowAnswerYes EWRAM_COMMON(4);

u8 UpdateCardMsgwinLoadText(CardMsgWinWork* work, void* a);
u8 UpdateCardMsgwinWaitInput(CardMsgWinWork* work, void* a);
u8 UpdateCardMsgwinTypingPersistent(CardMsgWinWork* work, void* a);
u8 UpdateCardMsgwinPersistent(CardMsgWinWork* work, void* a);

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
    LoadBgTiles(work->args.bg, gUnk_094233B8, 1280);
    LoadBgPalette(work->args.bg, gUnk_096148D8, 32);
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
        p = gUnk_09EF126C;
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
                work->palette2 = LoadObjPalette(gUnk_08F69BE4, 32);
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
            pal = gUnk_09614418;
            work->palette3 = LoadObjPalette(pal, 32);
            LoadObjPaletteBank(work->palette3->index, pal);
            SetObjTileSource(work->tiles, gUnk_090A4664);
            AnimInit(&work->anim3, gUnk_09EEB03C, gUnk_09EEB008);
            AnimStart(&work->anim3, 2, ANIM_FLAG_LOOP);
            work->gfx3 = AnimGetGfx(&work->anim3);
            work->tiles2 = LoadObjTiles(gUnk_093F7C9C, 0xFC0);
            work->palette4 = LoadObjPalette(gCard00Palette, 32);
            work->choice = 0;
            work->cursorX = 0x5800;
            work->cursorY = gMsgwaitYesnoCursorY[work->choice];
#ifdef VERSION_EU
            work->textSlotCounts[0] = LoadTextSlots(eu_0805E924(&gUnkEu_08890E1C), work->textSlots);
            work->textSlotCounts[1] = LoadTextSlots(eu_0805E924(&gUnkEu_08890E44), work->textSlots2);
#else
            work->textSlotCounts[0] = LoadTextSlots(gUnk_08159E10, work->textSlots);
            work->textSlotCounts[1] = LoadTextSlots(gUnk_08159E18, work->textSlots2);
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
        1, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F660F4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0901048C,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F5B8,
#endif
        0,
        0,
    },
    {
        1, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66108,
#elif defined(VERSION_JP)
        gCardMessageTextJp_09010454,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F642,
#endif
        0,
        0,
    },
    {
        1, 3, 4, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6611C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_09010410,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F6A2,
#endif
        0,
        0,
    },
    {
        1, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66130,
#elif defined(VERSION_JP)
        gCardMessageTextJp_090103D0,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F714,
#endif
        0,
        0,
    },
    {
        1, 3, 3, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66144,
#elif defined(VERSION_JP)
        gCardMessageTextJp_09010394,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F778,
#endif
        0,
        0,
    },
    {
        1, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66158,
#elif defined(VERSION_JP)
        gCardMessageTextJp_09010348,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F7F0,
#endif
        0,
        0,
    },
    {
        1, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6616C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_09010314,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F87C,
#endif
        0,
        0,
    },
    {
        1, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66180,
#elif defined(VERSION_JP)
        gCardMessageTextJp_090102E0,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F8E4,
#endif
        0,
        0,
    },
    {
        1, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66194,
#elif defined(VERSION_JP)
        gCardMessageTextJp_090102A0,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F94C,
#endif
        0,
        0,
    },
    {
        1, 3, 3, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F661A8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_09010250,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F9BC,
#endif
        0,
        0,
    },
    {
        1, 3, 3, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F661BC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_09010218,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903FA2A,
#endif
        0,
        0,
    },
    {
        1, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F661D0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_090101DC,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903FAB2,
#endif
        0,
        0,
    },
    {
        1, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F661E4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_090101A0,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903FB04,
#endif
        0,
        0,
    },
    {
        1, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F661F8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_09010184,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903FB76,
#endif
        0,
        0,
    },
    {
        1, 3, 3, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6620C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_09010154,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903FBAC,
#endif
        0,
        0,
    },
    {
        1, 3, 4, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66220,
#elif defined(VERSION_JP)
        gCardMessageTextJp_09010124,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903FBFA,
#endif
        0,
        0,
    },
    {
        1, 3, 2, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66234,
#elif defined(VERSION_JP)
        gCardMessageTextJp_090100E8,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903FC6A,
#endif
        0,
        0,
    },
    {
        1, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66248,
#elif defined(VERSION_JP)
        gCardMessageTextJp_090100A4,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903FCDE,
#endif
        0,
        0,
    },
    {
        1, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6625C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_09010078,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903FD46,
#endif
        0,
        0,
    },
    {
        1, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66270,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0901003C,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903FDAA,
#endif
        0,
        0,
    },
    {
        1, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66284,
#elif defined(VERSION_JP)
        gCardMessageTextJp_09010000,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903FE34,
#endif
        0,
        0,
    },
    {
        1, 3, 2, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66298,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FFD0,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903FEA2,
#endif
        0,
        0,
    },
    {
        1, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F662AC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FF8C,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903FEF8,
#endif
        0,
        0,
    },
    {
        1, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F662C0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FF54,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903FF4E,
#endif
        0,
        0,
    },
    {
        1, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F662D4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FF08,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903FFC4,
#endif
        0,
        0,
    },
    {
        2, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F662E8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FED0,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040042,
#endif
        0,
        0,
    },
    {
        2, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F662FC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FEA0,
#elif defined(VERSION_US)
        gCardMessageTextUs_090400DC,
#endif
        0,
        0,
    },
    {
        2, 3, 3, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66310,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FE58,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040170,
#endif
        0,
        0,
    },
    {
        2, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66324,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FE14,
#elif defined(VERSION_US)
        gCardMessageTextUs_090401E4,
#endif
        0,
        0,
    },
    {
        2, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66338,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FDE8,
#elif defined(VERSION_US)
        gCardMessageTextUs_0904026E,
#endif
        0,
        0,
    },
    {
        2, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6634C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FDC0,
#elif defined(VERSION_US)
        gCardMessageTextUs_090402D0,
#endif
        0,
        0,
    },
    {
        2, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66360,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FD8C,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040328,
#endif
        0,
        0,
    },
    {
        2, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66374,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FD50,
#elif defined(VERSION_US)
        gCardMessageTextUs_090403A0,
#endif
        0,
        0,
    },
    {
        2, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66388,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FD18,
#elif defined(VERSION_US)
        gCardMessageTextUs_0904041C,
#endif
        0,
        0,
    },
    {
        2, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6639C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FCD0,
#elif defined(VERSION_US)
        gCardMessageTextUs_090404AA,
#endif
        0,
        0,
    },
    {
        2, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F663B0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FC80,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040552,
#endif
        0,
        0,
    },
    {
        2, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F663C4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FC38,
#elif defined(VERSION_US)
        gCardMessageTextUs_090405D8,
#endif
        0,
        0,
    },
    {
        2, 3, 4, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F663D8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FC00,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040662,
#endif
        0,
        0,
    },
    {
        2, 3, 3, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F663EC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FBCC,
#elif defined(VERSION_US)
        gCardMessageTextUs_090406E4,
#endif
        0,
        0,
    },
    {
        2, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66400,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FB90,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040758,
#endif
        0,
        0,
    },
    {
        2, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66414,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FB5C,
#elif defined(VERSION_US)
        gCardMessageTextUs_090407B2,
#endif
        0,
        0,
    },
    {
        2, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66428,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FB20,
#elif defined(VERSION_US)
        gCardMessageTextUs_0904083C,
#endif
        0,
        0,
    },
    {
        2, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6643C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FAE8,
#elif defined(VERSION_US)
        gCardMessageTextUs_090408CC,
#endif
        0,
        0,
    },
    {
        2, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66450,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FA90,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040932,
#endif
        0,
        0,
    },
    {
        2, 3, 4, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66464,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FA60,
#elif defined(VERSION_US)
        gCardMessageTextUs_090409E6,
#endif
        0,
        0,
    },
    {
        2, 3, 3, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66478,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FA2C,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040A5C,
#endif
        0,
        0,
    },
    {
        2, 3, 2, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6648C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900FA04,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040AEE,
#endif
        0,
        0,
    },
    {
        2, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F664A0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F9C4,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040B46,
#endif
        0,
        0,
    },
    {
        2, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F664B4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F998,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040BA8,
#endif
        0,
        0,
    },
    {
        2, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F664C8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F968,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040C0C,
#endif
        0,
        0,
    },
    {
        60, 3, 4, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F664DC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F934,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040C98,
#endif
        0,
        0,
    },
    {
        60, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F664F0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F8F4,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040D0E,
#endif
        0,
        0,
    },
    {
        27, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66504,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F8D0,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040D90,
#endif
        0,
        0,
    },
    {
        36, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F69614,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F8B0,
#elif defined(VERSION_US)
        gEventTextUs_0900868C,
#endif
        CARD_MSG_FLAG_CHOICE_AT_END,
        0,
    },
    {
        47, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F68368,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F880,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C10C,
#endif
        0,
        0,
    },
    {
        48, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F68354,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F844,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C186,
#endif
        0,
        0,
    },
    {
        50, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F68340,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F820,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C0D4,
#endif
        0,
        0,
    },
    {
        50, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6832C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F7E0,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C060,
#endif
        0,
        0,
    },
    {
        51, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F683A4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F798,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C20C,
#endif
        0,
        0,
    },
    {
        49, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F68390,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F75C,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C2F4,
#endif
        0,
        0,
    },
    {
        49, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6837C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F720,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C272,
#endif
        0,
        0,
    },
    {
        61, 3, 4, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6C97C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F6E8,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040DDA,
#endif
        0,
        0,
    },
    {
        61, 3, 1, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6C990,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F6B4,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040E4C,
#endif
        0,
        0,
    },
    {
        61, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6C9A4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F668,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040ED6,
#endif
        0,
        0,
    },
    {
        7, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F660CC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F638,
#elif defined(VERSION_US)
        gCardMessageTextUs_090411BA,
#endif
        0,
        0,
    },
    {
        7, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F660E0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F608,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041224,
#endif
        0,
        0,
    },
    {
        7, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F660B8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F5E8,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041176,
#endif
        0,
        0,
    },
    {
        7, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F660E0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F5C8,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041E66,
#endif
        0,
        0,
    },
    {
        7, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F660E0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F5A0,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041E66,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66068,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F588,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C03C,
#endif
        CARD_MSG_FLAG_CHOICE_AT_END | CARD_MSG_FLAG_CHOICE_WINDOW,
        0,
    },
    {
        3, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63E44,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F554,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C37E,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63E58,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F50C,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C410,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63E6C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F4D4,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C656,
#endif
        0,
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63E80,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F4AC,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C6F0,
#endif
        0,
        0,
    },
    {
        62, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63E94,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F498,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C76E,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63EA8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F424,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C79A,
#endif
        0,
        0,
    },
    {
        62, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63EBC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F40C,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C86C,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63ED0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F3A8,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C898,
#endif
        0,
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63EE4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F2E8,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C97C,
#endif
        0,
        0,
    },
    {
        62, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63EF8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F2A8,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903CAD0,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63F0C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F274,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903CB7C,
#endif
        0,
        0,
    },
    {
        62, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63F20,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F40C,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903CBE4,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63F34,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F234,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903CC10,
#endif
        0,
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63F48,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F1FC,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903CC80,
#endif
        0,
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63F5C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F1B4,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903CCF2,
#endif
        0,
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63F70,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F180,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903CD96,
#endif
        0,
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63F84,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F134,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903CE0C,
#endif
        0,
        0,
    },
    {
        62, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63F98,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F0EC,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903CEC4,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63FAC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900F010,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903CF58,
#endif
        0,
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63FC0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900EF60,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903D0BE,
#endif
        0,
        0,
    },
    {
        62, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63FD4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900EF2C,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903D1FA,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63FE8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900EEE4,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903D294,
#endif
        0,
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F63FFC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900EE28,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903D32E,
#endif
        0,
        0,
    },
    {
        62, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64010,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900EE00,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903D47A,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        3, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64024,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900ED7C,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903D4C2,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64164,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900ED44,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903E7EC,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64178,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900ED0C,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903E854,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6418C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900ECD4,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903E8C4,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F641A0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900EC94,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903E91C,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F641B4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900EC58,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903E9C8,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F641C8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900EC14,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903EA78,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F641DC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900EBD8,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903EB28,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F641F0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900EB18,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903EB8E,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64204,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900EAA0,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903ED16,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64204,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900EA28,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903ED16,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64218,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E980,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903EE14,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6422C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E914,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903EF68,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64240,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E8E8,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F02C,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64254,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E854,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F098,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64268,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E824,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F180,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6427C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E7F0,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F1E2,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64290,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E7C4,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F25A,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F642A4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E768,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F2D0,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F642B8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E710,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F410,
#endif
        0,
        0,
    },
    {
        31, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64038,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E648,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903D5E8,
#endif
        0,
        0,
    },
    {
        31, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6404C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E5E4,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903D774,
#endif
        0,
        0,
    },
    {
        31, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64060,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E528,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903D872,
#endif
        0,
        0,
    },
    {
        31, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64074,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E4F4,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903DA40,
#endif
        0,
        0,
    },
    {
        31, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64088,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E450,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903DA92,
#endif
        0,
        0,
    },
    {
        31, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6409C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E3E8,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903DC44,
#endif
        0,
        0,
    },
    {
        31, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F640B0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E398,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903DD36,
#endif
        0,
        0,
    },
    {
        31, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F640C4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E364,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903DDCA,
#endif
        0,
        0,
    },
    {
        31, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F640D8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E2EC,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903DE28,
#endif
        0,
        0,
    },
    {
        31, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F640EC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E240,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903DF44,
#endif
        0,
        0,
    },
    {
        62, 1, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64100,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E210,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903E0CA,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        31, 1, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64114,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E144,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903E142,
#endif
        0,
        0,
    },
    {
        62, 1, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64128,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E0F8,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903E2C8,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        31, 1, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6413C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900E00C,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903E370,
#endif
        0,
        0,
    },
    {
        31, 0, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F64150,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DF14,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903E5D4,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F682F0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DED0,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040F4E,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F68304,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DE50,
#elif defined(VERSION_US)
        gCardMessageTextUs_09040FE2,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F68318,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DE04,
#elif defined(VERSION_US)
        gCardMessageTextUs_090410E8,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6459C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DD60,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903C4C2,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66518,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DD34,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041492,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6652C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DCEC,
#elif defined(VERSION_US)
        gCardMessageTextUs_090414BE,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66540,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DCC8,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041522,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66554,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DCA4,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041548,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66568,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DC74,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041568,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6657C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DC20,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041594,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66590,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DBFC,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041606,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F665A4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DBD0,
#elif defined(VERSION_US)
        gCardMessageTextUs_0904162C,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F665B8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DBA4,
#elif defined(VERSION_US)
        gCardMessageTextUs_0904165C,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F665CC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DB78,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041690,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F665E0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DB4C,
#elif defined(VERSION_US)
        gCardMessageTextUs_090416C0,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F665F4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DB1C,
#elif defined(VERSION_US)
        gCardMessageTextUs_090416EA,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66608,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DAF0,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041718,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6661C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DAC4,
#elif defined(VERSION_US)
        gCardMessageTextUs_0904174A,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66630,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DA94,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041774,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66644,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DA64,
#elif defined(VERSION_US)
        gCardMessageTextUs_090417A4,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66658,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DA40,
#elif defined(VERSION_US)
        gCardMessageTextUs_090417DA,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6666C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900DA14,
#elif defined(VERSION_US)
        gCardMessageTextUs_090417FC,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66680,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D9E4,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041830,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66694,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D9C0,
#elif defined(VERSION_US)
        gCardMessageTextUs_0904185E,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F666A8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D99C,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041886,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F666BC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D974,
#elif defined(VERSION_US)
        gCardMessageTextUs_090418AC,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F666D0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D948,
#elif defined(VERSION_US)
        gCardMessageTextUs_090418DC,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F666E4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D91C,
#elif defined(VERSION_US)
        gCardMessageTextUs_0904190C,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F666F8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D8F8,
#elif defined(VERSION_US)
        gCardMessageTextUs_0904193C,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6670C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D8CC,
#elif defined(VERSION_US)
        gCardMessageTextUs_0904195C,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66798,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D8B0,
#elif defined(VERSION_US)
        gCardMessageTextUs_090419E2,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66784,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D88C,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041A08,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F667C0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D870,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041A38,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F667E8,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D854,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041A5C,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F667FC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D834,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041AE2,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66810,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D810,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041CAC,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66824,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D7DC,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041B10,
#endif
        CARD_MSG_FLAG_CHOICE_AT_END,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66838,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D7C4,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041B6C,
#endif
        CARD_MSG_FLAG_CHOICE_AT_END,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F642CC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D728,
#elif defined(VERSION_US)
        gCardMessageTextUs_0903F492,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66748,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D700,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041BA0,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6675C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D6D8,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041BDC,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66770,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D6B4,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041C14,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F6684C,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D68C,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041C46,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F667D4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D670,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041C7C,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66734,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D650,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041D06,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66720,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D650,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041CD6,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F667AC,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D610,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041D38,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F66018,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D5E0,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041D98,
#endif
        0,
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F697E0,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D560,
#elif defined(VERSION_US)
        gCardMessageTextUs_0904128A,
#endif
#if defined(VERSION_EU)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        CARD_MSG_FLAG_ALT_HIGHLIGHT,
#endif
        0,
    },
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_EU)
        &gUnkEu_09F660A4,
#elif defined(VERSION_JP)
        gCardMessageTextJp_0900D500,
#elif defined(VERSION_US)
        gCardMessageTextUs_090413BE,
#endif
        0,
        0,
    },
#ifndef VERSION_EU
    {
        62, 3, 0, 3, 0,
#if defined(VERSION_JP)
        gCardMessageTextJp_0900D4C0,
#elif defined(VERSION_US)
        gCardMessageTextUs_09041DE2,
#endif
        0,
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
