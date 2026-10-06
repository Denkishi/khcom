/**
 * map_data.c
 * Field Map Data Tables
 */

#include "map.h"
#include "map_enemy_data.h"
#include "map_spawn_data.h"
#include "event_backgrounds.h"
#include "card_ids.h"
#include "registration_data.h"
#include "sprites_map.h"
#include "sprites_map_tasks.h"
#include "songs.h"
#include "map_room_types.h"
#include "map_rooms.h"
#include "types.h"
#include "default_bg_map.h"
#include "card_message_data.h"

const MapRoomDef* gMapRoomDefs[14] = {
    &gMapRoom00Def,
    &gMapRoom01Def,
    &gMapRoom02Def,
    &gMapRoom03Def,
    &gMapRoom04Def,
    &gMapRoom05Def,
    &gMapRoom06Def,
    &gMapRoom07Def,
    &gMapRoom08Def,
    &gMapRoom09Def,
    &gMapRoom10Def,
    &gMapRoom11Def,
    &gMapRoom12Def,
    &gMapRoom00Def,
};

u8 gMapFixed0CellTypes[1536] = {
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 6, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 6, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 6, 2, 2, 2, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 5, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 5, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 5, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 5, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
};

u8 gMapFixed1CellTypes[768] = {
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 7, 7, 7, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 7, 7, 7, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 7, 7, 7, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 7, 7, 7, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 7, 7, 7, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 7, 7, 7, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 7, 7, 7, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 7, 7, 7, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 7, 7, 7, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 7, 7, 7, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 7, 7, 7, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 9, 9, 9, 7, 7, 7, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 9, 9, 9, 7, 7, 7, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 6, 9, 9, 7, 7, 7, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 6, 9, 7, 7, 7, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 6, 2, 2, 2, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 9, 9,
    8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 5, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 5, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 5, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 5, 0, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,
};

u8 gMapFixed2CellTypes[768] = {
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 7, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 7, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 7, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 7, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 7, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 7, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 7, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 7, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 7, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 9, 7, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 2, 2, 2, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 6, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 6, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 6, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 9, 9,
    8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 5, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 5, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 5, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 5, 0, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,
};

u8 gMapFixed3CellTypes[768] = {
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 2, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 6, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 6, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 6, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 6, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 9,
    8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 9,
    8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 9,
    8, 8, 8, 8, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 9,
    8, 8, 8, 8, 8, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 9,
    8, 8, 8, 8, 8, 9, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 5, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 5, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8, 8, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 5, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 5, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9,
    8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9,
};

u8 gMapFixed4CellTypes[512] = {
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 2, 2, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 6, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 6, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 6, 9, 9,
    8, 8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 6, 9,
    8, 8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
    8, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8,
    8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8,
    4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8,
    5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8,
    9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8,
    9, 9, 5, 0, 0, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8,
    9, 9, 9, 5, 0, 0, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8,
    9, 9, 9, 9, 5, 0, 0, 3, 8, 8, 8, 8, 8, 8, 8, 8,
    9, 9, 9, 9, 9, 5, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
};

const void* gMapFixed0Bg3Blocks[12] = {
    gEventBg000Bg3Map0,
    gEventBg000Bg3Map1,
    gEventBg000Bg3Map2,
    gEventBg000Bg3Map3,
    gEventBg000Bg3Map4,
    gEventBg000Bg3Map5,
    gEventBg000Bg3Map6,
    gEventBg000Bg3Map7,
    gEventBg000Bg3Map8,
    gEventBg000Bg3Map9,
    gEventBg000Bg3Map10,
    gEventBg000Bg3Map11,
};

const void* gMapFixed0Bg2Blocks[12] = {
    gEventBg000Bg2Map0,
    gEventBg000Bg2Map1,
    gEventBg000Bg2Map2,
    gEventBg000Bg2Map3,
    gEventBg000Bg2Map4,
    gEventBg000Bg2Map5,
    gEventBg000Bg2Map6,
    gEventBg000Bg2Map7,
    gEventBg000Bg2Map8,
    gEventBg000Bg2Map9,
    gEventBg000Bg2Map10,
    gEventBg000Bg2Map11,
};

const void* gMapFixed0Bg1Blocks[12] = {
#ifdef VERSION_EU
    gDefaultBgMapLz77,
    gDefaultBgMapLz77,
    gDefaultBgMapLz77,
    gDefaultBgMapLz77,
#else
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
#endif
    gEventBg000Bg1Map4,
    gEventBg000UnusedDoorMap,
#ifdef VERSION_EU
    gDefaultBgMapLz77,
    gDefaultBgMapLz77,
    gDefaultBgMapLz77,
#else
    gDefaultBgMap,
    gDefaultBgMap,
    gDefaultBgMap,
#endif
    gEventBg000Bg1Map9,
#ifdef VERSION_EU
    gDefaultBgMapLz77,
    gDefaultBgMapLz77,
#else
    gDefaultBgMap,
    gDefaultBgMap,
#endif
};

const void* gMapFixed1Bg3Blocks[6] = {
    gEventBg001Bg3Map1,
    gEventBg001Bg3Map2,
    gEventBg001Bg3Map3,
    gEventBg001Bg3Map5,
    gEventBg001Bg3Map6,
    gEventBg001Bg3Map7,
};

const void* gMapFixed1Bg2Blocks[6] = {
    gEventBg001Bg2Map1,
    gEventBg001Bg2Map2,
    gEventBg001Bg2Map3,
    gEventBg001Bg2Map5,
    gEventBg001Bg2Map6,
    gEventBg001Bg2Map7,
};

const void* gMapFixed2Bg3Blocks[6] = {
    gEventBg010Bg3Map1,
    gEventBg010Bg3Map2,
    gEventBg010Bg3Map3,
    gEventBg010Bg3Map5,
    gEventBg010Bg3Map6,
    gEventBg010Bg3Map7,
};

const void* gMapFixed2Bg2Blocks[6] = {
    gEventBg010Bg2Map1,
    gEventBg010Bg2Map2,
    gEventBg010Bg2Map3,
    gEventBg010Bg2Map5,
    gEventBg010Bg2Map6,
    gEventBg010Bg2Map7,
};

const void* gMapFixed3Bg3Blocks[6] = {
    gEventBg066Bg3Map1,
    gEventBg066Bg3Map2,
    gEventBg066Bg3Map3,
    gEventBg066Bg3Map5,
    gEventBg066Bg3Map6,
    gEventBg066Bg3Map7,
};

const void* gMapFixed3Bg2Blocks[6] = {
    gEventBg066Bg2Map1,
    gEventBg066Bg2Map2,
    gEventBg066Bg2Map3,
    gEventBg066Bg2Map5,
    gEventBg066Bg2Map6,
    gEventBg066Bg2Map7,
};

const void* gMapFixed4Bg3Blocks[4] = {
    gEventBg002Bg3Map0,
    gEventBg002Bg3Map1,
    gEventBg002Bg3Map4,
    gEventBg002Bg3Map5,
};

const void* gMapFixed4Bg2Blocks[4] = {
    gEventBg002Bg2Map0,
    gEventBg002Bg2Map1,
    gEventBg002Bg2Map4,
    gEventBg002Bg2Map5,
};

const void* gMapFixed4Bg1Blocks[4] = {
    gEventBg002Bg1Map0,
    gEventBg002Bg1Map1,
    gEventBg002Bg1Map4,
    gEventBg002Bg1Map5,
};

const void* gMapFixed5Bg2Blocks[6] = {
    gEventBg001Bg2Map1,
    gEventBg001Bg2Map2,
    gEventBg001Bg2Map3,
    gMapFixed5Bg2Block3Map,
    gMapFixed5Bg2Block4Map,
    gEventBg001Bg2Map7,
};

const MapFixedDef* gMapFixedDefs[6] = {
    &gMapFixed0Def,
    &gMapFixed1Def,
    &gMapFixed2Def,
    &gMapFixed3Def,
    &gMapFixed4Def,
    &gMapFixed5Def,
};

const PrzCardChance* gWorldPrzCardChances[14] = {
    gPrzCardChancesDefault,
    gPrzCardChancesAgrabah,
    gPrzCardChancesAtlantica,
    gPrzCardChancesOlympusColiseum,
    gPrzCardChancesWonderland,
    gPrzCardChancesMonstro,
    gPrzCardChancesHalloweenTown,
    gPrzCardChancesNeverLand,
    gPrzCardChancesHollowBastion,
    gPrzCardChancesDestinyIslands,
    gPrzCardChancesTraverseTown,
    gPrzCardChancesTwilightTown,
    gPrzCardChancesCastleOblivion,
    gPrzCardChancesDefault,
};

const PrizeEntry* gWorldPrizeLists[14] = {
    gPrizeListEmpty,
    gPrizeListAgrabah,
    gPrizeListAtlantica,
    gPrizeListOlympusColiseum,
    gPrizeListWonderland,
    gPrizeListMonstro,
    gPrizeListHalloweenTown,
    gPrizeListNeverLand,
    gPrizeListHollowBastion,
    gPrizeListDestinyIslands,
    gPrizeListTraverseTown,
    gPrizeListTwilightTown,
    gPrizeListCastleOblivion,
    gPrizeListEmpty,
};

const MapEnmDef* gMapEnmDefs[7] = {
    &gMapEnm00Def,
    &gMapEnm01Def,
    &gMapEnm02Def,
    &gMapEnm03Def,
    &gMapEnm04Def,
    &gMapEnm05Def,
    &gMapEnm06Def,
};

const MapGmkDef gMapGmkDefs[67] = {
    { gMapGmkAtlantica00Palette, gMapGmkAtlantica00Tiles, 0x800, gMapGmkAtlantica00Frames, gMapGmkAtlantica00Anims, 0, 9, 0, 0, 0, 16, 88, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkAtlantica01Palette, gMapGmkAtlantica01Tiles, 0xB60, gMapGmkAtlantica01Frames, gMapGmkAtlantica01Anims, 0, 9, 0, 0, 0, 32, 24, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmkGP09 },
    { gMapGmkAgrabah00Palette, gMapGmkAgrabah00Tiles, 0x800, gMapGmkAgrabah00Frames, gMapGmkAgrabah00Anims, 0, 1, 0, 0, 0, 32, 32, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkAgrabah00Palette, gMapGmkAgrabah01Tiles, 0x800, gMapGmkAgrabah01Frames, gMapGmkAgrabah01Anims, 0, 1, 0, 0, 0, 32, 32, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkAgrabah01Palette, gMapGmkAgrabah02Tiles, 0x1000, gMapGmkAgrabah02Frames, gMapGmkAgrabah02Anims, 0, 11, 0, 0, 0, 28, 74, SONG_SND_216, &gTaskDescMapGmkGP00 },
    { gMapGmkAgrabah01Palette, gMapGmkAgrabah03Tiles, 0xA00, gMapGmkAgrabah03Frames, gMapGmkAgrabah03Anims, 0, 9, 0, 0, 0, 30, 24, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkAgrabah01Palette, gMapGmkAgrabah04Tiles, 0x800, gMapGmkAgrabah04Frames, gMapGmkAgrabah04Anims, 1, 9, 0, 0, 0, 22, 24, SONG_SND_217, &gTaskDescMapGmkGP02 },
    { gMapGmkAgrabah01Palette, gMapGmkAgrabah05Tiles, 0x200, gMapGmkAgrabah05Frames, gMapGmkAgrabah05Anims, 1, 9, 0, 0, 0, 14, 20, SONG_SND_217, &gTaskDescMapGmkGP02 },
    { gMapGmkAgrabah01Palette, gMapGmkAgrabah06Tiles, 0x200, gMapGmkAgrabah06Frames, gMapGmkAgrabah06Anims, 0, 6, 16, 8, 14, 24, 4, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkAgrabah01Palette, gMapGmkAgrabah07Tiles, 0x200, gMapGmkAgrabah07Frames, gMapGmkAgrabah07Anims, 0, 7, 0, 12, 2, 20, 4, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkAgrabah01Palette, gMapGmkAgrabah08Tiles, 0x200, gMapGmkAgrabah08Frames, gMapGmkAgrabah08Anims, 0, 8, -16, 8, 14, 24, 4, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkAgrabah01Palette, gMapGmkAgrabah09Tiles, 0x800, gMapGmkAgrabah09Frames, gMapGmkAgrabah09Anims, 0, 9, 0, 0, 0, 28, 24, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkAgrabah02Palette, gMapGmkAgrabah10Tiles, 0x800, gMapGmkAgrabah10Frames, gMapGmkAgrabah10Anims, 0, 9, 0, 0, 0, 28, 24, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkAgrabah03Palette, gMapGmkAgrabah11Tiles, 0x800, gMapGmkAgrabah11Frames, gMapGmkAgrabah11Anims, 0, 9, 0, 0, 0, 28, 24, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkWonderland00Palette, gMapGmkWonderland00Tiles, 0x800, gMapGmkWonderland00Frames, gMapGmkWonderland00Anims, 1, 11, 0, 0, 0, 40, 32, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmkGP07 },
    { gMapGmkWonderland00Palette, gMapGmkWonderland01Tiles, 0x500, gMapGmkWonderland01Frames, gMapGmkWonderland01Anims, 1, 9, 0, 0, 0, 20, 20, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmkGP07 },
    { gMapGmkWonderland00Palette, gMapGmkWonderland02Tiles, 0x1800, gMapGmkWonderland02Frames, gMapGmkWonderland02Anims, 0, 12, 0, 0, 0, 44, 96, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkMonstro00Palette, gMapGmkMonstro00Tiles, 0xE80, gMapGmkMonstro00Frames, gMapGmkMonstro00Anims, 1, 11, 0, 0, 0, 40, 20, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmkGP07 },
    { gMapGmkMonstro01Palette, gMapGmkMonstro01Tiles, 0x1100, gMapGmkMonstro01Frames, gMapGmkMonstro01Anims, 1, 5, -6, 10, 0, 30, 20, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmkGP07 },
    { gMapGmkMonstro02Palette, gMapGmkMonstro02Tiles, 0x1100, gMapGmkMonstro02Frames, gMapGmkMonstro02Anims, 1, 4, 6, 10, 0, 30, 20, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmkGP07 },
    { gMapGmkMonstro03Palette, gMapGmkMonstro03Tiles, 0x1080, gMapGmkMonstro03Frames, gMapGmkMonstro03Anims, 1, 11, 0, 0, 0, 42, 40, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmkGP07 },
    { gMapGmkMonstro04Palette, gMapGmkMonstro04Tiles, 0x3C0, gMapGmkMonstro04Frames, gMapGmkMonstro04Anims, 1, 9, 0, 0, 0, 24, 20, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmkGP07 },
    { gMapGmkHalloweenTown00Palette, gMapGmkHalloweenTown00Tiles, 0x13C0, gMapGmkHalloweenTown00Frames, gMapGmkHalloweenTown00Anims, 0, 11, 0, 0, 0, 32, 44, SONG_SND_232, &gTaskDescMapGmkGP08 },
    { gMapGmkHalloweenTown00Palette, gMapGmkHalloweenTown01Tiles, 0x13C0, gMapGmkHalloweenTown01Frames, gMapGmkHalloweenTown01Anims, 0, 11, 0, 0, 0, 32, 44, SONG_SND_232, &gTaskDescMapGmkGP08 },
    { gMapGmkHalloweenTown01Palette, gMapGmkHalloweenTown02Tiles, 0x800, gMapGmkHalloweenTown02Frames, gMapGmkHalloweenTown02Anims, 1, 11, 0, 0, 0, 32, 16, SONG_SND_216, &gTaskDescMapGmkGP04 },
    { gMapGmkHalloweenTown01Palette, gMapGmkHalloweenTown03Tiles, 0x800, gMapGmkHalloweenTown03Frames, gMapGmkHalloweenTown03Anims, 1, 11, 0, 0, 0, 32, 32, SONG_SND_216, &gTaskDescMapGmkGP04 },
    { gMapGmkHalloweenTown01Palette, gMapGmkHalloweenTown04Tiles, 0x9A0, gMapGmkHalloweenTown04Frames, gMapGmkHalloweenTown04Anims, 0, 11, 0, 0, 0, 32, 44, SONG_SND_234, &gTaskDescMapGmkGP08 },
    { gMapGmkHalloweenTown02Palette, gMapGmkHalloweenTown05Tiles, 0xE80, gMapGmkHalloweenTown05Frames, gMapGmkHalloweenTown05Anims, 1, 11, 0, 0, 0, 32, 44, SONG_SND_233, &gTaskDescMapGmkGP02 },
    { gMapGmkHalloweenTown02Palette, gMapGmkHalloweenTown06Tiles, 0x800, gMapGmkHalloweenTown06Frames, gMapGmkHalloweenTown06Anims, 0, 11, 0, 0, 0, 32, 44, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkHalloweenTown01Palette, gMapGmkHalloweenTown07Tiles, 0xC00, gMapGmkHalloweenTown07Frames, gMapGmkHalloweenTown07Anims, 0, 3, 0, -8, 0, 30, 64, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkHalloweenTown01Palette, gMapGmkHalloweenTown08Tiles, 0xC00, gMapGmkHalloweenTown08Frames, gMapGmkHalloweenTown08Anims, 0, 1, 0, -8, 0, 30, 64, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkHalloweenTown01Palette, gMapGmkHalloweenTown09Tiles, 0xC00, gMapGmkHalloweenTown09Frames, gMapGmkHalloweenTown09Anims, 0, 2, 0, -8, 0, 30, 64, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkHalloweenTown01Palette, gMapGmkHalloweenTown10Tiles, 0x800, gMapGmkHalloweenTown10Frames, gMapGmkHalloweenTown10Anims, 1, 3, 0, -6, 0, 28, 104, SONG_SND_215, &gTaskDescMapGmkGP02 },
    { gMapGmkHalloweenTown01Palette, gMapGmkHalloweenTown10Tiles, 0x800, gMapGmkHalloweenTown10Frames, gMapGmkHalloweenTown10Anims, 1, 1, 0, -6, 0, 28, 104, SONG_SND_215, &gTaskDescMapGmkGP02 },
    { gMapGmkHalloweenTown01Palette, gMapGmkHalloweenTown10Tiles, 0x800, gMapGmkHalloweenTown10Frames, gMapGmkHalloweenTown10Anims, 1, 2, 0, -6, 0, 28, 104, SONG_SND_215, &gTaskDescMapGmkGP02 },
    { gMapGmkOlympusColiseum00Palette, gMapGmkOlympusColiseum00Tiles, 0x660, gMapGmkOlympusColiseum00Frames, gMapGmkOlympusColiseum00Anims, 0, 9, 0, 0, 0, 16, 72, SONG_SND_216, &gTaskDescMapGmkGP08 },
    { gMapGmkOlympusColiseum00Palette, gMapGmkOlympusColiseum01Tiles, 0x660, gMapGmkOlympusColiseum01Frames, gMapGmkOlympusColiseum01Anims, 0, 9, 0, 0, 0, 16, 72, SONG_SND_216, &gTaskDescMapGmkGP08 },
    { gMapGmkOlympusColiseum01Palette, gMapGmkOlympusColiseum02Tiles, 0x800, gMapGmkOlympusColiseum02Frames, gMapGmkOlympusColiseum02Anims, 0, 9, 0, 0, 0, 32, 24, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkOlympusColiseum02Palette, gMapGmkOlympusColiseum03Tiles, 0x800, gMapGmkOlympusColiseum03Frames, gMapGmkOlympusColiseum03Anims, 0, 9, 0, 0, 0, 28, 16, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkOlympusColiseum03Palette, gMapGmkOlympusColiseum04Tiles, 0xA00, gMapGmkOlympusColiseum04Frames, gMapGmkOlympusColiseum04Anims, 0, 9, 0, 0, 0, 32, 48, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkHollowBastion00Palette, gMapGmkHollowBastion00Tiles, 0x3E0, gMapGmkHollowBastion00Frames, gMapGmkHollowBastion00Anims, 0, 9, 0, 0, 0, 20, 32, SONG_SND_216, &gTaskDescMapGmkGP08 },
    { gMapGmkHollowBastion00Palette, gMapGmkHollowBastion01Tiles, 0x6E0, gMapGmkHollowBastion01Frames, gMapGmkHollowBastion01Anims, 0, 9, 0, 0, 0, 20, 44, SONG_SND_216, &gTaskDescMapGmkGP08 },
    { gMapGmkHollowBastion00Palette, gMapGmkHollowBastion02Tiles, 0xCE0, gMapGmkHollowBastion02Frames, gMapGmkHollowBastion02Anims, 0, 9, 0, 0, 0, 20, 60, SONG_SND_216, &gTaskDescMapGmkGP08 },
    { gMapGmkHollowBastion00Palette, gMapGmkHollowBastion03Tiles, 0x9E0, gMapGmkHollowBastion03Frames, gMapGmkHollowBastion03Anims, 0, 9, 0, 0, 0, 24, 48, SONG_SND_216, &gTaskDescMapGmkGP08 },
    { gMapGmkHollowBastion01Palette, gMapGmkHollowBastion04Tiles, 0x800, gMapGmkHollowBastion04Frames, gMapGmkHollowBastion04Anims, 0, 9, 0, 0, 0, 24, 40, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkNeverLand00Palette, gMapGmkNeverLand00Tiles, 0x900, gMapGmkNeverLand00Frames, gMapGmkNeverLand00Anims, 1, 9, 0, 0, 0, 24, 28, SONG_SYS_TRESURE, &gTaskDescMapGmkGP03 },
    { gMapGmkNeverLand01Palette, gMapGmkNeverLand01Tiles, 0x680, gMapGmkNeverLand01Frames, gMapGmkNeverLand01Anims, 1, 0, 0, 0, 0, 16, 16, SONG_SYS_TRESURE, &gTaskDescMapGmkGP03 },
    { gMapGmkNeverLand02Palette, gMapGmkNeverLand02Tiles, 0x1060, gMapGmkNeverLand02Frames, gMapGmkNeverLand02Anims, 0, 9, 0, 0, 0, 20, 32, SONG_SND_231, &gTaskDescMapGmkGP08 },
    { gMapGmkNeverLand02Palette, gMapGmkNeverLand03Tiles, 0x600, gMapGmkNeverLand03Frames, gMapGmkNeverLand03Anims, 0, 9, 0, 0, 0, 32, 24, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkNeverLand02Palette, gMapGmkNeverLand04Tiles, 0x800, gMapGmkNeverLand04Frames, gMapGmkNeverLand04Anims, 0, 9, 0, 0, 0, 24, 32, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkNeverLand03Palette, gMapGmkNeverLand05Tiles, 0x1C40, gMapGmkNeverLand05Frames, gMapGmkNeverLand05Anims, 0, 11, 0, 0, 0, 34, 24, SONG_SND_229, &gTaskDescMapGmkGP08 },
    { gMapGmkNeverLand04Palette, gMapGmkNeverLand06Tiles, 0x24A0, gMapGmkNeverLand06Frames, gMapGmkNeverLand06Anims, 0, 12, 0, 0, 0, 52, 24, SONG_SND_235, &gTaskDescMapGmkGP08 },
    { gMapGmkDestinyIslands00Palette, gMapGmkDestinyIslands00Tiles, 0xC00, gMapGmkDestinyIslands00Frames, gMapGmkDestinyIslands00Anims, 1, 11, 0, 0, 0, 32, 28, SONG_SYS_OBJ_BREAK, &gTaskDescMapGmkGP05 },
    { gMapGmkDestinyIslands01Palette, gMapGmkDestinyIslands01Tiles, 0x800, gMapGmkDestinyIslands01Frames, gMapGmkDestinyIslands01Anims, 0, 9, 0, 0, 0, 16, 24, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkDestinyIslands01Palette, gMapGmkDestinyIslands02Tiles, 0x800, gMapGmkDestinyIslands02Frames, gMapGmkDestinyIslands02Anims, 0, 9, 0, 0, 0, 24, 16, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkDestinyIslands01Palette, gMapGmkDestinyIslands03Tiles, 0x900, gMapGmkDestinyIslands03Frames, gMapGmkDestinyIslands03Anims, 0, 11, 0, 0, 0, 32, 20, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkDestinyIslands02Palette, gMapGmkDestinyIslands04Tiles, 0x1960, gMapGmkDestinyIslands04Frames, gMapGmkDestinyIslands04Anims, 0, 9, 0, 0, 0, 24, 96, SONG_SND_230, &gTaskDescMapGmkGP08 },
    { gMapGmkTraverseTown00Palette, gMapGmkTraverseTown00Tiles, 0x500, gMapGmkTraverseTown00Frames, gMapGmkTraverseTown00Anims, 1, 9, 0, 0, 0, 12, 64, SONG_SND_214, &gTaskDescMapGmkGP06 },
    { gMapGmkTraverseTown01Palette, gMapGmkTraverseTown01Tiles, 0x800, gMapGmkTraverseTown01Frames, gMapGmkTraverseTown01Anims, 0, 9, 0, 0, 0, 32, 32, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkTwilightTown00Palette, gMapGmkTwilightTown00Tiles, 0x800, gMapGmkTwilightTown00Frames, gMapGmkTwilightTown00Anims, 0, 9, 0, 0, 0, 28, 16, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkTwilightTown01Palette, gMapGmkTwilightTown01Tiles, 0x480, gMapGmkTwilightTown01Frames, gMapGmkTwilightTown01Anims, 1, 9, 0, 0, 0, 16, 48, SONG_SND_216, &gTaskDescMapGmkGP06 },
    { gMapGmkTwilightTown02Palette, gMapGmkTwilightTown02Tiles, 0x960, gMapGmkTwilightTown02Frames, gMapGmkTwilightTown02Anims, 0, 11, 0, 0, 0, 32, 32, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkCastleOblivion00Palette, gMapGmkCastleOblivion00Tiles, 0xDC0, gMapGmkCastleOblivion00Frames, gMapGmkCastleOblivion00Anims, 0, 0, 0, 0, 0, 16, 26, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkCastleOblivion00Palette, gMapGmkCastleOblivion01Tiles, 0x880, gMapGmkCastleOblivion01Frames, gMapGmkCastleOblivion01Anims, 0, 9, 0, 0, 0, 32, 32, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkCastleOblivion01Palette, gMapGmkCastleOblivion02Tiles, 0x600, gMapGmkCastleOblivion02Frames, gMapGmkCastleOblivion02Anims, 1, 9, 0, 0, 0, 20, 13, SONG_SND_218, &gTaskDescMapGmkGP05 },
    { gMapGmkCastleOblivion00Palette, gMapGmkCastleOblivion03Tiles, 0x300, gMapGmkCastleOblivion03Frames, gMapGmkCastleOblivion03Anims, 0, 0, 0, 0, 0, 16, 26, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
    { gMapGmkCastleOblivion00Palette, gMapGmkCastleOblivion04Tiles, 0x880, gMapGmkCastleOblivion04Frames, gMapGmkCastleOblivion04Anims, 0, 9, 0, 0, 0, 32, 32, SONG_SYS_FIELD_ATT00, &gTaskDescMapGmk00 },
};

const MapGmkDef gWorldMapGmkDefs[7] = {
    { gWorldMapGmkTraverseTownPalette, gWorldMapGmkTraverseTownTiles, 0x800, gWorldMapGmkTraverseTownFrames, gWorldMapGmkTraverseTownAnims, 1, 0, 0, 0, 0, 28, 32, SONG_SYS_OBJ_BREAK, &gTaskDescMapGmkGP01 },
    { gWorldMapGmkWonderlandPalette, gWorldMapGmkWonderlandTiles, 0x420, gWorldMapGmkWonderlandFrames, gWorldMapGmkWonderlandAnims, 1, 0, 0, 0, 0, 12, 36, SONG_SND_221, &gTaskDescMapGmkGP03 },
    { gWorldMapGmkAtlanticaPalette, gWorldMapGmkAtlanticaTiles, 0x720, gWorldMapGmkAtlanticaFrames, gWorldMapGmkAtlanticaAnims, 1, 0, 0, 0, 0, 16, 8, SONG_SYS_TRESURE, &gTaskDescMapGmkGP03 },
    { gWorldMapGmkHalloweenTownPalette, gWorldMapGmkHalloweenTownTiles, 0x500, gWorldMapGmkHalloweenTownFrames, gWorldMapGmkHalloweenTownAnims, 1, 0, 0, 0, 0, 16, 12, SONG_SYS_OBJ_BREAK, &gTaskDescMapGmkGP01 },
    { gWorldMapGmkHollowBastionPalette, gWorldMapGmkHollowBastion00Tiles, 0x400, gWorldMapGmkHollowBastion00Frames, gWorldMapGmkHollowBastion00Anims, 1, 0, 0, 0, 0, 16, 16, SONG_SND_223, &gTaskDescMapGmkGP02 },
    { gWorldMapGmkHollowBastionPalette, gWorldMapGmkHollowBastion01Tiles, 0x500, gWorldMapGmkHollowBastion01Frames, gWorldMapGmkHollowBastion01Anims, 1, 0, 0, 0, 0, 16, 32, SONG_SND_223, &gTaskDescMapGmkGP02 },
    { gMapGmkCastleOblivion00Palette, gMapGmkCastleOblivion00Tiles, 0x440, gMapGmkCastleOblivion00Frames, gMapGmkCastleOblivion00Anims, 1, 0, 0, 0, 0, 16, 26, SONG_SND_219, &gTaskDescMapGmkGP01 },
};

const PrzCardChance gPrzCardChancesDefault[7] = {
    { 0, 2500, 2500, { 0, 0 } },
    { 20, 500, 500, { 0, 0 } },
    { 17, 1500, 1500, { 0, 0 } },
    { 18, 200, 200, { 0, 0 } },
    { 19, 200, 200, { 0, 0 } },
    { 31, 1000, 1000, { 0, 0 } },
    { 41, 0, 0, { 0, 0 } },
};

const PrzCardChance gPrzCardChancesTraverseTown[8] = {
    { 0, 5000, 1000, { 0, 0 } },
    { 9, 1200, 1000, { 0, 0 } },
    { 14, 300, 500, { 0, 0 } },
    { 18, 1000, 3000, { 0, 0 } },
    { 20, 1000, 3000, { 0, 0 } },
    { 24, 500, 1000, { 0, 0 } },
    { 31, 1000, 500, { 0, 0 } },
    { 41, 0, 0, { 0, 0 } },
};

const PrzCardChance gPrzCardChancesAgrabah[12] = {
    { 0, 3000, 0, { 0, 0 } },
    { 2, 2000, 1500, { 0, 0 } },
    { 14, 300, 500, { 0, 0 } },
    { 18, 500, 1500, { 0, 0 } },
    { 17, 500, 1500, { 0, 0 } },
    { 20, 0, 500, { 0, 0 } },
    { 21, 1000, 2000, { 0, 0 } },
    { 22, 500, 0, { 0, 0 } },
    { 25, 700, 1500, { 0, 0 } },
    { 32, 500, 0, { 0, 0 } },
    { 34, 1000, 1000, { 0, 0 } },
    { 41, 0, 0, { 0, 0 } },
};

const PrzCardChance gPrzCardChancesHalloweenTown[13] = {
    { 0, 3000, 0, { 0, 0 } },
    { 4, 2000, 1500, { 0, 0 } },
    { 14, 300, 500, { 0, 0 } },
    { 18, 600, 1500, { 0, 0 } },
    { 17, 600, 2000, { 0, 0 } },
    { 20, 600, 500, { 0, 0 } },
    { 21, 600, 1000, { 0, 0 } },
    { 22, 600, 1000, { 0, 0 } },
    { 24, 0, 500, { 0, 0 } },
    { 31, 700, 500, { 0, 0 } },
    { 32, 500, 500, { 0, 0 } },
    { 34, 500, 500, { 0, 0 } },
    { 41, 0, 0, { 0, 0 } },
};

const PrzCardChance gPrzCardChancesMonstro[13] = {
    { 0, 3000, 0, { 0, 0 } },
    { 6, 2000, 1500, { 0, 0 } },
    { 14, 300, 500, { 0, 0 } },
    { 18, 500, 1500, { 0, 0 } },
    { 17, 500, 1500, { 0, 0 } },
    { 20, 500, 500, { 0, 0 } },
    { 21, 500, 1000, { 0, 0 } },
    { 22, 500, 1000, { 0, 0 } },
    { 27, 700, 1500, { 0, 0 } },
    { 31, 500, 0, { 0, 0 } },
    { 32, 500, 500, { 0, 0 } },
    { 34, 500, 500, { 0, 0 } },
    { 41, 0, 0, { 0, 0 } },
};

const PrzCardChance gPrzCardChancesOlympusColiseum[13] = {
    { 0, 2000, 0, { 0, 0 } },
    { 8, 1000, 500, { 0, 0 } },
    { 1, 2000, 1000, { 0, 0 } },
    { 14, 300, 500, { 0, 0 } },
    { 18, 500, 1500, { 0, 0 } },
    { 17, 500, 1500, { 0, 0 } },
    { 20, 500, 500, { 0, 0 } },
    { 21, 500, 1000, { 0, 0 } },
    { 22, 500, 1000, { 0, 0 } },
    { 30, 1000, 1500, { 0, 0 } },
    { 32, 700, 1000, { 0, 0 } },
    { 34, 500, 0, { 0, 0 } },
    { 41, 0, 0, { 0, 0 } },
};

const PrzCardChance gPrzCardChancesWonderland[13] = {
    { 0, 3000, 0, { 0, 0 } },
    { 10, 2000, 1500, { 0, 0 } },
    { 14, 300, 500, { 0, 0 } },
    { 18, 600, 1500, { 0, 0 } },
    { 17, 600, 1500, { 0, 0 } },
    { 20, 0, 500, { 0, 0 } },
    { 21, 500, 0, { 0, 0 } },
    { 22, 1000, 2000, { 0, 0 } },
    { 24, 0, 500, { 0, 0 } },
    { 31, 600, 1000, { 0, 0 } },
    { 32, 700, 500, { 0, 0 } },
    { 34, 700, 500, { 0, 0 } },
    { 41, 0, 0, { 0, 0 } },
};

const PrzCardChance gPrzCardChancesAtlantica[17] = {
    { 0, 2000, 0, { 0, 0 } },
    { 3, 2000, 1500, { 0, 0 } },
    { 7, 0, 500, { 0, 0 } },
    { 8, 200, 0, { 0, 0 } },
    { 9, 500, 500, { 0, 0 } },
    { 14, 300, 500, { 0, 0 } },
    { 18, 1000, 500, { 0, 0 } },
    { 17, 0, 500, { 0, 0 } },
    { 19, 1000, 2000, { 0, 0 } },
    { 21, 500, 0, { 0, 0 } },
    { 22, 500, 1000, { 0, 0 } },
    { 23, 1000, 2000, { 0, 0 } },
    { 26, 0, 1000, { 0, 0 } },
    { 31, 300, 0, { 0, 0 } },
    { 32, 400, 0, { 0, 0 } },
    { 34, 300, 0, { 0, 0 } },
    { 41, 0, 0, { 0, 0 } },
};

const PrzCardChance gPrzCardChancesNeverLand[16] = {
    { 0, 2000, 0, { 0, 0 } },
    { 5, 2000, 1500, { 0, 0 } },
    { 7, 0, 500, { 0, 0 } },
    { 8, 200, 0, { 0, 0 } },
    { 9, 500, 500, { 0, 0 } },
    { 14, 300, 500, { 0, 0 } },
    { 18, 0, 500, { 0, 0 } },
    { 17, 1000, 500, { 0, 0 } },
    { 19, 1000, 1000, { 0, 0 } },
    { 20, 0, 500, { 0, 0 } },
    { 21, 500, 1000, { 0, 0 } },
    { 22, 500, 0, { 0, 0 } },
    { 23, 1000, 1000, { 0, 0 } },
    { 28, 1000, 2000, { 0, 0 } },
    { 31, 0, 500, { 0, 0 } },
    { 41, 0, 0, { 0, 0 } },
};

const PrzCardChance gPrzCardChancesHollowBastion[15] = {
    { 0, 2000, 0, { 0, 0 } },
    { 7, 0, 500, { 0, 0 } },
    { 8, 200, 0, { 0, 0 } },
    { 9, 500, 500, { 0, 0 } },
    { 11, 2000, 1500, { 0, 0 } },
    { 14, 300, 500, { 0, 0 } },
    { 19, 1000, 1000, { 0, 0 } },
    { 20, 0, 500, { 0, 0 } },
    { 21, 500, 1000, { 0, 0 } },
    { 22, 500, 1000, { 0, 0 } },
    { 23, 1000, 1000, { 0, 0 } },
    { 29, 1000, 2000, { 0, 0 } },
    { 30, 1000, 0, { 0, 0 } },
    { 34, 0, 500, { 0, 0 } },
    { 41, 0, 0, { 0, 0 } },
};

const PrzCardChance gPrzCardChancesTwilightTown[25] = {
    { 0, 1500, 0, { 0, 0 } },
    { 7, 1500, 500, { 0, 0 } },
    { 8, 1500, 0, { 0, 0 } },
    { 9, 1500, 500, { 0, 0 } },
    { 14, 300, 500, { 0, 0 } },
    { 16, 500, 1000, { 0, 0 } },
    { 18, 100, 1500, { 0, 0 } },
    { 17, 100, 1500, { 0, 0 } },
    { 19, 100, 1500, { 0, 0 } },
    { 20, 100, 1500, { 0, 0 } },
    { 21, 100, 0, { 0, 0 } },
    { 22, 100, 0, { 0, 0 } },
    { 23, 100, 0, { 0, 0 } },
    { 24, 100, 0, { 0, 0 } },
    { 25, 100, 0, { 0, 0 } },
    { 26, 100, 500, { 0, 0 } },
    { 27, 100, 0, { 0, 0 } },
    { 28, 100, 0, { 0, 0 } },
    { 29, 100, 0, { 0, 0 } },
    { 30, 100, 0, { 0, 0 } },
    { 33, 0, 1000, { 0, 0 } },
    { 34, 300, 0, { 0, 0 } },
    { 35, 500, 0, { 0, 0 } },
    { 36, 500, 0, { 0, 0 } },
    { 41, 0, 0, { 0, 0 } },
};

const PrzCardChance gPrzCardChancesDestinyIslands[16] = {
    { 0, 1000, 0, { 0, 0 } },
    { 12, 1500, 1000, { 0, 0 } },
    { 13, 1500, 1000, { 0, 0 } },
    { 14, 300, 500, { 0, 0 } },
    { 18, 800, 0, { 0, 0 } },
    { 17, 800, 0, { 0, 0 } },
    { 19, 800, 0, { 0, 0 } },
    { 20, 0, 500, { 0, 0 } },
    { 21, 800, 2000, { 0, 0 } },
    { 22, 800, 2000, { 0, 0 } },
    { 23, 800, 2000, { 0, 0 } },
    { 33, 300, 0, { 0, 0 } },
    { 35, 300, 500, { 0, 0 } },
    { 36, 0, 500, { 0, 0 } },
    { 37, 300, 0, { 0, 0 } },
    { 41, 0, 0, { 0, 0 } },
};

const PrzCardChance gPrzCardChancesCastleOblivion[25] = {
    { 0, 500, 0, { 0, 0 } },
    { 7, 1000, 500, { 0, 0 } },
    { 8, 1000, 500, { 0, 0 } },
    { 9, 1000, 500, { 0, 0 } },
    { 14, 300, 500, { 0, 0 } },
    { 15, 1000, 1000, { 0, 0 } },
    { 18, 0, 1000, { 0, 0 } },
    { 17, 0, 1000, { 0, 0 } },
    { 19, 0, 1000, { 0, 0 } },
    { 20, 800, 500, { 0, 0 } },
    { 21, 0, 500, { 0, 0 } },
    { 22, 0, 500, { 0, 0 } },
    { 23, 0, 500, { 0, 0 } },
    { 24, 500, 0, { 0, 0 } },
    { 25, 500, 0, { 0, 0 } },
    { 26, 500, 0, { 0, 0 } },
    { 27, 500, 0, { 0, 0 } },
    { 28, 500, 0, { 0, 0 } },
    { 29, 500, 0, { 0, 0 } },
    { 30, 500, 0, { 0, 0 } },
    { 33, 100, 500, { 0, 0 } },
    { 35, 100, 1000, { 0, 0 } },
    { 36, 200, 300, { 0, 0 } },
    { 37, 500, 200, { 0, 0 } },
    { 41, 0, 0, { 0, 0 } },
};

const PrizeEntry gPrzCardKinds[40] = {
    { { 0, 0 }, CARD_ID(CARD_KINGDOM_KEY, 0) },
    { { 8, 0 }, CARD_ID(CARD_OLYMPIA, 0) },
    { { 1, 0 }, CARD_ID(CARD_THREE_WISHES, 0) },
    { { 2, 0 }, CARD_ID(CARD_CRABCLAW, 0) },
    { { 3, 0 }, CARD_ID(CARD_PUMPKINHEAD, 0) },
    { { 4, 0 }, CARD_ID(CARD_FAIRY_HARP, 0) },
    { { 5, 0 }, CARD_ID(CARD_WISHING_STAR, 0) },
    { { 6, 0 }, CARD_ID(CARD_SPELLBINDER, 0) },
    { { 7, 0 }, CARD_ID(CARD_METAL_CHOCOBO, 0) },
    { { 9, 0 }, CARD_ID(CARD_LIONHEART, 0) },
    { { 10, 0 }, CARD_ID(CARD_LADY_LUCK, 0) },
    { { 11, 0 }, CARD_ID(CARD_DIVINE_ROSE, 0) },
    { { 12, 0 }, CARD_ID(CARD_OATHKEEPER, 0) },
    { { 13, 0 }, CARD_ID(CARD_OBLIVION, 0) },
    { { 14, 0 }, CARD_ID(CARD_ULTIMA_WEAPON, 0) },
    { { 15, 0 }, CARD_ID(CARD_DIAMOND_DUST, 0) },
    { { 16, 0 }, CARD_ID(CARD_ONE_WINGED_ANGEL, 0) },
    { { 17, 0 }, CARD_ID(CARD_FIRE, 0) },
    { { 18, 0 }, CARD_ID(CARD_BLIZZARD, 0) },
    { { 19, 0 }, CARD_ID(CARD_THUNDER, 0) },
    { { 20, 0 }, CARD_ID(CARD_CURE, 0) },
    { { 21, 0 }, CARD_ID(CARD_GRAVITY, 0) },
    { { 22, 0 }, CARD_ID(CARD_STOP, 0) },
    { { 23, 0 }, CARD_ID(CARD_AERO, 0) },
    { { 24, 0 }, CARD_ID(CARD_SIMBA, 0) },
    { { 25, 0 }, CARD_ID(CARD_GENIE, 0) },
    { { 26, 0 }, CARD_ID(CARD_BAMBI, 0) },
    { { 27, 0 }, CARD_ID(CARD_DUMBO, 0) },
    { { 28, 0 }, CARD_ID(CARD_TINKER_BELL, 0) },
    { { 29, 0 }, CARD_ID(CARD_MUSHU, 0) },
    { { 30, 0 }, CARD_ID(CARD_CLOUD, 0) },
    { { 31, 0 }, CARD_ID(CARD_POTION, 0) },
    { { 32, 0 }, CARD_ID(CARD_HI_POTION, 0) },
    { { 33, 0 }, CARD_ID(CARD_MEGA_POTION, 0) },
    { { 34, 0 }, CARD_ID(CARD_ETHER, 0) },
    { { 35, 0 }, CARD_ID(CARD_MEGA_ETHER, 0) },
    { { 36, 0 }, CARD_ID(CARD_ELIXIR, 0) },
    { { 37, 0 }, CARD_ID(CARD_MEGALIXIR, 0) },
    { { 57, 0 }, CARD_LEXAEUS_9 },
    { { 56, 0 }, CARD_ANSEM_9 },
};

const PrizeEntry gPrzStocks[19] = {
    { { 25, 0 }, CARD_MSG_LEARNED_THUNDER_RAID },
    { { 44, 0 }, CARD_MSG_LEARNED_GIFTED_MIRACLE },
    { { 26, 0 }, CARD_MSG_LEARNED_GRAVITY_RAID },
    { { 23, 0 }, CARD_MSG_LEARNED_FIRE_RAID },
    { { 34, 0 }, CARD_MSG_LEARNED_AQUA_SPLASH },
    { { 24, 0 }, CARD_MSG_LEARNED_BLIZZARD_RAID },
    { { 27, 0 }, CARD_MSG_LEARNED_STOP_RAID },
    { { 35, 0 }, CARD_MSG_LEARNED_SHOCK_IMPACT },
    { { 33, 0 }, CARD_MSG_LEARNED_HOMING_BLIZZARA },
    { { 37, 0 }, CARD_MSG_LEARNED_QUAKE },
    { { 58, 0 }, CARD_MSG_LEARNED_BLAZING_DONALD },
    { { 30, 0 }, CARD_MSG_LEARNED_HOMING_FIRA },
    { { 45, 0 }, CARD_MSG_LEARNED_TELEPORT },
    { { 36, 0 }, CARD_MSG_LEARNED_TORNADO },
    { { 56, 0 }, CARD_MSG_LEARNED_CROSS_SLASH_PLUS },
    { { 29, 0 }, CARD_MSG_LEARNED_REFLECT_RAID },
    { { 31, 0 }, CARD_MSG_LEARNED_FIRAGA_BREAK },
    { { 39, 0 }, CARD_MSG_LEARNED_WARP },
    { { 28, 0 }, CARD_MSG_LEARNED_JUDGMENT },
};

const u16 gCardValueWeights[10] = { 500, 1500, 1500, 1600, 1400, 1000, 1000, 600, 500, 400 };

const PrizeEntry gPrizeListEmpty[1] = {
    { { 4, 0 }, 0 },
};

const PrizeEntry gPrizeListTraverseTown[2] = {
    { { 2, 9 }, 0 },
    { { 4, 0 }, 0 },
};

const PrizeEntry gPrizeListAgrabah[3] = {
    { { 0, 21 }, 0 },
    { { 3, 10 }, 0 },
    { { 4, 0 }, 0 },
};

const PrizeEntry gPrizeListHalloweenTown[3] = {
    { { 1, 1 }, 0 },
    { { 3, 2 }, 0 },
    { { 4, 0 }, 0 },
};

const PrizeEntry gPrizeListMonstro[3] = {
    { { 1, 3 }, 0 },
    { { 3, 4 }, 0 },
    { { 4, 0 }, 0 },
};

const PrizeEntry gPrizeListOlympusColiseum[3] = {
    { { 1, 5 }, 0 },
    { { 2, 8 }, 0 },
    { { 4, 0 }, 0 },
};

const PrizeEntry gPrizeListWonderland[3] = {
    { { 0, 22 }, 0 },
    { { 3, 6 }, 0 },
    { { 4, 0 }, 0 },
};

const PrizeEntry gPrizeListAtlantica[4] = {
    { { 1, 7 }, 0 },
    { { 1, 8 }, 0 },
    { { 3, 9 }, 0 },
    { { 4, 0 }, 0 },
};

const PrizeEntry gPrizeListNeverLand[4] = {
    { { 1, 12 }, 0 },
    { { 1, 11 }, 0 },
    { { 3, 0 }, 0 },
    { { 4, 0 }, 0 },
};

const PrizeEntry gPrizeListHollowBastion[4] = {
    { { 1, 14 }, 0 },
    { { 1, 15 }, 0 },
    { { 2, 29 }, 0 },
    { { 4, 0 }, 0 },
};

const PrizeEntry gPrizeListTwilightTown[3] = {
    { { 1, 16 }, 0 },
    { { 3, 17 }, 0 },
    { { 4, 0 }, 0 },
};

const PrizeEntry gPrizeListDestinyIslands[3] = {
    { { 1, 18 }, 0 },
    { { 2, 37 }, 0 },
    { { 4, 0 }, 0 },
};

const PrizeEntry gPrizeListCastleOblivion[1] = {
    { { 4, 0 }, 0 },
};
