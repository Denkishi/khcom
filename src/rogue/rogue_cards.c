#include <stddef.h>
#include "card_def_data.h"
#include "card_def_assets.h"
#include "sprites_card_pictures.h"
#include "sprite_palettes.h"
#include "card_label_data.h"
#include "card_localized_data.h"
#include "card_label_language_data.h"
#include "mode_test_assets.h"
#include "rogue.h"
#include "card_ids.h"

// The card table: the 950 cards of the original game, then the mod's. The
// original table cannot grow where it is, so every card lookup goes through
// this one instead.

// The new cards, their names and their art come from tools/rogue_cards.py,
// which reads what each one's base card is like from the original table.
#include "rogue_card_table.inc"

const CardDef gCardDefs[ROGUE_CARD_DEFS] = {
#include "../card/card_catalog_defs.inc"
    // 950 means "no card" to the battle code, so the ten ids from it are skipped.
    { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
    ROGUE_CARD_TABLE
};

const RogueCardEffect gRogueCardEffects[ROGUE_CARD_KINDS] = {
    ROGUE_CARD_EFFECTS
};

// The table and the header must agree on how many cards there are.
typedef char RogueCardKinds_check[(ROGUE_CARD_TABLE_KINDS == ROGUE_CARD_KINDS) ? 1 : -1];
