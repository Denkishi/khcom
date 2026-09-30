#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "msg_api.h"
#include "display.h"
#include "fade.h"
#include "text.h"
#include "monsgage.h"
#include "bos5.h"
#include "anim.h"
#include "ms_charge.h"
#include "mode_mapinspect.h"
#include "mode_worldwarp.h"
#include "mode_battle_data.h"
#include "worldinspect_assets.h"
#include "sprites_bos5.h"
#include "sprites_worldinspect.h"
#include "sprites_room.h"
#include "chara_types.h"
#include "chara_api.h"
#include "prize_types.h"
#include "gba/keys.h"
#include "gba/io_reg.h"
#include "btl_api.h"
#include "malloc.h"
#include "songs.h"
#include "worldselect_assets.h"
#include "jiminy_records_assets.h"
#include "world_types.h"

static const EmyKind sBosGaEmyKind =
{32, 100, 16, 16, 0, 100, EMY_KIND_FLAG_NO_COLLIDER}
;

static const GaEntryDef sGaEntryDefs[6] = {
#if defined(VERSION_US)
    {256, 0, 0, -15872, 0, 0, gRoomAssetUs_099939FA, gUnk_09EF96A4, gUnk_09EF9684, 8, 0},
    {256, -2560, 2048, -25088, 0, 0, gRoomAssetUs_09995E9C, gUnk_09EF96C8, gUnk_09EF96B0, 6, 0},
    {256, 2560, 5632, -14848, 0, 0, gRoomAssetUs_09996B82, gUnk_09EF96EC, gUnk_09EF96D0, 7, 0},
    {256, -11264, -3328, -12288, 0, 0, gRoomAssetUs_09997F64, gUnk_09EF9710, gUnk_09EF96F4, 7, 0},
    {256, 3840, 512, -2048, 0, 0, gRoomAssetUs_09999244, gUnk_09EF971C, gUnk_09EF9718, 1, 0},
    {256, -3328, -1792, -2048, 0, 0, gRoomAssetUs_099995FC, gUnk_09EF9724, gUnk_09EF9720, 1, 0},
#elif defined(VERSION_JP)
    {256, 0, 0, -15872, 0, 0, gRoomAssetJp_0994850E, gUnk_09EF96A4, gUnk_09EF9684, 8, 0},
    {256, -2560, 2048, -25088, 0, 0, gRoomAssetJp_0994A9B0, gUnk_09EF96C8, gUnk_09EF96B0, 6, 0},
    {256, 2560, 5632, -14848, 0, 0, gRoomAssetJp_0994B696, gUnk_09EF96EC, gUnk_09EF96D0, 7, 0},
    {256, -11264, -3328, -12288, 0, 0, gRoomAssetJp_0994CA78, gUnk_09EF9710, gUnk_09EF96F4, 7, 0},
    {256, 3840, 512, -2048, 0, 0, gRoomAssetJp_0994DD58, gUnk_09EF971C, gUnk_09EF9718, 1, 0},
    {256, -3328, -1792, -2048, 0, 0, gRoomAssetJp_0994E110, gUnk_09EF9724, gUnk_09EF9720, 1, 0},
#elif defined(VERSION_EU)
    {256, 0, 0, -15872, 0, 0, gRoomAssetEu_09999CB6, gUnk_09EF96A4, gUnk_09EF9684, 8, 0},
    {256, -2560, 2048, -25088, 0, 0, gRoomAssetEu_0999C158, gUnk_09EF96C8, gUnk_09EF96B0, 6, 0},
    {256, 2560, 5632, -14848, 0, 0, gRoomAssetEu_0999CE3E, gUnk_09EF96EC, gUnk_09EF96D0, 7, 0},
    {256, -11264, -3328, -12288, 0, 0, gRoomAssetEu_0999E220, gUnk_09EF9710, gUnk_09EF96F4, 7, 0},
    {256, 3840, 512, -2048, 0, 0, gRoomAssetEu_0999F500, gUnk_09EF971C, gUnk_09EF9718, 1, 0},
    {256, -3328, -1792, -2048, 0, 0, gRoomAssetEu_0999F8B8, gUnk_09EF9724, gUnk_09EF9720, 1, 0},
#endif
};

static const BosMapConfig sBosMapConfig =
#if defined(VERSION_US)
{gRoomAssetUs_099A899C, 16352, 0, gRoomAssetUs_09A3C75C, 320, 0, {gRoomAssetUs_09A1E0DC, gRoomAssetUs_09A1F0DC, gRoomAssetUs_09A1E8DC, gRoomAssetUs_09A1F8DC}}
#elif defined(VERSION_JP)
{gRoomAssetJp_0995D424, 16352, 0, gRoomAssetJp_099F11E4, 320, 0, {gRoomAssetJp_099D2B64, gRoomAssetJp_099D3B64, gRoomAssetJp_099D3364, gRoomAssetJp_099D4364}}
#elif defined(VERSION_EU)
{gRoomAssetEu_099B6920, 16352, 0, gRoomAssetEu_09A9A220, 320, 0, {gRoomAssetEu_09A6FCA0, gRoomAssetEu_09A70CA0, gRoomAssetEu_09A704A0, gRoomAssetEu_09A714A0}}
#endif
;

static const s32 sBos5TanTable[32] = {
    6,
    12,
    18,
    25,
    31,
    37,
    44,
    50,
    57,
    64,
    70,
    77,
    84,
    91,
    98,
    106,
    113,
    121,
    128,
    136,
    145,
    153,
    162,
    171,
    180,
    189,
    199,
    210,
    220,
    232,
    243,
    256,
};

TaskDesc gTaskDescBosGa = {
    "task_bos_ga",
    (TaskInitFunc)task_bos_ga_0,
    (TaskUpdateFunc)task_bos_ga_1,
    (TaskDrawFunc)task_bos_ga_2,
    (TaskDestroyFunc)task_bos_ga_3,
    sizeof(GaWork),
};

static const EmyKind sBosMdEmyKind = { 37, 1000, 16, 16, 0, 60, EMY_KIND_FLAG_NO_COLLIDER };

static const MdMapData sMdMapData = {
    gUnk_099AC97C, 32768, { 0, 0 }, gUnk_09A3C8BC, 192, { 0, 0 }, { gUnk_09A208DC, gUnk_09A210DC, gUnk_09A218DC, gUnk_09A220DC }
};

static const MdFrameDef sMdFrameDefs[41] = {
    {
        32, 0, gUnk_099B497C, 16864, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A228DC },
        { { 0, 112, 0xFF90, 0, gUnk_099D559C, 1952, gUnk_099A7E04 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7D06 } },
        { { -100, 0, -45, 0 } },
    },
    {
        32, 0, gUnk_099B497C, 4480, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A228DC },
        { { 0, 112, 0xFF90, 0, gUnk_099D559C, 1952, gUnk_099A7E04 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7D06 } },
        { { -100, 0, -45, 0 } },
    },
    {
        32, 0, gUnk_099B8B5C, 3872, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A230DC },
        { { 0, 112, 0xFF90, 0, gUnk_099D5D3C, 2176, gUnk_099A7E54 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7D34 } },
        { { -101, 0, -34, 0 } },
    },
    {
        32, 0, gUnk_099B9A7C, 4064, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A238DC },
        { { 0, 112, 0xFF90, 0, gUnk_099D65BC, 2048, gUnk_099A7EA0 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -103, 0, -28, 0 } },
    },
    {
        0, 65521, gUnk_099C2E3C, 4448, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A280DC },
        { { 0xFFF8, 112, 0xFF90, 0, gUnk_099DED9C, 2368, gUnk_099A8400 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -131, 0, -108, 0 } },
    },
    {
        3, 65524, gUnk_099C3F9C, 4448, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A288DC },
        { { 0, 112, 0xFF90, 0, gUnk_099DF6DC, 2400, gUnk_099A8468 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7D34 } },
        { { -142, 0, -105, 0 } },
    },
    {
        4, 65529, gUnk_099C50FC, 4480, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A290DC },
        { { 0, 112, 0xFF8F, 0, gUnk_099E003C, 2432, gUnk_099A84C4 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7D06 } },
        { { -145, 0, -94, 0 } },
    },
    {
        43, 65504, gUnk_099BAA5C, 3712, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A240DC },
        { { 0, 112, 0xFF90, 0, gUnk_099D6DBC, 2368, gUnk_099A7EF8 }, { 11, 56, 0xFFE0, 0, gUnk_099D42FC, 4768, gUnk_099A7C98 } },
        { { -67, 0, -126, 0 } },
    },
    {
        43, 65528, gUnk_099BB8DC, 3712, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A248DC },
        { { 0, 112, 0xFF90, 0, gUnk_099D76FC, 1952, gUnk_099A7F48 }, { 24, 56, 0xFFE2, 0, gUnk_099D42FC, 4768, gUnk_099A7D6E } },
        { { -46, 0, -154, 0 } },
    },
    {
        31, 0, gUnk_099BC75C, 4160, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A250DC },
        { { 0, 112, 0xFF90, 0, gUnk_099D7E9C, 2112, gUnk_099A7FAC }, { 2, 56, 0xFFF2, 0, gUnk_099D42FC, 4768, gUnk_099A7DBE } },
        { { -105, 0, -135, 0 } },
    },
    {
        29, 65531, gUnk_099BD79C, 4480, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A258DC },
        { { 0, 112, 0xFF90, 0, gUnk_099D86DC, 2080, gUnk_099A8004 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7D06 } },
        { { -123, 0, -42, 0 } },
    },
    {
        25, 65527, gUnk_099BE91C, 4480, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A260DC },
        { { 0, 112, 0xFF91, 0, gUnk_099D8EFC, 2368, gUnk_099A805C }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -123, 0, -30, 0 } },
    },
    {
        22, 65519, gUnk_099BFA9C, 4448, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A268DC },
        { { 0xFFFF, 112, 0xFF90, 0, gUnk_099D983C, 2432, gUnk_099A80D0 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -129, 0, -36, 0 } },
    },
    {
        36, 65518, gUnk_099C0BFC, 4384, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A270DC },
        { { 0, 112, 0xFF90, 0, gUnk_099DA1BC, 2208, gUnk_099A8134 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -115, 0, -31, 0 } },
    },
    {
        35, 65533, gUnk_099C1D1C, 4384, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A278DC },
        { { 0, 112, 0xFF90, 0, gUnk_099DAA5C, 2016, gUnk_099A8190 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -98, 0, -49, 0 } },
    },
    {
        35, 65530, gUnk_099C2E3C, 4448, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A280DC },
        { { 0, 112, 0xFF90, 0, gUnk_099DB23C, 2336, gUnk_099A81E0 }, { 20, 56, 0xFFCF, 0, gUnk_099D42FC, 4768, gUnk_099A7D6E } },
        { { -94, 0, -100, 0 } },
    },
    {
        45, 65535, gUnk_099C3F9C, 4448, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A288DC },
        { { 0, 112, 0xFF90, 0, gUnk_099DBB5C, 1920, gUnk_099A8218 }, { 19, 56, 0xFFED, 0, gUnk_099D42FC, 4768, gUnk_099A7D90 } },
        { { -104, 0, -94, 0 } },
    },
    {
        48, 6, gUnk_099C50FC, 4480, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A290DC },
        { { 0, 112, 0xFF90, 0, gUnk_099DC2DC, 1632, gUnk_099A8270 }, { 17, 56, 0xFFF3, 0, gUnk_099D42FC, 4768, gUnk_099A7DBE } },
        { { -105, 0, -79, 0 } },
    },
    {
        56, 11, gUnk_099C627C, 4448, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A298DC },
        { { 0, 112, 0xFF90, 0, gUnk_099DC93C, 1408, gUnk_099A82B0 }, { 23, 56, 0xFFF8, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -103, 0, -57, 0 } },
    },
    {
        35, 65533, gUnk_099C73DC, 4448, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A2A0DC },
        { { 0, 112, 0xFF9A, 0, gUnk_099DCEBC, 2176, gUnk_099A82E4 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -98, 0, -78, 0 } },
    },
    {
        36, 65535, gUnk_099C853C, 4480, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A2A8DC },
        { { 0, 112, 0xFF92, 0, gUnk_099DD73C, 1920, gUnk_099A8328 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7D34 } },
        { { -102, 0, -59, 0 } },
    },
    {
        38, 0, gUnk_099C96BC, 4480, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A2B0DC },
        { { 0, 112, 0xFF89, 0, gUnk_099DDEBC, 1824, gUnk_099A8368 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7D34 } },
        { { -102, 0, -52, 0 } },
    },
    {
        37, 0, gUnk_099CA83C, 4448, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A2B8DC },
        { { 0, 112, 0xFF8D, 0, gUnk_099DE5DC, 1984, gUnk_099A83B4 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7D06 } },
        { { -100, 0, -50, 0 } },
    },
    {
        5, 5, gUnk_099B9A7C, 4064, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A238DC },
        { { 0xFFFF, 112, 0xFF90, 0, gUnk_099E25DC, 2336, gUnk_099A865C }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -128, 0, -22, 0 } },
    },
    {
        41, 65504, gUnk_099CDBDC, 4480, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A2D0DC },
        { { 0, 112, 0xFF90, 0, gUnk_099D6DBC, 2368, gUnk_099A7EF8 }, { 13, 56, 0xFFDF, 0, gUnk_099D42FC, 4768, gUnk_099A7C98 } },
        { { -108, 0, -88, 0 } },
    },
    {
        46, 65499, gUnk_099BAA5C, 3712, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A240DC },
        { { 11, 112, 0xFF85, 0, gUnk_099DCEBC, 2176, gUnk_099A82E4 }, { 29, 56, 0xFFBA, 0, gUnk_099D42FC, 4768, gUnk_099A7D6E } },
        { { -62, 0, -126, 0 } },
    },
    {
        60, 65491, gUnk_099CB99C, 4320, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A2C0DC },
        { { 21, 112, 0xFF70, 0, gUnk_099DD73C, 1920, gUnk_099A8328 }, { 40, 56, 0xFFC4, 0, gUnk_099D42FC, 4768, gUnk_099A7D90 } },
        { { -3, 0, -168, 0 } },
    },
    {
        36, 65527, gUnk_099BC75C, 4160, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A250DC },
        { { 0, 112, 0xFF89, 0, gUnk_099DDEBC, 1824, gUnk_099A8368 }, { 17, 56, 0xFFF3, 0, gUnk_099D42FC, 4768, gUnk_099A7DBE } },
        { { -103, 0, -142, 0 } },
    },
    {
        1, 65530, gUnk_099C627C, 4448, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A298DC },
        { { 0, 112, 0xFF8F, 0, gUnk_099E003C, 2432, gUnk_099A84C4 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -158, 0, -75, 0 } },
    },
    {
        36, 65518, gUnk_099C0BFC, 4384, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A270DC },
        { { 0, 112, 0xFF90, 0, gUnk_099DA1BC, 2208, gUnk_099A8134 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -115, 0, -31, 0 } },
    },
    {
        35, 65533, gUnk_099C1D1C, 4384, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A278DC },
        { { 0, 112, 0xFF90, 0, gUnk_099DAA5C, 2016, gUnk_099A8190 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -98, 0, -49, 0 } },
    },
    {
        0, 65525, gUnk_099CB99C, 4320, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A2C0DC },
        { { 0xFFF8, 112, 0xFF90, 0, gUnk_099DED9C, 2368, gUnk_099A8400 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -62, 0, -136, 0 } },
    },
    {
        0, 65530, gUnk_099CCA7C, 4448, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A2C8DC },
        { { 0, 112, 0xFF90, 0, gUnk_099DF6DC, 2400, gUnk_099A8468 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -98, 0, -135, 0 } },
    },
    {
        0, 65535, gUnk_099CDBDC, 4480, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A2D0DC },
        { { 0, 112, 0xFF8F, 0, gUnk_099E003C, 2432, gUnk_099A84C4 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -149, -20, -38, 0 } },
    },
    {
        0, 65535, gUnk_099CED5C, 4256, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A2D8DC },
        { { 0, 112, 0xFF90, 0, gUnk_099E09BC, 2432, gUnk_099A8538 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -140, 17, -24, 0 } },
    },
    {
        0, 65532, gUnk_099CFDFC, 4480, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A2E0DC },
        { { 0, 112, 0xFF90, 0, gUnk_099E133C, 2400, gUnk_099A8590 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -171, 0, -78, 0 } },
    },
    {
        0, 14, gUnk_099D0F7C, 4480, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_09A2F0DC, gUnk_09A2E8DC },
        { { 0, 112, 0xFF90, 0, gUnk_099E1C9C, 2368, gUnk_099A8600 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -190, -20, -33, 0 } },
    },
    {
        3, 12, gUnk_099D20FC, 4480, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_09A300DC, gUnk_09A2F8DC },
        { { 0, 112, 0xFF90, 0, gUnk_099E25DC, 2336, gUnk_099A865C }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -181, 17, -25, 0 } },
    },
    {
        31, 2, gUnk_099D327C, 4224, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A308DC },
        { { 0, 112, 0xFF90, 0, gUnk_099E2EFC, 1920, gUnk_099A86C0 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7D06 } },
        { { -86, 0, -26, 0 } },
    },
    {
        32, 65530, gUnk_099BAA5C, 3712, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A240DC },
        { { 0, 112, 0xFF90, 0, gUnk_099D559C, 1952, gUnk_099A7E04 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -79, 0, -98, 0 } },
    },
    {
        32, 4, gUnk_099C0BFC, 4384, 0,
        { gUnk_08125E24, gUnk_08125E24, gUnk_08125E24, gUnk_09A270DC },
        { { 0, 112, 0xFF90, 0, gUnk_099E2EFC, 1920, gUnk_099A86C0 }, { 0, 56, 0xFFEE, 0, gUnk_099D42FC, 4768, gUnk_099A7CD2 } },
        { { -119, 19, -27, 0 } },
    },
};

static const MdAnimFrame sUnk_09992D34[4] = { { 1, 18 }, { 2, 12 }, { 3, 24 }, { 2, 12 } };

static const MdAnimFrame sUnk_09992D44[4] = { { 4, 18 }, { 5, 12 }, { 6, 24 }, { 5, 12 } };

static const MdAnimFrame sUnk_09992D54[4] = { { 7, 12 }, { 8, 30 }, { 9, 3 }, { 10, 6 } };

static const MdAnimFrame sUnk_09992D64[2] = { { 11, 24 }, { 12, 6 } };

static const MdAnimFrame sUnk_09992D6C[2] = { { 13, 6 }, { 14, 6 } };

static const MdAnimFrame sUnk_09992D74[10] = { { 15, 6 }, { 16, 3 }, { 17, 3 }, { 18, 24 }, { 1, 6 }, { 19, 6 }, { 20, 3 }, { 21, 3 }, { 22, 24 }, { 1, 6 } };

static const MdAnimFrame sUnk_09992D9C[8] = { { 23, 6 }, { 24, 6 }, { 25, 6 }, { 26, 30 }, { 27, 3 }, { 28, 6 }, { 29, 6 }, { 30, 6 } };

static const MdAnimFrame sUnk_09992DBC[6] = { { 39, 3 }, { 31, 24 }, { 32, 3 }, { 33, 3 }, { 34, 24 }, { 40, 3 } };

static const MdAnimFrame sUnk_09992DD4[8] = { { 39, 3 }, { 31, 24 }, { 32, 3 }, { 35, 3 }, { 36, 3 }, { 37, 24 }, { 34, 6 }, { 40, 6 } };

static const MdAnimFrame sUnk_09992DF4[11] = { { 39, 3 }, { 31, 24 }, { 32, 3 }, { 33, 3 }, { 34, 24 }, { 35, 6 }, { 32, 12 }, { 36, 3 }, { 37, 24 }, { 34, 6 }, { 38, 6 } };

static const MdAnimFrame sUnk_09992E20[1] = { { 1, 32767 } };

static const MdAnimDef sMdAnimDefs[11] = {
    { sUnk_09992D34, 4, 0 },
    { sUnk_09992D44, 4, 0 },
    { sUnk_09992D54, 4, 0 },
    { sUnk_09992D64, 2, 0 },
    { sUnk_09992D6C, 2, 0 },
    { sUnk_09992D74, 10, 0 },
    { sUnk_09992D9C, 8, 0 },
    { sUnk_09992DBC, 6, 0 },
    { sUnk_09992DD4, 8, 0 },
    { sUnk_09992DF4, 11, 0 },
    { sUnk_09992E20, 1, 0 },
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

static const MdFirePoint sUnk_09992E98[4] = { { 88, 288, 240, 0 }, { 56, 312, 330, 0 }, { 72, 336, 420, 0 }, { 104, 360, 510, 0 } };

static const MdFirePoint sUnk_09992EB8[4] = { { 128, 304, 0, 0 }, { 104, 324, 0, 0 }, { 144, 344, 0, 0 }, { 112, 364, 0, 0 } };

static const MdFirePoint sUnk_09992ED8[4] = { { 128, 288, 0, 0 }, { 156, 312, 0, 0 }, { 172, 336, 0, 0 }, { 144, 360, 0, 0 } };

static const MdFireDef sMdFireDefs[6] = {
    { sUnk_09992E98, 4, 0 },
    { sUnk_09992EB8, 4, 0 },
    { sUnk_09992ED8, 4, 0 },
    { sUnk_09992E98, 4, 0 },
    { sUnk_09992E98, 4, 0 },
    { sUnk_09992E98, 4, 0 },
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

#ifdef VERSION_EU
static void* sWorldselectBg1Maps[5] = {
    gUnk_09A31FDC,
    gUnkEu_09A840A0,
    gUnkEu_09A84FA0,
    gUnkEu_09A84AA0,
    gUnkEu_09A845A0,
};

static void* sWorldselectNameTileData[5] = {
    gUnk_099F4D3C,
    gUnkEu_09A0A480,
    gUnkEu_09A1DC80,
    gUnkEu_09A17480,
    gUnkEu_09A10C80,
};

static void* sWorldselectTitleGfx[5] = {
    gUnk_0999CB90,
    gUnkEu_099A31F4,
    gUnkEu_099A3DF4,
    gUnkEu_099A39CC,
    gUnkEu_099A35E0,
};

static void* sWorldselectTitleTileData[5] = {
    gUnk_0999CBB6,
    gUnkEu_099A3220,
    gUnkEu_099A3E1A,
    gUnkEu_099A39F2,
    gUnkEu_099A360C,
};

#endif

static void* sWorldselectPaletteCycle[30] = {
    gUnk_09A3CA3C,
    gUnk_09A3CA5C,
    gUnk_09A3CA7C,
    gUnk_09A3CA9C,
    gUnk_09A3CABC,
    gUnk_09A3CADC,
    gUnk_09A3CAFC,
    gUnk_09A3CB1C,
    gUnk_09A3CB3C,
    gUnk_09A3CB5C,
    gUnk_09A3CB7C,
    gUnk_09A3CB9C,
    gUnk_09A3CBBC,
    gUnk_09A3CBDC,
    gUnk_09A3CBFC,
    gUnk_09A3CC1C,
    gUnk_09A3CBFC,
    gUnk_09A3CBDC,
    gUnk_09A3CBBC,
    gUnk_09A3CB9C,
    gUnk_09A3CB7C,
    gUnk_09A3CB5C,
    gUnk_09A3CB3C,
    gUnk_09A3CB1C,
    gUnk_09A3CAFC,
    gUnk_09A3CADC,
    gUnk_09A3CABC,
    gUnk_09A3CA9C,
    gUnk_09A3CA7C,
    gUnk_09A3CA5C,
};

#ifdef VERSION_EU
static const WorldselectTileSizes sWorldselectTitleTileSizes = { { 896, 960, 1024, 1024, 960 } };
#endif

static const WorldselectWorldDef sWorldselectWorldDefs[13] = {
#ifdef VERSION_EU
    { 1, WORLD_AGRABAH, 107, -1, gUnk_09A3CD1C, gUnk_099E7E7C, gUnk_099A8824, sWorldselectNameTileData, 8192, 0 },
#else
    { 1, WORLD_AGRABAH, 107, -1, gUnk_09A3CD1C, gUnk_099E7E7C, gUnk_099A8824, gUnk_099F6D3C },
#endif
#ifdef VERSION_EU
    { 2, WORLD_ATLANTICA, 101, -1, gUnk_09A3CD5C, gUnk_099E9E7C, gUnk_099A8880, sWorldselectNameTileData, 12288, 0 },
#else
    { 2, WORLD_ATLANTICA, 101, -1, gUnk_09A3CD5C, gUnk_099E9E7C, gUnk_099A8880, gUnk_099F7D3C },
#endif
#ifdef VERSION_EU
    { 4, WORLD_OLYMPUS_COLISEUM, 120, -1, gUnk_09A3CCFC, gUnk_099E6E7C, gUnk_099A87F8, sWorldselectNameTileData, 6144, 0 },
#else
    { 4, WORLD_OLYMPUS_COLISEUM, 120, -1, gUnk_09A3CCFC, gUnk_099E6E7C, gUnk_099A87F8, gUnk_099F653C },
#endif
#ifdef VERSION_EU
    { 8, WORLD_WONDERLAND, 94, -1, gUnk_09A3CC9C, gUnk_099E3E7C, gUnk_099A8758, sWorldselectNameTileData, 0, 0 },
#else
    { 8, WORLD_WONDERLAND, 94, -1, gUnk_09A3CC9C, gUnk_099E3E7C, gUnk_099A8758, gUnk_099F4D3C },
#endif
#ifdef VERSION_EU
    { 16, WORLD_MONSTRO, 74, -1, gUnk_09A3CD3C, gUnk_099E8E7C, gUnk_099A884C, sWorldselectNameTileData, 10240, 0 },
#else
    { 16, WORLD_MONSTRO, 74, -1, gUnk_09A3CD3C, gUnk_099E8E7C, gUnk_099A884C, gUnk_099F753C },
#endif
#ifdef VERSION_EU
    { 32, WORLD_HALLOWEEN_TOWN, 87, -1, gUnk_09A3CD7C, gUnk_099EAE7C, gUnk_099A88A0, sWorldselectNameTileData, 14336, 0 },
#else
    { 32, WORLD_HALLOWEEN_TOWN, 87, -1, gUnk_09A3CD7C, gUnk_099EAE7C, gUnk_099A88A0, gUnk_099F853C },
#endif
#ifdef VERSION_EU
    { 64, WORLD_NEVER_LAND, 115, -1, gUnk_09A3CD9C, gUnk_099EBE7C, gUnk_099A88D4, sWorldselectNameTileData, 16384, 0 },
#else
    { 64, WORLD_NEVER_LAND, 115, -1, gUnk_09A3CD9C, gUnk_099EBE7C, gUnk_099A88D4, gUnk_099F8D3C },
#endif
#ifdef VERSION_EU
    { 128, WORLD_HOLLOW_BASTION, 127, 149, gUnk_09A3CE1C, gUnk_099EEE7C, gUnk_099A8930, sWorldselectNameTileData, 20480, 0 },
#else
    { 128, WORLD_HOLLOW_BASTION, 129, 151, gUnk_09A3CE1C, gUnk_099EEE7C, gUnk_099A8930, gUnk_099F9D3C },
#endif
#ifdef VERSION_EU
    { 256, WORLD_DESTINY_ISLANDS, 53, 175, gUnk_09A3CCBC, gUnk_099E4E7C, gUnk_099A8780, sWorldselectNameTileData, 2048, 0 },
#else
    { 256, WORLD_DESTINY_ISLANDS, 53, 177, gUnk_09A3CCBC, gUnk_099E4E7C, gUnk_099A8780, gUnk_099F553C },
#endif
#ifdef VERSION_EU
    { 512, WORLD_TRAVERSE_TOWN, 1, -1, gUnk_09A3CCDC, gUnk_099E5E7C, gUnk_099A87C0, sWorldselectNameTileData, 4096, 0 },
#else
    { 512, WORLD_TRAVERSE_TOWN, 1, -1, gUnk_09A3CCDC, gUnk_099E5E7C, gUnk_099A87C0, gUnk_099F5D3C },
#endif
#ifdef VERSION_EU
    { 2048, WORLD_TWILIGHT_TOWN, 44, 184, gUnk_09A3CE3C, gUnk_099EFE7C, gUnk_099A895C, sWorldselectNameTileData, 22528, 0 },
#else
    { 2048, WORLD_TWILIGHT_TOWN, 44, 186, gUnk_09A3CE3C, gUnk_099EFE7C, gUnk_099A895C, gUnk_099FA53C },
#endif
#ifdef VERSION_EU
    { 4096, WORLD_CASTLE_OBLIVION, 61, 190, gUnk_09A3CE5C, gUnk_099F0E7C, gUnk_099A897C, sWorldselectNameTileData, 24576, 0 },
#else
    { 4096, WORLD_CASTLE_OBLIVION, 61, 192, gUnk_09A3CE5C, gUnk_099F0E7C, gUnk_099A897C, gUnk_099FAD3C },
#endif
#ifdef VERSION_EU
    { 1024, WORLD_100_ACRE_WOOD, 132, -1, gUnk_09A3CDBC, gUnk_099ECE7C, gUnk_099A8900, sWorldselectNameTileData, 18432, 0 },
#else
    { 1024, WORLD_100_ACRE_WOOD, 134, -1, gUnk_09A3CDBC, gUnk_099ECE7C, gUnk_099A8900, gUnk_099F953C },
#endif
};

Mode gModeWorldselect = {
    "mode_worldselect",
    (ModeInitFunc)mode_worldselect_0,
    mode_worldselect_1,
    mode_worldselect_2,
};

GaWork* gGaWork;
u32 gUnk_02034FEC;
s16 gWorldselectCursor;
u32 gUnk_02034FF4;
WorldselectSlot gWorldselectSlots[5];
s16 gWorldselectWorlds[14];
u32 gWorldselectRotation;
s16 gWorldselectSlotCount;
s16 gWorldselectWorldCount;
u32 gUnk_02035094;
void* gWorldselectCardTiles[2];
void* gWorldselectCardPalettes[2];
struct ObjTiles* gWorldselectTitleTiles;
struct ObjPalette* gWorldselectOverlayPalette;
struct ObjTiles* gWorldselectFrameTiles;
u8 gWorldselectBobPhase;
s16 gWorldselectNameMode;
s16 gWorldselectNameWidth;
s16 gWorldselectNameWorld;
void* gWorldselectNameBuffer;
s16 gWorldselectStep;
s16 gWorldselectTimer;
u32 gUnk_020350C4;
s32 gWorldselectFrameY[2];
s32 gWorldselectTitleX;
u32 gUnk_020350D4;
TaskPool gWorldselectTaskPool;
s16 gWorldselectTutorialStep;
u8 gWorldselectFirstVisit;
u8 gWorldselectBgAnimActive;
u8 gWorldselectCancelled;
s16 gWorldselectPaletteTimer;
u16 gWorldselectPaletteFrame;

u16 Bos5Atan(s32 a) {
    u16 i;

    if (a == 0x100) {
        return 0x20;
    }
    i = 0;

    if (a >= sBos5TanTable[0]) {
        do {
            i++;
            if (i > 0x3F) {
                break;
            }
        } while (a >= sBos5TanTable[i]);
    }
    return i;
}

s32 Bos5GetAngle(s32 x0, s32 y0, s32 x1, s32 y1) {
    s32 dx;
    s32 dy;
    s32 tmp;
    s32 q;
    u16 t;

    dx = x1 - x0;
    dy = y1 - y0;

    if (dx >= 0) {
        q = 0;

        if (dy < 0) {
            q = 3;
            tmp = dx;
            dx = -dy;
            dy = tmp;
        }
    } else if (dy >= 0) {
        q = 1;
        tmp = dx;
        dx = dy;
        dy = -tmp;
    } else {
        q = 2;
        dx = -dx;
        dy = -dy;
    }

    if (dy > dx) {
        if (dy == 0) {
            return 0;
        }
        dx <<= 8;
        t = 0x40 - Bos5Atan(dx / dy);
    } else {
        if (dx == 0) {
            return 0;
        }
        dy <<= 8;
        t = Bos5Atan(dy / dx);
    }
    return (t + (q << 6) + 0x40) & 0xFF;
}

void BosGaEntryUpdateFall(GaEntryWork* e) {
    e->vz += 0x4C;
    e->actor.z += e->vz;
    if (e->actor.z > 0) {
        if (e->vz > 0x500) {
            m4aSongNumStart(SONG_BTL_IRON_GIMICBREAK);
        }
        e->actor.z = 0;
        e->vz = -e->vz / 2;
    }

    if (e->vx > 0) {
        e->actor.x += e->vx;
        e->vx -= 0x11;
        if (e->vx < 0) {
            e->vx = 0;
        }
    } else if (e->vx < 0) {
        e->actor.x += e->vx;
        e->vx += 0x11;
        if (e->vx > 0) {
            e->vx = 0;
        }
    }

    if (e->vy > 0) {
        e->actor.y += e->vy / 2;
        e->vy -= 0x11;
        if (e->vy < 0) {
            e->vy = 0;
        }
    } else if (e->vy < 0) {
        e->actor.y += e->vy / 2;
        e->vy += 0x11;
        if (e->vy > 0) {
            e->vy = 0;
        }
    }
    ClampBattlePosition(&e->actor.x, &e->actor.y, -0x18, -0x0C);
}

void BosGaRequestState(GaWork* work, s32 state) {
    if (work->nextState != 11 && work->state != 11) {
        work->nextState = state;
        work->flags |= 1;
    }
}

s32 BosGaEntryOffsetX(GaWork* work, s16 i) {
    s32 v;

    v = sGaEntryDefs[i].offsetX;

    if (work->flipped != 0) {
        v = -v;
    }
    return v;
}

s32 BosGaEntryOffsetY(GaWork* work, s16 i) {
    return sGaEntryDefs[i].offsetY;
}

s32 BosGaEntryHomeX(GaWork* work, s16 i) {
    return BosGaEntryOffsetX(work, i) + gBtlWork->bossX;
}

s32 BosGaEntryHomeY(GaWork* work, s16 i) {
    return BosGaEntryOffsetY(work, i) + gBtlWork->bossY;
}

s32 BosGaEntryHomeZ(GaWork* work, s16 i) {
    return sGaEntryDefs[i].offsetZ + gBtlWork->bossZ;
}

void BosGaEntryResetHome(GaWork* work, s32 i) {
    GaEntryWork* e;
    s32 v;

    e = &work->entries[i];

    if (work->flipped == 0) {
        e->actor.flags |= BTLOBJ_FLAG_FACING_LEFT;
    } else {
        e->actor.flags &= ~BTLOBJ_FLAG_FACING_LEFT;
    }
    e->offsetX = BosGaEntryOffsetX(work, i);
    e->offsetY = BosGaEntryOffsetY(work, i);
    e->baseX = BosGaEntryHomeX(work, i);
    e->baseY = BosGaEntryHomeY(work, i);
    e->baseZ = BosGaEntryHomeZ(work, i);
    v = sGaEntryDefs[i].x2;

    if (work->flipped != 0) {
        v = -v;
    }
    e->x2 = v;
    e->y2 = sGaEntryDefs[i].y2;
}

void BosGaUpdateFacing(GaWork* work) {
    s32 flip;
    u32 i;

    flip = 0;

    if (gBtlWork->bossX <= gBtlWork->actor->x) {
        flip = 1;
    }

    if (work->flipped != flip) {
        work->flipped = flip;

        for (i = 0; i <= 5; i++) {
            BosGaEntryResetHome(work, i);
        }
    }
}

void BosGaEntryInit(GaWork* work, u32 i, s32 c) {
    GaEntryWork* e;
    void* p;

    e = &work->entries[i];
    e->index = i;
    e->bobZ = 0;
    e->bobAngle = GetRandom();
    e->mode = 0;
    e->vz = 0;
    e->rotation = 0;
    e->flags = 0;
    e->unk_15C = 0;
    e->vx = e->vy = 0;
    BosGaEntryResetHome(work, i);
    e->unk_130 = 0;
    e->unk_134 = 0;
    e->unk_138 = 0;
    e->orbitAngle = 0;

    if (c != 0) {
        if (i != 1) {
            e->baseX -= (GetRandom() & 0x1F) << 8;
            e->baseY -= (GetRandom() & 0x1F) << 8;
        }
        e->baseZ -= 0xA000;
    }
    InitEnemyBtlObj(&e->actor, &sBosGaEmyKind, e->baseX, e->baseY, e->baseZ);
    SetEnemyHpFromStats(&e->actor, sBosGaEmyKind.id, sGaEntryDefs[i].hpScale);
    e->actor.radiusY = 0x10;

    if (i == 0) {
        e->actor.flags |= 0x400;
    } else {
        e->actor.flags |= BTLOBJ_FLAG_NEVER_USES_CARDS;
    }
    e->actor.flags |= BTLOBJ_FLAG_FACING_LEFT;

    switch (i) {
    case 4:
    case 5:
        e->flags |= 1;
        break;
    }
    TaskPoolInit(&e->tasks, 1);
    TaskCreate(&e->tasks, &gTaskDescBtlShadow, &e->actor);
    p = sGaEntryDefs[i].gfxTable;
    e->tiles = AllocObjTiles(GetMaxSpriteTileBytes(p, sGaEntryDefs[i].spriteCount), sGaEntryDefs[i].owner);
    AnimInit(&e->anim, sGaEntryDefs[i].anims, p);
    AnimStart(&e->anim, 0, ANIM_FLAG_LOOP);
    e->gfx = AnimGetGfx(&e->anim);

    if (i == 0) {
        work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF9728, 4), gUnk_099999AC);
        AnimInit(&work->anim, gUnk_09EF9738, gUnk_09EF9728);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        work->gfx = AnimGetGfx(&work->anim);
    }
    ColliderInit(&e->actor.collider, 8, 8, 0x10);
}

void BosGaEntryRelease(GaEntryWork* e) {
    if (!(e->flags & 0x10)) {
        ColliderUnregister(&e->actor.collider);
        ReleaseObjTiles(e->tiles);
        ReleaseEnemyBtlObj(&e->actor);
        TaskPoolDestroy(&e->tasks);
        e->flags |= 0x10;
    }
}

void BosGaReleaseBody(void) {
    BosGaEntryRelease(&gGaWork->entries[1]);
    BosGaEntryRelease(&gGaWork->entries[0]);
}

void BosGaEntryDraw(GaWork* work, GaEntryWork* e) {
    ObjAffine* f;
    u16 g;
    void* pal;
    u16 sx;
    u16 sy;
    GaEntryWork* q;

    if (e->flags & 0x10) {
        return;
    }
    f = AllocObjAffineAngle(e->rotation, 1);
    q = e;
    g = GetBattleSpritePriorityFlags(e->actor.y);

    if (work->flipped == 1) {
        g |= 1;
    }

    if (StepHitFlash(&e->actor)) {
        pal = work->palette2;
    } else {
        pal = work->palette;
    }
    WorldToScreen(&sx, &sy, q->actor.x, q->actor.y, q->actor.z);
    DrawSprite((s16)(sx + e->x2), (s16)(sy + e->y2), e->gfx, e->tiles, pal, f, g,
               0xEFFC - ((q->actor.y >> 8) << 2));

    if (e->index == 0 && work->state != 7 && work->state != 8 && work->state != 9) {
        DrawSprite((s16)(sx + e->x2), (s16)(sy + e->y2), work->gfx, work->tiles, pal, f, g,
                   0xEFFC - ((q->actor.y >> 8) << 2));
    }
    TaskPoolDraw(&e->tasks);
}

u8 BosGaUpdateAssemble(GaWork* work) {
    u32 i = 0;
    GaEntryWork* e;

    if (work->flags & 1) {
        work->statePhase = 2;
    }
    switch (work->statePhase) {
    case 0:
        work->timer = 60;
        work->step = i;
        work->statePhase = 1;
        break;
    case 1:
        switch (work->step) {
        case 0:
            work->timer--;
            if (work->timer <= 0) {
                work->step = 1;
            }
            break;
        case 1:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                e->baseVx = 0;
                e->baseVy = 0;
                e->baseVz = 1;
                e->unk_15C = i * 8;
                if (i == 1) {
                    e->rotation = 0;
                } else {
                    e->rotation = GetRandom() % 100;
                }
            }
            gBtlWork->bossZ = -0x2000;
            work->timer = 5;
            work->step = 2;
            break;
        case 2:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                if (i != 1) {
                    if (e->unk_15C > 0) {
                        e->unk_15C--;
                    } else if (e->unk_15C == 0) {
                        e->baseX += e->baseVx;
                        e->baseY += e->baseVy;
                        e->baseZ += e->baseVz;
                        if (e->baseVz > 0) {
                            e->baseVz += 76;
                            if (e->baseZ > -0x800) {
                                s32 t = BosGaEntryHomeZ(work, i);
                                e->baseVz = (t - e->baseZ) / 15;
                                e->baseAccelZ = -((t - e->baseZ) * 2) / 900;
                                e->baseVx = (BosGaEntryHomeX(work, i) - e->baseX) / 30;
                                e->baseVy = (BosGaEntryHomeY(work, i) - e->baseY) / 30;
                                e->rotationFixed = e->rotation << 8;
                                e->landSteps = 30;
                                m4aSongNumStart(SONG_SND_388);
                            }
                        } else {
                            ApproachValue(&e->rotationFixed, 0x10000, e->landSteps);
                            e->rotation = e->rotationFixed >> 8;
                            e->baseVz += e->baseAccelZ;
                            e->landSteps--;
                            if ((s16)e->landSteps <= 0) {
                                BosGaEntryResetHome(work, i);
                                e->rotation = 0;
                                e->baseVz = 0;
                                e->unk_15C = -1;
                                work->timer--;
                                if (work->timer <= 0) {
                                    work->timer = 60;
                                    work->step = 3;
                                }
                            }
                        }
                    }
                }
            }
            break;
        case 3:
            ApproachValue(&gBtlWork->bossZ, 0, work->timer);
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                if (i != 1) {
                    ApproachValue(&e->baseZ, BosGaEntryHomeZ(work, i), work->timer);
                }
            }
            work->timer--;
            if (work->timer <= 0) {
                work->timer = 0;
                work->vz = 256;
                work->step = 4;
            }
            break;
        case 4:
            for (i = 0; i <= 5; i++) {
                switch (i) {
                case 0:
                case 2:
                case 3:
                    work->entries[i].baseZ += work->vz;
                    break;
                }
            }
            work->vz -= 10;
            if (work->vz > 0) {
                work->timer++;
            } else {
                work->timer--;
                if (work->timer <= 0) {
                    work->timer = 60;
                    work->step = 5;
                }
            }
            break;
        case 5:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                if (i == 1) {
                    ApproachValue(&e->baseZ, BosGaEntryHomeZ(work, i), work->timer);
                }
            }
            work->timer--;
            if (work->timer <= 0) {
                work->step = 6;
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
        work->flags &= 0xFFFE;
    }
    return 1;
}

u8 BosGaUpdateIdle(GaWork* work) {
    s32 d;
    s32 dx;
    s32 dy;

    if (work->flags & 1) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
        work->timer = 15;
        break;
    case 1:
        if (gBtlWork->phase == 0) {
            break;
        }
        work->timer--;
        if (work->timer > 0) {
            break;
        }
        dx = gBtlWork->actor->x - gBtlWork->bossX;
        dx = (dx * dx) >> 8;
        dy = gBtlWork->actor->y - gBtlWork->bossY;
        dy = (dy * dy) >> 8;
        d = (dx + dy) >> 8;
        if (d <= 0xE0F) {
            if (work->attackToggle == 0) {
                if (GetRandom() % 3 != 0) {
                    BosGaRequestState(work, 1);
                    RequestEnemyCardUse(&work->entries[0].actor);
                } else {
                    BosGaRequestState(work, 2);
                }
            } else {
                if (GetRandom() % 3 != 0) {
                    BosGaRequestState(work, 2);
                } else {
                    BosGaRequestState(work, 1);
                    RequestEnemyCardUse(&work->entries[0].actor);
                }
            }
        } else if (d <= 0x270F) {
            if (work->attackToggle == 0) {
                if (GetRandom() & 1) {
                    BosGaRequestState(work, 1);
                    RequestEnemyCardUse(&work->entries[0].actor);
                } else {
                    BosGaRequestState(work, 2);
                }
            } else {
                if (GetRandom() & 1) {
                    BosGaRequestState(work, 2);
                } else {
                    BosGaRequestState(work, 1);
                    RequestEnemyCardUse(&work->entries[0].actor);
                }
            }
        } else {
            if (work->attackToggle == 0) {
                if (GetRandom() % 3 != 0) {
                    BosGaRequestState(work, 2);
                } else {
                    BosGaRequestState(work, 1);
                    RequestEnemyCardUse(&work->entries[0].actor);
                }
            } else {
                if (GetRandom() % 3 != 0) {
                    BosGaRequestState(work, 1);
                    RequestEnemyCardUse(&work->entries[0].actor);
                } else {
                    BosGaRequestState(work, 2);
                }
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
        work->flags &= 0xFFFE;
    }
    return 1;
}

u8 BosGaUpdateWalk(GaWork* work) {
    u32 i;
    GaEntryWork* e;
    s32 x, y;

    if (work->flags & 1) {
        work->statePhase = 2;
    }
    for (i = 0; i <= 5; i++) {
        e = &work->entries[i];
        switch (work->statePhase) {
        case 0: {
            s32 d;
            if (e->index != 0) {
                break;
            }
            x = gBtlWork->actor->x;
            y = gBtlWork->actor->y;
            if (work->attackToggle == 0) {
                if (x > e->baseX) {
                    x -= 0x2800;
                    if (x < 0) {
                        x += 0x5000;
                    }
                } else {
                    x += 0x2800;
                    if (x > 0x10000) {
                        x -= 0x5000;
                    }
                }
            } else {
                if (x > e->baseX) {
                    x -= 0x6400;
                    if (x < 0) {
                        x += 0xC800;
                    }
                } else {
                    x += 0x6400;
                    if (x > 0x10000) {
                        x -= 0xC800;
                    }
                }
                y = ((GetRandom() & 80) + 296) << 8;
            }
            work->vx = ((x - e->baseX) * (x - e->baseX)) >> 8;
            work->vy = ((y - e->baseY) * (y - e->baseY)) >> 8;
            d = (work->vx + work->vy) >> 8;
            work->timer = 15;
            work->stepsLeft = d / 4900 + 2;
            work->vz = 768;
            work->vzDelta = work->vz * 2 / work->timer;
            work->angle = Bos5GetAngle(e->baseX, e->baseY, x, y);
            work->vx = (x - e->baseX) / ((work->stepsLeft - 1) * work->timer * 2);
            if (work->vx > 640) {
                work->vx = 640;
            } else if (work->vx < -640) {
                work->vx = -640;
            }
            work->vy = (y - e->baseY) / ((work->stepsLeft - 1) * work->timer * 2);
            if (work->vy > 640) {
                work->vy = 640;
            } else if (work->vy < -640) {
                work->vy = -640;
            }
            if (work->vy >= 0) {
                work->entries[4].flags |= 8;
                work->entries[5].flags &= 0xFFF7;
            } else {
                work->entries[4].flags &= 0xFFF7;
                work->entries[5].flags |= 8;
            }
            BosGaUpdateFacing(work);
            break;
        }
        case 1:
            switch (e->index) {
            case 4:
            case 5: {
                s32 velocity;
                if (!(e->flags & 8)) {
                    break;
                }
                velocity = work->vx;
                e->baseX += velocity;
                if (velocity < 0) {
                    if (e->baseX < 0) {
                        e->baseX = 0;
                    }
                } else if (velocity > 0) {
                    if (e->baseX > 0x10000) {
                        e->baseX = 0x10000;
                    }
                }
                velocity = work->vy;
                e->baseY += velocity;
                if (velocity < 0) {
                    if (e->baseY < 0x12800) {
                        e->baseY = 0x12800;
                    }
                } else if (velocity > 0) {
                    if (e->baseY > 0x17800) {
                        e->baseY = 0x17800;
                    }
                }
                e->baseZ -= work->vz;
                work->vz -= work->vzDelta;
                work->timer--;
                if (work->timer <= 0) {
                    if (!(e->flags & 4)) {
                        if (e->index == 4) {
                            m4aSongNumStart(SONG_BTL_IRON_FOOTL);
                        } else if (e->index == 5) {
                            m4aSongNumStart(SONG_BTL_IRON_FOOTR);
                        }
                    }
                    work->stepsLeft--;
                    e->baseZ = BosGaEntryHomeZ(work, i);
                    if (work->stepsLeft > 0) {
                        if (work->stepsLeft == 1) {
                            work->timer = 15;
                        } else {
                            work->timer = 30;
                        }
                        work->vz = 768;
                        work->vzDelta = work->vz * 2 / work->timer;
                        work->entries[5].flags ^= 8;
                        work->entries[4].flags ^= 8;
                    } else {
                        BosGaRequestState(work, 1);
                    }
                }
                break;
            }
            case 0: {
                s32 a, b, d;
                a = work->entries[4].baseX - work->entries[4].offsetX;
                b = work->entries[5].baseX - work->entries[5].offsetX;
                d = a - b >= 0 ? a - b : b - a;
                e->baseX = (a < b ? d + 1 : d) ? a : b;
                gBtlWork->bossX = e->baseX;
                a = work->entries[4].baseY - work->entries[4].offsetY;
                b = work->entries[5].baseY - work->entries[5].offsetY;
                d = a - b >= 0 ? a - b : b - a;
                e->baseY = (a < b ? d + 1 : d) ? a : b;
                gBtlWork->bossY = e->baseY;
                break;
            }
            default:
                BosGaEntryResetHome(work, i);
                break;
            }
            break;
        case 2:
            switch (e->index) {
            case 4:
            case 5:
                e->flags &= 0xFFF7;
                break;
            }
            BosGaEntryResetHome(work, i);
            break;
        }
    }
    if (work->statePhase == 0) {
        work->statePhase = 1;
    }
    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= 0xFFFE;
    }
    return 1;
}
u8 BosGaUpdateStomp(GaWork* work) {
    u32 i = 0;
    GaEntryWork* e;
    s32 velocity;

    if (work->flags & 1) {
        work->statePhase = 2;
    }
    switch (work->statePhase) {
    case 0:
            for (; i <= 5; i++) {
                e = &work->entries[i];
                switch (e->index) {
                case 4:
                    e->flags |= 8;
                    break;
                case 5:
                    e->flags &= 0xFFF7;
                    break;
                case 0:
                    work->timer = 10;
                    work->stepsLeft = 5;
                    work->vz = 1024;
                    work->vzDelta = work->vz * 2 / work->timer;
                    work->step = 0;
                    BosGaUpdateFacing(work);
                    break;
                }
            }
            break;
    case 1:
        switch (work->step) {
        case 0:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                switch (e->index) {
                case 4:
                case 5:
                    if (!(e->flags & 8)) {
                        break;
                    }
                    e->baseZ -= work->vz;
                    work->vz -= work->vzDelta;
                    work->timer--;
                    if (work->timer <= 0) {
                        if (!(e->flags & 4)) {
                            if (e->index == 4) {
                                m4aSongNumStart(SONG_BTL_IRON_FOOTL);
                            } else if (e->index == 5) {
                                m4aSongNumStart(SONG_BTL_IRON_FOOTR);
                            }
                        }
                        work->stepsLeft--;
                        e->baseZ = BosGaEntryHomeZ(work, i);
                        if (work->stepsLeft > 0) {
                            if (work->stepsLeft == 1) {
                                work->timer = 10;
                            } else {
                                work->timer = 20;
                            }
                            work->vz = 896;
                            work->vzDelta = work->vz * 2 / work->timer;
                            work->entries[5].flags ^= 8;
                            work->entries[4].flags ^= 8;
                        } else {
                            work->step = 1;
                        }
                    }
                    break;
                default:
                    BosGaEntryResetHome(work, i);
                    break;
                }
            }
            break;
        case 1:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                switch (e->index) {
                case 0:
                    work->step = 2;
                    break;
                case 4:
                case 5:
                    e->flags &= 0xFFF7;
                    break;
                }
                BosGaEntryResetHome(work, i);
            }
            break;
        case 2:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                switch (e->index) {
                case 4:
                    e->flags |= 8;
                    break;
                case 5:
                    e->flags &= 0xFFF7;
                    break;
                case 0:
                    work->timer = 10;
                    work->stepsLeft = 5;
                    work->vz = 1024;
                    work->vzDelta = work->vz * 2 / work->timer;
                    work->angle = Bos5GetAngle(e->baseX, e->baseY, gBtlWork->actor->x, gBtlWork->actor->y);
                    work->step = 3;
                    break;
                }
            }
            break;
        case 3:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                switch (e->index) {
                case 4:
                case 5:
                    if (!(e->flags & 8)) {
                        break;
                    }
                    velocity = gSineTable[work->angle] * 972 >> 8;
                    e->baseX += velocity;
                    if (velocity < 0) {
                        if (e->baseX < 0) {
                            e->baseX = 0;
                        }
                    } else if (velocity > 0) {
                        if (e->baseX > 0x10000) {
                            e->baseX = 0x10000;
                        }
                    }
                    velocity = -gSineTable[work->angle + 64] * 972 >> 8;
                    e->baseY += velocity;
                    if (velocity < 0) {
                        if (e->baseY < 0x12800) {
                            e->baseY = 0x12800;
                        }
                    } else if (velocity > 0) {
                        if (e->baseY > 0x17800) {
                            e->baseY = 0x17800;
                        }
                    }
                    e->baseZ -= work->vz;
                    work->vz -= work->vzDelta;
                    work->timer--;
                    if (work->timer <= 0) {
                        if (!(e->flags & 4)) {
                            if (ApplyAttackBox(226, e->actor.x, e->actor.y, e->actor.z, 16, 16, 16)) {
                                m4aSongNumStart(SONG_BTL_IRON_HIT00);
                            } else if (e->index == 4) {
                                m4aSongNumStart(SONG_BTL_IRON_FOOTL);
                            } else if (e->index == 5) {
                                m4aSongNumStart(SONG_BTL_IRON_FOOTR);
                            }
                        }
                        work->stepsLeft--;
                        e->baseZ = BosGaEntryHomeZ(work, i);
                        if (work->stepsLeft > 0) {
                            if (work->stepsLeft == 1) {
                                work->timer = 10;
                            } else {
                                work->timer = 20;
                            }
                            work->vz = 896;
                            work->vzDelta = work->vz * 2 / work->timer;
                            work->entries[5].flags ^= 8;
                            work->entries[4].flags ^= 8;
                        } else {
                            work->step = 4;
                        }
                    }
                    break;
                }
            }
            break;
        case 4:
            work->timer = 20;
            work->stepsLeft = 6;
            work->vz = 1024;
            work->vzDelta = work->vz * 2 / work->timer;
            work->step = 5;
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                switch (e->index) {
                case 4:
                    e->flags |= 8;
                    e->baseVx = (BosGaEntryHomeX(work, i) - e->baseX) / (work->stepsLeft * work->timer / 2);
                    e->baseVy = (BosGaEntryHomeY(work, i) - e->baseY) / (work->stepsLeft * work->timer / 2);
                    break;
                case 5:
                    e->flags &= 0xFFF7;
                    e->baseVx = (BosGaEntryHomeX(work, i) - e->baseX) / (work->stepsLeft * work->timer / 2);
                    e->baseVy = (BosGaEntryHomeY(work, i) - e->baseY) / (work->stepsLeft * work->timer / 2);
                    break;
                }
            }
            break;
        case 5:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                switch (e->index) {
                case 4:
                case 5:
                    if (!(e->flags & 8)) {
                        break;
                    }
                    e->baseX += e->baseVx;
                    if (e->baseVx < 0) {
                        if (e->baseX < 0) {
                            e->baseX = 0;
                        }
                    } else if (e->baseVx > 0) {
                        if (e->baseX > 0x10000) {
                            e->baseX = 0x10000;
                        }
                    }
                    e->baseY += e->baseVy;
                    if (e->baseVy < 0) {
                        if (e->baseY < 0x12800) {
                            e->baseY = 0x12800;
                        }
                    } else if (e->baseVy > 0) {
                        if (e->baseY > 0x17800) {
                            e->baseY = 0x17800;
                        }
                    }
                    e->baseZ -= work->vz;
                    work->vz -= work->vzDelta;
                    work->timer--;
                    if (work->timer <= 0) {
                        if (!(e->flags & 4)) {
                            if (e->index == 4) {
                                m4aSongNumStart(SONG_BTL_IRON_FOOTL);
                            } else if (e->index == 5) {
                                m4aSongNumStart(SONG_BTL_IRON_FOOTR);
                            }
                        }
                        work->stepsLeft--;
                        e->baseZ = BosGaEntryHomeZ(work, i);
                        if (work->stepsLeft > 0) {
                            work->timer = 20;
                            work->vz = 896;
                            work->vzDelta = work->vz * 2 / work->timer;
                            work->entries[5].flags ^= 8;
                            work->entries[4].flags ^= 8;
                        } else {
                            BosGaRequestState(work, 1);
                        }
                    }
                    break;
                }
            }
            break;
        }
        break;
    case 2:
        for (; i <= 5; i++) {
            e = &work->entries[i];
            switch (e->index) {
            case 0:
                ClearBtlObjActionFlags(&e->actor);
                break;
            case 4:
            case 5:
                e->flags &= 0xFFF7;
                break;
            }
            BosGaEntryResetHome(work, i);
        }
        break;
    }
    if (work->statePhase == 0) {
        work->statePhase = 1;
    }
    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= 0xFFFE;
    }
    return 1;
}

u8 BosGaUpdateThrust(GaWork* work) {
    GaEntryWork* e;
    u32 i;

    if (work->flags & 1) {
        work->statePhase = 2;
    }

    for (i = 0; i <= 5; i++) {
        e = &work->entries[i];

        switch (work->statePhase) {
        case 0:
            switch (e->index) {
            case 0:
                work->timer = 0;
                work->step = 0;
                break;
            case 2:
            case 3:
                e->flags |= 1;
                break;
            }
            break;
        case 1:
            switch (work->step) {
            case 0:
                if (e->index == 3) {
                    e->baseX = e->baseX + (work->flipped == 0 ? 0x80 : -0x80);
                    work->timer++;
                    if (work->timer > 30) {
                        work->timer = 0;
                        work->step = 1;
                    }
                } else {
                    BosGaEntryResetHome(work, i);
                }
                break;
            case 1:
                if (e->index == 3) {
                    e->baseX = e->baseX + (work->flipped == 0 ? -0x300 : 0x300);
                    e->baseY += 0x133;

                    if (!(e->flags & 4)) {
                        if (ApplyAttackBox(0xE3, e->actor.x, e->actor.y, e->actor.z, 0x10, 0x10, 0x20)) {
                            m4aSongNumStart(SONG_BTL_IRON_HIT00);
                        }
                    }
                    work->timer++;
                    if (work->timer > 15) {
                        work->timer = 0;
                        work->step = 2;
                    }
                } else {
                    BosGaEntryResetHome(work, i);
                }
                break;
            case 2:
                if (e->index == 2) {
                    e->baseX = e->baseX + (work->flipped == 0 ? 0x80 : -0x80);
                    work->timer++;
                    if (work->timer > 30) {
                        work->timer = 0;
                        work->step = 3;
                    }
                } else {
                    BosGaEntryResetHome(work, i);
                }
                break;
            case 3:
                if (e->index == 2) {
                    e->baseX = e->baseX + (work->flipped == 0 ? -0x300 : 0x300);
                    e->baseY -= 0x133;

                    if (!(e->flags & 4)) {
                        if (ApplyAttackBox(0xE3, e->actor.x, e->actor.y, e->actor.z, 0x10, 0x10, 0x20)) {
                            m4aSongNumStart(SONG_BTL_IRON_HIT00);
                        }
                    }
                    work->timer++;
                    if (work->timer > 15) {
                        BosGaRequestState(work, 1);
                    }
                } else {
                    BosGaEntryResetHome(work, i);
                }
                break;
            }
            break;
        case 2:
            switch (e->index) {
            case 0:
                ClearBtlObjActionFlags(&e->actor);
                break;
            case 2:
            case 3:
                e->flags &= 0xFFFE;
                break;
            }
            BosGaEntryResetHome(work, i);
            break;
        }
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= 0xFFFE;
    }
    return 1;
}

u8 BosGaUpdateOrbit(GaWork* work) {
    GaEntryWork* e;
    u32 i;
    s32 t;

    if (work->flags & 1) {
        work->statePhase = 2;
    }

    for (i = 0; i <= 5; i++) {
        e = &work->entries[i];

        switch (work->statePhase) {
        case 0:
            switch (e->index) {
            case 0:
                work->step = 0;
                work->timer = 0;
                work->orbitRadius = 0x1E00;
                break;
            case 2:
                e->orbitAngle = 0x80;
                AnimStart(&e->anim, 1, ANIM_FLAG_LOOP);
                break;
            case 3:
                e->orbitAngle = work->flipped == 0 ? 0xC0 : 0x40;
                AnimStart(&e->anim, 1, ANIM_FLAG_LOOP);
                break;
            }
            break;
        case 1:
            switch (work->step) {
            case 0:
                switch (e->index) {
                case 0:
                    work->timer++;
                    if (work->timer > 31) {
                        work->timer = 0;
                        work->step = 1;
                    }
                    break;
                case 2:
                    t = e->orbitAngle;
                    e->orbitAngle = work->flipped == 0 ? t - 1 : t + 1;
                    e->baseX = (gSineTable[e->orbitAngle] * work->orbitRadius >> 8) + work->entries[0].baseX;
                    e->baseY = (-gSineTable[e->orbitAngle + 0x40] * work->orbitRadius >> 8) + work->entries[0].baseY;
                    break;
                case 3:
                    t = e->orbitAngle;
                    e->orbitAngle = work->flipped == 0 ? t + 1 : t - 1;
                    e->baseX = (gSineTable[e->orbitAngle] * work->orbitRadius >> 8) + work->entries[0].baseX;
                    e->baseY = (-gSineTable[e->orbitAngle + 0x40] * work->orbitRadius >> 8) + work->entries[0].baseY;
                    break;
                default:
                    BosGaEntryResetHome(work, i);
                    break;
                }
                break;
            case 1:
                switch (e->index) {
                case 0:
                    work->orbitRadius += 0x59;
                    work->timer++;
                    if (work->timer > 0x7F) {
                        BosGaRequestState(work, 1);
                    }
                    break;
                case 2:
                case 3:
                    e->orbitAngle = e->orbitAngle + 4;

                    if (!(e->flags & 4)) {
                        if (ApplyAttackBox(0xE4, e->actor.x, e->actor.y, e->actor.z, 0x10, 0x10, 0x20)) {
                            m4aSongNumStart(SONG_BTL_IRON_HIT00);
                        }
                    }
                    e->baseX = (gSineTable[e->orbitAngle] * work->orbitRadius >> 8) + work->entries[0].baseX;
                    e->baseY = (-gSineTable[e->orbitAngle + 0x40] * work->orbitRadius >> 8) + work->entries[0].baseY;
                    break;
                default:
                    BosGaEntryResetHome(work, i);
                    break;
                }
                break;
            }
            break;
        case 2:
            switch (e->index) {
            case 0:
                ClearBtlObjActionFlags(&e->actor);
                break;
            case 2:
            case 3:
                AnimStart(&e->anim, 0, ANIM_FLAG_LOOP);
                break;
            }
            BosGaEntryResetHome(work, i);
            break;
        }
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= 0xFFFE;
    }
    return 1;
}

u8 BosGaUpdateJump(GaWork* work) {
    GaEntryWork* e;
    u32 i;
    s32 t;

    e = 0;

    if (work->flags & 1) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];
            e->flags |= 1;

            if (i == 0) {
                AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
                AnimStart(&e->anim, 2, ANIM_FLAG_LOOP);
            }
        }
        work->step = 0;
        break;
    case 1:
        switch (work->step) {
        case 0:
            gBtlWork->bossZ += 0x33;
            if (gBtlWork->bossZ > 0x1800) {
                work->step = 1;
            }

            for (i = 0; i <= 5; i++) {
                if (i <= 3) {
                    BosGaEntryResetHome(work, i);
                }
            }
            break;
        case 1:
            gBtlWork->bossZ = 0;
            work->vx = (gBtlWork->actor->x - gBtlWork->bossX) / 60;
            work->vy = (gBtlWork->actor->y - gBtlWork->bossY) / 60;
            work->vz = 0x600;
            work->step = 2;
            break;
        case 2:
            gBtlWork->bossX += work->vx;
            gBtlWork->bossY += work->vy;
            gBtlWork->bossZ -= work->vz;
            work->vz -= 0x33;

            if (gBtlWork->bossZ > 0) {
                BtlMapStartShake();
                m4aSongNumStart(SONG_BTL_IRON_RUMB);
                ApplyAttackBox(0xE5, gBtlWork->viewX, gBtlWork->viewY, 0, 0x140, 0xF0, 1);
                work->step = 3;
            }

            for (i = 0; i <= 5; i++) {
                BosGaEntryResetHome(work, i);
            }
            break;
        case 3:
            gBtlWork->bossZ = 0;
            work->vz = 0x100;
            work->step = 4;
            break;
        case 4:
            gBtlWork->bossZ += work->vz;
            t = work->vz - 7;
            work->vz = t;

            if (gBtlWork->bossZ <= 0 && t < 0) {
                BosGaRequestState(work, 1);
            }

            for (i = 0; i <= 5; i++) {
                if (i <= 3) {
                    BosGaEntryResetHome(work, i);
                }
            }
            break;
        }
        break;
    case 2:
        gBtlWork->bossZ = 0;

        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];

            switch (i) {
            case 0:
                AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
                AnimStart(&e->anim, 0, ANIM_FLAG_LOOP);
                ClearBtlObjActionFlags(&e->actor);
            default:
                e->flags &= 0xFFFE;
                break;
            case 4:
            case 5:
                break;
            }
            BosGaEntryResetHome(work, i);
        }
        break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= 0xFFFE;
    }
    return 1;
}

u8 BosGaUpdateBodyChase(GaWork* work) {
    GaEntryWork* e;
    u32 i;

    e = 0;

    if (work->flags & 1) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];
            e->flags |= 1;

            switch (i) {
            case 0:
                AnimStart(&e->anim, 1, ANIM_FLAG_LOOP);
                break;
            case 1:
                e->baseX = gBtlWork->bossX;
                e->baseY = gBtlWork->bossY + 0x100;
                break;
            }
        }
        work->step = 0;
        break;
    case 1:
        switch (work->step) {
        case 0:
            gBtlWork->bossZ += 0x66;
            if (gBtlWork->bossZ > 0x25FF) {
                work->step = 1;
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                if (i <= 1) {
                    e->baseZ = BosGaEntryHomeZ(work, i);
                }
            }
            break;
        case 1:
            work->vx = 0;
            work->vy = 0;
            work->timer = 0x12C;
            work->step = 2;
            BosGaUpdateFacing(work);
            break;
        case 2:
            work->angle = Bos5GetAngle(gBtlWork->bossX, gBtlWork->bossY, gBtlWork->actor->x, gBtlWork->actor->y);
            work->vx += gSineTable[work->angle] * 5 >> 8;
            if (work->vx > 0x200) {
                work->vx = 0x200;
            } else if (work->vx < -0x200) {
                work->vx = -0x200;
            }

            gBtlWork->bossX += work->vx;
            if (work->vx < 0) {
                if (gBtlWork->bossX < 0) {
                    work->vx = -work->vx;
                    gBtlWork->bossX = 0;
                    BosGaUpdateFacing(work);
                }
            } else if (work->vx > 0) {
                if (gBtlWork->bossX > 0x10000) {
                    work->vx = -work->vx;
                    gBtlWork->bossX = 0x10000;
                    BosGaUpdateFacing(work);
                }
            }

            work->vy += -gSineTable[work->angle + 0x40] * 5 >> 8;
            if (work->vy > 0x200) {
                work->vy = 0x200;
            } else if (work->vy < -0x200) {
                work->vy = -0x200;
            }

            gBtlWork->bossY += work->vy;
            if (work->vy < 0) {
                if (gBtlWork->bossY <= 0x127FF) {
                    work->vy = -work->vy;
                    gBtlWork->bossY = 0x12800;
                    BosGaUpdateFacing(work);
                }
            } else if (work->vy > 0) {
                if (gBtlWork->bossY > 0x17800) {
                    work->vy = -work->vy;
                    gBtlWork->bossY = 0x17800;
                    BosGaUpdateFacing(work);
                }
            }

            if (ApplyAttackBox(0xE6, work->entries[0].actor.x, work->entries[0].actor.y, work->entries[0].actor.z, 0x10, 0x10, 0x18)) {
                m4aSongNumStart(SONG_BTL_MON_HIT03);
                work->step = 3;
            }

            work->timer--;
            if (work->timer < 0) {
                work->step = 3;
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                switch (i) {
                case 0:
                    e->baseX = gBtlWork->bossX;
                    e->baseY = gBtlWork->bossY;
                    break;
                case 1:
                    e->baseX = gBtlWork->bossX;
                    e->baseY = gBtlWork->bossY + 0x100;
                    break;
                }
            }
            break;
        case 3:
            work->step = 4;
            break;
        case 4:
            gBtlWork->bossZ -= 0x33;
            if (gBtlWork->bossZ <= 0) {
                BosGaRequestState(work, 1);
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                if (i <= 1) {
                    e->baseZ = BosGaEntryHomeZ(work, i);
                }
            }
            break;
        }
        break;
    case 2:
        gBtlWork->bossZ = 0;

        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];

            switch (i) {
            case 0:
                AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
                AnimStart(&e->anim, 0, ANIM_FLAG_LOOP);
                ClearBtlObjActionFlags(&e->actor);
            default:
                e->flags &= 0xFFFE;
                break;
            case 4:
            case 5:
                break;
            }
            BosGaEntryResetHome(work, i);
        }
        break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= 0xFFFE;
    }
    return 1;
}

u8 BosGaUpdateBodyDash(GaWork* work) {
    GaEntryWork* e;
    u32 i;

    e = 0;

    if (work->flags & 1) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];
            e->flags |= 1;

            switch (i) {
            case 0:
                AnimStart(&e->anim, 1, ANIM_FLAG_LOOP);
                break;
            case 1:
                e->baseX = gBtlWork->bossX;
                e->baseY = gBtlWork->bossY + 0x100;
                break;
            }
        }
        work->step = 0;
        break;
    case 1:
        switch (work->step) {
        case 0:
            gBtlWork->bossZ += 0x66;
            if (gBtlWork->bossZ > 0x25FF) {
                work->step = 1;
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                if (i <= 1) {
                    e->baseZ = BosGaEntryHomeZ(work, i);
                }
            }
            break;
        case 1:
            work->angle = Bos5GetAngle(gBtlWork->bossX, gBtlWork->bossY, gBtlWork->actor->x, gBtlWork->actor->y);
            work->vx = gSineTable[work->angle] * 4;
            work->vy = -gSineTable[work->angle + 0x40] * 4;
            work->timer = 0x12C;
            work->step = 2;
            BosGaUpdateFacing(work);
            break;
        case 2:
            gBtlWork->bossX += work->vx;
            if (work->vx < 0) {
                if (gBtlWork->bossX < 0) {
                    work->vx = -work->vx;
                    gBtlWork->bossX = 0;
                    BosGaUpdateFacing(work);
                }
            } else if (work->vx > 0) {
                if (gBtlWork->bossX > 0x10000) {
                    work->vx = -work->vx;
                    gBtlWork->bossX = 0x10000;
                    BosGaUpdateFacing(work);
                }
            }

            gBtlWork->bossY += work->vy;
            if (work->vy < 0) {
                if (gBtlWork->bossY <= 0x127FF) {
                    work->vy = -work->vy;
                    gBtlWork->bossY = 0x12800;
                    BosGaUpdateFacing(work);
                }
            } else if (work->vy > 0) {
                if (gBtlWork->bossY > 0x17800) {
                    work->vy = -work->vy;
                    gBtlWork->bossY = 0x17800;
                    BosGaUpdateFacing(work);
                }
            }

            if (ApplyAttackBox(0xE6, work->entries[0].actor.x, work->entries[0].actor.y, work->entries[0].actor.z, 0x10, 0x10, 0x18)) {
                m4aSongNumStart(SONG_BTL_MON_HIT03);
                work->step = 3;
            }

            work->timer--;
            if (work->timer < 0) {
                work->step = 3;
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                switch (i) {
                case 0:
                    e->baseX = gBtlWork->bossX;
                    e->baseY = gBtlWork->bossY;
                    break;
                case 1:
                    e->baseX = gBtlWork->bossX;
                    e->baseY = gBtlWork->bossY + 0x100;
                    break;
                }
            }
            break;
        case 3:
            work->step = 4;
            break;
        case 4:
            gBtlWork->bossZ -= 0x33;
            if (gBtlWork->bossZ <= 0) {
                BosGaRequestState(work, 1);
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                if (i <= 1) {
                    e->baseZ = BosGaEntryHomeZ(work, i);
                }
            }
            break;
        }
        break;
    case 2:
        gBtlWork->bossZ = 0;

        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];

            switch (i) {
            case 0:
                AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
                AnimStart(&e->anim, 0, ANIM_FLAG_LOOP);
                ClearBtlObjActionFlags(&e->actor);
            default:
                e->flags &= 0xFFFE;
                break;
            case 4:
            case 5:
                break;
            }
            BosGaEntryResetHome(work, i);
        }
        break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= 0xFFFE;
    }
    return 1;
}

u8 BosGaUpdateBodyJump(GaWork* work) {
    GaEntryWork* e;
    u32 i;

    e = 0;

    if (work->flags & 1) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];
            e->flags |= 1;

            switch (i) {
            case 0:
                AnimStart(&e->anim, 1, ANIM_FLAG_LOOP);
                break;
            case 1:
                e->baseX = gBtlWork->bossX;
                e->baseY = gBtlWork->bossY + 0x100;
                break;
            }
        }
        work->step = 0;
        break;
    case 1:
        switch (work->step) {
        case 0:
            gBtlWork->bossZ += 0x66;
            if (gBtlWork->bossZ > 0x25FF) {
                gBtlWork->bossZ = 0x2600;
                work->timer = 3;
                work->step = 1;
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                if (i <= 1) {
                    e->baseZ = BosGaEntryHomeZ(work, i);
                }
            }
            break;
        case 1:
            work->vx = (gBtlWork->actor->x - gBtlWork->bossX) / 60;
            work->vy = (gBtlWork->actor->y - gBtlWork->bossY) / 60;
            work->vz = -0x400;
            work->vzDelta = 0x22;
            work->step = 2;
            BosGaUpdateFacing(work);
            break;
        case 2:
            gBtlWork->bossX += work->vx;
            if (work->vx < 0) {
                if (gBtlWork->bossX < 0) {
                    work->vx = -work->vx;
                    gBtlWork->bossX = 0;
                    BosGaUpdateFacing(work);
                }
            } else if (work->vx > 0) {
                if (gBtlWork->bossX > 0x10000) {
                    work->vx = -work->vx;
                    gBtlWork->bossX = 0x10000;
                    BosGaUpdateFacing(work);
                }
            }

            gBtlWork->bossY += work->vy;
            if (work->vy < 0) {
                if (gBtlWork->bossY <= 0x127FF) {
                    work->vy = -work->vy;
                    gBtlWork->bossY = 0x12800;
                    BosGaUpdateFacing(work);
                }
            } else if (work->vy > 0) {
                if (gBtlWork->bossY > 0x17800) {
                    work->vy = -work->vy;
                    gBtlWork->bossY = 0x17800;
                    BosGaUpdateFacing(work);
                }
            }

            gBtlWork->bossZ += work->vz;
            work->vz += work->vzDelta;
            if (gBtlWork->bossZ > 0x2600) {
                gBtlWork->bossZ = 0x2600;
                BtlMapStartShake();
                m4aSongNumStart(SONG_BTL_IRON_RUMB);
                ApplyAttackBox(0xE5, gBtlWork->viewX, gBtlWork->viewY, 0, 0x140, 0xF0, 1);
                work->timer--;
                if (work->timer > 0) {
                    work->step = 1;
                } else {
                    work->step = 3;
                }
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                switch (i) {
                case 0:
                    BosGaEntryResetHome(work, 0);
                    break;
                case 1:
                    e->baseX = gBtlWork->bossX;
                    e->baseY = gBtlWork->bossY + 0x100;
                    e->baseZ = BosGaEntryHomeZ(work, 1);
                    break;
                }
            }
            break;
        case 3:
            work->step = 4;
            break;
        case 4:
            gBtlWork->bossZ -= 0x33;
            if (gBtlWork->bossZ <= 0) {
                BosGaRequestState(work, 1);
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                if (i <= 1) {
                    e->baseZ = BosGaEntryHomeZ(work, i);
                }
            }
            break;
        }
        break;
    case 2:
        gBtlWork->bossZ = 0;

        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];

            switch (i) {
            case 0:
                AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
                AnimStart(&e->anim, 0, ANIM_FLAG_LOOP);
                ClearBtlObjActionFlags(&e->actor);
            default:
                e->flags &= 0xFFFE;
                break;
            case 4:
            case 5:
                break;
            }
            BosGaEntryResetHome(work, i);
        }
        break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= 0xFFFE;
    }
    return 1;
}

u8 BosGaUpdateGimmick(GaWork* work) {
    GaEntryWork* e;
    u32 i;
    s32 t;

    e = 0;

    if (work->flags & 1) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
        work->timer = 0x12C;

        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];
            if (!(e->flags & 4)) {
                e->vz = -gSineTable[((GetRandom() % 0x20) & 0xFF) + 0x40] * -3;
                e->vx = gSineTable[(GetRandom() % 0x100) & 0xFF] * 0x233 >> 8;
                e->vy = -gSineTable[((GetRandom() % 0x100) & 0xFF) + 0x40] * 0x233 >> 8;
                e->mode = 1;

                if (i == 0) {
                    AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
                    AnimStart(&e->anim, 2, ANIM_FLAG_LOOP);
                }
            }
        }
        m4aSongNumStart(SONG_BTL_IRON_GIMICBREAK);
        BtlMapStartShake();
        break;
    case 1:
        work->timer--;
        if (work->timer > 0) {
            break;
        }
        BosGaRequestState(work, 1);
        break;
    case 2:
        gBtlWork->bossZ = 0;

        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];
            t = e->flags & 4;
            if (t == 0) {
                if (i == 0) {
                    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
                    AnimStart(&e->anim, 0, ANIM_FLAG_LOOP);
                }
                e->mode = t;
                BosGaEntryResetHome(work, i);
            }
        }
        break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= 0xFFFE;
    }
    return 1;
}

u8 BosGaUpdateDefeat(GaWork* work) {
    CharaObjParam param;
    u32 i;
    GaEntryWork* e;
    u8 result = 1;

    if (work->flags & 1) {
        work->statePhase = 2;
    }
    switch (work->statePhase) {
    case 0:
        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];
            e->flags |= 1;
            switch (i) {
            case 0:
                AnimStart(&work->anim, 1, 0);
                AnimStart(&e->anim, 2, 0);
                e->baseVz = 0;
                break;
            case 1:
                e->baseVz = 0;
                break;
            }
        }
        work->timer = 3;
        work->step = 0;
        break;
    case 1:
        switch (work->step) {
        case 0:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                switch (i) {
                case 0:
                    e->baseZ += e->baseVz;
                    e->baseVz += 128;
                    if (e->baseZ > -0x1800) {
                        m4aSongNumStart(SONG_SND_389);
                        e->baseZ = -0x1800;
                        e->baseVz = -(e->baseVz / 2);
                        work->entries[1].baseVz = -(work->entries[1].baseVz / 2);
                        work->timer--;
                        if (work->timer <= 0) {
                            work->step = 1;
                        }
                    }
                    break;
                case 1:
                    e->baseZ += e->baseVz;
                    e->baseVz += 128;
                    break;
                }
            }
            break;
        case 1:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                if (i == 1) {
                    work->timer = 20;
                    e->baseVx = (work->flipped == 0 ? -0xA00 : 0xA00) / work->timer;
                    e->baseVy = 0x600 / work->timer;
                    work->step = 2;
                }
            }
            break;
        case 2:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                if (i == 1) {
                    e->baseX += e->baseVx;
                    e->baseY += e->baseVy;
                    work->timer--;
                    if (work->timer <= 0) {
                        work->step = 3;
                    }
                }
            }
            break;
        case 3:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                if (i == 1) {
                    e->baseVz = 0;
                    work->timer = 3;
                    work->step = 4;
                }
            }
            break;
        case 4:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                if (i == 1) {
                    e->baseZ += e->baseVz;
                    e->baseVz += 128;
                    if (e->baseZ > -0x800) {
                        m4aSongNumStart(SONG_BTL_IRON_FOOTR);
                        e->baseZ = -0x800;
                        e->baseVz = -(e->baseVz / 2);
                        work->timer--;
                        if (work->timer <= 0) {
                            work->step = 5;
                        }
                    }
                }
            }
            break;
        case 5:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                switch (i) {
                case 0:
                    param.tilesAddr = 0x06010000 + (e->tiles->index << 5);
                    param.tileCount = e->tiles->count;
                    param.tilesAddr2 = 0x06010000 + (work->tiles->index << 5);
                    param.tileCount2 = work->tiles->count;
                    param.x = e->baseX + (work->flipped == 0 ? -0x700 : 0x700);
                    param.y = e->baseY;
                    param.z = e->baseZ + 0x1000;
                    param.prizeObj = &e->actor;
                    break;
                case 1:
                    param.tilesAddr3 = 0x06010000 + (e->tiles->index << 5);
                    param.tileCount3 = e->tiles->count;
                    break;
                }
            }
            param.paletteAddr = 0x05000200 + (work->palette->index << 5);
            param.paletteSize = work->palette->count << 5;
            param.tilesAddr4 = 0;
            param.tileCount4 = 0;
            param.paletteAddr2 = 0;
            param.paletteSize2 = 0;
            param.callback = BosGaReleaseBody;
            CharaObjInitDefeat(&param);
            work->step = 6;
            break;
        case 6:
            if (CharaObjUpdateDefeat() == 0) {
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
        work->flags &= 0xFFFE;
    }
    return result;
}

void BosGaEntryUpdate(GaWork* work, GaEntryWork* e) {
    s32 d1;
    s32 d2;
    s32 flag;
    s32 v;
    u16 t;

    if (e->flags & 0x10) {
        return;
    }

    switch (UpdateBtlObjReaction(&e->actor)) {
    case 5:
        work->cardActionSeen = 1;

        if (work->state == 10 || work->nextState == 10) {
            ClearBtlObjActionFlags(&e->actor);
        } else {
            d1 = gBtlWork->actor->x - e->baseX;
            d1 = (d1 * d1) >> 8;
            d2 = gBtlWork->actor->y - e->baseY;
            d2 = (d2 * d2) >> 8;

            if (work->entries[2].flags & work->entries[3].flags & work->entries[4].flags & work->entries[5].flags & 4) {
                switch (GetRandom() % 3) {
                case 0:
                    BosGaRequestState(work, 7);
                    break;
                case 1:
                    BosGaRequestState(work, 8);
                    break;
                case 2:
                    BosGaRequestState(work, 9);
                    break;
                }
            } else if (d1 + d2 <= 0xE0FFF) {
                if (GetRandom() % 100 < 70) {
                    if ((work->entries[2].flags & work->entries[3].flags & 4) == 0) {
                        flag = 0;

                        if (gBtlWork->bossX <= gBtlWork->actor->x) {
                            flag = 1;
                        }

                        if (work->flipped == flag) {
                            BosGaRequestState(work, 4);
                        } else {
                            BosGaRequestState(work, 5);
                        }
                    } else {
                        if (work->attackToggle == 0) {
                            BosGaRequestState(work, 6);
                        } else {
                            BosGaRequestState(work, 3);
                        }
                    }
                } else {
                    if ((work->entries[4].flags & work->entries[5].flags & 4) == 0) {
                        if (work->attackToggle == 0) {
                            BosGaRequestState(work, 6);
                        } else {
                            BosGaRequestState(work, 3);
                        }
                    } else {
                        flag = 0;

                        if (gBtlWork->bossX <= gBtlWork->actor->x) {
                            flag = 1;
                        }

                        if (work->flipped == flag) {
                            BosGaRequestState(work, 4);
                        } else {
                            BosGaRequestState(work, 5);
                        }
                    }
                }
            } else if (d1 + d2 <= 0x270FFF) {
                if (GetRandom() % 100 < 50) {
                    if ((work->entries[2].flags & work->entries[3].flags & 4) == 0) {
                        flag = 0;

                        if (gBtlWork->bossX <= gBtlWork->actor->x) {
                            flag = 1;
                        }

                        if (work->flipped == flag) {
                            BosGaRequestState(work, 4);
                        } else {
                            BosGaRequestState(work, 5);
                        }
                    } else {
                        if (work->attackToggle == 0) {
                            BosGaRequestState(work, 6);
                        } else {
                            BosGaRequestState(work, 3);
                        }
                    }
                } else {
                    if ((work->entries[4].flags & work->entries[5].flags & 4) == 0) {
                        if (work->attackToggle == 0) {
                            BosGaRequestState(work, 6);
                        } else {
                            BosGaRequestState(work, 3);
                        }
                    } else {
                        flag = 0;

                        if (gBtlWork->bossX <= gBtlWork->actor->x) {
                            flag = 1;
                        }

                        if (work->flipped == flag) {
                            BosGaRequestState(work, 4);
                        } else {
                            BosGaRequestState(work, 5);
                        }
                    }
                }
            } else {
                if (GetRandom() % 100 < 30) {
                    if ((work->entries[2].flags & work->entries[3].flags & 4) == 0) {
                        flag = 0;

                        if (gBtlWork->bossX <= gBtlWork->actor->x) {
                            flag = 1;
                        }

                        if (work->flipped == flag) {
                            BosGaRequestState(work, 4);
                        } else {
                            BosGaRequestState(work, 5);
                        }
                    } else {
                        if (work->attackToggle == 0) {
                            BosGaRequestState(work, 6);
                        } else {
                            BosGaRequestState(work, 3);
                        }
                    }
                } else {
                    if ((work->entries[4].flags & work->entries[5].flags & 4) == 0) {
                        if (work->attackToggle == 0) {
                            BosGaRequestState(work, 6);
                        } else {
                            BosGaRequestState(work, 3);
                        }
                    } else {
                        flag = 0;

                        if (gBtlWork->bossX <= gBtlWork->actor->x) {
                            flag = 1;
                        }

                        if (work->flipped == flag) {
                            BosGaRequestState(work, 4);
                        } else {
                            BosGaRequestState(work, 5);
                        }
                    }
                }
            }
        }

        if (GetRandom() % 3 != 0) {
            if (work->attackToggle == 0) {
                work->attackToggle = 1;
            } else {
                work->attackToggle = 0;
            }
        }
        break;
    case 1:
    case 6:
    case 7:
        e->flags |= 2;
        e->flashTimer = 0;

        if (e->index == 0) {
            work->entries[1].flags |= 2;
            work->entries[1].flashTimer = 0;
        }
        break;
    case 3:
    case 8:
        SetBtlObjUnhittable(&e->actor, 1);
        e->flags |= 4;

        if (e->index == 0) {
            BeginBossDefeat(&e->actor);
            e->mode = 0;
            e->unk_15C = 0;
            work->entries[1].mode = 0;
            work->entries[1].unk_15C = 0;
            BosGaRequestState(work, 11);
        } else {
            e->mode = 3;
            e->unk_15C = 0;

            if (work->state != 10 && work->nextState != 10) {
                if (work->cardActionSeen != 0) {
                    ClearBtlObjActionFlags(&work->entries[0].actor);
                }
                BosGaRequestState(work, 1);
            }
        }
        break;
    case 4:
        if (work->state != 10 && work->nextState != 10) {
            if (GetRandom() % 100 < 30) {
                _0801C1F8(0, e->baseX, e->baseY, e->baseZ);
            }
            BosGaRequestState(work, 1);
        }
        ClearBtlObjActionFlags(&e->actor);
        break;
    }

    switch ((u32)e->mode) {
    case 0:
        v = (e->baseX - e->actor.x) >> 1;
        if (v > 0x600) {
            v = 0x600;
        } else if (v < -0x600) {
            v = -0x600;
        }
        e->actor.x += v;
        v = (e->baseY - e->actor.y) >> 1;
        if (v > 0x600) {
            v = 0x600;
        } else if (v < -0x600) {
            v = -0x600;
        }
        e->actor.y += v;
        v = ((e->baseZ + e->bobZ) - e->actor.z) >> 1;
        if (v > 0x600) {
            v = 0x600;
        } else if (v < -0x600) {
            v = -0x600;
        }
        e->actor.z += v;
        t = e->rotation;
        ApproachAngle(&t, 0, 3);
        e->rotation = t;

        if (e->flags & 1) {
            break;
        }
        e->bobZ = gSineTable[e->bobAngle] << 2;
        e->bobAngle += 4;
        break;
    case 1:
        BosGaEntryUpdateFall(e);
        break;
    case 3:
        if (e->unk_15C == 0) {
            e->flags |= 2;
            e->flashTimer = 0;

            if (!BgFxIsActive()) {
                BgFxStartEnemyDeath(e->actor.x, e->actor.y + e->actor.z, 0, 0x100);
                e->unk_15C++;
            }
        } else if (e->unk_15C > 0) {
            if (work->entries[2].flags & work->entries[3].flags & work->entries[4].flags & work->entries[5].flags & 4) {
                SetBtlObjUnhittable(&work->entries[0].actor, 0);
            }
            ClearBtlObjActionFlags(&e->actor);
            BosGaEntryRelease(e);
            return;
        }
        BosGaEntryUpdateFall(e);
        break;
    }

    if (e->flags & 2) {
        e->flashTimer++;
        if (e->flashTimer > 30) {
            ClearBtlObjActionFlags(&e->actor);
            e->flags &= 0xFFFD;
            e->flashTimer = 0;
        }
    }
    e->gfx = AnimUpdate(&e->anim);

    if (e->index == 0) {
        work->gfx = AnimUpdate(&work->anim);
    }

    if (e->actor.collider.colliding != 0) {
        e->actor.x += e->actor.collider.pushX;
        e->actor.y += e->actor.collider.pushY;
    }
    ColliderSetPosition(&e->actor.collider, e->actor.x, e->actor.y, e->actor.z + e->bobZ);
    TaskPoolUpdate(&e->tasks);
}

void task_bos_ga_0(GaWork* work, s32 arg) {
    u32 i;
    GaEntryWork* p;

    gGaWork = work;

    if (arg == 0) {
        work->state = 1;
    } else {
        work->state = 0;
    }

    work->nextState = work->state;
    work->flags = 0;
    work->statePhase = 0;
    work->timer = 0;
    work->stepsLeft = 0;
    work->unk_014 = 0;
    work->flipped = 0;
    work->angle = 0;
    work->attackToggle = 0;
    work->cardTimer = 60;
    TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosMap, &sBosMapConfig);
    gBtlWork->bossX = 0xE200;
    gBtlWork->bossY = 0x15E00;
    gBtlWork->bossZ = 0;
    SetBattleActorPosition(0x8200, 0x15E00, 0);
    p = work->entries;

    for (i = 0; i <= 5; i++) {
        BosGaEntryInit(work, i, arg);
    }

    SetBtlObjUnhittable(&p->actor, 1);
    SetBtlObjUnhittable(&work->entries[1].actor, 1);
    work->palette = LoadObjPalette(gBoss01objPalette, 32);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    SetBtlPaletteFadeExcluded(work->palette->index + 16, 1);
    SetBtlPaletteFadeExcluded(work->palette2->index + 16, 1);
    RequestBossCardValue(GetRandom() % 4 + 1);
}
u8 task_bos_ga_1(GaWork* work) {
    u8 result;
    GaEntryWork* p;
    AnimState* anim;
    u32 i;

    result = 1;
    work->cardTimer--;

    if (work->cardTimer <= 0) {
        RequestBossCardValue(GetRandom() % 7 + 1);
        work->cardTimer = 60;
    }

    work->cardActionSeen = 0;
    i = 0;
    p = work->entries;

    do {
        BosGaEntryUpdate(work, p);
        p++;
        i++;
    } while (i <= 5);

    switch (work->state) {
    case 0:
        result = BosGaUpdateAssemble(work);
        break;
    case 1:
        result = BosGaUpdateIdle(work);
        break;
    case 2:
        result = BosGaUpdateWalk(work);
        break;
    case 3:
        result = BosGaUpdateStomp(work);
        break;
    case 4:
        result = BosGaUpdateThrust(work);
        break;
    case 5:
        result = BosGaUpdateOrbit(work);
        break;
    case 6:
        result = BosGaUpdateJump(work);
        break;
    case 7:
        result = BosGaUpdateBodyChase(work);
        break;
    case 8:
        result = BosGaUpdateBodyDash(work);
        break;
    case 9:
        result = BosGaUpdateBodyJump(work);
        break;
    case 10:
        result = BosGaUpdateGimmick(work);
        break;
    case 11:
        result = BosGaUpdateDefeat(work);
        break;
    }

    if (ConsumeGimmickFlag(0)) {
        BosGaRequestState(work, 10);
    }

    anim = &work->entries[1].anim;

    if (AnimIsFinished(anim) && GetRandom() % 100 == 0 && work->state != 11) {
        AnimStart(anim, 1, 0);
    }

    return result;
}

void task_bos_ga_2(GaWork* work) {
    GaEntryWork* p;
    u32 i;

    i = 0;
    p = work->entries;

    do {
        BosGaEntryDraw(work, p);
        p++;
        i++;
    } while (i <= 5);
}

void task_bos_ga_3(GaWork* work) {
    GaEntryWork* p;
    u32 i;

    i = 0;
    p = work->entries;

    do {
        BosGaEntryRelease(p);
        p++;
        i++;
    } while (i <= 5);

    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
}

void BosMdRequestState(MdWork* work, s32 state) {
    u16 t;

    work->nextState = state;
    t = work->flags | 1;
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

    if (work->bgVisible == 0) {
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
    if (work->flags & 1) {
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
        if (BosMdAnimIsLastFrame(work) != 0 && gBtlWork->actor->x > 0x8000) {
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
        work->flags &= 0xFFFE;
    }

    return 1;
}
u8 BosMdUpdateBite(MdWork* work) {
    s32 d;
    u16 r;

    if (work->flags & 1) {
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
            switch ((s16)work->anim.frames[work->anim.frame].gfxIndex) {
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

            if (BosMdAnimIsLastFrame(work) != 0) {
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
        work->flags &= 0xFFFE;
    }

    return 1;
}
u8 BosMdUpdateQuake(MdWork* work) {
    s32 v;

    if (work->flags & 1) {
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
                v = (s16)work->anim.frames[work->anim.frame].gfxIndex;

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
                v = (s16)work->anim.frames[work->anim.frame].gfxIndex;

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

            if (BosMdAnimIsLastFrame(work) != 0) {
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
        work->flags &= 0xFFFE;
    }

    return 1;
}
u8 BosMdUpdateFireBreath(MdWork* work) {
    MdFireArg a;

    if (work->flags & 1) {
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
                    if (BosMdAnimIsLastFrame(work) != 0) {
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

                    if (BgFxIsActive() == 0) {
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
                    if (BosMdAnimIsLastFrame(work) != 0) {
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
        work->flags &= 0xFFFE;
    }

    return 1;
}
u8 BosMdUpdateDefeat(MdWork* work) {
    u8 result;
    PrizeCardArg arg;

    result = 1;

    if (work->flags & 1) {
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
                if (FadeIsActive() == 0) {
                    BgFxStartBossDeath(work->sub[0].x,
                                  work->sub[0].y + work->sub[0].z);
                    FadeToAmount(0, gBtlWork->fadeAmount, 8);
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
                if (work->bgVisible != 0 && FadeGetAmount() == 31) {
                    DisableBg(1);
                    work->bgVisible = 0;
                }

                if (BgFxIsActive() == 0) {
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
        work->flags &= 0xFFFE;
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
        case 5:
            BosMdChooseAttack(work);
            break;
        case 1:
        case 6:
        case 7:
            work->hurtTimer = 30;
            work->hurtState[i] = 2;
            break;
        case 3:
        case 8:
            SetBtlObjUnhittable(e, 1);
            BosMdRequestState(work, 4);
            break;
        case 4:
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
    work->unk_018 = 0;
    work->hurtTimer = 0;
    work->signals = 0;
    work->bgVisible = 1;

    for (i = 0; i < 1; i++) {
        work->hurtState[i] = 0;
    }

    for (i = 0; i < 2; i++) {
        work->gfx[i].tiles = 0;
        work->gfx[i].src = 0;
        work->gfx[i].sprite = 0;
        work->gfx[i].x = 0;
        work->gfx[i].y = 0;
    }

    work->gfx[0].tiles = AllocSpriteFrameTiles(2432);
    work->gfx[1].tiles = LoadObjTiles(gUnk_099D42FC, 0x12A0);
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
    LoadPalette(gUnk_09A3C97C, (void*)0x05000000, 32);
    SetBtlPaletteFadeExcluded(0, 1);
    work->bgPalette = gUnk_09A3C97C;
    work->palette = LoadObjPalette(gUnk_09A3C97C, 32);
    SetBtlPaletteFadeExcluded(work->palette->index + 16, 1);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
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

    if (ConsumeGimmickFlag(0) != 0) {
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
            + sMdFrameDefs[(s16)work->anim.frames[work->anim.frame].gfxIndex]
                  .pos[i].x * 256;
        work->sub[i].y = gBtlWork->bossY
            + sMdFrameDefs[(s16)work->anim.frames[work->anim.frame].gfxIndex]
                  .pos[i].y * 256;
        work->sub[i].z = gBtlWork->bossZ
            + sMdFrameDefs[(s16)work->anim.frames[work->anim.frame].gfxIndex]
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

    if (work->bgVisible == 0) {
        return;
    }

    if (StepHitFlash(&work->sub[0]) != 0) {
        if (work->bgPalette != gUnk_08F69BC4) {
            LoadPalette(gUnk_08F69BC4, (void*)0x05000000, 32);
            work->bgPalette = gUnk_08F69BC4;
        }

        pal = work->palette2;
    } else {
        if (work->bgPalette != gUnk_09A3C97C) {
            LoadPalette(gUnk_09A3C97C, (void*)0x05000000, 32);
            work->bgPalette = gUnk_09A3C97C;
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
        DrawSprite(x, y, work->gfx[i].sprite, work->gfx[i].tiles, pal, 0, frame,
                   (u16)(-4100 - (wy >> 6)));
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

void task_bos_md_map_0(MdMapWork* work, MdMapData* p) {
    LoadBgTiles(0, p->tiles, p->tilesSize);
    LoadBgPalette(0, p->palette, p->paletteSize);
    SetBgMapBlocks(0, &p->map, 2, 2);
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
    case 1:
    case 6:
    case 7:
        work->flashTimer = 30;
        work->state = 3;
        break;
    case 3:
    case 8:
        if (GetRandom() % 100 <= 49) {
            if ((gBtlWork->flags & 0x100000) == 0) {
                _0801C1F8(0, e->x, e->y, e->z);
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
                                a = Bos5GetAngle(work->x, work->y,
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
            } else if (ColliderIsTouchingType(&work->sub.collider, 1) != 0) {
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
    work->palette = LoadObjPalette(gUnk_09A3C99C, 32);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    work->tiles = LoadObjTiles(gUnk_099E367C, 0x800);
    AnimInit(&work->anim, gUnk_09EF9BC0, gUnk_09EF9BB0);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    a.pool = 0;
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
        sprite = 0;
    }

    DrawSprite(x, y, AnimUpdate(&work->anim), work->tiles, gfx,
                  sprite, frame, (u16)(-4100 - (work->y >> 8) * 4));
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
    work->palette = LoadObjPalette(gUnk_09A3C9BC, 32);
    work->tiles = LoadObjTiles(gUnk_09999ED0, 0x480);
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
        DrawSprite(x, y + 24, gUnk_09999E0C, work->tiles, work->palette, 0,
                      frame, (u16)(-4100 - (work->y >> 8) * 4));
        DrawSprite(x, y, gUnk_09999E1C, work->tiles, work->palette, 0, frame,
                      (u16)(-4100 - (work->y >> 8) * 4));
        DrawSprite(x + 8, y - 16, gUnk_09999E0C, work->tiles, work->palette, 0,
                      frame, (u16)(-4100 - (work->y >> 8) * 4));
    }

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    frame = GetBattleSpritePriorityFlags(work->y);

    if (work->level > 0) {
        DrawSprite(x, y, gUnk_09EF9740[work->level + 1], work->tiles,
                      work->palette, 0, frame,
                      (u16)(-4100 - (work->y >> 8) * 4));
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
    work->palette = LoadObjPalette(gUnk_09A3C9BC, 32);
    work->tiles = LoadObjTiles(gUnk_09999ED0, 0x480);
    work->gfx = gUnk_09EF9740[GetRandom() % 2];
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
                  0, frame, (u16)(-4100 - (work->y >> 8) * 4));
}

void task_bos_md_hahen_3(MdHahenWork* work) {
    ReleaseObjPalette(work->palette);
    ReleaseObjTiles(work->tiles);
}

void WorldselectLoadSlotPalette(s16 model, s16 slot) {
    void* src;
    s32 size;

    if (sWorldselectWorldDefs[model].world == WORLD_100_ACRE_WOOD && func_080D2DD8()) {
        src = gUnk_09A3CDDC;
        size = 0x40;
    } else {
        src = sWorldselectWorldDefs[model].palette;
        size = 0x20;
    }

    gWorldselectSlots[slot].palette = LoadObjPalette(src, size);
}

void WorldselectLoadSlotTiles(s16 model, s16 slot) {
    void* src;

    if (sWorldselectWorldDefs[model].world == WORLD_100_ACRE_WOOD && func_080D2DD8()) {
        src = gUnk_099EDE7C;
    } else {
        src = sWorldselectWorldDefs[model].tiles;
    }

    gWorldselectSlots[slot].tiles = LoadObjTiles(src, 0x1000);
}

s16 WorldselectSetSlotGfx(s16 model, s16 slot) {
    if (sWorldselectWorldDefs[model].world == WORLD_100_ACRE_WOOD && func_080D2DD8()) {
        gWorldselectSlots[slot].gfx = gUnk_099A8914;
    } else {
        gWorldselectSlots[slot].gfx = sWorldselectWorldDefs[model].gfx;
    }
}

void WorldselectDrawName(s16 model, s16 n) {
    vu32* dma;
    u16 zero;
    u8* src;
    u8* src2;
    u8* dst;
    u32 ctrl;
    u16* zp;

    zp = &zero;
    zero = 0;
    dma = (vu32*)REG_ADDR_DMA3;
    dma[0] = (vu32)zp;
    dma[1] = (vu32)gWorldselectNameBuffer;
    dma[2] = ((DMA_ENABLE | DMA_SRC_FIXED) << 16) | 0x360;
    dma[2];

    if (n > 0) {
#ifdef VERSION_EU
        src = ((u8**)sWorldselectWorldDefs[model].nameTiles)[gLanguage];
        src += sWorldselectWorldDefs[model].nameTilesOffset;
#else
        src = sWorldselectWorldDefs[model].nameTiles;
#endif
        dma[0] = (vu32)src;
        dst = (u8*)gWorldselectNameBuffer + (9 - n) * 32;
        dma[1] = (vu32)dst;
        ctrl = (n << 4) | (DMA_ENABLE << 16);
        dma[2] = ctrl;
        dma[2];
        src2 = src + (18 - n) * 32;
        dma[0] = (vu32)src2;
        dma[1] = (vu32)((u8*)gWorldselectNameBuffer + 288);
        dma[2] = ctrl;
        dma[2];
        dma[0] = (vu32)(src + 576);
        dma[1] = (vu32)(dst + 576);
        dma[2] = ctrl;
        dma[2];
        dma[0] = (vu32)(src2 + 576);
        dma[1] = (vu32)((u8*)gWorldselectNameBuffer + 864);
        dma[2] = ctrl;
        dma[2];
        src += 1152;
        dma[0] = (vu32)src;
        dst += 1152;
        dma[1] = (vu32)dst;
        dma[2] = ctrl;
        dma[2];
        src2 += 1152;
        dma[0] = (vu32)src2;
        dma[1] = (vu32)((u8*)gWorldselectNameBuffer + 1440);
        dma[2] = ctrl;
        dma[2];
    }

    RequestDma3Copy(gWorldselectNameBuffer, (u8*)GetBgCharBase(0) + 1024, 0x6C0);
}

void WorldselectHandleInput(void) {
    s16 i;
    s16 j;
    s16 k;
    u8 step;

    switch (gWorldselectRotation) {
    case 0:
        if (GetKeysPressed() & A_BUTTON) {
            BgAnimInit(2, 0x8000, 128);
            BgAnimStart(&gBgAnimDefWorldStart, 112, 126);
            SetBgPriority(2, 1);
            gBldCnt |= BLDCNT_TGT2_OBJ;
            gWorldselectBgAnimActive = 1;
            m4aSongNumStart(SONG_SYS_WORLDSTART);
            gWorldselectCancelled = 0;
            gWorldselectStep = 4;
        } else if ((GetKeysPressed() & B_BUTTON) && gWorldselectFirstVisit == 0) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            LoadBgMap(0, gUnk_09A310DC, 0x500);
            LoadBgMap(1, gUnk_09A31ADC, 0x500);
            gWorldselectCancelled = 1;
            gWorldselectTimer = 16;
            gWorldselectStep = 5;
        } else if (gWorldselectSlotCount > 1) {
            if (GetKeysHeld() & DPAD_LEFT) {
                j = gWorldselectCursor - gWorldselectSlotCount / 2;

                while (j < 0) {
                    j += gWorldselectSlotCount;
                }

                ReleaseObjPalette(gWorldselectSlots[j].palette);
                ReleaseObjTiles(gWorldselectSlots[j].tiles);
                k = gWorldselectSlots[gWorldselectCursor].listIndex - gWorldselectSlotCount / 2;

                while (k < 0) {
                    k += gWorldselectWorldCount;
                }

                gWorldselectSlots[j].listIndex = k;
                WorldselectLoadSlotPalette(gWorldselectWorlds[k], j);
                WorldselectLoadSlotTiles(gWorldselectWorlds[k], j);
                WorldselectSetSlotGfx(gWorldselectWorlds[k], j);
                gWorldselectCursor--;

                if (gWorldselectCursor < 0) {
                    gWorldselectCursor = gWorldselectSlotCount - 1;
                }

                m4aSongNumStart(SONG_SYS_WORLDSELECT);
                gWorldselectNameMode = 2;
                gWorldselectRotation = 2;
            } else if (GetKeysHeld() & DPAD_RIGHT) {
                j = gWorldselectCursor + gWorldselectSlotCount / 2;

                while (j >= gWorldselectSlotCount) {
                    j -= gWorldselectSlotCount;
                }

                ReleaseObjPalette(gWorldselectSlots[j].palette);
                ReleaseObjTiles(gWorldselectSlots[j].tiles);
                k = gWorldselectSlots[gWorldselectCursor].listIndex + gWorldselectSlotCount / 2;

                while (k >= gWorldselectWorldCount) {
                    k -= gWorldselectWorldCount;
                }

                gWorldselectSlots[j].listIndex = k;
                WorldselectLoadSlotPalette(gWorldselectWorlds[k], j);
                WorldselectLoadSlotTiles(gWorldselectWorlds[k], j);
                WorldselectSetSlotGfx(gWorldselectWorlds[k], j);
                gWorldselectCursor++;

                if (gWorldselectCursor >= gWorldselectSlotCount) {
                    gWorldselectCursor = 0;
                }

                m4aSongNumStart(SONG_SYS_WORLDSELECT);
                gWorldselectNameMode = 2;
                gWorldselectRotation = 1;
            }
        }
        break;
    case 1:
        if (GetKeysHeld() & DPAD_LEFT) {
            j = gWorldselectCursor - gWorldselectSlotCount / 2;

            while (j < 0) {
                j += gWorldselectSlotCount;
            }

            ReleaseObjPalette(gWorldselectSlots[j].palette);
            ReleaseObjTiles(gWorldselectSlots[j].tiles);
            k = gWorldselectSlots[gWorldselectCursor].listIndex - gWorldselectSlotCount / 2;

            while (k < 0) {
                k += gWorldselectWorldCount;
            }

            gWorldselectSlots[j].listIndex = k;
            WorldselectLoadSlotPalette(gWorldselectWorlds[k], j);
            WorldselectLoadSlotTiles(gWorldselectWorlds[k], j);
            WorldselectSetSlotGfx(gWorldselectWorlds[k], j);
            gWorldselectCursor--;

            if (gWorldselectCursor < 0) {
                gWorldselectCursor = gWorldselectSlotCount - 1;
            }

            m4aSongNumStart(SONG_SYS_WORLDSELECT);
            gWorldselectRotation = 2;
        } else {
            for (i = 0; i < gWorldselectSlotCount; i++) {
                gWorldselectSlots[i].angle -= 2;
            }

            if (gWorldselectSlots[gWorldselectCursor].angle <= 128) {
                if (GetKeysHeld() & DPAD_RIGHT) {
                    j = gWorldselectCursor + gWorldselectSlotCount / 2;

                    while (j >= gWorldselectSlotCount) {
                        j -= gWorldselectSlotCount;
                    }

                    ReleaseObjPalette(gWorldselectSlots[j].palette);
                    ReleaseObjTiles(gWorldselectSlots[j].tiles);
                    k = gWorldselectSlots[gWorldselectCursor].listIndex + gWorldselectSlotCount / 2;

                    while (k >= gWorldselectWorldCount) {
                        k -= gWorldselectWorldCount;
                    }

                    gWorldselectSlots[j].listIndex = k;
                    WorldselectLoadSlotPalette(gWorldselectWorlds[k], j);
                    WorldselectLoadSlotTiles(gWorldselectWorlds[k], j);
                    WorldselectSetSlotGfx(gWorldselectWorlds[k], j);
                    gWorldselectCursor++;

                    if (gWorldselectCursor >= gWorldselectSlotCount) {
                        gWorldselectCursor = 0;
                    }

                    m4aSongNumStart(SONG_SYS_WORLDSELECT);
                    gWorldselectRotation = 1;
                } else {
                    step = 128 - gWorldselectSlots[gWorldselectCursor].angle;

                    for (i = 0; i < gWorldselectSlotCount; i++) {
                        gWorldselectSlots[i].angle += step;
                    }

                    gWorldselectNameMode = 1;
                    gWorldselectNameWorld = gWorldselectWorlds[gWorldselectSlots[gWorldselectCursor].listIndex];
                    gWorldselectRotation = 0;
                }
            }
        }
        break;
    case 2:
        if (GetKeysHeld() & DPAD_RIGHT) {
            j = gWorldselectCursor + gWorldselectSlotCount / 2;

            while (j >= gWorldselectSlotCount) {
                j -= gWorldselectSlotCount;
            }

            ReleaseObjPalette(gWorldselectSlots[j].palette);
            ReleaseObjTiles(gWorldselectSlots[j].tiles);
            k = gWorldselectSlots[gWorldselectCursor].listIndex + gWorldselectSlotCount / 2;

            while (k >= gWorldselectWorldCount) {
                k -= gWorldselectWorldCount;
            }

            gWorldselectSlots[j].listIndex = k;
            WorldselectLoadSlotPalette(gWorldselectWorlds[k], j);
            WorldselectLoadSlotTiles(gWorldselectWorlds[k], j);
            WorldselectSetSlotGfx(gWorldselectWorlds[k], j);
            gWorldselectCursor++;

            if (gWorldselectCursor >= gWorldselectSlotCount) {
                gWorldselectCursor = 0;
            }

            m4aSongNumStart(SONG_SYS_WORLDSELECT);
            gWorldselectRotation = 1;
        } else {
            for (i = 0; i < gWorldselectSlotCount; i++) {
                gWorldselectSlots[i].angle += 2;
            }

            if ((s8)gWorldselectSlots[gWorldselectCursor].angle < 0) {
                if (GetKeysHeld() & DPAD_LEFT) {
                    j = gWorldselectCursor - gWorldselectSlotCount / 2;

                    while (j < 0) {
                        j += gWorldselectSlotCount;
                    }

                    ReleaseObjPalette(gWorldselectSlots[j].palette);
                    ReleaseObjTiles(gWorldselectSlots[j].tiles);
                    k = gWorldselectSlots[gWorldselectCursor].listIndex - gWorldselectSlotCount / 2;

                    while (k < 0) {
                        k += gWorldselectWorldCount;
                    }

                    gWorldselectSlots[j].listIndex = k;
                    WorldselectLoadSlotPalette(gWorldselectWorlds[k], j);
                    WorldselectLoadSlotTiles(gWorldselectWorlds[k], j);
                    WorldselectSetSlotGfx(gWorldselectWorlds[k], j);
                    gWorldselectCursor--;

                    if (gWorldselectCursor < 0) {
                        gWorldselectCursor = gWorldselectSlotCount - 1;
                    }

                    m4aSongNumStart(SONG_SYS_WORLDSELECT);
                    gWorldselectRotation = 2;
                } else {
                    step = gWorldselectSlots[gWorldselectCursor].angle + 128;

                    for (i = 0; i < gWorldselectSlotCount; i++) {
                        gWorldselectSlots[i].angle -= step;
                    }

                    gWorldselectNameMode = 1;
                    gWorldselectNameWorld = gWorldselectWorlds[gWorldselectSlots[gWorldselectCursor].listIndex];
                    gWorldselectRotation = 0;
                }
            }
        }
        break;
    }
}

void WorldselectDraw(void) {
    s16 i;
    ObjAffine* sprite;
    s16 x;
    s16 y;
    u8 ang;
    u8 t;
    s32 s;
    s32 h;
    s32 d;
    s32 w;
    s32 v;
    s16 angle;
    void* anim;
    void* tiles;
    void* pal;

    if (gWorldselectStep < 2 || gWorldselectStep > 4) {
        DrawSprite(gWorldselectTitleX >> 8, 0,
#ifdef VERSION_EU
                      sWorldselectTitleGfx[gLanguage],
#else
                      gUnk_0999CB90,
#endif
                      gWorldselectTitleTiles, gWorldselectOverlayPalette, 0, SPRITE_PRIORITY(1),
                      0x3E8);
        DrawSprite(120, gWorldselectFrameY[0] >> 8, gUnk_0999C394, gWorldselectFrameTiles, gWorldselectOverlayPalette, 0,
                      SPRITE_PRIORITY(1), 0x3E9);
        DrawSprite(120, gWorldselectFrameY[1] >> 8, gUnk_0999C3C8, gWorldselectFrameTiles, gWorldselectOverlayPalette, 0,
                      SPRITE_PRIORITY(3), 0xBBA);
    }

    for (i = 0; i < gWorldselectSlotCount; i++) {
        ang = gWorldselectSlots[i].angle;
        s = -gSineTable[((256 / gWorldselectSlotCount * i + gWorldselectBobPhase) & 0xFF) + 64];
        t = (s * 3 >> 7) + ang;

        if ((u8)(t - 62) > 2 && (u8)(t + 64) > 2) {
            h = -gSineTable[ang + 64] * 5 >> 5;
            d = -25600 / (h - 140);
            w = -gSineTable[t + 64] * d >> 8;
            angle = ang;
            x = (gSineTable[angle] * 5 >> 4) + 120;
            v = ((d << 3) * s >> 16) + 64;
            y = h + v;

            if ((u8)(t - 121) <= 14) {
                sprite = 0;
                tiles = gWorldselectCardTiles[0];
                pal = gWorldselectCardPalettes[0];
                anim = gUnk_0999A350;

                if (gWorldselectStep > 3 && gWorldselectCancelled == 0) {
                    BgAnimSetPosition(x - 1, y - 5);
                }
            } else if (t <= 61) {
                sprite = 0;
                tiles = gWorldselectCardTiles[1];
                pal = gWorldselectCardPalettes[1];
                anim = gUnk_09EF9770[(62 - t) / 13];
            } else if (t > 194) {
                sprite = 0;
                tiles = gWorldselectCardTiles[1];
                pal = gWorldselectCardPalettes[1];
                anim = gUnk_09EF9770[(t - 194) / 13];
            } else {
                sprite = AllocObjAffine(0, w, d, 0);
                tiles = gWorldselectCardTiles[0];
                pal = gWorldselectCardPalettes[0];
                anim = gUnk_0999A350;
            }

            DrawSprite(x, y, anim, tiles, pal, sprite, SPRITE_PRIORITY(2),
                          ang > 128 ? (u16)(ang * 2 + 0x6D1) : (u16)((128 - ang) * 2 + 0x7D1));

            if ((u8)(t - 65) <= 126) {
                DrawSprite(x, y, gWorldselectSlots[i].gfx, gWorldselectSlots[i].tiles,
                              gWorldselectSlots[i].palette, sprite, SPRITE_PRIORITY(2),
                              ang > 128 ? (u16)(ang * 2 + 0x6D0)
                                        : (u16)((128 - ang) * 2 + 0x7D0));
            }
        }
    }

    switch (gWorldselectNameMode) {
    case 1:
        WorldselectDrawName(gWorldselectNameWorld, gWorldselectNameWidth);

        if (gWorldselectNameWidth <= 8) {
            gWorldselectNameWidth++;
        } else {
            gWorldselectNameMode = 0;
        }
        break;
    case 2:
        WorldselectDrawName(gWorldselectNameWorld, gWorldselectNameWidth);

        if (gWorldselectNameWidth > 0) {
            gWorldselectNameWidth--;
        } else {
            gWorldselectNameMode = 0;
        }
        break;
    }

    if (gWorldselectBgAnimActive != 0) {
        BgAnimUpdate();
    }

    TaskPoolDraw(&gWorldselectTaskPool);
}

void WorldselectSetBgMode0(void) {
    SetBgMode0();
    SetupBg(0, 0, 28, 0);
    SetupBg(1, 0, 29, 0);
    SetupBg(2, 1, 30, 14);
    SetBgPriority(0, 3);
    SetBgPriority(1, 1);
    SetBgPriority(2, 0);
}
void WorldselectSetBgMode1(void) {
    SetBgMode1();
    SetupBg(0, 0, 28, 0);
    SetupBg(1, 0, 29, 0);
    SetupBg(2, 1, 30, 10);
    SetBgPriority(0, 3);
    SetBgPriority(1, 0);
    SetBgPriority(2, 2);
    gBldCnt = (BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1);
    gBldAlpha = 0x1010;
}
void WorldselectCyclePalette(void) {
    gWorldselectPaletteTimer++;

    if (gWorldselectPaletteTimer > 6) {
        gWorldselectPaletteTimer = 0;
        gWorldselectPaletteFrame++;

        if (gWorldselectPaletteFrame > 29) {
            gWorldselectPaletteFrame = 0;
        }

        LoadPalette(sWorldselectPaletteCycle[(s16)gWorldselectPaletteFrame], (void*)0x05000040, 32);
    }
}

void mode_worldselect_0(void) {
    s16 i;
    s16 j;
    void** p;

    SpriteReset();
    gWorldselectFirstVisit = (gGameState.progression.unk_82 ^ 1) & 1;
    gWorldselectBgAnimActive = 0;
    gWorldselectCancelled = 0;
    FadeStartIn(2, 16);

    if (gWorldselectFirstVisit != 0) {
        WorldselectSetBgMode0();
    } else {
        WorldselectSetBgMode1();
    }

    gWorldselectCursor = 0;
    gWorldselectRotation = 0;
    j = 0;

    for (i = 0; i <= 12; i++) {
        if (gGameState.availableWorlds & sWorldselectWorldDefs[i].worldBit) {
            gWorldselectWorlds[j] = i;
            j++;
        }
    }

    gWorldselectWorldCount = j;
    gWorldselectSlotCount = j > 5 ? 5 : j;
    j = 0;

    for (i = 0; i < gWorldselectSlotCount; i++, j++) {
        if (j >= gWorldselectWorldCount) {
            j = 0;
        }

        if (i == gWorldselectSlotCount - 1 && gWorldselectSlotCount > 2) {
            j = gWorldselectWorldCount - 1;
        }

        gWorldselectSlots[i].listIndex = j;
        gWorldselectSlots[i].angle = 256 / gWorldselectSlotCount * i - 128;
        WorldselectLoadSlotPalette(gWorldselectWorlds[j], i);
        WorldselectLoadSlotTiles(gWorldselectWorlds[j], i);
        WorldselectSetSlotGfx(gWorldselectWorlds[j], i);
    }

    gWorldselectBobPhase = 0;
    gWorldselectNameMode = 1;
    gWorldselectNameWidth = 0;
    gWorldselectNameWorld = gWorldselectWorlds[gWorldselectSlots[gWorldselectCursor].listIndex];
    p = &gWorldselectNameBuffer;
    *p = EwramAlloc(0x6C0);
    gWorldselectPaletteTimer = 0;
    gWorldselectPaletteFrame = 0;
    gWorldselectStep = 0;
    gWorldselectTimer = 16;
    gWorldselectFrameY[0] = -2048;
    gWorldselectFrameY[1] = 0xA800;
    gWorldselectTitleX = -32768;
    LoadBgPalette(0, gUnk_09A3C9DC, 96);
#ifdef VERSION_EU
    LoadBgTiles(0, gUnk_099F1E7C, 16000);
#else
    LoadBgTiles(0, gUnk_099F1E7C, 11968);
#endif
    WorldselectDrawName(gWorldselectNameWorld, gWorldselectNameWidth);
    LoadBgMap(0, gUnk_09A310DC, 0x500);
    LoadBgMap(1, gUnk_09A31ADC, 0x500);

    if (gWorldselectFirstVisit == 0) {
        BgAnimInit(2, 0x8000, 128);
        BgAnimStart(&gBgAnimDefWorldSelect, 120, 110);
        BgAnimSetLoopStartFrame(0);
        gWorldselectBgAnimActive = 1;
    }

    gWorldselectCardPalettes[0] = LoadObjPalette(gUnk_09A3CC3C, 32);
    gWorldselectCardTiles[0] = LoadObjTiles(gUnk_0999A394, 0xC40);
    gWorldselectCardPalettes[1] = LoadObjPalette(gUnk_09A3CC5C, 32);
    gWorldselectCardTiles[1] = LoadObjTiles(gUnk_0999B052, 0x1340);
    gWorldselectOverlayPalette = LoadObjPalette(gUnk_09A3CC7C, 32);
#ifdef VERSION_EU
    gWorldselectTitleTiles = LoadObjTiles(sWorldselectTitleTileData[gLanguage], sWorldselectTitleTileSizes.sizes[gLanguage]);
#else
    gWorldselectTitleTiles = LoadObjTiles(gUnk_0999CBB6, 0x380);
#endif
    gWorldselectFrameTiles = LoadObjTiles(gUnk_0999C410, 0x780);
    TaskPoolInit(&gWorldselectTaskPool, 1);
    EnableBg(0);
    EnableBg(1);

    if (gWorldselectFirstVisit != 0) {
        DisableBg(2);
    } else {
        EnableBg(2);
    }
}

void mode_worldselect_1(void) {
    s16 a;
    s16 b;

    UpdatePlayTime();
    gWorldselectBobPhase += 2;

    switch (gWorldselectStep) {
    case 0:
        ApproachValue(&gWorldselectFrameY[0], 0, gWorldselectTimer);
        ApproachValue(&gWorldselectFrameY[1], 0x9800, gWorldselectTimer);
        gWorldselectTimer--;

        if (gWorldselectTimer <= 0) {
            gWorldselectTimer = 16;
            gWorldselectStep = 1;
        }
        break;
    case 1:
        ApproachValue(&gWorldselectTitleX, 0, gWorldselectTimer);
        gWorldselectTimer--;

        if (gWorldselectTimer <= 0) {
            if (gWorldselectFirstVisit != 0) {
                gWorldselectTutorialStep = 0;
                CreateCardMessageTask(&gWorldselectTaskPool, 2, 70);
                gWorldselectStep = 2;
            } else {
                gWorldselectStep = 3;
            }

            LoadBgMap(0, gUnk_09A315DC, 0x500);
#ifdef VERSION_EU
            LoadBgMap(1, sWorldselectBg1Maps[gLanguage], 0x500);
#else
            LoadBgMap(1, gUnk_09A31FDC, 0x500);
#endif
        }
        break;
    case 2:
        if (IsMessageWindowOpen() == 0) {
            if (gWorldselectTutorialStep == 0) {
                CreateCardMessageTask(&gWorldselectTaskPool, 2, 71);
                gWorldselectTutorialStep++;
            } else {
                gGameState.progression.unk_82 |= 1;
                WorldselectSetBgMode1();
                BgAnimInit(2, 0x8000, 128);
                BgAnimStart(&gBgAnimDefWorldSelect, 120, 110);
                BgAnimSetLoopStartFrame(0);
                gWorldselectBgAnimActive = 1;
                gWorldselectStep = 3;
            }
        }
        break;
    case 3:
        WorldselectHandleInput();
        break;
    case 4:
        if (BgAnimIsStopped() != 0) {
            LoadBgMap(0, gUnk_09A310DC, 0x500);
            LoadBgMap(1, gUnk_09A31ADC, 0x500);
            gWorldselectTimer = 16;
            gWorldselectStep = 5;
        }
        break;
    case 5:
        ApproachValue(&gWorldselectTitleX, -32768, gWorldselectTimer);
        gWorldselectTimer--;

        if (gWorldselectTimer <= 0) {
            gWorldselectTimer = 16;
            gWorldselectStep = 6;
        }
        break;
    case 6:
        ApproachValue(&gWorldselectFrameY[0], -2048, gWorldselectTimer);
        ApproachValue(&gWorldselectFrameY[1], 0xA800, gWorldselectTimer);
        gWorldselectTimer--;

        if (gWorldselectTimer <= 0) {
            gWorldselectStep = 7;
        }
        break;
    case 7:
        FadeLock();

        if (gWorldselectCancelled != 0) {
            FadeStartOut(0, 16);
        } else {
            FadeStartOut(2, 16);
        }

        gWorldselectStep = 8;
        break;
    case 8:
        if (FadeIsActive() == 0) {
            if (gWorldselectCancelled != 0) {
                RequestMapMode();
            } else {
                gWorldselectTimer = 60;
                gWorldselectStep = 9;
            }
        }
        break;
    case 9:
        gWorldselectTimer--;

        if (gWorldselectTimer <= 0) {
            a = sWorldselectWorldDefs[gWorldselectWorlds[gWorldselectSlots[gWorldselectCursor].listIndex]].world;

            if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
                b = sWorldselectWorldDefs[gWorldselectWorlds[gWorldselectSlots[gWorldselectCursor].listIndex]].eventId;
            } else {
                b = sWorldselectWorldDefs[gWorldselectWorlds[gWorldselectSlots[gWorldselectCursor].listIndex]].rikuEventId;
            }

            gGameState.availableWorlds &=
                ~sWorldselectWorldDefs[gWorldselectWorlds[gWorldselectSlots[gWorldselectCursor].listIndex]].worldBit;
            SetFloorWorld(a);

            if (b >= 0) {
                RequestEventMode(b);
            } else {
                if (gGameState.flags & GAME_FLAG_RIKU) {
                    AddMapCard(221);
                }

                EnterFloorWorld();
                RequestMapMode();
            }
        }
        break;
    }

    WorldselectCyclePalette();

    if (FadeIsActive() != 0) {
        FadeGetAmount();
    }

    TaskPoolUpdate(&gWorldselectTaskPool);
    WorldselectDraw();
}

void mode_worldselect_2(void) {
    s16 i;

    EwramFree(gWorldselectNameBuffer);

    for (i = 0; i < gWorldselectSlotCount; i++) {
        ReleaseObjPalette(gWorldselectSlots[i].palette);
        ReleaseObjTiles(gWorldselectSlots[i].tiles);
    }

    for (i = 0; i < 2; i++) {
        ReleaseObjPalette(gWorldselectCardPalettes[i]);
        ReleaseObjTiles(gWorldselectCardTiles[i]);
    }

    ReleaseObjPalette(gWorldselectOverlayPalette);
    ReleaseObjTiles(gWorldselectTitleTiles);
    ReleaseObjTiles(gWorldselectFrameTiles);
    TaskPoolDestroy(&gWorldselectTaskPool);
}
