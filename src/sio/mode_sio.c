/**
 * mode_sio.c
 * Link Battle and Card Trade Modes
 */

#include "macros.h"
#include "mode_sio_dbg.h"
#include "mode_chkobj_assets.h"
#include "registration_data.h"
#include "system_state.h"
#include "chara_api.h"
#include "msg_api.h"
#include "m4a_song.h"
#include "pallet.h"
#include "sio_api.h"
#include "display.h"
#include "text.h"
#include "monsgage.h"
#include "mode_sio.h"
#include "gba/keys.h"
#include "jiminy_data.h"
#include "sprites_boss_tm.h"
#include "sprites_evt.h"
#include "sprites_fld.h"
#include "sprites_sora.h"
#include "battle_backgrounds.h"
#include "sprites_msg.h"
#include "link_menus.h"
#include "sprites_card_pictures.h"
#include "sprites_card.h"
#include "card_ids.h"
#include "malloc.h"
#include "fade.h"
#include "card_deck.h"
#include "songs.h"
#include "common_text.h"
#include "anim.h"
#include "card.h"
#include "card_api.h"
#include "card_def_data.h"
#include "card_types.h"
#include "chara_types.h"
#include "engine_math.h"
#include "game_state.h"
#include "gba/defines.h"
#include "jiminy_inline_text_data.h"
#include "key.h"
#include "mode.h"
#include "mode_sio_api.h"
#include "obj.h"
#include "obj_api.h"
#include "player_progression_types.h"
#include "save_api.h"
#include "taskpool.h"
#include "text_types.h"
#include "types.h"
#include <stddef.h>

s8 gSioDebugMode EWRAM_COMMON(4);

u8 gSioBattleFileLoaded EWRAM_COMMON(4);

u16 gSioWinCount EWRAM_COMMON(4);
u16 gSioLoseCount EWRAM_COMMON(4);
s8 gSioWorldCursor EWRAM_COMMON(16);
CharaLinkData gCharaLinkRecv EWRAM_COMMON(16);
u8 gSioDeckNames[2][20] EWRAM_COMMON(16);
u8 gSioHandicaps[2] EWRAM_COMMON(4);
u8 gSioDeckNameRecv[2][20] EWRAM_COMMON(16);
u8 gSioWorldCount EWRAM_COMMON(4);
s8 gSioDeckNameChunk EWRAM_COMMON(4);
s8 gSioPrevWorldCursor EWRAM_COMMON(4);
s8 gSioWorldList[14] EWRAM_COMMON(16);
u8 gSioSavedWorld EWRAM_COMMON(4);
CharaLinkData gCharaLinkSend EWRAM_COMMON(16);
u8 gSioDeckNameRecvBuf[2][20] EWRAM_COMMON(16);
#ifdef VERSION_EU
s8 gSioDebugReady[2] EWRAM_COMMON(4);
#endif

#ifndef VERSION_EU
s8 gSioChgCardCursor EWRAM_COMMON(16);
u16 gSioChgCardSlots[10] EWRAM_COMMON(16);
s8 gSioChgCardReady[2] EWRAM_COMMON(4);
#endif

Mode gModeSioBattle = {
    "mode_sio_battle",
    mode_sio_battle_0,
    mode_sio_battle_1,
    mode_sio_battle_2,
};

Mode gModeSioBtlConnect = {
    "mode_sio_btl_connect",
    mode_sio_btl_connect_0,
    mode_sio_btl_connect_1,
    mode_sio_btl_connect_2,
};

static const SioAnimDef sSioBtlOptionAnimDefs[2] = {
    {gSor1fl00Frames, gSor1fl00Anims, gSor1fl00Tiles, 0},
    {gSor1ll51Frames, gSor1ll51Anims, gSor1ll51Tiles, 0},
};

#ifndef VERSION_EU
extern const SioAnimDef gSioChgCardAnimDefs[3];
#endif
#ifdef VERSION_EU
#include "link_deck_names.inc"
#endif
#ifdef VERSION_EU
#endif
extern SioWorldEntry gSioWorldEntries[];
extern s8 gSioHandicapMarkerX[];
extern u16 gSioHandicapAp[];
#ifndef VERSION_EU
extern SioChgCardPos gSioChgCardSlotPos[];
#endif

static SioBattleWork* sSioBattleWork;
static SioBtlConnectWork* sSioBtlConnectWork;
static SioBtlOptionWork* sSioBtlOptionWork;
static SioBtlCardgetWork* sSioBtlCardgetWork;
#ifndef VERSION_EU
static SioBtlConnectWork* sSioChgConnectWork;
static SioChgCardWork* sSioChgCardWork;
#endif
static SioErrorWork* sSioErrorWork;

void mode_sio_battle_0(s32 a) {
    SioBattleWork* w;
    void* gfx;
    s32 i;

    sSioBattleWork = EwramAlloc(sizeof(SioBattleWork));
    FadeStartIn(FADE_MODE_BLACK, 16);
    SetBgMode0();
    SetupBg(0, 0, 7, 0);
    SetupBg(1, 0, 31, 0);
    LoadBgTiles(1, gUnk_096ACA44, 0xBC0);
    LoadBgPalette(1, gUnk_096FBA04, 64);
    LoadBgMap(1, gUnk_096F5464, 0x800);
    EnableBg(1);
    sSioBattleWork->state = 0;
    sSioBattleWork->slideTimer = 0;
    sSioBattleWork->stateFrames = 0;
    sSioBattleWork->x = -0x8000;
    sSioBattleWork->y = -0x800;
    sSioBattleWork->y2 = 0xA000;
    sSioBattleWork->tiles = LoadObjTiles(gUnk_0962AD62, 0x240);
    sSioBattleWork->palette = LoadObjPalette(gUnk_096FBA44, 32);

    for (i = 0; i < 3; i++) {
        sSioBattleWork->gfx2[i] = gUnk_09EF3884[i];
    }

#ifdef VERSION_EU
    sSioBattleWork->palette2 = LoadObjPalette(gUnk_096FBA64, 32);
    sSioBattleWork->palette3 = LoadObjPalette(gUnk_096FBA84, 32);

    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        sSioBattleWork->tiles2 = LoadObjTiles(gUnkEu_095EDAAA, 0x600);
        sSioBattleWork->tiles3 = LoadObjTiles(gUnkEu_095EE0E2, 0x600);
        break;
    case LANGUAGE_ITALIAN:
        sSioBattleWork->tiles2 = LoadObjTiles(gUnkEu_095EFFFA, 0x600);
        sSioBattleWork->tiles3 = LoadObjTiles(gUnkEu_095F0632, 0x600);
        break;
    case LANGUAGE_FRENCH:
        sSioBattleWork->tiles2 = LoadObjTiles(gUnkEu_095EE71A, 0x600);
        sSioBattleWork->tiles3 = LoadObjTiles(gUnkEu_095EED52, 0x600);
        break;
    case LANGUAGE_SPANISH:
        sSioBattleWork->tiles2 = LoadObjTiles(gUnkEu_095EF38A, 0x600);
        sSioBattleWork->tiles3 = LoadObjTiles(gUnkEu_095EF9C2, 0x600);
        break;
    case LANGUAGE_GERMAN:
    default:
        sSioBattleWork->tiles2 = LoadObjTiles(gUnkEu_095F0C6A, 0x600);
        sSioBattleWork->tiles3 = LoadObjTiles(gUnkEu_095F12A2, 0x600);
        break;
    }
#else
    sSioBattleWork->tiles2 = LoadObjTiles(gUnk_0962B286, 0x600);
    sSioBattleWork->palette2 = LoadObjPalette(gUnk_096FBA64, 32);
    sSioBattleWork->tiles3 = LoadObjTiles(gUnk_0962B8BE, 0x600);
    sSioBattleWork->palette3 = LoadObjPalette(gUnk_096FBA84, 32);
#endif
    sSioBattleWork->tiles4 = LoadObjTiles(gUnk_0962B090, 0x1C0);
    sSioBattleWork->palette4 = LoadObjPalette(gUnk_096FBAA4, 32);
    AnimInit(&sSioBattleWork->anim, gUnk_09EF38B4, gUnk_09EF3894);
    AnimStart(&sSioBattleWork->anim, 1, ANIM_FLAG_LOOP);
    gfx = AnimGetGfx(&sSioBattleWork->anim);
    w = sSioBattleWork;
    w->gfx = gfx;
    w->modeArg = a;

    switch (w->modeArg) {
    case 0:
    case 1:
        if (w->modeArg == 0) {
            if (gSioBattleFileLoaded != 1) {
                gSioBattleFileLoaded = 0;
                w->cursor = 1;
            } else {
                gSioBattleFileLoaded = 1;
                w->cursor = 0;
            }
        } else {
            gSioBattleFileLoaded = 1;
            w->cursor = 0;
        }

#ifdef VERSION_EU
        sSioBattleWork->cursorY = sSioBattleWork->cursor * 0x1C00 + 0x3300;

        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB38[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB44[sSioBattleWork->cursor];
            break;
        case LANGUAGE_ITALIAN:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB80[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB8C[sSioBattleWork->cursor];
            break;
        case LANGUAGE_FRENCH:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB50[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB5C[sSioBattleWork->cursor];
            break;
        case LANGUAGE_SPANISH:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB68[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB74[sSioBattleWork->cursor];
            break;
        case LANGUAGE_GERMAN:
        default:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB98[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EBA4[sSioBattleWork->cursor];
            break;
        }
#else
        sSioBattleWork->gfx3 = gUnk_09EF38BC[sSioBattleWork->cursor];
        sSioBattleWork->gfx4 = gUnk_09EF38C8[sSioBattleWork->cursor];
        sSioBattleWork->cursorY = sSioBattleWork->cursor * 0x1C00 + 0x3300;
#endif
        break;
    case 2:
#ifdef VERSION_EU
        sSioBattleWork->cursorY = sSioBattleWork->cursor * 0x1C00 + 0x3300;
        gSioBattleFileLoaded = 1;
        w->cursor = 0;

        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB38[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB44[sSioBattleWork->cursor];
            break;
        case LANGUAGE_ITALIAN:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB80[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB8C[sSioBattleWork->cursor];
            break;
        case LANGUAGE_FRENCH:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB50[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB5C[sSioBattleWork->cursor];
            break;
        case LANGUAGE_SPANISH:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB68[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB74[sSioBattleWork->cursor];
            break;
        case LANGUAGE_GERMAN:
        default:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB98[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EBA4[sSioBattleWork->cursor];
            break;
        }
#else
        w->cursor = 0;
        sSioBattleWork->gfx3 = gUnk_09EF38BC[sSioBattleWork->cursor];
        sSioBattleWork->gfx4 = gUnk_09EF38C8[sSioBattleWork->cursor];
        sSioBattleWork->cursorY = sSioBattleWork->cursor * 0x1C00 + 0x3300;
        gSioBattleFileLoaded = 1;
#endif
        break;
    case 3:
        w->cursor = 0;
#ifdef VERSION_EU
        sSioBattleWork->cursorY = sSioBattleWork->cursor * 0x1C00 + 0x3300;
        gSioBattleFileLoaded = 1;

        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB38[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB44[sSioBattleWork->cursor];
            break;
        case LANGUAGE_ITALIAN:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB80[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB8C[sSioBattleWork->cursor];
            break;
        case LANGUAGE_FRENCH:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB50[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB5C[sSioBattleWork->cursor];
            break;
        case LANGUAGE_SPANISH:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB68[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB74[sSioBattleWork->cursor];
            break;
        case LANGUAGE_GERMAN:
        default:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB98[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EBA4[sSioBattleWork->cursor];
            break;
        }
#else
        sSioBattleWork->gfx3 = gUnk_09EF38BC[sSioBattleWork->cursor];
        sSioBattleWork->gfx4 = gUnk_09EF38C8[sSioBattleWork->cursor];
        sSioBattleWork->cursorY = sSioBattleWork->cursor * 0x1C00 + 0x3300;
        gSioBattleFileLoaded = 1;
#endif
        break;
    case 0xFFFF:
        break;
    }

    gLinkDecksAllocated = 0;
    gSioDebugMode = 0;
}

void mode_sio_battle_1() {
    switch ((s8)sSioBattleWork->state) {
    case 0:
        if ((s16)sSioBattleWork->stateFrames == 0) {
            sSioBattleWork->slideTimer = 16;
        }

        ApproachValue(&sSioBattleWork->y, 0, sSioBattleWork->slideTimer);
        ApproachValue(&sSioBattleWork->y2, 0x9800, sSioBattleWork->slideTimer);
        sSioBattleWork->slideTimer--;

        if ((s16)sSioBattleWork->slideTimer > 0) {
            sSioBattleWork->stateFrames++;
        } else {
            sSioBattleWork->state = 1;
            sSioBattleWork->stateFrames = 0;
        }

        break;
    case 1:
        if ((s16)sSioBattleWork->stateFrames == 0) {
            sSioBattleWork->slideTimer = 16;
        }

        ApproachValue(&sSioBattleWork->x, 0, sSioBattleWork->slideTimer);
        sSioBattleWork->slideTimer--;

        if ((s16)sSioBattleWork->slideTimer > 0) {
            sSioBattleWork->stateFrames++;
        } else {
            sSioBattleWork->state = 5;
            sSioBattleWork->stateFrames = 0;
        }

        break;
    case 5:
        sSioBattleWork->state = 6;
        break;
    case 6:
        if (gSioBattleFileLoaded == 1) {
            if (GetKeysPressed() & DPAD_UP) {
                m4aSongNumStart(SONG_SYS_CLICK);
                sSioBattleWork->cursor--;

                if (sSioBattleWork->cursor < 0) {
                    sSioBattleWork->cursor = 1;
                }
            }

            if (GetKeysPressed() & DPAD_DOWN) {
                m4aSongNumStart(SONG_SYS_CLICK);
                sSioBattleWork->cursor++;

                if (sSioBattleWork->cursor > 1) {
                    sSioBattleWork->cursor = 0;
                }
            }
        } else {
            if (GetKeysPressed() & (DPAD_UP | DPAD_DOWN)) {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        }

#ifdef VERSION_EU
        switch (gLanguage) {
        case LANGUAGE_ENGLISH:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB38[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB44[sSioBattleWork->cursor];
            break;
        case LANGUAGE_ITALIAN:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB80[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB8C[sSioBattleWork->cursor];
            break;
        case LANGUAGE_FRENCH:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB50[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB5C[sSioBattleWork->cursor];
            break;
        case LANGUAGE_SPANISH:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB68[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EB74[sSioBattleWork->cursor];
            break;
        case LANGUAGE_GERMAN:
        default:
            sSioBattleWork->gfx3 = gUnkEu_09F7EB98[sSioBattleWork->cursor];
            sSioBattleWork->gfx4 = gUnkEu_09F7EBA4[sSioBattleWork->cursor];
            break;
        }
#else
        sSioBattleWork->gfx3 = gUnk_09EF38BC[sSioBattleWork->cursor];
        sSioBattleWork->gfx4 = gUnk_09EF38C8[sSioBattleWork->cursor];
#endif

        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            m4aSongNumStart(SONG_SYS_KETTEI);

            switch (sSioBattleWork->cursor) {
            case 0:
                ModeRequest(&gModeSioBtlConnect, 0);
                break;
            case 1:
                ModeRequest(&gModeMenuLoad, 1);
                break;
            }
        }

        if (GetKeysPressed() & B_BUTTON) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            sSioBattleWork->state = 2;
        }

        break;
    case 2:
        if ((s16)sSioBattleWork->stateFrames == 0) {
            sSioBattleWork->slideTimer = 16;
        }

        ApproachValue(&sSioBattleWork->x, -0x8000, sSioBattleWork->slideTimer);
        sSioBattleWork->slideTimer--;

        if ((s16)sSioBattleWork->slideTimer > 0) {
            sSioBattleWork->stateFrames++;
        } else {
            sSioBattleWork->state = 3;
            sSioBattleWork->stateFrames = 0;
        }

        break;
    case 3:
        if ((s16)sSioBattleWork->stateFrames == 0) {
            sSioBattleWork->slideTimer = 16;
        }

        ApproachValue(&sSioBattleWork->y, -0x800, sSioBattleWork->slideTimer);
        ApproachValue(&sSioBattleWork->y2, 0xA000, sSioBattleWork->slideTimer);
        sSioBattleWork->slideTimer--;

        if ((s16)sSioBattleWork->slideTimer > 0) {
            sSioBattleWork->stateFrames++;
        } else {
            ModeRequest(&gModeTitle, 0);
            return;
        }

        break;
    }

    sSioBattleWork->gfx = AnimUpdate(&sSioBattleWork->anim);
    DrawSprite(sSioBattleWork->x >> 8, 0, sSioBattleWork->gfx2[0], sSioBattleWork->tiles, sSioBattleWork->palette, NULL, SPRITE_PRIORITY(1), -16);
    DrawSprite(128, sSioBattleWork->y >> 8, sSioBattleWork->gfx2[1], sSioBattleWork->tiles, sSioBattleWork->palette, NULL, SPRITE_PRIORITY(1), -1);
    DrawSprite(128, sSioBattleWork->y2 >> 8, sSioBattleWork->gfx2[2], sSioBattleWork->tiles, sSioBattleWork->palette, NULL, SPRITE_PRIORITY(1), -1);
    DrawSprite(72, 48, sSioBattleWork->gfx3, sSioBattleWork->tiles2, sSioBattleWork->palette2, NULL, SPRITE_PRIORITY(1), -32);
    DrawSprite(72, 48, sSioBattleWork->gfx4, sSioBattleWork->tiles3, sSioBattleWork->palette3, NULL, SPRITE_PRIORITY(1), -32);
    ApproachValueHalf(&sSioBattleWork->cursorY, sSioBattleWork->cursor * 7 * 1024 + 0x3300);
    DrawSprite(64, sSioBattleWork->cursorY >> 8, sSioBattleWork->gfx, sSioBattleWork->tiles4, sSioBattleWork->palette4, NULL, SPRITE_PRIORITY(1), -48);
}

void mode_sio_battle_2() {
    ReleaseObjTiles(sSioBattleWork->tiles);
    ReleaseObjPalette(sSioBattleWork->palette);
    ReleaseObjTiles(sSioBattleWork->tiles2);
    ReleaseObjPalette(sSioBattleWork->palette2);
    ReleaseObjTiles(sSioBattleWork->tiles3);
    ReleaseObjPalette(sSioBattleWork->palette3);
    ReleaseObjTiles(sSioBattleWork->tiles4);
    ReleaseObjPalette(sSioBattleWork->palette4);
    EwramFree(sSioBattleWork);
}

void ClearSioBattleFileLoaded() {
    gSioBattleFileLoaded = 0;
}

void mode_sio_btl_connect_0(s32 arg) {
    sSioBtlConnectWork = EwramAlloc(sizeof(SioBtlConnectWork));
    FadeStartIn(FADE_MODE_BLACK, 16);
    SetBgMode0();
    SetupBg(0, 0, 7, 15);
    SetupBg(1, 1, 31, 0);
    EnableBg(0);
    EnableBg(1);
    LoadBgTiles(0, gUnk_096AD604, 0x140);
    LoadBgMap(0, gUnk_096F6464, 0x800);
    LoadBgPalette(0, gCard00Palette, 0x20);
    LoadBgTiles(1, gUnk_096ACA44, 0xBC0);
    LoadBgPalette(1, gUnk_096FBA04, 0x40);
    LoadBgMap(1, gUnk_096F5C64, 0x800);
    sSioBtlConnectWork->unk_00 = 0;
    sSioBtlConnectWork->timer = 0;
    sSioBtlConnectWork->state = 0;
    sSioBtlConnectWork->textSlotCount = 0;
    InitTextSlots(sSioBtlConnectWork->textSlots, SIO_CONNECT_TEXT_SLOTS);
#ifdef VERSION_EU
    sSioBtlConnectWork->textSlotCount = LoadTextSlots(eu_0805E924(&gUnkEu_08891508), sSioBtlConnectWork->textSlots);
#else
    sSioBtlConnectWork->textSlotCount = LoadTextSlots(gUnk_08159E4A, sSioBtlConnectWork->textSlots);
#endif
    sSioBtlConnectWork->palette = LoadObjPalette(gUnk_096FBAA4, 32);

#ifdef VERSION_EU
    if (!gSioDebugMode) {
        SioReset();
        SioConnectInit(SioBtlConnectOnConnect, SioBtlConnectOnCancel, 0);
    }
#else
    SioReset();
    SioConnectInit(SioBtlConnectOnConnect, SioBtlConnectOnCancel, 0);
#endif
}

void mode_sio_btl_connect_1() {
    s32 i;
    s32 j;

#ifdef VERSION_EU
    s16 width;
    s16 x;

    if (!gSioDebugMode) {
#endif
    switch (sSioBtlConnectWork->state) {
    case 0:
        SioConnectUpdate();
        break;
    case 1:
        SioConnectUpdate();
        sSioBtlConnectWork->timer++;

        if (sSioBtlConnectWork->timer > 4) {
            SioSetLinkCallbacks(SioExchangeSend, SioExchangeRecv);
            SioPrepareCharaLinkExchange();
            gSystemFlags |= SYSTEM_FLAG_LINK_ACTIVE;
            gSystemFlags |= SYSTEM_FLAG_DMA3_FLUSH_CPU;
            sSioBtlConnectWork->state++;
        }

        break;
    case 2:
        if (gSioLinkResult == 2) {
            sSioBtlConnectWork->timer = 0;
            SioInitWorldList();
            sSioBtlConnectWork->state++;
        }

        break;
    case 3:
        sSioBtlConnectWork->timer++;

        if (sSioBtlConnectWork->timer > 4) {
            SioSetLinkCallbacks(SioCommandSend, SioCommandRecv);
            SioCommandReset();
            gSioWorldCursor = 1;
            gSioPrevWorldCursor = 1;
            gSioDeckNameChunk = 1;
            gSioHandicaps[0] = 6;
            gSioHandicaps[1] = 6;

            for (i = 0; i < 2; i++) {
                for (j = 0; j < 20; j++) {
                    gSioDeckNameRecv[i][j] = 0;
                    gSioDeckNameRecvBuf[i][j] = 0;
                    gSioDeckNames[i][j] = 0;
                }
            }

            gSioWinCount = 0;
            gSioLoseCount = 0;
            ModeRequest(&gModeSioBtlOption, 0);
            return;
        }

        break;
    }
#ifdef VERSION_EU
    } else if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
        gSioWorldCursor = 1;
        gSioPrevWorldCursor = 1;
        gSioDeckNameChunk = 1;
        gSioHandicaps[0] = 6;
        gSioHandicaps[1] = 6;

        for (i = 0; i < 2; i++) {
            for (j = 0; j < 20; j++) {
                gSioDeckNameRecv[i][j] = 0;
                gSioDeckNameRecvBuf[i][j] = 0;
                gSioDeckNames[i][j] = 0;
            }
        }

        SioDbgApplySettings();
        SioInitWorldList();
        ModeRequest(&gModeSioBtlOption, 0);
    }

    width = GetTextSlotsMaxLineWidth(sSioBtlConnectWork->textSlots, sSioBtlConnectWork->textSlotCount);

    if (gLanguage == LANGUAGE_FRENCH) {
        x = 120 - (width >> 1);
        DrawTextSlots(x, 68, sSioBtlConnectWork->textSlots, sSioBtlConnectWork->palette, 20, sSioBtlConnectWork->textSlotCount);
    } else {
        x = 120 - (width >> 1);
        DrawTextSlots(x, 63, sSioBtlConnectWork->textSlots, sSioBtlConnectWork->palette, 20, sSioBtlConnectWork->textSlotCount);
    }
#elif defined(VERSION_JP)
    DrawTextSlots(0x3D, 0x3F, sSioBtlConnectWork->textSlots, sSioBtlConnectWork->palette, 20, sSioBtlConnectWork->textSlotCount);
#else
    DrawTextSlots(0x42, 0x3F, sSioBtlConnectWork->textSlots, sSioBtlConnectWork->palette, 20, sSioBtlConnectWork->textSlotCount);
#endif
}

void mode_sio_btl_connect_2() {
    ReleaseObjPalette(sSioBtlConnectWork->palette);
    FreeTextSlots(sSioBtlConnectWork->textSlots, SIO_CONNECT_TEXT_SLOTS);
    EwramFree(sSioBtlConnectWork);
}

void SioBtlConnectOnConnect() {
    m4aSongNumStart(SONG_SYS_ITEMGET);
    sSioBtlConnectWork->state++;
}

void SioBtlConnectOnCancel() {
    m4aSongNumStart(SONG_SYS_CLOSE);
    ModeRequest(&gModeSioBattle, 2);
}

void SioInitWorldList() {
    s32 i;
    s32 flags;
    gSioWorldCount = 0;

    for (i = 0; i < 13; i++) {
        gSioWorldList[i] = 0;
    }

    flags = 0x1FFE;

    for (i = 1; i < 14; i++) {
        if ((flags >> i) & 1) {
            gSioWorldList[gSioWorldCount + 1] = i;
            gSioWorldCount++;
        }
    }
}

void SetSioBtlOptionAnimation(u16 a, u16 b, u16 c) {
    const SioAnimDef* def = &sSioBtlOptionAnimDefs[b];
    AnimChangeWithTables(&sSioBtlOptionWork->anim2[a], def->animId, c, def->anims, def->gfxTable);
    SetObjTileSource(sSioBtlOptionWork->playerTilesPalettes[a], def->tiles);
}

void mode_sio_btl_option_0(s32 arg) {
    sSioBtlOptionWork = EwramAlloc(sizeof(SioBtlOptionWork));
    SetBgMode1();
    SetupBg(0, 0, 7, 10);
    SetBgPriority(0, 0);
    SetBgOverflow(0, 1);
    SetBgSize(0, 0);
    SetupBg(1, 0, 15, 10);
    SetBgPriority(1, 1);
    SetBgOverflow(1, 1);
    SetBgSize(1, 0);
    SetupBg(2, 2, 24, 0);
    SetBgPriority(2, 2);
    SetBgOverflow(2, 1);
    SetBgSize(2, 0x8000);
    RequestDma3Copy(gUnk_096AD744, GetBgCharBase(0), 0x2000);
#ifdef VERSION_EU
    InitTextSlots(sSioBtlOptionWork->textSlots, 40);
    InitTextSlots(sSioBtlOptionWork->textSlots2, 20);
    InitTextSlots(sSioBtlOptionWork->textSlots3, 20);

    if (!gSioDebugMode) {
        sSioBtlOptionWork->textSlotCount2 = LoadTextSlots(gSioDeckNames[0], sSioBtlOptionWork->textSlots2);
        sSioBtlOptionWork->textSlotCount3 = LoadTextSlots(gSioDeckNames[1], sSioBtlOptionWork->textSlots3);
    } else {
        sSioBtlOptionWork->textSlotCount2 = LoadTextSlots((u16*)gUnkEu_095DA860, sSioBtlOptionWork->textSlots2);
        sSioBtlOptionWork->textSlotCount3 = LoadTextSlots((u16*)gUnkEu_095DA867, sSioBtlOptionWork->textSlots3);
    }
#else
    InitTextSlots(sSioBtlOptionWork->textSlots, 20);
    InitTextSlots(sSioBtlOptionWork->textSlots2, 10);
    InitTextSlots(sSioBtlOptionWork->textSlots3, 10);
    sSioBtlOptionWork->textSlotCount2 = LoadTextSlots(gSioDeckNames[0], sSioBtlOptionWork->textSlots2);
    sSioBtlOptionWork->textSlotCount3 = LoadTextSlots(gSioDeckNames[1], sSioBtlOptionWork->textSlots3);
#endif
    sSioBtlOptionWork->palette7 = LoadObjPalette(gUnk_096FBCC4, 32);
    sSioBtlOptionWork->palette8 = LoadObjPalette(gUnk_096FBCC4 + 32, 32);
    sSioBtlOptionWork->palette9 = LoadObjPalette(gUnk_096FBCC4 + 16, 32);
    sSioBtlOptionWork->worldEntry = gSioWorldList[gSioWorldCursor];
    DisableBg(0);
    DisableBg(1);
    sSioBtlOptionWork->modeArg = arg;
    sSioBtlOptionWork->state = 0;
}

void SioBtlOptionLoadBg() {
    RequestDma3Copy(gUnk_096AF744, (u8*)GetBgCharBase(0) + 0x2000, 0x800);

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        LoadBgMap(0, gUnk_096F6C64, 0x800);
        LoadBgMap(1, gUnk_096F7464, 0x800);
        break;
    case LANGUAGE_ITALIAN:
        LoadBgMap(0, gUnkEu_096C298C, 0x800);
        LoadBgMap(1, gUnkEu_096C498C, 0x800);
        break;
    case LANGUAGE_FRENCH:
        LoadBgMap(0, gUnkEu_096C198C, 0x800);
        LoadBgMap(1, gUnkEu_096C398C, 0x800);
        break;
    case LANGUAGE_SPANISH:
        LoadBgMap(0, gUnkEu_096C218C, 0x800);
        LoadBgMap(1, gUnkEu_096C418C, 0x800);
        break;
    case LANGUAGE_GERMAN:
    default:
        LoadBgMap(0, gUnkEu_096C318C, 0x800);
        LoadBgMap(1, gUnkEu_096C518C, 0x800);
        break;
    }
#else
    LoadBgMap(0, gUnk_096F6C64, 0x800);
#endif
    LoadBgPalette(0, gUnk_096FBC04, 0xC0);
#ifndef VERSION_EU
    LoadBgMap(1, gUnk_096F7464, 0x800);
#endif
    DisableBg(0);
    DisableBg(1);
    sSioBtlOptionWork->state = 1;
}

void SioBtlOptionInitObjs() {
    s32 i;

#ifdef VERSION_EU
    RequestDma3Copy(gUnkEu_0967CB6C, (u8*)GetBgCharBase(0) + 0x49E0, 0x1620);
#endif

    if (sSioBtlOptionWork->modeArg == 1) {
        sSioBtlOptionWork->menuOpen = 1;
        sSioBtlOptionWork->cursor = 1;
        sSioBtlOptionWork->y = sSioBtlOptionWork->cursor * 4608 + 10752;
    } else {
        sSioBtlOptionWork->menuOpen = 0;
        sSioBtlOptionWork->cursor = 0;
        sSioBtlOptionWork->y = 10752;
    }

    sSioBtlOptionWork->fadeLevel = 0;
    sSioBtlOptionWork->timer = 0;
    sSioBtlOptionWork->player1Ready = 0;
    sSioBtlOptionWork->player2Ready = 0;
    sSioBtlOptionWork->worldChangeState = 0;
    sSioBtlOptionWork->frameCount = 0;
    sSioBtlOptionWork->leaveDelay = 0;
    sSioBtlOptionWork->unk_418 = 0;
    SetBgAffine(2, 0, 256, 256, 0x10000, 0x16800);

    for (i = 0; i < 2; i++) {
        sSioBtlOptionWork->playerTilesPalettes[i] = AllocObjTiles(0xC80, NULL);
        AnimInit(&sSioBtlOptionWork->anim2[i], NULL, NULL);
        SetSioBtlOptionAnimation(i, 0, 0);
        sSioBtlOptionWork->gfx6[i] = AnimGetGfx(&sSioBtlOptionWork->anim2[i]);
    }

    if (gSioPlayerId == 0) {
        sSioBtlOptionWork->playerTilesPalettes[2] = LoadObjPalette(gSoraPalette, 32);
        sSioBtlOptionWork->playerTilesPalettes[3] = LoadObjPalette(gUnk_096FAC64, 32);
    } else {
        sSioBtlOptionWork->playerTilesPalettes[2] = LoadObjPalette(gUnk_096FAC64, 32);
        sSioBtlOptionWork->playerTilesPalettes[3] = LoadObjPalette(gSoraPalette, 32);
    }

#ifdef VERSION_EU
    sSioBtlOptionWork->palette = LoadObjPalette(gUnk_096FBD24, 32);

    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        sSioBtlOptionWork->tiles = LoadObjTiles(gUnkEu_095F18BE, 0xC00);
        sSioBtlOptionWork->gfx = gUnkEu_09F7EBB0[0];
        break;
    case LANGUAGE_ITALIAN:
        sSioBtlOptionWork->tiles = LoadObjTiles(gUnkEu_095F3D12, 0xC00);
        sSioBtlOptionWork->gfx = gUnkEu_09F7EBC8[0];
        break;
    case LANGUAGE_FRENCH:
        sSioBtlOptionWork->tiles = LoadObjTiles(gUnkEu_095F24DA, 0xC00);
        sSioBtlOptionWork->gfx = gUnkEu_09F7EBB8[0];
        break;
    case LANGUAGE_SPANISH:
        sSioBtlOptionWork->tiles = LoadObjTiles(gUnkEu_095F30F6, 0xC00);
        sSioBtlOptionWork->gfx = gUnkEu_09F7EBC0[0];
        break;
    case LANGUAGE_GERMAN:
    default:
        sSioBtlOptionWork->tiles = LoadObjTiles(gUnkEu_095F492E, 0xC00);
        sSioBtlOptionWork->gfx = gUnkEu_09F7EBD0[0];
        break;
    }
#else
    sSioBtlOptionWork->tiles = LoadObjTiles(gUnk_0962BEDA, 0xC00);
    sSioBtlOptionWork->palette = LoadObjPalette(gUnk_096FBD24, 32);
    sSioBtlOptionWork->gfx = gUnk_09EF38D4[0];
#endif
    sSioBtlOptionWork->tiles2 = LoadObjTiles(gUnk_0962B090, 0x1C0);
    sSioBtlOptionWork->palette2 = LoadObjPalette(gUnk_096FBAA4, 32);
    AnimInit(&sSioBtlOptionWork->anim, gUnk_09EF38B4, gUnk_09EF3894);
    AnimStart(&sSioBtlOptionWork->anim, 1, ANIM_FLAG_LOOP);
    sSioBtlOptionWork->gfx2 = AnimGetGfx(&sSioBtlOptionWork->anim);
    sSioBtlOptionWork->cursorVisible = 1;
    sSioBtlOptionWork->tiles3 = LoadObjTiles(gUnk_093F8C8E, 0xC00);
    sSioBtlOptionWork->palette3 = LoadObjPalette(gCard00Palette, 32);
    sSioBtlOptionWork->gfx3 = gUnk_09EF1278[0];
    sSioBtlOptionWork->messageVisible = 0;
#ifdef VERSION_EU
    InitTextSlots(sSioBtlOptionWork->textSlots4, 120);
    sSioBtlOptionWork->textSlotCount4 = LoadTextSlots(eu_0805E924(&gUnkEu_08891580), sSioBtlOptionWork->textSlots4);
#else
    InitTextSlots(sSioBtlOptionWork->textSlots4, 60);
    sSioBtlOptionWork->textSlotCount4 = LoadTextSlots(gUnk_0815A20C, sSioBtlOptionWork->textSlots4);
#endif
#ifdef VERSION_JP
    sSioBtlOptionWork->x = 68;
#else
    sSioBtlOptionWork->x = 65;
#endif
    sSioBtlOptionWork->y2 = 124;
    sSioBtlOptionWork->palette6 = LoadObjPalette(gUnk_096FBAA4, 32);
#ifdef VERSION_EU
    sSioBtlOptionWork->tiles4 = LoadObjTiles(gUnkEu_095EC758, 0x120);
#else
    sSioBtlOptionWork->tiles4 = LoadObjTiles(gUnk_0962D7C0, 0x120);
#endif
    sSioBtlOptionWork->palette4 = LoadObjPalette(gUnk_096FBD44, 32);
#ifdef VERSION_EU
    sSioBtlOptionWork->gfx4 = gUnkEu_09F7EB08[0];
    sSioBtlOptionWork->gfx7 = gUnkEu_09F7EB08[1];
    sSioBtlOptionWork->gfx8 = gUnkEu_09F7EB08[2];
#else
    sSioBtlOptionWork->gfx4 = gUnk_09EF38EC[0];
    sSioBtlOptionWork->gfx7 = gUnk_09EF38EC[1];
    sSioBtlOptionWork->gfx8 = gUnk_09EF38EC[2];
#endif
    sSioBtlOptionWork->handicapMarkerVisible = 0;
#ifdef VERSION_EU
    sSioBtlOptionWork->tiles5[0] = LoadObjTiles(gUnkEu_095EC898, 0x280);
#else
    sSioBtlOptionWork->tiles5[0] = LoadObjTiles(gUnk_0962D900, 0x280);
#endif
    sSioBtlOptionWork->palette5[0] = LoadObjPalette(gUnk_096FBD64, 32);
#ifdef VERSION_EU
    sSioBtlOptionWork->gfx5[0] = gUnkEu_09F7EB18[0];
#else
    sSioBtlOptionWork->gfx5[0] = gUnk_09EF38FC[0];
#endif
    sSioBtlOptionWork->handicaps[0] = gSioHandicaps[0];
#ifdef VERSION_EU
    sSioBtlOptionWork->tiles5[1] = LoadObjTiles(gUnkEu_095ECB38, 0x280);
#else
    sSioBtlOptionWork->tiles5[1] = LoadObjTiles(gUnk_0962DBA0, 0x280);
#endif
    sSioBtlOptionWork->palette5[1] = LoadObjPalette(gUnk_096FBDA4, 32);
#ifdef VERSION_EU
    sSioBtlOptionWork->gfx5[1] = gUnkEu_09F7EB20[0];
#else
    sSioBtlOptionWork->gfx5[1] = gUnk_09EF3904[0];
#endif
    sSioBtlOptionWork->handicaps[1] = gSioHandicaps[1];

    if (gSioPlayerId == 0) {
        sSioBtlOptionWork->handicap = gSioHandicaps[0];
    } else {
        sSioBtlOptionWork->handicap = gSioHandicaps[1];
    }

    SioBtlOptionDrawStats();
    sSioBtlOptionWork->state = 2;
}

void SioBtlOptionLoadWorld() {
    s8 i = gSioWorldList[gSioWorldCursor];
    RequestDma3Copy(gSioWorldEntries[i].tiles, GetBgCharBase(2), 0x2000);
    LoadBgPalette(2, gSioWorldEntries[i].palette, gSioWorldEntries[i].paletteSize);
#ifdef VERSION_EU
    LoadBgMapLz77(2, gSioWorldEntries[i].map);
    sSioBtlOptionWork->textSlotCount = LoadTextSlots(eu_0805E924(gSioWorldEntries[i].text), sSioBtlOptionWork->textSlots);
#else
    LoadBgMap(2, gSioWorldEntries[i].map, gSioWorldEntries[i].mapSize);
    sSioBtlOptionWork->textSlotCount = LoadTextSlots(gSioWorldEntries[i].text, sSioBtlOptionWork->textSlots);
#endif
    DisableBg(2);
    sSioBtlOptionWork->state++;
}

void SioBtlOptionFadeIn() {
    s8 i = gSioWorldList[gSioWorldCursor];
    FadeStartIn(FADE_MODE_BLACK, 16);
    RequestDma3Copy((u8*)gSioWorldEntries[i].tiles + 0x2000, (u8*)GetBgCharBase(2) + 0x2000, gSioWorldEntries[i].tilesSize - 0x2000);
    EnableBg(0);
    EnableBg(1);
    EnableBg(2);
    SioBtlOptionPlayWorldBgm();
    sSioBtlOptionWork->returnState = 4;
    sSioBtlOptionWork->state = 4;
}

void mode_sio_btl_option_1() {
    switch (sSioBtlOptionWork->state) {
    case 0:
        SioBtlOptionLoadBg();
        break;
    case 1:
        SioBtlOptionInitObjs();
        break;
    case 2:
        SioBtlOptionLoadWorld();
        break;
    case 3:
        SioBtlOptionFadeIn();
        break;
    case 4:
        SioBtlOptionWaitStart();
        break;
    case 5:
        SioBtlOptionHandleIdle();
        SioBtlOptionDraw();
        break;
    case 6:
        SioBtlOptionHandleMenu();
        SioBtlOptionDraw();
        break;
    case 7:
        SioBtlOptionSetHandicap();
        SioBtlOptionDraw();
        break;
    case 8:
        SioBtlOptionChangeWorld();
        SioBtlOptionDraw();
        break;
    case 9:
        SioBtlOptionWaitReady();
        SioBtlOptionDraw();
        break;
    case 10:
        SioBtlOptionConfirm();
        SioBtlOptionDraw();
        break;
    case 11:
        SioBtlOptionStartDeckExchange();
        SioBtlOptionDraw();
        break;
    case 12:
        SioBtlOptionWaitDeckExchange();
        SioBtlOptionDraw();
        break;
    case 13:
        SioBtlOptionResumeCommands();
        SioBtlOptionDraw();
        break;
    case 14:
        SioBtlOptionWaitBeforeSync();
        SioBtlOptionDraw();
        break;
    case 15:
        SioBtlOptionSyncStart();
        SioBtlOptionDraw();
        break;
    case 16:
        SioBtlOptionStartBattle();
        SioBtlOptionDraw();
        break;
    }
}

void SioBtlOptionDraw() {
#ifdef VERSION_EU
    s16 width;
    s32 multiline;
    s32 i;
#endif
    sSioBtlOptionWork->gfx6[0] = AnimUpdate(&sSioBtlOptionWork->anim2[0]);
    sSioBtlOptionWork->gfx6[1] = AnimUpdate(&sSioBtlOptionWork->anim2[1]);
    sSioBtlOptionWork->gfx2 = AnimUpdate(&sSioBtlOptionWork->anim);
    DrawSprite(60, 88, sSioBtlOptionWork->gfx6[0], sSioBtlOptionWork->playerTilesPalettes[0], sSioBtlOptionWork->playerTilesPalettes[2], NULL, SPRITE_FLAG_HFLIP, 0xFFF0);
    DrawSprite(180, 88, sSioBtlOptionWork->gfx6[1], sSioBtlOptionWork->playerTilesPalettes[1], sSioBtlOptionWork->playerTilesPalettes[3], NULL, 0, 0xFFF0);
#ifdef VERSION_EU
    width = GetTextSlotsWidth(sSioBtlOptionWork->textSlots, sSioBtlOptionWork->textSlotCount);
    DrawTextSlots(162 - width / 2, 4, sSioBtlOptionWork->textSlots, sSioBtlOptionWork->palette7, 20, sSioBtlOptionWork->textSlotCount);
#else
    DrawTextSlots(gSioWorldEntries[sSioBtlOptionWork->worldEntry].textX + 108, 4, sSioBtlOptionWork->textSlots, sSioBtlOptionWork->palette7, 20, sSioBtlOptionWork->textSlotCount);
#endif
    DrawTextSlots(16, 144, sSioBtlOptionWork->textSlots2, sSioBtlOptionWork->palette8, 0xF200, sSioBtlOptionWork->textSlotCount2);
    DrawTextSlots(136, 144, sSioBtlOptionWork->textSlots3, sSioBtlOptionWork->palette9, 0xF200, sSioBtlOptionWork->textSlotCount3);
    DrawSprite(-((sSioBtlOptionWork->frameCount >> 3) % 4) + 88, 2, sSioBtlOptionWork->gfx4, sSioBtlOptionWork->tiles4, sSioBtlOptionWork->palette4, NULL, 0, 0xFF00);
    DrawSprite(224 + ((sSioBtlOptionWork->frameCount >> 3) % 4), 2, sSioBtlOptionWork->gfx7, sSioBtlOptionWork->tiles4, sSioBtlOptionWork->palette4, NULL, 0, 0xFF00);

    if (sSioBtlOptionWork->menuOpen == 1) {
        DrawSprite(72, 38, sSioBtlOptionWork->gfx, sSioBtlOptionWork->tiles, sSioBtlOptionWork->palette, NULL, 0, 0x200);

        if (sSioBtlOptionWork->cursorVisible == 1) {
            ApproachValueHalf(&sSioBtlOptionWork->y, sSioBtlOptionWork->cursor * 4608 + 10752);
            DrawSprite(64, sSioBtlOptionWork->y >> 8, sSioBtlOptionWork->gfx2, sSioBtlOptionWork->tiles2, sSioBtlOptionWork->palette2, NULL, 0, 0x100);
        }
    }

    if (sSioBtlOptionWork->messageVisible == 1) {
        DrawSprite(120, 131, sSioBtlOptionWork->gfx3, sSioBtlOptionWork->tiles3, sSioBtlOptionWork->palette3, NULL, 0, 0xF000);
#ifdef VERSION_EU
        width = GetTextSlotsMaxLineWidth(sSioBtlOptionWork->textSlots4, sSioBtlOptionWork->textSlotCount4);
        multiline = 0;

        for (i = 0; i < sSioBtlOptionWork->textSlotCount4; i++) {
            if (sSioBtlOptionWork->textSlots4[i].tiles == NULL) {
                multiline = 1;
                break;
            }
        }

        if (multiline) {
            DrawTextSlots(120 - (width >> 1), 119, sSioBtlOptionWork->textSlots4, sSioBtlOptionWork->palette6, 20, sSioBtlOptionWork->textSlotCount4);
        } else {
            DrawTextSlots(120 - (width >> 1), 124, sSioBtlOptionWork->textSlots4, sSioBtlOptionWork->palette6, 20, sSioBtlOptionWork->textSlotCount4);
        }
#else
        DrawTextSlots(sSioBtlOptionWork->x, sSioBtlOptionWork->y2, sSioBtlOptionWork->textSlots4, sSioBtlOptionWork->palette6, 20, sSioBtlOptionWork->textSlotCount4);
#endif
    }

    DrawSprite(32, 24, sSioBtlOptionWork->gfx5[0], sSioBtlOptionWork->tiles5[0], sSioBtlOptionWork->palette5[0], NULL, 0, 0xF100);
    DrawSprite(132, 24, sSioBtlOptionWork->gfx5[1], sSioBtlOptionWork->tiles5[1], sSioBtlOptionWork->palette5[1], NULL, 0, 0xF100);

    if (sSioBtlOptionWork->handicapMarkerVisible == 1) {
        DrawSprite(gSioPlayerId * 101 + 44 + gSioHandicapMarkerX[sSioBtlOptionWork->handicap], -((sSioBtlOptionWork->frameCount >> 3) % 4) / 2 + 22, sSioBtlOptionWork->gfx8, sSioBtlOptionWork->tiles4, sSioBtlOptionWork->palette4, NULL, 0, 0xF000);
    }

    sSioBtlOptionWork->frameCount++;
}

void SioBtlOptionWaitStart() {
    if (sSioBtlOptionWork->timer > 4) {
        sSioBtlOptionWork->timer = 0;

        if (sSioBtlOptionWork->modeArg == 1) {
            sSioBtlOptionWork->state = 6;
        } else {
            sSioBtlOptionWork->state = 5;
        }
    } else {
        sSioBtlOptionWork->timer++;
    }

    SioBtlOptionCheckReady();
    SioBtlOptionSyncHandicaps();
    SioBtlOptionRecvWorld();
    SioBtlOptionSyncDeckNames();
}

void SioBtlOptionHandleIdle() {
    s8 v = 0;

#ifdef VERSION_EU
    if (!gSioDebugMode) {
#endif
    gSioCommandSend[1] |= 5;

    if (GetKeysPressed() & A_BUTTON) {
        gSioCommandSend[1] |= 0x1F20;
    } else if (GetKeysPressed() & B_BUTTON) {
        gSioCommandSend[1] |= 0xC2F0;
    }

    if (GetKeysPressed() & L_BUTTON) {
        if (gSioWorldCount == 1) {
            m4aSongNumStart(SONG_SYS_BEEP);
        } else {
            v = gSioWorldCursor;
            v--;

            if (v <= 0) {
                v = gSioWorldCount;
            }

            gSioCommandSend[2] |= v & 15;
        }
    } else if (GetKeysPressed() & R_BUTTON) {
        if (gSioWorldCount == 1) {
            m4aSongNumStart(SONG_SYS_BEEP);
        } else {
            v = gSioWorldCursor;
            v++;

            if (v > gSioWorldCount) {
                v = 1;
            }

            gSioCommandSend[2] |= v & 15;
        }
    } else {
        gSioCommandSend[2] &= 0xFFF0;
    }

    if ((gSioCommandRecv[1][0] & 0xFFF0) == 0xC2F0 || (gSioCommandRecv[1][1] & 0xFFF0) == 0xC2F0) {
        if ((gSioCommandRecv[1][0] & 15) == 5 && (gSioCommandRecv[1][1] & 15) == 5 && sSioBtlOptionWork->leaveDelay == 0) {
            SioLinkClose();
            m4aMPlayAllStop();
            gSioWinCount = 0;
            gSioLoseCount = 0;
            ModeRequest(&gModeSioBtlConnect, 0);
        }
    } else if ((gSioCommandRecv[1][0] & 0xFFF0) == 0x1F20) {
        sSioBtlOptionWork->leaveDelay = 10;

        if (gSioPlayerId == 0) {
            m4aSongNumStart(SONG_SYS_CANSEL);
            sSioBtlOptionWork->menuOpen = 1;
            sSioBtlOptionWork->state = 6;
        }
    } else if ((gSioCommandRecv[1][1] & 0xFFF0) == 0x1F20) {
        sSioBtlOptionWork->leaveDelay = 10;

        if (gSioPlayerId == 1) {
            m4aSongNumStart(SONG_SYS_CANSEL);
            sSioBtlOptionWork->menuOpen = 1;
            sSioBtlOptionWork->state = 6;
        }
    }

    SioBtlOptionCheckReady();
    SioBtlOptionSyncHandicaps();
    SioBtlOptionRecvWorld();
    SioBtlOptionSyncDeckNames();

    if (sSioBtlOptionWork->leaveDelay > 0) {
        sSioBtlOptionWork->leaveDelay--;
    }
#ifdef VERSION_EU
    } else {
        if (GetKeysPressed() & A_BUTTON) {
            m4aSongNumStart(SONG_SYS_CANSEL);
            sSioBtlOptionWork->menuOpen = 1;
            sSioBtlOptionWork->state = 6;
        }

        if (GetKeysPressed() & L_BUTTON) {
            if (gSioWorldCount == 1) {
                m4aSongNumStart(SONG_SYS_BEEP);
            } else {
                v = gSioWorldCursor;
                v--;

                if (v <= 0) {
                    v = gSioWorldCount;
                }

                sSioBtlOptionWork->timer = 0;
                sSioBtlOptionWork->fadeLevel = 0;
                sSioBtlOptionWork->worldChangeState = 0;
                sSioBtlOptionWork->returnState = sSioBtlOptionWork->state;
                gSioPrevWorldCursor = gSioWorldCursor;
                gSioWorldCursor = v;
                sSioBtlOptionWork->state = 8;
                m4aSongNumStart(SONG_SYS_CANSEL);
            }
        } else if (GetKeysPressed() & R_BUTTON) {
            if (gSioWorldCount == 1) {
                m4aSongNumStart(SONG_SYS_BEEP);
            } else {
                v = gSioWorldCursor;
                v++;

                if (v > gSioWorldCount) {
                    v = 1;
                }

                sSioBtlOptionWork->timer = 0;
                sSioBtlOptionWork->fadeLevel = 0;
                sSioBtlOptionWork->worldChangeState = 0;
                sSioBtlOptionWork->returnState = sSioBtlOptionWork->state;
                gSioPrevWorldCursor = gSioWorldCursor;
                gSioWorldCursor = v;
                sSioBtlOptionWork->state = 8;
                m4aSongNumStart(SONG_SYS_CANSEL);
            }
        } else {
            gSioCommandSend[2] &= 0xFFF0;
        }

        SioBtlOptionCheckReady();
        SioBtlOptionSyncHandicaps();
        SioBtlOptionRecvWorld();
        SioBtlOptionSyncDeckNames();
    }
#endif
}

void SioBtlOptionHandleMenu() {
    s8 v;

#ifdef VERSION_EU
    if (!gSioDebugMode) {
#endif
    gSioCommandSend[1] = 6;

    if (GetKeysPressed() & DPAD_UP) {
        m4aSongNumStart(SONG_SYS_CLICK);
        sSioBtlOptionWork->cursor--;

        if (sSioBtlOptionWork->cursor < 0) {
            sSioBtlOptionWork->cursor = 2;
        }
    } else if (GetKeysPressed() & DPAD_DOWN) {
        m4aSongNumStart(SONG_SYS_CLICK);
        sSioBtlOptionWork->cursor++;

        if (sSioBtlOptionWork->cursor > 2) {
            sSioBtlOptionWork->cursor = 0;
        }
    }

    if (GetKeysPressed() & L_BUTTON) {
        if (gSioWorldCount == 1) {
            m4aSongNumStart(SONG_SYS_BEEP);
        } else {
            v = gSioWorldCursor;
            v--;

            if (v <= 0) {
                v = gSioWorldCount;
            }

            gSioCommandSend[2] |= v & 15;
        }
    } else if (GetKeysPressed() & R_BUTTON) {
        if (gSioWorldCount == 1) {
            m4aSongNumStart(SONG_SYS_BEEP);
        } else {
            v = gSioWorldCursor;
            v++;

            if (v > gSioWorldCount) {
                v = 1;
            }

            gSioCommandSend[2] |= v & 15;
        }
    } else {
        gSioCommandSend[2] &= 0xFFF0;
    }

    if (GetKeysPressed() & A_BUTTON) {
        m4aSongNumStart(SONG_SYS_KETTEI);

        switch (sSioBtlOptionWork->cursor) {
        case 0:
            if (gSioPlayerId == 0) {
                gSioCommandSend[1] = 0x2FCF;
            } else {
                gSioCommandSend[1] = 0x6AD6;
            }

            sSioBtlOptionWork->menuOpen = 0;
            sSioBtlOptionWork->messageVisible = 1;
#ifdef VERSION_EU
            sSioBtlOptionWork->textSlotCount4 = LoadTextSlots(eu_0805E924(&gUnkEu_08891580), sSioBtlOptionWork->textSlots4);
#else
            sSioBtlOptionWork->textSlotCount4 = LoadTextSlots(gUnk_0815A20C, sSioBtlOptionWork->textSlots4);
#endif
#ifdef VERSION_JP
            sSioBtlOptionWork->x = 68;
#else
            sSioBtlOptionWork->x = 65;
#endif
            sSioBtlOptionWork->y2 = 124;
            sSioBtlOptionWork->state = 9;
            break;
        case 1:
            ModeRequest(&gModeDeck, 0);
            break;
        case 2:
            sSioBtlOptionWork->cursorVisible = 0;
            sSioBtlOptionWork->handicapMarkerVisible = 1;
            sSioBtlOptionWork->state = 7;
            break;
        }
    } else if (GetKeysPressed() & B_BUTTON) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        sSioBtlOptionWork->menuOpen = 0;
        sSioBtlOptionWork->state = 5;
    }

    SioBtlOptionCheckReady();
    SioBtlOptionSyncHandicaps();
    SioBtlOptionRecvWorld();
    SioBtlOptionSyncDeckNames();
#ifdef VERSION_EU
    } else {
        if (GetKeysPressed() & DPAD_UP) {
            m4aSongNumStart(SONG_SYS_CLICK);
            sSioBtlOptionWork->cursor--;

            if (sSioBtlOptionWork->cursor < 0) {
                sSioBtlOptionWork->cursor = 2;
            }
        } else if (GetKeysPressed() & DPAD_DOWN) {
            m4aSongNumStart(SONG_SYS_CLICK);
            sSioBtlOptionWork->cursor++;

            if (sSioBtlOptionWork->cursor > 2) {
                sSioBtlOptionWork->cursor = 0;
            }
        }

        if (GetKeysPressed() & L_BUTTON) {
            if (gSioWorldCount == 1) {
                m4aSongNumStart(SONG_SYS_BEEP);
            } else {
                v = gSioWorldCursor;
                v--;

                if (v <= 0) {
                    v = gSioWorldCount;
                }

                sSioBtlOptionWork->timer = 0;
                sSioBtlOptionWork->fadeLevel = 0;
                sSioBtlOptionWork->worldChangeState = 0;
                sSioBtlOptionWork->returnState = sSioBtlOptionWork->state;
                gSioPrevWorldCursor = gSioWorldCursor;
                gSioWorldCursor = v;
                sSioBtlOptionWork->state = 8;
                m4aSongNumStart(SONG_SYS_CANSEL);
            }
        } else if (GetKeysPressed() & R_BUTTON) {
            if (gSioWorldCount == 1) {
                m4aSongNumStart(SONG_SYS_BEEP);
            } else {
                v = gSioWorldCursor;
                v++;

                if (v > gSioWorldCount) {
                    v = 1;
                }

                sSioBtlOptionWork->timer = 0;
                sSioBtlOptionWork->fadeLevel = 0;
                sSioBtlOptionWork->worldChangeState = 0;
                sSioBtlOptionWork->returnState = sSioBtlOptionWork->state;
                gSioPrevWorldCursor = gSioWorldCursor;
                gSioWorldCursor = v;
                sSioBtlOptionWork->state = 8;
                m4aSongNumStart(SONG_SYS_CANSEL);
            }
        }

        if (GetKeysPressed() & A_BUTTON) {
            m4aSongNumStart(SONG_SYS_KETTEI);

            switch (sSioBtlOptionWork->cursor) {
            case 0:
                gSioDebugReady[0] = 1;
                sSioBtlOptionWork->menuOpen = 0;
                sSioBtlOptionWork->messageVisible = 1;
                sSioBtlOptionWork->textSlotCount4 = LoadTextSlots(eu_0805E924(&gUnkEu_08891580), sSioBtlOptionWork->textSlots4);
#ifdef VERSION_JP
                sSioBtlOptionWork->x = 68;
#else
                sSioBtlOptionWork->x = 65;
#endif
                sSioBtlOptionWork->y2 = 124;
                sSioBtlOptionWork->state = 9;
                break;
            case 1:
                ModeRequest(&gModeDeck, 0);
                break;
            case 2:
                sSioBtlOptionWork->cursorVisible = 0;
                sSioBtlOptionWork->handicapMarkerVisible = 1;
                sSioBtlOptionWork->state = 7;
                break;
            }
        } else if (GetKeysPressed() & B_BUTTON) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            sSioBtlOptionWork->menuOpen = 0;
            sSioBtlOptionWork->state = 5;
        }

        SioBtlOptionCheckReady();
        SioBtlOptionSyncHandicaps();
        SioBtlOptionRecvWorld();
        SioBtlOptionSyncDeckNames();
    }
#endif
}

void SioBtlOptionSetHandicap() {
#ifdef VERSION_EU
    if (!gSioDebugMode) {
#endif
    if (GetKeysPressed() & DPAD_LEFT) {
        if (sSioBtlOptionWork->handicap > 1) {
            m4aSongNumStart(SONG_SYS_CLICK);
            sSioBtlOptionWork->handicap--;
        } else {
            m4aSongNumStart(SONG_SYS_BEEP);
        }
    } else if (GetKeysPressed() & DPAD_RIGHT) {
        if (sSioBtlOptionWork->handicap <= 10) {
            m4aSongNumStart(SONG_SYS_CLICK);
            sSioBtlOptionWork->handicap++;
        } else {
            m4aSongNumStart(SONG_SYS_BEEP);
        }
    }

    if (gSioPlayerId == 0) {
        gSioHandicaps[0] = sSioBtlOptionWork->handicap;
    } else {
        gSioHandicaps[1] = sSioBtlOptionWork->handicap;
    }

    if (GetKeysPressed() & (A_BUTTON | B_BUTTON)) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        sSioBtlOptionWork->cursorVisible = 1;
        sSioBtlOptionWork->handicapMarkerVisible = 0;
        sSioBtlOptionWork->state = 6;
    }

    SioBtlOptionCheckReady();
    SioBtlOptionSyncHandicaps();
    SioBtlOptionRecvWorld();
    SioBtlOptionSyncDeckNames();
#ifdef VERSION_EU
    } else {
        if (GetKeysPressed() & DPAD_LEFT) {
            if (sSioBtlOptionWork->handicap > 1) {
                m4aSongNumStart(SONG_SYS_CLICK);
                sSioBtlOptionWork->handicap--;
                gSioHandicaps[0] = sSioBtlOptionWork->handicap;
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        } else if (GetKeysPressed() & DPAD_RIGHT) {
            if (sSioBtlOptionWork->handicap <= 10) {
                m4aSongNumStart(SONG_SYS_CLICK);
                sSioBtlOptionWork->handicap++;
                gSioHandicaps[0] = sSioBtlOptionWork->handicap;
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        }

        if (GetKeysPressed() & L_BUTTON) {
            if ((s8)gSioHandicaps[1] > 1) {
                m4aSongNumStart(SONG_SYS_CLICK);
                gSioHandicaps[1]--;
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        } else if (GetKeysPressed() & R_BUTTON) {
            if ((s8)gSioHandicaps[1] <= 10) {
                m4aSongNumStart(SONG_SYS_CLICK);
                gSioHandicaps[1]++;
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        }

        if (GetKeysPressed() & (A_BUTTON | B_BUTTON)) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            sSioBtlOptionWork->cursorVisible = 1;
            sSioBtlOptionWork->handicapMarkerVisible = 0;
            sSioBtlOptionWork->state = 6;
        }

        SioBtlOptionCheckReady();
        SioBtlOptionSyncHandicaps();
        SioBtlOptionRecvWorld();
        SioBtlOptionSyncDeckNames();
    }
#endif
}

void SioBtlOptionChangeWorld() {
    s8 a = gSioWorldList[gSioPrevWorldCursor];
    s8 b = gSioWorldList[gSioWorldCursor];

    switch (sSioBtlOptionWork->worldChangeState) {
    case 0:
        sSioBtlOptionWork->timer++;

        if (sSioBtlOptionWork->timer > 1) {
            sSioBtlOptionWork->timer = 0;

            if (sSioBtlOptionWork->fadeLevel > 31) {
                sSioBtlOptionWork->fadeLevel = 32;
                sSioBtlOptionWork->worldChangeState++;
            } else {
                sSioBtlOptionWork->fadeLevel += 8;
                FadePaletteToBlack(gSioWorldEntries[a].palette, (u16*)PLTT, gSioWorldEntries[a].paletteSize, sSioBtlOptionWork->fadeLevel);
            }
        }

        break;
    case 1:
        FadePaletteToBlack(gSioWorldEntries[b].palette, (u16*)PLTT, gSioWorldEntries[b].paletteSize, 32);
#ifdef VERSION_EU
        LoadBgMapLz77(2, gSioWorldEntries[b].map);
#else
        LoadBgMap(2, gSioWorldEntries[b].map, gSioWorldEntries[b].mapSize);
#endif
        RequestDma3Copy(gSioWorldEntries[b].tiles, GetBgCharBase(2), 0x2000);
        sSioBtlOptionWork->worldChangeState++;
        break;
    case 2:
        RequestDma3Copy((u8*)gSioWorldEntries[b].tiles + 0x2000, (u8*)GetBgCharBase(2) + 0x2000, gSioWorldEntries[b].tilesSize - 0x2000);
#ifdef VERSION_EU
        sSioBtlOptionWork->textSlotCount = LoadTextSlots(eu_0805E924(gSioWorldEntries[b].text), sSioBtlOptionWork->textSlots);
#else
        sSioBtlOptionWork->textSlotCount = LoadTextSlots(gSioWorldEntries[b].text, sSioBtlOptionWork->textSlots);
#endif
        sSioBtlOptionWork->worldEntry = b;
        sSioBtlOptionWork->worldChangeState++;
        break;
    case 3:
        sSioBtlOptionWork->timer++;

        if (sSioBtlOptionWork->timer > 1) {
            sSioBtlOptionWork->timer = 0;

            if (sSioBtlOptionWork->fadeLevel <= 0) {
                sSioBtlOptionWork->fadeLevel = 0;
                SioBtlOptionPlayWorldBgm();
                sSioBtlOptionWork->worldChangeState++;
            } else {
                sSioBtlOptionWork->fadeLevel -= 8;

                if (sSioBtlOptionWork->fadeLevel == 0) {
                    LoadPaletteWithEffect(gSioWorldEntries[b].palette, (u16*)PLTT, gSioWorldEntries[b].paletteSize);
                } else {
                    FadePaletteToBlack(gSioWorldEntries[b].palette, (u16*)PLTT, gSioWorldEntries[b].paletteSize, sSioBtlOptionWork->fadeLevel);
                }
            }
        }

        break;
    default:
        sSioBtlOptionWork->state = sSioBtlOptionWork->returnState;
        break;
    }

    SioBtlOptionCheckReady();
    SioBtlOptionSyncHandicaps();
    SioBtlOptionSyncDeckNames();
}

void SioBtlOptionWaitReady() {
#ifdef VERSION_EU
    if (!gSioDebugMode) {
#endif
        if (gSioPlayerId == 0) {
            gSioCommandSend[1] = 0x2FCF;
        } else {
            gSioCommandSend[1] = 0x6AD6;
        }

#ifdef VERSION_EU
    } else if (GetKeysPressed() & A_BUTTON) {
        gSioDebugReady[1] = 1;
    }
#endif

    if (sSioBtlOptionWork->player1Ready == 1 && sSioBtlOptionWork->player2Ready == 1) {
        sSioBtlOptionWork->timer = 0;
#ifdef VERSION_EU
        sSioBtlOptionWork->textSlotCount4 = LoadTextSlots(eu_0805E924(&gUnkEu_08891670), sSioBtlOptionWork->textSlots4);
#else
        sSioBtlOptionWork->textSlotCount4 = LoadTextSlots(gUnk_0815A23C, sSioBtlOptionWork->textSlots4);
#endif
#ifdef VERSION_JP
        sSioBtlOptionWork->x = 61;
#else
        sSioBtlOptionWork->x = 68;
#endif
        sSioBtlOptionWork->y2 = 119;
        sSioBtlOptionWork->state++;
    }

    SioBtlOptionCheckReady();
    SioBtlOptionSyncHandicaps();
    SioBtlOptionRecvWorld();
    SioBtlOptionSyncDeckNames();
}

void SioBtlOptionConfirm() {
#ifdef VERSION_EU
    if (!gSioDebugMode) {
#endif
    if (GetKeysPressed() & A_BUTTON) {
        gSioCommandSend[1] = 0xA926;
    } else if (GetKeysPressed() & B_BUTTON) {
        gSioCommandSend[1] = 0xDD42;
    }

    if (gSioCommandRecv[1][0] == 0xA926 || gSioCommandRecv[1][1] == 0xA926) {
        m4aSongNumStart(SONG_SYS_ITEMGET);
        sSioBtlOptionWork->timer = 0;
#ifdef VERSION_EU
        sSioBtlOptionWork->textSlotCount4 = LoadTextSlots(eu_0805E924(&gUnkEu_08891714), sSioBtlOptionWork->textSlots4);
#else
        sSioBtlOptionWork->textSlotCount4 = LoadTextSlots(gUnk_0815B3D4, sSioBtlOptionWork->textSlots4);
#endif
#ifdef VERSION_JP
        sSioBtlOptionWork->x = 74;
#else
        sSioBtlOptionWork->x = 72;
#endif
        sSioBtlOptionWork->y2 = 124;
        sSioBtlOptionWork->state++;
    } else if (gSioCommandRecv[1][0] == 0xDD42 || gSioCommandRecv[1][1] == 0xDD42) {
        sSioBtlOptionWork->leaveDelay = 10;
        m4aSongNumStart(SONG_SYS_CLOSE);
        sSioBtlOptionWork->timer = 0;
        SioBtlOptionCancelReady();
        sSioBtlOptionWork->state = 5;
    }
#ifdef VERSION_EU
    } else if (GetKeysPressed() & A_BUTTON) {
        m4aSongNumStart(SONG_SYS_ITEMGET);
        sSioBtlOptionWork->timer = 0;
        sSioBtlOptionWork->textSlotCount4 = LoadTextSlots(eu_0805E924(&gUnkEu_08891714), sSioBtlOptionWork->textSlots4);
        sSioBtlOptionWork->x = 72;
        sSioBtlOptionWork->y2 = 124;
        sSioBtlOptionWork->state++;
    }
#endif
}

void SioBtlOptionStartDeckExchange() {
#ifdef VERSION_EU
    if (!gSioDebugMode) {
        sSioBtlOptionWork->timer++;

        if (sSioBtlOptionWork->timer > 9) {
            SioSetLinkCallbacks(SioExchangeSend, SioExchangeRecv);
            SioPrepareDeckExchange();
            sSioBtlOptionWork->state++;
        }
    } else {
        sSioBtlOptionWork->timer++;

        if (sSioBtlOptionWork->timer > 9) {
            SioPrepareDeckExchange();
            SioExchangeLoopback();
            sSioBtlOptionWork->timer = 0;
            sSioBtlOptionWork->state++;
        }
    }
#else
    sSioBtlOptionWork->timer++;

    if (sSioBtlOptionWork->timer > 9) {
        SioSetLinkCallbacks(SioExchangeSend, SioExchangeRecv);
        SioPrepareDeckExchange();
        sSioBtlOptionWork->state++;
    }
#endif
}

void SioBtlOptionWaitDeckExchange() {
#ifdef VERSION_EU
    if (!gSioDebugMode) {
        if (gSioLinkResult == 2) {
            sSioBtlOptionWork->timer = 0;
            sSioBtlOptionWork->state++;
        }
    } else {
        sSioBtlOptionWork->timer++;

        if (sSioBtlOptionWork->timer > 59) {
            sSioBtlOptionWork->timer = 0;
            gSystemFlags |= SYSTEM_FLAG_LINK_ACTIVE;
            SioSetLinkCallbacks(SioRandomPartnerSend, SioRandomPartnerRecv);
            SioApplyBattleSettings();
            gRandomPartnerDpadTimer = 180;
            gRandomPartnerDpad = 0;
            gRandomPartnerATimer = 120;
            ModeRequest(&gModeVsbattle, 0);
        }
    }
#else
    if (gSioLinkResult == 2) {
        sSioBtlOptionWork->timer = 0;
        sSioBtlOptionWork->state++;
    }
#endif
}

void SioBtlOptionResumeCommands() {
    sSioBtlOptionWork->timer++;

    if (sSioBtlOptionWork->timer > 4) {
        sSioBtlOptionWork->timer = 0;
        SioSetLinkCallbacks(SioCommandSend, SioCommandRecv);
        SioCommandReset();
        sSioBtlOptionWork->state++;
    }
}

void SioBtlOptionWaitBeforeSync() {
    sSioBtlOptionWork->timer++;

    if (sSioBtlOptionWork->timer > 30) {
        sSioBtlOptionWork->timer = 0;
        sSioBtlOptionWork->state++;
    }
}

void SioBtlOptionSyncStart() {
    sSioBtlOptionWork->timer++;

    if (sSioBtlOptionWork->timer > 20) {
        gSioCommandSend[1] = 0x7CD2;

        if (gSioCommandRecv[1][0] == 0x7CD2 && gSioCommandRecv[1][1] == 0x7CD2) {
            sSioBtlOptionWork->timer = 0;
            gSystemFlags &= ~SYSTEM_FLAG_DMA3_FLUSH_CPU;
            sSioBtlOptionWork->state++;
        }
    }
}

void SioBtlOptionStartBattle() {
    sSioBtlOptionWork->timer++;

    if (sSioBtlOptionWork->timer > 4) {
        sSioBtlOptionWork->timer = 0;
        SioSetLinkCallbacks(SioKeySyncSend, SioKeySyncRecv);
        SioApplyBattleSettings();

        if (gSioPlayerId == 0) {
            ModeRequest(&gModeVsbattle, 0);
        } else {
            ModeRequest(&gModeVsbattle, 1);
        }
    }
}

void mode_sio_btl_option_2() {
    ReleaseObjTiles(sSioBtlOptionWork->playerTilesPalettes[0]);
    ReleaseObjPalette(sSioBtlOptionWork->playerTilesPalettes[2]);
    ReleaseObjTiles(sSioBtlOptionWork->playerTilesPalettes[1]);
    ReleaseObjPalette(sSioBtlOptionWork->playerTilesPalettes[3]);
    ReleaseObjPalette(sSioBtlOptionWork->palette7);
    ReleaseObjPalette(sSioBtlOptionWork->palette8);
    ReleaseObjPalette(sSioBtlOptionWork->palette9);
    ReleaseObjPalette(sSioBtlOptionWork->palette6);
#ifdef VERSION_EU
    FreeTextSlots(sSioBtlOptionWork->textSlots, 40);
    FreeTextSlots(sSioBtlOptionWork->textSlots2, 20);
    FreeTextSlots(sSioBtlOptionWork->textSlots3, 20);
    FreeTextSlots(sSioBtlOptionWork->textSlots4, 120);
#else
    FreeTextSlots(sSioBtlOptionWork->textSlots, 20);
    FreeTextSlots(sSioBtlOptionWork->textSlots2, 10);
    FreeTextSlots(sSioBtlOptionWork->textSlots3, 10);
    FreeTextSlots(sSioBtlOptionWork->textSlots4, 60);
#endif
    ReleaseObjTiles(sSioBtlOptionWork->tiles);
    ReleaseObjPalette(sSioBtlOptionWork->palette);
    ReleaseObjTiles(sSioBtlOptionWork->tiles2);
    ReleaseObjPalette(sSioBtlOptionWork->palette2);
    ReleaseObjTiles(sSioBtlOptionWork->tiles3);
    ReleaseObjPalette(sSioBtlOptionWork->palette3);
    ReleaseObjTiles(sSioBtlOptionWork->tiles4);
    ReleaseObjPalette(sSioBtlOptionWork->palette4);
    ReleaseObjTiles(sSioBtlOptionWork->tiles5[0]);
    ReleaseObjPalette(sSioBtlOptionWork->palette5[0]);
    ReleaseObjTiles(sSioBtlOptionWork->tiles5[1]);
    ReleaseObjPalette(sSioBtlOptionWork->palette5[1]);
    EwramFree(sSioBtlOptionWork);
}

void SioBtlOptionCheckReady() {
#ifdef VERSION_EU
    if (!gSioDebugMode) {
#endif
    if (gSioCommandRecv[1][0] == 0x2FCF) {
        RequestDma3Copy(gUnk_096B2724, (void*)(BG_VRAM + TILE_SIZE_4BPP), 0xC0);

        if (!sSioBtlOptionWork->player1Ready) {
            SetSioBtlOptionAnimation(0, 1, 1);
        }

        sSioBtlOptionWork->player1Ready = 1;
    }

    if (gSioCommandRecv[1][1] == 0x6AD6) {
        RequestDma3Copy(gUnk_096B2B24, (void*)(BG_VRAM + 24 * TILE_SIZE_4BPP), 0xC0);

        if (!sSioBtlOptionWork->player2Ready) {
            SetSioBtlOptionAnimation(1, 1, 1);
        }

        sSioBtlOptionWork->player2Ready = 1;
    }
#ifdef VERSION_EU
    } else {
    if (gSioDebugReady[0] == 1) {
        RequestDma3Copy(gUnk_096B2724, (void*)(BG_VRAM + TILE_SIZE_4BPP), 0xC0);

        if (!sSioBtlOptionWork->player1Ready) {
            SetSioBtlOptionAnimation(0, 1, 1);
        }

        sSioBtlOptionWork->player1Ready = 1;
    }

    if (gSioDebugReady[1] == 1) {
        RequestDma3Copy(gUnk_096B2B24, (void*)(BG_VRAM + 24 * TILE_SIZE_4BPP), 0xC0);

        if (!sSioBtlOptionWork->player2Ready) {
            SetSioBtlOptionAnimation(1, 1, 1);
        }

        sSioBtlOptionWork->player2Ready = 1;
    }
    }
#endif
}

void SioBtlOptionRecvWorld() {
    s8 x;
    s8 y;

#ifdef VERSION_EU
    if (gSioDebugMode) {
        return;
    }
#endif

    x = gSioCommandRecv[2][0] & 15;
    y = gSioCommandRecv[2][1] & 15;

    if (x != 0 || y != 0) {
        if (x <= 12 && y <= 12) {
            gSioPrevWorldCursor = gSioWorldCursor;

            if (x > y) {
                gSioWorldCursor = x;
            } else if (x < y) {
                gSioWorldCursor = y;
            } else {
                gSioWorldCursor = x;
            }

            sSioBtlOptionWork->timer = 0;
            sSioBtlOptionWork->fadeLevel = 0;
            sSioBtlOptionWork->worldChangeState = 0;
            sSioBtlOptionWork->returnState = sSioBtlOptionWork->state;
            sSioBtlOptionWork->state = 8;
            m4aSongNumStart(SONG_SYS_CANSEL);
        }
    }
}

void SioBtlOptionRecvSettings() {
    u8 buf[2];
    s8 x;
    s8 y;
    s32 i;

#ifdef VERSION_EU
    if (gSioDebugMode) {
        return;
    }
#endif

    buf[0] = (gSioCommandRecv[2][0] & 0xF0) >> 4;
    buf[1] = (gSioCommandRecv[2][1] & 0xF0) >> 4;

    if (buf[0] >= 1 && buf[0] <= 11) {
        gSioHandicaps[0] = buf[0];
    }

    if (buf[1] >= 1 && buf[1] <= 11) {
        gSioHandicaps[1] = buf[1];
    }

    if ((gSioCommandRecv[2][0] >> 12) != 0) {
        u16 n = (gSioCommandRecv[2][0] >> 12) - 1;
        gSioDeckNameRecvBuf[0][n * 2] = gSioCommandRecv[3][0];
        gSioDeckNameRecvBuf[0][n * 2 + 1] = gSioCommandRecv[3][0] >> 8;

        if (n == 9) {
            for (i = 0; i < 20; i++) {
                gSioDeckNameRecv[0][i] = gSioDeckNameRecvBuf[0][i];
            }
        }
    }

    if ((gSioCommandRecv[2][1] >> 12) != 0) {
        u16 n = (gSioCommandRecv[2][1] >> 12) - 1;
        gSioDeckNameRecvBuf[1][n * 2] = gSioCommandRecv[3][1];
        gSioDeckNameRecvBuf[1][n * 2 + 1] = gSioCommandRecv[3][1] >> 8;

        if (n == 9) {
            for (i = 0; i < 20; i++) {
                gSioDeckNameRecv[1][i] = gSioDeckNameRecvBuf[1][i];
            }
        }
    }

    x = gSioCommandRecv[2][0] & 15;
    y = gSioCommandRecv[2][1] & 15;

    if (x != 0 || y != 0) {
        if (x <= 12 && y <= 12) {
            if (x > y) {
                gSioWorldCursor = x;
            } else if (x < y) {
                gSioWorldCursor = y;
            } else {
                gSioWorldCursor = x;
            }
        }
    }
}

void SioBtlOptionSyncDeckNames() {
    s32 deck;
    s32 i;

#ifdef VERSION_EU
    if (gSioDebugMode) {
        return;
    }
#endif

    deck = GetActiveDeckIndex();
    gSioCommandSend[2] |= (gSioDeckNameChunk & 15) << 12;
    gSioCommandSend[3] = gDecks[deck].name[(gSioDeckNameChunk - 1) * 2] | (gDecks[deck].name[(gSioDeckNameChunk - 1) * 2 + 1] << 8);
    gSioDeckNameChunk++;

    if (gSioDeckNameChunk > 10) {
        gSioDeckNameChunk = 1;
    }

    if ((gSioCommandRecv[2][0] >> 12) != 0) {
        u16 n = (gSioCommandRecv[2][0] >> 12) - 1;
        gSioDeckNameRecvBuf[0][n * 2] = gSioCommandRecv[3][0];
        gSioDeckNameRecvBuf[0][n * 2 + 1] = gSioCommandRecv[3][0] >> 8;

        if (n == 9) {
            for (i = 0; i < 20; i++) {
                gSioDeckNameRecv[0][i] = gSioDeckNameRecvBuf[0][i];
                gSioDeckNames[0][i] = gSioDeckNameRecv[0][i];
            }

            sSioBtlOptionWork->textSlotCount2 = LoadTextSlots(gSioDeckNames[0], sSioBtlOptionWork->textSlots2);
        }
    }

    if ((gSioCommandRecv[2][1] >> 12) != 0) {
        u16 n = (gSioCommandRecv[2][1] >> 12) - 1;
        gSioDeckNameRecvBuf[1][n * 2] = gSioCommandRecv[3][1];
        gSioDeckNameRecvBuf[1][n * 2 + 1] = gSioCommandRecv[3][1] >> 8;

        if (n == 9) {
            for (i = 0; i < 20; i++) {
                gSioDeckNameRecv[1][i] = gSioDeckNameRecvBuf[1][i];
                gSioDeckNames[1][i] = gSioDeckNameRecv[1][i];
            }

            sSioBtlOptionWork->textSlotCount3 = LoadTextSlots(gSioDeckNames[1], sSioBtlOptionWork->textSlots3);
        }
    }
}

void SioBtlOptionDrawStats() {
    s16 digits[4];
    s16 a, b, c, d, e, f, g, h;

#ifdef VERSION_EU
    if ((!gSioDebugMode ? gSioPlayerId : 0) != 0) {
        a = gCharaLinkRecv.level;
        b = gCharaLinkSend.level;
        c = gCharaLinkRecv.maxHp;
        d = gCharaLinkSend.maxHp;
        e = gCharaLinkRecv.winCount;
        f = gCharaLinkSend.winCount;
        g = gCharaLinkRecv.loseCount;
        h = gCharaLinkSend.loseCount;
    } else {
        a = gCharaLinkSend.level;
        b = gCharaLinkRecv.level;
        c = gCharaLinkSend.maxHp;
        d = gCharaLinkRecv.maxHp;
        e = gCharaLinkSend.winCount;
        f = gCharaLinkRecv.winCount;
        g = gCharaLinkSend.loseCount;
        h = gCharaLinkRecv.loseCount;
    }
#else
    if (gSioPlayerId == 0) {
        a = gCharaLinkSend.level;
        b = gCharaLinkRecv.level;
        c = gCharaLinkSend.maxHp;
        d = gCharaLinkRecv.maxHp;
        e = gCharaLinkSend.winCount;
        f = gCharaLinkRecv.winCount;
        g = gCharaLinkSend.loseCount;
        h = gCharaLinkRecv.loseCount;
    } else {
        a = gCharaLinkRecv.level;
        b = gCharaLinkSend.level;
        c = gCharaLinkRecv.maxHp;
        d = gCharaLinkSend.maxHp;
        e = gCharaLinkRecv.winCount;
        f = gCharaLinkSend.winCount;
        g = gCharaLinkRecv.loseCount;
        h = gCharaLinkSend.loseCount;
    }
#endif

    digits[0] = a / 100;
    a %= 100;
    digits[1] = a / 10;
    a %= 10;
    digits[2] = a;
    RequestDma3Copy(gUnk_096B2124 + digits[1] * 32, (void*)(BG_VRAM + 8 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + digits[2] * 32, (void*)(BG_VRAM + 9 * TILE_SIZE_4BPP), 32);

    digits[0] = c / 100;
    c %= 100;
    digits[1] = c / 10;
    c %= 10;
    digits[2] = c;
    RequestDma3Copy(gUnk_096B2124 + digits[0] * 32, (void*)(BG_VRAM + 10 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + digits[1] * 32, (void*)(BG_VRAM + 11 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + digits[2] * 32, (void*)(BG_VRAM + 12 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + digits[0] * 32, (void*)(BG_VRAM + 13 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + digits[1] * 32, (void*)(BG_VRAM + 14 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + digits[2] * 32, (void*)(BG_VRAM + 15 * TILE_SIZE_4BPP), 32);

    digits[0] = e / 1000;
    e %= 1000;
    digits[1] = e / 100;
    e %= 100;
    digits[2] = e / 10;
    e %= 10;
    digits[3] = e;
    RequestDma3Copy(gUnk_096B2124 + digits[0] * 32, (void*)(BG_VRAM + 16 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + digits[1] * 32, (void*)(BG_VRAM + 17 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + digits[2] * 32, (void*)(BG_VRAM + 18 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + digits[3] * 32, (void*)(BG_VRAM + 19 * TILE_SIZE_4BPP), 32);

    digits[0] = g / 1000;
    g %= 1000;
    digits[1] = g / 100;
    g %= 100;
    digits[2] = g / 10;
    g %= 10;
    digits[3] = g;
    RequestDma3Copy(gUnk_096B2124 + digits[0] * 32, (void*)(BG_VRAM + 20 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + digits[1] * 32, (void*)(BG_VRAM + 21 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + digits[2] * 32, (void*)(BG_VRAM + 22 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + digits[3] * 32, (void*)(BG_VRAM + 23 * TILE_SIZE_4BPP), 32);

    digits[0] = b / 100;
    b %= 100;
    digits[1] = b / 10;
    b %= 10;
    digits[2] = b;
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[1] * 32, (void*)(BG_VRAM + 31 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[2] * 32, (void*)(BG_VRAM + 32 * TILE_SIZE_4BPP), 32);

    digits[0] = d / 100;
    d %= 100;
    digits[1] = d / 10;
    d %= 10;
    digits[2] = d;
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[0] * 32, (void*)(BG_VRAM + 33 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[1] * 32, (void*)(BG_VRAM + 34 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[2] * 32, (void*)(BG_VRAM + 35 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[0] * 32, (void*)(BG_VRAM + 36 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[1] * 32, (void*)(BG_VRAM + 37 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[2] * 32, (void*)(BG_VRAM + 38 * TILE_SIZE_4BPP), 32);

    digits[0] = f / 1000;
    f %= 1000;
    digits[1] = f / 100;
    f %= 100;
    digits[2] = f / 10;
    f %= 10;
    digits[3] = f;
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[0] * 32, (void*)(BG_VRAM + 39 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[1] * 32, (void*)(BG_VRAM + 40 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[2] * 32, (void*)(BG_VRAM + 41 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[3] * 32, (void*)(BG_VRAM + 42 * TILE_SIZE_4BPP), 32);

    digits[0] = h / 1000;
    h %= 1000;
    digits[1] = h / 100;
    h %= 100;
    digits[2] = h / 10;
    h %= 10;
    digits[3] = h;
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[0] * 32, (void*)(BG_VRAM + 43 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[1] * 32, (void*)(BG_VRAM + 44 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[2] * 32, (void*)(BG_VRAM + 45 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[3] * 32, (void*)(BG_VRAM + 46 * TILE_SIZE_4BPP), 32);
}

void SioApplyBattleSettings() {
    s8* base;
    s8* p;
    GameState* gs;
    SioWorldEntry* table;
    SioWorldEntry* entry;

    base = gSioWorldList;
    p = base + gSioWorldCursor;
    gs = &gGameState;
    table = gSioWorldEntries;
    entry = &table[*p];

    gs->battleStage = entry->world;
    gSioSavedWorld = gs->world;
    gs->world = entry->world;

    if (gSioPlayerId == 0) {
        gCharaLinkSend.ap += gSioHandicapAp[sSioBtlOptionWork->handicaps[0]];
        gCharaLinkRecv.ap += gSioHandicapAp[sSioBtlOptionWork->handicaps[1]];
    } else {
        gCharaLinkSend.ap += gSioHandicapAp[sSioBtlOptionWork->handicaps[1]];
        gCharaLinkRecv.ap += gSioHandicapAp[sSioBtlOptionWork->handicaps[0]];
    }

    gGameState.linkMaxHp = gCharaLinkSend.maxHp;
    gGameState.linkAp = gCharaLinkSend.ap;
    gGameState.linkLevel = gCharaLinkSend.level;
    gGameState.linkLearnedStocks = gCharaLinkSend.learnedStocks;
    gGameState.linkLearnedStocks2 = gCharaLinkSend.learnedStocks2;
    gGameState.linkPartnerMaxHp = gCharaLinkRecv.maxHp;
    gGameState.linkPartnerAp = gCharaLinkRecv.ap;
    gGameState.linkPartnerLevel = gCharaLinkRecv.level;
    gGameState.linkPartnerLearnedStocks = gCharaLinkRecv.learnedStocks;
    gGameState.linkPartnerLearnedStocks2 = gCharaLinkRecv.learnedStocks2;
}

void SioBtlOptionSyncHandicaps() {
    u8 buf[2];

#ifdef VERSION_EU
    if (!gSioDebugMode) {
#endif
    if (gSioPlayerId == 0) {
        gSioCommandSend[2] |= (gSioHandicaps[0] & 15) << 4;
    } else {
        gSioCommandSend[2] |= (gSioHandicaps[1] & 15) << 4;
    }

    buf[0] = (gSioCommandRecv[2][0] & 0xF0) >> 4;
    buf[1] = (gSioCommandRecv[2][1] & 0xF0) >> 4;

    if (buf[0] >= 1 && buf[0] <= 11) {
        sSioBtlOptionWork->handicaps[0] = buf[0];
        gSioHandicaps[0] = sSioBtlOptionWork->handicaps[0];
    }

    if (buf[1] >= 1 && buf[1] <= 11) {
        sSioBtlOptionWork->handicaps[1] = buf[1];
        gSioHandicaps[1] = sSioBtlOptionWork->handicaps[1];
    }

    SioBtlOptionUpdateHandicapGauges(sSioBtlOptionWork->handicaps[0], sSioBtlOptionWork->handicaps[1]);
#ifdef VERSION_EU
    } else {
    buf[0] = gSioHandicaps[0];
    buf[1] = gSioHandicaps[1];

    if (buf[0] >= 1 && buf[0] <= 11) {
        sSioBtlOptionWork->handicaps[0] = buf[0];
    }

    if (buf[1] >= 1 && buf[1] <= 11) {
        sSioBtlOptionWork->handicaps[1] = buf[1];
    }

    SioBtlOptionUpdateHandicapGauges(sSioBtlOptionWork->handicaps[0], sSioBtlOptionWork->handicaps[1]);
    }
#endif
}

void SioBtlOptionUpdateHandicapGauges(u16 a, u16 b) {
    switch (a) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        LoadPalette(gUnk_096FBD64, (void*)(sSioBtlOptionWork->palette5[0]->index * 32 + OBJ_PLTT), 32);
        LoadPalette(gUnk_096FBD64 + 0x11, (void*)(sSioBtlOptionWork->palette5[0]->index * 32 + OBJ_PLTT + 2), (6 - a) * 2);
        break;
    case 6:
        LoadPalette(gUnk_096FBD64, (void*)(sSioBtlOptionWork->palette5[0]->index * 32 + OBJ_PLTT), 32);
        break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        LoadPalette(gUnk_096FBD64, (void*)(sSioBtlOptionWork->palette5[0]->index * 32 + OBJ_PLTT), 32);
        LoadPalette(gUnk_096FBD64 + 0x16, (void*)(sSioBtlOptionWork->palette5[0]->index * 32 + OBJ_PLTT + 0xC), (a - 6) * 2);
        break;
    }

    switch (b) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        LoadPalette(gUnk_096FBDA4, (void*)(sSioBtlOptionWork->palette5[1]->index * 32 + OBJ_PLTT), 32);
        LoadPalette(gUnk_096FBDA4 + 0x11, (void*)(sSioBtlOptionWork->palette5[1]->index * 32 + OBJ_PLTT + 2), (6 - b) * 2);
        break;
    case 6:
        LoadPalette(gUnk_096FBDA4, (void*)(sSioBtlOptionWork->palette5[1]->index * 32 + OBJ_PLTT), 32);
        break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        LoadPalette(gUnk_096FBDA4, (void*)(sSioBtlOptionWork->palette5[1]->index * 32 + OBJ_PLTT), 32);
        LoadPalette(gUnk_096FBDA4 + 0x16, (void*)(sSioBtlOptionWork->palette5[1]->index * 32 + OBJ_PLTT + 0xC), (b - 6) * 2);
        break;
    }
}

void SioBtlOptionCancelReady() {
    sSioBtlOptionWork->messageVisible = 0;
    RequestDma3Copy(gUnk_096B2664, (void*)(BG_VRAM + TILE_SIZE_4BPP), 0xC0);
    RequestDma3Copy(gUnk_096B2664 + 0x400, (void*)(BG_VRAM + 24 * TILE_SIZE_4BPP), 0xC0);
    sSioBtlOptionWork->player1Ready = 0;
    sSioBtlOptionWork->player2Ready = 0;
    SetSioBtlOptionAnimation(0, 0, 0);
    SetSioBtlOptionAnimation(1, 0, 0);
}

void SioBtlOptionPlayWorldBgm() {
    s8 i = gSioWorldList[gSioWorldCursor];

    switch (i) {
    case 1:
        m4aSongNumStart(SONG_BGM_ALADDIN_BATTLE);
        break;
    case 2:
        m4aSongNumStart(SONG_BGM_MARMAID_BATTLE);
        break;
    case 3:
        m4aSongNumStart(SONG_BGM_HERCULES_BATTLE);
        break;
    case 4:
        m4aSongNumStart(SONG_BGM_ALICE_BTL);
        break;
    case 5:
        m4aSongNumStart(SONG_BGM_PINOCCHIO_BTL);
        break;
    case 6:
        m4aSongNumStart(SONG_BGM_HALLOWEEN_BTL);
        break;
    case 7:
        m4aSongNumStart(SONG_BGM_PETERPAN_BTL);
        break;
    case 8:
        m4aSongNumStart(SONG_BGM_HOLLOW_BATTLE);
        break;
    case 9:
        m4aSongNumStart(SONG_BGM_DESTINY_BATTLE);
        break;
    case 10:
        m4aSongNumStart(SONG_BGM_TOWN_BTL);
        break;
    case 11:
        m4aSongNumStart(SONG_BGM_TWILIGHT_BATTLE);
        break;
    case 12:
        m4aSongNumStart(SONG_BGM_F13F_FORGET_BATTLE);
        break;
    }
}

void mode_sio_btl_cardget_0(s32 arg) {
#ifdef VERSION_EU
    if (!gSioDebugMode) {
        gSystemFlags |= SYSTEM_FLAG_DMA3_FLUSH_CPU;
    }
#else
    gSystemFlags |= SYSTEM_FLAG_DMA3_FLUSH_CPU;
#endif

    if (gLinkDecksAllocated == 1) {
        FreeLinkDecks();
        gLinkDecksAllocated = 0;
    }

    sSioBtlCardgetWork = EwramAlloc(sizeof(SioBtlCardgetWork));

    if (arg == 0) {
        sSioBtlCardgetWork->lost = 0;
    } else {
        sSioBtlCardgetWork->lost = 1;
    }

    SetBgMode0();
    SetupBg(1, 0, 16, 0);
    SetBgPriority(1, 1);
    SetupBg(2, 0, 24, 0);
    SetBgPriority(2, 2);
    RequestDma3Copy(gUnk_096AD744, GetBgCharBase(1), 0x2000);
    sSioBtlCardgetWork->state = 0;
}

void SioBtlCardgetLoadBgTiles() {
    RequestDma3Copy(gUnk_096AF744, (u8*)GetBgCharBase(1) + 0x2000, 0x2000);
}

void SioBtlCardgetLoadBg() {
#ifdef VERSION_EU
    RequestDma3Copy(gUnk_096B1744, (u8*)GetBgCharBase(1) + 0x4000, 0x2000);
#else
    RequestDma3Copy(gUnk_096B1744, (u8*)GetBgCharBase(1) + 0x4000, 0x9E0);
#endif
    LoadBgPalette(1, gUnk_096FBAC4, 0x200);

#ifdef VERSION_EU
    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        LoadBgMap(1, gUnk_096F7C64, 0x800);
        break;
    case LANGUAGE_ITALIAN:
        LoadBgMap(1, gUnkEu_096C698C, 0x800);
        break;
    case LANGUAGE_FRENCH:
        LoadBgMap(1, gUnkEu_096C598C, 0x800);
        break;
    case LANGUAGE_SPANISH:
        LoadBgMap(1, gUnkEu_096C618C, 0x800);
        break;
    case LANGUAGE_GERMAN:
    default:
        LoadBgMap(1, gUnkEu_096C718C, 0x800);
        break;
    }
#else
    LoadBgMap(1, gUnk_096F7C64, 0x800);
#endif
    DisableBg(1);
}

void SioBtlCardgetShowResult() {
    FadeStartIn(FADE_MODE_BLACK, 16);
    DisableBg(0);
    EnableBg(1);
    EnableBg(2);
    DisableBg(3);

    if (!sSioBtlCardgetWork->lost) {
        gSioWinCount++;

        if (gSioWinCount > 0x270F) {
            gSioWinCount = 0x270F;
        }

        if (gSioPlayerId == 0) {
            SioBtlCardgetLoad1PWin();
            sSioBtlCardgetWork->palette = LoadObjPalette(gSoraPalette, 32);
            sSioBtlCardgetWork->palette2 = LoadObjPalette(gUnk_096FAC64, 32);
        } else {
            SioBtlCardgetLoad2PWin();
            sSioBtlCardgetWork->palette = LoadObjPalette(gUnk_096FAC64, 32);
            sSioBtlCardgetWork->palette2 = LoadObjPalette(gSoraPalette, 32);
        }
    } else {
        gSioLoseCount++;

        if (gSioLoseCount > 0x270F) {
            gSioLoseCount = 0x270F;
        }

        if (gSioPlayerId == 0) {
            SioBtlCardgetLoad2PWin();
            sSioBtlCardgetWork->palette = LoadObjPalette(gSoraPalette, 32);
            sSioBtlCardgetWork->palette2 = LoadObjPalette(gUnk_096FAC64, 32);
        } else {
            SioBtlCardgetLoad1PWin();
            sSioBtlCardgetWork->palette = LoadObjPalette(gUnk_096FAC64, 32);
            sSioBtlCardgetWork->palette2 = LoadObjPalette(gSoraPalette, 32);
        }
    }

    if (gSioPlayerId == 0) {
        sSioBtlCardgetWork->unk_20 = 0x3C00;
        sSioBtlCardgetWork->unk_24 = 0x6000;
    } else {
        sSioBtlCardgetWork->unk_20 = 0xB400;
        sSioBtlCardgetWork->unk_24 = 0x6000;
    }

    sSioBtlCardgetWork->unk_02 = 0;
    sSioBtlCardgetWork->timer = 0;
    gGameState.hp = gCharaLinkSend.hp;
    gGameState.world = gSioSavedWorld;
}

void mode_sio_btl_cardget_1() {
#ifdef VERSION_EU
    SioBtlCardgetWork* work;
#endif

    switch (sSioBtlCardgetWork->state) {
    case 0:
        SioBtlCardgetLoadBgTiles();
        sSioBtlCardgetWork->state++;
        break;
    case 1:
        SioBtlCardgetLoadBg();
        sSioBtlCardgetWork->state++;
        break;
    case 2:
        SioBtlCardgetShowResult();
        sSioBtlCardgetWork->state++;
        break;
    case 3:
        sSioBtlCardgetWork->timer++;

        if (sSioBtlCardgetWork->timer > 4) {
            sSioBtlCardgetWork->timer = 0;

#ifdef VERSION_EU
            if (!gSioDebugMode) {
#endif
            SioSetLinkCallbacks(SioCommandSend, SioCommandRecv);
            SioCommandReset();
#ifdef VERSION_EU
            }
#endif

            sSioBtlCardgetWork->state++;
        }

        SioBtlCardgetDraw();
        break;
    case 4:
        sSioBtlCardgetWork->timer++;

        if (sSioBtlCardgetWork->timer > 4) {
            sSioBtlCardgetWork->timer = 0;
            sSioBtlCardgetWork->state++;
        }

        SioBtlCardgetDraw();
        break;
    case 5:
#ifdef VERSION_EU
        if (!gSioDebugMode) {
#endif
        if (GetKeysPressed() & (A_BUTTON | B_BUTTON | START_BUTTON)) {
            gSioCommandSend[1] = 0x45FC;
        }

        if (gSioCommandRecv[1][0] == 0x45FC || gSioCommandRecv[1][1] == 0x45FC) {
            m4aSongNumStart(SONG_SYS_ITEMGET);
            sSioBtlCardgetWork->timer = 0;
            sSioBtlCardgetWork->state++;
        }

#ifdef VERSION_EU
        } else if (GetKeysPressed() & (A_BUTTON | B_BUTTON | START_BUTTON)) {
            m4aSongNumStart(SONG_SYS_ITEMGET);
            sSioBtlCardgetWork->timer = 0;
            sSioBtlCardgetWork->state++;
        }
#endif

        SioBtlCardgetDraw();
        break;
    case 6:
        sSioBtlCardgetWork->timer++;

        if (sSioBtlCardgetWork->timer > 4) {
#ifdef VERSION_EU
            work = sSioBtlCardgetWork;

            if (!gSioDebugMode) {
#endif
            SioSetLinkCallbacks(SioExchangeSend, SioExchangeRecv);
            SioPrepareCharaLinkExchange();
#ifdef VERSION_EU
                work = sSioBtlCardgetWork;
            }

            work->state++;
#else
            sSioBtlCardgetWork->state++;
#endif
        }

        SioBtlCardgetDraw();
        break;
    case 7:
#ifdef VERSION_EU
        if (!gSioDebugMode) {
#endif
        if (gSioLinkResult == 2) {
            sSioBtlCardgetWork->timer = 0;
            sSioBtlCardgetWork->state++;
        }

#ifdef VERSION_EU
        } else {
            sSioBtlCardgetWork->timer = 0;
            sSioBtlCardgetWork->state++;
        }
#endif

        SioBtlCardgetDraw();
        break;
    case 8:
        sSioBtlCardgetWork->timer++;

        if (sSioBtlCardgetWork->timer > 4) {
#ifdef VERSION_EU
            work = sSioBtlCardgetWork;

            if (!gSioDebugMode) {
#endif
            SioSetLinkCallbacks(SioCommandSend, SioCommandRecv);
            SioCommandReset();
#ifdef VERSION_EU
                work = sSioBtlCardgetWork;
            }

            work->state++;
#else
            sSioBtlCardgetWork->state++;
#endif
        }

        SioBtlCardgetDraw();
        break;
    case 9:
        ModeRequestHeapReset(&gModeSioBtlOption, 0);
        sSioBtlCardgetWork->state++;
        break;
    }
}

void mode_sio_btl_cardget_2() {
}

void SioBtlCardgetDraw() {
    DrawSprite(60, 116, sSioBtlCardgetWork->gfx, sSioBtlCardgetWork->tiles, sSioBtlCardgetWork->palette, NULL, 0, 0xFFF0);
    DrawSprite(180, 116, sSioBtlCardgetWork->gfx2, sSioBtlCardgetWork->tiles2, sSioBtlCardgetWork->palette2, NULL, 0, 0xFFF0);
#ifdef VERSION_JP
    DrawSprite(28, 36, sSioBtlCardgetWork->gfx3, sSioBtlCardgetWork->tiles3, sSioBtlCardgetWork->palette3, NULL, 0, 0xFF00);
#else
    DrawSprite(13, 36, sSioBtlCardgetWork->gfx3, sSioBtlCardgetWork->tiles3, sSioBtlCardgetWork->palette3, NULL, 0, 0xFF00);
#endif
#ifdef VERSION_JP
    DrawSprite(148, 36, sSioBtlCardgetWork->gfx4, sSioBtlCardgetWork->tiles4, sSioBtlCardgetWork->palette4, NULL, 0, 0xFF00);
#else
    DrawSprite(135, 36, sSioBtlCardgetWork->gfx4, sSioBtlCardgetWork->tiles4, sSioBtlCardgetWork->palette4, NULL, 0, 0xFF00);
#endif
}

void SioBtlCardgetLoad1PWin() {
    LoadBgMap(2, gUnk_096F8C64, 0x800);
    sSioBtlCardgetWork->tiles = AllocObjTiles(0xC80, gSor1ff00Tiles);
    sSioBtlCardgetWork->gfx = gSor1ff00Frames[18];
    sSioBtlCardgetWork->tiles2 = AllocObjTiles(0xC80, gSor1fl26Tiles);
    sSioBtlCardgetWork->gfx2 = gSor1fl26Frames[6];
#ifdef VERSION_EU
    sSioBtlCardgetWork->palette3 = LoadObjPalette(gUnk_096FBDE4, 32);
    sSioBtlCardgetWork->palette4 = LoadObjPalette(gUnk_096FBE04, 32);

    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        sSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095ECDD8, 0x680);
        sSioBtlCardgetWork->gfx3 = gUnkEu_09F7EB28[0];
        sSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095ED472, 0x600);
        sSioBtlCardgetWork->gfx4 = gUnkEu_09F7EB30[0];
        break;
    case LANGUAGE_FRENCH:
        sSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F5550, 0x640);
        sSioBtlCardgetWork->gfx3 = gUnkEu_09F7EBD8[0];
        sSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F5BB0, 0x580);
        sSioBtlCardgetWork->gfx4 = gUnkEu_09F7EBE0[0];
        break;
    case LANGUAGE_SPANISH:
        sSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F6150, 0x640);
        sSioBtlCardgetWork->gfx3 = gUnkEu_09F7EBE8[0];
        sSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F67B0, 0x580);
        sSioBtlCardgetWork->gfx4 = gUnkEu_09F7EBF0[0];
        break;
    case LANGUAGE_ITALIAN:
        sSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F6D50, 0x640);
        sSioBtlCardgetWork->gfx3 = gUnkEu_09F7EBF8[0];
        sSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F73AA, 0x600);
        sSioBtlCardgetWork->gfx4 = gUnkEu_09F7EC00[0];
        break;
    case LANGUAGE_GERMAN:
    default:
        sSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F79D2, 0x5C0);
        sSioBtlCardgetWork->gfx3 = gUnkEu_09F7EC08[0];
        sSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F7FAE, 0x600);
        sSioBtlCardgetWork->gfx4 = gUnkEu_09F7EC10[0];
        break;
    }
#else
#ifdef VERSION_JP
    sSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnk_0962CAFC, 0x500);
#else
    sSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnk_0962CAFC, 0x680);
#endif
    sSioBtlCardgetWork->palette3 = LoadObjPalette(gUnk_096FBDE4, 32);
    sSioBtlCardgetWork->gfx3 = gUnk_09EF38DC[0];
#ifdef VERSION_JP
    sSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnk_0962D196, 0x480);
#else
    sSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnk_0962D196, 0x600);
#endif
    sSioBtlCardgetWork->palette4 = LoadObjPalette(gUnk_096FBE04, 32);
    sSioBtlCardgetWork->gfx4 = gUnk_09EF38E4[0];
#endif
}

void SioBtlCardgetLoad2PWin() {
    LoadBgMap(2, gUnk_096F8464, 0x800);
    sSioBtlCardgetWork->tiles = AllocObjTiles(0xC80, gSor1fl26Tiles);
    sSioBtlCardgetWork->gfx = gSor1fl26Frames[6];
    sSioBtlCardgetWork->tiles2 = AllocObjTiles(0xC80, gSor1ff00Tiles);
    sSioBtlCardgetWork->gfx2 = gSor1ff00Frames[18];
#ifdef VERSION_EU
    sSioBtlCardgetWork->palette3 = LoadObjPalette(gUnk_096FBE04, 32);
    sSioBtlCardgetWork->palette4 = LoadObjPalette(gUnk_096FBDE4, 32);

    switch (gLanguage) {
    case LANGUAGE_ENGLISH:
        sSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095ED472, 0x600);
        sSioBtlCardgetWork->gfx3 = gUnkEu_09F7EB30[0];
        sSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095ECDD8, 0x680);
        sSioBtlCardgetWork->gfx4 = gUnkEu_09F7EB28[0];
        break;
    case LANGUAGE_FRENCH:
        sSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F5BB0, 0x580);
        sSioBtlCardgetWork->gfx3 = gUnkEu_09F7EBE0[0];
        sSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F5550, 0x640);
        sSioBtlCardgetWork->gfx4 = gUnkEu_09F7EBD8[0];
        break;
    case LANGUAGE_SPANISH:
        sSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F67B0, 0x580);
        sSioBtlCardgetWork->gfx3 = gUnkEu_09F7EBF0[0];
        sSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F6150, 0x640);
        sSioBtlCardgetWork->gfx4 = gUnkEu_09F7EBE8[0];
        break;
    case LANGUAGE_ITALIAN:
        sSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F73AA, 0x600);
        sSioBtlCardgetWork->gfx3 = gUnkEu_09F7EC00[0];
        sSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F6D50, 0x640);
        sSioBtlCardgetWork->gfx4 = gUnkEu_09F7EBF8[0];
        break;
    case LANGUAGE_GERMAN:
    default:
        sSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F7FAE, 0x600);
        sSioBtlCardgetWork->gfx3 = gUnkEu_09F7EC10[0];
        sSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F79D2, 0x5C0);
        sSioBtlCardgetWork->gfx4 = gUnkEu_09F7EC08[0];
        break;
    }
#else
#ifdef VERSION_JP
    sSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnk_0962D196, 0x480);
#else
    sSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnk_0962D196, 0x600);
#endif
    sSioBtlCardgetWork->palette3 = LoadObjPalette(gUnk_096FBE04, 32);
    sSioBtlCardgetWork->gfx3 = gUnk_09EF38E4[0];
#ifdef VERSION_JP
    sSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnk_0962CAFC, 0x500);
#else
    sSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnk_0962CAFC, 0x680);
#endif
    sSioBtlCardgetWork->palette4 = LoadObjPalette(gUnk_096FBDE4, 32);
    sSioBtlCardgetWork->gfx4 = gUnk_09EF38DC[0];
#endif
}

#ifndef VERSION_EU
void mode_sio_chg_connect_0(s32 arg) {
    sSioChgConnectWork = EwramAlloc(sizeof(SioBtlConnectWork));
    FadeStartIn(FADE_MODE_BLACK, 16);
    SetBgMode0();
    SetupBg(0, 0, 7, 15);
    SetupBg(1, 1, 31, 0);
    EnableBg(0);
    EnableBg(1);
    LoadBgTiles(0, gUnk_096AD604, 0x140);
    LoadBgMap(0, gUnk_096F6464, 0x800);
    LoadBgPalette(0, gCard00Palette, 0x20);
    LoadBgTiles(1, gUnk_096ACA44, 0xBC0);
    LoadBgPalette(1, gUnk_096FBA04, 0x40);
    LoadBgMap(1, gUnk_096F5C64, 0x800);
    sSioChgConnectWork->unk_00 = 0;
    sSioChgConnectWork->timer = 0;
    sSioChgConnectWork->state = 0;
    sSioChgConnectWork->textSlotCount = 0;
    InitTextSlots(sSioChgConnectWork->textSlots, 0x5A);
    sSioChgConnectWork->textSlotCount = LoadTextSlots(gUnk_08159EC4, sSioChgConnectWork->textSlots);
    sSioChgConnectWork->palette = LoadObjPalette(gUnk_096FBAA4, 32);
    SioReset();
    SioConnectInit(SioChgConnectOnConnect, SioChgConnectOnCancel, 1);
}
#endif

#ifndef VERSION_EU
void mode_sio_chg_connect_1() {
    switch (sSioChgConnectWork->state) {
    case 0:
        SioConnectUpdate();
        break;
    case 1:
        SioConnectUpdate();
        sSioChgConnectWork->timer++;

        if (sSioChgConnectWork->timer > 4) {
            SioSetLinkCallbacks(SioCommandSend, SioCommandRecv);
            SioCommandReset();
            gSystemFlags |= SYSTEM_FLAG_LINK_ACTIVE;
            gSystemFlags |= SYSTEM_FLAG_DMA3_FLUSH_CPU;
            SioChgConnectStartTrade();
            return;
        }

        break;
    }

    DrawTextSlots(61, 68, sSioChgConnectWork->textSlots, sSioChgConnectWork->palette, 20, sSioChgConnectWork->textSlotCount);
}
#endif

#ifndef VERSION_EU
void mode_sio_chg_connect_2() {
    ReleaseObjPalette(sSioChgConnectWork->palette);
    FreeTextSlots(sSioChgConnectWork->textSlots, 0x5A);
    EwramFree(sSioChgConnectWork);
}
#endif

#ifndef VERSION_EU
void SioChgConnectOnConnect() {
    m4aSongNumStart(SONG_SYS_ITEMGET);
    sSioChgConnectWork->state++;
}
#endif

#ifndef VERSION_EU
void SioChgConnectOnCancel() {
    m4aSongNumStart(SONG_SYS_CLOSE);
    ModeRequest(&gModeSioBattle, 3);
}
#endif

#ifndef VERSION_EU
void SioChgConnectStartTrade() {
    s32 i;

    if (gSioPlayerId == 0) {
        gSioChgCardCursor = 0;
    } else {
        gSioChgCardCursor = 5;
    }

    for (i = 0; i < 10; i++) {
        gSioChgCardSlots[i] = 0x800;
    }

    for (i = 0; i < 2; i++) {
        gSioChgCardReady[i] = 0;
    }

    ModeRequest(&gModeSioChgCard, 0x800);
}
#endif

#ifndef VERSION_EU
void SetSioChgCardAnimation(u16 a, u16 b, u16 c) {
    const SioAnimDef* def = &gSioChgCardAnimDefs[b];
    AnimChangeWithTables(&sSioChgCardWork->anim[a], def->animId, c, def->anims, def->gfxTable);
    SetObjTileSource(sSioChgCardWork->playerTilesPalettes[a], def->tiles);
}
#endif

#ifndef VERSION_EU
void mode_sio_chg_card_0(s32 arg) {
    sSioChgCardWork = EwramAlloc(sizeof(SioChgCardWork));
    SetBgMode0();
    SetupBg(0, 0, 7, 0);
    SetBgPriority(0, 0);
    SetBgOverflow(0, 1);
    SetBgSize(0, 0);
    SetupBg(1, 0, 15, 0);
    SetBgPriority(1, 1);
    SetBgOverflow(1, 1);
    SetBgSize(1, 0);
    SetupBg(2, 0, 24, 0);
    SetBgPriority(2, 2);
    SetBgOverflow(2, 1);
    SetBgSize(2, 0);
    RequestDma3Copy(gUnk_096B2BE4, GetBgCharBase(0), 0x2000);
    DisableBg(0);
    DisableBg(1);
    DisableBg(2);
    sSioChgCardWork->blinkPhase = 0;
    sSioChgCardWork->timer = 0;
    sSioChgCardWork->ready = 0;
    sSioChgCardWork->state = 0;
    sSioChgCardWork->receiveOk = 0;
    sSioChgCardWork->leaveDelay = 0;
    sSioChgCardWork->offeredCard = arg;
    gSioCommandSend[3] = ((gSioChgCardCursor & 15) << 12) | ((arg + 1) & 0x0FFF);
}
#endif

#ifndef VERSION_EU
void SioChgCardLoadBg() {
    RequestDma3Copy(gUnk_096B4BE4, (u8*)GetBgCharBase(0) + 0x2000, 0x11C0);
    LoadBgPalette(0, gUnk_096FBE24, 0xE0);
    LoadBgMap(0, gUnk_096FA464, 0x800);
    DisableBg(0);
    DisableBg(1);
    DisableBg(2);
    gSioCommandSend[3] = ((gSioChgCardCursor & 15) << 12) | ((sSioChgCardWork->offeredCard + 1) & 0x0FFF);
    sSioChgCardWork->state++;
}
#endif

#ifndef VERSION_EU
void SioChgCardInitObjs() {
    s32 i;
    s16 n;
    FadeStartIn(FADE_MODE_BLACK, 16);
    LoadBgMap(1, gUnk_096F9C64, 0x800);
    LoadBgMap(2, gUnk_096F9464, 0x800);
    DisableBg(0);
    EnableBg(1);
    EnableBg(2);
    sSioChgCardWork->cursor = gSioChgCardCursor;
    sSioChgCardWork->x = gSioChgCardSlotPos[sSioChgCardWork->cursor].x;
    sSioChgCardWork->y = gSioChgCardSlotPos[sSioChgCardWork->cursor].y;
    sSioChgCardWork->nextCursor = sSioChgCardWork->cursor;
    sSioChgCardWork->cursorVisible = 1;

    for (i = 0; i < 2; i++) {
        sSioChgCardWork->playerTilesPalettes[i] = AllocObjTiles(0xC80, NULL);
        AnimInit(&sSioChgCardWork->anim[i], NULL, NULL);

        if (gSioChgCardReady[i] == 0) {
            SetSioChgCardAnimation(i, 0, 0);
        } else {
            SetSioChgCardAnimation(i, 2, 0);
        }

        sSioChgCardWork->gfx[i] = AnimGetGfx(&sSioChgCardWork->anim[i]);
    }

    if (gSioPlayerId == 0) {
        sSioChgCardWork->playerTilesPalettes[2] = LoadObjPalette(gSoraPalette, 32);
        sSioChgCardWork->playerTilesPalettes[3] = LoadObjPalette(gUnk_096FAC64, 32);
    } else {
        sSioChgCardWork->playerTilesPalettes[2] = LoadObjPalette(gUnk_096FAC64, 32);
        sSioChgCardWork->playerTilesPalettes[3] = LoadObjPalette(gSoraPalette, 32);
    }

    sSioChgCardWork->tiles = LoadObjTiles(gUnk_0962DEA8, 0x780);
    sSioChgCardWork->palette = LoadObjPalette(gUnk_096FBF04, 32);
    AnimInit(&sSioChgCardWork->anim2, gUnk_09EF3920, gUnk_09EF390C);
    AnimStart(&sSioChgCardWork->anim2, 0, ANIM_FLAG_LOOP);
    sSioChgCardWork->gfx2 = AnimGetGfx(&sSioChgCardWork->anim2);
    sSioChgCardWork->tiles2 = LoadObjTiles(gUnk_0962B090, 0x1C0);
    sSioChgCardWork->palette2 = LoadObjPalette(gUnk_096FBAA4, 32);
    AnimInit(&sSioChgCardWork->anim3, gUnk_09EF38B4, gUnk_09EF3894);
    AnimStart(&sSioChgCardWork->anim3, 0, ANIM_FLAG_LOOP);
    sSioChgCardWork->gfx3 = AnimGetGfx(&sSioChgCardWork->anim3);

    for (i = 0; i < 10; i++) {
        if (gSioChgCardSlots[i] == 0x800) {
            sSioChgCardWork->cardVisible[i] = 0;
            sSioChgCardWork->x2[i] = gSioChgCardSlotPos[i].x << 8;
            sSioChgCardWork->y2[i] = gSioChgCardSlotPos[i].y << 8;
            sSioChgCardWork->tiles3[i] = LoadObjTiles(gCardDefs[CARD_ID(CARD_KINGDOM_KEY, 0)].tiles2, 0x200);
            sSioChgCardWork->palette3[i] = LoadObjPalette(gCardDefs[CARD_ID(CARD_KINGDOM_KEY, 0)].palette2, 32);
            sSioChgCardWork->gfx4[i] = gCardDefs[CARD_ID(CARD_KINGDOM_KEY, 0)].gfx2;
            sSioChgCardWork->gfx5[i] = gUnk_09EE981C[0];
            sSioChgCardWork->scaleX[i] = 0x100;
            sSioChgCardWork->scaleY[i] = 0x100;
            sSioChgCardWork->angle[i] = 0;
        } else {
            sSioChgCardWork->cardVisible[i] = 1;
            sSioChgCardWork->x2[i] = gSioChgCardSlotPos[i].x << 8;
            sSioChgCardWork->y2[i] = gSioChgCardSlotPos[i].y << 8;
            n = gSioChgCardSlots[i];
            sSioChgCardWork->tiles3[i] = LoadObjTiles(gCardDefs[n].tiles2, 0x200);
            sSioChgCardWork->palette3[i] = LoadObjPalette(gCardDefs[n].palette2, 32);
            sSioChgCardWork->gfx4[i] = gCardDefs[n].gfx2;
            sSioChgCardWork->gfx5[i] = gUnk_09EE981C[gCardDefs[n].value];
            sSioChgCardWork->scaleX[i] = 0x100;
            sSioChgCardWork->scaleY[i] = 0x100;
            sSioChgCardWork->angle[i] = 0;
        }
    }

    sSioChgCardWork->tiles4 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    sSioChgCardWork->palette4 = LoadObjPalette(gCard00Palette, 32);
    sSioChgCardWork->tiles5 = LoadObjTiles(gUnk_093F8C8E, 0xC00);
    sSioChgCardWork->gfx6 = gUnk_09EF1278[0];
    sSioChgCardWork->messageVisible = 0;
    InitTextSlots(sSioChgCardWork->textSlots, 42);
    sSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815A394, sSioChgCardWork->textSlots);
    sSioChgCardWork->x3 = 68;
    sSioChgCardWork->y3 = 124;
    InitTextSlots(sSioChgCardWork->textSlots2, 20);
    sSioChgCardWork->textSlotCount2 = LoadTextSlots(gCardDefs[CARD_ID(CARD_KINGDOM_KEY, 0)].name, sSioChgCardWork->textSlots2);
    sSioChgCardWork->cardInfoVisible = 0;
    TaskPoolInit(&sSioChgCardWork->tasks, 11);
    gSioCommandSend[3] = ((gSioChgCardCursor & 15) << 12) | ((sSioChgCardWork->offeredCard + 1) & 0x0FFF);
    sSioChgCardWork->state++;
}
#endif

#ifndef VERSION_EU
void mode_sio_chg_card_1() {
    switch (sSioChgCardWork->state) {
    case 0:
        SioChgCardLoadBg();
        break;
    case 1:
        SioChgCardInitObjs();
        break;
    case 2:
        SioChgCardWaitStart();
        SioChgCardDraw();
        break;
    case 3:
        SioChgCardSelect();
        SioChgCardDraw();
        break;
    case 4:
        SioChgCardConfirm();
        SioChgCardDraw();
        break;
    case 5:
        SioChgCardTryTrade();
        SioChgCardDraw();
        break;
    case 6:
        SioChgCardWaitTradeResult();
        SioChgCardDraw();
        break;
    case 7:
        SioChgCardTradeFailed();
        SioChgCardDraw();
        break;
    case 8:
        SioChgCardStartMove();
        SioChgCardDraw();
        break;
    case 9:
        SioChgCardSave();
        SioChgCardDraw();
        break;
    case 10:
        SioChgCardWaitMove();
        SioChgCardDraw();
        break;
    case 11:
        SioChgCardShowSecondMessage();
        SioChgCardDraw();
        break;
    case 12:
        SioChgCardHideMessage();
        SioChgCardDraw();
        break;
    case 13:
        SioChgCardRestart();
        SioChgCardDraw();
        break;
    }
}

void SioChgCardWaitStart() {
    sSioChgCardWork->timer++;

    if (sSioChgCardWork->timer > 5) {
        SioChgCardRecvSlots();
        SioChgCardDrawPointTotals();
        sSioChgCardWork->state++;
    }

    gSioCommandSend[3] = ((gSioChgCardCursor & 15) << 12) | ((sSioChgCardWork->offeredCard + 1) & 0x0FFF);
}

void SioChgCardSelect() {
    gSioCommandSend[2] = (GetKeysPressed() & 0x0FFF) | 0x5000;
    gSioCommandSend[3] = ((gSioChgCardCursor & 15) << 12) | ((sSioChgCardWork->offeredCard + 1) & 0x0FFF);

    if (!sSioChgCardWork->ready) {
        SioChgCardHandleInput();
    } else {
        func_080B3DF8();
        gSioCommandSend[1] = 0x1AC7;
    }

    if (gSioCommandRecv[1][0] == 0x1AC7) {
        if (gSioChgCardReady[0] == 0) {
            SetSioChgCardAnimation(0, 1, 0);
            m4aSongNumStart(SONG_SYS_KETTEI);
        }

        RequestDma3Copy(gUnk_096B5FA4, (void*)(BG_VRAM + TILE_SIZE_4BPP), 0xC0);
        gSioChgCardReady[0] = 1;
    } else if (gSioCommandRecv[1][0] == 0x2B9A) {
        if (gSioChgCardReady[0] == 1) {
            SetSioChgCardAnimation(0, 0, 0);
            m4aSongNumStart(SONG_SYS_CLOSE);
            sSioChgCardWork->messageVisible = 0;
        }

        RequestDma3Copy(gUnk_096B5EE4, (void*)(BG_VRAM + TILE_SIZE_4BPP), 0xC0);
        gSioChgCardReady[0] = 0;
    }

    if (gSioCommandRecv[1][1] == 0x1AC7) {
        if (gSioChgCardReady[1] == 0) {
            SetSioChgCardAnimation(1, 1, 0);
            m4aSongNumStart(SONG_SYS_KETTEI);
        }

        RequestDma3Copy(gUnk_096B63A4, (void*)(BG_VRAM + 7 * TILE_SIZE_4BPP), 0xC0);
        gSioChgCardReady[1] = 1;
    } else if (gSioCommandRecv[1][1] == 0x2B9A) {
        if (gSioChgCardReady[1] == 1) {
            SetSioChgCardAnimation(1, 0, 0);
            m4aSongNumStart(SONG_SYS_CLOSE);
            sSioChgCardWork->messageVisible = 0;
        }

        RequestDma3Copy(gUnk_096B62E4, (void*)(BG_VRAM + 7 * TILE_SIZE_4BPP), 0xC0);
        gSioChgCardReady[1] = 0;
    }

    if (gSioChgCardReady[0] == 1 && gSioChgCardReady[1] == 1) {
        sSioChgCardWork->timer = 0;
        m4aSongNumStart(SONG_SYS_ITEMGET);
        sSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815A3C0, sSioChgCardWork->textSlots);
        sSioChgCardWork->x3 = 64;
        sSioChgCardWork->y3 = 114;
        sSioChgCardWork->state++;
    }

    if (gSioCommandRecv[1][0] == 0xA4CA || gSioCommandRecv[1][1] == 0xA4CA) {
        if ((gSioCommandRecv[2][0] & 0xF000) == 0x5000 && (gSioCommandRecv[2][1] & 0xF000) == 0x5000 && sSioChgCardWork->leaveDelay == 0) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            SioChgCardReturnOwnCards();
            SioLinkClose();
            ModeRequest(&gModeSioChgConnect, 3);
        }
    } else if (gSioCommandRecv[1][0] == 0x1D58) {
        sSioChgCardWork->leaveDelay = 10;

        if (gSioPlayerId == 0) {
            m4aSongNumStart(SONG_SYS_KETTEI);
            gSioChgCardCursor = sSioChgCardWork->cursor;
            ModeRequest(&gModeDeckExchange, 0);
        }
    } else if (gSioCommandRecv[1][1] == 0x1D58) {
        sSioChgCardWork->leaveDelay = 10;

        if (gSioPlayerId == 1) {
            m4aSongNumStart(SONG_SYS_KETTEI);
            gSioChgCardCursor = sSioChgCardWork->cursor;
            ModeRequest(&gModeDeckExchange, 0);
        }
    }

    SioChgCardRecvSlots();
    SioChgCardDrawPointTotals();

    if (sSioChgCardWork->leaveDelay > 0) {
        sSioChgCardWork->leaveDelay--;
    }
}

void SioChgCardConfirm() {
    if (GetKeysPressed() & A_BUTTON) {
        gSioCommandSend[1] = 0xEF01;
    } else if (GetKeysPressed() & B_BUTTON) {
        gSioCommandSend[1] = 0x58FA;
    }

    if (gSioCommandRecv[1][0] == 0xEF01 || gSioCommandRecv[1][1] == 0xEF01) {
        sSioChgCardWork->timer = 0;
        sSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815A404, sSioChgCardWork->textSlots);
        sSioChgCardWork->x3 = 71;
        sSioChgCardWork->y3 = 124;
        sSioChgCardWork->state++;
    }

    if (gSioCommandRecv[1][0] == 0x58FA || gSioCommandRecv[1][1] == 0x58FA) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        sSioChgCardWork->timer = 0;
        SioChgCardCancelReady();
        sSioChgCardWork->state = 3;
    }

    SioChgCardRecvSlots();
    SioChgCardDrawPointTotals();
}

void SioChgCardTryTrade() {
    SioChgCardBackupCollection();
    sSioChgCardWork->receiveOk = SioChgCardReceiveCards();

    if (sSioChgCardWork->receiveOk == 1) {
        gSioCommandSend[1] = 0xEF23;
    } else {
        gSioCommandSend[1] = 0x1269;
    }

    sSioChgCardWork->state++;
}

void SioChgCardWaitTradeResult() {
    if (sSioChgCardWork->receiveOk == 1) {
        gSioCommandSend[1] = 0xEF23;
    } else {
        gSioCommandSend[1] = 0x1269;
    }

    if (gSioCommandRecv[1][0] == 0xEF23 && gSioCommandRecv[1][1] == 0xEF23) {
        m4aSongNumStart(SONG_SYS_ITEMGET);
        sSioChgCardWork->timer = 0;
        gGameState.progression.obtainedCardKinds = sSioChgCardWork->obtainedCardKindsBackup;
        sSioChgCardWork->state = 8;
    }

    if (gSioCommandRecv[1][0] == 0x1269 || gSioCommandRecv[1][1] == 0x1269) {
        m4aSongNumStart(SONG_SYS_BEEP);
        sSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815A4B6, sSioChgCardWork->textSlots);
        sSioChgCardWork->x3 = 63;
        sSioChgCardWork->y3 = 118;
        SioChgCardRestoreCollection();
        sSioChgCardWork->timer = 0;
        sSioChgCardWork->state = 7;
    }
}

void SioChgCardTradeFailed() {
    if (sSioChgCardWork->timer > 179) {
        sSioChgCardWork->timer = 0;
        SioChgCardCancelReady();
        sSioChgCardWork->state = 3;
    } else {
        sSioChgCardWork->timer++;
    }
}

void SioChgCardStartMove() {
    SioChgCardCreateMoveTasks();
    sSioChgCardWork->timer = 0;
    sSioChgCardWork->state++;
}

void SioChgCardSave() {
    TaskPoolUpdate(&sSioChgCardWork->tasks);

    if (!SioHasError()) {
        if (!gSioDebugMode) {
            if (gGameState.flags & GAME_FLAG_SECOND_FILE) {
                SaveWriteFileLarge(1);
            } else {
                SaveWriteFileLarge(0);
            }
        }
    } else {
        gSystemFlags &= ~SYSTEM_FLAG_LINK_ACTIVE;
        ModeRequest(&gModeSioError, 0);
    }

    sSioChgCardWork->timer = 0;
    sSioChgCardWork->state++;
}

void SioChgCardWaitMove() {
    TaskPoolUpdate(&sSioChgCardWork->tasks);

    if (sSioChgCardWork->timer == 80) {
        sSioChgCardWork->messageVisible = 0;
    }

    sSioChgCardWork->timer++;

    if (sSioChgCardWork->timer > 199) {
        sSioChgCardWork->timer = 0;
        sSioChgCardWork->messageVisible = 1;
        sSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815A428, sSioChgCardWork->textSlots);
        sSioChgCardWork->x3 = 70;
        sSioChgCardWork->y3 = 119;
        sSioChgCardWork->state++;
    }
}

void SioChgCardShowSecondMessage() {
    sSioChgCardWork->timer++;

    if (sSioChgCardWork->timer > 119) {
        sSioChgCardWork->timer = 0;
        sSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815B3FA, sSioChgCardWork->textSlots);
        sSioChgCardWork->x3 = 83;
        sSioChgCardWork->y3 = 124;
        sSioChgCardWork->state++;
    }
}

void SioChgCardHideMessage() {
    sSioChgCardWork->timer++;

    if (sSioChgCardWork->timer > 119) {
        sSioChgCardWork->timer = 0;
        sSioChgCardWork->messageVisible = 0;
        sSioChgCardWork->state++;
    }
}

void SioChgCardRestart() {
    s32 i;
    gSioCommandSend[1] = 0x25FD;

    if (gSioCommandRecv[1][0] == 0x25FD || gSioCommandRecv[1][1] == 0x25FD) {
        if (gSioPlayerId == 0) {
            gSioChgCardCursor = 0;
        } else {
            gSioChgCardCursor = 5;
        }

        for (i = 0; i < 10; i++) {
            gSioChgCardSlots[i] = 0x800;
        }

        gSioChgCardReady[0] = 0;
        gSioChgCardReady[1] = 0;
        ModeRequest(&gModeSioChgCard, 0x800);
    }
}

void mode_sio_chg_card_2() {
    s32 i;
    ReleaseObjTiles(sSioChgCardWork->playerTilesPalettes[0]);
    ReleaseObjTiles(sSioChgCardWork->playerTilesPalettes[1]);
    ReleaseObjPalette(sSioChgCardWork->playerTilesPalettes[2]);
    ReleaseObjPalette(sSioChgCardWork->playerTilesPalettes[3]);
    ReleaseObjTiles(sSioChgCardWork->tiles);
    ReleaseObjPalette(sSioChgCardWork->palette);
    ReleaseObjTiles(sSioChgCardWork->tiles2);
    ReleaseObjPalette(sSioChgCardWork->palette2);

    for (i = 0; i < 10; i++) {
        ReleaseObjTiles(sSioChgCardWork->tiles3[i]);
        ReleaseObjPalette(sSioChgCardWork->palette3[i]);
    }

    ReleaseObjTiles(sSioChgCardWork->tiles4);
    ReleaseObjPalette(sSioChgCardWork->palette4);
    ReleaseObjTiles(sSioChgCardWork->tiles5);
    FreeTextSlots(sSioChgCardWork->textSlots, 42);
    FreeTextSlots(sSioChgCardWork->textSlots2, 20);
    TaskPoolDestroy(&sSioChgCardWork->tasks);
    EwramFree(sSioChgCardWork);
}

void SioChgCardDraw() {
    s32 i;
    ObjAffine* aff;
    sSioChgCardWork->gfx[0] = AnimUpdate(&sSioChgCardWork->anim[0]);
    sSioChgCardWork->gfx[1] = AnimUpdate(&sSioChgCardWork->anim[1]);
    sSioChgCardWork->gfx2 = AnimUpdate(&sSioChgCardWork->anim2);
    sSioChgCardWork->gfx3 = AnimUpdate(&sSioChgCardWork->anim3);
    DrawSprite(72, 72, sSioChgCardWork->gfx[0], sSioChgCardWork->playerTilesPalettes[0], sSioChgCardWork->playerTilesPalettes[2], NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_HFLIP, 0xFFFF);
    DrawSprite(168, 72, sSioChgCardWork->gfx[1], sSioChgCardWork->playerTilesPalettes[1], sSioChgCardWork->playerTilesPalettes[3], NULL, SPRITE_PRIORITY(1), 0xFFFF);

    if (sSioChgCardWork->cursorVisible == 1) {
        DrawSprite(sSioChgCardWork->x, sSioChgCardWork->y, sSioChgCardWork->gfx2, sSioChgCardWork->tiles, sSioChgCardWork->palette, NULL, SPRITE_PRIORITY(1), 0xFFC0);
        DrawSprite(sSioChgCardWork->x + 2, sSioChgCardWork->y - 8, sSioChgCardWork->gfx3, sSioChgCardWork->tiles2, sSioChgCardWork->palette2, NULL, SPRITE_PRIORITY(1), 0xFFA0);
    }

    for (i = 0; i < 10; i++) {
        if (sSioChgCardWork->cardVisible[i] == 1) {
            aff = AllocObjAffine(sSioChgCardWork->angle[i], sSioChgCardWork->scaleX[i], sSioChgCardWork->scaleY[i], 1);
            DrawSprite((sSioChgCardWork->x2[i] >> 8) + 16, (sSioChgCardWork->y2[i] >> 8) + 20, sSioChgCardWork->gfx4[i], sSioChgCardWork->tiles3[i], sSioChgCardWork->palette3[i], aff, SPRITE_PRIORITY(1), 0xFFF0);

            if (gCardDefs[gSioChgCardSlots[i]].category != 3) {
                DrawSprite((sSioChgCardWork->x2[i] >> 8) + 13, (sSioChgCardWork->y2[i] >> 8) + 16, sSioChgCardWork->gfx5[i], sSioChgCardWork->tiles4, sSioChgCardWork->palette4, aff, SPRITE_PRIORITY(1), 0xFFE0);
            }
        }
    }

    if (sSioChgCardWork->messageVisible == 1) {
        DrawSprite(120, 131, sSioChgCardWork->gfx6, sSioChgCardWork->tiles5, sSioChgCardWork->palette4, NULL, 0, 0xFF00);
        DrawTextSlots(sSioChgCardWork->x3, sSioChgCardWork->y3, sSioChgCardWork->textSlots, sSioChgCardWork->palette2, 20, sSioChgCardWork->textSlotCount);
    }

    if (sSioChgCardWork->cardInfoVisible == 1) {
        DrawTextSlots(58, 27, sSioChgCardWork->textSlots2, sSioChgCardWork->palette, 18, sSioChgCardWork->textSlotCount2);
        DrawTextSlots(52, 42, sSioChgCardWork->textSlots, sSioChgCardWork->palette2, 18, sSioChgCardWork->textSlotCount);
    }
}

void SioChgCardRecvSlots() {
    if (gSioCommandRecv[0][0] == 0xACD) {
        SioChgCardSetSlot(gSioCommandRecv[3][0]);
    }

    if (gSioCommandRecv[0][1] == 0xACD) {
        SioChgCardSetSlot(gSioCommandRecv[3][1]);
    }
}

void SioChgCardSetSlot(u16 a) {
    u16 slot;
    s32 i;

    if (a != 0) {
        i = a;
        i = i >> 12;
        slot = (a & 0x0FFF) - 1;

        if (slot == 0x800) {
            sSioChgCardWork->cardVisible[i] = 0;
            ReleaseObjTiles(sSioChgCardWork->tiles3[i]);
            ReleaseObjPalette(sSioChgCardWork->palette3[i]);
            sSioChgCardWork->tiles3[i] = LoadObjTiles(gCardDefs[CARD_ID(CARD_KINGDOM_KEY, 0)].tiles2, 0x200);
            sSioChgCardWork->palette3[i] = LoadObjPalette(gCardDefs[CARD_ID(CARD_KINGDOM_KEY, 0)].palette2, 32);
            sSioChgCardWork->gfx4[i] = gCardDefs[CARD_ID(CARD_KINGDOM_KEY, 0)].gfx2;
            sSioChgCardWork->gfx5[i] = gUnk_09EE981C[0];
            gSioChgCardSlots[i] = slot;

            if (sSioChgCardWork->cardInfoVisible == 1) {
                if (i == sSioChgCardWork->cursor) {
                    SioChgCardHideInfo();
                }
            }
        } else {
            sSioChgCardWork->cardVisible[i] = 1;
            ReleaseObjTiles(sSioChgCardWork->tiles3[i]);
            ReleaseObjPalette(sSioChgCardWork->palette3[i]);
            sSioChgCardWork->tiles3[i] = LoadObjTiles(gCardDefs[slot].tiles2, 0x200);
            sSioChgCardWork->palette3[i] = LoadObjPalette(gCardDefs[slot].palette2, 32);
            sSioChgCardWork->gfx4[i] = gCardDefs[slot].gfx2;
            sSioChgCardWork->gfx5[i] = gUnk_09EE981C[gCardDefs[slot].value];
            gSioChgCardSlots[i] = slot;
        }
    }
}

void SioChgCardRecvSlotIds() {
    gSioCommandSend[2] = 0x6000;

    if (gSioCommandRecv[0][0] == 0xACD) {
        SioChgCardSetSlotId(gSioCommandRecv[3][0]);
    }

    if (gSioCommandRecv[0][1] == 0xACD) {
        SioChgCardSetSlotId(gSioCommandRecv[3][1]);
    }
}

void SioChgCardSetSlotId(u16 a) {
    u16 slot;
    s32 i;

    if (a != 0) {
        i = a;
        i = i >> 12;
        slot = (a & 0x0FFF) - 1;

        if (slot == 0x800) {
            gSioChgCardSlots[i] = 0x800;
        } else {
            gSioChgCardSlots[i] = slot;
        }
    }
}

void SioChgCardDrawPointTotals() {
    u16 sum;
    s32 lim;
    s32 x;
    s32 i;
    s32 j;
    s16 digits[3];
    s32 v;
    sum = 0;
    lim = 0x800;

    for (i = 0; i < 5; i++) {
        x = gSioChgCardSlots[i];

        if ((s16)x != lim) {
            sum = GetCardMooglePointValue(x) - (0 - sum);
        }
    }

    v = (s16)sum;
    digits[0] = v / 100;
    v = v % 100;
    digits[1] = v / 10;
    v = v % 10;
    digits[2] = v;
    RequestDma3Copy(&gUnk_096B5DA4[digits[0] * 32], (void*)(BG_VRAM + 13 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(&gUnk_096B5DA4[digits[1] * 32], (void*)(BG_VRAM + 14 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(&gUnk_096B5DA4[digits[2] * 32], (void*)(BG_VRAM + 15 * TILE_SIZE_4BPP), 32);
    sum = 0;

    for (j = 5; j < 10; j++) {
        x = gSioChgCardSlots[j];

        if ((s16)x != 0x800) {
            sum = GetCardMooglePointValue(x) - (0 - sum);
        }
    }

    v = (s16)sum;
    digits[0] = v / 100;
    v = v % 100;
    digits[1] = v / 10;
    v = v % 10;
    digits[2] = v;
    RequestDma3Copy(&gUnk_096B5DA4[digits[0] * 32], (void*)(BG_VRAM + 16 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(&gUnk_096B5DA4[digits[1] * 32], (void*)(BG_VRAM + 17 * TILE_SIZE_4BPP), 32);
    RequestDma3Copy(&gUnk_096B5DA4[digits[2] * 32], (void*)(BG_VRAM + 18 * TILE_SIZE_4BPP), 32);
}

void SioChgCardHandleInput() {
    u16 k1;
    u16 k2;
    s16 v;
    k1 = GetKeysPressed();
    k2 = GetKeysPressed();

    if (sSioChgCardWork->cardInfoVisible == 1) {
        if (GetKeysPressed() & B_BUTTON) {
            if (sSioChgCardWork->cardInfoVisible == 1) {
                SioChgCardHideInfo();
            }
        }
    } else if (gSioPlayerId == 0) {
        if (k1 & DPAD_ANY) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        if (k1 & DPAD_UP) {
            sSioChgCardWork->nextCursor = gSioChgCardSlotPos[sSioChgCardWork->cursor].up;
        } else if (k1 & DPAD_DOWN) {
            sSioChgCardWork->nextCursor = gSioChgCardSlotPos[sSioChgCardWork->cursor].down;
        }

        if (k1 & DPAD_LEFT) {
            sSioChgCardWork->nextCursor = gSioChgCardSlotPos[sSioChgCardWork->cursor].left;
        } else if (k1 & DPAD_RIGHT) {
            sSioChgCardWork->nextCursor = gSioChgCardSlotPos[sSioChgCardWork->cursor].right;
        }

        if (sSioChgCardWork->nextCursor != 11) {
            sSioChgCardWork->cursor = sSioChgCardWork->nextCursor;
        }

        if (k1 & START_BUTTON) {
            m4aSongNumStart(SONG_SYS_CLICK);
            sSioChgCardWork->nextCursor = 10;
            sSioChgCardWork->cursor = 10;
        }

        sSioChgCardWork->x = gSioChgCardSlotPos[sSioChgCardWork->cursor].x;
        sSioChgCardWork->y = gSioChgCardSlotPos[sSioChgCardWork->cursor].y;
        v = gSioChgCardSlotPos[sSioChgCardWork->cursor].owner;

        if (k1 & A_BUTTON) {
            if (v == 2) {
                if (SioChgCardHasOwnCards() == 1) {
                    sSioChgCardWork->ready = 1;
                    sSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815A394, sSioChgCardWork->textSlots);
                    sSioChgCardWork->x3 = 68;
                    sSioChgCardWork->y3 = 124;
                    sSioChgCardWork->messageVisible = 1;
                } else {
                    m4aSongNumStart(SONG_SYS_BEEP);
                }
            } else if (gSioChgCardSlots[sSioChgCardWork->cursor] == 0x800) {
                if (v == 0) {
                    gSioCommandSend[1] = 0x1D58;
                }
            } else if (!sSioChgCardWork->cardInfoVisible) {
                m4aSongNumStart(SONG_SYS_KETTEI);
                SioChgCardShowInfo();
            }
        } else if (k1 & B_BUTTON) {
            if (SioChgCardSlotsEmpty() == 1) {
                gSioCommandSend[1] = 0xA4CA;
            } else if (v == 0) {
                if (gSioChgCardSlots[sSioChgCardWork->cursor] != 0x800) {
                    m4aSongNumStart(SONG_SYS_CLOSE);
                    SioChgCardReturnCard();
                }
            }
        }
    } else {
        if (k2 & DPAD_ANY) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        if (k2 & DPAD_UP) {
            sSioChgCardWork->nextCursor = gSioChgCardSlotPos[sSioChgCardWork->cursor].up;
        } else if (k2 & DPAD_DOWN) {
            sSioChgCardWork->nextCursor = gSioChgCardSlotPos[sSioChgCardWork->cursor].down;
        }

        if (k2 & DPAD_LEFT) {
            sSioChgCardWork->nextCursor = gSioChgCardSlotPos[sSioChgCardWork->cursor].left;
        } else if (k2 & DPAD_RIGHT) {
            sSioChgCardWork->nextCursor = gSioChgCardSlotPos[sSioChgCardWork->cursor].right;
        }

        if (sSioChgCardWork->nextCursor != 10) {
            sSioChgCardWork->cursor = sSioChgCardWork->nextCursor;
        }

        if (k2 & START_BUTTON) {
            m4aSongNumStart(SONG_SYS_CLICK);
            sSioChgCardWork->nextCursor = 11;
            sSioChgCardWork->cursor = 11;
        }

        sSioChgCardWork->x = gSioChgCardSlotPos[sSioChgCardWork->cursor].x;
        sSioChgCardWork->y = gSioChgCardSlotPos[sSioChgCardWork->cursor].y;
        v = gSioChgCardSlotPos[sSioChgCardWork->cursor].owner;

        if (k2 & A_BUTTON) {
            if (v == 2) {
                if (SioChgCardHasOwnCards() == 1) {
                    sSioChgCardWork->ready = 1;
                    sSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815A394, sSioChgCardWork->textSlots);
                    sSioChgCardWork->x3 = 68;
                    sSioChgCardWork->y3 = 124;
                    sSioChgCardWork->messageVisible = 1;
                } else {
                    m4aSongNumStart(SONG_SYS_BEEP);
                }
            } else if (gSioChgCardSlots[sSioChgCardWork->cursor] == 0x800) {
                if (v == 1) {
                    gSioCommandSend[1] = 0x1D58;
                }
            } else if (!sSioChgCardWork->cardInfoVisible) {
                m4aSongNumStart(SONG_SYS_KETTEI);
                SioChgCardShowInfo();
            }
        } else if (k2 & B_BUTTON) {
            if (SioChgCardSlotsEmpty() == 1) {
                gSioCommandSend[1] = 0xA4CA;
            } else if (v == 1) {
                if (gSioChgCardSlots[sSioChgCardWork->cursor] != 0x800) {
                    m4aSongNumStart(SONG_SYS_CLOSE);
                    SioChgCardReturnCard();
                }
            }
        }
    }

    if (sSioChgCardWork->cursor == 10) {
        sSioChgCardWork->cursorVisible = 0;

        if (gFrameCounter % 10 == 0) {
            RequestDma3Copy(&gUnk_096B5EE4[sSioChgCardWork->blinkPhase * 192], (void*)(BG_VRAM + TILE_SIZE_4BPP), 0xC0);
            sSioChgCardWork->blinkPhase = 1 - sSioChgCardWork->blinkPhase;
        }
    } else if (sSioChgCardWork->cursor == 11) {
        sSioChgCardWork->cursorVisible = 0;

        if (gFrameCounter % 10 == 0) {
            RequestDma3Copy(&gUnk_096B62E4[sSioChgCardWork->blinkPhase * 192], (void*)(BG_VRAM + 7 * TILE_SIZE_4BPP), 0xC0);
            sSioChgCardWork->blinkPhase = 1 - sSioChgCardWork->blinkPhase;
        }
    } else {
        sSioChgCardWork->cursorVisible = 1;
        RequestDma3Copy(gUnk_096B5EE4, (void*)(BG_VRAM + TILE_SIZE_4BPP), 0xC0);
        RequestDma3Copy(gUnk_096B5EE4 + 0x400, (void*)(BG_VRAM + 7 * TILE_SIZE_4BPP), 0xC0);
    }
}

void SioChgCardReturnCard() {
    AddCardToCollection(gSioChgCardSlots[sSioChgCardWork->cursor]);
    gSioChgCardSlots[sSioChgCardWork->cursor] = 0x800;
    gSioChgCardCursor = sSioChgCardWork->cursor;
    sSioChgCardWork->offeredCard = 0x800;
    gSioCommandSend[3] = ((gSioChgCardCursor & 15) << 12) | ((sSioChgCardWork->offeredCard + 1) & 0x0FFF);
}

s8 SioChgCardHasOwnCards() {
    s32 i;

    if (gSioPlayerId == 0) {
        for (i = 0; i < 5; i++) {
            if (gSioChgCardSlots[i] != 0x800) {
                return 1;
            }
        }
    } else {
        for (i = 5; i < 10; i++) {
            if (gSioChgCardSlots[i] != 0x800) {
                return 1;
            }
        }
    }

    return 0;
}

s8 SioChgCardSlotsEmpty() {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (gSioChgCardSlots[i] != 0x800) {
            return 0;
        }
    }

    return 1;
}

void SioChgCardShowInfo() {
    s16 n;
    u32 off;
    u16 nameId;
    const CardDef* defs;
    const CardDef* def;
    n = gSioChgCardSlots[sSioChgCardWork->cursor];
    defs = gCardDefs;
    def = &defs[n];
    off = def->category << 4;
    LoadPalette(gUnk_096FBF84 + off, (void*)(BG_PLTT + 5 * PLTT_SIZE_4BPP), 32);
    LoadObjPaletteBank(sSioChgCardWork->palette->index, gUnk_096FBF04 + off);
    nameId = def->kind;
    defs = (CardDef*)&defs->name;
    sSioChgCardWork->textSlotCount2 = LoadTextSlots(defs[n].gfx, sSioChgCardWork->textSlots2);
    sSioChgCardWork->textSlotCount = LoadTextSlots((void*)gCardKindDescriptions[nameId], sSioChgCardWork->textSlots);
    EnableBg(0);
    sSioChgCardWork->cardInfoVisible = 1;
}

void SioChgCardHideInfo() {
    DisableBg(0);
    sSioChgCardWork->cardInfoVisible = 0;
}

void SioChgCardCancelReady() {
    s8 v;
    sSioChgCardWork->ready = 0;

    if (gSioPlayerId == 0) {
        gSioChgCardCursor = 0;
    } else {
        gSioChgCardCursor = 5;
    }

    v = gSioChgCardCursor;
    sSioChgCardWork->cursor = v;
    sSioChgCardWork->nextCursor = v;
    sSioChgCardWork->x = gSioChgCardSlotPos[sSioChgCardWork->cursor].x;
    sSioChgCardWork->y = gSioChgCardSlotPos[sSioChgCardWork->cursor].y;
    sSioChgCardWork->cursorVisible = 1;
    sSioChgCardWork->offeredCard = gSioChgCardSlots[sSioChgCardWork->cursor];
    SetSioChgCardAnimation(0, 0, 0);
    SetSioChgCardAnimation(1, 0, 0);
    RequestDma3Copy(gUnk_096B5EE4, (void*)(BG_VRAM + TILE_SIZE_4BPP), 0xC0);
    RequestDma3Copy(gUnk_096B5EE4 + 0x400, (void*)(BG_VRAM + 7 * TILE_SIZE_4BPP), 0xC0);
    gSioChgCardReady[0] = 0;
    gSioChgCardReady[1] = 0;
    sSioChgCardWork->messageVisible = 0;
}

void SioChgCardCreateMoveTasks() {
    SioCardTaskArg arg;
    s32 i;

    for (i = 0; i < 5; i++) {
        if (gSioChgCardSlots[i] != 0x800) {
            arg.x = &sSioChgCardWork->x2[i];
            arg.y = &sSioChgCardWork->y2[i];
            arg.scaleX = &sSioChgCardWork->scaleX[i];
            arg.scaleY = &sSioChgCardWork->scaleY[i];
            arg.angle = &sSioChgCardWork->angle[i];
            arg.visible = &sSioChgCardWork->cardVisible[i];
            arg.targetX = 0xA000;
            arg.targetY = 0x800;
            arg.delay = (5 - i) * 20;
            TaskCreate(&sSioChgCardWork->tasks, &gTaskDescChgCardObj, &arg);
        }
    }

    for (i = 5; i < 10; i++) {
        if (gSioChgCardSlots[i] != 0x800) {
            arg.x = &sSioChgCardWork->x2[i];
            arg.y = &sSioChgCardWork->y2[i];
            arg.scaleX = &sSioChgCardWork->scaleX[i];
            arg.scaleY = &sSioChgCardWork->scaleY[i];
            arg.angle = &sSioChgCardWork->angle[i];
            arg.visible = &sSioChgCardWork->cardVisible[i];
            arg.targetX = 0x4000;
            arg.targetY = 0x800;
            arg.delay = (10 - i) * 20 + 10;
            TaskCreate(&sSioChgCardWork->tasks, &gTaskDescChgCardObj, &arg);
        }
    }
}

void SioChgCardBackupCollection() {
    u16 i;

    for (i = 0; i <= 0x3E6; i++) {
        sSioChgCardWork->collectionBackup[i] = gCardCollection[i];
    }

    sSioChgCardWork->obtainedCardKindsBackup = gGameState.progression.obtainedCardKinds;
}

void SioChgCardRestoreCollection() {
    u16 i;

    for (i = 0; i <= 0x3E6; i++) {
        gCardCollection[i] = sSioChgCardWork->collectionBackup[i];
    }

    gGameState.progression.obtainedCardKinds = sSioChgCardWork->obtainedCardKindsBackup;
}

s16 SioChgCardReceiveCards() {
    s32 i;
    s32 t;

    if (gSioPlayerId == 0) {
        for (i = 5; i < 10; i++) {
            t = gSioChgCardSlots[i] != 0x800;

            if (t) {
                if (AddCardToCollection(gSioChgCardSlots[i]) == -1) {
                    return 0;
                }
            }
        }
    } else {
        for (i = 0; i < 5; i++) {
            t = gSioChgCardSlots[i] != 0x800;

            if (t) {
                if (AddCardToCollection(gSioChgCardSlots[i]) == -1) {
                    return 0;
                }
            }
        }
    }

    return 1;
}

void SioChgCardReturnOwnCards() {
    s32 i;

    if (gSioPlayerId == 0) {
        for (i = 0; i < 5; i++) {
            if (gSioChgCardSlots[i] != 0x800) {
                AddCardToCollection(gSioChgCardSlots[i]);
            }
        }
    } else {
        for (i = 5; i < 10; i++) {
            if (gSioChgCardSlots[i] != 0x800) {
                AddCardToCollection(gSioChgCardSlots[i]);
            }
        }
    }
}

void func_080B3DF8() {
}
#endif

void mode_sioError_0(s32 arg) {
    gSystemFlags |= SYSTEM_FLAG_NO_SOFT_RESET;
    sSioErrorWork = EwramAlloc(sizeof(SioErrorWork));
    m4aMPlayAllStop();
    FadeStartIn(FADE_MODE_BLACK, 16);
    SioLinkClose();
    SetBgMode0();
    SetupBg(0, 0, 7, 15);
    SetupBg(1, 1, 31, 0);
    SetBgSize(1, 0);
    LoadBgTiles(1, gUnk_096ACA44, 0xBC0);
    LoadBgPalette(1, gUnk_096FBA04, 0x40);
    LoadBgMap(1, gUnk_096F5C64, 0x800);
    EnableBg(0);
    EnableBg(1);
    DisableBg(2);
    DisableBg(3);
    sSioErrorWork->unk_00 = 0;
    sSioErrorWork->unk_02 = 0;
    sSioErrorWork->unk_04 = 0;
#ifdef VERSION_EU
    LoadBgPalette(0, gCard00Palette, 32);
    LoadBgTiles(0, gUnk_0950E2F8, 0x140);

    if (gLanguage == LANGUAGE_FRENCH || gLanguage == LANGUAGE_SPANISH) {
        LoadBgMap(0, gUnkEu_096C798C, 0x800);
        SetBgScroll(0, 0xFFE9, 0xFFCD);
    } else {
        LoadBgMap(0, gUnk_096112B8, 0x800);
        SetBgScroll(0, 0xFFE9, 0xFFD0);
    }
#elif defined(VERSION_JP)
    LoadBgTiles(0, gUnk_096AD604, 0x140);
    LoadBgMap(0, gUnk_096F6464, 0x800);
    LoadBgPalette(0, gCard00Palette, 32);
#else
    LoadBgTiles(0, gUnk_0950E2F8, 0x140);
    LoadBgMap(0, gUnk_096112B8, 0x800);
    LoadBgPalette(0, gCard00Palette, 32);
    SetBgScroll(0, 0xFFE9, 0xFFD0);
#endif
    InitTextSlots(sSioErrorWork->textSlots, SIO_ERROR_TEXT_SLOTS);
#ifdef VERSION_EU
    sSioErrorWork->textSlotCount = LoadTextSlots(eu_0805E924(&gUnkEu_088920BC), sSioErrorWork->textSlots);
#elif defined(VERSION_JP)
    sSioErrorWork->textSlotCount = LoadTextSlots(gUnk_0814F180, sSioErrorWork->textSlots);
#else
    sSioErrorWork->textSlotCount = LoadTextSlots(gUnk_0815A2BE, sSioErrorWork->textSlots);
#endif
    sSioErrorWork->palette = LoadObjPalette(gUnk_096FBAA4, 32);
}

void mode_sioError_1() {
    SioErrorDraw();
}

void SioErrorDraw() {
#ifdef VERSION_JP
    DrawTextSlots(58, 62, sSioErrorWork->textSlots, sSioErrorWork->palette, 20, sSioErrorWork->textSlotCount);
#else
    DrawTextSlots(36, 57, sSioErrorWork->textSlots, sSioErrorWork->palette, 20, sSioErrorWork->textSlotCount);
#endif
}

void mode_sioError_2() {
    ReleaseObjPalette(sSioErrorWork->palette);
    FreeTextSlots(sSioErrorWork->textSlots, SIO_ERROR_TEXT_SLOTS);
    EwramFree(sSioErrorWork);
}

SioWorldEntry gSioWorldEntries[13] = {
#if defined(VERSION_US)
    {gUnk_08C94824, 16384, 0, gUnk_08EF6384, 4096, 0, gUnk_08F68C84, 224, 0, gUnk_0815A57C, BATTLE_STAGE_HALLOWEEN_TOWN, 0, 0},
    {gUnk_08C90824, 16384, 0, gUnk_08EF5384, 4096, 0, gUnk_08F68B84, 256, 0, gUnk_0815A56C, BATTLE_STAGE_AGRABAH, 0, 36},
    {gUnk_08C88824, 16384, 0, gUnk_08EF3384, 4096, 0, gUnk_08F689C4, 192, 0, gUnk_0815A5AA, BATTLE_STAGE_ATLANTICA, 0, 32},
    {gUnk_08C7C824, 16384, 0, gUnk_08EF0384, 4096, 0, gUnk_08F686E4, 224, 0, gUnk_0815A54A, BATTLE_STAGE_OLYMPUS_COLISEUM, 0, 16},
    {gUnk_08C84824, 16384, 0, gUnk_08EF2384, 4096, 0, gUnk_08F68904, 192, 0, gUnk_0815A534, BATTLE_STAGE_WONDERLAND, 0, 28},
    {gUnk_08C8C824, 16384, 0, gUnk_08EF4384, 4096, 0, gUnk_08F68A84, 256, 0, gUnk_0815A59A, BATTLE_STAGE_MONSTRO, 0, 36},
    {gUnk_08C94824, 16384, 0, gUnk_08EF6384, 4096, 0, gUnk_08F68C84, 224, 0, gUnk_0815A57C, BATTLE_STAGE_HALLOWEEN_TOWN, 0, 18},
    {gUnk_08C98824, 16064, 0, gUnk_08EF7384, 4096, 0, gUnk_08F68D64, 320, 0, gUnk_0815A5BE, BATTLE_STAGE_NEVER_LAND, 0, 26},
    {gUnk_08CA06E4, 16384, 0, gUnk_08EF9384, 4096, 0, gUnk_08F68FC4, 224, 0, gUnk_0815A5D4, BATTLE_STAGE_HOLLOW_BASTION, 0, 20},
    {gUnk_08C9C6E4, 16384, 0, gUnk_08EF8384, 4096, 0, gUnk_08F68EA4, 288, 0, gUnk_0815A62A, BATTLE_STAGE_DESTINY_ISLANDS, 0, 18},
    {gUnk_08C78824, 16384, 0, gUnk_08EEF384, 4096, 0, gUnk_08F68624, 192, 0, gUnk_0815A518, BATTLE_STAGE_TRAVERSE_TOWN, 0, 20},
    {gUnk_08CA46E4, 16384, 0, gUnk_08EFA384, 4096, 0, gUnk_08F690A4, 320, 0, gUnk_0815A60E, BATTLE_STAGE_TWILIGHT_TOWN, 0, 22},
    {gUnk_08CA86E4, 16384, 0, gUnk_08EFB384, 4096, 0, gUnk_08F691E4, 224, 0, gUnk_0815A64A, BATTLE_STAGE_CASTLE_OBLIVION, 0, 22},
#elif defined(VERSION_JP)
    {gUnk_08C94824, 16384, 0, gUnk_08EF6384, 4096, 0, gUnk_08F68C84, 224, 0, gUnkJp_0814E5B8, BATTLE_STAGE_HALLOWEEN_TOWN, 0, 0},
    {gUnk_08C90824, 16384, 0, gUnk_08EF5384, 4096, 0, gUnk_08F68B84, 256, 0, gUnkJp_0814E590, BATTLE_STAGE_AGRABAH, 0, 28},
    {gUnk_08C88824, 16384, 0, gUnk_08EF3384, 4096, 0, gUnk_08F689C4, 192, 0, gUnkJp_0814E5E4, BATTLE_STAGE_ATLANTICA, 0, 20},
    {gUnk_08C7C824, 16384, 0, gUnk_08EF0384, 4096, 0, gUnk_08F686E4, 224, 0, gUnkJp_0814E5CC, BATTLE_STAGE_OLYMPUS_COLISEUM, 0, 8},
    {gUnk_08C84824, 16384, 0, gUnk_08EF2384, 4096, 0, gUnk_08F68904, 192, 0, gUnkJp_0814E59C, BATTLE_STAGE_WONDERLAND, 0, 20},
    {gUnk_08C8C824, 16384, 0, gUnk_08EF4384, 4096, 0, gUnk_08F68A84, 256, 0, gUnkJp_0814E5AC, BATTLE_STAGE_MONSTRO, 0, 28},
    {gUnk_08C94824, 16384, 0, gUnk_08EF6384, 4096, 0, gUnk_08F68C84, 224, 0, gUnkJp_0814E5B8, BATTLE_STAGE_HALLOWEEN_TOWN, 0, 16},
    {gUnk_08C98824, 16064, 0, gUnk_08EF7384, 4096, 0, gUnk_08F68D64, 320, 0, gUnkJp_0814E5F4, BATTLE_STAGE_NEVER_LAND, 0, 26},
    {gUnk_08CA06E4, 16384, 0, gUnk_08EF9384, 4096, 0, gUnk_08F68FC4, 224, 0, gUnkJp_0814E618, BATTLE_STAGE_HOLLOW_BASTION, 0, 12},
    {gUnk_08C9C6E4, 16384, 0, gUnk_08EF8384, 4096, 0, gUnk_08F68EA4, 288, 0, gUnkJp_0814E62C, BATTLE_STAGE_DESTINY_ISLANDS, 0, 2},
    {gUnk_08C78824, 16384, 0, gUnk_08EEF384, 4096, 0, gUnk_08F68624, 192, 0, gUnkJp_0814E57C, BATTLE_STAGE_TRAVERSE_TOWN, 0, 12},
    {gUnk_08CA46E4, 16384, 0, gUnk_08EFA384, 4096, 0, gUnk_08F690A4, 320, 0, gUnkJp_0814E644, BATTLE_STAGE_TWILIGHT_TOWN, 0, 12},
    {gUnk_08CA86E4, 16384, 0, gUnk_08EFB384, 4096, 0, gUnk_08F691E4, 224, 0, gUnkJp_0814E658, BATTLE_STAGE_CASTLE_OBLIVION, 0, 34},
#elif defined(VERSION_EU)
    {gUnk_08C94824, 16384, 0, gUnk_08EF6384, 1312, 0, gUnk_08F68C84, 224, 0, &gUnkEu_0888E4C0, BATTLE_STAGE_HALLOWEEN_TOWN, 0, 0},
    {gUnk_08C90824, 16384, 0, gUnk_08EF5384, 1216, 0, gUnk_08F68B84, 256, 0, &gUnkEu_0888E3A0, BATTLE_STAGE_AGRABAH, 0, 36},
    {gUnk_08C88824, 16384, 0, gUnk_08EF3384, 1620, 0, gUnk_08F689C4, 192, 0, &gUnkEu_0888E578, BATTLE_STAGE_ATLANTICA, 0, 32},
    {gUnk_08C7C824, 16384, 0, gUnk_08EF0384, 1164, 0, gUnk_08F686E4, 224, 0, &gUnkEu_0888E530, BATTLE_STAGE_OLYMPUS_COLISEUM, 0, 16},
    {gUnk_08C84824, 16384, 0, gUnk_08EF2384, 1412, 0, gUnk_08F68904, 192, 0, &gUnkEu_0888E410, BATTLE_STAGE_WONDERLAND, 0, 28},
    {gUnk_08C8C824, 16384, 0, gUnk_08EF4384, 1692, 0, gUnk_08F68A84, 256, 0, &gUnkEu_0888E450, BATTLE_STAGE_MONSTRO, 0, 36},
    {gUnk_08C94824, 16384, 0, gUnk_08EF6384, 1312, 0, gUnk_08F68C84, 224, 0, &gUnkEu_0888E4C0, BATTLE_STAGE_HALLOWEEN_TOWN, 0, 18},
    {gUnk_08C98824, 16064, 0, gUnk_08EF7384, 1020, 0, gUnk_08F68D64, 320, 0, &gUnkEu_0888E5DC, BATTLE_STAGE_NEVER_LAND, 0, 26},
    {gUnk_08CA06E4, 16384, 0, gUnk_08EF9384, 1084, 0, gUnk_08F68FC4, 224, 0, &gUnkEu_0888E6BC, BATTLE_STAGE_HOLLOW_BASTION, 0, 20},
    {gUnk_08C9C6E4, 16384, 0, gUnk_08EF8384, 1112, 0, gUnk_08F68EA4, 288, 0, &gUnkEu_0888E72C, BATTLE_STAGE_DESTINY_ISLANDS, 0, 18},
    {gUnk_08C78824, 16384, 0, gUnk_08EEF384, 1088, 0, gUnk_08F68624, 192, 0, &gUnkEu_0888E364, BATTLE_STAGE_TRAVERSE_TOWN, 0, 20},
    {gUnk_08CA46E4, 16384, 0, gUnk_08EFA384, 1196, 0, gUnk_08F690A4, 320, 0, &gUnkEu_0888E78C, BATTLE_STAGE_TWILIGHT_TOWN, 0, 22},
    {gUnk_08CA86E4, 16384, 0, gUnk_08EFB384, 868, 0, gUnk_08F691E4, 224, 0, &gUnkEu_0888E804, BATTLE_STAGE_CASTLE_OBLIVION, 0, 22},
#endif
};

s8 gSioHandicapMarkerX[12] = {
    0,
    0,
    4,
    8,
    12,
    16,
    21,
    26,
    30,
    34,
    38,
    42,
};

u16 gSioHandicapAp[12] = {
    0,
    65527,
    65528,
    65529,
    65530,
    65531,
    65532,
    65533,
    65534,
    65535,
    0,
    1,
};

Mode gModeSioBtlOption = {
    "mode_sio_btl_option",
    mode_sio_btl_option_0,
    mode_sio_btl_option_1,
    mode_sio_btl_option_2,
};

Mode gModeSioBtlCardget = {
    "mode_sio_btl_cardget",
    mode_sio_btl_cardget_0,
    mode_sio_btl_cardget_1,
    mode_sio_btl_cardget_2,
};

#ifndef VERSION_EU
Mode gModeSioChgConnect = {
    "mode_sio_chg_connect",
    mode_sio_chg_connect_0,
    mode_sio_chg_connect_1,
    mode_sio_chg_connect_2,
};

SioChgCardPos gSioChgCardSlotPos[13] = {
    {16, 76, 0, 10, 1, 9, 2, {0, 0, 0}},
    {30, 105, 0, 0, 10, 8, 3, {0, 0, 0}},
    {43, 76, 0, 10, 3, 0, 4, {0, 0, 0}},
    {57, 105, 0, 2, 10, 1, 6, {0, 0, 0}},
    {70, 76, 0, 10, 3, 2, 5, {0, 0, 0}},
    {139, 76, 1, 11, 6, 4, 7, {0, 0, 0}},
    {153, 105, 1, 7, 11, 3, 8, {0, 0, 0}},
    {166, 76, 1, 11, 6, 5, 9, {0, 0, 0}},
    {180, 105, 1, 9, 11, 6, 1, {0, 0, 0}},
    {193, 76, 1, 11, 8, 7, 0, {0, 0, 0}},
    {0, 0, 2, 1, 0, 10, 10, {0, 0, 0}},
    {0, 0, 2, 8, 9, 11, 11, {0, 0, 0}},
    {0, 0, 0, 0, 0, 0, 0, {0, 0, 0}},
};
#endif

#ifndef VERSION_EU
const SioAnimDef gSioChgCardAnimDefs[3] = {
    {gSor1fl00Frames, gSor1fl00Anims, gSor1fl00Tiles, 0},
    {gSor1fl15Frames, gSor1fl15Anims, gSor1fl15Tiles, 0},
    {gSor1fl15Frames, gSor1fl15Anims, gSor1fl15Tiles, 1},
};
#endif

#ifndef VERSION_EU
Mode gModeSioChgCard = {
    "mode_sio_chg_card",
    mode_sio_chg_card_0,
    mode_sio_chg_card_1,
    mode_sio_chg_card_2,
};
#endif

Mode gModeSioError = {
    "mode_sioError",
    mode_sioError_0,
    mode_sioError_1,
    mode_sioError_2,
};
