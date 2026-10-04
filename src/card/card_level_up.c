#include "card_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "card_battle.h"
#include "m4a_song.h"
#include "game_state.h"
#include "text.h"
#include "fade.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "display.h"
#include "engine_math.h"
#include "anim.h"
#include "obj.h"
#include "taskpool.h"
#include "key.h"
#include "card.h"
#include "sprites_evt.h"
#include "sprites_fld.h"
#include "sprites_level_up.h"
#include "sprites_sora.h"
#include "sprites_msg.h"
#include "sprites_card.h"
#include "gba/io_reg.h"
#include "gba/keys.h"
#include "songs.h"
#include "battle.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "mode_battle_data.h"
#include "player_progression_types.h"
#include "types.h"
#include "gba/defines.h"
#include "sprite_palettes.h"
#include <stddef.h>

u8 UpdateLevelUpWaitFade();
s32 IsLevelUpApUnlocked();
struct LevelUpWork;
u8 UpdateLevelUpResult(struct LevelUpWork* work, void* a);
u8 UpdateLevelUpNextSlideOut(LevelUpWork* work, void* a);

#ifdef VERSION_EU
static const u16 sLevelUpHeaderTileSizesByLanguage[5] = { 0x500, 0x500, 0x580, 0x500, 0x500 };

const u16 gUnkEu_090D1332[5] = { 0xE80, 0x1140, 0x1280, 0xF00, 0xF60 };

const u8 gLevelUpDisabledText[] = "\x19\x19\x19";

const u8* const gUnkEu_090D1340[5] = { gLevelUpDisabledText, gLevelUpDisabledText, gLevelUpDisabledText, gLevelUpDisabledText, gLevelUpDisabledText };
#elif defined(VERSION_JP)
const u8 gLevelUpDisabledText[] = "\x81\x7c\x81\x7c\x81\x7c";
#else
const u16 gLevelUpDisabledText[4] = { 0xE000, 0xE000, 0xE000, 0 };
#endif

static const s16 sLevelUpCursorY[3] = { 30, 78, 128 };

static const s16 sLevelUpApLevels[20] = { 2, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95 };

void Level_Up_0(LevelUpWork* work) {
    s16 x;
    s16 y;

    work->tiles4 = NULL;
    work->palette5 = NULL;
    work->unk_000[0] = NULL;
    work->unk_000[1] = NULL;
    work->unk_000[2] = NULL;
    work->unk_000[3] = NULL;
    work->unk_000[4] = NULL;
    work->unk_000[5] = NULL;
    work->unk_000[6] = NULL;
    work->unk_000[7] = NULL;
    work->palette = NULL;
    work->palette2 = NULL;
    work->tiles = NULL;
    work->palette3 = NULL;
    work->tiles2 = NULL;
    work->tiles3 = NULL;
    work->palette4 = NULL;
    work->optionEnabled[0] = 1;
    work->optionEnabled[1] = 1;
    work->optionEnabled[2] = 1;

    if (gCardBattleState != NULL) {
        gCardBattleState->levelUpShown = 1;
    }

#ifndef VERSION_EU
    InitTextSlots(work->textSlots[0], 36);
    InitTextSlots(work->textSlots[1], 36);
    InitTextSlots(work->textSlots[2], 36);
    InitTextSlots(work->textSlots[3], 36);
    InitTextSlots(work->textSlots[4], 36);
    InitTextSlots(work->textSlots[5], 36);
    work->unk_000[6] = LoadObjTiles(gUnk_0908CAEC, 0x500);
#else
    work->unk_000[6] = LoadObjTiles(gLevelUpHeaderTilesByLanguage[gLanguage], sLevelUpHeaderTileSizesByLanguage[gLanguage]);
    work->tiles5[0] = AllocSpriteFrameTiles(0x500);
    work->tiles5[1] = AllocSpriteFrameTiles(0x500);
    work->tiles5[2] = AllocSpriteFrameTiles(0x500);
#endif
    work->unk_000[7] = LoadObjPalette(gUnk_09613E98 + 0x30, 32);
    FadeSetPaletteExcluded(((ObjPalette*)work->unk_000[7])->index + 16, 1);
    work->tiles2 = LoadObjTiles(gUnk_0908D05E, 0x3C0);
    TaskPoolInit(&work->pool, 10);

    if (!(gGameState.flags & GAME_FLAG_RIKU)) {
        work->tiles4 = AllocObjTiles(0x500, NULL);
        work->palette5 = AllocObjPalette(32);
        UpdateAllocatedObjPalette(work->palette5, gSoraPalette);
        FadeSetPaletteExcluded(work->palette5->index + 16, 1);
        WorldToScreen(&x, &y, gBtlWork->actor->x,
                      gBtlWork->actor->y,
                      gBtlWork->actor->z);
        SetObjTileSource(work->tiles4, gSor1ll51Tiles);
        AnimInit(&work->anim2, gSor1ll51Anims, gSor1ll51Frames);
        AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
    } else {
        work->tiles4 = AllocObjTiles(0x800, NULL);
        work->palette5 = AllocObjPalette(32);
        UpdateAllocatedObjPalette(work->palette5, gRikuPalette);
        FadeSetPaletteExcluded(work->palette5->index + 16, 1);
        WorldToScreen(&x, &y, gBtlWork->actor->x,
                      gBtlWork->actor->y,
                      gBtlWork->actor->z);
        SetObjTileSource(work->tiles4, gRikuBt00Tiles);
        AnimInit(&work->anim2, gRikuBt00Anims, gRikuBt00Frames);
        AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
    }

    if (gBtlWork->flags & BTL_FLAG_FIELD_HIDDEN) {
        work->x7 = 0x1C400;
        work->y6 = 0x5000;
    } else {
        work->x7 = x << 8;
        work->y6 = y << 8;
    }

    work->gfx = AnimGetGfx(&work->anim2);

    if (!(gBtlWork->flags & BTL_FLAG_BOSS_BATTLE)) {
        work->bossBattle = 0;
        gDispCnt = (gDispCnt & ~DISPCNT_MODE_MASK) | DISPCNT_MODE_1;
        gBg1Cnt &= ~BGCNT_256COLOR;
        SetBgSize(1, 0);
        SetupBg(2, 0, 12, 0);
        SetupBg(1, 2, 24, 0);
        SetupBg(0, 2, 25, 0);
        LoadBgMap(1, gUnk_08125E24, 0x800);
        LoadBgMap(0, gUnk_08125E24, 0x800);
        EnableBg(2);
        DisableBg(1);
        DisableBg(0);
        gBg2Cnt = gBg3Cnt;
        gBg2PA = gBg3PA;
        gBg2PB = gBg3PB;
        gBg2PC = gBg3PC;
        gBg2PD = gBg3PD;
        gBg2X = gBg3X;
        gBg2Y = gBg3Y;
    } else {
        work->bossBattle = 1;

        switch (gBtlWork->battleId) {
        case 151:
            SetBgSize(0, 0);
            SetupBg(0, 0, 26, 0);
            LoadBgMap(0, gUnk_08125E24, 0x800);
            DisableBg(0);
            break;
        case 152:
            SetBgSize(1, 0);
            SetupBg(1, 1, 24, 0);
            LoadBgMap(1, gUnk_08125E24, 0x800);
            DisableBg(1);
            break;
        case 148:
            SetBgSize(1, 0);
            SetupBg(1, 2, 26, 0);
            LoadBgMap(1, gUnk_08125E24, 0x800);
            DisableBg(1);
            break;
        default:
            SetBgSize(1, 0);
            LoadBgMap(1, gUnk_08125E24, 0x800);
            DisableBg(1);
            break;
        }
    }

    gBldCnt &= ~BLDCNT_EFFECT_BLEND;
    work->x6 = -128;
    work->x4[0] = -128;
    work->x4[1] = -128;
    work->x4[2] = -128;
    work->y4[0] = 16;
    work->y4[1] = 64;
    work->y4[2] = 112;
    work->slideSteps = 24;
    work->headerSteps = 16;
    work->optionSteps[0] = 16;
    work->optionSteps[1] = 16;
    work->optionSteps[2] = 16;
    work->x5[0] = 8;
    work->x5[1] = 8;
    work->x5[2] = 8;
    work->y5[0] = 31;
    work->y5[1] = 79;
    work->y5[2] = 127;
    work->x = 128;
    work->x2 = 128;
    work->y = -0x800;
    work->y2 = 0xA000;
    work->barSteps = 16;
    work->bgScrollX = 0;
    work->statsOffsetX = 256;
    work->x3 = 132;
    work->y3 = sLevelUpCursorY[0];
    work->state = 0;
    work->cursor = 0;
    work->applied = 0;
    LevelUpSplitDigits3(gGameState.progression.level, work->levelDigits);
    LevelUpSplitDigits3(gGameState.progression.maxHp, work->maxHpDigits);
    LevelUpSplitDigits4(gGameState.progression.cp, work->cpDigits);
    LevelUpSplitDigits3(gGameState.progression.dp, work->dpDigits);
    LevelUpSplitDigits2(gGameState.progression.ap, work->apDigits);
    work->timer = 0;
    work->loaded[1] = 0;
    work->loaded[0] = 0;
    work->blinkTimer = 0;
    work->blinkOn = 0;
    work->playerSteps = 16;
    work->effectShown = 0;
}
#ifdef VERSION_EU
#define CARD_E7A4_DST 0x20
#else
#define CARD_E7A4_DST 0x2480
#endif
void LoadLevelUpRikuBgTiles() {
    u8* base;

    if (gBtlWork->battleId == 151) {
        base = GetBgCharBase(0);
        RequestDma3Copy(gUnk_093FEEB8, base + CARD_E7A4_DST, 288);
        RequestDma3Copy(&gUnk_093FEEB8[0x400], base + CARD_E7A4_DST + 0x120, 288);
        RequestDma3Copy(&gUnk_093FEEB8[0x800], base + CARD_E7A4_DST + 0x240, 288);
        RequestDma3Copy(&gUnk_093FEEB8[288], base + CARD_E7A4_DST + 0x360, 288);
        RequestDma3Copy(&gUnk_093FEEB8[0x520], base + CARD_E7A4_DST + 0x480, 288);
        RequestDma3Copy(&gUnk_093FEEB8[0x920], base + CARD_E7A4_DST + 0x5A0, 288);
#ifdef VERSION_EU
        RequestDma3Copy((u8*)gLevelUpBgTilesByLanguage[gLanguage] + 0xC00, base + 0x800, 0xA80);
#else
        RequestDma3Copy(gUnk_093FD438, base + 0x2C00, 0xA80);
#endif
    } else {
        base = GetBgCharBase(1);
        RequestDma3Copy(gUnk_093FEEB8, base + CARD_E7A4_DST, 288);
        RequestDma3Copy(&gUnk_093FEEB8[0x400], base + CARD_E7A4_DST + 0x120, 288);
        RequestDma3Copy(&gUnk_093FEEB8[0x800], base + CARD_E7A4_DST + 0x240, 288);
        RequestDma3Copy(&gUnk_093FEEB8[288], base + CARD_E7A4_DST + 0x360, 288);
        RequestDma3Copy(&gUnk_093FEEB8[0x520], base + CARD_E7A4_DST + 0x480, 288);
        RequestDma3Copy(&gUnk_093FEEB8[0x920], base + CARD_E7A4_DST + 0x5A0, 288);
#ifdef VERSION_EU
        RequestDma3Copy((u8*)gLevelUpBgTilesByLanguage[gLanguage] + 0xC00, base + 0x800, 0xA80);
#else
        RequestDma3Copy(gUnk_093FD438, base + 0x2C00, 0xA80);
#endif
    }
}

u8 UpdateLevelUpSelect(LevelUpWork* work, void* a);

u8 Level_Up_1(LevelUpWork* work, void* a) {
    s32 x[3];
#ifdef VERSION_EU
    enum { tileSize = 0xC80, mapSize = 0x500, bgSize = 0x2C00 };
#else
    enum { tileSize = 0xD80, mapSize = 0x800, bgSize = 0x3680 };
#endif

    if (work->loaded[1] == 0) {
        work->timer++;

        if (work->timer > 7) {
            if (!work->bossBattle) {
                LoadBgTiles(1, gUnk_093FF8F8, bgSize);

#ifdef VERSION_EU
                switch (gLanguage) {
                case LANGUAGE_ENGLISH:
                    break;
                case LANGUAGE_FRENCH:
                    RequestDma3Copy(gUnkEu_094D53C4, GetBgCharBase(1) + 0x2400, 0x800);
                    RequestDma3Copy(gLevelUpBgTilesByLanguage[gLanguage], GetBgCharBase(1) + 0x800, 0xC00);
                    break;
                case LANGUAGE_GERMAN:
                    RequestDma3Copy(gUnkEu_094D6BC4, GetBgCharBase(1) + 0x2400, 0x800);
                    RequestDma3Copy(gLevelUpBgTilesByLanguage[gLanguage], GetBgCharBase(1) + 0x800, 0xC00);
                    break;
                case LANGUAGE_ITALIAN:
                    RequestDma3Copy(gUnkEu_094D63C4, GetBgCharBase(1) + 0x2400, 0x800);
                    RequestDma3Copy(gLevelUpBgTilesByLanguage[gLanguage], GetBgCharBase(1) + 0x800, 0xC00);
                    break;
                case LANGUAGE_SPANISH:
                    RequestDma3Copy(gUnkEu_094D5BC4, GetBgCharBase(1) + 0x2400, 0x800);
                    RequestDma3Copy(gLevelUpBgTilesByLanguage[gLanguage], GetBgCharBase(1) + 0x800, 0xC00);
                    break;
                }
#endif

                if (!(gGameState.flags & GAME_FLAG_RIKU)) {
                    LoadPalette(gUnk_09614018, (void*)(BG_PLTT + 10 * PLTT_SIZE_4BPP), 0x80);
                } else {
                    LoadLevelUpRikuBgTiles();
                    LoadPalette(gUnk_09614098, (void*)(BG_PLTT + 10 * PLTT_SIZE_4BPP), 0x80);
                }

                LoadBgMap(1, gUnk_0950F2B8, mapSize);
                SetBgMapBlocks(1, gLevelUpBgMapBlocks, 2, 1);
                RedrawBgMapAt(1, 0, 0);
            } else {
                if (gBtlWork->battleId == 151) {
                    LoadBgTiles(0, gUnk_093FF8F8, bgSize);

#ifdef VERSION_EU
                    switch (gLanguage) {
                    case LANGUAGE_ENGLISH:
                        break;
                    case LANGUAGE_FRENCH:
                        RequestDma3Copy(gUnkEu_094D53C4, GetBgCharBase(0) + 0x2400, 0x800);
                        RequestDma3Copy(gLevelUpBgTilesByLanguage[gLanguage], GetBgCharBase(0) + 0x800, 0xC00);
                        break;
                    case LANGUAGE_GERMAN:
                        RequestDma3Copy(gUnkEu_094D6BC4, GetBgCharBase(0) + 0x2400, 0x800);
                        RequestDma3Copy(gLevelUpBgTilesByLanguage[gLanguage], GetBgCharBase(0) + 0x800, 0xC00);
                        break;
                    case LANGUAGE_ITALIAN:
                        RequestDma3Copy(gUnkEu_094D63C4, GetBgCharBase(0) + 0x2400, 0x800);
                        RequestDma3Copy(gLevelUpBgTilesByLanguage[gLanguage], GetBgCharBase(0) + 0x800, 0xC00);
                        break;
                    case LANGUAGE_SPANISH:
                        RequestDma3Copy(gUnkEu_094D5BC4, GetBgCharBase(0) + 0x2400, 0x800);
                        RequestDma3Copy(gLevelUpBgTilesByLanguage[gLanguage], GetBgCharBase(0) + 0x800, 0xC00);
                        break;
                    }
#endif

                    if (!(gGameState.flags & GAME_FLAG_RIKU)) {
                        LoadPalette(gUnk_09614018, (void*)(BG_PLTT + 10 * PLTT_SIZE_4BPP), 0x80);
                    } else {
                        LoadLevelUpRikuBgTiles();
                        LoadPalette(gUnk_09614098, (void*)(BG_PLTT + 10 * PLTT_SIZE_4BPP), 0x80);
                    }

                    SetBgMapBlocks(0, gLevelUpBgMapBlocks, 2, 1);
                    RedrawBgMapAt(0, 0, 0);
                } else {
                    LoadBgTiles(1, gUnk_093FF8F8, bgSize);

#ifdef VERSION_EU
                    switch (gLanguage) {
                    case LANGUAGE_ENGLISH:
                        break;
                    case LANGUAGE_FRENCH:
                        RequestDma3Copy(gUnkEu_094D53C4, GetBgCharBase(1) + 0x2400, 0x800);
                        RequestDma3Copy(gLevelUpBgTilesByLanguage[gLanguage], GetBgCharBase(1) + 0x800, 0xC00);
                        break;
                    case LANGUAGE_GERMAN:
                        RequestDma3Copy(gUnkEu_094D6BC4, GetBgCharBase(1) + 0x2400, 0x800);
                        RequestDma3Copy(gLevelUpBgTilesByLanguage[gLanguage], GetBgCharBase(1) + 0x800, 0xC00);
                        break;
                    case LANGUAGE_ITALIAN:
                        RequestDma3Copy(gUnkEu_094D63C4, GetBgCharBase(1) + 0x2400, 0x800);
                        RequestDma3Copy(gLevelUpBgTilesByLanguage[gLanguage], GetBgCharBase(1) + 0x800, 0xC00);
                        break;
                    case LANGUAGE_SPANISH:
                        RequestDma3Copy(gUnkEu_094D5BC4, GetBgCharBase(1) + 0x2400, 0x800);
                        RequestDma3Copy(gLevelUpBgTilesByLanguage[gLanguage], GetBgCharBase(1) + 0x800, 0xC00);
                        break;
                    }
#endif

                    if (!(gGameState.flags & GAME_FLAG_RIKU)) {
                        LoadPalette(gUnk_09614018, (void*)(BG_PLTT + 10 * PLTT_SIZE_4BPP), 0x80);
                    } else {
                        LoadLevelUpRikuBgTiles();
                        LoadPalette(gUnk_09614098, (void*)(BG_PLTT + 10 * PLTT_SIZE_4BPP), 0x80);
                    }

                    SetBgMapBlocks(1, gLevelUpBgMapBlocks, 2, 1);
                    RedrawBgMapAt(1, 0, 0);
                }
            }

            FadeSetPaletteExcluded(10, 1);
            FadeSetPaletteExcluded(11, 1);
            FadeSetPaletteExcluded(12, 1);
            FadeSetPaletteExcluded(13, 1);
            work->loaded[1] = 1;
            work->timer = 0;
            return 1;
        }

        return 1;
    }

    if (work->loaded[0] == 0) {
        work->timer++;

        if (work->timer > 7) {
            if (!(gGameState.flags & GAME_FLAG_RIKU)) {
                work->unk_000[0] = AllocSpriteFrameTiles(tileSize);
                work->unk_000[1] = AllocSpriteFrameTiles(tileSize);
                work->unk_000[2] = AllocSpriteFrameTiles(tileSize);

#ifdef VERSION_EU
                if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                    UpdateSpriteFrameTiles(work->unk_000[0], gUnk_09EEA2BC[0], gUnk_090950F4);
                    UpdateSpriteFrameTiles(work->unk_000[1], gUnk_09EEA2BC[1], gUnk_090950F4);
                    UpdateSpriteFrameTiles(work->unk_000[2], gUnk_09EEA2BC[2], gUnk_090950F4);
#ifdef VERSION_EU
                } else {
                    UpdateSpriteFrameTiles(work->unk_000[0], gUnkEu_09F7626C[0], gUnkEu_09172200);
                    UpdateSpriteFrameTiles(work->unk_000[1], gUnkEu_09F7626C[1], gUnkEu_09172200);
                    UpdateSpriteFrameTiles(work->unk_000[2], gUnkEu_09F7626C[2], gUnkEu_09172200);
                }
#endif

                work->unk_000[4] = LoadObjPalette(gUnk_09613F18, 32);
                work->unk_000[5] = LoadObjPalette(gUnk_09613F38, 32);
            } else {
                work->unk_000[0] = AllocSpriteFrameTiles(tileSize);
                work->unk_000[1] = AllocSpriteFrameTiles(tileSize);
                work->unk_000[2] = AllocSpriteFrameTiles(tileSize);

#ifdef VERSION_EU
                if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                    UpdateSpriteFrameTiles(work->unk_000[0], gUnk_09EEA29C[0], gUnk_09091D36);
                    UpdateSpriteFrameTiles(work->unk_000[1], gUnk_09EEA29C[1], gUnk_09091D36);
                    UpdateSpriteFrameTiles(work->unk_000[2], gUnk_09EEA29C[2], gUnk_09091D36);
#ifdef VERSION_EU
                } else {
                    UpdateSpriteFrameTiles(work->unk_000[0], gUnkEu_09F762A4[0], gUnkEu_091759BA);
                    UpdateSpriteFrameTiles(work->unk_000[1], gUnkEu_09F762A4[1], gUnkEu_091759BA);
                    UpdateSpriteFrameTiles(work->unk_000[2], gUnkEu_09F762A4[2], gUnkEu_091759BA);
                }
#endif

                work->unk_000[4] = LoadObjPalette(gUnk_09613EB8, 32);
                work->unk_000[5] = LoadObjPalette(gUnk_09613ED8, 32);
            }

#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                work->tiles3 = LoadObjTiles(gUnk_0908C686, 0x3E0);
                break;
            case LANGUAGE_FRENCH:
                work->tiles3 = LoadObjTiles(gUnkEu_0916F992, 0x3E0);
                break;
            case LANGUAGE_GERMAN:
                work->tiles3 = LoadObjTiles(gUnkEu_0917063A, 0x3E0);
                break;
            case LANGUAGE_ITALIAN:
                work->tiles3 = LoadObjTiles(gUnkEu_09170202, 0x3E0);
                break;
            case LANGUAGE_SPANISH:
                work->tiles3 = LoadObjTiles(gUnkEu_0916FDCA, 0x3E0);
                break;
            default:
                work->tiles3 = LoadObjTiles(gUnk_0908C686, 0x3E0);
                break;
            }
#else
            work->tiles3 = LoadObjTiles(gUnk_0908C686, 0x3E0);
#endif
            work->palette4 = LoadObjPalette(gCard00Palette, 32);
            FadeSetPaletteExcluded(((ObjPalette*)work->unk_000[4])->index + 16, 1);
            FadeSetPaletteExcluded(((ObjPalette*)work->unk_000[5])->index + 16, 1);
            FadeSetPaletteExcluded(work->palette4->index + 16, 1);
            work->tiles = AllocObjTiles(0x3C0, NULL);
            work->palette3 = LoadObjPalette(gUnk_09618CD8, 32);
            FadeSetPaletteExcluded(work->palette3->index + 16, 1);
            SetObjTileSource(work->tiles, gUnk_093F4578);
            AnimInit(&work->anim, gUnk_09EF1170, gUnk_09EF1150);
            AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);
            work->gfx2 = AnimGetGfx(&work->anim);
            work->loaded[0] = 1;
            work->timer = 0;
            FadeToAmount(FADE_MODE_BLACK, 8, 16);
        }

        return 1;
    }

    work->gfx = AnimUpdate(&work->anim2);

    if (work->playerSteps != 0) {
        ApproachValue(&work->x7, 0xBE00, work->playerSteps);
        ApproachValue(&work->y6, 0x5000, work->playerSteps);
        work->playerSteps--;
    }

    if (work->barSteps != 0) {
        ApproachValue(&work->y, 0, work->barSteps);
        ApproachValue(&work->y2, 0x9800, work->barSteps);
        work->barSteps--;
    } else {
        s32 x3 = work->bgScrollX << 8;
        s32 x4 = work->statsOffsetX << 8;
        ApproachValue(&x3, 0x10000, work->slideSteps);
        ApproachValue(&x4, 0, work->slideSteps);

        if (gBtlWork->battleId == 151) {
            ScrollBgMapTo(0, x3 >> 8, 0);
        } else {
            ScrollBgMapTo(1, x3 >> 8, 0);
        }

        work->bgScrollX = x3 >> 8;
        work->statsOffsetX = x4 >> 8;

        if (work->slideSteps > 0) {
            work->slideSteps--;
        }

        if (work->slideSteps <= 11) {
            s32 x5 = work->x6 << 8;
            ApproachValue(&x5, 0, work->headerSteps);
            work->x6 = x5 >> 8;

            if (work->headerSteps > 0) {
                work->headerSteps--;
            }

            if (work->headerSteps <= 6) {
                x[0] = work->x4[0] << 8;
                x[1] = work->x4[1] << 8;
                x[2] = work->x4[2] << 8;
                ApproachValue(&x[0], 0x1000, work->optionSteps[0]);

                if (work->optionSteps[0] > 0) {
                    work->optionSteps[0]--;
                }

                if (work->optionSteps[0] <= 6) {
                    ApproachValue(&x[1], 0x1000, work->optionSteps[1]);

                    if (work->optionSteps[1] > 0) {
                        work->optionSteps[1]--;
                    }
                }

                if (work->optionSteps[1] <= 6) {
                    ApproachValue(&x[2], 0x1000, work->optionSteps[2]);

                    if (work->optionSteps[2] > 0) {
                        work->optionSteps[2]--;
                    }
                }

                work->x4[0] = x[0] >> 8;
                work->x4[1] = x[1] >> 8;
                work->x4[2] = x[2] >> 8;

                if (work->optionSteps[2] == 0) {
                    u8 i;

                    if (gBtlWork->battleId == 151) {
                        LoadBgMap(0, gUnk_095112B8, mapSize);
                    } else {
                        LoadBgMap(1, gUnk_095112B8, mapSize);
                    }

                    work->state = 1;

                    if (!(gGameState.flags & GAME_FLAG_RIKU)) {
                        if (gGameState.progression.maxHp > 559) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(work->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            work->textSlotCounts[0] = LoadTextSlots(gLevelUpSoraTexts[6], work->textSlots[0]);
                            work->textSlotCounts[3] = 0;
#endif
                            work->optionEnabled[0] = 0;
                        } else {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(work->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][0], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            work->textSlotCounts[0] = LoadTextSlots(gLevelUpSoraTexts[0], work->textSlots[0]);
                            work->textSlotCounts[3] = LoadTextSlots(gLevelUpSoraTexts[3], work->textSlots[3]);
#endif
                        }

                        if (gGameState.progression.cp > 1899) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(work->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            work->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[6], work->textSlots[1]);
                            work->textSlotCounts[4] = 0;
#endif
                            work->optionEnabled[1] = 0;
                        } else {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(work->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][1], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            work->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[1], work->textSlots[1]);
                            work->textSlotCounts[4] = LoadTextSlots(gLevelUpSoraTexts[4], work->textSlots[4]);
#endif
                        }

                        if (gGameState.progression.levelMilestone > 10) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(work->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            work->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[6], work->textSlots[2]);
                            work->textSlotCounts[5] = 0;
#endif
                            work->optionEnabled[2] = 0;
                        } else if (!IsLevelUpStockUnlocked()) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(work->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            work->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[6], work->textSlots[2]);
                            work->textSlotCounts[5] = 0;
#endif
                            work->optionEnabled[2] = 0;
                        } else {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(work->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][2], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            work->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[2], work->textSlots[2]);
                            work->textSlotCounts[5] = LoadTextSlots(gLevelUpSoraTexts[5], work->textSlots[5]);
#endif
                        }

                        work->palette = LoadObjPalette(gUnk_09613F98, 32);
                        work->palette2 = LoadObjPalette(gUnk_09613FB8, 32);
                    } else {
                        if (gGameState.progression.maxHp > 559) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(work->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            work->textSlotCounts[0] = LoadTextSlots(gLevelUpRikuTexts[6], work->textSlots[0]);
                            work->textSlotCounts[3] = 0;
#endif
                            work->optionEnabled[0] = 0;
                        } else {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(work->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][3], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            work->textSlotCounts[0] = LoadTextSlots(gLevelUpRikuTexts[0], work->textSlots[0]);
                            work->textSlotCounts[3] = LoadTextSlots(gLevelUpRikuTexts[3], work->textSlots[3]);
#endif
                        }

                        if (gGameState.progression.ap > 29) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(work->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            work->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[6], work->textSlots[1]);
                            work->textSlotCounts[4] = 0;
#endif
                            work->optionEnabled[1] = 0;
                        } else if (!(u8)IsLevelUpApUnlocked()) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(work->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            work->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[6], work->textSlots[1]);
                            work->textSlotCounts[4] = 0;
#endif
                            work->optionEnabled[1] = 0;
                        } else {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(work->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][4], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            work->textSlotCounts[1] = LoadTextSlots(gLevelUpRikuTexts[1], work->textSlots[1]);
                            work->textSlotCounts[4] = LoadTextSlots(gLevelUpRikuTexts[4], work->textSlots[4]);
#endif
                        }

                        if (gGameState.progression.dp > 299) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(work->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            work->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[6], work->textSlots[2]);
                            work->textSlotCounts[5] = 0;
#endif
                            work->optionEnabled[2] = 0;
                        } else {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(work->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][5], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            work->textSlotCounts[2] = LoadTextSlots(gLevelUpRikuTexts[2], work->textSlots[2]);
                            work->textSlotCounts[5] = LoadTextSlots(gLevelUpRikuTexts[5], work->textSlots[5]);
#endif
                        }

                        work->palette = LoadObjPalette(gUnk_09613FD8, 32);
                        work->palette2 = LoadObjPalette(gUnk_09613FF8, 32);
                    }

                    FadeSetPaletteExcluded(work->palette->index + 16, 1);
                    FadeSetPaletteExcluded(work->palette2->index + 16, 1);

                    for (i = 0; i < 3; i++) {
                        if (work->optionEnabled[i] == 1) {
                            break;
                        }
                    }

                    work->cursor = i;
                    work->y3 = sLevelUpCursorY[work->cursor];
                    SetTaskUpdate(a, (TaskUpdateFunc)UpdateLevelUpSelect);

                    if (gBtlWork->battleId == 151) {
                        LoadBgMap(0, gLevelUpOptionBgMaps[work->cursor], 0x800);
                    } else {
                        LoadBgMap(1, gLevelUpOptionBgMaps[work->cursor], 0x800);
                    }
                }
            }
        }
    }

    TaskPoolUpdate(&work->pool);
    return 1;
}

u8 UpdateLevelUpSelect(LevelUpWork* work, void* a) {
    s32 x;
    s8 i;
    u8* q;
#ifdef VERSION_EU
    enum { mapOffset = 0x20C0, mapSize = 0x500, palOffset = 0x1190 };
#else
    enum { mapOffset = 0x7C0, mapSize = 0x800, palOffset = 0x1250 };
#endif

    if (GetKeysRepeat() & DPAD_DOWN) {
        i = work->cursor;
        q = work->optionEnabled;

        do {
            i++;

            if (i > 2) {
                i = 0;
            }
        } while (q[i] == 0);

        if (i != work->cursor) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        work->cursor = i;

        if (gBtlWork->battleId == 151) {
            LoadBgMap(0, gLevelUpOptionBgMaps[work->cursor], 0x800);
        } else {
            LoadBgMap(1, gLevelUpOptionBgMaps[work->cursor], 0x800);
        }

        work->cursorSteps = 8;
    }

    if (GetKeysRepeat() & DPAD_UP) {
        i = work->cursor;
        q = work->optionEnabled;

        do {
            i--;

            if (i < 0) {
                i = 2;
            }
        } while (q[i] == 0);

        if (i != work->cursor) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        work->cursor = i;

        if (gBtlWork->battleId == 151) {
            LoadBgMap(0, gLevelUpOptionBgMaps[work->cursor], 0x800);
        } else {
            LoadBgMap(1, gLevelUpOptionBgMaps[work->cursor], 0x800);
        }

        work->cursorSteps = 8;
    }

    while (GetKeysRepeat() & A_BUTTON) {
        work->state = 2;

        if (gBtlWork->battleId == 151) {
            LoadBgMap(0, &gUnk_0950E2F8[mapOffset], mapSize);
        } else {
            LoadBgMap(1, &gUnk_0950E2F8[mapOffset], mapSize);
        }

        work->optionSteps[0] = 16;
        work->optionSteps[1] = 16;
        work->optionSteps[2] = 16;
        m4aSongNumStart(SONG_SYS_KETTEI);
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette3);
        work->tiles = AllocObjTiles(128, NULL);
        work->palette3 = LoadObjPalette(&gCard00Palette[palOffset], 32);
        FadeSetPaletteExcluded(work->palette3->index + 16, 1);
        SetObjTileSource(work->tiles, gUnk_0908F190);
        AnimInit(&work->anim, gUnk_09EEA280, gUnk_09EEA26C);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        work->gfx2 = AnimGetGfx(&work->anim);
        work->cursorSteps = 16;
        work->x3 = 136;

        if (!(gGameState.flags & GAME_FLAG_RIKU)) {
            SetObjTileSource(work->tiles4, gSor1ff00Tiles);
            AnimInit(&work->anim2, gSor1ff00Anims, gSor1ff00Frames);
            AnimStart(&work->anim2, 1, 0);
        } else {
            SetObjTileSource(work->tiles4, gRikuFf00Tiles);
            AnimInit(&work->anim2, gRikuFf00Anims, gRikuFf00Frames);
            AnimStart(&work->anim2, 1, 0);
        }

        SetTaskUpdate(a, (TaskUpdateFunc)UpdateLevelUpResult);
        return 1;
    }

    x = work->y3 << 8;
    ApproachValue(&x, sLevelUpCursorY[work->cursor] << 8, work->cursorSteps);
    work->cursorSteps--;
    work->y3 = x >> 8;
    work->gfx2 = AnimUpdate(&work->anim);
    work->blinkTimer++;

    if (work->blinkTimer == 32) {
        work->blinkTimer = 0;
        work->blinkOn ^= 1;
    }

    work->gfx = AnimUpdate(&work->anim2);
    TaskPoolUpdate(&work->pool);
    return 1;
}

u8 UpdateLevelUpClose(LevelUpWork* work, void* a);

u8 UpdateLevelUpResult(LevelUpWork* work, void* a) {
    u8 i;

    if (work->effectShown == 0) {
#ifndef VERSION_US
        LevelUpEffectArgs args;
        args.x = 192;
        args.y = 60;
        args.unk_08 = 0;
        args.target = NULL;
        TaskCreate(&work->pool, &gTaskDescLVUPEFFECT, &args);
        m4aSongNumStart(SONG_SYS_LVUP);
#endif
        work->effectShown++;
    }

    for (i = 0; i < 3; i++) {
        if (i != work->cursor) {
            s32 x = work->x4[i] << 8;
            s32 y = work->x5[i] << 8;
            ApproachValue(&x, -0x10000, work->optionSteps[i]);
            ApproachValue(&y, -0xF800, work->optionSteps[i]);
            work->x4[i] = x >> 8;
            work->x5[i] = y >> 8;
        } else {
            s32 x = work->y4[i] << 8;
            s32 y = work->y5[i] << 8;
            ApproachValue(&x, 0x2000, work->optionSteps[i]);
            ApproachValue(&y, 0x3100, work->optionSteps[i]);
            work->y4[i] = x >> 8;
            work->y5[i] = y >> 8;
        }

        if (work->optionSteps[i] > 0) {
            work->optionSteps[i]--;
        }
    }

    if (work->optionSteps[0] == 0) {
        for (i = 0; i < 3; i++) {
            if (i != work->cursor && work->unk_000[i] != NULL) {
                ReleaseObjTiles(work->unk_000[i]);
                work->unk_000[i] = NULL;
            }
        }

        if (!work->applied) {
            switch (work->cursor) {
            case 0: {
                s32 amount = LevelUpMaxHp();
                StatIncreaseDisplayArgs args;
                work->messageActive = 1;
                args.amount = amount;
                args.done = &work->messageActive;
                args.flags = STAT_INCREASE_FLAG_MAX_HP;
                TaskCreate(&work->pool, &gTaskDescLvupMsg, &args);
                break;
            }
            case 1:
                if (!(gGameState.flags & GAME_FLAG_RIKU)) {
                    s32 amount = LevelUpCp();
                    StatIncreaseDisplayArgs args;
                    work->messageActive = 1;
                    args.amount = amount;
                    args.done = &work->messageActive;
                    args.flags = 0;
                    TaskCreate(&work->pool, &gTaskDescLvupMsg, &args);
                } else {
                    s32 amount = LevelUpAp();
                    StatIncreaseDisplayArgs args;
                    work->messageActive = 1;
                    args.amount = amount;
                    args.done = &work->messageActive;
                    args.flags = 0;
                    gGameState.progression.levelMilestone++;
                    TaskCreate(&work->pool, &gTaskDescLvupMsg, &args);
                }

                break;
            case 2:
                if (!(gGameState.flags & GAME_FLAG_RIKU)) {
                    work->messageActive = 1;
                    TaskCreate(&work->pool, &gTaskDescStockInfo, &work->messageActive);
                } else {
                    s32 amount = LevelUpDp();
                    StatIncreaseDisplayArgs args;
                    work->messageActive = 1;
                    args.amount = amount;
                    args.done = &work->messageActive;
                    args.flags = STAT_INCREASE_FLAG_DP;
                    TaskCreate(&work->pool, &gTaskDescLvupMsg, &args);
                }

                break;
            }

            LevelUpSplitDigits3(gGameState.progression.maxHp, work->maxHpDigits);
            LevelUpSplitDigits4(gGameState.progression.cp, work->cpDigits);
            LevelUpSplitDigits3(gGameState.progression.dp, work->dpDigits);
            LevelUpSplitDigits2(gGameState.progression.ap, work->apDigits);
            work->applied = 1;
        }
    }

    {
        s32 y = work->y3 << 8;
        ApproachValue(&y, 0x3000, work->cursorSteps);
        work->cursorSteps--;
        work->y3 = y >> 8;
    }

    TaskPoolUpdate(&work->pool);
    work->blinkTimer++;

    if (work->blinkTimer == 32) {
        work->blinkTimer = 0;
        work->blinkOn ^= 1;
    }

    if (work->timer == 180) {
        if (GetKeysPressed() & A_BUTTON) {
            if (gBtlWork->battleId == 151) {
                SetBgMapBlocks(0, gLevelUpBgMapBlocks, 2, 1);
            } else {
                SetBgMapBlocks(1, gLevelUpBgMapBlocks, 2, 1);
            }

            work->headerSteps = 16;
            work->slideSteps = 16;
            work->optionSteps[work->cursor] = 16;
            work->barSteps = 16;
            work->state = 3;
            work->blinkOn = 0;
            work->messageActive = 0;
            gBtlWork->pendingLevelUps--;

            if (gBtlWork->pendingLevelUps == 0) {
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateLevelUpClose);
            } else {
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateLevelUpNextSlideOut);
            }

            m4aSongNumStart(SONG_SYS_KETTEI);
        }
    } else {
        work->timer++;
    }

    work->gfx2 = AnimUpdate(&work->anim);
    work->gfx = AnimUpdate(&work->anim2);
    return 1;
}

u8 UpdateLevelUpClose(LevelUpWork* work, void* a) {
    s32 v1;
    s32 v2;
    s32 v3;
    s32 v4;
    s32 v0;
    s8 n;

    v1 = work->x4[work->cursor] << 8;
    v2 = work->x5[work->cursor] << 8;
    v3 = work->bgScrollX << 8;
    v4 = work->statsOffsetX << 8;
    v0 = work->x6 << 8;
    ApproachValue(&v0, -0x8000, work->headerSteps);
    ApproachValue(&v1, -0x8000, work->optionSteps[work->cursor]);
    ApproachValue(&v2, -0xF800, work->optionSteps[work->cursor]);
    work->x4[work->cursor] = v1 >> 8;
    work->x5[work->cursor] = v2 >> 8;
    work->x6 = v0 >> 8;
    work->headerSteps--;
    work->optionSteps[work->cursor]--;
    ApproachValue(&v3, 0, work->slideSteps);
    ApproachValue(&v4, 0x10000, work->slideSteps);
    ApproachValue(&work->x7, 0x1BE00, work->slideSteps);
    ApproachValue(&work->y6, 0x4800, work->slideSteps);

    if (gBtlWork->battleId == 151) {
        ScrollBgMapTo(0, v3 >> 8, 0);
    } else {
        ScrollBgMapTo(1, v3 >> 8, 0);
    }

    work->bgScrollX = v3 >> 8;
    work->statsOffsetX = v4 >> 8;

    if (work->slideSteps > 0) {
        work->slideSteps--;
    }

    n = work->slideSteps;

    if (n == 0) {
        if (work->barSteps != 0) {
            ApproachValue(&work->y, -0x800, work->barSteps);
            ApproachValue(&work->y2, 0xA000, work->barSteps);
            work->barSteps--;
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateLevelUpWaitFade);
        }
    }

    work->gfx = AnimUpdate(&work->anim2);
    TaskPoolUpdate(&work->pool);
    return 1;
}

u8 UpdateLevelUpWaitFade() {
    if (!FadeIsActive()) {
        return 0;
    }

    return 1;
}

void DrawLevelUpStatDigits(s16 x, s16 y, void* tiles, void* pal, void** gfx, u16* digits, u8 kind);

void Level_Up_2(LevelUpWork* work) {
    u8 i = 0;

    if (work->loaded[0] != 0) {
        switch (work->state) {
        case 0:
            DrawSprite(work->x6, 0,
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage][10],
#else
                       gUnk_09EEA1BC[10],
#endif
                       work->unk_000[6], work->unk_000[7], NULL, 0, 50);

            if (work->unk_000[0] != NULL) {
#ifdef VERSION_EU
                if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                    DrawSprite(work->x4[0], work->y4[0], gUnk_09EEA2BC[0], work->unk_000[0], work->unk_000[4], NULL, 0, 50);
#ifdef VERSION_EU
                } else {
                    DrawSprite(work->x4[0], work->y4[0], gUnkEu_09F7626C[0], work->unk_000[0], work->unk_000[4], NULL, 0, 50);
                }
#endif
            }

            if (work->unk_000[1] != NULL) {
#ifdef VERSION_EU
                if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                    DrawSprite(work->x4[1], work->y4[1], gUnk_09EEA2BC[1], work->unk_000[1], work->unk_000[4], NULL, 0, 50);
#ifdef VERSION_EU
                } else {
                    DrawSprite(work->x4[1], work->y4[1], gUnkEu_09F7626C[1], work->unk_000[1], work->unk_000[4], NULL, 0, 50);
                }
#endif
            }

            if (work->unk_000[2] != NULL) {
#ifdef VERSION_EU
                if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                    DrawSprite(work->x4[2], work->y4[2], gUnk_09EEA2BC[2], work->unk_000[2], work->unk_000[4], NULL, 0, 50);
#ifdef VERSION_EU
                } else {
                    DrawSprite(work->x4[2], work->y4[2], gUnkEu_09F7626C[2], work->unk_000[2], work->unk_000[4], NULL, 0, 50);
                }
#endif
            }

            DrawSprite(work->x, work->y >> 8, gUnk_09EEA1EC[0], work->tiles2, work->unk_000[7], NULL, SPRITE_PRIORITY(1), 51);
            DrawSprite(work->x2, work->y2 >> 8, gUnk_09EEA1EC[1], work->tiles2, work->unk_000[7], NULL, SPRITE_PRIORITY(1), 51);
            break;
        case 1:
            for (; i < 3; i++) {
                if (i == work->cursor) {
#ifdef VERSION_EU
                    DrawSprite(work->x5[i] + 5, work->y5[i] - 4, NULL, work->tiles5[i], work->palette, NULL, 0, 40);
#else
                    DrawTextSlots(work->x5[i] + 22, work->y5[i] - 5, work->textSlots[i], work->palette, 40, work->textSlotCounts[i]);
                    DrawTextSlots(work->x5[i] + 4, work->y5[i] + 13, work->textSlots[i + 3], work->palette, 40, work->textSlotCounts[i + 3]);
#endif
                } else {
#ifdef VERSION_EU
                    DrawSprite(work->x5[i] + 3, work->y5[i] - 2, NULL, work->tiles5[i], work->palette2, NULL, 0, 40);
#else
                    DrawTextSlots(work->x5[i] + 20, work->y5[i] - 3, work->textSlots[i], work->palette2, 40, work->textSlotCounts[i]);
                    DrawTextSlots(work->x5[i] + 2, work->y5[i] + 15, work->textSlots[i + 3], work->palette2, 40, work->textSlotCounts[i + 3]);
#endif
                }
            }

            DrawSprite(work->x3, work->y3, work->gfx2, work->tiles, work->palette3, NULL, 0, 40);
            break;
        case 2:
            for (; i < 3; i++) {
                if (i == work->cursor) {
#ifdef VERSION_EU
                    DrawSprite(work->x5[i] + 4, work->y5[i] - 3, NULL, work->tiles5[i], work->palette, NULL, 0, 40);
#else
                    DrawTextSlots(work->x5[i] + 22, work->y5[i] - 5, work->textSlots[i], work->palette, 40, work->textSlotCounts[i]);
                    DrawTextSlots(work->x5[i] + 4, work->y5[i] + 13, work->textSlots[i + 3], work->palette, 40, work->textSlotCounts[i + 3]);
#endif
                    DrawSprite(work->x4[i], work->y4[i], gUnk_09EEA2D8[i], work->unk_000[i], work->unk_000[5], NULL, 0, 50);
                } else {
                    if (work->unk_000[i] != NULL) {
#ifdef VERSION_EU
                        DrawSprite(work->x5[i] + 2, work->y5[i] - 1, NULL, work->tiles5[i], work->palette2, NULL, 0, 40);
#else
                        DrawTextSlots(work->x5[i] + 20, work->y5[i] - 3, work->textSlots[i], work->palette2, 40, work->textSlotCounts[i]);
                        DrawTextSlots(work->x5[i] + 2, work->y5[i] + 15, work->textSlots[i + 3], work->palette2, 40, work->textSlotCounts[i + 3]);
#endif
#ifdef VERSION_EU
                        if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                            DrawSprite(work->x4[i], work->y4[i], gUnk_09EEA2BC[i], work->unk_000[i], work->unk_000[4], NULL, 0, 50);
#ifdef VERSION_EU
                        } else {
                            DrawSprite(work->x4[i], work->y4[i], gUnkEu_09F7626C[i], work->unk_000[i], work->unk_000[4], NULL, 0, 50);
                        }
#endif
                    }
                }
            }

            DrawSprite(work->x3, work->y3, work->gfx2, work->tiles, work->palette3, NULL, 0, 40);
            break;
        case 3:
#ifdef VERSION_EU
            DrawSprite(work->x5[work->cursor] + 2, work->y5[work->cursor] - 1, NULL, work->tiles5[work->cursor], work->palette, NULL, 0, 40);
#else
            DrawTextSlots(work->x5[work->cursor] + 22, work->y5[work->cursor] - 5, work->textSlots[work->cursor], work->palette, 40, work->textSlotCounts[work->cursor]);
            DrawTextSlots(work->x5[work->cursor] + 4, work->y5[work->cursor] + 13, work->textSlots[work->cursor + 3], work->palette, 40, work->textSlotCounts[work->cursor + 3]);
#endif
            DrawSprite(work->x4[work->cursor], work->y4[work->cursor], NULL, work->unk_000[work->cursor], work->unk_000[5], NULL, 0, 50);
            DrawSprite(work->x6, 0,
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage][10],
#else
                       gUnk_09EEA1BC[10],
#endif
                       work->unk_000[6], work->unk_000[7], NULL, 0, 50);
            DrawSprite(work->x, work->y >> 8, gUnk_09EEA1EC[0], work->tiles2, work->unk_000[7], NULL, SPRITE_PRIORITY(1), 51);
            DrawSprite(work->x2, work->y2 >> 8, gUnk_09EEA1EC[1], work->tiles2, work->unk_000[7], NULL, SPRITE_PRIORITY(1), 51);
            break;
        }

#ifdef VERSION_JP
        if (work->blinkOn != 0) {
            DrawSprite(192, 82, gUnk_09EEA19C[0], work->tiles3, work->palette4, NULL, 0, 10);
        }
#endif

        if (!(gGameState.flags & GAME_FLAG_RIKU)) {
            DrawLevelUpStatDigits(work->statsOffsetX + 214, 17, work->unk_000[6], work->unk_000[7],
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage],
#else
                       gUnk_09EEA1BC,
#endif
                       work->levelDigits, 0);
            DrawLevelUpStatDigits(work->statsOffsetX + 214, 111, work->unk_000[6], work->unk_000[7],
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage],
#else
                       gUnk_09EEA1BC,
#endif
                       work->maxHpDigits, 1);
            DrawLevelUpStatDigits(work->statsOffsetX + 206, 132, work->unk_000[6], work->unk_000[7],
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage],
#else
                       gUnk_09EEA1BC,
#endif
                       work->cpDigits, 2);
        } else {
            DrawLevelUpStatDigits(work->statsOffsetX + 214, 17, work->unk_000[6], work->unk_000[7],
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage],
#else
                       gUnk_09EEA1BC,
#endif
                       work->levelDigits, 0);
            DrawLevelUpStatDigits(work->statsOffsetX + 214, 106, work->unk_000[6], work->unk_000[7],
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage],
#else
                       gUnk_09EEA1BC,
#endif
                       work->maxHpDigits, 1);
            DrawLevelUpStatDigits(work->statsOffsetX + 214, 122, work->unk_000[6], work->unk_000[7],
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage],
#else
                       gUnk_09EEA1BC,
#endif
                       work->apDigits, 4);
            DrawLevelUpStatDigits(work->statsOffsetX + 214, 137, work->unk_000[6], work->unk_000[7],
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage],
#else
                       gUnk_09EEA1BC,
#endif
                       work->dpDigits, 3);
        }
    }

    DrawSprite(work->x7 >> 8, work->y6 >> 8, work->gfx, work->tiles4, work->palette5, NULL, SPRITE_PRIORITY(1), 40);
    TaskPoolDraw(&work->pool);
}

void Level_Up_3(LevelUpWork* work) {
#ifdef VERSION_EU
    if (work->tiles5[0] != NULL) {
        ReleaseObjTiles(work->tiles5[0]);
    }

    if (work->tiles5[1] != NULL) {
        ReleaseObjTiles(work->tiles5[1]);
    }

    if (work->tiles5[2] != NULL) {
        ReleaseObjTiles(work->tiles5[2]);
    }
#else
    FreeTextSlots(work->textSlots[0], 36);
    FreeTextSlots(work->textSlots[1], 36);
    FreeTextSlots(work->textSlots[2], 36);
    FreeTextSlots(work->textSlots[3], 36);
    FreeTextSlots(work->textSlots[4], 36);
    FreeTextSlots(work->textSlots[5], 36);
#endif

    if (work->unk_000[6] != NULL) {
        ReleaseObjTiles(work->unk_000[6]);
    }

    if (work->unk_000[7] != NULL) {
        ReleaseObjPalette(work->unk_000[7]);
    }

    if (work->unk_000[0] != NULL) {
        ReleaseObjTiles(work->unk_000[0]);
    }

    if (work->unk_000[1] != NULL) {
        ReleaseObjTiles(work->unk_000[1]);
    }

    if (work->unk_000[2] != NULL) {
        ReleaseObjTiles(work->unk_000[2]);
    }

    if (work->unk_000[4] != NULL) {
        ReleaseObjPalette(work->unk_000[4]);
    }

    if (work->unk_000[5] != NULL) {
        ReleaseObjPalette(work->unk_000[5]);
    }

    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
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

    if (work->tiles3 != NULL) {
        ReleaseObjTiles(work->tiles3);
    }

    if (work->palette4 != NULL) {
        ReleaseObjPalette(work->palette4);
    }

    if (work->tiles4 != NULL) {
        ReleaseObjTiles(work->tiles4);
    }

    if (work->palette5 != NULL) {
        ReleaseObjPalette(work->palette5);
    }

    TaskPoolDestroy(&work->pool);
}

void DrawLevelUpStatDigits(s16 x, s16 y, void* tiles, void* pal, void** gfx, u16* digits, u8 kind) {
    switch (kind) {
    case 0:
        DrawSprite(x + 8, y, gfx[digits[1]], tiles, pal, NULL, 0, 0);
        x += 16;
        DrawSprite(x, y, gfx[digits[2]], tiles, pal, NULL, 0, 0);
        break;
    case 1:
        DrawSprite(x, y, gfx[digits[0]], tiles, pal, NULL, 0, 0);
        DrawSprite(x + 8, y, gfx[digits[1]], tiles, pal, NULL, 0, 0);
        x += 16;
        DrawSprite(x, y, gfx[digits[2]], tiles, pal, NULL, 0, 0);
        break;
    case 2:
        DrawSprite(x, y, gfx[digits[0]], tiles, pal, NULL, 0, 0);
        DrawSprite(x + 8, y, gfx[digits[1]], tiles, pal, NULL, 0, 0);
        DrawSprite(x + 16, y, gfx[digits[2]], tiles, pal, NULL, 0, 0);
        x += 24;
        DrawSprite(x, y, gfx[digits[3]], tiles, pal, NULL, 0, 0);
        break;
    case 4:
        DrawSprite(x + 8, y, gfx[digits[1]], tiles, pal, NULL, 0, 0);
        x += 16;
        DrawSprite(x, y, gfx[digits[2]], tiles, pal, NULL, 0, 0);
        break;
    case 3:
        DrawSprite(x, y, gfx[digits[0]], tiles, pal, NULL, 0, 0);
        DrawSprite(x + 8, y, gfx[digits[1]], tiles, pal, NULL, 0, 0);
        x += 16;
        DrawSprite(x, y, gfx[digits[2]], tiles, pal, NULL, 0, 0);
        break;
    }
}

void LevelUpSplitDigits2(u16 a, u16* p) {
    u16 q;
    u16 r;

    q = a / 10;
    r = a - q * 10;
    p[1] = q;
    p[2] = r;
}

void LevelUpSplitDigits3(u16 a, u16* p) {
    u16 h;
    u16 t;
    u16 o;

    h = a / 100;
    t = a / 10 - h * 10;
    o = a - h * 100 - t * 10;
    p[0] = h;
    p[1] = t;
    p[2] = o;
}

void LevelUpSplitDigits4(u16 n, u16* out) {
    u16 d3;
    u16 d2;
    u16 d1;
    u16 d0;

    d3 = n / 1000;
    d2 = n / 100 - d3 * 10;
    d1 = n / 10 - d2 * 10 - d3 * 100;
    d0 = n - d3 * 1000 - d2 * 100 - d1 * 10;
    out[0] = d3;
    out[1] = d2;
    out[2] = d1;
    out[3] = d0;
}

u8 UpdateLevelUpNextSlideIn(LevelUpWork* work, void* a) {
#ifdef VERSION_EU
    enum { tileSize = 0xC80, mapSize = 0x500 };
#else
    enum { tileSize = 0xD80, mapSize = 0x800 };
#endif

    if (work->loaded[0] == 0) {
        work->timer++;

        if (work->timer > 7) {
#ifdef VERSION_EU
            work->tiles5[0] = AllocSpriteFrameTiles(0x500);
            work->tiles5[1] = AllocSpriteFrameTiles(0x500);
            work->tiles5[2] = AllocSpriteFrameTiles(0x500);
#endif

            if (!(gGameState.flags & GAME_FLAG_RIKU)) {
                work->unk_000[0] = AllocSpriteFrameTiles(tileSize);
                work->unk_000[1] = AllocSpriteFrameTiles(tileSize);
                work->unk_000[2] = AllocSpriteFrameTiles(tileSize);

#ifdef VERSION_EU
                if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                    UpdateSpriteFrameTiles(work->unk_000[0], gUnk_09EEA2BC[0], gUnk_090950F4);
                    UpdateSpriteFrameTiles(work->unk_000[1], gUnk_09EEA2BC[1], gUnk_090950F4);
                    UpdateSpriteFrameTiles(work->unk_000[2], gUnk_09EEA2BC[2], gUnk_090950F4);
#ifdef VERSION_EU
                } else {
                    UpdateSpriteFrameTiles(work->unk_000[0], gUnkEu_09F7626C[0], gUnkEu_09172200);
                    UpdateSpriteFrameTiles(work->unk_000[1], gUnkEu_09F7626C[1], gUnkEu_09172200);
                    UpdateSpriteFrameTiles(work->unk_000[2], gUnkEu_09F7626C[2], gUnkEu_09172200);
                }
#endif

                work->unk_000[4] = LoadObjPalette(gUnk_09613F18, 32);
                work->unk_000[5] = LoadObjPalette(gUnk_09613F38, 32);
            } else {
                work->unk_000[0] = AllocSpriteFrameTiles(tileSize);
                work->unk_000[1] = AllocSpriteFrameTiles(tileSize);
                work->unk_000[2] = AllocSpriteFrameTiles(tileSize);

#ifdef VERSION_EU
                if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                    UpdateSpriteFrameTiles(work->unk_000[0], gUnk_09EEA29C[0], gUnk_09091D36);
                    UpdateSpriteFrameTiles(work->unk_000[1], gUnk_09EEA29C[1], gUnk_09091D36);
                    UpdateSpriteFrameTiles(work->unk_000[2], gUnk_09EEA29C[2], gUnk_09091D36);
#ifdef VERSION_EU
                } else {
                    UpdateSpriteFrameTiles(work->unk_000[0], gUnkEu_09F762A4[0], gUnkEu_091759BA);
                    UpdateSpriteFrameTiles(work->unk_000[1], gUnkEu_09F762A4[1], gUnkEu_091759BA);
                    UpdateSpriteFrameTiles(work->unk_000[2], gUnkEu_09F762A4[2], gUnkEu_091759BA);
                }
#endif

                work->unk_000[4] = LoadObjPalette(gUnk_09613EB8, 32);
                work->unk_000[5] = LoadObjPalette(gUnk_09613ED8, 32);
            }

#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                work->tiles3 = LoadObjTiles(gUnk_0908C686, 0x3E0);
                break;
            case LANGUAGE_FRENCH:
                work->tiles3 = LoadObjTiles(gUnkEu_0916F992, 0x3E0);
                break;
            case LANGUAGE_GERMAN:
                work->tiles3 = LoadObjTiles(gUnkEu_0917063A, 0x3E0);
                break;
            case LANGUAGE_ITALIAN:
                work->tiles3 = LoadObjTiles(gUnkEu_09170202, 0x3E0);
                break;
            case LANGUAGE_SPANISH:
                work->tiles3 = LoadObjTiles(gUnkEu_0916FDCA, 0x3E0);
                break;
            default:
                work->tiles3 = LoadObjTiles(gUnk_0908C686, 0x3E0);
                break;
            }
#else
            work->tiles3 = LoadObjTiles(gUnk_0908C686, 0x3E0);
#endif
            work->palette4 = LoadObjPalette(gCard00Palette, 32);
            FadeSetPaletteExcluded(((ObjPalette*)work->unk_000[4])->index + 16, 1);
            FadeSetPaletteExcluded(((ObjPalette*)work->unk_000[5])->index + 16, 1);
            FadeSetPaletteExcluded(work->palette4->index + 16, 1);
            work->tiles = AllocObjTiles(0x3C0, NULL);
            work->palette3 = LoadObjPalette(gUnk_09618CD8, 32);
            FadeSetPaletteExcluded(work->palette3->index + 16, 1);
            SetObjTileSource(work->tiles, gUnk_093F4578);
            AnimInit(&work->anim, gUnk_09EF1170, gUnk_09EF1150);
            AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);
            work->gfx2 = AnimGetGfx(&work->anim);
            work->loaded[0] = 1;
            work->timer = 0;
            FadeToAmount(FADE_MODE_BLACK, 8, 16);
        }

        return 1;
    }

    work->gfx = AnimUpdate(&work->anim2);

    {
        s32 x0 = work->x4[0] << 8;
        s32 x1 = work->x4[1] << 8;
        s32 x2 = work->x4[2] << 8;
        ApproachValue(&x0, 0x1000, work->optionSteps[0]);

        if (work->optionSteps[0] > 0) {
            work->optionSteps[0]--;
        }

        if (work->optionSteps[0] <= 6) {
            ApproachValue(&x1, 0x1000, work->optionSteps[1]);

            if (work->optionSteps[1] > 0) {
                work->optionSteps[1]--;
            }
        }

        if (work->optionSteps[1] <= 6) {
            ApproachValue(&x2, 0x1000, work->optionSteps[2]);

            if (work->optionSteps[2] > 0) {
                work->optionSteps[2]--;
            }
        }

        work->x4[0] = x0 >> 8;
        work->x4[1] = x1 >> 8;
        work->x4[2] = x2 >> 8;
    }

    if (work->optionSteps[2] == 0) {
        u8 i;

        if (gBtlWork->battleId == 151) {
            LoadBgMap(0, gUnk_095112B8, mapSize);
        } else {
            LoadBgMap(1, gUnk_095112B8, mapSize);
        }

        work->state = 1;

        if (!(gGameState.flags & GAME_FLAG_RIKU)) {
            if (gGameState.progression.maxHp > 559) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(work->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                work->textSlotCounts[0] = LoadTextSlots(gLevelUpSoraTexts[6], work->textSlots[0]);
                work->textSlotCounts[3] = 0;
#endif
                work->optionEnabled[0] = 0;
            } else {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(work->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][0], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                work->textSlotCounts[0] = LoadTextSlots(gLevelUpSoraTexts[0], work->textSlots[0]);
                work->textSlotCounts[3] = LoadTextSlots(gLevelUpSoraTexts[3], work->textSlots[3]);
#endif
            }

            if (gGameState.progression.cp > 1899) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(work->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                work->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[6], work->textSlots[1]);
                work->textSlotCounts[4] = 0;
#endif
                work->optionEnabled[1] = 0;
            } else {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(work->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][1], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                work->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[1], work->textSlots[1]);
                work->textSlotCounts[4] = LoadTextSlots(gLevelUpSoraTexts[4], work->textSlots[4]);
#endif
            }

            if (gGameState.progression.levelMilestone > 10) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(work->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                work->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[6], work->textSlots[2]);
                work->textSlotCounts[5] = 0;
#endif
                work->optionEnabled[2] = 0;
            } else if (!IsLevelUpStockUnlocked()) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(work->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                work->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[6], work->textSlots[2]);
                work->textSlotCounts[5] = 0;
#endif
                work->optionEnabled[2] = 0;
            } else {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(work->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][2], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                work->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[2], work->textSlots[2]);
                work->textSlotCounts[5] = LoadTextSlots(gLevelUpSoraTexts[5], work->textSlots[5]);
#endif
            }

            work->palette = LoadObjPalette(gUnk_09613F98, 32);
            work->palette2 = LoadObjPalette(gUnk_09613FB8, 32);
        } else {
            if (gGameState.progression.maxHp > 559) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(work->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                work->textSlotCounts[0] = LoadTextSlots(gLevelUpRikuTexts[6], work->textSlots[0]);
                work->textSlotCounts[3] = 0;
#endif
                work->optionEnabled[0] = 0;
            } else {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(work->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][3], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                work->textSlotCounts[0] = LoadTextSlots(gLevelUpRikuTexts[0], work->textSlots[0]);
                work->textSlotCounts[3] = LoadTextSlots(gLevelUpRikuTexts[3], work->textSlots[3]);
#endif
            }

            if (gGameState.progression.ap > 29) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(work->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                work->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[6], work->textSlots[1]);
                work->textSlotCounts[4] = 0;
#endif
                work->optionEnabled[1] = 0;
            } else if (!(u8)IsLevelUpApUnlocked()) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(work->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                work->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[6], work->textSlots[1]);
                work->textSlotCounts[4] = 0;
#endif
                work->optionEnabled[1] = 0;
            } else {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(work->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][4], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                work->textSlotCounts[1] = LoadTextSlots(gLevelUpRikuTexts[1], work->textSlots[1]);
                work->textSlotCounts[4] = LoadTextSlots(gLevelUpRikuTexts[4], work->textSlots[4]);
#endif
            }

            if (gGameState.progression.dp > 299) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(work->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                work->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[6], work->textSlots[2]);
                work->textSlotCounts[5] = 0;
#endif
                work->optionEnabled[2] = 0;
            } else {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(work->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][5], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                work->textSlotCounts[2] = LoadTextSlots(gLevelUpRikuTexts[2], work->textSlots[2]);
                work->textSlotCounts[5] = LoadTextSlots(gLevelUpRikuTexts[5], work->textSlots[5]);
#endif
            }

            work->palette = LoadObjPalette(gUnk_09613FD8, 32);
            work->palette2 = LoadObjPalette(gUnk_09613FF8, 32);
        }

        FadeSetPaletteExcluded(work->palette->index + 16, 1);
        FadeSetPaletteExcluded(work->palette2->index + 16, 1);

        for (i = 0; i < 3; i++) {
            if (work->optionEnabled[i] == 1) {
                break;
            }
        }

        work->cursor = i;
        work->y3 = sLevelUpCursorY[work->cursor];
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateLevelUpSelect);

        if (gBtlWork->battleId == 151) {
            LoadBgMap(0, gLevelUpOptionBgMaps[work->cursor], 0x800);
        } else {
            LoadBgMap(1, gLevelUpOptionBgMaps[work->cursor], 0x800);
        }
    }

    TaskPoolUpdate(&work->pool);
    return 1;
}

u8 UpdateLevelUpNextSlideOut(LevelUpWork* work, void* a) {
    s32 x;
    s32 y;
    s8 n;

    x = work->x4[work->cursor] << 8;
    y = work->x5[work->cursor] << 8;
    ApproachValue(&x, -0x8000, work->optionSteps[work->cursor]);
    ApproachValue(&y, -0xF800, work->optionSteps[work->cursor]);
    work->x4[work->cursor] = x >> 8;
    work->x5[work->cursor] = y >> 8;
    work->optionSteps[work->cursor]--;

    if (work->slideSteps > 0) {
        work->slideSteps--;
    }

    n = work->slideSteps;

    if (n == 0) {
        if (work->barSteps != 0) {
            ApproachValue(&work->y, 0, work->barSteps);
            ApproachValue(&work->y2, 0x9800, work->barSteps);
            work->barSteps--;
        } else {
            if (work->unk_000[0] != NULL) {
                ReleaseObjTiles(work->unk_000[0]);
            }

            if (work->unk_000[1] != NULL) {
                ReleaseObjTiles(work->unk_000[1]);
            }

            if (work->unk_000[2] != NULL) {
                ReleaseObjTiles(work->unk_000[2]);
            }

#ifdef VERSION_EU
            if (work->tiles5[0] != NULL) {
                ReleaseObjTiles(work->tiles5[0]);
            }

            if (work->tiles5[1] != NULL) {
                ReleaseObjTiles(work->tiles5[1]);
            }

            if (work->tiles5[2] != NULL) {
                ReleaseObjTiles(work->tiles5[2]);
            }
#endif

            if (work->unk_000[4] != NULL) {
                ReleaseObjPalette(work->unk_000[4]);
            }

            if (work->unk_000[5] != NULL) {
                ReleaseObjPalette(work->unk_000[5]);
            }

            if (work->palette != NULL) {
                ReleaseObjPalette(work->palette);
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

            if (work->tiles3 != NULL) {
                ReleaseObjTiles(work->tiles3);
            }

            if (work->palette4 != NULL) {
                ReleaseObjPalette(work->palette4);
            }

            work->x4[0] = 0xFF80;
            work->x4[1] = 0xFF80;
            work->x4[2] = 0xFF80;
            work->y4[0] = 16;
            work->y4[1] = 64;
            work->y4[2] = 112;
            work->slideSteps = 24;
            work->headerSteps = 16;
            work->optionSteps[0] = 16;
            work->optionSteps[1] = 16;
            work->optionSteps[2] = 16;
            work->x5[0] = 8;
            work->x5[1] = 8;
            work->x5[2] = 8;
            work->y5[0] = 31;
            work->y5[1] = 79;
            work->y5[2] = 127;
            work->x3 = 132;
            work->y3 = sLevelUpCursorY[0];

            if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
                SetObjTileSource(work->tiles4, gSor1ll51Tiles);
                AnimInit(&work->anim2, gSor1ll51Anims, gSor1ll51Frames);
                AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
            } else {
                SetObjTileSource(work->tiles4, gRikuBt00Tiles);
                AnimInit(&work->anim2, gRikuBt00Anims, gRikuBt00Frames);
                AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
            }

            work->loaded[0] = 0;
            work->state = 0;
            work->effectShown = 0;
            work->timer = 0;
            work->applied = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateLevelUpNextSlideIn);
        }
    }

    work->optionEnabled[0] = 1;
    work->optionEnabled[1] = 1;
    work->optionEnabled[2] = 1;
    work->gfx = AnimUpdate(&work->anim2);
    TaskPoolUpdate(&work->pool);
    return 1;
}

s32 IsLevelUpApUnlocked() {
    if (gGameState.progression.level >= sLevelUpApLevels[gGameState.progression.levelMilestone]) {
        return 1;
    }

    return 0;
}

#ifdef VERSION_EU
void* gLevelUpBgTilesByLanguage[5] = { gUnkEu_094CF704, gUnkEu_094D72E4, gUnkEu_094DB664, gUnkEu_094D9FE4, gUnkEu_094D8964 };
void* gLevelUpHeaderTilesByLanguage[5] = { gUnk_0908CAEC, gUnkEu_09170AA0, gUnkEu_09171B2C, gUnkEu_091715A8, gUnkEu_09171024 };

void** gUnk_09EEA1BC[5] = {
    gUnkEu_09F75FF4,
    gUnkEu_09F761AC,
    gUnkEu_09F7623C,
    gUnkEu_09F7620C,
    gUnkEu_09F761DC,
};

void* gLevelUpOptionTilesByLanguage[5] = {
    gUnkEu_09178D40,
    gUnkEu_09179CEE,
    gUnkEu_0917CFE2,
    gUnkEu_0917BFA6,
    gUnkEu_0917AF3A,
};

void** gLevelUpOptionSpritesByLanguage[5] = {
    gUnkEu_09F762C4,
    gUnkEu_09F762E4,
    gUnkEu_09F76344,
    gUnkEu_09F76324,
    gUnkEu_09F76304,
};
#endif

#ifndef VERSION_EU
u16* gLevelUpSoraTexts[7] = { gUnk_0815A066, gUnk_0815A0BA, gUnk_0815B1D2, gUnk_0815A078, gUnk_0815A0CC, gUnk_0815B1A8, (u16*)gLevelUpDisabledText };
u16* gLevelUpRikuTexts[7] = { gUnk_0815A066, gUnk_0815A116, gUnk_0815A158, gUnk_0815A0F4, gUnk_0815A130, gUnk_0815A176, (u16*)gLevelUpDisabledText };
#endif
const void* gLevelUpBgMapBlocks[2] = { gUnk_08125E24, gUnk_0950F2B8 };

void* gLevelUpOptionBgMaps[3] = { gUnk_095112B8, gUnk_09511AB8, gUnk_095122B8 };

TaskDesc gTaskDescLevelUp = {
    "Level_Up",
    (TaskInitFunc)Level_Up_0,
    (TaskUpdateFunc)Level_Up_1,
    (TaskDrawFunc)Level_Up_2,
    (TaskDestroyFunc)Level_Up_3,
    sizeof(LevelUpWork),
};
