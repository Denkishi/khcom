/**
 * mode_chkbtl.c
 * Debug Battle Check
 */

#include "macros.h"
#include "mode_chkbtl.h"
#include "gba/keys.h"
#include "world_types.h"
#include "fade.h"
#include "battle_debug_types.h"
#include "battle_work.h"
#include "card_api.h"
#include "display.h"
#include "engine_math.h"
#include "game_state.h"
#include "key.h"
#include "mode.h"
#include "mode_battle_data.h"
#include "player_progression_types.h"
#include "registration_data.h"
#include <stddef.h>
#include "system_state.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"
#include "debug_text.h"

static ChkBtlWork sChkBtlWork;

BtlWork* gBtlWork EWRAM_COMMON(4);
u16 gVsBattleMinY EWRAM_COMMON(4);
u16 gVsBattleMaxY EWRAM_COMMON(4);
u16 gVsBattleHalfWidth EWRAM_COMMON(4);

static const ChkBtlEntry sChkBtlEntries[209] = {
    { WORLD_TRAVERSE_TOWN, 0, 10, NULL, "\x82\x73\x82\x76\x82\x6d\x82\x4f" },
    { WORLD_TRAVERSE_TOWN, 0, 11, NULL, "\x82\x73\x82\x76\x82\x6d\x82\x50" },
    { WORLD_TRAVERSE_TOWN, 0, 12, NULL, "\x82\x73\x82\x76\x82\x6d\x82\x51" },
    { WORLD_TRAVERSE_TOWN, 0, 13, NULL, "\x82\x73\x82\x76\x82\x6d\x82\x52" },
    { WORLD_TRAVERSE_TOWN, 0, 14, NULL, "\x82\x73\x82\x76\x82\x6d\x82\x53" },
    { WORLD_TRAVERSE_TOWN, 0, 15, NULL, "\x82\x73\x82\x76\x82\x6d\x82\x54" },
    { WORLD_TRAVERSE_TOWN, 0, 16, NULL, "\x82\x73\x82\x76\x82\x6d\x82\x55" },
    { WORLD_TRAVERSE_TOWN, 0, 17, NULL, "\x82\x73\x82\x76\x82\x6d\x82\x56" },
    { WORLD_TRAVERSE_TOWN, 0, 18, NULL, "\x82\x73\x82\x76\x82\x6d\x82\x57" },
    { WORLD_TRAVERSE_TOWN, 0, 19, NULL, "\x82\x73\x82\x76\x82\x6d\x82\x58" },
    { WORLD_OLYMPUS_COLISEUM, 0, 30, NULL, "\x82\x62\x82\x6e\x82\x6b\x82\x4f" },
    { WORLD_OLYMPUS_COLISEUM, 0, 31, NULL, "\x82\x62\x82\x6e\x82\x6b\x82\x50" },
    { WORLD_OLYMPUS_COLISEUM, 0, 32, NULL, "\x82\x62\x82\x6e\x82\x6b\x82\x51" },
    { WORLD_OLYMPUS_COLISEUM, 0, 33, NULL, "\x82\x62\x82\x6e\x82\x6b\x82\x52" },
    { WORLD_OLYMPUS_COLISEUM, 0, 34, NULL, "\x82\x62\x82\x6e\x82\x6b\x82\x53" },
    { WORLD_OLYMPUS_COLISEUM, 0, 35, NULL, "\x82\x62\x82\x6e\x82\x6b\x82\x54" },
    { WORLD_OLYMPUS_COLISEUM, 0, 36, NULL, "\x82\x62\x82\x6e\x82\x6b\x82\x55" },
    { WORLD_OLYMPUS_COLISEUM, 0, 37, NULL, "\x82\x62\x82\x6e\x82\x6b\x82\x56" },
    { WORLD_OLYMPUS_COLISEUM, 0, 38, NULL, "\x82\x62\x82\x6e\x82\x6b\x82\x57" },
    { WORLD_OLYMPUS_COLISEUM, 0, 39, NULL, "\x82\x62\x82\x6e\x82\x6b\x82\x58" },
    { WORLD_WONDERLAND, 0, 20, NULL, "\x82\x76\x82\x6e\x82\x6d\x82\x4f" },
    { WORLD_WONDERLAND, 0, 21, NULL, "\x82\x76\x82\x6e\x82\x6d\x82\x50" },
    { WORLD_WONDERLAND, 0, 22, NULL, "\x82\x76\x82\x6e\x82\x6d\x82\x51" },
    { WORLD_WONDERLAND, 0, 23, NULL, "\x82\x76\x82\x6e\x82\x6d\x82\x52" },
    { WORLD_WONDERLAND, 0, 24, NULL, "\x82\x76\x82\x6e\x82\x6d\x82\x53" },
    { WORLD_WONDERLAND, 0, 25, NULL, "\x82\x76\x82\x6e\x82\x6d\x82\x54" },
    { WORLD_WONDERLAND, 0, 26, NULL, "\x82\x76\x82\x6e\x82\x6d\x82\x55" },
    { WORLD_WONDERLAND, 0, 27, NULL, "\x82\x76\x82\x6e\x82\x6d\x82\x56" },
    { WORLD_WONDERLAND, 0, 28, NULL, "\x82\x76\x82\x6e\x82\x6d\x82\x57" },
    { WORLD_WONDERLAND, 0, 29, NULL, "\x82\x76\x82\x6e\x82\x6d\x82\x58" },
    { WORLD_MONSTRO, 0, 80, NULL, "\x82\x6c\x82\x6e\x82\x6d\x82\x4f" },
    { WORLD_MONSTRO, 0, 81, NULL, "\x82\x6c\x82\x6e\x82\x6d\x82\x50" },
    { WORLD_MONSTRO, 0, 82, NULL, "\x82\x6c\x82\x6e\x82\x6d\x82\x51" },
    { WORLD_MONSTRO, 0, 83, NULL, "\x82\x6c\x82\x6e\x82\x6d\x82\x52" },
    { WORLD_MONSTRO, 0, 84, NULL, "\x82\x6c\x82\x6e\x82\x6d\x82\x53" },
    { WORLD_MONSTRO, 0, 85, NULL, "\x82\x6c\x82\x6e\x82\x6d\x82\x54" },
    { WORLD_MONSTRO, 0, 86, NULL, "\x82\x6c\x82\x6e\x82\x6d\x82\x55" },
    { WORLD_MONSTRO, 0, 87, NULL, "\x82\x6c\x82\x6e\x82\x6d\x82\x56" },
    { WORLD_MONSTRO, 0, 88, NULL, "\x82\x6c\x82\x6e\x82\x6d\x82\x57" },
    { WORLD_MONSTRO, 0, 89, NULL, "\x82\x6c\x82\x6e\x82\x6d\x82\x58" },
    { WORLD_HALLOWEEN_TOWN, 0, 60, NULL, "\x82\x67\x82\x60\x82\x6b\x82\x4f" },
    { WORLD_HALLOWEEN_TOWN, 0, 61, NULL, "\x82\x67\x82\x60\x82\x6b\x82\x50" },
    { WORLD_HALLOWEEN_TOWN, 0, 62, NULL, "\x82\x67\x82\x60\x82\x6b\x82\x51" },
    { WORLD_HALLOWEEN_TOWN, 0, 63, NULL, "\x82\x67\x82\x60\x82\x6b\x82\x52" },
    { WORLD_HALLOWEEN_TOWN, 0, 64, NULL, "\x82\x67\x82\x60\x82\x6b\x82\x53" },
    { WORLD_HALLOWEEN_TOWN, 0, 65, NULL, "\x82\x67\x82\x60\x82\x6b\x82\x54" },
    { WORLD_HALLOWEEN_TOWN, 0, 66, NULL, "\x82\x67\x82\x60\x82\x6b\x82\x55" },
    { WORLD_HALLOWEEN_TOWN, 0, 67, NULL, "\x82\x67\x82\x60\x82\x6b\x82\x56" },
    { WORLD_HALLOWEEN_TOWN, 0, 68, NULL, "\x82\x67\x82\x60\x82\x6b\x82\x57" },
    { WORLD_HALLOWEEN_TOWN, 0, 69, NULL, "\x82\x67\x82\x60\x82\x6b\x82\x58" },
    { WORLD_ATLANTICA, 0, 50, NULL, "\x82\x60\x82\x73\x82\x6b\x82\x4f" },
    { WORLD_ATLANTICA, 0, 51, NULL, "\x82\x60\x82\x73\x82\x6b\x82\x50" },
    { WORLD_ATLANTICA, 0, 52, NULL, "\x82\x60\x82\x73\x82\x6b\x82\x51" },
    { WORLD_ATLANTICA, 0, 53, NULL, "\x82\x60\x82\x73\x82\x6b\x82\x52" },
    { WORLD_ATLANTICA, 0, 54, NULL, "\x82\x60\x82\x73\x82\x6b\x82\x53" },
    { WORLD_ATLANTICA, 0, 55, NULL, "\x82\x60\x82\x73\x82\x6b\x82\x54" },
    { WORLD_ATLANTICA, 0, 56, NULL, "\x82\x60\x82\x73\x82\x6b\x82\x55" },
    { WORLD_ATLANTICA, 0, 57, NULL, "\x82\x60\x82\x73\x82\x6b\x82\x56" },
    { WORLD_ATLANTICA, 0, 58, NULL, "\x82\x60\x82\x73\x82\x6b\x82\x57" },
    { WORLD_ATLANTICA, 0, 59, NULL, "\x82\x60\x82\x73\x82\x6b\x82\x58" },
    { WORLD_AGRABAH, 0, 40, NULL, "\x82\x60\x82\x66\x82\x71\x82\x4f" },
    { WORLD_AGRABAH, 0, 41, NULL, "\x82\x60\x82\x66\x82\x71\x82\x50" },
    { WORLD_AGRABAH, 0, 42, NULL, "\x82\x60\x82\x66\x82\x71\x82\x51" },
    { WORLD_AGRABAH, 0, 43, NULL, "\x82\x60\x82\x66\x82\x71\x82\x52" },
    { WORLD_AGRABAH, 0, 44, NULL, "\x82\x60\x82\x66\x82\x71\x82\x53" },
    { WORLD_AGRABAH, 0, 45, NULL, "\x82\x60\x82\x66\x82\x71\x82\x54" },
    { WORLD_AGRABAH, 0, 46, NULL, "\x82\x60\x82\x66\x82\x71\x82\x55" },
    { WORLD_AGRABAH, 0, 47, NULL, "\x82\x60\x82\x66\x82\x71\x82\x56" },
    { WORLD_AGRABAH, 0, 48, NULL, "\x82\x60\x82\x66\x82\x71\x82\x57" },
    { WORLD_AGRABAH, 0, 49, NULL, "\x82\x60\x82\x66\x82\x71\x82\x58" },
    { WORLD_NEVER_LAND, 0, 70, NULL, "\x82\x6d\x82\x64\x82\x75\x82\x4f" },
    { WORLD_NEVER_LAND, 0, 71, NULL, "\x82\x6d\x82\x64\x82\x75\x82\x50" },
    { WORLD_NEVER_LAND, 0, 72, NULL, "\x82\x6d\x82\x64\x82\x75\x82\x51" },
    { WORLD_NEVER_LAND, 0, 73, NULL, "\x82\x6d\x82\x64\x82\x75\x82\x52" },
    { WORLD_NEVER_LAND, 0, 74, NULL, "\x82\x6d\x82\x64\x82\x75\x82\x53" },
    { WORLD_NEVER_LAND, 0, 75, NULL, "\x82\x6d\x82\x64\x82\x75\x82\x54" },
    { WORLD_NEVER_LAND, 0, 76, NULL, "\x82\x6d\x82\x64\x82\x75\x82\x55" },
    { WORLD_NEVER_LAND, 0, 77, NULL, "\x82\x6d\x82\x64\x82\x75\x82\x56" },
    { WORLD_NEVER_LAND, 0, 78, NULL, "\x82\x6d\x82\x64\x82\x75\x82\x57" },
    { WORLD_NEVER_LAND, 0, 79, NULL, "\x82\x6d\x82\x64\x82\x75\x82\x58" },
    { WORLD_HOLLOW_BASTION, 0, 100, NULL, "\x82\x67\x82\x6e\x82\x6b\x82\x4f" },
    { WORLD_HOLLOW_BASTION, 0, 101, NULL, "\x82\x67\x82\x6e\x82\x6b\x82\x50" },
    { WORLD_HOLLOW_BASTION, 0, 102, NULL, "\x82\x67\x82\x6e\x82\x6b\x82\x51" },
    { WORLD_HOLLOW_BASTION, 0, 103, NULL, "\x82\x67\x82\x6e\x82\x6b\x82\x52" },
    { WORLD_HOLLOW_BASTION, 0, 104, NULL, "\x82\x67\x82\x6e\x82\x6b\x82\x53" },
    { WORLD_HOLLOW_BASTION, 0, 105, NULL, "\x82\x67\x82\x6e\x82\x6b\x82\x54" },
    { WORLD_HOLLOW_BASTION, 0, 106, NULL, "\x82\x67\x82\x6e\x82\x6b\x82\x55" },
    { WORLD_HOLLOW_BASTION, 0, 107, NULL, "\x82\x67\x82\x6e\x82\x6b\x82\x56" },
    { WORLD_HOLLOW_BASTION, 0, 108, NULL, "\x82\x67\x82\x6e\x82\x6b\x82\x57" },
    { WORLD_HOLLOW_BASTION, 0, 109, NULL, "\x82\x67\x82\x6e\x82\x6b\x82\x58" },
    { WORLD_TWILIGHT_TOWN, 0, 90, NULL, "\x82\x73\x82\x76\x82\x68\x82\x4f" },
    { WORLD_TWILIGHT_TOWN, 0, 91, NULL, "\x82\x73\x82\x76\x82\x68\x82\x50" },
    { WORLD_TWILIGHT_TOWN, 0, 92, NULL, "\x82\x73\x82\x76\x82\x68\x82\x51" },
    { WORLD_TWILIGHT_TOWN, 0, 93, NULL, "\x82\x73\x82\x76\x82\x68\x82\x52" },
    { WORLD_TWILIGHT_TOWN, 0, 94, NULL, "\x82\x73\x82\x76\x82\x68\x82\x53" },
    { WORLD_TWILIGHT_TOWN, 0, 95, NULL, "\x82\x73\x82\x76\x82\x68\x82\x54" },
    { WORLD_TWILIGHT_TOWN, 0, 96, NULL, "\x82\x73\x82\x76\x82\x68\x82\x55" },
    { WORLD_TWILIGHT_TOWN, 0, 97, NULL, "\x82\x73\x82\x76\x82\x68\x82\x56" },
    { WORLD_TWILIGHT_TOWN, 0, 98, NULL, "\x82\x73\x82\x76\x82\x68\x82\x57" },
    { WORLD_TWILIGHT_TOWN, 0, 99, NULL, "\x82\x73\x82\x76\x82\x68\x82\x58" },
    { WORLD_DESTINY_ISLANDS, 0, 0, NULL, "\x82\x63\x82\x64\x82\x72\x82\x4f" },
    { WORLD_DESTINY_ISLANDS, 0, 1, NULL, "\x82\x63\x82\x64\x82\x72\x82\x50" },
    { WORLD_DESTINY_ISLANDS, 0, 2, NULL, "\x82\x63\x82\x64\x82\x72\x82\x51" },
    { WORLD_DESTINY_ISLANDS, 0, 3, NULL, "\x82\x63\x82\x64\x82\x72\x82\x52" },
    { WORLD_DESTINY_ISLANDS, 0, 4, NULL, "\x82\x63\x82\x64\x82\x72\x82\x53" },
    { WORLD_DESTINY_ISLANDS, 0, 5, NULL, "\x82\x63\x82\x64\x82\x72\x82\x54" },
    { WORLD_DESTINY_ISLANDS, 0, 6, NULL, "\x82\x63\x82\x64\x82\x72\x82\x55" },
    { WORLD_DESTINY_ISLANDS, 0, 7, NULL, "\x82\x63\x82\x64\x82\x72\x82\x56" },
    { WORLD_DESTINY_ISLANDS, 0, 8, NULL, "\x82\x63\x82\x64\x82\x72\x82\x57" },
    { WORLD_DESTINY_ISLANDS, 0, 9, NULL, "\x82\x63\x82\x64\x82\x72\x82\x58" },
    { WORLD_CASTLE_OBLIVION, 0, 110, NULL, "\x82\x62\x82\x72\x82\x6b\x82\x4f" },
    { WORLD_CASTLE_OBLIVION, 0, 111, NULL, "\x82\x62\x82\x72\x82\x6b\x82\x50" },
    { WORLD_CASTLE_OBLIVION, 0, 112, NULL, "\x82\x62\x82\x72\x82\x6b\x82\x51" },
    { WORLD_CASTLE_OBLIVION, 0, 113, NULL, "\x82\x62\x82\x72\x82\x6b\x82\x52" },
    { WORLD_CASTLE_OBLIVION, 0, 114, NULL, "\x82\x62\x82\x72\x82\x6b\x82\x53" },
    { WORLD_CASTLE_OBLIVION, 0, 115, NULL, "\x82\x62\x82\x72\x82\x6b\x82\x54" },
    { WORLD_CASTLE_OBLIVION, 0, 116, NULL, "\x82\x62\x82\x72\x82\x6b\x82\x55" },
    { WORLD_CASTLE_OBLIVION, 0, 117, NULL, "\x82\x62\x82\x72\x82\x6b\x82\x56" },
    { WORLD_CASTLE_OBLIVION, 0, 118, NULL, "\x82\x62\x82\x72\x82\x6b\x82\x57" },
    { WORLD_CASTLE_OBLIVION, 0, 119, NULL, "\x82\x62\x82\x72\x82\x6b\x82\x58" },
    { WORLD_WONDERLAND, 0, 120, NULL, "\x82\x73\x82\x71\x82\x74\x82\x6c\x82\x6f" },
    { WORLD_MONSTRO, 0, 121, NULL, "\x82\x72\x82\x67\x82\x60\x82\x63\x82\x6e\x82\x76\x82\x50\x82\x4f\x82\x4f" },
    { WORLD_HALLOWEEN_TOWN, 0, 122, NULL, "\x82\x64\x82\x75\x82\x73\x81\x7c\x82\x67\x82\x60\x82\x6b" },
    { WORLD_AGRABAH, 0, 123, NULL, "\x82\x64\x82\x75\x82\x73\x81\x7c\x82\x60\x82\x66\x82\x71\x82\x50" },
    { WORLD_AGRABAH, 0, 124, NULL, "\x82\x64\x82\x75\x82\x73\x81\x7c\x82\x60\x82\x66\x82\x71\x82\x51" },
    { WORLD_NEVER_LAND, 0, 125, NULL, "\x82\x61\x82\x60\x82\x71\x82\x71\x82\x64\x82\x6b\x82\x4f" },
    { WORLD_NEVER_LAND, 0, 126, NULL, "\x82\x61\x82\x60\x82\x71\x82\x71\x82\x64\x82\x6b\x82\x50" },
    { WORLD_NEVER_LAND, 0, 127, NULL, "\x82\x61\x82\x60\x82\x71\x82\x71\x82\x64\x82\x6b\x82\x51" },
    { WORLD_HOLLOW_BASTION, 0, 128, NULL, "\x82\x76\x81\x5c\x82\x6c\x82\x74\x82\x72\x82\x67\x82\x71\x82\x6e\x82\x6e\x82\x6c\x82\x4f" },
    { WORLD_HOLLOW_BASTION, 0, 129, NULL, "\x82\x76\x81\x5c\x82\x6c\x82\x74\x82\x72\x82\x67\x82\x71\x82\x6e\x82\x6e\x82\x6c\x82\x50" },
    { WORLD_HOLLOW_BASTION, 0, 130, NULL, "\x82\x76\x81\x5c\x82\x6c\x82\x74\x82\x72\x82\x67\x82\x71\x82\x6e\x82\x6e\x82\x6c\x82\x51" },
    { WORLD_AGRABAH, 0, 131, NULL, "\x82\x61\x81\x7c\x82\x65\x82\x74\x82\x6d\x82\x66\x82\x74\x82\x72\x82\x4f" },
    { WORLD_AGRABAH, 0, 132, NULL, "\x82\x61\x81\x7c\x82\x65\x82\x74\x82\x6d\x82\x66\x82\x74\x82\x72\x82\x50" },
    { WORLD_AGRABAH, 0, 133, NULL, "\x82\x61\x81\x7c\x82\x65\x82\x74\x82\x6d\x82\x66\x82\x74\x82\x72\x82\x51" },
    { WORLD_HOLLOW_BASTION, 0, 134, NULL, "\x82\x71\x82\x6a\x81\x40\x82\x67\x82\x6e\x82\x6b\x82\x4f" },
    { WORLD_HOLLOW_BASTION, 0, 135, NULL, "\x82\x71\x82\x6a\x81\x40\x82\x67\x82\x6e\x82\x6b\x82\x50" },
    { WORLD_HOLLOW_BASTION, 0, 136, NULL, "\x82\x71\x82\x6a\x81\x40\x82\x67\x82\x6e\x82\x6b\x82\x51" },
    { WORLD_HOLLOW_BASTION, 0, 137, NULL, "\x82\x71\x82\x6a\x81\x40\x82\x67\x82\x6e\x82\x6b\x82\x52" },
    { WORLD_HOLLOW_BASTION, 0, 138, NULL, "\x82\x71\x82\x6a\x81\x40\x82\x67\x82\x6e\x82\x6b\x82\x53" },
    { WORLD_HOLLOW_BASTION, 0, 139, NULL, "\x82\x71\x82\x6a\x81\x40\x82\x67\x82\x6e\x82\x6b\x82\x54" },
    { WORLD_HOLLOW_BASTION, 0, 140, NULL, "\x82\x71\x82\x6a\x81\x40\x82\x67\x82\x6e\x82\x6b\x82\x55" },
    { WORLD_HOLLOW_BASTION, 0, 141, NULL, "\x82\x71\x82\x6a\x81\x40\x82\x67\x82\x6e\x82\x6b\x82\x56" },
    { WORLD_HOLLOW_BASTION, 0, 142, NULL, "\x82\x71\x82\x6a\x81\x40\x82\x67\x82\x6e\x82\x6b\x82\x57" },
    { WORLD_HOLLOW_BASTION, 0, 143, NULL, "\x82\x71\x82\x6a\x81\x40\x82\x67\x82\x6e\x82\x6b\x82\x58" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy00, "\x82\x64\x82\x6c\x82\x78\x82\x4f\x82\x4f" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy01, "\x82\x64\x82\x6c\x82\x78\x82\x4f\x82\x50" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy02, "\x82\x64\x82\x6c\x82\x78\x82\x4f\x82\x51" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy03, "\x82\x64\x82\x6c\x82\x78\x82\x4f\x82\x52" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy04, "\x82\x64\x82\x6c\x82\x78\x82\x4f\x82\x53" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy06, "\x82\x64\x82\x6c\x82\x78\x82\x4f\x82\x55" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy07, "\x82\x64\x82\x6c\x82\x78\x82\x4f\x82\x56" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy08, "\x82\x64\x82\x6c\x82\x78\x82\x4f\x82\x57" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy14, "\x82\x64\x82\x6c\x82\x78\x82\x50\x82\x53" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy15, "\x82\x64\x82\x6c\x82\x78\x82\x50\x82\x54" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy16, "\x82\x64\x82\x6c\x82\x78\x82\x50\x82\x55" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy18, "\x82\x64\x82\x6c\x82\x78\x82\x50\x82\x57" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy19, "\x82\x64\x82\x6c\x82\x78\x82\x50\x82\x58" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy21, "\x82\x64\x82\x6c\x82\x78\x82\x51\x82\x50" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy22, "\x82\x64\x82\x6c\x82\x78\x82\x51\x82\x51" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy23, "\x82\x64\x82\x6c\x82\x78\x82\x51\x82\x52" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy25, "\x82\x64\x82\x6c\x82\x78\x82\x51\x82\x54" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy26, "\x82\x64\x82\x6c\x82\x78\x82\x51\x82\x55" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy27, "\x82\x64\x82\x6c\x82\x78\x82\x51\x82\x56" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy28, "\x82\x64\x82\x6c\x82\x78\x82\x51\x82\x57" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy29, "\x82\x64\x82\x6c\x82\x78\x82\x51\x82\x58" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy30, "\x82\x64\x82\x6c\x82\x78\x82\x52\x82\x4f" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy31, "\x82\x64\x82\x6c\x82\x78\x82\x52\x82\x50" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy37, "\x82\x64\x82\x6c\x82\x78\x82\x52\x82\x56" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy38, "\x82\x64\x82\x6c\x82\x78\x82\x52\x82\x57" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy39, "\x82\x64\x82\x6c\x82\x78\x82\x52\x82\x58" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy41, "\x82\x64\x82\x6c\x82\x78\x82\x53\x82\x50" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy44, "\x82\x64\x82\x6c\x82\x78\x82\x53\x82\x53" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy81, "\x82\x64\x82\x6c\x82\x78\x82\x57\x82\x50" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy82, "\x82\x64\x82\x6c\x82\x78\x82\x57\x82\x51" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmy83, "\x82\x64\x82\x6c\x82\x78\x82\x57\x82\x52" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmyTrumpH, "\x82\x67\x82\x64\x82\x60\x82\x71\x82\x73" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmyTrumpS, "\x82\x72\x82\x6f\x82\x60\x82\x63\x82\x64" },
    { WORLD_NEVER_LAND, 2, 158, NULL, "\x82\x67\x82\x6e\x82\x6e\x82\x6a\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_OLYMPUS_COLISEUM, 2, 159, NULL, "\x82\x62\x82\x6b\x82\x6e\x82\x74\x82\x63\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_OLYMPUS_COLISEUM, 2, 160, NULL, "\x82\x67\x82\x60\x82\x63\x82\x64\x82\x72\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 161, NULL, "\x82\x71\x82\x68\x82\x6a\x82\x74\x82\x50\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 168, NULL, "\x82\x71\x82\x68\x82\x6a\x82\x74\x82\x51\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 169, NULL, "\x82\x71\x82\x68\x82\x6a\x82\x74\x82\x52\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 170, NULL, "\x82\x71\x82\x68\x82\x6a\x82\x74\x82\x53\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 171, NULL, "\x82\x71\x82\x68\x82\x6a\x82\x74\x82\x54\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 172, NULL, "\x82\x71\x82\x68\x82\x6a\x82\x74\x82\x55\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 162, NULL, "\x82\x60\x82\x77\x82\x64\x82\x6b\x82\x50\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 173, NULL, "\x82\x60\x82\x77\x82\x64\x82\x6b\x82\x51\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 163, NULL, "\x82\x6b\x82\x60\x82\x71\x82\x77\x82\x64\x82\x6d\x82\x60\x82\x50\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 174, NULL, "\x82\x6b\x82\x60\x82\x71\x82\x77\x82\x64\x82\x6d\x82\x60\x82\x51\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 164, NULL, "\x82\x75\x82\x64\x82\x77\x82\x64\x82\x6d\x82\x50\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 175, NULL, "\x82\x75\x82\x64\x82\x77\x82\x64\x82\x6d\x82\x51\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 176, NULL, "\x82\x75\x82\x64\x82\x77\x82\x64\x82\x6d\x82\x52\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 165, NULL, "\x82\x6c\x82\x60\x82\x71\x82\x6b\x82\x74\x82\x77\x82\x68\x82\x60\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 166, NULL, "\x82\x60\x82\x6d\x82\x72\x82\x64\x82\x6c\x82\x50\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 177, NULL, "\x82\x60\x82\x6d\x82\x72\x82\x64\x82\x6c\x82\x51\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_CASTLE_OBLIVION, 2, 167, NULL, "\x82\x6b\x82\x64\x82\x77\x82\x60\x82\x64\x82\x74\x82\x72\x81\x69\x82\x67\x82\x74\x82\x6c\x81\x6a" },
    { WORLD_MONSTRO, 2, 152, NULL, "\x82\x6f\x82\x60\x82\x71\x82\x60\x82\x72\x82\x68\x82\x73\x82\x64\x82\x62\x82\x60\x82\x66\x82\x64" },
    { WORLD_DESTINY_ISLANDS, 2, 154, NULL, "\x82\x63\x82\x60\x82\x71\x82\x6a\x82\x72\x82\x68\x82\x63\x82\x64" },
    { WORLD_TRAVERSE_TOWN, 2, 148, NULL, "\x82\x66\x82\x74\x82\x60\x82\x71\x82\x63\x82\x60\x82\x71\x82\x6e\x82\x6c\x82\x6e\x82\x71" },
    { WORLD_WONDERLAND, 2, 150, NULL, "\x82\x73\x82\x71\x82\x68\x82\x62\x82\x6a\x82\x6c\x82\x60\x82\x72\x82\x73\x82\x64\x82\x71" },
    { WORLD_HALLOWEEN_TOWN, 2, 155, NULL, "\x82\x61\x82\x6e\x82\x6e\x82\x66\x82\x68\x82\x64" },
    { WORLD_HOLLOW_BASTION, 2, 153, NULL, "\x82\x6c\x81\x7c\x82\x63\x82\x71\x82\x60\x82\x66\x82\x6e\x82\x6d" },
    { WORLD_ATLANTICA, 2, 151, NULL, "\x82\x74\x82\x71\x82\x72\x82\x74\x82\x6b\x82\x60" },
    { WORLD_AGRABAH, 2, 149, NULL, "\x82\x69\x82\x60\x82\x65\x82\x60\x82\x71" },
    { WORLD_CASTLE_OBLIVION, 2, 156, NULL, "\x82\x6c\x82\x60\x82\x71\x82\x6b\x82\x74\x82\x77\x82\x68\x82\x60\x81\x7c\x82\x51" },
    { WORLD_CASTLE_OBLIVION, 1, 185, &gTaskDescEmyTest, "\x82\x73\x82\x64\x82\x72\x82\x73" },
    { WORLD_TRAVERSE_TOWN, 1, 178, NULL, "\x82\x73\x82\x74\x82\x73\x82\x6e\x82\x71\x82\x68\x82\x60\x82\x6b\x82\x4f" },
    { WORLD_TRAVERSE_TOWN, 1, 179, NULL, "\x82\x73\x82\x74\x82\x73\x82\x6e\x82\x71\x82\x68\x82\x60\x82\x6b\x82\x50" },
};

static const ChkBtlWorld sChkBtlWorlds[13] = {
    { BATTLE_STAGE_TWILIGHT_TOWN, "\x82\x73\x82\x76\x82\x68" },
    { BATTLE_STAGE_TRAVERSE_TOWN, "\x82\x73\x82\x76\x82\x6d" },
    { BATTLE_STAGE_WONDERLAND, "\x82\x76\x82\x6e\x82\x6d" },
    { 2, "\x82\x66\x82\x71\x82\x63" },
    { BATTLE_STAGE_OLYMPUS_COLISEUM, "\x82\x62\x82\x6e\x82\x6b" },
    { BATTLE_STAGE_MONSTRO, "\x82\x6c\x82\x6e\x82\x6d" },
    { BATTLE_STAGE_NEVER_LAND, "\x82\x6d\x82\x64\x82\x75" },
    { BATTLE_STAGE_HALLOWEEN_TOWN, "\x82\x67\x82\x60\x82\x6b" },
    { BATTLE_STAGE_AGRABAH, "\x82\x60\x82\x66\x82\x71" },
    { BATTLE_STAGE_ATLANTICA, "\x82\x60\x82\x73\x82\x6b" },
    { BATTLE_STAGE_HOLLOW_BASTION, "\x82\x67\x82\x6e\x82\x6b" },
    { BATTLE_STAGE_DESTINY_ISLANDS, "\x82\x63\x82\x64\x82\x72" },
    { BATTLE_STAGE_CASTLE_OBLIVION, "\x82\x62\x82\x72\x82\x6b" },
};

const char gWhitePalette[32] = "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff";

void mode_chkbtl_0() {
    FadeStartIn(FADE_MODE_BLACK, 8);
    SetBgMode0();
    SetupBg(0, 0, 15, 0);
    EnableBg(0);
    DebugTextInit(0, 0x5400, 0x500);
    DebugTextLoadPalette(0, gWhitePalette, 0x20, 0x0F);
    DebugTextPrint(0, 0, 2, "\x82\x63\x82\x64\x82\x62\x82\x6a\x81\x7c\x82\x72\x82\x64\x82\x6b\x82\x64\x82\x62\x82\x73\x81\x40\x82\x61\x82\x74\x82\x73\x82\x73\x82\x6e\x82\x6d");
    DebugTextPrint(24, 32, 2, "\x82\x64\x82\x6d\x82\x6c\x81\x46");
    DebugTextPrint(24, 44, 2, "\x82\x61\x82\x66\x81\x40\x81\x46");
    DebugTextPrint(24, 56, 2, "\x82\x65\x82\x6b\x81\x40\x81\x46");
    DebugTextPrint(24, 68, 2, "\x82\x67\x82\x6f\x81\x40\x81\x46");
    DebugTextPrint(62, 32, 2, sChkBtlEntries[gChkBtlWork->enemy].name);

    if (sChkBtlEntries[gChkBtlWork->enemy].kind == 2) {
        DebugTextPrint(62, 44, 2, "\x81\x5c\x81\x5c");
    } else {
        DebugTextPrint(62, 44, 2, sChkBtlWorlds[gChkBtlWork->bg].name);
    }

    DebugTextPrintNumber(62, 56, 2, gChkBtlWork->floor + 1);
    DebugTextPrintNumber(62, 68, 2, gChkBtlWork->hp);

    if (!(gDebugFlags & DEBUG_FLAG_CHKBTL)) {
        func_08085FB0();
        InitDebugDecks();
        gGameState.progression.cp = 9999;
        gDebugFlags |= DEBUG_FLAG_CHKBTL;
        gGameState.progression.friendFlags = 0xFFFF;
    }
}

void mode_chkbtl_1() {
    s32 i;

    if (GetKeysRepeat() & DPAD_UP) {
        gChkBtlWork->cursor--;
    }

    if (GetKeysRepeat() & DPAD_DOWN) {
        gChkBtlWork->cursor++;
    }

    if (GetKeysRepeat() & (DPAD_UP | DPAD_DOWN)) {
        for (i = 0; i < 4; i++) {
            DebugTextPrint(12, i * 12 + 32, 2, "\x81\x40");
        }
    }

    switch (gChkBtlWork->cursor) {
    case 0:
        if (GetKeysRepeat() & DPAD_LEFT) {
            gChkBtlWork->enemy--;
        }

        if (GetKeysRepeat() & DPAD_RIGHT) {
            gChkBtlWork->enemy++;
        }

        if (gChkBtlWork->enemy < 0) {
            gChkBtlWork->enemy = 0xD0;
        } else if ((u16)gChkBtlWork->enemy > 0xD0) {
            gChkBtlWork->enemy = 0;
        }

        break;
    case 1:
        if (GetKeysRepeat() & DPAD_LEFT) {
            gChkBtlWork->bg--;
        }

        if (GetKeysRepeat() & DPAD_RIGHT) {
            gChkBtlWork->bg++;
        }

        if (gChkBtlWork->bg < 0) {
            gChkBtlWork->bg = 12;
        } else if ((u8)gChkBtlWork->bg > 12) {
            gChkBtlWork->bg = 0;
        }

        break;
    case 2:
        if (GetKeysRepeat() & DPAD_LEFT) {
            gChkBtlWork->floor--;
        }

        if (GetKeysRepeat() & DPAD_RIGHT) {
            gChkBtlWork->floor++;
        }

        if (gChkBtlWork->floor < 0) {
            gChkBtlWork->floor = 0;
        }

        if (gGameState.flags & GAME_FLAG_RIKU) {
            if (gChkBtlWork->floor > 11) {
                gChkBtlWork->floor = 11;
            }
        } else {
            if (gChkBtlWork->floor > 12) {
                gChkBtlWork->floor = 12;
            }
        }

        break;
    case 3:
        if (GetKeysRepeat() & DPAD_LEFT) {
            gChkBtlWork->hp--;
        }

        if (GetKeysRepeat() & DPAD_RIGHT) {
            gChkBtlWork->hp++;
        }

        if (gChkBtlWork->hp <= 0) {
            gChkBtlWork->hp = 1;
        } else if (gChkBtlWork->hp > 560) {
            gChkBtlWork->hp = 560;
        }

        break;
    case 4:
        gChkBtlWork->cursor = 0;
        break;
    case -1:
        gChkBtlWork->cursor = 3;
        break;
    }

    DebugTextPrint(12, gChkBtlWork->cursor * 12 + 32, 2, "\x81\x84");

    if (GetKeysRepeat() & (DPAD_RIGHT | DPAD_LEFT)) {
        switch (gChkBtlWork->cursor) {
        case 0:
        case 1:
            DebugTextPrint(62, 32, 2, "\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40");
            DebugTextPrint(62, 32, 2, sChkBtlEntries[gChkBtlWork->enemy].name);
            DebugTextPrint(62, 44, 2, "\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40\x81\x40");

            if (sChkBtlEntries[gChkBtlWork->enemy].kind == 2) {
                DebugTextPrint(62, 44, 2, "\x81\x5c\x81\x5c");
            } else {
                DebugTextPrint(62, 44, 2, sChkBtlWorlds[gChkBtlWork->bg].name);
            }

            break;
        case 2:
            DebugTextPrintNumber(62, 56, 2, gChkBtlWork->floor + 1);
            break;
        case 3:
            DebugTextPrintNumber(62, 68, 2, gChkBtlWork->hp);
            break;
        }
    }

    if (GetKeysPressed() & SELECT_BUTTON) {
        ModeRequest(&gModeDeck, 0);
    } else if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
        SeedRandom(gFrameCounter);
        gGameState.battleStage = sChkBtlWorlds[gChkBtlWork->bg].world;
        gGameState.floor = gChkBtlWork->floor;
        gGameState.hp = gChkBtlWork->hp;
        gGameState.progression.maxHp = gChkBtlWork->hp;
        gGameState.world = sChkBtlEntries[gChkBtlWork->enemy].world;

        if (GetKeysHeld() & L_BUTTON) {
            gGameState.flags |= GAME_FLAG_FIRST_STRIKE;
        } else {
            gGameState.flags &= ~GAME_FLAG_FIRST_STRIKE;
        }

        if (gGameState.flags & GAME_FLAG_RIKU) {
            InitRikuDeckForWorld(gChkBtlWork->floor);
        }

        ModeRequest(&gModeBattle, sChkBtlEntries[gChkBtlWork->enemy].battleId);
    } else if (GetKeysPressed() & B_BUTTON) {
        ModeRequest(&gModeDebug, 0);
        return;
    }

    DebugTextDraw(0);
    DebugTextClear();
}

void mode_chkbtl_2() {
    DebugTextDestroy();
}

void ChkBtlSpawnEnemy() {
    const ChkBtlEntry* entry;
    ChkBtlPos pos;

    entry = &sChkBtlEntries[gChkBtlWork->enemy];

    if (entry->battleId == 0xB9) {
        pos.x = 0x15000;
        pos.y = 0x16000;
        pos.z = 0;
        TaskCreate(&gBtlWork->taskPools[0], entry->taskDesc, &pos);
    }
}

void ChkBtlReset() {
    gChkBtlWork->cursor = 0;
    gChkBtlWork->bg = 0;
    gChkBtlWork->enemy = 0;
    gChkBtlWork->floor = 0;
    gChkBtlWork->hp = gGameState.progression.maxHp;
    gDebugFlags &= ~DEBUG_FLAG_CHKBTL;
    gVsBattleHalfWidth = 0x98;
    gVsBattleMinY = 0x160;
    gVsBattleMaxY = 0x1A2;
}

ChkBtlWork* gChkBtlWork = &sChkBtlWork;

Mode gModeChkbtl = { "mode_chkbtl", mode_chkbtl_0, mode_chkbtl_1, mode_chkbtl_2 };
