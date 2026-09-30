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

vu16 gMovieModeState;
s32 gMovieId;
u16 gUnk_02034940;
volatile s16 gMovieFrame;
volatile s16 gMovieSubIndex;
volatile u16 gMovieSubCount;
MovieSub* volatile gMovieSubUpper;
MovieSub* volatile gMovieSubLower;
MovieSub* gMovieSubs;
volatile s16 gMovieSubUpperTimer;
volatile u16 gMovieSubUpperLength;
volatile u16 gMovieFlags;
volatile u16 gMovieSubUpperAlpha;
volatile s16 gMovieSubLowerTimer;
volatile u16 gMovieSubLowerLength;
volatile u16 gMovieSubLowerAlpha;

void mode_movie_0(s32 a) {
    gMovieModeState = 0;
    gMovieId = a;
    gUnk_02034940 = 0;
    gMovieFrame = 0;
    gMovieSubIndex = 0;
    gMovieSubCount = 0;
    gMovieSubs = 0;
    gMovieFlags = 0;
    gMovieSubUpperTimer = 0;
    gMovieSubUpperLength = 0;
    gMovieSubUpperAlpha = 0;
    gMovieSubUpper = 0;
    gMovieSubLowerTimer = 0;
    gMovieSubLowerLength = 0;
    gMovieSubLowerAlpha = 0;
    gMovieSubLower = 0;
}

#ifdef VERSION_JP
#define MOVIE_SUB_MAX_CHARS 24
#elif defined(VERSION_EU)
#define MOVIE_SUB_MAX_CHARS 48
#else
#define MOVIE_SUB_MAX_CHARS 40
#endif

s32 HandleMovieFrame(s32 arg) {
    s32 i;
    u16 keys;

    keys = ~REG_KEYINPUT;

    if ((keys & SOFT_RESET_KEYS) == SOFT_RESET_KEYS) {
        gMovieFlags |= MOVIE_FLAG_SOFT_RESET;
        return 1;
    }

    if (gMovieSubs != NULL) {
        for (i = 0; i < 2; i++) {
            if (gMovieSubs[gMovieSubIndex].frame == gMovieFrame) {
                if (gMovieSubs[gMovieSubIndex].line == 0) {
                    MovieSub* e;

                    gMovieSubUpper = e = &gMovieSubs[gMovieSubIndex];
                    gMovieFlags |= MOVIE_FLAG_UPPER_SUB_PENDING;
                    gMovieSubUpperTimer = e->duration;

                    if (gMovieSubIndex < gMovieSubCount - 1) {
                        gMovieSubIndex++;
                    }

                    gMovieSubUpperLength = CountNonSpaceChars(gMovieSubUpper->text);

                    if (gMovieSubUpperLength > MOVIE_SUB_MAX_CHARS) {
                        gMovieSubUpperLength = MOVIE_SUB_MAX_CHARS;
                    }
                } else {
                    MovieSub* e;

                    gMovieSubLower = e = &gMovieSubs[gMovieSubIndex];
                    gMovieFlags |= MOVIE_FLAG_LOWER_SUB_PENDING;
                    gMovieSubLowerTimer = e->duration;

                    if (gMovieSubIndex < gMovieSubCount - 1) {
                        gMovieSubIndex++;
                    }

                    gMovieSubLowerLength = CountNonSpaceChars(e->text);

                    if (gMovieSubLowerLength > MOVIE_SUB_MAX_CHARS) {
                        gMovieSubLowerLength = MOVIE_SUB_MAX_CHARS;
                    }
                }
            }
        }

        if (gMovieSubUpperTimer > 0) {
            gMovieSubUpperTimer--;
        }

        if (gMovieSubLowerTimer > 0) {
            gMovieSubLowerTimer--;
        }
    }
    gMovieFrame++;
    return 0;
}
void MovieVBlankIntr(void) {
    u16* oam;
#ifndef VERSION_JP
    s16 x;
    s16 y;
#endif
    u16 i;
    u32 attr0;
    u32 attr1;

    if (gMovieFlags & MOVIE_FLAG_PLAYING) {
        REG_DISPCNT = (DISPCNT_MODE_3 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG_ALL_ON);
        MovieUpdate();
        if (gMovieSubs != NULL) {
            if (gMovieFlags & MOVIE_FLAG_UPPER_SUB_PENDING) {
                gMovieFlags &= ~MOVIE_FLAG_UPPER_SUB_PENDING;
                gMovieSubUpperAlpha = 0;
#ifdef VERSION_JP
                CopySjisGlyphsToVram(gMovieSubUpper->text);
#else
                CopyLatinGlyphsToVram(gMovieSubUpper->text, gMovieSubUpperWidths, 0);
#endif
            }
            if (gMovieFlags & MOVIE_FLAG_LOWER_SUB_PENDING) {
                gMovieFlags &= ~MOVIE_FLAG_LOWER_SUB_PENDING;
                gMovieSubLowerAlpha = 0;
#ifdef VERSION_JP
                CopySjisGlyphsToVramAt(gMovieSubLower->text, 0x100);
#else
                CopyLatinGlyphsToVram(gMovieSubLower->text, gMovieSubLowerWidths, 0x100);
#endif
            }
            if (gMovieSubUpperTimer > 0 || gMovieSubUpperAlpha != 0 ||
                gMovieSubLowerTimer > 0 || gMovieSubLowerAlpha != 0) {
                REG_DISPCNT |= DISPCNT_OBJ_ON;
                REG_BLDCNT = (BLDCNT_TGT1_OBJ | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
                if (gMovieSubUpperAlpha < 16) {
                    if (gMovieSubUpperAlpha == 0) {
                        attr0 = OAM_DISABLE;
                    } else {
                        REG_BLDALPHA = ((16 - gMovieSubUpperAlpha) << 8) | gMovieSubUpperAlpha;
                        attr0 = OAM_BLEND;
                    }
                } else {
                    attr0 = 0;
                }
                if (gMovieSubLowerAlpha < 16) {
                    if (gMovieSubLowerAlpha == 0) {
                        attr1 = OAM_DISABLE;
                    } else {
                        REG_BLDALPHA = ((16 - gMovieSubLowerAlpha) << 8) | gMovieSubLowerAlpha;
                        attr1 = OAM_BLEND;
                    }
                } else {
                    attr1 = 0;
                }
                oam = (u16*)0x07000000;
#ifndef VERSION_JP
                x = 0;
                y = 0;
                if (gMovieSubUpperLength != 0) {
                    x = gMovieSubUpper->x;
                    x += GetCenteredTextX(gMovieSubUpperWidths, gMovieSubUpperLength);
                    y = 0x74;
                }
#endif
                for (i = 0; i < gMovieSubUpperLength; i++) {
                    u16 tile;
                    u16 palette;
#ifdef VERSION_JP
                    MovieSub* sub;
                    s16 x;
#endif

                    tile = i * 4;
#ifdef VERSION_JP
                    sub = gMovieSubUpper;
                    x = sub->x;
                    palette = (sub->palette & 15) << 12;
                    oam[0] = attr0 | 0x74;
                    oam[1] = (x + i * 10) | 0x4000;
#else
                    palette = (gMovieSubUpper->palette & 15) << 12;
                    oam[0] = attr0 | y;
                    oam[1] = x | 0x4000;
#endif
                    oam[2] = palette | (tile + 0x200);
                    oam += 4;
#ifndef VERSION_JP
                    x += gMovieSubUpperWidths[i];
#endif
                }
#ifndef VERSION_JP
                if (gMovieSubLowerLength != 0) {
                    x = gMovieSubLower->x;
                    x += GetCenteredTextX(gMovieSubLowerWidths, gMovieSubLowerLength);
                    y = 0x84;
                }
#endif
                for (i = 0; i < gMovieSubLowerLength; i++) {
                    u16 tile;
                    u16 palette;
#ifdef VERSION_JP
                    MovieSub* sub;
                    s16 x;
#endif

                    tile = i * 4;
#ifdef VERSION_JP
                    sub = gMovieSubLower;
                    x = sub->x;
                    palette = (sub->palette & 15) << 12;
                    oam[0] = attr1 | 0x84;
                    oam[1] = (x + i * 10) | 0x4000;
#else
                    palette = (gMovieSubLower->palette & 15) << 12;
                    oam[0] = attr1 | y;
                    oam[1] = x | 0x4000;
#endif
                    oam[2] = palette | (tile + 0x300);
                    oam += 4;
#ifndef VERSION_JP
                    x += gMovieSubLowerWidths[i];
#endif
                }
                for (i = gMovieSubUpperLength + gMovieSubLowerLength;
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
                if (gMovieSubUpperTimer > 0) {
                    if (gMovieSubUpperAlpha < 16) {
                        gMovieSubUpperAlpha += 4;
                    }
                } else if (gMovieSubUpperAlpha != 0) {
                    gMovieSubUpperAlpha -= 4;
                    if (gMovieSubUpperAlpha == 0) {
                        gMovieSubUpperLength = 0;
                    }
                }
                if (gMovieSubLowerTimer > 0) {
                    if (gMovieSubLowerAlpha < 16) {
                        gMovieSubLowerAlpha += 4;
                    }
                } else if (gMovieSubLowerAlpha != 0) {
                    gMovieSubLowerAlpha -= 4;
                    if (gMovieSubLowerAlpha == 0) {
                        gMovieSubLowerLength = 0;
                    }
                }
            } else {
                REG_DISPCNT &= ~DISPCNT_OBJ_ON;
            }
        }
    }
    *(vu16*)0x03007FF8 |= 1;
}

void mode_movie_1(void) {
    void* p;

    switch (gMovieModeState) {
    case 0: {
        s32 fill;

        InitDisplayRegs();
        gDispCnt &= ~(DISPCNT_BG_ALL_ON | DISPCNT_OBJ_ON);
        fill = 0;
        CpuSet(&fill, (void*)0x06000000, CPU_SET_SRC_FIXED | CPU_SET_32BIT | 0x6000);
        gMovieModeState++;
        break;
    }
    case 1:
        gMovieModeState++;
        break;
    case 2:
        m4aSoundVSyncOff();
        gVBlankHandlerOverride = MovieVBlankIntr;
        IwramHeapInit(GetIwramHeapStart(), GetIwramHeapSize());
        EwramHeapInit(GetEwramHeapStart(), GetEwramHeapSize());
        SetEwramHeapName(sMovieHeapName);
        SetIwramHeapName(sMovieHeapName);
        CpuSet(gUnk_08F69C04, (void*)0x05000200, 16);
        CpuSet(gUnk_09614718, (void*)0x05000220, 16);
        MovieSetCallbacks(IwramAlloc, EwramAlloc, IwramFree, EwramFree);

        switch (gMovieId) {
        case 1:
            p = gUnk_0815C3EC;
#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                gMovieSubs = gUnkEu_0883E040;
                gMovieSubCount = 3;
                break;
            case LANGUAGE_FRENCH:
                gMovieSubs = gUnkEu_0883E454;
                gMovieSubCount = 4;
                break;
            case LANGUAGE_GERMAN:
                gMovieSubs = gUnkEu_0883E8D4;
                gMovieSubCount = 4;
                break;
            case LANGUAGE_ITALIAN:
                gMovieSubs = gUnkEu_0883ECE8;
                gMovieSubCount = 4;
                break;
            case LANGUAGE_SPANISH:
            default:
                gMovieSubs = gUnkEu_0883F0F8;
                gMovieSubCount = 4;
                break;
            }
#else
            gMovieSubs = gUnk_0886AB40;
            gMovieSubCount = 3;
#endif
            break;
        case 2:
            p = gUnk_084E0F34;
            gMovieSubs = 0;
            gMovieSubCount = 0;
            break;
        case 3:
            p = gUnk_084F4660;
            gMovieSubs = 0;
            gMovieSubCount = 0;
            break;
        case 4:
            p = gUnk_0855CCB4;
#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                gMovieSubs = gUnkEu_0883E070;
                gMovieSubCount = 14;
                break;
            case LANGUAGE_FRENCH:
                gMovieSubs = gUnkEu_0883E494;
                gMovieSubCount = 14;
                break;
            case LANGUAGE_GERMAN:
                gMovieSubs = gUnkEu_0883E914;
                gMovieSubCount = 14;
                break;
            case LANGUAGE_ITALIAN:
                gMovieSubs = gUnkEu_0883ED28;
                gMovieSubCount = 14;
                break;
            case LANGUAGE_SPANISH:
            default:
                gMovieSubs = gUnkEu_0883F138;
                gMovieSubCount = 14;
                break;
            }
#else
            gMovieSubs = gUnk_0886AB90;
#ifdef VERSION_JP
            gMovieSubCount = 12;
#else
            gMovieSubCount = 14;
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
                gMovieSubs = gUnkEu_0883E150;
                gMovieSubCount = 10;
                break;
            case LANGUAGE_FRENCH:
                gMovieSubs = gUnkEu_0883E574;
                gMovieSubCount = 12;
                break;
            case LANGUAGE_GERMAN:
                gMovieSubs = gUnkEu_0883E9F4;
                gMovieSubCount = 11;
                break;
            case LANGUAGE_ITALIAN:
                gMovieSubs = gUnkEu_0883EE08;
                gMovieSubCount = 10;
                break;
            case LANGUAGE_SPANISH:
            default:
                gMovieSubs = gUnkEu_0883F218;
                gMovieSubCount = 11;
                break;
            }
#else
            gMovieSubs = gUnk_0886AC70;
#ifdef VERSION_JP
            gMovieSubCount = 8;
#else
            gMovieSubCount = 10;
#endif
#endif
            break;
#ifndef VERSION_EU
        default:
            p = gUnk_0855CCB4;
            gMovieSubs = gUnk_0886AB40;
            gMovieSubCount = 3;
            break;
#endif
        }

        if (MovieStart(p)) {
            gMovieFlags |= MOVIE_FLAG_PLAYING;
            MoviePlay(HandleMovieFrame, 0);
            gMovieFlags &= ~MOVIE_FLAG_PLAYING;
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
        gMovieModeState++;
        break;
    case 3: {
        s32 fill;

        fill = 0;
        CpuSet(&fill, (void*)0x06000000, CPU_SET_SRC_FIXED | CPU_SET_32BIT | 0x6000);

        if (gMovieFlags & MOVIE_FLAG_SOFT_RESET) {
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
            switch (gMovieId) {
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
        gMovieModeState++;
        break;
    }
    }
}

void mode_movie_2(void) {
    gVBlankHandlerOverride = 0;
}

#ifndef VERSION_JP
u16 gMovieSubUpperWidths[MOVIE_SUB_MAX_CHARS] __attribute__((aligned(8)));
u16 gMovieSubLowerWidths[MOVIE_SUB_MAX_CHARS] __attribute__((aligned(8)));
#endif

Mode gModeMovie = {
    "mode_movie",
    mode_movie_0,
    mode_movie_1,
    mode_movie_2,
};
