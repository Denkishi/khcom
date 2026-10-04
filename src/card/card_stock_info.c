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
static const CardHelpDef sUnk_0903BD0C = {
    gUnk_09EE7A38,
    2,
    { 0, 0, 0 },
};
#endif

#if defined(VERSION_US)
static const CardHelpDef sUnk_0903BD14 = {
    gUnk_09EE7A40,
    2,
    { 0, 0, 0 },
};
#endif

#if defined(VERSION_JP)
static const CardHelpDef sUnk_0903BD0C = {
    gUnk_09EE7A38,
    2,
    { 0, 0, 0 },
};
#endif

#if defined(VERSION_JP)
#include "card_help_pages_head.inc"
#endif
#if defined(VERSION_JP)
static const CardHelpDef sUnk_0903BD14 = {
    gUnk_09EE7A40,
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

static const CardHelpDef sUnk_0903BD1C = {
    gUnk_09EE7A48,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BD24 = {
    gUnk_09EE7A50,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BD2C = {
    gUnk_09EE7A60,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BD34 = {
    gUnk_09EE79F4,
#if defined(VERSION_US) || defined(VERSION_EU)
    3,
#elif defined(VERSION_JP)
    2,
#endif
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BD3C = {
    gUnk_09EE7A08,
    2,
    { 0, 0, 0 },
};

#if defined(VERSION_EU)
static const CardHelpDef sUnk_0903BD0C = {
    gUnk_09EE7A38,
    2,
    { 0, 0, 0 },
};
#endif

static const CardHelpDef sUnk_0903BD44 = {
    gUnk_09EE7A70,
    2,
    { 0, 0, 0 },
};

#if defined(VERSION_EU)
static const CardHelpDef sUnk_0903BD14 = {
    gUnk_09EE7A40,
    2,
    { 0, 0, 0 },
};
#endif

static const CardHelpDef sUnk_0903BD4C = {
    gUnk_09EE7A78,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BD54 = {
    gUnk_09EE7A80,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BD5C = {
    gUnk_09EE7A88,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BD64 = {
    gUnk_09EE7A58,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BD6C = {
    gUnk_09EE7A90,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BD74 = {
    gUnk_09EE7A98,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BD7C = {
    gUnk_09EE7B98,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BD84 = {
    gUnk_09EE7BA0,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BD8C = {
    gUnk_09EE7B78,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BD94 = {
    gUnk_09EE7B88,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BD9C = {
    gUnk_09EE7AA8,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BDA4 = {
    gUnk_09EE7AB8,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BDAC = {
    gUnk_09EE7AC8,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BDB4 = {
    gUnk_09EE7AD8,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BDBC = {
    gUnk_09EE7B38,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BDC4 = {
    gUnk_09EE7B48,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BDCC = {
    gUnk_09EE7B58,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BDD4 = {
    gUnk_09EE7B68,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BDDC = {
    gUnk_09EE7AE8,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BDE4 = {
    gUnk_09EE7AF8,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BDEC = {
    gUnk_09EE7B08,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BDF4 = {
    gUnk_09EE7B18,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BDFC = {
    gUnk_09EE7B28,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE04 = {
    gUnk_09EE7B30,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE0C = {
    gUnk_09EE7BA8,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE14 = {
    gUnk_09EE7BB8,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE1C = {
    gUnk_09EE7BE8,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE24 = {
    gUnk_09EE7BF8,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE2C = {
    gUnk_09EE7BC8,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE34 = {
    gUnk_09EE7BD8,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE3C = {
    gUnk_09EE7C08,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE44 = {
    gUnk_09EE7C18,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE4C = {
    gUnk_09EE7C28,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE54 = {
    gUnk_09EE7C38,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE5C = {
    gUnk_09EE7D54,
    4,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE64 = {
    gUnk_09EE7D64,
#if defined(VERSION_US) || defined(VERSION_EU)
    4,
#elif defined(VERSION_JP)
    2,
#endif
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE6C = {
    gUnk_09EE7A68,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE74 = {
    gUnk_09EE7AA0,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE7C = {
    gUnk_09EE79EC,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE84 = {
    gUnk_09EE7A00,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE8C = {
    gUnk_09EE7A10,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE94 = {
    gUnk_09EE7A18,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BE9C = {
    gUnk_09EE7A20,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BEA4 = {
    gUnk_09EE7A28,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BEAC = {
    gUnk_09EE7A30,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BEB4 = {
    gUnk_09EE7C48,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BEBC = {
    gUnk_09EE7C50,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BEC4 = {
    gUnk_09EE7C58,
    3,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BECC = {
    gUnk_09EE7C64,
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

static const CardHelpDef sUnk_0903BEDC = {
    gUnk_09EE7C6C,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BEE4 = {
    gUnk_09EE7C74,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BEEC = {
    gUnk_09EE7C7C,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BEF4 = {
    gUnk_09EE7C84,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BEFC = {
    gUnk_09EE7C8C,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF04 = {
    gUnk_09EE7C94,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF0C = {
    gUnk_09EE7C9C,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF14 = {
    gUnk_09EE7CA4,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF1C = {
    gUnk_09EE7CAC,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF24 = {
    gUnk_09EE7CB4,
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

static const CardHelpDef sUnk_0903BF34 = {
    gUnk_09EE7CBC,
    3,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF3C = {
    gUnk_09EE7CC8,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF44 = {
    gUnk_09EE7CD0,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF4C = {
    gUnk_09EE7CD8,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF54 = {
    gUnk_09EE7CE0,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF5C = {
    gUnk_09EE7CE8,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF64 = {
    gUnk_09EE7CF0,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF6C = {
    gUnk_09EE7CF8,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF74 = {
    gUnk_09EE7D00,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF7C = {
    gUnk_09EE7D08,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF84 = {
    gUnk_09EE7D10,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF8C = {
    gUnk_09EE7D18,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF94 = {
    gUnk_09EE7D20,
    3,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BF9C = {
    gUnk_09EE7D2C,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BFA4 = {
    gUnk_09EE7D34,
    2,
    { 0, 0, 0 },
};

static const CardHelpDef sUnk_0903BFAC = {
    gUnk_09EE7D3C,
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
const CardHelpText* gUnk_09EE79EC[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_090381F8,
    gCardHelpTextUs_09038260,
#elif defined(VERSION_EU)
    &gCardHelp46Text0,
    &gCardHelp46Text1,
#endif
};
#endif

const CardHelpText* gUnk_09EE79F4[] = {
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
const CardHelpText* gUnk_09EE7A00[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038440,
    gCardHelpTextUs_0903848E,
#elif defined(VERSION_EU)
    &gCardHelp47Text0,
    &gCardHelp47Text1,
#endif
};
#endif

const CardHelpText* gUnk_09EE7A08[] = {
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
const CardHelpText* gUnk_09EE7A10[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_090385CC,
    gCardHelpTextUs_09038646,
#elif defined(VERSION_EU)
    &gCardHelp48Text0,
    &gCardHelp48Text1,
#endif
};

const CardHelpText* gUnk_09EE7A18[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038694,
    gCardHelpTextUs_090386F0,
#elif defined(VERSION_EU)
    &gCardHelp49Text0,
    &gCardHelp49Text1,
#endif
};

const CardHelpText* gUnk_09EE7A20[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038736,
    gCardHelpTextUs_090387A4,
#elif defined(VERSION_EU)
    &gCardHelp50Text0,
    &gCardHelp50Text1,
#endif
};

const CardHelpText* gUnk_09EE7A28[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_0903881C,
    gCardHelpTextUs_0903887A,
#elif defined(VERSION_EU)
    &gCardHelp51Text0,
    &gCardHelp51Text1,
#endif
};

const CardHelpText* gUnk_09EE7A30[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_090388F2,
    gCardHelpTextUs_0903897C,
#elif defined(VERSION_EU)
    &gCardHelp52Text0,
    &gCardHelp52Text1,
#endif
};
#endif

const CardHelpText* gUnk_09EE7A38[] = {
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

const CardHelpText* gUnk_09EE7A40[] = {
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

const CardHelpText* gUnk_09EE7A48[] = {
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

const CardHelpText* gUnk_09EE7A50[] = {
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
const CardHelpText* gUnk_09EE7A58[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038BAC,
    gCardHelpTextUs_09038C10,
#elif defined(VERSION_EU)
    &gCardHelp11Text0,
    &gCardHelp11Text1,
#endif
};
#endif

const CardHelpText* gUnk_09EE7A60[] = {
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
const CardHelpText* gUnk_09EE7A68[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09038CB2,
    gCardHelpTextUs_09038D16,
#elif defined(VERSION_EU)
    &gCardHelp44Text0,
    &gCardHelp44Text1,
#endif
};
#endif

const CardHelpText* gUnk_09EE7A70[] = {
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

const CardHelpText* gUnk_09EE7A78[] = {
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

const CardHelpText* gUnk_09EE7A80[] = {
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

const CardHelpText* gUnk_09EE7A88[] = {
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
const CardHelpText* gUnk_09EE7A58[] = {
    gCardHelpTextJp_0900BBB8,
    gCardHelpTextJp_0900BBE4,
};
#endif

const CardHelpText* gUnk_09EE7A90[] = {
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

const CardHelpText* gUnk_09EE7A98[] = {
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
const CardHelpText* gUnk_09EE7AA0[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09039098,
    gCardHelpTextUs_09039110,
#elif defined(VERSION_EU)
    &gCardHelp45Text0,
    &gCardHelp45Text1,
#endif
};
#endif

const CardHelpText* gUnk_09EE7AA8[] = {
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

const CardHelpText* gUnk_09EE7AB8[] = {
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

const CardHelpText* gUnk_09EE7AC8[] = {
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

const CardHelpText* gUnk_09EE7AD8[] = {
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

const CardHelpText* gUnk_09EE7AE8[] = {
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

const CardHelpText* gUnk_09EE7AF8[] = {
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

const CardHelpText* gUnk_09EE7B08[] = {
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

const CardHelpText* gUnk_09EE7B18[] = {
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
const CardHelpText* gUnk_09EE7B30[] = {
    gCardHelpTextJp_0900BF88,
    gCardHelpTextJp_0900BF9C,
};
#endif

const CardHelpText* gUnk_09EE7B28[] = {
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
const CardHelpText* gUnk_09EE7B30[] = {
#if defined(VERSION_US)
    gCardHelpTextUs_09039738,
    gCardHelpTextUs_0903979A,
#elif defined(VERSION_EU)
    &gCardHelp31Text0,
    &gCardHelp31Text1,
#endif
};
#endif

const CardHelpText* gUnk_09EE7B38[] = {
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

const CardHelpText* gUnk_09EE7B48[] = {
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

const CardHelpText* gUnk_09EE7B58[] = {
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

const CardHelpText* gUnk_09EE7B68[] = {
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

const CardHelpText* gUnk_09EE7B78[] = {
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

const CardHelpText* gUnk_09EE7B88[] = {
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

const CardHelpText* gUnk_09EE7B98[] = {
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

const CardHelpText* gUnk_09EE7BA0[] = {
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

const CardHelpText* gUnk_09EE7BA8[] = {
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

const CardHelpText* gUnk_09EE7BB8[] = {
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

const CardHelpText* gUnk_09EE7BC8[] = {
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

const CardHelpText* gUnk_09EE7BD8[] = {
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

const CardHelpText* gUnk_09EE7BE8[] = {
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

const CardHelpText* gUnk_09EE7BF8[] = {
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

const CardHelpText* gUnk_09EE7C08[] = {
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

const CardHelpText* gUnk_09EE7C18[] = {
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

const CardHelpText* gUnk_09EE7C28[] = {
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

const CardHelpText* gUnk_09EE7C38[] = {
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
const CardHelpText* gUnk_09EE7D54[] = {
    gCardHelpTextJp_0900D0D8,
    gCardHelpTextJp_0900D110,
    gCardHelpTextJp_0900D11C,
    gCardHelpTextJp_0900D158,
};

const CardHelpText* gUnk_09EE7D44[] = {
    gCardHelpTextJp_0900D16C,
    gCardHelpTextJp_0900D174,
};

const CardHelpText* gUnk_09EE7D64[] = {
    gCardHelpTextJp_0900D11C,
    gCardHelpTextJp_0900D158,
};

const CardHelpText* gUnk_09EE7A68[] = {
    gCardHelpTextJp_0900BC8C,
    gCardHelpTextJp_0900BCC0,
};

const CardHelpText* gUnk_09EE7AA0[] = {
    gCardHelpTextJp_0900BCD0,
    gCardHelpTextJp_0900BD08,
};

const CardHelpText* gUnk_09EE79EC[] = {
    gCardHelpTextJp_0900B684,
    gCardHelpTextJp_0900B6B0,
};

const CardHelpText* gUnk_09EE7A00[] = {
    gCardHelpTextJp_0900B76C,
    gCardHelpTextJp_0900B78C,
};

const CardHelpText* gUnk_09EE7A10[] = {
    gCardHelpTextJp_0900B81C,
    gCardHelpTextJp_0900B83C,
};

const CardHelpText* gUnk_09EE7A18[] = {
    gCardHelpTextJp_0900B864,
    gCardHelpTextJp_0900B8A0,
};

const CardHelpText* gUnk_09EE7A20[] = {
    gCardHelpTextJp_0900B8C8,
    gCardHelpTextJp_0900B8F0,
};

const CardHelpText* gUnk_09EE7A28[] = {
    gCardHelpTextJp_0900B928,
    gCardHelpTextJp_0900B950,
};

const CardHelpText* gUnk_09EE7A30[] = {
    gCardHelpTextJp_0900B988,
    gCardHelpTextJp_0900B9C4,
};
#endif

const CardHelpText* gUnk_09EE7C48[] = {
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

const CardHelpText* gUnk_09EE7C50[] = {
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

const CardHelpText* gUnk_09EE7C58[] = {
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

const CardHelpText* gUnk_09EE7C64[] = {
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

const CardHelpText* gUnk_09EE7C6C[] = {
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

const CardHelpText* gUnk_09EE7C74[] = {
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

const CardHelpText* gUnk_09EE7C7C[] = {
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

const CardHelpText* gUnk_09EE7C84[] = {
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

const CardHelpText* gUnk_09EE7C8C[] = {
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

const CardHelpText* gUnk_09EE7C94[] = {
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

const CardHelpText* gUnk_09EE7C9C[] = {
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

const CardHelpText* gUnk_09EE7CA4[] = {
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

const CardHelpText* gUnk_09EE7CAC[] = {
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

const CardHelpText* gUnk_09EE7CB4[] = {
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

const CardHelpText* gUnk_09EE7CBC[] = {
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

const CardHelpText* gUnk_09EE7CC8[] = {
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

const CardHelpText* gUnk_09EE7CD0[] = {
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

const CardHelpText* gUnk_09EE7CD8[] = {
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

const CardHelpText* gUnk_09EE7CE0[] = {
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

const CardHelpText* gUnk_09EE7CE8[] = {
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

const CardHelpText* gUnk_09EE7CF0[] = {
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

const CardHelpText* gUnk_09EE7CF8[] = {
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

const CardHelpText* gUnk_09EE7D00[] = {
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

const CardHelpText* gUnk_09EE7D08[] = {
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

const CardHelpText* gUnk_09EE7D10[] = {
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

const CardHelpText* gUnk_09EE7D18[] = {
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

const CardHelpText* gUnk_09EE7D20[] = {
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

const CardHelpText* gUnk_09EE7D2C[] = {
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

const CardHelpText* gUnk_09EE7D34[] = {
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

const CardHelpText* gUnk_09EE7D3C[] = {
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

const CardHelpText* gUnk_09EE7D54[] = {
    gCardHelpTextUs_0903BB76,
    gCardHelpTextUs_0903BBF8,
    gCardHelpTextUs_0903BC24,
    gCardHelpTextUs_0903BCB8,
};

const CardHelpText* gUnk_09EE7D64[] = {
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
const CardHelpText* gUnk_09EE7D54[] = {
    &gCardHelp42Text0,
    &gCardHelp42Text1,
    &gCardHelp42Text2,
    &gCardHelp42Text3,
};

const CardHelpText* gUnk_09EE7D64[] = {
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
    &sUnk_0903BD0C,
    &sUnk_0903BD14,
    &sUnk_0903BD1C,
    &sUnk_0903BD24,
    &sUnk_0903BD2C,
    &sUnk_0903BD34,
    &sUnk_0903BD3C,
    &sUnk_0903BD44,
    &sUnk_0903BD4C,
    &sUnk_0903BD54,
    &sUnk_0903BD5C,
    &sUnk_0903BD64,
    &sUnk_0903BD6C,
    &sUnk_0903BD74,
    &sUnk_0903BD84,
    &sUnk_0903BD7C,
    &sUnk_0903BD8C,
    &sUnk_0903BD94,
    &sUnk_0903BD9C,
    &sUnk_0903BDA4,
    &sUnk_0903BDAC,
    &sUnk_0903BDB4,
    &sUnk_0903BDBC,
    &sUnk_0903BDC4,
    &sUnk_0903BDCC,
    &sUnk_0903BDD4,
    &sUnk_0903BDDC,
    &sUnk_0903BDE4,
    &sUnk_0903BDEC,
    &sUnk_0903BDF4,
    &sUnk_0903BDFC,
    &sUnk_0903BE04,
    &sUnk_0903BE0C,
    &sUnk_0903BE14,
    &sUnk_0903BE1C,
    &sUnk_0903BE24,
    &sUnk_0903BE2C,
    &sUnk_0903BE34,
    &sUnk_0903BE3C,
    &sUnk_0903BE44,
    &sUnk_0903BE4C,
    &sUnk_0903BE54,
    &sUnk_0903BE5C,
    &sUnk_0903BE64,
    &sUnk_0903BE6C,
    &sUnk_0903BE74,
    &sUnk_0903BE7C,
    &sUnk_0903BE84,
    &sUnk_0903BE8C,
    &sUnk_0903BE94,
    &sUnk_0903BE9C,
    &sUnk_0903BEA4,
    &sUnk_0903BEAC,
    &sUnk_0903BEB4,
    &sUnk_0903BEBC,
    &sUnk_0903BEC4,
    &sUnk_0903BECC,
#if defined(VERSION_US) || defined(VERSION_JP)
    &sUnk_0903BED4,
#elif defined(VERSION_EU)
    NULL,
#endif
    &sUnk_0903BEDC,
    &sUnk_0903BEE4,
    &sUnk_0903BEEC,
    &sUnk_0903BEF4,
    &sUnk_0903BEFC,
    &sUnk_0903BF04,
    &sUnk_0903BF0C,
    &sUnk_0903BF14,
    &sUnk_0903BF1C,
    &sUnk_0903BF24,
#if defined(VERSION_US) || defined(VERSION_JP)
    &sUnk_0903BF2C,
#elif defined(VERSION_EU)
    NULL,
#endif
    &sUnk_0903BF34,
    &sUnk_0903BF3C,
    &sUnk_0903BF44,
    &sUnk_0903BF4C,
    &sUnk_0903BF54,
    &sUnk_0903BF5C,
    &sUnk_0903BF64,
    &sUnk_0903BF6C,
    &sUnk_0903BF74,
    &sUnk_0903BF7C,
    &sUnk_0903BF84,
    &sUnk_0903BF8C,
    &sUnk_0903BF94,
    &sUnk_0903BF9C,
    &sUnk_0903BFA4,
    &sUnk_0903BFAC,
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
