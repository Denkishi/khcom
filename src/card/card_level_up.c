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
u8 UpdateLevelUpResult(struct LevelUpWork* w, void* a);
u8 UpdateLevelUpNextSlideOut(LevelUpWork* w, void* a);

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

void Level_Up_0(LevelUpWork* w) {
    s16 x;
    s16 y;

    w->tiles4 = NULL;
    w->palette5 = NULL;
    w->unk_000[0] = NULL;
    w->unk_000[1] = NULL;
    w->unk_000[2] = NULL;
    w->unk_000[3] = NULL;
    w->unk_000[4] = NULL;
    w->unk_000[5] = NULL;
    w->unk_000[6] = NULL;
    w->unk_000[7] = NULL;
    w->palette = NULL;
    w->palette2 = NULL;
    w->tiles = NULL;
    w->palette3 = NULL;
    w->tiles2 = NULL;
    w->tiles3 = NULL;
    w->palette4 = NULL;
    w->optionEnabled[0] = 1;
    w->optionEnabled[1] = 1;
    w->optionEnabled[2] = 1;

    if (gCardBattleState != NULL) {
        gCardBattleState->levelUpShown = 1;
    }

#ifndef VERSION_EU
    InitTextSlots(w->textSlots[0], 36);
    InitTextSlots(w->textSlots[1], 36);
    InitTextSlots(w->textSlots[2], 36);
    InitTextSlots(w->textSlots[3], 36);
    InitTextSlots(w->textSlots[4], 36);
    InitTextSlots(w->textSlots[5], 36);
    w->unk_000[6] = LoadObjTiles(gUnk_0908CAEC, 0x500);
#else
    w->unk_000[6] = LoadObjTiles(gLevelUpHeaderTilesByLanguage[gLanguage], sLevelUpHeaderTileSizesByLanguage[gLanguage]);
    w->tiles5[0] = AllocSpriteFrameTiles(0x500);
    w->tiles5[1] = AllocSpriteFrameTiles(0x500);
    w->tiles5[2] = AllocSpriteFrameTiles(0x500);
#endif
    w->unk_000[7] = LoadObjPalette(gUnk_09613E98 + 0x30, 32);
    FadeSetPaletteExcluded(((ObjPalette*)w->unk_000[7])->index + 16, 1);
    w->tiles2 = LoadObjTiles(gUnk_0908D05E, 0x3C0);
    TaskPoolInit(&w->pool, 10);

    if (!(gGameState.flags & GAME_FLAG_RIKU)) {
        w->tiles4 = AllocObjTiles(0x500, NULL);
        w->palette5 = AllocObjPalette(32);
        UpdateAllocatedObjPalette(w->palette5, gSoraPalette);
        FadeSetPaletteExcluded(w->palette5->index + 16, 1);
        WorldToScreen(&x, &y, gBtlWork->actor->x,
                      gBtlWork->actor->y,
                      gBtlWork->actor->z);
        SetObjTileSource(w->tiles4, gSor1ll51Tiles);
        AnimInit(&w->anim2, gSor1ll51Anims, gSor1ll51Frames);
        AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
    } else {
        w->tiles4 = AllocObjTiles(0x800, NULL);
        w->palette5 = AllocObjPalette(32);
        UpdateAllocatedObjPalette(w->palette5, gRikuPalette);
        FadeSetPaletteExcluded(w->palette5->index + 16, 1);
        WorldToScreen(&x, &y, gBtlWork->actor->x,
                      gBtlWork->actor->y,
                      gBtlWork->actor->z);
        SetObjTileSource(w->tiles4, gRikuBt00Tiles);
        AnimInit(&w->anim2, gRikuBt00Anims, gRikuBt00Frames);
        AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
    }

    if (gBtlWork->flags & BTL_FLAG_FIELD_HIDDEN) {
        w->x7 = 0x1C400;
        w->y6 = 0x5000;
    } else {
        w->x7 = x << 8;
        w->y6 = y << 8;
    }

    w->gfx = AnimGetGfx(&w->anim2);

    if (!(gBtlWork->flags & BTL_FLAG_BOSS_BATTLE)) {
        w->bossBattle = 0;
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
        w->bossBattle = 1;

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
    w->x6 = -128;
    w->x4[0] = -128;
    w->x4[1] = -128;
    w->x4[2] = -128;
    w->y4[0] = 16;
    w->y4[1] = 64;
    w->y4[2] = 112;
    w->slideSteps = 24;
    w->headerSteps = 16;
    w->optionSteps[0] = 16;
    w->optionSteps[1] = 16;
    w->optionSteps[2] = 16;
    w->x5[0] = 8;
    w->x5[1] = 8;
    w->x5[2] = 8;
    w->y5[0] = 31;
    w->y5[1] = 79;
    w->y5[2] = 127;
    w->x = 128;
    w->x2 = 128;
    w->y = -0x800;
    w->y2 = 0xA000;
    w->barSteps = 16;
    w->bgScrollX = 0;
    w->statsOffsetX = 256;
    w->x3 = 132;
    w->y3 = sLevelUpCursorY[0];
    w->state = 0;
    w->cursor = 0;
    w->applied = 0;
    LevelUpSplitDigits3(gGameState.progression.level, w->levelDigits);
    LevelUpSplitDigits3(gGameState.progression.maxHp, w->maxHpDigits);
    LevelUpSplitDigits4(gGameState.progression.cp, w->cpDigits);
    LevelUpSplitDigits3(gGameState.progression.dp, w->dpDigits);
    LevelUpSplitDigits2(gGameState.progression.ap, w->apDigits);
    w->timer = 0;
    w->loaded[1] = 0;
    w->loaded[0] = 0;
    w->blinkTimer = 0;
    w->blinkOn = 0;
    w->playerSteps = 16;
    w->effectShown = 0;
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

u8 UpdateLevelUpSelect(LevelUpWork* w, void* a);

u8 Level_Up_1(LevelUpWork* w, void* a) {
    s32 x[3];
#ifdef VERSION_EU
    enum { tileSize = 0xC80, mapSize = 0x500, bgSize = 0x2C00 };
#else
    enum { tileSize = 0xD80, mapSize = 0x800, bgSize = 0x3680 };
#endif

    if (w->loaded[1] == 0) {
        w->timer++;

        if (w->timer > 7) {
            if (w->bossBattle == 0) {
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
            w->loaded[1] = 1;
            w->timer = 0;
            return 1;
        }

        return 1;
    }

    if (w->loaded[0] == 0) {
        w->timer++;

        if (w->timer > 7) {
            if (!(gGameState.flags & GAME_FLAG_RIKU)) {
                w->unk_000[0] = AllocSpriteFrameTiles(tileSize);
                w->unk_000[1] = AllocSpriteFrameTiles(tileSize);
                w->unk_000[2] = AllocSpriteFrameTiles(tileSize);

#ifdef VERSION_EU
                if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                    UpdateSpriteFrameTiles(w->unk_000[0], gUnk_09EEA2BC[0], gUnk_090950F4);
                    UpdateSpriteFrameTiles(w->unk_000[1], gUnk_09EEA2BC[1], gUnk_090950F4);
                    UpdateSpriteFrameTiles(w->unk_000[2], gUnk_09EEA2BC[2], gUnk_090950F4);
#ifdef VERSION_EU
                } else {
                    UpdateSpriteFrameTiles(w->unk_000[0], gUnkEu_09F7626C[0], gUnkEu_09172200);
                    UpdateSpriteFrameTiles(w->unk_000[1], gUnkEu_09F7626C[1], gUnkEu_09172200);
                    UpdateSpriteFrameTiles(w->unk_000[2], gUnkEu_09F7626C[2], gUnkEu_09172200);
                }
#endif

                w->unk_000[4] = LoadObjPalette(gUnk_09613F18, 32);
                w->unk_000[5] = LoadObjPalette(gUnk_09613F38, 32);
            } else {
                w->unk_000[0] = AllocSpriteFrameTiles(tileSize);
                w->unk_000[1] = AllocSpriteFrameTiles(tileSize);
                w->unk_000[2] = AllocSpriteFrameTiles(tileSize);

#ifdef VERSION_EU
                if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                    UpdateSpriteFrameTiles(w->unk_000[0], gUnk_09EEA29C[0], gUnk_09091D36);
                    UpdateSpriteFrameTiles(w->unk_000[1], gUnk_09EEA29C[1], gUnk_09091D36);
                    UpdateSpriteFrameTiles(w->unk_000[2], gUnk_09EEA29C[2], gUnk_09091D36);
#ifdef VERSION_EU
                } else {
                    UpdateSpriteFrameTiles(w->unk_000[0], gUnkEu_09F762A4[0], gUnkEu_091759BA);
                    UpdateSpriteFrameTiles(w->unk_000[1], gUnkEu_09F762A4[1], gUnkEu_091759BA);
                    UpdateSpriteFrameTiles(w->unk_000[2], gUnkEu_09F762A4[2], gUnkEu_091759BA);
                }
#endif

                w->unk_000[4] = LoadObjPalette(gUnk_09613EB8, 32);
                w->unk_000[5] = LoadObjPalette(gUnk_09613ED8, 32);
            }

#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                w->tiles3 = LoadObjTiles(gUnk_0908C686, 0x3E0);
                break;
            case LANGUAGE_FRENCH:
                w->tiles3 = LoadObjTiles(gUnkEu_0916F992, 0x3E0);
                break;
            case LANGUAGE_GERMAN:
                w->tiles3 = LoadObjTiles(gUnkEu_0917063A, 0x3E0);
                break;
            case LANGUAGE_ITALIAN:
                w->tiles3 = LoadObjTiles(gUnkEu_09170202, 0x3E0);
                break;
            case LANGUAGE_SPANISH:
                w->tiles3 = LoadObjTiles(gUnkEu_0916FDCA, 0x3E0);
                break;
            default:
                w->tiles3 = LoadObjTiles(gUnk_0908C686, 0x3E0);
                break;
            }
#else
            w->tiles3 = LoadObjTiles(gUnk_0908C686, 0x3E0);
#endif
            w->palette4 = LoadObjPalette(gCard00Palette, 32);
            FadeSetPaletteExcluded(((ObjPalette*)w->unk_000[4])->index + 16, 1);
            FadeSetPaletteExcluded(((ObjPalette*)w->unk_000[5])->index + 16, 1);
            FadeSetPaletteExcluded(w->palette4->index + 16, 1);
            w->tiles = AllocObjTiles(0x3C0, NULL);
            w->palette3 = LoadObjPalette(gUnk_09618CD8, 32);
            FadeSetPaletteExcluded(w->palette3->index + 16, 1);
            SetObjTileSource(w->tiles, gUnk_093F4578);
            AnimInit(&w->anim, gUnk_09EF1170, gUnk_09EF1150);
            AnimStart(&w->anim, 2, ANIM_FLAG_LOOP);
            w->gfx2 = AnimGetGfx(&w->anim);
            w->loaded[0] = 1;
            w->timer = 0;
            FadeToAmount(FADE_MODE_BLACK, 8, 16);
        }

        return 1;
    }

    w->gfx = AnimUpdate(&w->anim2);

    if (w->playerSteps != 0) {
        ApproachValue(&w->x7, 0xBE00, w->playerSteps);
        ApproachValue(&w->y6, 0x5000, w->playerSteps);
        w->playerSteps--;
    }

    if (w->barSteps != 0) {
        ApproachValue(&w->y, 0, w->barSteps);
        ApproachValue(&w->y2, 0x9800, w->barSteps);
        w->barSteps--;
    } else {
        s32 x3 = w->bgScrollX << 8;
        s32 x4 = w->statsOffsetX << 8;
        ApproachValue(&x3, 0x10000, w->slideSteps);
        ApproachValue(&x4, 0, w->slideSteps);

        if (gBtlWork->battleId == 151) {
            ScrollBgMapTo(0, x3 >> 8, 0);
        } else {
            ScrollBgMapTo(1, x3 >> 8, 0);
        }

        w->bgScrollX = x3 >> 8;
        w->statsOffsetX = x4 >> 8;

        if (w->slideSteps > 0) {
            w->slideSteps--;
        }

        if (w->slideSteps <= 11) {
            s32 x5 = w->x6 << 8;
            ApproachValue(&x5, 0, w->headerSteps);
            w->x6 = x5 >> 8;

            if (w->headerSteps > 0) {
                w->headerSteps--;
            }

            if (w->headerSteps <= 6) {
                x[0] = w->x4[0] << 8;
                x[1] = w->x4[1] << 8;
                x[2] = w->x4[2] << 8;
                ApproachValue(&x[0], 0x1000, w->optionSteps[0]);

                if (w->optionSteps[0] > 0) {
                    w->optionSteps[0]--;
                }

                if (w->optionSteps[0] <= 6) {
                    ApproachValue(&x[1], 0x1000, w->optionSteps[1]);

                    if (w->optionSteps[1] > 0) {
                        w->optionSteps[1]--;
                    }
                }

                if (w->optionSteps[1] <= 6) {
                    ApproachValue(&x[2], 0x1000, w->optionSteps[2]);

                    if (w->optionSteps[2] > 0) {
                        w->optionSteps[2]--;
                    }
                }

                w->x4[0] = x[0] >> 8;
                w->x4[1] = x[1] >> 8;
                w->x4[2] = x[2] >> 8;

                if (w->optionSteps[2] == 0) {
                    u8 i;

                    if (gBtlWork->battleId == 151) {
                        LoadBgMap(0, gUnk_095112B8, mapSize);
                    } else {
                        LoadBgMap(1, gUnk_095112B8, mapSize);
                    }

                    w->state = 1;

                    if (!(gGameState.flags & GAME_FLAG_RIKU)) {
                        if (gGameState.progression.maxHp > 559) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(w->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            w->textSlotCounts[0] = LoadTextSlots(gLevelUpSoraTexts[6], w->textSlots[0]);
                            w->textSlotCounts[3] = 0;
#endif
                            w->optionEnabled[0] = 0;
                        } else {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(w->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][0], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            w->textSlotCounts[0] = LoadTextSlots(gLevelUpSoraTexts[0], w->textSlots[0]);
                            w->textSlotCounts[3] = LoadTextSlots(gLevelUpSoraTexts[3], w->textSlots[3]);
#endif
                        }

                        if (gGameState.progression.cp > 1899) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(w->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            w->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[6], w->textSlots[1]);
                            w->textSlotCounts[4] = 0;
#endif
                            w->optionEnabled[1] = 0;
                        } else {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(w->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][1], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            w->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[1], w->textSlots[1]);
                            w->textSlotCounts[4] = LoadTextSlots(gLevelUpSoraTexts[4], w->textSlots[4]);
#endif
                        }

                        if (gGameState.progression.levelMilestone > 10) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(w->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            w->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[6], w->textSlots[2]);
                            w->textSlotCounts[5] = 0;
#endif
                            w->optionEnabled[2] = 0;
                        } else if (IsLevelUpStockUnlocked() == 0) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(w->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            w->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[6], w->textSlots[2]);
                            w->textSlotCounts[5] = 0;
#endif
                            w->optionEnabled[2] = 0;
                        } else {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(w->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][2], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            w->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[2], w->textSlots[2]);
                            w->textSlotCounts[5] = LoadTextSlots(gLevelUpSoraTexts[5], w->textSlots[5]);
#endif
                        }

                        w->palette = LoadObjPalette(gUnk_09613F98, 32);
                        w->palette2 = LoadObjPalette(gUnk_09613FB8, 32);
                    } else {
                        if (gGameState.progression.maxHp > 559) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(w->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            w->textSlotCounts[0] = LoadTextSlots(gLevelUpRikuTexts[6], w->textSlots[0]);
                            w->textSlotCounts[3] = 0;
#endif
                            w->optionEnabled[0] = 0;
                        } else {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(w->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][3], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            w->textSlotCounts[0] = LoadTextSlots(gLevelUpRikuTexts[0], w->textSlots[0]);
                            w->textSlotCounts[3] = LoadTextSlots(gLevelUpRikuTexts[3], w->textSlots[3]);
#endif
                        }

                        if (gGameState.progression.ap > 29) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(w->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            w->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[6], w->textSlots[1]);
                            w->textSlotCounts[4] = 0;
#endif
                            w->optionEnabled[1] = 0;
                        } else if ((u8)IsLevelUpApUnlocked() == 0) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(w->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            w->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[6], w->textSlots[1]);
                            w->textSlotCounts[4] = 0;
#endif
                            w->optionEnabled[1] = 0;
                        } else {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(w->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][4], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            w->textSlotCounts[1] = LoadTextSlots(gLevelUpRikuTexts[1], w->textSlots[1]);
                            w->textSlotCounts[4] = LoadTextSlots(gLevelUpRikuTexts[4], w->textSlots[4]);
#endif
                        }

                        if (gGameState.progression.dp > 299) {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(w->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            w->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[6], w->textSlots[2]);
                            w->textSlotCounts[5] = 0;
#endif
                            w->optionEnabled[2] = 0;
                        } else {
#ifdef VERSION_EU
                            UpdateSpriteFrameTiles(w->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][5], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                            w->textSlotCounts[2] = LoadTextSlots(gLevelUpRikuTexts[2], w->textSlots[2]);
                            w->textSlotCounts[5] = LoadTextSlots(gLevelUpRikuTexts[5], w->textSlots[5]);
#endif
                        }

                        w->palette = LoadObjPalette(gUnk_09613FD8, 32);
                        w->palette2 = LoadObjPalette(gUnk_09613FF8, 32);
                    }

                    FadeSetPaletteExcluded(w->palette->index + 16, 1);
                    FadeSetPaletteExcluded(w->palette2->index + 16, 1);

                    for (i = 0; i < 3; i++) {
                        if (w->optionEnabled[i] == 1) {
                            break;
                        }
                    }

                    w->cursor = i;
                    w->y3 = sLevelUpCursorY[w->cursor];
                    SetTaskUpdate(a, (TaskUpdateFunc)UpdateLevelUpSelect);

                    if (gBtlWork->battleId == 151) {
                        LoadBgMap(0, gLevelUpOptionBgMaps[w->cursor], 0x800);
                    } else {
                        LoadBgMap(1, gLevelUpOptionBgMaps[w->cursor], 0x800);
                    }
                }
            }
        }
    }

    TaskPoolUpdate(&w->pool);
    return 1;
}

u8 UpdateLevelUpSelect(LevelUpWork* w, void* a) {
    s32 x;
    s8 i;
    u8* q;
#ifdef VERSION_EU
    enum { mapOffset = 0x20C0, mapSize = 0x500, palOffset = 0x1190 };
#else
    enum { mapOffset = 0x7C0, mapSize = 0x800, palOffset = 0x1250 };
#endif

    if (GetKeysRepeat() & DPAD_DOWN) {
        i = w->cursor;
        q = w->optionEnabled;

        do {
            i++;

            if (i > 2) {
                i = 0;
            }
        } while (q[i] == 0);

        if (i != w->cursor) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        w->cursor = i;

        if (gBtlWork->battleId == 151) {
            LoadBgMap(0, gLevelUpOptionBgMaps[w->cursor], 0x800);
        } else {
            LoadBgMap(1, gLevelUpOptionBgMaps[w->cursor], 0x800);
        }

        w->cursorSteps = 8;
    }

    if (GetKeysRepeat() & DPAD_UP) {
        i = w->cursor;
        q = w->optionEnabled;

        do {
            i--;

            if (i < 0) {
                i = 2;
            }
        } while (q[i] == 0);

        if (i != w->cursor) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        w->cursor = i;

        if (gBtlWork->battleId == 151) {
            LoadBgMap(0, gLevelUpOptionBgMaps[w->cursor], 0x800);
        } else {
            LoadBgMap(1, gLevelUpOptionBgMaps[w->cursor], 0x800);
        }

        w->cursorSteps = 8;
    }

    while (GetKeysRepeat() & A_BUTTON) {
        w->state = 2;

        if (gBtlWork->battleId == 151) {
            LoadBgMap(0, &gUnk_0950E2F8[mapOffset], mapSize);
        } else {
            LoadBgMap(1, &gUnk_0950E2F8[mapOffset], mapSize);
        }

        w->optionSteps[0] = 16;
        w->optionSteps[1] = 16;
        w->optionSteps[2] = 16;
        m4aSongNumStart(SONG_SYS_KETTEI);
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette3);
        w->tiles = AllocObjTiles(128, NULL);
        w->palette3 = LoadObjPalette(&gCard00Palette[palOffset], 32);
        FadeSetPaletteExcluded(w->palette3->index + 16, 1);
        SetObjTileSource(w->tiles, gUnk_0908F190);
        AnimInit(&w->anim, gUnk_09EEA280, gUnk_09EEA26C);
        AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
        w->gfx2 = AnimGetGfx(&w->anim);
        w->cursorSteps = 16;
        w->x3 = 136;

        if (!(gGameState.flags & GAME_FLAG_RIKU)) {
            SetObjTileSource(w->tiles4, gSor1ff00Tiles);
            AnimInit(&w->anim2, gSor1ff00Anims, gSor1ff00Frames);
            AnimStart(&w->anim2, 1, 0);
        } else {
            SetObjTileSource(w->tiles4, gRikuFf00Tiles);
            AnimInit(&w->anim2, gRikuFf00Anims, gRikuFf00Frames);
            AnimStart(&w->anim2, 1, 0);
        }

        SetTaskUpdate(a, (TaskUpdateFunc)UpdateLevelUpResult);
        return 1;
    }

    x = w->y3 << 8;
    ApproachValue(&x, sLevelUpCursorY[w->cursor] << 8, w->cursorSteps);
    w->cursorSteps--;
    w->y3 = x >> 8;
    w->gfx2 = AnimUpdate(&w->anim);
    w->blinkTimer++;

    if (w->blinkTimer == 32) {
        w->blinkTimer = 0;
        w->blinkOn ^= 1;
    }

    w->gfx = AnimUpdate(&w->anim2);
    TaskPoolUpdate(&w->pool);
    return 1;
}

u8 UpdateLevelUpClose(LevelUpWork* w, void* a);

u8 UpdateLevelUpResult(LevelUpWork* w, void* a) {
    u8 i;

    if (w->effectShown == 0) {
#ifndef VERSION_US
        LevelUpEffectArgs args;
        args.x = 192;
        args.y = 60;
        args.unk_08 = 0;
        args.target = NULL;
        TaskCreate(&w->pool, &gTaskDescLVUPEFFECT, &args);
        m4aSongNumStart(SONG_SYS_LVUP);
#endif
        w->effectShown++;
    }

    for (i = 0; i < 3; i++) {
        if (i != w->cursor) {
            s32 x = w->x4[i] << 8;
            s32 y = w->x5[i] << 8;
            ApproachValue(&x, -0x10000, w->optionSteps[i]);
            ApproachValue(&y, -0xF800, w->optionSteps[i]);
            w->x4[i] = x >> 8;
            w->x5[i] = y >> 8;
        } else {
            s32 x = w->y4[i] << 8;
            s32 y = w->y5[i] << 8;
            ApproachValue(&x, 0x2000, w->optionSteps[i]);
            ApproachValue(&y, 0x3100, w->optionSteps[i]);
            w->y4[i] = x >> 8;
            w->y5[i] = y >> 8;
        }

        if (w->optionSteps[i] > 0) {
            w->optionSteps[i]--;
        }
    }

    if (w->optionSteps[0] == 0) {
        for (i = 0; i < 3; i++) {
            if (i != w->cursor && w->unk_000[i] != NULL) {
                ReleaseObjTiles(w->unk_000[i]);
                w->unk_000[i] = NULL;
            }
        }

        if (w->applied == 0) {
            switch (w->cursor) {
            case 0: {
                s32 amount = LevelUpMaxHp();
                StatIncreaseDisplayArgs args;
                w->messageActive = 1;
                args.amount = amount;
                args.done = &w->messageActive;
                args.flags = STAT_INCREASE_FLAG_MAX_HP;
                TaskCreate(&w->pool, &gTaskDescLvupMsg, &args);
                break;
            }
            case 1:
                if (!(gGameState.flags & GAME_FLAG_RIKU)) {
                    s32 amount = LevelUpCp();
                    StatIncreaseDisplayArgs args;
                    w->messageActive = 1;
                    args.amount = amount;
                    args.done = &w->messageActive;
                    args.flags = 0;
                    TaskCreate(&w->pool, &gTaskDescLvupMsg, &args);
                } else {
                    s32 amount = LevelUpAp();
                    StatIncreaseDisplayArgs args;
                    w->messageActive = 1;
                    args.amount = amount;
                    args.done = &w->messageActive;
                    args.flags = 0;
                    gGameState.progression.levelMilestone++;
                    TaskCreate(&w->pool, &gTaskDescLvupMsg, &args);
                }

                break;
            case 2:
                if (!(gGameState.flags & GAME_FLAG_RIKU)) {
                    w->messageActive = 1;
                    TaskCreate(&w->pool, &gTaskDescStockInfo, &w->messageActive);
                } else {
                    s32 amount = LevelUpDp();
                    StatIncreaseDisplayArgs args;
                    w->messageActive = 1;
                    args.amount = amount;
                    args.done = &w->messageActive;
                    args.flags = STAT_INCREASE_FLAG_DP;
                    TaskCreate(&w->pool, &gTaskDescLvupMsg, &args);
                }

                break;
            }

            LevelUpSplitDigits3(gGameState.progression.maxHp, w->maxHpDigits);
            LevelUpSplitDigits4(gGameState.progression.cp, w->cpDigits);
            LevelUpSplitDigits3(gGameState.progression.dp, w->dpDigits);
            LevelUpSplitDigits2(gGameState.progression.ap, w->apDigits);
            w->applied = 1;
        }
    }

    {
        s32 y = w->y3 << 8;
        ApproachValue(&y, 0x3000, w->cursorSteps);
        w->cursorSteps--;
        w->y3 = y >> 8;
    }

    TaskPoolUpdate(&w->pool);
    w->blinkTimer++;

    if (w->blinkTimer == 32) {
        w->blinkTimer = 0;
        w->blinkOn ^= 1;
    }

    if (w->timer == 180) {
        if (GetKeysPressed() & A_BUTTON) {
            if (gBtlWork->battleId == 151) {
                SetBgMapBlocks(0, gLevelUpBgMapBlocks, 2, 1);
            } else {
                SetBgMapBlocks(1, gLevelUpBgMapBlocks, 2, 1);
            }

            w->headerSteps = 16;
            w->slideSteps = 16;
            w->optionSteps[w->cursor] = 16;
            w->barSteps = 16;
            w->state = 3;
            w->blinkOn = 0;
            w->messageActive = 0;
            gBtlWork->pendingLevelUps--;

            if (gBtlWork->pendingLevelUps == 0) {
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateLevelUpClose);
            } else {
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateLevelUpNextSlideOut);
            }

            m4aSongNumStart(SONG_SYS_KETTEI);
        }
    } else {
        w->timer++;
    }

    w->gfx2 = AnimUpdate(&w->anim);
    w->gfx = AnimUpdate(&w->anim2);
    return 1;
}

u8 UpdateLevelUpClose(LevelUpWork* w, void* a) {
    s32 v1;
    s32 v2;
    s32 v3;
    s32 v4;
    s32 v0;
    s8 n;

    v1 = w->x4[w->cursor] << 8;
    v2 = w->x5[w->cursor] << 8;
    v3 = w->bgScrollX << 8;
    v4 = w->statsOffsetX << 8;
    v0 = w->x6 << 8;
    ApproachValue(&v0, -0x8000, w->headerSteps);
    ApproachValue(&v1, -0x8000, w->optionSteps[w->cursor]);
    ApproachValue(&v2, -0xF800, w->optionSteps[w->cursor]);
    w->x4[w->cursor] = v1 >> 8;
    w->x5[w->cursor] = v2 >> 8;
    w->x6 = v0 >> 8;
    w->headerSteps--;
    w->optionSteps[w->cursor]--;
    ApproachValue(&v3, 0, w->slideSteps);
    ApproachValue(&v4, 0x10000, w->slideSteps);
    ApproachValue(&w->x7, 0x1BE00, w->slideSteps);
    ApproachValue(&w->y6, 0x4800, w->slideSteps);

    if (gBtlWork->battleId == 151) {
        ScrollBgMapTo(0, v3 >> 8, 0);
    } else {
        ScrollBgMapTo(1, v3 >> 8, 0);
    }

    w->bgScrollX = v3 >> 8;
    w->statsOffsetX = v4 >> 8;

    if (w->slideSteps > 0) {
        w->slideSteps--;
    }

    n = w->slideSteps;

    if (n == 0) {
        if (w->barSteps != 0) {
            ApproachValue(&w->y, -0x800, w->barSteps);
            ApproachValue(&w->y2, 0xA000, w->barSteps);
            w->barSteps--;
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateLevelUpWaitFade);
        }
    }

    w->gfx = AnimUpdate(&w->anim2);
    TaskPoolUpdate(&w->pool);
    return 1;
}

u8 UpdateLevelUpWaitFade() {
    if (FadeIsActive() == 0) {
        return 0;
    }

    return 1;
}

void DrawLevelUpStatDigits(s16 x, s16 y, void* tiles, void* pal, void** gfx, u16* digits, u8 kind);

void Level_Up_2(LevelUpWork* w) {
    u8 i = 0;

    if (w->loaded[0] != 0) {
        switch (w->state) {
        case 0:
            DrawSprite(w->x6, 0,
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage][10],
#else
                       gUnk_09EEA1BC[10],
#endif
                       w->unk_000[6], w->unk_000[7], NULL, 0, 50);

            if (w->unk_000[0] != NULL) {
#ifdef VERSION_EU
                if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                    DrawSprite(w->x4[0], w->y4[0], gUnk_09EEA2BC[0], w->unk_000[0], w->unk_000[4], NULL, 0, 50);
#ifdef VERSION_EU
                } else {
                    DrawSprite(w->x4[0], w->y4[0], gUnkEu_09F7626C[0], w->unk_000[0], w->unk_000[4], NULL, 0, 50);
                }
#endif
            }

            if (w->unk_000[1] != NULL) {
#ifdef VERSION_EU
                if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                    DrawSprite(w->x4[1], w->y4[1], gUnk_09EEA2BC[1], w->unk_000[1], w->unk_000[4], NULL, 0, 50);
#ifdef VERSION_EU
                } else {
                    DrawSprite(w->x4[1], w->y4[1], gUnkEu_09F7626C[1], w->unk_000[1], w->unk_000[4], NULL, 0, 50);
                }
#endif
            }

            if (w->unk_000[2] != NULL) {
#ifdef VERSION_EU
                if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                    DrawSprite(w->x4[2], w->y4[2], gUnk_09EEA2BC[2], w->unk_000[2], w->unk_000[4], NULL, 0, 50);
#ifdef VERSION_EU
                } else {
                    DrawSprite(w->x4[2], w->y4[2], gUnkEu_09F7626C[2], w->unk_000[2], w->unk_000[4], NULL, 0, 50);
                }
#endif
            }

            DrawSprite(w->x, w->y >> 8, gUnk_09EEA1EC[0], w->tiles2, w->unk_000[7], NULL, SPRITE_PRIORITY(1), 51);
            DrawSprite(w->x2, w->y2 >> 8, gUnk_09EEA1EC[1], w->tiles2, w->unk_000[7], NULL, SPRITE_PRIORITY(1), 51);
            break;
        case 1:
            for (; i < 3; i++) {
                if (i == w->cursor) {
#ifdef VERSION_EU
                    DrawSprite(w->x5[i] + 5, w->y5[i] - 4, NULL, w->tiles5[i], w->palette, NULL, 0, 40);
#else
                    DrawTextSlots(w->x5[i] + 22, w->y5[i] - 5, w->textSlots[i], w->palette, 40, w->textSlotCounts[i]);
                    DrawTextSlots(w->x5[i] + 4, w->y5[i] + 13, w->textSlots[i + 3], w->palette, 40, w->textSlotCounts[i + 3]);
#endif
                } else {
#ifdef VERSION_EU
                    DrawSprite(w->x5[i] + 3, w->y5[i] - 2, NULL, w->tiles5[i], w->palette2, NULL, 0, 40);
#else
                    DrawTextSlots(w->x5[i] + 20, w->y5[i] - 3, w->textSlots[i], w->palette2, 40, w->textSlotCounts[i]);
                    DrawTextSlots(w->x5[i] + 2, w->y5[i] + 15, w->textSlots[i + 3], w->palette2, 40, w->textSlotCounts[i + 3]);
#endif
                }
            }

            DrawSprite(w->x3, w->y3, w->gfx2, w->tiles, w->palette3, NULL, 0, 40);
            break;
        case 2:
            for (; i < 3; i++) {
                if (i == w->cursor) {
#ifdef VERSION_EU
                    DrawSprite(w->x5[i] + 4, w->y5[i] - 3, NULL, w->tiles5[i], w->palette, NULL, 0, 40);
#else
                    DrawTextSlots(w->x5[i] + 22, w->y5[i] - 5, w->textSlots[i], w->palette, 40, w->textSlotCounts[i]);
                    DrawTextSlots(w->x5[i] + 4, w->y5[i] + 13, w->textSlots[i + 3], w->palette, 40, w->textSlotCounts[i + 3]);
#endif
                    DrawSprite(w->x4[i], w->y4[i], gUnk_09EEA2D8[i], w->unk_000[i], w->unk_000[5], NULL, 0, 50);
                } else {
                    if (w->unk_000[i] != NULL) {
#ifdef VERSION_EU
                        DrawSprite(w->x5[i] + 2, w->y5[i] - 1, NULL, w->tiles5[i], w->palette2, NULL, 0, 40);
#else
                        DrawTextSlots(w->x5[i] + 20, w->y5[i] - 3, w->textSlots[i], w->palette2, 40, w->textSlotCounts[i]);
                        DrawTextSlots(w->x5[i] + 2, w->y5[i] + 15, w->textSlots[i + 3], w->palette2, 40, w->textSlotCounts[i + 3]);
#endif
#ifdef VERSION_EU
                        if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                            DrawSprite(w->x4[i], w->y4[i], gUnk_09EEA2BC[i], w->unk_000[i], w->unk_000[4], NULL, 0, 50);
#ifdef VERSION_EU
                        } else {
                            DrawSprite(w->x4[i], w->y4[i], gUnkEu_09F7626C[i], w->unk_000[i], w->unk_000[4], NULL, 0, 50);
                        }
#endif
                    }
                }
            }

            DrawSprite(w->x3, w->y3, w->gfx2, w->tiles, w->palette3, NULL, 0, 40);
            break;
        case 3:
#ifdef VERSION_EU
            DrawSprite(w->x5[w->cursor] + 2, w->y5[w->cursor] - 1, NULL, w->tiles5[w->cursor], w->palette, NULL, 0, 40);
#else
            DrawTextSlots(w->x5[w->cursor] + 22, w->y5[w->cursor] - 5, w->textSlots[w->cursor], w->palette, 40, w->textSlotCounts[w->cursor]);
            DrawTextSlots(w->x5[w->cursor] + 4, w->y5[w->cursor] + 13, w->textSlots[w->cursor + 3], w->palette, 40, w->textSlotCounts[w->cursor + 3]);
#endif
            DrawSprite(w->x4[w->cursor], w->y4[w->cursor], NULL, w->unk_000[w->cursor], w->unk_000[5], NULL, 0, 50);
            DrawSprite(w->x6, 0,
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage][10],
#else
                       gUnk_09EEA1BC[10],
#endif
                       w->unk_000[6], w->unk_000[7], NULL, 0, 50);
            DrawSprite(w->x, w->y >> 8, gUnk_09EEA1EC[0], w->tiles2, w->unk_000[7], NULL, SPRITE_PRIORITY(1), 51);
            DrawSprite(w->x2, w->y2 >> 8, gUnk_09EEA1EC[1], w->tiles2, w->unk_000[7], NULL, SPRITE_PRIORITY(1), 51);
            break;
        }

#ifdef VERSION_JP
        if (w->blinkOn != 0) {
            DrawSprite(192, 82, gUnk_09EEA19C[0], w->tiles3, w->palette4, NULL, 0, 10);
        }
#endif

        if (!(gGameState.flags & GAME_FLAG_RIKU)) {
            DrawLevelUpStatDigits(w->statsOffsetX + 214, 17, w->unk_000[6], w->unk_000[7],
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage],
#else
                       gUnk_09EEA1BC,
#endif
                       w->levelDigits, 0);
            DrawLevelUpStatDigits(w->statsOffsetX + 214, 111, w->unk_000[6], w->unk_000[7],
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage],
#else
                       gUnk_09EEA1BC,
#endif
                       w->maxHpDigits, 1);
            DrawLevelUpStatDigits(w->statsOffsetX + 206, 132, w->unk_000[6], w->unk_000[7],
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage],
#else
                       gUnk_09EEA1BC,
#endif
                       w->cpDigits, 2);
        } else {
            DrawLevelUpStatDigits(w->statsOffsetX + 214, 17, w->unk_000[6], w->unk_000[7],
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage],
#else
                       gUnk_09EEA1BC,
#endif
                       w->levelDigits, 0);
            DrawLevelUpStatDigits(w->statsOffsetX + 214, 106, w->unk_000[6], w->unk_000[7],
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage],
#else
                       gUnk_09EEA1BC,
#endif
                       w->maxHpDigits, 1);
            DrawLevelUpStatDigits(w->statsOffsetX + 214, 122, w->unk_000[6], w->unk_000[7],
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage],
#else
                       gUnk_09EEA1BC,
#endif
                       w->apDigits, 4);
            DrawLevelUpStatDigits(w->statsOffsetX + 214, 137, w->unk_000[6], w->unk_000[7],
#ifdef VERSION_EU
                       gUnk_09EEA1BC[gLanguage],
#else
                       gUnk_09EEA1BC,
#endif
                       w->dpDigits, 3);
        }
    }

    DrawSprite(w->x7 >> 8, w->y6 >> 8, w->gfx, w->tiles4, w->palette5, NULL, SPRITE_PRIORITY(1), 40);
    TaskPoolDraw(&w->pool);
}

void Level_Up_3(LevelUpWork* w) {
#ifdef VERSION_EU
    if (w->tiles5[0] != NULL) {
        ReleaseObjTiles(w->tiles5[0]);
    }

    if (w->tiles5[1] != NULL) {
        ReleaseObjTiles(w->tiles5[1]);
    }

    if (w->tiles5[2] != NULL) {
        ReleaseObjTiles(w->tiles5[2]);
    }
#else
    FreeTextSlots(w->textSlots[0], 36);
    FreeTextSlots(w->textSlots[1], 36);
    FreeTextSlots(w->textSlots[2], 36);
    FreeTextSlots(w->textSlots[3], 36);
    FreeTextSlots(w->textSlots[4], 36);
    FreeTextSlots(w->textSlots[5], 36);
#endif

    if (w->unk_000[6] != NULL) {
        ReleaseObjTiles(w->unk_000[6]);
    }

    if (w->unk_000[7] != NULL) {
        ReleaseObjPalette(w->unk_000[7]);
    }

    if (w->unk_000[0] != NULL) {
        ReleaseObjTiles(w->unk_000[0]);
    }

    if (w->unk_000[1] != NULL) {
        ReleaseObjTiles(w->unk_000[1]);
    }

    if (w->unk_000[2] != NULL) {
        ReleaseObjTiles(w->unk_000[2]);
    }

    if (w->unk_000[4] != NULL) {
        ReleaseObjPalette(w->unk_000[4]);
    }

    if (w->unk_000[5] != NULL) {
        ReleaseObjPalette(w->unk_000[5]);
    }

    if (w->palette != NULL) {
        ReleaseObjPalette(w->palette);
    }

    if (w->palette2 != NULL) {
        ReleaseObjPalette(w->palette2);
    }

    if (w->tiles != NULL) {
        ReleaseObjTiles(w->tiles);
    }

    if (w->palette3 != NULL) {
        ReleaseObjPalette(w->palette3);
    }

    if (w->tiles2 != NULL) {
        ReleaseObjTiles(w->tiles2);
    }

    if (w->tiles3 != NULL) {
        ReleaseObjTiles(w->tiles3);
    }

    if (w->palette4 != NULL) {
        ReleaseObjPalette(w->palette4);
    }

    if (w->tiles4 != NULL) {
        ReleaseObjTiles(w->tiles4);
    }

    if (w->palette5 != NULL) {
        ReleaseObjPalette(w->palette5);
    }

    TaskPoolDestroy(&w->pool);
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

u8 UpdateLevelUpNextSlideIn(LevelUpWork* w, void* a) {
#ifdef VERSION_EU
    enum { tileSize = 0xC80, mapSize = 0x500 };
#else
    enum { tileSize = 0xD80, mapSize = 0x800 };
#endif

    if (w->loaded[0] == 0) {
        w->timer++;

        if (w->timer > 7) {
#ifdef VERSION_EU
            w->tiles5[0] = AllocSpriteFrameTiles(0x500);
            w->tiles5[1] = AllocSpriteFrameTiles(0x500);
            w->tiles5[2] = AllocSpriteFrameTiles(0x500);
#endif

            if (!(gGameState.flags & GAME_FLAG_RIKU)) {
                w->unk_000[0] = AllocSpriteFrameTiles(tileSize);
                w->unk_000[1] = AllocSpriteFrameTiles(tileSize);
                w->unk_000[2] = AllocSpriteFrameTiles(tileSize);

#ifdef VERSION_EU
                if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                    UpdateSpriteFrameTiles(w->unk_000[0], gUnk_09EEA2BC[0], gUnk_090950F4);
                    UpdateSpriteFrameTiles(w->unk_000[1], gUnk_09EEA2BC[1], gUnk_090950F4);
                    UpdateSpriteFrameTiles(w->unk_000[2], gUnk_09EEA2BC[2], gUnk_090950F4);
#ifdef VERSION_EU
                } else {
                    UpdateSpriteFrameTiles(w->unk_000[0], gUnkEu_09F7626C[0], gUnkEu_09172200);
                    UpdateSpriteFrameTiles(w->unk_000[1], gUnkEu_09F7626C[1], gUnkEu_09172200);
                    UpdateSpriteFrameTiles(w->unk_000[2], gUnkEu_09F7626C[2], gUnkEu_09172200);
                }
#endif

                w->unk_000[4] = LoadObjPalette(gUnk_09613F18, 32);
                w->unk_000[5] = LoadObjPalette(gUnk_09613F38, 32);
            } else {
                w->unk_000[0] = AllocSpriteFrameTiles(tileSize);
                w->unk_000[1] = AllocSpriteFrameTiles(tileSize);
                w->unk_000[2] = AllocSpriteFrameTiles(tileSize);

#ifdef VERSION_EU
                if (gLanguage != LANGUAGE_ITALIAN) {
#endif
                    UpdateSpriteFrameTiles(w->unk_000[0], gUnk_09EEA29C[0], gUnk_09091D36);
                    UpdateSpriteFrameTiles(w->unk_000[1], gUnk_09EEA29C[1], gUnk_09091D36);
                    UpdateSpriteFrameTiles(w->unk_000[2], gUnk_09EEA29C[2], gUnk_09091D36);
#ifdef VERSION_EU
                } else {
                    UpdateSpriteFrameTiles(w->unk_000[0], gUnkEu_09F762A4[0], gUnkEu_091759BA);
                    UpdateSpriteFrameTiles(w->unk_000[1], gUnkEu_09F762A4[1], gUnkEu_091759BA);
                    UpdateSpriteFrameTiles(w->unk_000[2], gUnkEu_09F762A4[2], gUnkEu_091759BA);
                }
#endif

                w->unk_000[4] = LoadObjPalette(gUnk_09613EB8, 32);
                w->unk_000[5] = LoadObjPalette(gUnk_09613ED8, 32);
            }

#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                w->tiles3 = LoadObjTiles(gUnk_0908C686, 0x3E0);
                break;
            case LANGUAGE_FRENCH:
                w->tiles3 = LoadObjTiles(gUnkEu_0916F992, 0x3E0);
                break;
            case LANGUAGE_GERMAN:
                w->tiles3 = LoadObjTiles(gUnkEu_0917063A, 0x3E0);
                break;
            case LANGUAGE_ITALIAN:
                w->tiles3 = LoadObjTiles(gUnkEu_09170202, 0x3E0);
                break;
            case LANGUAGE_SPANISH:
                w->tiles3 = LoadObjTiles(gUnkEu_0916FDCA, 0x3E0);
                break;
            default:
                w->tiles3 = LoadObjTiles(gUnk_0908C686, 0x3E0);
                break;
            }
#else
            w->tiles3 = LoadObjTiles(gUnk_0908C686, 0x3E0);
#endif
            w->palette4 = LoadObjPalette(gCard00Palette, 32);
            FadeSetPaletteExcluded(((ObjPalette*)w->unk_000[4])->index + 16, 1);
            FadeSetPaletteExcluded(((ObjPalette*)w->unk_000[5])->index + 16, 1);
            FadeSetPaletteExcluded(w->palette4->index + 16, 1);
            w->tiles = AllocObjTiles(0x3C0, NULL);
            w->palette3 = LoadObjPalette(gUnk_09618CD8, 32);
            FadeSetPaletteExcluded(w->palette3->index + 16, 1);
            SetObjTileSource(w->tiles, gUnk_093F4578);
            AnimInit(&w->anim, gUnk_09EF1170, gUnk_09EF1150);
            AnimStart(&w->anim, 2, ANIM_FLAG_LOOP);
            w->gfx2 = AnimGetGfx(&w->anim);
            w->loaded[0] = 1;
            w->timer = 0;
            FadeToAmount(FADE_MODE_BLACK, 8, 16);
        }

        return 1;
    }

    w->gfx = AnimUpdate(&w->anim2);

    {
        s32 x0 = w->x4[0] << 8;
        s32 x1 = w->x4[1] << 8;
        s32 x2 = w->x4[2] << 8;
        ApproachValue(&x0, 0x1000, w->optionSteps[0]);

        if (w->optionSteps[0] > 0) {
            w->optionSteps[0]--;
        }

        if (w->optionSteps[0] <= 6) {
            ApproachValue(&x1, 0x1000, w->optionSteps[1]);

            if (w->optionSteps[1] > 0) {
                w->optionSteps[1]--;
            }
        }

        if (w->optionSteps[1] <= 6) {
            ApproachValue(&x2, 0x1000, w->optionSteps[2]);

            if (w->optionSteps[2] > 0) {
                w->optionSteps[2]--;
            }
        }

        w->x4[0] = x0 >> 8;
        w->x4[1] = x1 >> 8;
        w->x4[2] = x2 >> 8;
    }

    if (w->optionSteps[2] == 0) {
        u8 i;

        if (gBtlWork->battleId == 151) {
            LoadBgMap(0, gUnk_095112B8, mapSize);
        } else {
            LoadBgMap(1, gUnk_095112B8, mapSize);
        }

        w->state = 1;

        if (!(gGameState.flags & GAME_FLAG_RIKU)) {
            if (gGameState.progression.maxHp > 559) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(w->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                w->textSlotCounts[0] = LoadTextSlots(gLevelUpSoraTexts[6], w->textSlots[0]);
                w->textSlotCounts[3] = 0;
#endif
                w->optionEnabled[0] = 0;
            } else {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(w->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][0], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                w->textSlotCounts[0] = LoadTextSlots(gLevelUpSoraTexts[0], w->textSlots[0]);
                w->textSlotCounts[3] = LoadTextSlots(gLevelUpSoraTexts[3], w->textSlots[3]);
#endif
            }

            if (gGameState.progression.cp > 1899) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(w->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                w->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[6], w->textSlots[1]);
                w->textSlotCounts[4] = 0;
#endif
                w->optionEnabled[1] = 0;
            } else {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(w->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][1], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                w->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[1], w->textSlots[1]);
                w->textSlotCounts[4] = LoadTextSlots(gLevelUpSoraTexts[4], w->textSlots[4]);
#endif
            }

            if (gGameState.progression.levelMilestone > 10) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(w->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                w->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[6], w->textSlots[2]);
                w->textSlotCounts[5] = 0;
#endif
                w->optionEnabled[2] = 0;
            } else if (IsLevelUpStockUnlocked() == 0) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(w->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                w->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[6], w->textSlots[2]);
                w->textSlotCounts[5] = 0;
#endif
                w->optionEnabled[2] = 0;
            } else {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(w->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][2], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                w->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[2], w->textSlots[2]);
                w->textSlotCounts[5] = LoadTextSlots(gLevelUpSoraTexts[5], w->textSlots[5]);
#endif
            }

            w->palette = LoadObjPalette(gUnk_09613F98, 32);
            w->palette2 = LoadObjPalette(gUnk_09613FB8, 32);
        } else {
            if (gGameState.progression.maxHp > 559) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(w->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                w->textSlotCounts[0] = LoadTextSlots(gLevelUpRikuTexts[6], w->textSlots[0]);
                w->textSlotCounts[3] = 0;
#endif
                w->optionEnabled[0] = 0;
            } else {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(w->tiles5[0], gLevelUpOptionSpritesByLanguage[gLanguage][3], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                w->textSlotCounts[0] = LoadTextSlots(gLevelUpRikuTexts[0], w->textSlots[0]);
                w->textSlotCounts[3] = LoadTextSlots(gLevelUpRikuTexts[3], w->textSlots[3]);
#endif
            }

            if (gGameState.progression.ap > 29) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(w->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                w->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[6], w->textSlots[1]);
                w->textSlotCounts[4] = 0;
#endif
                w->optionEnabled[1] = 0;
            } else if ((u8)IsLevelUpApUnlocked() == 0) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(w->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                w->textSlotCounts[1] = LoadTextSlots(gLevelUpSoraTexts[6], w->textSlots[1]);
                w->textSlotCounts[4] = 0;
#endif
                w->optionEnabled[1] = 0;
            } else {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(w->tiles5[1], gLevelUpOptionSpritesByLanguage[gLanguage][4], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                w->textSlotCounts[1] = LoadTextSlots(gLevelUpRikuTexts[1], w->textSlots[1]);
                w->textSlotCounts[4] = LoadTextSlots(gLevelUpRikuTexts[4], w->textSlots[4]);
#endif
            }

            if (gGameState.progression.dp > 299) {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(w->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][6], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                w->textSlotCounts[2] = LoadTextSlots(gLevelUpSoraTexts[6], w->textSlots[2]);
                w->textSlotCounts[5] = 0;
#endif
                w->optionEnabled[2] = 0;
            } else {
#ifdef VERSION_EU
                UpdateSpriteFrameTiles(w->tiles5[2], gLevelUpOptionSpritesByLanguage[gLanguage][5], gLevelUpOptionTilesByLanguage[gLanguage]);
#else
                w->textSlotCounts[2] = LoadTextSlots(gLevelUpRikuTexts[2], w->textSlots[2]);
                w->textSlotCounts[5] = LoadTextSlots(gLevelUpRikuTexts[5], w->textSlots[5]);
#endif
            }

            w->palette = LoadObjPalette(gUnk_09613FD8, 32);
            w->palette2 = LoadObjPalette(gUnk_09613FF8, 32);
        }

        FadeSetPaletteExcluded(w->palette->index + 16, 1);
        FadeSetPaletteExcluded(w->palette2->index + 16, 1);

        for (i = 0; i < 3; i++) {
            if (w->optionEnabled[i] == 1) {
                break;
            }
        }

        w->cursor = i;
        w->y3 = sLevelUpCursorY[w->cursor];
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateLevelUpSelect);

        if (gBtlWork->battleId == 151) {
            LoadBgMap(0, gLevelUpOptionBgMaps[w->cursor], 0x800);
        } else {
            LoadBgMap(1, gLevelUpOptionBgMaps[w->cursor], 0x800);
        }
    }

    TaskPoolUpdate(&w->pool);
    return 1;
}

u8 UpdateLevelUpNextSlideOut(LevelUpWork* w, void* a) {
    s32 x;
    s32 y;
    s8 n;

    x = w->x4[w->cursor] << 8;
    y = w->x5[w->cursor] << 8;
    ApproachValue(&x, -0x8000, w->optionSteps[w->cursor]);
    ApproachValue(&y, -0xF800, w->optionSteps[w->cursor]);
    w->x4[w->cursor] = x >> 8;
    w->x5[w->cursor] = y >> 8;
    w->optionSteps[w->cursor]--;

    if (w->slideSteps > 0) {
        w->slideSteps--;
    }

    n = w->slideSteps;

    if (n == 0) {
        if (w->barSteps != 0) {
            ApproachValue(&w->y, 0, w->barSteps);
            ApproachValue(&w->y2, 0x9800, w->barSteps);
            w->barSteps--;
        } else {
            if (w->unk_000[0] != NULL) {
                ReleaseObjTiles(w->unk_000[0]);
            }

            if (w->unk_000[1] != NULL) {
                ReleaseObjTiles(w->unk_000[1]);
            }

            if (w->unk_000[2] != NULL) {
                ReleaseObjTiles(w->unk_000[2]);
            }

#ifdef VERSION_EU
            if (w->tiles5[0] != NULL) {
                ReleaseObjTiles(w->tiles5[0]);
            }

            if (w->tiles5[1] != NULL) {
                ReleaseObjTiles(w->tiles5[1]);
            }

            if (w->tiles5[2] != NULL) {
                ReleaseObjTiles(w->tiles5[2]);
            }
#endif

            if (w->unk_000[4] != NULL) {
                ReleaseObjPalette(w->unk_000[4]);
            }

            if (w->unk_000[5] != NULL) {
                ReleaseObjPalette(w->unk_000[5]);
            }

            if (w->palette != NULL) {
                ReleaseObjPalette(w->palette);
            }

            if (w->palette2 != NULL) {
                ReleaseObjPalette(w->palette2);
            }

            if (w->tiles != NULL) {
                ReleaseObjTiles(w->tiles);
            }

            if (w->palette3 != NULL) {
                ReleaseObjPalette(w->palette3);
            }

            if (w->tiles3 != NULL) {
                ReleaseObjTiles(w->tiles3);
            }

            if (w->palette4 != NULL) {
                ReleaseObjPalette(w->palette4);
            }

            w->x4[0] = 0xFF80;
            w->x4[1] = 0xFF80;
            w->x4[2] = 0xFF80;
            w->y4[0] = 16;
            w->y4[1] = 64;
            w->y4[2] = 112;
            w->slideSteps = 24;
            w->headerSteps = 16;
            w->optionSteps[0] = 16;
            w->optionSteps[1] = 16;
            w->optionSteps[2] = 16;
            w->x5[0] = 8;
            w->x5[1] = 8;
            w->x5[2] = 8;
            w->y5[0] = 31;
            w->y5[1] = 79;
            w->y5[2] = 127;
            w->x3 = 132;
            w->y3 = sLevelUpCursorY[0];

            if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
                SetObjTileSource(w->tiles4, gSor1ll51Tiles);
                AnimInit(&w->anim2, gSor1ll51Anims, gSor1ll51Frames);
                AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
            } else {
                SetObjTileSource(w->tiles4, gRikuBt00Tiles);
                AnimInit(&w->anim2, gRikuBt00Anims, gRikuBt00Frames);
                AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
            }

            w->loaded[0] = 0;
            w->state = 0;
            w->effectShown = 0;
            w->timer = 0;
            w->applied = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateLevelUpNextSlideIn);
        }
    }

    w->optionEnabled[0] = 1;
    w->optionEnabled[1] = 1;
    w->optionEnabled[2] = 1;
    w->gfx = AnimUpdate(&w->anim2);
    TaskPoolUpdate(&w->pool);
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
