/**
 * sroll_b_secn.c
 * Staff Roll Section Headers
 */

#include "sroll.h"
#include "sprites_staff_roll.h"
#include "fade.h"
#include <stdlib.h>
#include "anim.h"
#include "engine_math.h"
#include "obj_api.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"
#include "sprite_palettes.h"

static s32 Square(s32 x) {
    return x * x;
}

void task_sroll_b_secn_0(SrollBSecnWork* work, SrollBSecnArg* arg) {
    u32 i;

    work->timer = 0;
    work->x = arg->x;
    work->y = arg->y;
    work->scrollY = arg->scrollY;
    work->scrollSpeed = arg->scrollSpeed;

    if (arg->index < 0) {
#ifdef VERSION_JP
        work->tiles = LoadObjTiles(gSrollSecnThemeSongTiles, 590 * 32);
#else
        work->tiles = LoadObjTiles(gSrollSecnThemeSongTiles, 606 * 32);
#endif
        work->palette = LoadObjPalette(gSrollSecnThemeSongPalette, 32);
        AnimInit(&work->anim, gSrollSecnThemeSongAnims, gSrollSecnThemeSongFrames);
        AnimStart(&work->anim, 0, 0);
        AnimInit(&work->anim2, gSrollSecnThemeSongAnims, gSrollSecnThemeSongFrames);
        AnimStart(&work->anim2, 0, 0);
    } else {
        work->tiles = LoadObjTiles(gSrollSecnSprites[arg->index].tiles, gSrollSecnSprites[arg->index].tileSize);
        work->palette = LoadObjPalette(gSrollSecnPalettes, 256);
        AnimInit(&work->anim, gSrollSecnSprites[arg->index].anims, gSrollSecnSprites[arg->index].gfxTable);
        AnimStart(&work->anim, 0, 0);
        AnimInit(&work->anim2, gSrollSecnSprites[arg->index].anims, gSrollSecnSprites[arg->index].gfxTable);
        AnimStart(&work->anim2, 1, 0);
    }

    for (i = 0; i < 8; i++) {
        FadeSetPaletteExcluded((work->palette->index + i) % 16 + 16, 1);
    }
}

u8 task_sroll_b_secn_1(SrollBSecnWork* work) {
    u8 alive;
    s16 y;

    alive = 1;
    y = (work->y >> 8) - (*work->scrollY >> 8);

    if (y <= -32) {
        alive = 0;
    }

    if (y <= 159) {
        ApproachValueHalfSteps(&work->x, 0x7800, 20);

        if (abs(work->x - 0x7800) <= 255) {
            work->x = 0x7800;
        }

        if (work->x == 0x7800) {
            AnimUpdate(&work->anim);
            AnimUpdate(&work->anim2);
        }
    }

    work->timer++;
    return alive;
}

void task_sroll_b_secn_2(SrollBSecnWork* work) {
    u16 y;

    y = (work->y >> 8) - (*work->scrollY >> 8);
    DrawSprite(120, y, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL, 0, 0xEF0);
    DrawSprite(120, y, AnimGetGfx(&work->anim2), work->tiles, work->palette, NULL, 0, 0xEE0);
}

void task_sroll_b_secn_3(SrollBSecnWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

const SrollSecnSprite gSrollSecnSprites[] = {
    { gSrollSecnScenarioTiles, 27 * 32, gSrollSecnScenarioAnims, gSrollSecnScenarioFrames },
    { gSrollSecn2DArtTiles, 24 * 32, gSrollSecn2DArtAnims, gSrollSecn2DArtFrames },
    { gSrollSecn3DAnimationTiles, 37 * 32, gSrollSecn3DAnimationAnims, gSrollSecn3DAnimationFrames },
    { gSrollSecnPlanningTiles, 27 * 32, gSrollSecnPlanningAnims, gSrollSecnPlanningFrames },
    { gSrollSecnEventCreationTiles, 39 * 32, gSrollSecnEventCreationAnims, gSrollSecnEventCreationFrames },
    { gSrollSecnProgrammingTiles, 35 * 32, gSrollSecnProgrammingAnims, gSrollSecnProgrammingFrames },
    { gSrollSecnGraphicDesignTiles, 41 * 32, gSrollSecnGraphicDesignAnims, gSrollSecnGraphicDesignFrames },
    { gSrollSecnSoundTiles, 21 * 32, gSrollSecnSoundAnims, gSrollSecnSoundFrames },
    { gSrollSecnEndingThemeTiles, 39 * 32, gSrollSecnEndingThemeAnims, gSrollSecnEndingThemeFrames },
    { gSrollSecnBuenaVistaGamesJapanTiles, 61 * 32, gSrollSecnBuenaVistaGamesJapanAnims, gSrollSecnBuenaVistaGamesJapanFrames },
    { gSrollSecnBuenaVistaGamesTiles, 47 * 32, gSrollSecnBuenaVistaGamesAnims, gSrollSecnBuenaVistaGamesFrames },
#ifdef VERSION_EU
    { gSrollSecnBuenaVistaGamesEmeaTiles, 61 * 32, gSrollSecnBuenaVistaGamesEmeaAnims, gSrollSecnBuenaVistaGamesEmeaFrames },
#endif
    { gSrollSecnVoiceTalentsTiles, 61 * 32, gSrollSecnVoiceTalentsAnims, gSrollSecnVoiceTalentsFrames },
#ifdef VERSION_JP
    { gSrollSecnVoiceRecordingTiles, 41 * 32, gSrollSecnVoiceRecordingAnims, gSrollSecnVoiceRecordingFrames },
#endif
    { gSrollSecnOutsideContractorsTiles, 50 * 32, gSrollSecnOutsideContractorsAnims, gSrollSecnOutsideContractorsFrames },
    { gSrollSecnManagementTiles, 35 * 32, gSrollSecnManagementAnims, gSrollSecnManagementFrames },
    { gSrollSecnQualityAssuranceTiles, 47 * 32, gSrollSecnQualityAssuranceAnims, gSrollSecnQualityAssuranceFrames },
#ifdef VERSION_JP
    { gSrollSecnRatingProofreadingTiles, 57 * 32, gSrollSecnRatingProofreadingAnims, gSrollSecnRatingProofreadingFrames },
    { gSrollSecnInformationTechnologyTiles, 83 * 32, gSrollSecnInformationTechnologyAnims, gSrollSecnInformationTechnologyFrames },
    { gSrollSecnPublicityTeamTiles, 41 * 32, gSrollSecnPublicityTeamAnims, gSrollSecnPublicityTeamFrames },
    { gSrollSecnSalesMarketingTiles, 71 * 32, gSrollSecnSalesMarketingAnims, gSrollSecnSalesMarketingFrames },
    { gSrollSecnSalesAdministrationTiles, 77 * 32, gSrollSecnSalesAdministrationAnims, gSrollSecnSalesAdministrationFrames },
#endif
    { gSrollSecnLegalAffairsTiles, 79 * 32, gSrollSecnLegalAffairsAnims, gSrollSecnLegalAffairsFrames },
#ifndef VERSION_JP
    { gSrollSecnLocalizationTeamTiles, 48 * 32, gSrollSecnLocalizationTeamAnims, gSrollSecnLocalizationTeamFrames },
    { gSrollSecnSquareEnixIncTiles, 44 * 32, gSrollSecnSquareEnixIncAnims, gSrollSecnSquareEnixIncFrames },
#endif
    { gSrollSecnSpecialThanksTiles, 41 * 32, gSrollSecnSpecialThanksAnims, gSrollSecnSpecialThanksFrames },
    { gSrollSecnJupiterCorporationTiles, 50 * 32, gSrollSecnJupiterCorporationAnims, gSrollSecnJupiterCorporationFrames },
};

TaskDesc gTaskDescSrollBSecn = {
    "task_sroll_b_secn",
    (TaskInitFunc)task_sroll_b_secn_0,
    (TaskUpdateFunc)task_sroll_b_secn_1,
    (TaskDrawFunc)task_sroll_b_secn_2,
    (TaskDestroyFunc)task_sroll_b_secn_3,
    sizeof(SrollBSecnWork),
};
