#include <stddef.h>
#include "card_def_data.h"
#include "card_def_assets.h"
#include "sprites_card_pictures.h"
#include "sprite_palettes.h"
#include "card_label_data.h"
#include "card_localized_data.h"
#include "card_label_language_data.h"
#include "mode_test_assets.h"

const CardBack gUnk_08F709B0[5] = {
    {
        gUnk_0905A668, gUnk_0905D564, gUnk_09047A10, gUnk_0905A682, gUnk_0905D64E, gUnk_09047A2A,
    },
    {
        gUnk_09059E94, gUnk_0905ABA0, gUnk_0904723C, gUnk_09059EAE, gUnk_0905AC8A, gUnk_09047256,
    },
    {
        gUnk_0905A3CC, gUnk_0905C778, gUnk_09047774, gUnk_0905A3E6, gUnk_0905C862, gUnk_0904778E,
    },
    {
        gUnk_0905A130, gUnk_0905B98C, gUnk_090474D8, gUnk_0905A14A, gUnk_0905BA76, gUnk_090474F2,
    },
    {
        gUnk_0905A904, gUnk_0905E350, gUnk_09047CAC, gUnk_0905A91E, gUnk_0905E3BA, gUnk_09047CC6,
    },
};

const CardBack gUnk_08F70A28[5] = {
    {
        gUnk_0905A130, gUnk_0905B98C, gUnk_0904A190, gUnk_0905A14A, gUnk_0905BA76, gUnk_0904A1AA,
    },
    {
        gUnk_0905A130, gUnk_0905B98C, gUnk_0904A190, gUnk_0905A14A, gUnk_0905BA76, gUnk_0904A1AA,
    },
    {
        gUnk_0905A130, gUnk_0905B98C, gUnk_0904A190, gUnk_0905A14A, gUnk_0905BA76, gUnk_0904A1AA,
    },
    {
        gUnk_0905A130, gUnk_0905B98C, gUnk_0904A190, gUnk_0905A14A, gUnk_0905BA76, gUnk_0904A1AA,
    },
    {
        gUnk_0905A130, gUnk_0905B98C, gUnk_0904A190, gUnk_0905A14A, gUnk_0905BA76, gUnk_0904A1AA,
    },
};

const u8 gUnk_08F70AA0[3] = "\x81\x9C";

const u8 gUnk_08F70AA4[3] = "\x81\x9B";

const u8 gUnk_08F70AA8[3] = "\x81\x9A";

const u8 gUnk_08F70AAC[3] = "\x81\x99";

// The mod's card table, gCardDefs in src/rogue/rogue_cards.c, starts with these
// same 950 definitions and goes on with its own. This copy is no longer read:
// it stays so that the data after it keeps its address.
const CardDef gCardDefsVanilla[950] = {
#include "card_catalog_defs.inc"
};

const UnkStruct_08F7CBA8 gUnk_08F7CBA8[55] = {
    {
#ifdef VERSION_EU
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
#endif
        0,
        0,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
#endif
        0,
        2,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
#endif
        10,
        1,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
#endif
        11,
        1,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
#endif
        12,
        1,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
#endif
        21,
        1,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
#endif
        31,
        1,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
#endif
        32,
        1,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
#endif
        48,
        50,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
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
        gUnkEu_09F5D574,
#else
        gUnk_09079EB2,
#endif
#ifndef VERSION_EU
#if defined(VERSION_JP)
        28032,
#elif defined(VERSION_US)
        24704,
#endif
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D588,
#elif defined(VERSION_JP)
        gUnkJp_09EC12D4,
#elif defined(VERSION_US)
        gUnkUs_09EE9EF8,
#endif
        0,
        1,
    },
};

const SpriteFrameResourceDef gUnk_08F7CF18[106] = {
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
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
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5EC,
#else
        gUnk_09086C1C,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D600,
#elif defined(VERSION_JP)
        gUnkJp_09EC14A4,
#elif defined(VERSION_US)
        gUnkUs_09EEA0B0,
#endif
        640,
        2,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5EC,
#else
        gUnk_09086C1C,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D600,
#elif defined(VERSION_JP)
        gUnkJp_09EC14A4,
#elif defined(VERSION_US)
        gUnkUs_09EEA0B0,
#endif
        640,
        1,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5EC,
#else
        gUnk_09086C1C,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D600,
#elif defined(VERSION_JP)
        gUnkJp_09EC14A4,
#elif defined(VERSION_US)
        gUnkUs_09EEA0B0,
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
        gUnkEu_09F5D5EC,
#else
        gUnk_09086C1C,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D600,
#elif defined(VERSION_JP)
        gUnkJp_09EC14A4,
#elif defined(VERSION_US)
        gUnkUs_09EEA0B0,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5EC,
#else
        gUnk_09086C1C,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D600,
#elif defined(VERSION_JP)
        gUnkJp_09EC14A4,
#elif defined(VERSION_US)
        gUnkUs_09EEA0B0,
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
        gUnkEu_09F5D5EC,
#else
        gUnk_09086C1C,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D600,
#elif defined(VERSION_JP)
        gUnkJp_09EC14A4,
#elif defined(VERSION_US)
        gUnkUs_09EEA0B0,
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
        gUnkEu_09F5D5EC,
#else
        gUnk_09086C1C,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D600,
#elif defined(VERSION_JP)
        gUnkJp_09EC14A4,
#elif defined(VERSION_US)
        gUnkUs_09EEA0B0,
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
        gUnkEu_09F5D5EC,
#else
        gUnk_09086C1C,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D600,
#elif defined(VERSION_JP)
        gUnkJp_09EC14A4,
#elif defined(VERSION_US)
        gUnkUs_09EEA0B0,
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
        gUnkEu_09F5D5EC,
#else
        gUnk_09086C1C,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D600,
#elif defined(VERSION_JP)
        gUnkJp_09EC14A4,
#elif defined(VERSION_US)
        gUnkUs_09EEA0B0,
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
        gUnkEu_09F5D5EC,
#else
        gUnk_09086C1C,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D600,
#elif defined(VERSION_JP)
        gUnkJp_09EC14A4,
#elif defined(VERSION_US)
        gUnkUs_09EEA0B0,
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
        gUnkEu_09F5D5EC,
#else
        gUnk_09086C1C,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D600,
#elif defined(VERSION_JP)
        gUnkJp_09EC14A4,
#elif defined(VERSION_US)
        gUnkUs_09EEA0B0,
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
        gUnkEu_09F5D5EC,
#else
        gUnk_09086C1C,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D600,
#elif defined(VERSION_JP)
        gUnkJp_09EC14A4,
#elif defined(VERSION_US)
        gUnkUs_09EEA0B0,
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
        gUnkEu_09F5D5EC,
#else
        gUnk_09086C1C,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D600,
#elif defined(VERSION_JP)
        gUnkJp_09EC14A4,
#elif defined(VERSION_US)
        gUnkUs_09EEA0B0,
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
        gUnkEu_09F5D5EC,
#else
        gUnk_09086C1C,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D600,
#elif defined(VERSION_JP)
        gUnkJp_09EC14A4,
#elif defined(VERSION_US)
        gUnkUs_09EEA0B0,
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
        gUnkEu_09F5D614,
#else
        gUnk_0908AF32,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D628,
#elif defined(VERSION_JP)
        gUnkJp_09EC1534,
#elif defined(VERSION_US)
        gUnkUs_09EEA140,
#endif
        640,
        0,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D614,
#else
        gUnk_0908AF32,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D628,
#elif defined(VERSION_JP)
        gUnkJp_09EC1534,
#elif defined(VERSION_US)
        gUnkUs_09EEA140,
#endif
        640,
        0,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
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
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
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
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
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
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
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
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
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
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
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
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
#endif
        640,
        25,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
#endif
        640,
        9,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
#endif
        640,
        10,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
#endif
        640,
        11,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
#endif
        640,
        12,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
#endif
        640,
        13,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
#endif
        640,
        14,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D59C,
#else
        gUnk_09080074,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5B0,
#elif defined(VERSION_JP)
        gUnkJp_09EC13AC,
#elif defined(VERSION_US)
        gUnkUs_09EE9FC0,
#endif
        640,
        15,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
#endif
        640,
        26,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
#endif
        640,
        28,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
#endif
        640,
        0,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
#endif
        640,
        29,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
#endif
        640,
        30,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
#endif
        640,
        31,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
#endif
        640,
        32,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
#endif
        640,
        33,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
#endif
        640,
        34,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
#endif
        640,
        35,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
#endif
        704,
        36,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D5C4,
#else
        gUnk_090822F2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D5D8,
#elif defined(VERSION_JP)
        gUnkJp_09EC13F4,
#elif defined(VERSION_US)
        gUnkUs_09EEA004,
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
        gUnkEu_09F5D63C,
#else
        gUnk_0908A958,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D650,
#elif defined(VERSION_JP)
        gUnkJp_09EC1524,
#elif defined(VERSION_US)
        gUnkUs_09EEA130,
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
        gUnkEu_09F5D63C,
#else
        gUnk_0908A958,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D650,
#elif defined(VERSION_JP)
        gUnkJp_09EC1524,
#elif defined(VERSION_US)
        gUnkUs_09EEA130,
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
        gUnkEu_09F5D63C,
#else
        gUnk_0908A958,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D650,
#elif defined(VERSION_JP)
        gUnkJp_09EC1524,
#elif defined(VERSION_US)
        gUnkUs_09EEA130,
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
        gUnkEu_09F5D664,
#else
        gUnk_09087DD2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D678,
#elif defined(VERSION_JP)
        gUnkJp_09EC14C8,
#elif defined(VERSION_US)
        gUnkUs_09EEA0D4,
#endif
        640,
        0,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D68C,
#else
        gUnk_09089C16,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D6A0,
#elif defined(VERSION_JP)
        gUnkJp_09EC1508,
#elif defined(VERSION_US)
        gUnkUs_09EEA114,
#endif
        640,
        0,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D68C,
#else
        gUnk_09089C16,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D6A0,
#elif defined(VERSION_JP)
        gUnkJp_09EC1508,
#elif defined(VERSION_US)
        gUnkUs_09EEA114,
#endif
        640,
        1,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D68C,
#else
        gUnk_09089C16,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D6A0,
#elif defined(VERSION_JP)
        gUnkJp_09EC1508,
#elif defined(VERSION_US)
        gUnkUs_09EEA114,
#endif
        640,
        2,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D68C,
#else
        gUnk_09089C16,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D6A0,
#elif defined(VERSION_JP)
        gUnkJp_09EC1508,
#elif defined(VERSION_US)
        gUnkUs_09EEA114,
#endif
        640,
        3,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D664,
#else
        gUnk_09087DD2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D678,
#elif defined(VERSION_JP)
        gUnkJp_09EC14C8,
#elif defined(VERSION_US)
        gUnkUs_09EEA0D4,
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
        gUnkEu_09F5D68C,
#else
        gUnk_09089C16,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D6A0,
#elif defined(VERSION_JP)
        gUnkJp_09EC1508,
#elif defined(VERSION_US)
        gUnkUs_09EEA114,
#endif
        640,
        4,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D68C,
#else
        gUnk_09089C16,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D6A0,
#elif defined(VERSION_JP)
        gUnkJp_09EC1508,
#elif defined(VERSION_US)
        gUnkUs_09EEA114,
#endif
        640,
        5,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D664,
#else
        gUnk_09087DD2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D678,
#elif defined(VERSION_JP)
        gUnkJp_09EC14C8,
#elif defined(VERSION_US)
        gUnkUs_09EEA0D4,
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
        gUnkEu_09F5D664,
#else
        gUnk_09087DD2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D678,
#elif defined(VERSION_JP)
        gUnkJp_09EC14C8,
#elif defined(VERSION_US)
        gUnkUs_09EEA0D4,
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
        gUnkEu_09F5D664,
#else
        gUnk_09087DD2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D678,
#elif defined(VERSION_JP)
        gUnkJp_09EC14C8,
#elif defined(VERSION_US)
        gUnkUs_09EEA0D4,
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
        gUnkEu_09F5D664,
#else
        gUnk_09087DD2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D678,
#elif defined(VERSION_JP)
        gUnkJp_09EC14C8,
#elif defined(VERSION_US)
        gUnkUs_09EEA0D4,
#endif
        640,
        5,
    },
    {
#ifdef VERSION_EU
        gUnkEu_09F5D664,
#else
        gUnk_09087DD2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D678,
#elif defined(VERSION_JP)
        gUnkJp_09EC14C8,
#elif defined(VERSION_US)
        gUnkUs_09EEA0D4,
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
        gUnkEu_09F5D664,
#else
        gUnk_09087DD2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D678,
#elif defined(VERSION_JP)
        gUnkJp_09EC14C8,
#elif defined(VERSION_US)
        gUnkUs_09EEA0D4,
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
        gUnkEu_09F5D664,
#else
        gUnk_09087DD2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D678,
#elif defined(VERSION_JP)
        gUnkJp_09EC14C8,
#elif defined(VERSION_US)
        gUnkUs_09EEA0D4,
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
        gUnkEu_09F5D664,
#else
        gUnk_09087DD2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D678,
#elif defined(VERSION_JP)
        gUnkJp_09EC14C8,
#elif defined(VERSION_US)
        gUnkUs_09EEA0D4,
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
        gUnkEu_09F5D664,
#else
        gUnk_09087DD2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D678,
#elif defined(VERSION_JP)
        gUnkJp_09EC14C8,
#elif defined(VERSION_US)
        gUnkUs_09EEA0D4,
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
        gUnkEu_09F5D664,
#else
        gUnk_09087DD2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D678,
#elif defined(VERSION_JP)
        gUnkJp_09EC14C8,
#elif defined(VERSION_US)
        gUnkUs_09EEA0D4,
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
        gUnkEu_09F5D664,
#else
        gUnk_09087DD2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D678,
#elif defined(VERSION_JP)
        gUnkJp_09EC14C8,
#elif defined(VERSION_US)
        gUnkUs_09EEA0D4,
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
        gUnkEu_09F5D664,
#else
        gUnk_09087DD2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D678,
#elif defined(VERSION_JP)
        gUnkJp_09EC14C8,
#elif defined(VERSION_US)
        gUnkUs_09EEA0D4,
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
        gUnkEu_09F5D664,
#else
        gUnk_09087DD2,
#endif
#if defined(VERSION_EU)
        gUnkEu_09F5D678,
#elif defined(VERSION_JP)
        gUnkJp_09EC14C8,
#elif defined(VERSION_US)
        gUnkUs_09EEA0D4,
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
void* gUnkEu_09F5D574[5] = { gUnk_09079EB2, gUnkEu_0910DD2E, gUnkEu_09121002, gUnkEu_0911AB16, gUnkEu_09114860 };
void** gUnkEu_09F5D588[5] = { gUnkEu_09F753D0, gUnkEu_09F75498, gUnkEu_09F756F0, gUnkEu_09F75628, gUnkEu_09F75560 };
void* gUnkEu_09F5D59C[5] = { gUnk_09080074, gUnkEu_091292D6, gUnkEu_0912F83E, gUnkEu_0912D736, gUnkEu_0912B47C };
void** gUnkEu_09F5D5B0[5] = { gUnkEu_09F757B8, gUnkEu_09F757FC, gUnkEu_09F758C8, gUnkEu_09F75884, gUnkEu_09F75840 };
void* gUnkEu_09F5D5C4[5] = { gUnk_090822F2, gUnkEu_091367CC, gUnkEu_0914583A, gUnkEu_091407A2, gUnkEu_0913B7F4 };
void** gUnkEu_09F5D5D8[5] = { gUnkEu_09F7590C, gUnkEu_09F759B8, gUnkEu_09F75BBC, gUnkEu_09F75B10, gUnkEu_09F75A64 };
void* gUnkEu_09F5D5EC[5] = { gUnk_09086C1C, gUnkEu_0914B41E, gUnkEu_0914E89E, gUnkEu_0914D7B0, gUnkEu_0914C648 };
void** gUnkEu_09F5D600[5] = { gUnkEu_09F75C68, gUnkEu_09F75C8C, gUnkEu_09F75CF8, gUnkEu_09F75CD4, gUnkEu_09F75CB0 };
void* gUnkEu_09F5D614[5] = { gUnkEu_09160A0E, gUnkEu_09160C2A, gUnk_0908AF32, gUnk_0908A958, gUnkEu_09160E46 };
void** gUnkEu_09F5D628[5] = { gUnkEu_09F75F38, gUnkEu_09F75F40, gUnkEu_09F75F58, gUnkEu_09F75F50, gUnkEu_09F75F48 };
void* gUnkEu_09F5D63C[5] = { gUnkEu_0915E7D4, gUnkEu_0915EDDA, gUnkEu_091602F4, gUnkEu_0915FC28, gUnkEu_0915F468 };
void** gUnkEu_09F5D650[5] = { gUnkEu_09F75EE8, gUnkEu_09F75EF8, gUnkEu_09F75F28, gUnkEu_09F75F18, gUnkEu_09F75F08 };
void* gUnkEu_09F5D664[5] = { gUnk_09087DD2, gUnkEu_091519CE, gUnkEu_091581F6, gUnkEu_09155EFE, gUnkEu_09153BC6 };
void** gUnkEu_09F5D678[5] = { gUnkEu_09F75D1C, gUnkEu_09F75D5C, gUnkEu_09F75E1C, gUnkEu_09F75DDC, gUnkEu_09F75D9C };
void* gUnkEu_09F5D68C[5] = { gUnk_09089C16, gUnkEu_0915B004, gUnkEu_0915DAD4, gUnkEu_0915CC96, gUnkEu_0915BE46 };
void** gUnkEu_09F5D6A0[5] = { gUnkEu_09F75E5C, gUnkEu_09F75E78, gUnkEu_09F75ECC, gUnkEu_09F75EB0, gUnkEu_09F75E94 };
#endif
