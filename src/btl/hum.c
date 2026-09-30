#include "task_descriptors.h"
#include "system_state.h"
#include "map_api.h"
#include "ms_api.h"
#include "fade.h"
#include "obj_api.h"
#include "pallet.h"
#include "hum.h"
#include "task_animation_assets.h"
#include "sprites_btl.h"
#include "sprites_cloud.h"
#include "sprites_evt.h"
#include "sprites_hum.h"
#include "gba/io_reg.h"
#include "btl_api.h"
#include "pc_api.h"
#include "hum_common.h"
#include "songs.h"
#include <stdlib.h>
#include "actor_localized_data.h"
#include <string.h>
#include "hum_tasks.h"

const u32 gHumCloudStockMoves[2][3] = {
    { 37, 37, 37 },
    { 37, 36, 37 },
};

const AnimDef gHumCloudAnimDefs[20] = {
    { gCroudBt00Frames, gCroudBt00Anims, gCroudBt00Tiles, 0, { 0, 0, 0 } },
    { gCroudBt01Frames, gCroudBt01Anims, gCroudBt01Tiles, 0, { 0, 0, 0 } },
    { gCroudBt02Frames, gCroudBt02Anims, gCroudBt02Tiles, 0, { 0, 0, 0 } },
    { gCroudBt03Frames, gCroudBt03Anims, gCroudBt03Tiles, 0, { 0, 0, 0 } },
    { gCroudBt03Frames, gCroudBt03Anims, gCroudBt03Tiles, 1, { 0, 0, 0 } },
    { gCroudBt03Frames, gCroudBt03Anims, gCroudBt03Tiles, 2, { 0, 0, 0 } },
    { gCroudBt03Frames, gCroudBt03Anims, gCroudBt03Tiles, 3, { 0, 0, 0 } },
    { gCroudBt03Frames, gCroudBt03Anims, gCroudBt03Tiles, 4, { 0, 0, 0 } },
    { gCroud01Frames, gCroud01Anims, gCroud01Tiles, 2, { 0, 0, 0 } },
    { gCroud01Frames, gCroud01Anims, gCroud01Tiles, 2, { 0, 0, 0 } },
    { gCroud00Frames, gCroud00Anims, gCroud00Tiles, 0, { 0, 0, 0 } },
    { gCroud00Frames, gCroud00Anims, gCroud00Tiles, 1, { 0, 0, 0 } },
    { gCroud00Frames, gCroud00Anims, gCroud00Tiles, 2, { 0, 0, 0 } },
    { gCroud00Frames, gCroud00Anims, gCroud00Tiles, 3, { 0, 0, 0 } },
    { gCroud10Frames, gCroud10Anims, gCroud10Tiles, 0, { 0, 0, 0 } },
    { gCroud11Frames, gCroud11Anims, gCroud11Tiles, 0, { 0, 0, 0 } },
    { gCroud12Frames, gCroud12Anims, gCroud12Tiles, 0, { 0, 0, 0 } },
    { gCroud13Frames, gCroud13Anims, gCroud13Tiles, 0, { 0, 0, 0 } },
    { gCroud01Frames, gCroud01Anims, gCroud01Tiles, 0, { 0, 0, 0 } },
    { gCroud02Frames, gCroud02Anims, gCroud02Tiles, 0, { 0, 0, 0 } },
};

const HumDef gHumCloudDef = { 128, 0, gCroudPalette, 0, { 43, 99, 38, 14, 24, 99, 0 } };

TaskDesc gTaskDescHumCloud = {
    "task_hum_cloud",
    (TaskInitFunc)task_hum_cloud_0,
    (TaskUpdateFunc)task_hum_cloud_1,
    (TaskDrawFunc)task_hum_cloud_2,
    (TaskDestroyFunc)task_hum_cloud_3,
    sizeof(CloudWork),
};

const u32 gHumHookStockMovesA[3] = {
    36, 36, 38,
};

const u32 gHumHookStockMovesB[3] = {
    37, 37, 38,
};

const AnimDef gHumHookAnimDefs[15] = {
    { gHookBt00Frames, gHookBt00Anims, gHookBt00Tiles, 0, { 0, 0, 0 } },
    { gHookBt01Frames, gHookBt01Anims, gHookBt01Tiles, 0, { 0, 0, 0 } },
    { gHookBt02Frames, gHookBt02Anims, gHookBt02Tiles, 0, { 0, 0, 0 } },
    { gHookBt03Frames, gHookBt03Anims, gHookBt03Tiles, 0, { 0, 0, 0 } },
    { gHookBt03Frames, gHookBt03Anims, gHookBt03Tiles, 1, { 0, 0, 0 } },
    { gHookBt03Frames, gHookBt03Anims, gHookBt03Tiles, 2, { 0, 0, 0 } },
    { gHookBt03Frames, gHookBt03Anims, gHookBt03Tiles, 3, { 0, 0, 0 } },
    { gHookBt03Frames, gHookBt03Anims, gHookBt03Tiles, 4, { 0, 0, 0 } },
    { gHookBt10Frames, gHookBt10Anims, gHookBt10Tiles, 0, { 0, 0, 0 } },
    { gHookBt11Frames, gHookBt11Anims, gHookBt11Tiles, 1, { 0, 0, 0 } },
    { gHookBt11Frames, gHookBt11Anims, gHookBt11Tiles, 0, { 0, 0, 0 } },
    { gHookBt11Frames, gHookBt11Anims, gHookBt11Tiles, 2, { 0, 0, 0 } },
    { gHookBt12Frames, gHookBt12Anims, gHookBt12Tiles, 0, { 0, 0, 0 } },
    { gHookF03Frames, gHookF03Anims, gHookF03Tiles, 2, { 0, 0, 0 } },
    { gHookF03Frames, gHookF03Anims, gHookF03Tiles, 3, { 0, 0, 0 } },
};

const HumDef gHumHookDef = { 128, 0, gHookPalette, 0, { 42, 99, 38, 14, 24, 99, 0 } };

const u8 gHumHookRollAmplitudes[8] = {
    0, 4, 4, 6, 8, 10, 8, 6,
};

TaskDesc gTaskDescHumHook = {
    "task_hum_hook",
    (TaskInitFunc)task_hum_hook_0,
    (TaskUpdateFunc)task_hum_hook_1,
    (TaskDrawFunc)task_hum_hook_2,
    (TaskDestroyFunc)task_hum_hook_3,
    sizeof(HookWork),
};

TaskDesc gTaskDescHumHookMoon = {
    "task_hum_hook_moon",
    (TaskInitFunc)task_hum_hook_moon_0,
    (TaskUpdateFunc)task_hum_hook_moon_1,
    (TaskDrawFunc)task_hum_hook_moon_2,
    (TaskDestroyFunc)task_hum_hook_moon_3,
    sizeof(HookMoonWork),
};

TaskDesc gTaskDescHumHookBomb = {
    "task_hum_hook_bomb",
    (TaskInitFunc)task_hum_hook_bomb_0,
    (TaskUpdateFunc)task_hum_hook_bomb_1,
    (TaskDrawFunc)task_hum_hook_bomb_2,
    (TaskDestroyFunc)task_hum_hook_bomb_3,
    sizeof(HookBombWork),
};

const u32 gHumAnsemStockMovesA[3] = {
    36, 37, 37,
};

const u32 gHumAnsemStockMovesB[3] = {
    36, 37, 36,
};

const AnimDef gHumAnsemAnimDefs[7] = {
    { gAnsemBt00Frames, gAnsemBt00Anims, gAnsemBt00Tiles, 0, { 0, 0, 0 } },
    { gAnsemBt01Frames, gAnsemBt01Anims, gAnsemBt01Tiles, 0, { 0, 0, 0 } },
    { gAnsemBt03Frames, gAnsemBt03Anims, gAnsemBt03Tiles, 0, { 0, 0, 0 } },
    { gAnsemBt04Frames, gAnsemBt04Anims, gAnsemBt04Tiles, 0, { 0, 0, 0 } },
    { gAnsemBt05Frames, gAnsemBt05Anims, gAnsemBt05Tiles, 0, { 0, 0, 0 } },
    { gAnsemBt05Frames, gAnsemBt05Anims, gAnsemBt05Tiles, 1, { 0, 0, 0 } },
    { gAnsemBt05Frames, gAnsemBt05Anims, gAnsemBt05Tiles, 2, { 0, 0, 0 } },
};

const AnimDef gHumAnsemBackAnimDefs[10] = {
    { gAnsembackBt00Frames, gAnsembackBt00Anims, gAnsembackBt00Tiles, 0, { 0, 0, 0 } },
    { gAnsembackBt01Frames, gAnsembackBt01Anims, gAnsembackBt01Tiles, 0, { 0, 0, 0 } },
    { gAnsembackBt02Frames, gAnsembackBt02Anims, gAnsembackBt02Tiles, 0, { 0, 0, 0 } },
    { gAnsembackBt03Frames, gAnsembackBt03Anims, gAnsembackBt03Tiles, 0, { 0, 0, 0 } },
    { gAnsembackBt03bFrames, gAnsembackBt03bAnims, gAnsembackBt03bTiles, 1, { 0, 0, 0 } },
    { gAnsembackBt03bFrames, gAnsembackBt03bAnims, gAnsembackBt03bTiles, 0, { 0, 0, 0 } },
    { gAnsembackBt04Frames, gAnsembackBt04Anims, gAnsembackBt04Tiles, 0, { 0, 0, 0 } },
    { gAnsembackBt05Frames, gAnsembackBt05Anims, gAnsembackBt05Tiles, 0, { 0, 0, 0 } },
    { gAnsembackBt05Frames, gAnsembackBt05Anims, gAnsembackBt05Tiles, 1, { 0, 0, 0 } },
    { gAnsembackBt05Frames, gAnsembackBt05Anims, gAnsembackBt05Tiles, 2, { 0, 0, 0 } },
};

const HumSubDef gHumAnsemSubDef = { gAnsembackPalette, 128, 0 };

const HumDef gHumAnsemDef = { 80, 0, gAnsemPalette, 0, { 52, 99, 65, 14, 42, 99, 0 } };

TaskDesc gTaskDescHumAnsem = {
    "task_hum_ansem",
    (TaskInitFunc)task_hum_ansem_0,
    (TaskUpdateFunc)task_hum_ansem_1,
    (TaskDrawFunc)task_hum_ansem_2,
    (TaskDestroyFunc)task_hum_ansem_3,
    sizeof(AnsemWork),
};

const u32 gHumHadesStockMoves[3] = {
    36, 36, 36,
};

const u32 gHumHadesAngryStockMoves[3] = {
    37, 36, 37,
};

const AnimDef gHumHadesAnimDefs[10] = {
    { gHadesFloatFollowFrames, gHadesFloatFollowAnims, gHadesFloatFollowTiles, 0, { 0, 0, 0 } },
    { gHadesFloatBackFrames, gHadesFloatBackAnims, gHadesFloatBackTiles, 0, { 0, 0, 0 } },
    { gHadesDamageFrames, gHadesDamageAnims, gHadesDamageTiles, 0, { 0, 0, 0 } },
    { gHadesFirashotFrames, gHadesFirashotAnims, gHadesFirashotTiles, 0, { 0, 0, 0 } },
    { gHadesFigaballFrames, gHadesFigaballAnims, gHadesFigaballTiles, 0, { 0, 0, 0 } },
    { gHadesNailofframeFrames, gHadesNailofframeAnims, gHadesNailofframeTiles, 0, { 0, 0, 0 } },
    { gHadesAngryFrames, gHadesAngryAnims, gHadesAngryTiles, 0, { 0, 0, 0 } },
    { gHadesFramespreadFrames, gHadesFramespreadAnims, gHadesFramespreadTiles, 1, { 0, 0, 0 } },
    { gHadesFramespreadFrames, gHadesFramespreadAnims, gHadesFramespreadTiles, 2, { 0, 0, 0 } },
    { gHadesFramespreadFrames, gHadesFramespreadAnims, gHadesFramespreadTiles, 3, { 0, 0, 0 } },
};

const AnimDef gHumHadesEffectAnimDefs[5] = {
    { gHadesAngryHiFrames, gHadesAngryHiAnims, gHadesAngryHiTiles, 0, { 0, 0, 0 } },
    { gHadesNailFrameFrames, gHadesNailFrameAnims, gHadesNailFrameTiles, 0, { 0, 0, 0 } },
    { gHadesFigaballBallFrames, gHadesFigaballBallAnims, gHadesFigaballBallTiles, 0, { 0, 0, 0 } },
    { gHadesFigaballBallFrames, gHadesFigaballBallAnims, gHadesFigaballBallTiles, 1, { 0, 0, 0 } },
    { gHadesFirashotFiraFrames, gHadesFirashotFiraAnims, gHadesFirashotFiraTiles, 0, { 0, 0, 0 } },
};

const HumSubDef gHumHadesSubDef = { gBStatesPalette, 75, 0 };

const HumDef gHumHadesDef = {
#ifdef VERSION_EU
        100
#else
        128
#endif
    , 0, gHadesPalette, 0, { 44, 99, 90, 14, 52, 99, 4 } };

TaskDesc gTaskDescHumHades = {
    "task_hum_hades",
    (TaskInitFunc)task_hum_hades_0,
    (TaskUpdateFunc)task_hum_hades_1,
    (TaskDrawFunc)task_hum_hades_2,
    (TaskDestroyFunc)task_hum_hades_3,
    sizeof(HadesWork),
};

const u32 gHumMahluxiaStockMovesA[3] = {
    37, 36, 37,
};

const u32 gHumMahluxiaStockMovesB[3] = {
    36, 37, 38,
};

const AnimDef gHumMahluxiaAnimDefs[13] = {
    { gMaruxhaIdleFrames, gMaruxhaIdleAnims, gMaruxhaIdleTiles, 0, { 0, 0, 0 } },
    { gMaruxhaMoveFrames, gMaruxhaMoveAnims, gMaruxhaMoveTiles, 0, { 0, 0, 0 } },
    { gMaruxhaDamegeFrames, gMaruxhaDamegeAnims, gMaruxhaDamegeTiles, 0, { 0, 0, 0 } },
    { gMaruxhaAtk1Frames, gMaruxhaAtk1Anims, gMaruxhaAtk1Tiles, 0, { 0, 0, 0 } },
    { gMaruxhaAtk4Frames, gMaruxhaAtk4Anims, gMaruxhaAtk4Tiles, 0, { 0, 0, 0 } },
    { gMaruxhaAtk4Frames, gMaruxhaAtk4Anims, gMaruxhaAtk4Tiles, 1, { 0, 0, 0 } },
    { gMaruxhaAtk4Frames, gMaruxhaAtk4Anims, gMaruxhaAtk4Tiles, 2, { 0, 0, 0 } },
    { gMaruxhaAtk1Frames, gMaruxhaAtk1Anims, gMaruxhaAtk1Tiles, 1, { 0, 0, 0 } },
    { gMaruxhaAtk3Frames, gMaruxhaAtk3Anims, gMaruxhaAtk3Tiles, 0, { 0, 0, 0 } },
    { gMaruxhaAtk2Frames, gMaruxhaAtk2Anims, gMaruxhaAtk2Tiles, 0, { 0, 0, 0 } },
    { gMaruxhaAtk1Frames, gMaruxhaAtk1Anims, gMaruxhaAtk1Tiles, 2, { 0, 0, 0 } },
    { gMaruxhaAtk1Frames, gMaruxhaAtk1Anims, gMaruxhaAtk1Tiles, 3, { 0, 0, 0 } },
    { gMaruxhaAtk1Frames, gMaruxhaAtk1Anims, gMaruxhaAtk1Tiles, 4, { 0, 0, 0 } },
};

const AnimDef gHumMahluxiaEffAnimDef = { gMaruxhaBtEff1Frames, gMaruxhaBtEff1Anims, gMaruxhaBtEff1Tiles, 0, { 0, 0, 0 } };

const HumSubDef gHumMahluxiaSubDef = { gMaruxhaBtEffPalette, 90, 0 };

const HumDef gHumMahluxiaDef = { 90, 0, gMaruxhaPalette, 0, { 51, 99, 60, 14, 40, 99, 0 } };

TaskDesc gTaskDescHumMahluxia = {
    "task_hum_mahluxia",
    (TaskInitFunc)task_hum_mahluxia_0,
    (TaskUpdateFunc)task_hum_mahluxia_1,
    (TaskDrawFunc)task_hum_mahluxia_2,
    (TaskDestroyFunc)task_hum_mahluxia_3,
    sizeof(MahluxiaWork),
};

const u32 gHumLaxeneStockMoves[2][3] = {
    { 36, 38, 38 },
    { 37, 37, 36 },
};

const AnimDef gHumLaxeneAnimDefs[15] = {
    { gLaxineIdleFrames, gLaxineIdleAnims, gLaxineIdleTiles, 0, { 0, 0, 0 } },
    { gLaxineMoveFrames, gLaxineMoveAnims, gLaxineMoveTiles, 0, { 0, 0, 0 } },
    { gLaxineMoveFrames, gLaxineMoveAnims, gLaxineMoveTiles, 1, { 0, 0, 0 } },
    { gLaxineDamageFrames, gLaxineDamageAnims, gLaxineDamageTiles, 0, { 0, 0, 0 } },
    { gLaxineRenzokFrames, gLaxineRenzokAnims, gLaxineRenzokTiles, 1, { 0, 0, 0 } },
    { gLaxineRenzokFrames, gLaxineRenzokAnims, gLaxineRenzokTiles, 2, { 0, 0, 0 } },
    { gLaxineMagicFrames, gLaxineMagicAnims, gLaxineMagicTiles, 0, { 0, 0, 0 } },
    { gLaxineMagicFrames, gLaxineMagicAnims, gLaxineMagicTiles, 1, { 0, 0, 0 } },
    { gLaxineMagicFrames, gLaxineMagicAnims, gLaxineMagicTiles, 2, { 0, 0, 0 } },
    { gLaxineMagicFrames, gLaxineMagicAnims, gLaxineMagicTiles, 3, { 0, 0, 0 } },
    { gLaxineMagicFrames, gLaxineMagicAnims, gLaxineMagicTiles, 4, { 0, 0, 0 } },
    { gLaxineMagicFrames, gLaxineMagicAnims, gLaxineMagicTiles, 5, { 0, 0, 0 } },
    { gLaxineKnifethrowFrames, gLaxineKnifethrowAnims, gLaxineKnifethrowTiles, 0, { 0, 0, 0 } },
    { gLaxineRenzokFrames, gLaxineRenzokAnims, gLaxineRenzokTiles, 3, { 0, 0, 0 } },
    { gLaxineRenzokFrames, gLaxineRenzokAnims, gLaxineRenzokTiles, 4, { 0, 0, 0 } },
};

const HumDef gHumLaxeneDef = { 128, 0, gLaxinePalette, 0, { 49, 99, 60, 14, 46, 99, 0 } };

TaskDesc gTaskDescHumLaxene = {
    "task_hum_laxene",
    (TaskInitFunc)task_hum_laxene_0,
    (TaskUpdateFunc)task_hum_laxene_1,
    (TaskDrawFunc)task_hum_laxene_2,
    (TaskDestroyFunc)task_hum_laxene_3,
    sizeof(LaxeneWork),
};

TaskDesc gTaskDescHumLaxeneKnf = {
    "task_hum_laxene_knf",
    (TaskInitFunc)task_hum_laxene_knf_0,
    (TaskUpdateFunc)task_hum_laxene_knf_1,
    (TaskDrawFunc)task_hum_laxene_knf_2,
    (TaskDestroyFunc)task_hum_laxene_knf_3,
    sizeof(LaxeneKnfWork),
};

const u32 gHumAxcelStockMoves[2][3] = {
    { 36, 36, 36 },
    { 36, 37, 36 },
};

const AnimDef gHumAxcelAnimDefs[14] = {
    { gAcceleBt00Frames, gAcceleBt00Anims, gAcceleBt00Tiles, 0, { 0, 0, 0 } },
    { gAcceleBt01Frames, gAcceleBt01Anims, gAcceleBt01Tiles, 0, { 0, 0, 0 } },
    { gAcceleBt02Frames, gAcceleBt02Anims, gAcceleBt02Tiles, 0, { 0, 0, 0 } },
    { gAcceleBt03Frames, gAcceleBt03Anims, gAcceleBt03Tiles, 1, { 0, 0, 0 } },
    { gAcceleBt03Frames, gAcceleBt03Anims, gAcceleBt03Tiles, 2, { 0, 0, 0 } },
    { gAcceleBt04Frames, gAcceleBt04Anims, gAcceleBt04Tiles, 0, { 0, 0, 0 } },
    { gAcceleBt04Frames, gAcceleBt04Anims, gAcceleBt04Tiles, 1, { 0, 0, 0 } },
    { gAcceleBt04Frames, gAcceleBt04Anims, gAcceleBt04Tiles, 2, { 0, 0, 0 } },
    { gAcceleBt06Frames, gAcceleBt06Anims, gAcceleBt06Tiles, 0, { 0, 0, 0 } },
    { gAcceleBt06Frames, gAcceleBt06Anims, gAcceleBt06Tiles, 1, { 0, 0, 0 } },
    { gAcceleBt06Frames, gAcceleBt06Anims, gAcceleBt06Tiles, 2, { 0, 0, 0 } },
    { gAcceleBt05Frames, gAcceleBt05Anims, gAcceleBt05Tiles, 0, { 0, 0, 0 } },
    { gAcceleBt05Frames, gAcceleBt05Anims, gAcceleBt05Tiles, 1, { 0, 0, 0 } },
    { gAcceleBt05Frames, gAcceleBt05Anims, gAcceleBt05Tiles, 2, { 0, 0, 0 } },
};

const AnimDef gHumAxcelWeaponAnimDefs[10] = {
    { gAcceleBtWepFrames, gAcceleBtWepAnims, gAcceleBtWepTiles, 0, { 0, 0, 0 } },
    { gAcceleBt06WepFrames, gAcceleBt06WepAnims, gAcceleBt06WepTiles, 0, { 0, 0, 0 } },
    { gAcceleBt06WepFrames, gAcceleBt06WepAnims, gAcceleBt06WepTiles, 1, { 0, 0, 0 } },
    { gAcceleBt06WepFrames, gAcceleBt06WepAnims, gAcceleBt06WepTiles, 2, { 0, 0, 0 } },
    { gAcceleBt06WepFrames, gAcceleBt06WepAnims, gAcceleBt06WepTiles, 7, { 0, 0, 0 } },
    { gAcceleBt06WepFrames, gAcceleBt06WepAnims, gAcceleBt06WepTiles, 3, { 0, 0, 0 } },
    { gAcceleBt06WepFrames, gAcceleBt06WepAnims, gAcceleBt06WepTiles, 4, { 0, 0, 0 } },
    { gAcceleBt06WepFrames, gAcceleBt06WepAnims, gAcceleBt06WepTiles, 5, { 0, 0, 0 } },
    { gAcceleBt06WepFrames, gAcceleBt06WepAnims, gAcceleBt06WepTiles, 8, { 0, 0, 0 } },
    { gAcceleBt06WepFrames, gAcceleBt06WepAnims, gAcceleBt06WepTiles, 6, { 0, 0, 0 } },
};

const HumSubDef gHumAxcelSubDef = { gBStatesPalette, 64, 0 };

const HumDef gHumAxcelDef = {
#ifdef VERSION_EU
        102
#else
        128
#endif
    , 0, gAccelePalette, 0, { 48, 99, 60, 14, 32, 99, 0 } };

TaskDesc gTaskDescHumAxcel = {
    "task_hum_axcel",
    (TaskInitFunc)task_hum_axcel_0,
    (TaskUpdateFunc)task_hum_axcel_1,
    (TaskDrawFunc)task_hum_axcel_2,
    (TaskDestroyFunc)task_hum_axcel_3,
    sizeof(AxcelWork),
};

TaskDesc gTaskDescHumAxcelPtc = {
    "task_hum_axcel_ptc",
    (TaskInitFunc)task_hum_axcel_ptc_0,
    (TaskUpdateFunc)task_hum_axcel_ptc_1,
    (TaskDrawFunc)task_hum_axcel_ptc_2,
    (TaskDestroyFunc)task_hum_axcel_ptc_3,
    sizeof(AxcelPtcWork),
};

const u32 gHumVixenStockMovesA[3] = {
    36, 37, 36,
};

const u32 gHumVixenStockMovesB[3] = {
    37, 36, 36,
};

const u32 gHumVixenStockMovesC[3] = {
    36, 36, 37,
};

const u32 gHumVixenStockMovesD[3] = {
    36, 36, 36,
};

const AnimDef gHumVixenAnimDefs[15] = {
    { gVixenS1Frames, gVixenS1Anims, gVixenS1Tiles, 0, { 0, 0, 0 } },
    { gVixenW1Frames, gVixenW1Anims, gVixenW1Tiles, 0, { 0, 0, 0 } },
    { gVixenD1Frames, gVixenD1Anims, gVixenD1Tiles, 0, { 0, 0, 0 } },
    { gVixenA1Frames, gVixenA1Anims, gVixenA1Tiles, 0, { 0, 0, 0 } },
    { gVixenM1bFrames, gVixenM1bAnims, gVixenM1bTiles, 0, { 0, 0, 0 } },
    { gVixenM2aFrames, gVixenM2aAnims, gVixenM2aTiles, 0, { 0, 0, 0 } },
    { gVixenM2aFrames, gVixenM2aAnims, gVixenM2aTiles, 2, { 0, 0, 0 } },
    { gVixenM2aFrames, gVixenM2aAnims, gVixenM2aTiles, 3, { 0, 0, 0 } },
    { gVixenM4Frames, gVixenM4Anims, gVixenM4Tiles, 0, { 0, 0, 0 } },
    { gVixenM1aFrames, gVixenM1aAnims, gVixenM1aTiles, 0, { 0, 0, 0 } },
    { gVixenM1aFrames, gVixenM1aAnims, gVixenM1aTiles, 1, { 0, 0, 0 } },
    { gVixenM1aFrames, gVixenM1aAnims, gVixenM1aTiles, 2, { 0, 0, 0 } },
    { gUnk_09EE2098, gUnk_09EE20A8, gUnk_08C08E48, 0, { 0, 0, 0 } },
    { gUnk_09EE2098, gUnk_09EE20A8, gUnk_08C08E48, 1, { 0, 0, 0 } },
    { gUnk_09EE2098, gUnk_09EE20A8, gUnk_08C08E48, 2, { 0, 0, 0 } },
};

const HumDef gHumVixenDef = { 83, 0, gVixenPalette, 0, { 50, 99, 80, 14, 48, 99, 0 } };

TaskDesc gTaskDescHumVixen = {
    "task_hum_vixen",
    (TaskInitFunc)task_hum_vixen_0,
    (TaskUpdateFunc)task_hum_vixen_1,
    (TaskDrawFunc)task_hum_vixen_2,
    (TaskDestroyFunc)task_hum_vixen_3,
    sizeof(VixenWork),
};

TaskDesc gTaskDescHumVixenNdl = {
    "task_hum_vixen_ndl",
    (TaskInitFunc)task_hum_vixen_ndl_0,
    (TaskUpdateFunc)task_hum_vixen_ndl_1,
    (TaskDrawFunc)task_hum_vixen_ndl_2,
    (TaskDestroyFunc)task_hum_vixen_ndl_3,
    sizeof(VixenNdlWork),
};

TaskDesc gTaskDescHumVixenIce = {
    "task_hum_vixen_ice",
    (TaskInitFunc)task_hum_vixen_ice_0,
    (TaskUpdateFunc)task_hum_vixen_ice_1,
    (TaskDrawFunc)task_hum_vixen_ice_2,
    (TaskDestroyFunc)task_hum_vixen_ice_3,
    sizeof(VixenIceWork),
};

const AnimDef gHumVixenFrzAnimDefs[13] = {
    { gVixenReitouFrames, gVixenReitouAnims, gVixenReitouTiles, 0, { 0, 0, 0 } },
    { gVixenReitouFrames, gVixenReitouAnims, gVixenReitouTiles, 1, { 0, 0, 0 } },
    { gReitouSoraFrames, gReitouSoraAnims, gReitouSoraTiles, 0, { 0, 0, 0 } },
    { gVixenReitouFrames, gVixenReitouAnims, gVixenReitouTiles, 2, { 0, 0, 0 } },
    { gReitouSoraFrames, gReitouSoraAnims, gReitouSoraTiles, 1, { 0, 0, 0 } },
    { gVixenReitouFrames, gVixenReitouAnims, gVixenReitouTiles, 3, { 0, 0, 0 } },
    { gReitouSoraFrames, gReitouSoraAnims, gReitouSoraTiles, 2, { 0, 0, 0 } },
    { gReitouRikuFrames, gReitouRikuAnims, gReitouRikuTiles, 0, { 0, 0, 0 } },
    { gReitouRikuFrames, gReitouRikuAnims, gReitouRikuTiles, 1, { 0, 0, 0 } },
    { gReitouRikuFrames, gReitouRikuAnims, gReitouRikuTiles, 2, { 0, 0, 0 } },
    { gReitouNiseFrames, gReitouNiseAnims, gReitouNiseTiles, 0, { 0, 0, 0 } },
    { gReitouNiseFrames, gReitouNiseAnims, gReitouNiseTiles, 1, { 0, 0, 0 } },
    { gReitouNiseFrames, gReitouNiseAnims, gReitouNiseTiles, 2, { 0, 0, 0 } },
};

TaskDesc gTaskDescHumVixenFrz = {
    "task_hum_vixen_frz",
    (TaskInitFunc)task_hum_vixen_frz_0,
    (TaskUpdateFunc)task_hum_vixen_frz_1,
    (TaskDrawFunc)task_hum_vixen_frz_2,
    (TaskDestroyFunc)task_hum_vixen_frz_3,
    sizeof(VixenFrzWork),
};

const VixenFrgDef gVixenFrgDefs[15] = {
    { 12, -29, 3, 0 },
    { 5, -37, 0, 0 },
    { -16, -24, 3, 2 },
    { -18, -6, 0, 1 },
    { 14, -4, 5, 0 },
    { 17, -5, 4, 0 },
    { -12, -44, 5, 1 },
    { -16, -40, 2, 0 },
    { 8, 0, 1, 0 },
    { 0, -13, 2, 2 },
    { -4, -24, 5, 0 },
    { 8, -12, 5, 0 },
    { 4, -48, 5, 3 },
    { -7, -39, 4, 1 },
    { 3, -54, 1, 1 },
};

TaskDesc gTaskDescHumVixenFrg = {
    "task_hum_vixen_frg",
    (TaskInitFunc)task_hum_vixen_frg_0,
    (TaskUpdateFunc)task_hum_vixen_frg_1,
    (TaskDrawFunc)task_hum_vixen_frg_2,
    (TaskDestroyFunc)task_hum_vixen_frg_3,
    sizeof(VixenFrgWork),
};

const u32 gHumLexceusStockMoves[3] = {
    36, 37, 36,
};

const AnimDef gHumLexceusAnimDefs[10] = {
    { gRexeusIdlFrames, gRexeusIdlAnims, gRexeusIdlTiles, 0, { 0, 0, 0 } },
    { gRexeusMovFrames, gRexeusMovAnims, gRexeusMovTiles, 0, { 0, 0, 0 } },
    { gRexeusDmgFrames, gRexeusDmgAnims, gRexeusDmgTiles, 0, { 0, 0, 0 } },
    { gRexeusCmb1Frames, gRexeusCmb1Anims, gRexeusCmb1Tiles, 0, { 0, 0, 0 } },
    { gRexeusCmb2Frames, gRexeusCmb2Anims, gRexeusCmb2Tiles, 1, { 0, 0, 0 } },
    { gRexeusTmhFrames, gRexeusTmhAnims, gRexeusTmhTiles, 0, { 0, 0, 0 } },
    { gRexeusTmhFrames, gRexeusTmhAnims, gRexeusTmhTiles, 1, { 0, 0, 0 } },
    { gRexeusRckFrames, gRexeusRckAnims, gRexeusRckTiles, 0, { 0, 0, 0 } },
    { gRexeusRckFrames, gRexeusRckAnims, gRexeusRckTiles, 1, { 0, 0, 0 } },
    { gRexeusImpFrames, gRexeusImpAnims, gRexeusImpTiles, 0, { 0, 0, 0 } },
};

const HumDef gHumLexceusDef = { 128, 0, gRexeusPalette, 0, { 53, 99, 70, 24, 52, 99, 4 } };

TaskDesc gTaskDescHumLexceus = {
    "task_hum_lexceus",
    (TaskInitFunc)task_hum_lexceus_0,
    (TaskUpdateFunc)task_hum_lexceus_1,
    (TaskDrawFunc)task_hum_lexceus_2,
    (TaskDestroyFunc)task_hum_lexceus_3,
    sizeof(LexceusWork),
};

TaskDesc gTaskDescHumLexTmh = {
    "task_hum_lex_tmh",
    (TaskInitFunc)task_hum_lex_tmh_0,
    (TaskUpdateFunc)task_hum_lex_tmh_1,
    (TaskDrawFunc)task_hum_lex_tmh_2,
    (TaskDestroyFunc)task_hum_lex_tmh_3,
    sizeof(LexTmhWork),
};

TaskDesc gTaskDescHumLexTmh0 = {
    "task_hum_lex_tmh0",
    (TaskInitFunc)task_hum_lex_tmh0_0,
    (TaskUpdateFunc)task_hum_lex_tmh0_1,
    (TaskDrawFunc)task_hum_lex_tmh0_2,
    (TaskDestroyFunc)task_hum_lex_tmh0_3,
    sizeof(LexTmh0Work),
};

TaskDesc gTaskDescHumLexRock = {
    "task_hum_lex_rock",
    (TaskInitFunc)task_hum_lex_rock_0,
    (TaskUpdateFunc)task_hum_lex_rock_1,
    (TaskDrawFunc)task_hum_lex_rock_2,
    (TaskDestroyFunc)task_hum_lex_rock_3,
    sizeof(LexRockWork),
};

TaskDesc gTaskDescHumMahluxiaFlw = {
    "task_hum_mahluxia_flw",
    (TaskInitFunc)task_hum_mahluxia_flw_0,
    (TaskUpdateFunc)task_hum_mahluxia_flw_1,
    (TaskDrawFunc)task_hum_mahluxia_flw_2,
    (TaskDestroyFunc)task_hum_mahluxia_flw_3,
    sizeof(MahluxiaFlwWork),
};

const u32 gHumRikuStockMoves[2][3] = {
    { 36, 36, 38 },
    { 37, 37, 39 },
};

const AnimDef gHumRikuAnimDefs[21] = {
    { gNiserikuIdolFrames, gNiserikuIdolAnims, gNiserikuIdolTiles, 0, { 0, 0, 0 } },
    { gNiserikuRunFrames, gNiserikuRunAnims, gNiserikuRunTiles, 0, { 0, 0, 0 } },
    { gNiserikuDamageFrames, gNiserikuDamageAnims, gNiserikuDamageTiles, 0, { 0, 0, 0 } },
    { gNiserikuJumpFrames, gNiserikuJumpAnims, gNiserikuJumpTiles, 0, { 0, 0, 0 } },
    { gNiserikuJumpFrames, gNiserikuJumpAnims, gNiserikuJumpTiles, 1, { 0, 0, 0 } },
    { gNiserikuJumpFrames, gNiserikuJumpAnims, gNiserikuJumpTiles, 2, { 0, 0, 0 } },
    { gNiserikuJumpFrames, gNiserikuJumpAnims, gNiserikuJumpTiles, 3, { 0, 0, 0 } },
    { gNiserikuJumpFrames, gNiserikuJumpAnims, gNiserikuJumpTiles, 4, { 0, 0, 0 } },
    { gNiserikuDashFrames, gNiserikuDashAnims, gNiserikuDashTiles, 0, { 0, 0, 0 } },
    { gNiserikuFuriharaiFrames, gNiserikuFuriharaiAnims, gNiserikuFuriharaiTiles, 0, { 0, 0, 0 } },
    { gNiserikuTategiriFrames, gNiserikuTategiriAnims, gNiserikuTategiriTiles, 0, { 0, 0, 0 } },
    { gNiserikuKabutoFrames, gNiserikuKabutoAnims, gNiserikuKabutoTiles, 0, { 0, 0, 0 } },
    { gNiserikuKabutoFrames, gNiserikuKabutoAnims, gNiserikuKabutoTiles, 2, { 0, 0, 0 } },
    { gNiserikuDarkfigaFrames, gNiserikuDarkfigaAnims, gNiserikuDarkfigaTiles, 0, { 0, 0, 0 } },
    { gNiserikuYamiStartFrames, gNiserikuYamiStartAnims, gNiserikuYamiStartTiles, 0, { 0, 0, 0 } },
    { gNiserikuYamiStartFrames, gNiserikuYamiStartAnims, gNiserikuYamiStartTiles, 1, { 0, 0, 0 } },
    { gNiserikuYamiStartFrames, gNiserikuYamiStartAnims, gNiserikuYamiStartTiles, 2, { 0, 0, 0 } },
    { gNiserikuYamiIngFrames, gNiserikuYamiIngAnims, gNiserikuYamiIngTiles, 0, { 0, 0, 0 } },
    { gNiserikuYamiIngFrames, gNiserikuYamiIngAnims, gNiserikuYamiIngTiles, 1, { 0, 0, 0 } },
    { gNiserikuYamiIngFrames, gNiserikuYamiIngAnims, gNiserikuYamiIngTiles, 2, { 0, 0, 0 } },
    { gNiserikuYamiEndFrames, gNiserikuYamiEndAnims, gNiserikuYamiEndTiles, 0, { 0, 0, 0 } },
};

const HumDef gHumRikuDef = { 64, 0, gNiserikuPalette, 0, { 45, 99, 38, 14, 24, 99, 0 } };

const HumSubDef gHumRikuSubDef = { gNiserikuPalette, 64, 0 };

TaskDesc gTaskDescHumRiku = {
    "task_hum_riku",
    (TaskInitFunc)task_hum_riku_0,
    (TaskUpdateFunc)task_hum_riku_1,
    (TaskDrawFunc)task_hum_riku_2,
    (TaskDestroyFunc)task_hum_riku_3,
    sizeof(RikuWork),
};

const AnimDef gHumLeonAnimDefs[5] = {
    { gReonFl00Frames, gReonFl00Anims, gReonFl00Tiles, 0, { 0, 0, 0 } },
    { gUnk_09EE25D0, gUnk_09EE25E4, gUnk_08C6668E, 0, { 0, 0, 0 } },
    { gUnk_09EE25D0, gUnk_09EE25E4, gUnk_08C6668E, 3, { 0, 0, 0 } },
    { gUnk_09EE25D0, gUnk_09EE25E4, gUnk_08C6668E, 1, { 0, 0, 0 } },
    { gUnk_09EE25D0, gUnk_09EE25E4, gUnk_08C6668E, 2, { 0, 0, 0 } },
};

const HumDef gHumLeonDef = { 128, 0, gReonPalette, 0, { 41, 99, 64, 14, 40, 99, 0 } };

TaskDesc gTaskDescHumLeon = {
    "task_hum_leon",
    (TaskInitFunc)task_hum_leon_0,
    (TaskUpdateFunc)task_hum_leon_1,
    (TaskDrawFunc)task_hum_leon_2,
    (TaskDestroyFunc)task_hum_leon_3,
    sizeof(LeonWork),
};

const AnimDef gHumRobeAnimDefs[2] = {
    { gRobeFl00Frames, gRobeFl00Anims, gRobeFl00Tiles, 5, { 0, 0, 0 } },
    { gUnk_09EE25F4, gUnk_09EE2604, gUnk_08C67F86, 0, { 0, 0, 0 } },
};

const HumDef gHumRobeDef = { 128, 0, gRobePalette, 0, { 51, 99, 64, 14, 32, 99, 0 } };

void task_hum_cloud_0(CloudWork* work, void* obj) {
    HumInit(&work->base, &gHumCloudDef);
    work->unk_188 = 0;
    work->base.stockMoves = gHumCloudStockMoves[0];
}

u8 task_hum_cloud_1(CloudWork* work) {
    CloudWork* w;
    BtlObj* act;
    s32 x;
    s32 y;
    s32 z;
    u8 ret;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &x, &y, &z);

    switch (_0800E434(&work->base)) {
    case 5:
        work->base.stateTimer = 0;
        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
        case 38:
            if (act->z < 0) {
                work->base.state = 21;
            } else {
                work->base.state = 19;
            }
            break;
        case 37:
        case 39:
            if (act->z < 0) {
                work->base.state = 21;
            } else {
                work->base.state = 20;
            }
            break;
        case 0xEB3ACEB3:
            work->base.state = 31;
            break;
        case 0xEB3AA6B3:
            work->base.state = 28;
            break;
        }
        break;
    case 4:
        work->nextState = 0;
        break;
    }
    if (HumChooseCardAction(&work->base, 8, 32, 32, 24)) {
        if ((u16)GetRandom() % 2) {
            work->base.stockMoves = gHumCloudStockMoves[0];
        } else {
            work->base.stockMoves = gHumCloudStockMoves[1];
        }
    }
    switch (work->base.state) {
    case 12:
    case 18:
        AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        break;
    case 17: {
        AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 0, 3, w->base.tiles);
        if (gBtlWork->flags & 0x20000000) {
            if ((u8)CloudTryJumpAway(w)) {
                break;
            }
        }
        if ((act->x - x >= 0) ? act->x - x <= 0x4FFF : x - act->x <= 0x4FFF) {
            if (x <= 0xFFFF) {
                CloudLeapTo(w, (gBtlWork->xMax - 40) << 8,
                    (gBtlWork->yMin + gBtlWork->yMax) << 7);
            } else {
                CloudLeapTo(w, (gBtlWork->xMin + 40) << 8,
                    (gBtlWork->yMin + gBtlWork->yMax) << 7);
            }
        }
        break;
    }
    case 0:
        AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 0, 3, w->base.tiles);
        if (func_08081828()) {
            break;
        }
        if ((u16)((u16)GetRandom() % 60) == 0) {
            work->base.state = 8;
            work->base.stateTimer = 0;
            break;
        }
        if (HumIsNearAreaEdge(&work->base, 40)) {
            CloudLeapTo(w, 0x10000,
                (gBtlWork->yMin + gBtlWork->yMax) << 7);
            break;
        }
        if (gBtlWork->flags & 0x20000000) {
            if ((u8)CloudTryJumpAway(w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 30);
        }
        work->base.stateTimer++;
        break;
    case 8: {
        AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 1, 3, w->base.tiles);
        work->base.targetX = x;
        work->base.targetY = y;
        if (HumMoveToward(&work->base, work->base.targetX, y, 0x133)) {
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }
        if ((u16)((u16)GetRandom() % 150) == 0) {
            if ((act->x - x >= 0) ? act->x - x > 70 : x - act->x > 70) {
                CloudJumpTo(w, x, y);
                break;
            }
        }
        if (gBtlWork->flags & 0x20000000) {
            if ((u8)CloudTryJumpAway(w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 30);
        }
        work->base.stateTimer++;
        break;
    }
    case 1:
    case 3:
    case 9:
    case 11:
    case 14:
        AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        break;
    case 19:
        if ((s16)work->base.stateTimer == 0) {
            AnimReset(&work->base.anim);
            AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 8, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_MKU_ATTACK00);
            MakeOpponentsHittable();
        }
        if (AnimGetFrame(&work->base.anim) == 6) {
            if ((act->flags & 4)
                ? ApplyAttackBox(0x11A, act->x - 9216, act->y, act->z, 24, 16, 50)
                : ApplyAttackBox(0x11A, act->x + 9216, act->y, act->z, 24, 16, 50)) {
                m4aSongNumStart(SONG_EF_KU_ATT00);
            }
        } else if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }
        work->base.stateTimer++;
        break;
    case 20:
        if ((s16)work->base.stateTimer == 0) {
            AnimReset(&work->base.anim);
            AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_MKU_ATTACK01);
            MakeOpponentsHittable();
        }
        if (AnimGetFrame(&work->base.anim) == 6) {
            if ((act->flags & 4)
                ? ApplyAttackBox(0x11A, act->x - 8192, act->y, act->z, 22, 16, 50)
                : ApplyAttackBox(0x11A, act->x + 8192, act->y, act->z, 22, 16, 50)) {
                m4aSongNumStart(SONG_EF_KU_ATT01);
            }
        } else if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }
        work->base.stateTimer++;
        break;
    case 25:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
        }
        if ((s16)work->base.stateTimer > 3) {
            work->base.stateTimer = 0;
            work->base.state = 26;
            work->base.vz = w->unk_188;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 26: {
        s32 d;

        act->x += ((s32)work->base.targetX - act->x) >> 4;
        act->y += ((s32)work->base.targetY - act->y) >> 4;
        d = work->base.vz;
        if (d < 0) {
            if (d <= -0x200) {
                AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            }
        } else if (d <= 0x1FF) {
            AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
        } else {
            AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
        }
        if (act->z >= 0) {
            work->base.stateTimer = 0;
            work->base.state = 27;
        } else {
            HumFaceTarget(&work->base, 1);
            work->base.stateTimer++;
        }
        break;
    }
    case 27:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 7, 0, w->base.tiles);
        }
        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = w->nextState;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 33: {
        s32 d;

        if ((s16)work->base.stateTimer == 0) {
            work->base.vz = -0x500;
        }
        d = work->base.vz;
        if (d < 0) {
            if (d > -0x200) {
                AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            }
        }
        if ((s32)work->base.vz > 0) {
            work->base.stateTimer = 0;
            work->base.state = 34;
        } else {
            work->base.stateTimer++;
        }
        break;
    }
    case 34: {
        s32 d;

        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 14, 0, w->base.tiles);
            w->unk_188 = 0;
            work->base.targetZ = act->z;
        }
        ret = HumMoveToward(&work->base, work->base.targetX, work->base.targetY, w->unk_188);
        if (ret) {
            work->base.state = 26;
            w->nextState = 0;
            work->base.stateTimer = 0;
        } else {
            w->unk_188 += 76;
            if ((s32)w->unk_188 > 0x800) {
                w->unk_188 = 0x800;
            }
            d = ((s32)work->base.targetX - act->x) >> 3;
            if (d < 0) {
                d = -d;
            }
            if (d < (s32)w->unk_188) {
                w->unk_188 = d;
            }
            {
                s32 v = work->base.targetZ + gSineTable[(gFrameCounter * 4) & 0xFF] * 12;
            work->base.vz = 0;
            act->z += (v - act->z) >> 3;
            }
            if (act->x < (s32)work->base.targetX) {
                act->flags &= ~4;
            } else {
                act->flags |= 4;
            }
            work->base.stateTimer++;
        }
        break;
    }
    case 21: {
        s32 d;

        if ((s16)work->base.stateTimer == 0) {
            AnimReset(&work->base.anim);
            AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 10, 0, w->base.tiles);
        }
        act->z += (gSineTable[gFrameCounter % 256] * 10 - (d = act->z + 0x2C00)) >> 3;
        if (act->x < x) {
            s32 d = act->x + 0x2100;
            act->x += (x - d) >> 3;
        } else {
            s32 d = act->x - 0x2100;
            act->x += (x - d) >> 3;
        }
        act->y += (y - act->y) >> 4;
        work->base.vz = 0;
        if ((s16)work->base.stateTimer > 30) {
            work->base.state = 22;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    }
    case 22:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 11, 0, w->base.tiles);
        }
        work->base.vz = 0;
        if ((s16)work->base.stateTimer > 8) {
            work->base.vz = 0x500;
            work->base.state = 23;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 23:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
        }
        if (act->z >= 0) {
            work->base.state = 24;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 24:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 13, 0, w->base.tiles);
        }
        if ((act->flags & 4)
            ? ApplyAttackBox(0x11A, act->x - 0x2000, act->y, act->z, 22, 16, 30)
            : ApplyAttackBox(0x11A, act->x + 0x2000, act->y, act->z, 22, 16, 30)) {
            m4aSongNumStart(SONG_EF_KU_ATT02);
        }
        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 31:
        if (act->z >= act->groundZ) {
            s32 v;
            work->base.targetX = x + (v = ((u16)((u16)GetRandom() % 41) << 8) - 0x1400);
            work->base.targetY = y;
            work->base.state = 25;
            work->base.stateTimer = 0;
            w->unk_188 = -0x500;
            w->nextState = 32;
        }
        break;
    case 32: {
        s32 d;
        if ((s16)work->base.stateTimer == 0) {
            w->unk_18E = 0;
            AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 18, 0, w->base.tiles);
        } else if ((s16)w->unk_18E == 0 && AnimIsFinished(&work->base.anim)) {
            AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 19, 0, w->base.tiles);
            w->unk_18E++;
        } else if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            w->nextState = 0;
            work->base.stateTimer = 0;
            break;
        }
        HumFaceTarget(&work->base, 1);
        if (work->base.anim.timer == 0) {
            if ((s16)w->unk_18E == 0) {
                switch (AnimGetFrame(&work->base.anim)) {
                case 2:
                    m4aSongNumStart(SONG_VO_MKU_ATTACK00);
                    break;
                case 6:
                    if ((act->flags & 4)
                        ? ApplyAttackBox(0x11B, act->x - 0x2800, act->y, act->z, 24, 24, 48)
                        : ApplyAttackBox(0x11B, act->x + 0x2800, act->y, act->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT00);
                        FadeStartIn(2, 20);
                        if (act->flags & 4) {
                            SetBattleZoom(6, 0x133, act->x - 0x2000, (d = act->z - 0x1800, act->y + d));
                        } else {
                            SetBattleZoom(6, 0x133, act->x + 0x2000, (d = act->z - 0x1800, act->y + d));
                        }
                    }
                    break;
                case 7:
                    SetBattleZoom(6, 0x100, gBtlWork->x2, gBtlWork->y2);
                    break;
                case 9:
                    m4aSongNumStart(SONG_VO_MKU_ATTACK01);
                    break;
                }
            } else {
                switch (AnimGetFrame(&work->base.anim)) {
                case 0:
                    MakeOpponentsHittable();
                    if ((act->flags & 4)
                        ? ApplyAttackBox(0x11B, act->x - 0x2800, act->y, act->z, 24, 24, 48)
                        : ApplyAttackBox(0x11B, act->x + 0x2800, act->y, act->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT01);
                        FadeStartIn(2, 20);
                        if (act->flags & 4) {
                            SetBattleZoom(6, 0x133, act->x - 0x2000, (d = act->z - 0x1800, act->y + d));
                        } else {
                            SetBattleZoom(6, 0x133, act->x + 0x2000, (d = act->z - 0x1800, act->y + d));
                        }
                    }
                    break;
                case 1:
                    SetBattleZoom(6, 0x100, gBtlWork->x2, gBtlWork->y2);
                    break;
                case 4:
                    m4aSongNumStart(SONG_VO_MKU_ATTACK02);
                    break;
                case 5:
                    MakeOpponentsHittable();
                    if ((act->flags & 4)
                        ? ApplyAttackBox(0x11C, act->x - 0x2800, act->y, act->z, 24, 24, 48)
                        : ApplyAttackBox(0x11C, act->x + 0x2800, act->y, act->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT02);
                        FadeStartIn(2, 50);
                        if (act->flags & 4) {
                            SetBattleZoom(6, 0x200, act->x - 0x2000, (d = act->z - 0x1800, act->y + d));
                        } else {
                            SetBattleZoom(6, 0x200, act->x + 0x2000, (d = act->z - 0x1800, act->y + d));
                        }
                    }
                    break;
                case 6:
                    SetBattleZoom(6, 0x100, gBtlWork->x2, gBtlWork->y2);
                    break;
                }
            }
        }
        work->base.stateTimer++;
        break;
    }
    case 28: {
        s32 d;

        if ((s16)work->base.stateTimer == 0) {
            work->base.vz = -0x500;
        }
        d = work->base.vz;
        if (d < 0) {
            if (d > -0x200) {
                AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            }
        }
        if ((s32)work->base.vz > 0) {
            work->base.stateTimer = 0;
            work->base.state = 29;
            w->state = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    }
    case 29: {
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 14, 0, w->base.tiles);
            w->unk_188 = 0;
            if (act->flags & 4) {
                work->base.targetX = (gBtlWork->xMin + 50) << 8;
            } else {
                work->base.targetX = (gBtlWork->xMax - 50) << 8;
            }
            work->base.targetY = act->y;
            work->base.targetZ = -0xC800;
        }
        work->base.vz = 0;
        act->x += ((s32)work->base.targetX - act->x) >> 4;
        act->y += ((s32)work->base.targetY - act->y) >> 4;
        {
            s32 v;
        v = ((s32)work->base.targetZ - act->z) >> 3;
        if (v > (s32)w->unk_188) {
            v = w->unk_188;
        }
        if (v < -(s32)w->unk_188) {
            v = -w->unk_188;
        }
        act->z += v;
        }
        w->unk_188 += 0x80;
        if ((act->z - (s32)work->base.targetZ >= 0) ? act->z - (s32)work->base.targetZ <= 0xFFF : (s32)work->base.targetZ - act->z <= 0xFFF) {
            work->base.state = 30;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    }
    case 30:
        if ((s16)work->base.stateTimer == 0) {
            work->base.targetX = x;
            work->base.targetY = y;
            work->base.targetZ = z - 0x1000;
            MakeOpponentsHittable();
            switch ((s16)w->state) {
            case 0:
                m4aSongNumStart(SONG_VO_MKU_ATTACK00);
                AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 15, 0, w->base.tiles);
                break;
            case 1:
                m4aSongNumStart(SONG_VO_MKU_ATTACK01);
                AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 16, 0, w->base.tiles);
                break;
            case 2:
            default:
                m4aSongNumStart(SONG_VO_MKU_ATTACK02);
                AnimChangeWithDef(gHumCloudAnimDefs, &w->base.anim, 17, 0, w->base.tiles);
                break;
            }
            if (act->x < (s32)work->base.targetX) {
                act->flags &= ~4;
            } else {
                act->flags |= 4;
            }
        }
        work->base.vz = 0;
        act->x += ((s32)work->base.targetX - act->x) >> 3;
        act->y += ((s32)work->base.targetY - act->y) >> 3;
        act->z += ((s32)work->base.targetZ - act->z) >> 3;
        if (work->base.anim.timer == 0) {
            switch ((s16)w->state) {
            case 0:
                if (AnimGetFrame(&work->base.anim) == 4) {
                    if ((act->flags & 4)
                        ? ApplyAttackBox(0x11D, act->x - 0x2800, act->y, act->z, 24, 24, 48)
                        : ApplyAttackBox(0x11D, act->x + 0x2800, act->y, act->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT00);
                        FadeStartIn(2, 20);
                    }
                }
                break;
            case 1:
                if (AnimGetFrame(&work->base.anim) == 3) {
                    MakeOpponentsHittable();
                    if ((act->flags & 4)
                        ? ApplyAttackBox(0x11D, act->x - 0x2800, act->y, act->z, 24, 24, 48)
                        : ApplyAttackBox(0x11D, act->x + 0x2800, act->y, act->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT01);
                        FadeStartIn(2, 20);
                    }
                }
                break;
            case 2:
            default:
                if (AnimGetFrame(&work->base.anim) == 3) {
                    MakeOpponentsHittable();
                    if ((act->flags & 4)
                        ? ApplyAttackBox(0x11D, act->x - 0x2800, act->y, act->z, 24, 24, 48)
                        : ApplyAttackBox(0x11D, act->x + 0x2800, act->y, act->z, 24, 24, 48)) {
                        m4aSongNumStart(SONG_EF_KU_ATT02);
                        FadeStartIn(2, 20);
                    }
                }
                break;
            }
        }
        if ((s16)work->base.stateTimer > 23 && AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            w->state++;
            if ((s16)w->state > 2) {
                ClearBtlObjActionFlags(act);
                work->base.state = 26;
                w->nextState = 0;
            } else {
                work->base.state = 29;
            }
        } else {
            work->base.stateTimer++;
        }
        break;
    }
    return HumUpdate(&work->base);
}

void task_hum_cloud_2(HumWork* work) {
    HumDraw(work);
}

void task_hum_cloud_3(HumWork* work) {
    HumReleaseResources(work);
}

void HookJumpOffset(CloudWork* work, s16 a, s32 b) {
    HumWork* w = &work->base;
    BtlObj* act = &w->actor;

    if (act->flags & 4) {
        work->base.targetX = act->x - (a << 8);
    } else {
        work->base.targetX = act->x + (a << 8);
    }
    w->targetY = act->y;
    w->state = 0x16;
    w->stateTimer = 0;
    work->unk_188 = -b;
}

void HookJumpTo(CloudWork* work, s32 a, s32 b) {
    work->base.targetX = a;
    work->base.targetY = b;
    work->base.state = 0x16;
    work->base.stateTimer = 0;
    work->unk_188 = -0x680;
}

u8 HookTryJumpAway(CloudWork* work) {
    s32 x;
    s32 y;
    BtlObj* c;

    c = gBtlWork->actor;
    GetEnemyTargetPosition(&work->base.actor, &x, &y, 0);
    HumFaceTarget(&work->base, 1);

    if (HumIsInPlayerReach(&work->base, 0x100, 0x100, 0x100)) {
        if (gBtlWork->flags & 0x8000) {
            HookJumpOffset(work, -99, 0x280);
        } else if (GetRandom() & 1) {
            if (c->flags & 4) {
                HookJumpTo(work, x + 0x2800, y);
            } else {
                HookJumpTo(work, x - 0x2800, y);
            }
        } else {
            HookJumpOffset(work, -80, 0x500);
        }
        return 1;
    }
    return 0;
}

void task_hum_hook_0(HookWork* work, void* arg) {
    TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumHookMoon, 0);
    HumInit(&work->base, &gHumHookDef);
    work->base.actor.flags |= 0x10000000;

    if (GetRandom() % 2) {
        work->base.stockMoves = gHumHookStockMovesA;
    } else {
        work->base.stockMoves = gHumHookStockMovesB;
    }
    work->base.flags |= 0x40;
    work->unk_188 = 0;
    work->playerSlide = 0;
    work->slide = 0;
    work->angle = 0;
    work->rollLevel = 0;
    work->flags = 0;
    TaskPoolInit(&work->tasks, 3);
}

u8 task_hum_hook_1(HookWork* work) {
    HookWork* w;
    BtlObj* act;
    BtlObj* c;
    VixenNdlArgs args;
    s32 x;
    s32 y;
    s32 z;
    u16 f;
    u8 a;

    w = work;
    act = &work->base.actor;
    c = gBtlWork->actor;
    GetEnemyTargetPosition(act, &x, &y, &z);

    if (_0800E434(&work->base) == 5) {
        work->base.stateTimer = 0;

        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
            work->base.state = 20;
            break;
        case 37:
            work->base.state = 21;
            break;
        case 38:
            work->base.state = 19;
            break;
        case 39:
            work->base.state = 25;
            break;
        case 0xED1AF6BD:
            work->base.state = 26;
            break;
        case 0xED1B1EC7:
            work->base.state = 29;
            work->base.steps = 0;
            break;
        }
    }

    if (HumChooseCardAction(&work->base, 13, 40, 40, 24)) {
        if (GetRandom() % 2) {
            w->base.stockMoves = gHumHookStockMovesA;
        } else {
            w->base.stockMoves = gHumHookStockMovesB;
        }
    }

    switch (work->base.state) {
    case 12:
    case 18:
        AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        break;
    case 17: {
        s32 d;

        AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 0, 3, w->base.tiles);

        if (gBtlWork->flags & 0x20000000) {
            if (HookTryJumpAway((CloudWork*)w)) {
                break;
            }
        }
        d = act->x - x;

        if ((d >= 0) ? d <= 0x3FFF : (d = x - act->x) <= 0x3FFF) {
            if (x <= 0xFFFF) {
                HookJumpTo((CloudWork*)w, (gBtlWork->xMax - 40) << 8,
                    (gBtlWork->yMin + gBtlWork->yMax) << 7);
            } else {
                HookJumpTo((CloudWork*)w, (gBtlWork->xMin + 40) << 8,
                    (gBtlWork->yMin + gBtlWork->yMax) << 7);
            }
        }
        break;
    }
    case 0:
        AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 0, 3, w->base.tiles);

        if (func_08081828()) {
            break;
        }

        if (GetRandom() % 150 == 0) {
            work->base.state = 8;
            work->base.stateTimer = 0;
            break;
        }

        if (HumIsNearAreaEdge(&work->base, 40)) {
            HookJumpTo((CloudWork*)w, 0x10000,
                (gBtlWork->yMin + gBtlWork->yMax) << 7);
            break;
        }

        if (gBtlWork->flags & 0x20000000) {
            if (HookTryJumpAway((CloudWork*)w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 8);
        }
        work->base.stateTimer++;
        break;
    case 8:
        AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 1, 3, w->base.tiles);
        work->base.targetX = x;
        work->base.targetY = y;

        if (HumMoveToward(&work->base, work->base.targetX, y, 358)) {
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }

        if (gBtlWork->flags & 0x20000000) {
            if (HookTryJumpAway((CloudWork*)w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 8);
        }
        work->base.stateTimer++;
        break;
    case 3:
        AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        gBtlWork->rotation = 0;
        break;
    case 1:
    case 9:
    case 11:
    case 14:
        AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        break;
    case 2:
        if (func_08081828() == 0) {
            break;
        }

        if (GetRandom() % 10 != 0) {
            break;
        }

        if (x <= 0xFFFF) {
            work->base.targetX = (gBtlWork->xMax - 40) << 8;
        } else {
            work->base.targetX = (gBtlWork->xMin + 40) << 8;
        }
        work->base.targetY = (gBtlWork->yMin + gBtlWork->yMax) << 7;
        work->base.state = 23;
        work->base.stateTimer = 0;
        work->base.vz = -0x680;
        break;
    case 26:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 11, 1, w->base.tiles);
        }
        BtlMapFollowPosition(act->x, act->y, act->z);
        HumFaceTarget(&work->base, 1);

        if (act->flags & 4) {
            s32 d = act->x - 0x1000;
            act->x += (x - d) >> 4;
        } else {
            s32 d = act->x + 0x1000;
            act->x += (x - d) >> 4;
        }
        act->y += (y - act->y) >> 4;

        if (work->base.anim.timer == 0) {
            switch (AnimGetFrame(&work->base.anim)) {
            case 2:
            case 4:
            case 7:
                MakeOpponentsHittable();

                if ((act->flags & 4)
                    ? ApplyAttackBox(280, act->x - 0x1400, act->y, act->z, 20, 20, 50)
                    : ApplyAttackBox(280, act->x + 0x1400, act->y, act->z, 20, 20, 50)) {
                    m4aSongNumStart(SONG_BTL_MON_SWORD00);
                }
                break;
            }
        }

        if ((s16)work->base.stateTimer > 120) {
            work->base.state = 27;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 27:
        BtlMapFollowPosition(act->x, act->y, act->z);

        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
        }
        HumFaceTarget(&work->base, 1);

        if (act->flags & 4) {
            s32 d = act->x - 0x1000;
            act->x += (x - d) >> 4;
        } else {
            s32 d = act->x + 0x1000;
            act->x += (x - d) >> 4;
        }
        act->y += (y - act->y) >> 4;

        if (work->base.anim.timer == 0 && AnimGetFrame(&work->base.anim) == 3) {
            MakeOpponentsHittable();

            if ((act->flags & 4)
                ? ApplyAttackBox(0x119, act->x - 0x1400, act->y, act->z, 20, 20, 50)
                : ApplyAttackBox(0x119, act->x + 0x1400, act->y, act->z, 20, 20, 50)) {
                m4aSongNumStart(SONG_BTL_MON_SWORD00);
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 28;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 28:
        BtlMapFollowPosition(act->x, act->y, act->z);

        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
            w->bombTask = 0;
            w->bombTask2 = 0;
            w->bombTask3 = 0;
            w->flags &= 0xFFFC;
            m4aSongNumStart(SONG_VO_HO_VOICE00);
        }

        if ((w->flags & 1) == 0) {
            if (AnimGetFrame(&work->base.anim) == 6 && work->base.anim.timer == 0) {
                if (act->flags & 4) {
                    args.x = act->x - 0x3200;
                    args.y = act->y;
                    args.z = act->z - 0x1C00;
                    args.unk_12 = 1;
                    args.unk_14 = 1;
                } else {
                    args.x = act->x + 0x3200;
                    args.y = act->y;
                    args.z = act->z - 0x1C00;
                    args.unk_12 = 0;
                    args.unk_14 = 1;
                }
                w->bombTask = TaskCreate(&w->tasks, &gTaskDescHumHookBomb, &args);
                w->bombTask2 = TaskCreate(&w->tasks, &gTaskDescHumHookBomb, &args);
                w->bombTask3 = TaskCreate(&w->tasks, &gTaskDescHumHookBomb, &args);
                w->flags |= 1;
            }
        } else if (w->flags & 2) {
            if (AnimIsFinished(&work->base.anim)) {
                AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 14, 1, w->base.tiles);
            }
        } else {
            if (AnimIsFinished(&work->base.anim)) {
                AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 13, 0, w->base.tiles);
                w->flags |= 2;
            }
        }

        if ((w->flags & 1) &&
            IsTaskActiveNamed(w->bombTask, gTaskDescHumHookBomb.name) == 0 &&
            IsTaskActiveNamed(w->bombTask2, gTaskDescHumHookBomb.name) == 0 &&
            IsTaskActiveNamed(w->bombTask3, gTaskDescHumHookBomb.name) == 0) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 25:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
            w->bombTask = 0;
            w->flags &= 0xFFFC;
            m4aSongNumStart(SONG_VO_HO_VOICE00);
        }

        if ((w->flags & 1) == 0) {
            if (AnimGetFrame(&work->base.anim) == 6 && work->base.anim.timer == 0) {
                if (act->flags & 4) {
                    args.x = act->x - 0x3200;
                    args.y = act->y;
                    args.z = act->z - 0x1C00;
                    args.unk_12 = 1;
                    args.unk_14 = 0;
                } else {
                    args.x = act->x + 0x3200;
                    args.y = act->y;
                    args.z = act->z - 0x1C00;
                    args.unk_12 = 0;
                    args.unk_14 = 0;
                }
                w->bombTask = TaskCreate(&w->tasks, &gTaskDescHumHookBomb, &args);
                w->flags |= 1;
            }
        } else if (w->flags & 2) {
            if (AnimIsFinished(&work->base.anim)) {
                AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 14, 1, w->base.tiles);
            }
        } else {
            if (AnimIsFinished(&work->base.anim)) {
                AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 13, 0, w->base.tiles);
                w->flags |= 2;
            }
        }

        if ((w->flags & 1) &&
            IsTaskActiveNamed(w->bombTask, gTaskDescHumHookBomb.name) == 0) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 29:
        if ((s16)work->base.stateTimer == 0) {
            AnimReset(&work->base.anim);
            AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
            w->bombTask = 0;
            w->flags &= 0xFFFE;
            m4aSongNumStart(SONG_VO_HO_VOICE00);
        }
        HumFaceTarget(&work->base, 1);

        if ((w->flags & 1) == 0) {
            if (AnimGetFrame(&work->base.anim) == 6 && work->base.anim.timer == 0) {
                if (act->flags & 4) {
                    args.x = act->x - 0x3200;
                    args.y = act->y;
                    args.z = act->z - 0x1C00;
                    args.unk_12 = 1;
                    args.unk_14 = 2;
                } else {
                    args.x = act->x + 0x3200;
                    args.y = act->y;
                    args.z = act->z - 0x1C00;
                    args.unk_12 = 0;
                    args.unk_14 = 2;
                }
                w->bombTask = TaskCreate(&w->tasks, &gTaskDescHumHookBomb, &args);
                w->flags |= 1;
            }
        }

        if (w->flags & 1) {
            if ((s16)work->base.steps <= 4) {
                work->base.stateTimer = 0;
                work->base.steps++;
                work->base.state = 29;
            } else {
                if (IsTaskActiveNamed(w->bombTask, gTaskDescHumHookBomb.name) == 0) {
                    work->base.stateTimer = 0;
                    ClearBtlObjActionFlags(act);
                    work->base.state = 0;
                }
            }
        } else {
            work->base.stateTimer++;
        }
        break;
    case 20:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_HO_VOICE00);
        }
        f = AnimGetFrame(&work->base.anim);

        if (f > 1) {
            if (act->flags & 4) {
                s32 d = act->x + 0x1400;
                act->x += (act->originX - d) >> 3;
            } else {
                s32 d = act->x - 0x1400;
                act->x += (act->originX - d) >> 3;
            }
        }

        if (f == 2) {
            if ((act->flags & 4)
                ? ApplyAttackBox(0x115, act->x - 0x2000, act->y, act->z, 16, 16, 50)
                : ApplyAttackBox(0x115, act->x + 0x2000, act->y, act->z, 16, 16, 50)) {
                m4aSongNumStart(SONG_BTL_MON_SWORD00);
            }
        } else if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }
        work->base.stateTimer++;
        break;
    case 19:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 8, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_HO_VOICE01);
        }
        f = AnimGetFrame(&work->base.anim);

        if (f >= 3 && f <= 5) {
            if (act->flags & 4) {
                s32 d = act->x + 0x4000;
                act->x += (act->originX - d) >> 3;
            } else {
                s32 d = act->x - 0x4000;
                act->x += (act->originX - d) >> 3;
            }
        }

        switch (f) {
        case 4:
        case 5:
            if ((act->flags & 4)
                ? ApplyAttackBox(0x115, act->x - 0x4400, act->y, act->z, 20, 16, 50)
                : ApplyAttackBox(0x115, act->x + 0x4400, act->y, act->z, 20, 16, 50)) {
                m4aSongNumStart(SONG_BTL_MON_SWORD00);
            }
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 21:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 10, 0, w->base.tiles);
        }
        HumFaceTarget(&work->base, 1);
        f = AnimGetFrame(&work->base.anim);

        switch (f) {
        case 2:
        case 6:
            if (work->base.anim.timer == 0) {
                if (GetRandom() & 1) {
                    m4aSongNumStart(SONG_VO_HO_VOICE00);
                } else {
                    m4aSongNumStart(SONG_VO_HO_VOICE01);
                }
                a = GetAngle(act->x, act->y, x, y);
                work->base.targetX = act->x + gSineTable[a] * 50;
                work->base.targetY = act->y + -gSineTable[a + 64] * 50;
                MakeOpponentsHittable();
            }
            act->x += ((s32)work->base.targetX - act->x) >> 3;
            act->y += ((s32)work->base.targetY - act->y) >> 3;

            if ((act->flags & 4)
                ? ApplyAttackBox(278, act->x - 0x1000, act->y, act->z, 32, 24, 70)
                : ApplyAttackBox(278, act->x + 0x1000, act->y, act->z, 32, 24, 70)) {
                m4aSongNumStart(SONG_BTL_MON_SWORD01);
            }
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 22:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 23;
            work->base.vz = w->unk_188;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 23: {
        s32 d;

        act->x += ((s32)work->base.targetX - act->x) >> 4;
        act->y += ((s32)work->base.targetY - act->y) >> 4;
        d = work->base.vz;

        if (d < 0) {
            if (d > -0x200) {
                AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            }
        } else if (d <= 0x1FF) {
            AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
        } else {
            AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
        }

        if (act->z >= 0) {
            work->base.stateTimer = 0;
            work->base.state = 24;
        } else {
            HumFaceTarget(&work->base, 1);
            work->base.stateTimer++;
        }
        break;
    }
    case 24:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHookAnimDefs, &w->base.anim, 7, 0, w->base.tiles);
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    }

    if ((s16)act->hp > 0) {
        gBtlWork->rotation = (gSineTable[(w->angle / 2) & 0xFF] * gHumHookRollAmplitudes[w->rollLevel]) >> 8;
        {
            s32 t;

            t = w->angle + 1;
            w->angle = t;

            if ((t & 511) == 0) {
                w->rollLevel++;

                if (w->rollLevel > 7) {
                    w->rollLevel = 1;
                }
            }
        }

        if (c->z >= c->groundZ && (s16)c->hp > 0 && c->badStatus != 2 &&
            !(c->flags & 16)) {
            w->playerSlide += (((s16)GetAngleDiff(0, gBtlWork->rotation) << 6) - w->playerSlide) >> 4;
            c->x -= w->playerSlide;
        } else {
            w->playerSlide = 0;
        }

        if (act->z >= act->groundZ && (s16)act->hp > 0 && act->badStatus != 2 &&
            !(act->flags & 16)) {
            w->slide += (((s16)GetAngleDiff(0, gBtlWork->rotation) << 6) - w->slide) >> 4;
            act->x -= w->slide;
        } else {
            w->slide = 0;
        }
    }
    TaskPoolUpdate(&w->tasks);
    return HumUpdate(&work->base);
}

void task_hum_hook_2(HookWork* work) {
    TaskPoolDraw(&work->tasks);
    HumDraw(&work->base);
}

void task_hum_hook_3(HookWork* work) {
    TaskPoolDestroy(&work->tasks);
    HumReleaseResources(&work->base);
    gBtlWork->rotation = 0;
}

void task_hum_hook_moon_0(HookMoonWork* work) {
    work->tiles = LoadObjTiles(gUnk_08B5A872, 0xC00);
    PushPaletteEffect(0);
    work->palette = LoadObjPalette(gUnk_08F6DC64, 0x20);
    PopPaletteEffect();
    SetBtlPaletteFadeExcluded(work->palette->index + 16, 0);
    work->backdropSet = 0;
    work->angle = 0;
}

u8 task_hum_hook_moon_1(HookMoonWork* work) {
    work->angle++;
    return 1;
}

void task_hum_hook_moon_2(HookMoonWork* work) {
    s16 x;
    s16 y;
    u16 v;
    u16 t;
    s32 s;

    x = 248 - (gBtlWork->viewX >> 9);
    y = 208 - (gBtlWork->viewY >> 9);
    s = gSineTable[(u8)work->angle];
    y += s >> 5;
    DrawSprite(x + 64, y - 28, gUnk_08B5A854, work->tiles, work->palette, 0, 0xC00, 0xFFFF);
    DrawSprite(x - 144, y, gUnk_08B5A85E, work->tiles, work->palette, 0, 0xC00, 0xFFFE);
    DrawSprite(x - 88, y, gUnk_08B5A85E, work->tiles, work->palette, 0, 0xC00, 0xFFFE);
    DrawSprite(x - 32, y, gUnk_08B5A85E, work->tiles, work->palette, 0, 0xC00, 0xFFFE);
    DrawSprite(x + 24, y, gUnk_08B5A85E, work->tiles, work->palette, 0, 0xC00, 0xFFFE);
    DrawSprite(x + 80, y, gUnk_08B5A85E, work->tiles, work->palette, 0, 0xC00, 0xFFFE);
    v = FadeGetAmount();
    if (v != 0) {
        switch (FadeGetColor()) {
        case 0:
            t = 9 - v;
            if ((s16)t < 0) {
                t = 0;
            }
            SetBackdropColor(0, 0, t);
            break;
        case 0x7FFF:
            t = v + 9;
            if ((s16)t > 31) {
                t = 31;
            }
            SetBackdropColor(v, v, t);
            break;
        case 31:
            SetBackdropColor(v, 0, 9);
            break;
        case 0x7C00:
            t = v + 9;
            if ((s16)t > 31) {
                t = 31;
            }
            SetBackdropColor(0, 0, t);
            break;
        case 0x3E0:
            SetBackdropColor(0, v, 9);
            break;
        }
        work->backdropSet = 1;
    } else if (work->backdropSet != 0) {
        SetBackdropColor(0, 0, 9);
        work->backdropSet = v;
    }
}

void task_hum_hook_moon_3(HookMoonWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_hum_hook_bomb_0(HookBombWork* work, VixenNdlArgs* args) {
    if (args->unk_12 != 0) {
        work->facingLeft = 1;
    } else {
        work->facingLeft = 0;
    }
    work->palette = LoadObjPalette(gPBakudanPalette, 0x20);
    work->tiles = AllocObjTiles(0x280, gPBakudanTiles);
    AnimInit(&work->anim, gPBakudanAnims, gPBakudanFrames);
    AnimStart(&work->anim, 0, 1);
    work->x = args->x;
    work->y = args->y;
    work->z = args->z;
    work->variant = args->unk_14;
    work->timer = 0;
    work->bounceCount = 0;
    work->speed = GetRandom() % 0x201 + 0x14C;
    work->vz = -(GetRandom() % 0x201 + 0x100);

    switch (work->variant) {
    case 0:
        work->angle = GetAngle(work->x, work->y,
            gBtlWork->targetX, gBtlWork->targetY);
        work->maxBounces = GetRandom() % 3 + 1;
        work->state = 0;
        break;
    case 2:
        work->angle = GetAngle(work->x, work->y,
            gBtlWork->targetX, gBtlWork->targetY);
        work->maxBounces = 0;
        work->state = 1;
        break;
    case 1:
    default:
        work->angle = GetRandom();
        work->maxBounces = GetRandom() % 5 + 4;
        work->state = 0;
        break;
    }
    work->tiles2 = LoadObjTiles(gUnk_08B22CE4, 0x200);
    work->palette2 = LoadObjPalette(gBStatesPalette, 0x20);
    work->visible = 1;
}

u8 task_hum_hook_bomb_1(HookBombWork* work) {
    if ((gBtlWork->flags & 0x40) == 0) {
        return 0;
    }

    switch (work->state) {
    case 0:
        work->x += gSineTable[work->angle] * work->speed >> 8;
        work->y += -gSineTable[work->angle + 64] * work->speed >> 8;
        work->z += work->vz;
        work->vz += 64;

        if (work->z > 0) {
            work->z = 0;

            if (work->bounceCount >= work->maxBounces) {
                work->timer = 0;
                work->state = 1;
                break;
            }
            work->vz = -(GetRandom() % 0x301 + 0x200);

            if (work->variant == 0) {
                work->angle = GetAngle(work->x, work->y,
                    gBtlWork->targetX, gBtlWork->targetY);
            } else {
                work->angle = GetRandom();
            }
            work->bounceCount++;
        }

        if (TestAttackBox(work->x, work->y, work->z, 2, 2, 2)) {
            work->timer = 0;
            work->state = 1;
            break;
        }
        work->timer++;
        break;
    default:
        if (work->timer == 0) {
            AnimStart(&work->anim, 1, 0);
        }

        if (work->timer <= 17) {
            work->x += gSineTable[work->angle] * work->speed >> 8;
            work->y += -gSineTable[work->angle + 64] * work->speed >> 8;
            work->z += work->vz;
            work->vz += 64;

            if (work->z > 0) {
                work->z = 0;
                work->vz = -(GetRandom() % 0x301 + 0x200);
                work->angle = GetAngle(work->x, work->y,
                    gBtlWork->targetX, gBtlWork->targetY);
            }
        } else if (work->timer == 18) {
            MakeOpponentsHittable();
            BgFxStartExplosion(work->x, work->y, work->z);
            work->visible = 0;
        } else if (work->timer > 18) {
            if (ApplyAttackBox(0x117, work->x, work->y, work->z, 24, 24, 24)) {
                m4aSongNumStart(SONG_BTL_BW_PACHIN);
            }
        }

        if (work->timer > 17 && BgFxIsActive() == 0) {
            return 0;
        }
        work->timer++;
        break;
    }
    if (ClampBattlePosition(&work->x, &work->y, 0, 0)) {
        work->angle = (u8)(work->angle + 118) + GetRandom() % 21;
    }
    AnimUpdate(&work->anim);
    return 1;
}

void task_hum_hook_bomb_2(HookBombWork* work) {
    void* gfx;
    u16 attr;
    s16 x;
    s16 y;

    if (work->visible == 0) {
        return;
    }
    gfx = AnimGetGfx(&work->anim);
    attr = GetBattleSpritePriorityFlags(work->y);

    if (work->facingLeft == 0) {
        attr |= 1;
    }
    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gfx, work->tiles, work->palette, 0, attr,
        -0x1004 - ((work->y + 0x800) >> 8) * 4);
    WorldToScreen(&x, &y, work->x, work->y, 0);
    DrawSprite(x, y, gUnk_08B22CBC, work->tiles2, work->palette2, 0, attr, 0xFFF0);
}

void task_hum_hook_bomb_3(HookBombWork* work) {
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette2);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void AnsemHover(HumWork* work, s32 a) {
    BtlObj* act = &work->actor;
    s32 t;

    if (a != 0) {
        t = a + gSineTable[gFrameCounter * 4 % 256] * 8;
        work->vz = 0;
        act->z += (t - act->z) >> 4;
    }
}

void AnsemPlaceSub(AnsemWork* work) {
    BtlObj* act = &work->base.actor;

    if (act->flags & 4) {
        work->subOffsetX += (0x1800 - work->subOffsetX) >> 3;
    } else {
        work->subOffsetX += (-0x1800 - work->subOffsetX) >> 3;
    }
    work->subOffsetZ += (-0x1200 - work->subOffsetZ) >> 3;
    work->sub.x = act->x + work->subOffsetX;
    work->sub.y = act->y;
    work->sub.z = act->z + work->subOffsetZ;
}

void task_hum_ansem_0(AnsemWork* work) {
    HumInit(&work->base, &gHumAnsemDef);
    HumSubInit(&work->base, &work->sub, &gHumAnsemSubDef);
    work->hoverZ = -0xC00;
    work->subOffsetX = 0;
    work->base.boundsMargin = -50;
    work->base.stockMoves = gHumAnsemStockMovesA;
}

u8 task_hum_ansem_1(AnsemWork* work) {
    AnsemWork* w;
    BtlObj* act;
    s32 x;
    s32 y;
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &x, &y, 0);

    switch (_0800E434(&work->base)) {
    case 5:
        work->base.stateTimer = 0;
        act->flags &= ~0x100008000;
        MakeOpponentsHittable();

        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
        case 38:
            work->base.state = 20;
            break;
        case 37:
        case 39:
            work->base.state = 25;
            break;
        case 0xFADEB7A3:
            work->base.state = 26;
            work->repeatCount = 0;
            break;
        case 0xFA3EB7A3:
            work->base.state = 21;
            work->repeatCount = 0;
            break;
        }
        break;
    case 4:
        act->flags &= ~0x100008000;
        work->sub.flags &= ~5;
        break;
    }

    if (gBtlWork->battleId == 166) {
        HumChooseCardAction(&work->base, 30, 80, 80, 24);
    } else if (HumChooseCardAction(&work->base, 2, 80, 80, 24)) {
        if (GetRandom() % 2) {
            work->base.stockMoves = gHumAnsemStockMovesA;
        } else {
            work->base.stockMoves = gHumAnsemStockMovesB;
        }
    }

    switch (work->base.state) {
    case 12:
    case 18:
        AnimChangeWithDef(gHumAnsemAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        AnimChangeWithDef(gHumAnsemBackAnimDefs, &w->base.sub->anim, 0, 1, w->base.sub->tiles);
        break;
    case 17:
        AnimChangeWithDef(gHumAnsemAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        AnimChangeWithDef(gHumAnsemBackAnimDefs, &w->base.sub->anim, 0, 1, w->base.sub->tiles);
        w->hoverZ = -0x5000;
        break;
    case 0:
        AnimChangeWithDef(gHumAnsemAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        AnimChangeWithDef(gHumAnsemBackAnimDefs, &w->base.sub->anim, 0, 1, w->base.sub->tiles);
        w->hoverZ = -0xC00;

        if (func_08081828()) {
            break;
        }

        if (gBtlWork->battleId == 177) {
            if ((u16)(GetRandom() % 15) == 0) {
                if (gBtlWork->flags & 0x20000000) {
                    work->base.state = 29;
                    work->base.stateTimer = 0;
                    break;
                }
            }
        }

        if ((u16)(GetRandom() % 80) == 0) {
            work->base.state = 8;
            work->base.stateTimer = 0;
            break;
        }
        HumFaceTarget(&work->base, 3);
        work->base.stateTimer++;
        break;
    case 8:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAnsemAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
            AnimChangeWithDef(gHumAnsemBackAnimDefs, &w->base.sub->anim, 0, 1, w->base.sub->tiles);
            w->hoverZ = -0xC00;
            work->base.targetY = y;

            if (act->x < x) {
                work->base.targetX = x - 0x7800;
            } else {
                work->base.targetX = x + 0x7800;
            }
        }

        if (gBtlWork->battleId == 177) {
            if ((u16)(GetRandom() % 30) == 0) {
                if (gBtlWork->flags & 0x20000000) {
                    work->base.state = 29;
                    work->base.stateTimer = 0;
                    break;
                }
            }
        }

        if (HumMoveToward(&work->base, work->base.targetX, work->base.targetY, 0x300)) {
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }
        HumFaceTarget(&work->base, 1);
        work->base.stateTimer++;
        break;
    case 1:
    case 3:
    case 9:
    case 11:
    case 14:
        w->hoverZ = 0;
        AnimChangeWithDef(gHumAnsemAnimDefs, &w->base.anim, 1, 0, w->base.tiles);
        AnimChangeWithDef(gHumAnsemBackAnimDefs, &w->base.sub->anim, 1, 0, w->base.sub->tiles);
        break;
    case 2:
        if (gBtlWork->battleId != 177) {
            break;
        }

        if (!(gBtlWork->flags & 0x20000000)) {
            break;
        }

        if (!(GetRandom() % 2)) {
            break;
        }
        work->base.state = 29;
        work->base.stateTimer = 0;
        break;
    case 20:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAnsemAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
            AnimChangeWithDef(gHumAnsemBackAnimDefs, &w->base.sub->anim, 2, 0, w->base.sub->tiles);
            w->hoverZ = -0x800;
            m4aSongNumStart(SONG_VO_AN_ATTACK00);
        }

        if (act->flags & 4) {
            s32 d = act->x - 0x2800;
            act->x = act->x + ((x - d) >> 4);
        } else {
            s32 d = act->x + 0x2800;
            act->x = act->x + ((x - d) >> 4);
        }
        act->y += (y - act->y) >> 4;

        switch (AnimGetFrame(&w->sub.anim)) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (act->flags & 4) {
                act->x -= 0x100;
            } else {
                act->x += 0x100;
            }
            break;
        case 4:
            w->sub.flags |= 1;

            if ((act->flags & 4)
                ? ApplyAttackBox(0x140, act->x - 0x2000, act->y, act->z, 20, 12, 24)
                : ApplyAttackBox(0x140, act->x + 0x2000, act->y, act->z, 20, 12, 24)) {
                m4aSongNumStart(SONG_BTL_MON_HIT06);
            }
            break;
        }

        if (AnimIsFinished(&w->sub.anim)) {
            w->sub.flags &= ~1;
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 21:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAnsemAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
            AnimChangeWithDef(gHumAnsemBackAnimDefs, &w->base.sub->anim, 3, 0, w->base.sub->tiles);
            w->subRiseSpeed = 0;
            FadeStartOut(9, 90);
            m4aSongNumStart(SONG_BTL_AN_STANDENTRY);
            w->hoverZ = -0xC00;
        }

        switch (AnimGetFrame(&w->sub.anim)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            AnsemPlaceSub(w);
            break;
        default:
            w->subRiseSpeed += 25;
            w->sub.z -= w->subRiseSpeed;
            break;
        }

        if (AnimIsFinished(&w->sub.anim)) {
            work->base.state = 22;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 22:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAnsemAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
            AnimChangeWithDef(gHumAnsemBackAnimDefs, &w->base.sub->anim, 5, 0, w->base.sub->tiles);
        }
        w->subRiseSpeed += 25;
        w->sub.z -= w->subRiseSpeed;

        if (w->sub.z < -0x12C00) {
            work->base.state = 23;
            work->base.stateTimer = 0;
            break;
        }
        work->base.stateTimer++;
        break;
    case 23:
        if ((s16)work->base.stateTimer == 0) {
            AnimReset(&w->sub.anim);
            AnimChangeWithDef(gHumAnsemAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
            AnimChangeWithDef(gHumAnsemBackAnimDefs, &w->base.sub->anim, 4, 0, w->base.sub->tiles);
            w->subRiseSpeed = 0x800;
            w->sub.x = x + (d = ((u16)(GetRandom() % 65) << 8) - 0x2000);
            w->sub.y = y;
            w->sub.z = 0;
            w->sub.flags |= 4;
            m4aSongNumStart(SONG_EF_AN_STANDUP);
        }

        switch (AnimGetFrame(&w->sub.anim)) {
        case 5:
            if (w->sub.anim.timer == 4) {
                m4aSongNumStart(SONG_EF_BOSS_DEADL);
            }
            break;
        case 6:
            w->subRiseSpeed += 25;
            w->sub.z -= w->subRiseSpeed;
            break;
        }

        if ((s16)((s16)work->base.stateTimer % 10) == 0) {
            MakeOpponentsHittable();
        }

        switch (AnimGetFrame(&w->sub.anim)) {
        case 2:
        case 3:
            if (ApplyAttackBox(0x141, w->sub.x, w->sub.y,
                    w->sub.z - 0x800, 20, 16, 8)) {
                m4aSongNumStart(SONG_BTL_MON_HIT06);
            }
            break;
        case 4:
            if (ApplyAttackBox(0x141, w->sub.x, w->sub.y,
                    w->sub.z - 0x1000, 20, 16, 16)) {
                m4aSongNumStart(SONG_BTL_MON_HIT00);
            }
            break;
        case 5:
            if (ApplyAttackBox(0x141, w->sub.x, w->sub.y,
                    w->sub.z - 0x2000, 20, 16, 32)) {
                m4aSongNumStart(SONG_BTL_MON_HIT00);
            }
            break;
        case 6:
            if (ApplyAttackBox(0x141, w->sub.x, w->sub.y,
                    w->sub.z - 0x3000, 20, 16, 48)) {
                m4aSongNumStart(SONG_BTL_MON_HIT00);
            }
            break;
        }

        if (w->sub.z < -0x12C00) {
            w->sub.flags &= ~4;
            work->base.stateTimer = 0;

            if (w->repeatCount > 6) {
                work->base.state = 24;
                break;
            }
            work->base.state = 23;
            w->repeatCount++;
            break;
        }
        work->base.stateTimer++;
        break;
    case 24:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAnsemBackAnimDefs, &w->base.sub->anim, 0, 1, w->base.sub->tiles);
            w->steps = 30;
        }

        if (act->flags & 4) {
            ApproachValueHalfSteps(&w->sub.x, act->x + 0x1800, w->steps);
        } else {
            ApproachValueHalfSteps(&w->sub.x, act->x - 0x1800, w->steps);
        }
        ApproachValueHalfSteps(&w->sub.y, act->y, w->steps);
        ApproachValueHalfSteps(&w->sub.z, act->z, w->steps);
        w->steps--;

        if (w->steps <= 0) {
            FadeStartIn(0, 30);
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 29:
        if ((s16)work->base.stateTimer == 0) {
            AnimReset(&w->sub.anim);
            AnimChangeWithDef(gHumAnsemBackAnimDefs, &w->base.sub->anim, 7, 0, w->base.sub->tiles);
            w->sub.flags |= 1;
            act->originX = act->x;
            act->flags |= 0x200;
        }
        HumFaceTarget(&work->base, 1);

        if (AnimGetFrame(&w->sub.anim) != 0) {
            act->flags |= 0x100008000;

            if (act->flags & 4) {
                s32 d = act->x - 0x1000;
                act->x = act->x + ((act->originX - d) >> 2);
            } else {
                s32 d = act->x + 0x1000;
                act->x = act->x + ((act->originX - d) >> 2);
            }
            w->subOffsetX += (0 - w->subOffsetX) >> 2;
            w->subOffsetZ += (0 - w->subOffsetZ) >> 2;
            w->sub.x = act->x + w->subOffsetX;
            w->sub.y = act->y;
            w->sub.z = act->z + w->subOffsetZ;
        }

        if ((s16)work->base.stateTimer == 25) {
            act->flags &= ~0x200;
        }

        if ((s16)work->base.stateTimer > 50) {
            w->sub.flags &= ~1;
            act->flags &= ~0x100008000;
            work->base.stateTimer = 0;
            work->base.state = 0;
            break;
        }
        work->base.stateTimer++;
        break;
    case 26:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAnsemAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            AnimChangeWithDef(gHumAnsemBackAnimDefs, &w->base.sub->anim, 7, 0, w->base.sub->tiles);
            w->hoverZ = -0xC00;
            m4aSongNumStart(SONG_VO_AN_ATTACK01);
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 27;
            break;
        }
        work->base.stateTimer++;
        break;
    case 27:
        if ((s16)work->base.stateTimer == 0) {
            if (act->x <= 0xFFFF) {
                work->base.targetX = (gBtlWork->xMax - 48) << 8;
                act->flags &= ~4;
            } else {
                work->base.targetX = (gBtlWork->xMin + 48) << 8;
                act->flags |= 4;
            }
            work->base.targetY = y;
            AnimReset(&work->base.anim);
            AnimReset(&w->sub.anim);
            AnimChangeWithDef(gHumAnsemAnimDefs, &w->base.anim, 5, 1, w->base.tiles);
            AnimChangeWithDef(gHumAnsemBackAnimDefs, &w->base.sub->anim, 8, 1, w->base.sub->tiles);
            w->hoverZ = -0xC00;
            w->steps = 40;
            func_080169A0(w->sub.x, w->sub.y,
                w->sub.z - 0x2100, act->flags & 4);
        }
        a = w->sub.x;
        b = w->sub.y;
        c = w->sub.z;

        if (w->steps > 0) {
            ApproachValue(&act->x, work->base.targetX, w->steps);
            ApproachValueHalfSteps(&act->y, work->base.targetY, w->steps);
        }
        w->steps--;

        if ((s16)work->base.stateTimer > 5) {
            w->sub.flags |= 1;

            if (act->flags & 4) {
                w->subOffsetX += (-0x2200 - w->subOffsetX) >> 3;
            } else {
                w->subOffsetX += (0x2200 - w->subOffsetX) >> 3;
            }
            w->subOffsetZ += (0 - w->subOffsetZ) >> 3;
            w->sub.x = act->x + w->subOffsetX;
            w->sub.y = act->y;
            w->sub.z = act->z + w->subOffsetZ;
        } else {
            AnsemPlaceSub(w);
        }

        if (ApplyAttackBox(0x143, w->sub.x, w->sub.y,
                w->sub.z, 32, 16, 32)) {
            m4aSongNumStart(SONG_BTL_MON_HIT02);
        }
        BgFxAddPosition(w->sub.x - a, w->sub.y - b, w->sub.z - c);

        if (w->steps <= 0) {
            w->sub.flags &= ~1;
            work->base.stateTimer = 0;

            if (w->repeatCount > 3) {
                work->base.state = 28;
                break;
            }
            work->base.state = 27;
            w->repeatCount++;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 28:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAnsemAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
            AnimChangeWithDef(gHumAnsemBackAnimDefs, &w->base.sub->anim, 9, 0, w->base.sub->tiles);
            w->hoverZ = -0xC00;
        }

        if (!AnimIsFinished(&work->base.anim)) {
            break;
        }
        ClearBtlObjActionFlags(act);
        work->base.state = 0;
        work->base.stateTimer = 0;
        break;
    case 25:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAnsemAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
            AnimChangeWithDef(gHumAnsemBackAnimDefs, &w->base.sub->anim, 6, 0, w->base.sub->tiles);
            FadeToAmount(0, gBtlWork->fadeAmount, 8);
            w->hoverZ = -0xC00;
        }

        if ((s16)work->base.stateTimer == 20) {
            if (act->flags & 4) {
                BgFxStartAnsemWave(act->x, act->y, 0, 1, 0x142);
            } else {
                BgFxStartAnsemWave(act->x, act->y, 0, 0, 0x142);
            }
        }

        switch (AnimGetFrame(&w->sub.anim)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            AnsemPlaceSub(w);
            break;
        case 5:
            if (w->sub.anim.timer == 0) {
                w->steps = 8;
            }

            if (w->steps > 0) {
                ApproachValueHalfSteps(&w->sub.z, act->z - 0x3000, w->steps);
                w->steps--;
            }
            break;
        case 6:
            if (w->sub.anim.timer == 0) {
                w->steps = 8;
            }

            if (w->steps > 0) {
                ApproachValueHalfSteps(&w->sub.z, act->z - 0x1000, w->steps);
                w->steps--;
            }
            break;
        }

        if (AnimIsFinished(&w->sub.anim)) {
            if (BgFxIsActive() == 0) {
                ClearBtlObjActionFlags(act);
                FadeToOriginal(0, 8);
                work->base.state = 0;
                work->base.stateTimer = 0;
                break;
            }
        }
        work->base.stateTimer++;
        break;
    }

    if (!(act->flags & 0x2000) && act->badStatus != 2) {
        AnsemHover(&work->base, w->hoverZ);
    }

    switch (work->base.state) {
    case 21:
    case 22:
    case 23:
    case 25:
    case 27:
    case 29:
        break;
    default:
        AnsemPlaceSub(w);
        break;
    }
    return HumUpdate(&work->base);
}

void task_hum_ansem_2(HumWork* work) {
    HumDraw(work);
}

void task_hum_ansem_3(HumWork* work) {
    HumReleaseResources(work);
}

void HadesHover(HumWork* work, s32 a) {
    BtlObj* act = &work->actor;
    s32 t;

    if (a != 0) {
        t = a + gSineTable[gFrameCounter * 4 % 256] * 4;
        work->vz = 0;
        act->z += (t - act->z) >> 4;
    }
}

void HadesEndAttack(HadesWork* work) {
    BtlObj* act = &work->base.actor;

    if (work->angryAttacks > 2) {
        LoadObjPaletteBank(work->base.palette->index, gHadesPalette);
        work->base.paletteData = gHadesPalette;
        work->flags &= 0xFFFE;
        work->base.stockMoves = gHumHadesStockMoves;
    } else {
        work->angryAttacks++;
    }
    ClearBtlObjActionFlags(act);
}

void task_hum_hades_0(HadesWork* work) {
    HumInit(&work->base, &gHumHadesDef);
    HumSubInit(&work->base, &work->sub, &gHumHadesSubDef);
    work->base.actor.flags |= 0x100000;
    work->base.flags |= 0x40;
    work->flags = 0;
    work->hoverZ = -0xA00;
    work->sub.flags |= 3;
    work->tiles = AllocObjTiles(0x80, gHadesFramespreadHiTiles);
    work->tiles2 = AllocObjTiles(0x280, gHadesFramespreadHiTiles);
    work->tiles3 = AllocObjTiles(0x3A0, gHadesFramespreadHiTiles);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    AnimInit(&work->anim, gHadesFramespreadHiAnims, gHadesFramespreadHiFrames);
    AnimStart(&work->anim, 2, 1);
    AnimInit(&work->anim2, gHadesFramespreadHiAnims, gHadesFramespreadHiFrames);
    AnimStart(&work->anim2, 1, 1);
    AnimInit(&work->anim3, gHadesFramespreadHiAnims, gHadesFramespreadHiFrames);
    AnimStart(&work->anim3, 0, 1);
    work->base.stockMoves = gHumHadesStockMoves;
}

u8 task_hum_hades_1(HadesWork* work) {
    HadesWork* w;
    BtlObj* act;
    s32 x;
    s32 y;
    s32 z;
    s16 p;
    s16 q;
    s16 r;
    s16 s;
    u16 frame;
    u8 t;
    u8 ret;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &x, &y, &z);

    switch (_0800E434(&work->base)) {
    case 5:
        work->base.stateTimer = 0;

        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
        case 38:
            if (w->flags & 1) {
                work->base.state = 21;
            } else {
                work->base.state = 20;
            }
            break;
        case 37:
        case 39:
            if (w->flags & 1) {
                work->base.state = 24;
            } else {
                work->base.state = 20;
            }
            break;
        case 0xEE5B96E5:
        case 0xEEFB96EF:
            if (w->flags & 1) {
                work->base.state = 22;
            } else {
                work->base.state = 19;
            }
            break;
        }
        break;
    case 4:
        work->sub.flags |= 2;
        work->flags &= 0xFFFD;
        break;
    }

    if (w->flags & 1) {
        HumChooseCardAction(&work->base, 3, 40, 40, 24);
    } else {
        HumChooseCardAction(&work->base, 15, 40, 40, 24);
    }
    w->hoverZ = -0xA00;

    switch (work->base.state) {
    case 12:
    case 17:
    case 18:
        AnimChangeWithDef(gHumHadesAnimDefs, &w->base.anim, 1, 1, w->base.tiles);
        break;
    case 0:
    case 8:
        t = -((u8)work->base.stateTimer * 2);
        work->base.targetX = x + gSineTable[t] * 90;
        work->base.targetY = y + (-gSineTable[t + 64]) * 45;

        if (w->flags & 1) {
            HumMoveToward(&work->base, work->base.targetX, work->base.targetY, 0x333);
        } else {
            HumMoveToward(&work->base, work->base.targetX, work->base.targetY, 0x140);
        }
        HumFaceTarget(&work->base, 5);

        if (AnimIsFinished(&work->base.anim)) {
            if (act->flags & 4) {
                if ((s32)work->base.targetX < act->x) {
                    AnimChangeWithDef(gHumHadesAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
                } else {
                    AnimChangeWithDef(gHumHadesAnimDefs, &w->base.anim, 1, 1, w->base.tiles);
                }
            } else {
                if ((s32)work->base.targetX < act->x) {
                    AnimChangeWithDef(gHumHadesAnimDefs, &w->base.anim, 1, 1, w->base.tiles);
                } else {
                    AnimChangeWithDef(gHumHadesAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
                }
            }
        }
        work->base.stateTimer++;
        break;
    case 1:
    case 3:
    case 9:
    case 11:
    case 14:
        w->hoverZ = 0;
        AnimChangeWithDef(gHumHadesAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        break;
    case 19:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHadesAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
            AnimReset(&w->sub.anim);
            AnimChangeWithDef(gHumHadesEffectAnimDefs, &w->base.sub->anim, 0, 0, w->base.sub->tiles);
            w->sub.flags &= 0xFFFD;
        }
        w->sub.x = act->x;
        w->sub.y = act->y;
        w->sub.z = act->z;

        if (AnimGetFrame(&w->sub.anim) == 1 && w->sub.anim.timer == 0) {
            m4aSongNumStart(SONG_BTL_HA_IKARI);
        }

        if (AnimGetFrame(&work->base.anim) == 5 && work->base.anim.timer == 0) {
            LoadObjPaletteBank(work->base.palette->index, gHadesAngryPalette);
            work->base.paletteData = gHadesAngryPalette;
            w->flags |= 1;
            work->base.stockMoves = gHumHadesAngryStockMoves;
            w->angryAttacks = 0;
        }

        if (AnimIsFinished(&work->base.anim)) {
            w->sub.flags |= 2;
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 22:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHadesAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            AnimReset(&w->sub.anim);
            AnimChangeWithDef(gHumHadesEffectAnimDefs, &w->base.sub->anim, 2, 0, w->base.sub->tiles);
            w->sub.flags &= 0xFFFD;
            m4aSongNumStart(SONG_VO_HA_ATTACK00);
            m4aSongNumStart(SONG_BTL_HA_FIREENTRY);
        }
        w->sub.x = act->x;
        w->sub.y = act->y;
        w->sub.z = act->z;

        if (AnimIsFinished(&w->sub.anim)) {
            work->base.state = 23;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 23:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHadesEffectAnimDefs, &w->base.sub->anim, 3, 1, w->base.sub->tiles);

            if (act->flags & 4) {
                w->sub.x -= 0xA00;
            } else {
                w->sub.x += 0xA00;
            }
            w->sub.z -= 0x4E00;
            w->subVz = 0;
            m4aSongNumStart(SONG_BTL_HA_BALLSHOT);
        }

        if (act->flags & 4) {
            w->sub.x -= 0x700;
        } else {
            w->sub.x += 0x700;
        }
        w->sub.y += (y - w->sub.y) >> 4;
        w->sub.z += w->subVz;
        w->subVz += 89;

        if (w->sub.z + 0xF00 > 0) {
            w->sub.z = -0xF00;
            w->subVz = -(w->subVz >> 1);
        }

        if (ApplyAttackBox(0x120, w->sub.x, w->sub.y, w->sub.z, 16, 16, 16)) {
            m4aSongNumStart(SONG_EF_TARU_BOMB);
        }

        if (w->sub.x < (gBtlWork->xMin - 32) << 8 || w->sub.x > (gBtlWork->xMax + 32) << 8) {
            w->sub.flags |= 2;
            HadesEndAttack(w);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 24:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHadesAnimDefs, &w->base.anim, 7, 0, w->base.tiles);
#ifdef VERSION_EU
            if (act->btl->hcEffect == 8) {
                act->btl->hcEffectCount--;
            }
#endif
        }

        if (AnimGetFrame(&work->base.anim) == 4) {
            work->base.state = 25;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 25:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHadesAnimDefs, &w->base.anim, 8, 1, w->base.tiles);
            w->scale = 10;
            work->base.steps = 8;
            w->flags = (w->flags & 0xFFFB) | 2;

            if (act->flags & 4) {
                w->sub2[0].x = w->sub2[0].x2 = w->sub2[0].x3 = act->x - 0x2800;
                w->sub2[0].y = w->sub2[0].y2 = w->sub2[0].y3 = act->y;
                w->sub2[0].z = w->sub2[0].z2 = w->sub2[0].z3 = act->z - 0x3600;
                w->sub2[1].x = w->sub2[1].x2 = w->sub2[1].x3 = act->x + 0x600;
                w->sub2[1].y = w->sub2[1].y2 = w->sub2[1].y3 = act->y;
                w->sub2[1].z = w->sub2[1].z2 = w->sub2[1].z3 = act->z - 0x3400;
            } else {
                w->sub2[0].x = w->sub2[0].x2 = w->sub2[0].x3 = act->x + 0x2800;
                w->sub2[0].y = w->sub2[0].y2 = w->sub2[0].y3 = act->y;
                w->sub2[0].z = w->sub2[0].z2 = w->sub2[0].z3 = act->z - 0x3600;
                w->sub2[1].x = w->sub2[1].x2 = w->sub2[1].x3 = act->x - 0x600;
                w->sub2[1].y = w->sub2[1].y2 = w->sub2[1].y3 = act->y;
                w->sub2[1].z = w->sub2[1].z2 = w->sub2[1].z3 = act->z - 0x3400;
            }
            m4aSongNumStart(SONG_BTL_LEC_ROCKB1);
        }
        w->hoverZ = 0;

        if ((s16)work->base.steps > 0) {
            if (w->flags & 4) {
                ApproachValue(&w->scale, 10, (u16)work->base.steps);
            } else {
                ApproachValue(&w->scale, 0x100, (u16)work->base.steps);
            }
            work->base.steps--;
        }

        if ((s16)work->base.stateTimer == 180) {
            w->flags |= 4;
            work->base.steps = 8;
        }
        HumFaceTarget(&work->base, 8);
        act->y += (y - act->y) >> 4;
        act->x += gSineTable[(u8)work->base.stateTimer];
        w->sub2[0].groundY = act->y;
        w->sub2[1].groundY = act->y;

        if (w->flags & 2) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                p = 44;
                q = -50;
                r = 2;
                s = -44;
                break;
            case 3:
                p = 44;
                q = -39;
                r = 33;
                s = -32;
                break;
            case 4:
                p = 46;
                q = -42;
                r = 21;
                s = -32;
                break;
            case 5:
                p = 46;
                q = -50;
                r = -3;
                s = -30;
                break;
            case 6:
                p = 48;
                q = -43;
                r = -2;
                s = -30;
                break;
            case 7:
                p = 45;
                q = -43;
                r = 2;
                s = -31;
                break;
            case 8:
                p = 42;
                q = -48;
                r = 19;
                s = -34;
                break;
            case 9:
            default:
                p = 33;
                q = -49;
                r = 20;
                s = -41;
                break;
            }

            if (act->flags & 4) {
                w->sub2[0].x += (act->x - ((s16)p << 8) - w->sub2[0].x) >> 1;
                w->sub2[1].x += (act->x - ((s16)r << 8) - w->sub2[1].x) >> 1;
            } else {
                w->sub2[0].x += (act->x + ((s16)p << 8) - w->sub2[0].x) >> 1;
                w->sub2[1].x += (act->x + ((s16)r << 8) - w->sub2[1].x) >> 1;
            }
            w->sub2[0].y += (act->y - w->sub2[0].y) >> 1;
            w->sub2[1].y += (act->y - w->sub2[1].y) >> 1;
            w->sub2[0].z += (act->z + ((s16)q << 8) - w->sub2[0].z) >> 1;
            w->sub2[1].z += (act->z + ((s16)s << 8) - w->sub2[1].z) >> 1;
            {
                s32 v = w->scale;
                p = (s16)p + (v * 14 >> 8);
                q = (s16)q + (v * 10 >> 8);
                r = (s16)r + (v * 8 >> 8);
                s = (s16)s + (v * 12 >> 8);
            }

            if (act->flags & 4) {
                w->sub2[0].x2 += (act->x - ((s16)p << 8) - w->sub2[0].x2) >> 3;
                w->sub2[1].x2 += (act->x - ((s16)r << 8) - w->sub2[1].x2) >> 3;
            } else {
                w->sub2[0].x2 += (act->x + ((s16)p << 8) - w->sub2[0].x2) >> 3;
                w->sub2[1].x2 += (act->x + ((s16)r << 8) - w->sub2[1].x2) >> 3;
            }
            w->sub2[0].y2 += (act->y - w->sub2[0].y2) >> 3;
            w->sub2[1].y2 += (act->y - w->sub2[1].y2) >> 3;
            w->sub2[0].z2 += (act->z + ((s16)q << 8) - w->sub2[0].z2) >> 3;
            w->sub2[1].z2 += (act->z + ((s16)s << 8) - w->sub2[1].z2) >> 3;
            {
                s32 v = w->scale;
                p = (s16)p + (v * 24 >> 8);
                q = (s16)q + (v * 20 >> 8);
                r = (s16)r + (v * 10 >> 8);
                s = (s16)s + (v * 20 >> 8);
            }

            if (act->flags & 4) {
                w->sub2[0].x3 += (act->x - ((s16)p << 8) - w->sub2[0].x3) >> 4;
                w->sub2[1].x3 += (act->x - ((s16)r << 8) - w->sub2[1].x3) >> 4;
            } else {
                w->sub2[0].x3 += (act->x + ((s16)p << 8) - w->sub2[0].x3) >> 4;
                w->sub2[1].x3 += (act->x + ((s16)r << 8) - w->sub2[1].x3) >> 4;
            }
            w->sub2[0].y3 += (act->y - w->sub2[0].y3) >> 4;
            w->sub2[1].y3 += (act->y - w->sub2[1].y3) >> 4;
            w->sub2[0].z3 += (act->z + ((s16)q << 8) - w->sub2[0].z3) >> 4;
            w->sub2[1].z3 += (act->z + ((s16)s << 8) - w->sub2[1].z3) >> 4;
        }

#ifndef VERSION_EU
        if (act->btl->hcEffect == 8 && act->hp < act->maxHp >> 1) {
            gBtlWork->damageScale = 0x200;
        }
#endif

        if (w->scale == 0x100) {
            if (ApplyAttackBox(0x121, w->sub2[0].x3, w->sub2[0].groundY, w->sub2[0].z3, 16, 16, 16)) {
                m4aSongNumStart(SONG_EF_FIRE01);
            }

            if (ApplyAttackBox(0x121, w->sub2[1].x3, w->sub2[1].groundY, w->sub2[1].z3, 16, 16, 16)) {
                m4aSongNumStart(SONG_EF_FIRE01);
            }
        }
#ifndef VERSION_EU
        gBtlWork->damageScale = 0;
#endif

        if ((w->flags & 4) && (s16)work->base.steps <= 0) {
            w->flags &= 0xFFFD;
            work->base.state = 26;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 26:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHadesAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 21:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHadesAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            AnimReset(&w->sub.anim);
            AnimChangeWithDef(gHumHadesEffectAnimDefs, &w->base.sub->anim, 1, 0, w->base.sub->tiles);
            w->sub.flags &= 0xFFFD;
#ifdef VERSION_EU
            if (act->btl->hcEffect == 8) {
                act->btl->hcEffectCount--;
            }
#endif
        }
        w->sub.x = act->x;
        w->sub.y = act->y;
        w->sub.z = act->z;

        frame = AnimGetFrame(&w->sub.anim);

        switch (frame) {
        case 2:
        case 3:
        case 4:
#ifndef VERSION_EU
            if (act->btl->hcEffect == 8 && act->hp < act->maxHp >> 1) {
                gBtlWork->damageScale = 0x200;
            }
#endif

            if ((act->flags & 4)
                ? ApplyAttackBox(0x11F, act->x - 0x1E00, act->y, act->z, 30, 16, 60)
                : ApplyAttackBox(0x11F, act->x + 0x1E00, act->y, act->z, 30, 16, 60)) {
                m4aSongNumStart(SONG_EF_FIRE01);
            }
#ifndef VERSION_EU
            gBtlWork->damageScale = 0;
#endif
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            w->sub.flags |= 2;
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 20:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumHadesAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
            AnimReset(&w->sub.anim);
            AnimChangeWithDef(gHumHadesEffectAnimDefs, &w->base.sub->anim, 4, 0, w->base.sub->tiles);
            w->sub.flags &= 0xFFFD;
            w->sub.x = act->x;
            w->sub.y = act->y;
            w->sub.z = act->z;
            m4aSongNumStart(SONG_VO_HA_ATTACK01);
#ifdef VERSION_EU
            if (act->btl->hcEffect == 8) {
                act->btl->hcEffectCount--;
            }
#endif
        }

        switch (AnimGetFrame(&w->sub.anim)) {
        case 1:
            if (w->sub.anim.timer == 0) {
                m4aSongNumStart(SONG_EF_HA_FINGFIRE);
            }
            break;
        case 2:
#ifndef VERSION_EU
            if (act->btl->hcEffect == 8 && act->hp < act->maxHp >> 1) {
                gBtlWork->damageScale = 0x200;
            }
#endif

            if (act->flags & 4) {
                ApplyAttackBox(0x11E, act->x - 0x2000, act->y, act->z, 24, 16, 60);
            } else {
                ApplyAttackBox(0x11E, act->x + 0x2000, act->y, act->z, 24, 16, 60);
            }
#ifndef VERSION_EU
            gBtlWork->damageScale = 0;
#endif
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            w->sub.flags |= 2;
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    }

    if (!(act->flags & 0x2000) && act->badStatus != 2) {
        HadesHover(&work->base, w->hoverZ);
    }

    if (w->flags & 2) {
        AnimUpdate(&w->anim);
        AnimUpdate(&w->anim2);
        AnimUpdate(&w->anim3);
    }
    ret = HumUpdate(&work->base);
    return ret;
}

void task_hum_hades_2(HadesWork* work) {
    BtlObj* act;
    HadesSub* e;
    void* gfx;
    u16 attr;
    s32 sx;
    ObjAffine* affine;
    s16 x;
    s16 y;
    s32 i;

    HumDraw(&work->base);

    if ((work->flags & 2) == 0) {
        return;
    }
    act = &work->base.actor;

    for (i = 0; i < 2; i++) {
        e = &work->sub2[i];
        attr = GetBattleSpritePriorityFlags(e->groundY);

        if (work->scale == 0x100) {
            if ((act->flags & 4) == 0) {
                attr |= 1;
            }
            sx = work->scale;
        } else {
            if ((act->flags & 4) == 0) {
                sx = work->scale;
            } else {
                sx = -work->scale;
            }
        }
        affine = AllocObjAffine(0, sx, work->scale, 0);
        gfx = AnimGetGfx(&work->anim);
        WorldToScreen(&x, &y, e->x, e->y, e->z);
        DrawSprite(x, y, gfx, work->tiles, work->palette, affine, attr,
            -0x1005 - (e->groundY >> 8) * 4);
        gfx = AnimGetGfx(&work->anim2);
        WorldToScreen(&x, &y, e->x2, e->y2, e->z2);
        DrawSprite(x, y, gfx, work->tiles2, work->palette, affine, attr,
            -0x1006 - (e->groundY >> 8) * 4);
        gfx = AnimGetGfx(&work->anim3);
        WorldToScreen(&x, &y, e->x3, e->y3, e->z3);
        DrawSprite(x, y, gfx, work->tiles3, work->palette, affine, attr,
            -0x1007 - (e->groundY >> 8) * 4);
    }
}

void task_hum_hades_3(HadesWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles3);
    ReleaseObjPalette(work->palette);
    HumReleaseResources(&work->base);
}

void MahluxiaJumpOffset(MahluxiaWork* work, s16 a) {
    HumWork* w = &work->base;
    BtlObj* act = &w->actor;
    s32 v;

    GetEnemyTargetPosition(act, &v, 0, 0);

    if (act->flags & 4) {
        w->targetX = act->x - (a << 8);
    } else {
        w->targetX = act->x + (a << 8);
    }
    w->state = 20;
    w->stateTimer = 0;
    work->hoverZ = -0x300;

    if (act->y < v) {
        w->targetY = (gBtlWork->yMin + 16) << 8;
    } else {
        w->targetY = (gBtlWork->yMax - 16) << 8;
    }
}

void MahluxiaSwingTo(MahluxiaWork* work, s32 a, u16 b) {
    work->base.targetX = a;
    work->swingAmplitude = b;
    work->base.state = 19;
    work->base.stateTimer = 0;
}

u8 MahluxiaTryJumpAway(MahluxiaWork* work) {
    s32 v;
    BtlObj* c;

    c = gBtlWork->actor;
    GetEnemyTargetPosition(&work->base.actor, &v, 0, 0);
    HumFaceTarget(&work->base, 1);

    if (HumIsInPlayerReach(&work->base, 0x100, 0x100, 0x100)) {
        if (gBtlWork->flags & 0x8000) {
            MahluxiaJumpOffset(work, -128);
        } else if (GetRandom() & 1) {
            if (c->flags & 4) {
                MahluxiaSwingTo(work, v + 0x2800, 48);
            } else {
                MahluxiaSwingTo(work, v - 0x2800, 48);
            }
        } else {
            MahluxiaJumpOffset(work, -128);
        }
        return 1;
    }
    return 0;
}

void MahluxiaSaveAfterimage(MahluxiaWork* work, RikuSpawn* dst) {
    BtlObj* act = &work->base.actor;

    dst->x = act->x;
    dst->y = act->y;
    dst->z = act->z;

    if (act->flags & 4) {
        dst->flags |= 1;
    } else {
        dst->flags &= 0xFFFE;
    }
    dst->anim = work->base.anim;
    dst->tileSrc = work->base.tiles->src;
    dst->scale = gBtlWork->scale;
}

void MahluxiaDrawAfterimage(MahluxiaWork* work, RikuSpawn* p) {
    BtlObj* act;
    HumSub* sub;
    void* gfx;
    u16 attr;
    s32 sx;
    s32 sy;
    ObjAffine* affine;
    s16 x;
    s16 y;
    u16 pri;

    sub = work->base.sub;
    gfx = AnimGetGfx(&p->anim);
    act = &work->base.actor;

    if (BgFxIsActive() == 0) {
        gBldCnt = (BLDCNT_TGT1_OBJ | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
        SetBlendAlpha(4, 14);
        attr = 0x804;
    } else {
        attr = GetBattleSpritePriorityFlags(act->y);
    }

    if (p->flags & 1) {
        sy = p->scale;
        sx = sy;
    } else if (p->scale == 0x100) {
        sy = p->scale;
        sx = sy;
        attr |= 1;
    } else {
        sx = -gBtlWork->scale;
        sy = gBtlWork->scale;
    }

    if (sy == 0x100 && sx == sy) {
        affine = 0;
    } else if (sy <= 255) {
        affine = AllocObjAffine(0, sx, sy, 0);
    } else {
        affine = AllocObjAffine(0, sx, sy, 1);
    }
    pri = 0xFFF0;
    WorldToScreen(&x, &y, p->x, p->y, p->z);
    SetObjTileSource(sub->tiles, p->tileSrc);
    DrawSprite(x, y, gfx, sub->tiles, work->base.palette, affine, attr, pri);
}

void MahluxiaHover(HumWork* work, s32 a) {
    BtlObj* act;
    s32 t;

    if (a != 0) {
        act = &work->actor;
        t = a + gSineTable[gFrameCounter * 4 % 256] * 3;
        work->vz = 0;
        act->z += (t - act->z) >> 4;
    }
}

void task_hum_mahluxia_0(MahluxiaWork* work) {
    HumInit(&work->base, &gHumMahluxiaDef);
    HumSubInit(&work->base, &work->sub, &gHumMahluxiaSubDef);
    work->flags = 0;
    work->hoverZ = -0x300;
    work->sub.flags |= 3;
    work->unk_1D8 = 0;
    AnimChangeWithDef(gHumMahluxiaAnimDefs, &work->base.anim, 0, 1, work->base.tiles);
    MahluxiaSaveAfterimage(work, &work->spawns[0]);
    work->spawns[1] = work->spawns[0];
    work->spawns[2] = work->spawns[0];
    work->spawns[3] = work->spawns[0];
    work->spawns[4] = work->spawns[0];
    work->spawns[5] = work->spawns[0];
    work->spawns[6] = work->spawns[0];
    work->spawns[7] = work->spawns[0];
    work->spawns[8] = work->spawns[0];
    TaskPoolInit(&work->tasks, 22);
    work->base.stockMoves = gHumMahluxiaStockMovesB;
}

void MahluxiaSpawnFlower(MahluxiaWork* work) {
    BtlObj* act = &work->base.actor;
    VixenNdlArgs args;
    s32 range;

    if (gFrameCounter % 5 == 0) {
        args.x = act->x;
        args.y = act->y;
        args.z = act->z - ((s16)act->centerHeight << 8);
        range = 0x2000;
        args.x += ((GetRandom() % 65) << 8) - range;
        range = 0x1000;
        args.y += ((GetRandom() % 33) << 8) - range;
        args.z += ((GetRandom() % 41) << 8) - range;
        TaskCreate(&work->tasks, &gTaskDescHumMahluxiaFlw, &args);
    }
}

u8 task_hum_mahluxia_1(MahluxiaWork* work) {
    MahluxiaWork* w;
    BtlObj* act;
    s32 x;
    s32 y;
    s32 z;
    u16 n;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &x, &y, &z);
    work->flags &= ~2;

    switch (_0800E434(&work->base)) {
    case 5:
        work->base.stateTimer = 0;
        w->hoverZ = 0;

        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
            work->base.state = 21;
            break;
        case 37:
            work->base.state = 27;
            break;
        case 38:
        case 39:
            work->base.state = 28;
            break;
        case 0xF71D9F71:
            work->base.state = 26;
            break;
        case 0xF7BDC767:
            work->base.state = 22;
            break;
        }
        break;
    case 4:
        w->sub.flags |= 2;
        break;
    }

    if (HumChooseCardAction(&work->base, 4, 40, 40, 24)) {
        if (GetRandom() % 2) {
            work->base.stockMoves = gHumMahluxiaStockMovesB;
        } else {
            work->base.stockMoves = gHumMahluxiaStockMovesA;
        }
    }

    switch (work->base.state) {
    case 12:
    case 18:
        AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        break;
    case 17:
        AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 0, 1, w->base.tiles);

        if (gBtlWork->flags & 0x20000000) {
            if (MahluxiaTryJumpAway(w)) {
                break;
            }
        }

        if (act->x - x >= 0 ? act->x - x <= 0x4FFF : x - act->x <= 0x4FFF) {
            if (x <= 0xFFFF) {
                MahluxiaSwingTo(w, (gBtlWork->xMax - 60) << 8, 48);
            } else {
                MahluxiaSwingTo(w, (gBtlWork->xMin + 60) << 8, 48);
            }
        }
        break;
    case 0:
        AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        w->hoverZ = -0x300;

        if (func_08081828()) {
            break;
        }

        if (act->x - x >= 0 ? act->x - x > 0x2800 : x - act->x > 0x2800) {
            if (GetRandom() % 80 == 0) {
                work->base.state = 8;
                work->base.stateTimer = 0;
                break;
            }
        }

        if (HumIsNearAreaEdge(&work->base, 40)) {
            MahluxiaSwingTo(w, 0x10000, 48);
            break;
        }

        if (gBtlWork->flags & 0x20000000) {
            if (MahluxiaTryJumpAway(w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 8);
        }
        work->base.stateTimer++;
        break;
    case 8:
        AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 1, 1, w->base.tiles);
        work->base.targetX = x;
        work->base.targetY = y;

        if (HumMoveToward(&work->base, work->base.targetX, work->base.targetY, 358)) {
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }

        if (gBtlWork->flags & 0x20000000) {
            if (MahluxiaTryJumpAway(w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 30);
        }
        work->base.stateTimer++;
        break;
    case 1:
        MahluxiaSpawnFlower(w);
    case 3:
    case 9:
    case 11:
    case 14:
        AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        break;
    case 20:
        AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 1, 0, w->base.tiles);
        act->x += ((s32)work->base.targetX - act->x) >> 4;
        act->y += ((s32)work->base.targetY - act->y) >> 4;

        if ((work->base.flags & 1)
                || ((s32)work->base.targetX - act->x >= 0
                    ? (s32)work->base.targetX - act->x <= 0x7FF
                    : act->x - (s32)work->base.targetX <= 0x7FF)) {
            work->base.stateTimer = 0;
            work->base.state = 0;
            break;
        }
        HumFaceTarget(&work->base, 1);
        MahluxiaSpawnFlower(w);
        w->flags |= 2;
        work->base.stateTimer++;
        break;
    case 19:
        if ((s16)work->base.stateTimer == 0) {
            w->steps = 60;
            w->angle = 0;
            w->swingBaseY = act->y;

            if (((gBtlWork->yMin + gBtlWork->yMax) << 7) < act->y) {
                w->flags &= ~1;
            } else {
                w->flags |= 1;
            }
            AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 1, 1, w->base.tiles);
        }

        if ((s16)w->steps != 0) {
            ApproachValueHalfSteps(&act->x, work->base.targetX, w->steps);
            ApproachValueHalfSteps(&w->angle, 128, w->steps);

            if (w->flags & 1) {
                act->y = w->swingBaseY + gSineTable[(u8)w->angle] * w->swingAmplitude;
            } else {
                act->y = w->swingBaseY - gSineTable[(u8)w->angle] * w->swingAmplitude;
            }
            w->steps--;
        }
        MahluxiaSpawnFlower(w);

        if ((s16)w->steps <= 0) {
            work->base.stateTimer = 0;
            work->base.state = 0;
            break;
        }
        HumFaceTarget(&work->base, 3);
        w->flags |= 2;
        work->base.stateTimer++;
        break;
    case 22:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
        }
        w->flags |= 2;

        if (!AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer++;
            break;
        }
        work->base.state = 23;
        work->base.stateTimer = 0;
        break;
    case 23:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 5, 1, w->base.tiles);
        }
        act->y += (y - act->y) >> 2;
        n = (u16)work->base.stateTimer;

        if ((s16)n > 60) {
            work->base.state = 24;
            work->base.stateTimer = 0;
            break;
        }
        work->base.stateTimer = n + 1;
        break;
    case 24:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
        }
        w->flags |= 2;

        if (!AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer++;
            break;
        }
        work->base.state = 25;
        work->base.stateTimer = 0;
        break;
    case 25:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 7, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_MARL_ATTACK00);
        }
        w->flags |= 2;

        switch (AnimGetFrame(&work->base.anim)) {
        case 1:
            if (work->base.anim.timer == 0) {
                HumFaceTarget(&work->base, 1);
                BgFxStartKama(act->x, act->y, act->z, x - act->x, 316);
            }
            break;
        case 2:
            if (work->base.anim.timer == 0) {
                if ((act->flags & 4)
                    ? ApplyAttackBox(0x13B, act->x - 0x2800, act->y, act->z, 40, 12, 64)
                    : ApplyAttackBox(0x13B, act->x + 0x2800, act->y, act->z, 40, 12, 64)) {
                    m4aSongNumStart(SONG_EF_KU_ATT02);
                }
            }
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            if (BgFxIsActive() == 0) {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
                work->base.stateTimer = 0;
                break;
            }
        }
        work->base.stateTimer++;
        break;
    case 28:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 10, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_MARL_ATTACK03);
        }
        w->flags |= 2;

        if (act->flags & 4) {
            act->x = act->x - 0x105;
        } else {
            act->x = act->x + 0x105;
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 29;
            work->base.stateTimer = 0;
            break;
        }
        work->base.stateTimer++;
        break;
    case 29:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 11, 0, w->base.tiles);
            FadeStartIn(2, 20);
            m4aSongNumStart(SONG_SND_706);
            FadeLock();
            gBtlWork->hitStop = 20;
            w->flags |= 2;

            if (act->flags & 4) {
                act->x -= 0x5000;
                ApplyAttackBox(0x13F, act->x + 0x2800, act->y, 0, 40, 16, 40);
            } else {
                act->x += 0x5000;
                ApplyAttackBox(0x13F, act->x - 0x2800, act->y, 0, 40, 16, 40);
            }
        }
        n = (u16)work->base.stateTimer;

        if ((s16)n > 60) {
            work->base.state = 30;
            work->base.stateTimer = 0;
            break;
        }
        work->base.stateTimer = n + 1;
        break;
    case 30:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
        }
        w->flags |= 2;

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }
        work->base.stateTimer++;
        break;
    case 26:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 8, 0, w->base.tiles);
            w->flags &= ~4;
            m4aSongNumStart(SONG_VO_MARL_ATTACK01);
        }
        w->flags |= 2;

        if (AnimGetFrame(&work->base.anim) == 4) {
            if (work->base.anim.timer == 0) {
                BgFxStartHanabira(act->x, act->y, act->z - 0x4D00, 318);
                w->flags |= 4;
            }
        }

        if (w->flags & 4) {
            MahluxiaSpawnFlower(w);
        }

        if (AnimIsFinished(&work->base.anim)) {
            if (BgFxIsActive() == 0) {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
                work->base.stateTimer = 0;
                break;
            }
        }
        work->base.stateTimer++;
        break;
    case 27:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_MARL_ATTACK03);
        }
        w->flags |= 2;

        switch (AnimGetFrame(&work->base.anim)) {
        case 4:
            if (work->base.anim.timer == 0) {
                m4aSongNumStart(SONG_BTL_MARL_STAMP);

                if (act->flags & 4) {
                    BgFxStartMahluxiaGround(act->x + 0x1700, act->y, 0, 0x13D);
                } else {
                    BgFxStartMahluxiaGround(act->x - 0x1700, act->y, 0, 0x13D);
                }
            }
            break;
        case 5:
            if (work->base.anim.timer == 0) {
                m4aSongNumStart(SONG_EF_MARL_GROUND);
            }
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            if (BgFxIsActive() == 0) {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
                work->base.stateTimer = 0;
                break;
            }
        }
        work->base.stateTimer++;
        break;
    case 21:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumMahluxiaAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
            w->flags &= ~4;

            if (act->flags & 4) {
                w->sub.x = act->x - 0x4600;
            } else {
                w->sub.x = act->x + 0x4600;
            }
            w->sub.z = 0;
            w->subSpeed = 0;
            m4aSongNumStart(SONG_VO_MARL_ATTACK03);
        }

        switch (AnimGetFrame(&work->base.anim)) {
        case 0:
        case 1:
        case 2:
        case 3:
            w->flags |= 2;
            act->y += (y - act->y) >> 2;
            w->sub.y = act->y;
            break;
        case 4:
            if (work->base.anim.timer == 0) {
                AnimReset(&w->sub.anim);
                AnimChangeWithDef(&gHumMahluxiaEffAnimDef, &w->base.sub->anim, 0, 0, w->base.sub->tiles);
                w->flags |= 4;
                w->sub.flags &= ~2;
                m4aSongNumStart(SONG_EF_KU_ATT03);

                if ((act->flags & 4)
                    ? ApplyAttackBox(0x13B, act->x - 0x2800, act->y, act->z, 40, 12, 64)
                    : ApplyAttackBox(0x13B, act->x + 0x2800, act->y, act->z, 40, 12, 64)) {
                    m4aSongNumStart(SONG_EF_KU_ATT02);
                }
            }
            MahluxiaSpawnFlower(w);
            break;
        case 5:
        case 6:
            MahluxiaSpawnFlower(w);
            break;
        }

        if (w->flags & 4) {
            w->subSpeed += 25;

            if (act->flags & 4) {
                w->sub.x = w->sub.x - w->subSpeed;
            } else {
                w->sub.x = w->sub.x + w->subSpeed;
            }

            switch (AnimGetFrame(&w->sub.anim)) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                if (ApplyAttackBox(0x13B, w->sub.x, w->sub.y, w->sub.z, 8, 4, 64)) {
                    m4aSongNumStart(SONG_EF_MLC_SNICHIT);
                }
                break;
            default:
                if (ApplyAttackBox(0x13B, w->sub.x, w->sub.y, w->sub.z, 16, 4, 20)) {
                    m4aSongNumStart(SONG_EF_MLC_SNICHIT);
                }
                break;
            }

            if (w->sub.x < (gBtlWork->xMin - 32) << 8 ||
                w->sub.x > (gBtlWork->xMax + 32) << 8) {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
                work->base.stateTimer = 0;
                w->sub.flags |= 2;
                break;
            }
        }
        work->base.stateTimer++;
        break;
    }

    if (!(act->flags & 0x2000)) {
        if (act->badStatus != 2) {
            MahluxiaHover(&work->base, w->hoverZ);
        }
    }
    TaskPoolUpdate(&w->tasks);
    return HumUpdate(&work->base);
}

void task_hum_mahluxia_2(MahluxiaWork* work) {
    HumDraw(&work->base);

    if ((work->flags & 2) && (work->sub.flags & 2)) {
        switch (work->unk_1D8 % 12) {
        case 0:
        case 2:
        case 4:
        case 6:
        case 8:
        case 10:
            MahluxiaDrawAfterimage(work, &work->spawns[2]);
            break;
        case 1:
        case 3:
        case 7:
            MahluxiaDrawAfterimage(work, &work->spawns[4]);
            break;
        case 5:
        case 9:
            MahluxiaDrawAfterimage(work, &work->spawns[6]);
            break;
        case 11:
            MahluxiaDrawAfterimage(work, &work->spawns[8]);
            break;
        }
        work->unk_1D8++;
    }
    work->spawns[8] = work->spawns[7];
    work->spawns[7] = work->spawns[6];
    work->spawns[6] = work->spawns[5];
    work->spawns[5] = work->spawns[4];
    work->spawns[4] = work->spawns[3];
    work->spawns[3] = work->spawns[2];
    work->spawns[2] = work->spawns[1];
    work->spawns[1] = work->spawns[0];
    MahluxiaSaveAfterimage(work, &work->spawns[0]);
    TaskPoolDraw(&work->tasks);
}

void task_hum_mahluxia_3(MahluxiaWork* work) {
    HumReleaseResources(&work->base);
    TaskPoolDestroy(&work->tasks);
}

void LaxeneHover(HumWork* work, s32 a) {
    BtlObj* act;
    s32 t;

    if (a != 0) {
        act = &work->actor;
        t = a + gSineTable[gFrameCounter * 4 % 256] * 6;
        work->vz = 0;
        act->z += (t - act->z) >> 3;
    }
}

void CreateHumLaxeneKnfTask(LaxeneWork* work, s16 a, s16 b) {
    BtlObj* act = &work->base.actor;
    VixenNdlArgs args;

    if (act->flags & 4) {
        args.x = act->x + (a << 8);
        args.unk_12 = 1;
    } else {
        args.x = act->x - (a << 8);
        args.unk_12 = 0;
    }
    args.z = act->z + (b << 8);
    args.y = act->y;
    TaskCreate(&work->tasks, &gTaskDescHumLaxeneKnf, &args);
}

void task_hum_laxene_0(LaxeneWork* work) {
    HumInit(&work->base, &gHumLaxeneDef);
    work->flags = 0;
    work->hoverZ = -0x3000;
    work->scaleSteps = 0;
    work->base.actor.flags |= 0x80000000000;
    work->base.stockMoves = gHumLaxeneStockMoves[0];
    TaskPoolInit(&work->tasks, 12);
}

u8 task_hum_laxene_1(LaxeneWork* work) {
    LaxeneWork* w;
    BtlObj* act;
    s32 x;
    s32 y;
    s32 z;
    s16 d;
    s32 u;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &x, &y, &z);

    switch (_0800E434(&work->base)) {
    case 5:
        work->base.stateTimer = 0;
        work->base.steps = 0;

        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
            work->base.state = 21;
            break;
        case 37:
            work->base.state = 30;
            break;
        case 38:
        case 39:
            if (act->hp < (act->maxHp >> 1)) {
                work->base.state = 31;
            } else {
                work->base.state = 22;
            }
            break;
        case 0xF49D2735:
            work->base.state = 25;
            break;
        case 0xF35CFF3F:
            work->base.steps = GetRandom() % 4 + 4;
            work->base.state = 32;
            m4aSongNumStart(SONG_SND_284);
            break;
        }
        break;
    case 4:
        m4aSongNumStop(SONG_EF_RAC_BEEM);
        work->base.scaleX = 256;
        work->base.scaleY = 256;
        break;
    }

    if (gBtlWork->battleId == 163) {
        if (HumChooseCardAction(&work->base, 15, 80, 80, 50)) {
            work->base.stockMoves = gHumLaxeneStockMoves[0];
        }
    } else if (HumChooseCardAction(&work->base, 5, 80, 80, 50)) {
        if (GetRandom() % 2) {
            work->base.stockMoves = gHumLaxeneStockMoves[0];
        } else {
            work->base.stockMoves = gHumLaxeneStockMoves[1];
        }
    }

    switch (work->base.state) {
    case 12:
    case 18:
        AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        break;
    case 17:
        AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        break;
    case 0:
        AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        HumFaceTarget(&work->base, 5);

        if (func_08081828() == 0) {
            if (GetRandom() % 30 == 0) {
                work->base.state = 8;
                work->base.stateTimer = 0;
            } else {
                work->base.stateTimer++;
            }
        }
        break;
    case 8:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 1, 0, w->base.tiles);
            work->base.targetX = (gBtlWork->xMin + GetRandom() % (gBtlWork->xMax - gBtlWork->xMin + 1)) << 8;
            work->base.targetY = (gBtlWork->yMin + GetRandom() % (gBtlWork->yMax - gBtlWork->yMin + 1)) << 8;
            work->base.targetZ = -((GetRandom() % 71) << 8);

            if (act->btl->hcEffect == 50) {
                work->base.steps = 12;
            } else {
                work->base.steps = 25;
            }
            w->hoverZ = 0;
        } else if (AnimIsFinished(&work->base.anim)) {
            AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 2, 1, w->base.tiles);
        }
        ApproachValue(&act->x, work->base.targetX, (u16)work->base.steps);
        ApproachValue(&act->y, work->base.targetY, (u16)work->base.steps);
        ApproachValue(&act->z, work->base.targetZ, (u16)work->base.steps);
        work->base.steps--;

        if ((s16)work->base.steps <= 0) {
            work->base.state = 0;
            work->base.stateTimer = 0;
            w->hoverZ = act->z;
            break;
        }
        work->base.vz = 0;

        if (act->x < (s32)work->base.targetX) {
            act->flags &= ~4;
        } else {
            act->flags |= 4;
        }
        work->base.stateTimer++;
        break;
    case 1:
    case 3:
    case 9:
    case 11:
    case 14:
        w->hoverZ = 0;
        AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
        break;
    case 25:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
            w->hoverZ = 0;
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 26;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 26:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 7, 1, w->base.tiles);

            if (act->flags & 4) {
                BgFxStartThunder(0, act->x + 0x400, act->y, act->z - 0x5000, act->x,
                    act->y, act->z - 0x5000, 0x135);
            } else {
                BgFxStartThunder(0, act->x - 0x400, act->y, act->z - 0x5000, act->x,
                    act->y, act->z - 0x5000, 0x135);
            }
        }

        if (BgFxIsActive()) {
            work->base.stateTimer++;
        } else {
            work->base.stateTimer = 0;
            work->base.state = 27;
        }
        break;
    case 27:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
        }
        HumFaceTarget(&work->base, 1);

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 28;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 28:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 10, 1, w->base.tiles);
            m4aSongNumStart(SONG_EF_RAC_BEEM);

            if (act->flags & 4) {
                BgFxStartLaxeneBeam(act->x - 0x1000, act->y, act->z - 0x3000, 1, 310);
            } else {
                BgFxStartLaxeneBeam(act->x + 0x1000, act->y, act->z - 0x3000, 0, 310);
            }
        }
        u = (y - act->y) >> 3;
        act->y += u;
        BgFxAddPosition(0, u, 0);

        if (BgFxIsActive()) {
            work->base.stateTimer++;
        } else {
            m4aSongNumStop(SONG_EF_RAC_BEEM);
            work->base.stateTimer = 0;
            work->base.state = 29;
        }
        break;
    case 29:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 11, 0, w->base.tiles);
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 22:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
            w->hoverZ = 0;
            m4aSongNumStart(SONG_SND_283);
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 23;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 23:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 7, 1, w->base.tiles);

            if (act->flags & 4) {
                BgFxStartThunder(1, act->x + 0x400, act->y, act->z - 0x5000, x, y, 0, 0x135);
            } else {
                BgFxStartThunder(1, act->x - 0x400, act->y, act->z - 0x5000, x, y, 0, 0x135);
            }
        }

        if (BgFxIsActive()) {
            work->base.stateTimer++;
        } else {
            work->base.stateTimer = 0;
            work->base.state = 24;
        }
        break;
    case 24:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 8, 0, w->base.tiles);
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 30:
        if ((s16)work->base.stateTimer == 0) {
            m4aSongNumStart(SONG_SND_285);
            AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
            FadeToAmount(0, gBtlWork->fadeAmount, 8);
            w->hoverZ = 0;
            work->base.vz = 0x400;
        }
        MakeOpponentsHittable();

        switch ((s16)work->base.stateTimer) {
        case 28:
            CreateHumLaxeneKnfTask(w, -38, -11);
            break;
        case 32:
            CreateHumLaxeneKnfTask(w, -37, -25);
            break;
        case 36:
            CreateHumLaxeneKnfTask(w, -32, -38);
            break;
        case 44:
            CreateHumLaxeneKnfTask(w, -36, -18);
            break;
        case 48:
            CreateHumLaxeneKnfTask(w, -35, -32);
            break;
        case 52:
            CreateHumLaxeneKnfTask(w, -30, -45);
            break;
        }

        if ((s16)work->base.stateTimer > 120) {
            FadeToOriginal(0, 8);
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 21:
        if ((s16)work->base.stateTimer == 0) {
            AnimReset(&work->base.anim);

            if ((s16)work->base.steps == 0) {
                AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            }
            w->hoverZ = 0;
            w->flags &= ~1;
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                d = 13;
                break;
            case 3:
                d = -1;
                break;
            case 4:
                d = -4;
                break;
            case 5:
                d = -3;
                break;
            case 9:
                d = -2;
                break;
            case 10:
                d = -3;
                break;
            default:
                d = 0;
                break;
            }

            if (act->flags & 4) {
                act->x -= d << 8;
            } else {
                act->x += d << 8;
            }
        }

        if (act->flags & 4) {
            s32 v = act->x - 0x1000;
            act->x += (x - v) >> 4;
        } else {
            s32 v = act->x + 0x1000;
            act->x += (x - v) >> 4;
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                MakeOpponentsHittable();

                if ((act->flags & 4)
                    ? ApplyAttackBox(0x131, act->x - 0x1800, act->y, act->z, 8, 24, 50)
                    : ApplyAttackBox(0x131, act->x + 0x1800, act->y, act->z, 8, 24, 50)) {
                    m4aSongNumStart(SONG_BTL_RAC_HIT);
                    w->flags |= 1;
                }
                break;
            case 8:
                MakeOpponentsHittable();

                if ((act->flags & 4)
                    ? ApplyAttackBox(0x132, act->x - 0x1000, act->y, act->z, 16, 24, 50)
                    : ApplyAttackBox(0x132, act->x + 0x1000, act->y, act->z, 16, 24, 50)) {
                    m4aSongNumStart(SONG_BTL_RAC_HIT);
                    w->flags |= 1;
                }
                break;
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;

            if ((s16)work->base.steps <= 0 && (w->flags & 1)) {
                work->base.state = 21;
                work->base.steps++;
            } else {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
            }
        } else {
            work->base.stateTimer++;
        }
        break;
    case 31:
        if ((s16)work->base.stateTimer == 0) {
            AnimReset(&work->base.anim);

            if ((work->base.steps & 1) == 0) {
                AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 13, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 14, 0, w->base.tiles);
            }
            w->hoverZ = 0;
            w->flags &= ~1;
            act->originX = act->x;
            work->base.vz = 0x400;
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                d = 13;
                break;
            case 3:
                d = -1;
                break;
            case 4:
                d = -4;
                break;
            case 5:
                d = -3;
                break;
            case 9:
                d = -2;
                break;
            case 10:
                d = -3;
                break;
            default:
                d = 0;
                break;
            }

            if (act->flags & 4) {
                act->x -= d << 8;
            } else {
                act->x += d << 8;
            }
        }

        if (act->flags & 4) {
            s32 v = act->x - 0x1000;
            act->x += (x - v) >> 3;
        } else {
            s32 v = act->x + 0x1000;
            act->x += (x - v) >> 3;
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                MakeOpponentsHittable();

                if ((act->flags & 4)
                    ? ApplyAttackBox(0x131, act->x - 0x1800, act->y, act->z, 8, 24, 50)
                    : ApplyAttackBox(0x131, act->x + 0x1800, act->y, act->z, 8, 24, 50)) {
                    m4aSongNumStart(SONG_BTL_RAC_HIT);
                    w->flags |= 1;

                    if ((s16)work->base.steps == 4) {
                        MakeOpponentsHittable();
                        BgFxStartThunderStrike(x, y, 0, 0x137);
                    }
                }
                break;
            case 8:
                MakeOpponentsHittable();

                if ((act->flags & 4)
                    ? ApplyAttackBox(0x132, act->x - 0x1000, act->y, act->z, 16, 24, 50)
                    : ApplyAttackBox(0x132, act->x + 0x1000, act->y, act->z, 16, 24, 50)) {
                    m4aSongNumStart(SONG_BTL_RAC_HIT);
                    w->flags |= 1;

                    if ((s16)work->base.steps == 4) {
                        MakeOpponentsHittable();
                        BgFxStartThunderStrike(x, y, z, 0x137);
                    }
                }
                break;
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;

            if (w->flags & 1) {
                if ((s16)work->base.steps > 3) {
                    ClearBtlObjActionFlags(act);
                    work->base.state = 0;
                } else {
                    work->base.state = 31;
                    work->base.steps++;
                }
            } else {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
            }
        } else {
            work->base.stateTimer++;
        }
        break;
    case 32:
        if ((s16)work->base.stateTimer == 0) {
            act->flags ^= 4;

            if (act->flags & 4) {
                s32 t = ((GetRandom() % 57) << 8) + 0x1800;
                act->x = x + t;
            } else {
                s32 t = ((GetRandom() % 57) << 8) + 0x1800;
                act->x = x - t;
            }
            {
                s32 t = ((GetRandom() % 27) << 8) - 0xD00;
                act->y = y + t;
            }
            act->z = 0;
            AnimReset(&work->base.anim);

            if ((GetRandom() & 1) == 0) {
                AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 13, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 14, 0, w->base.tiles);
            }
            w->hoverZ = 0;
            w->flags &= ~1;
            w->scaleSteps = 8;
            work->base.scaleX = 5;
            work->base.scaleY = 384;
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                d = 13;
                break;
            case 3:
                d = -1;
                break;
            case 4:
                d = -4;
                break;
            case 5:
                d = -3;
                break;
            case 9:
                d = -2;
                break;
            case 10:
                d = -3;
                break;
            default:
                d = 0;
                break;
            }

            if (act->flags & 4) {
                act->x -= d << 8;
            } else {
                act->x += d << 8;
            }
        }

        if (act->flags & 4) {
            s32 v = act->x - 0x1000;
            act->x += (x - v) >> 3;
        } else {
            s32 v = act->x + 0x1000;
            act->x += (x - v) >> 3;
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                MakeOpponentsHittable();

                if ((act->flags & 4)
                    ? ApplyAttackBox(0x131, act->x - 0x1800, act->y, act->z, 8, 24, 50)
                    : ApplyAttackBox(0x131, act->x + 0x1800, act->y, act->z, 8, 24, 50)) {
                    m4aSongNumStart(SONG_BTL_RAC_HIT);
                    w->flags |= 1;
                }
                break;
            case 8:
                MakeOpponentsHittable();

                if ((act->flags & 4)
                    ? ApplyAttackBox(0x132, act->x - 0x1000, act->y, act->z, 16, 24, 50)
                    : ApplyAttackBox(0x132, act->x + 0x1000, act->y, act->z, 16, 24, 50)) {
                    m4aSongNumStart(SONG_BTL_RAC_HIT);
                    w->flags |= 1;
                }
                break;
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.steps--;

            if ((s16)work->base.steps > 0) {
                if (GetRandom() % 6 != 0) {
                    work->base.state = 32;
                } else {
                    work->base.state = 33;
                }
            } else {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
            }
        } else {
            work->base.stateTimer++;
        }
        break;
    case 33:
        if ((s16)work->base.stateTimer == 0) {
            m4aSongNumStart(SONG_SND_285);
            act->flags ^= 4;

            if (act->flags & 4) {
                s32 t = ((GetRandom() % 41) << 8) + 0x5000;
                act->x = x + t;
            } else {
                s32 t = ((GetRandom() % 41) << 8) + 0x5000;
                act->x = x - t;
            }
            {
                s32 t = ((GetRandom() % 49) << 8) - 0x1800;
                act->y = y + t;
            }
            act->z = 0;
            AnimReset(&work->base.anim);
            AnimChangeWithDef(gHumLaxeneAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
            FadeToAmount(0, gBtlWork->fadeAmount, 8);
            w->hoverZ = 0;
            work->base.vz = 0x400;
            w->scaleSteps = 8;
            work->base.scaleX = 5;
            work->base.scaleY = 384;
        }
        MakeOpponentsHittable();

        switch ((s16)work->base.stateTimer) {
        case 28:
            CreateHumLaxeneKnfTask(w, -38, -11);
            break;
        case 32:
            CreateHumLaxeneKnfTask(w, -37, -25);
            break;
        case 36:
            CreateHumLaxeneKnfTask(w, -32, -38);
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            FadeToOriginal(0, 8);
            work->base.stateTimer = 0;
            work->base.steps--;

            if ((s16)work->base.steps <= 0) {
                ClearBtlObjActionFlags(act);
                work->base.state = 0;
            } else if (GetRandom() & 10) {
                work->base.state = 32;
            } else {
                work->base.state = 33;
            }
        } else {
            work->base.stateTimer++;
        }
        break;
    }

    if (!(act->flags & 0x2000) && act->badStatus != 2) {
        LaxeneHover(&work->base, w->hoverZ);
    }
    TaskPoolUpdate(&w->tasks);

    if ((s16)w->scaleSteps > 0) {
        ApproachValue(&work->base.scaleX, 256, w->scaleSteps);
        ApproachValue(&work->base.scaleY, 256, w->scaleSteps);
        w->scaleSteps--;
    }

    return HumUpdate(&work->base);
}

void task_hum_laxene_2(LaxeneWork* work) {
    HumDraw(&work->base);
    TaskPoolDraw(&work->tasks);
}

void task_hum_laxene_3(LaxeneWork* work) {
    m4aSongNumStop(SONG_EF_RAC_BEEM);
    HumReleaseResources(&work->base);
    TaskPoolDestroy(&work->tasks);
}

void task_hum_laxene_knf_0(LaxeneKnfWork* work, VixenNdlArgs* args) {
    work->palette = LoadObjPalette(gLaxinePalette, 0x20);
    work->tiles = LoadObjTiles(gLaxineKnifeTiles, 0x2C0);
    AnimInit(&work->anim, gLaxineKnifeAnims, gLaxineKnifeFrames);
    AnimStart(&work->anim, 0, 0);

    if (args->unk_12 != 0) {
        work->facingLeft = 1;
    } else {
        work->facingLeft = 0;
    }
    work->x = args->x;
    work->y = args->y;
    work->z = args->z;
    work->timer = 0;
    work->onScreen = 1;
    work->state = 0;
    work->playerPrevX = gBtlWork->actor->x;
    work->playerPrevY = gBtlWork->actor->y;
    work->playerPrevZ = gBtlWork->actor->z;
    work->vx = GetRandom() % 897 + 0x800;
    m4aSongNumStart(SONG_EF_RAC_3TR);
}

u8 task_hum_laxene_knf_1(LaxeneKnfWork* work) {
    BtlObj* c;

    if ((gBtlWork->flags & 0x40) == 0) {
        return 0;
    }

    if (work->onScreen == 0) {
        return 0;
    }

    switch (work->state) {
    case 0:
        if (ApplyAttackBox(0x133, work->x, work->y, work->z, 1, 6, 2)) {
            m4aSongNumStart(SONG_BTL_RAC_HIT);
            work->timer = 0;
            work->state = 1;
            BgFxStartThunderHit(work->x, work->y, work->z + 0x1000);
        } else {
            if (work->facingLeft != 0) {
                work->x = work->x - work->vx;
            } else {
                work->x = work->x + work->vx;
            }
            work->timer++;
        }
        break;
    case 1:
        if ((s16)work->timer == 0) {
            AnimStart(&work->anim, 1, 0);
        }
        c = gBtlWork->actor;
        work->x += c->x - work->playerPrevX;
        work->y += c->y - work->playerPrevY;
        work->z += c->z - work->playerPrevZ;

        if ((s16)work->timer > 30) {
            return 0;
        }
        work->timer++;
        break;
    }
    AnimUpdate(&work->anim);
    work->playerPrevX = gBtlWork->actor->x;
    work->playerPrevY = gBtlWork->actor->y;
    work->playerPrevZ = gBtlWork->actor->z;
    return 1;
}

void task_hum_laxene_knf_2(LaxeneKnfWork* work) {
    s16 x;
    s16 y;
    void* gfx;
    u16 attr;

    gfx = AnimGetGfx(&work->anim);

    if (work->facingLeft != 0) {
        attr = GetBattleSpritePriorityFlags(work->y);
    } else {
        attr = GetBattleSpritePriorityFlags(work->y) | 1;
    }
    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gfx, work->tiles, work->palette, 0, attr,
        -0x1004 - (work->y >> 8) * 4);

    if (IsRectOutsideScreen(x, y, 2, 2, 32, 32)) {
        work->onScreen = 0;
    }
}

void task_hum_laxene_knf_3(LaxeneKnfWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void AxcelMoveTo(HumWork* work, s32 a, s32 b) {
    work->targetX = a;
    work->targetY = b;
    work->state = 19;
    work->stateTimer = 0;
}

void AxcelScaleTo(AxcelWork* work, s32 a, s32 b, u16 c) {
    work->scaleSteps = c;
    work->targetScaleX = a;
    work->targetScaleY = b;
}

void AxcelHover(HumWork* work, s32 a) {
    BtlObj* act;
    s32 t;

    if (a != 0) {
        act = &work->actor;
        t = a + gSineTable[gFrameCounter * 4 % 256] * 3;
        work->vz = 0;
        act->z += (t - act->z) >> 4;
    }
}

void AxcelSpawnParticle(AxcelWork* work, HumSub* sub) {
    s32 args[3];

    if (GetRandom() % 6 == 0) {
        args[0] = sub->x + (GetRandom() % 29 - 14) * 256;
        args[1] = sub->y + (GetRandom() % 15 - 7) * 256;
        args[2] = sub->z;
        TaskCreate(&work->tasks, &gTaskDescHumAxcelPtc, args);
    }
}

void task_hum_axcel_0(AxcelWork* work) {
    HumInit(&work->base, &gHumAxcelDef);
    HumSubInit(&work->base, &work->sub, &gHumAxcelSubDef);
    HumSubInit(&work->base, &work->sub2, &gHumAxcelSubDef);
    work->base.actor.flags |= 0x04000000;
    work->base.stockMoves = gHumAxcelStockMoves[0];
    work->flags = 0;
    work->hoverZ = -0x300;
    work->scaleSteps = 0;
    work->sub.flags |= 2;
    work->sub2.flags |= 2;
    work->tiles = LoadObjTiles(gUnk_08B22BBC, 0x100);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    TaskPoolInit(&work->tasks, 16);
}

u8 task_hum_axcel_1(AxcelWork* work) {
    AxcelWork* w;
    HumSub* sub;
    HumSub* sub2;
    BtlObj* act;
    s32 x;
    s32 y;

    w = work;
    sub = &work->sub;
    sub2 = &work->sub2;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &x, &y, 0);
    switch (_0800E434(&work->base)) {
    case 5:
        work->base.stateTimer = 0;
        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
        case 38:
            work->base.state = 20;
            work->base.steps = 0;
            break;
        case 37:
        case 39:
            work->base.state = 22;
            break;
        case 0xF21C8721:
            work->base.state = 32;
            break;
        case 0xF21CAF21:
            work->base.state = 26;
            break;
        }
        w->targetScaleX = work->base.scaleX = 0x100;
        w->targetScaleY = work->base.scaleY = 0x100;
        break;
    case 4:
        work->base.flags &= ~32;
#ifdef VERSION_EU
        act->flags &= ~0x2000000ULL;
#endif
        sub->flags |= 2;
        sub2->flags |= 2;
        work->targetScaleX = work->base.scaleX = 0x100;
        work->targetScaleY = work->base.scaleY = 0x100;
        m4aSongNumStop(SONG_EF_AKL_FIREWALL);
        break;
    }
    if (gBtlWork->battleId == 162) {
        if (HumChooseCardAction(&work->base, 20, 40, 40, 24)) {
            work->base.stockMoves = gHumAxcelStockMoves[0];
        }
    } else if (HumChooseCardAction(&work->base, 5, 40, 40, 24)) {
        if ((u16)GetRandom() % 2) {
            work->base.stockMoves = gHumAxcelStockMoves[0];
        } else {
            work->base.stockMoves = gHumAxcelStockMoves[1];
        }
    }
    switch (work->base.state) {
    case 12:
    case 18:
        AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        break;
    case 17:
        AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        break;
    case 0:
        AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        w->hoverZ = -0x300;
        if (func_08081828()) {
            break;
        }
        if ((u16)((u16)GetRandom() % 80) == 0) {
            work->base.state = 8;
            work->base.stateTimer = 0;
            break;
        }
        if (HumIsNearAreaEdge(&work->base, 40)) {
            AxcelMoveTo(&w->base, 0x10000, act->y);
            break;
        }
        HumFaceTarget(&work->base, 8);
        work->base.stateTimer++;
        break;
    case 8:
        if ((s16)work->base.stateTimer == 0) {
            work->base.targetX = x + (((u16)((u16)GetRandom() % 201) - 100) << 8);
            work->base.targetY = y + (((u16)((u16)GetRandom() % 65) - 32) << 8);
            work->base.state = 19;
        }
        break;
    case 1:
        if ((s16)work->base.stateTimer == 0) {
            if (act->btl->hcEffect == 18) {
                act->btl->hcEffectCount--;
#ifdef VERSION_EU
                w->targetScaleX = work->base.scaleX = 0x100;
                w->targetScaleY = work->base.scaleY = 0x100;
#endif
                act->vx = act->vy = 0;
                work->base.vz = 0;
                act->invincibleTimer = 30;
                work->base.stateTimer = 6;
                break;
            }
        }
    case 3:
    case 9:
    case 11:
    case 14:
        if ((s16)work->base.stateTimer == 0) {
            w->targetScaleX = work->base.scaleX = 0x100;
            w->targetScaleY = work->base.scaleY = 0x100;
        }
        w->hoverZ = 0;
        AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        break;
    case 22:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 1, 1, w->base.tiles);
            work->base.steps = 10;
        }
        if (act->x < x) {
            work->base.targetX = x - 0x6E00;
        } else {
            work->base.targetX = x + 0x6E00;
        }
        ApproachValueHalfSteps(&act->x, work->base.targetX, (u16)work->base.steps);
        work->base.steps--;
        HumFaceTarget(&work->base, 1);
        if ((s16)work->base.steps <= 0) {
            work->base.state = 23;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 23:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            w->hoverZ = 0;
            work->base.targetX = x * 2 - act->x;
            work->base.targetY = y * 2 - act->y;
        }
        HumFaceTarget(&work->base, 1);
        BtlMapFollowPosition(act->x, act->y, act->z);
        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 24;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 24:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
            AnimChangeWithDef(gHumAxcelWeaponAnimDefs, &w->base.sub->anim, 0, 1, w->base.sub->tiles);
            sub->palette2 = work->base.palette;
            sub->flags |= 4;
            sub->flags &= ~2;
            m4aSongNumStart(SONG_BTL_AKL_WTHR);
            if (act->flags & 4) {
                sub->x = act->x - 0x2000;
            } else {
                sub->x = act->x + 0x2000;
            }
            sub->y = act->y;
            sub->z = act->z - 0x2000;
            HumFaceTarget(&work->base, 1);
            w->steps = 30;
        }
        ApproachValue(&sub->x, work->base.targetX, w->steps);
        ApproachValue(&sub->y, work->base.targetY, w->steps);
        w->steps--;
        BtlMapFollowPosition(sub->x, sub->y, sub->z);
        if (ApplyAttackBox(302, sub->x, sub->y, sub->z, 8, 8, 2)) {
            m4aSongNumStart(SONG_BTL_MON_SWORD01);
        }
        if ((s16)w->steps == 19) {
            AxcelScaleTo(w, 12, 0x200, 8);
        }
        if ((s16)w->steps == 11) {
            act->x = work->base.targetX;
            act->y = work->base.targetY;
            act->flags ^= 4;
            AxcelScaleTo(w, 0x100, 0x100, 8);
        }
        if ((s16)w->steps <= 4) {
            work->base.state = 25;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 25:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 7, 0, w->base.tiles);
            sub->flags |= 2;
            sub->flags &= ~4;
        }
        BtlMapFollowPosition(act->x, act->y, act->z);
        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 26:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 8, 0, w->base.tiles);
            AnimReset(&sub->anim);
            AnimReset(&sub2->anim);
            AnimChangeWithDef(gHumAxcelWeaponAnimDefs, &w->base.sub->anim, 6, 0, w->base.sub->tiles);
            AnimChangeWithDef(gHumAxcelWeaponAnimDefs, &((HumSub*)w->base.sub2)->anim, 2, 0, ((HumSub*)w->base.sub2)->tiles);
            sub->palette2 = sub->palette;
            sub->flags &= ~6;
            sub2->flags &= ~6;
            sub->flags |= 1;
            sub2->flags &= ~1;
            w->hoverZ = 0;
        }
        HumFaceTarget(&work->base, 1);
        work->base.vz = 0;
        if (work->base.anim.timer == 0) {
            switch (AnimGetFrame(&work->base.anim)) {
            case 3:
                m4aSongNumStart(SONG_BTL_AKL_FIREENTRY);
                AnimChangeWithDef(gHumAxcelWeaponAnimDefs, &w->base.sub->anim, 7, 1, w->base.sub->tiles);
                AnimChangeWithDef(gHumAxcelWeaponAnimDefs, &((HumSub*)w->base.sub2)->anim, 3, 1, ((HumSub*)w->base.sub2)->tiles);
                break;
            case 6:
                m4aSongNumStart(SONG_SND_290);
                AnimChangeWithDef(gHumAxcelWeaponAnimDefs, &w->base.sub->anim, 8, 1, w->base.sub->tiles);
                AnimChangeWithDef(gHumAxcelWeaponAnimDefs, &((HumSub*)w->base.sub2)->anim, 4, 1, ((HumSub*)w->base.sub2)->tiles);
                break;
            case 7:
                AnimChangeWithDef(gHumAxcelWeaponAnimDefs, &w->base.sub->anim, 9, 0, w->base.sub->tiles);
                AnimChangeWithDef(gHumAxcelWeaponAnimDefs, &((HumSub*)w->base.sub2)->anim, 5, 0, ((HumSub*)w->base.sub2)->tiles);
                m4aSongNumStart(SONG_BTL_AKL_FIRETHR);
                break;
            }
        }
        switch (AnimGetFrame(&work->base.anim)) {
        case 3:
        case 4:
        case 5:
            {
                s32 t = act->z + 0x1000;
                act->z += (act->originZ - t) >> 4;
            }
            break;
        case 6:
            if (act->flags & 4) {
                {
                s32 t = act->x - 0x800;
                act->x += (act->originX - t) >> 3;
            }
            } else {
                {
                s32 t = act->x + 0x800;
                act->x += (act->originX - t) >> 3;
            }
            }
            {
                s32 t = act->z + 0x1400;
                act->z += (act->originZ - t) >> 3;
            }
            break;
        }
        act->y += (((gBtlWork->yMin + gBtlWork->yMax + 32) << 7) - act->y) >> 3;
        sub->x = act->x;
        sub->y = act->y;
        sub->z = act->z;
        sub2->x = act->x;
        sub2->y = act->y;
        sub2->z = act->z;
        if (AnimIsFinished(&work->base.anim)) {
            if (act->hp < act->maxHp / 2) {
                work->base.state = 31;
            } else if ((x - act->x >= 0) ? x - act->x <= 0x4FFF : act->x - x <= 0x4FFF) {
                work->base.state = 29;
            } else {
                work->base.state = 27;
            }
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 27: {
        s32 t;
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 9, 1, w->base.tiles);
            AnimChangeWithDef(gHumAxcelWeaponAnimDefs, &w->base.sub->anim, 1, 1, w->base.sub->tiles);
            AnimChangeWithDef(gHumAxcelWeaponAnimDefs, &((HumSub*)w->base.sub2)->anim, 1, 1, ((HumSub*)w->base.sub2)->tiles);
            sub->flags |= 4;
            sub2->flags |= 4;
            if (act->flags & 4) {
                sub->x = act->x - 0x3700;
                sub2->x = act->x - 0x5700;
            } else {
                sub->x = act->x + 0x3700;
                sub2->x = act->x + 0x5700;
            }
            sub->y = act->y + 0xA00;
            sub->z = act->z - 0x1E00;
            sub2->y = act->y - 0xA00;
            sub2->z = act->z - 0x1400;
            w->hoverZ = act->z;
        }
        if (act->flags & 4) {
            s32 d = ((s16)work->base.stateTimer << 9) + 0x5A00;
            t = act->x - d;
        } else {
            s32 d = ((s16)work->base.stateTimer << 9) + 0x5A00;
            t = act->x + d;
        }
        sub->x += (t - sub->x) >> 3;
        sub2->x += (t - sub2->x) >> 3;
        sub->y += (act->y + gSineTable[((u16)work->base.stateTimer * 4) & 255] * 55 - sub->y) >> 2;
        sub2->y += (act->y - gSineTable[((u16)work->base.stateTimer * 4) & 255] * 55 - sub2->y) >> 2;
        {
            s32* ground = &gBtlWork->targetZ;
            {
                s32 t = sub->z + 0x1800;
                sub->z += (*ground - t) >> 2;
            }
            {
                s32 t = sub2->z + 0x1800;
                sub2->z += (*ground - t) >> 3;
            }
        }
        if (ApplyAttackBox(304, sub->x, sub->y, sub->z, 8, 8, 2)) {
            m4aSongNumStart(SONG_EF_FIRE01);
        }
        if (ApplyAttackBox(304, sub2->x, sub2->y, sub2->z, 8, 8, 2)) {
            m4aSongNumStart(SONG_EF_FIRE01);
        }
        AxcelSpawnParticle(w, sub);
        AxcelSpawnParticle(w, sub2);
        if (sub->x > ((gBtlWork->xMax + 32) << 8) ||
            sub->x < ((gBtlWork->xMin - 32) << 8)) {
            sub->flags |= 2;
            sub2->flags |= 2;
            work->base.stateTimer = 0;
            work->base.state = 28;
        } else {
            work->base.stateTimer++;
        }
        break;
    }
    case 29: {
        u16 angle;
        s32 dx;
        s32 dy;
        HumFaceTarget(&work->base, 1);
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 9, 1, w->base.tiles);
            AnimChangeWithDef(gHumAxcelWeaponAnimDefs, &w->base.sub->anim, 1, 1, w->base.sub->tiles);
            AnimChangeWithDef(gHumAxcelWeaponAnimDefs, &((HumSub*)w->base.sub2)->anim, 1, 1, ((HumSub*)w->base.sub2)->tiles);
            sub->flags |= 4;
            sub2->flags |= 4;
            if (act->flags & 4) {
                sub->x = act->x - 0x3700;
                sub2->x = act->x - 0x5700;
            } else {
                sub->x = act->x + 0x3700;
                sub2->x = act->x + 0x5700;
            }
            sub->y = act->y + 0xA00;
            sub->z = act->z - 0x1E00;
            sub2->y = act->y - 0xA00;
            sub2->z = act->z - 0x1400;
            w->hoverZ = act->z;
            w->steps = 200;
            w->orbitRadius = 0x5A00;
            m4aSongNumStart(SONG_BTL_AKL_FIRETHR);
        }
        angle = (u16)work->base.stateTimer * 4;
        ApproachValue(&w->orbitRadius, 0x2800, w->steps);
        w->steps--;
        dx = gSineTable[angle % 256] * w->orbitRadius >> 8;
        dy = -gSineTable[angle % 256 + 64] * w->orbitRadius >> 8;
        sub->x += (x + dx - sub->x) >> 4;
        sub->y += (y + dy - sub->y) >> 4;
        sub2->x += (x - dx - sub2->x) >> 4;
        sub2->y += (y - dy - sub2->y) >> 4;
        sub->z += (-0x1800 - sub->z) >> 3;
        sub2->z += (-0x1800 - sub2->z) >> 3;
        if (ApplyAttackBox(304, sub->x, sub->y, sub->z, 8, 8, 2)) {
            m4aSongNumStart(SONG_EF_FIRE01);
        }
        if (ApplyAttackBox(304, sub2->x, sub2->y, sub2->z, 8, 8, 2)) {
            m4aSongNumStart(SONG_EF_FIRE01);
        }
        AxcelSpawnParticle(w, sub);
        AxcelSpawnParticle(w, sub2);
        if ((s16)w->steps <= 0) {
            work->base.stateTimer = 0;
            work->base.state = 30;
        } else {
            work->base.stateTimer++;
        }
        break;
    }
    case 30:
        if ((s16)work->base.stateTimer == 0) {
            w->steps = 20;
        }
        if (act->flags & 4) {
            ApproachValue(&sub->x, (gBtlWork->xMin - 32) << 8, w->steps);
            ApproachValue(&sub2->x, (gBtlWork->xMin - 32) << 8, w->steps);
        } else {
            ApproachValue(&sub->x, (gBtlWork->xMax + 32) << 8, w->steps);
            ApproachValue(&sub2->x, (gBtlWork->xMax + 32) << 8, w->steps);
        }
        ApproachValue(&sub->z, -0x5A00, w->steps);
        ApproachValue(&sub2->z, -0x5A00, w->steps);
        w->steps--;
        if ((s16)w->steps <= 0) {
            sub->flags |= 2;
            sub2->flags |= 2;
            work->base.stateTimer = 0;
            work->base.state = 28;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 31:
        HumFaceTarget(&work->base, 1);
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 9, 1, w->base.tiles);
            AnimChangeWithDef(gHumAxcelWeaponAnimDefs, &w->base.sub->anim, 1, 1, w->base.sub->tiles);
            AnimChangeWithDef(gHumAxcelWeaponAnimDefs, &((HumSub*)w->base.sub2)->anim, 1, 1, ((HumSub*)w->base.sub2)->tiles);
            sub->flags |= 4;
            sub2->flags |= 4;
            if (act->flags & 4) {
                sub->x = act->x - 0x3700;
                sub2->x = act->x - 0x5700;
            } else {
                sub->x = act->x + 0x3700;
                sub2->x = act->x + 0x5700;
            }
            sub->y = act->y + 0xA00;
            sub->z = act->z - 0x1E00;
            sub2->y = act->y - 0xA00;
            sub2->z = act->z - 0x1400;
            w->hoverZ = act->z;
            w->subAngle = GetAngle(sub->x, sub->y, x, y);
            w->sub2Angle = GetAngle(sub2->x, sub2->y, x, y);
        }
        sub->x += gSineTable[(u8)w->subAngle] * 6;
        sub->y -= gSineTable[(u8)w->subAngle + 64] * 4;
        sub2->x += gSineTable[(u8)w->sub2Angle] * 6;
        sub2->y -= gSineTable[(u8)w->sub2Angle + 64] * 4;
        sub->z += (-0x1000 - sub->z) >> 3;
        sub2->z += (-0x1000 - sub2->z) >> 3;
        w->subAngle += 2;
        w->sub2Angle -= 2;
        if (ClampBattlePosition(&sub->x, &sub->y, 0, 0)) {
            w->subAngle += 128;
        }
        if (ClampBattlePosition(&sub2->x, &sub2->y, 0, 0)) {
            w->sub2Angle += 128;
        }
        if (ApplyAttackBox(304, sub->x, sub->y, sub->z, 8, 8, 2)) {
            m4aSongNumStart(SONG_EF_FIRE01);
            w->subAngle += 128;
        }
        if (ApplyAttackBox(304, sub2->x, sub2->y, sub2->z, 8, 8, 2)) {
            m4aSongNumStart(SONG_EF_FIRE01);
            w->sub2Angle += 128;
        }
        AxcelSpawnParticle(w, sub);
        AxcelSpawnParticle(w, sub2);
        if ((s16)work->base.stateTimer > 300) {
            work->base.stateTimer = 0;
            work->base.state = 30;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 28:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 10, 0, w->base.tiles);
        }
        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.stateTimer = 0;
            work->base.state = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 20:
        if ((s16)work->base.stateTimer == 0) {
            m4aSongNumStart(SONG_SND_291);
            AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
            w->hoverZ = 0;
            w->flags &= ~1;
        }
        switch (AnimGetFrame(&work->base.anim)) {
        case 1:
        case 2:
        case 3:
            if (act->flags & 4) {
                s32 t = act->x + 0x3000;
                act->x += (act->originX - t) >> 3;
            } else {
                s32 t = act->x - 0x3000;
                act->x += (act->originX - t) >> 3;
            }
            break;
        }
        if (AnimGetFrame(&work->base.anim) == 2 && work->base.anim.timer == 0) {
            MakeOpponentsHittable();
            if (act->flags & 4 ?
                ApplyAttackBox(300, act->x - 0x2000, act->y, act->z, 20, 24, 50) :
                ApplyAttackBox(300, act->x + 0x2000, act->y, act->z, 20, 24, 50)) {
                m4aSongNumStart(SONG_BTL_MON_SWORD00);
                w->flags |= 1;
            }
        }
        if (w->flags & 1) {
            work->base.state = 21;
            work->base.stateTimer = 0;
        } else if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 21:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            w->hoverZ = 0;
            w->flags &= ~1;
        }
        if (AnimGetFrame(&work->base.anim) == 1) {
            if (act->flags & 4) {
                s32 t = act->x + 0x2800;
                act->x += (act->originX - t) >> 3;
            } else {
                s32 t = act->x - 0x2800;
                act->x += (act->originX - t) >> 3;
            }
        }
        if (AnimGetFrame(&work->base.anim) == 2 && work->base.anim.timer == 0) {
            MakeOpponentsHittable();
            if (act->flags & 4 ?
                ApplyAttackBox(301, act->x - 0x2000, act->y, act->z, 24, 24, 50) :
                ApplyAttackBox(301, act->x + 0x2000, act->y, act->z, 24, 24, 50)) {
                m4aSongNumStart(SONG_BTL_MON_SWORD00);
                w->flags |= 1;
            }
        }
        if ((s16)work->base.steps <= 1 && (w->flags & 1) && AnimGetFrame(&work->base.anim) > 2) {
            work->base.state = 20;
            work->base.stateTimer = 0;
            work->base.steps++;
        } else if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 32:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 11, 0, w->base.tiles);
            w->hoverZ = 0;
            m4aSongNumStart(SONG_SND_289);
        }
        HumFaceTarget(&work->base, 1);
        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 33;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 33: {
        s32 a, b, c;
        if ((s16)work->base.stateTimer == 0) {
            FadeToAmount(0, gBtlWork->fadeAmount, 8);
            AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
            if (act->flags & 4) {
                BgFxStartAxcelFireWall(act->x, 1, 303);
            } else {
                BgFxStartAxcelFireWall(act->x, 0, 303);
            }
            work->base.flags |= 32;
#ifdef VERSION_EU
            act->flags |= 0x2000000ULL;
#endif
            m4aSongNumStart(SONG_EF_AKL_FIREWALL);
        }
        if (act->flags & 4) {
            BgFxAddPosition(-76, 0, 0);
        } else {
            BgFxAddPosition(76, 0, 0);
        }
        BgFxGetPosition(&a, &b, &c);
        if (!BgFxIsActive() || a < ((gBtlWork->xMin - 64) << 8) || a > ((gBtlWork->xMax + 64) << 8)) {
            m4aSongNumStop(SONG_EF_AKL_FIREWALL);
            work->base.state = 34;
            work->base.stateTimer = 0;
            gBtlWork->flags |= 0x400000;
            FadeToOriginal(0, 8);
        } else {
            work->base.stateTimer++;
        }
        break;
    }
    case 34:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 13, 0, w->base.tiles);
            w->hoverZ = 0;
        }
        if (AnimIsFinished(&work->base.anim)) {
            work->base.flags &= ~32;
#ifdef VERSION_EU
            act->flags &= ~0x2000000ULL;
#endif
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 19:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumAxcelAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
            AxcelScaleTo(w, 12, 512, 8);
        }
        if ((s16)work->base.stateTimer > 6) {
            if ((s16)work->base.stateTimer == 7) {
                act->x = work->base.targetX;
                act->y = work->base.targetY;
                AxcelScaleTo(w, 256, 256, 8);
            }
            if (AnimIsFinished(&work->base.anim)) {
                work->base.state = 0;
                work->base.stateTimer = 0;
                break;
            }
        }
        work->base.stateTimer++;
        break;
    }
    if (act->badStatus != 2) {
        AxcelHover(&work->base, w->hoverZ);
    }
    if ((s16)w->scaleSteps > 0) {
        ApproachValue(&work->base.scaleX, w->targetScaleX, w->scaleSteps);
        ApproachValue(&work->base.scaleY, w->targetScaleY, w->scaleSteps);
        w->scaleSteps--;
    }
    TaskPoolUpdate(&w->tasks);
    return HumUpdate(&work->base);
}

void AxcelDrawSubShadow(AxcelWork* work, HumSub* sub) {
    s16 x;
    s16 y;
    ObjAffine* affine;
    s32 scale;
    s32 f;

    if ((sub->flags & 2) == 0) {
        if (sub->z >= 0) {
            affine = 0;
        } else {
            scale = 0x100 - (-sub->z) / 128;
            if (scale <= 127) {
                scale = 128;
            }
            f = 0;

            if (scale > 0x100) {
                f = 1;
            }
            affine = AllocObjAffine(0, scale, scale, f);
        }
        WorldToScreen(&x, &y, sub->x, sub->y, 0);
        DrawSprite(x, y, gUnk_08B22BA8, work->tiles, work->palette, affine, 0x800, 0xFFFE);
    }
}

void task_hum_axcel_2(AxcelWork* work) {
    HumDraw(&work->base);
    AxcelDrawSubShadow(work, &work->sub);
    AxcelDrawSubShadow(work, &work->sub2);
    TaskPoolDraw(&work->tasks);
}

void task_hum_axcel_3(AxcelWork* work) {
    m4aSongNumStop(SONG_EF_AKL_FIREWALL);
    TaskPoolDestroy(&work->tasks);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    HumReleaseResources(&work->base);
}

void task_hum_axcel_ptc_0(AxcelPtcWork* work, s32* args) {
    work->x = args[0];
    work->y = args[1];
    work->z = args[2];
    work->tiles = LoadObjTiles(gUnk_08BF73C6, 0x300);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    AnimInit(&work->anim, gUnk_09EE1FC0, gUnk_09EE1F90);

    switch (GetRandom() % 3) {
    case 0:
        AnimStart(&work->anim, 0, 0);
        break;
    case 1:
        AnimStart(&work->anim, 1, 0);
        break;
    case 2:
        AnimStart(&work->anim, 2, 0);
        break;
    }
}

u8 task_hum_axcel_ptc_1(AxcelPtcWork* work) {
    if (AnimIsFinished(&work->anim)) {
        return 0;
    }
    work->gfx = AnimUpdate(&work->anim);
    return 1;
}

void task_hum_axcel_ptc_2(AxcelPtcWork* work) {
    s16 x;
    s16 y;

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, 0,
        GetBattleSpritePriorityFlags(work->y), -0x1004 - (work->y >> 8) * 4);
}

void task_hum_axcel_ptc_3(AxcelPtcWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void VixenPlaceGroundIce(VixenWork* work) {
    VixenSub* p;
    s32 i;

    m4aSongNumStart(SONG_BTL_VIC_GROUNDICE);
    p = work->sub;

    for (i = 0; i < 3; i++) {
        p[i].pending = p[i].active = 1;
        p[i].x = (gBtlWork->xMin + 32 +
            GetRandom() % (gBtlWork->xMax - gBtlWork->xMin - 0x3F)) << 8;
        p[i].y = (gBtlWork->yMin + 16 +
            GetRandom() % (gBtlWork->yMax - gBtlWork->yMin - 0x1F)) << 8;
    }
}

void VixenCreateIceTasks(VixenWork* work) {
    VixenSub* p;
    s32 i;
    u8 z;

    z = 0;
    p = work->sub;

    for (i = 0; i < 3; i++) {
        p->active = z;
        p->pending = z;
        TaskCreate(&work->tasks, &gTaskDescHumVixenIce, &work->sub[i]);
        p++;
    }
}

void VixenHover(HumWork* work, s32 a) {
    BtlObj* act;
    s32 t;

    if (a != 0) {
        act = &work->actor;
        t = a + gSineTable[gFrameCounter * 4 % 256] * 3;
        work->vz = 0;
        act->z += (t - act->z) >> 4;
    }
}

void task_hum_vixen_0(VixenWork* work) {
    HumInit(&work->base, &gHumVixenDef);
    work->hoverZ = 0;
    work->base.actor.flags |= 0x08000000;
    work->flags = 0;
    TaskPoolInit(&work->tasks, 15);
    VixenCreateIceTasks(work);
    work->base.stockMoves = gHumVixenStockMovesA;

    if (gGameState.flags & 8) {
        gBtlWork->tiles2 = AllocObjTiles(0x840, 0);
    }
}

u8 task_hum_vixen_1(VixenWork* work) {
    VixenWork* w;
    BtlObj* act;
    VixenNdlArgs args;
    s32 x;
    s32 y;
    s32 z;
    s32 s;
    u8 ang;
    s32 d;
    s32 v;
    s32 cx;
    s32 ax;
    u16 t;
    u8 r;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &x, &y, &z);

    switch ((u32)_0800E434(&work->base)) {
    case 5:
        work->base.stateTimer = 0;

        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
        case 38:
            w->base.state = 22;
            break;
        case 37:
        case 39:
            w->base.state = 21;
            break;
        case 0xF53D7753:
            work->base.state = 33;
            break;
        case 0xF53D4F5D:
            work->base.state = 28;
            break;
        case 0xF5DD4F53:
            work->base.state = 29;
            break;
        case 0xF53D4F53:
            work->base.state = 23;
            break;
        }
        break;
    case 4:
        m4aSongNumStop(SONG_BTL_VIC_ICEFALL);
        break;
    case 3:
    case 8:
        if (act->btl->hcEffect == 27) {
            w->base.state = 37;
            w->base.stateTimer = 0;
        }
        break;
    }

    switch ((u32)gBtlWork->battleId) {
    case 164:
        if (HumChooseCardAction(&w->base, 30, 40, 40, 24)) {
            w->base.stockMoves = gHumVixenStockMovesA;
        }
        break;
    case 175:
        if (HumChooseCardAction(&w->base, 5, 40, 40, 24)) {
            switch (GetRandom() % 3) {
            case 0:
                w->base.stockMoves = gHumVixenStockMovesA;
                break;
            case 1:
                w->base.stockMoves = gHumVixenStockMovesC;
                break;
            case 2:
                w->base.stockMoves = gHumVixenStockMovesD;
                break;
            }
        }
        break;
    case 176:
    default:
        if (HumChooseCardAction(&w->base, 30, 40, 40, 24)) {
            switch (GetRandom() % 3) {
            case 0:
                w->base.stockMoves = gHumVixenStockMovesA;
                break;
            case 1:
                w->base.stockMoves = gHumVixenStockMovesB;
                break;
            case 2:
                w->base.stockMoves = gHumVixenStockMovesD;
                break;
            }
        }
        break;
    }

    switch (w->base.state) {
    case 12:
    case 18:
        AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 0, 1, work->base.tiles);
        break;
    case 17:
        AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 0, 1, work->base.tiles);
        work->hoverZ = -0x4000;
        HumFaceTarget(&w->base, 20);
        break;
    case 0:
        AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 0, 1, work->base.tiles);
        work->hoverZ = 0;

        if (func_08081828() == 0) {
            HumFaceTarget(&w->base, 80);

            if (AnimIsFinished(&w->base.anim) && GetRandom() % 80 == 0) {
                w->base.state = 8;
                w->base.stateTimer = 0;
            } else {
                w->base.stateTimer++;
            }
        }
        break;
    case 8:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 1, 1, work->base.tiles);
            work->hoverZ = -0xF00;

            if (act->x <= 0xFFFF) {
                act->flags &= ~4;
                w->base.targetX = (gBtlWork->xMax - 48) << 8;
            } else {
                act->flags |= 4;
                w->base.targetX = (gBtlWork->xMin + 48) << 8;
            }
            work->slideSpeed = 0;
        }
        work->slideSpeed += 17;

        if (work->slideSpeed > 0x199) {
            work->slideSpeed = 0x199;
        }

        if (act->flags & 4) {
            act->x -= work->slideSpeed;
        } else {
            act->x += work->slideSpeed;
        }

        if (w->base.flags & 1) {
            work->flags ^= 1;
        }

        if (work->flags & 1) {
            act->y += work->slideSpeed;
        } else {
            act->y -= work->slideSpeed;
        }
        d = act->x - (s32)w->base.targetX;

        if ((d >= 0) ? d <= 0xBFF : (s32)w->base.targetX - act->x <= 0xBFF) {
            w->base.state = 0;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 1:
    case 3:
    case 9:
    case 11:
    case 14:
        AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 2, 0, work->base.tiles);
        break;
    case 21:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 3, 0, work->base.tiles);
            work->hoverZ = 0;
        }

        if (AnimGetFrame(&w->base.anim) == 3) {
            if (act->flags & 4) {
                s32 d = act->x + 0x3200;
                act->x += (act->originX - d) >> 2;
            } else {
                s32 d = act->x - 0x3200;
                act->x += (act->originX - d) >> 2;
            }

            if ((act->flags & 4)
                ? ApplyAttackBox(312, act->x - 0x2000, act->y, act->z, 12, 12, 48)
                : ApplyAttackBox(312, act->x + 0x2000, act->y, act->z, 12, 12, 48)) {
                m4aSongNumStart(SONG_BTL_VIC_SWORDHIT);
            }
        }

        if (AnimIsFinished(&w->base.anim)) {
            ClearBtlObjActionFlags(act);
            w->base.state = 0;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 37:
        if ((s16)w->base.stateTimer == 0) {
            AnimReset(&w->base.anim);
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 2, 0, work->base.tiles);
        }

        if (AnimIsFinished(&w->base.anim)) {
            w->base.flags &= ~4;
            act->btl->hcEffectCount--;
            v = 0;
            act->hp = act->maxHp / 4;
            act->flags &= ~0x100;
            ClearBtlObjActionFlags(act);
            CreateBtlPopTask(act, 10);
            w->base.state = v;
            w->base.stateTimer = v;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 22:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 4, 0, work->base.tiles);
            work->hoverZ = 0;
        }

        if (AnimGetFrame(&w->base.anim) == 3 && w->base.anim.timer == 0) {
            if (act->flags & 4) {
                BgFxStartBlizzard(1, act->x - 0x3700, act->y, act->z - 0x4000,
                    act->x - 0x6E00, act->y, -0x1400, 1, 0x139);
            } else {
                BgFxStartBlizzard(1, act->x + 0x3700, act->y, act->z - 0x4000,
                    act->x + 0x6E00, act->y, -0x1400, 0, 0x139);
            }
        }

        if (AnimIsFinished(&w->base.anim) && BgFxIsActive() == 0) {
            ClearBtlObjActionFlags(act);
            w->base.state = 0;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 23:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 5, 0, work->base.tiles);
            work->hoverZ = 0;
            work->needleCount = 0;
        }

        if (AnimIsFinished(&w->base.anim)) {
            w->base.stateTimer = 0;
            w->base.state = 24;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 24:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 6, 1, work->base.tiles);
        }

        if ((s16)w->base.stateTimer > 60) {
            w->base.stateTimer = 0;
            w->base.state = 25;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 25:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 7, 0, work->base.tiles);
        }

        if (AnimIsFinished(&w->base.anim)) {
            w->base.stateTimer = 0;
            w->base.state = 26;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 26:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 4, 0, work->base.tiles);

            if (act->flags & 4) {
                work->needleX = act->x - 0x2000;
                work->angle = 192;
            } else {
                work->needleX = act->x + 0x2000;
                work->angle = 64;
            }
            work->needleY = act->y;
            m4aSongNumStart(SONG_VO_VIC_ATTACK01);
            InitObjTilesAtSlot(&work->needleTiles, ((ObjTiles*)gBtlWork->tiles2)->index, gVixenE1Tiles, 0x7E0);
        }

        if (AnimGetFrame(&w->base.anim) > 2) {
            ang = GetAngle(work->needleX, work->needleY, x, y);
            ApproachAngle(&work->angle, ang, 3);
            s = abs(gSineTable[((u16)w->base.stateTimer * 2) & 0xFF]);
            s += 384;
            work->needleX += (gSineTable[(u8)work->angle] * s) >> 8;
            work->needleY += (-gSineTable[(u8)work->angle + 64] * s) >> 8;
            ClampBattlePosition(&work->needleX, &work->needleY, 0, 0);
            HumFaceTarget(&w->base, 1);

            if ((s16)w->base.stateTimer % 9 == 0) {
                args.x = work->needleX;
                args.y = work->needleY;
                args.z = 0;
                args.unk_12 = work->needleCount % 8;
                args.tiles = &work->needleTiles;
                work->needleCount++;
                TaskCreate(&work->tasks, &gTaskDescHumVixenNdl, &args);
            }
        }

        if ((s16)w->base.stateTimer > 360 || (gBtlWork->actor->flags & 0x2000)) {
            w->base.state = 27;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 27:
        if ((s16)w->base.stateTimer > 70) {
            ClearBtlObjActionFlags(act);
            w->base.state = 0;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 28:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 8, 0, work->base.tiles);
            work->hoverZ = 0;
            FadeToAmount(0, gBtlWork->fadeAmount, 8);
        }

        if (AnimGetFrame(&w->base.anim) > 4 && BgFxIsActive() == 0) {
            m4aSongNumStart(SONG_VO_VIC_ATTACK02);
            m4aSongNumStart(SONG_BTL_VIC_ICEFALL);
            BgFxStartVixenIceFall(9999);
        }

        if ((s16)w->base.stateTimer % 15 == 0) {
            t = gBtlWork->actor->hp;

            if ((s16)t > 1) {
                gBtlWork->actor->hp = t - 1;
            }
        }

        if ((s16)w->base.stateTimer > 300 ||
            ((s16)w->base.stateTimer > 120 && (s16)gBtlWork->actor->hp <= 1)) {
            m4aSongNumStop(SONG_BTL_VIC_ICEFALL);
            FadeToOriginal(0, 8);
            gBtlWork->flags |= 0x400000;
            ClearBtlObjActionFlags(act);
            w->base.state = 0;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 29:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 9, 0, work->base.tiles);
            work->hoverZ = 0;
        }

        if (AnimIsFinished(&w->base.anim)) {
            w->base.stateTimer = 0;
            w->base.state = 30;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 30:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 10, 1, work->base.tiles);
        }

        if ((s16)w->base.stateTimer > 60) {
            w->base.stateTimer = 0;
            w->base.state = 31;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 31:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 11, 0, work->base.tiles);
        }

        if (AnimIsFinished(&w->base.anim)) {
            w->base.stateTimer = 0;
            w->base.state = 32;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 32:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 4, 0, work->base.tiles);
        }

        if (AnimGetFrame(&w->base.anim) == 3 && w->base.anim.timer == 0) {
            FadeStartIn(1, 60);
            VixenPlaceGroundIce(work);
        }

        if (AnimIsFinished(&w->base.anim) && FadeIsActive() == 0) {
            ClearBtlObjActionFlags(act);
            w->base.state = 0;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 33:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 12, 0, work->base.tiles);
            work->hoverZ = 0;
        }

        if (AnimIsFinished(&w->base.anim)) {
            w->base.stateTimer = 0;
            w->base.state = 34;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 34:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 13, 1, work->base.tiles);
        }

        if ((s16)w->base.stateTimer > 60) {
            w->base.stateTimer = 0;
            w->base.state = 35;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 35:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 14, 0, work->base.tiles);
            m4aSongNumStart(SONG_VO_VIC_ATTACK00);
        }

        if (AnimIsFinished(&w->base.anim)) {
            w->base.stateTimer = 0;
            w->base.state = 36;
        } else {
            w->base.stateTimer++;
        }
        break;
    case 36:
        if ((s16)w->base.stateTimer == 0) {
            AnimChangeWithDef(gHumVixenAnimDefs, &work->base.anim, 4, 0, work->base.tiles);
            work->task = 0;
        }

        if (AnimGetFrame(&w->base.anim) == 3 && w->base.anim.timer == 0) {
            args.x = x;
            args.y = y;
            args.z = 0;
            work->task = TaskCreate(&work->tasks, &gTaskDescHumVixenFrz, &args);
        }

        if (AnimIsFinished(&w->base.anim) &&
            IsTaskActiveNamed(work->task, gTaskDescHumVixenFrz.name) == 0) {
            ClearBtlObjActionFlags(act);
            w->base.state = 0;
            w->base.stateTimer = 0;
        } else {
            w->base.stateTimer++;
        }
        break;
    }

    if (!(act->flags & 0x2000) && act->badStatus != 2) {
        VixenHover(&w->base, work->hoverZ);
    }
    r = HumUpdate(&w->base);
    cx = gBtlWork->actor->x;
    ax = act->x;

    if ((cx < ax && (act->flags & 4)) || (cx > ax && !(act->flags & 4))) {
        act->flags |= 0x8000;
    } else {
        act->flags &= ~0x8000;
    }
    TaskPoolUpdate(&work->tasks);
    return r;
}

void task_hum_vixen_2(VixenWork* work) {
    HumDraw(&work->base);
    TaskPoolDraw(&work->tasks);
}

void task_hum_vixen_3(VixenWork* work) {
    if (gGameState.flags & 8) {
        ReleaseObjTiles(gBtlWork->tiles2);
    }
    HumReleaseResources(&work->base);
    TaskPoolDestroy(&work->tasks);
}

void task_hum_vixen_ndl_0(VixenNdlWork* work, VixenNdlArgs* args) {
    work->palette = LoadObjPalette(gVixEPalette, 0x20);
    work->tiles = args->tiles;
    AnimInit(&work->anim, gVixenE1Anims, gVixenE1Frames);
    AnimStart(&work->anim, 0, 0);
    work->hitPhase = args->unk_12;
    work->x = args->x;
    work->y = args->y + (GetRandom() % 11 - 5) * 256;
    work->z = args->z;
    work->hitDone = 0;
    m4aSongNumStart(SONG_BTL_VIC_ICEP);

    if ((GetRandom() & 1) != 0) {
        work->flipped = 1;
    } else {
        work->flipped = 0;
    }
}

u8 task_hum_vixen_ndl_1(VixenNdlWork* work) {
    if ((gBtlWork->flags & 0x40) == 0) {
        return 0;
    }

    if (AnimIsFinished(&work->anim)) {
        return 0;
    }

    switch (AnimGetFrame(&work->anim)) {
    case 1:
    case 2:
        if (work->hitDone == 0) {
            if (gFrameCounter % 8 == work->hitPhase) {
                ApplyAttackBox(0x13A, work->x, work->y, 0, 4, 4, 16);
            }
        }
        break;
    }

    if (gBtlWork->actor->flags & 0x2000) {
        work->hitDone = 1;
    }
    AnimUpdate(&work->anim);
    return 1;
}

void task_hum_vixen_ndl_2(VixenNdlWork* work) {
    s16 x;
    s16 y;
    void* gfx;
    u16 attr;

    gfx = AnimGetGfx(&work->anim);
    attr = GetBattleSpritePriorityFlags(work->y);

    if (work->flipped != 0) {
        attr |= 1;
    }
    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gfx, work->tiles, work->palette, 0, attr,
        -0x1004 - (work->y >> 8) * 4);
}

void task_hum_vixen_ndl_3(VixenNdlWork* work) {
    ReleaseObjPalette(work->palette);
}

void task_hum_vixen_ice_0(VixenIceWork* work, VixenSub* args) {
    work->palette = LoadObjPalette(gVixEPalette, 0x20);
    work->tiles = LoadObjTiles(gVixenE2Tiles, 0x800);
    work->sub = args;
    work->state = 3;
    AnimInit(&work->anim, gVixenE2Anims, gVixenE2Frames);
    AnimStart(&work->anim, 0, 0);
    ColliderInit(&work->collider, 12, 27, 1);
    ColliderSetDisabled(&work->collider, 1);
}

u8 task_hum_vixen_ice_1(VixenIceWork* work) {
    if (work->sub->active == 0) {
        if (work->sub->pending != 0) {
            FadeSetPaletteExcluded(((ObjPalette*)work->palette)->index + 16, 1);
            work->sub->pending = 0;
            ColliderSetDisabled(&work->collider, 1);
        }
        return 1;
    }

    if (work->sub->pending != 0) {
        FadeSetPaletteExcluded(((ObjPalette*)work->palette)->index + 16, 0);
        work->sub->pending = 0;
        work->state = 0;
        work->stateTimer = 0;
        work->scale = 10;

        switch (GetRandom() % 3) {
        case 0:
            work->targetScale = 0x100;
            break;
        case 1:
            work->targetScale = 0xC0;
            break;
        case 2:
            work->targetScale = 0x80;
            break;
        }
    }

    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            work->steps = 30;
            work->stateTimer++;
        }
        ApproachValue(&work->scale, work->targetScale, work->steps);
        work->steps--;
        if ((s16)work->steps <= 0) {
            ColliderSetDisabled(&work->collider, 0);
            work->state = 1;
            work->stateTimer = 0;
            work->lifetime = GetRandom() % 0x259 + 600;
        }
        break;
    case 1:
        if (work->stateTimer == 0) {
            AnimStart(&work->anim, 0, 0);
            work->stateTimer++;
        }

        if (GetRandom() % 300 == 0) {
            work->state = 2;
            work->stateTimer = 0;
        }
        break;
    case 2:
        if (work->stateTimer == 0) {
            AnimStart(&work->anim, 1, 0);
            work->stateTimer++;
        }

        if (AnimIsFinished(&work->anim)) {
            work->state = 1;
            work->stateTimer = 0;
        }
        break;
    }

    switch (work->state) {
    case 1:
    case 2:
        ApproachValue(&work->scale, 10, work->lifetime);
        work->lifetime--;
        if ((s16)work->lifetime <= 0) {
            work->sub->active = 0;
            work->sub->pending = 1;
        }
        ColliderSetRadius(&work->collider, work->scale * 27 >> 8);
        ColliderSetPosition(&work->collider, work->sub->x, work->sub->y, 0);
        break;
    }
    AnimUpdate(&work->anim);
    return 1;
}

void task_hum_vixen_ice_2(VixenIceWork* work) {
    s16 x;
    s16 y;
    void* gfx;
    s32 s;
    ObjAffine* affine;

    if (work->sub->active != 0) {
        gfx = AnimGetGfx(&work->anim);
        WorldToScreen(&x, &y, work->sub->x, work->sub->y, 0);
        s = work->scale * gBtlWork->scale >> 8;
        if (gBtlWork->rotation != 0 || s > 0x100) {
            affine = AllocObjAffine(gBtlWork->rotation, s, s, 1);
        } else {
            affine = AllocObjAffine(gBtlWork->rotation, s, s, 0);
        }
        DrawSprite(x, y, gfx, work->tiles, work->palette, affine, 0x800, 0xFFFF);
    }
}

void task_hum_vixen_ice_3(VixenIceWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

void task_hum_vixen_frz_0(VixenFrzWork* work, VixenNdlArgs* args) {
    work->palette = LoadObjPalette(gVixEPalette, 0x20);
    work->tiles = gBtlWork->tiles2;

    if (gGameState.flags & 8) {
        if (gBtlWork->flags & 0x800000000000) {
            work->variant = 2;
        } else {
            work->variant = 1;
        }
    } else {
        work->variant = 0;
    }
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(gHumVixenFrzAnimDefs, &work->anim, 0, 0, work->tiles);
    work->state = 0;

    if (gBtlWork->actor->flags & 4) {
        work->flipped = 0;
    } else {
        work->flipped = 1;
    }
    m4aSongNumStart(SONG_EF_BURIZA02);
    work->x = args->x;
    work->y = args->y;
    work->z = args->z;
}

u8 task_hum_vixen_frz_1(VixenFrzWork* work) {
    VixenNdlArgs args;
    VixenNdlArgs args2;

    if ((gBtlWork->flags & 0x40) == 0) {
        return 0;
    }

    switch (work->state) {
    case 1:
        if (work->timer == 0) {
            switch (work->variant) {
            case 0:
                AnimChangeWithDef(gHumVixenFrzAnimDefs, &work->anim, 2, 0, work->tiles);
                break;
            case 1:
                AnimChangeWithDef(gHumVixenFrzAnimDefs, &work->anim, 7, 0, work->tiles);
                break;
            case 2:
                AnimChangeWithDef(gHumVixenFrzAnimDefs, &work->anim, 10, 0, work->tiles);
                break;
            }
        }
        work->x = gBtlWork->actor->x;
        work->y = gBtlWork->actor->y;
        work->z = gBtlWork->actor->z;

        if (AnimIsFinished(&work->anim)) {
            work->state = 2;
            work->timer = 0;
        } else {
            work->timer++;
        }
        break;
    case 2:
        if (work->timer == 0) {
            switch (work->variant) {
            case 0:
                AnimChangeWithDef(gHumVixenFrzAnimDefs, &work->anim, 4, 0, work->tiles);
                break;
            case 1:
                AnimChangeWithDef(gHumVixenFrzAnimDefs, &work->anim, 8, 0, work->tiles);
                break;
            case 2:
                AnimChangeWithDef(gHumVixenFrzAnimDefs, &work->anim, 11, 0, work->tiles);
                break;
            }
        }
        work->x = gBtlWork->actor->x;
        work->y = gBtlWork->actor->y;
        work->z = gBtlWork->actor->z;

        if (gBtlWork->flags & 0x100000) {
            work->state = 3;
            work->timer = 0;
        } else {
            work->timer++;
        }
        break;
    case 3:
        if (work->timer == 0) {
            switch (work->variant) {
            case 0:
                AnimChangeWithDef(gHumVixenFrzAnimDefs, &work->anim, 6, 0, work->tiles);
                break;
            case 1:
                AnimChangeWithDef(gHumVixenFrzAnimDefs, &work->anim, 9, 0, work->tiles);
                break;
            case 2:
                AnimChangeWithDef(gHumVixenFrzAnimDefs, &work->anim, 12, 0, work->tiles);
                break;
            }
        }
        work->x = gBtlWork->actor->x;
        work->y = gBtlWork->actor->y;
        work->z = gBtlWork->actor->z;

        if (AnimIsFinished(&work->anim)) {
            args.x = work->x;
            args.y = work->y;
            args.z = work->z;
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumVixenFrg, &args);
            work->state = 6;
            work->timer = 0;
        } else {
            work->timer++;
        }
        break;
    case 0:
        if (!AnimIsFinished(&work->anim)) {
            break;
        }

        if (TestAttackBox(work->x, work->y, work->z, 8, 8, 1)) {
            gBtlWork->actor->x = work->x;
            gBtlWork->actor->y = work->y;
            gBtlWork->actor->z = work->z;
            gBtlWork->actor->flags |= 0x100000000200;
            work->state = 1;
            gBtlWork->flags &= ~0x100000;
            work->timer = 0;
        } else {
            work->state = 4;
            work->timer = 0;
        }
        break;
    case 4:
        if (work->timer == 0) {
            AnimChangeWithDef(gHumVixenFrzAnimDefs, &work->anim, 1, 0, work->tiles);
        }

        if (AnimIsFinished(&work->anim)) {
            work->state = 5;
            work->timer = 0;
        } else {
            work->timer++;
        }
        break;
    case 5:
        if (work->timer == 0) {
            AnimChangeWithDef(gHumVixenFrzAnimDefs, &work->anim, 5, 0, work->tiles);
        }

        if (AnimIsFinished(&work->anim)) {
            args2.x = work->x;
            args2.y = work->y;
            args2.z = work->z;
            TaskCreate(&gBtlWork->taskPools[0], &gTaskDescHumVixenFrg, &args2);
            work->state = 6;
            work->timer = 0;
        } else {
            work->timer++;
        }
        break;
    case 6:
        if (work->timer > 80) {
            return 0;
        }
        work->timer++;
        break;
    }
    AnimUpdate(&work->anim);
    return 1;
}

void task_hum_vixen_frz_2(VixenFrzWork* work) {
    s16 x;
    s16 y;
    void* gfx;
    u16 attr;

    if (work->state != 6) {
        gfx = AnimGetGfx(&work->anim);
        attr = GetBattleSpritePriorityFlags(work->y) | work->flipped;
        WorldToScreen(&x, &y, work->x, work->y, work->z);
        DrawSprite(x, y, gfx, work->tiles, work->palette, 0, attr,
            -0x1004 - (work->y >> 8) * 4);
    }
}

void task_hum_vixen_frz_3(VixenFrzWork* work) {
    ReleaseObjPalette(work->palette);
}

void task_hum_vixen_frg_0(VixenFrgWork* work, VixenNdlArgs* args) {
    VixenFrgSub* e;
    s32 i;
    s32 a;
    s32 b;

    InitObjTilesAtSlot(&work->tilesSlot, ((ObjTiles*)gBtlWork->tiles2)->index, gVixenReitouHahenTiles, 0x4C0);
    work->tiles = &work->tilesSlot;
    work->palette = LoadObjPalette(gVixEPalette, 0x20);
    work->timer = 0;
    work->blinking = 0;

    for (i = 0; i < 15; i++) {
        const VixenFrgDef* d = &gVixenFrgDefs[i];
        e = &work->sub[i];
        e->x = args->x + (d->x << 8);
        e->y = args->y;
        e->z = args->z + (d->z << 8);
        e->spriteFlags = d->spriteFlags;
        e->gfx = gVixenReitouHahenFrames[d->frame];
        e->vz = GetRandom() % 0x401 - 0x500;
        a = (u8)GetRandom();
        b = GetRandom() % 0x380;
        e->vx = gSineTable[a] * b >> 8;
        e->vy = -gSineTable[a + 64] * (b >> 1) >> 8;
    }
    m4aSongNumStart(SONG_EF_VIC_ICEBREAK);
}

u8 task_hum_vixen_frg_1(VixenFrgWork* work) {
    VixenFrgSub* e;
    s32 i;

    if (gBtlWork->flags & 0x200000) {
        return 0;
    }

    for (i = 0; i < 15; i++) {
        e = &work->sub[i];
        e->x += e->vx;
        e->y += e->vy;
        e->z += e->vz;
        e->vz += gBtlWork->gravity;

        if (e->z > 0) {
            e->z = 0;
            e->vz = -(e->vz >> 1);
            e->vx = e->vx >> 1;
            e->vy = e->vy >> 1;
        }
        ClampBattlePosition(&e->x, &e->y, 0, 0);
    }
    work->timer++;
    if (work->timer == 50) {
        work->blinking = 1;
    }

    if (work->timer > 70) {
        return 0;
    }
    return 1;
}

void task_hum_vixen_frg_2(VixenFrgWork* work) {
    VixenFrgSub* p;
    s16 x;
    s16 y;
    u16 attr;
    s32 i;

    if (work->blinking != 0) {
        if (work->timer & 1) {
            return;
        }
    }
    p = work->sub;

    for (i = 0; i < 15; i++) {
        attr = GetBattleSpritePriorityFlags(p[i].y) | p[i].spriteFlags;
        WorldToScreen(&x, &y, p[i].x, p[i].y, p[i].z);
        DrawSprite(x, y, p[i].gfx, work->tiles, work->palette, 0, attr,
            -0x1004 - (p[i].y >> 8) * 4);
    }
}

void task_hum_vixen_frg_3(VixenFrgWork* work) {
    ReleaseObjPalette(work->palette);
}

void LexceusHover(HumWork* work, s32 a) {
    BtlObj* act;
    s32 t;

    if (a != 0) {
        act = &work->actor;
        t = a + gSineTable[gFrameCounter * 4 % 256] * 3;
        work->vz = 0;
        act->z += (t - act->z) >> 4;
    }
}

void task_hum_lexceus_0(LexceusWork* work) {
    HumInit(&work->base, &gHumLexceusDef);
    work->flags = 0;
    work->hoverZ = 0;
    work->scaleSteps = 0;
    work->tiltSteps = 0;
    work->tilt = 0;
    work->targetTilt = 0;
    work->tiltSlide = 0;
    work->base.stockMoves = gHumLexceusStockMoves;
    TaskPoolInit(&work->tasks, 3);
}

u8 task_hum_lexceus_1(LexceusWork* work) {
    LexceusWork* w;
    BtlObj* act;
    BtlObj* p;
    VixenNdlArgs a1;
    VixenNdlArgs a2;
    s32 x;
    s32 y;
    s32 z;
    s16 dx;
    s16 dy;

    w = work;
    act = &work->base.actor;
    p = gBtlWork->actor;
    GetEnemyTargetPosition(act, &x, &y, &z);

    switch (_0800E434(&work->base)) {
    case 5:
        work->base.stateTimer = 0;
        work->base.steps = 0;

        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
            work->base.state = 21;
            break;
        case 37:
            work->base.state = 23;
            break;
        case 38:
        case 39:
            work->base.state = 27;
            break;
        case 0xF85E3F85:
            work->base.state = 25;
            break;
        }
        break;
    case 4:
        work->base.scaleX = work->targetScaleX = 0x100;
        work->base.scaleY = work->targetScaleY = 0x100;
        work->scaleSteps = 0;

        if (work->targetTilt != 0) {
            work->targetTilt = 0;
            work->tiltSteps = 420;
        }
        break;
    }
    HumChooseCardAction(&work->base, 3, 40, 40, 20);
    w->hoverZ = 0;

    switch (work->base.state) {
    case 12:
        AnimChangeWithDef(gHumLexceusAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        break;
    case 17:
    case 18:
        AnimChangeWithDef(gHumLexceusAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        break;
    case 0:
        AnimChangeWithDef(gHumLexceusAnimDefs, &w->base.anim, 0, 1, w->base.tiles);

        if (func_08081828()) {
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            if (GetRandom() % 80 == 0) {
                work->base.state = 8;
                work->base.stateTimer = 0;
                break;
            }
        }
        HumFaceTarget(&work->base, 10);
        work->base.stateTimer++;
        break;
    case 8:
        AnimChangeWithDef(gHumLexceusAnimDefs, &w->base.anim, 1, 1, w->base.tiles);
        w->hoverZ = -0x1000;
        work->base.targetX = x;
        work->base.targetY = y;

        if (AnimIsFinished(&work->base.anim)) {
            if (HumMoveToward(&work->base, work->base.targetX, work->base.targetY, 0x100)) {
                work->base.state = 0;
                work->base.stateTimer = 0;
                break;
            }
        }
        HumFaceTarget(&work->base, 10);
        work->base.stateTimer++;
        break;
    case 1:
        act->vx = act->vy = 0;
        work->base.vz = 0;

        if ((s16)work->base.stateTimer > 5) {
            break;
        }
        work->base.stateTimer = 6;
        act->invincibleTimer = 30;
        break;
    case 3:
    case 9:
    case 11:
    case 14:
        AnimChangeWithDef(gHumLexceusAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        break;
    case 25:
        if ((s16)work->base.stateTimer == 0) {
            m4aSongNumStart(SONG_SND_286);
            AnimChangeWithDef(gHumLexceusAnimDefs, &w->base.anim, 7, 0, w->base.tiles);
            gBtlWork->flags &= ~0x100000;
        }

        switch (AnimGetFrame(&work->base.anim)) {
        case 2:
            if (work->base.anim.timer == 0) {
                m4aSongNumStart(SONG_BTL_LEC_ROCKB2);
            }
            break;
        case 3:
            if (work->base.anim.timer == 0) {
                if (act->flags & 4) {
                    a1.x = act->x - 0x2000;
                    a1.unk_12 = 1;
                } else {
                    a1.x = act->x + 0x2000;
                    a1.unk_12 = 0;
                }
                a1.y = act->y;
                a1.z = 0;
                w->task = TaskCreate(&w->tasks, &gTaskDescHumLexRock, &a1);
            }
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 26;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 26:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumLexceusAnimDefs, &w->base.anim, 8, 0, w->base.tiles);
            gBtlWork->flags |= 0x100000;
        }

        if (IsTaskActiveNamed(w->task, gTaskDescHumLexRock.name)) {
            break;
        }

        if (!AnimIsFinished(&work->base.anim)) {
            break;
        }
        work->base.stateTimer = 0;
        work->base.state = 0;
        ClearBtlObjActionFlags(act);
        break;
    case 23:
        if ((s16)work->base.stateTimer == 0) {
            w->hoverZ = 0;
            AnimChangeWithDef(gHumLexceusAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            w->flags &= ~4;
            w->task = 0;
            m4aSongNumStart(SONG_SND_287);
        }

        if (AnimGetFrame(&work->base.anim) == 3) {
            if (work->base.anim.timer == 2) {
                if (act->flags & 4) {
                    a1.x = act->x - 0x1800;
                    a1.unk_12 = 1;
                } else {
                    a1.x = act->x + 0x1800;
                    a1.unk_12 = 0;
                }
                a1.y = act->y;
                a1.z = act->z - 0x6000;
                w->flags |= 4;
                w->task = TaskCreate(&w->tasks, &gTaskDescHumLexTmh, &a1);
            }
        }

        if (w->flags & 4) {
            if (IsTaskActiveNamed(w->task, gTaskDescHumLexTmh.name) == 0) {
                work->base.stateTimer = 0;
                work->base.state = 24;
                break;
            }
        }
        work->base.stateTimer++;
        break;
    case 24:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumLexceusAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
        }

        if (AnimGetFrame(&work->base.anim) == 2) {
            if (work->base.anim.timer == 10) {
                if (act->flags & 4) {
                    a2.x = act->x - 0x700;
                    a2.unk_12 = 1;
                } else {
                    a2.x = act->x + 0x700;
                    a2.unk_12 = 0;
                }
                a2.y = act->y;
                a2.z = act->z;
                TaskCreate(&w->tasks, &gTaskDescHumLexTmh0, &a2);
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }
        work->base.stateTimer++;
        break;
    case 21:
        if ((s16)work->base.stateTimer == 0) {
            w->hoverZ = 0;
            AnimReset(&work->base.anim);
            AnimChangeWithDef(gHumLexceusAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
            w->flags &= ~3;
#ifdef VERSION_EU
            if (act->btl->hcEffect == 49) {
                act->btl->hcEffectCount--;
            }
#endif
        }

        if (work->base.anim.timer == 0) {
            switch (AnimGetFrame(&work->base.anim)) {
            case 3:
                dx = 9;
                dy = 0;
                break;
            case 4:
                dx = 13;
                dy = 0;
                break;
            case 5:
                dx = 6;
                dy = 6;
                break;
            case 7:
                dx = -21;
                dy = -6;
                break;
            default:
                dx = 0;
                dy = 0;
                break;
            }

            if (!AnimIsFinished(&work->base.anim)) {
                if (act->flags & 4) {
                    act->x = act->x - (dx << 8);
                } else {
                    act->x = act->x + (dx << 8);
                }
                act->y = act->y + (dy << 8);
            }

            if (work->base.anim.timer == 0) {
                if (AnimGetGfxIndex(&work->base.anim) == 5) {
                    MakeOpponentsHittable();

                    if ((act->flags & 4)
                        ? ApplyAttackBox(0x144, act->x - 0x3C00, act->y, act->z, 24, 20, 30)
                        : ApplyAttackBox(0x144, act->x + 0x3C00, act->y, act->z, 24, 20, 30)) {
                        m4aSongNumStart(SONG_BTL_LEC_HIT);
                        w->flags |= 1;
                    }
                }
            }
        }

        if (w->flags & 1) {
            if (AnimGetFrame(&work->base.anim) == 6) {
                if (work->base.anim.timer == 19) {
                    w->flags |= 2;
                }
            }
        }

        if (w->flags & 2) {
            work->base.stateTimer = 0;
            work->base.state = 22;
            work->base.steps++;
        } else if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 22:
        if ((s16)work->base.stateTimer == 0) {
            w->hoverZ = 0;
            AnimReset(&work->base.anim);
            AnimChangeWithDef(gHumLexceusAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            w->flags &= ~1;
#ifdef VERSION_EU
            if (act->btl->hcEffect == 49) {
                act->btl->hcEffectCount--;
            }
#endif
        }

        if (work->base.anim.timer == 0) {
            if (AnimGetGfxIndex(&work->base.anim) == 1) {
                MakeOpponentsHittable();

                if (act->btl->hcEffect == 49) {
                    if ((act->flags & 4)
                        ? ApplyAttackBox(0x149, act->x - 0x2800, act->y, act->z, 24, 20, 55)
                        : ApplyAttackBox(0x149, act->x + 0x2800, act->y, act->z, 24, 20, 55)) {
                        m4aSongNumStart(SONG_BTL_LEC_HIT);
                        w->flags |= 1;
                    }
                } else {
                    if ((act->flags & 4)
                        ? ApplyAttackBox(0x145, act->x - 0x2800, act->y, act->z, 24, 20, 55)
                        : ApplyAttackBox(0x145, act->x + 0x2800, act->y, act->z, 24, 20, 55)) {
                        m4aSongNumStart(SONG_BTL_LEC_HIT);
                        w->flags |= 1;
                    }
                }
            }
        }

        if (AnimIsFinished(&work->base.anim)) {
            if (act->flags & 4) {
                act->x = act->x - 0x1900;
            } else {
                act->x = act->x + 0x1900;
            }
            AnimChangeWithDef(gHumLexceusAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
            work->base.stateTimer = 0;
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 27:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumLexceusAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
            w->hoverZ = 0;
            w->cameraBaseY = gBtlWork->y;
        }

        if (AnimGetFrame(&work->base.anim) == 3) {
            if (work->base.anim.timer == 0) {
                m4aSongNumStart(SONG_SND_288);
            }
        }

        switch (AnimGetFrame(&work->base.anim)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            HumFaceTarget(&work->base, 1);
            break;
        case 5:
            if (work->base.anim.timer == 0) {
                m4aSongNumStart(SONG_EF_AIRO);

                if ((act->flags & 4) == 0) {
                    w->targetTilt = -0x800;
                } else {
                    w->targetTilt = 0x800;
                }
                w->tiltSteps = 10;

                if (act->flags & 4) {
                    BgFxStartLexceusGround(act->x - 0x3000, act->y + 0xE00, 0, 0x147);
                } else {
                    BgFxStartLexceusGround(act->x + 0x3000, act->y + 0xE00, 0, 0x147);
                }
            }

            if ((s16)work->base.stateTimer % 6 <= 2) {
                gBtlWork->y2 = w->cameraBaseY - 0x4000;
            } else {
                gBtlWork->y2 = w->cameraBaseY + 0x4000;
            }
            break;
        case 6:
            if ((s16)work->base.stateTimer % 6 <= 2) {
                gBtlWork->y2 = w->cameraBaseY - 0x3000;
            } else {
                gBtlWork->y2 = w->cameraBaseY + 0x3000;
            }
            break;
        case 7:
            if ((s16)work->base.stateTimer % 6 <= 2) {
                gBtlWork->y2 = w->cameraBaseY - 0x2000;
            } else {
                gBtlWork->y2 = w->cameraBaseY + 0x2000;
            }
            break;
        case 8:
            if ((s16)work->base.stateTimer % 6 <= 2) {
                gBtlWork->y2 = w->cameraBaseY - 0x1000;
            } else {
                gBtlWork->y2 = w->cameraBaseY + 0x1000;
            }
            break;
        }

        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
            w->targetTilt = 0;
            w->tiltSteps = 420;
        } else {
            work->base.stateTimer++;
        }
        break;
    }

    if (!(act->flags & 0x2000)) {
        if (act->badStatus != 2) {
            LexceusHover(&work->base, w->hoverZ);
        }
    }

    if ((s16)w->tiltSteps > 0) {
        ApproachValue(&w->tilt, w->targetTilt, w->tiltSteps);
        w->tiltSteps--;
    }
    gBtlWork->rotation = w->tilt >> 8;

    if (p->z >= p->groundZ && (s16)p->hp > 0 && p->badStatus != 2 && !(p->flags & 16)) {
        w->tiltSlide += (GetAngleDiff(0, gBtlWork->rotation) * 64 - w->tiltSlide) >> 4;
        p->x -= w->tiltSlide;
    } else {
        w->tiltSlide = 0;
    }
    TaskPoolUpdate(&w->tasks);
    return HumUpdate(&work->base);
}

void task_hum_lexceus_2(LexceusWork* work) {
    HumDraw(&work->base);

    if (work->scaleSteps > 0) {
        ApproachValue(&work->base.scaleX, work->targetScaleX, work->scaleSteps);
        ApproachValue(&work->base.scaleY, work->targetScaleY, work->scaleSteps);
        work->scaleSteps--;
    }
    TaskPoolDraw(&work->tasks);
}

void task_hum_lexceus_3(LexceusWork* work) {
    HumReleaseResources(&work->base);
    TaskPoolDestroy(&work->tasks);
}

void task_hum_lex_tmh_0(LexTmhWork* work, VixenNdlArgs* args) {
    work->palette = LoadObjPalette(gRexeusPalette, 0x20);
    work->tiles = AllocObjTiles(0x400, gRexeusTmhAxTiles);
    AnimInit(&work->anim, gRexeusTmhAxAnims, gRexeusTmhAxFrames);
    AnimStart(&work->anim, 0, 1);

    if (args->unk_12 != 0) {
        work->facingLeft = 1;
    } else {
        work->facingLeft = 0;
    }
    work->x = args->x;
    work->y = args->y;
    work->z = args->z;
    work->targetX = gBtlWork->targetX + (GetRandom() % 65 - 32) * 256;
    work->targetY = gBtlWork->targetY + (GetRandom() % 33 - 16) * 256;
    work->state = 0;
    work->timer = 0;
    work->done = 0;
    work->vz = -0x980;
    work->tiles2 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    work->palette2 = LoadObjPalette(gBStatesPalette, 0x20);
    m4aSongNumStart(SONG_BTL_LEC_THRSW);
}

u8 task_hum_lex_tmh_1(LexTmhWork* work) {
    if ((gBtlWork->flags & 0x40) == 0) {
        return 0;
    }

    if (work->done != 0) {
        return 0;
    }

    switch (work->state) {
    case 0:
        work->x += (work->targetX - work->x) >> 4;
        work->y += (work->targetY - work->y) >> 4;
        work->z += work->vz;
        work->vz += 64;

        if (ApplyAttackBox(0x146, work->x, work->y, work->z, 16, 12, 16)) {
            m4aSongNumStart(SONG_BTL_LEC_THRHIT);
            work->timer = 0;
            work->state = 1;
        } else if (work->z >= 0) {
            m4aSongNumStart(SONG_BTL_LEC_THR);
            work->timer = 0;
            work->state = 1;
        } else {
            work->timer++;
        }
        break;
    case 1:
        if (work->timer == 0) {
            work->vz = -work->vz >> 1;

            if (gBtlWork->targetX < work->x) {
                work->flyLeft = 1;
            } else {
                work->flyLeft = 0;
            }
        }

        if (work->x < (gBtlWork->xMin - 32) << 8 ||
            work->x > (gBtlWork->xMax + 32) << 8) {
            work->done = 1;
        }

        if (work->flyLeft != 0) {
            work->x += -0x400;
        } else {
            work->x += 0x400;
        }
        work->y += (gBtlWork->targetY - work->y) >> 4;
        work->z += work->vz;
        work->vz += 64;

        if (ApplyAttackBox(0x146, work->x, work->y, work->z, 16, 12, 16)) {
            m4aSongNumStart(SONG_BTL_LEC_THRHIT);
        }

        if (work->z >= 0) {
            m4aSongNumStart(SONG_BTL_LEC_THR);
            work->vz = -work->vz >> 1;
            work->z = 0;
        }
        work->timer++;
        break;
    }
    AnimUpdate(&work->anim);
    return 1;
}

void task_hum_lex_tmh_2(LexTmhWork* work) {
    s16 x;
    s16 y;
    void* gfx;
    u16 attr;
    ObjAffine* affine;
    s32 scale;

    gfx = AnimGetGfx(&work->anim);

    if (work->facingLeft != 0) {
        attr = GetBattleSpritePriorityFlags(work->y);
    } else {
        attr = GetBattleSpritePriorityFlags(work->y) | 1;
    }
    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gfx, work->tiles, work->palette, 0, attr,
        -0x1004 - (work->y >> 8) * 4);

    if (work->z >= 0) {
        affine = 0;
    } else {
        scale = 0x100 - (-work->z) / 256;
        if (scale <= 75) {
            scale = 76;
        }
        affine = AllocObjAffine(0, scale, scale, 0);
    }
    WorldToScreen(&x, &y, work->x, work->y, 0);
    DrawSprite(x, y, gUnk_08B22BA8, work->tiles2, work->palette2, affine, attr, 0xFFF0);
}

void task_hum_lex_tmh_3(LexTmhWork* work) {
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette2);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_hum_lex_tmh0_0(LexTmh0Work* work, VixenNdlArgs* args) {
    work->palette = LoadObjPalette(gRexeusPalette, 0x20);
    work->tiles = AllocObjTiles(0x400, gRexeusTmhTiles);
    AnimInit(&work->anim, gRexeusTmhAnims, gRexeusTmhFrames);
    AnimStart(&work->anim, 2, 1);

    if (args->unk_12 != 0) {
        work->facingLeft = 1;
    } else {
        work->facingLeft = 0;
    }
    work->x = args->x;
    work->y = args->y;
    work->z = args->z;
    work->scale = 10;
    work->steps = 21;
    m4aSongNumStart(SONG_BTL_LEC_WEPUP);
}

u8 task_hum_lex_tmh0_1(LexTmh0Work* work) {
    if (gBtlWork->flags & 0x40) {
        ApproachValue(&work->scale, 0x100, work->steps--);

        if (work->steps > 0) {
            AnimUpdate(&work->anim);
            return 1;
        }
    }
    return 0;
}

void task_hum_lex_tmh0_2(LexTmh0Work* work) {
    void* gfx;
    u16 attr;
    s32 sx;
    s32 h;
    ObjAffine* affine;
    s16 x;
    s16 y;

    gfx = AnimGetGfx(&work->anim);
    attr = GetBattleSpritePriorityFlags(work->y);
    h = work->scale;
    if (h == 0x100) {
        if (work->facingLeft == 0) {
            attr |= 1;
        }
        sx = h;
    } else {
        if (work->facingLeft != 0) {
            sx = h;
        } else {
            sx = -h;
        }
    }
    affine = AllocObjAffine(0, sx, 0x100, 0);
    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gfx, work->tiles, work->palette, affine, attr,
        -0x100C - (work->y >> 8) * 4);
}

void task_hum_lex_tmh0_3(LexTmh0Work* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_hum_lex_rock_0(LexRockWork* work, VixenNdlArgs* args) {
    if (args->unk_12 != 0) {
        work->facingLeft = 1;
    } else {
        work->facingLeft = 0;
    }
    work->x = args->x;
    work->y = args->y;
    work->z = args->z;
    work->state = 0;
    work->rockCount = 0;
    work->tiles = LoadObjTiles(gUnk_08B22CE4, 0x200);
    work->palette = LoadObjPalette(gBStatesPalette, 0x20);
    work->blinking = 0;
}

u8 task_hum_lex_rock_1(LexRockWork* work) {
    s32 i;
    s32 range;
    LexRockSub* e;
    u32 v;

    if ((gBtlWork->flags & 0x40) == 0) {
        return 0;
    }

    switch (work->state) {
    case 0:
        work->rockCount = 1;
        work->palette2 = LoadObjPalette(gRexeusRock01Palette, 0x20);
        work->tiles2[0] = AllocObjTiles(0xDC0, gRexeusRock01Tiles);
        AnimInit(&work->anim[0], gRexeusRock01Anims, gRexeusRock01Frames);
        AnimStart(&work->anim[0], 0, 0);
        work->state++;
        break;
    case 1:
        if (!AnimIsFinished(&work->anim[0])) {
            break;
        }
        work->state++;
        break;
    case 2:
        ReleaseObjTiles(work->tiles2[0]);
        ReleaseObjPalette(work->palette2);
        work->rockCount = 1;
        work->palette2 = LoadObjPalette(gRexeusRock02Palette, 0x20);
        work->tiles2[0] = AllocObjTiles(0xDC0, gRexeusRock02Tiles);
        AnimInit(&work->anim[0], gRexeusRock02Anims, gRexeusRock02Frames);
        AnimStart(&work->anim[0], 0, 0);
        work->z -= 0x4000;
        work->state++;
        break;
    case 3:
        if (gBtlWork->flags & 0x100000) {
            m4aSongNumStart(SONG_BTL_LEC_JMPKUEIKU);
            work->state += 2;
        }
        break;
    case 4:
        if (!AnimIsFinished(&work->anim[0])) {
            break;
        }
        work->state++;
        break;
    case 5:
        work->rockCount = 12;
        ReleaseObjTiles(work->tiles2[0]);

        for (i = 0; i < 12; i++) {
            e = &work->sub[i];
            work->tiles2[i] = AllocObjTiles(0xC0, gRexeusRock02Tiles);
            AnimInit(&work->anim[i], gRexeusRock02Anims, gRexeusRock02Frames);
            AnimStart(&work->anim[i], GetRandom() % 5 + 2, 3);

            if (work->facingLeft != 0) {
                e->vx = -(GetRandom() % 0x501 + 0x300);
            } else {
                e->vx = GetRandom() % 0x501 + 0x300;
            }
            e->vy = GetRandom() % 0x801 - 0x400;
            e->x = work->x + ((GetRandom() % 17 - 8) << 8);
            e->y = work->y + ((GetRandom() % 17 - 8) << 8);
            e->z = work->z + ((GetRandom() % 17 - 8) << 8);
            e->hasHit = 0;

            if (GetRandom() % 2) {
                e->vz = -(GetRandom() % 0x701 + 0x100);
            } else {
                e->vz = GetRandom() % 1 + 0x300;
            }
        }
        work->state++;
        work->timer = 0;
        break;
    case 6:
        if (work->blinking == 0) {
            MakeOpponentsHittable();

            for (i = 0; i < 12; i++) {
                e = &work->sub[i];
                e->x += e->vx;
                e->y += e->vy;
                e->z += e->vz;
                e->vz += 64;

                if (e->z > 0) {
                    e->z = 0;
                    e->vz = -(e->vz >> 1);
                }
                v = ClampBattlePosition(&e->x, &e->y, 0, 0);

                switch (v) {
                case 3:
                case 4:
                    e->vy = -e->vy;
                    break;
                case 1:
                case 2:
                    e->vx = -e->vx;
                    break;
                }

                if (e->hasHit == 0) {
                    if (ApplyAttackBox(0x148, e->x, e->y, e->z, 4, 4, 4)) {
                        m4aSongNumStart(SONG_BTL_MON_HIT02);
                        e->hasHit = 1;
                    }
                }
            }
        }

        if (work->timer == 80) {
            work->blinking = 1;
        }

        if (work->timer > 100) {
            return 0;
        }
        work->timer++;
        break;
    }

    for (i = 0; i < work->rockCount; i++) {
        AnimUpdate(&work->anim[i]);
    }
    return 1;
}

void task_hum_lex_rock_2(LexRockWork* work) {
    void* gfx;
    u16 attr;
    s16 x;
    s16 y;
    s32 i;
    LexRockSub* e;

    if (work->blinking != 0 && (work->timer & 1)) {
        return;
    }

    if (work->rockCount == 1) {
        gfx = AnimGetGfx(&work->anim[0]);

        if (work->facingLeft != 0) {
            attr = GetBattleSpritePriorityFlags(work->y);
        } else {
            attr = GetBattleSpritePriorityFlags(work->y) | 1;
        }
        WorldToScreen(&x, &y, work->x, work->y, work->z);
        DrawSprite(x, y, gfx, work->tiles2[0], work->palette2, 0, attr,
            -0x1006 - (work->y >> 8) * 4);
    } else if (work->rockCount == 12) {
        for (i = 0; i < work->rockCount; i++) {
            e = &work->sub[i];
            gfx = AnimGetGfx(&work->anim[i]);

            if (work->facingLeft != 0) {
                attr = GetBattleSpritePriorityFlags(e->y);
            } else {
                attr = GetBattleSpritePriorityFlags(e->y) | 1;
            }
            WorldToScreen(&x, &y, e->x, e->y,
                e->z);
            DrawSprite(x, y, gfx, work->tiles2[i], work->palette2, 0, attr,
                -0x1006 - (e->y >> 8) * 4);
            WorldToScreen(&x, &y, e->x, e->y, 0);
            DrawSprite(x, y, gUnk_08B22CBC, work->tiles, work->palette, 0, attr, 0xFFFE);
        }
    }
}

void task_hum_lex_rock_3(LexRockWork* work) {
    s32 i;

    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);

    if (work->rockCount != 0) {
        ReleaseObjPalette(work->palette2);

        for (i = 0; i < work->rockCount; i++) {
            ReleaseObjTiles(work->tiles2[i]);
        }
    }
}

void task_hum_mahluxia_flw_0(MahluxiaFlwWork* work, VixenNdlArgs* args) {
    work->palette = LoadObjPalette(gMaruxhaBtEffPalette, 0x20);
    work->tiles = LoadObjTiles(gMaruxhaBtEff2Tiles, 0x100);
    work->state = 0;
    work->x = args->x;
    work->y = args->y;
    work->z = args->z;
    work->vx = GetRandom() % 717 - 358;
    work->vz = -(GetRandom() % 539 + 102);
    AnimInit(&work->anim, gMaruxhaBtEff2Anims, gMaruxhaBtEff2Frames);
    AnimStart(&work->anim, GetRandom() & 1, 1);
}

u8 task_hum_mahluxia_flw_1(MahluxiaFlwWork* work) {
    switch (work->state) {
    case 0:
        work->x += work->vx;
        work->z += work->vz;
        work->vz += 17;
        if (work->vz > 0x1CC) {
            work->state = 1;
        }
        break;
    case 1:
        work->x += work->vx;
        work->z += work->vz;
        work->vz -= 12;
        if (work->vz < 0) {
            work->vz = GetRandom() % 181 + 204;

            if (work->vx > 0) {
                work->vx = -(GetRandom() % 257 + 128);
            } else {
                work->vx = GetRandom() % 257 + 128;
            }
        }

        if (work->z >= 0) {
            return 0;
        }
        break;
    }
    AnimUpdate(&work->anim);
    return 1;
}

void task_hum_mahluxia_flw_2(MahluxiaFlwWork* work) {
    s16 x;
    s16 y;
    void* gfx;

    gfx = AnimGetGfx(&work->anim);
    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, gfx, work->tiles, work->palette, 0, 0x800,
        -0x1004 - (work->y >> 8) * 4);
}

void task_hum_mahluxia_flw_3(MahluxiaFlwWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void RikuJumpOffset(RikuWork* work, s16 a, s32 b) {
    HumWork* w = &work->base;
    BtlObj* act = &w->actor;

    if (act->flags & 4) {
        work->base.targetX = act->x - (a << 8);
    } else {
        work->base.targetX = act->x + (a << 8);
    }
    w->targetY = act->y;
    w->state = 19;
    w->stateTimer = 0;
    work->unk_1C4 = -b;
    work->unk_1C8 = 0;
}

void RikuJumpTo(RikuWork* work, s32 a, s32 b) {
    work->base.targetX = a;
    work->base.targetY = b;
    work->base.state = 19;
    work->base.stateTimer = 0;
    work->unk_1C4 = -0x500;
}

u8 RikuTryJumpAway(RikuWork* work) {
    s32 v;
    s32 w;
    BtlObj* c;

    c = gBtlWork->actor;

    if (GetRandom() % 30 == 0) {
        GetEnemyTargetPosition(&work->base.actor, &v, &w, 0);
        HumFaceTarget(&work->base, 1);

        if (HumIsInPlayerReach(&work->base, 0x100, 0x100, 0x100)) {
            if (gBtlWork->flags & 0x8000) {
                RikuJumpOffset(work, -99, 0x280);
            } else if (GetRandom() & 1) {
                if (c->flags & 4) {
                    RikuJumpTo(work, v + 0x2800, w);
                } else {
                    RikuJumpTo(work, v - 0x2800, w);
                }
            } else {
                RikuJumpOffset(work, -80, 0x500);
            }
            return 1;
        }
    }
    return 0;
}

void RikuSaveAfterimage(RikuWork* work, RikuSpawn* dst) {
    BtlObj* act = &work->base.actor;

    dst->x = act->x;
    dst->y = act->y;
    dst->z = act->z;

    if (act->flags & 4) {
        dst->flags |= 1;
    } else {
        dst->flags &= 0xFFFE;
    }
    dst->anim = work->base.anim;
    dst->tileSrc = work->base.tiles->src;
    dst->scale = gBtlWork->scale;
}

void RikuDrawAfterimage(RikuWork* work, RikuSpawn* p) {
    BtlObj* act;
    HumSub* sub;
    void* gfx;
    u16 attr;
    s32 sx;
    s32 sy;
    ObjAffine* affine;
    s16 x;
    s16 y;
    u16 pri;

    sub = work->base.sub;
    gfx = AnimGetGfx(&p->anim);
    act = &work->base.actor;

    if (BgFxIsActive() == 0) {
        gBldCnt = (BLDCNT_TGT1_OBJ | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
        SetBlendAlpha(6, 12);
        attr = 0x804;
    } else {
        attr = GetBattleSpritePriorityFlags(act->y);
    }

    if (p->flags & 1) {
        sy = p->scale;
        sx = sy;
    } else if (p->scale == 0x100) {
        sy = p->scale;
        sx = sy;
        attr |= 1;
    } else {
        sx = -gBtlWork->scale;
        sy = gBtlWork->scale;
    }

    if (sy == 0x100 && sx == sy) {
        affine = 0;
    } else if (sy <= 255) {
        affine = AllocObjAffine(0, sx, sy, 0);
    } else {
        affine = AllocObjAffine(0, sx, sy, 1);
    }
    pri = 0xFFF0;
    WorldToScreen(&x, &y, p->x, p->y, p->z);
    SetObjTileSource(sub->tiles, p->tileSrc);
    DrawSprite(x, y, gfx, sub->tiles, work->base.palette, affine, attr, pri);
}

void task_hum_riku_0(RikuWork* work) {
    HumInit(&work->base, &gHumRikuDef);
    HumSubInit(&work->base, &work->sub, &gHumRikuSubDef);
    work->unk_1C4 = 0;
    work->flags = 0;
    work->sub.flags |= 3;
    work->unk_1CC = 0;

    if (gBtlWork->battleId != 0xA1) {
        work->base.stockMoves = gHumRikuStockMoves[0];
    }
    RikuSaveAfterimage(work, &work->spawns[0]);
    work->spawns[1] = work->spawns[0];
    work->spawns[2] = work->spawns[0];
    work->spawns[3] = work->spawns[0];
    work->spawns[4] = work->spawns[0];
    work->spawns[5] = work->spawns[0];
    work->spawns[6] = work->spawns[0];
    work->spawns[7] = work->spawns[0];
    work->spawns[8] = work->spawns[0];
}

u8 task_hum_riku_1(RikuWork* work) {
    RikuWork* w;
    BtlObj* act;
    s32 x;
    s32 y;
    s32 z;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &x, &y, &z);
    work->flags &= ~4;
    switch (_0800E434(&work->base)) {
    case 5:
        work->base.stateTimer = 0;
        switch ((u32)HumResolveCardMove(&work->base)) {
        case 36:
            work->base.state = 24;
            break;
        case 37:
            work->base.state = 22;
            break;
        case 38:
            work->base.state = 23;
            break;
        case 39:
            work->base.state = 25;
            break;
        case 0xF0DBE6F9:
            work->base.state = 29;
            break;
        case 0xF17C0F03:
            work->base.state = 30;
            break;
        }
        break;
    case 4:
        work->base.flags &= ~8;
        work->base.scaleX = 256;
        break;
    }
    switch (gBtlWork->battleId) {
    case 161:
        HumChooseCardAction(&work->base, 20, 40, 40, 20);
        break;
    case 168:
    case 171:
        if (HumChooseCardAction(&work->base, 15, 40, 40, 20)) {
            work->base.stockMoves = gHumRikuStockMoves[0];
        }
        break;
    case 169:
        if (HumChooseCardAction(&work->base, 10, 40, 40, 20)) {
            work->base.stockMoves = gHumRikuStockMoves[0];
        }
        break;
    case 170:
    case 172:
        if (HumChooseCardAction(&work->base, 3, 40, 40, 20)) {
            if ((u16)GetRandom() % 2) {
                work->base.stockMoves = gHumRikuStockMoves[0];
            } else {
                work->base.stockMoves = gHumRikuStockMoves[1];
            }
        }
        break;
    }
    switch (work->base.state) {
    case 12:
    case 18:
        AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        break;
    case 17:
        AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 0, 3, w->base.tiles);
        if ((gBtlWork->flags & 0x20000000) && RikuTryJumpAway(w)) {
            break;
        }
        if ((act->x - x >= 0 ? act->x - x : x - act->x) <= 0x4FFF) {
            if (x < 0x10000) {
                RikuJumpTo(w, (gBtlWork->xMax - 40) << 8, (gBtlWork->yMin + gBtlWork->yMax) << 7);
            } else {
                RikuJumpTo(w, (gBtlWork->xMin + 40) << 8, (gBtlWork->yMin + gBtlWork->yMax) << 7);
            }
        }
        break;
    case 0:
        AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        if (func_08081828()) {
            break;
        }
        if (AnimIsFinished(&work->base.anim) && (u16)((u16)GetRandom() % 60) == 0) {
            work->base.state = 8;
            work->base.stateTimer = 0;
            break;
        }
        if (HumIsNearAreaEdge(&work->base, 40)) {
            RikuJumpTo(w, 0x10000, (gBtlWork->yMin + gBtlWork->yMax) << 7);
            break;
        }
        if (gBtlWork->flags & 0x20000000) {
            if (RikuTryJumpAway(w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 60);
        }
        work->base.stateTimer++;
        break;
    case 8:
        AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 1, 1, w->base.tiles);
        work->base.targetX = x;
        work->base.targetY = y;
        if (HumMoveToward(&work->base, work->base.targetX, work->base.targetY, 512) && AnimIsFinished(&work->base.anim)) {
            work->base.state = 0;
            work->base.stateTimer = 0;
            break;
        }
        if ((u16)((u16)GetRandom() % 500) == 0 && (act->x - x >= 0 ? act->x - x : x - act->x) > 70) {
            RikuJumpTo(w, x, y);
            break;
        }
        if (gBtlWork->flags & 0x20000000) {
            if (RikuTryJumpAway(w)) {
                break;
            }
        } else {
            HumFaceTarget(&work->base, 1);
        }
        work->base.stateTimer++;
        break;
    case 3:
    case 9:
    case 11:
    case 14:
        AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        break;
    case 1:
        AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
        if ((s16)work->base.stateTimer == 3) {
            switch ((s32)(u16)((u16)GetRandom() % 3)) {
            case 0:
                m4aSongNumStart(SONG_VO_RK_DAMAGE00);
                break;
            case 1:
                m4aSongNumStart(SONG_VO_RK_DAMAGE01);
                break;
            case 2:
            default:
                m4aSongNumStart(SONG_VO_RK_DAMAGE02);
                break;
            }
        }
        break;
    case 30:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 14, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_RK_ATTACK08);
            m4aSongNumStart(SONG_BTL_AN_STANDENTRY);
            FadeStartOut(9, 80);
        }
        work->base.vz = 0;
        act->z += (-0x2800 - act->z) >> 5;
        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 31;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 31: {

        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 15, 0, w->base.tiles);
        }
        switch (AnimGetFrame(&work->base.anim)) {
        case 1:
        case 2:
            work->base.vz -= 179;
            break;
        }
        w->flags |= 4;
        if (act->flags & 4) {
            s32 t = act->x - 0x3000;
            act->x += (act->originX - t) >> 3;
        } else {
            s32 t = act->x + 0x3000;
            act->x += (act->originX - t) >> 3;
        }
        if (AnimIsFinished(&work->base.anim)) {
            work->base.state = 32;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    }
    case 32:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 16, 0, w->base.tiles);
            work->base.flags |= 8;
        }
        work->base.vz = 0;
        w->flags |= 4;
        if (act->flags & 4) {
            act->x -= 0xC00;
        } else {
            act->x += 0xC00;
        }
        if (act->x < ((gBtlWork->xMin - 48) << 8) ||
            act->x > ((gBtlWork->xMax + 48) << 8)) {
            work->base.state = 33;
            work->base.stateTimer = 0;
            w->dashCount = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 33:
        if ((s16)work->base.stateTimer == 0) {
            act->flags ^= 4;
            switch ((u16)((u16)GetRandom() % 3)) {
            case 0:
                AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 17, 1, w->base.tiles);
                if (act->flags & 4) {
                    w->unk_1C4 = (u16)((u16)GetRandom() % 17) + 184;
                } else {
                    w->unk_1C4 = (u16)((u16)GetRandom() % 17) + 56;
                }
                act->y = y + (((u16)((u16)GetRandom() % 33) - 16) << 8);
                break;
            case 1:
                AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 18, 1, w->base.tiles);
                if (act->flags & 4) {
                    w->unk_1C4 = (u16)((u16)GetRandom() % 17) + 203;
                } else {
                    w->unk_1C4 = (u16)((u16)GetRandom() % 17) + 37;
                }
                act->y = y + (((u16)((u16)GetRandom() % 17) + 16) << 8);
                break;
            case 2:
                AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 19, 1, w->base.tiles);
                if (act->flags & 4) {
                    w->unk_1C4 = (u16)((u16)GetRandom() % 17) + 165;
                } else {
                    w->unk_1C4 = (u16)((u16)GetRandom() % 17) + 75;
                }
                act->y = y - (((u16)((u16)GetRandom() % 17) + 16) << 8);
                break;
            }
            act->z = -0x1000;
            if (act->flags & 4) {
                act->x = x + 0x6300;
                BgFxStartRikuLimit(act->x, act->y, act->z, 192);
            } else {
                act->x = x - 0x6300;
                BgFxStartRikuLimit(act->x, act->y, act->z, 64);
            }
            m4aSongNumStart(SONG_BTL_RK_LIMITENTRY);
            work->base.steps = 10;
            work->base.scaleX = 10;
        }
        work->base.vz = 0;
        BtlMapFollowPosition(gBtlWork->actor->x, gBtlWork->actor->y, gBtlWork->actor->z);
        ApproachValue(&work->base.scaleX, 256, (u16)work->base.steps);
        work->base.steps--;
        if ((s16)work->base.steps <= 0) {
            work->base.state = 34;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 34:
        if ((s16)work->base.stateTimer == 0) {
            m4aSongNumStart(SONG_EF_RK_LIMITMOV);
            MakeOpponentsHittable();
        }
        w->flags |= 4;
        act->x += gSineTable[(u8)w->unk_1C4] * 12;
        act->y += -gSineTable[(u8)w->unk_1C4 + 64] * 12;
        if (ApplyAttackBox(295, act->x, act->y, act->z, 24, 16, 24)) {
            m4aSongNumStart(SONG_BTL_RK_HIT03);
        }
        work->base.vz = 0;
        BtlMapFollowPosition(gBtlWork->actor->x, gBtlWork->actor->y, gBtlWork->actor->z);
        if ((s16)work->base.stateTimer == 15 && (s16)w->dashCount > 4) {
            work->base.state = 35;
            work->base.stateTimer = 0;
        } else if ((s16)work->base.stateTimer > 30) {
            work->base.state = 33;
            work->base.stateTimer = 0;
            w->dashCount++;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 35:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 20, 0, w->base.tiles);
            work->base.steps = 40;
        }
        if ((s16)work->base.steps > 0) {
            ApproachValue(&act->x, act->originX, (u16)work->base.steps);
            ApproachValue(&act->y, act->originY, (u16)work->base.steps);
            ApproachValue(&act->z, act->originZ, (u16)work->base.steps);
            work->base.steps--;
            if ((s16)work->base.steps <= 0) {
                BgFxStartRikuLimitFinish(act->x, act->y - 0x2000, 0);
            }
        }
        if (!BgFxIsActive() && (s16)work->base.steps <= 0 && AnimIsFinished(&work->base.anim)) {
            work->base.flags &= ~8;
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            FadeStartIn(9, 30);
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 24:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 10, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_RK_ATTACK02);
        }
        if (work->base.anim.timer == 0) {
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 1:
                work->base.vz = -972;
                break;
            case 4:
                work->base.vz = 0x1000;
                if (act->flags & 4 ?
                    ApplyAttackBox(293, act->x - 0x2000, act->y, act->z, 28, 16, 16) :
                    ApplyAttackBox(293, act->x + 0x2000, act->y, act->z, 28, 16, 16)) {
                    m4aSongNumStart(SONG_BTL_RK_HIT00);
                }
                break;
            }
        }
        switch (AnimGetFrame(&work->base.anim)) {
        case 1:
        case 2:
        case 3: {

            if (act->flags & 4) {
                s32 t = act->x + 0x3200;
                act->x += (act->originX - t) >> 3;
            } else {
                s32 t = act->x - 0x3200;
                act->x += (act->originX - t) >> 3;
            }
            break;
        }
        }
        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 29:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 13, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_RK_ATTACK08);
            w->flags &= ~2;
            HumFaceTarget(&work->base, 1);
        }
        if (w->flags & 2) {
            BtlObj* p = gBtlWork->actor;
            if (p != 0) {
                s32 follow = 0;
                if (act->flags & 4) {
                    if (p->x < act->x - 0x2000) {
                        follow = 1;
                    }
                } else {
                    if (p->x > act->x + 0x2000) {
                        follow = 1;
                    }
                }
                if (follow) {
                    BgFxSetTarget(p->x, p->y, p->z - ((s16)p->centerHeight << 8));
                }
            }
        }
        if (!(w->flags & 2) && work->base.anim.timer == 0) {
            s16 d = 0;
            s32 spawn = 0;
            switch (AnimGetFrame(&work->base.anim)) {
            case 0:
                d = -10;
                break;
            case 1:
                d = -24;
                break;
            case 4:
                d = 12;
                break;
            case 5:
                d = 15;
                break;
            case 6:
                d = 7;
                spawn = 1;
                break;
            }
            if (act->flags & 4) {
                act->x -= d << 8;
            } else {
                act->x += d << 8;
            }
            if (spawn) {
                w->flags |= 2;
                if (act->flags & 4) {
                    BgFxStartFire(3, act->x - 0x4A00, act->y, act->z - 0x1800,
                        act->originX - 0xC800, act->originY, act->z - 0x1800, 1, 296);
                } else {
                    BgFxStartFire(3, act->x + 0x4A00, act->y, act->z - 0x1800,
                        act->originX + 0xC800, act->originY, act->z - 0x1800, 0, 296);
                }
            }
        }
        if (AnimIsFinished(&work->base.anim)) {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        }
        if (AnimIsFinished(&work->base.anim) && !BgFxIsActive()) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 23:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 9, 0, w->base.tiles);
            m4aSongNumStart((u16)GetRandom() % 2 + 259);
        }
        if (work->base.anim.timer == 0) {
            s32 d = 0;
            s32 hit = 0;
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 2:
                d = 4;
                break;
            case 3:
                d = 16;
                hit = 1;
                break;
            case 4:
                d = 5;
                break;
            case 6:
                d = 1;
                break;
            case 7:
                d = 4;
                hit = 1;
                break;
            case 8:
                d = 6;
                break;
            case 9:
            case 10:
                d = 2;
                break;
            }
            if (act->flags & 4) {
                act->x -= d << 8;
            } else {
                act->x += d << 8;
            }
            if (hit) {
                MakeOpponentsHittable();
                if (act->flags & 4 ?
                    ApplyAttackBox(292, act->x - 0x1400, act->y, act->z, 30, 16, 16) :
                    ApplyAttackBox(292, act->x + 0x1400, act->y, act->z, 30, 16, 16)) {
                    m4aSongNumStart(SONG_BTL_RK_HIT01);
                }
            }
        }
        switch (AnimGetFrame(&work->base.anim)) {
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            if (act->flags & 4) {
                act->x -= 256;
            } else {
                act->x += 256;
            }
            break;
        }
        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 22:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 8, 0, w->base.tiles);
            m4aSongNumStart((u16)GetRandom() % 2 + 259);
        }
        if (AnimGetGfxIndex(&work->base.anim) == 6) {

            w->flags |= 4;
            if (act->flags & 4) {
                s32 t = act->x + 0x5800;
                act->x += (act->originX - t) >> 2;
            } else {
                s32 t = act->x - 0x5800;
                act->x += (act->originX - t) >> 2;
            }
        }
        if (work->base.anim.timer == 0) {
            s16 d = 0;
            s32 hit = 0;
            s32 attack = 290;
            switch (AnimGetGfxIndex(&work->base.anim)) {
            case 1:
                d = 15;
                break;
            case 2:
                d = 5;
                hit = 1;
                attack = 290;
                break;
            case 4:
                d = -5;
                break;
            case 5:
                d = 10;
                break;
            case 6:
                d = 20;
                hit = 1;
                attack = 291;
                break;
            case 7:
                d = -9;
                break;
            case 8:
                d = 6;
                break;
            case 9:
                d = 1;
                break;
            }
            if (act->flags & 4) {
                act->x -= d << 8;
            } else {
                act->x += d << 8;
            }
            if (hit) {
                MakeOpponentsHittable();
                if (act->flags & 4 ?
                    ApplyAttackBox(attack, act->x - 0x1400, act->y, act->z, 20, 8, 16) :
                    ApplyAttackBox(attack, act->x + 0x1400, act->y, act->z, 20, 8, 16)) {
                    m4aSongNumStart(SONG_BTL_RK_HIT01);
                    if (attack == 291) {
                        FadeStartIn(2, 45);
                        if (act->flags & 4) {
                            SetBattleZoom(6, 332, act->x - 0x2000, (act->y - 0x1800) + act->z);
                        } else {
                            SetBattleZoom(6, 332, act->x + 0x2000, (act->y - 0x1800) + act->z);
                        }
                    }
                }
            }
        }
        if (work->base.anim.timer == 2 && AnimGetGfxIndex(&work->base.anim) == 6) {
            SetBattleZoom(8, 256, gBtlWork->x2, gBtlWork->y2);
        }
        if (AnimIsFinished(&work->base.anim)) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 25:
        if (act->z < act->groundZ) {
            break;
        }
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
            m4aSongNumStart(SONG_VO_RK_ATTACK02);
        }
        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 26;
            work->base.vz = -0x600;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 26:
        act->x += (x - act->x) >> 4;
        act->y += (y - act->y) >> 4;
        if ((s32)work->base.vz < 0) {
            if ((s32)work->base.vz > -0x200) {
                AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            }
        } else {
            work->base.stateTimer = 0;
            work->base.state = 27;
            break;
        }
        work->base.stateTimer++;
        break;
    case 27:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 11, 0, w->base.tiles);
            w->flags &= ~1;
        }
        act->x += (x - act->x) >> 4;
        act->y += (y - act->y) >> 4;
        if (AnimGetFrame(&work->base.anim) > 1) {
            if (ApplyAttackBox(294, act->x, act->y, act->z, 10, 10, 4)) {
                m4aSongNumStart(SONG_BTL_RK_HIT02);
                w->flags |= 1;
            }
        }
        if ((w->flags & 1) || act->z >= act->groundZ) {
            work->base.stateTimer = 0;
            work->base.state = 28;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 28:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 12, 0, w->base.tiles);
            work->base.vz = -0x400;
            if (act->flags & 4) {
                work->base.targetX = act->x + 0x3000;
            } else {
                work->base.targetX = act->x - 0x3000;
            }
        }
        act->x += ((s32)work->base.targetX - act->x) >> 3;
        if (AnimIsFinished(&work->base.anim) && act->z >= act->groundZ) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 19:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
        }
        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 20;
            work->base.vz = w->unk_1C4;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 20:
        act->x += ((s32)work->base.targetX - act->x) >> 4;
        act->y += ((s32)work->base.targetY - act->y) >> 4;
        if ((s32)work->base.vz < 0) {
            if ((s32)work->base.vz <= -0x200) {
                AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            } else {
                AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
            }
        } else if ((s32)work->base.vz <= 0x1FF) {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 5, 0, w->base.tiles);
        } else {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 6, 0, w->base.tiles);
        }
        if (act->z >= 0) {
            work->base.stateTimer = 0;
            work->base.state = 21;
            break;
        }
        HumFaceTarget(&work->base, 1);
        work->base.stateTimer++;
        break;
    case 21:
        if ((s16)work->base.stateTimer == 0) {
            AnimChangeWithDef(gHumRikuAnimDefs, &w->base.anim, 7, 0, w->base.tiles);
        }
        if (AnimIsFinished(&work->base.anim)) {
            work->base.stateTimer = 0;
            work->base.state = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    }
    return HumUpdate(&work->base);
}

void task_hum_riku_2(RikuWork* work) {
    HumDraw(&work->base);

    if ((work->flags & 4) && (work->sub.flags & 2)) {
        switch (work->unk_1CC % 2) {
        case 0:
            RikuDrawAfterimage(work, &work->spawns[2]);
            break;
        case 1:
            RikuDrawAfterimage(work, &work->spawns[4]);
            break;
        }
        work->unk_1CC++;
    }
    work->spawns[4] = work->spawns[3];
    work->spawns[3] = work->spawns[2];
    work->spawns[2] = work->spawns[1];
    work->spawns[1] = work->spawns[0];
    RikuSaveAfterimage(work, &work->spawns[0]);
}

void task_hum_riku_3(HumWork* work) {
    HumReleaseResources(work);
}

void task_hum_leon_0(LeonWork* work) {
    HumInit(&work->base, &gHumLeonDef);
    work->flashTimer = 0;
    work->unk_18A = 0;
    AnimChangeWithDef(gHumLeonAnimDefs, &work->base.anim, 0, 1, work->base.tiles);
    work->savedLearnedStocks = gGameState.progression.learnedStocks;
    work->savedLearnedStocks2 = gGameState.progression.learnedStocks2;
    gGameState.progression.learnedStocks = 0;
    gGameState.progression.learnedStocks2 = 0;
}

u8 task_hum_leon_1(LeonWork* work) {
    LeonWork* w;
    BtlObj* act;
    s32 x;
    s32 y;
    s32 z;
    s32 a;
    s32 b;
    s32 c;
    u8 r;

    w = work;
    act = &work->base.actor;
    GetEnemyTargetPosition(act, &a, &b, &c);

    switch (_0800E434(&work->base)) {
    case 4:
        break;
    case 5:
        work->base.state = 19;
        work->base.stateTimer = 0;
        break;
    }
    HumFaceTarget(&work->base, 1);

    switch (work->base.state) {
    case 12:
        AnimChangeWithDef(gHumLeonAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
        break;
    case 0:
        if (gBtlWork->flags & 0x20000000000) {
            if (w->unk_18A == 0) {
                AnimChangeWithDef(gHumLeonAnimDefs, &w->base.anim, 1, 0, w->base.tiles);
                w->unk_18A = 1;
            } else if (AnimIsFinished(&work->base.anim)) {
                AnimChangeWithDef(gHumLeonAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
            }
        } else {
            if (w->unk_18A != 0) {
                AnimChangeWithDef(gHumLeonAnimDefs, &w->base.anim, 2, 0, w->base.tiles);
                w->unk_18A = 0;
            } else if (AnimIsFinished(&work->base.anim)) {
                AnimChangeWithDef(gHumLeonAnimDefs, &w->base.anim, 0, 1, w->base.tiles);
            }
        }

        if (gBtlWork->flags & 0x100000) {
            if (gBtlWork->flags & 0x20000000) {
                work->base.state = 20;
                work->base.stateTimer = 0;
            }
        }
        break;
    case 1:
        if ((s16)work->base.stateTimer == 0) {
            ClearBtlObjActionFlags(act);
            AnimChangeWithDef(gHumLeonAnimDefs, &w->base.anim, 4, 0, w->base.tiles);
            work->base.stateTimer = 8;
        }
        break;
    case 2:
        if (gBtlWork->flags & 0x100000) {
            if (gBtlWork->flags & 0x20000000) {
                work->base.state = 20;
                work->base.stateTimer = 0;
            }
        }
        break;
    case 20:
        if ((s16)work->base.stateTimer > 10) {
            gBtlWork->rikuKeys |= 32;
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    case 19:
        if ((s16)work->base.stateTimer > 80) {
            ClearBtlObjActionFlags(act);
            work->base.state = 0;
            work->base.stateTimer = 0;
        } else {
            work->base.stateTimer++;
        }
        break;
    default:
        AnimChangeWithDef(gHumLeonAnimDefs, &w->base.anim, 3, 0, w->base.tiles);
        HumFaceTarget(&work->base, 1);
        break;
    }

    if ((s16)w->flashTimer > 0) {
        w->flashTimer--;
        act->flags |= 0x2000;
    } else {
        act->flags &= ~0x2000;
    }
    x = act->x;
    y = act->y;
    z = act->z;
    r = HumUpdate(&work->base);
    act->x = x;
    act->y = y;
    act->z = z;
    return r;
}

void task_hum_leon_2(HumWork* work) {
    HumDraw(work);
}

void task_hum_leon_3(LeonWork* work) {
    gGameState.progression.learnedStocks = work->savedLearnedStocks;
    gGameState.progression.learnedStocks2 = work->savedLearnedStocks2;
    HumReleaseResources(&work->base);
}

void task_hum_robe_0(RobeWork* work) {
    HumInit(&work->base, &gHumRobeDef);
    work->idleAnim = 1;
    AnimChangeWithDef(gHumRobeAnimDefs, &work->base.anim, 0, 1, work->base.tiles);
}

u8 task_hum_robe_1(RobeWork* work) {
    BtlObj* act = &work->base.actor;
    s32 x;
    s32 y;
    s32 z;
    u8 r;

    if (_0800E434(&work->base) == 1) {
        work->base.stateTimer = 1;
    }

    if (gBtlWork->flags & 0x20000000) {
        if (work->idleAnim == 1) {
            AnimChangeWithDef(gHumRobeAnimDefs, &work->base.anim, 1, 0, work->base.tiles);
            work->idleAnim = 0;
        }
    } else if (AnimIsFinished(&work->base.anim)) {
        AnimChangeWithDef(gHumRobeAnimDefs, &work->base.anim, 0, 1, work->base.tiles);
        work->idleAnim = 1;
    }
    HumFaceTarget(&work->base, 1);
    x = act->x;
    y = act->y;
    z = act->z;
    r = HumUpdate(&work->base);
    act->x = x;
    act->y = y;
    act->z = z;
    return r;
}

void task_hum_robe_2(HumWork* work) {
    HumDraw(work);
}

void task_hum_robe_3(HumWork* work) {
    HumReleaseResources(work);
}

void MakeSaveHeaderData(SaveHeaderData* data, s16 file) {
    s16 i;

    data->flags = 0;

    if (gGameState.flags & 0x20) {
        data->flags = 1;
    }

    if (gGameState.flags & 0x800) {
        data->flags |= 4;

        if (gGameState.flags & 8) {
            data->flags |= 2;
        } else {
            data->flags &= ~2;
        }
    } else if (gGameState.flags & 0x20) {
        data->flags |= 2;
    }

#ifdef VERSION_EU
    data->language = gLanguage;
#endif

    for (i = 0; i < 4; i++) {
        if (file == i) {
            data->files[i].floor = gGameState.floor;
            data->files[i].world = gGameState.world;
            data->files[i].level = gGameState.progression.level;
            data->files[i].playTime = gGameState.playTime;
        } else {
            data->files[i].floor = gGameState.fileSummaries[i].floor;
            data->files[i].world = gGameState.fileSummaries[i].world;
            data->files[i].level = gGameState.fileSummaries[i].level;
            data->files[i].playTime = gGameState.fileSummaries[i].playTime;
        }
    }
}

void MakeSaveSystem(SaveFileLarge* save) {
    save->common.flags = gGameState.flags;
    save->common.hp = gGameState.hp;
    memcpy(save->common.progression, &gGameState.progression.maxHp, 0x88);
    save->common.availableWorlds = gGameState.availableWorlds;
    save->common.floor = gGameState.floor;
    save->common.world = gGameState.world;
    save->common.playTime = gGameState.playTime;
    CopyMapProgress(&save->shared);
    WriteCardSaveSlice(&save->large);
    func_080C700C(&save->unk_E6C);
    SavePooState(save->pooState);
    SaveMoogleShopFlags(&save->moogleShop);
}

void MakeSaveFileLarge(SaveFileLarge* save) {
    save->common.flags = gGameState.flags;
    save->common.hp = gGameState.hp;
    memcpy(save->common.progression, &gGameState.progression.maxHp, 0x88);
    save->common.availableWorlds = gGameState.availableWorlds;
    save->common.floor = gGameState.floor;
    save->common.world = gGameState.world;
    save->common.playTime = gGameState.playTime;
    CopyMapProgress(&save->shared);
    WriteCardSaveSlice(&save->large);
    func_080C700C(&save->unk_E6C);
    SavePooState(save->pooState);
    SaveMoogleShopFlags(&save->moogleShop);

    if (gGameState.flags & 0x10) {
        gGameState.fileSummaries[1].floor = gGameState.floor;
        gGameState.fileSummaries[1].world = gGameState.world;
        gGameState.fileSummaries[1].level = gGameState.progression.level;
        gGameState.fileSummaries[1].playTime = gGameState.playTime;
    } else {
        gGameState.fileSummaries[0].floor = gGameState.floor;
        gGameState.fileSummaries[0].world = gGameState.world;
        gGameState.fileSummaries[0].level = gGameState.progression.level;
        gGameState.fileSummaries[0].playTime = gGameState.playTime;
    }
}

void MakeSaveFileSmall(SaveFileSmall* save) {
    save->common.flags = gGameState.flags;
    save->common.hp = gGameState.hp;
    memcpy(save->common.progression, &gGameState.progression.maxHp, 0x88);
    save->common.availableWorlds = gGameState.availableWorlds;
    save->common.floor = gGameState.floor;
    save->common.world = gGameState.world;
    save->common.playTime = gGameState.playTime;
    CopyMapProgress(&save->shared);
    CopyMapCardInventory(&save->small);

    if (gGameState.flags & 0x10) {
        gGameState.fileSummaries[3].floor = gGameState.floor;
        gGameState.fileSummaries[3].world = gGameState.world;
        gGameState.fileSummaries[3].level = gGameState.progression.level;
        gGameState.fileSummaries[3].playTime = gGameState.playTime;
    } else {
        gGameState.fileSummaries[2].floor = gGameState.floor;
        gGameState.fileSummaries[2].world = gGameState.world;
        gGameState.fileSummaries[2].level = gGameState.progression.level;
        gGameState.fileSummaries[2].playTime = gGameState.playTime;
    }
}

void ApplySaveHeaderData(SaveHeaderData* data) {
    if (SaveRepairHeader() == SAVE_OK) {
        if (data->flags & 1) {
            gGameState.flags |= 0x20;
        }

        if (data->flags & 4) {
            gGameState.flags |= 0x800;
        }

        if (data->flags & 2) {
            gGameState.flags |= 0x200;
        }

#ifdef VERSION_EU
        gLanguage = data->language;
#endif
    }

    if (SaveRepairFileLarge(0) == SAVE_OK) {
        gGameState.fileSummaries[0].floor = data->files[0].floor;
        gGameState.fileSummaries[0].world = data->files[0].world;
        gGameState.fileSummaries[0].level = data->files[0].level;
        gGameState.fileSummaries[0].playTime = data->files[0].playTime;
    } else {
        gGameState.fileSummaries[0].floor = 0;
        gGameState.fileSummaries[0].world = 0;
        gGameState.fileSummaries[0].level = 0;
        gGameState.fileSummaries[0].playTime = 0;
    }

    if (SaveRepairFileLarge(1) == SAVE_OK) {
        gGameState.fileSummaries[1].floor = data->files[1].floor;
        gGameState.fileSummaries[1].world = data->files[1].world;
        gGameState.fileSummaries[1].level = data->files[1].level;
        gGameState.fileSummaries[1].playTime = data->files[1].playTime;
    } else {
        gGameState.fileSummaries[1].floor = 0;
        gGameState.fileSummaries[1].world = 0;
        gGameState.fileSummaries[1].level = 0;
        gGameState.fileSummaries[1].playTime = 0;
    }

    if (SaveRepairFileSmall(0) == SAVE_OK) {
        gGameState.fileSummaries[2].floor = data->files[2].floor;
        gGameState.fileSummaries[2].world = data->files[2].world;
        gGameState.fileSummaries[2].level = data->files[2].level;
        gGameState.fileSummaries[2].playTime = data->files[2].playTime;
    } else {
        gGameState.fileSummaries[2].floor = 0;
        gGameState.fileSummaries[2].world = 0;
        gGameState.fileSummaries[2].level = 0;
        gGameState.fileSummaries[2].playTime = 0;
    }

    if (SaveRepairFileSmall(1) == SAVE_OK) {
        gGameState.fileSummaries[3].floor = data->files[3].floor;
        gGameState.fileSummaries[3].world = data->files[3].world;
        gGameState.fileSummaries[3].level = data->files[3].level;
        gGameState.fileSummaries[3].playTime = data->files[3].playTime;
    } else {
        gGameState.fileSummaries[3].floor = 0;
        gGameState.fileSummaries[3].world = 0;
        gGameState.fileSummaries[3].level = 0;
        gGameState.fileSummaries[3].playTime = 0;
    }
}

void ApplySaveSystem(SaveFileLarge* save) {
    u32 t;

    t = gGameState.flags & 0xA20;
    save->common.flags &= 0xFFFFF5DF;
    gGameState.flags = save->common.flags | t;
    gGameState.hp = save->common.hp;
    memcpy(&gGameState.progression.maxHp, save->common.progression, 0x88);
    gGameState.availableWorlds = save->common.availableWorlds;
    gGameState.floor = save->common.floor;
    gGameState.world = save->common.world;
    gGameState.playTime = save->common.playTime;
    RestoreMapProgress(&save->shared);
    ReadCardSaveSlice(&save->large);
    func_080C7024(&save->unk_E6C);
    LoadPooState(save->pooState);
    LoadMoogleShopFlags(&save->moogleShop);
}

void ApplySaveFileLarge(SaveFileLarge* save) {
    u32 t;

    t = gGameState.flags & 0xA20;
    save->common.flags &= 0xFFFFF5DF;
    gGameState.flags = save->common.flags | t;
    gGameState.hp = save->common.hp;
    memcpy(&gGameState.progression.maxHp, save->common.progression, 0x88);
    gGameState.availableWorlds = save->common.availableWorlds;
    gGameState.floor = save->common.floor;
    gGameState.world = save->common.world;
    gGameState.playTime = save->common.playTime;
    RestoreMapProgress(&save->shared);
    ReadCardSaveSlice(&save->large);
    func_080C7024(&save->unk_E6C);
    LoadPooState(save->pooState);
    LoadMoogleShopFlags(&save->moogleShop);
    gGameState.flags &= ~8;
}

void ApplySaveFileSmall(SaveFileSmall* save) {
    u32 t;

    t = gGameState.flags & 0xA20;
    save->common.flags &= 0xFFFFF5DF;
    gGameState.flags = save->common.flags | t;
    gGameState.hp = save->common.hp;
    memcpy(&gGameState.progression.maxHp, save->common.progression, 0x88);
    gGameState.availableWorlds = save->common.availableWorlds;
    gGameState.floor = save->common.floor;
    gGameState.world = save->common.world;
    gGameState.playTime = save->common.playTime;
    RestoreMapProgress(&save->shared);
    RestoreMapCardInventory(&save->small);
    gGameState.flags |= 8;
}

TaskDesc gTaskDescHumRobe = {
    "task_hum_robe",
    (TaskInitFunc)task_hum_robe_0,
    (TaskUpdateFunc)task_hum_robe_1,
    (TaskDrawFunc)task_hum_robe_2,
    (TaskDestroyFunc)task_hum_robe_3,
    sizeof(RobeWork),
};
