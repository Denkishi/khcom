#include "display.h"
#include "battle.h"
#include "battle_bg_animations.h"
#include "malloc.h"
#include "fade.h"
#include "songs.h"
#include <stdlib.h>
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "bg_animation_types.h"
#include "btl_collision.h"
#include "engine_math.h"
#include "listpool.h"
#include "m4a_song.h"
#include "types.h"
#include <stddef.h>

static const BgAnimationChunk sBgAnimationChunks[108] = {
    { gUnk_08CEFCE4, 29696, 0 },
    { gUnk_08D0E664, 31168, 0 },
    { gUnk_08D16024, 3008, 0 },
    { gUnk_08D16BE4, 17408, 0 },
    { gUnk_08D1AFE4, 21312, 0 },
    { gUnk_08CC46E4, 16640, 0 },
    { gUnk_08CC87E4, 4416, 0 },
    { gUnk_08CD3464, 9472, 0 },
    { gUnk_08CC9924, 16064, 0 },
    { gUnk_08CCD7E4, 23680, 0 },
    { gUnk_08CD5964, 9152, 0 },
    { gUnk_08CE9664, 26240, 0 },
    { gUnk_08D299A4, 29568, 0 },
    { gUnk_08D30D24, 11840, 0 },
    { gUnk_08D33B64, 11648, 0 },
    { gUnk_08D368E4, 18368, 0 },
    { gUnk_08D3B0A4, 31040, 0 },
    { gUnk_08D429E4, 24832, 0 },
    { gUnk_08D48AE4, 29056, 0 },
    { gUnk_08D4FC64, 11200, 0 },
    { gUnk_08D52824, 28160, 0 },
    { gUnk_08D59624, 28416, 0 },
    { gUnk_08D60524, 7104, 0 },
    { gUnk_08D620E4, 29504, 0 },
    { gUnk_08D69424, 29952, 0 },
    { gUnk_08D70924, 28928, 0 },
    { gUnk_08D9D764, 10752, 0 },
    { gUnk_08DA0164, 19904, 0 },
    { gUnk_08DA4F24, 20160, 0 },
    { gUnk_08D022A4, 30336, 0 },
    { gUnk_08D09924, 19776, 0 },
    { gUnk_08CF70E4, 30656, 0 },
    { gUnk_08CFE8A4, 14848, 0 },
    { gUnk_08D20324, 30464, 0 },
    { gUnk_08D27A24, 8064, 0 },
    { gUnk_08CD7D24, 19520, 0 },
    { gUnk_08D77A24, 12224, 0 },
    { gUnk_08D7A9E4, 19712, 0 },
    { gUnk_08D7F6E4, 28416, 0 },
    { gUnk_08D865E4, 17280, 0 },
    { gUnk_08DA9DE4, 31104, 0 },
    { gUnk_08DB1764, 9920, 0 },
    { gUnk_08CE0664, 32256, 0 },
    { gUnk_08CE8464, 4608, 0 },
    { gUnk_08DB3E24, 22656, 0 },
    { gUnk_08DB96A4, 22656, 0 },
    { gUnk_08DBEF24, 22656, 0 },
    { gUnk_08DC47A4, 22656, 0 },
    { gUnk_08DCA024, 22656, 0 },
    { gUnk_08DCF8A4, 11328, 0 },
    { gUnk_08CDC964, 15616, 0 },
    { gUnk_08DD24E4, 30848, 0 },
    { gUnk_08DD9D64, 17664, 0 },
    { gUnk_08DDE264, 32640, 0 },
    { gUnk_08DE61E4, 21184, 0 },
    { gUnk_08D8A964, 23616, 0 },
    { gUnk_08D905A4, 31936, 0 },
    { gUnk_08D98264, 21760, 0 },
    { gUnk_08DEB4A4, 30720, 0 },
    { gUnk_08DF2CA4, 24256, 0 },
    { gUnk_08DF8B64, 18688, 0 },
    { gUnk_08DFD464, 11776, 0 },
    { gUnk_08E00264, 8640, 0 },
    { gUnk_08E02424, 9216, 0 },
    { gUnk_08E0CB24, 7808, 0 },
    { gUnk_08E04824, 29632, 0 },
    { gUnk_08E0BBE4, 3904, 0 },
    { gUnk_08E0E9A4, 19392, 0 },
    { gUnk_08E13564, 6720, 0 },
    { gUnk_08E14FA4, 31104, 0 },
    { gUnk_08E1C924, 31104, 0 },
    { gUnk_08E242A4, 7232, 0 },
    { gUnk_08E25EE4, 12288, 0 },
    { gUnk_08E28EE4, 30400, 0 },
    { gUnk_08E305A4, 11392, 0 },
    { gUnk_08E33224, 31232, 0 },
    { gUnk_08E3F6E4, 15744, 0 },
    { gUnk_08E3AC24, 4736, 0 },
    { gUnk_08E3BEA4, 14400, 0 },
    { gUnk_08E43464, 18176, 0 },
    { gUnk_08E47B64, 11520, 0 },
    { gUnk_08E4A864, 32448, 0 },
    { gUnk_08E52724, 29760, 0 },
    { gUnk_08E59B64, 29760, 0 },
    { gUnk_08E60FA4, 32640, 0 },
    { gUnk_08E68F24, 8064, 0 },
    { gUnk_08E6AEA4, 7360, 0 },
    { gUnk_08E6CB64, 15168, 0 },
    { gUnk_08E706A4, 27648, 0 },
    { gUnk_08E772A4, 9216, 0 },
    { gUnk_08E796A4, 28224, 0 },
    { gUnk_08E804E4, 8896, 0 },
    { gUnk_08E83864, 3776, 0 },
    { gUnk_08E827A4, 4288, 0 },
    { gUnk_08E84724, 30016, 0 },
    { gUnk_08E8BC64, 12032, 0 },
    { gUnk_08E8EB64, 28928, 0 },
    { gUnk_08E95C64, 13952, 0 },
    { gUnk_08E992E4, 29824, 0 },
    { gUnk_08EA0764, 12032, 0 },
    { gUnk_08EA3664, 28416, 0 },
    { gUnk_08EAA564, 4736, 0 },
    { gUnk_08EB17A4, 27648, 0 },
    { gUnk_08EB83A4, 26496, 0 },
    { gUnk_08EBEB24, 26944, 0 },
    { gUnk_08EC5464, 32448, 0 },
    { gUnk_08EAB7E4, 24512, 0 },
    { gUnk_08ECD324, 20160, 0 },
};

BgAnimationDef gBgAnimDefCure00 = { &sBgAnimationChunks[0], gUnk_08F0C384, gUnk_08F6A824, 192, 58, 16, 16, 8, 6 };

BgAnimationDef gBgAnimDefFire00 = { &sBgAnimationChunks[1], gUnk_08F0F384, gUnk_08F6AA64, 192, 56, 21, 16, 10, 3 };

BgAnimationDef gBgAnimDefRikuFire00 = { &sBgAnimationChunks[1], gUnk_08F0F384, gUnk_08F69FE4, 192, 56, 21, 16, 10, 3 };

BgAnimationDef gBgAnimDefFlame = { &sBgAnimationChunks[1], gUnk_08F0F384, gUnk_08F6AA64, 192, 56, 12, 16, 3, 4 };

BgAnimationDef gBgAnimDefFire01 = { &sBgAnimationChunks[3], gUnk_08F10384, gUnk_08F6AB24, 192, 41, 16, 16, 7, 4 };

static BgAnimationDef sBgAnimDefFireHit = { &sBgAnimationChunks[3], gUnk_08F10384, gUnk_08F6AB24, 192, 41, 16, 16, 7, 2 };

BgAnimationDef gBgAnimDefFire02 = { &sBgAnimationChunks[4], gUnk_08F11384, gUnk_08F6ABE4, 192, 48, 16, 16, 7, 4 };

BgAnimationDef gBgAnimDefExplosion = { &sBgAnimationChunks[5], gUnk_08F02384, gUnk_08F6A0A4, 192, 33, 16, 16, 8, 6 };

BgAnimationDef gBgAnimDefFlash = { &sBgAnimationChunks[6], gUnk_08F03384, gUnk_08F6A164, 192, 69, 16, 16, 1, 65535 };

BgAnimationDef gBgAnimDefSoraHit = { &sBgAnimationChunks[7], gUnk_08F06384, gUnk_08F6A3A4, 192, 37, 16, 16, 4, 3 };

BgAnimationDef gBgAnimDefLimit = { &sBgAnimationChunks[8], gUnk_08F04384, gUnk_08F6A224, 192, 42, 16, 16, 6, 3 };

BgAnimationDef gUnk_09EDA660 = { &sBgAnimationChunks[9], gUnk_08F05384, gUnk_08F6A2E4, 192, 74, 16, 16, 5, 3 };

BgAnimationDef gBgAnimDefEnemyHit = { &sBgAnimationChunks[10], gUnk_08F07384, gUnk_08F6A464, 192, 36, 16, 16, 4, 4 };

BgAnimationDef gUnk_09EDA690 = { &sBgAnimationChunks[10], gUnk_08F07384, gUnk_08F69DA4, 192, 36, 16, 16, 4, 4 };

BgAnimationDef gUnk_09EDA6A8 = { &sBgAnimationChunks[10], gUnk_08F07384, gUnk_08F69E64, 192, 36, 16, 16, 4, 4 };

BgAnimationDef gBgAnimDefPotion = { &sBgAnimationChunks[11], gUnk_08F0B384, gUnk_08F6A764, 192, 46, 16, 16, 9, 5 };

BgAnimationDef gBgAnimDefBlizzard00 = { &sBgAnimationChunks[12], gUnk_08F13384, gUnk_08F6AD64, 192, 66, 21, 16, 10, 3 };

BgAnimationDef gBgAnimDefFrost = { &sBgAnimationChunks[12], gUnk_08F13384, gUnk_08F6AD64, 192, 66, 12, 16, 3, 4 };

BgAnimationDef gBgAnimDefBlizzard01 = { &sBgAnimationChunks[14], gUnk_08F14384, gUnk_08F6AE24, 192, 37, 16, 16, 5, 7 };

static BgAnimationDef sBgAnimDefBlizzardHit = { &sBgAnimationChunks[14], gUnk_08F14384, gUnk_08F6AE24, 192, 37, 16, 16, 5, 3 };

BgAnimationDef gBgAnimDefBlizzard02 = { &sBgAnimationChunks[15], gUnk_08F15384, gUnk_08F6AEE4, 192, 48, 16, 16, 6, 8 };

BgAnimationDef gBgAnimDefBlizzard03 = { &sBgAnimationChunks[16], gUnk_08F16384, gUnk_08F6AFA4, 192, 97, 16, 16, 9, 7 };

BgAnimationDef gBgAnimDefThunder00 = { &sBgAnimationChunks[18], gUnk_08F17384, gUnk_08F6B064, 192, 57, 16, 16, 8, 4 };

static BgAnimationDef sBgAnimDefThunderHit = { &sBgAnimationChunks[18], gUnk_08F17384, gUnk_08F6B064, 192, 57, 16, 16, 8, 2 };

BgAnimationDef gBgAnimDefThunder01 = { &sBgAnimationChunks[19], gUnk_08F18384, gUnk_08F6B124, 192, 36, 16, 21, 5, 5 };

BgAnimationDef gBgAnimDefThunder02 = { &sBgAnimationChunks[20], gUnk_08F19384, gUnk_08F6B1E4, 192, 111, 16, 19, 9, 5 };

BgAnimationDef gBgAnimDefThunder03 = { &sBgAnimationChunks[23], gUnk_08F1A384, gUnk_08F6B2A4, 192, 117, 16, 19, 12, 6 };

BgAnimationDef gBgAnimDefCharaDefeatEnd = { &sBgAnimationChunks[26], gUnk_08F20384, gUnk_08F6B724, 192, 21, 16, 16, 8, 8 };

BgAnimationDef gBgAnimDefEnemyDeath = { &sBgAnimationChunks[27], gUnk_08F21384, gUnk_08F6B7E4, 192, 61, 16, 21, 5, 2 };

BgAnimationDef gBgAnimDefDarkDeath = { &sBgAnimationChunks[28], gUnk_08F22384, gUnk_08F6B8A4, 64, 64, 8, 8, 5, 3 };

BgAnimationDef gBgAnimDefCure02 = { &sBgAnimationChunks[29], gUnk_08F0E384, gUnk_08F6A9A4, 192, 79, 16, 16, 10, 6 };

BgAnimationDef gBgAnimDefCure01 = { &sBgAnimationChunks[31], gUnk_08F0D384, gUnk_08F6A8E4, 192, 80, 16, 16, 9, 6 };

BgAnimationDef gBgAnimDefFire03 = { &sBgAnimationChunks[33], gUnk_08F12384, gUnk_08F6ACA4, 192, 68, 16, 16, 9, 6 };

BgAnimationDef gBgAnimDefRikuFire03 = { &sBgAnimationChunks[33], gUnk_08F12384, gUnk_08F69F24, 192, 68, 16, 16, 9, 6 };

BgAnimationDef gBgAnimDefFriendHit = { &sBgAnimationChunks[35], gUnk_08F08384, gUnk_08F6A524, 192, 61, 16, 16, 5, 3 };

BgAnimationDef gBgAnimDefStop00 = { &sBgAnimationChunks[36], gUnk_08F1B384, gUnk_08F6B364, 192, 33, 16, 16, 6, 5 };

BgAnimationDef gBgAnimDefStop01 = { &sBgAnimationChunks[37], gUnk_08F1C384, gUnk_08F6B424, 192, 52, 16, 16, 6, 5 };

BgAnimationDef gBgAnimDefStop02 = { &sBgAnimationChunks[38], gUnk_08F1D384, gUnk_08F6B4E4, 192, 90, 16, 16, 8, 5 };

BgAnimationDef gBgAnimDefSummon = { &sBgAnimationChunks[40], gUnk_08F23384, gUnk_08F6B8E4, 192, 81, 16, 16, 8, 3 };

BgAnimationDef gBgAnimDefGroundImpact = { &sBgAnimationChunks[42], gUnk_08F0A384, gUnk_08F6A6A4, 192, 72, 16, 16, 8, 3 };

BgAnimationDef gBgAnimDefBtlStart = { &sBgAnimationChunks[44], gUnk_08F24384, gUnk_08F6B9A4, 192, 177, 16, 11, 11, 4 };

BgAnimationDef gBgAnimDefGuard = { &sBgAnimationChunks[50], gUnk_08F09384, gUnk_08F6A5E4, 192, 41, 16, 16, 6, 3 };

BgAnimationDef gBgAnimDefCharaDefeat = { &sBgAnimationChunks[51], gUnk_08F25384, gUnk_08F6BA64, 192, 69, 16, 16, 11, 5 };

BgAnimationDef gBgAnimDefHumDefeat = { &sBgAnimationChunks[53], gUnk_08F26384, gUnk_08F6BB24, 192, 85, 16, 16, 10, 5 };

BgAnimationDef gBgAnimDefGravity00 = { &sBgAnimationChunks[55], gUnk_08F1E384, gUnk_08F6B5A4, 192, 41, 16, 16, 9, 2 };

BgAnimationDef gBgAnimDefGravity01 = { &sBgAnimationChunks[56], gUnk_08F1F384, gUnk_08F6B664, 192, 85, 16, 22, 10, 6 };

BgAnimationDef gBgAnimDefPremireChance = { &sBgAnimationChunks[58], gUnk_08F27384, gUnk_08F6BBE4, 192, 96, 12, 14, 9, 5 };

BgAnimationDef gBgAnimDefGas = { &sBgAnimationChunks[60], gUnk_08F28384, gUnk_08F6BCA4, 192, 73, 16, 16, 4, 5 };

BgAnimationDef gBgAnimDefEnemySpawn = { &sBgAnimationChunks[61], gUnk_08F29384, gUnk_08F6BD64, 192, 46, 16, 16, 4, 2 };

BgAnimationDef gBgAnimDefBoogieKaihuku = { &sBgAnimationChunks[62], gUnk_08F2A384, gUnk_08F6BE24, 192, 45, 16, 9, 3, 6 };

BgAnimationDef gBgAnimDefPcShot = { &sBgAnimationChunks[63], gUnk_08F2B384, gUnk_08F6BEE4, 192, 48, 16, 16, 3, 8 };

BgAnimationDef gUnk_09EDAA20 = { &sBgAnimationChunks[64], gUnk_08F2D384, gUnk_08F6C124, 192, 122, 16, 16, 1, 65535 };

static BgAnimationDef sUnk_09EDAA38 = { &sBgAnimationChunks[64], gUnk_08F2D384, gUnk_08F6C064, 192, 122, 16, 16, 1, 65535 };

BgAnimationDef gBgAnimDefBossDeath = { &sBgAnimationChunks[65], gUnk_08F2C384, gUnk_08F6BFA4, 192, 67, 16, 16, 8, 5 };

BgAnimationDef gBgAnimDefDumboSplash = { &sBgAnimationChunks[67], gUnk_08F2E384, gUnk_08F6C1E4, 192, 77, 26, 16, 4, 4 };

BgAnimationDef gBgAnimDefTrinityLimit = { &sBgAnimationChunks[68], gUnk_08F2F384, gUnk_08F6C2A4, 192, 105, 16, 15, 1, 65535 };

BgAnimationDef gBgAnimDefTrinityLimitCharge = { &sBgAnimationChunks[69], gUnk_08F30384, gUnk_08F6C364, 192, 122, 16, 22, 8, 4 };

BgAnimationDef gBgAnimDefTrinityLimitBlast = { &sBgAnimationChunks[71], gUnk_08F31384, gUnk_08F6C424, 192, 113, 15, 15, 1, 65535 };

BgAnimationDef gBgAnimDefRagnarokCharge = { &sBgAnimationChunks[72], gUnk_08F32384, gUnk_08F6C5A4, 192, 64, 10, 16, 3, 8 };

static BgAnimationDef sUnk_09EDAAE0 = { &sBgAnimationChunks[72], gUnk_08F32384, gUnk_08F6C4E4, 192, 86, 10, 16, 6, 3 };

BgAnimationDef gBgAnimDefRagnarokShot = { &sBgAnimationChunks[73], gUnk_08F33384, gUnk_08F6C664, 192, 95, 10, 16, 7, 3 };

BgAnimationDef gBgAnimDefUrsulaBeam = { &sBgAnimationChunks[75], gUnk_08F34384, gUnk_08F6C724, 192, 122, 24, 8, 4, 8 };

BgAnimationDef gBgAnimDefJfMajinBeam = { &sBgAnimationChunks[76], gUnk_08F37384, gUnk_08F6C964, 192, 82, 16, 27, 3, 8 };

BgAnimationDef gUnk_09EDAB40 = { &sBgAnimationChunks[77], gUnk_08F35384, gUnk_08F6C7E4, 192, 74, 17, 16, 1, 65535 };

BgAnimationDef gBgAnimDefAnsemWave = { &sBgAnimationChunks[78], gUnk_08F36384, gUnk_08F6C8A4, 192, 75, 16, 26, 3, 3 };

BgAnimationDef gBgAnimDefStunImpact = { &sBgAnimationChunks[79], gUnk_08F38384, gUnk_08F6CA24, 192, 74, 16, 18, 4, 5 };

BgAnimationDef gBgAnimDefUrsulaThunder = { &sBgAnimationChunks[80], gUnk_08F39384, gUnk_08F6CAE4, 192, 45, 16, 16, 4, 5 };

BgAnimationDef gBgAnimDefWorldSelect = { &sBgAnimationChunks[81], gUnk_08F3A384, gUnk_08F6CBA4, 192, 64, 20, 7, 8, 6 };

BgAnimationDef gBgAnimDefWorldStart = { &sBgAnimationChunks[82], gUnk_08F3B384, gUnk_08F6CC64, 192, 155, 16, 16, 6, 4 };

BgAnimationDef gBgAnimDefXmas = { &sBgAnimationChunks[84], gUnk_08F3C384, gUnk_08F6CD24, 192, 64, 32, 32, 10, 8 };

BgAnimationDef gBgAnimDefVixenIceFall = { &sBgAnimationChunks[84], gUnk_08F3C384, gUnk_08F6CD24, 192, 64, 32, 32, 10, 2 };

BgAnimationDef gUnk_09EDAC00 = { &sBgAnimationChunks[86], gUnk_08F3D384, gUnk_08F6CDE4, 192, 115, 16, 27, 1, 65535 };

BgAnimationDef gBgAnimDefTornado = { &sBgAnimationChunks[87], gUnk_08F3E384, gUnk_08F6CEA4, 192, 79, 16, 23, 3, 6 };

BgAnimationDef gUnk_09EDAC30 = { &sBgAnimationChunks[8], gUnk_08F04384, gUnk_08F69C24, 192, 42, 16, 16, 6, 3 };

BgAnimationDef gUnk_09EDAC48 = { &sBgAnimationChunks[9], gUnk_08F05384, gUnk_08F69CE4, 192, 74, 16, 16, 5, 3 };

BgAnimationDef gBgAnimDefAxcelFireWall = { &sBgAnimationChunks[88], gUnk_08F3F384, gUnk_08F6CF64, 192, 144, 20, 30, 4, 6 };

BgAnimationDef gBgAnimDefMahluxiaGround = { &sBgAnimationChunks[90], gUnk_08F40384, gUnk_08F6D0E4, 192, 74, 16, 16, 8, 6 };

static BgAnimationDef sBgAnimDefLexceusGround = { &sBgAnimationChunks[90], gUnk_08F40384, gUnk_08F6D024, 192, 74, 16, 16, 8, 4 };

static BgAnimationDef sBgAnimDefRikuLimit = { &sBgAnimationChunks[90], gUnk_08F40384, gUnk_08F6D0E4, 192, 74, 16, 16, 8, 3 };

BgAnimationDef gBgAnimDefHanabira = { &sBgAnimationChunks[92], gUnk_08F42384, gUnk_08F6D264, 192, 64, 32, 32, 1, 65535 };

BgAnimationDef gBgAnimDefKama = { &sBgAnimationChunks[93], gUnk_08F41384, gUnk_08F6D1A4, 192, 67, 16, 16, 1, 65535 };

BgAnimationDef gBgAnimDefDragonFire = { &sBgAnimationChunks[94], gUnk_08F43384, gUnk_08F6D324, 192, 96, 13, 24, 5, 6 };

BgAnimationDef gBgAnimDefLaxeneBeam = { &sBgAnimationChunks[96], gUnk_08F44384, gUnk_08F6D3E4, 192, 117, 8, 16, 6, 5 };

BgAnimationDef gBgAnimDefAero = { &sBgAnimationChunks[98], gUnk_08F45384, gUnk_08F6D4A4, 192, 81, 16, 22, 6, 6 };

BgAnimationDef gBgAnimDefRikuHit = { &sBgAnimationChunks[99], gUnk_08F46384, gUnk_08F6D564, 192, 48, 16, 16, 4, 4 };

BgAnimationDef gBgAnimDefRikuDarkModeFlash = { &sBgAnimationChunks[100], gUnk_08F47384, gUnk_08F6D624, 192, 74, 16, 21, 7, 5 };

BgAnimationDef gBgAnimDefLstCtr = { &sBgAnimationChunks[102], gUnk_08F49384, gUnk_08F6D7A4, 192, 108, 16, 16, 12, 7 };

BgAnimationDef gUnk_09EDAD80 = { &sBgAnimationChunks[105], gUnk_08F4A384, gUnk_08F6D864, 192, 64, 16, 16, 8, 6 };

BgAnimationDef gBgAnimDefRikuLimitFinish = { &sBgAnimationChunks[106], gUnk_08F48384, gUnk_08F6D6E4, 192, 64, 30, 30, 6, 7 };

BgAnimationDef gUnk_09EDADB0 = { &sBgAnimationChunks[107], gUnk_08F4B384, gUnk_08F6D924, 192, 64, 16, 16, 5, 5 };

BgFx* gBgFx;

void BgFxReset() {
    if (gBtlWork->flags & BTL_FLAG_BOSS_BATTLE) {
        SetBgPriority(gBgFx->bg, 0);
    } else {
        SetBgPriority(gBgFx->bg, 1);
    }

    SetBgBlend(gBgFx->bg, 16, 16);
    gBgFx->scaleX = 0x100;
    gBgFx->scaleY = 0x100;
    gBgFx->angle = 0;
    gBgFx->update = NULL;
    gBgFx->timer = 0;
    gBgFx->z = 0;
    gBgFx->flags = BGFX_FLAG_ACTIVE;
    gBgFx->releaseFrames = 0;
}

u8 BgFxIsBlocked(u8 a) {
    if (BgAnimIsStopped()) {
        gBgFx->priority = a;
        return 0;
    }

    if (gBgFx->priority < a) {
        return 1;
    }

    gBgFx->priority = a;
    return 0;
}

void BgFxReleaseEarly(s16 a) {
    u16 b;
    u16 c;
    BgAnimGetFrameState(&b, &c);

    if (BgAnimGetDuration(BgAnimGetCurrent()) - b * c <= a) {
        gBgFx->flags &= ~BGFX_FLAG_ACTIVE;
        gBgFx->priority = 2;

        if (gBgFx->flags & BGFX_FLAG_SCREEN_DIMMED) {
            gBgFx->flags &= ~BGFX_FLAG_SCREEN_DIMMED;
            FadeToOriginal(FADE_MODE_BLACK, 8);
        }
    }
}

void BgFxInit(u16 a, u16 bg) {
    s32 i;
    gBgFx = EwramAlloc(sizeof(BgFx));

    for (i = 10; i < 16; i++) {
        FadeSetPaletteExcluded(i, 1);
    }

    if (a == 0) {
        BgAnimInit(bg, 0xC000, 0);
    } else {
        BgAnimInit(bg, 0x8000, 0x80);
    }

    SetBgBlend(bg, 16, 16);
    gBgFx->update = NULL;
    gBgFx->priority = 0xFF;
    gBgFx->bg = bg;
    BgFxReset();
    gBgFx->flags = 0;
}

void BgFxFree() {
    EwramFree(gBgFx);
}

void BgFxUpdate() {
    if (gBtlWork->flags & BTL_FLAG_STOP_BGFX) {
        gBtlWork->flags &= ~BTL_FLAG_STOP_BGFX;
        gBgFx->flags &= ~BGFX_FLAG_ACTIVE;
        gBgFx->update = NULL;
        BgAnimStop();
        SetBgBlend(gBgFx->bg, 16, 16);
    }

    if (gBgFx->update != NULL) {
        gBgFx->update();

        if (!(gBtlWork->flags & BTL_FLAG_BOSS_BATTLE)) {
            gBtlWork->bossY = gBgFx->y;

            if (gBgFx->flags & BGFX_FLAG_ABOVE_SPRITES) {
                SetBgPriority(gBgFx->bg, 0);
            } else if (gBgFx->flags & BGFX_FLAG_BELOW_SPRITES) {
                SetBgPriority(gBgFx->bg, 1);
                gBtlWork->bossPriorityOffset = 0xFF00;
            } else {
                gBtlWork->bossPriorityOffset = 8;
            }
        }
    }

    BgAnimUpdate();
}

u8 BgFxIsActive() {
    if (gBgFx->flags & BGFX_FLAG_ACTIVE) {
        return 1;
    }

    return 0;
}

void BgFxUpdateBase() {
    s16 sx;
    s16 sy;

    if (BgAnimIsStopped()) {
        SetBgBlend(gBgFx->bg, 16, 16);
        gBgFx->update = NULL;
        gBgFx->flags &= ~BGFX_FLAG_ACTIVE;

        if (gBgFx->flags & BGFX_FLAG_SCREEN_DIMMED) {
            FadeToOriginal(FADE_MODE_BLACK, 8);
        }

        return;
    }

    if (gBtlWork->flags & BTL_FLAG_VS_BATTLE) {
        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            if (gBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE) {
                if (gBtlWork->stockMove < GetStockMoveCount()) {
                    BgFxReleaseEarly(gBgFx->releaseFrames);
                }
            }
        } else if (gRikuBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE) {
            if (gRikuBtlWork->stockMove < GetStockMoveCount()) {
                BgFxReleaseEarly(gBgFx->releaseFrames);
            }
        }
    } else if (gBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE) {
        if (gBtlWork->stockMove < GetStockMoveCount()) {
            BgFxReleaseEarly(gBgFx->releaseFrames);
        }
    }

    WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, gBgFx->z);
    BgAnimSetPosition(sx, sy);

    if (gBgFx->flags & BGFX_FLAG_IGNORE_ZOOM) {
        BgAnimSetTransform(gBgFx->angle + gBtlWork->rotation, gBgFx->scaleX, gBgFx->scaleY);
    } else {
        s32 a = gBgFx->scaleX * gBtlWork->scale >> 8;
        s32 b = gBgFx->scaleY * gBtlWork->scale >> 8;

        BgAnimSetTransform(gBgFx->angle + gBtlWork->rotation, a, b);
    }
}

void BgFxStartCure(u16 a, s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->releaseFrames = 20;
    gBgFx->x = x;
    gBgFx->y = y;

    switch (a) {
    case 0:
        gBgFx->z = z - 0x1400;
        break;
    case 1:
        gBgFx->z = z;
        break;
    case 2:
        gBgFx->z = z - 0x1000;
        break;
    }

    WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, gBgFx->z);

    switch (a) {
    case 0:
        BgAnimStart(&gBgAnimDefCure00, sx, sy);
        m4aSongNumStart(SONG_EF_CAREL00);
        break;
    case 1:
        BgAnimStart(&gBgAnimDefCure01, sx, sy);
        m4aSongNumStart(SONG_EF_CAREL01);
        break;
    case 2:
        BgAnimStart(&gBgAnimDefCure02, sx, sy);
        m4aSongNumStart(SONG_EF_CAREL02);
        break;
    }

    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
    gBgFx->update = BgFxUpdateBase;
}

void BgFxUpdateFadeOut() {
    SetBlendAlpha(16, 16 - gBgFx->timer);

    if (gBgFx->timer > 15) {
        BgAnimStop();
    } else {
        gBgFx->timer++;
    }

    BgFxUpdateBase();
}

void BgFxUpdateFire() {
    u16 a;
    u16 b;
    u16 ang;
    s16 sx;
    s16 sy;
    s32 dx;

    BgAnimGetFrameState(&a, &b);
    dx = 0;

    if (gBgFx->timer > 0) {
        if (a > 7) {
            ang = gBgFx->angle;

            if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
                ApproachAngle(&ang, GetAngle(gBgFx->x, gBgFx->y,
                                             gBgFx->unk_28, gBgFx->unk_2C) + 64, 5);
            } else {
                ApproachAngle(&ang, GetAngle(gBgFx->x, gBgFx->y,
                                             gBgFx->unk_28, gBgFx->unk_2C) - 64, 5);
            }

            gBgFx->angle = ang;
            ApproachValue(&gBgFx->x, gBgFx->unk_28, gBgFx->timer);
            ApproachValue(&gBgFx->y, gBgFx->unk_2C, gBgFx->timer);
            ApproachValue(&gBgFx->z, gBgFx->unk_30, gBgFx->timer);

            if (ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y,
                              gBgFx->z, 8, 8, 16)) {
                gBgFx->timer = -1;
            } else {
                gBgFx->timer--;
            }
        } else if (a > 2) {
            if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
                dx = ((7 - a) << 8) * 7;
            } else {
                s32 t = 7 - a;
                t *= 256;
                dx = t * -7;
            }

            if (ApplyAttackBox(gBgFx->attack, gBgFx->x + dx,
                              gBgFx->y, gBgFx->z, 8, 8, 16)) {
                gBgFx->timer = -1;
            }
        }
    }

    if (gBgFx->timer == 0) {
        gBgFx->update = BgFxUpdateFadeOut;
    } else if (gBgFx->timer == -1) {
        gBgFx->angle = 0;
        gBgFx->scaleX = 0x100;
        gBgFx->scaleY = 0x100;
        gBgFx->x += dx;
        gBgFx->releaseFrames = 20;
        WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y,
                      gBgFx->z);

        switch (gBgFx->state) {
        case 0:
            BgAnimStart(&gBgAnimDefFire01, sx, sy);
            m4aSongNumStart(SONG_EF_FIRE01);
            break;
        case 1:
            BgAnimStart(&gBgAnimDefFire02, sx, sy);
            m4aSongNumStart(SONG_EF_FIRE02);
            break;
        case 2:
            BgAnimStart(&gBgAnimDefFire03, sx, sy);
            m4aSongNumStart(SONG_EF_FIRE03);
            break;
        default:
            BgAnimStart(&gBgAnimDefRikuFire03, sx, sy);
            m4aSongNumStart(SONG_EF_FIRE03);
            break;
        }

        gBgFx->timer = -2;
    }

    BgFxUpdateBase();
}

void BgFxStartFire(u16 a, s32 x, s32 y, s32 z, s32 p, s32 q, s32 r, u8 f, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);

    if (a == 3) {
        BgAnimStart(&gBgAnimDefRikuFire00, sx, sy);
    } else {
        BgAnimStart(&gBgAnimDefFire00, sx, sy);
    }

    if ((gBtlWork->flags & BTL_FLAG_VS_BATTLE) == 0 && (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION)) {
        m4aSongNumStart(SONG_EF_MON_FIRE);
    } else {
        m4aSongNumStart(SONG_EF_FIRE00);
    }

    BgAnimSetLoopStartFrame(8);
    gBgFx->update = BgFxUpdateFire;
    gBgFx->unk_28 = p;
    gBgFx->unk_2C = q;
    gBgFx->unk_30 = r;
    gBgFx->timer = 15;
    gBgFx->state = a;
    gBgFx->attack = w;

    if (f) {
        gBgFx->flags |= BGFX_FLAG_FLIP_X;
        gBgFx->scaleX = -0x100;
    }

    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartFireAtPlayer(s32 x, s32 y, s32 z, u8 f, s32 unused, s32 w, u16 a) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefFire00, sx, sy);
    m4aSongNumStart(SONG_EF_MON_FIRE);
    BgAnimSetLoopStartFrame(8);
    gBgFx->update = BgFxUpdateFire;
    gBgFx->unk_28 = gBtlWork->actor->x;
    gBgFx->unk_2C = gBtlWork->actor->y;
    gBgFx->unk_30 = gBtlWork->actor->z;
    gBgFx->timer = a;
    gBgFx->state = 1;
    gBgFx->attack = w;

    if (f) {
        gBgFx->flags |= BGFX_FLAG_FLIP_X;
        gBgFx->scaleX = -0x180;
    } else {
        gBgFx->scaleX = 0x180;
    }

    gBgFx->scaleY = 0x180;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateBlizzard() {
    u16 a;
    u16 b;
    u16 angle;
    s16 sx;
    s16 sy;
    s32 dx;

    BgAnimGetFrameState(&a, &b);
    dx = 0;

    if (gBgFx->timer > 0) {
        if (a > 7) {
            angle = gBgFx->angle;

            if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
                ApproachAngle(&angle,
                    GetAngle(gBgFx->x, gBgFx->y, gBgFx->unk_28,
                        gBgFx->unk_2C) + 64,
                    5);
            } else {
                ApproachAngle(&angle,
                    GetAngle(gBgFx->x, gBgFx->y, gBgFx->unk_28,
                        gBgFx->unk_2C) - 64,
                    5);
            }

            gBgFx->angle = angle;
            ApproachValue(&gBgFx->x, gBgFx->unk_28, gBgFx->timer);
            ApproachValue(&gBgFx->y, gBgFx->unk_2C, gBgFx->timer);
            ApproachValue(&gBgFx->z, gBgFx->unk_30, gBgFx->timer);

            if (TestAttackBox(gBgFx->x, gBgFx->y, gBgFx->z, 8, 16, 16)) {
                gBgFx->timer = -1;
            } else {
                gBgFx->timer--;
            }
        } else if (a > 2) {
            if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
                dx = ((7 - a) << 8) * 7;
            } else {
                s32 t = 7 - a;
                t *= 256;
                dx = t * -7;
            }

            if (TestAttackBox(gBgFx->x + dx, gBgFx->y, gBgFx->z, 8, 16, 16)) {
                gBgFx->timer = -1;
            }
        }
    }

    if (gBgFx->timer == 0) {
        gBgFx->timer = -1;
    } else if (gBgFx->timer == -1) {
        gBgFx->angle = 0;
        gBgFx->scaleX = 0x100;
        gBgFx->scaleY = 0x100;
        gBgFx->x += dx;
        gBgFx->releaseFrames = 20;
        WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, gBgFx->z);

        switch (gBgFx->state) {
        case 0:
            BgAnimStart(&gBgAnimDefBlizzard01, sx, sy);
            m4aSongNumStart(SONG_EF_BURIZA01);
            break;
        case 1:
            BgAnimStart(&gBgAnimDefBlizzard02, sx, sy);
            m4aSongNumStart(SONG_EF_BURIZA02);
            break;
        case 2:
        default:
            BgAnimStart(&gBgAnimDefBlizzard03, sx, sy);
            m4aSongNumStart(SONG_EF_BURIZA03);
            break;
        }

        gBgFx->timer = -2;
    }

    if (gBgFx->timer == -2) {
        switch (gBgFx->state) {
        case 0:
            if (gBgFx->unk_0A == 20) {
                ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y,
                    gBgFx->z, 18, 18, 18);
            }

            break;
        case 1:
            if (gBgFx->unk_0A == 35) {
                ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y,
                    gBgFx->z, 24, 24, 30);
            }

            break;
        case 2:
        default:
            if (gBgFx->unk_0A == 50) {
                ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y,
                    gBgFx->z, 48, 48, 52);
            }

            break;
        }

        gBgFx->unk_0A++;
    }

    BgFxUpdateBase();
}

void BgFxStartBlizzard(u16 a, s32 x, s32 y, s32 z, s32 p, s32 q, s32 r, u8 f, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefBlizzard00, sx, sy);

    if ((gBtlWork->flags & BTL_FLAG_VS_BATTLE) == 0 && (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION)) {
        m4aSongNumStart(SONG_EF_MON_BURIZA);
    } else {
        m4aSongNumStart(SONG_EF_BURIZA00);
    }

    BgAnimSetLoopStartFrame(8);
    gBgFx->update = BgFxUpdateBlizzard;
    gBgFx->unk_28 = p;
    gBgFx->unk_2C = q;
    gBgFx->unk_30 = r;
    gBgFx->timer = 15;
    gBgFx->state = a;
    gBgFx->attack = w;
    gBgFx->unk_0A = 0;

    if (f) {
        gBgFx->scaleX = -0x100;
        gBgFx->flags |= BGFX_FLAG_FLIP_X;
    }

    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateFlash() {
    gBgFx->scaleX += gBgFx->unk_28;
    gBgFx->scaleY += gBgFx->unk_2C;
    gBgFx->angle += 3;
    BgFxUpdateBase();

    if (gBgFx->timer > 5) {
        s16 t = gBgFx->timer - 5;
        SetBlendAlpha(16, 16 - t);

        if (t > 15) {
            BgAnimStop();
        }
    }

    gBgFx->timer++;
}

void BgFxStartFlash(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(3)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    gBgFx->scaleX = 76;
    gBgFx->scaleY = 76;
    gBgFx->angle = 0;
    gBgFx->unk_28 = 25;
    gBgFx->unk_2C = 25;
    BgAnimStart(&gBgAnimDefFlash, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->update = BgFxUpdateFlash;
    gBgFx->timer = 0;
}

void BgFxUpdateFlashHit() {
    s16 t = gBgFx->timer;

    gBgFx->angle += 4;
    gBgFx->scaleX += gBgFx->unk_28;
    gBgFx->scaleY += gBgFx->unk_2C;
    SetBlendAlpha(16, 16 - t);

    if (t > 15) {
        BgAnimStop();
    }

    gBgFx->timer++;
    BgFxUpdateBase();
}

void BgFxStartFlashHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    gBgFx->scaleX = 256;
    gBgFx->scaleY = 256;
    gBgFx->angle = 0;
    gBgFx->unk_28 = 76;
    gBgFx->unk_2C = 76;
    BgAnimStart(&gBgAnimDefFlash, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->update = BgFxUpdateFlashHit;
    gBgFx->timer = 0;
}

void func_080135EC(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    gBgFx->scaleX = 128;
    gBgFx->scaleY = 128;
    gBgFx->angle = 0;
    BgAnimStart(&gBgAnimDefFlash, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->update = BgFxUpdateFlash;
    gBgFx->timer = 0;
}

void BgFxStartSoraHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(3)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    BgAnimStart(&gBgAnimDefSoraHit, sx, sy);
    gBgFx->update = BgFxUpdateBase;
}

void BgFxStartRikuHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(3)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    BgAnimStart(&gBgAnimDefRikuHit, sx, sy);
    gBgFx->update = BgFxUpdateBase;
}

void BgFxStartLimit(s32 x, s32 y, s32 z, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;

    if (f != 0) {
        gBgFx->scaleX = -0x100;
    }

    WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, gBgFx->z);
    BgAnimStart(&gBgAnimDefLimit, sx, sy);
    gBgFx->update = BgFxUpdateBase;
}

void func_080137C8(s32 x, s32 y, s32 z, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x + 0x400;
    gBgFx->y = y;
    gBgFx->z = z - 0x1000;

    if (f != 0) {
        gBgFx->scaleX = -0x100;
    }

    WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, gBgFx->z);
    BgAnimStart(&gUnk_09EDA660, sx, sy);
    gBgFx->update = BgFxUpdateBase;
}

void BgFxStartEnemyHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    BgAnimStart(&gBgAnimDefEnemyHit, sx, sy);
    gBgFx->update = BgFxUpdateBase;
}

void BgFxStartFireHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z - 0x1000;
    gBgFx->scaleY = 0x200;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    BgAnimStart(&sBgAnimDefFireHit, sx, sy);
    gBgFx->update = BgFxUpdateBase;
}

void BgFxStartBlizzardHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    BgAnimStart(&sBgAnimDefBlizzardHit, sx, sy);
    gBgFx->update = BgFxUpdateBase;
}

void BgFxStartThunderHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    BgAnimStart(&sBgAnimDefThunderHit, sx, sy);
    gBgFx->update = BgFxUpdateBase;
}

void BgFxStartGuard(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefGuard, sx, sy);
    gBgFx->update = BgFxUpdateBase;
}

void BgFxStartPotion(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->releaseFrames = 20;
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z - 0x3000;
    WorldToScreen(&sx, &sy, x, y, z - 0x3000);
    BgAnimStart(&gBgAnimDefPotion, sx, sy);
    m4aSongNumStart(SONG_EF_POSION);
    gBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateWideThunder() {
    s16 sx;
    s16 sy;
    s16 sx2;
    s16 sy2;

    if (gBgFx->timer == 0 && BgAnimIsStopped()) {
        SetBlendAlpha(16, 16);
        gBgFx->x = gBtlWork->viewX;
        gBgFx->y = (gBtlWork->yMin + gBtlWork->yMax) << 7;
        gBgFx->z = gBgFx->unk_30;
        WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, gBgFx->z);
        gBgFx->angle = 0;
        gBgFx->releaseFrames = 20;
        gBgFx->flags |= BGFX_FLAG_IGNORE_ZOOM;
        gBgFx->scaleX = 512;
        gBgFx->scaleY = (sy << 8) / 40;

        if (gBgFx->scaleY < 384) {
            gBgFx->scaleY = 384;
        }

        switch (gBgFx->state) {
        case 0:
            ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 32, 256, 256);
            BgAnimStart(&gBgAnimDefThunder01, sx, sy);
            m4aSongNumStart(SONG_EF_THUND01);
            break;
        case 1:
            ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 256, 256, 256);
            BgAnimStart(&gBgAnimDefThunder02, sx, sy);
            m4aSongNumStart(SONG_EF_THUND02);
            break;
        case 2:
            ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 256, 256, 256);
            BgAnimStart(&gBgAnimDefThunder03, sx, sy);
            m4aSongNumStart(SONG_EF_THUND03);
            break;
        }

        gBgFx->timer = 1;
    } else if (gBgFx->timer == 1) {
        s32 t;

        WorldToScreen(&sx2, &sy2, gBgFx->x, gBgFx->y, gBgFx->z);
        t = sy2 << 8;
        gBgFx->scaleY = t / 40;

        if (gBgFx->scaleY < 384) {
            gBgFx->scaleY = 384;
        }
    }

    BgFxUpdateBase();
}

void BgFxStartWideThunder(u16 a, s32 x, s32 y, s32 z, s32 p, s32 q) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->unk_30 = p;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefThunder00, sx, sy);
    m4aSongNumStart(SONG_EF_THUND00);
    gBgFx->attack = q;
    gBgFx->update = BgFxUpdateWideThunder;
    gBgFx->state = a;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateEnemyDeath() {
    u16 a;
    BgAnimGetFrameState(&a, NULL);

    if (a > 3) {
        gBgFx->scaleX += 12;
        gBgFx->scaleY += 12;
        SetBlendAlpha(gBgFx->timer, 16 - gBgFx->timer);

        if (gBgFx->timer > 15) {
            BgAnimStop();
        } else {
            gBgFx->timer += 2;
        }
    }

    BgFxUpdateBase();
}

void BgFxStartEnemyDeath(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    gBgFx->scaleX = s;
    gBgFx->scaleY = s;
    SetBgBlend(gBgFx->bg, 0, 16);
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefEnemyDeath, sx, sy);
    BgAnimSetLoopStartFrame(4);
    m4aSongNumStart(SONG_EF_MON_DEATH);
    gBgFx->update = BgFxUpdateEnemyDeath;
    gBgFx->unk_2C = 0;
    gBgFx->timer = 0;
}

void BgFxStartDarkDeath(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    gBgFx->scaleX = s;
    gBgFx->scaleY = s;
    SetBgBlend(gBgFx->bg, 0, 16);
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefDarkDeath, sx, sy);
    m4aSongNumStart(SONG_BTL_DARKDEAD);
    gBgFx->update = BgFxUpdateBase;
    gBgFx->unk_2C = 0;
    gBgFx->timer = 0;
}

void BgFxStartEnemySpawn(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    gBgFx->scaleX = s;
    gBgFx->scaleY = s;
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefEnemySpawn, sx, sy);
    gBgFx->update = BgFxUpdateBase;
    gBgFx->unk_2C = 0;
    gBgFx->timer = 0;
}

void BgFxStartDarkDeathBlend(s32 x, s32 y, s32 s, u16 b, u16 c) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    gBgFx->scaleX = s;
    gBgFx->scaleY = s;
    SetBgBlend(gBgFx->bg, b, c);
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = -0x1000;
    WorldToScreen(&sx, &sy, x, y, -0x1000);
    BgAnimStart(&gBgAnimDefDarkDeath, sx, sy);
    m4aSongNumStart(SONG_BTL_DARKDEAD);
    gBgFx->update = BgFxUpdateBase;
    gBgFx->unk_2C = 0;
    gBgFx->timer = 0;
}

void BgFxUpdateExplosion() {
    gBgFx->scaleX += 12;
    gBgFx->scaleY += 12;
    BgFxUpdateBase();
}

void BgFxStartExplosion(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefExplosion, sx, sy);
    gBgFx->update = BgFxUpdateExplosion;
    m4aSongNumStart(SONG_EF_TARU_BOMB);
    gBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxGetPosition(s32* a, s32* b, s32* c) {
    *a = gBgFx->x;
    *b = gBgFx->y;
    *c = gBgFx->z;
}

void BgFxStartSummon(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefSummon, sx, sy);
    gBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartFriendHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    BgAnimStart(&gBgAnimDefFriendHit, sx, sy);
    gBgFx->update = BgFxUpdateBase;
}

void BgFxUpdateFollowActor() {
    BtlObj* p = gBgFx->actor;
    gBgFx->x = p->x;
    gBgFx->y = p->y;
    gBgFx->z = p->z - 0x800;
    BgFxUpdateBase();
}

void BgFxStartActorThunder(BtlObj* p) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->actor = p;
    gBgFx->x = p->x;
    gBgFx->y = p->y;
    gBgFx->z = p->z - 0x800;
    gBgFx->scaleX = 0x133;
    gBgFx->scaleY = 0x133;
    WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, gBgFx->z);
    BgAnimStart(&gBgAnimDefThunder00, sx, sy);
    BgAnimSetLoopStartFrame(4);
    gBgFx->update = BgFxUpdateFollowActor;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void func_08014294() {
    switch (gBgFx->state) {
    case 0:
        if (gBgFx->timer > 30) {
            gBgFx->state = 1;
        } else {
            gBgFx->timer++;
        }

        break;
    case 1:
        gBgFx->unk_3C += 64;
        gBgFx->z += gBgFx->unk_3C;

        if (gBgFx->z > 0) {
            gBgFx->z = 0;
            gBgFx->state = 2;
            gBgFx->timer = 30;
        }

        gBgFx->x += (gBgFx->unk_28 - gBgFx->x) >> 5;
        gBgFx->angle += 4;
        break;
    case 2:
        ApproachValue(&gBgFx->scaleX, 3, gBgFx->timer);
        ApproachValue(&gBgFx->scaleY, 3, gBgFx->timer);
        gBgFx->timer--;

        if (gBgFx->timer <= 0) {
            BgAnimStop();
            gBgFx->update = NULL;
        }

        break;
    }

    ApplyAttackBox(256, gBgFx->x, gBgFx->y, gBgFx->z, 32, 32, 32);
    BgFxUpdateBase();
}

void func_0801435C(s32 x, s32 y, s32 z, s32 w, s32 v) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->unk_28 = w;
    gBgFx->unk_3C = v;
    gBgFx->state = 0;
    gBgFx->scaleX = 0x299;
    gBgFx->scaleY = 0x299;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefThunder00, sx, sy);
    BgAnimSetLoopStartFrame(4);
    gBgFx->update = func_08014294;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateDsdEnergy() {
    switch (gBgFx->state) {
    case 0:
        ApproachValue(&gBgFx->scaleX, gBgFx->unk_28, gBgFx->unk_0A);
        gBgFx->scaleY = gBgFx->scaleX;
        ApproachValue(&gBgFx->unk_3C, 0x1000, gBgFx->unk_0A);
        SetBlendAlpha(16, gBgFx->unk_3C >> 8);
        gBgFx->unk_0A--;

        if (gBgFx->unk_0A <= 0) {
            gBgFx->timer = 0;
            gBgFx->state = 1;
        }

        break;
    case 1:
        if (gBgFx->endSignals != 0) {
            gBgFx->state = 2;
            gBgFx->timer = 0;
            gBgFx->unk_0A = 16;
        }

        break;
    case 2:
        ApproachValue(&gBgFx->unk_3C, 0, gBgFx->unk_0A);
        SetBlendAlpha(16, gBgFx->unk_3C >> 8);
        gBgFx->unk_0A--;

        if (gBgFx->unk_0A <= 0) {
            gBgFx->timer = 0;
            gBgFx->state = 3;
            BgAnimStop();
        }

        break;
    }

    gBgFx->angle += gBgFx->unk_0C;
    BgFxUpdateBase();
}

void func_080144D8(s32 x, s32 y, s32 z, s32 w, u16 a, u16 b) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    SetBlendAlpha(16, 0);
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->state = 0;
    gBgFx->scaleX = w;
    gBgFx->scaleY = w;
    gBgFx->unk_28 = w;
    gBgFx->unk_3C = 0;
    gBgFx->endSignals = 0;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&sUnk_09EDAAE0, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->update = BgFxUpdateDsdEnergy;
    gBgFx->unk_0A = a;
    gBgFx->unk_0C = b;
}

void BgFxStartDsdEnergy(s32 x, s32 y, s32 z, s32 w, s32 paramA, s32 paramB) {
    u16 a = paramA;
    u16 b = paramB;
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    SetBlendAlpha(16, 0);
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->state = 0;
    gBgFx->scaleX = w;
    gBgFx->scaleY = w;
    gBgFx->unk_28 = w;
    gBgFx->unk_3C = 0;
    gBgFx->endSignals = 0;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&sUnk_09EDAA38, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->update = BgFxUpdateDsdEnergy;
    gBgFx->unk_0A = a;
    gBgFx->unk_0C = b;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void func_08014654() {
    u16 t;
    s16 u;
    gBgFx->scaleX += 25;
    gBgFx->scaleY += 25;
    BgFxUpdateBase();
    t = gBgFx->timer;

    if (gBgFx->timer > 3) {
        u = t - 3;
        SetBlendAlpha(16, 16 - u);

        if (u > 15) {
            BgAnimStop();
        }
    }

    gBgFx->timer++;
}

void func_080146A8(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, 0);
    gBgFx->scaleX = 512;
    gBgFx->scaleY = 768;
    gBgFx->angle = 0;
    BgAnimStart(&gBgAnimDefFlash, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->update = func_08014654;
    gBgFx->timer = 0;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxAddPosition(s32 a, s32 b, s32 c) {
    gBgFx->x += a;
    gBgFx->y += b;
    gBgFx->z += c;
}

void BgFxSetPosition(s32 a, s32 b, s32 c) {
    gBgFx->x = a;
    gBgFx->y = b;
    gBgFx->z = c;
}

void BgFxSignalEnd(u8 bit) {
    gBgFx->endSignals |= 1 << bit;
}

void BgFxSetTarget(s32 a, s32 b, s32 c) {
    gBgFx->unk_28 = a;
    gBgFx->unk_2C = b;
    gBgFx->unk_30 = c;
}

void BgFxSetAngle(u8 a) {
    gBgFx->angle = a;
}

void BgFxSetScale(s32 a, s32 b) {
    gBgFx->scaleX = a;
    gBgFx->scaleY = b;
}

void BgFxStartGroundImpact(s32 x, s32 y) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    SetBgBlend(gBgFx->bg, 5, 16);
    gBgFx->x = x;
    gBgFx->y = y;
    WorldToScreen(&sx, &sy, x, y, 0);
    BgAnimStart(&gBgAnimDefGroundImpact, sx, sy);
    gBgFx->update = BgFxUpdateBase;
    gBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxUpdateStop() {
    switch (gBgFx->state) {
    case 0:
#ifdef VERSION_EU
        if (gBgFx->timer == 20) {
#else
        if (gBgFx->timer == 21) {
#endif
            ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 16, 16, 48);
        }

        break;
    case 1:
#ifdef VERSION_EU
        if (gBgFx->timer == 20) {
#else
        if (gBgFx->timer == 25) {
#endif
            ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 24, 24, 48);
        }

        break;
    case 2:
        if (gBgFx->timer == 33) {
            ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 32, 32, 48);
        }

        break;
    }

    gBgFx->timer++;
    BgFxUpdateBase();
}

void BgFxStartStop(u16 a, s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->releaseFrames = 20;
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->attack = w;
    gBgFx->state = a;
    WorldToScreen(&sx, &sy, x, y, 0);

    switch (a) {
    case 0:
        BgAnimStart(&gBgAnimDefStop00, sx, sy);
        m4aSongNumStart(SONG_EF_STOP00);
        break;
    case 1:
        BgAnimStart(&gBgAnimDefStop01, sx, sy);
        m4aSongNumStart(SONG_EF_STOP01);
        break;
    case 2:
    default:
        BgAnimStart(&gBgAnimDefStop02, sx, sy);
        m4aSongNumStart(SONG_EF_STOP02);
        break;
    }

    gBgFx->update = BgFxUpdateStop;
}

void BgFxStartCharaDefeat(s32 x, s32 y) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    WorldToScreen(&sx, &sy, x, y, 0);
    BgAnimStart(&gBgAnimDefCharaDefeat, sx, sy);
    BgAnimSetLoopStartFrame(8);
    gBgFx->update = BgFxUpdateBase;
    gBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxStartHumDefeat(s32 x, s32 y) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    WorldToScreen(&sx, &sy, x, y, 0);
    BgAnimStart(&gBgAnimDefHumDefeat, sx, sy);
    BgAnimSetLoopStartFrame(7);
    gBgFx->update = BgFxUpdateBase;
    gBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxStartBossDeath(s32 x, s32 y) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    WorldToScreen(&sx, &sy, x, y, 0);
    m4aSongNumStart(SONG_BTL_GF_LOOP);
    BgAnimStart(&gBgAnimDefBossDeath, sx, sy);
    BgAnimSetLoopStartFrame(4);
    gBgFx->update = BgFxUpdateBase;
    gBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxStartCharaDefeatEnd(s32 x, s32 y) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    WorldToScreen(&sx, &sy, x, y, 0);
    BgAnimStart(&gBgAnimDefCharaDefeatEnd, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->update = BgFxUpdateBase;
    gBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxUpdateGravity() {
    s16 sx;
    s16 sy;
    s16 t;
    u8 r;

    t = gBgFx->timer % 8;

    if (t <= 3) {
        SetBlendAlpha(t, 16);
    } else {
        SetBlendAlpha(8 - t, 16);
    }

    if (gBgFx->unk_0A == 0 && BgAnimIsStopped()) {
        gBgFx->x = gBgFx->unk_28;
        gBgFx->y = gBgFx->unk_2C;
        gBgFx->z = gBgFx->unk_30;
        WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->x, gBgFx->z);
        gBgFx->angle = 0;
        gBgFx->releaseFrames = 20;

        switch (gBgFx->state) {
        case 0:
            gBgFx->unk_28 = 128;
            gBgFx->unk_2C = 128;
            BgAnimStart(&gBgAnimDefGravity01, sx, sy);
            break;
        case 1:
            gBgFx->unk_28 = 256;
            gBgFx->unk_2C = 256;
            BgAnimStart(&gBgAnimDefGravity01, sx, sy);
            break;
        case 2:
        default:
            gBgFx->unk_28 = 512;
            gBgFx->unk_2C = 512;
            BgAnimStart(&gBgAnimDefGravity01, sx, sy);
            break;
        }

        if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
            gBgFx->unk_28 = -gBgFx->unk_28;
        }

        m4aSongNumStart(SONG_EF_GRABI01);
        gBgFx->unk_0A++;
    } else if (gBgFx->unk_0A == 1) {
        if (gBgFx->timer <= 29) {
            ApproachValue(&gBgFx->scaleX, gBgFx->unk_28, 30 - gBgFx->timer);
            ApproachValue(&gBgFx->scaleY, gBgFx->unk_2C, 30 - gBgFx->timer);
        }

        if (gBgFx->timer == 35) {
            switch (gBgFx->state) {
            case 0:
                r = ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 24, 12, 256);
                break;
            case 1:
                r = ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 40, 20, 256);
                break;
            case 2:
            default:
                r = ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 80, 40, 256);
                break;
            }

            if (r) {
                m4aSongNumStart(SONG_EF_GRABI02);
            }
        }

        gBgFx->timer++;
    }

    BgFxUpdateBase();
}

void BgFxStartGravity(u16 a, s32 x, s32 y, s32 z, s32 p, s32 q, s32 r, u8 f, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    SetBlendAlpha(2, 16);
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->unk_28 = p;
    gBgFx->unk_2C = q;
    gBgFx->unk_30 = r;
    gBgFx->attack = w;

    if (f != 0) {
        gBgFx->scaleX = -gBgFx->scaleX;
        gBgFx->flags |= BGFX_FLAG_FLIP_X;
    }

    gBgFx->unk_0A = 0;
    WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, gBgFx->z);
    BgAnimStart(&gBgAnimDefGravity00, sx, sy);
    m4aSongNumStart(SONG_EF_GRABI00);
    gBgFx->state = a;
    gBgFx->update = BgFxUpdateGravity;
}

void BgFxUpdateGravityStrike() {
    s16 t = gBgFx->timer % 8;

    if (t <= 3) {
        SetBlendAlpha(t, 16);
    } else {
        SetBlendAlpha(8 - t, 16);
    }

    if (gBgFx->timer == 0x23) {
        if (ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 40, 20, 256)) {
            m4aSongNumStart(SONG_EF_GRABI02);
        }
    }

    BgFxUpdateBase();
    gBgFx->timer++;
}

void BgFxStartGravityStrike(s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    SetBlendAlpha(2, 16);
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->attack = w;
    gBgFx->unk_0A = 0;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefGravity01, sx, sy);
    m4aSongNumStart(SONG_EF_GRABI01);
    gBgFx->update = BgFxUpdateGravityStrike;
}

void BgFxUpdateShockwave() {
    gBgFx->scaleX += 0x80;
    gBgFx->scaleY += 0x80;
    gBgFx->angle += 3;

    if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
        gBgFx->x += -0x300;
    } else {
        gBgFx->x += 0x300;
    }

    BgFxUpdateBase();
    SetBlendAlpha(16, 8 - gBgFx->unk_0A);

    if (gBgFx->unk_0A > 7) {
        BgAnimStop();
    }

    if (gBgFx->timer % 5 == 0) {
        gBgFx->unk_0A++;
    }

    gBgFx->timer++;
}

void BgFxStartShockwave(s32 x, s32 y, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y - 0x1000;
    SetBlendAlpha(16, 8);

    if (f) {
        gBgFx->flags |= BGFX_FLAG_FLIP_X;
    }

    WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, 0);
    gBgFx->scaleX = 128;
    gBgFx->scaleY = 128;
    gBgFx->angle = 0;
    gBgFx->unk_0A = 0;
    BgAnimStart(&gBgAnimDefFlash, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->update = BgFxUpdateShockwave;
    gBgFx->timer = 0;
    gBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxUpdateGas() {
    if (gBgFx->timer > 19) {
        gBgFx->unk_0A = (gBgFx->timer - 20) / 2;
        SetBlendAlpha(16, 16 - gBgFx->unk_0A);

        if (gBgFx->unk_0A > 15) {
            BgAnimStop();
        }
    }

    gBgFx->timer++;
    BgFxUpdateBase();
}

void BgFxStartGas(s32 x, s32 y, s32 z, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    SetBlendAlpha(16, 16);
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->scaleX = 0x100;
    gBgFx->scaleY = 0x100;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefGas, sx, sy);
    gBgFx->update = BgFxUpdateGas;
    m4aSongNumStart(SONG_EF_BFG_GASS);

    if (f == 0) {
        gBgFx->flags |= BGFX_FLAG_FLIP_X;
    }

    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
    BgAnimSetLoopStartFrame(3);
}

void BgFxUpdateFadeInOut() {
    switch (gBgFx->state) {
    case 0:
        SetBlendAlpha(16, gBgFx->timer);

        if (gBgFx->timer > 15) {
            gBgFx->timer = 0;
            gBgFx->state = 1;
        } else {
            gBgFx->timer++;
        }

        break;
    case 1:
        if (gBgFx->timer > gBgFx->unk_0A) {
            gBgFx->timer = 0;
            gBgFx->state = 2;
        } else {
            gBgFx->timer++;
        }

        break;
    case 2:
        SetBlendAlpha(16, 16 - gBgFx->timer);

        if (gBgFx->timer > 15) {
            BgAnimStop();
        } else {
            gBgFx->timer++;
        }

        break;
    }

    BgFxUpdateBase();
}

void BgFxStartBoogieKaihuku(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    SetBlendAlpha(16, 0);
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    gBgFx->scaleX = s;
    gBgFx->scaleY = s;
    gBgFx->state = 0;
    gBgFx->unk_0A = 30;
    BgAnimStart(&gBgAnimDefBoogieKaihuku, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->update = BgFxUpdateFadeInOut;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateBossDeathFlash() {
    switch (gBgFx->state) {
    case 0:
        if (gBgFx->timer > 30) {
            FadeStartOut(FADE_MODE_ADD_WHITE, 60);
            FadeLock();
            gBgFx->timer = 0;
            gBgFx->state = 1;
        } else {
            gBgFx->timer++;
        }

        break;
    case 1:
        if (FadeIsActive() == 0) {
            BgAnimStop();
            FadeStartIn(FADE_MODE_ADD_WHITE, 120);
            FadeLock();
            gBgFx->update = NULL;
            gBgFx->flags &= ~BGFX_FLAG_ACTIVE;
        }

        break;
    }

    BgAnimSetTransform(0, gBgFx->scaleX, gBgFx->scaleY);
    gBgFx->scaleX += 20;
    gBgFx->scaleY += 20;
}

void BgFxStartBossDeathFlash() {
    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->state = 0;
    gBgFx->scaleX = 0x19;
    gBgFx->scaleY = 0x19;
    BgAnimStart(&gUnk_09EDAA20, 0x78, 0x50);
    BgAnimSetLoopStartFrame(0);
    m4aSongNumStart(SONG_EF_DBOSS_DEAD);
    gBgFx->update = BgFxUpdateBossDeathFlash;
    gBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxUpdatePcShot() {
    s16 t;
    s16 u;

    switch (gBgFx->state) {
    case 0:
        t = gBgFx->timer;
        SetBlendAlpha(16, t);
        ApproachValueHalfSteps(&gBgFx->scaleX, 0x100, 17 - t);
        gBgFx->scaleY = gBgFx->scaleX;

        if (t > 15) {
            gBgFx->timer = gBgFx->unk_0A;
            gBgFx->state = 1;
        } else {
            gBgFx->timer++;
        }

        break;
    case 1:
        ApproachValue(&gBgFx->x, gBgFx->unk_28, gBgFx->timer);
        ApproachValue(&gBgFx->y, gBgFx->unk_2C, gBgFx->timer);
        ApproachValue(&gBgFx->z, gBgFx->unk_30, gBgFx->timer);
        ApproachValue(&gBgFx->scaleX, gBgFx->unk_3C, gBgFx->timer);
        gBgFx->scaleY = gBgFx->scaleX;
        u = (gBgFx->scaleX * 3) >> 6;

        if (gBgFx->timer <= 0) {
            gBgFx->timer = 0;
            gBgFx->state = 2;
        } else if (ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, u, u, u)) {
            m4aSongNumStart(SONG_BTL_AN_WAVEHIT);
            gBgFx->timer = 0;
            gBgFx->state = 2;
        } else {
            gBgFx->timer--;
        }

        break;
    case 2:
        t = gBgFx->timer;
        SetBlendAlpha(16, 16 - t);

        if (t > 15) {
            BgAnimStop();
        } else {
            gBgFx->scaleX += 7;
            gBgFx->scaleY += 7;
            gBgFx->z -= gBgFx->scaleX;
            gBgFx->timer++;
        }

        break;
    }

    BgFxUpdateBase();
}

void BgFxStartPcShot(s32 x, s32 y, s32 z, s32 p, s32 q, s32 r, s32 s, u16 a, s32 t) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    SetBlendAlpha(16, 0);
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->unk_28 = p;
    gBgFx->unk_2C = q;
    gBgFx->unk_30 = r;
    gBgFx->unk_0A = a;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefPcShot, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->scaleX = 25;
    gBgFx->scaleY = 25;
    gBgFx->update = BgFxUpdatePcShot;
    gBgFx->state = 0;
    gBgFx->attack = s;
    gBgFx->unk_3C = t;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartThunderStrike(s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;
    s32 t;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    t = sy << 8;
    gBgFx->scaleX = 384;
    gBgFx->scaleY = t / 40;

    if (gBgFx->scaleY < 384) {
        gBgFx->scaleY = 384;
    }

    BgAnimStart(&gBgAnimDefThunder01, sx, sy);
    m4aSongNumStart(SONG_EF_THUND01);
    ApplyAttackBox(w, gBgFx->x, gBgFx->y, gBgFx->z, 16, 16, 256);
    gBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateThunder() {
    s16 sx;
    s16 sy;
    s16 sx2;
    s16 sy2;

    if (gBgFx->timer == 0 && BgAnimIsStopped()) {
        SetBlendAlpha(16, 16);
        gBgFx->x = gBgFx->unk_28;
        gBgFx->y = gBgFx->unk_2C;
        gBgFx->z = gBgFx->unk_30;
        WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, gBgFx->z);
        gBgFx->angle = 0;
        gBgFx->scaleX = 384;
        gBgFx->scaleY = (sy << 8) / 40;

        if (gBgFx->scaleY < 384) {
            gBgFx->scaleY = 384;
        }

        gBgFx->flags |= BGFX_FLAG_IGNORE_ZOOM;

        switch (gBgFx->state) {
        case 0:
            ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 16, 16, 256);
            BgAnimStart(&gBgAnimDefThunder01, sx, sy);
            m4aSongNumStart(SONG_EF_THUND01);
            break;
        case 1:
            ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 40, 40, 256);
            BgAnimStart(&gBgAnimDefThunder02, sx, sy);
            m4aSongNumStart(SONG_EF_THUND02);
            break;
        case 2:
            ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 64, 64, 256);
            BgAnimStart(&gBgAnimDefThunder03, sx, sy);
            m4aSongNumStart(SONG_EF_THUND03);
            break;
        }

        gBgFx->timer = 1;
    } else if (gBgFx->timer == 1) {
        s32 t;

        WorldToScreen(&sx2, &sy2, gBgFx->x, gBgFx->y, gBgFx->z);
        t = sy2 << 8;
        gBgFx->scaleY = t / 40;

        if (gBgFx->scaleY < 384) {
            gBgFx->scaleY = 384;
        }
    }

    BgFxUpdateBase();
}

void BgFxStartThunder(u16 a, s32 x, s32 y, s32 z, s32 p, s32 q, s32 r, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->unk_28 = p;
    gBgFx->unk_2C = q;
    gBgFx->unk_30 = r;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefThunder00, sx, sy);
    m4aSongNumStart(SONG_EF_THUND00);
    gBgFx->attack = s;
    gBgFx->update = BgFxUpdateThunder;
    gBgFx->state = a;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateDumboSplash() {
    s32 t;
    u16 v;

    switch (gBgFx->state) {
    case 0:
        if (gBgFx->timer == 0) {
            gBgFx->unk_0A = 40;
        }

        ApproachValue(&gBgFx->unk_3C, 0x1000, gBgFx->unk_0A);
        ApproachValue(&gBgFx->scaleX, gBgFx->unk_28, gBgFx->unk_0A);
        ApproachValue(&gBgFx->scaleY, 0x100, gBgFx->unk_0A);
        ApproachValue(&gBgFx->unk_40, 0, gBgFx->unk_0A);
        gBgFx->angle = gBgFx->unk_40 >> 8;
        t = gBgFx->scaleX;

        if (t < 0) {
            t = -t;
        }

        t *= 44;

        if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
            ApplyAttackBox(gBgFx->attack, gBgFx->x + t, gBgFx->y,
                gBgFx->z, t << 8 >> 16, 24, 24);
        } else {
            ApplyAttackBox(gBgFx->attack, gBgFx->x - t, gBgFx->y,
                gBgFx->z, t << 8 >> 16, 24, 24);
        }

        SetBlendAlpha(16, gBgFx->unk_3C >> 8);

        if (--gBgFx->unk_0A <= 0) {
            gBgFx->timer = 0;
            gBgFx->state = 1;
        } else {
            gBgFx->timer++;
        }

        break;
    case 1:
        v = gBgFx->timer;

        if (gBgFx->timer > 50) {
            gBgFx->timer = 0;
            gBgFx->state = 2;
            break;
        }

        t = gBgFx->scaleX;

        if (t < 0) {
            t = -t;
        }

        t *= 44;

        if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
            gBgFx->unk_40 = -gSineTable[(v * 4) & 0xFF] * 6;
            ApplyAttackBox(gBgFx->attack, gBgFx->x + t, gBgFx->y,
                gBgFx->z, t << 8 >> 16, 24, 24);
        } else {
            gBgFx->unk_40 = gSineTable[(v * 4) & 0xFF] * 6;
            ApplyAttackBox(gBgFx->attack, gBgFx->x - t, gBgFx->y,
                gBgFx->z, t << 8 >> 16, 24, 24);
        }

        gBgFx->angle = gBgFx->unk_40 >> 8;
        gBgFx->timer++;
        break;
    case 2:
        if (gBgFx->timer == 0) {
            gBgFx->unk_0A = 20;
        }

        ApproachValue(&gBgFx->unk_3C, 0, gBgFx->unk_0A);
        ApproachValue(&gBgFx->scaleY, 128, gBgFx->unk_0A);

        if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
            ApproachValue(&gBgFx->scaleX, -128, gBgFx->unk_0A);
            ApproachValue(&gBgFx->unk_40, 0x800, gBgFx->unk_0A);
        } else {
            ApproachValue(&gBgFx->scaleX, 128, gBgFx->unk_0A);
            ApproachValue(&gBgFx->unk_40, -0x800, gBgFx->unk_0A);
        }

        gBgFx->angle = gBgFx->unk_40 >> 8;
        SetBlendAlpha(16, gBgFx->unk_3C >> 8);

        if (--gBgFx->unk_0A <= 0) {
            BgAnimStop();
            gBgFx->state = 99;
        } else {
            gBgFx->timer++;
        }

        break;
    }

    BgFxUpdateBase();
}

void BgFxStartDumboSplash(u16 a, s32 x, s32 y, s32 z, u8 f, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    SetBlendAlpha(16, 0);

    if (f) {
        gBgFx->flags |= BGFX_FLAG_FLIP_X;
    }

    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->attack = w;
    WorldToScreen(&sx, &sy, x, y, z);
    gBgFx->scaleY = 25;

    switch (a) {
    case 0:
        gBgFx->unk_28 = 256;
        break;
    case 1:
        gBgFx->unk_28 = 384;
        break;
    case 2:
        gBgFx->unk_28 = 512;
        break;
    }

    if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
        gBgFx->scaleX = -25;
        gBgFx->unk_40 = 2048;
        gBgFx->unk_28 = -gBgFx->unk_28;
    } else {
        gBgFx->scaleX = 25;
        gBgFx->unk_40 = -2048;
    }

    gBgFx->state = 0;
    gBgFx->unk_3C = 0;
    BgAnimStart(&gBgAnimDefDumboSplash, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->update = BgFxUpdateDumboSplash;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void func_08015C80(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    gBgFx->scaleX = 76;
    gBgFx->scaleY = 76;
    gBgFx->unk_28 = 12;
    gBgFx->unk_2C = 12;
    BgAnimStart(&gBgAnimDefFlash, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->update = BgFxUpdateFlash;
}

void BgFxUpdateTrinityLimit() {
    if (gBgFx->timer <= 16) {
        SetBlendAlpha(16, gBgFx->timer);
        gBgFx->timer++;
    }

    BgFxUpdateBase();
}

void BgFxStartTrinityLimit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->scaleX = 0x100;
    gBgFx->scaleY = 0x100;
    WorldToScreen(&sx, &sy, x, y, z);
    gBgFx->flags |= BGFX_FLAG_BELOW_SPRITES;
    SetBlendAlpha(16, 0);
    gBgFx->state = 0;
    BgAnimStart(&gBgAnimDefTrinityLimit, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->update = BgFxUpdateTrinityLimit;
}

void BgFxStartTrinityLimitCharge(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    gBgFx->scaleX = 0x200;
    gBgFx->scaleY = 0x200;
    BgAnimSetLoopStartFrame(7);
    BgAnimStart(&gBgAnimDefTrinityLimitCharge, sx, sy);
    gBgFx->update = BgFxUpdateBase;
}

void BgFxUpdateTrinityLimitBlast() {
    switch (gBgFx->state) {
    case 0: {
        s16 t = gBgFx->timer;

        if (t <= 64) {
            SetBlendAlpha(16, t >> 2);
            gBgFx->timer++;
        } else {
            gBgFx->timer = 0;
            gBgFx->state++;
        }

        gBgFx->scaleX += 25;
        gBgFx->scaleY += 25;
        break;
    }
    case 1: {
        u16 t;

        gBgFx->scaleX += 0x100;
        gBgFx->scaleY += 0x100;
        t = gBgFx->timer;

        if ((s16)t > 32) {
            ApplyAttackBox(87, gBgFx->x, gBgFx->y, 0, 0x100, 0x100, 0x100);
            SetBattleZoom(1, 0x100, gBtlWork->x2, gBtlWork->y2);
            FadeStartIn(FADE_MODE_ADD_WHITE, 60);
            gBgFx->timer = 0;
            gBgFx->state++;
        } else {
            gBgFx->timer = t + 1;
        }

        break;
    }
    case 2: {
        u16 t = gBgFx->timer;

        if ((s16)t <= 15) {
            SetBlendAlpha(16, 16 - t);
            gBgFx->timer++;
        } else {
            BgAnimStop();
        }

        break;
    }
    }

    gBgFx->angle++;
    BgFxUpdateBase();
}

void BgFxStartTrinityLimitBlast(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    SetBlendAlpha(16, 0);
    WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, gBgFx->z);
    gBgFx->scaleX = 0x300;
    gBgFx->scaleY = 0x300;
    BgAnimStart(&gBgAnimDefTrinityLimitBlast, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->timer = 8;
    gBgFx->state = 0;
    gBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
    gBgFx->update = BgFxUpdateTrinityLimitBlast;
    FadeStartOut(FADE_MODE_ADD_WHITE, 40);
    SetBattleZoom(80, 204, x, y + z + 0x2000);
}

void BgFxUpdateRagnarokCharge() {
    if (gBgFx->timer > 0) {
        ApproachValueHalfSteps(&gBgFx->scaleX, 0x100, gBgFx->timer);
        ApproachValueHalfSteps(&gBgFx->scaleY, 0x100, gBgFx->timer);
        gBgFx->timer--;
    }

    BgFxUpdateBase();
}

void BgFxStartRagnarokCharge(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    gBgFx->scaleX = 0x19;
    gBgFx->scaleY = 0x19;
    m4aSongNumStart(SONG_EF_RAGNA01);
    BgAnimStart(&gBgAnimDefRagnarokCharge, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->timer = 0x23;
    gBgFx->update = BgFxUpdateRagnarokCharge;
}

void BgFxUpdateRagnarokShot() {
    u16 k;
    u16 v;
    s16 t;

    BgAnimGetFrameState(&k, &v);

    switch (k) {
    case 4:
        ApplyAttackBox(91, gBgFx->x + gBgFx->scaleX * 40, gBgFx->y, gBgFx->z, 32, 32, 50);
        break;
    case 5:
        if (v == 0) {
            gBgFx->state = 1;
        }

        break;
    case 6:
        if (v == 0) {
            gBgFx->state = 2;
        }

        break;
    }

    switch (gBgFx->state) {
    case 1:
        gBgFx->unk_3C += 51;

        if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
            gBgFx->x -= gBgFx->unk_3C;
        } else {
            gBgFx->x += gBgFx->unk_3C;
        }

        break;
    case 2:
        gBgFx->unk_3C += 51;

        if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
            gBgFx->x -= gBgFx->unk_3C;
            gBgFx->scaleX -= 51;
        } else {
            gBgFx->x += gBgFx->unk_3C;
            gBgFx->scaleX += 51;
        }

        ApplyAttackBox(91, gBgFx->x + gBgFx->scaleX * 40, gBgFx->y, gBgFx->z, 32, 32, 50);

        if (gBgFx->timer > 20) {
            t = 36 - gBgFx->timer;
            SetBlendAlpha(16, t);

            if (t <= 0) {
                BgAnimStop();
            }
        }

        gBgFx->timer++;
        break;
    }

    BgFxUpdateBase();
}

void BgFxStartRagnarokShot(s32 x, s32 y, s32 z, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    gBgFx->state = 0;

    if (f) {
        gBgFx->flags |= BGFX_FLAG_FLIP_X;
        gBgFx->scaleX = -0x100;
    }

    gBgFx->unk_3C = 0;
    m4aSongNumStart(SONG_EF_RAGNA02);
    BgAnimStart(&gBgAnimDefRagnarokShot, sx, sy);
    BgAnimSetLoopStartFrame(6);
    gBgFx->update = BgFxUpdateRagnarokShot;
}

void func_080162A8(s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gUnk_09EDAA20, sx, sy);
    gBgFx->scaleX = w;
    gBgFx->scaleY = w;
    gBgFx->update = BgFxUpdateFadeOut;
}

BtlObj* BgFxGetSyncTarget() {
    if (gBtlWork->flags & BTL_FLAG_VS_BATTLE) {
        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            return gBtlWork->actor;
        }

        return gRikuBtlWork->actor;
    }

    if (gBtlWork->actor2 != NULL) {
        return gBtlWork->actor2;
    }

    return ListPoolFirst(&gBtlWork->pool);
}

void BgFxApplySyncHp(s16 a) {
    BtlObj* o;

    if (gBtlWork->flags & BTL_FLAG_VS_BATTLE) {
        if (GetRandom() % 5) {
            if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
                CreateBtlPopTask(gBtlWork->actor, 2);
            } else {
                CreateBtlPopTask(gRikuBtlWork->actor, 2);
            }
        } else {
            o = gRikuBtlWork->actor;
            o->hp = a;

            if (a > o->maxHp) {
                o->hp = o->maxHp;
            }

            o = gBtlWork->actor;
            o->hp = a;

            if (a > o->maxHp) {
                o->hp = o->maxHp;
            }
        }
    } else {
        o = ListPoolFirst(&gBtlWork->pool);

        while (o != NULL) {
            if (o->flags & BTLOBJ_FLAG_BOSS) {
                CreateBtlPopTask(o, 0);
            } else {
                o->hp = a;

                if (a > o->maxHp) {
                    o->hp = o->maxHp;
                }
            }

            o = ListPoolNext(&o->node);
        }
    }
}

void BgFxUpdateSync() {
    BtlObj* o;

    switch (gBgFx->state) {
    case 0:
        gBgFx->scaleX = (gSineTable[((u16)gBgFx->timer * 4) & 0xFF] >> 3) + 89;

        if (gBgFx->unk_0A > 0) {
            ApproachValueHalfSteps(&gBgFx->z, gBgFx->unk_30 - 0x2000, gBgFx->unk_0A);
            gBgFx->unk_0A--;
        } else {
            gBgFx->state = 1;
            gBgFx->unk_0A = 60;
        }

        break;
    case 1:
        gBgFx->scaleX = (gSineTable[((u16)gBgFx->timer * 4) & 0xFF] >> 3) + 89;
        gBgFx->unk_0A--;

        if (gBgFx->unk_0A <= 0) {
            gBgFx->state = 2;
            gBgFx->unk_0A = 50;
        }

        break;
    case 2:
        gBgFx->scaleX = (gSineTable[((u16)gBgFx->timer * 4) & 0xFF] >> 3) + 89;
        o = BgFxGetSyncTarget();

        if (o != NULL) {
            ApproachValueHalfSteps(&gBgFx->x, o->x, gBgFx->unk_0A);
            ApproachValueHalfSteps(&gBgFx->y, o->y, gBgFx->unk_0A);
            ApproachValueHalfSteps(&gBgFx->z, o->z - (o->centerHeight << 8), gBgFx->unk_0A);
        }

        gBgFx->unk_0A--;

        if (o != NULL) {
            if (gBgFx->unk_0A > 0) {
                break;
            }

            BgFxApplySyncHp(o->hp);
        }

        gBgFx->state = 3;
        m4aSongNumStart(SONG_EF_SYNC2);
        gBgFx->unk_0A = 16;
        break;
    case 3:
        gBgFx->scaleX += 166;
        gBgFx->scaleY = gBgFx->scaleX;
        SetBlendAlpha(16, gBgFx->unk_0A);
        gBgFx->unk_0A--;

        if (gBgFx->unk_0A <= 0) {
            BgAnimStop();
        }

        break;
    }

    gBgFx->scaleY = gBgFx->scaleX;
    gBgFx->timer++;
    BgFxUpdateBase();
}

void BgFxStartSync(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->unk_30 = z;
    gBgFx->state = 0;
    gBgFx->unk_0A = 50;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gUnk_09EDAA20, sx, sy);
    gBgFx->scaleX = 89;
    gBgFx->scaleY = 89;
    gBgFx->update = BgFxUpdateSync;
    m4aSongNumStart(SONG_EF_SYNC1);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartStunImpact(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefStunImpact, sx, sy);
    gBgFx->scaleX = 0x200;
    gBgFx->scaleY = 0x200;
    gBgFx->update = BgFxUpdateBase;
}

void BgFxUpdateZantetsuken() {
    gBgFx->scaleX += gBgFx->unk_28;
    gBgFx->scaleY += gBgFx->unk_2C;
    BgFxUpdateBase();

    if (gBgFx->timer > 5) {
        s16 t = gBgFx->timer - 5;
        SetBlendAlpha(16, 16 - t);

        if (t > 15) {
            BgAnimStop();
        }
    }

    gBgFx->timer++;
}

void BgFxStartZantetsuken(s32 x, s32 y, s32 z, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gUnk_09EDAA20, sx, sy);
    gBgFx->scaleX = 38;
    gBgFx->scaleY = 256;
    gBgFx->unk_28 = 7;
    gBgFx->unk_2C = 153;

    if (f) {
        gBgFx->angle += 40;
    } else {
        gBgFx->angle -= 40;
    }

    gBgFx->update = BgFxUpdateZantetsuken;
}

void BgFxUpdateUrsulaBeam() {
    switch (gBgFx->state) {
    case 0:
        SetBlendAlpha(16, (gBgFx->timer >> 1) + 8);
        ApproachValueHalfSteps(&gBgFx->scaleX, gBgFx->unk_28, 17 - gBgFx->timer);
        ApproachValueHalfSteps(&gBgFx->scaleY, gBgFx->unk_2C, 17 - gBgFx->timer);

        if (gBgFx->timer > 15) {
            gBgFx->timer = 0;
            gBgFx->state = 1;
        } else {
            gBgFx->timer++;
        }

        break;
    case 1:
        if (gBgFx->timer > gBgFx->unk_0A) {
            gBgFx->timer = 0;
            gBgFx->state = 2;
        } else {
            gBgFx->timer++;
        }

        break;
    case 2:
        SetBlendAlpha(16, 16 - gBgFx->timer);

        if (gBgFx->timer > 15) {
            BgAnimStop();
        } else {
            gBgFx->timer++;
        }

        break;
    }

    BgFxUpdateBase();
}

void BgFxStartUrsulaBeam(s32 x, s32 y, s32 z, u8 f, s32 w, u16 a) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->unk_0A = a;
    gBgFx->state = 0;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefUrsulaBeam, sx, sy);

    if (f) {
        gBgFx->unk_28 = w;
        gBgFx->scaleX = 76;
    } else {
        gBgFx->unk_28 = -w;
        gBgFx->scaleX = -76;
    }

    gBgFx->unk_2C = w;
    gBgFx->scaleY = 76;
    m4aSongNumStart(SONG_EF_UR_BEEM);
    gBgFx->update = BgFxUpdateUrsulaBeam;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void func_080169A0(s32 x, s32 y, s32 z, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->state = 0;
    gBgFx->unk_0A = 45;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gUnk_09EDAB40, sx, sy);

    if (f) {
        gBgFx->scaleX = -0x100;
    } else {
        gBgFx->scaleX = 0x100;
    }

    gBgFx->scaleY = 0x100;
    gBgFx->update = BgFxUpdateFadeInOut;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateAnsemWave() {
    if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
        gBgFx->x += 0x700;
    } else {
        gBgFx->x += -0x700;
    }

    if (gBgFx->x < (gBtlWork->xMin - 0x40) << 8 || gBgFx->x > (gBtlWork->xMax + 0x40) << 8) {
        BgAnimStop();
    } else if (ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 16, 16, 48)) {
        m4aSongNumStart(SONG_BTL_AN_WAVEHIT);
    }

    BgFxUpdateBase();
}

void BgFxStartAnsemWave(s32 x, s32 y, s32 z, u8 f, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->attack = w;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefAnsemWave, sx, sy);

    if (f) {
        gBgFx->scaleX = 0x100;
    } else {
        gBgFx->scaleX = -0x100;
        gBgFx->flags |= BGFX_FLAG_FLIP_X;
    }

    gBgFx->scaleY = 0x100;
    m4aSongNumStart(SONG_EF_AN_WAVE);
    gBgFx->update = BgFxUpdateAnsemWave;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void func_08016BCC(s32 x, s32 y) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    WorldToScreen(&sx, &sy, x, y, 0);
    BgAnimStart(&gBgAnimDefFriendHit, sx, sy);
    gBgFx->scaleX = 0x900;
    gBgFx->scaleY = 0x900;
    gBgFx->update = BgFxUpdateBase;
}

void BgFxStartJfMajinBeam(s32 x, s32 y, s32 z, s32 w, u8 f, u16 a) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->unk_0A = a;
    gBgFx->state = 0;
    gBgFx->angle = f;
    WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, gBgFx->z);
    BgAnimStart(&gBgAnimDefJfMajinBeam, sx, sy);
    gBgFx->scaleY = w;
    gBgFx->update = BgFxUpdateFadeInOut;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateFireBurst() {
    u16 a;
    u16 b;
    u16 ang;
    s16 sx;
    s16 sy;
    s32 dx;

    BgAnimGetFrameState(&a, &b);
    dx = 0;

    if (gBgFx->timer > 0) {
        if (a > 7) {
            ang = gBgFx->angle;

            if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
                ApproachAngle(&ang, GetAngle(gBgFx->x, gBgFx->y,
                                             gBgFx->unk_28, gBgFx->unk_2C) + 64, 5);
            } else {
                ApproachAngle(&ang, GetAngle(gBgFx->x, gBgFx->y,
                                             gBgFx->unk_28, gBgFx->unk_2C) - 64, 5);
            }

            gBgFx->angle = ang;
            ApproachValue(&gBgFx->x, gBgFx->unk_28, gBgFx->timer);
            ApproachValue(&gBgFx->y, gBgFx->unk_2C, gBgFx->timer);
            ApproachValue(&gBgFx->z, gBgFx->unk_30, gBgFx->timer);

            if (TestAttackBox(gBgFx->x, gBgFx->y, gBgFx->z,
                              8, 8, 16)) {
                gBgFx->timer = -1;
            } else {
                gBgFx->timer--;
            }
        } else if (a > 2) {
            if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
                dx = ((7 - a) << 8) * 7;
            } else {
                s32 t = 7 - a;
                t *= 256;
                dx = t * -7;
            }

            if (TestAttackBox(gBgFx->x + dx, gBgFx->y,
                              gBgFx->z, 8, 8, 16)) {
                gBgFx->timer = -1;
            }
        }
    }

    switch (gBgFx->timer) {
    case 0:
        gBgFx->update = BgFxUpdateFadeOut;
        break;
    case -1:
        m4aSongNumStart(SONG_EF_DRHEET);
        SetBlendAlpha(16, 11);
        gBgFx->angle = 0;
        gBgFx->scaleX = 0x500;
        gBgFx->scaleY = 0x500;
        gBgFx->x += dx;
        gBgFx->releaseFrames = 20;
        WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y,
                      gBgFx->z);
        BgAnimStart(&gBgAnimDefExplosion, sx, sy);
        m4aSongNumStart(SONG_EF_FIRE03);
        gBgFx->timer = -2;
        gBgFx->unk_0A = 0;
        break;
    case -2:
        if (gBgFx->unk_0A == 7) {
            ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y,
                          gBgFx->z, 256, 256, 256);
        }

        gBgFx->scaleX += 51;
        gBgFx->scaleY += 51;
        gBgFx->unk_0A++;
        break;
    }

    BgFxUpdateBase();
}

void BgFxStartFireBurst(s32 x, s32 y, s32 z, s32 p, s32 q, s32 r, u8 f, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefFire00, sx, sy);
    m4aSongNumStart(SONG_EF_DRHEET);
    BgAnimSetLoopStartFrame(8);
    gBgFx->update = BgFxUpdateFireBurst;
    gBgFx->unk_28 = p;
    gBgFx->unk_2C = q;
    gBgFx->unk_30 = r;
    gBgFx->timer = 15;
    gBgFx->state = 3;
    gBgFx->attack = w;

    if (f) {
        gBgFx->flags |= BGFX_FLAG_FLIP_X;
        gBgFx->scaleX = -0x100;
    }

    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartFireExplosion(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->scaleX = 0x180;
    gBgFx->scaleY = 0x180;
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefFire03, sx, sy);
    gBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateFullscreen() {
    switch (gBgFx->state) {
    case 0:
        SetBlendAlpha(16, gBgFx->timer);

        if (gBgFx->timer > 15) {
            gBgFx->timer = 0;
            gBgFx->state = 1;
        } else {
            gBgFx->timer++;
        }

        break;
    case 1:
        if (gBgFx->timer > gBgFx->unk_0A) {
            gBgFx->timer = 0;
            gBgFx->state = 2;
        } else {
            gBgFx->timer++;
        }

        break;
    case 2:
        SetBlendAlpha(16, 16 - gBgFx->timer);

        if (gBgFx->timer > 15) {
            BgAnimStop();
            gBgFx->update = NULL;
            gBgFx->flags &= ~BGFX_FLAG_ACTIVE;
        } else {
            gBgFx->timer++;
        }

        break;
    }
}

void BgFxStartXmas(u16 a) {
    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->unk_0A = a;
    gBgFx->state = 0;
    BgAnimStart(&gBgAnimDefXmas, 120, 80);
    gBgFx->update = BgFxUpdateFullscreen;
    BgAnimSetLoopStartFrame(0);
    gBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxUpdateVixenIceFall() {
    u16 t;
    s32 w;
    t = (gSineTable[(gBgFx->unk_0C / 3) & 0xFF] * 10240) >> 16;
    w = ((abs(gSineTable[(u8)gBgFx->unk_0C]) >> 1) + 0x100) * 0x133 >> 8;
    BgAnimSetTransform(t + 15, 0x133, w);
    BgFxUpdateFullscreen();
    gBgFx->unk_0C++;
}

void BgFxStartVixenIceFall(u16 a) {
    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->unk_0A = a;
    gBgFx->unk_0C = 0;
    gBgFx->state = 0;
    BgAnimStart(&gBgAnimDefVixenIceFall, 120, 80);
    BgAnimSetTransform(10, 0x133, 0x133);
    gBgFx->update = BgFxUpdateVixenIceFall;
    BgAnimSetLoopStartFrame(0);
    gBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxStartFlame(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->scaleX = s;
    gBgFx->scaleY = s;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefFlame, sx, sy);
    gBgFx->update = BgFxUpdateBase;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartFrost(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->scaleX = s;
    gBgFx->scaleY = s;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefFrost, sx, sy);
    gBgFx->update = BgFxUpdateBase;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartUrsulaThunder(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefUrsulaThunder, sx, sy);
    gBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
}

void BgFxUpdateHoly() {
    if (gBgFx->unk_0C > 0) {
        ApproachValueHalfSteps(&gBgFx->scaleX, 0x200, gBgFx->unk_0C);
        gBgFx->unk_0C--;
    }

    if (gBgFx->unk_0E > 0) {
        ApproachValue(&gBgFx->scaleY, 0x180, gBgFx->unk_0E);
        gBgFx->unk_0E--;
    }

    switch (gBgFx->state) {
    case 0: {
        u16 t;

        SetBlendAlpha(16, gBgFx->timer);
        t = gBgFx->timer;

        if ((s16)t > 15) {
            gBgFx->timer = 0;
            gBgFx->state = 1;
        } else {
            gBgFx->timer = t + 1;
        }

        break;
    }
    case 1: {
        u16 t;

        ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 32, 16, 256);
        t = gBgFx->timer;

        if ((s16)t > gBgFx->unk_0A) {
            gBgFx->timer = 0;
            gBgFx->state = 2;
        } else {
            gBgFx->timer = t + 1;
        }

        break;
    }
    case 2: {
        u16 a = gBgFx->timer;
        u16 t;

        SetBlendAlpha(16, 16 - ((s16)a >> 1));
        ApproachValue(&gBgFx->scaleX, 10, 33 - gBgFx->timer);
        t = gBgFx->timer;

        if ((s16)t > 31) {
            BgAnimStop();
        } else {
            gBgFx->timer = t + 1;
        }

        break;
    }
    }

    BgFxUpdateBase();
}

void BgFxStartHoly(s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->unk_0A = 120;
    gBgFx->unk_0C = 60;
    gBgFx->unk_0E = 20;
    gBgFx->state = 0;
    gBgFx->attack = w;
    gBgFx->scaleX = 10;
    gBgFx->scaleY = 10;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gUnk_09EDAC00, sx, sy);
    gBgFx->update = BgFxUpdateHoly;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxTornadoLiftBtlObj(BtlObj* a, BtlObj* b, u8 c, u8 d) {
    s32 h;
    s32 dx;
    s32 dy;
    s32 t;
    s32 nx;
    s32 ny;

    if (d) {
        b->angle = GetAngle(a->x, a->y, b->x, b->y);
        b->knockbackSpeed = 0;
    }

    dx = b->x - gBgFx->x;

    if (dx >= 0 ? dx <= 0x4FFF : gBgFx->x - b->x <= 0x4FFF) {
        dy = b->y - gBgFx->y;

        if (dy >= 0 ? dy <= 0x27FF : gBgFx->y - b->y <= 0x27FF) {
            if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
                h = b->knockbackSpeed - ((gBgFx->x - b->x) >> 1);
            } else {
                h = b->knockbackSpeed + ((gBgFx->x - b->x) >> 1);
            }

            if (h > 0) {
                h = 0;
            }

            t = -(h >> 9);
            nx = gBgFx->x + gSineTable[(b->angle + c) & 0xFF] * (s16)t;
            ny = gBgFx->y + -gSineTable[((b->angle + c) & 0xFF) + 64] * ((s16)t >> 1);

            if (b->x < nx) {
                b->flags &= ~BTLOBJ_FLAG_FACING_LEFT;
            } else {
                b->flags |= BTLOBJ_FLAG_FACING_LEFT;
            }

            b->x += (nx - b->x) >> 3;
            b->y += (ny - b->y) >> 3;
            b->z += (h - b->z) >> 2;
            b->knockbackSpeed -= 110;
        }
    }
}

void BgFxTornadoLiftOpponents(u8 a, u8 b) {
    BtlObj* p;
    BtlObj* o;

    if (gBtlWork->flags & BTL_FLAG_VS_BATTLE) {
        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            p = gBtlWork->actor;
            o = gRikuBtlWork->actor;
        } else {
            p = gRikuBtlWork->actor;
            o = gBtlWork->actor;
        }

        BgFxTornadoLiftBtlObj(p, o, a, b);
    } else {
        p = gBtlWork->actor;
        o = ListPoolFirst(&gBtlWork->pool);

        while (o != NULL) {
            if (!(o->flags & BTLOBJ_FLAG_BOSS) && o->kind != 31) {
                BgFxTornadoLiftBtlObj(p, o, a, b);
            }

            o = ListPoolNext(&o->node);
        }
    }
}

void BgFxUpdateTornado() {
    u16 alpha;
    s16 v;
    u32 u;

    switch (gBgFx->state) {
    case 0:
        v = 17 - gBgFx->timer;

        if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
            ApproachValueHalfSteps(&gBgFx->scaleX, -0x100, v);
        } else {
            ApproachValueHalfSteps(&gBgFx->scaleX, 0x100, v);
        }

        ApproachValueHalfSteps(&gBgFx->scaleY, 0x100, v);
        SetBlendAlpha(16, gBgFx->timer);

        if (gBgFx->timer > 15) {
            gBgFx->timer = 0;
            gBgFx->state = 1;
        } else {
            gBgFx->timer++;
        }

        break;
    case 1:
        u = (u16)gBgFx->timer;
        gBgFx->scaleY = abs(gSineTable[(u8)gBgFx->timer] >> 1) + 0x100;

        if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
            if ((u16)u == 0) {
                BgFxTornadoLiftOpponents(-u * 8, 1);
            } else {
                BgFxTornadoLiftOpponents(-u * 8, 0);
            }
        } else {
            if ((u16)u == 0) {
                BgFxTornadoLiftOpponents(u * 8, 1);
            } else {
                BgFxTornadoLiftOpponents(u * 8, 0);
            }
        }

        if (gBgFx->timer > gBgFx->unk_0A) {
            gBgFx->timer = 0;
            gBgFx->state = 2;
            ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y,
                          gBgFx->z, 40, 20, 256);
        } else {
            gBgFx->timer++;
        }

        break;
    case 2:
        alpha = 16;
        v = gBgFx->timer;
        u = v;
        alpha -= u;
        SetBlendAlpha(16, alpha);

        if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
            ApproachValue(&gBgFx->scaleX, -10, 17 - u);
        } else {
            ApproachValue(&gBgFx->scaleX, 10, 17 - u);
        }

        ApproachValue(&gBgFx->scaleY, 768, 17 - v);

        if (v > 15) {
            BgAnimStop();
        } else {
            gBgFx->timer++;
        }

        break;
    }

    if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
        gBgFx->x -= 102;
    } else {
        gBgFx->x += 102;
    }

    gBgFx->unk_3C = 0;
    ApplyBattleBounds(&gBgFx->x, &gBgFx->y, &gBgFx->z,
                  &gBgFx->unk_3C);
    ClampBattlePosition(&gBgFx->x, &gBgFx->y, -16, 0);
    BgFxUpdateBase();
}

void BgFxStartTornado(s32 x, s32 y, s32 z, s32 w, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->unk_0A = 220;
    gBgFx->unk_0C = 0;
    gBgFx->state = 0;
    gBgFx->attack = w;
    gBgFx->scaleY = 10;

    if (f) {
        gBgFx->scaleX = -10;
        gBgFx->flags |= BGFX_FLAG_FLIP_X;
    } else {
        gBgFx->scaleX = 10;
    }

    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefTornado, sx, sy);
    gBgFx->update = BgFxUpdateTornado;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateBind() {
    s16 v;
    s16 w;

    switch (gBgFx->state) {
    case 0:
        gBgFx->scaleX += 0x80;

        if (gBgFx->timer > 60) {
            gBgFx->timer = 0;
            gBgFx->state = 1;
        } else {
            gBgFx->timer++;
        }

        break;
    case 1:
        v = gBgFx->timer;
        SetBlendAlpha(16, v + 8);

        if (v > 7) {
#ifdef VERSION_EU
            ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y + 0x1000, 0, 0x100, 0x100, 0x100);
#else
            ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y + 0x1000, 0, 0x100, 0x100, 8);
#endif
            gBgFx->timer = 0;
            gBgFx->state = 2;
        } else {
            gBgFx->timer++;
        }

        break;
    case 2:
        w = gBgFx->timer >> 2;
        SetBlendAlpha(16, 16 - w);

        if (w > 15) {
            BgAnimStop();
        } else {
            gBgFx->timer++;
        }

        break;
    }

    BgFxUpdateBase();
}

void BgFxStartBind(s32 x, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = gBtlWork->yMin << 8;
    gBgFx->z = 0;
    gBgFx->attack = w;
    gBgFx->scaleX = 10;
    gBgFx->scaleY = -((gBtlWork->yMax - gBtlWork->yMin) << 8) / 96;
    WorldToScreen(&sx, &sy, x, gBgFx->y, 0);
    BgAnimStart(&gUnk_09EDAC00, sx, sy);
    gBgFx->flags |= BGFX_FLAG_BELOW_SPRITES;
    gBgFx->state = 0;
    SetBlendAlpha(16, 8);
    gBgFx->update = BgFxUpdateBind;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateAxcelFireWall() {
    switch (gBgFx->state) {
    case 0:
        ApproachValue(&gBgFx->x, gBgFx->unk_28, gBgFx->unk_0A);

        if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
            ApproachValue(&gBgFx->scaleX, -256, gBgFx->unk_0A);
        } else {
            ApproachValue(&gBgFx->scaleX, 256, gBgFx->unk_0A);
        }

        gBgFx->scaleY = abs(gBgFx->scaleX);
        gBgFx->unk_0A--;

        if (gBgFx->unk_0A <= 0) {
            gBgFx->state = 1;
            gBgFx->unk_0A = 16;
        }

        break;
    case 1:
        if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
            if (ApplyAttackBox(gBgFx->attack, gBgFx->x - 0x1000, gBgFx->y + 0x2000, 0, 20, 32, 64) || ApplyAttackBox(gBgFx->attack, gBgFx->x + 0x1000, gBgFx->y - 0x2000, 0, 20, 32, 64)) {
                gBgFx->state = 2;
                m4aSongNumStart(SONG_EF_FIRE01);
            }
        } else if (ApplyAttackBox(gBgFx->attack, gBgFx->x - 0x1000, gBgFx->y - 0x2000, 0, 20, 32, 64)) {
            gBgFx->state = 2;
            m4aSongNumStart(SONG_EF_FIRE01);
        } else if (ApplyAttackBox(gBgFx->attack, gBgFx->x + 0x1000, gBgFx->y + 0x2000, 0, 20, 32, 64)) {
            gBgFx->state = 2;
            m4aSongNumStart(SONG_EF_FIRE01);
        }

        if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
            if (gBtlWork->actor->x < gBgFx->x) {
                gBgFx->state = 2;
            }
        } else {
            if (gBtlWork->actor->x > gBgFx->x) {
                gBgFx->state = 2;
            }
        }

        break;
    case 2:
        SetBlendAlpha(16, gBgFx->unk_0A);

        if (gBgFx->unk_0A <= 0) {
            BgAnimStop();
        } else {
            gBgFx->unk_0A--;
        }

        break;
    }

    BgFxUpdateBase();
}

void BgFxStartAxcelFireWall(s32 x, u8 f, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->state = 0;
    gBgFx->x = x;
    gBgFx->y = (gBtlWork->yMin + gBtlWork->yMax) << 7;
    gBgFx->z = 0;
    gBgFx->attack = w;
    gBgFx->unk_0A = 20;
    WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, 0);
    BgAnimStart(&gBgAnimDefAxcelFireWall, sx, sy);

    if (f) {
        gBgFx->scaleX = 10;
        gBgFx->unk_28 = x - 0x3700;
    } else {
        gBgFx->scaleX = -10;
        gBgFx->unk_28 = x + 0x3700;
        gBgFx->flags |= BGFX_FLAG_FLIP_X;
    }

    gBgFx->scaleY = 10;
    gBgFx->flags |= BGFX_FLAG_BELOW_SPRITES;
    gBgFx->update = BgFxUpdateAxcelFireWall;
    BgAnimSetLoopStartFrame(0);
}

void BgFxUpdateGround() {
    u16 k;
    u16 t;
    ApproachValue(&gBgFx->scaleX, 0x300, gBgFx->unk_0A);
    gBgFx->scaleY = gBgFx->scaleX;
    gBgFx->unk_0A--;
    BgAnimGetFrameState(&k, NULL);

    if (k <= 4) {
        t = (gBgFx->scaleX * 5) >> 5;

        if (ApplyAttackBox(0x13D, gBgFx->x, gBgFx->y, gBgFx->z, t, (s16)t >> 1, 1)) {
            m4aSongNumStart(SONG_BTL_MARL_GROUNDHIT);
        }
    }

    BgFxUpdateBase();
}

void BgFxStartMahluxiaGround(s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->attack = w;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefMahluxiaGround, sx, sy);
    gBgFx->scaleX = 0x80;
    gBgFx->scaleY = 0x80;
    gBgFx->unk_0A = BgAnimGetDuration(BgAnimGetCurrent());
    gBgFx->flags |= BGFX_FLAG_BELOW_SPRITES;
    gBgFx->update = BgFxUpdateGround;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartLexceusGround(s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->attack = w;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&sBgAnimDefLexceusGround, sx, sy);
    gBgFx->scaleX = 0x80;
    gBgFx->scaleY = 0x80;
    gBgFx->unk_0A = BgAnimGetDuration(BgAnimGetCurrent());
    gBgFx->flags |= BGFX_FLAG_BELOW_SPRITES;
    gBgFx->update = BgFxUpdateGround;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateHanabira() {
    switch (gBgFx->state) {
    case 0:
        if (gBgFx->timer > 50) {
            gBgFx->timer = 0;
            gBgFx->state = 1;
        } else {
            gBgFx->timer++;
        }

        break;
    case 1:
        gBgFx->timer = 0;
        gBgFx->state = 2;

        if (ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 0x100, 0x100, 0x100)) {
            m4aSongNumStart(SONG_BTL_ETC_HIT05);
        }

        break;
    case 2:
        SetBlendAlpha(16, 16 - gBgFx->timer);

        if (gBgFx->timer > 15) {
            BgAnimStop();
        } else {
            gBgFx->timer++;
        }

        break;
    }

    gBgFx->unk_28 += 30;
    gBgFx->angle += gBgFx->unk_28 >> 8;
    gBgFx->scaleX += 10;
    gBgFx->scaleY = gBgFx->scaleX;
    BgFxUpdateBase();
}

void BgFxStartHanabira(s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->attack = w;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefHanabira, sx, sy);
    gBgFx->state = 0;
    gBgFx->scaleX = 5;
    gBgFx->scaleY = 5;
    gBgFx->unk_28 = 256;
    gBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
    m4aSongNumStart(SONG_EF_MARL_HANABIRA);
    gBgFx->update = BgFxUpdateHanabira;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateKama() {
    if (gBtlWork->hitStop != 0) {
        BgFxUpdateBase();
        return;
    }

    if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
        gBgFx->angle += 3;
    } else {
        gBgFx->angle -= 3;
    }

    gBgFx->x = gBgFx->unk_28 + ((gSineTable[gBgFx->angle] * gBgFx->unk_3C) >> 8);
    gBgFx->z = gBgFx->unk_30 + ((-gSineTable[gBgFx->angle + 64] * gBgFx->unk_3C) >> 8);

    if (ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, 10, 5, 72)) {
        m4aSongNumStart(SONG_BTL_MARL_EFEHIT);
    }

    switch (gBgFx->state) {
    case 0:
        SetBlendAlpha(16, (u16)gBgFx->timer * 2);

        if (gBgFx->timer > 7) {
            gBgFx->timer = 0;
            gBgFx->state = 1;
        } else {
            gBgFx->timer++;
        }

        break;
    case 1:
        if (gBgFx->timer > 30) {
            gBgFx->timer = 0;
            gBgFx->state = 2;
        } else {
            gBgFx->timer++;
        }

        break;
    case 2:
        SetBlendAlpha(16, 16 - (u16)gBgFx->timer * 2);

        if (gBgFx->timer > 7) {
            BgAnimStop();
        } else {
            gBgFx->timer++;
        }

        break;
    }

    BgFxUpdateBase();
}

void BgFxStartKama(s32 x, s32 y, s32 z, s32 w, s32 v) {
    s16 sx;
    s16 sy;
    s32 d;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->attack = v;

    if (w > 0) {
        gBgFx->scaleX = -0x180;
        gBgFx->flags |= BGFX_FLAG_FLIP_X;
        x -= 0x4000;
        w += 0x4000;
    } else {
        gBgFx->scaleX = 0x180;
        x += 0x4000;
        w -= 0x4000;
    }

    gBgFx->unk_28 = x;
    gBgFx->unk_30 = z;
    d = abs(w);
    gBgFx->unk_3C = d;
    gBgFx->x = x + ((gSineTable[0] * d) >> 8);
    gBgFx->z = z + ((-gSineTable[64] * d) >> 8);
    gBgFx->y = y;
    gBgFx->scaleY = 0x180;
    SetBlendAlpha(16, 0);
    m4aSongNumStart(SONG_EF_MARL_KAMAEF);
    WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, gBgFx->z);
    BgAnimStart(&gBgAnimDefKama, sx, sy);
    gBgFx->state = 0;
    gBgFx->update = BgFxUpdateKama;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateRikuLimit() {
    s16 t = gBgFx->timer >> 1;
    SetBlendAlpha(16, 16 - t);

    if (t > 15) {
        BgAnimStop();
    }

    gBgFx->timer++;
    BgFxUpdateBase();
}

void BgFxStartRikuLimit(s32 x, s32 y, s32 z, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(3)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->angle = f;
    WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, gBgFx->z);
    BgAnimStart(&sBgAnimDefRikuLimit, sx, sy);
    gBgFx->flags |= BGFX_FLAG_BELOW_SPRITES;
    gBgFx->update = BgFxUpdateRikuLimit;
}

void BgFxStartDragonFire(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->scaleX = s;
    gBgFx->scaleY = s;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefDragonFire, sx, sy);
    gBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateLaxeneBeam() {
    s32 x;
    s32 y;
    s32 z;
    s16 r;
    u8 ang;
    BtlObj* o;

    switch (gBgFx->state) {
    case 0:
        if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
            ApproachValueHalfSteps(&gBgFx->scaleX, -204, gBgFx->unk_0A);
        } else {
            ApproachValueHalfSteps(&gBgFx->scaleX, 204, gBgFx->unk_0A);
        }

        gBgFx->unk_0A--;

        if (gBgFx->unk_0A <= 0) {
            gBgFx->timer = 0;
            gBgFx->state = 1;
        } else {
            gBgFx->timer++;
        }

        break;
    case 1:
        SetBlendAlpha(16, 16 - gBgFx->timer);

        if (gBgFx->timer > 15) {
            BgAnimStop();
        } else {
            gBgFx->timer++;
        }

        break;
    }

    r = (abs(gBgFx->scaleX) * 5) >> 4;

    if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
        ang = gBgFx->angle + 192;
    } else {
        ang = gBgFx->angle + 64;
    }

    x = gBgFx->x + gSineTable[ang] * r;
    z = gBgFx->z + -gSineTable[ang + 64] * r;
    y = gBgFx->y;
    ApplyAttackBox(gBgFx->attack, x, y, z, 32, 16, 16);
    o = gBtlWork->actor;

    if (o->flags & BTLOBJ_FLAG_HURT) {
        o->x += (x - o->x) >> 2;
        o->y += (y - o->y) >> 2;
        o->z += (z - o->z) >> 1;
    }

    BgFxUpdateBase();
}

void BgFxStartLaxeneBeam(s32 x, s32 y, s32 z, u8 f, s32 v) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->state = 0;
    gBgFx->unk_0A = 80;
    gBgFx->attack = v;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefLaxeneBeam, sx, sy);

    if (f) {
        gBgFx->flags |= BGFX_FLAG_FLIP_X;
        gBgFx->angle = 248;
    } else {
        gBgFx->angle = 8;
    }

    if (gBgFx->flags & BGFX_FLAG_FLIP_X) {
        if (gBgFx->x < gBtlWork->actor->x) {
            gBgFx->state = 1;
        } else {
            gBgFx->scaleX = -(((gBgFx->x - gBtlWork->actor->x) << 8) / 19200);
        }
    } else {
        if (gBgFx->x > gBtlWork->actor->x) {
            gBgFx->state = 1;
        } else {
            gBgFx->scaleX = ((gBtlWork->actor->x - gBgFx->x) << 8) / 19200;
        }
    }

    BgAnimSetLoopStartFrame(3);
    gBgFx->update = BgFxUpdateLaxeneBeam;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateAero() {
    s16 t;

    switch (gBgFx->state) {
    case 0:
        gBgFx->scaleX += 2;
        gBgFx->scaleY += 2;
        break;
    case 1:
        gBgFx->scaleX += 5;
        gBgFx->scaleY += 5;
        break;
    case 2:
        gBgFx->scaleX += 10;
        gBgFx->scaleY += 10;
        break;
    }

    if (gBgFx->timer == 10) {
        t = (gBgFx->scaleX * 3) >> 4;

        if (ApplyAttackBox(gBgFx->attack, gBgFx->x, gBgFx->y, gBgFx->z, t, t, 100)) {
            m4aSongNumStart(SONG_EF_DS_ANKOKUPUNCH);
        }
    }

    gBgFx->timer++;
    BgFxUpdateBase();
}

void BgFxStartAero(u16 a, s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->attack = w;
    gBgFx->state = a;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefAero, sx, sy);
    gBgFx->update = BgFxUpdateAero;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartRikuDarkModeFlash(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefRikuDarkModeFlash, sx, sy);
    gBgFx->update = BgFxUpdateBase;
}

void BgFxStartLstCtr(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->scaleX = s;
    gBgFx->scaleY = s;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefLstCtr, sx, sy);
    gBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartLstCtrFlipped(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->scaleX = -s;
    gBgFx->scaleY = s;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefLstCtr, sx, sy);
    gBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    gBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void func_08018B04(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->scaleX = s;
    gBgFx->scaleY = s;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gUnk_09EDAD80, sx, sy);
    gBgFx->update = BgFxUpdateBase;
}

void BgFxUpdateRikuDarkMode() {
    switch (gBgFx->state) {
    case 0:
        ApproachValue(&gBgFx->unk_3C, 0xA00, gBgFx->unk_0A);
        ApproachValueHalfSteps(&gBgFx->scaleX, 460, gBgFx->unk_0A);
        ApproachValueHalfSteps(&gBgFx->scaleY, 512, gBgFx->unk_0A);
        SetBlendAlpha(16, gBgFx->unk_3C >> 8);
        gBgFx->unk_0A--;

        if (gBgFx->unk_0A <= 0) {
            gBgFx->timer = 0;
            gBgFx->state = 1;
        }

        break;
    case 1:
        gBgFx->state = 2;
        gBgFx->timer = 0;
        gBgFx->unk_0A = 25;
        break;
    case 2:
        ApproachValue(&gBgFx->unk_3C, 0, gBgFx->unk_0A);
        SetBlendAlpha(16, gBgFx->unk_3C >> 8);
        gBgFx->unk_0A--;

        if (gBgFx->unk_0A <= 0) {
            gBgFx->timer = 0;
            gBgFx->state = 3;
            BgAnimStop();
        }

        break;
    }

    BgFxUpdateBase();
}

void BgFxStartRikuDarkMode(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    SetBlendAlpha(16, 0);
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    gBgFx->state = 0;
    gBgFx->scaleX = 10;
    gBgFx->scaleY = 10;
    gBgFx->unk_3C = 0;
    gBgFx->endSignals = 0;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&sUnk_09EDAA38, sx, sy);
    BgAnimSetLoopStartFrame(0);
    gBgFx->update = BgFxUpdateRikuDarkMode;
    gBgFx->unk_0A = 43;
}

void BgFxUpdateRikuLimitFinish() {
    if (gBgFx->timer > 10) {
        switch (gBgFx->state) {
        case 0:
            ApplyAttackBox(11, gBgFx->x - 0x6000, gBgFx->y - 0x1000, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x, gBgFx->y + 0x2000, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x + 0x7000, gBgFx->y - 0x1000, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x - 0x3000, gBgFx->y + 0x2000, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x + 0x3000, gBgFx->y + 0x2800, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x - 0x6000, gBgFx->y + 0x6000, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x + 0x800, gBgFx->y + 0x7800, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x + 0x3000, gBgFx->y + 0x2800, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x + 0x6800, gBgFx->y + 0x6800, gBgFx->z,
                14, 14, 14);
            break;
        case 1:
            ApplyAttackBox(11, gBgFx->x + 0x6000, gBgFx->y - 0x1000, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x, gBgFx->y + 0x2000, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x - 0x7000, gBgFx->y - 0x1000, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x + 0x3000, gBgFx->y + 0x2000, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x - 0x3000, gBgFx->y + 0x2800, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x + 0x6000, gBgFx->y + 0x6000, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x - 0x800, gBgFx->y + 0x7800, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x - 0x3000, gBgFx->y + 0x2800, gBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, gBgFx->x - 0x6800, gBgFx->y + 0x6800, gBgFx->z,
                14, 14, 14);
            break;
        }
    }

    gBgFx->timer++;
    BgFxUpdateBase();
}

void BgFxStartRikuLimitFinish(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    m4aSongNumStart(SONG_SND_705);
    WorldToScreen(&sx, &sy, gBgFx->x, gBgFx->y, gBgFx->z);
    gBgFx->state = GetRandom() % 2;

    switch (gBgFx->state) {
    case 0:
        BgAnimStart(&gBgAnimDefRikuLimitFinish, sx, sy);
        break;
    case 1:
        BgAnimStart(&gBgAnimDefRikuLimitFinish, sx, sy);
        gBgFx->flags |= BGFX_FLAG_FLIP_X;
        gBgFx->scaleX = -0x100;
        break;
    }

    gBgFx->update = BgFxUpdateRikuLimitFinish;
}

void func_08018FE4(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    gBgFx->x = x;
    gBgFx->y = y;
    gBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gUnk_09EDADB0, sx, sy);
    gBgFx->update = BgFxUpdateBase;
}
