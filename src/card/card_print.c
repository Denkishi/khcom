#include "macros.h"
#include "registration_data.h"
#include "system_state.h"
#include "m4a_song.h"
#include "fade.h"
#include "obj_api.h"
#include "display.h"
#include "engine_math.h"
#include "anim.h"
#include "obj.h"
#include "taskpool.h"
#include "key.h"
#include "malloc.h"
#include "card.h"
#include "sprites_boss_tm.h"
#include "link_menus.h"
#include "gba/keys.h"
#include "songs.h"
#include "mode.h"
#include "types.h"

s8 gSioDebugMode EWRAM_COMMON(4);

u8 gSioBattleFileLoaded EWRAM_COMMON(4);

static SioBattleWork* sSioBattleWork;

void task_print_0(void) {
    InitPrintLayer(0);
}

s32 task_print_1(void) {
    return 1;
}

void task_print_2(void) {
    ResetPrintLines();
}

void task_print_3(void) {
    FreePrintLayer();
}

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

void mode_sio_battle_1(void) {
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
    DrawSprite(sSioBattleWork->x >> 8, 0, sSioBattleWork->gfx2[0], sSioBattleWork->tiles, sSioBattleWork->palette, 0, SPRITE_PRIORITY(1), -16);
    DrawSprite(128, sSioBattleWork->y >> 8, sSioBattleWork->gfx2[1], sSioBattleWork->tiles, sSioBattleWork->palette, 0, SPRITE_PRIORITY(1), -1);
    DrawSprite(128, sSioBattleWork->y2 >> 8, sSioBattleWork->gfx2[2], sSioBattleWork->tiles, sSioBattleWork->palette, 0, SPRITE_PRIORITY(1), -1);
    DrawSprite(72, 48, sSioBattleWork->gfx3, sSioBattleWork->tiles2, sSioBattleWork->palette2, 0, SPRITE_PRIORITY(1), -32);
    DrawSprite(72, 48, sSioBattleWork->gfx4, sSioBattleWork->tiles3, sSioBattleWork->palette3, 0, SPRITE_PRIORITY(1), -32);
    ApproachValueHalf(&sSioBattleWork->cursorY, sSioBattleWork->cursor * 7 * 1024 + 0x3300);
    DrawSprite(64, sSioBattleWork->cursorY >> 8, sSioBattleWork->gfx, sSioBattleWork->tiles4, sSioBattleWork->palette4, 0, SPRITE_PRIORITY(1), -48);
}

void mode_sio_battle_2(void) {
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

void ClearSioBattleFileLoaded(void) {
    gSioBattleFileLoaded = 0;
}

TaskDesc gTaskDescPrint = {
    "task_print",
    (TaskInitFunc)task_print_0,
    (TaskUpdateFunc)task_print_1,
    (TaskDrawFunc)task_print_2,
    (TaskDestroyFunc)task_print_3,
    sizeof(PrintWork),
};
