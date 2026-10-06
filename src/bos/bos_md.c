/**
 * bos_md.c
 * Dragon Maleficent Boss
 */

#include "system_state.h"
#include "display.h"
#include "fade.h"
#include "bos_md.h"
#include "anim.h"
#include "sprites_bos5.h"
#include "sprites_worldinspect.h"
#include "chara_types.h"
#include "prize_types.h"
#include "btl_api.h"
#include "songs.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "card_api.h"
#include "engine_math.h"
#include "gba/defines.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "bos_ga.h"
#include "default_bg_map.h"
#include "sprite_palettes.h"

static const EmyKind sBosMdEmyKind = { 37, 1000, 16, 16, 0, 60, EMY_KIND_FLAG_NO_COLLIDER };

static const MdMapData sMdMapData = {
    gBosMdBgTiles, 32768, gBosMdBgPalettes, 192, { gBosMdBgMap0, gBosMdBgMap1, gBosMdBgMap2, gBosMdBgMap3 }
};

static const MdFrameDef sMdFrameDefs[41] = {
    {
        32, 0, gBosMdFrame0Tiles, 16864,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame0Map },
        { { 0, 112, 0xFF90, gBosMdFrame0ArmTiles, 1952, gBosMdFrame0ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame2 } },
        { { -100, 0, -45, 0 } },
    },
    {
        32, 0, gBosMdFrame0Tiles, 4480,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame0Map },
        { { 0, 112, 0xFF90, gBosMdFrame0ArmTiles, 1952, gBosMdFrame0ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame2 } },
        { { -100, 0, -45, 0 } },
    },
    {
        32, 0, gBosMdFrame2Tiles, 3872,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame2Map },
        { { 0, 112, 0xFF90, gBosMdFrame2ArmTiles, 2176, gBosMdFrame2ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame3 } },
        { { -101, 0, -34, 0 } },
    },
    {
        32, 0, gBosMdFrame3Tiles, 4064,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame3Map },
        { { 0, 112, 0xFF90, gBosMdFrame3ArmTiles, 2048, gBosMdFrame3ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -103, 0, -28, 0 } },
    },
    {
        0, 65521, gBosMdFrame4Tiles, 4448,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame4Map },
        { { 0xFFF8, 112, 0xFF90, gBosMdFrame4ArmTiles, 2368, gBosMdFrame4ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -131, 0, -108, 0 } },
    },
    {
        3, 65524, gBosMdFrame5Tiles, 4448,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame5Map },
        { { 0, 112, 0xFF90, gBosMdFrame5ArmTiles, 2400, gBosMdFrame5ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame3 } },
        { { -142, 0, -105, 0 } },
    },
    {
        4, 65529, gBosMdFrame6Tiles, 4480,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame6Map },
        { { 0, 112, 0xFF8F, gBosMdFrame6ArmTiles, 2432, gBosMdFrame6ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame2 } },
        { { -145, 0, -94, 0 } },
    },
    {
        43, 65504, gBosMdFrame7Tiles, 3712,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame7Map },
        { { 0, 112, 0xFF90, gBosMdFrame7ArmTiles, 2368, gBosMdFrame7ArmFrame0 }, { 11, 56, 0xFFE0, gBosMdForearmTiles, 4768, gBosMdForearmFrame0 } },
        { { -67, 0, -126, 0 } },
    },
    {
        43, 65528, gBosMdFrame8Tiles, 3712,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame8Map },
        { { 0, 112, 0xFF90, gBosMdFrame8ArmTiles, 1952, gBosMdFrame8ArmFrame0 }, { 24, 56, 0xFFE2, gBosMdForearmTiles, 4768, gBosMdForearmFrame4 } },
        { { -46, 0, -154, 0 } },
    },
    {
        31, 0, gBosMdFrame9Tiles, 4160,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame9Map },
        { { 0, 112, 0xFF90, gBosMdFrame9ArmTiles, 2112, gBosMdFrame9ArmFrame0 }, { 2, 56, 0xFFF2, gBosMdForearmTiles, 4768, gBosMdForearmFrame6 } },
        { { -105, 0, -135, 0 } },
    },
    {
        29, 65531, gBosMdFrame10Tiles, 4480,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame10Map },
        { { 0, 112, 0xFF90, gBosMdFrame10ArmTiles, 2080, gBosMdFrame10ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame2 } },
        { { -123, 0, -42, 0 } },
    },
    {
        25, 65527, gBosMdFrame11Tiles, 4480,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame11Map },
        { { 0, 112, 0xFF91, gBosMdFrame11ArmTiles, 2368, gBosMdFrame11ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -123, 0, -30, 0 } },
    },
    {
        22, 65519, gBosMdFrame12Tiles, 4448,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame12Map },
        { { 0xFFFF, 112, 0xFF90, gBosMdFrame12ArmTiles, 2432, gBosMdFrame12ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -129, 0, -36, 0 } },
    },
    {
        36, 65518, gBosMdFrame13Tiles, 4384,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame13Map },
        { { 0, 112, 0xFF90, gBosMdFrame13ArmTiles, 2208, gBosMdFrame13ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -115, 0, -31, 0 } },
    },
    {
        35, 65533, gBosMdFrame14Tiles, 4384,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame14Map },
        { { 0, 112, 0xFF90, gBosMdFrame14ArmTiles, 2016, gBosMdFrame14ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -98, 0, -49, 0 } },
    },
    {
        35, 65530, gBosMdFrame4Tiles, 4448,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame4Map },
        { { 0, 112, 0xFF90, gBosMdFrame15ArmTiles, 2336, gBosMdFrame15ArmFrame0 }, { 20, 56, 0xFFCF, gBosMdForearmTiles, 4768, gBosMdForearmFrame4 } },
        { { -94, 0, -100, 0 } },
    },
    {
        45, 65535, gBosMdFrame5Tiles, 4448,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame5Map },
        { { 0, 112, 0xFF90, gBosMdFrame16ArmTiles, 1920, gBosMdFrame16ArmFrame0 }, { 19, 56, 0xFFED, gBosMdForearmTiles, 4768, gBosMdForearmFrame5 } },
        { { -104, 0, -94, 0 } },
    },
    {
        48, 6, gBosMdFrame6Tiles, 4480,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame6Map },
        { { 0, 112, 0xFF90, gBosMdFrame17ArmTiles, 1632, gBosMdFrame17ArmFrame0 }, { 17, 56, 0xFFF3, gBosMdForearmTiles, 4768, gBosMdForearmFrame6 } },
        { { -105, 0, -79, 0 } },
    },
    {
        56, 11, gBosMdFrame18Tiles, 4448,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame18Map },
        { { 0, 112, 0xFF90, gBosMdFrame18ArmTiles, 1408, gBosMdFrame18ArmFrame0 }, { 23, 56, 0xFFF8, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -103, 0, -57, 0 } },
    },
    {
        35, 65533, gBosMdFrame19Tiles, 4448,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame19Map },
        { { 0, 112, 0xFF9A, gBosMdFrame19ArmTiles, 2176, gBosMdFrame19ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -98, 0, -78, 0 } },
    },
    {
        36, 65535, gBosMdFrame20Tiles, 4480,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame20Map },
        { { 0, 112, 0xFF92, gBosMdFrame20ArmTiles, 1920, gBosMdFrame20ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame3 } },
        { { -102, 0, -59, 0 } },
    },
    {
        38, 0, gBosMdFrame21Tiles, 4480,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame21Map },
        { { 0, 112, 0xFF89, gBosMdFrame21ArmTiles, 1824, gBosMdFrame21ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame3 } },
        { { -102, 0, -52, 0 } },
    },
    {
        37, 0, gBosMdFrame22Tiles, 4448,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame22Map },
        { { 0, 112, 0xFF8D, gBosMdFrame22ArmTiles, 1984, gBosMdFrame22ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame2 } },
        { { -100, 0, -50, 0 } },
    },
    {
        5, 5, gBosMdFrame3Tiles, 4064,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame3Map },
        { { 0xFFFF, 112, 0xFF90, gBosMdFrame23ArmTiles, 2336, gBosMdFrame23ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -128, 0, -22, 0 } },
    },
    {
        41, 65504, gBosMdFrame24Tiles, 4480,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame24Map },
        { { 0, 112, 0xFF90, gBosMdFrame7ArmTiles, 2368, gBosMdFrame7ArmFrame0 }, { 13, 56, 0xFFDF, gBosMdForearmTiles, 4768, gBosMdForearmFrame0 } },
        { { -108, 0, -88, 0 } },
    },
    {
        46, 65499, gBosMdFrame7Tiles, 3712,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame7Map },
        { { 11, 112, 0xFF85, gBosMdFrame19ArmTiles, 2176, gBosMdFrame19ArmFrame0 }, { 29, 56, 0xFFBA, gBosMdForearmTiles, 4768, gBosMdForearmFrame4 } },
        { { -62, 0, -126, 0 } },
    },
    {
        60, 65491, gBosMdFrame26Tiles, 4320,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame26Map },
        { { 21, 112, 0xFF70, gBosMdFrame20ArmTiles, 1920, gBosMdFrame20ArmFrame0 }, { 40, 56, 0xFFC4, gBosMdForearmTiles, 4768, gBosMdForearmFrame5 } },
        { { -3, 0, -168, 0 } },
    },
    {
        36, 65527, gBosMdFrame9Tiles, 4160,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame9Map },
        { { 0, 112, 0xFF89, gBosMdFrame21ArmTiles, 1824, gBosMdFrame21ArmFrame0 }, { 17, 56, 0xFFF3, gBosMdForearmTiles, 4768, gBosMdForearmFrame6 } },
        { { -103, 0, -142, 0 } },
    },
    {
        1, 65530, gBosMdFrame18Tiles, 4448,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame18Map },
        { { 0, 112, 0xFF8F, gBosMdFrame6ArmTiles, 2432, gBosMdFrame6ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -158, 0, -75, 0 } },
    },
    {
        36, 65518, gBosMdFrame13Tiles, 4384,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame13Map },
        { { 0, 112, 0xFF90, gBosMdFrame13ArmTiles, 2208, gBosMdFrame13ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -115, 0, -31, 0 } },
    },
    {
        35, 65533, gBosMdFrame14Tiles, 4384,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame14Map },
        { { 0, 112, 0xFF90, gBosMdFrame14ArmTiles, 2016, gBosMdFrame14ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -98, 0, -49, 0 } },
    },
    {
        0, 65525, gBosMdFrame26Tiles, 4320,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame26Map },
        { { 0xFFF8, 112, 0xFF90, gBosMdFrame4ArmTiles, 2368, gBosMdFrame4ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -62, 0, -136, 0 } },
    },
    {
        0, 65530, gBosMdFrame32Tiles, 4448,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame32Map },
        { { 0, 112, 0xFF90, gBosMdFrame5ArmTiles, 2400, gBosMdFrame5ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -98, 0, -135, 0 } },
    },
    {
        0, 65535, gBosMdFrame24Tiles, 4480,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame24Map },
        { { 0, 112, 0xFF8F, gBosMdFrame6ArmTiles, 2432, gBosMdFrame6ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -149, -20, -38, 0 } },
    },
    {
        0, 65535, gBosMdFrame34Tiles, 4256,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame34Map },
        { { 0, 112, 0xFF90, gBosMdFrame34ArmTiles, 2432, gBosMdFrame34ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -140, 17, -24, 0 } },
    },
    {
        0, 65532, gBosMdFrame35Tiles, 4480,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame35Map },
        { { 0, 112, 0xFF90, gBosMdFrame35ArmTiles, 2400, gBosMdFrame35ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -171, 0, -78, 0 } },
    },
    {
        0, 14, gBosMdFrame36Tiles, 4480,
        { gDefaultBgMap, gDefaultBgMap, gBosMdFrame36LeftMap, gBosMdFrame36Map },
        { { 0, 112, 0xFF90, gBosMdFrame36ArmTiles, 2368, gBosMdFrame36ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -190, -20, -33, 0 } },
    },
    {
        3, 12, gBosMdFrame37Tiles, 4480,
        { gDefaultBgMap, gDefaultBgMap, gBosMdFrame37LeftMap, gBosMdFrame37Map },
        { { 0, 112, 0xFF90, gBosMdFrame23ArmTiles, 2336, gBosMdFrame23ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -181, 17, -25, 0 } },
    },
    {
        31, 2, gBosMdFrame38Tiles, 4224,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame38Map },
        { { 0, 112, 0xFF90, gBosMdFrame38ArmTiles, 1920, gBosMdFrame38ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame2 } },
        { { -86, 0, -26, 0 } },
    },
    {
        32, 65530, gBosMdFrame7Tiles, 3712,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame7Map },
        { { 0, 112, 0xFF90, gBosMdFrame0ArmTiles, 1952, gBosMdFrame0ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -79, 0, -98, 0 } },
    },
    {
        32, 4, gBosMdFrame13Tiles, 4384,
        { gDefaultBgMap, gDefaultBgMap, gDefaultBgMap, gBosMdFrame13Map },
        { { 0, 112, 0xFF90, gBosMdFrame38ArmTiles, 1920, gBosMdFrame38ArmFrame0 }, { 0, 56, 0xFFEE, gBosMdForearmTiles, 4768, gBosMdForearmFrame1 } },
        { { -119, 19, -27, 0 } },
    },
};

static const MdAnimFrame sMdIdleFrames[4] = { { 1, 18 }, { 2, 12 }, { 3, 24 }, { 2, 12 } };

static const MdAnimFrame sMdIdleNearFrames[4] = { { 4, 18 }, { 5, 12 }, { 6, 24 }, { 5, 12 } };

static const MdAnimFrame sMdFireBreathStartFrames[4] = { { 7, 12 }, { 8, 30 }, { 9, 3 }, { 10, 6 } };

static const MdAnimFrame sMdFireBreathFrames[2] = { { 11, 24 }, { 12, 6 } };

static const MdAnimFrame sMdFireBreathEndFrames[2] = { { 13, 6 }, { 14, 6 } };

static const MdAnimFrame sMdQuakeDoubleFrames[10] = { { 15, 6 }, { 16, 3 }, { 17, 3 }, { 18, 24 }, { 1, 6 }, { 19, 6 }, { 20, 3 }, { 21, 3 }, { 22, 24 }, { 1, 6 } };

static const MdAnimFrame sMdQuakeHeavyFrames[8] = { { 23, 6 }, { 24, 6 }, { 25, 6 }, { 26, 30 }, { 27, 3 }, { 28, 6 }, { 29, 6 }, { 30, 6 } };

static const MdAnimFrame sMdBiteNearFrames[6] = { { 39, 3 }, { 31, 24 }, { 32, 3 }, { 33, 3 }, { 34, 24 }, { 40, 3 } };

static const MdAnimFrame sMdBiteFarFrames[8] = { { 39, 3 }, { 31, 24 }, { 32, 3 }, { 35, 3 }, { 36, 3 }, { 37, 24 }, { 34, 6 }, { 40, 6 } };

static const MdAnimFrame sMdBiteDoubleFrames[11] = { { 39, 3 }, { 31, 24 }, { 32, 3 }, { 33, 3 }, { 34, 24 }, { 35, 6 }, { 32, 12 }, { 36, 3 }, { 37, 24 }, { 34, 6 }, { 38, 6 } };

static const MdAnimFrame sMdDefeatFrames[1] = { { 1, 32767 } };

static const MdAnimDef sMdAnimDefs[11] = {
    { sMdIdleFrames, 4 },
    { sMdIdleNearFrames, 4 },
    { sMdFireBreathStartFrames, 4 },
    { sMdFireBreathFrames, 2 },
    { sMdFireBreathEndFrames, 2 },
    { sMdQuakeDoubleFrames, 10 },
    { sMdQuakeHeavyFrames, 8 },
    { sMdBiteNearFrames, 6 },
    { sMdBiteFarFrames, 8 },
    { sMdBiteDoubleFrames, 11 },
    { sMdDefeatFrames, 1 },
};

TaskDesc gTaskDescBosMd = {
    "task_bos_md",
    (TaskInitFunc)task_bos_md_0,
    (TaskUpdateFunc)task_bos_md_1,
    (TaskDrawFunc)task_bos_md_2,
    (TaskDestroyFunc)task_bos_md_3,
    sizeof(MdWork),
};

static TaskDesc sTaskDescBosMdMap = {
    "task_bos_md_map",
    (TaskInitFunc)task_bos_md_map_0,
    (TaskUpdateFunc)task_bos_md_map_1,
    NULL,
    NULL,
    sizeof(MdMapWork),
};

static const MdFirePoint sMdFirePoints0[4] = { { 88, 288, 240, 0 }, { 56, 312, 330, 0 }, { 72, 336, 420, 0 }, { 104, 360, 510, 0 } };

static const MdFirePoint sMdFirePoints1[4] = { { 128, 304, 0, 0 }, { 104, 324, 0, 0 }, { 144, 344, 0, 0 }, { 112, 364, 0, 0 } };

static const MdFirePoint sMdFirePoints2[4] = { { 128, 288, 0, 0 }, { 156, 312, 0, 0 }, { 172, 336, 0, 0 }, { 144, 360, 0, 0 } };

static const MdFireDef sMdFireDefs[6] = {
    { sMdFirePoints0, 4 },
    { sMdFirePoints1, 4 },
    { sMdFirePoints2, 4 },
    { sMdFirePoints0, 4 },
    { sMdFirePoints0, 4 },
    { sMdFirePoints0, 4 },
};

static const EmyKind sBosMdFireEmyKind = { 37, 1000, 16, 16, 0, 60, EMY_KIND_FLAG_NO_COLLIDER };

static TaskDesc sTaskDescBosMdFire = {
    "task_bos_md_fire",
    (TaskInitFunc)task_bos_md_fire_0,
    (TaskUpdateFunc)task_bos_md_fire_1,
    (TaskDrawFunc)task_bos_md_fire_2,
    (TaskDestroyFunc)task_bos_md_fire_3,
    sizeof(MdFireWork),
};

static TaskDesc sTaskDescBosMdDai = {
    "task_bos_md_dai",
    (TaskInitFunc)task_bos_md_dai_0,
    (TaskUpdateFunc)task_bos_md_dai_1,
    (TaskDrawFunc)task_bos_md_dai_2,
    (TaskDestroyFunc)task_bos_md_dai_3,
    sizeof(MdDaiWork),
};

static TaskDesc sTaskDescBosMdHahen = {
    "task_bos_md_hahen",
    (TaskInitFunc)task_bos_md_hahen_0,
    (TaskUpdateFunc)task_bos_md_hahen_1,
    (TaskDrawFunc)task_bos_md_hahen_2,
    (TaskDestroyFunc)task_bos_md_hahen_3,
    sizeof(MdHahenWork),
};

void BosMdRequestState(MdWork* work, s32 state) {
    u16 t;

    work->nextState = state;
    t = work->flags | MD_FLAG_STATE_REQUESTED;
    work->flags = t;
}

void BosMdSetBgMap(MdWork* work, u16 index) {
    SetBgMapBlocks(1, (void*)sMdFrameDefs[index].blocks, 2, 2);
}

void BosMdLoadBgTiles(MdWork* work, u16 index) {
    LoadBgTiles(1, sMdFrameDefs[index].tiles, sMdFrameDefs[index].tilesSize);
}

void BosMdSetFrame(MdWork* work, u16 id) {
    s32 n;

    if (!work->bgVisible) {
        return;
    }

    BosMdLoadBgTiles(work, id);
    BosMdSetBgMap(work, id);
    work->bgOffsetX = sMdFrameDefs[id].bgOffsetX;
    work->bgOffsetY = sMdFrameDefs[id].bgOffsetY;

    for (n = 0; n < 2; n++) {
        work->gfx[n].sprite = sMdFrameDefs[id].desc[n].sprite;

        if (work->gfx[n].src != sMdFrameDefs[id].desc[n].src && n == 0) {
            work->gfx[n].src = sMdFrameDefs[id].desc[n].src;
            UpdateSpriteFrameTiles(work->gfx[n].tiles, work->gfx[n].sprite, work->gfx[n].src);
        }

        work->gfx[n].x = sMdFrameDefs[id].desc[n].x;
        work->gfx[n].y = sMdFrameDefs[id].desc[n].y;
        work->gfx[n].z = sMdFrameDefs[id].desc[n].z;
    }
}

void MdAnimStart(MdWork* work, s16 id) {
    MdAnim* a;
    const MdAnimDef* base;
    const MdAnimDef* d;
    const MdAnimFrame* f;

    a = &work->anim;
    a->animId = id;
    base = sMdAnimDefs;
    d = base + id;
    f = d->frames;
    a->frames = f;
    a->frameCount = d->frameCount;
    a->frame = 0;
    a->timer = f->duration;
    BosMdSetFrame(work, f->gfxIndex);
}

void MdAnimUpdate(MdWork* work) {
    MdAnim* a;

    a = &work->anim;
    a->timer--;

    if (a->timer < 0) {
        a->frame++;

        if (a->frame >= a->frameCount) {
            a->frame = 0;
        }

        a->timer = a->frames[a->frame].duration;
        BosMdSetFrame(work, a->frames[a->frame].gfxIndex);
    }
}

u8 BosMdAnimIsLastFrame(MdWork* work) {
    MdAnim* a;

    a = &work->anim;

    if (a->frame >= a->frameCount - 1) {
        return 1;
    }

    return 0;
}

u8 BosMdUpdateIdle(MdWork* work) {
    if (work->flags & MD_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
        if (gBtlWork->actor->x > 0x8000) {
            MdAnimStart(work, 1);
        } else {
            MdAnimStart(work, 0);
        }

        if (gBtlWork->flags & 0x100000) {
            work->timer = ((GetRandom() & 3) + (GetRandom() & 3)) / 2 * 20 + 60;
        } else if (work->sub[0].hp * 10 / work->sub[0].maxHp > 4) {
            work->timer = (GetRandom() % 5 + GetRandom() % 5) / 2 * 30 + 30;
        } else {
            work->timer = (GetRandom() % 6 + GetRandom() % 6) / 2 * 10 + 30;
        }

        break;
    case 1:
        if (BosMdAnimIsLastFrame(work) && gBtlWork->actor->x > 0x8000) {
            MdAnimStart(work, 1);
        }

        if (gBtlWork->phase != 0) {
            work->timer--;

            if (work->timer <= 0) {
                RequestEnemyCardUse(&work->sub[0]);
                BosMdRequestState(work, 0);
            }
        }

        break;
    case 2:
        break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~MD_FLAG_STATE_REQUESTED;
    }

    return 1;
}

u8 BosMdUpdateBite(MdWork* work) {
    s32 d;
    u16 r;

    if (work->flags & MD_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
        case 0:
            d = gBtlWork->actor->x;

            if (d > 0xA800) {
                switch (GetRandom() % 3) {
                case 0:
                    MdAnimStart(work, 7);
                    break;
                case 1:
                    MdAnimStart(work, 8);
                    break;
                case 2:
                    MdAnimStart(work, 9);
                    break;
                }
            } else if (d > 0x7000) {
                r = GetRandom() % 100;

                if (r <= 59) {
                    MdAnimStart(work, 7);
                } else if (r <= 89) {
                    MdAnimStart(work, 8);
                } else {
                    MdAnimStart(work, 9);
                }
            } else if (d > 0x3800) {
                r = GetRandom() % 100;

                if (r <= 59) {
                    MdAnimStart(work, 8);
                } else if (r <= 89) {
                    MdAnimStart(work, 7);
                } else {
                    MdAnimStart(work, 9);
                }
            } else {
                switch (GetRandom() % 3) {
                case 0:
                    MdAnimStart(work, 7);
                    break;
                case 1:
                    MdAnimStart(work, 8);
                    break;
                case 2:
                    MdAnimStart(work, 9);
                    break;
                }
            }

            break;
        case 1:
            switch (work->anim.frames[work->anim.frame].gfxIndex) {
            case 33:
            case 34:
            case 36:
            case 37:
                if (ApplyAttackBox(251, work->sub[0].x, work->sub[0].y,
                                  work->sub[0].z, 40, 20, 24) != 0) {
                    m4aSongNumStart(SONG_BTL_DRGN_BITE);
                }

                break;
            }

            if (BosMdAnimIsLastFrame(work)) {
                BosMdRequestState(work, 0);
            }

            break;
        case 2:
            ClearBtlObjActionFlags(&work->sub[0]);
            break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~MD_FLAG_STATE_REQUESTED;
    }

    return 1;
}

u8 BosMdUpdateQuake(MdWork* work) {
    s32 v;

    if (work->flags & MD_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
        case 0:
            if (gBtlWork->actor->x > 0xA800) {
                if (GetRandom() % 100 <= 59) {
                    MdAnimStart(work, 6);
                } else {
                    MdAnimStart(work, 5);
                }
            } else {
                if (GetRandom() % 100 <= 79) {
                    MdAnimStart(work, 5);
                } else {
                    MdAnimStart(work, 6);
                }
            }

            work->step = 0;
            break;
        case 1:
            switch (work->step) {
            case 0:
                v = work->anim.frames[work->anim.frame].gfxIndex;

                if (v == 18) {
                    ApplyAttackBox(252, gBtlWork->viewX, gBtlWork->viewY, 0,
                                  256, 256, 1);
                    m4aSongNumStart(SONG_BTL_DRGN_RUMB);
                    BtlMapStartShake();
                    work->signals |= 1;
                    work->step = 1;
                } else if (v == 28) {
                    ApplyAttackBox(254, gBtlWork->viewX, gBtlWork->viewY, 0,
                                  256, 256, 1);
                    m4aSongNumStart(SONG_BTL_DRGN_RUMB);
                    BtlMapStartShake();
                    work->signals |= 1;
                    work->step = 2;
                }

                break;
            case 1:
                v = work->anim.frames[work->anim.frame].gfxIndex;

                if (v == 22) {
                    MakeOpponentsHittable();
                    ApplyAttackBox(252, gBtlWork->viewX, gBtlWork->viewY, 0,
                                  256, 256, 1);
                    m4aSongNumStart(SONG_BTL_DRGN_RUMB);
                    BtlMapStartShake();
                    work->signals |= 1;
                    work->step = 2;
                }

                break;
            }

            if (BosMdAnimIsLastFrame(work)) {
                BosMdRequestState(work, 0);
            }

            break;
        case 2:
            ClearBtlObjActionFlags(&work->sub[0]);
            break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~MD_FLAG_STATE_REQUESTED;
    }

    return 1;
}

u8 BosMdUpdateFireBreath(MdWork* work) {
    MdFireArg a;

    if (work->flags & MD_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
        case 0:
            work->signals = work->signals | 2;
            MdAnimStart(work, 2);
            work->step = 0;
            break;
        case 1:
            switch (work->step) {
                case 0:
                    if (BosMdAnimIsLastFrame(work)) {
                        MdAnimStart(work, 3);
                        BgFxStartDragonFire(work->sub[0].x, work->sub[0].y,
                                      work->sub[0].z + 0x1200, 512);
                        m4aSongNumStart(SONG_EF_DRGN_FIRE);
                        work->step = 1;
                    }

                    break;
                case 1:
                    if (ApplyAttackBox(253, work->sub[0].x,
                                      work->sub[0].y + 0x1800, 0, 72, 48, 1) != 0) {
                        m4aSongNumStart(SONG_SND_714);
                    }

                    if (!BgFxIsActive()) {
                        work->signals &= 0xFFFD;
                        a.pool = &work->tasks;
                        a.index = 0;
                        a.flags = &work->signals;

                        if (work->sub[0].hp * 10 / work->sub[0].maxHp > 4) {
                            switch (GetRandom() % 3) {
                            case 0:
                                a.pattern = 0;
                                break;
                            case 1:
                                a.pattern = 1;
                                break;
                            case 2:
                                a.pattern = 2;
                                break;
                            }
                        } else {
                            switch (GetRandom() % 3) {
                            case 0:
                                a.pattern = 3;
                                break;
                            case 1:
                                a.pattern = 4;
                                break;
                            case 2:
                                a.pattern = 5;
                                break;
                            }
                        }

                        TaskCreate(&work->tasks, &sTaskDescBosMdFire, &a);
                        MdAnimStart(work, 4);
                        work->step = 2;
                    }

                    break;
                case 2:
                    if (BosMdAnimIsLastFrame(work)) {
                        BosMdRequestState(work, 0);
                    }

                    break;
            }

            break;
        case 2:
            ClearBtlObjActionFlags(&work->sub[0]);
            break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~MD_FLAG_STATE_REQUESTED;
    }

    return 1;
}

u8 BosMdUpdateDefeat(MdWork* work) {
    u8 result;
    PrizeCardArg arg;

    result = 1;

    if (work->flags & MD_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
        case 0:
            MdAnimStart(work, 10);
            BeginBossDefeat(&work->sub[0]);
            work->signals |= 2;
            work->step = 0;
            break;
        case 1:
            switch (work->step) {
            case 0:
                if (!FadeIsActive()) {
                    BgFxStartBossDeath(work->sub[0].x,
                                  work->sub[0].y + work->sub[0].z);
                    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
                    work->timer = 120;
                    work->step = 1;
                }

                break;
            case 1:
                work->timer--;

                if (work->timer <= 0) {
                    BgFxStartBossDeathFlash();
                    work->step = 2;
                }

                break;
            case 2:
                if (work->bgVisible && FadeGetAmount() == 31) {
                    DisableBg(1);
                    work->bgVisible = 0;
                }

                if (!BgFxIsActive()) {
                    arg.x = work->sub[0].x;
                    arg.y = work->sub[0].y;
                    arg.z = work->sub[0].z;
                    CreateBossPrizeCardTask(&gBtlWork->taskPools[0], &arg);
                    DropBossPrizes(&work->sub[0]);
                    EndBossDefeat();
                    result = 0;
                }

                break;
            }

            break;
        case 2:
            break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~MD_FLAG_STATE_REQUESTED;
    }

    return result;
}

void BosMdChooseAttack(MdWork* work) {
    s32 d;
    u16 r;

    d = gBtlWork->actor->x;

    if (d > 0xA800) {
        r = GetRandom() % 100;

        if (r <= 59) {
            BosMdRequestState(work, 2);
        } else if (r <= 89) {
            BosMdRequestState(work, 3);
        } else {
            BosMdRequestState(work, 1);
        }
    } else if (d > 0x7000) {
        r = GetRandom() % 100;

        if (r <= 59) {
            BosMdRequestState(work, 1);
        } else if (r <= 89) {
            BosMdRequestState(work, 3);
        } else {
            BosMdRequestState(work, 2);
        }
    } else if (d > 0x3800) {
        r = GetRandom() % 100;

        if (r <= 59) {
            BosMdRequestState(work, 1);
        } else if (r <= 89) {
            BosMdRequestState(work, 3);
        } else {
            BosMdRequestState(work, 2);
        }
    } else {
        r = GetRandom() % 100;

        if (r <= 59) {
            BosMdRequestState(work, 2);
        } else if (r <= 89) {
            BosMdRequestState(work, 3);
        } else {
            BosMdRequestState(work, 1);
        }
    }
}

void BosMdHandleReaction(MdWork* work) {
    s16 i;

    for (i = 0; i < 1; i++) {
        BtlObj* e = &work->sub[i];

        switch (UpdateBtlObjReaction(e)) {
        case BTL_REACTION_CARD_ACTION:
            BosMdChooseAttack(work);
            break;
        case BTL_REACTION_HURT:
        case BTL_REACTION_STUNNED:
        case BTL_REACTION_GRAVITY:
            work->hurtTimer = 30;
            work->hurtState[i] = 2;
            break;
        case BTL_REACTION_DEFEATED:
        case BTL_REACTION_GRAVITY_DEFEATED:
            SetBtlObjUnhittable(e, 1);
            BosMdRequestState(work, 4);
            break;
        case BTL_REACTION_CARD_BROKEN:
            BosMdRequestState(work, 0);
            ClearBtlObjActionFlags(e);
            break;
        }
    }
}

void BosMdEndHurt(MdWork* work) {
    s16 i;

    for (i = 0; i < 1; i++) {
        BtlObj* e = &work->sub[i];

        if (work->hurtState[i] == 2 && work->hurtTimer == 0) {
            work->hurtState[i] = 0;
            ClearBtlObjActionFlags(e);
        }
    }
}

void task_bos_md_0(MdWork* work, void* arg) {
    s16 i;

    TaskCreate(&gBtlWork->taskPools[1], &sTaskDescBosMdMap, (void*)&sMdMapData);
    gBtlWork->flags &= 0xFFFFFFFFFFEFFFFF;
    work->state = 0;
    work->nextState = 0;
    work->flags = 0;
    work->statePhase = 0;
    work->timer = 0;
    work->stepsLeft = 0;
    work->hurtTimer = 0;
    work->signals = 0;
    work->bgVisible = 1;

    for (i = 0; i < 1; i++) {
        work->hurtState[i] = 0;
    }

    for (i = 0; i < 2; i++) {
        work->gfx[i].tiles = NULL;
        work->gfx[i].src = NULL;
        work->gfx[i].sprite = NULL;
        work->gfx[i].x = 0;
        work->gfx[i].y = 0;
    }

    work->gfx[0].tiles = AllocSpriteFrameTiles(2432);
    work->gfx[1].tiles = LoadObjTiles(gBosMdForearmTiles, 0x12A0);
    gBtlWork->bossX = 0x11000;
    gBtlWork->bossY = 0x15000;
    gBtlWork->bossZ = 0;
    SetBattleActorPosition(0x7800, gBtlWork->bossY, 0);

    for (i = 0; i < 1; i++) {
        InitEnemyBtlObj(&work->sub[i], &sBosMdEmyKind, gBtlWork->bossX,
                      gBtlWork->bossY, gBtlWork->bossZ);
#ifdef VERSION_EU
        ColliderInit(&work->sub[i].collider, 8, 16, 24);
#else
        ColliderInit(&work->sub[i].collider, 8, 16, 16);
#endif

        if (i == 0) {
            work->sub[i].flags |= 0x400;
        } else {
            work->sub[i].flags |= BTLOBJ_FLAG_NEVER_USES_CARDS;
        }

        work->sub[i].flags |= BTLOBJ_FLAG_FACING_LEFT;
    }

    BosMdSetFrame(work, 0);
    MdAnimStart(work, 0);
    LoadPalette(gBosMdPalette, (void*)PLTT, 32);
    SetBtlPaletteFadeExcluded(0, 1);
    work->bgPalette = gBosMdPalette;
    work->palette = LoadObjPalette(gBosMdPalette, 32);
    SetBtlPaletteFadeExcluded(work->palette->index + 16, 1);
    work->palette2 = LoadObjPalette(gHitFlashPalette, 32);
    SetBtlPaletteFadeExcluded(work->palette2->index + 16, 1);
    TaskPoolInit(&work->tasks, 6);
    TaskPoolInit(&work->tasks2, 1);
    TaskPoolInit(&work->tasks3, 8);
    ScrollBgMapTo(1, (gBtlWork->viewX >> 8) + 72 - work->bgOffsetX,
                  (gBtlWork->viewY >> 8) + 48 - work->bgOffsetY);
}

s32 task_bos_md_1(MdWork* work) {
    void* args[2];
    s32 result;
    s16 i;

    result = 1;
    BosMdHandleReaction(work);

    switch (work->state) {
    case 0:
        result = BosMdUpdateIdle(work);
        break;
    case 1:
        result = BosMdUpdateBite(work);
        break;
    case 2:
        result = BosMdUpdateQuake(work);
        break;
    case 3:
        result = BosMdUpdateFireBreath(work);
        break;
    case 4:
        result = BosMdUpdateDefeat(work);
        break;
    }

    BosMdEndHurt(work);

    if (ConsumeGimmickFlag(0)) {
        args[0] = &work->tasks3;
        args[1] = &work->signals;
        TaskCreate(&work->tasks2, &sTaskDescBosMdDai, args);
    }

    MdAnimUpdate(work);

    if (work->hurtTimer > 0) {
        work->hurtTimer--;
    }

    for (i = 0; i < 1; i++) {
        work->sub[i].x = gBtlWork->bossX
            + sMdFrameDefs[work->anim.frames[work->anim.frame].gfxIndex]
                  .pos[i].x * 256;
        work->sub[i].y = gBtlWork->bossY
            + sMdFrameDefs[work->anim.frames[work->anim.frame].gfxIndex]
                  .pos[i].y * 256;
        work->sub[i].z = gBtlWork->bossZ
            + sMdFrameDefs[work->anim.frames[work->anim.frame].gfxIndex]
                  .pos[i].z * 256;
        ColliderSetPosition(&work->sub[i].collider, work->sub[i].x, work->sub[i].y,
                      work->sub[i].z);
    }

    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&work->tasks2);
    TaskPoolUpdate(&work->tasks3);
    return result;
}

void task_bos_md_2(MdWork* work) {
    s16 x;
    s16 y;
    void* pal;
    void* p1;
    void* p2;
    void* p0;
    s32 i;

    if (!work->bgVisible) {
        return;
    }

    if (StepHitFlash(&work->sub[0])) {
        if (work->bgPalette != gHitFlashPalette) {
            LoadPalette(gHitFlashPalette, (void*)PLTT, 32);
            work->bgPalette = gHitFlashPalette;
        }

        pal = work->palette2;
    } else {
        if (work->bgPalette != gBosMdPalette) {
            LoadPalette(gBosMdPalette, (void*)PLTT, 32);
            work->bgPalette = gBosMdPalette;
        }

        pal = work->palette;
    }

    x = (gBtlWork->viewX >> 8) - (work->bgOffsetX - 72);
    y = (gBtlWork->viewY >> 8) - (work->bgOffsetY - 48);
    ScrollBgMapTo(1, x, y);
    p0 = &work->tasks;
    p1 = &work->tasks2;
    p2 = &work->tasks3;

    for (i = 0; i < 2; i++) {
        s32 wx;
        s32 wy;
        u16 frame;

        wx = (work->gfx[i].x + 224) * 256;
        wy = (work->gfx[i].y + 256) * 256;
        WorldToScreen(&x, &y, wx, wy, work->gfx[i].z * 256);
        frame = GetBattleSpritePriorityFlags(wy);
        DrawSprite(x, y, work->gfx[i].sprite, work->gfx[i].tiles, pal, NULL, frame,
                   -4100 - (wy >> 6));
    }

    TaskPoolDraw(p0);
    TaskPoolDraw(p1);
    TaskPoolDraw(p2);
}

void task_bos_md_3(MdWork* work) {
    void* q;
    void* r;
    void* t;
    s32 i;

    DisableBg(1);

    for (i = 0; i < 1; i++) {
        ColliderUnregister(&work->sub[i].collider);
        ReleaseEnemyBtlObj(&work->sub[i]);
    }

    q = &work->tasks;
    r = &work->tasks2;
    t = &work->tasks3;

    for (i = 0; i < 2; i++) {
        if (work->gfx[i].tiles != NULL) {
            ReleaseObjTiles(work->gfx[i].tiles);
        }
    }

    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
    TaskPoolDestroy(q);
    TaskPoolDestroy(r);
    TaskPoolDestroy(t);
}

void task_bos_md_map_0(MdMapWork* work, MdMapData* arg) {
    LoadBgTiles(0, arg->tiles, arg->tilesSize);
    LoadBgPalette(0, arg->palette, arg->paletteSize);
    SetBgMapBlocks(0, &arg->map, 2, 2);
    gBtlWork->scale = 256;
    gBtlWork->zoomScale = 256;
    gBtlWork->x = 0x10000;
    gBtlWork->y = 0x14000;
    gBtlWork->viewX = 0x10000;
    gBtlWork->viewY = 0x14000;
    gBtlWork->x2 = 0x10000;
    gBtlWork->y2 = 0x14000;
    gBtlWork->zoomX = 0x10000;
    gBtlWork->zoomY = 0x14000;
    gBtlWork->zoomSteps = 15;
    gBtlWork->rotation = 0;
    BtlMapResetShake();
    ScrollBgMapTo(0, gBtlWork->viewX >> 8, gBtlWork->viewY >> 8);
}

s32 task_bos_md_map_1(MdMapWork* work) {
    s32 dx;
    s32 dy;

    BtlMapUpdateShake();
    dx = (gBtlWork->x2 - gBtlWork->x) >> 3;
    dy = (gBtlWork->y2 - gBtlWork->y) >> 3;

    if (dx > 1280) {
        dx = 1280;
    } else if (dx < -1280) {
        dx = -1280;
    }

    gBtlWork->x += dx;
    gBtlWork->y += dy;
    gBtlWork->viewX = gBtlWork->x;
    gBtlWork->viewY = gBtlWork->y;

    if (gBtlWork->viewX - 30720 < gBtlWork->xMin * 256) {
        gBtlWork->viewX = (gBtlWork->xMin + 120) * 256;
    } else if (gBtlWork->viewX + 30720 > (gBtlWork->xMax + 96) * 256) {
        gBtlWork->viewX = (gBtlWork->xMax - 24) * 256;
    }

    if (gBtlWork->viewY + 20480 < gBtlWork->yMin * 256) {
        gBtlWork->viewY = (gBtlWork->yMin - 80) * 256;
    } else if (gBtlWork->viewY + 20480 > gBtlWork->yMax * 256) {
        gBtlWork->viewY = (gBtlWork->yMax - 80) * 256;
    }

    gBtlWork->viewY += BtlMapGetShake();
    ScrollBgMapTo(0, (gBtlWork->viewX >> 8) + 8, (gBtlWork->viewY >> 8) + 40);
    return 1;
}

void BosMdFireHandleReaction(MdFireWork* work) {
    BtlObj* e;

    e = &work->sub;

    switch (UpdateBtlObjReaction(e)) {
    case BTL_REACTION_HURT:
    case BTL_REACTION_STUNNED:
    case BTL_REACTION_GRAVITY:
        work->flashTimer = 30;
        work->state = 3;
        break;
    case BTL_REACTION_DEFEATED:
    case BTL_REACTION_GRAVITY_DEFEATED:
        if (GetRandom() % 100 <= 49) {
            if ((gBtlWork->flags & 0x100000) == 0) {
                DropGimmickCard(0, e->x, e->y, e->z);
            }
        }

        SetBtlObjUnhittable(e, 1);
        work->scaleSteps = 30;
        work->state = 4;
        break;
    }
}

u8 BosMdFireUpdateMotion(MdFireWork* work) {
    u8 result;
    BtlObj* e;
    u8 a;

    result = 1;
    e = &work->sub;

    if ((*work->flags & 2) && work->state != 4) {
        SetBtlObjUnhittable(e, 1);
        work->scaleSteps = 30;
        work->state = 4;
    }

    switch (work->state) {
        case 0:
            work->scaleSteps--;

            if (work->scaleSteps <= 0) {
                SetBtlObjUnhittable(e, 0);
                work->state = 1;
            }

            break;
        case 1:
            switch (work->motion) {
                case 0:
                    if (work->timer > 0) {
                        work->timer--;

                        if (work->timer <= 0) {
                            switch (work->pattern) {
                            case 0:
                            case 1:
                            case 2:
                            case 4:
                                a = BosGaGetAngle(work->x, work->y,
                                                  gBtlWork->actor->x,
                                                  gBtlWork->actor->y);
                                work->vx = gSineTable[a] * 3;
                                work->vy = -gSineTable[a + 0x40] * 3;
                                work->timer = 90;
                                work->motion = 1;
                                break;
                            case 3:
                                work->motion = 2;
                                break;
                            case 5:
                                work->motion = 3;
                                break;
                            }
                        }
                    }

                    break;
                case 1:
                    work->x += work->vx;
                    work->y += work->vy;
                    work->timer--;

#ifdef VERSION_EU
                    if (work->timer <= 0 || work->y <= 0x12FFF) {
#else
                    if (work->timer <= 0 || work->y <= 0x117FF) {
#endif
                        SetBtlObjUnhittable(e, 1);
                        work->scaleSteps = 30;
                        work->state = 4;
                    }

                    break;
                case 2:
                    work->angle++;
                    work->x = gSineTable[work->angle] * 40 + work->centerX;
                    work->y = -gSineTable[work->angle + 0x40] * 40 + work->centerY;
                    break;
                case 3:
                    work->angle++;
                    work->x = gSineTable[work->angle] * 32 + work->centerX;
                    break;
            }

            if (work->contactCooldown > 0) {
                work->contactCooldown--;
            } else if (ColliderIsTouchingType(&work->sub.collider, 1)) {
                m4aSongNumStart(SONG_SND_714);
                gBtlWork->actor->flags |= BTLOBJ_FLAG_HAZARD_PENDING;
                work->contactCooldown = 60;
            }

            break;
        case 2:
            break;
        case 3:
            if (work->flashTimer == 0) {
                work->state = 1;
                ClearBtlObjActionFlags(e);
            }

            break;
        case 4:
            work->scaleSteps--;

            if (work->scaleSteps <= 0) {
                result = 0;
            }

            break;
    }

    return result;
}

void BosMdFirePlace(MdFireWork* work) {
    const MdFirePoint* p;

    switch (work->pattern) {
    case 0:
    case 1:
    case 2:
        p = sMdFireDefs[work->pattern].points + work->index;
        work->x = p->x * 256;
        work->y = p->y * 256;
        work->timer = p->delay;
        work->motion = 0;
        break;
    case 3:
        work->angle = work->index * 256 / 6;
        work->centerX = 0x8000;
        work->centerY = 0x14800;
        work->x = gSineTable[work->angle] * 40 + work->centerX;
        work->y = -gSineTable[work->angle + 0x40] * 40 + work->centerY;
        work->timer = 60;
        work->motion = 0;
        break;
    case 4:
        work->x = GetRandom() % 96 * 256 + 0x9800;
        work->y = work->index * 4096 + 0x11800;
        work->timer = work->index * 60 + 240;
        work->motion = 0;
        break;
    case 5:
        work->angle = 0;
        work->centerX = 0x9800;
        work->x = gSineTable[work->angle] * 32 + work->centerX;
        work->y = work->index * 4096 + 0x11800;
        work->timer = work->index * 256 / 6 + 60;
        work->motion = 0;
        break;
    }
}

void task_bos_md_fire_0(MdFireWork* work, MdFireArg* arg) {
    MdFireArg a;
    s16 i;
    s16 n;

    work->flashTimer = 0;
    work->contactCooldown = 0;
    work->scale = 25;
    work->scaleSteps = 30;
    work->state = 0;
    work->z = 0;
    work->pattern = arg->pattern;
    work->index = arg->index;
    work->flags = arg->flags;
    BosMdFirePlace(work);
    InitEnemyBtlObj(&work->sub, &sBosMdFireEmyKind, work->x, work->y, work->z);
    ColliderInit(&work->sub.collider, 3, 16, 16);
    ColliderSetPosition(&work->sub.collider, work->sub.x, work->sub.y,
                  work->sub.z);
    work->sub.flags |= BTLOBJ_FLAG_NEVER_USES_CARDS;
    work->sub.hp = 20;
    work->sub.maxHp = 20;
    SetBtlObjUnhittable(&work->sub, 1);
    work->palette = LoadObjPalette(gBosMdFirePalette, 32);
    work->palette2 = LoadObjPalette(gHitFlashPalette, 32);
    work->tiles = LoadObjTiles(gBosMdFireTiles, 0x800);
    AnimInit(&work->anim, gBosMdFireAnims, gBosMdFireFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    a.pool = NULL;
    a.pattern = arg->pattern;
    a.flags = arg->flags;

    if (arg->pool != NULL) {
        if (work->pattern <= 2) {
            n = sMdFireDefs[work->pattern].count;
        } else {
            n = 6;
        }

        for (i = 1; i < n; i++) {
            a.index = i;
            TaskCreate(arg->pool, &sTaskDescBosMdFire, &a);
        }
    }
}

u8 task_bos_md_fire_1(MdFireWork* work) {
    u8 result;

    BosMdFireHandleReaction(work);
    result = BosMdFireUpdateMotion(work);

    if (work->flashTimer > 0) {
        work->flashTimer--;
    }

    work->sub.x = work->x;
    work->sub.y = work->y;
    work->sub.z = work->z;
    ColliderSetPosition(&work->sub.collider, work->sub.x, work->sub.y,
                  work->sub.z);
    return result;
}

void task_bos_md_fire_2(MdFireWork* work) {
    s16 x;
    s16 y;
    void* gfx;
    ObjAffine* sprite;
    u16 frame;

    if (work->flashTimer > 0 && (gFrameCounter & 1)) {
        gfx = work->palette2;
    } else {
        gfx = work->palette;
    }

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    frame = GetBattleSpritePriorityFlags(work->y);

    if (work->state == 0) {
        ApproachValue(&work->scale, 0x100, work->scaleSteps);
        sprite = AllocObjAffine(0, work->scale, work->scale, 0);
    } else if (work->state == 4) {
        ApproachValue(&work->scale, 25, work->scaleSteps);
        sprite = AllocObjAffine(0, work->scale, work->scale, 0);
    } else {
        sprite = NULL;
    }

    DrawSprite(x, y, AnimUpdate(&work->anim), work->tiles, gfx,
                  sprite, frame, -4100 - (work->y >> 8) * 4);
}

void task_bos_md_fire_3(MdFireWork* work) {
    ColliderUnregister(&work->sub.collider);
    ReleaseEnemyBtlObj(&work->sub);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
    ReleaseObjTiles(work->tiles);
}

void task_bos_md_dai_0(MdDaiWork* work, void** args) {
    Collider* p;

    gBtlWork->flags |= 0x100000;
    work->flags = args[1];
    work->pool = args[0];
    work->level = 0;
    work->state = 0;
    work->x = 0x8000;
    work->y = 0x14F00;
    work->z = 0;
    work->dropSteps = 20;
    work->dropZ = -40960;
    p = &work->collider;
    ColliderInit(p, 7, 24, 24);
    ColliderSetPosition(p, work->x, work->y, work->z);
    ColliderSetDisabled(p, 1);
    work->palette = LoadObjPalette(gBosMdDaiPalette, 32);
    work->tiles = LoadObjTiles(gBosMdDaiTiles, 0x480);
}

s32 task_bos_md_dai_1(MdDaiWork* work) {
    s32 result;
    s32 args[3];
    s16 i;
    s16 n;

    result = 1;

    switch (work->state) {
    case 0:
        ApproachValue(&work->dropZ, 0, work->dropSteps);
        work->dropSteps--;

        if (work->dropSteps <= 0) {
            ColliderSetDisabled(&work->collider, 0);
            ColliderSetHeight(&work->collider, 8);
            work->dropZ = work->z - 0xA000;
            m4aSongNumStart(SONG_BTL_DRGN_GIMIC);
            work->level = 1;
            work->dropSteps = 20;
            work->state = 1;
        }

        break;
    case 1:
        ApproachValue(&work->dropZ, -3584, work->dropSteps);
        work->dropSteps--;

        if (work->dropSteps <= 0) {
            ColliderSetDisabled(&work->collider, 0);
            ColliderSetHeight(&work->collider, 16);
            work->dropZ = work->z - 0xA000;
            m4aSongNumStart(SONG_BTL_DRGN_GIMIC);
            work->level = 2;
            work->dropSteps = 20;
            work->state = 2;
        }

        break;
    case 2:
        ApproachValue(&work->dropZ, -7168, work->dropSteps);
        work->dropSteps--;

        if (work->dropSteps <= 0) {
            ColliderSetDisabled(&work->collider, 0);
            ColliderSetHeight(&work->collider, 24);
            m4aSongNumStart(SONG_BTL_DRGN_GIMIC);
            work->level = 3;
            *work->flags &= 0xFFFE;
            work->state = 3;
        }

        break;
    case 3:
        if (*work->flags & 1) {
            *work->flags &= 0xFFFE;
            args[0] = work->x;
            args[1] = work->y;
            args[2] = -((work->level - 1) * 7 << 9);
            n = GetRandom() % 3 + 3;

            for (i = 0; i < n; i++) {
                TaskCreate(work->pool, &sTaskDescBosMdHahen, args);
            }

            work->level--;

            if (work->level <= 0) {
                ColliderSetDisabled(&work->collider, 1);
                result = 0;
            } else {
                ColliderSetHeight(&work->collider, work->level * 8);
            }
        }

        break;
    }

    return result;
}

void task_bos_md_dai_2(MdDaiWork* work) {
    s16 x;
    s16 y;
    u16 frame;

    WorldToScreen(&x, &y, work->x, work->y, work->z + work->dropZ);
    frame = GetBattleSpritePriorityFlags(work->y);

    if (work->state <= 2) {
        DrawSprite(x, y + 24, gBosMdDaiFrame0, work->tiles, work->palette, NULL,
                      frame, -4100 - (work->y >> 8) * 4);
        DrawSprite(x, y, gBosMdDaiFrame1, work->tiles, work->palette, NULL, frame,
                      -4100 - (work->y >> 8) * 4);
        DrawSprite(x + 8, y - 16, gBosMdDaiFrame0, work->tiles, work->palette, NULL,
                      frame, -4100 - (work->y >> 8) * 4);
    }

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    frame = GetBattleSpritePriorityFlags(work->y);

    if (work->level > 0) {
        DrawSprite(x, y, gBosMdDaiFrames[work->level + 1], work->tiles,
                      work->palette, NULL, frame,
                      -4100 - (work->y >> 8) * 4);
    }
}

void task_bos_md_dai_3(MdDaiWork* work) {
    ColliderUnregister(&work->collider);
    ReleaseObjPalette(work->palette);
    ReleaseObjTiles(work->tiles);
    gBtlWork->flags &= 0xFFFFFFFFFFEFFFFF;
}

void task_bos_md_hahen_0(MdHahenWork* work, s32* src) {
    u8 angle;
    s32 speed;

    work->x = src[0];
    work->y = src[1];
    work->z = src[2];
    angle = GetRandom();
    speed = (GetRandom() & 0x1FF) + 0x100;
    work->vx = -gSineTable[angle + 0x40] * speed >> 8;
    work->vy = gSineTable[angle] * speed >> 8;
    work->vz = -((GetRandom() & 0x1FF) + 0x100);
    work->timer = 3;
    work->palette = LoadObjPalette(gBosMdDaiPalette, 32);
    work->tiles = LoadObjTiles(gBosMdDaiTiles, 0x480);
    work->gfx = gBosMdDaiFrames[GetRandom() % 2];
}

s32 task_bos_md_hahen_1(MdHahenWork* work) {
    s32 result;

    result = 1;
    work->x += work->vx;
    work->y += work->vy;

#ifdef VERSION_EU
    if (work->y <= 0x12FFF) {
#else
    if (work->y <= 0x117FF) {
#endif
        work->vy = -work->vy;
    }

    work->z += work->vz;
    work->vz += 102;

    if (work->z > 0) {
        work->z = 0;
        work->vz = -(work->vz * 8 / 10);
        work->timer--;

        if ((s16)work->timer <= 0) {
            result = 0;
        }
    }

    return result;
}

void task_bos_md_hahen_2(MdHahenWork* work) {
    s16 x;
    s16 y;
    u16 frame;
    s32 flag;

    flag = gFrameCounter & 1;

    if (flag != 0) {
        return;
    }

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    frame = GetBattleSpritePriorityFlags(work->y);
    DrawSprite(x, y, work->gfx, work->tiles, work->palette,
                  NULL, frame, -4100 - (work->y >> 8) * 4);
}

void task_bos_md_hahen_3(MdHahenWork* work) {
    ReleaseObjPalette(work->palette);
    ReleaseObjTiles(work->tiles);
}
