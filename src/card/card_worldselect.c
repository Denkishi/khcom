/**
 * card_worldselect.c
 * Map Card Selection and Inventory
 */

#include "macros.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "card_battle.h"
#include "player_progression.h"
#include "m4a_song.h"
#include "game_state.h"
#include "text.h"
#include "monsgage.h"
#include "fade.h"
#include "obj_api.h"
#include "display.h"
#include "engine_math.h"
#include "listpool.h"
#include "anim.h"
#include "obj.h"
#include "taskpool.h"
#include "key.h"
#include "gba/syscall.h"
#include "malloc.h"
#include "card.h"
#include "sprites_map.h"
#include "sprites_worldselect.h"
#include "battle_backgrounds.h"
#include "sprites_card_pictures.h"
#include "sprites_card.h"
#include "sprites_deck_menu.h"
#include "gba/keys.h"
#include "songs.h"
#include "card_selection_data.h"
#include "battle_work.h"
#include "card_api.h"
#include "card_def_data.h"
#include "card_types.h"
#include "card_ui_types.h"
#include "field_state.h"
#include "fld_types.h"
#include "gba/defines.h"
#include "map.h"
#include "map_runtime.h"
#include "map_text_data.h"
#include "mode.h"
#include "player_progression_types.h"
#include "types.h"
#include "gba/macro.h"
#include "sprite_palettes.h"
#include <stddef.h>
#include "lockon.h"
#include "card_worldselect.h"
#include "default_bg_map.h"

static TaskPool sModeWorldselectTasks;

static u8 sMapCardDelivered;

static void* sSelectedMapCard;

MapCardUiResources gMapCardUiResources EWRAM_COMMON(16);

u8 gMapCardCounts[270] EWRAM_COMMON(16);

void WORLDSELECT_0() {
    SetBgMode2();
    SetupBg(3, 0, 12, 0);
    SetupBg(2, 2, 28, 10);
    SetBgSize(3, 0x8000);
    LoadBgTiles(3, gBtlBgMonstroTiles, 0x4000);
    LoadBgPalette(3, gBtlBgMonstroPalette, 0x100);
#ifdef VERSION_EU
    LoadBgMapLz77(3, gBtlBgMonstroMap);
#else
    LoadBgMap(3, gBtlBgMonstroMap, 0x1000);
#endif
    SetBgAffine(3, 0, 0x100, 0x100, 0x10000, 0x16800);
    TaskPoolInit(&sModeWorldselectTasks, 1);
    TaskCreate(&sModeWorldselectTasks, &gTaskDescPremireChance, NULL);
}

void WORLDSELECT_1() {
    TaskPoolUpdate(&sModeWorldselectTasks);
    TaskPoolDraw(&sModeWorldselectTasks);
}

void WORLDSELECT_2() {
    TaskPoolDestroy(&sModeWorldselectTasks);
}

void MapSelect_0(MapSelectWork* work, u8* a) {
    s32 n;

    ResetMessageWindowFlags();
    CpuFill32(0, work, sizeof(MapSelectWork));
    work->status = a;
    *a = 0;
    work->messageTimer = 0;
    work->cancelled = 0;
    work->pageScroll = 0;
    work->card2 = NULL;
    sMapCardDelivered = 0;
    work->valueColumn = 0;
    work->valueRow = 0;
    work->scrollBarVisible = 0;
    work->isEventDoor = SelectCurrentEventDoor();
    n = GetCurrentRoomCardValue() + 1;
    work->requiredValue = n;

    if (n == 10) {
        work->requiredValue = 0;
    }

    work->tiles3 = NULL;

    if (!work->isEventDoor) {
        if (work->requiredValue == 0) {
            work->tiles4 = AllocSpriteFrameTiles(0x80);
            UpdateSpriteFrameTiles(work->tiles4, gUnk_09EF1198[0], gUnk_0950C478);
        } else {
            work->tiles4 = AllocSpriteFrameTiles(0x180);
            UpdateSpriteFrameTiles(work->tiles4, gUnk_09EF1198[1], gUnk_0950C478);
            RequestDma3Copy(work->tiles4->src + (work->requiredValue << 7),
                           (void*)(OBJ_VRAM0 + ((work->tiles4->index + 4) << 5)), 0x80);
            RequestDma3Copy(work->tiles4->src + 0x500,
                           (void*)(OBJ_VRAM0 + (work->tiles4->index << 5)), 0x80);
        }

        work->tiles2 = LoadObjTiles(gCardBacks[4].tiles2, 0x300);
        work->palette = LoadObjPalette(gUnk_09618D38, 32);
        FadeSetPaletteExcluded(work->palette->index + 16, 1);
    } else {
        work->tiles4 = NULL;
        work->tiles2 = NULL;
        work->palette = LoadObjPalette(gUnk_09618D38, 32);
        FadeSetPaletteExcluded(work->palette->index + 16, 1);
    }

    gMapCardUiResources.tiles = AllocObjTiles(0x280, NULL);
    SetObjTileSource(gMapCardUiResources.tiles, gUnk_0908B1B4);
    AnimInit(&gMapCardUiResources.anim, gUnk_09EEA164, gUnk_09EEA148);
    AnimStart(&gMapCardUiResources.anim, 0, ANIM_FLAG_LOOP);
    gMapCardUiResources.gfx = AnimGetGfx(&gMapCardUiResources.anim);
    work->tiles = AllocObjTiles(0x3C0, NULL);
    work->palette2 = LoadObjPalette(gUnk_09618D18, 32);
    SetObjTileSource(work->tiles, gUnk_093F47E4);
    AnimInit(&work->anim, gUnk_09EF1194, gUnk_09EF1180);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    work->tiles5 = AllocObjTiles(0x120, NULL);
    work->palette3 = LoadObjPalette(gUnk_09618CD8, 32);
    SetObjTileSource(work->tiles5, gUnk_093F4578);
    AnimInit(&work->anim2, gUnk_09EF1170, gUnk_09EF1150);
    AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
    work->gfx2 = AnimGetGfx(&work->anim2);
    work->tiles7 = LoadObjTiles(gUnk_093F5422, 0xC0);
    work->y3 = -0x800;
    work->y4 = 0xA000;
    work->barSteps = 16;
    work->slideSteps = 16;
    work->kindCount = CountOwnedMapCardKinds();
    TaskPoolInit(&work->tasks, work->kindCount + 10);
    ListPoolInit(&work->cards);
    work->kindEntries = EwramAlloc(work->kindCount * sizeof(MapSelectKindEntry));
    ListOwnedMapCardKinds(work->kindEntries);
    CreateMapSelectCards(work);
#ifdef VERSION_EU
    gMapCardUiResources.extraTiles = LoadObjTiles(gMapCardUiExtraTilesByLanguage[gLanguage], gMapCardUiExtraTileSizes[gLanguage]);
#else
    gMapCardUiResources.extraTiles = LoadObjTiles(gUnk_093F6734, 0x360);
#endif
    gMapCardUiResources.palette = work->palette3;
#ifdef VERSION_EU
    gMapCardUiResources.sprites = gMapCardUiSpritesByLanguage[gLanguage];
#else
    gMapCardUiResources.sprites = gUnk_09EF11F8;
#endif
    work->tiles6 = LoadObjTiles(gUnk_093F5C40, 32);
    work->page = 0;
    work->lastPage = 0;
    work->card = ListPoolFirst(&work->cards);
    work->prevCard = NULL;
    m4aSongNumStart(SONG_SYS_CLICKI02);
    sSelectedMapCard = NULL;
    work->x2 = 0x1600;
    work->y2 = 0x16400;
    work->unk_28D[0] = 0;
    work->unk_260 = 0;
    work->cursorTargetX = 0x1600;
    work->unk_268 = 0x6400;
    work->unk_28D[1] = 0;
    work->steps = 0;

    if (work->card != NULL) {
        work->x = work->card->x;
        work->y = work->card->y;
        work->card->flags |= MAPCARD_FLAG_CURSOR;
    } else {
        work->x = -0x6400;
        work->y = -0x6400;
    }

    work->x3 = -0xA000;
    work->titleY = 0;
    work->palette4 = LoadTextPalette(1);
    work->textSlotCounts[0] = 0;
    work->textSlotCounts[1] = 0;
    work->textSlotCounts[2] = 0;
    InitTextSlots(work->textSlots, 48);

    if (work->card != NULL) {
        work->prevCard = work->card;
        work->textSlotCounts[0] = LoadTextSlots(GetRoomName(gMapCardDefs[work->card->args.baseCardId].kind), work->textSlots);
    }

    work->nameY = 0x19100;
    FadeSetPaletteExcluded(work->palette3->index + 16, 1);
    FadeSetPaletteExcluded(work->palette2->index + 16, 1);
    FadeSetPaletteExcluded(15, 1);
    FadeSetPaletteExcluded(work->palette4->index + 16, 1);
    work->unk_1E4 = NULL;
    work->mosaicX = 9;
    work->mosaicY = 9;
    work->mosaicTimer = 0;
    work->inTutorial = 0;
}

u8 MapSelect_1(MapSelectWork* work, void* a) {
#ifdef VERSION_EU
    LoadBgTiles(1, gMapSelectTiles, 0x2020);

    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        work->tiles3 = LoadObjTiles(gUnk_093F7172, 0x400);
        break;
    case LANGUAGE_FRENCH:
        work->tiles3 = LoadObjTiles(gUnkEu_094C6C22, 0x400);
        RequestDma3Copy(gUnkEu_0952DDE4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
        break;
    case LANGUAGE_GERMAN:
        work->tiles3 = LoadObjTiles(gUnkEu_094C789A, 0x400);
        RequestDma3Copy(gUnkEu_0952E0E4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
        break;
    case LANGUAGE_ITALIAN:
        work->tiles3 = LoadObjTiles(gUnkEu_094C7472, 0x400);
        RequestDma3Copy(gUnkEu_0952DFE4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
        break;
    case LANGUAGE_SPANISH:
        work->tiles3 = LoadObjTiles(gUnkEu_094C704A, 0x400);
        RequestDma3Copy(gUnkEu_0952DEE4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
        break;
    }
#else
    work->tiles3 = LoadObjTiles(gUnk_093F7172, 0x400);
    LoadBgTiles(1, gMapSelectTiles, 0x2020);
#endif
    LoadPalette(gUnk_09618C58, (void*)(BG_PLTT + 12 * PLTT_SIZE_4BPP), 32);
    LoadPalette(&gUnk_09618C58[0x40], (void*)(BG_PLTT + 14 * PLTT_SIZE_4BPP), 64);
    FadeSetPaletteExcluded(12, 1);
    FadeSetPaletteExcluded(14, 1);
    FadeSetPaletteExcluded(15, 1);
    work->messageTimer++;
    DisableBg(1);
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectSetup);
    return 1;
}

u8 UpdateMapSelectSetup(MapSelectWork* work, void* a) {
    s32 n;

    SetBgMapBlocks(1, gMapSelectBgMapBlocks, 1, 2);
    work->bgScrollY = 0;
    ScrollBgMapTo(1, 0, 0);
    EnableBg(1);

    if (work->isEventDoor == 1) {
        work->remainingKeys = CountRemainingEventKeys();
        work->nextEventKey = GetEventKey(0);
        n = work->remainingKeys;

        while (n != 0) {
            n--;
        }

        work->eventKeyArgs.palette = work->palette3;
        work->eventKeyArgs.closeMode = 0;
        work->eventKey =
            TaskCreate(&work->tasks, &gTaskDescSELMAPEVKEY, &work->eventKeyArgs)->work;
    }

    LoadMapSelectKindPalette(work->card->args.baseCardId, work);
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectSlideIn);
    return 1;
}

u8 UpdateMapSelectSlideIn(MapSelectWork* work, void* a) {
    MapcardWork* n;

    if (work->barSteps != 0) {
        ApproachValue(&work->y3, 0, work->barSteps);
        ApproachValue(&work->y4, 0x9800, work->barSteps);
        work->barSteps--;
    } else {
        ApproachValue(&work->bgScrollY, 0x10000, work->slideSteps);
        ApproachValue(&work->x3, 0, work->slideSteps);
        ScrollBgMapTo(1, 0, (u32)work->bgScrollY >> 8);

        if (work->slideSteps != 0) {
            work->slideSteps--;
        } else {
            if ((gGameState.progression.tutorialFlags & 8) == 0) {
                work->inTutorial = 1;
                ResetMessageWindowFlags();
                work->tutorialMessage = 95;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectTutorial);
            } else if ((gGameState.progression.tutorialFlags & 0x40) == 0 && work->isEventDoor == 1) {
                ResetMessageWindowFlags();
                work->tutorialMessage = 109;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectEventDoorTutorial);
                gGameState.progression.tutorialFlags |= 0x40;
            } else {
                n = ListPoolFirst(&work->cards);
                SetBgMapBlocks(1, gMapSelectBgMapBlocks, 1, 2);

                while (n != NULL) {
                    n->flags |= MAPCARD_FLAG_RAISED;
                    n = ListPoolNext(&n->node);
                }

                if (work->kindCount <= 6) {
                    work->lastPage = 0;
                } else {
                    work->lastPage = work->kindCount / 6;

#ifdef VERSION_EU
                    if ((u16)(work->kindCount % 6) == 0) {
                        work->lastPage--;
                    }
#endif
                }

                work->y2 = 0x6400;
                work->y = 0x7A00;
                work->nameY = 0x9100;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectKindInput);
                work->scrollBarVisible = 1;
            }
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 UpdateMapSelectEnterValues(MapSelectWork* work, void* a) {
    s8 v;

    if (work->card->steps == 0) {
        LoadBgTiles(1, gMapSelectValuesTiles, 0x23C0);

#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            break;
        case LANGUAGE_FRENCH:
            RequestDma3Copy(gUnkEu_0952DDE4, (u8*)GetBgCharBase(1) + 0x1EA0, 0x100);
            break;
        case LANGUAGE_GERMAN:
            RequestDma3Copy(gUnkEu_0952E0E4, (u8*)GetBgCharBase(1) + 0x1EA0, 0x100);
            break;
        case LANGUAGE_ITALIAN:
            RequestDma3Copy(gUnkEu_0952DFE4, (u8*)GetBgCharBase(1) + 0x1EA0, 0x100);
            break;
        case LANGUAGE_SPANISH:
            RequestDma3Copy(gUnkEu_0952DEE4, (u8*)GetBgCharBase(1) + 0x1EA0, 0x100);
            break;
        }
#endif

        LoadBgMap(1, gMapSelectValuesMap, 0x800);
        LoadMapSelectGridPalette(work->card->args.baseCardId, work);
        v = LoadMapSelectValueCounts(work->card->args.baseCardId, work);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectValueInput);
        ReleaseObjTiles(work->tiles);
        work->tiles = AllocObjTiles(0x1E0, NULL);
        SetObjTileSource(work->tiles, gUnk_093F556C);
        AnimInit(&work->anim, gUnk_09EF11CC, gUnk_09EF11B8);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        work->gfx = AnimGetGfx(&work->anim);
        work->savedCursorX = work->x2 >> 8;
        work->savedCursorY = work->y2 >> 8;

        if (v > 4) {
            work->valueColumn = v - 5;
            work->valueRow = 1;
        } else {
            work->valueColumn = v;
            work->valueRow = 0;
        }

        work->steps = 4;
        work->steps2 = 4;
        work->scrollBarVisible = 0;
    }

    SetObjMosaicSize(work->mosaicX, work->mosaicY);

    if (work->mosaicTimer == 2) {
        if (work->mosaicX != 0) {
            work->mosaicX--;
        }

        if (work->mosaicY != 0) {
            work->mosaicY--;
        }

        work->mosaicTimer = 0;
    }

    work->mosaicTimer++;
    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 UpdateMapSelectValueInput(MapSelectWork* work, void* a) {
    u16 keys;
    s16 sel;
    u8 n;

    keys = GetKeysPressed();
    sel = work->valueColumn + work->valueRow * 5;

    if ((gGameState.progression.tutorialFlags & 8) == 0) {
        if (work->steps == 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectValueTutorial);
            TaskPoolUpdate(&work->tasks);
            return 1;
        }

        keys = 0;
    }

    switch (keys & (A_BUTTON | B_BUTTON | SELECT_BUTTON | START_BUTTON | L_BUTTON | R_BUTTON)) {
    case B_BUTTON:
        LoadBgTiles(1, gMapSelectTiles, 0x2020);
#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            break;
        case LANGUAGE_FRENCH:
            RequestDma3Copy(gUnkEu_0952DDE4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
            break;
        case LANGUAGE_GERMAN:
            RequestDma3Copy(gUnkEu_0952E0E4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
            break;
        case LANGUAGE_ITALIAN:
            RequestDma3Copy(gUnkEu_0952DFE4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
            break;
        case LANGUAGE_SPANISH:
            RequestDma3Copy(gUnkEu_0952DEE4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
            break;
        }
#endif
        LoadBgMap(1, gMapSelectMap, 0x800);
        work->card->flags &= ~MAPCARD_FLAG_OPENED;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectLeaveValues);
        m4aSongNumStart(SONG_SYS_CLOSE);
        break;
    case A_BUTTON:
        n = DoorAcceptsMapCard((struct MapCardAttributes*)&gMapCardDefs[work->card->args.baseCardId + sel].kind);

        if (n == 1) {
            if (gMapCardCounts[work->card->args.baseCardId + sel] != 0) {
                if (work->isEventDoor == 1) {
                    m4aSongNumStart(SONG_SYS_KETEI2);

                    if (CountMapCardsOfKind(work->card->args.baseCardId) == 0) {
                        work->card->value = sel;
                        work->card->flags |= MAPCARD_FLAG_CHOSEN;
                    }

                    RemoveMapCard(work->card->args.baseCardId + sel);

                    if ((u8)PayEventKey((struct MapCardAttributes*)&gMapCardDefs[work->card->args.baseCardId + sel].kind) == 1) {
                        work->remainingKeys = CountRemainingEventKeys();
                        work->eventKey->paidCount++;
                        work->eventKey->slideSteps = 8;

                        if (work->remainingKeys == 0) {
                            work->card->value = sel;
                            work->card->flags |= MAPCARD_FLAG_CHOSEN;
                            *work->status = 2;
                            work->slideSteps = 16;
                            work->barSteps = 16;
                            work->lastPage = 0;
                            work->page = 0;
                            work->eventKeyArgs.closeMode = n;
                            SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectClose);
                            return 1;
                        }
                    }

                    LoadMapSelectKindPalette(work->card->args.baseCardId, work);
                    LoadMapSelectGridPalette(work->card->args.baseCardId, work);

                    if ((s8)LoadMapSelectValueCounts(work->card->args.baseCardId, work) == -1) {
                        LoadBgTiles(1, gMapSelectTiles, 0x2020);
#ifdef VERSION_EU
                        switch (gLanguage) {
                        case LANGUAGE_ENGLISH:
                            break;
                        case LANGUAGE_FRENCH:
                            RequestDma3Copy(gUnkEu_0952DDE4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
                            break;
                        case LANGUAGE_GERMAN:
                            RequestDma3Copy(gUnkEu_0952E0E4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
                            break;
                        case LANGUAGE_ITALIAN:
                            RequestDma3Copy(gUnkEu_0952DFE4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
                            break;
                        case LANGUAGE_SPANISH:
                            RequestDma3Copy(gUnkEu_0952DEE4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
                            break;
                        }
#endif
                        LoadBgMap(1, gMapSelectMap, 0x800);
                        work->card->flags &= ~MAPCARD_FLAG_OPENED;
                        RemoveMapSelectCard(work);
                        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectLeaveValues);
                    }

                    break;
                }

                work->card->value = sel;
                work->card->flags |= MAPCARD_FLAG_CHOSEN;
                RemoveMapCard(work->card->args.baseCardId + sel);
                *work->status = 2;
                work->slideSteps = 16;
                work->barSteps = 16;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectClose);
                m4aSongNumStart(SONG_SYS_KETEI2);
                work->lastPage = 0;
                work->page = 0;
                work->eventKeyArgs.closeMode = n;
                return 1;
            }
        }

        m4aSongNumStart(SONG_SYS_BEEP);
        break;
    }

    work->gfx2 = AnimUpdate(&work->anim2);
    work->gfx = AnimUpdate(&work->anim);
    gMapCardUiResources.gfx = AnimUpdate(&gMapCardUiResources.anim);
    TaskPoolUpdate(&work->tasks);
    HandleMapSelectValueCursor(work);
    SetObjMosaicSize(work->mosaicX, work->mosaicY);

    if (work->mosaicTimer == 2) {
        if (work->mosaicX != 0) {
            work->mosaicX--;
        }

        if (work->mosaicY != 0) {
            work->mosaicY--;
        }

        work->mosaicTimer = 0;
    }

    work->mosaicTimer++;
    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 UpdateMapSelectLeaveValues(MapSelectWork* work, void* a) {
    MapcardWork* node;

    if (CountOwnedMapCardKinds() == 0) {
        return 0;
    }

    if (work->card->steps == 0) {
        node = ListPoolFirst(&work->cards);

        while (node != NULL) {
            if (work->card != node) {
                node->flags |= MAPCARD_FLAG_RAISED;
            }

            node = ListPoolNext(&node->node);
        }

        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectKindInput);
        ReleaseObjTiles(work->tiles);
        work->tiles = AllocObjTiles(0x3C0, NULL);
        SetObjTileSource(work->tiles, gUnk_093F47E4);
        AnimInit(&work->anim, gUnk_09EF1194, gUnk_09EF1180);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        work->gfx = AnimGetGfx(&work->anim);
        work->x2 = work->savedCursorX << 8;
        work->y2 = work->savedCursorY << 8;
        work->x = work->card->x;
        work->y = work->card->y;
        work->scrollBarVisible = 1;
    }

    SetObjMosaicSize(work->mosaicX, work->mosaicY);

    if (work->mosaicTimer == 2) {
        if (work->mosaicX != 0) {
            work->mosaicX--;
        }

        if (work->mosaicY != 0) {
            work->mosaicY--;
        }

        work->mosaicTimer = 0;
    }

    work->mosaicTimer++;
    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 UpdateMapSelectKindInput(MapSelectWork* work, void* a) {
    u16 keys = GetKeysPressed();
    MapcardWork* p;

    ApplyMapSelectPageScroll(work);
    SetObjMosaicSize(work->mosaicX, work->mosaicY);

    if (work->mosaicTimer == 2) {
        if (work->mosaicX != 0) {
            work->mosaicX--;
        }

        if (work->mosaicY != 0) {
            work->mosaicY--;
        }

        work->mosaicTimer = 0;
    }

    work->mosaicTimer++;

    switch (keys & (A_BUTTON | B_BUTTON | SELECT_BUTTON | START_BUTTON | L_BUTTON | R_BUTTON)) {
    case A_BUTTON:
        if (work->card != NULL) {
            if (work->card->args.baseCardId >= 220) {
                if (DoorAcceptsMapCard((struct MapCardAttributes*)&gMapCardDefs[work->card->args.baseCardId + 1].kind) == 1) {
                    if (gMapCardCounts[work->card->args.baseCardId + 1] != 0) {
                        m4aSongNumStart(SONG_SYS_KETEI2);
                        RemoveMapCard(work->card->args.baseCardId + 1);

                        if ((u8)PayEventKey((struct MapCardAttributes*)&gMapCardDefs[work->card->args.baseCardId + 1].kind) == 1) {
                            work->remainingKeys = CountRemainingEventKeys();
                            work->eventKey->paidCount++;
                            work->eventKey->slideSteps = 8;

                            if (work->remainingKeys == 0) {
                                work->card->value = 1;
                                work->card->flags |= MAPCARD_FLAG_CHOSEN;

                                for (p = ListPoolFirst(&work->cards); p != NULL; p = ListPoolNext(&p->node)) {
                                    if (work->card != p) {
                                        p->flags &= ~MAPCARD_FLAG_RAISED;
                                    }
                                }

                                *work->status = 2;
                                work->slideSteps = 16;
                                work->barSteps = 16;
                                work->lastPage = 0;
                                work->page = 0;
                                work->eventKeyArgs.closeMode = 1;
                                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectClose);
                                return 1;
                            }
                        }

                        break;
                    }
                }
            } else {
                if (CountMapCardsOfKind(work->card->args.baseCardId) != 0) {
                    for (p = ListPoolFirst(&work->cards); p != NULL; p = ListPoolNext(&p->node)) {
                        if (work->card != p) {
                            p->flags &= ~MAPCARD_FLAG_RAISED;
                        }
                    }

                    if (work->card != NULL) {
                        work->openedCardX = work->card->x;
                        work->card->flags |= MAPCARD_FLAG_OPENED;
                    }

                    m4aSongNumStart(SONG_SYS_KETTEI);
                    SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectEnterValues);
                    return 1;
                }
            }
        }

        m4aSongNumStart(SONG_SYS_BEEP);
        break;
    case B_BUTTON:
        if (!work->inTutorial) {
            for (p = ListPoolFirst(&work->cards); p != NULL; p = ListPoolNext(&p->node)) {
                p->flags &= ~MAPCARD_FLAG_RAISED;
            }

            work->cancelled = 1;
            work->slideSteps = 16;
            work->barSteps = 16;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectClose);
            m4aSongNumStart(SONG_SYS_CANSEL);
            sSelectedMapCard = NULL;
            work->lastPage = 0;
            work->page = 0;
            work->eventKeyArgs.closeMode = 2;
        } else {
            m4aSongNumStart(SONG_SYS_BEEP);
        }

        break;
    }

    HandleMapSelectKindCursor(work);

    if (work->pageScroll == 0) {
        if (work->card != work->prevCard) {
            if (work->card != NULL) {
                work->textSlotCounts[0] = LoadTextSlots(GetRoomName(gMapCardDefs[work->card->args.baseCardId].kind), work->textSlots);
                LoadMapSelectKindPalette(work->card->args.baseCardId, work);
            } else {
                work->textSlotCounts[0] = 0;
                work->textSlotCounts[1] = 0;
                work->textSlotCounts[2] = 0;
            }

            work->prevCard = work->card;
            work->steps = 4;
        } else if (work->card != NULL) {
            ApproachValue(&work->x, work->card->x, work->steps);
            ApproachValue(&work->y, work->card->y, work->steps);

            if (work->steps != 0) {
                work->steps--;
            }
        }
    }

    work->gfx2 = AnimUpdate(&work->anim2);
    work->gfx = AnimUpdate(&work->anim);
    gMapCardUiResources.gfx = AnimUpdate(&gMapCardUiResources.anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 UpdateMapSelectClose(MapSelectWork* work) {
    ApproachValue(&work->bgScrollY, 0, work->slideSteps);
    ApproachValue(&work->x3, -0xA000, work->slideSteps);
    ApproachValue(&work->y2, 0x16400, work->slideSteps);
    ApproachValue(&work->y, 0x17A00, work->slideSteps);
    ApproachValue(&work->nameY, 0x19100, work->slideSteps);
    ScrollBgMapTo(1, 0, (u32)work->bgScrollY >> 8);
    work->scrollBarVisible = 0;

    if (work->mosaicX <= 8) {
        work->mosaicX++;
    }

    if (work->mosaicY <= 8) {
        work->mosaicY++;
    }

    SetObjMosaicSize(work->mosaicX, work->mosaicY);

    if (work->slideSteps != 0) {
        work->slideSteps--;
    } else if (work->barSteps != 0) {
        ApproachValue(&work->y3, -0x800, work->barSteps);
        ApproachValue(&work->y4, 0xA000, work->barSteps);
        work->barSteps--;
    } else {
        if (work->cancelled || (work->card->flags & MAPCARD_FLAG_DELIVERED)) {
            return 0;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void MapSelect_2(MapSelectWork* work) {
    if (work->tiles3 != NULL && work->palette3 != NULL) {
        DrawSprite(work->x3 >> 8, work->titleY >> 8,
#ifdef VERSION_EU
                   gMapSelectTitleSpritesByLanguage[gLanguage][0],
#else
                   gUnk_09EF1228[0],
#endif
                   work->tiles3, work->palette3, NULL, 0, 80);
    }

    if (work->isEventDoor == 1) {
        switch (gMapCardDefs[work->card->args.baseCardId].backIndex) {
        case 0:
            break;
        case 2:
            DrawSprite((work->card->x >> 8) + 4, (work->card->y >> 8) - 32, gMapCardUiResources.sprites[3], gMapCardUiResources.extraTiles, gMapCardUiResources.palette, NULL, 0, 20);
            break;
        case 3:
            DrawSprite((work->card->x >> 8) + 4, (work->card->y >> 8) - 32, gMapCardUiResources.sprites[7], gMapCardUiResources.extraTiles, gMapCardUiResources.palette, NULL, 0, 20);
            break;
        case 1:
            DrawSprite((work->card->x >> 8) + 4, (work->card->y >> 8) - 32, gMapCardUiResources.sprites[5], gMapCardUiResources.extraTiles, gMapCardUiResources.palette, NULL, 0, 20);
            break;
        case 4:
            break;
        }
    }

    if (!IsMessageWindowOpen()) {
        DrawSprite((work->x >> 8) - 23, (work->y >> 8) - 27, work->gfx, work->tiles, work->palette2, NULL, 0, 41);
        DrawSprite((work->x2 >> 8) - 16, (work->y2 >> 8) - 12, work->gfx2, work->tiles5, work->palette3, NULL, 0, 40);
    }

    if (work->scrollBarVisible) {
        DrawSprite(224,
#ifdef VERSION_EU
                   (18 / work->lastPage) * work->page + 108,
#else
                   (17 / work->lastPage) * work->page + 108,
#endif
                   gUnk_09EEB000[0], work->tiles6, work->palette, NULL, 0, 40);
    }

    if (!work->isEventDoor && work->mosaicX != 9 && work->mosaicY != 9) {
        DrawSprite(120, 56, NULL, work->tiles4, work->palette, NULL, SPRITE_FLAG_MOSAIC, 60);
        DrawSprite(120, 56, gCardBacks[4].gfx2, work->tiles2, work->palette, NULL, SPRITE_FLAG_MOSAIC, 60);
    }

    DrawSprite(128, work->y3 >> 8, gUnk_09EF11AC[0], work->tiles7, work->palette3, NULL, SPRITE_PRIORITY(2), 80);
    DrawSprite(128, work->y4 >> 8, gUnk_09EF11AC[1], work->tiles7, work->palette3, NULL, SPRITE_PRIORITY(2), 80);
    DrawTextSlots(16, work->nameY >> 8, work->textSlots, work->palette4, 50, work->textSlotCounts[0]);
    TaskPoolDraw(&work->tasks);
}

void MapSelect_3(MapSelectWork* work) {
    TaskPoolDestroy(&work->tasks);

    if (work->kindEntries != NULL) {
        EwramFree(work->kindEntries);
    }

    FadeSetPaletteExcluded(work->palette3->index + 16, 0);
    FadeSetPaletteExcluded(work->palette2->index + 16, 0);
    FadeSetPaletteExcluded(15, 0);
    FadeSetPaletteExcluded(work->palette4->index + 16, 0);
    ReleaseObjTiles(work->tiles5);
    ReleaseObjPalette(work->palette3);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette2);
    ReleaseObjTiles(work->tiles3);

    if (work->tiles4 != NULL) {
        ReleaseObjTiles(work->tiles4);
    }

    if (work->tiles2 != NULL) {
        ReleaseObjTiles(work->tiles2);
    }

    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
    }

    ReleaseObjTiles(work->tiles7);
    FreeTextSlots(work->textSlots, 48);
    ReleaseObjPalette(work->palette4);
    *work->status = 1;
    ReleaseObjTiles(work->tiles6);
    ReleaseObjTiles(gMapCardUiResources.tiles);
    ReleaseObjTiles(gMapCardUiResources.extraTiles);
}

void CreateMapSelectCards(MapSelectWork* work) {
    MapcardArgs args;
    MapSelectKindEntry* q;
    u16 i;

    for (i = 0; i < work->kindCount; i++) {
        q = work->kindEntries;
        args.baseCardId = q[i].baseCardId;
        args.index = i;
        args.kindCount = work->kindCount;
        args.count = q[i].count;
        args.pool = &work->cards;
        args.parent = work;
        CreateMapCard(&args, &work->tasks);
    }
}

u16 CountOwnedMapCardKinds() {
    u16 count;
    u16 i;
    u16 j;

    count = 0;

    for (j = 0; j < 27; j++) {
        for (i = j * 10; i < j * 10 + 10; i++) {
            if (gMapCardCounts[i] != 0) {
                count++;
                break;
            }
        }
    }

    return count;
}

void ListOwnedMapCardKinds(MapSelectKindEntry* p) {
    u16 i;
    u16 j;

    for (i = 0; i <= 26; i++) {
        j = i * 10;

        while (j < i * 10 + 10) {
            if (gMapCardCounts[j] != 0) {
                p->baseCardId = i * 10;
                p->count = gMapCardCounts[j];
                p++;
                break;
            }

            j++;
        }
    }
}

void HandleMapSelectKindCursor(MapSelectWork* work) {
    MapcardWork* a;
    MapcardWork* b;
    MapcardWork* found;
    MapcardWork* p;
    MapcardWork* c;
    s8 cnt;

    if (work->pageScroll != 0) {
        return;
    }

    if (work->card == NULL) {
        return;
    }

    switch (GetKeysRepeat() & DPAD_ANY) {
    case DPAD_RIGHT:
        p = ListPoolNext(&work->card->node);

        if (p != NULL && (p->flags & MAPCARD_FLAG_GFX_LOADED)) {
            work->cursorTargetX = p->x;
            work->steps2 = 4;
            work->card->flags &= ~MAPCARD_FLAG_CURSOR;
            work->card = ListPoolNext(&work->card->node);
            work->card->flags |= MAPCARD_FLAG_CURSOR;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        break;
    case DPAD_LEFT:
        p = ListPoolPrev(&work->card->node);

        if (p != NULL && (p->flags & MAPCARD_FLAG_GFX_LOADED)) {
            work->cursorTargetX = p->x;
            work->steps2 = 4;
            work->card->flags &= ~MAPCARD_FLAG_CURSOR;
            work->card = ListPoolPrev(&work->card->node);
            work->card->flags |= MAPCARD_FLAG_CURSOR;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        break;
    case DPAD_DOWN:
        a = ListPoolFirst(&work->cards);
        b = NULL;
        found = NULL;
        cnt = 0;

        while (a != NULL) {
            if (a->flags & MAPCARD_FLAG_GFX_LOADED) {
                b = a;
                break;
            }

            a = ListPoolNext(&a->node);
        }

        for (;;) {
            if (b != NULL) {
                if (b->flags & MAPCARD_FLAG_GFX_LOADED) {
                    cnt++;
                    b = ListPoolNext(&b->node);
                    continue;
                }

                if (cnt == 6) {
                    found = b;
                }
            }

            break;
        }

        if (found != NULL) {
            work->card2 = found;
            work->pageScroll = 1;

            if (a != NULL) {
                do {
                    if (a->flags & MAPCARD_FLAG_GFX_LOADED) {
                        a->x = -0x6400;
                        a->flags &= ~MAPCARD_FLAG_CURSOR;
                        a = ListPoolNext(&a->node);
                    } else {
                        break;
                    }
                } while (a != NULL);
            }

            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        b = ListPoolFirst(&work->cards);

        while (b != NULL) {
            if (b->x == -0x6400) {
                a->flags &= ~MAPCARD_FLAG_CURSOR;
            }

            b = ListPoolNext(&b->node);
        }

        break;
    case DPAD_UP:
        a = ListPoolFirst(&work->cards);
        b = NULL;

        while (a != NULL) {
            if (a->flags & MAPCARD_FLAG_GFX_LOADED) {
                b = a;
                break;
            }

            a = ListPoolNext(&a->node);
        }

        if (ListPoolPrev(&a->node) != NULL) {
            work->card2 = ListPoolPrev(&a->node);
            work->pageScroll = 2;

            if (b != NULL) {
                c = b;

                do {
                    if ((c->flags & MAPCARD_FLAG_GFX_LOADED) == 0) {
                        break;
                    }

                    b->x = -0x6400;
                    b = c = ListPoolNext(&b->node);
                } while (b != NULL);
            }

            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }

        b = ListPoolFirst(&work->cards);

        while (b != NULL) {
            if (b->x == -0x6400) {
                a->flags &= ~MAPCARD_FLAG_CURSOR;
            }

            b = ListPoolNext(&b->node);
        }

        break;
    }

    ApproachValue(&work->x2, work->cursorTargetX, work->steps2);

    if (work->steps2 != 0) {
        work->steps2--;
    }
}

void ApplyMapSelectPageScroll(MapSelectWork* work) {
    MapcardWork* node;
    s8 i;

    switch (work->pageScroll) {
    case 0:
        break;
    case 1:
        node = work->card2;
        i = 0;

        while (node != NULL) {
            node->x = gMapcardSlotX[i++] << 8;

            if (i == 6) {
                break;
            }

            node = ListPoolNext(&node->node);
        }

        work->pageScroll = 0;
        SelectNearestMapSelectCard(work);

        if (work->card != NULL) {
            work->cursorTargetX = work->card->x;
            work->steps2 = 4;
        }

        work->page++;
        break;
    case 2:
        node = work->card2;
        i = 5;

        while (node != NULL) {
            node->x = gMapcardSlotX[i--] << 8;

            if (i < 0) {
                break;
            }

            node = ListPoolPrev(&node->node);
        }

        work->pageScroll = 0;
        SelectNearestMapSelectCard(work);

        if (work->card != NULL) {
            work->cursorTargetX = work->card->x;
            work->steps2 = 4;
        }

        work->page--;
        break;
    }
}

s32 SelectNearestMapSelectCard(MapSelectWork* work) {
    MapcardWork* node;
    s32 best;
    s32 d;
    u16 r;
    void* z;
    void* q;

    node = ListPoolFirst(&work->cards);
    best = 0x100;
    z = NULL;
    work->card = z;

    while (node != NULL) {
        if (node->x != -0x6400) {
            d = (node->x >> 8) - (work->x2 >> 8);
            r = Sqrt(d * d);

            if (best > r) {
                best = r;
                work->card = node;
            }
        }

        node = ListPoolNext(&node->node);
    }

    q = work->card;

    if (q != NULL) {
        q = &((MapcardWork*)q)->flags;
        r = *(u16*)q | MAPCARD_FLAG_CURSOR;
        *(u16*)q = r;

        return (work->card->x - work->x2) >> 8;
    }

    return 0;
}

u16 CountMapCards() {
    u8 sum;
    s32 i;

    sum = 0;

    for (i = 0; i <= 0x10D; i++) {
        sum += gMapCardCounts[i];
    }

    return sum;
}

s32 AddMapCard(u16 a) {
    if (CountRegularMapCards() <= 98) {
        if (gMapCardCounts[a] <= 8) {
            gMapCardCounts[a]++;

            switch (gMapCardDefs[a].kind) {
            case 0:
                SetJiminyFlag(209);
                break;
            case 1:
                SetJiminyFlag(210);
                break;
            case 2:
                SetJiminyFlag(211);
                break;
            case 3:
                SetJiminyFlag(212);
                break;
            case 4:
                SetJiminyFlag(213);
                break;
            case 5:
                SetJiminyFlag(214);
                break;
            case 6:
                SetJiminyFlag(215);
                break;
            case 7:
                SetJiminyFlag(216);
                break;
            case 8:
                SetJiminyFlag(217);
                break;
            case 9:
                SetJiminyFlag(218);
                break;
            case 10:
                SetJiminyFlag(219);
                break;
            case 11:
                SetJiminyFlag(220);
                break;
            case 12:
                SetJiminyFlag(221);
                break;
            case 13:
                SetJiminyFlag(222);
                break;
            case 14:
                SetJiminyFlag(223);
                break;
            case 15:
                SetJiminyFlag(224);
                break;
            case 16:
                SetJiminyFlag(225);
                break;
            case 17:
                SetJiminyFlag(226);
                break;
            case 18:
                SetJiminyFlag(227);
                break;
            case 19:
                SetJiminyFlag(228);
                break;
            case 20:
                SetJiminyFlag(229);
                break;
            case 21:
                SetJiminyFlag(230);
                break;
            case 22:
                SetJiminyFlag(231);
                break;
            case 23:
                SetJiminyFlag(232);
                break;
            case 24:
                SetJiminyFlag(233);
                break;
            case 25:
                SetJiminyFlag(234);
                break;
            }

            return 1;
        }
    } else {
        if (gMapCardDefs[a].kind > 21) {
            gMapCardCounts[a]++;

            switch (gMapCardDefs[a].kind) {
            case 22:
                SetJiminyFlag(231);
                break;
            case 23:
                SetJiminyFlag(232);
                break;
            case 24:
                SetJiminyFlag(233);
                break;
            case 25:
                SetJiminyFlag(234);
                break;
            }

            return 1;
        }
    }

    return 0;
}

s32 RemoveMapCard(u16 a) {
    if (gMapCardCounts[a] != 0) {
        gMapCardCounts[a]--;
        return 1;
    }

    return 0;
}

s32 AddRandomMapCard() {
    AddMapCard(GetRandom() % 270);
}

u16 CountMapCardsOfKind(u16 a) {
    u16 sum;
    s32 i;

    sum = 0;

    for (i = a; i < a + 10; i++) {
        sum += gMapCardCounts[i];
    }

    return sum;
}

u16 CountRegularMapCards() {
    u16 sum;
    s32 i;

    sum = 0;

    for (i = 0; i < 220; i++) {
        sum += gMapCardCounts[i];
    }

    return sum;
}

u16 CountZeroValueMapCards() {
    u16 sum;
    s32 i;

    sum = 0;

    for (i = 0; i < 27; i++) {
        sum += gMapCardCounts[i * 10];
    }

    return sum;
}

void CreateMapCardSelection(TaskPool* pool, u8* p) {
    TaskCreate(pool, &gTaskDescMapSelect, p);
}

void ClearMapCardInventory() {
    u16 i;

    for (i = 0; i < 270; i++) {
        gMapCardCounts[i] = 0;
    }
}

void InitMapCardInventory() {
    ClearMapCardInventory();

    if (gDebugFlags & DEBUG_FLAG_ALL_MAP_CARD) {
#ifdef VERSION_EU
        s32 i;

        AddMapCard(211);
        AddMapCard(191);

        for (i = 0; i <= 219; i += 10) {
            if (CountMapCards() <= 98) {
                AddMapCard(i);
            }
        }

        AddMapCard(221);
        AddMapCard(231);
        AddMapCard(241);
        AddMapCard(251);
#endif
    } else {
        AddMapCard(191);
    }
}

u8 IsMapCardDelivered() {
    return sMapCardDelivered;
}

void SetMapCardDelivered() {
    sMapCardDelivered = 1;
}

void SetSelectedMapCard(void* a) {
    sSelectedMapCard = a;
}

void* GetSelectedMapCard() {
    return sSelectedMapCard;
}

void ResetSelectedMapCard() {
    sSelectedMapCard = NULL;
    sMapCardDelivered = 0;
}

const void* GetRoomName(u16 a) {
#ifdef VERSION_EU
    return GetLocalizedString(gRoomNames[a]);
#else
    return gRoomNames[a];
#endif
}

u8 HasMapCard(u16 a) {
    if (gMapCardCounts[a] != 0) {
        return 1;
    }

    return 0;
}

void LoadMapSelectKindPalette(u16 a, MapSelectWork* work) {
    u16 i;
    u16 j;
    u8* pal;
    s32 k;
    s32 k2;
    MapCardDef* card;
    MapCardDef* cards;

    for (i = 0; i < 22; i++) {
        pal = work->paletteBuffer;
        pal[i] = gUnk_09619098[i + 32];
    }

    for (i = 22; i < 32; i++) {
        pal = work->paletteBuffer;
        pal[i] = gUnk_09618C58[i + 64];
    }

    for (i = a, j = 2; i < a + 10; i++, j += 2) {
        cards = gMapCardDefs;
        card = &cards[a];
        pal = work->paletteBuffer;

        if (gMapCardCounts[i] != 0) {
            if (card->backIndex != 4) {
                pal[j] = -1;
                k = j + 1;
                pal[k] = 0x7F;
            } else {
                pal[j] = gUnk_09618C58[j];
                k2 = j + 1;
                pal[k2] = gUnk_09618C58[k2];
            }
        }
    }

    LoadPalette(work->paletteBuffer, (void*)(BG_PLTT + 14 * PLTT_SIZE_4BPP), 32);
}

void LoadMapSelectGridPalette(u16 a, MapSelectWork* work) {
    u16 i;
    u16 j;
    u8* pal;
    MapcardWork** mp;
    s32 k;

    for (i = 0; i < 22; i++) {
        pal = work->paletteBuffer;
        pal[i] = gUnk_09619098[i + 32];
    }

    for (i = 22, j = 2; i < 26; i++, j++) {
        mp = &work->card;
        pal = work->paletteBuffer;

        switch ((*mp)->cardDef->backIndex) {
        case 1:
            pal[i] = gUnk_09619098[j + 0x60];
            break;
        case 2:
            pal[i] = gUnk_09619098[j + 0x40];
            break;
        case 3:
            pal[i] = gUnk_09619098[j + 0xA0];
            break;
        case 4:
            pal[i] = gUnk_09619098[j + 0x80];
            break;
        }
    }

    for (i = 26; i < 32; i++) {
        pal = work->paletteBuffer;
        pal[i] = gUnk_09618C58[i];
    }

    for (i = a, j = 2; i < a + 10; i++, j += 2) {
        pal = work->paletteBuffer;

        if (gMapCardCounts[i] != 0) {
            pal[j] = -1;
            k = j + 1;
            pal[k] = 0x7F;
        }
    }

    LoadPalette(work->paletteBuffer, (void*)(BG_PLTT + 12 * PLTT_SIZE_4BPP), 32);
}

s32 LoadMapSelectValueCounts(u16 a, MapSelectWork* work) {
    u16 i;
    u16 j;
    u8 count;
    u8* src;
    u8* base;

    for (i = a, j = 0; i < a + 10; i++, j++) {
        if (gMapCardCounts[i] != 0) {
            count = gMapCardCounts[i];

            if (count > 9) {
                count = 9;
                gMapCardCounts[i] = count;
            }

            src = &gUnk_09507F38[(count + 1) * 32];
            base = GetBgCharBase(1);
            base += gMapSelectCountTileIndices[i - a] * 32;
            RequestDma3Copy(src, base, 32);
            work->valueCounts[j] = count;
        } else {
            base = GetBgCharBase(1);
            base += gMapSelectCountTileIndices[i - a] * 32;
            RequestDma3Copy(gUnk_09507F58, base, 32);
            work->valueCounts[j] = 0;
        }
    }

    for (i = 0; i < 10; i++) {
        if (work->valueCounts[i] != 0) {
            return (s8)i;
        }
    }

    return -1;
}

s32 FindLastMapSelectValueInRow(MapSelectWork* work) {
    u8* p;
    s32 base;
    u8 i;

    i = 4;
    base = work->valueRow * 5;
    p = work->valueCounts;

    do {
        if (p[i + base] == 0) {
            i--;
        } else {
            return (s8)i;
        }
    } while (i != 0);

    return -1;
}

void HandleMapSelectValueCursor(MapSelectWork* work) {
    s8 c0;
    s8 y0;
    s32 z;

    c0 = work->valueColumn;
    y0 = work->valueRow;
    z = 0;

    switch (GetKeysRepeat() & DPAD_ANY) {
    case DPAD_RIGHT:
        do {
            if (work->valueColumn <= 3) {
                work->valueColumn++;
            } else {
                work->valueColumn = 0;
                work->valueRow ^= 1;
            }
        } while (work->valueCounts[work->valueColumn + work->valueRow * 5] == 0);

        work->steps2 = 4;
        break;
    case DPAD_LEFT:
        do {
            if (work->valueColumn > 0) {
                work->valueColumn--;
            } else {
                work->valueColumn = 4;
                work->valueRow ^= 1;
            }
        } while (work->valueCounts[work->valueColumn + work->valueRow * 5] == 0);

        work->steps2 = 4;
        break;
    case DPAD_UP:
        work->valueRow ^= 1;
        c0 = work->valueColumn;

        while (work->valueCounts[work->valueColumn + work->valueRow * 5] == 0) {
            if (work->valueColumn > 3) {
                z = 1;
                break;
            }

            work->valueColumn++;
            z = 0;
        }

        if (z == 1) {
            work->valueColumn = FindLastMapSelectValueInRow(work);

            if (work->valueColumn == -1) {
                work->valueRow ^= 1;
                work->valueColumn = c0;
            }
        }

        work->steps2 = 4;
        break;
    case DPAD_DOWN:
        work->valueRow ^= 1;
        c0 = work->valueColumn;

        while (work->valueCounts[work->valueColumn + work->valueRow * 5] == 0) {
            if (work->valueColumn > 3) {
                z = 1;
                break;
            }

            work->valueColumn++;
            z = 0;
        }

        if (z == 1) {
            work->valueColumn = FindLastMapSelectValueInRow(work);

            if (work->valueColumn == -1) {
                work->valueRow ^= 1;
                work->valueColumn = c0;
            }
        }

        work->steps2 = 4;
        break;
    }

    if (c0 != work->valueColumn || y0 != work->valueRow) {
        m4aSongNumStart(SONG_SYS_CLICKI04B);
    }

    ApproachValue(&work->x2, gMapSelectValueColumnX[work->valueColumn] << 8, work->steps2);
    ApproachValue(&work->y2, gMapSelectValueRowY[work->valueRow] << 8, work->steps2);
    ApproachValue(&work->x, gMapSelectValueColumnX[work->valueColumn] << 8, work->steps);
    ApproachValue(&work->y, (gMapSelectValueRowY[work->valueRow] + 34) << 8,
                  work->steps);

    if (work->steps != 0) {
        work->steps--;
    }

    if (work->steps2 != 0) {
        work->steps2--;
    }
}

u8 UpdateMapSelectTutorial(MapSelectWork* work, void* a) {
    MapcardWork* n;
    u8 v;

    SetObjMosaicSize(work->mosaicX, work->mosaicY);

    if (work->mosaicTimer == 2) {
        if (work->mosaicX != 0) {
            work->mosaicX--;
        }

        if (work->mosaicY != 0) {
            work->mosaicY--;
        }

        work->mosaicTimer = 0;
    }

    work->mosaicTimer++;

    if (!IsMessageWindowOpen()) {
        if (work->messageTimer == 8) {
            work->messageTimer = 0;

            if (work->tutorialMessage <= 98) {
                CreateSysmsgwinTask(&work->tasks, work->tutorialMessage);
                work->tutorialMessage++;
            } else {
                n = ListPoolFirst(&work->cards);
                SetBgMapBlocks(1, gMapSelectBgMapBlocks, 1, 2);

                while (n != NULL) {
                    n->flags |= MAPCARD_FLAG_RAISED;
                    n = ListPoolNext(&n->node);
                }

                if (work->kindCount <= 6) {
                    work->lastPage = 0;
                } else {
                    v = work->kindCount / 6;
                    work->lastPage = v;
                }

                work->y2 = 0x6400;
                work->y = 0x7A00;
                work->nameY = 0x9100;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectKindInput);
                work->scrollBarVisible = 1;
                work->tutorialMessage = 99;
                return 1;
            }
        } else {
            work->messageTimer++;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 UpdateMapSelectValueTutorial(MapSelectWork* work, void* a) {
    u8 r;

    r = IsMessageWindowOpen();

    if (!r) {
        if (work->messageTimer == 8) {
            work->messageTimer = 0;

            if (work->tutorialMessage <= 0x66) {
                CreateSysmsgwinTask(&work->tasks, work->tutorialMessage);
                work->tutorialMessage++;
            } else {
                gGameState.progression.tutorialFlags |= 8;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectValueInput);
            }
        } else {
            work->messageTimer++;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 UpdateMapSelectEventDoorTutorial(MapSelectWork* work, void* a) {
    MapcardWork* node;
    u32 pages;

    SetObjMosaicSize(work->mosaicX, work->mosaicY);

    if (work->mosaicTimer == 2) {
        if (work->mosaicX != 0) {
            work->mosaicX--;
        }

        if (work->mosaicY != 0) {
            work->mosaicY--;
        }

        work->mosaicTimer = 0;
    }

    work->mosaicTimer++;

    if (!IsMessageWindowOpen()) {
        if (work->messageTimer == 8) {
            work->messageTimer = 0;

            if (work->tutorialMessage <= 0x71) {
                CreateSysmsgwinTask(&work->tasks, work->tutorialMessage);
                work->tutorialMessage++;
            } else {
                node = ListPoolFirst(&work->cards);
                SetBgMapBlocks(1, gMapSelectBgMapBlocks, 1, 2);

                while (node != NULL) {
                    node->flags |= MAPCARD_FLAG_RAISED;
                    node = ListPoolNext(&node->node);
                }

                if (work->kindCount <= 6) {
                    work->lastPage = 0;
                } else {
                    pages = work->kindCount / 6;
                    work->lastPage = pages;
                }

                work->y2 = 0x6400;
                work->y = 0x7A00;
                work->nameY = 0x9100;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectKindInput);
                work->scrollBarVisible = 1;
                return 1;
            }
        } else {
            work->messageTimer++;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void RemoveMapSelectCard(MapSelectWork* work) {
    MapcardWork* n;
    s32 v;
    s32 i;

    v = work->openedCardX >> 8;

    for (i = 0; i < 6; i++) {
        if (v == gMapcardSlotX[i]) {
            break;
        }
    }

    n = ListPoolRemove(&work->card->node, &work->cards);
    work->card->flags |= MAPCARD_FLAG_REMOVED;
    work->card = n;

    while (n != NULL) {
        n->args.index--;

        if (i <= 5) {
            n->x = gMapcardSlotX[i] << 8;
            i++;
        }

        n = ListPoolNext(&n->node);
    }

    for (n = ListPoolFirst(&work->cards); n != NULL; n = ListPoolNext(&n->node)) {
        n->flags |= MAPCARD_FLAG_RAISED;
    }

    if (work->card == NULL) {
        work->card = ListPoolLast(&work->cards);

        if (work->card == NULL) {
            work->cursorTargetX = 0x1600;
        } else {
            work->cursorTargetX = work->card->x;
        }
    } else {
        work->cursorTargetX = work->card->x;
    }
}

void Mapcard_0(MapcardWork* work, MapcardArgs* a) {
    work->tiles = NULL;
    work->unk_04 = NULL;
    work->tiles2 = NULL;
    work->palette = NULL;
    work->args = *a;
    work->x = work->args.index <= 5 ? gMapcardSlotX[work->args.index] << 8 : -0x6400;
    work->y = 0x10500;
    work->priority = 50;
    work->deceleration = 0;
    work->speed = 0;
    work->distance = 0;
    work->flags = 0;
    work->angle = 0;
    work->steps = 16;
    work->holdTimer = 0;
    work->scale = 0x100;
    work->unk_71 = 0;
    work->unk_72 = 0;
    work->value = gMapCardDefs[work->args.baseCardId].value;
    work->cardDef = &gMapCardDefs[work->args.baseCardId];
    work->cardBack = &gMapCardBackDefs[work->cardDef->backIndex];
    LinkMapcardNode(work);
    UpdateMapcardRise(work);
    UpdateMapcardGfx(work);
}

u8 Mapcard_1(MapcardWork* work, void* a) {
    if (work->flags & 0xC) {
        work->steps = 12;
        func_08094DEC(work);
        SetTaskUpdate(a, (TaskUpdateFunc)func_080948F0);
    }

    if (work->flags & MAPCARD_FLAG_OPENED) {
        work->angle = 0;
        work->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapcardMoveToFront);
    }

    if (work->flags & MAPCARD_FLAG_CHOSEN) {
        work->angle = 0;
        work->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapcardToCenter);
    }

    if (work->flags & MAPCARD_FLAG_REMOVED) {
        return 0;
    }

    work->angle = 0;
    UpdateMapcardRise(work);
    UpdateMapcardGfx(work);
    return 1;
}

u8 UpdateMapcardMoveToFront(MapcardWork* work, void* a) {
    ApproachValue(&work->x, gMapcardSlotX[0] << 8, work->steps);
    work->steps--;

    if (!(work->flags & MAPCARD_FLAG_OPENED)) {
        work->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapcardMoveBack);
    }

    if (work->flags & MAPCARD_FLAG_CURSOR) {
        work->angle += 8;
    } else {
        work->angle = 0;
    }

    if (work->flags & MAPCARD_FLAG_CHOSEN) {
        work->angle = 0;
        work->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapcardToCenter);
    }

    if (work->flags & MAPCARD_FLAG_REMOVED) {
        return 0;
    }

    UpdateMapcardRise(work);
    UpdateMapcardGfx(work);
    return 1;
}

u8 UpdateMapcardMoveBack(MapcardWork* work, void* a) {
    ApproachValue(&work->x, gMapcardSlotX[work->args.index % 6] << 8, work->steps);
    work->steps--;

    if (work->steps == 0) {
        SetTaskUpdate(a, (TaskUpdateFunc)Mapcard_1);
    }

    if (work->flags & MAPCARD_FLAG_CURSOR) {
        work->angle += 8;
    } else {
        work->angle = 0;
    }

    UpdateMapcardRise(work);
    UpdateMapcardGfx(work);
    return 1;
}

s32 func_080948F0(MapcardWork* work, void* a) {
    u8 t;

    t = func_08094E4C(work);
    UpdateMapcardRise(work);
    UpdateMapcardGfx(work);

    if (!t) {
        work->flags &= 0xFFF3;
        SetTaskUpdate(a, (TaskUpdateFunc)Mapcard_1);
    }

    return 1;
}

u8 UpdateMapcardToCenter(MapcardWork* work, void* a) {
    work->angle = 0;
    ApproachValue(&work->x, 0x7800, work->steps);
    ApproachValue(&work->y, 0x3800, work->steps);

    if (work->steps != 0) {
        work->steps--;
    } else {
        work->holdTimer++;

        if (work->holdTimer > 15) {
            AimMapcardAtDoor(work);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapcardFlyToDoor);
        }
    }

    UpdateMapcardGfx(work);
    return 1;
}

void AimMapcardAtDoor(MapcardWork* work) {
    s32 v[2];
    s32 dx;
    s32 dy;
    FldObj* p = GetMapRoomDoor();

    dx = (p->fieldPosition.x >> 8) - (gFieldState->x >> 8);
    dy = (p->fieldPosition.y >> 8) + (p->fieldPosition.z >> 8) - (gFieldState->y >> 8) - 24;
    v[0] = dx * 256 - work->x;
    v[1] = dy * 256 - work->y;
    work->distance = NormalizeVector2D8(&v[0], &v[1]);
    work->dirX = -v[0];
    work->dirY = -v[1];
    work->speed = 0x300;
    work->deceleration = 25;
    work->angle = 0;
    work->scale = 0x100;
}

u8 UpdateMapcardFlyToDoor(MapcardWork* work, void* a) {
    FldObj* p;
    s32 dx;
    s32 dy;
    s32 d;
    s32 x;
    s32 y;
    u16 t;
    u16 f;

    p = GetMapRoomDoor();
    dx = (p->fieldPosition.x >> 8) - (gFieldState->x >> 8);
    dy = (p->fieldPosition.y >> 8) + (p->fieldPosition.z >> 8) - (gFieldState->y >> 8) - 24;

    if (work->speed < 0) {
        x = (dx << 8) - work->x;
        y = (dy << 8) - work->y;
        NormalizeVector2D8(&x, &y);
        work->dirX = -x;
        work->dirY = -y;
    }

    {
        u8* q = &work->angle;
        u16* scale;

        *q += 24;
        scale = (u16*)(q - (offsetof(MapcardWork, angle) - offsetof(MapcardWork, scale)));
        t = *scale;
        *scale = (s16)t > 25 ? t - 12 : 25;
    }

    work->x += (work->dirX * work->speed) >> 8;
    work->y += (work->dirY * work->speed) >> 8;
    d = VectorLength2D((dx << 8) - work->x, (dy << 8) - work->y);
    work->distance = d;
    work->speed -= work->deceleration;
    work->deceleration += 2;

    if (work->args.parent->isEventDoor != 1) {
        if (d <= 0x7FF) {
            SetMapCardDelivered();
            f = work->flags | MAPCARD_FLAG_DELIVERED;
            work->flags = f;
            SetSelectedMapCard(&gMapCardDefs[work->args.baseCardId + work->value].kind);
        }
    } else {
        if (d <= 0x7FF && work->args.parent->remainingKeys == 0) {
            SetMapCardDelivered();
            f = work->flags | MAPCARD_FLAG_DELIVERED;
            work->flags = f;
            SetSelectedMapCard(&gMapCardDefs[work->args.baseCardId + work->value].kind);
        }
    }

    return 1;
}

void Mapcard_2(MapcardWork* work) {
    ObjAffine* aff;
    u16 y;
    void* sprite;

    if (!IsMessageWindowOpen()) {
        y = (work->y >> 8) + (gSineTable[work->angle] >> 8);

        if (work->flags & MAPCARD_FLAG_GFX_LOADED) {
            if (work->x > 0) {
                if (work->x <= 0xEFFF) {
                    goto draw;
                }
            }

            // fakematch
            do {
                return;
            } while (0);

        draw:
            aff = NULL;

            if (work->flags & MAPCARD_FLAG_CHOSEN) {
                aff = AllocObjAffine(work->angle, (s16)work->scale, (s16)work->scale, 1);
            }

            if (gMapCardDefs[work->args.baseCardId].backIndex == 4) {
                DrawSprite(work->x >> 8, y, gMapCardUiResources.gfx, gMapCardUiResources.tiles, work->palette2, aff, 0,
                           work->priority - 2);
            }

            sprite = work->cardBack->sprites[0];
            DrawSprite(work->x >> 8, y, sprite, work->tiles3, work->palette2, aff, 0, work->priority);
            sprite = work->cardDef->sprites[0];
            DrawSprite(work->x >> 8, y, sprite, work->tiles2, work->palette, aff, 0, work->priority + 1);
        }
    }
}

void Mapcard_3(MapcardWork* work) {
    if (work->flags & MAPCARD_FLAG_GFX_LOADED) {
        ReleaseObjTiles(work->tiles2);
        ReleaseObjPalette(work->palette);
        ReleaseObjTiles(work->tiles3);
        ReleaseObjPalette(work->palette2);
    }
}

u8 IsMapcardOnScreen(MapcardWork* work) {
    if (work->x >= -4096) {
        if (work->x <= 0x10000) {
            if (work->y >= -5120) {
                if (work->y <= 0xC000) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void UpdateMapcardGfx(MapcardWork* work) {
    MapCardDef* a;
    MapCardBackDef* b;
    u16 t;

    if (IsMapcardOnScreen(work)) {
        if (!(work->flags & MAPCARD_FLAG_GFX_LOADED)) {
            a = work->cardDef;
            b = work->cardBack;
            work->tiles2 = LoadObjTiles(a->tiles, a->tilesSize);
            work->palette = LoadObjPalette(a->palette, 32);
            work->tiles3 = LoadObjTiles(b->tiles, b->tilesSize);
            work->palette2 = LoadObjPalette(b->palette, 32);
            work->tiles = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
            FadeSetPaletteExcluded(work->palette->index + 16, 1);
            FadeSetPaletteExcluded(work->palette2->index + 16, 1);
            t = work->flags | MAPCARD_FLAG_GFX_LOADED;
            work->flags = t;
        }
    } else if (work->flags & MAPCARD_FLAG_GFX_LOADED) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjTiles(work->tiles2);
        ReleaseObjPalette(work->palette);
        ReleaseObjTiles(work->tiles3);
        ReleaseObjPalette(work->palette2);
        work->flags &= ~MAPCARD_FLAG_GFX_LOADED;
    }
}

void UpdateMapcardRise(MapcardWork* work) {
    if (work->flags & MAPCARD_FLAG_RAISED) {
        ApproachValue(&work->y, 0x7900, work->steps);
    } else {
        ApproachValue(&work->y, 0x10500, work->steps);
    }

    if (work->steps != 0) {
        work->steps--;
    }
}

void func_08094DEC(MapcardWork* work) {
    if ((work->flags & 4) && work->speed - work->deceleration > 0x8000) {
        work->deceleration += 0x10000;
    }

    if ((work->flags & 8) && work->speed < work->deceleration) {
        work->deceleration -= 0x10000;
    }

    ApproachValue(&work->deceleration, work->speed, work->steps);
    work->steps--;
}

u8 func_08094E4C(MapcardWork* work) {
    ApproachValue(&work->deceleration, work->speed, work->steps);

    if (work->steps != 0) {
        work->steps--;
        return 1;
    }

    return 0;
}

MapcardWork* CreateMapCard(MapcardArgs* args, TaskPool* pool) {
    return TaskCreate(pool, &gTaskDescMapcard, args)->work;
}

void LinkMapcardNode(MapcardWork* work) {
    ListNodeInit(&work->node, work->args.pool, work);
    ListPoolAppend(&work->node, work->args.pool);
}

void Reload_Gage_0(CardDisplayWork* work, CardDisplayArgs* a) {
    ReloadGauge* d;
    ReloadChildArgs args;
    u16 v;
    s8 n;
    s8 i;

    work->tiles = NULL;
    work->tiles2 = NULL;
    work->tiles4 = NULL;
    work->tiles3 = NULL;
    work->tiles5 = NULL;
    work->palette = NULL;
    work->command = 0;
    work->args = *a;
    work->flags = 0;
    work->timer = 16;
    work->ringRadius = 0;
    work->stockIndex = 0;
    work->priority = 4;
    work->ringRadiusTarget = 0x2400;
    work->ringAngleTarget = 0;
    work->ringAngle = 0;
    work->reloadGauge = EwramAlloc(sizeof(ReloadGauge));
    work->phase = 0;
    work->swingSteps = 0;
    d = work->reloadGauge;
    v = a->index;

    if ((s16)v >= 0) {
        d->reloadCounter = v;
    } else {
        d->reloadCounter = -1;
    }

    if (d->reloadCounter > 17) {
        d->reloadCounter = 18;
    }

    d->chargeTick = 0;
    work->children = EwramAlloc(sizeof(ListPool));

    switch (work->args.variant) {
    case 1:
        work->ringCenterX = gSoraCardLayout[0][0];
        work->ringCenterY = gSoraCardLayout[0][1];
        work->x = gSoraCardLayout[4][0];
        work->y = gSoraCardLayout[4][1];
        work->swingAngle = work->swingAngleTarget = 0x2000;
        work->flags |= 0x8000000;
        break;
    case 2:
        work->ringCenterX = gRikuCardLayout[0][0];
        work->ringCenterY = gRikuCardLayout[0][1];
        work->x = gRikuCardLayout[4][0];
        work->y = gRikuCardLayout[4][1];
        work->swingAngle = work->swingAngleTarget = -0x2000;
        break;
    }

    work->scaleX = 0x100;
    work->scaleY = 0;
    ListPoolInit(work->children);
    ListNodeInit(&work->node, work->args.pool, work);
    ListPoolAppend(&work->node, work->args.pool);
    work->tiles2 = LoadObjTiles(gReloadCardTiles[work->args.listIndex], 0x280);
    work->tiles3 = AllocObjTiles(0x200, NULL);
    SetObjTileSource(work->tiles3, gReloadCardTiles[1]);
    work->tiles4 = AllocObjTiles(0x80, NULL);
    SetObjTileSource(work->tiles4, gReloadCardTiles[1]);
    InitReloadGageAnims(work->reloadGauge, work, work->args.listIndex);
    work->tiles = LoadObjTiles(gUnk_0905F03C, 0x80);
    work->palette = LoadObjPalette(gBStatesPalette, 32);
    work->tiles5 = AllocObjTiles(0x100, NULL);
    SetObjTileSource(work->tiles5, gReloadCounterTiles[work->args.listIndex]);
    InitReloadGageCounterAnim(work->reloadGauge, work->tiles5, work->args.listIndex, d->reloadCounter);
    work->flags |= (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_OPEN | CARD_DISP_FLAG_RELOAD_GAUGE);

    if (d->reloadCounter >= 0) {
        TaskPoolInit(&work->tasks, d->reloadCounter + 1);
        n = d->reloadCounter;

        if (d->reloadCounter > 3) {
            n = 3;
        }

        for (i = 0; i < n; i++) {
            args.pool = work->children;
            args.index = i;
            args.parentX = &work->x;
            args.parentY = &work->y;
            args.flags = 0;
            args.listIndex = work->args.listIndex;
            args.side = work->args.variant;
            TaskCreate(&work->tasks, &gTaskDescReloadChildren, &args);
        }
    } else {
        TaskPoolInit(&work->tasks, 1);
    }
}

u8 Reload_Gage_1(CardDisplayWork* work, void* a) {
    ReloadChildArgs args;
    ReloadGauge* p;
    ReloadChildWork* node;
    ReloadChildWork* child;
    s32 flags;
    u8 v;

    p = work->reloadGauge;
    v = 0;

    switch (work->args.variant) {
    case 1:
        if (gCardBattleState->soraListIndex == work->args.listIndex) {
            v = gCardBattleState->soraReloadCharging;
            gCardBattleState->soraReloadCharging = 0;
        }

        break;
    case 2:
        if (gCardBattleState->rikuListIndex == work->args.listIndex) {
            v = gCardBattleState->rikuReloadCharging;
            gCardBattleState->rikuReloadCharging = 0;
        }

        break;
    }

    if ((work->flags & (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) == (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) {
        if (v == 1) {
            if ((s8)p->chargeTick == 2) {
                switch (work->args.variant) {
                case 1:
                    if ((gBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) == 0) {
                        m4aSongNumStart(SONG_SYS_CHAGE);
                        gBtlWork->flags |= BTL_FLAG_RELOAD_CHARGING;
                    }

                    break;
                case 2:
                    if ((gRikuBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) == 0) {
                        m4aSongNumStart(SONG_SYS_CHAGE);
                        gRikuBtlWork->flags |= BTL_FLAG_RELOAD_CHARGING;
                    }

                    break;
                }

                node = ListPoolFirst(work->children);

                while (node != NULL) {
                    node->args.flags &= ~RELOAD_CHILD_FLAG_IDLE;
                    node = ListPoolNext(&node->node);
                }

                if (work->stockIndex == 0) {
                    work->scaleY += 25;

                    if (work->scaleY > 0x100) {
                        work->scaleY = 0x100;
                        work->stockIndex = 1;
                    }
                } else {
                    work->priority += 3;
                    AdvanceReloadGageAnim(work->reloadGauge, work);

                    if (work->priority == 10) {
                        work->priority = 4;
                        work->scaleY = 0;
                        work->stockIndex = 0;
                        child = ListPoolFirst(work->children);

                        while (child != NULL) {
                            child->args.flags |= RELOAD_CHILD_FLAG_SHIFTED;
                            child->args.index--;
                            child = ListPoolNext(&child->node);
                        }

                        p->reloadCounter--;

                        if (p->reloadCounter > 2) {
                            args.pool = work->children;
                            args.index = 3;
                            args.parentX = &work->x;
                            args.parentY = &work->y;
                            args.flags = 0;
                            args.listIndex = work->args.listIndex;
                            args.side = work->args.variant;
                            child = TaskCreate(&work->tasks, &gTaskDescReloadChildren, &args)->work;
                            flags = child->args.flags | RELOAD_CHILD_FLAG_SHIFTED;
                            flags &= 0xFFFD;
                            child->args.flags = flags;
                            child->args.index--;
                        }

                        work->timer = 8;
                        work->phase = 1;
                        ResetReloadGageAnim(work->reloadGauge);
                        m4aSongNumStart(SONG_SYS_CHAGEF1);
                    }
                }

                switch (work->args.variant) {
                case 1:
                    if (gBtlWork->hcEffect == 9) {
                        p->chargeTick = 1;
                    } else if (gBtlWork->hcEffect == 43) {
                        p->chargeTick = 254;
                    } else {
                        p->chargeTick = 0;
                    }

                    break;
                case 2:
                    if (gRikuBtlWork->hcEffect == 9) {
                        p->chargeTick = 1;
                    } else if (gRikuBtlWork->hcEffect == 43) {
                        p->chargeTick = 254;
                    } else {
                        p->chargeTick = 0;
                    }

                    break;
                }
            }

            UpdateReloadGageAnims(work->reloadGauge, work);
            p->chargeTick++;
        } else {
            SetReloadGageIdleFrames(work->reloadGauge, work);
            p->chargeTick = 0;
            work->flags |= 0x8000000;
            m4aSongNumStop(SONG_SYS_CHAGE);

            switch (work->args.variant) {
            case 1:
                gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
                break;
            case 2:
                gRikuBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
                break;
            }

            node = ListPoolFirst(work->children);

            while (node != NULL) {
                node->args.flags |= RELOAD_CHILD_FLAG_IDLE;
                node = ListPoolNext(&node->node);
            }
        }
    }

    if (p->reloadCounter < 0) {
        if ((work->flags & CARD_DISP_FLAG_RELOAD_DONE) == 0) {
            work->flags |= CARD_DISP_FLAG_RELOAD_DONE;
            m4aSongNumStart(SONG_SYS_CHAGEF2);
        }

        if (FadeGetAmount() == 0) {
            FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
        }

        return 0;
    }

    UpdateReloadGageSlide(work->reloadGauge, work);

    if (work->phase == 1 && (s16)work->timer == 1) {
        SetReloadGageCounterAnim(work->reloadGauge, p->reloadCounter);
    }

    UpdateReloadGageRingPosition(work);

    if (work->flags & CARD_DISP_FLAG_REMOVE) {
        return 0;
    }

    StepReloadGageSine(work->reloadGauge);
    work->bobAngle += 4;

    if ((work->flags & CARD_DISP_FLAG_OPEN) == 0) {
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateReloadGageIdle);
        m4aSongNumStop(SONG_SYS_CHAGE);

        switch (work->args.variant) {
        case 1:
            gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
            break;
        case 2:
            gRikuBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
            break;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 UpdateReloadGageIdle(CardDisplayWork* work, void* a) {
    if (work->command == 7) {
        return 0;
    }

    work->ringRadius += -work->ringRadius >> 1;
    work->x += (gSoraCardLayout[4][0] - work->x) >> 1;
    work->y += (gSoraCardLayout[4][1] - work->y) >> 1;

    if (work->flags & CARD_DISP_FLAG_OPEN) {
        SetTaskUpdate(a, (TaskUpdateFunc)Reload_Gage_1);
    }

    return 1;
}

void Reload_Gage_2(CardDisplayWork* work) {
    ReloadGauge* q;
    ObjAffine* affine;
    void* gfx;
    s32 t;

    q = work->reloadGauge;
    gfx = gCardBacks[work->args.listIndex].gfx2;
    DrawSprite((work->x >> 8) + (q->offsetX >> 8),
               (work->y >> 8) + (gSineTable[work->bobAngle] >> 8),
               gfx, work->tiles2,
               gCardBattleState->palette, NULL, SPRITE_PRIORITY(1), 50);

    if (work->scaleY > 0) {
        affine = AllocObjAffine(0, 0x100, work->scaleY, 0);
        DrawSprite((work->x >> 8) + (q->offsetX >> 8),
                   (work->y >> 8) + (t = (gSineTable[work->bobAngle] >> 8) + 17),
                   q->gfx, work->tiles3, gCardBattleState->palette, affine,
                   SPRITE_PRIORITY(1), 49);

        if (work->stockIndex == 1) {
            DrawSprite((work->x >> 8) + (q->offsetX >> 8),
                       (work->y >> 8) + (gSineTable[work->bobAngle] >> 8),
                       q->gfx2, work->tiles4, gCardBattleState->palette, NULL,
                       SPRITE_PRIORITY(1), 49);
        }
    }

    if (q->gfx3 != NULL) {
        DrawSprite((work->x >> 8) + (q->offsetX >> 8),
                   (work->y >> 8) + (gSineTable[work->bobAngle] >> 8),
                   q->gfx3, work->tiles5,
                   gCardBattleState->palette, NULL, SPRITE_PRIORITY(1), 48);
    }

    TaskPoolDraw(&work->tasks);
}

void Reload_Gage_3(CardDisplayWork* work) {
    TaskPoolDestroy(&work->tasks);
    ReleaseObjPalette(work->palette);
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles3);
    ReleaseObjTiles(work->tiles4);
    ReleaseObjTiles(work->tiles5);
    EwramFree(work->children);
    EwramFree(work->reloadGauge);

    switch (work->args.variant) {
    case 1:
        gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;

        switch (gBtlWork->hcEffect) {
        case 9:
        case 10:
        case 25:
        case 30:
        case 40:
        case 43:
        case 54:
            gBtlWork->hcEffectCount--;
            break;
        }

        break;
    case 2:
        gRikuBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;

        switch (gRikuBtlWork->hcEffect) {
        case 9:
        case 10:
        case 25:
        case 30:
        case 40:
        case 43:
        case 54:
            gRikuBtlWork->hcEffectCount--;
            break;
        }

        break;
    }

    ListPoolRemove(&work->node, work->args.pool);
}

void UpdateReloadGageRingPosition(CardDisplayWork* work) {
    ApproachValue(&work->swingAngle, work->swingAngleTarget, work->swingSteps);

    if (work->swingSteps != 0) {
        work->swingSteps--;
    }

    work->ringRadius += (work->ringRadiusTarget - work->ringRadius) >> 1;

    if ((s16)work->timer > 0) {
        work->timer--;
        work->flags &= ~CARD_DISP_FLAG_SETTLED;
    } else {
        work->timer = 0;
        work->flags |= CARD_DISP_FLAG_SETTLED;
    }

    switch (work->args.variant) {
    case 1:
        work->ringCenterX = SIN(work->swingAngle >> 8) * 80 + gSoraCardLayout[0][0];
        work->ringCenterY = -COS(work->swingAngle >> 8) * 80 + gSoraCardLayout[0][1];
        work->x = gSineTable[0x20] * (work->ringRadius >> 8) + work->ringCenterX;
        work->y = -gSineTable[0x60] * (work->ringRadius >> 8) + work->ringCenterY;
        break;
    case 2:
        work->ringCenterX = SIN(work->swingAngle >> 8) * 80 + gRikuCardLayout[0][0];
        work->ringCenterY = -COS(work->swingAngle >> 8) * 80 + gRikuCardLayout[0][1];
        work->x = gSineTable[0xE0] * (work->ringRadius >> 8) + work->ringCenterX;
        work->y = -gSineTable[0x120] * (work->ringRadius >> 8) + work->ringCenterY;
        break;
    }
}

void StepReloadGageSine(ReloadGauge* p) {
    p->sine = gSineTable[(u8)p->angle] >> 8;
    p->angle += 16;
}

void InitReloadGageCounterAnim(ReloadGauge* p, void* a, u8 b, s32 count) {
    s8 c = count;

    AnimInit(&p->anim, gReloadCounterAnims[b], gReloadCounterFrames[b]);

    if (c >= 0) {
        AnimStart(&p->anim, c, 0);
    } else {
        AnimStart(&p->anim, 0, 0);
    }

    p->gfx3 = AnimGetGfx(&p->anim);
}

void SetReloadGageCounterAnim(ReloadGauge* p, s32 count) {
    void* gfx;

    if ((u16)count <= 18) {
        AnimStart(&p->anim, count, 0);
        gfx = AnimGetGfx(&p->anim);
    } else {
        gfx = NULL;
    }

    p->gfx3 = gfx;
}

s32 UpdateReloadGageSlide(ReloadGauge* p, CardDisplayWork* work) {
    if ((s16)work->timer > 0 && work->phase == 1) {
        switch (work->args.variant) {
        case 1:
            ApproachValue(&p->offsetX, -0x3000, work->timer);
            break;
        case 2:
            ApproachValue(&p->offsetX, 0x12000, work->timer);
            break;
        }
    } else {
        p->offsetX = 0;
    }
}

void InitReloadGageAnims(ReloadGauge* p, CardDisplayWork* work, u8 idx) {
    p->gaugeAnim = 2;
    AnimInit(&p->anim2, gReloadGaugeAnims[idx], gReloadGaugeFrames[idx]);
    AnimStart(&p->anim2, 1, ANIM_FLAG_LOOP);
    p->gfx = gReloadGaugeFrames[idx][3];
    AnimInit(&p->anim3, gReloadGaugeAnims[idx], gReloadGaugeFrames[idx]);
    AnimStart(&p->anim3, 2, ANIM_FLAG_LOOP);
    p->gfx2 = gReloadGaugeFrames[idx][6];
}

void UpdateReloadGageAnims(ReloadGauge* p, CardDisplayWork* work) {
    p->gfx = AnimUpdate(&p->anim2);
    p->gfx2 = AnimUpdate(&p->anim3);
}

void SetReloadGageIdleFrames(ReloadGauge* p, CardDisplayWork* work) {
    p->gfx = gReloadGaugeFrames[work->args.listIndex][3];
    p->gfx2 = gReloadGaugeFrames[work->args.listIndex][work->priority + 2];
}

void AdvanceReloadGageAnim(ReloadGauge* p, CardDisplayWork* work) {
    if (p->gaugeAnim <= 3) {
        p->gaugeAnim++;
    }

    AnimStart(&p->anim3, p->gaugeAnim, ANIM_FLAG_LOOP | ANIM_FLAG_KEEP_FRAME);
}

void ResetReloadGageAnim(ReloadGauge* p) {
    p->gaugeAnim = 2;
}

void* CreateReloadGageTask(CardBattleWork* work, u16 b, void* pool, u8 mode) {
    CardDisplayArgs args;

    args.pool = &work->cardDisplays[work->listIndex];
    args.slot = NULL;

    switch (mode) {
    case 1:
        if (gBtlWork->hcEffect == 10) {
            args.index = b - 2;
        } else {
            args.index = b;
        }

        break;
    case 2:
        if (gRikuBtlWork->hcEffect == 10) {
            args.index = b - 2;
        } else {
            args.index = b;
        }

        break;
    }

    args.variant = mode;
    args.listIndex = work->listIndex;
    return TaskCreate(pool, &gTaskDescReloadGage, &args)->work;
}

Mode gModeWORLDSELECT = {
    "WORLDSELECT",
    (ModeInitFunc)WORLDSELECT_0,
    WORLDSELECT_1,
    WORLDSELECT_2,
};

#ifdef VERSION_EU
const u16 gMapCardUiExtraTileSizes[5] = {
    864, 864, 864, 864, 864,
};
#endif

#ifdef VERSION_EU
void* gMapCardUiExtraTilesByLanguage[5] = {
    gUnk_093F6734, gUnkEu_094C9860, gUnk_093F6734, gUnkEu_094C9860, gUnkEu_094C9C20,
};

void** gMapCardUiSpritesByLanguage[5] = {
    gUnk_09EF11F8, gUnkEu_09F7C454, gUnk_09EF11F8, gUnkEu_09F7C454, gUnkEu_09F7C47C,
};
#endif

const void* gMapSelectBgMapBlocks[2] = {
    gUnk_08125E24, gMapSelectMap,
};

s16 gMapSelectValueColumnX[5] = {
    59, 99, 139, 179, 219,
};

s16 gMapSelectValueRowY[2] = {
    88, 112,
};

#ifdef VERSION_EU
void** gMapSelectTitleSpritesByLanguage[5] = {
    gUnk_09EF1228, gUnkEu_09F7C414, gUnkEu_09F7C42C, gUnkEu_09F7C424, gUnkEu_09F7C41C,
};
#endif

TaskDesc gTaskDescMapSelect = {
    "MapSelect",
    (TaskInitFunc)MapSelect_0,
    (TaskUpdateFunc)MapSelect_1,
    (TaskDrawFunc)MapSelect_2,
    (TaskDestroyFunc)MapSelect_3,
    sizeof(MapSelectWork),
};

u16 gMapSelectCountTileIndices[10] = {
    72, 77, 82, 87, 92, 168, 173, 178, 183, 188,
};

MapCardBackDef gMapCardBackDefs[5] = {
    { gUnk_093F61B2, gUnk_09618D78, gUnk_09EF11E8, gUnk_0905E3BA, gUnk_09EE97F4, 640, 32, 640 },
    { gUnk_093F5C7A, gUnk_09618D78, gUnk_09EF11D8, gUnk_0905C862, gUnk_09EE9764, 640, 32, 640 },
    { gUnk_093F5F16, gUnk_09618D78, gUnk_09EF11E0, gUnk_0905D64E, gUnk_09EE97AC, 640, 32, 640 },
    { gUnk_093F61B2, gUnk_09618D78, gUnk_09EF11E8, gUnk_0905AC8A, gUnk_09EE96D4, 640, 32, 640 },
    { gUnk_093F644E, gUnk_09618D78, gUnk_09EF11F0, gUnk_0905E3BA, gUnk_09EE97F4, 640, 32, 640 },
};

MapCardDef gMapCardDefs[260] = {
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 1, 0, 2 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 1, 1, 2 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 1, 2, 2 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 1, 3, 2 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 1, 4, 2 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 1, 5, 2 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 1, 6, 2 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 1, 7, 2 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 1, 8, 2 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 1, 9, 2 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 0, 2 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 1, 2 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 2, 2 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 3, 2 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 4, 2 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 5, 2 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 6, 2 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 7, 2 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 8, 2 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 9, 2 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 6, 0, 2 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 6, 1, 2 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 6, 2, 2 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 6, 3, 2 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 6, 4, 2 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 6, 5, 2 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 6, 6, 2 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 6, 7, 2 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 6, 8, 2 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 6, 9, 2 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 7, 0, 2 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 7, 1, 2 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 7, 2, 2 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 7, 3, 2 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 7, 4, 2 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 7, 5, 2 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 7, 6, 2 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 7, 7, 2 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 7, 8, 2 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 7, 9, 2 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 4, 0, 2 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 4, 1, 2 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 4, 2, 2 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 4, 3, 2 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 4, 4, 2 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 4, 5, 2 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 4, 6, 2 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 4, 7, 2 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 4, 8, 2 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 4, 9, 2 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 3, 0, 2 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 3, 1, 2 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 3, 2, 2 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 3, 3, 2 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 3, 4, 2 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 3, 5, 2 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 3, 6, 2 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 3, 7, 2 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 3, 8, 2 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 3, 9, 2 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 19, 0, 2 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 19, 1, 2 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 19, 2, 2 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 19, 3, 2 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 19, 4, 2 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 19, 5, 2 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 19, 6, 2 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 19, 7, 2 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 19, 8, 2 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 19, 9, 2 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 20, 0, 2 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 20, 1, 2 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 20, 2, 2 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 20, 3, 2 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 20, 4, 2 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 20, 5, 2 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 20, 6, 2 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 20, 7, 2 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 20, 8, 2 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 20, 9, 2 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 21, 0, 2 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 21, 1, 2 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 21, 2, 2 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 21, 3, 2 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 21, 4, 2 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 21, 5, 2 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 21, 6, 2 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 21, 7, 2 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 21, 8, 2 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 21, 9, 2 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 12, 0, 1 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 12, 1, 1 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 12, 2, 1 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 12, 3, 1 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 12, 4, 1 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 12, 5, 1 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 12, 6, 1 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 12, 7, 1 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 12, 8, 1 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 12, 9, 1 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 11, 0, 1 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 11, 1, 1 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 11, 2, 1 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 11, 3, 1 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 11, 4, 1 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 11, 5, 1 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 11, 6, 1 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 11, 7, 1 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 11, 8, 1 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 11, 9, 1 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 13, 0, 1 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 13, 1, 1 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 13, 2, 1 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 13, 3, 1 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 13, 4, 1 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 13, 5, 1 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 13, 6, 1 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 13, 7, 1 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 13, 8, 1 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 13, 9, 1 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 14, 0, 1 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 14, 1, 1 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 14, 2, 1 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 14, 3, 1 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 14, 4, 1 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 14, 5, 1 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 14, 6, 1 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 14, 7, 1 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 14, 8, 1 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 14, 9, 1 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 18, 0, 1 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 18, 1, 1 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 18, 2, 1 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 18, 3, 1 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 18, 4, 1 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 18, 5, 1 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 18, 6, 1 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 18, 7, 1 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 18, 8, 1 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 18, 9, 1 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 16, 0, 1 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 16, 1, 1 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 16, 2, 1 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 16, 3, 1 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 16, 4, 1 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 16, 5, 1 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 16, 6, 1 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 16, 7, 1 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 16, 8, 1 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 16, 9, 1 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 17, 0, 1 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 17, 1, 1 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 17, 2, 1 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 17, 3, 1 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 17, 4, 1 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 17, 5, 1 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 17, 6, 1 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 17, 7, 1 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 17, 8, 1 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 17, 9, 1 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 8, 0, 3 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 8, 1, 3 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 8, 2, 3 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 8, 3, 3 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 8, 4, 3 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 8, 5, 3 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 8, 6, 3 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 8, 7, 3 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 8, 8, 3 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 8, 9, 3 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 2, 0, 3 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 2, 1, 3 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 2, 2, 3 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 2, 3, 3 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 2, 4, 3 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 2, 5, 3 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 2, 6, 3 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 2, 7, 3 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 2, 8, 3 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 2, 9, 3 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 9, 0, 3 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 9, 1, 3 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 9, 2, 3 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 9, 3, 3 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 9, 4, 3 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 9, 5, 3 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 9, 6, 3 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 9, 7, 3 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 9, 8, 3 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 9, 9, 3 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 5, 0, 3 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 5, 1, 3 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 5, 2, 3 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 5, 3, 3 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 5, 4, 3 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 5, 5, 3 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 5, 6, 3 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 5, 7, 3 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 5, 8, 3 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 5, 9, 3 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 15, 0, 3 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 15, 1, 3 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 15, 2, 3 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 15, 3, 3 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 15, 4, 3 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 15, 5, 3 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 15, 6, 3 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 15, 7, 3 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 15, 8, 3 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 15, 9, 3 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 10, 0, 3 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 10, 1, 3 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 10, 2, 3 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 10, 3, 3 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 10, 4, 3 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 10, 5, 3 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 10, 6, 3 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 10, 7, 3 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 10, 8, 3 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 10, 9, 3 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 22, 0, 4 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 22, 1, 4 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 22, 2, 4 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 22, 3, 4 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 22, 4, 4 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 22, 5, 4 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 22, 6, 4 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 22, 7, 4 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 22, 8, 4 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 22, 9, 4 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 23, 0, 4 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 23, 1, 4 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 23, 2, 4 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 23, 3, 4 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 23, 4, 4 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 23, 5, 4 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 23, 6, 4 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 23, 7, 4 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 23, 8, 4 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 23, 9, 4 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 24, 0, 4 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 24, 1, 4 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 24, 2, 4 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 24, 3, 4 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 24, 4, 4 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 24, 5, 4 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 24, 6, 4 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 24, 7, 4 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 24, 8, 4 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 24, 9, 4 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 25, 0, 4 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 25, 1, 4 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 25, 2, 4 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 25, 3, 4 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 25, 4, 4 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 25, 5, 4 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 25, 6, 4 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 25, 7, 4 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 25, 8, 4 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 25, 9, 4 },
};

s16 gMapcardSlotX[6] = {
    20,
    57,
    94,
    131,
    168,
    205,
};

PrizeMapCardBackAnimStep gPrizeMapCardBackAnim[7] = {
    { 0, 5, 0, 0 },
    { 1, 5, 0, 0 },
    { 2, 5, 0, 0 },
    { 3, 5, 0, 0 },
    { 4, 5, 0, 0 },
    { 5, 5, 0, 0 },
    { 0, 100, 0, 0 },
};

TaskDesc gTaskDescMapcard = {
    "Mapcard",
    (TaskInitFunc)Mapcard_0,
    (TaskUpdateFunc)Mapcard_1,
    (TaskDrawFunc)Mapcard_2,
    (TaskDestroyFunc)Mapcard_3,
    sizeof(MapcardWork),
};

TaskDesc gTaskDescReloadGage = {
    "Reload Gage",
    (TaskInitFunc)Reload_Gage_0,
    (TaskUpdateFunc)Reload_Gage_1,
    (TaskDrawFunc)Reload_Gage_2,
    (TaskDestroyFunc)Reload_Gage_3,
    sizeof(CardDisplayWork),
};

void* gReloadCounterTiles[4] = {
    gUnk_0909A4E0,
    gUnk_0909AB98,
    gUnk_09099E28,
    gUnk_0909AB98,
};

AnimHeader** gReloadCounterAnims[4] = {
    gUnk_09EEA4E0,
    gUnk_09EEA578,
    gUnk_09EEA448,
    gUnk_09EEA578,
};

void** gReloadCounterFrames[4] = {
    gUnk_09EEA494,
    gUnk_09EEA52C,
    gUnk_09EEA3FC,
    gUnk_09EEA52C,
};

void* gReloadCardTiles[4] = {
    gUnk_0909FDCA,
    gRiCardF0RedTiles,
    gUnk_0909EFDE,
    gUnk_0909EFDE,
};

void** gReloadGaugeFrames[4] = {
    gUnk_09EEAF04,
    gUnk_09EEAEBC,
    gUnk_09EEAE74,
    gUnk_09EEAEBC,
};

AnimHeader** gReloadGaugeAnims[4] = {
    gUnk_09EEAF38,
    gUnk_09EEAEF0,
    gUnk_09EEAEA8,
    gUnk_09EEAEF0,
};
