#include "macros.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "card_battle.h"
#include "mode_test_api.h"
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
#include "map_card_assets.h"
#include "game.h"
#include "sprites_map.h"
#include "sprites_worldselect.h"
#include "battle_backgrounds.h"
#include "prize_card.h"
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
#include "mode_battle_data.h"
#include "player_progression_types.h"
#include "types.h"
#include "gba/macro.h"
#include "sprite_palettes.h"
#include <stddef.h>

static TaskPool sModeWorldselectTasks;

static u8 sMapCardDelivered;

static void* sSelectedMapCard;

MapCardUiResources gMapCardUiResources EWRAM_COMMON(16);

u8 gMapCardCounts[270] EWRAM_COMMON(16);

u16 CountMapCardsOfKind(u16 a);
u8 UpdateReloadGageIdle(CardDisplayWork* w, void* a);
u8 UpdateMapSelectSetup(MapSelectWork* w, void* a);
void LoadMapSelectKindPalette(u16 a, MapSelectWork* w);
s32 LoadMapSelectValueCounts(u16 a, MapSelectWork* w);
u8 UpdateMapSelectSlideIn(MapSelectWork* w, void* a);
u8 UpdateMapSelectKindInput(MapSelectWork* w, void* a);
void AimMapcardAtDoor(MapcardWork* w);
u8 UpdateMapcardFlyToDoor(MapcardWork* w, void* a);
s32 RemoveMapCard(u16 a);
u8 UpdateMapSelectValueInput(MapSelectWork* w, void* a);
u8 UpdateMapSelectLeaveValues(MapSelectWork* w, void* a);
u8 UpdateMapSelectClose(MapSelectWork* w);
void HandleMapSelectKindCursor(MapSelectWork* w);
void ApplyMapSelectPageScroll(MapSelectWork* w);
s32 SelectNearestMapSelectCard(MapSelectWork* w);
void LoadMapSelectGridPalette(u16 a, MapSelectWork* w);
void HandleMapSelectValueCursor(MapSelectWork* w);
void UpdateMapcardRise(MapcardWork* w);
void func_08094DEC(MapcardWork* w);
u8 func_08094E4C(MapcardWork* w);
MapcardWork* CreateMapCard(MapcardArgs* args, TaskPool* pool);
void LinkMapcardNode(MapcardWork* w);
void UpdateReloadGageRingPosition(CardDisplayWork* w);
void StepReloadGageSine(ReloadGauge* p);
void InitReloadGageCounterAnim(ReloadGauge* p, void* a, u8 b, s32 count);
void SetReloadGageCounterAnim(ReloadGauge* p, s32 count);
s32 UpdateReloadGageSlide(ReloadGauge* p, CardDisplayWork* w);
void InitReloadGageAnims(ReloadGauge* p, CardDisplayWork* w, u8 idx);
void UpdateReloadGageAnims(ReloadGauge* p, CardDisplayWork* w);
void SetReloadGageIdleFrames(ReloadGauge* p, CardDisplayWork* w);
void AdvanceReloadGageAnim(ReloadGauge* p, CardDisplayWork* w);
void ResetReloadGageAnim(ReloadGauge* p);

void WORLDSELECT_0() {
    SetBgMode2();
    SetupBg(3, 0, 12, 0);
    SetupBg(2, 2, 28, 10);
    SetBgSize(3, 0x8000);
#ifdef VERSION_EU
    LoadBgTiles(3, gUnk_08C8C824, 0x4000);
    LoadBgPalette(3, gUnk_08F68A84, 0x100);
    LoadBgMapLz77(3, gUnk_08EF4384);
#else
    LoadBgTiles(3, gUnk_08C8C824, 0x4000);
    LoadBgPalette(3, gUnk_08F68A84, 0x100);
    LoadBgMap(3, gUnk_08EF4384, 0x1000);
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

void CreateMapSelectCards(MapSelectWork* w);

void MapSelect_0(MapSelectWork* w, u8* a) {
    s32 n;

    ResetMessageWindowFlags();
    CpuFill32(0, w, sizeof(MapSelectWork));
    w->status = a;
    *a = 0;
    w->messageTimer = 0;
    w->cancelled = 0;
    w->pageScroll = 0;
    w->card2 = NULL;
    sMapCardDelivered = 0;
    w->valueColumn = 0;
    w->valueRow = 0;
    w->scrollBarVisible = 0;
    w->isEventDoor = SelectCurrentEventDoor();
    n = GetCurrentRoomCardValue() + 1;
    w->requiredValue = n;

    if (n == 10) {
        w->requiredValue = 0;
    }

    w->tiles3 = NULL;

    if (!w->isEventDoor) {
        if (w->requiredValue == 0) {
            w->tiles4 = AllocSpriteFrameTiles(0x80);
            UpdateSpriteFrameTiles(w->tiles4, gUnk_09EF1198[0], gUnk_0950C478);
        } else {
            w->tiles4 = AllocSpriteFrameTiles(0x180);
            UpdateSpriteFrameTiles(w->tiles4, gUnk_09EF1198[1], gUnk_0950C478);
            RequestDma3Copy(w->tiles4->src + (w->requiredValue << 7),
                           (void*)(OBJ_VRAM0 + ((w->tiles4->index + 4) << 5)), 0x80);
            RequestDma3Copy(w->tiles4->src + 0x500,
                           (void*)(OBJ_VRAM0 + (w->tiles4->index << 5)), 0x80);
        }

        w->tiles2 = LoadObjTiles(gCardBacks[4].tiles2, 0x300);
        w->palette = LoadObjPalette(gUnk_09618D38, 32);
        FadeSetPaletteExcluded(w->palette->index + 16, 1);
    } else {
        w->tiles4 = NULL;
        w->tiles2 = NULL;
        w->palette = LoadObjPalette(gUnk_09618D38, 32);
        FadeSetPaletteExcluded(w->palette->index + 16, 1);
    }

    gMapCardUiResources.tiles = AllocObjTiles(0x280, NULL);
    SetObjTileSource(gMapCardUiResources.tiles, gUnk_0908B1B4);
    AnimInit(&gMapCardUiResources.anim, gUnk_09EEA164, gUnk_09EEA148);
    AnimStart(&gMapCardUiResources.anim, 0, ANIM_FLAG_LOOP);
    gMapCardUiResources.gfx = AnimGetGfx(&gMapCardUiResources.anim);
    w->tiles = AllocObjTiles(0x3C0, NULL);
    w->palette2 = LoadObjPalette(gUnk_09618D18, 32);
    SetObjTileSource(w->tiles, gUnk_093F47E4);
    AnimInit(&w->anim, gUnk_09EF1194, gUnk_09EF1180);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    w->tiles5 = AllocObjTiles(0x120, NULL);
    w->palette3 = LoadObjPalette(gUnk_09618CD8, 32);
    SetObjTileSource(w->tiles5, gUnk_093F4578);
    AnimInit(&w->anim2, gUnk_09EF1170, gUnk_09EF1150);
    AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
    w->gfx2 = AnimGetGfx(&w->anim2);
    w->tiles7 = LoadObjTiles(gUnk_093F5422, 0xC0);
    w->y3 = -0x800;
    w->y4 = 0xA000;
    w->barSteps = 16;
    w->slideSteps = 16;
    w->kindCount = CountOwnedMapCardKinds();
    TaskPoolInit(&w->tasks, w->kindCount + 10);
    ListPoolInit(&w->cards);
    w->kindEntries = EwramAlloc(w->kindCount * sizeof(MapSelectKindEntry));
    ListOwnedMapCardKinds(w->kindEntries);
    CreateMapSelectCards(w);
#ifdef VERSION_EU
    gMapCardUiResources.extraTiles = LoadObjTiles(gMapCardUiExtraTilesByLanguage[gLanguage], gMapCardUiExtraTileSizes[gLanguage]);
#else
    gMapCardUiResources.extraTiles = LoadObjTiles(gUnk_093F6734, 0x360);
#endif
    gMapCardUiResources.palette = w->palette3;
#ifdef VERSION_EU
    gMapCardUiResources.sprites = gMapCardUiSpritesByLanguage[gLanguage];
#else
    gMapCardUiResources.sprites = gUnk_09EF11F8;
#endif
    w->tiles6 = LoadObjTiles(gUnk_093F5C40, 32);
    w->page = 0;
    w->lastPage = 0;
    w->card = ListPoolFirst(&w->cards);
    w->prevCard = NULL;
    m4aSongNumStart(SONG_SYS_CLICKI02);
    sSelectedMapCard = NULL;
    w->x2 = 0x1600;
    w->y2 = 0x16400;
    w->unk_28D[0] = 0;
    w->unk_260 = 0;
    w->cursorTargetX = 0x1600;
    w->unk_268 = 0x6400;
    w->unk_28D[1] = 0;
    w->steps = 0;

    if (w->card != NULL) {
        w->x = w->card->x;
        w->y = w->card->y;
        w->card->flags |= MAPCARD_FLAG_CURSOR;
    } else {
        w->x = -0x6400;
        w->y = -0x6400;
    }

    w->x3 = -0xA000;
    w->titleY = 0;
    w->palette4 = LoadTextPalette(1);
    w->textSlotCounts[0] = 0;
    w->textSlotCounts[1] = 0;
    w->textSlotCounts[2] = 0;
    InitTextSlots(w->textSlots, 48);

    if (w->card != NULL) {
        w->prevCard = w->card;
        w->textSlotCounts[0] = LoadTextSlots(GetRoomName(gMapCardDefs[w->card->args.baseCardId].kind), w->textSlots);
    }

    w->nameY = 0x19100;
    FadeSetPaletteExcluded(w->palette3->index + 16, 1);
    FadeSetPaletteExcluded(w->palette2->index + 16, 1);
    FadeSetPaletteExcluded(15, 1);
    FadeSetPaletteExcluded(w->palette4->index + 16, 1);
    w->unk_1E4 = NULL;
    w->mosaicX = 9;
    w->mosaicY = 9;
    w->mosaicTimer = 0;
    w->inTutorial = 0;
}

u8 MapSelect_1(MapSelectWork* w, void* a) {
#ifdef VERSION_EU
    LoadBgTiles(1, gUnk_09508098, 0x2020);

    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        w->tiles3 = LoadObjTiles(gUnk_093F7172, 0x400);
        break;
    case LANGUAGE_FRENCH:
        w->tiles3 = LoadObjTiles(gUnkEu_094C6C22, 0x400);
        RequestDma3Copy(gUnkEu_0952DDE4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
        break;
    case LANGUAGE_GERMAN:
        w->tiles3 = LoadObjTiles(gUnkEu_094C789A, 0x400);
        RequestDma3Copy(gUnkEu_0952E0E4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
        break;
    case LANGUAGE_ITALIAN:
        w->tiles3 = LoadObjTiles(gUnkEu_094C7472, 0x400);
        RequestDma3Copy(gUnkEu_0952DFE4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
        break;
    case LANGUAGE_SPANISH:
        w->tiles3 = LoadObjTiles(gUnkEu_094C704A, 0x400);
        RequestDma3Copy(gUnkEu_0952DEE4, (u8*)GetBgCharBase(1) + 0x1AA0, 0x100);
        break;
    }
#else
    w->tiles3 = LoadObjTiles(gUnk_093F7172, 0x400);
    LoadBgTiles(1, gUnk_09508098, 0x2020);
#endif
    LoadPalette(gUnk_09618C58, (void*)(BG_PLTT + 12 * PLTT_SIZE_4BPP), 32);
    LoadPalette(&gUnk_09618C58[0x40], (void*)(BG_PLTT + 14 * PLTT_SIZE_4BPP), 64);
    FadeSetPaletteExcluded(12, 1);
    FadeSetPaletteExcluded(14, 1);
    FadeSetPaletteExcluded(15, 1);
    w->messageTimer++;
    DisableBg(1);
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectSetup);
    return 1;
}

u8 UpdateMapSelectSetup(MapSelectWork* w, void* a) {
    s32 n;

    SetBgMapBlocks(1, gMapSelectBgMapBlocks, 1, 2);
    w->bgScrollY = 0;
    ScrollBgMapTo(1, 0, 0);
    EnableBg(1);

    if (w->isEventDoor == 1) {
        w->remainingKeys = CountRemainingEventKeys();
        w->unk_2DC = GetEventKey(0);
        n = w->remainingKeys;

        while (n != 0) {
            n--;
        }

        w->eventKeyArgs.palette = w->palette3;
        w->eventKeyArgs.closeMode = 0;
        w->eventKey =
            TaskCreate(&w->tasks, &gTaskDescSELMAPEVKEY, &w->eventKeyArgs)->work;
    }

    LoadMapSelectKindPalette(w->card->args.baseCardId, w);
    SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectSlideIn);
    return 1;
}

u8 UpdateMapSelectEventDoorTutorial(MapSelectWork* w, void* a);

u8 UpdateMapSelectSlideIn(MapSelectWork* w, void* a) {
    MapcardWork* n;

    if (w->barSteps != 0) {
        ApproachValue(&w->y3, 0, w->barSteps);
        ApproachValue(&w->y4, 0x9800, w->barSteps);
        w->barSteps--;
    } else {
        ApproachValue(&w->bgScrollY, 0x10000, w->slideSteps);
        ApproachValue(&w->x3, 0, w->slideSteps);
        ScrollBgMapTo(1, 0, (u32)w->bgScrollY >> 8);

        if (w->slideSteps != 0) {
            w->slideSteps--;
        } else {
            if ((gGameState.progression.tutorialFlags & 8) == 0) {
                w->inTutorial = 1;
                ResetMessageWindowFlags();
                w->tutorialMessage = 95;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectTutorial);
            } else if ((gGameState.progression.tutorialFlags & 0x40) == 0 && w->isEventDoor == 1) {
                ResetMessageWindowFlags();
                w->tutorialMessage = 109;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectEventDoorTutorial);
                gGameState.progression.tutorialFlags |= 0x40;
            } else {
                n = ListPoolFirst(&w->cards);
                SetBgMapBlocks(1, gMapSelectBgMapBlocks, 1, 2);

                while (n != NULL) {
                    n->flags |= MAPCARD_FLAG_RAISED;
                    n = ListPoolNext(&n->node);
                }

                if (w->kindCount <= 6) {
                    w->lastPage = 0;
                } else {
                    w->lastPage = w->kindCount / 6;

#ifdef VERSION_EU
                    if ((u16)(w->kindCount % 6) == 0) {
                        w->lastPage--;
                    }
#endif
                }

                w->y2 = 0x6400;
                w->y = 0x7A00;
                w->nameY = 0x9100;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectKindInput);
                w->scrollBarVisible = 1;
            }
        }
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 UpdateMapSelectEnterValues(MapSelectWork* w, void* a) {
    s8 v;

    if (w->card->steps == 0) {
        LoadBgTiles(1, &gUnk_09508098[0x2020], 0x23C0);

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

        LoadBgMap(1, &gUnk_0960F2B8[0xC00], 0x800);
        LoadMapSelectGridPalette(w->card->args.baseCardId, w);
        v = LoadMapSelectValueCounts(w->card->args.baseCardId, w);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectValueInput);
        ReleaseObjTiles(w->tiles);
        w->tiles = AllocObjTiles(0x1E0, NULL);
        SetObjTileSource(w->tiles, gUnk_093F556C);
        AnimInit(&w->anim, gUnk_09EF11CC, gUnk_09EF11B8);
        AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
        w->gfx = AnimGetGfx(&w->anim);
        w->savedCursorX = w->x2 >> 8;
        w->savedCursorY = w->y2 >> 8;

        if (v > 4) {
            w->valueColumn = v - 5;
            w->valueRow = 1;
        } else {
            w->valueColumn = v;
            w->valueRow = 0;
        }

        w->steps = 4;
        w->steps2 = 4;
        w->scrollBarVisible = 0;
    }

    SetObjMosaicSize(w->mosaicX, w->mosaicY);

    if (w->mosaicTimer == 2) {
        if (w->mosaicX != 0) {
            w->mosaicX--;
        }

        if (w->mosaicY != 0) {
            w->mosaicY--;
        }

        w->mosaicTimer = 0;
    }

    w->mosaicTimer++;
    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 UpdateMapSelectValueInput(MapSelectWork* w, void* a) {
    u16 keys;
    s16 sel;
    u8 n;

    keys = GetKeysPressed();
    sel = w->valueColumn + w->valueRow * 5;

    if ((gGameState.progression.tutorialFlags & 8) == 0) {
        if (w->steps == 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectValueTutorial);
            TaskPoolUpdate(&w->tasks);
            return 1;
        }

        keys = 0;
    }

    switch (keys & (A_BUTTON | B_BUTTON | SELECT_BUTTON | START_BUTTON | L_BUTTON | R_BUTTON)) {
    case B_BUTTON:
#ifdef VERSION_EU
        LoadBgTiles(1, gUnk_09508098, 0x2020);

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

        LoadBgMap(1, gUnk_096102B8, 0x800);
#else
        LoadBgTiles(1, gUnk_09508098, 0x2020);
        LoadBgMap(1, gUnk_096102B8, 0x800);
#endif
        w->card->flags &= ~MAPCARD_FLAG_OPENED;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectLeaveValues);
        m4aSongNumStart(SONG_SYS_CLOSE);
        break;
    case A_BUTTON:
        n = DoorAcceptsMapCard((struct MapCardAttributes*)&gMapCardDefs[w->card->args.baseCardId + sel].kind);

        if (n == 1) {
            if (gMapCardCounts[w->card->args.baseCardId + sel] != 0) {
                if (w->isEventDoor == 1) {
                    m4aSongNumStart(SONG_SYS_KETEI2);

                    if (CountMapCardsOfKind(w->card->args.baseCardId) == 0) {
                        w->card->value = sel;
                        w->card->flags |= MAPCARD_FLAG_CHOSEN;
                    }

                    RemoveMapCard(w->card->args.baseCardId + sel);

                    if ((u8)PayEventKey((struct UnkStruct_080E8E24*)&gMapCardDefs[w->card->args.baseCardId + sel].kind) == 1) {
                        w->remainingKeys = CountRemainingEventKeys();
                        w->eventKey->paidCount++;
                        w->eventKey->slideSteps = 8;

                        if (w->remainingKeys == 0) {
                            w->card->value = sel;
                            w->card->flags |= MAPCARD_FLAG_CHOSEN;
                            *w->status = 2;
                            w->slideSteps = 16;
                            w->barSteps = 16;
                            w->lastPage = 0;
                            w->page = 0;
                            w->eventKeyArgs.closeMode = n;
                            SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectClose);
                            return 1;
                        }
                    }

                    LoadMapSelectKindPalette(w->card->args.baseCardId, w);
                    LoadMapSelectGridPalette(w->card->args.baseCardId, w);

                    if ((s8)LoadMapSelectValueCounts(w->card->args.baseCardId, w) == -1) {
#ifdef VERSION_EU
                        LoadBgTiles(1, gUnk_09508098, 0x2020);

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

                        LoadBgMap(1, gUnk_096102B8, 0x800);
#else
                        LoadBgTiles(1, gUnk_09508098, 0x2020);
                        LoadBgMap(1, gUnk_096102B8, 0x800);
#endif
                        w->card->flags &= ~MAPCARD_FLAG_OPENED;
                        RemoveMapSelectCard(w);
                        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectLeaveValues);
                    }

                    break;
                }

                w->card->value = sel;
                w->card->flags |= MAPCARD_FLAG_CHOSEN;
                RemoveMapCard(w->card->args.baseCardId + sel);
                *w->status = 2;
                w->slideSteps = 16;
                w->barSteps = 16;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectClose);
                m4aSongNumStart(SONG_SYS_KETEI2);
                w->lastPage = 0;
                w->page = 0;
                w->eventKeyArgs.closeMode = n;
                return 1;
            }
        }

        m4aSongNumStart(SONG_SYS_BEEP);
        break;
    }

    w->gfx2 = AnimUpdate(&w->anim2);
    w->gfx = AnimUpdate(&w->anim);
    gMapCardUiResources.gfx = AnimUpdate(&gMapCardUiResources.anim);
    TaskPoolUpdate(&w->tasks);
    HandleMapSelectValueCursor(w);
    SetObjMosaicSize(w->mosaicX, w->mosaicY);

    if (w->mosaicTimer == 2) {
        if (w->mosaicX != 0) {
            w->mosaicX--;
        }

        if (w->mosaicY != 0) {
            w->mosaicY--;
        }

        w->mosaicTimer = 0;
    }

    w->mosaicTimer++;
    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 UpdateMapSelectLeaveValues(MapSelectWork* w, void* a) {
    MapcardWork* node;

    if (CountOwnedMapCardKinds() == 0) {
        return 0;
    }

    if (w->card->steps == 0) {
        node = ListPoolFirst(&w->cards);

        while (node != NULL) {
            if (w->card != node) {
                node->flags |= MAPCARD_FLAG_RAISED;
            }

            node = ListPoolNext(&node->node);
        }

        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectKindInput);
        ReleaseObjTiles(w->tiles);
        w->tiles = AllocObjTiles(0x3C0, NULL);
        SetObjTileSource(w->tiles, gUnk_093F47E4);
        AnimInit(&w->anim, gUnk_09EF1194, gUnk_09EF1180);
        AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
        w->gfx = AnimGetGfx(&w->anim);
        w->x2 = w->savedCursorX << 8;
        w->y2 = w->savedCursorY << 8;
        w->x = w->card->x;
        w->y = w->card->y;
        w->scrollBarVisible = 1;
    }

    SetObjMosaicSize(w->mosaicX, w->mosaicY);

    if (w->mosaicTimer == 2) {
        if (w->mosaicX != 0) {
            w->mosaicX--;
        }

        if (w->mosaicY != 0) {
            w->mosaicY--;
        }

        w->mosaicTimer = 0;
    }

    w->mosaicTimer++;
    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 UpdateMapSelectKindInput(MapSelectWork* w, void* a) {
    u16 keys = GetKeysPressed();
    MapcardWork* p;

    ApplyMapSelectPageScroll(w);
    SetObjMosaicSize(w->mosaicX, w->mosaicY);

    if (w->mosaicTimer == 2) {
        if (w->mosaicX != 0) {
            w->mosaicX--;
        }

        if (w->mosaicY != 0) {
            w->mosaicY--;
        }

        w->mosaicTimer = 0;
    }

    w->mosaicTimer++;

    switch (keys & (A_BUTTON | B_BUTTON | SELECT_BUTTON | START_BUTTON | L_BUTTON | R_BUTTON)) {
    case A_BUTTON:
        if (w->card != NULL) {
            if (w->card->args.baseCardId >= 220) {
                if (DoorAcceptsMapCard((struct MapCardAttributes*)&gMapCardDefs[w->card->args.baseCardId + 1].kind) == 1) {
                    if (gMapCardCounts[w->card->args.baseCardId + 1] != 0) {
                        m4aSongNumStart(SONG_SYS_KETEI2);
                        RemoveMapCard(w->card->args.baseCardId + 1);

                        if ((u8)PayEventKey((struct UnkStruct_080E8E24*)&gMapCardDefs[w->card->args.baseCardId + 1].kind) == 1) {
                            w->remainingKeys = CountRemainingEventKeys();
                            w->eventKey->paidCount++;
                            w->eventKey->slideSteps = 8;

                            if (w->remainingKeys == 0) {
                                w->card->value = 1;
                                w->card->flags |= MAPCARD_FLAG_CHOSEN;

                                for (p = ListPoolFirst(&w->cards); p != NULL; p = ListPoolNext(&p->node)) {
                                    if (w->card != p) {
                                        p->flags &= ~MAPCARD_FLAG_RAISED;
                                    }
                                }

                                *w->status = 2;
                                w->slideSteps = 16;
                                w->barSteps = 16;
                                w->lastPage = 0;
                                w->page = 0;
                                w->eventKeyArgs.closeMode = 1;
                                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectClose);
                                return 1;
                            }
                        }

                        break;
                    }
                }
            } else {
                if (CountMapCardsOfKind(w->card->args.baseCardId) != 0) {
                    for (p = ListPoolFirst(&w->cards); p != NULL; p = ListPoolNext(&p->node)) {
                        if (w->card != p) {
                            p->flags &= ~MAPCARD_FLAG_RAISED;
                        }
                    }

                    if (w->card != NULL) {
                        w->openedCardX = w->card->x;
                        w->card->flags |= MAPCARD_FLAG_OPENED;
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
        if (!w->inTutorial) {
            for (p = ListPoolFirst(&w->cards); p != NULL; p = ListPoolNext(&p->node)) {
                p->flags &= ~MAPCARD_FLAG_RAISED;
            }

            w->cancelled = 1;
            w->slideSteps = 16;
            w->barSteps = 16;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectClose);
            m4aSongNumStart(SONG_SYS_CANSEL);
            sSelectedMapCard = NULL;
            w->lastPage = 0;
            w->page = 0;
            w->eventKeyArgs.closeMode = 2;
        } else {
            m4aSongNumStart(SONG_SYS_BEEP);
        }

        break;
    }

    HandleMapSelectKindCursor(w);

    if (w->pageScroll == 0) {
        if (w->card != w->prevCard) {
            if (w->card != NULL) {
                w->textSlotCounts[0] = LoadTextSlots(GetRoomName(gMapCardDefs[w->card->args.baseCardId].kind), w->textSlots);
                LoadMapSelectKindPalette(w->card->args.baseCardId, w);
            } else {
                w->textSlotCounts[0] = 0;
                w->textSlotCounts[1] = 0;
                w->textSlotCounts[2] = 0;
            }

            w->prevCard = w->card;
            w->steps = 4;
        } else if (w->card != NULL) {
            ApproachValue(&w->x, w->card->x, w->steps);
            ApproachValue(&w->y, w->card->y, w->steps);

            if (w->steps != 0) {
                w->steps--;
            }
        }
    }

    w->gfx2 = AnimUpdate(&w->anim2);
    w->gfx = AnimUpdate(&w->anim);
    gMapCardUiResources.gfx = AnimUpdate(&gMapCardUiResources.anim);
    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 UpdateMapSelectClose(MapSelectWork* w) {
    ApproachValue(&w->bgScrollY, 0, w->slideSteps);
    ApproachValue(&w->x3, -0xA000, w->slideSteps);
    ApproachValue(&w->y2, 0x16400, w->slideSteps);
    ApproachValue(&w->y, 0x17A00, w->slideSteps);
    ApproachValue(&w->nameY, 0x19100, w->slideSteps);
    ScrollBgMapTo(1, 0, (u32)w->bgScrollY >> 8);
    w->scrollBarVisible = 0;

    if (w->mosaicX <= 8) {
        w->mosaicX++;
    }

    if (w->mosaicY <= 8) {
        w->mosaicY++;
    }

    SetObjMosaicSize(w->mosaicX, w->mosaicY);

    if (w->slideSteps != 0) {
        w->slideSteps--;
    } else if (w->barSteps != 0) {
        ApproachValue(&w->y3, -0x800, w->barSteps);
        ApproachValue(&w->y4, 0xA000, w->barSteps);
        w->barSteps--;
    } else {
        if (w->cancelled || (w->card->flags & MAPCARD_FLAG_DELIVERED)) {
            return 0;
        }
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

void MapSelect_2(MapSelectWork* w) {
    if (w->tiles3 != NULL && w->palette3 != NULL) {
        DrawSprite(w->x3 >> 8, w->titleY >> 8,
#ifdef VERSION_EU
                   gMapSelectTitleSpritesByLanguage[gLanguage][0],
#else
                   gUnk_09EF1228[0],
#endif
                   w->tiles3, w->palette3, NULL, 0, 80);
    }

    if (w->isEventDoor == 1) {
        switch (gMapCardDefs[w->card->args.baseCardId].backIndex) {
        case 0:
            break;
        case 2:
            DrawSprite((w->card->x >> 8) + 4, (w->card->y >> 8) - 32, gMapCardUiResources.sprites[3], gMapCardUiResources.extraTiles, gMapCardUiResources.palette, NULL, 0, 20);
            break;
        case 3:
            DrawSprite((w->card->x >> 8) + 4, (w->card->y >> 8) - 32, gMapCardUiResources.sprites[7], gMapCardUiResources.extraTiles, gMapCardUiResources.palette, NULL, 0, 20);
            break;
        case 1:
            DrawSprite((w->card->x >> 8) + 4, (w->card->y >> 8) - 32, gMapCardUiResources.sprites[5], gMapCardUiResources.extraTiles, gMapCardUiResources.palette, NULL, 0, 20);
            break;
        case 4:
            break;
        }
    }

    if (!IsMessageWindowOpen()) {
        DrawSprite((w->x >> 8) - 23, (w->y >> 8) - 27, w->gfx, w->tiles, w->palette2, NULL, 0, 41);
        DrawSprite((w->x2 >> 8) - 16, (w->y2 >> 8) - 12, w->gfx2, w->tiles5, w->palette3, NULL, 0, 40);
    }

    if (w->scrollBarVisible) {
        DrawSprite(224,
#ifdef VERSION_EU
                   (18 / w->lastPage) * w->page + 108,
#else
                   (17 / w->lastPage) * w->page + 108,
#endif
                   gUnk_09EEB000, w->tiles6, w->palette, NULL, 0, 40);
    }

    if (!w->isEventDoor && w->mosaicX != 9 && w->mosaicY != 9) {
        DrawSprite(120, 56, NULL, w->tiles4, w->palette, NULL, SPRITE_FLAG_MOSAIC, 60);
        DrawSprite(120, 56, gCardBacks[4].gfx2, w->tiles2, w->palette, NULL, SPRITE_FLAG_MOSAIC, 60);
    }

    DrawSprite(128, w->y3 >> 8, gUnk_09EF11AC[0], w->tiles7, w->palette3, NULL, SPRITE_PRIORITY(2), 80);
    DrawSprite(128, w->y4 >> 8, gUnk_09EF11AC[1], w->tiles7, w->palette3, NULL, SPRITE_PRIORITY(2), 80);
    DrawTextSlots(16, w->nameY >> 8, w->textSlots, w->palette4, 50, w->textSlotCounts[0]);
    TaskPoolDraw(&w->tasks);
}

void MapSelect_3(MapSelectWork* w) {
    TaskPoolDestroy(&w->tasks);

    if (w->kindEntries != NULL) {
        EwramFree(w->kindEntries);
    }

    FadeSetPaletteExcluded(w->palette3->index + 16, 0);
    FadeSetPaletteExcluded(w->palette2->index + 16, 0);
    FadeSetPaletteExcluded(15, 0);
    FadeSetPaletteExcluded(w->palette4->index + 16, 0);
    ReleaseObjTiles(w->tiles5);
    ReleaseObjPalette(w->palette3);
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette2);
    ReleaseObjTiles(w->tiles3);

    if (w->tiles4 != NULL) {
        ReleaseObjTiles(w->tiles4);
    }

    if (w->tiles2 != NULL) {
        ReleaseObjTiles(w->tiles2);
    }

    if (w->palette != NULL) {
        ReleaseObjPalette(w->palette);
    }

    ReleaseObjTiles(w->tiles7);
    FreeTextSlots(w->textSlots, 48);
    ReleaseObjPalette(w->palette4);
    *w->status = 1;
    ReleaseObjTiles(w->tiles6);
    ReleaseObjTiles(gMapCardUiResources.tiles);
    ReleaseObjTiles(gMapCardUiResources.extraTiles);
}

void CreateMapSelectCards(MapSelectWork* w) {
    MapcardArgs args;
    MapSelectKindEntry* q;
    u16 i;

    for (i = 0; i < w->kindCount; i++) {
        q = w->kindEntries;
        args.baseCardId = q[i].baseCardId;
        args.index = i;
        args.kindCount = w->kindCount;
        args.count = q[i].count;
        args.pool = &w->cards;
        args.parent = w;
        CreateMapCard(&args, &w->tasks);
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

void ApplyMapSelectPageScroll(MapSelectWork* w) {
    MapcardWork* node;
    s8 i;

    switch (w->pageScroll) {
    case 0:
        break;
    case 1:
        node = w->card2;
        i = 0;

        while (node != NULL) {
            node->x = gMapcardSlotX[i++] << 8;

            if (i == 6) {
                break;
            }

            node = ListPoolNext(&node->node);
        }

        w->pageScroll = 0;
        SelectNearestMapSelectCard(w);

        if (w->card != NULL) {
            w->cursorTargetX = w->card->x;
            w->steps2 = 4;
        }

        w->page++;
        break;
    case 2:
        node = w->card2;
        i = 5;

        while (node != NULL) {
            node->x = gMapcardSlotX[i--] << 8;

            if (i < 0) {
                break;
            }

            node = ListPoolPrev(&node->node);
        }

        w->pageScroll = 0;
        SelectNearestMapSelectCard(w);

        if (w->card != NULL) {
            w->cursorTargetX = w->card->x;
            w->steps2 = 4;
        }

        w->page--;
        break;
    }
}

s32 SelectNearestMapSelectCard(MapSelectWork* w) {
    MapcardWork* node;
    s32 best;
    s32 d;
    u16 r;
    void* z;
    void* q;

    node = ListPoolFirst(&w->cards);
    best = 0x100;
    z = NULL;
    w->card = z;

    while (node != NULL) {
        if (node->x != -0x6400) {
            d = (node->x >> 8) - (w->x2 >> 8);
            r = Sqrt(d * d);

            if (best > r) {
                best = r;
                w->card = node;
            }
        }

        node = ListPoolNext(&node->node);
    }

    q = w->card;

    if (q != NULL) {
        q = &((MapcardWork*)q)->flags;
        r = *(u16*)q | MAPCARD_FLAG_CURSOR;
        *(u16*)q = r;

        return (w->card->x - w->x2) >> 8;
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
    return eu_0805E924(gRoomNames[a]);
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

void LoadMapSelectKindPalette(u16 a, MapSelectWork* w) {
    u16 i;
    u16 j;
    u8* pal;
    s32 k;
    s32 k2;
    MapCardDef* card;
    MapCardDef* cards;

    for (i = 0; i < 22; i++) {
        pal = w->paletteBuffer;
        pal[i] = gUnk_09619098[i + 32];
    }

    for (i = 22; i < 32; i++) {
        pal = w->paletteBuffer;
        pal[i] = gUnk_09618C58[i + 64];
    }

    for (i = a, j = 2; i < a + 10; i++, j += 2) {
        cards = gMapCardDefs;
        card = &cards[a];
        pal = w->paletteBuffer;

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

    LoadPalette(w->paletteBuffer, (void*)(BG_PLTT + 14 * PLTT_SIZE_4BPP), 32);
}

void LoadMapSelectGridPalette(u16 a, MapSelectWork* w) {
    u16 i;
    u16 j;
    u8* pal;
    MapcardWork** mp;
    s32 k;

    for (i = 0; i < 22; i++) {
        pal = w->paletteBuffer;
        pal[i] = gUnk_09619098[i + 32];
    }

    for (i = 22, j = 2; i < 26; i++, j++) {
        mp = &w->card;
        pal = w->paletteBuffer;

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
        pal = w->paletteBuffer;
        pal[i] = gUnk_09618C58[i];
    }

    for (i = a, j = 2; i < a + 10; i++, j += 2) {
        pal = w->paletteBuffer;

        if (gMapCardCounts[i] != 0) {
            pal[j] = -1;
            k = j + 1;
            pal[k] = 0x7F;
        }
    }

    LoadPalette(w->paletteBuffer, (void*)(BG_PLTT + 12 * PLTT_SIZE_4BPP), 32);
}

s32 LoadMapSelectValueCounts(u16 a, MapSelectWork* w) {
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
            w->valueCounts[j] = count;
        } else {
            base = GetBgCharBase(1);
            base += gMapSelectCountTileIndices[i - a] * 32;
            RequestDma3Copy(gUnk_09507F58, base, 32);
            w->valueCounts[j] = 0;
        }
    }

    for (i = 0; i < 10; i++) {
        if (w->valueCounts[i] != 0) {
            return (s8)i;
        }
    }

    return -1;
}

s32 FindLastMapSelectValueInRow(MapSelectWork* w) {
    u8* p;
    s32 base;
    u8 i;

    i = 4;
    base = w->valueRow * 5;
    p = w->valueCounts;

    do {
        if (p[i + base] == 0) {
            i--;
        } else {
            return (s8)i;
        }
    } while (i != 0);

    return -1;
}

void HandleMapSelectValueCursor(MapSelectWork* w) {
    s8 c0;
    s8 y0;
    s32 z;

    c0 = w->valueColumn;
    y0 = w->valueRow;
    z = 0;

    switch (GetKeysRepeat() & DPAD_ANY) {
    case DPAD_RIGHT:
        do {
            if (w->valueColumn <= 3) {
                w->valueColumn++;
            } else {
                w->valueColumn = 0;
                w->valueRow ^= 1;
            }
        } while (w->valueCounts[w->valueColumn + w->valueRow * 5] == 0);

        w->steps2 = 4;
        break;
    case DPAD_LEFT:
        do {
            if (w->valueColumn > 0) {
                w->valueColumn--;
            } else {
                w->valueColumn = 4;
                w->valueRow ^= 1;
            }
        } while (w->valueCounts[w->valueColumn + w->valueRow * 5] == 0);

        w->steps2 = 4;
        break;
    case DPAD_UP:
        w->valueRow ^= 1;
        c0 = w->valueColumn;

        while (w->valueCounts[w->valueColumn + w->valueRow * 5] == 0) {
            if (w->valueColumn > 3) {
                z = 1;
                break;
            }

            w->valueColumn++;
            z = 0;
        }

        if (z == 1) {
            w->valueColumn = FindLastMapSelectValueInRow(w);

            if (w->valueColumn == -1) {
                w->valueRow ^= 1;
                w->valueColumn = c0;
            }
        }

        w->steps2 = 4;
        break;
    case DPAD_DOWN:
        w->valueRow ^= 1;
        c0 = w->valueColumn;

        while (w->valueCounts[w->valueColumn + w->valueRow * 5] == 0) {
            if (w->valueColumn > 3) {
                z = 1;
                break;
            }

            w->valueColumn++;
            z = 0;
        }

        if (z == 1) {
            w->valueColumn = FindLastMapSelectValueInRow(w);

            if (w->valueColumn == -1) {
                w->valueRow ^= 1;
                w->valueColumn = c0;
            }
        }

        w->steps2 = 4;
        break;
    }

    if (c0 != w->valueColumn || y0 != w->valueRow) {
        m4aSongNumStart(SONG_SYS_CLICKI04B);
    }

    ApproachValue(&w->x2, gMapSelectValueColumnX[w->valueColumn] << 8, w->steps2);
    ApproachValue(&w->y2, gMapSelectValueRowY[w->valueRow] << 8, w->steps2);
    ApproachValue(&w->x, gMapSelectValueColumnX[w->valueColumn] << 8, w->steps);
    ApproachValue(&w->y, (gMapSelectValueRowY[w->valueRow] + 34) << 8,
                  w->steps);

    if (w->steps != 0) {
        w->steps--;
    }

    if (w->steps2 != 0) {
        w->steps2--;
    }
}

u8 UpdateMapSelectTutorial(MapSelectWork* w, void* a) {
    MapcardWork* n;
    u8 v;

    SetObjMosaicSize(w->mosaicX, w->mosaicY);

    if (w->mosaicTimer == 2) {
        if (w->mosaicX != 0) {
            w->mosaicX--;
        }

        if (w->mosaicY != 0) {
            w->mosaicY--;
        }

        w->mosaicTimer = 0;
    }

    w->mosaicTimer++;

    if (!IsMessageWindowOpen()) {
        if (w->messageTimer == 8) {
            w->messageTimer = 0;

            if (w->tutorialMessage <= 98) {
                CreateSysmsgwinTask(&w->tasks, w->tutorialMessage);
                w->tutorialMessage++;
            } else {
                n = ListPoolFirst(&w->cards);
                SetBgMapBlocks(1, gMapSelectBgMapBlocks, 1, 2);

                while (n != NULL) {
                    n->flags |= MAPCARD_FLAG_RAISED;
                    n = ListPoolNext(&n->node);
                }

                if (w->kindCount <= 6) {
                    w->lastPage = 0;
                } else {
                    v = w->kindCount / 6;
                    w->lastPage = v;
                }

                w->y2 = 0x6400;
                w->y = 0x7A00;
                w->nameY = 0x9100;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectKindInput);
                w->scrollBarVisible = 1;
                w->tutorialMessage = 99;
                return 1;
            }
        } else {
            w->messageTimer++;
        }
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 UpdateMapSelectValueTutorial(MapSelectWork* w, void* a) {
    u8 r;

    r = IsMessageWindowOpen();

    if (!r) {
        if (w->messageTimer == 8) {
            w->messageTimer = 0;

            if (w->tutorialMessage <= 0x66) {
                CreateSysmsgwinTask(&w->tasks, w->tutorialMessage);
                w->tutorialMessage++;
            } else {
                gGameState.progression.tutorialFlags |= 8;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectValueInput);
            }
        } else {
            w->messageTimer++;
        }
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 UpdateMapSelectEventDoorTutorial(MapSelectWork* w, void* a) {
    MapcardWork* node;
    u32 pages;

    SetObjMosaicSize(w->mosaicX, w->mosaicY);

    if (w->mosaicTimer == 2) {
        if (w->mosaicX != 0) {
            w->mosaicX--;
        }

        if (w->mosaicY != 0) {
            w->mosaicY--;
        }

        w->mosaicTimer = 0;
    }

    w->mosaicTimer++;

    if (!IsMessageWindowOpen()) {
        if (w->messageTimer == 8) {
            w->messageTimer = 0;

            if (w->tutorialMessage <= 0x71) {
                CreateSysmsgwinTask(&w->tasks, w->tutorialMessage);
                w->tutorialMessage++;
            } else {
                node = ListPoolFirst(&w->cards);
                SetBgMapBlocks(1, gMapSelectBgMapBlocks, 1, 2);

                while (node != NULL) {
                    node->flags |= MAPCARD_FLAG_RAISED;
                    node = ListPoolNext(&node->node);
                }

                if (w->kindCount <= 6) {
                    w->lastPage = 0;
                } else {
                    pages = w->kindCount / 6;
                    w->lastPage = pages;
                }

                w->y2 = 0x6400;
                w->y = 0x7A00;
                w->nameY = 0x9100;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapSelectKindInput);
                w->scrollBarVisible = 1;
                return 1;
            }
        } else {
            w->messageTimer++;
        }
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

void RemoveMapSelectCard(MapSelectWork* w) {
    MapcardWork* n;
    s32 v;
    s32 i;

    v = w->openedCardX >> 8;

    for (i = 0; i < 6; i++) {
        if (v == gMapcardSlotX[i]) {
            break;
        }
    }

    n = ListPoolRemove(&w->card->node, &w->cards);
    w->card->flags |= MAPCARD_FLAG_REMOVED;
    w->card = n;

    while (n != NULL) {
        n->args.index--;

        if (i <= 5) {
            n->x = gMapcardSlotX[i] << 8;
            i++;
        }

        n = ListPoolNext(&n->node);
    }

    for (n = ListPoolFirst(&w->cards); n != NULL; n = ListPoolNext(&n->node)) {
        n->flags |= MAPCARD_FLAG_RAISED;
    }

    if (w->card == NULL) {
        w->card = ListPoolLast(&w->cards);

        if (w->card == NULL) {
            w->cursorTargetX = 0x1600;
        } else {
            w->cursorTargetX = w->card->x;
        }
    } else {
        w->cursorTargetX = w->card->x;
    }
}

void Mapcard_0(MapcardWork* w, MapcardArgs* a) {
    w->tiles = NULL;
    w->unk_04 = NULL;
    w->tiles2 = NULL;
    w->palette = NULL;
    w->args = *a;
    w->x = w->args.index <= 5 ? gMapcardSlotX[w->args.index] << 8 : -0x6400;
    w->y = 0x10500;
    w->priority = 50;
    w->deceleration = 0;
    w->speed = 0;
    w->distance = 0;
    w->flags = 0;
    w->angle = 0;
    w->steps = 16;
    w->holdTimer = 0;
    w->scale = 0x100;
    w->unk_71 = 0;
    w->unk_72 = 0;
    w->value = gMapCardDefs[w->args.baseCardId].value;
    w->cardDef = &gMapCardDefs[w->args.baseCardId];
    w->cardBack = &gMapCardBackDefs[w->cardDef->backIndex];
    LinkMapcardNode(w);
    UpdateMapcardRise(w);
    UpdateMapcardGfx(w);
}

s32 func_080948F0(MapcardWork* w, void* a);

u8 Mapcard_1(MapcardWork* w, void* a) {
    if (w->flags & 0xC) {
        w->steps = 12;
        func_08094DEC(w);
        SetTaskUpdate(a, (TaskUpdateFunc)func_080948F0);
    }

    if (w->flags & MAPCARD_FLAG_OPENED) {
        w->angle = 0;
        w->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapcardMoveToFront);
    }

    if (w->flags & MAPCARD_FLAG_CHOSEN) {
        w->angle = 0;
        w->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapcardToCenter);
    }

    if (w->flags & MAPCARD_FLAG_REMOVED) {
        return 0;
    }

    w->angle = 0;
    UpdateMapcardRise(w);
    UpdateMapcardGfx(w);
    return 1;
}

u8 UpdateMapcardMoveToFront(MapcardWork* w, void* a) {
    ApproachValue(&w->x, gMapcardSlotX[0] << 8, w->steps);
    w->steps--;

    if (!(w->flags & MAPCARD_FLAG_OPENED)) {
        w->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapcardMoveBack);
    }

    if (w->flags & MAPCARD_FLAG_CURSOR) {
        w->angle += 8;
    } else {
        w->angle = 0;
    }

    if (w->flags & MAPCARD_FLAG_CHOSEN) {
        w->angle = 0;
        w->steps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapcardToCenter);
    }

    if (w->flags & MAPCARD_FLAG_REMOVED) {
        return 0;
    }

    UpdateMapcardRise(w);
    UpdateMapcardGfx(w);
    return 1;
}

u8 UpdateMapcardMoveBack(MapcardWork* w, void* a) {
    ApproachValue(&w->x, gMapcardSlotX[w->args.index % 6] << 8, w->steps);
    w->steps--;

    if (w->steps == 0) {
        SetTaskUpdate(a, (TaskUpdateFunc)Mapcard_1);
    }

    if (w->flags & MAPCARD_FLAG_CURSOR) {
        w->angle += 8;
    } else {
        w->angle = 0;
    }

    UpdateMapcardRise(w);
    UpdateMapcardGfx(w);
    return 1;
}

s32 func_080948F0(MapcardWork* w, void* a) {
    u8 t;

    t = func_08094E4C(w);
    UpdateMapcardRise(w);
    UpdateMapcardGfx(w);

    if (!t) {
        w->flags &= 0xFFF3;
        SetTaskUpdate(a, (TaskUpdateFunc)Mapcard_1);
    }

    return 1;
}

u8 UpdateMapcardToCenter(MapcardWork* w, void* a) {
    w->angle = 0;
    ApproachValue(&w->x, 0x7800, w->steps);
    ApproachValue(&w->y, 0x3800, w->steps);

    if (w->steps != 0) {
        w->steps--;
    } else {
        w->holdTimer++;

        if (w->holdTimer > 15) {
            AimMapcardAtDoor(w);
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateMapcardFlyToDoor);
        }
    }

    UpdateMapcardGfx(w);
    return 1;
}

void AimMapcardAtDoor(MapcardWork* w) {
    s32 v[2];
    s32 dx;
    s32 dy;
    FldObj* p = GetMapRoomDoor();

    dx = (p->fieldPosition.x >> 8) - (gFieldState->x >> 8);
    dy = (p->fieldPosition.y >> 8) + (p->fieldPosition.z >> 8) - (gFieldState->y >> 8) - 24;
    v[0] = dx * 256 - w->x;
    v[1] = dy * 256 - w->y;
    w->distance = NormalizeVector2D8(&v[0], &v[1]);
    w->dirX = -v[0];
    w->dirY = -v[1];
    w->speed = 0x300;
    w->deceleration = 25;
    w->angle = 0;
    w->scale = 0x100;
}

u8 UpdateMapcardFlyToDoor(MapcardWork* w, void* a) {
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

    if (w->speed < 0) {
        x = (dx << 8) - w->x;
        y = (dy << 8) - w->y;
        NormalizeVector2D8(&x, &y);
        w->dirX = -x;
        w->dirY = -y;
    }

    {
        u8* q = &w->angle;
        u16* scale;

        *q += 24;
        scale = (u16*)(q - (offsetof(MapcardWork, angle) - offsetof(MapcardWork, scale)));
        t = *scale;
        *scale = (s16)t > 25 ? t - 12 : 25;
    }

    w->x += (w->dirX * w->speed) >> 8;
    w->y += (w->dirY * w->speed) >> 8;
    d = VectorLength2D((dx << 8) - w->x, (dy << 8) - w->y);
    w->distance = d;
    w->speed -= w->deceleration;
    w->deceleration += 2;

    if (w->args.parent->isEventDoor != 1) {
        if (d <= 0x7FF) {
            SetMapCardDelivered();
            f = w->flags | MAPCARD_FLAG_DELIVERED;
            w->flags = f;
            SetSelectedMapCard(&gMapCardDefs[w->args.baseCardId + w->value].kind);
        }
    } else {
        if (d <= 0x7FF && w->args.parent->remainingKeys == 0) {
            SetMapCardDelivered();
            f = w->flags | MAPCARD_FLAG_DELIVERED;
            w->flags = f;
            SetSelectedMapCard(&gMapCardDefs[w->args.baseCardId + w->value].kind);
        }
    }

    return 1;
}

void Mapcard_2(MapcardWork* w) {
    ObjAffine* aff;
    u16 y;
    void* sprite;

    if (!IsMessageWindowOpen()) {
        y = (w->y >> 8) + (gSineTable[w->angle] >> 8);

        if (w->flags & MAPCARD_FLAG_GFX_LOADED) {
            if (w->x > 0) {
                if (w->x <= 0xEFFF) {
                    goto draw;
                }
            }

            // fakematch
            do {
                return;
            } while (0);

        draw:
            aff = NULL;

            if (w->flags & MAPCARD_FLAG_CHOSEN) {
                aff = AllocObjAffine(w->angle, (s16)w->scale, (s16)w->scale, 1);
            }

            if (gMapCardDefs[w->args.baseCardId].backIndex == 4) {
                DrawSprite(w->x >> 8, y, gMapCardUiResources.gfx, gMapCardUiResources.tiles, w->palette2, aff, 0,
                           w->priority - 2);
            }

            sprite = w->cardBack->sprites[0];
            DrawSprite(w->x >> 8, y, sprite, w->tiles3, w->palette2, aff, 0, w->priority);
            sprite = w->cardDef->sprites[0];
            DrawSprite(w->x >> 8, y, sprite, w->tiles2, w->palette, aff, 0, w->priority + 1);
        }
    }
}

void Mapcard_3(MapcardWork* w) {
    if (w->flags & MAPCARD_FLAG_GFX_LOADED) {
        ReleaseObjTiles(w->tiles2);
        ReleaseObjPalette(w->palette);
        ReleaseObjTiles(w->tiles3);
        ReleaseObjPalette(w->palette2);
    }
}

u8 IsMapcardOnScreen(MapcardWork* w) {
    if (w->x >= -4096) {
        if (w->x <= 0x10000) {
            if (w->y >= -5120) {
                if (w->y <= 0xC000) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void UpdateMapcardGfx(MapcardWork* w) {
    MapCardDef* a;
    MapCardBackDef* b;
    u16 t;

    if (IsMapcardOnScreen(w)) {
        if (!(w->flags & MAPCARD_FLAG_GFX_LOADED)) {
            a = w->cardDef;
            b = w->cardBack;
            w->tiles2 = LoadObjTiles(a->tiles, a->tilesSize);
            w->palette = LoadObjPalette(a->palette, 32);
            w->tiles3 = LoadObjTiles(b->tiles, b->tilesSize);
            w->palette2 = LoadObjPalette(b->palette, 32);
            w->tiles = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
            FadeSetPaletteExcluded(w->palette->index + 16, 1);
            FadeSetPaletteExcluded(w->palette2->index + 16, 1);
            t = w->flags | MAPCARD_FLAG_GFX_LOADED;
            w->flags = t;
        }
    } else if (w->flags & MAPCARD_FLAG_GFX_LOADED) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjTiles(w->tiles2);
        ReleaseObjPalette(w->palette);
        ReleaseObjTiles(w->tiles3);
        ReleaseObjPalette(w->palette2);
        w->flags &= ~MAPCARD_FLAG_GFX_LOADED;
    }
}

void UpdateMapcardRise(MapcardWork* w) {
    if (w->flags & MAPCARD_FLAG_RAISED) {
        ApproachValue(&w->y, 0x7900, w->steps);
    } else {
        ApproachValue(&w->y, 0x10500, w->steps);
    }

    if (w->steps != 0) {
        w->steps--;
    }
}

void func_08094DEC(MapcardWork* w) {
    if ((w->flags & 4) && w->speed - w->deceleration > 0x8000) {
        w->deceleration += 0x10000;
    }

    if ((w->flags & 8) && w->speed < w->deceleration) {
        w->deceleration -= 0x10000;
    }

    ApproachValue(&w->deceleration, w->speed, w->steps);
    w->steps--;
}

u8 func_08094E4C(MapcardWork* w) {
    ApproachValue(&w->deceleration, w->speed, w->steps);

    if (w->steps != 0) {
        w->steps--;
        return 1;
    }

    return 0;
}

MapcardWork* CreateMapCard(MapcardArgs* args, TaskPool* pool) {
    return TaskCreate(pool, &gTaskDescMapcard, args)->work;
}

void LinkMapcardNode(MapcardWork* w) {
    ListNodeInit(&w->node, w->args.pool, w);
    ListPoolAppend(&w->node, w->args.pool);
}

void Reload_Gage_0(CardDisplayWork* w, CardDisplayArgs* a) {
    ReloadGauge* d;
    ReloadChildArgs args;
    u16 v;
    s8 n;
    s8 i;

    w->tiles = NULL;
    w->tiles2 = NULL;
    w->tiles4 = NULL;
    w->tiles3 = NULL;
    w->tiles5 = NULL;
    w->palette = NULL;
    w->command = 0;
    w->args = *a;
    w->flags = 0;
    w->timer = 16;
    w->ringRadius = 0;
    w->stockIndex = 0;
    w->priority = 4;
    w->ringRadiusTarget = 0x2400;
    w->ringAngleTarget = 0;
    w->ringAngle = 0;
    w->reloadGauge = EwramAlloc(sizeof(ReloadGauge));
    w->phase = 0;
    w->swingSteps = 0;
    d = w->reloadGauge;
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
    w->children = EwramAlloc(sizeof(ListPool));

    switch (w->args.variant) {
    case 1:
        w->ringCenterX = gSoraCardLayout[0][0];
        w->ringCenterY = gSoraCardLayout[0][1];
        w->x = gSoraCardLayout[4][0];
        w->y = gSoraCardLayout[4][1];
        w->swingAngle = w->swingAngleTarget = 0x2000;
        w->flags |= 0x8000000;
        break;
    case 2:
        w->ringCenterX = gRikuCardLayout[0][0];
        w->ringCenterY = gRikuCardLayout[0][1];
        w->x = gRikuCardLayout[4][0];
        w->y = gRikuCardLayout[4][1];
        w->swingAngle = w->swingAngleTarget = -0x2000;
        break;
    }

    w->scaleX = 0x100;
    w->scaleY = 0;
    ListPoolInit(w->children);
    ListNodeInit(&w->node, w->args.pool, w);
    ListPoolAppend(&w->node, w->args.pool);
    w->tiles2 = LoadObjTiles(gReloadCardTiles[w->args.listIndex], 0x280);
    w->tiles3 = AllocObjTiles(0x200, NULL);
    SetObjTileSource(w->tiles3, gReloadCardTiles[1]);
    w->tiles4 = AllocObjTiles(0x80, NULL);
    SetObjTileSource(w->tiles4, gReloadCardTiles[1]);
    InitReloadGageAnims(w->reloadGauge, w, w->args.listIndex);
    w->tiles = LoadObjTiles(gUnk_0905F03C, 0x80);
    w->palette = LoadObjPalette(gBStatesPalette, 32);
    w->tiles5 = AllocObjTiles(0x100, NULL);
    SetObjTileSource(w->tiles5, gReloadCounterTiles[w->args.listIndex]);
    InitReloadGageCounterAnim(w->reloadGauge, w->tiles5, w->args.listIndex, d->reloadCounter);
    w->flags |= (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_OPEN | CARD_DISP_FLAG_RELOAD_GAUGE);

    if (d->reloadCounter >= 0) {
        TaskPoolInit(&w->tasks, d->reloadCounter + 1);
        n = d->reloadCounter;

        if (d->reloadCounter > 3) {
            n = 3;
        }

        for (i = 0; i < n; i++) {
            args.pool = w->children;
            args.index = i;
            args.parentX = &w->x;
            args.parentY = &w->y;
            args.flags = 0;
            args.listIndex = w->args.listIndex;
            args.side = w->args.variant;
            TaskCreate(&w->tasks, &gTaskDescReloadChildren, &args);
        }
    } else {
        TaskPoolInit(&w->tasks, 1);
    }
}

u8 Reload_Gage_1(CardDisplayWork* w, void* a) {
    ReloadChildArgs args;
    ReloadGauge* p;
    ReloadChildWork* node;
    ReloadChildWork* child;
    s32 flags;
    u8 v;

    p = w->reloadGauge;
    v = 0;

    switch (w->args.variant) {
    case 1:
        if (gCardBattleState->soraListIndex == w->args.listIndex) {
            v = gCardBattleState->soraReloadCharging;
            gCardBattleState->soraReloadCharging = 0;
        }

        break;
    case 2:
        if (gCardBattleState->rikuListIndex == w->args.listIndex) {
            v = gCardBattleState->rikuReloadCharging;
            gCardBattleState->rikuReloadCharging = 0;
        }

        break;
    }

    if ((w->flags & (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) == (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) {
        if (v == 1) {
            if ((s8)p->chargeTick == 2) {
                switch (w->args.variant) {
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

                node = ListPoolFirst(w->children);

                while (node != NULL) {
                    node->args.flags &= ~RELOAD_CHILD_FLAG_IDLE;
                    node = ListPoolNext(&node->node);
                }

                if (w->stockIndex == 0) {
                    w->scaleY += 25;

                    if (w->scaleY > 0x100) {
                        w->scaleY = 0x100;
                        w->stockIndex = 1;
                    }
                } else {
                    w->priority += 3;
                    AdvanceReloadGageAnim(w->reloadGauge, w);

                    if (w->priority == 10) {
                        w->priority = 4;
                        w->scaleY = 0;
                        w->stockIndex = 0;
                        child = ListPoolFirst(w->children);

                        while (child != NULL) {
                            child->args.flags |= RELOAD_CHILD_FLAG_SHIFTED;
                            child->args.index--;
                            child = ListPoolNext(&child->node);
                        }

                        p->reloadCounter--;

                        if (p->reloadCounter > 2) {
                            args.pool = w->children;
                            args.index = 3;
                            args.parentX = &w->x;
                            args.parentY = &w->y;
                            args.flags = 0;
                            args.listIndex = w->args.listIndex;
                            args.side = w->args.variant;
                            child = TaskCreate(&w->tasks, &gTaskDescReloadChildren, &args)->work;
                            flags = child->args.flags | RELOAD_CHILD_FLAG_SHIFTED;
                            flags &= 0xFFFD;
                            child->args.flags = flags;
                            child->args.index--;
                        }

                        w->timer = 8;
                        w->phase = 1;
                        ResetReloadGageAnim(w->reloadGauge);
                        m4aSongNumStart(SONG_SYS_CHAGEF1);
                    }
                }

                switch (w->args.variant) {
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

            UpdateReloadGageAnims(w->reloadGauge, w);
            p->chargeTick++;
        } else {
            SetReloadGageIdleFrames(w->reloadGauge, w);
            p->chargeTick = 0;
            w->flags |= 0x8000000;
            m4aSongNumStop(SONG_SYS_CHAGE);

            switch (w->args.variant) {
            case 1:
                gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
                break;
            case 2:
                gRikuBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
                break;
            }

            node = ListPoolFirst(w->children);

            while (node != NULL) {
                node->args.flags |= RELOAD_CHILD_FLAG_IDLE;
                node = ListPoolNext(&node->node);
            }
        }
    }

    if (p->reloadCounter < 0) {
        if ((w->flags & CARD_DISP_FLAG_RELOAD_DONE) == 0) {
            w->flags |= CARD_DISP_FLAG_RELOAD_DONE;
            m4aSongNumStart(SONG_SYS_CHAGEF2);
        }

        if (FadeGetAmount() == 0) {
            FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
        }

        return 0;
    }

    UpdateReloadGageSlide(w->reloadGauge, w);

    if (w->phase == 1 && (s16)w->timer == 1) {
        SetReloadGageCounterAnim(w->reloadGauge, p->reloadCounter);
    }

    UpdateReloadGageRingPosition(w);

    if (w->flags & CARD_DISP_FLAG_REMOVE) {
        return 0;
    }

    StepReloadGageSine(w->reloadGauge);
    w->bobAngle += 4;

    if ((w->flags & CARD_DISP_FLAG_OPEN) == 0) {
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateReloadGageIdle);
        m4aSongNumStop(SONG_SYS_CHAGE);

        switch (w->args.variant) {
        case 1:
            gBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
            break;
        case 2:
            gRikuBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
            break;
        }
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 UpdateReloadGageIdle(CardDisplayWork* w, void* a) {
    if (w->command == 7) {
        return 0;
    }

    w->ringRadius += -w->ringRadius >> 1;
    w->x += (gSoraCardLayout[4][0] - w->x) >> 1;
    w->y += (gSoraCardLayout[4][1] - w->y) >> 1;

    if (w->flags & CARD_DISP_FLAG_OPEN) {
        SetTaskUpdate(a, (TaskUpdateFunc)Reload_Gage_1);
    }

    return 1;
}

void Reload_Gage_2(CardDisplayWork* p) {
    ReloadGauge* q;
    ObjAffine* affine;
    void* gfx;
    s32 t;

    q = p->reloadGauge;
    gfx = gCardBacks[p->args.listIndex].gfx2;
    DrawSprite((p->x >> 8) + (q->offsetX >> 8),
               (p->y >> 8) + (gSineTable[p->bobAngle] >> 8),
               gfx, p->tiles2,
               gCardBattleState->palette, NULL, SPRITE_PRIORITY(1), 50);

    if (p->scaleY > 0) {
        affine = AllocObjAffine(0, 0x100, p->scaleY, 0);
        DrawSprite((p->x >> 8) + (q->offsetX >> 8),
                   (p->y >> 8) + (t = (gSineTable[p->bobAngle] >> 8) + 17),
                   q->gfx, p->tiles3, gCardBattleState->palette, affine,
                   SPRITE_PRIORITY(1), 49);

        if (p->stockIndex == 1) {
            DrawSprite((p->x >> 8) + (q->offsetX >> 8),
                       (p->y >> 8) + (gSineTable[p->bobAngle] >> 8),
                       q->gfx2, p->tiles4, gCardBattleState->palette, NULL,
                       SPRITE_PRIORITY(1), 49);
        }
    }

    if (q->gfx3 != NULL) {
        DrawSprite((p->x >> 8) + (q->offsetX >> 8),
                   (p->y >> 8) + (gSineTable[p->bobAngle] >> 8),
                   q->gfx3, p->tiles5,
                   gCardBattleState->palette, NULL, SPRITE_PRIORITY(1), 48);
    }

    TaskPoolDraw(&p->tasks);
}

void Reload_Gage_3(CardDisplayWork* p) {
    TaskPoolDestroy(&p->tasks);
    ReleaseObjPalette(p->palette);
    ReleaseObjTiles(p->tiles);
    ReleaseObjTiles(p->tiles2);
    ReleaseObjTiles(p->tiles3);
    ReleaseObjTiles(p->tiles4);
    ReleaseObjTiles(p->tiles5);
    EwramFree(p->children);
    EwramFree(p->reloadGauge);

    switch (p->args.variant) {
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

    ListPoolRemove(&p->node, p->args.pool);
}

void UpdateReloadGageRingPosition(CardDisplayWork* w) {
    ApproachValue(&w->swingAngle, w->swingAngleTarget, w->swingSteps);

    if (w->swingSteps != 0) {
        w->swingSteps--;
    }

    w->ringRadius += (w->ringRadiusTarget - w->ringRadius) >> 1;

    if ((s16)w->timer > 0) {
        w->timer--;
        w->flags &= ~CARD_DISP_FLAG_SETTLED;
    } else {
        w->timer = 0;
        w->flags |= CARD_DISP_FLAG_SETTLED;
    }

    switch (w->args.variant) {
    case 1:
        w->ringCenterX = gSineTable[(w->swingAngle >> 8) & 0xFF] * 80 + gSoraCardLayout[0][0];
        w->ringCenterY = -gSineTable[((w->swingAngle >> 8) & 0xFF) + 0x40] * 80 + gSoraCardLayout[0][1];
        w->x = gSineTable[0x20] * (w->ringRadius >> 8) + w->ringCenterX;
        w->y = -gSineTable[0x60] * (w->ringRadius >> 8) + w->ringCenterY;
        break;
    case 2:
        w->ringCenterX = gSineTable[(w->swingAngle >> 8) & 0xFF] * 80 + gRikuCardLayout[0][0];
        w->ringCenterY = -gSineTable[((w->swingAngle >> 8) & 0xFF) + 0x40] * 80 + gRikuCardLayout[0][1];
        w->x = gSineTable[0xE0] * (w->ringRadius >> 8) + w->ringCenterX;
        w->y = -gSineTable[0x120] * (w->ringRadius >> 8) + w->ringCenterY;
        break;
    }
}

void StepReloadGageSine(ReloadGauge* p) {
    p->unk_00 = gSineTable[(u8)p->angle] >> 8;
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

s32 UpdateReloadGageSlide(ReloadGauge* p, CardDisplayWork* w) {
    if ((s16)w->timer > 0 && w->phase == 1) {
        switch (w->args.variant) {
        case 1:
            ApproachValue(&p->offsetX, -0x3000, w->timer);
            break;
        case 2:
            ApproachValue(&p->offsetX, 0x12000, w->timer);
            break;
        }
    } else {
        p->offsetX = 0;
    }
}

void InitReloadGageAnims(ReloadGauge* p, CardDisplayWork* w, u8 idx) {
    p->gaugeAnim = 2;
    AnimInit(&p->anim2, gReloadGaugeAnims[idx], gReloadGaugeFrames[idx]);
    AnimStart(&p->anim2, 1, ANIM_FLAG_LOOP);
    p->gfx = gReloadGaugeFrames[idx][3];
    AnimInit(&p->anim3, gReloadGaugeAnims[idx], gReloadGaugeFrames[idx]);
    AnimStart(&p->anim3, 2, ANIM_FLAG_LOOP);
    p->gfx2 = gReloadGaugeFrames[idx][6];
}

void UpdateReloadGageAnims(ReloadGauge* p, CardDisplayWork* w) {
    p->gfx = AnimUpdate(&p->anim2);
    p->gfx2 = AnimUpdate(&p->anim3);
}

void SetReloadGageIdleFrames(ReloadGauge* p, CardDisplayWork* w) {
    p->gfx = gReloadGaugeFrames[w->args.listIndex][3];
    p->gfx2 = gReloadGaugeFrames[w->args.listIndex][w->priority + 2];
}

void AdvanceReloadGageAnim(ReloadGauge* p, CardDisplayWork* w) {
    if (p->gaugeAnim <= 3) {
        p->gaugeAnim++;
    }

    AnimStart(&p->anim3, p->gaugeAnim, ANIM_FLAG_LOOP | ANIM_FLAG_KEEP_FRAME);
}

void ResetReloadGageAnim(ReloadGauge* p) {
    p->gaugeAnim = 2;
}

void* CreateReloadGageTask(CardBattleWork* w, u16 b, void* pool, u8 mode) {
    CardDisplayArgs args;

    args.pool = &w->cardDisplays[w->listIndex];
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
    args.listIndex = w->listIndex;
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
    gUnk_08125E24, gUnk_096102B8,
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
    { gUnk_093F61B2, gUnk_09618D78, gUnk_09EF11E8, gUnk_0905E3BA, gUnk_09EE97F4, 640, 32, 640, { 0, 0 } },
    { gUnk_093F5C7A, gUnk_09618D78, gUnk_09EF11D8, gUnk_0905C862, gUnk_09EE9764, 640, 32, 640, { 0, 0 } },
    { gUnk_093F5F16, gUnk_09618D78, gUnk_09EF11E0, gUnk_0905D64E, gUnk_09EE97AC, 640, 32, 640, { 0, 0 } },
    { gUnk_093F61B2, gUnk_09618D78, gUnk_09EF11E8, gUnk_0905AC8A, gUnk_09EE96D4, 640, 32, 640, { 0, 0 } },
    { gUnk_093F644E, gUnk_09618D78, gUnk_09EF11F0, gUnk_0905E3BA, gUnk_09EE97F4, 640, 32, 640, { 0, 0 } },
};

MapCardDef gMapCardDefs[260] = {
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 0, 1, 0, 2, 0 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 0, 1, 1, 2, 0 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 0, 1, 2, 2, 0 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 0, 1, 3, 2, 0 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 0, 1, 4, 2, 0 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 0, 1, 5, 2, 0 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 0, 1, 6, 2, 0 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 0, 1, 7, 2, 0 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 0, 1, 8, 2, 0 },
    { gCardRoom02Tiles, gCardRoom02Palette, gCardRoom02Frames, gUnk_093F2148, gUnk_09618898, gUnk_09EF1068, 512, 32, 256, 2, 0, 1, 9, 2, 0 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 0, 0, 2, 0 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 0, 1, 2, 0 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 0, 2, 2, 0 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 0, 3, 2, 0 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 0, 4, 2, 0 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 0, 5, 2, 0 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 0, 6, 2, 0 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 0, 7, 2, 0 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 0, 8, 2, 0 },
    { gCardRoom01Tiles, gCardRoom01Palette, gCardRoom01Frames, gUnk_093F2034, gUnk_09618878, gUnk_09EF1060, 512, 32, 256, 2, 0, 0, 9, 2, 0 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 0, 6, 0, 2, 0 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 0, 6, 1, 2, 0 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 0, 6, 2, 2, 0 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 0, 6, 3, 2, 0 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 0, 6, 4, 2, 0 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 0, 6, 5, 2, 0 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 0, 6, 6, 2, 0 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 0, 6, 7, 2, 0 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 0, 6, 8, 2, 0 },
    { gCardRoom07Tiles, gCardRoom07Palette, gCardRoom07Frames, gUnk_093F26AC, gUnk_09618938, gUnk_09EF1090, 512, 32, 256, 2, 0, 6, 9, 2, 0 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 0, 7, 0, 2, 0 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 0, 7, 1, 2, 0 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 0, 7, 2, 2, 0 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 0, 7, 3, 2, 0 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 0, 7, 4, 2, 0 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 0, 7, 5, 2, 0 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 0, 7, 6, 2, 0 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 0, 7, 7, 2, 0 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 0, 7, 8, 2, 0 },
    { gCardRoom08Tiles, gCardRoom08Palette, gCardRoom08Frames, gUnk_093F27C0, gUnk_09618958, gUnk_09EF1098, 512, 32, 256, 2, 0, 7, 9, 2, 0 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 0, 4, 0, 2, 0 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 0, 4, 1, 2, 0 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 0, 4, 2, 2, 0 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 0, 4, 3, 2, 0 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 0, 4, 4, 2, 0 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 0, 4, 5, 2, 0 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 0, 4, 6, 2, 0 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 0, 4, 7, 2, 0 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 0, 4, 8, 2, 0 },
    { gCardRoom05Tiles, gCardRoom05Palette, gCardRoom05Frames, gUnk_093F2484, gUnk_096188F8, gUnk_09EF1080, 512, 32, 256, 2, 0, 4, 9, 2, 0 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 0, 3, 0, 2, 0 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 0, 3, 1, 2, 0 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 0, 3, 2, 2, 0 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 0, 3, 3, 2, 0 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 0, 3, 4, 2, 0 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 0, 3, 5, 2, 0 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 0, 3, 6, 2, 0 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 0, 3, 7, 2, 0 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 0, 3, 8, 2, 0 },
    { gCardRoom04Tiles, gCardRoom04Palette, gCardRoom04Frames, gUnk_093F2370, gUnk_096188D8, gUnk_09EF1078, 512, 32, 256, 2, 0, 3, 9, 2, 0 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 0, 19, 0, 2, 0 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 0, 19, 1, 2, 0 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 0, 19, 2, 2, 0 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 0, 19, 3, 2, 0 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 0, 19, 4, 2, 0 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 0, 19, 5, 2, 0 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 0, 19, 6, 2, 0 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 0, 19, 7, 2, 0 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 0, 19, 8, 2, 0 },
    { gCardRoom20Tiles, gCardRoom20Palette, gCardRoom20Frames, gUnk_093F34B0, gUnk_09618AD8, gUnk_09EF10F8, 512, 32, 256, 2, 0, 19, 9, 2, 0 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 0, 20, 0, 2, 0 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 0, 20, 1, 2, 0 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 0, 20, 2, 2, 0 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 0, 20, 3, 2, 0 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 0, 20, 4, 2, 0 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 0, 20, 5, 2, 0 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 0, 20, 6, 2, 0 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 0, 20, 7, 2, 0 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 0, 20, 8, 2, 0 },
    { gCardRoom21Tiles, gCardRoom21Palette, gCardRoom21Frames, gUnk_093F35C4, gUnk_09618AF8, gUnk_09EF1100, 512, 32, 256, 2, 0, 20, 9, 2, 0 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 0, 21, 0, 2, 0 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 0, 21, 1, 2, 0 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 0, 21, 2, 2, 0 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 0, 21, 3, 2, 0 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 0, 21, 4, 2, 0 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 0, 21, 5, 2, 0 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 0, 21, 6, 2, 0 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 0, 21, 7, 2, 0 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 0, 21, 8, 2, 0 },
    { gCardRoom22Tiles, gCardRoom22Palette, gCardRoom22Frames, gUnk_093F36D8, gUnk_09618B18, gUnk_09EF1108, 512, 32, 256, 2, 0, 21, 9, 2, 0 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 0, 12, 0, 1, 0 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 0, 12, 1, 1, 0 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 0, 12, 2, 1, 0 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 0, 12, 3, 1, 0 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 0, 12, 4, 1, 0 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 0, 12, 5, 1, 0 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 0, 12, 6, 1, 0 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 0, 12, 7, 1, 0 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 0, 12, 8, 1, 0 },
    { gCardRoom13Tiles, gCardRoom13Palette, gCardRoom13Frames, gUnk_093F2D24, gUnk_096189F8, gUnk_09EF10C0, 512, 32, 256, 1, 0, 12, 9, 1, 0 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 0, 11, 0, 1, 0 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 0, 11, 1, 1, 0 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 0, 11, 2, 1, 0 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 0, 11, 3, 1, 0 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 0, 11, 4, 1, 0 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 0, 11, 5, 1, 0 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 0, 11, 6, 1, 0 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 0, 11, 7, 1, 0 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 0, 11, 8, 1, 0 },
    { gCardRoom12Tiles, gCardRoom12Palette, gCardRoom12Frames, gUnk_093F2C10, gUnk_096189D8, gUnk_09EF10B8, 512, 32, 256, 1, 0, 11, 9, 1, 0 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 0, 13, 0, 1, 0 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 0, 13, 1, 1, 0 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 0, 13, 2, 1, 0 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 0, 13, 3, 1, 0 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 0, 13, 4, 1, 0 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 0, 13, 5, 1, 0 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 0, 13, 6, 1, 0 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 0, 13, 7, 1, 0 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 0, 13, 8, 1, 0 },
    { gCardRoom14Tiles, gCardRoom14Palette, gCardRoom14Frames, gUnk_093F2E38, gUnk_09618A18, gUnk_09EF10C8, 512, 32, 256, 1, 0, 13, 9, 1, 0 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 0, 14, 0, 1, 0 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 0, 14, 1, 1, 0 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 0, 14, 2, 1, 0 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 0, 14, 3, 1, 0 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 0, 14, 4, 1, 0 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 0, 14, 5, 1, 0 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 0, 14, 6, 1, 0 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 0, 14, 7, 1, 0 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 0, 14, 8, 1, 0 },
    { gCardRoom15Tiles, gCardRoom15Palette, gCardRoom15Frames, gUnk_093F2F4C, gUnk_09618A38, gUnk_09EF10D0, 512, 32, 256, 1, 0, 14, 9, 1, 0 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 0, 18, 0, 1, 0 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 0, 18, 1, 1, 0 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 0, 18, 2, 1, 0 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 0, 18, 3, 1, 0 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 0, 18, 4, 1, 0 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 0, 18, 5, 1, 0 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 0, 18, 6, 1, 0 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 0, 18, 7, 1, 0 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 0, 18, 8, 1, 0 },
    { gCardRoom19Tiles, gCardRoom19Palette, gCardRoom19Frames, gUnk_093F339C, gUnk_09618AB8, gUnk_09EF10F0, 512, 32, 256, 1, 0, 18, 9, 1, 0 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 0, 16, 0, 1, 0 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 0, 16, 1, 1, 0 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 0, 16, 2, 1, 0 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 0, 16, 3, 1, 0 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 0, 16, 4, 1, 0 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 0, 16, 5, 1, 0 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 0, 16, 6, 1, 0 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 0, 16, 7, 1, 0 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 0, 16, 8, 1, 0 },
    { gCardRoom17Tiles, gCardRoom17Palette, gCardRoom17Frames, gUnk_093F3174, gUnk_09618A78, gUnk_09EF10E0, 512, 32, 256, 1, 0, 16, 9, 1, 0 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 0, 17, 0, 1, 0 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 0, 17, 1, 1, 0 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 0, 17, 2, 1, 0 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 0, 17, 3, 1, 0 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 0, 17, 4, 1, 0 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 0, 17, 5, 1, 0 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 0, 17, 6, 1, 0 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 0, 17, 7, 1, 0 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 0, 17, 8, 1, 0 },
    { gCardRoom18Tiles, gCardRoom18Palette, gCardRoom18Frames, gUnk_093F3288, gUnk_09618A98, gUnk_09EF10E8, 512, 32, 256, 1, 0, 17, 9, 1, 0 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 0, 8, 0, 3, 0 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 0, 8, 1, 3, 0 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 0, 8, 2, 3, 0 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 0, 8, 3, 3, 0 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 0, 8, 4, 3, 0 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 0, 8, 5, 3, 0 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 0, 8, 6, 3, 0 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 0, 8, 7, 3, 0 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 0, 8, 8, 3, 0 },
    { gCardRoom09Tiles, gCardRoom09Palette, gCardRoom09Frames, gUnk_093F28D4, gUnk_09618978, gUnk_09EF10A0, 512, 32, 256, 3, 0, 8, 9, 3, 0 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 0, 2, 0, 3, 0 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 0, 2, 1, 3, 0 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 0, 2, 2, 3, 0 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 0, 2, 3, 3, 0 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 0, 2, 4, 3, 0 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 0, 2, 5, 3, 0 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 0, 2, 6, 3, 0 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 0, 2, 7, 3, 0 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 0, 2, 8, 3, 0 },
    { gCardRoom03Tiles, gCardRoom03Palette, gCardRoom03Frames, gUnk_093F225C, gUnk_096188B8, gUnk_09EF1070, 512, 32, 256, 3, 0, 2, 9, 3, 0 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 0, 9, 0, 3, 0 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 0, 9, 1, 3, 0 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 0, 9, 2, 3, 0 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 0, 9, 3, 3, 0 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 0, 9, 4, 3, 0 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 0, 9, 5, 3, 0 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 0, 9, 6, 3, 0 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 0, 9, 7, 3, 0 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 0, 9, 8, 3, 0 },
    { gCardRoom10Tiles, gCardRoom10Palette, gCardRoom10Frames, gUnk_093F29E8, gUnk_09618998, gUnk_09EF10A8, 512, 32, 256, 3, 0, 9, 9, 3, 0 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 0, 5, 0, 3, 0 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 0, 5, 1, 3, 0 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 0, 5, 2, 3, 0 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 0, 5, 3, 3, 0 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 0, 5, 4, 3, 0 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 0, 5, 5, 3, 0 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 0, 5, 6, 3, 0 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 0, 5, 7, 3, 0 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 0, 5, 8, 3, 0 },
    { gCardRoom06Tiles, gCardRoom06Palette, gCardRoom06Frames, gUnk_093F2598, gUnk_09618918, gUnk_09EF1088, 512, 32, 256, 3, 0, 5, 9, 3, 0 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 0, 15, 0, 3, 0 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 0, 15, 1, 3, 0 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 0, 15, 2, 3, 0 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 0, 15, 3, 3, 0 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 0, 15, 4, 3, 0 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 0, 15, 5, 3, 0 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 0, 15, 6, 3, 0 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 0, 15, 7, 3, 0 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 0, 15, 8, 3, 0 },
    { gCardRoom16Tiles, gCardRoom16Palette, gCardRoom16Frames, gUnk_093F3060, gUnk_09618A58, gUnk_09EF10D8, 512, 32, 256, 3, 0, 15, 9, 3, 0 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 0, 10, 0, 3, 0 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 0, 10, 1, 3, 0 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 0, 10, 2, 3, 0 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 0, 10, 3, 3, 0 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 0, 10, 4, 3, 0 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 0, 10, 5, 3, 0 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 0, 10, 6, 3, 0 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 0, 10, 7, 3, 0 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 0, 10, 8, 3, 0 },
    { gCardRoom11Tiles, gCardRoom11Palette, gCardRoom11Frames, gUnk_093F2AFC, gUnk_096189B8, gUnk_09EF10B0, 512, 32, 256, 3, 0, 10, 9, 3, 0 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 0, 22, 0, 4, 0 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 0, 22, 1, 4, 0 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 0, 22, 2, 4, 0 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 0, 22, 3, 4, 0 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 0, 22, 4, 4, 0 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 0, 22, 5, 4, 0 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 0, 22, 6, 4, 0 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 0, 22, 7, 4, 0 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 0, 22, 8, 4, 0 },
    { gCardEve00Tiles, gCardEve00Palette, gCardEve00Frames, gUnk_093F3900, gUnk_09618B58, gUnk_09EF1118, 512, 32, 256, 4, 0, 22, 9, 4, 0 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 0, 23, 0, 4, 0 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 0, 23, 1, 4, 0 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 0, 23, 2, 4, 0 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 0, 23, 3, 4, 0 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 0, 23, 4, 4, 0 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 0, 23, 5, 4, 0 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 0, 23, 6, 4, 0 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 0, 23, 7, 4, 0 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 0, 23, 8, 4, 0 },
    { gCardEve01Tiles, gCardEve01Palette, gCardEve01Frames, gUnk_093F3A14, gUnk_09618B78, gUnk_09EF1120, 512, 32, 256, 4, 0, 23, 9, 4, 0 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 0, 24, 0, 4, 0 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 0, 24, 1, 4, 0 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 0, 24, 2, 4, 0 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 0, 24, 3, 4, 0 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 0, 24, 4, 4, 0 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 0, 24, 5, 4, 0 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 0, 24, 6, 4, 0 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 0, 24, 7, 4, 0 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 0, 24, 8, 4, 0 },
    { gCardEve02Tiles, gCardEve02Palette, gCardEve02Frames, gUnk_093F3B28, gUnk_09618B98, gUnk_09EF1128, 512, 32, 256, 4, 0, 24, 9, 4, 0 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 0, 25, 0, 4, 0 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 0, 25, 1, 4, 0 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 0, 25, 2, 4, 0 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 0, 25, 3, 4, 0 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 0, 25, 4, 4, 0 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 0, 25, 5, 4, 0 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 0, 25, 6, 4, 0 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 0, 25, 7, 4, 0 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 0, 25, 8, 4, 0 },
    { gCardRoom23Tiles, gCardRoom23Palette, gCardRoom23Frames, gUnk_093F37EC, gUnk_09618B38, gUnk_09EF1110, 512, 32, 256, 4, 0, 25, 9, 4, 0 },
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
