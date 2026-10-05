/**
 * mode_staffroll.c
 * Staff Roll Mode
 */

#include "registration_data.h"
#include "system_state.h"
#include "mode.h"
#include "mode_staffroll.h"
#include "sprites_title.h"
#include "sprites_staff_roll.h"
#include "gba/io_reg.h"
#include "staff_roll_text_assets.h"
#include "staff_roll_types.h"
#include "gba/keys.h"
#include "sroll_api.h"
#include "evt_obj_api.h"
#include "malloc.h"
#include "fade.h"
#include "songs.h"
#include "staff_roll_script_text.h"
#include "display.h"
#include "evt_object_types.h"
#include "game_state.h"
#include "gba/defines.h"
#include "gba/syscall.h"
#include "key.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "types.h"
#include "gba/macro.h"
#include <stddef.h>

static const s32 sStaffRollSoraScript0[46] = {
    6, 6, 0, 0, 0, 6,
    4, 6, 0, 0, 208, 85,
    9, 5, 0, 0, 30,
    5, 7, 0, 0, 208, 100, 30,
    2, 5, 100, 0, 1,
    2, 5, 200, 0, 109,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript1[61] = {
    6, 6, 0, 0, 1, 117,
    3, 5, 0, 0, 1,
    4, 6, 0, 0, 17, 70,
    9, 5, 0, 0, 30,
    5, 7, 0, 0, 32, 85, 30,
    2, 5, 100, 0, 112,
    2, 5, 120, 0, 125,
    2, 5, 256, 0, 112,
    2, 5, 306, 0, 136,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript2[63] = {
    6, 6, 0, 0, 2, 149,
    4, 6, 0, 0, 218, 85,
    9, 5, 0, 0, 30,
    5, 7, 0, 0, 203, 100, 30,
    2, 5, 100, 0, 144,
    2, 5, 160, 0, 164,
    2, 5, 280, 0, 144,
    2, 5, 340, 0, 152,
    10, 5, 400, 0, 30,
    5, 7, 400, 0, 188, 115, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript3[80] = {
    6, 6, 0, 0, 9, 245,
    3, 5, 0, 0, 1,
    4, 6, 0, 0, 17, 85,
    9, 5, 0, 0, 30,
    4, 6, 0, 0, 32, 100,
    2, 5, 50, 0, 236,
    6, 6, 150, 1, 8, 235,
    4, 6, 150, 1, 208, 100,
    11, 5, 150, 1, 8,
    14, 4, 160, 1,
    15, 5, 160, 0, 0,
    2, 5, 180, 0, 254,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    7, 4, 480, 1,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript4[93] = {
    6, 6, 0, 0, 12, 270,
    4, 6, 0, 0, 208, 130,
    9, 5, 0, 0, 30,
    2, 5, 160, 0, 276,
    6, 6, 180, 1, 68, 743,
    3, 5, 180, 1, 1,
    4, 6, 180, 1, 40, 120,
    6, 6, 200, 2, 59, 668,
    3, 5, 200, 2, 1,
    4, 6, 200, 2, 40, 120,
    5, 7, 200, 2, 40, 60, 60,
    7, 4, 232, 1,
    2, 5, 273, 2, 664,
    2, 5, 283, 2, 666,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    7, 4, 480, 2,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript5[79] = {
    6, 6, 0, 1, 7, 222,
    4, 6, 0, 1, 208, 120,
    9, 5, 0, 0, 30,
    6, 6, 50, 0, 17, 337,
    3, 5, 50, 0, 1,
    4, 6, 50, 0, 32, 80,
    11, 5, 50, 0, 30,
    14, 4, 95, 0,
    2, 5, 100, 1, 228,
    2, 5, 260, 1, 222,
    2, 5, 280, 1, 221,
    2, 5, 300, 0, 340,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    7, 4, 480, 1,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript6[141] = {
    6, 6, 0, 0, 55, 631,
    4, 6, 0, 0, 223, 65,
    9, 5, 0, 0, 30,
    5, 7, 0, 0, 208, 80, 30,
    6, 6, 100, 1, 60, 676,
    4, 6, 100, 1, 24, 120,
    3, 5, 100, 1, 1,
    11, 5, 100, 1, 30,
    6, 6, 100, 2, 61, 678,
    4, 6, 100, 2, 60, 108,
    3, 5, 100, 2, 1,
    11, 5, 100, 2, 30,
    14, 4, 135, 1,
    14, 4, 135, 2,
    2, 5, 140, 0, 627,
    3, 5, 260, 1, 0,
    3, 5, 270, 2, 0,
    2, 5, 280, 1, 677,
    2, 5, 290, 2, 680,
    2, 5, 300, 0, 631,
    16, 5, 370, 1, 1,
    16, 5, 380, 2, 1,
    16, 5, 400, 0, 1,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    7, 4, 480, 1,
    7, 4, 480, 2,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript7[60] = {
    6, 6, 0, 0, 14, 299,
    4, 6, 0, 0, 24, 100,
    3, 5, 0, 0, 1,
    6, 6, 0, 1, 37, 456,
    4, 6, 0, 1, 64, 72,
    16, 5, 0, 1, 3,
    9, 5, 0, 0, 30,
    2, 5, 150, 0, 306,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    7, 4, 480, 1,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript8[113] = {
    6, 6, 0, 0, 15, 318,
    4, 6, 0, 0, 211, 75,
    9, 5, 0, 0, 30,
    5, 7, 0, 0, 196, 90, 30,
    6, 6, 80, 1, 38, 462,
    4, 6, 80, 1, 17, 95,
    3, 5, 80, 1, 1,
    11, 5, 80, 1, 30,
    5, 7, 80, 1, 32, 110, 60,
    14, 4, 145, 1,
    2, 5, 150, 0, 322,
    15, 5, 150, 0, 3,
    2, 5, 200, 0, 314,
    3, 5, 210, 0, 1,
    2, 5, 220, 0, 316,
    2, 5, 230, 0, 320,
    10, 5, 400, 0, 30,
    16, 5, 400, 0, 4,
    16, 5, 400, 1, 1,
    7, 4, 480, 0,
    7, 4, 480, 1,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript9[61] = {
    6, 6, 0, 0, 13, 290,
    4, 6, 0, 0, 32, 100,
    3, 5, 0, 0, 1,
    9, 5, 0, 0, 30,
    2, 5, 50, 0, 288,
    2, 5, 150, 0, 298,
    2, 5, 250, 0, 292,
    2, 5, 350, 0, 294,
    10, 5, 400, 0, 30,
    5, 7, 400, 0, 32, 115, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript10[70] = {
    6, 6, 0, 0, 24, 387,
    4, 6, 0, 0, 208, 108,
    6, 6, 0, 1, 23, 381,
    3, 5, 0, 1, 1,
    4, 6, 0, 1, 24, 108,
    9, 5, 0, 0, 30,
    2, 5, 100, 1, 385,
    2, 5, 200, 1, 386,
    2, 5, 300, 0, 392,
    2, 5, 300, 1, 381,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    7, 4, 480, 1,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript11[44] = {
    6, 6, 0, 0, 16, 328,
    4, 6, 0, 0, 48, 108,
    3, 5, 0, 0, 1,
    9, 5, 0, 0, 30,
    2, 5, 140, 0, 335,
    2, 5, 270, 0, 332,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript12[65] = {
    6, 6, 0, 0, 10, 260,
    3, 5, 0, 0, 1,
    4, 6, 0, 0, 20, 100,
    6, 6, 0, 1, 54, 623,
    4, 6, 0, 1, 212, 100,
    9, 5, 0, 0, 30,
    2, 5, 100, 1, 626,
    2, 5, 200, 1, 623,
    2, 5, 300, 1, 626,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    7, 4, 480, 1,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript13[101] = {
    6, 6, 0, 0, 76, 827,
    3, 5, 0, 0, 1,
    4, 6, 0, 0, 24, 100,
    6, 6, 0, 1, 70, 756,
    4, 6, 0, 1, 220, 100,
    6, 6, 0, 2, 72, 810,
    3, 5, 0, 2, 1,
    4, 6, 0, 2, 184, 108,
    9, 5, 0, 0, 30,
    2, 5, 100, 0, 829,
    2, 5, 200, 0, 829,
    2, 5, 200, 1, 798,
    15, 5, 280, 1, 5,
    2, 5, 300, 0, 829,
    2, 5, 300, 1, 799,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    7, 4, 480, 1,
    7, 4, 480, 2,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript14[51] = {
    6, 6, 0, 0, 19, 344,
    4, 6, 0, 0, 204, 110,
    9, 5, 0, 0, 30,
    2, 5, 120, 0, 348,
    2, 5, 240, 0, 351,
    2, 5, 300, 0, 349,
    10, 5, 400, 0, 30,
    5, 7, 400, 0, 189, 95, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript15[61] = {
    6, 6, 0, 0, 57, 638,
    4, 6, 0, 0, 24, 90,
    3, 5, 0, 0, 1,
    9, 5, 0, 0, 30,
    2, 5, 40, 0, 642,
    2, 5, 120, 0, 644,
    2, 5, 290, 0, 638,
    2, 5, 300, 0, 640,
    10, 5, 400, 0, 30,
    5, 7, 400, 0, 39, 105, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollSoraScript16[88] = {
    6, 6, 0, 0, 35, 424,
    4, 6, 0, 0, 120, 100,
    9, 5, 0, 0, 80,
    5, 7, 0, 0, 216, 100, 80,
    6, 6, 100, 1, 34, 420,
    4, 6, 100, 1, 120, 100,
    3, 5, 100, 1, 1,
    11, 5, 100, 1, 80,
    5, 7, 100, 1, 24, 100, 80,
    14, 4, 185, 1,
    2, 5, 250, 1, 421,
    3, 5, 300, 0, 0,
    2, 5, 300, 0, 425,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    7, 4, 480, 1,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript0[51] = {
    6, 6, 0, 0, 44, 516,
    3, 5, 0, 0, 1,
    4, 6, 0, 0, 17, 95,
    9, 5, 0, 0, 30,
    5, 7, 0, 0, 32, 110, 30,
    2, 5, 100, 0, 514,
    2, 5, 200, 0, 567,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript1[51] = {
    6, 6, 0, 0, 69, 747,
    4, 6, 0, 0, 223, 85,
    9, 5, 0, 0, 30,
    5, 7, 0, 0, 208, 100, 30,
    2, 5, 190, 0, 745,
    2, 5, 200, 0, 752,
    2, 5, 300, 0, 751,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript2[44] = {
    6, 6, 0, 0, 43, 485,
    3, 5, 0, 0, 1,
    4, 6, 0, 0, 32, 110,
    9, 5, 0, 0, 30,
    2, 5, 150, 0, 509,
    2, 5, 300, 0, 495,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript3[39] = {
    6, 6, 0, 0, 81, 856,
    4, 6, 0, 0, 200, 110,
    9, 5, 0, 0, 30,
    2, 5, 150, 0, 868,
    2, 5, 200, 0, 870,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript4[39] = {
    6, 6, 0, 0, 67, 721,
    3, 5, 0, 0, 1,
    4, 6, 0, 0, 28, 110,
    9, 5, 0, 0, 30,
    2, 5, 200, 0, 727,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript5[34] = {
    6, 6, 0, 0, 83, 889,
    4, 6, 0, 0, 216, 110,
    9, 5, 0, 0, 30,
    2, 5, 200, 0, 899,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript6[44] = {
    6, 6, 0, 0, 82, 887,
    3, 5, 0, 0, 1,
    4, 6, 0, 0, 32, 110,
    9, 5, 0, 0, 30,
    2, 5, 200, 0, 883,
    2, 5, 300, 0, 888,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript7[93] = {
    6, 6, 0, 0, 79, 841,
    4, 6, 0, 0, 184, 110,
    9, 5, 0, 0, 30,
    2, 5, 100, 0, 847,
    6, 6, 100, 1, 80, 853,
    4, 6, 100, 1, 184, 60,
    16, 5, 100, 1, 5,
    2, 5, 123, 0, 848,
    5, 7, 160, 1, 184, 110, 90,
    7, 4, 260, 1,
    6, 6, 260, 2, 80, 854,
    4, 6, 260, 2, 184, 110,
    7, 4, 300, 2,
    2, 5, 300, 0, 849,
    2, 5, 310, 0, 850,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript8[49] = {
    6, 6, 0, 0, 30, 410,
    4, 6, 0, 0, 48, 110,
    3, 5, 0, 0, 1,
    9, 5, 0, 0, 30,
    2, 5, 100, 0, 415,
    2, 5, 200, 0, 416,
    2, 5, 300, 0, 414,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript9[46] = {
    6, 6, 0, 0, 21, 364,
    4, 6, 0, 0, 212, 110,
    9, 5, 0, 0, 30,
    5, 7, 0, 0, 200, 110, 30,
    2, 5, 150, 0, 361,
    2, 5, 250, 0, 365,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript10[110] = {
    6, 6, 0, 0, 25, 397,
    4, 6, 0, 0, 25, 105,
    3, 5, 0, 0, 1,
    6, 6, 0, 1, 26, 397,
    4, 6, 0, 1, 40, 256,
    3, 5, 0, 1, 1,
    9, 5, 0, 0, 30,
    5, 7, 0, 0, 40, 120, 30,
    2, 5, 100, 0, 395,
    2, 5, 200, 0, 401,
    6, 6, 210, 2, 27, 404,
    3, 5, 210, 2, 1,
    4, 6, 210, 2, 40, 120,
    4, 6, 235, 0, 40, 256,
    4, 6, 235, 1, 40, 120,
    2, 5, 235, 1, 402,
    7, 4, 275, 2,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    7, 4, 480, 1,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript11[54] = {
    6, 6, 0, 0, 47, 582,
    4, 6, 0, 0, 200, 110,
    9, 5, 0, 0, 30,
    2, 5, 160, 0, 581,
    2, 5, 170, 0, 579,
    2, 5, 180, 0, 576,
    2, 5, 280, 0, 584,
    2, 5, 300, 0, 585,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript12[44] = {
    6, 6, 0, 0, 20, 353,
    4, 6, 0, 0, 52, 110,
    3, 5, 0, 0, 1,
    9, 5, 0, 0, 30,
    2, 5, 100, 0, 356,
    2, 5, 300, 0, 360,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript13[34] = {
    6, 6, 0, 0, 64, 688,
    4, 6, 0, 0, 208, 110,
    9, 5, 0, 0, 30,
    2, 5, 200, 0, 694,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript14[39] = {
    6, 6, 0, 0, 84, 907,
    4, 6, 0, 0, 32, 110,
    3, 5, 0, 0, 1,
    9, 5, 0, 0, 30,
    2, 5, 150, 0, 908,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript15[44] = {
    6, 6, 0, 0, 65, 695,
    4, 6, 0, 0, 216, 100,
    9, 5, 0, 0, 30,
    2, 5, 100, 0, 706,
    2, 5, 250, 0, 695,
    2, 5, 280, 0, 698,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    0, 0, -1,
};

static const s32 sStaffRollRikuScript16[88] = {
    6, 6, 0, 1, 34, 420,
    4, 6, 0, 1, 128, 100,
    3, 5, 0, 1, 1,
    9, 5, 0, 0, 80,
    5, 7, 0, 1, 24, 100, 80,
    6, 6, 100, 0, 35, 424,
    4, 6, 100, 0, 120, 100,
    11, 5, 100, 0, 80,
    5, 7, 100, 0, 208, 100, 80,
    14, 4, 185, 0,
    2, 5, 250, 0, 425,
    3, 5, 300, 0, 0,
    2, 5, 300, 1, 421,
    10, 5, 400, 0, 30,
    7, 4, 480, 0,
    7, 4, 480, 1,
    0, 0, -1,
};

#ifdef VERSION_US
static u8* sStaffRollLines[632] = {
    gStaffRollSecnScenarioText,
    gStaffRollSpaceText,
    gStaffRollScenarioSupervisorsText,
    gStaffRollSkipText,
    gStaffRollScenarioSupervisorsNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecn2DArtText,
    gStaffRollSpaceText,
    gStaffRollCharacterArtSupervisorText,
    gStaffRollSkipText,
    gStaffRollCharacterArtSupervisorNamesText,
    gStaffRollSkipText,
    gStaffRollCharacterFaceArtistText,
    gStaffRollSkipText,
    gStaffRollCharacterFaceArtistNamesText,
    gStaffRollSkipText,
    gStaffRollCharacterDesignersText,
    gStaffRollSkipText,
    gStaffRollCharacterDesignersNamesText,
    gStaffRollSkipText,
    gStaffRollEnemyDesignText,
    gStaffRollSkipText,
    gStaffRollEnemyDesignNames1Text,
    gStaffRollSkipText,
    gStaffRollEnemyDesignNames2Text,
    gStaffRollSkipText,
    gStaffRoll2DArtistsText,
    gStaffRollSkipText,
    gStaffRoll2DArtistsNames1Text,
    gStaffRollSkipText,
    gStaffRoll2DArtistsNames2Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecn3DAnimationText,
    gStaffRollSpaceText,
    gStaffRollAnimationStaffText,
    gStaffRollSkipText,
    gStaffRollAnimationStaffNames1Text,
    gStaffRollSkipText,
    gStaffRollAnimationStaffNames2Text,
    gStaffRollSkipText,
    gStaffRollAnimationStaffNames3Text,
    gStaffRollSkipText,
    gStaffRollAnimationStaffNames4Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollDevelopmentTeamText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSkipText,
    gStaffRollSecnPlanningText,
    gStaffRollSpaceText,
    gStaffRollGeneralPlannersText,
    gStaffRollSkipText,
    gStaffRollGeneralPlannersNamesText,
    gStaffRollSkipText,
    gStaffRollTheHundredAcreWoodText,
    gStaffRollSkipText,
    gStaffRollTheHundredAcreWoodNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnEventCreationText,
    gStaffRollSpaceText,
    gStaffRollScriptWriterText,
    gStaffRollSkipText,
    gStaffRollScriptWriterNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnProgrammingText,
    gStaffRollSpaceText,
    gStaffRollProgrammingNames1Text,
    gStaffRollSkipText,
    gStaffRollProgrammingNames2Text,
    gStaffRollSkipText,
    gStaffRollProgrammingNames3Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnGraphicDesignText,
    gStaffRollSpaceText,
    gStaffRollCharacterArtistsText,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames1Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames2Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames3Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames4Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames5Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames6Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames7Text,
    gStaffRollSkipText,
    gStaffRollBgDesignersText,
    gStaffRollSkipText,
    gStaffRollBgDesignersNames1Text,
    gStaffRollSkipText,
    gStaffRollBgDesignersNames2Text,
    gStaffRollSkipText,
    gStaffRollBgDesignersNames3Text,
    gStaffRollSkipText,
    gStaffRollBgDesignersNames4Text,
    gStaffRollSkipText,
    gStaffRollVfxDesignerText,
    gStaffRollSkipText,
    gStaffRollVfxDesignerNamesText,
    gStaffRollSkipText,
    gStaffRollMenuDesignerText,
    gStaffRollSkipText,
    gStaffRollMenuDesignerNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnSoundText,
    gStaffRollSpaceText,
    gStaffRollSynthesizerOperatorText,
    gStaffRollSkipText,
    gStaffRollSynthesizerOperatorNamesText,
    gStaffRollSkipText,
    gStaffRollSoundEditorText,
    gStaffRollSkipText,
    gStaffRollSoundEditorNamesText,
    gStaffRollSkipText,
    gStaffRollDialogueEditorText,
    gStaffRollSkipText,
    gStaffRollDialogueEditorNamesText,
    gStaffRollSkipText,
    gStaffRollProductionManagerText,
    gStaffRollSkipText,
    gStaffRollSoundProductionManagerNamesText,
    gStaffRollSkipText,
    gStaffRollProductionAssistantsText,
    gStaffRollSkipText,
    gStaffRollProductionAssistantsNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnEndingThemeText,
    gStaffRollSpaceText,
    gStaffRollSecnThemeSongText,
    gStaffRollFont1Text,
    gStaffRollThemeSongWrittenByText,
    gStaffRollThemeSongProducedBy1Text,
    gStaffRollThemeSongProducedBy2Text,
    gStaffRollThemeSongArrangedByText,
    gStaffRollThemeSongKeyboardsProgrammingText,
    gStaffRollThemeSongBasicProgrammingText,
    gStaffRollThemeSongSynthesizerProgrammingText,
    gStaffRollThemeSongAcousticGuitarText,
    gStaffRollThemeSongAllVocalsText,
    gStaffRollBlankText,
    gStaffRollThemeSongRecordedByText,
    gStaffRollThemeSongMixedByText,
    gStaffRollBlankText,
    gStaffRollThemeSongLicensedByText,
    gStaffRollBlankText,
    gStaffRollThemeSongSoundtrackText,
    gStaffRollFont0Text,
    gStaffRollSpaceText,
    gStaffRollSecnBuenaVistaGamesJapanText,
    gStaffRollSpaceText,
    gStaffRollSeniorProducerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesJapanSeniorProducerNamesText,
    gStaffRollSkipText,
    gStaffRollSeniorManagerMarketingText,
    gStaffRollSkipText,
    gStaffRollSeniorManagerMarketingNamesText,
    gStaffRollSkipText,
    gStaffRollGeneralManagerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesJapanGeneralManagerNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnBuenaVistaGamesText,
    gStaffRollSpaceText,
    gStaffRollVpGlobalProductionText,
    gStaffRollSkipText,
    gStaffRollVpGlobalProductionNamesText,
    gStaffRollSkipText,
    gStaffRollSeniorProducerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesSeniorProducerNamesText,
    gStaffRollSkipText,
    gStaffRollProducerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesProducerNamesText,
    gStaffRollSkipText,
    gStaffRollLocalizationManagerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesLocalizationManagerNamesText,
    gStaffRollSkipText,
    gStaffRollVpMarketingText,
    gStaffRollSkipText,
    gStaffRollVpMarketingNamesText,
    gStaffRollSkipText,
    gStaffRollDirectorMarketingText,
    gStaffRollSkipText,
    gStaffRollDirectorMarketingNamesText,
    gStaffRollSkipText,
    gStaffRollManagerMarketingText,
    gStaffRollSkipText,
    gStaffRollManagerMarketingNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnVoiceTalentsText,
    gStaffRollSpaceText,
    gStaffRollSoraVoiceText,
    gStaffRollSkipText,
    gStaffRollRikuVoiceText,
    gStaffRollSkipText,
    gStaffRollDonaldDuckVoiceText,
    gStaffRollSkipText,
    gStaffRollGoofyVoiceText,
    gStaffRollSkipText,
    gStaffRollAnsemVoiceText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollTheBeastVoiceText,
    gStaffRollSkipText,
    gStaffRollAladdinVoiceText,
    gStaffRollSkipText,
    gStaffRollGenieVoiceText,
    gStaffRollSkipText,
    gStaffRollIagoVoiceText,
    gStaffRollSkipText,
    gStaffRollArielVoiceText,
    gStaffRollSkipText,
    gStaffRollUrsulaVoiceText,
    gStaffRollSkipText,
    gStaffRollJackVoiceText,
    gStaffRollSkipText,
    gStaffRollBoogieVoiceText,
    gStaffRollSkipText,
    gStaffRollHadesVoiceText,
    gStaffRollSkipText,
    gStaffRollPeterPanVoiceText,
    gStaffRollSkipText,
    gStaffRollCaptainHookVoiceText,
    gStaffRollSkipText,
    gStaffRollCloudVoiceText,
    gStaffRollSkipText,
    gStaffRollAxelVoiceText,
    gStaffRollSkipText,
    gStaffRollAndAlsoNames1Text,
    gStaffRollSkipText,
    gStaffRollAndAlsoNames2Text,
    gStaffRollSkipText,
    gStaffRollFont1Text,
    gStaffRollBlankText,
    gStaffRollWinnieThePoohTitleText,
    gStaffRollWinnieThePoohWordsMusicByText,
    gStaffRollWinnieThePoohCopyrightText,
    gStaffRollBlankText,
    gStaffRollThisIsHalloweenTitleText,
    gStaffRollThisIsHalloweenWordsMusicByText,
    gStaffRollThisIsHalloweenCopyrightText,
    gStaffRollBlankText,
    gStaffRollUnderTheSeaTitleText,
    gStaffRollUnderTheSeaMusicWordsByText,
    gStaffRollUnderTheSeaCopyright1Text,
    gStaffRollUnderTheSeaCopyright2Text,
    gStaffRollFont0Text,
    gStaffRollSpaceText,
    gStaffRollSecnOutsideContractorsText,
    gStaffRollSpaceText,
    gStaffRollMovieCompressionText,
    gStaffRollSkipText,
    gStaffRollMovieCompressionNames1Text,
    gStaffRollSkipText,
    gStaffRollMovieCompressionNames2Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollMovieCompressionNames3Text,
    gStaffRollSkipText,
    gStaffRollMovieCompressionNames4Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollMovieCompressionNames5Text,
    gStaffRollSkipText,
    gStaffRollMovieCompressionNames6Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollMovieCompressionNames7Text,
    gStaffRollSkipText,
    gStaffRollMovieCompressionNames8Text,
    gStaffRollSkipText,
    gStaffRollPvCmMaterialsText,
    gStaffRollSkipText,
    gStaffRollDirectorText,
    gStaffRollSkipText,
    gStaffRollPvCmMaterialsDirectorNamesText,
    gStaffRollSkipText,
    gStaffRollEditorText,
    gStaffRollSkipText,
    gStaffRollPvCmMaterialsEditorNamesText,
    gStaffRollSkipText,
    gStaffRollCoordinatorText,
    gStaffRollSkipText,
    gStaffRollPvCmMaterialsCoordinatorNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnManagementText,
    gStaffRollSpaceText,
    gStaffRollProductionManagerText,
    gStaffRollSkipText,
    gStaffRollManagementProductionManagerNamesText,
    gStaffRollSkipText,
    gStaffRollBusinessManagerText,
    gStaffRollSkipText,
    gStaffRollBusinessManagerNamesText,
    gStaffRollSkipText,
    gStaffRollProductionAssistantText,
    gStaffRollSkipText,
    gStaffRollProductionAssistantNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnQualityAssuranceText,
    gStaffRollSpaceText,
    gStaffRollGeneralManagerText,
    gStaffRollSkipText,
    gStaffRollQualityAssuranceGeneralManagerNamesText,
    gStaffRollSkipText,
    gStaffRollQaDirectorText,
    gStaffRollSkipText,
    gStaffRollQaDirectorNamesText,
    gStaffRollSkipText,
    gStaffRollQaCoordinatorsText,
    gStaffRollSkipText,
    gStaffRollQualityAssuranceQaCoordinatorsNamesText,
    gStaffRollSkipText,
    gStaffRollQaAssistantCoordinatorsText,
    gStaffRollSkipText,
    gStaffRollQaAssistantCoordinatorsNames1Text,
    gStaffRollSkipText,
    gStaffRollQaAssistantCoordinatorsNames2Text,
    gStaffRollSkipText,
    gStaffRollQaStaffText,
    gStaffRollSkipText,
    gStaffRollQaStaffNames1Text,
    gStaffRollSkipText,
    gStaffRollQaStaffNames2Text,
    gStaffRollSkipText,
    gStaffRollQaStaffNames3Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollAllQaStaffText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnLegalAffairsText,
    gStaffRollSpaceText,
    gStaffRollLegalManagerText,
    gStaffRollSkipText,
    gStaffRollLegalManagerNamesText,
    gStaffRollSkipText,
    gStaffRollLegalAffairsCoordinatorsText,
    gStaffRollSkipText,
    gStaffRollLegalAffairsCoordinatorsNamesText,
    gStaffRollSkipText,
    gStaffRollPatentDepartmentStaffText,
    gStaffRollSkipText,
    gStaffRollPatentDepartmentStaffNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSkipText,
    gStaffRollSecnLocalizationTeamText,
    gStaffRollSkipText,
    gStaffRollGeneralManagerText,
    gStaffRollSkipText,
    gStaffRollLocalizationTeamGeneralManagerNamesText,
    gStaffRollSkipText,
    gStaffRollLocalizationDirectorText,
    gStaffRollSkipText,
    gStaffRollLocalizationDirectorNamesText,
    gStaffRollSkipText,
    gStaffRollLocalizationSpecialistText,
    gStaffRollSkipText,
    gStaffRollLocalizationSpecialistNamesText,
    gStaffRollSkipText,
    gStaffRollLocalizationAssistantText,
    gStaffRollSkipText,
    gStaffRollLocalizationAssistantNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSkipText,
    gStaffRollSecnSquareEnixIncText,
    gStaffRollSkipText,
    gStaffRollQualityAssuranceManagerText,
    gStaffRollSkipText,
    gStaffRollQualityAssuranceManagerNamesText,
    gStaffRollSkipText,
    gStaffRollAssistantQaManagerText,
    gStaffRollSkipText,
    gStaffRollAssistantQaManagerNamesText,
    gStaffRollSkipText,
    gStaffRollSeniorLeadProductAnalystText,
    gStaffRollSkipText,
    gStaffRollSeniorLeadProductAnalystNamesText,
    gStaffRollSkipText,
    gStaffRollLeadProductAnalystText,
    gStaffRollSkipText,
    gStaffRollLeadProductAnalystNamesText,
    gStaffRollSkipText,
    gStaffRollProductAnalystsText,
    gStaffRollSkipText,
    gStaffRollProductAnalystsNames1Text,
    gStaffRollSkipText,
    gStaffRollProductAnalystsNames2Text,
    gStaffRollSkipText,
    gStaffRollProductAnalystsNames3Text,
    gStaffRollSkipText,
    gStaffRollProductAnalystsNames4Text,
    gStaffRollSkipText,
    gStaffRollProductAnalystsNames5Text,
    gStaffRollSkipText,
    gStaffRollQaTranslatorsText,
    gStaffRollSkipText,
    gStaffRollQaTranslatorsNamesText,
    gStaffRollSkipText,
    gStaffRollLocalizationManagerText,
    gStaffRollSkipText,
    gStaffRollSquareEnixIncLocalizationManagerNamesText,
    gStaffRollSkipText,
    gStaffRollCustomerSupportText,
    gStaffRollSkipText,
    gStaffRollCustomerSupportNamesText,
    gStaffRollSkipText,
    gStaffRollMarketingCommunicationsText,
    gStaffRollSkipText,
    gStaffRollMarketingCommunicationsNamesText,
    gStaffRollSkipText,
    gStaffRollMarketingText,
    gStaffRollSkipText,
    gStaffRollMarketingNamesText,
    gStaffRollSkipText,
    gStaffRollSalesText,
    gStaffRollSkipText,
    gStaffRollSalesNamesText,
    gStaffRollSkipText,
    gStaffRollPresidentCooText,
    gStaffRollSkipText,
    gStaffRollPresidentCooNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnSpecialThanksText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks1Names1Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks2Names1Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks2Names2Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks2Names3Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks3Names1Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks3Names2Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks3Names3Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks3Names4Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks3Names5Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks4NamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks5Names1Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names2Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names3Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names4Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names5Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names6Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names7Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names8Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names9Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names10Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names11Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names12Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names13Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names14Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names15Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names16Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names17Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names18Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks6NamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollAllStaffFansText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnJupiterCorporationText,
    gStaffRollSpaceText,
    gStaffRollProducerText,
    gStaffRollSkipText,
    gStaffRollJupiterCorporationProducerNamesText,
    gStaffRollSkipText,
    gStaffRollExecutiveProducerText,
    gStaffRollSkipText,
    gStaffRollJupiterCorporationExecutiveProducerNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollExecutiveProducerText,
    gStaffRollSkipText,
    gStaffRollFinalExecutiveProducerNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollLogoDisneyText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollLogoSquareEnixText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollLogoJupiterText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    NULL,
};

static const s32* sStaffRollSoraScripts[17] = {
    sStaffRollSoraScript0,
    sStaffRollSoraScript1,
    sStaffRollSoraScript2,
    sStaffRollSoraScript3,
    sStaffRollSoraScript4,
    sStaffRollSoraScript5,
    sStaffRollSoraScript6,
    sStaffRollSoraScript7,
    sStaffRollSoraScript8,
    sStaffRollSoraScript9,
    sStaffRollSoraScript10,
    sStaffRollSoraScript11,
    sStaffRollSoraScript12,
    sStaffRollSoraScript13,
    sStaffRollSoraScript14,
    sStaffRollSoraScript15,
    sStaffRollSoraScript16,
};

static const s32* sStaffRollRikuScripts[17] = {
    sStaffRollRikuScript0,
    sStaffRollRikuScript1,
    sStaffRollRikuScript2,
    sStaffRollRikuScript3,
    sStaffRollRikuScript4,
    sStaffRollRikuScript5,
    sStaffRollRikuScript6,
    sStaffRollRikuScript7,
    sStaffRollRikuScript8,
    sStaffRollRikuScript9,
    sStaffRollRikuScript10,
    sStaffRollRikuScript11,
    sStaffRollRikuScript12,
    sStaffRollRikuScript13,
    sStaffRollRikuScript14,
    sStaffRollRikuScript15,
    sStaffRollRikuScript16,
};

static u8* sStaffRollSpaceText = gStaffRollSpaceText;
static const u8* sStaffRollTildeText = gStaffRollTildeUs;
#endif
#ifdef VERSION_JP
static u8* sStaffRollLines[704] = {
    gStaffRollSecnScenarioText,
    gStaffRollSpaceText,
    gStaffRollScenarioSupervisorsText,
    gStaffRollSkipText,
    gStaffRollScenarioSupervisorsNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecn2DArtText,
    gStaffRollSpaceText,
    gStaffRollCharacterArtSupervisorText,
    gStaffRollSkipText,
    gStaffRollCharacterArtSupervisorNamesText,
    gStaffRollSkipText,
    gStaffRollCharacterFaceArtistText,
    gStaffRollSkipText,
    gStaffRollCharacterFaceArtistNamesText,
    gStaffRollSkipText,
    gStaffRollCharacterDesignersText,
    gStaffRollSkipText,
    gStaffRollCharacterDesignersNamesText,
    gStaffRollSkipText,
    gStaffRollEnemyDesignText,
    gStaffRollSkipText,
    gStaffRollEnemyDesignNames1Text,
    gStaffRollSkipText,
    gStaffRollEnemyDesignNames2Text,
    gStaffRollSkipText,
    gStaffRoll2DArtistsText,
    gStaffRollSkipText,
    gStaffRoll2DArtistsNames1Text,
    gStaffRollSkipText,
    gStaffRoll2DArtistsNames2Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecn3DAnimationText,
    gStaffRollSpaceText,
    gStaffRollAnimationStaffText,
    gStaffRollSkipText,
    gStaffRollAnimationStaffNames1Text,
    gStaffRollSkipText,
    gStaffRollAnimationStaffNames2Text,
    gStaffRollSkipText,
    gStaffRollAnimationStaffNames3Text,
    gStaffRollSkipText,
    gStaffRollAnimationStaffNames4Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollDevelopmentTeamText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSkipText,
    gStaffRollSecnPlanningText,
    gStaffRollSpaceText,
    gStaffRollGeneralPlannersText,
    gStaffRollSkipText,
    gStaffRollGeneralPlannersNamesText,
    gStaffRollSkipText,
    gStaffRollTheHundredAcreWoodText,
    gStaffRollSkipText,
    gStaffRollTheHundredAcreWoodNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnEventCreationText,
    gStaffRollSpaceText,
    gStaffRollScriptWriterText,
    gStaffRollSkipText,
    gStaffRollScriptWriterNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnProgrammingText,
    gStaffRollSpaceText,
    gStaffRollProgrammingNames1Text,
    gStaffRollSkipText,
    gStaffRollProgrammingNames2Text,
    gStaffRollSkipText,
    gStaffRollProgrammingNames3Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnGraphicDesignText,
    gStaffRollSpaceText,
    gStaffRollCharacterArtistsText,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames1Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames2Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames3Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames4Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames5Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames6Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames7Text,
    gStaffRollSkipText,
    gStaffRollBgDesignersText,
    gStaffRollSkipText,
    gStaffRollBgDesignersNames1Text,
    gStaffRollSkipText,
    gStaffRollBgDesignersNames2Text,
    gStaffRollSkipText,
    gStaffRollBgDesignersNames3Text,
    gStaffRollSkipText,
    gStaffRollBgDesignersNames4Text,
    gStaffRollSkipText,
    gStaffRollVfxDesignerText,
    gStaffRollSkipText,
    gStaffRollVfxDesignerNamesText,
    gStaffRollSkipText,
    gStaffRollMenuDesignerText,
    gStaffRollSkipText,
    gStaffRollMenuDesignerNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnSoundText,
    gStaffRollSpaceText,
    gStaffRollSynthesizerOperatorText,
    gStaffRollSkipText,
    gStaffRollSynthesizerOperatorNamesText,
    gStaffRollSkipText,
    gStaffRollSoundEditorText,
    gStaffRollSkipText,
    gStaffRollSoundEditorNamesText,
    gStaffRollSkipText,
    gStaffRollDialogueEditorText,
    gStaffRollSkipText,
    gStaffRollDialogueEditorNamesText,
    gStaffRollSkipText,
    gStaffRollProductionManagerText,
    gStaffRollSkipText,
    gStaffRollSoundProductionManagerNamesText,
    gStaffRollSkipText,
    gStaffRollProductionAssistantsText,
    gStaffRollSkipText,
    gStaffRollProductionAssistantsNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnEndingThemeText,
    gStaffRollSpaceText,
    gStaffRollSecnThemeSongText,
    gStaffRollFont1Text,
    gStaffRollThemeSongWrittenByText,
    gStaffRollThemeSongProducedBy1Text,
    gStaffRollThemeSongProducedBy2Text,
    gStaffRollThemeSongArrangedByText,
    gStaffRollThemeSongKeyboardsProgrammingText,
    gStaffRollThemeSongBasicProgrammingText,
    gStaffRollThemeSongSynthesizerProgrammingText,
    gStaffRollThemeSongAcousticGuitarText,
    gStaffRollThemeSongAllVocalsText,
    gStaffRollBlankText,
    gStaffRollThemeSongRecordedByText,
    gStaffRollThemeSongMixedByText,
    gStaffRollBlankText,
    gStaffRollThemeSongLicensedByText,
    gStaffRollBlankText,
    gStaffRollThemeSongSoundtrackText,
    gStaffRollFont0Text,
    gStaffRollSpaceText,
    gStaffRollSecnBuenaVistaGamesJapanText,
    gStaffRollSpaceText,
    gStaffRollSeniorProducerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesJapanSeniorProducerNamesText,
    gStaffRollSkipText,
    gStaffRollSeniorManagerMarketingText,
    gStaffRollSkipText,
    gStaffRollSeniorManagerMarketingNamesText,
    gStaffRollSkipText,
    gStaffRollGeneralManagerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesJapanGeneralManagerNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnBuenaVistaGamesText,
    gStaffRollSpaceText,
    gStaffRollSeniorProducerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesSeniorProducerNamesText,
    gStaffRollSkipText,
    gStaffRollProducerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesProducerNamesText,
    gStaffRollSkipText,
    gStaffRollLocalizationManagerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesLocalizationManagerNamesText,
    gStaffRollSkipText,
    gStaffRollVpGlobalProductionText,
    gStaffRollSkipText,
    gStaffRollVpGlobalProductionNamesText,
    gStaffRollSkipText,
    gStaffRollVpMarketingText,
    gStaffRollSkipText,
    gStaffRollVpMarketingNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnVoiceTalentsText,
    gStaffRollSpaceText,
    gStaffRollSoraVoiceText,
    gStaffRollSkipText,
    gStaffRollRikuVoiceText,
    gStaffRollSkipText,
    gStaffRollDonaldDuckVoiceText,
    gStaffRollSkipText,
    gStaffRollGoofyVoiceText,
    gStaffRollSkipText,
    gStaffRollAnsemVoiceText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollTheBeastVoiceText,
    gStaffRollSkipText,
    gStaffRollAladdinVoiceText,
    gStaffRollSkipText,
    gStaffRollGenieVoiceText,
    gStaffRollSkipText,
    gStaffRollIagoVoiceText,
    gStaffRollSkipText,
    gStaffRollArielVoiceText,
    gStaffRollSkipText,
    gStaffRollUrsulaVoiceText,
    gStaffRollSkipText,
    gStaffRollJackVoiceText,
    gStaffRollSkipText,
    gStaffRollBoogieVoiceText,
    gStaffRollSkipText,
    gStaffRollHadesVoiceText,
    gStaffRollSkipText,
    gStaffRollPeterPanVoiceText,
    gStaffRollSkipText,
    gStaffRollCaptainHookVoiceText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollCloudVoiceText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSkipText,
    gStaffRollAxelVoiceText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollAndAlsoText,
    gStaffRollSkipText,
    gStaffRollAndAlsoNames1Text,
    gStaffRollSkipText,
    gStaffRollAndAlsoNames2Text,
    gStaffRollSkipText,
    gStaffRollFont1Text,
    gStaffRollBlankText,
    gStaffRollWinnieThePoohTitleText,
    gStaffRollWinnieThePoohWordsMusicByText,
    gStaffRollWinnieThePoohCopyrightText,
    gStaffRollBlankText,
    gStaffRollThisIsHalloweenTitleText,
    gStaffRollThisIsHalloweenWordsMusicByText,
    gStaffRollThisIsHalloweenCopyrightText,
    gStaffRollBlankText,
    gStaffRollUnderTheSeaTitleText,
    gStaffRollUnderTheSeaMusicWordsByText,
    gStaffRollUnderTheSeaCopyright1Text,
    gStaffRollUnderTheSeaCopyright2Text,
    gStaffRollFont0Text,
    gStaffRollSpaceText,
    gStaffRollSecnVoiceRecordingText,
    gStaffRollSpaceText,
    gStaffRollDisneyCharacterVoiceText,
    gStaffRollSkipText,
    gStaffRollDisneyCharacterVoiceNamesText,
    gStaffRollSkipText,
    gStaffRollVoiceDirectorsText,
    gStaffRollSkipText,
    gStaffRollVoiceDirectorsNames1Text,
    gStaffRollSkipText,
    gStaffRollVoiceDirectorsNames2Text,
    gStaffRollSkipText,
    gStaffRollRecordistsText,
    gStaffRollSkipText,
    gStaffRollRecordistsNames1Text,
    gStaffRollSkipText,
    gStaffRollRecordistsNames2Text,
    gStaffRollSkipText,
    gStaffRollProductionCoordinatorsText,
    gStaffRollSkipText,
    gStaffRollProductionCoordinatorsNamesText,
    gStaffRollSkipText,
    gStaffRollRecordingStudioText,
    gStaffRollSkipText,
    gStaffRollRecordingStudioNamesText,
    gStaffRollSkipText,
    gStaffRollVoiceProductionManagementText,
    gStaffRollSkipText,
    gStaffRollVoiceProductionManagementNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnOutsideContractorsText,
    gStaffRollSpaceText,
    gStaffRollMovieCompressionText,
    gStaffRollSkipText,
    gStaffRollMovieCompressionNames1Text,
    gStaffRollSkipText,
    gStaffRollMovieCompressionNames2Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollMovieCompressionNames3Text,
    gStaffRollSkipText,
    gStaffRollMovieCompressionNames4Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollMovieCompressionNames5Text,
    gStaffRollSkipText,
    gStaffRollMovieCompressionNames6Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollMovieCompressionNames7Text,
    gStaffRollSkipText,
    gStaffRollMovieCompressionNames8Text,
    gStaffRollSkipText,
    gStaffRollPvCmMaterialsText,
    gStaffRollSkipText,
    gStaffRollDirectorText,
    gStaffRollSkipText,
    gStaffRollPvCmMaterialsDirectorNamesText,
    gStaffRollSkipText,
    gStaffRollEditorText,
    gStaffRollSkipText,
    gStaffRollPvCmMaterialsEditorNamesText,
    gStaffRollSkipText,
    gStaffRollCoordinatorText,
    gStaffRollSkipText,
    gStaffRollPvCmMaterialsCoordinatorNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnManagementText,
    gStaffRollSpaceText,
    gStaffRollProductionManagerText,
    gStaffRollSkipText,
    gStaffRollManagementProductionManagerNamesText,
    gStaffRollSkipText,
    gStaffRollBusinessManagerText,
    gStaffRollSkipText,
    gStaffRollBusinessManagerNamesText,
    gStaffRollSkipText,
    gStaffRollProductionAssistantText,
    gStaffRollSkipText,
    gStaffRollProductionAssistantNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnQualityAssuranceText,
    gStaffRollSpaceText,
    gStaffRollGeneralManagerText,
    gStaffRollSkipText,
    gStaffRollQualityAssuranceGeneralManagerNamesText,
    gStaffRollSkipText,
    gStaffRollQaDirectorText,
    gStaffRollSkipText,
    gStaffRollQaDirectorNamesText,
    gStaffRollSkipText,
    gStaffRollQaCoordinatorsText,
    gStaffRollSkipText,
    gStaffRollQualityAssuranceQaCoordinatorsNamesText,
    gStaffRollSkipText,
    gStaffRollQaAssistantCoordinatorsText,
    gStaffRollSkipText,
    gStaffRollQaAssistantCoordinatorsNames1Text,
    gStaffRollSkipText,
    gStaffRollQaAssistantCoordinatorsNames2Text,
    gStaffRollSkipText,
    gStaffRollQaStaffText,
    gStaffRollSkipText,
    gStaffRollQaStaffNames1Text,
    gStaffRollSkipText,
    gStaffRollQaStaffNames2Text,
    gStaffRollSkipText,
    gStaffRollQaStaffNames3Text,
    gStaffRollSkipText,
    gStaffRollInformationCenterManagerText,
    gStaffRollSkipText,
    gStaffRollInformationCenterManagerNamesText,
    gStaffRollSkipText,
    gStaffRollInformationCenterCoordinatorText,
    gStaffRollSkipText,
    gStaffRollInformationCenterCoordinatorNamesText,
    gStaffRollSkipText,
    gStaffRollInformationCenterSupervisorsText,
    gStaffRollSkipText,
    gStaffRollInformationCenterSupervisorsNames1Text,
    gStaffRollSkipText,
    gStaffRollInformationCenterSupervisorsNames2Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollAllQaStaffText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnRatingProofreadingText,
    gStaffRollSpaceText,
    gStaffRollRatingAdvisorsText,
    gStaffRollSkipText,
    gStaffRollRatingAdvisorsNames1Text,
    gStaffRollSkipText,
    gStaffRollRatingAdvisorsNames2Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnInformationTechnologyText,
    gStaffRollSpaceText,
    gStaffRollGeneralManagerText,
    gStaffRollSkipText,
    gStaffRollInformationTechnologyGeneralManagerNamesText,
    gStaffRollSkipText,
    gStaffRollEngineersText,
    gStaffRollSkipText,
    gStaffRollEngineersNames1Text,
    gStaffRollSkipText,
    gStaffRollEngineersNames2Text,
    gStaffRollSkipText,
    gStaffRollEngineersNames3Text,
    gStaffRollSkipText,
    gStaffRollEngineersNames4Text,
    gStaffRollSkipText,
    gStaffRollEngineersNames5Text,
    gStaffRollSkipText,
    gStaffRollEngineersNames6Text,
    gStaffRollSkipText,
    gStaffRollCoordinatorsText,
    gStaffRollSkipText,
    gStaffRollCoordinatorsNames1Text,
    gStaffRollSkipText,
    gStaffRollCoordinatorsNames2Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnPublicityTeamText,
    gStaffRollSpaceText,
    gStaffRollPublicityCoordinatorText,
    gStaffRollSkipText,
    gStaffRollPublicityCoordinatorNamesText,
    gStaffRollSkipText,
    gStaffRollPublicityStaffText,
    gStaffRollSkipText,
    gStaffRollPublicityStaffNamesText,
    gStaffRollSkipText,
    gStaffRollPublicityAssistantText,
    gStaffRollSkipText,
    gStaffRollPublicityAssistantNamesText,
    gStaffRollSkipText,
    gStaffRollGeneralProducerText,
    gStaffRollSkipText,
    gStaffRollGeneralProducerNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnSalesMarketingText,
    gStaffRollSpaceText,
    gStaffRollGeneralManagerText,
    gStaffRollSkipText,
    gStaffRollSalesMarketingGeneralManagerNamesText,
    gStaffRollSkipText,
    gStaffRollManagerText,
    gStaffRollSkipText,
    gStaffRollSalesMarketingManagerNamesText,
    gStaffRollSkipText,
    gStaffRollSalesMarketingStaffText,
    gStaffRollSkipText,
    gStaffRollSalesMarketingStaffNames1Text,
    gStaffRollSkipText,
    gStaffRollSalesMarketingStaffNames2Text,
    gStaffRollSkipText,
    gStaffRollSalesMarketingStaffNames3Text,
    gStaffRollSkipText,
    gStaffRollSalesMarketingStaffNames4Text,
    gStaffRollSkipText,
    gStaffRollSalesMarketingStaffNames5Text,
    gStaffRollSkipText,
    gStaffRollSalesMarketingStaffNames6Text,
    gStaffRollSkipText,
    gStaffRollSalesMarketingStaffNames7Text,
    gStaffRollSkipText,
    gStaffRollSalesMarketingStaffNames8Text,
    gStaffRollSkipText,
    gStaffRollSalesMarketingStaffNames9Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnSalesAdministrationText,
    gStaffRollSpaceText,
    gStaffRollManagerText,
    gStaffRollSkipText,
    gStaffRollSalesAdministrationManagerNames1Text,
    gStaffRollSkipText,
    gStaffRollSalesAdministrationManagerNames2Text,
    gStaffRollSkipText,
    gStaffRollSalesAdministrationStaffText,
    gStaffRollSkipText,
    gStaffRollSalesAdministrationStaffNames1Text,
    gStaffRollSkipText,
    gStaffRollSalesAdministrationStaffNames2Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnLegalAffairsText,
    gStaffRollSpaceText,
    gStaffRollLegalManagerText,
    gStaffRollSkipText,
    gStaffRollLegalManagerNamesText,
    gStaffRollSkipText,
    gStaffRollLegalAffairsCoordinatorsText,
    gStaffRollSkipText,
    gStaffRollLegalAffairsCoordinatorsNamesText,
    gStaffRollSkipText,
    gStaffRollPatentDepartmentStaffText,
    gStaffRollSkipText,
    gStaffRollPatentDepartmentStaffNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnSpecialThanksText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks1Names1Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks1Names2Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks1Names3Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks2Names1Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks2Names2Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks2Names3Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks3Names1Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks3Names2Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks3Names3Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks3Names4Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks3Names5Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks4NamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks5Names1Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names2Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names3Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names4Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names5Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names6Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names7Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names8Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names9Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names10Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names11Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names12Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names13Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names14Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names15Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names16Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names17Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names18Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollAllStaffFansText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnJupiterCorporationText,
    gStaffRollSpaceText,
    gStaffRollProducerText,
    gStaffRollSkipText,
    gStaffRollJupiterCorporationProducerNamesText,
    gStaffRollSkipText,
    gStaffRollExecutiveProducerText,
    gStaffRollSkipText,
    gStaffRollJupiterCorporationExecutiveProducerNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollExecutiveProducerText,
    gStaffRollSkipText,
    gStaffRollFinalExecutiveProducerNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollLogoDisneyText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollLogoSquareEnixText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollLogoJupiterText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    NULL,
};

static const s32* sStaffRollSoraScripts[17] = {
    sStaffRollSoraScript0,
    sStaffRollSoraScript1,
    sStaffRollSoraScript2,
    sStaffRollSoraScript3,
    sStaffRollSoraScript4,
    sStaffRollSoraScript5,
    sStaffRollSoraScript6,
    sStaffRollSoraScript7,
    sStaffRollSoraScript8,
    sStaffRollSoraScript9,
    sStaffRollSoraScript10,
    sStaffRollSoraScript11,
    sStaffRollSoraScript12,
    sStaffRollSoraScript13,
    sStaffRollSoraScript14,
    sStaffRollSoraScript15,
    sStaffRollSoraScript16,
};

static const s32* sStaffRollRikuScripts[17] = {
    sStaffRollRikuScript0,
    sStaffRollRikuScript1,
    sStaffRollRikuScript2,
    sStaffRollRikuScript3,
    sStaffRollRikuScript4,
    sStaffRollRikuScript5,
    sStaffRollRikuScript6,
    sStaffRollRikuScript7,
    sStaffRollRikuScript8,
    sStaffRollRikuScript9,
    sStaffRollRikuScript10,
    sStaffRollRikuScript11,
    sStaffRollRikuScript12,
    sStaffRollRikuScript13,
    sStaffRollRikuScript14,
    sStaffRollRikuScript15,
    sStaffRollRikuScript16,
};

static u8* sStaffRollSpaceText = gStaffRollSpaceText;
static const u8* sStaffRollTildeText = gStaffRollTildeJp;
#endif

#ifdef VERSION_EU
static u8* sStaffRollLines[688] = {
    gStaffRollSecnScenarioText,
    gStaffRollSpaceText,
    gStaffRollScenarioSupervisorsText,
    gStaffRollSkipText,
    gStaffRollScenarioSupervisorsNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecn2DArtText,
    gStaffRollSpaceText,
    gStaffRollCharacterArtSupervisorText,
    gStaffRollSkipText,
    gStaffRollCharacterArtSupervisorNamesText,
    gStaffRollSkipText,
    gStaffRollCharacterFaceArtistText,
    gStaffRollSkipText,
    gStaffRollCharacterFaceArtistNamesText,
    gStaffRollSkipText,
    gStaffRollCharacterDesignersText,
    gStaffRollSkipText,
    gStaffRollCharacterDesignersNamesText,
    gStaffRollSkipText,
    gStaffRollEnemyDesignText,
    gStaffRollSkipText,
    gStaffRollEnemyDesignNames1Text,
    gStaffRollSkipText,
    gStaffRollEnemyDesignNames2Text,
    gStaffRollSkipText,
    gStaffRoll2DArtistsText,
    gStaffRollSkipText,
    gStaffRoll2DArtistsNames1Text,
    gStaffRollSkipText,
    gStaffRoll2DArtistsNames2Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecn3DAnimationText,
    gStaffRollSpaceText,
    gStaffRollAnimationStaffText,
    gStaffRollSkipText,
    gStaffRollAnimationStaffNames1Text,
    gStaffRollSkipText,
    gStaffRollAnimationStaffNames2Text,
    gStaffRollSkipText,
    gStaffRollAnimationStaffNames3Text,
    gStaffRollSkipText,
    gStaffRollAnimationStaffNames4Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollDevelopmentTeamText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSkipText,
    gStaffRollSecnPlanningText,
    gStaffRollSpaceText,
    gStaffRollGeneralPlannersText,
    gStaffRollSkipText,
    gStaffRollGeneralPlannersNamesText,
    gStaffRollSkipText,
    gStaffRollTheHundredAcreWoodText,
    gStaffRollSkipText,
    gStaffRollTheHundredAcreWoodNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnEventCreationText,
    gStaffRollSpaceText,
    gStaffRollScriptWriterText,
    gStaffRollSkipText,
    gStaffRollScriptWriterNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnProgrammingText,
    gStaffRollSpaceText,
    gStaffRollProgrammingNames1Text,
    gStaffRollSkipText,
    gStaffRollProgrammingNames2Text,
    gStaffRollSkipText,
    gStaffRollProgrammingNames3Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnGraphicDesignText,
    gStaffRollSpaceText,
    gStaffRollCharacterArtistsText,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames1Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames2Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames3Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames4Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames5Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames6Text,
    gStaffRollSkipText,
    gStaffRollCharacterArtistsNames7Text,
    gStaffRollSkipText,
    gStaffRollBgDesignersText,
    gStaffRollSkipText,
    gStaffRollBgDesignersNames1Text,
    gStaffRollSkipText,
    gStaffRollBgDesignersNames2Text,
    gStaffRollSkipText,
    gStaffRollBgDesignersNames3Text,
    gStaffRollSkipText,
    gStaffRollBgDesignersNames4Text,
    gStaffRollSkipText,
    gStaffRollVfxDesignerText,
    gStaffRollSkipText,
    gStaffRollVfxDesignerNamesText,
    gStaffRollSkipText,
    gStaffRollMenuDesignerText,
    gStaffRollSkipText,
    gStaffRollMenuDesignerNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnSoundText,
    gStaffRollSpaceText,
    gStaffRollSynthesizerOperatorText,
    gStaffRollSkipText,
    gStaffRollSynthesizerOperatorNamesText,
    gStaffRollSkipText,
    gStaffRollSoundEditorText,
    gStaffRollSkipText,
    gStaffRollSoundEditorNamesText,
    gStaffRollSkipText,
    gStaffRollDialogueEditorText,
    gStaffRollSkipText,
    gStaffRollDialogueEditorNamesText,
    gStaffRollSkipText,
    gStaffRollProductionManagerText,
    gStaffRollSkipText,
    gStaffRollSoundProductionManagerNamesText,
    gStaffRollSkipText,
    gStaffRollProductionAssistantsText,
    gStaffRollSkipText,
    gStaffRollProductionAssistantsNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnEndingThemeText,
    gStaffRollSpaceText,
    gStaffRollSecnThemeSongText,
    gStaffRollFont1Text,
    gStaffRollThemeSongWrittenByText,
    gStaffRollThemeSongProducedBy1Text,
    gStaffRollThemeSongProducedBy2Text,
    gStaffRollThemeSongArrangedByText,
    gStaffRollThemeSongKeyboardsProgrammingText,
    gStaffRollThemeSongBasicProgrammingText,
    gStaffRollThemeSongSynthesizerProgrammingText,
    gStaffRollThemeSongAcousticGuitarText,
    gStaffRollThemeSongAllVocalsText,
    gStaffRollBlankText,
    gStaffRollThemeSongRecordedByText,
    gStaffRollThemeSongMixedByText,
    gStaffRollBlankText,
    gStaffRollThemeSongLicensedByText,
    gStaffRollBlankText,
    gStaffRollThemeSongSoundtrackText,
    gStaffRollFont0Text,
    gStaffRollSpaceText,
    gStaffRollSecnBuenaVistaGamesJapanText,
    gStaffRollSpaceText,
    gStaffRollSeniorProducerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesJapanSeniorProducerNamesText,
    gStaffRollSkipText,
    gStaffRollSeniorManagerMarketingText,
    gStaffRollSkipText,
    gStaffRollSeniorManagerMarketingNamesText,
    gStaffRollSkipText,
    gStaffRollGeneralManagerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesJapanGeneralManagerNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnBuenaVistaGamesText,
    gStaffRollSpaceText,
    gStaffRollVpGlobalProductionText,
    gStaffRollSkipText,
    gStaffRollVpGlobalProductionNamesText,
    gStaffRollSkipText,
    gStaffRollSeniorProducerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesSeniorProducerNamesText,
    gStaffRollSkipText,
    gStaffRollProducerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesProducerNamesText,
    gStaffRollSkipText,
    gStaffRollLocalizationManagerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesLocalizationManagerNamesText,
    gStaffRollSkipText,
    gStaffRollVpMarketingText,
    gStaffRollSkipText,
    gStaffRollVpMarketingNamesText,
    gStaffRollSkipText,
    gStaffRollDirectorMarketingText,
    gStaffRollSkipText,
    gStaffRollDirectorMarketingNamesText,
    gStaffRollSkipText,
    gStaffRollManagerMarketingText,
    gStaffRollSkipText,
    gStaffRollManagerMarketingNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnBuenaVistaGamesEmeaText,
    gStaffRollSpaceText,
    gStaffRollSeniorCategoryManagerText,
    gStaffRollSkipText,
    gStaffRollSeniorCategoryManagerNamesText,
    gStaffRollSkipText,
    gStaffRollLocalizationManagerText,
    gStaffRollSkipText,
    gStaffRollBuenaVistaGamesEmeaLocalizationManagerNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnVoiceTalentsText,
    gStaffRollSpaceText,
    gStaffRollSoraVoiceText,
    gStaffRollSkipText,
    gStaffRollRikuVoiceText,
    gStaffRollSkipText,
    gStaffRollDonaldDuckVoiceText,
    gStaffRollSkipText,
    gStaffRollGoofyVoiceText,
    gStaffRollSkipText,
    gStaffRollAnsemVoiceText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollTheBeastVoiceText,
    gStaffRollSkipText,
    gStaffRollAladdinVoiceText,
    gStaffRollSkipText,
    gStaffRollGenieVoiceText,
    gStaffRollSkipText,
    gStaffRollIagoVoiceText,
    gStaffRollSkipText,
    gStaffRollArielVoiceText,
    gStaffRollSkipText,
    gStaffRollUrsulaVoiceText,
    gStaffRollSkipText,
    gStaffRollJackVoiceText,
    gStaffRollSkipText,
    gStaffRollBoogieVoiceText,
    gStaffRollSkipText,
    gStaffRollHadesVoiceText,
    gStaffRollSkipText,
    gStaffRollPeterPanVoiceText,
    gStaffRollSkipText,
    gStaffRollCaptainHookVoiceText,
    gStaffRollSkipText,
    gStaffRollCloudVoiceText,
    gStaffRollSkipText,
    gStaffRollAxelVoiceText,
    gStaffRollSkipText,
    gStaffRollAndAlsoNames1Text,
    gStaffRollSkipText,
    gStaffRollAndAlsoNames2Text,
    gStaffRollSkipText,
    gStaffRollFont1Text,
    gStaffRollBlankText,
    gStaffRollWinnieThePoohTitleText,
    gStaffRollWinnieThePoohWordsMusicByText,
    gStaffRollWinnieThePoohCopyrightText,
    gStaffRollBlankText,
    gStaffRollThisIsHalloweenTitleText,
    gStaffRollThisIsHalloweenWordsMusicByText,
    gStaffRollThisIsHalloweenCopyrightText,
    gStaffRollBlankText,
    gStaffRollUnderTheSeaTitleText,
    gStaffRollUnderTheSeaMusicWordsByText,
    gStaffRollUnderTheSeaCopyright1Text,
    gStaffRollUnderTheSeaCopyright2Text,
    gStaffRollFont0Text,
    gStaffRollSpaceText,
    gStaffRollSecnOutsideContractorsText,
    gStaffRollSpaceText,
    gStaffRollMovieCompressionText,
    gStaffRollSkipText,
    gStaffRollMovieCompressionNames1Text,
    gStaffRollSkipText,
    gStaffRollMovieCompressionNames2Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollMovieCompressionNames3Text,
    gStaffRollSkipText,
    gStaffRollMovieCompressionNames4Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollMovieCompressionNames5Text,
    gStaffRollSkipText,
    gStaffRollMovieCompressionNames6Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollMovieCompressionNames7Text,
    gStaffRollSkipText,
    gStaffRollMovieCompressionNames8Text,
    gStaffRollSkipText,
    gStaffRollPvCmMaterialsText,
    gStaffRollSkipText,
    gStaffRollDirectorText,
    gStaffRollSkipText,
    gStaffRollPvCmMaterialsDirectorNamesText,
    gStaffRollSkipText,
    gStaffRollEditorText,
    gStaffRollSkipText,
    gStaffRollPvCmMaterialsEditorNamesText,
    gStaffRollSkipText,
    gStaffRollCoordinatorText,
    gStaffRollSkipText,
    gStaffRollPvCmMaterialsCoordinatorNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnManagementText,
    gStaffRollSpaceText,
    gStaffRollProductionManagerText,
    gStaffRollSkipText,
    gStaffRollManagementProductionManagerNamesText,
    gStaffRollSkipText,
    gStaffRollBusinessManagerText,
    gStaffRollSkipText,
    gStaffRollBusinessManagerNamesText,
    gStaffRollSkipText,
    gStaffRollProductionAssistantText,
    gStaffRollSkipText,
    gStaffRollProductionAssistantNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnQualityAssuranceText,
    gStaffRollSpaceText,
    gStaffRollGeneralManagerText,
    gStaffRollSkipText,
    gStaffRollQualityAssuranceGeneralManagerNamesText,
    gStaffRollSkipText,
    gStaffRollQaDirectorText,
    gStaffRollSkipText,
    gStaffRollQaDirectorNamesText,
    gStaffRollSkipText,
    gStaffRollQaCoordinatorsText,
    gStaffRollSkipText,
    gStaffRollQualityAssuranceQaCoordinatorsNamesText,
    gStaffRollSkipText,
    gStaffRollQaAssistantCoordinatorsText,
    gStaffRollSkipText,
    gStaffRollQaAssistantCoordinatorsNames1Text,
    gStaffRollSkipText,
    gStaffRollQaTechnicalAssistantsText,
    gStaffRollSkipText,
    gStaffRollQaTechnicalAssistantsNamesText,
    gStaffRollSkipText,
    gStaffRollQaStaffText,
    gStaffRollSkipText,
    gStaffRollQaStaffNames1Text,
    gStaffRollSkipText,
    gStaffRollQaStaffNames2Text,
    gStaffRollSkipText,
    gStaffRollQaStaffNames3Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollAllQaStaffText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnLegalAffairsText,
    gStaffRollSpaceText,
    gStaffRollLegalManagerText,
    gStaffRollSkipText,
    gStaffRollLegalManagerNamesText,
    gStaffRollSkipText,
    gStaffRollLegalAffairsCoordinatorsText,
    gStaffRollSkipText,
    gStaffRollLegalAffairsCoordinatorsNamesText,
    gStaffRollSkipText,
    gStaffRollPatentDepartmentStaffText,
    gStaffRollSkipText,
    gStaffRollPatentDepartmentStaffNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSkipText,
    gStaffRollSecnLocalizationTeamText,
    gStaffRollSkipText,
    gStaffRollGeneralManagerText,
    gStaffRollSkipText,
    gStaffRollLocalizationTeamGeneralManagerNamesText,
    gStaffRollSkipText,
    gStaffRollLocalizationCoordinatorText,
    gStaffRollSkipText,
    gStaffRollLocalizationCoordinatorNamesText,
    gStaffRollSkipText,
    gStaffRollLocalizationSpecialistText,
    gStaffRollSkipText,
    gStaffRollLocalizationSpecialistNamesText,
    gStaffRollSkipText,
    gStaffRollLocalizationSpecialistFrenchText,
    gStaffRollSkipText,
    gStaffRollLocalizationSpecialistFrenchNamesText,
    gStaffRollSkipText,
    gStaffRollLocalizationSpecialistGermanText,
    gStaffRollSkipText,
    gStaffRollLocalizationSpecialistGermanNamesText,
    gStaffRollSkipText,
    gStaffRollLocalizationSpecialistItalianText,
    gStaffRollSkipText,
    gStaffRollLocalizationSpecialistItalianNamesText,
    gStaffRollSkipText,
    gStaffRollLocalizationSpecialistSpanishText,
    gStaffRollSkipText,
    gStaffRollLocalizationSpecialistSpanishNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSkipText,
    gStaffRollSecnSquareEnixIncText,
    gStaffRollSkipText,
    gStaffRollPresidentCeoText,
    gStaffRollSkipText,
    gStaffRollPresidentCeoNamesText,
    gStaffRollSkipText,
    gStaffRollSeniorVicePresidentText,
    gStaffRollSkipText,
    gStaffRollSeniorVicePresidentNamesText,
    gStaffRollSkipText,
    gStaffRollVicePresidentMarketingSalesText,
    gStaffRollSkipText,
    gStaffRollVicePresidentMarketingSalesNamesText,
    gStaffRollSkipText,
    gStaffRollProductionDepartmentManagerText,
    gStaffRollSkipText,
    gStaffRollProductionDepartmentManagerNamesText,
    gStaffRollSkipText,
    gStaffRollAssistantManagerProductionText,
    gStaffRollSkipText,
    gStaffRollAssistantManagerProductionNamesText,
    gStaffRollSkipText,
    gStaffRollAssistantManagerItTechnicalSupportText,
    gStaffRollSkipText,
    gStaffRollAssistantManagerItTechnicalSupportNamesText,
    gStaffRollSkipText,
    gStaffRollProductionLocalizationCoordinatorText,
    gStaffRollSkipText,
    gStaffRollProductionLocalizationCoordinatorNamesText,
    gStaffRollSkipText,
    gStaffRollQaCoordinatorsText,
    gStaffRollSkipText,
    gStaffRollSquareEnixIncQaCoordinatorsNamesText,
    gStaffRollSkipText,
    gStaffRollUkCoordinatorText,
    gStaffRollSkipText,
    gStaffRollUkCoordinatorNamesText,
    gStaffRollSkipText,
    gStaffRollUkTeamText,
    gStaffRollSkipText,
    gStaffRollUkTeamNames1Text,
    gStaffRollSkipText,
    gStaffRollUkTeamNames2Text,
    gStaffRollSkipText,
    gStaffRollFrenchCoordinatorText,
    gStaffRollSkipText,
    gStaffRollFrenchCoordinatorNamesText,
    gStaffRollSkipText,
    gStaffRollFrenchTeamText,
    gStaffRollSkipText,
    gStaffRollFrenchTeamNames1Text,
    gStaffRollSkipText,
    gStaffRollFrenchTeamNames2Text,
    gStaffRollSkipText,
    gStaffRollGermanCoordinatorText,
    gStaffRollSkipText,
    gStaffRollGermanCoordinatorNamesText,
    gStaffRollSkipText,
    gStaffRollGermanTeamText,
    gStaffRollSkipText,
    gStaffRollGermanTeamNames1Text,
    gStaffRollSkipText,
    gStaffRollGermanTeamNames2Text,
    gStaffRollSkipText,
    gStaffRollItalianCoordinatorText,
    gStaffRollSkipText,
    gStaffRollItalianCoordinatorNamesText,
    gStaffRollSkipText,
    gStaffRollItalianTeamText,
    gStaffRollSkipText,
    gStaffRollItalianTeamNames1Text,
    gStaffRollSkipText,
    gStaffRollItalianTeamNames2Text,
    gStaffRollSkipText,
    gStaffRollSpanishCoordinatorText,
    gStaffRollSkipText,
    gStaffRollSpanishCoordinatorNamesText,
    gStaffRollSkipText,
    gStaffRollSpanishTeamText,
    gStaffRollSkipText,
    gStaffRollSpanishTeamNames1Text,
    gStaffRollSkipText,
    gStaffRollSpanishTeamNames2Text,
    gStaffRollSkipText,
    gStaffRollSpanishTeamNames3Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnSpecialThanksText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks1Names1Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks2Names1Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks2Names2Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks2Names3Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks3Names1Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks3Names2Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks3Names3Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks3Names4Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks3Names5Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks4NamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks5Names1Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names2Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names3Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names4Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names5Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names6Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names7Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names8Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names9Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names10Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names11Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names12Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names13Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names14Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names15Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names16Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names17Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names18Text,
    gStaffRollSkipText,
    gStaffRollSpecialThanks5Names19Text,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSpecialThanks6NamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollAllStaffFansText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollSecnJupiterCorporationText,
    gStaffRollSpaceText,
    gStaffRollProducerText,
    gStaffRollSkipText,
    gStaffRollJupiterCorporationProducerNamesText,
    gStaffRollSkipText,
    gStaffRollExecutiveProducerText,
    gStaffRollSkipText,
    gStaffRollJupiterCorporationExecutiveProducerNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollExecutiveProducerText,
    gStaffRollSkipText,
    gStaffRollFinalExecutiveProducerNamesText,
    gStaffRollSkipText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollLogoDisneyText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollLogoSquareEnixText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollLogoJupiterText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    gStaffRollSpaceText,
    gStaffRollBlankText,
    NULL,
};

static const s32* sStaffRollSoraScripts[17] = {
    sStaffRollSoraScript0,
    sStaffRollSoraScript1,
    sStaffRollSoraScript2,
    sStaffRollSoraScript3,
    sStaffRollSoraScript4,
    sStaffRollSoraScript5,
    sStaffRollSoraScript6,
    sStaffRollSoraScript7,
    sStaffRollSoraScript8,
    sStaffRollSoraScript9,
    sStaffRollSoraScript10,
    sStaffRollSoraScript11,
    sStaffRollSoraScript12,
    sStaffRollSoraScript13,
    sStaffRollSoraScript14,
    sStaffRollSoraScript15,
    sStaffRollSoraScript16,
};

static const s32* sStaffRollRikuScripts[17] = {
    sStaffRollRikuScript0,
    sStaffRollRikuScript1,
    sStaffRollRikuScript2,
    sStaffRollRikuScript3,
    sStaffRollRikuScript4,
    sStaffRollRikuScript5,
    sStaffRollRikuScript6,
    sStaffRollRikuScript7,
    sStaffRollRikuScript8,
    sStaffRollRikuScript9,
    sStaffRollRikuScript10,
    sStaffRollRikuScript11,
    sStaffRollRikuScript12,
    sStaffRollRikuScript13,
    sStaffRollRikuScript14,
    sStaffRollRikuScript15,
    sStaffRollRikuScript16,
};

static u8* sStaffRollSpaceText = gStaffRollSpaceText;
static const u8* sStaffRollTildeText = gStaffRollTildeEu;
#endif
#ifdef VERSION_JP
static const StaffRollScene sStaffRollSoraScenes[22] = {
    { 0, 1, 1, 120, 0, -2048, gStaffRollCaptionTiles, 5120, gStaffRollSquareEnixCaptionMap, 2048, gStaffRollCaptionPalette, 32, 30720, 51200, 0, 0 },
    { 1, 1, 1, 300, -1024, -1024, gStaffRollSoraScene1Tiles, 11200, gStaffRollSoraScene1Map, 2048, gStaffRollSoraScene1Palette, 512, 30720, 31744, 0, 1 },
    { 1, 1, 0, 180, -1024, -1024, gStaffRollSoraScene2Tiles, 11200, gStaffRollSoraScene2Map, 2048, gStaffRollSoraScene2Palette, 512, 30720, 31744, 0, 2 },
    { 1, 0, 1, 180, -1024, -1024, gStaffRollSoraScene2Tiles, 11200, gStaffRollSoraScene2Map, 2048, gStaffRollSoraScene2Palette, 512, 30720, 31744, 0, 3 },
    { 1, 1, 0, 180, 0, 1024, gStaffRollSoraScene4Tiles, 11200, gStaffRollSoraScene4Map, 2048, gStaffRollSoraScene4Palette, 512, 30720, 9216, 0, 4 },
    { 1, 0, 1, 180, 0, 1024, gStaffRollSoraScene4Tiles, 11200, gStaffRollSoraScene4Map, 2048, gStaffRollSoraScene4Palette, 512, 30720, 9216, 0, 5 },
    { 1, 1, 0, 180, 0, 1024, gStaffRollSoraScene6Tiles, 11200, gStaffRollSoraScene6Map, 2048, gStaffRollSoraScene6Palette, 512, 36864, 9216, 0, 6 },
    { 1, 0, 1, 180, 0, 1024, gStaffRollSoraScene6Tiles, 11200, gStaffRollSoraScene6Map, 2048, gStaffRollSoraScene6Palette, 512, 36864, 9216, 0, 7 },
    { 1, 1, 0, 180, -1024, -1024, gStaffRollSoraScene8Tiles, 11200, gStaffRollSoraScene8Map, 2048, gStaffRollSoraScene8Palette, 512, 26624, 31744, 0, 8 },
    { 1, 0, 1, 180, -1024, -1024, gStaffRollSoraScene8Tiles, 11200, gStaffRollSoraScene8Map, 2048, gStaffRollSoraScene8Palette, 512, 26624, 31744, 0, 9 },
    { 1, 1, 0, 180, 0, 1024, gStaffRollSoraScene10Tiles, 11200, gStaffRollSoraScene10Map, 2048, gStaffRollSoraScene10Palette, 512, 30720, 9216, 0, 10 },
    { 1, 0, 1, 180, 0, 1024, gStaffRollSoraScene10Tiles, 11200, gStaffRollSoraScene10Map, 2048, gStaffRollSoraScene10Palette, 512, 30720, 9216, 0, 11 },
    { 0, 1, 1, 120, 0, 0, gStaffRollCaptionTiles, 5120, gStaffRollJupiterCaptionMap, 2048, gStaffRollCaptionPalette, 32, 30720, 52224, 0, 0 },
    { 1, 1, 1, 300, 0, -1024, gStaffRollSoraScene13Tiles, 11200, gStaffRollSoraScene13Map, 2048, gStaffRollSoraScene13Palette, 512, 40960, 31744, 0, 12 },
    { 1, 1, 0, 180, 0, 0, gStaffRollSoraScene14Tiles, 11200, gStaffRollSoraScene14Map, 2048, gStaffRollSoraScene14Palette, 512, 30720, 9216, 1, 13 },
    { 1, 0, 1, 180, 0, 0, gStaffRollSoraScene14Tiles, 11200, gStaffRollSoraScene14Map, 2048, gStaffRollSoraScene14Palette, 512, 30720, 9216, 1, 14 },
    { 1, 1, 0, 180, 0, 0, gStaffRollSoraScene16Tiles, 11200, gStaffRollSoraScene16Map, 2048, gStaffRollSoraScene16Palette, 512, 34816, 33792, 0, 15 },
    { 1, 0, 1, 180, 0, 0, gStaffRollSoraScene16Tiles, 11200, gStaffRollSoraScene16Map, 2048, gStaffRollSoraScene16Palette, 512, 30720, 31744, 1, 16 },
    { 0, 1, 1, 120, 0, 0, gStaffRollCaptionTiles, 5120, gStaffRollAndCaptionMap, 2048, gStaffRollCaptionPalette, 32, 30720, 51200, 0, 0 },
    { 1, 1, 0, 180, -1024, -1024, gStaffRollSoraScene19Tiles, 11200, gStaffRollSoraScene19Map, 2048, gStaffRollSoraScene19Palette, 512, 30720, 9216, 0, 17 },
    { 1, 0, 0, 180, -1024, -1024, gStaffRollSoraScene19Tiles, 11200, gStaffRollSoraScene19Map, 2048, gStaffRollSoraScene19Palette, 512, 30720, 9216, 0, 18 },
    { 1, 0, 0, 180, -1024, -1024, gStaffRollSoraScene19Tiles, 11200, gStaffRollSoraScene19Map, 2048, gStaffRollSoraScene19Palette, 512, 30720, 9216, 0, 19 },
};

static const StaffRollScene sStaffRollRikuScenes[22] = {
    { 0, 1, 1, 120, 0, -2048, gStaffRollCaptionTiles, 5120, gStaffRollSquareEnixCaptionMap, 2048, gStaffRollCaptionPalette, 32, 30720, 51200, 0, 0 },
    { 1, 1, 1, 300, -1024, -1024, gStaffRollRikuScene1Tiles, 11200, gStaffRollRikuScene1Map, 2048, gStaffRollRikuScene1Palette, 512, 30720, 31744, 0, 1 },
    { 1, 1, 0, 180, -1024, -1024, gStaffRollRikuScene2Tiles, 11200, gStaffRollRikuScene2Map, 2048, gStaffRollRikuScene2Palette, 512, 30720, 31744, 0, 2 },
    { 1, 0, 1, 180, -1024, -1024, gStaffRollRikuScene2Tiles, 11200, gStaffRollRikuScene2Map, 2048, gStaffRollRikuScene2Palette, 512, 30720, 31744, 0, 3 },
    { 1, 1, 0, 180, 0, 1024, gStaffRollRikuScene4Tiles, 11200, gStaffRollRikuScene4Map, 2048, gStaffRollRikuScene4Palette, 512, 30720, 9216, 0, 4 },
    { 1, 0, 1, 180, 0, 1024, gStaffRollRikuScene4Tiles, 11200, gStaffRollRikuScene4Map, 2048, gStaffRollRikuScene4Palette, 512, 30720, 9216, 0, 5 },
    { 1, 1, 0, 180, 0, 1024, gStaffRollRikuScene6Tiles, 11200, gStaffRollRikuScene6Map, 2048, gStaffRollRikuScene6Palette, 512, 36864, 9216, 0, 6 },
    { 1, 0, 1, 180, 0, 1024, gStaffRollRikuScene6Tiles, 11200, gStaffRollRikuScene6Map, 2048, gStaffRollRikuScene6Palette, 512, 36864, 9216, 0, 7 },
    { 1, 1, 0, 180, -1024, -1024, gStaffRollRikuScene8Tiles, 11200, gStaffRollRikuScene8Map, 2048, gStaffRollRikuScene8Palette, 512, 26624, 31744, 0, 8 },
    { 1, 0, 1, 180, -1024, -1024, gStaffRollRikuScene8Tiles, 11200, gStaffRollRikuScene8Map, 2048, gStaffRollRikuScene8Palette, 512, 26624, 31744, 0, 9 },
    { 1, 1, 0, 180, 0, 1024, gStaffRollRikuScene10Tiles, 11200, gStaffRollRikuScene10Map, 2048, gStaffRollRikuScene10Palette, 512, 30720, 9216, 0, 10 },
    { 1, 0, 1, 180, 0, 1024, gStaffRollRikuScene10Tiles, 11200, gStaffRollRikuScene10Map, 2048, gStaffRollRikuScene10Palette, 512, 30720, 9216, 0, 11 },
    { 0, 1, 1, 120, 0, 0, gStaffRollCaptionTiles, 5120, gStaffRollJupiterCaptionMap, 2048, gStaffRollCaptionPalette, 32, 30720, 52224, 0, 0 },
    { 1, 1, 1, 300, 0, -1024, gStaffRollRikuScene13Tiles, 11200, gStaffRollRikuScene13Map, 2048, gStaffRollRikuScene13Palette, 512, 40960, 31744, 0, 12 },
    { 1, 1, 0, 180, 0, 0, gStaffRollRikuScene14Tiles, 11200, gStaffRollRikuScene14Map, 2048, gStaffRollRikuScene14Palette, 512, 30720, 9216, 1, 13 },
    { 1, 0, 1, 180, 0, 0, gStaffRollRikuScene14Tiles, 11200, gStaffRollRikuScene14Map, 2048, gStaffRollRikuScene14Palette, 512, 30720, 9216, 1, 14 },
    { 1, 1, 0, 180, 0, 0, gStaffRollRikuScene16Tiles, 11200, gStaffRollRikuScene16Map, 2048, gStaffRollRikuScene16Palette, 512, 34816, 33792, 0, 15 },
    { 1, 0, 1, 180, 0, 0, gStaffRollRikuScene16Tiles, 11200, gStaffRollRikuScene16Map, 2048, gStaffRollRikuScene16Palette, 512, 30720, 31744, 1, 16 },
    { 0, 1, 1, 120, 0, 0, gStaffRollCaptionTiles, 5120, gStaffRollAndCaptionMap, 2048, gStaffRollCaptionPalette, 32, 30720, 51200, 0, 0 },
    { 1, 1, 0, 180, -1024, -1024, gStaffRollRikuScene19Tiles, 11200, gStaffRollRikuScene19Map, 2048, gStaffRollRikuScene19Palette, 512, 30720, 9216, 0, 17 },
    { 1, 0, 0, 180, -1024, -1024, gStaffRollRikuScene19Tiles, 11200, gStaffRollRikuScene19Map, 2048, gStaffRollRikuScene19Palette, 512, 30720, 9216, 0, 18 },
    { 1, 0, 0, 180, -1024, -1024, gStaffRollRikuScene19Tiles, 11200, gStaffRollRikuScene19Map, 2048, gStaffRollRikuScene19Palette, 512, 30720, 9216, 0, 19 },
};

#else

static const StaffRollScene sStaffRollSoraScenes[22] = {
    { 0, 1, 1, 120, 0, -2048, gStaffRollCaptionTiles, 5120, gStaffRollSquareEnixCaptionMap, 2048, gStaffRollCaptionPalette, 32, 30720, 51200, 0, 0 },
    { 1, 1, 1, 300, -1024, -1024, gStaffRollSoraScene1Tiles, 11200, gStaffRollSoraScene1Map, 2048, gStaffRollSoraScene1Palette, 512, 30720, 32768, 0, 1 },
    { 1, 1, 0, 180, -1024, -1024, gStaffRollSoraScene2Tiles, 11200, gStaffRollSoraScene2Map, 2048, gStaffRollSoraScene2Palette, 512, 30720, 32768, 0, 2 },
    { 1, 0, 1, 180, -1024, -1024, gStaffRollSoraScene2Tiles, 11200, gStaffRollSoraScene2Map, 2048, gStaffRollSoraScene2Palette, 512, 30720, 32768, 0, 3 },
    { 1, 1, 0, 180, 0, 1024, gStaffRollSoraScene4Tiles, 11200, gStaffRollSoraScene4Map, 2048, gStaffRollSoraScene4Palette, 512, 30720, 11264, 0, 4 },
    { 1, 0, 1, 180, 0, 1024, gStaffRollSoraScene4Tiles, 11200, gStaffRollSoraScene4Map, 2048, gStaffRollSoraScene4Palette, 512, 30720, 11264, 0, 5 },
    { 1, 1, 0, 180, 0, 1024, gStaffRollSoraScene6Tiles, 11200, gStaffRollSoraScene6Map, 2048, gStaffRollSoraScene6Palette, 512, 36864, 10240, 0, 6 },
    { 1, 0, 1, 180, 0, 1024, gStaffRollSoraScene6Tiles, 11200, gStaffRollSoraScene6Map, 2048, gStaffRollSoraScene6Palette, 512, 36864, 10240, 0, 7 },
    { 1, 1, 0, 180, -1024, -1024, gStaffRollSoraScene8Tiles, 11200, gStaffRollSoraScene8Map, 2048, gStaffRollSoraScene8Palette, 512, 26624, 32768, 0, 8 },
    { 1, 0, 1, 180, -1024, -1024, gStaffRollSoraScene8Tiles, 11200, gStaffRollSoraScene8Map, 2048, gStaffRollSoraScene8Palette, 512, 26624, 32768, 0, 9 },
    { 1, 1, 0, 180, 0, 1024, gStaffRollSoraScene10Tiles, 11200, gStaffRollSoraScene10Map, 2048, gStaffRollSoraScene10Palette, 512, 30720, 10240, 0, 10 },
    { 1, 0, 1, 180, 0, 1024, gStaffRollSoraScene10Tiles, 11200, gStaffRollSoraScene10Map, 2048, gStaffRollSoraScene10Palette, 512, 30720, 10240, 0, 11 },
    { 0, 1, 1, 120, 0, 0, gStaffRollCaptionTiles, 5120, gStaffRollJupiterCaptionMap, 2048, gStaffRollCaptionPalette, 32, 30720, 51200, 0, 0 },
    { 1, 1, 1, 300, 0, -1024, gStaffRollSoraScene13Tiles, 11200, gStaffRollSoraScene13Map, 2048, gStaffRollSoraScene13Palette, 512, 40960, 32768, 0, 12 },
    { 1, 1, 0, 180, 0, 2048, gStaffRollSoraScene14Tiles, 11200, gStaffRollSoraScene14Map, 2048, gStaffRollSoraScene14Palette, 512, 30720, 7168, 1, 13 },
    { 1, 0, 1, 180, 0, 2048, gStaffRollSoraScene14Tiles, 11200, gStaffRollSoraScene14Map, 2048, gStaffRollSoraScene14Palette, 512, 30720, 7168, 1, 14 },
    { 1, 1, 0, 180, 0, -2048, gStaffRollSoraScene16Tiles, 11200, gStaffRollSoraScene16Map, 2048, gStaffRollSoraScene16Palette, 512, 34816, 32768, 0, 15 },
    { 1, 0, 1, 180, 0, -2048, gStaffRollSoraScene16Tiles, 11200, gStaffRollSoraScene16Map, 2048, gStaffRollSoraScene16Palette, 512, 39936, 29696, 1, 16 },
    { 0, 1, 1, 120, 0, 0, gStaffRollCaptionTiles, 5120, gStaffRollAndCaptionMap, 2048, gStaffRollCaptionPalette, 32, 30720, 51200, 0, 0 },
    { 1, 1, 0, 180, -1024, -1024, gStaffRollSoraScene19Tiles, 11200, gStaffRollSoraScene19Map, 2048, gStaffRollSoraScene19Palette, 512, 30720, 10240, 0, 17 },
    { 1, 0, 0, 180, -1024, -1024, gStaffRollSoraScene19Tiles, 11200, gStaffRollSoraScene19Map, 2048, gStaffRollSoraScene19Palette, 512, 30720, 10240, 0, 18 },
    { 1, 0, 0, 180, -1024, -1024, gStaffRollSoraScene19Tiles, 11200, gStaffRollSoraScene19Map, 2048, gStaffRollSoraScene19Palette, 512, 30720, 10240, 0, 19 },
};

static const StaffRollScene sStaffRollRikuScenes[22] = {
    { 0, 1, 1, 120, 0, -2048, gStaffRollCaptionTiles, 5120, gStaffRollSquareEnixCaptionMap, 2048, gStaffRollCaptionPalette, 32, 30720, 51200, 0, 0 },
    { 1, 1, 1, 300, -1024, -1024, gStaffRollRikuScene1Tiles, 11200, gStaffRollRikuScene1Map, 2048, gStaffRollRikuScene1Palette, 512, 30720, 32768, 0, 1 },
    { 1, 1, 0, 180, -1024, -1024, gStaffRollRikuScene2Tiles, 11200, gStaffRollRikuScene2Map, 2048, gStaffRollRikuScene2Palette, 512, 30720, 32768, 0, 2 },
    { 1, 0, 1, 180, -1024, -1024, gStaffRollRikuScene2Tiles, 11200, gStaffRollRikuScene2Map, 2048, gStaffRollRikuScene2Palette, 512, 30720, 32768, 0, 3 },
    { 1, 1, 0, 180, 0, 1024, gStaffRollRikuScene4Tiles, 11200, gStaffRollRikuScene4Map, 2048, gStaffRollRikuScene4Palette, 512, 30720, 11264, 0, 4 },
    { 1, 0, 1, 180, 0, 1024, gStaffRollRikuScene4Tiles, 11200, gStaffRollRikuScene4Map, 2048, gStaffRollRikuScene4Palette, 512, 30720, 11264, 0, 5 },
    { 1, 1, 0, 180, 0, 1024, gStaffRollRikuScene6Tiles, 11200, gStaffRollRikuScene6Map, 2048, gStaffRollRikuScene6Palette, 512, 36864, 10240, 0, 6 },
    { 1, 0, 1, 180, 0, 1024, gStaffRollRikuScene6Tiles, 11200, gStaffRollRikuScene6Map, 2048, gStaffRollRikuScene6Palette, 512, 36864, 10240, 0, 7 },
    { 1, 1, 0, 180, -1024, -1024, gStaffRollRikuScene8Tiles, 11200, gStaffRollRikuScene8Map, 2048, gStaffRollRikuScene8Palette, 512, 26624, 32768, 0, 8 },
    { 1, 0, 1, 180, -1024, -1024, gStaffRollRikuScene8Tiles, 11200, gStaffRollRikuScene8Map, 2048, gStaffRollRikuScene8Palette, 512, 26624, 32768, 0, 9 },
    { 1, 1, 0, 180, 0, 1024, gStaffRollRikuScene10Tiles, 11200, gStaffRollRikuScene10Map, 2048, gStaffRollRikuScene10Palette, 512, 30720, 10240, 0, 10 },
    { 1, 0, 1, 180, 0, 1024, gStaffRollRikuScene10Tiles, 11200, gStaffRollRikuScene10Map, 2048, gStaffRollRikuScene10Palette, 512, 30720, 10240, 0, 11 },
    { 0, 1, 1, 120, 0, 0, gStaffRollCaptionTiles, 5120, gStaffRollJupiterCaptionMap, 2048, gStaffRollCaptionPalette, 32, 30720, 51200, 0, 0 },
    { 1, 1, 1, 300, 0, -1024, gStaffRollRikuScene13Tiles, 11200, gStaffRollRikuScene13Map, 2048, gStaffRollRikuScene13Palette, 512, 40960, 32768, 0, 12 },
    { 1, 1, 0, 180, 0, 0, gStaffRollRikuScene14Tiles, 11200, gStaffRollRikuScene14Map, 2048, gStaffRollRikuScene14Palette, 512, 30720, 7168, 1, 13 },
    { 1, 0, 1, 180, 0, 0, gStaffRollRikuScene14Tiles, 11200, gStaffRollRikuScene14Map, 2048, gStaffRollRikuScene14Palette, 512, 30720, 7168, 1, 14 },
    { 1, 1, 0, 180, 0, 0, gStaffRollRikuScene16Tiles, 11200, gStaffRollRikuScene16Map, 2048, gStaffRollRikuScene16Palette, 512, 34816, 32768, 0, 15 },
    { 1, 0, 1, 180, 0, 0, gStaffRollRikuScene16Tiles, 11200, gStaffRollRikuScene16Map, 2048, gStaffRollRikuScene16Palette, 512, 39936, 29696, 1, 16 },
    { 0, 1, 1, 120, 0, 0, gStaffRollCaptionTiles, 5120, gStaffRollAndCaptionMap, 2048, gStaffRollCaptionPalette, 32, 30720, 51200, 0, 0 },
    { 1, 1, 0, 180, -1024, -1024, gStaffRollRikuScene19Tiles, 11200, gStaffRollRikuScene19Map, 2048, gStaffRollRikuScene19Palette, 512, 30720, 10240, 0, 17 },
    { 1, 0, 0, 180, -1024, -1024, gStaffRollRikuScene19Tiles, 11200, gStaffRollRikuScene19Map, 2048, gStaffRollRikuScene19Palette, 512, 30720, 10240, 0, 18 },
    { 1, 0, 0, 180, -1024, -1024, gStaffRollRikuScene19Tiles, 11200, gStaffRollRikuScene19Map, 2048, gStaffRollRikuScene19Palette, 512, 30720, 10240, 0, 19 },
};
#endif

static const SrollInit sStaffRollTextInit = {
    0, 0, 0, 0, 0x40, NULL, NULL, (u8*)(BG_VRAM + 0x40 * TILE_SIZE_4BPP), (u8*)(BG_VRAM + 0xE000),
    15, 13, 0, 14, 0, 0, 0, 30, 32, 0, 0, 30, 32,
};

#if defined(VERSION_US)
const u8 gStaffRollTildeUs[2] = "~";
#elif defined(VERSION_JP)
const u8 gStaffRollTildeJp[2] = "~";
#else
const u8 gStaffRollTildeEu[2] = "~";
#endif

static StaffRollWork* sStaffRollWork;

static s32 Square(s32 x) {
    return x * x;
}

void StaffRollBlendReset(StaffRollWork* work) {
    work->blendMode = 0;
    work->blendDuration = 0;
    work->blendTimer = 0;
    gBldCnt = 0;
    gBldY = 0;
}

u8 StaffRollBlendIsActive(StaffRollWork* work) {
    u8 result;

    result = 1;

    if (work->blendTimer >= work->blendDuration) {
        gBldCnt &= ~BLDCNT_EFFECT_MASK;
        result = 0;
    }

    return result;
}

void StaffRollBlendUpdate(StaffRollWork* work) {
    u16 v;

    if (work->blendTimer < work->blendDuration) {
        v = ((work->blendTimer << 12) / work->blendDuration) << 8 >> 16;
        work->blendTimer = work->blendTimer + 1;
    } else {
        v = 16;
        gBldCnt &= ~BLDCNT_EFFECT_MASK;
        gBldAlpha = 0;
        gBldY = 0;
    }

    switch (work->blendMode) {
    case 0:
    case 2:
        gBldY = 16 - v;
        break;
    case 1:
    case 3:
        gBldY = v;
        break;
    case 4:
        gBldAlpha = v;
        break;
    case 5:
        gBldAlpha = 16 - v;
        break;
    }
}

void StaffRollBlendFadeIn(StaffRollWork* work, u16 flags, s32 dur) {
    work->blendMode = 0;
    work->blendDuration = dur;
    work->blendTimer = 0;
    gBldCnt = flags | BLDCNT_TGT1_BD | BLDCNT_EFFECT_DARKEN;
    gBldY = 16;
}

void StaffRollBlendFadeOut(StaffRollWork* work, u16 flags, s32 dur) {
    work->blendMode = 1;
    work->blendDuration = dur;
    work->blendTimer = 0;
    gBldCnt = flags | BLDCNT_TGT1_BD | BLDCNT_EFFECT_DARKEN;
    gBldY = 0;
}

void StaffRollBlendAlphaIn(StaffRollWork* work, u16 flags, s32 dur) {
    work->blendMode = 4;
    work->blendDuration = dur;
    work->blendTimer = 0;
    gBldCnt = flags | BLDCNT_EFFECT_BLEND;
    gBldAlpha = 0;
}

void StaffRollBlendAlphaOut(StaffRollWork* work, u16 flags, s32 dur) {
    work->blendMode = 5;
    work->blendDuration = dur;
    work->blendTimer = 0;
    gBldCnt = flags | BLDCNT_EFFECT_BLEND;
    gBldAlpha = 16;
}

EvtObj* StaffRollGetScriptObj(StaffRollWork* work) {
    return &work->objs[work->script[work->scriptPos + 3]];
}

void StaffRollRunScript(StaffRollWork* work) {
    StaffRollLabelArg arg;
    EvtObj* e;
    s32 run;
    s32 x;
    s32 y;

    if (work->script == NULL) {
        return;
    }

    run = 1;

    while (run) {
        if (work->scriptFrame != work->script[work->scriptPos + 2]) {
            switch (work->activeOp) {
            case 5:
                if (work->opDuration > work->opTimer) {
                    x = work->moveStartX + (work->moveEndX - work->moveStartX) * work->opTimer / work->opDuration;
                    y = work->opTimer;
                    y = work->moveStartY + (work->moveEndY - work->moveStartY) * y / work->opDuration;
                } else {
                    x = work->moveEndX;
                    y = work->moveEndY;
                    work->activeOp = -1;
                    work->opTimer = 0;
                }

                e = &work->objs[work->moveObj];
                EvtObjSetPos(e, x, y, 0);
                work->opTimer++;
                break;
            case 8:
                if (work->opDuration <= work->opTimer) {
                    work->activeOp = -1;
                    work->opTimer = 0;
                }

                work->opTimer++;
                break;
            }

            break;
        }

        work->activeOp = -1;
        work->opTimer = 0;

        switch (work->script[work->scriptPos]) {
        case 0:
            run = 0;
            continue;
        case 1:
            work->scriptPos = 0;
            work->scriptFrame = 0;
            continue;
        case 2:
            e = StaffRollGetScriptObj(work);
            EvtObjSetAnim(e, work->script[work->scriptPos + 4]);
            break;
        case 3:
            e = StaffRollGetScriptObj(work);
            EvtObjSetDrawFlags(e, work->script[work->scriptPos + 4] | 0x400);
            break;
        case 4:
            e = StaffRollGetScriptObj(work);
            EvtObjSetPos(e, work->script[work->scriptPos + 4] << 8, work->script[work->scriptPos + 5] << 8, 0);
            break;
        case 5:
            e = StaffRollGetScriptObj(work);
            work->activeOp = 5;
            work->moveObj = work->script[work->scriptPos + 3];
            work->moveStartX = e->x;
            work->moveStartY = e->y;
            work->moveEndX = work->script[work->scriptPos + 4] << 8;
            work->moveEndY = work->script[work->scriptPos + 5] << 8;
            work->opDuration = work->script[work->scriptPos + 6];
            break;
        case 6:
            work->subTasks[work->script[work->scriptPos + 3] + 3] =
                CreateEvtObjTaskWithDesc(&work->tasks2, &gTaskDescSrollBChar, StaffRollGetScriptObj(work), work->script[work->scriptPos + 4],
                              work->script[work->scriptPos + 5], 0x2800, 0xF000, 0);
            break;
        case 7:
            TaskKill(&work->tasks2, work->subTasks[work->script[work->scriptPos + 3] + 3]);
            break;
        case 8:
            work->activeOp = 5;
            work->opDuration = work->script[work->scriptPos + 4];
            break;
        case 9:
            FadeStartIn(FADE_MODE_BLACK, work->script[work->scriptPos + 4]);
            break;
        case 10:
            FadeStartOut(FADE_MODE_BLACK, work->script[work->scriptPos + 4]);
            break;
        case 11:
            e = StaffRollGetScriptObj(work);
            e->drawFlags |= SPRITE_FLAG_BLEND;
            StaffRollBlendAlphaIn(work, 0x2000, work->script[work->scriptPos + 4]);
            break;
        case 12:
            e = StaffRollGetScriptObj(work);
            e->drawFlags |= SPRITE_FLAG_BLEND;
            StaffRollBlendAlphaOut(work, 0x2000, work->script[work->scriptPos + 4]);
            break;
        case 13:
            e = StaffRollGetScriptObj(work);
            e->drawFlags |= SPRITE_FLAG_BLEND;
            break;
        case 14:
            e = StaffRollGetScriptObj(work);
            e->drawFlags &= ~SPRITE_FLAG_BLEND;
            break;
        case 15:
            e = StaffRollGetScriptObj(work);
            arg.kind = work->script[work->scriptPos + 4];
            arg.x = e->x;
            arg.y = e->y;
            TaskCreate(&work->tasks2, &gTaskDescSrollBCrtn, &arg);
            break;
        case 16:
            SrollBCharSetMotion(work->subTasks[work->script[work->scriptPos + 3] + 3],
                          work->script[work->scriptPos + 4]);
            break;
        default:
            continue;
        }

        work->scriptPos += work->script[work->scriptPos + 1];
    }

    work->scriptFrame++;
}

void mode_StaffRoll_0() {
    StaffRollWork* w;
    StaffRollWork** p;

    p = &sStaffRollWork;
    w = EwramAlloc(sizeof(StaffRollWork));
    *p = w;
    SetBackdropColor(0, 0, 0);
    SpriteReset();
    w->palette = LoadObjPalette(gSrollSecnPalettes, 0x100);
    w->unk_000 = 1;
    w->unk_001 = 1;
    w->phase = 0;
    w->phaseTimer = 0;
    w->musicFrames = 0;
    w->secnCount = 0;
    StaffRollBlendReset(w);
    w->sceneState = 0;
    w->sceneStep = 0;
    w->sceneTimer = 0;
    w->sceneIndex = -1;
    w->nextScene = 0;
    w->sceneScroll = 0;
    w->creditsState = 0;
    w->creditsEnded = 0;
    w->creditsTimer = 0;
    w->unk_0AC = 0;
    w->lastRow = -1;
    w->scrollY = 0;
    w->imageState = 0;
    w->imageTimer = 0;
    w->endState = 0;
    w->endTimer = 0;
    w->script = NULL;
    w->scriptPos = 0;
    w->scriptFrame = 0;
    w->activeOp = -1;
    w->opTimer = 0;
    TaskPoolInit(&w->tasks, 32);
    TaskPoolInit(&w->tasks2, 32);
    w->subTasks[0] = NULL;
    w->subTasks[1] = NULL;
    w->subTasks[2] = NULL;
    w->subTasks[4] = NULL;
    w->subTasks[5] = NULL;
    w->objs[0].animEntry = NULL;
}

u8 StaffRollWaitStart(StaffRollWork* work) {
    u8 result;

    result = 1;

    if (work->phaseTimer > 74) {
        result = 0;
    }

    work->phaseTimer++;

    return result;
}

u8 StaffRollRunScenes(StaffRollWork* work) {
    StaffRollTaskArg arg;
    u8 result;
    s32 z;

    result = 1;

    if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
        work->scene = sStaffRollRikuScenes;
    } else {
        work->scene = sStaffRollSoraScenes;
    }

    switch (work->sceneState) {
    case 0:
        SetBgMode1();
        SetupBg(0, 0, 28, 0);
        SetupBg(1, 0, 29, 0);
        SetupBg(2, 0, 30, 11);
        SetupBg(3, 0, 31, 0);
        SetBgPriority(0, 0);
        SetBgPriority(1, 0);
        SetBgPriority(2, 0);
        SetBgPriority(3, 0);
        SetBgSize(0, 0);
        SetBgSize(1, 0);
        SetBgSize(2, 0x4000);
        SetBgSize(3, 0x4000);
        SetBgScroll(0, 0, 0);
        SetBgScroll(1, 0, 0);
        SetBgScroll(2, 0, 0);
        SetBgScroll(3, 0, 0);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        SetBgColorMode(0, BGCNT_256COLOR);

        if (work->sceneIndex != work->nextScene) {
            work->sceneIndex = work->nextScene;

            if (work->scene[work->sceneIndex].color256 == 1) {
                SetBgColorMode(0, BGCNT_256COLOR);
            } else {
                SetBgColorMode(0, BGCNT_16COLOR);
            }

            EnableBg(0);
            LoadBgTiles(0, work->scene[work->sceneIndex].tiles, work->scene[work->sceneIndex].tilesSize);
            LoadBgMap(0, work->scene[work->sceneIndex].map, work->scene[work->sceneIndex].mapSize);
            LoadBgPalette(0, work->scene[work->sceneIndex].palette, work->scene[work->sceneIndex].paletteSize);
            SetBgScroll(0, (u16) - (work->scene[work->sceneIndex].x >> 8),
                        (u16) - (work->scene[work->sceneIndex].y >> 8));
        }

        work->sceneState = 1;
        work->sceneStep = 0;
    case 1:
    {
        u8 t;

            if (work->sceneStep == 0) {
                if (work->scene[work->sceneIndex].fadeInBg == 1) {
                    StaffRollBlendFadeIn(work, 17, 30);
                } else {
                    StaffRollBlendFadeIn(work, 16, 30);
                }

                work->sceneStep++;
            }

            StaffRollBlendUpdate(work);
            t = StaffRollBlendIsActive(work);

            if (t) {
                break;
            }

            arg.kind = t;
            arg.animId = work->scene[work->sceneIndex].animId;
            arg.nameIndex = t;
            arg.x = 0x14000;
            arg.y = work->scene[work->sceneIndex].targetY;
            arg.targetX = work->scene[work->sceneIndex].targetX;
            arg.targetY = work->scene[work->sceneIndex].targetY;
            work->subTasks[0] = TaskCreate(&work->tasks, &gTaskDescSrollAName, &arg);
            arg.kind = 1;
            arg.animId = 1;
            arg.nameIndex = work->scene[work->sceneIndex].nameIndex;
            arg.x = -0x5000;
            z = 0x7800;
            arg.targetX = z;
            work->subTasks[1] = TaskCreate(&work->tasks, &gTaskDescSrollAName, &arg);
            arg.kind = 2;
            arg.animId = work->scene[work->sceneIndex].animId;
            arg.nameIndex = work->scene[work->sceneIndex].nameIndex;
            arg.x = z;
            work->subTasks[2] = TaskCreate(&work->tasks, &gTaskDescSrollAName, &arg);
            work->sceneState = 2;
            work->sceneStep = t;
            break;
    }
    case 2:
        work->sceneTimer++;

        if (work->sceneTimer >= work->scene[work->sceneIndex].duration) {
            work->sceneState = 3;
            work->sceneStep = 0;
            work->sceneTimer = 0;
            break;
        }

        if ((work->flags & 1) != 0 || (work->unk_004 & 0x100) != 0) {
            work->sceneState = 3;
            work->sceneStep = 0;
            work->sceneTimer = 0;
            break;
        }

        if ((work->flags & 2) == 0) {
            break;
        }

        TaskKill(&work->tasks, work->subTasks[0]);
        TaskKill(&work->tasks, work->subTasks[1]);
        TaskKill(&work->tasks, work->subTasks[2]);
        work->musicFrames = 0x1518;
        work->sceneState = 4;
        work->sceneStep = 0;
        work->sceneTimer = 0;
        break;
    case 3:
    {
        u8 t;

            if (work->sceneStep == 0) {
                if (work->scene[work->sceneIndex].fadeOutBg == 1) {
                    StaffRollBlendFadeOut(work, 17, 30);
                } else {
                    StaffRollBlendFadeOut(work, 16, 30);
                }

                work->sceneStep++;
            }

            StaffRollBlendUpdate(work);
            t = StaffRollBlendIsActive(work);

            if (t) {
                break;
            }

            if (work->scene[work->sceneIndex].fadeOutBg == 1) {
                DisableBg(0);
            }

            TaskKill(&work->tasks, work->subTasks[0]);
            TaskKill(&work->tasks, work->subTasks[1]);
            TaskKill(&work->tasks, work->subTasks[2]);
            work->nextScene = work->sceneIndex + 1;

            if (work->nextScene > 21) {
                work->sceneState = 4;
            } else {
                work->sceneState = t;
            }

            work->sceneStep = 0;
            work->sceneTimer = 0;
            break;
    }
    case 4:
    {
        s32 v;

        v = work->sceneScroll + 64;
        work->sceneScroll = v;

        if (v > 0x1BFF) {
            SetBgScroll(0, (u16) - (work->scene[work->sceneIndex].x >> 8),
                        (u16)(-(work->scene[work->sceneIndex].y >> 8) + 28));

            if (work->sceneScroll > 0x4000) {
                work->sceneState = 6;
                work->sceneStep = 0;
                work->sceneTimer = 0;
            }
        } else {
            SetBgScroll(0, (u16) - (work->scene[work->sceneIndex].x >> 8),
                        (u16)(-(work->scene[work->sceneIndex].y >> 8) + (v >> 8)));
        }

        break;
    }
    case 5:
        break;
    case 6:
        if (work->sceneStep == 0) {
            StaffRollBlendFadeOut(work, 17, 120);
            work->sceneStep++;
        }

        StaffRollBlendUpdate(work);

        if (!StaffRollBlendIsActive(work)) {
            result = 0;
        }

        break;
    }

    return result;
}

#ifdef VERSION_JP
#define STAFFROLL_SCROLL_FRAMES 0x4321
#define STAFFROLL_SCROLL_SPEED 0x16000000
#define STAFFROLL_SCRIPT_PERIOD 635
#else
#ifdef VERSION_EU
#define STAFFROLL_SCROLL_FRAMES 0x431C
#define STAFFROLL_SCROLL_SPEED 0x15800000
#define STAFFROLL_SCRIPT_PERIOD 635
#else
#define STAFFROLL_SCROLL_FRAMES 0x431C
#define STAFFROLL_SCROLL_SPEED 0x13C00000
#define STAFFROLL_SCRIPT_PERIOD 627
#endif
#endif

u8 StaffRollRunCredits(StaffRollWork* work) {
    u8 buf[80];
    StaffRollLogoArg logo;
    StaffRollSecnArg secn;
    u8 result;
    s32 i;
    u32 row;
    u8* s;
    s32 loop;
    s32 x;
    u32 y;
    s32 total;
    s32 wa;
    s32 wb;
    s32 wc;
    s32 w1;
    s32 n;
    s32 t;
    s32 sub;
    s32 idx;

    result = 1;

    switch (work->creditsState) {
    case 0:
        StaffRollBlendReset(work);
        SetBgMode1();
        SetupBg(0, 0, 28, 0);
        SetupBg(1, 0, 29, 0);
        SetupBg(2, 0, 30, 11);
        SetupBg(3, 0, 31, 0);
        SetBgPriority(0, 0);
        SetBgPriority(1, 0);
        SetBgPriority(2, 0);
        SetBgPriority(3, 0);
        SetBgSize(0, 0);
        SetBgSize(1, 0);
        SetBgSize(2, 0x4000);
        SetBgSize(3, 0x4000);
        SetBgScroll(0, 0, 0);
        SetBgScroll(1, 0, 0);
        SetBgScroll(2, 0, 0);
        SetBgScroll(3, 0, 0);
        EnableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);

        for (i = 0; i < 32; i++) {
            FadeSetPaletteExcluded(i, 1);
        }

        SrollTextInit(&work->text, &sStaffRollTextInit);
        LoadBgPalette(0, gStaffRollTextPalette, 32);
        gDispCnt |= 0;
        gWinIn = (WININ_WIN0_BG0 | WININ_WIN0_BG1 | WININ_WIN0_BG2 | WININ_WIN0_BG3 | WININ_WIN0_OBJ);
        gWinOut = (WINOUT_WIN01_BG1 | WINOUT_WIN01_BG2 | WINOUT_WIN01_BG3 | WINOUT_WIN01_OBJ);
        gWin0H = WIN_RANGE(16, 224);
        gWin0V = WIN_RANGE(8, 152);
        work->creditsState = 1;
        work->creditsTimer = 0;
    case 1:
        work->scrollSpeed = STAFFROLL_SCROLL_SPEED / ((STAFFROLL_SCROLL_FRAMES - work->musicFrames) << 8);
        work->creditsState = 2;
        work->creditsTimer = 0;
        break;
    case 2:
        work->scrollY += work->scrollSpeed;
        sub = work->scrollY >> 8;
        row = work->scrollY >> 11;

        if (sub % 8 == 0 && work->lastRow != row) {
            s = sStaffRollLines[row];

            if (!work->creditsEnded && s == NULL) {
                work->scrollSpeed = 0;
                work->creditsEnded = 1;
            }

            if (*s != '!') {
                SrollTextClearRect(&work->text, 0, (row + 20) & 31, 30, 2, 1);
            }

            if (!work->creditsEnded) {
                SrollTextSetColors(&work->text, 15, 13, 0, 14);
                loop = 1;

                while (loop) {
                    switch (*s) {
                    case '!':
                        loop = 0;
                        break;
                    case '*':
                        switch (s[1]) {
                        case 'D':
                            logo.animId = 0;
                            break;
                        case 'S':
                            logo.animId = 1;
                            break;
                        case 'J':
                            logo.animId = 2;
                            break;
                        }

                        logo.x = 0x7800;
                        logo.y = ((work->scrollY >> 8) + 168) << 8;
                        logo.scrollY = &work->scrollY;
                        logo.scrollSpeed = &work->scrollSpeed;
                        TaskCreate(&work->tasks2, &gTaskDescSrollBLogo, &logo);
                        loop = 0;
                        break;
                    case '<':
                        secn.index = work->secnCount;
                        secn.x = 0x17800;
                        secn.y = ((work->scrollY >> 8) + 168) << 8;
                        secn.scrollY = &work->scrollY;
                        secn.scrollSpeed = &work->scrollSpeed;
                        TaskCreate(&work->tasks2, &gTaskDescSrollBSecn, &secn);
                        work->secnCount++;
                        loop = 0;
                        break;
                    case '[':
                        secn.index = -1;
                        secn.x = 0x7800;
                        secn.y = ((work->scrollY >> 8) + 168) << 8;
                        secn.scrollY = &work->scrollY;
                        secn.scrollSpeed = &work->scrollSpeed;
                        TaskCreate(&work->tasks2, &gTaskDescSrollBSecn, &secn);
                        loop = 0;
                        break;
                    case '#':
                        SrollTextSelectFont(&work->text, s[1] - '0');
                        s += 2;
                        break;
                    case '@':
                        SrollTextSetColors(&work->text, 7, 5, 0, 6);
                        s++;
                        break;
                    case '~':
                        s++;
                        wa = SrollTextMeasureWidth(&work->text, s);
                        wb = SrollTextMeasureWidth(&work->text, sStaffRollTildeText);
                        wc = SrollTextMeasureWidth(&work->text, sStaffRollSpaceText);
                        w1 = wa - wb + wc * 3;
                        x = (240 - w1) >> 1;
                        SrollTextSetColors(&work->text, 7, 5, 0, 6);

                        for (n = 0; s[n] != '~'; n++) {
                            buf[n] = s[n];
                        }

                        buf[n] = ' ';
                        buf[n + 1] = ' ';
                        buf[n + 2] = ' ';
                        buf[n + 3] = 0;
                        w1 = SrollTextMeasureWidth(&work->text, buf);
                        SrollTextDrawStringAtPixelX(&work->text, x, (row + 20) & 31, buf, 1);
                        s += n + 1;

                        for (n = 0; s[n] != 0; n++) {
                            buf[n] = s[n];
                        }

                        buf[n] = 0;
                        SrollTextSetColors(&work->text, 15, 13, 0, 14);
                        SrollTextDrawStringAtPixelX(&work->text, x + w1, (row + 20) & 31, buf, 1);
                        loop = 0;
                        break;
                    case '=':
                        SrollTextDrawStringAtPixelX(&work->text, (240 - SrollTextMeasureWidth(&work->text, s + 1)) >> 1, (row + 20) & 31, s + 1, 1);
                        loop = 0;
                        break;
                    case '-':
                        SrollTextDrawStringAtPixelX(&work->text, 0, (row + 20) & 31, s + 1, 1);
                        loop = 0;
                        break;
                    case '+':
                        SrollTextDrawStringAtPixelX(&work->text, 240 - SrollTextMeasureWidth(&work->text, s + 1), (row + 20) & 31, s + 1, 1);
                        loop = 0;
                        break;
                    default:
                        SrollTextDrawStringAtPixelX(&work->text, (240 - SrollTextMeasureWidth(&work->text, s)) >> 1, (row + 20) & 31, s, 1);
                        loop = 0;
                        break;
                    }
                }
            }
        }

        work->lastRow = row;
        t = work->creditsTimer;

        if (t % STAFFROLL_SCRIPT_PERIOD == 60) {
            work->script = NULL;
            idx = t / STAFFROLL_SCRIPT_PERIOD;

            if (idx <= 16) {
                if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
                    work->script = sStaffRollRikuScripts[idx];
                } else {
                    work->script = sStaffRollSoraScripts[idx];
                }
            }

            work->scriptPos = 0;
            work->scriptFrame = 0;
            work->activeOp = -1;
            work->opTimer = 0;
        }

        work->creditsTimer++;
        SetBgScroll(0, 0, (u16)(work->scrollY >> 8));

        if (work->musicFrames >= STAFFROLL_SCROLL_FRAMES || (work->flags & 2) != 0) {
            work->creditsState = 4;
            work->creditsTimer = 0;
        }

        break;
    case 4:
        work->creditsTimer++;

        if (work->creditsTimer > 120) {
            work->creditsState = 3;
            work->creditsTimer = 0;
        }

        break;
    case 3:
        for (i = 0; i < 32; i++) {
            FadeSetPaletteExcluded(i, 0);
        }

        gDispCnt &= ~DISPCNT_WIN0_ON;
        gWinIn = 0;
        gWinOut = 0;
        gWin0H = 0;
        gWin0V = 0;
        result = 0;
        break;
    }

    StaffRollRunScript(work);
    TaskPoolUpdate(&work->tasks2);
    TaskPoolDraw(&work->tasks2);
    StaffRollBlendUpdate(work);

    return result;
}

u8 StaffRollShowTitleBg(StaffRollWork* work) {
    u8 result;
    u8 t;

    result = 1;

    switch (work->creditsState) {
    case 0:
        TaskPoolDestroy(&work->tasks2);
        DisableBg(0);
        DisableBg(1);
        EnableBg(2);
        DisableBg(3);
        LoadBgTiles(2, gTitleLogoBgTiles, 0x3F00);
        LoadBgMap(2, gTitleLogoBgMap, 0x400);
        LoadBgPalette(2, gTitleLogoBgPalette, 0xA0);
        SetBgAffine(2, 0, 0x100, 0x100, 0x7800, 0x5C00);
        work->creditsState = 1;
        work->creditsTimer = 0;
        break;
    case 1:
        if (work->creditsTimer == 0) {
            FadeStartIn(FADE_MODE_BLACK, 1);
            work->creditsTimer++;
        }

        t = FadeIsActive();

        if (!t) {
            work->creditsState = 2;
            work->creditsTimer = 0;
        }

        break;
    case 2:
        work->creditsTimer++;

        if (work->creditsTimer > 179) {
            work->creditsState = 3;
            work->creditsTimer = 0;
        }

        break;
    case 3:
        if (work->creditsTimer == 0) {
            FadeStartOut(FADE_MODE_BLACK, 120);
            work->creditsTimer++;
        }

        t = FadeIsActive();

        if (!t) {
            work->creditsState = 4;
            work->creditsTimer = 0;
        }

        break;
    case 4:
        work->creditsTimer++;

        if (work->creditsTimer > 119) {
            BlockAudioStop();
            result = 0;
        }

        break;
    }

    return result;
}

#ifdef VERSION_JP
#define STAFFROLL_HOLD_FRAMES 720
#else
#define STAFFROLL_HOLD_FRAMES 900
#endif

u8 StaffRollShowCharacter(StaffRollWork* work) {
    u8 result;

    result = 1;

    switch (work->imageState) {
    case 0:
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        work->imageState = 1;
        work->imageTimer = 0;
        break;
    case 1:
        if (work->imageTimer == 0) {
            FadeStartIn(FADE_MODE_BLACK, 60);
            work->imageTimer++;
        }

        if (!FadeIsActive()) {
            if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
                work->subTasks[0] = TaskCreate(&work->tasks, &gTaskDescSrollCChar, (void*)1);
            } else {
                work->subTasks[0] = TaskCreate(&work->tasks, &gTaskDescSrollCChar, NULL);
            }

            work->imageState = 2;
            work->imageTimer = 0;
        }

        break;
    case 2:
        work->imageTimer++;

        if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
            if (work->imageTimer >= STAFFROLL_HOLD_FRAMES) {
                work->imageState = 3;
                work->imageTimer = 0;
            }
        } else {
            if (work->imageTimer >= 900) {
                work->imageState = 3;
                work->imageTimer = 0;
            }
        }

        break;
    case 3:
        if (work->imageTimer == 0) {
            FadeStartOut(FADE_MODE_BLACK, 120);
            work->imageTimer++;
        }

        if (!FadeIsActive()) {
            result = 0;
        }

        break;
    }

    return result;
}

u8 StaffRollShowSoraImage1(StaffRollWork* work) {
    u8 result;
    u8 t;

    result = 1;

    switch (work->imageState) {
    case 0:
        if (work->imageTimer <= 119) {
            work->imageTimer++;
            break;
        }

        SetBgMode0();
        SetupBg(0, 0, 28, 0);
        SetupBg(1, 0, 30, 0);
        SetupBg(2, 0, 31, 0);
        SetupBg(3, 0, 31, 0);
        SetBgPriority(0, 0);
        SetBgPriority(1, 0);
        SetBgPriority(2, 0);
        SetBgPriority(3, 0);
        SetBgSize(0, 0x8000);
        SetBgSize(1, 0);
        SetBgSize(2, 0);
        SetBgSize(3, 0);
        SetBgScroll(0, 0, 0);
        SetBgScroll(1, 0, 0);
        SetBgScroll(2, 0, 0);
        SetBgScroll(3, 0, 0);
        EnableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        LoadBgTiles(0, gStaffRollSoraImage1Tiles, 0x7200);
        LoadBgMap(0, gStaffRollSoraImage1Map, 0x1000);
        LoadBgPalette(0, gStaffRollSoraImage1Palette, 0x200);
        SetBgScroll(0, 0, 160);
        work->imageState = 1;
        work->imageTimer = 0;
    case 1:
        if (work->imageTimer == 0) {
            FadeStartIn(FADE_MODE_BLACK, 120);
            work->imageTimer++;
        }

        t = FadeIsActive();

        if (!t) {
            work->imageState = 2;
            work->imageTimer = 0;
        }

        break;
    case 2:
        SetBgScroll(0, 0, (u16)(160 - (work->imageTimer >> 1)));

        if (work->imageTimer <= 255) {
            work->imageTimer++;
        }

        if (work->imageTimer > 255) {
            work->imageState = 3;
            work->imageTimer = 0;
        }

        break;
    case 3:
        work->imageTimer++;

        if (work->imageTimer > 179) {
            work->imageState = 4;
            work->imageTimer = 0;
        }

        break;
    case 4:
        if (work->imageTimer == 0) {
            SetBackdropColor(31, 31, 31);
            FadeStartOut(FADE_MODE_WHITE, 120);
            work->imageTimer++;
        }

        if (!FadeIsActive()) {
            SetBgScroll(0, 0, 0);
            result = 0;
        }

        break;
    }

    return result;
}

u8 StaffRollShowSoraImage2(StaffRollWork* work) {
    u8 result;
    u8 t;

    result = 1;

    switch (work->imageState) {
    case 0:
        LoadBgTiles(0, gStaffRollSoraImage2Tiles, 0x53C0);
        LoadBgMap(0, gStaffRollSoraImage2Map, 0x800);
        LoadBgPalette(0, gStaffRollSoraImage2Palette, 0x200);
        work->imageState = 1;
        work->imageTimer = 0;
    case 1:
        if (work->imageTimer == 0) {
            FadeStartIn(FADE_MODE_WHITE, 120);
            work->imageTimer++;
        }

        t = FadeIsActive();

        if (!t) {
            SetBackdropColor(0, 0, 0);
            work->imageState = 2;
            work->imageTimer = 0;
        }

        break;
    case 2:
        work->imageTimer++;

        if (work->imageTimer > 179) {
            work->imageState = 3;
            work->imageTimer = 0;
        }

        break;
    case 3:
        if (work->imageTimer == 0) {
            FadeStartOut(FADE_MODE_BLACK, 60);
            work->imageTimer++;
        }

        if (!FadeIsActive()) {
            result = 0;
        }

        break;
    }

    return result;
}

u8 StaffRollShowRikuImage1(StaffRollWork* work) {
    u8 result;
    u8 t;

    result = 1;

    switch (work->imageState) {
    case 0:
        if (work->imageTimer <= 119) {
            work->imageTimer++;
            break;
        }

        SetBgMode0();
        SetupBg(0, 0, 28, 0);
        SetupBg(1, 0, 30, 0);
        SetupBg(2, 0, 31, 0);
        SetupBg(3, 0, 31, 0);
        SetBgPriority(0, 0);
        SetBgPriority(1, 0);
        SetBgPriority(2, 0);
        SetBgPriority(3, 0);
        SetBgSize(0, 0x8000);
        SetBgSize(1, 0);
        SetBgSize(2, 0);
        SetBgSize(3, 0);
        SetBgScroll(0, 0, 0);
        SetBgScroll(1, 0, 0);
        SetBgScroll(2, 0, 0);
        SetBgScroll(3, 0, 0);
        EnableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        LoadBgTiles(0, gStaffRollRikuImage1Tiles, 0x53C0);
        LoadBgMap(0, gStaffRollRikuImage1Map, 0x800);
        LoadBgPalette(0, gStaffRollRikuImage1Palette, 0x200);
        work->imageState = 1;
        work->imageTimer = 0;
    case 1:
        if (work->imageTimer == 0) {
            FadeStartIn(FADE_MODE_BLACK, 120);
            work->imageTimer++;
        }

        t = FadeIsActive();

        if (!t) {
            work->imageState = 2;
            work->imageTimer = 0;
        }

        break;
    case 2:
        work->imageTimer++;

        if (work->imageTimer > 179) {
            work->imageState = 3;
            work->imageTimer = 0;
        }

        break;
    case 3:
        if (work->imageTimer == 0) {
            SetBackdropColor(31, 31, 31);
            FadeStartOut(FADE_MODE_WHITE, 120);
            work->imageTimer++;
        }

        if (!FadeIsActive()) {
            result = 0;
        }

        break;
    }

    return result;
}

u8 StaffRollShowRikuImage2(StaffRollWork* work) {
    u8 result;
    u8 t;

    result = 1;

    switch (work->imageState) {
    case 0:
        LoadBgTiles(0, gStaffRollRikuImage2Tiles, 0x53C0);
        LoadBgMap(0, gStaffRollRikuImage2Map, 0x800);
        LoadBgPalette(0, gStaffRollRikuImage2Palette, 0x200);
        work->imageState = 1;
        work->imageTimer = 0;
    case 1:
        if (work->imageTimer == 0) {
            FadeStartIn(FADE_MODE_WHITE, 120);
            work->imageTimer++;
        }

        t = FadeIsActive();

        if (!t) {
            work->imageState = 2;
            work->imageTimer = 0;
        }

        break;
    case 2:
        work->imageTimer++;

        if (work->imageTimer > 179) {
            work->imageState = 3;
            work->imageTimer = 0;
        }

        break;
    case 3:
        if (work->imageTimer == 0) {
            FadeStartOut(FADE_MODE_WHITE, 120);
            work->imageTimer++;
        }

        if (!FadeIsActive()) {
            result = 0;
        }

        break;
    }

    return result;
}

u8 StaffRollShowRikuImage3(StaffRollWork* work) {
    u8 result;
    u8 t;

    result = 1;

    switch (work->imageState) {
    case 0:
        LoadBgTiles(0, gStaffRollRikuImage3Tiles, 0x53C0);
        LoadBgMap(0, gStaffRollRikuImage3Map, 0x800);
        LoadBgPalette(0, gStaffRollRikuImage3Palette, 0x200);
        work->imageState = 1;
        work->imageTimer = 0;
    case 1:
        if (work->imageTimer == 0) {
            FadeStartIn(FADE_MODE_WHITE, 120);
            work->imageTimer++;
        }

        t = FadeIsActive();

        if (!t) {
            SetBackdropColor(0, 0, 0);
            work->imageState = 2;
            work->imageTimer = 0;
        }

        break;
    case 2:
        work->imageTimer++;

        if (work->imageTimer > 179) {
            work->imageState = 3;
            work->imageTimer = 0;
        }

        break;
    case 3:
        if (work->imageTimer == 0) {
            FadeStartOut(FADE_MODE_BLACK, 60);
            work->imageTimer++;
        }

        if (!FadeIsActive()) {
            result = 0;
        }

        break;
    }

    return result;
}

u8 StaffRollShowEndScreen(StaffRollWork* work) {
    u8 result;
    u8 t;

    result = 1;

    switch (work->endState) {
    case 0:
        DisableBg(0);
        EnableBg(1);
        DisableBg(2);
        DisableBg(3);
        SetBgScroll(1, 0, 0);
        SetBgColorMode(1, BGCNT_256COLOR);

        if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                LoadBgMap(1, gStaffRollRikuEndMap, 0x800);
                break;
            case LANGUAGE_FRENCH:
                LoadBgMap(1, gStaffRollRikuEndFrenchMap, 0x800);
                break;
            case LANGUAGE_SPANISH:
                LoadBgMap(1, gStaffRollRikuEndSpanishMap, 0x800);
                break;
            case LANGUAGE_ITALIAN:
                LoadBgMap(1, gStaffRollRikuEndItalianMap, 0x800);
                break;
            case LANGUAGE_GERMAN:
            default:
                LoadBgMap(1, gStaffRollRikuEndGermanMap, 0x800);
                break;
            }

            LoadBgTiles(1, gStaffRollRikuEndTiles, 0x45C0);
#else
            LoadBgTiles(1, gStaffRollRikuEndTiles, 0x7F40);
            LoadBgMap(1, gStaffRollRikuEndMap, 0x800);
#endif
            LoadBgPalette(1, gStaffRollRikuEndPalette, 0x200);
        } else {
#ifdef VERSION_EU
            switch (gLanguage) {
            case LANGUAGE_ENGLISH:
                LoadBgMap(1, gStaffRollSoraEndMap, 0x800);
                break;
            case LANGUAGE_FRENCH:
                LoadBgMap(1, gStaffRollSoraEndFrenchMap, 0x800);
                break;
            case LANGUAGE_SPANISH:
                LoadBgMap(1, gStaffRollSoraEndSpanishMap, 0x800);
                break;
            case LANGUAGE_ITALIAN:
                LoadBgMap(1, gStaffRollSoraEndItalianMap, 0x800);
                break;
            case LANGUAGE_GERMAN:
            default:
                LoadBgMap(1, gStaffRollSoraEndGermanMap, 0x800);
                break;
            }

            LoadBgTiles(1, gStaffRollSoraEndTiles, 0x5140);
#else
            LoadBgTiles(1, gStaffRollSoraEndTiles, 0x5BC0);
            LoadBgMap(1, gStaffRollSoraEndMap, 0x800);
#endif
            LoadBgPalette(1, gStaffRollSoraEndPalette, 0x200);
        }

        m4aSongNumStart(SONG_BGM_TITLE);
        work->endState = 1;
        work->endTimer = 0;
        break;
    case 1:
        work->endTimer++;

        if (work->endTimer > 59) {
            work->endState = 2;
            work->endTimer = 0;
        }

        break;
    case 2:
        if (work->endTimer == 0) {
            FadeStartIn(FADE_MODE_BLACK, 120);
            work->endTimer++;
        }

        t = FadeIsActive();

        if (!t) {
            work->endState = 3;
            work->endTimer = 0;
        }

        break;
    default:
        if ((GetKeysPressed() & (A_BUTTON | START_BUTTON)) != 0) {
            result = 0;
        }

        break;
    }

    return result;
}

void mode_StaffRoll_1() {
    StaffRollWork* w;

    w = sStaffRollWork;
    w->unk_004 = 0;
    w->flags = 0;

    switch (w->phase) {
    case 0:
        if (StaffRollWaitStart(w)) {
            break;
        }

        w->phase = 1;
        w->phaseTimer = 0;
        w->musicFrames = 0;
        BlockAudioStart();
    case 1:
    {
        if (StaffRollRunScenes(w)) {
            break;
        }

        w->phase = 2;
        w->phaseTimer = 0;
        DmaFill16(3, 0, VRAM, 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(1), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(2), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(3), 0x4000);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        w->creditsState = 0;
        w->creditsTimer = 0;
        break;
    }
    case 2:
    {
        if (StaffRollRunCredits(w)) {
            break;
        }

        w->phase = 3;
        w->phaseTimer = 0;
        DmaFill16(3, 0, VRAM, 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(1), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(2), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(3), 0x4000);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        w->creditsState = 0;
        w->creditsTimer = 0;
        break;
    }
    case 3:
    {
        if (StaffRollShowTitleBg(w)) {
            break;
        }

        DmaFill16(3, 0, VRAM, 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(1), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(2), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(3), 0x4000);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);

        if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
            w->phase = 7;
            w->imageState = 0;
        } else {
            w->phase = 5;
            w->imageState = 0;
        }

        w->phaseTimer = 0;
        w->imageTimer = 0;
        break;
    }
    case 4:
    {
        if (StaffRollShowCharacter(w)) {
            break;
        }

        w->phase = 10;
        w->phaseTimer = 0;
        DmaFill16(3, 0, VRAM, 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(1), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(2), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(3), 0x4000);
        w->endState = 0;
        w->endTimer = 0;
        break;
    }
    case 5:
    {
        if (StaffRollShowSoraImage1(w)) {
            break;
        }

        w->phase = 6;
        w->phaseTimer = 0;
        DmaFill16(3, 0, VRAM, 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(1), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(2), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(3), 0x4000);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        w->imageState = 0;
        w->imageTimer = 0;
        break;
    }
    case 6:
    {
        if (StaffRollShowSoraImage2(w)) {
            break;
        }

        w->phase = 4;
        w->phaseTimer = 0;
        DmaFill16(3, 0, VRAM, 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(1), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(2), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(3), 0x4000);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        w->imageState = 0;
        w->imageTimer = 0;
        break;
    }
    case 7:
    {
        if (StaffRollShowRikuImage1(w)) {
            break;
        }

        w->phase = 8;
        w->phaseTimer = 0;
        DmaFill16(3, 0, VRAM, 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(1), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(2), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(3), 0x4000);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        w->imageState = 0;
        w->imageTimer = 0;
        break;
    }
    case 8:
    {
        if (StaffRollShowRikuImage2(w)) {
            break;
        }

        w->phase = 9;
        w->phaseTimer = 0;
        DmaFill16(3, 0, VRAM, 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(1), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(2), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(3), 0x4000);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        w->imageState = 0;
        w->imageTimer = 0;
        break;
    }
    case 9:
    {
        if (StaffRollShowRikuImage3(w)) {
            break;
        }

        w->phase = 4;
        w->phaseTimer = 0;
        DmaFill16(3, 0, VRAM, 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(1), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(2), 0x40);
        DmaFill16(3, 0, BG_CHAR_ADDR(3), 0x4000);
        DisableBg(0);
        DisableBg(1);
        DisableBg(2);
        DisableBg(3);
        w->imageState = 0;
        w->imageTimer = 0;
        break;
    }
    case 10:
        if (StaffRollShowEndScreen(w)) {
            break;
        }

        w->phase = 11;
        w->phaseTimer = 0;
        break;
    case 11:
        if (w->phaseTimer == 0) {
            FadeStartOut(FADE_MODE_BLACK, 120);
        }

        w->phaseTimer++;

        if (w->phaseTimer > 120) {
#ifdef VERSION_EU
            DoSoftReset();
#else
            SoftReset(RESET_ALL);
#endif
        }

        break;
    }

    TaskPoolUpdate(&w->tasks);
    TaskPoolDraw(&w->tasks);
    BlockAudioUpdate();
    w->musicFrames++;
}

void mode_StaffRoll_2() {
    StaffRollWork* w;

    w = sStaffRollWork;
    ReleaseObjPalette(w->palette);
    TaskPoolDestroy(&w->tasks);

    if (sStaffRollWork != NULL) {
        EwramFree(w);
        sStaffRollWork = NULL;
    }
}

Mode gModeStaffRoll = {
    "mode_StaffRoll",
    (ModeInitFunc)mode_StaffRoll_0,
    mode_StaffRoll_1,
    mode_StaffRoll_2,
};
