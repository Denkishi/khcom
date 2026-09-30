#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "msg_api.h"
#include "mode_test_api.h"
#include "mode_debug.h"
#include "m4a_song.h"
#include "game_state.h"
#include "text.h"
#include "fade.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "display.h"
#include "engine_math.h"
#include "anim.h"
#include "obj.h"
#include "taskpool.h"
#include "gba/syscall.h"
#include "card.h"
#include "card_reload_assets.h"
#include "sprites_btl.h"
#include "prize_card.h"
#include "sprites_worldselect.h"
#include "sprites_card_pictures.h"
#include "sprites_card.h"
#include "gba/io_reg.h"
#include "card_ids.h"
#include "songs.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "card_api.h"
#include "card_def_data.h"
#include "card_types.h"
#include "card_ui_types.h"
#include "map_types.h"
#include "player_progression_types.h"
#include "types.h"
#include <stddef.h>

u16 PickPrizeMapCardKindForWorld(u16 a, s32 b);
u16 PickPrizeMapCardForWorld(u16 a, s32 b);
void CreatePrizeMapCardTask(TaskPool* pool, s32* args);
s32 UpdateSpotLightFadeOut(SpotlightWork* w);
s32 UpdateSelmapEventKeyClose(SelmapEventKeyWork* work);

static const u16 sPrizeMapCardValueChances[10] = { 10, 5, 5, 15, 15, 15, 15, 10, 5, 5 };

static const PrizeMapCardEntry sUnk_09035A10[1] = {
    { CARD_ID(CARD_OATHKEEPER, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035A14[4] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035A24[2] = {
    { sUnk_09035A10, 1, 30 },
    { sUnk_09035A14, 4, 100 },
};

static const PrizeMapCardEntry sUnk_09035A34[2] = {
    { CARD_ID(CARD_LADY_LUCK, 0), 0 },
    { CARD_ID(CARD_ULTIMA_WEAPON, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035A3C[7] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_GRAVITY, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035A58[8] = {
    { CARD_ID(CARD_LIONHEART, 0), 0 },
    { CARD_ID(CARD_DIVINE_ROSE, 0), 0 },
    { CARD_ID(CARD_OATHKEEPER, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_SPELLBINDER, 0), 0 },
    { CARD_ID(CARD_METAL_CHOCOBO, 0), 0 },
    { CARD_ID(CARD_OLYMPIA, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035A78[3] = {
    { sUnk_09035A34, 2, 40 },
    { sUnk_09035A3C, 7, 85 },
    { sUnk_09035A58, 8, 100 },
};

static const PrizeMapCardEntry sUnk_09035A90[2] = {
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_ULTIMA_WEAPON, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035A98[7] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_GRAVITY, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035AB4[8] = {
    { CARD_ID(CARD_LADY_LUCK, 0), 0 },
    { CARD_ID(CARD_LIONHEART, 0), 0 },
    { CARD_ID(CARD_DIVINE_ROSE, 0), 0 },
    { CARD_ID(CARD_OATHKEEPER, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_SPELLBINDER, 0), 0 },
    { CARD_ID(CARD_METAL_CHOCOBO, 0), 0 },
    { CARD_ID(CARD_OLYMPIA, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035AD4[3] = {
    { sUnk_09035A90, 2, 40 },
    { sUnk_09035A98, 7, 85 },
    { sUnk_09035AB4, 8, 100 },
};

static const PrizeMapCardEntry sUnk_09035AEC[2] = {
    { CARD_ID(CARD_ULTIMA_WEAPON, 0), 0 },
    { CARD_ID(CARD_DIVINE_ROSE, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035AF4[7] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_GRAVITY, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035B10[7] = {
    { CARD_ID(CARD_LADY_LUCK, 0), 0 },
    { CARD_ID(CARD_LIONHEART, 0), 0 },
    { CARD_ID(CARD_OATHKEEPER, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_SPELLBINDER, 0), 0 },
    { CARD_ID(CARD_METAL_CHOCOBO, 0), 0 },
    { CARD_ID(CARD_OLYMPIA, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035B2C[3] = {
    { sUnk_09035AEC, 2, 40 },
    { sUnk_09035AF4, 7, 85 },
    { sUnk_09035B10, 7, 100 },
};

static const PrizeMapCardEntry sUnk_09035B44[2] = {
    { CARD_ID(CARD_ULTIMA_WEAPON, 0), 0 },
    { CARD_ID(CARD_LIONHEART, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035B4C[7] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_GRAVITY, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035B68[8] = {
    { CARD_ID(CARD_LADY_LUCK, 0), 0 },
    { CARD_ID(CARD_DIVINE_ROSE, 0), 0 },
    { CARD_ID(CARD_OATHKEEPER, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_SPELLBINDER, 0), 0 },
    { CARD_ID(CARD_METAL_CHOCOBO, 0), 0 },
    { CARD_ID(CARD_OLYMPIA, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035B88[3] = {
    { sUnk_09035B44, 2, 40 },
    { sUnk_09035B4C, 7, 85 },
    { sUnk_09035B68, 8, 100 },
};

static const PrizeMapCardEntry sUnk_09035BA0[2] = {
    { CARD_ID(CARD_ULTIMA_WEAPON, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035BA8[7] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_GRAVITY, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035BC4[8] = {
    { CARD_ID(CARD_LADY_LUCK, 0), 0 },
    { CARD_ID(CARD_LIONHEART, 0), 0 },
    { CARD_ID(CARD_DIVINE_ROSE, 0), 0 },
    { CARD_ID(CARD_OATHKEEPER, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_SPELLBINDER, 0), 0 },
    { CARD_ID(CARD_METAL_CHOCOBO, 0), 0 },
    { CARD_ID(CARD_OLYMPIA, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035BE4[3] = {
    { sUnk_09035BA0, 2, 40 },
    { sUnk_09035BA8, 7, 85 },
    { sUnk_09035BC4, 8, 100 },
};

static const PrizeMapCardEntry sUnk_09035BFC[1] = {
    { CARD_ID(CARD_METAL_CHOCOBO, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035C00[5] = {
    { CARD_ID(CARD_FIRE, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_BLIZZARD, 0), 0 },
    { CARD_ID(CARD_GRAVITY, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035C14[9] = {
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_LADY_LUCK, 0), 0 },
    { CARD_ID(CARD_LIONHEART, 0), 0 },
    { CARD_ID(CARD_DIVINE_ROSE, 0), 0 },
    { CARD_ID(CARD_OATHKEEPER, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_SPELLBINDER, 0), 0 },
    { CARD_ID(CARD_OLYMPIA, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035C38[3] = {
    { sUnk_09035BFC, 1, 20 },
    { sUnk_09035C00, 5, 80 },
    { sUnk_09035C14, 9, 100 },
};

static const PrizeMapCardEntry sUnk_09035C50[1] = {
    { CARD_ID(CARD_SPELLBINDER, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035C54[5] = {
    { CARD_ID(CARD_FIRE, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_BLIZZARD, 0), 0 },
    { CARD_ID(CARD_GRAVITY, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035C68[9] = {
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_LADY_LUCK, 0), 0 },
    { CARD_ID(CARD_LIONHEART, 0), 0 },
    { CARD_ID(CARD_DIVINE_ROSE, 0), 0 },
    { CARD_ID(CARD_OATHKEEPER, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_METAL_CHOCOBO, 0), 0 },
    { CARD_ID(CARD_OLYMPIA, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035C8C[3] = {
    { sUnk_09035C50, 1, 20 },
    { sUnk_09035C54, 5, 80 },
    { sUnk_09035C68, 9, 100 },
};

static const PrizeMapCardEntry sUnk_09035CA4[1] = {
    { CARD_ID(CARD_OLYMPIA, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035CA8[5] = {
    { CARD_ID(CARD_FIRE, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_BLIZZARD, 0), 0 },
    { CARD_ID(CARD_GRAVITY, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035CBC[9] = {
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_LADY_LUCK, 0), 0 },
    { CARD_ID(CARD_LIONHEART, 0), 0 },
    { CARD_ID(CARD_DIVINE_ROSE, 0), 0 },
    { CARD_ID(CARD_OATHKEEPER, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_SPELLBINDER, 0), 0 },
    { CARD_ID(CARD_METAL_CHOCOBO, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035CE0[3] = {
    { sUnk_09035CA4, 1, 20 },
    { sUnk_09035CA8, 5, 80 },
    { sUnk_09035CBC, 9, 100 },
};

static const PrizeMapCardEntry sUnk_09035CF8[1] = {
    { CARD_ID(CARD_CURE, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035CFC[6] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_ULTIMA_WEAPON, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035D14[8] = {
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_GRAVITY, 0), 0 },
    { CARD_ID(CARD_LADY_LUCK, 0), 0 },
    { CARD_ID(CARD_LIONHEART, 0), 0 },
    { CARD_ID(CARD_DIVINE_ROSE, 0), 0 },
    { CARD_ID(CARD_OATHKEEPER, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035D34[3] = {
    { sUnk_09035CF8, 1, 20 },
    { sUnk_09035CFC, 6, 80 },
    { sUnk_09035D14, 8, 100 },
};

static const PrizeMapCardEntry sUnk_09035D4C[1] = {
    { CARD_ID(CARD_CURE, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035D50[4] = {
    { CARD_ID(CARD_FIRE, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_BLIZZARD, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035D60[5] = {
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_GRAVITY, 0), 0 },
    { CARD_ID(CARD_SPELLBINDER, 0), 0 },
    { CARD_ID(CARD_METAL_CHOCOBO, 0), 0 },
    { CARD_ID(CARD_OLYMPIA, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035D74[3] = {
    { sUnk_09035D4C, 1, 30 },
    { sUnk_09035D50, 4, 80 },
    { sUnk_09035D60, 5, 100 },
};

static const PrizeMapCardEntry sUnk_09035D8C[9] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_FIRE, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_ULTIMA_WEAPON, 0), 0 },
    { CARD_ID(CARD_BLIZZARD, 0), 0 },
};

static const PrizeMapCardEntry sUnk_09035DB0[3] = {
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_GRAVITY, 0), 0 },
    { CARD_ID(CARD_CURE, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035DBC[2] = {
    { sUnk_09035D8C, 9, 85 },
    { sUnk_09035DB0, 3, 100 },
};

static const PrizeMapCardGroupList sSoraPrizeMapCardGroups[14] = {
    { sUnk_09035A24, 2 },
    { sUnk_09035A78, 3 },
    { sUnk_09035C38, 3 },
    { sUnk_09035B88, 3 },
    { sUnk_09035BE4, 3 },
    { sUnk_09035B2C, 3 },
    { sUnk_09035AD4, 3 },
    { sUnk_09035C8C, 3 },
    { sUnk_09035CE0, 3 },
    { sUnk_09035D74, 3 },
    { sUnk_09035A24, 2 },
    { sUnk_09035D34, 3 },
    { sUnk_09035DBC, 2 },
    { sUnk_09035DBC, 2 },
};

const u16 gUnk_09035E3C[10] = { 10, 5, 5, 15, 15, 15, 15, 10, 5, 5 };

static const PrizeMapCardEntry sUnk_09035E50[11] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_CURE, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035E7C[1] = {
    { sUnk_09035E50, 11, 100 },
};

static const PrizeMapCardEntry sUnk_09035E84[11] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_CURE, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035EB0[1] = {
    { sUnk_09035E84, 11, 100 },
};

static const PrizeMapCardEntry sUnk_09035EB8[11] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_CURE, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035EE4[1] = {
    { sUnk_09035EB8, 11, 100 },
};

static const PrizeMapCardEntry sUnk_09035EEC[11] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_CURE, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035F18[1] = {
    { sUnk_09035EEC, 11, 100 },
};

static const PrizeMapCardEntry sUnk_09035F20[11] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_CURE, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035F4C[1] = {
    { sUnk_09035F20, 11, 100 },
};

static const PrizeMapCardEntry sUnk_09035F54[11] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_CURE, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035F80[1] = {
    { sUnk_09035F54, 11, 100 },
};

static const PrizeMapCardEntry sUnk_09035F88[11] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_CURE, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035FB4[1] = {
    { sUnk_09035F88, 11, 100 },
};

static const PrizeMapCardEntry sUnk_09035FBC[11] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_CURE, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09035FE8[1] = {
    { sUnk_09035FBC, 11, 100 },
};

#ifdef VERSION_EU
static const PrizeMapCardEntry sUnk_09035FF0[9] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};
#else
static const PrizeMapCardEntry sUnk_09035FF0[10] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_CURE, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};
#endif

#ifdef VERSION_EU
static const PrizeMapCardGroup sUnk_09036018[1] = {
    { sUnk_09035FF0, 9, 100 },
};
#else
static const PrizeMapCardGroup sUnk_09036018[1] = {
    { sUnk_09035FF0, 10, 100 },
};
#endif

static const PrizeMapCardEntry sUnk_09036020[11] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_CURE, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardGroup sUnk_0903604C[1] = {
    { sUnk_09036020, 11, 100 },
};

static const PrizeMapCardEntry sUnk_09036054[11] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_CURE, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardGroup sUnk_09036080[1] = {
    { sUnk_09036054, 11, 100 },
};

static const PrizeMapCardEntry sUnk_09036088[11] = {
    { CARD_ID(CARD_THREE_WISHES, 0), 0 },
    { CARD_ID(CARD_KINGDOM_KEY, 0), 0 },
    { CARD_ID(CARD_WISHING_STAR, 0), 0 },
    { CARD_ID(CARD_FAIRY_HARP, 0), 0 },
    { CARD_ID(CARD_THUNDER, 0), 0 },
    { CARD_ID(CARD_CRABCLAW, 0), 0 },
    { CARD_ID(CARD_PUMPKINHEAD, 0), 0 },
    { CARD_ID(CARD_CURE, 0), 0 },
    { CARD_ID(CARD_DIAMOND_DUST, 0), 0 },
    { CARD_ID(CARD_ONE_WINGED_ANGEL, 0), 0 },
    { CARD_ID(CARD_OBLIVION, 0), 0 },
};

static const PrizeMapCardGroup sUnk_090360B4[1] = {
    { sUnk_09036088, 11, 100 },
};

static const PrizeMapCardGroupList sRikuPrizeMapCardGroups[14] = {
    { sUnk_09035E7C, 1 },
    { sUnk_09035EB0, 1 },
    { sUnk_09035FB4, 1 },
    { sUnk_09035F4C, 1 },
    { sUnk_09035F80, 1 },
    { sUnk_09035F18, 1 },
    { sUnk_09035EE4, 1 },
    { sUnk_09035FE8, 1 },
    { sUnk_09036018, 1 },
    { sUnk_09036080, 1 },
    { sUnk_09035E7C, 1 },
    { sUnk_0903604C, 1 },
    { sUnk_090360B4, 1 },
    { sUnk_090360B4, 1 },
};

static const u16 sUnk_0903612C[16] = { 0, 0, 8, 0, 0, 0, 0, 8, 8, 12, 0, 12, 16, 16, 16, 0 };

void PrizeCardInitInit(PrizeCardInitWork* w, PrizeCardArgs* args) {
    w->spawned = 0;
    w->args = *args;
    TaskPoolInit(&w->tasks, 1);
}

s32 PrizeCardInit_1(PrizeCardInitWork* w) {
    s32 args[9];
    s32 v;

    if (w->spawned == 0) {
        if ((gGameState.progression.unk_82 & 0x20) == 0) {
            *(PrizeCardArgs*)args = w->args;
            args[8] = 2;
            CreatePrizeMapCardTask(&w->tasks, args);
            gGameState.progression.unk_82 |= 0x20;
        } else if (gGameState.floor == 0) {
            if (CountZeroValueMapCards() == 0) {
                *(PrizeCardArgs*)args = w->args;
                args[8] = PickPrizeMapCardKindForWorld(gGameState.world, 1);

                if (args[8] != 0xFFFF) {
                    CreatePrizeMapCardTask(&w->tasks, args);
                } else {
                    return 0;
                }
            } else {
                *(PrizeCardArgs*)args = w->args;
                args[8] = PickPrizeMapCardForWorld(gGameState.world, 1);

                if (args[8] != 0xFFFF) {
                    CreatePrizeMapCardTask(&w->tasks, args);
                } else {
                    return 0;
                }
            }
        } else {
            v = gBtlWork->battleId;

            if (v >= 125 && v <= 127) {
                if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
                    if (GetRandom() % 100 < 20) {
                        *(PrizeCardArgs*)args = w->args;

#ifdef VERSION_EU
                        if (CountRegularMapCards() <= 98) {
                            args[8] = CARD_ID(CARD_GRAVITY, GetRandom() % 10);
                        } else {
                            args[8] = 0xFFFF;
                        }
#else
                        args[8] = CARD_ID(CARD_GRAVITY, GetRandom() % 10);
#endif
                    } else {
                        *(PrizeCardArgs*)args = w->args;
                        args[8] = PickPrizeMapCardForWorld(gGameState.world, 1);
                    }

                    if (args[8] != 0xFFFF) {
                        CreatePrizeMapCardTask(&w->tasks, args);
                    } else {
                        return 0;
                    }
                } else {
                    *(PrizeCardArgs*)args = w->args;
                    args[8] = PickPrizeMapCardForWorld(gGameState.world, 1);

                    if (args[8] != 0xFFFF) {
                        CreatePrizeMapCardTask(&w->tasks, args);
                    } else {
                        return 0;
                    }
                }
            } else if (v >= 131 && v <= 133) {
#ifdef VERSION_EU
                if (CountRegularMapCards() <= 98) {
                    *(PrizeCardArgs*)args = w->args;
                    args[8] = CARD_ID(CARD_ULTIMA_WEAPON, GetRandom() % 10);
                    CreatePrizeMapCardTask(&w->tasks, args);
                }
#else
                *(PrizeCardArgs*)args = w->args;
                args[8] = CARD_ID(CARD_ULTIMA_WEAPON, GetRandom() % 10);
                CreatePrizeMapCardTask(&w->tasks, args);
#endif
            } else {
                *(PrizeCardArgs*)args = w->args;

                if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
                    if (HasMapCard(0xFB) == 0) {
                        if (AreWorldPrizesCollected() == 0) {
                            if (sUnk_0903612C[gGameState.world] != 0) {
                                if (GetRandom() % 100 <= sUnk_0903612C[gGameState.world]) {
                                    args[8] = 0xFB;
                                } else {
                                    args[8] = PickPrizeMapCardForWorld(gGameState.world, 1);
                                }
                            } else {
                                args[8] = PickPrizeMapCardForWorld(gGameState.world, 1);
                            }
                        } else {
                            args[8] = PickPrizeMapCardForWorld(gGameState.world, 1);
                        }
                    } else {
                        args[8] = PickPrizeMapCardForWorld(gGameState.world, 1);
                    }
                } else {
                    args[8] = PickPrizeMapCardForWorld(gGameState.world, 1);
                }

                if (args[8] != 0xFFFF) {
                    CreatePrizeMapCardTask(&w->tasks, args);
                } else {
                    return 0;
                }
            }
        }

        w->spawned = 1;
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

s32 PrizeCardInit_Boss_1(PrizeCardInitWork* w, void* a) {
    PrizeCardTaskArgs args;

    if (w->spawned == 0) {
        *(PrizeCardArgs*)&args = w->args;

        switch (gBtlWork->battleId) {
        case 148:
            args.cardId = CARD_GUARD_ARMOR_1;
            break;
        case 149:
            args.cardId = CARD_JAFAR_1;
            break;
        case 150:
            args.cardId = CARD_TRICKMASTER_1;
            break;
        case 151:
            args.cardId = CARD_URSULA_1;
            break;
        case 152:
            args.cardId = CARD_PARASITE_CAGE_1;
            break;
        case 153:
            args.cardId = CARD_DRAGON_MALEFICENT_1;
            break;
        case 154:
            args.cardId = CARD_DARKSIDE_1;
            break;
        case 155:
            args.cardId = CARD_OOGIE_BOOGIE_1;
            break;
        case 156:
            args.cardId = CARD_MARLUXIA_1;
            break;
        case 120:
            args.cardId = CARD_CARD_SOLDIER_2;
            break;
        case 162:
            args.cardId = CARD_ID(CARD_FIRE, 5);
            break;
        case 163:
            args.cardId = CARD_ID(CARD_THUNDER, 7);
            break;
        case 161:
            args.cardId = CARD_ID(CARD_AERO, 6);
            break;
        case 157:
        case 158:
            args.cardId = CARD_HOOK_9;
            break;
        case 159:
            args.cardId = CARD_ID(CARD_HI_POTION, 3);
            break;
        case 160:
            args.cardId = CARD_HADES_9;
            break;
        case 165:
            args.cardId = CARD_MARLUXIA_9;
            break;
        case 164:
            args.cardId = CARD_ID(CARD_MEGA_ETHER, 4);
            break;
        case 169:
            args.cardId = CARD_ID(CARD_MEGA_POTION, 2);
            break;
        case 170:
            args.cardId = CARD_RIKU_9;
            break;
        case 173:
            args.cardId = CARD_AXEL_9;
            break;
        case 174:
            args.cardId = CARD_LARXENE_9;
            break;
        case 175:
            args.cardId = CARD_VEXEN_9;
            break;
        case 121:
            args.cardId = CARD_ID(CARD_DUMBO, 3);
            break;
        case 124:
            args.cardId = CARD_ID(CARD_ETHER, 3);
            break;
        case 167:
            args.cardId = CARD_LEXAEUS_9;
            break;
        default:
            w->spawned = 1;
            return 1;
        }

        if (gBtlWork->battleId != 121) {
            if (CollectionHasCard(args.cardId) == 0) {
                TaskCreate(&w->tasks, &gTaskDescPrizeBoss, &args);
            }
        } else {
            TaskCreate(&w->tasks, &gTaskDescPrizeBoss, &args);
        }

        w->spawned = 1;
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

void PrizeCardInitDraw(PrizeCardInitWork* w) {
    TaskPoolDraw(&w->tasks);
}

void PrizeCardInitDestroy(PrizeCardInitWork* w) {
    TaskPoolDestroy(&w->tasks);
}

u16 PickPrizeMapCardKind(const PrizeMapCardGroup* tbl, u16 n) {
    s32 i;
    const PrizeMapCardEntry* arr;
    u16 cnt;
    u16 v;
    u16 card;

    i = 0;

    if (CountRegularMapCards() <= 98) {
        while (i < n) {
            arr = tbl[i].entries;
            cnt = tbl[i].count;
            v = GetRandom() % 100;

            if (v <= tbl[i].chance) {
                card = arr[GetRandom() % cnt].cardId;
                v = CountMapCardsOfKind(card);

                if (v <= 89) {
                    return card;
                }
            }

            i++;

            if (i >= n) {
                i = 0;
            }
        }
    } else {
        return 0xFFFF;
    }
}

u16 PickPrizeMapCardValue(void) {
    u16 i;

    do {
        i = GetRandom() % 10;
    } while (sPrizeMapCardValueChances[i] <= GetRandom() % 100);

    return i;
}

u16 PickPrizeMapCardKindForWorld(u16 a, s32 b) {
    const PrizeMapCardGroup* tiles;
    u16 n;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        tiles = sRikuPrizeMapCardGroups[a].data;
        n = sRikuPrizeMapCardGroups[a].size;
    } else {
        tiles = sSoraPrizeMapCardGroups[a].data;
        n = sSoraPrizeMapCardGroups[a].size;
    }

    return PickPrizeMapCardKind(tiles, n);
}

u16 PickPrizeMapCardForWorld(u16 a, s32 b) {
    const PrizeMapCardGroup* tiles;
    u16 base;
    u16 off;

    off = 0;

    if (gGameState.flags & GAME_FLAG_RIKU) {
        tiles = sRikuPrizeMapCardGroups[a].data;
        base = PickPrizeMapCardKind(tiles, sRikuPrizeMapCardGroups[a].size);
    } else {
        tiles = sSoraPrizeMapCardGroups[a].data;
        base = PickPrizeMapCardKind(tiles, sSoraPrizeMapCardGroups[a].size);
    }

    if (base != 0xFFFF) {
        do {
            off = PickPrizeMapCardValue();
        } while (gMapCardCounts[base + off] == 9);
    }

    return base + off;
}

void CreatePrizeCardTask(TaskPool* pool, struct BtlPrizeSrc* src) {
    TaskCreate(pool, &gTaskDescPrizeCardInit, src);
}

void CreateBossPrizeCardTask(void* a, void* b) {
    TaskCreate(a, &gTaskDescPrizeCardInitBoss, b);
}

void DispCardname_0(DispCardnameWork* work, u16* a) {
    ObjPalette* p;
    s32 v;

    InitTextSlots(work->textSlots, 32);
    p = LoadTextPalette(1);
    work->textPalette = p;
    FadeSetPaletteExcluded(p->index + 16, 1);
    work->textSlotCount = LoadTextSlots(a, work->textSlots);
    work->tiles = LoadObjTiles(gUnk_093F7C9C, 0xFC0);
    work->palette = LoadObjPalette(gCard00Palette, 32);
#ifdef VERSION_JP
    v = (240 - work->textSlotCount * 10) / 2;
#else
    v = (240 - GetTextSlotsWidth(work->textSlots, work->textSlotCount)) / 2;
#endif
    work->x = v;
}

s32 DispCardname_1(void) {
    return 1;
}

void DispCardname_2(DispCardnameWork* work) {
    DrawTextSlots(work->x, 120, work->textSlots, work->textPalette, 50,
                  work->textSlotCount);
    DrawSprite(120, 125, gUnk_09EF126C[0], work->tiles,
               work->palette, 0, 0, 55);
}

void DispCardname_3(DispCardnameWork* work) {
    FreeTextSlots(work->textSlots, 32);
    ReleaseObjTiles(work->tiles);
    FadeSetPaletteExcluded(work->textPalette->index + 16, 0);
    ReleaseObjPalette(work->textPalette);
    ReleaseObjPalette(work->palette);
}

void CreateCardNameDisplay(void* a, void* b) {
    TaskCreate(a, &gTaskDescDispCardname, b);
}

void Version_0(VersionWork* work) {
    work->tiles = LoadSmallFontTiles();
    work->palette = LoadSmallFontPalette();
    work->textLength = EncodeSmallFontString(gVersionString, work->text);
}

s32 Version_1(void) {
    return 1;
}

void Version_2(VersionWork* work) {
    DrawSmallFontString(0, 152, work->text, work->tiles, work->palette, 0,
                  work->textLength);
}

void Version_3(VersionWork* work) {
    FreeSmallFontResources(work->tiles, work->palette);
}

Task* CreateVersionDisplay(TaskPool* pool) {
    return TaskCreate(pool, &gTaskDescVersion, 0);
}

static void PrizeCard_0(PrizeMapCardWork* w, s32* args) {
    Collider* p;

    w->cardId = args[8];
    w->cardDef = &gMapCardDefs[args[8]];
    w->cardBack = &gMapCardBackDefs[w->cardDef->backIndex];
    w->tiles = LoadObjTiles(w->cardDef->tiles, 0x300);
    w->palette = LoadObjPalette(w->cardDef->palette, 32);
    *(u64*)&w->kind = *(u64*)&w->cardDef->kind;
    w->tiles2 = LoadObjTiles(w->cardBack->tiles, w->cardBack->tilesSize);
    w->tiles3 = LoadObjTiles(w->cardBack->tiles, w->cardBack->tilesSize);
    w->palette2 = LoadObjPalette(w->cardBack->palette, w->cardBack->paletteSize);
    w->tiles4 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    w->tiles5 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    w->palette3 = LoadObjPalette(gUnk_08F69BE4, 32);
    w->posX = args[0];
    w->posY = args[1];
    w->posZ = 0;
    w->groundZ = 0;
    w->rotation = 24;
    w->vz = -(GetRandom() % 129 + 0x300);
    w->speed = GetRandom() % 129 + 0x80;
    w->moveAngle = GetRandom() % 256;
    w->scaleX = 0x80;
    w->scaleY = 0x80;
    w->scale = 0x80;
    w->flipAngleY = 0;
    w->flipAngleX = 0;
    p = &w->collider;
    ColliderInit(p, 5, 8, 10);
    ColliderSetDisabled(p, 1);
    ColliderSetPosition(p, w->posX, w->posY, w->posZ);
    w->backAnimTimer = 0;
    w->backAnimStep = 0;
    w->backFrame = 0;
    w->timer = 0;
    w->collected = 0;
    w->steps = 0;
    w->holdTimer = 0;
    TaskPoolInit(&w->tasks, 1);
    gBtlWork->prizeCount++;
}

static u8 PrizeCard_1(PrizeMapCardWork* w, void* a) {
    s16 x;
    s16 y;

    w->vz += 56;
    w->posZ += w->vz;
    w->posX += (gSineTable[(u8)w->moveAngle] * w->speed) >> 8;
    w->posY += (-gSineTable[(u8)w->moveAngle + 64] * w->speed) >> 8;

    if (ClampBattlePosition(&w->posX, &w->posY, -10, -10)) {
        w->moveAngle += GetRandom() % 57 + 100;
    }

    if (gBtlWork->hcEffect == 6) {
        ColliderSetRadius(&w->collider, 50);
    } else {
        ColliderSetRadius(&w->collider, 10);
    }

    if (w->posZ - 8 > w->groundZ) {
        w->posZ = w->groundZ - 8;
        w->vz = -((w->vz * 217) >> 8);
        w->moveAngle = GetAngle(w->posX, w->posY, gBtlWork->actor->x, gBtlWork->actor->y);
        w->moveAngle += GetRandom() % 65 - 32;

        if (w->vz > -0x200) {
            w->vz = -0x200;
        }
    }

    if (w->collider.colliding != 0) {
        w->collected = 1;
        m4aSongNumStart(SONG_SYS_ITEMGET);
        AddMapCard(w->cardId);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdatePrizeMapCardFlight);
        WorldToScreen(&x, &y, w->posX, w->posY, w->posZ);
        w->posX = x << 8;
        w->posY = y << 8;
        ColliderSetDisabled(&w->collider, 1);
        w->priority = 50;
        AimPrizeMapCardAtCenter(w);
        return 1;
    } else {
        ColliderSetPosition(&w->collider, w->posX, w->posY, w->posZ);
        WorldToScreen(&w->x, &w->y2, w->posX, w->posY, w->posZ);
        WorldToScreen(&w->x2, &w->y, w->posX, w->posY, w->groundZ);
        w->priority = -0x1004 - (w->posY >> 8) * 4;
        UpdatePrizeMapCardScale(w);
        w->flipAngleX += 2;

        if (w->timer == 20) {
            ColliderSetDisabled(&w->collider, 0);
        }

        if (w->timer <= 59) {
            w->timer++;
        }
    }

    return 1;
}

void AimPrizeMapCardAtCenter(PrizeMapCardWork* w) {
    s16 x;
    s16 y;
    s32 dx;
    s32 dy;
    s32 tx;
    s32 ty;

    WorldToScreen(&x, &y, gBtlWork->actor->x, gBtlWork->actor->y, gBtlWork->actor->z);
    tx = 0x7800;
    ty = 0x5000;
    dx = tx - w->posX;
    dy = ty - w->posY;
    w->distance = NormalizeVector2D8(&dx, &dy);
    w->dirX = -dx;
    w->dirY = -dy;
    w->speed = 0x300;
    w->vz = 2;
}

u8 UpdatePrizeMapCardFlight(PrizeMapCardWork* w, void* a) {
    s32 dx;
    s32 dy;
    u8 z;
    u8 t;
    s32 x;
    s32 y;
    s16* q1;
    s16* q2;

    if (w->speed < 0) {
        dx = 0x7800 - w->posX;
        dy = 0x5000 - w->posY;
        NormalizeVector2D8(&dx, &dy);
        w->dirX = -dx;
        w->dirY = -dy;

        if (w->distance <= 0x7FF) {
            w->steps = 0;
            w->rotation = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdatePrizeMapCardShow);
            CreateCardNameDisplay(&w->tasks, GetRoomName(w->cardDef->kind));
        }
    }

    w->posX += (w->dirX * w->speed) >> 8;
    w->posY += (w->dirY * w->speed) >> 8;
    t = w->rotation + 32;
    z = 0;
    w->rotation = t;
    w->flipAngleY += (64 - w->flipAngleY) >> 4;
    w->flipAngleX = z;
    w->distance = VectorLength2D(0x7800 - w->posX, 0x5000 - w->posY);
    w->speed -= w->vz;
    w->vz += 2;

    if (w->scale <= 0xFF) {
        w->scale += 3;
    }

    x = w->posX >> 8;
    q1 = &w->x;
    *q1 = x;
    y = w->posY >> 8;
    q2 = &w->y2;
    *q2 = y;
    UpdatePrizeMapCardScale(w);
    return 1;
}

u8 UpdatePrizeMapCardShow(PrizeMapCardWork* w, void* a) {
    s32 v;
    s16 lim;
    s32 x;
    s16* q;

    v = w->rotation << 8;
    ApproachValue((s32*)&w->flipAngleY, 0, w->steps);
    ApproachValue(&v, 0, w->steps);
    ApproachValue(&w->posX, 0x7800, w->steps);
    ApproachValue(&w->posY, 0x5800, w->steps);
    w->rotation = v >> 8;

    if (w->steps != 0) {
        w->steps--;
    }

    lim = 0x100;

    if (w->scale < 0x100) {
        w->scale += 2;
    } else {
        w->scale = lim;
    }

    x = w->posX >> 8;
    q = &w->x;
    *q = x;
    x = w->posY >> 8;
    q = &w->y2;
    *q = x;
    UpdatePrizeMapCardScale(w);
    w->holdTimer++;

    if (w->holdTimer == 30) {
        w->holdTimer = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdatePrizeMapCardShrink);
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 UpdatePrizeMapCardShrink(PrizeMapCardWork* w) {
    w->rotation += 32;
    WorldToScreen(&w->x3, &w->y3, gBtlWork->actor->x, gBtlWork->actor->y, gBtlWork->actor->z);
    w->x += (w->x3 - w->x) >> 3;
    w->y2 += (w->y3 - w->y2) >> 3;
    w->scaleX -= 10;
    w->scaleY -= 10;

    if (w->scaleX <= 10) {
        return 0;
    }

    return 1;
}

static void PrizeCard_2(PrizeMapCardWork* w) {
    u16 pal;
    ObjAffine* affine;
    void* gfx;
    s16 v;

    pal = w->collected == 0 ? GetBattleSpritePriorityFlags(w->posY) : 0;

    if (w->scaleX == 0x100 && w->rotation == 0) {
        affine = 0;
    } else {
        affine = AllocObjAffine(w->rotation, w->scaleX, w->scaleY, 1);
    }

    DrawSprite(w->x, (u16)w->y2 - 8,
               *w->cardDef->sprites,
               w->tiles, w->palette, affine, pal,
               (u16)(w->priority + 1));

    if (w->cardDef->backIndex == 4) {
        gfx = w->cardBack->sprites[w->backFrame];
    } else {
        gfx = w->cardBack->sprites[0];
    }

    DrawSprite(w->x, (u16)w->y2 - 8, gfx,
               w->tiles2, w->palette2, affine, pal,
               w->priority);

    if (w->cardDef->backIndex != 4) {
        gfx = gUnk_09EE981C[w->value];
        DrawSprite(w->x, (u16)w->y2 - 8, gfx,
                   w->tiles4, w->palette2, affine, pal,
                   (u16)(w->priority - 1));
    }

    if (w->collected == 0) {
        v = 204 - ((w->groundZ - w->posZ) >> 7);

        if (v <= 2) {
            v = 2;
        }

        DrawSprite(w->x2, w->y, gUnk_09EE1380[0],
                   w->tiles5, w->palette3,
                   AllocObjAffine(0, v, v, 0), pal,
                   (u16)(w->priority + 2));
    }

    TaskPoolDraw(&w->tasks);
}

static void PrizeCard_3(PrizeMapCardWork* w) {
    FadeSetPaletteExcluded(w->palette2->index + 16, 0);
    FadeSetPaletteExcluded(w->palette->index + 16, 0);
    ColliderUnregister(&w->collider);
    ReleaseObjTiles(w->tiles);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjTiles(w->tiles4);
    ReleaseObjTiles(w->tiles3);
    ReleaseObjTiles(w->tiles5);
    ReleaseObjPalette(w->palette);
    ReleaseObjPalette(w->palette2);
    ReleaseObjPalette(w->palette3);
    TaskPoolDestroy(&w->tasks);
    gBtlWork->prizeCount--;
}

void UpdatePrizeMapCardScale(PrizeMapCardWork* w) {
    w->scaleX = (-gSineTable[((w->flipAngleX + 0x80) & 0xFF) + 0x40] * w->scale) >> 8;
    w->scaleY = (-gSineTable[((w->flipAngleY + 0x80) & 0xFF) + 0x40] * w->scale) >> 8;

    if ((u16)(w->scaleX + 2) <= 4) {
        w->scaleX = 2;
    }

    if ((u16)(w->scaleY + 2) <= 4) {
        w->scaleY = 2;
    }
}

#ifndef VERSION_EU
void UpdatePrizeMapCardBackAnim(PrizeMapCardWork* w) {
    u8* p;
    u8* q;
    u8 k;
    u8 v;
    u8 z;
    v = gPrizeMapCardBackAnim[w->backAnimStep].sprite;
    q = &w->backFrame;
    z = 0;
    *q = v;
    p = &w->backAnimTimer;
    k = w->backAnimStep;

    if (*p == gPrizeMapCardBackAnim[k].duration) {
        w->backAnimStep = k + 1;

        if (w->backAnimStep == 7) {
            w->backAnimStep = z;
        }

        *p = z;
    }

    w->backAnimTimer++;
}
#endif

void CreatePrizeMapCardTask(TaskPool* pool, s32* args) {
    TaskCreate(pool, &gTaskDescPrizeMapCard, args);
}

void SpotLight_0(SpotlightWork* w, u8* src) {
    if (src != NULL) {
        w->endFlag = src;
    } else {
        w->endFlag = &w->ownEndFlag;
        w->ownEndFlag = 0;
    }

    LoadBgTiles(0, gUnk_09501778, 0xCA0);
    LoadPalette(gUnk_09618C38, gUnk_050001A0, 32);
    FadeSetPaletteExcluded(13, 1);
    LoadBgMap(0, gUnk_0960F2B8, 0x800);
    SetBgScroll(0, 0, 0);
    w->steps = 30;
    w->blendB = 0x1000;
    w->blendA = 0;
    FadeStartOut(FADE_MODE_BLACK, 30);
    gBldCnt = (BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
}

u8 SpotLight_1(SpotlightWork* w, void* a) {
    ApproachValue(&w->blendA, 0x1000, w->steps);

    if (w->steps != 0) {
        w->steps--;
        w->bldAlpha = ((w->blendB >> 8) << 8) | (w->blendA >> 8);
        gBldAlpha = w->bldAlpha;
    }

    if (*w->endFlag == 1) {
        FadeStartIn(FADE_MODE_BLACK, 30);
        w->steps = 30;
        gBldCnt = (BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateSpotLightFadeOut);
    }

    return 1;
}

s32 UpdateSpotLightFadeOut(SpotlightWork* w) {
    s32 v;

    ApproachValue(&w->blendA, 0, w->steps);

    if (w->steps != 0) {
        w->steps--;
    }

    v = ((w->blendB >> 8) << 8) | (w->blendA >> 8);
    w->bldAlpha = v;
    gBldAlpha = v;
    return 1;
}

void SpotLight_2(void) {
}

void SpotLight_3(void) {
    FadeSetPaletteExcluded(13, 0);
}

void SELMAP_EVKEY_0(SelmapEventKeyWork* work, SelmapEventKeyArgs* a) {
    s32 zero;
    s32 i;

    zero = 0;
    CpuSet(&zero, work, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(SelmapEventKeyWork) / 4);
    work->args = a;
    work->unk_F8 = a->unk_04;
    work->keyCount = CountRemainingEventKeys();

    for (i = 0; i < work->keyCount; i++) {
        InitEventKeyCard(&work->cards[i], GetEventKey((u8)i));

        if (work->cards[i].sprite.palette != NULL) {
            FadeSetPaletteExcluded(work->cards[i].sprite.palette->index + 16, 1);
        }

        if (work->cards[i].sprite.palette2 != NULL) {
            FadeSetPaletteExcluded(work->cards[i].sprite.palette2->index + 16, 1);
        }

        if (work->cards[i].sprite.palette3 != NULL) {
            FadeSetPaletteExcluded(work->cards[i].sprite.palette3->index + 16, 1);
        }
    }

#ifdef VERSION_EU
    work->tiles = AllocObjTiles(0x800, 0);
    SetObjTileSource(work->tiles, gSelmapEventKeyTitleTilesByLanguage[gLanguage]);
    AnimInit(&work->anim, gSelmapEventKeyTitleAnimsByLanguage[gLanguage], gSelmapEventKeyTitleFramesByLanguage[gLanguage]);
#else
#ifdef VERSION_JP
    work->tiles = AllocObjTiles(0x480, 0);
#else
    work->tiles = AllocObjTiles(0x6C0, 0);
#endif
    SetObjTileSource(work->tiles, gUnk_093F6ACC);
    AnimInit(&work->anim, gUnk_09EF1224, gUnk_09EF1220);
#endif
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    work->palette = work->args->palette;
    work->unk_11C = 0;
    work->unk_11D = 0;
    work->mosaicX = 8;
    work->mosaicY = 8;
    work->mosaicTimer = 0;
    work->unk_123 = 0;
    SetObjMosaicSize(work->mosaicX, work->mosaicY);
    work->rowX = 0x7800;
    work->rowY = 0x4000;
    work->unk_114 = 0x100;
    work->unk_116 = 0x100;
    work->unk_11B = 0;
    work->paidCount = 0;
    work->slideSteps = 8;
    work->pulseAngle = 0;
    SetLayeredCardSpritePos(0x10000, work->rowY, &work->cards[0].sprite);
    SetLayeredCardSpritePos(0x10000, work->rowY, &work->cards[1].sprite);
    SetLayeredCardSpritePos(0x10000, work->rowY, &work->cards[2].sprite);
    SetLayeredCardSpritePos(0x10000, work->rowY, &work->cards[3].sprite);
}

s32 SELMAP_EVKEY_1(SelmapEventKeyWork* work, void* a) {
    s32 i;
    EventKey* r;
    u8 n;

    work->gfx = AnimUpdate(&work->anim);
    work->rowTargetX = ((240 - (work->keyCount - work->paidCount) * 32) << 7) + 0x1000;
    ApproachValue(&work->rowX, work->rowTargetX, work->slideSteps);

    if (work->slideSteps != 0) {
        work->slideSteps--;
    }

    for (i = work->paidCount; i < work->keyCount; i++) {
        SetLayeredCardSpritePos(work->rowX + ((i - work->paidCount) << 13), work->rowY, &work->cards[i].sprite);
    }

    SetObjMosaicSize(work->mosaicX, work->mosaicY);

    if (work->mosaicTimer == 2) {
        if (work->mosaicX != 0) {
            work->mosaicX--;
        }

        if (work->mosaicY != 0) {
            work->mosaicY--;
        }

        work->mosaicTimer = 0;
    }

    work->mosaicTimer++;
    work->unk_11D++;

    if (work->args->closeMode != 0) {
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateSelmapEventKeyClose);
    }

    if (work->cards[work->paidCount].total != 0) {
        r = GetEventKey(0);
        work->cards[work->paidCount].total = r->value;
        n = work->paidCount;

        if (work->cards[n].drawnTotal != work->cards[n].total) {
            UpdateEventKeyTotal(&work->cards[n]);
        }
    }

    work->pulseAngle += 8;
    return 1;
}

s32 UpdateSelmapEventKeyClose(SelmapEventKeyWork* work) {
    u8* a;
    u8* b;

    a = &work->mosaicX;

    if (*a <= 14) {
        (*a)++;
    }

    b = &work->mosaicY;

    if (*b <= 14) {
        (*b)++;
    }

    SetObjMosaicSize(*a, *b);
    return 1;
}

void SELMAP_EVKEY_2(SelmapEventKeyWork* work) {
    s32 i;

    switch (work->args->closeMode) {
    case 0:
    case 2:
        if (work->mosaicX == 15) {
            return;
        }

        if (work->mosaicY == 15) {
            break;
        }

        for (i = work->paidCount; i < work->keyCount; i++) {
            if (i == work->paidCount) {
                DrawLayeredCardSpriteScaled(&work->cards[i].sprite, 0x808, 0,
                              (gSineTable[(u8)work->pulseAngle] >> 8) * 8 + 256);

                switch (work->cards[i].color) {
                case 2:
                    DrawSprite(work->cards[i].sprite.x >> 8, (work->cards[i].sprite.y >> 8) + 8,
                               gMapCardUiResources.sprites[4], gMapCardUiResources.extraTiles, gMapCardUiResources.palette, 0, SPRITE_FLAG_MOSAIC, 20);
                    break;
                case 3:
                    DrawSprite(work->cards[i].sprite.x >> 8, (work->cards[i].sprite.y >> 8) + 8,
                               gMapCardUiResources.sprites[8], gMapCardUiResources.extraTiles, gMapCardUiResources.palette, 0, SPRITE_FLAG_MOSAIC, 20);
                    break;
                case 1:
                    DrawSprite(work->cards[i].sprite.x >> 8, (work->cards[i].sprite.y >> 8) + 8,
                               gMapCardUiResources.sprites[6], gMapCardUiResources.extraTiles, gMapCardUiResources.palette, 0, SPRITE_FLAG_MOSAIC, 20);
                    break;
                case 0:
                case 4:
                default:
                    break;
                }
            } else {
                DrawLayeredCardSprite(&work->cards[i].sprite, 0x808);
            }
        }

        break;
    }

    if (work->mosaicX == 15) {
        return;
    }

    if (work->mosaicY == 15) {
        return;
    }

    DrawSprite(120, 42, work->gfx, work->tiles, work->palette, 0, SPRITE_FLAG_MOSAIC, 10);
}

void SELMAP_EVKEY_3(SelmapEventKeyWork* work) {
    s32 i;

    for (i = 0; i < work->keyCount; i++) {
        ReleaseLayeredCardSprite(&work->cards[i].sprite);
    }

    ReleaseObjTiles(work->tiles);
}

void InitEventKeyCard(EventKeyCard* work, EventKey* key) {
    s32 zero;
    MapCardDef* c;
    MapCardBackDef* b;
    MapCardBackDef* d;
    CardBack* cb;
    u8 n;
    void* z;
    u8 t;
    u8* q;

    zero = 0;
    CpuSet((void*)&zero, work, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(EventKeyCard) / 4);

    if (key->kind != 255) {
        c = &gMapCardDefs[key->kind * 10];
        b = &gMapCardBackDefs[c->backIndex];
        work->sprite.tiles = LoadObjTiles(c->tiles, c->tilesSize);
        work->sprite.palette = LoadObjPalette(c->palette, c->paletteSize);
        work->sprite.gfx = *c->sprites;
        work->sprite.tiles2 = LoadObjTiles(b->tiles, b->tilesSize);
        work->sprite.palette2 = LoadObjPalette(b->palette, b->paletteSize);
        work->sprite.gfx2 = *b->sprites;
        work->sprite.tiles3 = 0;
        work->sprite.palette3 = 0;
        return;
    }

    work->sprite.tiles = 0;
    work->sprite.palette = 0;
    work->sprite.gfx = 0;
    work->sprite.tiles3 = 0;
    work->sprite.palette3 = 0;

    if (key->color == 0) {
        n = key->color;
        work->sprite.tiles2 = 0;
        work->sprite.palette2 = 0;
        work->sprite.gfx2 = 0;
    } else {
        d = &gMapCardBackDefs[key->color];
        work->sprite.tiles2 = LoadObjTiles(d->tiles2, d->tilesSize2);
        work->sprite.palette2 = LoadObjPalette(d->palette, d->paletteSize);
        work->sprite.gfx2 = *d->sprites2;
        work->sprite.tiles3 = 0;
        work->sprite.tiles = 0;
        work->sprite.palette = 0;
        work->sprite.gfx = 0;
        work->sprite.palette3 = 0;

        switch (key->color) {
        case 1:
            n = 1;
            break;
        case 2:
            n = 2;
            break;
        case 3:
            n = 3;
            break;
        default:
            n = key->color;
            break;
        }
    }

    q = &work->color;
    *q = (z = 0, n);

    if (key->rule == 0) {
        return;
    }

    switch (key->rule) {
    case 1:
        if (key->value <= 9) {
            work->sprite.tiles3 = AllocSpriteFrameTiles(0x100);
            UpdateSpriteFrameTiles(work->sprite.tiles3, gUnk_09EF1198[1], gUnk_0950C478);
            work->sprite.gfx3 = z;
            RequestDma3Copy((u8*)work->sprite.tiles3->src + key->value * 128, &gUnk_06010000[(work->sprite.tiles3->index + 4) * 32], 128);
            RequestDma3Copy((u8*)work->sprite.tiles3->src + 0x500, &gUnk_06010000[work->sprite.tiles3->index * 32], 128);
        } else {
            work->sprite.tiles3 = AllocSpriteFrameTiles(0x180);
            UpdateSpriteFrameTiles(work->sprite.tiles3, gUnk_09EF1198[3], gUnk_0950C478);
            work->sprite.gfx3 = z;
            RequestDma3Copy((u8*)work->sprite.tiles3->src + (u8)(key->value / 10) * 128, &gUnk_06010000[(work->sprite.tiles3->index + 4) * 32], 128);
            RequestDma3Copy((u8*)work->sprite.tiles3->src + (key->value - (u8)(key->value / 10) * 10) * 128, &gUnk_06010000[(work->sprite.tiles3->index + 8) * 32], 128);
            RequestDma3Copy((u8*)work->sprite.tiles3->src + 0x500, &gUnk_06010000[work->sprite.tiles3->index * 32], 128);
        }

        break;
    case 2:
        if (key->value <= 9) {
            work->sprite.tiles3 = AllocSpriteFrameTiles(0x100);
            UpdateSpriteFrameTiles(work->sprite.tiles3, gUnk_09EF1198[1], gUnk_0950C478);
            work->sprite.gfx3 = z;
            RequestDma3Copy((u8*)work->sprite.tiles3->src + key->value * 128, &gUnk_06010000[(work->sprite.tiles3->index + 4) * 32], 128);
            RequestDma3Copy((u8*)work->sprite.tiles3->src + 0x580, &gUnk_06010000[work->sprite.tiles3->index * 32], 128);
        } else {
            work->sprite.tiles3 = AllocSpriteFrameTiles(0x180);
            UpdateSpriteFrameTiles(work->sprite.tiles3, gUnk_09EF1198[3], gUnk_0950C478);
            work->sprite.gfx3 = z;
            RequestDma3Copy((u8*)work->sprite.tiles3->src + (u8)(key->value / 10) * 128, &gUnk_06010000[(work->sprite.tiles3->index + 4) * 32], 128);
            RequestDma3Copy((u8*)work->sprite.tiles3->src + (key->value - (u8)(key->value / 10) * 10) * 128, &gUnk_06010000[(work->sprite.tiles3->index + 8) * 32], 128);
            RequestDma3Copy((u8*)work->sprite.tiles3->src + 0x580, &gUnk_06010000[work->sprite.tiles3->index * 32], 128);
        }

        break;
    case 3:
        if (key->value <= 9) {
            work->sprite.tiles3 = AllocSpriteFrameTiles(0x100);
            UpdateSpriteFrameTiles(work->sprite.tiles3, gUnk_09EF1198[1], gUnk_0950C478);
            work->sprite.gfx3 = z;
            RequestDma3Copy((u8*)work->sprite.tiles3->src + key->value * 128, &gUnk_06010000[(work->sprite.tiles3->index + 4) * 32], 128);
            RequestDma3Copy((u8*)work->sprite.tiles3->src + 0x600, &gUnk_06010000[work->sprite.tiles3->index * 32], 128);
        } else {
            work->sprite.tiles3 = AllocSpriteFrameTiles(0x180);
            UpdateSpriteFrameTiles(work->sprite.tiles3, gUnk_09EF1198[3], gUnk_0950C478);
            work->sprite.gfx3 = z;
            RequestDma3Copy((u8*)work->sprite.tiles3->src + (u8)(key->value / 10) * 128, &gUnk_06010000[(work->sprite.tiles3->index + 4) * 32], 128);
            RequestDma3Copy((u8*)work->sprite.tiles3->src + (key->value - (u8)(key->value / 10) * 10) * 128, &gUnk_06010000[(work->sprite.tiles3->index + 8) * 32], 128);
            RequestDma3Copy((u8*)work->sprite.tiles3->src + 0x600, &gUnk_06010000[work->sprite.tiles3->index * 32], 128);
        }

        break;
    case 4:
        if (key->value <= 9) {
            work->sprite.tiles3 = AllocSpriteFrameTiles(0x80);
            UpdateSpriteFrameTiles(work->sprite.tiles3, gUnk_09EF1198[0], gUnk_0950C478);
            work->sprite.gfx3 = z;
            RequestDma3Copy((u8*)work->sprite.tiles3->src + key->value * 128, &gUnk_06010000[work->sprite.tiles3->index * 32], 128);
        } else {
            work->sprite.tiles3 = AllocSpriteFrameTiles(0x100);
            UpdateSpriteFrameTiles(work->sprite.tiles3, gUnk_09EF1198[2], gUnk_0950C478);
            work->sprite.gfx3 = z;
            RequestDma3Copy((u8*)work->sprite.tiles3->src + (u8)(key->value / 10) * 128, &gUnk_06010000[work->sprite.tiles3->index * 32], 128);
            RequestDma3Copy((u8*)work->sprite.tiles3->src + (key->value - (u8)(key->value / 10) * 10) * 128, &gUnk_06010000[(work->sprite.tiles3->index + 4) * 32], 128);
        }

        t = key->value;
        work->total = t;
        work->drawnTotal = t;
        break;
    }

    work->sprite.tiles = 0;
    work->sprite.palette = 0;
    work->sprite.gfx = 0;
    work->sprite.palette3 = LoadObjPalette(gUnk_09618D38, 32);

    if (work->sprite.tiles2 == NULL) {
        cb = &gCardBacks[4];
        work->sprite.tiles2 = LoadObjTiles(cb->tiles2, 0x300);
        work->sprite.palette2 = LoadObjPalette(gUnk_09618D38, 32);
        work->sprite.gfx2 = cb->gfx2;
    }
}

void UpdateEventKeyTotal(EventKeyCard* w) {
    void* z;

    if (w->total <= 9) {
        z = 0;
        UpdateSpriteFrameTiles(w->sprite.tiles3, gUnk_09EF1198[0], gUnk_0950C478);
        w->sprite.gfx3 = z;
        RequestDma3Copy((u8*)w->sprite.tiles3->src + w->total * 128, &gUnk_06010000[w->sprite.tiles3->index * 32], 128);
    } else {
        z = 0;
        UpdateSpriteFrameTiles(w->sprite.tiles3, gUnk_09EF1198[2], gUnk_0950C478);
        w->sprite.gfx3 = z;
        RequestDma3Copy((u8*)w->sprite.tiles3->src + (u16)(w->total / 10) * 128, &gUnk_06010000[w->sprite.tiles3->index * 32], 128);
        RequestDma3Copy((u8*)w->sprite.tiles3->src + (w->total - (u16)(w->total / 10) * 10) * 128, &gUnk_06010000[(w->sprite.tiles3->index + 4) * 32], 128);
    }

    w->drawnTotal = w->total;
}

void SetLayeredCardSpritePos(s32 x, s32 y, LayeredCardSprite* p) {
    p->x = x;
    p->y = y;
}

void DrawLayeredCardSpriteScaled(LayeredCardSprite* w, u16 b, s16 c, s16 d) {
    ObjAffine* aff;

    aff = AllocObjAffine(0, d, d, 1);

    if (w->tiles != NULL) {
        DrawSprite(w->x >> 8, c + (w->y >> 8), w->gfx, w->tiles, w->palette, aff, b, 10);
    }

    if (w->tiles2 != NULL) {
        DrawSprite(w->x >> 8, c + (w->y >> 8), w->gfx2, w->tiles2, w->palette2, aff, b, 9);
    }

    if (w->tiles3 != NULL) {
        DrawSprite(w->x >> 8, c + (w->y >> 8), w->gfx3, w->tiles3, w->palette3, aff, b, 8);
    }
}

void DrawLayeredCardSprite(LayeredCardSprite* p, u16 a) {
    if (p->tiles != NULL) {
        DrawSprite(p->x >> 8, p->y >> 8, p->gfx, p->tiles, p->palette, 0, a, 10);
    }

    if (p->tiles2 != NULL) {
        DrawSprite(p->x >> 8, p->y >> 8, p->gfx2, p->tiles2, p->palette2, 0, a, 9);
    }

    if (p->tiles3 != NULL) {
        DrawSprite(p->x >> 8, p->y >> 8, p->gfx3, p->tiles3, p->palette3, 0, a, 8);
    }
}

ObjTiles* AllocKeyValueTiles(u8 a) {
    ObjTiles* obj;

    if (a != 0) {
        obj = AllocSpriteFrameTiles(256);
        UpdateSpriteFrameTiles(obj, gUnk_09EF1198[1], gUnk_0950C478);
        RequestDma3Copy(&((u8*)obj->src)[a * 128], (void*)(0x06010000 + (obj->index + 4) * 32), 128);
        RequestDma3Copy(&((u8*)obj->src)[0x500], (void*)(0x06010000 + obj->index * 32), 128);
    } else {
        obj = AllocSpriteFrameTiles(128);
        UpdateSpriteFrameTiles(obj, gUnk_09EF1198[0], gUnk_0950C478);
    }

    return obj;
}

void ReleaseLayeredCardSprite(LayeredCardSprite* p) {
    if (p->tiles != NULL) {
        ReleaseObjTiles(p->tiles);
    }

    if (p->tiles2 != NULL) {
        ReleaseObjTiles(p->tiles2);
    }

    if (p->tiles3 != NULL) {
        ReleaseObjTiles(p->tiles3);
    }

    if (p->palette != NULL) {
        ReleaseObjPalette(p->palette);
    }

    if (p->palette2 != NULL) {
        ReleaseObjPalette(p->palette2);
    }

    if (p->palette3 != NULL) {
        ReleaseObjPalette(p->palette3);
    }
}

u8 GetRoomCardBackIndex(u16 n) {
    u8 idx;

    idx = 0;

    switch (n) {
    case 1:
        idx = 0;
        break;
    case 2:
        idx = 170;
        break;
    case 3:
        idx = 50;
        break;
    case 4:
        idx = 40;
        break;
    case 5:
        idx = 190;
        break;
    case 6:
        idx = 20;
        break;
    case 7:
        idx = 30;
        break;
    case 8:
        idx = 160;
        break;
    case 9:
        idx = 180;
        break;
    case 10:
        idx = 210;
        break;
    case 11:
        idx = 100;
        break;
    case 12:
        idx = 90;
        break;
    case 13:
        idx = 110;
        break;
    case 14:
        idx = 120;
        break;
    case 15:
        idx = 200;
        break;
    case 16:
        idx = 140;
        break;
    case 17:
        idx = 150;
        break;
    case 18:
        idx = 130;
        break;
    case 19:
        idx = 60;
        break;
    case 20:
        idx = 70;
        break;
    case 21:
        idx = 80;
        break;
    case 22:
        idx = 220;
        break;
    case 23:
        idx = 230;
        break;
    case 24:
        idx = 240;
        break;
    case 0:
    case 26:
        idx = 10;
        break;
    case 25:
    case 27:
        idx = 250;
        break;
    }

    return gMapCardDefs[idx].backIndex;
}

TaskDesc gTaskDescPrizeCardInit = {
    "PrizeCardInit",
    (TaskInitFunc)PrizeCardInitInit,
    (TaskUpdateFunc)PrizeCardInit_1,
    (TaskDrawFunc)PrizeCardInitDraw,
    (TaskDestroyFunc)PrizeCardInitDestroy,
    sizeof(PrizeCardInitWork),
};

TaskDesc gTaskDescPrizeCardInitBoss = {
    "PrizeCardInit_Boss",
    (TaskInitFunc)PrizeCardInitInit,
    (TaskUpdateFunc)PrizeCardInit_Boss_1,
    (TaskDrawFunc)PrizeCardInitDraw,
    (TaskDestroyFunc)PrizeCardInitDestroy,
    sizeof(PrizeCardInitWork),
};

TaskDesc gTaskDescDispCardname = {
    "DispCardname",
    (TaskInitFunc)DispCardname_0,
    (TaskUpdateFunc)DispCardname_1,
    (TaskDrawFunc)DispCardname_2,
    (TaskDestroyFunc)DispCardname_3,
    sizeof(DispCardnameWork),
};

TaskDesc gTaskDescVersion = {
    "Version",
    (TaskInitFunc)Version_0,
    (TaskUpdateFunc)Version_1,
    (TaskDrawFunc)Version_2,
    (TaskDestroyFunc)Version_3,
    sizeof(VersionWork),
};

TaskDesc gTaskDescPrizeMapCard = {
    "PrizeCard",
    (TaskInitFunc)PrizeCard_0,
    (TaskUpdateFunc)PrizeCard_1,
    (TaskDrawFunc)PrizeCard_2,
    (TaskDestroyFunc)PrizeCard_3,
    sizeof(PrizeMapCardWork),
};

TaskDesc gTaskDescSpotLight = {
    "SpotLight",
    (TaskInitFunc)SpotLight_0,
    (TaskUpdateFunc)SpotLight_1,
    (TaskDrawFunc)SpotLight_2,
    (TaskDestroyFunc)SpotLight_3,
    sizeof(SpotlightWork),
};

#ifdef VERSION_EU
void* gSelmapEventKeyTitleAnimsByLanguage[5] = { gUnk_09EF1224, gUnkEu_09F7C438, gUnkEu_09F7C450, gUnkEu_09F7C448, gUnkEu_09F7C440 };
void* gSelmapEventKeyTitleFramesByLanguage[5] = { gUnk_09EF1220, gUnkEu_09F7C434, gUnkEu_09F7C44C, gUnkEu_09F7C444, gUnkEu_09F7C43C };
void* gSelmapEventKeyTitleTilesByLanguage[5] = { gUnk_093F6ACC, gUnkEu_094C7CCE, gUnkEu_094C9180, gUnkEu_094C8946, gUnkEu_094C8288 };
#endif

TaskDesc gTaskDescSELMAPEVKEY = {
    "SELMAP_EVKEY",
    (TaskInitFunc)SELMAP_EVKEY_0,
    (TaskUpdateFunc)SELMAP_EVKEY_1,
    (TaskDrawFunc)SELMAP_EVKEY_2,
    (TaskDestroyFunc)SELMAP_EVKEY_3,
    sizeof(SelmapEventKeyWork),
};
