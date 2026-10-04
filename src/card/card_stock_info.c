/**
 * card_stock_info.c
 * Card Help Text and Sleight Info
 */

#include "msg_localized_data.h"
#include "system_state.h"
#include "player_progression.h"
#include "m4a_song.h"
#include "game_state.h"
#include "fade.h"
#include "obj_api.h"
#include "engine_math.h"
#include "taskpool.h"
#include "card.h"
#include "card_help_data.h"
#include "sprites_level_up.h"
#include "songs.h"
#include "card_help_text.h"
#include "player_progression_types.h"
#include "status.h"
#include <stddef.h>
#include "types.h"
#include "card_stock_info.h"

#if defined(VERSION_US)
static const CardHelpDef sFiraHelpDef = {
    gFiraHelpTexts,
    2,
    { 0, 0, 0 },
};
#endif

#if defined(VERSION_US)
static const CardHelpDef sBlizzaraHelpDef = {
    gBlizzaraHelpTexts,
    2,
    { 0, 0, 0 },
};
#endif

#if defined(VERSION_JP)
static const CardHelpDef sFiraHelpDef = {
    gFiraHelpTexts,
    2,
    { 0, 0, 0 },
};
#endif

#if defined(VERSION_JP)
#include "card_help_pages_head.inc"
#endif
#if defined(VERSION_JP)
static const CardHelpDef sBlizzaraHelpDef = {
    gBlizzaraHelpTexts,
    2,
    { 0, 0, 0 },
};
#endif

#if defined(VERSION_JP)
#include "card_help_pages.inc"
#endif
#if defined(VERSION_JP)
static const CardHelpDef sUnk_0903BFB4 = {
    gUnk_09EE7D44,
    2,
    { 0, 0, 0 },
};
#endif

static const CardHelpDef sThundaraHelpDef = {
    gThundaraHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sCuraHelpDef = {
    gCuraHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sStopraHelpDef = {
    gStopraHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sSonicBladeHelpDef = {
    gSonicBladeHelpTexts,
#if defined(VERSION_US) || defined(VERSION_EU)
    3,
#elif defined(VERSION_JP)
    2,
#endif
    { 0, 0, 0 },
};

static const CardHelpDef sStrikeRaidHelpDef = {
    gStrikeRaidHelpTexts,
    2,
    { 0, 0, 0 },
};

#if defined(VERSION_EU)
static const CardHelpDef sFiraHelpDef = {
    gFiraHelpTexts,
    2,
    { 0, 0, 0 },
};
#endif

static const CardHelpDef sFiragaHelpDef = {
    gFiragaHelpTexts,
    2,
    { 0, 0, 0 },
};

#if defined(VERSION_EU)
static const CardHelpDef sBlizzaraHelpDef = {
    gBlizzaraHelpTexts,
    2,
    { 0, 0, 0 },
};
#endif

static const CardHelpDef sBlizzagaHelpDef = {
    gBlizzagaHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sThundagaHelpDef = {
    gThundagaHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sCuragaHelpDef = {
    gCuragaHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sGraviraHelpDef = {
    gGraviraHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sGravigaHelpDef = {
    gGravigaHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sStopgaHelpDef = {
    gStopgaHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sGoofyChargeHelpDef = {
    gGoofyChargeHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sGoofyTornadoHelpDef = {
    gGoofyTornadoHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sMagicHelpDef = {
    gMagicHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sMagicPairHelpDef = {
    gMagicPairHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sProudRoarHelpDef = {
    gProudRoarHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sProudRoarPairHelpDef = {
    gProudRoarPairHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sShowtimeHelpDef = {
    gShowtimeHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sShowtimePairHelpDef = {
    gShowtimePairHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sParadiseHelpDef = {
    gParadiseHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sParadisePairHelpDef = {
    gParadisePairHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sSplashHelpDef = {
    gSplashHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sSplashPairHelpDef = {
    gSplashPairHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sTwinkleHelpDef = {
    gTwinkleHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sTwinklePairHelpDef = {
    gTwinklePairHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sFlareBreathHelpDef = {
    gFlareBreathHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sFlareBreathPairHelpDef = {
    gFlareBreathPairHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sOmnislashHelpDef = {
    gOmnislashHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sCrossSlashHelpDef = {
    gCrossSlashHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sSandstormHelpDef = {
    gSandstormHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sSandstormPairHelpDef = {
    gSandstormPairHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sSpiralWaveHelpDef = {
    gSpiralWaveHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sSpiralWavePairHelpDef = {
    gSpiralWavePairHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sSurpriseHelpDef = {
    gSurpriseHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sSurprisePairHelpDef = {
    gSurprisePairHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sHummingbirdHelpDef = {
    gHummingbirdHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sHummingbirdPairHelpDef = {
    gHummingbirdPairHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sFerociousLungeHelpDef = {
    gFerociousLungeHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sFerociousLungePairHelpDef = {
    gFerociousLungePairHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sMmMiracleHelpDef = {
    gMmMiracleHelpTexts,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sMmMiraclePairHelpDef = {
    gMmMiraclePairHelpTexts,
#if defined(VERSION_US) || defined(VERSION_EU)
    4,
#elif defined(VERSION_JP)
    2,
#endif
    { 0, 0, 0 },
};

static const CardHelpDef sAeroraHelpDef = {
    gAeroraHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sAerogaHelpDef = {
    gAerogaHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sBlitzHelpDef = {
    gBlitzHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sArsArcanumHelpDef = {
    gArsArcanumHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sRagnarokHelpDef = {
    gRagnarokHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sTrinityLimitHelpDef = {
    gTrinityLimitHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sSlidingDashHelpDef = {
    gSlidingDashHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sStunImpactHelpDef = {
    gStunImpactHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sZantetsukenHelpDef = {
    gZantetsukenHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sWarpHelpDef = {
    gWarpHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sWarpinatorHelpDef = {
    gWarpinatorHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sTerrorHelpDef = {
    gTerrorHelpTexts,
    3,
    { 0, 0, 0 },
};

static const CardHelpDef sConfuseHelpDef = {
    gConfuseHelpTexts,
    2,
    { 0, 0, 0 },
};

#if defined(VERSION_US) || defined(VERSION_JP)
static const CardHelpDef sUnk_0903BED4 = {
    gUnk_09EE7D74,
    2,
    { 0, 0, 0 },
};
#endif

static const CardHelpDef sStopRaidHelpDef = {
    gStopRaidHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sJudgmentHelpDef = {
    gJudgmentHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sReflectRaidHelpDef = {
    gReflectRaidHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sFireRaidHelpDef = {
    gFireRaidHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sBlizzardRaidHelpDef = {
    gBlizzardRaidHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sThunderRaidHelpDef = {
    gThunderRaidHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sGravityRaidHelpDef = {
    gGravityRaidHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sAquaSplashHelpDef = {
    gAquaSplashHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sHolyHelpDef = {
    gHolyHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sBlazingDonaldHelpDef = {
    gBlazingDonaldHelpTexts,
    2,
    { 0, 0, 0 },
};

#if defined(VERSION_US) || defined(VERSION_JP)
static const CardHelpDef sUnk_0903BF2C = {
    gUnk_09EE7D7C,
    2,
    { 0, 0, 0 },
};
#endif

static const CardHelpDef sGiftedMiracleHelpDef = {
    gGiftedMiracleHelpTexts,
    3,
    { 0, 0, 0 },
};

static const CardHelpDef sMegaFlareHelpDef = {
    gMegaFlareHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sFiragaBreakHelpDef = {
    gFiragaBreakHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sShockImpactHelpDef = {
    gShockImpactHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sIdyllRompHelpDef = {
    gIdyllRompHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sCrossSlashPlusHelpDef = {
    gCrossSlashPlusHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sHomingFiraHelpDef = {
    gHomingFiraHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sHomingBlizzaraHelpDef = {
    gHomingBlizzaraHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sSynchroHelpDef = {
    gSynchroHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sBindHelpDef = {
    gBindHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sTornadoHelpDef = {
    gTornadoHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sQuakeHelpDef = {
    gQuakeHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sTeleportHelpDef = {
    gTeleportHelpTexts,
    3,
    { 0, 0, 0 },
};

static const CardHelpDef sDarkBreakHelpDef = {
    gDarkBreakHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sDarkFiragaHelpDef = {
    gDarkFiragaHelpTexts,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sDarkAuraHelpDef = {
    gDarkAuraHelpTexts,
    2,
    { 0, 0, 0 },
};

#if defined(VERSION_US)
static const CardHelpDef sUnk_0903BFB4 = {
    gUnk_09EE7D44,
    4,
    { 0, 0, 0 },
};
#endif

#if defined(VERSION_US) || defined(VERSION_EU)
const CardHelpText* gBlitzHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_090381F8,
    gCardHelpTextUs_09038260,
#elif defined(VERSION_EU)
    &gCardHelp46Text0,
    &gCardHelp46Text1,
#endif
};
#endif

const CardHelpText* gSonicBladeHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_090382DC,
    gCardHelpTextUs_0903835A,
    gCardHelpTextUs_090383C4,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900B6E8,
    gCardHelpTextJp_0900B734,
#elif defined(VERSION_EU)
    &gCardHelp05Text0,
    &gCardHelp05Text1,
    &gCardHelp05Text2,
#endif
};

#if defined(VERSION_US) || defined(VERSION_EU)
const CardHelpText* gArsArcanumHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038440,
    gCardHelpTextUs_0903848E,
#elif defined(VERSION_EU)
    &gCardHelp47Text0,
    &gCardHelp47Text1,
#endif
};
#endif

const CardHelpText* gStrikeRaidHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_090384DC,
    gCardHelpTextUs_0903857A,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900B7B4,
    gCardHelpTextJp_0900B7F0,
#elif defined(VERSION_EU)
    &gCardHelp06Text0,
    &gCardHelp06Text1,
#endif
};

#if defined(VERSION_US) || defined(VERSION_EU)
const CardHelpText* gRagnarokHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_090385CC,
    gCardHelpTextUs_09038646,
#elif defined(VERSION_EU)
    &gCardHelp48Text0,
    &gCardHelp48Text1,
#endif
};

const CardHelpText* gTrinityLimitHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038694,
    gCardHelpTextUs_090386F0,
#elif defined(VERSION_EU)
    &gCardHelp49Text0,
    &gCardHelp49Text1,
#endif
};

const CardHelpText* gSlidingDashHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038736,
    gCardHelpTextUs_090387A4,
#elif defined(VERSION_EU)
    &gCardHelp50Text0,
    &gCardHelp50Text1,
#endif
};

const CardHelpText* gStunImpactHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903881C,
    gCardHelpTextUs_0903887A,
#elif defined(VERSION_EU)
    &gCardHelp51Text0,
    &gCardHelp51Text1,
#endif
};

const CardHelpText* gZantetsukenHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_090388F2,
    gCardHelpTextUs_0903897C,
#elif defined(VERSION_EU)
    &gCardHelp52Text0,
    &gCardHelp52Text1,
#endif
};
#endif

const CardHelpText* gFiraHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_090389D2,
    gCardHelpTextUs_09038A32,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900B9F0,
    gCardHelpTextJp_0900BA08,
#elif defined(VERSION_EU)
    &gCardHelp00Text0,
    &gCardHelp00Text1,
#endif
};

const CardHelpText* gBlizzaraHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038A4E,
    gCardHelpTextUs_09038AAA,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BA24,
    gCardHelpTextJp_0900BA3C,
#elif defined(VERSION_EU)
    &gCardHelp01Text0,
    &gCardHelp01Text1,
#endif
};

const CardHelpText* gThundaraHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038AD6,
    gCardHelpTextUs_09038B3E,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BA58,
    gCardHelpTextJp_0900BA70,
#elif defined(VERSION_EU)
    &gCardHelp02Text0,
    &gCardHelp02Text1,
#endif
};

const CardHelpText* gCuraHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038B66,
    gCardHelpTextUs_09038B90,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BA84,
    gCardHelpTextJp_0900BA9C,
#elif defined(VERSION_EU)
    &gCardHelp03Text0,
    &gCardHelp03Text1,
#endif
};

#if defined(VERSION_US) || defined(VERSION_EU)
const CardHelpText* gGraviraHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038BAC,
    gCardHelpTextUs_09038C10,
#elif defined(VERSION_EU)
    &gCardHelp11Text0,
    &gCardHelp11Text1,
#endif
};
#endif

const CardHelpText* gStopraHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038C38,
    gCardHelpTextUs_09038C96,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BAAC,
    gCardHelpTextJp_0900BAC8,
#elif defined(VERSION_EU)
    &gCardHelp04Text0,
    &gCardHelp04Text1,
#endif
};

#if defined(VERSION_US) || defined(VERSION_EU)
const CardHelpText* gAeroraHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038CB2,
    gCardHelpTextUs_09038D16,
#elif defined(VERSION_EU)
    &gCardHelp44Text0,
    &gCardHelp44Text1,
#endif
};
#endif

const CardHelpText* gFiragaHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038D32,
    gCardHelpTextUs_09038D90,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BADC,
    gCardHelpTextJp_0900BAF4,
#elif defined(VERSION_EU)
    &gCardHelp07Text0,
    &gCardHelp07Text1,
#endif
};

const CardHelpText* gBlizzagaHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038DBA,
    gCardHelpTextUs_09038E16,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BB14,
    gCardHelpTextJp_0900BB2C,
#elif defined(VERSION_EU)
    &gCardHelp08Text0,
    &gCardHelp08Text1,
#endif
};

const CardHelpText* gThundagaHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038E58,
    gCardHelpTextUs_09038EBA,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BB4C,
    gCardHelpTextJp_0900BB64,
#elif defined(VERSION_EU)
    &gCardHelp09Text0,
    &gCardHelp09Text1,
#endif
};

const CardHelpText* gCuragaHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038EF6,
    gCardHelpTextUs_09038F3C,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BB84,
    gCardHelpTextJp_0900BBA0,
#elif defined(VERSION_EU)
    &gCardHelp10Text0,
    &gCardHelp10Text1,
#endif
};

#if defined(VERSION_JP)
const CardHelpText* gGraviraHelpTexts[] = {
    gCardHelpTextJp_0900BBB8,
    gCardHelpTextJp_0900BBE4,
};
#endif

const CardHelpText* gGravigaHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038F66,
    gCardHelpTextUs_09038FCA,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BBF8,
    gCardHelpTextJp_0900BC24,
#elif defined(VERSION_EU)
    &gCardHelp12Text0,
    &gCardHelp12Text1,
#endif
};

const CardHelpText* gStopgaHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09039006,
    gCardHelpTextUs_0903906E,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BC44,
    gCardHelpTextJp_0900BC6C,
#elif defined(VERSION_EU)
    &gCardHelp13Text0,
    &gCardHelp13Text1,
#endif
};

#if defined(VERSION_US) || defined(VERSION_EU)
const CardHelpText* gAerogaHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09039098,
    gCardHelpTextUs_09039110,
#elif defined(VERSION_EU)
    &gCardHelp45Text0,
    &gCardHelp45Text1,
#endif
};
#endif

const CardHelpText* gProudRoarHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903913A,
    gCardHelpTextUs_090391BA,
    gCardHelpTextUs_090391DA,
    gCardHelpTextUs_0903926E,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BD20,
    gCardHelpTextJp_0900BD4C,
    gCardHelpTextJp_0900BD5C,
    gCardHelpTextJp_0900BD90,
#elif defined(VERSION_EU)
    &gCardHelp18Text0,
    &gCardHelp18Text1,
    &gCardHelp18Text2,
    &gCardHelp18Text3,
#endif
};

const CardHelpText* gProudRoarPairHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903913A,
    gCardHelpTextUs_090391BA,
    gCardHelpTextUs_090391DA,
    gCardHelpTextUs_0903926E,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BD20,
    gCardHelpTextJp_0900BD4C,
    gCardHelpTextJp_0900BD5C,
    gCardHelpTextJp_0900BD90,
#elif defined(VERSION_EU)
    &gCardHelp18Text0,
    &gCardHelp18Text1,
    &gCardHelp18Text2,
    &gCardHelp18Text3,
#endif
};

const CardHelpText* gShowtimeHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903929E,
    gCardHelpTextUs_09039334,
    gCardHelpTextUs_09039354,
    gCardHelpTextUs_090393EE,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BDA8,
    gCardHelpTextJp_0900BDE0,
    gCardHelpTextJp_0900BDF4,
    gCardHelpTextJp_0900BE2C,
#elif defined(VERSION_EU)
    &gCardHelp20Text0,
    &gCardHelp20Text1,
    &gCardHelp20Text2,
    &gCardHelp20Text3,
#endif
};

const CardHelpText* gShowtimePairHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903929E,
    gCardHelpTextUs_09039334,
    gCardHelpTextUs_09039354,
    gCardHelpTextUs_090393EE,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BDA8,
    gCardHelpTextJp_0900BDE0,
    gCardHelpTextJp_0900BDF4,
    gCardHelpTextJp_0900BE2C,
#elif defined(VERSION_EU)
    &gCardHelp20Text0,
    &gCardHelp20Text1,
    &gCardHelp20Text2,
    &gCardHelp20Text3,
#endif
};

const CardHelpText* gTwinkleHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903941E,
    gCardHelpTextUs_09039490,
    gCardHelpTextUs_090394C8,
    gCardHelpTextUs_09039562,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BE4C,
    gCardHelpTextJp_0900BE7C,
    gCardHelpTextJp_0900BE90,
    gCardHelpTextJp_0900BEC4,
#elif defined(VERSION_EU)
    &gCardHelp26Text0,
    &gCardHelp26Text1,
    &gCardHelp26Text2,
    &gCardHelp26Text3,
#endif
};

const CardHelpText* gTwinklePairHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903941E,
    gCardHelpTextUs_09039490,
    gCardHelpTextUs_090394C8,
    gCardHelpTextUs_09039562,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BE4C,
    gCardHelpTextJp_0900BE7C,
    gCardHelpTextJp_0900BE90,
    gCardHelpTextJp_0900BEC4,
#elif defined(VERSION_EU)
    &gCardHelp26Text0,
    &gCardHelp26Text1,
    &gCardHelp26Text2,
    &gCardHelp26Text3,
#endif
};

const CardHelpText* gFlareBreathHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_090395B6,
    gCardHelpTextUs_09039646,
    gCardHelpTextUs_09039666,
    gCardHelpTextUs_09039708,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BEE4,
    gCardHelpTextJp_0900BF14,
    gCardHelpTextJp_0900BF2C,
    gCardHelpTextJp_0900BF64,
#elif defined(VERSION_EU)
    &gCardHelp28Text0,
    &gCardHelp28Text1,
    &gCardHelp28Text2,
    &gCardHelp28Text3,
#endif
};

const CardHelpText* gFlareBreathPairHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_090395B6,
    gCardHelpTextUs_09039646,
    gCardHelpTextUs_09039666,
    gCardHelpTextUs_09039708,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BEE4,
    gCardHelpTextJp_0900BF14,
    gCardHelpTextJp_0900BF2C,
    gCardHelpTextJp_0900BF64,
#elif defined(VERSION_EU)
    &gCardHelp28Text0,
    &gCardHelp28Text1,
    &gCardHelp28Text2,
    &gCardHelp28Text3,
#endif
};

#if defined(VERSION_JP)
const CardHelpText* gCrossSlashHelpTexts[] = {
    gCardHelpTextJp_0900BF88,
    gCardHelpTextJp_0900BF9C,
};
#endif

const CardHelpText* gOmnislashHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_090397BA,
    gCardHelpTextUs_09039842,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BFB0,
    gCardHelpTextJp_0900BFDC,
#elif defined(VERSION_EU)
    &gCardHelp30Text0,
    &gCardHelp30Text1,
#endif
};

#if defined(VERSION_US) || defined(VERSION_EU)
const CardHelpText* gCrossSlashHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09039738,
    gCardHelpTextUs_0903979A,
#elif defined(VERSION_EU)
    &gCardHelp31Text0,
    &gCardHelp31Text1,
#endif
};
#endif

const CardHelpText* gParadiseHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09039872,
    gCardHelpTextUs_090398D4,
    gCardHelpTextUs_090398F4,
    gCardHelpTextUs_09039988,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BFFC,
    gCardHelpTextJp_0900C02C,
    gCardHelpTextJp_0900C03C,
    gCardHelpTextJp_0900C084,
#elif defined(VERSION_EU)
    &gCardHelp22Text0,
    &gCardHelp22Text1,
    &gCardHelp22Text2,
    &gCardHelp22Text3,
#endif
};

const CardHelpText* gParadisePairHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09039872,
    gCardHelpTextUs_090398D4,
    gCardHelpTextUs_090398F4,
    gCardHelpTextUs_09039988,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900BFFC,
    gCardHelpTextJp_0900C02C,
    gCardHelpTextJp_0900C03C,
    gCardHelpTextJp_0900C084,
#elif defined(VERSION_EU)
    &gCardHelp22Text0,
    &gCardHelp22Text1,
    &gCardHelp22Text2,
    &gCardHelp22Text3,
#endif
};

const CardHelpText* gSplashHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_090399B8,
    gCardHelpTextUs_09039A3A,
    gCardHelpTextUs_09039A5A,
    gCardHelpTextUs_09039AF8,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C09C,
    gCardHelpTextJp_0900C0CC,
    gCardHelpTextJp_0900C0DC,
    gCardHelpTextJp_0900C118,
#elif defined(VERSION_EU)
    &gCardHelp24Text0,
    &gCardHelp24Text1,
    &gCardHelp24Text2,
    &gCardHelp24Text3,
#endif
};

const CardHelpText* gSplashPairHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_090399B8,
    gCardHelpTextUs_09039A3A,
    gCardHelpTextUs_09039A5A,
    gCardHelpTextUs_09039AF8,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C09C,
    gCardHelpTextJp_0900C0CC,
    gCardHelpTextJp_0900C0DC,
    gCardHelpTextJp_0900C118,
#elif defined(VERSION_EU)
    &gCardHelp24Text0,
    &gCardHelp24Text1,
    &gCardHelp24Text2,
    &gCardHelp24Text3,
#endif
};

const CardHelpText* gMagicHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09039B28,
    gCardHelpTextUs_09039B96,
    gCardHelpTextUs_09039BBA,
    gCardHelpTextUs_09039C30,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C130,
    gCardHelpTextJp_0900C174,
    gCardHelpTextJp_0900C188,
    gCardHelpTextJp_0900C1CC,
#elif defined(VERSION_EU)
    &gCardHelp16Text0,
    &gCardHelp16Text1,
    &gCardHelp16Text2,
    &gCardHelp16Text3,
#endif
};

const CardHelpText* gMagicPairHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09039B28,
    gCardHelpTextUs_09039B96,
    gCardHelpTextUs_09039BBA,
    gCardHelpTextUs_09039C30,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C188,
    gCardHelpTextJp_0900C1CC,
    gCardHelpTextJp_0900C130,
    gCardHelpTextJp_0900C174,
#elif defined(VERSION_EU)
    &gCardHelp16Text0,
    &gCardHelp16Text1,
    &gCardHelp16Text2,
    &gCardHelp16Text3,
#endif
};

const CardHelpText* gGoofyChargeHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09039C66,
    gCardHelpTextUs_09039CEE,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C1EC,
    gCardHelpTextJp_0900C218,
#elif defined(VERSION_EU)
    &gCardHelp15Text0,
    &gCardHelp15Text1,
#endif
};

const CardHelpText* gGoofyTornadoHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09039D0E,
    gCardHelpTextUs_09039D8E,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C230,
    gCardHelpTextJp_0900C25C,
#elif defined(VERSION_EU)
    &gCardHelp14Text0,
    &gCardHelp14Text1,
#endif
};

const CardHelpText* gSandstormHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09039DBE,
    gCardHelpTextUs_09039E1A,
    gCardHelpTextUs_09039E42,
    gCardHelpTextUs_09039ED6,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C280,
    gCardHelpTextJp_0900C29C,
    gCardHelpTextJp_0900C2B0,
    gCardHelpTextJp_0900C2E0,
#elif defined(VERSION_EU)
    &gCardHelp32Text0,
    &gCardHelp32Text1,
    &gCardHelp32Text2,
    &gCardHelp32Text3,
#endif
};

const CardHelpText* gSandstormPairHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09039DBE,
    gCardHelpTextUs_09039E1A,
    gCardHelpTextUs_09039E42,
    gCardHelpTextUs_09039ED6,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C280,
    gCardHelpTextJp_0900C29C,
    gCardHelpTextJp_0900C2B0,
    gCardHelpTextJp_0900C2E0,
#elif defined(VERSION_EU)
    &gCardHelp32Text0,
    &gCardHelp32Text1,
    &gCardHelp32Text2,
    &gCardHelp32Text3,
#endif
};

const CardHelpText* gSurpriseHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09039F12,
    gCardHelpTextUs_09039F82,
    gCardHelpTextUs_09039F9E,
    gCardHelpTextUs_0903A012,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C300,
    gCardHelpTextJp_0900C33C,
    gCardHelpTextJp_0900C350,
    gCardHelpTextJp_0900C38C,
#elif defined(VERSION_EU)
    &gCardHelp36Text0,
    &gCardHelp36Text1,
    &gCardHelp36Text2,
    &gCardHelp36Text3,
#endif
};

const CardHelpText* gSurprisePairHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09039F12,
    gCardHelpTextUs_09039F82,
    gCardHelpTextUs_09039F9E,
    gCardHelpTextUs_0903A012,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C300,
    gCardHelpTextJp_0900C33C,
    gCardHelpTextJp_0900C350,
    gCardHelpTextJp_0900C38C,
#elif defined(VERSION_EU)
    &gCardHelp36Text0,
    &gCardHelp36Text1,
    &gCardHelp36Text2,
    &gCardHelp36Text3,
#endif
};

const CardHelpText* gSpiralWaveHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903A03C,
    gCardHelpTextUs_0903A0A4,
    gCardHelpTextUs_0903A0C4,
    gCardHelpTextUs_0903A15C,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C3AC,
    gCardHelpTextJp_0900C3DC,
    gCardHelpTextJp_0900C3F0,
    gCardHelpTextJp_0900C428,
#elif defined(VERSION_EU)
    &gCardHelp34Text0,
    &gCardHelp34Text1,
    &gCardHelp34Text2,
    &gCardHelp34Text3,
#endif
};

const CardHelpText* gSpiralWavePairHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903A03C,
    gCardHelpTextUs_0903A0A4,
    gCardHelpTextUs_0903A0C4,
    gCardHelpTextUs_0903A15C,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C3AC,
    gCardHelpTextJp_0900C3DC,
    gCardHelpTextJp_0900C3F0,
    gCardHelpTextJp_0900C428,
#elif defined(VERSION_EU)
    &gCardHelp34Text0,
    &gCardHelp34Text1,
    &gCardHelp34Text2,
    &gCardHelp34Text3,
#endif
};

const CardHelpText* gHummingbirdHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903A18C,
    gCardHelpTextUs_0903A1FE,
    gCardHelpTextUs_0903A22E,
    gCardHelpTextUs_0903A2D0,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C448,
    gCardHelpTextJp_0900C474,
    gCardHelpTextJp_0900C490,
    gCardHelpTextJp_0900C4C0,
#elif defined(VERSION_EU)
    &gCardHelp38Text0,
    &gCardHelp38Text1,
    &gCardHelp38Text2,
    &gCardHelp38Text3,
#endif
};

const CardHelpText* gHummingbirdPairHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903A18C,
    gCardHelpTextUs_0903A1FE,
    gCardHelpTextUs_0903A22E,
    gCardHelpTextUs_0903A2D0,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C448,
    gCardHelpTextJp_0900C474,
    gCardHelpTextJp_0900C490,
    gCardHelpTextJp_0900C4C0,
#elif defined(VERSION_EU)
    &gCardHelp38Text0,
    &gCardHelp38Text1,
    &gCardHelp38Text2,
    &gCardHelp38Text3,
#endif
};

const CardHelpText* gFerociousLungeHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903A318,
    gCardHelpTextUs_0903A39A,
    gCardHelpTextUs_0903A3CA,
    gCardHelpTextUs_0903A448,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C4EC,
    gCardHelpTextJp_0900C524,
    gCardHelpTextJp_0900C538,
    gCardHelpTextJp_0900C568,
#elif defined(VERSION_EU)
    &gCardHelp40Text0,
    &gCardHelp40Text1,
    &gCardHelp40Text2,
    &gCardHelp40Text3,
#endif
};

const CardHelpText* gFerociousLungePairHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903A318,
    gCardHelpTextUs_0903A39A,
    gCardHelpTextUs_0903A3CA,
    gCardHelpTextUs_0903A448,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C4EC,
    gCardHelpTextJp_0900C524,
    gCardHelpTextJp_0900C538,
    gCardHelpTextJp_0900C568,
#elif defined(VERSION_EU)
    &gCardHelp40Text0,
    &gCardHelp40Text1,
    &gCardHelp40Text2,
    &gCardHelp40Text3,
#endif
};

#if defined(VERSION_JP)
const CardHelpText* gMmMiracleHelpTexts[] = {
    gCardHelpTextJp_0900D0D8,
    gCardHelpTextJp_0900D110,
    gCardHelpTextJp_0900D11C,
    gCardHelpTextJp_0900D158,
};

const CardHelpText* gUnk_09EE7D44[] = {
    gCardHelpTextJp_0900D16C,
    gCardHelpTextJp_0900D174,
};

const CardHelpText* gMmMiraclePairHelpTexts[] = {
    gCardHelpTextJp_0900D11C,
    gCardHelpTextJp_0900D158,
};

const CardHelpText* gAeroraHelpTexts[] = {
    gCardHelpTextJp_0900BC8C,
    gCardHelpTextJp_0900BCC0,
};

const CardHelpText* gAerogaHelpTexts[] = {
    gCardHelpTextJp_0900BCD0,
    gCardHelpTextJp_0900BD08,
};

const CardHelpText* gBlitzHelpTexts[] = {
    gCardHelpTextJp_0900B684,
    gCardHelpTextJp_0900B6B0,
};

const CardHelpText* gArsArcanumHelpTexts[] = {
    gCardHelpTextJp_0900B76C,
    gCardHelpTextJp_0900B78C,
};

const CardHelpText* gRagnarokHelpTexts[] = {
    gCardHelpTextJp_0900B81C,
    gCardHelpTextJp_0900B83C,
};

const CardHelpText* gTrinityLimitHelpTexts[] = {
    gCardHelpTextJp_0900B864,
    gCardHelpTextJp_0900B8A0,
};

const CardHelpText* gSlidingDashHelpTexts[] = {
    gCardHelpTextJp_0900B8C8,
    gCardHelpTextJp_0900B8F0,
};

const CardHelpText* gStunImpactHelpTexts[] = {
    gCardHelpTextJp_0900B928,
    gCardHelpTextJp_0900B950,
};

const CardHelpText* gZantetsukenHelpTexts[] = {
    gCardHelpTextJp_0900B988,
    gCardHelpTextJp_0900B9C4,
};
#endif

const CardHelpText* gWarpHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903A490,
    gCardHelpTextUs_0903A4D0,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C588,
    gCardHelpTextJp_0900C5B0,
#elif defined(VERSION_EU)
    &gCardHelp53Text0,
    &gCardHelp53Text1,
#endif
};

const CardHelpText* gWarpinatorHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903A4FA,
    gCardHelpTextUs_0903A562,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C5CC,
    gCardHelpTextJp_0900C600,
#elif defined(VERSION_EU)
    &gCardHelp54Text0,
    &gCardHelp54Text1,
#endif
};

const CardHelpText* gTerrorHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903A592,
    gCardHelpTextUs_0903A5FC,
    gCardHelpTextUs_0903A652,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C61C,
    gCardHelpTextJp_0900C644,
    gCardHelpTextJp_0900C668,
#elif defined(VERSION_EU)
    &gCardHelp55Text0,
    &gCardHelp55Text1,
    &gCardHelp55Text2,
#endif
};

const CardHelpText* gConfuseHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903A692,
    gCardHelpTextUs_0903A700,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C68C,
    gCardHelpTextJp_0900C6C0,
#elif defined(VERSION_EU)
    &gCardHelp56Text0,
    &gCardHelp56Text1,
#endif
};

#if defined(VERSION_JP)
const CardHelpText* gUnk_09EE7D74[] = {
    gCardHelpTextJp_0900C6E0,
    gCardHelpTextJp_0900C718,
};
#endif

const CardHelpText* gStopRaidHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903A750,
    gCardHelpTextUs_0903A7B0,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C728,
    gCardHelpTextJp_0900C75C,
#elif defined(VERSION_EU)
    &gCardHelp58Text0,
    &gCardHelp58Text1,
#endif
};

const CardHelpText* gJudgmentHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903A806,
    gCardHelpTextUs_0903A878,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C788,
    gCardHelpTextJp_0900C7B8,
#elif defined(VERSION_EU)
    &gCardHelp59Text0,
    &gCardHelp59Text1,
#endif
};

const CardHelpText* gReflectRaidHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903A8CE,
    gCardHelpTextUs_0903A95A,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C7E0,
    gCardHelpTextJp_0900C82C,
#elif defined(VERSION_EU)
    &gCardHelp60Text0,
    &gCardHelp60Text1,
#endif
};

const CardHelpText* gFireRaidHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903A9B2,
    gCardHelpTextUs_0903AA08,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C858,
    gCardHelpTextJp_0900C880,
#elif defined(VERSION_EU)
    &gCardHelp61Text0,
    &gCardHelp61Text1,
#endif
};

const CardHelpText* gBlizzardRaidHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903AA5E,
    gCardHelpTextUs_0903AAB2,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C8AC,
    gCardHelpTextJp_0900C8D4,
#elif defined(VERSION_EU)
    &gCardHelp62Text0,
    &gCardHelp62Text1,
#endif
};

const CardHelpText* gThunderRaidHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903AB10,
    gCardHelpTextUs_0903AB70,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C900,
    gCardHelpTextJp_0900C928,
#elif defined(VERSION_EU)
    &gCardHelp63Text0,
    &gCardHelp63Text1,
#endif
};

const CardHelpText* gGravityRaidHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903ABCC,
    gCardHelpTextUs_0903AC32,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C954,
    gCardHelpTextJp_0900C988,
#elif defined(VERSION_EU)
    &gCardHelp64Text0,
    &gCardHelp64Text1,
#endif
};

const CardHelpText* gAquaSplashHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903AC8E,
    gCardHelpTextUs_0903AD26,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900C9B4,
    gCardHelpTextJp_0900C9F0,
#elif defined(VERSION_EU)
    &gCardHelp65Text0,
    &gCardHelp65Text1,
#endif
};

const CardHelpText* gHolyHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903AD58,
    gCardHelpTextUs_0903ADD8,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CA0C,
    gCardHelpTextJp_0900CA48,
#elif defined(VERSION_EU)
    &gCardHelp66Text0,
    &gCardHelp66Text1,
#endif
};

const CardHelpText* gBlazingDonaldHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903AE2A,
    gCardHelpTextUs_0903AE60,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CA78,
    gCardHelpTextJp_0900CAA4,
#elif defined(VERSION_EU)
    &gCardHelp67Text0,
    &gCardHelp67Text1,
#endif
};

#if defined(VERSION_JP)
const CardHelpText* gUnk_09EE7D7C[] = {
    gCardHelpTextJp_0900CAC4,
    gCardHelpTextJp_0900CAFC,
};
#endif

const CardHelpText* gGiftedMiracleHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903AEA2,
    gCardHelpTextUs_0903AF44,
    gCardHelpTextUs_0903AF98,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CB0C,
    gCardHelpTextJp_0900CB48,
    gCardHelpTextJp_0900CB6C,
#elif defined(VERSION_EU)
    &gCardHelp69Text0,
    &gCardHelp69Text1,
    &gCardHelp69Text2,
#endif
};

const CardHelpText* gMegaFlareHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903AFDE,
    gCardHelpTextUs_0903B02C,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CB90,
    gCardHelpTextJp_0900CBAC,
#elif defined(VERSION_EU)
    &gCardHelp70Text0,
    &gCardHelp70Text1,
#endif
};

const CardHelpText* gFiragaBreakHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903B058,
    gCardHelpTextUs_0903B0E6,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CBCC,
    gCardHelpTextJp_0900CBF8,
#elif defined(VERSION_EU)
    &gCardHelp71Text0,
    &gCardHelp71Text1,
#endif
};

const CardHelpText* gShockImpactHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903B128,
    gCardHelpTextUs_0903B192,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CC20,
    gCardHelpTextJp_0900CC50,
#elif defined(VERSION_EU)
    &gCardHelp72Text0,
    &gCardHelp72Text1,
#endif
};

const CardHelpText* gIdyllRompHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903B1EA,
    gCardHelpTextUs_0903B260,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CC78,
    gCardHelpTextJp_0900CCA4,
#elif defined(VERSION_EU)
    &gCardHelp73Text0,
    &gCardHelp73Text1,
#endif
};

const CardHelpText* gCrossSlashPlusHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903B2B8,
    gCardHelpTextUs_0903B31A,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CCCC,
    gCardHelpTextJp_0900CCFC,
#elif defined(VERSION_EU)
    &gCardHelp74Text0,
    &gCardHelp74Text1,
#endif
};

const CardHelpText* gHomingFiraHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903B35C,
    gCardHelpTextUs_0903B3C6,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CD20,
    gCardHelpTextJp_0900CD50,
#elif defined(VERSION_EU)
    &gCardHelp75Text0,
    &gCardHelp75Text1,
#endif
};

const CardHelpText* gHomingBlizzaraHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903B404,
    gCardHelpTextUs_0903B476,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CD70,
    gCardHelpTextJp_0900CDA0,
#elif defined(VERSION_EU)
    &gCardHelp76Text0,
    &gCardHelp76Text1,
#endif
};

const CardHelpText* gSynchroHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903B4BC,
    gCardHelpTextUs_0903B522,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CDC0,
    gCardHelpTextJp_0900CDFC,
#elif defined(VERSION_EU)
    &gCardHelp77Text0,
    &gCardHelp77Text1,
#endif
};

const CardHelpText* gBindHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903B552,
    gCardHelpTextUs_0903B5DE,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CE18,
    gCardHelpTextJp_0900CE54,
#elif defined(VERSION_EU)
    &gCardHelp78Text0,
    &gCardHelp78Text1,
#endif
};

const CardHelpText* gTornadoHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903B622,
    gCardHelpTextUs_0903B6B0,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CE74,
    gCardHelpTextJp_0900CEB0,
#elif defined(VERSION_EU)
    &gCardHelp79Text0,
    &gCardHelp79Text1,
#endif
};

const CardHelpText* gQuakeHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903B6F6,
    gCardHelpTextUs_0903B76E,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CED0,
    gCardHelpTextJp_0900CF0C,
#elif defined(VERSION_EU)
    &gCardHelp80Text0,
    &gCardHelp80Text1,
#endif
};

const CardHelpText* gTeleportHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903B7B4,
    gCardHelpTextUs_0903B842,
    gCardHelpTextUs_0903B89E,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CF2C,
    gCardHelpTextJp_0900CF68,
    gCardHelpTextJp_0900CF90,
#elif defined(VERSION_EU)
    &gCardHelp81Text0,
    &gCardHelp81Text1,
    &gCardHelp81Text2,
#endif
};

const CardHelpText* gDarkBreakHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903B8DA,
    gCardHelpTextUs_0903B976,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900CFB4,
    gCardHelpTextJp_0900CFE8,
#elif defined(VERSION_EU)
    &gCardHelp82Text0,
    &gCardHelp82Text1,
#endif
};

const CardHelpText* gDarkFiragaHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903B9C4,
    gCardHelpTextUs_0903BA4A,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900D014,
    gCardHelpTextJp_0900D04C,
#elif defined(VERSION_EU)
    &gCardHelp83Text0,
    &gCardHelp83Text1,
#endif
};

const CardHelpText* gDarkAuraHelpTexts[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903BA9A,
    gCardHelpTextUs_0903BB2C,
#elif defined(VERSION_JP)
    gCardHelpTextJp_0900D078,
    gCardHelpTextJp_0900D0B0,
#elif defined(VERSION_EU)
    &gCardHelp84Text0,
    &gCardHelp84Text1,
#endif
};

#if defined(VERSION_US)
const CardHelpText* gUnk_09EE7D44[] = {
    gCardHelpTextUs_0903BCFA,
    gCardHelpTextUs_0903BCFA,
    gCardHelpTextUs_0903BCFA,
    gCardHelpTextUs_0903BCFA,
};

const CardHelpText* gMmMiracleHelpTexts[] = {
    gCardHelpTextUs_0903BB76,
    gCardHelpTextUs_0903BBF8,
    gCardHelpTextUs_0903BC24,
    gCardHelpTextUs_0903BCB8,
};

const CardHelpText* gMmMiraclePairHelpTexts[] = {
    gCardHelpTextUs_0903BB76,
    gCardHelpTextUs_0903BBF8,
    gCardHelpTextUs_0903BC24,
    gCardHelpTextUs_0903BCB8,
};

const CardHelpText* gUnk_09EE7D74[] = {
    gCardHelpTextUs_0903BCFA,
    gCardHelpTextUs_0903BCFA,
};

const CardHelpText* gUnk_09EE7D7C[] = {
    gCardHelpTextUs_0903BCFA,
    gCardHelpTextUs_0903BCFA,
};
#endif

#if defined(VERSION_EU)
const CardHelpText* gMmMiracleHelpTexts[] = {
    &gCardHelp42Text0,
    &gCardHelp42Text1,
    &gCardHelp42Text2,
    &gCardHelp42Text3,
};

const CardHelpText* gMmMiraclePairHelpTexts[] = {
    &gCardHelp42Text0,
    &gCardHelp42Text1,
    &gCardHelp42Text2,
    &gCardHelp42Text3,
};
#endif

static const u16 sLevelUpStockHelpIndices[12] = {
    50, 51, 6, 46, 5, 52, 79, 47, 66, 48, 70, 0xFFFF,
};

static const u16 sLevelUpStockLevels[12] = {
    2, 7, 12, 17, 22, 27, 32, 37, 42, 47, 52, 999,
};

void StockInfo_0(StockInfoWork* work, u8* active) {
    u8 i;

    work->active = active;
    TaskPoolInit(&work->tasks, 1);
    work->tiles = LoadObjTiles(gUnk_0908FCEE, 0x12A0);
    work->palette = LoadObjPalette(gUnk_09613F78, 32);

    for (i = 16; i < 32; i++) {
        FadeSetPaletteExcluded(i, 1);
    }

    work->x = 0x4C00;
    work->y = 0xBC00;
    work->timer = 16;

    switch (gGameState.progression.levelMilestone) {
    case 0:
        LearnStock(0);
        break;
    case 1:
        LearnStock(2);
        break;
    case 2:
        LearnStock(4);
        break;
    case 3:
        LearnStock(1);
        break;
    case 4:
        LearnStock(5);
        break;
    case 5:
        LearnStock(3);
        break;
    case 6:
        LearnStock(36);
        break;
    case 7:
        LearnStock(6);
        break;
    case 8:
        LearnStock(46);
        break;
    case 9:
        LearnStock(7);
        break;
    case 10:
        LearnStock(32);
        break;
    }
}

u8 StockInfo_1(StockInfoWork* work, void* a) {
    if (work->timer > 0) {
        ApproachValue(&work->y, 0x6C00, work->timer);
        work->timer--;
    } else {
        m4aSongNumStart(SONG_SYS_CHAGEF2);
        CreateStockMesDispTask(&work->tasks, sLevelUpStockHelpIndices[gGameState.progression.levelMilestone], 0, 0, 0x50);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateStockInfoMessage);
    }

    return 1;
}

s32 UpdateStockInfoMessage(StockInfoWork* work) {
    if (*work->active == 0) {
        return 0;
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void StockInfo_2(StockInfoWork* work) {
    DrawSprite(work->x >> 8, work->y >> 8, gUnk_09EEA28C[0], work->tiles, work->palette, NULL, 0, 50);
    TaskPoolDraw(&work->tasks);
}

void StockInfo_3(StockInfoWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    gGameState.progression.levelMilestone++;
    TaskPoolDestroy(&work->tasks);
}

void* GetCardHelpText(u16 a, u8 b) {
    if (b < gCardHelpDefs[a]->textCount) {
        return LANGSTR(gCardHelpDefs[a]->texts[b]);
    }

    return NULL;
}

u8 GetCardHelpTextCount(u16 a) {
    return gCardHelpDefs[a]->textCount;
}

u8 IsLevelUpStockUnlocked() {
    if (gGameState.progression.level >= sLevelUpStockLevels[gGameState.progression.levelMilestone]) {
        return 1;
    }

    return 0;
}

const CardHelpDef* gCardHelpDefs[] = {
    &sFiraHelpDef,
    &sBlizzaraHelpDef,
    &sThundaraHelpDef,
    &sCuraHelpDef,
    &sStopraHelpDef,
    &sSonicBladeHelpDef,
    &sStrikeRaidHelpDef,
    &sFiragaHelpDef,
    &sBlizzagaHelpDef,
    &sThundagaHelpDef,
    &sCuragaHelpDef,
    &sGraviraHelpDef,
    &sGravigaHelpDef,
    &sStopgaHelpDef,
    &sGoofyTornadoHelpDef,
    &sGoofyChargeHelpDef,
    &sMagicHelpDef,
    &sMagicPairHelpDef,
    &sProudRoarHelpDef,
    &sProudRoarPairHelpDef,
    &sShowtimeHelpDef,
    &sShowtimePairHelpDef,
    &sParadiseHelpDef,
    &sParadisePairHelpDef,
    &sSplashHelpDef,
    &sSplashPairHelpDef,
    &sTwinkleHelpDef,
    &sTwinklePairHelpDef,
    &sFlareBreathHelpDef,
    &sFlareBreathPairHelpDef,
    &sOmnislashHelpDef,
    &sCrossSlashHelpDef,
    &sSandstormHelpDef,
    &sSandstormPairHelpDef,
    &sSpiralWaveHelpDef,
    &sSpiralWavePairHelpDef,
    &sSurpriseHelpDef,
    &sSurprisePairHelpDef,
    &sHummingbirdHelpDef,
    &sHummingbirdPairHelpDef,
    &sFerociousLungeHelpDef,
    &sFerociousLungePairHelpDef,
    &sMmMiracleHelpDef,
    &sMmMiraclePairHelpDef,
    &sAeroraHelpDef,
    &sAerogaHelpDef,
    &sBlitzHelpDef,
    &sArsArcanumHelpDef,
    &sRagnarokHelpDef,
    &sTrinityLimitHelpDef,
    &sSlidingDashHelpDef,
    &sStunImpactHelpDef,
    &sZantetsukenHelpDef,
    &sWarpHelpDef,
    &sWarpinatorHelpDef,
    &sTerrorHelpDef,
    &sConfuseHelpDef,
#if defined(VERSION_US) || defined(VERSION_JP)
    &sUnk_0903BED4,
#elif defined(VERSION_EU)
    NULL,
#endif
    &sStopRaidHelpDef,
    &sJudgmentHelpDef,
    &sReflectRaidHelpDef,
    &sFireRaidHelpDef,
    &sBlizzardRaidHelpDef,
    &sThunderRaidHelpDef,
    &sGravityRaidHelpDef,
    &sAquaSplashHelpDef,
    &sHolyHelpDef,
    &sBlazingDonaldHelpDef,
#if defined(VERSION_US) || defined(VERSION_JP)
    &sUnk_0903BF2C,
#elif defined(VERSION_EU)
    NULL,
#endif
    &sGiftedMiracleHelpDef,
    &sMegaFlareHelpDef,
    &sFiragaBreakHelpDef,
    &sShockImpactHelpDef,
    &sIdyllRompHelpDef,
    &sCrossSlashPlusHelpDef,
    &sHomingFiraHelpDef,
    &sHomingBlizzaraHelpDef,
    &sSynchroHelpDef,
    &sBindHelpDef,
    &sTornadoHelpDef,
    &sQuakeHelpDef,
    &sTeleportHelpDef,
    &sDarkBreakHelpDef,
    &sDarkFiragaHelpDef,
    &sDarkAuraHelpDef,
#if defined(VERSION_US) || defined(VERSION_JP)
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
    &sUnk_0903BFB4,
#endif
};

TaskDesc gTaskDescStockInfo = {
    "StockInfo",
    (TaskInitFunc)StockInfo_0,
    (TaskUpdateFunc)StockInfo_1,
    (TaskDrawFunc)StockInfo_2,
    (TaskDestroyFunc)StockInfo_3,
    sizeof(StockInfoWork),
};
