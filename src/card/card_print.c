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
#include "sprites_boss_tm.h"
#include "link_menus.h"

s8 gSioDebugMode EWRAM_COMMON(4);

u8 gSioBattleFileLoaded EWRAM_COMMON(4);

static void** sSioBattleWork;

void InitPrintLayer(u8 bg);
void FreePrintLayer(void);
void ResetPrintLines(void);
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
    FadeStartIn(0, 16);
    SetBgMode0();
    SetupBg(0, 0, 7, 0);
    SetupBg(1, 0, 31, 0);
    LoadBgTiles(1, gUnk_096ACA44, 0xBC0);
    LoadBgPalette(1, gUnk_096FBA04, 64);
    LoadBgMap(1, gUnk_096F5464, 0x800);
    EnableBg(1);
    ((SioBattleWork*)sSioBattleWork)->state = 0;
    ((SioBattleWork*)sSioBattleWork)->slideTimer = 0;
    ((SioBattleWork*)sSioBattleWork)->stateFrames = 0;
    ((SioBattleWork*)sSioBattleWork)->x = -0x8000;
    ((SioBattleWork*)sSioBattleWork)->y = -0x800;
    ((SioBattleWork*)sSioBattleWork)->y2 = 0xA000;
    ((SioBattleWork*)sSioBattleWork)->tiles = LoadObjTiles(gUnk_0962AD62, 0x240);
    ((SioBattleWork*)sSioBattleWork)->palette = LoadObjPalette(gUnk_096FBA44, 32);

    for (i = 0; i < 3; i++) {
        ((SioBattleWork*)sSioBattleWork)->gfx2[i] = gUnk_09EF3884[i];
    }

#ifdef VERSION_EU
    ((SioBattleWork*)sSioBattleWork)->palette2 = LoadObjPalette(gUnk_096FBA64, 32);
    ((SioBattleWork*)sSioBattleWork)->palette3 = LoadObjPalette(gUnk_096FBA84, 32);

    switch (gLanguage) {
    case 0:
        ((SioBattleWork*)sSioBattleWork)->tiles2 = LoadObjTiles(gUnkEu_095EDAAA, 0x600);
        ((SioBattleWork*)sSioBattleWork)->tiles3 = LoadObjTiles(gUnkEu_095EE0E2, 0x600);
        break;
    case 3:
        ((SioBattleWork*)sSioBattleWork)->tiles2 = LoadObjTiles(gUnkEu_095EFFFA, 0x600);
        ((SioBattleWork*)sSioBattleWork)->tiles3 = LoadObjTiles(gUnkEu_095F0632, 0x600);
        break;
    case 1:
        ((SioBattleWork*)sSioBattleWork)->tiles2 = LoadObjTiles(gUnkEu_095EE71A, 0x600);
        ((SioBattleWork*)sSioBattleWork)->tiles3 = LoadObjTiles(gUnkEu_095EED52, 0x600);
        break;
    case 4:
        ((SioBattleWork*)sSioBattleWork)->tiles2 = LoadObjTiles(gUnkEu_095EF38A, 0x600);
        ((SioBattleWork*)sSioBattleWork)->tiles3 = LoadObjTiles(gUnkEu_095EF9C2, 0x600);
        break;
    case 2:
    default:
        ((SioBattleWork*)sSioBattleWork)->tiles2 = LoadObjTiles(gUnkEu_095F0C6A, 0x600);
        ((SioBattleWork*)sSioBattleWork)->tiles3 = LoadObjTiles(gUnkEu_095F12A2, 0x600);
        break;
    }
#else
    ((SioBattleWork*)sSioBattleWork)->tiles2 = LoadObjTiles(gUnk_0962B286, 0x600);
    ((SioBattleWork*)sSioBattleWork)->palette2 = LoadObjPalette(gUnk_096FBA64, 32);
    ((SioBattleWork*)sSioBattleWork)->tiles3 = LoadObjTiles(gUnk_0962B8BE, 0x600);
    ((SioBattleWork*)sSioBattleWork)->palette3 = LoadObjPalette(gUnk_096FBA84, 32);
#endif
    ((SioBattleWork*)sSioBattleWork)->tiles4 = LoadObjTiles(gUnk_0962B090, 0x1C0);
    ((SioBattleWork*)sSioBattleWork)->palette4 = LoadObjPalette(gUnk_096FBAA4, 32);
    AnimInit(&((SioBattleWork*)sSioBattleWork)->anim, gUnk_09EF38B4, gUnk_09EF3894);
    AnimStart(&((SioBattleWork*)sSioBattleWork)->anim, 1, 1);
    gfx = AnimGetGfx(&((SioBattleWork*)sSioBattleWork)->anim);
    w = (SioBattleWork*)sSioBattleWork;
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
        ((SioBattleWork*)sSioBattleWork)->cursorY = ((SioBattleWork*)sSioBattleWork)->cursor * 0x1C00 + 0x3300;

        switch (gLanguage) {
        case 0:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB38[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB44[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 3:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB80[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB8C[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 1:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB50[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB5C[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 4:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB68[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB74[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 2:
        default:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB98[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EBA4[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        }
#else
        ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnk_09EF38BC[((SioBattleWork*)sSioBattleWork)->cursor];
        ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnk_09EF38C8[((SioBattleWork*)sSioBattleWork)->cursor];
        ((SioBattleWork*)sSioBattleWork)->cursorY = ((SioBattleWork*)sSioBattleWork)->cursor * 0x1C00 + 0x3300;
#endif
        break;
    case 2:
#ifdef VERSION_EU
        ((SioBattleWork*)sSioBattleWork)->cursorY = ((SioBattleWork*)sSioBattleWork)->cursor * 0x1C00 + 0x3300;
        gSioBattleFileLoaded = 1;
        w->cursor = 0;

        switch (gLanguage) {
        case 0:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB38[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB44[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 3:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB80[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB8C[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 1:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB50[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB5C[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 4:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB68[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB74[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 2:
        default:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB98[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EBA4[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        }
#else
        w->cursor = 0;
        ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnk_09EF38BC[((SioBattleWork*)sSioBattleWork)->cursor];
        ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnk_09EF38C8[((SioBattleWork*)sSioBattleWork)->cursor];
        ((SioBattleWork*)sSioBattleWork)->cursorY = ((SioBattleWork*)sSioBattleWork)->cursor * 0x1C00 + 0x3300;
        gSioBattleFileLoaded = 1;
#endif
        break;
    case 3:
        w->cursor = 0;
#ifdef VERSION_EU
        ((SioBattleWork*)sSioBattleWork)->cursorY = ((SioBattleWork*)sSioBattleWork)->cursor * 0x1C00 + 0x3300;
        gSioBattleFileLoaded = 1;

        switch (gLanguage) {
        case 0:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB38[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB44[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 3:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB80[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB8C[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 1:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB50[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB5C[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 4:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB68[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB74[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 2:
        default:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB98[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EBA4[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        }
#else
        ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnk_09EF38BC[((SioBattleWork*)sSioBattleWork)->cursor];
        ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnk_09EF38C8[((SioBattleWork*)sSioBattleWork)->cursor];
        ((SioBattleWork*)sSioBattleWork)->cursorY = ((SioBattleWork*)sSioBattleWork)->cursor * 0x1C00 + 0x3300;
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
    switch ((s8)((SioBattleWork*)sSioBattleWork)->state) {
    case 0:
        if ((s16)((SioBattleWork*)sSioBattleWork)->stateFrames == 0) {
            ((SioBattleWork*)sSioBattleWork)->slideTimer = 16;
        }

        ApproachValue(&((SioBattleWork*)sSioBattleWork)->y, 0, ((SioBattleWork*)sSioBattleWork)->slideTimer);
        ApproachValue(&((SioBattleWork*)sSioBattleWork)->y2, 0x9800, ((SioBattleWork*)sSioBattleWork)->slideTimer);
        ((SioBattleWork*)sSioBattleWork)->slideTimer--;

        if ((s16)((SioBattleWork*)sSioBattleWork)->slideTimer > 0) {
            ((SioBattleWork*)sSioBattleWork)->stateFrames++;
        } else {
            ((SioBattleWork*)sSioBattleWork)->state = 1;
            ((SioBattleWork*)sSioBattleWork)->stateFrames = 0;
        }
        break;
    case 1:
        if ((s16)((SioBattleWork*)sSioBattleWork)->stateFrames == 0) {
            ((SioBattleWork*)sSioBattleWork)->slideTimer = 16;
        }

        ApproachValue(&((SioBattleWork*)sSioBattleWork)->x, 0, ((SioBattleWork*)sSioBattleWork)->slideTimer);
        ((SioBattleWork*)sSioBattleWork)->slideTimer--;

        if ((s16)((SioBattleWork*)sSioBattleWork)->slideTimer > 0) {
            ((SioBattleWork*)sSioBattleWork)->stateFrames++;
        } else {
            ((SioBattleWork*)sSioBattleWork)->state = 5;
            ((SioBattleWork*)sSioBattleWork)->stateFrames = 0;
        }
        break;
    case 5:
        ((SioBattleWork*)sSioBattleWork)->state = 6;
        break;
    case 6:
        if (gSioBattleFileLoaded == 1) {
            if (GetKeysPressed() & DPAD_UP) {
                m4aSongNumStart(SONG_SYS_CLICK);
                ((SioBattleWork*)sSioBattleWork)->cursor--;

                if (((SioBattleWork*)sSioBattleWork)->cursor < 0) {
                    ((SioBattleWork*)sSioBattleWork)->cursor = 1;
                }
            }

            if (GetKeysPressed() & DPAD_DOWN) {
                m4aSongNumStart(SONG_SYS_CLICK);
                ((SioBattleWork*)sSioBattleWork)->cursor++;

                if (((SioBattleWork*)sSioBattleWork)->cursor > 1) {
                    ((SioBattleWork*)sSioBattleWork)->cursor = 0;
                }
            }
        } else {
            if (GetKeysPressed() & (DPAD_UP | DPAD_DOWN)) {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        }

#ifdef VERSION_EU
        switch (gLanguage) {
        case 0:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB38[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB44[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 3:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB80[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB8C[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 1:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB50[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB5C[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 4:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB68[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EB74[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        case 2:
        default:
            ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnkEu_09F7EB98[((SioBattleWork*)sSioBattleWork)->cursor];
            ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnkEu_09F7EBA4[((SioBattleWork*)sSioBattleWork)->cursor];
            break;
        }
#else
        ((SioBattleWork*)sSioBattleWork)->gfx3 = gUnk_09EF38BC[((SioBattleWork*)sSioBattleWork)->cursor];
        ((SioBattleWork*)sSioBattleWork)->gfx4 = gUnk_09EF38C8[((SioBattleWork*)sSioBattleWork)->cursor];
#endif

        if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
            m4aSongNumStart(SONG_SYS_KETTEI);

            switch (((SioBattleWork*)sSioBattleWork)->cursor) {
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
            ((SioBattleWork*)sSioBattleWork)->state = 2;
        }
        break;
    case 2:
        if ((s16)((SioBattleWork*)sSioBattleWork)->stateFrames == 0) {
            ((SioBattleWork*)sSioBattleWork)->slideTimer = 16;
        }

        ApproachValue(&((SioBattleWork*)sSioBattleWork)->x, -0x8000, ((SioBattleWork*)sSioBattleWork)->slideTimer);
        ((SioBattleWork*)sSioBattleWork)->slideTimer--;

        if ((s16)((SioBattleWork*)sSioBattleWork)->slideTimer > 0) {
            ((SioBattleWork*)sSioBattleWork)->stateFrames++;
        } else {
            ((SioBattleWork*)sSioBattleWork)->state = 3;
            ((SioBattleWork*)sSioBattleWork)->stateFrames = 0;
        }
        break;
    case 3:
        if ((s16)((SioBattleWork*)sSioBattleWork)->stateFrames == 0) {
            ((SioBattleWork*)sSioBattleWork)->slideTimer = 16;
        }

        ApproachValue(&((SioBattleWork*)sSioBattleWork)->y, -0x800, ((SioBattleWork*)sSioBattleWork)->slideTimer);
        ApproachValue(&((SioBattleWork*)sSioBattleWork)->y2, 0xA000, ((SioBattleWork*)sSioBattleWork)->slideTimer);
        ((SioBattleWork*)sSioBattleWork)->slideTimer--;

        if ((s16)((SioBattleWork*)sSioBattleWork)->slideTimer > 0) {
            ((SioBattleWork*)sSioBattleWork)->stateFrames++;
        } else {
            ModeRequest(&gModeTitle, 0);
            return;
        }
        break;
    }

    ((SioBattleWork*)sSioBattleWork)->gfx = AnimUpdate(&((SioBattleWork*)sSioBattleWork)->anim);
    DrawSprite(((SioBattleWork*)sSioBattleWork)->x >> 8, 0, ((SioBattleWork*)sSioBattleWork)->gfx2[0], ((SioBattleWork*)sSioBattleWork)->tiles, ((SioBattleWork*)sSioBattleWork)->palette, 0, 0x400, -16);
    DrawSprite(128, ((SioBattleWork*)sSioBattleWork)->y >> 8, ((SioBattleWork*)sSioBattleWork)->gfx2[1], ((SioBattleWork*)sSioBattleWork)->tiles, ((SioBattleWork*)sSioBattleWork)->palette, 0, 0x400, -1);
    DrawSprite(128, ((SioBattleWork*)sSioBattleWork)->y2 >> 8, ((SioBattleWork*)sSioBattleWork)->gfx2[2], ((SioBattleWork*)sSioBattleWork)->tiles, ((SioBattleWork*)sSioBattleWork)->palette, 0, 0x400, -1);
    DrawSprite(72, 48, ((SioBattleWork*)sSioBattleWork)->gfx3, ((SioBattleWork*)sSioBattleWork)->tiles2, ((SioBattleWork*)sSioBattleWork)->palette2, 0, 0x400, -32);
    DrawSprite(72, 48, ((SioBattleWork*)sSioBattleWork)->gfx4, ((SioBattleWork*)sSioBattleWork)->tiles3, ((SioBattleWork*)sSioBattleWork)->palette3, 0, 0x400, -32);
    ApproachValueHalf(&((SioBattleWork*)sSioBattleWork)->cursorY, ((SioBattleWork*)sSioBattleWork)->cursor * 7 * 1024 + 0x3300);
    DrawSprite(64, ((SioBattleWork*)sSioBattleWork)->cursorY >> 8, ((SioBattleWork*)sSioBattleWork)->gfx, ((SioBattleWork*)sSioBattleWork)->tiles4, ((SioBattleWork*)sSioBattleWork)->palette4, 0, 0x400, -48);
}

void mode_sio_battle_2(void) {
    ReleaseObjTiles(sSioBattleWork[5]);
    ReleaseObjPalette(sSioBattleWork[6]);
    ReleaseObjTiles(sSioBattleWork[10]);
    ReleaseObjPalette(sSioBattleWork[11]);
    ReleaseObjTiles(sSioBattleWork[13]);
    ReleaseObjPalette(sSioBattleWork[14]);
    ReleaseObjTiles(sSioBattleWork[16]);
    ReleaseObjPalette(sSioBattleWork[17]);
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
