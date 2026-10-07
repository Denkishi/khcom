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

// Italian names; the other languages get the same text.
#define CARD_NAME(name, text) \
    static const u8 name##_It[] = text; \
    static const LocalizedText name = { { (u8*)name##_It, (u8*)name##_It, (u8*)name##_It, (u8*)name##_It, (u8*)name##_It } }

CARD_NAME(sNameBondOfFlame, "Legame di fuoco");
CARD_NAME(sNameTwoBecomeOne, "Due in uno");
CARD_NAME(sNameHiddenDragon, "Drago celato");
CARD_NAME(sNameFollowTheWind, "Segui il vento");
CARD_NAME(sNameMonochrome, "Monocromia");

extern const u8 gRogueCardBondOfFlameTiles[], gRogueCardBondOfFlamePalette[], gRogueCardBondOfFlameSmallTiles[], gRogueCardBondOfFlameSmallPalette[];
extern const u8 gRogueCardTwoBecomeOneTiles[], gRogueCardTwoBecomeOnePalette[], gRogueCardTwoBecomeOneSmallTiles[], gRogueCardTwoBecomeOneSmallPalette[];
extern const u8 gRogueCardHiddenDragonTiles[], gRogueCardHiddenDragonPalette[], gRogueCardHiddenDragonSmallTiles[], gRogueCardHiddenDragonSmallPalette[];
extern const u8 gRogueCardFollowTheWindTiles[], gRogueCardFollowTheWindPalette[], gRogueCardFollowTheWindSmallTiles[], gRogueCardFollowTheWindSmallPalette[];
extern const u8 gRogueCardMonochromeTiles[], gRogueCardMonochromePalette[], gRogueCardMonochromeSmallTiles[], gRogueCardMonochromeSmallPalette[];

// A new keyblade behaves as one of the original ones: it takes that one's
// swings (action), sleight group and help text (index), with a picture, a name
// and a CP cost of its own. The cost is written for each value because only
// the original cards have theirs worked out from a base.
#define KEYBLADE(art, name, index, action, group, cp, value) \
    { gCardWep01Frame0, (void*)gRogueCard##art##Tiles, (void*)gRogueCard##art##Palette, (void*)&name, gUnk_0905F0BC, \
      (void*)gRogueCard##art##SmallTiles, (void*)gRogueCard##art##SmallPalette, \
      index, 0x0, value, { 0, 0, 0 }, action, group, 0, 0, (cp) + (cp) / 10 * ((value) == 0 ? 9 : (value) - 1), \
      { 2, 0, 0, 0, 0, 0 } }

#define KEYBLADE_VALUES(art, name, index, action, group, cp) \
    KEYBLADE(art, name, index, action, group, cp, 0), KEYBLADE(art, name, index, action, group, cp, 1), \
    KEYBLADE(art, name, index, action, group, cp, 2), KEYBLADE(art, name, index, action, group, cp, 3), \
    KEYBLADE(art, name, index, action, group, cp, 4), KEYBLADE(art, name, index, action, group, cp, 5), \
    KEYBLADE(art, name, index, action, group, cp, 6), KEYBLADE(art, name, index, action, group, cp, 7), \
    KEYBLADE(art, name, index, action, group, cp, 8), KEYBLADE(art, name, index, action, group, cp, 9)

const CardDef gCardDefs[ROGUE_CARD_DEFS] = {
#include "../card/card_catalog_defs.inc"
    // 950 means "no card" to the battle code, so the ten ids from it are skipped.
    { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
    // Bond of Flame: Lionheart's fire swings.
    KEYBLADE_VALUES(BondOfFlame, sNameBondOfFlame, 9, 0xA, 91, 30),
    // Two Become One: Oblivion's swings.
    KEYBLADE_VALUES(TwoBecomeOne, sNameTwoBecomeOne, 13, 0xE, 131, 35),
    // Hidden Dragon: Divine Rose's swings.
    KEYBLADE_VALUES(HiddenDragon, sNameHiddenDragon, 11, 0xC, 111, 30),
    // Follow the Wind: Metal Chocobo's swings.
    KEYBLADE_VALUES(FollowTheWind, sNameFollowTheWind, 7, 0x9, 71, 25),
    // Monochrome: Oathkeeper's swings.
    KEYBLADE_VALUES(Monochrome, sNameMonochrome, 12, 0xD, 121, 30),
};
