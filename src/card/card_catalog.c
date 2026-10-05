/**
 * card_catalog.c
 * Card Definition Catalog
 */

#include <stddef.h>
#include "sprites_card_pictures.h"
#include "sprite_palettes.h"
#include "card_label_data.h"
#include "card_label_language_data.h"
#include "common_text.h"
#include "card_types.h"
#include "card_ui_types.h"
#include "jiminy_data.h"
#include "types.h"

const CardBack gCardBacks[5] = {
    {
        gCardBorderRedFrame0, gCardOutlineRedFrame0, gCardBackRedFrame0, gCardBorderRedTiles, gCardOutlineRedTiles, gCardBackRedTiles,
    },
    {
        gCardBorderBlueFrame0, gCardOutlineBlueFrame0, gCardBackBlueFrame0, gCardBorderBlueTiles, gCardOutlineBlueTiles, gCardBackBlueTiles,
    },
    {
        gCardBorderGreenFrame0, gCardOutlineGreenFrame0, gCardBackGreenFrame0, gCardBorderGreenTiles, gCardOutlineGreenTiles, gCardBackGreenTiles,
    },
    {
        gCardBorderBlackFrame0, gCardOutlineBlackFrame0, gCardBackBlackFrame0, gCardBorderBlackTiles, gCardOutlineBlackTiles, gCardBackBlackTiles,
    },
    {
        gCardBorderWhiteFrame0, gCardOutlineWhiteFrame0, gCardBackWhiteFrame0, gCardBorderWhiteTiles, gCardOutlineWhiteTiles, gCardBackWhiteTiles,
    },
};

const CardBack gEnemyCardBacks[5] = {
    {
        gCardBorderBlackFrame0, gCardOutlineBlackFrame0, gEnemyCardBackFrame0, gCardBorderBlackTiles, gCardOutlineBlackTiles, gEnemyCardBackTiles,
    },
    {
        gCardBorderBlackFrame0, gCardOutlineBlackFrame0, gEnemyCardBackFrame0, gCardBorderBlackTiles, gCardOutlineBlackTiles, gEnemyCardBackTiles,
    },
    {
        gCardBorderBlackFrame0, gCardOutlineBlackFrame0, gEnemyCardBackFrame0, gCardBorderBlackTiles, gCardOutlineBlackTiles, gEnemyCardBackTiles,
    },
    {
        gCardBorderBlackFrame0, gCardOutlineBlackFrame0, gEnemyCardBackFrame0, gCardBorderBlackTiles, gCardOutlineBlackTiles, gEnemyCardBackTiles,
    },
    {
        gCardBorderBlackFrame0, gCardOutlineBlackFrame0, gEnemyCardBackFrame0, gCardBorderBlackTiles, gCardOutlineBlackTiles, gEnemyCardBackTiles,
    },
};

const u8 gBlackCircleText[3] = "\x81\x9C";

const u8 gWhiteCircleText[3] = "\x81\x9B";

const u8 gBlackStarText[3] = "\x81\x9A";

const u8 gWhiteStarText[3] = "\x81\x99";

const u8* gWhiteStarTextPtr = gWhiteStarText;
const u8* gBlackStarTextPtr = gBlackStarText;
const u8* gWhiteCircleTextPtr = gWhiteCircleText;
const u8* gBlackCircleTextPtr = gBlackCircleText;

const CardDef gCardDefs[950] = {
    {
#if defined(VERSION_US)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, &gCardNameKingdomKeyByLanguage, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#endif
        0, 0x0, 0, 0x0, 1, 0, 10, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, &gCardNameKingdomKeyByLanguage, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#endif
        0, 0x0, 1, 0x0, 1, 0, 10, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, &gCardNameKingdomKeyByLanguage, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#endif
        0, 0x0, 2, 0x0, 1, 0, 10, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, &gCardNameKingdomKeyByLanguage, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#endif
        0, 0x0, 3, 0x0, 1, 0, 10, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, &gCardNameKingdomKeyByLanguage, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#endif
        0, 0x0, 4, 0x0, 1, 0, 10, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, &gCardNameKingdomKeyByLanguage, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#endif
        0, 0x0, 5, 0x0, 1, 0, 10, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, &gCardNameKingdomKeyByLanguage, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#endif
        0, 0x0, 6, 0x0, 1, 0, 10, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, &gCardNameKingdomKeyByLanguage, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#endif
        0, 0x0, 7, 0x0, 1, 0, 10, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, &gCardNameKingdomKeyByLanguage, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#endif
        0, 0x0, 8, 0x0, 1, 0, 10, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, gCardNameKingdomKey, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep01Frame0, gCardWep01Tiles, gCardWep01Palette, &gCardNameKingdomKeyByLanguage, gKingdomKeySmallCardFrame0, gKingdomKeySmallCardTiles, gKingdomKeySmallCardPalette,
#endif
        0, 0x0, 9, 0x0, 1, 0, 10, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, &gCardNameThreeWishesByLanguage, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#endif
        1, 0x0, 0, 0x3, 11, 0, 15, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, &gCardNameThreeWishesByLanguage, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#endif
        1, 0x0, 1, 0x3, 11, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, &gCardNameThreeWishesByLanguage, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#endif
        1, 0x0, 2, 0x3, 11, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, &gCardNameThreeWishesByLanguage, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#endif
        1, 0x0, 3, 0x3, 11, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, &gCardNameThreeWishesByLanguage, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#endif
        1, 0x0, 4, 0x3, 11, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, &gCardNameThreeWishesByLanguage, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#endif
        1, 0x0, 5, 0x3, 11, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, &gCardNameThreeWishesByLanguage, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#endif
        1, 0x0, 6, 0x3, 11, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, &gCardNameThreeWishesByLanguage, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#endif
        1, 0x0, 7, 0x3, 11, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, &gCardNameThreeWishesByLanguage, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#endif
        1, 0x0, 8, 0x3, 11, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, gCardNameThreeWishes, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep04Frame0, gCardWep04Tiles, gCardWep04Palette, &gCardNameThreeWishesByLanguage, gThreeWishesSmallCardFrame0, gThreeWishesSmallCardTiles, gThreeWishesSmallCardPalette,
#endif
        1, 0x0, 9, 0x3, 11, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, &gCardNameCrabclawByLanguage, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#endif
        2, 0x0, 0, 0x4, 21, 0, 20, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, &gCardNameCrabclawByLanguage, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#endif
        2, 0x0, 1, 0x4, 21, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, &gCardNameCrabclawByLanguage, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#endif
        2, 0x0, 2, 0x4, 21, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, &gCardNameCrabclawByLanguage, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#endif
        2, 0x0, 3, 0x4, 21, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, &gCardNameCrabclawByLanguage, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#endif
        2, 0x0, 4, 0x4, 21, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, &gCardNameCrabclawByLanguage, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#endif
        2, 0x0, 5, 0x4, 21, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, &gCardNameCrabclawByLanguage, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#endif
        2, 0x0, 6, 0x4, 21, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, &gCardNameCrabclawByLanguage, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#endif
        2, 0x0, 7, 0x4, 21, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, &gCardNameCrabclawByLanguage, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#endif
        2, 0x0, 8, 0x4, 21, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, gCardNameCrabclaw, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep05Frame0, gCardWep05Tiles, gCardWep05Palette, &gCardNameCrabclawByLanguage, gCrabclawSmallCardFrame0, gCrabclawSmallCardTiles, gCrabclawSmallCardPalette,
#endif
        2, 0x0, 9, 0x4, 21, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, &gCardNamePumpkinheadByLanguage, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#endif
        3, 0x0, 0, 0x5, 31, 0, 15, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, &gCardNamePumpkinheadByLanguage, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#endif
        3, 0x0, 1, 0x5, 31, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, &gCardNamePumpkinheadByLanguage, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#endif
        3, 0x0, 2, 0x5, 31, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, &gCardNamePumpkinheadByLanguage, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#endif
        3, 0x0, 3, 0x5, 31, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, &gCardNamePumpkinheadByLanguage, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#endif
        3, 0x0, 4, 0x5, 31, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, &gCardNamePumpkinheadByLanguage, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#endif
        3, 0x0, 5, 0x5, 31, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, &gCardNamePumpkinheadByLanguage, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#endif
        3, 0x0, 6, 0x5, 31, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, &gCardNamePumpkinheadByLanguage, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#endif
        3, 0x0, 7, 0x5, 31, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, &gCardNamePumpkinheadByLanguage, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#endif
        3, 0x0, 8, 0x5, 31, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, gCardNamePumpkinhead, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep06Frame0, gCardWep06Tiles, gCardWep06Palette, &gCardNamePumpkinheadByLanguage, gPumpkinheadSmallCardFrame0, gPumpkinheadSmallCardTiles, gPumpkinheadSmallCardPalette,
#endif
        3, 0x0, 9, 0x5, 31, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, &gCardNameFairyHarpByLanguage, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#endif
        4, 0x0, 0, 0x6, 41, 0, 20, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, &gCardNameFairyHarpByLanguage, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#endif
        4, 0x0, 1, 0x6, 41, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, &gCardNameFairyHarpByLanguage, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#endif
        4, 0x0, 2, 0x6, 41, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, &gCardNameFairyHarpByLanguage, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#endif
        4, 0x0, 3, 0x6, 41, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, &gCardNameFairyHarpByLanguage, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#endif
        4, 0x0, 4, 0x6, 41, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, &gCardNameFairyHarpByLanguage, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#endif
        4, 0x0, 5, 0x6, 41, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, &gCardNameFairyHarpByLanguage, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#endif
        4, 0x0, 6, 0x6, 41, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, &gCardNameFairyHarpByLanguage, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#endif
        4, 0x0, 7, 0x6, 41, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, &gCardNameFairyHarpByLanguage, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#endif
        4, 0x0, 8, 0x6, 41, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, gCardNameFairyHarp, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep07Frame0, gCardWep07Tiles, gCardWep07Palette, &gCardNameFairyHarpByLanguage, gFairyHarpSmallCardFrame0, gFairyHarpSmallCardTiles, gFairyHarpSmallCardPalette,
#endif
        4, 0x0, 9, 0x6, 41, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, &gCardNameWishingStarByLanguage, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#endif
        5, 0x0, 0, 0x7, 51, 0, 15, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, &gCardNameWishingStarByLanguage, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#endif
        5, 0x0, 1, 0x7, 51, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, &gCardNameWishingStarByLanguage, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#endif
        5, 0x0, 2, 0x7, 51, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, &gCardNameWishingStarByLanguage, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#endif
        5, 0x0, 3, 0x7, 51, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, &gCardNameWishingStarByLanguage, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#endif
        5, 0x0, 4, 0x7, 51, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, &gCardNameWishingStarByLanguage, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#endif
        5, 0x0, 5, 0x7, 51, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, &gCardNameWishingStarByLanguage, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#endif
        5, 0x0, 6, 0x7, 51, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, &gCardNameWishingStarByLanguage, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#endif
        5, 0x0, 7, 0x7, 51, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, &gCardNameWishingStarByLanguage, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#endif
        5, 0x0, 8, 0x7, 51, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, gCardNameWishingStar, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep08Frame0, gCardWep08Tiles, gCardWep08Palette, &gCardNameWishingStarByLanguage, gWishingStarSmallCardFrame0, gWishingStarSmallCardTiles, gWishingStarSmallCardPalette,
#endif
        5, 0x0, 9, 0x7, 51, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, &gCardNameSpellbinderByLanguage, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#endif
        6, 0x0, 0, 0x8, 61, 0, 20, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, &gCardNameSpellbinderByLanguage, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#endif
        6, 0x0, 1, 0x8, 61, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, &gCardNameSpellbinderByLanguage, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#endif
        6, 0x0, 2, 0x8, 61, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, &gCardNameSpellbinderByLanguage, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#endif
        6, 0x0, 3, 0x8, 61, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, &gCardNameSpellbinderByLanguage, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#endif
        6, 0x0, 4, 0x8, 61, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, &gCardNameSpellbinderByLanguage, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#endif
        6, 0x0, 5, 0x8, 61, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, &gCardNameSpellbinderByLanguage, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#endif
        6, 0x0, 6, 0x8, 61, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, &gCardNameSpellbinderByLanguage, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#endif
        6, 0x0, 7, 0x8, 61, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, &gCardNameSpellbinderByLanguage, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#endif
        6, 0x0, 8, 0x8, 61, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, gCardNameSpellbinder, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep09Frame0, gCardWep09Tiles, gCardWep09Palette, &gCardNameSpellbinderByLanguage, gSpellbinderSmallCardFrame0, gSpellbinderSmallCardTiles, gSpellbinderSmallCardPalette,
#endif
        6, 0x0, 9, 0x8, 61, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, &gCardNameMetalChocoboByLanguage, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#endif
        7, 0x0, 0, 0x9, 71, 0, 20, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, &gCardNameMetalChocoboByLanguage, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#endif
        7, 0x0, 1, 0x9, 71, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, &gCardNameMetalChocoboByLanguage, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#endif
        7, 0x0, 2, 0x9, 71, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, &gCardNameMetalChocoboByLanguage, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#endif
        7, 0x0, 3, 0x9, 71, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, &gCardNameMetalChocoboByLanguage, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#endif
        7, 0x0, 4, 0x9, 71, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, &gCardNameMetalChocoboByLanguage, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#endif
        7, 0x0, 5, 0x9, 71, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, &gCardNameMetalChocoboByLanguage, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#endif
        7, 0x0, 6, 0x9, 71, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, &gCardNameMetalChocoboByLanguage, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#endif
        7, 0x0, 7, 0x9, 71, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, &gCardNameMetalChocoboByLanguage, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#endif
        7, 0x0, 8, 0x9, 71, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, gCardNameMetalChocobo, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep10Frame0, gCardWep10Tiles, gCardWep10Palette, &gCardNameMetalChocoboByLanguage, gMetalChocoboSmallCardFrame0, gMetalChocoboSmallCardTiles, gMetalChocoboSmallCardPalette,
#endif
        7, 0x0, 9, 0x9, 71, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, &gCardNameOlympiaByLanguage, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#endif
        8, 0x0, 0, 0x2, 81, 0, 15, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, &gCardNameOlympiaByLanguage, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#endif
        8, 0x0, 1, 0x2, 81, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, &gCardNameOlympiaByLanguage, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#endif
        8, 0x0, 2, 0x2, 81, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, &gCardNameOlympiaByLanguage, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#endif
        8, 0x0, 3, 0x2, 81, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, &gCardNameOlympiaByLanguage, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#endif
        8, 0x0, 4, 0x2, 81, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, &gCardNameOlympiaByLanguage, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#endif
        8, 0x0, 5, 0x2, 81, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, &gCardNameOlympiaByLanguage, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#endif
        8, 0x0, 6, 0x2, 81, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, &gCardNameOlympiaByLanguage, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#endif
        8, 0x0, 7, 0x2, 81, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, &gCardNameOlympiaByLanguage, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#endif
        8, 0x0, 8, 0x2, 81, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, gCardNameOlympia, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep03Frame0, gCardWep03Tiles, gCardWep03Palette, &gCardNameOlympiaByLanguage, gOlympiaSmallCardFrame0, gOlympiaSmallCardTiles, gOlympiaSmallCardPalette,
#endif
        8, 0x0, 9, 0x2, 81, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, &gCardNameLionheartByLanguage, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#endif
        9, 0x0, 0, 0xa, 91, 0, 20, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, &gCardNameLionheartByLanguage, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#endif
        9, 0x0, 1, 0xa, 91, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, &gCardNameLionheartByLanguage, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#endif
        9, 0x0, 2, 0xa, 91, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, &gCardNameLionheartByLanguage, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#endif
        9, 0x0, 3, 0xa, 91, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, &gCardNameLionheartByLanguage, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#endif
        9, 0x0, 4, 0xa, 91, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, &gCardNameLionheartByLanguage, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#endif
        9, 0x0, 5, 0xa, 91, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, &gCardNameLionheartByLanguage, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#endif
        9, 0x0, 6, 0xa, 91, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, &gCardNameLionheartByLanguage, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#endif
        9, 0x0, 7, 0xa, 91, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, &gCardNameLionheartByLanguage, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#endif
        9, 0x0, 8, 0xa, 91, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, gCardNameLionheart, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep11Frame0, gCardWep11Tiles, gCardWep11Palette, &gCardNameLionheartByLanguage, gLionheartSmallCardFrame0, gLionheartSmallCardTiles, gLionheartSmallCardPalette,
#endif
        9, 0x0, 9, 0xa, 91, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, &gCardNameLadyLuckByLanguage, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#endif
        10, 0x0, 0, 0xb, 101, 0, 15, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, &gCardNameLadyLuckByLanguage, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#endif
        10, 0x0, 1, 0xb, 101, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, &gCardNameLadyLuckByLanguage, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#endif
        10, 0x0, 2, 0xb, 101, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, &gCardNameLadyLuckByLanguage, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#endif
        10, 0x0, 3, 0xb, 101, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, &gCardNameLadyLuckByLanguage, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#endif
        10, 0x0, 4, 0xb, 101, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, &gCardNameLadyLuckByLanguage, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#endif
        10, 0x0, 5, 0xb, 101, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, &gCardNameLadyLuckByLanguage, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#endif
        10, 0x0, 6, 0xb, 101, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, &gCardNameLadyLuckByLanguage, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#endif
        10, 0x0, 7, 0xb, 101, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, &gCardNameLadyLuckByLanguage, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#endif
        10, 0x0, 8, 0xb, 101, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, gCardNameLadyLuck, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep12Frame0, gCardWep12Tiles, gCardWep12Palette, &gCardNameLadyLuckByLanguage, gLadyLuckSmallCardFrame0, gLadyLuckSmallCardTiles, gLadyLuckSmallCardPalette,
#endif
        10, 0x0, 9, 0xb, 101, 0, 15, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, &gCardNameDivineRoseByLanguage, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#endif
        11, 0x0, 0, 0xc, 111, 0, 20, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, &gCardNameDivineRoseByLanguage, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#endif
        11, 0x0, 1, 0xc, 111, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, &gCardNameDivineRoseByLanguage, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#endif
        11, 0x0, 2, 0xc, 111, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, &gCardNameDivineRoseByLanguage, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#endif
        11, 0x0, 3, 0xc, 111, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, &gCardNameDivineRoseByLanguage, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#endif
        11, 0x0, 4, 0xc, 111, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, &gCardNameDivineRoseByLanguage, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#endif
        11, 0x0, 5, 0xc, 111, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, &gCardNameDivineRoseByLanguage, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#endif
        11, 0x0, 6, 0xc, 111, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, &gCardNameDivineRoseByLanguage, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#endif
        11, 0x0, 7, 0xc, 111, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, &gCardNameDivineRoseByLanguage, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#endif
        11, 0x0, 8, 0xc, 111, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, gCardNameDivineRose, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep13Frame0, gCardWep13Tiles, gCardWep13Palette, &gCardNameDivineRoseByLanguage, gDivineRoseSmallCardFrame0, gDivineRoseSmallCardTiles, gDivineRoseSmallCardPalette,
#endif
        11, 0x0, 9, 0xc, 111, 0, 20, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, &gCardNameOathkeeperByLanguage, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#endif
        12, 0x0, 0, 0xd, 121, 0, 25, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, &gCardNameOathkeeperByLanguage, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#endif
        12, 0x0, 1, 0xd, 121, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, &gCardNameOathkeeperByLanguage, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#endif
        12, 0x0, 2, 0xd, 121, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, &gCardNameOathkeeperByLanguage, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#endif
        12, 0x0, 3, 0xd, 121, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, &gCardNameOathkeeperByLanguage, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#endif
        12, 0x0, 4, 0xd, 121, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, &gCardNameOathkeeperByLanguage, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#endif
        12, 0x0, 5, 0xd, 121, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, &gCardNameOathkeeperByLanguage, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#endif
        12, 0x0, 6, 0xd, 121, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, &gCardNameOathkeeperByLanguage, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#endif
        12, 0x0, 7, 0xd, 121, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, &gCardNameOathkeeperByLanguage, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#endif
        12, 0x0, 8, 0xd, 121, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, gCardNameOathkeeper, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep14Frame0, gCardWep14Tiles, gCardWep14Palette, &gCardNameOathkeeperByLanguage, gOathkeeperSmallCardFrame0, gOathkeeperSmallCardTiles, gOathkeeperSmallCardPalette,
#endif
        12, 0x0, 9, 0xd, 121, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, &gCardNameOblivionByLanguage, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#endif
        13, 0x0, 0, 0xe, 131, 0, 25, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, &gCardNameOblivionByLanguage, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#endif
        13, 0x0, 1, 0xe, 131, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, &gCardNameOblivionByLanguage, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#endif
        13, 0x0, 2, 0xe, 131, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, &gCardNameOblivionByLanguage, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#endif
        13, 0x0, 3, 0xe, 131, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, &gCardNameOblivionByLanguage, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#endif
        13, 0x0, 4, 0xe, 131, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, &gCardNameOblivionByLanguage, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#endif
        13, 0x0, 5, 0xe, 131, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, &gCardNameOblivionByLanguage, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#endif
        13, 0x0, 6, 0xe, 131, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, &gCardNameOblivionByLanguage, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#endif
        13, 0x0, 7, 0xe, 131, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, &gCardNameOblivionByLanguage, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#endif
        13, 0x0, 8, 0xe, 131, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, gCardNameOblivion, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep15Frame0, gCardWep15Tiles, gCardWep15Palette, &gCardNameOblivionByLanguage, gOblivionSmallCardFrame0, gOblivionSmallCardTiles, gOblivionSmallCardPalette,
#endif
        13, 0x0, 9, 0xe, 131, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, &gCardNameDiamondDustByLanguage, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#endif
        14, 0x0, 0, 0x10, 141, 0, 25, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, &gCardNameDiamondDustByLanguage, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#endif
        14, 0x0, 1, 0x10, 141, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, &gCardNameDiamondDustByLanguage, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#endif
        14, 0x0, 2, 0x10, 141, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, &gCardNameDiamondDustByLanguage, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#endif
        14, 0x0, 3, 0x10, 141, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, &gCardNameDiamondDustByLanguage, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#endif
        14, 0x0, 4, 0x10, 141, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, &gCardNameDiamondDustByLanguage, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#endif
        14, 0x0, 5, 0x10, 141, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, &gCardNameDiamondDustByLanguage, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#endif
        14, 0x0, 6, 0x10, 141, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, &gCardNameDiamondDustByLanguage, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#endif
        14, 0x0, 7, 0x10, 141, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, &gCardNameDiamondDustByLanguage, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#endif
        14, 0x0, 8, 0x10, 141, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, gCardNameDiamondDust, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep18Frame0, gCardWep18Tiles, gCardWep18Palette, &gCardNameDiamondDustByLanguage, gDiamondDustSmallCardFrame0, gDiamondDustSmallCardTiles, gDiamondDustSmallCardPalette,
#endif
        14, 0x0, 9, 0x10, 141, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, &gCardNameOneWingedAngelByLanguage, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#endif
        15, 0x0, 0, 0x11, 151, 0, 25, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, &gCardNameOneWingedAngelByLanguage, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#endif
        15, 0x0, 1, 0x11, 151, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, &gCardNameOneWingedAngelByLanguage, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#endif
        15, 0x0, 2, 0x11, 151, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, &gCardNameOneWingedAngelByLanguage, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#endif
        15, 0x0, 3, 0x11, 151, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, &gCardNameOneWingedAngelByLanguage, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#endif
        15, 0x0, 4, 0x11, 151, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, &gCardNameOneWingedAngelByLanguage, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#endif
        15, 0x0, 5, 0x11, 151, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, &gCardNameOneWingedAngelByLanguage, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#endif
        15, 0x0, 6, 0x11, 151, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, &gCardNameOneWingedAngelByLanguage, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#endif
        15, 0x0, 7, 0x11, 151, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, &gCardNameOneWingedAngelByLanguage, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#endif
        15, 0x0, 8, 0x11, 151, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, gCardNameOneWingedAngel, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep19Frame0, gCardWep19Tiles, gCardWep19Palette, &gCardNameOneWingedAngelByLanguage, gOneWingedAngelSmallCardFrame0, gOneWingedAngelSmallCardTiles, gOneWingedAngelSmallCardPalette,
#endif
        15, 0x0, 9, 0x11, 151, 0, 25, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, &gCardNameUltimaWeaponByLanguage, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#endif
        16, 0x0, 0, 0xf, 161, 0, 30, {10, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, &gCardNameUltimaWeaponByLanguage, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#endif
        16, 0x0, 1, 0xf, 161, 0, 30, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, &gCardNameUltimaWeaponByLanguage, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#endif
        16, 0x0, 2, 0xf, 161, 0, 30, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, &gCardNameUltimaWeaponByLanguage, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#endif
        16, 0x0, 3, 0xf, 161, 0, 30, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, &gCardNameUltimaWeaponByLanguage, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#endif
        16, 0x0, 4, 0xf, 161, 0, 30, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, &gCardNameUltimaWeaponByLanguage, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#endif
        16, 0x0, 5, 0xf, 161, 0, 30, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, &gCardNameUltimaWeaponByLanguage, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#endif
        16, 0x0, 6, 0xf, 161, 0, 30, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, &gCardNameUltimaWeaponByLanguage, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#endif
        16, 0x0, 7, 0xf, 161, 0, 30, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, &gCardNameUltimaWeaponByLanguage, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#endif
        16, 0x0, 8, 0xf, 161, 0, 30, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, gCardNameUltimaWeapon, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep16Frame0, gCardWep16Tiles, gCardWep16Palette, &gCardNameUltimaWeaponByLanguage, gUltimaWeaponSmallCardFrame0, gUltimaWeaponSmallCardTiles, gUltimaWeaponSmallCardPalette,
#endif
        16, 0x0, 9, 0xf, 161, 0, 30, {2, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, &gCardNameFireByLanguage, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#endif
        18, 0x0, 0, 0x13, 171, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, &gCardNameFireByLanguage, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#endif
        18, 0x0, 1, 0x13, 171, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, &gCardNameFireByLanguage, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#endif
        18, 0x0, 2, 0x13, 171, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, &gCardNameFireByLanguage, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#endif
        18, 0x0, 3, 0x13, 171, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, &gCardNameFireByLanguage, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#endif
        18, 0x0, 4, 0x13, 171, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, &gCardNameFireByLanguage, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#endif
        18, 0x0, 5, 0x13, 171, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, &gCardNameFireByLanguage, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#endif
        18, 0x0, 6, 0x13, 171, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, &gCardNameFireByLanguage, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#endif
        18, 0x0, 7, 0x13, 171, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, &gCardNameFireByLanguage, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#endif
        18, 0x0, 8, 0x13, 171, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, gCardNameFire, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc01Frame0, gCardMgc01Tiles, gCardMgc01Palette, &gCardNameFireByLanguage, gFireSmallCardFrame0, gFireSmallCardTiles, gFireSmallCardPalette,
#endif
        18, 0x0, 9, 0x13, 171, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, &gCardNameBlizzardByLanguage, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#endif
        19, 0x0, 0, 0x14, 181, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, &gCardNameBlizzardByLanguage, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#endif
        19, 0x0, 1, 0x14, 181, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, &gCardNameBlizzardByLanguage, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#endif
        19, 0x0, 2, 0x14, 181, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, &gCardNameBlizzardByLanguage, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#endif
        19, 0x0, 3, 0x14, 181, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, &gCardNameBlizzardByLanguage, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#endif
        19, 0x0, 4, 0x14, 181, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, &gCardNameBlizzardByLanguage, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#endif
        19, 0x0, 5, 0x14, 181, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, &gCardNameBlizzardByLanguage, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#endif
        19, 0x0, 6, 0x14, 181, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, &gCardNameBlizzardByLanguage, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#endif
        19, 0x0, 7, 0x14, 181, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, &gCardNameBlizzardByLanguage, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#endif
        19, 0x0, 8, 0x14, 181, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, gCardNameBlizzard, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc02Frame0, gCardMgc02Tiles, gCardMgc02Palette, &gCardNameBlizzardByLanguage, gBlizzardSmallCardFrame0, gBlizzardSmallCardTiles, gBlizzardSmallCardPalette,
#endif
        19, 0x0, 9, 0x14, 181, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, &gCardNameThunderByLanguage, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#endif
        20, 0x0, 0, 0x15, 191, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, &gCardNameThunderByLanguage, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#endif
        20, 0x0, 1, 0x15, 191, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, &gCardNameThunderByLanguage, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#endif
        20, 0x0, 2, 0x15, 191, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, &gCardNameThunderByLanguage, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#endif
        20, 0x0, 3, 0x15, 191, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, &gCardNameThunderByLanguage, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#endif
        20, 0x0, 4, 0x15, 191, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, &gCardNameThunderByLanguage, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#endif
        20, 0x0, 5, 0x15, 191, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, &gCardNameThunderByLanguage, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#endif
        20, 0x0, 6, 0x15, 191, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, &gCardNameThunderByLanguage, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#endif
        20, 0x0, 7, 0x15, 191, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, &gCardNameThunderByLanguage, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#endif
        20, 0x0, 8, 0x15, 191, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, gCardNameThunder, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc03Frame0, gCardMgc03Tiles, gCardMgc03Palette, &gCardNameThunderByLanguage, gThunderSmallCardFrame0, gThunderSmallCardTiles, gThunderSmallCardPalette,
#endif
        20, 0x0, 9, 0x15, 191, 1, 15, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, &gCardNameCureByLanguage, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#endif
        21, 0x0, 0, 0x16, 201, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, &gCardNameCureByLanguage, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#endif
        21, 0x0, 1, 0x16, 201, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, &gCardNameCureByLanguage, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#endif
        21, 0x0, 2, 0x16, 201, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, &gCardNameCureByLanguage, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#endif
        21, 0x0, 3, 0x16, 201, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, &gCardNameCureByLanguage, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#endif
        21, 0x0, 4, 0x16, 201, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, &gCardNameCureByLanguage, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#endif
        21, 0x0, 5, 0x16, 201, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, &gCardNameCureByLanguage, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#endif
        21, 0x0, 6, 0x16, 201, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, &gCardNameCureByLanguage, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#endif
        21, 0x0, 7, 0x16, 201, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, &gCardNameCureByLanguage, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#endif
        21, 0x0, 8, 0x16, 201, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, gCardNameCure, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc04Frame0, gCardMgc04Tiles, gCardMgc04Palette, &gCardNameCureByLanguage, gCureSmallCardFrame0, gCureSmallCardTiles, gCureSmallCardPalette,
#endif
        21, 0x0, 9, 0x16, 201, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, &gCardNameGravityByLanguage, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#endif
        22, 0x0, 0, 0x17, 211, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, &gCardNameGravityByLanguage, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#endif
        22, 0x0, 1, 0x17, 211, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, &gCardNameGravityByLanguage, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#endif
        22, 0x0, 2, 0x17, 211, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, &gCardNameGravityByLanguage, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#endif
        22, 0x0, 3, 0x17, 211, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, &gCardNameGravityByLanguage, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#endif
        22, 0x0, 4, 0x17, 211, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, &gCardNameGravityByLanguage, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#endif
        22, 0x0, 5, 0x17, 211, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, &gCardNameGravityByLanguage, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#endif
        22, 0x0, 6, 0x17, 211, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, &gCardNameGravityByLanguage, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#endif
        22, 0x0, 7, 0x17, 211, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, &gCardNameGravityByLanguage, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#endif
        22, 0x0, 8, 0x17, 211, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, gCardNameGravity, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc05Frame0, gCardMgc05Tiles, gCardMgc05Palette, &gCardNameGravityByLanguage, gGravitySmallCardFrame0, gGravitySmallCardTiles, gGravitySmallCardPalette,
#endif
        22, 0x0, 9, 0x17, 211, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, &gCardNameStopByLanguage, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#endif
        23, 0x0, 0, 0x18, 221, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, &gCardNameStopByLanguage, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#endif
        23, 0x0, 1, 0x18, 221, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, &gCardNameStopByLanguage, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#endif
        23, 0x0, 2, 0x18, 221, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, &gCardNameStopByLanguage, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#endif
        23, 0x0, 3, 0x18, 221, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, &gCardNameStopByLanguage, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#endif
        23, 0x0, 4, 0x18, 221, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, &gCardNameStopByLanguage, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#endif
        23, 0x0, 5, 0x18, 221, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, &gCardNameStopByLanguage, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#endif
        23, 0x0, 6, 0x18, 221, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, &gCardNameStopByLanguage, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#endif
        23, 0x0, 7, 0x18, 221, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, &gCardNameStopByLanguage, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#endif
        23, 0x0, 8, 0x18, 221, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, gCardNameStop, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc06Frame0, gCardMgc06Tiles, gCardMgc06Palette, &gCardNameStopByLanguage, gStopSmallCardFrame0, gStopSmallCardTiles, gStopSmallCardPalette,
#endif
        23, 0x0, 9, 0x18, 221, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, &gCardNameAeroByLanguage, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#endif
        24, 0x0, 0, 0x19, 231, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, &gCardNameAeroByLanguage, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#endif
        24, 0x0, 1, 0x19, 231, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, &gCardNameAeroByLanguage, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#endif
        24, 0x0, 2, 0x19, 231, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, &gCardNameAeroByLanguage, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#endif
        24, 0x0, 3, 0x19, 231, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, &gCardNameAeroByLanguage, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#endif
        24, 0x0, 4, 0x19, 231, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, &gCardNameAeroByLanguage, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#endif
        24, 0x0, 5, 0x19, 231, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, &gCardNameAeroByLanguage, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#endif
        24, 0x0, 6, 0x19, 231, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, &gCardNameAeroByLanguage, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#endif
        24, 0x0, 7, 0x19, 231, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, &gCardNameAeroByLanguage, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#endif
        24, 0x0, 8, 0x19, 231, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_JP)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, gCardNameAero, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#elif defined(VERSION_EU)
        gCardMgc07Frame0, gCardMgc07Tiles, gCardMgc07Palette, &gCardNameAeroByLanguage, gAeroSmallCardFrame0, gAeroSmallCardTiles, gAeroSmallCardPalette,
#endif
        24, 0x0, 9, 0x19, 231, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, &gCardNameDonaldDuckByLanguage, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#endif
        39, CARD_DEF_FLAG_FRIEND, 0, 0x1c, 241, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, &gCardNameDonaldDuckByLanguage, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#endif
        39, CARD_DEF_FLAG_FRIEND, 1, 0x1c, 241, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, &gCardNameDonaldDuckByLanguage, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#endif
        39, CARD_DEF_FLAG_FRIEND, 2, 0x1c, 241, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, &gCardNameDonaldDuckByLanguage, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#endif
        39, CARD_DEF_FLAG_FRIEND, 3, 0x1c, 241, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, &gCardNameDonaldDuckByLanguage, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#endif
        39, CARD_DEF_FLAG_FRIEND, 4, 0x1c, 241, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, &gCardNameDonaldDuckByLanguage, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#endif
        39, CARD_DEF_FLAG_FRIEND, 5, 0x1c, 241, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, &gCardNameDonaldDuckByLanguage, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#endif
        39, CARD_DEF_FLAG_FRIEND, 6, 0x1c, 241, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, &gCardNameDonaldDuckByLanguage, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#endif
        39, CARD_DEF_FLAG_FRIEND, 7, 0x1c, 241, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, &gCardNameDonaldDuckByLanguage, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#endif
        39, CARD_DEF_FLAG_FRIEND, 8, 0x1c, 241, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, gCardNameDonaldDuck, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn02Frame0, gCardSmn02Tiles, gDonaldPalette, &gCardNameDonaldDuckByLanguage, gDonaldDuckSmallCardFrame0, gDonaldDuckSmallCardTiles, gDonaldDuckSmallCardPalette,
#endif
        39, CARD_DEF_FLAG_FRIEND, 9, 0x1c, 241, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, &gCardNameGoofyByLanguage, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#endif
        40, CARD_DEF_FLAG_FRIEND, 0, 0x1b, 251, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, &gCardNameGoofyByLanguage, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#endif
        40, CARD_DEF_FLAG_FRIEND, 1, 0x1b, 251, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, &gCardNameGoofyByLanguage, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#endif
        40, CARD_DEF_FLAG_FRIEND, 2, 0x1b, 251, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, &gCardNameGoofyByLanguage, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#endif
        40, CARD_DEF_FLAG_FRIEND, 3, 0x1b, 251, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, &gCardNameGoofyByLanguage, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#endif
        40, CARD_DEF_FLAG_FRIEND, 4, 0x1b, 251, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, &gCardNameGoofyByLanguage, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#endif
        40, CARD_DEF_FLAG_FRIEND, 5, 0x1b, 251, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, &gCardNameGoofyByLanguage, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#endif
        40, CARD_DEF_FLAG_FRIEND, 6, 0x1b, 251, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, &gCardNameGoofyByLanguage, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#endif
        40, CARD_DEF_FLAG_FRIEND, 7, 0x1b, 251, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, &gCardNameGoofyByLanguage, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#endif
        40, CARD_DEF_FLAG_FRIEND, 8, 0x1b, 251, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, gCardNameGoofy, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn01Frame0, gCardSmn01Tiles, gGoofyPalette, &gCardNameGoofyByLanguage, gGoofySmallCardFrame0, gGoofySmallCardTiles, gGoofySmallCardPalette,
#endif
        40, CARD_DEF_FLAG_FRIEND, 9, 0x1b, 251, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, &gCardNameSimbaByLanguage, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#endif
        25, CARD_DEF_FLAG_SUMMON, 0, 0x1d, 261, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, &gCardNameSimbaByLanguage, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#endif
        25, CARD_DEF_FLAG_SUMMON, 1, 0x1d, 261, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, &gCardNameSimbaByLanguage, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#endif
        25, CARD_DEF_FLAG_SUMMON, 2, 0x1d, 261, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, &gCardNameSimbaByLanguage, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#endif
        25, CARD_DEF_FLAG_SUMMON, 3, 0x1d, 261, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, &gCardNameSimbaByLanguage, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#endif
        25, CARD_DEF_FLAG_SUMMON, 4, 0x1d, 261, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, &gCardNameSimbaByLanguage, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#endif
        25, CARD_DEF_FLAG_SUMMON, 5, 0x1d, 261, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, &gCardNameSimbaByLanguage, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#endif
        25, CARD_DEF_FLAG_SUMMON, 6, 0x1d, 261, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, &gCardNameSimbaByLanguage, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#endif
        25, CARD_DEF_FLAG_SUMMON, 7, 0x1d, 261, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, &gCardNameSimbaByLanguage, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#endif
        25, CARD_DEF_FLAG_SUMMON, 8, 0x1d, 261, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, gCardNameSimba, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn03Frame0, gCardSmn03Tiles, gCardSmn03Palette, &gCardNameSimbaByLanguage, gSimbaSmallCardFrame0, gSimbaSmallCardTiles, gSimbaSmallCardPalette,
#endif
        25, CARD_DEF_FLAG_SUMMON, 9, 0x1d, 261, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, &gCardNameGenieByLanguage, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#endif
        26, CARD_DEF_FLAG_SUMMON, 0, 0x1e, 271, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, &gCardNameGenieByLanguage, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#endif
        26, CARD_DEF_FLAG_SUMMON, 1, 0x1e, 271, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, &gCardNameGenieByLanguage, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#endif
        26, CARD_DEF_FLAG_SUMMON, 2, 0x1e, 271, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, &gCardNameGenieByLanguage, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#endif
        26, CARD_DEF_FLAG_SUMMON, 3, 0x1e, 271, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, &gCardNameGenieByLanguage, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#endif
        26, CARD_DEF_FLAG_SUMMON, 4, 0x1e, 271, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, &gCardNameGenieByLanguage, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#endif
        26, CARD_DEF_FLAG_SUMMON, 5, 0x1e, 271, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, &gCardNameGenieByLanguage, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#endif
        26, CARD_DEF_FLAG_SUMMON, 6, 0x1e, 271, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, &gCardNameGenieByLanguage, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#endif
        26, CARD_DEF_FLAG_SUMMON, 7, 0x1e, 271, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, &gCardNameGenieByLanguage, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#endif
        26, CARD_DEF_FLAG_SUMMON, 8, 0x1e, 271, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, gCardNameGenie, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn04Frame0, gCardSmn04Tiles, gCardSmn04Palette, &gCardNameGenieByLanguage, gGenieSmallCardFrame0, gGenieSmallCardTiles, gGenieSmallCardPalette,
#endif
        26, CARD_DEF_FLAG_SUMMON, 9, 0x1e, 271, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, &gCardNameBambiByLanguage, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#endif
        27, CARD_DEF_FLAG_SUMMON, 0, 0x1f, 281, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, &gCardNameBambiByLanguage, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#endif
        27, CARD_DEF_FLAG_SUMMON, 1, 0x1f, 281, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, &gCardNameBambiByLanguage, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#endif
        27, CARD_DEF_FLAG_SUMMON, 2, 0x1f, 281, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, &gCardNameBambiByLanguage, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#endif
        27, CARD_DEF_FLAG_SUMMON, 3, 0x1f, 281, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, &gCardNameBambiByLanguage, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#endif
        27, CARD_DEF_FLAG_SUMMON, 4, 0x1f, 281, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, &gCardNameBambiByLanguage, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#endif
        27, CARD_DEF_FLAG_SUMMON, 5, 0x1f, 281, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, &gCardNameBambiByLanguage, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#endif
        27, CARD_DEF_FLAG_SUMMON, 6, 0x1f, 281, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, &gCardNameBambiByLanguage, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#endif
        27, CARD_DEF_FLAG_SUMMON, 7, 0x1f, 281, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, &gCardNameBambiByLanguage, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#endif
        27, CARD_DEF_FLAG_SUMMON, 8, 0x1f, 281, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, gCardNameBambi, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn05Frame0, gCardSmn05Tiles, gBanbPalette, &gCardNameBambiByLanguage, gBambiSmallCardFrame0, gBambiSmallCardTiles, gBambiSmallCardPalette,
#endif
        27, CARD_DEF_FLAG_SUMMON, 9, 0x1f, 281, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, &gCardNameDumboByLanguage, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#endif
        28, CARD_DEF_FLAG_SUMMON, 0, 0x20, 291, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, &gCardNameDumboByLanguage, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#endif
        28, CARD_DEF_FLAG_SUMMON, 1, 0x20, 291, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, &gCardNameDumboByLanguage, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#endif
        28, CARD_DEF_FLAG_SUMMON, 2, 0x20, 291, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, &gCardNameDumboByLanguage, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#endif
        28, CARD_DEF_FLAG_SUMMON, 3, 0x20, 291, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, &gCardNameDumboByLanguage, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#endif
        28, CARD_DEF_FLAG_SUMMON, 4, 0x20, 291, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, &gCardNameDumboByLanguage, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#endif
        28, CARD_DEF_FLAG_SUMMON, 5, 0x20, 291, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, &gCardNameDumboByLanguage, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#endif
        28, CARD_DEF_FLAG_SUMMON, 6, 0x20, 291, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, &gCardNameDumboByLanguage, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#endif
        28, CARD_DEF_FLAG_SUMMON, 7, 0x20, 291, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, &gCardNameDumboByLanguage, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#endif
        28, CARD_DEF_FLAG_SUMMON, 8, 0x20, 291, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, gCardNameDumbo, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn06Frame0, gCardSmn06Tiles, gCardSmn06Palette, &gCardNameDumboByLanguage, gDumboSmallCardFrame0, gDumboSmallCardTiles, gDumboSmallCardPalette,
#endif
        28, CARD_DEF_FLAG_SUMMON, 9, 0x20, 291, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, &gCardNameTinkerBellByLanguage, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#endif
        29, CARD_DEF_FLAG_SUMMON, 0, 0x21, 301, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, &gCardNameTinkerBellByLanguage, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#endif
        29, CARD_DEF_FLAG_SUMMON, 1, 0x21, 301, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, &gCardNameTinkerBellByLanguage, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#endif
        29, CARD_DEF_FLAG_SUMMON, 2, 0x21, 301, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, &gCardNameTinkerBellByLanguage, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#endif
        29, CARD_DEF_FLAG_SUMMON, 3, 0x21, 301, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, &gCardNameTinkerBellByLanguage, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#endif
        29, CARD_DEF_FLAG_SUMMON, 4, 0x21, 301, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, &gCardNameTinkerBellByLanguage, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#endif
        29, CARD_DEF_FLAG_SUMMON, 5, 0x21, 301, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, &gCardNameTinkerBellByLanguage, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#endif
        29, CARD_DEF_FLAG_SUMMON, 6, 0x21, 301, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, &gCardNameTinkerBellByLanguage, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#endif
        29, CARD_DEF_FLAG_SUMMON, 7, 0x21, 301, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, &gCardNameTinkerBellByLanguage, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#endif
        29, CARD_DEF_FLAG_SUMMON, 8, 0x21, 301, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, gCardNameTinkerBell, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn07Frame0, gCardSmn07Tiles, gTinkPalette, &gCardNameTinkerBellByLanguage, gTinkerBellSmallCardFrame0, gTinkerBellSmallCardTiles, gTinkerBellSmallCardPalette,
#endif
        29, CARD_DEF_FLAG_SUMMON, 9, 0x21, 301, 1, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, &gCardNameMushuByLanguage, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#endif
        30, CARD_DEF_FLAG_SUMMON, 0, 0x22, 311, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, &gCardNameMushuByLanguage, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#endif
        30, CARD_DEF_FLAG_SUMMON, 1, 0x22, 311, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, &gCardNameMushuByLanguage, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#endif
        30, CARD_DEF_FLAG_SUMMON, 2, 0x22, 311, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, &gCardNameMushuByLanguage, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#endif
        30, CARD_DEF_FLAG_SUMMON, 3, 0x22, 311, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, &gCardNameMushuByLanguage, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#endif
        30, CARD_DEF_FLAG_SUMMON, 4, 0x22, 311, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, &gCardNameMushuByLanguage, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#endif
        30, CARD_DEF_FLAG_SUMMON, 5, 0x22, 311, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, &gCardNameMushuByLanguage, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#endif
        30, CARD_DEF_FLAG_SUMMON, 6, 0x22, 311, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, &gCardNameMushuByLanguage, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#endif
        30, CARD_DEF_FLAG_SUMMON, 7, 0x22, 311, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, &gCardNameMushuByLanguage, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#endif
        30, CARD_DEF_FLAG_SUMMON, 8, 0x22, 311, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, gCardNameMushu, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn08Frame0, gCardSmn08Tiles, gMushuPalette, &gCardNameMushuByLanguage, gMushuSmallCardFrame0, gMushuSmallCardTiles, gMushuSmallCardPalette,
#endif
        30, CARD_DEF_FLAG_SUMMON, 9, 0x22, 311, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, &gCardNameCloudByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#endif
        31, CARD_DEF_FLAG_SUMMON, 0, 0x23, 321, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, &gCardNameCloudByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#endif
        31, CARD_DEF_FLAG_SUMMON, 1, 0x23, 321, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, &gCardNameCloudByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#endif
        31, CARD_DEF_FLAG_SUMMON, 2, 0x23, 321, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, &gCardNameCloudByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#endif
        31, CARD_DEF_FLAG_SUMMON, 3, 0x23, 321, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, &gCardNameCloudByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#endif
        31, CARD_DEF_FLAG_SUMMON, 4, 0x23, 321, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, &gCardNameCloudByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#endif
        31, CARD_DEF_FLAG_SUMMON, 5, 0x23, 321, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, &gCardNameCloudByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#endif
        31, CARD_DEF_FLAG_SUMMON, 6, 0x23, 321, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, &gCardNameCloudByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#endif
        31, CARD_DEF_FLAG_SUMMON, 7, 0x23, 321, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, &gCardNameCloudByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#endif
        31, CARD_DEF_FLAG_SUMMON, 8, 0x23, 321, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, gCardNameCloud, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09Palette, &gCardNameCloudByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudSmallCardPalette,
#endif
        31, CARD_DEF_FLAG_SUMMON, 9, 0x23, 321, 1, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, &gCardNameAladdinByLanguage, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#endif
        41, CARD_DEF_FLAG_FRIEND, 0, 0x28, 331, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, &gCardNameAladdinByLanguage, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#endif
        41, CARD_DEF_FLAG_FRIEND, 1, 0x28, 331, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, &gCardNameAladdinByLanguage, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#endif
        41, CARD_DEF_FLAG_FRIEND, 2, 0x28, 331, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, &gCardNameAladdinByLanguage, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#endif
        41, CARD_DEF_FLAG_FRIEND, 3, 0x28, 331, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, &gCardNameAladdinByLanguage, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#endif
        41, CARD_DEF_FLAG_FRIEND, 4, 0x28, 331, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, &gCardNameAladdinByLanguage, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#endif
        41, CARD_DEF_FLAG_FRIEND, 5, 0x28, 331, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, &gCardNameAladdinByLanguage, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#endif
        41, CARD_DEF_FLAG_FRIEND, 6, 0x28, 331, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, &gCardNameAladdinByLanguage, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#endif
        41, CARD_DEF_FLAG_FRIEND, 7, 0x28, 331, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, &gCardNameAladdinByLanguage, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#endif
        41, CARD_DEF_FLAG_FRIEND, 8, 0x28, 331, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, gCardNameAladdin, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn10Frame0, gCardSmn10Tiles, gAladdinPalette, &gCardNameAladdinByLanguage, gAladdinSmallCardFrame0, gAladdinSmallCardTiles, gAladdinSmallCardPalette,
#endif
        41, CARD_DEF_FLAG_FRIEND, 9, 0x28, 331, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, &gCardNameArielByLanguage, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#endif
        42, CARD_DEF_FLAG_FRIEND, 0, 0x29, 341, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, &gCardNameArielByLanguage, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#endif
        42, CARD_DEF_FLAG_FRIEND, 1, 0x29, 341, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, &gCardNameArielByLanguage, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#endif
        42, CARD_DEF_FLAG_FRIEND, 2, 0x29, 341, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, &gCardNameArielByLanguage, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#endif
        42, CARD_DEF_FLAG_FRIEND, 3, 0x29, 341, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, &gCardNameArielByLanguage, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#endif
        42, CARD_DEF_FLAG_FRIEND, 4, 0x29, 341, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, &gCardNameArielByLanguage, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#endif
        42, CARD_DEF_FLAG_FRIEND, 5, 0x29, 341, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, &gCardNameArielByLanguage, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#endif
        42, CARD_DEF_FLAG_FRIEND, 6, 0x29, 341, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, &gCardNameArielByLanguage, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#endif
        42, CARD_DEF_FLAG_FRIEND, 7, 0x29, 341, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, &gCardNameArielByLanguage, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#endif
        42, CARD_DEF_FLAG_FRIEND, 8, 0x29, 341, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, gCardNameAriel, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn11Frame0, gCardSmn11Tiles, gArielPalette, &gCardNameArielByLanguage, gArielSmallCardFrame0, gArielSmallCardTiles, gArielSmallCardPalette,
#endif
        42, CARD_DEF_FLAG_FRIEND, 9, 0x29, 341, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, &gCardNameJackByLanguage, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#endif
        43, CARD_DEF_FLAG_FRIEND, 0, 0x2a, 351, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, &gCardNameJackByLanguage, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#endif
        43, CARD_DEF_FLAG_FRIEND, 1, 0x2a, 351, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, &gCardNameJackByLanguage, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#endif
        43, CARD_DEF_FLAG_FRIEND, 2, 0x2a, 351, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, &gCardNameJackByLanguage, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#endif
        43, CARD_DEF_FLAG_FRIEND, 3, 0x2a, 351, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, &gCardNameJackByLanguage, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#endif
        43, CARD_DEF_FLAG_FRIEND, 4, 0x2a, 351, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, &gCardNameJackByLanguage, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#endif
        43, CARD_DEF_FLAG_FRIEND, 5, 0x2a, 351, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, &gCardNameJackByLanguage, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#endif
        43, CARD_DEF_FLAG_FRIEND, 6, 0x2a, 351, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, &gCardNameJackByLanguage, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#endif
        43, CARD_DEF_FLAG_FRIEND, 7, 0x2a, 351, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, &gCardNameJackByLanguage, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#endif
        43, CARD_DEF_FLAG_FRIEND, 8, 0x2a, 351, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, gCardNameJack, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn12Frame0, gCardSmn12Tiles, gJackPalette, &gCardNameJackByLanguage, gJackSmallCardFrame0, gJackSmallCardTiles, gJackSmallCardPalette,
#endif
        43, CARD_DEF_FLAG_FRIEND, 9, 0x2a, 351, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, &gCardNamePeterPanByLanguage, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#endif
        44, CARD_DEF_FLAG_FRIEND, 0, 0x2b, 361, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, &gCardNamePeterPanByLanguage, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#endif
        44, CARD_DEF_FLAG_FRIEND, 1, 0x2b, 361, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, &gCardNamePeterPanByLanguage, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#endif
        44, CARD_DEF_FLAG_FRIEND, 2, 0x2b, 361, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, &gCardNamePeterPanByLanguage, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#endif
        44, CARD_DEF_FLAG_FRIEND, 3, 0x2b, 361, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, &gCardNamePeterPanByLanguage, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#endif
        44, CARD_DEF_FLAG_FRIEND, 4, 0x2b, 361, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, &gCardNamePeterPanByLanguage, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#endif
        44, CARD_DEF_FLAG_FRIEND, 5, 0x2b, 361, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, &gCardNamePeterPanByLanguage, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#endif
        44, CARD_DEF_FLAG_FRIEND, 6, 0x2b, 361, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, &gCardNamePeterPanByLanguage, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#endif
        44, CARD_DEF_FLAG_FRIEND, 7, 0x2b, 361, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, &gCardNamePeterPanByLanguage, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#endif
        44, CARD_DEF_FLAG_FRIEND, 8, 0x2b, 361, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, gCardNamePeterPan, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn13Frame0, gCardSmn13Tiles, gPeterPalette, &gCardNamePeterPanByLanguage, gPeterPanSmallCardFrame0, gPeterPanSmallCardTiles, gPeterPanSmallCardPalette,
#endif
        44, CARD_DEF_FLAG_FRIEND, 9, 0x2b, 361, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, &gCardNameBeastByLanguage, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#endif
        45, CARD_DEF_FLAG_FRIEND, 0, 0x2c, 371, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, &gCardNameBeastByLanguage, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#endif
        45, CARD_DEF_FLAG_FRIEND, 1, 0x2c, 371, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, &gCardNameBeastByLanguage, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#endif
        45, CARD_DEF_FLAG_FRIEND, 2, 0x2c, 371, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, &gCardNameBeastByLanguage, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#endif
        45, CARD_DEF_FLAG_FRIEND, 3, 0x2c, 371, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, &gCardNameBeastByLanguage, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#endif
        45, CARD_DEF_FLAG_FRIEND, 4, 0x2c, 371, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, &gCardNameBeastByLanguage, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#endif
        45, CARD_DEF_FLAG_FRIEND, 5, 0x2c, 371, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, &gCardNameBeastByLanguage, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#endif
        45, CARD_DEF_FLAG_FRIEND, 6, 0x2c, 371, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, &gCardNameBeastByLanguage, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#endif
        45, CARD_DEF_FLAG_FRIEND, 7, 0x2c, 371, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, &gCardNameBeastByLanguage, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#endif
        45, CARD_DEF_FLAG_FRIEND, 8, 0x2c, 371, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, gCardNameBeast, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn14Frame0, gCardSmn14Tiles, gBeastPalette, &gCardNameBeastByLanguage, gTheBeastSmallCardFrame0, gTheBeastSmallCardTiles, gTheBeastSmallCardPalette,
#endif
        45, CARD_DEF_FLAG_FRIEND, 9, 0x2c, 371, 2, 25, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, &gCardNamePotionByLanguage, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#endif
        32, CARD_DEF_FLAG_ITEM, 0, 0x2f, 381, 2, 30, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, &gCardNamePotionByLanguage, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#endif
        32, CARD_DEF_FLAG_ITEM, 1, 0x2f, 381, 2, 30, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, &gCardNamePotionByLanguage, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#endif
        32, CARD_DEF_FLAG_ITEM, 2, 0x2f, 381, 2, 30, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, &gCardNamePotionByLanguage, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#endif
        32, CARD_DEF_FLAG_ITEM, 3, 0x2f, 381, 2, 30, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, &gCardNamePotionByLanguage, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#endif
        32, CARD_DEF_FLAG_ITEM, 4, 0x2f, 381, 2, 30, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, &gCardNamePotionByLanguage, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#endif
        32, CARD_DEF_FLAG_ITEM, 5, 0x2f, 381, 2, 30, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, &gCardNamePotionByLanguage, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#endif
        32, CARD_DEF_FLAG_ITEM, 6, 0x2f, 381, 2, 30, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, &gCardNamePotionByLanguage, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#endif
        32, CARD_DEF_FLAG_ITEM, 7, 0x2f, 381, 2, 30, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, &gCardNamePotionByLanguage, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#endif
        32, CARD_DEF_FLAG_ITEM, 8, 0x2f, 381, 2, 30, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, gCardNamePotion, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm01Frame0, gCardItm01Tiles, gCardItm01Palette, &gCardNamePotionByLanguage, gPotionSmallCardFrame0, gPotionSmallCardTiles, gPotionSmallCardPalette,
#endif
        32, CARD_DEF_FLAG_ITEM, 9, 0x2f, 381, 2, 30, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, &gCardNameHiPotionByLanguage, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#endif
        33, CARD_DEF_FLAG_ITEM, 0, 0x30, 391, 2, 40, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, &gCardNameHiPotionByLanguage, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#endif
        33, CARD_DEF_FLAG_ITEM, 1, 0x30, 391, 2, 40, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, &gCardNameHiPotionByLanguage, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#endif
        33, CARD_DEF_FLAG_ITEM, 2, 0x30, 391, 2, 40, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, &gCardNameHiPotionByLanguage, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#endif
        33, CARD_DEF_FLAG_ITEM, 3, 0x30, 391, 2, 40, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, &gCardNameHiPotionByLanguage, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#endif
        33, CARD_DEF_FLAG_ITEM, 4, 0x30, 391, 2, 40, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, &gCardNameHiPotionByLanguage, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#endif
        33, CARD_DEF_FLAG_ITEM, 5, 0x30, 391, 2, 40, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, &gCardNameHiPotionByLanguage, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#endif
        33, CARD_DEF_FLAG_ITEM, 6, 0x30, 391, 2, 40, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, &gCardNameHiPotionByLanguage, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#endif
        33, CARD_DEF_FLAG_ITEM, 7, 0x30, 391, 2, 40, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, &gCardNameHiPotionByLanguage, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#endif
        33, CARD_DEF_FLAG_ITEM, 8, 0x30, 391, 2, 40, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, gCardNameHiPotion, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm02Frame0, gCardItm02Tiles, gCardItm02Palette, &gCardNameHiPotionByLanguage, gHiPotionSmallCardFrame0, gHiPotionSmallCardTiles, gHiPotionSmallCardPalette,
#endif
        33, CARD_DEF_FLAG_ITEM, 9, 0x30, 391, 2, 40, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, &gCardNameMegaPotionByLanguage, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#endif
        34, CARD_DEF_FLAG_ITEM, 0, 0x31, 401, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, &gCardNameMegaPotionByLanguage, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#endif
        34, CARD_DEF_FLAG_ITEM, 1, 0x31, 401, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, &gCardNameMegaPotionByLanguage, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#endif
        34, CARD_DEF_FLAG_ITEM, 2, 0x31, 401, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, &gCardNameMegaPotionByLanguage, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#endif
        34, CARD_DEF_FLAG_ITEM, 3, 0x31, 401, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, &gCardNameMegaPotionByLanguage, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#endif
        34, CARD_DEF_FLAG_ITEM, 4, 0x31, 401, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, &gCardNameMegaPotionByLanguage, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#endif
        34, CARD_DEF_FLAG_ITEM, 5, 0x31, 401, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, &gCardNameMegaPotionByLanguage, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#endif
        34, CARD_DEF_FLAG_ITEM, 6, 0x31, 401, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, &gCardNameMegaPotionByLanguage, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#endif
        34, CARD_DEF_FLAG_ITEM, 7, 0x31, 401, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, &gCardNameMegaPotionByLanguage, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#endif
        34, CARD_DEF_FLAG_ITEM, 8, 0x31, 401, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, gCardNameMegaPotion, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm03Frame0, gCardItm03Tiles, gCardItm03Palette, &gCardNameMegaPotionByLanguage, gMegaPotionSmallCardFrame0, gMegaPotionSmallCardTiles, gMegaPotionSmallCardPalette,
#endif
        34, CARD_DEF_FLAG_ITEM, 9, 0x31, 401, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, &gCardNameEtherByLanguage, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#endif
        35, CARD_DEF_FLAG_ITEM, 0, 0x32, 411, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, &gCardNameEtherByLanguage, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#endif
        35, CARD_DEF_FLAG_ITEM, 1, 0x32, 411, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, &gCardNameEtherByLanguage, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#endif
        35, CARD_DEF_FLAG_ITEM, 2, 0x32, 411, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, &gCardNameEtherByLanguage, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#endif
        35, CARD_DEF_FLAG_ITEM, 3, 0x32, 411, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, &gCardNameEtherByLanguage, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#endif
        35, CARD_DEF_FLAG_ITEM, 4, 0x32, 411, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, &gCardNameEtherByLanguage, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#endif
        35, CARD_DEF_FLAG_ITEM, 5, 0x32, 411, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, &gCardNameEtherByLanguage, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#endif
        35, CARD_DEF_FLAG_ITEM, 6, 0x32, 411, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, &gCardNameEtherByLanguage, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#endif
        35, CARD_DEF_FLAG_ITEM, 7, 0x32, 411, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, &gCardNameEtherByLanguage, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#endif
        35, CARD_DEF_FLAG_ITEM, 8, 0x32, 411, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, gCardNameEther, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm04Frame0, gCardItm04Tiles, gCardItm04Palette, &gCardNameEtherByLanguage, gEtherSmallCardFrame0, gEtherSmallCardTiles, gEtherSmallCardPalette,
#endif
        35, CARD_DEF_FLAG_ITEM, 9, 0x32, 411, 2, 20, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, &gCardNameMegaEtherByLanguage, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#endif
        36, CARD_DEF_FLAG_ITEM, 0, 0x33, 421, 2, 35, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, &gCardNameMegaEtherByLanguage, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#endif
        36, CARD_DEF_FLAG_ITEM, 1, 0x33, 421, 2, 35, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, &gCardNameMegaEtherByLanguage, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#endif
        36, CARD_DEF_FLAG_ITEM, 2, 0x33, 421, 2, 35, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, &gCardNameMegaEtherByLanguage, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#endif
        36, CARD_DEF_FLAG_ITEM, 3, 0x33, 421, 2, 35, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, &gCardNameMegaEtherByLanguage, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#endif
        36, CARD_DEF_FLAG_ITEM, 4, 0x33, 421, 2, 35, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, &gCardNameMegaEtherByLanguage, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#endif
        36, CARD_DEF_FLAG_ITEM, 5, 0x33, 421, 2, 35, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, &gCardNameMegaEtherByLanguage, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#endif
        36, CARD_DEF_FLAG_ITEM, 6, 0x33, 421, 2, 35, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, &gCardNameMegaEtherByLanguage, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#endif
        36, CARD_DEF_FLAG_ITEM, 7, 0x33, 421, 2, 35, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, &gCardNameMegaEtherByLanguage, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#endif
        36, CARD_DEF_FLAG_ITEM, 8, 0x33, 421, 2, 35, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, gCardNameMegaEther, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm05Frame0, gCardItm05Tiles, gCardItm05Palette, &gCardNameMegaEtherByLanguage, gMegaEtherSmallCardFrame0, gMegaEtherSmallCardTiles, gMegaEtherSmallCardPalette,
#endif
        36, CARD_DEF_FLAG_ITEM, 9, 0x33, 421, 2, 35, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, &gCardNameElixirByLanguage, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#endif
        37, CARD_DEF_FLAG_ITEM, 0, 0x34, 431, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, &gCardNameElixirByLanguage, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#endif
        37, CARD_DEF_FLAG_ITEM, 1, 0x34, 431, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, &gCardNameElixirByLanguage, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#endif
        37, CARD_DEF_FLAG_ITEM, 2, 0x34, 431, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, &gCardNameElixirByLanguage, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#endif
        37, CARD_DEF_FLAG_ITEM, 3, 0x34, 431, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, &gCardNameElixirByLanguage, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#endif
        37, CARD_DEF_FLAG_ITEM, 4, 0x34, 431, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, &gCardNameElixirByLanguage, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#endif
        37, CARD_DEF_FLAG_ITEM, 5, 0x34, 431, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, &gCardNameElixirByLanguage, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#endif
        37, CARD_DEF_FLAG_ITEM, 6, 0x34, 431, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, &gCardNameElixirByLanguage, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#endif
        37, CARD_DEF_FLAG_ITEM, 7, 0x34, 431, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, &gCardNameElixirByLanguage, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#endif
        37, CARD_DEF_FLAG_ITEM, 8, 0x34, 431, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, gCardNameElixir, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm06Frame0, gCardItm06Tiles, gCardItm06Palette, &gCardNameElixirByLanguage, gElixirSmallCardFrame0, gElixirSmallCardTiles, gElixirSmallCardPalette,
#endif
        37, CARD_DEF_FLAG_ITEM, 9, 0x34, 431, 2, 45, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, &gCardNameMegalixirByLanguage, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#endif
        38, CARD_DEF_FLAG_ITEM, 0, 0x35, 441, 2, 50, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, &gCardNameMegalixirByLanguage, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#endif
        38, CARD_DEF_FLAG_ITEM, 1, 0x35, 441, 2, 50, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, &gCardNameMegalixirByLanguage, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#endif
        38, CARD_DEF_FLAG_ITEM, 2, 0x35, 441, 2, 50, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, &gCardNameMegalixirByLanguage, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#endif
        38, CARD_DEF_FLAG_ITEM, 3, 0x35, 441, 2, 50, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, &gCardNameMegalixirByLanguage, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#endif
        38, CARD_DEF_FLAG_ITEM, 4, 0x35, 441, 2, 50, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, &gCardNameMegalixirByLanguage, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#endif
        38, CARD_DEF_FLAG_ITEM, 5, 0x35, 441, 2, 50, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, &gCardNameMegalixirByLanguage, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#endif
        38, CARD_DEF_FLAG_ITEM, 6, 0x35, 441, 2, 50, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, &gCardNameMegalixirByLanguage, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#endif
        38, CARD_DEF_FLAG_ITEM, 7, 0x35, 441, 2, 50, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, &gCardNameMegalixirByLanguage, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#endif
        38, CARD_DEF_FLAG_ITEM, 8, 0x35, 441, 2, 50, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_JP)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, gCardNameMegalixir, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#elif defined(VERSION_EU)
        gCardItm07Frame0, gCardItm07Tiles, gCardItm07Palette, &gCardNameMegalixirByLanguage, gMegalixirSmallCardFrame0, gMegalixirSmallCardTiles, gMegalixirSmallCardPalette,
#endif
        38, CARD_DEF_FLAG_ITEM, 9, 0x35, 441, 2, 50, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy00Frame0, gCardEmy00Tiles, gEmy00Palette, gEnemyNameShadow, gShadowSmallCardFrame0, gShadowSmallCardTiles, gShadowSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy00Frame0, gCardEmy00Tiles, gEmy00Palette, gEnemyNameShadow, gShadowSmallCardFrame0, gShadowSmallCardTiles, gShadowSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy00Frame0, gCardEmy00Tiles, gEmy00Palette, &gEnemyNameShadowByLanguage, gShadowSmallCardFrame0, gShadowSmallCardTiles, gShadowSmallCardPalette,
#endif
        47, 0x0, 1, 0x1, 450, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy00Frame0, gCardEmy00Tiles, gEmy00Palette, gEnemyNameShadow, gShadowSmallCardFrame0, gShadowSmallCardTiles, gShadowSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy00Frame0, gCardEmy00Tiles, gEmy00Palette, gEnemyNameShadow, gShadowSmallCardFrame0, gShadowSmallCardTiles, gShadowSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy00Frame0, gCardEmy00Tiles, gEmy00Palette, &gEnemyNameShadowByLanguage, gShadowSmallCardFrame0, gShadowSmallCardTiles, gShadowSmallCardPalette,
#endif
        47, 0x0, 1, 0x1, 450, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy00Frame0, gCardEmy00Tiles, gEmy00Palette, gEnemyNameShadow, gShadowSmallCardFrame0, gShadowSmallCardTiles, gShadowSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy00Frame0, gCardEmy00Tiles, gEmy00Palette, gEnemyNameShadow, gShadowSmallCardFrame0, gShadowSmallCardTiles, gShadowSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy00Frame0, gCardEmy00Tiles, gEmy00Palette, &gEnemyNameShadowByLanguage, gShadowSmallCardFrame0, gShadowSmallCardTiles, gShadowSmallCardPalette,
#endif
        47, 0x0, 1, 0x1, 450, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy14Frame0, gCardEmy14Tiles, gEmy14Palette, gEnemyNameSoldier, gSoldierSmallCardFrame0, gSoldierSmallCardTiles, gSoldierSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy14Frame0, gCardEmy14Tiles, gEmy14Palette, gEnemyNameSoldier, gSoldierSmallCardFrame0, gSoldierSmallCardTiles, gSoldierSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy14Frame0, gCardEmy14Tiles, gEmy14Palette, &gEnemyNameSoldierByLanguage, gSoldierSmallCardFrame0, gSoldierSmallCardTiles, gSoldierSmallCardPalette,
#endif
        48, 0x0, 1, 0x3, 453, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy14Frame0, gCardEmy14Tiles, gEmy14Palette, gEnemyNameSoldier, gSoldierSmallCardFrame0, gSoldierSmallCardTiles, gSoldierSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy14Frame0, gCardEmy14Tiles, gEmy14Palette, gEnemyNameSoldier, gSoldierSmallCardFrame0, gSoldierSmallCardTiles, gSoldierSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy14Frame0, gCardEmy14Tiles, gEmy14Palette, &gEnemyNameSoldierByLanguage, gSoldierSmallCardFrame0, gSoldierSmallCardTiles, gSoldierSmallCardPalette,
#endif
        48, 0x0, 2, 0x3, 453, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy14Frame0, gCardEmy14Tiles, gEmy14Palette, gEnemyNameSoldier, gSoldierSmallCardFrame0, gSoldierSmallCardTiles, gSoldierSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy14Frame0, gCardEmy14Tiles, gEmy14Palette, gEnemyNameSoldier, gSoldierSmallCardFrame0, gSoldierSmallCardTiles, gSoldierSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy14Frame0, gCardEmy14Tiles, gEmy14Palette, &gEnemyNameSoldierByLanguage, gSoldierSmallCardFrame0, gSoldierSmallCardTiles, gSoldierSmallCardPalette,
#endif
        48, 0x0, 2, 0x3, 453, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy38Frame0, gCardEmy38Tiles, gEmy38Palette, gEnemyNameLargeBody, gLargeBodySmallCardFrame0, gLargeBodySmallCardTiles, gLargeBodySmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy38Frame0, gCardEmy38Tiles, gEmy38Palette, gEnemyNameLargeBody, gLargeBodySmallCardFrame0, gLargeBodySmallCardTiles, gLargeBodySmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy38Frame0, gCardEmy38Tiles, gEmy38Palette, &gEnemyNameLargeBodyByLanguage, gLargeBodySmallCardFrame0, gLargeBodySmallCardTiles, gLargeBodySmallCardPalette,
#endif
        49, 0x0, 1, 0x33, 456, 3, 40, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy38Frame0, gCardEmy38Tiles, gEmy38Palette, gEnemyNameLargeBody, gLargeBodySmallCardFrame0, gLargeBodySmallCardTiles, gLargeBodySmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy38Frame0, gCardEmy38Tiles, gEmy38Palette, gEnemyNameLargeBody, gLargeBodySmallCardFrame0, gLargeBodySmallCardTiles, gLargeBodySmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy38Frame0, gCardEmy38Tiles, gEmy38Palette, &gEnemyNameLargeBodyByLanguage, gLargeBodySmallCardFrame0, gLargeBodySmallCardTiles, gLargeBodySmallCardPalette,
#endif
        49, 0x0, 3, 0x33, 456, 3, 40, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy38Frame0, gCardEmy38Tiles, gEmy38Palette, gEnemyNameLargeBody, gLargeBodySmallCardFrame0, gLargeBodySmallCardTiles, gLargeBodySmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy38Frame0, gCardEmy38Tiles, gEmy38Palette, gEnemyNameLargeBody, gLargeBodySmallCardFrame0, gLargeBodySmallCardTiles, gLargeBodySmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy38Frame0, gCardEmy38Tiles, gEmy38Palette, &gEnemyNameLargeBodyByLanguage, gLargeBodySmallCardFrame0, gLargeBodySmallCardTiles, gLargeBodySmallCardPalette,
#endif
        49, 0x0, 4, 0x33, 456, 3, 40, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy01Frame0, gCardEmy01Tiles, gEmy01Palette, gEnemyNameRedNocturne, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gRedNocturneSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy01Frame0, gCardEmy01Tiles, gEmy01Palette, gEnemyNameRedNocturne, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gRedNocturneSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy01Frame0, gCardEmy01Tiles, gEmy01Palette, &gEnemyNameRedNocturneByLanguage, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gRedNocturneSmallCardPalette,
#endif
        50, 0x0, 1, 0x4, 459, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy01Frame0, gCardEmy01Tiles, gEmy01Palette, gEnemyNameRedNocturne, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gRedNocturneSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy01Frame0, gCardEmy01Tiles, gEmy01Palette, gEnemyNameRedNocturne, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gRedNocturneSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy01Frame0, gCardEmy01Tiles, gEmy01Palette, &gEnemyNameRedNocturneByLanguage, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gRedNocturneSmallCardPalette,
#endif
        50, 0x0, 2, 0x4, 459, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy01Frame0, gCardEmy01Tiles, gEmy01Palette, gEnemyNameRedNocturne, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gRedNocturneSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy01Frame0, gCardEmy01Tiles, gEmy01Palette, gEnemyNameRedNocturne, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gRedNocturneSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy01Frame0, gCardEmy01Tiles, gEmy01Palette, &gEnemyNameRedNocturneByLanguage, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gRedNocturneSmallCardPalette,
#endif
        50, 0x0, 4, 0x4, 459, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gBlueRhapsodyCardFrame0, gBlueRhapsodyCardTiles, gEmy02Palette, gEnemyNameBlueRhapsody, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gBlueRhapsodySmallCardPalette,
#elif defined(VERSION_JP)
        gBlueRhapsodyCardFrame0, gBlueRhapsodyCardTiles, gEmy02Palette, gEnemyNameBlueRhapsody, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gBlueRhapsodySmallCardPalette,
#elif defined(VERSION_EU)
        gBlueRhapsodyCardFrame0, gBlueRhapsodyCardTiles, gEmy02Palette, &gEnemyNameBlueRhapsodyByLanguage, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gBlueRhapsodySmallCardPalette,
#endif
        51, 0x0, 1, 0xb, 463, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gBlueRhapsodyCardFrame0, gBlueRhapsodyCardTiles, gEmy02Palette, gEnemyNameBlueRhapsody, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gBlueRhapsodySmallCardPalette,
#elif defined(VERSION_JP)
        gBlueRhapsodyCardFrame0, gBlueRhapsodyCardTiles, gEmy02Palette, gEnemyNameBlueRhapsody, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gBlueRhapsodySmallCardPalette,
#elif defined(VERSION_EU)
        gBlueRhapsodyCardFrame0, gBlueRhapsodyCardTiles, gEmy02Palette, &gEnemyNameBlueRhapsodyByLanguage, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gBlueRhapsodySmallCardPalette,
#endif
        51, 0x0, 2, 0xb, 463, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gBlueRhapsodyCardFrame0, gBlueRhapsodyCardTiles, gEmy02Palette, gEnemyNameBlueRhapsody, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gBlueRhapsodySmallCardPalette,
#elif defined(VERSION_JP)
        gBlueRhapsodyCardFrame0, gBlueRhapsodyCardTiles, gEmy02Palette, gEnemyNameBlueRhapsody, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gBlueRhapsodySmallCardPalette,
#elif defined(VERSION_EU)
        gBlueRhapsodyCardFrame0, gBlueRhapsodyCardTiles, gEmy02Palette, &gEnemyNameBlueRhapsodyByLanguage, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gBlueRhapsodySmallCardPalette,
#endif
        51, 0x0, 4, 0xb, 463, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gYellowOperaCardFrame0, gYellowOperaCardTiles, gEmy03Palette, gEnemyNameYellowOpera, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gYellowOperaSmallCardPalette,
#elif defined(VERSION_JP)
        gYellowOperaCardFrame0, gYellowOperaCardTiles, gEmy03Palette, gEnemyNameYellowOpera, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gYellowOperaSmallCardPalette,
#elif defined(VERSION_EU)
        gYellowOperaCardFrame0, gYellowOperaCardTiles, gEmy03Palette, &gEnemyNameYellowOperaByLanguage, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gYellowOperaSmallCardPalette,
#endif
        52, 0x0, 1, 0xc, 466, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gYellowOperaCardFrame0, gYellowOperaCardTiles, gEmy03Palette, gEnemyNameYellowOpera, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gYellowOperaSmallCardPalette,
#elif defined(VERSION_JP)
        gYellowOperaCardFrame0, gYellowOperaCardTiles, gEmy03Palette, gEnemyNameYellowOpera, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gYellowOperaSmallCardPalette,
#elif defined(VERSION_EU)
        gYellowOperaCardFrame0, gYellowOperaCardTiles, gEmy03Palette, &gEnemyNameYellowOperaByLanguage, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gYellowOperaSmallCardPalette,
#endif
        52, 0x0, 2, 0xc, 466, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gYellowOperaCardFrame0, gYellowOperaCardTiles, gEmy03Palette, gEnemyNameYellowOpera, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gYellowOperaSmallCardPalette,
#elif defined(VERSION_JP)
        gYellowOperaCardFrame0, gYellowOperaCardTiles, gEmy03Palette, gEnemyNameYellowOpera, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gYellowOperaSmallCardPalette,
#elif defined(VERSION_EU)
        gYellowOperaCardFrame0, gYellowOperaCardTiles, gEmy03Palette, &gEnemyNameYellowOperaByLanguage, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gYellowOperaSmallCardPalette,
#endif
        52, 0x0, 4, 0xc, 466, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gGreenRequiemCardFrame0, gGreenRequiemCardTiles, gEmy04Palette, gEnemyNameGreenRequiem, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gGreenRequiemSmallCardPalette,
#elif defined(VERSION_JP)
        gGreenRequiemCardFrame0, gGreenRequiemCardTiles, gEmy04Palette, gEnemyNameGreenRequiem, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gGreenRequiemSmallCardPalette,
#elif defined(VERSION_EU)
        gGreenRequiemCardFrame0, gGreenRequiemCardTiles, gEmy04Palette, &gEnemyNameGreenRequiemByLanguage, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gGreenRequiemSmallCardPalette,
#endif
        53, 0x0, 1, 0xd, 469, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gGreenRequiemCardFrame0, gGreenRequiemCardTiles, gEmy04Palette, gEnemyNameGreenRequiem, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gGreenRequiemSmallCardPalette,
#elif defined(VERSION_JP)
        gGreenRequiemCardFrame0, gGreenRequiemCardTiles, gEmy04Palette, gEnemyNameGreenRequiem, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gGreenRequiemSmallCardPalette,
#elif defined(VERSION_EU)
        gGreenRequiemCardFrame0, gGreenRequiemCardTiles, gEmy04Palette, &gEnemyNameGreenRequiemByLanguage, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gGreenRequiemSmallCardPalette,
#endif
        53, 0x0, 2, 0xd, 469, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gGreenRequiemCardFrame0, gGreenRequiemCardTiles, gEmy04Palette, gEnemyNameGreenRequiem, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gGreenRequiemSmallCardPalette,
#elif defined(VERSION_JP)
        gGreenRequiemCardFrame0, gGreenRequiemCardTiles, gEmy04Palette, gEnemyNameGreenRequiem, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gGreenRequiemSmallCardPalette,
#elif defined(VERSION_EU)
        gGreenRequiemCardFrame0, gGreenRequiemCardTiles, gEmy04Palette, &gEnemyNameGreenRequiemByLanguage, gRedNocturneSmallCardFrame0, gRedNocturneSmallCardTiles, gGreenRequiemSmallCardPalette,
#endif
        53, 0x0, 4, 0xd, 469, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy15Frame0, gCardEmy15Tiles, gEmy15Palette, gEnemyNamePowerwild, gPowerwildSmallCardFrame0, gPowerwildSmallCardTiles, gPowerwildSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy15Frame0, gCardEmy15Tiles, gEmy15Palette, gEnemyNamePowerwild, gPowerwildSmallCardFrame0, gPowerwildSmallCardTiles, gPowerwildSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy15Frame0, gCardEmy15Tiles, gEmy15Palette, &gEnemyNamePowerwildByLanguage, gPowerwildSmallCardFrame0, gPowerwildSmallCardTiles, gPowerwildSmallCardPalette,
#endif
        54, 0x0, 3, 0x1f, 471, 3, 40, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy15Frame0, gCardEmy15Tiles, gEmy15Palette, gEnemyNamePowerwild, gPowerwildSmallCardFrame0, gPowerwildSmallCardTiles, gPowerwildSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy15Frame0, gCardEmy15Tiles, gEmy15Palette, gEnemyNamePowerwild, gPowerwildSmallCardFrame0, gPowerwildSmallCardTiles, gPowerwildSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy15Frame0, gCardEmy15Tiles, gEmy15Palette, &gEnemyNamePowerwildByLanguage, gPowerwildSmallCardFrame0, gPowerwildSmallCardTiles, gPowerwildSmallCardPalette,
#endif
        54, 0x0, 3, 0x1f, 471, 3, 40, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy15Frame0, gCardEmy15Tiles, gEmy15Palette, gEnemyNamePowerwild, gPowerwildSmallCardFrame0, gPowerwildSmallCardTiles, gPowerwildSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy15Frame0, gCardEmy15Tiles, gEmy15Palette, gEnemyNamePowerwild, gPowerwildSmallCardFrame0, gPowerwildSmallCardTiles, gPowerwildSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy15Frame0, gCardEmy15Tiles, gEmy15Palette, &gEnemyNamePowerwildByLanguage, gPowerwildSmallCardFrame0, gPowerwildSmallCardTiles, gPowerwildSmallCardPalette,
#endif
        54, 0x0, 3, 0x1f, 471, 3, 40, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy16Frame0, gCardEmy16Tiles, gEmy16Palette, gEnemyNameBouncywild, gBouncywildSmallCardFrame0, gBouncywildSmallCardTiles, gBouncywildSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy16Frame0, gCardEmy16Tiles, gEmy16Palette, gEnemyNameBouncywild, gBouncywildSmallCardFrame0, gBouncywildSmallCardTiles, gBouncywildSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy16Frame0, gCardEmy16Tiles, gEmy16Palette, &gEnemyNameBouncywildByLanguage, gBouncywildSmallCardFrame0, gBouncywildSmallCardTiles, gBouncywildSmallCardPalette,
#endif
        55, 0x0, 2, 0x6, 474, 3, 10, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy16Frame0, gCardEmy16Tiles, gEmy16Palette, gEnemyNameBouncywild, gBouncywildSmallCardFrame0, gBouncywildSmallCardTiles, gBouncywildSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy16Frame0, gCardEmy16Tiles, gEmy16Palette, gEnemyNameBouncywild, gBouncywildSmallCardFrame0, gBouncywildSmallCardTiles, gBouncywildSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy16Frame0, gCardEmy16Tiles, gEmy16Palette, &gEnemyNameBouncywildByLanguage, gBouncywildSmallCardFrame0, gBouncywildSmallCardTiles, gBouncywildSmallCardPalette,
#endif
        55, 0x0, 2, 0x6, 474, 3, 10, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy16Frame0, gCardEmy16Tiles, gEmy16Palette, gEnemyNameBouncywild, gBouncywildSmallCardFrame0, gBouncywildSmallCardTiles, gBouncywildSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy16Frame0, gCardEmy16Tiles, gEmy16Palette, gEnemyNameBouncywild, gBouncywildSmallCardFrame0, gBouncywildSmallCardTiles, gBouncywildSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy16Frame0, gCardEmy16Tiles, gEmy16Palette, &gEnemyNameBouncywildByLanguage, gBouncywildSmallCardFrame0, gBouncywildSmallCardTiles, gBouncywildSmallCardPalette,
#endif
        55, 0x0, 2, 0x6, 474, 3, 10, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy18Frame0, gCardEmy18Tiles, gEmy18Palette, gEnemyNameAirSoldier, gAirSoldierSmallCardFrame0, gAirSoldierSmallCardTiles, gAirSoldierSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy18Frame0, gCardEmy18Tiles, gEmy18Palette, gEnemyNameAirSoldier, gAirSoldierSmallCardFrame0, gAirSoldierSmallCardTiles, gAirSoldierSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy18Frame0, gCardEmy18Tiles, gEmy18Palette, &gEnemyNameAirSoldierByLanguage, gAirSoldierSmallCardFrame0, gAirSoldierSmallCardTiles, gAirSoldierSmallCardPalette,
#endif
        56, 0x0, 3, 0x1e, 477, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy18Frame0, gCardEmy18Tiles, gEmy18Palette, gEnemyNameAirSoldier, gAirSoldierSmallCardFrame0, gAirSoldierSmallCardTiles, gAirSoldierSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy18Frame0, gCardEmy18Tiles, gEmy18Palette, gEnemyNameAirSoldier, gAirSoldierSmallCardFrame0, gAirSoldierSmallCardTiles, gAirSoldierSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy18Frame0, gCardEmy18Tiles, gEmy18Palette, &gEnemyNameAirSoldierByLanguage, gAirSoldierSmallCardFrame0, gAirSoldierSmallCardTiles, gAirSoldierSmallCardPalette,
#endif
        56, 0x0, 4, 0x1e, 477, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy18Frame0, gCardEmy18Tiles, gEmy18Palette, gEnemyNameAirSoldier, gAirSoldierSmallCardFrame0, gAirSoldierSmallCardTiles, gAirSoldierSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy18Frame0, gCardEmy18Tiles, gEmy18Palette, gEnemyNameAirSoldier, gAirSoldierSmallCardFrame0, gAirSoldierSmallCardTiles, gAirSoldierSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy18Frame0, gCardEmy18Tiles, gEmy18Palette, &gEnemyNameAirSoldierByLanguage, gAirSoldierSmallCardFrame0, gAirSoldierSmallCardTiles, gAirSoldierSmallCardPalette,
#endif
        56, 0x0, 4, 0x1e, 477, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy19Frame0, gCardEmy19Tiles, gEmy19Palette, gEnemyNameBandit, gBanditSmallCardFrame0, gBanditSmallCardTiles, gBanditSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy19Frame0, gCardEmy19Tiles, gEmy19Palette, gEnemyNameBandit, gBanditSmallCardFrame0, gBanditSmallCardTiles, gBanditSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy19Frame0, gCardEmy19Tiles, gEmy19Palette, &gEnemyNameBanditByLanguage, gBanditSmallCardFrame0, gBanditSmallCardTiles, gBanditSmallCardPalette,
#endif
        57, 0x0, 1, 0x5, 480, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy19Frame0, gCardEmy19Tiles, gEmy19Palette, gEnemyNameBandit, gBanditSmallCardFrame0, gBanditSmallCardTiles, gBanditSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy19Frame0, gCardEmy19Tiles, gEmy19Palette, gEnemyNameBandit, gBanditSmallCardFrame0, gBanditSmallCardTiles, gBanditSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy19Frame0, gCardEmy19Tiles, gEmy19Palette, &gEnemyNameBanditByLanguage, gBanditSmallCardFrame0, gBanditSmallCardTiles, gBanditSmallCardPalette,
#endif
        57, 0x0, 2, 0x5, 480, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy19Frame0, gCardEmy19Tiles, gEmy19Palette, gEnemyNameBandit, gBanditSmallCardFrame0, gBanditSmallCardTiles, gBanditSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy19Frame0, gCardEmy19Tiles, gEmy19Palette, gEnemyNameBandit, gBanditSmallCardFrame0, gBanditSmallCardTiles, gBanditSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy19Frame0, gCardEmy19Tiles, gEmy19Palette, &gEnemyNameBanditByLanguage, gBanditSmallCardFrame0, gBanditSmallCardTiles, gBanditSmallCardPalette,
#endif
        57, 0x0, 2, 0x5, 480, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy39Frame0, gCardEmy39Tiles, gEmy39Palette, gEnemyNameFatBandit, gFatBanditSmallCardFrame0, gFatBanditSmallCardTiles, gFatBanditSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy39Frame0, gCardEmy39Tiles, gEmy39Palette, gEnemyNameFatBandit, gFatBanditSmallCardFrame0, gFatBanditSmallCardTiles, gFatBanditSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy39Frame0, gCardEmy39Tiles, gEmy39Palette, &gEnemyNameFatBanditByLanguage, gFatBanditSmallCardFrame0, gFatBanditSmallCardTiles, gFatBanditSmallCardPalette,
#endif
        58, 0x0, 3, 0x24, 483, 3, 40, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy39Frame0, gCardEmy39Tiles, gEmy39Palette, gEnemyNameFatBandit, gFatBanditSmallCardFrame0, gFatBanditSmallCardTiles, gFatBanditSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy39Frame0, gCardEmy39Tiles, gEmy39Palette, gEnemyNameFatBandit, gFatBanditSmallCardFrame0, gFatBanditSmallCardTiles, gFatBanditSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy39Frame0, gCardEmy39Tiles, gEmy39Palette, &gEnemyNameFatBanditByLanguage, gFatBanditSmallCardFrame0, gFatBanditSmallCardTiles, gFatBanditSmallCardPalette,
#endif
        58, 0x0, 1, 0x24, 483, 3, 40, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy39Frame0, gCardEmy39Tiles, gEmy39Palette, gEnemyNameFatBandit, gFatBanditSmallCardFrame0, gFatBanditSmallCardTiles, gFatBanditSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy39Frame0, gCardEmy39Tiles, gEmy39Palette, gEnemyNameFatBandit, gFatBanditSmallCardFrame0, gFatBanditSmallCardTiles, gFatBanditSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy39Frame0, gCardEmy39Tiles, gEmy39Palette, &gEnemyNameFatBanditByLanguage, gFatBanditSmallCardFrame0, gFatBanditSmallCardTiles, gFatBanditSmallCardPalette,
#endif
        58, 0x0, 6, 0x24, 483, 3, 40, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy21Frame0, gCardEmy21Tiles, gEmy21Palette, gEnemyNameBarrelSpider, gBarrelSpiderSmallCardFrame0, gBarrelSpiderSmallCardTiles, gBarrelSpiderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy21Frame0, gCardEmy21Tiles, gEmy21Palette, gEnemyNameBarrelSpider, gBarrelSpiderSmallCardFrame0, gBarrelSpiderSmallCardTiles, gBarrelSpiderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy21Frame0, gCardEmy21Tiles, gEmy21Palette, &gEnemyNameBarrelSpiderByLanguage, gBarrelSpiderSmallCardFrame0, gBarrelSpiderSmallCardTiles, gBarrelSpiderSmallCardPalette,
#endif
        59, 0x0, 4, 0x9, 486, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy21Frame0, gCardEmy21Tiles, gEmy21Palette, gEnemyNameBarrelSpider, gBarrelSpiderSmallCardFrame0, gBarrelSpiderSmallCardTiles, gBarrelSpiderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy21Frame0, gCardEmy21Tiles, gEmy21Palette, gEnemyNameBarrelSpider, gBarrelSpiderSmallCardFrame0, gBarrelSpiderSmallCardTiles, gBarrelSpiderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy21Frame0, gCardEmy21Tiles, gEmy21Palette, &gEnemyNameBarrelSpiderByLanguage, gBarrelSpiderSmallCardFrame0, gBarrelSpiderSmallCardTiles, gBarrelSpiderSmallCardPalette,
#endif
        59, 0x0, 4, 0x9, 486, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy21Frame0, gCardEmy21Tiles, gEmy21Palette, gEnemyNameBarrelSpider, gBarrelSpiderSmallCardFrame0, gBarrelSpiderSmallCardTiles, gBarrelSpiderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy21Frame0, gCardEmy21Tiles, gEmy21Palette, gEnemyNameBarrelSpider, gBarrelSpiderSmallCardFrame0, gBarrelSpiderSmallCardTiles, gBarrelSpiderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy21Frame0, gCardEmy21Tiles, gEmy21Palette, &gEnemyNameBarrelSpiderByLanguage, gBarrelSpiderSmallCardFrame0, gBarrelSpiderSmallCardTiles, gBarrelSpiderSmallCardPalette,
#endif
        59, 0x0, 4, 0x9, 486, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy22Frame0, gCardEmy22Tiles, gEmy22Palette, gEnemyNameSearchGhost, gSearchGhostSmallCardFrame0, gSearchGhostSmallCardTiles, gSearchGhostSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy22Frame0, gCardEmy22Tiles, gEmy22Palette, gEnemyNameSearchGhost, gSearchGhostSmallCardFrame0, gSearchGhostSmallCardTiles, gSearchGhostSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy22Frame0, gCardEmy22Tiles, gEmy22Palette, &gEnemyNameSearchGhostByLanguage, gSearchGhostSmallCardFrame0, gSearchGhostSmallCardTiles, gSearchGhostSmallCardPalette,
#endif
        60, 0x0, 1, 0x23, 489, 3, 35, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy22Frame0, gCardEmy22Tiles, gEmy22Palette, gEnemyNameSearchGhost, gSearchGhostSmallCardFrame0, gSearchGhostSmallCardTiles, gSearchGhostSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy22Frame0, gCardEmy22Tiles, gEmy22Palette, gEnemyNameSearchGhost, gSearchGhostSmallCardFrame0, gSearchGhostSmallCardTiles, gSearchGhostSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy22Frame0, gCardEmy22Tiles, gEmy22Palette, &gEnemyNameSearchGhostByLanguage, gSearchGhostSmallCardFrame0, gSearchGhostSmallCardTiles, gSearchGhostSmallCardPalette,
#endif
        60, 0x0, 2, 0x23, 489, 3, 35, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy22Frame0, gCardEmy22Tiles, gEmy22Palette, gEnemyNameSearchGhost, gSearchGhostSmallCardFrame0, gSearchGhostSmallCardTiles, gSearchGhostSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy22Frame0, gCardEmy22Tiles, gEmy22Palette, gEnemyNameSearchGhost, gSearchGhostSmallCardFrame0, gSearchGhostSmallCardTiles, gSearchGhostSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy22Frame0, gCardEmy22Tiles, gEmy22Palette, &gEnemyNameSearchGhostByLanguage, gSearchGhostSmallCardFrame0, gSearchGhostSmallCardTiles, gSearchGhostSmallCardPalette,
#endif
        60, 0x0, 2, 0x23, 489, 3, 35, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy06Frame0, gCardEmy06Tiles, gEmy06Palette, gEnemyNameSeaNeon, gSeaNeonSmallCardFrame0, gSeaNeonSmallCardTiles, gSeaNeonSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy06Frame0, gCardEmy06Tiles, gEmy06Palette, gEnemyNameSeaNeon, gSeaNeonSmallCardFrame0, gSeaNeonSmallCardTiles, gSeaNeonSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy06Frame0, gCardEmy06Tiles, gEmy06Palette, &gEnemyNameSeaNeonByLanguage, gSeaNeonSmallCardFrame0, gSeaNeonSmallCardTiles, gSeaNeonSmallCardPalette,
#endif
        61, 0x0, 1, 0x10, 492, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy06Frame0, gCardEmy06Tiles, gEmy06Palette, gEnemyNameSeaNeon, gSeaNeonSmallCardFrame0, gSeaNeonSmallCardTiles, gSeaNeonSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy06Frame0, gCardEmy06Tiles, gEmy06Palette, gEnemyNameSeaNeon, gSeaNeonSmallCardFrame0, gSeaNeonSmallCardTiles, gSeaNeonSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy06Frame0, gCardEmy06Tiles, gEmy06Palette, &gEnemyNameSeaNeonByLanguage, gSeaNeonSmallCardFrame0, gSeaNeonSmallCardTiles, gSeaNeonSmallCardPalette,
#endif
        61, 0x0, 1, 0x10, 492, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy06Frame0, gCardEmy06Tiles, gEmy06Palette, gEnemyNameSeaNeon, gSeaNeonSmallCardFrame0, gSeaNeonSmallCardTiles, gSeaNeonSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy06Frame0, gCardEmy06Tiles, gEmy06Palette, gEnemyNameSeaNeon, gSeaNeonSmallCardFrame0, gSeaNeonSmallCardTiles, gSeaNeonSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy06Frame0, gCardEmy06Tiles, gEmy06Palette, &gEnemyNameSeaNeonByLanguage, gSeaNeonSmallCardFrame0, gSeaNeonSmallCardTiles, gSeaNeonSmallCardPalette,
#endif
        61, 0x0, 1, 0x10, 492, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy23Frame0, gCardEmy23Tiles, gEmy23Palette, gEnemyNameScrewdiver, gScrewdiverSmallCardFrame0, gScrewdiverSmallCardTiles, gScrewdiverSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy23Frame0, gCardEmy23Tiles, gEmy23Palette, gEnemyNameScrewdiver, gScrewdiverSmallCardFrame0, gScrewdiverSmallCardTiles, gScrewdiverSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy23Frame0, gCardEmy23Tiles, gEmy23Palette, &gEnemyNameScrewdiverByLanguage, gScrewdiverSmallCardFrame0, gScrewdiverSmallCardTiles, gScrewdiverSmallCardPalette,
#endif
        62, 0x0, 1, 0x15, 495, 3, 15, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy23Frame0, gCardEmy23Tiles, gEmy23Palette, gEnemyNameScrewdiver, gScrewdiverSmallCardFrame0, gScrewdiverSmallCardTiles, gScrewdiverSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy23Frame0, gCardEmy23Tiles, gEmy23Palette, gEnemyNameScrewdiver, gScrewdiverSmallCardFrame0, gScrewdiverSmallCardTiles, gScrewdiverSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy23Frame0, gCardEmy23Tiles, gEmy23Palette, &gEnemyNameScrewdiverByLanguage, gScrewdiverSmallCardFrame0, gScrewdiverSmallCardTiles, gScrewdiverSmallCardPalette,
#endif
        62, 0x0, 2, 0x15, 495, 3, 15, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy23Frame0, gCardEmy23Tiles, gEmy23Palette, gEnemyNameScrewdiver, gScrewdiverSmallCardFrame0, gScrewdiverSmallCardTiles, gScrewdiverSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy23Frame0, gCardEmy23Tiles, gEmy23Palette, gEnemyNameScrewdiver, gScrewdiverSmallCardFrame0, gScrewdiverSmallCardTiles, gScrewdiverSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy23Frame0, gCardEmy23Tiles, gEmy23Palette, &gEnemyNameScrewdiverByLanguage, gScrewdiverSmallCardFrame0, gScrewdiverSmallCardTiles, gScrewdiverSmallCardPalette,
#endif
        62, 0x0, 2, 0x15, 495, 3, 15, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy41Frame0, gCardEmy41Tiles, gEmy41Palette, gEnemyNameAquatank, gAquatankSmallCardFrame0, gAquatankSmallCardTiles, gAquatankSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy41Frame0, gCardEmy41Tiles, gEmy41Palette, gEnemyNameAquatank, gAquatankSmallCardFrame0, gAquatankSmallCardTiles, gAquatankSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy41Frame0, gCardEmy41Tiles, gEmy41Palette, &gEnemyNameAquatankByLanguage, gAquatankSmallCardFrame0, gAquatankSmallCardTiles, gAquatankSmallCardPalette,
#endif
        63, 0x0, 2, 0x28, 498, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy41Frame0, gCardEmy41Tiles, gEmy41Palette, gEnemyNameAquatank, gAquatankSmallCardFrame0, gAquatankSmallCardTiles, gAquatankSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy41Frame0, gCardEmy41Tiles, gEmy41Palette, gEnemyNameAquatank, gAquatankSmallCardFrame0, gAquatankSmallCardTiles, gAquatankSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy41Frame0, gCardEmy41Tiles, gEmy41Palette, &gEnemyNameAquatankByLanguage, gAquatankSmallCardFrame0, gAquatankSmallCardTiles, gAquatankSmallCardPalette,
#endif
        63, 0x0, 1, 0x28, 498, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy41Frame0, gCardEmy41Tiles, gEmy41Palette, gEnemyNameAquatank, gAquatankSmallCardFrame0, gAquatankSmallCardTiles, gAquatankSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy41Frame0, gCardEmy41Tiles, gEmy41Palette, gEnemyNameAquatank, gAquatankSmallCardFrame0, gAquatankSmallCardTiles, gAquatankSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy41Frame0, gCardEmy41Tiles, gEmy41Palette, &gEnemyNameAquatankByLanguage, gAquatankSmallCardFrame0, gAquatankSmallCardTiles, gAquatankSmallCardPalette,
#endif
        63, 0x0, 7, 0x28, 498, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy25Frame0, gCardEmy25Tiles, gEmy25Palette, gEnemyNameWightKnight, gWightKnightSmallCardFrame0, gWightKnightSmallCardTiles, gWightKnightSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy25Frame0, gCardEmy25Tiles, gEmy25Palette, gEnemyNameWightKnight, gWightKnightSmallCardFrame0, gWightKnightSmallCardTiles, gWightKnightSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy25Frame0, gCardEmy25Tiles, gEmy25Palette, &gEnemyNameWightKnightByLanguage, gWightKnightSmallCardFrame0, gWightKnightSmallCardTiles, gWightKnightSmallCardPalette,
#endif
        64, 0x0, 2, 0x35, 501, 3, 15, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy25Frame0, gCardEmy25Tiles, gEmy25Palette, gEnemyNameWightKnight, gWightKnightSmallCardFrame0, gWightKnightSmallCardTiles, gWightKnightSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy25Frame0, gCardEmy25Tiles, gEmy25Palette, gEnemyNameWightKnight, gWightKnightSmallCardFrame0, gWightKnightSmallCardTiles, gWightKnightSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy25Frame0, gCardEmy25Tiles, gEmy25Palette, &gEnemyNameWightKnightByLanguage, gWightKnightSmallCardFrame0, gWightKnightSmallCardTiles, gWightKnightSmallCardPalette,
#endif
        64, 0x0, 3, 0x35, 501, 3, 15, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy25Frame0, gCardEmy25Tiles, gEmy25Palette, gEnemyNameWightKnight, gWightKnightSmallCardFrame0, gWightKnightSmallCardTiles, gWightKnightSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy25Frame0, gCardEmy25Tiles, gEmy25Palette, gEnemyNameWightKnight, gWightKnightSmallCardFrame0, gWightKnightSmallCardTiles, gWightKnightSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy25Frame0, gCardEmy25Tiles, gEmy25Palette, &gEnemyNameWightKnightByLanguage, gWightKnightSmallCardFrame0, gWightKnightSmallCardTiles, gWightKnightSmallCardPalette,
#endif
        64, 0x0, 3, 0x35, 501, 3, 15, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy26Frame0, gCardEmy26Tiles, gEmy26Palette, gEnemyNameGargoyle, gGargoyleSmallCardFrame0, gGargoyleSmallCardTiles, gGargoyleSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy26Frame0, gCardEmy26Tiles, gEmy26Palette, gEnemyNameGargoyle, gGargoyleSmallCardFrame0, gGargoyleSmallCardTiles, gGargoyleSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy26Frame0, gCardEmy26Tiles, gEmy26Palette, &gEnemyNameGargoyleByLanguage, gGargoyleSmallCardFrame0, gGargoyleSmallCardTiles, gGargoyleSmallCardPalette,
#endif
        65, 0x0, 3, 0x13, 504, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy26Frame0, gCardEmy26Tiles, gEmy26Palette, gEnemyNameGargoyle, gGargoyleSmallCardFrame0, gGargoyleSmallCardTiles, gGargoyleSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy26Frame0, gCardEmy26Tiles, gEmy26Palette, gEnemyNameGargoyle, gGargoyleSmallCardFrame0, gGargoyleSmallCardTiles, gGargoyleSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy26Frame0, gCardEmy26Tiles, gEmy26Palette, &gEnemyNameGargoyleByLanguage, gGargoyleSmallCardFrame0, gGargoyleSmallCardTiles, gGargoyleSmallCardPalette,
#endif
        65, 0x0, 4, 0x13, 504, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy26Frame0, gCardEmy26Tiles, gEmy26Palette, gEnemyNameGargoyle, gGargoyleSmallCardFrame0, gGargoyleSmallCardTiles, gGargoyleSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy26Frame0, gCardEmy26Tiles, gEmy26Palette, gEnemyNameGargoyle, gGargoyleSmallCardFrame0, gGargoyleSmallCardTiles, gGargoyleSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy26Frame0, gCardEmy26Tiles, gEmy26Palette, &gEnemyNameGargoyleByLanguage, gGargoyleSmallCardFrame0, gGargoyleSmallCardTiles, gGargoyleSmallCardPalette,
#endif
        65, 0x0, 4, 0x13, 504, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy27Frame0, gCardEmy27Tiles, gEmy27Palette, gEnemyNamePirate, gPirateSmallCardFrame0, gPirateSmallCardTiles, gPirateSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy27Frame0, gCardEmy27Tiles, gEmy27Palette, gEnemyNamePirate, gPirateSmallCardFrame0, gPirateSmallCardTiles, gPirateSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy27Frame0, gCardEmy27Tiles, gEmy27Palette, &gEnemyNamePirateByLanguage, gPirateSmallCardFrame0, gPirateSmallCardTiles, gPirateSmallCardPalette,
#endif
        66, 0x0, 1, 0x11, 507, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy27Frame0, gCardEmy27Tiles, gEmy27Palette, gEnemyNamePirate, gPirateSmallCardFrame0, gPirateSmallCardTiles, gPirateSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy27Frame0, gCardEmy27Tiles, gEmy27Palette, gEnemyNamePirate, gPirateSmallCardFrame0, gPirateSmallCardTiles, gPirateSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy27Frame0, gCardEmy27Tiles, gEmy27Palette, &gEnemyNamePirateByLanguage, gPirateSmallCardFrame0, gPirateSmallCardTiles, gPirateSmallCardPalette,
#endif
        66, 0x0, 2, 0x11, 507, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy27Frame0, gCardEmy27Tiles, gEmy27Palette, gEnemyNamePirate, gPirateSmallCardFrame0, gPirateSmallCardTiles, gPirateSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy27Frame0, gCardEmy27Tiles, gEmy27Palette, gEnemyNamePirate, gPirateSmallCardFrame0, gPirateSmallCardTiles, gPirateSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy27Frame0, gCardEmy27Tiles, gEmy27Palette, &gEnemyNamePirateByLanguage, gPirateSmallCardFrame0, gPirateSmallCardTiles, gPirateSmallCardPalette,
#endif
        66, 0x0, 2, 0x11, 507, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy28Frame0, gCardEmy28Tiles, gEmy28Palette, gEnemyNameAirPirate, gAirPirateSmallCardFrame0, gAirPirateSmallCardTiles, gAirPirateSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy28Frame0, gCardEmy28Tiles, gEmy28Palette, gEnemyNameAirPirate, gAirPirateSmallCardFrame0, gAirPirateSmallCardTiles, gAirPirateSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy28Frame0, gCardEmy28Tiles, gEmy28Palette, &gEnemyNameAirPirateByLanguage, gAirPirateSmallCardFrame0, gAirPirateSmallCardTiles, gAirPirateSmallCardPalette,
#endif
        67, 0x0, 3, 0x1d, 510, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy28Frame0, gCardEmy28Tiles, gEmy28Palette, gEnemyNameAirPirate, gAirPirateSmallCardFrame0, gAirPirateSmallCardTiles, gAirPirateSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy28Frame0, gCardEmy28Tiles, gEmy28Palette, gEnemyNameAirPirate, gAirPirateSmallCardFrame0, gAirPirateSmallCardTiles, gAirPirateSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy28Frame0, gCardEmy28Tiles, gEmy28Palette, &gEnemyNameAirPirateByLanguage, gAirPirateSmallCardFrame0, gAirPirateSmallCardTiles, gAirPirateSmallCardPalette,
#endif
        67, 0x0, 4, 0x1d, 510, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy28Frame0, gCardEmy28Tiles, gEmy28Palette, gEnemyNameAirPirate, gAirPirateSmallCardFrame0, gAirPirateSmallCardTiles, gAirPirateSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy28Frame0, gCardEmy28Tiles, gEmy28Palette, gEnemyNameAirPirate, gAirPirateSmallCardFrame0, gAirPirateSmallCardTiles, gAirPirateSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy28Frame0, gCardEmy28Tiles, gEmy28Palette, &gEnemyNameAirPirateByLanguage, gAirPirateSmallCardFrame0, gAirPirateSmallCardTiles, gAirPirateSmallCardPalette,
#endif
        67, 0x0, 4, 0x1d, 510, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy29Frame0, gCardEmy29Tiles, gEmy29Palette, gEnemyNameDarkball, gDarkballSmallCardFrame0, gDarkballSmallCardTiles, gDarkballSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy29Frame0, gCardEmy29Tiles, gEmy29Palette, gEnemyNameDarkball, gDarkballSmallCardFrame0, gDarkballSmallCardTiles, gDarkballSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy29Frame0, gCardEmy29Tiles, gEmy29Palette, &gEnemyNameDarkballByLanguage, gDarkballSmallCardFrame0, gDarkballSmallCardTiles, gDarkballSmallCardPalette,
#endif
        68, 0x0, 2, 0x7, 513, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy29Frame0, gCardEmy29Tiles, gEmy29Palette, gEnemyNameDarkball, gDarkballSmallCardFrame0, gDarkballSmallCardTiles, gDarkballSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy29Frame0, gCardEmy29Tiles, gEmy29Palette, gEnemyNameDarkball, gDarkballSmallCardFrame0, gDarkballSmallCardTiles, gDarkballSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy29Frame0, gCardEmy29Tiles, gEmy29Palette, &gEnemyNameDarkballByLanguage, gDarkballSmallCardFrame0, gDarkballSmallCardTiles, gDarkballSmallCardPalette,
#endif
        68, 0x0, 4, 0x7, 513, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy29Frame0, gCardEmy29Tiles, gEmy29Palette, gEnemyNameDarkball, gDarkballSmallCardFrame0, gDarkballSmallCardTiles, gDarkballSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy29Frame0, gCardEmy29Tiles, gEmy29Palette, gEnemyNameDarkball, gDarkballSmallCardFrame0, gDarkballSmallCardTiles, gDarkballSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy29Frame0, gCardEmy29Tiles, gEmy29Palette, &gEnemyNameDarkballByLanguage, gDarkballSmallCardFrame0, gDarkballSmallCardTiles, gDarkballSmallCardPalette,
#endif
        68, 0x0, 6, 0x7, 513, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy44Frame0, gCardEmy44Tiles, gEmy44Palette, gEnemyNameDefender, gDefenderSmallCardFrame0, gDefenderSmallCardTiles, gDefenderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy44Frame0, gCardEmy44Tiles, gEmy44Palette, gEnemyNameDefender, gDefenderSmallCardFrame0, gDefenderSmallCardTiles, gDefenderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy44Frame0, gCardEmy44Tiles, gEmy44Palette, &gEnemyNameDefenderByLanguage, gDefenderSmallCardFrame0, gDefenderSmallCardTiles, gDefenderSmallCardPalette,
#endif
        69, 0x0, 5, 0xe, 516, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy44Frame0, gCardEmy44Tiles, gEmy44Palette, gEnemyNameDefender, gDefenderSmallCardFrame0, gDefenderSmallCardTiles, gDefenderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy44Frame0, gCardEmy44Tiles, gEmy44Palette, gEnemyNameDefender, gDefenderSmallCardFrame0, gDefenderSmallCardTiles, gDefenderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy44Frame0, gCardEmy44Tiles, gEmy44Palette, &gEnemyNameDefenderByLanguage, gDefenderSmallCardFrame0, gDefenderSmallCardTiles, gDefenderSmallCardPalette,
#endif
        69, 0x0, 1, 0xe, 516, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy44Frame0, gCardEmy44Tiles, gEmy44Palette, gEnemyNameDefender, gDefenderSmallCardFrame0, gDefenderSmallCardTiles, gDefenderSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy44Frame0, gCardEmy44Tiles, gEmy44Palette, gEnemyNameDefender, gDefenderSmallCardFrame0, gDefenderSmallCardTiles, gDefenderSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy44Frame0, gCardEmy44Tiles, gEmy44Palette, &gEnemyNameDefenderByLanguage, gDefenderSmallCardFrame0, gDefenderSmallCardTiles, gDefenderSmallCardPalette,
#endif
        69, 0x0, 9, 0xe, 516, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy30Frame0, gCardEmy30Tiles, gEmy30Palette, gEnemyNameWyvern, gWyvernSmallCardFrame0, gWyvernSmallCardTiles, gWyvernSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy30Frame0, gCardEmy30Tiles, gEmy30Palette, gEnemyNameWyvern, gWyvernSmallCardFrame0, gWyvernSmallCardTiles, gWyvernSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy30Frame0, gCardEmy30Tiles, gEmy30Palette, &gEnemyNameWyvernByLanguage, gWyvernSmallCardFrame0, gWyvernSmallCardTiles, gWyvernSmallCardPalette,
#endif
        70, 0x0, 4, 0x19, 519, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy30Frame0, gCardEmy30Tiles, gEmy30Palette, gEnemyNameWyvern, gWyvernSmallCardFrame0, gWyvernSmallCardTiles, gWyvernSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy30Frame0, gCardEmy30Tiles, gEmy30Palette, gEnemyNameWyvern, gWyvernSmallCardFrame0, gWyvernSmallCardTiles, gWyvernSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy30Frame0, gCardEmy30Tiles, gEmy30Palette, &gEnemyNameWyvernByLanguage, gWyvernSmallCardFrame0, gWyvernSmallCardTiles, gWyvernSmallCardPalette,
#endif
        70, 0x0, 5, 0x19, 519, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy30Frame0, gCardEmy30Tiles, gEmy30Palette, gEnemyNameWyvern, gWyvernSmallCardFrame0, gWyvernSmallCardTiles, gWyvernSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy30Frame0, gCardEmy30Tiles, gEmy30Palette, gEnemyNameWyvern, gWyvernSmallCardFrame0, gWyvernSmallCardTiles, gWyvernSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy30Frame0, gCardEmy30Tiles, gEmy30Palette, &gEnemyNameWyvernByLanguage, gWyvernSmallCardFrame0, gWyvernSmallCardTiles, gWyvernSmallCardPalette,
#endif
        70, 0x0, 5, 0x19, 519, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy31Frame0, gCardEmy31Tiles, gEmy31Palette, gEnemyNameWizard, gWizardSmallCardFrame0, gWizardSmallCardTiles, gWizardSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy31Frame0, gCardEmy31Tiles, gEmy31Palette, gEnemyNameWizard, gWizardSmallCardFrame0, gWizardSmallCardTiles, gWizardSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy31Frame0, gCardEmy31Tiles, gEmy31Palette, &gEnemyNameWizardByLanguage, gWizardSmallCardFrame0, gWizardSmallCardTiles, gWizardSmallCardPalette,
#endif
        71, 0x0, 3, 0x26, 522, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy31Frame0, gCardEmy31Tiles, gEmy31Palette, gEnemyNameWizard, gWizardSmallCardFrame0, gWizardSmallCardTiles, gWizardSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy31Frame0, gCardEmy31Tiles, gEmy31Palette, gEnemyNameWizard, gWizardSmallCardFrame0, gWizardSmallCardTiles, gWizardSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy31Frame0, gCardEmy31Tiles, gEmy31Palette, &gEnemyNameWizardByLanguage, gWizardSmallCardFrame0, gWizardSmallCardTiles, gWizardSmallCardPalette,
#endif
        71, 0x0, 1, 0x26, 522, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy31Frame0, gCardEmy31Tiles, gEmy31Palette, gEnemyNameWizard, gWizardSmallCardFrame0, gWizardSmallCardTiles, gWizardSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy31Frame0, gCardEmy31Tiles, gEmy31Palette, gEnemyNameWizard, gWizardSmallCardFrame0, gWizardSmallCardTiles, gWizardSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy31Frame0, gCardEmy31Tiles, gEmy31Palette, &gEnemyNameWizardByLanguage, gWizardSmallCardFrame0, gWizardSmallCardTiles, gWizardSmallCardPalette,
#endif
        71, 0x0, 7, 0x26, 522, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy37Frame0, gCardEmy37Tiles, gEmy37Palette, gEnemyNameNeoshadow, gNeoshadowSmallCardFrame0, gNeoshadowSmallCardTiles, gNeoshadowSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy37Frame0, gCardEmy37Tiles, gEmy37Palette, gEnemyNameNeoshadow, gNeoshadowSmallCardFrame0, gNeoshadowSmallCardTiles, gNeoshadowSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy37Frame0, gCardEmy37Tiles, gEmy37Palette, &gEnemyNameNeoshadowByLanguage, gNeoshadowSmallCardFrame0, gNeoshadowSmallCardTiles, gNeoshadowSmallCardPalette,
#endif
        72, 0x0, 7, 0x18, 525, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy37Frame0, gCardEmy37Tiles, gEmy37Palette, gEnemyNameNeoshadow, gNeoshadowSmallCardFrame0, gNeoshadowSmallCardTiles, gNeoshadowSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy37Frame0, gCardEmy37Tiles, gEmy37Palette, gEnemyNameNeoshadow, gNeoshadowSmallCardFrame0, gNeoshadowSmallCardTiles, gNeoshadowSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy37Frame0, gCardEmy37Tiles, gEmy37Palette, &gEnemyNameNeoshadowByLanguage, gNeoshadowSmallCardFrame0, gNeoshadowSmallCardTiles, gNeoshadowSmallCardPalette,
#endif
        72, 0x0, 2, 0x18, 525, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy37Frame0, gCardEmy37Tiles, gEmy37Palette, gEnemyNameNeoshadow, gNeoshadowSmallCardFrame0, gNeoshadowSmallCardTiles, gNeoshadowSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy37Frame0, gCardEmy37Tiles, gEmy37Palette, gEnemyNameNeoshadow, gNeoshadowSmallCardFrame0, gNeoshadowSmallCardTiles, gNeoshadowSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy37Frame0, gCardEmy37Tiles, gEmy37Palette, &gEnemyNameNeoshadowByLanguage, gNeoshadowSmallCardFrame0, gNeoshadowSmallCardTiles, gNeoshadowSmallCardPalette,
#endif
        72, 0x0, 8, 0x18, 525, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy07Frame0, gCardEmy07Tiles, gEmy07Palette, gEnemyNameWhiteMushroom, gWhiteMushroomSmallCardFrame0, gWhiteMushroomSmallCardTiles, gWhiteMushroomSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy07Frame0, gCardEmy07Tiles, gEmy07Palette, gEnemyNameWhiteMushroom, gWhiteMushroomSmallCardFrame0, gWhiteMushroomSmallCardTiles, gWhiteMushroomSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy07Frame0, gCardEmy07Tiles, gEmy07Palette, &gEnemyNameWhiteMushroomByLanguage, gWhiteMushroomSmallCardFrame0, gWhiteMushroomSmallCardTiles, gWhiteMushroomSmallCardPalette,
#endif
        73, 0x0, 2, 0x2a, 528, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy08Frame0, gCardEmy08Tiles, gEmy07bPalette, gEnemyNameBlackFungus, gBlackFungusSmallCardFrame0, gBlackFungusSmallCardTiles, gBlackFungusSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy08Frame0, gCardEmy08Tiles, gEmy07bPalette, gEnemyNameBlackFungus, gBlackFungusSmallCardFrame0, gBlackFungusSmallCardTiles, gBlackFungusSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy08Frame0, gCardEmy08Tiles, gEmy07bPalette, &gEnemyNameBlackFungusByLanguage, gBlackFungusSmallCardFrame0, gBlackFungusSmallCardTiles, gBlackFungusSmallCardPalette,
#endif
        74, 0x0, 7, 0x25, 529, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy08Frame0, gCardEmy08Tiles, gEmy07bPalette, gEnemyNameBlackFungus, gBlackFungusSmallCardFrame0, gBlackFungusSmallCardTiles, gBlackFungusSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy08Frame0, gCardEmy08Tiles, gEmy07bPalette, gEnemyNameBlackFungus, gBlackFungusSmallCardFrame0, gBlackFungusSmallCardTiles, gBlackFungusSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy08Frame0, gCardEmy08Tiles, gEmy07bPalette, &gEnemyNameBlackFungusByLanguage, gBlackFungusSmallCardFrame0, gBlackFungusSmallCardTiles, gBlackFungusSmallCardPalette,
#endif
        74, 0x0, 7, 0x25, 529, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy08Frame0, gCardEmy08Tiles, gEmy07bPalette, gEnemyNameBlackFungus, gBlackFungusSmallCardFrame0, gBlackFungusSmallCardTiles, gBlackFungusSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy08Frame0, gCardEmy08Tiles, gEmy07bPalette, gEnemyNameBlackFungus, gBlackFungusSmallCardFrame0, gBlackFungusSmallCardTiles, gBlackFungusSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy08Frame0, gCardEmy08Tiles, gEmy07bPalette, &gEnemyNameBlackFungusByLanguage, gBlackFungusSmallCardFrame0, gBlackFungusSmallCardTiles, gBlackFungusSmallCardPalette,
#endif
        74, 0x0, 7, 0x25, 529, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy83Frame0, gCardEmy83Tiles, gEmy83Palette, gEnemyNameCreeperPlant, gCreeperPlantSmallCardFrame0, gCreeperPlantSmallCardTiles, gCreeperPlantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy83Frame0, gCardEmy83Tiles, gEmy83Palette, gEnemyNameCreeperPlant, gCreeperPlantSmallCardFrame0, gCreeperPlantSmallCardTiles, gCreeperPlantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy83Frame0, gCardEmy83Tiles, gEmy83Palette, &gEnemyNameCreeperPlantByLanguage, gCreeperPlantSmallCardFrame0, gCreeperPlantSmallCardTiles, gCreeperPlantSmallCardPalette,
#endif
        75, 0x0, 2, 0x14, 532, 3, 35, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy83Frame0, gCardEmy83Tiles, gEmy83Palette, gEnemyNameCreeperPlant, gCreeperPlantSmallCardFrame0, gCreeperPlantSmallCardTiles, gCreeperPlantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy83Frame0, gCardEmy83Tiles, gEmy83Palette, gEnemyNameCreeperPlant, gCreeperPlantSmallCardFrame0, gCreeperPlantSmallCardTiles, gCreeperPlantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy83Frame0, gCardEmy83Tiles, gEmy83Palette, &gEnemyNameCreeperPlantByLanguage, gCreeperPlantSmallCardFrame0, gCreeperPlantSmallCardTiles, gCreeperPlantSmallCardPalette,
#endif
        75, 0x0, 4, 0x14, 532, 3, 35, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy83Frame0, gCardEmy83Tiles, gEmy83Palette, gEnemyNameCreeperPlant, gCreeperPlantSmallCardFrame0, gCreeperPlantSmallCardTiles, gCreeperPlantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy83Frame0, gCardEmy83Tiles, gEmy83Palette, gEnemyNameCreeperPlant, gCreeperPlantSmallCardFrame0, gCreeperPlantSmallCardTiles, gCreeperPlantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy83Frame0, gCardEmy83Tiles, gEmy83Palette, &gEnemyNameCreeperPlantByLanguage, gCreeperPlantSmallCardFrame0, gCreeperPlantSmallCardTiles, gCreeperPlantSmallCardPalette,
#endif
        75, 0x0, 6, 0x14, 532, 3, 35, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy81Frame0, gCardEmy81Tiles, gEmy81Palette, gEnemyNameTornadoStep, gTornadoStepSmallCardFrame0, gTornadoStepSmallCardTiles, gTornadoStepSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy81Frame0, gCardEmy81Tiles, gEmy81Palette, gEnemyNameTornadoStep, gTornadoStepSmallCardFrame0, gTornadoStepSmallCardTiles, gTornadoStepSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy81Frame0, gCardEmy81Tiles, gEmy81Palette, &gEnemyNameTornadoStepByLanguage, gTornadoStepSmallCardFrame0, gTornadoStepSmallCardTiles, gTornadoStepSmallCardPalette,
#endif
        76, 0x0, 2, 0xa, 535, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy81Frame0, gCardEmy81Tiles, gEmy81Palette, gEnemyNameTornadoStep, gTornadoStepSmallCardFrame0, gTornadoStepSmallCardTiles, gTornadoStepSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy81Frame0, gCardEmy81Tiles, gEmy81Palette, gEnemyNameTornadoStep, gTornadoStepSmallCardFrame0, gTornadoStepSmallCardTiles, gTornadoStepSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy81Frame0, gCardEmy81Tiles, gEmy81Palette, &gEnemyNameTornadoStepByLanguage, gTornadoStepSmallCardFrame0, gTornadoStepSmallCardTiles, gTornadoStepSmallCardPalette,
#endif
        76, 0x0, 4, 0xa, 535, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy81Frame0, gCardEmy81Tiles, gEmy81Palette, gEnemyNameTornadoStep, gTornadoStepSmallCardFrame0, gTornadoStepSmallCardTiles, gTornadoStepSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy81Frame0, gCardEmy81Tiles, gEmy81Palette, gEnemyNameTornadoStep, gTornadoStepSmallCardFrame0, gTornadoStepSmallCardTiles, gTornadoStepSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy81Frame0, gCardEmy81Tiles, gEmy81Palette, &gEnemyNameTornadoStepByLanguage, gTornadoStepSmallCardFrame0, gTornadoStepSmallCardTiles, gTornadoStepSmallCardPalette,
#endif
        76, 0x0, 6, 0xa, 535, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy82Frame0, gCardEmy82Tiles, gEmy82Palette, gEnemyNameCrescendo, gCrescendoSmallCardFrame0, gCrescendoSmallCardTiles, gCrescendoSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy82Frame0, gCardEmy82Tiles, gEmy82Palette, gEnemyNameCrescendo, gCrescendoSmallCardFrame0, gCrescendoSmallCardTiles, gCrescendoSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy82Frame0, gCardEmy82Tiles, gEmy82Palette, &gEnemyNameCrescendoByLanguage, gCrescendoSmallCardFrame0, gCrescendoSmallCardTiles, gCrescendoSmallCardPalette,
#endif
        77, 0x0, 2, 0x27, 538, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy82Frame0, gCardEmy82Tiles, gEmy82Palette, gEnemyNameCrescendo, gCrescendoSmallCardFrame0, gCrescendoSmallCardTiles, gCrescendoSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy82Frame0, gCardEmy82Tiles, gEmy82Palette, gEnemyNameCrescendo, gCrescendoSmallCardFrame0, gCrescendoSmallCardTiles, gCrescendoSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy82Frame0, gCardEmy82Tiles, gEmy82Palette, &gEnemyNameCrescendoByLanguage, gCrescendoSmallCardFrame0, gCrescendoSmallCardTiles, gCrescendoSmallCardPalette,
#endif
        77, 0x0, 4, 0x27, 538, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardEmy82Frame0, gCardEmy82Tiles, gEmy82Palette, gEnemyNameCrescendo, gCrescendoSmallCardFrame0, gCrescendoSmallCardTiles, gCrescendoSmallCardPalette,
#elif defined(VERSION_JP)
        gCardEmy82Frame0, gCardEmy82Tiles, gEmy82Palette, gEnemyNameCrescendo, gCrescendoSmallCardFrame0, gCrescendoSmallCardTiles, gCrescendoSmallCardPalette,
#elif defined(VERSION_EU)
        gCardEmy82Frame0, gCardEmy82Tiles, gEmy82Palette, &gEnemyNameCrescendoByLanguage, gCrescendoSmallCardFrame0, gCrescendoSmallCardTiles, gCrescendoSmallCardPalette,
#endif
        77, 0x0, 6, 0x27, 538, 3, 20, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gEnemyNameGuardArmor, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gEnemyNameGuardArmor, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, &gEnemyNameGuardArmorByLanguage, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#endif
        78, 0x0, 1, 0x22, 575, 3, 30, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gEnemyNameParasiteCage, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gEnemyNameParasiteCage, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, &gEnemyNameParasiteCageByLanguage, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#endif
        79, 0x0, 1, 0x29, 605, 3, 60, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gEnemyNameTrickmaster, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gEnemyNameTrickmaster, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, &gEnemyNameTrickmasterByLanguage, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#endif
        80, 0x0, 1, 0x30, 595, 3, 25, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gEnemyNameDarkside, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gEnemyNameDarkside, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, &gEnemyNameDarksideByLanguage, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#endif
        81, 0x0, 1, 0x2d, 565, 3, 99, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardNpcAw04Frame0, gCardNpcAw04Tiles, gTrumpHPalette, gEnemyNameCardSoldier, gCardSoldierHeartSmallCardFrame0, gCardSoldierHeartSmallCardTiles, gCardSoldierHeartSmallCardPalette,
#elif defined(VERSION_JP)
        gCardNpcAw04Frame0, gCardNpcAw04Tiles, gTrumpHPalette, gEnemyNameCardSoldier, gCardSoldierHeartSmallCardFrame0, gCardSoldierHeartSmallCardTiles, gCardSoldierHeartSmallCardPalette,
#elif defined(VERSION_EU)
        gCardNpcAw04Frame0, gCardNpcAw04Tiles, gTrumpHPalette, &gEnemyNameCardSoldierByLanguage, gCardSoldierHeartSmallCardFrame0, gCardSoldierHeartSmallCardTiles, gCardSoldierHeartSmallCardPalette,
#endif
        82, 0x0, 2, 0x2c, 545, 3, 55, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardNpcAw04Frame0, gCardNpcAw04Tiles, gTrumpHPalette, gEnemyNameCardSoldier, gCardSoldierHeartSmallCardFrame0, gCardSoldierHeartSmallCardTiles, gCardSoldierHeartSmallCardPalette,
#elif defined(VERSION_JP)
        gCardNpcAw04Frame0, gCardNpcAw04Tiles, gTrumpHPalette, gEnemyNameCardSoldier, gCardSoldierHeartSmallCardFrame0, gCardSoldierHeartSmallCardTiles, gCardSoldierHeartSmallCardPalette,
#elif defined(VERSION_EU)
        gCardNpcAw04Frame0, gCardNpcAw04Tiles, gTrumpHPalette, &gEnemyNameCardSoldierByLanguage, gCardSoldierHeartSmallCardFrame0, gCardSoldierHeartSmallCardTiles, gCardSoldierHeartSmallCardPalette,
#endif
        82, 0x0, 3, 0x2c, 545, 3, 55, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardNpcAw04Frame0, gCardNpcAw04Tiles, gTrumpHPalette, gEnemyNameCardSoldier, gCardSoldierHeartSmallCardFrame0, gCardSoldierHeartSmallCardTiles, gCardSoldierHeartSmallCardPalette,
#elif defined(VERSION_JP)
        gCardNpcAw04Frame0, gCardNpcAw04Tiles, gTrumpHPalette, gEnemyNameCardSoldier, gCardSoldierHeartSmallCardFrame0, gCardSoldierHeartSmallCardTiles, gCardSoldierHeartSmallCardPalette,
#elif defined(VERSION_EU)
        gCardNpcAw04Frame0, gCardNpcAw04Tiles, gTrumpHPalette, &gEnemyNameCardSoldierByLanguage, gCardSoldierHeartSmallCardFrame0, gCardSoldierHeartSmallCardTiles, gCardSoldierHeartSmallCardPalette,
#endif
        82, 0x0, 3, 0x2c, 545, 3, 55, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardNpcAw03Frame0, gCardNpcAw03Tiles, gTrumpSPalette, gEnemyNameCardSoldier, gCardSoldierSpadeSmallCardFrame0, gCardSoldierSpadeSmallCardTiles, gCardSoldierSpadeSmallCardPalette,
#elif defined(VERSION_JP)
        gCardNpcAw03Frame0, gCardNpcAw03Tiles, gTrumpSPalette, gEnemyNameCardSoldier, gCardSoldierSpadeSmallCardFrame0, gCardSoldierSpadeSmallCardTiles, gCardSoldierSpadeSmallCardPalette,
#elif defined(VERSION_EU)
        gCardNpcAw03Frame0, gCardNpcAw03Tiles, gTrumpSPalette, &gEnemyNameCardSoldierByLanguage, gCardSoldierSpadeSmallCardFrame0, gCardSoldierSpadeSmallCardTiles, gCardSoldierSpadeSmallCardPalette,
#endif
        83, 0x0, 1, 0x2c, 548, 3, 55, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardNpcAw03Frame0, gCardNpcAw03Tiles, gTrumpSPalette, gEnemyNameCardSoldier, gCardSoldierSpadeSmallCardFrame0, gCardSoldierSpadeSmallCardTiles, gCardSoldierSpadeSmallCardPalette,
#elif defined(VERSION_JP)
        gCardNpcAw03Frame0, gCardNpcAw03Tiles, gTrumpSPalette, gEnemyNameCardSoldier, gCardSoldierSpadeSmallCardFrame0, gCardSoldierSpadeSmallCardTiles, gCardSoldierSpadeSmallCardPalette,
#elif defined(VERSION_EU)
        gCardNpcAw03Frame0, gCardNpcAw03Tiles, gTrumpSPalette, &gEnemyNameCardSoldierByLanguage, gCardSoldierSpadeSmallCardFrame0, gCardSoldierSpadeSmallCardTiles, gCardSoldierSpadeSmallCardPalette,
#endif
        83, 0x0, 4, 0x2c, 548, 3, 55, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardNpcAw03Frame0, gCardNpcAw03Tiles, gTrumpSPalette, gEnemyNameCardSoldier, gCardSoldierSpadeSmallCardFrame0, gCardSoldierSpadeSmallCardTiles, gCardSoldierSpadeSmallCardPalette,
#elif defined(VERSION_JP)
        gCardNpcAw03Frame0, gCardNpcAw03Tiles, gTrumpSPalette, gEnemyNameCardSoldier, gCardSoldierSpadeSmallCardFrame0, gCardSoldierSpadeSmallCardTiles, gCardSoldierSpadeSmallCardPalette,
#elif defined(VERSION_EU)
        gCardNpcAw03Frame0, gCardNpcAw03Tiles, gTrumpSPalette, &gEnemyNameCardSoldierByLanguage, gCardSoldierSpadeSmallCardFrame0, gCardSoldierSpadeSmallCardTiles, gCardSoldierSpadeSmallCardPalette,
#endif
        83, 0x0, 4, 0x2c, 548, 3, 55, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11Palette, gEnemyNameHades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11Palette, gEnemyNameHades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11Palette, &gEnemyNameHadesByLanguage, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesSmallCardPalette,
#endif
        84, 0x0, 9, 0x8, 551, 3, 40, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gEnemyNameJafar, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gEnemyNameJafar, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, &gEnemyNameJafarByLanguage, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#endif
        85, 0x0, 1, 0x2, 615, 3, 65, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gEnemyNameOogieBoogie, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gEnemyNameOogieBoogie, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, &gEnemyNameOogieBoogieByLanguage, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#endif
        86, 0x0, 1, 0x17, 585, 3, 40, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gEnemyNameUrsula, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gEnemyNameUrsula, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, &gEnemyNameUrsulaByLanguage, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#endif
        87, 0x0, 1, 0x2e, 625, 3, 50, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10Palette, gEnemyNameHook, gHookSmallCardFrame0, gHookSmallCardTiles, gHookSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10Palette, gEnemyNameHook, gHookSmallCardFrame0, gHookSmallCardTiles, gHookSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10Palette, &gEnemyNameHookByLanguage, gHookSmallCardFrame0, gHookSmallCardTiles, gHookSmallCardPalette,
#endif
        88, 0x0, 9, 0x1a, 555, 3, 35, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gEnemyNameDragonMaleficent, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gEnemyNameDragonMaleficent, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, &gEnemyNameDragonMaleficentByLanguage, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#endif
        89, 0x0, 1, 0x2b, 635, 3, 70, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12Palette, gEnemyNameRiku, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12Palette, gEnemyNameRiku, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12Palette, &gEnemyNameRikuByLanguage, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuSmallCardPalette,
#endif
        90, 0x0, 9, 0xf, 557, 3, 80, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13Palette, gEnemyNameAxel, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13Palette, gEnemyNameAxel, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13Palette, &gEnemyNameAxelByLanguage, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelSmallCardPalette,
#endif
        91, 0x0, 9, 0x12, 558, 3, 75, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14Palette, gEnemyNameLarxene, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14Palette, gEnemyNameLarxene, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14Palette, &gEnemyNameLarxeneByLanguage, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneSmallCardPalette,
#endif
        92, 0x0, 9, 0x32, 559, 3, 60, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15Palette, gEnemyNameVexen, gVexenSmallCardFrame0, gVexenSmallCardTiles, gVexenSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15Palette, gEnemyNameVexen, gVexenSmallCardFrame0, gVexenSmallCardTiles, gVexenSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15Palette, &gEnemyNameVexenByLanguage, gVexenSmallCardFrame0, gVexenSmallCardTiles, gVexenSmallCardPalette,
#endif
        93, 0x0, 9, 0x1b, 560, 3, 60, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16Palette, gEnemyNameMarluxia, gMarluxiaSmallCardFrame0, gMarluxiaSmallCardTiles, gMarluxiaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16Palette, gEnemyNameMarluxia, gMarluxiaSmallCardFrame0, gMarluxiaSmallCardTiles, gMarluxiaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16Palette, &gEnemyNameMarluxiaByLanguage, gMarluxiaSmallCardFrame0, gMarluxiaSmallCardTiles, gMarluxiaSmallCardPalette,
#endif
        94, 0x0, 9, 0x2f, 561, 3, 99, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gEnemyNameMarluxia, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gEnemyNameMarluxia, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, &gEnemyNameMarluxiaByLanguage, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#endif
        95, 0x0, 1, 0x2b, 645, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17Palette, gEnemyNameLexaeus, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17Palette, gEnemyNameLexaeus, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17Palette, &gEnemyNameLexaeusByLanguage, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusSmallCardPalette,
#endif
        96, 0x0, 9, 0x31, 563, 3, 99, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18Palette, gEnemyNameAnsem, gAnsemSmallCardFrame0, gAnsemSmallCardTiles, gAnsemSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18Palette, gEnemyNameAnsem, gAnsemSmallCardFrame0, gAnsemSmallCardTiles, gAnsemSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18Palette, &gEnemyNameAnsemByLanguage, gAnsemSmallCardFrame0, gAnsemSmallCardTiles, gAnsemSmallCardPalette,
#endif
        97, 0x0, 9, 0x1c, 564, 3, 60, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, &gCharacterNameCardOfSpadesByLanguage, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#endif
        81, 0x0, 0, 0x0, 565, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, &gCharacterNameCardOfSpadesByLanguage, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#endif
        81, 0x0, 1, 0x0, 565, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, &gCharacterNameCardOfSpadesByLanguage, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#endif
        81, 0x0, 2, 0x0, 565, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, &gCharacterNameCardOfSpadesByLanguage, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#endif
        81, 0x0, 3, 0x0, 565, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, &gCharacterNameCardOfSpadesByLanguage, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#endif
        81, 0x0, 4, 0x0, 565, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, &gCharacterNameCardOfSpadesByLanguage, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#endif
        81, 0x0, 5, 0x0, 565, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, &gCharacterNameCardOfSpadesByLanguage, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#endif
        81, 0x0, 6, 0x0, 565, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, &gCharacterNameCardOfSpadesByLanguage, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#endif
        81, 0x0, 7, 0x0, 565, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, &gCharacterNameCardOfSpadesByLanguage, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#endif
        81, 0x0, 8, 0x0, 565, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, gCharacterNameCardOfSpades, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos00Frame0, gCardBos00Tiles, gBoss00ObjPalette, &gCharacterNameCardOfSpadesByLanguage, gDarksideSmallCardFrame0, gDarksideSmallCardTiles, gDarksideSmallCardPalette,
#endif
        81, 0x0, 9, 0x0, 565, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, &gCharacterNameCardOfSpadesByLanguage, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#endif
        78, 0x0, 0, 0x0, 575, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, &gCharacterNameCardOfSpadesByLanguage, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#endif
        78, 0x0, 1, 0x0, 575, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, &gCharacterNameCardOfSpadesByLanguage, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#endif
        78, 0x0, 2, 0x0, 575, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, &gCharacterNameCardOfSpadesByLanguage, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#endif
        78, 0x0, 3, 0x0, 575, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, &gCharacterNameCardOfSpadesByLanguage, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#endif
        78, 0x0, 4, 0x0, 575, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, &gCharacterNameCardOfSpadesByLanguage, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#endif
        78, 0x0, 5, 0x0, 575, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, &gCharacterNameCardOfSpadesByLanguage, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#endif
        78, 0x0, 6, 0x0, 575, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, &gCharacterNameCardOfSpadesByLanguage, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#endif
        78, 0x0, 7, 0x0, 575, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, &gCharacterNameCardOfSpadesByLanguage, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#endif
        78, 0x0, 8, 0x0, 575, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, gCharacterNameCardOfSpades, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos01Frame0, gCardBos01Tiles, gBoss01objPalette, &gCharacterNameCardOfSpadesByLanguage, gGuardArmorSmallCardFrame0, gGuardArmorSmallCardTiles, gGuardArmorSmallCardPalette,
#endif
        78, 0x0, 9, 0x0, 575, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, &gCharacterNameCardOfSpadesByLanguage, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#endif
        86, 0x0, 0, 0x0, 585, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, &gCharacterNameCardOfSpadesByLanguage, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#endif
        86, 0x0, 1, 0x0, 585, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, &gCharacterNameCardOfSpadesByLanguage, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#endif
        86, 0x0, 2, 0x0, 585, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, &gCharacterNameCardOfSpadesByLanguage, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#endif
        86, 0x0, 3, 0x0, 585, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, &gCharacterNameCardOfSpadesByLanguage, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#endif
        86, 0x0, 4, 0x0, 585, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, &gCharacterNameCardOfSpadesByLanguage, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#endif
        86, 0x0, 5, 0x0, 585, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, &gCharacterNameCardOfSpadesByLanguage, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#endif
        86, 0x0, 6, 0x0, 585, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, &gCharacterNameCardOfSpadesByLanguage, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#endif
        86, 0x0, 7, 0x0, 585, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, &gCharacterNameCardOfSpadesByLanguage, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#endif
        86, 0x0, 8, 0x0, 585, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, gCharacterNameCardOfSpades, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos02Frame0, gCardBos02Tiles, gBoss02objPalette, &gCharacterNameCardOfSpadesByLanguage, gOogieBoogieSmallCardFrame0, gOogieBoogieSmallCardTiles, gOogieBoogieSmallCardPalette,
#endif
        86, 0x0, 9, 0x0, 585, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, &gCharacterNameCardOfSpadesByLanguage, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#endif
        80, 0x0, 0, 0x0, 595, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, &gCharacterNameCardOfSpadesByLanguage, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#endif
        80, 0x0, 1, 0x0, 595, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, &gCharacterNameCardOfSpadesByLanguage, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#endif
        80, 0x0, 2, 0x0, 595, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, &gCharacterNameCardOfSpadesByLanguage, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#endif
        80, 0x0, 3, 0x0, 595, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, &gCharacterNameCardOfSpadesByLanguage, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#endif
        80, 0x0, 4, 0x0, 595, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, &gCharacterNameCardOfSpadesByLanguage, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#endif
        80, 0x0, 5, 0x0, 595, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, &gCharacterNameCardOfSpadesByLanguage, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#endif
        80, 0x0, 6, 0x0, 595, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, &gCharacterNameCardOfSpadesByLanguage, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#endif
        80, 0x0, 7, 0x0, 595, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, &gCharacterNameCardOfSpadesByLanguage, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#endif
        80, 0x0, 8, 0x0, 595, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, gCharacterNameCardOfSpades, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos03Frame0, gCardBos03Tiles, gBoss03objPalette, &gCharacterNameCardOfSpadesByLanguage, gTrickmasterSmallCardFrame0, gTrickmasterSmallCardTiles, gTrickmasterSmallCardPalette,
#endif
        80, 0x0, 9, 0x0, 595, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, &gCharacterNameCardOfSpadesByLanguage, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#endif
        79, 0x0, 0, 0x0, 605, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, &gCharacterNameCardOfSpadesByLanguage, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#endif
        79, 0x0, 1, 0x0, 605, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, &gCharacterNameCardOfSpadesByLanguage, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#endif
        79, 0x0, 2, 0x0, 605, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, &gCharacterNameCardOfSpadesByLanguage, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#endif
        79, 0x0, 3, 0x0, 605, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, &gCharacterNameCardOfSpadesByLanguage, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#endif
        79, 0x0, 4, 0x0, 605, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, &gCharacterNameCardOfSpadesByLanguage, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#endif
        79, 0x0, 5, 0x0, 605, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, &gCharacterNameCardOfSpadesByLanguage, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#endif
        79, 0x0, 6, 0x0, 605, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, &gCharacterNameCardOfSpadesByLanguage, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#endif
        79, 0x0, 7, 0x0, 605, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, &gCharacterNameCardOfSpadesByLanguage, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#endif
        79, 0x0, 8, 0x0, 605, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, gCharacterNameCardOfSpades, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos04Frame0, gCardBos04Tiles, gBosPcBgPalette, &gCharacterNameCardOfSpadesByLanguage, gParasiteCageSmallCardFrame0, gParasiteCageSmallCardTiles, gParasiteCageSmallCardPalette,
#endif
        79, 0x0, 9, 0x0, 605, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, &gCharacterNameCardOfSpadesByLanguage, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#endif
        85, 0x0, 0, 0x0, 615, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, &gCharacterNameCardOfSpadesByLanguage, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#endif
        85, 0x0, 1, 0x0, 615, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, &gCharacterNameCardOfSpadesByLanguage, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#endif
        85, 0x0, 2, 0x0, 615, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, &gCharacterNameCardOfSpadesByLanguage, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#endif
        85, 0x0, 3, 0x0, 615, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, &gCharacterNameCardOfSpadesByLanguage, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#endif
        85, 0x0, 4, 0x0, 615, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, &gCharacterNameCardOfSpadesByLanguage, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#endif
        85, 0x0, 5, 0x0, 615, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, &gCharacterNameCardOfSpadesByLanguage, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#endif
        85, 0x0, 6, 0x0, 615, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, &gCharacterNameCardOfSpadesByLanguage, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#endif
        85, 0x0, 7, 0x0, 615, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, &gCharacterNameCardOfSpadesByLanguage, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#endif
        85, 0x0, 8, 0x0, 615, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, gCharacterNameCardOfSpades, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos05Frame0, gCardBos05Tiles, gCardBos05Palette, &gCharacterNameCardOfSpadesByLanguage, gJafarSmallCardFrame0, gJafarSmallCardTiles, gJafarSmallCardPalette,
#endif
        85, 0x0, 9, 0x0, 615, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, &gCharacterNameCardOfSpadesByLanguage, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#endif
        87, 0x0, 0, 0x0, 625, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, &gCharacterNameCardOfSpadesByLanguage, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#endif
        87, 0x0, 1, 0x0, 625, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, &gCharacterNameCardOfSpadesByLanguage, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#endif
        87, 0x0, 2, 0x0, 625, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, &gCharacterNameCardOfSpadesByLanguage, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#endif
        87, 0x0, 3, 0x0, 625, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, &gCharacterNameCardOfSpadesByLanguage, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#endif
        87, 0x0, 4, 0x0, 625, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, &gCharacterNameCardOfSpadesByLanguage, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#endif
        87, 0x0, 5, 0x0, 625, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, &gCharacterNameCardOfSpadesByLanguage, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#endif
        87, 0x0, 6, 0x0, 625, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, &gCharacterNameCardOfSpadesByLanguage, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#endif
        87, 0x0, 7, 0x0, 625, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, &gCharacterNameCardOfSpadesByLanguage, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#endif
        87, 0x0, 8, 0x0, 625, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, gCharacterNameCardOfSpades, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos06Frame0, gCardBos06Tiles, gCardBos06Palette, &gCharacterNameCardOfSpadesByLanguage, gUrsulaSmallCardFrame0, gUrsulaSmallCardTiles, gUrsulaSmallCardPalette,
#endif
        87, 0x0, 9, 0x0, 625, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, &gCharacterNameCardOfSpadesByLanguage, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#endif
        89, 0x0, 0, 0x0, 635, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, &gCharacterNameCardOfSpadesByLanguage, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#endif
        89, 0x0, 1, 0x0, 635, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, &gCharacterNameCardOfSpadesByLanguage, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#endif
        89, 0x0, 2, 0x0, 635, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, &gCharacterNameCardOfSpadesByLanguage, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#endif
        89, 0x0, 3, 0x0, 635, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, &gCharacterNameCardOfSpadesByLanguage, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#endif
        89, 0x0, 4, 0x0, 635, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, &gCharacterNameCardOfSpadesByLanguage, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#endif
        89, 0x0, 5, 0x0, 635, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, &gCharacterNameCardOfSpadesByLanguage, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#endif
        89, 0x0, 6, 0x0, 635, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, &gCharacterNameCardOfSpadesByLanguage, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#endif
        89, 0x0, 7, 0x0, 635, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, &gCharacterNameCardOfSpadesByLanguage, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#endif
        89, 0x0, 8, 0x0, 635, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, gCharacterNameCardOfSpades, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos07Frame0, gCardBos07Tiles, gCardBos07Palette, &gCharacterNameCardOfSpadesByLanguage, gDragonMaleficentSmallCardFrame0, gDragonMaleficentSmallCardTiles, gDragonMaleficentSmallCardPalette,
#endif
        89, 0x0, 9, 0x0, 635, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, &gCharacterNameCardOfSpadesByLanguage, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#endif
        95, 0x0, 0, 0x0, 645, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, &gCharacterNameCardOfSpadesByLanguage, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#endif
        95, 0x0, 1, 0x0, 645, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, &gCharacterNameCardOfSpadesByLanguage, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#endif
        95, 0x0, 2, 0x0, 645, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, &gCharacterNameCardOfSpadesByLanguage, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#endif
        95, 0x0, 3, 0x0, 645, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, &gCharacterNameCardOfSpadesByLanguage, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#endif
        95, 0x0, 4, 0x0, 645, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, &gCharacterNameCardOfSpadesByLanguage, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#endif
        95, 0x0, 5, 0x0, 645, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, &gCharacterNameCardOfSpadesByLanguage, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#endif
        95, 0x0, 6, 0x0, 645, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, &gCharacterNameCardOfSpadesByLanguage, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#endif
        95, 0x0, 7, 0x0, 645, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, &gCharacterNameCardOfSpadesByLanguage, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#endif
        95, 0x0, 8, 0x0, 645, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, gCharacterNameCardOfSpades, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos08Frame0, gCardBos08Tiles, gCardBos08Palette, &gCharacterNameCardOfSpadesByLanguage, gMarluxia2SmallCardFrame0, gMarluxia2SmallCardTiles, gMarluxia2SmallCardPalette,
#endif
        95, 0x0, 9, 0x0, 645, 3, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gGimmickCardFrame0, gGimmickCardTiles, gGimmickCardPalette, gCharacterNameCardOfSpades, NULL, NULL, NULL,
#elif defined(VERSION_JP)
        gGimmickCardFrame0, gGimmickCardTiles, gGimmickCardPalette, gCharacterNameCardOfSpades, NULL, NULL, NULL,
#elif defined(VERSION_EU)
        gGimmickCardFrame0, gGimmickCardTiles, gGimmickCardPalette, &gCharacterNameCardOfSpadesByLanguage, NULL, NULL, NULL,
#endif
        98, CARD_DEF_FLAG_GIMMICK, 0, 0x8c, 655, 2, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gGimmickCardFrame0, gGimmickCardTiles, gGimmickCardPalette, gCharacterNameCardOfSpades, NULL, NULL, NULL,
#elif defined(VERSION_JP)
        gGimmickCardFrame0, gGimmickCardTiles, gGimmickCardPalette, gCharacterNameCardOfSpades, NULL, NULL, NULL,
#elif defined(VERSION_EU)
        gGimmickCardFrame0, gGimmickCardTiles, gGimmickCardPalette, &gCharacterNameCardOfSpadesByLanguage, NULL, NULL, NULL,
#endif
        99, CARD_DEF_FLAG_GIMMICK, 0, 0x8d, 656, 2, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gGimmickCardFrame0, gGimmickCardTiles, gGimmickCardPalette, gCharacterNameCardOfSpades, NULL, NULL, NULL,
#elif defined(VERSION_JP)
        gGimmickCardFrame0, gGimmickCardTiles, gGimmickCardPalette, gCharacterNameCardOfSpades, NULL, NULL, NULL,
#elif defined(VERSION_EU)
        gGimmickCardFrame0, gGimmickCardTiles, gGimmickCardPalette, &gCharacterNameCardOfSpadesByLanguage, NULL, NULL, NULL,
#endif
        100, CARD_DEF_FLAG_GIMMICK, 0, 0x8e, 657, 2, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gGimmickCardFrame0, gGimmickCardTiles, gGimmickCardPalette, gCharacterNameCardOfSpades, NULL, NULL, NULL,
#elif defined(VERSION_JP)
        gGimmickCardFrame0, gGimmickCardTiles, gGimmickCardPalette, gCharacterNameCardOfSpades, NULL, NULL, NULL,
#elif defined(VERSION_EU)
        gGimmickCardFrame0, gGimmickCardTiles, gGimmickCardPalette, &gCharacterNameCardOfSpadesByLanguage, NULL, NULL, NULL,
#endif
        101, CARD_DEF_FLAG_GIMMICK, 0, 0x8f, 658, 2, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gGimmickCardFrame0, gGimmickCardTiles, gGimmickCardPalette, gCharacterNameCardOfSpades, NULL, NULL, NULL,
#elif defined(VERSION_JP)
        gGimmickCardFrame0, gGimmickCardTiles, gGimmickCardPalette, gCharacterNameCardOfSpades, NULL, NULL, NULL,
#elif defined(VERSION_EU)
        gGimmickCardFrame0, gGimmickCardTiles, gGimmickCardPalette, &gCharacterNameCardOfSpadesByLanguage, NULL, NULL, NULL,
#endif
        102, CARD_DEF_FLAG_GIMMICK, 0, 0x90, 659, 2, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, &gCardNameSoulEaterByLanguage, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#endif
        17, 0x0, 0, 0x12, 661, 0, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, &gCardNameSoulEaterByLanguage, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#endif
        17, 0x0, 1, 0x12, 661, 0, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, &gCardNameSoulEaterByLanguage, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#endif
        17, 0x0, 2, 0x12, 661, 0, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, &gCardNameSoulEaterByLanguage, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#endif
        17, 0x0, 3, 0x12, 661, 0, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, &gCardNameSoulEaterByLanguage, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#endif
        17, 0x0, 4, 0x12, 661, 0, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, &gCardNameSoulEaterByLanguage, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#endif
        17, 0x0, 5, 0x12, 661, 0, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, &gCardNameSoulEaterByLanguage, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#endif
        17, 0x0, 6, 0x12, 661, 0, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, &gCardNameSoulEaterByLanguage, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#endif
        17, 0x0, 7, 0x12, 661, 0, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, &gCardNameSoulEaterByLanguage, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#endif
        17, 0x0, 8, 0x12, 661, 0, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_JP)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, gCardNameSoulEater, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#elif defined(VERSION_EU)
        gCardWep20Frame0, gCardWep20Tiles, gCardWep20Palette, &gCardNameSoulEaterByLanguage, gSoulEaterSmallCardFrame0, gSoulEaterSmallCardTiles, gSoulEaterSmallCardPalette,
#endif
        17, 0x0, 9, 0x12, 661, 0, 0, {5, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, &gCardNameKingByLanguage, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#endif
        46, CARD_DEF_FLAG_FRIEND, 0, 0x2d, 671, 2, 0, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, &gCardNameKingByLanguage, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#endif
        46, CARD_DEF_FLAG_FRIEND, 1, 0x2d, 671, 2, 0, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, &gCardNameKingByLanguage, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#endif
        46, CARD_DEF_FLAG_FRIEND, 2, 0x2d, 671, 2, 0, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, &gCardNameKingByLanguage, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#endif
        46, CARD_DEF_FLAG_FRIEND, 3, 0x2d, 671, 2, 0, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, &gCardNameKingByLanguage, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#endif
        46, CARD_DEF_FLAG_FRIEND, 4, 0x2d, 671, 2, 0, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, &gCardNameKingByLanguage, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#endif
        46, CARD_DEF_FLAG_FRIEND, 5, 0x2d, 671, 2, 0, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, &gCardNameKingByLanguage, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#endif
        46, CARD_DEF_FLAG_FRIEND, 6, 0x2d, 671, 2, 0, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, &gCardNameKingByLanguage, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#endif
        46, CARD_DEF_FLAG_FRIEND, 7, 0x2d, 671, 2, 0, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, &gCardNameKingByLanguage, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#endif
        46, CARD_DEF_FLAG_FRIEND, 8, 0x2d, 671, 2, 0, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, gCardNameKing, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn15Frame0, gCardSmn15Tiles, gMickeyPalette, &gCardNameKingByLanguage, gTheKingSmallCardFrame0, gTheKingSmallCardTiles, gTheKingSmallCardPalette,
#endif
        46, CARD_DEF_FLAG_FRIEND, 9, 0x2d, 671, 2, 0, {3, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#endif
        131, 0x0, 0, 0x24, 681, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#endif
        131, 0x0, 1, 0x24, 681, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#endif
        131, 0x0, 2, 0x24, 681, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#endif
        131, 0x0, 3, 0x24, 681, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#endif
        131, 0x0, 4, 0x24, 681, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#endif
        131, 0x0, 5, 0x24, 681, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#endif
        131, 0x0, 6, 0x24, 681, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#endif
        131, 0x0, 7, 0x24, 681, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#endif
        131, 0x0, 8, 0x24, 681, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09aPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudASmallCardPalette,
#endif
        131, 0x0, 9, 0x24, 681, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#endif
        132, 0x0, 0, 0x25, 691, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#endif
        132, 0x0, 1, 0x25, 691, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#endif
        132, 0x0, 2, 0x25, 691, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#endif
        132, 0x0, 3, 0x25, 691, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#endif
        132, 0x0, 4, 0x25, 691, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#endif
        132, 0x0, 5, 0x25, 691, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#endif
        132, 0x0, 6, 0x25, 691, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#endif
        132, 0x0, 7, 0x25, 691, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#endif
        132, 0x0, 8, 0x25, 691, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, gCharacterNameCardOfSpades, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardSmn09Frame0, gCardSmn09Tiles, gCardSmn09bPalette, &gCharacterNameCardOfSpadesByLanguage, gCloudSmallCardFrame0, gCloudSmallCardTiles, gCloudBSmallCardPalette,
#endif
        132, 0x0, 9, 0x25, 691, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, &gCharacterNameCardOfSpadesByLanguage, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#endif
        103, 0x0, 0, 0x24, 701, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, &gCharacterNameCardOfSpadesByLanguage, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#endif
        103, 0x0, 1, 0x24, 701, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, &gCharacterNameCardOfSpadesByLanguage, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#endif
        103, 0x0, 2, 0x24, 701, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, &gCharacterNameCardOfSpadesByLanguage, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#endif
        103, 0x0, 3, 0x24, 701, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, &gCharacterNameCardOfSpadesByLanguage, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#endif
        103, 0x0, 4, 0x24, 701, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, &gCharacterNameCardOfSpadesByLanguage, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#endif
        103, 0x0, 5, 0x24, 701, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, &gCharacterNameCardOfSpadesByLanguage, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#endif
        103, 0x0, 6, 0x24, 701, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, &gCharacterNameCardOfSpadesByLanguage, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#endif
        103, 0x0, 7, 0x24, 701, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, &gCharacterNameCardOfSpadesByLanguage, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#endif
        103, 0x0, 8, 0x24, 701, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, gCharacterNameCardOfSpades, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10aPalette, &gCharacterNameCardOfSpadesByLanguage, gHookASmallCardFrame0, gHookASmallCardTiles, gHookVariantSmallCardPalette,
#endif
        103, 0x0, 9, 0x24, 701, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, &gCharacterNameCardOfSpadesByLanguage, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        104, 0x0, 0, 0x25, 711, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, &gCharacterNameCardOfSpadesByLanguage, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        104, 0x0, 1, 0x25, 711, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, &gCharacterNameCardOfSpadesByLanguage, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        104, 0x0, 2, 0x25, 711, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, &gCharacterNameCardOfSpadesByLanguage, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        104, 0x0, 3, 0x25, 711, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, &gCharacterNameCardOfSpadesByLanguage, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        104, 0x0, 4, 0x25, 711, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, &gCharacterNameCardOfSpadesByLanguage, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        104, 0x0, 5, 0x25, 711, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, &gCharacterNameCardOfSpadesByLanguage, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        104, 0x0, 6, 0x25, 711, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, &gCharacterNameCardOfSpadesByLanguage, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        104, 0x0, 7, 0x25, 711, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, &gCharacterNameCardOfSpadesByLanguage, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        104, 0x0, 8, 0x25, 711, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, gCharacterNameCardOfSpades, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10bPalette, &gCharacterNameCardOfSpadesByLanguage, gHookBSmallCardFrame0, gHookBSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        104, 0x0, 9, 0x25, 711, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, &gCharacterNameCardOfSpadesByLanguage, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        105, 0x0, 0, 0x26, 721, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, &gCharacterNameCardOfSpadesByLanguage, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        105, 0x0, 1, 0x26, 721, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, &gCharacterNameCardOfSpadesByLanguage, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        105, 0x0, 2, 0x26, 721, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, &gCharacterNameCardOfSpadesByLanguage, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        105, 0x0, 3, 0x26, 721, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, &gCharacterNameCardOfSpadesByLanguage, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        105, 0x0, 4, 0x26, 721, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, &gCharacterNameCardOfSpadesByLanguage, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        105, 0x0, 5, 0x26, 721, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, &gCharacterNameCardOfSpadesByLanguage, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        105, 0x0, 6, 0x26, 721, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, &gCharacterNameCardOfSpadesByLanguage, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        105, 0x0, 7, 0x26, 721, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, &gCharacterNameCardOfSpadesByLanguage, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        105, 0x0, 8, 0x26, 721, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, gCharacterNameCardOfSpades, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10cPalette, &gCharacterNameCardOfSpadesByLanguage, gHookCSmallCardFrame0, gHookCSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        105, 0x0, 9, 0x26, 721, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, &gCharacterNameCardOfSpadesByLanguage, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        106, 0x0, 0, 0x27, 731, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, &gCharacterNameCardOfSpadesByLanguage, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        106, 0x0, 1, 0x27, 731, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, &gCharacterNameCardOfSpadesByLanguage, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        106, 0x0, 2, 0x27, 731, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, &gCharacterNameCardOfSpadesByLanguage, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        106, 0x0, 3, 0x27, 731, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, &gCharacterNameCardOfSpadesByLanguage, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        106, 0x0, 4, 0x27, 731, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, &gCharacterNameCardOfSpadesByLanguage, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        106, 0x0, 5, 0x27, 731, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, &gCharacterNameCardOfSpadesByLanguage, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        106, 0x0, 6, 0x27, 731, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, &gCharacterNameCardOfSpadesByLanguage, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        106, 0x0, 7, 0x27, 731, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, &gCharacterNameCardOfSpadesByLanguage, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        106, 0x0, 8, 0x27, 731, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, gCharacterNameCardOfSpades, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos10Frame0, gCardBos10Tiles, gCardBos10dPalette, &gCharacterNameCardOfSpadesByLanguage, gHookSmallCardFrame0, gHookSmallCardTiles, gHookVariantSmallCardPalette,
#endif
        106, 0x0, 9, 0x27, 731, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesASmallCardFrame0, gHadesASmallCardTiles, gHadesASmallCardPalette,
#endif
        107, 0x0, 0, 0x24, 741, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesASmallCardFrame0, gHadesASmallCardTiles, gHadesASmallCardPalette,
#endif
        107, 0x0, 1, 0x24, 741, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesASmallCardFrame0, gHadesASmallCardTiles, gHadesASmallCardPalette,
#endif
        107, 0x0, 2, 0x24, 741, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesASmallCardFrame0, gHadesASmallCardTiles, gHadesASmallCardPalette,
#endif
        107, 0x0, 3, 0x24, 741, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesASmallCardFrame0, gHadesASmallCardTiles, gHadesASmallCardPalette,
#endif
        107, 0x0, 4, 0x24, 741, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesASmallCardFrame0, gHadesASmallCardTiles, gHadesASmallCardPalette,
#endif
        107, 0x0, 5, 0x24, 741, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesASmallCardFrame0, gHadesASmallCardTiles, gHadesASmallCardPalette,
#endif
        107, 0x0, 6, 0x24, 741, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesASmallCardFrame0, gHadesASmallCardTiles, gHadesASmallCardPalette,
#endif
        107, 0x0, 7, 0x24, 741, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesASmallCardFrame0, gHadesASmallCardTiles, gHadesASmallCardPalette,
#endif
        107, 0x0, 8, 0x24, 741, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11aPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesASmallCardFrame0, gHadesASmallCardTiles, gHadesASmallCardPalette,
#endif
        107, 0x0, 9, 0x24, 741, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesBSmallCardFrame0, gHadesBSmallCardTiles, gHadesASmallCardPalette,
#endif
        108, 0x0, 0, 0x25, 751, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesBSmallCardFrame0, gHadesBSmallCardTiles, gHadesASmallCardPalette,
#endif
        108, 0x0, 1, 0x25, 751, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesBSmallCardFrame0, gHadesBSmallCardTiles, gHadesASmallCardPalette,
#endif
        108, 0x0, 2, 0x25, 751, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesBSmallCardFrame0, gHadesBSmallCardTiles, gHadesASmallCardPalette,
#endif
        108, 0x0, 3, 0x25, 751, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesBSmallCardFrame0, gHadesBSmallCardTiles, gHadesASmallCardPalette,
#endif
        108, 0x0, 4, 0x25, 751, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesBSmallCardFrame0, gHadesBSmallCardTiles, gHadesASmallCardPalette,
#endif
        108, 0x0, 5, 0x25, 751, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesBSmallCardFrame0, gHadesBSmallCardTiles, gHadesASmallCardPalette,
#endif
        108, 0x0, 6, 0x25, 751, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesBSmallCardFrame0, gHadesBSmallCardTiles, gHadesASmallCardPalette,
#endif
        108, 0x0, 7, 0x25, 751, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesBSmallCardFrame0, gHadesBSmallCardTiles, gHadesASmallCardPalette,
#endif
        108, 0x0, 8, 0x25, 751, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, gCharacterNameCardOfSpades, gHadesSmallCardFrame0, gHadesSmallCardTiles, gHadesBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos11Frame0, gCardBos11Tiles, gCardBos11bPalette, &gCharacterNameCardOfSpadesByLanguage, gHadesBSmallCardFrame0, gHadesBSmallCardTiles, gHadesASmallCardPalette,
#endif
        108, 0x0, 9, 0x25, 751, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuASmallCardFrame0, gRikuASmallCardTiles, gRikuASmallCardPalette,
#endif
        111, 0x0, 0, 0x24, 761, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuASmallCardFrame0, gRikuASmallCardTiles, gRikuASmallCardPalette,
#endif
        111, 0x0, 1, 0x24, 761, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuASmallCardFrame0, gRikuASmallCardTiles, gRikuASmallCardPalette,
#endif
        111, 0x0, 2, 0x24, 761, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuASmallCardFrame0, gRikuASmallCardTiles, gRikuASmallCardPalette,
#endif
        111, 0x0, 3, 0x24, 761, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuASmallCardFrame0, gRikuASmallCardTiles, gRikuASmallCardPalette,
#endif
        111, 0x0, 4, 0x24, 761, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuASmallCardFrame0, gRikuASmallCardTiles, gRikuASmallCardPalette,
#endif
        111, 0x0, 5, 0x24, 761, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuASmallCardFrame0, gRikuASmallCardTiles, gRikuASmallCardPalette,
#endif
        111, 0x0, 6, 0x24, 761, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuASmallCardFrame0, gRikuASmallCardTiles, gRikuASmallCardPalette,
#endif
        111, 0x0, 7, 0x24, 761, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuASmallCardFrame0, gRikuASmallCardTiles, gRikuASmallCardPalette,
#endif
        111, 0x0, 8, 0x24, 761, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12aPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuASmallCardFrame0, gRikuASmallCardTiles, gRikuASmallCardPalette,
#endif
        111, 0x0, 9, 0x24, 761, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuBSmallCardFrame0, gRikuBSmallCardTiles, gRikuASmallCardPalette,
#endif
        112, 0x0, 0, 0x25, 771, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuBSmallCardFrame0, gRikuBSmallCardTiles, gRikuASmallCardPalette,
#endif
        112, 0x0, 1, 0x25, 771, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuBSmallCardFrame0, gRikuBSmallCardTiles, gRikuASmallCardPalette,
#endif
        112, 0x0, 2, 0x25, 771, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuBSmallCardFrame0, gRikuBSmallCardTiles, gRikuASmallCardPalette,
#endif
        112, 0x0, 3, 0x25, 771, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuBSmallCardFrame0, gRikuBSmallCardTiles, gRikuASmallCardPalette,
#endif
        112, 0x0, 4, 0x25, 771, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuBSmallCardFrame0, gRikuBSmallCardTiles, gRikuASmallCardPalette,
#endif
        112, 0x0, 5, 0x25, 771, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuBSmallCardFrame0, gRikuBSmallCardTiles, gRikuASmallCardPalette,
#endif
        112, 0x0, 6, 0x25, 771, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuBSmallCardFrame0, gRikuBSmallCardTiles, gRikuASmallCardPalette,
#endif
        112, 0x0, 7, 0x25, 771, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuBSmallCardFrame0, gRikuBSmallCardTiles, gRikuASmallCardPalette,
#endif
        112, 0x0, 8, 0x25, 771, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12bPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuBSmallCardFrame0, gRikuBSmallCardTiles, gRikuASmallCardPalette,
#endif
        112, 0x0, 9, 0x25, 771, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuCSmallCardFrame0, gRikuCSmallCardTiles, gRikuASmallCardPalette,
#endif
        113, 0x0, 0, 0x26, 781, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuCSmallCardFrame0, gRikuCSmallCardTiles, gRikuASmallCardPalette,
#endif
        113, 0x0, 1, 0x26, 781, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuCSmallCardFrame0, gRikuCSmallCardTiles, gRikuASmallCardPalette,
#endif
        113, 0x0, 2, 0x26, 781, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuCSmallCardFrame0, gRikuCSmallCardTiles, gRikuASmallCardPalette,
#endif
        113, 0x0, 3, 0x26, 781, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuCSmallCardFrame0, gRikuCSmallCardTiles, gRikuASmallCardPalette,
#endif
        113, 0x0, 4, 0x26, 781, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuCSmallCardFrame0, gRikuCSmallCardTiles, gRikuASmallCardPalette,
#endif
        113, 0x0, 5, 0x26, 781, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuCSmallCardFrame0, gRikuCSmallCardTiles, gRikuASmallCardPalette,
#endif
        113, 0x0, 6, 0x26, 781, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuCSmallCardFrame0, gRikuCSmallCardTiles, gRikuASmallCardPalette,
#endif
        113, 0x0, 7, 0x26, 781, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuCSmallCardFrame0, gRikuCSmallCardTiles, gRikuASmallCardPalette,
#endif
        113, 0x0, 8, 0x26, 781, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12cPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuCSmallCardFrame0, gRikuCSmallCardTiles, gRikuASmallCardPalette,
#endif
        113, 0x0, 9, 0x26, 781, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuDSmallCardFrame0, gRikuDSmallCardTiles, gRikuASmallCardPalette,
#endif
        114, 0x0, 0, 0x27, 791, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuDSmallCardFrame0, gRikuDSmallCardTiles, gRikuASmallCardPalette,
#endif
        114, 0x0, 1, 0x27, 791, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuDSmallCardFrame0, gRikuDSmallCardTiles, gRikuASmallCardPalette,
#endif
        114, 0x0, 2, 0x27, 791, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuDSmallCardFrame0, gRikuDSmallCardTiles, gRikuASmallCardPalette,
#endif
        114, 0x0, 3, 0x27, 791, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuDSmallCardFrame0, gRikuDSmallCardTiles, gRikuASmallCardPalette,
#endif
        114, 0x0, 4, 0x27, 791, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuDSmallCardFrame0, gRikuDSmallCardTiles, gRikuASmallCardPalette,
#endif
        114, 0x0, 5, 0x27, 791, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuDSmallCardFrame0, gRikuDSmallCardTiles, gRikuASmallCardPalette,
#endif
        114, 0x0, 6, 0x27, 791, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuDSmallCardFrame0, gRikuDSmallCardTiles, gRikuASmallCardPalette,
#endif
        114, 0x0, 7, 0x27, 791, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuDSmallCardFrame0, gRikuDSmallCardTiles, gRikuASmallCardPalette,
#endif
        114, 0x0, 8, 0x27, 791, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, gCharacterNameCardOfSpades, gRikuSmallCardFrame0, gRikuSmallCardTiles, gRikuDSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos12Frame0, gCardBos12Tiles, gCardBos12dPalette, &gCharacterNameCardOfSpadesByLanguage, gRikuDSmallCardFrame0, gRikuDSmallCardTiles, gRikuASmallCardPalette,
#endif
        114, 0x0, 9, 0x27, 791, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelASmallCardFrame0, gAxelASmallCardTiles, gAxelASmallCardPalette,
#endif
        115, 0x0, 0, 0x24, 801, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelASmallCardFrame0, gAxelASmallCardTiles, gAxelASmallCardPalette,
#endif
        115, 0x0, 1, 0x24, 801, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelASmallCardFrame0, gAxelASmallCardTiles, gAxelASmallCardPalette,
#endif
        115, 0x0, 2, 0x24, 801, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelASmallCardFrame0, gAxelASmallCardTiles, gAxelASmallCardPalette,
#endif
        115, 0x0, 3, 0x24, 801, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelASmallCardFrame0, gAxelASmallCardTiles, gAxelASmallCardPalette,
#endif
        115, 0x0, 4, 0x24, 801, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelASmallCardFrame0, gAxelASmallCardTiles, gAxelASmallCardPalette,
#endif
        115, 0x0, 5, 0x24, 801, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelASmallCardFrame0, gAxelASmallCardTiles, gAxelASmallCardPalette,
#endif
        115, 0x0, 6, 0x24, 801, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelASmallCardFrame0, gAxelASmallCardTiles, gAxelASmallCardPalette,
#endif
        115, 0x0, 7, 0x24, 801, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelASmallCardFrame0, gAxelASmallCardTiles, gAxelASmallCardPalette,
#endif
        115, 0x0, 8, 0x24, 801, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13aPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelASmallCardFrame0, gAxelASmallCardTiles, gAxelASmallCardPalette,
#endif
        115, 0x0, 9, 0x24, 801, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelBSmallCardFrame0, gAxelBSmallCardTiles, gAxelASmallCardPalette,
#endif
        116, 0x0, 0, 0x25, 811, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelBSmallCardFrame0, gAxelBSmallCardTiles, gAxelASmallCardPalette,
#endif
        116, 0x0, 1, 0x25, 811, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelBSmallCardFrame0, gAxelBSmallCardTiles, gAxelASmallCardPalette,
#endif
        116, 0x0, 2, 0x25, 811, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelBSmallCardFrame0, gAxelBSmallCardTiles, gAxelASmallCardPalette,
#endif
        116, 0x0, 3, 0x25, 811, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelBSmallCardFrame0, gAxelBSmallCardTiles, gAxelASmallCardPalette,
#endif
        116, 0x0, 4, 0x25, 811, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelBSmallCardFrame0, gAxelBSmallCardTiles, gAxelASmallCardPalette,
#endif
        116, 0x0, 5, 0x25, 811, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelBSmallCardFrame0, gAxelBSmallCardTiles, gAxelASmallCardPalette,
#endif
        116, 0x0, 6, 0x25, 811, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelBSmallCardFrame0, gAxelBSmallCardTiles, gAxelASmallCardPalette,
#endif
        116, 0x0, 7, 0x25, 811, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelBSmallCardFrame0, gAxelBSmallCardTiles, gAxelASmallCardPalette,
#endif
        116, 0x0, 8, 0x25, 811, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, gCharacterNameCardOfSpades, gAxelSmallCardFrame0, gAxelSmallCardTiles, gAxelBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos13Frame0, gCardBos13Tiles, gCardBos13bPalette, &gCharacterNameCardOfSpadesByLanguage, gAxelBSmallCardFrame0, gAxelBSmallCardTiles, gAxelASmallCardPalette,
#endif
        116, 0x0, 9, 0x25, 811, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneASmallCardFrame0, gLarxeneASmallCardTiles, gLarxeneASmallCardPalette,
#endif
        119, 0x0, 0, 0x24, 821, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneASmallCardFrame0, gLarxeneASmallCardTiles, gLarxeneASmallCardPalette,
#endif
        119, 0x0, 1, 0x24, 821, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneASmallCardFrame0, gLarxeneASmallCardTiles, gLarxeneASmallCardPalette,
#endif
        119, 0x0, 2, 0x24, 821, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneASmallCardFrame0, gLarxeneASmallCardTiles, gLarxeneASmallCardPalette,
#endif
        119, 0x0, 3, 0x24, 821, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneASmallCardFrame0, gLarxeneASmallCardTiles, gLarxeneASmallCardPalette,
#endif
        119, 0x0, 4, 0x24, 821, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneASmallCardFrame0, gLarxeneASmallCardTiles, gLarxeneASmallCardPalette,
#endif
        119, 0x0, 5, 0x24, 821, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneASmallCardFrame0, gLarxeneASmallCardTiles, gLarxeneASmallCardPalette,
#endif
        119, 0x0, 6, 0x24, 821, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneASmallCardFrame0, gLarxeneASmallCardTiles, gLarxeneASmallCardPalette,
#endif
        119, 0x0, 7, 0x24, 821, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneASmallCardFrame0, gLarxeneASmallCardTiles, gLarxeneASmallCardPalette,
#endif
        119, 0x0, 8, 0x24, 821, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneASmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14aPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneASmallCardFrame0, gLarxeneASmallCardTiles, gLarxeneASmallCardPalette,
#endif
        119, 0x0, 9, 0x24, 821, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneBSmallCardFrame0, gLarxeneBSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        120, 0x0, 0, 0x25, 831, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneBSmallCardFrame0, gLarxeneBSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        120, 0x0, 1, 0x25, 831, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneBSmallCardFrame0, gLarxeneBSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        120, 0x0, 2, 0x25, 831, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneBSmallCardFrame0, gLarxeneBSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        120, 0x0, 3, 0x25, 831, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneBSmallCardFrame0, gLarxeneBSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        120, 0x0, 4, 0x25, 831, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneBSmallCardFrame0, gLarxeneBSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        120, 0x0, 5, 0x25, 831, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneBSmallCardFrame0, gLarxeneBSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        120, 0x0, 6, 0x25, 831, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneBSmallCardFrame0, gLarxeneBSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        120, 0x0, 7, 0x25, 831, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneBSmallCardFrame0, gLarxeneBSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        120, 0x0, 8, 0x25, 831, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneBSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14bPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneBSmallCardFrame0, gLarxeneBSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        120, 0x0, 9, 0x25, 831, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneCSmallCardFrame0, gLarxeneCSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        121, 0x0, 0, 0x26, 841, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneCSmallCardFrame0, gLarxeneCSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        121, 0x0, 1, 0x26, 841, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneCSmallCardFrame0, gLarxeneCSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        121, 0x0, 2, 0x26, 841, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneCSmallCardFrame0, gLarxeneCSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        121, 0x0, 3, 0x26, 841, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneCSmallCardFrame0, gLarxeneCSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        121, 0x0, 4, 0x26, 841, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneCSmallCardFrame0, gLarxeneCSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        121, 0x0, 5, 0x26, 841, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneCSmallCardFrame0, gLarxeneCSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        121, 0x0, 6, 0x26, 841, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneCSmallCardFrame0, gLarxeneCSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        121, 0x0, 7, 0x26, 841, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneCSmallCardFrame0, gLarxeneCSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        121, 0x0, 8, 0x26, 841, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, gCharacterNameCardOfSpades, gLarxeneSmallCardFrame0, gLarxeneSmallCardTiles, gLarxeneCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos14Frame0, gCardBos14Tiles, gCardBos14cPalette, &gCharacterNameCardOfSpadesByLanguage, gLarxeneCSmallCardFrame0, gLarxeneCSmallCardTiles, gLarxeneASmallCardPalette,
#endif
        121, 0x0, 9, 0x26, 841, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        123, 0x0, 0, 0x24, 851, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        123, 0x0, 1, 0x24, 851, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        123, 0x0, 2, 0x24, 851, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        123, 0x0, 3, 0x24, 851, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        123, 0x0, 4, 0x24, 851, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        123, 0x0, 5, 0x24, 851, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        123, 0x0, 6, 0x24, 851, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        123, 0x0, 7, 0x24, 851, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        123, 0x0, 8, 0x24, 851, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, gCharacterNameCardOfSpades, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15aPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenASmallCardFrame0, gVexenASmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        123, 0x0, 9, 0x24, 851, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        124, 0x0, 0, 0x25, 861, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        124, 0x0, 1, 0x25, 861, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        124, 0x0, 2, 0x25, 861, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        124, 0x0, 3, 0x25, 861, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        124, 0x0, 4, 0x25, 861, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        124, 0x0, 5, 0x25, 861, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        124, 0x0, 6, 0x25, 861, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        124, 0x0, 7, 0x25, 861, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        124, 0x0, 8, 0x25, 861, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, gCharacterNameCardOfSpades, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos15Frame0, gCardBos15Tiles, gCardBos15bPalette, &gCharacterNameCardOfSpadesByLanguage, gVexenBSmallCardFrame0, gVexenBSmallCardTiles, gVexenVariantSmallCardPalette,
#endif
        124, 0x0, 9, 0x25, 861, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        127, 0x0, 0, 0x24, 871, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        127, 0x0, 1, 0x24, 871, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        127, 0x0, 2, 0x24, 871, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        127, 0x0, 3, 0x24, 871, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        127, 0x0, 4, 0x24, 871, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        127, 0x0, 5, 0x24, 871, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        127, 0x0, 6, 0x24, 871, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        127, 0x0, 7, 0x24, 871, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        127, 0x0, 8, 0x24, 871, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, gCharacterNameCardOfSpades, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16aPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaASmallCardFrame0, gMarluxiaASmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        127, 0x0, 9, 0x24, 871, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        128, 0x0, 0, 0x25, 881, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        128, 0x0, 1, 0x25, 881, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        128, 0x0, 2, 0x25, 881, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        128, 0x0, 3, 0x25, 881, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        128, 0x0, 4, 0x25, 881, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        128, 0x0, 5, 0x25, 881, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        128, 0x0, 6, 0x25, 881, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        128, 0x0, 7, 0x25, 881, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        128, 0x0, 8, 0x25, 881, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, gCharacterNameCardOfSpades, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16bPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaBSmallCardFrame0, gMarluxiaBSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        128, 0x0, 9, 0x25, 881, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        129, 0x0, 0, 0x26, 891, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        129, 0x0, 1, 0x26, 891, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        129, 0x0, 2, 0x26, 891, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        129, 0x0, 3, 0x26, 891, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        129, 0x0, 4, 0x26, 891, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        129, 0x0, 5, 0x26, 891, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        129, 0x0, 6, 0x26, 891, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        129, 0x0, 7, 0x26, 891, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        129, 0x0, 8, 0x26, 891, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, gCharacterNameCardOfSpades, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos16Frame0, gCardBos16Tiles, gCardBos16cPalette, &gCharacterNameCardOfSpadesByLanguage, gMarluxiaCSmallCardFrame0, gMarluxiaCSmallCardTiles, gMarluxiaVariantSmallCardPalette,
#endif
        129, 0x0, 9, 0x26, 891, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        139, 0x0, 0, 0x24, 901, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        139, 0x0, 1, 0x24, 901, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        139, 0x0, 2, 0x24, 901, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        139, 0x0, 3, 0x24, 901, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        139, 0x0, 4, 0x24, 901, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        139, 0x0, 5, 0x24, 901, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        139, 0x0, 6, 0x24, 901, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        139, 0x0, 7, 0x24, 901, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        139, 0x0, 8, 0x24, 901, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, gCharacterNameCardOfSpades, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17aPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusASmallCardFrame0, gLexaeusASmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        139, 0x0, 9, 0x24, 901, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        140, 0x0, 0, 0x25, 911, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        140, 0x0, 1, 0x25, 911, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        140, 0x0, 2, 0x25, 911, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        140, 0x0, 3, 0x25, 911, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        140, 0x0, 4, 0x25, 911, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        140, 0x0, 5, 0x25, 911, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        140, 0x0, 6, 0x25, 911, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        140, 0x0, 7, 0x25, 911, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        140, 0x0, 8, 0x25, 911, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, gCharacterNameCardOfSpades, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17bPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusBSmallCardFrame0, gLexaeusBSmallCardTiles, gLexaeusVariantSmallCardPalette,
#endif
        140, 0x0, 9, 0x25, 911, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#endif
        141, 0x0, 0, 0x26, 921, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#endif
        141, 0x0, 1, 0x26, 921, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#endif
        141, 0x0, 2, 0x26, 921, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#endif
        141, 0x0, 3, 0x26, 921, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#endif
        141, 0x0, 4, 0x26, 921, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#endif
        141, 0x0, 5, 0x26, 921, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#endif
        141, 0x0, 6, 0x26, 921, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#endif
        141, 0x0, 7, 0x26, 921, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#endif
        141, 0x0, 8, 0x26, 921, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, gCharacterNameCardOfSpades, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos17Frame0, gCardBos17Tiles, gCardBos17cPalette, &gCharacterNameCardOfSpadesByLanguage, gLexaeusSmallCardFrame0, gLexaeusSmallCardTiles, gLexaeusCSmallCardPalette,
#endif
        141, 0x0, 9, 0x26, 921, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        135, 0x0, 0, 0x24, 931, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        135, 0x0, 1, 0x24, 931, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        135, 0x0, 2, 0x24, 931, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        135, 0x0, 3, 0x24, 931, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        135, 0x0, 4, 0x24, 931, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        135, 0x0, 5, 0x24, 931, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        135, 0x0, 6, 0x24, 931, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        135, 0x0, 7, 0x24, 931, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        135, 0x0, 8, 0x24, 931, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, gCharacterNameCardOfSpades, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18aPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemASmallCardFrame0, gAnsemASmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        135, 0x0, 9, 0x24, 931, 1, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        136, 0x0, 0, 0x25, 941, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        136, 0x0, 1, 0x25, 941, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        136, 0x0, 2, 0x25, 941, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        136, 0x0, 3, 0x25, 941, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        136, 0x0, 4, 0x25, 941, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        136, 0x0, 5, 0x25, 941, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        136, 0x0, 6, 0x25, 941, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        136, 0x0, 7, 0x25, 941, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        136, 0x0, 8, 0x25, 941, 0, 0, {0, 0, 0, 0, 0, 0},
    },
    {
#if defined(VERSION_US)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_JP)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, gCharacterNameCardOfSpades, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#elif defined(VERSION_EU)
        gCardBos18Frame0, gCardBos18Tiles, gCardBos18bPalette, &gCharacterNameCardOfSpadesByLanguage, gAnsemBSmallCardFrame0, gAnsemBSmallCardTiles, gAnsemVariantSmallCardPalette,
#endif
        136, 0x0, 9, 0x25, 941, 0, 0, {0, 0, 0, 0, 0, 0},
    },
};

const HcEffectDef gHcEffectDefs[55] = {
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
        0,
        0,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
        0,
        2,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        33,
#elif defined(VERSION_JP)
        1,
#elif defined(VERSION_US)
        33,
#endif
        20,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        1,
#elif defined(VERSION_JP)
        2,
#elif defined(VERSION_US)
        1,
#endif
        3,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        9,
#elif defined(VERSION_JP)
        3,
#elif defined(VERSION_US)
        9,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        7,
#elif defined(VERSION_JP)
        4,
#elif defined(VERSION_US)
        7,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        3,
#elif defined(VERSION_JP)
        5,
#elif defined(VERSION_US)
        3,
#endif
        5,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        22,
#elif defined(VERSION_JP)
        6,
#elif defined(VERSION_US)
        22,
#endif
        3,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        32,
#elif defined(VERSION_JP)
        7,
#elif defined(VERSION_US)
        32,
#endif
        30,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        30,
#elif defined(VERSION_JP)
        8,
#elif defined(VERSION_US)
        30,
#endif
        3,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        28,
#elif defined(VERSION_JP)
        9,
#elif defined(VERSION_US)
        28,
#endif
#ifdef VERSION_EU
        1,
#else
        2,
#endif
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
        10,
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
        11,
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
        12,
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        24,
#elif defined(VERSION_JP)
        13,
#elif defined(VERSION_US)
        24,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        43,
#elif defined(VERSION_JP)
        14,
#elif defined(VERSION_US)
        43,
#endif
        5,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        6,
#elif defined(VERSION_JP)
        15,
#elif defined(VERSION_US)
        6,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        8,
#elif defined(VERSION_JP)
        16,
#elif defined(VERSION_US)
        8,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        41,
#elif defined(VERSION_JP)
        17,
#elif defined(VERSION_US)
        41,
#endif
        10,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        16,
#elif defined(VERSION_JP)
        18,
#elif defined(VERSION_US)
        16,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        20,
#elif defined(VERSION_JP)
        19,
#elif defined(VERSION_US)
        20,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        21,
#elif defined(VERSION_JP)
        20,
#elif defined(VERSION_US)
        21,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
        21,
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        36,
#elif defined(VERSION_JP)
        22,
#elif defined(VERSION_US)
        36,
#endif
        10,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        15,
#elif defined(VERSION_JP)
        23,
#elif defined(VERSION_US)
        15,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        23,
#elif defined(VERSION_JP)
        24,
#elif defined(VERSION_US)
        23,
#endif
#ifdef VERSION_EU
        3,
#else
        1,
#endif
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        38,
#elif defined(VERSION_JP)
        25,
#elif defined(VERSION_US)
        38,
#endif
        3,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        44,
#elif defined(VERSION_JP)
        26,
#elif defined(VERSION_US)
        44,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        42,
#elif defined(VERSION_JP)
        27,
#elif defined(VERSION_US)
        42,
#endif
        10,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        17,
#elif defined(VERSION_JP)
        28,
#elif defined(VERSION_US)
        17,
#endif
        3,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        27,
#elif defined(VERSION_JP)
        29,
#elif defined(VERSION_US)
        27,
#endif
        3,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        2,
#elif defined(VERSION_JP)
        30,
#elif defined(VERSION_US)
        2,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
        31,
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
        32,
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        31,
#elif defined(VERSION_JP)
        33,
#elif defined(VERSION_US)
        31,
#endif
        30,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        19,
#elif defined(VERSION_JP)
        34,
#elif defined(VERSION_US)
        19,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        4,
#elif defined(VERSION_JP)
        35,
#elif defined(VERSION_US)
        4,
#endif
        2,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        26,
#elif defined(VERSION_JP)
        36,
#elif defined(VERSION_US)
        26,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        14,
#elif defined(VERSION_JP)
        37,
#elif defined(VERSION_US)
        14,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        13,
#elif defined(VERSION_JP)
        38,
#elif defined(VERSION_US)
        13,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        29,
#elif defined(VERSION_JP)
        39,
#elif defined(VERSION_US)
        29,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        37,
#elif defined(VERSION_JP)
        40,
#elif defined(VERSION_US)
        37,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        25,
#elif defined(VERSION_JP)
        41,
#elif defined(VERSION_US)
        25,
#endif
        3,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        39,
#elif defined(VERSION_JP)
        42,
#elif defined(VERSION_US)
        39,
#endif
        30,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        40,
#elif defined(VERSION_JP)
        43,
#elif defined(VERSION_US)
        40,
#endif
        30,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        34,
#elif defined(VERSION_JP)
        44,
#elif defined(VERSION_US)
        34,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        35,
#elif defined(VERSION_JP)
        45,
#elif defined(VERSION_US)
        35,
#endif
        5,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        45,
#elif defined(VERSION_JP)
        46,
#elif defined(VERSION_US)
        45,
#endif
        3,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        46,
#elif defined(VERSION_JP)
        47,
#elif defined(VERSION_US)
        46,
#endif
        10,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
        48,
        50,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        47,
#elif defined(VERSION_JP)
        49,
#elif defined(VERSION_US)
        47,
#endif
        15,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        5,
#elif defined(VERSION_JP)
        50,
#elif defined(VERSION_US)
        5,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        34,
#elif defined(VERSION_JP)
        51,
#elif defined(VERSION_US)
        34,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
#if defined(VERSION_EU)
        18,
#elif defined(VERSION_JP)
        52,
#elif defined(VERSION_US)
        18,
#endif
        3,
    },
    {
#ifdef VERSION_EU
        gHcEffectNameTilesByLanguage,
#else
        gHcEffectNameTiles,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#ifdef VERSION_EU
        gHcEffectNameSpritesByLanguage,
#else
        gHcEffectNameFrames,
#endif
        0,
        1,
    },
};

const SpriteFrameResourceDef gStockNameSprites[106] = {
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#ifdef VERSION_EU
        640,
#else
        384,
#endif
        0,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        384,
#elif defined(VERSION_US)
        512,
#endif
        2,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        384,
#elif defined(VERSION_US)
        576,
#endif
        4,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#ifdef VERSION_EU
        640,
#else
        384,
#endif
#if defined(VERSION_EU)
        6,
#elif defined(VERSION_JP)
        10,
#elif defined(VERSION_US)
        6,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        384,
#elif defined(VERSION_US)
        448,
#endif
#if defined(VERSION_EU)
        10,
#elif defined(VERSION_JP)
        6,
#elif defined(VERSION_US)
        10,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
        640,
#if defined(VERSION_EU)
        1,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        1,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        576,
#elif defined(VERSION_US)
        640,
#endif
#if defined(VERSION_EU)
        3,
#elif defined(VERSION_JP)
        1,
#elif defined(VERSION_US)
        3,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        384,
#elif defined(VERSION_US)
        448,
#endif
        1,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        384,
#elif defined(VERSION_US)
        512,
#endif
        3,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        384,
#elif defined(VERSION_US)
        576,
#endif
        5,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        384,
#elif defined(VERSION_US)
        512,
#endif
#if defined(VERSION_EU)
        7,
#elif defined(VERSION_JP)
        11,
#elif defined(VERSION_US)
        7,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        384,
#elif defined(VERSION_US)
        512,
#endif
        8,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        384,
#elif defined(VERSION_US)
        512,
#endif
        9,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        384,
#elif defined(VERSION_US)
        448,
#endif
#if defined(VERSION_EU)
        11,
#elif defined(VERSION_JP)
        7,
#elif defined(VERSION_US)
        11,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameFriendTilesByLanguage,
#else
        gStockNameFriendTiles,
#endif
#ifdef VERSION_EU
        gStockNameFriendSpritesByLanguage,
#else
        gStockNameFriendFrames,
#endif
        640,
        2,
    },
    {
#ifdef VERSION_EU
        gStockNameFriendTilesByLanguage,
#else
        gStockNameFriendTiles,
#endif
#ifdef VERSION_EU
        gStockNameFriendSpritesByLanguage,
#else
        gStockNameFriendFrames,
#endif
        640,
        1,
    },
    {
#ifdef VERSION_EU
        gStockNameFriendTilesByLanguage,
#else
        gStockNameFriendTiles,
#endif
#ifdef VERSION_EU
        gStockNameFriendSpritesByLanguage,
#else
        gStockNameFriendFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        384,
#elif defined(VERSION_US)
        640,
#endif
        0,
    },
    {
#ifdef VERSION_EU
        gStockNameFriendTilesByLanguage,
#else
        gStockNameFriendTiles,
#endif
#ifdef VERSION_EU
        gStockNameFriendSpritesByLanguage,
#else
        gStockNameFriendFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        384,
#elif defined(VERSION_US)
        640,
#endif
        0,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        512,
#elif defined(VERSION_US)
        640,
#endif
#if defined(VERSION_EU)
        14,
#elif defined(VERSION_JP)
        12,
#elif defined(VERSION_US)
        14,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        512,
#elif defined(VERSION_US)
        640,
#endif
#if defined(VERSION_EU)
        14,
#elif defined(VERSION_JP)
        12,
#elif defined(VERSION_US)
        14,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        704,
#elif defined(VERSION_US)
        512,
#endif
#if defined(VERSION_EU)
        15,
#elif defined(VERSION_JP)
        17,
#elif defined(VERSION_US)
        15,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        704,
#elif defined(VERSION_US)
        512,
#endif
#if defined(VERSION_EU)
        15,
#elif defined(VERSION_JP)
        17,
#elif defined(VERSION_US)
        15,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
#if defined(VERSION_EU)
        20,
#elif defined(VERSION_JP)
        19,
#elif defined(VERSION_US)
        20,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
#if defined(VERSION_EU)
        20,
#elif defined(VERSION_JP)
        19,
#elif defined(VERSION_US)
        20,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        640,
#elif defined(VERSION_US)
        448,
#endif
#if defined(VERSION_EU)
        21,
#elif defined(VERSION_JP)
        20,
#elif defined(VERSION_US)
        21,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        640,
#elif defined(VERSION_US)
        448,
#endif
#if defined(VERSION_EU)
        21,
#elif defined(VERSION_JP)
        20,
#elif defined(VERSION_US)
        21,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
#if defined(VERSION_EU)
        16,
#elif defined(VERSION_JP)
        42,
#elif defined(VERSION_US)
        16,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
#if defined(VERSION_EU)
        16,
#elif defined(VERSION_JP)
        42,
#elif defined(VERSION_US)
        16,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
#if defined(VERSION_EU)
        17,
#elif defined(VERSION_JP)
        18,
#elif defined(VERSION_US)
        17,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
#if defined(VERSION_EU)
        17,
#elif defined(VERSION_JP)
        18,
#elif defined(VERSION_US)
        17,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        640,
#elif defined(VERSION_US)
        576,
#endif
#if defined(VERSION_EU)
        19,
#elif defined(VERSION_JP)
        16,
#elif defined(VERSION_US)
        19,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
#if defined(VERSION_EU)
        18,
#elif defined(VERSION_JP)
        15,
#elif defined(VERSION_US)
        18,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameFriendTilesByLanguage,
#else
        gStockNameFriendTiles,
#endif
#ifdef VERSION_EU
        gStockNameFriendSpritesByLanguage,
#else
        gStockNameFriendFrames,
#endif
        640,
#if defined(VERSION_EU)
        3,
#elif defined(VERSION_JP)
        6,
#elif defined(VERSION_US)
        3,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameFriendTilesByLanguage,
#else
        gStockNameFriendTiles,
#endif
#ifdef VERSION_EU
        gStockNameFriendSpritesByLanguage,
#else
        gStockNameFriendFrames,
#endif
        640,
#if defined(VERSION_EU)
        3,
#elif defined(VERSION_JP)
        6,
#elif defined(VERSION_US)
        3,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameFriendTilesByLanguage,
#else
        gStockNameFriendTiles,
#endif
#ifdef VERSION_EU
        gStockNameFriendSpritesByLanguage,
#else
        gStockNameFriendFrames,
#endif
        640,
#if defined(VERSION_EU)
        5,
#elif defined(VERSION_JP)
        3,
#elif defined(VERSION_US)
        5,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameFriendTilesByLanguage,
#else
        gStockNameFriendTiles,
#endif
#ifdef VERSION_EU
        gStockNameFriendSpritesByLanguage,
#else
        gStockNameFriendFrames,
#endif
        640,
#if defined(VERSION_EU)
        5,
#elif defined(VERSION_JP)
        3,
#elif defined(VERSION_US)
        5,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameFriendTilesByLanguage,
#else
        gStockNameFriendTiles,
#endif
#ifdef VERSION_EU
        gStockNameFriendSpritesByLanguage,
#else
        gStockNameFriendFrames,
#endif
        640,
#if defined(VERSION_EU)
        4,
#elif defined(VERSION_JP)
        7,
#elif defined(VERSION_US)
        4,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameFriendTilesByLanguage,
#else
        gStockNameFriendTiles,
#endif
#ifdef VERSION_EU
        gStockNameFriendSpritesByLanguage,
#else
        gStockNameFriendFrames,
#endif
        640,
#if defined(VERSION_EU)
        4,
#elif defined(VERSION_JP)
        7,
#elif defined(VERSION_US)
        4,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameFriendTilesByLanguage,
#else
        gStockNameFriendTiles,
#endif
#ifdef VERSION_EU
        gStockNameFriendSpritesByLanguage,
#else
        gStockNameFriendFrames,
#endif
        640,
#if defined(VERSION_EU)
        6,
#elif defined(VERSION_JP)
        5,
#elif defined(VERSION_US)
        6,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameFriendTilesByLanguage,
#else
        gStockNameFriendTiles,
#endif
#ifdef VERSION_EU
        gStockNameFriendSpritesByLanguage,
#else
        gStockNameFriendFrames,
#endif
        640,
#if defined(VERSION_EU)
        6,
#elif defined(VERSION_JP)
        5,
#elif defined(VERSION_US)
        6,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameFriendTilesByLanguage,
#else
        gStockNameFriendTiles,
#endif
#ifdef VERSION_EU
        gStockNameFriendSpritesByLanguage,
#else
        gStockNameFriendFrames,
#endif
        640,
#if defined(VERSION_EU)
        7,
#elif defined(VERSION_JP)
        4,
#elif defined(VERSION_US)
        7,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameFriendTilesByLanguage,
#else
        gStockNameFriendTiles,
#endif
#ifdef VERSION_EU
        gStockNameFriendSpritesByLanguage,
#else
        gStockNameFriendFrames,
#endif
        640,
#if defined(VERSION_EU)
        7,
#elif defined(VERSION_JP)
        4,
#elif defined(VERSION_US)
        7,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMmMiracleTilesByLanguage,
#else
        gUnk_0908AF32,
#endif
#ifdef VERSION_EU
        gStockNameMmMiracleSpritesByLanguage,
#else
        gUnk_09EEA140,
#endif
        640,
        0,
    },
    {
#ifdef VERSION_EU
        gStockNameMmMiracleTilesByLanguage,
#else
        gUnk_0908AF32,
#endif
#ifdef VERSION_EU
        gStockNameMmMiracleSpritesByLanguage,
#else
        gUnk_09EEA140,
#endif
        640,
        0,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        512,
#elif defined(VERSION_US)
        448,
#endif
#if defined(VERSION_EU)
        12,
#elif defined(VERSION_JP)
        13,
#elif defined(VERSION_US)
        12,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        512,
#elif defined(VERSION_US)
        448,
#endif
#if defined(VERSION_EU)
        13,
#elif defined(VERSION_JP)
        14,
#elif defined(VERSION_US)
        13,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
        640,
#if defined(VERSION_EU)
        0,
#elif defined(VERSION_JP)
        8,
#elif defined(VERSION_US)
        0,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
        640,
#if defined(VERSION_EU)
        2,
#elif defined(VERSION_JP)
        5,
#elif defined(VERSION_US)
        2,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        576,
#elif defined(VERSION_US)
        640,
#endif
#if defined(VERSION_EU)
        4,
#elif defined(VERSION_JP)
        2,
#elif defined(VERSION_US)
        4,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
        640,
#if defined(VERSION_EU)
        5,
#elif defined(VERSION_JP)
        7,
#elif defined(VERSION_US)
        5,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
        640,
#if defined(VERSION_EU)
        6,
#elif defined(VERSION_JP)
        4,
#elif defined(VERSION_US)
        6,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
        640,
#if defined(VERSION_EU)
        7,
#elif defined(VERSION_JP)
        6,
#elif defined(VERSION_US)
        7,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
        640,
#if defined(VERSION_EU)
        8,
#elif defined(VERSION_JP)
        3,
#elif defined(VERSION_US)
        8,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        640,
#elif defined(VERSION_US)
        384,
#endif
#if defined(VERSION_EU)
        22,
#elif defined(VERSION_JP)
        21,
#elif defined(VERSION_US)
        22,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
#if defined(VERSION_EU)
        23,
#elif defined(VERSION_JP)
        22,
#elif defined(VERSION_US)
        23,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        640,
#elif defined(VERSION_US)
        448,
#endif
#if defined(VERSION_EU)
        24,
#elif defined(VERSION_JP)
        23,
#elif defined(VERSION_US)
        24,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        640,
#elif defined(VERSION_US)
        512,
#endif
#if defined(VERSION_EU)
        25,
#elif defined(VERSION_JP)
        24,
#elif defined(VERSION_US)
        25,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
        25,
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
        640,
        9,
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
        640,
        10,
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
        640,
        11,
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
        640,
        12,
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
        640,
        13,
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
        640,
        14,
    },
    {
#ifdef VERSION_EU
        gStockNameAttackTilesByLanguage,
#else
        gStockNameAttackTiles,
#endif
#ifdef VERSION_EU
        gStockNameAttackSpritesByLanguage,
#else
        gStockNameAttackFrames,
#endif
        640,
        15,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
        26,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        640,
#elif defined(VERSION_US)
        448,
#endif
        27,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
        28,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
        0,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
        29,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
        30,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
        31,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
        32,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
        33,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
        34,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        640,
        35,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
        704,
        36,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        640,
#elif defined(VERSION_US)
        512,
#endif
        37,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        640,
#elif defined(VERSION_US)
        320,
#endif
        38,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        640,
#elif defined(VERSION_US)
        512,
#endif
        39,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        640,
#elif defined(VERSION_US)
        448,
#endif
        40,
    },
    {
#ifdef VERSION_EU
        gStockNameMagicTilesByLanguage,
#else
        gStockNameMagicTiles,
#endif
#ifdef VERSION_EU
        gStockNameMagicSpritesByLanguage,
#else
        gStockNameMagicFrames,
#endif
#if defined(VERSION_EU)
        640,
#elif defined(VERSION_JP)
        640,
#elif defined(VERSION_US)
        512,
#endif
        41,
    },
    {
#ifdef VERSION_EU
        gStockNameRikuTilesByLanguage,
#else
        gUnk_0908A958,
#endif
#ifdef VERSION_EU
        gStockNameRikuSpritesByLanguage,
#else
        gUnk_09EEA130,
#endif
        640,
#if defined(VERSION_EU)
        2,
#elif defined(VERSION_JP)
        0,
#elif defined(VERSION_US)
        2,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameRikuTilesByLanguage,
#else
        gUnk_0908A958,
#endif
#ifdef VERSION_EU
        gStockNameRikuSpritesByLanguage,
#else
        gUnk_09EEA130,
#endif
        640,
#if defined(VERSION_EU)
        0,
#elif defined(VERSION_JP)
        1,
#elif defined(VERSION_US)
        0,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameRikuTilesByLanguage,
#else
        gUnk_0908A958,
#endif
#ifdef VERSION_EU
        gStockNameRikuSpritesByLanguage,
#else
        gUnk_09EEA130,
#endif
        640,
#if defined(VERSION_EU)
        1,
#elif defined(VERSION_JP)
        2,
#elif defined(VERSION_US)
        1,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameBossTilesByLanguage,
#else
        gStockNameBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameBossSpritesByLanguage,
#else
        gStockNameBossFrames,
#endif
        640,
        0,
    },
    {
#ifdef VERSION_EU
        gStockNameWorldBossTilesByLanguage,
#else
        gStockNameWorldBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameWorldBossSpritesByLanguage,
#else
        gStockNameWorldBossFrames,
#endif
        640,
        0,
    },
    {
#ifdef VERSION_EU
        gStockNameWorldBossTilesByLanguage,
#else
        gStockNameWorldBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameWorldBossSpritesByLanguage,
#else
        gStockNameWorldBossFrames,
#endif
        640,
        1,
    },
    {
#ifdef VERSION_EU
        gStockNameWorldBossTilesByLanguage,
#else
        gStockNameWorldBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameWorldBossSpritesByLanguage,
#else
        gStockNameWorldBossFrames,
#endif
        640,
        2,
    },
    {
#ifdef VERSION_EU
        gStockNameWorldBossTilesByLanguage,
#else
        gStockNameWorldBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameWorldBossSpritesByLanguage,
#else
        gStockNameWorldBossFrames,
#endif
        640,
        3,
    },
    {
#ifdef VERSION_EU
        gStockNameBossTilesByLanguage,
#else
        gStockNameBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameBossSpritesByLanguage,
#else
        gStockNameBossFrames,
#endif
        640,
#if defined(VERSION_EU)
        2,
#elif defined(VERSION_JP)
        1,
#elif defined(VERSION_US)
        2,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameWorldBossTilesByLanguage,
#else
        gStockNameWorldBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameWorldBossSpritesByLanguage,
#else
        gStockNameWorldBossFrames,
#endif
        640,
        4,
    },
    {
#ifdef VERSION_EU
        gStockNameWorldBossTilesByLanguage,
#else
        gStockNameWorldBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameWorldBossSpritesByLanguage,
#else
        gStockNameWorldBossFrames,
#endif
        640,
        5,
    },
    {
#ifdef VERSION_EU
        gStockNameBossTilesByLanguage,
#else
        gStockNameBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameBossSpritesByLanguage,
#else
        gStockNameBossFrames,
#endif
        640,
#if defined(VERSION_EU)
        10,
#elif defined(VERSION_JP)
        2,
#elif defined(VERSION_US)
        10,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameBossTilesByLanguage,
#else
        gStockNameBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameBossSpritesByLanguage,
#else
        gStockNameBossFrames,
#endif
        640,
#if defined(VERSION_EU)
        4,
#elif defined(VERSION_JP)
        3,
#elif defined(VERSION_US)
        4,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameBossTilesByLanguage,
#else
        gStockNameBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameBossSpritesByLanguage,
#else
        gStockNameBossFrames,
#endif
        640,
#if defined(VERSION_EU)
        7,
#elif defined(VERSION_JP)
        4,
#elif defined(VERSION_US)
        7,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameBossTilesByLanguage,
#else
        gStockNameBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameBossSpritesByLanguage,
#else
        gStockNameBossFrames,
#endif
        640,
        5,
    },
    {
#ifdef VERSION_EU
        gStockNameBossTilesByLanguage,
#else
        gStockNameBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameBossSpritesByLanguage,
#else
        gStockNameBossFrames,
#endif
        640,
#if defined(VERSION_EU)
        11,
#elif defined(VERSION_JP)
        6,
#elif defined(VERSION_US)
        11,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameBossTilesByLanguage,
#else
        gStockNameBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameBossSpritesByLanguage,
#else
        gStockNameBossFrames,
#endif
        640,
#if defined(VERSION_EU)
        3,
#elif defined(VERSION_JP)
        7,
#elif defined(VERSION_US)
        3,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameBossTilesByLanguage,
#else
        gStockNameBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameBossSpritesByLanguage,
#else
        gStockNameBossFrames,
#endif
        640,
#if defined(VERSION_EU)
        1,
#elif defined(VERSION_JP)
        8,
#elif defined(VERSION_US)
        1,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameBossTilesByLanguage,
#else
        gStockNameBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameBossSpritesByLanguage,
#else
        gStockNameBossFrames,
#endif
        640,
#if defined(VERSION_EU)
        8,
#elif defined(VERSION_JP)
        9,
#elif defined(VERSION_US)
        8,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameBossTilesByLanguage,
#else
        gStockNameBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameBossSpritesByLanguage,
#else
        gStockNameBossFrames,
#endif
        640,
#if defined(VERSION_EU)
        9,
#elif defined(VERSION_JP)
        10,
#elif defined(VERSION_US)
        9,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameBossTilesByLanguage,
#else
        gStockNameBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameBossSpritesByLanguage,
#else
        gStockNameBossFrames,
#endif
        640,
#ifdef VERSION_EU
        13,
#else
        12,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameBossTilesByLanguage,
#else
        gStockNameBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameBossSpritesByLanguage,
#else
        gStockNameBossFrames,
#endif
        640,
#if defined(VERSION_EU)
        14,
#elif defined(VERSION_JP)
        13,
#elif defined(VERSION_US)
        14,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameBossTilesByLanguage,
#else
        gStockNameBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameBossSpritesByLanguage,
#else
        gStockNameBossFrames,
#endif
        640,
#if defined(VERSION_EU)
        12,
#elif defined(VERSION_JP)
        11,
#elif defined(VERSION_US)
        12,
#endif
    },
    {
#ifdef VERSION_EU
        gStockNameBossTilesByLanguage,
#else
        gStockNameBossTiles,
#endif
#ifdef VERSION_EU
        gStockNameBossSpritesByLanguage,
#else
        gStockNameBossFrames,
#endif
        640,
#if defined(VERSION_EU)
        6,
#elif defined(VERSION_JP)
        14,
#elif defined(VERSION_US)
        6,
#endif
    },
};

#ifdef VERSION_EU
void* gHcEffectNameTilesByLanguage[5] = { gHcEffectNameTiles, gHcEffectNameFrenchTiles, gHcEffectNameGermanTiles, gHcEffectNameItalianTiles, gHcEffectNameSpanishTiles };
void** gHcEffectNameSpritesByLanguage[5] = { gHcEffectNameFrames, gHcEffectNameFrenchFrames, gHcEffectNameGermanFrames, gHcEffectNameItalianFrames, gHcEffectNameSpanishFrames };
void* gStockNameAttackTilesByLanguage[5] = { gStockNameAttackTiles, gStockNameAttackFrenchTiles, gStockNameAttackGermanTiles, gStockNameAttackItalianTiles, gStockNameAttackSpanishTiles };
void** gStockNameAttackSpritesByLanguage[5] = { gStockNameAttackFrames, gStockNameAttackFrenchFrames, gStockNameAttackGermanFrames, gStockNameAttackItalianFrames, gStockNameAttackSpanishFrames };
void* gStockNameMagicTilesByLanguage[5] = { gStockNameMagicTiles, gStockNameMagicFrenchTiles, gStockNameMagicGermanTiles, gStockNameMagicItalianTiles, gStockNameMagicSpanishTiles };
void** gStockNameMagicSpritesByLanguage[5] = { gStockNameMagicFrames, gStockNameMagicFrenchFrames, gStockNameMagicGermanFrames, gStockNameMagicItalianFrames, gStockNameMagicSpanishFrames };
void* gStockNameFriendTilesByLanguage[5] = { gStockNameFriendTiles, gStockNameFriendFrenchTiles, gStockNameFriendGermanTiles, gStockNameFriendItalianTiles, gStockNameFriendSpanishTiles };
void** gStockNameFriendSpritesByLanguage[5] = { gStockNameFriendFrames, gStockNameFriendFrenchFrames, gStockNameFriendGermanFrames, gStockNameFriendItalianFrames, gStockNameFriendSpanishFrames };
void* gStockNameMmMiracleTilesByLanguage[5] = { gStockNameMmMiracleTiles, gStockNameMmMiracleFrenchTiles, gUnk_0908AF32, gUnk_0908A958, gStockNameMmMiracleSpanishTiles };
void** gStockNameMmMiracleSpritesByLanguage[5] = { gStockNameMmMiracleFrames, gStockNameMmMiracleFrenchFrames, gUnk_09EEA140, gUnkEu_09F75F50, gStockNameMmMiracleSpanishFrames };
void* gStockNameRikuTilesByLanguage[5] = { gStockNameRikuTiles, gStockNameRikuFrenchTiles, gStockNameRikuGermanTiles, gStockNameRikuItalianTiles, gStockNameRikuSpanishTiles };
void** gStockNameRikuSpritesByLanguage[5] = { gStockNameRikuFrames, gStockNameRikuFrenchFrames, gStockNameRikuGermanFrames, gStockNameRikuItalianFrames, gStockNameRikuSpanishFrames };
void* gStockNameBossTilesByLanguage[5] = { gStockNameBossTiles, gStockNameBossFrenchTiles, gStockNameBossGermanTiles, gStockNameBossItalianTiles, gStockNameBossSpanishTiles };
void** gStockNameBossSpritesByLanguage[5] = { gStockNameBossFrames, gStockNameBossFrenchFrames, gStockNameBossGermanFrames, gStockNameBossItalianFrames, gStockNameBossSpanishFrames };
void* gStockNameWorldBossTilesByLanguage[5] = { gStockNameWorldBossTiles, gStockNameWorldBossFrenchTiles, gStockNameWorldBossGermanTiles, gStockNameWorldBossItalianTiles, gStockNameWorldBossSpanishTiles };
void** gStockNameWorldBossSpritesByLanguage[5] = { gStockNameWorldBossFrames, gStockNameWorldBossFrenchFrames, gStockNameWorldBossGermanFrames, gStockNameWorldBossItalianFrames, gStockNameWorldBossSpanishFrames };
#endif

u16 GetCardCpCost(u16 a) {
    s32 n;
    u16 v;
    CardStat* stat;

    if (a & 0x8000) {
        return gCardDefs[a & 0x0FFF].cpCost;
    }

    if ((a & 0x0FFF) <= 0x1C1) {
        stat = (CardStat*)&gCardDefs[a & 0x0FFF].kind;
        n = stat->value;

        if (n == 0) {
            n = 10;
        }

        n--;
        v = stat->cpCost;
        v += (v / 10) * n;
        return v;
    }

    return gCardDefs[a & 0x0FFF].cpCost;
}

u16 GetCardMooglePointValue(u16 a) {
    u16 v;

    if ((a & 0x8000) == 0) {
        v = GetCardCpCost(a) / 5 * 2;
    } else {
        v = GetCardCpCost(a & 0x0FFF) / 5 * 2 + 10;
    }

    return v;
}
