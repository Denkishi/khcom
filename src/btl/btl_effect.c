/**
 * btl_effect.c
 * Battle Background Effects
 */

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

BgAnimationDef gBgAnimDefDashRing = { &sBgAnimationChunks[9], gUnk_08F05384, gUnk_08F6A2E4, 192, 74, 16, 16, 5, 3 };

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

BgAnimationDef gBgAnimDefGlow = { &sBgAnimationChunks[64], gUnk_08F2D384, gUnk_08F6C124, 192, 122, 16, 16, 1, 65535 };

static BgAnimationDef sBgAnimDefDarkGlow = { &sBgAnimationChunks[64], gUnk_08F2D384, gUnk_08F6C064, 192, 122, 16, 16, 1, 65535 };

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

BgAnimationDef gBgAnimDefAnsemRush = { &sBgAnimationChunks[77], gUnk_08F35384, gUnk_08F6C7E4, 192, 74, 17, 16, 1, 65535 };

BgAnimationDef gBgAnimDefAnsemWave = { &sBgAnimationChunks[78], gUnk_08F36384, gUnk_08F6C8A4, 192, 75, 16, 26, 3, 3 };

BgAnimationDef gBgAnimDefStunImpact = { &sBgAnimationChunks[79], gUnk_08F38384, gUnk_08F6CA24, 192, 74, 16, 18, 4, 5 };

BgAnimationDef gBgAnimDefUrsulaThunder = { &sBgAnimationChunks[80], gUnk_08F39384, gUnk_08F6CAE4, 192, 45, 16, 16, 4, 5 };

BgAnimationDef gBgAnimDefWorldSelect = { &sBgAnimationChunks[81], gUnk_08F3A384, gUnk_08F6CBA4, 192, 64, 20, 7, 8, 6 };

BgAnimationDef gBgAnimDefWorldStart = { &sBgAnimationChunks[82], gUnk_08F3B384, gUnk_08F6CC64, 192, 155, 16, 16, 6, 4 };

BgAnimationDef gBgAnimDefXmas = { &sBgAnimationChunks[84], gUnk_08F3C384, gUnk_08F6CD24, 192, 64, 32, 32, 10, 8 };

BgAnimationDef gBgAnimDefVixenIceFall = { &sBgAnimationChunks[84], gUnk_08F3C384, gUnk_08F6CD24, 192, 64, 32, 32, 10, 2 };

BgAnimationDef gBgAnimDefLightPillar = { &sBgAnimationChunks[86], gUnk_08F3D384, gUnk_08F6CDE4, 192, 115, 16, 27, 1, 65535 };

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

BgAnimationDef gBgAnimDefDsdTransition = { &sBgAnimationChunks[105], gUnk_08F4A384, gUnk_08F6D864, 192, 64, 16, 16, 8, 6 };

BgAnimationDef gBgAnimDefRikuLimitFinish = { &sBgAnimationChunks[106], gUnk_08F48384, gUnk_08F6D6E4, 192, 64, 30, 30, 6, 7 };

BgAnimationDef gBgAnimDefRikuDiveHit = { &sBgAnimationChunks[107], gUnk_08F4B384, gUnk_08F6D924, 192, 64, 16, 16, 5, 5 };

static BgFx* sBgFx;

void BgFxReset() {
    if (gBtlWork->flags & BTL_FLAG_BOSS_BATTLE) {
        SetBgPriority(sBgFx->bg, 0);
    } else {
        SetBgPriority(sBgFx->bg, 1);
    }

    SetBgBlend(sBgFx->bg, 16, 16);
    sBgFx->scaleX = 0x100;
    sBgFx->scaleY = 0x100;
    sBgFx->angle = 0;
    sBgFx->update = NULL;
    sBgFx->timer = 0;
    sBgFx->z = 0;
    sBgFx->flags = BGFX_FLAG_ACTIVE;
    sBgFx->releaseFrames = 0;
}

u8 BgFxIsBlocked(u8 a) {
    if (BgAnimIsStopped()) {
        sBgFx->priority = a;
        return 0;
    }

    if (sBgFx->priority < a) {
        return 1;
    }

    sBgFx->priority = a;
    return 0;
}

void BgFxReleaseEarly(s16 a) {
    u16 b;
    u16 c;
    BgAnimGetFrameState(&b, &c);

    if (BgAnimGetDuration(BgAnimGetCurrent()) - b * c <= a) {
        sBgFx->flags &= ~BGFX_FLAG_ACTIVE;
        sBgFx->priority = 2;

        if (sBgFx->flags & BGFX_FLAG_SCREEN_DIMMED) {
            sBgFx->flags &= ~BGFX_FLAG_SCREEN_DIMMED;
            FadeToOriginal(FADE_MODE_BLACK, 8);
        }
    }
}

void BgFxInit(u16 a, u16 bg) {
    s32 i;
    sBgFx = EwramAlloc(sizeof(BgFx));

    for (i = 10; i < 16; i++) {
        FadeSetPaletteExcluded(i, 1);
    }

    if (a == 0) {
        BgAnimInit(bg, 0xC000, 0);
    } else {
        BgAnimInit(bg, 0x8000, 0x80);
    }

    SetBgBlend(bg, 16, 16);
    sBgFx->update = NULL;
    sBgFx->priority = 0xFF;
    sBgFx->bg = bg;
    BgFxReset();
    sBgFx->flags = 0;
}

void BgFxFree() {
    EwramFree(sBgFx);
}

void BgFxUpdate() {
    if (gBtlWork->flags & BTL_FLAG_STOP_BGFX) {
        gBtlWork->flags &= ~BTL_FLAG_STOP_BGFX;
        sBgFx->flags &= ~BGFX_FLAG_ACTIVE;
        sBgFx->update = NULL;
        BgAnimStop();
        SetBgBlend(sBgFx->bg, 16, 16);
    }

    if (sBgFx->update != NULL) {
        sBgFx->update();

        if (!(gBtlWork->flags & BTL_FLAG_BOSS_BATTLE)) {
            gBtlWork->bossY = sBgFx->y;

            if (sBgFx->flags & BGFX_FLAG_ABOVE_SPRITES) {
                SetBgPriority(sBgFx->bg, 0);
            } else if (sBgFx->flags & BGFX_FLAG_BELOW_SPRITES) {
                SetBgPriority(sBgFx->bg, 1);
                gBtlWork->bossPriorityOffset = 0xFF00;
            } else {
                gBtlWork->bossPriorityOffset = 8;
            }
        }
    }

    BgAnimUpdate();
}

u8 BgFxIsActive() {
    if (sBgFx->flags & BGFX_FLAG_ACTIVE) {
        return 1;
    }

    return 0;
}

void BgFxUpdateBase() {
    s16 sx;
    s16 sy;

    if (BgAnimIsStopped()) {
        SetBgBlend(sBgFx->bg, 16, 16);
        sBgFx->update = NULL;
        sBgFx->flags &= ~BGFX_FLAG_ACTIVE;

        if (sBgFx->flags & BGFX_FLAG_SCREEN_DIMMED) {
            FadeToOriginal(FADE_MODE_BLACK, 8);
        }

        return;
    }

    if (gBtlWork->flags & BTL_FLAG_VS_BATTLE) {
        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            if (gBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE) {
                if (gBtlWork->stockMove < GetStockMoveCount()) {
                    BgFxReleaseEarly(sBgFx->releaseFrames);
                }
            }
        } else if (gRikuBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE) {
            if (gRikuBtlWork->stockMove < GetStockMoveCount()) {
                BgFxReleaseEarly(sBgFx->releaseFrames);
            }
        }
    } else if (gBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE) {
        if (gBtlWork->stockMove < GetStockMoveCount()) {
            BgFxReleaseEarly(sBgFx->releaseFrames);
        }
    }

    WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, sBgFx->z);
    BgAnimSetPosition(sx, sy);

    if (sBgFx->flags & BGFX_FLAG_IGNORE_ZOOM) {
        BgAnimSetTransform(sBgFx->angle + gBtlWork->rotation, sBgFx->scaleX, sBgFx->scaleY);
    } else {
        s32 a = sBgFx->scaleX * gBtlWork->scale >> 8;
        s32 b = sBgFx->scaleY * gBtlWork->scale >> 8;

        BgAnimSetTransform(sBgFx->angle + gBtlWork->rotation, a, b);
    }
}

void BgFxStartCure(u16 a, s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->releaseFrames = 20;
    sBgFx->x = x;
    sBgFx->y = y;

    switch (a) {
    case 0:
        sBgFx->z = z - 0x1400;
        break;
    case 1:
        sBgFx->z = z;
        break;
    case 2:
        sBgFx->z = z - 0x1000;
        break;
    }

    WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, sBgFx->z);

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
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
    sBgFx->update = BgFxUpdateBase;
}

void BgFxUpdateFadeOut() {
    SetBlendAlpha(16, 16 - sBgFx->timer);

    if (sBgFx->timer > 15) {
        BgAnimStop();
    } else {
        sBgFx->timer++;
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

    if (sBgFx->timer > 0) {
        if (a > 7) {
            ang = sBgFx->angle;

            if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
                ApproachAngle(&ang, GetAngle(sBgFx->x, sBgFx->y,
                                             sBgFx->targetX, sBgFx->targetY) + 64, 5);
            } else {
                ApproachAngle(&ang, GetAngle(sBgFx->x, sBgFx->y,
                                             sBgFx->targetX, sBgFx->targetY) - 64, 5);
            }

            sBgFx->angle = ang;
            ApproachValue(&sBgFx->x, sBgFx->targetX, sBgFx->timer);
            ApproachValue(&sBgFx->y, sBgFx->targetY, sBgFx->timer);
            ApproachValue(&sBgFx->z, sBgFx->targetZ, sBgFx->timer);

            if (ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y,
                              sBgFx->z, 8, 8, 16)) {
                sBgFx->timer = -1;
            } else {
                sBgFx->timer--;
            }
        } else if (a > 2) {
            if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
                dx = ((7 - a) << 8) * 7;
            } else {
                s32 t = 7 - a;
                t *= 256;
                dx = t * -7;
            }

            if (ApplyAttackBox(sBgFx->attack, sBgFx->x + dx,
                              sBgFx->y, sBgFx->z, 8, 8, 16)) {
                sBgFx->timer = -1;
            }
        }
    }

    if (sBgFx->timer == 0) {
        sBgFx->update = BgFxUpdateFadeOut;
    } else if (sBgFx->timer == -1) {
        sBgFx->angle = 0;
        sBgFx->scaleX = 0x100;
        sBgFx->scaleY = 0x100;
        sBgFx->x += dx;
        sBgFx->releaseFrames = 20;
        WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y,
                      sBgFx->z);

        switch (sBgFx->state) {
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

        sBgFx->timer = -2;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
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
    sBgFx->update = BgFxUpdateFire;
    sBgFx->targetX = p;
    sBgFx->targetY = q;
    sBgFx->targetZ = r;
    sBgFx->timer = 15;
    sBgFx->state = a;
    sBgFx->attack = w;

    if (f) {
        sBgFx->flags |= BGFX_FLAG_FLIP_X;
        sBgFx->scaleX = -0x100;
    }

    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartFireAtPlayer(s32 x, s32 y, s32 z, u8 f, s32 unused, s32 w, u16 a) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefFire00, sx, sy);
    m4aSongNumStart(SONG_EF_MON_FIRE);
    BgAnimSetLoopStartFrame(8);
    sBgFx->update = BgFxUpdateFire;
    sBgFx->targetX = gBtlWork->actor->x;
    sBgFx->targetY = gBtlWork->actor->y;
    sBgFx->targetZ = gBtlWork->actor->z;
    sBgFx->timer = a;
    sBgFx->state = 1;
    sBgFx->attack = w;

    if (f) {
        sBgFx->flags |= BGFX_FLAG_FLIP_X;
        sBgFx->scaleX = -0x180;
    } else {
        sBgFx->scaleX = 0x180;
    }

    sBgFx->scaleY = 0x180;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
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

    if (sBgFx->timer > 0) {
        if (a > 7) {
            angle = sBgFx->angle;

            if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
                ApproachAngle(&angle,
                    GetAngle(sBgFx->x, sBgFx->y, sBgFx->targetX,
                        sBgFx->targetY) + 64,
                    5);
            } else {
                ApproachAngle(&angle,
                    GetAngle(sBgFx->x, sBgFx->y, sBgFx->targetX,
                        sBgFx->targetY) - 64,
                    5);
            }

            sBgFx->angle = angle;
            ApproachValue(&sBgFx->x, sBgFx->targetX, sBgFx->timer);
            ApproachValue(&sBgFx->y, sBgFx->targetY, sBgFx->timer);
            ApproachValue(&sBgFx->z, sBgFx->targetZ, sBgFx->timer);

            if (TestAttackBox(sBgFx->x, sBgFx->y, sBgFx->z, 8, 16, 16)) {
                sBgFx->timer = -1;
            } else {
                sBgFx->timer--;
            }
        } else if (a > 2) {
            if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
                dx = ((7 - a) << 8) * 7;
            } else {
                s32 t = 7 - a;
                t *= 256;
                dx = t * -7;
            }

            if (TestAttackBox(sBgFx->x + dx, sBgFx->y, sBgFx->z, 8, 16, 16)) {
                sBgFx->timer = -1;
            }
        }
    }

    if (sBgFx->timer == 0) {
        sBgFx->timer = -1;
    } else if (sBgFx->timer == -1) {
        sBgFx->angle = 0;
        sBgFx->scaleX = 0x100;
        sBgFx->scaleY = 0x100;
        sBgFx->x += dx;
        sBgFx->releaseFrames = 20;
        WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, sBgFx->z);

        switch (sBgFx->state) {
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

        sBgFx->timer = -2;
    }

    if (sBgFx->timer == -2) {
        switch (sBgFx->state) {
        case 0:
            if (sBgFx->steps == 20) {
                ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y,
                    sBgFx->z, 18, 18, 18);
            }

            break;
        case 1:
            if (sBgFx->steps == 35) {
                ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y,
                    sBgFx->z, 24, 24, 30);
            }

            break;
        case 2:
        default:
            if (sBgFx->steps == 50) {
                ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y,
                    sBgFx->z, 48, 48, 52);
            }

            break;
        }

        sBgFx->steps++;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefBlizzard00, sx, sy);

    if ((gBtlWork->flags & BTL_FLAG_VS_BATTLE) == 0 && (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION)) {
        m4aSongNumStart(SONG_EF_MON_BURIZA);
    } else {
        m4aSongNumStart(SONG_EF_BURIZA00);
    }

    BgAnimSetLoopStartFrame(8);
    sBgFx->update = BgFxUpdateBlizzard;
    sBgFx->targetX = p;
    sBgFx->targetY = q;
    sBgFx->targetZ = r;
    sBgFx->timer = 15;
    sBgFx->state = a;
    sBgFx->attack = w;
    sBgFx->steps = 0;

    if (f) {
        sBgFx->scaleX = -0x100;
        sBgFx->flags |= BGFX_FLAG_FLIP_X;
    }

    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateFlash() {
    sBgFx->scaleX += sBgFx->targetX;
    sBgFx->scaleY += sBgFx->targetY;
    sBgFx->angle += 3;
    BgFxUpdateBase();

    if (sBgFx->timer > 5) {
        s16 t = sBgFx->timer - 5;
        SetBlendAlpha(16, 16 - t);

        if (t > 15) {
            BgAnimStop();
        }
    }

    sBgFx->timer++;
}

void BgFxStartFlash(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(3)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    sBgFx->scaleX = 76;
    sBgFx->scaleY = 76;
    sBgFx->angle = 0;
    sBgFx->targetX = 25;
    sBgFx->targetY = 25;
    BgAnimStart(&gBgAnimDefFlash, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->update = BgFxUpdateFlash;
    sBgFx->timer = 0;
}

void BgFxUpdateFlashHit() {
    s16 t = sBgFx->timer;

    sBgFx->angle += 4;
    sBgFx->scaleX += sBgFx->targetX;
    sBgFx->scaleY += sBgFx->targetY;
    SetBlendAlpha(16, 16 - t);

    if (t > 15) {
        BgAnimStop();
    }

    sBgFx->timer++;
    BgFxUpdateBase();
}

void BgFxStartFlashHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    sBgFx->scaleX = 256;
    sBgFx->scaleY = 256;
    sBgFx->angle = 0;
    sBgFx->targetX = 76;
    sBgFx->targetY = 76;
    BgAnimStart(&gBgAnimDefFlash, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->update = BgFxUpdateFlashHit;
    sBgFx->timer = 0;
}

void func_080135EC(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    sBgFx->scaleX = 128;
    sBgFx->scaleY = 128;
    sBgFx->angle = 0;
    BgAnimStart(&gBgAnimDefFlash, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->update = BgFxUpdateFlash;
    sBgFx->timer = 0;
}

void BgFxStartSoraHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(3)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    BgAnimStart(&gBgAnimDefSoraHit, sx, sy);
    sBgFx->update = BgFxUpdateBase;
}

void BgFxStartRikuHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(3)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    BgAnimStart(&gBgAnimDefRikuHit, sx, sy);
    sBgFx->update = BgFxUpdateBase;
}

void BgFxStartLimit(s32 x, s32 y, s32 z, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;

    if (f) {
        sBgFx->scaleX = -0x100;
    }

    WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, sBgFx->z);
    BgAnimStart(&gBgAnimDefLimit, sx, sy);
    sBgFx->update = BgFxUpdateBase;
}

void BgFxStartDashRing(s32 x, s32 y, s32 z, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x + 0x400;
    sBgFx->y = y;
    sBgFx->z = z - 0x1000;

    if (f) {
        sBgFx->scaleX = -0x100;
    }

    WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, sBgFx->z);
    BgAnimStart(&gBgAnimDefDashRing, sx, sy);
    sBgFx->update = BgFxUpdateBase;
}

void BgFxStartEnemyHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    BgAnimStart(&gBgAnimDefEnemyHit, sx, sy);
    sBgFx->update = BgFxUpdateBase;
}

void BgFxStartFireHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z - 0x1000;
    sBgFx->scaleY = 0x200;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    BgAnimStart(&sBgAnimDefFireHit, sx, sy);
    sBgFx->update = BgFxUpdateBase;
}

void BgFxStartBlizzardHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    BgAnimStart(&sBgAnimDefBlizzardHit, sx, sy);
    sBgFx->update = BgFxUpdateBase;
}

void BgFxStartThunderHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    BgAnimStart(&sBgAnimDefThunderHit, sx, sy);
    sBgFx->update = BgFxUpdateBase;
}

void BgFxStartGuard(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefGuard, sx, sy);
    sBgFx->update = BgFxUpdateBase;
}

void BgFxStartPotion(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->releaseFrames = 20;
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z - 0x3000;
    WorldToScreen(&sx, &sy, x, y, z - 0x3000);
    BgAnimStart(&gBgAnimDefPotion, sx, sy);
    m4aSongNumStart(SONG_EF_POSION);
    sBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateWideThunder() {
    s16 sx;
    s16 sy;
    s16 sx2;
    s16 sy2;

    if (sBgFx->timer == 0 && BgAnimIsStopped()) {
        SetBlendAlpha(16, 16);
        sBgFx->x = gBtlWork->viewX;
        sBgFx->y = (gBtlWork->yMin + gBtlWork->yMax) << 7;
        sBgFx->z = sBgFx->targetZ;
        WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, sBgFx->z);
        sBgFx->angle = 0;
        sBgFx->releaseFrames = 20;
        sBgFx->flags |= BGFX_FLAG_IGNORE_ZOOM;
        sBgFx->scaleX = 512;
        sBgFx->scaleY = (sy << 8) / 40;

        if (sBgFx->scaleY < 384) {
            sBgFx->scaleY = 384;
        }

        switch (sBgFx->state) {
        case 0:
            ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 32, 256, 256);
            BgAnimStart(&gBgAnimDefThunder01, sx, sy);
            m4aSongNumStart(SONG_EF_THUND01);
            break;
        case 1:
            ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 256, 256, 256);
            BgAnimStart(&gBgAnimDefThunder02, sx, sy);
            m4aSongNumStart(SONG_EF_THUND02);
            break;
        case 2:
            ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 256, 256, 256);
            BgAnimStart(&gBgAnimDefThunder03, sx, sy);
            m4aSongNumStart(SONG_EF_THUND03);
            break;
        }

        sBgFx->timer = 1;
    } else if (sBgFx->timer == 1) {
        s32 t;

        WorldToScreen(&sx2, &sy2, sBgFx->x, sBgFx->y, sBgFx->z);
        t = sy2 << 8;
        sBgFx->scaleY = t / 40;

        if (sBgFx->scaleY < 384) {
            sBgFx->scaleY = 384;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->targetZ = p;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefThunder00, sx, sy);
    m4aSongNumStart(SONG_EF_THUND00);
    sBgFx->attack = q;
    sBgFx->update = BgFxUpdateWideThunder;
    sBgFx->state = a;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateEnemyDeath() {
    u16 a;
    BgAnimGetFrameState(&a, NULL);

    if (a > 3) {
        sBgFx->scaleX += 12;
        sBgFx->scaleY += 12;
        SetBlendAlpha(sBgFx->timer, 16 - sBgFx->timer);

        if (sBgFx->timer > 15) {
            BgAnimStop();
        } else {
            sBgFx->timer += 2;
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
    sBgFx->scaleX = s;
    sBgFx->scaleY = s;
    SetBgBlend(sBgFx->bg, 0, 16);
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefEnemyDeath, sx, sy);
    BgAnimSetLoopStartFrame(4);
    m4aSongNumStart(SONG_EF_MON_DEATH);
    sBgFx->update = BgFxUpdateEnemyDeath;
    sBgFx->targetY = 0;
    sBgFx->timer = 0;
}

void BgFxStartDarkDeath(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    sBgFx->scaleX = s;
    sBgFx->scaleY = s;
    SetBgBlend(sBgFx->bg, 0, 16);
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefDarkDeath, sx, sy);
    m4aSongNumStart(SONG_BTL_DARKDEAD);
    sBgFx->update = BgFxUpdateBase;
    sBgFx->targetY = 0;
    sBgFx->timer = 0;
}

void BgFxStartEnemySpawn(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    sBgFx->scaleX = s;
    sBgFx->scaleY = s;
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefEnemySpawn, sx, sy);
    sBgFx->update = BgFxUpdateBase;
    sBgFx->targetY = 0;
    sBgFx->timer = 0;
}

void BgFxStartDarkDeathBlend(s32 x, s32 y, s32 s, u16 b, u16 c) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    sBgFx->scaleX = s;
    sBgFx->scaleY = s;
    SetBgBlend(sBgFx->bg, b, c);
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = -0x1000;
    WorldToScreen(&sx, &sy, x, y, -0x1000);
    BgAnimStart(&gBgAnimDefDarkDeath, sx, sy);
    m4aSongNumStart(SONG_BTL_DARKDEAD);
    sBgFx->update = BgFxUpdateBase;
    sBgFx->targetY = 0;
    sBgFx->timer = 0;
}

void BgFxUpdateExplosion() {
    sBgFx->scaleX += 12;
    sBgFx->scaleY += 12;
    BgFxUpdateBase();
}

void BgFxStartExplosion(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefExplosion, sx, sy);
    sBgFx->update = BgFxUpdateExplosion;
    m4aSongNumStart(SONG_EF_TARU_BOMB);
    sBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxGetPosition(s32* a, s32* b, s32* c) {
    *a = sBgFx->x;
    *b = sBgFx->y;
    *c = sBgFx->z;
}

void BgFxStartSummon(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefSummon, sx, sy);
    sBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartFriendHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, z - 0x1000);
    BgAnimStart(&gBgAnimDefFriendHit, sx, sy);
    sBgFx->update = BgFxUpdateBase;
}

void BgFxUpdateFollowActor() {
    BtlObj* p = sBgFx->actor;
    sBgFx->x = p->x;
    sBgFx->y = p->y;
    sBgFx->z = p->z - 0x800;
    BgFxUpdateBase();
}

void BgFxStartActorThunder(BtlObj* p) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->actor = p;
    sBgFx->x = p->x;
    sBgFx->y = p->y;
    sBgFx->z = p->z - 0x800;
    sBgFx->scaleX = 0x133;
    sBgFx->scaleY = 0x133;
    WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, sBgFx->z);
    BgAnimStart(&gBgAnimDefThunder00, sx, sy);
    BgAnimSetLoopStartFrame(4);
    sBgFx->update = BgFxUpdateFollowActor;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateFallingThunder() {
    switch (sBgFx->state) {
    case 0:
        if (sBgFx->timer > 30) {
            sBgFx->state = 1;
        } else {
            sBgFx->timer++;
        }

        break;
    case 1:
        sBgFx->unk_3C += 64;
        sBgFx->z += sBgFx->unk_3C;

        if (sBgFx->z > 0) {
            sBgFx->z = 0;
            sBgFx->state = 2;
            sBgFx->timer = 30;
        }

        sBgFx->x += (sBgFx->targetX - sBgFx->x) >> 5;
        sBgFx->angle += 4;
        break;
    case 2:
        ApproachValue(&sBgFx->scaleX, 3, sBgFx->timer);
        ApproachValue(&sBgFx->scaleY, 3, sBgFx->timer);
        sBgFx->timer--;

        if (sBgFx->timer <= 0) {
            BgAnimStop();
            sBgFx->update = NULL;
        }

        break;
    }

    ApplyAttackBox(256, sBgFx->x, sBgFx->y, sBgFx->z, 32, 32, 32);
    BgFxUpdateBase();
}

void BgFxStartFallingThunder(s32 x, s32 y, s32 z, s32 w, s32 v) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->targetX = w;
    sBgFx->unk_3C = v;
    sBgFx->state = 0;
    sBgFx->scaleX = 0x299;
    sBgFx->scaleY = 0x299;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefThunder00, sx, sy);
    BgAnimSetLoopStartFrame(4);
    sBgFx->update = BgFxUpdateFallingThunder;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateDsdEnergy() {
    switch (sBgFx->state) {
    case 0:
        ApproachValue(&sBgFx->scaleX, sBgFx->targetX, sBgFx->steps);
        sBgFx->scaleY = sBgFx->scaleX;
        ApproachValue(&sBgFx->unk_3C, 0x1000, sBgFx->steps);
        SetBlendAlpha(16, sBgFx->unk_3C >> 8);
        sBgFx->steps--;

        if (sBgFx->steps <= 0) {
            sBgFx->timer = 0;
            sBgFx->state = 1;
        }

        break;
    case 1:
        if (sBgFx->endSignals != 0) {
            sBgFx->state = 2;
            sBgFx->timer = 0;
            sBgFx->steps = 16;
        }

        break;
    case 2:
        ApproachValue(&sBgFx->unk_3C, 0, sBgFx->steps);
        SetBlendAlpha(16, sBgFx->unk_3C >> 8);
        sBgFx->steps--;

        if (sBgFx->steps <= 0) {
            sBgFx->timer = 0;
            sBgFx->state = 3;
            BgAnimStop();
        }

        break;
    }

    sBgFx->angle += sBgFx->unk_0C;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->state = 0;
    sBgFx->scaleX = w;
    sBgFx->scaleY = w;
    sBgFx->targetX = w;
    sBgFx->unk_3C = 0;
    sBgFx->endSignals = 0;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&sUnk_09EDAAE0, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->update = BgFxUpdateDsdEnergy;
    sBgFx->steps = a;
    sBgFx->unk_0C = b;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->state = 0;
    sBgFx->scaleX = w;
    sBgFx->scaleY = w;
    sBgFx->targetX = w;
    sBgFx->unk_3C = 0;
    sBgFx->endSignals = 0;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&sBgAnimDefDarkGlow, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->update = BgFxUpdateDsdEnergy;
    sBgFx->steps = a;
    sBgFx->unk_0C = b;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void func_08014654() {
    u16 t;
    s16 u;
    sBgFx->scaleX += 25;
    sBgFx->scaleY += 25;
    BgFxUpdateBase();
    t = sBgFx->timer;

    if (sBgFx->timer > 3) {
        u = t - 3;
        SetBlendAlpha(16, 16 - u);

        if (u > 15) {
            BgAnimStop();
        }
    }

    sBgFx->timer++;
}

void func_080146A8(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z - 0x1000;
    WorldToScreen(&sx, &sy, x, y, 0);
    sBgFx->scaleX = 512;
    sBgFx->scaleY = 768;
    sBgFx->angle = 0;
    BgAnimStart(&gBgAnimDefFlash, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->update = func_08014654;
    sBgFx->timer = 0;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxAddPosition(s32 a, s32 b, s32 c) {
    sBgFx->x += a;
    sBgFx->y += b;
    sBgFx->z += c;
}

void BgFxSetPosition(s32 a, s32 b, s32 c) {
    sBgFx->x = a;
    sBgFx->y = b;
    sBgFx->z = c;
}

void BgFxSignalEnd(u8 bit) {
    sBgFx->endSignals |= 1 << bit;
}

void BgFxSetTarget(s32 a, s32 b, s32 c) {
    sBgFx->targetX = a;
    sBgFx->targetY = b;
    sBgFx->targetZ = c;
}

void BgFxSetAngle(u8 a) {
    sBgFx->angle = a;
}

void BgFxSetScale(s32 a, s32 b) {
    sBgFx->scaleX = a;
    sBgFx->scaleY = b;
}

void BgFxStartGroundImpact(s32 x, s32 y) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    SetBgBlend(sBgFx->bg, 5, 16);
    sBgFx->x = x;
    sBgFx->y = y;
    WorldToScreen(&sx, &sy, x, y, 0);
    BgAnimStart(&gBgAnimDefGroundImpact, sx, sy);
    sBgFx->update = BgFxUpdateBase;
    sBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxUpdateStop() {
    switch (sBgFx->state) {
    case 0:
#ifdef VERSION_EU
        if (sBgFx->timer == 20) {
#else
        if (sBgFx->timer == 21) {
#endif
            ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 16, 16, 48);
        }

        break;
    case 1:
#ifdef VERSION_EU
        if (sBgFx->timer == 20) {
#else
        if (sBgFx->timer == 25) {
#endif
            ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 24, 24, 48);
        }

        break;
    case 2:
        if (sBgFx->timer == 33) {
            ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 32, 32, 48);
        }

        break;
    }

    sBgFx->timer++;
    BgFxUpdateBase();
}

void BgFxStartStop(u16 a, s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->releaseFrames = 20;
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->attack = w;
    sBgFx->state = a;
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

    sBgFx->update = BgFxUpdateStop;
}

void BgFxStartCharaDefeat(s32 x, s32 y) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    WorldToScreen(&sx, &sy, x, y, 0);
    BgAnimStart(&gBgAnimDefCharaDefeat, sx, sy);
    BgAnimSetLoopStartFrame(8);
    sBgFx->update = BgFxUpdateBase;
    sBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxStartHumDefeat(s32 x, s32 y) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    WorldToScreen(&sx, &sy, x, y, 0);
    BgAnimStart(&gBgAnimDefHumDefeat, sx, sy);
    BgAnimSetLoopStartFrame(7);
    sBgFx->update = BgFxUpdateBase;
    sBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxStartBossDeath(s32 x, s32 y) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    WorldToScreen(&sx, &sy, x, y, 0);
    m4aSongNumStart(SONG_BTL_GF_LOOP);
    BgAnimStart(&gBgAnimDefBossDeath, sx, sy);
    BgAnimSetLoopStartFrame(4);
    sBgFx->update = BgFxUpdateBase;
    sBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxStartCharaDefeatEnd(s32 x, s32 y) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    WorldToScreen(&sx, &sy, x, y, 0);
    BgAnimStart(&gBgAnimDefCharaDefeatEnd, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->update = BgFxUpdateBase;
    sBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxUpdateGravity() {
    s16 sx;
    s16 sy;
    s16 t;
    u8 r;

    t = sBgFx->timer % 8;

    if (t <= 3) {
        SetBlendAlpha(t, 16);
    } else {
        SetBlendAlpha(8 - t, 16);
    }

    if (sBgFx->steps == 0 && BgAnimIsStopped()) {
        sBgFx->x = sBgFx->targetX;
        sBgFx->y = sBgFx->targetY;
        sBgFx->z = sBgFx->targetZ;
        WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->x, sBgFx->z);
        sBgFx->angle = 0;
        sBgFx->releaseFrames = 20;

        switch (sBgFx->state) {
        case 0:
            sBgFx->targetX = 128;
            sBgFx->targetY = 128;
            BgAnimStart(&gBgAnimDefGravity01, sx, sy);
            break;
        case 1:
            sBgFx->targetX = 256;
            sBgFx->targetY = 256;
            BgAnimStart(&gBgAnimDefGravity01, sx, sy);
            break;
        case 2:
        default:
            sBgFx->targetX = 512;
            sBgFx->targetY = 512;
            BgAnimStart(&gBgAnimDefGravity01, sx, sy);
            break;
        }

        if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
            sBgFx->targetX = -sBgFx->targetX;
        }

        m4aSongNumStart(SONG_EF_GRABI01);
        sBgFx->steps++;
    } else if (sBgFx->steps == 1) {
        if (sBgFx->timer <= 29) {
            ApproachValue(&sBgFx->scaleX, sBgFx->targetX, 30 - sBgFx->timer);
            ApproachValue(&sBgFx->scaleY, sBgFx->targetY, 30 - sBgFx->timer);
        }

        if (sBgFx->timer == 35) {
            switch (sBgFx->state) {
            case 0:
                r = ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 24, 12, 256);
                break;
            case 1:
                r = ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 40, 20, 256);
                break;
            case 2:
            default:
                r = ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 80, 40, 256);
                break;
            }

            if (r) {
                m4aSongNumStart(SONG_EF_GRABI02);
            }
        }

        sBgFx->timer++;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->targetX = p;
    sBgFx->targetY = q;
    sBgFx->targetZ = r;
    sBgFx->attack = w;

    if (f) {
        sBgFx->scaleX = -sBgFx->scaleX;
        sBgFx->flags |= BGFX_FLAG_FLIP_X;
    }

    sBgFx->steps = 0;
    WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, sBgFx->z);
    BgAnimStart(&gBgAnimDefGravity00, sx, sy);
    m4aSongNumStart(SONG_EF_GRABI00);
    sBgFx->state = a;
    sBgFx->update = BgFxUpdateGravity;
}

void BgFxUpdateGravityStrike() {
    s16 t = sBgFx->timer % 8;

    if (t <= 3) {
        SetBlendAlpha(t, 16);
    } else {
        SetBlendAlpha(8 - t, 16);
    }

    if (sBgFx->timer == 0x23) {
        if (ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 40, 20, 256)) {
            m4aSongNumStart(SONG_EF_GRABI02);
        }
    }

    BgFxUpdateBase();
    sBgFx->timer++;
}

void BgFxStartGravityStrike(s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    SetBlendAlpha(2, 16);
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->attack = w;
    sBgFx->steps = 0;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefGravity01, sx, sy);
    m4aSongNumStart(SONG_EF_GRABI01);
    sBgFx->update = BgFxUpdateGravityStrike;
}

void BgFxUpdateShockwave() {
    sBgFx->scaleX += 0x80;
    sBgFx->scaleY += 0x80;
    sBgFx->angle += 3;

    if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
        sBgFx->x += -0x300;
    } else {
        sBgFx->x += 0x300;
    }

    BgFxUpdateBase();
    SetBlendAlpha(16, 8 - sBgFx->steps);

    if (sBgFx->steps > 7) {
        BgAnimStop();
    }

    if (sBgFx->timer % 5 == 0) {
        sBgFx->steps++;
    }

    sBgFx->timer++;
}

void BgFxStartShockwave(s32 x, s32 y, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y - 0x1000;
    SetBlendAlpha(16, 8);

    if (f) {
        sBgFx->flags |= BGFX_FLAG_FLIP_X;
    }

    WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, 0);
    sBgFx->scaleX = 128;
    sBgFx->scaleY = 128;
    sBgFx->angle = 0;
    sBgFx->steps = 0;
    BgAnimStart(&gBgAnimDefFlash, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->update = BgFxUpdateShockwave;
    sBgFx->timer = 0;
    sBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxUpdateGas() {
    if (sBgFx->timer > 19) {
        sBgFx->steps = (sBgFx->timer - 20) / 2;
        SetBlendAlpha(16, 16 - sBgFx->steps);

        if (sBgFx->steps > 15) {
            BgAnimStop();
        }
    }

    sBgFx->timer++;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->scaleX = 0x100;
    sBgFx->scaleY = 0x100;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefGas, sx, sy);
    sBgFx->update = BgFxUpdateGas;
    m4aSongNumStart(SONG_EF_BFG_GASS);

    if (!f) {
        sBgFx->flags |= BGFX_FLAG_FLIP_X;
    }

    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
    BgAnimSetLoopStartFrame(3);
}

void BgFxUpdateFadeInOut() {
    switch (sBgFx->state) {
    case 0:
        SetBlendAlpha(16, sBgFx->timer);

        if (sBgFx->timer > 15) {
            sBgFx->timer = 0;
            sBgFx->state = 1;
        } else {
            sBgFx->timer++;
        }

        break;
    case 1:
        if (sBgFx->timer > sBgFx->steps) {
            sBgFx->timer = 0;
            sBgFx->state = 2;
        } else {
            sBgFx->timer++;
        }

        break;
    case 2:
        SetBlendAlpha(16, 16 - sBgFx->timer);

        if (sBgFx->timer > 15) {
            BgAnimStop();
        } else {
            sBgFx->timer++;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    sBgFx->scaleX = s;
    sBgFx->scaleY = s;
    sBgFx->state = 0;
    sBgFx->steps = 30;
    BgAnimStart(&gBgAnimDefBoogieKaihuku, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->update = BgFxUpdateFadeInOut;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateBossDeathFlash() {
    switch (sBgFx->state) {
    case 0:
        if (sBgFx->timer > 30) {
            FadeStartOut(FADE_MODE_ADD_WHITE, 60);
            FadeLock();
            sBgFx->timer = 0;
            sBgFx->state = 1;
        } else {
            sBgFx->timer++;
        }

        break;
    case 1:
        if (!FadeIsActive()) {
            BgAnimStop();
            FadeStartIn(FADE_MODE_ADD_WHITE, 120);
            FadeLock();
            sBgFx->update = NULL;
            sBgFx->flags &= ~BGFX_FLAG_ACTIVE;
        }

        break;
    }

    BgAnimSetTransform(0, sBgFx->scaleX, sBgFx->scaleY);
    sBgFx->scaleX += 20;
    sBgFx->scaleY += 20;
}

void BgFxStartBossDeathFlash() {
    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->state = 0;
    sBgFx->scaleX = 0x19;
    sBgFx->scaleY = 0x19;
    BgAnimStart(&gBgAnimDefGlow, 0x78, 0x50);
    BgAnimSetLoopStartFrame(0);
    m4aSongNumStart(SONG_EF_DBOSS_DEAD);
    sBgFx->update = BgFxUpdateBossDeathFlash;
    sBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxUpdatePcShot() {
    s16 t;
    s16 u;

    switch (sBgFx->state) {
    case 0:
        t = sBgFx->timer;
        SetBlendAlpha(16, t);
        ApproachValueHalfSteps(&sBgFx->scaleX, 0x100, 17 - t);
        sBgFx->scaleY = sBgFx->scaleX;

        if (t > 15) {
            sBgFx->timer = sBgFx->steps;
            sBgFx->state = 1;
        } else {
            sBgFx->timer++;
        }

        break;
    case 1:
        ApproachValue(&sBgFx->x, sBgFx->targetX, sBgFx->timer);
        ApproachValue(&sBgFx->y, sBgFx->targetY, sBgFx->timer);
        ApproachValue(&sBgFx->z, sBgFx->targetZ, sBgFx->timer);
        ApproachValue(&sBgFx->scaleX, sBgFx->unk_3C, sBgFx->timer);
        sBgFx->scaleY = sBgFx->scaleX;
        u = (sBgFx->scaleX * 3) >> 6;

        if (sBgFx->timer <= 0) {
            sBgFx->timer = 0;
            sBgFx->state = 2;
        } else if (ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, u, u, u)) {
            m4aSongNumStart(SONG_BTL_AN_WAVEHIT);
            sBgFx->timer = 0;
            sBgFx->state = 2;
        } else {
            sBgFx->timer--;
        }

        break;
    case 2:
        t = sBgFx->timer;
        SetBlendAlpha(16, 16 - t);

        if (t > 15) {
            BgAnimStop();
        } else {
            sBgFx->scaleX += 7;
            sBgFx->scaleY += 7;
            sBgFx->z -= sBgFx->scaleX;
            sBgFx->timer++;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->targetX = p;
    sBgFx->targetY = q;
    sBgFx->targetZ = r;
    sBgFx->steps = a;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefPcShot, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->scaleX = 25;
    sBgFx->scaleY = 25;
    sBgFx->update = BgFxUpdatePcShot;
    sBgFx->state = 0;
    sBgFx->attack = s;
    sBgFx->unk_3C = t;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartThunderStrike(s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;
    s32 t;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    t = sy << 8;
    sBgFx->scaleX = 384;
    sBgFx->scaleY = t / 40;

    if (sBgFx->scaleY < 384) {
        sBgFx->scaleY = 384;
    }

    BgAnimStart(&gBgAnimDefThunder01, sx, sy);
    m4aSongNumStart(SONG_EF_THUND01);
    ApplyAttackBox(w, sBgFx->x, sBgFx->y, sBgFx->z, 16, 16, 256);
    sBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateThunder() {
    s16 sx;
    s16 sy;
    s16 sx2;
    s16 sy2;

    if (sBgFx->timer == 0 && BgAnimIsStopped()) {
        SetBlendAlpha(16, 16);
        sBgFx->x = sBgFx->targetX;
        sBgFx->y = sBgFx->targetY;
        sBgFx->z = sBgFx->targetZ;
        WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, sBgFx->z);
        sBgFx->angle = 0;
        sBgFx->scaleX = 384;
        sBgFx->scaleY = (sy << 8) / 40;

        if (sBgFx->scaleY < 384) {
            sBgFx->scaleY = 384;
        }

        sBgFx->flags |= BGFX_FLAG_IGNORE_ZOOM;

        switch (sBgFx->state) {
        case 0:
            ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 16, 16, 256);
            BgAnimStart(&gBgAnimDefThunder01, sx, sy);
            m4aSongNumStart(SONG_EF_THUND01);
            break;
        case 1:
            ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 40, 40, 256);
            BgAnimStart(&gBgAnimDefThunder02, sx, sy);
            m4aSongNumStart(SONG_EF_THUND02);
            break;
        case 2:
            ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 64, 64, 256);
            BgAnimStart(&gBgAnimDefThunder03, sx, sy);
            m4aSongNumStart(SONG_EF_THUND03);
            break;
        }

        sBgFx->timer = 1;
    } else if (sBgFx->timer == 1) {
        s32 t;

        WorldToScreen(&sx2, &sy2, sBgFx->x, sBgFx->y, sBgFx->z);
        t = sy2 << 8;
        sBgFx->scaleY = t / 40;

        if (sBgFx->scaleY < 384) {
            sBgFx->scaleY = 384;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->targetX = p;
    sBgFx->targetY = q;
    sBgFx->targetZ = r;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefThunder00, sx, sy);
    m4aSongNumStart(SONG_EF_THUND00);
    sBgFx->attack = s;
    sBgFx->update = BgFxUpdateThunder;
    sBgFx->state = a;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateDumboSplash() {
    s32 t;
    u16 v;

    switch (sBgFx->state) {
    case 0:
        if (sBgFx->timer == 0) {
            sBgFx->steps = 40;
        }

        ApproachValue(&sBgFx->unk_3C, 0x1000, sBgFx->steps);
        ApproachValue(&sBgFx->scaleX, sBgFx->targetX, sBgFx->steps);
        ApproachValue(&sBgFx->scaleY, 0x100, sBgFx->steps);
        ApproachValue(&sBgFx->angleFixed, 0, sBgFx->steps);
        sBgFx->angle = sBgFx->angleFixed >> 8;
        t = sBgFx->scaleX;

        if (t < 0) {
            t = -t;
        }

        t *= 44;

        if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
            ApplyAttackBox(sBgFx->attack, sBgFx->x + t, sBgFx->y,
                sBgFx->z, t << 8 >> 16, 24, 24);
        } else {
            ApplyAttackBox(sBgFx->attack, sBgFx->x - t, sBgFx->y,
                sBgFx->z, t << 8 >> 16, 24, 24);
        }

        SetBlendAlpha(16, sBgFx->unk_3C >> 8);

        if (--sBgFx->steps <= 0) {
            sBgFx->timer = 0;
            sBgFx->state = 1;
        } else {
            sBgFx->timer++;
        }

        break;
    case 1:
        v = sBgFx->timer;

        if (sBgFx->timer > 50) {
            sBgFx->timer = 0;
            sBgFx->state = 2;
            break;
        }

        t = sBgFx->scaleX;

        if (t < 0) {
            t = -t;
        }

        t *= 44;

        if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
            sBgFx->angleFixed = -gSineTable[(v * 4) & 0xFF] * 6;
            ApplyAttackBox(sBgFx->attack, sBgFx->x + t, sBgFx->y,
                sBgFx->z, t << 8 >> 16, 24, 24);
        } else {
            sBgFx->angleFixed = gSineTable[(v * 4) & 0xFF] * 6;
            ApplyAttackBox(sBgFx->attack, sBgFx->x - t, sBgFx->y,
                sBgFx->z, t << 8 >> 16, 24, 24);
        }

        sBgFx->angle = sBgFx->angleFixed >> 8;
        sBgFx->timer++;
        break;
    case 2:
        if (sBgFx->timer == 0) {
            sBgFx->steps = 20;
        }

        ApproachValue(&sBgFx->unk_3C, 0, sBgFx->steps);
        ApproachValue(&sBgFx->scaleY, 128, sBgFx->steps);

        if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
            ApproachValue(&sBgFx->scaleX, -128, sBgFx->steps);
            ApproachValue(&sBgFx->angleFixed, 0x800, sBgFx->steps);
        } else {
            ApproachValue(&sBgFx->scaleX, 128, sBgFx->steps);
            ApproachValue(&sBgFx->angleFixed, -0x800, sBgFx->steps);
        }

        sBgFx->angle = sBgFx->angleFixed >> 8;
        SetBlendAlpha(16, sBgFx->unk_3C >> 8);

        if (--sBgFx->steps <= 0) {
            BgAnimStop();
            sBgFx->state = 99;
        } else {
            sBgFx->timer++;
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
        sBgFx->flags |= BGFX_FLAG_FLIP_X;
    }

    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->attack = w;
    WorldToScreen(&sx, &sy, x, y, z);
    sBgFx->scaleY = 25;

    switch (a) {
    case 0:
        sBgFx->targetX = 256;
        break;
    case 1:
        sBgFx->targetX = 384;
        break;
    case 2:
        sBgFx->targetX = 512;
        break;
    }

    if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
        sBgFx->scaleX = -25;
        sBgFx->angleFixed = 2048;
        sBgFx->targetX = -sBgFx->targetX;
    } else {
        sBgFx->scaleX = 25;
        sBgFx->angleFixed = -2048;
    }

    sBgFx->state = 0;
    sBgFx->unk_3C = 0;
    BgAnimStart(&gBgAnimDefDumboSplash, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->update = BgFxUpdateDumboSplash;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void func_08015C80(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    sBgFx->scaleX = 76;
    sBgFx->scaleY = 76;
    sBgFx->targetX = 12;
    sBgFx->targetY = 12;
    BgAnimStart(&gBgAnimDefFlash, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->update = BgFxUpdateFlash;
}

void BgFxUpdateTrinityLimit() {
    if (sBgFx->timer <= 16) {
        SetBlendAlpha(16, sBgFx->timer);
        sBgFx->timer++;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->scaleX = 0x100;
    sBgFx->scaleY = 0x100;
    WorldToScreen(&sx, &sy, x, y, z);
    sBgFx->flags |= BGFX_FLAG_BELOW_SPRITES;
    SetBlendAlpha(16, 0);
    sBgFx->state = 0;
    BgAnimStart(&gBgAnimDefTrinityLimit, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->update = BgFxUpdateTrinityLimit;
}

void BgFxStartTrinityLimitCharge(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    sBgFx->scaleX = 0x200;
    sBgFx->scaleY = 0x200;
    BgAnimSetLoopStartFrame(7);
    BgAnimStart(&gBgAnimDefTrinityLimitCharge, sx, sy);
    sBgFx->update = BgFxUpdateBase;
}

void BgFxUpdateTrinityLimitBlast() {
    switch (sBgFx->state) {
    case 0: {
        s16 t = sBgFx->timer;

        if (t <= 64) {
            SetBlendAlpha(16, t >> 2);
            sBgFx->timer++;
        } else {
            sBgFx->timer = 0;
            sBgFx->state++;
        }

        sBgFx->scaleX += 25;
        sBgFx->scaleY += 25;
        break;
    }
    case 1: {
        u16 t;

        sBgFx->scaleX += 0x100;
        sBgFx->scaleY += 0x100;
        t = sBgFx->timer;

        if ((s16)t > 32) {
            ApplyAttackBox(87, sBgFx->x, sBgFx->y, 0, 0x100, 0x100, 0x100);
            SetBattleZoom(1, 0x100, gBtlWork->x2, gBtlWork->y2);
            FadeStartIn(FADE_MODE_ADD_WHITE, 60);
            sBgFx->timer = 0;
            sBgFx->state++;
        } else {
            sBgFx->timer = t + 1;
        }

        break;
    }
    case 2: {
        u16 t = sBgFx->timer;

        if ((s16)t <= 15) {
            SetBlendAlpha(16, 16 - t);
            sBgFx->timer++;
        } else {
            BgAnimStop();
        }

        break;
    }
    }

    sBgFx->angle++;
    BgFxUpdateBase();
}

void BgFxStartTrinityLimitBlast(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    SetBlendAlpha(16, 0);
    WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, sBgFx->z);
    sBgFx->scaleX = 0x300;
    sBgFx->scaleY = 0x300;
    BgAnimStart(&gBgAnimDefTrinityLimitBlast, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->timer = 8;
    sBgFx->state = 0;
    sBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
    sBgFx->update = BgFxUpdateTrinityLimitBlast;
    FadeStartOut(FADE_MODE_ADD_WHITE, 40);
    SetBattleZoom(80, 204, x, y + z + 0x2000);
}

void BgFxUpdateRagnarokCharge() {
    if (sBgFx->timer > 0) {
        ApproachValueHalfSteps(&sBgFx->scaleX, 0x100, sBgFx->timer);
        ApproachValueHalfSteps(&sBgFx->scaleY, 0x100, sBgFx->timer);
        sBgFx->timer--;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    sBgFx->scaleX = 0x19;
    sBgFx->scaleY = 0x19;
    m4aSongNumStart(SONG_EF_RAGNA01);
    BgAnimStart(&gBgAnimDefRagnarokCharge, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->timer = 0x23;
    sBgFx->update = BgFxUpdateRagnarokCharge;
}

void BgFxUpdateRagnarokShot() {
    u16 k;
    u16 v;
    s16 t;

    BgAnimGetFrameState(&k, &v);

    switch (k) {
    case 4:
        ApplyAttackBox(91, sBgFx->x + sBgFx->scaleX * 40, sBgFx->y, sBgFx->z, 32, 32, 50);
        break;
    case 5:
        if (v == 0) {
            sBgFx->state = 1;
        }

        break;
    case 6:
        if (v == 0) {
            sBgFx->state = 2;
        }

        break;
    }

    switch (sBgFx->state) {
    case 1:
        sBgFx->unk_3C += 51;

        if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
            sBgFx->x -= sBgFx->unk_3C;
        } else {
            sBgFx->x += sBgFx->unk_3C;
        }

        break;
    case 2:
        sBgFx->unk_3C += 51;

        if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
            sBgFx->x -= sBgFx->unk_3C;
            sBgFx->scaleX -= 51;
        } else {
            sBgFx->x += sBgFx->unk_3C;
            sBgFx->scaleX += 51;
        }

        ApplyAttackBox(91, sBgFx->x + sBgFx->scaleX * 40, sBgFx->y, sBgFx->z, 32, 32, 50);

        if (sBgFx->timer > 20) {
            t = 36 - sBgFx->timer;
            SetBlendAlpha(16, t);

            if (t <= 0) {
                BgAnimStop();
            }
        }

        sBgFx->timer++;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    sBgFx->state = 0;

    if (f) {
        sBgFx->flags |= BGFX_FLAG_FLIP_X;
        sBgFx->scaleX = -0x100;
    }

    sBgFx->unk_3C = 0;
    m4aSongNumStart(SONG_EF_RAGNA02);
    BgAnimStart(&gBgAnimDefRagnarokShot, sx, sy);
    BgAnimSetLoopStartFrame(6);
    sBgFx->update = BgFxUpdateRagnarokShot;
}

void BgFxStartGlow(s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefGlow, sx, sy);
    sBgFx->scaleX = w;
    sBgFx->scaleY = w;
    sBgFx->update = BgFxUpdateFadeOut;
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

    switch (sBgFx->state) {
    case 0:
        sBgFx->scaleX = (gSineTable[((u16)sBgFx->timer * 4) & 0xFF] >> 3) + 89;

        if (sBgFx->steps > 0) {
            ApproachValueHalfSteps(&sBgFx->z, sBgFx->targetZ - 0x2000, sBgFx->steps);
            sBgFx->steps--;
        } else {
            sBgFx->state = 1;
            sBgFx->steps = 60;
        }

        break;
    case 1:
        sBgFx->scaleX = (gSineTable[((u16)sBgFx->timer * 4) & 0xFF] >> 3) + 89;
        sBgFx->steps--;

        if (sBgFx->steps <= 0) {
            sBgFx->state = 2;
            sBgFx->steps = 50;
        }

        break;
    case 2:
        sBgFx->scaleX = (gSineTable[((u16)sBgFx->timer * 4) & 0xFF] >> 3) + 89;
        o = BgFxGetSyncTarget();

        if (o != NULL) {
            ApproachValueHalfSteps(&sBgFx->x, o->x, sBgFx->steps);
            ApproachValueHalfSteps(&sBgFx->y, o->y, sBgFx->steps);
            ApproachValueHalfSteps(&sBgFx->z, o->z - (o->centerHeight << 8), sBgFx->steps);
        }

        sBgFx->steps--;

        if (o != NULL) {
            if (sBgFx->steps > 0) {
                break;
            }

            BgFxApplySyncHp(o->hp);
        }

        sBgFx->state = 3;
        m4aSongNumStart(SONG_EF_SYNC2);
        sBgFx->steps = 16;
        break;
    case 3:
        sBgFx->scaleX += 166;
        sBgFx->scaleY = sBgFx->scaleX;
        SetBlendAlpha(16, sBgFx->steps);
        sBgFx->steps--;

        if (sBgFx->steps <= 0) {
            BgAnimStop();
        }

        break;
    }

    sBgFx->scaleY = sBgFx->scaleX;
    sBgFx->timer++;
    BgFxUpdateBase();
}

void BgFxStartSync(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->targetZ = z;
    sBgFx->state = 0;
    sBgFx->steps = 50;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefGlow, sx, sy);
    sBgFx->scaleX = 89;
    sBgFx->scaleY = 89;
    sBgFx->update = BgFxUpdateSync;
    m4aSongNumStart(SONG_EF_SYNC1);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartStunImpact(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefStunImpact, sx, sy);
    sBgFx->scaleX = 0x200;
    sBgFx->scaleY = 0x200;
    sBgFx->update = BgFxUpdateBase;
}

void BgFxUpdateZantetsuken() {
    sBgFx->scaleX += sBgFx->targetX;
    sBgFx->scaleY += sBgFx->targetY;
    BgFxUpdateBase();

    if (sBgFx->timer > 5) {
        s16 t = sBgFx->timer - 5;
        SetBlendAlpha(16, 16 - t);

        if (t > 15) {
            BgAnimStop();
        }
    }

    sBgFx->timer++;
}

void BgFxStartZantetsuken(s32 x, s32 y, s32 z, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefGlow, sx, sy);
    sBgFx->scaleX = 38;
    sBgFx->scaleY = 256;
    sBgFx->targetX = 7;
    sBgFx->targetY = 153;

    if (f) {
        sBgFx->angle += 40;
    } else {
        sBgFx->angle -= 40;
    }

    sBgFx->update = BgFxUpdateZantetsuken;
}

void BgFxUpdateUrsulaBeam() {
    switch (sBgFx->state) {
    case 0:
        SetBlendAlpha(16, (sBgFx->timer >> 1) + 8);
        ApproachValueHalfSteps(&sBgFx->scaleX, sBgFx->targetX, 17 - sBgFx->timer);
        ApproachValueHalfSteps(&sBgFx->scaleY, sBgFx->targetY, 17 - sBgFx->timer);

        if (sBgFx->timer > 15) {
            sBgFx->timer = 0;
            sBgFx->state = 1;
        } else {
            sBgFx->timer++;
        }

        break;
    case 1:
        if (sBgFx->timer > sBgFx->steps) {
            sBgFx->timer = 0;
            sBgFx->state = 2;
        } else {
            sBgFx->timer++;
        }

        break;
    case 2:
        SetBlendAlpha(16, 16 - sBgFx->timer);

        if (sBgFx->timer > 15) {
            BgAnimStop();
        } else {
            sBgFx->timer++;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->steps = a;
    sBgFx->state = 0;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefUrsulaBeam, sx, sy);

    if (f) {
        sBgFx->targetX = w;
        sBgFx->scaleX = 76;
    } else {
        sBgFx->targetX = -w;
        sBgFx->scaleX = -76;
    }

    sBgFx->targetY = w;
    sBgFx->scaleY = 76;
    m4aSongNumStart(SONG_EF_UR_BEEM);
    sBgFx->update = BgFxUpdateUrsulaBeam;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartAnsemRush(s32 x, s32 y, s32 z, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->state = 0;
    sBgFx->steps = 45;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefAnsemRush, sx, sy);

    if (f) {
        sBgFx->scaleX = -0x100;
    } else {
        sBgFx->scaleX = 0x100;
    }

    sBgFx->scaleY = 0x100;
    sBgFx->update = BgFxUpdateFadeInOut;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateAnsemWave() {
    if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
        sBgFx->x += 0x700;
    } else {
        sBgFx->x += -0x700;
    }

    if (sBgFx->x < (gBtlWork->xMin - 0x40) << 8 || sBgFx->x > (gBtlWork->xMax + 0x40) << 8) {
        BgAnimStop();
    } else if (ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 16, 16, 48)) {
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->attack = w;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefAnsemWave, sx, sy);

    if (f) {
        sBgFx->scaleX = 0x100;
    } else {
        sBgFx->scaleX = -0x100;
        sBgFx->flags |= BGFX_FLAG_FLIP_X;
    }

    sBgFx->scaleY = 0x100;
    m4aSongNumStart(SONG_EF_AN_WAVE);
    sBgFx->update = BgFxUpdateAnsemWave;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void func_08016BCC(s32 x, s32 y) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    WorldToScreen(&sx, &sy, x, y, 0);
    BgAnimStart(&gBgAnimDefFriendHit, sx, sy);
    sBgFx->scaleX = 0x900;
    sBgFx->scaleY = 0x900;
    sBgFx->update = BgFxUpdateBase;
}

void BgFxStartJfMajinBeam(s32 x, s32 y, s32 z, s32 w, u8 f, u16 a) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->steps = a;
    sBgFx->state = 0;
    sBgFx->angle = f;
    WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, sBgFx->z);
    BgAnimStart(&gBgAnimDefJfMajinBeam, sx, sy);
    sBgFx->scaleY = w;
    sBgFx->update = BgFxUpdateFadeInOut;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
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

    if (sBgFx->timer > 0) {
        if (a > 7) {
            ang = sBgFx->angle;

            if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
                ApproachAngle(&ang, GetAngle(sBgFx->x, sBgFx->y,
                                             sBgFx->targetX, sBgFx->targetY) + 64, 5);
            } else {
                ApproachAngle(&ang, GetAngle(sBgFx->x, sBgFx->y,
                                             sBgFx->targetX, sBgFx->targetY) - 64, 5);
            }

            sBgFx->angle = ang;
            ApproachValue(&sBgFx->x, sBgFx->targetX, sBgFx->timer);
            ApproachValue(&sBgFx->y, sBgFx->targetY, sBgFx->timer);
            ApproachValue(&sBgFx->z, sBgFx->targetZ, sBgFx->timer);

            if (TestAttackBox(sBgFx->x, sBgFx->y, sBgFx->z,
                              8, 8, 16)) {
                sBgFx->timer = -1;
            } else {
                sBgFx->timer--;
            }
        } else if (a > 2) {
            if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
                dx = ((7 - a) << 8) * 7;
            } else {
                s32 t = 7 - a;
                t *= 256;
                dx = t * -7;
            }

            if (TestAttackBox(sBgFx->x + dx, sBgFx->y,
                              sBgFx->z, 8, 8, 16)) {
                sBgFx->timer = -1;
            }
        }
    }

    switch (sBgFx->timer) {
    case 0:
        sBgFx->update = BgFxUpdateFadeOut;
        break;
    case -1:
        m4aSongNumStart(SONG_EF_DRHEET);
        SetBlendAlpha(16, 11);
        sBgFx->angle = 0;
        sBgFx->scaleX = 0x500;
        sBgFx->scaleY = 0x500;
        sBgFx->x += dx;
        sBgFx->releaseFrames = 20;
        WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y,
                      sBgFx->z);
        BgAnimStart(&gBgAnimDefExplosion, sx, sy);
        m4aSongNumStart(SONG_EF_FIRE03);
        sBgFx->timer = -2;
        sBgFx->steps = 0;
        break;
    case -2:
        if (sBgFx->steps == 7) {
            ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y,
                          sBgFx->z, 256, 256, 256);
        }

        sBgFx->scaleX += 51;
        sBgFx->scaleY += 51;
        sBgFx->steps++;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefFire00, sx, sy);
    m4aSongNumStart(SONG_EF_DRHEET);
    BgAnimSetLoopStartFrame(8);
    sBgFx->update = BgFxUpdateFireBurst;
    sBgFx->targetX = p;
    sBgFx->targetY = q;
    sBgFx->targetZ = r;
    sBgFx->timer = 15;
    sBgFx->state = 3;
    sBgFx->attack = w;

    if (f) {
        sBgFx->flags |= BGFX_FLAG_FLIP_X;
        sBgFx->scaleX = -0x100;
    }

    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartFireExplosion(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->scaleX = 0x180;
    sBgFx->scaleY = 0x180;
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefFire03, sx, sy);
    sBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateFullscreen() {
    switch (sBgFx->state) {
    case 0:
        SetBlendAlpha(16, sBgFx->timer);

        if (sBgFx->timer > 15) {
            sBgFx->timer = 0;
            sBgFx->state = 1;
        } else {
            sBgFx->timer++;
        }

        break;
    case 1:
        if (sBgFx->timer > sBgFx->steps) {
            sBgFx->timer = 0;
            sBgFx->state = 2;
        } else {
            sBgFx->timer++;
        }

        break;
    case 2:
        SetBlendAlpha(16, 16 - sBgFx->timer);

        if (sBgFx->timer > 15) {
            BgAnimStop();
            sBgFx->update = NULL;
            sBgFx->flags &= ~BGFX_FLAG_ACTIVE;
        } else {
            sBgFx->timer++;
        }

        break;
    }
}

void BgFxStartXmas(u16 a) {
    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->steps = a;
    sBgFx->state = 0;
    BgAnimStart(&gBgAnimDefXmas, 120, 80);
    sBgFx->update = BgFxUpdateFullscreen;
    BgAnimSetLoopStartFrame(0);
    sBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxUpdateVixenIceFall() {
    u16 t;
    s32 w;
    t = (gSineTable[(sBgFx->unk_0C / 3) & 0xFF] * 10240) >> 16;
    w = ((abs(gSineTable[(u8)sBgFx->unk_0C]) >> 1) + 0x100) * 0x133 >> 8;
    BgAnimSetTransform(t + 15, 0x133, w);
    BgFxUpdateFullscreen();
    sBgFx->unk_0C++;
}

void BgFxStartVixenIceFall(u16 a) {
    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->steps = a;
    sBgFx->unk_0C = 0;
    sBgFx->state = 0;
    BgAnimStart(&gBgAnimDefVixenIceFall, 120, 80);
    BgAnimSetTransform(10, 0x133, 0x133);
    sBgFx->update = BgFxUpdateVixenIceFall;
    BgAnimSetLoopStartFrame(0);
    sBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
}

void BgFxStartFlame(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->scaleX = s;
    sBgFx->scaleY = s;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefFlame, sx, sy);
    sBgFx->update = BgFxUpdateBase;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartFrost(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->scaleX = s;
    sBgFx->scaleY = s;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefFrost, sx, sy);
    sBgFx->update = BgFxUpdateBase;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartUrsulaThunder(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefUrsulaThunder, sx, sy);
    sBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
}

void BgFxUpdateHoly() {
    if (sBgFx->unk_0C > 0) {
        ApproachValueHalfSteps(&sBgFx->scaleX, 0x200, sBgFx->unk_0C);
        sBgFx->unk_0C--;
    }

    if (sBgFx->scaleYSteps > 0) {
        ApproachValue(&sBgFx->scaleY, 0x180, sBgFx->scaleYSteps);
        sBgFx->scaleYSteps--;
    }

    switch (sBgFx->state) {
    case 0: {
        u16 t;

        SetBlendAlpha(16, sBgFx->timer);
        t = sBgFx->timer;

        if ((s16)t > 15) {
            sBgFx->timer = 0;
            sBgFx->state = 1;
        } else {
            sBgFx->timer = t + 1;
        }

        break;
    }
    case 1: {
        u16 t;

        ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 32, 16, 256);
        t = sBgFx->timer;

        if ((s16)t > sBgFx->steps) {
            sBgFx->timer = 0;
            sBgFx->state = 2;
        } else {
            sBgFx->timer = t + 1;
        }

        break;
    }
    case 2: {
        u16 a = sBgFx->timer;
        u16 t;

        SetBlendAlpha(16, 16 - ((s16)a >> 1));
        ApproachValue(&sBgFx->scaleX, 10, 33 - sBgFx->timer);
        t = sBgFx->timer;

        if ((s16)t > 31) {
            BgAnimStop();
        } else {
            sBgFx->timer = t + 1;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->steps = 120;
    sBgFx->unk_0C = 60;
    sBgFx->scaleYSteps = 20;
    sBgFx->state = 0;
    sBgFx->attack = w;
    sBgFx->scaleX = 10;
    sBgFx->scaleY = 10;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefLightPillar, sx, sy);
    sBgFx->update = BgFxUpdateHoly;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
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

    dx = b->x - sBgFx->x;

    if (dx >= 0 ? dx <= 0x4FFF : sBgFx->x - b->x <= 0x4FFF) {
        dy = b->y - sBgFx->y;

        if (dy >= 0 ? dy <= 0x27FF : sBgFx->y - b->y <= 0x27FF) {
            if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
                h = b->knockbackSpeed - ((sBgFx->x - b->x) >> 1);
            } else {
                h = b->knockbackSpeed + ((sBgFx->x - b->x) >> 1);
            }

            if (h > 0) {
                h = 0;
            }

            t = -(h >> 9);
            nx = sBgFx->x + gSineTable[(b->angle + c) & 0xFF] * (s16)t;
            ny = sBgFx->y + -gSineTable[((b->angle + c) & 0xFF) + 64] * ((s16)t >> 1);

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

    switch (sBgFx->state) {
    case 0:
        v = 17 - sBgFx->timer;

        if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
            ApproachValueHalfSteps(&sBgFx->scaleX, -0x100, v);
        } else {
            ApproachValueHalfSteps(&sBgFx->scaleX, 0x100, v);
        }

        ApproachValueHalfSteps(&sBgFx->scaleY, 0x100, v);
        SetBlendAlpha(16, sBgFx->timer);

        if (sBgFx->timer > 15) {
            sBgFx->timer = 0;
            sBgFx->state = 1;
        } else {
            sBgFx->timer++;
        }

        break;
    case 1:
        u = (u16)sBgFx->timer;
        sBgFx->scaleY = abs(gSineTable[(u8)sBgFx->timer] >> 1) + 0x100;

        if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
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

        if (sBgFx->timer > sBgFx->steps) {
            sBgFx->timer = 0;
            sBgFx->state = 2;
            ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y,
                          sBgFx->z, 40, 20, 256);
        } else {
            sBgFx->timer++;
        }

        break;
    case 2:
        alpha = 16;
        v = sBgFx->timer;
        u = v;
        alpha -= u;
        SetBlendAlpha(16, alpha);

        if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
            ApproachValue(&sBgFx->scaleX, -10, 17 - u);
        } else {
            ApproachValue(&sBgFx->scaleX, 10, 17 - u);
        }

        ApproachValue(&sBgFx->scaleY, 768, 17 - v);

        if (v > 15) {
            BgAnimStop();
        } else {
            sBgFx->timer++;
        }

        break;
    }

    if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
        sBgFx->x -= 102;
    } else {
        sBgFx->x += 102;
    }

    sBgFx->unk_3C = 0;
    ApplyBattleBounds(&sBgFx->x, &sBgFx->y, &sBgFx->z,
                  &sBgFx->unk_3C);
    ClampBattlePosition(&sBgFx->x, &sBgFx->y, -16, 0);
    BgFxUpdateBase();
}

void BgFxStartTornado(s32 x, s32 y, s32 z, s32 w, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->steps = 220;
    sBgFx->unk_0C = 0;
    sBgFx->state = 0;
    sBgFx->attack = w;
    sBgFx->scaleY = 10;

    if (f) {
        sBgFx->scaleX = -10;
        sBgFx->flags |= BGFX_FLAG_FLIP_X;
    } else {
        sBgFx->scaleX = 10;
    }

    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefTornado, sx, sy);
    sBgFx->update = BgFxUpdateTornado;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateBind() {
    s16 v;
    s16 w;

    switch (sBgFx->state) {
    case 0:
        sBgFx->scaleX += 0x80;

        if (sBgFx->timer > 60) {
            sBgFx->timer = 0;
            sBgFx->state = 1;
        } else {
            sBgFx->timer++;
        }

        break;
    case 1:
        v = sBgFx->timer;
        SetBlendAlpha(16, v + 8);

        if (v > 7) {
#ifdef VERSION_EU
            ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y + 0x1000, 0, 0x100, 0x100, 0x100);
#else
            ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y + 0x1000, 0, 0x100, 0x100, 8);
#endif
            sBgFx->timer = 0;
            sBgFx->state = 2;
        } else {
            sBgFx->timer++;
        }

        break;
    case 2:
        w = sBgFx->timer >> 2;
        SetBlendAlpha(16, 16 - w);

        if (w > 15) {
            BgAnimStop();
        } else {
            sBgFx->timer++;
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
    sBgFx->x = x;
    sBgFx->y = gBtlWork->yMin << 8;
    sBgFx->z = 0;
    sBgFx->attack = w;
    sBgFx->scaleX = 10;
    sBgFx->scaleY = -((gBtlWork->yMax - gBtlWork->yMin) << 8) / 96;
    WorldToScreen(&sx, &sy, x, sBgFx->y, 0);
    BgAnimStart(&gBgAnimDefLightPillar, sx, sy);
    sBgFx->flags |= BGFX_FLAG_BELOW_SPRITES;
    sBgFx->state = 0;
    SetBlendAlpha(16, 8);
    sBgFx->update = BgFxUpdateBind;
    BgAnimSetLoopStartFrame(0);
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateAxcelFireWall() {
    switch (sBgFx->state) {
    case 0:
        ApproachValue(&sBgFx->x, sBgFx->targetX, sBgFx->steps);

        if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
            ApproachValue(&sBgFx->scaleX, -256, sBgFx->steps);
        } else {
            ApproachValue(&sBgFx->scaleX, 256, sBgFx->steps);
        }

        sBgFx->scaleY = abs(sBgFx->scaleX);
        sBgFx->steps--;

        if (sBgFx->steps <= 0) {
            sBgFx->state = 1;
            sBgFx->steps = 16;
        }

        break;
    case 1:
        if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
            if (ApplyAttackBox(sBgFx->attack, sBgFx->x - 0x1000, sBgFx->y + 0x2000, 0, 20, 32, 64) || ApplyAttackBox(sBgFx->attack, sBgFx->x + 0x1000, sBgFx->y - 0x2000, 0, 20, 32, 64)) {
                sBgFx->state = 2;
                m4aSongNumStart(SONG_EF_FIRE01);
            }
        } else if (ApplyAttackBox(sBgFx->attack, sBgFx->x - 0x1000, sBgFx->y - 0x2000, 0, 20, 32, 64)) {
            sBgFx->state = 2;
            m4aSongNumStart(SONG_EF_FIRE01);
        } else if (ApplyAttackBox(sBgFx->attack, sBgFx->x + 0x1000, sBgFx->y + 0x2000, 0, 20, 32, 64)) {
            sBgFx->state = 2;
            m4aSongNumStart(SONG_EF_FIRE01);
        }

        if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
            if (gBtlWork->actor->x < sBgFx->x) {
                sBgFx->state = 2;
            }
        } else {
            if (gBtlWork->actor->x > sBgFx->x) {
                sBgFx->state = 2;
            }
        }

        break;
    case 2:
        SetBlendAlpha(16, sBgFx->steps);

        if (sBgFx->steps <= 0) {
            BgAnimStop();
        } else {
            sBgFx->steps--;
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
    sBgFx->state = 0;
    sBgFx->x = x;
    sBgFx->y = (gBtlWork->yMin + gBtlWork->yMax) << 7;
    sBgFx->z = 0;
    sBgFx->attack = w;
    sBgFx->steps = 20;
    WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, 0);
    BgAnimStart(&gBgAnimDefAxcelFireWall, sx, sy);

    if (f) {
        sBgFx->scaleX = 10;
        sBgFx->targetX = x - 0x3700;
    } else {
        sBgFx->scaleX = -10;
        sBgFx->targetX = x + 0x3700;
        sBgFx->flags |= BGFX_FLAG_FLIP_X;
    }

    sBgFx->scaleY = 10;
    sBgFx->flags |= BGFX_FLAG_BELOW_SPRITES;
    sBgFx->update = BgFxUpdateAxcelFireWall;
    BgAnimSetLoopStartFrame(0);
}

void BgFxUpdateGround() {
    u16 k;
    u16 t;
    ApproachValue(&sBgFx->scaleX, 0x300, sBgFx->steps);
    sBgFx->scaleY = sBgFx->scaleX;
    sBgFx->steps--;
    BgAnimGetFrameState(&k, NULL);

    if (k <= 4) {
        t = (sBgFx->scaleX * 5) >> 5;

        if (ApplyAttackBox(0x13D, sBgFx->x, sBgFx->y, sBgFx->z, t, (s16)t >> 1, 1)) {
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->attack = w;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefMahluxiaGround, sx, sy);
    sBgFx->scaleX = 0x80;
    sBgFx->scaleY = 0x80;
    sBgFx->steps = BgAnimGetDuration(BgAnimGetCurrent());
    sBgFx->flags |= BGFX_FLAG_BELOW_SPRITES;
    sBgFx->update = BgFxUpdateGround;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartLexceusGround(s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->attack = w;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&sBgAnimDefLexceusGround, sx, sy);
    sBgFx->scaleX = 0x80;
    sBgFx->scaleY = 0x80;
    sBgFx->steps = BgAnimGetDuration(BgAnimGetCurrent());
    sBgFx->flags |= BGFX_FLAG_BELOW_SPRITES;
    sBgFx->update = BgFxUpdateGround;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateHanabira() {
    switch (sBgFx->state) {
    case 0:
        if (sBgFx->timer > 50) {
            sBgFx->timer = 0;
            sBgFx->state = 1;
        } else {
            sBgFx->timer++;
        }

        break;
    case 1:
        sBgFx->timer = 0;
        sBgFx->state = 2;

        if (ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 0x100, 0x100, 0x100)) {
            m4aSongNumStart(SONG_BTL_ETC_HIT05);
        }

        break;
    case 2:
        SetBlendAlpha(16, 16 - sBgFx->timer);

        if (sBgFx->timer > 15) {
            BgAnimStop();
        } else {
            sBgFx->timer++;
        }

        break;
    }

    sBgFx->targetX += 30;
    sBgFx->angle += sBgFx->targetX >> 8;
    sBgFx->scaleX += 10;
    sBgFx->scaleY = sBgFx->scaleX;
    BgFxUpdateBase();
}

void BgFxStartHanabira(s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->attack = w;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefHanabira, sx, sy);
    sBgFx->state = 0;
    sBgFx->scaleX = 5;
    sBgFx->scaleY = 5;
    sBgFx->targetX = 256;
    sBgFx->flags |= BGFX_FLAG_ABOVE_SPRITES;
    m4aSongNumStart(SONG_EF_MARL_HANABIRA);
    sBgFx->update = BgFxUpdateHanabira;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateKama() {
    if (gBtlWork->hitStop != 0) {
        BgFxUpdateBase();
        return;
    }

    if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
        sBgFx->angle += 3;
    } else {
        sBgFx->angle -= 3;
    }

    sBgFx->x = sBgFx->targetX + ((gSineTable[sBgFx->angle] * sBgFx->unk_3C) >> 8);
    sBgFx->z = sBgFx->targetZ + ((-gSineTable[sBgFx->angle + 64] * sBgFx->unk_3C) >> 8);

    if (ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, 10, 5, 72)) {
        m4aSongNumStart(SONG_BTL_MARL_EFEHIT);
    }

    switch (sBgFx->state) {
    case 0:
        SetBlendAlpha(16, (u16)sBgFx->timer * 2);

        if (sBgFx->timer > 7) {
            sBgFx->timer = 0;
            sBgFx->state = 1;
        } else {
            sBgFx->timer++;
        }

        break;
    case 1:
        if (sBgFx->timer > 30) {
            sBgFx->timer = 0;
            sBgFx->state = 2;
        } else {
            sBgFx->timer++;
        }

        break;
    case 2:
        SetBlendAlpha(16, 16 - (u16)sBgFx->timer * 2);

        if (sBgFx->timer > 7) {
            BgAnimStop();
        } else {
            sBgFx->timer++;
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
    sBgFx->attack = v;

    if (w > 0) {
        sBgFx->scaleX = -0x180;
        sBgFx->flags |= BGFX_FLAG_FLIP_X;
        x -= 0x4000;
        w += 0x4000;
    } else {
        sBgFx->scaleX = 0x180;
        x += 0x4000;
        w -= 0x4000;
    }

    sBgFx->targetX = x;
    sBgFx->targetZ = z;
    d = abs(w);
    sBgFx->unk_3C = d;
    sBgFx->x = x + ((gSineTable[0] * d) >> 8);
    sBgFx->z = z + ((-gSineTable[64] * d) >> 8);
    sBgFx->y = y;
    sBgFx->scaleY = 0x180;
    SetBlendAlpha(16, 0);
    m4aSongNumStart(SONG_EF_MARL_KAMAEF);
    WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, sBgFx->z);
    BgAnimStart(&gBgAnimDefKama, sx, sy);
    sBgFx->state = 0;
    sBgFx->update = BgFxUpdateKama;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateRikuLimit() {
    s16 t = sBgFx->timer >> 1;
    SetBlendAlpha(16, 16 - t);

    if (t > 15) {
        BgAnimStop();
    }

    sBgFx->timer++;
    BgFxUpdateBase();
}

void BgFxStartRikuLimit(s32 x, s32 y, s32 z, u8 f) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(3)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->angle = f;
    WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, sBgFx->z);
    BgAnimStart(&sBgAnimDefRikuLimit, sx, sy);
    sBgFx->flags |= BGFX_FLAG_BELOW_SPRITES;
    sBgFx->update = BgFxUpdateRikuLimit;
}

void BgFxStartDragonFire(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->scaleX = s;
    sBgFx->scaleY = s;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefDragonFire, sx, sy);
    sBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateLaxeneBeam() {
    s32 x;
    s32 y;
    s32 z;
    s16 r;
    u8 ang;
    BtlObj* o;

    switch (sBgFx->state) {
    case 0:
        if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
            ApproachValueHalfSteps(&sBgFx->scaleX, -204, sBgFx->steps);
        } else {
            ApproachValueHalfSteps(&sBgFx->scaleX, 204, sBgFx->steps);
        }

        sBgFx->steps--;

        if (sBgFx->steps <= 0) {
            sBgFx->timer = 0;
            sBgFx->state = 1;
        } else {
            sBgFx->timer++;
        }

        break;
    case 1:
        SetBlendAlpha(16, 16 - sBgFx->timer);

        if (sBgFx->timer > 15) {
            BgAnimStop();
        } else {
            sBgFx->timer++;
        }

        break;
    }

    r = (abs(sBgFx->scaleX) * 5) >> 4;

    if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
        ang = sBgFx->angle + 192;
    } else {
        ang = sBgFx->angle + 64;
    }

    x = sBgFx->x + gSineTable[ang] * r;
    z = sBgFx->z + -gSineTable[ang + 64] * r;
    y = sBgFx->y;
    ApplyAttackBox(sBgFx->attack, x, y, z, 32, 16, 16);
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->state = 0;
    sBgFx->steps = 80;
    sBgFx->attack = v;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefLaxeneBeam, sx, sy);

    if (f) {
        sBgFx->flags |= BGFX_FLAG_FLIP_X;
        sBgFx->angle = 248;
    } else {
        sBgFx->angle = 8;
    }

    if (sBgFx->flags & BGFX_FLAG_FLIP_X) {
        if (sBgFx->x < gBtlWork->actor->x) {
            sBgFx->state = 1;
        } else {
            sBgFx->scaleX = -(((sBgFx->x - gBtlWork->actor->x) << 8) / 19200);
        }
    } else {
        if (sBgFx->x > gBtlWork->actor->x) {
            sBgFx->state = 1;
        } else {
            sBgFx->scaleX = ((gBtlWork->actor->x - sBgFx->x) << 8) / 19200;
        }
    }

    BgAnimSetLoopStartFrame(3);
    sBgFx->update = BgFxUpdateLaxeneBeam;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxUpdateAero() {
    s16 t;

    switch (sBgFx->state) {
    case 0:
        sBgFx->scaleX += 2;
        sBgFx->scaleY += 2;
        break;
    case 1:
        sBgFx->scaleX += 5;
        sBgFx->scaleY += 5;
        break;
    case 2:
        sBgFx->scaleX += 10;
        sBgFx->scaleY += 10;
        break;
    }

    if (sBgFx->timer == 10) {
        t = (sBgFx->scaleX * 3) >> 4;

        if (ApplyAttackBox(sBgFx->attack, sBgFx->x, sBgFx->y, sBgFx->z, t, t, 100)) {
            m4aSongNumStart(SONG_EF_DS_ANKOKUPUNCH);
        }
    }

    sBgFx->timer++;
    BgFxUpdateBase();
}

void BgFxStartAero(u16 a, s32 x, s32 y, s32 z, s32 w) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->attack = w;
    sBgFx->state = a;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefAero, sx, sy);
    sBgFx->update = BgFxUpdateAero;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartRikuDarkModeFlash(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefRikuDarkModeFlash, sx, sy);
    sBgFx->update = BgFxUpdateBase;
}

void BgFxStartLstCtr(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->scaleX = s;
    sBgFx->scaleY = s;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefLstCtr, sx, sy);
    sBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartLstCtrFlipped(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->scaleX = -s;
    sBgFx->scaleY = s;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefLstCtr, sx, sy);
    sBgFx->update = BgFxUpdateBase;
    FadeToAmount(FADE_MODE_BLACK, gBtlWork->fadeAmount, 8);
    sBgFx->flags |= BGFX_FLAG_SCREEN_DIMMED;
}

void BgFxStartDsdTransition(s32 x, s32 y, s32 z, s32 s) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(1)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->scaleX = s;
    sBgFx->scaleY = s;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefDsdTransition, sx, sy);
    sBgFx->update = BgFxUpdateBase;
}

void BgFxUpdateRikuDarkMode() {
    switch (sBgFx->state) {
    case 0:
        ApproachValue(&sBgFx->unk_3C, 0xA00, sBgFx->steps);
        ApproachValueHalfSteps(&sBgFx->scaleX, 460, sBgFx->steps);
        ApproachValueHalfSteps(&sBgFx->scaleY, 512, sBgFx->steps);
        SetBlendAlpha(16, sBgFx->unk_3C >> 8);
        sBgFx->steps--;

        if (sBgFx->steps <= 0) {
            sBgFx->timer = 0;
            sBgFx->state = 1;
        }

        break;
    case 1:
        sBgFx->state = 2;
        sBgFx->timer = 0;
        sBgFx->steps = 25;
        break;
    case 2:
        ApproachValue(&sBgFx->unk_3C, 0, sBgFx->steps);
        SetBlendAlpha(16, sBgFx->unk_3C >> 8);
        sBgFx->steps--;

        if (sBgFx->steps <= 0) {
            sBgFx->timer = 0;
            sBgFx->state = 3;
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
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    sBgFx->state = 0;
    sBgFx->scaleX = 10;
    sBgFx->scaleY = 10;
    sBgFx->unk_3C = 0;
    sBgFx->endSignals = 0;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&sBgAnimDefDarkGlow, sx, sy);
    BgAnimSetLoopStartFrame(0);
    sBgFx->update = BgFxUpdateRikuDarkMode;
    sBgFx->steps = 43;
}

void BgFxUpdateRikuLimitFinish() {
    if (sBgFx->timer > 10) {
        switch (sBgFx->state) {
        case 0:
            ApplyAttackBox(11, sBgFx->x - 0x6000, sBgFx->y - 0x1000, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x, sBgFx->y + 0x2000, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x + 0x7000, sBgFx->y - 0x1000, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x - 0x3000, sBgFx->y + 0x2000, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x + 0x3000, sBgFx->y + 0x2800, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x - 0x6000, sBgFx->y + 0x6000, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x + 0x800, sBgFx->y + 0x7800, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x + 0x3000, sBgFx->y + 0x2800, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x + 0x6800, sBgFx->y + 0x6800, sBgFx->z,
                14, 14, 14);
            break;
        case 1:
            ApplyAttackBox(11, sBgFx->x + 0x6000, sBgFx->y - 0x1000, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x, sBgFx->y + 0x2000, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x - 0x7000, sBgFx->y - 0x1000, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x + 0x3000, sBgFx->y + 0x2000, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x - 0x3000, sBgFx->y + 0x2800, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x + 0x6000, sBgFx->y + 0x6000, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x - 0x800, sBgFx->y + 0x7800, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x - 0x3000, sBgFx->y + 0x2800, sBgFx->z,
                14, 14, 14);
            ApplyAttackBox(11, sBgFx->x - 0x6800, sBgFx->y + 0x6800, sBgFx->z,
                14, 14, 14);
            break;
        }
    }

    sBgFx->timer++;
    BgFxUpdateBase();
}

void BgFxStartRikuLimitFinish(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(0)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    m4aSongNumStart(SONG_SND_705);
    WorldToScreen(&sx, &sy, sBgFx->x, sBgFx->y, sBgFx->z);
    sBgFx->state = GetRandom() % 2;

    switch (sBgFx->state) {
    case 0:
        BgAnimStart(&gBgAnimDefRikuLimitFinish, sx, sy);
        break;
    case 1:
        BgAnimStart(&gBgAnimDefRikuLimitFinish, sx, sy);
        sBgFx->flags |= BGFX_FLAG_FLIP_X;
        sBgFx->scaleX = -0x100;
        break;
    }

    sBgFx->update = BgFxUpdateRikuLimitFinish;
}

void BgFxStartRikuDiveHit(s32 x, s32 y, s32 z) {
    s16 sx;
    s16 sy;

    if (BgFxIsBlocked(2)) {
        return;
    }

    BgFxReset();
    sBgFx->x = x;
    sBgFx->y = y;
    sBgFx->z = z;
    WorldToScreen(&sx, &sy, x, y, z);
    BgAnimStart(&gBgAnimDefRikuDiveHit, sx, sy);
    sBgFx->update = BgFxUpdateBase;
}
