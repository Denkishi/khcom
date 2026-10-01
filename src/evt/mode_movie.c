#include "mode_chkmov.h"
#include "registration_data.h"
#include "system_state.h"
#include "main.h"
#include "movie.h"
#include "movie_text.h"
#include "msg_api.h"
#include "mode.h"
#include "display.h"
#include "pallet.h"
#include "mode_movie.h"
#include "sprite_palettes.h"
#include "gba/io_reg.h"
#include "malloc.h"
#include "fade.h"
#include <stddef.h>
#include "gba/keys.h"
#include "gba/oam.h"
#include "engine.h"
#include "gba/defines.h"
#include "gba/macro.h"
#include "gba/syscall.h"
#include "intr.h"
#include "m4a.h"
#include "obj_api.h"
#include "sprite.h"
#include "types.h"
#include "util.h"

static vu16 sMovieModeState;
static s32 sMovieId;
static u16 sUnk_02034940;
static volatile s16 sMovieFrame;
static volatile s16 sMovieSubIndex;
static volatile u16 sMovieSubCount;
static MovieSub* volatile sMovieSubUpper;
static MovieSub* volatile sMovieSubLower;
static MovieSub* sMovieSubs;
static volatile s16 sMovieSubUpperTimer;
static volatile u16 sMovieSubUpperLength;
static volatile u16 sMovieFlags;
static volatile u16 sMovieSubUpperAlpha;
static volatile s16 sMovieSubLowerTimer;
static volatile u16 sMovieSubLowerLength;
static volatile u16 sMovieSubLowerAlpha;

void mode_movie_0(s32 a) {
    sMovieModeState = 0;
    sMovieId = a;
    sUnk_02034940 = 0;
    sMovieFrame = 0;
    sMovieSubIndex = 0;
    sMovieSubCount = 0;
    sMovieSubs = 0;
    sMovieFlags = 0;
    sMovieSubUpperTimer = 0;
    sMovieSubUpperLength = 0;
    sMovieSubUpperAlpha = 0;
    sMovieSubUpper = 0;
    sMovieSubLowerTimer = 0;
    sMovieSubLowerLength = 0;
    sMovieSubLowerAlpha = 0;
    sMovieSubLower = 0;
}

#ifdef VERSION_JP
#define MOVIE_SUB_MAX_CHARS 24
#elif defined(VERSION_EU)
#define MOVIE_SUB_MAX_CHARS 48
#else
#define MOVIE_SUB_MAX_CHARS 40
#endif

#ifndef VERSION_JP
static u16 sMovieSubUpperWidths[MOVIE_SUB_MAX_CHARS];
static u16 sMovieSubLowerWidths[MOVIE_SUB_MAX_CHARS];
#endif

s32 HandleMovieFrame(s32 arg) {
    s32 i;
    u16 keys;

    keys = ~REG_KEYINPUT;

    if ((keys & SOFT_RESET_KEYS) == SOFT_RESET_KEYS) {
        sMovieFlags |= MOVIE_FLAG_SOFT_RESET;
        return 1;
    }

    if (sMovieSubs != NULL) {
        for (i = 0; i < 2; i++) {
            if (sMovieSubs[sMovieSubIndex].frame == sMovieFrame) {
                if (sMovieSubs[sMovieSubIndex].line == 0) {
                    MovieSub* e;

                    sMovieSubUpper = e = &sMovieSubs[sMovieSubIndex];
                    sMovieFlags |= MOVIE_FLAG_UPPER_SUB_PENDING;
                    sMovieSubUpperTimer = e->duration;

                    if (sMovieSubIndex < sMovieSubCount - 1) {
                        sMovieSubIndex++;
                    }

                    sMovieSubUpperLength = CountNonSpaceChars(sMovieSubUpper->text);

                    if (sMovieSubUpperLength > MOVIE_SUB_MAX_CHARS) {
                        sMovieSubUpperLength = MOVIE_SUB_MAX_CHARS;
                    }
                } else {
                    MovieSub* e;

                    sMovieSubLower = e = &sMovieSubs[sMovieSubIndex];
                    sMovieFlags |= MOVIE_FLAG_LOWER_SUB_PENDING;
                    sMovieSubLowerTimer = e->duration;

                    if (sMovieSubIndex < sMovieSubCount - 1) {
                        sMovieSubIndex++;
                    }

                    sMovieSubLowerLength = CountNonSpaceChars(e->text);

                    if (sMovieSubLowerLength > MOVIE_SUB_MAX_CHARS) {
                        sMovieSubLowerLength = MOVIE_SUB_MAX_CHARS;
                    }
                }
            }
        }

        if (sMovieSubUpperTimer > 0) {
            sMovieSubUpperTimer--;
        }

        if (sMovieSubLowerTimer > 0) {
            sMovieSubLowerTimer--;
        }
    }

    sMovieFrame++;
    return 0;
}

void MovieVBlankIntr() {
    u16* oam;
#ifndef VERSION_JP
    s16 x;
    s16 y;
#endif
    u16 i;
    u32 attr0;
    u32 attr1;

    if (sMovieFlags & MOVIE_FLAG_PLAYING) {
        REG_DISPCNT = (DISPCNT_MODE_3 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG_ALL_ON);
        MovieUpdate();

        if (sMovieSubs != NULL) {
            if (sMovieFlags & MOVIE_FLAG_UPPER_SUB_PENDING) {
                sMovieFlags &= ~MOVIE_FLAG_UPPER_SUB_PENDING;
                sMovieSubUpperAlpha = 0;
#ifdef VERSION_JP
                CopySjisGlyphsToVram(sMovieSubUpper->text);
#else
                CopyLatinGlyphsToVram(sMovieSubUpper->text, sMovieSubUpperWidths, 0);
#endif
            }

            if (sMovieFlags & MOVIE_FLAG_LOWER_SUB_PENDING) {
                sMovieFlags &= ~MOVIE_FLAG_LOWER_SUB_PENDING;
                sMovieSubLowerAlpha = 0;
#ifdef VERSION_JP
                CopySjisGlyphsToVramAt(sMovieSubLower->text, 0x100);
#else
                CopyLatinGlyphsToVram(sMovieSubLower->text, sMovieSubLowerWidths, 0x100);
#endif
            }

            if (sMovieSubUpperTimer > 0 || sMovieSubUpperAlpha != 0 ||
                sMovieSubLowerTimer > 0 || sMovieSubLowerAlpha != 0) {
                REG_DISPCNT |= DISPCNT_OBJ_ON;
                REG_BLDCNT = (BLDCNT_TGT1_OBJ | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);

                if (sMovieSubUpperAlpha < 16) {
                    if (sMovieSubUpperAlpha == 0) {
                        attr0 = OAM_DISABLE;
                    } else {
                        REG_BLDALPHA = ((16 - sMovieSubUpperAlpha) << 8) | sMovieSubUpperAlpha;
                        attr0 = OAM_BLEND;
                    }
                } else {
                    attr0 = 0;
                }

                if (sMovieSubLowerAlpha < 16) {
                    if (sMovieSubLowerAlpha == 0) {
                        attr1 = OAM_DISABLE;
                    } else {
                        REG_BLDALPHA = ((16 - sMovieSubLowerAlpha) << 8) | sMovieSubLowerAlpha;
                        attr1 = OAM_BLEND;
                    }
                } else {
                    attr1 = 0;
                }

                oam = (u16*)OAM;

#ifndef VERSION_JP
                x = 0;
                y = 0;

                if (sMovieSubUpperLength != 0) {
                    x = sMovieSubUpper->x;
                    x += GetCenteredTextX(sMovieSubUpperWidths, sMovieSubUpperLength);
                    y = 0x74;
                }
#endif

                for (i = 0; i < sMovieSubUpperLength; i++) {
                    u16 tile;
                    u16 palette;
#ifdef VERSION_JP
                    MovieSub* sub;
                    s16 x;
#endif

                    tile = i * 4;
#ifdef VERSION_JP
                    sub = sMovieSubUpper;
                    x = sub->x;
                    palette = (sub->palette & 15) << 12;
                    oam[0] = attr0 | 0x74;
                    oam[1] = (x + i * 10) | 0x4000;
#else
                    palette = (sMovieSubUpper->palette & 15) << 12;
                    oam[0] = attr0 | y;
                    oam[1] = x | 0x4000;
#endif
                    oam[2] = palette | (tile + 0x200);
                    oam += 4;
#ifndef VERSION_JP
                    x += sMovieSubUpperWidths[i];
#endif
                }

#ifndef VERSION_JP
                if (sMovieSubLowerLength != 0) {
                    x = sMovieSubLower->x;
                    x += GetCenteredTextX(sMovieSubLowerWidths, sMovieSubLowerLength);
                    y = 0x84;
                }
#endif

                for (i = 0; i < sMovieSubLowerLength; i++) {
                    u16 tile;
                    u16 palette;
#ifdef VERSION_JP
                    MovieSub* sub;
                    s16 x;
#endif

                    tile = i * 4;
#ifdef VERSION_JP
                    sub = sMovieSubLower;
                    x = sub->x;
                    palette = (sub->palette & 15) << 12;
                    oam[0] = attr1 | 0x84;
                    oam[1] = (x + i * 10) | 0x4000;
#else
                    palette = (sMovieSubLower->palette & 15) << 12;
                    oam[0] = attr1 | y;
                    oam[1] = x | 0x4000;
#endif
                    oam[2] = palette | (tile + 0x300);
                    oam += 4;
#ifndef VERSION_JP
                    x += sMovieSubLowerWidths[i];
#endif
                }

                for (i = sMovieSubUpperLength + sMovieSubLowerLength;
#ifdef VERSION_JP
                     i < 48;
#elif defined(VERSION_EU)
                     i < 96;
#else
                     i < 80;
#endif
                     i++) {
                    oam[0] = OAM_DISABLE;
                    oam += 4;
                }

                if (sMovieSubUpperTimer > 0) {
                    if (sMovieSubUpperAlpha < 16) {
                        sMovieSubUpperAlpha += 4;
                    }
                } else if (sMovieSubUpperAlpha != 0) {
                    sMovieSubUpperAlpha -= 4;

                    if (sMovieSubUpperAlpha == 0) {
                        sMovieSubUpperLength = 0;
                    }
                }

                if (sMovieSubLowerTimer > 0) {
                    if (sMovieSubLowerAlpha < 16) {
                        sMovieSubLowerAlpha += 4;
                    }
                } else if (sMovieSubLowerAlpha != 0) {
                    sMovieSubLowerAlpha -= 4;

                    if (sMovieSubLowerAlpha == 0) {
                        sMovieSubLowerLength = 0;
                    }
                }
            } else {
                REG_DISPCNT &= ~DISPCNT_OBJ_ON;
            }
        }
    }

    gIntrCheck |= INTR_FLAG_VBLANK;
}

void mode_movie_1() {
    void* p;

    switch (sMovieModeState) {
    case 0: {
        InitDisplayRegs();
        gDispCnt &= ~(DISPCNT_BG_ALL_ON | DISPCNT_OBJ_ON);
        CpuFill32(0, (void*)VRAM, 0x18000);
        sMovieModeState++;
        break;
    }
    case 1:
        sMovieModeState++;
        break;
    case 2:
        m4aSoundVSyncOff();
        gVBlankHandlerOverride = MovieVBlankIntr;
        IwramHeapInit(GetIwramHeapStart(), GetIwramHeapSize());
        EwramHeapInit(GetEwramHeapStart(), GetEwramHeapSize());
        SetEwramHeapName(sMovieHeapName);
        SetIwramHeapName(sMovieHeapName);
        CpuCopy16(gUnk_08F69C04, (void*)OBJ_PLTT, 32);
        CpuCopy16(gUnk_09614718, (void*)0x05000220, 32);
        MovieSetCallbacks(IwramAlloc, EwramAlloc, IwramFree, EwramFree);

        switch (sMovieId) {
        case 1:
            p = gUnk_0815C3EC;

#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                sMovieSubs = gUnkEu_0883E040;
                sMovieSubCount = 3;
                break;
            case LANGUAGE_FRENCH:
                sMovieSubs = gUnkEu_0883E454;
                sMovieSubCount = 4;
                break;
            case LANGUAGE_GERMAN:
                sMovieSubs = gUnkEu_0883E8D4;
                sMovieSubCount = 4;
                break;
            case LANGUAGE_ITALIAN:
                sMovieSubs = gUnkEu_0883ECE8;
                sMovieSubCount = 4;
                break;
            case LANGUAGE_SPANISH:
            default:
                sMovieSubs = gUnkEu_0883F0F8;
                sMovieSubCount = 4;
                break;
            }
#else
            sMovieSubs = gUnk_0886AB40;
            sMovieSubCount = 3;
#endif
            break;
        case 2:
            p = gUnk_084E0F34;
            sMovieSubs = 0;
            sMovieSubCount = 0;
            break;
        case 3:
            p = gUnk_084F4660;
            sMovieSubs = 0;
            sMovieSubCount = 0;
            break;
        case 4:
            p = gUnk_0855CCB4;

#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                sMovieSubs = gUnkEu_0883E070;
                sMovieSubCount = 14;
                break;
            case LANGUAGE_FRENCH:
                sMovieSubs = gUnkEu_0883E494;
                sMovieSubCount = 14;
                break;
            case LANGUAGE_GERMAN:
                sMovieSubs = gUnkEu_0883E914;
                sMovieSubCount = 14;
                break;
            case LANGUAGE_ITALIAN:
                sMovieSubs = gUnkEu_0883ED28;
                sMovieSubCount = 14;
                break;
            case LANGUAGE_SPANISH:
            default:
                sMovieSubs = gUnkEu_0883F138;
                sMovieSubCount = 14;
                break;
            }
#else
            sMovieSubs = gUnk_0886AB90;
#ifdef VERSION_JP
            sMovieSubCount = 12;
#else
            sMovieSubCount = 14;
#endif
#endif
            break;
#ifdef VERSION_EU
        default:
#endif
        case 5:
            p = gUnk_086FBA14;

#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                sMovieSubs = gUnkEu_0883E150;
                sMovieSubCount = 10;
                break;
            case LANGUAGE_FRENCH:
                sMovieSubs = gUnkEu_0883E574;
                sMovieSubCount = 12;
                break;
            case LANGUAGE_GERMAN:
                sMovieSubs = gUnkEu_0883E9F4;
                sMovieSubCount = 11;
                break;
            case LANGUAGE_ITALIAN:
                sMovieSubs = gUnkEu_0883EE08;
                sMovieSubCount = 10;
                break;
            case LANGUAGE_SPANISH:
            default:
                sMovieSubs = gUnkEu_0883F218;
                sMovieSubCount = 11;
                break;
            }
#else
            sMovieSubs = gUnk_0886AC70;
#ifdef VERSION_JP
            sMovieSubCount = 8;
#else
            sMovieSubCount = 10;
#endif
#endif
            break;
#ifndef VERSION_EU
        default:
            p = gUnk_0855CCB4;
            sMovieSubs = gUnk_0886AB40;
            sMovieSubCount = 3;
            break;
#endif
        }

        if (MovieStart(p)) {
            sMovieFlags |= MOVIE_FLAG_PLAYING;
            MoviePlay(HandleMovieFrame, 0);
            sMovieFlags &= ~MOVIE_FLAG_PLAYING;
        }

        MovieClose();
        IwramHeapInit(GetIwramHeapStart(), GetIwramHeapSize());
        EwramHeapInit(GetEwramHeapStart(), GetEwramHeapSize());
        VTransInit();
        SpriteInit();
        BgInit();
        FadeInit();
        PalletInit();
        SioKeyInit();
        VTransReset();
        BgReset();
        SpriteReset();
        FadeReset();
        MosaicReset();
        InitDisplayRegs();
        gVBlankHandlerOverride = 0;
        m4aSoundInit();
        m4aSoundVSyncOn();
        sMovieModeState++;
        break;
    case 3: {
        CpuFill32(0, (void*)VRAM, 0x18000);

        if (sMovieFlags & MOVIE_FLAG_SOFT_RESET) {
#ifdef VERSION_EU
            eu_0800115C();
#else
            SoftReset(RESET_ALL);
#endif
#ifdef VERSION_EU
        } else if (gDebugFlags & DEBUG_FLAG_DEBUG_MENU) {
            ModeRequest(&gModeMovieDebugEu, 0);
#endif
        } else {
            switch (sMovieId) {
            case 1:
                RequestEventMode(0);
                break;
            case 2:
                RequestEventMode(26);
                break;
            case 3:
                RequestEventMode(57);
                break;
            case 4:
                ModeRequest(&gModeStaffRoll, 0);
                break;
            case 5:
                ModeRequest(&gModeStaffRoll, 0);
                break;
            default:
                ModeRequest(&gModeDebug, 0);
                break;
            }
        }

        sMovieModeState++;
        break;
    }
    }
}

void mode_movie_2() {
    gVBlankHandlerOverride = 0;
}

Mode gModeMovie = {
    "mode_movie",
    mode_movie_0,
    mode_movie_1,
    mode_movie_2,
};
