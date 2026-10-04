#include "bg_animation_data.h"
#include "display.h"
#include "mode_chkeff.h"
#include "gba/keys.h"
#include "sprites_mode_debug.h"
#include "system_state.h"
#include "malloc.h"
#include "fade.h"
#include "bg_animation_types.h"
#include "card_api.h"
#include "key.h"
#include "mode.h"
#include "registration_data.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"

extern BgAnimationDef* gChkEffBgAnimations[83];

static ChkEffWork* sChkEffWork;

static const char sChkEffPauseText[8] = "PAUSE";
static const char sChkEffPauseBlankText[8] = "     ";
static const char sChkEffBlankLineText[40] = "                                      ";
static const char sChkEffAlphaALabel[8] = "alp A";
static const char sChkEffAlphaBLabel[8] = "alp B";
static const char sChkEffScaleLabel[8] = "scale";
static const char sChkEffNumLabel[4] = "num";
static const char sChkEffPicLabel[4] = "pic";
static const char sChkEffFrameLabel[8] = "frame";

void mode_chkeff_0() {
    sChkEffWork = EwramAlloc(sizeof(ChkEffWork));
    SetBgMode1();
    SetupBg(0, 0, 7, 0);
    SetupBg(1, 1, 12, 8);
    SetupBg(2, 2, 28, 10);
    SetBgBlend(2, 16, 16);
    SetBgPriority(2, 0);
    SetBgPriority(0, 1);
    SetBgPriority(1, 2);
#ifdef VERSION_EU
    LoadBgTilesLz77(1, gUnk_08C6B0C4);
    LoadBgMapLz77(1, gUnk_08EEE384);
    LoadBgPalette(1, gUnk_08F683C4, 0x20);
#else
    LoadBgTiles(1, gUnk_08C6B0C4, 0x7C20);
    LoadBgPalette(1, gUnk_08F683C4, 0x20);
    LoadBgMap(1, gUnk_08EEE384, 0x800);
#endif
    FadeSetPaletteExcluded(8, 1);
    FadeSetPaletteExcluded(9, 1);
    FadeSetPaletteExcluded(10, 1);
    FadeSetPaletteExcluded(11, 1);
    FadeSetPaletteExcluded(12, 1);
    FadeSetPaletteExcluded(13, 1);
    FadeSetPaletteExcluded(14, 1);
    FadeSetPaletteExcluded(15, 1);
    BgAnimInit(2, 0x8000, 0x80);
    TaskPoolInit(&sChkEffWork->pool, 1);
    TaskCreate(&sChkEffWork->pool, &gTaskDescPrint, NULL);
    sChkEffWork->effectIndex = 0;
    sChkEffWork->paused = 0;
    sChkEffWork->scrollX = 0;
    sChkEffWork->scrollY = 0;
    sChkEffWork->scale = 0x100;
    sChkEffWork->rotation = 0;
    sChkEffWork->alphaA = 16;
    sChkEffWork->alphaB = 16;
    BgAnimStart(gChkEffBgAnimations[0], 0x78, 0x50);
}

void mode_chkeff_1() {
    ChkEffWork** wp;
    void* obj;
    s16 prev;
    u16 a;
    u16 b;

    if (GetKeysPressed() & B_BUTTON) {
        ModeRequest(&gModeDebug, 0);
    } else {
        if (GetKeysPressed() & START_BUTTON) {
            sChkEffWork->paused = !sChkEffWork->paused;
        }

        prev = sChkEffWork->effectIndex;

        if (GetKeysRepeat() & DPAD_LEFT) {
            sChkEffWork->effectIndex--;
        }

        if (GetKeysRepeat() & DPAD_RIGHT) {
            sChkEffWork->effectIndex++;
        }

        if (sChkEffWork->effectIndex < 0) {
            sChkEffWork->effectIndex = 82;
        }

        if ((u16)sChkEffWork->effectIndex > 82) {
            sChkEffWork->effectIndex = 0;
        }

        obj = gChkEffBgAnimations[sChkEffWork->effectIndex];

        if (prev != sChkEffWork->effectIndex) {
            sChkEffWork->paused = 0;
            BgAnimStart(obj, 120, 80);
        }

        if (GetKeysRepeat() & DPAD_UP) {
            sChkEffWork->scale += 8;
        } else if (GetKeysRepeat() & DPAD_DOWN) {
            sChkEffWork->scale -= 8;
        }

        if (GetKeysPressed() & SELECT_BUTTON) {
            sChkEffWork->scale = 0x100;
            sChkEffWork->rotation = 0;
        }

        if (GetKeysRepeat() & L_BUTTON) {
            sChkEffWork->alphaA++;
            sChkEffWork->alphaA %= 17;
        }

        if (GetKeysRepeat() & R_BUTTON) {
            sChkEffWork->alphaB++;
            sChkEffWork->alphaB %= 17;
        }

        if (sChkEffWork->scale <= 9) {
            sChkEffWork->scale = 10;
        }

        if (sChkEffWork->scale > 0xA00) {
            sChkEffWork->scale = 0xA00;
        }

        if (BgAnimIsStopped() && (GetKeysHeld() & A_BUTTON)) {
            BgAnimStart(obj, 120, 80);
        }

        if (sChkEffWork->paused) {
            PrintString(0, 0, 0, sChkEffPauseText);
        } else {
            PrintString(0, 0, 0, sChkEffPauseBlankText);
        }

        wp = &sChkEffWork;
        PrintString(0, 14, 0, sChkEffBlankLineText);
        PrintString(0, 15, 0, sChkEffBlankLineText);
        PrintString(0, 16, 0, sChkEffBlankLineText);
        PrintString(0, 17, 0, sChkEffBlankLineText);
        PrintString(0, 18, 0, sChkEffBlankLineText);
        PrintString(0, 19, 0, sChkEffBlankLineText);
        BgAnimGetFrameState(&a, &b);
        PrintString(0, 14, 0, sChkEffAlphaALabel);
        PrintNumber(6, 14, 0, (*wp)->alphaA);
        PrintString(0, 15, 0, sChkEffAlphaBLabel);
        PrintNumber(6, 15, 0, (*wp)->alphaB);
        PrintString(0, 16, 0, sChkEffScaleLabel);
        PrintNumber(6, 16, 0, (*wp)->scale);
        PrintString(0, 17, 0, sChkEffNumLabel);
        PrintNumber(6, 17, 0, (*wp)->effectIndex);
        PrintString(0, 18, 0, sChkEffPicLabel);
        PrintNumber(6, 18, 0, a);
        PrintString(0, 19, 0, sChkEffFrameLabel);
        PrintNumber(6, 19, 0, b);
        TaskPoolUpdate(&(*wp)->pool);
        TaskPoolDraw(&(*wp)->pool);
        BgAnimSetTransform((*wp)->rotation, (*wp)->scale, (*wp)->scale);
        SetBlendAlpha((*wp)->alphaA, (*wp)->alphaB);

        if (!(*wp)->paused || (GetKeysRepeat() & A_BUTTON)) {
            BgAnimUpdate();
        }

        SetBgScroll(1, sChkEffWork->scrollX, sChkEffWork->scrollY);

        if ((gFrameCounter & 3) == 0) {
            sChkEffWork->scrollY--;
        }
    }
}

void mode_chkeff_2() {
    TaskPoolDestroy(&sChkEffWork->pool);
    EwramFree(sChkEffWork);
}

BgAnimationDef* gChkEffBgAnimations[83] = {
    &gBgAnimDefCure00,
    &gBgAnimDefCure01,
    &gBgAnimDefCure02,
    &gBgAnimDefPotion,
    &gBgAnimDefBlizzard00,
    &gBgAnimDefBlizzard01,
    &gBgAnimDefBlizzard02,
    &gBgAnimDefBlizzard03,
    &gBgAnimDefFire00,
    &gBgAnimDefFire01,
    &gBgAnimDefFire02,
    &gBgAnimDefFire03,
    &gBgAnimDefThunder00,
    &gBgAnimDefThunder01,
    &gBgAnimDefThunder02,
    &gBgAnimDefThunder03,
    &gBgAnimDefFlash,
    &gBgAnimDefLimit,
    &gUnk_09EDA660,
    &gUnk_09EDAC30,
    &gUnk_09EDAC48,
    &gBgAnimDefSoraHit,
    &gBgAnimDefRikuHit,
    &gBgAnimDefEnemyHit,
    &gUnk_09EDA690,
    &gUnk_09EDA6A8,
    &gBgAnimDefFriendHit,
    &gBgAnimDefCharaDefeatEnd,
    &gBgAnimDefEnemyDeath,
    &gBgAnimDefDarkDeath,
    &gBgAnimDefCharaDefeat,
    &gBgAnimDefHumDefeat,
    &gBgAnimDefExplosion,
    &gBgAnimDefStop00,
    &gBgAnimDefStop01,
    &gBgAnimDefStop02,
    &gBgAnimDefSummon,
    &gBgAnimDefGroundImpact,
    &gBgAnimDefBtlStart,
    &gBgAnimDefGuard,
    &gBgAnimDefGravity00,
    &gBgAnimDefGravity01,
    &gBgAnimDefPremireChance,
    &gBgAnimDefGas,
    &gBgAnimDefEnemySpawn,
    &gBgAnimDefBoogieKaihuku,
    &gBgAnimDefPcShot,
    &gBgAnimDefDumboSplash,
    &gBgAnimDefTrinityLimit,
    &gBgAnimDefTrinityLimitCharge,
    &gBgAnimDefTrinityLimitBlast,
    &gBgAnimDefRagnarokCharge,
    &gBgAnimDefRagnarokShot,
    &gBgAnimDefBossDeath,
    &gUnk_09EDAA20,
    &gBgAnimDefUrsulaBeam,
    &gUnk_09EDAB40,
    &gBgAnimDefAnsemWave,
    &gBgAnimDefJfMajinBeam,
    &gBgAnimDefFlame,
    &gBgAnimDefFrost,
    &gBgAnimDefStunImpact,
    &gBgAnimDefUrsulaThunder,
    &gBgAnimDefWorldSelect,
    &gBgAnimDefWorldStart,
    &gBgAnimDefXmas,
    &gBgAnimDefVixenIceFall,
    &gUnk_09EDAC00,
    &gBgAnimDefTornado,
    &gBgAnimDefAxcelFireWall,
    &gBgAnimDefKama,
    &gBgAnimDefHanabira,
    &gBgAnimDefMahluxiaGround,
    &gBgAnimDefDragonFire,
    &gBgAnimDefLaxeneBeam,
    &gBgAnimDefAero,
    &gBgAnimDefRikuDarkModeFlash,
    &gBgAnimDefRikuFire03,
    &gBgAnimDefRikuFire00,
    &gBgAnimDefLstCtr,
    &gUnk_09EDAD80,
    &gBgAnimDefRikuLimitFinish,
    &gUnk_09EDADB0,
};

Mode gModeChkeff = { "mode_chkeff", (ModeInitFunc)mode_chkeff_0, mode_chkeff_1, mode_chkeff_2 };
